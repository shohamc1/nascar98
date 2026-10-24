"""Tests for tools/tim.py. The real-disc test skips without disc/dat/."""

import io
import pathlib
import random
import struct
import unittest
import zlib

from PIL import Image

import tim

ROOT = pathlib.Path(__file__).resolve().parent.parent
DAT = ROOT / "disc" / "dat"


def make_tim(pmode: int, w: int, h: int, clut: tuple[int, int] | None, seed: int = 0, trailing: bytes = b"") -> bytes:
    """Return a synthetic TIM with random pixels; clut is (width, rows)."""
    rng = random.Random(seed)
    out = struct.pack("<II", 0x10, pmode | (8 if clut else 0))
    if clut:
        cw, ch = clut
        out += struct.pack("<I4H", 12 + cw * ch * 2, 0, 480, cw, ch) + rng.randbytes(cw * ch * 2)
    out += struct.pack("<I4H", 12 + w * h * 2, 320, 0, w, h) + rng.randbytes(w * h * 2)
    return out + trailing


def round_trip(data: bytes) -> bytes:
    return tim.serialise_tim(tim.png_to_tim(*tim.tim_to_png(tim.parse_tim(data))))


def png_chunk(kind: bytes, body: bytes) -> bytes:
    return struct.pack(">I", len(body)) + kind + body + struct.pack(">I", zlib.crc32(kind + body))


def raw_png(width: int, height: int, color_type: int, depth: int, scanlines: bytes, interlace: int = 0) -> bytes:
    """Return a PNG built by hand, for variants Pillow can't write."""
    header = struct.pack(">IIBBBBB", width, height, depth, color_type, 0, 0, interlace)
    return (
        b"\x89PNG\r\n\x1a\n"
        + png_chunk(b"IHDR", header)
        + png_chunk(b"IDAT", zlib.compress(scanlines))
        + png_chunk(b"IEND", b"")
    )


