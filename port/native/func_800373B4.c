/* Native body from m2c --valid-syntax of the retail asm. */
#include "port_m2c.h"

void func_800373B4(Car *arg0) {
    extern u8 port_D_8008D0F8 __asm__("D_8008D0F8");
    extern s32 port_D_800A2E4C __asm__("D_800A2E4C");
    extern s32 port_D_800A2E90 __asm__("D_800A2E90");
    extern s32 port_D_800A2E94 __asm__("D_800A2E94");
    extern s32 port_gSplitScreenMode __asm__("gSplitScreenMode");
    extern s32 port_D_800A2EAC __asm__("D_800A2EAC");
    extern s32 port_gSessionType __asm__("gSessionType");
    extern u8 port_D_800A2EDC __asm__("D_800A2EDC");
    extern u8 port_D_800A2EE0 __asm__("D_800A2EE0");
    extern u8 port_D_800A2F48 __asm__("D_800A2F48");
    extern s32 port_D_800A2F50 __asm__("D_800A2F50");
    extern s32 port_D_800A2F54 __asm__("D_800A2F54");
    extern u8 port_D_800A2F58 __asm__("D_800A2F58");
    extern s32 port_D_800A2F5C __asm__("D_800A2F5C");
    extern s32 port_D_800A2F84 __asm__("D_800A2F84");
    extern u8 port_D_800A3071 __asm__("D_800A3071");
    extern u8 port_D_800A3320 __asm__("D_800A3320");
    extern void * port_gPlayerCar __asm__("gPlayerCar");
    extern s8 port_D_800A3564 __asm__("D_800A3564");
    extern s32 port_D_800A3598 __asm__("D_800A3598");
    extern void * port_D_800A35E0 __asm__("D_800A35E0");
    extern u8 port_D_800A3670 __asm__("D_800A3670");
    extern s32 port_D_800A36A4 __asm__("D_800A36A4");
    extern void * port_D_800A3728 __asm__("D_800A3728");
    extern u8 port_D_800A372C __asm__("D_800A372C");
    extern s8 port_D_800A3764 __asm__("D_800A3764");
    extern s32 port_D_800A37C0 __asm__("D_800A37C0");
    extern void * port_gCarList __asm__("gCarList");
    extern s16 port_D_800A3910 __asm__("D_800A3910");
    extern void * port_gCrashCar __asm__("gCrashCar");
    extern s32 port_gCosTable __asm__("gCosTable");
    extern s32 port_gSinTable __asm__("gSinTable");
    extern void * port_D_800A3A64 __asm__("D_800A3A64");
    extern u8 port_D_800AE154 __asm__("D_800AE154");
    extern u8 port_D_800B1EA8 __asm__("D_800B1EA8");
    extern s32 port_gTrackSectionCount __asm__("gTrackSectionCount");
    extern s32 port_gTrackSections __asm__("gTrackSections");
    extern void port_CarResetMotionCounters(void *) __asm__("CarResetMotionCounters");
    extern s32 port_func_800A2CE0 __asm__("func_800A2CE0");
    s32 port_frame[50];
#define sp10 ((s32 *)((u8 *)port_frame + 0x10))
#define sp14 (*(s32 *)((u8 *)port_frame + 0x14))
#define sp18 (*(s32 *)((u8 *)port_frame + 0x18))
#define sp20 (*(s32 *)((u8 *)port_frame + 0x20))
#define sp24 (*(s32 *)((u8 *)port_frame + 0x24))
#define sp28 (*(s32 *)((u8 *)port_frame + 0x28))
#define sp2C (*(s32 *)((u8 *)port_frame + 0x2C))
#define sp30 (*(s32 *)((u8 *)port_frame + 0x30))
#define sp34 (*(s32 *)((u8 *)port_frame + 0x34))
#define sp38 (*(s32 *)((u8 *)port_frame + 0x38))
#define sp40 (*(s32 *)((u8 *)port_frame + 0x40))
#define sp48 (*(s32 *)((u8 *)port_frame + 0x48))
#define sp50 (*(u8 *)((u8 *)port_frame + 0x50))
#define sp58 (*(u8 *)((u8 *)port_frame + 0x58))
#define sp60 (*(s32 *)((u8 *)port_frame + 0x60))
#define sp68 (*(u8 *)((u8 *)port_frame + 0x68))
#define sp70 (*(u8 *)((u8 *)port_frame + 0x70))
#define sp ((u8 *)port_frame)
    M2C_UNK (*temp_v1_18)(void *, s16);
    s16 temp_a0_11;
    s16 temp_a2;
    s16 temp_a2_4;
    s16 temp_lo;
    s16 temp_v1_14;
    s16 var_a1_9;
    s16 var_v0_4;
    s32 *temp_a1_2;
    s32 *var_a0_3;
    s32 *var_a0_4;
    s32 temp_a0_12;
    s32 temp_a0_13;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a1_6;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_a2_5;
    s32 temp_a3;
    s32 temp_a3_2;
    s32 temp_hi;
    s32 temp_lo_2;
    s32 temp_s0;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s0_5;
    s32 temp_s0_6;
    s32 temp_s0_7;
    s32 temp_s0_8;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_v0_13;
    s32 temp_v0_18;
    s32 temp_v0_19;
    s32 temp_v0_20;
    s32 temp_v0_21;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v1;
    s32 temp_v1_12;
    s32 temp_v1_13;
    s32 temp_v1_15;
    s32 temp_v1_16;
    s32 temp_v1_17;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    s32 var_a1_5;
    s32 var_a1_6;
    s32 var_a1_7;
    s32 var_a1_8;
    s32 var_fp;
    s32 var_s3_2;
    s32 var_s3_3;
    s32 var_s3_4;
    s32 var_s5;
    s32 var_s6;
    s32 var_s7;
    s32 var_v0;
    s32 var_v0_10;
    s32 var_v0_11;
    s32 var_v0_13;
    s32 var_v0_14;
    s32 var_v0_16;
    s32 var_v0_17;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v1;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    s32 var_v1_7;
    s8 temp_a0_10;
    s8 temp_a0_4;
    s8 temp_a0_5;
    s8 temp_a0_7;
    s8 temp_a1_3;
    s8 temp_a1_5;
    s8 temp_v0;
    s8 temp_v0_10;
    s8 temp_v0_11;
    s8 temp_v0_14;
    s8 temp_v0_17;
    s8 temp_v0_7;
    s8 temp_v0_8;
    s8 temp_v0_9;
    s8 temp_v1_3;
    s8 temp_v1_8;
    s8 temp_v1_9;
    s8 var_s3;
    s8 var_v0_12;
    u16 temp_a1_4;
    u32 temp_v1_2;
    u8 temp_a0_6;
    u8 temp_v0_15;
    u8 temp_v0_16;
    u8 var_s4;
    u8 var_v0_15;
    u8 var_v0_8;
    u8 var_v0_9;
    u8 var_v1_2;
    u8 var_v1_6;
    void *temp_a0;
    void *temp_a0_3;
    void *temp_a0_8;
    void *temp_a0_9;
    void *temp_s0_2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_v0_12;
    void *temp_v0_2;
    void *temp_v1_10;
    void *temp_v1_11;
    void *var_s1;
    void *var_s1_2;
    void *var_s1_3;
    void *var_s1_4;
    void *var_s1_5;

    sp20 = M2C_FIELD(port_D_8008D0F8, s32 *, 0);
    sp24 = M2C_FIELD(port_D_8008D0F8, s32 *, 4);
    sp28 = M2C_FIELD(port_D_8008D0F8, s32 *, 8);
    sp2C = M2C_FIELD(port_D_8008D0F8, s32 *, 0xC);
    sp30 = M2C_FIELD(port_D_8008D0F8, s32 *, 0x10);
    sp34 = M2C_FIELD(port_D_8008D0F8, s32 *, 0x14);
    var_s7 = 0;
    var_s5 = 0;
    var_fp = 0;
    sp68 = 0;
    sp70 = 0;
    if (M2C_FIELD(arg0, u8 *, 0xF4) != 0) {
        if (M2C_FIELD(arg0, s16 *, 0x1EC) == 0) {
            if (M2C_FIELD(arg0, M2C_UNK (**)(void *, s16), 0x354) == &func_80025730) {
                M2C_FIELD(arg0, M2C_UNK (**)(void *, M2C_UNK *), 0x350)(arg0, port_D_8008D0F8);
                return;
            }
            func_8002D16C(arg0);
            goto block_5;
        }
block_5:
        if (M2C_FIELD(arg0, u8 *, 0x268) != 0) {
            func_8003DBA8(arg0);
            M2C_FIELD(arg0, s16 *, 0x288) = 1;
            return;
        }
        port_D_800A2F54 = 0;
        if (func_8003E78C(arg0) & 0xFF) {
            if (port_D_800A2EAC == 0) {
                port_D_800A2F54 = 1;
                goto block_10;
            }
            goto block_11;
        }
block_10:
        if (port_D_800A2EAC != 0) {
block_11:
            if (M2C_FIELD(arg0, u16 *, 0x360) == 4) {
                temp_v0 = CarGetTrackSide(arg0, 0);
                if (temp_v0 == 1) {
                    port_D_800A2F54 = (s32) temp_v0;
                }
            }
        }
        temp_a1 = port_D_800A2F54 * 4;
        temp_hi = (s32) (M2C_FIELD(arg0, s16 *, 0x1E0) + 2) % (s32) (*(M2C_UNK *)(port_D_800B1EA8 + (temp_a1)));
        temp_a1_2 = temp_a1 + port_D_800AE154;
        temp_v1 = temp_hi * 0xC;
        temp_a0 = temp_v1 + *temp_a1_2;
        sp38 = M2C_FIELD(temp_a0, s32 *, 0);
        sp40 = M2C_FIELD(temp_a0, s32 *, 4);
        sp48 = (s32) M2C_FIELD(temp_a0, u16 *, 0xA);
        M2C_FIELD(arg0, s32 *, 0x84) = (s32) (M2C_FIELD(temp_a0, s16 *, 8) << 0x10);
        temp_v1_2 = M2C_FIELD((temp_v1 + *temp_a1_2), u32 *, 8);
        sp50 = ((temp_v1_2 >> 0x1E) ^ 1) & 1;
        sp48 &= 0x3FFF;
        sp58 = (temp_v1_2 >> 0x1F) ^ 1;
        if (port_D_800A2F58 != 0) {
            if (port_gSessionType == 1) {
                M2C_FIELD(arg0, s32 *, 0x84) = MathMultiplyFixed16(M2C_FIELD(arg0, s32 *, 0x84), MathFixedDivide(port_D_800A2F50 + 0x28, 0x198));
                func_8002A1D0();
                func_8002BC88(arg0);
                temp_a0_2 = M2C_FIELD(arg0, s32 *, 0x98);
                if ((temp_a0_2 >> 0x10) < M2C_FIELD(arg0, s16 *, 0x86)) {
                    M2C_FIELD(arg0, s32 *, 0x84) = temp_a0_2;
                }
                if ((M2C_FIELD(arg0, s32 *, 0x98) >> 0x10) < M2C_FIELD(arg0, s16 *, 0x92)) {
                    M2C_FIELD(arg0, s32 *, 0x90) = M2C_FIELD(arg0, s32 *, 0x98);
                }
            } else {
                var_a0 = 2;
                if (port_D_800A36A4 >= 0x29) {
                    var_a1 = 3;
                } else {
                    var_a0 = port_D_800A2F50;
                    var_a1 = 0x1A7;
                }
                M2C_FIELD(arg0, s32 *, 0x84) = MathMultiplyFixed16(M2C_FIELD(arg0, s32 *, 0x84), MathFixedDivide(var_a0, var_a1));
            }
            M2C_FIELD(arg0, s32 *, 0x22C) = 0;
            if (arg0 != port_D_800A35E0) {
                temp_v0_2 = M2C_FIELD(arg0, void **, 0x3E4);
                if (temp_v0_2 != NULL) {
                    temp_a0_3 = M2C_FIELD(temp_v0_2, void **, 8);
                    if (M2C_FIELD(arg0, s16 *, 0x1E0) == M2C_FIELD(temp_a0_3, s16 *, 0x1E0)) {
                        temp_v0_3 = M2C_FIELD(temp_a0_3, s32 *, 0x90) + 0xFFFC0000;
                        M2C_FIELD(arg0, s32 *, 0x90) = temp_v0_3;
                        M2C_FIELD(arg0, s32 *, 0x84) = temp_v0_3;
                    }
                }
            }
            if ((port_gSessionType != 1) && (port_func_800A2CE0 == 5)) {
                M2C_FIELD(arg0, s32 *, 0x84) = MathMultiplyFixed16(M2C_FIELD(arg0, s32 *, 0x84), MathFixedDivide(0x41, 0x64));
            }
        } else {
            if ((M2C_FIELD(port_D_800A35E0, s16 *, 0x1EC) == 0) && (M2C_FIELD(port_D_800A35E0, s16 *, 0x284) >= M2C_FIELD(arg0, s16 *, 0x284)) && (port_D_800A2F54 != 1) && (temp_v0_4 = port_D_800A2F5C + 1, port_D_800A2F5C = temp_v0_4, (temp_v0_4 >= 0))) {
                temp_a2 = M2C_FIELD(arg0, s16 *, 0xFA);
                var_v0 = temp_a2 * 4;
                if (temp_a2 < 0x10) {
                    var_v1 = port_D_800A2F50 * 8;
                } else {
                    var_v0 = temp_a2 * 0xC;
                    var_v1 = port_D_800A2F50 * 8;
                }
                M2C_FIELD(arg0, s32 *, 0x84) = MathMultiplyFixed16(M2C_FIELD(arg0, s32 *, 0x84), MathFixedDivide((var_v1 - var_v0) + ((0x96 - port_D_800A3320) * 2), 0x198 * 8));
                M2C_FIELD(arg0, s32 *, 0x22C) = 0x1E0000;
                port_D_800A2F5C = port_D_800A2E94 * 0x190;
            } else {
                if (port_D_800A2F5C > 0) {
                    port_D_800A2F5C -= 1;
                    temp_a2_2 = (port_D_800A2F50 * 8) - (M2C_FIELD(arg0, s16 *, 0xFA) * 4);
                    M2C_FIELD(arg0, s32 *, 0x84) = MathMultiplyFixed16(M2C_FIELD(arg0, s32 *, 0x84), MathFixedDivide(temp_a2_2 + ((0x66 - port_D_800A3320) * 3), 0x198 * 8));
                    var_v0_2 = 0x140000;
                } else {
                    if (port_D_800A2F5C >= 0) {
                        port_D_800A2F5C = -(port_D_800A2E94 * 0x258);
                    }
                    temp_v1_3 = M2C_FIELD(port_gCarList, s8 *, 0x204);
                    if (temp_v1_3 >= 0x15) {
                        var_v0_3 = M2C_FIELD(arg0, s16 *, 0xFA) * 0x10;
                    } else if (temp_v1_3 >= 0xD) {
                        var_v0_3 = M2C_FIELD(arg0, s16 *, 0xFA) * 0xA;
                    } else {
                        var_v0_3 = M2C_FIELD(arg0, s16 *, 0xFA) * 4;
                    }
                    M2C_FIELD(arg0, s32 *, 0x84) = MathMultiplyFixed16(M2C_FIELD(arg0, s32 *, 0x84), MathFixedDivide((port_D_800A2F50 * 8) - var_v0_3, 0x198 * 8));
                    var_v0_2 = 0xA0000;
                }
                M2C_FIELD(arg0, s32 *, 0x22C) = var_v0_2;
            }
            if (port_D_800A2F5C < -(port_D_800A2E94 * 0xC8)) {
                M2C_FIELD(arg0, u8 *, 0x3FC) = 0U;
                M2C_FIELD(arg0, s32 *, 0x22C) = 0;
                port_D_800A2F5C += 1;
                M2C_FIELD(arg0, s32 *, 0x84) = MathMultiplyFixed16(M2C_FIELD(arg0, s32 *, 0x84), MathFixedDivide(0x60, 0x64));
            }
            if (M2C_FIELD(arg0, u8 *, 0x3FC) != 0) {
                if (port_gSplitScreenMode == 0) {
                    M2C_FIELD(arg0, s32 *, 0x84) = (s32) (M2C_FIELD(arg0, s32 *, 0x84) + M2C_FIELD(port_gPlayerCar, s32 *, 0x22C));
                } else {
                    M2C_FIELD(arg0, s32 *, 0x84) = (s32) (M2C_FIELD(arg0, s32 *, 0x84) + 0xC0000);
                }
                M2C_FIELD(arg0, u8 *, 0x3FC) = (u8) (M2C_FIELD(arg0, u8 *, 0x3FC) - 1);
            }
        }
        M2C_FIELD(arg0, s32 *, 0x84) = MathMultiplyFixed16(M2C_FIELD(arg0, s32 *, 0x84), MathFixedDivide(port_D_800A2E4C, 0x64));
        if (M2C_FIELD(arg0, u16 *, 0x3A4) & 0x1000) {
            M2C_FIELD(arg0, s32 *, 0x84) = MathMultiplyFixed16(M2C_FIELD(arg0, s32 *, 0x84), MathFixedDivide(1, 2));
        }
        if (M2C_FIELD(arg0, s32 *, 0x84) <= 0x31FFFF) {
            M2C_FIELD(arg0, s32 *, 0x84) = 0x320000;
        }
        if (port_D_800A372C != 0) {
            port_D_800A2F5C = -(port_D_800A2E94 * 0x190);
            if (port_D_800A2F54 == 0) {
                sp68 = 1;
            }
            if (M2C_FIELD(arg0, u16 *, 0x3A4) & 0xF) {
                M2C_FIELD(arg0, s32 *, 0x84) = 0;
            } else if (arg0 == port_D_800A3A64) {
                M2C_FIELD(arg0, s32 *, 0x84) = 0xAC0000;
            } else {
                var_s1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x3F0), void **, 8);
                var_v0_4 = M2C_FIELD(var_s1, s16 *, 0x288);
                var_s4 = 0;
loop_70:
                if (var_v0_4 != 0) {
block_69:
                    var_s1 = M2C_FIELD(M2C_FIELD(var_s1, void **, 0x3F0), void **, 8);
                    var_v0_4 = M2C_FIELD(var_s1, s16 *, 0x288);
                    goto loop_70;
                }
                if (M2C_FIELD(var_s1, u16 *, 0x3A4) & 0xF) {
                    goto block_69;
                }
                if (M2C_FIELD(var_s1, s32 *, 0x354) != (s32)port_CarResetMotionCounters) {
                    goto block_69;
                }
                temp_v0_5 = func_8003702C(var_s1, arg0);
                var_s6 = temp_v0_5;
                temp_v0_6 = func_8003702C(port_D_800A3A64, arg0);
                var_v0_5 = temp_v0_6 << 0x10;
                if ((u32) (temp_v0_5 & 0xFFFF) < 0xBU) {
                    temp_a0_4 = M2C_FIELD(var_s1, s8 *, 0x408);
                    temp_a1_3 = M2C_FIELD(arg0, s8 *, 0x408);
                    var_v0_5 = temp_v0_6 << 0x10;
                    if (temp_a0_4 < temp_a1_3) {
                        var_v0_5 = temp_v0_6 << 0x10;
                        if (M2C_FIELD(var_s1, s8 *, 0x3FE) == M2C_FIELD(arg0, s8 *, 0x3FE)) {
                            if (((u32) ((temp_v0_5 - 1) & 0xFFFF) < 2U) && (temp_a1_3 == (temp_a0_4 + 1))) {
                                var_s4 = 1;
                            }
                            sp60 = M2C_FIELD(var_s1, s32 *, 0x84);
                            goto block_87;
                        }
                    }
                }
                temp_v1_4 = var_v0_5 >> 0x10;
                var_v0_6 = 0 & 0xFF;
                if (temp_v1_4 >= 0) {
                    temp_a0_5 = M2C_FIELD(arg0, s8 *, 0x408);
                    var_v0_6 = 0 & 0xFF;
                    if ((temp_a0_5 + 0xA) >= temp_v1_4) {
                        temp_v1_5 = temp_v0_6 - temp_a0_5;
                        var_s6 = temp_v1_5;
                        if (arg0 == port_D_800A37C0) {
                            if ((u32) ((temp_v1_5 - 1) & 0xFFFF) < 2U) {
                                var_s4 = 1;
                            }
                        }
                        sp60 = 0xAC0000;
block_87:
                        var_v0_6 = 1 & 0xFF;
                    }
                }
                if (var_v0_6 != 0) {
                    if (port_D_800A3670 != 0) {
                        M2C_FIELD(arg0, u8 *, 0x401) = var_s4;
                    } else {
                        var_v1_2 = 0;
                        if (M2C_FIELD(var_s1, u8 *, 0x401) != 0) {
                            var_v1_2 = var_s4;
                        }
                        M2C_FIELD(arg0, u8 *, 0x401) = var_v1_2;
                    }
                    if ((s16) var_s6 >= 2) {
                        M2C_FIELD(arg0, s32 *, 0x84) = (s32) (sp60 + MathMultiplyFixed16(M2C_FIELD(arg0, s32 *, 0x84) - sp60, MathFixedDivide((s16) var_s6 - 1, 9)));
                    } else {
                        var_a0_2 = 5;
                        M2C_FIELD(arg0, s32 *, 0x84) = MathMultiplyFixed16(sp60, MathFixedDivide(9, 0xA));
                        if ((s16) var_s6 != 0) {
                            var_a0_2 = 9;
                        }
                        M2C_FIELD(arg0, s32 *, 0x90) = MathMultiplyFixed16(M2C_FIELD(var_s1, s32 *, 0x90), MathFixedDivide(var_a0_2, 0xA));
                    }
                }
            }
        }
        if ((port_D_800A2EDC != 0) && (temp_a1_4 = M2C_FIELD(arg0, u16 *, 0x3A4), ((temp_a1_4 & 0xF) != 0))) {
            temp_a0_6 = M2C_FIELD(arg0, u8 *, 0x3B7);
            if (temp_a0_6 != 0) {
                if ((M2C_FIELD(arg0, M2C_UNK (**)(void *, s16), 0x354) == (s32)port_CarResetMotionCounters) && (temp_a0_6 == 0x64) && (M2C_FIELD(arg0, s16 *, 0x1EC) != 0)) {
                    if (temp_a1_4 & 3) {
                        M2C_FIELD(arg0, s16 *, 0x102) = 0;
                    } else {
                        M2C_FIELD(arg0, s16 *, 0x102) = 1;
                    }
                    ObjectSetCallbackIfAllowed(arg0, &func_8003AA20);
                }
                M2C_FIELD(arg0, u8 *, 0x3B7) = (u8) (M2C_FIELD(arg0, u8 *, 0x3B7) - 1);
                goto block_120;
            }
            if (port_D_800A2EE0 != 0) {
                func_80044114(arg0);
                goto block_120;
            }
            if ((port_D_800A3071 != 0) && (port_D_800A3910 == 0) && (port_gCrashCar == NULL) && (port_gSessionType == 0)) {
                SceneSetCameraTarget(arg0, temp_a1_4);
                port_D_800A3764 = 1;
                goto block_120;
            }
            if (arg0 != port_D_800A3728) {
                if (!(func_80037204(arg0) & 0xFF)) {
                    port_D_800A3564 = 1;
                    goto block_120;
                }
            } else {
block_120:
                M2C_FIELD(arg0, s32 *, 0x84) = MathMultiplyFixed16(M2C_FIELD(arg0, s32 *, 0x84), MathFixedDivide((s32) M2C_FIELD(arg0, u8 *, 0x3B7), 0x64));
                goto block_121;
            }
        } else {
block_121:
            if ((port_D_800A2E90 != 0) && (port_gSessionType != 1)) {
                if (port_D_800A2F54 != 1) {
                    if (sp50 == 0) {
                        var_s5 = 1;
                    }
                    var_s1_2 = arg0;
                    if (sp58 == 0) {
                        var_s5 |= 4;
                    }
loop_128:
                    var_s1_2 = M2C_FIELD(M2C_FIELD(var_s1_2, void **, 0x3F0), void **, 8);
                    var_v1_3 = 0;
                    if (M2C_FIELD(var_s1_2, u8 *, 0x268) != 0) {
                        var_v0_7 = 0;
loop_130:
                        var_v1_3 += 1;
                        if (var_v0_7 < 3) {
                            var_s1_2 = M2C_FIELD(M2C_FIELD(var_s1_2, void **, 0x3F0), void **, 8);
                            var_v0_7 = var_v1_3;
                            if (M2C_FIELD(var_s1_2, u8 *, 0x268) != 0) {
                                goto loop_130;
                            }
                        }
                    }
                    if (func_8003702C(var_s1_2, arg0) < 0) {
                        var_a1_2 = -func_8003702C(var_s1_2, arg0);
                    } else {
                        var_a1_2 = func_8003702C(var_s1_2, arg0);
                    }
                    if (var_a1_2 < 2) {
                        temp_v1_6 = 1 << (M2C_FIELD(var_s1_2, s8 *, 0x206) + 1);
                        var_s5 |= temp_v1_6;
                        var_fp |= temp_v1_6;
                        if (var_s7 < 6) {
                            M2C_FIELD(&(&sp10[0])[var_s7], void **, 0x10) = var_s1_2;
                            var_s7 += 1;
                            goto loop_128;
                        }
                    }
                    var_s1_3 = arg0;
loop_139:
                    var_s1_3 = M2C_FIELD(M2C_FIELD(var_s1_3, void **, 0x3F4), void **, 8);
                    var_v0_8 = M2C_FIELD(var_s1_3, u8 *, 0x268);
                    var_v1_4 = 0;
loop_142:
                    if ((var_v0_8 != 0) || (M2C_FIELD(var_s1_3, s16 *, 0x1EC) == 0)) {
                        var_v1_4 += 1;
                        if (var_v1_4 < 2) {
                            var_s1_3 = M2C_FIELD(M2C_FIELD(var_s1_3, void **, 0x3F4), void **, 8);
                            var_v0_8 = M2C_FIELD(var_s1_3, u8 *, 0x268);
                            goto loop_142;
                        }
                    }
                    if (func_8003702C(var_s1_3, arg0) < 0) {
                        var_a1_3 = -func_8003702C(var_s1_3, arg0);
                    } else {
                        var_a1_3 = func_8003702C(var_s1_3, arg0);
                    }
                    if (var_a1_3 < 2) {
                        temp_v1_7 = 1 << (M2C_FIELD(var_s1_3, s8 *, 0x206) + 1);
                        var_s5 |= temp_v1_7;
                        var_fp |= temp_v1_7;
                        if (var_s7 < 6) {
                            M2C_FIELD(&(&sp10[0])[var_s7], void **, 0x10) = var_s1_3;
                            var_s7 += 1;
                            goto loop_139;
                        }
                    }
                    if ((var_s5 & 2) || ((var_s3 = 0, (port_D_800A2F58 != 0)) && (port_D_800A3598 == 0))) {
                        temp_a0_7 = M2C_FIELD(arg0, s8 *, 0x206);
                        var_s3 = temp_a0_7;
                        if (var_s5 & (1 << (temp_a0_7 + 1))) {
                            var_s1_4 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x3F0), void **, 8);
                            var_v0_9 = M2C_FIELD(var_s1_4, u8 *, 0x268);
                            var_v1_5 = 0;
loop_157:
                            if ((var_v0_9 != 0) || (M2C_FIELD(var_s1_4, s16 *, 0x1EC) == 0)) {
                                var_v1_5 += 1;
                                if (var_v1_5 < 3) {
                                    var_s1_4 = M2C_FIELD(M2C_FIELD(var_s1_4, void **, 0x3F0), void **, 8);
                                    var_v0_9 = M2C_FIELD(var_s1_4, u8 *, 0x268);
                                    goto loop_157;
                                }
                            }
                            temp_s0 = M2C_FIELD(arg0, s16 *, 0x92) - M2C_FIELD(var_s1_4, s16 *, 0x92);
                            if (temp_s0 >= 0x10) {
                                if (func_8003702C(var_s1_4, arg0) < 0) {
                                    var_a1_4 = -func_8003702C(var_s1_4, arg0);
                                } else {
                                    var_a1_4 = func_8003702C(var_s1_4, arg0);
                                }
                                if (var_a1_4 < 2) {
                                    if (var_s5 != 7) {
                                        temp_v1_8 = M2C_FIELD(arg0, s8 *, 0x206);
                                        if (temp_v1_8 != 0) {
                                            if (temp_v1_8 <= 0) {
                                                var_v0_10 = temp_s0 < 0x64;
                                                if (temp_v1_8 != -1) {

                                                } else {
                                                    goto block_174;
                                                }
                                            } else {
                                                var_v0_10 = temp_s0 < 0x64;
                                                if (temp_v1_8 != 1) {

                                                } else {
                                                    goto block_174;
                                                }
                                            }
                                        } else {
                                            var_s3 = 1;
                                            if (!(var_s5 & 1)) {
                                                var_s3 = -1;
                                            }
                                        }
                                    } else {
                                        var_v0_10 = temp_s0 < 0x64;
block_174:
                                        if (var_v0_10 != 0) {
                                            M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(var_s1_4, s32 *, 0x90) + 0xFFFF0000);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    temp_a0_8 = M2C_FIELD(arg0, void **, 0x3F4);
                    if (temp_a0_8 != NULL) {
                        temp_s1 = M2C_FIELD(temp_a0_8, void **, 8);
                        if (M2C_FIELD(temp_s1, s16 *, 0x1EC) == 0) {
                            if (func_8003702C(temp_s1, arg0) < 0) {
                                var_a1_5 = -func_8003702C(temp_s1, arg0);
                            } else {
                                var_a1_5 = func_8003702C(temp_s1, arg0);
                            }
                            if (((u32) (var_a1_5 - 2) < 4U) && (M2C_FIELD(arg0, s32 *, 0x90) < M2C_FIELD(temp_s1, s32 *, 0x90)) && (temp_a0_9 = M2C_FIELD(arg0, void **, 0x3F0), (temp_a0_9 != NULL))) {
                                temp_s0_2 = M2C_FIELD(temp_a0_9, void **, 8);
                                if (func_8003702C(temp_s0_2, arg0) < 0) {
                                    var_a1_6 = -func_8003702C(temp_s0_2, arg0);
                                } else {
                                    var_a1_6 = func_8003702C(temp_s0_2, arg0);
                                }
                                var_v0_11 = 1 & 0xFF;
                                if (var_a1_6 < 2) {
                                    goto block_188;
                                }
                            } else {
block_188:
                                var_v0_11 = 0 & 0xFF;
                            }
                            if ((var_v0_11 != 0) && (M2C_FIELD(arg0, s32 *, 0x90) > 0x01720000)) {
                                if (M2C_FIELD(arg0, s8 *, 0x205) == 0) {
                                    temp_v1_9 = M2C_FIELD(arg0, s8 *, 0x203);
                                    temp_a0_10 = M2C_FIELD(temp_s1, s8 *, 0x203);
                                    if (temp_v1_9 < temp_a0_10) {
                                        temp_v0_7 = (u8) M2C_FIELD(arg0, s8 *, 0x206) - 1;
                                        M2C_FIELD(arg0, s8 *, 0x206) = temp_v0_7;
                                        if (temp_v0_7 < -1) {
                                            M2C_FIELD(arg0, s8 *, 0x206) = -1;
                                        }
                                    } else if (temp_a0_10 < temp_v1_9) {
                                        temp_v0_8 = (u8) M2C_FIELD(arg0, s8 *, 0x206) + 1;
                                        M2C_FIELD(arg0, s8 *, 0x206) = temp_v0_8;
                                        if (temp_v0_8 >= 2) {
                                            M2C_FIELD(arg0, s8 *, 0x206) = 1;
                                        }
                                    }
                                    var_s3 = M2C_FIELD(arg0, s8 *, 0x206);
                                    M2C_FIELD(arg0, s8 *, 0x205) = (s8) M2C_FIELD(arg0, u16 *, 0x248);
                                }
                            }
                            if (M2C_FIELD(arg0, s8 *, 0x205) > 0) {
                                M2C_FIELD(arg0, s8 *, 0x205) = (s8) (M2C_FIELD(arg0, s8 *, 0x205) - 1);
                            }
                        }
                    }
                    if (M2C_FIELD(arg0, u16 *, 0x3A4) & 0x1000) {
                        var_s3 = 2;
                        if (port_D_800A2F84 != 0) {
                            var_s3 = -2;
                        }
                        sp68 = 1;
                    } else if ((port_gCrashCar != NULL) && (M2C_FIELD(port_gCrashCar, s16 *, 0x1EC) != 0)) {
                        if (func_8003702C(port_gCrashCar, arg0) < 0) {
                            if (-func_8003702C(port_gCrashCar, arg0) < 5) {
                                goto block_212;
                            }
                        } else if (func_8003702C(port_gCrashCar, arg0) < 5) {
block_212:
                            if (var_s3 == 0) {
                                if (port_D_800A2F84 != 0) {
                                    if (sp50 == 0) {
                                        var_s3 = 1;
                                    }
                                } else if (sp58 == 0) {
                                    var_s3 = -1;
                                }
                            }
                        }
                    }
                    if (port_D_800A372C != 0) {
                        temp_v0_9 = M2C_FIELD(port_D_800A3728, s8 *, 0x203);
                        if (temp_v0_9 >= 0) {
                            if (temp_v0_9 < 4) {
                                goto block_223;
                            }
                            goto block_229;
                        }
                        if (-temp_v0_9 < 4) {
block_223:
                            func_8003702C(port_D_800A3728, arg0);
                            if (func_8003702C(port_D_800A3728, arg0) < 5) {
                                temp_v0_10 = M2C_FIELD(port_D_800A3728, s8 *, 0x203);
                                if (temp_v0_10 != 0) {
                                    var_s3 = -1;
                                    if (temp_v0_10 > 0) {
                                        var_s3 = 1;
                                    }
                                } else {
                                    var_s3 = M2C_FIELD(arg0, s8 *, 0x3FE);
                                }
                                sp70 = 1;
                            } else {
                                goto block_229;
                            }
                        } else {
block_229:
                            if (M2C_FIELD(arg0, u8 *, 0x401) != 0) {
                                temp_v0_11 = M2C_FIELD(arg0, s8 *, 0x400);
                                if (temp_v0_11 == 0) {
                                    var_v1_6 = 0;
                                    if (M2C_FIELD(arg0, s8 *, 0x3FF) == 0) {
                                        var_v1_6 = (u8) M2C_FIELD(arg0, s8 *, 0x3FE);
                                    }
                                    M2C_FIELD(arg0, s8 *, 0x3FF) = (s8) var_v1_6;
                                    temp_s0_3 = M2C_FIELD(arg0, s8 *, 0x409) - 5;
                                    if (RandomScaledGet(0xA) < 0) {
                                        var_v0_12 = temp_s0_3 - RandomScaledGet(0xA);
                                    } else {
                                        var_v0_12 = temp_s0_3 + RandomScaledGet(0xA);
                                    }
                                } else {
                                    var_v0_12 = temp_v0_11 - 1;
                                }
                                M2C_FIELD(arg0, s8 *, 0x400) = var_v0_12;
                            }
                            var_s3 = M2C_FIELD(arg0, s8 *, 0x3FF);
                        }
                    }
                    if (sp68 != 0) {
                        sp58 = 1;
                        sp50 = 1;
                        temp_a0_11 = M2C_FIELD(arg0, s16 *, 0x1E0);
                        var_v0_13 = temp_a0_11 + 2;
                        if (sp70 == 0) {
                            var_v0_13 = temp_a0_11 + 2;
                            if (M2C_FIELD(arg0, s16 *, 0x1EC) == 0) {
                                var_v0_13 = temp_a0_11 + 3;
                            }
                        }
                        temp_v0_12 = ((var_v0_13 % (s32) port_gTrackSectionCount) * 0x90) + port_gTrackSections;
                        sp38 = M2C_FIELD(temp_v0_12, s32 *, 0x14);
                        sp40 = M2C_FIELD(temp_v0_12, s32 *, 0x18);
                    }
                    if ((var_s3 != 0) && ((var_s3 >= 0) || (sp50 != 0)) && ((var_s3 <= 0) || (sp58 != 0))) {
                        M2C_FIELD(arg0, s8 *, 0x206) = var_s3;
                    } else {
                        M2C_FIELD(arg0, s8 *, 0x206) = 0;
                    }
                    if (M2C_FIELD(arg0, s8 *, 0x206) < 0) {
                        if (sp50 == 0) {
                            M2C_FIELD(arg0, s8 *, 0x206) = 0;
                            if (var_fp & 2) {
                                var_s3_2 = 0;
                                if (var_s7 > 0) {
                                    var_a0_3 = &sp10[0];
                                    do {
                                        temp_v1_10 = M2C_FIELD(var_a0_3, void **, 0x10);
                                        if (M2C_FIELD(temp_v1_10, s8 *, 0x206) == 0) {
                                            M2C_FIELD(temp_v1_10, s8 *, 0x206) = 1;
                                        }
                                        var_s3_2 += 1;
                                        var_a0_3 += 4;
                                    } while (var_s3_2 < var_s7);
                                }
                            }
                        }
                    }
                    if ((M2C_FIELD(arg0, s8 *, 0x206) > 0) && (sp58 == 0)) {
                        M2C_FIELD(arg0, s8 *, 0x206) = 0;
                        if (var_fp & 2) {
                            var_s3_3 = 0;
                            if (var_s7 > 0) {
                                var_a0_4 = &sp10[0];
                                do {
                                    temp_v1_11 = M2C_FIELD(var_a0_4, void **, 0x10);
                                    if (M2C_FIELD(temp_v1_11, s8 *, 0x206) == 0) {
                                        M2C_FIELD(temp_v1_11, s8 *, 0x206) = -1;
                                    }
                                    var_s3_3 += 1;
                                    var_a0_4 += 4;
                                } while (var_s3_3 < var_s7);
                            }
                        }
                    }
                    var_s3_4 = 0;
                    if (var_s7 > 0) {
                        var_v0_14 = 0 * 4;
loop_270:
                        temp_s1_2 = M2C_FIELD((sp + var_v0_14), void **, 0x20);
                        temp_a3 = M2C_FIELD(arg0, s32 *, 0);
                        temp_a2_3 = M2C_FIELD(temp_s1_2, s32 *, 4);
                        temp_s5 = 0x3FF - M2C_FIELD(arg0, s16 *, 0x114);
                        temp_s0_4 = temp_s5 * 4;
                        temp_s4 = temp_a3 - M2C_FIELD(temp_s1_2, s32 *, 0);
                        temp_s6 = M2C_FIELD(arg0, s32 *, 4) - temp_a2_3;
                        temp_s0_5 = MathMultiplyFixed16(*(s32 *)(temp_s0_4 + port_gCosTable), temp_s4 << 0x10);
                        temp_v0_13 = (s32) (temp_s0_5 - MathMultiplyFixed16(*(s32 *)(temp_s0_4 + port_gSinTable), temp_s6 << 0x10)) >> 0x10;
                        temp_v1_12 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x36C), s16 *, 0x1E) * 2;
                        if (temp_v0_13 >= 0) {
                            if (temp_v0_13 >= temp_v1_12) {
                                var_s3_4 += 1;
                                goto block_290;
                            }
                            goto block_274;
                        }
                        if (-temp_v0_13 < temp_v1_12) {
block_274:
                            temp_s0_6 = temp_s5 * 4;
                            temp_s0_7 = MathMultiplyFixed16(*(s32 *)(temp_s0_6 + port_gSinTable), temp_s4 << 0x10);
                            temp_s0_8 = (s32) (temp_s0_7 + MathMultiplyFixed16(*(s32 *)(temp_s0_6 + port_gCosTable), temp_s6 << 0x10)) >> 0x10;
                            temp_v1_13 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x36C), s16 *, 0x22) * 2;
                            if (temp_s0_8 >= 0) {
                                if (temp_s0_8 >= temp_v1_13) {
                                    var_s3_4 += 1;
                                    goto block_290;
                                }
                                goto block_278;
                            }
                            if (-temp_s0_8 < temp_v1_13) {
block_278:
                                if (temp_s0_8 < 0) {
                                    temp_v0_14 = (u8) M2C_FIELD(arg0, s8 *, 0x206) - 1;
                                    M2C_FIELD(arg0, s8 *, 0x206) = temp_v0_14;
                                    if (temp_v0_14 < -1) {
                                        M2C_FIELD(arg0, s8 *, 0x206) = -1;
                                    }
                                    temp_v0_15 = M2C_FIELD(temp_s1_2, u8 *, 0x206) + 1;
                                    M2C_FIELD(temp_s1_2, u8 *, 0x206) = temp_v0_15;
                                    if ((s8) temp_v0_15 >= 2) {
                                        M2C_FIELD(temp_s1_2, u8 *, 0x206) = 1U;
                                    }
                                } else {
                                    temp_v0_16 = M2C_FIELD(temp_s1_2, u8 *, 0x206) - 1;
                                    M2C_FIELD(temp_s1_2, u8 *, 0x206) = temp_v0_16;
                                    if ((s8) temp_v0_16 < -1) {
                                        M2C_FIELD(temp_s1_2, u8 *, 0x206) = -1U;
                                    }
                                    temp_v0_17 = (u8) M2C_FIELD(arg0, s8 *, 0x206) + 1;
                                    M2C_FIELD(arg0, s8 *, 0x206) = temp_v0_17;
                                    if (temp_v0_17 >= 2) {
                                        M2C_FIELD(arg0, s8 *, 0x206) = 1;
                                    }
                                }
                                if ((s16) M2C_FIELD(arg0, u16 *, 0x248) >= M2C_FIELD(temp_s1_2, s16 *, 0x248)) {
                                    M2C_FIELD(temp_s1_2, s32 *, 0x90) = (s32) (M2C_FIELD(temp_s1_2, s32 *, 0x90) + 0xFFFF0000);
                                } else {
                                    M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + 0xFFFF0000);
                                }
                            } else {
                                goto block_289;
                            }
                        } else {
block_289:
                            var_s3_4 += 1;
block_290:
                            var_v0_14 = var_s3_4 * 4;
                            if (var_s3_4 >= var_s7) {

                            } else {
                                goto loop_270;
                            }
                        }
                    }
                } else {
                    goto block_293;
                }
            } else if (port_D_800A2F54 == 1) {
block_293:
                M2C_FIELD(arg0, s8 *, 0x206) = 0;
                var_s1_5 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x3F0), void **, 8);
                var_v0_15 = M2C_FIELD(var_s1_5, u8 *, 0x268);
                var_v1_7 = 0;
