/* SPDX-License-Identifier: AGPL-3.0-only AND MIT */
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", __SN_ENTRY_POINT);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", __udivmoddi4);

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

extern int CdGetToc2(int mode, u8 *toc);

int CdGetToc(u8 *toc) {
    return CdGetToc2(1, toc);
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdGetToc2);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdInit);
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

int CdMode(void) {
    return D_8009BA9C[0];
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA9D[];

int CdLastCom(void) {
    return D_8009BA9D[0];
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA98[];

unsigned char *CdLastPos(void) {
    return D_8009BA98;
}

/* SPDX-License-Identifier: MIT */

extern int CD_initintr(void);
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
    CdlCB old;

    old = (CdlCB)D_8009BA7C[0];
    ((CdlCB *)D_8009BA80)[-1] = func;
    return old;
}

/* SPDX-License-Identifier: MIT */

extern u32 D_8009BA88[];

CdlCB CdReadyCallback(CdlCB func) {
    CdlCB old;

    old = (CdlCB)D_8009BA80[0];
    ((CdlCB *)D_8009BA88)[-2] = func;
    return old;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdControl);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdControlF);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdControlB);

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

extern void CD_datasync(int mode);

void CdDataSync(int mode) {
    CD_datasync(mode);
}

CdlLOC *CdIntToPos(int i, CdlLOC *p) {
    s32 n = i;
    CdlLOC *out;
    s32 minuteBcd;

    asm volatile(
        "lui\t$3,0x1b4e\n\tori\t$3,$3,0x81b5\n\taddiu\t%0,%0,0x96\n\tmult\t%0,$3\n\taddu\t%1,%3,$0"
        : "=r"(n), "=r"(out)
        : "0"(n), "r"(p));
    asm volatile(
        "lui\t$7,0x6666\n\tori\t$7,$7,0x6667\n\tsra\t$3,%1,31\n\tmfhi\t$6\n\tsra\t$6,$6,0x3\n\tsubu\t$6,$6,$3\n\tsll\t%0,$6,0x2\n\taddu\t%0,%0,$6\n\tsll\t$3,%0,0x4\n\tsubu\t$3,$3,%0\n\tsubu\t%1,%1,$3\n\tmult\t%1,$7\n\tmfhi\t$8\n\tlui\t$3,0x8888\n\tori\t$3,$3,0x8889\n\tmult\t$6,$3\n\tsra\t$3,$6,31\n\tmfhi\t$9\n\taddu\t$9,$9,$6\n\tsra\t$9,$9,0x5\n\tsubu\t$9,$9,$3\n\tsll\t$3,$9,0x4\n\tsubu\t$3,$3,$9\n\tsll\t$3,$3,0x2\n\tsubu\t$6,$6,$3\n\tmult\t$6,$7\n\tsra\t$8,$8,0x2\n\tsra\t$3,%1,31\n\tsubu\t$8,$8,$3\n\tsll\t$3,$8,0x2\n\taddu\t$3,$3,$8\n\tsll\t$3,$3,0x1\n\tmfhi\t%0\n\tsubu\t%1,%1,$3\n\tsra\t$3,$6,31\n\tmult\t$9,$7\n\tsll\t$7,$8,0x4\n\taddu\t$7,$7,%1\n\tsra\t%0,%0,0x2\n\tsubu\t%0,%0,$3\n\tsll\t%1,%0,0x4\n\tsll\t$3,%0,0x2\n\taddu\t$3,$3,%0\n\tsll\t$3,$3,0x1\n\tsubu\t$6,$6,$3\n\taddu\t%1,%1,$6\n\tsb\t%1,0x1(%3)\n\tsra\t%1,$9,31\n\tsb\t$7,0x2(%3)\n\tmfhi\t$3\n\tsra\t$3,$3,0x2\n\tsubu\t$3,$3,%1\n\tsll\t%0,$3,0x4\n\tsll\t%1,$3,0x2\n\taddu\t%1,%1,$3\n\tsll\t%1,%1,0x1\n\tsubu\t$9,$9,%1\n\taddu\t%0,%0,$9"
        : "=r"(minuteBcd), "=r"(n)
        : "1"(n), "r"(out)
        : "v1", "a2", "a3", "t0", "t1");
    out->minute = minuteBcd;
    return out;
}

