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
    best = {}  # offset -> (length, [version, lib, obj, labels, ...])
    for ver in vers:
        for lib, obj, off, length, labels in matches(text, ver):
            if off not in best or length > best[off][0]:
                best[off] = (length, [(ver, lib, obj, labels)])
            elif length == best[off][0]:
                best[off][1].append((ver, lib, obj, labels))

    ignored = ("loc_", "text_", "lab_", "def_")
    starts = {}
    for off, (_, candidates) in best.items():
        names = {label["name"] for _, _, _, labels in candidates
                 for label in labels
                 if label["offset"] == 0 and not label["name"].startswith(ignored)}
        starts[off] = names

    # Resolve calls only through names that have no competing signature at
    # their address. This is enough to distinguish the masked SpuRead/Write
    # JAL without trusting signature file order.
    callees = {}
    for off, (_, candidates) in best.items():
        if len(starts[off]) != 1:
            continue
        for _, _, _, labels in candidates:
            for label in labels:
                name = label["name"]
                if not name.startswith(ignored):
                    addr = vram + off + label["offset"]
                    callees.setdefault(addr, set()).add(name)

    names = {}
    # These releases rename the same BIOS veneer in the same library object.
    aliases = [
        {"InitPAD", "InitPAD2"}, {"StartPAD", "StartPAD2"},
        {"delete", "erase"}, {"InitCARD", "InitCARD2"},
        {"StartCARD", "StartCARD2"}, {"StopCARD", "StopCARD2"},
    ]
    for off, (_, candidates) in sorted(best.items()):
        is_alias = starts[off] in aliases and len({
            (lib, obj) for _, lib, obj, _ in candidates
        }) == 1
        if len(starts[off]) > 1 and not is_alias:
            is_spu_pair = starts[off] == {"SpuRead", "SpuWrite"} and all(
                lib == "LIBSPU.LIB" and obj in ("S_R.OBJ", "S_W.OBJ")
                for _, lib, obj, _ in candidates
            )
            if not is_spu_pair:
                continue
            word = struct.unpack_from("<I", text, off + 0x28)[0]
            if word >> 26 != 3:  # JAL
                continue
            target = ((vram + off + 0x2C) & 0xF0000000) | ((word & 0x03FFFFFF) << 2)
            target_names = callees.get(target, set())
            wanted = {"_spu_read": "SpuRead", "_spu_write": "SpuWrite"}
            if len(target_names) != 1 or next(iter(target_names), "") not in wanted:
                continue
            chosen = wanted[next(iter(target_names))]
            candidates = [c for c in candidates if any(
                label["offset"] == 0 and label["name"] == chosen
                for label in c[3]
            )]
            if not candidates:
                continue
        _, _, _, labels = candidates[0]
        for label in labels:
            name = label["name"]
            if name.startswith(ignored):
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
