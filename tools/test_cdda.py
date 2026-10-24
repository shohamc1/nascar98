"""Tests for tools/cdda.py. The real-track test skips without the disc."""

import hashlib
import io
import pathlib
import random
import unittest
import wave

import cdda
import cue
import extract

ROOT = pathlib.Path(__file__).resolve().parent.parent
CUE = ROOT / "NASCAR 98 (USA)" / "NASCAR 98 (USA).cue"


def make_wav(rate: int, channels: int, frames: int) -> bytes:
    out = io.BytesIO()
    with wave.open(out, "wb") as w:
        w.setnchannels(channels)
        w.setsampwidth(2)
        w.setframerate(rate)
        w.writeframes(bytes(frames * channels * 2))
    return out.getvalue()


class CddaTest(unittest.TestCase):
    def test_round_trip_synthetic(self) -> None:
        rng = random.Random(1)
        raw = bytes(150 * 2352) + rng.randbytes(3 * 2352)
        self.assertEqual(cdda.wav_to_raw(cdda.raw_to_wav(raw, 150), 150), raw)

    def test_nonzero_pregap_is_rejected(self) -> None:
        raw = bytearray(151 * 2352)
        raw[100] = 1
        with self.assertRaises(ValueError):
            cdda.raw_to_wav(bytes(raw), 150)

    def test_wav_longer_than_original_is_padded(self) -> None:
        raw = cdda.wav_to_raw(make_wav(44100, 2, 588 * 3 + 1), 150)
        self.assertEqual(len(raw) % 2352, 0)
        self.assertEqual(len(raw), (150 + 4) * 2352)

    def test_wrong_format_is_rejected(self) -> None:
        for wav in (make_wav(48000, 2, 10), make_wav(44100, 1, 10)):
            with self.assertRaises(ValueError) as caught:
                cdda.wav_to_raw(wav, 150)
            self.assertIn("44100", str(caught.exception))

    def test_raw_length_must_be_whole_sectors(self) -> None:
        with self.assertRaises(ValueError):
            cdda.raw_to_wav(bytes(150 * 2352 + 4), 150)

    @unittest.skipUnless(CUE.is_file(), "needs the disc image")
    def test_real_tracks_round_trip(self) -> None:
        hashes = extract.read_hashes(ROOT / "config" / "disc.sha1")
        for track in cue.parse_cue(CUE)[1:]:
            with self.subTest(track=track.number):
                raw = track.path.read_bytes()
                wav = cdda.raw_to_wav(raw, track.index01)
                back = cdda.wav_to_raw(wav, track.index01)
                self.assertEqual(hashlib.sha1(back).hexdigest(), hashes[track.path.name])


if __name__ == "__main__":
    unittest.main()
