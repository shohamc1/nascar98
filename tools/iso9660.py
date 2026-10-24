"""Parse and rewrite the ISO 9660 metadata of a PlayStation data track.

parse_volume reads the primary volume descriptor, the path tables, and
the directory tree into fields; Volume.serialise writes them back as
2048-byte user data per LBA. relocate moves files and directories to new
extents, and the path tables, "." and ".." records, and volume size follow.
Directory records carry the 14-byte CD-ROM XA system-use field, kept as
is. The descriptor's text fields don't change, so they stay raw bytes.
"""

import dataclasses
import pathlib
import struct

import extract

BLOCK = 2048
SYSTEM_SECTORS = 16
PVD_LBA = 16


@dataclasses.dataclass(frozen=True)
class Extent:
    kind: str  # system, meta, file, or gap
    lba: int
    count: int
    name: str | None


@dataclasses.dataclass
class Record:
    """One directory record. A directory also holds its own records."""

    lba: int
    size: int
    date: bytes
    flags: int
    unit: int
    gap: int
    seq: int
    name: bytes
    system_use: bytes
    children: list["Record"] | None = None

    @property
    def is_dir(self) -> bool:
        return bool(self.flags & 2)

    def serialise(self, lba: int, size: int) -> bytes:
        name = self.name + bytes(1 - len(self.name) % 2)
        length = 33 + len(name) + len(self.system_use)
        return (
            struct.pack("<BB", length, 0)
            + both32(lba)
            + both32(size)
            + self.date
            + struct.pack("<BBB", self.flags, self.unit, self.gap)
            + both16(self.seq)
            + struct.pack("<B", len(self.name))
            + name
            + self.system_use
        )


def both16(n: int) -> bytes:
    return struct.pack("<H", n) + struct.pack(">H", n)


def both32(n: int) -> bytes:
    return struct.pack("<I", n) + struct.pack(">I", n)


def parse_record(data: bytes) -> Record:
    lba, size = struct.unpack_from("<I4xI", data, 2)
    flags, unit, gap = data[25:28]
    seq = struct.unpack_from("<H", data, 28)[0]
    name = data[33 : 33 + data[32]]
    system_use = data[33 + len(name) + (1 - len(name) % 2) : data[0]]
    return Record(lba, size, data[18:25], flags, unit, gap, seq, name, system_use)


def sectors(size: int) -> int:
    return (size + BLOCK - 1) // BLOCK


@dataclasses.dataclass
class Volume:
    pvd: bytes
    terminators: list[bytes]
    path_table_lbas: tuple[int, int, int, int]  # L, optional L, M, optional M
    path_table_size: int
    volume_sectors: int
    root: Record

    def walk(self, record: Record | None = None, prefix: str = ""):
        """Yield (path, record, parent) for the root and every named record."""
        if record is None:
            yield "", self.root, self.root
            record = self.root
        for child in record.children[2:]:
            name = child.name.decode("ascii").split(";")[0]
            yield f"{prefix}{name}", child, record
            if child.is_dir:
                yield from self.walk(child, f"{prefix}{name}/")

    def directories(self) -> list[tuple[Record, int]]:
        """Return (directory, parent number) in path table order, numbered from 1."""
        order = [(self.root, 1)]
        i = 0
        while i < len(order):
            parent, number = order[i][0], i + 1
            kids = sorted((c for c in parent.children[2:] if c.is_dir), key=lambda c: c.name)
            order.extend((kid, number) for kid in kids)
            i += 1
        return order

    def path_table(self, big: bool) -> bytes:
        out = b""
        for record, parent in self.directories():
            name = b"\0" if record is self.root else record.name
            lba = struct.pack(">I" if big else "<I", record.lba)
            number = struct.pack(">H" if big else "<H", parent)
            out += struct.pack("<BB", len(name), 0) + lba + number + name + bytes(len(name) % 2)
        return out

    def serialise_dir(self, record: Record, parent: Record) -> bytes:
        out = bytearray()
        for i, child in enumerate(record.children):
            target = (record, parent)[i] if i < 2 else child
            entry = child.serialise(target.lba, target.size)
            if len(out) // BLOCK != (len(out) + len(entry) - 1) // BLOCK:
                out += bytes(-len(out) % BLOCK)
            out += entry
        return bytes(out) + bytes(sectors(record.size) * BLOCK - len(out))

    def serialise(self) -> dict[int, bytes]:
        """Return the user data of every metadata sector, keyed by LBA."""
        pvd = bytearray(self.pvd)
        pvd[80:88] = both32(self.volume_sectors)
        pvd[132:140] = both32(self.path_table_size)
        struct.pack_into("<II", pvd, 140, *self.path_table_lbas[:2])
        struct.pack_into(">II", pvd, 148, *self.path_table_lbas[2:])
        pvd[156:190] = self.root.serialise(self.root.lba, self.root.size)
        out = {PVD_LBA: bytes(pvd)}
        for i, sector in enumerate(self.terminators):
            out[PVD_LBA + 1 + i] = sector
        tables = (self.path_table(False),) * 2 + (self.path_table(True),) * 2
        if len(tables[0]) != self.path_table_size:
            raise ValueError(f"path table is {len(tables[0])} bytes, the descriptor says {self.path_table_size}")
        for lba, table in zip(self.path_table_lbas, tables):
            if lba:
                padded = table + bytes(sectors(len(table)) * BLOCK - len(table))
                for i in range(sectors(len(table))):
                    out[lba + i] = padded[i * BLOCK : (i + 1) * BLOCK]
        for _, record, parent in self.walk():
            if record.is_dir:
                data = self.serialise_dir(record, parent)
                for i in range(sectors(record.size)):
                    out[record.lba + i] = data[i * BLOCK : (i + 1) * BLOCK]
        return out

    def relocate(self, files: dict[str, tuple[int, int]], volume_sectors: int | None = None) -> "Volume":
        """Return a copy with each named path at a new (lba, size)."""
        moved = Volume(
            self.pvd,
            self.terminators,
            self.path_table_lbas,
            self.path_table_size,
            self.volume_sectors if volume_sectors is None else volume_sectors,
            copy_tree(self.root),
        )
        found = set()
        for path, record, _ in moved.walk():
            if path in files:
                record.lba, record.size = files[path]
                found.add(path)
        if missing := set(files) - found:
            raise KeyError(f"no such paths on the volume: {sorted(missing)}")
        return moved


