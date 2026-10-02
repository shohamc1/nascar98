#!/usr/bin/env python3
"""Find Psy-Q SDK library objects in a PS-X EXE by signature.

Usage:
  python3 tools/psyq_sigs.py EXE                 score each SDK version
  python3 tools/psyq_sigs.py EXE --symbols VER.. print splat symbol lines

Signatures come from lab313ru/psx_psyq_signatures (tools/psyq_signatures).
A game can link libraries from more than one SDK release, so --symbols takes
several versions and keeps, for each address, the longest signature that
matched. A signature must match exactly once: short ones (BIOS call veneers,
tiny wrappers) also match unrelated game code.
"""

import argparse
import glob
import json
import os
import re
import struct

SIG_DIR = os.path.join(os.path.dirname(__file__), "psyq_signatures")
MIN_LEN = 12


def load_exe(path: str) -> tuple[bytes, int]:
    data = open(path, "rb").read()
    if data[:8] != b"PS-X EXE":
        raise SystemExit(f"{path}: not a PS-X EXE")
    vram, size = struct.unpack_from("<2I", data, 0x18)
    return data[0x800 : 0x800 + size], vram


def compile_sig(sig: str) -> re.Pattern:
    parts = (b"." if t == "??" else re.escape(bytes([int(t, 16)])) for t in sig.split())
    return re.compile(b"".join(parts), re.S)


def versions() -> list[str]:
    return sorted(v for v in os.listdir(SIG_DIR) if v.isdigit())


def matches(text: bytes, ver: str):
    """Yield (lib, obj, offset, length, labels) for each object that matches."""
    for path in glob.glob(os.path.join(SIG_DIR, ver, "*.json")):
        lib = os.path.basename(path)[: -len(".json")]
        for obj in json.load(open(path)):
            sig = obj.get("sig", "")
            length = len(sig.split())
            if length < MIN_LEN:
                continue
            hits = [m.start() for m in compile_sig(sig).finditer(text) if m.start() % 4 == 0]
            if len(hits) == 1:
                yield lib, obj["name"], hits[0], length, obj["labels"]


def score(text: bytes) -> None:
    print("version  objects  bytes")
    for ver in versions():
        found = list(matches(text, ver))
        print(f"{ver:>7}  {len(found):7d}  {sum(m[3] for m in found):6d}")


def symbols(text: bytes, vram: int, vers: list[str]) -> None:
    best = {}  # offset -> (length, ver, lib, obj, labels)
    for ver in vers:
        for lib, obj, off, length, labels in matches(text, ver):
            if off not in best or length > best[off][0]:
                best[off] = (length, ver, lib, obj, labels)
    names = {}
    for off, (length, ver, lib, obj, labels) in sorted(best.items()):
        for label in labels:
            name = label["name"]
            if name.startswith(("loc_", "text_", "lab_", "def_")):
                continue
            addr = vram + off + label["offset"]
            names.setdefault(addr, name)
    seen = set()
    for addr, name in sorted(names.items()):
        if name in seen:  # a static function another object also defines
            name = f"{name}_{addr:08X}"
        seen.add(name)
        print(f"{name} = 0x{addr:08X}; // type:func")


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("exe")
    ap.add_argument("--symbols", nargs="+", metavar="VER")
    args = ap.parse_args()
    text, vram = load_exe(args.exe)
    if args.symbols:
        symbols(text, vram, args.symbols)
    else:
        score(text)


if __name__ == "__main__":
    main()
