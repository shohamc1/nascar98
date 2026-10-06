/* SPDX-License-Identifier: AGPL-3.0-only AND MIT */
/* SDK C from sotn-decomp d818995ec49ef76e3b1625a96f4360108b3168be. */
#include "common.h"
#include "psxsdk_internal.h"
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/stdarg.h>

#include <psxsdk/libspu.h>
#include <psxsdk/libgpu.h>
#include <psxsdk/libcd.h>

extern void SpuVmSeqKeyOff();

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", InitHeap);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _bu_init);

INCLUDE_ASM("asm/nonmatchings/psxsdk", OpenEvent);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CloseEvent);

INCLUDE_ASM("asm/nonmatchings/psxsdk", TestEvent);

INCLUDE_ASM("asm/nonmatchings/psxsdk", EnableEvent);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DisableEvent);

INCLUDE_ASM("asm/nonmatchings/psxsdk", InitPAD);

INCLUDE_ASM("asm/nonmatchings/psxsdk", StartPAD);

INCLUDE_ASM("asm/nonmatchings/psxsdk", EnterCriticalSection);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ExitCriticalSection);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SwEnterCriticalSection);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SwExitCriticalSection);

INCLUDE_ASM("asm/nonmatchings/psxsdk", open);

INCLUDE_ASM("asm/nonmatchings/psxsdk", close);

INCLUDE_ASM("asm/nonmatchings/psxsdk", format);

INCLUDE_ASM("asm/nonmatchings/psxsdk", firstfile);

INCLUDE_ASM("asm/nonmatchings/psxsdk", nextfile);

INCLUDE_ASM("asm/nonmatchings/psxsdk", delete);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ChangeClearPAD);

INCLUDE_ASM("asm/nonmatchings/psxsdk", GetGp);

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
    asm("");
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
    asm("" : : "r"(addr));
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
    asm("");
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", DeliverEvent);

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
    register int ret asm("v0");

    asm volatile("addiu $29, $29, -24\n\tsw $31, 16($29)");
    asm volatile("jal CD_vol");
    asm volatile("ori $2, $zero, 1" : "=r"(ret));
    asm volatile("lw $31, 16($29)\n\taddiu $29, $29, 24");
    return ret;
}

/* SPDX-License-Identifier: MIT */

extern int CD_getsector(void *madr, int size);

int CdGetSector(void *madr, int size) {
    register int ret asm("v0");

    asm volatile("addiu $29, $29, -24\n\tsw $31, 16($29)");
    asm volatile("jal CD_getsector");
    asm volatile("sltiu $2, $2, 1" : "=r"(ret));
    asm volatile("lw $31, 16($29)\n\taddiu $29, $29, 24");
    return ret;
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
    register s32 n asm("a0") = i;
    register CdlLOC *out asm("v0");
    register s32 minuteBcd asm("a1");

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", ChangeClearRCnt);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", stopIntr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", restartIntr);

void memclr(void *ptr, size_t size) {
    int *end;
    end = (int *)ptr;
    while (size--) {
        *end++ = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", _96_remove);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ReturnFromException);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ResetEntryInt);

INCLUDE_ASM("asm/nonmatchings/psxsdk", HookEntryInt);

INCLUDE_ASM("asm/nonmatchings/psxsdk", startIntrVSync);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", startIntrDMA);

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
    register DRAWENV *sEnv asm("s1");
    register s32 sX asm("s3");
    register s32 sY asm("s4");
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
            asm("" : : "r"(width));
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
                    asm("" : : "r"(magic));
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawTPage);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawLoad);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MargePrim);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", DrawSync);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", ClearImage);

INCLUDE_ASM("asm/nonmatchings/psxsdk", LoadImage);

INCLUDE_ASM("asm/nonmatchings/psxsdk", StoreImage);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MoveImage);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ClearOTag);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ClearOTagR);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DrawPrim);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DrawOTag);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetTexWindow);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawArea);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawOffset);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawMode);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawEnv);

INCLUDE_ASM("asm/nonmatchings/psxsdk", get_mode);

INCLUDE_ASM("asm/nonmatchings/psxsdk", get_cs);

INCLUDE_ASM("asm/nonmatchings/psxsdk", get_ce);

INCLUDE_ASM("asm/nonmatchings/psxsdk", get_ofs);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _cwb);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _cwc);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _param);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _addque);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _addque2);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", GPU_cw);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", InitGeom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", InvSquareRoot);

INCLUDE_ASM("asm/nonmatchings/psxsdk", VectorNormalS);

INCLUDE_ASM("asm/nonmatchings/psxsdk", VectorNormal);

INCLUDE_ASM("asm/nonmatchings/psxsdk", VectorNormalSS);

INCLUDE_ASM("asm/nonmatchings/psxsdk", func_8007C548);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MatrixNormal);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CompMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MulMatrix0);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MulRotMatrix0);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MulRotMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetMulMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ApplyMatrixLV);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ApplyRotMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ScaleMatrixL);

INCLUDE_ASM("asm/nonmatchings/psxsdk", PushMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", PopMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ReadRotMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ReadLightMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ReadColorMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MulMatrix2);

INCLUDE_ASM("asm/nonmatchings/psxsdk", TransMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetRotMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetTransMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetVertex0);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetVertex1);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetVertex2);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetVertexTri);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetRGBfifo);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetIR123);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetIR0);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetSZfifo3);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetSZfifo4);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetSXSYfifo);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetRii);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetMAC123);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetData32);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDQA);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDQB);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetBackColor);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetFarColor);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetGeomOffset);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetGeomScreen);