class TimTest(unittest.TestCase):
    def test_round_trip_4bpp(self) -> None:
        data = make_tim(0, 4, 3, (16, 1))
        self.assertEqual(round_trip(data), data)

    def test_round_trip_8bpp_two_clut_rows(self) -> None:
        data = make_tim(1, 4, 3, (256, 2))
        self.assertEqual(round_trip(data), data)

    def test_round_trip_16bpp_all_stp_states(self) -> None:
        data = bytearray(make_tim(2, 4, 1, None))
        struct.pack_into("<4H", data, 20, 0x0000, 0x8000, 0x7FFF, 0x801F)
        self.assertEqual(round_trip(bytes(data)), bytes(data))

    def test_16bpp_without_stp_is_opaque_rgb(self) -> None:
        data = bytearray(make_tim(2, 4, 1, None))
        struct.pack_into("<4H", data, 20, 0x0000, 0x001F, 0x7FFF, 0x0400)
        png, sidecar = tim.tim_to_png(tim.parse_tim(bytes(data)))
        image = Image.open(io.BytesIO(png))
        self.assertEqual(image.mode, "RGB")
        self.assertEqual(image.getpixel((0, 0)), (0, 0, 0))
        self.assertTrue(sidecar["opaque"])
        self.assertEqual(round_trip(bytes(data)), bytes(data))

    def test_16bpp_with_stp_keeps_alpha(self) -> None:
        data = bytearray(make_tim(2, 2, 1, None))
        struct.pack_into("<2H", data, 20, 0x0000, 0x801F)
        png, sidecar = tim.tim_to_png(tim.parse_tim(bytes(data)))
        self.assertEqual(Image.open(io.BytesIO(png)).mode, "RGBA")
        self.assertFalse(sidecar["opaque"])

    def test_round_trip_24bpp(self) -> None:
        data = make_tim(3, 3, 2, None)
        self.assertEqual(round_trip(data), data)

    def test_trailing_bytes_preserved(self) -> None:
        data = make_tim(2, 2, 2, None, trailing=b"\x01\x02\x03")
        self.assertEqual(round_trip(data), data)

    def test_odd_block_length_preserved(self) -> None:
        data = bytearray(make_tim(2, 2, 2, None))
        struct.pack_into("<I", data, 8, 7)
        self.assertEqual(round_trip(bytes(data)), bytes(data))

    def test_alpha_thresholds(self) -> None:
        cases = {0: 0x0000, 63: 0x0000, 64: 0x8000 | 0x1F, 191: 0x8000 | 0x1F, 192: 0x1F, 255: 0x1F}
        for alpha, word in cases.items():
            with self.subTest(alpha=alpha):
                self.assertEqual(tim.rgba_to_word(255, 0, 0, alpha), word)

    def test_resized_png_raises_size_mismatch(self) -> None:
        _, sidecar = tim.tim_to_png(tim.parse_tim(make_tim(2, 4, 3, None)))
        out = io.BytesIO()
        Image.new("RGBA", (5, 3)).save(out, "PNG")
        with self.assertRaises(tim.SizeMismatch) as caught:
            tim.png_to_tim(out.getvalue(), sidecar)
        self.assertIn("4x3", str(caught.exception))
        self.assertIn("5x3", str(caught.exception))

    def test_indexed_tim_accepts_truecolour_png_in_palette(self) -> None:
        data = make_tim(0, 4, 3, (16, 2))
        words = struct.unpack_from("<16H", data, 20)
        self.assertEqual(len(set(words)), 16)  # unique, so the mapping is exact
        png, sidecar = tim.tim_to_png(tim.parse_tim(data))
        out = io.BytesIO()
        Image.open(io.BytesIO(png)).convert("RGBA").save(out, "PNG")
        self.assertEqual(tim.serialise_tim(tim.png_to_tim(out.getvalue(), sidecar)), data)

    def test_truecolour_png_with_new_colour_is_named(self) -> None:
        png, sidecar = tim.tim_to_png(tim.parse_tim(make_tim(1, 2, 2, (256, 1))))
        image = Image.open(io.BytesIO(png)).convert("RGBA")
        image.putpixel((3, 1), (1, 2, 3, 255))
        out = io.BytesIO()
        image.save(out, "PNG")
        with self.assertRaises(ValueError) as caught:
            tim.png_to_tim(out.getvalue(), sidecar)
        message = str(caught.exception)
        self.assertIn("(3, 1)", message)
        self.assertIn("Indexed", message)

    def test_png_variants_accepted(self) -> None:
        _, sidecar = tim.tim_to_png(tim.parse_tim(make_tim(2, 4, 2, None)))
        for mode in ("RGB", "L", "LA"):
            with self.subTest(mode=mode):
                out = io.BytesIO()
                Image.new(mode, (4, 2), 200).save(out, "PNG")
                tim.png_to_tim(out.getvalue(), sidecar)
        with self.subTest(mode="16-bit RGBA"):
            row = b"\x00" + b"\xff\xff\x00\x00\x00\x00\xff\xff" * 4
            converted = tim.png_to_tim(raw_png(4, 2, 6, 16, row * 2), sidecar)
            self.assertEqual(converted.pixels[:2], b"\x1f\x00")
        with self.subTest(mode="interlaced"):
            _, small = tim.tim_to_png(tim.parse_tim(make_tim(2, 1, 1, None)))
            converted = tim.png_to_tim(raw_png(1, 1, 6, 8, b"\x00\xff\x00\x00\xff", interlace=1), small)
            self.assertEqual(converted.pixels, b"\x1f\x00")

    def test_bundle_round_trip(self) -> None:
        parts = [make_tim(2, 2, 2, None, seed=i) for i in range(4)]
        offsets, at = [], 4 + 4 * 5
        for part in parts:
            offsets.append(at)
            at += len(part)
        data = struct.pack("<6I", 4, *offsets, at) + b"".join(parts)
        split, meta = tim.split_bundle(data)
        self.assertEqual(split, parts)
        self.assertEqual(tim.join_bundle(split, meta), data)

    @unittest.skipUnless(DAT.is_dir(), "needs disc/dat (make extract)")
    def test_real_tims_round_trip(self) -> None:
        for path in sorted(DAT.glob("*.tim")):
            with self.subTest(file=path.name):
                data = path.read_bytes()
                self.assertEqual(round_trip(data), data)
                png, sidecar = tim.tim_to_png(tim.parse_tim(data))
                out = io.BytesIO()
                Image.open(io.BytesIO(png)).convert("RGBA").save(out, "PNG")
                self.assertEqual(tim.serialise_tim(tim.png_to_tim(out.getvalue(), sidecar)), data)
        bundle = next(DAT.glob("000.*")).read_bytes()
        parts, meta = tim.split_bundle(bundle)
        self.assertEqual(tim.join_bundle([round_trip(p) for p in parts], meta), bundle)


if __name__ == "__main__":
    unittest.main()
