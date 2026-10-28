#!/usr/bin/env python3
"""Run the port and an emulator on the same pad script, then compare races.

Usage:
    emu_compare.py emu --core CORE --bios BIOS --pad PAD --frames N [--every K] [--start F] OUT
    emu_compare.py port --pad PAD --frames N [--every K] [--start F] OUT
    emu_compare.py report PORT_DIR EMU_DIR [--html OUT.html]

`emu` runs a libretro PSX core (Beetle PSX, mednafen's PSX emulation) with
no window. `port` runs build/port/nascar98 headless with NASCAR98_DUMP. Both
write FRAME.ram (main RAM, 2 MB from 0x80000000) and FRAME.bmp every K
frames from frame F. PAD is the port's NASCAR98_PAD format: "FRAME BUTTON[+BUTTON...]"
lines, "-" for none, held until the next line.

`report` decodes the cars from each dump and lines the two runs up on the
game's frame counter (CLOCK, which counts the 30 Hz game frames), not on
VBlank numbers: the console's CD
loads take real time and the port's don't, so the same frame lands at
different moments.
"""

import argparse
import ctypes
import dataclasses
import html
import os
import pathlib
import re
import shutil
import struct
import subprocess
import sys
import wave

ROOT = pathlib.Path(__file__).resolve().parent.parent
RAM_BASE = 0x80000000
RAM_SIZE = 0x200000
CUE = ROOT / "NASCAR 98 (USA)" / "NASCAR 98 (USA).cue"

# The port's script names, in libretro RetroPad ids (Beetle PSX maps B to
# cross, A to circle, Y to square, X to triangle).
RETRO_IDS = {
    "cross": 0, "square": 1, "select": 2, "start": 3, "up": 4, "down": 5,
    "left": 6, "right": 7, "circle": 8, "triangle": 9, "l1": 10, "r1": 11,
    "l2": 12, "r2": 13,
}  # fmt: skip


def parse_pad(text: str) -> list[tuple[int, set[str]]]:
    script = []
    for line in text.splitlines():
        parts = line.split()
        if len(parts) < 2 or not parts[0].lstrip("-").isdigit():
            continue
        names = set() if parts[1] == "-" else set(parts[1].split("+"))
        unknown = names - RETRO_IDS.keys()
        if unknown:
            raise SystemExit(f"emu_compare: unknown button {sorted(unknown)} in pad script")
        script.append((int(parts[0]), names))
    return script


def held(script: list[tuple[int, set[str]]], frame: int) -> set[str]:
    buttons: set[str] = set()
    for start, names in script:
        if start > frame:
            break
        buttons = names
    return buttons


def write_bmp(path: pathlib.Path, width: int, height: int, rgb: bytes) -> None:
    row = (width * 3 + 3) & ~3
    body = bytearray()
    for y in range(height - 1, -1, -1):
        line = bytearray(rgb[y * width * 3 : (y + 1) * width * 3])
        for x in range(width):  # RGB to BGR
            line[x * 3], line[x * 3 + 2] = line[x * 3 + 2], line[x * 3]
        body += line + bytes(row - width * 3)
    head = struct.pack("<2sIHHI", b"BM", 54 + len(body), 0, 0, 54)
    info = struct.pack("<IiiHHIIiiII", 40, width, height, 1, 24, 0, len(body), 2835, 2835, 0, 0)
    path.write_bytes(head + info + body)


# libretro.h
ENV_GET_CAN_DUPE = 3
ENV_GET_SYSTEM_DIRECTORY = 9
ENV_GET_VARIABLE = 15
ENV_SET_PIXEL_FORMAT = 10
ENV_GET_SAVE_DIRECTORY = 31
RETRO_MEMORY_SAVE_RAM = 0  # Beetle's card in slot 1
RETRO_MEMORY_SYSTEM_RAM = 2
PIXEL_XRGB8888 = 1
PIXEL_RGB565 = 2


class GameInfo(ctypes.Structure):
    _fields_ = [("path", ctypes.c_char_p), ("data", ctypes.c_void_p), ("size", ctypes.c_size_t), ("meta", ctypes.c_char_p)]


