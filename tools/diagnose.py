#!/usr/bin/env python3
"""Print one verdict for why FUNC's compiled code differs from retail.

    .venv/bin/python tools/diagnose.py FUNC

Diffs FUNC the way the workflow does — asm-differ plain output, rebuilt
first — then classifies the rows, in this decision order:

    MATCH                score 0
    SIZE_DELTA           FUNC's own length differs from its splat .s
                         header; nothing below this verdict is reliable
                         until the length is right
    GP_LAYOUT_SHIFT      every $gp offset moved by one constant because
                         a size change elsewhere moved _gp
    REGISTER_PERMUTATION only register names differ
    INSTRUCTION_ORDER    same instruction multiset, different order
    STRUCTURAL           missing, extra, or genuinely different rows

Each verdict comes with evidence lines and the next lever to pull, mined
from the symptom tables in kb/psx/matching.md. Exits 0 on MATCH, 1 on
any mismatch, 2 on tool errors. Stale build objects (edited source,
header, or INCLUDE_ASM'd .s newer than their .o) are removed first and
the diff's own `make` rebuilds them.
"""

import collections
import pathlib
import re
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).parent))
from funcs import invalidate_stale_objects  # noqa: E402

DIFF = [
    ".venv/bin/python", "tools/asm-differ/diff.py",
    "--no-pager", "--format", "plain", "--max-lines", "6000", "-m",
]
ELF = "build/slus_005.21.elf"
MAP = "build/slus_005.21.map"
RETAIL_GP = 0x800A2CE0
VRAM_BASE = 0x80011800  # diff display address = vaddr - VRAM_BASE
MARKERS = " rRiSs|<>"
REGISTERS = {
    "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t8", "t9", "k0", "k1", "gp", "sp", "fp", "s8", "ra",
}
POLARITY_PAIRS = {
    "beq": "bne", "blez": "bgtz", "bltz": "bgez", "bltzal": "bgezal",
}
INSN = r"(?:[\da-f]+:\s*)?(?:~>\s*)?\s*"


class Row:
    def __init__(self, marker: str, base: str, cur: str):
        self.marker = marker
        self.base = base          # target-side text, "" if absent
        self.cur = cur            # current-side text, "" if absent

    def mnemonic(self, side: str) -> str:
        m = re.match(INSN + r"(\S+)", getattr(self, side))
        return m[1] if m else ""

    def address(self, side: str) -> str:
        m = re.match(r"\s*([\da-f]+):", getattr(self, side))
        return m[1] if m else "?"

    def operands(self, side: str) -> list:
        m = re.match(INSN + r"\S+\s*(.*)", getattr(self, side))
        return re.split(r"[,\s]+", m[1]) if m and m[1] else []


def run_diff(func: str) -> str:
    p = subprocess.run(DIFF + [func], capture_output=True, text=True,
                       errors="replace")
    if p.returncode:
        sys.stderr.write(p.stderr[-2000:])
        print(f"diff.py failed for {func} (exit {p.returncode})",
              file=sys.stderr)
        sys.exit(2)
    return p.stdout


def parse_rows(out: str):
    """(score, rows, unparsed) from asm-differ plain output. Each cell is
    padded to --width (50, the default we invoke it with), so the row
    marker sits at index 50, one cell past the target text."""
    lines = out.splitlines()
    start = next((i for i, l in enumerate(lines) if l.startswith("TARGET")),
                 None)
    header = lines[start] if start is not None else ""
    m = re.search(r"CURRENT \((\d+)\)", header)
    if start is None or not m:
        print("no diff table in asm-differ output:\n" + out[:2000],
              file=sys.stderr)
        sys.exit(2)
    col = 50
    rows, unparsed = [], 0
    for line in lines[start + 1:]:
        if not line.strip():
            continue
        marker = line[col] if len(line) > col else " "
        if marker not in MARKERS:
            unparsed += 1
            continue
        cur = line[col + 1:].rstrip() if len(line) > col else ""
        rows.append(Row(marker, line[:col].rstrip(),
                        cur.lstrip()))  # skip the line-number gutter
    return int(m[1]), rows, unparsed


