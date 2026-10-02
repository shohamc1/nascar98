#!/usr/bin/env python3
"""Copy the game files out of a NASCAR 98 (USA) disc image.

Usage: python3 tools/extract.py "NASCAR 98 (USA).cue" disc

Reads the data track named by the cue sheet (MODE2/2352), checks it against
config/disc.sha1, and writes:

  disc/SLUS_005.21, disc/SYSTEM.CNF, disc/NASCAR.DAT  the ISO 9660 files
  disc/dat/NNN.<ext>                                   NASCAR.DAT's entries

NASCAR.DAT has no directory of its own. The EXE holds its file table: 185
records of {sector, size, name hash} at 0x80098340 (see dat_table()).
Everything written here is copyrighted. disc/ is gitignored: keep it so.
"""

import hashlib
import pathlib
import re
import struct
import sys

SECTOR = 2352
USER_DATA = 24  # sync (12) + header (4) + XA subheader (8)
FILE_TABLE_VRAM = 0x80098340
FILE_TABLE_COUNT = 185
EXE_VRAM = 0x80012000
EXE_HEADER = 0x800


def read_cue(cue: pathlib.Path) -> pathlib.Path:
    """Return the path of the cue sheet's first (data) track."""
    match = re.search(r'FILE "([^"]+)" BINARY\s+TRACK 01 MODE2/2352', cue.read_text())
    if not match:
        sys.exit(f"{cue}: track 1 must be MODE2/2352")
    return cue.parent / match.group(1)


def sha1(path: pathlib.Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        for block in iter(lambda: f.read(1 << 20), b""):
            h.update(block)
    return h.hexdigest()


class Disc:
    def __init__(self, path: pathlib.Path):
        self.f = path.open("rb")

    def sector(self, lba: int) -> bytes:
        self.f.seek(lba * SECTOR + USER_DATA)
        return self.f.read(2048)

    def read(self, lba: int, size: int) -> bytes:
        data = b"".join(self.sector(lba + i) for i in range((size + 2047) // 2048))
        return data[:size]

    def files(self):
        """Yield (path, lba, size) for every file in the ISO 9660 tree."""
        pvd = self.sector(16)
        if pvd[1:6] != b"CD001":
            sys.exit("track 1 has no ISO 9660 volume descriptor")
        root = pvd[156:190]
        yield from self._walk(*struct.unpack_from("<I4xI", root, 2), "")

    def _walk(self, lba: int, size: int, prefix: str):
        data = self.read(lba, size)
        i = 0
        while i < len(data):
            length = data[i]
            if length == 0:  # records never cross a sector boundary
                i = (i // 2048 + 1) * 2048
                continue
            rec = data[i : i + length]
            i += length
            elba, esize = struct.unpack_from("<I4xI", rec, 2)
            name = rec[33 : 33 + rec[32]]
            if name in (b"\0", b"\1"):
                continue
            name = name.decode("ascii").split(";")[0]
            if rec[25] & 2:
                yield from self._walk(elba, esize, f"{prefix}{name}/")
            else:
                yield f"{prefix}{name}", elba, esize


def dat_table(exe: bytes):
    """Yield (sector, size, name_hash) for each NASCAR.DAT entry."""
    base = FILE_TABLE_VRAM - EXE_VRAM + EXE_HEADER
    for i in range(FILE_TABLE_COUNT):
        yield struct.unpack_from("<3I", exe, base + 12 * i)


def guess_ext(data: bytes) -> str:
    magic = data[:4]
    if magic == b"\x10\0\0\0":
        return "tim"
    if magic == b"VLC0":
        return "vlc"
    if magic == b"pBAV":
        return "vab"
    return "bin"


def main() -> None:
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    cue, out = pathlib.Path(sys.argv[1]), pathlib.Path(sys.argv[2])
    track = read_cue(cue)
    expected = pathlib.Path("config/disc.sha1").read_text().split()[0]
    print(f"checking {track.name}")
    if sha1(track) != expected:
        sys.exit(f"{track}: SHA-1 differs from config/disc.sha1 (wrong dump or region)")

    disc = Disc(track)
    out.mkdir(parents=True, exist_ok=True)
    for name, lba, size in disc.files():
        if name.startswith("CDTRACKS/"):
            continue  # pointers into the CD audio tracks
        (out / name).write_bytes(disc.read(lba, size))
        print(f"wrote {out / name}")

    exe = (out / "SLUS_005.21").read_bytes()
    dat = (out / "NASCAR.DAT").read_bytes()
    (out / "dat").mkdir(exist_ok=True)
    with (out / "dat" / "index.tsv").open("w") as index:
        index.write("index\tsector\tsize\thash\tfile\n")
        for i, (lba, size, name_hash) in enumerate(dat_table(exe)):
            data = dat[lba * 2048 : lba * 2048 + size]
            path = out / "dat" / f"{i:03d}.{guess_ext(data)}"
            path.write_bytes(data)
            index.write(f"{i}\t{lba}\t{size}\t{name_hash:08x}\t{path.name}\n")
    print(f"wrote {FILE_TABLE_COUNT} NASCAR.DAT entries to {out / 'dat'}")


if __name__ == "__main__":
    main()