ENV_CB = ctypes.CFUNCTYPE(ctypes.c_bool, ctypes.c_uint, ctypes.c_void_p)
VIDEO_CB = ctypes.CFUNCTYPE(None, ctypes.c_void_p, ctypes.c_uint, ctypes.c_uint, ctypes.c_size_t)
AUDIO_CB = ctypes.CFUNCTYPE(None, ctypes.c_int16, ctypes.c_int16)
AUDIO_BATCH_CB = ctypes.CFUNCTYPE(ctypes.c_size_t, ctypes.c_void_p, ctypes.c_size_t)
POLL_CB = ctypes.CFUNCTYPE(None)
INPUT_CB = ctypes.CFUNCTYPE(ctypes.c_int16, ctypes.c_uint, ctypes.c_uint, ctypes.c_uint, ctypes.c_uint)


class Emulator:
    """A libretro PSX core with the disc loaded and a pad script on port 1."""

    def __init__(self, core: str, bios: str, pad: str, out: pathlib.Path, options: dict[str, str] | None = None) -> None:
        system = out / "system"
        system.mkdir(parents=True, exist_ok=True)
        (system / "scph5501.bin").write_bytes(pathlib.Path(bios).read_bytes())
        script = parse_pad(pathlib.Path(pad).read_text())
        self.core = ctypes.CDLL(core)
        self.frame = 0
        self.input_frame: int | None = None  # the script's clock, if not frame
        self.format = PIXEL_RGB565
        self.video = None
        system_dir = ctypes.c_char_p(str(system).encode())
        values = {k.encode(): ctypes.c_char_p(v.encode()) for k, v in (options or {}).items()}

        def environment(cmd: int, data: int) -> bool:
            if cmd in (ENV_GET_SYSTEM_DIRECTORY, ENV_GET_SAVE_DIRECTORY):
                ctypes.cast(data, ctypes.POINTER(ctypes.c_char_p))[0] = system_dir.value
                return True
            if cmd == ENV_SET_PIXEL_FORMAT:
                self.format = ctypes.cast(data, ctypes.POINTER(ctypes.c_int))[0]
                return self.format in (PIXEL_XRGB8888, PIXEL_RGB565)
            if cmd == ENV_GET_VARIABLE:  # struct retro_variable { key, value }
                pair = ctypes.cast(data, ctypes.POINTER(ctypes.c_char_p))
                if pair[0] in values:
                    pair[1] = values[pair[0]].value
                    return True
                return False
            if cmd == ENV_GET_CAN_DUPE:
                ctypes.cast(data, ctypes.POINTER(ctypes.c_bool))[0] = True
                return True
            return False

        def video(data: int, width: int, height: int, pitch: int) -> None:
            if data:
                self.video = (ctypes.string_at(data, pitch * height), width, height, pitch)

        def input_state(port: int, device: int, index: int, button: int) -> int:
            if port != 0 or device != 1:  # RETRO_DEVICE_JOYPAD
                return 0
            clock = self.frame if self.input_frame is None else self.input_frame
            return int(any(RETRO_IDS[n] == button for n in held(script, clock)))

        def audio(data: int, frames: int) -> int:
            if self.sound is not None:
                self.sound += ctypes.string_at(data, frames * 4)
            return frames

        core = self.core
        self.sound: bytearray | None = None  # stereo s16 at 44.1 kHz, once set
        self.callbacks = [
            ENV_CB(environment), VIDEO_CB(video), AUDIO_CB(lambda l, r: None),
            AUDIO_BATCH_CB(audio), POLL_CB(lambda: None), INPUT_CB(input_state),
        ]  # fmt: skip
        core.retro_set_environment(self.callbacks[0])
        core.retro_init()
        core.retro_set_video_refresh(self.callbacks[1])
        core.retro_set_audio_sample(self.callbacks[2])
        core.retro_set_audio_sample_batch(self.callbacks[3])
        core.retro_set_input_poll(self.callbacks[4])
        core.retro_set_input_state(self.callbacks[5])
        core.retro_load_game.argtypes = [ctypes.POINTER(GameInfo)]
        if not core.retro_load_game(ctypes.byref(GameInfo(str(CUE).encode(), None, 0, None))):
            raise SystemExit("emu_compare: the core didn't load the disc")
        core.retro_set_controller_port_device(0, 1)
        core.retro_get_memory_data.restype = ctypes.c_void_p
        self.ram_address = core.retro_get_memory_data(RETRO_MEMORY_SYSTEM_RAM)

    def run(self) -> None:
        """Runs one frame: up to the next VBlank."""
        self.frame += 1
        self.core.retro_run()

    def ram(self) -> bytes:
        return ctypes.string_at(self.ram_address, RAM_SIZE)

    def write(self, address: int, data: bytes) -> None:
        ctypes.memmove(self.ram_address + address - RAM_BASE, data, len(data))

    def card(self) -> bytes:
        size = self.core.retro_get_memory_size(RETRO_MEMORY_SAVE_RAM)
        return ctypes.string_at(self.core.retro_get_memory_data(RETRO_MEMORY_SAVE_RAM), size)

    def load_card(self, data: bytes) -> None:
        ctypes.memmove(self.core.retro_get_memory_data(RETRO_MEMORY_SAVE_RAM), data, len(data))

    def screenshot(self, path: pathlib.Path) -> None:
        if self.video:
            write_bmp(path, *to_rgb(self.format, *self.video))

    def close(self) -> None:
        self.core.retro_unload_game()
        self.core.retro_deinit()