def cut_rows(rows, end: int):
    """Drop the diff window's tail past the function's last address, so
    a later function's diffs can't pollute the verdict."""
    out = []
    for row in rows:
        base_addr = re.match(r"\s*([\da-f]+):", row.base)
        if base_addr and int(base_addr[1], 16) >= end:
            break
        out.append(row)
    return out


def splat_size(func: str):
    """The authoritative retail length: the .s file's header."""
    for path in sorted(pathlib.Path("asm/nonmatchings").rglob(f"{func}.s")):
        m = re.match(rf"nonmatching {func}, (0x[0-9A-Fa-f]+)",
                     path.read_text().splitlines()[0])
        if m:
            return int(m[1], 16)
    return None


def elf_syms() -> dict:
    """name -> (address, size) from the built ELF."""
    out = subprocess.run(["mipsel-linux-gnu-nm", "-S", ELF],
                         capture_output=True, text=True, check=True).stdout
    return {m[3]: (int(m[1], 16), int(m[2], 16)) for m in
            re.finditer(r"^(\w+) (\w+) [Tt] (\w+)$", out, re.M)}


def gp_from_map():
    for line in pathlib.Path(MAP).read_text().splitlines():
        m = re.search(r"0x([0-9a-fA-F]+)\s+_gp\s*=", line)
        if m:
            return int(m[1], 16)
    return None


def gp_deltas(rows):
    """(delta, gp rows) if every $gp-relative offset moved by one
    constant; (None, gp rows) otherwise."""
    deltas, total = [], 0
    for row in rows:
        t = re.search(r"(-?0x[0-9a-f]+)\(gp\)", row.base)
        c = re.search(r"(-?0x[0-9a-f]+)\(gp\)", row.cur)
        if not (t and c):
            continue
        total += 1
        deltas.append(int(t[1], 16) - int(c[1], 16))
    if total and deltas.count(deltas[0]) == len(deltas) and deltas[0]:
        return deltas[0], total
    return None, total


def find_offenders(syms: dict):
    """Functions whose built size disagrees with their .s header: the
    size change that shifted everything. The psxsdk unit is skipped:
    its ELF symbol sizes are unreliable even in a matching build (gas
    label-delta quirks), per kb/psx/matching.md 'Length errors'."""
    offenders = {}
    for path in pathlib.Path("asm/nonmatchings").rglob("*.s"):
        if "psxsdk" in path.parts:
            continue
        m = re.match(r"nonmatching (\w+), (0x[0-9A-Fa-f]+)",
                     path.read_text().splitlines()[0])
        if not m:
            continue
        sym = syms.get(m[1])
        want, got = int(m[2], 16), sym[1] if sym else None
        if got is None or got == want:
            continue
        offenders[m[1]] = (m[1], want, got)
    return sorted(offenders.values())


def register_swaps(reg_rows):
    """retail-register -> ours-register mappings, with the rows that
    show each mapping."""
    swaps = collections.defaultdict(list)
    for row in reg_rows:
        for a, b in zip(row.operands("base"), row.operands("cur")):
            if a != b and a in REGISTERS and b in REGISTERS:
                swaps[(a, b)].append(row.address("base"))
    return swaps


def reg_evidence(reg_rows):
    lines = []
    swaps = register_swaps(reg_rows)
    for (a, b), addrs in sorted(swaps.items(), key=lambda kv: -len(kv[1]))[:3]:
        where = ", ".join(addrs[:4]) + (f" (+{len(addrs) - 4})" if len(addrs) > 4 else "")
        lines.append(f"retail {a} -> ours {b} ({len(addrs)} rows: {where})")
    return lines


def lui_materializations(rows):
    """constant -> count, per side, over all rows."""
    counts = collections.Counter(), collections.Counter()
    for row in rows:
        for side, tally in (("base", counts[0]), ("cur", counts[1])):
            m = re.match(INSN + r"lui\s+\w+,(0x[0-9a-f]+)",
                         getattr(row, side))
            if m:
                tally[m[1]] += 1
    return counts


