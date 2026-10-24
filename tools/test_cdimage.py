"""Tests for tools/cdimage.py. They rebuild the real disc and skip without it.

Each build writes about 420 MB to a temporary directory and takes about
half a minute.
"""

import hashlib
import pathlib
import random
import struct
import tempfile
import unittest

import cdda
import cdimage
import cdsector
import cue
import extract
import iso9660

ROOT = pathlib.Path(__file__).resolve().parent.parent
CUE = ROOT / "NASCAR 98 (USA)" / "NASCAR 98 (USA).cue"
DISC = ROOT / "disc"
NAMES = ("SYSTEM.CNF", "SLUS_005.21", "NASCAR.DAT")


def da_extents(track1: pathlib.Path) -> dict[str, int]:
    volume = iso9660.parse_volume(track1)
    return {path: r.lba for path, r, _ in volume.walk() if path.endswith(".DA")}


def lui_ori(value: int) -> bytes:
    return struct.pack("<II", 0x3C040000 | value >> 16, 0x34840000 | value & 0xFFFF)


class PatchAudioStartsTest(unittest.TestCase):
    def test_patch_rewrites_each_constant(self) -> None:
        old, new = [104009, 115896], [104014, 115901]
        exe = b"\0" * 8 + lui_ori(old[0]) + b"\0" * 12 + lui_ori(old[1])
        patched = cdimage.patch_audio_starts(exe, old, new)
        self.assertEqual(patched, b"\0" * 8 + lui_ori(new[0]) + b"\0" * 12 + lui_ori(new[1]))

    def test_missing_or_repeated_constant_is_an_error(self) -> None:
        with self.assertRaises(ValueError):
            cdimage.patch_audio_starts(bytes(64), [104009], [104010])
        with self.assertRaises(ValueError):
            cdimage.patch_audio_starts(lui_ori(104009) * 2, [104009], [104010])


@unittest.skipUnless(CUE.is_file() and DISC.is_dir(), "needs the disc image and disc/ (make extract)")
class CdimageTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.tracks = cue.parse_cue(CUE)
        cls.frame = cdimage.capture_frame(cls.tracks[0].path)
        cls.volume = iso9660.parse_volume(cls.tracks[0].path)
        cls.files = {name: (DISC / name).read_bytes() for name in NAMES}
        cls.wavs = [cdda.raw_to_wav(t.path.read_bytes(), t.index01) for t in cls.tracks[1:]]
        cls.original_das = da_extents(cls.tracks[0].path)

    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.out = pathlib.Path(tmp.name)

    def build(self, files: dict[str, bytes], wavs: list[bytes]) -> None:
        cdimage.build_image(self.frame, self.volume, files, wavs, self.out)

    def track(self, n: int) -> pathlib.Path:
        return self.out / f"NASCAR 98 (USA) (Track {n}).bin"

    def test_unedited_image_matches_disc(self) -> None:
        hashes = extract.read_hashes(ROOT / "config" / "disc.sha1")
        self.build(self.files, self.wavs)
        for n in range(1, 8):
            with self.subTest(track=n):
                self.assertEqual(extract.sha1(self.track(n)), hashes[self.track(n).name])
        self.assertEqual((self.out / CUE.name).read_text(), CUE.read_text())

    def test_grown_dat_moves_later_things_together(self) -> None:
        files = dict(self.files)
        files["NASCAR.DAT"] += bytes(2048)
        self.build(files, self.wavs)
        track1 = self.track(1)
        self.assertEqual(track1.stat().st_size, self.tracks[0].path.stat().st_size + cdsector.SECTOR)
        disc = extract.Disc(track1)
        listed = {name: (lba, size) for name, lba, size in disc.files()}
        lba, size = listed["NASCAR.DAT"]
        self.assertEqual(size, len(files["NASCAR.DAT"]))
        self.assertEqual(hashlib.sha1(disc.read(lba, size)).digest(), hashlib.sha1(files["NASCAR.DAT"]).digest())
        disc.f.close()
        moved = da_extents(track1)
        for path, lba in self.original_das.items():
            self.assertEqual(moved[path], lba + 1, path)
        self.assert_sectors_encode(track1)

    def test_longer_wav_shifts_later_audio_tracks(self) -> None:
        wavs = list(self.wavs)
        wavs[0] = cdda.raw_to_wav(cdda.wav_to_raw(wavs[0], 0) + bytes(75 * cdsector.SECTOR), 0)
        self.build(self.files, wavs)
        moved = da_extents(self.track(1))
        order = sorted(self.original_das, key=self.original_das.get)
        self.assertEqual(moved[order[0]], self.original_das[order[0]])
        for path in order[1:]:
            self.assertEqual(moved[path], self.original_das[path] + 75, path)

    def assert_sectors_encode(self, track1: pathlib.Path) -> None:
        count = track1.stat().st_size // cdsector.SECTOR
        with track1.open("rb") as f:
            for lba in sorted(random.Random(7).sample(range(count), 2000)):
                f.seek(lba * cdsector.SECTOR)
                sector = f.read(cdsector.SECTOR)
                if sector[18] & 0x20:
                    continue  # Form 2, copied raw
                rebuilt = [cdsector.encode_form1(lba, sector[16:24], sector[24:2072], covered) for covered in (False, True)]
                self.assertIn(sector, rebuilt, lba)


if __name__ == "__main__":
    unittest.main()
