"""Pack NASCAR.DAT and generate the EXE's file table for it.

NASCAR.DAT has no header or directory. Each entry starts on a 2048-byte
sector and is followed by zero bytes up to the next sector. The EXE holds
the directory: 185 records of {sector, size, name hash} at 0x80098340,
which is file offset 0x86B40. The name hash function is unknown, so hashes
pass through as opaque values.
"""

import dataclasses
import struct

SECTOR = 2048
TABLE_FILE_OFFSET = 0x86B40
TABLE_COUNT = 185
RECORD = struct.Struct("<3I")
TABLE_SIZE = RECORD.size * TABLE_COUNT


@dataclasses.dataclass(frozen=True)
class DatEntry:
    sector: int
    size: int
    name_hash: int


def read_table(exe: bytes) -> list[DatEntry]:
    return [
        DatEntry(*RECORD.unpack_from(exe, TABLE_FILE_OFFSET + RECORD.size * i))
        for i in range(TABLE_COUNT)
    ]


def build_table(entries: list[DatEntry]) -> bytes:
    if len(entries) != TABLE_COUNT:
        raise ValueError(f"the EXE's file table holds {TABLE_COUNT} entries, not {len(entries)}")
    return b"".join(RECORD.pack(e.sector, e.size, e.name_hash) for e in entries)


def patch_exe_table(exe: bytes, entries: list[DatEntry]) -> bytes:
    """Return exe with its file table replaced by entries."""
    end = TABLE_FILE_OFFSET + TABLE_SIZE
    if len(exe) < end:
        raise ValueError(f"EXE is {len(exe)} bytes, too short to hold the file table")
    return exe[:TABLE_FILE_OFFSET] + build_table(entries) + exe[end:]


def pack_dat(payloads: list[bytes], hashes: list[int]) -> tuple[bytes, list[DatEntry]]:
    """Return NASCAR.DAT holding payloads in order, and the table that finds them."""
    if len(payloads) != len(hashes):
        raise ValueError(f"{len(payloads)} payloads but {len(hashes)} name hashes")
    out = bytearray()
    entries = []
    for payload, name_hash in zip(payloads, hashes):
        entries.append(DatEntry(len(out) // SECTOR, len(payload), name_hash))
        out += payload + bytes(-len(payload) % SECTOR)
    return bytes(out), entries
