"""Tests for tools/port_filter.py. Fixtures use invented names only."""

import pathlib
import subprocess
import sys
import tempfile
import unittest

import port_filter as pf

ROOT = pathlib.Path(__file__).resolve().parent.parent


class ReadInputs(unittest.TestCase):
    def test_read_defsyms(self) -> None:
        text = (
            "LDFLAGS := -T x \\\n"
            "    --defsym=gDanaAbsolute=gDana \\\n"
            "    --defsym=D_80001004=gQuinnTable+4 \\\n"
            "    --defsym=_spu_attr=D_80002008-4 \\\n"
        )
        self.assertEqual(
            pf.read_defsyms(text),
            {
                "gDanaAbsolute": ("gDana", 0),
                "D_80001004": ("gQuinnTable", 4),
                "_spu_attr": ("D_80002008", -4),
            },
        )

    def test_harvest_aliases(self) -> None:
        text = (
            'asm(".globl gDanaW\\ngDanaW = gDana");\n'
            '__asm__("gQuinn.MainLoop = gQuinn\\n"\n'
            '        "gAvery.MainLoop2 = gAvery\\n");\n'
        )
        self.assertEqual(
            pf.harvest_aliases(text),
            {
                "gDanaW": ("gDana", 0),
                "gQuinn.MainLoop": ("gQuinn", 0),
                "gAvery.MainLoop2": ("gAvery", 0),
            },
        )

    def test_read_absolutes(self) -> None:
        text = "D_1F800004 = 0x1F800004;\nD_801F3FF8 = 0x801F3FF8;\n"
        self.assertEqual(
            pf.read_absolutes(text),
            {"D_1F800004": 0x1F800004, "D_801F3FF8": 0x801F3FF8},
        )

    def test_read_symbols(self) -> None:
        text = (
            "8008ca04 0000004c R D_8008CA04\n"
            "8007400c 00000098 T __divdi3\n"
            "8008c0ac t __gnu_compiled_c\n"
        )
        self.assertEqual(
            pf.read_symbols(text),
            {"D_8008CA04": (0x8008CA04, 0x4C), "__divdi3": (0x8007400C, 0x98)},
        )


class Resolve(unittest.TestCase):
    def test_resolve_chain(self) -> None:
        aliases = {"A": ("B", 0), "B": ("C.NON_MATCHING", 0)}
        self.assertEqual(pf.resolve("A", aliases), ("C", 0))

    def test_resolve_strips_any_suffix(self) -> None:
        self.assertEqual(pf.resolve("gDana.MainLoop7", {}), ("gDana", 0))

    def test_resolve_adds_offsets(self) -> None:
        aliases = {"A": ("B", 4), "B": ("C", -2)}
        self.assertEqual(pf.resolve("A", aliases), ("C", 2))

    def test_resolve_unknown_name(self) -> None:
        self.assertEqual(pf.resolve("gQuinn", {}), ("gQuinn", 0))


class PlaceAbsolute(unittest.TestCase):
    SYMBOLS = {"gDanaTable": (0x8008CA04, 0x4C)}
    RANGES = [(0x80090DC8, 0x800A2CE0)]
    IMAGE = (0x80010000, 0x800CEFE0)

    def place(self, address: int) -> object:
        return pf.place_absolute(address, self.SYMBOLS, self.RANGES, self.IMAGE)

    def test_place_inside_data(self) -> None:
        self.assertIsNone(self.place(0x80091000))

    def test_place_in_rodata(self) -> None:
        self.assertEqual(self.place(0x8008CA18), ("gDanaTable", 0x14))

    def test_place_fixed_ram(self) -> None:
        self.assertEqual(self.place(0x801F3FF8), 0x801F3FF8)

    def test_place_scratchpad(self) -> None:
        self.assertEqual(self.place(0x1F800004), 0x1F800004)

    def test_place_unowned_image_address(self) -> None:
        with self.assertRaises(ValueError):
            self.place(0x8008CA60)


