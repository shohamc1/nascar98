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

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
extern u32 D_8009BA7C[];
extern u32 D_8009B9FC[];
extern u8 D_8009BA8C[];
extern s32 CD_cw(u8, u8 *, u8 *, s32);
extern s32 CD_sync(s32, u8 *);
int CdControl(u_char com, u_char *param, u_char *result) {
    CdlCB old;
    s32 count;
    s32 status;
    old = (CdlCB)D_8009BA7C[0];
    count = 3;
    status = 0;
again:
    D_8009BA7C[0] = 0;
    if (com != CdlNop && (D_8009BA8C[0] & CdlStatShellOpen)) {
        CD_cw(CdlNop, 0, 0, 0);
    }
    if (param == 0 || D_8009B9FC[(u8)com] == 0 ||
        !CD_cw(CdlSetloc, param, result, 0)) {
        D_8009BA7C[0] = (u32)old;
        if (!CD_cw(com, param, result, 0)) {
            status = 0;
            goto done;
        }
    }
    count--;
    if (count != -1)
        goto again;
    D_8009BA7C[0] = (u32)old;
    status = -1;
done:
    return status + 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", CdControl);
#endif

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
extern u32 D_8009BA7C[];
extern u32 D_8009B9FC[];
extern u8 D_8009BA8C[];
extern s32 CD_cw(u8, u8 *, u8 *, s32);
extern s32 CD_sync(s32, u8 *);
int CdControlF(u_char com, u_char *param) {
    CdlCB old;
    s32 count;
    s32 status;
    old = (CdlCB)D_8009BA7C[0];
    count = 3;
    status = 0;
again:
    D_8009BA7C[0] = 0;
    if (com != CdlNop && (D_8009BA8C[0] & CdlStatShellOpen)) {
        CD_cw(CdlNop, 0, 0, 0);
    }
    if (param == 0 || D_8009B9FC[(u8)com] == 0 ||
        !CD_cw(CdlSetloc, param, 0, 0)) {
        D_8009BA7C[0] = (u32)old;
        if (!CD_cw(com, param, 0, 1)) {
            status = 0;
            goto done;
        }
    }
    count--;
    if (count != -1)
        goto again;
    D_8009BA7C[0] = (u32)old;
    status = -1;
done:
    return status + 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", CdControlF);
#endif

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
extern u32 D_8009BA7C[];
extern u32 D_8009B9FC[];
extern u8 D_8009BA8C[];
extern s32 CD_cw(u8, u8 *, u8 *, s32);
extern s32 CD_sync(s32, u8 *);
int CdControlB(u_char com, u_char *param, u_char *result) {
    CdlCB old;
    s32 count;
    s32 status;
    old = (CdlCB)D_8009BA7C[0];
    count = 3;
    status = 0;
again:
    D_8009BA7C[0] = 0;
    if (com != CdlNop && (D_8009BA8C[0] & CdlStatShellOpen)) {
        CD_cw(CdlNop, 0, 0, 0);
    }
    if (param == 0 || D_8009B9FC[(u8)com] == 0 ||
        !CD_cw(CdlSetloc, param, result, 0)) {
        D_8009BA7C[0] = (u32)old;
        if (!CD_cw(com, param, result, 0)) {
            status = 0;
            goto done;
        }
    }
    count--;
    if (count != -1)
        goto again;
    D_8009BA7C[0] = (u32)old;
    status = -1;
done:
    if (status != 0)
        return 0;
    return CD_sync(CdlSync, result) == CdlComplete;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", CdControlB);
#endif

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

extern u32 D_8009BD40[];
extern u32 D_8009BD44[];
extern u32 D_8009BD48[];
extern u32 D_8009BD4C[];
extern u32 D_8009BD50[];
extern u8 D_8009BD58[];
extern u8 D_8009BD59[];
extern u8 D_8009BD5A[];

void CD_flush(void) {
    register volatile u8 *statusPtr asm("$2");
    register u8 statusValue asm("$3");
    *(u8 *)D_8009BD40[0] = 1;
    while (*(u8 *)D_8009BD4C[0] & 7) {
        *(u8 *)D_8009BD40[0] = 1;
        *(u8 *)D_8009BD4C[0] = 7;
        *(u8 *)D_8009BD48[0] = 7;
    }
    asm volatile(
        "lui $1, %%hi(D_8009BD5A)\n\tsb $0, %%lo(D_8009BD5A)($1)\n\tlui %0, %%hi(D_8009BD5A)\n\tlbu %0, %%lo(D_8009BD5A)(%0)"
        : "=r"(statusValue)
        :
        : "$1", "memory");
    asm volatile("" : : "r"(statusValue) : "memory");
    statusPtr = (volatile u8 *)D_8009BD59;
    *statusPtr = statusValue;
    D_8009BD58[0] = 2;
    *(u8 *)D_8009BD40[0] = 0;
    *(u8 *)D_8009BD4C[0] = 0;
    *(u32 *)D_8009BD50[0] = 0x1325;
    asm("");
}

extern u32 D_8009BD54[];
int CD_initvol(void) {
    CdlATV vol;
    u8 *spu;
    spu = (u8 *)D_8009BD54[0];
    if (*(u16 *)(spu + 0x1B8) == 0 && *(u16 *)(spu + 0x1BA) == 0) {
        *(u16 *)(spu + 0x180) = 0x3FFF;
        *(u16 *)(spu + 0x182) = 0x3FFF;
    }
    spu = (u8 *)D_8009BD54[0];
    *(u16 *)(spu + 0x1B0) = 0x3FFF;
    *(u16 *)(spu + 0x1B2) = 0x3FFF;
    *(u16 *)(spu + 0x1AA) = 0xC001;
    vol.val0 = vol.val2 = 0x80;
    vol.val1 = vol.val3 = 0;
    *(u8 *)D_8009BD40[0] = 2;
    *(u8 *)D_8009BD48[0] = vol.val0;
    *(u8 *)D_8009BD4C[0] = vol.val1;
    *(u8 *)D_8009BD40[0] = 3;
    *(u8 *)D_8009BD44[0] = vol.val2;
    *(u8 *)D_8009BD48[0] = vol.val3;
    *(u8 *)D_8009BD4C[0] = 0x20;
    return 0;
}

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

extern u32 D_8009BD74[];
extern u32 D_8009BD78[];
extern u32 D_8009BD7C[];
extern u32 D_8009BD80[];
extern u32 D_8009BD84[];
int CD_getsector(void *buffer, int size) {
    *(u8 *)D_8009BD40[0] = 0;
    *(u8 *)D_8009BD4C[0] = 0x80;
    *(u32 *)D_8009BD74[0] = 0x20943;
    *(u32 *)D_8009BD50[0] = 0x1323;
    *(u32 *)D_8009BD78[0] |= 0x8000;
    *(u32 *)D_8009BD7C[0] = (u32)buffer;
    *(u32 *)D_8009BD80[0] = size | 0x10000;
    while ((*(volatile u8 *)D_8009BD40[0] & 0x40) == 0) {
    }
    *(u32 *)D_8009BD84[0] = 0x11000000;
    while (*(volatile u32 *)D_8009BD84[0] & 0x01000000) {
    }
    *(u32 *)D_8009BD50[0] = 0x1325;
    return 0;
}

extern u32 D_8009BD24[];

void CD_set_test_parmnum(int parmNum) {
    D_8009BD24[0] = parmNum;
}

extern u32 D_8009BD40[];
extern u8 D_8009BD58[];
extern u8 D_8009BD59[];
extern u8 D_800A8CB8[];
extern u8 D_800A8CC0[];
extern int getintr(void);
void callback(void) {
    int interrupt;
    u8 temp;
    u8 *readyPtr;
    temp = *(u8 *)D_8009BD40[0] & 3;
    readyPtr = D_8009BD59;
    for (;;) {
        interrupt = getintr();
        if (interrupt == 0) {
            break;
        }
        if ((interrupt & 4) && D_8009BA80[0] != 0) {
            ((CdlCB)D_8009BA80[0])(readyPtr[0], D_800A8CC0);
        }
        if ((interrupt & 2) && D_8009BA7C[0] != 0) {
            register u8 *syncPtr asm("$2");
            asm volatile("" : "=r"(syncPtr) : "0"(D_8009BD58));
            ((CdlCB)D_8009BA7C[0])(syncPtr[0], D_800A8CB8);
        }
    }
    *(u8 *)D_8009BD40[0] = temp;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", cb_read);

INCLUDE_ASM("asm/nonmatchings/psxsdk", cd_read_retry);

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
extern volatile u32 D_8009BD98[];
extern volatile u32 D_8009BD9C[];
extern u32 D_8009BD90[];
extern u32 D_8009BD8C[];
extern u32 D_8009BDB0[];
extern u32 D_8009BDB4[];
extern s32 D_8009BDA8[];
extern s32 VSync(s32);
extern char CdStatus(void);
extern s32 cd_read_retry(s32);
int CdRead(int sectors, u_long *buffer, int mode) {
    D_8009BD98[0] = mode;
    switch (D_8009BD98[0] & 0x30) {
    case 0:
        D_8009BD9C[0] = 0x200;
        break;
    case 0x20:
        D_8009BD9C[0] = 0x249;
        break;
    default:
        D_8009BD9C[0] = 0x246;
        break;
    }
    D_8009BD98[0] |= 0x20;
    D_8009BD90[0] = (u32)buffer;
    D_8009BD8C[0] = sectors;
    D_8009BDB0[0] = (u32)CdSyncCallback(0);
    D_8009BDB4[0] = (u32)CdReadyCallback(0);
    D_8009BDA8[0] = VSync(-1);
    if (CdStatus() & (CdlStatPlay | CdlStatSeek | CdlStatRead))
        CdControlB(CdlPause, 0, 0);
    return cd_read_retry(0) > 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", CdRead);
#endif

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", DumpDrawEnv);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", ResetGraph);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetGraphReverse);

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
#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
extern u32 D_8009DA8C[];
extern u8 D_8009DA92[];
extern u8 D_8009DB4C[];
extern char D_80090770[];
OT_TYPE *ClearOTag(OT_TYPE *arg0, int arg1) {
    s32 *var_s0;
    OT_TYPE *temp_a0;
    var_s0 = (s32 *)arg0;
    if ((u8)D_8009DA92[0] >= 2U) {
        ((int (*)(const char *, ...))D_8009DA8C[0])(D_80090770, var_s0, arg1);
    }
    arg1 -= 1;
    if (arg1 != 0) {
        do {
            arg1 -= 1;
            temp_a0 = (OT_TYPE *)var_s0 + 1;
            ((u8 *)var_s0)[3] = 0;
            var_s0[0] = ((u32)temp_a0 & 0xFFFFFF) | (var_s0[0] & 0xFF000000);
            var_s0 = (s32 *)temp_a0;
        } while (arg1 != 0);
    }
    *var_s0 = (s32)((u32)D_8009DB4C & 0xFFFFFF);
    return (OT_TYPE *)var_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", ClearOTag);
#endif

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
void SpuVmKeyOn(s16, s16, s16, s32, s32, s32);
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
typedef struct {
    u8 tones;
    u8 bytes[15];
} ProgramAttrBuffer;
typedef struct {
    u8 bytes[32];
} ToneAttrBuffer;
s16 SsUtGetProgAtr(s16, s16, u8 *);
void SsUtGetVagAtr(s16, s16, s16, u8 *);
void SsUtSetVagAtr(s16, s16, s16, u8 *);
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsContPortamento);

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
    func_80082670();
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
void SsUtGetVagAtr(s16, s16, s16, u8 *);
void SsUtSetVagAtr(s16, s16, s16, u8 *);
void SsUtSetReverbType(short);
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
    rows = D_800BDF0C;
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsSetTableSize);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabOpenHeadWithMode);

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

void func_80082670(void) {
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtSetVagAtr);

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
u8 SpuVmAllocDraft(s32) asm("SpuVmAlloc");
u8 SpuVmAllocDraft(s32 arg0) {
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
        s16 auto_vol;
        s16 unk1e;
        s16 unk20;
        s16 unk22;
        s16 start_vol;
        s16 end_vol;
        s16 auto_pan;
        s16 unk2a;
        s16 unk2c;
        s16 unk2e;
        s16 start_pan;
        s16 end_pan;
    };
    extern u8 D_800AD3BC[];
    extern u8 D_800B9C80[];
    extern u8 D_800B9DD3[];
    struct SpuVoice *voices;
    u8 var_t2;
    u16 var_t0;
    u16 var_t3;
    u8 cur_voice;
    u8 channel;
    u8 var_t1;
    u16 prior;

    voices = (struct SpuVoice *)D_800AD3BC;

    channel = 99;
    var_t3 = -1;
    var_t2 = 0;
    var_t0 = 0;
    prior = D_800B9DD3[0];
    var_t1 = 99;
    for (cur_voice = 0; cur_voice < D_800B9C80[0]; cur_voice++) {
        if (voices[cur_voice].unk1b == 0 && voices[cur_voice].unk6 == 0) {
            channel = cur_voice;
            break;
        }
        if (voices[cur_voice].unk18 < prior) {
            prior = voices[cur_voice].unk18;
            var_t1 = cur_voice;
            var_t3 = voices[cur_voice].unk6;
            var_t0 = voices[cur_voice].unk2;
            var_t2 = 1;
        } else if (voices[cur_voice].unk18 == prior) {
            var_t2 += 1;
            if (voices[cur_voice].unk6 < var_t3) {
                var_t0 = voices[cur_voice].unk2;
                var_t3 = voices[cur_voice].unk6;
                var_t1 = cur_voice;
            } else if (voices[cur_voice].unk6 == var_t3) {
                if (var_t0 < voices[cur_voice].unk2) {
                    var_t0 = voices[cur_voice].unk2;
                    var_t1 = cur_voice;
                }
            }
        }
    }
    if (channel == 99) {
        if (var_t2 == 0) {
            channel = D_800B9C80[0];
        } else {
            channel = var_t1;
        }
    }
    if (channel < D_800B9C80[0]) {
        for (cur_voice = 0; cur_voice < D_800B9C80[0]; cur_voice++) {
            voices[cur_voice].unk2++;
        }
        voices[channel].unk2 = 0;
        voices[channel].unk18 = D_800B9DD3[0];
        if (voices[channel].unk1b == 2) {
            SpuSetNoiseVoice(0, 0xFFFFFF);
        }
    }
    return channel;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmAlloc);
