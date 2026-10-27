"""Tests for the native runner, build/port/nascar98 (make -f port/port.mk nascar98).

Each test skips when the runner or the disc is missing.
"""

import os
import pathlib
import subprocess
import tempfile
import unittest

ROOT = pathlib.Path(__file__).resolve().parent.parent
RUNNER = ROOT / "build/port/nascar98"
TRACK1 = ROOT / "NASCAR 98 (USA)/NASCAR 98 (USA) (Track 1).bin"


def run(timeout: float, **env: str) -> subprocess.CompletedProcess:
    return subprocess.run(
        [str(RUNNER)], cwd=ROOT, env={**os.environ, **env}, capture_output=True, text=True, timeout=timeout
    )


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
        result = run(60, NASCAR98_FRAMES="600")
        self.assertEqual(result.returncode, 0, result.stderr[-2000:])
        self.assertIn("DrawOTag", result.stderr)
        self.assertIn("nascar98: stopped after 600 frames", result.stderr)

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
