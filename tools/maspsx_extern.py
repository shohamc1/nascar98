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

from maspsx import MaspsxProcessor  # noqa: E402

_preprocess_lines = MaspsxProcessor.preprocess_lines


def preprocess_lines(self):
    _preprocess_lines(self)
    for line in self.lines:
        match = re.match(r"\.extern\s+([^,\s]+)\s*,\s*([0-9]+)", line)
        if match and 0 < int(match.group(2)) <= self.sdata_limit:
            self.sdata_entries.setdefault(match.group(1), int(match.group(2)))


MaspsxProcessor.preprocess_lines = preprocess_lines
sys.argv[0] = str(MASPSX / "maspsx.py")
runpy.run_path(sys.argv[0], run_name="__main__")
