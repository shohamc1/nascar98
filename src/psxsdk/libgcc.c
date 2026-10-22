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

/* clang-format off */
const u8 gLibgccClzTable[256] = {
    0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
};
/* clang-format on */

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
