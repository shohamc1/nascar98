#!/usr/bin/env python3
"""List functions still in asm, find near-duplicates, or rank parked drafts.

    .venv/bin/python tools/funcs.py queue [--sdk] [--parked]
    .venv/bin/python tools/funcs.py dups [--threshold 0.94]
    .venv/bin/python tools/funcs.py near [FUNC...]

Both read the linked build (run `make check` first), so matched and asm
functions are measured the same way. `queue` ranks unmatched functions
easiest first, the way sotn-decomp's function_finder does: by length,
then branches. `dups` pairs functions whose opcode sequences have a
Levenshtein similarity at or above the threshold, as sotn-decomp's dups
tool does, and lists pairs where a matched function can guide an
unmatched one first. `near` builds the EXE once per parked
`#ifdef NON_MATCHING` draft, with only that draft switched on, and ranks
the drafts by how many bytes still differ from the retail EXE.
"""

import argparse
import concurrent.futures
import os
import pathlib
import re
import subprocess

import Levenshtein

ELF = "build/slus_005.21.elf"
EXE = "build/SLUS_005.21"
LD_SCRIPT = "build/slus_005.21.ld"
RETAIL = "disc/SLUS_005.21"
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


def parked_drafts(src: pathlib.Path) -> list[tuple[str, int]]:
    """(function, line index of its `#ifdef NON_MATCHING`) for each draft."""
    lines = src.read_text().splitlines()
    drafts = []
    for i, line in enumerate(lines):
        if line != "#ifdef NON_MATCHING":
            continue
        depth, j = 1, i + 1
        while depth:
            if lines[j].startswith("#if"):
                depth += 1
            elif lines[j].startswith("#endif"):
                depth -= 1
            elif lines[j] == "#else" and depth == 1:
                m = re.match(r'INCLUDE_ASM\("[^"]+", (\w+)\);', lines[j + 1])
                if m:
                    drafts.append((m[1], i))
            j += 1
    return drafts


def make_command(target: str, touched: str, tool: str) -> str:
    """The recipe line `make` would run for target, read from `make -n`."""
    out = subprocess.run(
        ["make", "-n", "-W", touched, target],
        capture_output=True, text=True, check=True,
    ).stdout
    return next(line for line in out.splitlines() if tool in line)


def header_deps(src: pathlib.Path, recipe: str) -> list[pathlib.Path]:
    """Every header src reaches through #include, searched as cpp does.

    The Makefile tracks no header dependencies (only the .c, the linker
    script, and fixed_addrs.h), so an edited header leaves a stale object
    that `make` happily reuses. The -I paths come from the compile recipe.
    """
    dirs = [pathlib.Path(t[2:]) for t in recipe.split() if t.startswith("-I")]
    re_quoted = re.compile(r'^\s*#\s*include\s*"([^"]+)"', re.M)
    re_angle = re.compile(r'^\s*#\s*include\s*<([^>]+)>', re.M)

    def resolve(name: str, includer: pathlib.Path, quoted: bool):
        roots = ([includer.parent] if quoted else []) + dirs
        for root in roots:
            cand = root / name
            if cand.is_file():
                return cand.resolve()
        return None

    deps, todo, seen = [], [src.resolve()], set()
    while todo:
        path = todo.pop()
        if path in seen or not path.is_file():
            continue
        seen.add(path)
        if path != src.resolve():
            deps.append(path)
        text = path.read_text(errors="replace")
        for match in re_quoted.finditer(text):
            hit = resolve(match[1], path, True)
            if hit:
                todo.append(hit)
        for match in re_angle.finditer(text):
            hit = resolve(match[1], path, False)
            if hit:
                todo.append(hit)
    return deps


def asm_deps(obj: pathlib.Path) -> list[pathlib.Path]:
    """The .s files the object's INCLUDE_ASM stubs pulled in, from the
    build's own .asmproc.d depfile (make never includes it)."""
    dep = obj.parent / (obj.name[:-len(".c.o")] + ".asmproc.d")
    if not dep.is_file():
        return []
    tokens = dep.read_text().replace("\\\n", " ").split()
    return [pathlib.Path(t) for t in tokens[1:] if t.endswith(".s")]


def invalidate_stale_objects() -> list[str]:
    """Remove build/src/<tu>.c.o files older than their inputs, so the
    next diff/permute/near cannot measure a stale build. Returns the
    removed objects; prints one line per removal."""
    removed = []
    for src in sorted(pathlib.Path("src").rglob("*.c")):
        obj = pathlib.Path(f"build/{src}.o")
        if not obj.is_file():
            continue
        obj_time = obj.stat().st_mtime
        deps = [src, *asm_deps(obj)]
        try:
            deps += header_deps(src, make_command(obj, src, "cc1"))
        except (subprocess.CalledProcessError, StopIteration):
            pass  # no recipe readable; the source mtime check still applies
        for dep in deps:
            if dep.is_file() and dep.stat().st_mtime > obj_time:
                obj.unlink()
                print(f"stale object: {obj} older than {dep} — removed")
                removed.append(str(obj))
                break
    return removed