int CdPosToInt(CdlLOC *p) {
#define DECODE_BCD(x) (((x) >> 4) * 10 + ((x) & 0xF))

    u8 sector = p->sector;
    u8 second = p->second;
    u8 minute = p->minute;

    return (DECODE_BCD(minute) * 60 + DECODE_BCD(second)) * 75 +
           DECODE_BCD(sector) - 150;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", getintr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CD_sync);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CD_ready);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CD_cw);

extern u32 D_8009BD40[];
extern u32 D_8009BD44[];
extern u32 D_8009BD48[];
extern u32 D_8009BD4C[];

int CD_vol(CdlATV *vol) {
    *(u8 *)D_8009BD40[0] = 2;
    *(u8 *)D_8009BD48[0] = vol->val0;
    *(u8 *)D_8009BD4C[0] = vol->val1;
    *(u8 *)D_8009BD40[0] = 3;
    *(u8 *)D_8009BD44[0] = vol->val2;
    *(u8 *)D_8009BD48[0] = vol->val3;
    *(u8 *)D_8009BD4C[0] = 0x20;
    return 0;
}

extern u8 D_8009BD58[];
extern u8 D_8009BD59[];
extern u8 D_8009BD5A[];
extern u32 D_8009BD50[];

#ifdef NON_MATCHING
/* WALL (2026-10-05):
 * 220 bytes versus 224 retail; 72 linked text bytes differ including the size
 * deficit. Retail copies status byte D_8009BD5A to D_8009BD59, not
 * D_8009BD58. The loop matches; status-address materialization and final
 * stores still differ. */
void CD_flush(void) {
    *(u8 *)D_8009BD40[0] = 1;
    while (*(u8 *)D_8009BD4C[0] & 7) {
        *(u8 *)D_8009BD40[0] = 1;
        *(u8 *)D_8009BD4C[0] = 7;
        *(u8 *)D_8009BD48[0] = 7;
    }
    D_8009BD5A[0] = 0;
    asm("");
    D_8009BD59[0] = ((volatile u8 *)D_8009BD59)[1];
    D_8009BD58[0] = 2;
    *(u8 *)D_8009BD40[0] = 0;
    *(u8 *)D_8009BD4C[0] = 0;
    *(u32 *)D_8009BD50[0] = 0x1325;
    asm("");
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", CD_flush);
#endif

INCLUDE_ASM("asm/nonmatchings/psxsdk", CD_initvol);

extern u32 D_8009BA80[];
extern u32 D_8009BA7C[];
extern u32 D_8009BA90[];
extern void callback();

int CD_initintr(void) {
    D_8009BA80[0] = 0;
    D_8009BA7C[0] = 0;
    D_8009BA90[0] = 0;
    ((u32 *)D_8009BA8C)[0] = 0;
    ResetCallback();
    InterruptCallback(2, callback);
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", CD_init);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CD_datasync);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CD_getsector);

extern u32 D_8009BD24[];

void CD_set_test_parmnum(int parmNum) {
    D_8009BD24[0] = parmNum;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", callback);

INCLUDE_ASM("asm/nonmatchings/psxsdk", cb_read);

INCLUDE_ASM("asm/nonmatchings/psxsdk", cd_read_retry);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdRead);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdReadSync);

/* SPDX-License-Identifier: MIT */

extern u32 D_8009BD88[];
extern u32 D_8009BD8C[];

CdlCB CdReadCallback(CdlCB func) {
    CdlCB old;

    old = (CdlCB)D_8009BD88[0];
    ((CdlCB *)D_8009BD8C)[-1] = func;
    return old;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", VSync);

extern s32 D_8009CE84[];
extern char D_80090404[];

#ifdef NON_MATCHING
/* WALL (2026-10-05):
 * 156 bytes, 22 linked text bytes differ. Moving the existing empty barrier
 * inside the condition slightly improves the prologue. Remaining differences
 * concern initial load/store ordering and the ra save delay slot. */
void v_wait(int mode, int time) {
    volatile int count;

    count = time << 15;
    if (D_8009CE84[0] < mode) {
        asm("");
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
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", v_wait);
#endif
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", startIntr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", trapIntr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", setIntr);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", trapIntrVSync);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", trapIntrDMA);

INCLUDE_ASM("asm/nonmatchings/psxsdk", setIntrDMA);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", FntOpen);

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
                    asm volatile("\n\tmultu %0, %1" : : "r"(value), "r"(magic));
                    buf--;
                    count++;
                    asm volatile("\n\tmfhi %0\n\tsrl %0, %0, 3" : "=r"(quot));
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", GetTPage);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", DumpDrawEnv);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DumpDispEnv);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ResetGraph);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetGraphReverse);

