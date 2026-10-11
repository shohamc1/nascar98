"""Run maspsx, treating small `.extern` symbols as $gp-relative.

gcc writes `.extern sym, size` for every external it uses, and ASPSX
addresses a symbol through $gp when its size is within -G. maspsx ignores
`.extern`, so it assumes a store such as `sw $2,sym` expands through $at
and drops the load-delay nop after a `lw $2`. GNU as with -G8 then emits a
$gp store, and the hazard stays. Registering small externs as sdata lets
maspsx see the $gp access. See kb/psx/toolchain.md.
"""

import re
import runpy
import sys
from pathlib import Path

MASPSX = Path(__file__).parent / "maspsx"
sys.path.insert(0, str(MASPSX))

import maspsx  # noqa: E402
from maspsx import MaspsxProcessor  # noqa: E402

_preprocess_lines = MaspsxProcessor.preprocess_lines

# .sdata starts at _gp; the last $gp-reached .sbss symbol is D_800A3A94.
SMALL_START, SMALL_END = 0x800A2CE0, 0x800A3A98
_ADDRS = {}
for _line in (Path(__file__).parent.parent / "config/symbol_addrs.txt").read_text().splitlines():
    _m = re.match(r"\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)", _line)
    if _m:
        _ADDRS[_m.group(1)] = int(_m.group(2), 16)


def may_be_small(name):
    if re.search(r"Absolute\d*$", name):
        return False  # lui aliases (Makefile defsyms) are never $gp
    m = re.match(r"D_([0-9A-F]{8})$", name)
    addr = int(m.group(1), 16) if m else _ADDRS.get(name)
    return addr is None or SMALL_START <= addr < SMALL_END


def preprocess_lines(self):
    _preprocess_lines(self)
    prev = None
    for i, line in enumerate(self.lines):
        # gcc 2.7.2 emits ".rdata / .align 3" before every switch jump
        # table, but the retail tables sit at 4-byte alignment (430 words
        # at 0 mod 8 vs 432 at 4 mod 8): ASPSX 2.34 did not 8-align them.
        # GNU as reads .align logarithmically, so align the tables to 4.
        if re.match(r"\s*\.align\s+3\s*$", line) and re.match(
            r"\s*\.rdata\s*$", prev or ""
        ):
            self.lines[i] = re.sub(r"3\s*$", "2", line)
        if line.strip():
            prev = line
        match = re.match(r"\.extern\s+([^,\s]+)\s*,\s*([0-9]+)", line)
        if match and not may_be_small(match.group(1)):
            # Outside .sdata/.sbss: never $gp. Drop the size so GNU as
            # uses lui, as ASPSX did for an `extern` defined elsewhere.
            self.lines[i] = ""
            continue
        if match and 0 < int(match.group(2)) <= self.sdata_limit:
            self.sdata_entries.setdefault(match.group(1), int(match.group(2)))


MaspsxProcessor.preprocess_lines = preprocess_lines

# maspsx's expand_load_immediate falls through to a TODO for li $reg,0 and
# emits "ori $reg,0", dropping the source register: GNU as then reads rs=$reg
# instead of $zero and encodes 0x34E70000 where retail has 0x34070000.
# Emit the correct form here; see kb/psx/matching.md (2026-10-03).
_expand_load_immediate = maspsx.expand_load_immediate


def expand_load_immediate(line):
    match = re.match(r"li\s+(\$[0-9A-z]+),\s?(-?[x0-9a-fA-F]+)", line)
    if match and int(match.group(2), 0) == 0:
        return [f"ori\t{match.group(1)},$zero,0"]
    return _expand_load_immediate(line)


maspsx.expand_load_immediate = expand_load_immediate
sys.argv[0] = str(MASPSX / "maspsx.py")
runpy.run_path(sys.argv[0], run_name="__main__")