def score_draft(src: pathlib.Path, name: str, line: int, cmds: dict,
                targets: dict) -> tuple:
    """Build the EXE with one draft on; return (rank key, row)."""
    work = pathlib.Path("build/near") / name
    work.mkdir(parents=True, exist_ok=True)
    lines = src.read_text().splitlines()
    lines[line] = "#if 1"
    variant = work / src.name
    variant.write_text("\n".join(lines) + "\n")

    obj = f"build/{src}.o"
    cc = cmds["cc", str(src)].replace(f" {src} ", f" {variant} ")
    cc = cc.replace(f"-o {obj}", f"-o {work}/unit.o")
    p = subprocess.run(["bash", "-c", cc], capture_output=True, text=True,
                       errors="replace")
    if "Segmentation fault" in p.stderr:
        return (2, 0, 0, name), (name, "cc1 crash", "", "", "")
    if p.returncode or "error" in p.stderr:
        first = next((l for l in p.stderr.splitlines()
                      if "error" in l or "conflicting types" in l), "")
        return (2, 0, 0, name), (name, "cc1 error", "", "", first[:70])

    script = pathlib.Path(LD_SCRIPT).read_text().replace(obj, f"{work}/unit.o")
    (work / "link.ld").write_text(script)
    ld = cmds["ld"].replace(f"-T {LD_SCRIPT}", f"-T {work}/link.ld")
    ld = ld.replace(f"-o {ELF}", f"-o {work}/game.elf")
    ld = re.sub(r"-Map \S+", f"-Map {work}/game.map", ld)
    p = subprocess.run(["bash", "-c", ld], capture_output=True, text=True,
                       errors="replace")
    if p.returncode:
        return (2, 0, 0, name), (name, "link error", "", "", p.stderr[:70])
    subprocess.run(
        ["mipsel-linux-gnu-objcopy", "-O", "binary", "--gap-fill", "0",
         "--pad-to", "0x92000", f"{work}/game.elf", f"{work}/game.exe"],
        check=True,
    )

    nm = subprocess.run(["mipsel-linux-gnu-nm", "-S", f"{work}/game.elf"],
                        capture_output=True, text=True, check=True).stdout
    m = re.search(rf"^\w+ (\w+) [Tt] {name}$", nm, re.M)
    size = int(m[1], 16) if m else 0
    addr, want = targets[name]
    delta = size - want
    if delta:
        return (1, abs(delta), 0, name), (name, f"{delta:+}", "", "", "")

    built = (work / "game.exe").read_bytes()
    retail = pathlib.Path(RETAIL).read_bytes()
    start = addr - VRAM + FILE_OFFSET
    in_func = sum(a != b for a, b in
                  zip(built[start:start + size], retail[start:start + size]))
    total = sum(a != b for a, b in zip(built, retail))
    note = "MATCH" if total == 0 else ""
    return (0, in_func, total, name), (name, "0", in_func, total, note)


def near(args: argparse.Namespace) -> None:
    if invalidate_stale_objects():
        subprocess.run(["make", EXE], check=True)
    syms = subprocess.run(["mipsel-linux-gnu-nm", "-S", ELF],
                          capture_output=True, text=True, check=True).stdout
    targets = {
        m[3]: (int(m[1], 16), int(m[2], 16))
        for m in re.finditer(r"^(\w+) (\w+) [Tt] (\w+)$", syms, re.M)
    }
    jobs = [
        (src, name, line)
        for src in sorted(pathlib.Path("src").rglob("*.c"))
        for name, line in parked_drafts(src)
        if not args.funcs or name in args.funcs
    ]
    cmds = {("cc", str(src)): make_command(f"build/{src}.o", str(src), "cc1")
            for src in {src for src, _, _ in jobs}}
    cmds["ld"] = make_command(ELF, "build/src/game.c.o", "-ld ")

    with concurrent.futures.ThreadPoolExecutor(os.cpu_count()) as pool:
        results = sorted(pool.map(
            lambda job: score_draft(*job, cmds, targets), jobs))
    print("name\tsize_delta\tfunc_bytes\texe_bytes\tnote")
    for _, row in results:
        print(*row, sep="\t")


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
    n = sub.add_parser("near", help="parked drafts, closest to matching first")
    n.add_argument("funcs", nargs="*", help="rank only these functions")
    n.set_defaults(run=near)
    args = parser.parse_args()
    args.run(args)


if __name__ == "__main__":
    main()
