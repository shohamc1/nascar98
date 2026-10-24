"""Tests for tools/assets.py. Most need the disc and disc/, and skip without them."""

import io
import pathlib
import shutil
import struct
import tempfile
import unittest

from PIL import Image

import assets
import cdda
import datfile
import extract
import iso9660

ROOT = pathlib.Path(__file__).resolve().parent.parent
CUE = ROOT / "NASCAR 98 (USA)" / "NASCAR 98 (USA).cue"
DISC = ROOT / "disc"


class NamesTest(unittest.TestCase):
    def read(self, text: str) -> dict[str, str]:
        with tempfile.TemporaryDirectory() as tmp:
            path = pathlib.Path(tmp) / "names.txt"
            path.write_text(text)
            return assets.read_names(path)

    def test_names_file_is_parsed(self) -> None:
        names = self.read("# comment\n\ndat/005 = title_screen  # inline\naudio/02 = race_one\n")
        self.assertEqual(names, {"dat/005": "title_screen", "audio/02": "race_one"})

    def test_missing_names_file_is_empty(self) -> None:
        self.assertEqual(assets.read_names(pathlib.Path("/nonexistent/names.txt")), {})

    def test_bad_lines_are_rejected(self) -> None:
        for text in ("dat/5 = x\n", "dat/005 = has space\n", "dat/005\n", "dat/005 = a\ndat/005 = b\n"):
            with self.subTest(text=text), self.assertRaises(SystemExit):
                self.read(text)