#ifdef NON_MATCHING
/* WALL (2026-10-05):
 * 108 bytes, 24 linked text bytes differ after removing the duplicate typedef
 * and retaining rodata. Debug pointer allocation and indirect-printer
 * argument/load ordering still differ. A printer temporary did not improve
 * linked bytes. */
/* SPDX-License-Identifier: MIT */

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
        ((DebugPrintf)D_8009DA8C[0])(D_80090698, debug[0], D_8009DA90[0],
                                     D_8009DA93[0]);
    }
    return old;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SetGraphDebug);
#endif
INCLUDE_RODATA("asm/nonmatchings/psxsdk", D_80090698);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetGraphQueue);
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDispMask);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", ClearOTag);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ClearOTagR);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", PutDrawEnv);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DrawOTagEnv);

/* SPDX-License-Identifier: MIT */

extern u8 D_8009DAA0[];
extern void *memcpy();

DRAWENV *GetDrawEnv(DRAWENV *env) {
    s32 size = 0x5C;

    memcpy(env, D_8009DAA0, size);
    return env;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", PutDispEnv);

/* SPDX-License-Identifier: MIT */

extern u8 D_8009DAFC[];

DISPENV *GetDispEnv(DISPENV *env) {
    s32 size = 0x14;

    memcpy(env, D_8009DAFC, size);
    return env;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", GetODE);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawEnv);

/* SPDX-License-Identifier: MIT */

extern u8 D_8009DA90[];

s32 get_mode(s32 dfe, s32 dtd, s32 tpage) {
    register s32 mode asm("v1");
    register s32 page asm("v0");
    u8 *type;

    type = D_8009DA90;
    asm("" : "=r"(type) : "0"(type));
    if ((u32)(type[0] - 1) < 2U) {
        mode = 0xE1000000;
        if (dtd != 0) {
            mode = 0xE1000800;
        }
        page = tpage & 0x27FF;
        if (dfe != 0) {
            page = page | 0x1000;
        }
    } else {
        mode = 0xE1000000;
        if (dtd != 0) {
            mode = 0xE1000200;
        }
        page = tpage & 0x9FF;
        if (dfe != 0) {
            page = page | 0x400;
        }
    }
    return mode | page;
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
    register s32 offsetX asm("v0");
    register s32 offsetY asm("v1");
    u8 *type;

    type = D_8009DA90;
    asm("" : "=r"(type) : "0"(type));
    offsetY = y & 0xFFF;
    if ((u32)(type[0] - 1) >= 2U) {
        offsetY = y & 0x7FF;
        offsetY = offsetY << 0xB;
        offsetX = x & 0x7FF;
    } else {
        offsetY = offsetY << 0xC;
        offsetX = x & 0xFFF;
    }
    offsetX = offsetX | 0xE5000000;
    return offsetY | offsetX;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", get_tw);

INCLUDE_ASM("asm/nonmatchings/psxsdk", get_dx);

/* SPDX-License-Identifier: MIT */

extern s32 *D_8009DB64[];

s32 _status(void) {
    return *(s32 *)D_8009DB64[0];
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", _otc);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _clr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _dws);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _drs);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _param);

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
extern void _exeque(void);
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
    } while ((*(volatile s32 *)D_8009DB64[0] & spinMask) == 0);
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _exeque);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _reset);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _sync);

/* SPDX-License-Identifier: MIT */

extern s32 D_8009DBA8[];
extern s32 D_8009DBAC[];

