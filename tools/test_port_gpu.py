"""Tests for the host GPU (port/host/gpu.c), built with SDL3 and a C driver.

The driver's main returns the number of the first failed check.
"""

import os
import pathlib
import shutil
import struct
import subprocess
import tempfile
import unittest

ROOT = pathlib.Path(__file__).resolve().parent.parent
CC = os.environ.get("HOST_CC") or shutil.which("cc")


def sdl_flags() -> list[str] | None:
    pc = shutil.which("pkg-config")
    if not pc:
        return None
    run = subprocess.run([pc, "--cflags", "--libs", "sdl3"], capture_output=True, text=True)
    return run.stdout.split() if run.returncode == 0 else None


SDL = sdl_flags()

PRELUDE = """
#include <stdint.h>
#include <string.h>
#include "gpu.h"
#include "textures.h"

/* A fake module memory: wasm address A is mem[A - BASE]. */
#define BASE 0x80100000u
static uint8_t mem[0x10000];
static uint32_t *W(uint32_t a) { return (uint32_t *)(mem + (a - BASE)); }
static void Rect(uint32_t a, int16_t x, int16_t y, int16_t w, int16_t h) {
    int16_t *r = (int16_t *)(mem + (a - BASE));
    r[0] = x; r[1] = y; r[2] = w; r[3] = h;
}
"""


def run_driver(body: str) -> subprocess.CompletedProcess:
    with tempfile.TemporaryDirectory() as tmp:
        main = pathlib.Path(tmp) / "driver.c"
        main.write_text(PRELUDE + "int main(void) {\n" + body + "    return 0;\n}\n")
        exe = pathlib.Path(tmp) / "driver"
        build = subprocess.run(
            [CC, "-O1", f"-I{ROOT / 'port/host'}", str(ROOT / "port/host/gpu.c"), str(ROOT / "port/host/textures.c"),
             str(main), "-o", str(exe), *SDL],
            capture_output=True,
            text=True,
        )
        if build.returncode:
            raise AssertionError(build.stderr)
        return subprocess.run([str(exe)], capture_output=True, text=True, timeout=60)