class MissingDiscTest(unittest.TestCase):
    def test_missing_disc_directory_message(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            with self.assertRaises(SystemExit) as caught:
                assets.convert(CUE, pathlib.Path(tmp) / "disc", pathlib.Path(tmp) / "assets")
        self.assertIn("make extract", str(caught.exception.code))


@unittest.skipUnless(CUE.is_file() and DISC.is_dir(), "needs the disc image and disc/ (make extract)")
class AssetsTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.tmp = tempfile.TemporaryDirectory()
        cls.out = pathlib.Path(cls.tmp.name) / "assets"
        assets.convert(CUE, DISC, cls.out)
        cls.manifest = (cls.out / "manifest.json").read_bytes()

    @classmethod
    def tearDownClass(cls) -> None:
        cls.tmp.cleanup()

    def test_convert_is_idempotent(self) -> None:
        assets.convert(CUE, DISC, self.out, force=True)
        self.assertEqual((self.out / "manifest.json").read_bytes(), self.manifest)

    def test_convert_keeps_existing_assets_without_force(self) -> None:
        with self.assertRaises(SystemExit) as caught:
            assets.convert(CUE, DISC, self.out)
        self.assertIn("--force", str(caught.exception.code))

    def test_names_differing_only_in_case_are_rejected(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            with self.assertRaises(SystemExit):
                assets.convert(CUE, DISC, pathlib.Path(tmp), {"dat/005": "Same", "dat/040": "same"})

    def test_sound_bank_on_a_sector_boundary_is_padded(self) -> None:
        entry = assets.load_manifest(self.out)["dat"][4]
        path = self.out / entry["file"]
        saved = path.read_bytes()
        self.addCleanup(path.write_bytes, saved)
        path.write_bytes((saved + bytes(61440))[:61440])
        _, table = assets.build_dat(self.out)
        self.assertEqual(table[4].size, 61444)

    def test_build_moves_audio_starts_in_the_exe(self) -> None:
        wav = self.out / assets.load_manifest(self.out)["audio"][0]
        saved = wav.read_bytes()
        self.addCleanup(wav.write_bytes, saved)
        wav.write_bytes(cdda.raw_to_wav(cdda.wav_to_raw(saved, 0) + bytes(75 * 2352), 0))
        with tempfile.TemporaryDirectory() as tmp:
            out = pathlib.Path(tmp)
            assets.build(CUE, DISC / "SLUS_005.21", self.out, out)
            track1 = out / "NASCAR 98 (USA) (Track 1).bin"
            volume = iso9660.parse_volume(track1)
            starts = sorted(r.lba for p, r, _ in volume.walk() if p.endswith(".DA"))
            disc = extract.Disc(track1)
            exe = next(disc.read(lba, size) for name, lba, size in disc.files() if name == "SLUS_005.21")
            disc.f.close()
        self.assertEqual(starts[1] - starts[0], 11887 + 75)
        for start in starts:
            self.assertEqual(exe.count(struct.pack("<II", 0x3C040000 | start >> 16, 0x34840000 | start & 0xFFFF)), 1)

    def test_unedited_dat_matches_disc(self) -> None:
        dat, _ = assets.build_dat(self.out)
        self.assertEqual(dat, (DISC / "NASCAR.DAT").read_bytes())

    def test_replaced_png_reaches_the_dat(self) -> None:
        original, before = assets.build_dat(self.out)
        entries = assets.load_manifest(self.out)["dat"]
        index = next(i for i, e in enumerate(entries) if e["kind"] == "tim")
        png = self.out / entries[index]["file"]
        saved = png.read_bytes()
        self.addCleanup(png.write_bytes, saved)
        image = Image.open(io.BytesIO(saved)).convert("RGBA")
        r, g, b, _ = image.getpixel((0, 0))
        image.putpixel((0, 0), (255 - r, 255 - g, 255 - b, 255))
        image.save(png)

        edited, after = assets.build_dat(self.out)
        # Same size, so only the edited entry's checksum changes.
        self.assertNotEqual(after[index].checksum, before[index].checksum)
        self.assertEqual(after[:index] + after[index + 1 :], before[:index] + before[index + 1 :])
        for i, entry in enumerate(after):
            span = slice(entry.sector * datfile.SECTOR, entry.sector * datfile.SECTOR + entry.size)
            if i == index:
                self.assertNotEqual(edited[span], original[span])
            else:
                self.assertEqual(edited[span], original[span], i)

    def test_custom_names_rename_files_and_build_follows(self) -> None:
        manifest = assets.load_manifest(self.out)
        raw = next(i for i, e in enumerate(manifest["dat"]) if e["kind"] == "raw")
        names = {"dat/005": "title_screen", f"dat/{raw:03d}": "some_data", "dat/000": "logos", "audio/02": "race_one"}
        with tempfile.TemporaryDirectory() as tmp:
            out = pathlib.Path(tmp)
            assets.convert(CUE, DISC, out, names)
            entries = assets.load_manifest(out)["dat"]
            self.assertEqual(entries[5]["file"], "dat/title_screen.png")
            self.assertEqual(entries[5]["sidecar"], "dat/title_screen.json")
            self.assertEqual(entries[raw]["file"], "dat/some_data" + pathlib.Path(manifest["dat"][raw]["file"]).suffix)
            self.assertEqual(entries[0]["parts"][1]["file"], "dat/logos-1.png")
            self.assertEqual(assets.load_manifest(out)["audio"][0], "audio/race_one.wav")
            self.assertTrue((out / "dat" / "title_screen.png").is_file())
            dat, _ = assets.build_dat(out)
        self.assertEqual(dat, (DISC / "NASCAR.DAT").read_bytes())

    def test_duplicate_file_names_are_rejected(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            with self.assertRaises(SystemExit) as caught:
                assets.convert(CUE, DISC, pathlib.Path(tmp), {"dat/005": "same", "dat/040": "same"})
        self.assertIn("same.png", str(caught.exception.code))

    def test_missing_asset_is_an_error(self) -> None:
        entry = next(e for e in assets.load_manifest(self.out)["dat"] if e["kind"] == "raw")
        path = self.out / entry["file"]
        moved = path.with_name(path.name + ".moved")
        shutil.move(path, moved)
        self.addCleanup(shutil.move, moved, path)
        with self.assertRaises(SystemExit) as caught:
            assets.build_dat(self.out)
        self.assertIn(entry["file"], str(caught.exception.code))


if __name__ == "__main__":
    unittest.main()
