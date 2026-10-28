"""Tests for the port's software GTE (port/sdk/gte.c) and libgte (port/sdk/libgte.c).

Expected values come from the GTE's formulas in psx-spx, worked by hand.
"""

import unittest

from test_port_sdk import CC, run_driver

PRELUDE = """
#include "port_gte.h"
#include <psxsdk/libgte.h>
#define W PortGteWrite
#define R PortGteRead
#define WC PortGteWriteControl
#define RC PortGteReadControl
/* Psy-Q's sine table: sin in the low half, cos in the high half. */
u32 D_8009E070[4096];
/* libgte's matrix stack and its depth in bytes. */
u32 D_8009DD70[160];
s32 D_8009DD6C;
/* VectorNormal's reciprocal square roots (retail's are game data). */
s16 D_8009DBD4[192];
static void Identity(void) {
    WC(0, 0x1000); WC(1, 0); WC(2, 0x1000); WC(3, 0); WC(4, 0x1000);
}
"""


@unittest.skipUnless(CC, "no host compiler")
class Gte(unittest.TestCase):
    def check(self, body: str) -> None:
        run = run_driver(["port/sdk/gte.c", "port/sdk/libgte.c"], PRELUDE + "int main(void) {\n" + body + "    return 0;\n}\n")
        self.assertEqual(run.returncode, 0, f"check {run.returncode} failed\n{run.stderr}")

    def test_rtps_projects(self) -> None:
        self.check(
            "    Identity();\n"
            "    WC(5, 0); WC(6, 0); WC(7, 1000);           /* TR */\n"
            "    WC(24, 160 << 16); WC(25, 120 << 16);      /* OFX, OFY */\n"
            "    WC(26, 1000);                              /* H */\n"
            "    W(0, 50u << 16 | 100); W(1, 0);            /* V0 = (100, 50, 0) */\n"
            "    PortGteCommand(PORT_GTE_RTPS);\n"
            "    if (R(19) != 1000) return 1;               /* SZ3 */\n"
            "    if (R(14) != (170u << 16 | 260)) return 2; /* SXY2 */\n"
            "    if (R(9) != 100 || R(10) != 50 || R(11) != 1000) return 3;\n"
        )

    def test_rtps_divides_like_the_console(self) -> None:
        # The GTE divides H by SZ3 with its UNR table and two Newton-Raphson
        # steps (psx-spx), not exactly: 300 / 188 in 16.16 is 104578, where
        # rounding the exact quotient gives 104579. DQA 1, DQB 0 make MAC0
        # the quotient.
        self.check(
            "    Identity();\n"
            "    WC(5, 0); WC(6, 0); WC(24, 0); WC(25, 0); WC(26, 300);\n"
            "    WC(27, 1); WC(28, 0);                      /* DQA, DQB */\n"
            "    W(0, 0); W(1, 0);\n"
            "    WC(7, 188); PortGteCommand(PORT_GTE_RTPS);\n"
            "    if (R(24) != 104578) return 1;\n"
            "    WC(7, 370); PortGteCommand(PORT_GTE_RTPS);\n"
            "    if (R(24) != 53138) return 2;              /* exact: 53137 */\n"
        )

    def test_rtps_saturates(self) -> None:
        self.check(
            "    Identity();\n"
            "    WC(5, 0); WC(6, 0); WC(7, 100);\n"
            "    WC(24, 0); WC(25, 0); WC(26, 1000);\n"
            "    W(0, (u32)(u16)-3000); W(1, 0);            /* far left */\n"
            "    PortGteCommand(PORT_GTE_RTPS);\n"
            "    if ((s16)(R(14) & 0xFFFF) != -0x400) return 1;\n"
            "    if (!(RC(31) & (1 << 14))) return 2;       /* SX2 saturated */\n"
            "    if (!(RC(31) & (1u << 31))) return 3;      /* the error summary bit */\n"
            "    if (!(RC(31) & (1 << 17))) return 4;       /* division overflow: H >= 2 SZ3 */\n"
        )

    def test_rtpt_fifo_and_nclip(self) -> None:
        self.check(
            "    Identity();\n"
            "    WC(5, 0); WC(6, 0); WC(7, 1000);\n"
            "    WC(24, 0); WC(25, 0); WC(26, 1000);\n"
            "    W(0, 0); W(1, 0); W(2, 10); W(3, 0); W(4, 10u << 16); W(5, 0);\n"
            "    PortGteCommand(PORT_GTE_RTPT);\n"
            "    if (R(12) != 0 || R(13) != 10 || R(14) != 10u << 16) return 1;\n"
            "    PortGteCommand(PORT_GTE_NCLIP);\n"
            "    if ((s32)R(24) != 100) return 2;            /* counter-clockwise: positive */\n"
            "    WC(29, 0x155);\n"
            "    PortGteCommand(PORT_GTE_AVSZ3);\n"
            "    if (R(7) != (0x155 * 3000) >> 12) return 3; /* OTZ */\n"
        )

    def test_mvmva_rotation_plus_translation(self) -> None:
        self.check(
            "    WC(0, 0); WC(1, (u32)(u16)-0x1000 << 16); WC(2, 0); WC(3, 0); WC(4, 0x1000); /* 90 deg about Z */\n"
            "    WC(0, (u32)(u16)-0x1000 << 16); WC(1, 0x1000 << 16);\n"
            "    WC(5, 1); WC(6, 2); WC(7, 3);\n"
            "    W(0, 0u << 16 | 100); W(1, 7);\n"
            "    PortGteCommand(0x4A480012u);              /* MVMVA sf=1 RT V0 TR */\n"
            "    if ((s32)R(25) != 1 || (s32)R(26) != 102 || (s32)R(27) != 10) return 1;\n"
        )

    def test_mulmatrix0_and_rotmatrix(self) -> None:
        self.check(
            "    MATRIX a, b, c;\n"
            "    SVECTOR r = {0, 0, 1024, 0};\n"
            "    D_8009E070[0] = 0x1000u << 16;              /* sin 0, cos 1 */\n"
            "    D_8009E070[1024] = 0x1000;                  /* sin 1, cos 0 */\n"
            "    RotMatrix(&r, &a);                          /* 90 degrees about Z */\n"
            "    if (a.m[0][0] != 0 || a.m[0][1] != -4096 || a.m[1][0] != 4096 || a.m[2][2] != 4096) return 1;\n"
            "    MulMatrix0(&a, &a, &b);                     /* 180 degrees */\n"
            "    if (b.m[0][0] != -4096 || b.m[1][1] != -4096 || b.m[0][1] != 0) return 2;\n"
            "    SetRotMatrix(&a); PushMatrix();\n"
            "    SetRotMatrix(&b); PopMatrix();\n"
            "    if ((s16)RC(0) != 0 || (s16)(RC(0) >> 16) != -4096) return 3;\n"
            "    (void)c;\n"
        )

    def test_matrix_products_store_ir3_as_a_word(self) -> None:
        # Retail ends MulMatrix0, MulMatrix2 and MulRotMatrix with swc2 $11,
        # 0x10: m[2][2] and the pad after it, which takes IR3's sign.
        self.check(
            "    MATRIX a, b;\n"
            "    int i, j;\n"
            "#define PAD(x) (((s16 *)&(x))[9])                /* the 2 bytes after m[2][2] */\n"
            "    for (i = 0; i < 3; i++) for (j = 0; j < 3; j++) a.m[i][j] = i == j ? 4096 : 0;\n"
            "    a.m[2][2] = -4096;\n"
            "    b = a; PAD(b) = 0x1234;\n"
            "    MulMatrix0(&a, &a, &b);                     /* m[2][2] = 4096 */\n"
            "    if (b.m[2][2] != 4096 || PAD(b) != 0) return 1;\n"
            "    b = a; b.m[2][2] = 4096; PAD(b) = 0x1234;\n"
            "    MulMatrix0(&a, &b, &b);                     /* m[2][2] = -4096 */\n"
            "    if (b.m[2][2] != -4096 || (u16)PAD(b) != 0xFFFF) return 2;\n"
            "    PAD(b) = 0x1234; MulMatrix2(&a, &b);          /* back to 4096 */\n"
            "    if (b.m[2][2] != 4096 || PAD(b) != 0) return 3;\n"
        )

    def test_matrix_stack_lives_in_game_memory(self) -> None:
        # Retail's PushMatrix keeps the stack in RAM at D_8009DD70, 0x20
        # bytes an entry, with the depth in bytes at D_8009DD6C.
        self.check(
            "    Identity(); WC(5, 7);\n"
            "    PushMatrix();\n"
            "    if (D_8009DD6C != 0x20) return 1;\n"
            "    if (D_8009DD70[0] != 0x1000 || D_8009DD70[5] != 7) return 2;\n"
            "    WC(5, 0); PopMatrix();\n"
            "    if (RC(5) != 7 || D_8009DD6C != 0) return 3;\n"
        )

    def test_vector_normal_follows_retail(self) -> None:
        # Retail (func_8007C548) normalises with the GTE: SQR, LZCS on the
        # sum, a reciprocal square root from the table at D_8009DBD4, GPF,
        # then a shift. The table here is made up; retail's is game data.
        table = [0x1000 - i * 13 for i in range(192)]
        cases = [(300, -400, 1200), (1, 2, 3), (-30000, 25000, 7), (4096, 0, 0)]
        lines = ["    s16 *t = D_8009DBD4;", "    VECTOR in, out;", "    int i;"]
        lines.append(f"    for (i = 0; i < 192; i++) t[i] = 0x1000 - i * 13;")
        for k, (x, y, z) in enumerate(cases):
            want = retail_vector_normal(x, y, z, table)
            lines.append(f"    in.vx = {x}; in.vy = {y}; in.vz = {z}; VectorNormal(&in, &out, 0);")
            lines.append(f"    if (out.vx != {want[0]} || out.vy != {want[1]} || out.vz != {want[2]}) return {k + 1};")
        self.check("\n".join(lines) + "\n")


def retail_vector_normal(x: int, y: int, z: int, table: list[int]) -> tuple[int, int, int]:
    """func_8007C548, step by step, for nonzero 16-bit components."""
    ir = [x, y, z]
    total = sum(v * v for v in ir)
    lz = 32 - total.bit_length()
    lz &= ~1
    shift = (31 - lz) >> 1
    scaled = total << (lz - 24) if lz >= 24 else total >> (24 - lz)
    ir0 = table[scaled - 64]
    return tuple((ir0 * v) >> (shift & 31) for v in ir)


if __name__ == "__main__":
    unittest.main()
