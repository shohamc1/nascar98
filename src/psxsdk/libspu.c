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
            printf("SPU:T/O [%s]\n", "wait (reset)");
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
                printf("SPU:T/O [%s]\n", "wait (wrdy H -> L)");
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
            printf("SPU:T/O [%s]\n", "wait (dmaf clear/W)");
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

extern s32 _spu_rev_flag;
s32 SpuSetReverb(s32 on_off) {
    u16 cnt;
    switch (on_off) {
    case 0:
        _spu_rev_flag = 0;
        cnt = _spu_RXX->rxx.spucnt;
        cnt &= ~0x80;
        _spu_RXX->rxx.spucnt = cnt;
        break;
    case 1:
        if (_spu_rev_reserve_wa != on_off &&
            _SpuIsInAllocateArea_(_spu_rev_offsetaddr) != 0) {
            _spu_rev_flag = 0;
            cnt = _spu_RXX->rxx.spucnt;
            cnt &= ~0x80;
            _spu_RXX->rxx.spucnt = cnt;
        } else {
            _spu_rev_flag = on_off;
            cnt = _spu_RXX->rxx.spucnt;
            cnt |= 0x80;
            _spu_RXX->rxx.spucnt = cnt;
        }
        break;
    }
    return _spu_rev_flag;
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

typedef struct SpuIRQPrefix {
    u8 pad[0x1AA];
    u16 control;
} SpuIRQPrefix;
typedef union SpuIRQUnion {
    volatile SpuIRQPrefix rxx;
} SpuIRQUnion;
extern SpuIRQUnion *D_800A26ACIRQ[];
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
                printf("SPU: time out: wait (IRQ/ON)");
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
                printf("SPU: time out: wait (IRQ/OFF)");
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
