/* SPDX-License-Identifier: AGPL-3.0-only AND MIT */
/* SDK C from sotn-decomp d818995ec49ef76e3b1625a96f4360108b3168be. */
#include "common.h"
#include "psxsdk_internal.h"
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>

#include <psxsdk/libspu.h>
#include <psxsdk/libgpu.h>
#include <psxsdk/libcd.h>

extern void SpuVmSeqKeyOff();

INCLUDE_ASM("asm/nonmatchings/psxsdk", __SN_ENTRY_POINT);

INCLUDE_ASM("asm/nonmatchings/psxsdk", __do_global_dtors);

INCLUDE_ASM("asm/nonmatchings/psxsdk", __main);

INCLUDE_ASM("asm/nonmatchings/psxsdk", __divdi3);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetRCnt);

INCLUDE_ASM("asm/nonmatchings/psxsdk", GetRCnt);

INCLUDE_ASM("asm/nonmatchings/psxsdk", StartRCnt);

INCLUDE_ASM("asm/nonmatchings/psxsdk", StopRCnt);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ResetRCnt);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdGetToc);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdGetToc2);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdInit);

INCLUDE_ASM("asm/nonmatchings/psxsdk", func_80074C98);

INCLUDE_ASM("asm/nonmatchings/psxsdk", func_80074CC0);

INCLUDE_ASM("asm/nonmatchings/psxsdk", func_80074CE8);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DeliverEvent);

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA8C[];

char CdStatus(void) { return D_8009BA8C[0]; }

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA9C[];

int CdMode(void) { return D_8009BA9C[0]; }

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA9D[];

int CdLastCom(void) { return D_8009BA9D[0]; }

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA98[];

unsigned char* CdLastPos(void) { return D_8009BA98; }

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

void CdFlush(void) { CD_flush(); }

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdSetDebug);

/* SPDX-License-Identifier: MIT */

extern char* D_8009BAA0[];
extern char D_80090168[];

char* CdComstr(unsigned char com) {
    if (com > 0x1B) {
        return D_80090168;
    }
    return D_8009BAA0[com];
}

/* SPDX-License-Identifier: MIT */

extern char* D_8009BB20[];
extern char D_80090168[];

char* CdIntstr(u8 intr) {
    if (intr > 6) {
        return D_80090168;
    }
    return D_8009BB20[intr];
}

/* SPDX-License-Identifier: MIT */

extern int CD_sync(int mode, u8* result);

int CdSync(int mode, u8* result) { return CD_sync(mode, result); }

/* SPDX-License-Identifier: MIT */

extern int CD_ready(int mode, u8* result);

int CdReady(int mode, u8* result) { return CD_ready(mode, result); }

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdSyncCallback);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdReadyCallback);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdControl);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdControlF);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdControlB);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdMix);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdGetSector);

/* SPDX-License-Identifier: MIT */

long CdDataCallback(void (*func)()) { return (long)DMACallback(3, func); }

/* SPDX-License-Identifier: MIT */

extern void CD_datasync(int mode);

void CdDataSync(int mode) { CD_datasync(mode); }

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdIntToPos);