def parse_poke(text: str | None, port: bool) -> tuple[int, list[tuple[int, int]]] | None:
    """FRAME:NAME=VALUE[,NAME=VALUE...], with each name's address on that side."""
    if not text:
        return None
    frame, _, rest = text.partition(":")
    words = []
    for item in rest.split(","):
        name, _, value = item.partition("=")
        words.append((symbol(name, port), int(value, 0)))
    return int(frame), words


def run_emu(args: argparse.Namespace) -> None:
    out = pathlib.Path(args.out)
    emu = Emulator(args.core, args.bios, args.pad, out)
    poke = parse_poke(args.poke, False)
    if args.card:
        emu.load_card(pathlib.Path(args.card).read_bytes())
    emu.sound = bytearray()
    while emu.frame < args.frames:
        emu.run()
        if poke and emu.frame == poke[0]:
            for address, value in poke[1]:
                emu.write(address, struct.pack("<I", value))
        if emu.frame % args.every or emu.frame < args.start:
            continue
        (out / f"{emu.frame:06d}.ram").write_bytes(emu.ram())
        emu.screenshot(out / f"{emu.frame:06d}.bmp")
    (out / "card1.mcd").write_bytes(emu.card())  # the port's name for it
    with wave.open(str(out / "audio.wav"), "wb") as w:
        w.setnchannels(2)
        w.setsampwidth(2)
        w.setframerate(44100)
        w.writeframes(emu.sound)
    emu.close()


def to_rgb(fmt: int, data: bytes, width: int, height: int, pitch: int) -> tuple[int, int, bytes]:
    rgb = bytearray(width * height * 3)
    for y in range(height):
        for x in range(width):
            if fmt == PIXEL_XRGB8888:
                (p,) = struct.unpack_from("<I", data, y * pitch + x * 4)
                r, g, b = p >> 16 & 255, p >> 8 & 255, p & 255
            else:
                (p,) = struct.unpack_from("<H", data, y * pitch + x * 2)
                r, g, b = (p >> 11) << 3, (p >> 5 & 63) << 2, (p & 31) << 3
            rgb[(y * width + x) * 3 : (y * width + x) * 3 + 3] = bytes((r, g, b))
    return width, height, bytes(rgb)


def run_port(args: argparse.Namespace) -> None:
    out = pathlib.Path(args.out)
    out.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, NASCAR98_HEADLESS="1", NASCAR98_SCALE="1", NASCAR98_FRAMES=str(args.frames))
    env.update(NASCAR98_PAD=str(pathlib.Path(args.pad).resolve()), NASCAR98_DUMP=f"{args.every}:{out.resolve()}")
    env["NASCAR98_DUMP_START"] = str(args.start)
    if poke := parse_poke(args.poke, True):
        env["NASCAR98_POKE"] = f"{poke[0]}:" + ",".join(f"{a:#x}={v:#x}" for a, v in poke[1])
    env["NASCAR98_WAV"] = str((out / "audio.wav").resolve())
    env["NASCAR98_SAVES"] = str((out / "saves").resolve())
    (out / "saves").mkdir(exist_ok=True)
    if args.card:
        shutil.copyfile(args.card, out / "saves/card1.mcd")
    subprocess.run([str(ROOT / "build/port/nascar98")], env=env, cwd=ROOT, check=False)


