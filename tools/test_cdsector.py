"""Tests for tools/cdsector.py. The real-sector test skips without the disc."""

import pathlib
import random
import unittest

import cdsector

ROOT = pathlib.Path(__file__).resolve().parent.parent
TRACK1 = ROOT / "NASCAR 98 (USA)" / "NASCAR 98 (USA) (Track 1).bin"


class CdsectorTest(unittest.TestCase):
    def test_msf(self) -> None:
        self.assertEqual(cdsector.msf(0), b"\x00\x02\x00")
        self.assertEqual(cdsector.msf(316), b"\x00\x06\x16")

    def test_encode_form1_layout(self) -> None:
        sector = cdsector.encode_form1(316, bytes(8), bytes(2048))
        self.assertEqual(len(sector), 2352)
        self.assertEqual(sector[:12], b"\x00" + b"\xff" * 10 + b"\x00")
        self.assertEqual(sector[12:16], b"\x00\x06\x16\x02")

    def test_encode_form1_rejects_wrong_sizes(self) -> None:
        with self.assertRaises(ValueError):
            cdsector.encode_form1(0, bytes(8), bytes(2047))

    @unittest.skipUnless(TRACK1.is_file(), "needs the disc image")
    def test_real_sectors_re_encode(self) -> None:
        count = TRACK1.stat().st_size // cdsector.SECTOR
        rng = random.Random(5)
        checked = 0
        with TRACK1.open("rb") as f:
            for lba in sorted(rng.sample(range(count), 2000)):
                f.seek(lba * cdsector.SECTOR)
                sector = f.read(cdsector.SECTOR)
                if sector[18] & 0x20:
                    continue  # Form 2
                with self.subTest(lba=lba):
                    self.assertEqual(cdsector.encode_form1(lba, sector[16:24], sector[24:2072]), sector)
                checked += 1
        self.assertGreater(checked, 1900)


if __name__ == "__main__":
    unittest.main()
