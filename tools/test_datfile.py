"""Tests for tools/datfile.py. The real-disc test skips without disc/."""

import csv
import hashlib
import pathlib
import random
import unittest

import datfile

ROOT = pathlib.Path(__file__).resolve().parent.parent
DISC = ROOT / "disc"


def payloads() -> list[bytes]:
    rng = random.Random(4)
    return [rng.randbytes(n) for n in (1, 2048, 2049, 5000)]


class DatfileTest(unittest.TestCase):
    def test_pack_aligns_entries_and_pads_tail(self) -> None:
        parts = payloads()
        dat, entries = datfile.pack_dat(parts)
        self.assertEqual(len(dat) % 2048, 0)
        self.assertEqual([e.checksum for e in entries], [datfile.checksum(p) for p in parts])
        end = 0
        for part, entry in zip(parts, entries):
            at = entry.sector * 2048
            self.assertEqual(dat[end:at].count(0), at - end)
            self.assertEqual(dat[at : at + entry.size], part)
            end = at + entry.size
        self.assertEqual(dat[end:].count(0), len(dat) - end)

    def test_growing_an_entry_shifts_later_sectors(self) -> None:
        parts = payloads()
        _, before = datfile.pack_dat(parts)
        parts[1] += bytes(2048)
        _, after = datfile.pack_dat(parts)
        self.assertEqual([e.sector for e in after[:2]], [e.sector for e in before[:2]])
        self.assertEqual([e.sector - 1 for e in after[2:]], [e.sector for e in before[2:]])

    def test_checksum_is_word_sum(self) -> None:
        self.assertEqual(datfile.checksum(b"\x01\0\0\0\x02\0\0\0"), 3)
        self.assertEqual(datfile.checksum(b"\xff\xff\xff\xff\x02\0\0\0"), 1)  # wraps at 32 bits
        self.assertEqual(datfile.checksum(b"\x05"), 5)  # zero padding counts as zero

    def test_edit_changes_checksum(self) -> None:
        parts = payloads()
        _, before = datfile.pack_dat(parts)
        parts[2] = b"\x01" + parts[2][1:]
        _, after = datfile.pack_dat(parts)
        self.assertNotEqual(after[2].checksum, before[2].checksum)
        self.assertEqual(after[:2] + after[3:], before[:2] + before[3:])

    def exe(self) -> bytes:
        return random.Random(9).randbytes(datfile.TABLE_FILE_OFFSET + datfile.TABLE_SIZE + 64)

    def entries(self) -> list[datfile.DatEntry]:
        return [datfile.DatEntry(i * 3, i * 5000 + 1, i * 0x01010101) for i in range(datfile.TABLE_COUNT)]

    def test_patch_exe_table_changes_only_table_bytes(self) -> None:
        exe = self.exe()
        patched = datfile.patch_exe_table(exe, self.entries())
        self.assertEqual(len(patched), len(exe))
        changed = [i for i, (a, b) in enumerate(zip(exe, patched)) if a != b]
        self.assertTrue(changed)
        self.assertGreaterEqual(min(changed), datfile.TABLE_FILE_OFFSET)
        self.assertLess(max(changed), datfile.TABLE_FILE_OFFSET + datfile.TABLE_SIZE)

    def test_table_round_trip(self) -> None:
        entries = self.entries()
        self.assertEqual(datfile.read_table(datfile.patch_exe_table(self.exe(), entries)), entries)

    def test_wrong_entry_count_is_rejected(self) -> None:
        with self.assertRaises(ValueError):
            datfile.build_table(self.entries()[:-1])

    @unittest.skipUnless((DISC / "dat" / "index.tsv").is_file(), "needs disc/ (make extract)")
    def test_real_pack_matches_disc(self) -> None:
        with (DISC / "dat" / "index.tsv").open() as f:
            rows = list(csv.DictReader(f, delimiter="\t"))
        parts = [(DISC / "dat" / row["file"]).read_bytes() for row in rows]
        dat, entries = datfile.pack_dat(parts)
        original = (DISC / "NASCAR.DAT").read_bytes()
        self.assertEqual(hashlib.sha1(dat).hexdigest(), hashlib.sha1(original).hexdigest())
        exe = (DISC / "SLUS_005.21").read_bytes()
        self.assertEqual(datfile.read_table(exe), entries)
        self.assertEqual(datfile.patch_exe_table(exe, datfile.read_table(exe)), exe)


if __name__ == "__main__":
    unittest.main()