class FilterSource(unittest.TestCase):
    def run_filter(
        self,
        text: str,
        aliases: dict[str, tuple[str, int]] | None = None,
        absolutes: dict[str, tuple[str, int] | int] | None = None,
    ) -> str:
        return pf.filter_source(text, aliases or {}, absolutes or {})

    def test_strip_register_pin(self) -> None:
        text = (
            '    register u8 *rec asm("a1");\n'
            '    register s32 n __asm__("$17") = 0;\n'
            "    register u8 *src asm(srcReg) = (src);\n"
        )
        self.assertEqual(
            self.run_filter(text),
            "    register u8 *rec;\n"
            "    register s32 n = 0;\n"
            "    register u8 *src = (src);\n",
        )

    def test_map_existing_label(self) -> None:
        text = 'extern Car *gDanaLui asm("gDanaAbsolute");\n'
        out = self.run_filter(text, {"gDanaAbsolute": ("gDana", 0)})
        self.assertEqual(out, 'extern Car *gDanaLui __asm__("gDana");\n')

    def test_map_non_matching_label(self) -> None:
        text = 'extern u8 gQuinnNM asm("gQuinn.NON_MATCHING");\n'
        out = self.run_filter(text)
        self.assertEqual(out, 'extern u8 gQuinnNM __asm__("gQuinn");\n')

    def test_label_alias_declaration(self) -> None:
        text = "extern s32 gDanaAbs[];\nvoid DanaDrawW(s32 x);\n"
        aliases = {"gDanaAbs": ("gDana", 0), "DanaDrawW": ("DanaDraw", 0)}
        self.assertEqual(
            self.run_filter(text, aliases),
            'extern s32 gDanaAbs[] __asm__("gDana");\n'
            'void DanaDrawW(s32 x) __asm__("DanaDraw");\n',
        )

    def test_alias_use_untouched(self) -> None:
        text = "    gDanaAbs[0] = 1;\n"
        self.assertEqual(self.run_filter(text, {"gDanaAbs": ("gDana", 0)}), text)

    def test_main_label_kept(self) -> None:
        text = 'int main(void) __asm__("func_80012108");\n'
        self.assertEqual(self.run_filter(text), text)

    def test_absolute_base_offset(self) -> None:
        text = "extern u16 D_8008CA18[];\n"
        out = self.run_filter(text, absolutes={"D_8008CA18": ("gDanaTable", 0x14)})
        self.assertEqual(
            out,
            'extern u8 D_8008CA18_base[] __asm__("gDanaTable");\n'
            "#define D_8008CA18 ((u16 *)(D_8008CA18_base + 0x14))\n",
        )

    def test_absolute_address(self) -> None:
        text = "    extern u32 D_801F3FF8[];\n"
        out = self.run_filter(text, absolutes={"D_801F3FF8": 0x801F3FF8})
        self.assertEqual(out, "    #define D_801F3FF8 ((u32 *)0x801F3FF8)\n")

    def test_absolute_comma_list(self) -> None:
        text = "extern u8 D_1F800004[], gDana[], D_1F800008[];\n"
        absolutes = {"D_1F800004": 0x1F800004, "D_1F800008": 0x1F800008}
        self.assertEqual(
            self.run_filter(text, absolutes=absolutes),
            "extern u8 gDana[];\n"
            "#define D_1F800004 ((u8 *)0x1F800004)\n"
            "#define D_1F800008 ((u8 *)0x1F800008)\n",
        )

    def test_alias_with_offset_becomes_define(self) -> None:
        text = "extern u8 gQuinnTail[];\n"
        out = self.run_filter(text, {"gQuinnTail": ("gQuinn", 4)})
        self.assertEqual(
            out,
            'extern u8 gQuinnTail_base[] __asm__("gQuinn");\n'
            "#define gQuinnTail ((u8 *)(gQuinnTail_base + 0x4))\n",
        )

    def test_drop_file_scope_asm(self) -> None:
        text = (
            "s32 gDana;\n"
            'asm(".globl gDanaW\\ngDanaW = gDana");\n'
            '__asm__("gQuinn.MainLoop = gQuinn\\n"\n'
            '        "gAvery.MainLoop = gAvery\\n");\n'
            'asm(".rdata\\n.long 0\\n.text");\n'
            "s32 gQuinn;\n"
        )
        self.assertEqual(self.run_filter(text), "s32 gDana;\ns32 gQuinn;\n")

    def test_function_asm_kept(self) -> None:
        text = 'void Dana(void) {\n    asm("" : : : "memory");\n}\n'
        self.assertEqual(self.run_filter(text), text)

    def test_drop_padding_asm_in_function(self) -> None:
        text = (
            "s32 Dana(void) {\n"
            '    asm(".rdata\\n.long 0\\n.text");\n'
            '    __asm__ volatile(".section .rodata\\n"\n'
            '                     ".word 0\\n"\n'
            '                     ".section .text");\n'
            "    return 1;\n"
            "}\n"
        )
        self.assertEqual(self.run_filter(text), "s32 Dana(void) {\n    return 1;\n}\n")

    def test_drop_gp_write(self) -> None:
        text = (
            "void Dana(s32 oldGp) {\n"
            '    asm("addu $gp, %0, $zero" : : "r"(oldGp));\n'
            '    asm("addu $gp, $a0, $zero");\n'
            "}\n"
        )
        self.assertEqual(self.run_filter(text), "void Dana(s32 oldGp) {\n}\n")

    def test_gp_relative_store(self) -> None:
        out = self.run_filter('    asm volatile("sw\\t$zero, %gp_rel(gDana)($gp)");\n')
        self.assertIn("PORT_STORE(u32, (u32)port_sym_gDana, 0u);", out)

    def test_drop_nop_only(self) -> None:
        text = 'void Dana(void) {\n    asm volatile(".set noreorder\\nnop\\n.set reorder");\n}\n'
        self.assertEqual(self.run_filter(text), "void Dana(void) {\n}\n")

    def test_gte_command(self) -> None:
        text = '    asm volatile(\n        ".set\\tnoreorder\\n\\tnop\\n\\tnop\\n\\trtpt\\n\\t.set\\treorder");\n'
        out = self.run_filter(text)
        self.assertIn("PortGteCommand(0x4a280030u);", out)
        self.assertNotIn("asm", out)

    def test_gte_moves(self) -> None:
        cases = {
            '    asm volatile("mfc2 %0, $7\\n\\tnop" : "=r"(otz) : "0"(otz));\n': "PortGteRead(7)",
            '    asm volatile("mtc2 %0, $8" : : "r"(ir0));\n': "PortGteWrite(8, port_o0)",
            '    asm("cfc2 %1, $31" : "=r"(a), "=r"(flag));\n': "PortGteReadControl(31)",
            '    asm("lwc2 $0, 0x8(%0)" : : "r"(v));\n': "PortGteWrite(0, PORT_LOAD(u32, (port_o0 + (u32)8)))",
        }
        for text, call in cases.items():
            out = self.run_filter(text)
            self.assertIn(call, out)
            self.assertNotIn("asm", out)

    def test_gte_in_macro(self) -> None:
        text = (
            "#define DanaStore(a, b) \\\n"
            '    asm volatile("swc2 $17, 0(%0)\\n\\tswc2 $18, 0(%1)" \\\n'
            '                 : \\\n'
            '                 : "r"(a), "r"(b) \\\n'
            '                 : "memory")\n'
            "\n"
            "s32 gDana;\n"
        )
        first, second, *rest = self.run_filter(text).split("\n")
        self.assertEqual(first, "#define DanaStore(a, b) \\")
        self.assertTrue(second.startswith("    { ") and second.endswith(" }"))
        self.assertIn("PortGteRead(17)", second)
        self.assertEqual(rest, ["", "s32 gDana;", ""])

    def test_asm_symbol_extern(self) -> None:
        out = self.run_filter('    asm("la %0, gDanaTable" : "=r"(p));\n')
        self.assertIn('extern u8 port_sym_gDanaTable[] __asm__("gDanaTable");', out)
        self.assertIn("PORT_OUT(p, port_o0);", out)

    def test_asm_symbol_alias(self) -> None:
        out = self.run_filter('    asm("la %0, gDanaAbs" : "=r"(p));\n', {"gDanaAbs": ("gDana", 0)})
        self.assertIn('__asm__("gDana")', out)

    def test_asm_symbol_offset_alias(self) -> None:
        out = self.run_filter('    asm("la %0, gDanaTail" : "=r"(p));\n', {"gDanaTail": ("gDana", 4)})
        self.assertIn("((u32)port_sym_gDana + 0x4)", out)

    def test_asm_symbol_absolute(self) -> None:
        out = self.run_filter('    asm("la %0, D_1F800004" : "=r"(p));\n', absolutes={"D_1F800004": 0x1F800004})
        self.assertIn("(u32)0x1F800004", out)
        self.assertNotIn("extern", out)

    def test_asm_symbol_function(self) -> None:
        out = pf.filter_source('    asm("la %0, DanaStep" : "=r"(p));\n', {}, {}, {"DanaStep"})
        self.assertIn('extern void port_sym_DanaStep(void) __asm__("DanaStep");', out)

    def test_gte_hard_register_kept(self) -> None:
        text = '    asm volatile("mfc2 $8, $7");\n'
        self.assertEqual(self.run_filter(text), text)

    def test_instruction_asm_in_function_kept(self) -> None:
        text = 'void Dana(void) {\n    asm(".set noreorder\\naddu $2, $3, $4\\n.set reorder");\n}\n'
        self.assertEqual(self.run_filter(text), text)

    def test_barrier_register_clobbers_dropped(self) -> None:
        text = (
            '    asm("" : "=r"(x) : "0"(y) : "v0");\n'
            '    asm volatile("" : : "r"(z) : "$2", "memory", "a1");\n'
            '    asm("" : : : "lo", "hi");\n'
        )
        self.assertEqual(
            self.run_filter(text),
            '    asm("" : "=r"(x) : "0"(y));\n'
            '    asm volatile("" : : "r"(z) : "memory");\n'
            '    asm("" : :);\n',
        )

    def test_instruction_clobbers_kept(self) -> None:
        text = '    asm("addu $2, $3, $4" : : : "v0");\n'
        self.assertEqual(self.run_filter(text), text)

    def test_drop_maspsx_hack(self) -> None:
        text = (
            "s32 gDana;\n"
            "void __maspsx_include_asm_hack_pad_80001000(void) {\n"
            '    __asm__(".section .rodata # maspsx-keep\\n"\n'
            '            "    .word 0 # maspsx-keep\\n");\n'
            "}\n"
            "s32 gQuinn;\n"
        )
        self.assertEqual(self.run_filter(text), "s32 gDana;\ns32 gQuinn;\n")

    def test_filter_is_idempotent(self) -> None:
        text = (
            '    register u8 *rec asm("a1");\n'
            'extern Car *gDanaLui asm("gDanaAbsolute");\n'
            "extern u16 D_8008CA18[];\n"
            'asm(".globl gDanaW\\ngDanaW = gDana");\n'
        )
        aliases = {"gDanaAbsolute": ("gDana", 0)}
        absolutes = {"D_8008CA18": ("gDanaTable", 0x14)}
        once = self.run_filter(text, aliases, absolutes)
        self.assertEqual(self.run_filter(once, aliases, absolutes), once)


