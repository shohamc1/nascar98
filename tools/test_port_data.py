"""Tests for tools/port_data.py. Fixtures are invented splat lines."""

import os
import pathlib
import shutil
import subprocess
import tempfile
import unittest

import port_data as pd

DATA = """.include "macro.inc"

.section .data, "wa"

nonmatching D_80001000

dlabel D_80001000
    /* 100 80001000 */ .short 0x0190
    /* 102 80001002 */ .byte 0x7F
enddlabel D_80001000
.align 2
nonmatching gDanaNames

dlabel gDanaNames
    /* 104 80001004 */ .word gQuinnText
    /* 108 80001008 */ .word DanaStep
    /* 10C 8000100C */ .word 0x80001000
enddlabel gDanaNames

dlabel gDanaText
    /* 110 80001010 */ .asciz "Hi\\n\\"x\\""
    /* 4869 */
.align 2
dlabel D_80001018
    /* 118 80001018 */ .word D_80001000
"""

BSS = """.section .bss, "wa"

nonmatching D_80002000, 0x4

dlabel D_80002000
    /* 80002000 */ .space 0x04

dlabel D_80002004
    /* 80002004 */ .space 0x10
"""

OBJDUMP = """Type[3]:
 - type[0] () -> nil
 - type[1] (i32) -> i32
 - type[2] (i32, i32) -> nil
Import[2]:
 - memory[0] pages: initial=0 <- env.__linear_memory
 - func[0] sig=2 <AveryDraw> <- env.AveryDraw
Function[2]:
 - func[1] sig=1 <DanaStep>
 - func[2] sig=0 <QuinnStep>
"""

WASM_CC = os.environ.get("WASM_CC") or shutil.which("clang")
BREW_CLANG = pathlib.Path("/opt/homebrew/opt/llvm/bin/clang")
if BREW_CLANG.exists():
    WASM_CC = str(BREW_CLANG)


def plain_symbol(name: str) -> str:
    return name


class Parse(unittest.TestCase):
    def test_parse_each_directive(self) -> None:
        items = pd.parse_splat(DATA)
        kinds = [(i.kind, i.address) for i in items]
        self.assertEqual(
            kinds,
            [
                ("label", 0x80001000),
                ("short", 0x80001000),
                ("byte", 0x80001002),
                ("label", 0x80001004),
                ("word", 0x80001004),
                ("word", 0x80001008),
                ("word", 0x8000100C),
                ("label", 0x80001010),
                ("asciz", 0x80001010),
                ("label", 0x80001018),
                ("word", 0x80001018),
            ],
        )
        self.assertEqual(items[1].value, 0x190)
        self.assertEqual(items[4].value, "gQuinnText")
        self.assertEqual(items[6].value, 0x80001000)
        self.assertEqual(items[8].value, b'Hi\n"x"\x00')

    def test_bss_space(self) -> None:
        items = pd.parse_splat(BSS)
        self.assertEqual(
            [(i.kind, i.value, i.address) for i in items],
            [
                ("label", "D_80002000", 0x80002000),
                ("space", 4, 0x80002000),
                ("label", "D_80002004", 0x80002004),
                ("space", 0x10, 0x80002004),
            ],
        )

    def test_read_signatures(self) -> None:
        self.assertEqual(
            pd.read_signatures(OBJDUMP),
            {"DanaStep": "(i32) -> (i32)", "QuinnStep": "() -> ()", "AveryDraw": "(i32, i32) -> ()"},
        )

    def test_read_signatures_prefers_definitions(self) -> None:
        dump = OBJDUMP.replace("func[1] sig=1 <DanaStep>", "func[1] sig=1 <AveryDraw>")
        self.assertEqual(pd.read_signatures(dump)["AveryDraw"], "(i32) -> (i32)")


class Emit(unittest.TestCase):
    SIGS = {"DanaStep": "(i32) -> (i32)"}

    def emit(self, text: str, section: str = ".data.port", extra: dict[int, str] | None = None, **kw) -> str:
        return pd.emit_wasm(pd.parse_splat(text), section, extra or {}, self.SIGS, plain_symbol, **kw)

    def test_layout_by_address(self) -> None:
        out = self.emit(DATA)
        self.assertIn("D_80001000:\n\t.int16 400\n\t.int8 127\n\t.skip 1\n", out)
        self.assertIn("\t.size D_80001000, 4\n", out)

    def test_word_symbol_reloc(self) -> None:
        self.assertIn("\t.int32 gQuinnText\n", self.emit(DATA))

    def test_word_number_kept(self) -> None:
        self.assertIn("\t.int32 2147487744\n", self.emit(DATA))

    def test_name_pointers(self) -> None:
        items = pd.parse_splat(DATA)
        named = pd.name_pointers(items, {0x80001000: "sQuinnTitle"}, [(0x80002000, 0x80003000)])
        self.assertEqual([i.value for i in named if i.address == 0x8000100C], ["sQuinnTitle"])

    def test_name_pointers_skips_data_ranges(self) -> None:
        items = pd.parse_splat(DATA)
        named = pd.name_pointers(items, {0x80001000: "sQuinnTitle"}, [(0x80001000, 0x80002000)])
        self.assertEqual([i.value for i in named if i.address == 0x8000100C], [0x80001000])

    def test_function_gets_functype(self) -> None:
        out = self.emit(DATA)
        self.assertIn("\t.functype DanaStep (i32) -> (i32)\n", out)
        self.assertIn("\t.int32 DanaStep\n", out)

    def test_asciz_bytes_and_padding(self) -> None:
        out = self.emit(DATA)
        self.assertIn("gDanaText:\n\t.int8 72\n\t.int8 105\n\t.int8 10\n", out)
        self.assertIn("\t.size gDanaText, 8\n", out)

    def test_extra_label_mid_object(self) -> None:
        out = self.emit(DATA, extra={0x80001008: "D_80001008"})
        self.assertIn("\t.globl D_80001008\nD_80001008:\n", out)
        self.assertIn("\t.size gDanaNames, 4\n", out)

    def test_extra_label_on_existing_label_ignored(self) -> None:
        out = self.emit(DATA, extra={0x80001004: "D_80001004"})
        self.assertNotIn("D_80001004", out)

    def test_bss_skips(self) -> None:
        out = self.emit(BSS, ".bss.port")
        self.assertIn('\t.section .bss.port,"",@\n', out)
        self.assertIn("D_80002004:\n\t.skip 16\n", out)

    def test_zeroed_function(self) -> None:
        text = DATA.replace(".word DanaStep", ".word _avery_internal")
        out = self.emit(text, zero={"_avery_internal"})
        self.assertNotIn("_avery_internal", out)
        self.assertIn("\t.int32 0\n", out)

    def test_unknown_function_rejected(self) -> None:
        text = DATA.replace(".word DanaStep", ".word QuinnStep")
        with self.assertRaises(ValueError):
            self.emit(text, functions={"QuinnStep"})

    @unittest.skipUnless(WASM_CC, "no wasm clang")
    def test_round_trip_assembles(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            src = pathlib.Path(tmp) / "d.s"
            src.write_text(self.emit(DATA) + self.emit(BSS, ".bss.port"))
            run = subprocess.run(
                [WASM_CC, "--target=wasm32", "-c", str(src), "-o", str(src.with_suffix(".o"))],
                capture_output=True,
                text=True,
            )
            self.assertEqual(run.returncode, 0, run.stderr)


if __name__ == "__main__":
    unittest.main()
