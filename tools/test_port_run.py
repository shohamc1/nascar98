"""Tests for the native runner, build/port/nascar98 (make -f port/port.mk nascar98).

Each test skips when the runner or the disc is missing.
"""

import os
import re
import pathlib
import subprocess
import tempfile
import unittest
import wave

from PIL import Image

ROOT = pathlib.Path(__file__).resolve().parent.parent
RUNNER = ROOT / "build/port/nascar98"
TRACK1 = ROOT / "NASCAR 98 (USA)/NASCAR 98 (USA) (Track 1).bin"


SAVES = tempfile.TemporaryDirectory()  # memory cards stay out of the checkout


def run(timeout: float, **env: str) -> subprocess.CompletedProcess:
    return subprocess.run(
        [str(RUNNER)],
        cwd=ROOT,
        env={**os.environ, "NASCAR98_HEADLESS": "1", "NASCAR98_SAVES": SAVES.name, **env},
        capture_output=True,
        text=True,
        timeout=timeout,
    )


MAGENTA = (255, 0, 255, 255)
WHITE_LIMIT = 50  # 525 with the reordered stores, 0 without


def magenta_pixels(path: pathlib.Path) -> int:
    with Image.open(path) as image:
        rgb = image.convert("RGB").tobytes()
    return sum(1 for i in range(0, len(rgb), 3) if rgb[i] > 200 and rgb[i + 1] < 60 and rgb[i + 2] > 200)


MAP = ROOT / "build/port/nascar98.map"


def retail_addresses() -> dict[str, int]:
    text = (ROOT / "config/symbol_addrs.txt").read_text()
    return {m[1]: int(m[2], 16) for m in re.finditer(r"^(\w+) = 0x([0-9A-Fa-f]+);", text, re.M)}


def port_addresses() -> dict[str, int]:
    found = {}
    for line in MAP.read_text().splitlines():
        parts = line.split()
        if len(parts) == 4 and re.fullmatch(r"[0-9a-f]{8}", parts[0]):
            found[parts[3]] = int(parts[0], 16)
    return found


@unittest.skipUnless(MAP.exists(), "no link map: make -f port/port.mk nascar98")
class Layout(unittest.TestCase):
    def test_globals_keep_retail_neighbours(self) -> None:
        # The game reads past one global into the next, as GCC laid them
        # out: FontDrawString takes glyph widths from D_800A2D88[scale].
        retail, port = retail_addresses(), port_addresses()
        names = re.findall(r"^[A-Za-z_][\w ]*?\b(\w+)(?:\[[^\]]*\])* = ", (ROOT / "src/globals.c").read_text(), re.M)
        moved = []
        for a, b in zip(names, names[1:]):
            ra = int(a[2:], 16) if re.fullmatch(r"D_[0-9A-F]{8}", a) else retail.get(a)
            rb = int(b[2:], 16) if re.fullmatch(r"D_[0-9A-F]{8}", b) else retail.get(b)
            if ra is None or rb is None or not 0 < rb - ra <= 16:
                continue
            if a not in port or b not in port or port[b] - port[a] != rb - ra:
                moved.append(f"{a} -> {b}")
        self.assertEqual(moved, [])


SCRATCHPAD = range(0x1F800000, 0x1F800400)


@unittest.skipUnless((ROOT / "build/port/src").exists(), "no filtered sources: make -f port/port.mk objects")
class UndefinedBehaviour(unittest.TestCase):
    def test_no_pointer_arithmetic_from_null(self) -> None:
        # GCC 2.7.2 adds to a null-based pointer as it would to any other;
        # clang marks the result poison and may drop the stores through it
        # (func_800525A8's skid marks read stale stack). Only scratchpad
        # addresses may serve as an integer base.
        import emu_swap

        found = []
        with tempfile.TemporaryDirectory() as tmp:
            for src in sorted((ROOT / "build/port/src").glob("*.c")):
                extra = ["-include", "port_prelude.h"] if src.stem == "memory_card" else []
                ir = pathlib.Path(tmp) / f"{src.stem}.ll"
                cmd = [str(emu_swap.LLVM / "clang"), "--target=wasm32", *emu_swap.CFLAGS, *extra, "-S", "-emit-llvm", str(src), "-o", str(ir)]
                subprocess.run(cmd, cwd=ROOT, check=True, capture_output=True)
                func = None
                for line in ir.read_text().splitlines():
                    if m := re.match(r"define .*@(\w+)\(", line):
                        func = m[1]
                    m = re.search(r"getelementptr inbounds[^,]*, ptr (null|inttoptr \(i32 (\d+) to ptr\)), i32 %", line)
                    if m and (m[2] is None or int(m[2]) not in SCRATCHPAD):
                        found.append(f"{src.stem}: {func}")
        self.assertEqual(sorted(set(found)), [])


