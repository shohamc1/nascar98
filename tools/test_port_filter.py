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

    def test_static_string_made_global(self) -> None:
        text = 'static const char sDanaTitle[] = "DANA*";\n'
        self.assertEqual(self.run_filter(text), '__attribute__((used)) const char sDanaTitle[] = "DANA*";\n')

    def test_empty_loop_polls(self) -> None:
        text = (
            "    while (gDanaFlag == 0) {\n    }\n"
            "    do {\n\n    } while (QuinnBusy() & 0xFF);\n"
            "    while (gDanaFlag) {\n        x++;\n    }\n"
            "    do {\n    } while (0);\n"
        )
        self.assertEqual(
            self.run_filter(text),
            "    while (gDanaFlag == 0) { PortPoll(); }\n"
            "    do { PortPoll(); } while (QuinnBusy() & 0xFF);\n"
            "    while (gDanaFlag) {\n        x++;\n    }\n"
            "    do {\n    } while (0);\n",  # a scheduling barrier, not a wait
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

    def test_maspsx_hack_data_becomes_c(self) -> None:
        text = (
            "void __maspsx_include_asm_hack_gDanaTable(void) {\n"
            '    __asm__(".section .rodata # maspsx-keep \\n"\n'
            '            "dlabel gDanaTable # maspsx-keep\\n"\n'
            '            "    .word 0x00010002 # maspsx-keep\\n"\n'
            '            "    .word 0xFFFB0000 # maspsx-keep\\n"\n'
            '            "dlabel gQuinnTable # maspsx-keep\\n"\n'
            '            "    .word 0x3 # maspsx-keep\\n"\n'
            '            "    .section .text # maspsx-keep\\n");\n'
            "}\n"
        )
        self.assertEqual(
            self.run_filter(text),
            'const u32 port_rodata_gDanaTable[] __asm__("gDanaTable") = {0x00010002, 0xFFFB0000};\n'
            'const u32 port_rodata_gQuinnTable[] __asm__("gQuinnTable") = {0x3};\n',
        )

    def test_offset_label_on_fixed_address(self) -> None:
        text = 'extern u32 gDana[] asm("gScratchpad+4");\nextern u32 *gQuinn[] asm("gScratchpad");\n'
        self.assertEqual(
            self.run_filter(text, absolutes={"gScratchpad": 0x1F800000}),
            "#define gDana ((u32 *)0x1F800004)\n#define gQuinn ((u32 * *)0x1F800000)\n",
        )

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


class NativeBranches(unittest.TestCase):
    def test_keeps_the_native_branch(self) -> None:
        text = (
            "int a;\n"
            "#ifdef NATIVE\n"
            "void DanaStep(void) { PortPoll(); }\n"
            "#if 0\nnested\n#endif\n"
            "#else\n"
            'INCLUDE_ASM("asm/nonmatchings/dana", DanaStep);\n'
            "#endif\n"
            "#ifndef NATIVE\nretail only\n#else\nport only\n#endif\n"
            "#ifdef NON_MATCHING\ndraft\n#else\nstub\n#endif\n"
        )
        self.assertEqual(
            pf.native_branches(text),
            "int a;\n"
            "void DanaStep(void) { PortPoll(); }\n"
            "#if 0\nnested\n#endif\n"
            "port only\n"
            "#ifdef NON_MATCHING\ndraft\n#else\nstub\n#endif\n",
        )


class Prototypes(unittest.TestCase):
    def test_read_returns(self) -> None:
        text = (
            "void DanaStep(s32 x) {\n}\n"
            "u8 *QuinnFind(Face *f,\n              s32 n) {\n    return 0;\n}\n"
            "static void AveryHelp(void) {\n}\n"
            "extern long SdkThing(int);\n"
        )
        self.assertEqual(
            pf.read_returns(text),
            {"DanaStep": "void", "QuinnFind": "u8 *", "SdkThing": "long"},
        )

    def test_read_knr_definition(self) -> None:
        text = "void DanaStep(id, pitch) s8 id;\ns8 pitch;\n{\n}\n"
        self.assertEqual(pf.read_returns(text), {"DanaStep": "void"})
        self.assertEqual(pf.read_params(text), {"DanaStep": ["s8 id", "s8 pitch"]})

    def test_return_table_priority(self) -> None:
        headers = ["s32 DanaStep(void);\nvoid QuinnStep(void);\n"]
        sources = [
            "extern void AveryDraw(void);\nextern void DanaStep(void);\n",
            "s8 QuinnStep(void) {\n}\nextern s32 AveryDraw(void);\n",
        ]
        # Definitions beat headers; headers beat other declarations; the
        # first source declaration of an undefined function wins.
        self.assertEqual(
            pf.return_table(headers, sources), {"DanaStep": "s32", "QuinnStep": "s8", "AveryDraw": "void"}
        )

    def test_repair_types_matches_definition(self) -> None:
        # Two names for one symbol in a file must lower to one IR type, or
        # clang turns the call into a trap: integer widths follow the
        # definition, pointers stay pointers.
        params = {"HudDraw": ["u8 *text", "s32 x", "s32 y", "s8 color"], "Quinn": ["s16 a"], "Avery": ["Car *car"]}
        returns = {"HudDraw": "void", "Quinn": "s8", "Avery": "s32"}
        text = (
            'extern void DanaDraw(s8 *, s16, s16, s8) asm("HudDraw");\n'
            "extern void HudDraw(u8 *, s32, s32, s8);\n"
            "extern s32 Quinn();\n"
            "void Avery(s32);\n"
            "s8 Quinn(s16 a) {\n}\n"
        )
        self.assertEqual(
            pf.repair_types(text, params, returns),
            'extern void DanaDraw(s8 *, s32, s32, s8) asm("HudDraw");\n'
            "extern void HudDraw(u8 *, s32, s32, s8);\n"
            "extern s8 Quinn(s16);\n"
            "s32 Avery(void *);\n"
            "s8 Quinn(s16 a) {\n}\n",
        )

    def test_repair_types_same_file_uses_definition(self) -> None:
        params = {"Dana": ["s32 *mem", "u32 count"]}
        text = (
            'extern void DanaArgs(u8 *, s32) asm("Dana");\n'
            "extern s32 Dana();\ns32 Dana(s32 *mem, u32 count) {\n}\n"
        )
        # An alias under another C name needs only matching IR types.
        self.assertEqual(
            pf.repair_types(text, params, {"Dana": "s32"}),
            'extern s32 DanaArgs(u8 *, u32) asm("Dana");\n'
            "extern s32 Dana(s32 *, u32);\ns32 Dana(s32 *mem, u32 count) {\n}\n",
        )

    def test_read_params_knr_types(self) -> None:
        text = "void DanaStep(id, pitch, count) s8 id;\ns8 pitch;\n{\n}\n"
        self.assertEqual(pf.read_params(text), {"DanaStep": ["s8 id", "s8 pitch", "int count"]})

    def test_read_returns_by_label(self) -> None:
        text = 's8 DanaStepBody(s32 arg0) asm("DanaStep");\ns8 DanaStepBody(s32 arg0) {\n}\n'
        self.assertEqual(pf.read_returns(text), {"DanaStep": "s8"})

    def test_read_params_by_label(self) -> None:
        text = 's8 DanaStepBody(s32 arg0) asm("DanaStep");\ns8 DanaStepBody(s32 arg0) {\n}\n'
        self.assertEqual(pf.read_params(text), {"DanaStep": ["s32 arg0"]})

    def test_repair_declared_return(self) -> None:
        text = "extern void QuinnFind(Face *f, s32 n);\n    extern s32 DanaStep(s32);\n"
        returns = {"QuinnFind": "u8 *", "DanaStep": "void"}
        self.assertEqual(
            pf.repair_prototypes(text, returns),
            "extern u8 *QuinnFind(Face *f, s32 n);\n    extern void DanaStep(s32);\n",
        )

    def test_matching_return_untouched(self) -> None:
        text = "extern s32 *QuinnFind(Face *f, s32 n);\n"
        self.assertEqual(pf.repair_prototypes(text, {"QuinnFind": "u8 *"}), text)

    def test_implicit_void_call_declared(self) -> None:
        text = '#include "common.h"\n\nvoid Avery(void) {\n    DanaStep(1);\n    x = QuinnCount();\n}\n'
        returns = {"DanaStep": "void", "QuinnCount": "s32", "Avery": "void"}
        self.assertEqual(
            pf.repair_prototypes(text, returns),
            '#include "common.h"\nvoid DanaStep();\n\nvoid Avery(void) {\n    DanaStep(1);\n    x = QuinnCount();\n}\n',
        )

    def test_implicit_declared_before_first_code(self) -> None:
        text = '#include "common.h"\n/* x */\n\nvoid Avery(void) {\n    DanaStep(1);\n}\n#include "late.h"\n'
        out = pf.repair_prototypes(text, {"DanaStep": "void", "Avery": "void"})
        self.assertTrue(out.startswith('#include "common.h"\nvoid DanaStep();\n'))

    def test_macro_call_not_declared(self) -> None:
        text = "#define DanaStep(x) Avery2(x)\nvoid Avery(void) {\n    DanaStep(1);\n}\n"
        self.assertEqual(pf.repair_prototypes(text, {"DanaStep": "void", "Avery": "void"}), text)

    def test_header_macro_call_not_declared(self) -> None:
        text = "void Avery(void) {\n    DanaStep(1);\n}\n"
        out = pf.repair_prototypes(text, {"DanaStep": "void", "Avery": "void"}, macros={"DanaStep"})
        self.assertEqual(out, text)

    def test_header_declared_call_not_redeclared(self) -> None:
        text = "void Avery(void) {\n    DanaStep(1);\n}\n"
        out = pf.repair_prototypes(text, {"DanaStep": "void", "Avery": "void"}, {"DanaStep"})
        self.assertEqual(out, text)

    def test_declared_call_not_redeclared(self) -> None:
        text = "extern void DanaStep(s32);\nvoid Avery(void) {\n    DanaStep(1);\n}\n"
        self.assertEqual(pf.repair_prototypes(text, {"DanaStep": "void", "Avery": "void"}), text)


class Arity(unittest.TestCase):
    PARAMS = {"FileSeek": ["s32 offset"], "DanaInit": [], "QuinnSet": ["s32 a", "s32 b", "s32 c"]}

    def test_read_params(self) -> None:
        text = "s32 FileSeek(s32 offset) {\n}\nvoid DanaInit(void) {\n}\nvoid Avery(int n, ...);\n"
        self.assertEqual(pf.read_params(text), {"FileSeek": ["s32 offset"], "DanaInit": [], "Avery": None})

    def test_trim_call(self) -> None:
        text = "    x = FileSeek(handle, f(a, b), 0);\n"
        out, padded = pf.repair_arity(text, self.PARAMS)
        self.assertEqual(out, "    x = FileSeek(handle);\n")
        self.assertEqual(padded, [])

    def test_pad_call_reports(self) -> None:
        out, padded = pf.repair_arity("    QuinnSet(1);\n", self.PARAMS)
        self.assertEqual(out, "    QuinnSet(1, 0, 0);\n")
        self.assertEqual(padded, ["QuinnSet"])

    def test_declaration_params_follow_definition(self) -> None:
        text = "extern s32 FileSeek(s32, s32, s32);\nextern void DanaInit(s32 x);\nextern void QuinnSet(s32);\n"
        out, _ = pf.repair_arity(text, self.PARAMS)
        self.assertEqual(
            out,
            "extern s32 FileSeek(s32);\nextern void DanaInit(void);\nextern void QuinnSet(s32, s32, s32);\n",
        )

    def test_unprototyped_declaration_kept(self) -> None:
        out, _ = pf.repair_arity("extern void DanaInit();\n    DanaInit(3);\n", self.PARAMS)
        self.assertEqual(out, "extern void DanaInit();\n    DanaInit();\n")

    def test_alias_label_resolves(self) -> None:
        text = 'extern s32 FileSeekNoArgs(void) __asm__("FileSeek");\n    FileSeekNoArgs();\n'
        out, padded = pf.repair_arity(text, self.PARAMS)
        self.assertEqual(out, 'extern s32 FileSeekNoArgs(s32) __asm__("FileSeek");\n    FileSeekNoArgs(0);\n')
        self.assertEqual(padded, ["FileSeekNoArgs"])

    def test_variadic_declaration_follows_definition(self) -> None:
        out, _ = pf.repair_arity("extern void DanaInit(s32, ...);\n    DanaInit(1);\n", self.PARAMS)
        self.assertEqual(out, "extern void DanaInit(void);\n    DanaInit();\n")

    def test_plain_asm_label_resolves(self) -> None:
        text = 'extern void DanaInitRun(s8) asm(\n    "DanaInit");\n    DanaInitRun(0);\n'
        out, _ = pf.repair_arity(text, self.PARAMS)
        self.assertEqual(out, 'extern void DanaInitRun(void) asm(\n    "DanaInit");\n    DanaInitRun();\n')

    def test_definition_untouched(self) -> None:
        text = "void DanaInit(void) {\n    FileSeek(1);\n}\n"
        self.assertEqual(pf.repair_arity(text, self.PARAMS)[0], text)


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

    def test_cli_filters_native_branch(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            d = pathlib.Path(tmp)
            (d / "a.c").write_text(
                '#ifdef NATIVE\nvoid DanaStep(void) {\n    register s32 x asm("a0");\n}\n'
                '#else\nINCLUDE_ASM("asm/nonmatchings/a", DanaStep);\n#endif\n'
            )
            run = self.run_cli(d)
            self.assertEqual(run.returncode, 0, run.stderr)
            self.assertEqual((d / "out" / "a.c").read_text(), "void DanaStep(void) {\n    register s32 x;\n}\n")

    def run_cli(self, d: pathlib.Path, *extra: str) -> subprocess.CompletedProcess:
        for name in ("Makefile", "abs.txt", "syms.txt", "defined.txt"):
            if not (d / name).exists():
                (d / name).write_text("")
        return subprocess.run(
            [
                sys.executable,
                str(ROOT / "tools" / "port_filter.py"),
                "--makefile", str(d / "Makefile"),
                "--absolutes", str(d / "abs.txt"),
                "--symbols", str(d / "syms.txt"),
                "--defined", str(d / "defined.txt"),
                "--image", "0x80010000:0x800CEFE0",
                *extra,
                str(d / "a.c"), str(d / "out"),
            ],
            capture_output=True,
            text=True,
        )

    def test_cli_native_signature_wins(self) -> None:
        # A native body that names an argument the asm passed through
        # registers: callers must pass it, not lose it to trimming.
        with tempfile.TemporaryDirectory() as tmp:
            d = pathlib.Path(tmp)
            (d / "a.c").write_text(
                "void FileOpen(s32 fileId) {\n}\n"
                "#ifdef NATIVE\nvoid DanaLoad(s32 fileId) {\n    FileOpen(fileId);\n}\n"
                "#else\nvoid DanaLoad(void) {\n    FileOpen();\n}\n#endif\n"
                "void Quinn(void) {\n    DanaLoad(0x44);\n}\n"
            )
            run = self.run_cli(d)
            self.assertEqual(run.returncode, 0, run.stderr)
            self.assertIn("    DanaLoad(0x44);\n", (d / "out" / "a.c").read_text())

    def test_cli_rejects_unlisted_padding(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            d = pathlib.Path(tmp)
            (d / "a.c").write_text("void FileOpen(s32 fileId) {\n}\nvoid Dana(void) {\n    FileOpen();\n}\n")
            (d / "padded.txt").write_text("# reviewed\n")
            run = self.run_cli(d, "--padded-ok", str(d / "padded.txt"))
            self.assertNotEqual(run.returncode, 0)
            self.assertIn("a.c: FileOpen()", run.stderr)
            (d / "padded.txt").write_text("a.c FileOpen\n")
            run = self.run_cli(d, "--padded-ok", str(d / "padded.txt"))
            self.assertEqual(run.returncode, 0, run.stderr)


if __name__ == "__main__":
    unittest.main()
