"""Tests for tools/port_asm.py.

The execution tests compile translated statements with the host C
compiler and run them, so they check what the C computes, not its text.
They skip when no compiler is on PATH. Fixtures use invented names only.
"""

import pathlib
import shutil
import subprocess
import tempfile
import unittest

import port_asm

CC = shutil.which("cc") or shutil.which("clang") or shutil.which("gcc")

PRELUDE = """
#include <stdio.h>
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

/* A 64-bit host can't hold addresses in u32: tests address an arena. */
static u8 port_test_base[256];
#define PORT_ADDR(p) ((u32)((u8 *)(p) - port_test_base))
#define PORT_VAL(x) _Generic((x), u8 *: PORT_ADDR(x), u32 *: PORT_ADDR(x), default: (u32)(x))
#define PORT_LOAD(T, a) (*(T *)(port_test_base + (u32)(a)))
#define PORT_STORE(T, a, v) (*(T *)(port_test_base + (u32)(a)) = (T)(v))
#define PORT_OUT(lhs, v) ((lhs) = (__typeof__(lhs))(v))
u32 PortGteRead(int reg) { return 0; }
"""


def symbol(name: str) -> str:
    return f"PORT_ADDR({name})"


def translate(statement: str) -> str | None:
    return port_asm.translate(statement, "t", symbol)


def run_c(body: str, globals_: str = "") -> str:
    """Compile and run main() { body } and return its stdout."""
    with tempfile.TemporaryDirectory() as tmp:
        src = pathlib.Path(tmp) / "t.c"
        exe = pathlib.Path(tmp) / "t"
        src.write_text(PRELUDE + globals_ + "\nint main(void) {\n" + body + "\nreturn 0;\n}\n")
        subprocess.run([CC, "-w", "-o", str(exe), str(src)], check=True)
        return subprocess.run([str(exe)], check=True, capture_output=True, text=True).stdout


class Refuses(unittest.TestCase):
    def test_refuses_call(self) -> None:
        self.assertIsNone(translate('asm("jal DanaStep\\n\\tnop");'))

    def test_refuses_unclobbered_register(self) -> None:
        self.assertIsNone(translate('asm("addiu %0, $a0, 1" : "=r"(x));'))

    def test_refuses_unknown_instruction(self) -> None:
        self.assertIsNone(translate('asm("syscall");'))

    def test_accepts_clobbered_register(self) -> None:
        self.assertIsNotNone(translate('asm("addiu $v1, %1, 1\\n\\taddu %0, $v1, $v1" : "=r"(x) : "r"(y) : "v1");'))


