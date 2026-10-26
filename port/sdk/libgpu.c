/*
 * Psy-Q libgpu for the port: environments and ordering tables behave as
 * on the console, with no drawing. Every other function logs its first
 * call and returns 0.
 */
#include "host.h"
#include <psxsdk/libgpu.h>

s32 sprintf(char *, char *, ...);

void AddPrim(void *ot, void *p)
{
    u32 *tag = ot, *prim = p;

    *prim = (*prim & 0xFF000000) | (*tag & 0xFFFFFF);
    *tag = (*tag & 0xFF000000) | ((u32)prim & 0xFFFFFF);
}

/* Links each entry to the one before it; ot[0] ends at libgpu's own packet. */
OT_TYPE *ClearOTagR(OT_TYPE *ot, int n)
{
    extern u8 D_8009DB4C[];
    u32 *words = (u32 *)ot;

    while (--n > 0) {
        words[n] = (u32)&words[n - 1] & 0xFFFFFF;
    }
    words[0] = (u32)D_8009DB4C & 0xFFFFFF;
    return ot;
}

/* Walks the list as the GPU's DMA would, and logs its packet count. */
void DrawOTag(OT_TYPE *p)
{
    char line[48];
    u32 link = (u32)p & 0xFFFFFF;
    int packets = 0, guard = 1 << 20;

    while (link != 0xFFFFFF && --guard) {
        u32 tag = *(u32 *)(link | 0x80000000);

        packets += (tag >> 24) != 0;
        link = tag & 0xFFFFFF;
    }
    sprintf(line, guard ? "DrawOTag: %d packets" : "DrawOTag: cycle after %d packets", packets);
    HostLog(line);
}

void DrawPrim(s32 arg0)
{
    PORT_STUB(DrawPrim);
}

int DrawSync(int mode)
{
    return 0;
}

u_long DrawSyncCallback(void (*func)())
{
    PORT_STUB(DrawSyncCallback);
    return 0;
}

u_long* FntFlush(int id)
{
    PORT_STUB(FntFlush);
    return 0;
}

void FntLoad(int tx, int ty)
{
    PORT_STUB(FntLoad);
}

int FntOpen(int x, int y, int w, int h, int isbg, int n)
{
    PORT_STUB(FntOpen);
    return 0;
}

int FntPrint(const char* fmt, ...)
{
    PORT_STUB(FntPrint);
    return 0;
}

u_short GetClut(int x, int y)
{
    PORT_STUB(GetClut);
    return 0;
}

u_short GetTPage(int tp, int abr, int x, int y)
{
    PORT_STUB(GetTPage);
    return 0;
}

int LoadImage(RECT* rect, u_long* p)
{
    PORT_STUB(LoadImage);
    return 0;
}

int MoveImage(RECT* rect, int x, int y)
{
    PORT_STUB(MoveImage);
    return 0;
}

DISPENV *PutDispEnv(DISPENV *env)
{
    return env;
}

DRAWENV *PutDrawEnv(DRAWENV *env)
{
    return env;
}

int ResetGraph(int mode)
{
    return 0;
}

DISPENV *SetDefDispEnv(DISPENV *env, int x, int y, int w, int h)
{
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

/* As Psy-Q in NTSC mode (GetVideoMode() == 0). */
DRAWENV *SetDefDrawEnv(DRAWENV *env, int x, int y, int w, int h)
{
    env->clip.x = x;
    env->clip.y = y;
    env->clip.w = w;
    env->clip.h = h;
    env->tw.x = 0;
    env->tw.y = 0;
    env->tw.w = 0;
    env->tw.h = 0;
    env->r0 = 0;
    env->g0 = 0;
    env->b0 = 0;
    env->dtd = 1;
    env->dfe = h < 0x101;
    env->ofs[0] = x;
    env->ofs[1] = y;
    env->tpage = 10;
    env->isbg = 0;
    return env;
}

void SetDispMask(int mask)
{
}

void SetDrawEnv(DR_ENV* dr_env, DRAWENV* env)
{
    PORT_STUB(SetDrawEnv);
}

int SetGraphDebug(int level)
{
    PORT_STUB(SetGraphDebug);
    return 0;
}

void SetLineF2(s32 arg0)
{
    PORT_STUB(SetLineF2);
}

void SetLineF4(s32 arg0)
{
    PORT_STUB(SetLineF4);
}

void SetPolyF3(s32 arg0)
{
    PORT_STUB(SetPolyF3);
}

void SetPolyF4(s32 arg0)
{
    PORT_STUB(SetPolyF4);
}

void SetPolyFT3(s32 arg0)
{
    PORT_STUB(SetPolyFT3);
}

void SetPolyFT4(s32 arg0)
{
    PORT_STUB(SetPolyFT4);
}

void SetPolyGT4(POLY_GT4* p)
{
    PORT_STUB(SetPolyGT4);
}

void SetSemiTrans(void* p, int abe)
{
    PORT_STUB(SetSemiTrans);
}

void SetShadeTex(void* p, int tge)
{
    PORT_STUB(SetShadeTex);
}

void SetTile(TILE* p)
{
    PORT_STUB(SetTile);
}

int StoreImage(RECT* rect, u_long* p)
{
    PORT_STUB(StoreImage);
    return 0;
}
