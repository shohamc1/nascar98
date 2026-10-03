#!/usr/bin/env python3
"""Write objdiff.json: one unit per object that holds game or SDK code.

objdiff compares build/<obj> (your C) against expected/build/<obj>, the copy
`make expected` takes from a matching build. Functions still in asm carry a
`.NON_MATCHING` symbol from splat, so objdiff counts them as unmatched.

Usage: python3 tools/objdiff_config.py > objdiff.json
"""

import json
import pathlib
import sys

# Objects that hold code, by progress category. Data-only objects
# (asm/data/*) aren't units: decomp.dev tracks code.
SDK_C = "src/psxsdk.c"


def unit(src: pathlib.Path, category: str) -> dict:
    obj = f"build/{src}.o"
    return {
        "name": str(src.with_suffix("")),
        "target_path": f"expected/{obj}",
        "base_path": obj,
        "metadata": {
            "source_path": str(src),
            "progress_categories": [category],
            "auto_generated": src.suffix == ".s",
        },
    }


def main() -> None:
    units = [
        unit(p, "sdk" if str(p) == SDK_C else "game")
        for p in sorted(pathlib.Path("src").rglob("*.c"))
    ]
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