#endif

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

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
void SpuVmDoAllocate(void) {
    extern s16 D_800B9DDE[];
    extern u8 D_800B9DCB[];
    extern u8 D_800B9DD0[];
    extern u16 D_800B9DDC[];
    extern s32 D_800B9928[];
    extern s32 D_800B9950[];
    extern s32 D_800AD8A0[];
    extern u8 D_800AD3A4[];
    extern s16 D_800AD3C2[];
    extern u16 D_800AD228[];
    extern u16 D_800AFD98[];
    s32 i;
    s32 toneIndex;
    s32 progIndex;
    s32 offset;

    offset = D_800B9DDE[0] * 8;
    toneIndex = D_800B9DD0[0] + D_800B9DCB[0] * 16;
    D_800B9DDE[1] = offset;
    D_800B9DDE[2] = toneIndex;
    D_800AD3C2[D_800B9DDE[0] * 26] = 0x7FFF;
    for (i = 0; i < 0x10; i++) {
        D_800AD8A0[i] &= ~(1 << D_800B9DDE[0]);
    }
    if ((D_800B9DDC[0] & 1) > 0) {
        progIndex = (D_800B9DDC[0] - 1) / 2;
        D_800AD228[offset + 3] =
            *(u16 *)((s32)D_800B9928[0] + progIndex * 16 + 0xC);
        D_800AD3A4[D_800B9DDE[0]] |= 8;
    } else {
        progIndex = (D_800B9DDC[0] - 1) / 2;
        D_800AD228[offset + 3] =
            *(u16 *)((s32)D_800B9928[0] + progIndex * 16 + 0xE);
        D_800AD3A4[D_800B9DDE[0]] |= 8;
    }
    D_800AD228[offset + 4] =
        *(u16 *)((s32)D_800B9950[0] + toneIndex * 32 + 0x10);
    D_800AD228[offset + 5] =
        *(u16 *)((s32)D_800B9950[0] + toneIndex * 32 + 0x12) + D_800AFD98[0];
    D_800AD3A4[D_800B9DDE[0]] |= 0x30;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmDoAllocate);