@unittest.skipUnless(RUNNER.exists(), "no runner: make -f port/port.mk nascar98")
@unittest.skipUnless(TRACK1.exists(), "no disc")
class Run(unittest.TestCase):
    def test_missing_disc(self) -> None:
        result = run(10, NASCAR98_TRACK1="/nonexistent/Track 1.bin")
        self.assertEqual(result.returncode, 2, result.stderr)
        self.assertIn("/nonexistent/Track 1.bin", result.stderr)
        self.assertIn("NASCAR98_TRACK1", result.stderr)

    def test_wrong_disc(self) -> None:
        # A zero-filled file and Track 2 (audio) both lack an ISO 9660 volume.
        with tempfile.NamedTemporaryFile(suffix=".bin") as zeros:
            zeros.write(bytes(2352 * 32))
            zeros.flush()
            for path in (zeros.name, str(TRACK1).replace("Track 1", "Track 2")):
                result = run(10, NASCAR98_TRACK1=path)
                self.assertEqual(result.returncode, 2, result.stderr[-2000:])
                self.assertIn(path, result.stderr)
                self.assertIn("NASCAR98_TRACK1", result.stderr)

    def test_boot_600_frames(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            shot = pathlib.Path(tmp) / "shot.bmp"
            result = run(60, NASCAR98_FRAMES="600", NASCAR98_SCREENSHOT=f"600:{shot}")
            self.assertEqual(result.returncode, 0, result.stderr[-2000:])
            self.assertIn("nascar98: stopped after 600 frames", result.stderr)
            data = shot.read_bytes()
            self.assertEqual(data[:2], b"BM", result.stderr[-2000:])
            # The title screen: a picture, not one flat colour.
            pixels = data[int.from_bytes(data[10:14], "little") :]
            self.assertGreater(len({pixels[i : i + 4] for i in range(0, len(pixels) - 4, 4)}), 1000)

    def test_start_leaves_title(self) -> None:
        # Start pressed at frame 620 moves on from the title; without it, the title stays.
        with tempfile.TemporaryDirectory() as tmp:
            d = pathlib.Path(tmp)
            (d / "pad.txt").write_text("0 -\n620 start\n625 -\n")
            shots = []
            for name, pad in (("idle", ""), ("start", str(d / "pad.txt"))):
                shot = d / f"{name}.bmp"
                result = run(60, NASCAR98_FRAMES="900", NASCAR98_SCREENSHOT=f"900:{shot}", NASCAR98_PAD=pad)
                self.assertEqual(result.returncode, 0, result.stderr[-2000:])
                shots.append(shot.read_bytes())
            self.assertNotEqual(shots[0], shots[1])

    def test_replacement_texture(self) -> None:
        # Dump the uploads up to the memory card prompt, replace each one
        # (but the 320 x 240 movie frames) with a 2x magenta copy, and find
        # magenta on screen: the prompt's text samples a replacement.
        with tempfile.TemporaryDirectory() as tmp:
            d = pathlib.Path(tmp)
            (d / "pad.txt").write_text("0 -\n620 start\n625 -\n")
            dump, textures = d / "dump", d / "textures"
            dump.mkdir()
            textures.mkdir()
            env = {"NASCAR98_FRAMES": "700", "NASCAR98_PAD": str(d / "pad.txt")}
            result = run(120, NASCAR98_DUMP_TEXTURES=str(dump), NASCAR98_SCREENSHOT=f"700:{d / 'plain.bmp'}", **env)
            self.assertEqual(result.returncode, 0, result.stderr[-2000:])
            for png in dump.glob("*.png"):
                with Image.open(png) as image:
                    if image.size != (320, 240):
                        Image.new("RGBA", (image.width * 2, image.height * 2), MAGENTA).save(textures / png.name)
            self.assertTrue(any(textures.iterdir()))
            result = run(120, NASCAR98_TEXTURES=str(textures), NASCAR98_SCREENSHOT=f"700:{d / 'swap.bmp'}", **env)
            self.assertEqual(result.returncode, 0, result.stderr[-2000:])
            self.assertEqual(magenta_pixels(d / "plain.bmp"), 0)
            self.assertGreater(magenta_pixels(d / "swap.bmp"), 100)

    def test_title_music(self) -> None:
        # The title screen plays a CD audio track: sound with no input.
        with tempfile.TemporaryDirectory() as tmp:
            wav = pathlib.Path(tmp) / "out.wav"
            result = run(60, NASCAR98_FRAMES="300", NASCAR98_WAV=str(wav))
            self.assertEqual(result.returncode, 0, result.stderr[-2000:])
            with wave.open(str(wav)) as w:
                w.setpos(120 * 735)
                music = w.readframes(120 * 735)
            self.assertGreater(sum(1 for i in range(0, len(music), 2) if music[i : i + 2] != b"\0\0"), 50000)

    def test_menu_sounds(self) -> None:
        # X at frame 700 closes the memory card prompt with a sound effect.
        with tempfile.TemporaryDirectory() as tmp:
            d = pathlib.Path(tmp)
            (d / "pad.txt").write_text("0 -\n620 start\n625 -\n700 cross\n705 -\n")
            result = run(60, NASCAR98_FRAMES="760", NASCAR98_PAD=str(d / "pad.txt"), NASCAR98_WAV=str(d / "out.wav"))
            self.assertEqual(result.returncode, 0, result.stderr[-2000:])
            with wave.open(str(d / "out.wav")) as w:
                self.assertEqual((w.getnchannels(), w.getframerate(), w.getsampwidth()), (2, 44100, 2))
                self.assertAlmostEqual(w.getnframes(), 760 * 735, delta=735)  # the last VSync exits first
                w.setpos(700 * 735)
                tail = w.readframes(60 * 735)
            self.assertGreater(sum(1 for i in range(0, len(tail), 2) if tail[i : i + 2] != b"\0\0"), 1000)

    def test_race_loads(self) -> None:
        # Main menu, Single Race, Race Setup's Done, then Race, then Start
        # at the loading screen, whose loop polls the pads with no VSync.
        script = "0 -\n620 start\n625 -\n700 cross\n705 -\n760 cross\n765 -\n"
        script += "".join(f"{f} down\n{f + 5} -\n" for f in (900, 940, 980, 1020)) + "1060 cross\n1065 -\n"
        script += "".join(f"{f} down\n{f + 5} -\n" for f in (1200, 1240, 1280, 1320)) + "1360 cross\n1365 -\n"
        script += "".join(f"{f} start\n{f + 5} -\n" for f in range(1500, 3000, 100))
        with tempfile.TemporaryDirectory() as tmp:
            d = pathlib.Path(tmp)
            (d / "pad.txt").write_text(script)
            shot = d / "race.bmp"
            result = run(
                120,
                NASCAR98_FRAMES="4000",
                NASCAR98_PAD=str(d / "pad.txt"),
                NASCAR98_SCALE="1",
                NASCAR98_SCREENSHOT=f"3990:{shot}",
            )
            self.assertEqual(result.returncode, 0, result.stderr[-2000:])
            self.assertIn("nascar98: stopped after 4000 frames", result.stderr)
            # Subdivided road quads take a corner UV from the scratchpad. When
            # the port reorders the game's s32 and u16 stores there, the
            # corner reads past the tile into white (0x7FFF) texels.
            # The player's car, whose logo is white, sits in x 80 to 224,
            # y 100 to 199.
            with Image.open(shot) as image:
                rgb = image.convert("RGB")
                white = sum(
                    1
                    for y in range(80, 240)
                    for x in range(320)
                    if not (80 <= x < 225 and 100 <= y < 200) and rgb.getpixel((x, y)) == (248, 248, 248)
                )
            self.assertLess(white, WHITE_LIMIT, "white texels on the road")

    def test_watchdog_fires(self) -> None:
        result = run(20, NASCAR98_WATCHDOG="1", NASCAR98_HANG="1")
        self.assertEqual(result.returncode, 3, result.stderr[-2000:])
        self.assertIn("watchdog", result.stderr)
        self.assertIn("last log lines", result.stderr)
        # The hang is inside VSync, so it must be the last SDK call shown.
        calls = result.stderr.split("last SDK calls:", 1)[1]
        self.assertEqual(calls.split()[-1], "VSync", result.stderr[-2000:])


if __name__ == "__main__":
    unittest.main()