void set_alarm(void) {
    D_8009DBA8[0] = VSync(-1) + 0xF0;
    D_8009DBAC[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", get_alarm);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _version);

INCLUDE_ASM("asm/nonmatchings/psxsdk", memset);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", func_8007C548);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", ApplyMatrixLV);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", ScaleMatrixL);

INCLUDE_ASM("asm/nonmatchings/psxsdk", PushMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", PopMatrix);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _patch_gte);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsInitSoundSeq);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsSeqOpen);

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
void SpuVmKeyOn(s16, s16, u8, s32, s32, s32);
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

#ifdef NON_MATCHING
/* WALL (2026-10-05):
 * 692 bytes versus 792 retail; 632 linked text bytes differ including the
 * size deficit. Extra empty controller cases now correctly go to default, not
 * bank select. Channel lifetime, call-argument narrowing, save set, and
 * branch-tail shape remain different. Earlier claims of a matching jump table
 * were not reproduced. */
/* SPDX-License-Identifier: MIT */
void SpuVmSetVol(s16, s16, u8, s16, u8);
s32 SpuVmSetProgVol(s16, u8, u8);
void _SsContDataEntry(s16, s16, u8);
void _SsContPortamento(s16, s16, u8);
void _SsContNrpn1(s16, s16, u8);
void _SsContNrpn2(s16, s16, u8);
void _SsContRpn1(s16, s16, u8);
void _SsContResetAll(s16, s16);

void _SsSetControlChange(s16 access, s16 sequence, u8 event) {
    struct SeqStruct *score;
    u8 value;
    u8 ch;

    score = (struct SeqStruct *)((s32)D_800BDE3C[access] + sequence * 0xAC);
    value = *score->readPos++;
    ch = score->channel;
    switch (event) {
    case 0:
        score->unk4C = value;
        break;
    case 6:
        _SsContDataEntry(access, sequence, value);
        return;
    case 7:
        SpuVmSetVol((sequence << 8) | access, score->unk4C, score->programs[ch],
                    value, score->panpot[ch]);
        score->vol[ch] = value;
        break;
    case 10:
        SpuVmSetVol((sequence << 8) | access, score->unk4C, score->programs[ch],
                    score->vol[ch], value);
        score->panpot[ch] = value;
        break;
    case 11:
        SpuVmSetProgVol(score->unk4C, score->programs[ch], value);
        SpuVmSetVol((sequence << 8) | access, score->unk4C, score->programs[ch],
                    score->vol[ch], score->panpot[ch]);
        break;
    case 64:
        if (value < 0x40) {
            func_80082670();
        } else {
            SpuVmDamperOn();
        }
        break;
    case 65:
        _SsContPortamento(access, sequence, value);
        return;
    case 93:
        SsUtSetReverbDepth(value, value);
        break;
    case 98:
        _SsContNrpn1(access, sequence, value);
        return;
    case 99:
        _SsContNrpn2(access, sequence, value);
        return;
    case 100:
        _SsContRpn1(access, sequence, value);
        return;
    case 121:
        _SsContResetAll(access, sequence);
        return;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 8:
    case 9:
    case 12:
    case 91:
    case 92:
    case 94:
    case 95:
    case 96:
    case 97:
    case 101:
    case 120:
    default:
        break;
    }
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsSetControlChange);
#endif
INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsContModulation);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsContPortaTime);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsContPortamento);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsContResetAll);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsContNrpn1);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsContNrpn2);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsSndSetVabAttr);

/* SPDX-License-Identifier: MIT */
void SpuVmPitchBend(s32, s16, u8, u8);
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsGetMetaEvent);

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
typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
} SsAdsr;

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

#ifdef NON_MATCHING
/* WALL (2026-10-08): score 295 (11 rows, all in the join block after the
 * branch). The head matches exactly: loads 0xC/0x10/0xA in retail order,
 * mode in t1, the word2 copy `move t0,t1` inside the unkA load gap, and
 * `and t2` in the beqz delay slot. The t0 pin on word2 is required: every
 * unpinned spelling lets cse unify mode/word2 (ori t0,t0, no copy). What
 * resists: the join's first or-chain gives the unk0 term v0 and the unk2
 * term a0 (retail is inverted), the `sh 0(a1)` store sits before the unk6/
 * unk8 loads instead of after, and the adsr2 accumulator ties to the pinned
 * t0 (or t0,t0,v0) instead of to the unk6 term (or v0,t0,v0 + or t0,v0,v1).
 * Pins on other locals, value locals (load-sinking refolds them), statement
 * reorders, if/else and ternary shapes, opaque asm copies, and a 10-minute
 * permuter run (265 best) did not close it. */
