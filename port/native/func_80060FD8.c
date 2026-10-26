/* Native body from m2c --valid-syntax of the retail asm. */
#include "port_m2c.h"

void func_80060FD8(void) {
    extern s32 port_D_8009A314 __asm__("D_8009A314");
    extern s32 port_D_8009AC00 __asm__("D_8009AC00");
    extern s32 port_D_8009AC08 __asm__("D_8009AC08");
    extern u8 port_D_8009AC10 __asm__("D_8009AC10");
    extern u16 port_D_8009AEA0 __asm__("D_8009AEA0");
    extern u16 port_D_8009AEA2 __asm__("D_8009AEA2");
    extern u16 port_D_8009AEA4 __asm__("D_8009AEA4");
    extern u16 port_D_8009AEA6 __asm__("D_8009AEA6");
    extern u8 port_D_8009AEA8 __asm__("D_8009AEA8");
    extern u8 port_D_8009AEAA __asm__("D_8009AEAA");
    extern u16 port_D_8009AEAC __asm__("D_8009AEAC");
    extern u8 port_D_8009AEB2 __asm__("D_8009AEB2");
    extern u8 port_D_800A3348 __asm__("D_800A3348");
    extern u8 port_D_800A35EC __asm__("D_800A35EC");
    extern u8 port_D_800A3644 __asm__("D_800A3644");
    extern s32 port_D_800A3654 __asm__("D_800A3654");
    extern s32 port_D_800A3678 __asm__("D_800A3678");
    extern u8 port_D_800A37BC __asm__("D_800A37BC");
    extern u8 port_D_800A37D8 __asm__("D_800A37D8");
    extern void * port_D_800A37F8 __asm__("D_800A37F8");
    extern u8 port_D_800A37FC __asm__("D_800A37FC");
    extern u8 port_D_800A3888 __asm__("D_800A3888");
    extern u8 port_D_800A3A1C __asm__("D_800A3A1C");
    extern u8 port_D_800A3A84 __asm__("D_800A3A84");
    s32 port_frame[38];
#define sp20 (*(u8 *)((u8 *)port_frame + 0x20))
#define sp28 (*(s32 *)((u8 *)port_frame + 0x28))
#define sp30 (*(s32 *)((u8 *)port_frame + 0x30))
#define sp38 (*(s32 *)((u8 *)port_frame + 0x38))
#define sp40 (*(s32 *)((u8 *)port_frame + 0x40))
#define sp48 (*(s32 *)((u8 *)port_frame + 0x48))
#define sp50 (*(s32 *)((u8 *)port_frame + 0x50))
#define sp58 (*(s32 *)((u8 *)port_frame + 0x58))
#define sp60 (*(s32 *)((u8 *)port_frame + 0x60))
#define sp68 (*(s32 *)((u8 *)port_frame + 0x68))
#define sp ((u8 *)port_frame)
    s16 temp_s2_7;
    s16 temp_s3_2;
    s16 temp_s3_4;
    s16 temp_s4;
    s16 var_a1_2;
    s16 var_a1_3;
    s16 var_fp;
    s16 var_s4;
    s16 var_v0_2;
    s16 var_v0_3;
    s32 temp_a0_12;
    s32 temp_a0_7;
    s32 temp_fp;
    s32 temp_s0_10;
    s32 temp_s1_2;
    s32 temp_s2_5;
    s32 temp_s2_6;
    s32 temp_s2_8;
    s32 temp_s2_9;
    s32 temp_s3;
    s32 temp_s3_3;
    s32 temp_s3_5;
    s32 temp_s4_2;
    s32 temp_v0_16;
    s32 temp_v1_13;
    s32 temp_v1_14;
    s32 var_a2_2;
    s32 var_s4_2;
    s32 var_t4;
    s32 var_v0_4;
    s32 var_v1;
    s8 temp_v0;
    s8 temp_v0_11;
    s8 temp_v0_13;
    s8 temp_v0_15;
    s8 temp_v0_17;
    s8 temp_v0_20;
    s8 temp_v0_22;
    s8 temp_v0_23;
    s8 temp_v0_25;
    s8 temp_v0_3;
    s8 temp_v0_5;
    s8 temp_v0_9;
    s8 temp_v1_12;
    s8 var_a1;
    s8 var_a2;
    s8 var_a3;
    s8 var_s2;
    s8 var_s2_2;
    s8 var_s7;
    s8 var_s7_10;
    s8 var_s7_2;
    s8 var_s7_3;
    s8 var_s7_4;
    s8 var_s7_5;
    s8 var_s7_6;
    s8 var_s7_7;
    s8 var_s7_8;
    s8 var_s7_9;
    s8 var_v0;
    u16 temp_s0_7;
    u16 temp_s0_8;
    u16 temp_s1_3;
    u8 temp_a0;
    u8 temp_a0_10;
    u8 temp_a0_11;
    u8 temp_a0_2;
    u8 temp_a0_3;
    u8 temp_a0_4;
    u8 temp_a0_5;
    u8 temp_a0_6;
    u8 temp_a0_8;
    u8 temp_a0_9;
    u8 temp_v0_10;
    u8 temp_v1_15;
    u8 temp_v1_16;
    u8 temp_v1_21;
    u8 temp_v1_22;
    u8 temp_v1_23;
    u8 temp_v1_24;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u8 temp_v1_6;
    u8 temp_v1_7;
    void **temp_t0;
    void *temp_s0;
    void *temp_s0_11;
    void *temp_s0_12;
    void *temp_s0_13;
    void *temp_s0_14;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_s0_9;
    void *temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_v0_12;
    void *temp_v0_14;
    void *temp_v0_18;
    void *temp_v0_19;
    void *temp_v0_21;
    void *temp_v0_24;
    void *temp_v0_2;
    void *temp_v0_4;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v0_8;
    void *temp_v1;
    void *temp_v1_10;
    void *temp_v1_11;
    void *temp_v1_17;
    void *temp_v1_18;
    void *temp_v1_19;
    void *temp_v1_20;
    void *temp_v1_2;
    void *temp_v1_8;
    void *temp_v1_9;
    void *var_s5;
    void *var_s5_2;
    void *var_s5_3;
    void *var_s5_4;

    /* m2c seeds these from the caller's saved $s4, $s5, $fp: retail reads
     * them before writing only on paths a first-iteration test rules out. */
    var_s4 = 0;
    var_s5 = 0;
    var_fp = 0;
    temp_a0 = port_D_800A35EC;
    port_D_800A35EC = temp_a0 + 1;
    temp_v1 = port_D_800A3678 + (temp_a0 * 0x24);
    M2C_FIELD(temp_v1, s8 *, 4) = 0;
    M2C_FIELD(temp_v1, s8 *, 3) = 0;
    M2C_FIELD(temp_v1, s8 *, 2) = 0;
    temp_a0_2 = port_D_800A37BC;
    M2C_FIELD(temp_v1, s16 *, 0x12) = 0;
    M2C_FIELD(temp_v1, s16 *, 0x14) = 0;
    M2C_FIELD(temp_v1, s32 *, 0x1C) = 0;
    M2C_FIELD(temp_v1, s16 *, 0x1A) = 0;
    M2C_FIELD(temp_v1, s16 *, 0) = 0;
    M2C_FIELD(temp_v1, s16 *, 0xA) = 0;
    M2C_FIELD(temp_v1, s16 *, 6) = 0;
    M2C_FIELD(temp_v1, s16 *, 0xC) = 0;
    M2C_FIELD(temp_v1, s16 *, 8) = 0;
    M2C_FIELD(temp_v1, s16 *, 0xE) = 0;
    M2C_FIELD(temp_v1, s16 *, 0x10) = 0;
    M2C_FIELD(temp_v1, s16 *, 0x1A) = 0;
    port_D_800A37BC = temp_a0_2 + 1;
    temp_v1_2 = port_D_800A3654 + (temp_a0_2 * 0xC);
    M2C_FIELD(temp_v1, void **, 0x20) = temp_v1_2;
    M2C_FIELD(temp_v1_2, s8 *, 0) = 0;
    M2C_FIELD(temp_v1_2, s8 *, 3) = 0;
    M2C_FIELD(temp_v1_2, s32 *, 4) = 0;
    temp_s0 = M2C_FIELD(temp_v1, void **, 0x20);
    M2C_FIELD(temp_v1, s16 *, 0x1A) = 1;
    M2C_FIELD(temp_v1, s16 *, 0x14) = 0xDA;
    M2C_FIELD(temp_s0, s8 *, 2) = 2;
    M2C_FIELD(temp_s0, s8 *, 1) = 2;
    M2C_FIELD(temp_s0, s32 *, 8) = (s32) port_D_8009AC00;
    func_8005A7B8(2, 2, port_D_800A3348, M2C_UNALIGNED32(M2C_FIELD(port_D_800A3348, M2C_UNK *, 0)), M2C_FIELD(port_D_800A3348, s8 *, 4), M2C_FIELD(port_D_800A3348, s8 *, 5), M2C_FIELD(port_D_800A3348, s8 *, 6));
    M2C_FIELD(temp_v1, s16 *, 0x12) = func_8005B0E4(0x140, M2C_FIELD(temp_s0, s32 *, 8));
    port_D_800A37F8 = temp_v1;
    var_v1 = 0x3C;
    if (port_D_800A3644 == 0) {
        var_v1 = 0x55;
    }
    sp20 = 0;
    if ((port_D_800A3644 + 1) != 0) {
        sp40 = var_v1 << 0x18;
        do {
            var_s7 = 0;
            var_a2 = 0x20;
loop_5:
            temp_v1_3 = port_D_800A35EC;
            port_D_800A35EC = temp_v1_3 + 1;
            temp_s0_2 = port_D_800A3678 + (temp_v1_3 * 0x24);
            M2C_FIELD(temp_s0_2, s16 *, 0) = 2;
            M2C_FIELD(temp_s0_2, s8 *, 4) = 0;
            M2C_FIELD(temp_s0_2, s16 *, 0x16) = 0x140;
            M2C_FIELD(temp_s0_2, s16 *, 0x12) = 0;
            M2C_FIELD(temp_s0_2, s16 *, 0x14) = 0;
            M2C_FIELD(temp_s0_2, s32 *, 0x1C) = 0;
            M2C_FIELD(temp_s0_2, s8 *, 3) = 0;
            M2C_FIELD(temp_s0_2, s8 *, 2) = 0;
            M2C_FIELD(temp_s0_2, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_s0_2, s16 *, 6) = 0;
            M2C_FIELD(temp_s0_2, s16 *, 0xA) = 0;
            M2C_FIELD(temp_s0_2, s16 *, 8) = 0;
            M2C_FIELD(temp_s0_2, s16 *, 0xC) = 0;
            M2C_FIELD(temp_s0_2, s16 *, 0xE) = 0;
            M2C_FIELD(temp_s0_2, s16 *, 0x10) = 0;
            M2C_FIELD(temp_s0_2, s16 *, 0x18) = 0x4A;
            M2C_FIELD(temp_s0_2, s8 *, 2) = var_a2;
            M2C_FIELD(temp_s0_2, s8 *, 3) = var_a2;
            M2C_FIELD(temp_s0_2, s8 *, 4) = 0x40;
            sp68 = (s32) var_a2;
            temp_v0_2 = func_80057D50(1);
            M2C_FIELD(temp_s0_2, void **, 0x20) = temp_v0_2;
            SetPolyF4(temp_v0_2);
            SetSemiTrans(temp_v0_2, 1);
            M2C_FIELD(temp_v0_2, s8 *, 6) = 0x40;
            M2C_FIELD(temp_v0_2, s16 *, 0xC) = 0x140;
            M2C_FIELD(temp_v0_2, s16 *, 0x12) = 0x4A;
            M2C_FIELD(temp_v0_2, s16 *, 8) = 0;
            M2C_FIELD(temp_v0_2, s16 *, 0xA) = 0;
            M2C_FIELD(temp_v0_2, s16 *, 0xE) = 0;
            M2C_FIELD(temp_v0_2, s16 *, 0x10) = 0;
            M2C_FIELD(temp_v0_2, s16 *, 0x14) = 0x140;
            M2C_FIELD(temp_v0_2, s16 *, 0x16) = 0x4A;
            M2C_FIELD(temp_v0_2, s8 *, 4) = var_a2;
            M2C_FIELD(temp_v0_2, s8 *, 5) = var_a2;
            M2C_FIELD(temp_s0_2, s16 *, 0x1A) = 3;
            M2C_FIELD(temp_s0_2, s16 *, 0x12) = -0xA0;
            M2C_FIELD(temp_s0_2, s16 *, 0x14) = (s16) (((s8) sp20 * 0x4C) + 3);
            if ((var_s7 << 0x18) == 0) {
                (*(M2C_UNK *)(port_D_800A37D8 + (((s8) sp20 * 4)))) = temp_s0_2;
            } else {
                M2C_FIELD(var_s5, void **, 0x1C) = temp_s0_2;
            }
            temp_v0_3 = var_s7 + 1;
            var_s7 = temp_v0_3;
            var_s5 = temp_s0_2;
            if (temp_v0_3 < 2) {
                goto loop_5;
            }
            var_s7_2 = 0;
            temp_s3 = (s8) sp20 * 0x4C;
loop_10:
            if (var_s7_2 < 3) {
                if (var_s7_2 <= 0) {
                    if (var_s7_2 != 0) {

                    } else {
                        goto block_15;
                    }
                } else {
                    var_s4 = temp_s3 + 2;
                    var_fp = 0xA0;
                    sp28 = 2;
                    sp30 = 0x4C;
                    if (var_s7_2 == 1) {
                        var_fp = -0xA2;
                    }
                }
            } else if (var_s7_2 == 3) {
block_15:
                var_fp = -0xA1;
                sp28 = 0x142;
                sp30 = 2;
                if ((var_s7_2 << 0x18) == 0) {
                    var_s4 = temp_s3 + 1;
                } else {
                    var_s4 = temp_s3 + 0x4D;
                }
            }
            temp_v1_4 = port_D_800A35EC;
            port_D_800A35EC = temp_v1_4 + 1;
            temp_s2 = port_D_800A3678 + (temp_v1_4 * 0x24);
            M2C_FIELD(temp_s2, s16 *, 0x12) = 0;
            M2C_FIELD(temp_s2, s16 *, 0x14) = 0;
            M2C_FIELD(temp_s2, void **, 0x1C) = NULL;
            M2C_FIELD(temp_s2, s8 *, 4) = 0;
            M2C_FIELD(temp_s2, s8 *, 3) = 0;
            M2C_FIELD(temp_s2, s8 *, 2) = 0;
            M2C_FIELD(temp_s2, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_s2, s16 *, 0) = 2;
            M2C_FIELD(temp_s2, s16 *, 6) = 0;
            M2C_FIELD(temp_s2, s16 *, 0xA) = 0;
            M2C_FIELD(temp_s2, s16 *, 8) = 0;
            M2C_FIELD(temp_s2, s16 *, 0xC) = 0;
            M2C_FIELD(temp_s2, s16 *, 0xE) = 0;
            M2C_FIELD(temp_s2, s16 *, 0x10) = 0;
            M2C_FIELD(temp_s2, u16 *, 0x16) = (u16) sp28;
            M2C_FIELD(temp_s2, s8 *, 2) = 0x40;
            M2C_FIELD(temp_s2, s8 *, 3) = 0x40;
            M2C_FIELD(temp_s2, s8 *, 4) = 0x40;
            M2C_FIELD(temp_s2, u16 *, 0x18) = (u16) sp30;
            temp_v0_4 = func_80057D50(1, port_D_800A3678);
            M2C_FIELD(temp_s2, void **, 0x20) = temp_v0_4;
            SetPolyF4(temp_v0_4);
            SetSemiTrans(temp_v0_4, 0);
            M2C_FIELD(temp_v0_4, s8 *, 4) = 0x40;
            M2C_FIELD(temp_v0_4, s8 *, 5) = 0x40;
            M2C_FIELD(temp_v0_4, s8 *, 6) = 0x40;
            M2C_FIELD(temp_v0_4, s16 *, 8) = 0;
            M2C_FIELD(temp_v0_4, s16 *, 0xA) = 0;
            M2C_FIELD(temp_v0_4, s16 *, 0xE) = 0;
            M2C_FIELD(temp_v0_4, s16 *, 0x10) = 0;
            M2C_FIELD(temp_v0_4, u16 *, 0xC) = (u16) sp28;
            M2C_FIELD(temp_v0_4, u16 *, 0x14) = (u16) sp28;
            M2C_FIELD(temp_v0_4, u16 *, 0x12) = (u16) sp30;
            M2C_FIELD(temp_v0_4, u16 *, 0x16) = (u16) sp30;
            M2C_FIELD(temp_s2, s16 *, 0x1A) = 3;
            M2C_FIELD(temp_s2, s16 *, 0x12) = var_fp;
            M2C_FIELD(temp_s2, s16 *, 0x14) = var_s4;
            M2C_FIELD(var_s5, void **, 0x1C) = temp_s2;
            temp_v0_5 = var_s7_2 + 1;
            var_s7_2 = temp_v0_5;
            var_s5 = temp_s2;
            if (temp_v0_5 < 4) {
                goto loop_10;
            }
            temp_v1_5 = port_D_800A35EC;
            port_D_800A35EC = temp_v1_5 + 1;
            temp_s1 = port_D_800A3678 + (temp_v1_5 * 0x24);
            M2C_FIELD(temp_s1, s16 *, 0x12) = 0;
            M2C_FIELD(temp_s1, s16 *, 0x14) = 0;
            M2C_FIELD(temp_s1, void **, 0x1C) = NULL;
            M2C_FIELD(temp_s1, s8 *, 4) = 0;
            M2C_FIELD(temp_s1, s8 *, 3) = 0;
            M2C_FIELD(temp_s1, s8 *, 2) = 0;
            M2C_FIELD(temp_s1, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_s1, s16 *, 0) = 1;
            M2C_FIELD(temp_s1, s16 *, 0xA) = 0;
            M2C_FIELD(temp_s1, s16 *, 6) = 0;
            M2C_FIELD(temp_s1, s16 *, 0xC) = 0;
            M2C_FIELD(temp_s1, s16 *, 8) = 0;
            M2C_FIELD(temp_s1, s16 *, 0x16) = 0x74;
            M2C_FIELD(temp_s1, s16 *, 0x18) = 0x50;
            M2C_FIELD(temp_s1, s16 *, 0xE) = 0;
            M2C_FIELD(temp_s1, s16 *, 0x10) = 0;
            temp_v0_6 = func_80057CCC(1, 0x74);
            SetPolyFT4(temp_v0_6);
            SetShadeTex(temp_v0_6, 0);
            M2C_FIELD(temp_v0_6, s8 *, 4) = 0x80;
            M2C_FIELD(temp_v0_6, s8 *, 5) = 0x80;
            M2C_FIELD(temp_v0_6, s8 *, 6) = 0x80;
            SetSemiTrans(temp_v0_6, 0);
            M2C_FIELD(temp_s1, void **, 0x20) = temp_v0_6;
            M2C_FIELD(temp_s1, s16 *, 0x1A) = 2;
            M2C_FIELD(temp_s1, s16 *, 0x12) = -0x3A;
            temp_v1_6 = port_D_800A35EC;
            temp_s4 = (s8) sp20 * 0x4C;
            M2C_FIELD(temp_s1, s16 *, 0x14) = temp_s4;
            M2C_FIELD(temp_s2, void **, 0x1C) = temp_s1;
            (*(M2C_UNK *)(port_D_800A3A1C + (((s8) sp20 * 4)))) = temp_s1;
            port_D_800A35EC = temp_v1_6 + 1;
            temp_s2_2 = port_D_800A3678 + (temp_v1_6 * 0x24);
            M2C_FIELD(temp_s2_2, s16 *, 0x12) = 0;
            M2C_FIELD(temp_s2_2, s16 *, 0x14) = 0;
            M2C_FIELD(temp_s2_2, void **, 0x1C) = NULL;
            M2C_FIELD(temp_s2_2, s8 *, 4) = 0;
            M2C_FIELD(temp_s2_2, s8 *, 3) = 0;
            M2C_FIELD(temp_s2_2, s8 *, 2) = 0;
            M2C_FIELD(temp_s2_2, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_s2_2, s16 *, 0) = 2;
            M2C_FIELD(temp_s2_2, s16 *, 6) = 0;
            M2C_FIELD(temp_s2_2, s16 *, 0xA) = 0;
            M2C_FIELD(temp_s2_2, s16 *, 8) = 0;
            M2C_FIELD(temp_s2_2, s16 *, 0xC) = 0;
            M2C_FIELD(temp_s2_2, s16 *, 0xE) = 0;
            M2C_FIELD(temp_s2_2, s16 *, 0x10) = 0;
            M2C_FIELD(temp_s2_2, s16 *, 0x16) = 4;
            M2C_FIELD(temp_s2_2, s16 *, 0x18) = 1;
            M2C_FIELD(temp_s2_2, s8 *, 2) = 0;
            M2C_FIELD(temp_s2_2, s8 *, 3) = 0;
            M2C_FIELD(temp_s2_2, s8 *, 4) = 0;
            temp_v0_7 = func_80057D50(1);
            M2C_FIELD(temp_s2_2, void **, 0x20) = temp_v0_7;
            SetPolyF4(temp_v0_7);
            SetSemiTrans(temp_v0_7, 1);
            M2C_FIELD(temp_v0_7, s8 *, 4) = 0;
            M2C_FIELD(temp_v0_7, s8 *, 5) = 0;
            M2C_FIELD(temp_v0_7, s8 *, 6) = 0;
            temp_v1_7 = port_D_800A35EC;
            var_s7_3 = 0;
            M2C_FIELD(temp_v0_7, s16 *, 8) = 0;
            M2C_FIELD(temp_v0_7, s16 *, 0xA) = 0;
            M2C_FIELD(temp_v0_7, s16 *, 0xC) = 4;
            M2C_FIELD(temp_v0_7, s16 *, 0xE) = 0;
            M2C_FIELD(temp_v0_7, s16 *, 0x10) = 0;
            M2C_FIELD(temp_v0_7, s16 *, 0x12) = 1;
            M2C_FIELD(temp_v0_7, s16 *, 0x14) = 4;
            M2C_FIELD(temp_v0_7, s16 *, 0x16) = 1;
            M2C_FIELD(temp_s2_2, s16 *, 0x12) = -2;
            M2C_FIELD(temp_s2_2, s16 *, 0x1A) = 1;
            M2C_FIELD(temp_s2_2, s16 *, 0x14) = (s16) (temp_s4 + 0x35);
            M2C_FIELD(temp_s1, void **, 0x1C) = temp_s2_2;
            port_D_800A35EC = temp_v1_7 + 1;
            temp_s0_3 = port_D_800A3678 + (temp_v1_7 * 0x24);
            M2C_FIELD(temp_s0_3, s16 *, 0x12) = 0;
            M2C_FIELD(temp_s0_3, s16 *, 0x14) = 0;
            M2C_FIELD(temp_s0_3, s32 *, 0x1C) = 0;
            M2C_FIELD(temp_s0_3, s8 *, 4) = 0;
            M2C_FIELD(temp_s0_3, s8 *, 3) = 0;
            M2C_FIELD(temp_s0_3, s8 *, 2) = 0;
            M2C_FIELD(temp_s0_3, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_s0_3, s16 *, 0) = 2;
            M2C_FIELD(temp_s0_3, s16 *, 6) = 0;
            M2C_FIELD(temp_s0_3, s16 *, 0xA) = 0;
            M2C_FIELD(temp_s0_3, s16 *, 8) = 0;
            M2C_FIELD(temp_s0_3, s16 *, 0xC) = 0;
            M2C_FIELD(temp_s0_3, s16 *, 0xE) = 0;
            M2C_FIELD(temp_s0_3, s16 *, 0x10) = 0;
            M2C_FIELD(temp_s0_3, s16 *, 0x16) = 0x140;
            M2C_FIELD(temp_s0_3, s16 *, 0x18) = 0x4A;
            M2C_FIELD(temp_s0_3, s8 *, 2) = 0;
            M2C_FIELD(temp_s0_3, s8 *, 3) = 0;
            M2C_FIELD(temp_s0_3, s8 *, 4) = 0;
            temp_v0_8 = func_80057D50(1);
            M2C_FIELD(temp_s0_3, void **, 0x20) = temp_v0_8;
            SetPolyF4(temp_v0_8);
            SetSemiTrans(temp_v0_8, 1);
            M2C_FIELD(temp_v0_8, s16 *, 0xC) = 0x140;
            M2C_FIELD(temp_v0_8, s16 *, 0x12) = 0x4A;
            M2C_FIELD(temp_v0_8, s8 *, 4) = 0;
            M2C_FIELD(temp_v0_8, s8 *, 5) = 0;
            M2C_FIELD(temp_v0_8, s8 *, 6) = 0;
            M2C_FIELD(temp_v0_8, s16 *, 8) = 0;
            M2C_FIELD(temp_v0_8, s16 *, 0xA) = 0;
            M2C_FIELD(temp_v0_8, s16 *, 0xE) = 0;
            M2C_FIELD(temp_v0_8, s16 *, 0x10) = 0;
            M2C_FIELD(temp_v0_8, s16 *, 0x14) = 0x140;
            M2C_FIELD(temp_v0_8, s16 *, 0x16) = 0x4A;
            M2C_FIELD(temp_s0_3, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_s0_3, s16 *, 0x12) = -0xA0;
            M2C_FIELD(temp_s0_3, s16 *, 0x14) = (s16) (temp_s4 + 3);
            M2C_FIELD(temp_s2_2, void **, 0x1C) = temp_s0_3;
            func_8005A7B8(2, 2);
            var_s5_2 = temp_s0_3;
            temp_s1_2 = func_8005B0E4(0x140, port_D_8009A314) - 0xA0;
            temp_s3_2 = temp_s1_2 - 5;
loop_22:
            temp_a0_3 = port_D_800A35EC;
            port_D_800A35EC = temp_a0_3 + 1;
            temp_v1_8 = port_D_800A3678 + (temp_a0_3 * 0x24);
            M2C_FIELD(temp_v1_8, s8 *, 4) = 0;
            M2C_FIELD(temp_v1_8, s8 *, 3) = 0;
            M2C_FIELD(temp_v1_8, s8 *, 2) = 0;
            temp_a0_4 = port_D_800A37BC;
            M2C_FIELD(temp_v1_8, s16 *, 0x12) = 0;
            M2C_FIELD(temp_v1_8, s16 *, 0x14) = 0;
            M2C_FIELD(temp_v1_8, s32 *, 0x1C) = 0;
            M2C_FIELD(temp_v1_8, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_v1_8, s16 *, 0) = 0;
            M2C_FIELD(temp_v1_8, s16 *, 0xA) = 0;
            M2C_FIELD(temp_v1_8, s16 *, 6) = 0;
            M2C_FIELD(temp_v1_8, s16 *, 0xC) = 0;
            M2C_FIELD(temp_v1_8, s16 *, 8) = 0;
            M2C_FIELD(temp_v1_8, s16 *, 0xE) = 0;
            M2C_FIELD(temp_v1_8, s16 *, 0x10) = 0;
            M2C_FIELD(temp_v1_8, s16 *, 0x1A) = 0;
            port_D_800A37BC = temp_a0_4 + 1;
            temp_v1_9 = port_D_800A3654 + (temp_a0_4 * 0xC);
            M2C_FIELD(temp_v1_8, void **, 0x20) = temp_v1_9;
            M2C_FIELD(temp_v1_9, s8 *, 0) = 0;
            M2C_FIELD(temp_v1_9, s8 *, 3) = 0;
            M2C_FIELD(temp_v1_9, s32 *, 4) = 0;
            temp_s0_4 = M2C_FIELD(temp_v1_8, void **, 0x20);
            M2C_FIELD(temp_v1_8, s16 *, 0x14) = (s16) (((s8) sp20 * 0x4C) + 5);
            M2C_FIELD(temp_v1_8, s16 *, 0x1A) = 1;
            M2C_FIELD(temp_v1_8, s16 *, 0x12) = temp_s3_2;
            M2C_FIELD(temp_s0_4, s8 *, 2) = 2;
            M2C_FIELD(temp_s0_4, s8 *, 1) = 2;
            M2C_FIELD(temp_s0_4, s8 *, 3) = 0;
            if ((var_s7_3 << 0x18) != 0) {
                M2C_FIELD(temp_v1_8, s16 *, 0x12) = (s16) (func_8005A8E0(port_D_8009A314) + temp_s1_2);
                M2C_FIELD(temp_v1_8, s16 *, 0) = 5;
                M2C_FIELD(temp_s0_4, s32 *, 8) = 1;
            } else {
                M2C_FIELD(temp_v1_8, s16 *, 0x12) = temp_s3_2;
                M2C_FIELD(temp_s0_4, s32 *, 8) = (s32) port_D_8009A314;
            }
            M2C_FIELD(var_s5_2, void **, 0x1C) = temp_v1_8;
            temp_v0_9 = var_s7_3 + 1;
            var_s7_3 = temp_v0_9;
            var_s5_2 = temp_v1_8;
            if (temp_v0_9 < 2) {
                goto loop_22;
            }
            var_s7_4 = 0;
loop_27:
            var_s2 = 0;
            var_a2_2 = 2;
            var_a3 = var_s7_4 == 0;
loop_28:
            temp_a0_5 = port_D_800A35EC;
            port_D_800A35EC = temp_a0_5 + 1;
            temp_v1_10 = port_D_800A3678 + (temp_a0_5 * 0x24);
            M2C_FIELD(temp_v1_10, s8 *, 4) = 0;
            M2C_FIELD(temp_v1_10, s8 *, 3) = 0;
            M2C_FIELD(temp_v1_10, s8 *, 2) = 0;
            temp_a0_6 = port_D_800A37BC;
            M2C_FIELD(temp_v1_10, s16 *, 0x12) = 0;
            M2C_FIELD(temp_v1_10, s16 *, 0x14) = 0;
            M2C_FIELD(temp_v1_10, s32 *, 0x1C) = 0;
            M2C_FIELD(temp_v1_10, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_v1_10, s16 *, 0) = 0;
            M2C_FIELD(temp_v1_10, s16 *, 0xA) = 0;
            M2C_FIELD(temp_v1_10, s16 *, 6) = 0;
            M2C_FIELD(temp_v1_10, s16 *, 0xC) = 0;
            M2C_FIELD(temp_v1_10, s16 *, 8) = 0;
            M2C_FIELD(temp_v1_10, s16 *, 0xE) = 0;
            M2C_FIELD(temp_v1_10, s16 *, 0x10) = 0;
            M2C_FIELD(temp_v1_10, s16 *, 0x1A) = 0;
            port_D_800A37BC = temp_a0_6 + 1;
            temp_v1_11 = port_D_800A3654 + (temp_a0_6 * 0xC);
            M2C_FIELD(temp_v1_10, void **, 0x20) = temp_v1_11;
            M2C_FIELD(temp_v1_11, s8 *, 0) = 0;
            M2C_FIELD(temp_v1_11, s8 *, 3) = 0;
            M2C_FIELD(temp_v1_11, s32 *, 4) = 0;
            M2C_FIELD(temp_v1_10, s16 *, 0x1A) = 1;
            M2C_FIELD(temp_v1_10, s16 *, 0x12) = (s16) (((var_s7_4 * 2) - 1) * 0x3F);
            temp_v0_10 = M2C_FIELD((sp + var_s2), u8 *, 0x18);
            temp_v1_12 = var_s2 + 1;
            var_s2 = temp_v1_12;
            temp_s0_5 = M2C_FIELD(temp_v1_10, void **, 0x20);
            M2C_FIELD(temp_v1_10, s16 *, 0x14) = (s16) ((s8) temp_v0_10 + ((s8) sp20 * 0x4C));
            M2C_FIELD(temp_s0_5, s8 *, 2) = 2;
            M2C_FIELD(temp_s0_5, s8 *, 3) = var_a3;
            M2C_FIELD(temp_s0_5, s8 *, 1) = 2;
            M2C_FIELD(var_s5_2, void **, 0x1C) = temp_v1_10;
            var_s5_2 = temp_v1_10;
            if (temp_v1_12 < 7) {
                goto loop_28;
            }
            temp_v0_11 = var_s7_4 + 1;
            var_s7_4 = temp_v0_11;
            if (temp_v0_11 < 2) {
                goto loop_27;
            }
            temp_v1_13 = (s8) sp20 * 4;
            var_s5_3 = (*(M2C_UNK *)(port_D_800A37D8 + (temp_v1_13)));
            var_a1 = 2 - temp_v1_13;
            if (var_s5_3 != NULL) {
                var_a3 = (s8) sp20 * 0x140;
                var_a2_2 = ((s8) sp20 * 2) - 1;
                temp_a0_7 = var_a1 << 0x18;
                var_a1 = 0xA0;
                do {
                    M2C_FIELD(var_s5_3, s8 *, 5) = 1;
                    M2C_FIELD(var_s5_3, s16 *, 0xA) = 0xA0;
                    temp_v1_14 = sp40 >> 0x18;
                    M2C_FIELD(var_s5_3, s16 *, 8) = (s16) temp_v1_14;
                    M2C_FIELD(var_s5_3, s16 *, 0xE) = (s16) (temp_a0_7 >> 0x18);
                    M2C_FIELD(var_s5_3, s16 *, 0xC) = (s16) temp_v1_14;
                    M2C_FIELD(var_s5_3, s16 *, 6) = (s16) (var_a3 + (var_a2_2 * (M2C_FIELD(var_s5_3, s16 *, 0x12) + 0xA2)));
                    var_s5_3 = M2C_FIELD(var_s5_3, void **, 0x1C);
                } while (var_s5_3 != NULL);
            }
            var_s4_2 = 0;
            func_80062910(sp20, var_a1, var_a2_2, var_a3);
            var_s7_5 = 0;
            temp_fp = sp40 >> 0x18;
            temp_s3_3 = (s8) sp20 * 4;
            sp48 = (s32) (s8) sp20;
loop_34:
            switch (var_s7_5) {                     /* irregular */
            default:
                var_t4 = 3;
                if (var_s7_5 != 2) {

                } else {
                    sp30 = 2;
block_43:
                    sp38 = var_t4;
                }
                break;
            case 0:
                sp30 = 2;
                sp38 = 0;
                break;
            case 1:
                var_t4 = 1;
                sp30 = 6;
                goto block_43;
            }
            temp_v1_15 = port_D_800A35EC;
            port_D_800A35EC = temp_v1_15 + 1;
            temp_s0_6 = port_D_800A3678 + (temp_v1_15 * 0x24);
            M2C_FIELD(temp_s0_6, s16 *, 0x12) = 0;
            M2C_FIELD(temp_s0_6, s16 *, 0x14) = 0;
            M2C_FIELD(temp_s0_6, s32 *, 0x1C) = 0;
            M2C_FIELD(temp_s0_6, s8 *, 4) = 0;
            M2C_FIELD(temp_s0_6, s8 *, 3) = 0;
            M2C_FIELD(temp_s0_6, s8 *, 2) = 0;
            M2C_FIELD(temp_s0_6, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_s0_6, s16 *, 0) = 1;
            M2C_FIELD(temp_s0_6, s16 *, 0xA) = 0;
            M2C_FIELD(temp_s0_6, s16 *, 6) = 0;
            M2C_FIELD(temp_s0_6, s16 *, 0xC) = (s16) temp_fp;
            M2C_FIELD(temp_s0_6, s16 *, 8) = (s16) temp_fp;
            M2C_FIELD(temp_s0_6, u16 *, 0x16) = 0x68U;
            M2C_FIELD(temp_s0_6, s16 *, 0xE) = 0;
            M2C_FIELD(temp_s0_6, s16 *, 0x10) = 0;
            M2C_FIELD(temp_s0_6, u16 *, 0x18) = (u16) sp30;
            temp_v0_12 = func_80057CCC(1);
            SetPolyFT4(temp_v0_12);
            SetShadeTex(temp_v0_12, 0);
            M2C_FIELD(temp_v0_12, s8 *, 4) = 0x80;
            M2C_FIELD(temp_v0_12, s8 *, 5) = 0x80;
            M2C_FIELD(temp_v0_12, s8 *, 6) = 0x80;
            SetSemiTrans(temp_v0_12, 0);
            M2C_FIELD(temp_s0_6, void **, 0x20) = temp_v0_12;
            M2C_FIELD(temp_s0_6, s16 *, 0x1A) = 2;
            if ((var_s7_5 << 0x18) == 0) {
                (*(M2C_UNK *)(port_D_800A3888 + (temp_s3_3))) = temp_s0_6;
            } else {
                M2C_FIELD(var_s5_3, void **, 0x1C) = temp_s0_6;
            }
            if (sp48 != 0) {
                M2C_FIELD(temp_s0_6, s16 *, 6) = 0x140;
            } else {
                M2C_FIELD(temp_s0_6, s16 *, 6) = -0x140;
            }
            temp_s2_3 = M2C_FIELD(temp_s0_6, void **, 0x20);
            M2C_FIELD(temp_s0_6, s16 *, 0x12) = 0x78;
            M2C_FIELD(temp_s0_6, s16 *, 0x14) = (s16) (M2C_FIELD((*(M2C_UNK *)(port_D_800A37D8 + (temp_s3_3))), u16 *, 0x14) + (var_s4_2 + 0x3A));
            if (var_s7_5 == 1) {
                temp_s0_7 = M2C_FIELD(temp_s0_6, u16 *, 0x16);
                M2C_FIELD(temp_s2_3, s16 *, 0xE) = GetClut(port_D_8009AEA4, port_D_8009AEA6);
                M2C_FIELD(temp_s2_3, s16 *, 0x16) = GetTPage(port_D_8009AEAC, 3, port_D_8009AEA0, port_D_8009AEA2);
                M2C_FIELD(temp_s2_3, u8 *, 0xC) = (u8) port_D_8009AEA8;
                M2C_FIELD(temp_s2_3, s8 *, 0xD) = (s8) (port_D_8009AEAA + (u16) sp38);
                M2C_FIELD(temp_s2_3, s8 *, 0x14) = (s8) (port_D_8009AEA8 + temp_s0_7);
                M2C_FIELD(temp_s2_3, s8 *, 0x15) = (s8) (port_D_8009AEAA + (u16) sp38);
                M2C_FIELD(temp_s2_3, u8 *, 0x1C) = (u8) port_D_8009AEA8;
                M2C_FIELD(temp_s2_3, s8 *, 0x1D) = (s8) (port_D_8009AEAA + (u16) sp38 + 1);
                M2C_FIELD(temp_s2_3, s8 *, 0x24) = (s8) (port_D_8009AEA8 + temp_s0_7);
                var_v0 = port_D_8009AEAA + (u16) sp38 + 1;
            } else {
                temp_s0_8 = M2C_FIELD(temp_s0_6, u16 *, 0x16);
                temp_s1_3 = M2C_FIELD(temp_s0_6, u16 *, 0x18);
                M2C_FIELD(temp_s2_3, s16 *, 0xE) = GetClut(port_D_8009AEA4, port_D_8009AEA6);
                M2C_FIELD(temp_s2_3, s16 *, 0x16) = GetTPage(port_D_8009AEAC, 3, port_D_8009AEA0, port_D_8009AEA2);
                M2C_FIELD(temp_s2_3, u8 *, 0xC) = (u8) port_D_8009AEA8;
                M2C_FIELD(temp_s2_3, s8 *, 0xD) = (s8) (port_D_8009AEAA + (u16) sp38);
                M2C_FIELD(temp_s2_3, s8 *, 0x14) = (s8) (port_D_8009AEA8 + temp_s0_8);
                M2C_FIELD(temp_s2_3, s8 *, 0x15) = (s8) (port_D_8009AEAA + (u16) sp38);
                M2C_FIELD(temp_s2_3, u8 *, 0x1C) = (u8) port_D_8009AEA8;
                M2C_FIELD(temp_s2_3, s8 *, 0x1D) = (s8) (port_D_8009AEAA + (u16) sp38 + temp_s1_3);
                M2C_FIELD(temp_s2_3, s8 *, 0x24) = (s8) (port_D_8009AEA8 + temp_s0_8);
                var_v0 = port_D_8009AEAA + (u16) sp38 + temp_s1_3;
            }
            M2C_FIELD(temp_s2_3, s8 *, 0x25) = var_v0;
            var_s5_3 = temp_s0_6;
            temp_v0_13 = var_s7_5 + 1;
            var_s7_5 = temp_v0_13;
            var_s4_2 += (s16) M2C_FIELD(temp_s0_6, u16 *, 0x18);
            if (temp_v0_13 < 3) {
                goto loop_34;
            }
            var_s7_6 = 0;
            temp_s4_2 = sp40 >> 0x18;
            sp50 = (s8) sp20 * 4;
loop_55:
            temp_v1_16 = port_D_800A35EC;
            port_D_800A35EC = temp_v1_16 + 1;
            temp_s0_9 = port_D_800A3678 + (temp_v1_16 * 0x24);
            M2C_FIELD(temp_s0_9, s16 *, 0) = 1;
            M2C_FIELD(temp_s0_9, s16 *, 0x12) = 0;
            M2C_FIELD(temp_s0_9, s16 *, 0x14) = 0;
            M2C_FIELD(temp_s0_9, void **, 0x1C) = NULL;
            M2C_FIELD(temp_s0_9, s8 *, 4) = 0;
            M2C_FIELD(temp_s0_9, s8 *, 3) = 0;
            M2C_FIELD(temp_s0_9, s8 *, 2) = 0;
            M2C_FIELD(temp_s0_9, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_s0_9, s16 *, 0xA) = 0;
            M2C_FIELD(temp_s0_9, s16 *, 6) = 0;
            M2C_FIELD(temp_s0_9, s16 *, 0xC) = (s16) temp_s4_2;
            M2C_FIELD(temp_s0_9, s16 *, 8) = (s16) temp_s4_2;
            M2C_FIELD(temp_s0_9, s16 *, 0x16) = 0xE;
            M2C_FIELD(temp_s0_9, s16 *, 0x18) = 0x32;
            M2C_FIELD(temp_s0_9, s16 *, 0xE) = 0;
            M2C_FIELD(temp_s0_9, s16 *, 0x10) = 0;
            temp_v0_14 = func_80057CCC(1);
            SetPolyFT4(temp_v0_14);
            SetShadeTex(temp_v0_14, 0);
            M2C_FIELD(temp_v0_14, s8 *, 4) = 0x80;
            M2C_FIELD(temp_v0_14, s8 *, 5) = 0x80;
            M2C_FIELD(temp_v0_14, s8 *, 6) = 0x80;
            SetSemiTrans(temp_v0_14, 0);
            M2C_FIELD(temp_s0_9, void **, 0x20) = temp_v0_14;
            M2C_FIELD(temp_s0_9, s16 *, 0x1A) = 2;
            if ((s8) sp20 != 0) {
                M2C_FIELD(temp_s0_9, s16 *, 6) = 0x140;
            } else {
                M2C_FIELD(temp_s0_9, s16 *, 6) = -0x140;
            }
            M2C_FIELD(temp_s0_9, s16 *, 0x12) = (s16) (((s32) (var_s7_6 << 0x18) >> 0x13) + 0xFA);
            M2C_FIELD(temp_s0_9, s16 *, 0x14) = (s16) (M2C_FIELD((*(M2C_UNK *)(port_D_800A37D8 + (sp50))), u16 *, 0x14) + 7);
            temp_s2_4 = M2C_FIELD(temp_s0_9, void **, 0x20);
            M2C_FIELD(temp_s2_4, s16 *, 0xE) = GetClut(M2C_FIELD(port_D_8009AEB2, u16 *, 0), M2C_FIELD(port_D_8009AEB2, u16 *, 2));
            M2C_FIELD(temp_s2_4, s16 *, 0x16) = GetTPage(M2C_FIELD(port_D_8009AEB2, u16 *, 8), 0, M2C_FIELD(port_D_8009AEB2, u16 *, -4), M2C_FIELD(port_D_8009AEB2, u16 *, -2));
            M2C_FIELD(temp_s2_4, s8 *, 0xC) = (s8) M2C_FIELD(port_D_8009AEB2, u16 *, 4);
            M2C_FIELD(temp_s2_4, s8 *, 0xD) = (s8) (M2C_FIELD(port_D_8009AEB2, u8 *, 6) + 6);
            M2C_FIELD(temp_s2_4, s8 *, 0x14) = (s8) M2C_FIELD(port_D_8009AEB2, u16 *, 4);
            M2C_FIELD(temp_s2_4, s8 *, 0x15) = (s8) (u16) M2C_FIELD(port_D_8009AEB2, u8 *, 6);
            M2C_FIELD(temp_s2_4, s8 *, 0x1C) = (s8) ((u8) M2C_FIELD(port_D_8009AEB2, u16 *, 4) + 0x32);
            M2C_FIELD(temp_s2_4, s8 *, 0x1D) = (s8) (M2C_FIELD(port_D_8009AEB2, u8 *, 6) + 6);
            M2C_FIELD(temp_s2_4, s8 *, 0x24) = (s8) ((u8) M2C_FIELD(port_D_8009AEB2, u16 *, 4) + 0x32);
            temp_v0_15 = var_s7_6 + 1;
            var_s7_6 = temp_v0_15;
            M2C_FIELD(temp_s2_4, s8 *, 0x25) = (s8) (u16) M2C_FIELD(port_D_8009AEB2, u8 *, 6);
            M2C_FIELD(var_s5_3, void **, 0x1C) = temp_s0_9;
            var_s5_3 = temp_s0_9;
            if (temp_v0_15 < 2) {
                goto loop_55;
            }
            temp_a0_8 = port_D_800A35EC;
            port_D_800A35EC = temp_a0_8 + 1;
            temp_v1_17 = port_D_800A3678 + (temp_a0_8 * 0x24);
            M2C_FIELD(temp_v1_17, s8 *, 4) = 0;
            M2C_FIELD(temp_v1_17, s8 *, 3) = 0;
            M2C_FIELD(temp_v1_17, s8 *, 2) = 0;
            temp_a0_9 = port_D_800A37BC;
            M2C_FIELD(temp_v1_17, s16 *, 0x12) = 0;
            M2C_FIELD(temp_v1_17, s16 *, 0x14) = 0;
            M2C_FIELD(temp_v1_17, s32 *, 0x1C) = 0;
            M2C_FIELD(temp_v1_17, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_v1_17, s16 *, 0) = 0;
            M2C_FIELD(temp_v1_17, s16 *, 0xA) = 0;
            M2C_FIELD(temp_v1_17, s16 *, 6) = 0;
            M2C_FIELD(temp_v1_17, s16 *, 0xE) = 0;
            M2C_FIELD(temp_v1_17, s16 *, 0x10) = 0;
            M2C_FIELD(temp_v1_17, s16 *, 0x1A) = 0;
            temp_v0_16 = sp40 >> 0x18;
            M2C_FIELD(temp_v1_17, s16 *, 0xC) = (s16) temp_v0_16;
            M2C_FIELD(temp_v1_17, s16 *, 8) = (s16) temp_v0_16;
            port_D_800A37BC = temp_a0_9 + 1;
            temp_v1_18 = port_D_800A3654 + (temp_a0_9 * 0xC);
            M2C_FIELD(temp_v1_17, void **, 0x20) = temp_v1_18;
            M2C_FIELD(temp_v1_18, s8 *, 0) = 0;
            M2C_FIELD(temp_v1_18, s8 *, 3) = 0;
            M2C_FIELD(temp_v1_18, s32 *, 4) = 0;
            if ((sp20 << 0x18) != 0) {
                M2C_FIELD(temp_v1_17, s16 *, 6) = 0x140;
            } else {
                M2C_FIELD(temp_v1_17, s16 *, 6) = -0x140;
            }
            M2C_FIELD(temp_v1_17, s16 *, 0x12) = 8;
            temp_s0_10 = (s8) sp20 * 4;
            temp_t0 = temp_s0_10 + port_D_800A37D8;
            var_s7_7 = 0;
            M2C_FIELD(temp_v1_17, s16 *, 0x14) = (s16) (M2C_FIELD(*temp_t0, u16 *, 0x14) + 5);
            temp_s2_5 = sp40 >> 0x18;
            func_80067EA4(temp_v1_17, 2, 2, port_D_8009AC08, 0, 1);
            M2C_FIELD(var_s5_3, void **, 0x1C) = temp_v1_17;
            var_s5_4 = temp_v1_17;
            (*(M2C_UNK *)(port_D_800A3A84 + (temp_s0_10))) = var_s5_4;
loop_63:
            temp_a0_10 = port_D_800A35EC;
            port_D_800A35EC = temp_a0_10 + 1;
            temp_v1_19 = port_D_800A3678 + (temp_a0_10 * 0x24);
            M2C_FIELD(temp_v1_19, s8 *, 4) = 0;
            M2C_FIELD(temp_v1_19, s8 *, 3) = 0;
            M2C_FIELD(temp_v1_19, s8 *, 2) = 0;
            temp_a0_11 = port_D_800A37BC;
            M2C_FIELD(temp_v1_19, s16 *, 0x12) = 0;
            M2C_FIELD(temp_v1_19, s16 *, 0x14) = 0;
            M2C_FIELD(temp_v1_19, void **, 0x1C) = NULL;
            M2C_FIELD(temp_v1_19, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_v1_19, s16 *, 0) = 0;
            M2C_FIELD(temp_v1_19, s16 *, 0xA) = 0;
            M2C_FIELD(temp_v1_19, s16 *, 6) = 0;
            M2C_FIELD(temp_v1_19, s16 *, 0xC) = (s16) temp_s2_5;
            M2C_FIELD(temp_v1_19, s16 *, 8) = (s16) temp_s2_5;
            M2C_FIELD(temp_v1_19, s16 *, 0xE) = 0;
            M2C_FIELD(temp_v1_19, s16 *, 0x10) = 0;
            M2C_FIELD(temp_v1_19, s16 *, 0x1A) = 0;
            port_D_800A37BC = temp_a0_11 + 1;
            temp_v1_20 = port_D_800A3654 + (temp_a0_11 * 0xC);
            M2C_FIELD(temp_v1_19, void **, 0x20) = temp_v1_20;
            M2C_FIELD(temp_v1_20, s8 *, 0) = 0;
            M2C_FIELD(temp_v1_20, s8 *, 3) = 0;
            M2C_FIELD(temp_v1_20, s32 *, 4) = 0;
            if ((s8) sp20 != 0) {
                M2C_FIELD(temp_v1_19, s16 *, 6) = 0x140;
            } else {
                M2C_FIELD(temp_v1_19, s16 *, 6) = -0x140;
            }
            var_v0_2 = 0x46;
            if (var_s7_7 != 0) {
                if ((var_s7_7 >= 0) && (var_s7_7 < 3)) {
                    var_v0_2 = (var_s7_7 << 5) + 0xD5;
                    goto block_70;
                }
            } else {
block_70:
                M2C_FIELD(temp_v1_19, s16 *, 0x12) = var_v0_2;
                M2C_FIELD(temp_v1_19, s16 *, 0x14) = (s16) (M2C_FIELD(*temp_t0, u16 *, 0x14) + 0x3C);
            }
            func_80067EA4(temp_v1_19, 2, 2, (*(M2C_UNK *)(port_D_8009AC10 + (((s32) (var_s7_7 << 0x18) >> 0x16)))), 0, 1);
            M2C_FIELD(var_s5_4, void **, 0x1C) = temp_v1_19;
            temp_v0_17 = var_s7_7 + 1;
            var_s7_7 = temp_v0_17;
            var_s5_4 = temp_v1_19;
            if (temp_v0_17 < 3) {
                goto loop_63;
            }
            temp_v1_21 = port_D_800A35EC;
            port_D_800A35EC = temp_v1_21 + 1;
            temp_s0_11 = port_D_800A3678 + (temp_v1_21 * 0x24);
            M2C_FIELD(temp_s0_11, s16 *, 0x12) = 0;
            M2C_FIELD(temp_s0_11, s16 *, 0x14) = 0;
            M2C_FIELD(temp_s0_11, s32 *, 0x1C) = 0;
            M2C_FIELD(temp_s0_11, s8 *, 4) = 0;
            M2C_FIELD(temp_s0_11, s8 *, 3) = 0;
            M2C_FIELD(temp_s0_11, s8 *, 2) = 0;
            M2C_FIELD(temp_s0_11, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_s0_11, s16 *, 0) = 2;
            M2C_FIELD(temp_s0_11, s16 *, 6) = 0;
            M2C_FIELD(temp_s0_11, s16 *, 0xA) = 0;
            M2C_FIELD(temp_s0_11, s16 *, 0xE) = 0;
            M2C_FIELD(temp_s0_11, s16 *, 0x10) = 0;
            M2C_FIELD(temp_s0_11, s16 *, 0x16) = 6;
            M2C_FIELD(temp_s0_11, s16 *, 0x18) = 8;
            M2C_FIELD(temp_s0_11, s8 *, 2) = 0x80;
            M2C_FIELD(temp_s0_11, s8 *, 3) = 0;
            M2C_FIELD(temp_s0_11, s8 *, 4) = 0;
            temp_s2_6 = sp40 >> 0x18;
            M2C_FIELD(temp_s0_11, s16 *, 8) = (s16) temp_s2_6;
            M2C_FIELD(temp_s0_11, s16 *, 0xC) = (s16) temp_s2_6;
            temp_v0_18 = func_80057D50(1);
            M2C_FIELD(temp_s0_11, void **, 0x20) = temp_v0_18;
            SetPolyF4(temp_v0_18);
            SetSemiTrans(temp_v0_18, 0);
            M2C_FIELD(temp_v0_18, s16 *, 0xA) = (s16) temp_s2_6;
            M2C_FIELD(temp_v0_18, s16 *, 0xE) = (s16) temp_s2_6;
            temp_s2_7 = temp_s2_6 + 8;
            M2C_FIELD(temp_v0_18, s8 *, 4) = 0x80;
            M2C_FIELD(temp_v0_18, s8 *, 5) = 0;
            M2C_FIELD(temp_v0_18, s8 *, 6) = 0;
            M2C_FIELD(temp_v0_18, s16 *, 8) = 0;
            M2C_FIELD(temp_v0_18, s16 *, 0xC) = 6;
            M2C_FIELD(temp_v0_18, s16 *, 0x10) = 0;
            M2C_FIELD(temp_v0_18, s16 *, 0x12) = temp_s2_7;
            M2C_FIELD(temp_v0_18, s16 *, 0x14) = 6;
            M2C_FIELD(temp_v0_18, s16 *, 0x16) = temp_s2_7;
            M2C_FIELD(temp_s0_11, s16 *, 0x1A) = 0;
            if ((sp20 << 0x18) != 0) {
                M2C_FIELD(temp_s0_11, s16 *, 6) = 0x140;
            } else {
                M2C_FIELD(temp_s0_11, s16 *, 6) = -0x140;
            }
            M2C_FIELD(temp_s0_11, s16 *, 0x12) = 0xA9;
            temp_a0_12 = (s8) sp20 * 4;
            var_s7_8 = 0;
            temp_s2_8 = sp40 >> 0x18;
            temp_s3_4 = temp_s2_8 + 1;
            sp58 = (s32) (s8) sp20;
            M2C_FIELD(temp_s0_11, s16 *, 0x14) = (s16) (M2C_FIELD((*(M2C_UNK *)(port_D_800A37D8 + (temp_a0_12))), u16 *, 0x14) + 0x3B);
            M2C_FIELD(var_s5_4, void **, 0x1C) = temp_s0_11;
            var_s5 = temp_s0_11;
            (*(M2C_UNK *)(port_D_800A37FC + (temp_a0_12))) = var_s5;
loop_76:
            temp_v1_22 = port_D_800A35EC;
            port_D_800A35EC = temp_v1_22 + 1;
            temp_s0_12 = port_D_800A3678 + (temp_v1_22 * 0x24);
            M2C_FIELD(temp_s0_12, s8 *, 2) = 0;
            M2C_FIELD(temp_s0_12, s16 *, 0x12) = 0;
            M2C_FIELD(temp_s0_12, s16 *, 0x14) = 0;
            M2C_FIELD(temp_s0_12, s32 *, 0x1C) = 0;
            M2C_FIELD(temp_s0_12, s8 *, 4) = 0;
            M2C_FIELD(temp_s0_12, s8 *, 3) = 0;
            M2C_FIELD(temp_s0_12, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_s0_12, s16 *, 0) = 2;
            M2C_FIELD(temp_s0_12, s16 *, 6) = 0;
            M2C_FIELD(temp_s0_12, s16 *, 0xA) = 0;
            M2C_FIELD(temp_s0_12, s16 *, 8) = (s16) temp_s2_8;
            M2C_FIELD(temp_s0_12, s16 *, 0xC) = (s16) temp_s2_8;
            M2C_FIELD(temp_s0_12, s16 *, 0xE) = 0;
            M2C_FIELD(temp_s0_12, s16 *, 0x10) = 0;
            M2C_FIELD(temp_s0_12, s16 *, 0x16) = 0xB;
            M2C_FIELD(temp_s0_12, s16 *, 0x18) = 1;
            M2C_FIELD(temp_s0_12, s8 *, 2) = 0x80;
            M2C_FIELD(temp_s0_12, s8 *, 3) = 0;
            M2C_FIELD(temp_s0_12, s8 *, 4) = 0;
            temp_v0_19 = func_80057D50(1);
            M2C_FIELD(temp_s0_12, void **, 0x20) = temp_v0_19;
            SetPolyF4(temp_v0_19);
            SetSemiTrans(temp_v0_19, 0);
            M2C_FIELD(temp_v0_19, s8 *, 4) = 0x80;
            M2C_FIELD(temp_v0_19, s8 *, 5) = 0;
            M2C_FIELD(temp_v0_19, s8 *, 6) = 0;
            M2C_FIELD(temp_v0_19, s16 *, 8) = 0;
            M2C_FIELD(temp_v0_19, s16 *, 0xA) = (s16) temp_s2_8;
            M2C_FIELD(temp_v0_19, s16 *, 0xC) = 0xB;
            M2C_FIELD(temp_v0_19, s16 *, 0xE) = (s16) temp_s2_8;
            M2C_FIELD(temp_v0_19, s16 *, 0x10) = 0;
            M2C_FIELD(temp_v0_19, s16 *, 0x12) = temp_s3_4;
            M2C_FIELD(temp_v0_19, s16 *, 0x14) = 0xB;
            M2C_FIELD(temp_v0_19, s16 *, 0x16) = temp_s3_4;
            M2C_FIELD(temp_s0_12, s16 *, 0x1A) = 0;
            if (sp58 != 0) {
                M2C_FIELD(temp_s0_12, s16 *, 6) = 0x140;
            } else {
                M2C_FIELD(temp_s0_12, s16 *, 6) = -0x140;
            }
            var_v0_3 = 0xFC;
            if ((var_s7_8 << 0x18) == 0) {
                var_v0_3 = 0x11C;
            }
            M2C_FIELD(temp_s0_12, s16 *, 0x12) = var_v0_3;
            temp_v0_20 = var_s7_8 + 1;
            var_s7_8 = temp_v0_20;
            M2C_FIELD(temp_s0_12, s16 *, 0x14) = (s16) (M2C_FIELD((*(M2C_UNK *)(port_D_800A37D8 + (temp_a0_12))), u16 *, 0x14) + 0x37);
            M2C_FIELD(var_s5, void **, 0x1C) = temp_s0_12;
            var_s5 = temp_s0_12;
            if (temp_v0_20 < 2) {
                goto loop_76;
            }
            var_s7_9 = 0;
            temp_s3_5 = sp40 >> 0x18;
            var_v0_4 = 0 << 0x18;
loop_83:
            var_fp = 0xFA;
            if (var_v0_4 == 0) {
                var_fp = 0x11A;
            }
            var_s2_2 = 0;
            sp60 = (s8) sp20 * 4;
loop_86:
            var_a1_2 = -3;
            if ((var_s2_2 << 0x18) != 0) {
                var_a1_2 = 3;
            }
            temp_v1_23 = port_D_800A35EC;
            port_D_800A35EC = temp_v1_23 + 1;
            temp_s0_13 = port_D_800A3678 + (temp_v1_23 * 0x24);
            M2C_FIELD(temp_s0_13, s8 *, 2) = 0;
            M2C_FIELD(temp_s0_13, s8 *, 3) = 0;
            M2C_FIELD(temp_s0_13, s16 *, 0x18) = 6;
            M2C_FIELD(temp_s0_13, s8 *, 4) = 0;
            M2C_FIELD(temp_s0_13, s8 *, 2) = 0xFF;
            M2C_FIELD(temp_s0_13, s16 *, 0x12) = 0;
            M2C_FIELD(temp_s0_13, s16 *, 0x14) = 0;
            M2C_FIELD(temp_s0_13, s32 *, 0x1C) = 0;
            M2C_FIELD(temp_s0_13, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_s0_13, s16 *, 0) = 8;
            M2C_FIELD(temp_s0_13, s16 *, 6) = 0;
            M2C_FIELD(temp_s0_13, s16 *, 0xA) = 0;
            M2C_FIELD(temp_s0_13, s16 *, 8) = (s16) temp_s3_5;
            M2C_FIELD(temp_s0_13, s16 *, 0xC) = (s16) temp_s3_5;
            M2C_FIELD(temp_s0_13, s16 *, 0xE) = 0;
            M2C_FIELD(temp_s0_13, s16 *, 0x10) = 0;
            M2C_FIELD(temp_s0_13, s16 *, 0x16) = var_a1_2;
            M2C_FIELD(temp_s0_13, s8 *, 3) = 0x80;
            M2C_FIELD(temp_s0_13, s8 *, 4) = 0x40;
            temp_v0_21 = func_80057D50(1, (s32) var_a1_2);
            M2C_FIELD(temp_s0_13, void **, 0x20) = temp_v0_21;
            SetPolyF3(temp_v0_21);
            SetSemiTrans(temp_v0_21, 0);
            M2C_FIELD(temp_v0_21, s8 *, 4) = 0xFF;
            M2C_FIELD(temp_v0_21, s8 *, 5) = 0x80;
            M2C_FIELD(temp_v0_21, s8 *, 6) = 0x40;
            M2C_FIELD(temp_s0_13, s16 *, 0x1A) = 0;
            if ((s8) sp20 != 0) {
                M2C_FIELD(temp_s0_13, s16 *, 6) = 0x140;
            } else {
                M2C_FIELD(temp_s0_13, s16 *, 6) = -0x140;
            }
            M2C_FIELD(temp_s0_13, s16 *, 0x12) = var_fp;
            var_fp += 0xF;
            temp_v0_22 = var_s2_2 + 1;
            var_s2_2 = temp_v0_22;
            M2C_FIELD(temp_s0_13, s16 *, 0x14) = (s16) (M2C_FIELD((*(M2C_UNK *)(port_D_800A37D8 + (sp60))), u16 *, 0x14) + 0x37);
            M2C_FIELD(var_s5, void **, 0x1C) = temp_s0_13;
            var_s5 = temp_s0_13;
            if (temp_v0_22 < 2) {
                goto loop_86;
            }
            temp_v0_23 = var_s7_9 + 1;
            var_s7_9 = temp_v0_23;
            var_v0_4 = var_s7_9 << 0x18;
            if (temp_v0_23 < 2) {
                goto loop_83;
            }
            var_s7_10 = 0;
            temp_s2_9 = sp40 >> 0x18;
            var_s4 = M2C_FIELD((*(M2C_UNK *)(port_D_800A37D8 + (((s32) (sp20 << 0x18) >> 0x16)))), s16 *, 0x14) + 0x3A;
loop_94:
            var_a1_3 = -3;
            if ((var_s7_10 << 0x18) != 0) {
                var_a1_3 = 3;
            }
            temp_v1_24 = port_D_800A35EC;
            port_D_800A35EC = temp_v1_24 + 1;
            temp_s0_14 = port_D_800A3678 + (temp_v1_24 * 0x24);
            M2C_FIELD(temp_s0_14, s8 *, 2) = 0;
            M2C_FIELD(temp_s0_14, s8 *, 3) = 0;
            M2C_FIELD(temp_s0_14, s16 *, 0x16) = 6;
            M2C_FIELD(temp_s0_14, s16 *, 0x12) = 0;
            M2C_FIELD(temp_s0_14, s16 *, 0x14) = 0;
            M2C_FIELD(temp_s0_14, s32 *, 0x1C) = 0;
            M2C_FIELD(temp_s0_14, s8 *, 4) = 0;
            M2C_FIELD(temp_s0_14, s16 *, 0x1A) = 0;
            M2C_FIELD(temp_s0_14, s16 *, 0) = 7;
            M2C_FIELD(temp_s0_14, s16 *, 6) = 0;
            M2C_FIELD(temp_s0_14, s16 *, 0xA) = 0;
            M2C_FIELD(temp_s0_14, s16 *, 8) = (s16) temp_s2_9;
            M2C_FIELD(temp_s0_14, s16 *, 0xC) = (s16) temp_s2_9;
            M2C_FIELD(temp_s0_14, s16 *, 0xE) = 0;
            M2C_FIELD(temp_s0_14, s16 *, 0x10) = 0;
            M2C_FIELD(temp_s0_14, s16 *, 0x18) = var_a1_3;
            M2C_FIELD(temp_s0_14, s8 *, 2) = 0xFF;
            M2C_FIELD(temp_s0_14, s8 *, 3) = 0x80;
            M2C_FIELD(temp_s0_14, s8 *, 4) = 0x40;
            temp_v0_24 = func_80057D50(1, (s32) var_a1_3);
            M2C_FIELD(temp_s0_14, void **, 0x20) = temp_v0_24;
            SetPolyF3(temp_v0_24);
            SetSemiTrans(temp_v0_24, 0);
            M2C_FIELD(temp_v0_24, s8 *, 4) = 0xFF;
            M2C_FIELD(temp_v0_24, s8 *, 5) = 0x80;
            M2C_FIELD(temp_v0_24, s8 *, 6) = 0x40;
            M2C_FIELD(temp_s0_14, s16 *, 0x1A) = 0;
            if ((sp20 << 0x18) != 0) {
                M2C_FIELD(temp_s0_14, s16 *, 6) = 0x140;
            } else {
                M2C_FIELD(temp_s0_14, s16 *, 6) = -0x140;
            }
            M2C_FIELD(temp_s0_14, s16 *, 0x12) = 0xAC;
            M2C_FIELD(temp_s0_14, s16 *, 0x14) = var_s4;
            M2C_FIELD(var_s5, void **, 0x1C) = temp_s0_14;
            var_s5 = temp_s0_14;
            temp_v0_25 = var_s7_10 + 1;
            var_s7_10 = temp_v0_25;
            var_s4 += 0xC;
            if (temp_v0_25 < 2) {
                goto loop_94;
            }
            temp_v0 = sp20 + 1;
            sp20 = temp_v0;
        } while (temp_v0 < (port_D_800A3644 + 1));
    }
    ListSetFieldsAndEnable(port_D_800A37F8, -0x140, 0, 4);
}
#undef sp20
#undef sp28
#undef sp30
#undef sp38
#undef sp40
#undef sp48
#undef sp50
#undef sp58
#undef sp60
#undef sp68
#undef sp