INCLUDE_ASM("asm/nonmatchings/psxsdk", LightColor);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DpqColorLight);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DpqColor3);

INCLUDE_ASM("asm/nonmatchings/psxsdk", Intpl);

INCLUDE_ASM("asm/nonmatchings/psxsdk", Square12);

INCLUDE_ASM("asm/nonmatchings/psxsdk", Square0);

INCLUDE_ASM("asm/nonmatchings/psxsdk", AverageZ3);

INCLUDE_ASM("asm/nonmatchings/psxsdk", AverageZ4);

INCLUDE_ASM("asm/nonmatchings/psxsdk", OuterProduct12);

INCLUDE_ASM("asm/nonmatchings/psxsdk", OuterProduct0);

INCLUDE_ASM("asm/nonmatchings/psxsdk", Lzc);

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotTrans);

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotTransPers_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotTransPers3_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotTrans_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotTransPers4_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotAverage3_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotNclip3_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotAverageNclip3_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotColorDpq_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotColorDpq3_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotAverageNclipColorDpq3_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotAverageNclipColorCol3_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", NormalColor_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", NormalColor3_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", NormalColorDpq_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", NormalColorDpq3_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", NormalColorCol_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", NormalColorCol3_nom);

INCLUDE_ASM("asm/nonmatchings/psxsdk", RotMatrix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _patch_gte);

INCLUDE_ASM("asm/nonmatchings/psxsdk", func_8007DCDC);

INCLUDE_ASM("asm/nonmatchings/psxsdk", FlushCache);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsSetMute);

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
void SpuVmSetProgVol(s16, u8, u8);
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsContRpn1);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsContRpn2);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsUtResolveADSR);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsUtBuildADSR);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsIsEos);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsSetMarkCallback);

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
    register s32 magic asm("v1") = 0x81020409;
    register s32 n1 asm("a2") = (ldepth << 15) - ldepth;
    register s32 hi1 asm("v0");
    register s32 n2 asm("a3");
    register s32 d1 asm("v0");
    register s32 hi2 asm("v0");
    register s32 d2 asm("v0");
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SeAutoVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetAutoVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SeAutoPan);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmSetSeqVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmGetSeqVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmGetSeqLVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmGetSeqRVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmSeqKeyOff);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmSetProgVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmGetProgVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmSetProgPan);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmGetProgPan);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmSetVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtKeyOn);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtKeyOff);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtKeyOnV);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtKeyOffV);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtPitchBend);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtChangePitch);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtChangeADSR);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtGetDetVVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtSetDetVVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtGetVVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtSetVVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtAutoVol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtAutoPan);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_FsetRXX);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetMute);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuInitMalloc);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", WaitEvent);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetIRQ);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetIRQAddr);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuGetKeyStatus);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuGetAllKeysStatus);

INCLUDE_ASM("asm/nonmatchings/psxsdk", exit);

INCLUDE_ASM("asm/nonmatchings/psxsdk", puts);

INCLUDE_ASM("asm/nonmatchings/psxsdk", setjmp);

INCLUDE_ASM("asm/nonmatchings/psxsdk", strcat);

INCLUDE_ASM("asm/nonmatchings/psxsdk", strcmp);

INCLUDE_ASM("asm/nonmatchings/psxsdk", strcpy);

INCLUDE_ASM("asm/nonmatchings/psxsdk", strlen);

INCLUDE_ASM("asm/nonmatchings/psxsdk", bzero);

INCLUDE_ASM("asm/nonmatchings/psxsdk", memcpy);

INCLUDE_ASM("asm/nonmatchings/psxsdk", memset_8008B820);

INCLUDE_ASM("asm/nonmatchings/psxsdk", printf);

INCLUDE_ASM("asm/nonmatchings/psxsdk", sprintf);

INCLUDE_ASM("asm/nonmatchings/psxsdk", memchr);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _card_info);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _card_load);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _card_auto);

INCLUDE_ASM("asm/nonmatchings/psxsdk", InitCARD);

INCLUDE_ASM("asm/nonmatchings/psxsdk", StartCARD);

INCLUDE_ASM("asm/nonmatchings/psxsdk", StopCARD);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _card_write);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _card_read);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _new_card);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _card_clear);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DecDCTReset);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DecDCTGetEnv);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DecDCTPutEnv);

/* SPDX-License-Identifier: MIT */

u16 DecDCTBufSize(u16 *buf) {
    return buf[0];
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", DecDCTin);

/* SPDX-License-Identifier: MIT */

extern void MDEC_out(u_long *);

void DecDCTout(u_long *buf) {
    MDEC_out(buf);
}

/* SPDX-License-Identifier: MIT */

extern void MDEC_in_sync(void);

void DecDCTinSync(void) {
    MDEC_in_sync();
}

/* SPDX-License-Identifier: MIT */

extern void MDEC_out_sync(void);

void DecDCToutSync(void) {
    MDEC_out_sync();
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", DecDCTinCallback);

long DecDCToutCallback(void (*func)()) {
    return (long)DMACallback(1, func);
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", MDEC_reset);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MDEC_in);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MDEC_out);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MDEC_in_sync);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MDEC_out_sync);

INCLUDE_ASM("asm/nonmatchings/psxsdk", timeout);

INCLUDE_ASM("asm/nonmatchings/psxsdk", D_8008CA04);