void _SsUtBuildADSR(SsAdsr *adsr, u16 *adsr1, u16 *adsr2) {
    register s32 word2 asm("t0");
    s32 mode;
    s32 am;

    mode = -(adsr->unkC != 0) & ~0x7FFF;
    am = -(adsr->unkA != 0) & ~0x7FFF;
    word2 = mode;
    if (adsr->unk10 != 0) {
        word2 = mode | 0x4000;
    }
    *adsr1 = am | ((adsr->unk0 << 8) & 0x7F00) | ((adsr->unk2 << 4) & 0xF0) |
             (adsr->unk4 & 0xF);
    *adsr2 = word2 | ((adsr->unk6 << 6) & 0x1FC0) | (adsr->unk8 & 0x1F);
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsUtBuildADSR);
#endif

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsSetTempo);

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
    asm("" : "=r"(shifted) : "0"(shifted));
    rows = D_800BDF0C;
    asm("" : "=r"(rows) : "0"(rows));
    row = (s32 *)((shifted >> 10) + (s32)rows);
    row[arg1] = arg2;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsClose);

extern void _SsClose(short);

void SsSeqClose(short seq_access_num) {
    _SsClose(seq_access_num);
}

extern void _SsClose(short);

void SsSepClose(short sep_access_num) {
    _SsClose(sep_access_num);
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsInit);

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

#ifdef NON_MATCHING
/* WALL (2026-10-05):
 * 616 bytes, 234 linked text bytes differ. Direct rcntTarget assignment
 * restores size but does not recover the shared D_800A20A4 base or retail
 * quotient/branch-tail allocation. A permuter candidate using an
 * uninitialized base pointer was rejected. */

s32 _SsStart(s32 arg0) {
    s32 wait;
    s32 mode;
    s32 rcntSpec;
    s32 rcntTarget;
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
        u8 *env;
        u32 div;
        s32 ticks;

        env = (u8 *)D_800A20A4;
        if (*(s32 *)&env[0] == 0) {
            ticks = *(s32 *)&env[-4];
            if (ticks < 0x46) {
                rcntTarget = 0x204CC0 / ticks;
                asm("");
                env[0xD] += 1;
            } else {
                rcntTarget = 0x409980 / ticks;
            }
            break;
        }
    }
        return;
    }
    if (D_800A20B0[0] != 0) {
        EnterCriticalSection();
        VSyncCallback(D_800A20A8[0]);
    } else {
        EnterCriticalSection();
        ResetRCnt(rcntSpec);
        SetRCnt(rcntSpec, rcntTarget & 0xFFFF, 0x1000);
        if (D_800A20B2[0] == 0) {
            D_800A20AC[0] = InterruptCallback(0, NULL);
            callback = _SsTrapIntrVSync;
        } else if (D_800A20B1[0] == 0) {
            callback = D_800A20A8[0];
        } else {
            callback = _SsSeqCalledTbyT_1per2;
        }
        InterruptCallback(D_800A20B2[0], callback);
    }
    ExitCriticalSection();
    return;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsStart);
#endif

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsTrapIntrVSync);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsSeqCalledTbyT_1per2);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsSeqCalledTbyT);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsSndCrescendo);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsSndDecrescendo);

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

void func_8008134C(s16 arg0, s16 arg1) {
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsEnd);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsSetTableSize);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsSndSetPauseMode);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsSndSetReplayMode);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsSndTempo);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabOpen);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabOpenHead);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabOpenHeadSticky);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabFakeHead);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabOpenHeadWithMode);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabTransBody);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabTransCompleted);

/* SPDX-License-Identifier: MIT */

extern u16 D_800AFD98[];

void func_80082670(void) {
    D_800AFD98[0] = 0;
}

