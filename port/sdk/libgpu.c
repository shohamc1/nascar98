/*
 * Psy-Q libgpu for the port. Environments and ordering tables behave as
 * on the console; drawing and VRAM transfers go to the host's GPU
 * (port/host/gpu.c). The debug font and callbacks log their first call
 * and return 0.
 */
#include "host.h"
#include <psxsdk/libgpu.h>

/* Writes a primitive's length (in words after the tag) and its code. */
static void SetLenCode(void *p, int len, int code)
{
    ((u8 *)p)[3] = len;
    ((u8 *)p)[7] = code;
}

void AddPrim(void *ot, void *p)
{
    u32 *tag = ot, *prim = p;

    PORT_TRACE(AddPrim);
    *prim = (*prim & 0xFF000000) | (*tag & 0xFFFFFF);
    *tag = (*tag & 0xFF000000) | ((u32)prim & 0xFFFFFF);
}

/* Links each entry to the one before it; ot[0] ends at libgpu's own packet. */
OT_TYPE *ClearOTagR(OT_TYPE *ot, int n)
{
    extern u8 D_8009DB4C[];
    u32 *words = (u32 *)ot;

    PORT_TRACE(ClearOTagR);
    while (--n > 0) {
        words[n] = (u32)&words[n - 1] & 0xFFFFFF;
    }
    words[0] = (u32)D_8009DB4C & 0xFFFFFF;
    return ot;
}

/* Walks the list as the GPU's DMA would, and logs its packet count. */
void DrawOTag(OT_TYPE *p)
{
    PORT_TRACE(DrawOTag);
    HostGpuDrawOTag(p);
}

void DrawPrim(s32 arg0)
{
    PORT_TRACE(DrawPrim);
    HostGpuDrawPrim((void *)arg0);
}

int DrawSync(int mode)
{
    PORT_TRACE(DrawSync);

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
    return (u_short)(y << 6 | ((x >> 4) & 0x3F));
}

u_short GetTPage(int tp, int abr, int x, int y)
{
    return (u_short)((tp & 3) << 7 | (abr & 3) << 5 | (y & 0x100) >> 4 | (x & 0x3FF) >> 6 | (y & 0x200) << 2);
}

int LoadImage(RECT *rect, u_long *p)
{
    PORT_TRACE(LoadImage);
    HostGpuLoadImage(rect, p);
    return 0;
}

int MoveImage(RECT *rect, int x, int y)
{
    PORT_TRACE(MoveImage);
    HostGpuMoveImage(rect, x, y);
    return 0;
}

DISPENV *PutDispEnv(DISPENV *env)
{
    PORT_TRACE(PutDispEnv);
    HostGpuSetDispEnv(env);
    return env;
}

/* As Psy-Q: the environment goes out as a DR_ENV packet, then isbg clears. */
DRAWENV *PutDrawEnv(DRAWENV *env)
{
    PORT_TRACE(PutDrawEnv);
    SetDrawEnv(&env->dr_env, env);
    HostGpuDrawPrim(&env->dr_env);
    if (env->isbg) {
        HostGpuClearImage(&env->clip, env->r0, env->g0, env->b0);
    }
    return env;
}

int ResetGraph(int mode)
{
    PORT_TRACE(ResetGraph);
    HostGpuReset();
    return 0;
}

DISPENV *SetDefDispEnv(DISPENV *env, int x, int y, int w, int h)
{
    PORT_TRACE(SetDefDispEnv);

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
    PORT_TRACE(SetDefDrawEnv);

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
    PORT_TRACE(SetDispMask);
}

void SetDrawEnv(DR_ENV *dr_env, DRAWENV *env)
{
    u32 *code = (u32 *)dr_env->code;
    int x1 = env->clip.x + env->clip.w - 1, y1 = env->clip.y + env->clip.h - 1;

    code[0] = 0xE3000000 | (env->clip.y & 0x3FF) << 10 | (env->clip.x & 0x3FF);
    code[1] = 0xE4000000 | (y1 & 0x3FF) << 10 | (x1 & 0x3FF);
    code[2] = 0xE5000000 | (env->ofs[1] & 0x7FF) << 11 | (env->ofs[0] & 0x7FF);
    code[3] = 0xE1000000 | env->tpage | env->dtd << 9 | env->dfe << 10;
    code[4] = 0xE2000000;
    SetLenCode(dr_env, 5, ((u8 *)dr_env)[7]);
}

int SetGraphDebug(int level)
{
    PORT_STUB(SetGraphDebug);
    return 0;
}

void SetLineF2(void *p)
{
    PORT_TRACE(SetLineF2);
    SetLenCode(p, 3, 0x40);
}

void SetLineF4(void *p)
{
    PORT_TRACE(SetLineF4);
    SetLenCode(p, 6, 0x4C);
    ((u32 *)p)[6] = 0x55555555; /* the polyline's terminator */
}

void SetPolyF3(void *p)
{
    PORT_TRACE(SetPolyF3);
    SetLenCode(p, 4, 0x20);
}

void SetPolyF4(void *p)
{
    PORT_TRACE(SetPolyF4);
    SetLenCode(p, 5, 0x28);
}

void SetPolyFT3(void *p)
{
    PORT_TRACE(SetPolyFT3);
    SetLenCode(p, 7, 0x24);
}

void SetPolyFT4(void *p)
{
    PORT_TRACE(SetPolyFT4);
    SetLenCode(p, 9, 0x2C);
}

void SetPolyGT4(POLY_GT4 * p)
{
    PORT_TRACE(SetPolyGT4);
    SetLenCode(p, 12, 0x3C);
}

void SetSemiTrans(void *p, int abe)
{
    u8 *code = (u8 *)p + 7;

    *code = abe ? *code | 2 : *code & ~2;
}

void SetShadeTex(void *p, int tge)
{
    u8 *code = (u8 *)p + 7;

    *code = tge ? *code | 1 : *code & ~1;
}

void SetTile(TILE * p)
{
    PORT_TRACE(SetTile);
    SetLenCode(p, 3, 0x60);
}

int StoreImage(RECT *rect, u_long *p)
{
    PORT_TRACE(StoreImage);
    HostGpuStoreImage(rect, p);
    return 0;
}