class ReplaceFunctions(unittest.TestCase):
    TEXT = (
        "s32 gDana;\n"
        "\n"
        "/* Dana. */\n"
        "s32 DanaStep(s32 x) {\n"
        "    if (x) {\n"
        '        asm("addu %0, %0, 1" : "+r"(x));\n'
        "    }\n"
        '    return x + "}"[0];\n'
        "}\n"
        "\n"
        "void QuinnStep(void) {\n"
        "}\n"
    )

    def test_replace_function(self) -> None:
        native = "s32 DanaStep(s32 x) {\n    return x + 1;\n}\n"
        out = pf.replace_functions(self.TEXT, {"DanaStep": native})
        self.assertEqual(
            out,
            "s32 gDana;\n\n/* Dana. */\n" + native + "\nvoid QuinnStep(void) {\n}\n",
        )

    def test_prototype_untouched(self) -> None:
        text = "s32 DanaStep(s32 x);\n" + self.TEXT
        out = pf.replace_functions(text, {"DanaStep": "s32 DanaStep(s32 x) {}\n"})
        self.assertTrue(out.startswith("s32 DanaStep(s32 x);\n"))

    def test_override_for_other_file_ignored(self) -> None:
        self.assertEqual(pf.replace_functions(self.TEXT, {"AveryStep": "x"}), self.TEXT)