def imm_shuffle(rows):
    """True if the function-wide immediate multiset is the same on both
    sides, so immediate-only diff rows pair differently only because of
    a reorder — not because a constant is actually wrong."""
    def imms(side):
        out = []
        for row in rows:
            out += re.findall(r"-?0x[0-9a-f]+|\b\d+\b",
                              " ".join(row.operands(side)))
        return sorted(out)
    return imms("base") == imms("cur")


def case_compare_chain(rows, side):
    """The constants of li + beq/bne compare chains, in address order."""
    values = []
    for i, row in enumerate(rows):
        m = re.match(INSN + r"li\s+\w+,(-?(?:0x[0-9a-f]+|\d+))",
                     getattr(row, side))
        if not m:
            continue
        for j in (i + 1, i + 2):
            if j >= len(rows):
                break
            mn = rows[j].mnemonic(side)
            if mn in ("beq", "bne"):
                values.append(int(m[1], 0))
                break
            if mn and mn != "nop":
                break
    return values


def asm_stub_warning(func: str):
    """A parked or never-decompiled function diffs the retail stub
    against itself: every verdict is then meaningless. A draft whose
    guard was flipped to #if 1 is live C and diffs for real."""
    for src in sorted(pathlib.Path("src").rglob("*.c")):
        lines = src.read_text().splitlines()
        for i, line in enumerate(lines):
            if not re.match(rf'INCLUDE_ASM\("[^"]+", {func}\);', line):
                continue
            # The nearest guard above the INCLUDE_ASM decides: a parked
            # draft keeps `#ifdef NON_MATCHING`, a flipped one reads #if 1,
            # and no guard at all means the function was never decompiled.
            guard = next(((j, l) for j, l in reversed(list(enumerate(lines[:i])))
                          if l.startswith(("#ifdef", "#if "))), (None, ""))
            if guard[1] == "#if 1":
                return None
            if guard[1].startswith("#ifdef"):
                return (f"{func} is parked behind #ifdef NON_MATCHING at "
                        f"{src}:{guard[0] + 1}; this diff is the retail "
                        f"stub against itself — flip the guard to #if 1 "
                        f"first")
            return (f"{func} is still INCLUDE_ASM ({src}:{i + 1}), not "
                    f"decompiled; this diff is the retail stub against "
                    f"itself")
    return None


def counter_str(counter) -> str:
    inner = ", ".join(f"{n}x {m}" for m, n in counter.most_common())
    return "{" + inner + "}"


def print_verdict(verdict, evidence, lever, notes=()):
    print(f"VERDICT: {verdict}")
    for line in evidence:
        print(f"  {line}")
    if lever:
        print(f"  next lever: {lever}")
    for note in notes:
        print(f"  note: {note}")


