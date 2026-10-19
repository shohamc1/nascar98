/* SPDX-License-Identifier: AGPL-3.0-only AND MIT AND GPL-2.0-or-later */
/* SDK C from sotn-decomp d818995ec49ef76e3b1625a96f4360108b3168be. */
#include "common.h"
#include "psxsdk_internal.h"
#include "libpress.h"
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/stdarg.h>

#include <psxsdk/libspu.h>
#include <psxsdk/libgpu.h>
#include <psxsdk/libcd.h>

extern void MDEC_reset(s32 mode);
extern void MDEC_in(u32 *buf, u32 size);
extern void MDEC_out(u32 *buf, u32 size);
extern s32 MDEC_in_sync(void);
extern s32 MDEC_out_sync(void);

void DecDCTReset(s32 mode) {
    if (mode == 0) {
        ResetCallback();
    }
    MDEC_reset(mode);
}

extern u_long gMdecLumaQuantTable[];
extern u_long gMdecChromaQuantTable[];
extern u_long gMdecIdctCoefficients[];
extern u_long gMdecQuantTablePacket[];
extern u_long gMdecIdctPacket[];

DECDCTENV *DecDCTGetEnv(DECDCTENV *env) {
    s32 i;
    u_long *src;
    u_long *dst;

    dst = (u_long *)env->iq_y;
    src = gMdecLumaQuantTable;
    for (i = 15; i != -1; i--) {
        *dst++ = *src++;
    }
    dst = (u_long *)env->iq_c;
    src = gMdecChromaQuantTable;
    for (i = 15; i != -1; i--) {
        *dst++ = *src++;
    }
    dst = (u_long *)env->dct;
    src = gMdecIdctCoefficients;
    for (i = 31; i != -1; i--) {
        *dst++ = *src++;
    }
    return env;
}

DECDCTENV *DecDCTPutEnv(DECDCTENV *env) {
    s32 i;
    u_long *src;
    u_long *dst;

    src = (u_long *)env->iq_y;
    dst = gMdecLumaQuantTable;
    for (i = 15; i != -1; i--) {
        *dst++ = *src++;
    }
    dst = gMdecChromaQuantTable;
    src = (u_long *)env->iq_c;
    for (i = 15; i != -1; i--) {
        *dst++ = *src++;
    }
    MDEC_in(gMdecQuantTablePacket, 32);
    MDEC_in(gMdecIdctPacket, 32);
    return env;
}

/* SPDX-License-Identifier: MIT */

s32 DecDCTBufSize(u_long *buf) {
    return *(u16 *)buf;
}

void DecDCTin(u_long *buf, s32 mode) {
    if (mode & 1) {
        *buf &= ~0x08000000;
    } else {
        *buf |= 0x08000000;
    }
    if (mode & 2) {
        *buf |= 0x02000000;
    } else {
        *buf &= ~0x02000000;
    }
    MDEC_in(buf, *(u16 *)buf);
}

/* SPDX-License-Identifier: MIT */

void DecDCTout(u_long *buf, s32 size) {
    MDEC_out(buf, size);
}

/* SPDX-License-Identifier: MIT */

s32 DecDCTinSync(s32 mode) {
    /* This library version ignores mode. */
    return MDEC_in_sync();
}

/* SPDX-License-Identifier: MIT */

s32 DecDCToutSync(s32 mode) {
    /* This library version ignores mode. */
    return MDEC_out_sync();
}

s32 DecDCTinCallback(void (*func)(void)) {
    return (s32)DMACallback(0, func);
}

s32 DecDCToutCallback(void (*func)(void)) {
    return (s32)DMACallback(1, func);
}

INCLUDE_RODATA("asm/nonmatchings/psxsdk/libpress", D_80090D1C);
extern volatile u32 *D_800A2CD8[];
extern volatile u32 *D_800A2CB8[];
extern u32 D_800A2CAC[];
extern char D_80090D1C[];
void MDEC_reset(s32 mode) {
    switch (mode) {
    case 0:
        *D_800A2CD8[0] = 0x80000000;
        *(u32 *)D_800A2CAC[0] = 0;
        *D_800A2CB8[0] = 0;
        *D_800A2CD8[0] = 0x60000000;
        MDEC_in(gMdecQuantTablePacket, 0x20);
        MDEC_in(gMdecIdctPacket, 0x20);
        break;
    case 1:
        *D_800A2CD8[0] = 0x80000000;
        *(u32 *)D_800A2CAC[0] = 0;
        *D_800A2CB8[0] = 0;
        *(volatile u32 *)D_800A2CB8[0];
        *D_800A2CD8[0] = 0x60000000;
        break;
    default:
        printf(D_80090D1C, mode);
        break;
    }
}