/* SPDX-License-Identifier: MIT */
extern u16 D_800AFD98[];
void SpuVmDamperOn(void) {
    D_800AFD98[0] = 2;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtGetProgAtr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmVSetUp);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtGetVagAtr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtSetReverbType);

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
    s32 magic = 0x81020409;
    register s32 n1 asm("a2") = (ldepth << 15) - ldepth;
    register s32 hi1 asm("v0");
    register s32 n2 asm("a3");
    register s32 d1 asm("v0");
    register s32 hi2 asm("v0");
    s32 d2;
    register SpuReverbAttr *attr asm("a0");

    asm("mult %2, %3\n\tsll $5, $5, 16\n\tsra $5, $5, 16\n\tmfhi %0\n\tsll %1, $5, 15\n\tsubu %1, %1, $5"
        : "=r"(hi1), "=r"(n2)
        : "r"(n1), "r"(magic));
    asm("mult %1, %2" : "=r"(hi2) : "r"(n2), "r"(magic));
    asm volatile(
        "addiu $29, $29, -24\n\tlui %0, %%hi(D_800AE27C)\n\taddiu %0, %0, %%lo(D_800AE27C)\n\tsw $31, 16($29)"
        : "=r"(attr));
    magic = 6;
    d1 = hi1 + n1;
    d1 >>= 6;
    n1 >>= 31;
    d1 -= n1;
    attr->mask = magic;
    D_800AE27C[0].depth.left = d1;
    asm("mfhi %0" : "=r"(hi2) : "0"(hi2));
    d2 = hi2 + n2;
    d2 >>= 6;
    n2 >>= 31;
    d2 -= n2;
    D_800AE27C[0].depth.right = d2;
    asm("jal SpuSetReverbModeParam\n\tlw $31, 16($29)\n\taddiu $29, $29, 24");
}

void SsUtSetReverbDelay(short delay) {
    D_800AE27C[0].mask = SPU_REV_DELAYTIME;
    D_800AE27C[0].delay = delay;
    SpuSetReverbModeParam(D_800AE27C);
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtSetVagAtr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmAlloc);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmKeyOnNow);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmDoAllocate);

INCLUDE_ASM("asm/nonmatchings/psxsdk", vmNoiseOn);

INCLUDE_ASM("asm/nonmatchings/psxsdk", vmNoiseOn2);

INCLUDE_ASM("asm/nonmatchings/psxsdk", note2pitch);

INCLUDE_ASM("asm/nonmatchings/psxsdk", note2pitch2);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SePitchBend);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetAutoVol);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetAutoPan);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmInit);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmNoiseOnWithAdsr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmNoiseOff);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmNoiseOn);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmPBVoice);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmPitchBend);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmFlush);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmKeyOn);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmKeyOff);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmSeKeyOn);

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

#ifdef NON_MATCHING
s32 SpuVmSetSeqVol(s16 seq_access, u16 volL, u16 volR, s16 applyNow) {
    struct SeqStruct *score;
    s32 mvolL;
    s32 mvolR;
    s16 i;

    score = D_800BDE3C[seq_access & 0xFF];
    D_800B9DDA[0] = seq_access;
    score[(u16)seq_access >> 8].leftVolume = volL;
    score[(u16)seq_access >> 8].rightVolume = volR;
    if (score[(u16)seq_access >> 8].leftVolume >= 0x80) {
        score[(u16)seq_access >> 8].leftVolume = 0x7F;
    }
    if (score[(u16)seq_access >> 8].rightVolume >= 0x80) {
        score[(u16)seq_access >> 8].rightVolume = 0x7F;
    }
    mvolL = volL * 129;
    mvolR = volR * 129;
    if (applyNow == 1) {
        for (i = 0; i < D_800B9C80[0]; i++) {
            if (D_800AD3CA[i][0] == (u16)seq_access) {
                *(s16 *)&D_800AD224[i * 16] = mvolL;
                *(s16 *)&D_800AD224[i * 16 + 2] = mvolR;
                D_800AD3A4[i] |= 3;
            }
        }
    }
    return D_800B9DDA[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmSetSeqVol);
#endif

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmSeqKeyOff);

extern s32 SpuVmVSetUp();
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

extern s32 SpuVmVSetUp();
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmSetVol);

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

