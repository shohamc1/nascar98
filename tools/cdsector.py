"""Encode CD-ROM XA Mode 2 Form 1 sectors, with their EDC and ECC.

A raw sector is 2352 bytes: a 12-byte sync pattern, a 4-byte header (BCD
minute, second, frame, then mode 2), an 8-byte subheader, 2048 bytes of
user data, a 4-byte EDC (error-detection code), and 276 bytes of ECC
(error-correction code: 172 bytes of P parity, then 104 of Q parity).

The EDC is a reflected CRC-32 with polynomial 0xD8018001 over the
subheader and user data. The ECC is Reed-Solomon parity over GF(2^8),
computed with the header treated as zero, as Mode 2 requires. The
column-parallel ECC below follows the layout in ECMA-130 annex A.
"""

import operator
import struct

SECTOR = 2352
SYNC = b"\x00" + b"\xff" * 10 + b"\x00"


def make_edc_table() -> list[int]:
    table = []
    for i in range(256):
        edc = i
        for _ in range(8):
            edc = edc >> 1 ^ (0xD8018001 if edc & 1 else 0)
        table.append(edc)
    return table


EDC_TABLE = make_edc_table()
# Multiplication by 2 in GF(2^8) with polynomial 0x11D, and its inverse
# applied to x ^ f(x), as translate() tables.
ECC_F = bytes((i << 1 ^ (0x11D if i & 0x80 else 0)) & 0xFF for i in range(256))
ECC_B = bytearray(256)
for i in range(256):
    ECC_B[i ^ ECC_F[i]] = i
ECC_B = bytes(ECC_B)


def parity_layout(major_count: int, minor_count: int, major_mult: int, minor_inc: int) -> list:
    """Return, per minor step, a getter for that step's byte of every column."""
    size = major_count * minor_count
    steps = []
    for minor in range(minor_count):
        index = [
            ((major >> 1) * major_mult + (major & 1) + minor * minor_inc) % size
            for major in range(major_count)
        ]
        steps.append(operator.itemgetter(*index))
    return steps


P_STEPS = parity_layout(86, 24, 2, 86)
Q_STEPS = parity_layout(52, 43, 86, 88)


def parity(src: bytes, steps: list) -> bytes:
    """Return the two parity rows for src, computing every column at once."""
    width = len(steps[0](src))
    a = b = 0
    for step in steps:
        row = int.from_bytes(bytes(step(src)), "little")
        a = int.from_bytes((a ^ row).to_bytes(width, "little").translate(ECC_F), "little")
        b ^= row
    fa = int.from_bytes(a.to_bytes(width, "little").translate(ECC_F), "little")
    a = (fa ^ b).to_bytes(width, "little").translate(ECC_B)
    return a + (int.from_bytes(a, "little") ^ b).to_bytes(width, "little")


def bcd(n: int) -> int:
    return n // 10 << 4 | n % 10


def msf(lba: int) -> bytes:
    """Return the BCD minute, second, and frame of lba, after the 2-second lead-in."""
    frames = lba + 150
    return bytes((bcd(frames // 4500), bcd(frames // 75 % 60), bcd(frames % 75)))


def edc(data: bytes) -> int:
    value = 0
    for byte in data:
        value = EDC_TABLE[(value ^ byte) & 0xFF] ^ value >> 8
    return value


def encode_form1(lba: int, subheader: bytes, user: bytes) -> bytes:
    """Return the raw Mode 2 Form 1 sector for lba holding subheader and user."""
    if len(subheader) != 8 or len(user) != 2048:
        raise ValueError(f"Form 1 needs an 8-byte subheader and 2048 bytes, not {len(subheader)} and {len(user)}")
    body = subheader + user
    body += struct.pack("<I", edc(body))
    # ECC covers the header too, zeroed for Mode 2.
    p = parity(bytes(4) + body, P_STEPS)
    q = parity(bytes(4) + body + p, Q_STEPS)
    return SYNC + msf(lba) + b"\x02" + body + p + q