def symbol(name: str, port: bool) -> int:
    if port:
        text = (ROOT / "build/port/nascar98.map").read_text()
        m = re.search(rf"^([0-9a-f]{{8}})\s+\S+\s+\S+\s+{re.escape(name)}$", text, re.M)
        if not m and re.fullmatch(r"D_[0-9A-F]{8}", name):
            return int(name[2:], 16)  # heap: the port keeps the console's layout
    elif re.fullmatch(r"D_[0-9A-F]{8}", name):
        return int(name[2:], 16)
    else:
        text = (ROOT / "config/symbol_addrs.txt").read_text()
        m = re.search(rf"^{re.escape(name)} = 0x([0-9A-Fa-f]{{8}});", text, re.M)
    if not m:
        raise SystemExit(f"emu_compare: no address for {name}")
    return int(m.group(1), 16)


@dataclasses.dataclass
class CarState:
    address: int
    x: int
    y: int
    z: int
    speed: int
    heading: int
    steering: int
    rpm: int
    gear: int
    lap: int
    segment: int
    place: int
    mode: int
    type: int
    time: int


# Car fields (include/car.h): offset, struct format.
CAR_FIELDS = {
    "x": (0x000, "i"), "y": (0x004, "i"), "z": (0x008, "i"), "speed": (0x090, "i"),
    "heading": (0x114, "h"), "steering": (0x20E, "h"), "rpm": (0x108, "h"),
    "gear": (0x10C, "h"), "lap": (0x1D6, "h"), "segment": (0x1E0, "h"),
    "place": (0x204, "b"), "mode": (0x200, "b"), "type": (0x1EC, "h"), "time": (0x25C, "i"),
}  # fmt: skip
CAR_NEXT = 0x3E0
CLOCK = "D_800A2EC0"
CAR_SIZE = 0x500


def word(ram: bytes, address: int) -> int:
    return struct.unpack_from("<I", ram, address - RAM_BASE)[0]


def in_ram(address: int) -> bool:
    return RAM_BASE <= address < RAM_BASE + RAM_SIZE - CAR_SIZE


def read_car(ram: bytes, address: int) -> CarState:
    values = {k: struct.unpack_from("<" + f, ram, address - RAM_BASE + o)[0] for k, (o, f) in CAR_FIELDS.items()}
    return CarState(address, **values)


def cars(ram: bytes, port: bool) -> list[CarState]:
    return walk_cars(ram, symbol("gPlayerCar", port))


def walk_cars(ram: bytes, player_pointer: int) -> list[CarState]:
    """The player car, then the cars its `next` chain reaches."""
    address = word(ram, player_pointer)
    found: list[CarState] = []
    seen = set()
    while in_ram(address) and address not in seen and len(found) < 64:
        seen.add(address)
        found.append(read_car(ram, address))
        address = word(ram, address + CAR_NEXT)
    return found


Sample = tuple[int, int, list[CarState]]  # VBlank frame, game clock, cars


def load_run(directory: pathlib.Path, port: bool) -> list[Sample]:
    """The dumps that hold a race: the menus have one or two cars."""
    run = []
    for path in sorted(directory.glob("*.ram")):
        ram = path.read_bytes()
        found = cars(ram, port)
        if len(found) > 2:
            run.append((int(path.stem), word(ram, symbol(CLOCK, port)), found))
    return run


def describe(c: CarState) -> str:
    return (
        f"pos=({c.x},{c.y},{c.z}) speed={c.speed / 65536:.1f} heading={c.heading} steer={c.steering} "
        f"rpm={c.rpm} gear={c.gear} lap={c.lap} seg={c.segment} place={c.place} mode={c.mode}"
    )


def describe_ai(found: list[CarState]) -> str:
    ai = found[1:]
    speeds = sorted(c.speed / 65536 for c in ai)
    gears = sorted({c.gear for c in ai})
    return (
        f"{len(ai)} AI: speed {speeds[0]:.1f} to {speeds[-1]:.1f} (median {speeds[len(speeds) // 2]:.1f}), "
        f"{len({c.speed for c in ai})} distinct, gears {gears}, leader seg {max(c.lap * 1000 + c.segment for c in ai)}"
    )