def diagnose(func: str) -> int:
    if invalidate_stale_objects():
        print("(diff.py -m rebuilds the removed objects)")

    score, rows, unparsed = parse_rows(run_diff(func))
    # Read build outputs only after the diff's own `make` rebuilt them.
    syms = elf_syms()
    if func not in syms:
        print(f"{func}: no text symbol in {ELF} (typo, or build failed?)",
              file=sys.stderr)
        sys.exit(2)
    end = syms[func][0] + (splat_size(func) or syms[func][1]) - VRAM_BASE
    rows = cut_rows(rows, end)
    differing = [r for r in rows if r.marker != " "]
    notes = [f"asm-differ score {score} over {len(rows)} rows"]
    if unparsed:
        notes.append(f"{unparsed} rows unparsed (overlong cells)")
    stub = asm_stub_warning(func)
    if stub:
        notes.append(stub)

    # 1. MATCH — by the function's own rows: asm-differ's score covers
    # its whole disassembly window, which can include later functions.
    if not rows:
        print(f"{func}: diff produced no rows (build failure?)",
              file=sys.stderr)
        sys.exit(2)
    if not differing:
        print_verdict("MATCH", [], None, notes)
        return 0

    # 2. SIZE_DELTA — nothing below is reliable until the length is right
    want, got = splat_size(func), syms[func][1]
    if want is None:
        notes.append(f"no splat .s header found for {func}")
    elif got != want:
        print_verdict(
            "SIZE_DELTA",
            [f"retail {want:#x} bytes ({func}.s header) vs built {got:#x} "
             f"from nm -S: {got - want:+d} bytes"],
            "fix the length first — every other diff row, including $gp "
            "offsets, is noise until the sizes agree (kb/psx/matching.md "
            "'Length errors that look like drift')", notes)
        return 1

    # 3. GP_LAYOUT_SHIFT — ground truth is the map, not the diff rows:
    # a moved _gp also moves this function's address, so the rows
    # themselves may already be misaligned.
    gp = gp_from_map()
    if gp is not None and gp != RETAIL_GP:
        evidence = [f"_gp = {gp:#x} in {MAP}; retail is {RETAIL_GP:#x} "
                    f"({gp - RETAIL_GP:+#x})"]
        delta, gp_total = gp_deltas(rows)
        if delta is not None:
            evidence.append(f"all {gp_total} $gp-relative rows moved by "
                            f"{delta:+#x}")
        for name, w, g in find_offenders(syms)[:5]:
            evidence.append(f"offender? {name}: retail {w:#x} vs built "
                            f"{g:#x} ({g - w:+d})")
        notes.append("with _gp moved, this function's address moved too — "
                     "the diff rows themselves can be misaligned")
        print_verdict(
            "GP_LAYOUT_SHIFT", evidence,
            "fix the offending function's length — a size change moved "
            "main_sdata_start_OFFSET and _gp with it, so every $gp row "
            "(and possibly the whole row pairing) is noise until then "
            "(kb/psx/matching.md 'Trust the right check')", notes)
        return 1
    delta, gp_total = gp_deltas(rows)
    if delta is not None:
        notes.append("$gp rows moved uniformly but _gp is at its retail "
                     "value; treating them as ordinary immediate rows")

    reg_rows = [r for r in differing if r.marker in "rR"]
    imm_rows = [r for r in differing if r.marker in "is"]
    change_rows = [r for r in differing if r.marker == "|"]
    missing = [r for r in differing if r.marker == "<"]
    extra = [r for r in differing if r.marker == ">"]
    order_rows = [r for r in change_rows
                  if r.mnemonic("base") == r.mnemonic("cur")]

    target_mnems = collections.Counter(
        r.mnemonic("base") for r in rows if r.base)
    current_mnems = collections.Counter(
        r.mnemonic("cur") for r in rows if r.cur)
    residual = (target_mnems - current_mnems) + (current_mnems - target_mnems)

    # 4. REGISTER_PERMUTATION — every differing row is register-only
    if reg_rows and not (imm_rows or change_rows or missing or extra):
        print_verdict(
            "REGISTER_PERMUTATION",
            [f"{len(reg_rows)} register-only rows of {len(rows)}, same "
             f"size and schedule"] + reg_evidence(reg_rows),
            "statement/declaration order, expression-vs-local forms, "
            "permuter floor test, then cc1 allocation archaeology "
            "(kb/psx/ga-debug/)", notes)
        return 1

    # 5. INSTRUCTION_ORDER — same instruction multiset, different order
    if not residual:
        evidence = []
        if order_rows:
            evidence.append(f"{len(order_rows)} same-opcode rows reordered")
        if missing:
            def brief(row, side):
                ops = ",".join(row.operands(side)[:2])
                return row.mnemonic(side) + (f" {ops}" if ops else "")
            names = "; ".join(brief(r, "base") for r in missing[:4])
            at = missing[0].address("base")
            ours = extra[0].address("cur") if extra else "?"
            evidence.append(f"block ({names}) present on both sides; retail "
                            f"at {at}, ours at {ours}")
        if imm_rows:
            if imm_shuffle(rows):
                evidence.append(f"{len(imm_rows)} immediate-only rows: "
                                f"function-wide immediates match, so they "
                                f"are reorder/target-shift noise")
            else:
                evidence.append(f"{len(imm_rows)} immediate-only rows and "
                                f"function-wide immediates differ: a "
                                f"constant is actually wrong")
        t_lui, c_lui = lui_materializations(rows)
        for const, n in t_lui.items():
            if n > c_lui.get(const, 0):
                evidence.append(f"retail re-materialises lui {const} {n}x "
                                f"vs ours {c_lui.get(const, 0)}x")
                notes.append("address re-materialisation fingerprint: give "
                             "each access a distinct asm-label spelling "
                             "(kb/psx/matching.md 'Re-materialising "
                             "addresses across calls')")
        verdict = "INSTRUCTION_ORDER"
        if reg_rows:
            verdict = "REGISTER_PERMUTATION + INSTRUCTION_ORDER"
            evidence[0:0] = [f"{len(reg_rows)} register-only rows"] + \
                reg_evidence(reg_rows)
        if not evidence:
            evidence = [f"{len(differing)} differing rows"]
        print_verdict(
            verdict, evidence,
            "delay-slot contents and load placement: statement splitting "
            "and barriers (kb/psx/matching.md 'Statement splitting and "
            "priority', 'Delay slots')", notes)
        return 1

    # 6. STRUCTURAL — with cheap fingerprints
    evidence = []
    if missing:
        evidence.append(f"{len(missing)} rows missing in ours "
                        f"{counter_str(collections.Counter(r.mnemonic('base') for r in missing))}")
    if extra:
        evidence.append(f"{len(extra)} rows extra in ours "
                        f"{counter_str(collections.Counter(r.mnemonic('cur') for r in extra))}")
    if change_rows:
        evidence.append(f"{len(change_rows)} rows with different "
                        f"instructions")
    lever = "rework the C shape (kb/psx/matching.md 'Control flow')"
    hoist = [r for r in missing
             if r.mnemonic("base") == "li"
             and re.match(INSN + r"li\s+s\d+,", r.base)]
    if hoist:
        consts = ", ".join(r.operands("base")[-1] for r in hoist[:4])
        evidence.append(f"constant-hoist fingerprint: {len(hoist)} missing "
                        f"prologue li sN,{consts}")
        lever = ("write the constants as variables at function top "
                 "(kb/psx/matching.md 'Named temporaries')")
    polarity = [r for r in change_rows
                if POLARITY_PAIRS.get(r.mnemonic("base")) == r.mnemonic("cur")
                or POLARITY_PAIRS.get(r.mnemonic("cur")) == r.mnemonic("base")]
    if polarity:
        a = polarity[0]
        evidence.append(f"inverted-branch fingerprint: "
                        f"{a.mnemonic('base')} vs {a.mnemonic('cur')} at "
                        f"{a.address('base')}")
        lever = ("swap the condition so the retail fall-through path is "
                 "the else-arm (kb/psx/matching.md 'Branch sense and arm "
                 "layout')")
    t_chain = case_compare_chain(rows, "base")
    c_chain = case_compare_chain(rows, "cur")
    if (len(t_chain) >= 3 or len(c_chain) >= 3) and t_chain != c_chain:
        fmt = lambda v: "[" + ",".join(hex(x) for x in v) + "]"
        evidence.append(f"case-compare chain: retail {fmt(t_chain)} vs ours "
                        f"{fmt(c_chain)}")
        notes.append("switch fingerprint: gcc sorts/balances a switch's "
                     "compare tree while an if-chain tests in source order; "
                     "case bodies emit in source order either way "
                     "(kb/psx/matching.md 'Case order and layout', "
                     "'Choosing switch or if')")
    if reg_rows:
        evidence.append(f"also {len(reg_rows)} register-only rows")
        evidence += reg_evidence(reg_rows)
    print_verdict("STRUCTURAL", evidence, lever, notes)
    return 1


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    sys.exit(diagnose(sys.argv[1]))


if __name__ == "__main__":
    main()
