#!/usr/bin/env python3
"""Fast one-function row count against retail, without linking the EXE.

Compile one translation unit, disassemble one function out of its object,
and compare instruction rows with the function's nonmatching .s file. This
is a loop tool, not a check: `make check` still decides, and a row count
here ignores the .rodata/.data/.bss shifts a size change causes.

    SDK=1 .venv/bin/python tools/quickdiff.py <tu.c> <func>

SDK=1 picks the SDK compiler (GNU C 2.6.3, -mcpu=r3000) that the files in
src/psxsdk/ use; CC1 and CPU override either choice.
"""

import glob
import os
import re
import subprocess
import sys

CC_CPP = "tools/cc/2.7.2-psx-nascar98/cpp"
CPPFLAGS = [
    "-Iinclude", "-Ibuild", "-undef", "-Wall", "-lang-c", "-nostdinc",
    "-D__GNUC__=2", "-D__OPTIMIZE__", "-Dmips", "-D__mips__", "-D__mips",
    "-Dpsx", "-D__psx__", "-D__psx", "-D_PSYQ", "-D_MIPSEL",
    "-D_LANGUAGE_C", "-DLANGUAGE_C",
]
BRANCH = re.compile(r"^(b|j|jal|jr|jalr)")
REGNAME = ("zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra").split()


def compile_tu(tu: str, obj: str) -> None:
    sdk = "psxsdk" in os.path.normpath(tu).split(os.sep) or os.environ.get("SDK") == "1"
    cc1 = os.environ.get("CC1") or (
        "tools/cc1-263.sh" if sdk else "tools/cc/2.7.2-psx-nascar98/cc1")
    cpu = os.environ.get("CPU") or ("r3000" if sdk else "r4000")
    cpp = subprocess.Popen([CC_CPP, *CPPFLAGS, *os.environ.get("DEFS", "").split(), tu], stdout=subprocess.PIPE)
    c = subprocess.Popen(
        [cc1, "-O2", "-G" + os.environ.get("GP", "8"), f"-mcpu={cpu}", "-mips1", "-mgas", "-msoft-float",
         "-fgnu-linker", "-quiet", "-w"],
        stdin=cpp.stdout, stdout=subprocess.PIPE)
    maspsx = subprocess.Popen(
        [".venv/bin/python", "tools/maspsx_extern.py", "--aspsx-version=2.34",
         "-G8", "--dont-force-G0", "--expand-div"],
        stdin=c.stdout, stdout=subprocess.PIPE)
    asm = maspsx.stdout.read()
    for p in (cpp, c, maspsx):
        p.wait()
    if c.returncode:
        raise SystemExit("cc1 failed")
    subprocess.run(
        ["mipsel-linux-gnu-as", "-EL", "-march=r3000", "-mtune=r3000",
         "-no-pad-sections", "-O1", "-Iinclude", "-G8", "-o", obj],
        input=asm, check=True)


def num(text: str) -> str:
    text = text.strip()
    m = re.fullmatch(r"\((.*)\s*>>\s*16\)", text)
    if m:
        return hex(int(m.group(1), 0) >> 16)
    try:
        return hex(int(text, 0))
    except ValueError:
        return text


def normalize(mnemonic: str, operands: str) -> str:
    ops = [o.strip().replace(" ", "").replace("$", "")
           for o in operands.split(",") if o.strip()]
    ops = [re.sub(r"^.*<.*>$", "L", o) for o in ops]
    if BRANCH.match(mnemonic) and ops and not re.fullmatch(r"-?0x[0-9a-f]+",
                                                           ops[-1]):
        ops[-1] = "L"

    def fix(o):
        if ">>" in o:
            return num(o)
        m = re.fullmatch(r"(-?0x[0-9a-fA-F]+|\d+)?\((.+)\)", o)
        return f"{num(m.group(1) or '0')}({m.group(2)})" if m else num(o)

    ops = [fix(o) for o in ops]
    if mnemonic == "move":
        mnemonic, ops = "addu", [ops[0], ops[1], "zero"]

    return " ".join([mnemonic] + ops)