int CdPosToInt(CdlLOC* p) {
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", CD_vol);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CD_flush);

INCLUDE_ASM("asm/nonmatchings/psxsdk", CD_initvol);

extern u32 D_8009BA80[];
extern u32 D_8009BA7C[];
extern u32 D_8009BA90[];
extern u32 D_8009BA8C[];
extern void callback();

int CD_initintr(void) {
    D_8009BA80[0] = 0;
    D_8009BA7C[0] = 0;
    D_8009BA90[0] = 0;
    D_8009BA8C[0] = 0;
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", CdReadCallback);

INCLUDE_ASM("asm/nonmatchings/psxsdk", VSync);

INCLUDE_ASM("asm/nonmatchings/psxsdk", v_wait);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ChangeClearRCnt);

extern struct Callbacks *D_8009CE50[];
void *ResetCallback(void) { return D_8009CE50[0]->ResetCallback(); }

extern struct Callbacks *D_8009CE50[];
void InterruptCallback(int irq, Callback callback) {
    D_8009CE50[0]->InterruptCallback(irq, callback);
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
void StopCallback(void) { D_8009CE50[0]->StopCallback(); }

extern struct Callbacks *D_8009CE50[];
long RestartCallback(void) { return (long)D_8009CE50[0]->RestartCallback(); }

extern u16 D_8009BDCA[];
int CheckCallback(void) { return D_8009BDCA[0]; }

extern volatile u16 *D_8009CE58[];
u16 GetIntrMask(void) { return *D_8009CE58[0]; }

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", memclr_80077BBC);

INCLUDE_ASM("asm/nonmatchings/psxsdk", startIntrDMA);

INCLUDE_ASM("asm/nonmatchings/psxsdk", trapIntrDMA);

INCLUDE_ASM("asm/nonmatchings/psxsdk", setIntrDMA);

INCLUDE_ASM("asm/nonmatchings/psxsdk", memclr_80077E64);

extern long D_8009CEB0[];
extern long D_8009CEB4[];
long SetVideoMode(long mode) {
    long previous;
    previous = D_8009CEB4[0];
    D_8009CEB0[1] = mode;
    return previous;
}

extern long D_8009CEB4[];
long GetVideoMode(void) { return D_8009CEB4[0]; }

u_short LoadTPage(u_long* pix, int tp, int abr, int x, int y, int w, int h) {
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

u_short LoadClut(u_long* clut, int x, int y) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = 0x100;
    rect.h = 1;
    LoadImage(&rect, clut);

    return GetClut(x, y);
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", LoadClut2);

#ifdef NON_MATCHING
/* SPDX-License-Identifier: MIT */

extern long GetVideoMode(void);
extern int GetGraphType(void);

DRAWENV* SetDefDrawEnv(DRAWENV* env, s32 x, s32 y, s32 w, s32 h) {
    int videoMode;

    videoMode = GetVideoMode();
    env->clip.x = x;
    env->clip.y = y;
    env->clip.w = w;
    env->clip.h = h;
    env->ofs[0] = x;
    env->ofs[1] = y;
    env->r0 = 0;
    env->g0 = 0;
    env->b0 = 0;
    env->dtd = 1;
    if (videoMode == 0) {
        env->dfe = h < 0x101;
    } else {
        env->dfe = h < 0x121;
    }
    env->tw.x = 0;
    env->tw.y = 0;
    env->tw.w = 0;
    env->tw.h = 0;
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    env->tpage = 10;
    env->isbg = 0;
    return env;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDefDrawEnv);
#endif

DISPENV* SetDefDispEnv(DISPENV* env, s32 x, s32 y, s32 w, s32 h) {
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDumpFnt);

INCLUDE_ASM("asm/nonmatchings/psxsdk", FntLoad);

INCLUDE_ASM("asm/nonmatchings/psxsdk", FntOpen);

INCLUDE_ASM("asm/nonmatchings/psxsdk", FntFlush);

INCLUDE_ASM("asm/nonmatchings/psxsdk", FntPrint);

INCLUDE_ASM("asm/nonmatchings/psxsdk", GetTPage);

u16 GetClut(s32 x, s32 y) { return getClut(x, y); }

typedef int (*DebugPrintf)(const char *, ...);
extern u32 D_8009DA8C[];
extern char D_80090548[];

#ifdef NON_MATCHING
/* Retail's second branch computes ((tpage * 0x10) & 0x100) +
 * ((tpage >> 2) & 0x200) — an extra OR'd term absent from the sotn-decomp
 * source (different Psy-Q revision). Also gcc cross-jumps the two indirect
 * call tails, which retail keeps separate. */
void DumpTPage(u_short tpage) {
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        ((DebugPrintf)D_8009DA8C[0])(D_80090548, (tpage >> 9) & 3,
                                     (tpage >> 7) & 3, (tpage << 6) & 0x7C0,
                                     (tpage * 8) & 0x300);
        return;
    }
    ((DebugPrintf)D_8009DA8C[0])(D_80090548, (tpage >> 7) & 3,
                                 (tpage >> 5) & 3, (tpage << 6) & 0x7C0,
                                 (tpage * 0x10) & 0x100);
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", DumpTPage);
#endif

typedef int (*DebugPrintf)(const char *, ...);
extern u32 D_8009DA8C[];
extern char D_80090560[];

void DumpClut(u_short clut) {
    ((DebugPrintf)D_8009DA8C[0])(D_80090560, (clut & 0x3F) * 0x10, clut >> 6);
}

void* NextPrim(void* p) { return nextPrim(p); }

int IsEndPrim(void* p) { return isendprim(p); }

void AddPrim(void* ot, void* p) { addPrim(ot, p); }

void AddPrims(void* ot, void* p0, void* p1) { addPrims(ot, p0, p1); }

void CatPrim(void* p0, void* p1) { catPrim(p0, p1); }

void TermPrim(void* p) { return termPrim(p); }

void SetSemiTrans(void* p, int abe) { return setSemiTrans(p, abe); }

void SetShadeTex(void* p, int tge) { return setShadeTex(p, tge); }

void SetPolyF3(POLY_F3* p) { setPolyF3(p); }

void SetPolyFT3(POLY_FT3* p) { setPolyFT3(p); }

void SetPolyG3(POLY_G3* p) { setPolyG3(p); }

void SetPolyGT3(POLY_GT3* p) { setPolyGT3(p); }

void SetPolyF4(POLY_F4* p) { setPolyF4(p); }

void SetPolyFT4(POLY_FT4* p) { setPolyFT4(p); }

void SetPolyG4(POLY_G4* p) { setPolyG4(p); }

void SetPolyGT4(POLY_GT4* p) { setPolyGT4(p); }

void SetSprt8(SPRT_8* p) { setSprt8(p); }

void SetSprt16(SPRT_16* p) { setSprt16(p); }

void SetSprt(SPRT* p) { setSprt(p); }

void SetTile1(TILE_1* p) { setTile1(p); }

void SetTile8(TILE_8* p) { setTile8(p); }

void SetTile16(TILE_16* p) { setTile16(p); }

void SetTile(TILE* p) { setTile(p); }

void SetLineF2(LINE_F2* p) { setLineF2(p); }

void SetLineG2(LINE_G2* p) { setLineG2(p); }

void SetLineF3(LINE_F3* p) { setLineF3(p); }

void SetLineG3(LINE_G3* p) { setLineG3(p); }

void SetLineF4(LINE_F4* p) { setLineF4(p); }

void SetLineG4(LINE_G4* p) { setLineG4(p); }

void SetBlockFill(BLK_FILL* p) { setBlockFill(p); }

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawMove);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawTPage);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawLoad);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MargePrim);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DumpDrawEnv);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DumpDispEnv);