loop_296:
                if ((var_v0_15 != 0) || (M2C_FIELD(var_s1_5, s16 *, 0x1EC) == 0)) {
                    var_v1_7 += 1;
                    if (var_v1_7 < 3) {
                        var_s1_5 = M2C_FIELD(M2C_FIELD(var_s1_5, void **, 0x3F0), void **, 8);
                        var_v0_15 = M2C_FIELD(var_s1_5, u8 *, 0x268);
                        goto loop_296;
                    }
                }
                if (func_8003702C(var_s1_5, arg0) < 0) {
                    var_a1_7 = -func_8003702C(var_s1_5, arg0);
                } else {
                    var_a1_7 = func_8003702C(var_s1_5, arg0);
                }
                if (var_a1_7 < 2) {
                    temp_a0_12 = M2C_FIELD(var_s1_5, s32 *, 0x90);
                    if (temp_a0_12 > 0x640000) {
                        temp_v0_18 = temp_a0_12 + 0xFFFB0000;
                        M2C_FIELD(arg0, s32 *, 0x90) = temp_v0_18;
                        M2C_FIELD(arg0, s32 *, 0x84) = temp_v0_18;
                    }
                }
            }
            temp_v0_19 = (sp48 + 0x300) & 0x3FF;
            sp48 = temp_v0_19;
            temp_a0_13 = temp_v0_19 * 4;
            temp_a1_5 = -M2C_FIELD(arg0, s8 *, 0x206);
            temp_lo = ((s32) (*(s32 *)(temp_a0_13 + port_gCosTable) * 0x1F4) >> 0x10) * temp_a1_5;
            temp_lo_2 = ((s32) (*(s32 *)(temp_a0_13 + port_gSinTable) * 0x1F4) >> 0x10) * temp_a1_5;
            temp_v1_14 = M2C_FIELD(arg0, s16 *, 0x24E);
            sp38 += temp_lo;
            sp40 += temp_lo_2;
            if (temp_v1_14 != -1) {
                temp_a2_4 = M2C_FIELD(arg0, s16 *, 0x1E0);
                var_a1_8 = temp_a2_4 - temp_v1_14;
                temp_v1_15 = (s32) port_gTrackSectionCount >> 1;
                if (var_a1_8 >= 0) {
                    var_v0_16 = var_a1_8 < temp_v1_15;
                } else {
                    var_v0_16 = -var_a1_8 < temp_v1_15;
                }
                if (var_v0_16 == 0) {
                    temp_v1_16 = temp_v1_14 + port_gTrackSectionCount;
                    if (temp_v1_14 < temp_a2_4) {
                        temp_v0_20 = temp_v1_16 - temp_a2_4;
                        var_a1_8 = temp_v0_20;
                        if (temp_v0_20 >= 0) {
                            var_v0_17 = temp_a2_4 - temp_v1_16;
                            goto block_315;
                        }
                    } else {
                        temp_v1_17 = temp_a2_4 + port_gTrackSectionCount;
                        temp_v0_21 = temp_v1_17 - temp_v1_14;
                        var_a1_8 = temp_v0_21;
                        if (temp_v0_21 < 0) {
                            var_v0_17 = temp_v1_14 - temp_v1_17;
block_315:
                            var_a1_8 = var_v0_17;
                        }
                    }
                }
                if ((var_a1_8 > 0) || (sp38 = M2C_FIELD(arg0, s32 *, 0x250), sp40 = M2C_FIELD(arg0, s32 *, 0x254), (CarAvoidTraffic(arg0, 1, temp_a2_4, port_gTrackSectionCount) == 0))) {
                    M2C_FIELD(arg0, s16 *, 0x24E) = -1;
                }
            } else if (CarAvoidTraffic(arg0, 0, temp_lo, temp_lo_2) != 0) {
                sp38 = M2C_FIELD(arg0, s32 *, 0x250);
                sp40 = M2C_FIELD(arg0, s32 *, 0x254);
            }
            sp10[0] = sp38 - M2C_FIELD(arg0, s32 *, 0);
            sp14 = sp40 - M2C_FIELD(arg0, s32 *, 4);
            sp18 = -M2C_FIELD(arg0, s32 *, 8);
            var_a1_9 = func_800358EC(&sp10[0]);
            if (port_D_800A2F48 != 0) {
                var_a1_9 = M2C_FIELD(arg0, s16 *, 0x114);
                M2C_FIELD(arg0, s8 *, 0x201) = 1;
            } else {
                M2C_FIELD(arg0, s8 *, 0x201) = 0;
            }
            temp_v1_18 = M2C_FIELD(arg0, M2C_UNK (**)(void *, s16), 0x354);
            if (temp_v1_18 == (void *)port_CarResetMotionCounters) {
                CarSteerTowardHeading(arg0, var_a1_9);
                M2C_FIELD(arg0, u16 *, 0x104) = (u16) M2C_FIELD(arg0, s16 *, 0x114);
            } else {
                temp_v1_18(arg0, var_a1_9);
            }
            M2C_FIELD(arg0, s16 *, 0x116) = (s16) (M2C_FIELD(arg0, s16 *, 0x114) * 4);
            MatrixSetRotationFromAngle(arg0, M2C_FIELD(arg0, s16 *, 0x114) * 4);
            func_8001FB28(arg0, (s16) M2C_FIELD(arg0, u16 *, 0x104));
            M2C_FIELD(arg0, s32 *, 0xB0) = (s32) ((s32) (M2C_FIELD(arg0, s32 *, 0x60) * M2C_FIELD(arg0, s16 *, 0x92)) >> 0x10);
            temp_a2_5 = M2C_FIELD(arg0, s32 *, 0xB0);
            M2C_FIELD(arg0, s32 *, 0xB4) = (s32) ((s32) (M2C_FIELD(arg0, s32 *, 0x6C) * M2C_FIELD(arg0, s16 *, 0x92)) >> 0x10);
            temp_a3_2 = M2C_FIELD(arg0, s32 *, 0xB4);
            M2C_FIELD(arg0, s32 *, 0xB8) = (s32) ((s32) (M2C_FIELD(arg0, s32 *, 0x78) * M2C_FIELD(arg0, s16 *, 0x92)) >> 0x10);
            temp_a1_6 = M2C_FIELD(arg0, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0xB8);
            M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) + temp_a2_5);
            M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + temp_a3_2);
            M2C_FIELD(arg0, s32 *, 8) = temp_a1_6;
            func_80029CB4(arg0);
        }
    }
}
#undef sp10
#undef sp14
#undef sp18
#undef sp20
#undef sp24
#undef sp28
#undef sp2C
#undef sp30
#undef sp34
#undef sp38
#undef sp40
#undef sp48
#undef sp50
#undef sp58
#undef sp60
#undef sp68
#undef sp70
#undef sp
