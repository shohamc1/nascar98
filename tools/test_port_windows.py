"""Tests for the Windows cross-build (make -f port/port.mk nascar98 HOST=windows).

Skips without Docker or without the translated module (make -f port/port.mk nascar98).
"""

import pathlib
import shutil
import subprocess
import unittest

ROOT = pathlib.Path(__file__).resolve().parent.parent
MODULE_C = ROOT / "build/port/nascar98_wasm.c"
EXE = ROOT / "build/port/windows/nascar98.exe"


def docker_running() -> bool:
    return bool(shutil.which("docker")) and subprocess.run(["docker", "info"], capture_output=True).returncode == 0


@unittest.skipUnless(MODULE_C.exists(), "no module: make -f port/port.mk nascar98")
@unittest.skipUnless(docker_running(), "no Docker")
class Windows(unittest.TestCase):
    def test_cross_build(self) -> None:
        build = subprocess.run(
            ["make", "-f", "port/port.mk", "nascar98", "HOST=windows"],
            cwd=ROOT,
            capture_output=True,
            text=True,
            timeout=1800,
        )
        self.assertEqual(build.returncode, 0, build.stderr[-3000:])
        head = EXE.read_bytes()[:0x200]
        self.assertEqual(head[:2], b"MZ")
        pe = int.from_bytes(head[0x3C:0x40], "little")
        self.assertEqual(head[pe : pe + 4], b"PE\0\0")
        self.assertEqual(int.from_bytes(head[pe + 4 : pe + 6], "little"), 0x8664)  # x86-64
        self.assertTrue((EXE.parent / "SDL3.dll").exists())


if __name__ == "__main__":
    unittest.main()