#endif

INCLUDE_ASM("asm/nonmatchings/psxsdk", vmNoiseOn);

INCLUDE_ASM("asm/nonmatchings/psxsdk", vmNoiseOn2);

#if 1
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
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", note2pitch);
#endif

#if 1
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
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", note2pitch2);
#endif

#if 1
/* Complete C draft; code generation still differs from retail. */
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
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SePitchBend);
#endif

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

#if 1
/* Complete C draft; code generation still differs from retail. */
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
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmPBVoice);
#endif

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmPitchBend);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmFlush);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmKeyOn);

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
s32 SpuVmKeyOffDraft(s16, s16, s16, u16) asm("SpuVmKeyOff");
s32 SpuVmKeyOffDraft(s16 arg0, s16 vabId, s16 prog, u16 note) {
    extern u8 D_800B9C80[];
    extern u16 D_800B9DDE[];
    extern s32 D_800A20B8[];
    extern u16 D_800BEB98[];
    extern u16 D_800BEB9C[];
    extern u16 D_800AD96C[];
    extern u16 D_800AD970[];
    extern u8 D_800AD3BC[];
    extern u8 D_800AD3C0[];
    extern u8 D_800AD3C8[];
    extern u8 D_800AD3CA[];
    extern u8 D_800AD3CE[];
    extern u8 D_800AD3D2[];
    extern u8 D_800AD3D7[];
    u16 bitsUpper;
    u16 bitsLower;
    u8 voice;
    s32 count;
    u16 tempVoice;

    count = 0;
    for (voice = 0; voice < D_800B9C80[0]; voice++) {
        if (*(s16 *)(D_800AD3C8 + voice * 52) == note &&
            *(s16 *)(D_800AD3CE + voice * 52) == prog &&
            *(s16 *)(D_800AD3CA + voice * 52) == arg0 &&
            *(s16 *)(D_800AD3D2 + voice * 52) == vabId) {
            if (*(s16 *)(D_800AD3BC + voice * 52) == 0xFF) {
                D_800AD3D7[voice * 52] = 0;
                *(s16 *)(D_800AD3C0 + voice * 52) = 0;
                ((u16 *)D_800A20B8[0])[202] = 0;
                ((u16 *)D_800A20B8[0])[203] = 0;
            } else {
                D_800B9DDE[0] = voice;
                tempVoice = D_800B9DDE[0];
                if (tempVoice < 0x10) {
                    bitsLower = 1 << tempVoice;
                    bitsUpper = 0;
                } else {
                    bitsLower = 0;
                    bitsUpper = 1 << (tempVoice - 0x10);
                }
                D_800AD3D7[tempVoice * 52] = 0;
                *(s16 *)(D_800AD3C0 + tempVoice * 52) = 0;
                *(s16 *)(D_800AD3BC + tempVoice * 52) = 0;
                D_800BEB98[0] |= bitsLower;
                D_800BEB9C[0] |= bitsUpper;
                D_800AD96C[0] &= ~D_800BEB98[0];
                D_800AD970[0] &= ~D_800BEB9C[0];
            }
            count++;
        }
    }
    return count;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmKeyOff);