@unittest.skipUnless(CC and SDL, "no host compiler or SDL3")
class Gpu(unittest.TestCase):
    def check(self, body: str) -> None:
        run = run_driver(body)
        self.assertEqual(run.returncode, 0, f"check {run.returncode} failed\n{run.stderr}")

    def test_texture_hash(self) -> None:
        # 64-bit FNV-1a of x, y, w, h (little-endian u16s), then the pixels.
        data = struct.pack("<4H2H", 1, 2, 2, 1, 0x1234, 0xABCD)
        h = 0xCBF29CE484222325
        for b in data:
            h = (h ^ b) * 0x100000001B3 & (1 << 64) - 1
        self.check(
            "    static const uint16_t px[2] = {0x1234, 0xABCD};\n"
            f"    if (TextureHash(1, 2, 2, 1, (const uint8_t *)px) != 0x{h:016X}ull) return 1;\n"
        )

    def test_command_words(self) -> None:
        self.check(
            "    if (GpuCommandWords(0x20000000u) != 4) return 1;\n"   # F3
            "    if (GpuCommandWords(0x28000000u) != 5) return 2;\n"   # F4
            "    if (GpuCommandWords(0x24000000u) != 7) return 3;\n"   # FT3
            "    if (GpuCommandWords(0x2C000000u) != 9) return 4;\n"   # FT4
            "    if (GpuCommandWords(0x30000000u) != 6) return 5;\n"   # G3
            "    if (GpuCommandWords(0x38000000u) != 8) return 6;\n"   # G4
            "    if (GpuCommandWords(0x34000000u) != 9) return 7;\n"   # GT3
            "    if (GpuCommandWords(0x3C000000u) != 12) return 8;\n"  # GT4
            "    if (GpuCommandWords(0x40000000u) != 3) return 9;\n"   # line F2
            "    if (GpuCommandWords(0x50000000u) != 4) return 10;\n"  # line G2
            "    if (GpuCommandWords(0x48000000u) != 0) return 11;\n"  # polyline
            "    if (GpuCommandWords(0x60000000u) != 3) return 12;\n"  # tile
            "    if (GpuCommandWords(0x64000000u) != 4) return 13;\n"  # sprite
            "    if (GpuCommandWords(0x68000000u) != 2) return 14;\n"  # 1x1 tile
            "    if (GpuCommandWords(0x7C000000u) != 3) return 15;\n"  # 16x16 sprite
            "    if (GpuCommandWords(0x02000000u) != 3) return 16;\n"  # fill
            "    if (GpuCommandWords(0xE1000000u) != 1) return 17;\n"
        )

    def test_texel_decode(self) -> None:
        self.check(
            "    uint16_t *v;\n"
            "    if (GpuInit(1, 1)) return 1;\n"
            "    v = GpuVram();\n"
            "    v[500 * 1024 + 16 + 1] = 0x001F;          /* CLUT entry 1: red */\n"
            "    v[500 * 1024 + 16 + 2] = 0x8000 | 0x7C00; /* entry 2: blue, STP */\n"
            "    v[0 * 1024 + 640] = 0x0021;               /* u0 = 1, u1 = 2, u2 = 0 */\n"
            "    if (GpuTexel(640, 0, 0, 16, 500, 0, 0) != 0xFFF80000u) return 2;\n"
            "    if (GpuTexel(640, 0, 0, 16, 500, 1, 0) != 0x800000F8u) return 3;\n"
            "    if (GpuTexel(640, 0, 0, 16, 500, 2, 0) != 0) return 4;\n"
            "    v[1 * 1024 + 700] = 0x03E0;               /* 15-bit green */\n"
            "    if (GpuTexel(700, 0, 2, 0, 0, 0, 1) != 0xFF00F800u) return 5;\n"
            "    v[2 * 1024 + 704] = 0x0201;               /* 8-bit: u0 = 1, u1 = 2 */\n"
            "    if (GpuTexel(704, 0, 1, 16, 500, 1, 2) != 0x800000F8u) return 6;\n"
        )

    def test_texture_cache_invalidates(self) -> None:
        # A textured sprite caches its page; an upload over the page drops it.
        self.check(
            "    uint32_t *p;\n"
            "    if (GpuInit(1, 1)) return 1;\n"
            "    GpuSetMemory(mem - BASE, (uint64_t)BASE + sizeof(mem));\n"
            "    p = W(BASE + 0x100);\n"
            "    p[0] = 0x05FFFFFFu;               /* tag: 5 words, end */\n"
            "    p[1] = 0xE1000000u | 10;          /* page (640, 0), 4-bit */\n"
            "    p[2] = 0x64808080u;               /* textured sprite */\n"
            "    p[3] = (20 << 16) | 10;\n"
            "    p[4] = (unsigned)(500 << 6 | 1) << 16; /* CLUT (16, 500), uv 0 */\n"
            "    p[5] = (8 << 16) | 8;\n"
            "    GpuDrawPrim(BASE + 0x100);\n"
            "    if (GpuCachedTextures() != 1) return 2;\n"
            "    Rect(BASE + 0x200, 640, 0, 4, 4);\n"
            "    GpuLoadImage(BASE + 0x200, BASE + 0x300);\n"
            "    if (GpuCachedTextures() != 0) return 3;\n"
            "    GpuDrawPrim(BASE + 0x100);\n"
            "    Rect(BASE + 0x200, 16, 500, 16, 1);\n"
            "    GpuLoadImage(BASE + 0x200, BASE + 0x300); /* the CLUT row */\n"
            "    if (GpuCachedTextures() != 0) return 4;\n"
        )

    def test_draw_reaches_target(self) -> None:
        # A flat red tile and an upload both show in the display area.
        self.check(
            "    uint32_t *p;\n"
            "    uint16_t *src;\n"
            "    int i;\n"
            "    if (GpuInit(1, 1)) return 1;\n"
            "    GpuSetMemory(mem - BASE, (uint64_t)BASE + sizeof(mem));\n"
            "    Rect(BASE + 0x40, 0, 0, 320, 240);\n"
            "    *(uint8_t *)(mem + 0x50) = 0; /* isinter, isrgb24 off */\n"
            "    GpuSetDispEnv(BASE + 0x40);\n"
            "    p = W(BASE + 0x100);\n"
            "    p[0] = 0x05FFFFFFu;\n"
            "    p[1] = 0xE3000000u;                       /* area (0, 0) */\n"
            "    p[2] = 0xE4000000u | (239 << 10) | 319;   /* to (319, 239) */\n"
            "    p[3] = 0x600000FFu;                       /* red tile */\n"
            "    p[4] = (10 << 16) | 10;\n"
            "    p[5] = (20 << 16) | 20;\n"
            "    GpuDrawPrim(BASE + 0x100);\n"
            "    src = (uint16_t *)(mem + 0x400);\n"
            "    for (i = 0; i < 64; i++) src[i] = 0x7C00; /* blue */\n"
            "    Rect(BASE + 0x200, 100, 100, 8, 8);\n"
            "    GpuLoadImage(BASE + 0x200, BASE + 0x400);\n"
            "    if ((GpuTargetPixel(15, 15) & 0xFFFFFF) != 0xFF0000u) return 2;\n"
            "    if ((GpuTargetPixel(104, 104) & 0xFFFFFF) != 0x0000FFu) return 3;\n"
            "    if ((GpuTargetPixel(50, 50) & 0xFFFFFF) != 0) return 4;\n"
        )


    def test_oversized_polygon_skipped(self) -> None:
        # The GPU skips a polygon more than 1023 wide or 511 tall: games
        # rely on it for vertices projected from behind the camera.
        self.check(
            "    uint32_t *p;\n"
            "    if (GpuInit(1, 1)) return 1;\n"
            "    GpuSetMemory(mem - BASE, (uint64_t)BASE + sizeof(mem));\n"
            "    p = W(BASE + 0x100);\n"
            "    p[0] = 0x06FFFFFFu;\n"
            "    p[1] = 0xE3000000u;\n"
            "    p[2] = 0xE4000000u | (239 << 10) | 319;\n"
            "    p[3] = 0x20FFFFFFu;                          /* white F3 */\n"
            "    p[4] = (50u << 16) | 200;\n"
            "    p[5] = (60u << 16) | (uint16_t)(-1000 & 0x7FF);\n"
            "    p[6] = (70u << 16) | 200;\n"
            "    GpuDrawPrim(BASE + 0x100);\n"
            "    if ((GpuTargetPixel(150, 60) & 0xFFFFFF) != 0) return 2;\n"
            "    p[5] = (60u << 16) | 0;                     /* 200 wide: drawn */\n"
            "    GpuDrawPrim(BASE + 0x100);\n"
            "    if ((GpuTargetPixel(150, 60) & 0xFFFFFF) != 0xFFFFFFu) return 3;\n"
        )


if __name__ == "__main__":
    unittest.main()