#ifdef NON_MATCHING
/* WALL (2026-10-08): 39 diff lines, all register swaps cascading from two
 * roots: (1) the raw voll/volr stack loads land in s1/s0 instead of s0/s1, and
 * (2) the (s16) conversion temps pick a0/v1 backwards. volr==voll fixes the
 * temps but swaps the raws; voll==volr the reverse. Also missing: retail's
 * voice copy (move v1,s0) after SpuVmAlloc, the vag sll/sra interleave, and
 * the tail store-cluster order. cc1 -dl greg dump analyzed (span-based
 * ranking); permuter standalone wins do not transfer to the TU context. */
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
    if (volr == voll) {
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
        (u8 *)((D_800B9DCB[0] * 16 + D_800B9DD0[0]) * 32 + (s32)D_800B9950[0]);
    D_800B9DD3[0] = toneAttr[0];
    vag = *(u16 *)(toneAttr + 0x16);
    asm("" : "=r"(vag) : "0"(vag));
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
    voice = (u8)SpuVmAlloc();
    if (voice == D_800B9C80[0]) {
        keyOnGuard[0] = 0;
        return -1;
    }
    D_800B9DDE[0] = voice;
    D_800AD3CA[voice][0] = 0x21;
    *(s16 *)(D_800AD3D2 + voice * 52) = vabId;
    *(s16 *)(D_800AD3CE + voice * 52) = prog;
    *(s16 *)(D_800AD3CC + voice * 52) = D_800B9DC9[2];
    *(s16 *)(D_800AD3BC + voice * 52) = *(u16 *)&D_800B9DDA[1];
    *(s16 *)(D_800AD3C8 + voice * 52) = note;
    *(u8 *)(D_800AD3D7 + voice * 52) = 1;
    *(s16 *)(D_800AD3BE + voice * 52) = 0;
    *(s16 *)(D_800AD3D0 + voice * 52) = D_800B9DCF[1];
    SpuVmDoAllocate();
    if (((s16 *)D_800B9DDE)[-1] == 0xFF) {
        vmNoiseOn(voice);
    } else {
        SpuVmKeyOnNow(1, (u16)note2pitch2((u16)note, fine));
    }
    keyOnGuard[0] = 0;
    return voice;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtKeyOn);
#endif

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

#ifdef NON_MATCHING
/* WALL (2026-10-08): 2 insns: the D_800AD3CE field-2 load lands in a1
 * (the freed vabId param register) instead of sharing v1 with the field-1
 * load temp, and the following bne reads it. All capture variants (mask2,
 * onBits, onBits2, seq, orTemp, fresh local, pinned local) and neighbour
 * address spellings give the same 2 lines; without a capture the entry
 * t-registers rotate by one. gcc never shares v1 between the two load
 * temps here (live ranges overlap in the pre-sched RTL).
 * Recipes that did match: ANSI s16 prototype params; guard load via
 * D_800B2090[0], set/tails via ((s32 *)gOrderingTables)[-1]; store-then-
 * reload of D_800B9DDE needs asm("":::"memory") plus a ((u16 *)D_800B9DDC)[1]
 * read spelling; the four bit-mask stores need four distinct address
 * spellings; or-results go through orTemp locals so the or keeps retail's
 * operand order. */
/* SPDX-License-Identifier: MIT */
/* The onBits assignment inside the compare chain is load-bearing: without it
 * gcc puts the D_800B9DCE field load in mask1's register instead of a temp. */
s32 SsUtKeyOff(s16 vc, s16 vabId, s16 prog, s16 tone, s16 note) {
    u16 v;
    s32 mask2;
    s32 mask1;
    s32 onBits;
    s32 onBits2;
    s32 orTemp;
    s32 orTemp2;
    s32 seq;

    if (D_800B2090[0] == 1) {
        return -1;
    }
    ((s32 *)gOrderingTables)[-1] = 1;
    if ((u16)vc < 0x18) {
        if (*(s16 *)(D_800AD3D2 + vc * 52) == vabId &&
            (mask2 = *(s16 *)(D_800AD3CE + vc * 52)) == prog &&
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
                asm("" : : : "memory");
                v = ((u16 *)D_800B9DDC)[1];
                if (v < 0x10) {
                    mask1 = 1 << v;
                    mask2 = 0;
                } else {
                    mask1 = 0;
                    mask2 = 1 << (v - 0x10);
                }
                D_800AD3D7[v * 52] = 0;
                onBits = D_800BEB98[0];
                onBits2 = D_800BEB9C[0];
                *(s16 *)(D_800AD3C0 + v * 52) = 0;
                *(s16 *)(D_800AD3BC + v * 52) = 0;
                orTemp = mask1 | onBits;
                ((u16 *)D_800BEB9C)[-2] = orTemp;
                ((u16 *)D_800AD970)[-2] = D_800AD96C[0] & ~orTemp;
                orTemp2 = mask2 | onBits2;
                ((u16 *)D_800BEB98)[2] = orTemp2;
                ((u16 *)D_800AD96C)[2] = D_800AD970[0] & ~orTemp2;
            }
            D_800B2090[0] = 0;
            return 0;
        }
    }
    ((s32 *)gOrderingTables)[-1] = 0;
    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtKeyOff);
