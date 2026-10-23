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

extern volatile RCnt *_counters asm("D_8009B9E8");
long SetRCnt(long timer, unsigned short target, long mode) {
    long timerIndex = timer & 0xFFFF;
    long modeValue = 0x48;
    if (timerIndex >= 3) {
        return 0;
    }
    _counters[timerIndex].mode = 0;
    _counters[timerIndex].target = target;
    if (timerIndex < 2U) {
        if (mode & 0x10) {
            modeValue = 0x49;
        }
        if (!(mode & 1)) {
            modeValue |= 0x100;
        }
    } else if (timerIndex == 2U) {
        if (!(mode & 1)) {
            modeValue = 0x248;
        }
    }
    if ((mode & 0x1000) != 0) {
        modeValue |= 0x10;
    }
    _counters[timerIndex].mode = modeValue;
    return 1;
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