extern volatile u32 *D_800A2CDC[];
extern volatile u32 *D_800A2CB8[];
extern u32 D_800A2CA4[];
extern u32 D_800A2CA8[];
extern u32 D_800A2CD4[];
extern u32 D_800A2CAC[];
void MDEC_in(u32 *buf, u32 size) {
    u32 len;

    MDEC_in_sync();
    *D_800A2CDC[0] |= 0x88;
    len = (size >> 5) << 16;
    *(u32 *)D_800A2CA4[0] = (u32)(buf + 1);
    *(u32 *)D_800A2CA8[0] = len | 0x20;
    *(u32 *)D_800A2CD4[0] = *buf;
    *(u32 *)D_800A2CAC[0] = 0x01000201;
}

extern u32 D_800A2CB0[];
extern u32 D_800A2CB4[];
void MDEC_out(u32 *buf, u32 size) {
    u32 len;

    MDEC_out_sync();
    *D_800A2CDC[0] |= 0x88;
    len = (size >> 5) << 16;
    *D_800A2CB8[0] = 0;
    *(u32 *)D_800A2CB0[0] = (u32)buf;
    *(u32 *)D_800A2CB4[0] = len | 0x20;
    *D_800A2CB8[0] = 0x01000200;
}

extern int timeout(char *name);
extern volatile u32 *D_800A2CD8[];
extern char D_80090D38[];

s32 MDEC_in_sync(void) {
    volatile s32 i;

    i = 0x100000;
    if (*D_800A2CD8[0] & 0x20000000) {
        do {
            i = i - 1;
            if (i == -1) {
                timeout(D_80090D38);
                return -1;
            }
        } while (*D_800A2CD8[0] & 0x20000000);
    }
    return 0;
}

/* Carries the "MDEC_in_sync" rodata cell (0x80090D38) until the string gets
 * its own carrier .s via make split; then this becomes
 * INCLUDE_RODATA("asm/nonmatchings/psxsdk/libpress", D_80090D38). */
void __maspsx_include_asm_hack_D_80090D38(void) {
    __asm__(".section .rodata # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "    .globl D_80090D38 # maspsx-keep\n"
            "D_80090D38: # maspsx-keep\n"
            "    .asciz \"MDEC_in_sync\" # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern volatile u32 *D_800A2CB8[];
extern char D_80090D48[];

s32 MDEC_out_sync(void) {
    volatile s32 i;

    i = 0x100000;
    if (*D_800A2CB8[0] & 0x01000000) {
        do {
            i = i - 1;
            if (i == -1) {
                timeout(D_80090D48);
                return -1;
            }
        } while (*D_800A2CB8[0] & 0x01000000);
    }
    return 0;
}

/* Carries the "MDEC_out_sync" rodata cell (0x80090D48) until the string gets
 * its own carrier .s via make split; then this becomes
 * INCLUDE_RODATA("asm/nonmatchings/psxsdk/libpress", D_80090D48). */
void __maspsx_include_asm_hack_D_80090D48(void) {
    __asm__(".section .rodata # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "    .globl D_80090D48 # maspsx-keep\n"
            "D_80090D48: # maspsx-keep\n"
            "    .asciz \"MDEC_out_sync\" # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern char D_80090D58[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk/libpress", D_80090D58);
extern char D_80090D80[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk/libpress", D_80090D80);
extern char D_80090DB8[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk/libpress", D_80090DB8);
extern volatile u32 *mdec1;
extern volatile u32 *d0_chcr;
extern volatile u32 *d1_chcr;
extern volatile u32 *d0_madr;
extern volatile u32 *d1_madr;

int timeout(char *funcName) {
    u32 temp_s0;

    printf(D_80090DB8, funcName);
    temp_s0 = *mdec1;

    printf(D_80090D58, (*d0_chcr >> 0x18) & 1, (*d1_chcr >> 0x18) & 1, *d0_madr,
           *d1_madr);

    printf(D_80090D80, ~temp_s0 >> 0x1F, (temp_s0 >> 0x1E) & 1,
           (temp_s0 >> 0x1D) & 1, (temp_s0 >> 0x1C) & 1, (temp_s0 >> 0x1B) & 1,
           (temp_s0 >> 0x19) & 1, (temp_s0 >> 0x17) & 1);

    *mdec1 = 0x80000000;
    *d0_chcr = 0;
    *d1_chcr = 0;
    *d1_chcr;
    *mdec1 = 0x60000000;

    return 0;
}

/* 0x4C zero bytes after timeout(): a scratch buffer that input.c fills at
 * run time, not code. */
ASM_FUNC(D_8008CA04, "    .space 0x4C # maspsx-keep\n")