#endif

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtKeyOnV);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtKeyOffV);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtPitchBend);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtChangePitch);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtChangeADSR);

extern s32 D_800A20B8[];

s32 SsUtGetDetVVol(s32 vab, s16 *vl, s16 *vr) {
    if ((u16)vab < 0x18) {
        *vl = *(s16 *)((s32)D_800A20B8[0] + ((s16)vab) * 16);
        *vr = *(s16 *)((s32)D_800A20B8[0] + ((s16)vab) * 16 + 2);
        return 0;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtSetDetVVol);

extern s32 D_800A20B8[];

#ifdef NON_MATCHING
/* Two bytes of register allocation short: retail's two mfhi both land in
 * $v1, but this gcc fuses mult+mfhi into one smulsi3_highpart insn, so
 * both highpart pseudos conflict with each other and with the vm pointer
 * in $v1; they can only reach $t2/$a2 (SsUtSetReverbDepth class). */
s32 SsUtGetVVol(s32 vc, s16 *voll, s16 *volr) {
    s16 mvol;
    s16 mvol2;
    s32 volL;
    s32 volR;

    if ((u16)vc < 24) {
        mvol = *(s16 *)&((u8 *)D_800A20B8[0])[(s16)vc * 16];
        volL = mvol / 129;
        mvol = *(s16 *)&((u8 *)D_800A20B8[0])[(s16)vc * 16 + 2];
        mvol2 = mvol;
        volR = mvol2 / (mvol = 129);
        *voll = volL;
        *volr = volR;
        return 0;
    }
    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtGetVVol);
#endif

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtAllKeyOff);

void func_80087CC0(void) {
    _SpuInit(0);
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SpuInit);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuStart);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_reset);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_init);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_writeByIO);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_FiDMA);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_r_);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_t);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_write);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuQuit);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuMalloc);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_gcSPU);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuFree);

void _SpuSetAnyVoice(s32, u32, s32, s32);
void SpuSetNoiseVoice(s32 a, s32 b) {
    _SpuSetAnyVoice(a, b, 0xCA, 0xCB);
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SpuSetAnyVoice);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetReverb);

/* SPDX-License-Identifier: MIT */

typedef struct {
    u32 addr;
    u32 size;
} SpuMallocItem;

extern SpuMallocItem *D_800A270C[];

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetReverbModeParam);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_setReverbAttr);

void SpuSetReverbVoice(s32 a, s32 b) {
    _SpuSetAnyVoice(a, b, 0xCC, 0xCD);
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuClearReverbWorkArea);

ASM_FUNC(WaitEvent, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                    "    jr $t2 # maspsx-keep\n"
                    "    addiu $t1, $zero, 0xA # maspsx-keep\n"
                    "    nop # maspsx-keep\n")

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetIRQ);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetKey);

/* SPDX-License-Identifier: MIT */

extern s32 _SpuSetVoiceAttr(SpuVoiceAttr *, s32, s32, s32);

void SpuSetVoiceAttr(SpuVoiceAttr *arg) {
    _SpuSetVoiceAttr(arg, 0, 23, 0);
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SpuSetVoiceAttr);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuIsTransferCompleted);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetTransferCallback);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetCommonAttr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_note2pitch);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_pitch2note);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuRGetAllKeysStatus);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", sprintf);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", strtok);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _card_clear);

extern void MDEC_reset(s32 mode);
extern void MDEC_in(u_long *buf, s32 size);
extern void MDEC_out(u_long *buf, s32 size);
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", MDEC_reset);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MDEC_in);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MDEC_out);

extern void timeout(char *name);
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", timeout);

INCLUDE_ASM("asm/nonmatchings/psxsdk", D_8008CA04);
