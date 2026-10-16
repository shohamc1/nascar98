#!/usr/bin/env python3
"""Emit C constants for fixed RAM addresses named in the Splat config.

The fixed_address annotation selects addresses that the original C used as
constants. Ordinary symbols remain extern declarations and linker symbols.
"""

import pathlib
import re
import sys


def fixed_addresses(text):
    return re.findall(
        r"^([A-Z][A-Z0-9_]*)\s*=\s*(0x[0-9A-Fa-f]+);\s*// (?:absolute:True\s+)?fixed_address(?:\s+(?:allow_duplicated|absolute):True)*\s*$",
        text,
        re.MULTILINE,
    )


def absolute_addresses(text):
    return re.findall(
        r"^(\w+)\s*=\s*(0x[0-9A-Fa-f]+);\s*//[^\n]*\babsolute:True\b[^\n]*$",
        text,
        re.MULTILINE,
    )


if __name__ == "__main__":
    assert fixed_addresses("HEAP_LIMIT = 0x1234; // fixed_address\n") == [
        ("HEAP_LIMIT", "0x1234")
    ]
    assert fixed_addresses("gBuffer = 0x1234;\n") == []
    assert fixed_addresses(
        "SCRATCHPAD_BASE = 0x1F800000; // fixed_address allow_duplicated:True\n"
    ) == [("SCRATCHPAD_BASE", "0x1F800000")]
    assert fixed_addresses(
        "gScratchpad = 0x1F800000; // allow_duplicated:True CPU scratchpad RAM\n"
    ) == []
    assert fixed_addresses(
        "HEAP_LIMIT = 0x1234; // absolute:True fixed_address\n"
    ) == [("HEAP_LIMIT", "0x1234")]
    assert fixed_addresses(
        "SCRATCHPAD_BASE = 0x1F800000; // fixed_address allow_duplicated:True absolute:True\n"
    ) == [("SCRATCHPAD_BASE", "0x1F800000")]
    assert absolute_addresses(
        "gScratchpad = 0x1F800000; // absolute:True allow_duplicated:True\n"
    ) == [("gScratchpad", "0x1F800000")]
    text = pathlib.Path(sys.argv[-1]).read_text()
    if sys.argv[1] == "--ld":
        for name, address in absolute_addresses(text):
            print("%s = %s;" % (name, address))
    else:
        for name, address in fixed_addresses(text):
            print("#define %s ((u32)%s)" % (name, address))
