"""Convert PlayStation TIM images to PNG files and back, losslessly.

A TIM holds an optional CLUT block and an image block, each a VRAM
rectangle measured in 16-bit words. The PNG holds the pixels at their real
width: 4 and 8 bits per pixel give an indexed PNG whose palette is the
first 16 or 256 CLUT entries, 16 bits per pixel gives RGBA, and 24 bits per
pixel gives RGB. A JSON-able sidecar keeps what PNG can't: the VRAM
rectangles, the palette, the rest of the CLUT, any bytes after the image,
and block lengths that disagree with the rectangle.

An indexed TIM also accepts a truecolour PNG, as editors often save one,
provided every pixel uses a colour from the original palette. Edits made
in the PNG's own palette need it saved as an indexed PNG.

Alpha carries the semi-transparency (STP) bit of each 15-bit colour word:

  word 0x0000          alpha 0    (transparent)
  STP clear, non-zero  alpha 255
  STP set, non-zero    alpha 128
  word 0x8000          alpha 255, black (opaque black)

On the way back, alpha below 64 gives 0x0000, 64 to 191 sets STP, and 192
or more is opaque.

A 16-bit TIM with no STP bit set anywhere, such as a full-screen
background, gives an opaque RGB PNG instead, with 0x0000 as black: the
game copies these straight to the screen, where 0x0000 shows as black.
The sidecar marks it "opaque", and black converts back to 0x0000.
"""

import dataclasses
import io
import struct

from PIL import Image

MAGIC = 0x10
BPP = {0: 4, 1: 8, 2: 16, 3: 24}
PIXELS_PER_WORD = {4: 4, 8: 2, 16: 1}


class SizeMismatch(ValueError):
    """The PNG's size differs from the TIM it replaces."""


@dataclasses.dataclass
class Clut:
    x: int
    y: int
    w: int
    h: int
    data: bytes
    bnum: int | None = None  # block length, when it disagrees with w and h


@dataclasses.dataclass
class Tim:
    bpp: int
    clut: Clut | None
    x: int
    y: int
    w: int
    h: int
    pixels: bytes
    trailing: bytes
    bnum: int | None = None  # block length, when it disagrees with w and h


def read_block(data: bytes, at: int) -> tuple[tuple[int, int, int, int], bytes, int | None, int]:
    """Return ((x, y, w, h), words, odd block length or None, next offset)."""
    if at + 12 > len(data):
        raise ValueError("TIM ends inside a block header")
    bnum, x, y, w, h = struct.unpack_from("<I4H", data, at)
    end = at + 12 + w * h * 2
    if end > len(data):
        raise ValueError(f"TIM block of {w}x{h} words runs past the end of the data")
    return (x, y, w, h), data[at + 12 : end], None if bnum == 12 + w * h * 2 else bnum, end


def write_block(rect: tuple[int, int, int, int], words: bytes, bnum: int | None) -> bytes:
    return struct.pack("<I4H", 12 + len(words) if bnum is None else bnum, *rect) + words


def parse_tim(data: bytes) -> Tim:
    magic, flag = struct.unpack_from("<II", data)
    if magic != MAGIC or flag & ~0xF or flag & 7 not in BPP:
        raise ValueError(f"not a TIM (magic {magic:#x}, flag {flag:#x})")
    clut = None
    at = 8
    if flag & 8:
        rect, words, bnum, at = read_block(data, at)
        clut = Clut(*rect, words, bnum)
    rect, words, bnum, at = read_block(data, at)
    return Tim(BPP[flag & 7], clut, *rect, words, data[at:], bnum)


def serialise_tim(tim: Tim) -> bytes:
    pmode = {v: k for k, v in BPP.items()}[tim.bpp]
    out = struct.pack("<II", MAGIC, pmode | (8 if tim.clut else 0))
    if tim.clut:
        c = tim.clut
        out += write_block((c.x, c.y, c.w, c.h), c.data, c.bnum)
    out += write_block((tim.x, tim.y, tim.w, tim.h), tim.pixels, tim.bnum)
    return out + tim.trailing


