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
static const char sVSyncTimeoutMessage[] = "VSync: timeout\n";
static const char sIntrId[] =
    "$Id: intr.c,v 1.73 1995/11/10 05:29:40 suzu Exp $";

void v_wait(int mode, int time) {
    volatile int timeout[2];

    timeout[0] = time << 15;
    while (Vcount < mode) {
        if (timeout[0]-- == 0) {
            puts(sVSyncTimeoutMessage);
            ChangeClearPAD(0);
            ChangeClearRCnt(3, 0);
            return;
        }
    }
}

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

typedef struct IntrEnv {
    u16 initialized;
    u16 inInterrupt;
    Callback handlers[11];
    u16 enabledMask;
    u16 savedMask;
    s32 savedPcr;
    s32 buf[12];
    s32 stack[1024];
} IntrEnv;
extern IntrEnv intrEnv;
extern volatile u16 *i_mask;
extern volatile u16 *g_InterruptMask;
extern s32 intrTimeout;
extern int printf(const char *, ...);
extern void ReturnFromException(void);
static const char sUnexpectedInterruptFormat[] = "unexpected interrupt(%04x)\n";
static const char sInterruptTimeoutFormat[] = "intr timeout(%04x:%04x)\n";
extern struct Callbacks *pCallbacks;
extern void trapIntr(void);
extern int setjmp(s32 *);
extern Callback startIntrVSync(void);
extern Callback startIntrDMA(void);
extern void _96_remove(void);
extern void HookEntryInt(void *);
extern volatile s32 *d_pcr;
extern void memclr(void *, size_t);

void *startIntr(void) {
    if (intrEnv.initialized != 0) {
        return 0;
    }
    *i_mask = *g_InterruptMask = 0;
    *d_pcr = 0x33333333;
    memclr(&intrEnv, sizeof(intrEnv) / sizeof(s32));
    if (setjmp(intrEnv.buf) != 0) {
        trapIntr();
    }
    intrEnv.buf[1] = (s32)&intrEnv.stack[1004];
    HookEntryInt(intrEnv.buf);
    intrEnv.initialized = 1;
    pCallbacks->VSyncCallbacks = (void *)startIntrVSync();
    {
        register struct Callbacks *cb asm("a0");
        void *dma = startIntrDMA();
        cb = pCallbacks;
        cb->DMACallback = dma;
    }
    _96_remove();
    ExitCriticalSection();
    return &intrEnv;
}

void trapIntr(void) {
    s32 i;
    u16 mask;

    if (intrEnv.initialized == 0) {
        printf((char *)sUnexpectedInterruptFormat, *i_mask);
        ReturnFromException();
    }
    intrEnv.inInterrupt = 1;
    mask = (intrEnv.enabledMask & *i_mask) & *g_InterruptMask;
    while (mask != 0) {
        for (i = 0; mask && i < 11; ++i, mask >>= 1) {
            if (mask & 1) {
                *i_mask = ~(1 << i);
                if (intrEnv.handlers[i] != 0) {
                    intrEnv.handlers[i]();
                }
            }
        }
        mask = (intrEnv.enabledMask & *i_mask) & *g_InterruptMask;
    }
    if (*i_mask & *g_InterruptMask) {
        if (intrTimeout++ > 0x800) {
            printf((char *)sInterruptTimeoutFormat, *i_mask, *g_InterruptMask);
            intrTimeout = 0;
            *i_mask = 0;
        }
    } else {
        intrTimeout = 0;
    }
    intrEnv.inInterrupt = 0;
    ReturnFromException();
}

Callback setIntr(s32 irq, Callback callback) {
    Callback old;
    u16 prev;
    s32 mask;

    old = intrEnv.handlers[irq];
    if ((callback != old) && (intrEnv.initialized != 0)) {
        prev = *g_InterruptMask;
        *g_InterruptMask = 0;
        mask = prev & 0xFFFF;
        if (callback != 0) {
            intrEnv.handlers[irq] = callback;
            mask = mask | (1 << irq);
            intrEnv.enabledMask |= (1 << irq);
        } else {
            intrEnv.handlers[irq] = 0;
            mask = mask & ~(1 << irq);
            intrEnv.enabledMask &= ~(1 << irq);
        }
        if (irq == 0) {
            ChangeClearPAD(callback == 0);
            ChangeClearRCnt(3, callback == 0);
        }
        if (irq == 4) {
            ChangeClearRCnt(0, callback == 0);
        }
        if (irq == 5) {
            ChangeClearRCnt(1, callback == 0);
        }
        if (irq == 6) {
            ChangeClearRCnt(2, callback == 0);
        }
        *g_InterruptMask = mask;
    }
    return old;
}

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

void trapIntrVSync(void) {
    int i;

    Vcount += 1;
    (void)Vcount;
    for (i = 0; i < 8; i++) {
        if (D_8009CE64[i] != 0) {
            D_8009CE64[i]();
        }
    }
}

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

static const char sDmaBusErrorFormat[] = "DMA bus error: code=%08x\n";
static const char sDmaMadrFormat[] = "MADR[%d]=%08x\n";
static const char sHexDigits[] = "0123456789ABCDEF";
/* Retail pads this object's .rodata with one zero word. No code reads it. */
asm(".rdata\n.long 0\n.text");

extern volatile u32 *dicr;
extern u32 *dmaBase;

void trapIntrDMA(void) {
    u32 mask;
    s32 i;

    while ((mask = (*dicr >> 24) & 0x7F) != 0) {
        for (i = 0; mask != 0 && i < 7; i++, mask >>= 1) {
            if (mask & 1) {
                *dicr &= (0xFFFFFF | (1 << (i + 24)));
                if (D_8009CE90[i] != 0) {
                    D_8009CE90[i]();
                }
            }
        }
    }

    if ((*dicr & 0xFF000000) == 0x80000000 || *dicr & 0x8000) {
        printf((char *)sDmaBusErrorFormat, *dicr);
        for (i = 0; i < 7; i++) {
            printf((char *)sDmaMadrFormat, i, dmaBase[4 * i]);
        }
    }
}

Callback setIntrDMA(int index, Callback callback) {
    Callback prev = D_8009CE90[index];
    if (callback != prev) {
        if (callback != 0) {
            D_8009CE90[index] = callback;
            *dicr = (*dicr & 0xFFFFFF) | 0x800000 | ((1 << (index + 16)));
        } else {
            D_8009CE90[index] = 0;
            *dicr = ((*dicr & 0xFFFFFF) | 0x800000) & ~(1 << (index + 16));
        }
    }
    return prev;
}

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
