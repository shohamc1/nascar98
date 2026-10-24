"""Tests for tools/cue.py and the track checks in tools/extract.py."""

import pathlib
import tempfile
import unittest

import cue
import extract

SHEET = """FILE "Game (Track 1).bin" BINARY
  TRACK 01 MODE2/2352
    INDEX 01 00:00:00
FILE "Game (Track 2).bin" BINARY
  TRACK 02 AUDIO
    INDEX 00 00:00:00
    INDEX 01 00:02:00
"""


class CueTest(unittest.TestCase):
    def setUp(self) -> None:
        self.dir = tempfile.TemporaryDirectory()
        self.path = pathlib.Path(self.dir.name) / "Game.cue"
        self.path.write_text(SHEET)

    def tearDown(self) -> None:
        self.dir.cleanup()

    def test_parse_audio_track(self) -> None:
        track = cue.parse_cue(self.path)[1]
        self.assertEqual(track.number, 2)
        self.assertEqual(track.mode, "AUDIO")
        self.assertEqual(track.path, self.path.parent / "Game (Track 2).bin")
        self.assertEqual(track.index00, 0)
        self.assertEqual(track.index01, 150)

    def test_data_track_has_no_index00(self) -> None:
        track = cue.parse_cue(self.path)[0]
        self.assertEqual(track.mode, "MODE2/2352")
        self.assertIsNone(track.index00)
        self.assertEqual(track.index01, 0)

    def test_write_then_parse_is_identity(self) -> None:
        tracks = cue.parse_cue(self.path)
        text = cue.write_cue(tracks)
        self.assertEqual(text, SHEET)
        self.path.write_text(text)
        self.assertEqual(cue.parse_cue(self.path), tracks)

    def test_missing_track_file_is_reported(self) -> None:
        tracks = cue.parse_cue(self.path)
        with self.assertRaises(SystemExit) as caught:
            extract.verify_tracks(tracks, {})
        self.assertIn("Game (Track 1).bin", str(caught.exception.code))

    def test_hash_mismatch_is_reported(self) -> None:
        tracks = cue.parse_cue(self.path)
        for track in tracks:
            track.path.write_bytes(b"x")
        hashes = {t.path.name: "0" * 40 for t in tracks}
        with self.assertRaises(SystemExit) as caught:
            extract.verify_tracks(tracks, hashes)
        self.assertIn("SHA-1", str(caught.exception.code))


if __name__ == "__main__":
    unittest.main()