#endif

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

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
void SpuVmSeqKeyOff(arg0) s32 arg0;
{
    extern u8 D_800B9C80[];
    extern u16 D_800B9DDE[];
    extern s16 D_800AD3CASeq[][26] asm("D_800AD3CA");
    extern u8 D_800AD3D7[];
    extern u8 D_800AD3BC[];
    extern u8 D_800AD3C0[];
    extern u16 D_800BEB98[];
    extern u16 D_800BEB9C[];
    extern u16 D_800AD96C[];
    extern u16 D_800AD970[];
    u8 voice;
    u16 bitsUpper;
    u16 bitsLower;
    u16 temp2;

    if (D_800B9C80[0] == 0) {
        return;
    }
    for (voice = 0; voice < D_800B9C80[0]; voice++) {
        if (D_800AD3CASeq[voice][0] == (s16)arg0) {
            D_800B9DDE[0] = voice;
            temp2 = D_800B9DDE[0];
            if (temp2 < 0x10) {
                bitsLower = 1 << temp2;
                bitsUpper = 0;
            } else {
                bitsLower = 0;
                bitsUpper = 1 << (temp2 - 0x10);
            }
            D_800AD3D7[temp2 * 52] = 0;
            *(s16 *)(D_800AD3C0 + temp2 * 52) = 0;
            *(s16 *)(D_800AD3BC + temp2 * 52) = 0;
            D_800BEB98[0] |= bitsLower;
            D_800AD96C[0] &= ~D_800BEB98[0];
            D_800BEB9C[0] |= bitsUpper;
            D_800AD970[0] &= ~D_800BEB9C[0];
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmSeqKeyOff);
#endif

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

#if 1
/* Matches (0 words) under GNU C 2.6.3-psx only; the 2.7.2 build still
 * differs. Retail's codegen needs these spellings:
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

extern s16 D_800B9DDA[];
extern s32 SpuVmVSetUp(s16, s16);
extern s32 SpuVmPBVoice(s16, s16, s16, s16, u16);
s16 SsUtPitchBend(s16 voice, s16 vabId, s16 prog, s16 note, s16 pbend) {
    SpuVmVSetUp(vabId, prog);
    D_800B9DDA[0] = 0x21;
    return -((SpuVmPBVoice(voice, 0x21, vabId, prog, pbend) << 16) == 0);
}

#if 1
/* Complete C draft; code generation still differs from retail. */
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
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtChangePitch);
#endif

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

#if 1
/* Two bytes of register allocation short: retail's two mfhi both land in
 * $v1, but this gcc fuses mult+mfhi into one smulsi3_highpart insn, so
 * both highpart pseudos conflict with each other and with the vm pointer
 * in $v1; they can only reach $t2/$a2 (SsUtSetReverbDepth class). */
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

extern void _SpuInit(s32 mode);

void func_80087CC0(void) {
    _SpuInit(0);
}

extern void _spu_init(s32);
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
#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
s32 SpuInitHardwareDraft(s32) asm("_spu_init");
typedef struct SpuInitRegs {
    volatile u16 voice[24][8];
    volatile u16 main_vol[2];
    volatile u16 rev_vol[2];
    volatile u16 key_on[2];
    volatile u16 key_off[2];
    volatile u16 chan_fm[2];
    volatile u16 noise_mode[2];
    volatile u16 rev_mode[2];
    volatile u16 reserved[5];
    volatile u16 trans_addr;
    volatile u16 trans_data;
    volatile u16 spucnt;
    volatile u16 data_trans;
    volatile u16 spustat;
    volatile u16 cd_vol[2];
    volatile u16 ex_vol[2];
} SpuInitRegs;
extern volatile SpuInitRegs *D_800A26ACInitRegs[];
extern s32 *D_800A26BCInitPtr[];
extern s32 D_800A26A4Init[];
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
extern s32 _spu_tsa;
extern s32 _spu_inTransfer;
extern s32 _spu_transferCallback;
extern s32 _spu_IRQCallback;

extern s32 printf(const char *, ...);
s32 SpuInitHardwareDraft(s32 arg0) {
    volatile s32 sp0;
    volatile s32 sp4;
    s32 channel;
    *D_800A26BCInitPtr[0] |= 0xB0000;
    D_800A26ACInitRegs[0]->main_vol[0] = 0;
    D_800A26ACInitRegs[0]->main_vol[1] = 0;
    D_800A26ACInitRegs[0]->spucnt = 0;
    D_800A26C4Init[0] = 0;
    D_800A26C8Init[0] = 0;
    D_800A26A8Init[0] = 0;
    sp4 = 0xD;
    for (sp0 = 0; sp0 < 0xF0; sp0++) {
        sp4 *= 3;
    }
    D_800A26ACInitRegs[0]->main_vol[0] = 0;
    D_800A26ACInitRegs[0]->main_vol[1] = 0;
    D_800A26A4Init[0] = 0;
    while (D_800A26ACInitRegs[0]->spustat & 0x7FF) {
        D_800A26A4Init[0]++;
        if (D_800A26A4Init[0] > 5000) {
            printf(D_80090B38Init, D_80090B48Init);
            break;
        }
    }
    D_800A26CCInit[0] = 2;
    D_800A26D0Init[0] = 3;
    D_800A26D4Init[0] = 8;
    D_800A26D8Init[0] = 7;
    D_800A26ACInitRegs[0]->data_trans = 4;
    D_800A26ACInitRegs[0]->rev_vol[0] = 0;
    D_800A26ACInitRegs[0]->rev_vol[1] = 0;
    D_800A26ACInitRegs[0]->key_off[0] = 0xFFFF;
    D_800A26ACInitRegs[0]->key_off[1] = 0xFFFF;
    D_800A26ACInitRegs[0]->rev_mode[0] = 0;
    D_800A26ACInitRegs[0]->rev_mode[1] = 0;
    if (arg0 == 0) {
        D_800A26ACInitRegs[0]->chan_fm[0] = 0;
        D_800A26ACInitRegs[0]->chan_fm[1] = 0;
        D_800A26ACInitRegs[0]->noise_mode[0] = 0;
        D_800A26ACInitRegs[0]->noise_mode[1] = 0;
        D_800A26ACInitRegs[0]->cd_vol[0] = 0;
        D_800A26ACInitRegs[0]->cd_vol[1] = 0;
        D_800A26ACInitRegs[0]->ex_vol[0] = 0;
        D_800A26ACInitRegs[0]->ex_vol[1] = 0;
        D_800A26A8Init[0] = 0x200;
        _spu_writeByIO((u8 *)D_800A26E8Init, 0x10);
        for (channel = 0; channel < 24; channel++) {
            D_800A26ACInitRegs[0]->voice[channel][0] = 0;
            D_800A26ACInitRegs[0]->voice[channel][1] = 0;
            D_800A26ACInitRegs[0]->voice[channel][2] = 0x3FFF;
            D_800A26ACInitRegs[0]->voice[channel][3] = 0x200;
            D_800A26ACInitRegs[0]->voice[channel][4] = 0;
            D_800A26ACInitRegs[0]->voice[channel][5] = 0;
        }
        D_800A26ACInitRegs[0]->key_on[0] |= 0xFFFF;
        D_800A26ACInitRegs[0]->key_on[1] |= 0xFF;
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
        sp4 = 0xD;
        for (sp0 = 0; sp0 < 0xF0; sp0++) {
            sp4 *= 3;
        }
        D_800A26ACInitRegs[0]->key_off[0] |= 0xFFFF;
        D_800A26ACInitRegs[0]->key_off[1] |= 0xFF;
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
        sp4 = 0xD;
        for (sp0 = 0; sp0 < 0xF0; sp0++) {
            sp4 *= 3;
        }
    }
    _spu_inTransfer = 1;
    D_800A26ACInitRegs[0]->spucnt = 0xC000;
    _spu_transferCallback = 0;
    _spu_IRQCallback = 0;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_init);
#endif

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_writeByIO);

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

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
typedef struct SpuTRegs2 {
    u8 pad[0x1A6];
    volatile u16 trans_addr;
    u8 pad2[2];
    volatile u16 spucnt;
} SpuTRegs2;
typedef union SpuTRegsUnion2 {
    SpuTRegs2 rxx;
} SpuTRegsUnion2;
extern volatile SpuTRegsUnion2 *SpuRXXT[];
extern u16 SpuTsaT[];
extern s32 SpuMemModePlusT[];
extern s32 SpuTransferDirT[];
extern volatile s32 *SpuTransferAddrT[];
extern volatile s32 *SpuTransferSizeT[];
extern volatile s32 *SpuTransferCtrlT[];
extern volatile s32 *SpuDelayCtrlT[];
extern s32 SpuTransferCountT[];
extern s32 SpuTransferBlocksT[];
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
        SpuTsaT[0] = count >> SpuMemModePlusT[0];
        SpuRXXT[0]->rxx.trans_addr = SpuTsaT[0];
        break;
    case 1:
        SpuTransferDirT[0] = 0;
        i = 0;
        while (SpuRXXT[0]->rxx.trans_addr != SpuTsaT[0]) {
            if (++i > 0xF00)
                return -2;
        }
        cnt = SpuRXXT[0]->rxx.spucnt;
        cnt &= ~0x30;
        cnt |= 0x20;
        SpuRXXT[0]->rxx.spucnt = cnt;
        break;
    case 0:
        SpuTransferDirT[0] = 1;
        i = 0;
        while (SpuRXXT[0]->rxx.trans_addr != SpuTsaT[0]) {
            if (++i > 0xF00)
                return -2;
        }
        cnt = SpuRXXT[0]->rxx.spucnt;
        cnt &= ~0x30;
        cnt |= 0x30;
        SpuRXXT[0]->rxx.spucnt = cnt;
        break;
    case 3:
        if (SpuTransferDirT[0] == 1)
            ck2 = 0x30;
        else
            ck2 = 0x20;
        i = 0;
        while ((SpuRXXT[0]->rxx.spucnt & 0x30) != ck2) {
            if (++i > 0xF00)
                return -2;
        }
        if (SpuTransferDirT[0] == 1)
            var_a2 = 0x22000000;
        else
            var_a2 = 0x20000000;
        *SpuDelayCtrlT[0] = (*SpuDelayCtrlT[0] & 0xF0FFFFFF) | var_a2;
        count = va_arg(args, u32);
        SpuTransferCountT[0] = count;
        count = va_arg(args, u32);
        SpuTransferBlocksT[0] = count / 64;
        SpuTransferBlocksT[0] += ((count % 64) ? 1 : 0);
        *SpuTransferAddrT[0] = SpuTransferCountT[0];
        *SpuTransferSizeT[0] = (SpuTransferBlocksT[0] << 16) | 0x10;
        if (SpuTransferDirT[0] == 1)
            var_a2 = 0x01000200;
        else
            var_a2 = 0x01000201;
        *SpuTransferCtrlT[0] = var_a2;
        break;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_t);
