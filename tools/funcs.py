#!/usr/bin/env python3
"""List functions still in asm, or find near-duplicate functions.

    .venv/bin/python tools/funcs.py queue [--sdk] [--parked]
    .venv/bin/python tools/funcs.py dups [--threshold 0.94]

Both read the linked build (run `make check` first), so matched and asm
functions are measured the same way. `queue` ranks unmatched functions
easiest first, the way sotn-decomp's function_finder does: by length,
then branches. `dups` pairs functions whose opcode sequences have a
Levenshtein similarity at or above the threshold, as sotn-decomp's dups
tool does, and lists pairs where a matched function can guide an
unmatched one first.
"""

import argparse
import pathlib
import re
import subprocess

import Levenshtein

ELF = "build/slus_005.21.elf"
EXE = "build/SLUS_005.21"
VRAM = 0x80012000
FILE_OFFSET = 0x800
SDK_START = "__SN_ENTRY_POINT"


def functions() -> list[dict]:
    """Every text symbol with its instruction words, unit, and status."""
    out = subprocess.run(
        ["mipsel-linux-gnu-nm", "-n", "-S", ELF],
        capture_output=True, text=True, check=True,
    ).stdout
    # Rodata and data labels share the .main output section, so nm types
    # them T too; keep only symbols below the end of .text.
    text_end = int(re.search(r"^(\w+) \w main_TEXT_END$", out, re.M)[1], 16)
    syms = []
    for line in out.splitlines():
        parts = line.split()
        if len(parts) == 4 and parts[2] in "Tt" and "." not in parts[3]:
            addr = int(parts[0], 16)
            if addr < text_end:
                syms.append((addr, int(parts[1], 16), parts[3]))
    sdk_start = next(a for a, _, n in syms if n == SDK_START)
    exe = pathlib.Path(EXE).read_bytes()

    asm, parked = set(), set()
    for src in pathlib.Path("src").rglob("*.c"):
        text = src.read_text()
        asm.update(re.findall(r"^INCLUDE_ASM\(\"[^\"]+\", (\w+)\);", text, re.M))
        parked.update(
            re.findall(r"^#else\nINCLUDE_ASM\(\"[^\"]+\", (\w+)\);", text, re.M)
        )

    # gas aliases (FUNCArgs = FUNC) share an address; keep one name per
    # address, preferring the asm one so its status is right.
    by_addr = {}
    for addr, size, name in syms:
        if addr not in by_addr or name in asm:
            by_addr[addr] = (addr, size, name)

    funcs = []
    for addr, size, name in by_addr.values():
        start = addr - VRAM + FILE_OFFSET
        words = [
            int.from_bytes(exe[i:i + 4], "little")
            for i in range(start, start + size, 4)
        ]
        status = "parked" if name in parked else "asm" if name in asm else "C"
        funcs.append({
            "name": name,
            "unit": "sdk" if addr >= sdk_start else "game",
            "status": status,
            "words": words,
        })
    return funcs


def is_branch(word: int) -> bool:
    op = word >> 26
    if op == 0:
        return word & 0x3F in (0x08, 0x09)  # jr, jalr
    return op in (1, 2, 3, 4, 5, 6, 7)  # regimm, j, jal, beq, bne, blez, bgtz


def is_jump_table(word: int) -> bool:
    """jr through a register other than $ra."""
    return word >> 26 == 0 and word & 0x3F == 0x08 and (word >> 21) & 31 != 31


def queue(args: argparse.Namespace) -> None:
    rows = []
    for f in functions():
        if f["status"] == "C" or (f["unit"] == "sdk") != args.sdk:
            continue
        if args.parked and f["status"] != "parked":
            continue
        words = f["words"]
        rows.append((
            len(words),
            sum(map(is_branch, words)),
            "yes" if any(map(is_jump_table, words)) else "",
            f["status"],
            f["name"],
        ))
    rows.sort(key=lambda r: (r[0], r[1], r[4]))
    print("insns\tbranches\tjtbl\tstatus\tname")
    for row in rows:
        print(*row, sep="\t")


def opcode_key(words: list[int]) -> str:
    """One character per instruction: its opcode, or funct for SPECIAL."""
    return "".join(
        chr(0x100 + (w & 0x3F)) if w >> 26 == 0 else chr(w >> 26) for w in words
    )


def dups(args: argparse.Namespace) -> None:
    funcs = [f for f in functions() if len(f["words"]) >= args.min_insns]
    for f in funcs:
        f["key"] = opcode_key(f["words"])
    funcs.sort(key=lambda f: len(f["key"]))
    pairs = []
    for i, a in enumerate(funcs):
        for b in funcs[i + 1:]:
            longest = len(b["key"])
            if len(a["key"]) < longest * args.threshold:
                break  # every later b is longer still
            if a["status"] == "C" and b["status"] == "C":
                continue
            dist = Levenshtein.distance(a["key"], b["key"])
            similarity = 1 - dist / longest
            if similarity >= args.threshold:
                pairs.append((similarity, a, b))
    # A matched partner is the useful case: its C is a template.
    pairs.sort(key=lambda p: ("C" not in (p[1]["status"], p[2]["status"]), -p[0]))
    print("similarity\tinsns\tfunction\tstatus\tpartner\tstatus")
    for similarity, a, b in pairs:
        if b["status"] == "C":
            a, b = b, a
        print(
            f"{similarity:.3f}", len(b["words"]), b["name"], b["status"],
            a["name"], a["status"], sep="\t",
        )


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = parser.add_subparsers(required=True)
    q = sub.add_parser("queue", help="unmatched functions, easiest first")
    q.add_argument("--sdk", action="store_true", help="SDK instead of game")
    q.add_argument("--parked", action="store_true", help="parked drafts only")
    q.set_defaults(run=queue)
    d = sub.add_parser("dups", help="near-duplicate function pairs")
    d.add_argument("--threshold", type=float, default=0.94)
    d.add_argument("--min-insns", type=int, default=8,
                   help="skip tiny functions; they match each other trivially")
    d.set_defaults(run=dups)
    args = parser.parse_args()
    args.run(args)


if __name__ == "__main__":
    main()