INCLUDE_ASM("asm/nonmatchings/psxsdk", ResetGraph);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetGraphReverse);

#ifdef NON_MATCHING
/* SPDX-License-Identifier: MIT */

typedef int (*DebugPrintf)(const char *, ...);
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
        ((DebugPrintf)D_8009DA8C[0])(D_80090698, debug[0],
                                     D_8009DA90[0], D_8009DA93[0]);
    }
    return old;
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SetGraphDebug);
#endif

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetGraphQueue);

extern u8 D_8009DA90[];

int GetGraphType(void) { return D_8009DA90[0]; }

extern u8 D_8009DA92[];

int GetGraphDebug(void) { return D_8009DA92[0]; }

INCLUDE_ASM("asm/nonmatchings/psxsdk", DrawSyncCallback);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDispMask);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DrawSync);

INCLUDE_ASM("asm/nonmatchings/psxsdk", checkRECT);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", GetDrawEnv);

INCLUDE_ASM("asm/nonmatchings/psxsdk", PutDispEnv);

INCLUDE_ASM("asm/nonmatchings/psxsdk", GetDispEnv);

INCLUDE_ASM("asm/nonmatchings/psxsdk", GetODE);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetTexWindow);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawArea);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawOffset);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetPriority);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawMode);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SetDrawEnv);

INCLUDE_ASM("asm/nonmatchings/psxsdk", get_mode);

INCLUDE_ASM("asm/nonmatchings/psxsdk", get_cs);

INCLUDE_ASM("asm/nonmatchings/psxsdk", get_ce);

INCLUDE_ASM("asm/nonmatchings/psxsdk", get_ofs);

INCLUDE_ASM("asm/nonmatchings/psxsdk", get_tw);

INCLUDE_ASM("asm/nonmatchings/psxsdk", get_dx);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _status);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _otc);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _clr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _dws);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _drs);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _ctl);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _getctl);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _cwb);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _cwc);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _param);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _addque);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _addque2);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _exeque);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _reset);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _sync);

INCLUDE_ASM("asm/nonmatchings/psxsdk", set_alarm);

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
        SpuVmKeyOn(access | (sequence << 8), score->unk4C, score->programs[channel], note & 0xFF, volume, pan);
        score->unkA8 = volume;
    } else {
        SpuVmKeyOff(access | (sequence << 8), score->unk4C, score->programs[channel], note & 0xFF);
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsSetControlChange);

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
    SpuVmPitchBend((sequence << 8) | access, score->unk4C, score->programs[channel], *data);
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", func_80080728);

INCLUDE_ASM("asm/nonmatchings/psxsdk", func_80080758);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _SsStart);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsStart);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsStart2);

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", func_8008134C);

/* SPDX-License-Identifier: MIT */
void _SsSndReplay(s16 access, s16 sequence) {
    D_800BDE3C[access][sequence].unk2B = 1;
    D_800BDE3C[access][sequence].unk90 &= ~8;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsSetTickMode);

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
        SpuVmSetSeqVol(access | (sequence << 8), score->leftVolume, score->rightVolume, 0);
    } else if (mode == 0) {
        D_800BDE3C[access][sequence].unk90 |= 2;
    }
}