def report(args: argparse.Namespace) -> None:
    port_dir, emu_dir = pathlib.Path(args.port_dir), pathlib.Path(args.emu_dir)
    port_run, emu_run = load_run(port_dir, True), load_run(emu_dir, False)
    print(f"port: {len(port_run)} race dumps, emulator: {len(emu_run)}")
    if not port_run or not emu_run:
        print("emu_compare: one run never reached a race; check its screenshots")
        return
    for name, run in (("port", port_run), ("emulator", emu_run)):
        (f0, k0, c0), (f1, k1, _) = run[0], run[-1]
        print(f"{name}: race from frame {f0} to {f1}, {len(c0)} cars, "
              f"{(k1 - k0) / max(f1 - f0, 1) * 60:.1f} game frames a second")  # fmt: skip
    # The game scales its physics by the VBlanks each frame took, so line
    # the runs up on VBlanks since each race's first dump.
    port_base, emu_base = port_run[0][0], emu_run[0][0]
    rows = []
    for frame, _, port_cars in port_run:
        t = frame - port_base
        emu_frame, _, emu_cars = min(emu_run, key=lambda s: abs(s[0] - emu_base - t))
        if abs(emu_frame - emu_base - t) <= 30:
            rows.append((t, frame, port_cars, emu_frame, emu_cars))
    print("\nVBlanks into the race, port frame / emulator frame")
    for t, frame, port_cars, emu_frame, emu_cars in rows[:: max(len(rows) // 16, 1)]:
        print(f"{t:6d}  {frame}/{emu_frame}:")
        print(f"   port player {describe(port_cars[0])}")
        print(f"   emu  player {describe(emu_cars[0])}")
        print(f"   port {describe_ai(port_cars)}")
        print(f"   emu  {describe_ai(emu_cars)}")
    if args.html:
        write_html(pathlib.Path(args.html), port_dir, emu_dir, rows)


def write_html(path: pathlib.Path, port_dir: pathlib.Path, emu_dir: pathlib.Path, rows) -> None:
    parts = [
        "<!doctype html><meta charset=utf-8><title>Port and emulator</title>",
        "<style>body{font:13px system-ui;background:#111;color:#ddd}img{width:320px;image-rendering:pixelated}"
        "td{vertical-align:top;padding:4px}pre{margin:0;white-space:pre-wrap;width:320px}</style><table>",
        "<tr><th>VBlanks</th><th>Port</th><th>Emulator</th></tr>",
    ]
    for clock, frame, port_cars, emu_frame, emu_cars in rows:
        cells = []
        for directory, f, c in ((port_dir, frame, port_cars), (emu_dir, emu_frame, emu_cars)):
            img = os.path.relpath(directory / f"{f:06d}.bmp", path.parent)
            text = "\n".join(f"{i}: {describe(car)}" for i, car in enumerate(c[:4]))
            cells.append(f"<td><img src='{html.escape(img)}'><pre>frame {f}\n{html.escape(text)}</pre></td>")
        parts.append(f"<tr><td>{clock}</td>{''.join(cells)}</tr>")
    path.write_text("\n".join(parts) + "</table>")
    print(f"wrote {path}")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    for name in ("emu", "port"):
        p = sub.add_parser(name)
        p.add_argument("--pad", required=True)
        p.add_argument("--frames", type=int, required=True)
        p.add_argument("--every", type=int, default=30)
        p.add_argument("--start", type=int, default=0, help="first frame to dump")
        p.add_argument("--poke", help="FRAME:NAME=VALUE[,NAME=VALUE...] writes words after that frame")
        p.add_argument("--card", help="a 128 KB card image to start with in slot 1 (out/card1.mcd has the last)")
        p.add_argument("out")
        if name == "emu":
            p.add_argument("--core", required=True)
            p.add_argument("--bios", required=True)
    p = sub.add_parser("report")
    p.add_argument("port_dir")
    p.add_argument("emu_dir")
    p.add_argument("--html")
    args = parser.parse_args()
    {"emu": run_emu, "port": run_port, "report": report}[args.command](args)


if __name__ == "__main__":
    sys.exit(main())
