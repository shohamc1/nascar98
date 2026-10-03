#!/usr/bin/env python3
"""Small regression check for ambiguous Psy-Q wrapper signatures."""

import contextlib
import io
import struct
import subprocess
import sys
from pathlib import Path

import psyq_sigs


def run(matches, text, vram):
    original = psyq_sigs.matches
    psyq_sigs.matches = lambda _text, _ver: iter(matches)
    output = io.StringIO()
    try:
        with contextlib.redirect_stdout(output):
            psyq_sigs.symbols(text, vram, ["test"])
    finally:
        psyq_sigs.matches = original
    return output.getvalue()


def main():
    vram = 0x80010000
    text = bytearray(0x100)
    target = vram + 0x80
    struct.pack_into("<I", text, 0x28, 0x0C000000 | ((target >> 2) & 0x03FFFFFF))
    candidates = [
        ("LIBSPU.LIB", "S_R.OBJ", 0, 0x60, [{"name": "SpuRead", "offset": 0}]),
        ("LIBSPU.LIB", "S_W.OBJ", 0, 0x60, [{"name": "SpuWrite", "offset": 0}]),
        ("LIBSPU.LIB", "SPU_WRITE.OBJ", 0x80, 0x20, [{"name": "_spu_write", "offset": 0}]),
        ("LIBSPU.LIB", "SPU_READ.OBJ", 0xA0, 0x20, [{"name": "_spu_read", "offset": 0}]),
    ]
    output = run(candidates, text, vram)
    assert "SpuWrite = 0x80010000" in output
    assert "SpuRead = 0x80010000" not in output

    target = vram + 0xA0
    struct.pack_into("<I", text, 0x28, 0x0C000000 | ((target >> 2) & 0x03FFFFFF))
    output = run(candidates, text, vram)
    assert "SpuRead = 0x80010000" in output
    assert "SpuWrite = 0x80010000" not in output

    candidates = candidates[:2]
    output = run(candidates, text, vram)
    assert "SpuRead = 0x80010000" not in output
    assert "SpuWrite = 0x80010000" not in output

    aliases = [
        ("LIBAPI.LIB", "PADINIT.OBJ", 0, 12, [{"name": "InitPAD", "offset": 0}]),
        ("LIBAPI.LIB", "PADINIT.OBJ", 0, 12, [{"name": "InitPAD2", "offset": 0}]),
    ]
    output = run(aliases, text, vram)
    assert "InitPAD = 0x80010000" in output
    assert "InitPAD2 = 0x80010000" not in output

    exe = Path("build/SLUS_005.21")
    output = subprocess.check_output(
        [sys.executable, "tools/psyq_sigs.py", str(exe), "--symbols", "350", "3610", "3611"],
        text=True,
    )
    assert "SpuWrite = 0x8008AE80;" in output
    assert "SpuRead = 0x8008AE80;" not in output


if __name__ == "__main__":
    main()
