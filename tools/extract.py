#!/usr/bin/env python3
"""Copy the game files out of a NASCAR 98 (USA) disc image.

Usage: python3 tools/extract.py "NASCAR 98 (USA).cue" disc

Checks every track named by the cue sheet against config/disc.sha1, then
reads the data track (track 1, MODE2/2352) and writes:

  disc/SLUS_005.21, disc/SYSTEM.CNF, disc/NASCAR.DAT  the ISO 9660 files
  disc/dat/NNN.<ext>                                   NASCAR.DAT's entries

NASCAR.DAT has no directory of its own. The EXE holds its file table: 185
records of {sector, size, checksum} at 0x80098340 (see datfile.py).
Everything written here is copyrighted. disc/ is gitignored: keep it so.
"""

import hashlib
import pathlib
import struct
import sys

import cue
import datfile

SECTOR = 2352
USER_DATA = 24  # sync (12) + header (4) + XA subheader (8)


def sha1(path: pathlib.Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        for block in iter(lambda: f.read(1 << 20), b""):
            h.update(block)
    return h.hexdigest()


def read_hashes(path: pathlib.Path) -> dict[str, str]:
    """Return {file name: SHA-1} from a file of `shasum` lines."""
    hashes = {}
    for line in path.read_text().splitlines():
        if line.strip():
            digest, name = line.split(None, 1)
            hashes[name.lstrip("*")] = digest
    return hashes


def verify_tracks(tracks: list[cue.Track], hashes: dict[str, str]) -> None:
    """Exit with a message unless every track file exists and hashes as listed."""
    for track in tracks:
        print(f"checking {track.path.name}")
        if not track.path.is_file():
            sys.exit(f"{track.path}: missing (the cue sheet names it)")
        if track.path.name not in hashes:
            sys.exit(f"{track.path.name}: no SHA-1 in config/disc.sha1")
        if sha1(track.path) != hashes[track.path.name]:
            sys.exit(f"{track.path}: SHA-1 differs from config/disc.sha1 (wrong dump or region)")


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
    sheet, out = pathlib.Path(sys.argv[1]), pathlib.Path(sys.argv[2])
    if not sheet.is_file():
        sys.exit(f"{sheet}: no such cue sheet")
    tracks = cue.parse_cue(sheet)
    if not tracks or tracks[0].mode != "MODE2/2352":
        sys.exit(f"{sheet}: track 1 must be MODE2/2352")
    verify_tracks(tracks, read_hashes(pathlib.Path("config/disc.sha1")))

    disc = Disc(tracks[0].path)
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
        index.write("index\tsector\tsize\tchecksum\tfile\n")
        for i, entry in enumerate(datfile.read_table(exe)):
            data = dat[entry.sector * 2048 : entry.sector * 2048 + entry.size]
            path = out / "dat" / f"{i:03d}.{guess_ext(data)}"
            path.write_bytes(data)
            index.write(f"{i}\t{entry.sector}\t{entry.size}\t{entry.checksum:08x}\t{path.name}\n")
    print(f"wrote {datfile.TABLE_COUNT} NASCAR.DAT entries to {out / 'dat'}")


if __name__ == "__main__":
    main()