def copy_tree(record: Record) -> Record:
    children = None if record.children is None else [copy_tree(c) for c in record.children]
    return dataclasses.replace(record, children=children)


def read_dir(disc: extract.Disc, record: Record) -> None:
    data = disc.read(record.lba, record.size)
    record.children = []
    i = 0
    while i < len(data):
        if data[i] == 0:  # records never cross a sector boundary
            i = (i // BLOCK + 1) * BLOCK
            continue
        child = parse_record(data[i : i + data[i]])
        i += data[i]
        record.children.append(child)
        if child.is_dir and child.name not in (b"\0", b"\1"):
            read_dir(disc, child)


def parse_volume(track1: pathlib.Path) -> Volume:
    disc = extract.Disc(track1)
    pvd = disc.sector(PVD_LBA)
    if pvd[:6] != b"\x01CD001":
        raise ValueError(f"{track1}: no primary volume descriptor at LBA {PVD_LBA}")
    terminators = []
    lba = PVD_LBA + 1
    while True:
        sector = disc.sector(lba)
        terminators.append(sector)
        if sector[0] == 255:
            break
        lba += 1
    root = parse_record(pvd[156:190])
    read_dir(disc, root)
    disc.f.close()
    return Volume(
        pvd,
        terminators,
        struct.unpack_from("<II", pvd, 140) + struct.unpack_from(">II", pvd, 148),
        struct.unpack_from("<I", pvd, 132)[0],
        struct.unpack_from("<I", pvd, 80)[0],
        root,
    )


def classify(track1: pathlib.Path) -> list[Extent]:
    """Return extents covering every sector of track1, in LBA order."""
    total = track1.stat().st_size // extract.SECTOR
    volume = parse_volume(track1)
    marked = [Extent("system", 0, SYSTEM_SECTORS, None)]
    marked += [Extent("meta", lba, 1, None) for lba in volume.serialise()]
    for path, record, _ in volume.walk():
        if not record.is_dir and record.lba < total:
            marked.append(Extent("file", record.lba, sectors(record.size), path))
    marked.sort(key=lambda e: e.lba)

    extents = []
    at = 0
    for extent in marked:
        if extent.lba < at:
            raise ValueError(f"{extent} overlaps the extent before it")
        if extent.lba > at:
            extents.append(Extent("gap", at, extent.lba - at, None))
        if extent.kind == "meta" and extents and extents[-1].kind == "meta" and extents[-1].lba + extents[-1].count == extent.lba:
            extents[-1] = Extent("meta", extents[-1].lba, extents[-1].count + 1, None)
        else:
            extents.append(extent)
        at = extent.lba + extent.count
    if at < total:
        extents.append(Extent("gap", at, total - at, None))
    return extents