def objdump_rows(obj: str, func: str) -> list[str]:
    out = subprocess.run(
        ["mipsel-linux-gnu-objdump", "-dr", "-j", ".text", obj],
        capture_output=True, text=True, check=True).stdout
    rows, inside = [], False
    for line in out.splitlines():
        if re.match(r"^[0-9a-f]+ <.*>:$", line):
            inside = f"<{func}>:" in line
            continue
        if not inside:
            continue
        reloc = re.match(r"^\s*(?:0x)?[0-9a-f]+:\s+(R_MIPS_\w+)\s+(\S+)", line)
        if reloc and rows:
            kind, sym = reloc.group(1), reloc.group(2)
            if kind == "R_MIPS_HI16":
                rows[-1] = re.sub(r"\s\S+$", f"hi({sym})", rows[-1])
            elif kind == "R_MIPS_LO16":
                if "(" in rows[-1]:
                    rows[-1] = re.sub(r",?(?:0x0|0)?\((\w+)\)$",
                                      lambda m: f"lo({sym})({m.group(1)})",
                                      rows[-1])
                else:
                    rows[-1] = re.sub(r"\s\S+$", f" lo({sym})", rows[-1])
            continue
        m = re.match(r"^\s*[0-9a-f]+:\s+([0-9a-f]{8})\s+(\S+)\s*(.*)$",
                     line)
        if m:
            word, mnem = int(m.group(1), 16), m.group(2)
            ops = m.group(3).split("#")[0]
            if mnem == "li":
                op = (word >> 26) & 0x3F
                mnem = "ori" if op == 0x0D else "addiu"
                rt, rs = (word >> 16) & 0x1F, (word >> 21) & 0x1F
                imm = word & 0xFFFF
                ops = f"${REGNAME[rt]},${REGNAME[rs]},{hex(imm)}"
            rows.append(normalize(mnem, ops))
    return rows


def asm_rows(path: str, func: str) -> list[str]:
    text = open(path).read()
    body = text.split(f"glabel {func}\n", 1)[1].split(f"endlabel {func}")[0]
    rows = []
    for line in body.splitlines():
        m = re.match(
            r"^\s*/\* [0-9a-fA-F]+ [0-9a-fA-F]+ [0-9a-fA-F]+ \*/\s+(\S+)\s*(.*)$",
            line)
        if m:
            row = normalize(m.group(1), m.group(2))
            row = re.sub(r"%hi\((\w+)\)", r"hi(\1)", row)
            row = re.sub(r"%lo\((\w+)\)", r"lo(\1)", row)
            rows.append(row)
    return rows


def main() -> None:
    tu, func = sys.argv[1], sys.argv[2]
    os.makedirs("build/quickdiff", exist_ok=True)
    obj = f"build/quickdiff/{tu.replace('/', '_')}.o"
    compile_tu(tu, obj)
    path = next(iter(glob.glob(f"asm/nonmatchings/**/{func}.s", recursive=True)))
    want, got = asm_rows(path, func), objdump_rows(obj, func)
    want = [r.replace(" ", "") for r in want]
    got = [r.replace(" ", "") for r in got]
    if os.environ.get("NOSYM") == "1":
        # Compare shapes only: SDK externs carry donor names, not D_ names.
        strip = lambda r: re.sub(r"(?:-?0x[0-9a-f]+)?(hi|lo)\([^)]*\)", r"\1", r).replace("0xffff", "-0x1").replace("break0x7", "breakL").replace("break0x6", "breakL")
        want = [strip(r) for r in want]
        got = [strip(r) for r in got]
    n = max(len(want), len(got))
    diff = sum(1 for i in range(n)
               if i >= len(want) or i >= len(got) or want[i] != got[i])
    print(f"{func}: {len(got)} rows built, {len(want)} retail, {diff} differ"
          f" (size {len(got) * 4:#x} vs {len(want) * 4:#x})")
    for i in range(n):
        w = want[i] if i < len(want) else ""
        g = got[i] if i < len(got) else ""
        print(f"{i * 4:4x} {w:<40} {' ' if w == g else '|'} {g}")


main()
