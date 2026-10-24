"""Tests for tools/iso9660.py. They read the real data track and skip without it."""

import pathlib
import struct
import unittest

import extract
import iso9660

ROOT = pathlib.Path(__file__).resolve().parent.parent
TRACK1 = ROOT / "NASCAR 98 (USA)" / "NASCAR 98 (USA) (Track 1).bin"


@unittest.skipUnless(TRACK1.is_file(), "needs the disc image")
class Iso9660Test(unittest.TestCase):
    def test_classify_covers_every_sector(self) -> None:
        extents = iso9660.classify(TRACK1)
        at = 0
        for extent in extents:
            self.assertEqual(extent.lba, at)
            at += extent.count
        self.assertEqual(at, 103859)
        files = [e.name for e in extents if e.kind == "file"]
        self.assertEqual(files, ["SYSTEM.CNF", "SLUS_005.21", "NASCAR.DAT"])

    def test_serialise_matches_original(self) -> None:
        disc = extract.Disc(TRACK1)
        out = iso9660.parse_volume(TRACK1).serialise()
        self.assertEqual(sorted(out), [16, 17, 18, 19, 20, 21, 22, 103708])
        for lba, data in out.items():
            with self.subTest(lba=lba):
                self.assertEqual(data, disc.sector(lba))
        disc.f.close()

    def test_relocate_changes_only_extents(self) -> None:
        volume = iso9660.parse_volume(TRACK1)
        before = volume.serialise()
        sizes = {path: (r.lba, r.size) for path, r, _ in volume.walk()}
        moved = volume.relocate(
            {"NASCAR.DAT": (316, sizes["NASCAR.DAT"][1] + 2048), "CDTRACKS": (103709, 2048)},
            volume_sectors=177897,
        )
        after = moved.serialise()
        self.assertEqual(volume.serialise(), before)  # the original is untouched
        self.assertEqual(sorted(after), [16, 17, 18, 19, 20, 21, 22, 103709])

        old_root, new_root = before[22], after[22]
        self.assertEqual(len(old_root), len(new_root))
        at = old_root.index(b"NASCAR.DAT;1") - 33
        self.assertEqual(new_root[at], old_root[at])  # record length
        self.assertEqual(new_root[at + 33 : at + 45], b"NASCAR.DAT;1")
        self.assertEqual(struct.unpack_from("<I", new_root, at + 10)[0], sizes["NASCAR.DAT"][1] + 2048)
        self.assertEqual(struct.unpack_from(">I", new_root, at + 14)[0], sizes["NASCAR.DAT"][1] + 2048)
        changed = [i for i, (a, b) in enumerate(zip(old_root, new_root)) if a != b]
        self.assertTrue(all(at + 2 <= i < at + 18 or self.in_cdtracks_extent(old_root, i) for i in changed))

        self.assertEqual(struct.unpack_from("<I", after[18], 10 + 2)[0], 103709)
        self.assertEqual(struct.unpack_from(">I", after[20], 10 + 2)[0], 103709)
        self.assertEqual(struct.unpack_from("<I", after[16], 80)[0], 177897)
        self.assertEqual(struct.unpack_from("<I", after[103709], 2)[0], 103709)  # "."
        self.assertEqual(after[103709][48:], before[103708][48:])  # ".." and the .DA records

    @staticmethod
    def in_cdtracks_extent(root: bytes, i: int) -> bool:
        at = root.index(b"CDTRACKS") - 33
        return at + 2 <= i < at + 10


if __name__ == "__main__":
    unittest.main()