extern void Snd_SetPlayMode(short, short, unsigned char, short);

void SsSeqPlay(short seq_access_num, char play_mode, short l_count) {
    Snd_SetPlayMode(seq_access_num, 0, play_mode, l_count);
}

extern void Snd_SetPlayMode(short, short, unsigned char, short);

void SsSepPlay(short sep_access_num, short seq_num, char play_mode, short l_count) {
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
    SpuVmSetSeqVol(sep_access_num | (seq_num << 8), voll & 0xFFFF, volr & 0xFFFF, 0);
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
void SsSetMono(void) { D_800B1EA4[0] = 1; }

extern short D_800B1EA4[];
void SsSetStereo(void) { D_800B1EA4[0] = 0; }

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabClose);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabOpen);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabOpenHead);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabOpenHeadSticky);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabFakeHead);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabOpenHeadWithMode);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabTransBody);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsVabTransCompleted);

INCLUDE_ASM("asm/nonmatchings/psxsdk", func_80082670);

/* SPDX-License-Identifier: MIT */
extern s16 D_800AFD98[];
void SpuVmDamperOn(void) { D_800AFD98[0] = 2; }

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtGetProgAtr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmVSetUp);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtGetVagAtr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtSetReverbType);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtGetReverbType);

INCLUDE_ASM("asm/nonmatchings/psxsdk", func_80082B50);

INCLUDE_ASM("asm/nonmatchings/psxsdk", func_80082B70);

extern SpuReverbAttr D_800AE27C[];

void SsUtSetReverbFeedback(short feedback) {
    D_800AE27C[0].mask = SPU_REV_FEEDBACK;
    D_800AE27C[0].feedback = feedback;
    SpuSetReverbModeParam(D_800AE27C);
}

#ifdef NON_MATCHING
/* Registers only: the /127 magic constant lands in v0 instead of v1 and
 * the two products shift one register down. Instruction sequence is
 * otherwise identical. decomp-permuter candidate. */
void SsUtSetReverbDepth(short ldepth, short rdepth) {
    D_800AE27C[0].mask = 6;
    D_800AE27C[0].depth.left = (ldepth * 0x7FFF) / 127;
    D_800AE27C[0].depth.right = (rdepth * 0x7FFF) / 127;
    SpuSetReverbModeParam(D_800AE27C);
}
#else
INCLUDE_ASM("asm/nonmatchings/psxsdk", SsUtSetReverbDepth);
#endif

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

void SsUtVibrateOn(void) {}

void SsUtVibrateOff(void) {}

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuVmSeKeyOff);

void KeyOnCheck(void) {}

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

INCLUDE_ASM("asm/nonmatchings/psxsdk", func_80087CC0);

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

void _SpuDataCallback(void (*arg0)()) { DMACallback(4, arg0); }

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuQuit);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetMute);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuInitMalloc);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuMalloc);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_gcSPU);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuFree);

void _SpuSetAnyVoice(s32, u32, s32, s32);
void SpuSetNoiseVoice(s32 a, s32 b) { _SpuSetAnyVoice(a, b, 0xCA, 0xCB); }

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
        if (arg0 < (D_800A270C[0][i].addr & 0x0FFFFFFF) + D_800A270C[0][i].size) {
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
        if (arg0 < (D_800A270C[0][i].addr & 0x0FFFFFFF) + D_800A270C[0][i].size) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetReverbModeParam);

INCLUDE_ASM("asm/nonmatchings/psxsdk", _spu_setReverbAttr);

INCLUDE_ASM("asm/nonmatchings/psxsdk", SpuSetReverbVoice);

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

void _SpuCallback(s32 arg0) { InterruptCallback(9, arg0); }

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
s32 _spu_getInTransfer(void) { return D_800A26DC[0] == 0; }

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

void* memmove(u8* dest, u8* src, int count) {
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

INCLUDE_ASM("asm/nonmatchings/psxsdk", DecDCTBufSize);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DecDCTin);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DecDCTout);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DecDCTinSync);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DecDCToutSync);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DecDCTinCallback);

INCLUDE_ASM("asm/nonmatchings/psxsdk", DecDCToutCallback);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MDEC_reset);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MDEC_in);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MDEC_out);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MDEC_in_sync);

INCLUDE_ASM("asm/nonmatchings/psxsdk", MDEC_out_sync);

INCLUDE_ASM("asm/nonmatchings/psxsdk", timeout);

INCLUDE_ASM("asm/nonmatchings/psxsdk", D_8008CA04);
