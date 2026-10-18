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

/* libgpu state, Psy-Q 3.6 layout. The Makefile binds each name. */
typedef struct GpuVtbl {
    const char *rcsid;
    void (*addque)(void (*)(), s32 *, s32);
    s32 (*addque2)(void (*)(), s32 *, s32, s32);
    s32 (*clr)(RECT *, s32);
    void (*ctl)(u32);
    s32 (*cwb)(s32 *, s32);
    void (*cwc)(s32);
    s32 (*drs)(RECT *, s32 *);
    s32 (*dws)(RECT *, s32 *);
    s32 (*exeque)(void);
    s32 (*getctl)(s32);
    s32 (*otc)(s32, s32);
    s32 (*param)(s32);
    s32 (*reset)(s32);
    u32 (*status)(void);
    s32 (*sync)(s32);
} GpuVtbl;

/* Saved copy of the last DISPENV; retail reads its halfwords as unsigned. */
typedef struct SavedDispEnv {
    volatile u16 dispX;
    volatile u16 dispY;
    volatile u16 dispW;
    volatile u16 dispH;
    volatile u16 scrX;
    volatile u16 scrY;
    volatile u16 scrW;
    volatile u16 scrH;
    s32 flags;
} SavedDispEnv;

typedef struct GfxState {
    u8 type;    /* 0: PSX, 1: 1 MB VRAM, 2: debug */
    u8 queue;   /* 1: queued drawing */
    u8 level;   /* debug level */
    u8 reverse; /* upside-down display */
    s16 maxW;
    s16 maxH;
    s32 pad8; /* set while a draw-sync callback is pending */
    void (*drawSyncCb)();
    DRAWENV drawEnv;
    SavedDispEnv dispEnv;
} GfxState;

#define LOW(x) (*(u32 *)&(x))
#define GPU_CLAMP(value, low, high)                                            \
    value < low ? low : (value > high ? high : value)

extern volatile u16 gfxMaxW[];
extern volatile u16 gfxMaxH[];
extern GpuVtbl *gGpu;
extern s32 (*GPU_printf)(const char *, ...);
extern GfxState gGfx;
extern volatile s32 *GPU_DATA;
extern volatile u32 *GPU_STATUS;
extern volatile s32 *DMA2_MADR;
extern volatile s32 *DMA2_BCR;
extern volatile s32 *DMA2_CHCR;
extern volatile s32 *DMA6_MADR;
extern volatile s32 *DMA6_BCR;
extern volatile s32 *DMA6_CHCR;
extern volatile s32 *DPCR;

extern void SpuVmSeqKeyOff();

/* SDK functions whose Psy-Q source was assembly: BIOS table thunks and
 * GTE coprocessor moves no compiler emits. The wrapper's label and
 * epilogue are dropped by maspsx exactly as for INCLUDE_ASM (see
 * include/include_asm.h); the "# maspsx-keep" lines are the function. */
#define ASM_FUNC(name, body)                                                   \
    void __maspsx_include_asm_hack_##name(void) {                              \
        __asm__(".text # maspsx-keep\n"                                        \
                "    .align 2 # maspsx-keep\n"                                 \
                "    .globl " #name " # maspsx-keep\n"                         \
                "    .ent " #name " # maspsx-keep\n"                           \
                "    " #name ": # maspsx-keep\n"                               \
                "    .set noat # maspsx-keep\n"                                \
                "    .set noreorder # maspsx-keep\n" body                      \
                "    .set reorder # maspsx-keep\n"                             \
                "    .set at # maspsx-keep\n"                                  \
                "    .end " #name " # maspsx-keep\n");                         \
    }

ASM_FUNC(__SN_ENTRY_POINT,
         "    lui        $v0, %hi(D_800A33C0) # maspsx-keep\n"
         "    addiu      $v0, $v0, %lo(D_800A33C0) # maspsx-keep\n"
         "    lui        $v1, %hi(D_800BEBA0) # maspsx-keep\n"
         "    addiu      $v1, $v1, %lo(D_800BEBA0) # maspsx-keep\n"
         "    .L80073E9C: # maspsx-keep\n"
         "    sw         $zero, 0x0($v0) # maspsx-keep\n"
         "    addiu      $v0, $v0, 0x4 # maspsx-keep\n"
         "    sltu       $at, $v0, $v1 # maspsx-keep\n"
         "    bnez       $at, .L80073E9C # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    lui        $v0, %hi(D_800A2FC0) # maspsx-keep\n"
         "    lw         $v0, %lo(D_800A2FC0)($v0) # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    addi       $v0, $v0, -0x8 # maspsx-keep\n"
         "    lui        $t0, %hi(D_80000004) # maspsx-keep\n"
         "    or         $sp, $v0, $t0 # maspsx-keep\n"
         "    lui        $a0, %hi(D_800BEBA0) # maspsx-keep\n"
         "    addiu      $a0, $a0, %lo(D_800BEBA0) # maspsx-keep\n"
         "    sll        $a0, $a0, 3 # maspsx-keep\n"
         "    srl        $a0, $a0, 3 # maspsx-keep\n"
         "    lui        $v1, %hi(D_800A2FBC) # maspsx-keep\n"
         "    lw         $v1, %lo(D_800A2FBC)($v1) # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    subu       $a1, $v0, $v1 # maspsx-keep\n"
         "    subu       $a1, $a1, $a0 # maspsx-keep\n"
         "    lui        $at, %hi(D_8009B9C8) # maspsx-keep\n"
         "    sw         $a1, %lo(D_8009B9C8)($at) # maspsx-keep\n"
         "    or         $a0, $a0, $t0 # maspsx-keep\n"
         "    lui        $at, %hi(D_8009B9C4) # maspsx-keep\n"
         "    sw         $a0, %lo(D_8009B9C4)($at) # maspsx-keep\n"
         "    lui        $at, %hi(D_800A3520) # maspsx-keep\n"
         "    sw         $ra, %lo(D_800A3520)($at) # maspsx-keep\n"
         "    lui        $gp, %hi(_gp) # maspsx-keep\n"
         "    addiu      $gp, $gp, %lo(_gp) # maspsx-keep\n"
         "    addu       $fp, $sp, $zero # maspsx-keep\n"
         "    jal        InitHeap # maspsx-keep\n"
         "    addi      $a0, $a0, %lo(D_80000004) # maspsx-keep\n"
         "    lui        $ra, %hi(D_800A3520) # maspsx-keep\n"
         "    lw         $ra, %lo(D_800A3520)($ra) # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    jal        func_80012108 # maspsx-keep\n"
         "    nop # maspsx-keep\n")

INCLUDE_ASM("asm/nonmatchings/psxsdk", __do_global_dtors);

INCLUDE_ASM("asm/nonmatchings/psxsdk", __main);

extern unsigned long long __udivmoddi4(unsigned long long num,
                                       unsigned long long den,
                                       unsigned long long *rem);

typedef union {
    struct {
        s32 low;
        s32 high;
    } s;
    long long ll;
} DwUnion;

/* The negation temps are separate unions: one shared temp is coalesced into
 * an in-place negu pair, separate ones give retail's t0/t1 temps and moves. */
long long __divdi3(long long u, long long v) {
    DwUnion uu;
    DwUnion vv;
    DwUnion w;
    DwUnion n1;
    DwUnion n2;
    DwUnion n3;
    int c;
    s32 h1;
    s32 h2;
    s32 h3;

    c = 0;
    uu.ll = u;
    vv.ll = v;

    if (uu.s.high < 0) {
        c = ~c;
        n1.s.low = -uu.s.low;
        h1 = -uu.s.high;
        n1.s.high = h1 - (0 < (u32)n1.s.low);
        uu.ll = n1.ll;
    }
    if (vv.s.high < 0) {
        c = ~c;
        n2.s.low = -vv.s.low;
        h2 = -vv.s.high;
        n2.s.high = h2 - (0 < (u32)n2.s.low);
        vv.ll = n2.ll;
    }

    w.ll = __udivmoddi4(uu.ll, vv.ll, 0);
    if (c) {
        n3.s.low = -w.s.low;
        h3 = -w.s.high;
        n3.s.high = h3 - (0 < (u32)n3.s.low);
        return n3.ll;
    }
    return w.ll;
}

extern const u8 gLibgccClzTable[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", gLibgccClzTable);

/* Adapted from GNU CC libgcc2.c and longlong.h. */
/* Copyright (C) 1989, 1992, 1993, 1994, 1995 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.libgcc.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

#define USItype u32
#define UDItype unsigned long long
#define DIunion DwUnion
#define SI_TYPE_SIZE 32
#define __BITS4 8
#define __ll_B ((u32)1 << 16)
#define __ll_lowpart(t) ((u32)(t) & 0xFFFF)
#define __ll_highpart(t) ((u32)(t) >> 16)
#define __clz_tab gLibgccClzTable
#define udiv_qrnnd __udiv_qrnnd_c
/* Separate HI/LO results need independent GPRs in SDK GCC 2.6.3. */
#define umul_ppmm(hi, lo, a, b)                                                \
    __asm__("multu %2,%3\n\tmflo %0\n\tmfhi %1"                                \
            : "=r"(lo), "=r"(hi)                                               \
            : "r"((u32)(a)), "r"((u32)(b))                                     \
            : "hi", "lo")

#define sub_ddmmss(sh, sl, ah, al, bh, bl)                                     \
    do {                                                                       \
        USItype __x;                                                           \
        __x = (al) - (bl);                                                     \
        (sh) = (ah) - (bh) - (__x > (al));                                     \
        (sl) = __x;                                                            \
    } while (0)

#define __udiv_qrnnd_c(q, r, n1, n0, d)                                        \
    do {                                                                       \
        USItype __d1, __d0, __q1, __q0;                                        \
        USItype __r1, __r0, __m;                                               \
        __d1 = __ll_highpart(d);                                               \
        __d0 = __ll_lowpart(d);                                                \
                                                                               \
        __r1 = (n1) % __d1;                                                    \
        __q1 = (n1) / __d1;                                                    \
        __m = (USItype)__q1 * __d0;                                            \
        __r1 = __r1 * __ll_B | __ll_highpart(n0);                              \
        if (__r1 < __m) {                                                      \
            __q1--, __r1 += (d);                                               \
            if (__r1 >=                                                        \
                (d)) /* i.e. we didn't get carry when adding to __r1 */        \
                if (__r1 < __m)                                                \
                    __q1--, __r1 += (d);                                       \
        }                                                                      \
        __r1 -= __m;                                                           \
                                                                               \
        __r0 = __r1 % __d1;                                                    \
        __q0 = __r1 / __d1;                                                    \
        __m = (USItype)__q0 * __d0;                                            \
        __r0 = __r0 * __ll_B | __ll_lowpart(n0);                               \
        if (__r0 < __m) {                                                      \
            __q0--, __r0 += (d);                                               \
            if (__r0 >= (d))                                                   \
                if (__r0 < __m)                                                \
                    __q0--, __r0 += (d);                                       \
        }                                                                      \
        __r0 -= __m;                                                           \
                                                                               \
        (q) = (USItype)__q1 * __ll_B | __q0;                                   \
        (r) = __r0;                                                            \
    } while (0)

#define count_leading_zeros(count, x)                                          \
    do {                                                                       \
        u32 __xr = (x);                                                        \
        u32 __a;                                                               \
        __a = __xr < (1 << 16) ? (__xr < (1 << 8) ? 0 : 8)                     \
                               : (__xr < (1 << 24) ? 16 : 24);                 \
        (count) = 32 - (gLibgccClzTable[__xr >> __a] + __a);                   \
    } while (0)

UDItype __udivmoddi4(UDItype n, UDItype d, UDItype *rp) {
    DIunion ww;
    DIunion nn, dd;
    DIunion rr;
    USItype d0, d1, n0, n1, n2;
    USItype q0, q1;
    USItype b, bm;

    nn.ll = n;
    dd.ll = d;

    d0 = dd.s.low;
    d1 = dd.s.high;
    n0 = nn.s.low;
    n1 = nn.s.high;

    if (d1 == 0) {
        if (d0 > n1) {
            /* 0q = nn / 0D */

            count_leading_zeros(bm, d0);

            if (bm != 0) {
                /* Normalize, i.e. make the most significant bit of the
		 denominator set.  */

                d0 = d0 << bm;
                n1 = (n1 << bm) | (n0 >> (SI_TYPE_SIZE - bm));
                n0 = n0 << bm;
            }

            udiv_qrnnd(q0, n0, n1, n0, d0);
            q1 = 0;

            /* Remainder in n0 >> bm.  */
        } else {
            /* qq = NN / 0d */

            if (d0 == 0)
                d0 = 1 / d0; /* Divide intentionally by zero.  */

            count_leading_zeros(bm, d0);

            if (bm == 0) {
                /* From (n1 >= d0) /\ (the most significant bit of d0 is set),
		 conclude (the most significant bit of n1 is set) /\ (the
		 leading quotient digit q1 = 1).

		 This special case is necessary, not an optimization.
		 (Shifts counts of SI_TYPE_SIZE are undefined.)  */

                n1 -= d0;
                q1 = 1;
            } else {
                /* Normalize.  */

                b = SI_TYPE_SIZE - bm;

                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;

                udiv_qrnnd(q1, n1, n2, n1, d0);
            }

            /* n1 != d0... */

            udiv_qrnnd(q0, n0, n1, n0, d0);

            /* Remainder in n0 >> bm.  */
        }

        if (rp != 0) {
            rr.s.low = n0 >> bm;
            rr.s.high = 0;
            *rp = rr.ll;
        }
    }

    else {
        if (d1 > n1) {
            /* 00 = nn / DD */

            q0 = 0;
            q1 = 0;

            /* Remainder in n1n0.  */
            if (rp != 0) {
                rr.s.low = n0;
                rr.s.high = n1;
                *rp = rr.ll;
            }
        } else {
            /* 0q = NN / dd */

            count_leading_zeros(bm, d1);
            if (bm == 0) {
                /* From (n1 >= d1) /\ (the most significant bit of d1 is set),
		 conclude (the most significant bit of n1 is set) /\ (the
		 quotient digit q0 = 0 or 1).

		 This special case is necessary, not an optimization.  */

                /* The condition on the next line takes advantage of that
		 n1 >= d1 (true due to program flow).  */
                if (n1 > d1 || n0 >= d0) {
                    q0 = 1;
                    sub_ddmmss(n1, n0, n1, n0, d1, d0);
                } else
                    q0 = 0;

                q1 = 0;

                if (rp != 0) {
                    rr.s.low = n0;
                    rr.s.high = n1;
                    *rp = rr.ll;
                }
            } else {
                USItype m1, m0;
                /* Normalize.  */

                b = SI_TYPE_SIZE - bm;

                d1 = (d1 << bm) | (d0 >> b);
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;

                udiv_qrnnd(q0, n1, n2, n1, d1);
                umul_ppmm(m1, m0, q0, d0);

                if (m1 > n1 || (m1 == n1 && m0 > n0)) {
                    q0--;
                    sub_ddmmss(m1, m0, m1, m0, d1, d0);
                }

                q1 = 0;

                /* Remainder in (n1n0 - m1m0) >> bm.  */
                if (rp != 0) {
                    sub_ddmmss(n1, n0, n1, n0, m1, m0);
                    rr.s.low = (n1 << b) | (n0 >> bm);
                    rr.s.high = n1 >> bm;
                    *rp = rr.ll;
                }
            }
        }
    }

    ww.s.low = q0;
    ww.s.high = q1;
    return ww.ll;
}

#undef USItype
#undef UDItype
#undef DIunion
#undef SI_TYPE_SIZE
#undef __BITS4
#undef __ll_B
#undef __ll_lowpart
#undef __ll_highpart
#undef __clz_tab
#undef udiv_qrnnd
#undef umul_ppmm
#undef sub_ddmmss
#undef __udiv_qrnnd_c
#undef count_leading_zeros

ASM_FUNC(InitHeap, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                   "    jr $t2 # maspsx-keep\n"
                   "    addiu $t1, $zero, 0x39 # maspsx-keep\n"
                   "    nop # maspsx-keep\n")

ASM_FUNC(_bu_init, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                   "    jr $t2 # maspsx-keep\n"
                   "    addiu $t1, $zero, 0x70 # maspsx-keep\n"
                   "    nop # maspsx-keep\n")

/* BIOS calls, B table (0xB0). */
ASM_FUNC(OpenEvent, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                    "    jr $t2 # maspsx-keep\n"
                    "    addiu $t1, $zero, 0x8 # maspsx-keep\n"
                    "    nop # maspsx-keep\n")

ASM_FUNC(CloseEvent, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                     "    jr $t2 # maspsx-keep\n"
                     "    addiu $t1, $zero, 0x9 # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

ASM_FUNC(TestEvent, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                    "    jr $t2 # maspsx-keep\n"
                    "    addiu $t1, $zero, 0xB # maspsx-keep\n"
                    "    nop # maspsx-keep\n")

ASM_FUNC(EnableEvent, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                      "    jr $t2 # maspsx-keep\n"
                      "    addiu $t1, $zero, 0xC # maspsx-keep\n"
                      "    nop # maspsx-keep\n")

ASM_FUNC(DisableEvent, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                       "    jr $t2 # maspsx-keep\n"
                       "    addiu $t1, $zero, 0xD # maspsx-keep\n"
                       "    nop # maspsx-keep\n")

ASM_FUNC(InitPAD, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                  "    jr $t2 # maspsx-keep\n"
                  "    addiu $t1, $zero, 0x12 # maspsx-keep\n"
                  "    nop # maspsx-keep\n")

ASM_FUNC(StartPAD, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                   "    jr $t2 # maspsx-keep\n"
                   "    addiu $t1, $zero, 0x13 # maspsx-keep\n"
                   "    nop # maspsx-keep\n")

void EnterCriticalSection(void) {
    __asm__("addiu $a0, $zero, 1\n\t"
            "syscall 0");
}

void ExitCriticalSection(void) {
    __asm__("addiu $a0, $zero, 2\n\t"
            "syscall 0");
}

void SwEnterCriticalSection(void) {
    __asm__("mfc0 $a0, $12\n\t"
            "nop\n\t"
            "addiu $at, $zero, -0x402\n\t"
            "and $a0, $a0, $at\n\t"
            "mtc0 $a0, $12\n\t"
            "nop");
}

ASM_FUNC(SwExitCriticalSection, "    mfc0 $a0, $12 # maspsx-keep\n"
                                "    nop # maspsx-keep\n"
                                "    ori $a0, $a0, 0x401 # maspsx-keep\n"
                                "    mtc0 $a0, $12 # maspsx-keep\n"
                                "    nop # maspsx-keep\n"
                                "    jr $ra # maspsx-keep\n"
                                "    nop # maspsx-keep\n"
                                "    nop # maspsx-keep\n")

ASM_FUNC(open, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
               "    jr $t2 # maspsx-keep\n"
               "    addiu $t1, $zero, 0x32 # maspsx-keep\n"
               "    nop # maspsx-keep\n")

ASM_FUNC(close, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                "    jr $t2 # maspsx-keep\n"
                "    addiu $t1, $zero, 0x36 # maspsx-keep\n"
                "    nop # maspsx-keep\n")

ASM_FUNC(format, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x41 # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(firstfile, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                    "    jr $t2 # maspsx-keep\n"
                    "    addiu $t1, $zero, 0x42 # maspsx-keep\n"
                    "    nop # maspsx-keep\n")

ASM_FUNC(nextfile, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                   "    jr $t2 # maspsx-keep\n"
                   "    addiu $t1, $zero, 0x43 # maspsx-keep\n"
                   "    nop # maspsx-keep\n")

ASM_FUNC(delete, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x45 # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(ChangeClearPAD, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                         "    jr $t2 # maspsx-keep\n"
                         "    addiu $t1, $zero, 0x5B # maspsx-keep\n"
                         "    nop # maspsx-keep\n")

ASM_FUNC(GetGp, "    jr $ra # maspsx-keep\n"
                "    addu $v0, $gp, $zero # maspsx-keep\n"
                "    nop # maspsx-keep\n"
                "    nop # maspsx-keep\n")

/* SPDX-License-Identifier: MIT */

typedef struct {
    u16 count;
    u16 pad0;
    u16 mode;
    u16 pad1;
    u16 target;
    u16 pad2[3];
} RCnt;

extern u32 D_8009B9E8[];

long SetRCnt(long timer, unsigned short target, long mode) {
    RCnt *r;
    long md;
    int t;
    int isLow;
    u32 addr;
    register int result asm("v0");

    t = timer & 0xFFFF;
    if (t >= 3) {
        return 0;
    }
    md = 0x48;
    r = (RCnt *)(t * 16 + (u32)D_8009B9E8[0]);
    isLow = (unsigned)t < 2;
    r->mode = 0;
    r->target = target;
    do {
    } while (0);
    asm("" : : "r"(timer));
    if (isLow) {
        if (mode & 0x10) {
            md = 0x49;
        }
        if (!(mode & 1)) {
            md |= 0x100;
        }
    } else if (t == 2) {
        if (!(mode & 1)) {
            md = 0x248;
        }
    }
    if (mode & 0x1000) {
        md |= 0x10;
    }
    addr = t * 16;
    do {
    } while (0);
    result = 1;
    asm("" : : "r"(result));
    addr += (u32)D_8009B9E8[0];
    ((RCnt *)addr)->mode = md;
    return result;
}

long GetRCnt(long timer) {
    if ((timer & 0xFFFF) >= 3) {
        return 0;
    }
    return *(volatile u16 *)((timer & 0xFFFF) * 16 + (u32)D_8009B9E8[0]);
}

/* SPDX-License-Identifier: MIT */

extern u32 D_8009B9E4[];
extern u32 D_8009B9EC[];

int StartRCnt(int timer) {
    u32 *p;

    p = (u32 *)D_8009B9E4[0];
    *(volatile u32 *)&p[1] = p[1] | D_8009B9EC[timer & 0xFFFF];
    return (timer & 0xFFFF) < 3;
}

/* SPDX-License-Identifier: MIT */

int StopRCnt(int timer) {
    u32 *p;

    p = (u32 *)D_8009B9E4[0];
    p[1] = ~D_8009B9EC[timer & 0xFFFF] & p[1];
    return 1;
}

long ResetRCnt(long timer) {
    if ((timer & 0xFFFF) >= 3) {
        return 0;
    }
    *(volatile u16 *)((timer & 0xFFFF) * 16 + (u32)D_8009B9E8[0]) = 0;
    return 1;
}

/* SPDX-License-Identifier: MIT */

extern int CdGetToc2(int session, CdlLOC *table);

int CdGetToc(u8 *toc) {
    return CdGetToc2(1, toc);
}

extern s32 CD_debug;
extern char D_80090110[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090110);
extern char D_80090120[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090120);
extern char D_8009013C[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_8009013C);

#ifdef NON_MATCHING
/* 2026-10-17: same control flow as retail but 0x228 bytes against 0x224.
 * Retail gives first the lowest saved register and reuses the register that
 * held the result address as the table pointer. */
/* Reads the first and last track and the start of each track. Returns the
 * number of tracks, or 0 on failure. */
int CdGetToc2(int session, CdlLOC *table) {
    u8 param[4];
    u8 result[8];
    s32 first;
    s32 last;
    s32 n;
    s32 i;
    u32 a;
    u32 b;
    CdlCB old;

    param[0] = 1;
    old = CdSyncCallback(0);
    if (CdControlB(CdlGetTN, 0, result) != 0) {
        a = result[1];
        b = result[2];
        first = (a >> 4) * 10 + (a & 0xF);
        last = (b >> 4) * 10 + (b & 0xF);
        if (CD_debug >= 2) {
            printf(D_80090110, first, last);
        }
        param[0] = 0;
        if (CdControlB(CdlGetTD, param, result) != 0) {
            table[0].minute = result[1];
            table[0].sector = 0;
            table[0].second = result[2];
            n = 1;
            if (first <= last) {
                do {
                    param[0] = ((first / 10) << 4) + (first % 10);
                    n++;
                    if (CdControlB(CdlGetTD, param, result) == 0) {
                        goto fail;
                    }
                    table[n - 1].minute = result[1];
                    first++;
                    table[n - 1].sector = 0;
                    table[n - 1].second = result[2];
                } while (first <= last);
            }
            n--;
            if (CD_debug >= 2) {
                for (i = 0; i <= n; i++) {
                    printf(D_80090120, table[i].minute, table[i].second);
                }
            }
            CdSyncCallback(old);
            return n;
        }
    }
fail:
    if (CD_debug != 0) {
        printf(D_8009013C);
    }
    CdSyncCallback(old);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", CdGetToc2);
#endif

extern CdlCB CdSyncCallback(CdlCB func);
extern CdlCB CdReadyCallback(CdlCB func);
extern CdlCB CdReadCallback(CdlCB func);
extern void func_80074C98(void);
extern void func_80074CC0(void);
extern void func_80074CE8(void);
extern int printf(const char *, ...);
extern char D_80090150[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090150);
int CdInit(void) {
    s32 retry;
    retry = 4;
again:
    if (CdReset(1) != 1) {
        retry--;
        if (retry != -1)
            goto again;
        printf(D_80090150);
        return 0;
    }
    CdSyncCallback((CdlCB)func_80074C98);
    CdReadyCallback((CdlCB)func_80074CC0);
    CdReadCallback((CdlCB)func_80074CE8);
    return 1;
}
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090168);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800902AC);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800902BC);

/* SPDX-License-Identifier: MIT */

extern void DeliverEvent(unsigned long ev1, unsigned long ev2);

void func_80074C98(void) {
    DeliverEvent(0xF0000003, 0x20);
}

/* SPDX-License-Identifier: MIT */

void func_80074CC0(void) {
    DeliverEvent(0xF0000003, 0x40);
}

/* SPDX-License-Identifier: MIT */

void func_80074CE8(void) {
    DeliverEvent(0xF0000003, 0x40);
}

ASM_FUNC(DeliverEvent, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                       "    jr $t2 # maspsx-keep\n"
                       "    addiu $t1, $zero, 0x7 # maspsx-keep\n"
                       "    nop # maspsx-keep\n")

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA8C[];

char CdStatus(void) {
    return D_8009BA8C[0];
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA9C[];

extern CdlCB CD_cbsync;
extern CdlCB CD_cbready;
extern u8 CD_mode;
extern u8 CD_com;

int CdMode(void) {
    return CD_mode;
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA9D[];

int CdLastCom(void) {
    return CD_com;
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA98[];

unsigned char *CdLastPos(void) {
    return D_8009BA98;
}

/* SPDX-License-Identifier: MIT */

extern void CD_initintr(void);
extern int CD_init(void);
extern int CD_initvol(void);

int CdReset(int mode) {
    if (mode == CdlModeAP) {
        CD_initintr();
        return 1;
    }
    if (CD_init()) {
        return 0;
    }
    if (mode == CdlModeDA && CD_initvol()) {
        return 0;
    }
    return 1;
}

/* SPDX-License-Identifier: MIT */

extern void CD_flush(void);

void CdFlush(void) {
    CD_flush();
}

/* SPDX-License-Identifier: MIT */

extern u32 D_8009BA88[];
extern u8 D_8009BA8C[];

int CdSetDebug(int level) {
    int old;

    old = D_8009BA88[0];
    ((u32 *)D_8009BA8C)[-1] = level;
    return old;
}

/* SPDX-License-Identifier: MIT */

extern char *D_8009BAA0[];
extern char D_80090168[];

char *CdComstr(unsigned char com) {
    if (com > 0x1B) {
        return D_80090168;
    }
    return D_8009BAA0[com];
}

/* SPDX-License-Identifier: MIT */

extern char *D_8009BB20[];
extern char D_80090168[];

char *CdIntstr(u8 intr) {
    if (intr > 6) {
        return D_80090168;
    }
    return D_8009BB20[intr];
}

/* SPDX-License-Identifier: MIT */

extern int CD_sync(int mode, u8 *result);

int CdSync(int mode, u8 *result) {
    return CD_sync(mode, result);
}

/* SPDX-License-Identifier: MIT */

extern int CD_ready(int mode, u8 *result);

int CdReady(int mode, u8 *result) {
    return CD_ready(mode, result);
}

/* SPDX-License-Identifier: MIT */

extern u32 D_8009BA7C[];
extern u32 D_8009BA80[];

CdlCB CdSyncCallback(CdlCB func) {
    CdlCB old = CD_cbsync;
    CD_cbsync = func;
    return old;
}

/* SPDX-License-Identifier: MIT */

extern u32 D_8009BA88[];

CdlCB CdReadyCallback(CdlCB func) {
    CdlCB old = CD_cbready;
    CD_cbready = func;
    return old;
}

extern u32 D_8009BA7C[];
extern u32 D_8009B9FC[];
extern u8 D_8009BA8C[];
extern s32 CD_cw(u8, u8 *, u8 *, s32);
extern s32 CD_sync(s32, u8 *);
extern CdlCB CD_cbsync;

/* Sends a command, retrying up to four times. A command that takes a
 * position first sends CdlSetloc. Returns 0 on success and -1 on failure. */
static __inline__ s32 cd_cw(u8 com, u8 *param, u8 *result, s32 arg3) {
    CdlCB old = CD_cbsync;
    s32 count = 3;

    do {
        CD_cbsync = 0;
        if (com != CdlNop && (D_8009BA8C[0] & CdlStatShellOpen)) {
            CD_cw(CdlNop, 0, 0, 0);
        }
        if (param == 0 || D_8009B9FC[com] == 0 ||
            !CD_cw(CdlSetloc, param, result, 0)) {
            CD_cbsync = old;
            if (!CD_cw(com, param, result, arg3)) {
                return 0;
            }
        }
    } while (--count != -1);

    CD_cbsync = old;
    return -1;
}

int CdControl(u_char com, u_char *param, u_char *result) {
    return cd_cw(com, param, result, 0) == 0;
}

extern u32 D_8009BA7C[];
extern u32 D_8009B9FC[];
extern u8 D_8009BA8C[];
extern s32 CD_cw(u8, u8 *, u8 *, s32);
extern s32 CD_sync(s32, u8 *);
int CdControlF(u_char com, u_char *param) {
    return cd_cw(com, param, 0, 1) == 0;
}

int CdControlB(u_char com, u_char *param, u_char *result) {
    if (cd_cw(com, param, result, 0)) {
        return 0;
    }
    return CD_sync(CdlSync, result) == CdlComplete;
}

extern int CD_vol(CdlATV *vol);

int CdMix(CdlATV *vol) {
    CD_vol(vol);
    return 1;
}

/* SPDX-License-Identifier: MIT */

extern int CD_getsector(void *madr, int size);

int CdGetSector(void *madr, int size) {
    return CD_getsector(madr, size) == 0;
}

/* SPDX-License-Identifier: MIT */

long CdDataCallback(void (*func)()) {
    return (long)DMACallback(3, func);
}

/* SPDX-License-Identifier: MIT */

extern int CD_datasync(int mode);

void CdDataSync(int mode) {
    CD_datasync(mode);
}

CdlLOC *CdIntToPos(int i, CdlLOC *p) {
    i += 150;
    p->sector = (i % 75) / 10 * 16 + (i % 75) % 10;
    i /= 75;
    p->second = (i % 60) / 10 * 16 + (i % 60) % 10;
    i /= 60;
    p->minute = i / 10 * 16 + i % 10;
    return p;
}

int CdPosToInt(CdlLOC *p) {
#define DECODE_BCD(x) (((x) >> 4) * 10 + ((x) & 0xF))

    u8 sector = p->sector;
    u8 second = p->second;
    u8 minute = p->minute;

    return (DECODE_BCD(minute) * 60 + DECODE_BCD(second)) * 75 +
           DECODE_BCD(sector) - 150;
}

INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800902D8);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800902E4);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090300);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090314);
extern u32 D_8009BD40[];
extern u32 D_8009BD44[];
extern u32 D_8009BD48[];
extern u32 D_8009BD4C[];
extern u32 D_8009BA88[];
extern u32 D_8009BA90[];
extern s32 D_8009BA94[];
extern u8 D_8009BA9D[];
extern s32 D_8009BB40[];
extern s32 D_8009BC40[];
extern u8 D_8009BD58[];
extern u8 D_8009BD59[];
extern u8 D_8009BD5A[];
extern u8 D_800A8CB8[];
extern u8 D_800A8CC0[];
extern u8 D_800A8CC8[];
extern char D_800902D8[];
extern char D_800902E4[];
extern char D_80090300[];
extern char D_80090314[];

typedef char Result_t[8];

typedef struct {
    u8 sync;  /* sync state */
    u8 ready; /* ready state */
    u8 c;
} CD_intr;

typedef struct Alarm_t {
    s32 unk0;
    s32 unk4;
    char *unk8;
} Alarm_t;

extern volatile CD_intr Intr;
extern Result_t CD_resultSync;
extern Result_t CD_resultReady;
extern Result_t CD_resultC;
extern volatile Alarm_t Alarm;
extern CdlCB CD_cbready;
extern s32 CD_debug;
extern s32 CD_status;
extern s32 CD_status1;
extern s32 CD_nopen;
extern u8 CD_pos[];
extern u8 CD_mode;
extern u8 CD_com;
extern char *CD_comstr[];
extern char *CD_intrstr[];
extern s32 CD_cmdParams[];
extern s32 CD_cmdPos[];
extern volatile u8 *libcd_CDRegister0;
extern volatile u8 *libcd_CDRegister1;
extern volatile u8 *libcd_CDRegister2;
extern volatile u8 *libcd_CDRegister3;
extern volatile s32 *CD_comDelay;
extern char CD_info[];
extern volatile s32 *CD_dmaChcr;
extern s32 CheckCallback(void);
extern void CD_flush(void);
extern int getintr(void);

static __inline__ void CD_memcpy(void *_dst, void *_src, u32 _size) {
    char *pDst = (char *)_dst;
    char *pSrc = (char *)_src;

    if (pDst == 0) {
        return;
    }

    while (_size--) {
        *pDst++ = *pSrc++;
    }
}

extern s32 CD_cmdAck[];
extern s32 CD_cmdStat[];
extern char D_800902D8[];
extern char D_800902E4[];
extern char D_80090300[];
extern char D_80090314[];

s32 getintr(void) {
    volatile char nReg;
    volatile Result_t buf;
    s32 i, j;
    s32 bHasError;

    *libcd_CDRegister0 = 1;

    nReg = *libcd_CDRegister3 & 0x7;

    if (nReg == 0) {
        return 0;
    }

    bHasError = 0;

    while (nReg != (*libcd_CDRegister3 & 7)) {
        nReg = *libcd_CDRegister3 & 0x7;
    }

    for (i = 0; i < 8; i++) {
        if ((*libcd_CDRegister0 & 0x20) == 0) {
            break;
        }
        buf[i] = *libcd_CDRegister1;
    }
    for (j = i; j < 8; j++) {
        buf[j] = 0;
    }

    *libcd_CDRegister0 = 1;
    *libcd_CDRegister3 = 7;
    *libcd_CDRegister2 = 7;
    if (nReg != 3 || CD_cmdStat[CD_com]) {
        if (!(CD_status & CdlStatShellOpen) && (buf[0] & CdlStatShellOpen)) {
            CD_nopen++;
        }
        CD_status = buf[0];
        CD_status1 = buf[1];
        bHasError = CD_status;
        bHasError &= (CdlStatError | CdlStatSeekError | CdlStatIdError |
                      CdlStatShellOpen);
    }
    if (nReg == 5) {
        puts(D_800902D8);
        if (CD_debug > 0) {
            printf(D_800902E4, CD_comstr[CD_com], CD_status, CD_status1);
        }
    }
    switch (nReg) {
    case 3:
        if (bHasError) {
            Intr.sync = CdlDiskError;
            CD_memcpy(&CD_resultSync, &buf, sizeof(Result_t));
            return 2;
        }
        if (CD_cmdAck[CD_com]) {
            Intr.sync = CdlAcknowledge;
            CD_memcpy(&CD_resultSync, &buf, sizeof(Result_t));
            return 1;
        }
        Intr.sync = CdlComplete;
        CD_memcpy(&CD_resultSync, &buf, sizeof(Result_t));
        return 2;
    case 2:
        Intr.sync = bHasError ? CdlDiskError : CdlComplete;
        CD_memcpy(&CD_resultSync, &buf, sizeof(Result_t));
        return 2;
    case 1:
        if (bHasError && i == 1) {
            bHasError = 0;
        }
        Intr.ready = bHasError ? CdlDiskError : CdlDataReady;
        CD_memcpy(&CD_resultReady, &buf, sizeof(Result_t));
        *libcd_CDRegister0 = 0;
        *libcd_CDRegister3 = 0;
        return 4;
    case 4:
        Intr.ready = Intr.c = CdlDataEnd;
        CD_memcpy(&CD_resultC, &buf, sizeof(Result_t));
        CD_memcpy(&CD_resultReady, &buf, sizeof(Result_t));
        return 4;
    case 5:
        Intr.sync = Intr.ready = CdlDiskError;
        CD_memcpy(&CD_resultSync, &buf, sizeof(Result_t));
        CD_memcpy(&CD_resultReady, &buf, sizeof(Result_t));
        return 6;
    default:
        puts(D_80090300);
        printf(D_80090314, nReg);
        return 0;
    }
}

static __inline__ void CD_setAlarm(char *name) {
    /* schedule a timeout 960 vblanks from now */
    ((Alarm_t *)&Alarm)->unk0 = VSync(-1) + 960;
    ((Alarm_t *)&Alarm)->unk4 = 0;
    ((Alarm_t *)&Alarm)->unk8 = name;
}

extern char D_800902AC[];
extern char D_800902BC[];

static __inline__ s32 CD_getAlarm(void) {
    if (((Alarm_t *)&Alarm)->unk0 < VSync(-1) ||
        ((Alarm_t *)&Alarm)->unk4++ > 0x3C0000) {
        puts(D_800902AC);
        printf(D_800902BC, ((Alarm_t *)&Alarm)->unk8, CD_comstr[CD_com],
               CD_intrstr[Intr.sync], CD_intrstr[Intr.ready]);
        CD_flush();
        return -1;
    }
    return 0;
}

static __inline__ void CD_callback(void) {
    s32 interrupt;
    u8 temp_s1;

    temp_s1 = *libcd_CDRegister0 & 3;

    while (1) {
        interrupt = getintr();
        if (interrupt == 0) {
            break;
        }

        if ((interrupt & 4) && CD_cbready != 0) {
            CD_cbready(Intr.ready, CD_resultReady);
        }
        if ((interrupt & 2) && CD_cbsync != 0) {
            CD_cbsync(Intr.sync, CD_resultSync);
        }
    }
    *libcd_CDRegister0 = temp_s1;
}

extern char D_80090334[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090334);
extern char D_8009033C[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_8009033C);
extern char D_80090348[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090348);
extern char D_80090350[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090350);
extern char D_80090360[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090360);

s32 CD_sync(s32 mode, u8 *result) {
    s32 i;
    s32 sync;

    CD_setAlarm(D_80090334);

    while (1) {
        if (CD_getAlarm()) {
            return -1;
        }

        if (CheckCallback()) {
            CD_callback();
        }

        sync = Intr.sync;
        if (sync == CdlComplete || sync == CdlDiskError) {
            Intr.sync = CdlComplete;
            CD_memcpy(result, CD_resultSync, sizeof(Result_t));
            return sync;
        }

        if (mode != 0) {
            return 0;
        }
    }
}

s32 CD_ready(s32 mode, u8 *result) {
    s32 i;
    s32 c;
    s32 ready;

    CD_setAlarm(D_8009033C);
    while (1) {
        if (CD_getAlarm()) {
            return -1;
        }
        if (CheckCallback()) {
            CD_callback();
        }
        c = Intr.c;
        if (c != 0) {
            Intr.c = 0;
            CD_memcpy(result, CD_resultC, sizeof(Result_t));
            return c;
        }
        ready = Intr.ready;
        if (ready != 0) {
            Intr.ready = 0;
            CD_memcpy(result, CD_resultReady, sizeof(Result_t));
            return ready;
        }
        if (mode != 0) {
            return 0;
        }
    }
}

s32 CD_cw(u8 com, u8 *param, u8 *result, s32 arg3) {
    s32 i;

    if (CD_debug > 1) {
        printf(D_80090348, CD_comstr[com]);
    }
    if ((CD_cmdPos[com] != 0) && (param == 0)) {
        if (CD_debug > 0) {
            printf(D_80090350, CD_comstr[com]);
        }
        return -2;
    }
    CD_sync(CdlSync, 0);
    if (com == CdlSetloc) {
        for (i = 0; i < 4; i++) {
            CD_pos[i] = param[i];
        }
    }
    Intr.sync = CdlNoIntr;
    if (CD_cmdParams[com]) {
        Intr.ready = CdlNoIntr;
    }
    *libcd_CDRegister0 = 0;
    for (i = 0; i < CD_cmdParams[com + 0x40]; i++) {
        *libcd_CDRegister2 = param[i];
    }
    CD_com = com;
    *libcd_CDRegister1 = com;
    if (arg3 != 0) {
        return 0;
    }

    CD_setAlarm(D_80090360);

    while (Intr.sync == CdlNoIntr) {
        if (CD_getAlarm()) {
            return -1;
        }
        if (CheckCallback()) {
            CD_callback();
        }
    }
    if (Intr.sync == CdlComplete && com == CdlSetmode) {
        CD_mode = *param;
    }

    CD_memcpy(result, CD_resultSync, sizeof(Result_t));

    return -(Intr.sync == CdlDiskError);
}

extern u32 D_8009BD40[];
extern u32 D_8009BD44[];
extern u32 D_8009BD48[];
extern u32 D_8009BD4C[];

s32 CD_vol(CdlATV *vol) {
    *libcd_CDRegister0 = 2;
    *libcd_CDRegister2 = vol->val0;
    *libcd_CDRegister3 = vol->val1;
    *libcd_CDRegister0 = 3;
    *libcd_CDRegister1 = vol->val2;
    *libcd_CDRegister2 = vol->val3;
    *libcd_CDRegister3 = 0x20;
    return 0;
}

extern u8 D_8009BD58[];
extern u8 D_8009BD59[];
extern u8 D_8009BD5A[];
extern u32 D_8009BD50[];

extern u32 D_8009BD40[];
extern u32 D_8009BD44[];
extern u32 D_8009BD48[];
extern u32 D_8009BD4C[];
extern u32 D_8009BD50[];
extern u8 D_8009BD58[];
extern u8 D_8009BD59[];
extern u8 D_8009BD5A[];

void CD_flush(void) {
    *libcd_CDRegister0 = 1;
    while (*libcd_CDRegister3 & 7) {
        *libcd_CDRegister0 = 1;
        *libcd_CDRegister3 = 7;
        *libcd_CDRegister2 = 7;
    }

    Intr.ready = Intr.c = CdlNoIntr;
    Intr.sync = CdlComplete;
    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0;
    *CD_comDelay = 0x1325;
}

extern u32 D_8009BD54[];
typedef struct CdSpuRegs {
    u8 pad0[0x180];
    volatile s16 mainVolLeft;
    volatile s16 mainVolRight;
    u8 pad1[0x1AA - 0x184];
    volatile u16 spucnt;
    u8 pad2[0x1B0 - 0x1AC];
    volatile s16 cdVolLeft;
    volatile s16 cdVolRight;
    u8 pad3[0x1B8 - 0x1B4];
    volatile s16 mainVolxLeft;
    volatile s16 mainVolxRight;
} CdSpuRegs;

extern volatile CdSpuRegs *CD_spu;

s32 CD_initvol(void) {
    CdlATV vol;

    if (CD_spu->mainVolxLeft == 0 && CD_spu->mainVolxRight == 0) {
        CD_spu->mainVolLeft = 0x3FFF;
        CD_spu->mainVolRight = 0x3FFF;
    }

    CD_spu->cdVolLeft = 0x3FFF;
    CD_spu->cdVolRight = 0x3FFF;
    CD_spu->spucnt = 0xC001;
    vol.val0 = vol.val2 = 0x80;
    vol.val1 = vol.val3 = 0;
    *libcd_CDRegister0 = 2;
    *libcd_CDRegister2 = vol.val0;
    *libcd_CDRegister3 = vol.val1;
    *libcd_CDRegister0 = 3;
    *libcd_CDRegister1 = vol.val2;
    *libcd_CDRegister2 = vol.val3;
    *libcd_CDRegister3 = 0x20;

    return 0;
}

extern u32 D_8009BA80[];
extern u32 D_8009BA7C[];
extern u32 D_8009BA90[];
extern void callback();

void CD_initintr(void) {
    CD_cbready = 0;
    CD_cbsync = 0;
    CD_status1 = 0;
    CD_status = 0;
    ResetCallback();
    InterruptCallback(2, callback);
}

extern char D_8009039C[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_8009039C);
extern char D_800903A8[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800903A8);

s32 CD_init(void) {
    puts(D_8009039C);
    printf(D_800903A8, &CD_info);
    CD_com = 0;
    CD_mode = 0;
    CD_cbready = 0;
    CD_cbsync = 0;
    CD_status1 = 0;
    CD_status = 0;
    ResetCallback();
    InterruptCallback(2, callback);

    *libcd_CDRegister0 = 1;
    while (*libcd_CDRegister3 & 7) {
        *libcd_CDRegister0 = 1;
        *libcd_CDRegister3 = 7;
        *libcd_CDRegister2 = 7;
    }

    Intr.ready = Intr.c = CdlNoIntr;
    Intr.sync = CdlComplete;

    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0;
    *CD_comDelay = 0x1325;

    CD_cw(CdlNop, 0, 0, 0);
    if (CD_status & CdlStatShellOpen) {
        CD_cw(CdlNop, 0, 0, 0);
    }

    if (CD_cw(CdlReset, 0, 0, 0)) {
        return -1;
    }

    if (CD_cw(CdlDemute, 0, 0, 0)) {
        return -1;
    }

    if (CD_sync(CdlSync, 0) != CdlComplete) {
        return -1;
    }
    return 0;
}

extern char D_800903B4[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800903B4);

s32 CD_datasync(s32 mode) {
    s32 ret;

    CD_setAlarm(D_800903B4);
    while (1) {
        if (CD_getAlarm()) {
            ret = -1;
            break;
        }
        if (!(*CD_dmaChcr & 0x01000000)) {
            ret = 0;
            break;
        }
        if (mode != 0) {
            ret = 1;
            break;
        }
    }
    return ret;
}

extern u32 D_8009BD74[];
extern u32 D_8009BD78[];
extern u32 D_8009BD7C[];
extern u32 D_8009BD80[];
extern u32 D_8009BD84[];
extern volatile s32 *CD_dmaDelay;
extern volatile s32 *CD_dpcr;
extern volatile s32 *CD_dmaMadr;
extern volatile s32 *CD_dmaBcr;

s32 CD_getsector(void *buffer, s32 size) {
    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0x80;
    *CD_dmaDelay = 0x20943;
    *CD_comDelay = 0x1323;
    *CD_dpcr |= 0x8000;
    *CD_dmaMadr = (s32)buffer;
    *CD_dmaBcr = size | 0x10000;
    while (!(*libcd_CDRegister0 & 0x40)) {
    };
    *CD_dmaChcr = 0x11000000;
    while (*CD_dmaChcr & 0x01000000) {
    };
    *CD_comDelay = 0x1325;
    return 0;
}

extern u32 D_8009BD24[];

void CD_set_test_parmnum(s32 parmNum) {
    CD_cmdPos[25] = parmNum;
}

extern u32 D_8009BD40[];
extern u8 D_8009BD58[];
extern u8 D_8009BD59[];
extern u8 D_800A8CB8[];
extern u8 D_800A8CC0[];
extern int getintr(void);
void callback(void) {
    CD_callback();
}

typedef struct {
    s32 sectors;
    u32 *unk4;
    u32 *unk8;
    s32 mode;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    CdlCB sync;
    CdlCB ready;
} cdreadStruct;

extern volatile cdreadStruct CD_read;
extern CdlCB CD_ReadCallbackFunc;
extern char D_800903C0[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800903C0);
extern s32 cd_read_retry(s32);

void cb_read(u8 arg0, u8 *result) {
    s32 pos[3];

    if (arg0 == 1) {
        if (CD_read.unk14 > 0) {
            if (CD_read.unk10 == 0x200) {
                CdGetSector(pos, 3);
                if (CdPosToInt((CdlLOC *)pos) != CD_read.unk20) {
                    puts(D_800903C0);
                    CD_read.unk14 = -1;
                }
            }
            CdGetSector(CD_read.unk8, CD_read.unk10);
            CD_read.unk8 += CD_read.unk10;
            CD_read.unk14--;
            CD_read.unk20++;
        }
    } else {
        CD_read.unk14 = -1;
    }
    CD_read.unk18 = VSync(-1);
    if (CD_read.unk14 < 0) {
        cd_read_retry(1);
    }
    if (VSync(-1) > CD_read.unk1C + 1200) {
        CD_read.unk14 = -1;
    }
    if (CD_read.unk14 && VSync(-1) <= CD_read.unk1C + 1200) {
        return;
    }
    CdSyncCallback(CD_read.sync);
    CdReadyCallback(CD_read.ready);
    CdControl(CdlPause, 0, 0);
    if (CD_ReadCallbackFunc != 0) {
        CD_ReadCallbackFunc(CD_read.unk14 == 0 ? CdlComplete : CdlDiskError,
                            result);
    }
}

extern char D_800903D8[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800903D8);
extern char D_800903F0[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800903F0);

s32 cd_read_retry(s32 retry) {
    char mode;
    s32 mode2;
    CdSyncCallback(0);
    CdReadyCallback(0);
    if (CdStatus() & CdlStatShellOpen) {
        if ((VSync(-1) % 0x40) == 0) {
            puts(D_800903D8);
        }
        CdControlF(CdlNop, 0);
        CD_read.unk1C = VSync(-1);
        CD_read.unk14 = -1;
        return CD_read.unk14;
    }
    if (retry) {
        puts(D_800903F0);
        CdControl(CdlPause, 0, 0);
        if (!CdControl(CdlSetloc, CdLastPos(), 0)) {
            return CD_read.unk14 = -1;
        }
    }
    CdFlush();
    mode2 = CD_read.mode;
    mode = mode2;
    if ((char)mode2 != CdMode() || retry) {
        if (!CdControl(CdlSetmode, (u8 *)&mode, 0)) {
            CD_read.unk14 = -1;
            return CD_read.unk14;
        }
    }
    CD_read.unk20 = CdPosToInt(CdLastPos());
    CdReadyCallback((CdlCB)&cb_read);
    CD_read.unk8 = CD_read.unk4;
    CdControlF(CdlReadN, 0);
    CD_read.unk14 = CD_read.sectors;
    CD_read.unk18 = VSync(-1);
    return CD_read.unk14;
}

extern volatile u32 D_8009BD98[];
extern u32 D_8009BD9C[];
extern u32 D_8009BD90[];
extern u32 D_8009BD8C[];
extern u32 D_8009BDB0[];
extern u32 D_8009BDB4[];
extern s32 D_8009BDA8[];
extern s32 VSync(s32);
extern char CdStatus(void);
extern s32 cd_read_retry(s32);
int CdRead(int sectors, u_long *buf, int mode) {
    CD_read.mode = mode;
    switch (CD_read.mode & (CdlModeSize0 | CdlModeSize1)) {
    case 0:
        CD_read.unk10 = 0x200;
        break;
    case CdlModeSize1:
        CD_read.unk10 = 0x249;
        break;
    default:
        CD_read.unk10 = 0x246;
        break;
    }
    CD_read.mode |= CdlModeSize1;
    CD_read.unk4 = (u32 *)buf;
    CD_read.sectors = sectors;
    CD_read.sync = CdSyncCallback(0);
    CD_read.ready = CdReadyCallback(0);
    CD_read.unk1C = VSync(-1);
    if (CdStatus() & (CdlStatPlay | CdlStatSeek | CdlStatRead)) {
        CdControlB(CdlPause, 0, 0);
    }
    return cd_read_retry(0) > 0;
}

extern s32 D_8009BDA8[];
extern s32 cd_read_retry(s32 mode);
s32 CdReadSync(s32 mode, u8 *result) {
    s32 status;
    s32 now;

    do {
        now = VSync(-1);
        if (D_8009BDA8[0] + 0x4B0 < now) {
            status = -1;
        } else if (D_8009BDA8[-2] < 0) {
            cd_read_retry(1);
            status = D_8009BDA8[-7];
        } else {
            now = VSync(-1);
            if (D_8009BDA8[-1] + 0x3C < now) {
                cd_read_retry(1);
                status = D_8009BDA8[-7];
            } else {
                status = D_8009BDA8[-2];
            }
        }
    } while (mode == 0 && status > 0);
    CdReady(1, result);
    return status;
}

/* SPDX-License-Identifier: MIT */

extern u32 D_8009BD88[];
extern u32 D_8009BD8C[];

CdlCB CdReadCallback(CdlCB func) {
    CdlCB prevFunc = CD_ReadCallbackFunc;
    CD_ReadCallbackFunc = func;
    return prevFunc;
}

extern void v_wait(int, int);
extern volatile s32 *VSync_gpuStat;
extern volatile s32 *VSync_rcnt;
extern volatile s32 Hcount;
extern volatile s32 prevVcount;
extern volatile s32 Vcount;

s32 VSync(s32 mode) {
    s32 temp_s0;
    s32 ret;
    s32 max;
    s32 waitCount;

    temp_s0 = *VSync_gpuStat;

    ret = (*VSync_rcnt - Hcount) & 0xFFFF;
    if (mode < 0) {
        return Vcount;
    }
    if (mode == 1) {
        return ret;
    }
    if (mode > 0) {
        waitCount = 1;
        waitCount = (prevVcount - waitCount) + mode;
    } else {
        waitCount = prevVcount;
    }
    max = 0;
    if (mode > 0) {
        max = mode - 1;
    }
    v_wait(waitCount, max);
    temp_s0 = *VSync_gpuStat;
    v_wait(Vcount + 1, 1);
    if ((temp_s0 & 0x80000) && ((temp_s0 ^ *VSync_gpuStat) >= 0)) {
        do {

        } while (!((temp_s0 ^ *VSync_gpuStat) & 0x80000000));
    }
    prevVcount = Vcount;
    Hcount = *VSync_rcnt;
    return ret;
}

extern s32 D_8009CE84[];
extern char D_80090404[];

/* The asm orders the D_8009CE84 load after the volatile count store. With no
 * dependence between them sched moves the load above the store, and the ra
 * save stays in the prologue; with it, the save sinks into the first branch's
 * delay slot like retail. The asm emits no code. */
void v_wait(int mode, int time) {
    volatile int count;
    int cur;

    count = time << 15;
    asm("" : "=r"(cur) : "m"(count));
    if ((cur = D_8009CE84[0]) < mode) {
        do {
            count = count - 1;
            if (count == -1) {
                puts(D_80090404);
                ChangeClearPAD(0);
                ChangeClearRCnt(3, 0);
                break;
            }
        } while (D_8009CE84[0] < mode);
    }
}
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090404);

ASM_FUNC(ChangeClearRCnt, "    addiu $t2, $zero, 0xC0 # maspsx-keep\n"
                          "    jr $t2 # maspsx-keep\n"
                          "    addiu $t1, $zero, 0xA # maspsx-keep\n"
                          "    nop # maspsx-keep\n")

extern struct Callbacks *D_8009CE50[];
void *ResetCallback(void) {
    return D_8009CE50[0]->ResetCallback();
}

extern struct Callbacks *D_8009CE50[];
Callback InterruptCallback(int irq, Callback callback) {
    return D_8009CE50[0]->InterruptCallback(irq, callback);
}

extern struct Callbacks *D_8009CE50[];
Callback DMACallback(int dma, Callback callback) {
    return D_8009CE50[0]->DMACallback(dma, callback);
}

extern struct Callbacks *D_8009CE50[];
void VSyncCallback(Callback callback) {
    D_8009CE50[0]->VSyncCallbacks(0, callback);
}

extern struct Callbacks *D_8009CE50[];
Callback VSyncCallbacks(int channel, Callback callback) {
    return D_8009CE50[0]->VSyncCallbacks(channel, callback);
}

extern struct Callbacks *D_8009CE50[];
void StopCallback(void) {
    D_8009CE50[0]->StopCallback();
}

extern struct Callbacks *D_8009CE50[];
long RestartCallback(void) {
    return (long)D_8009CE50[0]->RestartCallback();
}

extern u16 D_8009BDCA[];
int CheckCallback(void) {
    return D_8009BDCA[0];
}

extern volatile u16 *D_8009CE58[];
u16 GetIntrMask(void) {
    return *D_8009CE58[0];
}

extern volatile u16 *D_8009CE58[];
u16 SetIntrMask(u16 arg0) {
    u16 mask;
    mask = *D_8009CE58[0];
    *D_8009CE58[0] = arg0;
    return mask;
}

ASM_FUNC(startIntr,
         "    addiu      $sp, $sp, -0x18 # maspsx-keep\n"
         "    sw         $s0, 0x10($sp) # maspsx-keep\n"
         "    lui        $s0, %hi(D_8009BDC8) # maspsx-keep\n"
         "    addiu      $s0, $s0, %lo(D_8009BDC8) # maspsx-keep\n"
         "    sw         $ra, 0x14($sp) # maspsx-keep\n"
         "    lhu        $v0, 0x0($s0) # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    bnez       $v0, .L800775D0 # maspsx-keep\n"
         "    addu      $v0, $zero, $zero # maspsx-keep\n"
         "    lui        $v1, %hi(D_8009CE54) # maspsx-keep\n"
         "    lw         $v1, %lo(D_8009CE54)($v1) # maspsx-keep\n"
         "    lui        $v0, %hi(D_8009CE58) # maspsx-keep\n"
         "    lw         $v0, %lo(D_8009CE58)($v0) # maspsx-keep\n"
         "    lui        $a1, (0x33333333 >> 16) # maspsx-keep\n"
         "    sh         $zero, 0x0($v0) # maspsx-keep\n"
         "    lhu        $v0, 0x0($v0) # maspsx-keep\n"
         "    ori        $a1, $a1, (0x33333333 & 0xFFFF) # maspsx-keep\n"
         "    sh         $v0, 0x0($v1) # maspsx-keep\n"
         "    lui        $v0, %hi(D_8009CE5C) # maspsx-keep\n"
         "    lw         $v0, %lo(D_8009CE5C)($v0) # maspsx-keep\n"
         "    addu       $a0, $s0, $zero # maspsx-keep\n"
         "    sw         $a1, 0x0($v0) # maspsx-keep\n"
         "    jal        memclr # maspsx-keep\n"
         "    ori       $a1, $zero, 0x41A # maspsx-keep\n"
         "    jal        setjmp # maspsx-keep\n"
         "    addiu     $a0, $s0, 0x38 # maspsx-keep\n"
         "    beqz       $v0, .L80077580 # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    jal        trapIntr # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    .L80077580: # maspsx-keep\n"
         "    lui        $s0, %hi(D_8009BE04) # maspsx-keep\n"
         "    addiu      $s0, $s0, %lo(D_8009BE04) # maspsx-keep\n"
         "    addiu      $a0, $s0, -0x4 # maspsx-keep\n"
         "    addiu      $v0, $s0, 0xFDC # maspsx-keep\n"
         "    jal        HookEntryInt # maspsx-keep\n"
         "    sw        $v0, 0x0($s0) # maspsx-keep\n"
         "    ori        $v0, $zero, 0x1 # maspsx-keep\n"
         "    jal        startIntrVSync # maspsx-keep\n"
         "    sh        $v0, -0x3C($s0) # maspsx-keep\n"
         "    lui        $v1, %hi(D_8009CE50) # maspsx-keep\n"
         "    lw         $v1, %lo(D_8009CE50)($v1) # maspsx-keep\n"
         "    jal        startIntrDMA # maspsx-keep\n"
         "    sw        $v0, 0x14($v1) # maspsx-keep\n"
         "    lui        $a0, %hi(D_8009CE50) # maspsx-keep\n"
         "    lw         $a0, %lo(D_8009CE50)($a0) # maspsx-keep\n"
         "    jal        _96_remove # maspsx-keep\n"
         "    sw        $v0, 0x4($a0) # maspsx-keep\n"
         "    jal        ExitCriticalSection # maspsx-keep\n"
         "    addiu     $s0, $s0, -0x3C # maspsx-keep\n"
         "    addu       $v0, $s0, $zero # maspsx-keep\n"
         "    .L800775D0: # maspsx-keep\n"
         "    lw         $ra, 0x14($sp) # maspsx-keep\n"
         "    lw         $s0, 0x10($sp) # maspsx-keep\n"
         "    addiu      $sp, $sp, 0x18 # maspsx-keep\n"
         "    jr         $ra # maspsx-keep\n"
         "    nop # maspsx-keep\n")

INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090448);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090464);

ASM_FUNC(trapIntr, "    addiu      $sp, $sp, -0x28 # maspsx-keep\n"
                   "    sw         $s1, 0x14($sp) # maspsx-keep\n"
                   "    lui        $s1, %hi(D_8009BDC8) # maspsx-keep\n"
                   "    addiu      $s1, $s1, %lo(D_8009BDC8) # maspsx-keep\n"
                   "    sw         $ra, 0x24($sp) # maspsx-keep\n"
                   "    sw         $s4, 0x20($sp) # maspsx-keep\n"
                   "    sw         $s3, 0x1C($sp) # maspsx-keep\n"
                   "    sw         $s2, 0x18($sp) # maspsx-keep\n"
                   "    sw         $s0, 0x10($sp) # maspsx-keep\n"
                   "    lhu        $v0, 0x0($s1) # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    bnez       $v0, .L80077640 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    lui        $v0, %hi(D_8009CE54) # maspsx-keep\n"
                   "    lw         $v0, %lo(D_8009CE54)($v0) # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    lhu        $a1, 0x0($v0) # maspsx-keep\n"
                   "    lui        $a0, %hi(D_80090448) # maspsx-keep\n"
                   "    addiu      $a0, $a0, %lo(D_80090448) # maspsx-keep\n"
                   "    jal        printf # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    jal        ReturnFromException # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    .L80077640: # maspsx-keep\n"
                   "    lui        $a0, %hi(D_8009CE54) # maspsx-keep\n"
                   "    lw         $a0, %lo(D_8009CE54)($a0) # maspsx-keep\n"
                   "    ori        $v0, $zero, 0x1 # maspsx-keep\n"
                   "    lui        $at, %hi(D_8009BDCA) # maspsx-keep\n"
                   "    sh         $v0, %lo(D_8009BDCA)($at) # maspsx-keep\n"
                   "    lui        $v0, %hi(D_8009BDF8) # maspsx-keep\n"
                   "    lhu        $v0, %lo(D_8009BDF8)($v0) # maspsx-keep\n"
                   "    lui        $v1, %hi(D_8009CE58) # maspsx-keep\n"
                   "    lw         $v1, %lo(D_8009CE58)($v1) # maspsx-keep\n"
                   "    lhu        $a0, 0x0($a0) # maspsx-keep\n"
                   "    lhu        $v1, 0x0($v1) # maspsx-keep\n"
                   "    and        $v0, $v0, $a0 # maspsx-keep\n"
                   "    and        $s0, $v1, $v0 # maspsx-keep\n"
                   "    beqz       $s0, .L80077710 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    ori        $s3, $zero, 0x1 # maspsx-keep\n"
                   "    addiu      $s4, $s1, 0x4 # maspsx-keep\n"
                   "    .L80077684: # maspsx-keep\n"
                   "    beqz       $s0, .L800776E0 # maspsx-keep\n"
                   "    addu      $s1, $zero, $zero # maspsx-keep\n"
                   "    addu       $s2, $s4, $zero # maspsx-keep\n"
                   "    .L80077690: # maspsx-keep\n"
                   "    slti       $v0, $s1, 0xB # maspsx-keep\n"
                   "    beqz       $v0, .L800776E0 # maspsx-keep\n"
                   "    andi      $v0, $s0, 0x1 # maspsx-keep\n"
                   "    beqz       $v0, .L800776CC # maspsx-keep\n"
                   "    sllv      $v0, $s3, $s1 # maspsx-keep\n"
                   "    lui        $v1, %hi(D_8009CE54) # maspsx-keep\n"
                   "    lw         $v1, %lo(D_8009CE54)($v1) # maspsx-keep\n"
                   "    nor        $v0, $zero, $v0 # maspsx-keep\n"
                   "    sh         $v0, 0x0($v1) # maspsx-keep\n"
                   "    lw         $v0, 0x0($s2) # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    beqz       $v0, .L800776CC # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    jalr       $v0 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    .L800776CC: # maspsx-keep\n"
                   "    addiu      $s2, $s2, 0x4 # maspsx-keep\n"
                   "    srl        $s0, $s0, 1 # maspsx-keep\n"
                   "    andi       $v0, $s0, 0xFFFF # maspsx-keep\n"
                   "    bnez       $v0, .L80077690 # maspsx-keep\n"
                   "    addiu     $s1, $s1, 0x1 # maspsx-keep\n"
                   "    .L800776E0: # maspsx-keep\n"
                   "    lui        $a0, %hi(D_8009CE54) # maspsx-keep\n"
                   "    lw         $a0, %lo(D_8009CE54)($a0) # maspsx-keep\n"
                   "    lui        $v0, %hi(D_8009BDF8) # maspsx-keep\n"
                   "    lhu        $v0, %lo(D_8009BDF8)($v0) # maspsx-keep\n"
                   "    lui        $v1, %hi(D_8009CE58) # maspsx-keep\n"
                   "    lw         $v1, %lo(D_8009CE58)($v1) # maspsx-keep\n"
                   "    lhu        $a0, 0x0($a0) # maspsx-keep\n"
                   "    lhu        $v1, 0x0($v1) # maspsx-keep\n"
                   "    and        $v0, $v0, $a0 # maspsx-keep\n"
                   "    and        $s0, $v1, $v0 # maspsx-keep\n"
                   "    bnez       $s0, .L80077684 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    .L80077710: # maspsx-keep\n"
                   "    lui        $a1, %hi(D_8009CE54) # maspsx-keep\n"
                   "    lw         $a1, %lo(D_8009CE54)($a1) # maspsx-keep\n"
                   "    lui        $a2, %hi(D_8009CE58) # maspsx-keep\n"
                   "    lw         $a2, %lo(D_8009CE58)($a2) # maspsx-keep\n"
                   "    lhu        $v0, 0x0($a1) # maspsx-keep\n"
                   "    lhu        $v1, 0x0($a2) # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    and        $v0, $v0, $v1 # maspsx-keep\n"
                   "    beqz       $v0, .L80077790 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    lui        $v0, %hi(D_8009CE60) # maspsx-keep\n"
                   "    lw         $v0, %lo(D_8009CE60)($v0) # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    addiu      $v1, $v0, 0x1 # maspsx-keep\n"
                   "    slti       $v0, $v0, 0x801 # maspsx-keep\n"
                   "    lui        $at, %hi(D_8009CE60) # maspsx-keep\n"
                   "    sw         $v1, %lo(D_8009CE60)($at) # maspsx-keep\n"
                   "    bnez       $v0, .L80077798 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    lui        $a0, %hi(D_80090464) # maspsx-keep\n"
                   "    addiu      $a0, $a0, %lo(D_80090464) # maspsx-keep\n"
                   "    lhu        $a1, 0x0($a1) # maspsx-keep\n"
                   "    lhu        $a2, 0x0($a2) # maspsx-keep\n"
                   "    jal        printf # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    lui        $v0, %hi(D_8009CE54) # maspsx-keep\n"
                   "    lw         $v0, %lo(D_8009CE54)($v0) # maspsx-keep\n"
                   "    lui        $at, %hi(D_8009CE60) # maspsx-keep\n"
                   "    sw         $zero, %lo(D_8009CE60)($at) # maspsx-keep\n"
                   "    sh         $zero, 0x0($v0) # maspsx-keep\n"
                   "    j          .L80077798 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    .L80077790: # maspsx-keep\n"
                   "    lui        $at, %hi(D_8009CE60) # maspsx-keep\n"
                   "    sw         $zero, %lo(D_8009CE60)($at) # maspsx-keep\n"
                   "    .L80077798: # maspsx-keep\n"
                   "    lui        $at, %hi(D_8009BDCA) # maspsx-keep\n"
                   "    sh         $zero, %lo(D_8009BDCA)($at) # maspsx-keep\n"
                   "    jal        ReturnFromException # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    lw         $ra, 0x24($sp) # maspsx-keep\n"
                   "    lw         $s4, 0x20($sp) # maspsx-keep\n"
                   "    lw         $s3, 0x1C($sp) # maspsx-keep\n"
                   "    lw         $s2, 0x18($sp) # maspsx-keep\n"
                   "    lw         $s1, 0x14($sp) # maspsx-keep\n"
                   "    lw         $s0, 0x10($sp) # maspsx-keep\n"
                   "    addiu      $sp, $sp, 0x28 # maspsx-keep\n"
                   "    jr         $ra # maspsx-keep\n"
                   "    nop # maspsx-keep\n")

ASM_FUNC(setIntr, "    addiu      $sp, $sp, -0x28 # maspsx-keep\n"
                  "    sw         $s1, 0x14($sp) # maspsx-keep\n"
                  "    addu       $s1, $a0, $zero # maspsx-keep\n"
                  "    sw         $s2, 0x18($sp) # maspsx-keep\n"
                  "    addu       $s2, $a1, $zero # maspsx-keep\n"
                  "    lui        $a1, %hi(D_8009BDCC) # maspsx-keep\n"
                  "    addiu      $a1, $a1, %lo(D_8009BDCC) # maspsx-keep\n"
                  "    sll        $v0, $s1, 2 # maspsx-keep\n"
                  "    addu       $a0, $v0, $a1 # maspsx-keep\n"
                  "    sw         $ra, 0x24($sp) # maspsx-keep\n"
                  "    sw         $s4, 0x20($sp) # maspsx-keep\n"
                  "    sw         $s3, 0x1C($sp) # maspsx-keep\n"
                  "    sw         $s0, 0x10($sp) # maspsx-keep\n"
                  "    lw         $s4, 0x0($a0) # maspsx-keep\n"
                  "    nop # maspsx-keep\n"
                  "    beq        $s2, $s4, .L800778FC # maspsx-keep\n"
                  "    addu      $v0, $s4, $zero # maspsx-keep\n"
                  "    lhu        $v0, -0x4($a1) # maspsx-keep\n"
                  "    nop # maspsx-keep\n"
                  "    beqz       $v0, .L800778FC # maspsx-keep\n"
                  "    addu      $v0, $s4, $zero # maspsx-keep\n"
                  "    lui        $v0, %hi(D_8009CE58) # maspsx-keep\n"
                  "    lw         $v0, %lo(D_8009CE58)($v0) # maspsx-keep\n"
                  "    nop # maspsx-keep\n"
                  "    lhu        $v1, 0x0($v0) # maspsx-keep\n"
                  "    sh         $zero, 0x0($v0) # maspsx-keep\n"
                  "    beqz       $s2, .L8007785C # maspsx-keep\n"
                  "    andi      $s3, $v1, 0xFFFF # maspsx-keep\n"
                  "    ori        $v1, $zero, 0x1 # maspsx-keep\n"
                  "    sllv       $v1, $v1, $s1 # maspsx-keep\n"
                  "    sw         $s2, 0x0($a0) # maspsx-keep\n"
                  "    lhu        $v0, 0x2C($a1) # maspsx-keep\n"
                  "    or         $s3, $s3, $v1 # maspsx-keep\n"
                  "    or         $v0, $v0, $v1 # maspsx-keep\n"
                  "    j          .L80077884 # maspsx-keep\n"
                  "    sh        $v0, 0x2C($a1) # maspsx-keep\n"
                  "    .L8007785C: # maspsx-keep\n"
                  "    ori        $v0, $zero, 0x1 # maspsx-keep\n"
                  "    sllv       $v0, $v0, $s1 # maspsx-keep\n"
                  "    nor        $v0, $zero, $v0 # maspsx-keep\n"
                  "    sw         $zero, 0x0($a0) # maspsx-keep\n"
                  "    lui        $v1, %hi(D_8009BDF8) # maspsx-keep\n"
                  "    lhu        $v1, %lo(D_8009BDF8)($v1) # maspsx-keep\n"
                  "    and        $s3, $s3, $v0 # maspsx-keep\n"
                  "    and        $v1, $v1, $v0 # maspsx-keep\n"
                  "    lui        $at, %hi(D_8009BDF8) # maspsx-keep\n"
                  "    sh         $v1, %lo(D_8009BDF8)($at) # maspsx-keep\n"
                  "    .L80077884: # maspsx-keep\n"
                  "    bnez       $s1, .L800778A8 # maspsx-keep\n"
                  "    ori       $v0, $zero, 0x4 # maspsx-keep\n"
                  "    sltiu      $s0, $s2, 0x1 # maspsx-keep\n"
                  "    jal        ChangeClearPAD # maspsx-keep\n"
                  "    addu      $a0, $s0, $zero # maspsx-keep\n"
                  "    ori        $a0, $zero, 0x3 # maspsx-keep\n"
                  "    jal        ChangeClearRCnt # maspsx-keep\n"
                  "    addu      $a1, $s0, $zero # maspsx-keep\n"
                  "    ori        $v0, $zero, 0x4 # maspsx-keep\n"
                  "    .L800778A8: # maspsx-keep\n"
                  "    bne        $s1, $v0, .L800778C0 # maspsx-keep\n"
                  "    ori       $v0, $zero, 0x5 # maspsx-keep\n"
                  "    addu       $a0, $zero, $zero # maspsx-keep\n"
                  "    jal        ChangeClearRCnt # maspsx-keep\n"
                  "    sltiu     $a1, $s2, 0x1 # maspsx-keep\n"
                  "    ori        $v0, $zero, 0x5 # maspsx-keep\n"
                  "    .L800778C0: # maspsx-keep\n"
                  "    bne        $s1, $v0, .L800778D8 # maspsx-keep\n"
                  "    ori       $v0, $zero, 0x6 # maspsx-keep\n"
                  "    ori        $a0, $zero, 0x1 # maspsx-keep\n"
                  "    jal        ChangeClearRCnt # maspsx-keep\n"
                  "    sltiu     $a1, $s2, 0x1 # maspsx-keep\n"
                  "    ori        $v0, $zero, 0x6 # maspsx-keep\n"
                  "    .L800778D8: # maspsx-keep\n"
                  "    bne        $s1, $v0, .L800778E8 # maspsx-keep\n"
                  "    ori       $a0, $zero, 0x2 # maspsx-keep\n"
                  "    jal        ChangeClearRCnt # maspsx-keep\n"
                  "    sltiu     $a1, $s2, 0x1 # maspsx-keep\n"
                  "    .L800778E8: # maspsx-keep\n"
                  "    lui        $v0, %hi(D_8009CE58) # maspsx-keep\n"
                  "    lw         $v0, %lo(D_8009CE58)($v0) # maspsx-keep\n"
                  "    nop # maspsx-keep\n"
                  "    sh         $s3, 0x0($v0) # maspsx-keep\n"
                  "    addu       $v0, $s4, $zero # maspsx-keep\n"
                  "    .L800778FC: # maspsx-keep\n"
                  "    lw         $ra, 0x24($sp) # maspsx-keep\n"
                  "    lw         $s4, 0x20($sp) # maspsx-keep\n"
                  "    lw         $s3, 0x1C($sp) # maspsx-keep\n"
                  "    lw         $s2, 0x18($sp) # maspsx-keep\n"
                  "    lw         $s1, 0x14($sp) # maspsx-keep\n"
                  "    lw         $s0, 0x10($sp) # maspsx-keep\n"
                  "    addiu      $sp, $sp, 0x28 # maspsx-keep\n"
                  "    jr         $ra # maspsx-keep\n"
                  "    nop # maspsx-keep\n")

void *stopIntr(void) {
    extern u8 D_8009BDC8[];
    extern u16 D_8009BDFA[];
    extern s32 D_8009BDFC[];
    extern volatile u16 *D_8009CE54[];
    extern volatile s32 *D_8009CE5C[];
    extern void ResetEntryInt(void);
    volatile u16 *mask;
    volatile u16 *stat;
    s32 saved;

    if (*(u16 *)&D_8009BDC8[0] == 0) {
        return 0;
    }
    EnterCriticalSection();
    mask = D_8009CE58[0];
    D_8009BDFA[0] = *mask;
    saved = *D_8009CE5C[0];
    stat = D_8009CE54[0];
    D_8009BDFC[0] = saved;
    *mask = 0;
    *stat = *mask;
    *D_8009CE5C[0] &= 0x77777777;
    ResetEntryInt();
    *(u16 *)&D_8009BDC8[0] = 0;
    return D_8009BDC8;
}

void *restartIntr(void) {
    extern u8 D_8009BDC8[];
    extern u16 D_8009BDFA[];
    extern s32 D_8009BDFC[];
    extern volatile s32 *D_8009CE5C[];
    extern void HookEntryInt(void *);

    if (*(u16 *)&D_8009BDC8[0] != 0) {
        return 0;
    }
    HookEntryInt(&D_8009BDC8[0x38]);
    *(u16 *)&D_8009BDC8[0] = 1;
    *D_8009CE58[0] = D_8009BDFA[0];
    *D_8009CE5C[0] = D_8009BDFC[0];
    ExitCriticalSection();
    return D_8009BDC8;
}

void memclr(void *ptr, size_t size) {
    int *end;
    end = (int *)ptr;
    while (size--) {
        *end++ = 0;
    }
}

ASM_FUNC(_96_remove, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                     "    jr $t2 # maspsx-keep\n"
                     "    addiu $t1, $zero, 0x72 # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

ASM_FUNC(ReturnFromException, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                              "    jr $t2 # maspsx-keep\n"
                              "    addiu $t1, $zero, 0x17 # maspsx-keep\n"
                              "    nop # maspsx-keep\n")

ASM_FUNC(ResetEntryInt, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                        "    jr $t2 # maspsx-keep\n"
                        "    addiu $t1, $zero, 0x18 # maspsx-keep\n"
                        "    nop # maspsx-keep\n")

ASM_FUNC(HookEntryInt, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                       "    jr $t2 # maspsx-keep\n"
                       "    addiu $t1, $zero, 0x19 # maspsx-keep\n"
                       "    nop # maspsx-keep\n")

/* SPDX-License-Identifier: MIT */

extern Callback D_8009CE64[];
extern s32 D_8009CE84[];
extern s32 *D_8009CE88[];
extern void trapIntrVSync(void);
Callback setIntrVSync(int index, Callback callback);
void memclr_80077BBC(void *ptr, size_t size);

Callback startIntrVSync(void) {
    *D_8009CE88[0] = 0x107;
    D_8009CE84[0] = 0;
    memclr_80077BBC(D_8009CE64, 8);
    InterruptCallback(0, trapIntrVSync);
    return setIntrVSync;
}

ASM_FUNC(trapIntrVSync,
         "    lui        $v0, %hi(D_8009CE84) # maspsx-keep\n"
         "    lw         $v0, %lo(D_8009CE84)($v0) # maspsx-keep\n"
         "    addiu      $sp, $sp, -0x20 # maspsx-keep\n"
         "    sw         $s1, 0x14($sp) # maspsx-keep\n"
         "    addu       $s1, $zero, $zero # maspsx-keep\n"
         "    sw         $s0, 0x10($sp) # maspsx-keep\n"
         "    lui        $s0, %hi(D_8009CE64) # maspsx-keep\n"
         "    addiu      $s0, $s0, %lo(D_8009CE64) # maspsx-keep\n"
         "    sw         $ra, 0x18($sp) # maspsx-keep\n"
         "    addiu      $v0, $v0, 0x1 # maspsx-keep\n"
         "    lui        $at, %hi(D_8009CE84) # maspsx-keep\n"
         "    sw         $v0, %lo(D_8009CE84)($at) # maspsx-keep\n"
         "    lui        $v0, %hi(D_8009CE84) # maspsx-keep\n"
         "    lw         $v0, %lo(D_8009CE84)($v0) # maspsx-keep\n"
         "    .L80077B50: # maspsx-keep\n"
         "    lw         $v0, 0x0($s0) # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    beqz       $v0, .L80077B68 # maspsx-keep\n"
         "    addiu     $s0, $s0, 0x4 # maspsx-keep\n"
         "    jalr       $v0 # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    .L80077B68: # maspsx-keep\n"
         "    addiu      $s1, $s1, 0x1 # maspsx-keep\n"
         "    slti       $v0, $s1, 0x8 # maspsx-keep\n"
         "    bnez       $v0, .L80077B50 # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    lw         $ra, 0x18($sp) # maspsx-keep\n"
         "    lw         $s1, 0x14($sp) # maspsx-keep\n"
         "    lw         $s0, 0x10($sp) # maspsx-keep\n"
         "    addiu      $sp, $sp, 0x20 # maspsx-keep\n"
         "    jr         $ra # maspsx-keep\n"
         "    nop # maspsx-keep\n")

/* SPDX-License-Identifier: MIT */

extern Callback D_8009CE64[];

Callback setIntrVSync(int index, Callback callback) {
    Callback previous;

    previous = D_8009CE64[index];
    if (callback != previous) {
        D_8009CE64[index] = callback;
    }
    return previous;
}

void memclr_80077BBC(void *ptr, size_t size) {
    int *end;
    end = (int *)ptr;
    while (size--) {
        *end++ = 0;
    }
}

/* SPDX-License-Identifier: MIT */

extern Callback D_8009CE90[];
extern s32 *D_8009CE8C[];
extern void trapIntrDMA(void);
Callback setIntrDMA(int index, Callback callback);
void memclr_80077E64(void *ptr, size_t size);

Callback startIntrDMA(void) {
    memclr_80077E64(D_8009CE90, 8);
    *(volatile s32 *)D_8009CE8C[0] = 0;
    InterruptCallback(3, trapIntrDMA);
    return setIntrDMA;
}

INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090480);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_8009049C);

ASM_FUNC(trapIntrDMA,
         "    lui        $v0, %hi(D_8009CE8C) # maspsx-keep\n"
         "    lw         $v0, %lo(D_8009CE8C)($v0) # maspsx-keep\n"
         "    addiu      $sp, $sp, -0x30 # maspsx-keep\n"
         "    sw         $ra, 0x28($sp) # maspsx-keep\n"
         "    sw         $s5, 0x24($sp) # maspsx-keep\n"
         "    sw         $s4, 0x20($sp) # maspsx-keep\n"
         "    sw         $s3, 0x1C($sp) # maspsx-keep\n"
         "    sw         $s2, 0x18($sp) # maspsx-keep\n"
         "    sw         $s1, 0x14($sp) # maspsx-keep\n"
         "    sw         $s0, 0x10($sp) # maspsx-keep\n"
         "    lw         $v0, 0x0($v0) # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    srl        $v0, $v0, 24 # maspsx-keep\n"
         "    andi       $s1, $v0, 0x7F # maspsx-keep\n"
         "    beqz       $s1, .L80077D14 # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    ori        $s4, $zero, 0x1 # maspsx-keep\n"
         "    lui        $s3, (0xFFFFFF >> 16) # maspsx-keep\n"
         "    ori        $s3, $s3, (0xFFFFFF & 0xFFFF) # maspsx-keep\n"
         "    lui        $s5, %hi(D_8009CE90) # maspsx-keep\n"
         "    addiu      $s5, $s5, %lo(D_8009CE90) # maspsx-keep\n"
         "    .L80077C8C: # maspsx-keep\n"
         "    beqz       $s1, .L80077CF0 # maspsx-keep\n"
         "    addu      $s0, $zero, $zero # maspsx-keep\n"
         "    addu       $s2, $s5, $zero # maspsx-keep\n"
         "    .L80077C98: # maspsx-keep\n"
         "    slti       $v0, $s0, 0x7 # maspsx-keep\n"
         "    beqz       $v0, .L80077CF0 # maspsx-keep\n"
         "    andi      $v0, $s1, 0x1 # maspsx-keep\n"
         "    beqz       $v0, .L80077CE0 # maspsx-keep\n"
         "    addiu     $v0, $s0, 0x18 # maspsx-keep\n"
         "    lui        $a0, %hi(D_8009CE8C) # maspsx-keep\n"
         "    lw         $a0, %lo(D_8009CE8C)($a0) # maspsx-keep\n"
         "    sllv       $v0, $s4, $v0 # maspsx-keep\n"
         "    lw         $v1, 0x0($a0) # maspsx-keep\n"
         "    or         $v0, $v0, $s3 # maspsx-keep\n"
         "    and        $v0, $v0, $v1 # maspsx-keep\n"
         "    sw         $v0, 0x0($a0) # maspsx-keep\n"
         "    lw         $v0, 0x0($s2) # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    beqz       $v0, .L80077CE0 # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    jalr       $v0 # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    .L80077CE0: # maspsx-keep\n"
         "    addiu      $s2, $s2, 0x4 # maspsx-keep\n"
         "    srl        $s1, $s1, 1 # maspsx-keep\n"
         "    bnez       $s1, .L80077C98 # maspsx-keep\n"
         "    addiu     $s0, $s0, 0x1 # maspsx-keep\n"
         "    .L80077CF0: # maspsx-keep\n"
         "    lui        $v0, %hi(D_8009CE8C) # maspsx-keep\n"
         "    lw         $v0, %lo(D_8009CE8C)($v0) # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    lw         $v0, 0x0($v0) # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    srl        $v0, $v0, 24 # maspsx-keep\n"
         "    andi       $s1, $v0, 0x7F # maspsx-keep\n"
         "    bnez       $s1, .L80077C8C # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    .L80077D14: # maspsx-keep\n"
         "    lui        $a1, %hi(D_8009CE8C) # maspsx-keep\n"
         "    lw         $a1, %lo(D_8009CE8C)($a1) # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    lw         $v0, 0x0($a1) # maspsx-keep\n"
         "    lui        $v1, (0xFF000000 >> 16) # maspsx-keep\n"
         "    and        $v0, $v0, $v1 # maspsx-keep\n"
         "    lui        $v1, (0x80000000 >> 16) # maspsx-keep\n"
         "    beq        $v0, $v1, .L80077D4C # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    lw         $v0, 0x0($a1) # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    andi       $v0, $v0, 0x8000 # maspsx-keep\n"
         "    beqz       $v0, .L80077D94 # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    .L80077D4C: # maspsx-keep\n"
         "    lui        $a0, %hi(D_80090480) # maspsx-keep\n"
         "    addiu      $a0, $a0, %lo(D_80090480) # maspsx-keep\n"
         "    lw         $a1, 0x0($a1) # maspsx-keep\n"
         "    jal        printf # maspsx-keep\n"
         "    addu      $s0, $zero, $zero # maspsx-keep\n"
         "    .L80077D60: # maspsx-keep\n"
         "    lui        $a0, %hi(D_8009049C) # maspsx-keep\n"
         "    addiu      $a0, $a0, %lo(D_8009049C) # maspsx-keep\n"
         "    addu       $a1, $s0, $zero # maspsx-keep\n"
         "    lui        $v0, %hi(D_8009CEB0) # maspsx-keep\n"
         "    lw         $v0, %lo(D_8009CEB0)($v0) # maspsx-keep\n"
         "    sll        $v1, $s0, 4 # maspsx-keep\n"
         "    addu       $v1, $v1, $v0 # maspsx-keep\n"
         "    lw         $a2, 0x0($v1) # maspsx-keep\n"
         "    jal        printf # maspsx-keep\n"
         "    addiu     $s0, $s0, 0x1 # maspsx-keep\n"
         "    slti       $v0, $s0, 0x7 # maspsx-keep\n"
         "    bnez       $v0, .L80077D60 # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    .L80077D94: # maspsx-keep\n"
         "    lw         $ra, 0x28($sp) # maspsx-keep\n"
         "    lw         $s5, 0x24($sp) # maspsx-keep\n"
         "    lw         $s4, 0x20($sp) # maspsx-keep\n"
         "    lw         $s3, 0x1C($sp) # maspsx-keep\n"
         "    lw         $s2, 0x18($sp) # maspsx-keep\n"
         "    lw         $s1, 0x14($sp) # maspsx-keep\n"
         "    lw         $s0, 0x10($sp) # maspsx-keep\n"
         "    addiu      $sp, $sp, 0x30 # maspsx-keep\n"
         "    jr         $ra # maspsx-keep\n"
         "    nop # maspsx-keep\n")

ASM_FUNC(setIntrDMA,
         "    addu       $a2, $a0, $zero # maspsx-keep\n"
         "    lui        $v1, %hi(D_8009CE90) # maspsx-keep\n"
         "    addiu      $v1, $v1, %lo(D_8009CE90) # maspsx-keep\n"
         "    sll        $v0, $a2, 2 # maspsx-keep\n"
         "    addu       $v1, $v0, $v1 # maspsx-keep\n"
         "    lw         $a3, 0x0($v1) # maspsx-keep\n"
         "    addu       $a0, $a1, $zero # maspsx-keep\n"
         "    beq        $a0, $a3, .L80077E5C # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    beqz       $a0, .L80077E24 # maspsx-keep\n"
         "    lui       $v0, (0xFFFFFF >> 16) # maspsx-keep\n"
         "    lui        $a1, %hi(D_8009CE8C) # maspsx-keep\n"
         "    lw         $a1, %lo(D_8009CE8C)($a1) # maspsx-keep\n"
         "    ori        $v0, $v0, (0xFFFFFF & 0xFFFF) # maspsx-keep\n"
         "    sw         $a0, 0x0($v1) # maspsx-keep\n"
         "    lw         $a0, 0x0($a1) # maspsx-keep\n"
         "    addiu      $v1, $a2, 0x10 # maspsx-keep\n"
         "    and        $a0, $a0, $v0 # maspsx-keep\n"
         "    ori        $v0, $zero, 0x1 # maspsx-keep\n"
         "    sllv       $v0, $v0, $v1 # maspsx-keep\n"
         "    lui        $v1, (0x800000 >> 16) # maspsx-keep\n"
         "    or         $v0, $v0, $v1 # maspsx-keep\n"
         "    or         $a0, $a0, $v0 # maspsx-keep\n"
         "    sw         $a0, 0x0($a1) # maspsx-keep\n"
         "    j          .L80077E5C # maspsx-keep\n"
         "    nop # maspsx-keep\n"
         "    .L80077E24: # maspsx-keep\n"
         "    lui        $a1, %hi(D_8009CE8C) # maspsx-keep\n"
         "    lw         $a1, %lo(D_8009CE8C)($a1) # maspsx-keep\n"
         "    ori        $v0, $v0, (0xFFFFFF & 0xFFFF) # maspsx-keep\n"
         "    sw         $zero, 0x0($v1) # maspsx-keep\n"
         "    lw         $v1, 0x0($a1) # maspsx-keep\n"
         "    addiu      $a0, $a2, 0x10 # maspsx-keep\n"
         "    and        $v1, $v1, $v0 # maspsx-keep\n"
         "    lui        $v0, (0x800000 >> 16) # maspsx-keep\n"
         "    or         $v1, $v1, $v0 # maspsx-keep\n"
         "    ori        $v0, $zero, 0x1 # maspsx-keep\n"
         "    sllv       $v0, $v0, $a0 # maspsx-keep\n"
         "    nor        $v0, $zero, $v0 # maspsx-keep\n"
         "    and        $v1, $v1, $v0 # maspsx-keep\n"
         "    sw         $v1, 0x0($a1) # maspsx-keep\n"
         "    .L80077E5C: # maspsx-keep\n"
         "    jr         $ra # maspsx-keep\n"
         "    addu      $v0, $a3, $zero # maspsx-keep\n")

void memclr_80077E64(void *ptr, size_t size) {
    int *end;
    end = (int *)ptr;
    while (size--) {
        *end++ = 0;
    }
}

extern long D_8009CEB0[];
extern long D_8009CEB4[];
long SetVideoMode(long mode) {
    long previous;
    previous = D_8009CEB4[0];
    D_8009CEB0[1] = mode;
    return previous;
}

extern long D_8009CEB4[];
long GetVideoMode(void) {
    return D_8009CEB4[0];
}

u_short LoadTPage(u_long *pix, int tp, int abr, int x, int y, int w, int h) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.h = h;
    switch (tp) {
    case 0:
        rect.w = w / 4;
        break;
    case 1:
        rect.w = w / 2;
        break;
    case 2:
        rect.w = w;
        break;
    }
    LoadImage(&rect, pix);

    return GetTPage(tp, abr, x, y);
}

u_short LoadClut(u_long *clut, int x, int y) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = 0x100;
    rect.h = 1;
    LoadImage(&rect, clut);

    return GetClut(x, y);
}

u_short LoadClut2(u_long *clut, int x, int y) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = 0x10;
    rect.h = 1;
    LoadImage(&rect, clut);

    return GetClut(x, y);
}

/* SPDX-License-Identifier: MIT */

extern long GetVideoMode(void);
extern int GetGraphType(void);

DRAWENV *SetDefDrawEnv(DRAWENV *env, s32 x, s32 y, s32 w, s32 h) {
    DRAWENV *sEnv;
    s32 sX;
    s32 sY;
    register s32 sW asm("s0");
    int videoMode;

    sEnv = env;
    sX = x;
    sY = y;
    sW = w;

    videoMode = GetVideoMode();
    sEnv->clip.x = sX;
    sEnv->clip.y = sY;
    sEnv->clip.w = sW;
    sEnv->clip.h = h;
    sEnv->tw.x = 0;
    sEnv->tw.y = 0;
    sEnv->tw.w = 0;
    sEnv->tw.h = 0;
    sEnv->r0 = 0;
    sEnv->g0 = 0;
    sEnv->b0 = 0;
    sEnv->dtd = 1;
    if (videoMode != 0) {
        sEnv->dfe = h < 0x121;
    } else {
        sEnv->dfe = h < 0x101;
    }
    sEnv->ofs[0] = sX;
    sEnv->ofs[1] = sY;
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    sEnv->tpage = 10;
    sEnv->isbg = 0;
    return sEnv;
}

DISPENV *SetDefDispEnv(DISPENV *env, s32 x, s32 y, s32 w, s32 h) {
    env->disp.x = x;
    env->disp.y = y;
    env->disp.w = w;
    env->disp.h = h;
    env->screen.x = 0;
    env->screen.y = 0;
    env->screen.w = 0;
    env->screen.h = 0;
    env->isrgb24 = 0;
    env->isinter = 0;
    env->pad1 = 0;
    env->pad0 = 0;
    return env;
}

extern u32 D_8009D038[];
extern u32 D_8009D03C[];
extern u32 D_8009DA8C[];

void SetDumpFnt(int id) {
    if (id >= 0 && (s32)D_8009D038[0] >= id) {
        D_8009D03C[0] = id;
        D_8009DA8C[0] = (u32)FntPrint;
    }
}

extern u16 D_800AD0DC[];
extern u16 D_800AD0E0[];
extern u32 D_8009D038[];
extern u8 D_8009D040[];

typedef struct {
    u8 unk00[0x1C];
    s32 unk1C;
    u8 unk20[4];
    u8 *unk24;
    s32 unk28;
    u8 unk2C[4];
} FntFont;

extern FntFont D_8009CEB8[];
extern void memset_8008B820();

void FntLoad(int tx, int ty) {
    D_800AD0E0[0] = LoadClut2(D_8009D040, tx, ty + 0x80);
    D_800AD0DC[0] = LoadTPage(D_8009D040 + 0x200, 0, 0, tx, ty, 0x80, 0x20);
    D_8009D038[0] = 0;
    memset_8008B820(D_8009CEB8, 0, 0x180);
}

typedef struct FntStream {
    TILE tile;         /* 0x00 */
    DR_MODE draw_mode; /* 0x10 */
    s32 capacity;      /* 0x1C */
    SPRT_8 *sprites;   /* 0x20 */
    char *buffer;      /* 0x24 */
    s32 written;       /* 0x28 */
    s32 autoWidth;     /* 0x2C: the box grows to fit the text */
} FntStream;

extern FntStream Font[];
extern s32 fntCountX;
extern s32 fntBase;
extern char fntText[];
extern SPRT_8 fntSprt[];
extern u16 fntTpage;
extern u16 fntClut;

#ifdef NON_MATCHING
/* 2026-10-17: right shape, 0x2D4 bytes against 0x2B8. Retail keeps one more
 * argument live across the SetDrawMode call and reloads the count (a word the
 * compiler must treat as aliased by the byte stores) before each tile store. */
/* Opens a text stream n characters long at (x, y). isbg is 0 for no
 * background, 1 for an opaque one and 2 for a semi-transparent one. */
s32 FntOpen(s32 x, s32 y, s32 w, s32 h, s32 isbg, s32 n) {
    RECT tw;
    s32 i;
    SPRT_8 *sprites;

    if (fntCountX >= 8) {
        return -1;
    }
    if (fntCountX == 0) {
        fntBase = 0;
    }
    Font[fntCountX].autoWidth = w == 0;
    if (n + fntBase > 0x400) {
        n = 0x400 - fntBase;
    }
    tw.w = 0x100;
    tw.h = 0x100;
    tw.x = 0;
    tw.y = 0;
    SetDrawMode(&Font[fntCountX].draw_mode, 0, 0, fntTpage, &tw);
    if (isbg != 0) {
        SetTile(&Font[fntCountX].tile);
        Font[fntCountX].tile.r0 = 0;
        Font[fntCountX].tile.g0 = 0;
        Font[fntCountX].tile.b0 = 0;
        SetSemiTrans(&Font[fntCountX].tile, isbg == 2);
    }
    Font[fntCountX].tile.x0 = x;
    Font[fntCountX].tile.y0 = y;
    Font[fntCountX].tile.w = w;
    Font[fntCountX].tile.h = h;
    Font[fntCountX].capacity = n;
    Font[fntCountX].written = 0;
    Font[fntCountX].buffer = &fntText[fntBase];
    Font[fntCountX].sprites = &fntSprt[fntBase];
    *Font[fntCountX].buffer = 0;
    sprites = Font[fntCountX].sprites;
    for (i = 0; i < n; i++) {
        SetSprt8(sprites);
        sprites->clut = fntClut;
        sprites++;
    }
    fntBase += n;
    return fntCountX++;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", FntOpen);
#endif

INCLUDE_ASM("asm/nonmatchings/psxsdk", FntFlush);

extern u8 *D_8009DA44[];
extern int strlen(const char *);

int FntPrint(const char *fmt, ...) {
    u8 *buf;
    s32 width;
    FntFont *font;
    u8 *str;
    u32 value;
    u32 t;
    s32 ch;
    s32 count;
    u8 zeroPad;
    s32 pctvar;
    u32 magic;
    u32 quot;
    u8 zeroChar;
    u8 spaceChar;
    volatile u8 pad[0x200];
    va_list ap;

    va_start(ap, fmt);
    if ((s32)fmt < 0 || (s32)fmt >= (s32)D_8009D038[0]) {
        str = (u8 *)fmt;
        fmt = (const char *)D_8009D03C[0];
        if (D_8009CEB8[(s32)fmt].unk24 == 0) {
            return -1;
        }
    } else {
        str = va_arg(ap, u8 *);
    }
    font = &D_8009CEB8[(s32)fmt];
    if (font->unk28 > font->unk1C) {
        return -1;
    }
    ch = *str;
    if (ch != 0) {
        pctvar = '%';
        magic = 0xCCCCCCCD;
        do {
            if (ch != pctvar) {
                goto store;
            }
            str++;
            ch = *str;
            width = 0;
            if (ch != pctvar) {
                goto format;
            }
        store:
            font->unk24[font->unk28++] = ch;
            if (font->unk28 > font->unk1C) {
                return -1;
            }
            goto tail;
        format:
            zeroPad = (ch == '0');
            while (ch >= '0' && ch <= '9') {
                t = width * 10 - '0';
                width = t + ch;
                str++;
                ch = *str;
            }
            buf = (u8 *)&ap;
            if (width <= 0) {
                width = 1;
            }
            switch (ch) {
            case 'd':
                value = va_arg(ap, u32);
                ch = 0;
                if ((s32)value < 0) {
                    value = -(s32)value;
                    ch = '-';
                }
                count = 0;
                do {
                    buf--;
                    count++;
                    quot = value / 10;
                    *buf = value - quot * 10 + '0';
                    value = quot;
                } while (count == 0 || value != 0);
                if (ch != 0) {
                    buf--;
                    *buf = ch;
                    count++;
                }
                break;
            case 'X':
            case 'x':
                count = 0;
                value = va_arg(ap, u32);
                do {
                    buf--;
                    *buf = D_8009DA44[0][value & 0xF];
                    value >>= 4;
                    count++;
                } while (count == 0 || value != 0);
                if (zeroPad) {
                    if (count < width) {
                        zeroChar = '0';
                        do {
                            buf--;
                            *buf = zeroChar;
                            count++;
                        } while (count < width);
                    }
                }
                break;
            case 'c':
                buf--;
                *buf = va_arg(ap, u8);
                count = 1;
                break;
            case 's':
                buf = va_arg(ap, u8 *);
                count = strlen((char *)buf);
                break;
            }
            if (count < width) {
                spaceChar = ' ';
                do {
                    font->unk24[font->unk28++] = spaceChar;
                    if (font->unk28 > font->unk1C) {
                        return -1;
                    }
                    width--;
                } while (count < width);
            }
            while (--count != -1) {
                font->unk24[font->unk28++] = *buf++;
                if (font->unk28 > font->unk1C) {
                    return -1;
                }
            }
        tail:
            str++;
            ch = *str;
        } while (ch != 0);
    }
    font->unk24[font->unk28] = 0;
    return font->unk28;
}

INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090548);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090560);

u_short GetTPage(int tp, int abr, int x, int y) {
    int t, last;
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        t = ((tp & 0x3) << 9) | ((abr & 0x3) << 7) | ((y & 0x300) >> 3);
        last = (x & 0x3ff) >> 6;
    } else {
        t = ((tp & 0x3) << 7) | ((abr & 0x3) << 5) | ((y & 0x100) >> 4) |
            ((x & 0x3ff) >> 6);
        last = (y & 0x200) << 2;
    }
    return t | last;
}

u16 GetClut(s32 x, s32 y) {
    return getClut(x, y);
}

typedef int (*DebugPrintf)(const char *, ...);
extern u32 D_8009DA8C[];
extern char D_80090548[];

extern u32 D_8009DA8C[];
extern char D_80090548[];

void DumpTPage(u_short tpage) {
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        ((DebugPrintf)D_8009DA8C[0])(D_80090548, (tpage >> 9) & 3,
                                     (tpage >> 7) & 3, (tpage << 6) & 0x7C0,
                                     (tpage * 8) & 0x300);
        return;
    }
    ((DebugPrintf)D_8009DA8C[0])(
        D_80090548, (tpage >> 7) & 3, (tpage >> 5) & 3, (tpage << 6) & 0x7C0,
        ((tpage * 0x10) & 0x100) + ((tpage >> 2) & 0x200));
}

extern char D_80090560[];

void DumpClut(u_short clut) {
    ((DebugPrintf)D_8009DA8C[0])(D_80090560, (clut & 0x3F) * 0x10, clut >> 6);
}

void *NextPrim(void *p) {
    return nextPrim(p);
}

int IsEndPrim(void *p) {
    return isendprim(p);
}

void AddPrim(void *ot, void *p) {
    addPrim(ot, p);
}

void AddPrims(void *ot, void *p0, void *p1) {
    addPrims(ot, p0, p1);
}

void CatPrim(void *p0, void *p1) {
    catPrim(p0, p1);
}

void TermPrim(void *p) {
    return termPrim(p);
}

void SetSemiTrans(void *p, int abe) {
    return setSemiTrans(p, abe);
}

void SetShadeTex(void *p, int tge) {
    return setShadeTex(p, tge);
}

void SetPolyF3(POLY_F3 *p) {
    setPolyF3(p);
}

void SetPolyFT3(POLY_FT3 *p) {
    setPolyFT3(p);
}

void SetPolyG3(POLY_G3 *p) {
    setPolyG3(p);
}

void SetPolyGT3(POLY_GT3 *p) {
    setPolyGT3(p);
}

void SetPolyF4(POLY_F4 *p) {
    setPolyF4(p);
}

void SetPolyFT4(POLY_FT4 *p) {
    setPolyFT4(p);
}

void SetPolyG4(POLY_G4 *p) {
    setPolyG4(p);
}

void SetPolyGT4(POLY_GT4 *p) {
    setPolyGT4(p);
}

void SetSprt8(SPRT_8 *p) {
    setSprt8(p);
}

void SetSprt16(SPRT_16 *p) {
    setSprt16(p);
}

void SetSprt(SPRT *p) {
    setSprt(p);
}

void SetTile1(TILE_1 *p) {
    setTile1(p);
}

void SetTile8(TILE_8 *p) {
    setTile8(p);
}

void SetTile16(TILE_16 *p) {
    setTile16(p);
}

void SetTile(TILE *p) {
    setTile(p);
}

void SetLineF2(LINE_F2 *p) {
    setLineF2(p);
}

void SetLineG2(LINE_G2 *p) {
    setLineG2(p);
}

void SetLineF3(LINE_F3 *p) {
    setLineF3(p);
}

void SetLineG3(LINE_G3 *p) {
    setLineG3(p);
}

void SetLineF4(LINE_F4 *p) {
    setLineF4(p);
}

void SetLineG4(LINE_G4 *p) {
    setLineG4(p);
}

void SetBlockFill(BLK_FILL *p) {
    setBlockFill(p);
}

/* SPDX-License-Identifier: MIT */

void SetDrawMove(void *arg0) {
    *((u8 *)arg0 + 3) = 5;
    *((u8 *)arg0 + 7) = 1;
    *((u32 *)arg0 + 2) = 0x80000000;
}

void SetDrawTPage(void *drtpage, s32 dfe, s32 dtd, s32 tpage) {
    u32 code;

    *((u8 *)drtpage + 3) = 1;
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        u32 mode;
        u32 page;

        mode = 0xE1000000;
        if (dtd != 0) {
            mode |= 0x800;
        }
        code = tpage & 0x27FF;
        page = code;
        if (dfe != 0) {
            do {
                page |= 0x1000;
            } while (0);
            code = mode | page;
        } else {
            code = mode | page;
        }
    } else {
        u32 mode;
        u32 page;

        mode = 0xE1000000;
        if (dtd != 0) {
            mode |= 0x200;
        }
        page = tpage & 0x9FF;
        if (dfe != 0) {
            page |= 0x400;
        }
        code = mode | page;
    }
    *((u32 *)drtpage + 1) = code;
}

void SetDrawLoad(void *dr, RECT *r) {
    s32 half;

    s32 code;

    half = (s32)((s16 *)r)[2] * (s32)((s16 *)r)[3];
    half = (half + 1) / 2;
    code = half + 4;
    if ((u32)(half - 1) >= 0xB) {
        code = 0;
    }
    *((u32 *)dr + 1) = 0x1000000;
    *((u8 *)dr + 3) = code;
    *((u32 *)dr + 2) = 0xA0000000;
    *((u32 *)dr + 3) = ((u32 *)r)[0];
    *((u32 *)dr + 4) = ((u32 *)r)[1];
}

/* SPDX-License-Identifier: MIT */

s32 MargePrim(void *p0, void *p1) {
    s32 len;

    len = *((u8 *)p0 + 3) + *((u8 *)p1 + 3) + 1;
    if (len >= 0x21) {
        return -1;
    }
    *((u8 *)p0 + 3) = len;
    *((u32 *)p1) = 0;
    return 0;
}

extern char D_80090548[];
extern char D_80090570[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090570);
extern char D_80090588[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090588);
extern char D_80090598[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090598);
extern char D_800905B0[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800905B0);
extern char D_800905BC[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800905BC);

void DumpDrawEnv(DRAWENV *env) {
    GPU_printf(D_80090570, env->clip.x, env->clip.y, env->clip.w, env->clip.h);
    GPU_printf(D_80090588, env->ofs[0], env->ofs[1]);
    GPU_printf(D_80090598, env->tw.x, env->tw.y, env->tw.w, env->tw.h);
    GPU_printf(D_800905B0, env->dtd);
    GPU_printf(D_800905BC, env->dfe);
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        GPU_printf(D_80090548, (env->tpage >> 9) & 3, (env->tpage >> 7) & 3,
                   (env->tpage << 6) & 0x7C0, (env->tpage * 8) & 0x300);
    } else {
        GPU_printf(D_80090548, (env->tpage >> 7) & 3, (env->tpage >> 5) & 3,
                   (env->tpage << 6) & 0x7C0,
                   ((env->tpage * 0x10) & 0x100) + ((env->tpage >> 2) & 0x200));
    }
}

extern u32 gDispPrintfRead1[];
extern u32 gDispPrintfRead2[];
extern u32 gDispPrintfRead3[];
extern u32 gDispPrintfRead4[];
extern char D_800905C8[];
extern char D_800905E4[];
extern char D_80090600[];
extern char D_8009060C[];

INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800905C8);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800905E4);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090600);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_8009060C);

void DumpDispEnv(DISPENV *env) {
    ((DebugPrintf)gDispPrintfRead1[0])(D_800905C8, env->disp.x, env->disp.y,
                                       env->disp.w, env->disp.h);
    ((DebugPrintf)gDispPrintfRead2[0])(D_800905E4, env->screen.x, env->screen.y,
                                       env->screen.w, env->screen.h);
    ((DebugPrintf)gDispPrintfRead3[0])(D_80090600, env->isinter);
    ((DebugPrintf)gDispPrintfRead4[0])(D_8009060C, env->isrgb24);
}

extern char D_8009064C[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_8009064C);
extern char D_8009066C[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_8009066C);
extern char D_8009DA48[];
extern u16 D_8009DB10[][2];
extern u16 D_8009DB24[][2];
extern s32 _reset(s32);
extern void GPU_cw(u32);

s32 ResetGraph(s32 level) {
    s32 mode = level & 7;

    if (mode == 0 || mode == 3) {
        printf(D_8009064C, D_8009DA48, &gGfx);
        memset(&gGfx, 0, sizeof(GfxState));
        ResetCallback();
        GPU_cw((u32)gGpu & 0xFFFFFF);
        gGfx.type = _reset(mode != 0);
        gGfx.queue = 1;
        gGfx.maxW = D_8009DB10[gGfx.type][0];
        gGfx.maxH = D_8009DB24[gGfx.type][0];
        memset(&gGfx.drawEnv, -1, sizeof(DRAWENV));
        memset(&gGfx.dispEnv, -1, sizeof(DISPENV));
        return gGfx.type;
    }
    if (gGfx.level >= 2) {
        GPU_printf(D_8009066C, level);
    }
    return gGpu->reset(1);
}

extern char D_80090680[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090680);

s32 SetGraphReverse(s32 mode) {
    s32 old = gGfx.reverse;

    if (gGfx.level >= 2) {
        GPU_printf(D_80090680, mode);
    }

    gGfx.reverse = mode;
    gGpu->ctl(gGpu->getctl(8) | (gGfx.reverse ? 0x08000080 : 0x08000000));
    if (gGfx.type == 2) {
        gGpu->ctl(gGfx.reverse ? 0x20000501 : 0x20000504);
    }
    return old;
}

extern u8 D_8009DA90[];
extern u8 D_8009DA92[];
extern u8 D_8009DA93[];
extern u32 D_8009DA8C[];
extern char D_80090698[];

int SetGraphDebug(int level) {
    volatile u8 *debug = D_8009DA92;
    u8 old = debug[0];

    debug[0] = level;
    if ((u8)level) {
        ((DebugPrintf)D_8009DA8C[0])(D_80090698, D_8009DA92[0], D_8009DA90[0],
                                     D_8009DA93[0]);
    }
    return old;
}

INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090698);

extern u32 D_8009DA88[];
extern u32 D_8009DA8C[];
extern u8 D_8009DA91[];
extern u8 D_8009DA92[];
extern char D_800906C4[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800906C4);
int SetGraphQueue(int mode) {
    u8 previousMode;
    previousMode = D_8009DA91[0];
    if (D_8009DA92[0] >= 2) {
        ((int (*)(const char *, ...))D_8009DA8C[0])(D_800906C4, mode);
    }
    if (mode != D_8009DA91[0]) {
        ((void (*)(int))((u32 *)D_8009DA88[0])[13])(1);
        D_8009DA91[0] = mode;
        DMACallback(2, 0);
    }
    return previousMode;
}

INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800906D8);

extern u8 D_8009DA90[];

int GetGraphType(void) {
    return D_8009DA90[0];
}

extern u8 D_8009DA92[];

int GetGraphDebug(void) {
    return D_8009DA92[0];
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009DA92[];
extern u32 D_8009DA9C[];
extern u32 D_8009DA8C[];
extern u8 D_8009DAA0[];
extern char D_800906D8[];

u_long DrawSyncCallback(void (*func)()) {
    Callback old;

    if (D_8009DA92[0] >= 2) {
        ((int (*)(const char *, ...))D_8009DA8C[0])(D_800906D8, func);
    }
    old = D_8009DA9C[0];
    ((u32 *)D_8009DAA0)[-1] = func;
    return old;
}

extern u32 D_8009DA88[];
extern u32 D_8009DA8C[];
extern u8 D_8009DA92[];
extern char D_800906F4[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800906F4);
void SetDispMask(s32 mode) {
    s32 command;
    u32 *gpu;
    if ((u8)D_8009DA92[0] >= 2U) {
        ((int (*)(const char *, ...))D_8009DA8C[0])(D_800906F4, mode);
    }
    if (mode == 0)
        memset(&D_8009DA92[0x6A], -1, 0x14);
    command = 0x03000001;
    gpu = (u32 *)D_8009DA88[0];
    if (mode != 0)
        command = 0x03000000;
    ((void (*)(int))gpu[4])(command);
}

extern char D_80090708[];
extern u32 D_8009DA88[];
extern u32 D_8009DA8C[];
extern u8 D_8009DA92[];

int DrawSync(int mode) {
    if (D_8009DA92[0] >= 2) {
        ((void (*)())D_8009DA8C[0])(D_80090708, mode);
    }
    return ((int (*)())((u32 *)D_8009DA88[0])[15])(mode);
}

/* "DrawSync(%d)..." string, in chunk form until it is split out by splat. */
void __maspsx_include_asm_hack_D_80090708(void) {
    __asm__(".section .rodata # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "nonmatching D_80090708 # maspsx-keep\n"
            "dlabel D_80090708 # maspsx-keep\n"
            "    .asciz \"DrawSync(%d)...\\n\" # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "enddlabel D_80090708 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern u8 D_8009DA92[];
extern s16 D_8009DA94[];
extern s16 D_8009DA96[];

extern char D_8009071C[];
extern char D_8009073C[];
extern char D_80090728[];

extern u8 D_8009DA92[];
extern s16 D_8009DA94[];
extern s16 D_8009DA96[];

extern char D_8009071C[];
extern char D_8009073C[];
extern char D_80090728[];

void checkRECT(RECT *r, RECT *rect) {
    switch (D_8009DA92[0]) {
    case 1:
        if (rect->w > D_8009DA94[0] || rect->w + rect->x > D_8009DA94[0] ||
            rect->y > D_8009DA96[0] || rect->y + rect->h > D_8009DA96[0] ||
            rect->w <= 0 || rect->x < 0 || rect->y < 0 || rect->h <= 0) {
            ((int (*)())D_8009DA8C[0])(D_8009071C, r);
            ((int (*)())((u32 *)D_8009DA90)[-1])(D_80090728, rect->x, rect->y,
                                                 rect->w, rect->h);
            return;
        }
        return;
    case 2:
        ((int (*)())D_8009DA8C[0])(D_8009073C, r);
        ((int (*)())((u32 *)D_8009DA90)[-1])(D_80090728, rect->x, rect->y,
                                             rect->w, rect->h);
        return;
    default:
        return;
    }
}

INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_8009071C);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090728);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_8009073C);

extern char D_80090740[];
extern u32 D_8009DA88[];

int ClearImage(RECT *rect, u_char r, u_char g, u_char b) {
    checkRECT((RECT *)D_80090740, rect);
    return ((int (*)())((u32 *)D_8009DA88[0])[2])(
        ((u32 *)D_8009DA88[0])[3], rect, 8, (b << 16) | (g << 8) | r);
}

/* "ClearImage" string, in chunk form until it is split out by splat. */
void __maspsx_include_asm_hack_D_80090740(void) {
    __asm__(".section .rodata # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "nonmatching D_80090740 # maspsx-keep\n"
            "dlabel D_80090740 # maspsx-keep\n"
            "    .asciz \"ClearImage\" # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "enddlabel D_80090740 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern char D_8009074C[];
extern u32 D_8009DA88[];

int LoadImage(RECT *rect, u_long *p) {
    checkRECT((RECT *)D_8009074C, rect);
    return ((int (*)())((u32 *)D_8009DA88[0])[2])(((u32 *)D_8009DA88[0])[8],
                                                  rect, 8, p);
}

/* "LoadImage" string, in chunk form until it is split out by splat. */
void __maspsx_include_asm_hack_D_8009074C(void) {
    __asm__(".section .rodata # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "nonmatching D_8009074C # maspsx-keep\n"
            "dlabel D_8009074C # maspsx-keep\n"
            "    .asciz \"LoadImage\" # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "enddlabel D_8009074C # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern char D_80090758[];

int StoreImage(RECT *rect, u_long *p) {
    checkRECT((RECT *)D_80090758, rect);
    return ((int (*)())((u32 *)D_8009DA88[0])[2])(((u32 *)D_8009DA88[0])[7],
                                                  rect, 8, p);
}

/* "StoreImage" string, in chunk form until it is split out by splat. */
void __maspsx_include_asm_hack_D_80090758(void) {
    __asm__(".section .rodata # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "nonmatching D_80090758 # maspsx-keep\n"
            "dlabel D_80090758 # maspsx-keep\n"
            "    .asciz \"StoreImage\" # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "enddlabel D_80090758 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern char D_80090764[];
extern u32 D_8009DB40[];
extern u32 D_8009DB44[];
extern u32 D_8009DB48[];

int MoveImage(RECT *rect, int x, int y) {
    u32 *gpu;
    u32 *cmd;

    gpu = D_8009DA88;
    checkRECT((RECT *)D_80090764, rect);
    if (rect->w == 0 || rect->h == 0) {
        return -1;
    }
    cmd = (u32 *)gpu[0];
    D_8009DB40[0] = *(u32 *)rect;
    D_8009DB44[0] = (y << 16) | (x & 0xFFFF);
    D_8009DB48[0] = *(u32 *)&rect->w;
    return ((int (*)())cmd[2])(cmd[6], D_8009DB40 - 2, 20, 0);
}

/* "MoveImage" string, in chunk form until it is split out by splat. */
void __maspsx_include_asm_hack_D_80090764(void) {
    __asm__(".section .rodata # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "nonmatching D_80090764 # maspsx-keep\n"
            "dlabel D_80090764 # maspsx-keep\n"
            "    .asciz \"MoveImage\" # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "enddlabel D_80090764 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090770);
extern u32 D_8009DA8C[];
extern u8 D_8009DA92[];
extern u8 D_8009DB4C[];
extern char D_80090770[];
OT_TYPE *ClearOTag(OT_TYPE *arg0, int arg1) {
    OT_TYPE *temp_a0;
    u32 masked;
    if ((u8)D_8009DA92[0] >= 2U) {
        temp_a0 = (OT_TYPE *)D_80090770;
        ((int (*)(const char *, ...))D_8009DA8C[0])(temp_a0, arg0, arg1);
    }
    arg1 -= 1;
    if (arg1 != 0) {
        do {
            arg1 -= 1;
            temp_a0 = (OT_TYPE *)arg0 + 1;
            ((u8 *)arg0)[3] = 0;
            masked = (u32)temp_a0 & 0xFFFFFF;
            arg0[0] = (arg0[0] & 0xFF000000) | masked;
            arg0 = temp_a0;
        } while (arg1 != 0);
    }
    *arg0 = (s32)((u32)D_8009DB4C & 0xFFFFFF);
    return arg0;
}

extern u32 D_8009DA88[];
extern u32 D_8009DA8C[];
extern u8 D_8009DA92[];
extern u8 D_8009DB4C[];
extern char D_80090788[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090788);
OT_TYPE *ClearOTagR(OT_TYPE *ot, int n) {
    if (D_8009DA92[0] >= 2) {
        ((int (*)(const char *, ...))D_8009DA8C[0])(D_80090788, ot, n);
    }
    ((void (*)(OT_TYPE *, int))((u32 *)D_8009DA88[0])[11])(ot, n);
    ot[0] = (OT_TYPE)((u32)D_8009DB4C & 0xFFFFFF);
    return ot;
}

int DrawPrim(void *prim) {
    u8 code;

    code = *((u8 *)prim + 3);
    ((int (*)())((u32 *)D_8009DA88[0])[15])(0);
    return ((int (*)())((u32 *)D_8009DA88[0])[5])((u32 *)prim + 1, code);
}

extern char D_800907A0[];

void DrawOTag(OT_TYPE *ot) {
    extern u32 D_8009DA88[];
    extern u32 D_8009DA8C[];
    extern u8 D_8009DA92[];

    if (D_8009DA92[0] >= 2) {
        ((void (*)())D_8009DA8C[0])(D_800907A0, ot);
    }
    ((void (*)())((u32 *)D_8009DA88[0])[2])(((u32 *)D_8009DA88[0])[6], ot, 0,
                                            0);
}

/* "DrawOTag(%08x)..." string, in chunk form until it is split out by splat. */
void __maspsx_include_asm_hack_D_800907A0(void) {
    __asm__(".section .rodata # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "nonmatching D_800907A0 # maspsx-keep\n"
            "dlabel D_800907A0 # maspsx-keep\n"
            "    .asciz \"DrawOTag(%08x)...\\n\" # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "enddlabel D_800907A0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern void *memcpy();
extern char D_800907B4[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800907B4);

DRAWENV *PutDrawEnv(DRAWENV *env) {
    s32 size;

    if (gGfx.level >= 2) {
        GPU_printf(D_800907B4, env);
    }

    SetDrawEnv(&env->dr_env, env);
    env->dr_env.tag |= 0xFFFFFF;
    gGpu->addque2(gGpu->cwc, &env->dr_env, sizeof(DR_ENV), 0);
    size = sizeof(DRAWENV);
    memcpy(&gGfx.drawEnv, env, size);

    return env;
}

extern char D_800907CC[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800907CC);

void DrawOTagEnv(OT_TYPE *ot, DRAWENV *env) {
    s32 size;

    if (gGfx.level >= 2) {
        GPU_printf(D_800907CC, ot, env);
    }

    SetDrawEnv(&env->dr_env, env);
    env->dr_env.tag = (env->dr_env.tag & 0xFF000000) | ((u32)ot & 0xFFFFFF);
    gGpu->addque2(gGpu->cwc, &env->dr_env, sizeof(DR_ENV), 0);
    size = sizeof(DRAWENV);
    memcpy(&gGfx.drawEnv, env, size);
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009DAA0[];
extern void *memcpy();

DRAWENV *GetDrawEnv(DRAWENV *env) {
    s32 size = 0x5C;

    memcpy(env, D_8009DAA0, size);
    return env;
}

extern char D_800907E8[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_800907E8);
extern s32 get_dx();

#ifdef NON_MATCHING
/* 2026-10-17: one compare short of retail. 0x4B4 bytes against 0x4B0; the final
 * height test (pad0 in v0, height in v1, one result register) and the saved
 * copy as volatile halfwords are the open rows. */
DISPENV *PutDispEnv(DISPENV *env) {
    s32 h_start;
    s32 v_start;
    s32 cmd;
    s32 v_end;
    s32 h_end;
    s32 size;
    s32 small;

    cmd = 0x08000000;
    if (*(volatile u8 *)&gGfx.level >= 2) {
        GPU_printf(D_800907E8, env);
    }
    gGpu->ctl(0x05000000 |
              (gGfx.type == 1 || gGfx.type == 2
                   ? ((env->disp.y & 0xFFF) << 0xC) | (get_dx(env) & 0xFFF)
                   : ((env->disp.y & 0x3FF) << 0xA) | (env->disp.x & 0x3FF)));
    if ((s16)gGfx.dispEnv.scrX != env->screen.x ||
        (s16)gGfx.dispEnv.scrY != env->screen.y ||
        (s16)gGfx.dispEnv.scrW != env->screen.w ||
        (s16)gGfx.dispEnv.scrH != env->screen.h) {
        env->pad0 = GetVideoMode();
        h_start = env->screen.x * 0xA + 0x260;
        v_start = env->screen.y + (env->pad0 ? 0x13 : 0x10);
        h_end = h_start + (env->screen.w ? env->screen.w * 0xA : 0xA00);
        v_end = v_start + (env->screen.h ? env->screen.h : 0xF0);
        h_start = GPU_CLAMP(h_start, 0x1F4, 0xCDA);
        h_end = GPU_CLAMP(h_end, h_start + 0x50, 0xCDA);
        v_start = GPU_CLAMP(v_start, 0x10, (env->pad0 ? 0x136 : 0x100));
        v_end = GPU_CLAMP(v_end, v_start + 2, (env->pad0 ? 0x138 : 0x102));
        gGpu->ctl(0x06000000 | ((h_end & 0xFFF) << 0xC) | (h_start & 0xFFF));
        gGpu->ctl(0x07000000 | ((v_end & 0x3FF) << 0xA) | (v_start & 0x3FF));
    }
    if (gGfx.dispEnv.flags != LOW(env->isinter) ||
        (s16)gGfx.dispEnv.dispX != env->disp.x ||
        (s16)gGfx.dispEnv.dispY != env->disp.y ||
        (s16)gGfx.dispEnv.dispW != env->disp.w ||
        (s16)gGfx.dispEnv.dispH != env->disp.h) {
        env->pad0 = GetVideoMode();
        if (env->pad0 == 1) {
            cmd |= 0x8;
        }
        if (env->isrgb24) {
            cmd |= 0x10;
        }
        if (env->isinter) {
            cmd |= 0x20;
        }
        if (*(volatile u8 *)&gGfx.reverse != 0) {
            cmd |= 0x80;
        }
        if (env->disp.w > 0x118) {
            if (env->disp.w < 0x161) {
                cmd |= 1;
            } else if (env->disp.w < 0x191) {
                cmd |= 0x40;
            } else if (env->disp.w < 0x231) {
                cmd |= 2;
            } else {
                cmd |= 3;
            }
        }
        small = env->disp.h < 0x121;
        if (env->pad0 == 0) {
            small = env->disp.h < 0x101;
        }
        if (small == 0) {
            cmd |= 0x24;
        }
        gGpu->ctl(cmd);
    }
    size = sizeof(DISPENV);
    memcpy(&gGfx.dispEnv, env, size);
    return env;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", PutDispEnv);
#endif

/* SPDX-License-Identifier: MIT */

extern u8 D_8009DAFC[];

DISPENV *GetDispEnv(DISPENV *env) {
    s32 size = 0x14;

    memcpy(env, D_8009DAFC, size);
    return env;
}

extern u32 D_8009DA88[];
u32 GetODE(void) {
    s32 (*getOde)(void);
    getOde = (s32 (*)(void))((u32 *)D_8009DA88[0])[14];
    return (u32)getOde() >> 31;
}

/* SPDX-License-Identifier: MIT */

extern u32 get_tw();

void SetTexWindow(void *drtw, RECT *tw) {
    *((u8 *)drtw + 3) = 2;
    *((u32 *)drtw + 1) = get_tw(tw);
    *((u32 *)drtw + 2) = 0;
}

extern u32 get_cs(s16 x, s16 y);
extern u32 get_ce(s16 x, s16 y);

void SetDrawArea(void *drarea, RECT *clip) {
    *((u8 *)drarea + 3) = 2;
    *((u32 *)drarea + 1) = get_cs(clip->x, clip->y);
    *((u32 *)drarea + 2) = get_ce((u16)clip->x + (u16)clip->w - 1,
                                  (u16)clip->y + (u16)clip->h - 1);
}

extern s32 get_ofs();

void SetDrawOffset(void *drofs, s16 *ofs) {
    *((u8 *)drofs + 3) = 2;
    *((u32 *)drofs + 1) = get_ofs(ofs[0], ofs[1]);
    *((u32 *)drofs + 2) = 0;
}

/* SPDX-License-Identifier: MIT */

void SetPriority(void *arg0, s32 arg1, s32 arg2) {
    u32 mode;

    *((u8 *)arg0 + 3) = 2;
    mode = 0xE6000000;
    if (arg1 != 0) {
        mode = 0xE6000002;
    }
    *((u32 *)arg0 + 1) = mode | (arg2 != 0);
    *((u32 *)arg0 + 2) = 0;
}

extern u32 get_tw();
extern s32 get_mode();

void SetDrawMode(DR_MODE *p, s32 dfe, s32 dtd, s32 tpage, RECT *tw) {
    *((u8 *)p + 3) = 2;
    *((u32 *)p + 1) = get_mode(dfe, dtd, (u16)tpage);
    *((u32 *)p + 2) = get_tw(tw);
}

extern s32 get_mode();

#ifdef NON_MATCHING
/* 2026-10-17: donor shape with retail's in-place clamp; the max size words read as volatile u16 give retail's lhu/sll/sra but the clamp temps allocate differently (about 60 rows off). */
void SetDrawEnv(DR_ENV *dr_env_in, DRAWENV *env) {
    RECT clip_rect;
    s32 offset;
    DR_ENV *dr_env;

    dr_env = dr_env_in;

    dr_env->code[0] = get_cs(env->clip.x, env->clip.y);
    dr_env->code[1] =
        get_ce(env->clip.w + env->clip.x - 1, env->clip.y + env->clip.h - 1);
    dr_env->code[2] = get_ofs(env->ofs[0], env->ofs[1]);
    dr_env->code[3] = get_mode(env->dfe, env->dtd, env->tpage);
    dr_env->code[4] = get_tw(&env->tw);
    dr_env->code[5] = 0xE6000000;

    offset = 7;
    if (env->isbg != 0) {
        clip_rect.x = env->clip.x;
        clip_rect.y = env->clip.y;
        clip_rect.w = env->clip.w;
        clip_rect.h = env->clip.h;
        clip_rect.w = GPU_CLAMP(clip_rect.w, 0, (s16)gfxMaxW[0] - 1);
        clip_rect.h = GPU_CLAMP(clip_rect.h, 0, (s16)gfxMaxH[0] - 1);

        if ((clip_rect.x & 0x3F) || (clip_rect.w & 0x3F)) {
            clip_rect.x -= env->ofs[0];
            clip_rect.y -= env->ofs[1];
            *((s32 *)dr_env + offset++) =
                0x60000000 | env->b0 << 0x10 | env->g0 << 8 | env->r0;
            *((s32 *)dr_env + offset++) = LOW(clip_rect.x);
            *((s32 *)dr_env + offset++) = LOW(clip_rect.w);
            clip_rect.x += env->ofs[0];
            clip_rect.y += env->ofs[1];
        } else {
            *((s32 *)dr_env + offset++) =
                0x02000000 | env->b0 << 0x10 | env->g0 << 8 | env->r0;
            *((s32 *)dr_env + offset++) = LOW(clip_rect.x);
            *((s32 *)dr_env + offset++) = LOW(clip_rect.w);
        }
    }

    setlen(dr_env, offset - 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawEnv);
#endif

/* SPDX-License-Identifier: MIT */

extern u8 D_8009DA90[];

s32 get_mode(s32 dfe, s32 dtd, s32 tpage) {
    if ((u32)(*(volatile u8 *)&gGfx.type - 1) < 2U) {
        return 0xE1000000 | (dtd ? 0x800 : 0) | (dfe ? 0x1000 : 0) |
               (tpage & 0x27FF);
    } else {
        return 0xE1000000 | (dtd ? 0x200 : 0) | (dfe ? 0x400 : 0) |
               (tpage & 0x9FF);
    }
}

/* SPDX-License-Identifier: MIT */

u32 get_cs(s16 arg0, s16 arg1) {
    volatile u16 *px;
    volatile u16 *py;
    register s32 cmdBase asm("$4");
    volatile u8 *pm;
    s32 xmax;
    s32 mx;
    s32 clipX;
    s32 xv;
    s32 yv;
    s32 ymax;
    s32 my;
    s32 clipY;
    s32 word1;
    s32 word0;

    clipX = 0;
    if (arg0 >= 0) {
        px = (volatile u16 *)D_8009DA94;
        asm("" : "=r"(px) : "0"(px));
        xmax = (s16)px[0];
        mx = xmax - 1;
        xv = arg0;
        if (mx < arg0) {
            xv = mx;
        }
        clipX = xv;
    }
    arg0 = clipX;
    asm("" : "=r"(arg0) : "0"(arg0));
    yv = arg1;
    clipY = 0;
    if (yv >= 0) {
        py = (volatile u16 *)D_8009DA96;
        asm("" : "=r"(py) : "0"(py));
        ymax = (s16)py[0];
        my = ymax - 1;
        if (my < yv) {
            yv = my;
        }
        clipY = yv;
    }
    pm = D_8009DA90;
    asm("" : "=r"(pm) : "0"(pm));
    if ((u32)(pm[0] - 1) >= 2) {
        word1 = clipY & 0x3FF;
        word1 = word1 << 0xA;
        word0 = arg0 & 0x3FF;
        cmdBase = 0xE3000000;
    } else {
        word1 = clipY & 0xFFF;
        word1 = word1 << 0xC;
        word0 = arg0 & 0xFFF;
        cmdBase = 0xE3000000;
    }
    if (mx) {
        return word1 | (word0 | cmdBase);
    } else {
        return word1 | (word0 | cmdBase);
    }
}

/* SPDX-License-Identifier: MIT */

u32 get_ce(s16 arg0, s16 arg1) {
    volatile u16 *px;
    volatile u16 *py;
    register s32 cmdBase asm("$4");
    volatile u8 *pm;
    s32 xmax;
    s32 mx;
    s32 clipX;
    s32 xv;
    s32 yv;
    s32 ymax;
    s32 my;
    s32 clipY;
    s32 word1;
    s32 word0;

    clipX = 0;
    if (arg0 >= 0) {
        px = (volatile u16 *)D_8009DA94;
        asm("" : "=r"(px) : "0"(px));
        xmax = (s16)px[0];
        mx = xmax - 1;
        xv = arg0;
        if (mx < arg0) {
            xv = mx;
        }
        clipX = xv;
    }
    arg0 = clipX;
    asm("" : "=r"(arg0) : "0"(arg0));
    yv = arg1;
    clipY = 0;
    if (yv >= 0) {
        py = (volatile u16 *)D_8009DA96;
        asm("" : "=r"(py) : "0"(py));
        ymax = (s16)py[0];
        my = ymax - 1;
        if (my < yv) {
            yv = my;
        }
        clipY = yv;
    }
    pm = D_8009DA90;
    asm("" : "=r"(pm) : "0"(pm));
    if ((u32)(pm[0] - 1) >= 2) {
        word1 = clipY & 0x3FF;
        word1 = word1 << 0xA;
        word0 = arg0 & 0x3FF;
        cmdBase = 0xE4000000;
    } else {
        word1 = clipY & 0xFFF;
        word1 = word1 << 0xC;
        word0 = arg0 & 0xFFF;
        cmdBase = 0xE4000000;
    }
    if (mx) {
        return word1 | (word0 | cmdBase);
    } else {
        return word1 | (word0 | cmdBase);
    }
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009DA90[];

s32 get_ofs(s32 x, s32 y) {
    if ((u32)(*(volatile u8 *)&gGfx.type - 1) < 2U) {
        return 0xE5000000 | ((y & 0xFFF) << 12) | (x & 0xFFF);
    } else {
        return 0xE5000000 | ((y & 0x7FF) << 11) | (x & 0x7FF);
    }
}

/* SPDX-License-Identifier: MIT */

u32 get_tw(RECT *tw) {
    /* Keep these values together to preserve the SDK stack layout. */
    struct {
        u32 xOffset, yOffset, widthMask, heightMask;
    } window;

    if (tw != 0) {
        window.xOffset = (tw->x & 0xFF) >> 3;
        window.widthMask = (-tw->w & 0xFF) >> 3;
        window.yOffset = (tw->y & 0xFF) >> 3;
        window.heightMask = (-tw->h & 0xFF) >> 3;
        return (window.yOffset << 15) | 0xE2000000 | (window.xOffset << 10) |
               (window.heightMask << 5) | window.widthMask;
    }
    return 0;
}

#ifdef NON_MATCHING
/* 2026-10-17: the type read as a volatile byte gives retail's lui/addiu/lbu/
 * andi head. The case blocks then differ (retail tests case 1 and case 2 in
 * order and cross-jumps the two "0x400 - w - x" tails into one) and the
 * result is 4 bytes long. */
s32 get_dx(DISPENV *env) {
    switch (*(volatile u8 *)&gGfx.type) {
    case 1:
        if (gGfx.reverse) {
            return 0x400 - env->disp.w - env->disp.x;
        }
    default:
        return env->disp.x;
    case 2:
        if (gGfx.reverse) {
            return 0x400 - env->disp.w / 2 - env->disp.x;
        }
        return env->disp.x / 2;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", get_dx);
#endif

/* SPDX-License-Identifier: MIT */

extern s32 *D_8009DB64[];

s32 _status(void) {
    return *(s32 *)D_8009DB64[0];
}

extern void set_alarm(void);
extern s32 get_alarm(void);

s32 _otc(s32 arg0, s32 arg1) {
    *DPCR |= 0x08000000;
    *DMA6_CHCR = 0;
    *DMA6_MADR = arg0 - 4 + arg1 * 4;
    *DMA6_BCR = arg1;
    *DMA6_CHCR = 0x11000002;
    set_alarm();
    while (*DMA6_CHCR & 0x01000000) {
        if (get_alarm()) {
            return -1;
        }
    }
    return arg1;
}

extern s32 gpuClrBuf[];
extern void _cwc(s32);

#ifdef NON_MATCHING
/* 2026-10-17: donor shape with retail's in-place clamp; the max size words read as volatile u16 give retail's lhu/sll/sra but the clamp temps allocate differently (about 60 rows off). */
/* Clears a frame buffer rectangle. */
s32 _clr(RECT *arg0, s32 color) {
    arg0->w = GPU_CLAMP(arg0->w, 0, (s16)gfxMaxW[0] - 1);
    arg0->h = GPU_CLAMP(arg0->h, 0, (s16)gfxMaxH[0] - 1);

    if ((arg0->x & 0x3F) || (arg0->w & 0x3F)) {
        gpuClrBuf[0] = 0x07000000 | ((s32)&gpuClrBuf[8] & 0xFFFFFF);
        gpuClrBuf[1] = 0xE3000000;
        gpuClrBuf[2] = 0xE4FFFFFF;
        gpuClrBuf[3] = 0xE5000000;
        gpuClrBuf[4] = 0xE6000000;

        gpuClrBuf[5] = (color & 0xFFFFFF) | 0x60000000;
        gpuClrBuf[6] = LOW(arg0->x);
        gpuClrBuf[7] = LOW(arg0->w);
        gpuClrBuf[8] = 0x03FFFFFF;
        gpuClrBuf[9] = 0xE3000000 | _param(3);
        gpuClrBuf[10] = 0xE4000000 | _param(4);
        gpuClrBuf[11] = 0xE5000000 | _param(5);
    } else {
        gpuClrBuf[0] = 0x04FFFFFF;
        gpuClrBuf[1] = 0xE6000000;

        gpuClrBuf[2] = (color & 0xFFFFFF) | 0x02000000;
        gpuClrBuf[3] = LOW(arg0->x);
        gpuClrBuf[4] = LOW(arg0->w);
    }
    _cwc(&gpuClrBuf[0]);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", _clr);
#endif

#ifdef NON_MATCHING
/* 2026-10-17: donor shape with retail's in-place clamp; the max size words read as volatile u16 give retail's lhu/sll/sra but the clamp temps allocate differently (about 60 rows off). */
/* LoadImage: copies host memory to VRAM. */
s32 _dws(RECT *arg0, s32 *arg1) {
    s32 temp_a0;
    s32 size;
    s32 var_s0;
    s32 var_s4;

    set_alarm();
    var_s4 = 0;

    arg0->w = GPU_CLAMP(arg0->w, 0, (s16)gfxMaxW[0]);
    arg0->h = GPU_CLAMP(arg0->h, 0, (s16)gfxMaxH[0]);

    temp_a0 = ((arg0->w * arg0->h) + 1) / 2;
    if (temp_a0 <= 0) {
        return -1;
    }
    var_s0 = temp_a0 % 16;
    size = temp_a0 / 16;
    while (!(*GPU_STATUS & 0x04000000)) {
        if (get_alarm()) {
            return -1;
        }
    }

    *GPU_STATUS = 0x04000000;

    *GPU_DATA = 0x01000000;
    *GPU_DATA = var_s4 ? 0xB0000000 : 0xA0000000;
    *GPU_DATA = LOW(arg0->x);
    *GPU_DATA = LOW(arg0->w);

    while (var_s0--) {
        *GPU_DATA = *arg1++;
    }

    if (size != 0) {
        *GPU_STATUS = 0x04000002;
        *DMA2_MADR = (s32)arg1;
        *DMA2_BCR = (size << 0x10) | 0x10;
        *DMA2_CHCR = 0x01000201;
    }

    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", _dws);
#endif

#ifdef NON_MATCHING
/* 2026-10-17: donor shape with retail's in-place clamp; the max size words read as volatile u16 give retail's lhu/sll/sra but the clamp temps allocate differently (about 60 rows off). */
/* StoreImage: copies VRAM to host memory. */
s32 _drs(RECT *arg0, s32 *arg1) {
    s32 temp_a0;
    s32 size;
    s32 var_s0;

    set_alarm();

    arg0->w = GPU_CLAMP(arg0->w, 0, (s16)gfxMaxW[0]);
    arg0->h = GPU_CLAMP(arg0->h, 0, (s16)gfxMaxH[0]);

    temp_a0 = ((arg0->w * arg0->h) + 1) / 2;
    if (temp_a0 <= 0) {
        return -1;
    }
    var_s0 = temp_a0 % 16;
    size = temp_a0 / 16;
    while (!(*GPU_STATUS & 0x04000000)) {
        if (get_alarm()) {
            return -1;
        }
    }

    *GPU_STATUS = 0x04000000;

    *GPU_DATA = 0x01000000;
    *GPU_DATA = 0xC0000000;
    *GPU_DATA = LOW(arg0->x);
    *GPU_DATA = LOW(arg0->w);

    while (!(*GPU_STATUS & 0x08000000)) {
        if (get_alarm()) {
            return -1;
        }
    }

    while (var_s0--) {
        *arg1++ = *GPU_DATA;
    }

    if (size != 0) {
        *GPU_STATUS = 0x04000003;
        *DMA2_MADR = (s32)arg1;
        *DMA2_BCR = (size << 0x10) | 0x10;
        *DMA2_CHCR = 0x01000200;
    }

    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", _drs);
#endif

/* SPDX-License-Identifier: MIT */

extern u8 D_800AD124[];

void _ctl(u32 arg0) {
    *(u32 *)D_8009DB64[0] = arg0;
    D_800AD124[arg0 >> 24] = arg0;
}

/* SPDX-License-Identifier: MIT */

u8 _getctl(s32 arg0) {
    return D_800AD124[arg0];
}

s32 _cwb(s32 *arg0, s32 arg1) {
    s32 i;
    extern s32 *D_8009DB60[];

    *(volatile u32 *)D_8009DB64[0] = 0x04000000;
    for (i = arg1 - 1; i != -1; i--) {
        *(volatile u32 *)D_8009DB60[0] = *arg0++;
    }
    return 0;
}

void _cwc(s32 arg0) {
    extern s32 *D_8009DB68[];
    extern s32 *D_8009DB6C[];
    extern s32 *D_8009DB70[];

    *(volatile u32 *)D_8009DB64[0] = 0x04000002;
    *(volatile u32 *)D_8009DB68[0] = arg0;
    *(volatile u32 *)D_8009DB6C[0] = 0;
    *(volatile u32 *)D_8009DB70[0] = 0x01000401;
}

s32 _param(s32 arg0) {
    *GPU_STATUS = 0x10000000 | arg0;
    return *GPU_DATA & 0xFFFFFF;
}

/* SPDX-License-Identifier: MIT */

extern s32 D_8009DB94[];
extern s32 D_8009DB98[];
extern s32 D_8009DB9C[];
extern volatile s32 D_8009DA98[];
extern u8 D_8009DA91[];
extern s32 *D_8009DB70[];
extern s32 D_8009DB84[];
extern s32 D_8009DB88[];
extern s32 D_8009DB8C[];
extern s32 D_800BC558[];
extern s32 D_800BC550[];
extern s32 D_800BC554[];
extern s32 D_800BC54C[];
extern void set_alarm(void);
extern s32 get_alarm(void);
extern s32 _exeque(void);
extern s32 SetIntrMaskFull(s32 arg0) asm("SetIntrMask");

s32 _addque2(Callback func, s32 *arg, s32 size, s32 arg2);

s32 _addque(Callback func, s32 *arg, s32 arg2) {
    return _addque2(func, arg, 0, arg2);
}

s32 _addque2(Callback func, s32 *arg, s32 size, s32 arg2) {
    s32 i;
    s32 *cursor;
    s32 *buf;
    s32 old;
    s32 spinMask;
    s32 debugFlag;
    s32 dmaStat;
    s32 status;
    register s32 idxv asm("v1");

    set_alarm();
    while (((D_8009DB94[0] + 1) & 0x3F) == D_8009DB98[0]) {
        if (get_alarm() != 0) {
            return -1;
        }
        _exeque();
    }
    old = SetIntrMaskFull(0);
    D_8009DA98[0] = 1;
    debugFlag = D_8009DA91[0];
    asm("");
    D_8009DB9C[0] = old;
    spinMask = 0x4000000;
    if (debugFlag != 0) {
        if (D_8009DB94[0] != D_8009DB98[0]) {
            goto queue;
        }
        asm("");
        dmaStat = *D_8009DB70[0];
        if ((dmaStat & 0x1000000) != 0) {
            goto queue;
        }
        if (D_8009DA9C[0] != 0) {
            goto queue;
        }
    }
    do {
        status = *(volatile s32 *)D_8009DB64[0];
    } while ((status & spinMask) == 0);
    func(arg, arg2);
    *(volatile Callback *)&D_8009DB84[0] = func;
    D_8009DB88[0] = (s32)arg;
    D_8009DB8C[0] = arg2;
    SetIntrMaskFull(D_8009DB9C[0]);
    return 0;
queue:
    DMACallback(2, _exeque);
    i = 0;
    if (size != 0) {
        buf = D_800BC558;
        cursor = arg;
        asm("" : : "r"(size));
    copyLoop:
        if (i < size / 4) {
            idxv = D_8009DB94[0];
            *(s32 *)(i * 4 + (idxv * 0x60 + (u32)buf)) = *cursor;
            cursor++;
            i++;
            asm("");
            goto copyLoop;
        }
        *(s32 *)((u8 *)D_800BC550 + D_8009DB94[0] * 0x60) =
            D_8009DB94[0] * 0x60 + (u32)D_800BC558;
    } else {
        *(s32 *)((u8 *)D_800BC550 + D_8009DB94[0] * 0x60) = (s32)arg;
    }
    *(s32 *)((u8 *)D_800BC554 + D_8009DB94[0] * 0x60) = arg2;
    *(Callback *)((u8 *)D_800BC54C + D_8009DB94[0] * 0x60) = func;
    ((s32 *)D_8009DB98)[-1] = (D_8009DB94[0] + 1) & 0x3F;
    SetIntrMaskFull(D_8009DB9C[0]);
    _exeque();
    return (((s32 *)D_8009DB9C)[-2] - D_8009DB98[0]) & 0x3F;
}

typedef struct GpuQueueItem {
    void (*func)(s32 *, s32);
    s32 *arg;
    s32 arg2;
    s32 data[21];
} GpuQueueItem;

typedef struct GpuLast {
    void (*func)(s32 *, s32);
    s32 *arg;
    s32 arg2;
} GpuLast;

extern volatile GpuQueueItem gpuQueue[];
extern GpuLast gpuLast;
extern volatile s32 _qin;
extern volatile s32 _qout;
extern s32 gpuSavedMask;
extern s32 gpuSavedMask2;
extern s32 gpuAlarmEnd;
extern s32 gpuAlarmCount;
extern u8 gpuCtlBuf[];

#ifdef NON_MATCHING
/* 2026-10-17: right control flow, but 0x2CC bytes against 0x2FC: retail
 * recomputes the queue index (qout * 0x60) for every field access. */
/* Runs queued drawing commands while the GPU DMA is idle. */
s32 _exeque(void) {
    s32 ret;

    ret = 1;
    if (!(*DMA2_CHCR & 0x01000000)) {
        gpuSavedMask2 = SetIntrMaskFull(0);
        if (_qin != _qout && !(*DMA2_CHCR & 0x01000000)) {
            do {
                if (((_qout + 1) & 0x3F) == _qin && gGfx.drawSyncCb == 0) {
                    DMACallback(2, 0);
                }
                if (!(*GPU_STATUS & 0x04000000)) {
                    do {
                    } while (!(*GPU_STATUS & 0x04000000));
                }
                gpuQueue[_qout].func(gpuQueue[_qout].arg, gpuQueue[_qout].arg2);
                gpuLast.func = gpuQueue[_qout].func;
                gpuLast.arg = gpuQueue[_qout].arg;
                gpuLast.arg2 = gpuQueue[_qout].arg2;
                _qout = (_qout + 1) & 0x3F;
            } while (_qin != _qout && !(*DMA2_CHCR & 0x01000000));
        }
        SetIntrMaskFull(gpuSavedMask2);
        if (_qin == _qout && !(*DMA2_CHCR & 0x01000000) && gGfx.pad8 != 0 &&
            gGfx.drawSyncCb != 0) {
            gGfx.pad8 = 0;
            gGfx.drawSyncCb();
        }
        ret = (_qin - _qout) & 0x3F;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", _exeque);
#endif

/* Resets the GPU (mode 0 also clears the control shadow and the queue) and
 * flushes the command queue. */
inline s32 _reset(s32 arg0) {
    s32 intrMask;

    intrMask = SetIntrMaskFull(0);
    _qout = 0;
    gpuSavedMask = intrMask;
    _qin = _qout;

    switch (arg0 & 7) {
    case 0:
        *DMA2_CHCR = 0x401;
        *DPCR |= 0x800;
        *GPU_STATUS = 0;
        memset(gpuCtlBuf, 0, 0x100);
        memset(gpuQueue, 0, sizeof(GpuQueueItem) * 64);
        break;
    case 1:
        *DMA2_CHCR = 0x401;
        *DPCR |= 0x800;
        *GPU_STATUS = 0x02000000;
        *GPU_STATUS = 0x01000000;
        break;
    }
    SetIntrMaskFull(gpuSavedMask);
    if ((arg0 & 7) == 0) {
        return _version(arg0);
    }
    return 0;
}

s32 _sync(s32 mode) {
    s32 n;

    if (mode == 0) {
        set_alarm();
        while (_qin != _qout) {
            _exeque();
            if (get_alarm()) {
                return -1;
            }
        }
        while ((*DMA2_CHCR & 0x01000000) || !(*GPU_STATUS & 0x04000000)) {
            if (get_alarm()) {
                return -1;
            }
        }
        return 0;
    }
    n = (_qin - _qout) & 0x3F;
    if (n != 0) {
        _exeque();
    }
    if ((*DMA2_CHCR & 0x01000000) || !(*GPU_STATUS & 0x04000000)) {
        if (n == 0) {
            return 1;
        }
        return n;
    }
    return n;
}

/* SPDX-License-Identifier: MIT */

extern s32 D_8009DBA8[];
extern s32 D_8009DBAC[];

void set_alarm(void) {
    D_8009DBA8[0] = VSync(-1) + 0xF0;
    D_8009DBAC[0] = 0;
}

extern char D_80090800[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090800);
extern char D_80090834[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090834);
#ifdef NON_MATCHING
/* 2026-10-17: retail loads the printf arguments in a different order and has 2 more rows than this draft */

s32 get_alarm(void) {
    if (gpuAlarmEnd < VSync(-1) || gpuAlarmCount++ > 0xF0000) {
        printf(D_80090800, (_qin - _qout) & 0x3F, *GPU_STATUS, *DMA2_CHCR,
               *DMA2_MADR);
        printf(D_80090834, gpuLast.func, gpuLast.arg, gpuLast.arg2);
        _reset(1);
        return -1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", get_alarm);
#endif

s32 _version(s32 mode) {
    *GPU_STATUS = 0x10000007;
    if ((*GPU_DATA & 0xFFFFFF) != 2) {
        *GPU_DATA = (*GPU_STATUS & 0x3FFF) | 0xE1001000;
        *GPU_DATA;
        if (!(*GPU_STATUS & 0x1000)) {
            return 0;
        }
        if (!(mode & 8)) {
            return 1;
        }
        *GPU_STATUS = 0x20000504;
        return 2;
    }
    if (!(mode & 8)) {
        return 3;
    }
    *GPU_STATUS = 0x09000001;
    return 4;
}

void MemsetBytes(unsigned char *dest, unsigned char value,
                 int count) asm("memset");
void MemsetBytes(unsigned char *dest, unsigned char value, int count) {
    int remaining;

    remaining = count - 1;
    if (remaining != -1) {
        do {
            *dest = value;
            remaining--;
            dest++;
        } while (remaining != -1);
    }
}

ASM_FUNC(GPU_cw, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x49 # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

void GsGetTimInfo(u8 *src, u8 *dst) {
    u32 flags;
    u8 *image;
    flags = *(u32 *)src;
    *(u32 *)dst = flags;
    if ((flags >> 3) & 1) {
        src += 4;
        image = src + ((*(u32 *)src >> 2) * 4);
        src += 4;
        *(u16 *)(dst + 0x10) = *(u16 *)src;
        *(u16 *)(dst + 0x12) = *(u16 *)(src + 2);
        src += 4;
        *(u16 *)(dst + 0x14) = *(u16 *)src;
        *(u16 *)(dst + 0x16) = *(u16 *)(src + 2);
        src += 4;
        *(u32 *)(dst + 0x18) = (u32)src;
        image += 4;
        *(u16 *)(dst + 4) = *(u16 *)image;
        *(u16 *)(dst + 6) = *(u16 *)(image + 2);
        image += 4;
        *(u16 *)(dst + 8) = *(u16 *)image;
        *(u16 *)(dst + 0xA) = *(u16 *)(image + 2);
        image += 4;
        *(u32 *)(dst + 0xC) = (u32)image;
        return;
    }
    src += 8;
    *(u16 *)(dst + 4) = *(u16 *)src;
    *(u16 *)(dst + 6) = *(u16 *)(src + 2);
    src += 4;
    *(u16 *)(dst + 8) = *(u16 *)src;
    *(u16 *)(dst + 0xA) = *(u16 *)(src + 2);
    src += 4;
    *(u32 *)(dst + 0xC) = (u32)src;
}

void SetFogFar(s32 a, s32 h) {
    SetDQA(((-a) << 6) / h);
    SetDQB(0x01400000);
}

void SetFogNear(s32 a, s32 h) {
    SetDQA(-(a * 0x140) / h);
    SetDQB(0x01400000);
}

/* Saves $ra in D_8009DBB0 (the GTE patcher needs it), enables the GTE
 * in COP0 SR, then resets the GTE control registers: FLAG, OFX, H,
 * DQA, DQB, and the screen offsets. C cannot express the COP0 moves or
 * $ra used as data, so this is the Psy-Q assembly verbatim. */
ASM_FUNC(InitGeom, "    lui $at, %hi(D_8009DBB0) # maspsx-keep\n"
                   "    sw $ra, %lo(D_8009DBB0)($at) # maspsx-keep\n"
                   "    jal _patch_gte # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    lui $ra, %hi(D_8009DBB0) # maspsx-keep\n"
                   "    lw $ra, %lo(D_8009DBB0)($ra) # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    mfc0 $v0, $12 # maspsx-keep\n"
                   "    lui $v1, (0x40000000 >> 16) # maspsx-keep\n"
                   "    or $v0, $v0, $v1 # maspsx-keep\n"
                   "    mtc0 $v0, $12 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    addiu $t0, $zero, 0x155 # maspsx-keep\n"
                   "    ctc2 $t0, $29 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    addiu $t0, $zero, 0x100 # maspsx-keep\n"
                   "    ctc2 $t0, $30 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    addiu $t0, $zero, 0x3E8 # maspsx-keep\n"
                   "    ctc2 $t0, $26 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    addiu $t0, $zero, -0x1062 # maspsx-keep\n"
                   "    ctc2 $t0, $27 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    lui $t0, (0x1400000 >> 16) # maspsx-keep\n"
                   "    ctc2 $t0, $28 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    ctc2 $zero, $24 # maspsx-keep\n"
                   "    ctc2 $zero, $25 # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    jr $ra # maspsx-keep\n"
                   "    nop # maspsx-keep\n")

/* 1/sqrt via the GTE leading-zero counter: LZCR of n picks the scale,
 * then the seed comes from the short table at D_8009DBD4. Writes the
 * seed to *a1 and the exponent to *a2, returns 1, or -1 when n <= 0.
 * The sub/addi/b forms and the dead $t0 andi are Psy-Q assembly that
 * gcc 2.7.2 cannot emit, so the body is verbatim keep lines. */
ASM_FUNC(InvSquareRoot, "    mtc2 $a0, $30 # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    mfc2 $v0, $31 # maspsx-keep\n"
                        "    addiu $at, $zero, 0x20 # maspsx-keep\n"
                        "    beq $v0, $at, .L8007C4D0 # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    beqz $v0, .L8007C4D0 # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    andi $t0, $v0, 0x1 # maspsx-keep\n"
                        "    addiu $t2, $zero, -0x2 # maspsx-keep\n"
                        "    and $t2, $v0, $t2 # maspsx-keep\n"
                        "    addiu $t1, $zero, 0x1F # maspsx-keep\n"
                        "    sub $t1, $t1, $t2 # maspsx-keep\n"
                        "    sra $t1, $t1, 1 # maspsx-keep\n"
                        "    addi $t3, $t2, -0x18 # maspsx-keep\n"
                        "    bltz $t3, .L8007C49C # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    sllv $t4, $a0, $t3 # maspsx-keep\n"
                        "    b .L8007C4A8 # maspsx-keep\n"
                        "    .L8007C49C: # maspsx-keep\n"
                        "    addiu $t3, $zero, 0x18 # maspsx-keep\n"
                        "    sub $t3, $t3, $t2 # maspsx-keep\n"
                        "    srav $t4, $a0, $t3 # maspsx-keep\n"
                        "    .L8007C4A8: # maspsx-keep\n"
                        "    addi $t4, $t4, -0x40 # maspsx-keep\n"
                        "    sll $t4, $t4, 1 # maspsx-keep\n"
                        "    lui $t5, %hi(D_8009DBD4) # maspsx-keep\n"
                        "    addu $t5, $t5, $t4 # maspsx-keep\n"
                        "    lh $t5, %lo(D_8009DBD4)($t5) # maspsx-keep\n"
                        "    sw $t1, 0x0($a2) # maspsx-keep\n"
                        "    sw $t5, 0x0($a1) # maspsx-keep\n"
                        "    addiu $v0, $zero, 0x1 # maspsx-keep\n"
                        "    jr $ra # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    .L8007C4D0: # maspsx-keep\n"
                        "    jr $ra # maspsx-keep\n"
                        "    addiu $v0, $zero, -0x1 # maspsx-keep\n")

/* Loads the vector as three words, then joins VectorNormalSS's
 * .L8007C52C entry (included below), which runs the normalisation. */
ASM_FUNC(VectorNormalS, "    lw $t0, 0x0($a0) # maspsx-keep\n"
                        "    lw $t1, 0x4($a0) # maspsx-keep\n"
                        "    lw $t2, 0x8($a0) # maspsx-keep\n"
                        "    b .L8007C52C # maspsx-keep\n"
                        "    addu $a3, $ra, $zero # maspsx-keep\n")

/* Loads the vector as three words, saves $ra in $a3, and calls the
 * shared normaliser; $t0-$t2 hold the scaled result on return. */
ASM_FUNC(VectorNormal, "    lw $t0, 0x0($a0) # maspsx-keep\n"
                       "    lw $t1, 0x4($a0) # maspsx-keep\n"
                       "    lw $t2, 0x8($a0) # maspsx-keep\n"
                       "    addu $a3, $ra, $zero # maspsx-keep\n"
                       "    jal func_8007C548 # maspsx-keep\n"
                       "    nop # maspsx-keep\n"
                       "    addu $ra, $a3, $zero # maspsx-keep\n"
                       "    sw $t0, 0x0($a1) # maspsx-keep\n"
                       "    sw $t1, 0x4($a1) # maspsx-keep\n"
                       "    jr $ra # maspsx-keep\n"
                       "    sw $t2, 0x8($a1) # maspsx-keep\n")

/* VectorNormalS branches into this function at .L8007C52C, so that
 * label must stay between the $ra save and the call. */
ASM_FUNC(VectorNormalSS, "    lh $t0, 0x0($a0) # maspsx-keep\n"
                         "    lh $t1, 0x2($a0) # maspsx-keep\n"
                         "    lh $t2, 0x4($a0) # maspsx-keep\n"
                         "    nop # maspsx-keep\n"
                         "    addu $a3, $ra, $zero # maspsx-keep\n"
                         "    .L8007C52C: # maspsx-keep\n"
                         "    jal func_8007C548 # maspsx-keep\n"
                         "    nop # maspsx-keep\n"
                         "    addu $ra, $a3, $zero # maspsx-keep\n"
                         "    sh $t0, 0x0($a1) # maspsx-keep\n"
                         "    sh $t1, 0x2($a1) # maspsx-keep\n"
                         "    jr $ra # maspsx-keep\n"
                         "    sh $t2, 0x4($a1) # maspsx-keep\n")

ASM_FUNC(func_8007C548, "mtc2 $t0, $9 # maspsx-keep\n"
                        "mtc2 $t1, $10 # maspsx-keep\n"
                        "mtc2 $t2, $11 # maspsx-keep\n"
                        "nop # maspsx-keep\n"
                        "sqr 0 # maspsx-keep\n"
                        "mfc2 $t3, $25 # maspsx-keep\n"
                        "mfc2 $t4, $26 # maspsx-keep\n"
                        "mfc2 $t5, $27 # maspsx-keep\n"
                        "add $t3, $t3, $t4 # maspsx-keep\n"
                        "add $v0, $t3, $t5 # maspsx-keep\n"
                        "mtc2 $v0, $30 # maspsx-keep\n"
                        "nop # maspsx-keep\n"
                        "nop # maspsx-keep\n"
                        "mfc2 $v1, $31 # maspsx-keep\n"
                        "addiu $at, $zero, -0x2 # maspsx-keep\n"
                        "and $v1, $v1, $at # maspsx-keep\n"
                        "addiu $t6, $zero, 0x1F # maspsx-keep\n"
                        "sub $t6, $t6, $v1 # maspsx-keep\n"
                        "addi $t3, $v1, -0x18 # maspsx-keep\n"
                        "bltz $t3, .L8007C5A4 # maspsx-keep\n"
                        "sra $t6, $t6, 1 # maspsx-keep\n"
                        "b .L8007C5B0 # maspsx-keep\n"
                        "sllv $t4, $v0, $t3 # maspsx-keep\n"
                        ".L8007C5A4: # maspsx-keep\n"
                        "addiu $t3, $zero, 0x18 # maspsx-keep\n"
                        "sub $t3, $t3, $v1 # maspsx-keep\n"
                        "srav $t4, $v0, $t3 # maspsx-keep\n"
                        ".L8007C5B0: # maspsx-keep\n"
                        "addi $t4, $t4, -0x40 # maspsx-keep\n"
                        "sll $t4, $t4, 1 # maspsx-keep\n"
                        "lui $t5, %hi(D_8009DBD4) # maspsx-keep\n"
                        "addu $t5, $t5, $t4 # maspsx-keep\n"
                        "lh $t5, %lo(D_8009DBD4)($t5) # maspsx-keep\n"
                        "nop # maspsx-keep\n"
                        "mtc2 $t5, $8 # maspsx-keep\n"
                        "mtc2 $t0, $9 # maspsx-keep\n"
                        "mtc2 $t1, $10 # maspsx-keep\n"
                        "mtc2 $t2, $11 # maspsx-keep\n"
                        "nop # maspsx-keep\n"
                        "nop # maspsx-keep\n"
                        "gpf 0 # maspsx-keep\n"
                        "mfc2 $t0, $25 # maspsx-keep\n"
                        "mfc2 $t1, $26 # maspsx-keep\n"
                        "mfc2 $t2, $27 # maspsx-keep\n"
                        "srav $t0, $t0, $t6 # maspsx-keep\n"
                        "srav $t1, $t1, $t6 # maspsx-keep\n"
                        "srav $t2, $t2, $t6 # maspsx-keep\n"
                        "jr $ra # maspsx-keep\n"
                        "nop # maspsx-keep\n")

/* Handwritten GTE asm: normalises m0's rotation matrix with two OP
 * commands and the VectorNormalS worker (func_8007C548), thrice.
 * The final nop is retail's padding before CompMatrix. */
ASM_FUNC(MatrixNormal, "    lh $t0, 0x0($a0) # maspsx-keep\n"
                       "    lh $t1, 0x2($a0) # maspsx-keep\n"
                       "    lh $t2, 0x4($a0) # maspsx-keep\n"
                       "    lh $t3, 0x6($a0) # maspsx-keep\n"
                       "    lh $t4, 0x8($a0) # maspsx-keep\n"
                       "    lh $t5, 0xA($a0) # maspsx-keep\n"
                       "    cfc2 $v0, $0 # maspsx-keep\n"
                       "    cfc2 $v1, $2 # maspsx-keep\n"
                       "    cfc2 $a2, $4 # maspsx-keep\n"
                       "    ctc2 $t0, $0 # maspsx-keep\n"
                       "    ctc2 $t1, $2 # maspsx-keep\n"
                       "    ctc2 $t2, $4 # maspsx-keep\n"
                       "    mtc2 $t5, $11 # maspsx-keep\n"
                       "    mtc2 $t3, $9 # maspsx-keep\n"
                       "    mtc2 $t4, $10 # maspsx-keep\n"
                       "    nop # maspsx-keep\n"
                       "    op 1 # maspsx-keep\n"
                       "    mfc2 $t7, $25 # maspsx-keep\n"
                       "    mfc2 $t8, $26 # maspsx-keep\n"
                       "    mfc2 $t9, $27 # maspsx-keep\n"
                       "    ctc2 $t3, $0 # maspsx-keep\n"
                       "    ctc2 $t4, $2 # maspsx-keep\n"
                       "    ctc2 $t5, $4 # maspsx-keep\n"
                       "    nop # maspsx-keep\n"
                       "    op 1 # maspsx-keep\n"
                       "    mtc2 $t3, $0 # maspsx-keep\n"
                       "    mtc2 $t4, $1 # maspsx-keep\n"
                       "    mtc2 $t5, $2 # maspsx-keep\n"
                       "    mfc2 $t0, $25 # maspsx-keep\n"
                       "    mfc2 $t1, $26 # maspsx-keep\n"
                       "    mfc2 $t2, $27 # maspsx-keep\n"
                       "    ctc2 $v0, $0 # maspsx-keep\n"
                       "    ctc2 $v1, $2 # maspsx-keep\n"
                       "    ctc2 $a2, $4 # maspsx-keep\n"
                       "    addu $a3, $ra, $zero # maspsx-keep\n"
                       "    jal func_8007C548 # maspsx-keep\n"
                       "    nop # maspsx-keep\n"
                       "    sh $t0, 0x0($a1) # maspsx-keep\n"
                       "    sh $t1, 0x2($a1) # maspsx-keep\n"
                       "    sh $t2, 0x4($a1) # maspsx-keep\n"
                       "    mfc2 $t0, $0 # maspsx-keep\n"
                       "    mfc2 $t1, $1 # maspsx-keep\n"
                       "    mfc2 $t2, $2 # maspsx-keep\n"
                       "    jal func_8007C548 # maspsx-keep\n"
                       "    nop # maspsx-keep\n"
                       "    sh $t0, 0x6($a1) # maspsx-keep\n"
                       "    sh $t1, 0x8($a1) # maspsx-keep\n"
                       "    sh $t2, 0xA($a1) # maspsx-keep\n"
                       "    addu $t0, $t7, $zero # maspsx-keep\n"
                       "    addu $t1, $t8, $zero # maspsx-keep\n"
                       "    jal func_8007C548 # maspsx-keep\n"
                       "    addu $t2, $t9, $zero # maspsx-keep\n"
                       "    addu $ra, $a3, $zero # maspsx-keep\n"
                       "    sh $t0, 0xC($a1) # maspsx-keep\n"
                       "    sh $t1, 0xE($a1) # maspsx-keep\n"
                       "    jr $ra # maspsx-keep\n"
                       "    sh $t2, 0x10($a1) # maspsx-keep\n"
                       "    nop # maspsx-keep\n")

ASM_FUNC(CompMatrix, "    lw $t0, 0x0($a0) # maspsx-keep\n"
                     "    lw $t1, 0x4($a0) # maspsx-keep\n"
                     "    lw $t2, 0x8($a0) # maspsx-keep\n"
                     "    lw $t3, 0xC($a0) # maspsx-keep\n"
                     "    lw $t4, 0x10($a0) # maspsx-keep\n"
                     "    ctc2 $t0, $0 # maspsx-keep\n"
                     "    ctc2 $t1, $1 # maspsx-keep\n"
                     "    ctc2 $t2, $2 # maspsx-keep\n"
                     "    ctc2 $t3, $3 # maspsx-keep\n"
                     "    ctc2 $t4, $4 # maspsx-keep\n"
                     "    lhu $t0, 0x0($a1) # maspsx-keep\n"
                     "    lw $t1, 0x4($a1) # maspsx-keep\n"
                     "    lw $t2, 0xC($a1) # maspsx-keep\n"
                     "    lui $at, 0xFFFF # maspsx-keep\n"
                     "    and $t1, $t1, $at # maspsx-keep\n"
                     "    or $t0, $t0, $t1 # maspsx-keep\n"
                     "    mtc2 $t0, $0 # maspsx-keep\n"
                     "    mtc2 $t2, $1 # maspsx-keep\n"
                     "    nop # maspsx-keep\n"
                     "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                     "    lhu $t0, 0x2($a1) # maspsx-keep\n"
                     "    lw $t1, 0x8($a1) # maspsx-keep\n"
                     "    lh $t2, 0xE($a1) # maspsx-keep\n"
                     "    sll $t1, $t1, 16 # maspsx-keep\n"
                     "    or $t0, $t0, $t1 # maspsx-keep\n"
                     "    mfc2 $t3, $9 # maspsx-keep\n"
                     "    mfc2 $t4, $10 # maspsx-keep\n"
                     "    mfc2 $t5, $11 # maspsx-keep\n"
                     "    mtc2 $t0, $0 # maspsx-keep\n"
                     "    mtc2 $t2, $1 # maspsx-keep\n"
                     "    nop # maspsx-keep\n"
                     "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                     "    lhu $t0, 0x4($a1) # maspsx-keep\n"
                     "    lw $t1, 0x8($a1) # maspsx-keep\n"
                     "    lw $t2, 0x10($a1) # maspsx-keep\n"
                     "    lui $at, 0xFFFF # maspsx-keep\n"
                     "    and $t1, $t1, $at # maspsx-keep\n"
                     "    or $t0, $t0, $t1 # maspsx-keep\n"
                     "    mfc2 $t6, $9 # maspsx-keep\n"
                     "    mfc2 $t7, $10 # maspsx-keep\n"
                     "    mfc2 $t8, $11 # maspsx-keep\n"
                     "    mtc2 $t0, $0 # maspsx-keep\n"
                     "    mtc2 $t2, $1 # maspsx-keep\n"
                     "    nop # maspsx-keep\n"
                     "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                     "    andi $t3, $t3, 0xFFFF # maspsx-keep\n"
                     "    sll $t6, $t6, 16 # maspsx-keep\n"
                     "    or $t6, $t6, $t3 # maspsx-keep\n"
                     "    sw $t6, 0x0($a2) # maspsx-keep\n"
                     "    andi $t5, $t5, 0xFFFF # maspsx-keep\n"
                     "    sll $t8, $t8, 16 # maspsx-keep\n"
                     "    or $t8, $t8, $t5 # maspsx-keep\n"
                     "    sw $t8, 0xC($a2) # maspsx-keep\n"
                     "    mfc2 $t0, $9 # maspsx-keep\n"
                     "    mfc2 $t1, $10 # maspsx-keep\n"
                     "    swc2 $11, 0x10($a2) # maspsx-keep\n"
                     "    lhu $t5, 0x14($a1) # maspsx-keep\n"
                     "    lw $t6, 0x18($a1) # maspsx-keep\n"
                     "    lw $t2, 0x1C($a1) # maspsx-keep\n"
                     "    sll $t6, $t6, 16 # maspsx-keep\n"
                     "    or $t5, $t5, $t6 # maspsx-keep\n"
                     "    mtc2 $t5, $0 # maspsx-keep\n"
                     "    mtc2 $t2, $1 # maspsx-keep\n"
                     "    nop # maspsx-keep\n"
                     "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                     "    sll $t4, $t4, 16 # maspsx-keep\n"
                     "    andi $t0, $t0, 0xFFFF # maspsx-keep\n"
                     "    or $t0, $t0, $t4 # maspsx-keep\n"
                     "    sw $t0, 0x4($a2) # maspsx-keep\n"
                     "    andi $t7, $t7, 0xFFFF # maspsx-keep\n"
                     "    sll $t1, $t1, 16 # maspsx-keep\n"
                     "    or $t1, $t1, $t7 # maspsx-keep\n"
                     "    sw $t1, 0x8($a2) # maspsx-keep\n"
                     "    mfc2 $t0, $25 # maspsx-keep\n"
                     "    mfc2 $t1, $26 # maspsx-keep\n"
                     "    mfc2 $t2, $27 # maspsx-keep\n"
                     "    lw $t3, 0x14($a0) # maspsx-keep\n"
                     "    lw $t4, 0x18($a0) # maspsx-keep\n"
                     "    lw $t5, 0x1C($a0) # maspsx-keep\n"
                     "    add $t0, $t0, $t3 # maspsx-keep\n"
                     "    add $t1, $t1, $t4 # maspsx-keep\n"
                     "    add $t2, $t2, $t5 # maspsx-keep\n"
                     "    sw $t0, 0x14($a2) # maspsx-keep\n"
                     "    sw $t1, 0x18($a2) # maspsx-keep\n"
                     "    sw $t2, 0x1C($a2) # maspsx-keep\n"
                     "    addu $v0, $a2, $zero # maspsx-keep\n"
                     "    jr $ra # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

ASM_FUNC(MulMatrix0, "    lw $t0, 0x0($a0) # maspsx-keep\n"
                     "    lw $t1, 0x4($a0) # maspsx-keep\n"
                     "    lw $t2, 0x8($a0) # maspsx-keep\n"
                     "    lw $t3, 0xC($a0) # maspsx-keep\n"
                     "    lw $t4, 0x10($a0) # maspsx-keep\n"
                     "    ctc2 $t0, $0 # maspsx-keep\n"
                     "    ctc2 $t1, $1 # maspsx-keep\n"
                     "    ctc2 $t2, $2 # maspsx-keep\n"
                     "    ctc2 $t3, $3 # maspsx-keep\n"
                     "    ctc2 $t4, $4 # maspsx-keep\n"
                     "    lhu $t0, 0x0($a1) # maspsx-keep\n"
                     "    lw $t1, 0x4($a1) # maspsx-keep\n"
                     "    lw $t2, 0xC($a1) # maspsx-keep\n"
                     "    lui $at, 0xFFFF # maspsx-keep\n"
                     "    and $t1, $t1, $at # maspsx-keep\n"
                     "    or $t0, $t0, $t1 # maspsx-keep\n"
                     "    mtc2 $t0, $0 # maspsx-keep\n"
                     "    mtc2 $t2, $1 # maspsx-keep\n"
                     "    nop # maspsx-keep\n"
                     "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                     "    lhu $t0, 0x2($a1) # maspsx-keep\n"
                     "    lw $t1, 0x8($a1) # maspsx-keep\n"
                     "    lh $t2, 0xE($a1) # maspsx-keep\n"
                     "    sll $t1, $t1, 16 # maspsx-keep\n"
                     "    or $t0, $t0, $t1 # maspsx-keep\n"
                     "    mfc2 $t3, $9 # maspsx-keep\n"
                     "    mfc2 $t4, $10 # maspsx-keep\n"
                     "    mfc2 $t5, $11 # maspsx-keep\n"
                     "    mtc2 $t0, $0 # maspsx-keep\n"
                     "    mtc2 $t2, $1 # maspsx-keep\n"
                     "    nop # maspsx-keep\n"
                     "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                     "    lhu $t0, 0x4($a1) # maspsx-keep\n"
                     "    lw $t1, 0x8($a1) # maspsx-keep\n"
                     "    lw $t2, 0x10($a1) # maspsx-keep\n"
                     "    lui $at, 0xFFFF # maspsx-keep\n"
                     "    and $t1, $t1, $at # maspsx-keep\n"
                     "    or $t0, $t0, $t1 # maspsx-keep\n"
                     "    mfc2 $t6, $9 # maspsx-keep\n"
                     "    mfc2 $t7, $10 # maspsx-keep\n"
                     "    mfc2 $t8, $11 # maspsx-keep\n"
                     "    mtc2 $t0, $0 # maspsx-keep\n"
                     "    mtc2 $t2, $1 # maspsx-keep\n"
                     "    nop # maspsx-keep\n"
                     "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                     "    andi $t3, $t3, 0xFFFF # maspsx-keep\n"
                     "    sll $t6, $t6, 16 # maspsx-keep\n"
                     "    or $t6, $t6, $t3 # maspsx-keep\n"
                     "    sw $t6, 0x0($a2) # maspsx-keep\n"
                     "    andi $t5, $t5, 0xFFFF # maspsx-keep\n"
                     "    sll $t8, $t8, 16 # maspsx-keep\n"
                     "    or $t8, $t8, $t5 # maspsx-keep\n"
                     "    sw $t8, 0xC($a2) # maspsx-keep\n"
                     "    mfc2 $t0, $9 # maspsx-keep\n"
                     "    mfc2 $t1, $10 # maspsx-keep\n"
                     "    andi $t0, $t0, 0xFFFF # maspsx-keep\n"
                     "    sll $t4, $t4, 16 # maspsx-keep\n"
                     "    or $t0, $t0, $t4 # maspsx-keep\n"
                     "    sw $t0, 0x4($a2) # maspsx-keep\n"
                     "    andi $t7, $t7, 0xFFFF # maspsx-keep\n"
                     "    sll $t1, $t1, 16 # maspsx-keep\n"
                     "    or $t1, $t1, $t7 # maspsx-keep\n"
                     "    sw $t1, 0x8($a2) # maspsx-keep\n"
                     "    swc2 $11, 0x10($a2) # maspsx-keep\n"
                     "    addu $v0, $a2, $zero # maspsx-keep\n"
                     "    jr $ra # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

ASM_FUNC(MulRotMatrix0, "    lhu $t0, 0x0($a0) # maspsx-keep\n"
                        "    lw $t1, 0x4($a0) # maspsx-keep\n"
                        "    lw $t2, 0xC($a0) # maspsx-keep\n"
                        "    lui $at, 0xFFFF # maspsx-keep\n"
                        "    and $t1, $t1, $at # maspsx-keep\n"
                        "    or $t0, $t0, $t1 # maspsx-keep\n"
                        "    mtc2 $t0, $0 # maspsx-keep\n"
                        "    mtc2 $t2, $1 # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                        "    lhu $t0, 0x2($a0) # maspsx-keep\n"
                        "    lw $t1, 0x8($a0) # maspsx-keep\n"
                        "    lh $t2, 0xE($a0) # maspsx-keep\n"
                        "    sll $t1, $t1, 16 # maspsx-keep\n"
                        "    or $t0, $t0, $t1 # maspsx-keep\n"
                        "    mfc2 $t3, $9 # maspsx-keep\n"
                        "    mfc2 $t4, $10 # maspsx-keep\n"
                        "    mfc2 $t5, $11 # maspsx-keep\n"
                        "    mtc2 $t0, $0 # maspsx-keep\n"
                        "    mtc2 $t2, $1 # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                        "    lhu $t0, 0x4($a0) # maspsx-keep\n"
                        "    lw $t1, 0x8($a0) # maspsx-keep\n"
                        "    lw $t2, 0x10($a0) # maspsx-keep\n"
                        "    lui $at, 0xFFFF # maspsx-keep\n"
                        "    and $t1, $t1, $at # maspsx-keep\n"
                        "    or $t0, $t0, $t1 # maspsx-keep\n"
                        "    mfc2 $t6, $9 # maspsx-keep\n"
                        "    mfc2 $t7, $10 # maspsx-keep\n"
                        "    mfc2 $t8, $11 # maspsx-keep\n"
                        "    mtc2 $t0, $0 # maspsx-keep\n"
                        "    mtc2 $t2, $1 # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                        "    andi $t3, $t3, 0xFFFF # maspsx-keep\n"
                        "    sll $t6, $t6, 16 # maspsx-keep\n"
                        "    or $t6, $t6, $t3 # maspsx-keep\n"
                        "    sw $t6, 0x0($a1) # maspsx-keep\n"
                        "    andi $t5, $t5, 0xFFFF # maspsx-keep\n"
                        "    sll $t8, $t8, 16 # maspsx-keep\n"
                        "    or $t8, $t8, $t5 # maspsx-keep\n"
                        "    sw $t8, 0xC($a1) # maspsx-keep\n"
                        "    mfc2 $t0, $9 # maspsx-keep\n"
                        "    mfc2 $t1, $10 # maspsx-keep\n"
                        "    andi $t0, $t0, 0xFFFF # maspsx-keep\n"
                        "    sll $t4, $t4, 16 # maspsx-keep\n"
                        "    or $t0, $t0, $t4 # maspsx-keep\n"
                        "    sw $t0, 0x4($a1) # maspsx-keep\n"
                        "    andi $t7, $t7, 0xFFFF # maspsx-keep\n"
                        "    sll $t1, $t1, 16 # maspsx-keep\n"
                        "    or $t1, $t1, $t7 # maspsx-keep\n"
                        "    sw $t1, 0x8($a1) # maspsx-keep\n"
                        "    swc2 $11, 0x10($a1) # maspsx-keep\n"
                        "    addu $v0, $a1, $zero # maspsx-keep\n"
                        "    jr $ra # maspsx-keep\n"
                        "    nop # maspsx-keep\n")

ASM_FUNC(MulRotMatrix, "    lw $t0, 0x0($a0) # maspsx-keep\n"
                       "    lw $t1, 0x4($a0) # maspsx-keep\n"
                       "    lw $t2, 0xC($a0) # maspsx-keep\n"
                       "    andi $t0, $t0, 0xFFFF # maspsx-keep\n"
                       "    lui $at, 0xFFFF # maspsx-keep\n"
                       "    and $t1, $t1, $at # maspsx-keep\n"
                       "    or $t0, $t0, $t1 # maspsx-keep\n"
                       "    mtc2 $t0, $0 # maspsx-keep\n"
                       "    mtc2 $t2, $1 # maspsx-keep\n"
                       "    nop # maspsx-keep\n"
                       "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                       "    lhu $t0, 0x2($a0) # maspsx-keep\n"
                       "    lw $t1, 0x8($a0) # maspsx-keep\n"
                       "    lh $t2, 0xE($a0) # maspsx-keep\n"
                       "    sll $t1, $t1, 16 # maspsx-keep\n"
                       "    or $t0, $t0, $t1 # maspsx-keep\n"
                       "    mfc2 $t3, $9 # maspsx-keep\n"
                       "    mfc2 $t4, $10 # maspsx-keep\n"
                       "    mfc2 $t5, $11 # maspsx-keep\n"
                       "    mtc2 $t0, $0 # maspsx-keep\n"
                       "    mtc2 $t2, $1 # maspsx-keep\n"
                       "    nop # maspsx-keep\n"
                       "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                       "    lhu $t0, 0x4($a0) # maspsx-keep\n"
                       "    lw $t1, 0x8($a0) # maspsx-keep\n"
                       "    lw $t2, 0x10($a0) # maspsx-keep\n"
                       "    lui $at, 0xFFFF # maspsx-keep\n"
                       "    and $t1, $t1, $at # maspsx-keep\n"
                       "    or $t0, $t0, $t1 # maspsx-keep\n"
                       "    mfc2 $t6, $9 # maspsx-keep\n"
                       "    mfc2 $t7, $10 # maspsx-keep\n"
                       "    mfc2 $t8, $11 # maspsx-keep\n"
                       "    mtc2 $t0, $0 # maspsx-keep\n"
                       "    mtc2 $t2, $1 # maspsx-keep\n"
                       "    nop # maspsx-keep\n"
                       "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                       "    andi $t3, $t3, 0xFFFF # maspsx-keep\n"
                       "    sll $t6, $t6, 16 # maspsx-keep\n"
                       "    or $t6, $t6, $t3 # maspsx-keep\n"
                       "    sw $t6, 0x0($a0) # maspsx-keep\n"
                       "    andi $t5, $t5, 0xFFFF # maspsx-keep\n"
                       "    sll $t8, $t8, 16 # maspsx-keep\n"
                       "    or $t8, $t8, $t5 # maspsx-keep\n"
                       "    sw $t8, 0xC($a0) # maspsx-keep\n"
                       "    mfc2 $t0, $9 # maspsx-keep\n"
                       "    mfc2 $t1, $10 # maspsx-keep\n"
                       "    andi $t0, $t0, 0xFFFF # maspsx-keep\n"
                       "    sll $t4, $t4, 16 # maspsx-keep\n"
                       "    or $t0, $t0, $t4 # maspsx-keep\n"
                       "    sw $t0, 0x4($a0) # maspsx-keep\n"
                       "    andi $t7, $t7, 0xFFFF # maspsx-keep\n"
                       "    sll $t1, $t1, 16 # maspsx-keep\n"
                       "    or $t1, $t1, $t7 # maspsx-keep\n"
                       "    sw $t1, 0x8($a0) # maspsx-keep\n"
                       "    swc2 $11, 0x10($a0) # maspsx-keep\n"
                       "    addu $v0, $a0, $zero # maspsx-keep\n"
                       "    jr $ra # maspsx-keep\n"
                       "    nop # maspsx-keep\n")

/* m0 = m0 * m1, using the GTE rotation matrix registers and mvmva; the
 * product is written back to the rotation registers and m0 is returned.
 * Handwritten library asm (LIBGTE MTX_00C), kept verbatim. */
ASM_FUNC(SetMulMatrix, "    lw $t0, 0x0($a0) # maspsx-keep\n"
                       "    lw $t1, 0x4($a0) # maspsx-keep\n"
                       "    lw $t2, 0x8($a0) # maspsx-keep\n"
                       "    lw $t3, 0xC($a0) # maspsx-keep\n"
                       "    lw $t4, 0x10($a0) # maspsx-keep\n"
                       "    ctc2 $t0, $0 # maspsx-keep\n"
                       "    ctc2 $t1, $1 # maspsx-keep\n"
                       "    ctc2 $t2, $2 # maspsx-keep\n"
                       "    ctc2 $t3, $3 # maspsx-keep\n"
                       "    ctc2 $t4, $4 # maspsx-keep\n"
                       "    lhu $t0, 0x0($a1) # maspsx-keep\n"
                       "    lw $t1, 0x4($a1) # maspsx-keep\n"
                       "    lw $t2, 0xC($a1) # maspsx-keep\n"
                       "    lui $at, (0xFFFF0000 >> 16) # maspsx-keep\n"
                       "    and $t1, $t1, $at # maspsx-keep\n"
                       "    or $t0, $t0, $t1 # maspsx-keep\n"
                       "    mtc2 $t0, $0 # maspsx-keep\n"
                       "    mtc2 $t2, $1 # maspsx-keep\n"
                       "    nop # maspsx-keep\n"
                       "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                       "    lhu $t0, 0x2($a1) # maspsx-keep\n"
                       "    lw $t1, 0x8($a1) # maspsx-keep\n"
                       "    lh $t2, 0xE($a1) # maspsx-keep\n"
                       "    sll $t1, $t1, 16 # maspsx-keep\n"
                       "    or $t0, $t0, $t1 # maspsx-keep\n"
                       "    mfc2 $t3, $9 # maspsx-keep\n"
                       "    mfc2 $t4, $10 # maspsx-keep\n"
                       "    mfc2 $t5, $11 # maspsx-keep\n"
                       "    mtc2 $t0, $0 # maspsx-keep\n"
                       "    mtc2 $t2, $1 # maspsx-keep\n"
                       "    nop # maspsx-keep\n"
                       "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                       "    lhu $t0, 0x4($a1) # maspsx-keep\n"
                       "    lw $t1, 0x8($a1) # maspsx-keep\n"
                       "    lw $t2, 0x10($a1) # maspsx-keep\n"
                       "    lui $at, (0xFFFF0000 >> 16) # maspsx-keep\n"
                       "    and $t1, $t1, $at # maspsx-keep\n"
                       "    or $t0, $t0, $t1 # maspsx-keep\n"
                       "    mfc2 $t6, $9 # maspsx-keep\n"
                       "    mfc2 $t7, $10 # maspsx-keep\n"
                       "    mfc2 $t8, $11 # maspsx-keep\n"
                       "    mtc2 $t0, $0 # maspsx-keep\n"
                       "    mtc2 $t2, $1 # maspsx-keep\n"
                       "    nop # maspsx-keep\n"
                       "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                       "    andi $t3, $t3, 0xFFFF # maspsx-keep\n"
                       "    sll $t6, $t6, 16 # maspsx-keep\n"
                       "    or $t6, $t6, $t3 # maspsx-keep\n"
                       "    andi $t5, $t5, 0xFFFF # maspsx-keep\n"
                       "    sll $t8, $t8, 16 # maspsx-keep\n"
                       "    or $t8, $t8, $t5 # maspsx-keep\n"
                       "    mfc2 $t0, $9 # maspsx-keep\n"
                       "    mfc2 $t1, $10 # maspsx-keep\n"
                       "    mfc2 $t2, $11 # maspsx-keep\n"
                       "    andi $t0, $t0, 0xFFFF # maspsx-keep\n"
                       "    sll $t4, $t4, 16 # maspsx-keep\n"
                       "    or $t0, $t0, $t4 # maspsx-keep\n"
                       "    andi $t7, $t7, 0xFFFF # maspsx-keep\n"
                       "    sll $t1, $t1, 16 # maspsx-keep\n"
                       "    or $t1, $t1, $t7 # maspsx-keep\n"
                       "    ctc2 $t6, $0 # maspsx-keep\n"
                       "    ctc2 $t0, $1 # maspsx-keep\n"
                       "    ctc2 $t1, $2 # maspsx-keep\n"
                       "    ctc2 $t8, $3 # maspsx-keep\n"
                       "    ctc2 $t2, $4 # maspsx-keep\n"
                       "    addu $v0, $a0, $zero # maspsx-keep\n"
                       "    jr $ra # maspsx-keep\n"
                       "    nop # maspsx-keep\n")

ASM_FUNC(ApplyMatrixLV, "lw $t0, 0x0($a0) # maspsx-keep\n"
                        "lw $t1, 0x4($a0) # maspsx-keep\n"
                        "lw $t2, 0x8($a0) # maspsx-keep\n"
                        "lw $t3, 0xC($a0) # maspsx-keep\n"
                        "lw $t4, 0x10($a0) # maspsx-keep\n"
                        "ctc2 $t0, $0 # maspsx-keep\n"
                        "ctc2 $t1, $1 # maspsx-keep\n"
                        "ctc2 $t2, $2 # maspsx-keep\n"
                        "ctc2 $t3, $3 # maspsx-keep\n"
                        "ctc2 $t4, $4 # maspsx-keep\n"
                        "lw $t0, 0x0($a1) # maspsx-keep\n"
                        "lw $t1, 0x4($a1) # maspsx-keep\n"
                        "lw $t2, 0x8($a1) # maspsx-keep\n"
                        "bgez $t0, .L8007CC8C # maspsx-keep\n"
                        "sra $t3, $t0, 15 # maspsx-keep\n"
                        "negu $t0, $t0 # maspsx-keep\n"
                        "sra $t3, $t0, 15 # maspsx-keep\n"
                        "andi $t0, $t0, 0x7FFF # maspsx-keep\n"
                        "negu $t3, $t3 # maspsx-keep\n"
                        "b .L8007CC90 # maspsx-keep\n"
                        "negu $t0, $t0 # maspsx-keep\n"
                        "sra $t3, $t0, 15 # maspsx-keep\n"
                        ".L8007CC8C: # maspsx-keep\n"
                        "andi $t0, $t0, 0x7FFF # maspsx-keep\n"
                        ".L8007CC90: # maspsx-keep\n"
                        "bgez $t1, .L8007CCB4 # maspsx-keep\n"
                        "sra $t4, $t1, 15 # maspsx-keep\n"
                        "negu $t1, $t1 # maspsx-keep\n"
                        "sra $t4, $t1, 15 # maspsx-keep\n"
                        "andi $t1, $t1, 0x7FFF # maspsx-keep\n"
                        "negu $t4, $t4 # maspsx-keep\n"
                        "b .L8007CCB8 # maspsx-keep\n"
                        "negu $t1, $t1 # maspsx-keep\n"
                        "sra $t4, $t1, 15 # maspsx-keep\n"
                        ".L8007CCB4: # maspsx-keep\n"
                        "andi $t1, $t1, 0x7FFF # maspsx-keep\n"
                        ".L8007CCB8: # maspsx-keep\n"
                        "bgez $t2, .L8007CCDC # maspsx-keep\n"
                        "sra $t5, $t2, 15 # maspsx-keep\n"
                        "negu $t2, $t2 # maspsx-keep\n"
                        "sra $t5, $t2, 15 # maspsx-keep\n"
                        "andi $t2, $t2, 0x7FFF # maspsx-keep\n"
                        "negu $t5, $t5 # maspsx-keep\n"
                        "b .L8007CCE0 # maspsx-keep\n"
                        "negu $t2, $t2 # maspsx-keep\n"
                        "sra $t5, $t2, 15 # maspsx-keep\n"
                        ".L8007CCDC: # maspsx-keep\n"
                        "andi $t2, $t2, 0x7FFF # maspsx-keep\n"
                        ".L8007CCE0: # maspsx-keep\n"
                        "mtc2 $t3, $9 # maspsx-keep\n"
                        "mtc2 $t4, $10 # maspsx-keep\n"
                        "mtc2 $t5, $11 # maspsx-keep\n"
                        "nop # maspsx-keep\n"
                        "mvmva 0, 0, 3, 3, 0 # maspsx-keep\n"
                        "mfc2 $t3, $25 # maspsx-keep\n"
                        "mfc2 $t4, $26 # maspsx-keep\n"
                        "mfc2 $t5, $27 # maspsx-keep\n"
                        "mtc2 $t0, $9 # maspsx-keep\n"
                        "mtc2 $t1, $10 # maspsx-keep\n"
                        "mtc2 $t2, $11 # maspsx-keep\n"
                        "nop # maspsx-keep\n"
                        "mvmva 1, 0, 3, 3, 0 # maspsx-keep\n"
                        "bgez $t3, .L8007CD2C # maspsx-keep\n"
                        "nop # maspsx-keep\n"
                        "negu $t3, $t3 # maspsx-keep\n"
                        "sll $t3, $t3, 3 # maspsx-keep\n"
                        "b .L8007CD30 # maspsx-keep\n"
                        "negu $t3, $t3 # maspsx-keep\n"
                        ".L8007CD2C: # maspsx-keep\n"
                        "sll $t3, $t3, 3 # maspsx-keep\n"
                        ".L8007CD30: # maspsx-keep\n"
                        "bgez $t4, .L8007CD48 # maspsx-keep\n"
                        "nop # maspsx-keep\n"
                        "negu $t4, $t4 # maspsx-keep\n"
                        "sll $t4, $t4, 3 # maspsx-keep\n"
                        "b .L8007CD4C # maspsx-keep\n"
                        "negu $t4, $t4 # maspsx-keep\n"
                        ".L8007CD48: # maspsx-keep\n"
                        "sll $t4, $t4, 3 # maspsx-keep\n"
                        ".L8007CD4C: # maspsx-keep\n"
                        "bgez $t5, .L8007CD64 # maspsx-keep\n"
                        "nop # maspsx-keep\n"
                        "negu $t5, $t5 # maspsx-keep\n"
                        "sll $t5, $t5, 3 # maspsx-keep\n"
                        "b .L8007CD68 # maspsx-keep\n"
                        "negu $t5, $t5 # maspsx-keep\n"
                        ".L8007CD64: # maspsx-keep\n"
                        "sll $t5, $t5, 3 # maspsx-keep\n"
                        ".L8007CD68: # maspsx-keep\n"
                        "mfc2 $t0, $25 # maspsx-keep\n"
                        "mfc2 $t1, $26 # maspsx-keep\n"
                        "mfc2 $t2, $27 # maspsx-keep\n"
                        "addu $t0, $t0, $t3 # maspsx-keep\n"
                        "addu $t1, $t1, $t4 # maspsx-keep\n"
                        "addu $t2, $t2, $t5 # maspsx-keep\n"
                        "sw $t0, 0x0($a2) # maspsx-keep\n"
                        "sw $t1, 0x4($a2) # maspsx-keep\n"
                        "sw $t2, 0x8($a2) # maspsx-keep\n"
                        "jr $ra # maspsx-keep\n"
                        "addu $v0, $a2, $zero # maspsx-keep\n")

/* libgte.h cannot be included in this unit (its SetFogNear prototype
 * conflicts with the local one), so the GTE vector types are defined
 * here, before their first use. */
typedef struct {
    short vx, vy, vz;
    short pad;
} SVECTOR;

typedef struct {
    long vx, vy, vz;
    long pad;
} VECTOR;

/* Applies the rotation part of the current rotation matrix to the
 * short vector v0 (mvmva with no translation vector) and stores the
 * long result in v1. Returns the third argument unchanged, exactly as
 * the Psy-Q assembly does. */
VECTOR *ApplyRotMatrix(SVECTOR *v0, VECTOR *v1, VECTOR *v2) {
    __asm__ volatile("lw $t0, 0($a0)\n\t"
                     "lw $t1, 4($a0)\n\t"
                     "mtc2 $t0, $0\n\t"
                     "mtc2 $t1, $1\n\t"
                     "nop\n\t"
                     "mvmva 1, 0, 0, 3, 0\n\t"
                     "swc2 $9, 0($a1)\n\t"
                     "swc2 $10, 4($a1)\n\t"
                     "swc2 $11, 8($a1)\n\t"
                     "addu $v0, $a2, $zero");
}

ASM_FUNC(ScaleMatrixL, "lw $t0, 0x0($a0) # maspsx-keep\n"
                       "lw $t3, 0x0($a1) # maspsx-keep\n"
                       "andi $t1, $t0, 0xFFFF # maspsx-keep\n"
                       "sll $t1, $t1, 16 # maspsx-keep\n"
                       "sra $t1, $t1, 16 # maspsx-keep\n"
                       "multu $t1, $t3 # maspsx-keep\n"
                       "sra $t2, $t0, 16 # maspsx-keep\n"
                       "lw $t4, 0x4($a1) # maspsx-keep\n"
                       "lw $t5, 0x8($a1) # maspsx-keep\n"
                       "lw $t0, 0x4($a0) # maspsx-keep\n"
                       "addu $v0, $a0, $zero # maspsx-keep\n"
                       "mflo $t1 # maspsx-keep\n"
                       "sra $t1, $t1, 12 # maspsx-keep\n"
                       "andi $t1, $t1, 0xFFFF # maspsx-keep\n"
                       "multu $t2, $t3 # maspsx-keep\n"
                       "mflo $t2 # maspsx-keep\n"
                       "sra $t2, $t2, 12 # maspsx-keep\n"
                       "sll $t2, $t2, 16 # maspsx-keep\n"
                       "or $t1, $t1, $t2 # maspsx-keep\n"
                       "sw $t1, 0x0($a0) # maspsx-keep\n"
                       "andi $t1, $t0, 0xFFFF # maspsx-keep\n"
                       "sll $t1, $t1, 16 # maspsx-keep\n"
                       "sra $t1, $t1, 16 # maspsx-keep\n"
                       "multu $t1, $t3 # maspsx-keep\n"
                       "sra $t2, $t0, 16 # maspsx-keep\n"
                       "lw $t0, 0x8($a0) # maspsx-keep\n"
                       "mflo $t1 # maspsx-keep\n"
                       "sra $t1, $t1, 12 # maspsx-keep\n"
                       "andi $t1, $t1, 0xFFFF # maspsx-keep\n"
                       "multu $t2, $t4 # maspsx-keep\n"
                       "mflo $t2 # maspsx-keep\n"
                       "sra $t2, $t2, 12 # maspsx-keep\n"
                       "sll $t2, $t2, 16 # maspsx-keep\n"
                       "or $t1, $t1, $t2 # maspsx-keep\n"
                       "sw $t1, 0x4($a0) # maspsx-keep\n"
                       "andi $t1, $t0, 0xFFFF # maspsx-keep\n"
                       "sll $t1, $t1, 16 # maspsx-keep\n"
                       "sra $t1, $t1, 16 # maspsx-keep\n"
                       "multu $t1, $t4 # maspsx-keep\n"
                       "sra $t2, $t0, 16 # maspsx-keep\n"
                       "lw $t0, 0xC($a0) # maspsx-keep\n"
                       "mflo $t1 # maspsx-keep\n"
                       "sra $t1, $t1, 12 # maspsx-keep\n"
                       "andi $t1, $t1, 0xFFFF # maspsx-keep\n"
                       "multu $t2, $t4 # maspsx-keep\n"
                       "mflo $t2 # maspsx-keep\n"
                       "sra $t2, $t2, 12 # maspsx-keep\n"
                       "sll $t2, $t2, 16 # maspsx-keep\n"
                       "or $t1, $t1, $t2 # maspsx-keep\n"
                       "sw $t1, 0x8($a0) # maspsx-keep\n"
                       "andi $t1, $t0, 0xFFFF # maspsx-keep\n"
                       "sll $t1, $t1, 16 # maspsx-keep\n"
                       "sra $t1, $t1, 16 # maspsx-keep\n"
                       "multu $t1, $t5 # maspsx-keep\n"
                       "sra $t2, $t0, 16 # maspsx-keep\n"
                       "lw $t0, 0x10($a0) # maspsx-keep\n"
                       "mflo $t1 # maspsx-keep\n"
                       "sra $t1, $t1, 12 # maspsx-keep\n"
                       "andi $t1, $t1, 0xFFFF # maspsx-keep\n"
                       "multu $t2, $t5 # maspsx-keep\n"
                       "mflo $t2 # maspsx-keep\n"
                       "sra $t2, $t2, 12 # maspsx-keep\n"
                       "sll $t2, $t2, 16 # maspsx-keep\n"
                       "or $t1, $t1, $t2 # maspsx-keep\n"
                       "sw $t1, 0xC($a0) # maspsx-keep\n"
                       "andi $t1, $t0, 0xFFFF # maspsx-keep\n"
                       "sll $t1, $t1, 16 # maspsx-keep\n"
                       "sra $t1, $t1, 16 # maspsx-keep\n"
                       "multu $t1, $t5 # maspsx-keep\n"
                       "mflo $t1 # maspsx-keep\n"
                       "sra $t1, $t1, 12 # maspsx-keep\n"
                       "jr $ra # maspsx-keep\n"
                       "sw $t1, 0x10($a0) # maspsx-keep\n")

ASM_FUNC(PushMatrix, "lui $t6, %hi(D_8009DD6C) # maspsx-keep\n"
                     "lw $t6, %lo(D_8009DD6C)($t6) # maspsx-keep\n"
                     "nop # maspsx-keep\n"
                     "slti $at, $t6, 0x280 # maspsx-keep\n"
                     "bnez $at, .L8007CF24 # maspsx-keep\n"
                     "lui $at, %hi(D_8009DD60) # maspsx-keep\n"
                     "sw $ra, %lo(D_8009DD60)($at) # maspsx-keep\n"
                     "lui $a0, %hi(D_8009DFF0) # maspsx-keep\n"
                     "jal printf # maspsx-keep\n"
                     "addiu $a0, $a0, %lo(D_8009DFF0) # maspsx-keep\n"
                     "lui $ra, %hi(D_8009DD60) # maspsx-keep\n"
                     "lw $ra, %lo(D_8009DD60)($ra) # maspsx-keep\n"
                     "nop # maspsx-keep\n"
                     "jr $ra # maspsx-keep\n"
                     "nop # maspsx-keep\n"
                     ".L8007CF24: # maspsx-keep\n"
                     "lui $t7, %hi(D_8009DD70) # maspsx-keep\n"
                     "addu $t7, $t7, $t6 # maspsx-keep\n"
                     "addiu $t7, $t7, %lo(D_8009DD70) # maspsx-keep\n"
                     "cfc2 $t0, $0 # maspsx-keep\n"
                     "cfc2 $t1, $1 # maspsx-keep\n"
                     "sw $t0, 0x0($t7) # maspsx-keep\n"
                     "sw $t1, 0x4($t7) # maspsx-keep\n"
                     "cfc2 $t0, $2 # maspsx-keep\n"
                     "cfc2 $t1, $3 # maspsx-keep\n"
                     "sw $t0, 0x8($t7) # maspsx-keep\n"
                     "sw $t1, 0xC($t7) # maspsx-keep\n"
                     "cfc2 $t0, $4 # maspsx-keep\n"
                     "nop # maspsx-keep\n"
                     "sw $t0, 0x10($t7) # maspsx-keep\n"
                     "cfc2 $t0, $5 # maspsx-keep\n"
                     "cfc2 $t1, $6 # maspsx-keep\n"
                     "cfc2 $t2, $7 # maspsx-keep\n"
                     "sw $t0, 0x14($t7) # maspsx-keep\n"
                     "sw $t1, 0x18($t7) # maspsx-keep\n"
                     "sw $t2, 0x1C($t7) # maspsx-keep\n"
                     "addi $t6, $t6, 0x20 # maspsx-keep\n"
                     "lui $at, %hi(D_8009DD6C) # maspsx-keep\n"
                     "sw $t6, %lo(D_8009DD6C)($at) # maspsx-keep\n"
                     "jr $ra # maspsx-keep\n"
                     "nop # maspsx-keep\n")

ASM_FUNC(PopMatrix, "lui $t6, %hi(D_8009DD6C) # maspsx-keep\n"
                    "lw $t6, %lo(D_8009DD6C)($t6) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "bgtz $t6, .L8007CFC0 # maspsx-keep\n"
                    "lui $at, %hi(D_8009DD60) # maspsx-keep\n"
                    "sw $ra, %lo(D_8009DD60)($at) # maspsx-keep\n"
                    "lui $a0, %hi(D_8009E021) # maspsx-keep\n"
                    "jal printf # maspsx-keep\n"
                    "addiu $a0, $a0, %lo(D_8009E021) # maspsx-keep\n"
                    "lui $ra, %hi(D_8009DD60) # maspsx-keep\n"
                    "lw $ra, %lo(D_8009DD60)($ra) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "jr $ra # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    ".L8007CFC0: # maspsx-keep\n"
                    "addi $t6, $t6, -0x20 # maspsx-keep\n"
                    "lui $at, %hi(D_8009DD6C) # maspsx-keep\n"
                    "sw $t6, %lo(D_8009DD6C)($at) # maspsx-keep\n"
                    "lui $t7, %hi(D_8009DD70) # maspsx-keep\n"
                    "addu $t7, $t7, $t6 # maspsx-keep\n"
                    "addiu $t7, $t7, %lo(D_8009DD70) # maspsx-keep\n"
                    "lw $t0, 0x0($t7) # maspsx-keep\n"
                    "lw $t1, 0x4($t7) # maspsx-keep\n"
                    "ctc2 $t0, $0 # maspsx-keep\n"
                    "ctc2 $t1, $1 # maspsx-keep\n"
                    "lw $t0, 0x8($t7) # maspsx-keep\n"
                    "lw $t1, 0xC($t7) # maspsx-keep\n"
                    "ctc2 $t0, $2 # maspsx-keep\n"
                    "ctc2 $t1, $3 # maspsx-keep\n"
                    "lw $t0, 0x10($t7) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "ctc2 $t0, $4 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "lw $t0, 0x14($t7) # maspsx-keep\n"
                    "lw $t1, 0x18($t7) # maspsx-keep\n"
                    "lw $t2, 0x1C($t7) # maspsx-keep\n"
                    "ctc2 $t0, $5 # maspsx-keep\n"
                    "ctc2 $t1, $6 # maspsx-keep\n"
                    "ctc2 $t2, $7 # maspsx-keep\n"
                    "jr $ra # maspsx-keep\n"
                    "nop # maspsx-keep\n")

/* libgte.h cannot be included in this unit (its SetFogNear prototype
 * conflicts with the local one), so the GTE matrix type is defined here. */
typedef struct {
    short m[3][3];
    long t[3];
} MATRIX;

void ReadRotMatrix(MATRIX *m) {
    __asm__("cfc2 $t0, $0\n\t"
            "cfc2 $t1, $1\n\t"
            "cfc2 $t2, $2\n\t"
            "cfc2 $t3, $3\n\t"
            "cfc2 $t4, $4\n\t"
            "sw $t0, 0($a0)\n\t"
            "sw $t1, 4($a0)\n\t"
            "sw $t2, 8($a0)\n\t"
            "sw $t3, 12($a0)\n\t"
            "sw $t4, 16($a0)\n\t"
            "cfc2 $t0, $5\n\t"
            "cfc2 $t1, $6\n\t"
            "cfc2 $t2, $7\n\t"
            "sw $t0, 20($a0)\n\t"
            "sw $t1, 24($a0)\n\t"
            "sw $t2, 28($a0)");
}

void ReadLightMatrix(MATRIX *m) {
    __asm__("cfc2 $t0, $8\n\t"
            "cfc2 $t1, $9\n\t"
            "cfc2 $t2, $10\n\t"
            "cfc2 $t3, $11\n\t"
            "cfc2 $t4, $12\n\t"
            "sw $t0, 0($a0)\n\t"
            "sw $t1, 4($a0)\n\t"
            "sw $t2, 8($a0)\n\t"
            "sw $t3, 12($a0)\n\t"
            "sw $t4, 16($a0)\n\t"
            "cfc2 $t0, $13\n\t"
            "cfc2 $t1, $14\n\t"
            "cfc2 $t2, $15\n\t"
            "sw $t0, 20($a0)\n\t"
            "sw $t1, 24($a0)\n\t"
            "sw $t2, 28($a0)");
}

/* The three nops after the delay slot are retail's padding before
 * MulMatrix2; they belong to this function's footprint. */
ASM_FUNC(ReadColorMatrix, "    cfc2 $t0, $16 # maspsx-keep\n"
                          "    cfc2 $t1, $17 # maspsx-keep\n"
                          "    cfc2 $t2, $18 # maspsx-keep\n"
                          "    cfc2 $t3, $19 # maspsx-keep\n"
                          "    cfc2 $t4, $20 # maspsx-keep\n"
                          "    sw $t0, 0($a0) # maspsx-keep\n"
                          "    sw $t1, 4($a0) # maspsx-keep\n"
                          "    sw $t2, 8($a0) # maspsx-keep\n"
                          "    sw $t3, 12($a0) # maspsx-keep\n"
                          "    sw $t4, 16($a0) # maspsx-keep\n"
                          "    cfc2 $t0, $21 # maspsx-keep\n"
                          "    cfc2 $t1, $22 # maspsx-keep\n"
                          "    cfc2 $t2, $23 # maspsx-keep\n"
                          "    sw $t0, 20($a0) # maspsx-keep\n"
                          "    sw $t1, 24($a0) # maspsx-keep\n"
                          "    sw $t2, 28($a0) # maspsx-keep\n"
                          "    jr $ra # maspsx-keep\n"
                          "    nop # maspsx-keep\n"
                          "    nop # maspsx-keep\n"
                          "    nop # maspsx-keep\n"
                          "    nop # maspsx-keep\n")

ASM_FUNC(MulMatrix2, "    lw $t0, 0x0($a0) # maspsx-keep\n"
                     "    lw $t1, 0x4($a0) # maspsx-keep\n"
                     "    lw $t2, 0x8($a0) # maspsx-keep\n"
                     "    lw $t3, 0xC($a0) # maspsx-keep\n"
                     "    lw $t4, 0x10($a0) # maspsx-keep\n"
                     "    ctc2 $t0, $0 # maspsx-keep\n"
                     "    ctc2 $t1, $1 # maspsx-keep\n"
                     "    ctc2 $t2, $2 # maspsx-keep\n"
                     "    ctc2 $t3, $3 # maspsx-keep\n"
                     "    ctc2 $t4, $4 # maspsx-keep\n"
                     "    lhu $t0, 0x0($a1) # maspsx-keep\n"
                     "    lw $t1, 0x4($a1) # maspsx-keep\n"
                     "    lw $t2, 0xC($a1) # maspsx-keep\n"
                     "    lui $at, 0xFFFF # maspsx-keep\n"
                     "    and $t1, $t1, $at # maspsx-keep\n"
                     "    or $t0, $t0, $t1 # maspsx-keep\n"
                     "    mtc2 $t0, $0 # maspsx-keep\n"
                     "    mtc2 $t2, $1 # maspsx-keep\n"
                     "    nop # maspsx-keep\n"
                     "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                     "    lhu $t0, 0x2($a1) # maspsx-keep\n"
                     "    lw $t1, 0x8($a1) # maspsx-keep\n"
                     "    lh $t2, 0xE($a1) # maspsx-keep\n"
                     "    sll $t1, $t1, 16 # maspsx-keep\n"
                     "    or $t0, $t0, $t1 # maspsx-keep\n"
                     "    mfc2 $t3, $9 # maspsx-keep\n"
                     "    mfc2 $t4, $10 # maspsx-keep\n"
                     "    mfc2 $t5, $11 # maspsx-keep\n"
                     "    mtc2 $t0, $0 # maspsx-keep\n"
                     "    mtc2 $t2, $1 # maspsx-keep\n"
                     "    nop # maspsx-keep\n"
                     "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                     "    lhu $t0, 0x4($a1) # maspsx-keep\n"
                     "    lw $t1, 0x8($a1) # maspsx-keep\n"
                     "    lw $t2, 0x10($a1) # maspsx-keep\n"
                     "    lui $at, 0xFFFF # maspsx-keep\n"
                     "    and $t1, $t1, $at # maspsx-keep\n"
                     "    or $t0, $t0, $t1 # maspsx-keep\n"
                     "    mfc2 $t6, $9 # maspsx-keep\n"
                     "    mfc2 $t7, $10 # maspsx-keep\n"
                     "    mfc2 $t8, $11 # maspsx-keep\n"
                     "    mtc2 $t0, $0 # maspsx-keep\n"
                     "    mtc2 $t2, $1 # maspsx-keep\n"
                     "    nop # maspsx-keep\n"
                     "    mvmva 1, 0, 0, 3, 0 # maspsx-keep\n"
                     "    andi $t3, $t3, 0xFFFF # maspsx-keep\n"
                     "    sll $t6, $t6, 16 # maspsx-keep\n"
                     "    or $t6, $t6, $t3 # maspsx-keep\n"
                     "    sw $t6, 0x0($a1) # maspsx-keep\n"
                     "    andi $t5, $t5, 0xFFFF # maspsx-keep\n"
                     "    sll $t8, $t8, 16 # maspsx-keep\n"
                     "    or $t8, $t8, $t5 # maspsx-keep\n"
                     "    sw $t8, 0xC($a1) # maspsx-keep\n"
                     "    mfc2 $t0, $9 # maspsx-keep\n"
                     "    mfc2 $t1, $10 # maspsx-keep\n"
                     "    andi $t0, $t0, 0xFFFF # maspsx-keep\n"
                     "    sll $t4, $t4, 16 # maspsx-keep\n"
                     "    or $t0, $t0, $t4 # maspsx-keep\n"
                     "    sw $t0, 0x4($a1) # maspsx-keep\n"
                     "    andi $t7, $t7, 0xFFFF # maspsx-keep\n"
                     "    sll $t1, $t1, 16 # maspsx-keep\n"
                     "    or $t1, $t1, $t7 # maspsx-keep\n"
                     "    sw $t1, 0x8($a1) # maspsx-keep\n"
                     "    swc2 $11, 0x10($a1) # maspsx-keep\n"
                     "    addu $v0, $a1, $zero # maspsx-keep\n"
                     "    jr $ra # maspsx-keep\n"
                     "    nop # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

ASM_FUNC(TransMatrix, "    lw $t0, 0x0($a1) # maspsx-keep\n"
                      "    lw $t1, 0x4($a1) # maspsx-keep\n"
                      "    lw $t2, 0x8($a1) # maspsx-keep\n"
                      "    sw $t0, 0x14($a0) # maspsx-keep\n"
                      "    sw $t1, 0x18($a0) # maspsx-keep\n"
                      "    sw $t2, 0x1C($a0) # maspsx-keep\n"
                      "    addu $v0, $a0, $zero # maspsx-keep\n"
                      "    jr $ra # maspsx-keep\n"
                      "    nop # maspsx-keep\n"
                      "    nop # maspsx-keep\n"
                      "    nop # maspsx-keep\n"
                      "    nop # maspsx-keep\n")

void SetRotMatrix(MATRIX *m) {
    __asm__("lw $t0, 0($a0)\n\t"
            "lw $t1, 4($a0)\n\t"
            "lw $t2, 8($a0)\n\t"
            "lw $t3, 12($a0)\n\t"
            "lw $t4, 16($a0)\n\t"
            "ctc2 $t0, $0\n\t"
            "ctc2 $t1, $1\n\t"
            "ctc2 $t2, $2\n\t"
            "ctc2 $t3, $3\n\t"
            "ctc2 $t4, $4");
}

void SetTransMatrix(MATRIX *m) {
    __asm__("lw $t0, 20($a0)\n\t"
            "lw $t1, 24($a0)\n\t"
            "lw $t2, 28($a0)\n\t"
            "ctc2 $t0, $5\n\t"
            "ctc2 $t1, $6\n\t"
            "ctc2 $t2, $7");
}

/* libgte.h cannot be included in this unit (its SetFogNear prototype
 * conflicts with the local one), so the GTE colour type is defined here. */
typedef struct {
    u8 r, g, b;
    u8 cd;
} CVECTOR;

void SetVertex0(SVECTOR *v0) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)");
}

void SetVertex1(SVECTOR *v1) {
    __asm__ volatile("lwc2 $2, 0($a0)\n\t"
                     "lwc2 $3, 4($a0)");
}

void SetVertex2(SVECTOR *v2) {
    __asm__ volatile("lwc2 $4, 0($a0)\n\t"
                     "lwc2 $5, 4($a0)");
}

void SetVertexTri(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "lwc2 $2, 0($a1)\n\t"
                     "lwc2 $3, 4($a1)\n\t"
                     "lwc2 $4, 0($a2)\n\t"
                     "lwc2 $5, 4($a2)");
}

void SetRGBfifo(CVECTOR *r0, CVECTOR *r1, CVECTOR *r2) {
    __asm__ volatile("lwc2 $20, 0($a0)\n\t"
                     "lwc2 $21, 0($a1)\n\t"
                     "lwc2 $22, 0($a2)");
}

void SetIR123(long r1, long r2, long r3) {
    __asm__("mtc2 $a0, $9\n\t"
            "mtc2 $a1, $10\n\t"
            "mtc2 $a2, $11");
}

void SetIR0(long r0) {
    __asm__("mtc2 $a0, $8");
}

void SetSZfifo3(long sz1, long sz2, long sz3) {
    __asm__("mtc2 $a0, $17\n\t"
            "mtc2 $a1, $18\n\t"
            "mtc2 $a2, $19");
}

void SetSZfifo4(long sz0, long sz1, long sz2, long sz3) {
    __asm__("mtc2 $a0, $16\n\t"
            "mtc2 $a1, $17\n\t"
            "mtc2 $a2, $18\n\t"
            "mtc2 $a3, $19");
}

void SetSXSYfifo(long sxy0, long sxy1, long sxy2) {
    __asm__("mtc2 $a0, $12\n\t"
            "mtc2 $a1, $13\n\t"
            "mtc2 $a2, $14");
}

/* Each word packs two 16-bit rotation coefficients: R11R12, R22R23, R33. */
void SetRii(long r11r12, long r22r23, long r33) {
    __asm__("ctc2 $a0, $0\n\t"
            "ctc2 $a1, $2\n\t"
            "ctc2 $a2, $4");
}

void SetMAC123(long mac1, long mac2, long mac3) {
    __asm__("mtc2 $a0, $25\n\t"
            "mtc2 $a1, $26\n\t"
            "mtc2 $a2, $27");
}

void SetData32(long d) {
    __asm__("mtc2 $a0, $30");
}

void SetDQA(long dqa) {
    __asm__("ctc2 $a0, $27");
}

void SetDQB(long dqb) {
    __asm__("ctc2 $a0, $28");
}

void SetBackColor(long rbk, long gbk, long bbk) {
    __asm__("sll $a0, $a0, 4\n\t"
            "sll $a1, $a1, 4\n\t"
            "sll $a2, $a2, 4\n\t"
            "ctc2 $a0, $13\n\t"
            "ctc2 $a1, $14\n\t"
            "ctc2 $a2, $15");
}

void SetFarColor(long rfc, long gfc, long bfc) {
    __asm__("sll $a0, $a0, 4\n\t"
            "sll $a1, $a1, 4\n\t"
            "sll $a2, $a2, 4\n\t"
            "ctc2 $a0, $21\n\t"
            "ctc2 $a1, $22\n\t"
            "ctc2 $a2, $23");
}

ASM_FUNC(SetGeomOffset, "    sll $a0, $a0, 16 # maspsx-keep\n"
                        "    sll $a1, $a1, 16 # maspsx-keep\n"
                        "    ctc2 $a0, $24 # maspsx-keep\n"
                        "    ctc2 $a1, $25 # maspsx-keep\n"
                        "    jr $ra # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    nop # maspsx-keep\n")

ASM_FUNC(SetGeomScreen, "    ctc2 $a0, $26 # maspsx-keep\n"
                        "    jr $ra # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    nop # maspsx-keep\n")

/* Multiplies the colour vector by the GTE colour matrix: IR1-3 in from
 * v0, saturated IR1-3 out to v1; the nop is the load latency. */
void LightColor(VECTOR *v0, VECTOR *v1) {
    __asm__ volatile("lwc2 $9, 0($a0)\n\t"
                     "lwc2 $10, 4($a0)\n\t"
                     "lwc2 $11, 8($a0)\n\t"
                     "nop\n\t"
                     "mvmva 1, 2, 3, 1, 1\n\t"
                     "swc2 $9, 0($a1)\n\t"
                     "swc2 $10, 4($a1)\n\t"
                     "swc2 $11, 8($a1)");
}

/* Depth-cues the light-source colour: IR1-3 from v0, the background
 * colour in $6, the interpolation factor dq in IR0; dpcl writes the
 * packed RGB result ($22) to out. */
void DpqColorLight(VECTOR *v0, CVECTOR *bk, long dq, CVECTOR *out) {
    __asm__ volatile("lwc2 $9, 0($a0)\n\t"
                     "lwc2 $10, 4($a0)\n\t"
                     "lwc2 $11, 8($a0)\n\t"
                     "lwc2 $6, 0($a1)\n\t"
                     "mtc2 $a2, $8\n\t"
                     "nop\n\t"
                     "dpcl\n\t"
                     "swc2 $22, 0($a3)");
}

/* Depth-cues the three colours c0-c2 (dpct) against the depth-cue
 * factor dq loaded into IR0; c2 is also loaded into the current colour
 * register. The three output pointers arrive on the stack and the
 * cued colours are stored to them from the colour FIFO. */
void DpqColor3(CVECTOR *c0, CVECTOR *c1, CVECTOR *c2, long dq, CVECTOR *r0,
               CVECTOR *r1, CVECTOR *r2) {
    __asm__ volatile("lwc2 $20, 0($a0)\n\t"
                     "lwc2 $21, 0($a1)\n\t"
                     "lwc2 $22, 0($a2)\n\t"
                     "lwc2 $6, 0($a2)\n\t"
                     "mtc2 $a3, $8\n\t"
                     "nop\n\t"
                     "dpct\n\t"
                     "lw $t0, 0x10($sp)\n\t"
                     "lw $t1, 0x14($sp)\n\t"
                     "lw $t2, 0x18($sp)\n\t"
                     "swc2 $20, 0($t0)\n\t"
                     "swc2 $21, 0($t1)\n\t"
                     "swc2 $22, 0($t2)");
}

/* Loads the 3-word vector into IR1-3 and t into IR0, runs the GTE
 * interpolation, and stores the packed RGB result ($22). */
void Intpl(long *v0, long t, long *out) {
    __asm__ volatile("lwc2 $9, 0($a0)\n\t"
                     "lwc2 $10, 4($a0)\n\t"
                     "lwc2 $11, 8($a0)\n\t"
                     "mtc2 $a1, $8\n\t"
                     "nop\n\t"
                     "intpl\n\t"
                     "swc2 $22, 0($a2)");
}

VECTOR *Square12(VECTOR *v0, VECTOR *v1) {
    __asm__ volatile("lwc2 $9, 0($a0)\n\t"
                     "lwc2 $10, 4($a0)\n\t"
                     "lwc2 $11, 8($a0)\n\t"
                     "nop\n\t"
                     "sqr 1\n\t"
                     "swc2 $25, 0($a1)\n\t"
                     "swc2 $26, 4($a1)\n\t"
                     "swc2 $27, 8($a1)");
    return v1;
}

VECTOR *Square0(VECTOR *v0, VECTOR *v1) {
    __asm__ volatile("lwc2 $9, 0($a0)\n\t"
                     "lwc2 $10, 4($a0)\n\t"
                     "lwc2 $11, 8($a0)\n\t"
                     "nop\n\t"
                     "sqr 0\n\t"
                     "swc2 $25, 0($a1)\n\t"
                     "swc2 $26, 4($a1)\n\t"
                     "swc2 $27, 8($a1)");
    return v1;
}

/* Loads the three depths into the SZ fifo and returns the GTE average
 * (OTZ) in $v0; avsz3 needs the nop stall after the fifo loads. */
long AverageZ3(long sz1, long sz2, long sz3) {
    __asm__ volatile("mtc2 $a0, $17\n\t"
                     "mtc2 $a1, $18\n\t"
                     "mtc2 $a2, $19\n\t"
                     "nop\n\t"
                     "avsz3\n\t"
                     "mfc2 $v0, $7");
}

/* Same over all four SZ fifo slots; avsz4 averages sz0-sz3 into OTZ. */
long AverageZ4(long sz0, long sz1, long sz2, long sz3) {
    __asm__ volatile("mtc2 $a0, $16\n\t"
                     "mtc2 $a1, $17\n\t"
                     "mtc2 $a2, $18\n\t"
                     "mtc2 $a3, $19\n\t"
                     "nop\n\t"
                     "avsz4\n\t"
                     "mfc2 $v0, $7");
}

/* Outer product of v0 and v1 into v2: saves the rotation matrix
 * diagonal, loads v0 into it and v1 into IR1-3, runs `op`, then restores
 * the diagonal. The sf bit (12 or 0) is the fraction shift. */
VECTOR *OuterProduct12(VECTOR *v0, VECTOR *v1, VECTOR *v2) {
    __asm__ volatile("cfc2 $t5, $0\n\t"
                     "cfc2 $t6, $2\n\t"
                     "cfc2 $t7, $4\n\t"
                     "lw $t0, 0($a0)\n\t"
                     "lw $t1, 4($a0)\n\t"
                     "lw $t2, 8($a0)\n\t"
                     "ctc2 $t0, $0\n\t"
                     "ctc2 $t1, $2\n\t"
                     "ctc2 $t2, $4\n\t"
                     "lwc2 $11, 8($a1)\n\t"
                     "lwc2 $9, 0($a1)\n\t"
                     "lwc2 $10, 4($a1)\n\t"
                     "nop\n\t"
                     "op 1\n\t"
                     "swc2 $25, 0($a2)\n\t"
                     "swc2 $26, 4($a2)\n\t"
                     "swc2 $27, 8($a2)\n\t"
                     "ctc2 $t5, $0\n\t"
                     "ctc2 $t6, $2\n\t"
                     "ctc2 $t7, $4");
}

VECTOR *OuterProduct0(VECTOR *v0, VECTOR *v1, VECTOR *v2) {
    __asm__ volatile("cfc2 $t5, $0\n\t"
                     "cfc2 $t6, $2\n\t"
                     "cfc2 $t7, $4\n\t"
                     "lw $t0, 0($a0)\n\t"
                     "lw $t1, 4($a0)\n\t"
                     "lw $t2, 8($a0)\n\t"
                     "ctc2 $t0, $0\n\t"
                     "ctc2 $t1, $2\n\t"
                     "ctc2 $t2, $4\n\t"
                     "lwc2 $11, 8($a1)\n\t"
                     "lwc2 $9, 0($a1)\n\t"
                     "lwc2 $10, 4($a1)\n\t"
                     "nop\n\t"
                     "op 0\n\t"
                     "swc2 $25, 0($a2)\n\t"
                     "swc2 $26, 4($a2)\n\t"
                     "swc2 $27, 8($a2)\n\t"
                     "ctc2 $t5, $0\n\t"
                     "ctc2 $t6, $2\n\t"
                     "ctc2 $t7, $4");
}

ASM_FUNC(Lzc, "    mtc2 $a0, $30 # maspsx-keep\n"
              "    nop # maspsx-keep\n"
              "    nop # maspsx-keep\n"
              "    mfc2 $v0, $31 # maspsx-keep\n"
              "    jr $ra # maspsx-keep\n"
              "    nop # maspsx-keep\n"
              "    nop # maspsx-keep\n")

ASM_FUNC(RotTrans, "    lwc2 $0, 0($a0) # maspsx-keep\n"
                   "    lwc2 $1, 4($a0) # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    mvmva 1, 0, 0, 0, 0 # maspsx-keep\n"
                   "    swc2 $25, 0($a1) # maspsx-keep\n"
                   "    swc2 $26, 4($a1) # maspsx-keep\n"
                   "    swc2 $27, 8($a1) # maspsx-keep\n"
                   "    cfc2 $v0, $31 # maspsx-keep\n"
                   "    jr $ra # maspsx-keep\n"
                   "    sw $v0, 0($a2) # maspsx-keep\n"
                   "    nop # maspsx-keep\n"
                   "    nop # maspsx-keep\n")

/* The _nom variants run the GTE command bare, without the result
 * readback the macro wrappers add. */
void RotTransPers_nom(SVECTOR *v0) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "nop\n\t"
                     "rtps");
}

void RotTransPers3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "lwc2 $2, 0($a1)\n\t"
                     "lwc2 $3, 4($a1)\n\t"
                     "lwc2 $4, 0($a2)\n\t"
                     "lwc2 $5, 4($a2)\n\t"
                     "nop\n\t"
                     "rtpt");
}

void RotTrans_nom(SVECTOR *v0) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "nop\n\t"
                     "mvmva 1, 0, 0, 0, 0");
}

/* Rotates the first three vertices with rtpt and the fourth with rtps.
 * Returns the flag ($v0); the third vertex's screen xy is left in $v1. */
long RotTransPers4_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, SVECTOR *v3) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "lwc2 $2, 0($a1)\n\t"
                     "lwc2 $3, 4($a1)\n\t"
                     "lwc2 $4, 0($a2)\n\t"
                     "lwc2 $5, 4($a2)\n\t"
                     "nop\n\t"
                     "rtpt\n\t"
                     "cfc2 $v0, $31\n\t"
                     "mfc2 $v1, $12\n\t"
                     "lwc2 $0, 0($a3)\n\t"
                     "lwc2 $1, 4($a3)\n\t"
                     "nop\n\t"
                     "rtps");
}

long RotAverage3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "lwc2 $2, 0($a1)\n\t"
                     "lwc2 $3, 4($a1)\n\t"
                     "lwc2 $4, 0($a2)\n\t"
                     "lwc2 $5, 4($a2)\n\t"
                     "nop\n\t"
                     "rtpt\n\t"
                     "cfc2 $v0, $31\n\t"
                     "avsz3");
}

long RotNclip3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "lwc2 $2, 0($a1)\n\t"
                     "lwc2 $3, 4($a1)\n\t"
                     "lwc2 $4, 0($a2)\n\t"
                     "lwc2 $5, 4($a2)\n\t"
                     "nop\n\t"
                     "rtpt\n\t"
                     "cfc2 $v0, $31\n\t"
                     "nclip");
}

long RotAverageNclip3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "lwc2 $2, 0($a1)\n\t"
                     "lwc2 $3, 4($a1)\n\t"
                     "lwc2 $4, 0($a2)\n\t"
                     "lwc2 $5, 4($a2)\n\t"
                     "nop\n\t"
                     "rtpt\n\t"
                     "cfc2 $v0, $31\n\t"
                     "avsz3\n\t"
                     "nclip");
}

/* Transforms one vertex (rtps) with the GTE's current matrix, then
 * depth-cues the normal n0 against the base color c0 (ncds). Returns
 * the GTE flag. */
long RotColorDpq_nom(SVECTOR *v0, SVECTOR *n0, CVECTOR *c0) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "nop\n\t"
                     "rtps\n\t"
                     "cfc2 $v0, $31\n\t"
                     "lwc2 $0, 0($a1)\n\t"
                     "lwc2 $1, 4($a1)\n\t"
                     "lwc2 $6, 0($a2)\n\t"
                     "nop\n\t"
                     "ncds");
}

/* Triple form: transforms v0-v2 (rtpt), then depth-cues the normals
 * n0-n2 against the base color c0 (ncdt). The fourth through seventh
 * arguments arrive on the stack and are read from there directly. */
long RotColorDpq3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, SVECTOR *n0,
                      SVECTOR *n1, SVECTOR *n2, CVECTOR *c0) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "lwc2 $2, 0($a1)\n\t"
                     "lwc2 $3, 4($a1)\n\t"
                     "lwc2 $4, 0($a2)\n\t"
                     "lwc2 $5, 4($a2)\n\t"
                     "nop\n\t"
                     "rtpt\n\t"
                     "cfc2 $v0, $31\n\t"
                     "lwc2 $0, 0($a3)\n\t"
                     "lwc2 $1, 4($a3)\n\t"
                     "lw $t0, 0x10($sp)\n\t"
                     "nop\n\t"
                     "lwc2 $2, 0($t0)\n\t"
                     "lwc2 $3, 4($t0)\n\t"
                     "lw $t0, 0x14($sp)\n\t"
                     "nop\n\t"
                     "lwc2 $4, 0($t0)\n\t"
                     "lwc2 $5, 4($t0)\n\t"
                     "lw $t0, 0x18($sp)\n\t"
                     "nop\n\t"
                     "lwc2 $6, 0($t0)\n\t"
                     "nop\n\t"
                     "ncdt");
}

/* Triple form with depth cue: transforms v0-v2 (rtpt), averages the Z
 * values (avsz3) and computes the clipping product (nclip), then
 * depth-cues the normals n0-n2 against the base color c0 (ncdt). */
long RotAverageNclipColorDpq3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2,
                                  SVECTOR *n0, SVECTOR *n1, SVECTOR *n2,
                                  CVECTOR *c0) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "lwc2 $2, 0($a1)\n\t"
                     "lwc2 $3, 4($a1)\n\t"
                     "lwc2 $4, 0($a2)\n\t"
                     "lwc2 $5, 4($a2)\n\t"
                     "nop\n\t"
                     "rtpt\n\t"
                     "cfc2 $v0, $31\n\t"
                     "avsz3\n\t"
                     "nclip\n\t"
                     "lwc2 $0, 0($a3)\n\t"
                     "lwc2 $1, 4($a3)\n\t"
                     "lw $t0, 0x10($sp)\n\t"
                     "nop\n\t"
                     "lwc2 $2, 0($t0)\n\t"
                     "lwc2 $3, 4($t0)\n\t"
                     "lw $t0, 0x14($sp)\n\t"
                     "nop\n\t"
                     "lwc2 $4, 0($t0)\n\t"
                     "lwc2 $5, 4($t0)\n\t"
                     "lw $t0, 0x18($sp)\n\t"
                     "nop\n\t"
                     "lwc2 $6, 0($t0)\n\t"
                     "nop\n\t"
                     "ncdt");
}

/* Triple form with color calculation: transforms v0-v2 (rtpt), averages
 * the Z values (avsz3) and computes the clipping product (nclip), then
 * lights the normals n0-n2 against the base color c0 (ncct). */
long RotAverageNclipColorCol3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2,
                                  SVECTOR *n0, SVECTOR *n1, SVECTOR *n2,
                                  CVECTOR *c0) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "lwc2 $2, 0($a1)\n\t"
                     "lwc2 $3, 4($a1)\n\t"
                     "lwc2 $4, 0($a2)\n\t"
                     "lwc2 $5, 4($a2)\n\t"
                     "nop\n\t"
                     "rtpt\n\t"
                     "cfc2 $v0, $31\n\t"
                     "avsz3\n\t"
                     "nclip\n\t"
                     "lwc2 $0, 0($a3)\n\t"
                     "lwc2 $1, 4($a3)\n\t"
                     "lw $t0, 0x10($sp)\n\t"
                     "nop\n\t"
                     "lwc2 $2, 0($t0)\n\t"
                     "lwc2 $3, 4($t0)\n\t"
                     "lw $t0, 0x14($sp)\n\t"
                     "nop\n\t"
                     "lwc2 $4, 0($t0)\n\t"
                     "lwc2 $5, 4($t0)\n\t"
                     "lw $t0, 0x18($sp)\n\t"
                     "nop\n\t"
                     "lwc2 $6, 0($t0)\n\t"
                     "nop\n\t"
                     "ncct");
}

/* Normal-colour GTE veneers: load the normal(s), plus the primary
 * colour ($6) and depth-cue factor ($8, IR0) where the command wants
 * them, then run the command. The nop before each command is the GTE
 * load latency; the colours stay in the colour FIFO for the caller. */
void NormalColor_nom(SVECTOR *v0) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "nop\n\t"
                     "ncs");
}

void NormalColor3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "lwc2 $2, 0($a1)\n\t"
                     "lwc2 $3, 4($a1)\n\t"
                     "lwc2 $4, 0($a2)\n\t"
                     "lwc2 $5, 4($a2)\n\t"
                     "nop\n\t"
                     "nct");
}

void NormalColorDpq_nom(SVECTOR *v0, CVECTOR *bk, long dq) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "lwc2 $6, 0($a1)\n\t"
                     "mtc2 $a2, $8\n\t"
                     "nop\n\t"
                     "ncds");
}

/* dq is the fifth argument, reached on the stack; the veneer reads it
 * at 0x10($sp) as retail does. */
void NormalColorDpq3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, CVECTOR *bk,
                         long dq) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "lwc2 $2, 0($a1)\n\t"
                     "lwc2 $3, 4($a1)\n\t"
                     "lwc2 $4, 0($a2)\n\t"
                     "lwc2 $5, 4($a2)\n\t"
                     "lwc2 $6, 0($a3)\n\t"
                     "lwc2 $8, 0x10($sp)\n\t"
                     "nop\n\t"
                     "ncdt");
}

void NormalColorCol_nom(SVECTOR *v0, CVECTOR *col) {
    __asm__ volatile("lwc2 $0, 0($a0)\n\t"
                     "lwc2 $1, 4($a0)\n\t"
                     "lwc2 $6, 0($a1)\n\t"
                     "nop\n\t"
                     "nccs");
}

/* The trailing nop is retail's padding before RotMatrix; it belongs to
 * this function's footprint. */
ASM_FUNC(NormalColorCol3_nom, "    lwc2 $0, 0($a0) # maspsx-keep\n"
                              "    lwc2 $1, 4($a0) # maspsx-keep\n"
                              "    lwc2 $2, 0($a1) # maspsx-keep\n"
                              "    lwc2 $3, 4($a1) # maspsx-keep\n"
                              "    lwc2 $4, 0($a2) # maspsx-keep\n"
                              "    lwc2 $5, 4($a2) # maspsx-keep\n"
                              "    lwc2 $6, 0($a3) # maspsx-keep\n"
                              "    nop # maspsx-keep\n"
                              "    ncct # maspsx-keep\n"
                              "    jr $ra # maspsx-keep\n"
                              "    nop # maspsx-keep\n"
                              "    nop # maspsx-keep\n")

ASM_FUNC(RotMatrix, "lh $t7, 0x0($a0) # maspsx-keep\n"
                    "addu $v0, $a1, $zero # maspsx-keep\n"
                    "bgez $t7, .L8007DA20 # maspsx-keep\n"
                    "andi $t9, $t7, 0xFFF # maspsx-keep\n"
                    "negu $t7, $t7 # maspsx-keep\n"
                    "bgez $t7, .L8007D9F8 # maspsx-keep\n"
                    "andi $t7, $t7, 0xFFF # maspsx-keep\n"
                    ".L8007D9F8: # maspsx-keep\n"
                    "sll $t8, $t7, 2 # maspsx-keep\n"
                    "lui $t9, %hi(D_8009E070) # maspsx-keep\n"
                    "addu $t9, $t9, $t8 # maspsx-keep\n"
                    "lw $t9, %lo(D_8009E070)($t9) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "sll $t8, $t9, 16 # maspsx-keep\n"
                    "sra $t8, $t8, 16 # maspsx-keep\n"
                    "negu $t3, $t8 # maspsx-keep\n"
                    "j .L8007DA40 # maspsx-keep\n"
                    "sra $t0, $t9, 16 # maspsx-keep\n"
                    ".L8007DA20: # maspsx-keep\n"
                    "sll $t8, $t9, 2 # maspsx-keep\n"
                    "lui $t9, %hi(D_8009E070) # maspsx-keep\n"
                    "addu $t9, $t9, $t8 # maspsx-keep\n"
                    "lw $t9, %lo(D_8009E070)($t9) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "sll $t8, $t9, 16 # maspsx-keep\n"
                    "sra $t3, $t8, 16 # maspsx-keep\n"
                    "sra $t0, $t9, 16 # maspsx-keep\n"
                    ".L8007DA40: # maspsx-keep\n"
                    "lh $t7, 0x2($a0) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "bgez $t7, .L8007DA84 # maspsx-keep\n"
                    "andi $t9, $t7, 0xFFF # maspsx-keep\n"
                    "negu $t7, $t7 # maspsx-keep\n"
                    "bgez $t7, .L8007DA5C # maspsx-keep\n"
                    "andi $t7, $t7, 0xFFF # maspsx-keep\n"
                    ".L8007DA5C: # maspsx-keep\n"
                    "sll $t8, $t7, 2 # maspsx-keep\n"
                    "lui $t9, %hi(D_8009E070) # maspsx-keep\n"
                    "addu $t9, $t9, $t8 # maspsx-keep\n"
                    "lw $t9, %lo(D_8009E070)($t9) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "sll $t4, $t9, 16 # maspsx-keep\n"
                    "sra $t4, $t4, 16 # maspsx-keep\n"
                    "negu $t6, $t4 # maspsx-keep\n"
                    "j .L8007DAA8 # maspsx-keep\n"
                    "sra $t1, $t9, 16 # maspsx-keep\n"
                    ".L8007DA84: # maspsx-keep\n"
                    "sll $t8, $t9, 2 # maspsx-keep\n"
                    "lui $t9, %hi(D_8009E070) # maspsx-keep\n"
                    "addu $t9, $t9, $t8 # maspsx-keep\n"
                    "lw $t9, %lo(D_8009E070)($t9) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "sll $t6, $t9, 16 # maspsx-keep\n"
                    "sra $t6, $t6, 16 # maspsx-keep\n"
                    "negu $t4, $t6 # maspsx-keep\n"
                    "sra $t1, $t9, 16 # maspsx-keep\n"
                    ".L8007DAA8: # maspsx-keep\n"
                    "multu $t1, $t3 # maspsx-keep\n"
                    "lh $t7, 0x4($a0) # maspsx-keep\n"
                    "sh $t6, 0x4($a1) # maspsx-keep\n"
                    "mflo $t8 # maspsx-keep\n"
                    "negu $t9, $t8 # maspsx-keep\n"
                    "sra $t6, $t9, 12 # maspsx-keep\n"
                    "multu $t1, $t0 # maspsx-keep\n"
                    "sh $t6, 0xA($a1) # maspsx-keep\n"
                    "bgez $t7, .L8007DB10 # maspsx-keep\n"
                    "andi $t9, $t7, 0xFFF # maspsx-keep\n"
                    "mflo $t8 # maspsx-keep\n"
                    "sra $t6, $t8, 12 # maspsx-keep\n"
                    "sh $t6, 0x10($a1) # maspsx-keep\n"
                    "negu $t7, $t7 # maspsx-keep\n"
                    "bgez $t7, .L8007DAE8 # maspsx-keep\n"
                    "andi $t7, $t7, 0xFFF # maspsx-keep\n"
                    ".L8007DAE8: # maspsx-keep\n"
                    "sll $t8, $t7, 2 # maspsx-keep\n"
                    "lui $t9, %hi(D_8009E070) # maspsx-keep\n"
                    "addu $t9, $t9, $t8 # maspsx-keep\n"
                    "lw $t9, %lo(D_8009E070)($t9) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "sll $t8, $t9, 16 # maspsx-keep\n"
                    "sra $t8, $t8, 16 # maspsx-keep\n"
                    "negu $t5, $t8 # maspsx-keep\n"
                    "j .L8007DB3C # maspsx-keep\n"
                    "sra $t2, $t9, 16 # maspsx-keep\n"
                    ".L8007DB10: # maspsx-keep\n"
                    "mflo $t7 # maspsx-keep\n"
                    "sra $t6, $t7, 12 # maspsx-keep\n"
                    "sh $t6, 0x10($a1) # maspsx-keep\n"
                    "sll $t8, $t9, 2 # maspsx-keep\n"
                    "lui $t9, %hi(D_8009E070) # maspsx-keep\n"
                    "addu $t9, $t9, $t8 # maspsx-keep\n"
                    "lw $t9, %lo(D_8009E070)($t9) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "sll $t8, $t9, 16 # maspsx-keep\n"
                    "sra $t5, $t8, 16 # maspsx-keep\n"
                    "sra $t2, $t9, 16 # maspsx-keep\n"
                    ".L8007DB3C: # maspsx-keep\n"
                    "multu $t2, $t1 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "mflo $t7 # maspsx-keep\n"
                    "sra $t6, $t7, 12 # maspsx-keep\n"
                    "sh $t6, 0x0($a1) # maspsx-keep\n"
                    "multu $t5, $t1 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "mflo $t7 # maspsx-keep\n"
                    "negu $t6, $t7 # maspsx-keep\n"
                    "sra $t7, $t6, 12 # maspsx-keep\n"
                    "multu $t2, $t4 # maspsx-keep\n"
                    "sh $t7, 0x2($a1) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "mflo $t7 # maspsx-keep\n"
                    "sra $t8, $t7, 12 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "multu $t8, $t3 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "mflo $t7 # maspsx-keep\n"
                    "sra $t6, $t7, 12 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "multu $t5, $t0 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "mflo $t7 # maspsx-keep\n"
                    "sra $t9, $t7, 12 # maspsx-keep\n"
                    "subu $t7, $t9, $t6 # maspsx-keep\n"
                    "multu $t8, $t0 # maspsx-keep\n"
                    "sh $t7, 0x6($a1) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "mflo $t6 # maspsx-keep\n"
                    "sra $t7, $t6, 12 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "multu $t5, $t3 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "mflo $t6 # maspsx-keep\n"
                    "sra $t9, $t6, 12 # maspsx-keep\n"
                    "addu $t6, $t9, $t7 # maspsx-keep\n"
                    "multu $t5, $t4 # maspsx-keep\n"
                    "sh $t6, 0xC($a1) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "mflo $t7 # maspsx-keep\n"
                    "sra $t8, $t7, 12 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "multu $t8, $t3 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "mflo $t7 # maspsx-keep\n"
                    "sra $t6, $t7, 12 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "multu $t2, $t0 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "mflo $t7 # maspsx-keep\n"
                    "sra $t9, $t7, 12 # maspsx-keep\n"
                    "addu $t7, $t9, $t6 # maspsx-keep\n"
                    "multu $t8, $t0 # maspsx-keep\n"
                    "sh $t7, 0x8($a1) # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "mflo $t6 # maspsx-keep\n"
                    "sra $t7, $t6, 12 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "multu $t2, $t3 # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "mflo $t6 # maspsx-keep\n"
                    "sra $t9, $t6, 12 # maspsx-keep\n"
                    "subu $t6, $t9, $t7 # maspsx-keep\n"
                    "sh $t6, 0xE($a1) # maspsx-keep\n"
                    "jr $ra # maspsx-keep\n"
                    "nop # maspsx-keep\n"
                    "nop # maspsx-keep\n")

ASM_FUNC(_patch_gte, "lui $at, %hi(D_800A3524) # maspsx-keep\n"
                     "sw $ra, %lo(D_800A3524)($at) # maspsx-keep\n"
                     "jal EnterCriticalSection # maspsx-keep\n"
                     "nop # maspsx-keep\n"
                     "addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                     "jalr $t2 # maspsx-keep\n"
                     "addiu $t1, $zero, 0x56 # maspsx-keep\n"
                     "lui $t2, %hi(D_8007DCD4) # maspsx-keep\n"
                     "lui $t1, %hi(FlushCache) # maspsx-keep\n"
                     "lw $v0, 0x18($v0) # maspsx-keep\n"
                     "addiu $t2, $t2, %lo(D_8007DCD4) # maspsx-keep\n"
                     "addiu $t1, $t1, %lo(FlushCache) # maspsx-keep\n"
                     ".L8007DC9C: # maspsx-keep\n"
                     "lw $v1, 0x0($t2) # maspsx-keep\n"
                     "addiu $t2, $t2, 0x4 # maspsx-keep\n"
                     "addiu $v0, $v0, 0x4 # maspsx-keep\n"
                     "bne $t2, $t1, .L8007DC9C # maspsx-keep\n"
                     "sw $v1, -0x4($v0) # maspsx-keep\n"
                     "jal FlushCache # maspsx-keep\n"
                     "nop # maspsx-keep\n"
                     "jal ExitCriticalSection # maspsx-keep\n"
                     "nop # maspsx-keep\n"
                     "lui $ra, %hi(D_800A3524) # maspsx-keep\n"
                     "lw $ra, %lo(D_800A3524)($ra) # maspsx-keep\n"
                     "nop # maspsx-keep\n"
                     "jr $ra # maspsx-keep\n"
                     "nop # maspsx-keep\n"
                     ".globl D_8007DCD4 # maspsx-keep\n"
                     "D_8007DCD4: # maspsx-keep\n"
                     "nop # maspsx-keep\n"
                     "nop # maspsx-keep\n")

ASM_FUNC(func_8007DCDC, "    addiu $k0, $zero, 0x100 # maspsx-keep\n"
                        "    lw $k0, 0x8($k0) # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    lw $k0, 0x0($k0) # maspsx-keep\n"
                        "    nop # maspsx-keep\n"
                        "    addi $k0, $k0, 0x8 # maspsx-keep\n"
                        "    sw $at, 0x4($k0) # maspsx-keep\n"
                        "    sw $v0, 0x8($k0) # maspsx-keep\n"
                        "    sw $v1, 0xC($k0) # maspsx-keep\n"
                        "    sw $ra, 0x7C($k0) # maspsx-keep\n"
                        "    mfc0 $v0, $13 # maspsx-keep\n"
                        "    nop # maspsx-keep\n")

ASM_FUNC(FlushCache, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                     "    jr $t2 # maspsx-keep\n"
                     "    addiu $t1, $zero, 0x44 # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

extern s32 SpuSetMute(s32 on_off);

void SsSetMute(u8 on_off) {
    if (on_off != 0) {
        if (on_off == 1) {
            SpuSetMute(1);
        }
    } else {
        SpuSetMute(0);
    }
}

extern long SpuSetCommonAttr(SpuCommonAttr *attr);

void SsSetMVol(short voll, short volr) {
    SpuCommonAttr attr;
    attr.mask = SPU_COMMON_MVOLL | SPU_COMMON_MVOLR;
    attr.mvol.left = 0x81 * voll;
    attr.mvol.right = 0x81 * volr;
    SpuSetCommonAttr(&attr);
}

extern long SpuSetCommonAttr(SpuCommonAttr *attr);

void SsSetSerialAttr(char arg0, char arg1, char arg2) {
    SpuCommonAttr attr;
    if (arg0 == 0) {
        if (arg1 == 0) {
            attr.mask = SPU_COMMON_CDMIX;
            attr.cd.mix = arg2;
        }
        if (arg1 == 1) {
            attr.mask = SPU_COMMON_CDREV;
            attr.cd.reverb = arg2;
        }
    }
    if (arg0 == 1) {
        if (arg1 == 0) {
            attr.mask = SPU_COMMON_EXTMIX;
            attr.ext.mix = arg2;
        }
        if (arg1 == 1) {
            attr.mask = SPU_COMMON_EXTREV;
            attr.ext.reverb = arg2;
        }
    }
    SpuSetCommonAttr(&attr);
}

extern long SpuSetCommonAttr(SpuCommonAttr *attr);

void SsSetSerialVol(short channel, short voll, short volr) {
    SpuCommonAttr attr;
    char s_num;

    s_num = channel;
    if (s_num == 0) {
        attr.mask = 0xC0;
        if (voll > 0x7F) {
            voll = 0x7F;
        }
        if (volr > 0x7F) {
            volr = 0x7F;
        }
        attr.cd.volume.left = voll * 258;
        attr.cd.volume.right = volr * 258;
    }
    if (s_num == 1) {
        attr.mask = 0xC00;
        if (voll > 0x7F) {
            voll = 0x7F;
        }
        if (volr > 0x7F) {
            volr = 0x7F;
        }
        attr.ext.volume.left = voll * 258;
        attr.ext.volume.right = volr * 258;
    }
    SpuSetCommonAttr(&attr);
}

extern char D_8009084C[];
extern char D_80090864[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_8009084C);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090864);
s32 _SsReadDeltaValue(s16, s16);

s16 _SsInitSoundSeq(s16 arg0, s16 vab_id, u8 *addr) {
    struct SeqStruct *score = &D_800BDE3C[arg0][0];
    s32 channel;

    score->unk4C = vab_id;
    score->unk4A = 0;
    score->unk13 = 0;
    score->unk14 = 0;
    score->unk29 = 0;
    score->unk15 = 0;
    score->unk16 = 0;
    score->unk2A = 0;
    score->channel = 0;
    score->unk7C = 0;
    score->unk80 = 0;
    score->unk84 = 0;
    score->unk72 = 0U;
    score->loopIndex = 0;
    score->unk2B = 0;
    score->deltaValue = 0;
    score->unk27 = 0;
    score->unk28 = 0;
    score->unk10 = 0;
    score->eventStatus = 0;
    score->unkA8 = 0x7F;
    score->unkAA = 0;
    for (channel = 0; channel < 16; channel++) {
        score->programs[channel] = channel;
        score->panpot[channel] = 0x40;
        score->vol[channel] = 0x7f;
    }
    score->unk6E = 1;
    score->readPos = addr;
    if ((*score->readPos == 'S') || (*score->readPos == 'p')) {
        score->readPos += 8;
        if (addr[7] != 1) {
            printf(D_8009084C);
            return -1;
        }
    } else {
        printf(D_80090864);
        return 0;
    }
    score->unk4A = (*score->readPos++) << 8 | *score->readPos++;
    score->unk84 = (*score->readPos++) << 0x10 | (*score->readPos++) << 8 |
                   *score->readPos++;
    if ((score->unk84 / 2) < (60000000 % score->unk84)) {
        score->unk84 = (60000000 / score->unk84) + 1;
    } else {
        score->unk84 = 60000000 / score->unk84;
    }
    score->unk8C = score->unk84;
    score->readPos += 2;
    score->deltaValue = score->unk7C = _SsReadDeltaValue(arg0, 0);
    score->nextSepPos = score->readPos;
    score->loopPos = score->readPos;

    if ((score->unk4A * score->unk84 * 10) < (VBLANK_MINUS * 60)) {
        score->unk70 = score->unk6E =
            (VBLANK_MINUS * 600) / (score->unk4A * score->unk84);
    } else {
        score->unk6E = -1;
        score->unk70 = (score->unk4A * score->unk84 * 10) / (VBLANK_MINUS * 60);
        if ((VBLANK_MINUS * 30) <
            (score->unk4A * score->unk84 * 10) % (VBLANK_MINUS * 60)) {
            score->unk70++;
        }
    }
    score->unk72 = score->unk70;
    return 0;
}

extern char D_80090888[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090888);
s16 _SsInitSoundSeq(s16, s16, u8 *);

s16 SsSeqOpen(u32 addr, s16 vab_id) {
    s16 seq_sep_no;
    u32 bit_pos;
    u8 found;

    if (_snd_openflag == 0xFFFFFFFF) {
        printf(D_80090888);
        return -1;
    }
    bit_pos = 0;
    found = 0;
    while (!found) {
        if (!((1 << bit_pos) & _snd_openflag)) {
            seq_sep_no = bit_pos;
            found = 1;
        }
        bit_pos++;
    }
    _snd_openflag |= 1 << seq_sep_no;
    if (_SsInitSoundSeq(seq_sep_no, vab_id, addr) == -1) {
        return -1;
    }
    return seq_sep_no;
}

/* SPDX-License-Identifier: MIT */
void _SsGetSeqData(s16, s16);
void _SsSeqPlay(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    s32 elapsed;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    if (score->deltaValue - score->unk70 > 0) {
        if (score->unk6E > 0) {
            score->unk6E--;
        } else if (score->unk6E == 0) {
            score->unk6E = score->unk70;
            score->deltaValue--;
        } else {
            score->deltaValue -= score->unk70;
        }
    } else if (score->deltaValue <= score->unk70) {
        elapsed = score->deltaValue;
        do {
            do {
                _SsGetSeqData(access, sequence);
            } while (score->deltaValue == 0);
            elapsed += score->deltaValue;
        } while (elapsed < score->unk70);
        score->deltaValue = elapsed - score->unk70;
    }
}

/* SPDX-License-Identifier: MIT */
void _SsGetMetaEvent(s16, s16, u8);
void _SsNoteOn(s16, s16, s32, s32);
s32 _SsReadDeltaValue(s16, s16);
void _SsSetPitchBend(s16, s16);
void _SsSetProgramChange(s16, s16, u8);
void _SsSetControlChange(s16, s16, u8);
void _SsGetSeqData(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    u8 event;
    u8 note;
    u8 velocity;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    event = *score->readPos++;
    if (event & 0x80) {
        score->channel = event & 0xF;
        switch (event & 0xF0) {
        case 0x90:
            score->eventStatus = 0x90;
            note = *score->readPos++;
            velocity = *score->readPos++;
            score->deltaValue = _SsReadDeltaValue(access, sequence);
            _SsNoteOn(access, sequence, note, velocity);
            return;
        case 0xB0:
            score->eventStatus = 0xB0;
            _SsSetControlChange(access, sequence, *score->readPos++);
            return;
        case 0xC0:
            score->eventStatus = 0xC0;
            _SsSetProgramChange(access, sequence, *score->readPos++);
            return;
        case 0xE0:
            score->eventStatus = 0xE0;
            score->readPos++;
            _SsSetPitchBend(access, sequence);
            return;
        case 0xF0:
            score->eventStatus = 0xFF;
            score->channel = event & 0xF;
            _SsGetMetaEvent(access, sequence, *score->readPos++);
            return;
        }
    } else {
        switch (score->eventStatus) {
        case 0x90:
            velocity = *score->readPos++;
            score->deltaValue = _SsReadDeltaValue(access, sequence);
            _SsNoteOn(access, sequence, event, velocity);
            return;
        case 0xB0:
            _SsSetControlChange(access, sequence, event);
            return;
        case 0xC0:
            _SsSetProgramChange(access, sequence, event);
            return;
        case 0xE0:
            _SsSetPitchBend(access, sequence);
            return;
        case 0xFF:
            _SsGetMetaEvent(access, sequence, event);
            return;
        }
    }
}

/* SPDX-License-Identifier: MIT */
s32 SpuVmKeyOn(s16, s16, s16, s32, s32, s32);
void SpuVmKeyOff(s16, s16, u8, s32);
void _SsNoteOn(s16 access, s16 sequence, s32 note, s32 velocity) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    u8 channel;
    s32 volume;
    u8 pan;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    channel = score->channel;
    pan = velocity;
    volume = pan & 0xFF;
    pan = score->panpot[channel];
    if ((score->unkAA >> channel) & 1 || score->leftVolume == 0) {
        return;
    }
    if (velocity & 0xFF) {
        SpuVmKeyOn(access | (sequence << 8), score->unk4C,
                   score->programs[channel], note & 0xFF, volume, pan);
        score->unkA8 = volume;
    } else {
        SpuVmKeyOff(access | (sequence << 8), score->unk4C,
                    score->programs[channel], note & 0xFF);
    }
}

/* SPDX-License-Identifier: MIT */
s32 _SsReadDeltaValue(s16, s16);
void _SsSetProgramChange(s16 access, s16 sequence, u8 program) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    score->programs[score->channel] = program;
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

/* SPDX-License-Identifier: MIT */
void SpuVmSetVol();
s32 SpuVmSetProgVol(s16, s16, s32);
void SpuVmDamperOff(void);
void _SsContDataEntry(s16, s16, u8);
void _SsContPortamento(s16, s16, u8);
void _SsContNrpn1(s16, s16, u8);
void _SsContNrpn2(s16, s16, u8);
void _SsContRpn1(s16, s16, u8);
void _SsContRpn2(s16, s16, u8);
void _SsContResetAll(s16, s16);

void _SsSetControlChange(s16 arg0, s16 arg1, u8 control) {
    struct SeqStruct *score = &D_800BDE3C[arg0][arg1];
    s16 channel = score->channel;
    s16 val = *score->readPos++;

    switch (control) {
    case 0x0:
        score->unk4C = val;
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    case 0x6:
        _SsContDataEntry(arg0, arg1, val);
        break;
    case 0x7:
        SpuVmSetVol((arg1 << 8) | arg0, score->unk4C, score->programs[channel],
                    val, score->panpot[channel]);
        score->vol[channel] = val;
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    case 0xA:
        SpuVmSetVol((arg1 << 8) | arg0, score->unk4C, score->programs[channel],
                    score->vol[channel], val);
        score->panpot[channel] = val;
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    case 0xB:
        SpuVmSetProgVol(score->unk4C, score->programs[channel], val);
        SpuVmSetVol((arg1 << 8) | arg0, score->unk4C, score->programs[channel],
                    score->vol[channel], score->panpot[channel]);
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    case 0x40:
        if (val >= 0 && val < 0x40) {
            SpuVmDamperOff();
        } else {
            SpuVmDamperOn();
        }
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    case 0x41:
        _SsContPortamento(arg0, arg1, val);
        break;
    case 0x5B:
        SsUtSetReverbDepth(val, val);
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    case 0x62:
        _SsContNrpn1(arg0, arg1, val);
        break;
    case 0x63:
        _SsContNrpn2(arg0, arg1, val);
        break;
    case 0x64:
        _SsContRpn1(arg0, arg1, val);
        break;
    case 0x65:
        _SsContRpn2(arg0, arg1, val);
        break;
    case 0x79:
        _SsContResetAll(arg0, arg1);
        break;
    default:
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    }
}
typedef struct {
    u8 tones;
    u8 bytes[15];
} ProgramAttrBuffer;
typedef struct {
    u8 bytes[32];
} ToneAttrBuffer;
s16 SsUtGetProgAtr(s16, s16, u8 *);
s16 SsUtGetVagAtr(s16, s16, s16, VagAtr *);
s16 SsUtSetVagAtr(s16, s16, s16, VagAtr *);
void _SsContModulation(s16 access, s16 sequence, s32 value) {
    struct SeqStruct *score;
    ProgramAttrBuffer progAtr;
    ToneAttrBuffer toneAtr;
    s32 tone;
    s32 row;
    s32 offset;
    u8 channel;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    channel = score->channel;
    SsUtGetProgAtr(score->unk4C, score->programs[channel], (u8 *)&progAtr);
    for (tone = 0; tone < progAtr.tones; tone++) {
        SsUtGetVagAtr(score->unk4C, score->programs[channel], tone,
                      (u8 *)&toneAtr);
        toneAtr.bytes[8] = value;
        SsUtSetVagAtr(score->unk4C, score->programs[channel], tone,
                      (u8 *)&toneAtr);
    }
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

void _SsContPortaTime(s16 access, s16 sequence, s32 value) {
    struct SeqStruct *score;
    ProgramAttrBuffer progAtr;
    ToneAttrBuffer toneAtr;
    s32 tone;
    s32 row;
    s32 offset;
    u8 channel;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    channel = score->channel;
    SsUtGetProgAtr(score->unk4C, score->programs[channel], (u8 *)&progAtr);
    for (tone = 0; tone < progAtr.tones; tone++) {
        SsUtGetVagAtr(score->unk4C, score->programs[channel], tone,
                      (u8 *)&toneAtr);
        toneAtr.bytes[11] = value;
        SsUtSetVagAtr(score->unk4C, score->programs[channel], tone,
                      (u8 *)&toneAtr);
    }
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

void _SsContPortamento(s16 arg0, s16 arg1, u8 arg2) {
    struct SeqStruct *score = &D_800BDE3C[arg0][arg1];
    u8 channel = score->channel;
    ProgAtr progAtr;
    VagAtr vagAtr;
    s32 toneNum;

    SsUtGetProgAtr(score->unk4C, score->programs[channel], (u8 *)&progAtr);
    for (toneNum = 0; toneNum < progAtr.tones; toneNum++) {
        SsUtGetVagAtr(score->unk4C, score->programs[channel], toneNum,
                      (u8 *)&vagAtr);
        if (arg2 >= 0 && arg2 < 0x40) {
            vagAtr.mode = 2;
        } else if (arg2 >= 0x40 && arg2 < 0x80) {
            vagAtr.mode = 0;
        }
        SsUtSetVagAtr(score->unk4C, score->programs[channel], toneNum,
                      (u8 *)&vagAtr);
    }

    score->deltaValue = _SsReadDeltaValue(arg0, arg1);
}

void _SsContResetAll(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    u8 *bytes;
    register s32 channel0 asm("v0");
    register s32 channel1 asm("v1");
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    bytes = (u8 *)score;
    func_80082B70();
    SpuVmDamperOff();
    channel0 = *(volatile u8 *)(bytes + 0x12);
    channel1 = *(volatile u8 *)(bytes + 0x12);
    asm("addu %0, %1, %0" : "=r"(channel0) : "r"(bytes), "0"(channel0));
    *(u8 *)(channel0 + 0x2C) = (u8)channel1;
    score->unk13 = 0;
    score->unk14 = 0;
    *(u16 *)(bytes + *(volatile u8 *)(bytes + 0x12) * 2 + 0x4E) = 0x7F;
    channel0 = *(volatile u8 *)(bytes + 0x12);
    asm("addu %0, %1, %0" : "=r"(channel0) : "r"(bytes), "0"(channel0));
    *(u8 *)(channel0 + 0x17) = 0x40;
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

void _SsContNrpn1(s16 access, s16 sequence, u8 value) {
    extern s32 D_800BDF0C[][16];
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    s32 (*callback)(s16, s16, s32);
    u8 status;

    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    if (score->unk27 != 1) {
        goto check_status;
    }
    if (score->unk10 != 0) {
        goto check_status;
    }
    score->unk28 = value;
    score->unk10 = 1;
    goto after_status;
check_status:
    status = score->unk16;
    if (status == 0x1E) {
        goto after_status;
    }
    if (status == 0x14) {
        goto after_status;
    }
    score->unk15 = value;
    score->unk2A++;
after_status:
    if (score->unk16 == 0x28) {
        callback = (s32 (*)(s16, s16, s32))D_800BDF0C[access][sequence];
        if (callback != 0) {
            callback(access, sequence, value & 0xFF);
        }
    }
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

void _SsContNrpn2(s16 arg0, s16 arg1, u8 arg2) {
    struct SeqStruct *score = &D_800BDE3C[arg0][arg1];

    switch (arg2) {
    case 0x14:
        score->unk16 = arg2;
        score->unk27 = 1;
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        score->loopPos = score->readPos;
        break;

    case 0x1E:
        score->unk16 = arg2;
        if (score->unk28 == 0) {
            score->unk10 = 0;
            score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        } else if (score->unk28 < 0x7FU) {
            score->unk28--;
            score->deltaValue = _SsReadDeltaValue(arg0, arg1);
            if (score->unk28 != 0) {
                score->readPos = score->loopPos;
            } else {
                score->unk10 = 0;
            }
        } else {
            _SsReadDeltaValue(arg0, arg1);
            score->deltaValue = 0;
            score->readPos = score->loopPos;
        }
        break;

    default:
        score->unk16 = arg2;
        score->unk2A += 1;
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    }
}

/* SPDX-License-Identifier: MIT */
s32 _SsReadDeltaValue(s16, s16);
void _SsContRpn1(s16 access, s16 sequence, u8 value) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    score->unk13 = value;
    score->unk29 = score->unk29 + 1;
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

/* SPDX-License-Identifier: MIT */
s32 _SsReadDeltaValue(s16, s16);
void _SsContRpn2(s16 access, s16 sequence, u8 value) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    score->unk14 = value;
    score->unk29 = score->unk29 + 1;
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsContDataEntry);

typedef struct {
    u16 unk0, unk2, unk4, unk6, unk8;
    s16 unkA, unkC, unkE, unk10;
} SsAdsr;
typedef struct {
    u8 prior;
    u8 mode;
    u8 vol;
    u8 pan;
    u8 center;
    u8 shift;
    u8 min;
    u8 max;
    u8 vibW;
    u8 vibT;
    u8 porW;
    u8 porT;
    u8 pbmin;
    u8 pbmax;
    u8 reserved1;
    u8 reserved2;
    u16 adsr1;
    u16 adsr2;
    s16 prog;
    s16 vag;
    s16 reserved[4];
} SdkVagAttr;
s16 SsUtGetVagAtr(s16, s16, s16, VagAtr *);
s16 SsUtSetVagAtr(s16, s16, s16, VagAtr *);
void SsUtSetReverbDepth(short, short);
void SsUtSetReverbFeedback(short);
void SsUtSetReverbDelay(short);
void func_80082B50(void);
void func_80082B70(void);
void _SsSndSetVabAttr(s16 vabId, s16 progNum, s16 toneNum, SdkVagAttr vagAtr,
                      SsAdsr adsrBuffer, s16 idx, u8 attr) {
    s16 temp;
    SsUtGetVagAtr(vabId, progNum, toneNum, (u8 *)&vagAtr);
    switch (idx) {
    case 0:
        vagAtr.prior = attr;
        SsUtSetVagAtr(vabId, progNum, toneNum, (u8 *)&vagAtr);
        break;
    case 1:
        vagAtr.mode = attr;
        SsUtSetVagAtr(vabId, progNum, toneNum, (u8 *)&vagAtr);
        if (attr == 0) {
            func_80082B70();
        } else if (attr == 1) {
        } else if (attr == 2) {
        } else if (attr == 3) {
        } else if (attr == 4) {
            func_80082B50();
        }
        break;
    case 2:
        vagAtr.min = attr;
        SsUtSetVagAtr(vabId, progNum, toneNum, (u8 *)&vagAtr);
        break;
    case 3:
        vagAtr.max = attr;
        SsUtSetVagAtr(vabId, progNum, toneNum, (u8 *)&vagAtr);
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        temp = idx - 4;
        _SsUtResolveADSR(vagAtr.adsr1, vagAtr.adsr2, &adsrBuffer);
        __asm__(".rdata\n.long 0\n.text");
        switch (temp) {
        case 0:
            adsrBuffer.unkA = 0;
            adsrBuffer.unk0 = attr;
            break;
        case 1:
            adsrBuffer.unkA = 1;
            adsrBuffer.unk0 = attr;
            break;
        case 2:
            adsrBuffer.unk2 = attr;
            break;
        case 3:
            adsrBuffer.unk4 = attr;
            break;
        case 4:
            adsrBuffer.unkC = 0;
            adsrBuffer.unk6 = attr;
            break;
        case 5:
            adsrBuffer.unkC = 1;
            adsrBuffer.unk6 = attr;
            break;
        case 6:
            adsrBuffer.unkE = 0;
            adsrBuffer.unk8 = attr;
            break;
        case 7:
            adsrBuffer.unkE = 1;
            adsrBuffer.unk8 = attr;
            break;
        case 8:
            if (attr > 0 && attr < 0x40)
                adsrBuffer.unk10 = 0;
            else if (attr >= 0x40 && attr < 0x80)
                adsrBuffer.unk10 = 1;
            break;
        case 9:
            vagAtr.vibT = attr;
            break;
        case 10:
            vagAtr.porW = attr;
            break;
        }
        _SsUtBuildADSR(&adsrBuffer, &vagAtr.adsr1, &vagAtr.adsr2);
        SsUtSetVagAtr(vabId, progNum, toneNum, (u8 *)&vagAtr);
        break;
    case 15:
        SsUtSetReverbType(attr);
        break;
    case 16:
        SsUtSetReverbDepth(attr, attr);
        break;
    case 17:
        SsUtSetReverbFeedback(attr);
        break;
    case 18:
    case 19:
        SsUtSetReverbDelay(attr);
        break;
    case 20:
    case 21:
    case 22:
        break;
    }
}

/* SPDX-License-Identifier: MIT */
s32 SpuVmPitchBend(s32, s16, s16, s16);
s32 _SsReadDeltaValue(s16, s16);
void _SsSetPitchBend(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    u8 channel;
    u8 *data;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    channel = score->channel;
    data = score->readPos++;
    SpuVmPitchBend((sequence << 8) | access, score->unk4C,
                   score->programs[channel], *data);
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

extern void _SsSndNextSep(s16, s16);

void _SsGetMetaEvent(s16 arg0, s16 arg1, u8 arg2) {
    struct SeqStruct *score = &D_800BDE3C[arg0][arg1];

    switch (arg2) {
    case 0x51:
        score->unk8C = (*score->readPos++) << 0x10 | (*score->readPos++) << 8 |
                       *score->readPos++;
        score->unk8C = 60000000 / score->unk8C;
        if ((score->unk4A * score->unk8C * 10) < VBLANK_MINUS * 60) {
            score->unk70 = score->unk6E =
                (VBLANK_MINUS * 600) / (score->unk4A * score->unk8C);
        } else {
            score->unk6E = -1;
            score->unk70 =
                (score->unk4A * score->unk8C * 10) / (VBLANK_MINUS * 60);
            if ((VBLANK_MINUS * 30) <
                (score->unk4A * score->unk8C * 10) % (VBLANK_MINUS * 60)) {
                score->unk70++;
            }
        }
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        return;
    case 0x2F:
        score->loopIndex++;
        if (score->loopCount == 0) {
            score->unk80 = 0;
            score->unk27 = 0;
            score->deltaValue = 0;
            score->readPos = score->nextSepPos;
            return;
        }
        if (score->loopIndex < score->loopCount) {
            score->unk80 = 0;
            score->unk27 = 0;
            score->deltaValue = 0;
            score->readPos = score->nextSepPos;
            score->loopPos = score->nextSepPos;
            return;
        }
        D_800BDE3C[arg0][arg1].unk90 &= ~1;
        D_800BDE3C[arg0][arg1].unk90 &= ~8;
        D_800BDE3C[arg0][arg1].unk90 &= ~2;
        D_800BDE3C[arg0][arg1].unk90 |= 0x200;
        D_800BDE3C[arg0][arg1].unk90 |= 4;
        score->unk2B = 0;
        score->loopPos = score->nextSepPos;
        if (score->unk3C != 0xFF) {
            score->unk2B = 0;
            _SsSndNextSep(score->unk3C, score->unk0);
            SpuVmSeqKeyOff((arg1 << 8) | arg0);
        }
        SpuVmSeqKeyOff((arg1 << 8) | arg0);
        score->deltaValue = score->unk70;
        return;
    }
}

/* SPDX-License-Identifier: MIT */
s32 _SsReadDeltaValue(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    s32 delta;
    u8 next;
    u32 value;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    value = *score->readPos++;
    if (value == 0) {
        return 0;
    }
    if (value & 0x80) {
        value &= 0x7F;
        do {
            next = *score->readPos++;
            value = (value << 7) + (next & 0x7F);
        } while (next & 0x80);
    }
    delta = value * 10;
    score->unk80 = delta + score->unk80;
    return delta;
}

/* Resolved ADSR envelope of a VagAtr: five rates/levels and four mode
 * flags, split out of the two packed adsr1/adsr2 words. */

void _SsUtResolveADSR(u16 adsr1, u16 adsr2, SsAdsr *adsr) {
    u32 temp;

    adsr->unkA = adsr1 & 0x8000;
    adsr->unkC = adsr2 & 0x8000;
    adsr->unk10 = adsr2 & 0x4000;
    temp = adsr1 & 0xFFFF;
    adsr->unkE = adsr2 & 0x20;
    adsr->unk0 = (temp >> 8) & 0x7F;
    adsr->unk2 = (temp >> 4) & 0xF;
    adsr->unk4 = adsr1 & 0xF;
    adsr->unk6 = (adsr2 >> 6) & 0x7F;
    adsr->unk8 = adsr2 & 0x1F;
}

void _SsUtBuildADSR(SsAdsr *adsr, u16 *adsr1, u16 *adsr2) {
    u16 word2;
    s32 mode;
    s32 am;
    u16 word1;

    mode = -(adsr->unkC != 0) & ~0x7FFF;
    am = -(adsr->unkA != 0) & ~0x7FFF;
    word2 = mode;
    if (adsr->unk10 != 0) {
        word2 = mode | 0x4000;
    }
    word1 = am | ((adsr->unk0 << 8) & 0x7F00) | ((adsr->unk2 << 4) & 0xF0) |
            (adsr->unk4 & 0xF);
    word2 = word2 | ((adsr->unk6 << 6) & 0x1FC0) | (adsr->unk8 & 0x1F);
    *adsr1 = word1;
    *adsr2 = word2;
}

/* SPDX-License-Identifier: MIT */
void _SsSndNextSep(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    score->loopCount = 1;
    score->loopIndex = 0;
    D_800BDE3C[access][sequence].unk90 &= ~0x100;
    D_800BDE3C[access][sequence].unk90 &= ~0x8;
    D_800BDE3C[access][sequence].unk90 &= ~0x2;
    D_800BDE3C[access][sequence].unk90 &= ~0x4;
    D_800BDE3C[access][sequence].unk90 &= ~0x200;
    score->unk2B = 1;
    score->readPos = score->nextSepPos;
    D_800BDE3C[access][sequence].unk90 |= 1;
}

void SsSetTempo(s16 access, s16 sequence, s16 tempo) {
    struct SeqStruct *score = &D_800BDE3C[access][sequence];

    score->unk8C = tempo;
    if ((score->unk4A * score->unk8C * 10) < (VBLANK_MINUS * 60)) {
        score->unk70 = score->unk6E =
            (VBLANK_MINUS * 600) / (score->unk4A * score->unk8C);
    } else {
        score->unk6E = -1;
        score->unk70 = (score->unk4A * score->unk8C * 10) / (VBLANK_MINUS * 60);
        if ((VBLANK_MINUS * 30) <
            (score->unk4A * score->unk8C * 10) % (VBLANK_MINUS * 60)) {
            score->unk70++;
        }
    }
    score->unk72 = score->unk70;
}

void SsSetLoop(s16 access, s16 sequence, s16 count) {
    struct SeqStruct *score;
    score = D_800BDE3C[access];
    score[sequence].loopCount = count;
    score[sequence].loopIndex = 0;
}

s32 SsIsEos(s32 vabId, s32 seqId) {
    return D_800BDE3C[(s16)vabId][(s16)seqId].unk2B;
}

extern s32 D_800BDF0C[][16];

void SsSetMarkCallback(s16 arg0, s16 arg1, s32 arg2) {
    s32 shifted;
    s32(*rows)[16];
    s32 *row;

    shifted = arg0 << 16;
    rows = D_800BDF0C;
    row = (s32 *)((shifted >> 10) + (s32)rows);
    row[arg1] = arg2;
}

void _SsClose(s16 seq_sep_num) {
    s32 seq_num;
    SpuVmSetSeqVol(seq_sep_num, 0, 0, 1);
    SpuVmSeqKeyOff(seq_sep_num);
    _snd_openflag &= ~(1 << seq_sep_num);
    for (seq_num = 0; seq_num < _snd_seq_t_max; seq_num++) {
        D_800BDE3C[seq_sep_num][seq_num].unk90 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk3C = 0xFF;
        D_800BDE3C[seq_sep_num][seq_num].unk0 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk3E = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk40 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk94 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk98 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk42 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unkA4 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unkA0 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk9C = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk44 = 0;
        D_800BDE3C[seq_sep_num][seq_num].leftVolume = 0x7f;
        D_800BDE3C[seq_sep_num][seq_num].rightVolume = 0x7f;
    }
}

extern void _SsClose(short);

void SsSeqClose(short seq_access_num) {
    _SsClose(seq_access_num);
}

extern void _SsClose(short);

void SsSepClose(short sep_access_num) {
    _SsClose(sep_access_num);
}

extern s16 D_800A2070[];
extern s16 D_800A2080[];
extern s32 D_800BDF0C[][16];
extern void SpuVmInit(u8);

void _SsInit(void) {
    u16 *var_a2;
    s32 i, j;

    var_a2 = (u16 *)0x1F801C00;
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 8; j++) {
            *var_a2++ = D_800A2070[j];
        }
    }

    var_a2 = (u16 *)0x1F801D80;
    for (i = 0; i < 16; i++) {
        *var_a2++ = D_800A2080[i];
    }

    SpuVmInit(24);

    for (j = 0; j < 32; j++) {
        for (i = 0; i < 16; i++) {
            D_800BDF0C[j][i] = 0;
        }
    }

    VBLANK_MINUS = 60;
    _snd_openflag = 0;
    _snd_ev_flag = 0;
}

extern void _SsInit(void);
extern void func_80087CC0(void);

void func_80080728(void) {
    ResetCallback();
    func_80087CC0();
    _SsInit();
}

void func_80080758(void) {
    SpuQuit();
}

/* SPDX-License-Identifier: MIT */

extern s32 D_800A20A0[];
extern s32 D_800A20A4[];
extern Callback D_800A20A8[];
extern s32 D_800A20AC[];
extern u8 D_800A20B0[];
extern u8 D_800A20B1[];
extern u8 D_800A20B2[];
extern void _SsTrapIntrVSync(void);
extern void _SsSeqCalledTbyT_1per2(void);

s32 _SsStart(s32 arg0) {
    s32 wait;
    s32 mode;
    s32 rcntSpec;
    s32 rcntTarget;
    s32 b2;
    Callback callback;

    wait = 1000;
    while (--wait >= 0) {
    }
    rcntSpec = 0xF2000002;
    D_800A20B0[0] = 0;
    mode = D_800A20A0[0];
    D_800A20B2[0] = 6;
    D_800A20B1[0] = 0;
    D_800A20AC[0] = 0;
    switch (mode) {
    case 0:
        ((u8 *)D_800A20B1)[1] = 0xFF;
        return;
    case 5:
        ((u8 *)D_800A20A4)[0xE] = 0;

        if (arg0 == 0) {
            D_800A20B0[0] = 1;
        } else {
            rcntSpec = 0xF2000003;
            rcntTarget = 1;
        }
        break;
    case 3:
        rcntTarget = 0x89D0;
        break;
    case 2:
        rcntTarget = 0x44E8;
        break;
    default: {
        register u8 *env asm("a0");
        register s32 ticks asm("v1");
        register s32 quot asm("v0");
        register s32 envD asm("v1");

        env = (u8 *)D_800A20A4;
        __asm__("" : "=r"(env) : "0"(env));
        if (*(s32 *)env != 0) {
            return;
        }
        ticks = *(s32 *)(env - 4);
        if (ticks < 0x46) {
            quot = 0x204CC0 / ticks;
            envD = env[0xD];
            envD = envD + 1;
            env[0xD] = envD;
        } else {
            quot = 0x409980 / ticks;
        }
        rcntTarget = quot;
        break;
    }
    }
    if (D_800A20B0[0] != 0) {
        EnterCriticalSection();
        VSyncCallback(D_800A20A8[0]);
    } else {
        EnterCriticalSection();
        ResetRCnt(rcntSpec);
        SetRCnt(rcntSpec, rcntTarget & 0xFFFF, 0x1000);
        b2 = ((u8 *)D_800A20B1)[1];
        if (b2 == 0) {
            D_800A20AC[0] = InterruptCallback(0, NULL);
            b2 = D_800A20B2[0];
            callback = _SsTrapIntrVSync;
        } else if (D_800A20B1[0] == 0) {
            callback = D_800A20A8[0];
        } else {
            callback = _SsSeqCalledTbyT_1per2;
        }
        InterruptCallback(b2, callback);
    }
    ExitCriticalSection();
    return;
}

/* SPDX-License-Identifier: MIT */

extern s32 _SsStart(s32); /* extern */

void SsStart(void) {
    _SsStart(1);
}

/* SPDX-License-Identifier: MIT */

extern s32 _SsStart(s32); /* extern */

void SsStart2(void) {
    _SsStart(0);
}

void _SsTrapIntrVSync(void) {
    if (D_800A20AC[0] != 0)
        ((Callback)D_800A20AC[0])();
    ((Callback)D_800A20A8[0])();
}

extern s32 D_800A20B4Read[];
extern s32 D_800A20B4Write[];
void _SsSeqCalledTbyT_1per2(void) {
    if (D_800A20B4Read[0] == 0) {
        D_800A20B4Write[0] = 1;
        return;
    }
    D_800A20B4Write[0] = 0;
    ((Callback)D_800A20A8[0])();
}

extern void SpuVmFlush(void);
extern void _SsSndPlay(s16, s16);
extern void _SsSndCrescendo(s16, s16);
extern void _SsSndDecrescendo(s16, s16);
extern void _SsSndTempo(s16, s16);
extern void _SsSndPause(s16, s16);
extern void _SsSndReplay(s16, s16);
extern void _SsSndStop(s16, s16);

void SsSeqCalledTbyT(void) {
    s32 i;
    s32 j;
    if (_snd_ev_flag != 1) {
        _snd_ev_flag = 1;

        SpuVmFlush();

        for (i = 0; i < _snd_seq_s_max; i++) {
            if ((1 << i) & _snd_openflag) {
                for (j = 0; j < _snd_seq_t_max; j++) {
                    if (D_800BDE3C[i][j].unk90 & 1) {
                        _SsSndPlay(i, j);

                        if (D_800BDE3C[i][j].unk90 & 0x10) {
                            _SsSndCrescendo(i, j);
                        }

                        if (D_800BDE3C[i][j].unk90 & 0x20) {
                            _SsSndDecrescendo(i, j);
                        }

                        if (D_800BDE3C[i][j].unk90 & 0x40) {
                            _SsSndTempo(i, j);
                        }

                        if (D_800BDE3C[i][j].unk90 & 0x80) {
                            _SsSndTempo(i, j);
                        }
                    }

                    if (D_800BDE3C[i][j].unk90 & 2) {
                        _SsSndPause(i, j);
                    }

                    if (D_800BDE3C[i][j].unk90 & 8) {
                        _SsSndReplay(i, j);
                    }

                    if (D_800BDE3C[i][j].unk90 & 4) {
                        ((void (*)())_SsSndStop)(i, j);
                        D_800BDE3C[i][j].unk90 = 0;
                    }
                }
            }
        }
        _snd_ev_flag = 0;
    }
}

extern long SpuVmGetSeqVol(short, short *, short *);
extern s32 SpuVmSetSeqVol(s16, u16, u16, s16);

void _SsSndCrescendo(s16 arg0, s16 arg1) {
    struct SeqStruct *score = &D_800BDE3C[arg0][arg1];
    u16 voll, volr;

    score->unk98--;

    if (score->unk42 > 0) {
        if ((score->unk98 % score->unk42) == 0) {
            score->unk40--;
            if (score->unk40 >= 0) {
                SpuVmGetSeqVol(arg0 | (arg1 << 8), &voll, &volr);
                if ((voll + 1) <= (voll + score->unk40)) {
                    SpuVmSetSeqVol(arg0 | (arg1 << 8), voll + 1, volr + 1, 0);
                }
            } else {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), 0x7F, 0x7F, 0);
                D_800BDE3C[arg0][arg1].unk90 &= ~0x10;
            }
            if ((score->unk98 == 0) || (score->unk40 == 0)) {
                D_800BDE3C[arg0][arg1].unk90 &= ~0x10;
            }
        }
    } else if (score->unk42 < 0) {
        score->unk40 += score->unk42;
        if (score->unk40 >= 0) {
            SpuVmGetSeqVol(arg0 | (arg1 << 8), &voll, &volr);
            if (((voll - score->unk42) >= 0x7F) &&
                ((volr - score->unk42) >= 0x7F)) {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), 0x7F, 0x7F, 0);
            }
            if (((score->unk94 - score->unk98) * -score->unk42) <
                score->unk3E) {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), voll - score->unk42,
                               volr - score->unk42, 0);
            }
        } else {
            SpuVmSetSeqVol(arg0 | (arg1 << 8), 0x7F, 0x7F, 0);
            D_800BDE3C[arg0][arg1].unk90 &= ~0x10;
        }
        if ((score->unk98 == 0) || (score->unk40 == 0)) {
            D_800BDE3C[arg0][arg1].unk90 &= ~0x10;
        }
    }
    SpuVmGetSeqVol(arg0 | (arg1 << 8), &score->unk78, &score->unk7A);
}

void _SsSndDecrescendo(s16 arg0, s16 arg1) {
    struct SeqStruct *score = &D_800BDE3C[arg0][arg1];
    u16 voll, volr;

    score->unk98--;

    if (score->unk42 > 0) {
        if ((score->unk98 % score->unk42) == 0) {
            score->unk40--;
            if (score->unk40 > 0) {
                SpuVmGetSeqVol(arg0 | (arg1 << 8), &voll, &volr);
                if (((voll - score->unk40) > 0) &&
                    ((volr - score->unk40) > 0) && voll != 1) {
                    SpuVmSetSeqVol(arg0 | (arg1 << 8), voll - 1, volr - 1, 0);
                } else {
                    SpuVmSetSeqVol(arg0 | (arg1 << 8), 1, 1, 0);
                }
            } else {
                D_800BDE3C[arg0][arg1].unk90 &= ~0x20;
            }
            if ((score->unk98 == 0) || (score->unk40 == 0)) {
                D_800BDE3C[arg0][arg1].unk90 &= ~0x20;
            }
        }
    } else {
        score->unk40 += score->unk42;
        if (score->unk40 > 0) {
            SpuVmGetSeqVol(arg0 | (arg1 << 8), &voll, &volr);
            if ((score->unk3E >=
                 ((score->unk94 - score->unk98) * -score->unk42)) &&
                -score->unk42 < voll) {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), voll + score->unk42,
                               volr + score->unk42, 0);
            } else {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), 1, 1, 0);
            }
        } else {
            D_800BDE3C[arg0][arg1].unk90 &= ~0x20;
        }
        if ((score->unk98 == 0) || (score->unk40 == 0)) {
            D_800BDE3C[arg0][arg1].unk90 &= ~0x20;
        }
    }
    SpuVmGetSeqVol(arg0 | (arg1 << 8), &score->unk78, &score->unk7A);
}

/* SPDX-License-Identifier: MIT */
void _SsSndPause(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    SpuVmSeqKeyOff((sequence << 8) | access, sequence << 8);
    score->unk2B = 0;
    D_800BDE3C[access][sequence].unk90 &= ~2;
}

void _SsSndPlay(s16 arg0, s16 arg1) {
    _SsSeqPlay(arg0, arg1);
}

/* SPDX-License-Identifier: MIT */
void _SsSndReplay(s16 access, s16 sequence) {
    D_800BDE3C[access][sequence].unk2B = 1;
    D_800BDE3C[access][sequence].unk90 &= ~8;
}

/* SPDX-License-Identifier: MIT */

extern s32 D_800BDE2C[];

void SsSetTickMode(long tickMode) {
    s32 videoMode;
    s32 mode;

    videoMode = GetVideoMode();
    if (tickMode & 0x1000) {
        D_800A20A4[0] = 1;
        D_800A20A0[0] = tickMode & 0xFFF;
    } else {
        D_800A20A4[0] = 0;
        D_800A20A0[0] = tickMode;
    }
    mode = D_800A20A0[0];
    if (mode < 6) {
        switch (mode) {
        case 4:
            D_800BDE2C[0] = 50;
            if (videoMode == 1) {
                D_800A20A0[0] = 5;
            } else {
                D_800A20A0[0] = 50;
            }
            break;
        case 1:
            D_800BDE2C[0] = 60;
            if (videoMode == 0) {
                D_800A20A0[0] = 5;
            } else {
                D_800A20A0[0] = 60;
            }
            break;
        case 3:
            D_800BDE2C[0] = 120;
            break;
        case 2:
            D_800BDE2C[0] = 240;
            break;
        case 5:
            if (videoMode == 0) {
                D_800BDE2C[0] = 60;
            } else if (videoMode == 1) {
                D_800BDE2C[0] = 50;
            } else {
                D_800BDE2C[0] = 60;
            }
            break;
        case 0:
            if (videoMode == 0) {
                D_800BDE2C[0] = 60;
            } else if (videoMode == 1) {
                D_800BDE2C[0] = 50;
            } else {
                D_800BDE2C[0] = 60;
            }
            break;
        default:
            D_800BDE2C[0] = 60;
            break;
        }
    } else {
        D_800BDE2C[0] = mode;
    }
}
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090B38);

extern u8 D_800A20B0Read[];
extern u8 D_800A20B0Write[];
extern s32 D_800A20ACRead[];
extern s32 D_800A20ACWrite[];
extern u8 D_800A20B2Read[];
extern u8 D_800A20B2Write[];
void SsEnd(void) {
    if (D_800A20A4[0] == 0) {
        D_800A20B1[0] = 0;
        EnterCriticalSection();
        if (D_800A20B0Read[0] != 0) {
            VSyncCallback(0);
            D_800A20B0Write[0] = 0;
        } else if (D_800A20B2Read[0] == 0) {
            InterruptCallback(0, (Callback)D_800A20ACRead[0]);
            D_800A20ACWrite[0] = 0;
        } else {
            InterruptCallback(6, 0);
        }
        ExitCriticalSection();
        D_800A20B2Write[0] = 0xFF;
    }
}

void SsSetTableSize(char *table, short s_max, short t_max) {
    s32 i, j;
    struct SeqStruct *pTypedTable;

    _snd_seq_s_max = s_max;
    _snd_seq_t_max = t_max;
    pTypedTable = (struct SeqStruct *)table;
    for (i = 0; i < s_max; i++) {
        D_800BDE3C[i] = &pTypedTable[i * t_max];
    }

    for (i = 0; i < _snd_seq_s_max; i++) {
        for (j = 0; j < _snd_seq_t_max; j++) {
            D_800BDE3C[i][j].unk90 = 0;
            D_800BDE3C[i][j].unk3C = 0xFF;
            D_800BDE3C[i][j].unk0 = 0;
            D_800BDE3C[i][j].unk3E = 0;
            D_800BDE3C[i][j].unk40 = 0;
            D_800BDE3C[i][j].unk94 = 0;
            D_800BDE3C[i][j].unk98 = 0;
            D_800BDE3C[i][j].unk42 = 0;
            D_800BDE3C[i][j].unkA4 = 0;
            D_800BDE3C[i][j].unkA0 = 0;
            D_800BDE3C[i][j].unk9C = 0;
            D_800BDE3C[i][j].unk44 = 0;
            D_800BDE3C[i][j].leftVolume = 0x7F;
            D_800BDE3C[i][j].rightVolume = 0x7F;
            D_800BDE3C[i][j].unk78 = 0x7F;
            D_800BDE3C[i][j].unk7A = 0x7F;
        }
    }
}

extern long SpuVmGetSeqVol(short, short *, short *);
void _SsSndSetPauseMode(short access, short sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    SpuVmGetSeqVol(access | (sequence << 8), &score->unk78, &score->unk7A);
    D_800BDE3C[access][sequence].unk90 &= ~1;
    D_800BDE3C[access][sequence].unk90 &= ~8;
    D_800BDE3C[access][sequence].unk90 |= 2;
}

extern void _SsSndSetPauseMode(short, short);

void SsSeqPause(short seq_access_num) {
    _SsSndSetPauseMode(seq_access_num, 0);
}

extern void _SsSndSetPauseMode(short, short);

void SsSepPause(short sep_access_num, short seq_num) {
    _SsSndSetPauseMode(sep_access_num, seq_num);
}

/* SPDX-License-Identifier: MIT */
extern s32 SpuVmSetSeqVol(s16, u16, u16, s16);
void Snd_SetPlayMode(s16 access, s16 sequence, u8 mode, s16 loopCount) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    D_800BDE3C[access][sequence].unk90 &= ~0x200;
    D_800BDE3C[access][sequence].unk90 &= ~4;
    score->loopCount = loopCount;
    if (mode == 1) {
        D_800BDE3C[access][sequence].unk90 |= 1;
        score->loopIndex = 0;
        score->unk2B = 1;
        SpuVmSetSeqVol(access | (sequence << 8), score->leftVolume,
                       score->rightVolume, 0);
    } else if (mode == 0) {
        D_800BDE3C[access][sequence].unk90 |= 2;
    }
}

extern void Snd_SetPlayMode(short, short, unsigned char, short);

void SsSeqPlay(short seq_access_num, char play_mode, short l_count) {
    Snd_SetPlayMode(seq_access_num, 0, play_mode, l_count);
}

extern void Snd_SetPlayMode(short, short, unsigned char, short);

void SsSepPlay(short sep_access_num, short seq_num, char play_mode,
               short l_count) {
    Snd_SetPlayMode(sep_access_num, seq_num, play_mode, l_count);
}

void _SsSndSetReplayMode(short access, short sequence) {
    s32 status;
    status = D_800BDE3C[access][sequence].unk90;
    if ((status & 0x204) != 0) {
        return;
    }
    if ((status & 0x100) != 0) {
        return;
    }
    D_800BDE3C[access][sequence].unk90 &= ~2;
    D_800BDE3C[access][sequence].unk90 |= 8;
    D_800BDE3C[access][sequence].unk90 |= 1;
}

extern void _SsSndSetReplayMode(short, short);

void SsSeqReplay(short seq_access_num) {
    _SsSndSetReplayMode(seq_access_num, 0);
}

extern void _SsSndSetReplayMode(short, short);

void SsSepReplay(short sep_access_num, short seq_num) {
    _SsSndSetReplayMode(sep_access_num, seq_num);
}

extern s32 SpuVmSetSeqVol(s16, u16, u16, s16);

void _SsSndSetVol(s32 access_num, s32 seq_num, u16 voll, u16 volr) {
    SpuVmSetSeqVol(access_num | (seq_num << 8), voll, volr, 0);
}

extern s32 SpuVmSetSeqVol(s16, u16, u16, s16);

void SsSeqSetVol(short access_num, short voll, short volr) {
    SpuVmSetSeqVol(access_num, voll, volr, 0);
}

extern s32 SpuVmSetSeqVol(s16, u16, u16, s16);

void SsSepSetVol(short sep_access_num, short seq_num, short voll, short volr) {
    SpuVmSetSeqVol(sep_access_num | (seq_num << 8), voll & 0xFFFF,
                   volr & 0xFFFF, 0);
}

extern long SpuVmGetSeqVol(short, short *, short *);

void SsSeqGetVol(short access_num, short seq_num, short *voll, short *volr) {
    SpuVmGetSeqVol(access_num | (seq_num << 8), voll, volr);
}

/* SPDX-License-Identifier: MIT */
void _SsSndStop(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    int i;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);

    D_800BDE3C[access][sequence].unk90 &= ~1;
    D_800BDE3C[access][sequence].unk90 &= ~2;
    D_800BDE3C[access][sequence].unk90 &= ~8;
    D_800BDE3C[access][sequence].unk90 |= 4;
    SpuVmSeqKeyOff(sequence << 8 | access);
    score->unk2B = 0;
    score->unk80 = 0;
    score->unk27 = 0;
    score->unk13 = 0;
    score->unk14 = 0;
    score->unk29 = 0;
    score->unk15 = 0;
    score->unk16 = 0;
    score->unk2A = 0;
    score->channel = 0;
    score->loopIndex = 0;
    score->unk27 = 0;
    score->unk28 = 0;
    score->unk10 = 0;
    score->eventStatus = 0;
    score->deltaValue = score->unk7C;
    score->unk8C = score->unk84;
    score->unk70 = score->unk72;
    score->readPos = score->nextSepPos;
    score->loopPos = score->nextSepPos;
    for (i = 0; i < 16; i++) {
        score->programs[i] = i;
        score->panpot[i] = 0x40;
        score->vol[i] = 127;
    }

    score->unk78 = 0x7F;
    score->unk7A = 0x7F;
}

extern void _SsSndStop(short, short);

void SsSeqStop(short seq_access_num) {
    _SsSndStop(seq_access_num, 0);
}

extern void _SsSndStop(short, short);

void SsSepStop(short sep_access_num, short seq_num) {
    _SsSndStop(sep_access_num, seq_num);
}

void _SsSndTempo(s16 arg0, s16 arg1) {
    struct SeqStruct *pSeq = &D_800BDE3C[arg0][arg1];

    pSeq->unkA0--;

    if (pSeq->unk44 > 0) {
        if ((pSeq->unkA0 % pSeq->unk44) == 0) {
            if (pSeq->unk8C > pSeq->unkA4) {
                pSeq->unk8C--;
            } else if (pSeq->unk8C < pSeq->unkA4) {
                pSeq->unk8C++;
            }

            pSeq->unk70 =
                (pSeq->unk4A * pSeq->unk8C * 10) / (VBLANK_MINUS * 60);
            if (pSeq->unk70 <= 0) {
                pSeq->unk70 = 1;
            }
            if ((pSeq->unkA0 == 0) || (pSeq->unk8C == pSeq->unkA4)) {
                D_800BDE3C[arg0][arg1].unk90 &= ~0x40;
                D_800BDE3C[arg0][arg1].unk90 &= ~0x80;
            }
        }
    } else {
        if (pSeq->unk8C > pSeq->unkA4) {
            pSeq->unk8C += pSeq->unk44;
            if (pSeq->unk8C < pSeq->unkA4) {
                pSeq->unk8C = pSeq->unkA4;
            }
        } else if (pSeq->unk8C < pSeq->unkA4) {
            pSeq->unk8C -= pSeq->unk44;
            if (pSeq->unk8C > pSeq->unkA4) {
                pSeq->unk8C = pSeq->unkA4;
            }
        }

        pSeq->unk70 = (pSeq->unk4A * pSeq->unk8C * 10) / (VBLANK_MINUS * 60);
        if (pSeq->unk70 <= 0) {
            pSeq->unk70 = 1;
        }
        if ((pSeq->unkA0 == 0) || (pSeq->unk8C == pSeq->unkA4)) {
            D_800BDE3C[arg0][arg1].unk90 &= ~0x40;
            D_800BDE3C[arg0][arg1].unk90 &= ~0x80;
        }
    }
}

extern short D_800B1EA4[];
void SsSetMono(void) {
    D_800B1EA4[0] = 1;
}

extern short D_800B1EA4[];
void SsSetStereo(void) {
    D_800B1EA4[0] = 0;
}

extern u8 D_800B9DE4[];
extern void *D_800BE8F0[];
extern u16 D_800BE8EC[];

void SsVabClose(s16 vabid) {
    if ((vabid >= 0 && vabid < 0x10) && D_800B9DE4[vabid] == 1) {
        SpuFree(D_800BE8F0[vabid]);
        D_800B9DE4[vabid] = 0;
        D_800BE8EC[0] = *(u16 *)((u8 *)D_800BE8F0 - 4) - 1;
    }
}

extern s32 D_800BE930[];
extern s32 SsVabTransBody(s32, s16);
s32 SsVabOpen(u8 *addr) {
    s32 result;
    s16 vabid;
    result = SsVabOpenHead(addr, -1);
    vabid = result;
    if (vabid != -1) {
        result = SsVabTransBody(D_800BE930[vabid], vabid);
    }
    return (s16)result;
}

extern s32 SsVabOpenHeadWithMode(u8 *, s32, s32, s32);
s32 SsVabOpenHead(addr, vabid)
u8 *addr;
s16 vabid;
{
    return (s16)SsVabOpenHeadWithMode(addr, vabid, 0, 0);
}

s32 SsVabOpenHeadSticky(u_char *addr, u_long vabid, u_long sbaddr) {
    return (s16)SsVabOpenHeadWithMode(addr, (s16)vabid, 1, sbaddr);
}

extern s32 SsVabOpenHeadWithMode(u8 *, s32, s32, s32);
s32 SsVabFakeHead(addr, vabid, sbaddr)
u8 *addr;
s16 vabid;
s32 sbaddr;
{
    return (s16)SsVabOpenHeadWithMode(addr, vabid, 1, sbaddr);
}

extern s32 _spu_getInTransfer(void);

s16 SsVabOpenHeadMode(u8 *, s16, s16, u32) asm("SsVabOpenHeadWithMode");
s16 SsVabOpenHeadMode(u8 *addr, s16 vabid, s16 arg2, u32 sbaddr) {
    s32 vagLens[256];
    s32 i;
    s32 var_s0;
    s16 vabId_2;
    u16 temp_v1;
    u16 *ptr_vag_off_table;
    u32 magic;
    u32 spuAllocMem;
    u8 num_vags;
    ProgAtr *pProgTable;
    u8 *var_a2;
    VabHdr *vab_hdr_2;
    vabId_2 = 0x10;
    if (_spu_getInTransfer() == 1) {
        return -1;
    }
    _spu_setInTransfer(1);
    if (vabid >= 0x10) {
        _spu_setInTransfer(0);
        return -1;
    }
    if (vabid == -1) {
        for (i = 0; i < 16; i++) {
            if (_svm_vab_used[i] == 0) {
                _svm_vab_used[i] = 1;
                vabId_2 = i;
                _svm_vab_count++;
                break;
            }
        }
    } else {
        var_a2 = _svm_vab_used;
        if (var_a2[vabid] == 0) {
            _svm_vab_used[vabid] = 1;
            vabId_2 = vabid;
            _svm_vab_count++;
        }
    }
    if (vabId_2 >= 0x10) {
        _spu_setInTransfer(0);
        return -1;
    }
    var_a2 = addr;
    _svm_vab_vh[vabId_2] = var_a2;

    var_a2 = var_a2 + 0x20;
    vab_hdr_2 = addr;
    magic = vab_hdr_2->form;
    if ((magic >> 8) != ('V' << 0x10 | 'A' << 0x8 | 'B')) {
        _svm_vab_used[vabId_2] = 0;
        _spu_setInTransfer(0);
        _svm_vab_count -= 1;
        return -1;
    }
    if ((magic & 0xFF) == 'p') {
        if (vab_hdr_2->ver >= 5) {
            kMaxPrograms = 0x80;
        } else {
            kMaxPrograms = 0x40;
        }
    } else {
        kMaxPrograms = 0x40;
    }
    if (vab_hdr_2->ps <= kMaxPrograms) {
        _svm_vab_pg[vabId_2] = var_a2;
        pProgTable = var_a2;
        var_a2 = var_a2 + (kMaxPrograms * 0x10);
        var_s0 = 0;
        for (i = 0; i < kMaxPrograms; i++) {
            pProgTable[i].reserved1 = var_s0;
            if (pProgTable[i].tones != 0) {
                var_s0++;
            }
        }
        var_s0 = 0;
        _svm_vab_tn[vabId_2] = var_a2;
        ptr_vag_off_table = var_a2 + (vab_hdr_2->ps << 9);
        num_vags = vab_hdr_2->vs;
        for (i = 0; i < 256; i++) {
            if (num_vags >= i) {
                temp_v1 = *ptr_vag_off_table;
                if (vab_hdr_2->ver >= 5) {
                    vagLens[i] = temp_v1 * 8;
                } else {
                    vagLens[i] = temp_v1 * 4;
                }
                var_s0 += vagLens[i];
            }
            ptr_vag_off_table++;
        }

        _svm_brr_start_addr[vabId_2] = ptr_vag_off_table;
        spuAllocMem = sbaddr;
        if (arg2 == 0) {
            spuAllocMem = SpuMalloc(var_s0);
            if (spuAllocMem == -1) {
                _svm_vab_used[vabId_2] = 0;
                _spu_setInTransfer(0);
                _svm_vab_count -= 1;
                return -1;
            }
        }
        if ((spuAllocMem + var_s0) > 0x80000U) {
        end:
            _svm_vab_used[vabId_2] = 0;

            _spu_setInTransfer(0);
            _svm_vab_count -= 1;
            return -1;
        }
        _svm_vab_start[vabId_2] = spuAllocMem;
        var_s0 = 0;
        for (i = 0; i <= num_vags; i++) {
            var_s0 += vagLens[i];
            if (!(i & 1)) {
                pProgTable[i / 2].reserved2 = (spuAllocMem + var_s0) >> 3;
            } else {
                pProgTable[i / 2].reserved3 = (spuAllocMem + var_s0) >> 3;
            }
        }

        _svm_vab_total[vabId_2] = var_s0;
        _svm_vab_used[vabId_2] = 2;
    } else {
        goto end;
    }
    return vabId_2;
}

extern s32 D_800BE8AC[];
extern s32 SpuSetTransferStartAddr(s32);
extern void _spu_setInTransfer(s32);
s32 SsVabTransBody(s32 addr, s16 vabId) {
    register s32 data asm("s3") = addr;
    register s32 id asm("s2");
    register s32 normalized asm("v0");
    register s32 index asm("s1");
    register s32 transfer asm("s0");
    if ((u16)vabId >= 0x11) {
        goto fail;
    }
    asm("sll %0, %2, 16\n\tsra %1, %0, 16"
        : "=r"(normalized), "=r"(id)
        : "r"(vabId));
    index = id * 4;
    if (D_800B9DE4[id] != 2) {
        goto fail;
    }
    transfer = *(s32 *)((u8 *)D_800BE8F0 + index);
    SpuSetTransferMode(0);
    SpuSetTransferStartAddr(transfer);
    SpuWrite((u8 *)data, *(s32 *)((u8 *)D_800BE8AC + index));
    D_800B9DE4[id] = 1;
    return id;
fail:
    _spu_setInTransfer(0);
    return -1;
}

extern s32 SpuIsTransferCompleted(s32);
s32 SsVabTransCompleted(immediateFlag)
s16 immediateFlag;
{
    return (s16)SpuIsTransferCompleted(immediateFlag);
}

/* SPDX-License-Identifier: MIT */

extern u16 D_800AFD98[];

void SpuVmDamperOff(void) {
    D_800AFD98[0] = 0;
}

/* SPDX-License-Identifier: MIT */
extern u16 D_800AFD98[];
void SpuVmDamperOn(void) {
    D_800AFD98[0] = 2;
}

extern u8 D_800B9DE4[];
extern s32 SpuVmVSetUp(s16, s16);
extern volatile u32 gProgramAttrsRead[];
s16 SsUtGetProgAtr(s16 vabId, s16 progNum, u8 *progatrptr) {
    u32 offset;
    if (D_800B9DE4[vabId] == 1) {
        SpuVmVSetUp(vabId, progNum);
        offset = progNum * 16;
        progatrptr[0] = *((u8 *)(offset + gProgramAttrsRead[0]));
        progatrptr[1] = ((u8 *)gProgramAttrsRead[0])[offset + 1];
        progatrptr[2] = ((u8 *)gProgramAttrsRead[0])[offset + 2];
        progatrptr[3] = ((u8 *)gProgramAttrsRead[0])[offset + 3];
        progatrptr[4] = ((u8 *)gProgramAttrsRead[0])[offset + 4];
        *(u16 *)&progatrptr[6] =
            *(u16 *)&((u8 *)gProgramAttrsRead[0])[offset + 6];
        return 0;
    }
    return -1;
}

typedef struct SpuVmProgEntry {
    u32 word0;
    u32 word4;
    u8 reserved1;
    u8 padding[7];
} SpuVmProgEntry;
extern u8 D_800B9DE4VSetUp[];
extern s16 D_800B60A0VSetUp[];
extern s32 D_800AFA98VSetUp[];
extern s32 D_800AFAD8VSetUp[];
extern s32 D_800AFD9CVSetUp[];
extern u8 D_800B9DC5VSetUp[];
extern u8 D_800B9DCAVSetUp[];
extern s32 D_800B9950VSetUp[];
extern s32 D_800B9930VSetUp[];
extern s32 D_800B9928VSetUp[];
extern u8 D_800B9DCBVSetUp[];
s32 SpuVmVSetUp(s16 vabId, s16 prog) {
    s32 programIndex;
    u16 id;
    register s32 vabVh asm("v1");
    register s32 vabPg asm("a0");
    s32 vabTn;
    SpuVmProgEntry *programs;
    id = vabId;
    if (id >= 16 || D_800B9DE4VSetUp[vabId] != 1 ||
        prog >= D_800B60A0VSetUp[0]) {
        return -1;
    }
    vabVh = D_800AFAD8VSetUp[vabId];
    vabPg = D_800AFA98VSetUp[vabId];
    vabTn = D_800AFD9CVSetUp[vabId];
    D_800B9DC5VSetUp[0] = vabId;
    D_800B9DCAVSetUp[0] = prog;
    D_800B9950VSetUp[0] = vabTn;
    D_800B9930VSetUp[0] = vabVh;
    D_800B9928VSetUp[0] = vabPg;
    programs = (SpuVmProgEntry *)vabPg;
    programIndex = prog;
    D_800B9DCBVSetUp[0] = programs[programIndex].reserved1;
    return 0;
}

s16 SsUtGetVagAtr(s16 vabId, s16 prog, s16 toneNum, VagAtr *vagatrptr) {
    s16 temp_v1;
    if (_svm_vab_used[vabId] == 1) {
        SpuVmVSetUp(vabId, prog);
        temp_v1 = toneNum + _svm_cur.fakeProgram * 0x10;
        vagatrptr->prior = _svm_tn[temp_v1].prior;
        vagatrptr->mode = _svm_tn[temp_v1].mode;
        vagatrptr->vol = _svm_tn[temp_v1].vol;
        vagatrptr->pan = _svm_tn[temp_v1].pan;
        vagatrptr->center = _svm_tn[temp_v1].center;
        vagatrptr->shift = _svm_tn[temp_v1].shift;
        vagatrptr->max = _svm_tn[temp_v1].max;
        vagatrptr->min = _svm_tn[temp_v1].min;
        vagatrptr->vibW = _svm_tn[temp_v1].vibW;
        vagatrptr->vibT = _svm_tn[temp_v1].vibT;
        vagatrptr->porW = _svm_tn[temp_v1].porW;
        vagatrptr->porT = _svm_tn[temp_v1].porT;
        vagatrptr->pbmin = _svm_tn[temp_v1].pbmin;
        vagatrptr->pbmax = _svm_tn[temp_v1].pbmax;
        vagatrptr->adsr1 = _svm_tn[temp_v1].adsr1;
        vagatrptr->adsr2 = _svm_tn[temp_v1].adsr2;
        vagatrptr->prog = _svm_tn[temp_v1].prog;
        vagatrptr->vag = _svm_tn[temp_v1].vag;
        return 0;
    }

    return -1;
}

extern SpuReverbAttr _svm_rattr;

/* libsnd.h declares this void; retail returns the type or -1. */
s16 SsUtSetReverbTypeS16(s16) asm("SsUtSetReverbType");
s16 SsUtSetReverbTypeS16(s16 arg0) {
    s16 var_v1;
    s32 var_a1;

    var_a1 = 0;
    var_v1 = arg0;
    if (arg0 < 0) {
        var_a1 = 1;
        var_v1 = -arg0;
    }

    if ((u16)var_v1 < 10) {
        _svm_rattr.mask = 1;
        if (var_a1 != 0) {
            _svm_rattr.mode = var_v1 | 0x100;
        } else {
            _svm_rattr.mode = var_v1;
        }
        if (var_v1 == 0) {
            SpuSetReverb(0);
        }
        SpuSetReverbModeParam(&_svm_rattr);
        return var_v1;
    }
    return -1;
}

/* SPDX-License-Identifier: MIT */

extern s16 D_800AE280[];

int SsUtGetReverbType(void) {
    return D_800AE280[0];
}

void func_80082B50(void) {
    SpuSetReverb(1);
}

void func_80082B70(void) {
    SpuSetReverb(0);
}

extern SpuReverbAttr D_800AE27C[];

void SsUtSetReverbFeedback(short feedback) {
    D_800AE27C[0].mask = SPU_REV_FEEDBACK;
    D_800AE27C[0].feedback = feedback;
    SpuSetReverbModeParam(D_800AE27C);
}

void SsUtSetReverbDepth(short ldepth, short rdepth) {
    D_800AE27C[0].mask = 6;
    D_800AE27C[0].depth.left = ldepth * 0x7FFF / 0x7F;
    D_800AE27C[0].depth.right = rdepth * 0x7FFF / 0x7F;
    SpuSetReverbModeParam(D_800AE27C);
}

void SsUtSetReverbDelay(short delay) {
    D_800AE27C[0].mask = SPU_REV_DELAYTIME;
    D_800AE27C[0].delay = delay;
    SpuSetReverbModeParam(D_800AE27C);
}

s16 SsUtSetVagAtr(s16 vabId, s16 prog, s16 toneNum, VagAtr *pVagAttr) {
    s16 toneIndex;
    if (_svm_vab_used[vabId] == 1) {
        SpuVmVSetUp(vabId, prog);
        toneIndex = toneNum + _svm_cur.fakeProgram * 0x10;
        _svm_tn[toneIndex].prior = pVagAttr->prior;
        _svm_tn[toneIndex].mode = pVagAttr->mode;
        _svm_tn[toneIndex].vol = pVagAttr->vol;
        _svm_tn[toneIndex].pan = pVagAttr->pan;
        _svm_tn[toneIndex].center = pVagAttr->center;
        _svm_tn[toneIndex].shift = pVagAttr->shift;
        _svm_tn[toneIndex].max = pVagAttr->max;
        _svm_tn[toneIndex].min = pVagAttr->min;
        _svm_tn[toneIndex].vibW = pVagAttr->vibW;
        _svm_tn[toneIndex].vibT = pVagAttr->vibT;
        _svm_tn[toneIndex].porW = pVagAttr->porW;
        _svm_tn[toneIndex].porT = pVagAttr->porT;
        _svm_tn[toneIndex].pbmin = pVagAttr->pbmin;
        _svm_tn[toneIndex].pbmax = pVagAttr->pbmax;
        _svm_tn[toneIndex].adsr1 = pVagAttr->adsr1;
        _svm_tn[toneIndex].adsr2 = pVagAttr->adsr2;
        _svm_tn[toneIndex].prog = pVagAttr->prog;
        _svm_tn[toneIndex].vag = pVagAttr->vag;
        return 0;
    }
    return -1;
}

/* Picks a free voice for a note, or steals the quietest lowest-priority one.
 * Returns spuVmMaxVoice when none can be used. */
u8 SpuVmAllocVoice(s32) asm("SpuVmAlloc");
u8 SpuVmAllocVoice(s32 arg0) {
    u8 var_t2;
    u16 var_t0;
    u16 var_t3;
    u8 cur_voice;
    u8 channel;
    u8 var_t1;
    u16 prior;

    channel = 99;
    var_t3 = -1;
    var_t2 = 0;
    var_t0 = 0;
    prior = _svm_cur.prior;
    var_t1 = 99;
    for (cur_voice = 0; cur_voice < spuVmMaxVoice; cur_voice++) {
        if (_svm_voice[cur_voice].unk1B == 0 &&
            _svm_voice[cur_voice].unk6 == 0) {
            channel = cur_voice;
            break;
        }
        if (_svm_voice[cur_voice].unk18 < prior) {
            prior = _svm_voice[cur_voice].unk18;
            var_t1 = cur_voice;
            var_t3 = _svm_voice[cur_voice].unk6;
            var_t0 = _svm_voice[cur_voice].unk2;
            var_t2 = 1;
        } else if (_svm_voice[cur_voice].unk18 == prior) {
            var_t2 += 1;
            if (_svm_voice[cur_voice].unk6 < var_t3) {
                var_t0 = _svm_voice[cur_voice].unk2;
                var_t3 = _svm_voice[cur_voice].unk6;
                var_t1 = cur_voice;
            } else if (_svm_voice[cur_voice].unk6 == var_t3) {
                if (var_t0 < _svm_voice[cur_voice].unk2) {
                    var_t0 = _svm_voice[cur_voice].unk2;
                    var_t1 = cur_voice;
                }
            }
        }
    }
    if (channel == 99) {
        if (var_t2 == 0) {
            channel = spuVmMaxVoice;
        } else {
            channel = var_t1;
        }
    }
    if (channel < spuVmMaxVoice) {
        for (cur_voice = 0; cur_voice < spuVmMaxVoice; cur_voice++) {
            _svm_voice[cur_voice].unk2++;
        }
        _svm_voice[channel].unk2 = 0;
        _svm_voice[channel].unk18 = _svm_cur.prior;
        if (_svm_voice[channel].unk1B == 2) {
            SpuSetNoiseVoice(0, 0xFFFFFF);
        }
    }
    return channel;
}

/* Matches (0 words) under GNU C 2.6.3-psx only. Retail's codegen needs these
 * spellings:
 * - pos is a u16 (andi 0xFFFF before the shift);
 * - D_800AD224 is the base of the sreg buffer: the pitch store is index
 *   pos + 2, not D_800AD228 + pos;
 * - D_800B1EA4, not D_800B9DD8, is the mono flag;
 * - the voice flag stores go through D_800AD3C0 and D_800AD3D7, so no
 *   voice-table base is shared;
 * - every mask register is read through one symbol and written through a
 *   neighbour symbol (D_800AD9AC[-2] for D_800AD9A8, and so on). A load
 *   and a store of one constant share a single la, which retail doesn't
 *   have. The "on" masks are written first and the "off" masks last. */
void SpuVmKeyOnNow(vagCount, pitch) u8 vagCount;
u16 pitch;
{
    extern s32 D_800B9930[];
    extern u8 D_800B9DC8[];
    extern u8 D_800B9DCE[];
    extern u8 D_800B9DD1[];
    extern u8 D_800B9DD2[];
    extern u8 D_800B9DCF[];
    extern u8 D_800B9DC9[];
    extern u8 D_800B9DD8[];
    extern s16 D_800B9DDA[];
    extern s16 D_800B9DDE[];
    extern struct SeqStruct *D_800BDE3C[];
    extern u16 D_800AD9A8[];
    extern u16 D_800AD9AC[];
    extern u16 D_800AD96C[];
    extern u16 D_800AD970[];
    extern u16 D_800BEB98[];
    extern u16 D_800BEB9C[];
    extern u8 D_800AD3A4[];
    extern u16 D_800AD224[];
    extern u8 D_800AD3C0[];
    extern u8 D_800AD3D7[];
    extern s16 D_800B1EA4[];
    struct SeqStruct *score;
    u16 pos;
    u16 bitsUpper;
    u16 bitsLower;
    u32 voll;
    u32 volr;
    u32 vollT;
    u32 volrT;
    s32 mvolScaled;

    pos = D_800B9DDE[0] * 8;
    mvolScaled = (*(u8 *)((s32)D_800B9930[0] + 0x18)) * 0x3FFF;
    vollT = ((D_800B9DC8[0] * mvolScaled) / 0x7F) / 0x7F;
    vollT = ((vollT * D_800B9DCE[0] * D_800B9DD1[0]) / 0x7F) / 0x7F;
    volrT = vollT;
    score = D_800BDE3C[D_800B9DDA[0] & 0xFF] + ((D_800B9DDA[0] & 0xFF00) >> 8);
    if (D_800B9DDA[0] != 0x21) {
        vollT = (vollT * score->leftVolume) / 0x7F;
        volrT = (volrT * score->rightVolume) / 0x7F;
    }
    if (D_800B9DD2[0] < 0x40) {
        voll = vollT;
        volr = (volrT * D_800B9DD2[0]) / 0x3F;
    } else {
        voll = (vollT * (0x7F - D_800B9DD2[0])) / 0x3F;
        volr = volrT;
    }
    if (D_800B9DCF[0] < 0x40) {
        volr = (volr * D_800B9DCF[0]) / 0x3F;
    } else {
        voll = (voll * (0x7F - D_800B9DCF[0])) / 0x3F;
    }
    if (D_800B9DC9[0] < 0x40) {
        volr = (volr * D_800B9DC9[0]) / 0x3F;
    } else {
        voll = (voll * (0x7F - D_800B9DC9[0])) / 0x3F;
    }
    if (D_800B1EA4[0] == 1) {
        if (voll < volr) {
            voll = volr;
        } else {
            volr = voll;
        }
    }
    voll = (voll * voll) / 0x3FFF;
    volr = (volr * volr) / 0x3FFF;
    D_800AD224[pos + 2] = pitch;
    D_800AD224[pos + 0] = voll;
    D_800AD224[pos + 1] = volr;
    D_800AD3A4[D_800B9DDE[0]] |= 7;
    *(u16 *)(D_800AD3C0 + D_800B9DDE[0] * 52) = pitch;
    D_800AD3D7[D_800B9DDE[0] * 52] = 1;
    if (D_800B9DDE[0] < 0x10) {
        bitsLower = 1 << D_800B9DDE[0];
        bitsUpper = 0;
    } else {
        bitsLower = 0;
        bitsUpper = 1 << (D_800B9DDE[0] - 0x10);
    }
    if (D_800B9DD8[0] & 4) {
        ((u16 *)D_800AD9AC)[-2] = D_800AD9A8[0] | bitsLower;
        ((u16 *)D_800AD9A8)[2] = D_800AD9AC[0] | bitsUpper;
    } else {
        ((u16 *)D_800AD9AC)[-2] = D_800AD9A8[0] & ~bitsLower;
        ((u16 *)D_800AD9A8)[2] = D_800AD9AC[0] & ~bitsUpper;
    }
    ((u16 *)D_800AD970)[-2] = D_800AD96C[0] | bitsLower;
    ((u16 *)D_800AD96C)[2] = D_800AD970[0] | bitsUpper;
    ((u16 *)D_800BEB9C)[-2] = D_800BEB98[0] & ~((u16 *)D_800AD970)[-2];
    ((u16 *)D_800BEB98)[2] = D_800BEB9C[0] & ~((u16 *)D_800AD96C)[2];
}

void SpuVmDoAllocate(void) {
    s32 i;

    _svm_cur.regOff = _svm_cur.voice * 8;
    _svm_cur.toneOff = _svm_cur.vagIdx + (_svm_cur.fakeProgram * 0x10);
    _svm_voice[_svm_cur.voice].unk6 = 0x7FFF;
    for (i = 0; i < 0x10; i++) {
        _svm_envx_hist[i] &= ~(1 << _svm_cur.voice);
    }
    if ((_svm_cur.voiceIdx & 1) > 0) {
        _svm_sreg_buf[_svm_cur.regOff + 3] =
            _svm_pg[(_svm_cur.voiceIdx - 1) / 2].reserved2;
        _svm_sreg_dirty[_svm_cur.voice] |= 8;
    } else {
        _svm_sreg_buf[_svm_cur.regOff + 3] =
            _svm_pg[(_svm_cur.voiceIdx - 1) / 2].reserved3;
        _svm_sreg_dirty[_svm_cur.voice] |= 8;
    }

    _svm_sreg_buf[_svm_cur.regOff + 4] =
        _svm_tn[(_svm_cur.fakeProgram * 0x10) + _svm_cur.vagIdx].adsr1;
    _svm_sreg_buf[_svm_cur.regOff + 5] =
        _svm_tn[(_svm_cur.fakeProgram * 0x10) + _svm_cur.vagIdx].adsr2 +
        _svm_damper;
    _svm_sreg_dirty[_svm_cur.voice] |= 0x30;
}

void vmNoiseOn(arg0) u8 arg0;
{
    struct SeqStruct *score = &D_800BDE3C[_svm_cur.vagIdx16 & 0xFF]
                                         [(_svm_cur.vagIdx16 & 0xFF00) >> 8];
    s16 voice;
    u16 bitsUpper;
    u16 bitsLower;
    u32 voll_t, volr_t;
    u32 voll, volr;
    u16 cnd;
    u32 temp;

    cnd = _svm_spuBase[0x1AA / 2];

    voll_t = score->leftVolume * 0x81;
    volr_t = score->rightVolume * 0x81;

    voll_t = (voll_t * _svm_cur.mvol) / 0x7F;
    volr_t = (volr_t * _svm_cur.mvol) / 0x7F;

    voll_t = (voll_t * _svm_cur.vol) / 0x7F;
    volr_t = (volr_t * _svm_cur.vol) / 0x7F;

    temp = _svm_cur.pan;
    if (temp < 0x40) {
        voll = voll_t;
        volr = (volr_t * temp) / 0x3F;
    } else {
        voll = (voll_t * (0x7F - temp)) / 0x3F;
        volr = volr_t;
    }
    temp = _svm_cur.mpan;
    if (temp < 0x40) {
        volr = (volr * temp) / 0x3F;
    } else {
        voll = (voll * (0x7F - temp)) / 0x3F;
    }
    temp = _svm_cur.field5;
    if (temp < 0x40) {
        volr = (temp * volr) / 0x3F;
    } else {
        voll = (voll * (0x7F - temp)) / 0x3F;
    }

    if (_svm_stereo_mono == 1) {
        if (voll < volr) {
            voll = volr;
        } else {
            volr = voll;
        }
    }

    cnd &= ~0x3F00;
    cnd |= ((_svm_cur.note - _svm_cur.centre) & 0x3F) << 8;
    _svm_spuBase[0x1AA / 2] = cnd;

    _svm_sreg_buf[arg0 * 8 + 0] = voll;
    _svm_sreg_buf[arg0 * 8 + 1] = volr;
    _svm_sreg_dirty[arg0] |= 3;
    if (arg0 < 0x10) {
        bitsLower = 1 << arg0;
        bitsUpper = 0;
    } else {
        bitsLower = 0;
        bitsUpper = 1 << (arg0 - 0x10);
    }
    _svm_voice[arg0].unk4 = 0xA;
    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        _svm_voice[voice].unk1B &= 1;
    }
    _svm_voice[arg0].unk1B = 2;

    _svm_okon1 |= bitsLower;
    _svm_okon2 |= bitsUpper;

    _svm_okof1 &= ~_svm_okon1;
    _svm_okof2 &= ~_svm_okon2;

    if (_svm_cur.seqSepNo & 4) {
        _svm_orev1 |= bitsLower;
        _svm_orev2 |= bitsUpper;
    } else {
        _svm_orev1 &= ~bitsLower;
        _svm_orev2 &= ~bitsUpper;
    }

    _svm_spuBase[0x194 / 2] = bitsLower;
    _svm_spuBase[0x196 / 2] = bitsUpper;
}

void vmNoiseOn2Impl(u8, u16, u16, u16, u16) asm("vmNoiseOn2");
void vmNoiseOn2Impl(u8 voice, u16 arg1, u16 arg2, u16 arg3, u16 arg4) {
    u16 i;
    u16 bitsUpper;
    u16 bitsLower;

    _svm_sreg_buf[voice * 8 + 0] = arg1;
    _svm_sreg_buf[voice * 8 + 1] = arg2;
    _svm_sreg_dirty[voice] |= 3;

    if (voice < 0x10) {
        bitsLower = 1 << voice;
        bitsUpper = 0;
    } else {
        bitsLower = 0;
        bitsUpper = 1 << (voice - 0x10);
    }

    _svm_voice[voice].unk4 = 0xA;
    for (i = 0; i < spuVmMaxVoice; i++) {
        _svm_voice[i].unk1B &= 1;
    }
    _svm_voice[voice].unk1B = 2;
    _svm_voice[voice].unk2 = 0;

    _svm_okon1 |= bitsLower;
    _svm_okon2 |= bitsUpper;

    _svm_okof1 &= ~_svm_okon1;
    _svm_okof2 &= ~_svm_okon2;
    _svm_spuBase[0x194 / 2] = bitsLower;
    _svm_spuBase[0x196 / 2] = bitsUpper;
}

extern u8 D_800B9DC6[];
extern u8 D_800B9DD4[];
extern u8 D_800B9DD5[];
extern u16 D_800A20BC[];
u16 note2pitch(void) {
    s16 new_var;
    s16 octave;
    s16 pos;
    u16 var_a2;
    u16 var_v1;
    new_var = (D_800B9DC6[0] + 60) - D_800B9DD4[0];
    octave = new_var / 12;
    pos = new_var % 12;
    var_a2 = D_800B9DD5[0] / 8;
    if (var_a2 > 15) {
        var_a2 = 15;
    }
    var_v1 = D_800A20BC[(pos * 16) + var_a2];
    do {
        octave -= 5;
        if (octave > 0) {
            var_v1 <<= octave;
        } else if (octave < 0) {
            var_v1 >>= -octave;
        }
    } while (0);
    return var_v1;
}

extern u8 D_800B9DCB[];
extern u8 D_800B9DD0[];
extern u8 D_800B9950Raw[] asm("D_800B9950");
extern u16 D_800A20BC[];
s32 note2pitch2(arg0, arg1)
u16 arg0;
u16 arg1;
{
    s32 pos;
    s16 new_var;
    s16 var_a3;
    s16 var_a2;
    s16 octave;
    u16 var_v1;
    var_a3 =
        (arg1 +
         ((u8 *)*(u32 *)
              D_800B9950Raw)[(D_800B9DD0[0] + (D_800B9DCB[0] << 4)) * 0x20 +
                             5]) /
        8;
    var_a2 = 0;
    if (var_a3 >= 16) {
        var_a2 = 1;
        var_a3 -= 16;
    }
    new_var =
        arg0 + 60 -
        ((u8 *)*(u32 *)
             D_800B9950Raw)[(D_800B9DD0[0] + (D_800B9DCB[0] << 4)) * 0x20 + 4] +
        var_a2;
    octave = new_var / 12;
    pos = (new_var % 12) * 16;
    var_v1 = D_800A20BC[pos + var_a3];
    octave -= 5;
    if (octave > 0)
        var_v1 <<= octave;
    else if (octave < 0)
        var_v1 >>= -octave;
    return var_v1;
}

void SePitchBend(u8 voice, s16 arg1) {
    extern u8 D_800AD3CC[];
    extern u8 D_800AD3D0[];
    extern u16 D_800AD3C8[];
    extern u8 D_800AD3A4[];
    extern u8 D_800B9DCB[];
    extern u8 D_800B9DD0[];
    extern u16 D_800B9DDE[];
    extern u32 D_800B9950[];
    extern u16 D_800AD224[];
    extern s32 note2pitch2();
    s32 tone;
    u16 note;
    u16 pbend;
    s32 pos;

    pos = voice * 8;
    if (voice >= 0 && voice < 24) {
        D_800B9DCB[0] = D_800AD3CC[(s32)voice * 52];
        D_800B9DD0[0] = D_800AD3D0[(s32)voice * 52];
        D_800B9DDE[0] = voice;
        tone = D_800B9DCB[5] + D_800B9DCB[0] * 16;
        if (arg1 >= 0) {
            note =
                D_800AD3C8[(s32)voice * 26] +
                (arg1 * *(u8 *)((s32)D_800B9950[0] + tone * 32 + 0xD)) / 0x7F;
            pbend =
                (arg1 * *(u8 *)((s32)D_800B9950[0] + tone * 32 + 0xD)) % 0x7F;
        } else {
            note = (D_800AD3C8[(s32)voice * 26] +
                    (arg1 * *(u8 *)((s32)D_800B9950[0] + tone * 32 + 0xC)) /
                        0x7F) -
                   1;
            pbend = ((arg1 * *(u8 *)((s32)D_800B9950[0] + tone * 32 + 0xC)) /
                     0x7F) +
                    0x7F;
        }
        D_800AD224[pos + 2] = note2pitch2(note, pbend);
        D_800AD3A4[voice] |= 4;
    }
}

void SsUtVibrateOn(void) {
}

void SsUtVibrateOff(void) {
}

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s8 unk18[0x1C];
} AutoSweep;

extern AutoSweep D_800AD3D8[];

void SeAutoVol(s16 seq_access, s16 vol1, s16 vol2, s16 mSec) {
    s32 m;
    s32 q;

    if (vol1 != vol2) {
        D_800AD3D8[seq_access].unk0 = 1;
        D_800AD3D8[seq_access].unk8 = vol1;
        D_800AD3D8[seq_access].unkA = vol2;
        m = mSec;
        if (vol1 - vol2 >= 0) {
            if (vol1 - vol2 < m) {
                goto fast;
            }
            goto slow;
        }
        if (vol2 - vol1 < m) {
        fast:
            q = mSec / (vol1 - vol2);
            D_800AD3D8[seq_access].unk2 = 1;
            D_800AD3D8[seq_access].unk4 = q;
            D_800AD3D8[seq_access].unk6 = q;
            return;
        }
    slow:
        D_800AD3D8[seq_access].unk4 = 0;
        D_800AD3D8[seq_access].unk2 = (vol1 - vol2) / mSec;
    }
}

void SetAutoVol(s16 voice) {
    s16 temp_v1_3;
    u32 voll_t, volr_t;
    u16 voll, volr;
    s16 pos;
    s32 mvol_scaled;

    pos = voice * 8;
    if (_svm_voice[voice].unk20 != 0) {
        if (_svm_voice[voice].unk22-- > 0) {
            return;
        }
        _svm_voice[voice].unk22 = _svm_voice[voice].unk20;
    }
    _svm_voice[voice].startVol += _svm_voice[voice].unk1E;
    if (_svm_voice[voice].unk1E > 0) {
        if (_svm_voice[voice].startVol >= _svm_voice[voice].endVol) {
            _svm_voice[voice].startVol = _svm_voice[voice].endVol;
            _svm_voice[voice].autoVol = 0;
        }
    } else if (_svm_voice[voice].unk1E < 0) {
        if (_svm_voice[voice].startVol <= _svm_voice[voice].endVol) {
            _svm_voice[voice].startVol = _svm_voice[voice].endVol;
            _svm_voice[voice].autoVol = 0;
        }
    }
    temp_v1_3 = _svm_voice[voice].startVol;
    _svm_cur.voll = temp_v1_3;
    mvol_scaled = _svm_vh->mvol * 0x3FFF;

    voll_t = ((temp_v1_3 * mvol_scaled) / 0x7F) / 0x7F;
    volr_t = ((temp_v1_3 * mvol_scaled) / 0x7F) / 0x7F;

    voll_t = ((voll_t * _svm_cur.mvol * _svm_cur.vol) / 0x7F) / 0x7F;
    volr_t = ((volr_t * _svm_cur.mvol * _svm_cur.vol) / 0x7F) / 0x7F;

    if (_svm_cur.pan < 0x40) {
        voll = voll_t;
        volr = (volr_t * _svm_cur.pan) / 0x40;
    } else {
        voll = (voll_t * (0x7F - _svm_cur.pan)) / 0x40;
        volr = volr_t;
    }

    if (_svm_cur.mpan < 0x40) {
        volr = (volr * _svm_cur.mpan) / 0x40;
    } else {
        voll = (voll * (0x7F - _svm_cur.mpan)) / 0x40;
    }

    if (_svm_cur.field5 < 0x40) {
        volr = (volr * _svm_cur.field5) / 0x40;
    } else {
        voll = (voll * (0x7F - _svm_cur.field5)) / 0x40;
    }

    if (_svm_stereo_mono == 1) {
        if (volr > voll) {
            voll = volr;
        } else {
            volr = voll;
        }
    }
    _svm_sreg_buf[pos + 0] = voll;
    _svm_sreg_buf[pos + 1] = volr;
    _svm_sreg_dirty[voice] |= 3;
}

void SeAutoPan(s16 seq_access, s16 pan1, s16 pan2, s16 mSec) {
    s32 m;
    s32 q;

    if (pan1 != pan2) {
        D_800AD3D8[seq_access].unkC = 1;
        D_800AD3D8[seq_access].unk14 = pan1;
        D_800AD3D8[seq_access].unk16 = pan2;
        m = mSec;
        if (pan1 - pan2 >= 0) {
            if (pan1 - pan2 < m) {
                goto fast;
            }
            goto slow;
        }
        if (pan2 - pan1 < m) {
        fast:
            q = mSec / (pan1 - pan2);
            D_800AD3D8[seq_access].unkE = 1;
            D_800AD3D8[seq_access].unk10 = q;
            D_800AD3D8[seq_access].unk12 = q;
            return;
        }
    slow:
        D_800AD3D8[seq_access].unk10 = 0;
        D_800AD3D8[seq_access].unkE = (pan1 - pan2) / mSec;
    }
}

void SetAutoPan(s16 voice) {
    u32 voll_t, volr_t;
    u16 voll, volr;
    s16 pos;
    char new_var;
    u16 new_var2;
    s32 mvol_scaled;

    pos = voice * 8;
    if (_svm_voice[voice].unk2C != 0) {
        if (_svm_voice[voice].unk2E-- > 0) {
            return;
        }
        _svm_voice[voice].unk2E = _svm_voice[voice].unk2C;
    }
    _svm_voice[voice].startPan += _svm_voice[voice].unk2A;
    if (_svm_voice[voice].unk2A > 0) {
        if (_svm_voice[voice].startPan >= _svm_voice[voice].endPan) {
            _svm_voice[voice].startPan = _svm_voice[voice].endPan;
            _svm_voice[voice].autoPan = 0;
        }
    } else if (_svm_voice[voice].unk2A < 0) {
        if (_svm_voice[voice].startPan <= _svm_voice[voice].endPan) {
            _svm_voice[voice].startPan = _svm_voice[voice].endPan;
            _svm_voice[voice].autoPan = 0;
        }
    }
    new_var = _svm_voice[voice].startPan;
    _svm_cur.field5 = new_var;
    mvol_scaled = _svm_vh->mvol * 0x3FFF;

    voll_t = ((_svm_cur.voll * mvol_scaled) / 0x7F) / 0x7F;
    volr_t = ((_svm_cur.voll * mvol_scaled) / 0x7F) / 0x7F;

    voll_t = ((voll_t * _svm_cur.mvol * _svm_cur.vol) / 0x7F) / 0x7F;
    volr_t = ((volr_t * _svm_cur.mvol * _svm_cur.vol) / 0x7F) / 0x7F;

    if (_svm_cur.pan < 0x40) {
        voll = voll_t;
        volr = (volr_t * _svm_cur.pan) / 0x40;
    } else {
        voll = (voll_t * (0x7F - _svm_cur.pan)) / 0x40;
        volr = volr_t;
    }

    if (_svm_cur.mpan < 0x40) {
        volr = (volr * _svm_cur.mpan) / 0x40;
    } else {
        voll = (voll * (0x7F - _svm_cur.mpan)) / 0x40;
    }
    new_var2 = new_var;
    if (new_var2 < 0x40) {
        volr = (volr * new_var2) / 0x40;
    } else {
        voll = (voll * (0x7F - new_var2)) / 0x40;
    }

    if (_svm_stereo_mono == 1) {
        if (volr > voll) {
            voll = volr;
        } else {
            volr = voll;
        }
    }
    _svm_sreg_buf[pos + 0] = voll;
    _svm_sreg_buf[pos + 1] = volr;
    _svm_sreg_dirty[voice] |= 3;
}

void SpuVmInit(u8 arg0) {
    u16 temp_v1;
    u16 var_a1;
    u16 *temp_a0;
    s32 var_a0;
    u16 bitsUpper;
    u16 bitsLower;
    u16 temp;
    _spu_setInTransfer(0);
    _svm_vcf = 0;
    _svm_damper = 0;
    SpuInitMalloc(0x20, _ss_spu_vm_rec);
    for (var_a1 = 0; var_a1 < 8 * 24; var_a1++) {
        _svm_sreg_buf[var_a1] = 0;
    }
    for (var_a1 = 0; var_a1 < 24; var_a1++) {
        _svm_sreg_dirty[var_a1] = 0;
    }

    _svm_vab_count = 0;

    for (var_a1 = 0; var_a1 < 16; var_a1++) {
        _svm_vab_used[var_a1] = 0;
    }

    var_a0 = arg0;
    if (arg0 >= 24) {
        spuVmMaxVoice = 24;
    } else {
        spuVmMaxVoice = var_a0;
    }
    for (var_a1 = 0; var_a1 < spuVmMaxVoice; var_a1++) {
        temp = var_a1 * 8;
        _svm_voice[var_a1].unk2 = 0x18;
        _svm_voice[var_a1].unkE = -1;
        _svm_voice[var_a1].unk0 = 0xFF;
        _svm_voice[var_a1].unk1B = 0;
        _svm_voice[var_a1].unk4 = 0;
        _svm_voice[var_a1].unk6 = 0;
        _svm_voice[var_a1].unk10 = 0;
        _svm_voice[var_a1].prog = 0;
        _svm_voice[var_a1].tone = 0xff;
        _svm_voice[var_a1].unk8 = 0;
        _svm_voice[var_a1].unkA = 0x40;
        _svm_voice[var_a1].autoVol = 0;
        _svm_voice[var_a1].unk1E = 0;
        _svm_voice[var_a1].unk20 = 0;
        _svm_voice[var_a1].unk22 = 0;
        _svm_voice[var_a1].autoPan = 0;
        _svm_voice[var_a1].unk2A = 0;
        _svm_voice[var_a1].unk2C = 0;
        _svm_voice[var_a1].unk2E = 0;
        _svm_voice[var_a1].startPan = 0;
        _svm_voice[var_a1].startVol = 0;

        temp_a0 = &_svm_spuBase[temp];
        temp_a0[3] = 0x200;
        temp_a0[2] = 0x1000;
        temp_a0[4] = 0x80FF;
        temp_a0[0] = 0;
        temp_a0[1] = 0;
        temp_a0[5] = 0x4000;

        _svm_cur.voice = var_a1;
        temp_v1 = GetSvmVoice();
        if (temp_v1 < 0x10) {
            bitsLower = 1 << temp_v1;
            bitsUpper = 0;
        } else {
            bitsLower = 0;
            bitsUpper = 1 << (temp_v1 - 0x10);
        }

        _svm_voice[temp_v1].unk1B = 0;
        _svm_voice[temp_v1].unk4 = 0;
        _svm_voice[temp_v1].unk0 = 0;

        _svm_okof1 |= bitsLower;
        _svm_okof2 |= bitsUpper;

        _svm_okon1 &= ~_svm_okof1;
        _svm_okon2 &= ~_svm_okof2;
    }
    _svm_rattr.depth.left = 0x3FFF;
    _svm_rattr.depth.right = 0x3FFF;
    _svm_okon1 = 0;
    _svm_okon2 = 0;
    _svm_okof1 = 0;
    _svm_orev1 = 0;
    _svm_orev2 = 0;
    _svm_rattr.mask = 0;
    _svm_rattr.mode = 0;
    _svm_auto_kof_mode = 0;
    _svm_stereo_mono = 0;
    kMaxPrograms = 0x80;
    SpuVmFlush();
}

extern u8 D_800B9DD3[];
extern u8 D_800B9C80[];
typedef struct SpuVmVoiceSlot {
    u16 voice;
    s32 padding[2];
} SpuVmVoiceSlot;
extern SpuVmVoiceSlot D_800B9DDERead;
extern SpuVmVoiceSlot D_800B9DDEWrite;
extern s32 SpuVmAlloc();
extern s32 vmNoiseOn2(s32, s32, s32, s32, s32);
void SpuVmNoiseOnWithAdsr(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 voice;
    D_800B9DD3[0] = 0x7F;
    voice = SpuVmAlloc(0xFF);
    voice &= 0xFF;
    D_800B9DDEWrite.voice = voice;
    if (voice < D_800B9C80[0]) {
        vmNoiseOn2(*(u8 *)&D_800B9DDERead.voice, arg0 & 0xFFFF, arg1 & 0xFFFF,
                   arg2 & 0xFFFF, arg3 & 0xFFFF);
    }
}

extern u8 D_800B9C80Start[];
extern u8 D_800B9C80Loop[];
extern u8 D_800AD3D7Read[];
extern u8 D_800AD3D7Write[];
extern u8 D_800AD3C0Write[];
typedef struct SpuPointerStorage {
    u32 pointer;
    s32 padding[2];
} SpuPointerStorage;
extern SpuPointerStorage D_800A20B8Read;
void SpuVmNoiseOff(void) {
    s32 status;
    s16 i;
    s32 index;
    u16 *spu;
    i = 0;
    if (D_800B9C80Start[0] == 0) {
        return;
    }
    status = 2;
again:
    if (D_800AD3D7Read[(s32)i * 52] == status) {
        index = (u8)i * 52;
        D_800AD3D7Write[index] = 0;
        spu = (u16 *)D_800A20B8Read.pointer;
        *(u16 *)(D_800AD3C0Write + index) = 0;
        spu[0x194 / 2] = 0;
        spu[0x196 / 2] = 0;
    }
    i++;
    if (i < D_800B9C80Loop[0]) {
        goto again;
    }
}

extern u8 D_800B9DD3[];
extern u8 D_800B9C80[];
extern SpuVmVoiceSlot D_800B9DDERead;
extern SpuVmVoiceSlot D_800B9DDEWrite;
extern s32 SpuVmAlloc();
extern s32 vmNoiseOn2(s32, s32, s32, s32, s32);
void SpuVmNoiseOn(s32 arg0, s32 arg1) {
    s32 voice;
    D_800B9DD3[0] = 0x7F;
    voice = SpuVmAlloc(0xFF);
    voice &= 0xFF;
    D_800B9DDEWrite.voice = voice;
    if (voice < D_800B9C80[0]) {
        vmNoiseOn2(*(u8 *)&D_800B9DDERead.voice, arg0 & 0xFFFF, arg1 & 0xFFFF,
                   0x80FF, 0x5FC8);
    }
}

s16 SpuVmPBVoiceDraft(s16, s16, s16, s16, u16) asm("SpuVmPBVoice");
s16 SpuVmPBVoiceDraft(s16 voice, s16 seq_sep_no, s16 vabId, s16 program,
                      u16 amount) {
    struct SpuVoice {
        s16 unk0;
        s16 unk2;
        s16 unk04;
        u16 unk6;
        s16 unk8;
        char unka;
        char unkb;
        s16 note;
        s16 unke;
        s16 unk10;
        s16 prog;
        s16 tone;
        s16 vabId;
        s16 unk18;
        u8 pad[1];
        u8 unk1b;
        s16 tail[12];
    };
    extern u8 D_800AD3BC[];
    extern u8 D_800B9DCB[];
    extern u16 D_800B9DDE[];
    extern u8 D_800B9DD0[];
    extern u16 D_800AD224[];
    extern u8 D_800AD3C8[];
    extern u8 D_800AD3CA[];
    extern u8 D_800AD3CE[];
    extern u8 D_800AD3D0[];
    extern u8 D_800AD3D2[];
    extern u8 D_800AD3A4[];
    extern s32 D_800B9950[];
    extern s32 note2pitch2();
    struct SpuVoice *voiceData;
    s16 temp_t1;
    u16 temp_v1;
    u16 pbend;
    u16 temp_a1;
    u16 note;

    voiceData = (struct SpuVoice *)D_800AD3BC;
    temp_t1 = amount - 0x40;
    if (*(s16 *)(D_800AD3CA + voice * 52) == seq_sep_no &&
        *(s16 *)(D_800AD3D2 + voice * 52) == vabId &&
        *(s16 *)(D_800AD3CE + voice * 52) == program) {
        temp_a1 = *(u16 *)(D_800AD3C8 + voice * 52);
        temp_v1 = *(u16 *)(D_800AD3D0 + voice * 52) + (D_800B9DCB[0] * 0x10);
        if (temp_t1 > 0) {
            do {
                note = *(u16 *)(D_800AD3C8 + voice * 52) +
                       ((temp_t1 *
                         *(u8 *)((s32)D_800B9950[0] + temp_v1 * 32 + 0xD)) /
                        0x3F);
            } while (0);
            pbend =
                ((temp_t1 * *(u8 *)((s32)D_800B9950[0] + temp_v1 * 32 + 0xD)) %
                 0x3F) *
                2;
        } else {
            note = temp_a1;
            if (temp_t1 < 0) {
                note = ((temp_t1 *
                         *(u8 *)((s32)D_800B9950[0] + temp_v1 * 32 + 0xC)) /
                        0x40);
                note = (temp_a1 + note) - 1;
                pbend = (((temp_t1 *
                           *(u8 *)((s32)D_800B9950[0] + temp_v1 * 32 + 0xC)) %
                          0x40) *
                         2) +
                        0x7F;
            } else {
                pbend = 0;
            }
        }
        D_800B9DD0[0] = D_800AD3D0[voice * 52];
        D_800B9DDE[0] = voice;
        D_800AD224[voice * 8 + 2] = note2pitch2(note, pbend);
        D_800AD3A4[voice] |= 4;
        return 1;
    }
    return 0;
}

s32 SpuVmPBVoice(s16, s16, s16, s16, u16);

#ifdef NON_MATCHING
/* 2026-10-17: the donor body is 240 bytes. This draft has the size but 22
 * rows differ: retail stores _svm_cur.vagIdx16 after the SpuVmVSetUp call
 * through a copy of arg0 (move v0,s2), and puts voice in s0 and the sum in
 * s1. */
s32 SpuVmPitchBend(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 var_s1;
    s16 voice;

    _svm_cur.vagIdx16 = arg0;
    SpuVmVSetUp(arg1, arg2);
    var_s1 = 0;
    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        var_s1 += (s16)SpuVmPBVoice(voice, arg0, arg1, arg2, arg3);
    }
    return var_s1;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmPitchBend);
#endif

void SpuVmFlush(void) {
    u32 env_mask;
    s32 i;

    _svm_envx_idx = (_svm_envx_idx + 1) & 0xF;
    _svm_envx_hist[_svm_envx_idx] = 0;

    for (i = 0; i < spuVmMaxVoice; i++) {
        _svm_voice[i].unk6 = _svm_spuBase[i * 8 + 6];
        if (_svm_voice[i].unk6 == 0) {
            _svm_envx_hist[_svm_envx_idx] |= 1 << i;
        }
    }
    if (_svm_auto_kof_mode == 0) {
        env_mask = 0xFFFFFFFF;
        for (i = 0; i < 0xF; i++) {
            env_mask &= _svm_envx_hist[i];
        }

        for (i = 0; i < spuVmMaxVoice; i++) {
            if (env_mask & (1 << i)) {
                if (_svm_voice[i].unk1B == 2) {
                    SpuSetNoiseVoice(0, 0xFFFFFF);
                }
                _svm_voice[i].unk1B = 0;
            }
        }
    }

    _svm_okon1 &= ~_svm_okof1;
    _svm_okon2 &= ~_svm_okof2;
    for (i = 0; i < 24; i++) {
        if (_svm_voice[i].autoVol != 0) {
            SetAutoVol(i);
        }
        if (_svm_voice[i].autoPan != 0) {
            SetAutoPan(i);
        }
    }

    for (i = 0; i < 24; i++) {
        if (_svm_sreg_dirty[i] & 1) {
            _svm_spuBase[i * 8 + 0] = _svm_sreg_buf[i * 8 + 0];
            _svm_spuBase[i * 8 + 1] = _svm_sreg_buf[i * 8 + 1];
        }
        if (_svm_sreg_dirty[i] & 4) {
            _svm_spuBase[i * 8 + 2] = _svm_sreg_buf[i * 8 + 2];
        }
        if (_svm_sreg_dirty[i] & 8) {
            _svm_spuBase[i * 8 + 3] = _svm_sreg_buf[i * 8 + 3];
        }
        if (_svm_sreg_dirty[i] & 0x10) {
            _svm_spuBase[i * 8 + 4] = _svm_sreg_buf[i * 8 + 4];
            _svm_spuBase[i * 8 + 5] = _svm_sreg_buf[i * 8 + 5];
        }
        _svm_sreg_dirty[i] = 0;
    }

    _svm_spuBase[0x18C / 2] = _svm_okof1;
    _svm_spuBase[0x18E / 2] = _svm_okof2;
    _svm_spuBase[0x188 / 2] = _svm_okon1;
    _svm_spuBase[0x18A / 2] = _svm_okon2;
    _svm_spuBase[0x198 / 2] = _svm_orev1;
    _svm_spuBase[0x19A / 2] = _svm_orev2;
    _svm_okof1 = 0;
    _svm_okof2 = 0;
    _svm_okon1 = 0;
    _svm_okon2 = 0;
}

struct KeyState {
    u8 toneCount;
    u8 vabId;
    u8 note;
    u8 fine;
    u8 volume;
    u8 pan;
    u8 prog;
    u8 fakeProg;
    u8 unk8[2];
    u8 progVolume;
    u8 progPan;
    u8 tone;
    u8 toneVolume;
    u8 tonePan;
    u8 priority;
    u8 center;
    u8 shift;
    u8 minNote;
    u8 maxNote;
    u8 mode;
    u8 unk15;
    s16 seq;
    u16 vag;
    s16 voice;
};
s32 SpuVmKeyOn(seq, vabId, prog, note, volume, pan)
s16 seq;
s16 vabId;
s16 prog;
u16 note;
u16 volume;
u16 pan;
{

    extern struct KeyState keyState[] asm("D_800B9DC4");
    extern s16 D_800B9DDA[];
    extern u8 D_800B9DC6[];
    extern u8 D_800B9DC7[];
    extern u8 D_800B9DC8[];
    extern u8 D_800B9DC9[];
    extern u8 D_800B9DCE[];
    extern u8 D_800B9DCF[];
    extern u8 D_800B9DC4[];
    extern u8 keyToneCountRead[] asm("D_800B9DC4");
    extern u8 D_800B9DCB[];
    extern u8 D_800B9928[];
    extern u8 D_800B9930[];
    extern u8 D_800B9950[];
    extern u8 D_800B9C80[];
    extern u8 D_800AD3BC[];
    extern u8 D_800AD3BE[];
    extern u8 D_800AD3C4[];
    extern u8 D_800AD3C6[];
    extern u8 D_800AD3C8[];
    extern u8 D_800AD3CA[];
    extern u8 D_800AD3CC[];
    extern u8 D_800AD3CE[];
    extern u8 D_800AD3D0[];
    extern u8 D_800AD3D2[];
    extern u8 D_800AD3D4[];
    extern u8 D_800AD3D7[];
    extern s32 SpuVmAlloc();
    extern s32 keyOff(s16, s16, s16, u16) asm("SpuVmKeyOff");
    extern void vmNoiseOn();
    u8 vags[128];
    u8 tones[128];
    s32 mask;
    u8 tone;
    s32 count;
    u32 vagCount;
    u8 i;
    s16 voice;
    s32 selected;
    s32 oldCount;
    u8 *progAttr;
    u8 *vagList;
    u8 *toneList;
    u8 *toneAttr;
    u8 *selectedTone;
    u8 *voiceLimit;
    struct SeqStruct *score;

    mask = 0;
    score = &D_800BDE3C[seq & 0xFF][(seq >> 8) & 0xFF];
    if (SpuVmVSetUp(vabId, prog) != 0) {
        return -1;
    }
    D_800B9DDA[0] = seq;
    D_800B9DC6[0] = note;
    D_800B9DC7[0] = 0;
    if (seq == 0x21) {
        D_800B9DC8[0] = volume;
    } else {
        D_800B9DC8[0] = volume * score->vol[score->channel] / 127;
    }
    D_800B9DC9[0] = pan;
    progAttr = (u8 *)(prog * 16 + *(s32 *)D_800B9928);
    D_800B9DCE[0] = progAttr[1];
    D_800B9DCF[0] = progAttr[4];
    D_800B9DC4[0] = progAttr[0];
    if (D_800B9DCB[0] >= *(u16 *)(*(u8 **)D_800B9930 + 0x12)) {
        return -1;
    }
    if (volume == 0) {
        mask = keyOff(seq, vabId, prog, note & 0xFFFF);
    } else {
        count = 0;
        toneList = tones;
        vagList = vags;
        tone = 0;
        if (tone >= keyToneCountRead[0]) {
            goto tonesDone;
        }
    findTone:
        {
            toneAttr =
                (u8 *)(((D_800B9DCB[0] * 16 + tone) << 5) + *(s32 *)D_800B9950);
            if (toneAttr[6] <= D_800B9DC6[0] && toneAttr[7] >= D_800B9DC6[0]) {
                selected = (u8)count;
                oldCount = count;
                count++;
                vagList[selected] = toneAttr[0x16];
                toneList[(u8)oldCount] = tone;
            }
        }
        do {
            tone++;
            if (tone < D_800B9DC4[0]) {
                goto findTone;
            }
        } while (0);
    tonesDone:
        {
            /* Keep the count in v0 for the copy and first loop test. */
            register u32 narrowedCount asm("v0");
            narrowedCount = (u8)count;
            vagCount = narrowedCount;
            asm("" : "=r"(narrowedCount) : "0"(narrowedCount));
            i = 0;
            if (narrowedCount != 0) {
                do {
                    keyState[0].vag = vags[(u8)i];
                    keyState[0].tone = tones[(u8)i];
                    selectedTone =
                        (u8 *)(((keyState[0].tone + keyState[0].fakeProg * 16)
                                << 5) +
                               *(s32 *)D_800B9950);
                    keyState[0].priority = selectedTone[0];
                    keyState[0].toneVolume = selectedTone[2];
                    keyState[0].tonePan = selectedTone[3];
                    keyState[0].center = selectedTone[4];
                    voiceLimit = D_800B9C80;
                    keyState[0].shift = selectedTone[5];
                    keyState[0].mode = selectedTone[1];
                    keyState[0].minNote = selectedTone[6];
                    keyState[0].maxNote = selectedTone[7];
                    voice = (u8)SpuVmAlloc(0);
                    keyState[0].voice = voice;
                    if (voice < voiceLimit[0]) {
                        D_800AD3D7[voice * 52] = 1;
                        *(s16 *)(D_800AD3BE + keyState[0].voice * 52) = 0;
                        *(s16 *)(D_800AD3CA + keyState[0].voice * 52) = seq;
                        *(s16 *)(D_800AD3D2 + keyState[0].voice * 52) =
                            keyState[0].vabId;
                        *(s16 *)(D_800AD3CC + keyState[0].voice * 52) =
                            keyState[0].fakeProg;
                        *(s16 *)(D_800AD3CE + keyState[0].voice * 52) = prog;
                        if (seq != 0x21) {
                            *(s16 *)(D_800AD3C4 + keyState[0].voice * 52) =
                                volume;
                        }
                        D_800AD3C6[keyState[0].voice * 52] = pan;
                        *(s16 *)(D_800AD3D0 + keyState[0].voice * 52) =
                            keyState[0].tone;
                        *(s16 *)(D_800AD3C8 + keyState[0].voice * 52) = note;
                        *(s16 *)(D_800AD3D4 + keyState[0].voice * 52) =
                            keyState[0].priority;
                        *(u16 *)(D_800AD3BC + keyState[0].voice * 52) =
                            keyState[0].vag;
                        SpuVmDoAllocate();
                        if ((s16)keyState[0].vag == 0xFF) {
                            vmNoiseOn(*(u8 *)&keyState[0].voice);
                        } else {
                            SpuVmKeyOnNow((u8)vagCount, (u16)note2pitch());
                        }
                        mask |= 1 << keyState[0].voice;
                    } else {
                        mask = -1;
                    }
                    i++;
                } while ((u8)i < vagCount);
            }
        }
    }
    return mask;
}

/* Keys off every voice that plays this note of this program. Returns the
 * number of voices found. */
s32 SpuVmKeyOffVoice(s16, s16, s16, u16) asm("SpuVmKeyOff");
s32 SpuVmKeyOffVoice(s16 arg0, s16 vabId, s16 prog, u16 note) {
    u16 bitsUpper;
    u16 bitsLower;
    u8 voice;
    s32 count;
    u16 tempVoice;

    count = 0;
    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        if ((_svm_voice[voice].note == note) &&
            (_svm_voice[voice].prog == prog) &&
            (_svm_voice[voice].unkE == arg0) &&
            (_svm_voice[voice].vabId == vabId)) {
            if (_svm_voice[voice].unk0 == 0xFF) {
                _svm_voice[voice].unk1B = 0;
                _svm_voice[voice].unk4 = 0;
                _svm_spuBase[202] = 0;
                _svm_spuBase[203] = 0;
            } else {
                _svm_cur.voice = voice;
                tempVoice = GetSvmVoice();
                if (tempVoice < 0x10) {
                    bitsLower = 1 << tempVoice;
                    bitsUpper = 0;
                } else {
                    bitsLower = 0;
                    bitsUpper = 1 << (tempVoice - 0x10);
                }

                _svm_voice[tempVoice].unk1B = 0;
                _svm_voice[tempVoice].unk4 = 0;
                _svm_voice[tempVoice].unk0 = 0;

                _svm_okof1 |= bitsLower;
                _svm_okof2 |= bitsUpper;

                _svm_okon1 &= ~_svm_okof1;
                _svm_okon2 &= ~_svm_okof2;
            }
            count++;
        }
    }
    return count;
}

void SpuVmSeKeyOn(s16 vabId, s16 prog, u16 note, s32 arg3, u16 voll, u16 volr) {
    u16 pan;
    u16 volume;

    if (voll == volr) {
        pan = 0x40;
        volume = voll;
    } else if (volr < voll) {
        volume = voll;
        pan = (volr * 0x40) / voll;
    } else {
        volume = volr;
        pan = 0x7F - ((voll * 0x40) / volr);
    }
    SpuVmKeyOn(0x21, vabId, prog, note, volume, pan);
}

extern void SpuVmKeyOff();

void SpuVmSeKeyOff(s16 vabId, s16 prog, u16 note) {
    SpuVmKeyOff(0x21, vabId, prog, note);
}

void KeyOnCheck(void) {
}

extern s16 D_800B9DDA[];
extern u8 D_800B9C80[];
extern u8 D_800AD224[];
extern u8 D_800AD3A4[];
extern u16 D_800AD3CA[][26];

extern struct SeqStruct *D_800BDE3C[];

/* Stores the sequence volume, and when applyNow is 1 updates the registers
 * of every voice that plays it. */
s32 SpuVmSetSeqVol(s16 seq, u16 voll, u16 volr, s16 applyNow) {
    struct SeqStruct *score = &D_800BDE3C[seq & 0xFF][(seq >> 8) & 0xFF];
    s16 voice;
    s32 vollMul;
    s32 volrMul;
    u8 pad[4];
    s32 temp;
    s16 pos;

    _svm_cur.vagIdx16 = seq;
    score->leftVolume = voll;
    score->rightVolume = volr;
    temp = seq;
    if (score->leftVolume >= 0x80) {
        score->leftVolume = 0x7F;
    }
    if (score->rightVolume >= 0x80) {
        score->rightVolume = 0x7F;
    }
    vollMul = voll * 0x81;
    volrMul = volr * 0x81;

    if (applyNow == 1) {
        for (voice = 0; voice < spuVmMaxVoice; voice++) {
            if ((u16)_svm_voice[voice].unkE == (u16)temp) {
                pos = voice * 8;
                _svm_sreg_buf[pos + 0] = vollMul;
                _svm_sreg_buf[pos + 1] = volrMul;
                _svm_sreg_dirty[voice] |= 3;
            }
        }
    }
    return _svm_cur.vagIdx16;
}

extern s16 D_800B9DDA[];

long SpuVmGetSeqVol(short seq_access, short *volL, short *volR) {
    struct SeqStruct *score;

    score = D_800BDE3C[seq_access & 0xFF];
    D_800B9DDA[0] = seq_access;
    *volL = score[(seq_access & 0xFF00) >> 8].leftVolume;
    *volR = score[(seq_access & 0xFF00) >> 8].rightVolume;
    return D_800B9DDA[0];
}

extern s16 D_800B9DDA[];

s16 SpuVmGetSeqLVol(s16 seq_access) {
    struct SeqStruct *score;

    score = D_800BDE3C[seq_access & 0xFF];
    D_800B9DDA[0] = seq_access;
    return *(s16 *)&score[(seq_access & 0xFF00) >> 8].leftVolume;
}

s16 SpuVmGetSeqRVol(s16 seq_access) {
    struct SeqStruct *score;

    score = D_800BDE3C[seq_access & 0xFF];
    D_800B9DDA[0] = seq_access;
    return *(s16 *)&score[(seq_access & 0xFF00) >> 8].rightVolume;
}

/* Keys off every voice that plays sequence arg0. */
void SpuVmSeqKeyOff(arg0) s16 arg0;
{
    u8 voice;
    u16 bitsUpper;
    u16 bitsLower;
    u16 tempVoice;

    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        if (_svm_voice[voice].unkE == arg0) {
            _svm_cur.voice = voice;
            tempVoice = GetSvmVoice();
            if (tempVoice < 0x10) {
                bitsLower = 1 << tempVoice;
                bitsUpper = 0;
            } else {
                bitsLower = 0;
                bitsUpper = 1 << (tempVoice - 0x10);
            }

            _svm_voice[tempVoice].unk1B = 0;
            _svm_voice[tempVoice].unk4 = 0;
            _svm_voice[tempVoice].unk0 = 0;

            _svm_okof1 |= bitsLower;
            _svm_okof2 |= bitsUpper;

            _svm_okon1 &= ~_svm_okof1;
            _svm_okon2 &= ~_svm_okof2;
        }
    }
}

extern s32 SpuVmVSetUp(s16, s16);
extern u32 D_800B9928[];

s32 SpuVmSetProgVol(vabId, prog, vol)
s16 vabId;
s16 prog;
s32 vol;
{
    if (SpuVmVSetUp(vabId, prog) != 0) {
        return -1;
    }
    ((u8 *)D_800B9928[0])[prog * 16 + 1] = vol;
    return ((u8 *)D_800B9928[0])[prog * 16 + 1];
}

extern s32 SpuVmVSetUp(s16, s16);
extern u32 D_800B9928[];

s32 SpuVmGetProgVol(vabId, prog)
s16 vabId;
s16 prog;
{
    if (SpuVmVSetUp(vabId, prog) != 0) {
        return -1;
    }
    return ((u8 *)D_800B9928[0])[prog * 16 + 1];
}

s32 SpuVmSetProgPan(vabId, prog, pan)
s16 vabId;
s16 prog;
s32 pan;
{
    if (SpuVmVSetUp(vabId, prog) != 0) {
        return -1;
    }
    ((u8 *)D_800B9928[0])[prog * 16 + 4] = pan;
    return ((u8 *)D_800B9928[0])[prog * 16 + 4];
}

s32 SpuVmGetProgPan(vabId, prog)
s16 vabId;
s16 prog;
{
    if (SpuVmVSetUp(vabId, prog) != 0) {
        return -1;
    }
    return ((u8 *)D_800B9928[0])[prog * 16 + 4];
}

/* The unprototyped void declaration above is what the callers see. */
s32 SpuVmSetVolImpl(s16, s16, s16, u16, u16) asm("SpuVmSetVol");
s32 SpuVmSetVolImpl(s16 seq_sep_no, s16 vabId, s16 prog, u16 arg3, u16 arg4) {
    struct SeqStruct *score =
        &D_800BDE3C[seq_sep_no & 0xFF][(seq_sep_no & 0xFF00) >> 8];
    s32 var_s2;
    u8 voice;
    s32 new_var;
    u32 voll, volr;
    u32 voll_t, volr_t;
    s32 mvol_scaled;
    u8 temp;
    s16 new_var2;

    var_s2 = 0;
    SpuVmVSetUp(vabId, prog);
    _svm_cur.vagIdx16 = seq_sep_no;
    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        new_var2 = prog;
        if ((_svm_voice[voice].unkE == seq_sep_no) &&
            (_svm_voice[voice].prog == new_var2) &&
            (_svm_voice[voice].vabId == vabId)) {
            if (score->vol[score->channel] != arg3 &&
                score->vol[score->channel] == 0) {
                score->vol[score->channel] = 1;
            }
            new_var = (_svm_voice[voice].unk8 * arg3) / 0x7F;
            mvol_scaled = _svm_vh->mvol * 0x3FFF;
            voll_t = ((new_var * mvol_scaled) / 0x7F) / 0x7F;
            voll_t =
                ((voll_t * _svm_pg[new_var2].mvol *
                  _svm_tn[_svm_voice[voice].tone + (new_var2 * 0x10)].vol) /
                 0x7F) /
                0x7F;
            volr_t = voll_t;

            voll_t = (voll_t * score->leftVolume) / 0x7F;
            volr_t = (volr_t * score->rightVolume) / 0x7F;

            temp = _svm_tn[_svm_voice[voice].tone].pan;
            if (temp < 0x40) {
                voll = voll_t;
                volr = (volr_t * temp) / 0x3F;
            } else {
                voll = (voll_t * (0x7F - temp)) / 0x3F;
                volr = volr_t;
            }
            temp = _svm_pg[_svm_voice[voice].unk10].mpan;
            if (temp < 0x40) {
                volr = (volr * temp) / 0x3F;
            } else {
                voll = (voll * (0x7F - temp)) / 0x3F;
            }
            do {
                do {
                    temp = arg4;
                } while (0);
            } while (0);
            if (temp < 0x40) {
                volr = (volr * temp) / 0x3F;
            } else {
                voll = (voll * (0x7F - temp)) / 0x3F;
            }
            if (_svm_stereo_mono == 1) {
                if (voll < volr) {
                    voll = volr;
                } else {
                    volr = voll;
                }
            }
            voll = (voll * voll) / 0x3FFF;
            volr = (volr * volr) / 0x3FFF;
            _svm_sreg_buf[voice * 8 + 0] = voll;
            _svm_sreg_buf[voice * 8 + 1] = volr;
            _svm_sreg_dirty[voice] |= 3;
            var_s2++;
        }
    }
    return var_s2;
}

extern s32 D_800B2090[];
extern s32 gOrderingTables[];
extern u16 D_800B9DDE[];
extern s16 D_800B9DDC[];
extern u8 D_800AD3BC[];
extern u8 D_800AD3C8[];
extern u8 D_800AD3CC[];
extern u8 D_800AD3CE[];
extern u8 D_800AD3D0[];
extern u8 D_800AD3D2[];
extern u8 D_800AD3D7[];
extern u8 D_800B9DC4[];
extern u8 D_800B9DC6[];
extern u8 D_800B9DC7[];
extern u8 D_800B9DC8[];
extern u8 D_800B9DC9[];
extern u8 D_800B9DCB[];
extern u8 D_800B9DCE[];
extern u8 D_800B9DCF[];
extern u8 D_800B9DD0[];
extern u8 D_800B9DD1[];
extern u8 D_800B9DD2[];
extern u8 D_800B9DD3[];
extern u8 D_800B9DD4[];
extern u8 D_800B9DD5[];
extern u8 D_800B9DD6[];
extern u8 D_800B9DD7[];
extern u8 D_800B9DD8[];
extern u8 D_800AD3BE[];
extern u8 D_800AD3CC[];
extern u32 D_800B9950[];

/* Retail's codegen needs these spellings:
 * - the (s16)vag test is also the SpuVmAlloc argument, so the sll/sra pair
 *   has a second use and combine can't fold it into the beqz;
 * - (u8)voice in the compare and in the *52 index makes the `move v1,s0`
 *   copy (combine reduces the zero-extend to a copy that has two uses);
 * - D_800B9DD0 + D_800B9DCB * 16 in that operand order;
 * - the post-alloc stores run D3CA, D3D2, D3CC, D3CE, D3BC, D3D0, D3C8,
 *   D3D7, D3BE so sched1 hoists the DCB/DDC/DD0 reloads like retail. */
/* SPDX-License-Identifier: MIT */
s32 SsUtKeyOn(s16 vabId, s16 prog, s16 tone, s16 note, u16 fine, s16 voll,
              s16 volr) {
    extern s32 SpuVmAlloc();
    extern void SpuVmDoAllocate();
    extern void vmNoiseOn();
    extern s32 note2pitch2();
    extern void SpuVmKeyOnNow();
    extern s32 keyOnGuard[] asm("D_800B2090.NON_MATCHING");
    s32 voice;
    u8 *progAttr;
    u8 *toneAttr;
    s32 vag;

    if (D_800B2090[0] == 1) {
        return -1;
    }
    ((s32 *)gOrderingTables)[-1] = 1;
    if (SpuVmVSetUp((s16)vabId, (s16)prog) != 0) {
        keyOnGuard[0] = 0;
        return -1;
    }
    D_800B9DDA[0] = 0x21;
    D_800B9DC6[0] = note;
    D_800B9DC7[0] = fine;
    D_800B9DD0[0] = tone;
    if (voll == volr) {
        D_800B9DC9[0] = 0x40;
        D_800B9DC8[0] = voll;
    } else if (volr < voll) {
        D_800B9DC8[0] = voll;
        D_800B9DC9[0] = (volr << 6) / voll;
    } else {
        D_800B9DC8[0] = volr;
        D_800B9DC9[0] = 0x7F - (voll << 6) / volr;
    }
    progAttr = (u8 *)(prog * 16 + (s32)D_800B9928[0]);
    D_800B9DCE[0] = progAttr[1];
    D_800B9DCF[0] = progAttr[4];
    D_800B9DC4[0] = progAttr[0];
    toneAttr =
        (u8 *)((D_800B9DD0[0] + D_800B9DCB[0] * 16) * 32 + (s32)D_800B9950[0]);
    D_800B9DD3[0] = toneAttr[0];
    vag = *(u16 *)(toneAttr + 0x16);
    D_800B9DDC[0] = vag;
    D_800B9DD1[0] = toneAttr[2];
    D_800B9DD2[0] = toneAttr[3];
    D_800B9DD4[0] = toneAttr[4];
    D_800B9DD5[0] = toneAttr[5];
    D_800B9DD8[0] = toneAttr[1];
    D_800B9DD6[0] = toneAttr[6];
    D_800B9DD7[0] = toneAttr[7];
    if ((s16)vag == 0) {
        keyOnGuard[0] = 0;
        return -1;
    }
    voice = (u8)SpuVmAlloc((s16)vag);
    if ((u8)voice == D_800B9C80[0]) {
        keyOnGuard[0] = 0;
        return -1;
    }
    D_800B9DDE[0] = voice;
    D_800AD3CA[(u8)voice][0] = 0x21;
    *(s16 *)(D_800AD3D2 + (u8)voice * 52) = vabId;
    *(s16 *)(D_800AD3CC + (u8)voice * 52) = D_800B9DC9[2];
    *(s16 *)(D_800AD3CE + (u8)voice * 52) = prog;
    *(s16 *)(D_800AD3BC + (u8)voice * 52) = *(u16 *)&D_800B9DDA[1];
    *(s16 *)(D_800AD3D0 + (u8)voice * 52) = D_800B9DCF[1];
    *(s16 *)(D_800AD3C8 + (u8)voice * 52) = note;
    *(u8 *)(D_800AD3D7 + (u8)voice * 52) = 1;
    *(s16 *)(D_800AD3BE + (u8)voice * 52) = 0;
    SpuVmDoAllocate();
    if (((s16 *)D_800B9DDE)[-1] == 0xFF) {
        vmNoiseOn(voice);
    } else {
        SpuVmKeyOnNow(1, (u16)note2pitch2((u16)note, fine));
    }
    keyOnGuard[0] = 0;
    return voice;
}

extern s32 D_800B2090[];
extern s32 gOrderingTables[];
extern s32 D_800A20B8[];
extern u16 D_800B9DDE[];
extern s16 D_800B9DDC[];
extern u16 D_800BEB98[];
extern u16 D_800BEB9C[];
extern u16 D_800AD96C[];
extern u16 D_800AD970[];
extern u8 D_800AD3BC[];
extern u8 D_800AD3C0[];
extern u8 D_800AD3C8[];
extern u8 D_800AD3CE[];
extern u8 D_800AD3D0[];
extern u8 D_800AD3D2[];
extern u8 D_800AD3D7[];

/* Matches (0 words) under GNU C 2.6.3-psx only. Retail's codegen needs these
 * spellings:
 * - The voice masks reuse the vabId and prog parameters (s32, narrowed with
 *   (s16) in the compares). Their copy pseudos prefer a1 and a2 and conflict
 *   with the constant 1 held in t1. Separate mask locals leave the constant
 *   preferring a0 (a mask merges its preference into it through
 *   expand_preferences), which pushes the vc * 52 index to t0 (20 rows) or,
 *   when the second chain load is captured, puts that load in a1 (2 rows).
 * - D_800B9DDE is stored through its own name and reloaded through the
 *   neighbour spelling D_800B9DDC + 2. cse can't forward the store and the
 *   two accesses don't share a la. Distinct symbols alone let sched1 hoist the
 *   reload above the store; the empty do-while leaves loop notes that stop
 *   that (no asm barrier needed).
 * - orTemp and orTemp2 keep the or operand order, and the four mask stores
 *   use four distinct address spellings. */
/* SPDX-License-Identifier: MIT */
s32 SsUtKeyOff(s16 vc, s32 vabId, s32 prog, s16 tone, s16 note) {
    u16 voice;
    s32 keyOnLow;
    s32 keyOnHigh;
    s32 newLow;
    s32 newHigh;
    s32 seq;

    if (D_800B2090[0] == 1) {
        return -1;
    }
    ((s32 *)gOrderingTables)[-1] = 1;
    if ((u16)vc < 0x18) {
        if (*(s16 *)(D_800AD3D2 + vc * 52) == (s16)vabId &&
            *(s16 *)(D_800AD3CE + vc * 52) == (s16)prog &&
            *(s16 *)(D_800AD3D0 + vc * 52) == tone &&
            *(s16 *)(D_800AD3C8 + vc * 52) == note) {
            if (*(s16 *)(D_800AD3BC + vc * 52) == 0xFF) {
                D_800AD3D7[(u8)vc * 52] = 0;
                seq = D_800A20B8[0];
                *(s16 *)(D_800AD3C0 + (u8)vc * 52) = 0;
                *(s16 *)(seq + 0x194) = 0;
                *(s16 *)(seq + 0x196) = 0;
            } else {
                D_800B9DDE[0] = vc;
                do {
                } while (0);
                voice = ((u16 *)D_800B9DDC)[1];
                if (voice < 0x10) {
                    prog = 1 << voice;
                    vabId = 0;
                } else {
                    prog = 0;
                    vabId = 1 << (voice - 0x10);
                }
                D_800AD3D7[voice * 52] = 0;
                keyOnLow = D_800BEB98[0];
                keyOnHigh = D_800BEB9C[0];
                *(s16 *)(D_800AD3C0 + voice * 52) = 0;
                *(s16 *)(D_800AD3BC + voice * 52) = 0;
                newLow = prog | keyOnLow;
                ((u16 *)D_800BEB9C)[-2] = newLow;
                ((u16 *)D_800AD970)[-2] = D_800AD96C[0] & ~newLow;
                newHigh = vabId | keyOnHigh;
                ((u16 *)D_800BEB98)[2] = newHigh;
                ((u16 *)D_800AD96C)[2] = D_800AD970[0] & ~newHigh;
            }
            D_800B2090[0] = 0;
            return 0;
        }
    }
    ((s32 *)gOrderingTables)[-1] = 0;
    return -1;
}

#ifdef NON_MATCHING
/* 2026-10-17: donor body (sotn vmanager.c). 0x3A4 bytes against 0x39C: retail
 * passes note and fine to note2pitch2 without a sign extension and allocates
 * voice and vabId to s2 and s3 in the other order. */
extern void SpuVmDoAllocate(void);
extern void SpuVmKeyOnNow();
extern s32 note2pitch2();

s16 SsUtKeyOnV(s16 voice, s16 vabId, s16 prog, s16 tone, s16 note, s16 fine,
               s16 voll, s16 volr) {
    s32 tone2;

    if (_snd_ev_flag == 1) {
        return -1;
    }
    _snd_ev_flag = 1;
    if (voice < 0 || voice >= 24) {
        _snd_ev_flag = 0;
        return -1;
    }
    if (SpuVmVSetUp(vabId, prog)) {
        _snd_ev_flag = 0;
        return -1;
    }
    _svm_cur.vagIdx16 = 0x21;
    _svm_cur.note = note;
    _svm_cur.field3 = fine;
    _svm_cur.vagIdx = tone;

    if (voll == volr) {
        _svm_cur.field5 = 0x40;
        _svm_cur.voll = voll;
    } else if (volr < voll) {
        _svm_cur.field5 = (volr * 0x40) / voll;
        _svm_cur.voll = voll;
    } else {
        _svm_cur.field5 = 0x7F - ((voll * 0x40) / volr);
        _svm_cur.voll = volr;
    }

    _svm_cur.mvol = _svm_pg[prog].mvol;
    _svm_cur.mpan = _svm_pg[prog].mpan;
    _svm_cur.field0 = _svm_pg[prog].tones;

    tone2 = _svm_cur.vagIdx + (_svm_cur.fakeProgram * 0x10);
    _svm_cur.prior = _svm_tn[tone2].prior;
    _svm_cur.voiceIdx = _svm_tn[tone2].vag;
    _svm_cur.vol = _svm_tn[tone2].vol;
    _svm_cur.pan = _svm_tn[tone2].pan;
    _svm_cur.centre = _svm_tn[tone2].center;
    _svm_cur.shift = _svm_tn[tone2].shift;
    _svm_cur.seqSepNo = _svm_tn[tone2].mode;
    _svm_cur.mode = _svm_tn[tone2].min;
    _svm_cur.field13 = _svm_tn[tone2].max;

    if (_svm_cur.voiceIdx == 0) {
        _snd_ev_flag = 0;
        return -1;
    }

    _svm_cur.voice = voice;
    _svm_voice[voice].unkE = 0x21;
    _svm_voice[voice].vabId = vabId;
    _svm_voice[voice].unk10 = _svm_cur.fakeProgram;
    _svm_voice[voice].prog = prog;
    _svm_voice[voice].unk0 = _svm_cur.voiceIdx;
    _svm_voice[voice].tone = _svm_cur.vagIdx;
    _svm_voice[voice].note = note;
    _svm_voice[voice].unk1B = 1;
    _svm_voice[voice].unk2 = 0;
    SpuVmDoAllocate();
    if (_svm_cur.voiceIdx == 0xFF) {
        vmNoiseOn(voice);
    } else {
        SpuVmKeyOnNow(1, note2pitch2(note, fine));
    }
    _snd_ev_flag = 0;
    return voice;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtKeyOnV);
#endif

s32 SsUtKeyOffV(s16 voice) {
    u16 bitsUpper;
    u16 bitsLower;
    u16 temp2;

    if (_snd_ev_flag == 1) {
        return -1;
    }
    _snd_ev_flag = 1;

    if (voice >= 0 && voice < 24) {
        _svm_cur.voice = voice;
        temp2 = GetSvmVoice();
        if (temp2 < 0x10) {
            bitsLower = 1 << temp2;
            bitsUpper = 0;
        } else {
            bitsLower = 0;
            bitsUpper = 1 << (temp2 - 0x10);
        }

        _svm_voice[temp2].unk1B = 0;
        _svm_voice[temp2].unk4 = 0;
        _svm_voice[temp2].unk0 = 0;

        _snd_ev_flag = 0;

        _svm_okof1 |= bitsLower;
        _svm_okof2 |= bitsUpper;

        _svm_okon1 &= ~_svm_okof1;
        _svm_okon2 &= ~_svm_okof2;
        return 0;
    }
    _snd_ev_flag = 0;
    return -1;
}

extern s16 D_800B9DDA[];
extern s32 SpuVmVSetUp(s16, s16);
extern s32 SpuVmPBVoice(s16, s16, s16, s16, u16);
s16 SsUtPitchBend(s16 voice, s16 vabId, s16 prog, s16 note, s16 pbend) {
    SpuVmVSetUp(vabId, prog);
    D_800B9DDA[0] = 0x21;
    return -((SpuVmPBVoice(voice, 0x21, vabId, prog, pbend) << 16) == 0);
}

short SsUtChangePitch(voice, vabId, prog, old_note, old_fine, new_note,
                      new_fine)
short voice;
short vabId;
short prog;
short old_note;
short old_fine;
u16 new_note;
u16 new_fine;
{
    extern s32 note2pitch2();
    extern u16 gSpuRegisterBuffer[] asm("D_800AD224");
    if (voice >= 0 && voice < 24) {
        if (((s16 *)D_800AD3D2)[voice * 26] == vabId) {
            if (((s16 *)D_800AD3CE)[voice * 26] == prog) {
                if (((s16 *)D_800AD3C8)[voice * 26] == old_note) {
                    SpuVmVSetUp(((s16 *)D_800AD3D2)[voice * 26],
                                ((s16 *)D_800AD3CE)[voice * 26]);
                    D_800B9DDA[0] = 0x21;
                    D_800B9DDE[0] = voice;
                    D_800B9DD0[0] = D_800AD3D0[voice * 52];
                    gSpuRegisterBuffer[voice * 8 + 2] =
                        note2pitch2(new_note, new_fine);
                    D_800AD3A4[voice] |= 4;
                    return 0;
                }
            }
        }
    }
    return -1;
}

extern u16 gSpuRegisterBuffer[];
extern u8 D_800AD3A4[];
s16 SsUtChangeADSR(s16 voice, s16 vabId, s16 prog, s16 oldNote, u16 adsr1,
                   u16 adsr2) {
    s32 voiceOffset;
    s32 attrOffset;
    if ((u16)voice < 0x18) {
        voiceOffset = voice * 26;
        if (((s16 *)D_800AD3D2)[voiceOffset] == vabId) {
            if (((s16 *)D_800AD3CE)[voiceOffset] == prog) {
                if (((s16 *)D_800AD3C8)[voiceOffset] == oldNote) {
                    attrOffset = voice * 8;
                    gSpuRegisterBuffer[attrOffset + 4] = adsr1;
                    gSpuRegisterBuffer[attrOffset + 5] = adsr2;
                    D_800AD3A4[voice] |= 0x30;
                    return 0;
                }
            }
        }
    }
    return -1;
}

extern s32 D_800A20B8[];

s32 SsUtGetDetVVol(s32 vab, s16 *vl, s16 *vr) {
    if ((u16)vab < 0x18) {
        *vl = *(s16 *)((s32)D_800A20B8[0] + ((s16)vab) * 16);
        *vr = *(s16 *)((s32)D_800A20B8[0] + ((s16)vab) * 16 + 2);
        return 0;
    }
    return -1;
}

short SsUtSetDetVVol(short vc, short vl, short vr) {
    if ((u16)vc < 24) {
        *(s16 *)&D_800AD224[vc * 16 + 2] = vr;
        D_800AD3A4[vc] |= 3;
        *(s16 *)&D_800AD224[vc * 16] = vl;
        return 0;
    }
    return -1;
}

extern s32 D_800A20B8[];

s32 SsUtGetVVol(s32 vc, s16 *voll, s16 *volr) {
    s16 mvolL;
    s16 mvolR;

    if ((u16)vc < 24) {
        mvolL = *(s16 *)&((u8 *)D_800A20B8[0])[(s16)vc * 16];
        mvolR = *(s16 *)&((u8 *)D_800A20B8[0])[(s16)vc * 16 + 2];
        *voll = mvolL / 129;
        *volr = mvolR / 129;
        return 0;
    }
    return -1;
}

short SsUtSetVVol(short vc, short voll, short volr) {
    s16 mvolL;
    s16 mvolR;

    if ((u16)vc < 24) {
        mvolL = voll * 129;
        mvolR = volr * 129;
        *(s16 *)&D_800AD224[vc * 16 + 2] = mvolR;
        D_800AD3A4[vc] |= 3;
        *(s16 *)&D_800AD224[vc * 16] = mvolL;
        return 0;
    }
    return -1;
}

extern void SeAutoVol(s16 seq_access, s16 vol1, s16 vol2, s16 mSec);

s32 SsUtAutoVol(s32 seq_access, s32 vol1, s32 vol2, s32 mSec) {
    if ((u16)seq_access < 24) {
        SeAutoVol(seq_access, vol1, vol2, mSec);
        return 0;
    }
    return -1;
}

extern void SeAutoPan(s16 seq_access, s16 pan1, s16 pan2, s16 mSec);

s32 SsUtAutoPan(s32 seq_access, s32 pan1, s32 pan2, s32 mSec) {
    if ((u16)seq_access < 24) {
        SeAutoPan(seq_access, pan1, pan2, mSec);
        return 0;
    }
    return -1;
}

void SsUtAllKeyOff(void) {
    s16 voice;
    u16 bitsUpper;
    u16 bitsLower;
    u16 temp2;
    s16 pos;

    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        _svm_voice[voice].unk2 = 0x18;
        _svm_voice[voice].unk0 = 0xFF;
        _svm_voice[voice].unk1B = 0;
        _svm_voice[voice].unk4 = 0;
        _svm_voice[voice].unk6 = 0;
        _svm_voice[voice].unkE = 0xFF;
        _svm_voice[voice].unk10 = 0;
        _svm_voice[voice].prog = 0;
        _svm_voice[voice].tone = 0xFF;

        pos = voice * 8;
        _svm_spuBase[pos + 0x6 / 2] = 0x200;
        _svm_spuBase[pos + 0x4 / 2] = 0x1000;
        _svm_spuBase[pos + 0x8 / 2] = 0x80ff;
        _svm_spuBase[pos + 0x0] = 0;
        _svm_spuBase[pos + 0x2 / 2] = 0;
        _svm_spuBase[pos + 0xa / 2] = 0x4000;

        _svm_cur.voice = voice;
        temp2 = GetSvmVoice();
        if (temp2 < 0x10) {
            bitsLower = 1 << temp2;
            bitsUpper = 0;
        } else {
            bitsLower = 0;
            bitsUpper = 1 << (temp2 - 0x10);
        }

        _svm_voice[temp2].unk1B = 0;
        _svm_voice[temp2].unk4 = 0;
        _svm_voice[temp2].unk0 = 0;

        _svm_okof1 |= bitsLower;
        _svm_okof2 |= bitsUpper;

        _svm_okon1 &= ~_svm_okof1;
        _svm_okon2 &= ~_svm_okof2;
    }
}

extern void _SpuInit(s32 mode);

void func_80087CC0(void) {
    _SpuInit(0);
}

extern s32 _spu_init(s32);
extern void SpuStart(void);
extern void _spu_FsetRXX(s32, u32, s32);
extern s16 gSpuVoiceCenterNotes[];
extern s32 D_800A2710Init[];
extern s32 D_800A2248Init[];
extern s32 D_800A224CInit[];
extern s32 D_800A2258Init[];
extern s16 D_800A225CInit[];
extern s16 D_800A225EInit[];
extern s32 D_800A2260Init[];
extern s32 D_800A2264Init[];
extern s32 D_800A2250Init[];
extern s32 D_800A2244Init[];
extern s32 D_800A26C4Init[];
extern s32 D_800A229CInit[];
void _SpuInit(s32 arg0) {
    s32 i;
    u32 centerNote;
    ResetCallback();
    _spu_init(arg0);
    if (arg0 == 0) {
        centerNote = 0xC000;
        i = 23;
        do {
            gSpuVoiceCenterNotes[i] = centerNote;
            i--;
        } while (i >= 0);
    }
    SpuStart();
    D_800A2248Init[0] = 0;
    D_800A224CInit[0] = 0;
    D_800A2258Init[0] = 0;
    D_800A225CInit[0] = 0;
    D_800A225EInit[0] = 0;
    D_800A2260Init[0] = 0;
    D_800A2264Init[0] = 0;
    D_800A2250Init[0] = D_800A2710Init[0];
    _spu_FsetRXX(0xD1, D_800A2710Init[0], 0);
    D_800A2244Init[0] = 0;
    D_800A26C4Init[0] = 0;
    D_800A229CInit[0] = 0;
}

typedef struct SpuStartedStorage {
    s32 started;
    s32 padding[2];
} SpuStartedStorage;
extern SpuStartedStorage D_800A26A0Read;
extern SpuStartedStorage D_800A26A0Write;
extern s32 D_800A2240[];
extern s32 D_800A2298[];
extern void _SpuDataCallback(void (*)());
extern void _spu_FiDMA(void);
void SpuStart(void) {
    s32 event;
    if (D_800A26A0Read.started == 0) {
        D_800A26A0Write.started = 1;
        EnterCriticalSection();
        D_800A2240[0] = 0;
        _SpuDataCallback(&_spu_FiDMA);
        event = OpenEvent(0xF0000009, 0x20, 0x2000, 0);
        D_800A2298[0] = event;
        EnableEvent(event);
        ExitCriticalSection();
    }
}

extern u16 *D_800A26AC[];
s32 _spu_reset(void) {
    volatile s32 i;
    volatile s32 j;
    u16 value;
    value = *(volatile u16 *)((u8 *)D_800A26AC[0] + 0x1AA);
    *(volatile u16 *)((u8 *)D_800A26AC[0] + 0x1AA) = value & 0x7FCF;
    j = 13;
    i = 0;
    while (i < 0xF0) {
        j = j * 3;
        i = i + 1;
        (void)i;
    }
    value &= 0xFFCF;
    *(volatile u16 *)((u8 *)D_800A26AC[0] + 0x1AA) = value;
    return 0;
}

INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090B48);
typedef struct SpuInitRegs {
    volatile u16 voice[24][8];
    volatile u16 mainVol[2];
    volatile u16 reverbVol[2];
    volatile u16 keyOn[2];
    volatile u16 keyOff[2];
    volatile u16 channelFm[2];
    volatile u16 noiseMode[2];
    volatile u16 reverbMode[2];
    volatile u16 reserved[5];
    volatile u16 transferAddr;
    volatile u16 transferData;
    volatile u16 spucnt;
    volatile u16 dataTransfer;
    volatile u16 spustat;
    volatile u16 cdVol[2];
    volatile u16 externalVol[2];
} SpuInitRegs;
extern volatile SpuInitRegs *D_800A26ACInitRegs[];
extern volatile s32 *D_800A26BCInitPtr[];
extern s32 D_800A26A4Init[];
extern s32 D_800A26A4[];
extern s32 D_800A26C4Init[];
extern s32 D_800A26C8Init[];
extern s16 D_800A26A8Init[];
extern s32 D_800A26CCInit[];
extern s32 D_800A26D0Init[];
extern s32 D_800A26D4Init[];
extern s32 D_800A26D8Init[];
extern u16 D_800A26E8Init[];
extern char D_80090B38Init[];
extern char D_80090B48Init[];
extern s32 D_800A26F8Init[];
extern s32 D_800A26A0Init[];
extern s32 D_800A26C0Init[];
extern s32 D_800A26B0Init[];
extern s32 D_800A26B4Init[];

extern s32 _spu_mem_mode_plus;
extern s32 _spu_mem_mode;
extern s32 _spu_mem_mode_unit;
extern s32 _spu_mem_mode_unitM;
extern u16 _spu_tsa;
extern s32 _spu_inTransfer[];
extern s32 _spu_transferCallback[];
extern s32 _spu_IRQCallback[];

extern s32 printf(const char *, ...);
s32 _spu_init(s32 hotInit) {
    volatile s32 delayCount;
    volatile u32 delayValue;
    s32 channel;
    volatile SpuInitRegs *regs;
    volatile u16 *voice;
    u16 status;
    s32 count;
    extern u16 *D_800A26ACFiDMA[];
    *D_800A26BCInitPtr[0] |= 0xB0000;
    {
        volatile SpuInitRegs *regs = D_800A26ACInitRegs[0];
        regs->mainVol[0] = 0;
        regs->mainVol[1] = 0;
        regs->spucnt = 0;
    }
    D_800A26C4Init[0] = 0;
    D_800A26C8Init[0] = 0;
    D_800A26A8Init[0] = 0;
    delayValue = 0xD;
    for (delayCount = 0; delayCount < 0xF0; delayCount++) {
        delayValue *= 3;
    }
    {
        volatile SpuInitRegs *initialRegs = D_800A26ACInitRegs[0];
        initialRegs->mainVol[0] = 0;
        initialRegs->mainVol[1] = 0;
        status = initialRegs->spustat;
    }
    D_800A26A4Init[0] = 0;
    if (status & 0x7FF) {
    waitSpu:
        count = D_800A26A4[0] + 1;
        D_800A26A4Init[0] = count;
        if (count > 5000) {
            printf(D_80090B38Init, D_80090B48Init);
        } else if (D_800A26ACInitRegs[0]->spustat & 0x7FF) {
            goto waitSpu;
        }
    }
    regs = D_800A26ACInitRegs[0];
    D_800A26CCInit[0] = 2;
    D_800A26D0Init[0] = 3;
    D_800A26D4Init[0] = 8;
    D_800A26D8Init[0] = 7;
    {
        regs->dataTransfer = 4;
        regs->reverbVol[0] = 0;
        regs->reverbVol[1] = 0;
        regs->keyOff[0] = 0xFFFF;
        regs->keyOff[1] = 0xFFFF;
        regs->reverbMode[0] = 0;
        regs->reverbMode[1] = 0;
    }
    if (hotInit == 0) {
        {
            regs->channelFm[0] = 0;
            regs->channelFm[1] = 0;
            regs->noiseMode[0] = 0;
            regs->noiseMode[1] = 0;
            regs->cdVol[0] = 0;
            regs->cdVol[1] = 0;
            regs->externalVol[0] = 0;
            regs->externalVol[1] = 0;
        }
        D_800A26A8Init[0] = 0x200;
        _spu_writeByIO((u8 *)D_800A26E8Init, 0x10);
        channel = 0;
        regs = (volatile SpuInitRegs *)D_800A26ACFiDMA[0];
        while (channel < 24) {
            voice = regs->voice[channel];
            voice[0] = 0;
            voice[1] = 0;
            voice[2] = 0x3FFF;
            voice[3] = 0x200;
            voice[4] = 0;
            voice[5] = 0;
            channel++;
        }
        {
            volatile SpuInitRegs *regs =
                (volatile SpuInitRegs *)D_800A26ACFiDMA[0];
            regs->keyOn[0] |= 0xFFFF;
            regs->keyOn[1] |= 0xFF;
        }
        delayValue = 0xD;
        for (delayCount = 0; delayCount < 0xF0; delayCount++) {
            delayValue *= 3;
        }
        delayValue = 0xD;
        for (delayCount = 0; delayCount < 0xF0; delayCount++) {
            delayValue *= 3;
        }
        delayValue = 0xD;
        for (delayCount = 0; delayCount < 0xF0; delayCount++) {
            delayValue *= 3;
        }
        delayValue = 0xD;
        for (delayCount = 0; delayCount < 0xF0; delayCount++) {
            delayValue *= 3;
        }
        {
            volatile SpuInitRegs *regs =
                (volatile SpuInitRegs *)D_800A26ACFiDMA[0];
            regs->keyOff[0] |= 0xFFFF;
            regs->keyOff[1] |= 0xFF;
        }
        delayValue = 0xD;
        for (delayCount = 0; delayCount < 0xF0; delayCount++) {
            delayValue *= 3;
        }
        delayValue = 0xD;
        for (delayCount = 0; delayCount < 0xF0; delayCount++) {
            delayValue *= 3;
        }
        delayValue = 0xD;
        for (delayCount = 0; delayCount < 0xF0; delayCount++) {
            delayValue *= 3;
        }
        delayValue = 0xD;
        for (delayCount = 0; delayCount < 0xF0; delayCount++) {
            delayValue *= 3;
        }
    }
    _spu_inTransfer[0] = 1;
    {
        volatile SpuInitRegs *regs = (volatile SpuInitRegs *)D_800A26ACFiDMA[0];
        regs->spucnt = 0xC000;
    }
    _spu_transferCallback[0] = 0;
    _spu_IRQCallback[0] = 0;
    return 0;
}

extern char D_80090B58[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090B58);
extern char D_80090B6C[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090B6C);
extern char D_80090B38[];
extern s32 _spu_timeout;
extern u16 _spu_tsa;

#define WASTE_TIME()                                                           \
    sp4 = 0xD;                                                                 \
    for (sp0 = 0; sp0 < 0xF0; sp0++) {                                         \
        sp4 *= 3;                                                              \
    }

s32 _spu_writeByIO(u8 *addr, u32 size) {
    volatile s32 sp0;
    volatile s32 sp4;
    u16 spustat;
    s32 num_to_trans;
    u16 *cur_pos;
    s32 spustat_cur;
    s32 i;
    u16 cnt;

    cur_pos = (u16 *)addr;
    spustat = _spu_RXX->rxx.spustat & 0x7FF;
    _spu_RXX->rxx.trans_addr = _spu_tsa;
    WASTE_TIME();
    while (size != 0) {
        num_to_trans = (size > 0x40) ? 0x40 : size;
        for (i = 0; i < num_to_trans; i += 2) {
            _spu_RXX->rxx.trans_fifo = *cur_pos++;
        }
        cnt = _spu_RXX->rxx.spucnt;
        cnt &= ~0x30;
        cnt |= 0x10;
        _spu_RXX->rxx.spucnt = cnt;
        WASTE_TIME();
        _spu_timeout = 0;
        while (_spu_RXX->rxx.spustat & 0x400) {
            _spu_timeout++;
            if (_spu_timeout > 5000) {
                printf(D_80090B38, D_80090B58);
                break;
            }
        }
        WASTE_TIME();
        WASTE_TIME();
        size -= num_to_trans;
    }
    cnt = _spu_RXX->rxx.spucnt;
    cnt &= ~0x30;
    _spu_RXX->rxx.spucnt = cnt;
    _spu_timeout = 0;
    spustat_cur = _spu_RXX->rxx.spustat & 0x7FF;
    while (spustat_cur != spustat) {
        _spu_timeout++;
        if (_spu_timeout > 5000) {
            printf(D_80090B38, D_80090B6C);
            return;
        }
        spustat_cur = _spu_RXX->rxx.spustat & 0x7FF;
    }
    return spustat_cur;
}

extern s32 D_800A26F8FiDMA[];
extern u16 *D_800A26ACFiDMA[];
extern SpuIRQCallbackProc D_800A26E0FiDMARead[];
extern SpuIRQCallbackProc D_800A26E0FiDMAWrite[];
void _spu_FiDMA(void) {
    volatile s32 sp0;
    volatile s32 sp4;
    s32 i;
    volatile u16 *spu;
    if (D_800A26F8FiDMA[0] == 0) {
        sp4 = 0xD;
        for (sp0 = 0; sp0 < 0xF0; sp0++) {
            sp4 *= 3;
        }
        sp4 = 0xD;
        for (sp0 = 0; sp0 < 0xF0; sp0++) {
            sp4 *= 3;
        }
        sp4 = 0xD;
        for (sp0 = 0; sp0 < 0xF0; sp0++) {
            sp4 *= 3;
        }
    }
    spu = D_800A26ACFiDMA[0];
    spu[0xD5] &= 0xFFCF;
    i = 0;
    while (spu[0xD5] & 0x30) {
        if (++i > 0xF00) {
            break;
        }
    }
    if (D_800A26E0FiDMARead[0] != 0) {
        D_800A26E0FiDMAWrite[0]();
        return;
    }
    DeliverEvent(0xF0000009, 0x20);
}

typedef struct SpuRxxPrefix {
    u8 pad[0x1A6];
    u16 transferAddress;
    u16 transferFifo;
    u16 control;
} SpuRxxPrefix;
typedef union SpuRxxUnion {
    volatile SpuRxxPrefix rxx;
} SpuRxxUnion;
extern SpuRxxUnion *gSpuRegisters[];
extern s32 *D_800A26C0r[];
extern s32 *D_800A26B0r[];
extern s32 *D_800A26B4r[];
extern s32 *D_800A26B8r[];
extern s32 D_800A26F8r[];
void _spu_r_(s32 arg0, u16 arg1, s32 arg2) {
    volatile s32 sp0;
    volatile s32 sp4;
    gSpuRegisters[0]->rxx.transferAddress = arg1;
    sp4 = 0xD;
    for (sp0 = 0; sp0 < 0xF0; sp0++) {
        sp4 *= 3;
    }
    sp4 = 0xD;
    for (sp0 = 0; sp0 < 0xF0; sp0++) {
        sp4 *= 3;
    }
    gSpuRegisters[0]->rxx.control |= 0x30;
    sp4 = 0xD;
    for (sp0 = 0; sp0 < 0xF0; sp0++) {
        sp4 *= 3;
    }
    sp4 = 0xD;
    for (sp0 = 0; sp0 < 0xF0; sp0++) {
        sp4 *= 3;
    }
    *D_800A26C0r[0] = (*D_800A26C0r[0] & 0xF0FFFFFF) | 0x22000000;
    *D_800A26B0r[0] = arg0;
    *D_800A26B4r[0] = (arg2 << 16) | 0x10;
    D_800A26F8r[0] = 1;
    *D_800A26B8r[0] = 0x01000200;
}

extern s32 _spu_transDir;
extern volatile s32 *_spu_dmaAddr;
extern volatile s32 *_spu_dmaSize;
extern volatile s32 *_spu_dmaCtrl;
extern volatile s32 *_spu_delayCtrl;
extern s32 _spu_xferAddr;
extern s32 _spu_xferBlocks;

static __inline__ void _spu_FsetDelayW(void) {
    *_spu_delayCtrl = (*_spu_delayCtrl & 0xF0FFFFFF) | 0x20000000;
}

static __inline__ void _spu_FsetDelayR(void) {
    *_spu_delayCtrl = (*_spu_delayCtrl & 0xF0FFFFFF) | 0x22000000;
}

/* Starts or checks an SPU transfer: 2 sets the address, 0 and 1 start a
 * write or a read, 3 programs the DMA for count bytes. Returns -2 when the
 * SPU does not settle. */
s32 _spu_t(s32 arg0, ...) {
    s32 var_a2;
    s32 i;
    va_list args;
    u32 count;
    u16 ck2;
    u16 cnt;
    va_start(args, arg0);
    switch (arg0) {
    case 2:
        count = va_arg(args, u32);
        _spu_tsa = count >> _spu_mem_mode_plus;
        _spu_RXX->rxx.trans_addr = _spu_tsa;
        break;
    case 1:
        _spu_transDir = 0;
        i = 0;
        while (_spu_RXX->rxx.trans_addr != _spu_tsa) {
            if (++i > 0xF00)
                return -2;
        }
        cnt = _spu_RXX->rxx.spucnt;
        cnt &= ~0x30;
        cnt |= 0x20;
        _spu_RXX->rxx.spucnt = cnt;
        break;
    case 0:
        _spu_transDir = 1;
        i = 0;
        while (_spu_RXX->rxx.trans_addr != _spu_tsa) {
            if (++i > 0xF00)
                return -2;
        }
        cnt = _spu_RXX->rxx.spucnt;
        cnt &= ~0x30;
        cnt |= 0x30;
        _spu_RXX->rxx.spucnt = cnt;
        break;
    case 3:
        if (_spu_transDir == 1)
            ck2 = 0x30;
        else
            ck2 = 0x20;
        i = 0;
        while ((_spu_RXX->rxx.spucnt & 0x30) != ck2) {
            if (++i > 0xF00)
                return -2;
        }
        if (_spu_transDir == 1)
            _spu_FsetDelayR();
        else
            _spu_FsetDelayW();
        count = va_arg(args, u32);
        _spu_xferAddr = count;
        count = va_arg(args, u32);
        _spu_xferBlocks = count / 64;
        _spu_xferBlocks += ((count % 64) ? 1 : 0);
        *_spu_dmaAddr = _spu_xferAddr;
        *_spu_dmaSize = (_spu_xferBlocks << 16) | 0x10;
        if (_spu_transDir == 1)
            var_a2 = 0x01000200;
        else
            var_a2 = 0x01000201;
        *_spu_dmaCtrl = var_a2;
        break;
    }
    return 0;
}

extern long D_800A26C4[];
extern u16 D_800A26A8[];
extern s32 D_800A26D0[];
extern s32 _spu_t(s32, ...);
extern s32 _spu_writeByIO(u8 *, u32);
s32 _spu_write(u8 *addr, u32 size) {
    if (D_800A26C4[0] == 0) {
        _spu_t(2, D_800A26A8[0] << D_800A26D0[0]);
        _spu_t(1);
        _spu_t(3, addr, size);
    } else {
        _spu_writeByIO(addr, size);
    }
    return size;
}

/* SPDX-License-Identifier: MIT */

extern u16 D_800A26A8[];
extern s32 D_800A26D0[];
s32 _spu_t(s32, ...);

s32 _spu_read(s32 arg0, u32 size) {
    _spu_t(2, D_800A26A8[0] << D_800A26D0[0]);
    _spu_t(0);
    _spu_t(3, arg0, size);
    return size;
}

void _spu_FsetRXX(s32 idx, u32 val, s32 mode) {
    extern u16 *D_800A26AC[];
    extern s32 D_800A26D0[];

    if (mode == 0) {
        *(volatile u16 *)&D_800A26AC[0][idx] = val;
    } else {
        D_800A26AC[0][idx] = val >> D_800A26D0[0];
    }
}

/* SPDX-License-Identifier: MIT */

extern u16 *D_800A26AC[];
extern s32 D_800A26CC[];
extern s32 D_800A26D0[];
extern u32 D_800A26D4[];
extern u32 D_800A26D8[];

u32 _spu_FsetRXXa(s32 arg0, u32 arg1) {
    u32 registerValue;
    u32 address;

    address = arg1;
    if ((D_800A26CC[0] != 0) && ((address % D_800A26D4[0]) != 0)) {
        address += D_800A26D4[0];
        address &= ~D_800A26D8[0];
    }
    registerValue = address >> D_800A26D0[0];
    switch (arg0) {
    case -1:
        return registerValue & 0xFFFF;
    case -2:
        return address;
    default:
        D_800A26AC[0][arg0] = registerValue;
        return address;
    }
}

/* SPDX-License-Identifier: MIT */

extern u16 *D_800A26AC[];
extern s32 D_800A26D0[];

u32 _spu_FgetRXXa(s32 arg0, s32 arg1) {
    u16 temp;

    temp = D_800A26AC[0][arg0];
    if (arg1 == -1) {
        return temp;
    }
    return temp << D_800A26D0[0];
}

void _SpuDataCallback(void (*arg0)()) {
    DMACallback(4, arg0);
}

extern SpuStartedStorage D_800A26A0Read;
extern SpuStartedStorage D_800A26A0Write;
extern SpuIRQCallbackProc D_800A26E0[];
extern SpuIRQCallbackProc D_800A26E4[];
extern s32 D_800A2298[];
extern s32 D_800A2298Clear[];
void SpuQuit(void) {
    SpuIRQCallbackProc callback;
    if (D_800A26A0Read.started == 1) {
        D_800A26A0Write.started = 0;
        EnterCriticalSection();
        callback = 0;
        asm("" : "=r"(callback) : "0"(callback));
        D_800A26E0[0] = 0;
        D_800A26E4[0] = 0;
        _SpuDataCallback(callback);
        CloseEvent(D_800A2298[0]);
        DisableEvent(D_800A2298Clear[0]);
        ExitCriticalSection();
    }
}

s32 SpuSetMute(s32 onOff) {
    switch (onOff) {
    case 0:
        D_800A26AC[0][0xD5] |= 0x4000;
        break;
    case 1:
        D_800A26AC[0][0xD5] &= 0xBFFF;
        break;
    }
    return onOff;
}

s32 SpuInitMalloc(s32 num, s32 *table) {
    extern s32 D_800A26D0[];
    extern s32 D_800A2704[];
    extern s32 D_800A2708[];
    extern s32 D_800A270C[];

    if (num > 0) {
        s32 shift = D_800A26D0[0];

        table[0] = 0x40001010;
        D_800A270C[0] = (s32)table;
        D_800A2708[0] = 0;
        D_800A2704[0] = num;
        table[1] = (0x10000 << shift) - 0x1010;
        return num;
    }
    return 0;
}

/* The SPU memory list that SpuMalloc and SpuFree keep. Entry flags sit in
 * the top bits of the address word. */
typedef struct tagSpuMalloc {
    u32 addr;
    u32 size;
} SPU_MALLOC;

#define SPU_MALLOC_DEAD_ENTRY (1 << 29)
#define SPU_MALLOC_END_MARKER (1 << 30)
#define SPU_MALLOC_FREE_ENTRY (1 << 31)
#define SPU_MALLOC_ADDR_MASK (~0xF0000000)
#define SPU_MALLOC_DEAD_MARKER (SPU_MALLOC_DEAD_ENTRY | 0x0FFFFFFF)

#define BLK(i) (&((SPU_MALLOC *)_spu_memList)[i])
#define BLK_IS_FREE(i) (BLK(i)->addr & SPU_MALLOC_FREE_ENTRY)
#define BLK_IS_END(i) (BLK(i)->addr & SPU_MALLOC_END_MARKER)
#define BLK_IS_DEAD_MARK(i) (BLK(i)->addr == SPU_MALLOC_DEAD_MARKER)
#define BLK_ADDR(i) (BLK(i)->addr & SPU_MALLOC_ADDR_MASK)
#define BLK_ADDR_END(i) (BLK_ADDR(i) + BLK(i)->size)
#define BLK_SWAP(dst, src)                                                     \
    {                                                                          \
        u32 addr, size;                                                        \
        addr = (src)->addr;                                                    \
        size = (src)->size;                                                    \
        (src)->addr = (dst)->addr;                                             \
        (src)->size = (dst)->size;                                             \
        (dst)->addr = addr;                                                    \
        (dst)->size = size;                                                    \
    }

extern void _spu_gcSPU(void);

extern s32 _spu_AllocBlockNum;
extern s32 _spu_AllocLastNum;
extern s8 *_spu_memList;
extern s32 _spu_rev_reserve_wa;
extern s32 _spu_rev_offsetaddr;

/* Returns the SPU address of a block of at least size bytes, or -1. */
long SpuMalloc(long size) {
    s32 rounded;
    s32 found;
    s32 reserve;
    s32 i;

    i = 0;
    found = -1;

    if (_spu_rev_reserve_wa == 0) {
        reserve = 0;
    } else {
        reserve = (0x10000 - _spu_rev_offsetaddr) << _spu_mem_mode_plus;
    }

    rounded = size;
    if (size & ~_spu_mem_mode_unitM) {
        rounded += _spu_mem_mode_unitM;
    }

    size = rounded;
    size >>= _spu_mem_mode_plus;
    size <<= _spu_mem_mode_plus;

    if (BLK_IS_END(0)) {
        found = 0;
    } else {
        _spu_gcSPU();

        for (; i < _spu_AllocBlockNum; i++) {
            if (BLK_IS_END(i) || (BLK_IS_FREE(i) && BLK(i)->size >= size)) {
                found = i;
                break;
            }
        }
    }

    if (found == -1) {
        return -1;
    }

    if (BLK_IS_END(found)) {
        if (found < _spu_AllocBlockNum && BLK(found)->size - reserve >= size) {
            s32 next = found + 1;

            BLK(next)->addr =
                (*(volatile u32 *)&BLK(found)->addr & SPU_MALLOC_ADDR_MASK) +
                size;
            BLK(next)->addr |= SPU_MALLOC_END_MARKER;
            BLK(next)->size = BLK(found)->size - size;

            BLK(found)->addr &= SPU_MALLOC_ADDR_MASK;
            BLK(found)->size = size;

            _spu_AllocLastNum = next;
            _spu_gcSPU();

            return BLK(found)->addr;
        }
    } else {
        if (size < BLK(found)->size && _spu_AllocLastNum < _spu_AllocBlockNum) {
            u32 tAddr, tSize;
            u32 addr = BLK(found)->addr + size;
            u32 left = BLK(found)->size - size;

            tAddr = BLK(_spu_AllocLastNum)->addr;
            tSize = BLK(_spu_AllocLastNum)->size;

            BLK(_spu_AllocLastNum)->addr = addr | SPU_MALLOC_FREE_ENTRY;
            BLK(_spu_AllocLastNum)->size = left;

            BLK(_spu_AllocLastNum + 1)->addr = tAddr;
            BLK(_spu_AllocLastNum + 1)->size = tSize;

            _spu_AllocLastNum++;
        }

        BLK(found)->size = size;
        BLK(found)->addr = BLK_ADDR(found);
        _spu_gcSPU();

        return BLK(found)->addr;
    }

    return -1;
}

/* Merges adjacent free blocks, drops empty ones, sorts the rest by address,
 * and trims free blocks off the end of the list. */
void _spu_gcSPU(void) {
    s32 i, j;

    for (i = 0; i <= _spu_AllocLastNum;) {
        if (BLK_IS_FREE(i)) {
            for (j = i + 1; 1; j++) {
                if (!BLK_IS_DEAD_MARK(j)) {
                    break;
                }
            }
            if (BLK_IS_FREE(j) && BLK_ADDR(j) == BLK_ADDR_END(i)) {
                BLK(j)->addr = SPU_MALLOC_DEAD_MARKER;
                BLK(i)->size += BLK(j)->size;
                continue;
            }
        }
        i++;
    }

    for (i = 0; i <= _spu_AllocLastNum; i++) {
        if (BLK(i)->size == 0) {
            BLK(i)->addr = SPU_MALLOC_DEAD_MARKER;
        }
    }

    for (i = 0; i <= _spu_AllocLastNum; i++) {
        if (BLK_IS_END(i)) {
            break;
        }
        for (j = i + 1; j <= _spu_AllocLastNum; j++) {
            if (BLK_IS_END(j)) {
                break;
            }
            if (BLK_ADDR(j) < BLK_ADDR(i)) {
                BLK_SWAP(BLK(j), BLK(i));
            }
        }
    }

    for (i = 0; i <= _spu_AllocLastNum; i++) {
        if (BLK_IS_END(i)) {
            break;
        }
        if (BLK_IS_DEAD_MARK(i)) {
            BLK(i)->addr = BLK(_spu_AllocLastNum)->addr;
            BLK(i)->size = BLK(_spu_AllocLastNum)->size;
            _spu_AllocLastNum = i;
            break;
        }
    }

    for (i = _spu_AllocLastNum - 1; i >= 0; i--) {
        if (BLK_IS_FREE(i) == 0) {
            break;
        }
        BLK(i)->addr = BLK_ADDR(i) | SPU_MALLOC_END_MARKER;
        BLK(i)->size += BLK(_spu_AllocLastNum)->size;
        _spu_AllocLastNum = i;
    }
}

/* Adapted from Sozud's MIT-licensed Psy-Q 3.5 source, src/spu/s_m_f.c. */
typedef struct SpuMallocItem {
    u32 addr;
    u32 size;
} SpuMallocItem;
extern s32 D_800A2704[];
extern SpuMallocItem *D_800A270C[];
extern void _spu_gcSPU(void);
void SpuFree(unsigned long arg0) {
    s32 temp_v1;
    s32 cur_block_num;
    SpuMallocItem *cur_mem;
    s32 temp;
    s32 mask4;
    s32 block_num;
    u8 pad[2];

    cur_block_num = 0;
    if (temp_v1 = D_800A2704[0] > 0) {
        mask4 = 0x40000000;
        temp = arg0 | 0x80000000;
        block_num = D_800A2704[0];
        cur_mem = D_800A270C[0];
        while (1) {
            temp_v1 = cur_mem->addr;
            if (temp_v1 & mask4) {
                break;
            }
            if (temp_v1 == arg0) {
                cur_mem->addr = temp;
                break;
            }
            cur_mem++;
            cur_block_num++;
            if (cur_block_num >= block_num) {
                break;
            }
        }
    }
    _spu_gcSPU();
}

s32 _SpuSetAnyVoice(s32, u32, s32, s32);
void SpuSetNoiseVoice(s32 a, s32 b) {
    _SpuSetAnyVoice(a, b, 0xCA, 0xCB);
}

extern u16 *D_800A26AC[];
s32 _SpuSetAnyVoice(s32 on_off, u32 bits, s32 addr1, s32 addr2) {
    s32 var_t0;
    volatile u16 *spu;
    spu = D_800A26AC[0];
    var_t0 = ((spu[addr2] & 0xFF) << 16) | spu[addr1];
    switch (on_off) {
    case 1:
        var_t0 |= bits & 0xFFFFFF;
        spu[addr1] |= bits;
        spu[addr2] |= ((bits >> 16) & 0xFF);
        break;
    case 0:
        var_t0 &= ~(bits & 0xFFFFFF);
        spu[addr1] &= ~bits;
        spu[addr2] &= ~((bits >> 16) & 0xFF);
        break;
    }
    return var_t0 & 0xFFFFFF;
}

typedef struct SpuReverbPrefix {
    u8 pad[0x1AA];
    u16 spucnt;
} SpuReverbPrefix;
typedef union SpuReverbUnion {
    volatile SpuReverbPrefix rxx;
} SpuReverbUnion;
extern SpuReverbUnion *D_800A26ACReverbA[];
extern SpuReverbUnion *D_800A26ACReverbB[];
extern s32 D_800A2248ReverbRead[];
extern s32 D_800A2248ReverbWrite[];
extern s32 D_800A224CReverb[];
extern s32 D_800A2250Reverb[];
s32 SpuSetReverb(s32 arg0) {
    register s32 value asm("$3");
    register SpuReverbUnion *spu asm("$2");
    switch (arg0) {
    case 0:
        spu = D_800A26ACReverbA[0];
        value = spu->rxx.spucnt;
        D_800A2248ReverbWrite[0] = 0;
        value &= 0xFF7F;
        spu->rxx.spucnt = value;
        break;
    case 1:
        if (D_800A224CReverb[0] != arg0 &&
            _SpuIsInAllocateArea_(D_800A2250Reverb[0]) != 0) {
            spu = D_800A26ACReverbB[0];
            value = spu->rxx.spucnt;
            D_800A2248ReverbWrite[0] = 0;
            value &= 0xFF7F;
            spu->rxx.spucnt = value;
        } else {
            spu = D_800A26ACReverbB[0];
            value = spu->rxx.spucnt;
            D_800A2248ReverbWrite[0] = arg0;
            value |= 0x80;
            spu->rxx.spucnt = value;
        }
        break;
    }
    return D_800A2248ReverbRead[0];
}

/* SPDX-License-Identifier: MIT */

s32 _SpuIsInAllocateArea(u32 arg0) {
    s32 i;

    for (i = 0; 1; i++) {
        if (D_800A270C[0][i].addr & 0x80000000) {
            continue;
        }
        if (D_800A270C[0][i].addr & 0x40000000) {
            break;
        }
        if (arg0 <= (D_800A270C[0][i].addr & 0x0FFFFFFF)) {
            return 1;
        }
        if (arg0 <
            (D_800A270C[0][i].addr & 0x0FFFFFFF) + D_800A270C[0][i].size) {
            return 1;
        }
    }
    return 0;
}

/* SPDX-License-Identifier: MIT */

extern SpuMallocItem *D_800A270C[];
extern s32 D_800A26D0[];

s32 _SpuIsInAllocateArea_(u32 arg0) {
    s32 i;

    arg0 <<= D_800A26D0[0];
    for (i = 0; 1; i++) {
        if (D_800A270C[0][i].addr & 0x80000000) {
            continue;
        }
        if (D_800A270C[0][i].addr & 0x40000000) {
            break;
        }
        if (arg0 <= (D_800A270C[0][i].addr & 0x0FFFFFFF)) {
            return 1;
        }
        if (arg0 <
            (D_800A270C[0][i].addr & 0x0FFFFFFF) + D_800A270C[0][i].size) {
            return 1;
        }
    }
    return 0;
}

struct rev_param_entry {
    u32 flags;
    u16 dAPF1;
    u16 dAPF2;
    u16 vIIR;
    u16 vCOMB1;
    u16 vCOMB2;
    u16 vCOMB3;
    u16 vCOMB4;
    u16 vWALL;
    u16 vAPF1;
    u16 vAPF2;
    u16 mLSAME;
    u16 mRSAME;
    u16 mLCOMB1;
    u16 mRCOMB1;
    u16 mLCOMB2;
    u16 mRCOMB2;
    u16 dLSAME;
    u16 dRSAME;
    u16 mLDIFF;
    u16 mRDIFF;
    u16 mLCOMB3;
    u16 mRCOMB3;
    u16 mLCOMB4;
    u16 mRCOMB4;
    u16 dLDIFF;
    u16 dRDIFF;
    u16 mLAPF1;
    u16 mRAPF1;
    u16 mLAPF2;
    u16 mRAPF2;
    u16 vLIN;
    u16 vRIN;
};

extern SpuReverbAttr _spu_rev_attr;
extern u32 _spu_rev_startaddr[];
extern struct rev_param_entry _spu_rev_param[];
extern s32 _SpuIsInAllocateArea_(u32);
extern void _spu_setReverbAttr();
extern void _spu_FsetRXX(s32, u32, s32);

static __inline__ void spuMemcpy(void *_dst, void *_src, u32 _size) {
    char *pDst = (char *)_dst;
    char *pSrc = (char *)_src;

    while (_size--) {
        *pDst++ = *pSrc++;
    }
}

long SpuSetReverbModeParam(SpuReverbAttr *attr) {
    struct rev_param_entry param;
    long clear_wa;
    long bSetMode;
    long bSetDelay;
    long bSetFeedback;
    long bReverbWasEnabled;
    long mode;
    u32 mask;
    long no_mask;
    long temp;
    long delay;
    long feedback;
    u16 spucnt;

    clear_wa = 0;
    mask = attr->mask;
    bReverbWasEnabled = 0;
    bSetMode = 0;
    bSetDelay = 0;
    bSetFeedback = 0;
    no_mask = (mask == 0);
    param.flags = 0;

    if (no_mask || (mask & SPU_REV_MODE)) {
        mode = attr->mode;
        if (mode & SPU_REV_MODE_CLEAR_WA) {
            mode &= ~SPU_REV_MODE_CLEAR_WA;
            clear_wa = 1;
        }

        if ((u32)mode >= SPU_REV_MODE_MAX ||
            _SpuIsInAllocateArea_(_spu_rev_startaddr[mode])) {
            return -1;
        }

        bSetMode = 1;
        _spu_rev_attr.mode = mode;
        _spu_rev_offsetaddr = _spu_rev_startaddr[_spu_rev_attr.mode];
        spuMemcpy(&param, &_spu_rev_param[_spu_rev_attr.mode], 0x44);

        switch (_spu_rev_attr.mode) {
        case SPU_REV_MODE_ECHO:
            _spu_rev_attr.feedback = 127;
            _spu_rev_attr.delay = 127;
            break;
        case SPU_REV_MODE_DELAY:
            _spu_rev_attr.feedback = 0;
            _spu_rev_attr.delay = 127;
            break;
        default:
            _spu_rev_attr.feedback = 0;
            _spu_rev_attr.delay = 0;
            break;
        }
    }

    if (no_mask || (mask & SPU_REV_DELAYTIME)) {
        if (_spu_rev_attr.mode < 9) {
            if (_spu_rev_attr.mode >= 7) {
                bSetDelay = 1;
                if (!bSetMode) {
                    spuMemcpy(&param, &_spu_rev_param[_spu_rev_attr.mode],
                              0x44);
                    param.flags = 0x0C011C00;
                }
                delay = attr->delay;
                _spu_rev_attr.delay = delay;
                param.mLSAME = ((delay << 13) / 127) - param.dAPF1;
                temp = (delay << 12) / 127;
                param.mRSAME = temp - param.dAPF2;
                param.mLCOMB1 = temp + param.mRCOMB1;
                param.dLSAME = temp + param.dRSAME;
                param.mLAPF1 = temp + param.mLAPF2;
                param.mRAPF1 = temp + param.mRAPF2;
            } else {
                _spu_rev_attr.delay = 0;
            }
        } else {
            _spu_rev_attr.delay = 0;
        }
    }

    if (no_mask || (mask & SPU_REV_FEEDBACK)) {
        if (_spu_rev_attr.mode < 9) {
            if (_spu_rev_attr.mode >= 7) {
                bSetFeedback = 1;
                if (!bSetMode) {
                    if (!bSetDelay) {
                        spuMemcpy(&param, &_spu_rev_param[_spu_rev_attr.mode],
                                  0x44);
                        param.flags = 0x80;
                    } else {
                        param.flags |= 0x80;
                    }
                }
                feedback = attr->feedback;
                _spu_rev_attr.feedback = feedback;
                param.vWALL = (feedback * 0x8100) / 127;
            } else {
                _spu_rev_attr.feedback = 0;
            }
        } else {
            _spu_rev_attr.feedback = 0;
        }
    }

    if (bSetMode) {
        bReverbWasEnabled = (_spu_RXX->rxx.spucnt) >> 7 & 1;
        if (bReverbWasEnabled) {
            spucnt = _spu_RXX->rxx.spucnt;
            spucnt &= 0xFF7F;
            _spu_RXX->rxx.spucnt = spucnt;
        }
    }

    if (!bSetMode) {
        if (no_mask || (mask & SPU_REV_DEPTHL)) {
            _spu_RXX->rxx.revVolLeft = attr->depth.left;
            _spu_rev_attr.depth.left = attr->depth.left;
        }
        if (no_mask || (mask & SPU_REV_DEPTHR)) {
            _spu_RXX->rxx.revVolRight = attr->depth.right;
            _spu_rev_attr.depth.right = attr->depth.right;
        }
    } else {
        _spu_RXX->rxx.revVolLeft = 0;
        _spu_RXX->rxx.revVolRight = 0;
        _spu_rev_attr.depth.left = 0;
        _spu_rev_attr.depth.right = 0;
    }

    if (bSetMode || bSetDelay || bSetFeedback) {
        _spu_setReverbAttr(&param);
    }

    if (clear_wa) {
        SpuClearReverbWorkArea(_spu_rev_attr.mode);
    }

    if (bSetMode) {
        _spu_FsetRXX(0xD1, _spu_rev_offsetaddr, 0);
        if (bReverbWasEnabled) {
            spucnt = _spu_RXX->rxx.spucnt;
            spucnt |= 0x80;
            _spu_RXX->rxx.spucnt = spucnt;
        }
    }

    return 0;
}

typedef struct SpuReverbParams {
    u32 mask;
    u16 value[32];
} SpuReverbParams;
extern volatile u16 *D_800A26ACReverbAttr2[];
void _spu_setReverbAttr(SpuReverbParams *params) {
    s32 mask;
    s32 allFields;
    mask = params->mask;
    allFields = (mask == 0);
    if ((allFields != 0) || (mask & 0x00000001U))
        D_800A26ACReverbAttr2[0][0xE0] = params->value[0];
    if ((allFields != 0) || (mask & 0x00000002U))
        D_800A26ACReverbAttr2[0][0xE1] = params->value[1];
    if ((allFields != 0) || (mask & 0x00000004U))
        D_800A26ACReverbAttr2[0][0xE2] = params->value[2];
    if ((allFields != 0) || (mask & 0x00000008U))
        D_800A26ACReverbAttr2[0][0xE3] = params->value[3];
    if ((allFields != 0) || (mask & 0x00000010U))
        D_800A26ACReverbAttr2[0][0xE4] = params->value[4];
    if ((allFields != 0) || (mask & 0x00000020U))
        D_800A26ACReverbAttr2[0][0xE5] = params->value[5];
    if ((allFields != 0) || (mask & 0x00000040U))
        D_800A26ACReverbAttr2[0][0xE6] = params->value[6];
    if ((allFields != 0) || (mask & 0x00000080U))
        D_800A26ACReverbAttr2[0][0xE7] = params->value[7];
    if ((allFields != 0) || (mask & 0x00000100U))
        D_800A26ACReverbAttr2[0][0xE8] = params->value[8];
    if ((allFields != 0) || (mask & 0x00000200U))
        D_800A26ACReverbAttr2[0][0xE9] = params->value[9];
    if ((allFields != 0) || (mask & 0x00000400U))
        D_800A26ACReverbAttr2[0][0xEA] = params->value[10];
    if ((allFields != 0) || (mask & 0x00000800U))
        D_800A26ACReverbAttr2[0][0xEB] = params->value[11];
    if ((allFields != 0) || (mask & 0x00001000U))
        D_800A26ACReverbAttr2[0][0xEC] = params->value[12];
    if ((allFields != 0) || (mask & 0x00002000U))
        D_800A26ACReverbAttr2[0][0xED] = params->value[13];
    if ((allFields != 0) || (mask & 0x00004000U))
        D_800A26ACReverbAttr2[0][0xEE] = params->value[14];
    if ((allFields != 0) || (mask & 0x00008000U))
        D_800A26ACReverbAttr2[0][0xEF] = params->value[15];
    if ((allFields != 0) || (mask & 0x00010000U))
        D_800A26ACReverbAttr2[0][0xF0] = params->value[16];
    if ((allFields != 0) || (mask & 0x00020000U))
        D_800A26ACReverbAttr2[0][0xF1] = params->value[17];
    if ((allFields != 0) || (mask & 0x00040000U))
        D_800A26ACReverbAttr2[0][0xF2] = params->value[18];
    if ((allFields != 0) || (mask & 0x00080000U))
        D_800A26ACReverbAttr2[0][0xF3] = params->value[19];
    if ((allFields != 0) || (mask & 0x00100000U))
        D_800A26ACReverbAttr2[0][0xF4] = params->value[20];
    if ((allFields != 0) || (mask & 0x00200000U))
        D_800A26ACReverbAttr2[0][0xF5] = params->value[21];
    if ((allFields != 0) || (mask & 0x00400000U))
        D_800A26ACReverbAttr2[0][0xF6] = params->value[22];
    if ((allFields != 0) || (mask & 0x00800000U))
        D_800A26ACReverbAttr2[0][0xF7] = params->value[23];
    if ((allFields != 0) || (mask & 0x01000000U))
        D_800A26ACReverbAttr2[0][0xF8] = params->value[24];
    if ((allFields != 0) || (mask & 0x02000000U))
        D_800A26ACReverbAttr2[0][0xF9] = params->value[25];
    if ((allFields != 0) || (mask & 0x04000000U))
        D_800A26ACReverbAttr2[0][0xFA] = params->value[26];
    if ((allFields != 0) || (mask & 0x08000000U))
        D_800A26ACReverbAttr2[0][0xFB] = params->value[27];
    if ((allFields != 0) || (mask & 0x10000000U))
        D_800A26ACReverbAttr2[0][0xFC] = params->value[28];
    if ((allFields != 0) || (mask & 0x20000000U))
        D_800A26ACReverbAttr2[0][0xFD] = params->value[29];
    if ((allFields != 0) || (mask & 0x40000000U))
        D_800A26ACReverbAttr2[0][0xFE] = params->value[30];
    if ((allFields != 0) || (mask & 0x80000000U))
        D_800A26ACReverbAttr2[0][0xFF] = params->value[31];
}

void SpuSetReverbVoice(s32 a, s32 b) {
    _SpuSetAnyVoice(a, b, 0xCC, 0xCD);
}

extern s32 D_800A2710Clear[];
extern s32 D_800A2298Clear[];
extern u8 D_800A22A0Clear[];
extern s32 D_800A26C4ClearRead[];
extern s32 D_800A26C4ClearWrite[];
extern s32 D_800A26D0Clear0[];
extern s32 D_800A26D0Clear2[];
extern s32 D_800A26E0ClearCheck[];
extern s32 D_800A26E0ClearSave[];
extern s32 D_800A26E0ClearWrite[];
extern s32 D_800A26E0ClearRestore[];
long SpuClearReverbWorkArea(long arg0) {
    volatile s32 sp10;
    s32 temp_a0;
    s32 *temp_s1;
    s32 *new_var;
    s32 temp_s4;
    s32 var_s2;
    s32 var_s3;
    s32 var_s5;
    u32 var_s0;
    u32 var_s1;
    sp10 = 0;
    var_s5 = 0;
    if ((u32)arg0 >= 10)
        return -1;
    new_var = D_800A2710Clear;
    temp_s1 = new_var + arg0;
    if (_SpuIsInAllocateArea_(*temp_s1) != 0)
        return -1;
    if (arg0 == 0) {
        var_s1 = 0x10 << D_800A26D0Clear0[0];
        var_s2 = 0xFFF0 << D_800A26D0Clear0[0];
    } else {
        temp_a0 = *temp_s1;
        var_s1 = (0x10000 - temp_a0) << D_800A26D0Clear2[0];
        var_s2 = temp_a0 << D_800A26D0Clear2[0];
    }
    temp_s4 = D_800A26C4ClearRead[0];
    if (temp_s4 == 1) {
        D_800A26C4ClearWrite[0] = 0;
        var_s5 = 1;
    }
    if (D_800A26E0ClearCheck[0] != 0) {
        do {
            var_s3 = 1;
        } while (0);
        sp10 = D_800A26E0ClearSave[0];
        do {
        } while (0);
        D_800A26E0ClearWrite[0] = 0;
    }
    asm("" : "=r"(var_s1) : "0"(var_s1));
    do {
        var_s0 = var_s1;
        if (var_s1 >= 0x401) {
            var_s0 = 0x400;
        } else {
            var_s3 = 0;
        }
        _spu_t(2, (u32)var_s2);
        _spu_t(1);
        _spu_t(3, D_800A22A0Clear, var_s0);
        temp_a0 = D_800A2298Clear[0];
        asm volatile("" : : "r"(temp_a0));
        var_s1 -= 0x400;
        var_s2 += 0x400;
        WaitEvent(temp_a0);
    } while (var_s3 != 0);
    asm("" : "=r"(var_s0) : "0"(var_s0));
    asm("" : "=r"(var_s0) : "0"(var_s0));
    if (var_s5 != 0)
        D_800A26C4ClearWrite[0] = temp_s4;
    if (sp10 != 0)
        D_800A26E0ClearRestore[0] = sp10;
    return 0;
}

ASM_FUNC(WaitEvent, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                    "    jr $t2 # maspsx-keep\n"
                    "    addiu $t1, $zero, 0xA # maspsx-keep\n"
                    "    nop # maspsx-keep\n")

INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090B80);
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090BA0);
typedef struct SpuIRQPrefix {
    u8 pad[0x1AA];
    u16 control;
} SpuIRQPrefix;
typedef union SpuIRQUnion {
    volatile SpuIRQPrefix rxx;
} SpuIRQUnion;
extern SpuIRQUnion *D_800A26ACIRQ[];
extern char D_80090B80[];
extern char D_80090BA0[];
extern s32 printf(const char *, ...);
s32 SpuSetIRQ(s32 arg0) {
    u16 value;
    SpuIRQUnion *spu;
    u32 i;
    if (arg0 == 0 || arg0 == 3) {
        spu = D_800A26ACIRQ[0];
        value = spu->rxx.control;
        value &= 0xFFBF;
        spu->rxx.control = value;
        i = 0;
        while (spu->rxx.control & 0x40) {
            i++;
            if (i > 0xF00) {
                printf(D_80090B80);
                return -1;
            }
            spu = D_800A26ACIRQ[0];
        }
    }
    if (arg0 == 1 || arg0 == 3) {
        spu = D_800A26ACIRQ[0];
        value = spu->rxx.control;
        value |= 0x40;
        spu->rxx.control = value;
        i = 0;
        while ((spu->rxx.control & 0x40) == 0) {
            i++;
            if (i > 0xF00) {
                printf(D_80090BA0);
                return -1;
            }
            spu = D_800A26ACIRQ[0];
        }
    }
    return arg0;
}

u32 _spu_FsetRXXa(s32, u32);
s32 SpuSetIRQAddr(u32 addr) {
    if (0x7FFF8 < addr) {
        return 0;
    }
    return _spu_FsetRXXa(0xD2, addr);
}

extern SpuIRQCallbackProc D_800A26E0[];
extern SpuIRQCallbackProc D_800A26E4[];
void _SpuCallback(s32);
SpuIRQCallbackProc SpuSetIRQCallback(SpuIRQCallbackProc func) {
    SpuIRQCallbackProc previous;
    previous = D_800A26E4[0];
    if (func != previous) {
        D_800A26E0[1] = func;
        _SpuCallback((s32)func);
    }
    return previous;
}

void _SpuCallback(s32 arg0) {
    InterruptCallback(9, arg0);
}

/* Each case needs its own base pointer, a u16 copy of the low half, and a
 * pointer local for the D_800A229C read. */
void SpuSetKey(long on_off, unsigned long voice_bit) {
    extern s32 D_800A229C[];
    u32 bits;
    volatile u16 *regsOn;
    volatile u16 *regsOff;
    u16 lo;
    u32 hi;
    s32 *keyStat;
    bits = voice_bit & 0xFFFFFF;
    hi = bits >> 16;
    lo = bits;
    switch (on_off) {
    case 1:
        regsOn = D_800A26AC[0];
        regsOn[0xC4] = lo;
        regsOn[0xC5] = hi;
        keyStat = (s32 *)D_800A229C;
        D_800A229CInit[0] = *keyStat | bits;
        break;
    case 0:
        regsOff = D_800A26AC[0];
        regsOff[0xC6] = lo;
        regsOff[0xC7] = hi;
        keyStat = (s32 *)D_800A229C;
        D_800A229CInit[0] = *keyStat & ~bits;
        break;
    }
}

/* SPDX-License-Identifier: MIT */

extern s32 _SpuSetVoiceAttr(SpuVoiceAttr *, s32, s32, s32);

void SpuSetVoiceAttr(SpuVoiceAttr *arg) {
    _SpuSetVoiceAttr(arg, 0, 23, 0);
}

extern u16 _spu_note2pitch();
extern volatile u16 *D_800A26ACVA[];
s32 _SpuSetVoiceAttr(SpuVoiceAttr *arg, s32 min, s32 max, s32 sw) {
    volatile s32 i;
    volatile s32 delay;
    s32 ch;
    s32 ch8;
    u32 attrMask;
    s32 maskFlag;
    u16 vl;
    u16 vr;
    s32 mode;
    u16 rate;
    u16 note;
    u16 pitchNote;
    s32 low;
    u16 volume;

    vl = 0;
    vr = 0;
    attrMask = arg->mask;
    maskFlag = attrMask == 0;
    if (min < 0) {
        min = 0;
    }
    if (min >= 24) {
        return -3;
    }
    if (max >= 24) {
        max = 23;
    }
    if (max < 0 || max < min) {
        return -3;
    }
    max++;
    for (ch = min; ch < max; ch++) {
        if (!((1 << ch) & arg->voice)) {
            continue;
        }
        ch8 = ch << 3;
        if (maskFlag || (attrMask & 0x10)) {
            D_800A26ACVA[0][ch * 8 + 2] = arg->pitch;
        }
        if (maskFlag || (attrMask & 0x40)) {
            gSpuVoiceCenterNotes[ch] = arg->sample_note;
        }
        if (maskFlag || (attrMask & 0x20)) {
            note = gSpuVoiceCenterNotes[ch];
            pitchNote = arg->note;
            D_800A26ACVA[0][ch8 + 2] = _spu_note2pitch(
                note >> 8, note & 0xFF, pitchNote >> 8, pitchNote & 0xFF);
        }
        if (maskFlag || (attrMask & 0x80)) {
            _spu_FsetRXXa(ch8 | 3, arg->addr);
        }
        if (maskFlag || (attrMask & 0x800)) {
            if (maskFlag || (attrMask & 0x100)) {
                switch (arg->a_mode) {
                case 1:
                    mode = 0;
                    break;
                case 5:
                    mode = 0x80;
                    break;
                default:
                    mode = 0;
                    break;
                }
            } else {
                mode = 0;
            }
            rate = 0x7F;
            if (arg->ar < 0x80) {
                rate = arg->ar;
            }
            low = D_800A26ACVA[0][ch8 + 4] & 0xFF;
            D_800A26ACVA[0][ch8 + 4] = low | ((rate | mode) << 8);
        }
        if (maskFlag || (attrMask & 0x1000)) {
            if (arg->dr >= 0x10) {
                rate = 0xF;
            } else {
                rate = arg->dr;
            }
            low = D_800A26ACVA[0][ch8 + 4] & 0xFF0F;
            D_800A26ACVA[0][ch8 + 4] = low | (rate << 4);
        }
        if (maskFlag || (attrMask & 0x8000)) {
            if (arg->sl >= 0x10) {
                rate = 0xF;
            } else {
                rate = arg->sl;
            }
            D_800A26ACVA[0][ch8 + 4] =
                rate | (D_800A26ACVA[0][ch8 + 4] & 0xFFF0);
        }
        if (maskFlag || (attrMask & 0x2000)) {
            if (maskFlag || (attrMask & 0x200)) {
                switch (arg->s_mode) {
                case 1:
                    mode = 0;
                    break;
                case 3:
                    mode = 0x100;
                    break;
                case 5:
                    mode = 0x200;
                    break;
                case 7:
                    mode = 0x300;
                    break;
                default:
                    mode = 0x100;
                    break;
                }
            } else {
                mode = 0;
            }
            rate = 0x7F;
            if (arg->sr < 0x80) {
                rate = arg->sr;
            }
            low = D_800A26ACVA[0][ch8 + 5] & 0x3F;
            D_800A26ACVA[0][ch8 + 5] = low | ((rate | mode) << 6);
        }
        if (maskFlag || (attrMask & 0x4000)) {
            if (maskFlag || (attrMask & 0x400)) {
                switch (arg->r_mode) {
                case 3:
                    mode = 0;
                    break;
                case 7:
                    mode = 0x20;
                    break;
                default:
                    mode = 0;
                    break;
                }
            } else {
                mode = 0;
            }
            rate = 0x1F;
            if (arg->rr < 0x20) {
                rate = arg->rr;
            }
            low = D_800A26ACVA[0][ch8 + 5] & 0xFFC0;
            D_800A26ACVA[0][ch8 + 5] = low | (rate | mode);
        }
        if (maskFlag || (attrMask & 0x20000)) {
            D_800A26ACVA[0][ch8 + 4] = arg->adsr1;
        }
        if (maskFlag || (attrMask & 0x40000)) {
            D_800A26ACVA[0][ch8 + 5] = arg->adsr2;
        }
        if (maskFlag || (attrMask & 0x10000)) {
            _spu_FsetRXXa(ch8 | 7, arg->loop_addr);
        }
        if (maskFlag || (attrMask & 1)) {
            if (maskFlag || (attrMask & 4)) {
                switch (*(s16 *)&arg->volmode.left) {
                case 1:
                    mode = 0x8000;
                    break;
                case 2:
                    mode = 0x9000;
                    break;
                case 3:
                    mode = 0xA000;
                    break;
                case 4:
                    mode = 0xB000;
                    break;
                case 5:
                    mode = 0xC000;
                    break;
                case 6:
                    mode = 0xD000;
                    break;
                case 7:
                    mode = 0xE000;
                    break;
                case 0:
                default:
                    vl = arg->volume.left;
                    mode = 0;
                    break;
                }
            } else {
                vl = arg->volume.left;
                mode = 0;
            }
            if (mode != 0) {
                if (*(s16 *)&arg->volume.left >= 0x80) {
                    vl = 0x7F;
                } else if (*(s16 *)&arg->volume.left < 0) {
                    vl = 0;
                } else {
                    vl = *(s16 *)&arg->volume.left;
                }
            }
            volume = vl & 0x7FFF;
            D_800A26ACVA[0][ch8] = volume | mode;
        }
        if (maskFlag || (attrMask & 2)) {
            if (maskFlag || (attrMask & 8)) {
                switch (*(s16 *)&arg->volmode.right) {
                case 1:
                    mode = 0x8000;
                    break;
                case 2:
                    mode = 0x9000;
                    break;
                case 3:
                    mode = 0xA000;
                    break;
                case 4:
                    mode = 0xB000;
                    break;
                case 5:
                    mode = 0xC000;
                    break;
                case 6:
                    mode = 0xD000;
                    break;
                case 7:
                    mode = 0xE000;
                    break;
                case 0:
                default:
                    vr = arg->volume.right;
                    mode = 0;
                    break;
                }
            } else {
                vr = arg->volume.right;
                mode = 0;
            }
            if (mode != 0) {
                if (*(s16 *)&arg->volume.right >= 0x80) {
                    vr = 0x7F;
                } else if (*(s16 *)&arg->volume.right < 0) {
                    vr = 0;
                } else {
                    vr = *(s16 *)&arg->volume.right;
                }
            }
            volume = vr & 0x7FFF;
            D_800A26ACVA[0][ch8 + 1] = volume | mode;
        }
    }
    if (sw == 0) {
        delay = 1;
        for (i = 0; i < 2; i++) {
            delay *= 13;
        }
    }
    return 0;
}

s32 SpuGetKeyStatus(s32 voice_bit) {
    extern u16 *D_800A26AC[];
    extern s32 D_800A229C[];
    s32 i;
    s32 voice;
    s32 mask;
    s32 mask2;
    s32 mask3;
    u16 volx;

    voice = -1;
    for (i = 0; i < 24; i++) {
        mask = 1 << i;
        if (voice_bit & mask) {
            voice = i;
            break;
        }
    }
    if (voice == -1) {
        return -1;
    }
    volx = *((u16 *)(voice * 0x10 + (u8 *)D_800A26AC[0]) + 6);
    mask3 = 1 << voice;
    mask2 = mask3 & D_800A229C[0];
    if (mask2 != 0) {
        if (volx != 0) {
            return 1;
        }
        return 3;
    }
    return (volx > 0) * 2;
}

/* SPDX-License-Identifier: MIT */

extern SpuIRQCallbackProc D_800A26E0[];
extern s32 D_800A26DC[];
extern s32 _spu_write(u8 *, u32);

unsigned long SpuWrite(unsigned char *addr, unsigned long size) {
    if (size > 0x7F000U) {
        size = 0x7F000;
    }
    _spu_write((u8 *)addr, (u32)size);
    if (D_800A26E0[0] == 0) {
        D_800A26DC[0] = 0;
    }
    return size;
}

extern u16 D_800A26A8[];
u32 _spu_FsetRXXa(s32, u32);
s32 SpuSetTransferStartAddr(s32 addr) {
    D_800A26A8[0] = _spu_FsetRXXa(-1, addr);
    return addr;
}

extern long D_800A2244[];
extern long D_800A26C4[];
long SpuSetTransferMode(long mode) {
    s32 transMode;
    switch (mode) {
    case 0:
        transMode = 0;
        break;
    case 1:
        transMode = 1;
        break;
    default:
        transMode = 0;
    }
    D_800A2244[0] = mode;
    D_800A26C4[0] = transMode;
    return transMode;
}

extern long D_800A2244[];
extern s32 D_800A26DC[];
extern s32 D_800A2298[];
extern s32 TestEvent(s32);
s32 SpuIsTransferCompleted(s32 immediateFlag) {
    s32 status;
    if (D_800A2244[0] == 1 || D_800A26DC[0] == 1) {
        return 1;
    }
    status = TestEvent(D_800A2298[0]);
    if (immediateFlag == 1) {
        if (status == 0) {
            do {
                status = TestEvent(D_800A2298[0]);
            } while (status == 0);
        }
        status = 1;
        goto saveStatus;
    }
    if (status != 1) {
        return status;
    }
saveStatus:
    D_800A26DC[0] = status;
    return status;
}

typedef struct SpuCallbackStorage {
    SpuIRQCallbackProc callback;
    SpuIRQCallbackProc pending;
    s32 padding;
} SpuCallbackStorage;
extern SpuCallbackStorage D_800A26E0Read;
extern SpuCallbackStorage D_800A26E0Write;
SpuIRQCallbackProc SpuSetTransferCallback(SpuIRQCallbackProc func) {
    SpuIRQCallbackProc previous;
    previous = D_800A26E0Read.callback;
    if (func != previous) {
        D_800A26E0Write.callback = func;
    }
    return previous;
}

extern s32 D_800A26DC[];
void _spu_setInTransfer(s32 arg0) {
    if (arg0 == 1) {
        D_800A26DC[0] = 0;
    } else {
        D_800A26DC[0] = 1;
    }
}

extern s32 D_800A26DC[];
s32 _spu_getInTransfer(void) {
    return D_800A26DC[0] == 0;
}

void SpuSetCommonAttrDraft(SpuCommonAttr *) asm("SpuSetCommonAttr");
extern volatile u16 *D_800A26ACCommon2[];
void SpuSetCommonAttrDraft(SpuCommonAttr *arg0) {
    s32 mask;
    s32 isDefault;
    s32 level;
    s32 volume;
    u16 volLeft;
    u16 volRight;
    s32 modeLeft;
    s32 modeRight;
    s32 modeCode;
    s32 value;
    volatile u16 *control;
    mask = arg0->mask;
    isDefault = (mask == 0);
    volLeft = 0;
    volRight = 0;
    modeLeft = 0;
    modeRight = 0;
    if (isDefault || (mask & 1)) {
        if (isDefault || (mask & 4)) {
            modeCode = (s16)arg0->mvolmode.left;
            switch (modeCode) {
            case 1:
                modeLeft = 0x8000;
                break;
            case 2:
                modeLeft = 0x9000;
                break;
            case 3:
                modeLeft = 0xA000;
                break;
            case 4:
                modeLeft = 0xB000;
                break;
            case 5:
                modeLeft = 0xC000;
                break;
            case 6:
                modeLeft = 0xD000;
                break;
            case 7:
                modeLeft = 0xE000;
                break;
            case 0:
            default:
                volLeft = arg0->mvol.left;
                modeLeft = 0;
                break;
            }
        } else {
            volLeft = arg0->mvol.left;
            modeLeft = 0;
        }
        if (modeLeft != 0) {
            if (*(s16 *)&arg0->mvol.left >= 0x80) {
                volLeft = 0x7F;
            } else if (*(s16 *)&arg0->mvol.left < 0) {
                volLeft = 0;
            } else {
                volLeft = *(s16 *)&arg0->mvol.left;
            }
            volume = volLeft & 0x7FFF;
        } else {
            volume = volLeft & 0x7FFF;
        }
        control = D_800A26ACCommon2[0];
        control[0x180 / 2] = volume | modeLeft;
    }
    if (isDefault || (mask & 2)) {
        if (isDefault || (mask & 8)) {
            modeCode = (s16)arg0->mvolmode.right;
            switch (modeCode) {
            case 1:
                modeRight = 0x8000;
                break;
            case 2:
                modeRight = 0x9000;
                break;
            case 3:
                modeRight = 0xA000;
                break;
            case 4:
                modeRight = 0xB000;
                break;
            case 5:
                modeRight = 0xC000;
                break;
            case 6:
                modeRight = 0xD000;
                break;
            case 7:
                modeRight = 0xE000;
                break;
            case 0:
            default:
                volRight = arg0->mvol.right;
                modeRight = 0;
                break;
            }
        } else {
            volRight = arg0->mvol.right;
            modeRight = 0;
        }
        if (modeRight != 0) {
            if (*(s16 *)&arg0->mvol.right >= 0x80) {
                volRight = 0x7F;
            } else if (*(s16 *)&arg0->mvol.right < 0) {
                volRight = 0;
            } else {
                volRight = *(s16 *)&arg0->mvol.right;
            }
            volume = volRight & 0x7FFF;
        } else {
            volume = volRight & 0x7FFF;
        }
        control = D_800A26ACCommon2[0];
        control[0x182 / 2] = volume | modeRight;
    }
    if (isDefault || (mask & 0x40))
        D_800A26ACCommon2[0][0x1B0 / 2] = arg0->cd.volume.left;
    if (isDefault || (mask & 0x80))
        D_800A26ACCommon2[0][0x1B2 / 2] = arg0->cd.volume.right;
    if (isDefault || (mask & 0x100)) {
        register volatile u16 *ctl asm("$2");

        if (arg0->cd.reverb == 0) {
            ctl = D_800A26ACCommon2[0];
            value = ctl[0x1AA / 2];
            value &= 0xFFFB;
        } else {
            ctl = D_800A26ACCommon2[0];
            value = ctl[0x1AA / 2];
            value |= 4;
        }
        ctl[0x1AA / 2] = value;
    }
    if (isDefault || (mask & 0x200)) {
        register volatile u16 *ctl asm("$2");

        if (arg0->cd.mix == 0) {
            ctl = D_800A26ACCommon2[0];
            value = ctl[0x1AA / 2];
            value &= 0xFFFE;
        } else {
            ctl = D_800A26ACCommon2[0];
            value = ctl[0x1AA / 2];
            value |= 1;
        }
        ctl[0x1AA / 2] = value;
    }
    if (isDefault || (mask & 0x400))
        D_800A26ACCommon2[0][0x1B4 / 2] = arg0->ext.volume.left;
    if (isDefault || (mask & 0x800))
        D_800A26ACCommon2[0][0x1B6 / 2] = arg0->ext.volume.right;
    if (isDefault || (mask & 0x1000)) {
        register volatile u16 *ctl asm("$2");

        if (arg0->ext.reverb == 0) {
            ctl = D_800A26ACCommon2[0];
            value = ctl[0x1AA / 2];
            value &= 0xFFF7;
        } else {
            ctl = D_800A26ACCommon2[0];
            value = ctl[0x1AA / 2];
            value |= 8;
        }
        ctl[0x1AA / 2] = value;
    }
    if (isDefault || (mask & 0x2000)) {
        register volatile u16 *ctl asm("$2");

        if (arg0->ext.mix == 0) {
            ctl = D_800A26ACCommon2[0];
            value = ctl[0x1AA / 2];
            value &= 0xFFFD;
        } else {
            ctl = D_800A26ACCommon2[0];
            value = ctl[0x1AA / 2];
            value |= 2;
        }
        ctl[0x1AA / 2] = value;
    }
}

extern u16 D_800A2A08[];
/* D_800A2A08 holds 12 rows of 16 columns. key % 12 picks the row, the fine
 * sum / 8 picks the column, and key / 12 sets the octave shift. */
u16 _spu_note2pitch(centerNote, centerFine, note, fine)
s32 centerNote;
u16 centerFine;
s32 note;
u16 fine;
{
    s16 shift;
    s16 fineIdx;
    s32 carry;
    s16 key;
    s16 semitone;
    s32 biased;
    u16 pitch;
    fineIdx = (fine + centerFine) / 8;
    carry = 0;
    while (fineIdx >= 16) {
        fineIdx -= 16;
        carry++;
    }
    if (fineIdx < 0) {
        fineIdx = 0;
    }
    biased = note + 60;
    key = carry + (biased - centerNote);
    semitone = key % 12;
    pitch = D_800A2A08[(semitone << 4) + fineIdx];
    shift = key / 12 - 5;
    if (shift > 0) {
        pitch <<= shift;
    } else if (shift < 0) {
        pitch >>= -shift;
    }
    return pitch;
}

/* The inverse of _spu_note2pitch. The highest set bit of the pitch gives the
 * octave. The offset above 1 << hi, scaled by 12, gives the semitone, and the
 * remainder, scaled by 128, adds to the fine value. The result is
 * (note << 8) | fine, or -1 when the note is outside 0 to 127. */
s32 _spu_pitch2note(note, fine, pitch)
u16 note;
u16 fine;
u16 pitch;
{
    s32 i;
    s32 hi;
    s32 range;
    s32 off;
    s32 semis;
    s32 rem;
    s32 fineSum;
    s32 key;
    s32 fineOut;
    hi = 0;
    for (i = 0; i < 16; i++) {
        if ((pitch >> i) & 1) {
            hi = i;
        }
    }
    range = (1 << (hi + 1)) - (1 << hi);
    off = pitch - (1 << hi);
    semis = (off * 12) / range;
    rem = off - (range * semis) / 12;
    key = note + (hi - 12) * 12 + semis;
    fineSum = fine + (rem * 0x600) / range;
    fineOut = fineSum % 128;
    key += fineSum >= 128;
    if (key >= 0) {
        if (key < 128) {
            return (key << 8) | fineOut;
        }
    }
    return -1;
}

/* Fills status[min..max] with the key state of each voice: 1 when the voice
 * is keyed on and has a volume, 3 when keyed on with no volume, 2 when keyed
 * off with a volume, 0 otherwise. Returns -3 for a bad range. */
extern s32 _spu_keystat;

s32 SpuRGetAllKeysStatus(s32 min, s32 max, s8 *status) {
    s32 voice;
    s32 one;
    u16 volume;
    if (min < 0)
        min = 0;
    if (min >= 24)
        return -3;
    if (max >= 24)
        max = 23;
    if (max < 0 || max < min)
        return -3;
    max++;
    for (voice = min; voice < max; voice++) {
        one = 1;
        volume = D_800A26AC[0][(8 * voice) + 6];
        if ((one << voice) & _spu_keystat) {
            if (volume != 0)
                status[voice] = one;
            else
                status[voice] = 3;
        } else {
            if (volume != 0)
                status[voice] = 2;
            else
                status[voice] = 0;
        }
    }
    return 0;
}

void SpuGetAllKeysStatus(s8 *status) {
    extern u16 *D_800A26AC[];
    extern s32 D_800A229C[];
    s32 i;
    s32 n;
    s32 one;
    s32 three;
    s32 two;
    s32 mask;
    s32 mask2;
    u16 volx;
    u8 *p;
    u16 *vptr;
    s32 off;
    u8 *base;

    n = 24;
    i = 0;
    one = 1;
    three = 3;
    two = 2;
    p = (u8 *)status;
again:
    base = (u8 *)D_800A26AC[0];
    off = i * 0x10;
    vptr = (u16 *)(off + (u32)base);
    mask = one << i;
    mask2 = mask & D_800A229C[0];
    volx = vptr[6];
    if (mask2 != 0) {
        if (volx != 0) {
            *p = one;
        } else {
            *p = three;
        }
    } else {
        if (volx != 0) {
            *p = two;
        } else {
            *p = 0;
        }
    }
    p++;
    i++;
    if (i < n) {
        goto again;
    }
}

ASM_FUNC(exit, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
               "    jr $t2 # maspsx-keep\n"
               "    addiu $t1, $zero, 0x38 # maspsx-keep\n"
               "    nop # maspsx-keep\n")

ASM_FUNC(puts, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
               "    jr $t2 # maspsx-keep\n"
               "    addiu $t1, $zero, 0x3F # maspsx-keep\n"
               "    nop # maspsx-keep\n")

ASM_FUNC(setjmp, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x13 # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(strcat, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x15 # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(strcmp, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x17 # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(strcpy, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x19 # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(strlen, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x1B # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(bzero, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                "    jr $t2 # maspsx-keep\n"
                "    addiu $t1, $zero, 0x28 # maspsx-keep\n"
                "    nop # maspsx-keep\n")

ASM_FUNC(memcpy, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x2A # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(memset_8008B820, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                          "    jr $t2 # maspsx-keep\n"
                          "    addiu $t1, $zero, 0x2B # maspsx-keep\n"
                          "    nop # maspsx-keep\n")

ASM_FUNC(printf, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x3F # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

typedef struct SprintfFormat {
    unsigned left : 1;
    unsigned plus : 1;
    unsigned alternate : 1;
    unsigned zero : 1;
    unsigned precisionSet : 1;
    unsigned shortArg : 1;
    unsigned longArg : 1;
    unsigned longDouble : 1;
    u8 sign;
    s32 width;
    s32 precision;
} SprintfFormat;
extern SprintfFormat gSprintfDefaultFormat[];
extern void *memchr(const void *, s32, s32);
extern void *memmove(u8 *, u8 *, s32);
extern u8 sSprintfUpperDigits[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", sSprintfUpperDigits);
extern u8 sSprintfLowerDigits[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", sSprintfLowerDigits);

s32 sprintf(char *dest, char *format, ...) {
    u8 buffer[512];
    SprintfFormat spec;
    u32 *args;
    s32 length;
    u8 *text;
    s32 written;
    s32 accumulator;
    s32 c;
    u32 value;
    u8 *end;
    const u8 *digits;

    /* Keep the SDK argument cursor in its stack slot. */
    (void)&args;
    args = (u32 *)((u8 *)&format + sizeof(format));
    written = 0;
    while ((c = (u8)*format) != 0) {
        if (c == '%') {
            spec = gSprintfDefaultFormat[0];
            for (;;) {
                c = (u8) * ++format;
                if (c == '-') {
                    spec.left = 1;
                } else if (c == '+') {
                    spec.plus = 1;
                } else if (c == ' ') {
                    spec.sign = c;
                } else if (c == '#') {
                    spec.alternate = 1;
                } else if (c == '0') {
                    spec.zero = 1;
                } else {
                    break;
                }
            }
            if (c == '*') {
                spec.width = (s32)*args++;
                if (spec.width < 0) {
                    spec.width = -spec.width;
                    spec.left = 1;
                }
                c = (u8) * ++format;
            } else {
                while ((u32)(c - '0') < 10) {
                    /* Keep the character offset after the multiply. */
                    accumulator = spec.width * 10 - '0';
                    asm("" : "=r"(accumulator) : "0"(accumulator));
                    spec.width = accumulator + c;
                    c = (u8) * ++format;
                }
            }
            if (c == '.') {
                c = (u8) * ++format;
                if (c == '*') {
                    spec.precision = (s32)*args++;
                    c = (u8) * ++format;
                } else {
                    while ((u32)(c - '0') < 10) {
                        accumulator = spec.precision * 10 - '0';
                        asm("" : "=r"(accumulator) : "0"(accumulator));
                        spec.precision = accumulator + c;
                        c = (u8) * ++format;
                    }
                }
                if (spec.precision >= 0) {
                    spec.precisionSet = 1;
                }
            }
            text = buffer + sizeof(buffer);
            if (spec.left) {
                spec.zero = 0;
            }
        convert:
            switch (c) {
            case 'h':
                spec.shortArg = 1;
                c = (u8) * ++format;
                goto convert;
            case 'l':
                spec.longArg = 1;
                c = (u8) * ++format;
                goto convert;
            case 'L':
                spec.longDouble = 1;
                c = (u8) * ++format;
                goto convert;
            case 'd':
            case 'i':
                /* Keep the argument load before the format flags. */
                {
                    register u32 *arg asm("v1");
                    arg = args;
                    args = arg + 1;
                    value = *arg;
                    asm("" : "=r"(value) : "0"(value));
                }
                if (spec.shortArg) {
                    value = (s16)value;
                }
                if ((s32)value < 0) {
                    value = -value;
                    spec.sign = '-';
                } else if (spec.plus) {
                    spec.sign = '+';
                }
                goto decimal;
            case 'u': {
                register u32 *arg asm("v1");
                arg = args;
                args = arg + 1;
                value = *arg;
                asm("" : "=r"(value) : "0"(value));
            }
                if (spec.shortArg) {
                    value = (u16)value;
                }
                spec.sign = 0;
            decimal:
                if (!spec.precisionSet) {
                    if (spec.zero) {
                        spec.precision = spec.width;
                        if (spec.sign) {
                            --spec.precision;
                        }
                    }
                    if (spec.precision <= 0) {
                        spec.precision = 1;
                    }
                }
                length = 0;
                while (value) {
                    *--text = value % 10 + '0';
                    value /= 10;
                    ++length;
                }
                while (length < spec.precision) {
                    *--text = '0';
                    ++length;
                }
                if (spec.sign) {
                    *--text = spec.sign;
                    ++length;
                }
                goto emit;
            case 'o': {
                register u32 *arg asm("v1");
                arg = args;
                args = arg + 1;
                value = *arg;
                asm("" : "=r"(value) : "0"(value));
            }
                if (spec.shortArg) {
                    value = (u16)value;
                }
                if (!spec.precisionSet) {
                    if (spec.zero) {
                        spec.precision = spec.width;
                    }
                    if (spec.precision <= 0) {
                        spec.precision = 1;
                    }
                }
                length = 0;
                while (value) {
                    *--text = (value & 7) + '0';
                    value >>= 3;
                    ++length;
                }
                if (spec.alternate && length && *text != '0') {
                    *--text = '0';
                    ++length;
                }
                while (length < spec.precision) {
                    *--text = '0';
                    ++length;
                }
                goto emit;
            case 'p':
                spec.precision = 8;
                spec.precisionSet = 1;
                spec.longArg = 1;
            case 'X':
                digits = sSprintfUpperDigits;
                goto hexadecimal;
            case 'x':
                digits = sSprintfLowerDigits;
            hexadecimal:
                {
                    register u32 *arg asm("v1");
                    arg = args;
                    args = arg + 1;
                    value = *arg;
                    asm("" : "=r"(value) : "0"(value));
                }
                if (spec.shortArg) {
                    value = (u16)value;
                }
                if (!spec.precisionSet) {
                    if (spec.zero) {
                        spec.precision = spec.width;
                        if (spec.alternate) {
                            spec.precision -= 2;
                        }
                    }
                    if (spec.precision <= 0) {
                        spec.precision = 1;
                    }
                }
                length = 0;
                while (value) {
                    *--text = digits[value & 15];
                    value >>= 4;
                    ++length;
                }
                while (length < spec.precision) {
                    *--text = '0';
                    ++length;
                }
                if (spec.alternate) {
                    *--text = c;
                    *--text = '0';
                    length += 2;
                }
                goto emit;
            case 'c':
                *--text = *(u8 *)args++;
                length = 1;
                goto emit;
            case 's':
                text = (u8 *)*args++;
                if (spec.alternate) {
                    length = *text++;
                    if (spec.precisionSet && spec.precision < length) {
                        length = spec.precision;
                    }
                } else if (!spec.precisionSet) {
                    length = strlen((char *)text);
                } else {
                    end = memchr(text, 0, spec.precision);
                    length = end - text;
                    if (!end) {
                        length = spec.precision;
                    }
                }
                goto emit;
            case 'n': {
                u32 flags;

                text = (u8 *)*args++;
                flags = *(u32 *)&spec;
                if (flags & 0x20) {
                    /* Keep the full flags live through this test. */
                    asm("" : : "r"(flags));
                    *(s16 *)text = written;
                } else {
                    *(s32 *)text = written;
                }
                goto next;
            }
            default:
                if (c != '%') {
                    goto done;
                }
                goto character;
            }
        }
    character:
        dest[written++] = c;
        goto next;
    emit:
        if (length < spec.width && !spec.left) {
            do {
                dest[written++] = ' ';
            } while (length < --spec.width);
        }
        memmove((u8 *)dest + written, text, length);
        written += length;
        while (length < spec.width) {
            dest[written++] = ' ';
            ++length;
        }
    next:
        ++format;
    }
done:
    dest[written] = 0;
    return written;
}

ASM_FUNC(memchr, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x2E # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

void *memmove(u8 *dest, u8 *src, int count) {
    if (dest >= src) {
        while (count-- > 0) {
            dest[count] = src[count];
        }
    } else {
        while (count-- > 0) {
            *dest++ = *src++;
        }
    }

    return dest;
}

extern char *_strtokLast;

char *strtok(char *s, char *delim) {
    u8 c;
    char *spanp;
    s32 found;
    char *tok;

    if (s == 0 && (s = _strtokLast) == 0) {
        return 0;
    }
    while ((c = *s++) != 0) {
        found = 0;
        for (spanp = delim; *spanp != 0; spanp++) {
            if (*spanp == c) {
                found = 1;
                break;
            }
        }
        if (!found) {
            break;
        }
    }
    if (c == 0) {
        _strtokLast = 0;
        return 0;
    }
    tok = s - 1;
    c = *s++;
    while (c != 0) {
        spanp = delim;
        if (*spanp != 0) {
            do {
                if (*spanp++ == c) {
                    s[-1] = 0;
                    _strtokLast = s;
                    return tok;
                }
            } while (*spanp != 0);
        }
        c = *s++;
    }
    _strtokLast = 0;
    return tok;
}

ASM_FUNC(_card_info, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                     "    jr $t2 # maspsx-keep\n"
                     "    addiu $t1, $zero, 0xAB # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

ASM_FUNC(_card_load, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                     "    jr $t2 # maspsx-keep\n"
                     "    addiu $t1, $zero, 0xAC # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

ASM_FUNC(_card_auto, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                     "    jr $t2 # maspsx-keep\n"
                     "    addiu $t1, $zero, 0xAD # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

ASM_FUNC(InitCARD, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                   "    jr $t2 # maspsx-keep\n"
                   "    addiu $t1, $zero, 0x4A # maspsx-keep\n"
                   "    nop # maspsx-keep\n")

ASM_FUNC(StartCARD, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                    "    jr $t2 # maspsx-keep\n"
                    "    addiu $t1, $zero, 0x4B # maspsx-keep\n"
                    "    nop # maspsx-keep\n")

ASM_FUNC(StopCARD, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                   "    jr $t2 # maspsx-keep\n"
                   "    addiu $t1, $zero, 0x4C # maspsx-keep\n"
                   "    nop # maspsx-keep\n")

ASM_FUNC(_card_write, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                      "    jr $t2 # maspsx-keep\n"
                      "    addiu $t1, $zero, 0x4E # maspsx-keep\n"
                      "    nop # maspsx-keep\n")

ASM_FUNC(_card_read, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                     "    jr $t2 # maspsx-keep\n"
                     "    addiu $t1, $zero, 0x4F # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

ASM_FUNC(_new_card, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                    "    jr $t2 # maspsx-keep\n"
                    "    addiu $t1, $zero, 0x50 # maspsx-keep\n"
                    "    nop # maspsx-keep\n")

extern long _new_card(void);
extern long _card_write(long chan, long size, void *data);
long _card_clear(long chan) {
    _new_card();
    return _card_write(chan, 0x3F, 0);
}

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

INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090D1C);
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
 * INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090D38). */
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
 * INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090D48). */
void __maspsx_include_asm_hack_D_80090D48(void) {
    __asm__(".section .rodata # maspsx-keep\n"
            "    .align 2 # maspsx-keep\n"
            "    .globl D_80090D48 # maspsx-keep\n"
            "D_80090D48: # maspsx-keep\n"
            "    .asciz \"MDEC_out_sync\" # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern char D_80090D58[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090D58);
extern char D_80090D80[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090D80);
extern char D_80090DB8[];
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090DB8);
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", D_8008CA04);