def word_to_rgba(word: int) -> tuple[int, int, int, int]:
    if word == 0:
        return 0, 0, 0, 0
    r, g, b = (word >> shift & 31 for shift in (0, 5, 10))
    alpha = 128 if word & 0x8000 and word != 0x8000 else 255
    return r << 3 | r >> 2, g << 3 | g >> 2, b << 3 | b >> 2, alpha


def rgba_to_word(r: int, g: int, b: int, a: int) -> int:
    if a < 64:
        return 0
    word = r >> 3 | (g >> 3) << 5 | (b >> 3) << 10
    if a < 192:
        return word | 0x8000
    return word or 0x8000


def opaque_word(r: int, g: int, b: int, a: int) -> int:
    """Return the colour word for a pixel of an opaque image: black is 0x0000."""
    return rgba_to_word(r, g, b, a) & 0x7FFF


RGBA = [bytes(word_to_rgba(w)) for w in range(0x10000)]


def pixel_width(bpp: int, w: int) -> int:
    if bpp == 24:
        if w * 2 % 3:
            raise ValueError(f"24-bit TIM row of {w} words isn't a whole number of pixels")
        return w * 2 // 3
    return w * PIXELS_PER_WORD[bpp]


def palette_size(tim: Tim) -> int:
    """Return how many CLUT entries the PNG palette carries."""
    if tim.bpp > 8 or tim.clut is None:
        return 0
    return min(1 << tim.bpp, len(tim.clut.data) // 2)


def tim_to_png(tim: Tim) -> tuple[bytes, dict]:
    """Return PNG bytes and the sidecar that png_to_tim needs to rebuild tim."""
    width = pixel_width(tim.bpp, tim.w)
    size = (width, tim.h)
    save = {}
    opaque = tim.bpp == 16 and not any(high & 0x80 for high in tim.pixels[1::2])
    if tim.bpp == 24:
        image = Image.frombytes("RGB", size, tim.pixels)
    elif tim.bpp == 16:
        words = struct.unpack(f"<{len(tim.pixels) // 2}H", tim.pixels)
        image = Image.frombytes("RGBA", size, b"".join(RGBA[w] for w in words))
        if opaque:
            image = image.convert("RGB")
    else:
        if tim.bpp == 4:
            indexes = bytes(i for byte in tim.pixels for i in (byte & 15, byte >> 4))
        else:
            indexes = tim.pixels
        image = Image.frombytes("P", size, indexes)
        count = palette_size(tim)
        words = struct.unpack(f"<{count}H", tim.clut.data[: count * 2]) if count else ()
        colours = [word_to_rgba(w) for w in words]
        image.putpalette(b"".join(bytes(c[:3]) for c in colours), "RGB")
        save["transparency"] = bytes(c[3] for c in colours)
        if tim.bpp == 4:
            save["bits"] = 4
    out = io.BytesIO()
    image.save(out, "PNG", **save)

    sidecar = {
        "bpp": tim.bpp,
        "x": tim.x,
        "y": tim.y,
        "w": tim.w,
        "h": tim.h,
        "trailing": tim.trailing.hex(),
        "bnum": tim.bnum,
        "clut": None,
        "opaque": opaque,
    }
    if tim.clut:
        c = tim.clut
        sidecar["clut"] = {
            "x": c.x,
            "y": c.y,
            "w": c.w,
            "h": c.h,
            "palette": c.data[: palette_size(tim) * 2].hex(),
            "rest": c.data[palette_size(tim) * 2 :].hex(),
            "bnum": c.bnum,
        }
    return out.getvalue(), sidecar


def read_rgba(image: Image.Image) -> bytes:
    """Return image's pixels as 8-bit RGBA, whatever the PNG's colour type."""
    if image.mode in ("I", "I;16", "I;16B"):
        image = image.point(lambda v: v / 257).convert("L")
    return image.convert("RGBA").tobytes()


def read_indexed(image: Image.Image, c: dict) -> tuple[bytes, bytes]:
    """Return an indexed PNG's pixels and its palette as CLUT words."""
    count = c["w"] * c["h"] - len(bytes.fromhex(c["rest"])) // 2
    indexes = image.tobytes()
    if any(i >= count for i in indexes):
        raise ValueError(f"PNG uses a palette index past the {count} colours this TIM has")
    rgb = image.getpalette("RGB") or []
    rgb += [0] * (count * 3 - len(rgb))
    alpha = image.info.get("transparency", b"")
    if isinstance(alpha, int):
        alpha = bytes(255 if i != alpha else 0 for i in range(count))
    alpha += b"\xff" * (count - len(alpha))
    words = (rgba_to_word(*rgb[i * 3 : i * 3 + 3], alpha[i]) for i in range(count))
    return indexes, struct.pack(f"<{count}H", *words)


def map_to_palette(image: Image.Image, c: dict, width: int) -> tuple[bytes, bytes]:
    """Return a truecolour PNG's pixels as indexes into the sidecar's palette.

    A palette that lists a colour twice maps it to the first entry.
    """
    palette = bytes.fromhex(c["palette"])
    words = struct.unpack(f"<{len(palette) // 2}H", palette)
    index = {}
    for i, word in enumerate(words):
        index.setdefault(word, i)
    rgba = read_rgba(image)
    indexes = bytearray()
    for i in range(0, len(rgba), 4):
        word = rgba_to_word(*rgba[i : i + 4])
        if word not in index:
            at = (i // 4 % width, i // 4 // width)
            raise ValueError(
                f"pixel {at} is RGBA {tuple(rgba[i : i + 4])}, which isn't in this "
                "TIM's palette; save the PNG as Indexed to change the palette"
            )
        indexes.append(index[word])
    return bytes(indexes), palette


def png_to_tim(png: bytes, sidecar: dict) -> Tim:
    """Return the TIM that sidecar describes, with its pixels taken from png."""
    image = Image.open(io.BytesIO(png))
    bpp, w, h = sidecar["bpp"], sidecar["w"], sidecar["h"]
    width = pixel_width(bpp, w)
    if image.size != (width, h):
        raise SizeMismatch(
            f"PNG is {image.size[0]}x{image.size[1]} pixels; this TIM needs {width}x{h}"
        )
    c = sidecar["clut"]
    clut = None
    if c:
        clut = Clut(c["x"], c["y"], c["w"], c["h"], b"", c["bnum"])
    tim = Tim(bpp, clut, sidecar["x"], sidecar["y"], w, h, b"", bytes.fromhex(sidecar["trailing"]), sidecar["bnum"])

    if bpp == 24:
        tim.pixels = image.convert("RGB").tobytes()
    elif bpp == 16:
        rgba = read_rgba(image)
        to_word = opaque_word if sidecar.get("opaque") else rgba_to_word
        tim.pixels = struct.pack(
            f"<{width * h}H", *(to_word(*rgba[i : i + 4]) for i in range(0, len(rgba), 4))
        )
    else:
        if image.mode == "P":
            indexes, palette = read_indexed(image, c)
        else:
            indexes, palette = map_to_palette(image, c, width)
        clut.data = palette + bytes.fromhex(c["rest"])
        if bpp == 4:
            indexes = bytes(indexes[i] | indexes[i + 1] << 4 for i in range(0, len(indexes), 2))
        tim.pixels = indexes
    return tim


def split_bundle(data: bytes) -> tuple[list[bytes], dict]:
    """Split a bundle (a count, count + 1 offsets, then the files) into its files."""
    count = struct.unpack_from("<I", data)[0]
    header = 4 + 4 * (count + 1)
    if header > len(data):
        raise ValueError(f"bundle of {count} files is shorter than its header")
    offsets = struct.unpack_from(f"<{count + 1}I", data, 4)
    if offsets[0] < header or list(offsets) != sorted(offsets) or offsets[-1] > len(data):
        raise ValueError("bundle offsets aren't in order inside the data")
    parts = [data[offsets[i] : offsets[i + 1]] for i in range(count)]
    meta = {"gap": data[header : offsets[0]].hex(), "trailing": data[offsets[-1] :].hex()}
    return parts, meta


def join_bundle(parts: list[bytes], meta: dict) -> bytes:
    gap = bytes.fromhex(meta["gap"])
    at = 4 + 4 * (len(parts) + 1) + len(gap)
    offsets = [at]
    for part in parts:
        at += len(part)
        offsets.append(at)
    header = struct.pack(f"<{len(parts) + 2}I", len(parts), *offsets)
    return header + gap + b"".join(parts) + bytes.fromhex(meta["trailing"])