class Cli(unittest.TestCase):
    def test_cli_writes_filtered_files(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            d = pathlib.Path(tmp)
            (d / "Makefile").write_text("    --defsym=gDanaAbsolute=gDana \\\n")
            (d / "syms.txt").write_text("8008ca04 0000004c R gDanaTable\n")
            (d / "defined.txt").write_text("00000000 D gAveryCount\n")
            (d / "abs.txt").write_text(
                "D_801F3FF8 = 0x801F3FF8;\ngAveryCount = 0x800A33AC;\n"
            )
            (d / "a.c").write_text(
                'asm(".globl gQuinnW\\ngQuinnW = gQuinn");\n'
                'extern s32 gDanaLui asm("gDanaAbsolute");\n'
            )
            (d / "b.c").write_text(
                "extern s32 gQuinnW;\nextern u32 D_801F3FF8[];\n"
                "extern u32 gAveryCount[];\n"
            )
            out = d / "out"
            subprocess.run(
                [
                    sys.executable,
                    str(ROOT / "tools" / "port_filter.py"),
                    "--makefile", str(d / "Makefile"),
                    "--absolutes", str(d / "abs.txt"),
                    "--symbols", str(d / "syms.txt"),
                    "--defined", str(d / "defined.txt"),
                    "--data-range", "0x80090DC8:0x800A2CE0",
                    "--image", "0x80010000:0x800CEFE0",
                    str(d / "a.c"), str(d / "b.c"), str(out),
                ],
                check=True,
            )
            self.assertEqual(
                (out / "a.c").read_text(),
                'extern s32 gDanaLui __asm__("gDana");\n',
            )
            self.assertEqual(
                (out / "b.c").read_text(),
                'extern s32 gQuinnW __asm__("gQuinn");\n'
                "#define D_801F3FF8 ((u32 *)0x801F3FF8)\n"
                "extern u32 gAveryCount[];\n",
            )

    def test_cli_filters_native_bodies(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            d = pathlib.Path(tmp)
            for name in ("Makefile", "abs.txt", "syms.txt", "defined.txt"):
                (d / name).write_text("")
            (d / "native").mkdir()
            (d / "native" / "DanaStep.c").write_text(
                'void DanaStep(void) {\n    register s32 x asm("a0");\n}\n'
            )
            (d / "a.c").write_text("void DanaStep(void) {\n}\n")
            subprocess.run(
                [
                    sys.executable,
                    str(ROOT / "tools" / "port_filter.py"),
                    "--makefile", str(d / "Makefile"),
                    "--absolutes", str(d / "abs.txt"),
                    "--symbols", str(d / "syms.txt"),
                    "--defined", str(d / "defined.txt"),
                    "--image", "0x80010000:0x800CEFE0",
                    "--native-dir", str(d / "native"),
                    str(d / "a.c"), str(d / "out"),
                ],
                check=True,
            )
            self.assertEqual(
                (d / "out" / "a.c").read_text(),
                "void DanaStep(void) {\n    register s32 x;\n}\n",
            )

    def test_cli_rejects_stale_native(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            d = pathlib.Path(tmp)
            for name in ("Makefile", "abs.txt", "syms.txt", "defined.txt"):
                (d / name).write_text("")
            (d / "native").mkdir()
            (d / "native" / "AveryStep.c").write_text("void AveryStep(void) {}\n")
            (d / "a.c").write_text("void DanaStep(void) {\n}\n")
            run = subprocess.run(
                [
                    sys.executable,
                    str(ROOT / "tools" / "port_filter.py"),
                    "--makefile", str(d / "Makefile"),
                    "--absolutes", str(d / "abs.txt"),
                    "--symbols", str(d / "syms.txt"),
                    "--defined", str(d / "defined.txt"),
                    "--image", "0x80010000:0x800CEFE0",
                    "--native-dir", str(d / "native"),
                    str(d / "a.c"), str(d / "out"),
                ],
                capture_output=True,
                text=True,
            )
            self.assertNotEqual(run.returncode, 0)
            self.assertIn("AveryStep", run.stderr)


if __name__ == "__main__":
    unittest.main()