#endif

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

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
extern SpuStartedStorage D_800A26A0Read;
extern SpuIRQCallbackProc D_800A26E0[];
extern SpuIRQCallbackProc D_800A26E4[];
extern s32 D_800A2298[];
void SpuQuit(void) {
    if (D_800A26A0Read.started == 1) {
        D_800A26A0Read.started = 0;
        EnterCriticalSection();
        D_800A26E0[0] = 0;
        D_800A26E4[0] = 0;
        _SpuDataCallback(0);
        CloseEvent(D_800A2298[0]);
        DisableEvent(D_800A2298[0]);
        ExitCriticalSection();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuQuit);
#endif

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

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
typedef struct {
    u32 addr;
    u32 size;
} SpuMallocCandidateItem;
extern s32 D_800A224CMalloc[];
extern s32 D_800A2250Malloc[];
extern s32 D_800A26D0Malloc[];
extern s32 D_800A26D8Malloc[];
extern s32 D_800A2704Malloc[];
extern s32 D_800A2708Malloc[];
extern void *D_800A270CMalloc[];
extern void _spu_gcSPU(void);
s32 SpuMalloc(s32 arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;
    s32 var_v0;
    u32 temp_s1;
    u32 temp_t0;
    void *temp_a2;
    void *temp_v0;
    void *temp_v1_3;
    void *temp_v1_4;
    void *var_a0_2;

    var_s0 = 0;
    var_s2 = -1;
    if (D_800A224CMalloc[0] == 0) {
        var_s3 = 0;
    } else {
        var_s3 = (0x10000 - D_800A2250Malloc[0]) << D_800A26D0Malloc[0];
    }
    var_a0 = arg0;
    if (arg0 & ~D_800A26D8Malloc[0]) {
        var_a0 = arg0 + D_800A26D8Malloc[0];
    }
    temp_s1 = (var_a0 >> D_800A26D0Malloc[0]) << D_800A26D0Malloc[0];
    if (*(s32 *)D_800A270CMalloc[0] & 0x40000000) {
        var_s2 = 0;
    } else {
        _spu_gcSPU();
        if (D_800A2704Malloc[0] > 0) {
            var_a0_2 = (0 * 8) + D_800A270CMalloc[0];
        loop_9:
            temp_v1 = *(s32 *)((u8 *)var_a0_2 + 0x0);
            if ((temp_v1 & 0x40000000) ||
                ((temp_v1 & 0x80000000) &&
                 ((u32) * (s32 *)((u8 *)var_a0_2 + 0x4) >= temp_s1))) {
                var_s2 = var_s0;
            } else {
                var_s0 += 1;
                var_a0_2 += 8;
                if (var_s0 < D_800A2704Malloc[0]) {
                    goto loop_9;
                }
            }
        }
    }
    var_v0 = -1;
    temp_s0 = var_s2 * 8;
    if (var_s2 != -1) {
        temp_a2 = temp_s0 + D_800A270CMalloc[0];
        temp_v1_2 = *(s32 *)((u8 *)temp_a2 + 0x0);
        if (temp_v1_2 & 0x40000000) {
            var_v0 = -1;
            if (var_s2 < D_800A2704Malloc[0]) {
                var_v0 = -1;
                if ((u32)(*(s32 *)((u8 *)temp_a2 + 0x4) - var_s3) >= temp_s1) {
                    temp_a0 = var_s2 + 1;
                    temp_v1_3 = (temp_a0 * 8) + D_800A270CMalloc[0];
                    *(s32 *)((u8 *)temp_v1_3 + 0x0) =
                        (s32)(((*(s32 *)((u8 *)temp_a2 + 0x0) & 0x0FFFFFFF) +
                               temp_s1) |
                              0x40000000);
                    *(s32 *)((u8 *)temp_v1_3 + 0x4) =
                        (s32)(*(s32 *)((u8 *)temp_a2 + 0x4) - temp_s1);
                    D_800A2708Malloc[0] = temp_a0;
                    *(s32 *)((u8 *)temp_a2 + 0x4) = temp_s1;
                    *(s32 *)((u8 *)temp_a2 + 0x0) =
                        (s32)(*(s32 *)((u8 *)temp_a2 + 0x0) & 0x0FFFFFFF);
                    _spu_gcSPU();
                    return *(s32 *)((u8 *)D_800A270CMalloc[0] + temp_s0);
                }
            }
            /* Duplicate return node #23. Try simplifying control flow for better match */
            return var_v0;
        }
        temp_t0 = *(s32 *)((u8 *)temp_a2 + 0x4);
        temp_s0_2 = var_s2 * 8;
        if ((temp_s1 < temp_t0) &&
            (D_800A2708Malloc[0] < D_800A2704Malloc[0])) {
            temp_v0 = (D_800A2708Malloc[0] * 8) + D_800A270CMalloc[0];
            temp_a1 = *(s32 *)((u8 *)temp_v0 + 0x0);
            temp_a0_2 = *(s32 *)((u8 *)temp_v0 + 0x4);
            *(s32 *)((u8 *)temp_v0 + 0x0) =
                (s32)((temp_s1 + temp_v1_2) | 0x80000000);
            *(s32 *)((u8 *)temp_v0 + 0x4) = (s32)(temp_t0 - temp_s1);
            D_800A2708Malloc[0] += 1;
            *(s32 *)((u8 *)temp_v0 + 0x8) = temp_a1;
            *(s32 *)((u8 *)temp_v0 + 0xC) = temp_a0_2;
        }
        temp_v1_4 = temp_s0_2 + D_800A270CMalloc[0];
        *(s32 *)((u8 *)temp_v1_4 + 0x4) = temp_s1;
        *(s32 *)((u8 *)temp_v1_4 + 0x0) =
            (s32)(*(s32 *)((u8 *)temp_v1_4 + 0x0) & 0x0FFFFFFF);
        _spu_gcSPU();
        var_v0 = *(s32 *)((u8 *)D_800A270CMalloc[0] + temp_s0_2);
        /* Duplicate return node #23. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuMalloc);
#endif

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
extern s32 D_800A2708GC[];
extern void *D_800A270CGC[];
void _spu_gcSPU(void) {
    s32 *var_v1;
    s32 temp_a1_2;
    s32 temp_a3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_t1;
    s32 var_t1_2;
    s32 var_t1_3;
    s32 var_t1_4;
    s32 var_t1_5;
    void *temp_a1;
    void *temp_v0;
    void *var_a0;
    void *var_a0_2;
    void *var_a0_3;
    void *var_a3;
    void *var_t2;
    void *var_v1_2;

    var_t1 = 0;
    if (D_800A2708GC[0] >= 0) {
        var_a3 = D_800A270CGC[0];
        do {
            var_a2 = var_t1 + 1;
            if (*(s32 *)((u8 *)var_a3 + 0x0) & 0x80000000) {
                var_v1 = (s32 *)((u8 *)D_800A270CGC[0] + (var_a2 * 8));
            loop_4:
                if (*var_v1 == 0x2FFFFFFF) {
                    var_a2 += 1;
                    var_v1 = (s32 *)((u8 *)var_v1 + 8);
                    goto loop_4;
                }
                temp_a1 = (var_a2 * 8) + D_800A270CGC[0];
                temp_v1 = *(s32 *)((u8 *)temp_a1 + 0x0);
                if ((temp_v1 & 0x80000000) &&
                    ((temp_v1 & 0x0FFFFFFF) ==
                     ((*(s32 *)((u8 *)var_a3 + 0x0) & 0x0FFFFFFF) +
                      *(s32 *)((u8 *)var_a3 + 0x4)))) {
                    *(s32 *)((u8 *)temp_a1 + 0x0) = 0x2FFFFFFF;
                    *(s32 *)((u8 *)var_a3 + 0x4) =
                        (s32)(*(s32 *)((u8 *)var_a3 + 0x4) +
                              *(s32 *)((u8 *)temp_a1 + 0x4));
                } else {
                    goto block_9;
                }
            } else {
            block_9:
                var_a3 += 8;
                var_t1 += 1;
            }
        } while (D_800A2708GC[0] >= var_t1);
    }
    var_t1_2 = 0;
    if (D_800A2708GC[0] >= 0) {
        var_v1_2 = D_800A270CGC[0];
        do {
            var_t1_2 += 1;
            if (*(s32 *)((u8 *)var_v1_2 + 0x4) == 0) {
                *(s32 *)((u8 *)var_v1_2 + 0x0) = 0x2FFFFFFF;
            }
            var_v1_2 += 8;
        } while (D_800A2708GC[0] >= var_t1_2);
    }
    var_t1_3 = 0;
    if (D_800A2708GC[0] >= 0) {
        var_t2 = D_800A270CGC[0];
    loop_19:
        if (!(*(s32 *)((u8 *)var_t2 + 0x0) & 0x40000000)) {
            var_a2_2 = var_t1_3 + 1;
            if (D_800A2708GC[0] >= var_a2_2) {
                var_a0 = (var_a2_2 * 8) + D_800A270CGC[0];
            loop_22:
                temp_a1_2 = *(s32 *)((u8 *)var_a0 + 0x0);
                if (!(temp_a1_2 & 0x40000000)) {
                    temp_a3 = *(s32 *)((u8 *)var_t2 + 0x0);
                    var_a2_2 += 1;
                    if ((u32)(temp_a1_2 & 0x0FFFFFFF) <
                        (u32)(temp_a3 & 0x0FFFFFFF)) {
                        *(s32 *)((u8 *)var_t2 + 0x0) = temp_a1_2;
                        temp_v1_2 = *(s32 *)((u8 *)var_t2 + 0x4);
                        *(s32 *)((u8 *)var_t2 + 0x4) =
                            (s32) * (s32 *)((u8 *)var_a0 + 0x4);
                        *(s32 *)((u8 *)var_a0 + 0x0) = temp_a3;
                        *(s32 *)((u8 *)var_a0 + 0x4) = temp_v1_2;
                    }
                    var_a0 += 8;
                    if (D_800A2708GC[0] >= var_a2_2) {
                        goto loop_22;
                    }
                }
            }
            var_t1_3 += 1;
            var_t2 += 8;
            if (D_800A2708GC[0] >= var_t1_3) {
                goto loop_19;
            }
        }
    }
    var_t1_4 = 0;
    if (D_800A2708GC[0] >= 0) {
        var_a0_2 = D_800A270CGC[0];
    loop_29:
        temp_v1_3 = *(s32 *)((u8 *)var_a0_2 + 0x0);
        if (!(temp_v1_3 & 0x40000000)) {
            if (temp_v1_3 == 0x2FFFFFFF) {
                temp_v0 = (D_800A2708GC[0] * 8) + D_800A270CGC[0];
                *(s32 *)((u8 *)var_a0_2 + 0x0) =
                    (s32) * (s32 *)((u8 *)temp_v0 + 0x0);
                D_800A2708GC[0] = var_t1_4;
                *(s32 *)((u8 *)var_a0_2 + 0x4) =
                    (s32) * (s32 *)((u8 *)temp_v0 + 0x4);
            } else {
                var_t1_4 += 1;
                var_a0_2 += 8;
                if (D_800A2708GC[0] >= var_t1_4) {
                    goto loop_29;
                }
            }
        }
    }
    var_t1_5 = D_800A2708GC[0] - 1;
    if (var_t1_5 >= 0) {
        var_a0_3 = (var_t1_5 * 8) + D_800A270CGC[0];
    loop_35:
        temp_v1_4 = *(s32 *)((u8 *)var_a0_3 + 0x0);
        if (temp_v1_4 & 0x80000000) {
            temp_v1_5 = D_800A2708GC[0];
            *(s32 *)((u8 *)var_a0_3 + 0x0) =
                (s32)((temp_v1_4 & 0x0FFFFFFF) | 0x40000000);
            D_800A2708GC[0] = var_t1_5;
            var_t1_5 -= 1;
            *(s32 *)((u8 *)var_a0_3 + 0x4) =
                (s32)(*(s32 *)((u8 *)var_a0_3 + 0x4) +
                      *(s32 *)((u8 *)D_800A270CGC[0] + (temp_v1_5 * 8) + 4));
            var_a0_3 -= 8;
            if (var_t1_5 >= 0) {
                goto loop_35;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_gcSPU);
#endif

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuFree);

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

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
extern s32 D_800A2710Clear[];
extern s32 D_800A2298Clear[];
extern u8 D_800A22A0Clear[];
extern s32 D_800A26C4ClearRead[];
extern s32 D_800A26C4ClearWrite[];
extern s32 D_800A26D0Clear0[];
extern s32 D_800A26D0Clear1[];
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
    s32 var_v0;
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
        var_s2 = 0xFFF0 << D_800A26D0Clear1[0];
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
    var_s3 = 1;
    if (D_800A26E0ClearCheck[0] != 0) {
        sp10 = D_800A26E0ClearSave[0];
        D_800A26E0ClearWrite[0] = 0;
    }
    var_v0 = var_s1 < 0x401;
    do {
        var_s0 = var_s1;
        if (var_v0 == 0) {
            var_s0 = 0x400;
        } else {
            var_s3 = 0;
        }
        _spu_t(2, (u32)var_s2);
        _spu_t(1);
        _spu_t(3, D_800A22A0Clear, var_s0);
        var_s1 -= 0x400;
        var_s2 += 0x400;
        WaitEvent(D_800A2298Clear[0]);
        var_v0 = var_s1 < 0x401;
    } while (var_s3 != 0);
    if (var_s5 != 0)
        D_800A26C4ClearWrite[0] = temp_s4;
    if (sp10 != 0)
        D_800A26E0ClearRestore[0] = sp10;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuClearReverbWorkArea);
#endif

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
    register s32 value asm("$3");
    register SpuIRQUnion *spu asm("$2");
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
        value = 1;
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

#if 1
/* Matches under GNU C 2.6.3 only (the retail libspu compiler). Each case
 * needs its own base pointer, a u16 copy of the low half, and a pointer
 * local for the D_800A229C read. See sdk-263 notes in the knowledge base. */
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
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetKey);
#endif

/* SPDX-License-Identifier: MIT */

extern s32 _SpuSetVoiceAttr(SpuVoiceAttr *, s32, s32, s32);

void SpuSetVoiceAttr(SpuVoiceAttr *arg) {
    _SpuSetVoiceAttr(arg, 0, 23, 0);
}

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
extern volatile u16 *D_800A26ACVA[];
extern s16 _spu_note2pitch(u32, s32, u32, s32);
s32 _SpuSetVoiceAttr(SpuVoiceAttr *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp10;
    s32 sp14;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_v1_10;
    s16 temp_v1_9;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s7;
    s32 temp_v1;
    s32 temp_v1_5;
    s32 temp_v1_7;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    s32 var_a1_5;
    s32 var_a1_6;
    s32 var_s4;
    s32 var_s7;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    u16 temp_a1;
    u16 temp_a3;
    u16 var_a2;
    u16 var_a2_2;
    u16 var_a2_3;
    u16 var_a2_4;
    u16 var_a2_5;
    u16 var_s5;
    u16 var_s6;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;
    void *temp_v1_6;
    void *temp_v1_8;

    var_a1 = arg1;
    var_s7 = arg2;
    var_s6 = 0;
    temp_s1 = (*(u32 *)((u8 *)arg0 + 0x4));
    var_s5 = 0;
    temp_s2 = temp_s1 == 0;
    if (var_a1 < 0) {
        var_a1 = 0;
    }
    if (var_a1 < 0x18) {
        if (var_s7 >= 0x18) {
            var_s7 = 0x17;
        }
        if ((var_s7 < 0) || (temp_s7 = var_s7 + 1, ((var_s7 < var_a1) != 0))) {
            goto block_7;
        }
        var_s4 = var_a1;
        if (var_s4 < temp_s7) {
            do {
                if ((1 << var_s4) & (*(u32 *)((u8 *)arg0 + 0x0))) {
                    temp_s3 = var_s4 * 8;
                    if ((temp_s2 != 0) || (temp_s1 & 0x10)) {
                        *(u16 *)((u8 *)D_800A26ACVA[0] + (var_s4 * 0x10) + 4) =
                            (u16)(*(u16 *)((u8 *)arg0 + 0x14));
                    }
                    if ((temp_s2 != 0) || (temp_s1 & 0x40)) {
                        gSpuVoiceCenterNotes[var_s4] =
                            (*(u16 *)((u8 *)arg0 + 0x18));
                    }
                    var_v0 = var_s4 * 2;
                    if ((temp_s2 != 0) ||
                        (var_v0 = var_s4 * 2, ((temp_s1 & 0x20) != 0))) {
                        temp_a1 = *(s16 *)((u8 *)gSpuVoiceCenterNotes + var_v0);
                        temp_a3 = (*(u16 *)((u8 *)arg0 + 0x16));
                        *(u16 *)((u8 *)D_800A26ACVA[0] + (temp_s3 * 2) + 4) =
                            _spu_note2pitch(temp_a1 >> 8, temp_a1 & 0xFF,
                                            temp_a3 >> 8, temp_a3 & 0xFF);
                    }
                    if ((temp_s2 != 0) || (temp_s1 & 0x80)) {
                        _spu_FsetRXXa(temp_s3 | 3,
                                      (*(u32 *)((u8 *)arg0 + 0x1c)));
                    }
                    if (temp_s2 == 0) {
                        if (temp_s1 & 0x800) {
                            var_a1_2 = 0;
                            if (temp_s1 & 0x100) {
                                goto block_25;
                            }
                            goto block_29;
                        }
                    } else {
                    block_25:
                        temp_v1 = (*(s32 *)((u8 *)arg0 + 0x24));
                        if (temp_v1 != 1) {
                            var_a1_2 = 0;
                            if (temp_v1 == 5) {
                                var_a1_2 = 0x80;
                            }
                        } else {
                            var_a1_2 = 0;
                        }
                    block_29:
                        var_a2 = 0x7F;
                        if ((u16)(*(u16 *)((u8 *)arg0 + 0x30)) < 0x80U) {
                            var_a2 = (*(u16 *)((u8 *)arg0 + 0x30));
                        }
                        temp_v1_2 = (temp_s3 * 2) + (u8 *)D_800A26ACVA[0];
                        *(u16 *)((u8 *)temp_v1_2 + 0x8) =
                            (u16)((*(u16 *)((u8 *)temp_v1_2 + 0x8) & 0xFF) |
                                  ((var_a2 | var_a1_2) << 8));
                    }
                    if ((temp_s2 != 0) || (temp_s1 & 0x1000)) {
                        var_a2_2 = 0xF;
                        if ((u16)(*(u16 *)((u8 *)arg0 + 0x32)) < 0x10U) {
                            var_a2_2 = (*(u16 *)((u8 *)arg0 + 0x32));
                        }
                        temp_v1_3 = (temp_s3 * 2) + (u8 *)D_800A26ACVA[0];
                        *(u16 *)((u8 *)temp_v1_3 + 0x8) =
                            (u16)((*(u16 *)((u8 *)temp_v1_3 + 0x8) & 0xFF0F) |
                                  (var_a2_2 * 0x10));
                    }
                    if ((temp_s2 != 0) || (temp_s1 & 0x8000)) {
                        var_a2_3 = 0xF;
                        if ((u16)(*(u16 *)((u8 *)arg0 + 0x38)) < 0x10U) {
                            var_a2_3 = (*(u16 *)((u8 *)arg0 + 0x38));
                        }
                        temp_v1_4 = (temp_s3 * 2) + (u8 *)D_800A26ACVA[0];
                        *(u16 *)((u8 *)temp_v1_4 + 0x8) =
                            (u16)(var_a2_3 |
                                  (*(u16 *)((u8 *)temp_v1_4 + 0x8) & 0xFFF0));
                    }
                    if (temp_s2 == 0) {
                        if (temp_s1 & 0x2000) {
                            var_a1_3 = 0;
                            if (temp_s1 & 0x200) {
                                goto block_45;
                            }
                            goto block_54;
                        }
                    } else {
                    block_45:
                        temp_v1_5 = (*(s32 *)((u8 *)arg0 + 0x28));
                        if (temp_v1_5 != 3) {
                            if (temp_v1_5 < 4) {
                                var_a1_3 = 0;
                                if (temp_v1_5 != 1) {
                                    var_a1_3 = 0x100;
                                }
                            } else if (temp_v1_5 != 5) {
                                var_a1_3 = 0x300;
                                if (temp_v1_5 != 7) {
                                    var_a1_3 = 0x100;
                                }
                            } else {
                                var_a1_3 = 0x200;
                            }
                        } else {
                            var_a1_3 = 0x100;
                        }
                    block_54:
                        var_a2_4 = 0x7F;
                        if ((u16)(*(u16 *)((u8 *)arg0 + 0x34)) < 0x80U) {
                            var_a2_4 = (*(u16 *)((u8 *)arg0 + 0x34));
                        }
                        temp_v1_6 = (temp_s3 * 2) + (u8 *)D_800A26ACVA[0];
                        *(u16 *)((u8 *)temp_v1_6 + 0xA) =
                            (u16)((*(u16 *)((u8 *)temp_v1_6 + 0xA) & 0x3F) |
                                  ((var_a2_4 | var_a1_3) << 6));
                    }
                    if (temp_s2 == 0) {
                        if (temp_s1 & 0x4000) {
                            var_a1_4 = 0;
                            if (temp_s1 & 0x400) {
                                goto block_60;
                            }
                            goto block_64;
                        }
                    } else {
                    block_60:
                        temp_v1_7 = (*(s32 *)((u8 *)arg0 + 0x2c));
                        if (temp_v1_7 != 3) {
                            var_a1_4 = 0;
                            if (temp_v1_7 == 7) {
                                var_a1_4 = 0x20;
                            }
                        } else {
                            var_a1_4 = 0;
                        }
                    block_64:
                        var_a2_5 = 0x1F;
                        if ((u16)(*(u16 *)((u8 *)arg0 + 0x36)) < 0x20U) {
                            var_a2_5 = (*(u16 *)((u8 *)arg0 + 0x36));
                        }
                        temp_v1_8 = (temp_s3 * 2) + (u8 *)D_800A26ACVA[0];
                        *(u16 *)((u8 *)temp_v1_8 + 0xA) =
                            (u16)((*(u16 *)((u8 *)temp_v1_8 + 0xA) & 0xFFC0) |
                                  (var_a2_5 | var_a1_4));
                    }
                    var_v0_2 = temp_s3 * 2;
                    if ((temp_s2 != 0) ||
                        (var_v0_2 = temp_s3 * 2, ((temp_s1 & 0x20000) != 0))) {
                        *(u16 *)((u8 *)D_800A26ACVA[0] + var_v0_2 + 8) =
                            (u16)(*(u16 *)((u8 *)arg0 + 0x3a));
                    }
                    var_v0_3 = temp_s3 * 2;
                    if ((temp_s2 != 0) ||
                        (var_v0_3 = temp_s3 * 2, ((temp_s1 & 0x40000) != 0))) {
                        *(u16 *)((u8 *)D_800A26ACVA[0] + var_v0_3 + 0xA) =
                            (u16)(*(u16 *)((u8 *)arg0 + 0x3c));
                    }
                    if ((temp_s2 != 0) || (temp_s1 & 0x10000)) {
                        _spu_FsetRXXa(temp_s3 | 7,
                                      (*(u32 *)((u8 *)arg0 + 0x20)));
                    }
                    if (temp_s2 == 0) {
                        if (temp_s1 & 1) {
                            if (temp_s1 & 4) {
                                goto block_79;
                            }
                            goto block_88;
                            goto block_89;
                        }
                    } else {
                    block_79:
                        temp_v1_9 = (*(u16 *)((u8 *)arg0 + 0xc));
                        switch (temp_v1_9) { /* switch 1 */
                        case 1:              /* switch 1 */
                            var_a1_5 = 0x8000;
                            break;
                        case 2: /* switch 1 */
                            var_a1_5 = 0x9000;
                            break;
                        case 3: /* switch 1 */
                            var_a1_5 = 0xA000;
                            break;
                        case 4: /* switch 1 */
                            var_a1_5 = 0xB000;
                            break;
                        case 5: /* switch 1 */
                            var_a1_5 = 0xC000;
                            break;
                        case 6: /* switch 1 */
                            var_a1_5 = 0xD000;
                            break;
                        case 7: /* switch 1 */
                            var_a1_5 = 0xE000;
                            break;
                        default: /* switch 1 */
                        block_88:
                            var_s6 = (*(u16 *)((u8 *)arg0 + 0x8));
                            var_a1_5 = 0;
                            break;
                        }
                    block_89:
                        var_v0_4 = var_s6 & 0x7FFF;
                        if (var_a1_5 != 0) {
                            temp_a0 = (s16)(*(u16 *)((u8 *)arg0 + 0x8));
                            if (temp_a0 >= 0x80) {
                                var_s6 = 0x7F;
                            } else {
                                var_s6 = (u16)temp_a0;
                                if (temp_a0 < 0) {
                                    var_s6 = 0;
                                }
                            }
                            var_v0_4 = var_s6 & 0x7FFF;
                        }
                        *((temp_s3 * 2) + (u8 *)D_800A26ACVA[0]) =
                            var_v0_4 | var_a1_5;
                    }
                    if (temp_s2 == 0) {
                        if (temp_s1 & 2) {
                            if (temp_s1 & 8) {
                                goto block_99;
                            }
                            goto block_108;
                            goto block_109;
                        }
                    } else {
                    block_99:
                        temp_v1_10 = (*(u16 *)((u8 *)arg0 + 0xe));
                        switch (temp_v1_10) { /* switch 2 */
                        case 1:               /* switch 2 */
                            var_a1_6 = 0x8000;
                            break;
                        case 2: /* switch 2 */
                            var_a1_6 = 0x9000;
                            break;
                        case 3: /* switch 2 */
                            var_a1_6 = 0xA000;
                            break;
                        case 4: /* switch 2 */
                            var_a1_6 = 0xB000;
                            break;
                        case 5: /* switch 2 */
                            var_a1_6 = 0xC000;
                            break;
                        case 6: /* switch 2 */
                            var_a1_6 = 0xD000;
                            break;
                        case 7: /* switch 2 */
                            var_a1_6 = 0xE000;
                            break;
                        default: /* switch 2 */
                        block_108:
                            var_s5 = (*(u16 *)((u8 *)arg0 + 0xa));
                            var_a1_6 = 0;
                            break;
                        }
                    block_109:
                        var_v0_5 = var_s5 & 0x7FFF;
                        if (var_a1_6 != 0) {
                            temp_a0_2 = (s16)(*(u16 *)((u8 *)arg0 + 0xa));
                            if (temp_a0_2 >= 0x80) {
                                var_s5 = 0x7F;
                            } else {
                                var_s5 = (u16)temp_a0_2;
                                if (temp_a0_2 < 0) {
                                    var_s5 = 0;
                                }
                            }
                            var_v0_5 = var_s5 & 0x7FFF;
                        }
                        *(u16 *)((u8 *)D_800A26ACVA[0] + (temp_s3 * 2) + 2) =
                            (s16)(var_v0_5 | var_a1_6);
                    }
                }
                var_s4 += 1;
            } while (var_s4 < temp_s7);
        }
        if (arg3 == 0) {
            sp14 = 1;
            sp10 = 0;
        loop_120:
            if (sp10 < 2) {
                sp14 *= 0xD;
                sp10 += 1;
                goto loop_120;
            }
        }
        return 0;
    }
block_7:
    return -3;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", _SpuSetVoiceAttr);
#endif

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

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
void SpuSetCommonAttrDraft(SpuCommonAttr *) asm("SpuSetCommonAttr");
extern volatile u16 *D_800A26ACCommon2[];
void SpuSetCommonAttrDraft(SpuCommonAttr *arg0) {
    s32 mask;
    s32 isDefault;
    u16 volLeft;
    u16 volRight;
    s32 modeLeft;
    s32 modeRight;
    s32 modeCode;
    s32 value;
    s32 tmp;
    mask = arg0->mask;
    isDefault = (mask == 0);
    volLeft = 0;
    volRight = 0;
    modeLeft = 0;
    modeRight = 0;
    if (isDefault || (mask & 1)) {
        if (!isDefault && !(mask & 4)) {
            volLeft = arg0->mvol.left;
            modeLeft = 0;
        } else {
            modeCode = arg0->mvolmode.left;
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
            default:
                volLeft = arg0->mvol.left;
                modeLeft = 0;
                break;
            }
        }
        value = volLeft & 0x7FFF;
        if (modeLeft != 0) {
            tmp = (s16)arg0->mvol.left;
            if (tmp >= 0x80)
                volLeft = 0x7F;
            else if (tmp < 0)
                volLeft = 0;
            else
                volLeft = tmp;
            value = volLeft & 0x7FFF;
        }
        D_800A26ACCommon2[0][0x180 / 2] = (value | modeLeft);
    }
    if (isDefault || (mask & 2)) {
        if (!isDefault && !(mask & 8)) {
            volRight = arg0->mvol.right;
            modeRight = 0;
        } else {
            modeCode = arg0->mvolmode.right;
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
            default:
                volRight = arg0->mvol.right;
                modeRight = 0;
                break;
            }
        }
        value = volRight & 0x7FFF;
        if (modeRight != 0) {
            tmp = (s16)arg0->mvol.right;
            if (tmp >= 0x80)
                volRight = 0x7F;
            else if (tmp < 0)
                volRight = 0;
            else
                volRight = tmp;
            value = volRight & 0x7FFF;
        }
        D_800A26ACCommon2[0][0x182 / 2] = (value | modeRight);
    }
    if (isDefault || (mask & 0x40))
        D_800A26ACCommon2[0][0x1B0 / 2] = arg0->cd.volume.left;
    if (isDefault || (mask & 0x80))
        D_800A26ACCommon2[0][0x1B2 / 2] = arg0->cd.volume.right;
    if (isDefault || (mask & 0x100)) {
        value = D_800A26ACCommon2[0][0x1AA / 2];
        if (arg0->cd.reverb == 0)
            value &= 0xFFFB;
        else
            value |= 4;
        D_800A26ACCommon2[0][0x1AA / 2] = value;
    }
    if (isDefault || (mask & 0x200)) {
        value = D_800A26ACCommon2[0][0x1AA / 2];
        if (arg0->cd.mix == 0)
            value &= 0xFFFE;
        else
            value |= 1;
        D_800A26ACCommon2[0][0x1AA / 2] = value;
    }
    if (isDefault || (mask & 0x400))
        D_800A26ACCommon2[0][0x1B4 / 2] = arg0->ext.volume.left;
    if (isDefault || (mask & 0x800))
        D_800A26ACCommon2[0][0x1B6 / 2] = arg0->ext.volume.right;
    if (isDefault || (mask & 0x1000)) {
        value = D_800A26ACCommon2[0][0x1AA / 2];
        if (arg0->ext.reverb == 0)
            value &= 0xFFF7;
        else
            value |= 8;
        D_800A26ACCommon2[0][0x1AA / 2] = value;
    }
    if (isDefault || (mask & 0x2000)) {
        value = D_800A26ACCommon2[0][0x1AA / 2];
        if (arg0->ext.mix == 0)
            value &= 0xFFFD;
        else
            value |= 2;
        D_800A26ACCommon2[0][0x1AA / 2] = value;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetCommonAttr);
#endif

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */
extern u16 D_800A2A08[];
s32 _spu_note2pitch(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 temp_a0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1_2;
    u16 var_v1;
    var_v0 = (arg3 & 0xFFFF) + (arg1 & 0xFFFF);
    if (var_v0 < 0)
        var_v0 += 7;
    temp_v0 = var_v0 >> 3;
    var_a1 = temp_v0;
    var_v1_2 = 0;
    if (temp_v0 >= 0x10) {
        do {
            temp_v0_2 = var_a1 - 0x10;
            var_a1 = temp_v0_2;
            var_v1_2 += 1;
        } while ((s16)temp_v0_2 >= 0x10);
    }
    if (var_a1 & 0x8000)
        var_a1 = 0;
    temp_v0_3 = (arg2 + 0x3C) - arg0;
    var_v1 = D_800A2A08[(((s32)(((var_v1_2 + temp_v0_3) % 12) << 16) >> 12) +
                         (s16)var_a1)];
    temp_a0 = ((var_v1_2 + temp_v0_3) / 12) - 5;
    if (temp_a0 > 0)
        var_v1 <<= temp_a0;
    else if (temp_a0 < 0)
        var_v1 = (u16)((s32)(var_v1 & 0xFFFF) >> -temp_a0);
    return var_v1 & 0xFFFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_note2pitch);
#endif

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */

s32 _spu_pitch2note(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_lo;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a3;
    s32 var_v0;
    s32 var_v1;

    var_a3 = 0;
    var_v1 = 0;
    do {
        if (((s32)(arg2 & 0xFFFF) >> var_v1) & 1) {
            var_a3 = var_v1;
        }
        var_v1 += 1;
    } while (var_v1 < 0x10);
    temp_v0 = 1 << var_a3;
    temp_a1_2 = (1 << (var_a3 + 1)) - temp_v0;
    temp_a0 = (arg2 & 0xFFFF) - temp_v0;
    temp_lo = (s32)(temp_a0 * 0xC) / temp_a1_2;
    temp_v1 =
        (arg1 & 0xFFFF) +
        ((s32)((temp_a0 - ((temp_a1_2 * temp_lo) / 12)) * 0x600) / temp_a1_2);
    var_v0 = temp_v1;
    if (temp_v1 < 0) {
        var_v0 = temp_v1 + 0x7F;
    }
    temp_a1 =
        (arg0 & 0xFFFF) + ((var_a3 - 0xC) * 0xC) + temp_lo + (temp_v1 >= 0x80);
    if ((temp_a1 >= 0) && (temp_a1 < 0x80)) {
        return (temp_a1 << 8) | (temp_v1 - ((var_v0 >> 7) << 7));
    }
    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_pitch2note);
#endif

#ifdef NON_MATCHING
/* Complete C draft; code generation still differs from retail. */

s32 SpuRGetAllKeysStatus(s32 min, s32 max, s8 *status) {
    s32 voice;
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
        volume = *(volatile u16 *)&D_800A26AC[0][(8 * voice) + 6];
        if ((1 << voice) & D_800A229CInit[0]) {
            if (volume != 0)
                status[voice] = 1;
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
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuRGetAllKeysStatus);
#endif

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