@unittest.skipUnless(CC, "no host C compiler")
class Executes(unittest.TestCase):
    def check(self, statement: str, setup: str, prints: str, expected: str, globals_: str = "") -> None:
        c = translate(statement)
        self.assertIsNotNone(c, statement)
        self.assertEqual(run_c(setup + "\n" + c + "\n" + prints, globals_).strip(), expected)

    def test_arithmetic(self) -> None:
        self.check(
            'asm("addiu %0, %1, -10\\n\\tsll %0, %0, 3\\n\\tsubu %0, %0, %1\\n\\tsra %0, %0, 1"'
            ' : "=r"(x) : "r"(y));',
            "s32 x = 0, y = 4;",
            'printf("%d", x);',
            "-26",
        )

    def test_logic_and_compare(self) -> None:
        self.check(
            'asm("nor %0, $zero, %2\\n\\tandi %0, %0, 0xFF\\n\\tslt %1, %2, $zero\\n\\tori %1, %1, 0x10"'
            ' : "=r"(a), "=r"(b) : "r"(c));',
            "u32 a = 0, b = 0; s32 c = -2;",
            'printf("%u %u", a, b);',
            "1 17",
        )

    def test_lui_ori_and_shifts(self) -> None:
        self.check(
            'asm("lui %0, 0x8888\\n\\tori %0, %0, 0x8889\\n\\tsrl %1, %0, 28\\n\\tsra %2, %0, 28"'
            ' : "=r"(a), "=r"(b), "=r"(c));',
            "u32 a, b; s32 c;",
            'printf("%x %u %d", a, b, c);',
            "88888889 8 -8",
        )

    def test_mult_hi_lo(self) -> None:
        self.check(
            'asm("mult %2, %3\\n\\tmflo %0\\n\\tmfhi %1" : "=r"(lo), "=r"(hi) : "r"(a), "r"(b));',
            "u32 lo, hi; s32 a = -3, b = 0x40000000;",
            'printf("%x %x", lo, hi);',
            "40000000 ffffffff",
        )

    def test_multu(self) -> None:
        self.check(
            'asm("multu %1, %2\\n\\tmfhi %0" : "=r"(hi) : "r"(a), "r"(b));',
            "u32 hi; u32 a = 0xFFFFFFFF, b = 2;",
            'printf("%u", hi);',
            "1",
        )

    def test_hi_lo_across_statements(self) -> None:
        first = translate('asm("mult %1, %2" : "=x"(acc) : "r"(a), "r"(b));')
        second = translate('asm("mfhi %0" : "=r"(hi) : "x"(acc));')
        out = run_c(
            "s64 acc; s32 a = 0x10000, b = 0x30000, hi;\n" + first + "\n" + second + '\nprintf("%d", hi);'
        )
        self.assertEqual(out, "3")

    def test_loads_and_stores(self) -> None:
        self.check(
            'asm("lh %0, 2(%2)\\n\\tlhu %1, 2(%2)\\n\\tsb %0, 0(%2)\\n\\tsw %1, 4(%2)" : "=r"(a), "=r"(b) : "r"(p));',
            "s32 a; u32 b; u8 *buf = port_test_base; u8 *p = buf; buf[2] = 0xFE; buf[3] = 0xFF;",
            'printf("%d %u %u %u", a, b, buf[0], *(u32 *)(buf + 4));',
            "-2 65534 254 65534",
        )

    def test_memory_operand(self) -> None:
        self.check(
            'asm("lw %0, %2\\n\\tnor %1, $zero, %0" : "=r"(a), "=r"(b) : "m"(pad[1]));',
            "u32 a, b; u32 *pad = (u32 *)(port_test_base + 32); pad[1] = 5;",
            'printf("%u %x", a, b);',
            "5 fffffffa",
        )

    def test_symbol_address(self) -> None:
        self.check(
            'asm("lui %0, %%hi(gDanaTable)\\n\\tlw %0, %%lo(gDanaTable)(%0)\\n\\tla %1, gDanaTable\\n\\t'
            'lbu %2, gDanaTable+4(%3)" : "=r"(a), "=r"(b), "=r"(c) : "r"(i));',
            "u32 a, b, c; s32 i = 1, k; for (k = 0; k < 8; k++) gDanaTable[k] = k + 1;",
            'printf("%u %d %u", a, b == PORT_ADDR(gDanaTable), c);',
            "67305985 1 6",
            "#define gDanaTable (port_test_base + 64)",
        )

    def test_tied_operand(self) -> None:
        self.check(
            'asm("sll %0, %0, 2" : "=r"(x) : "0"(x));',
            "s32 x = 5;",
            'printf("%d", x);',
            "20",
        )

    def test_byte_output_keeps_type(self) -> None:
        self.check(
            'asm("ori %0, $zero, 0x1FF" : "=r"(b));',
            "u8 b = 0; u8 guard = 7;",
            'printf("%u %u", b, guard);',
            "255 7",
        )

    def test_noreorder_delay_slot(self) -> None:
        statement = (
            'asm(".set\\tnoreorder\\n\\tnop\\n\\taddiu\\t%0,%2,-10\\n\\tbgez\\t%0,1f\\n\\tsll\\t%0,%0,3\\n\\t'
            'ori\\t%0,$zero,10\\n\\tsubu\\t%0,%0,%2\\n\\tsll\\t%0,%0,3\\n1:\\n\\taddiu\\t%0,%0,64\\n\\t'
            'andi\\t%1,%0,255" : "=&r"(m), "=r"(i) : "r"(p));'
        )
        for p, expected in ((14, "96 96"), (3, "120 120"), (-30, "384 128")):
            self.check(statement, f"s32 m, i, p = {p};", 'printf("%d %d", m, i);', expected)

    def test_branch_has_a_delay_slot_by_default(self) -> None:
        # maspsx assembles every function under .set noreorder, so inline
        # asm runs the instruction after a branch on both paths, as retail's
        # func_8002BD48 does with the mult after its bnez.
        self.check(
            'asm("beqz %1, 1f\\n\\taddiu %0, %0, 1\\n1:\\n\\taddiu %0, %0, 2" : "=r"(x) : "r"(c), "0"(x));',
            "s32 x = 0, c = 0;",
            'printf("%d", x);',
            "3",
        )

    def test_set_reorder_branch_has_no_delay_slot(self) -> None:
        self.check(
            'asm(".set\\treorder\\n\\tbeqz %1, 1f\\n\\taddiu %0, %0, 1\\n1:\\n\\taddiu %0, %0, 2"'
            ' : "=r"(x) : "r"(c), "0"(x));',
            "s32 x = 0, c = 0;",
            'printf("%d", x);',
            "2",
        )

    def test_backward_loop(self) -> None:
        self.check(
            'asm("1:\\n\\taddiu %0, %0, 3\\n\\taddiu %1, %1, -1\\n\\tbnez %1, 1b\\n\\tnop"'
            ' : "=r"(x), "=r"(n) : "0"(x), "1"(n));',
            "s32 x = 0, n = 4;",
            'printf("%d %d", x, n);',
            "12 0",
        )

    def test_gte_through_port_calls(self) -> None:
        c = translate('asm volatile("mfc2 %0, $7\\n\\tswc2 $14, 4(%1)" : "=r"(z) : "r"(p) : "memory");')
        self.assertIn("PortGteRead(7)", c)
        self.assertIn("PortGteRead(14)", c)


if __name__ == "__main__":
    unittest.main()
