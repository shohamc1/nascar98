#!/usr/bin/env python3
"""Write objdiff.json: one unit per code object, plus the asm data objects.

objdiff compares build/<obj> (your C) against expected/build/<obj>, the copy
`make expected` takes from a matching build. Functions still in asm carry a
`.NON_MATCHING` symbol from splat, so objdiff counts them as unmatched.

Usage: python3 tools/objdiff_config.py > objdiff.json
"""

import json
import pathlib
import sys

# Objects that hold code, by progress category: the Psy-Q libraries are
# the files under src/psxsdk/.
SDK_DIR = "psxsdk"

# Data-only objects, tracked like sotn-decomp's asm data units. No .bss:
# objdiff counts it as matched because it has no bytes to compare. The
# sdata range and several SDK data blocks are decompiled into C; the
# data_*.data.s units hold the interleaved ranges still in asm.
DATA_S = ["asm/data/data.data.s"]


def unit(src: pathlib.Path, category: str | None) -> dict:
    obj = f"build/{src}.o"
    return {
        "name": str(src.with_suffix("")),
        "target_path": f"expected/{obj}",
        "base_path": obj,
        "metadata": {
            "source_path": str(src),
            "progress_categories": [category] if category else [],
            "auto_generated": src.suffix == ".s",
        },
    }


def main() -> None:
    units = [
        unit(p, "sdk" if SDK_DIR in p.parts else "game")
        for p in sorted(pathlib.Path("src").rglob("*.c"))
    ] + [unit(pathlib.Path(s), None) for s in DATA_S]
    config = {
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "custom_make": "make",
        "build_target": False,
        "watch_patterns": ["*.c", "*.h", "*.s"],
        "progress_categories": [
            {"id": "game", "name": "Game"},
            {"id": "sdk", "name": "Psy-Q SDK"},
        ],
        "units": units,
    }
    json.dump(config, sys.stdout, indent=2)
    sys.stdout.write("\n")


if __name__ == "__main__":
    main()
