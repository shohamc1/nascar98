"""Tests for the host controls (port/host/pad.c), built with SDL3 and a C driver.

The driver's main returns the number of the first failed check.
"""

import os
import pathlib
import shutil
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
#include <SDL3/SDL.h>
#include "pad.h"

/* The buttons PadMapKeys gives with only KEY held. */
static uint16_t Key(SDL_Scancode key) {
    static bool keys[SDL_SCANCODE_COUNT];
    uint16_t buttons;

    keys[key] = true;
    buttons = PadMapKeys(keys);
    keys[key] = false;
    return buttons;
}
"""


def run_driver(body: str) -> subprocess.CompletedProcess:
    with tempfile.TemporaryDirectory() as tmp:
        main = pathlib.Path(tmp) / "driver.c"
        main.write_text(PRELUDE + "int main(void) {\n" + body + "    return 0;\n}\n")
        exe = pathlib.Path(tmp) / "driver"
        build = subprocess.run(
            [CC, "-O1", f"-I{ROOT / 'port/host'}", str(ROOT / "port/host/pad.c"), str(main), "-o", str(exe), *SDL],
            capture_output=True,
            text=True,
        )
        if build.returncode:
            raise AssertionError(build.stderr)
        return subprocess.run([str(exe)], capture_output=True, text=True, timeout=60)


@unittest.skipUnless(CC and SDL, "needs a C compiler and SDL3")
class KeyboardTest(unittest.TestCase):
    def test_racing_keys(self) -> None:
        # The game's default layout: cross accelerates, square brakes,
        # R2 shifts up, R1 shifts down, L1 changes the camera.
        run = run_driver(
            """
    if (Key(SDL_SCANCODE_W) != PAD_CROSS) return 1;
    if (Key(SDL_SCANCODE_S) != PAD_SQUARE) return 2;
    if (Key(SDL_SCANCODE_A) != PAD_LEFT) return 3;
    if (Key(SDL_SCANCODE_D) != PAD_RIGHT) return 4;
    if (Key(SDL_SCANCODE_E) != PAD_R2) return 5;
    if (Key(SDL_SCANCODE_Q) != PAD_R1) return 6;
    if (Key(SDL_SCANCODE_C) != PAD_L1) return 7;
"""
        )
        self.assertEqual(run.returncode, 0, run.stdout + run.stderr)

    def test_menu_keys(self) -> None:
        # Cross confirms, triangle goes back, Start pauses.
        run = run_driver(
            """
    if (Key(SDL_SCANCODE_RETURN) != PAD_CROSS) return 1;
    if (Key(SDL_SCANCODE_BACKSPACE) != PAD_TRIANGLE) return 2;
    if (Key(SDL_SCANCODE_ESCAPE) != PAD_START) return 3;
    if (Key(SDL_SCANCODE_UP) != PAD_UP) return 4;
    if (Key(SDL_SCANCODE_DOWN) != PAD_DOWN) return 5;
"""
        )
        self.assertEqual(run.returncode, 0, run.stdout + run.stderr)


if __name__ == "__main__":
    unittest.main()
