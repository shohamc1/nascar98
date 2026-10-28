#include "common.h"
#include "libpress.h"
#include "fixed_addrs.h"
extern s32 D_800A367CAbsolute2[];
#include <psxsdk/libgpu.h>
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/libcd.h>
#include <psxsdk/libgte.h>
#include "gte.h"
#include <psxsdk/libapi.h>
#include <psxsdk/libspu.h>
#include <psxsdk/kernel.h>
#include "game.h"
#include "car.h"
#include "graphics.h"
#include "menu.h"
#include "objects.h"
#include "scene.h"
#include "sound.h"
#include "util.h"
extern s32 gOrderingTableAbsolute7[];
extern s32 gMenuObjectPoolAbsolute2[];
extern u8 gCardMenuMessageAbsolute2[];
extern s32 gOrderingTableBankAbsolute3[];
extern s32 gOrderingTableBankAbsolute4[];
extern s32 gOrderingTableAbsolute4[];
extern s32 gOrderingTableAbsolute5[];
extern s32 gOrderingTableAbsolute6[];
extern s32 D_800A2CE0Absolute3[];
extern s32 D_800A2CE0Absolute4[];
extern u8 gCardMenuMessageAbsoluteU8[] asm("gCardMenuMessageAbsolute");
extern s32 D_800A2EA8Absolute[];
extern u8 gMenuObjectPoolCountAbsolute[];
extern void SetPolyFT4(POLY_FT4 *);
extern u8 *D_800A3428View asm("D_800A3428");
void HudDrawTime(s32 time, s16 x, s16 y, s8 color, u8 mode);
void MenuLoadResources(void);
void GraphicsInitDoubleBufferSwapped(void);
void TextureLoadTim(void *timImage);
extern u8 gSoundEffectsEnabledw15[] asm("gSoundEffectsEnabled.NON_MATCHING");
extern s32 gOrderingTable[];
extern s32 *gSinTableAbsolute[];
extern u8 D_800A3680[];
extern Car *gPlayerCar[];
extern void HeapFree(void *ptr);
extern s32 D_800A37B4Absolute[];
extern void SetPolyF4(u8 *prim);
extern Car *D_800A35E0[];
extern void FileRead(s32 buffer, s32 size, s32 count, s32 handle);
extern u8 gCdAudioEnabledAbsolute[];
extern void SoundPlaySlot(s8, s8);
s32 VSync(s32);
extern u8 D_800A2EE0[];
void GraphicsDrawRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5,
                      u8 arg6, s32 arg7);
void func_80028FCC(Car *arg0);
void *FileOpen(s32 fileId, void *mode);
void FileClose(s32 handle);
s32 FileSeek(s32 handle, s32 offset, s32 whence);
void CdLoadFileByIndex(s32 arg0, s32 arg1);
void CdStopIfPlaybackChanged(void);
void CdStop(void);
void SoundReloadVabAndResetSlots(s32 arg0);
void func_80041564(Car *arg0, s32 arg1);
s32 PadTypeNeedsCalibration(s32 arg0);
void HeapResetInitFlag(void);
void GraphicsDrawDoubleBorderRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3,
                                  u8 arg4, u8 arg5, u8 arg6, u8 arg7);
extern Car *gCarListNM[] asm("gCarList.NON_MATCHING");
extern s32 *gCosTableAbsolute[];
extern s32 D_800A2F84[];
s32 CarGetTrackSide(Car *car, s16 offset);
extern u8 D_800A372C;
typedef struct {
    u16 tpx;
    u16 tpy;
    u16 clutX;
    u16 clutY;
    u8 u;
    u8 unk9;
    u8 v;
    u8 unkB;
    u16 tpage;
} SceneTexture;
extern u8 D_80090F32[];
extern u8 D_800A3424;
extern u8 D_800A38F0;
extern s32 gOrderingTableAbsolute[];
extern s16 D_800A3910;
extern s32 sprintfHud(char *, char *, ...) asm("sprintf");
extern void func_8004AFE0(s8, u16 *, u16 *);
extern void GraphicsSetColor(u8, u8, u8);
extern void HudDrawTextS16(char *, s32, s16, s32) asm("HudDrawText");
extern void SoundStopConditionalSlots(s8);
extern s8 D_800A2FD4[4];

typedef struct {
    u16 tpx;
    u16 tpy;
    u16 clutX;
    u16 clutY;
    u16 u;
    u16 v;
    u16 tpage;
} HudTexture;

extern u8 D_800A3680[1];
extern s8 D_800A2FD0[3];
extern u8 D_800A3484Small;
asm(".globl D_800A3484Small\nD_800A3484Small = D_800A3484");
extern s8 *D_8009AE2C[];

extern u8 D_8009AE14[];
extern Glyph gHudGlyphs[];
extern s8 *D_800A78CC[];
extern u16 D_800A78E2[];
extern u16 D_800A78EA[];
extern u8 D_800A78A8[];
extern u8 D_800A78A9[];
extern u8 D_800A78B0[];
extern u8 D_800A78B1[];
extern u8 D_800A78B8[];
extern u8 D_800A78B9[];
extern u8 D_800A78C0[];
extern u8 D_800A78C1[];
extern u16 D_800A78B2[];
extern HudTexture D_80090FEA[];
extern u16 D_80090FEC[];
extern u16 D_80090FEE[];
extern u16 D_80090FF0[];
extern u16 D_80090FF2[];
extern u16 D_80090FF4[];
extern u16 D_80090FF6[];

extern u16 D_800A7592[];

extern u8 D_800A7932[];
extern u8 D_800A7944[];
extern u8 D_800A798B[];
extern u16 D_800A798C[];
extern u16 D_800A798E[];
extern u16 D_800A7990[];
extern u16 D_800A7992[];
extern u8 D_800A7564[];
extern u16 D_800B0B92[];
extern u16 D_80099298[];
extern void SetPolyFT4(POLY_FT4 *);
asm(".globl D_80090FF2a\nD_80090FF2a = D_80090FF2");
asm(".globl D_80090FF2b\nD_80090FF2b = D_80090FF2");
asm(".globl D_80090FF2c\nD_80090FF2c = D_80090FF2");
asm(".globl D_80090FF4a\nD_80090FF4a = D_80090FF4");
asm(".globl D_80090FF4b\nD_80090FF4b = D_80090FF4");
asm(".globl D_80090FF4c\nD_80090FF4c = D_80090FF4");
extern u16 D_80090FF2a[];
extern u16 D_80090FF2b[];
extern u16 D_80090FF2c[];
extern u16 D_80090FF4a[];
extern u16 D_80090FF4b[];
extern u16 D_80090FF4c[];

extern s32 gSinTableMap0[];
asm(".globl gSinTableMap0\ngSinTableMap0 = gSinTable");
extern s32 gSinTableMap1[];
asm(".globl gSinTableMap1\ngSinTableMap1 = gSinTable");
extern s32 gSinTableMap2[];
asm(".globl gSinTableMap2\ngSinTableMap2 = gSinTable");
extern s32 gSinTableMap3[];
asm(".globl gSinTableMap3\ngSinTableMap3 = gSinTable");

extern u8 D_800A798BWrite[];
asm(".globl D_800A798BWrite\nD_800A798BWrite = D_800A798B");

/* Keep address construction separate from the primitive stores. */
#ifdef NATIVE
void HudInitRacePrims(void);
#else
void HudInitRacePrims(void);
#endif
extern s8 D_800A2FD0[];

/* The `(u32)index + (u32)base` casts give retail's index-first `addu`
 * operands. The block-local row load and the `asm volatile` barrier keep
 * the row-pointer and pad-byte loads ahead of the x and y loads. */
void func_8004AFE0(s8 arg0, u16 *arg1, u16 *arg2);

void func_8004B128(Car *arg0);

/* These calls keep the preceding result in the delay slot. */
extern void HudMultiplyVoid(s32, s32) asm("MathMultiplyFixed16");
extern u32 gHudPrimitiveCursor asm("gPrimitiveCursorAbsolute");
extern u8 D_800A8184[], D_800A81B4[], D_800A82B4[];
extern POLY_FT4 D_800A8214[];
extern u8 D_800A80F4[], D_800A8354[], D_800A8534[], D_800A7995[];
extern u16 D_8009934C[], D_8009934E[];
extern s16 D_8009935C[], D_8009936C[];
extern s16 D_800A3008;
extern SVECTOR D_800A3004[];
extern MATRIX D_800A7FC4[];
extern u16 D_800A3494;
extern u8 D_800A2FD8[];
extern u8 D_800A2FDC[];
extern s16 D_800A853C[], D_800A8544[], D_800A854C[], D_800A854E[];
extern s16 D_800A8554[], D_800A8556[];

#ifdef NATIVE
void HudDrawDashboard(void);
#else
void HudDrawDashboard(void);
#endif

typedef struct {
    u16 tpx;
    u16 tpy;
    u16 clutX;
    u16 clutY;
    u16 u;
    u16 v;
    u16 tpage;
} SceneTexInfo;

typedef struct {
    s16 a[3];
} SceneRotTable;
typedef struct {
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} SceneSeg;
typedef struct {
    SceneSeg s[3];
} SceneQuadTable;
typedef struct {
    s16 x;
    s16 y;
} ScenePt;
typedef struct {
    u16 x;
    u16 y;
} ScenePt16;
typedef struct {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} SceneVert;
typedef struct {
    ScenePt p[4];
} ScenePairTable;
typedef struct {
    s16 a[4];
} SceneTailTable;

extern SceneTexInfo D_80090FCE[];
extern SceneTexInfo D_80091014;
extern SceneRotTable D_800A300C[];
static const SceneQuadTable sHudQuadCoords = {
    {{220, 50, 235, 50}, {319, 32, 319, 59}, {319, 128, 319, 135}}};
static const ScenePairTable sHudCornerOffsets = {
    {{0, 5}, {55, 5}, {0, -5}, {55, -5}}};
static const char sHudCaptionFormat[] = "%s %s %s";
static const char sHudTimeInvalidText[] = "--:--:---";
static const char sHudTimeFormatHms[] = "%02d:%02d:%02d";
static const char sHudTimeFormatMinSecMs[] = "%02d:%02d:%03d";
extern SceneTailTable D_800A3014[];
extern u16 D_80090F28[];
extern u8 D_80090F30[];
extern u16 D_80091016[];
extern u16 D_80091018[];
extern u16 D_8009101A[];
extern u16 D_8009101C[];
extern u16 D_8009101E[];
extern u16 D_80091020[];
extern u8 D_800A7994[];
extern u8 D_800A799C[];
extern u8 D_800A799D[];
extern u8 D_800A799E[];
extern u8 D_800A79A0[];
extern u8 D_800A79A1[];
extern u8 D_800A79A2[];
extern u8 D_800A79A4[];
extern u8 D_800A79A5[];
extern u8 D_800A79A8[];
extern u8 D_800A79A9[];
extern u8 D_800A79AC[];
extern u8 D_800A79B0[];
extern u8 D_800A79B4[];
extern u8 D_800A79B8[];
extern u8 D_800A7F14[];
extern u8 D_800A7F18[];
extern u8 D_800A7F19[];
extern u8 D_800A7F1A[];
extern u8 D_800A7F1C[];
extern u8 D_800A7F1D[];
extern u8 D_800A7F20[];
extern u8 D_800A7F21[];
extern u16 D_800A7F22[];
extern u8 D_800A7F24[];
extern u8 D_800A7F25[];
extern u8 D_800A7F28[];
extern u8 D_800A7F29[];
extern s32 D_800A7FD8[];
extern s32 D_800A7FDC[];
extern s32 D_800A7FE0[];
extern ScenePt16 D_800A7FE4[];
extern u8 D_800A8188[];
extern u8 D_800A8189[];
extern u8 D_800A818A[];
extern s16 D_800A818C[];
extern s16 D_800A818E[];
extern s16 D_800A8190[];
extern s16 D_800A8192[];
extern s16 D_800A8194[];
extern s16 D_800A8196[];
extern s16 D_800A8198[];
extern s16 D_800A819A[];
extern u8 D_800A81A0[];
extern u8 D_800A81A1[];
extern u8 D_800A81A2[];
extern s16 D_800A81A4[];
extern s16 D_800A81A6[];
extern s16 D_800A81A8[];
extern s16 D_800A81AA[];
extern s16 D_800A81AC[];
extern s16 D_800A81AE[];
extern s16 D_800A81B0[];
extern s16 D_800A81B2[];
extern s16 D_800A821C[];
extern s16 D_800A821E[];
extern u8 D_800A8220[];
extern u8 D_800A8221[];
extern u8 D_800A8222[];
extern s16 D_800A8224[];
extern s16 D_800A8226[];
extern u8 D_800A8228[];
extern u8 D_800A8229[];
extern u8 D_800A822A[];
extern s16 D_800A822C[];
extern s16 D_800A822E[];
extern u8 D_800A8230[];
extern u8 D_800A8231[];
extern s16 D_800A8234[];
extern s16 D_800A8236[];
extern u8 D_800A8238[];
extern u8 D_800A8239[];
extern s16 D_800A82BC[];
extern s16 D_800A82BE[];
extern u8 D_800A82C0[];
extern u8 D_800A82C1[];
extern u16 D_800A82C2[];
extern s16 D_800A82C4[];
extern s16 D_800A82C6[];
extern u8 D_800A82C8[];
extern u8 D_800A82C9[];
extern u16 D_800A82CA[];
extern s16 D_800A82CC[];
extern s16 D_800A82CE[];
extern u8 D_800A82D0[];
extern u8 D_800A82D1[];
extern s16 D_800A82D4[];
extern s16 D_800A82D6[];
extern u8 D_800A82D8[];
extern u8 D_800A82D9[];
extern s16 D_800A8334[];
extern s16 D_800A8336[];
extern s16 D_800A833C[];
extern s16 D_800A833E[];
extern s16 D_800A8344[];
extern s16 D_800A8346[];
extern s16 D_800A834C[];
extern s16 D_800A834E[];
extern u8 D_800A8362[];
extern u8 D_800A836A[];
extern u8 D_800A83DA[];
extern u8 D_800A83E2[];
extern u8 D_800A8402[];
extern u8 D_800A840A[];
extern u8 D_800A842A[];
extern u8 D_800A8432[];
extern u8 D_800A853E[];
extern u8 D_800A854A[];
extern SceneVert D_800A85AC[][4];
extern s16 D_800A89AC[];
extern s16 D_800A89AE[];
extern s16 D_800A89B4[];
extern s16 D_800A89B6[];
extern s16 D_800A89BC[];
extern s16 D_800A89BE[];
extern s16 D_800A89C4[];
extern s16 D_800A89C6[];

extern s32 gCosTableSmall[];
extern s32 gSinTableSmall[];

void HudInitPrims(void) {
    SceneTexInfo *tex;
    s32 idx;
    s32 rowOff;
    SceneRotTable rot;
    SceneQuadTable quads;
    ScenePairTable corners;
    SceneTailTable tail;
    POLY_FT4 *prim2;
    POLY_F4 *prim3;
    POLY_FT4 *p0;
    POLY_FT4 *p1;
    POLY_FT4 *p2;
    POLY_FT4 *p3;
    POLY_FT4 *p4;
    POLY_FT4 *p5;
    u8 *f4base;
    u16 *primC;
    POLY_FT4 *poly;
    u16 u;
    u16 v;
    u16 u2;
    u16 v2;
    u8 u3;
    u8 v3;
    s8 i;
    s8 j;
    s8 k;
    s32 matA;
    s32 matB;
    s16 yv;
    s32 xl;
    s32 xa;
    s32 xb;

    rot = D_800A300C[0];
    quads = sHudQuadCoords;
    corners = sHudCornerOffsets;
    tail = D_800A3014[0];
    D_800A2FD4[0] = -(gSplitScreenMode[0] != 0) & -0x28;
    for (i = 0; i < D_800A3424; i++) {
        tex = D_80090FCE;
        for (j = 0; j < 6; j++) {
            s32 rowOff;
            s32 tmp;
            POLY_FT4 *prim;
            s32 idx;
            rowOff = i * 0xF0;
            idx = j * 0x28;
            tmp = idx + (s32)D_800A8354;
            prim = (POLY_FT4 *)((u8 *)(rowOff + tmp));
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            idx += rowOff;
            *(u16 *)(D_800A8362 + idx) = GetClut(tex->clutX, tex->clutY);
            *(u16 *)(D_800A836A + idx) =
                GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
            prim2 = (POLY_FT4 *)(idx + D_800A8354);
            prim2->u0 = tex->u;
            prim2->v0 = tex->v;
            prim2->u1 = tex->u + 0x50;
            prim2->v1 = tex->v;
            prim2->u2 = tex->u;
            prim2->v2 = tex->v + 0x33;
            prim2->u3 = tex->u + 0x50;
            prim2->v3 = tex->v + 0x33;
        }
        p0 = (POLY_FT4 *)(i * 0xF0 + D_800A8354);
        p0->x0 = 0x11C;
        p0->y0 = D_800A2FD4[i];
        p0->x1 = 0x16C;
        p0->y1 = D_800A2FD4[i];
        p0->x2 = 0x11C;
        p0->y2 = D_800A2FD4[i] + 0x33;
        p0->x3 = 0x16C;
        p0->y3 = D_800A2FD4[i] + 0x33;
        p1 = (POLY_FT4 *)(i * 0xF0 + (D_800A8354 + 0x28));
        p1->x0 = 0xCC;
        p1->y0 = D_800A2FD4[i];
        p1->x1 = 0x11C;
        p1->y1 = D_800A2FD4[i];
        p1->x2 = 0xCC;
        p1->y2 = D_800A2FD4[i] + 0x33;
        p1->x3 = 0x11C;
        p1->y3 = D_800A2FD4[i] + 0x33;
        p2 = (POLY_FT4 *)(i * 0xF0 + (D_800A8354 + 0x50));
        p2->x0 = 0x7C;
        p2->y0 = D_800A2FD4[i];
        p2->x1 = 0xCC;
        p2->y1 = D_800A2FD4[i];
        p2->x2 = 0x7C;
        p2->y2 = D_800A2FD4[i] + 0x33;
        p2->x3 = 0xCC;
        p2->y3 = D_800A2FD4[i] + 0x33;
        tex = &D_80090FCE[1];
        *(u16 *)(D_800A83DA + i * 0xF0) = GetClut(tex->clutX, tex->clutY);
        *(u16 *)(D_800A83E2 + i * 0xF0) =
            GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
        p3 = (POLY_FT4 *)(i * 0xF0 + (D_800A8354 + 0x78));
        p3->u0 = tex->u;
        p3->v0 = tex->v;
        p3->u1 = tex->u + 0x7C;
        p3->v1 = tex->v;
        p3->u2 = tex->u;
        p3->v2 = tex->v + 0x3B;
        p3->u3 = tex->u + 0x7C;
        p3->v3 = tex->v + 0x3B;
        p3->x0 = 0;
        p3->y0 = D_800A2FD4[i];
        p3->x1 = 0x7C;
        p3->y1 = D_800A2FD4[i];
        p3->x2 = 0;
        p3->y2 = D_800A2FD4[i] + 0x3B;
        p3->x3 = 0x7C;
        p3->y3 = D_800A2FD4[i] + 0x3B;
        tex += 5;
        *(u16 *)(D_800A8402 + i * 0xF0) = GetClut(tex->clutX, tex->clutY);
        *(u16 *)(D_800A840A + i * 0xF0) =
            GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
        p4 = (POLY_FT4 *)(i * 0xF0 + (D_800A8354 + 0xA0));
        p4->u0 = tex->u;
        p4->v0 = tex->v + 0x4B;
        p4->u1 = tex->u;
        p4->v1 = tex->v;
        p4->u2 = tex->u + 0xB1;
        p4->v2 = tex->v + 0x4B;
        p4->u3 = tex->u + 0xB1;
        p4->v3 = tex->v;
        p4->x0 = 0;
        p4->y0 = D_800A2FD4[i] + 0x3B;
        p4->x1 = 0x4C;
        p4->y1 = D_800A2FD4[i] + 0x3B;
        p4->x2 = 0;
        p4->y2 = D_800A2FD4[i] + 0xEC;
        p4->x3 = 0x4C;
        p4->y3 = D_800A2FD4[i] + 0xEC;
        tex -= 17;
        *(u16 *)(D_800A842A + i * 0xF0) = GetClut(tex->clutX, tex->clutY);
        *(u16 *)(D_800A8432 + i * 0xF0) =
            GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
        p5 = (POLY_FT4 *)(i * 0xF0 + (D_800A8354 + 0xC8));
        p5->u0 = tex->u;
        p5->v0 = tex->v;
        p5->u1 = tex->u + 0xF4;
        p5->v1 = tex->v;
        p5->u2 = tex->u;
        p5->v2 = tex->v + 0x12;
        p5->u3 = tex->u + 0xF4;
        p5->v3 = tex->v + 0x12;
        p5->x0 = 0x4C;
        p5->y0 = D_800A2FD4[i] + 0x9A;
        p5->x1 = 0x140;
        p5->y1 = D_800A2FD4[i] + 0x9A;
        p5->x2 = 0x4C;
        p5->y2 = D_800A2FD4[i] + 0xAC;
        p5->x3 = 0x140;
        p5->y3 = D_800A2FD4[i] + 0xAC;
        f4base = D_800A80F4;
        for (j = 0; j < 3; j++) {
            POLY_FT4 *prim;
            POLY_F4 *prim3;
            s32 t;
            s32 t2;
            t = j * 0x18 + (s32)f4base;
            prim = (POLY_FT4 *)((u8 *)(i * 0x48 + t));
            SetPolyF4((POLY_F4 *)prim);
            t2 = i * 0x48 + j * 0x18;
            prim3 = (POLY_F4 *)((u8 *)(t2 + (s32)f4base));
            prim3->r0 = 8;
            prim3->g0 = 8;
            prim3->b0 = 8;
            prim3->x0 = quads.s[j].x0;
            prim3->y0 = quads.s[j].y0 + D_800A2FD4[i];
            prim3->x1 = quads.s[j].x1;
            prim3->y1 = quads.s[j].y1 + D_800A2FD4[i];
            prim3->x2 = *(u16 *)(D_800A2FDC + j * 2) - (s8)D_800A2FD8[j];
            prim3->y2 = D_800A2FD4[i] + 0x9E;
            prim3->x3 = *(u16 *)(D_800A2FDC + j * 2) + (s8)D_800A2FD8[j];
            prim3->y3 = D_800A2FD4[i] + 0x9E;
        }
    }
    if (gSplitScreenMode[0] == 0) {
        tex = &D_80090FCE[4];
        for (i = 0; i < 4; i++) {
            POLY_FT4 *prim;
            prim = &D_800A8214[i];
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            *(u16 *)(D_800A8222 + i * 0x28) = GetClut(tex->clutX, tex->clutY);
            *(u16 *)(D_800A822A + i * 0x28) =
                GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
            prim->u0 = tex->u;
            prim->v0 = tex->v;
            prim->u1 = tex->u + 0x30;
            prim->v1 = tex->v;
            prim->u2 = tex->u;
            prim->v2 = tex->v + 0x40;
            prim->u3 = tex->u + 0x30;
            prim->v3 = tex->v + 0x40;
        }
        D_800A8214[0].clut = GetClut(D_80091018[0], D_8009101A[0]);
        D_800A8214[0].tpage =
            GetTPage(D_80091020[0], 0, D_80091014.tpx, D_80091016[0]);
        u = D_8009101C[0];
        v = D_8009101E[0];
        D_800A8220[0] = u;
        D_800A8221[0] = v;
        D_800A8228[0] = u + 0x40;
        D_800A8229[0] = v;
        D_800A8230[0] = u;
        D_800A8231[0] = v + 0x40;
        D_800A8238[0] = u + 0x40;
        D_800A8239[0] = v + 0x40;
        D_800A821C[0] = 0x7C;
        D_800A821E[0] = D_800A2FD4[0] + 0xAC;
        D_800A8224[0] = 0xBC;
        D_800A8226[0] = D_800A2FD4[0] + 0xAC;
        D_800A822C[0] = 0x7C;
        D_800A822E[0] = D_800A2FD4[0] + 0xEC;
        D_800A8234[0] = 0xBC;
        D_800A8236[0] = D_800A2FD4[0] + 0xEC;
        D_800A8214[1].x0 = 0x3C;
        D_800A8214[1].y0 = D_800A2FD4[0] + 0xAC;
        D_800A8214[1].x1 = 0x6C;
        D_800A8214[1].y1 = D_800A2FD4[0] + 0xAC;
        D_800A8214[1].x2 = 0x3C;
        D_800A8214[1].y2 = D_800A2FD4[0] + 0xEC;
        D_800A8214[1].x3 = 0x6C;
        D_800A8214[1].y3 = D_800A2FD4[0] + 0xEC;
        D_800A8214[2].x0 = 0xE0;
        D_800A8214[2].y0 = D_800A2FD4[0] + 0xAC;
        D_800A8214[2].x1 = 0x110;
        D_800A8214[2].y1 = D_800A2FD4[0] + 0xAC;
        D_800A8214[2].x2 = 0xE0;
        D_800A8214[2].y2 = D_800A2FD4[0] + 0xEC;
        D_800A8214[2].x3 = 0x110;
        D_800A8214[2].y3 = D_800A2FD4[0] + 0xEC;
        D_800A8214[3].x0 = 0x110;
        D_800A8214[3].y0 = D_800A2FD4[0] + 0xAC;
        D_800A8214[3].x1 = 0x140;
        D_800A8214[3].y1 = D_800A2FD4[0] + 0xAC;
        D_800A8214[3].x2 = 0x110;
        D_800A8214[3].y2 = D_800A2FD4[0] + 0xEC;
        D_800A8214[3].x3 = 0x140;
        D_800A8214[3].y3 = D_800A2FD4[0] + 0xEC;
        for (i = 0; i < 4; i++) {
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(i * 0x28 + D_800A82B4);
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
        }
        tex = &D_80091014;
        primC = D_800A82C2;
        j = 0;
        primC[0] = GetClut(D_80091014.clutX, D_80091014.clutY);
        D_800A82CA[0] = GetTPage(D_80091014.tpage, 0, tex->tpx, D_80091014.tpy);
        u2 = D_8009101C[0];
        poly = (POLY_FT4 *)((u8 *)primC + 0x1A);
        tex++;
        v2 = D_8009101E[0];
        D_800A82C0[0] = u2;
        D_800A82C1[0] = v2;
        D_800A82C8[0] = u2 + 1;
        D_800A82C9[0] = v2;
        D_800A82D0[0] = u2;
        D_800A82D1[0] = v2 + 0x40;
        D_800A82D8[0] = u2 + 1;
        D_800A82D9[0] = v2 + 0x40;
        D_800A82BC[0] = 0xBC;
        D_800A82BE[0] = D_800A2FD4[0] + 0xAC;
        D_800A82C4[0] = 0xC4;
        D_800A82C6[0] = D_800A2FD4[0] + 0xAC;
        D_800A82CC[0] = 0xBC;
        D_800A82CE[0] = D_800A2FD4[0] + 0xEC;
        D_800A82D4[0] = 0xC4;
        D_800A82D6[0] = D_800A2FD4[0] + 0xEC;
        for (; j < 3; j++) {
            POLY_FT4 *prim;
            s32 next;
            s32 idx;
            u16 clut;
            clut = GetClut(tex->clutX, tex->clutY);
            next = j + 1;
            idx = next * 0x28;
            *(u16 *)((u8 *)D_800A82C2 + idx) = clut;
            *(u16 *)((u8 *)D_800A82CA + idx) =
                GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
            prim = (POLY_FT4 *)((u8 *)(j * 0x28 + (s32)poly));
            prim->u0 = tex->u + 0x71;
            prim->v0 = tex->v + 0x10;
            prim->u1 = tex->u + 0x71;
            prim->v1 = tex->v;
            prim->u2 = tex->u + 0xB1;
            prim->v2 = tex->v + 0x10;
            prim->u3 = tex->u + 0xB1;
            prim->v3 = tex->v;
            prim->x0 = (j << 4) + 0xC0;
            prim->y0 = D_800A2FD4[0] + 0xAC;
            prim->x1 = (j << 4) + 0xD0;
            prim->y1 = D_800A2FD4[0] + 0xAC;
            prim->x2 = (j << 4) + 0xC0;
            prim->y2 = D_800A2FD4[0] + 0xEC;
            prim->x3 = (j << 4) + 0xD0;
            prim->y3 = D_800A2FD4[0] + 0xEC;
        }
        D_800A8334[0] = 0x6C;
        D_800A833C[0] = 0x7C;
        D_800A8344[0] = 0x6C;
        D_800A834C[0] = 0x7C;
        D_800A8336[0] = D_800A2FD4[0] + 0xAC;
        D_800A833E[0] = D_800A2FD4[0] + 0xAC;
        D_800A8346[0] = D_800A2FD4[0] + 0xEC;
        D_800A834E[0] = D_800A2FD4[0] + 0xEC;
        for (i = 0; i < 4; i++) {
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(i * 0x18 + D_800A81B4);
            SetPolyF4((POLY_F4 *)prim);
            prim->r0 = 0xFF;
            prim->g0 = 0;
            prim->b0 = 0;
        }
        tex = D_80090FCE;
        for (i = 35; i >= 0; i--) {
            poly = (POLY_FT4 *)(i * 0x2C + D_800A7994);
            SetPolyFT4(poly);
            SetShadeTex(poly, 1);
            *(u16 *)(D_800A799E + i * 0x2C) = GetClut(tex->clutX, tex->clutY);
            *(u8 *)(D_800A7995 + i * 0x2C) = 2;
            *(u32 *)(D_800A79AC + i * 0x2C) = (u32)&D_800A85AC[i][0];
            *(u32 *)(D_800A79B0 + i * 0x2C) = (u32)&D_800A85AC[i][1];
            *(u32 *)(D_800A79B4 + i * 0x2C) = (u32)&D_800A85AC[i][3];
            *(u32 *)(D_800A79B8 + i * 0x2C) = (u32)&D_800A85AC[i][2];
            *(u16 *)(D_800A79A2 + i * 0x2C) =
                GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
            *(u8 *)(D_800A799C + i * 0x2C) = tex->u + 0x4F;
            *(u8 *)(D_800A799D + i * 0x2C) = tex->v + 0x2F;
            *(u8 *)(D_800A79A0 + i * 0x2C) = tex->u + 0x12;
            *(u8 *)(D_800A79A1 + i * 0x2C) = tex->v + 0x2F;
            *(u8 *)(D_800A79A4 + i * 0x2C) = tex->u + 0x4F;
            *(u8 *)(D_800A79A5 + i * 0x2C) = tex->v;
            *(u8 *)(D_800A79A8 + i * 0x2C) = tex->u + 0x12;
            *(u8 *)(D_800A79A9 + i * 0x2C) = tex->v;
        }
        for (i = 0; i < 0x20; i++) {
            D_800A7FE4[i].x =
                MathMultiplyFixed16(
                    0x3C0000, *(s32 *)(*(u8 **)gCosTableAbsolute2 + i * 128)) >>
                16;
            D_800A7FE4[i].y =
                MathMultiplyFixed16(
                    0x3C0000, *(s32 *)(*(u8 **)gSinTableAbsolute2 + i * 128)) >>
                16;
            D_800A7FE4[i + 0x20].x =
                MathMultiplyFixed16(
                    0x320000, *(s32 *)(*(u8 **)gCosTableAbsolute + i * 128)) >>
                16;
            D_800A7FE4[i + 0x20].y =
                MathMultiplyFixed16(
                    0x320000, *(s32 *)(*(u8 **)gSinTableAbsolute + i * 128)) >>
                16;
        }
        for (i = 0; i < 0x24; i++) {
            for (j = 0; j < 4; j++) {
                D_800A85AC[i][j].vz = 0x64;
            }
        }
        for (i = 0; i < 0x20; i++) {
            D_800A85AC[i][0].vx = D_800A7FE4[(i + 1) % 32].x;
            D_800A85AC[i][0].vy = D_800A7FE4[(i + 1) % 32].y;
            D_800A85AC[i][1].vx = D_800A7FE4[i].x;
            D_800A85AC[i][1].vy = D_800A7FE4[i].y;
            D_800A85AC[i][2].vx = D_800A7FE4[(i + 1) % 32 + 0x20].x;
            D_800A85AC[i][2].vy = D_800A7FE4[(i + 1) % 32 + 0x20].y;
            D_800A85AC[i][3].vx = D_800A7FE4[i + 0x20].x;
            D_800A85AC[i][3].vy = D_800A7FE4[i + 0x20].y;
        }
        D_800A89AC[0] = -0xA;
        D_800A89AE[0] = 0xA;
        D_800A89B4[0] = 0xA;
        D_800A89B6[0] = 0xA;
        D_800A89BC[0] = -0xA;
        D_800A89BE[0] = -0xA;
        D_800A89C4[0] = 0xA;
        D_800A89C6[0] = -0xA;
        SetShadeTex(D_800A7F14, 0);
        D_800A7F18[0] = 0x30;
        D_800A7F19[0] = 0x30;
        D_800A7F1A[0] = 0x30;
        tex = &D_80090FCE[-12];
        D_800A7F22[0] =
            GetTPage(*(u16 *)D_80090F32, 0, tex->tpx, D_80090F28[0]);
        tex += 12;
        u3 = D_80090F2E[0];
        v3 = D_80090F30[0];
        D_800A7F1C[0] = u3 + 0x60;
        D_800A7F1D[0] = v3 + 0xF;
        D_800A7F20[0] = u3 + 0x6F;
        D_800A7F21[0] = v3 + 0xF;
        D_800A7F24[0] = u3 + 0x60;
        D_800A7F25[0] = v3;
        D_800A7F28[0] = u3 + 0x6F;
        D_800A7F29[0] = v3;
        for (i = 0x21, j = 0; j < 3; j++, i++) {
            matA = *(s32 *)(*(u8 **)gCosTableSmall + rot.a[j] * 4);
            matB = *(s32 *)(*(u8 **)gSinTableSmall + rot.a[j] * 4);
            for (k = 0; k < 4; k++) {
                D_800A85AC[i][k].vx =
                    (MathMultiplyFixed16(corners.p[k].x << 16, matA) >> 16) -
                    (MathMultiplyFixed16(corners.p[k].y << 16, matB) >> 16);
                D_800A85AC[i][k].vy =
                    (MathMultiplyFixed16(corners.p[k].x << 16, matB) >> 16) +
                    (MathMultiplyFixed16(corners.p[k].y << 16, matA) >> 16);
            }
            idx = i * 0x2C;
            *(u8 *)(D_800A799C + idx) = tex->u + 0x12;
            *(u8 *)(D_800A799D + idx) = tex->v + 0x2F;
            *(u8 *)(D_800A79A0 + idx) = tex->u + 0x12;
            *(u8 *)(D_800A79A1 + idx) = tex->v;
            *(u8 *)(D_800A79A4 + idx) = tex->u + 0x4F;
            *(u8 *)(D_800A79A5 + idx) = tex->v + 0x2F;
            *(u8 *)(D_800A79A8 + idx) = tex->u + 0x4F;
            *(u8 *)(D_800A79A9 + idx) = tex->v;
        }
        D_800A3494 = 0x300;
        for (i = 0; i < 3; i++) {
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(i * 0x28 + D_800A8534);
            SetPolyFT4(prim);
            SetSemiTrans(prim, 1);
            prim->code = prim->code & 0xFE;
            *(u16 *)(D_800A854A + i * 0x28) = GetTPage(2, 2, 0x300, 0);
            prim->u0 = 0xFD;
            prim->v0 = 0;
            prim->u1 = 0xFE;
            prim->v1 = 0;
            prim->u2 = 0xFD;
            prim->v2 = 1;
            prim->u3 = 0xFE;
            prim->v3 = 1;
            yv = D_800A2FD4[0] + 0x9E;
            prim->y1 = yv;
            *(u16 *)(D_800A853E + i * 0x28) = yv;
        }
        for (i = 0; i < 2; i++) {
            SetPolyF4((POLY_F4 *)(D_800A8184 + i * 0x18));
        }
        D_800A8188[0] = 8;
        D_800A8189[0] = 8;
        D_800A818A[0] = 8;
        D_800A818C[0] = 0;
        D_800A818E[0] = 0xEC;
        D_800A8190[0] = 0x1F;
        D_800A8192[0] = 0xEC;
        D_800A8194[0] = 0;
        D_800A8196[0] = 0xF0;
        D_800A8198[0] = 0x1F;
        D_800A819A[0] = 0xF0;
        D_800A81A0[0] = 0x10;
        D_800A81A1[0] = 0x10;
        D_800A81A2[0] = 0x10;
        D_800A81A4[0] = 0x1F;
        D_800A81A6[0] = 0xEC;
        D_800A81A8[0] = 0x140;
        D_800A81AA[0] = 0xEC;
        D_800A81AC[0] = 0x1F;
        D_800A81AE[0] = 0xF0;
        D_800A81B0[0] = 0x140;
        D_800A81B2[0] = 0xF0;
        D_800A7FD8[0] = 0;
        D_800A7FDC[0] = 0x64;
        D_800A7FE0[0] = 0x64;
    }
}

extern u8 gStandingsPlaceX;
extern u8 gStandingsNameX;
extern u8 gStandingsNameXAbsolute[];
extern u8 gStandingsLapX;
extern u8 gStandingsTimeX;
extern char gFormatLeadingSpaceInteger[];
extern char gFormatInteger[];
extern char gFormatTwoSpacesString[];
extern char gFormatTwoSpacesInteger[];
extern char gTextNegativeSign[];
extern u8 gTextColor;
extern char *D_8009ADEC[];
extern char *D_8009ADF0[];
extern char *D_8009ADF4[];
extern char *D_8009AE94[];
extern s32 sprintfRow(char *, char *, ...) asm("sprintf");
extern void func_80050028Row(char *, s32, s32, s32);
asm(".globl func_80050028Row\nfunc_80050028Row = HudDrawText");
extern void FontDrawColoredIntegerRow(s16, s32, s32,
                                      s32) asm("FontDrawColoredInteger");
extern void HudDrawTimeRow(s32, s32, s32, s32, s32) asm("HudDrawTime");

void HudDrawStandings(s8 firstRow, s32 y) {
    char text[8];
    Car *entry;
    s8 index;
    s8 rowIndex;
    s8 row;
    s8 place;
    u8 selected;
    s32 gap;
    s32 limit;
    u8 *column;
    s32 textY;

    if (gSessionTypeAbsolute[0] != 0) {
        selected = 0;
        rowIndex = firstRow;
        row = 1;
        place = firstRow + 1;
        do {
            sprintfRow(text,
                       place < 10 ? gFormatLeadingSpaceInteger : gFormatInteger,
                       place);
            gTextColor = 9;
            textY = (u8)y;
            func_80050028Row(text, gStandingsPlaceX + 3, textY, 0);
            if (place == gPlayerCar[0]->place) {
                if (selected == 0 && D_800A2EACAbsolute[0] == 0) {
                    gTextColor = 0;
                    func_80050028Row(gPlayerCar[0]->name, gStandingsNameX,
                                     textY, 0);
                    gTextColor = 9;
                    FontDrawColoredIntegerRow(gPlayerCar[0]->lap,
                                              gStandingsLapX + 8, textY, 0);
                    HudDrawTimeRow(gPlayerCar[0]->time, gStandingsTimeX, textY,
                                   0, 1);
                    GraphicsDrawRect(0, (y & 0xFF) - 1, 0x140, 0xC, 0, 0, 0x80,
                                     0);
                    if (row == 15) {
                        return;
                    }
                    selected = 1;
                    row++;
                    place++;
                    gTextColor = 9;
                    y += 12;
                    sprintfRow(text,
                               place < 10 ? gFormatLeadingSpaceInteger
                                          : gFormatInteger,
                               place);
                    func_80050028Row(text, gStandingsPlaceX + 3, (u8)y, 0);
                }
                if (place == gPlayerCar[0]->place &&
                    D_800A2EA8[0] >= gPlayerCar[0]->lap) {
                    goto skipBlank;
                }
            }
            func_80050028Row(D_8009AE94[0], gStandingsLapX + 8, (u8)y, 0);
        skipBlank:
            gTextColor = 0;
            limit = (u8)firstRow + 1;
            index = rowIndex;
            if (gPlayerCar[0]->place < limit && D_800A2EACAbsolute[0] == 0) {
                index = rowIndex - 1;
            }
            textY = (u8)y;
            func_80050028Row(gDriverNames[gDriverOrder[index]], gStandingsNameX,
                             textY, 0);
            if (place == gPlayerCar[0]->place && gPlayerCar[0]->lap < 2) {
                func_80050028Row(D_8009ADF4[0], gStandingsTimeX, textY, 0);
            } else {
                HudDrawTimeRow(D_800AE1EC[index], gStandingsTimeX, (u8)y, 0, 1);
            }
            if (D_800A2EACAbsolute[0] != 0 && place == gPlayerCar[0]->place) {
                GraphicsDrawRect(0, (y & 0xFF) - 1, 0x140, 0xC, 0, 0, 0x80, 0);
            }
            rowIndex++;
            row++;
            place++;
            y += 12;
        } while (row < 16);
        return;
    }
    entry = D_800A35E0[0];
    for (rowIndex = 0; rowIndex < (u8)firstRow; rowIndex++) {
        entry = ((CarLink *)entry->order.node.previous)->car;
    }
    rowIndex = firstRow;
    row = 1;
    if (rowIndex < D_800A2E94[0]) {
        column = gStandingsNameXAbsolute;
        do {
            func_80050028Row(entry->name, gStandingsNameX, (u8)y, 0);
            if (gSplitScreenMode[0] != 0) {
                FontDrawColoredIntegerRow(entry->place, column[-1] + 6, (u8)y,
                                          0);
            } else {
                sprintfRow(text,
                           entry->place < 10 ? gFormatLeadingSpaceInteger
                                             : gFormatInteger,
                           entry->place);
                gTextColor = 9;
                func_80050028Row(text, column[-1] + 3, (u8)y, 0);
                gTextColor = 0;
            }
            if (entry->unkF4 == 0 && D_800A2EA8[0] >= entry->lap) {
                func_80050028Row(D_8009ADF4[0], gStandingsTimeX, (u8)y, 0);
            } else {
                s32 lap;

                lap = entry->lap;
                gTextColor = 9;
                if (D_800A2EA8[0] < lap) {
                    sprintfRow(text, gFormatTwoSpacesString, D_8009AE94[0]);
                } else if (lap >= 100) {
                    sprintfRow(text, gFormatInteger, lap);
                } else if (lap >= 10) {
                    sprintfRow(text, gFormatLeadingSpaceInteger, lap);
                } else {
                    sprintfRow(text, gFormatTwoSpacesInteger, lap);
                }
                textY = (u8)y;
                func_80050028Row(text, gStandingsLapX - 4, textY, 0);
                if (entry->lap == 0) {
                    HudDrawTimeRow(0x7FFFFFFF, gStandingsTimeX, textY, 0, 0);
                } else if (entry == D_800A35E0[0]) {
                    HudDrawTimeRow(entry->unk260, gStandingsTimeX, textY, 0, 0);
                } else {
                    gap = (s16)(((D_800A35E0[0]->lap * gTrackSectionCount[0] +
                                  D_800A35E0[0]->segment) -
                                 (entry->lap * gTrackSectionCount[0] +
                                  entry->segment)) /
                                gTrackSectionCount[0]);
                    gTextColor = 9;
                    if (gap > 0) {
                        func_80050028Row(gTextNegativeSign,
                                         gStandingsTimeX - 10, textY, 0);
                        FontDrawColoredIntegerRow(gap, gStandingsTimeX, textY,
                                                  0);
                        if (gap == 1) {
                            func_80050028Row(D_8009ADF0[0],
                                             gStandingsTimeX + 15, textY, 0);
                        } else if (gap < 10) {
                            func_80050028Row(D_8009ADEC[0],
                                             gStandingsTimeX + 15, textY, 0);
                        } else if (gap < 100) {
                            func_80050028Row(D_8009ADEC[0],
                                             gStandingsTimeX + 25, textY, 0);
                        } else {
                            func_80050028Row(D_8009ADEC[0],
                                             gStandingsTimeX + 35, textY, 0);
                        }
                    } else {
                        func_80050028Row(gTextPositiveSign,
                                         gStandingsTimeX - 10, textY, 0);
                        HudDrawTimeRow(entry->unk264, gStandingsTimeX, textY, 0,
                                       1);
                    }
                }
            }
            if (entry->type == 0 && D_800A2E94[0] >= 3) {
                GraphicsDrawRect(0, (y & 0xFF) - 1, 0x140, 0xC, 0, 0, 0x80, 0);
            }
            if (row == 15) {
                return;
            }
            rowIndex++;
            row++;
            entry = ((CarLink *)entry->order.node.previous)->car;
            y += 12;
        } while (rowIndex < D_800A2E94[0]);
    }
}

extern u8 D_800A3590;
extern s32 gOrderingTableBankLui asm("gOrderingTableBankAbsolute");
extern s32 gOrderingTableLui asm("gOrderingTableAbsolute");
extern char *gTrackShortNames[];
extern char *D_8009AE60[];
extern char *D_8009ADDC[];
extern u8 gStandingsPlaceXRow[] asm("gStandingsPlaceX");
extern void HudDrawStandingsRow(u8, u8) asm("HudDrawStandings");

void MenuDrawStatistics(void) {
    char text[40];
    u8 top;
    u8 y;
    u8 i;

    top = (s8)D_800A3590 / 12;
    GraphicsSetColor(128, 128, 192);
    sprintfHud(text, sHudCaptionFormat, D_8009AD68[gSessionTypeAbsolute[0]][0],
               D_8009AE60[0], gTrackShortNames[D_800A2CE0[0]]);
    if (gSplitScreenMode[0] == 0) {
        HudDrawTextS16(text, (s16)((320 - HudTextWidth((u8 *)text)) >> 1), 210,
                       0);
    }
    for (i = 0; i < 4; i++) {
        HudDrawTextS16(D_8009ADDC[i], gStandingsPlaceXRow[i], 20, 0);
    }
    y = 37 - (s8)D_800A3590 % 12;
    GraphicsDrawRect(0, 0, 320, 35, 0, 0, 0, 0);
    GraphicsDrawRect(0, 205, 320, 35, 0, 0, 0, 0);
    GraphicsSetColor(128, 128, 128);
    HudDrawStandingsRow(top, y);
    if (gSplitScreenMode[0] != 0) {
        gOrderingTableBankLui += 1;
        gOrderingTableLui += 0x1004;
        if (D_800A2E94[0] >= 3) {
            HudDrawStandingsRow(7, 1);
        }
        GraphicsSetColor(128, 128, 192);
        HudDrawTextS16(text, (s16)((320 - HudTextWidth((u8 *)text)) >> 1), 90,
                       0);
        GraphicsDrawRect(0, 85, 320, 35, 0, 0, 0, 0);
        GraphicsDrawRect(0, 0, 320, 120, 0, 0, 0, 1);
        GraphicsDrawRect(0, 0, 320, 120, 0, 0, 0, 1);
        gOrderingTableBankLui -= 1;
        gOrderingTableLui -= 0x1004;
    }
    GraphicsDrawRect(0, 35, 320, 170, 0, 0, 0, 1);
    GraphicsDrawRect(0, 35, 320, 170, 0, 0, 0, 1);
}

typedef struct LapSplit {
    s32 section;
    s32 best;
} LapSplit;

extern s8 gTrackSplitCount[];
extern LapSplit gLapSplits[];
extern s8 gLapSplitIndex;
extern s8 gLapSplitPanelY;
extern u8 gLapSplitShowDelta;
extern s16 gLapSplitMinPos;
extern s16 gLapSplitHoldTimer;
extern s32 gLapSplitDelta;
extern s32 gLapSplitTime;
extern s32 gLapSplitBest;
extern char *D_8009AE44[];
extern char *D_8009AE48[];
extern void HudRecordLapSplitStats(void);
extern void HudDrawTrafficGapPanel(void);
extern void HudDrawTextLap(char *, s16, s16, s8) asm("HudDrawText");
extern void HudDrawTimeLap(s32, s16, s16, s8, s8) asm("HudDrawTime");

void HudDrawLapSplit(void) {
    extern u8 D_800A3688;
    s32 pos;
    s32 time;
    s32 track;
    s16 delay;

    pos = gPlayerCar[0]->lap * gTrackSectionCount[0] + gPlayerCar[0]->segment;
    if (pos >= gLapSplits[gLapSplitIndex].section) {
        HudRecordLapSplitStats();
        gLapSplitTime = time = gPlayerCar[0]->unk258;
        gLapSplitBest = gLapSplits[gLapSplitIndex].best;
        gLapSplitDelta = time - gLapSplitBest;
        gLapSplits[gLapSplitIndex].section += gTrackSectionCount[0];
        if (time < gLapSplits[gLapSplitIndex].best) {
            gLapSplits[gLapSplitIndex].best = time;
        }
        track = D_800A2CE0[0];
        gLapSplitIndex = (gLapSplitIndex + 1) % gTrackSplitCount[track];
        if (pos > gLapSplitMinPos) {
            delay = 40;
            if (track == 3) {
                delay = 20;
            }
            gLapSplitHoldTimer = delay;
        }
        gLapSplitShowDelta = 1;
    }
    if (D_800A3688 == 0) {
        return;
    }
    if (gSessionTypeAbsolute[0] == 0) {
        HudDrawTrafficGapPanel();
    }
    if (D_800A3688 == 0 || pos <= gLapSplitMinPos) {
        return;
    }
    if (gLapSplitHoldTimer != 0) {
        gLapSplitHoldTimer--;
    } else if (pos >= gLapSplits[gLapSplitIndex].section - 20) {
        if (gLapSplitPanelY > 0) {
            gLapSplitPanelY -= 4;
        }
    } else if (gLapSplitPanelY < 60) {
        gLapSplitPanelY += 4;
    } else {
        gLapSplitShowDelta = 0;
        return;
    }
    if (gPlayerCar[0]->unk268 != 0) {
        return;
    }
    GraphicsSetColor(0x80, 0x80, 0xC0);
    HudDrawTextLap(D_8009AE44[0], 0x5A, gLapSplitPanelY + 0xB9, 0);
    HudDrawTextLap(D_8009AE48[0], 0x5A, gLapSplitPanelY + 0xC3, 0);
    GraphicsSetColor(0x80, 0xC0, 0x80);
    if (gLapSplitShowDelta != 0) {
        HudDrawTimeLap(gLapSplitBest, 0x87, gLapSplitPanelY + 0xB9, 0, 1);
        HudDrawTimeLap(gLapSplitTime, 0x87, gLapSplitPanelY + 0xC3, 0, 1);
        HudDrawTimeLap(gLapSplitDelta < 0 ? -gLapSplitDelta : gLapSplitDelta,
                       0x87, gLapSplitPanelY + 0xCD, 0, 1);
        HudDrawTextLap(gLapSplitDelta < 0 ? gTextNegativeSign
                                          : gTextPositiveSign,
                       0x7D, gLapSplitPanelY + 0xCD, 0);
    } else {
        HudDrawTimeLap(gLapSplits[gLapSplitIndex].best, 0x87,
                       gLapSplitPanelY + 0xB9, 0, 1);
        HudDrawTimeLap(gPlayerCar[0]->unk258, 0x87, gLapSplitPanelY + 0xC3, 0,
                       1);
    }
    GraphicsDrawDoubleBorderRect(0x55, gLapSplitPanelY + 0xB4, 0x87, 0x28, 0, 0,
                                 0, 1);
}

void HudInitLapSplits(void) {
    s32 idx;
    s32 *q;
    s8 *p;
    s32 pm;
    s32 base;
    s32 inf;
    s8 i;

    idx = D_800A2CE0[0];
    gLapSplitShowDelta = 0;
    gLapSplitIndex = 0;
    gLapSplitHoldTimer = 0;
    gLapSplitPanelY = 0x3C;
    p = gTrackSplitCount;
    i = 0;
    if (p[idx] > 0) {
        q = &gTrackSectionCount[0];
        pm = (s32)p;
        inf = 0x7FFFFFFF;
    loop:
        base = *q;
        /* The do-while (0) doubles the refs of the loop locals, which swaps
         * the a0/a1/a2 and t0/t1 allocation to retail's. */
        do {
            gLapSplits[i].section = base + base * (i + 1) / *(s8 *)(idx + pm);
            gLapSplits[i].best = inf;
            i++;
            if (i < *(s8 *)(idx + pm)) {
                goto loop;
            }
        } while (0);
    }
    gLapSplitMinPos = gTrackSectionCount[0] * 2 + 1;
}

extern u8 D_800A34AC;
extern u8 D_800A34B0;
extern s32 D_800A34B4;
extern s32 D_800A34B8;
extern s32 D_800A34BC;
extern s32 D_800A34C0;
extern u8 *D_8009AE4C[];
extern void func_80050028Lbl(char *, s16, s16, s8);
asm(".globl func_80050028Lbl\nfunc_80050028Lbl = HudDrawText");

void HudDrawTrafficGapPanel(void) {
    if (gLapSplitPanelY < 0x3C) {
        return;
    }
    if (D_800A34B0 != 0) {
        if ((s8)D_800A34AC == 0x3C) {
            HudUpdateTrafficGapData();
            if (D_800A34BC == 0 && D_800A34C0 == 0) {
                D_800A34B0 = 0;
                return;
            }
        }
        if ((s8)D_800A34AC > 0) {
            D_800A34AC = (s8)D_800A34AC - 4;
        }
        D_800A34B0 = D_800A34B0 - 1;
        goto display;
    }
    if ((s8)D_800A34AC < 0x3C) {
        D_800A34AC = (s8)D_800A34AC + 4;
    display:
        if (gPlayerCar[0]->unk268 == 0) {
            GraphicsSetColor(0x80, 0x80, 0xC0);
            func_80050028Lbl((char *)D_8009AE4C[0], 0x50, (s8)D_800A34AC + 0xB9,
                             0);
            GraphicsSetColor(0x80, 0xC0, 0x80);
            if (D_800A34BC != 0) {
                func_80050028Lbl((char *)D_800A34B4, 0x50,
                                 (s8)D_800A34AC + 0xC3, 0);
                HudDrawTime((void *)D_800A34BC, 0x96,
                            (s16)((s8)D_800A34AC + 0xC3), 0, 1);
            }
            if (D_800A34C0 != 0) {
                func_80050028Lbl((char *)D_800A34B8, 0x50,
                                 (s8)D_800A34AC + 0xCD, 0);
                HudDrawTime((void *)D_800A34C0, 0x96,
                            (s16)((s8)D_800A34AC + 0xCD), 0, 1);
            }
            GraphicsDrawDoubleBorderRect(0x4B, (s8)D_800A34AC + 0xB4, 0xA0,
                                         0x28, 0, 0, 0, 1);
        }
    }
}

extern char D_800A8A4C[];
extern char D_800A8A60[];
extern char gTextSpaceDelimiter[];
extern char *strcpy(char *, const char *);
extern char *strtok(char *, const char *);

#ifdef NATIVE
void HudUpdateTrafficGapData(void) {
    register s32 len;
    register Car *car;
    Car *e0;
    register s32 prod2;
    s32 prod1;
    s32 refDist;
    s32 rel;
    s32 e01d6;
    s32 car1d6;
    s32 e0dist;
    s32 cardist;
    s32 other1d6;
    s32 otherdist;
    char *name2;
    s32 t1;
    s32 t2;

    e0 = (u8 *)D_800A35E0[0];
    len = gTrackSectionCount[0];
    e01d6 = e0->lap;
    /* mult e01d6, len: mflo below reads the product. */
    car = gPlayerCar[0];
    car1d6 = car->lap;
    prod1 = e01d6 * len; /* mflo */
    /* mult car1d6, len: mflo below reads the product. */
    e0dist = e0->segment;
    cardist = car->segment;
    D_800A34C0 = 0; /* sw $zero, %gp_rel(D_800A34C0)($gp) */
    D_800A34BC = 0; /* sw $zero, %gp_rel(D_800A34BC)($gp) */
    refDist = prod1 + e0dist;
    prod2 = car1d6 * len; /* mflo */
    cardist = (u32)prod2 - -(u32)cardist;
    if (refDist - cardist < len) {
        if (car->place >= 2) {
            e0 = (u8 *)((CarLink *)car->order.node.next)->car;
            t1 = car->unk264;
            t2 = e0->unk264;
            car = (Car *)e0->name;
            D_800A34BC = t1 - t2;
            strcpy(D_800A8A4C, (char *)car);
            D_800A34B4 = (s32)strtok(D_800A8A4C, gTextSpaceDelimiter);
            D_800A34B4 = (s32)strtok((char *)0, gTextSpaceDelimiter);
        }
        asm volatile("" : : : "memory");
        if (*(s32 *)&gPlayerCar[0]->order.node.previous != 0) {
            e0 = (u8 *)((CarLink *)gPlayerCar[0]->order.node.previous)->car;
            len = gTrackSectionCount[0];
            other1d6 = e0->lap;
            /* mult other1d6, len: mflo below reads the product. */
            otherdist = e0->segment;
            otherdist = other1d6 * len + otherdist; /* mflo $7; addu */
            if (refDist - otherdist < len) {
                rel = e0->unk264;
                if (gPlayerCar[0]->place != 1) {
                    rel -= gPlayerCar[0]->unk264;
                }
                name2 = e0->name;
                D_800A34C0 = rel;
                strcpy(D_800A8A60, name2);
                D_800A34B8 = (s32)strtok(D_800A8A60, gTextSpaceDelimiter);
                D_800A34B8 = (s32)strtok((char *)0, gTextSpaceDelimiter);
            }
        }
    }
}
#else
void HudUpdateTrafficGapData(void) {
    register s32 len asm("v1");
    register Car *car asm("a1");
    Car *e0;
    register s32 prod2 asm("$8");
    s32 prod1;
    s32 refDist;
    s32 rel;
    s32 e01d6;
    s32 car1d6;
    s32 e0dist;
    s32 cardist;
    s32 other1d6;
    s32 otherdist;
    char *name2;
    s32 t1;
    s32 t2;

    e0 = (u8 *)D_800A35E0[0];
    len = gTrackSectionCount[0];
    e01d6 = e0->lap;
    asm volatile("mult\t%0, %1" : : "r"(e01d6), "r"(len));
    car = gPlayerCar[0];
    car1d6 = car->lap;
    asm volatile("mflo %0" : "=r"(prod1));
    asm volatile("mult\t%0, %1" : : "r"(car1d6), "r"(len));
    e0dist = e0->segment;
    cardist = car->segment;
    asm volatile("sw\t$zero, %gp_rel(D_800A34C0)($gp)");
    asm volatile("sw\t$zero, %gp_rel(D_800A34BC)($gp)");
    refDist = prod1 + e0dist;
    asm volatile("mflo %0" : "=r"(prod2));
    cardist = (u32)prod2 - -(u32)cardist;
    if (refDist - cardist < len) {
        if (car->place >= 2) {
            e0 = (u8 *)((CarLink *)car->order.node.next)->car;
            t1 = car->unk264;
            t2 = e0->unk264;
            car = (Car *)e0->name;
            D_800A34BC = t1 - t2;
            strcpy(D_800A8A4C, (char *)car);
            D_800A34B4 = (s32)strtok(D_800A8A4C, gTextSpaceDelimiter);
            D_800A34B4 = (s32)strtok((char *)0, gTextSpaceDelimiter);
        }
        asm volatile("" : : : "memory");
        if (*(s32 *)&gPlayerCar[0]->order.node.previous != 0) {
            e0 = (u8 *)((CarLink *)gPlayerCar[0]->order.node.previous)->car;
            len = gTrackSectionCount[0];
            other1d6 = e0->lap;
            asm volatile("mult\t%0, %1" : : "r"(other1d6), "r"(len));
            otherdist = e0->segment;
            asm volatile("mflo $7\n\taddu %0, $7, %1"
                         : "=r"(otherdist)
                         : "0"(otherdist));
            if (refDist - otherdist < len) {
                rel = e0->unk264;
                if (gPlayerCar[0]->place != 1) {
                    rel -= gPlayerCar[0]->unk264;
                }
                name2 = e0->name;
                D_800A34C0 = rel;
                strcpy(D_800A8A60, name2);
                D_800A34B8 = (s32)strtok(D_800A8A60, gTextSpaceDelimiter);
                D_800A34B8 = (s32)strtok((char *)0, gTextSpaceDelimiter);
            }
        }
    }
}
#endif

extern char *D_8009A3F8[];
extern char *D_8009AE70[];
extern POLY_FT4 D_800A8A84[];
extern u8 D_800A35A8;
extern u8 D_800A3924;
extern u8 D_800A380C;
extern u8 D_800A3614;
extern u8 D_800A36FC;
extern u8 D_800A3700;
extern s16 D_800A34C4;
extern u8 D_800A8AB6[];
/* Keep the first x-coordinate load separate from the indexed table base. */
extern s16 D_800A8AB4First[];
asm(".globl D_800A8AB4First\nD_800A8AB4First = D_800A8AB4");
extern s16 D_800A8AB4Coords[][2] asm("D_800A8AB4");
extern s16 D_800A8AB6Coords[][2] asm("D_800A8AB6");
extern void MenuDrawLapStatistics(s8, s8);
extern void FontDrawColoredInteger(s32, s32, s32, s8);

void MenuDrawTimingAndScoring(void) {
    char caption[40];
    char *title;
    char *captionArg;
    char **titleTable;
    s32 width;
    s32 centeredX;
    s8 *lapCount;
    s32 loopLapCount;
    u8 slideLap;
    u8 slideMode;
    s32 *position;
    s32 scale;
    s32 track;
    u8 i;

    GraphicsSetColor(128, 128, 192);
    sprintfHud(caption, sHudCaptionFormat, gPlayerCar[0]->name, D_8009A3F8[0],
               gTrackShortNames[D_800A2CE0[0]]);
    titleTable = D_8009AE70;
    width = HudTextWidth((u8 *)titleTable[0]);
    title = titleTable[0];
    centeredX = 320;
    width = centeredX - width;
    HudDrawTextS16(title, (s16)(width >> 1), 20, 0);
    width = HudTextWidth((u8 *)caption);
    captionArg = caption;
    HudDrawTextS16(captionArg, (s16)((320 - width) << 15 >> 16), 210, 0);
    GraphicsDrawRect(0, 0, 320, 35, 0, 0, 0, 0);
    GraphicsDrawRect(0, 205, 320, 35, 0, 0, 0, 0);
    GraphicsSetColor(128, 128, 128);
    MenuDrawLapStatistics((s8)D_800A35A8, (s8)D_800A3924);
    slideLap = D_800A36FC;
    slideMode = D_800A3700;
    D_800A36FC = 128 - slideLap;
    D_800A3700 = 128 - slideMode;
    MenuDrawLapStatistics((s8)D_800A380C, (s8)D_800A3614);
    if (slideLap != 0) {
        D_800A36FC = slideLap - 8;
    } else {
        D_800A36FC = 0;
        D_800A35A8 = D_800A380C;
    }
    if (slideMode != 0) {
        D_800A3700 = slideMode - 8;
    } else {
        D_800A3700 = 0;
        D_800A3924 = D_800A3614;
    }
    position = (s32 *)gPlayerCar[0];
    scale = D_800A34C4;
    track = D_800A2CE0[0] * 2;
    D_800A8A84[0].x0 = 300 - D_80099230[track] - position[0] / scale - 3;
    D_800A8A84[0].y0 = D_80099231[track] + position[1] / scale + 15;
    D_800A8A84[0].x1 = 300 - D_80099230[track] - position[0] / scale + 3;
    D_800A8A84[0].y1 = D_80099231[track] + position[1] / scale + 15;
    D_800A8A84[0].x2 = 300 - D_80099230[track] - position[0] / scale - 3;
    D_800A8A84[0].y2 = D_80099231[track] + position[1] / scale + 21;
    D_800A8A84[0].x3 = 300 - D_80099230[track] - position[0] / scale + 3;
    D_800A8A84[0].y3 = D_80099231[track] + position[1] / scale + 21;
    GraphicsAddPolyFT4((u8 *)D_800A8A84);
    HudDrawTextS16(D_8009AE94[0], D_800A8AB4First[0], *(s16 *)D_800A8AB6, 0);
    lapCount = gTrackSplitCount;
    i = 1;
    if (i < gTrackSplitCount[D_800A2CE0[0]]) {
        loopLapCount = (s32)lapCount;
    drawLapMarker:
        FontDrawColoredInteger(i, D_800A8AB4Coords[i][0],
                               D_800A8AB6Coords[i][0], 0);
        i++;
        if (i < *(s8 *)(D_800A2CE0[0] + loopLapCount)) {
            goto drawLapMarker;
        }
    }
    func_8001BA94(1);
    GraphicsDrawRect(0, 35, 320, 170, 0, 0, 0, 1);
    GraphicsDrawRect(0, 35, 320, 170, 0, 0, 0, 1);
}

/* A 0x30 lap record: split speeds, split times and running totals. */
typedef struct {
    u16 unk0;
    u16 unk2; /* 0x02: average split speed */
    s16 unk4;
    s16 splitSpeed[5]; /* 0x06 */
    s32 splitTime[4];  /* 0x10 */
    s32 splitTotal[4]; /* 0x20 */
} LapRecord;

extern LapRecord *D_800A8A74[];
extern char *D_8009AE64[];
extern char *D_8009AE74[];
extern char *D_8009AE78[];
extern char *D_8009AE7C[];
extern char *D_8009AE80[];
extern char *D_8009AE84[];
extern char *D_8009AE88[];
extern char *D_8009AE8C[];
extern char *D_8009AE90[];
extern char *D_8009AE98[];
extern char gFormatStringColonHashInteger[];
extern char gFormatStringString[];
extern char gFormatIntegerDotIntegerMenu[];

void MenuDrawLapStatistics(s8 lap, s8 mode) {
    char title[40];
    char valueText[8];
    u8 top;
    u8 y;
    u8 i;
    u8 *lapData;
    s32 textY;
    u8 x;
    s32 labelWidth;
    s32 fraction;
    register s32 setting asm("a3");
    s16 speed;
    s32 number;
    char **label;
    char *sign;

    top = 47;
    speed = D_800A8A74[lap]->unk4;
    if (speed == 0x7FFF) {
        strcpy(title, D_8009AE64[lap]);
    } else {
        sprintfRow(title, gFormatStringColonHashInteger, D_8009AE64[lap],
                   speed);
    }
    func_80050028Row(title, 20, top, 2);
    y = top + 24;
    for (i = 1; i < gTrackSplitCount[D_800A2CE0[0]]; i++) {
        textY = y;
        func_80050028Row(D_8009AE74[0], 20, textY, 0);
        FontDrawColoredInteger(i, 60, textY, 0);
        y += 12;
    }
    func_80050028Row(D_8009AE78[0], 20, y, 0);
    y = top + 24;
    switch (mode) {
    case 0:
        func_80050028Row(D_8009AE7C[0], 215, top, 3);
        for (i = 0; i < gTrackSplitCount[D_800A2CE0[0]]; i++) {
            HudDrawTimeRow(D_800A8A74[lap]->splitTime[i], 215, y, 3, 1);
            y += 12;
        }
        y += 6;
        textY = y;
        func_80050028Row(D_8009AE80[0], 20, textY, 3);
        lapData = (u8 *)D_800A8A74[lap];
        lapData += gTrackSplitCount[D_800A2CE0[0]] * 4;
        /* lapData is the record stepped by the split count, so this is
         * splitTotal[count - 1]. */
        HudDrawTimeRow(((LapRecord *)lapData)->splitTotal[-1], 215, textY, 3,
                       1);
        break;
    case 1: {
        s32 speedValue;

        func_80050028Row(D_8009AE84[0], 215, top, 3);
        for (i = 0; i < gTrackSplitCount[D_800A2CE0[0]]; i++) {
            speed = D_800A8A74[lap]->splitSpeed[i];
            if (speed == 0x7FFF) {
                func_80050028Row(D_8009AE90[0], 215, y, 3);
            } else {
                if (gPlayerCar[0]->unkF7) {
                    speedValue = speed * 292 / 550;
                } else {
                    speedValue = speed * 210 / 550;
                }
                FontDrawColoredInteger(speedValue, 215, y, 3);
            }
            y += 12;
        }
        y += 6;
        textY = y;
        func_80050028Row(D_8009AE88[0], 20, textY, 3);
        speed = *(s16 *)&D_800A8A74[lap]->unk2;
        if (speed == 0x7FFF) {
            func_80050028Row(D_8009AE90[0], 215, textY, 3);
        } else {
            if (gPlayerCar[0]->unkF7) {
                speedValue = speed * 292 / 550;
            } else {
                speedValue = speed * 210 / 550;
            }
            fraction = speedValue;
            FontDrawColoredInteger(fraction, 215, y, 3);
        }
        break;
    }
    case 2:
        func_80050028Row(D_8009AE8C[0], 215, top, 3);
        for (i = 0; i < gTrackSplitCount[D_800A2CE0[0]]; i++) {
            HudDrawTimeRow(D_800A8A74[lap]->splitTotal[i], 215, y, 3, 1);
            y += 12;
        }
        break;
    }
    top = 169;
    if (*(s8 *)&D_800A8A74[lap]->unk0 == 127) {
        for (i = 0; i < 2; i++) {
            sprintfRow(title, gFormatStringString, D_8009AE98[i],
                       D_8009AE98[-2]);
            func_80050028Row(
                title, (s32)((320 - HudTextWidth((u8 *)title)) << 15) >> 16,
                top, 2);
            top += 12;
        }
    } else {
        s32 footerY;
        register char *valueBuffer asm("a0");
        register char *valueFormat asm("a1");
        s32 wholeSetting;
        s32 setupIndex;
        s32 screenX;
        register s32 measuredWidth asm("v0");
        char **labelBase;

        for (i = 0; i < 2; i++) {
            setupIndex = i;
            setting = *(s8 *)((u8 *)D_800A8A74[lap] + setupIndex);
            valueBuffer = valueText;
            /* Set the buffer argument before the sign test. */
            asm("" : : "r"(valueBuffer), "r"(setting));
            valueFormat = gFormatIntegerDotIntegerMenu;
            if (setting < 0) {
                setting = -setting;
            }
            /* Keep the magnitude calculation before the split. */
            asm("" : "=r"(setting) : "0"(setting));
            wholeSetting = (u8)setting >> 1;
            fraction = setting & 1;
            setting = fraction;
            asm(""
                : "=r"(setting), "=r"(wholeSetting)
                : "0"(setting), "1"(wholeSetting));
            sprintfRow(valueBuffer, valueFormat, wholeSetting,
                       (setting * 4) | setting);
            labelBase = D_8009AE98;
            label = &labelBase[setupIndex];
            footerY = top;
            measuredWidth = HudTextWidth((u8 *)*label);
            valueBuffer = valueText;
            /* Keep the width result until the next pointer is ready. */
            asm(""
                : "=r"(measuredWidth)
                : "0"(measuredWidth), "r"(valueBuffer));
            labelWidth = measuredWidth;
            x = (u32)(320 -
                      ((u8)labelWidth + HudTextWidth((u8 *)valueBuffer))) >>
                1;
            screenX = x;
            func_80050028Row(*label, screenX, footerY, 2);
            /* The repeated index input preserves the register order. */
            asm(""
                : "=r"(labelWidth)
                : "0"(labelWidth), "r"(setupIndex), "r"(setupIndex),
                  "r"(setupIndex), "r"(setupIndex), "r"(screenX));
            sign = gTextPositiveSign;
            if (*(s8 *)((u8 *)D_800A8A74[lap] + setupIndex) < 0) {
                sign = gTextNegativeSign;
            }
            number = screenX + (u8)labelWidth;
            func_80050028Row(sign, number, footerY, 2);
            func_80050028Row(valueText, number + 9, footerY, 2);
            /* Keep both measured values through the setup text draws. */
            asm("" : : "r"(screenX), "r"(labelWidth));
            top += 12;
        }
    }
}

typedef struct {
    u16 tpx;
    u16 tpy;
    u16 clutX;
    u16 clutY;
    u8 u;
    u8 unk9;
    u16 v;
    u16 tpage;
} TrackTexture;
extern TrackTexture D_80090F26[];
extern u8 D_800A8A88[];
extern u8 D_800A8A89[];
extern u8 D_800A8A8A[];
extern u8 D_800A8A90[];
extern u8 D_800A8A91[];
extern u8 D_800A8A98[];
extern u8 D_800A8A99[];
extern u8 D_800A8AA0[];
extern u8 D_800A8AA1[];
extern u8 D_800A8AA8[];
extern u8 D_800A8AA9[];
extern u16 D_800A8A9A[];
extern u8 *D_800A8AB0[];
extern u8 *D_800A8AB0nm[] asm("D_800A8AB0.NON_MATCHING");
extern u8 D_800A8AB4[];

void func_8004F880(void) {
    TrackTexture *tim;
    Car *car;
    s8 *p;
    s8 *pb;
    s8 *pj;
    s32 pm;
    s32 *q;
    s32 uvBase;
    s32 distBase;
    s32 stride;
    s32 idx;
    s32 x;
    s32 lim;
    s32 inf;
    s32 w;
    s8 i;
    s8 j;
    s32 pad[2];

    (void)&pad;
    tim = D_80090F26;
    D_800A3614 = 0;
    D_800A380C = 0;
    D_800A3924 = 0;
    D_800A35A8 = 0;
    D_800A8AB0[0] = HeapAlloc(0xC0);
    for (i = 0; i < 4; i++) {
        lim = 0x7FFF;
        pb = gTrackSplitCount;
        do {
            stride = i * 0x30;
            *(u8 *)(stride + (s32)D_800A8AB0[0]) = 0x7F;
            uvBase = stride + (s32)D_800A8AB0[0];
            p = (s8 *)D_800A2CE0[0];
        } while (0);
        p = (s8 *)((s32)p + (s32)pb);
        *(u16 *)&((LapRecord *)uvBase)->unk4 = lim;
        ((LapRecord *)uvBase)->unk2 = lim;
        j = 0;
        if (j < p[0]) {
            pj = p;
        innerJ:
            inf = 0x7FFFFFFF;
            *(u16 *)&((LapRecord *)(stride + (s32)D_800A8AB0[0]))
                 ->splitSpeed[j] = lim;
            /* The record stepped by split j. */
            distBase = j * 4 + (stride + (s32)D_800A8AB0nm[0]);
            ((LapRecord *)distBase)->splitTotal[0] = inf;
            ((LapRecord *)distBase)->splitTime[0] = inf;
            j++;
            if (j < pj[0]) {
                goto innerJ;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        D_800A8A74[i] = (LapRecord *)(D_800A8AB0[0] + i * 0x30);
    }
    x = D_801F3FF8[0];
    D_800A34C4 = x * 4;
    idx = D_800A2CE0[0];
    p = gTrackSplitCount;
    if (gTrackSplitCount[idx] > 0) {
        i = 0;
        q = &gTrackSectionCount[0];
        pm = (s32)p;
        w = (x << 18) >> 16;
    loopM:
        *(u16 *)(D_800A8AB4 + i * 4) =
            0x12C - D_80099230[idx * 2] -
            gTrackSections[0][i * q[0] / *(s8 *)(idx + pm)].x / w - 4;
        uvBase = q[0];
        *(u16 *)(D_800A8AB6 + i * 4) =
            D_80099231[idx * 2] +
            gTrackSections[0][i * uvBase / *(s8 *)(idx + pm)].z / w + 0xE;
        i++;
        if (i < *(s8 *)(idx + pm)) {
            goto loopM;
        }
    }
    SetPolyFT4(D_800A8A84);
    SetShadeTex(D_800A8A84, 0);
    D_800A8A88[0] = 0x80;
    D_800A8A89[0] = 0x80;
    D_800A8A8A[0] = 0xC0;
    D_800A8A90[0] = tim->u + 0x60;
    D_800A8A91[0] = tim->v;
    D_800A8A98[0] = tim->u + 0x6F;
    D_800A8A99[0] = tim->v;
    D_800A8AA0[0] = tim->u + 0x60;
    D_800A8AA1[0] = (u8)tim->v + 0xF;
    D_800A8AA8[0] = tim->u + 0x6F;
    D_800A8AA9[0] = (u8)tim->v + 0xF;
    D_800A8A9A[0] = GetTPage(tim->tpage, 0, tim->tpx, tim->tpy);
    car = gPlayerCar[0];
    car->unk2A4 = (u16)car->unk2A0 + 8;
    car->unk2AA = (u16)car->unk2A6 + 8;
}

typedef struct {
    /* 0x00 */ s32 lapTime;
} LapTimeSlot;

void HudRecordLapSplitStats(void) {
    extern u8 D_800A3688;
    extern LapRecord *D_800A8A80[];
    u8 *entry;
    Car *car;
    LapTimeSlot *slot;
    s32 lapTime;
    s32 speed;
    s32 sum;
    s32 idx;
    u8 *tmp;
    s8 i;
    s8 j;

    /* The lap record stepped by one split, so ((LapRecord *)entry)
     * ->splitTotal[-1] is the previous split's total. */
    entry = (u8 *)(gLapSplitIndex * 4 + (s32)D_800A8A80[0]);
    slot = (LapTimeSlot *)(entry + 0x10);
    if (gLapSplitIndex == 0) {
        lapTime = gPlayerCar[0]->unk258;
    } else {
        lapTime = gPlayerCar[0]->unk258 - ((LapRecord *)entry)->splitTotal[-1];
    }
    car = gPlayerCar[0];
    slot->lapTime = lapTime;
    speed = ((s16 *)&car->speed)[1];
    D_800A8A80[0]->splitSpeed[gLapSplitIndex] = speed;
    D_800A8A80[0]->splitTotal[gLapSplitIndex] = car->unk258;
    if (gLapSplitIndex == gTrackSplitCount[*(s32 *)(void *)D_800A2CE0] - 1) {
        if (D_800A3688 != 0 && gSessionTypeAbsolute[0] == 0) {
            D_800A34B0 = *(s32 *)(void *)D_800A2CE0 == 3 ? 0x28 : 0x32;
        }
        sum = 0;
        i = 0;
        if (gTrackSplitCount[D_800A2CE0[0]] > 0) {
            do {
                sum += (u16)D_800A8A80[0]->splitSpeed[i];
                i++;
            } while (i < gTrackSplitCount[D_800A2CE0[0]]);
        }
        D_800A8A80[0]->unk2 = (s16)sum / gTrackSplitCount[D_800A2CE0[0]];
        idx = gLapSplitIndex;
        for (i = 0; i < 3; i++) {
            j = i + 1;
            if (j < 4) {
                do {
                    if (D_800A8A74[j]->splitTotal[idx] <
                        D_800A8A74[i]->splitTotal[idx]) {
                        tmp = D_800A8A74[i];
                        D_800A8A74[i] = D_800A8A74[j];
                        D_800A8A74[j] = tmp;
                    }
                    j++;
                } while (j < 4);
            }
        }
    }
}

extern LapRecord *D_800A8A80[];
void RaceStoreLapRecordCarFields(void) {
    *(u8 *)&D_800A8A80[0]->unk0 = (u16)gPlayerCar[0]->unk2AA;
    ((u8 *)D_800A8A80[0])[1] = (u16)gPlayerCar[0]->unk2A4;
    *(u16 *)&D_800A8A80[0]->unk4 = (u16)gPlayerCar[0]->lap;
}

extern s8 gTextColorS asm("gTextColor.NON_MATCHING");
extern char gFormatIntegernm[] asm("gFormatInteger.NON_MATCHING");
extern u8 gTextColorNm asm("gTextColor.NON_MATCHING");
extern void func_80050028Args(char *, s16, s16, s8);
asm(".globl func_80050028Args\nfunc_80050028Args = HudDrawText");
extern s32 sprintfTextArgs(char *, char *, ...);
asm(".globl sprintfTextArgs\nsprintfTextArgs = sprintf");
void FontDrawColoredInteger(s32 value, s32 x, s32 y, s8 colorMode) {
    char text[16];

    if (colorMode == 1) {
        gTextColorNm = 6;
    } else {
        gTextColorNm = 9;
    }
    sprintfTextArgs(text, gFormatIntegernm, value);
    func_80050028Args(text, (s16)x, (s16)y, colorMode);
    gTextColorNm = 0;
}

extern u8 D_800A34C8[3];
extern u8 D_800A8AC8[];
extern u8 D_800A8AC9[];
extern u8 D_800A8ACA[];
extern u8 D_80098D18[];
extern POLY_FT4 D_800A8AC4[];
extern u8 D_800A8ADA[];

/* Draws TEXT with the glyph table at gHudGlyphs, one POLY_FT4 per glyph.
 * Retail's allocation needs a few odd spellings: the y and mode copies
 * order the prologue moves, the s32 width keeps x first in `x + width`,
 * the two gTextColor paths share cellRightX so its sum isn't scheduled
 * late, the empty asm copies keep the x1/x3 stores on the right-edge
 * register, and lineH is pinned to s4 because y otherwise outranks it. */
void HudDrawText(u8 *text, s32 x, s32 yArg, s8 modeArg) {
    POLY_FT4 *prim;
    u8 *p;
    u8 *cp;
    Glyph *glyph;
    u16 w;
    s32 width;
    u8 i;
    s32 y;
    s8 mode;
    s32 lineH0;
    register s32 lineH asm("$20");
    s32 tc;
    u8 color;
    s32 ySum;
    s32 cellRightX;

    i = 0;
    y = yArg;
    mode = modeArg;
    if (mode == 1) {
        lineH0 = (u32)(*(s16 *)&D_80098D18[0] * 3) >> 2;
    } else {
        lineH0 = *(u16 *)&D_80098D18[0];
    }
    lineH = lineH0;
    if (mode >= 2) {
        u8 sr;
        u8 sg;
        u8 sb;

        do {
            asm("" : "=r"(cp) : "0"(D_800A8AC8));
            sr = cp[0];
            sg = cp[1];
            sb = cp[2];
            D_800A34C8[0] = sr;
            D_800A34C8[1] = sg;
            D_800A34C8[2] = sb;
            if (mode == 2) {
                color = D_800A36FC;
            } else {
                color = D_800A3700;
            }
            cp[0] = color;
            cp[1] = color;
            cp[2] = color;
        } while (0);
        prim = D_800A8AC4;
        SetSemiTrans(prim, 1);
        p = (u8 *)prim + 0x16;
        if (text[i] != 0) {
            lineH = y + lineH;
            while (text[i] != 0) {
                u8 v3;
                glyph = &gHudGlyphs[text[i]];
                tc = GetTPage(0, 1, glyph->x, glyph->y);
                ((POLY_FT4 *)(p - 0x16))->tpage = tc;
                width = (u16)glyph->width;
                w = width;
                ((POLY_FT4 *)(p - 0x16))->u0 = glyph->u;
                ((POLY_FT4 *)(p - 0x16))->v0 = glyph->v;
                ((POLY_FT4 *)(p - 0x16))->u1 = glyph->u + w;
                ((POLY_FT4 *)(p - 0x16))->v1 = glyph->v;
                ((POLY_FT4 *)(p - 0x16))->u2 = glyph->u;
                ((POLY_FT4 *)(p - 0x16))->v2 = glyph->v + *(u8 *)&glyph->height;
                ((POLY_FT4 *)(p - 0x16))->u3 = glyph->u + w;
                tc = gTextColorS;
                v3 = glyph->v + *(u8 *)&glyph->height;
                ((POLY_FT4 *)(p - 0x16))->v3 = v3;
                if (tc != 0) {
                    s32 newX;

                    newX = x + ((tc - (s16)width) >> 1);
                    x = x + tc;
                    cellRightX = width + newX;
                    ((POLY_FT4 *)(p - 0x16))->x0 = newX;
                    ((POLY_FT4 *)(p - 0x16))->y0 = y;
                    ((POLY_FT4 *)(p - 0x16))->x1 = cellRightX;
                    ((POLY_FT4 *)(p - 0x16))->y1 = y;
                    ((POLY_FT4 *)(p - 0x16))->x2 = newX;
                    ((POLY_FT4 *)(p - 0x16))->y2 = lineH;
                    ((POLY_FT4 *)(p - 0x16))->x3 = cellRightX;
                } else {
                    s32 rightX;
                    rightX = x + width;
                    ((POLY_FT4 *)(p - 0x16))->x0 = x;
                    ((POLY_FT4 *)(p - 0x16))->x2 = x;
                    ((POLY_FT4 *)(p - 0x16))->y0 = y;
                    ((POLY_FT4 *)(p - 0x16))->x1 = rightX;
                    ((POLY_FT4 *)(p - 0x16))->y1 = y;
                    ((POLY_FT4 *)(p - 0x16))->y2 = lineH;
                    ((POLY_FT4 *)(p - 0x16))->x3 = rightX;
                    asm("" : "=r"(x) : "0"(rightX));
                }
                ((POLY_FT4 *)(p - 0x16))->y3 = lineH;
                GraphicsAddPolyFT4((u8 *)D_800A8AC4);
                i++;
            }
        }
        D_800A8AC8[0] = D_800A34C8[0];
        D_800A8AC9[0] = D_800A34C8[1];
        D_800A8ACA[0] = D_800A34C8[2];
        SetSemiTrans(D_800A8AC8 - 4, 0);
        return;
    }
    if (mode == 1) {
        if (text[i] != 0) {
            p = D_800A8ADA;
            while (text[i] != 0) {
                s32 rightX;
                glyph = &gHudGlyphs[text[i]];
                ((POLY_FT4 *)(p - 0x16))->tpage =
                    GetTPage(0, 0, glyph->x, glyph->y);
                ((POLY_FT4 *)(p - 0x16))->u0 = glyph->u;
                ((POLY_FT4 *)(p - 0x16))->v0 = glyph->v;
                ((POLY_FT4 *)(p - 0x16))->u1 = glyph->u + *(u8 *)&glyph->width;
                ((POLY_FT4 *)(p - 0x16))->v1 = glyph->v;
                ((POLY_FT4 *)(p - 0x16))->u2 = glyph->u;
                ((POLY_FT4 *)(p - 0x16))->v2 = glyph->v + *(u8 *)&glyph->height;
                ((POLY_FT4 *)(p - 0x16))->u3 = glyph->u + *(u8 *)&glyph->width;
                ((POLY_FT4 *)(p - 0x16))->v3 = glyph->v + *(u8 *)&glyph->height;
                rightX = x + ((glyph->width * 3) >> 2);
                ((POLY_FT4 *)(p - 0x16))->x0 = x;
                ((POLY_FT4 *)(p - 0x16))->y0 = y;
                ((POLY_FT4 *)(p - 0x16))->y1 = y;
                ((POLY_FT4 *)(p - 0x16))->x2 = x;
                ySum = y + lineH;
                ((POLY_FT4 *)(p - 0x16))->y2 = ySum;
                ((POLY_FT4 *)(p - 0x16))->y3 = ySum;
                ((POLY_FT4 *)(p - 0x16))->x1 = rightX;
                ((POLY_FT4 *)(p - 0x16))->x3 = rightX;
                asm("" : "=r"(x) : "0"(rightX));
                GraphicsAddPolyFT4(p - 0x16);
                i++;
            }
        }
        return;
    }
    if (gTextColorS != 0) {
        if (text[i] != 0) {
            while (text[i] != 0) {
                s32 newX;
                s32 yy;
                glyph = &gHudGlyphs[text[i]];
                *(u16 *)D_800A8ADA = GetTPage(0, 0, glyph->x, glyph->y);
                width = (u16)glyph->width;
                w = width;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->u0 = glyph->u;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->v0 = glyph->v;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->u1 = glyph->u + w;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->v1 = glyph->v;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->u2 = glyph->u;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->v2 =
                    glyph->v + *(u8 *)&glyph->height;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->u3 = glyph->u + w;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->v3 =
                    glyph->v + *(u8 *)&glyph->height;
                newX = x + ((gTextColorS - (s16)width) >> 1);
                x = x + gTextColorS;
                cellRightX = width + newX;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->y0 = y;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->y1 = y;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->x0 = newX;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->x2 = newX;
                yy = y + lineH;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->x1 = cellRightX;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->y2 = yy;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->x3 = cellRightX;
                ((POLY_FT4 *)(D_800A8ADA - 0x16))->y3 = yy;
                GraphicsAddPolyFT4(D_800A8ADA - 0x16);
                i++;
            }
        }
        return;
    }
    if (text[i] != 0) {
        lineH = y + lineH;
        p = D_800A8ADA;
        while (text[i] != 0) {
            s32 rightX;
            u8 v3;
            glyph = &gHudGlyphs[text[i]];
            ((POLY_FT4 *)(p - 0x16))->tpage =
                GetTPage(0, 0, glyph->x, glyph->y);
            width = (u16)glyph->width;
            w = width;
            ((POLY_FT4 *)(p - 0x16))->u0 = glyph->u;
            ((POLY_FT4 *)(p - 0x16))->v0 = glyph->v;
            ((POLY_FT4 *)(p - 0x16))->u1 = glyph->u + w;
            ((POLY_FT4 *)(p - 0x16))->v1 = glyph->v;
            ((POLY_FT4 *)(p - 0x16))->u2 = glyph->u;
            ((POLY_FT4 *)(p - 0x16))->v2 = glyph->v + *(u8 *)&glyph->height;
            ((POLY_FT4 *)(p - 0x16))->u3 = glyph->u + w;
            v3 = glyph->v + *(u8 *)&glyph->height;
            rightX = x + width;
            ((POLY_FT4 *)(p - 0x16))->x0 = x;
            ((POLY_FT4 *)(p - 0x16))->x2 = x;
            ((POLY_FT4 *)(p - 0x16))->y0 = y;
            ((POLY_FT4 *)(p - 0x16))->x1 = rightX;
            ((POLY_FT4 *)(p - 0x16))->y1 = y;
            ((POLY_FT4 *)(p - 0x16))->y2 = lineH;
            ((POLY_FT4 *)(p - 0x16))->x3 = rightX;
            ((POLY_FT4 *)(p - 0x16))->y3 = lineH;
            asm("" : "=r"(x) : "0"(rightX));
            ((POLY_FT4 *)(p - 0x16))->v3 = v3;
            GraphicsAddPolyFT4(p - 0x16);
            i++;
        }
    }
}

/* Draws a race time at (x, y). Mode 1 counts 160 ticks per second and can
 * show hours; other modes count 20 ticks per second. Mode 2 randomises the
 * last two millisecond digits. */
void HudDrawTime(s32 time, s16 x, s16 y, s8 color, u8 mode) {
    char buf[16];
    s32 hours;
    s32 mins;
    s32 secs;
    s32 ms;

    hours = 0;
    gTextColor = (color == 1) ? 6 : 9;
    if (time == 0x7FFFFFFF) {
        HudDrawText(sHudTimeInvalidText, x, y, color);
        gTextColor = 0;
        return;
    }
    if ((s8)mode == 1) {
        hours = time / 576000;
        ms = time % 160 * 1000 / 160;
        mins = time / 9600 % 60;
        secs = time / 160 % 60;
    } else {
        mins = time / 1200;
        secs = time / 20 % 60;
        ms = time % 20 * 50;
    }
    if ((s8)mode == 2) {
        ms = ms / 100 * 100 + RandomScaledGet(100);
    }
    if (hours != 0) {
        sprintfRow(buf, sHudTimeFormatHms, hours, mins, secs);
    } else {
        sprintfRow(buf, sHudTimeFormatMinSecMs, mins, secs, ms);
    }
    HudDrawText(buf, x, y, color);
    gTextColor = 0;
}

extern s16 D_800A8AD2[];
void GraphicsInitializeTexturedQuad(void) {
    SetPolyFT4(D_800A8AC4);
    D_800A8AD2[0] = GetClut(0x390, 0x3C);
}

void GraphicsSetColor(u8 red, u8 green, u8 blue) {
    D_800A8AC8[0] = red;
    D_800A8AC9[0] = green;
    D_800A8ACA[0] = blue;
}

extern u8 D_80098D16[];
s32 HudTextWidth(u8 *str) {
    s32 sum;
    u8 c;
    s32 offset;

    sum = 0;
    if (*(volatile u8 *)str != 0) {
        c = *str;
        do {
            str++;
            offset = c;
            offset = offset - 0x20;
            offset = offset * 10;
            sum += *(s16 *)&D_80098D16[offset];
            c = *str;
        } while (c != 0);
    }
    return sum;
}

extern s32 D_800A2EFCLui[] asm("D_800A2EFC");
extern s32 D_800A2EFCSw[] asm("D_800A2EFC");
extern s32 D_800A2F00Lui[] asm("D_800A2F00");
extern s32 D_800A2EC4Lui[] asm("D_800A2EC4");
extern s8 D_800A34D4;
extern u8 D_800A3764;
extern u8 D_800A38B0;
extern u8 D_800A35D4;
extern u8 D_800A3414, D_800A3418, D_800A341C;
extern s32 D_800A35D0;
extern s16 D_800A35A4;
extern s16 D_800A34D8;
extern u8 D_800A34DC;
extern u8 D_800A8B30[], D_800A8B31[], D_800A8B32[];
void SceneSkyFadeDraw(void);
void SceneSetOverlayColor(u8, u8, u8);

void HudUpdateFlagOverlay(void) {
    Car *car;

    if (D_800A2EFCLui[0] != 0) {
        if (D_800A35D4 == 0) {
            if (D_800A372C == 0 || D_800A3764 != 0) {
                D_800A3414 = (u8)gPlayerCar[0]->unk209;
                gPlayerCar[0]->unk209 = (s8)(u8)gPlayerCar[0]->unk209 > 0;
                if (gSplitScreenMode[0] != 0) {
                    D_800A3418 = D_800A3428View[0x209];
                    D_800A3428View[0x209] = (s8)D_800A3428View[0x209] > 0;
                }
                if (gPlayerCar[0]->unk268 != 0) {
                    D_800A35D0 = gPlayerCar[0]->unk26C[13];
                } else {
                    D_800A35D0 = D_800A2EC4Lui[0];
                }
                D_800A2EC4Lui[0] = 0;
            }
            D_800A34D8 = 0x258;
            D_800A35D4 = 1;
            D_800A8B30[0] = 0x10;
            D_800A8B31[0] = 0x10;
            D_800A8B32[0] = 0x10;
            D_800A34DC = 1;
            D_800A341C = 1;
            switch (D_800A2F00Lui[0]) {
            case 1:
                SceneSetOverlayColor(0, 0xC0, 0);
                break;
            case 2:
                SceneSetOverlayColor(0xFF, 0xFF, 0xFF);
                break;
            case 3:
                SceneSetOverlayColor(0xFF, 0xFF, 0);
                break;
            }
            if (D_800A3910 == 0) {
                D_800A3910 = -1;
            }
        }
        if (D_800A341C != 0) {
            if (D_800A34D4 == 0) {
                switch (D_800A2F00Lui[0]) {
                case 1:
                    car = gPlayerCar[0];
                    func_80041564(car, D_800A35A4 != 0 ? 0x2B : 0x21);
                    break;
                case 2:
                    car = gPlayerCar[0];
                    func_80041564(car, 0x22);
                    break;
                case 3:
                    car = gPlayerCar[0];
                    if (car->unkF4 != 0) {
                        func_80041564(car, 0x2A);
                    }
                    break;
                }
                D_800A341C = 0;
            }
        }
        if (D_800A34D4 > 0) {
            D_800A34D4 -= 4;
        }
        SceneSkyFadeDraw();
        D_800A2EFCSw[0] = D_800A2EFCLui[0] - 1;
    } else if (D_800A34D4 < 0x50) {
        D_800A34D4 += 4;
        SceneSkyFadeDraw();
    } else if (D_800A35D4 != 0) {
        D_800A35D4 = 0;
        if (D_800A2EACAbsolute[0] == 0 && D_800A372C == 0) {
            gPlayerCar[0]->unk209 = D_800A3414;
            if (gSplitScreenMode[0] != 0) {
                D_800A3428View[0x209] = D_800A3418;
            }
            if (gPlayerCar[0]->unk268 == 0) {
                D_800A2EC4Lui[0] = D_800A35D0;
            }
        }
        if (D_800A3910 == -1 && D_800A2EACAbsolute[0] == 0 && D_800A38B0 == 0) {
            D_800A3910 = 0;
        }
    }
}

extern u8 D_800A39F8, D_800A38B8, D_800A3420;
extern u8 D_800A3564u asm("D_800A3564");
extern Car *D_800A3A64Car asm("D_800A3A64");
extern Car *gPlayerCarLui asm("gPlayerCarAbsolute");
extern Car *gCarListLui asm("gCarListAbsolute");
extern s32 D_800A2F00Sw[] asm("D_800A2F00");
extern void CarUpdateState(Car *);
void func_8005157C(void);

/* Runs the caution period. While D_800A3764 is set it starts the yellow
 * flag on the first frame, then updates every car and returns 1 until all
 * cars are settled and the 600-frame timer runs out. Afterwards it counts
 * down to the green flag. Returns 0 when racing runs normally. */
s32 RaceUpdateCaution(void) {
    Car *car;
    s8 side;
    s8 sideAhead;
    u8 done;
    s16 count;

    if (D_800A3764 != 0) {
        if (D_800A39F8 == 0) {
            Car *player;

            D_800A3564u = 1;
            D_800A34DC = 1;
            player = gPlayerCarLui;
            player->reverseSpeed = 0;
            player->unk120 = 0;
            gPlayerCarLui->draftTimer = 0;
            side = CarGetTrackSide(gPlayerCarLui, 0);
            if (side == 1) {
                gPlayerCarLui->unk26C[14] = 1;
            } else {
                sideAhead = CarGetTrackSide(gPlayerCarLui, 5);
                if (sideAhead == 1) {
                    if (side == 0 &&
                        (s8)CarGetTrackSide(gPlayerCarLui, 2) == sideAhead) {
                        D_800A38B8 = 1;
                    }
                    if (gPlayerCarLui->state == 5) {
                        gPlayerCarLui->unk26C[14] = 1;
                    }
                } else {
                    gPlayerCarLui->unk26C[14] = 0;
                }
            }
            gPlayerCarLui->sliding = 0;
            D_800A2F00Sw[0] = 3;
            D_800A3420 = gPlayerCarLui->automatic;
            gPlayerCarLui->automatic = 1;
            SoundStopConditionalSlots(0);
            D_800A35A4 = 600;
            D_800A39F8 = 1;
            D_800A38B0 = 1;
            D_800A372C = 1;
        } else {
            D_800A35A4--;
        }
        if (D_800A38B8 != 0 && (s8)CarGetTrackSide(gPlayerCarLui, 0) != 0) {
            D_800A38B8 = 0;
        }
        D_800A2EFCSw[0] = 1;
        if (gPlayerCarLui->unk268 == 0) {
            func_8002A1FC(gPlayerCarLui);
        }
        if (D_800A3564u != 0) {
            func_8005157C();
        }
        done = 1;
        for (car = D_800A3A64Car; car != NULL; car = (Car *)car->unk404) {
            CarUpdateState(car);
            func_800373B4(car);
            if (car->unkF4 != 0 && (car->unk3A4 & 0xF) != 0) {
                done = 0;
            }
            if (ABS(MathGetAngleDelta(car->heading,
                                      gTrackSections[0][car->segment].angle)) >
                0x40) {
                D_800A3564u = 1;
            }
        }
        func_80028FCC(gCarListLui);
        CarSetVelocityFromHeading(gPlayerCarLui, gPlayerCarLui->heading);
        if (done && D_800A35A4 <= 0) {
            D_800A3764 = 0;
            D_800A2EFCSw[0] = 0;
            D_800A38B8 = 0;
        }
        return 1;
    }
    if (D_800A39F8 != 0) {
        D_800A35A4 = 100;
        D_800A39F8 = 0;
    }
    count = D_800A35A4;
    if (count != 0) {
        if (count == 0x50) {
            D_800A2EFCSw[0] = count;
            D_800A2F00Sw[0] = 1;
        }
        D_800A35A4 = count - 1;
        if (D_800A35A4 > 0x28) {
            if (D_800A3564u != 0) {
                func_8005157C();
            }
            for (car = D_800A3A64Car; car != NULL; car = (Car *)car->unk404) {
                CarUpdateState(car);
                if (car != gPlayerCarLui) {
                    func_800373B4(car);
                } else if (D_800A35A4 < 0x32) {
                    car->automatic = D_800A3420;
                    car->update(car);
                } else {
                    func_800373B4(car);
                    CarSetVelocityFromHeading(gPlayerCarLui,
                                              gPlayerCarLui->heading);
                }
            }
            func_80028FCC(gCarListLui);
            return 1;
        }
        D_800A372C = 0;
        if (D_800A35A4 == 0) {
            D_800A38B0 = 0;
        }
    }
    if (D_800A3910 > 0) {
        D_800A3910--;
    }
    return 0;
}

extern u8 D_800A38E0;
extern u8 D_800A3A94;
extern u8 D_800A8AFC[], D_800A8B14[], D_800A8B2C[];
extern POLY_FT4 D_800A8B44[], D_800A8B6C[];
typedef struct TextureInfo {
    u16 tpx;
    u16 tpy;
    u16 clutX;
    u16 clutY;
    u16 u;
    u16 v;
    u16 u2;
    u16 v2;
    u16 u3;
    u16 v3;
} TextureInfo;
extern TextureInfo D_80090F96[];
extern u8 D_800A8B50[], D_800A8B51[], D_800A8B58[], D_800A8B59[];
extern u8 D_800A8B60[], D_800A8B61[], D_800A8B68[], D_800A8B69[];
extern u8 D_800A8B78[], D_800A8B79[], D_800A8B80[], D_800A8B81[];
extern u8 D_800A8B88[], D_800A8B89[], D_800A8B90[], D_800A8B91[];
extern u16 D_800A8B52[], D_800A8B7A[], D_800A8B5A[], D_800A8B82[];
extern s16 D_800A8AEC[], D_800A8AEE[], D_800A8AF0[], D_800A8AF2[];
extern s16 D_800A8AF4[], D_800A8AF6[], D_800A8AF8[], D_800A8AFA[];

void HudInitFlagOverlay(void) {
    u16 x;
    u16 y;

    D_800A34D4 = 0x50;
    D_800A3910 = -1;
    D_800A39F8 = 0;
    D_800A3764 = 0;
    D_800A38B0 = 0;
    D_800A372C = 0;
    D_800A38B8 = 0;
    D_800A35D4 = 0;
    D_800A38E0 = 1;
    D_800A3A94 = 1;
    D_800A35A4 = 0;
    SetPolyF4(D_800A8AFC);
    SetPolyF4(D_800A8B14);
    SetPolyF4(D_800A8B2C);
    SetPolyFT4(D_800A8B44);
    SetPolyFT4(D_800A8B6C);
    SetShadeTex(D_800A8B44, 1);
    SetShadeTex(D_800A8B6C, 1);
    D_800A8B5A[0] = GetTPage(0, 0, D_80090F96[0].tpx, D_80090F96[0].tpy);
    D_800A8B82[0] = GetTPage(0, 0, D_80090F96[0].tpx, D_80090F96[0].tpy);
    D_800A8B52[0] = GetClut(D_80090F96[0].clutX, D_80090F96[0].clutY);
    D_800A8B7A[0] = GetClut(D_80090F96[0].clutX, D_80090F96[0].clutY);
    x = D_80090F96[0].u;
    y = D_80090F96[0].v;
    D_800A8B50[0] = x;
    D_800A8B51[0] = y;
    D_800A8B59[0] = y;
    D_800A8B58[0] = x + 0x20;
    D_800A8B60[0] = x;
    D_800A8B61[0] = y + 0x18;
    D_800A8B68[0] = x + 0x20;
    D_800A8B69[0] = y + 0x18;
    D_800A8B78[0] = x;
    D_800A8B79[0] = y;
    D_800A8B80[0] = x + 0x20;
    D_800A8B81[0] = y;
    D_800A8B88[0] = x;
    D_800A8B89[0] = y + 0x18;
    D_800A8B90[0] = x + 0x20;
    D_800A8B91[0] = y + 0x18;
    D_800A8AEC[0] =
        (MathMultiplyFixed16(0x2D0000, gCosTableAbsolute[0][0x180]) >> 0x10) +
        0x122;
    D_800A8AEE[0] =
        (MathMultiplyFixed16(0x2D0000, gSinTableAbsolute[0][0x180]) >> 0x10) +
        0x3C;
    D_800A8AF0[0] =
        (MathMultiplyFixed16(0x140000, gCosTableAbsolute[0][0x180]) >> 0x10) +
        0x122;
    D_800A8AF2[0] =
        (MathMultiplyFixed16(0x140000, gSinTableAbsolute[0][0x180]) >> 0x10) +
        0x3C;
    D_800A8AF4[0] =
        (MathMultiplyFixed16(0x2D0000, gCosTableAbsolute[0][0x280]) >> 0x10) +
        0x122;
    D_800A8AF6[0] =
        (MathMultiplyFixed16(0x2D0000, gSinTableAbsolute[0][0x280]) >> 0x10) +
        0x3C;
    D_800A8AF8[0] =
        (MathMultiplyFixed16(0x140000, gCosTableAbsolute[0][0x280]) >> 0x10) +
        0x122;
    D_800A8AFA[0] =
        (MathMultiplyFixed16(0x140000, gSinTableAbsolute[0][0x280]) >> 0x10) +
        0x3C;
}

extern s8 D_800A34CC;
extern s8 D_800A34CD;
extern s8 D_800A34CE;
extern s8 D_800A34CF;
extern s8 D_800A34D0;
extern s8 D_800A34D1;
extern u8 D_800A8B00[];
extern u8 D_800A8B01[];
extern u8 D_800A8B02[];

void SceneSetOverlayColor(u8 arg0, u8 arg1, u8 arg2) {
    D_800A34CC = arg0;
    D_800A34CD = arg1;
    D_800A34CE = arg2;
    if (arg0 >= 0x40) {
        D_800A34CF = arg0 - 0x40;
    } else {
        D_800A34CF = 0;
    }
    if (arg1 >= 0x40) {
        D_800A34D0 = arg1 - 0x40;
    } else {
        D_800A34D0 = 0;
    }
    if (arg2 >= 0x40) {
        D_800A34D1 = arg2 - 0x40;
    } else {
        D_800A34D1 = 0;
    }
    D_800A8B00[0] = arg0;
    D_800A8B01[0] = arg1;
    D_800A8B02[0] = arg2;
}

extern s32 D_800A3598[];

/* The restart-order queue walks the section list (sectionLink) and
 * rebuilds the order into unk404/unk408. */

extern Car *D_800A37C0;
extern Car *D_800A3A64;
extern u8 D_800A3670;
extern s8 D_800A3564;

void func_8005157C(void) {
    Car *arr[0x60];
    Car *car;
    s32 playerDist;
    s8 i;
    s8 ahead;
    s8 behind;
    s8 flagged;
    s8 linked;
    s32 rnd;
    s8 dir;
    s32 pos;

    car = D_800A35E0[0];
    playerDist = (car->lap - 1) * gTrackSectionCount[0] + car->segment;
    ahead = 0;
    linked = 0;
    behind = 0;
    flagged = 0;
    D_800A37C0 = 0;
    D_800A3A64 = 0;
    D_800A3670 = 1;
    for (i = 0; i < 0x60; i++) {
        arr[i] = 0;
    }
    for (i = 0; i < D_800A2E94[0]; i++) {
        if (car->unkF4 != 0) {
            if (car->unk3A4 & 0xF) {
                arr[0x48 + flagged] = car;
                flagged++;
            } else if (car->unk26C[14] != 0) {
                arr[0x30 + linked] = car;
                linked++;
            } else {
                car->unk401 = 0;
                rnd = RandomScaledGet(0xA) + 0x14;
                car->unk400 = rnd;
                car->unk409 = rnd;
                if (D_800A3598[0] == 1) {
                    dir = -1;
                    if (D_800A2F84[0] != 0) {
                        dir = 1;
                    }
                    car->unk3FE = dir;
                    car->unk3FF = dir;
                    arr[ahead] = car;
                    ahead++;
                    if (D_800A3A64 == 0) {
                        car->unk401 = 1;
                        D_800A3A64 = car;
                    }
                } else if (playerDist <
                           car->lap * gTrackSectionCount[0] + car->segment) {
                    car->unk3FE = -1;
                    car->unk3FF = -1;
                    arr[ahead * 2] = car;
                    ahead++;
                    if (D_800A3A64 == 0) {
                        car->unk401 = 1;
                        D_800A3A64 = car;
                    }
                } else {
                    car->unk3FE = 1;
                    car->unk3FF = 1;
                    arr[behind * 2 + 1] = car;
                    behind++;
                    if (D_800A37C0 == 0) {
                        D_800A3670 = 0;
                        D_800A37C0 = car;
                    }
                }
            }
        }
        car = ((CarLink *)car->sectionLink.node.previous)->car;
    }
    if (D_800A3A64 == 0) {
        D_800A3A64 = gPlayerCar[0];
    }
    car = D_800A3A64;
    pos = 0;
    car->unk408 = -1;
    for (i = 1; i < 0x60; i++) {
        if (arr[i] != 0) {
            car->unk404 = arr[i];
            car = arr[i];
            car->unk408 = pos;
            pos++;
        }
    }
    car->unk404 = 0;
    D_800A3564 = 0;
}

extern u8 D_800A8B18[];
extern u8 D_800A8B19[];
extern u8 D_800A8B1A[];
extern u16 D_800A8B04[];
extern u16 D_800A8B0C[];
extern u16 D_800A8B0E[];
extern u16 D_800A8B10[];
extern u16 D_800A8B12[];
extern u16 D_800A8B1C[];
extern u16 D_800A8B1E[];
extern u16 D_800A8B20[];
extern u16 D_800A8B22[];
extern u16 D_800A8B24[];
extern u16 D_800A8B26[];
extern u16 D_800A8B28[];
extern u16 D_800A8B2A[];
extern u16 D_800A8B34[];
extern u16 D_800A8B36[];
extern u16 D_800A8B38[];
extern u16 D_800A8B3A[];
extern u16 D_800A8B3C[];
extern u16 D_800A8B3E[];
extern u16 D_800A8B40[];
extern u16 D_800A8B42[];
extern u16 D_800A8B4C[];
extern u16 D_800A8B5C[];
extern u16 D_800A8B5E[];
extern u16 D_800A8B64[];
extern u16 D_800A8B66[];
extern u16 D_800A8B74[];
extern u16 D_800A8B76[];
extern u16 D_800A8B7C[];
extern u16 D_800A8B7E[];
extern u16 D_800A8B84[];
extern u16 D_800A8B86[];
extern u16 D_800A8B8C[];
extern u16 D_800A8B8E[];
extern s32 D_8009937C[];
extern s32 D_80099380[];
extern s32 D_80099384[];
extern s32 D_80099394[];
extern s32 D_800993A4[];
extern s32 D_800993B4[];
extern s32 D_800A2DF4Absolute[];
extern s32 D_800A2DF0Absolute[];
extern s32 gOrderingTableBankSmall[];
void SceneSkyFadeDraw(void) {
    extern s32 D_800A2F00wC[] asm("D_800A2F00");
    extern s32 gCosTablewC[] asm("gCosTable");
    extern u8 *gSinTablewC[] asm("gSinTable");

    extern u8 *gSinTableNext[] asm("gSinTable.NON_MATCHING");

    /* The homes follow the observed stack offsets. The tail is compiler storage. */
    struct {
        s16 buf[8];
        u16 fadeVal;
        u8 reserved12[6];
        s32 entryA;
        s32 reserved1C;
        s32 entryB;
        u8 reserved24[20];
    } home;
    typedef char SkyFadeHomesSizeCheck[(sizeof(home) == 0x38) ? 1 : -1];
    register s32 argument asm("$4");
    register s32 result asm("$2");
    register s32 byteValue asm("$3");
    register s32 factor asm("$5");
    register s32 idx asm("$16");
    register s32 shade asm("$17");
    register u8 switched asm("$19");
    s32 gradA;
    s32 gradB;
    register s32 yBase asm("$23");
    s32 yStep;
    s32 m;
    s32 bank;

    /* shortcut: these pins require the qualified PSX compiler. Replace them
     * when a pure C form produces the same bytes. */
    switched = 0;
    /* The two fade directions use mirrored colors and screen offsets. */
    if (D_800A34DC != 0) {
        {
            u8 *table;
            s32 level;

            result = D_800A34D8;
            level = result;
            asm("" : "=r"(level) : "0"(level));

            if (result >= 0x259) {
                result = 0x500 - level;
                home.fadeVal = result;
                result += 0x200;
                idx = result & 0x3FF;
                shade = 0x140000;
                D_800A8B30[0] = 0x10;
                D_800A8B31[0] = 0x10;
                D_800A8B32[0] = 0x10;
                D_800A8B00[0] = D_800A34CC;
                D_800A8B01[0] = D_800A34CD;
                D_800A8B02[0] = D_800A34CE;
                D_800A8B18[0] = D_800A34CF;
                D_800A8B19[0] = D_800A34D0;
                D_800A8B1A[0] = D_800A34D1;
                switched = 1;
            } else {
                result = level + 0x200;
                idx = result & 0x3FF;
                shade = 0xFFEC0000;
            }
            result = (u8)D_800A34D4;
            argument = D_800A34D8;
            asm("" : "=r"(result) : "0"(result), "r"(argument));
            result = (s8)result;
            yBase = result + 0x122;
            result = 0x280 - argument;
            yStep = 0x3C;
            if (result >= 0) {
                table = gSinTablewC[0];
            } else {
                table = gSinTablewC[0];
                result = argument - 0x280;
            }
            result <<= 4;
            table += result;
            argument = *(s32 *)table;
        }
        result = MathMultiplyFixed16(argument, 0x80000);
        {
            u8 *table;

            argument = D_800A34D8;
            byteValue = 0x2D0000;
            gradA = result + byteValue;
            result = 0x280 - argument;
            if (result >= 0) {
                result <<= 4;
                table = gSinTablewC[0];
            } else {
                table = gSinTablewC[0];
                result = (argument - 0x280) << 4;
            }
            asm("" : "=r"(table) : "0"(table), "r"(result));
            table += result;
            argument = *(s32 *)table;
        }
        result = MathMultiplyFixed16(argument, 0x40000);
        byteValue = 0x140000;
        gradB = result + byteValue;
        result = switched & 0xFF;
        if (result != 0) {
            D_800A34D8 -= 8;
        } else {
            D_800A34D8 -= 0x10;
        }
        result = D_800A34D8;
        if (result < 0x181) {
            D_800A34D8 = 0x180;
            D_800A34DC = 0;
        }
    } else {
        {
            s32 level;
            u8 topRed, topGreen, topBlue;
            u8 bottomRed, bottomGreen, bottomBlue;
            result = D_800A34D8;
            level = result;
            asm("" : "=r"(level) : "0"(level));
            if (result < 0x1A8) {
                result = 0x300 - level;
                home.fadeVal = result;
                result += 0x200;
                idx = result & 0x3FF;
                topRed = D_800A34CF;
                topGreen = D_800A34D0;
                topBlue = D_800A34D1;
                bottomRed = D_800A34CC;
                bottomGreen = D_800A34CD;
                bottomBlue = D_800A34CE;
                shade = 0xFFEC0000;
                D_800A8B30[0] = 0;
                D_800A8B31[0] = 0;
                D_800A8B32[0] = 0;
                D_800A8B00[0] = topRed;
                D_800A8B01[0] = topGreen;
                D_800A8B02[0] = topBlue;
                D_800A8B18[0] = bottomRed;
                D_800A8B19[0] = bottomGreen;
                D_800A8B1A[0] = bottomBlue;
                switched = 1;
            } else {
                result = level + 0x200;
                idx = result & 0x3FF;
                shade = 0x140000;
            }
            result = D_800A34D8;
            factor = 0x80000;
            asm("" : "=r"(result), "=r"(factor) : "0"(result), "1"(factor));
            argument = (s32)gSinTablewC[0];
            byteValue = (u8)D_800A34D4;
            asm(""
                : "=r"(argument), "=r"(byteValue)
                : "0"(argument), "1"(byteValue));
            result -= 0x180;
            result <<= 4;
            result += argument;
            argument = *(s32 *)result;
            byteValue = (s8)byteValue;
            yBase = byteValue + 0x122;
        }
        result = MathMultiplyFixed16(argument, factor);
        {

            do {
                byteValue = D_800A34D8;
            } while (0);

            argument = (s32)gSinTableNext[0];
            asm(""
                : "=r"(byteValue), "=r"(argument)
                : "0"(byteValue), "1"(argument), "r"(result));
            do {
                yStep = 0x3C;
            } while (0);

            byteValue -= 0x180;
            byteValue <<= 4;
            byteValue += argument;
            argument = *(s32 *)byteValue;
            factor = 0x40000;
            byteValue = 0x2D0000;
            asm(""
                : "=r"(factor), "=r"(byteValue)
                : "0"(factor), "1"(byteValue), "r"(argument), "r"(result));
            gradA = result + byteValue;
            result = MathMultiplyFixed16(argument, factor);
        }
        byteValue = 0x140000;
        gradB = result + byteValue;
        result = switched & 0xFF;
        if (result != 0) {
            D_800A34D8 += 8;
        } else {
            D_800A34D8 += 0x10;
        }
        result = D_800A34D8;
        if (result >= 0x280) {
            D_800A34D8 = 0x280;
            D_800A34DC = 1;
        }
    }
    factor = D_800A34D8;
    byteValue = gCosTablewC[0];
    argument = (s32)gSinTablewC[0];
    result = factor << 2;
    byteValue = result + byteValue;
    byteValue = *(s32 *)byteValue;
    result += argument;
    home.entryA = byteValue;
    result = *(s32 *)result;
    home.entryB = result;
    result = factor - 0x200;
    if (result >= 0) {
        result = 0x380;
        argument = result - factor;
    } else {
        argument = factor - 0x80;
    }
    result = MathFixedDivide(argument, 0x180);
    shade = MathMultiplyFixed16(shade, result);
    {
        register s32 t2 asm("$18");
        register u16 *primitive asm("$20");
        if (D_800A2F00wC[0] == 0) {
            result = MathMultiplyFixed16(gradA, home.entryA);
            argument = gradA;
            factor = home.entryB;
            primitive = D_800A8B4C;
            asm(""
                : "=r"(factor), "=r"(primitive)
                : "0"(factor), "1"(primitive), "r"(argument), "r"(result));
            primitive[0] = yBase + (result >> 16);
            result = MathMultiplyFixed16(argument, factor);
            factor = home.entryA;
            argument = gradB;
            primitive[1] = yStep + (result >> 16);
            result = MathMultiplyFixed16(argument, factor);
            factor = home.entryB;
            argument = gradB;
            primitive[4] = yBase + (result >> 16);
            result = MathMultiplyFixed16(argument, factor);
            {
                s32 tableAddress;
                tableAddress = (s32)gSinTablewC[0];
                result = yStep + (result >> 16);
                idx <<= 2;
                primitive[5] = result;
                /* Preserve the retail operand order of this commutative add. */
                tableAddress = (s32)((u32)idx - -(u32)tableAddress);
                argument = *(s32 *)tableAddress;
            }
            result = MathMultiplyFixed16(argument, shade);
            {
                s32 tableAddress;
                tableAddress = gCosTablewC[0];
                idx += tableAddress;
                argument = *(s32 *)idx;
                factor = shade;
            }
            t2 = result >> 16;
            m = MathMultiplyFixed16(argument, factor);
            shade = m >> 16;
            result = switched & 0xFF;
            {
                register s32 xShift asm("$7");
                xShift = t2 << 24;
                if (result != 0) {
                    u16 *secondPrimitive;
                    {
                        register s32 paletteOffset asm("a1");
                        register s32 screenShift asm("a0");
                        s32 value;
                        register u32 fade asm("t4");
                        paletteOffset = D_800A34DC;
                        screenShift = (u8)D_800A34D4;
                        paletteOffset <<= 3;
                        value = *(u16 *)((u8 *)D_800A8AEC + paletteOffset);
                        secondPrimitive = D_800A8B74;
                        screenShift <<= 24;
                        result = (s32)screenShift >> 24;
                        value += result;
                        secondPrimitive[0] = value;
                        D_800A8B5C[0] = value;
                        result = *(u16 *)((u8 *)D_800A8AEE + paletteOffset);
                        D_800A8B76[0] = result;
                        D_800A8B5E[0] = result;
                        result = *(u16 *)((u8 *)D_800A8AF0 + paletteOffset);
                        fade = home.fadeVal;
                        asm(""
                            : "=r"(screenShift), "=r"(fade)
                            : "0"(screenShift), "1"(fade));
                        screenShift >>= 24;
                        result += screenShift;
                        D_800A8B7C[0] = result;
                        D_800A8B64[0] = result;
                        result = gCosTablewC[0];
                        value = *(u16 *)((u8 *)D_800A8AF2 + paletteOffset);
                        idx = (s32)(fade << 16) >> 14;
                        asm("" : : "r"(fade));
                        result = idx + result;
                        D_800A8B7E[0] = value;
                        D_800A8B66[0] = value;
                        factor = *(s32 *)result;
                    }
                    result = MathMultiplyFixed16(gradA, factor);
                    {
                        register s32 table asm("v1");
                        asm("" : "=r"(t2) : "0"(t2), "r"(result));
                        t2 <<= 24;
                        argument = t2 >> 24;
                        asm(""
                            : "=r"(t2), "=r"(argument)
                            : "0"(t2), "1"(argument));
                        table = (s32)gSinTablewC[0];
                        result >>= 16;
                        result = yBase + result;
                        result -= argument;
                        D_800A8B84[0] = result;
                        table = idx + table;
                        factor = *(s32 *)table;
                    }
                    result = MathMultiplyFixed16(gradA, factor);
                    {
                        shade <<= 24;
                        byteValue = shade >> 24;
                        asm(""
                            : "=r"(shade), "=r"(byteValue)
                            : "0"(shade), "1"(byteValue));
                        argument = gCosTablewC[0];
                        result >>= 16;
                        result = yStep + result;
                        byteValue += result;
                        D_800A8B86[0] = byteValue;
                        argument = idx + argument;
                        factor = *(s32 *)argument;
                    }
                    m = MathMultiplyFixed16(gradB, factor);
                    t2 >>= 24;
                    D_800A8B8C[0] = yBase + (m >> 16) - t2;
                    idx += (s32)gSinTablewC[0];
                    result = MathMultiplyFixed16(gradB, *(s32 *)idx);
                    shade >>= 24;
                    idx = (s32)primitive - 8;
                    result >>= 16;
                    result = yStep + result;
                    shade += result;
                    D_800A8B8E[0] = shade;
                    GraphicsAddPolyFT4((u8 *)idx);
                    GraphicsAddPolyFT4((u8 *)secondPrimitive - 8);
                    if (gSplitScreenModeAbsolute[0] != 0) {
                        gOrderingTableBankAbsolute3[0] =
                            gOrderingTableBankAbsolute4[0] + 1;
                        gOrderingTableAbsolute6[0] =
                            gOrderingTableAbsolute7[0] + 0x1004;
                        GraphicsAddPolyFT4((u8 *)idx);
                        GraphicsAddPolyFT4((u8 *)secondPrimitive - 8);
                        gOrderingTableBankSmall[0] =
                            gOrderingTableBankAbsolute[0] - 1;
                        gOrderingTableAbsolute5[0] =
                            gOrderingTableAbsolute4[0] - 0x1004;
                    }
                } else {
                    {
                        register s32 dx asm("t1");
                        s32 dy;
                        register s32 yBits asm("t0");
                        register u32 x0 asm("v0");
                        register u32 y0 asm("v1");
                        register u32 x1 asm("a1");
                        register u32 y1 asm("a2");
                        dx = xShift >> 24;
                        yBits = shade << 24;
                        dy = yBits >> 24;
                        asm(""
                            : "=r"(xShift), "=r"(yBits)
                            : "0"(xShift), "1"(yBits), "r"(dx), "r"(dy));
                        xShift >>= 24;
                        yBits >>= 24;
                        x0 = primitive[0];
                        y0 = primitive[1];
                        x1 = primitive[4];
                        y1 = primitive[5];
                        idx = (s32)primitive - 8;
                        D_800A8B5C[0] = x0 - dx;
                        D_800A8B5E[0] = y0 + dy;
                        D_800A8B64[0] = x1 - xShift;
                        D_800A8B66[0] = y1 + yBits;
                    }
                    argument = idx;
                    GraphicsAddPolyFT4((u8 *)argument);
                    if (gSplitScreenModeAbsolute[0] != 0) {
                        gOrderingTableBankAbsolute3[0] =
                            gOrderingTableBankAbsolute4[0] + 1;
                        gOrderingTableAbsolute6[0] =
                            gOrderingTableAbsolute7[0] + 0x1004;
                        GraphicsAddPolyFT4((u8 *)idx);
                        gOrderingTableBankSmall[0] =
                            gOrderingTableBankAbsolute[0] - 1;
                        gOrderingTableAbsolute5[0] =
                            gOrderingTableAbsolute4[0] - 0x1004;
                    }
                }
            }
        } else {
            result = MathMultiplyFixed16(gradA, home.entryA);
            argument = gradA;
            factor = home.entryB;
            primitive = D_800A8B04;
            asm(""
                : "=r"(factor), "=r"(primitive)
                : "0"(factor), "1"(primitive), "r"(argument), "r"(result));
            primitive[0] = yBase + (result >> 16);
            result = MathMultiplyFixed16(argument, factor);
            factor = home.entryA;
            argument = gradB;
            primitive[1] = yStep + (result >> 16);
            result = MathMultiplyFixed16(argument, factor);
            factor = home.entryB;
            argument = gradB;
            primitive[2] = yBase + (result >> 16);
            result = MathMultiplyFixed16(argument, factor);
            {
                s32 tableAddress;
                tableAddress = (s32)gSinTablewC[0];
                result = yStep + (result >> 16);
                idx <<= 2;
                primitive[3] = result;
                /* Preserve the retail operand order of this commutative add. */
                tableAddress = (s32)((u32)idx - -(u32)tableAddress);
                argument = *(s32 *)tableAddress;
            }
            result = MathMultiplyFixed16(argument, shade);
            {
                s32 tableAddress;
                tableAddress = gCosTablewC[0];
                idx += tableAddress;
                argument = *(s32 *)idx;
                factor = shade;
            }
            t2 = result >> 16;
            m = MathMultiplyFixed16(argument, factor);
            shade = m >> 16;
            result = switched & 0xFF;
            {
                register s32 xShift asm("$7");
                xShift = t2 << 24;
                if (result != 0) {
                    u16 *secondPrimitive;
                    {
                        register s32 paletteOffset asm("a1");
                        register s32 screenShift asm("a0");
                        s32 value;
                        register u32 fade asm("t4");
                        paletteOffset = D_800A34DC;
                        screenShift = (u8)D_800A34D4;
                        paletteOffset <<= 3;
                        value = *(u16 *)((u8 *)D_800A8AEC + paletteOffset);
                        secondPrimitive = D_800A8B1C;
                        screenShift <<= 24;
                        result = (s32)screenShift >> 24;
                        value += result;
                        secondPrimitive[0] = value;
                        D_800A8B0C[0] = value;
                        result = *(u16 *)((u8 *)D_800A8AEE + paletteOffset);
                        D_800A8B1E[0] = result;
                        D_800A8B0E[0] = result;
                        result = *(u16 *)((u8 *)D_800A8AF0 + paletteOffset);
                        fade = home.fadeVal;
                        asm(""
                            : "=r"(screenShift), "=r"(fade)
                            : "0"(screenShift), "1"(fade));
                        screenShift >>= 24;
                        result += screenShift;
                        D_800A8B20[0] = result;
                        D_800A8B10[0] = result;
                        result = gCosTablewC[0];
                        value = *(u16 *)((u8 *)D_800A8AF2 + paletteOffset);
                        idx = (s32)(fade << 16) >> 14;
                        asm("" : : "r"(fade));
                        result = idx + result;
                        D_800A8B22[0] = value;
                        D_800A8B12[0] = value;
                        factor = *(s32 *)result;
                    }
                    result = MathMultiplyFixed16(gradA, factor);
                    {
                        register s32 table asm("v1");
                        asm("" : "=r"(t2) : "0"(t2), "r"(result));
                        t2 <<= 24;
                        argument = t2 >> 24;
                        asm(""
                            : "=r"(t2), "=r"(argument)
                            : "0"(t2), "1"(argument));
                        table = (s32)gSinTablewC[0];
                        result >>= 16;
                        result = yBase + result;
                        result -= argument;
                        D_800A8B24[0] = result;
                        table = idx + table;
                        factor = *(s32 *)table;
                    }
                    result = MathMultiplyFixed16(gradA, factor);
                    {
                        shade <<= 24;
                        byteValue = shade >> 24;
                        asm(""
                            : "=r"(shade), "=r"(byteValue)
                            : "0"(shade), "1"(byteValue));
                        argument = gCosTablewC[0];
                        result >>= 16;
                        result = yStep + result;
                        byteValue += result;
                        D_800A8B26[0] = byteValue;
                        argument = idx + argument;
                        factor = *(s32 *)argument;
                    }
                    m = MathMultiplyFixed16(gradB, factor);
                    t2 >>= 24;
                    D_800A8B28[0] = yBase + (m >> 16) - t2;
                    idx += (s32)gSinTablewC[0];
                    result = MathMultiplyFixed16(gradB, *(s32 *)idx);
                    shade >>= 24;
                    idx = (s32)primitive - 8;
                    result >>= 16;
                    result = yStep + result;
                    shade += result;
                    D_800A8B2A[0] = shade;
                    GraphicsAddPolyFT4((u8 *)idx);
                    GraphicsAddPolyFT4((u8 *)secondPrimitive - 8);
                    if (gSplitScreenModeAbsolute[0] != 0) {
                        gOrderingTableBankAbsolute3[0] =
                            gOrderingTableBankAbsolute4[0] + 1;
                        gOrderingTableAbsolute6[0] =
                            gOrderingTableAbsolute7[0] + 0x1004;
                        GraphicsAddPolyFT4((u8 *)idx);
                        GraphicsAddPolyFT4((u8 *)secondPrimitive - 8);
                        gOrderingTableBankSmall[0] =
                            gOrderingTableBankAbsolute[0] - 1;
                        gOrderingTableAbsolute5[0] =
                            gOrderingTableAbsolute4[0] - 0x1004;
                    }
                } else {
                    {
                        register s32 dx asm("t1");
                        s32 dy;
                        register s32 yBits asm("t0");
                        register u32 x0 asm("v0");
                        register u32 y0 asm("v1");
                        register u32 x1 asm("a1");
                        register u32 y1 asm("a2");
                        dx = xShift >> 24;
                        yBits = shade << 24;
                        dy = yBits >> 24;
                        asm(""
                            : "=r"(xShift), "=r"(yBits)
                            : "0"(xShift), "1"(yBits), "r"(dx), "r"(dy));
                        xShift >>= 24;
                        yBits >>= 24;
                        x0 = primitive[0];
                        y0 = primitive[1];
                        x1 = primitive[2];
                        y1 = primitive[3];
                        idx = (s32)primitive - 8;
                        argument = idx;
                        D_800A8B0C[0] = x0 - dx;
                        D_800A8B0E[0] = y0 + dy;
                        D_800A8B10[0] = x1 - xShift;
                        D_800A8B12[0] = y1 + yBits;
                    }
                    GraphicsAddPolyFT4((u8 *)argument);
                    if (gSplitScreenModeAbsolute[0] != 0) {
                        gOrderingTableBankAbsolute3[0] =
                            gOrderingTableBankAbsolute4[0] + 1;
                        gOrderingTableAbsolute6[0] =
                            gOrderingTableAbsolute7[0] + 0x1004;
                        GraphicsAddPolyFT4((u8 *)idx);
                        gOrderingTableBankSmall[0] =
                            gOrderingTableBankAbsolute[0] - 1;
                        gOrderingTableAbsolute5[0] =
                            gOrderingTableAbsolute4[0] - 0x1004;
                    }
                }
            }
        }
    }
    {
        /* Rotate the four sky corners around the screen origin. */
        s32 loopI;
        register s32 signedI asm("s1");
        register s32 lookupOffset asm("s2");
        s16 *buf;
        register s32 accum asm("s0");
        s32 argA;
        s32 argB;
        register s32 scratch0 asm("v0");
        register s32 scratch1 asm("v1");
        s32 callOut;
        s32 nextI;
        loopI = 0;
        D_800993B4[0] = gradB;
        D_800993A4[0] = gradB;
        D_80099394[0] = gradB;
        D_80099384[0] = gradB;
    gradLoop:
        scratch0 = D_800A34DC;
        signedI = (s8)loopI;
        lookupOffset = signedI << 3;
        argA = home.entryA;
        scratch0 <<= 5;
        scratch0 = lookupOffset + scratch0;
        argB = *(s32 *)((u8 *)D_8009937C + scratch0);
        signedI <<= 2;
        callOut = MathMultiplyFixed16(argA, argB);
        scratch1 = D_800A34DC;
        argA = home.entryB;
        scratch1 <<= 5;
        scratch1 = lookupOffset + scratch1;
        argB = *(s32 *)((u8 *)D_80099380 + scratch1);
        accum = callOut;
        callOut = MathMultiplyFixed16(argA, argB);
        buf = (s16 *)((u8 *)home.buf + signedI);
        asm(""
            : "=r"(buf), "=r"(accum)
            : "0"(buf), "1"(accum), "r"(callOut)
            : "memory");
        scratch1 = D_800A34DC;
        accum -= callOut;
        accum >>= 16;
        accum = yBase + accum;
        buf[0] = accum;
        argA = home.entryB;
        scratch1 <<= 5;
        scratch1 = lookupOffset + scratch1;
        argB = *(s32 *)((u8 *)D_8009937C + scratch1);
        callOut = MathMultiplyFixed16(argA, argB);
        scratch1 = D_800A34DC;
        argA = home.entryA;
        scratch1 <<= 5;
        lookupOffset += scratch1;
        argB = *(s32 *)((u8 *)D_80099380 + lookupOffset);
        accum = callOut;
        callOut = MathMultiplyFixed16(argA, argB);
        nextI = loopI + 1;
        do {
            loopI = nextI;
        } while (0);

        accum += callOut;
        accum >>= 16;
        accum = yStep + accum;
        buf[1] = accum;
        if ((s8)nextI < 4)
            goto gradLoop;
    }
    D_800A8B34[0] = home.buf[0];
    D_800A8B36[0] = home.buf[1];
    D_800A8B38[0] = home.buf[2];
    D_800A8B3A[0] = home.buf[3];
    D_800A8B3C[0] = home.buf[4];
    D_800A8B3E[0] = home.buf[5];
    D_800A8B40[0] = home.buf[6];
    D_800A8B42[0] = home.buf[7];
    GraphicsAddPolyFT4((u8 *)D_800A8B34 - 8);
    GraphicsDrawRect((s8)D_800A34D4 + 0xEB, 0x14, 0x46, 0x50, 0, 0, 0, 1);
    if (gSplitScreenModeAbsolute[0] != 0) {
        gOrderingTableBankAbsolute3[0] = gOrderingTableBankAbsolute4[0] + 1;
        gOrderingTableAbsolute6[0] = gOrderingTableAbsolute7[0] + 0x1004;
        GraphicsAddPolyFT4((u8 *)D_800A8B34 - 8);
        GraphicsDrawRect((s8)D_800A34D4 + 0xEB, 0x14, 0x46, 0x50, 0, 0, 0, 1);
        bank = gOrderingTableBankAbsolute[0] - 1;
        gOrderingTableBankSmall[0] = bank;
        gOrderingTableAbsolute5[0] = gOrderingTableAbsolute4[0] - 0x1004;
    }
}

extern s8 D_800A34E4;
extern SkidMark *gSkidMarks;
extern u8 D_80090F7A[];

void func_800524A0(Car *car, s8 arg1) {
    Wheel *wheel;
    u8 *table;
    SkidMark *entry;
    u16 w;
    u32 v;
    s32 m2;

    wheel = &car->wheel[arg1];
    m2 = wheel->skidMark;
    wheel->unk24 = 0;
    wheel->skidding = 0;
    D_800A34E4 = 0;
    if (m2 != -1) {
        table = D_80090F7A;
        w = wheel->surface;
        entry = &gSkidMarks[m2];
        if (w == 2) {
            table += 0xE;
        }
        entry->face.clut = GetClut(((SceneTexture *)table)->clutX,
                                   ((SceneTexture *)table)->clutY);
        entry->face.tpage = GetTPage(((SceneTexture *)table)->tpage, 0,
                                     ((SceneTexture *)table)->tpx,
                                     ((SceneTexture *)table)->tpy);
        v = ((SceneTexture *)table)->u + 0x3F;
        entry->face.u1 = v;
        entry->face.u0 = v;
        v = ((SceneTexture *)table)->u;
        entry->face.u3 = v;
        entry->face.u2 = v;
        v = ((SceneTexture *)table)->v;
        entry->face.v2 = v;
        entry->face.v0 = v;
        v = ((SceneTexture *)table)->v + 0x1F;
        entry->face.v3 = v;
        entry->face.v1 = v;
    }
}

extern s16 D_800A34E8;
extern u8 D_80090F5E[], D_80090F6C[], D_80090F88[];

/* Retail's frame has 8 dead bytes between `m` and `rot`: the address-taken
 * `padRot`, referenced only inside `if (0)`, keeps that slot. The block
 * locals below are load-bearing. Retail computes each table slot as
 * index + base into a block-local register, and the pins and the two
 * `asm` statements reproduce the register choice and the store order
 * that sched1 picks there. */
void func_800525A8(Car *arg0, s8 arg1) {
    s16 coords[3][4];
    VECTOR vec;
    MATRIX m;
    SVECTOR padRot;
    s32 xoff;
    s32 d;
    SVECTOR rot;
    VECTOR out;
    long flag;
    Wheel *entry;
    s32 diff;
    Wheel *e;
    s32 m2;
    u16 w;
    SkidMark *tex;
    SkidMark *tex2;
    u8 *q;
    u8 *p;
    u32 v;
    s8 side1;
    s8 side2;
    u8 *new_var4;
    s32 *ref;
    s8 i;
    SceneTexture *tim;
    u8 u;
    u8 uv;
    SkidMark *node;

    diff = (u16)arg0->movementHeading - (u16)arg0->heading;
    entry = (u8 *)arg0 + (arg1 * 0x28 + 0x2AC);
    if (arg0->frontRightContact == 0 || arg0->frontLeftContact == 0 ||
        arg0->rearRightContact == 0 || arg0->rearLeftContact == 0) {
        for (i = 0; i < 4; i++) {
            u8 *row;

            row = (u8 *)arg0 + i * 0x28;
            if (row[0x2CC] != 0) {
                e = (u8 *)arg0 + (i * 0x28 + 0x2AC);
                m2 = e->skidMark;
                e->unk24 = 0;
                e->skidding = 0;
                D_800A34E4 = 0;
                if (m2 != -1) {
                    d = (s32)D_80090F7A;
                    p = (u8 *)d + 0xA;
                    asm("" : "=r"(q) : "0"((u8 *)d));
                    tex = &gSkidMarks[m2];
                    w = e->surface;
                    if (w == 2) {
                        p = q + 0x18;
                        q += 0xE;
                    }
                    tex->face.clut =
                        GetClut(((SceneTexture *)(p - 0xA))->clutX,
                                ((SceneTexture *)(p - 0xA))->clutY);
                    tex->face.tpage =
                        GetTPage(((SceneTexture *)(p - 0xA))->tpage, 0,
                                 *(u16 *)q, ((SceneTexture *)(p - 0xA))->tpy);
                    v = ((SceneTexture *)(p - 0xA))->u + 0x3F;
                    tex->face.u1 = v;
                    tex->face.u0 = v;
                    v = ((SceneTexture *)(p - 0xA))->u;
                    tex->face.u3 = v;
                    tex->face.u2 = v;
                    v = ((SceneTexture *)(p - 0xA))->v;
                    tex->face.v2 = v;
                    tex->face.v0 = v;
                    v = ((SceneTexture *)(p - 0xA))->v + 0x1F;
                    tex->face.v3 = v;
                    tex->face.v1 = v;
                }
            }
        }
        return;
    }
    if (arg1 == 0) {
        if (entry->skidding == 0 && arg0->steering != 0 && D_800A34E4 == 0) {
            if (arg0->steering > 0) {
                D_800A34E4 = 1;
            }
            if (arg0->steering < 0) {
                D_800A34E4 = -1;
            }
        } else {
            D_800A34E4 = 0;
        }
    }
    switch (arg1) {
    case 2:
        d = (s16)diff;
        if (d < 0) {
            d = -d;
        }
        side2 = 1;
        if (d < 0x40) {
            arg0->wheel[2].skidding = 0;
            return;
        }
        side1 = 1;
        break;
    case 3:
        d = (s16)diff;
        if (d < 0) {
            d = -d;
        }
        side1 = 1;
        if (d < 0x40) {
            arg0->wheel[3].skidding = 0;
            return;
        }
        side2 = -1;
        break;
    case 0:
        if (D_800A34E4 < 0) {
            return;
        }
        side1 = -1;
        side2 = 1;
        break;
    case 1:
        if (D_800A34E4 > 0) {
            return;
        }
        side2 = -1;
        side1 = -1;
        break;
    default:
        return;
    }
    rot.vx = 0;
    rot.vy = diff * 4;
    rot.vz = 0;
    RotMatrix(&rot, &m);
    SetRotMatrix(&m);
    if (0) {
        RotMatrix(&padRot, &m);
    }
    i = 0;
    xoff = side1 * 220;
    ref = D_800AE844;
loop2:
    if (i == 0) {
        rot.vx = 0x28;
    } else {
        rot.vx = -0x28;
    }
    rot.vy = 0;
    rot.vz = 0;
    RotTrans(&rot, &out, &flag);
    vec.vx = xoff + out.vz;
    vec.vy = side2 * 120 + out.vx;
    vec.vz = 0;
    MatrixTransformVector((s32 *)&vec);
    {
        register s16 *c asm("$5");

#ifdef NATIVE
        /* Retail's spelling below adds coords to a null-based pointer,
         * which clang may drop as undefined behaviour. */
        c = (s16 *)coords + i;
#else
        c = (s16 *)(i * 2);
        c = (s16 *)((u8 *)c + (s32)coords);
#endif
        c[0] = ((arg0->pos.x + vec.vx) >> 2) - ref[0];
        c[4] = ((arg0->pos.y + vec.vy) >> 2) - ref[1];
        c[8] = ((arg0->pos.z + vec.vz) >> 2) - ref[2];
    }
    i++;
    if (i < 2) {
        goto loop2;
    }
    if (entry->skidding == 0) {
        entry->edge0[0] = coords[0][0];
        entry->edge0[1] = coords[1][0];
        entry->edge0[2] = coords[2][0];
        entry->edge1[0] = coords[0][1];
        entry->edge1[1] = coords[1][1];
        entry->edge1[2] = coords[2][1];
        entry->skidding = 1;
    } else {
        {
            s32 cur;

            cur = D_800A34E8;
            tex2 = &gSkidMarks[cur];
        }
        tex2->vertex[2].vx = entry->edge0[0];
        tex2->vertex[2].vy = entry->edge0[1];
        tex2->vertex[2].vz = entry->edge0[2];
        tex2->vertex[0].vx = entry->edge0[0] = coords[0][0];
        tex2->vertex[0].vy = entry->edge0[1] = coords[1][0];
        tex2->vertex[0].vz = entry->edge0[2] = coords[2][0];
        tex2->vertex[3].vx = entry->edge1[0];
        tex2->vertex[3].vy = entry->edge1[1];
        tex2->vertex[3].vz = entry->edge1[2];
        tex2->vertex[1].vx = entry->edge1[0] = coords[0][1];
        tex2->vertex[1].vy = entry->edge1[1] = coords[1][1];
        tex2->vertex[1].vz = entry->edge1[2] = coords[2][1];
        if (*(s16 *)tex2 != -1) {
            node = gTrackSections[0][*(s16 *)tex2].children;
            if ((u8 *)node->next == 0) {
                gTrackSections[0][*(s16 *)tex2].children = 0;
            } else {
                while (node->next->next != 0) {
                    node = (u8 *)node->next;
                }
                node->next = 0;
            }
        }
        {
            s32 cur;
            register s32 owner asm("$5");
            register u8 *slot asm("$4");
            s32 key;

            cur = D_800A34E8;
            asm("" : "=r"(owner) : "0"((u16)arg0->segment));
            slot = (u8 *)((cur * 12 - cur) * 8);
            slot += (s32)gSkidMarks;
            key = (s16)owner;
            asm volatile("");
            *(u16 *)slot = owner;
            *(u8 **)&((SkidMark *)slot)->next = gTrackSections[0][key].children;
            gTrackSections[0][key].children = slot;
        }
        if (entry->surface == 2) {
            if (entry->unk24 != 0) {
                tim = (SceneTexture *)D_80090F6C;
            } else {
                tim = (SceneTexture *)D_80090F88;
                entry->unk24 = 1;
            }
        } else {
            if (entry->unk24 != 0) {
                tim = (SceneTexture *)D_80090F5E;
            } else {
                tim = (SceneTexture *)D_80090F7A;
                entry->unk24 = 1;
            }
        }
        tex2 =
            (new_var4 = (u8 *)gSkidMarks + (D_800A34E8 * 12 - D_800A34E8) * 8);
        tex2->face.clut = GetClut(tim->clutX, tim->clutY);
        tex2->face.tpage = GetTPage(tim->tpage, 0, tim->tpx, tim->tpy);
        u = tim->u;
        tex2->face.u1 = u;
        tex2->face.u0 = u;
        u = tim->u + 0x3F;
        tex2->face.u3 = u;
        tex2->face.u2 = u;
        uv = tim->v + 0x1F;
        tex2->face.v2 = uv;
        tex2->face.v0 = uv;
        uv = tim->v;
        tex2->face.v3 = uv;
        tex2->face.v1 = uv;
        {
            register u16 cur asm("$5");
            register u8 *base asm("$6");
            s32 head;
            s32 next;
            u8 *slot;

            cur = D_800A34E8;
            base = (u8 *)gSkidMarks;
            head = D_800A2EC0Absolute[0];
            slot = (u8 *)(((s16)cur * 12 - (s16)cur) * 8);
            slot += (s32)base;
            entry->skidMark = cur;
            next = (s16)(cur + 1);
            ((SkidMark *)slot)->depth = head;
            new_var4 = ((u8 *)arg0 + arg1 * 0x28) + 0x2B4;
            arg0->wheel[arg1].unkC -= (0x12C - *(s16 *)new_var4) >> 3;
            D_800A34E8 = next % 100;
        }
    }
    switch (arg1) {
    case 2:
        entry->surface = arg0->frontRightContact;
        break;
    case 3:
        entry->surface = arg0->frontLeftContact;
        break;
    case 0:
        entry->surface = arg0->rearRightContact;
        break;
    case 1:
        entry->surface = arg0->rearLeftContact;
        break;
    }
}

extern s8 D_800A34EC;
extern s8 D_800A34F0;

void func_80052E18(void) {
    s16 i;
    SkidMark *elem;
    POLY_FT4 *poly;
    Car *p;
    Car *entry;

    D_800A34E8 = 0;
    D_800A34F0 = 0;
    D_800A34EC = 0;
    gSkidMarks = (SkidMark *)HeapAlloc(0x2260);
    i = 0;
    do {
        elem = &gSkidMarks[i];
        poly = (POLY_FT4 *)&elem->face;
        SetPolyFT4(poly);
        SetSemiTrans(poly, 1);
        SetShadeTex(poly, 1);
        elem->face.depth = 0x10;
        elem->face.vertex[0] = &elem->vertex[0];
        elem->face.vertex[1] = &elem->vertex[1];
        elem->face.vertex[2] = &elem->vertex[3];
        elem->face.vertex[3] = &elem->vertex[2];
        elem->face.type = 0xD;
        elem->face.next = 0;
        *(s16 *)&elem->section = -1;
        i++;
    } while (i < 100);
    i = 0;
    while (i < gTrackSectionCount[0]) {
        gTrackSections[0][i].children = 0;
        i++;
    }
    p = gCarListNM[0];
    while (p != 0) {
        for (i = 0; i < 4; i++) {
            entry = (u8 *)p + i * 0x28;
            entry->wheel[0].skidMark = -1;
            entry->wheel[0].unk24 = 0;
            entry->wheel[0].skidding = 0;
        }
        p->unk3B9 = 0;
        p = p->next;
    }
}

void SoundStopConditionalSlots(s8 arg0) {
    if (arg0 < 2) {
        SoundStopSlot(0x14);
        D_800A34EC = 0;
    }
    if (!(arg0 & 1)) {
        SoundStopSlot(0x15);
        D_800A34F0 = 0;
    }
}

void func_8005301C(void) {
    Car *obj;

    if (gSoundEffectsEnabledw15[0] == 0) {
        return;
    }
    obj = gPlayerCar[0];
    if ((s8)obj->unk3B9 != 0) {
        func_8003FC0C(
            0x14,
            (s8)(((s16 *)&obj->speed)[1] * 8 / ((s16 *)&obj->maxSpeed)[1] +
                 0x2C),
            0);
        if (*(u8 *)&D_800A34EC == 0) {
            SoundPlaySlot(0x14, 2);
            D_800A34EC = 1;
        }
    } else if (*(u8 *)&D_800A34EC != 0) {
        SoundStopSlot(0x14);
        D_800A34EC = 0;
    }
    if (gSplitScreenModeAbsolute[0] == 0) {
        return;
    }
    obj = gPlayerCar[0]->next;
    if ((s8)obj->unk3B9 != 0) {
        func_8003FC0C(
            0x15,
            (s8)(((s16 *)&obj->speed)[1] * 8 / ((s16 *)&obj->maxSpeed)[1] +
                 0x2C),
            0);
        if (*(u8 *)&D_800A34F0 == 0) {
            SoundPlaySlot(0x15, 2);
            D_800A34F0 = 1;
        }
    } else if (*(u8 *)&D_800A34F0 != 0) {
        SoundStopSlot(0x15);
        D_800A34F0 = 0;
    }
}

extern u8 D_800A3058;
extern u8 D_800A3060;
extern u8 D_800A3061;
extern u8 gCdVolume;
extern u8 D_800A3950;
extern u8 D_800A3644;
extern u8 gScreenStateSmall;
extern void *gMenuBackground;
extern u16 *D_800A35F0;
extern s32 D_800A305C;
extern RECT D_800A3710[2];
extern RECT D_800A3710Small asm("D_800A3710");
extern s32 D_800A36B4w6c[] asm("D_800A36B4");
extern u8 D_800A3A58Lui asm("D_800A3A58Absolute");
extern s32 D_800A335C[];
extern u8 D_800A3884[];

void GraphicsHideDisplay(s32 hide);
void func_8006D4C8(s32, s32);
void SsStart2(void);
void PadResetAndInitializeBuffersFrontEnd(s32) asm(
    "PadResetAndInitializeBuffers");
void func_80053D40(void);
void MenuInitializeGlyphPrimitiveBuffer(void);
void GraphicsSelectPrimitiveBuffer(s32);
s32 MenuTextCenterOffset(s16, u8 *);
void MenuDrawString(u8 *, s16, s16, u8, u8, s32, u8, u8);
void func_80066730(void);
void func_80064E6C(void);
void MenuStartVBlankEventFrontEnd(s32) asm("MenuStartVBlankEvent");
void func_80057BFC(void);
void func_8005957C(void);
void GraphicsPutCurrentEnvironments(void);
void func_80058148(void);

/* Front-end session: set up, run the menu loop func_80053D40, tear down. */
void MenuRunFrontEnd(void) {
    s32 pad[2]; /* unused: retail's frame has 8 spare bytes */
    s32 buttons;
    s32 bank;
    u8 *ot;

    if (D_800A3058 != 0) {
        SoundReloadVabAndResetSlots(3);
    }
    D_800A3058 = 1;
    GraphicsHideDisplay(0);
    if (D_800A3060 != 0 && D_800A3061 != 0) {
        if (D_800A3A58Lui != 0) {
            func_8006D4C8(0, 0);
        }
        if (D_800A3A58Lui >= 2) {
            func_8006D4C8(1, 1);
        }
        D_800A3061 = 0;
    }
    MenuLoadResources();
    CdEnablePlaybackAndSetVolume();
    SsStart2();
    SsSetMVol(0x7F, 0x7F);
    CdSetMixVolume(gCdVolume);
    if (D_800A335C[0] == 0) {
        if (D_800A3950 != 0xF9) {
            GraphicsInitDoubleBufferSwapped();
        }
    } else {
        D_800A3884[0] = 1;
        do {
            CdStopIfPlaybackChanged();
            PadResetAndInitializeBuffersFrontEnd(0);
            buttons = PadGetButtons(0);
            if (D_800A3644 != 0) {
                if (buttons & 0x800) {
                    break;
                }
                buttons = PadGetButtons(1);
            }
        } while (!(buttons & 0x800));
        MenuStopVBlankEvent();
    }
    if (gScreenStateSmall == 0xC) {
        SetDispMask(0);
    }
    TextureLoadTim(gMenuBackground);
    D_800A3710[0] = D_800A39B0[0];
    D_800A35F0 = (u16 *)D_800A36B4w6c[0];
    func_80053D40();
    func_80063AE0(0, 0);
    func_80063AE0(1, 1);
    if (gScreenStateSmall != 0xF8 && gScreenStateSmall != 0xFD &&
        gSessionTypeAbsolute[0] != 2) {
        MenuInitializeGlyphPrimitiveBuffer();
    }
    if (gScreenStateSmall == 0xFD) {
        func_80063AE0(0, 0);
        func_80063AE0(1, 1);
        DrawSync(0);
        func_8005957C();
        bank = D_800A305C == 0;
        ot = gOrderingTables + (bank << 12);
        D_800A305C = bank;
        gOrderingTableBankAbsolute[0] = bank;
        gOrderingTable[0] = (s32)ot;
        ClearOTagR((OT_TYPE *)ot, 0x400);
        GraphicsSelectPrimitiveBuffer((u8)D_800A305C);
        MenuFontSet(1, 1);
        MenuTextCenterOffset(0x140, D_8009A400[0]);
        MenuDrawString(D_8009A400[0],
                       MenuTextCenterOffset(0x140, D_8009A400[0]), 0x78, 0, 0,
                       0, 0, 0);
        GraphicsPutCurrentEnvironments();
        D_800A3710Small.x = -(D_800A305C != 0) & 0x140;
        LoadImage(D_800A3710, (u_long *)D_800A35F0);
        DrawOTag((OT_TYPE *)(gOrderingTableAbsolute[0] + 0xFFC));
        D_800A305C = D_800A305C == 0;
        GraphicsPutCurrentEnvironments();
    } else if (gScreenStateSmall != 0xF8) {
        func_80058148();
    }
    CdStop();
    if (D_800A3058 != 0) {
        SsSetMVol(0, 0);
        SoundStopActiveSlots();
        SoundShutdown();
        VSync(0);
    }
    if (gSessionTypeAbsolute[0] == 2) {
        func_80066730();
        func_80057BFC();
    } else {
        func_80057BFC();
        if (gScreenStateSmall != 0xFD) {
            gScreenStateSmall = 0x80;
            func_80064E6C();
        }
    }
    MenuStartVBlankEventFrontEnd(gSessionTypeAbsolute[0]);
}

/* Called once at boot: resets the player names, volumes, and option
 * defaults, then loads the save table when a memory card holds one. */
void GameInitDefaults(void) {
    extern u8 D_800BBA24[2][17][4];
    extern u8 D_800B0A2C[];
    extern u8 D_800A36E4[];
    extern u8 D_800A36E1Lui asm("D_800A36E1Absolute");
    extern u8 D_800A3980Small;
    extern u8 D_800A3981Lui asm("D_800A3981Absolute");
    extern u8 D_800A3658;
    extern u8 gPlayerDriverSmall;
    extern s16 gCdVolumeSmall;
    extern s16 gMusicVolumeLui asm("gMusicVolumeAbsolute");
    extern u8 gMusicVolumeScaledLui asm("gMusicVolumeScaledAbsolute");
    extern u8 gStereoEnabledLui asm("gStereoEnabledAbsolute");
    extern u8 gSelectedTrackSmall;
    extern s32 D_800A37D0Small;
    extern u8 D_800A306F;
    extern u8 D_800A3968Lui asm("D_800A3968Absolute");
    extern u8 gCardSlotLui asm("gCardSlotAbsolute");
    extern u8 gCardMenuMessageLui asm("gCardMenuMessageAbsolute");
    extern u8 D_800A3A48;
    extern char *D_800A35F4Lui asm("D_800A35F4Absolute");
    extern void CardMenuSetSaveDataPointers(void);
    extern void func_8006ABF8(void);
    extern void func_8006BA68(void);
    extern void CardEnableAndTestEvents(void);
    extern void CardTestAndDisableEvents(void);
    extern u8 CardProbeSlots(void);
    extern u8 CardResolveSlot(void);
    extern u8 CardGetOtherFileBlocks(void);
    extern u8 CardLoadSaveTable(u8);
    extern void CardMenuSetDriverIndexFromName(s32);
    extern u8 DriverFindIndexById(u8);
    s32 i;
    s32 j;
    s32 k;
    s32 offset;
    u8 ok;
    u8 value;
    u8 *flags;

    D_800A36E1Lui = 1;
    D_800A3980Small = 8;
    D_800A3658 = 0;
    gPlayerDriverSmall = 0;
    D_800A3981Lui = 0xE;
    D_800A3644 = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 17; j++) {
            for (k = 3; k >= 0; k--) {
                D_800BBA24[i][j][k] = ' ';
            }
        }
    }
    for (i = 0; i < 2; i++) {
        for (j = 3; j >= 0; j--) {
            D_800A3860[i][j] = ' ';
        }
    }
    strcpy(D_800BB9B4, gDriverNames[gPlayerDriverSmall]);
    strcpy(&D_800BB9B4[0x18], gDriverNames[D_800A36E1Lui]);
    gCdVolumeSmall = 65;
    gMusicVolumeLui = 50;
    gMusicVolumeScaledLui = 0x20;
    gStereoEnabledLui = 1;
    gSelectedTrackSmall = 0;
    D_800A37D0Small = 3;
    D_800A306F = 0;
    for (offset = 14 * 0x18; offset >= 0; offset -= 0x18) {
        D_800B0A2C[offset] = 0;
    }
    D_800A3968Lui = 0;
    /* i holds the "card full" block count from here on. */
    i = 15;
    CardMenuSetSaveDataPointers();
    ok = 0;
    func_8006ABF8();
    value = 1;
    func_8006BA68();
    D_800A3060 = 0;
    D_800A3061 = value;
    CardEnableAndTestEvents();
    switch (CardProbeSlots()) {
    case 0:
        gCardMenuMessageLui = 2;
        D_800A3A48 = 0xFC;
        break;
    case 1:
        if (!CardResolveSlot()) {
            if (gCardMenuMessageLui == 0xD) {
                D_800A3A48 = 0xFC;
            }
        } else if (CardGetOtherFileBlocks() == i) {
            gCardMenuMessageLui = 0x1C;
            D_800A3A48 = 0xFC;
        } else {
            ok = 1;
        }
        break;
    case 2:
        if (!CardResolveSlot()) {
            gCardSlotLui = value;
            value = gCardMenuMessageLui;
            if (!CardResolveSlot()) {
                if (gCardMenuMessageLui == 0xD) {
                    gCardSlotLui = 0;
                    D_800A3A48 = 0xFC;
                }
            } else if (CardGetOtherFileBlocks() == i) {
                if (value == 0xD) {
                    gCardSlotLui = 0;
                    gCardMenuMessageLui = 0xD;
                } else {
                    gCardMenuMessageLui = 0x1C;
                }
                D_800A3A48 = 0xFC;
            } else {
                ok = 1;
            }
        } else if (CardGetOtherFileBlocks() == i) {
            gCardSlotLui = value;
            if (!CardResolveSlot()) {
                if (gCardMenuMessageLui != 0xD) {
                    gCardSlotLui = 0;
                    gCardMenuMessageLui = 0x1C;
                }
                D_800A3A48 = 0xFC;
            } else if (CardGetOtherFileBlocks() == i) {
                gCardMenuMessageLui = 0x1C;
                gCardSlotLui = 0;
                D_800A3A48 = 0xFC;
            } else {
                ok = 1;
            }
        } else {
            ok = 1;
        }
        break;
    }
    if (ok) {
        if (CardLoadSaveTable(1) == 1) {
            if (D_800A3A58Lui != 0) {
                strcpy(D_800BB9B4, D_800A35F4Lui);
                CardMenuSetDriverIndexFromName(0);
                D_800A3980Small = DriverFindIndexById(gPlayerDriverSmall);
                D_800A3060 = 1;
            }
            if (D_800A3A58Lui >= 2) {
                strcpy(&D_800BB9B4[0x18], D_800A35F4Lui + 0xE8);
                CardMenuSetDriverIndexFromName(1);
                D_800A3981Lui = DriverFindIndexById(D_800A36E1Lui);
            }
        }
        D_800A3A48 = 0;
        D_800A3950 = 0;
    }
    i = 1;
    CardTestAndDisableEvents();
    flags = D_800A36E4;
    for (; i >= 0; i--) {
        flags[i] = 0;
    }
    gScreenStateSmall = 0xF9;
}

extern void SceneInitPrimPools(void);
extern u8 D_800A3724NM asm("D_800A3724.NON_MATCHING");
extern u8 D_800A305ANM asm("D_800A305A.NON_MATCHING");
extern s32 D_800A37F0NM asm("D_800A37F0.NON_MATCHING");
extern s32 D_800A3830NM asm("D_800A3830.NON_MATCHING");

void MenuLoadResources(void) {
    s32 *table;
    u8 i;
    void *base;

    gMenuBackground = HeapAlloc(0x26000);
    CdLoadFileByIndex((s32)gMenuBackground, 5);
    MenuLoadOffsetResources(6);
    SceneInitPrimPools();
    i = 0;
    MenuAllocateObjectList();
    func_80063E7C();
    SceneAllocateRuntimeBuffers();
    MenuFontReset();
    base = FileLoadOffsetTable(9, &table, 0);
    TextureLoadTim(base + (table)[0xB]);
    DrawSync(0);
    TextureLoadTim(base + (table)[6]);
    DrawSync(0);
    TextureLoadTim(base + (table)[0xA]);
    DrawSync(0);
    while (i < 5) {
        TextureLoadTim(base + (table)[i + 1]);
        DrawSync(0);
        i++;
    }
    i = 0;
    TextureLoadTim(base + (table)[9]);
    DrawSync(0);
    while (i < 2) {
        TextureLoadTim(base + (table)[i + 7]);
        DrawSync(0);
        i++;
    }
    TextureLoadTim(base + (table)[0xC]);
    DrawSync(0);
    TextureLoadTim(base + (table)[0]);
    DrawSync(0);
    GraphicsLoadPaletteRow();
    HeapFree(base);
    MenuLoadTextureTable();
    CardMenuLoadResources();
    MenuFontBuildPrimitives(0, 0);
    MenuFontBuildPrimitives(1, 1);
    MenuFontBuildPrimitives(2, 2);
    MenuSetShadeColors(0xA0, 0xA0, 0x40);
    D_800A3724NM = 3;
    D_800A305ANM = 0;
    D_800A37F0NM = 1;
    D_800A3830NM = 0;
}

extern u8 D_800A3608;

extern u8 D_800A3059;
void func_80053C00(s32 arg0, s32 arg1) {
    extern s32 D_800A3914[];
    extern s32 D_800A3914NM[] asm("D_800A3914.NON_MATCHING");
    extern void MenuUpdateAndDrawObjectLists(void);
    extern void MenuUpdateObjectPosition(MenuObj *, u8);
    extern void MenuDrawObjectList(MenuObj *, u8);
    extern void MenuDrawObjectGroups(void);
    extern void func_800686FC(u8, u8);
    extern void func_8005D094(s32, u8, u8);
    extern s32 func_8005DCF0(void);

    if (gScreenStateSmall == 0xFC) {
        MenuUpdateAndDrawObjectLists();
    } else {
        if (D_800A3914[0] != 0) {
            MenuUpdateObjectPosition((MenuObj *)D_800A3914[0], 1);
        }
        if ((gScreenStateSmall >= 9 && gScreenStateSmall <= 10) ||
            gScreenStateSmall == 12 ||
            (gScreenStateSmall >= 16 && gScreenStateSmall <= 17)) {
            func_800686FC(gScreenStateSmall, arg0);
        } else if (gScreenStateSmall == 14) {
            MenuDrawObjectList((MenuObj *)D_800A3914NM[0], 0xFF);
            MenuDrawObjectGroups();
        } else {
            MenuDrawObjectList((MenuObj *)D_800A3914NM[0], 0xFF);
            func_8005D094(gScreenStateSmall, D_800A3059, arg1);
        }
    }
    if (D_800A3608 != 0) {
        D_800A3608 = D_800A3608 - 1;
    } else if (!((gScreenStateSmall >= 16 && gScreenStateSmall <= 17) ||
                 gScreenStateSmall == 14) &&
               func_8005DCF0() == 1) {
        D_800A3608 = 0x78;
    }
}

__asm__("gCdAudioEnabled.MainLoop = gCdAudioEnabled\n"
        "D_800A3059.MainLoop = D_800A3059\n"
        "D_800A305A.MainLoop = D_800A305A\n"
        "gSelectedTrack.MainLoop = gSelectedTrack\n"
        "D_800A305C.MainLoop = D_800A305C\n"
        "D_800A3064.MainLoop = D_800A3064\n"
        "D_800A3065.MainLoop = D_800A3065\n"
        "D_800A3076.MainLoop = D_800A3076\n"
        "D_800A358C.MainLoop = D_800A358C\n"
        "D_800A35F0.MainLoop = D_800A35F0\n"
        "D_800A3608.MainLoop = D_800A3608\n"
        "D_800A3644.MainLoop = D_800A3644\n"
        "D_800A3690.MainLoop = D_800A3690\n"
        "gPlayerDriver.MainLoop = gPlayerDriver\n"
        "D_800A3710.MainLoop = D_800A3710\n"
        "D_800A3724.MainLoop = D_800A3724\n"
        "gCardMenuMessage.MainLoop = gCardMenuMessage\n"
        "D_800A3928.MainLoop = D_800A3928\n"
        "D_800A3950.MainLoop = D_800A3950\n"
        "D_800A3968.MainLoop = D_800A3968\n"
        "D_800A3980.MainLoop = D_800A3980\n"
        "gScreenState.MainLoop = gScreenState\n"
        "D_800B9B84.MainLoop = D_800B9B84\n"
        "D_800A3684.MainLoopSmall = D_800A3684\n"
        "D_800A3988.MainLoopSmall = D_800A3988\n"
        "D_800AE178.MainLoop1 = D_800AE178\n"
        "D_800AE178.MainLoop2 = D_800AE178\n"
        "D_800A3A58.MainLoop3 = D_800A3A58\n"
        "D_800A36E1.MainLoop4 = D_800A36E1\n"
        "D_800A3981.MainLoop5 = D_800A3981\n"
        "D_800A3685.MainLoop6 = D_800A3685\n"
        "D_800A3685.MainLoop7 = D_800A3685\n"
        "gOrderingTables.MainLoop8 = gOrderingTables\n"
        "gOrderingTableBank.MainLoop9 = gOrderingTableBank\n"
        "gOrderingTable.MainLoop10 = gOrderingTable\n"
        "gOrderingTable.MainLoop11 = gOrderingTable\n"
        "D_800A3685.MainLoop12 = D_800A3685\n"
        "gPadPictureMenuLists.MainLoop13 = gPadPictureMenuLists\n"
        "D_800A37DC.MainLoop14 = D_800A37DC\n"
        "D_800A3684.MainLoop15 = D_800A3684\n"
        "gPadType.MainLoop16 = gPadType\n"
        "D_800A3684.MainLoop17 = D_800A3684\n"
        "gPadType.MainLoop18 = gPadType\n"
        "gPadLayout.MainLoop19 = gPadLayout\n"
        "gPadType.MainLoop20 = gPadType\n"
        "D_800A3888.MainLoop21 = D_800A3888\n"
        "D_800A3684.MainLoop22 = D_800A3684\n"
        "gPadLayout.MainLoop23 = gPadLayout\n"
        "gPadType.MainLoop24 = gPadType\n"
        "D_800A3888.MainLoop25 = D_800A3888\n"
        "D_800A3684.MainLoop26 = D_800A3684\n"
        "D_800A36E4.MainLoop27 = D_800A36E4\n"
        "D_800A3685.MainLoop28 = D_800A3685\n"
        "D_800A37F8.MainLoop29 = D_800A37F8\n"
        "D_800A3684.MainLoop30 = D_800A3684\n"
        "gPadType.MainLoop31 = gPadType\n"
        "gPadLayout.MainLoop32 = gPadLayout\n"
        "gPadType.MainLoop33 = gPadType\n"
        "gCardMenuMessage.MainLoop51 = gCardMenuMessage\n"
        "D_800A3770.MainLoop57 = D_800A3770\n"
        "D_800A3770.MainLoop58 = D_800A3770\n"
        "D_800A38E8.MainLoop59 = D_800A38E8\n"
        "D_800A3988.MainLoop60 = D_800A3988\n"
        "D_800A3988.MainLoop61 = D_800A3988\n"
        "D_800A3770.MainLoop62 = D_800A3770\n"
        "D_800A3770.MainLoop63 = D_800A3770\n"
        "D_800A38E8.MainLoop64 = D_800A38E8\n"
        "D_800A3988.MainLoop65 = D_800A3988\n"
        "D_800A3988.MainLoop66 = D_800A3988\n"
        "D_800A3684.MainLoop67 = D_800A3684\n"
        "gPadType.MainLoop68 = gPadType\n"
        "D_800A3684.MainLoop69 = D_800A3684\n"
        "D_800A3080.MainLoop70 = D_800A3080\n"
        "gPadType.MainLoop71 = gPadType\n"
        "gPadLayout.MainLoop72 = gPadLayout\n"
        "D_800A3684.MainLoop73 = D_800A3684\n"
        "gPadType.MainLoop74 = gPadType\n"
        "D_800A3684.MainLoop75 = D_800A3684\n"
        "gPadLayout.MainLoop76 = gPadLayout\n"
        "D_800A3080.MainLoop77 = D_800A3080\n"
        "gPadType.MainLoop78 = gPadType\n"
        "D_800A3A25.MainLoop79 = D_800A3A25\n"
        "D_800A3059.MainLoopPostUp = D_800A3059\n"
        "D_800A3059.MainLoopPostDown = D_800A3059\n");

s32 ListHasClearFlagsMainLoop(MenuObj *node) asm("ListHasClearFlags");
void ListSetFieldsAndEnableMainLoop(MenuObj *, s32, s32,
                                    s32) asm("ListSetFieldsAndEnable");
void GraphicsSelectPrimitiveBufferMainLoop(s32 arg0) asm(
    "GraphicsSelectPrimitiveBuffer");
void CdStopIfPlaybackChangedMainLoop(void) asm("CdStopIfPlaybackChanged");
void func_8003CCE0MainLoop(s32 arg0) asm("func_8003CCE0");
s32 func_8003F4FCMainLoop(s32 arg0) asm("SoundIsSlotActive");
/* All loop sound arguments fit s8. Pins already hold their extended values. */
void SoundPlaySlotMainLoop(s32, s32) asm("SoundPlaySlot");
void SoundStopSlotMainLoop(s32) asm("SoundStopSlot");
s32 func_80041B7CMainLoop(s32) asm("PadGetButtons");
s32 PadTypeNeedsCalibrationMainLoop(s32 arg0) asm("PadTypeNeedsCalibration");
void SoundRunSlotEnvelopeMainLoop(s32 arg0,
                                  s32 arg1) asm("SoundRunSlotEnvelope");
void MenuHandleOptionsInputMainLoop() asm("MenuHandleOptionsInput");
s32 func_80056B0CMainLoop(s32 arg0, s32 arg1) asm("func_80056B0C");
s32 func_80056B5CMainLoop(s32 arg0, s32 arg1, s32 arg2) asm("func_80056B5C");
void func_80056C84MainLoop(s32 arg0, s32 arg1) asm("func_80056C84");
void func_80056F04MainLoop(s32 arg0) asm("func_80056F04");
void func_80057008MainLoop(s32 arg0) asm("func_80057008");
void func_80057160MainLoop(s32 arg0) asm("func_80057160");
void func_80057DD4MainLoop(void) asm("func_80057DD4");
void func_80057DE8MainLoop(void) asm("func_80057DE8");
void func_80057DFCMainLoop(void) asm("func_80057DFC");
void func_80057E10MainLoop(void) asm("func_80057E10");
void InputGetPadButtonsMainLoop(s32 index, s32 *out) asm("InputGetPadButtons");
void GraphicsPutCurrentEnvironmentsMainLoop(void) asm(
    "GraphicsPutCurrentEnvironments");
void CdEnablePlaybackAndSetVolumeMainLoop(void) asm(
    "CdEnablePlaybackAndSetVolume");
void CardTestAndDisableEventsMainLoop(void) asm("CardTestAndDisableEvents");
void CardEnableAndTestEventsMainLoop(void) asm("CardEnableAndTestEvents");
/* Intensity is masked to u8 in the pulse block before these calls. */
void MenuSetShadeColorsMainLoop(s32, s32, s32) asm("MenuSetShadeColors");
void MenuObjResetPoolMainLoop(void) asm("MenuObjResetPool");
void MenuObjRestorePoolCursorMainLoop(void) asm("MenuObjRestorePoolCursor");
void func_8005E4A4MainLoop(u8 *table) asm("func_8005E4A4");
void MenuCenterTextMainLoop(s32 arg0) asm("MenuCenterText");
void MenuSetLinkedObjectLayoutMainLoop(s32 a, s32 b,
                                       s16 c) asm("MenuSetLinkedObjectLayout");
void MenuSetVolumeMainLoop(s32 arg0, s32 volume) asm("MenuSetVolume");
void func_80062874MainLoop(s32 arg0, s32 arg1) asm("func_80062874");
void func_80062F04MainLoop() asm("func_80062F04");
void func_80063180MainLoop(s32 enabled) asm("func_80063180");
void MenuNegateLinkedObjectValuesMainLoop(u8 index) asm(
    "MenuNegateLinkedObjectValues");
void func_80063AE0MainLoop(s32, s32) asm("func_80063AE0");
void func_80068AC4MainLoop(s32 arg0, s32 arg1, s32 arg2) asm("func_80068AC4");
void MenuUpdateItemRowMainLoop(s32 arg0) asm("MenuUpdateItemRow");
s32 func_80069EB8MainLoop(void) asm("func_80069EB8");
s32 CardProbeSlotsMainLoop(void) asm("CardProbeSlots");
u8 DriverFindIndexByIdMainLoop(u8 value) asm("DriverFindIndexById");
void CardMenuSetColorNodeLayoutMainLoop(s32 low, s32 high, s32 color) asm(
    "CardMenuSetColorNodeLayout");
void CardMenuCenterSelectedTextMainLoop(s32 arg0) asm(
    "CardMenuCenterSelectedText");
void MenuHideCurrentObjectMainLoop(void) asm("MenuHideCurrentObject");
void func_8006CE64MainLoop(void) asm("func_8006CE64");
void CardMenuAppendTrackNameMainLoop(void) asm("CardMenuAppendTrackName");
s32 CardMenuCheckTrackNameCapacityMainLoop(void) asm(
    "CardMenuCheckTrackNameCapacity");
void CardMenuWriteSaveSlotMainLoop(void) asm("CardMenuWriteSaveSlot");
s32 func_8006D258MainLoop(void) asm("func_8006D258");
void func_8006DA40MainLoop(void) asm("func_8006DA40");
void func_8006DE68MainLoop(u32 arg0, u32 mode) asm("func_8006DE68");
void PadResetAndInitializeBuffersMainLoop(s32) asm(
    "PadResetAndInitializeBuffers");
void ClearOTagRMainLoop(u32 *, s32) asm("ClearOTagR");
void DrawOTagMainLoop(u32 *) asm("DrawOTag");
s32 DrawSyncMainLoop(s32) asm("DrawSync");
s32 LoadImageMainLoop(s16 *, u32 *) asm("LoadImage");
s32 RandomScaledGetMainLoop(s32 scale) asm("RandomScaledGet");
void SetDispMaskMainLoop(s32) asm("SetDispMask");
s32 VSyncMainLoop(s32) asm("VSync");
void func_80053C00MainLoop(s32, s32) asm("func_80053C00");
u8 MenuUpdateScreenStateMainLoop(u8, u8 *, u8) asm("MenuUpdateScreenState");
void func_8005DAD4MainLoop(void) asm("func_8005DAD4");
void func_8005DFA0MainLoop(void) asm("func_8005DFA0");
void func_8005ED74MainLoop() asm("func_8005ED74");
void func_800606D4MainLoop(void) asm("func_800606D4");
void func_80060FD8MainLoop(void) asm("func_80060FD8");
void func_80063C34MainLoop(u8, u8) asm("func_80063C34");
void func_80064208MainLoop(void) asm("func_80064208");
void CardMenuCreateRecordTableMainLoop(s32) asm("CardMenuCreateRecordTable");
void func_80068CE4MainLoop(void) asm("func_80068CE4");
void CardMenuCreateStandingsTableMainLoop(void) asm(
    "CardMenuCreateStandingsTable");
void func_800697ECMainLoop(s32) asm("func_800697EC");
void MenuCreateItemRowMainLoop(u8) asm("MenuCreateItemRow");
s32 CardResolveSlotMainLoop(void) asm("CardResolveSlot");
s32 CardLoadNameListMainLoop(s32) asm("CardLoadNameList");
void CardLoadSaveTableMainLoop(s32) asm("CardLoadSaveTable");
void CardMenuBuildFileListMainLoop(void) asm("CardMenuBuildFileList");
s32 func_8006C700MainLoop(s32, s32) asm("func_8006C700");
void func_8006C9F8MainLoop(void) asm("func_8006C9F8");
void func_8006CB80MainLoop(s32) asm("func_8006CB80");
s32 func_8006D178MainLoop(void) asm("func_8006D178");
void CardMenuShowMessageMainLoop(s32) asm("CardMenuShowMessage");
void PadCalibrateRangeMainLoop(u32, u32, u32) asm("PadCalibrateRange");
void PadCalibrateCenterMainLoop(u32, u32, u32) asm("PadCalibrateCenter");
void RaceBuildQualifyingGridMainLoop(u8) asm("RaceBuildQualifyingGrid");
void func_8005C124MainLoop(u8, u8) asm("func_8005C124");
extern s8 gCdAudioEnabledMainLoop[] asm("gCdAudioEnabled.MainLoop");
extern u8 D_800A3059MainLoop asm("D_800A3059.MainLoop");
extern u8 D_800A305AMainLoop asm("D_800A305A.MainLoop");
extern u8 gSelectedTrackMainLoop asm("gSelectedTrack.MainLoop");
extern s32 D_800A305CMainLoop asm("D_800A305C.MainLoop");
extern u8 D_800A3064MainLoop asm("D_800A3064.MainLoop");
extern u8 D_800A3065MainLoop asm("D_800A3065.MainLoop");
extern u8 D_800A3076MainLoop asm("D_800A3076.MainLoop");
extern u8 D_800A358CMainLoop[] asm("D_800A358C.MainLoop");
extern u32 *D_800A35F0MainLoop asm("D_800A35F0.MainLoop");
extern u8 D_800A3608MainLoop asm("D_800A3608.MainLoop");
extern u8 D_800A3644MainLoop asm("D_800A3644.MainLoop");
extern u16 D_800A3690MainLoop[] asm("D_800A3690.MainLoop");
extern u8 gPlayerDriverMainLoop asm("gPlayerDriver.MainLoop");
extern s16 D_800A3710MainLoop asm("D_800A3710.MainLoop");
extern u8 D_800A3724MainLoop asm("D_800A3724.MainLoop");
extern u8 gCardMenuMessageMainLoop[] asm("gCardMenuMessage.MainLoop");
extern u8 D_800A3928MainLoop asm("D_800A3928.MainLoop");
extern u8 D_800A3950MainLoop asm("D_800A3950.MainLoop");
extern u8 D_800A3968MainLoop[] asm("D_800A3968.MainLoop");
extern s8 D_800A3980MainLoop asm("D_800A3980.MainLoop");
extern u8 gScreenStateMainLoop asm("gScreenState.MainLoop");
extern s16 D_800B9B84MainLoop[] asm("D_800B9B84.MainLoop");
extern u8 D_800A3684MainLoopSmall asm("D_800A3684.MainLoopSmall");
extern u8 D_800A3988MainLoopSmall asm("D_800A3988.MainLoopSmall");
extern u8 *D_800AE178MainLoopSite1[] asm("D_800AE178.MainLoop1");
extern u8 *D_800AE178MainLoopSite2[] asm("D_800AE178.MainLoop2");
extern u8 D_800A3A58MainLoopSite3[] asm("D_800A3A58.MainLoop3");
extern u8 D_800A36E1MainLoopSite4[] asm("D_800A36E1.MainLoop4");
extern s8 D_800A3981MainLoopSite5[] asm("D_800A3981.MainLoop5");
extern u8 D_800A3685MainLoopSite6[] asm("D_800A3685.MainLoop6");
extern u8 D_800A3685MainLoopSite7[] asm("D_800A3685.MainLoop7");
extern u8 gOrderingTablesMainLoopSite8[] asm("gOrderingTables.MainLoop8");
extern s32
    gOrderingTableBankMainLoopSite9[] asm("gOrderingTableBank.MainLoop9");
extern u32 *gOrderingTableMainLoopSite10[] asm("gOrderingTable.MainLoop10");
extern u32 *gOrderingTableMainLoopSite11[] asm("gOrderingTable.MainLoop11");
extern u8 D_800A3685MainLoopSite12[] asm("D_800A3685.MainLoop12");
extern MenuObj *
    gPadPictureMenuListsMainLoopSite13[] asm("gPadPictureMenuLists.MainLoop13");
extern MenuObj *D_800A37DCMainLoopSite14[] asm("D_800A37DC.MainLoop14");
extern u8 D_800A3684MainLoopSite15[] asm("D_800A3684.MainLoop15");
extern s8 gPadTypeMainLoopSite16[] asm("gPadType.MainLoop16");
extern u8 D_800A3684MainLoopSite17[] asm("D_800A3684.MainLoop17");
extern s8 gPadTypeMainLoopSite18[] asm("gPadType.MainLoop18");
extern s8 gPadLayoutMainLoopSite19[] asm("gPadLayout.MainLoop19");
extern s8 gPadTypeMainLoopSite20[] asm("gPadType.MainLoop20");
extern MenuObj *D_800A3888MainLoopSite21[] asm("D_800A3888.MainLoop21");
extern u8 D_800A3684MainLoopSite22[] asm("D_800A3684.MainLoop22");
extern s8 gPadLayoutMainLoopSite23[] asm("gPadLayout.MainLoop23");
extern s8 gPadTypeMainLoopSite24[] asm("gPadType.MainLoop24");
extern MenuObj *D_800A3888MainLoopSite25[] asm("D_800A3888.MainLoop25");
extern u8 D_800A3684MainLoopSite26[] asm("D_800A3684.MainLoop26");
extern u8 D_800A36E4MainLoopSite27[] asm("D_800A36E4.MainLoop27");
extern u8 D_800A3685MainLoopSite28[] asm("D_800A3685.MainLoop28");
extern MenuObj *D_800A37F8MainLoopSite29[] asm("D_800A37F8.MainLoop29");
extern u8 D_800A3684MainLoopSite30[] asm("D_800A3684.MainLoop30");
extern s8 gPadTypeMainLoopSite31[] asm("gPadType.MainLoop31");
extern s8 gPadLayoutMainLoopSite32[] asm("gPadLayout.MainLoop32");
extern s8 gPadTypeMainLoopSite33[] asm("gPadType.MainLoop33");
extern u8 gCardMenuMessageMainLoopSite51[] asm("gCardMenuMessage.MainLoop51");
extern u8 D_800A3770MainLoopSite57[] asm("D_800A3770.MainLoop57");
extern u8 D_800A3770MainLoopSite58[] asm("D_800A3770.MainLoop58");
extern u8 D_800A38E8MainLoopSite59[] asm("D_800A38E8.MainLoop59");
extern u8 D_800A3988MainLoopSite60[] asm("D_800A3988.MainLoop60");
extern u8 D_800A3988MainLoopSite61[] asm("D_800A3988.MainLoop61");
extern u8 D_800A3770MainLoopSite62[] asm("D_800A3770.MainLoop62");
extern u8 D_800A3770MainLoopSite63[] asm("D_800A3770.MainLoop63");
extern u8 D_800A38E8MainLoopSite64[] asm("D_800A38E8.MainLoop64");
extern u8 D_800A3988MainLoopSite65[] asm("D_800A3988.MainLoop65");
extern u8 D_800A3988MainLoopSite66[] asm("D_800A3988.MainLoop66");
extern u8 D_800A3684MainLoopSite67[] asm("D_800A3684.MainLoop67");
extern s8 gPadTypeMainLoopSite68[] asm("gPadType.MainLoop68");
extern u8 D_800A3684MainLoopSite69[] asm("D_800A3684.MainLoop69");
extern s8 D_800A3080MainLoopSite70[] asm("D_800A3080.MainLoop70");
extern s8 gPadTypeMainLoopSite71[] asm("gPadType.MainLoop71");
extern s8 gPadLayoutMainLoopSite72[] asm("gPadLayout.MainLoop72");
extern u8 D_800A3684MainLoopSite73[] asm("D_800A3684.MainLoop73");
extern s8 gPadTypeMainLoopSite74[] asm("gPadType.MainLoop74");
extern u8 D_800A3684MainLoopSite75[] asm("D_800A3684.MainLoop75");
extern s8 gPadLayoutMainLoopSite76[] asm("gPadLayout.MainLoop76");
extern s8 D_800A3080MainLoopSite77[] asm("D_800A3080.MainLoop77");
extern s8 gPadTypeMainLoopSite78[] asm("gPadType.MainLoop78");
extern s8 D_800A3A25MainLoopSite79[] asm("D_800A3A25.MainLoop79");
extern u8 D_800A3059MainLoopPostUp asm("D_800A3059.MainLoopPostUp");
extern u8 D_800A3059MainLoopPostDown asm("D_800A3059.MainLoopPostDown");

#ifdef NATIVE
void func_80053D40(void) {
    s32 newPad[2];
    s32 oldPad[2];
    u8 playerUnlockSteps[2];
    s32 one;
    s32 two;
    s32 mode13;
    u8 exitLoop;
    u8 displayPhase;
    s32 idleFrames;
    s32 animationStartX;
    s32 animationEndX;
    s32 animationStepX;
    s32 animationReverseStepX;
    s32 *previousPadCursor;
    register s32 *currentPadCursor;
    s32 argument0;
    s32 menuPhase;
    s32 animateX;
    s32 animateY;
    s32 animateStep;
    register MenuObj **animationNodeSlot;
    s32 padBits;
    s32 previousPadInverse;
    s32 nextIdleFrames;
    s32 cardMenuCode;
    s32 nextBufferIndex;
    s32 padBits0;
    s32 playerPadBits;
    s32 sequenceValue;
    s32 unlockPhase;
    s32 itemUp;
    s32 itemDown;
    s32 cardOperation;
    s32 menuDirection;
    s32 activePlayer;
    s32 index;
    s32 player;
    s32 screenResult;
    register s32 unlockStep;
    s32 unlockDirectionBits;
    s32 dialogScreen;
    s32 actionSound;
    s32 returnChannel;
    u32 *orderingTable;
    u8 *screenTable;
    register u8 *sequenceCursor;
    u8 *selectionCursor;
    s32 screenResultByte;
    u8 pulseTick;
    u8 transitionPhase;
    u8 nextItemUp;
    u8 nextItemDown;
    u8 nextScreen;
    u8 pulsePhase;
    u8 selection;
    u8 currentSelection;
    u8 sequencePhase;
    u8 itemCursorUp;
    u8 itemCursorDown;
    u8 secondPlayerEnabled;
    u8 menuCode;
    s32 wrappedItemUp;

    playerUnlockSteps[0] = 0;
    playerUnlockSteps[1] = 0;
    MenuObjResetPoolMainLoop();
    func_8005DAD4MainLoop();
    func_8005DFA0MainLoop();
    idleFrames = 0;
    if ((u8)gSelectedTrackMainLoop < 0x11U) {
        screenTable = D_800AE178MainLoopSite1[gSelectedTrackMainLoop];
    } else {
        screenTable = *D_800AE178MainLoopSite2;
    }
    activePlayer = 0;
    func_8005E4A4MainLoop(screenTable);
    one = 1;
    two = 2;
    D_800A3608MainLoop = 0;
    exitLoop = 0;
    do {
        {
            s32 randomScale;
            /* The original call retains the incoming a0 and ignores the result. */
            asm("" : "=r"(randomScale));
            RandomScaledGetMainLoop(randomScale);
        }
        func_80057DE8MainLoop();
        func_80057E10MainLoop();
        MenuObjRestorePoolCursorMainLoop();
        argument0 = gScreenStateMainLoop;
        asm("" : "=r"(argument0) : "0"(argument0));
        if (argument0 == 0xFC) {
            PadResetAndInitializeBuffersMainLoop(0);
            func_8006DA40MainLoop();
            D_800A3928MainLoop = 0;
        } else if (argument0 == 9) {
            if (*D_800A3A58MainLoopSite3 == 0) {
                CardEnableAndTestEventsMainLoop();
                if (CardResolveSlotMainLoop() & 0xFF) {
                    CardLoadSaveTableMainLoop(0);
                }
                CardTestAndDisableEventsMainLoop();
            }
            CardMenuCreateRecordTableMainLoop((s32)gSelectedTrackMainLoop);
        } else if (argument0 == 0xA) {
            func_80068CE4MainLoop();
        } else if (argument0 == 0xC) {
            CardMenuCreateStandingsTableMainLoop();
        } else if (argument0 == 0xE) {
            func_80064208MainLoop();
        } else if ((u32)(gScreenStateMainLoop - 0x10) < 2U) {
            func_800697ECMainLoop(argument0 - 0x10);
        } else {
            func_80056C84MainLoop(argument0, activePlayer);
            func_8005C124MainLoop(gScreenStateMainLoop, D_800A3059MainLoop);
        }
        MenuCreateItemRowMainLoop(gScreenStateMainLoop);
        func_80056F04MainLoop((s32)gScreenStateMainLoop);
        switch (gScreenStateMainLoop) {
        case 0:
            idleFrames = 0;
            goto initializePads;
        case 7:
            secondPlayerEnabled = 0;
            argument0 = activePlayer & 0xFF;
            if (((D_800A3950MainLoop == 0xFB) || (D_800A3950MainLoop == 3)) &&
                (D_800A3644MainLoop != 0)) {
                secondPlayerEnabled = 1;
            }
            func_8005ED74MainLoop(argument0, secondPlayerEnabled);
            /* End the old register lifetime before setting the pad index. */
            asm volatile("" : "=r"(index));
            index = 0;
            if (D_800A3950MainLoop == 0xFB) {
            case 1:
                index = 0;
                CardMenuBuildFileListMainLoop();
                currentPadCursor = &newPad[0];
            } else {
                goto resetPadArray;
            }
            break;
        case 2:
        case 8:
            index = 0;
            D_800A3980MainLoop =
                DriverFindIndexByIdMainLoop(gPlayerDriverMainLoop);
            D_800A3981MainLoopSite5[0] =
                DriverFindIndexByIdMainLoop(D_800A36E1MainLoopSite4[0]);
            currentPadCursor = &newPad[0];
            break;
        case 5:
            index = 0;
            func_800606D4MainLoop();
            func_80063180MainLoop((s32)D_800A3076MainLoop);
            currentPadCursor = &newPad[0];
            break;
        case 13:
            func_80060FD8MainLoop();
            /* End the old register lifetime before setting the pad index. */
            asm volatile("" : "=r"(index));
            D_800A3684MainLoopSmall = 0;
            index = 0;
            if (D_800A3644MainLoop != 0) {
                *D_800A3685MainLoopSite6 = 0;
            } else {
                *D_800A3685MainLoopSite7 = two;
            }
            goto resetPadArray;
        case 3:
        case 6:
            RaceBuildQualifyingGridMainLoop(gSelectedTrackMainLoop);
        default:
        initializePads:
            index = 0;
        resetPadArray:
            /* Keep pointer setup in the common reset path. */
            asm volatile("" : "=r"(currentPadCursor));
            currentPadCursor = &newPad[0];
            break;
        }
        previousPadCursor = &oldPad[0];
    readInitialPads:
        InputGetPadButtonsMainLoop(index & 0xFF, previousPadCursor);
        *currentPadCursor = 0;
        currentPadCursor++;
        index += 1;
        previousPadCursor++;
        if (index < 2) {
            goto readInitialPads;
        }
        screenResult = 0;
        D_800A305CMainLoop = 0;
        unlockStep = 0;
        if (gScreenStateMainLoop == 0xC) {
            displayPhase = 0;
        } else {
            displayPhase = 0xFF;
            SetDispMaskMainLoop(1);
        }
        if (!(screenResult & 0xFF)) {
            mode13 = 13;
            do {
                CdStopIfPlaybackChangedMainLoop();
                nextIdleFrames = idleFrames + 1;
                idleFrames = nextIdleFrames;
                if ((gScreenStateMainLoop == 0) && (nextIdleFrames >= 0x709)) {
                    screenResult = 1;
                    gScreenStateMainLoop = 0xFD;
                }
                pulseTick = D_800A3724MainLoop - 1;
                D_800A3724MainLoop = pulseTick;
                if (!(pulseTick & 0xFF)) {
                    pulsePhase = D_800A305AMainLoop + 1;
                    D_800A305AMainLoop = pulsePhase;
                    if ((u32)(pulsePhase & 0xFF) >= 0x15U) {
                        D_800A305AMainLoop = 0;
                    }
                    {
                        register s32 pulseValue;
                        s32 magnitude;
                        s32 intensity;
                        pulseValue = D_800A305AMainLoop;
                        /* Intensity is 64 + 8 * abs(pulseValue - 10), modulo 256. */
                        /* addiu; bgez with sll in the delay slot; ori; subu; sll; addiu; andi */
                        magnitude = pulseValue - 10;
                        if (magnitude < 0) {
                            magnitude = 10 - pulseValue;
                        }
                        magnitude = magnitude * 8 + 64;
                        intensity = magnitude & 255;
                        MenuSetShadeColorsMainLoop(intensity, intensity, 0x19U);
                    }
                    D_800A3724MainLoop = 3;
                }
                nextBufferIndex = D_800A305CMainLoop == 0;
                orderingTable =
                    (nextBufferIndex << 0xC) + gOrderingTablesMainLoopSite8;
                D_800A305CMainLoop = nextBufferIndex;
                gOrderingTableBankMainLoopSite9[0] = nextBufferIndex;
                gOrderingTableMainLoopSite10[0] = orderingTable;
                ClearOTagRMainLoop(orderingTable, 0x400);
                GraphicsSelectPrimitiveBufferMainLoop(
                    (s32)(u8)D_800A305CMainLoop);
                func_80057DFCMainLoop();
                func_80057DD4MainLoop();
                func_80053C00MainLoop((s32)(u8)D_800A305CMainLoop,
                                      activePlayer & 0xFF);
                DrawSyncMainLoop(0);
                VSyncMainLoop(0);
                GraphicsPutCurrentEnvironmentsMainLoop();
                if (displayPhase == one) {
                    SetDispMaskMainLoop(1);
                    displayPhase = 2;
                }
                D_800A3710MainLoop = -(D_800A305CMainLoop != 0) & 0x140;
                LoadImageMainLoop(&D_800A3710MainLoop, D_800A35F0MainLoop);
                DrawOTagMainLoop(
                    (u32 *)((u8 *)gOrderingTableMainLoopSite11[0] + 0xFFC));
                if (displayPhase == 0) {
                    displayPhase = 1;
                }
                PadResetAndInitializeBuffersMainLoop(0);
                if (newPad[0] != 0) {
                    idleFrames = 0;
                }
                if (gScreenStateMainLoop == 5) {
                    padBits0 = func_80041B7CMainLoop(0);
                    newPad[0] = padBits0;
                    if ((padBits0 & 0x20) && (D_800A3076MainLoop == 0)) {
                        unlockPhase = unlockStep & 0xFF;
                        if (padBits0 & 0xF000) {
                            if (unlockPhase == one) {
                                goto sequenceOne;
                            }
                            if (unlockPhase < 2) {
                                unlockDirectionBits = padBits0 & 0x1000;
                                if (unlockPhase == 0) {
                                    goto advanceUnlockStep;
                                }
                                goto sequenceDone;
                            }
                            if (unlockPhase == two) {
                                goto sequenceTwo;
                            }
                            if (unlockPhase == 3) {
                                goto sequenceLast;
                            }
                            goto sequenceDone;
                        sequenceOne:
                            unlockDirectionBits = padBits0 & 0x8000;
                            goto advanceUnlockStep;
                        sequenceTwo:
                            unlockDirectionBits = padBits0 & 0x4000;
                        advanceUnlockStep:
                            if (unlockDirectionBits != 0) {
                                unlockStep++;
                            }
                            goto sequenceDone;
                        sequenceLast:
                            if (padBits0 & 0x2000) {
                                D_800A3076MainLoop = one;
                                func_80063180MainLoop(1);
                                SoundPlaySlotMainLoop(0, 8);
                                goto resetUnlockStep;
                            }
                        sequenceDone:;
                        }
                    } else {
                    resetUnlockStep:
                        unlockStep = 0;
                    }
                } else if ((gScreenStateMainLoop == two) &&
                           (D_800A3059MainLoop == one)) {
                    index = 0;
                    sequenceCursor = &playerUnlockSteps[0];
                    selectionCursor = &gPlayerDriverMainLoop;
                readPlayerUnlockSequence:
                    if ((index != one) || (D_800A3644MainLoop != 0)) {
                        selection = *selectionCursor;
                        if ((selection == 5) || (selection == two)) {
                            playerPadBits = func_80041B7CMainLoop(index);
                            (&newPad[0])[index] = playerPadBits;
                            if (playerPadBits & 0x40) {
                                if (playerPadBits & 0x5000) {
                                    sequencePhase = *sequenceCursor;
                                    sequenceValue = sequencePhase & 0xFF;
                                    if (sequenceValue == 0) {
                                        goto playerSequenceFirst;
                                    }
                                    if (sequenceValue == one) {
                                        goto playerSequenceSecond;
                                    }
                                    sequenceCursor++;
                                    goto playerSequenceNext;
                                playerSequenceFirst:
                                    if (playerPadBits & 0x1000) {
                                        *sequenceCursor = sequencePhase + 1;
                                    }
                                    goto advancePlayerUnlockSequence;
                                playerSequenceSecond:
                                    if (!(playerPadBits & 0x4000)) {
                                        goto advancePlayerUnlockSequence;
                                    }
                                    currentSelection = *selectionCursor;
                                    if (currentSelection == two) {
                                        func_80063C34MainLoop(2, 0x19);
                                        func_80063AE0MainLoop(index, 2);
                                        D_800A3065MainLoop ^= 1;
                                        *sequenceCursor = 0;
                                        goto advancePlayerUnlockSequence;
                                    }
                                    if (currentSelection == 5) {
                                        func_80063C34MainLoop(5, 0x18);
                                        func_80063AE0MainLoop(index, 5);
                                        D_800A3064MainLoop ^= 1;
                                    }
                                    goto resetPlayerUnlockSequence;
                                } else {
                                    goto advancePlayerUnlockSequence;
                                }
                            } else {
                            resetPlayerUnlockSequence:
                                *sequenceCursor = 0;
                                goto advancePlayerUnlockSequence;
                            }
                        } else {
                        advancePlayerUnlockSequence:
                            sequenceCursor += 1;
                        }
                    playerSequenceNext:
                        index += 1;
                        selectionCursor += 1;
                        if (index < 2) {
                            goto readPlayerUnlockSequence;
                        }
                    }
                }
                if ((gScreenStateMainLoop == mode13) &&
                    (D_800A3684MainLoopSmall == two) &&
                    (ListHasClearFlagsMainLoop(
                         *gPadPictureMenuListsMainLoopSite13) != 0) &&
                    ((D_800A3644MainLoop == 0) ||
                     ((*D_800A3685MainLoopSite12 == two) &&
                      (ListHasClearFlagsMainLoop(*D_800A37DCMainLoopSite14) !=
                       0)))) {
                    screenResult = 1;
                } else {
                    player = 0;
                    asm("" : "=r"(player) : "0"(player));
                    index = player & 0xFF;
                    do {
                        if ((index == 0) || (D_800A3644MainLoop != 0)) {
                            (&newPad[0])[index] = func_80041B7CMainLoop(index);
                            if ((gScreenStateMainLoop == 7) &&
                                (activePlayer == one)) {
                                if (index != 0) {
                                    newPad[0] = newPad[1];
                                    oldPad[0] = oldPad[1];
                                    goto handlePlayerInput;
                                }
                                goto nextPlayer;
                            }
                            if (player & 0xFF) {
                                if (gScreenStateMainLoop != two) {
                                    if (gScreenStateMainLoop == mode13) {
                                        goto handlePlayerInput;
                                    }
                                    goto nextPlayer;
                                }
                                goto handlePlayerSelection;
                            }
                        handlePlayerInput:
                        handlePlayerSelection:
                            if (gScreenStateMainLoop == mode13) {
                                index = player & 0xFF;
                                if (newPad[index] &
                                    ((u16)~oldPad[index] & 0x800)) {
                                    transitionPhase =
                                        D_800A3684MainLoopSite15[index];
                                    if (transitionPhase == 0) {
                                        SoundPlaySlotMainLoop(0, 3);
                                        if (PadTypeNeedsCalibrationMainLoop(
                                                (s32)(u8)gPadTypeMainLoopSite16
                                                    [index]) &
                                            0xFF) {
                                            func_80062874MainLoop(index, 1);
                                            D_800A3684MainLoopSite17[index] =
                                                one;
                                            func_8006DE68MainLoop(
                                                (u32)index,
                                                (u32)(u8)gPadTypeMainLoopSite18
                                                    [index]);
                                            func_80062F04MainLoop(
                                                index,
                                                gPadTypeMainLoopSite20[index],
                                                gPadLayoutMainLoopSite19
                                                    [index]);
                                            animationStartX = -0x140;
                                            animationNodeSlot =
                                                D_800A3888MainLoopSite21;
                                            animationNodeSlot =
                                                (MenuObj *
                                                     *)((index * 4) +
                                                        (u32)animationNodeSlot);
                                            if (index != 0) {
                                                animationStartX = 0x140;
                                            }
                                            animationStepX = 4;
                                            if (index != 0) {
                                                animationStepX = -4;
                                            }
                                            ListSetFieldsAndEnableMainLoop(
                                                *animationNodeSlot,
                                                animationStartX, 0,
                                                animationStepX);
                                        } else {
                                            func_80062874MainLoop(index, 0);
                                            D_800A3684MainLoopSite22[index] =
                                                two;
                                            goto updateSelectionPanel;
                                        }
                                    } else if (transitionPhase == one) {
                                        SoundPlaySlotMainLoop(0, 3);
                                        PadCalibrateCenterMainLoop(
                                            (u32)index,
                                            (u32)(u8)
                                                gPadTypeMainLoopSite24[index],
                                            (u32)(u8)gPadLayoutMainLoopSite23
                                                [index]);
                                        func_80062874MainLoop(index, 0);
                                        animationEndX = 0x140;
                                        animationNodeSlot =
                                            D_800A3888MainLoopSite25;
                                        animationNodeSlot =
                                            (MenuObj **)((index * 4) +
                                                         (u32)
                                                             animationNodeSlot);
                                        if (index != 0) {
                                            animationEndX = -0x140;
                                        }
                                        animationReverseStepX = -4;
                                        if (index != 0) {
                                            animationReverseStepX = 4;
                                        }
                                        ListSetFieldsAndEnableMainLoop(
                                            *animationNodeSlot, 0,
                                            animationEndX,
                                            animationReverseStepX);
                                        D_800A3684MainLoopSite26[index] = two;
                                        D_800A36E4MainLoopSite27[index] = one;
                                    updateSelectionPanel:
                                        if ((D_800A3684MainLoopSmall != 0) &&
                                            (*D_800A3685MainLoopSite28 != 0)) {
                                            ListSetFieldsAndEnableMainLoop(
                                                *D_800A37F8MainLoopSite29, 0,
                                                0x140, 4);
                                        }
                                    }
                                } else if ((PadTypeNeedsCalibrationMainLoop(
                                                (s32)(u8)gPadTypeMainLoopSite31
                                                    [index]) &
                                            0xFF) &&
                                           (D_800A3684MainLoopSite30[index] ==
                                            one)) {
                                    PadCalibrateRangeMainLoop(
                                        (u32)index,
                                        (u32)(u8)gPadTypeMainLoopSite33[index],
                                        (u32)(u8)
                                            gPadLayoutMainLoopSite32[index]);
                                }
                            }
                            {
                                register s32 previousPadZero;
                                register s32 currentPadZero;
                                /* Read both pads before forming the pressed-edge mask. */
                                /* lw; lw; nor */
                                previousPadZero = oldPad[0];
                                currentPadZero = newPad[0];
                                previousPadInverse = ~previousPadZero;
                                if (currentPadZero &
                                    ((u16)previousPadInverse & 0x40)) {
                                    s32 confirmPivot;
                                    s32 confirmMode;
                                    screenResult = func_80056B5CMainLoop(
                                        (s32)D_800A3059MainLoop,
                                        (s32)gScreenStateMainLoop,
                                        (s32)D_800A3950MainLoop);
                                    if (screenResult & 0xFF) {

                                        if ((u32)(gScreenStateMainLoop -
                                                  0x10) >= 2U) {
                                            SoundPlaySlotMainLoop(0, 3);
                                        }
                                    } else {
                                        confirmPivot = 0x24;
                                        confirmMode = gScreenStateMainLoop;
                                        if (confirmMode == confirmPivot) {
                                            goto confirmMode24;
                                        }
                                        if (confirmMode < 0x25) {
                                            if (confirmMode == 0x21) {
                                                goto confirmMode21;
                                            }
                                            if (confirmMode < 0x22) {
                                                if (confirmMode == one) {
                                                    goto confirmMode1;
                                                }
                                                if (confirmMode == 5) {
                                                    goto confirmMode5;
                                                }
                                                goto finishInput;
                                            }
                                            if (confirmMode == 0x22) {
                                                goto confirmMode22;
                                            }
                                            if (confirmMode == 0x23) {
                                                goto confirmMode23;
                                            }
                                            goto finishInput;
                                        }
                                        if (confirmMode == 0x27) {
                                            goto confirmMode25;
                                        }
                                        if (confirmMode < 0x28) {
                                            if (confirmMode == 0x25) {
                                                goto confirmMode25;
                                            }
                                            if (confirmMode == 0x26) {
                                                goto confirmMode26;
                                            }
                                            goto finishInput;
                                        }
                                        if (confirmMode == 0x28) {
                                            goto confirmMode28;
                                        }
                                        if (confirmMode != 0xFC) {
                                            goto finishInput;
                                        }
                                    confirmModeFC:
                                        {
                                            s32 exitPhase;
                                            s32 exitChannel;
                                            s32 exitTone;
                                            exitPhase = D_800A3928MainLoop;
                                            if (exitPhase == 0) {
                                                goto confirmExitStatus;
                                            }
                                            exitChannel = 0;
                                            if (exitPhase == one) {
                                                goto confirmExitSound;
                                            }
                                            goto finishInput;
                                        confirmExitStatus:
                                            exitPhase =
                                                gCardMenuMessageMainLoop[0];
                                            exitChannel = 0;
                                            if (exitPhase != mode13) {
                                                goto confirmExitSound;
                                            }
                                            exitTone = 4;
                                            goto confirmExit;
                                        confirmExitSound:
                                            exitTone = 3;
                                        confirmExit:
                                            screenResult = 1;
                                            SoundPlaySlotMainLoop(exitChannel,
                                                                  exitTone);
                                            goto finishInput;
                                        }
                                    confirmMode1:
                                        SoundPlaySlotMainLoop(0, 3);
                                        if ((D_800A3059MainLoop == two &&
                                             D_800A3950MainLoop != 0) ||
                                            D_800A3059MainLoop == one) {
                                            CardEnableAndTestEventsMainLoop();
                                            if ((CardProbeSlotsMainLoop() &
                                                 0xFF) == two) {
                                                gScreenStateMainLoop = 0x28;
                                                CardMenuCenterSelectedTextMainLoop(
                                                    5);
                                                menuCode = 1;
                                            } else {
                                                menuCode =
                                                    CardLoadNameListMainLoop(
                                                        0xFF);
                                            }
                                            func_80057008MainLoop(menuCode &
                                                                  0xFF);
                                            CardTestAndDisableEventsMainLoop();
                                            func_80057160MainLoop(1);
                                        } else if (D_800A3059MainLoop == 6) {
                                            if (D_800B9B84MainLoop[0] == 0) {
                                                screenResult = 1;
                                                goto finishInput;
                                            }
                                            CardMenuCenterSelectedTextMainLoop(
                                                2);
                                            gCardMenuMessageMainLoop[0] = 0x15;
                                            CardMenuShowMessageMainLoop(0);
                                            animateX = -0x78;
                                            animateY = 0;
                                            animateStep = 2;
                                            dialogScreen = 0x25;
                                            goto showConfirmDialog;
                                        } else if (D_800A3059MainLoop == 0 &&
                                                   D_800A3950MainLoop != 0) {
                                            CardMenuCenterSelectedTextMainLoop(
                                                4);
                                            gCardMenuMessageMainLoop[0] = 0x18;
                                            CardMenuShowMessageMainLoop(0);
                                            animateX = -0x78;
                                            animateY = 0;
                                            animateStep = 2;
                                            dialogScreen = 0x27;
                                        showConfirmDialog:
                                            gScreenStateMainLoop = dialogScreen;
                                            CardMenuSetColorNodeLayoutMainLoop(
                                                animateX, animateY,
                                                animateStep);
                                            MenuNegateLinkedObjectValuesMainLoop(
                                                0);
                                        }
                                        goto finishInput;
                                    confirmMode5:
                                        if ((u32)(D_800A3059MainLoop - 2) <
                                            2U) {
                                            SoundPlaySlotMainLoop(0, 3);
                                            if (D_800A3059MainLoop == 3) {
                                                SoundRunSlotEnvelopeMainLoop(0,
                                                                             1);
                                                func_8003CCE0MainLoop(0);
                                                gCdAudioEnabledMainLoop[0] = 0;
                                            }
                                            MenuCenterTextMainLoop(
                                                D_800A3059MainLoop - 2);
                                            MenuSetVolumeMainLoop(
                                                (s16)D_800A3690MainLoop
                                                    [D_800A3059MainLoop],
                                                D_800A3059MainLoop - 2);
                                            MenuSetLinkedObjectLayoutMainLoop(
                                                -0x78, 0, 2);
                                            gScreenStateMainLoop = 0x21;
                                            MenuUpdateItemRowMainLoop(0x21);
                                        }
                                        goto finishInput;
                                    confirmMode21:
                                        SoundPlaySlotMainLoop(0, 3);
                                        MenuSetLinkedObjectLayoutMainLoop(
                                            0, -0x78, -2);
                                        gScreenStateMainLoop = 5;
                                        MenuUpdateItemRowMainLoop(5);
                                        if (D_800A3059MainLoop == 3) {
                                            SoundRunSlotEnvelopeMainLoop(2, 1);
                                            CdEnablePlaybackAndSetVolumeMainLoop();
                                        }
                                        goto finishInput;
                                    confirmMode28:
                                        SoundPlaySlotMainLoop(0, 3);
                                        CardEnableAndTestEventsMainLoop();
                                        cardMenuCode = CardLoadNameListMainLoop(
                                            D_800A358CMainLoop[0]);
                                        gScreenStateMainLoop = one;
                                        func_80057008MainLoop(cardMenuCode &
                                                              0xFF);
                                        CardTestAndDisableEventsMainLoop();
                                        func_80057160MainLoop(0);
                                        goto finishInput;
                                    confirmMode22:
                                        SoundPlaySlotMainLoop(0, 3);
                                        gScreenStateMainLoop = 0x23;
                                        CardMenuAppendTrackNameMainLoop();
                                        func_8006C9F8MainLoop();
                                        gCardMenuMessageMainLoop[0] = 0;
                                        MenuUpdateItemRowMainLoop(
                                            gScreenStateMainLoop);
                                        goto finishInput;
                                    confirmMode23:
                                        {
                                            s32 scanPhase;
                                            scanPhase = D_800A3928MainLoop;
                                            returnChannel = 0;
                                            if (scanPhase == 0) {
                                                goto confirmScan;
                                            }
                                            actionSound = 3;
                                            if (scanPhase == one) {
                                                goto returnMainMenu;
                                            }
                                            goto finishInput;
                                        confirmScan:
                                            {
                                                SoundPlaySlotMainLoop(0, 3);
                                                if (func_8006D178MainLoop() ==
                                                    0) {
                                                    SoundStopSlotMainLoop(0);
                                                } else {
                                                    MenuHideCurrentObjectMainLoop();
                                                    if (gCardMenuMessageMainLoop
                                                            [0] == 0) {
                                                        if (CardMenuCheckTrackNameCapacityMainLoop() ==
                                                            one) {
                                                            goto refreshCardMenu;
                                                        }
                                                        if (gCardMenuMessageMainLoop
                                                                [0] == 0) {
                                                            goto updateCardStatus;
                                                        }
                                                    }
                                                    if (gCardMenuMessageMainLoop
                                                            [0] == 0x10) {
                                                    updateCardStatus:
                                                        CardEnableAndTestEventsMainLoop();
                                                        if (!(CardResolveSlotMainLoop() &
                                                              0xFF)) {
                                                            CardMenuShowMessageMainLoop(
                                                                0);
                                                            if (gCardMenuMessageMainLoop
                                                                    [0] !=
                                                                mode13) {
                                                                D_800A3928MainLoop =
                                                                    one;
                                                            }
                                                        }
                                                        CardTestAndDisableEventsMainLoop();
                                                        if (gCardMenuMessageMainLoop
                                                                [0] == mode13) {
                                                            goto finishInput;
                                                        }
                                                    }
                                                    if (gCardMenuMessageMainLoop
                                                            [0] == mode13) {
                                                        SoundStopSlotMainLoop(
                                                            0);
                                                        goto playBackSound;
                                                    }
                                                    goto checkCardMenuReady;
                                                }
                                            }
                                            goto finishInput;
                                        }
                                    confirmMode24:
                                        SoundPlaySlotMainLoop(0, 3);
                                        menuPhase = D_800A3928MainLoop;
                                        if (menuPhase == one) {
                                            goto confirmStageOne;
                                        }
                                        if (menuPhase < 2) {
                                            if (menuPhase == 0) {
                                                goto confirmStageZero;
                                            }
                                            goto finishInput;
                                        }
                                        if (menuPhase == two) {
                                            goto confirmStageTwo;
                                        }
                                        goto finishInput;
                                    confirmStageZero:
                                        gCardMenuMessageMainLoop[0] = 0x17;
                                        cardOperation = 0;
                                        goto startCardOperation;
                                    confirmStageOne:
                                        if (func_8006D258MainLoop() == one) {
                                            gCardMenuMessageMainLoop[0] = 0x12;
                                        }
                                        D_800A3928MainLoop = two;
                                    refreshCardMenu:
                                        CardMenuShowMessageMainLoop(0);
                                        goto finishInput;
                                    confirmStageTwo:
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        if (D_800A3968MainLoop[0] != 0) {
                                            D_800A3950MainLoop = 0x24;
                                        }
                                        goto finishMainMenuReturn;
                                    confirmMode25:
                                        SoundPlaySlotMainLoop(0, 3);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        screenResult = 1;
                                        gScreenStateMainLoop = screenResult;
                                        goto finishInput;
                                    confirmMode26:
                                        SoundPlaySlotMainLoop(0, 3);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        gScreenStateMainLoop = 7;
                                        RaceBuildQualifyingGridMainLoop(
                                            gSelectedTrackMainLoop);
                                        screenResult = 0xFF;
                                        goto finishInput;
                                    }
                                    goto finishInput;
                                }
                                if (currentPadZero &
                                    ((u16)previousPadInverse & 0x10)) {
                                    if (gScreenStateMainLoop == 7) {

                                        if (D_800A3950MainLoop == 0xFB) {
                                            SoundPlaySlotMainLoop(0, 4);
                                            gScreenStateMainLoop = 0x26;
                                            gCardMenuMessageMainLoopSite51[0] =
                                                0x16;
                                            CardMenuShowMessageMainLoop(0);
                                            CardMenuCenterSelectedTextMainLoop(
                                                3);
                                            CardMenuSetColorNodeLayoutMainLoop(
                                                -0x78, 0, 2);
                                        }
                                    } else {
                                        screenResult = func_80056B0CMainLoop(
                                            (s32)gScreenStateMainLoop,
                                            (s32)D_800A3950MainLoop);
                                        if (screenResult & 0xFF) {
                                            SoundPlaySlotMainLoop(0, 4);

                                        } else {
                                            goto storePadStates;
                                        }
                                    }
                                    goto finishInput;
                                }
                                if (currentPadZero &
                                    ((u16)previousPadInverse & 0x80)) {
                                    s32 cancelPivot;
                                    s32 cancelMode;
                                    cancelPivot = 0x25;
                                    cancelMode = gScreenStateMainLoop;
                                    switch (cancelMode) {
                                    case 0xFC:
                                        if (gCardMenuMessageMainLoop[0] !=
                                                two &&
                                            D_800A3928MainLoop == 0) {
                                            s32 cardStatus;
                                            SoundPlaySlotMainLoop(0, 3);
                                            CardEnableAndTestEventsMainLoop();
                                            CardResolveSlotMainLoop();
                                            cardStatus =
                                                func_80069EB8MainLoop() & 0xFF;
                                            if (cardStatus == 0) {
                                                cardStatus = 4;
                                            } else {
                                                cardStatus = 0x13;
                                            }
                                            gCardMenuMessageMainLoop[0] =
                                                cardStatus;
                                            CardTestAndDisableEventsMainLoop();
                                            cardOperation = 1;
                                        startCardOperation:
                                            CardMenuShowMessageMainLoop(
                                                cardOperation);
                                            D_800A3928MainLoop = one;
                                        }
                                        break;
                                    case 0x23:
                                        if (D_800A3928MainLoop == 0) {
                                            if (gCardMenuMessageMainLoop[0] ==
                                                    mode13 ||
                                                (u32)(gCardMenuMessageMainLoop
                                                          [0] -
                                                      0x19) < 2U) {
                                                SoundPlaySlotMainLoop(0, 3);
                                                CardEnableAndTestEventsMainLoop();
                                                if (!(func_80069EB8MainLoop() &
                                                      0xFF)) {
                                                    gCardMenuMessageMainLoop
                                                        [0] = 4;
                                                    CardMenuShowMessageMainLoop(
                                                        0);
                                                    D_800A3928MainLoop = one;
                                                    MenuUpdateItemRowMainLoop(
                                                        0xA);
                                                } else {
                                                    CardTestAndDisableEventsMainLoop();
                                                checkCardMenuReady:
                                                    if (gCardMenuMessageMainLoop
                                                            [0] == 0) {
                                                        CardMenuWriteSaveSlotMainLoop();
                                                        CardMenuShowMessageMainLoop(
                                                            0);
                                                        D_800A3928MainLoop =
                                                            one;
                                                        MenuUpdateItemRowMainLoop(
                                                            0xA);
                                                    }
                                                }
                                            } else {
                                                goto playBackSound;
                                            }
                                        }
                                        break;
                                    case 0x24:
                                    playBackSound:
                                        returnChannel = 0;
                                        actionSound = 4;
                                    returnMainMenu:
                                        SoundPlaySlotMainLoop(returnChannel,
                                                              actionSound);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                    finishMainMenuReturn:
                                        gScreenStateMainLoop = one;
                                        MenuUpdateItemRowMainLoop(1);
                                        break;
                                    case 0x22:
                                    case 0x28:
                                        goto playBackSound;
                                    case 0x25:
                                    case 0x27:
                                        SoundPlaySlotMainLoop(0, 4);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        gScreenStateMainLoop = one;
                                        break;
                                    case 0x26:
                                        SoundPlaySlotMainLoop(0, 4);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        gScreenStateMainLoop = 7;
                                        break;
                                    }
                                    goto finishInput;
                                }
                                /* End the old register lifetime before setting the pad index. */
                                index = player & 0xFF;
                                padBits = newPad[index];
                                if (padBits &
                                    ((u16)previousPadInverse & 0x20)) {

                                    if (gScreenStateMainLoop == 0x23) {
                                        func_8006CE64MainLoop();
                                    }
                                    goto finishInput;
                                }
                                if (padBits & 0x1000) {
                                    register s32 padEdgeUp;
                                    s32 blockedModeUp;
                                    s32 cardModeUp;
                                    s32 rawModeUp;
                                    s32 modeUp;
                                    blockedModeUp = 0x21;
                                    /* Retain the raw mode byte and its comparison value. */
                                    rawModeUp = (u8)gScreenStateMainLoop;
                                    modeUp = rawModeUp & 255;
                                    if ((modeUp != blockedModeUp) &&
                                        (modeUp != 0xFC) &&
                                        ((u32)(rawModeUp - 0x25) >= 2U) &&
                                        (modeUp != mode13) &&
                                        (modeUp != 0x27) && (modeUp != 0xE)) {
                                        if (((u32)(rawModeUp - 9) < 2U) ||
                                            (modeUp == 0xC) ||
                                            ((u32)(rawModeUp - 0x10) < 2U)) {
                                            func_80068AC4MainLoop(newPad[0],
                                                                  oldPad[0], 1);

                                            goto finishInput;
                                        }
                                        cardModeUp = 0x23;
                                        if (modeUp == cardModeUp) {
                                            if (D_800A3928MainLoop == one) {
                                                goto nextPlayer;
                                            }
                                            if (D_800A3770MainLoopSite57[0] !=
                                                0) {
                                                goto nextPlayer;
                                            }
                                            menuDirection = 1;
                                            goto moveCardCursor;
                                        }
                                        padEdgeUp = previousPadInverse & 0x1000;
                                        if (currentPadZero & padEdgeUp) {
                                            if ((modeUp == 0x22) ||
                                                (modeUp == 0x24) ||
                                                (modeUp == 0x28)) {
                                                if (D_800A3770MainLoopSite58
                                                        [0] == 0) {
                                                    if (func_8006C700MainLoop(
                                                            0,
                                                            gScreenStateMainLoop ==
                                                                0x22) &
                                                        0xFF) {
                                                        SoundPlaySlotMainLoop(
                                                            0, 0);

                                                    } else {
                                                        goto storePadStates;
                                                    }
                                                    goto finishInput;
                                                }
                                            } else {
                                                SoundPlaySlotMainLoop(0, 0);
                                                wrappedItemUp =
                                                    D_800A3059MainLoop;
                                                if (wrappedItemUp == 0) {
                                                    wrappedItemUp =
                                                        D_800A38E8MainLoopSite59
                                                            [0] -
                                                        1;
                                                } else {
                                                    wrappedItemUp -= 1;
                                                }
                                                do {
                                                    D_800A3059MainLoop =
                                                        wrappedItemUp;
                                                } while (0);

                                                if (gScreenStateMainLoop ==
                                                    two) {

                                                    if (D_800A3988MainLoopSmall ==
                                                        0) {
                                                        if ((u32)(D_800A3059MainLoopPostUp -
                                                                  4) < 2U) {
                                                            D_800A3059MainLoopPostUp =
                                                                3;

                                                        } else {
                                                            goto storePadStates;
                                                        }
                                                    }
                                                    goto finishInput;
                                                }
                                                if ((gScreenStateMainLoop ==
                                                     one) &&
                                                    (D_800A3950MainLoop == 0)) {

                                                    if ((u32)(D_800A3059MainLoopPostUp -
                                                              2) < 4U) {
                                                        D_800A3059MainLoopPostUp =
                                                            one;

                                                    } else {
                                                        goto finishInput;
                                                    }
                                                } else {
                                                    if (gScreenStateMainLoop ==
                                                        3) {

                                                        if (D_800A3644MainLoop !=
                                                            0) {
                                                            itemUp =
                                                                D_800A3059MainLoopPostUp &
                                                                0xFF;
                                                            if (itemUp == 3) {
                                                                D_800A3059MainLoopPostUp -=
                                                                    2;

                                                            } else if (itemUp ==
                                                                       two) {
                                                                D_800A3059MainLoopPostUp -=
                                                                    1;

                                                            } else {
                                                                goto storePadStates;
                                                            }
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if (gScreenStateMainLoop ==
                                                        4) {
                                                        itemCursorUp =
                                                            D_800A3059MainLoopPostUp;

                                                        if (D_800A3988MainLoopSite60
                                                                [itemCursorUp &
                                                                 0xFF] &
                                                            0x80) {
                                                            do {
                                                                nextItemUp =
                                                                    itemCursorUp -
                                                                    1;
                                                                D_800A3059MainLoopPostUp =
                                                                    nextItemUp;
                                                                itemCursorUp =
                                                                    nextItemUp;
                                                            } while (
                                                                D_800A3988MainLoopSite61
                                                                    [nextItemUp &
                                                                     0xFF] &
                                                                0x80);
                                                        }
                                                        goto finishInput;
                                                    }

                                                    if (gScreenStateMainLoop ==
                                                        5) {

                                                        if (D_800A3059MainLoopPostUp ==
                                                            5) {

                                                            if (D_800A3076MainLoop ==
                                                                0) {
                                                                D_800A3059MainLoopPostUp -=
                                                                    1;
                                                            }
                                                            goto finishInput;
                                                        }
                                                    } else {
                                                        goto finishInput;
                                                    }
                                                }
                                                goto updatePreviousPad;
                                            }
                                        } else {
                                            goto storePadStates;
                                        }
                                        goto nextPlayer;
                                    }
                                    goto nextPlayer;
                                }
                                if (padBits & 0x4000) {
                                    register s32 padEdgeDown;
                                    s32 blockedModeDown;
                                    s32 cardModeDown;
                                    s32 rawModeDown;
                                    register s32 modeDown;
                                    blockedModeDown = 0x21;
                                    /* Retain the raw mode byte and its comparison value. */
                                    rawModeDown = (u8)gScreenStateMainLoop;
                                    modeDown = rawModeDown & 255;
                                    if ((modeDown != blockedModeDown) &&
                                        (modeDown != 0xFC) &&
                                        ((u32)(rawModeDown - 0x25) >= 2U) &&
                                        (modeDown != mode13) &&
                                        (modeDown != 0x27) &&
                                        (modeDown != 0xE)) {
                                        if (((u32)(rawModeDown - 9) < 2U) ||
                                            (modeDown == 0xC) ||
                                            ((u32)(rawModeDown - 0x10) < 2U)) {
                                            func_80068AC4MainLoop(newPad[0],
                                                                  oldPad[0], 0);

                                            goto finishInput;
                                        }
                                        cardModeDown = 0x23;
                                        if (modeDown == cardModeDown) {
                                            if (D_800A3928MainLoop == one) {
                                                goto nextPlayer;
                                            }
                                            if (D_800A3770MainLoopSite62[0] !=
                                                0) {
                                                goto nextPlayer;
                                            }
                                            menuDirection = 0;
                                        moveCardCursor:
                                            player += 1;
                                            /* guess: the asm passes leftover a1 and a2; func_8006CB80 tests
                                             * arg1 & ~arg2 as a pad edge, so give it the pad states. */
                                            func_8006CB80MainLoop(menuDirection,
                                                                  newPad[0],
                                                                  oldPad[0]);
                                            oldPad[0] = newPad[0];
                                        } else {
                                            padEdgeDown =
                                                previousPadInverse & 0x4000;
                                            if (currentPadZero & padEdgeDown) {
                                                if ((modeDown == 0x22) ||
                                                    (modeDown == 0x24) ||
                                                    (modeDown == 0x28)) {
                                                    if (D_800A3770MainLoopSite63
                                                            [0] == 0) {
                                                        if (func_8006C700MainLoop(
                                                                1,
                                                                gScreenStateMainLoop ==
                                                                    0x22) &
                                                            0xFF) {
                                                            SoundPlaySlotMainLoop(
                                                                0, 1);

                                                        } else {
                                                            goto storePadStates;
                                                        }
                                                        goto finishInput;
                                                    }
                                                } else {
                                                    SoundPlaySlotMainLoop(0, 1);
                                                    if ((D_800A3059MainLoop &
                                                         0xFF) ==
                                                        (D_800A38E8MainLoopSite64
                                                             [0] -
                                                         1)) {
                                                        D_800A3059MainLoop = 0;
                                                    } else {
                                                        D_800A3059MainLoop += 1;
                                                    }
                                                    if (gScreenStateMainLoop ==
                                                        two) {

                                                        if (D_800A3988MainLoopSmall ==
                                                            0) {

                                                            if (D_800A3059MainLoopPostDown ==
                                                                4) {
                                                                /* Keep the two skip paths separate until the store. */
                                                                asm volatile(
                                                                    ""
                                                                    :
                                                                    :
                                                                    : "memory");
                                                                goto skipLockedItems;
                                                            }
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if ((gScreenStateMainLoop ==
                                                         one) &&
                                                        (D_800A3950MainLoop ==
                                                         0)) {
                                                        if ((u32)(D_800A3059MainLoopPostDown -
                                                                  2) < 4U) {
                                                        skipLockedItems:
                                                            D_800A3059MainLoopPostDown =
                                                                6;

                                                        } else {
                                                            goto storePadStates;
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if (gScreenStateMainLoop ==
                                                        3) {

                                                        if (D_800A3644MainLoop !=
                                                            0) {
                                                            itemDown =
                                                                D_800A3059MainLoopPostDown &
                                                                0xFF;
                                                            if (itemDown ==
                                                                two) {
                                                                D_800A3059MainLoopPostDown +=
                                                                    2;

                                                            } else if (
                                                                itemDown ==
                                                                gScreenStateMainLoop) {
                                                                D_800A3059MainLoopPostDown +=
                                                                    1;

                                                            } else {
                                                                goto storePadStates;
                                                            }
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if (gScreenStateMainLoop ==
                                                        4) {
                                                        itemCursorDown =
                                                            D_800A3059MainLoopPostDown;

                                                        if (D_800A3988MainLoopSite65
                                                                [itemCursorDown &
                                                                 0xFF] &
                                                            0x80) {
                                                            do {
                                                                nextItemDown =
                                                                    itemCursorDown +
                                                                    1;
                                                                D_800A3059MainLoopPostDown =
                                                                    nextItemDown;
                                                                itemCursorDown =
                                                                    nextItemDown;
                                                            } while (
                                                                D_800A3988MainLoopSite66
                                                                    [nextItemDown &
                                                                     0xFF] &
                                                                0x80);
                                                        }
                                                        goto finishInput;
                                                    }

                                                    if (gScreenStateMainLoop !=
                                                        5) {
                                                        goto finishInput;
                                                    }
                                                    if (D_800A3059MainLoopPostDown !=
                                                        gScreenStateMainLoop) {
                                                        goto finishInput;
                                                    }
                                                    if (D_800A3076MainLoop !=
                                                        0) {
                                                        goto finishInput;
                                                    }
                                                    D_800A3059MainLoopPostDown =
                                                        0;
                                                    goto updatePreviousPad;
                                                }
                                            } else {
                                                goto storePadStates;
                                            }
                                            goto nextPlayer;
                                        }
                                    } else {
                                        goto nextPlayer;
                                    }
                                } else {
                                    if (padBits & 0x8000) {
                                        if (gScreenStateMainLoop == mode13 &&
                                            (padBits &
                                             ((u16)~oldPad[index] & 0x8000))) {
                                            if (!(PadTypeNeedsCalibrationMainLoop(
                                                      (u8)gPadTypeMainLoopSite68
                                                          [index]) &
                                                  0xFF) ||
                                                D_800A3684MainLoopSite67
                                                        [index] != one) {
                                                if (D_800A3684MainLoopSite69
                                                        [index] == 0) {
                                                    SoundPlaySlotMainLoop(0, 2);
                                                    {
                                                        s32 variantCount;
                                                        s32 variantValue;
                                                        s32 countMinusOne;
                                                        s32 variantRemainder;
                                                        variantCount =
                                                            D_800A3080MainLoopSite70
                                                                [gPadTypeMainLoopSite71
                                                                     [index]];
                                                        variantValue =
                                                            gPadLayoutMainLoopSite72
                                                                [index];
                                                        countMinusOne =
                                                            variantCount - 1;
                                                        variantValue +=
                                                            countMinusOne;
                                                        variantRemainder =
                                                            variantValue %
                                                            variantCount;
                                                        gPadLayoutMainLoopSite72
                                                            [index] =
                                                                variantRemainder;
                                                    }
                                                }
                                            }
                                        } else if (gScreenStateMainLoop ==
                                                       two &&
                                                   D_800A3059MainLoop == one) {
                                            MenuHandleOptionsInputMainLoop(
                                                2, 1, 1, newPad[player & 0xFF],
                                                oldPad[player & 0xFF],
                                                player & 0xFF);
                                        } else {
                                            MenuHandleOptionsInputMainLoop(
                                                gScreenStateMainLoop,
                                                D_800A3059MainLoop, 1,
                                                newPad[0], oldPad[0],
                                                activePlayer);
                                        }
                                    } else if (padBits & 0x2000) {
                                        if (gScreenStateMainLoop == mode13 &&
                                            (padBits &
                                             ((u16)~oldPad[index] & 0x2000))) {
                                            if (!(PadTypeNeedsCalibrationMainLoop(
                                                      (u8)gPadTypeMainLoopSite74
                                                          [index]) &
                                                  0xFF) ||
                                                D_800A3684MainLoopSite73
                                                        [index] != one) {
                                                if (D_800A3684MainLoopSite75
                                                        [index] == 0) {
                                                    SoundPlaySlotMainLoop(0, 2);
                                                    gPadLayoutMainLoopSite76[index] =
                                                        (gPadLayoutMainLoopSite76
                                                             [index] +
                                                         1) %
                                                        D_800A3080MainLoopSite77
                                                            [gPadTypeMainLoopSite78
                                                                 [index]];
                                                }
                                            }
                                        } else if (gScreenStateMainLoop ==
                                                       two &&
                                                   D_800A3059MainLoop == one) {
                                            MenuHandleOptionsInputMainLoop(
                                                2, 1, 0, newPad[player & 0xFF],
                                                oldPad[player & 0xFF],
                                                player & 0xFF);
                                        } else {
                                            MenuHandleOptionsInputMainLoop(
                                                gScreenStateMainLoop,
                                                D_800A3059MainLoop, 0,
                                                newPad[0], oldPad[0],
                                                activePlayer);
                                        }
                                    }
                                storePadStates:
                                finishInput:

                                updatePreviousPad:
                                    oldPad[player & 0xFF] =
                                        newPad[player & 0xFF];
                                    goto nextPlayer;
                                }
                            }
                        } else {
                        nextPlayer:
                            player += 1;
                        }
                        index = (u8)player;
                    } while ((u32)(player & 0xFF) < 2U);
                }
            } while (!(screenResult & 0xFF));
        }
        DrawSyncMainLoop(0);
        if (gScreenStateMainLoop == 7) {
            func_80057DE8MainLoop();
        }
        screenResultByte = screenResult & 0xFF;
        if (gScreenStateMainLoop != 0xFD) {
            nextScreen = MenuUpdateScreenStateMainLoop(
                gScreenStateMainLoop, &D_800A3950MainLoop, screenResultByte);
            gScreenStateMainLoop = nextScreen;
            if ((nextScreen & 0xFF) == 7) {
                activePlayer = 0;
            }
            if ((D_800A3950MainLoop == 7) && !(activePlayer & 0xFF) &&
                (D_800A3644MainLoop != 0) && (*D_800A3A25MainLoopSite79 != 0) &&
                (screenResultByte != 0xFF)) {
                activePlayer = 1;
                D_800A3950MainLoop = nextScreen;
                gScreenStateMainLoop = 7;
                D_800A3059MainLoop = 0;
            }
        }
        if ((gScreenStateMainLoop == 0xFF) || (gScreenStateMainLoop == 0xFD) ||
            (gScreenStateMainLoop == 0xF8)) {
            exitLoop = 1;
        }
    } while (exitLoop == 0);
    VSyncMainLoop(0);
    VSyncMainLoop(0);
    do {

    } while (func_8003F4FCMainLoop(0) & 0xFF);
}
#else
void func_80053D40(void) {
    s32 newPad[2];
    s32 oldPad[2];
    u8 playerUnlockSteps[2];
    s32 one;
    s32 two;
    s32 mode13;
    u8 exitLoop;
    u8 displayPhase;
    s32 idleFrames;
    s32 animationStartX;
    s32 animationEndX;
    s32 animationStepX;
    s32 animationReverseStepX;
    s32 *previousPadCursor;
    register s32 *currentPadCursor asm("s2");
    s32 argument0;
    s32 menuPhase;
    s32 animateX;
    s32 animateY;
    s32 animateStep;
    register MenuObj **animationNodeSlot asm("v0");
    s32 padBits;
    s32 previousPadInverse;
    s32 nextIdleFrames;
    s32 cardMenuCode;
    s32 nextBufferIndex;
    s32 padBits0;
    s32 playerPadBits;
    s32 sequenceValue;
    s32 unlockPhase;
    s32 itemUp;
    s32 itemDown;
    s32 cardOperation;
    s32 menuDirection;
    s32 activePlayer;
    s32 index;
    s32 player;
    s32 screenResult;
    register s32 unlockStep asm("s7");
    s32 unlockDirectionBits;
    s32 dialogScreen;
    s32 actionSound;
    s32 returnChannel;
    u32 *orderingTable;
    u8 *screenTable;
    register u8 *sequenceCursor asm("s1");
    u8 *selectionCursor;
    s32 screenResultByte;
    u8 pulseTick;
    u8 transitionPhase;
    u8 nextItemUp;
    u8 nextItemDown;
    u8 nextScreen;
    u8 pulsePhase;
    u8 selection;
    u8 currentSelection;
    u8 sequencePhase;
    u8 itemCursorUp;
    u8 itemCursorDown;
    u8 secondPlayerEnabled;
    u8 menuCode;
    s32 wrappedItemUp;

    playerUnlockSteps[0] = 0;
    playerUnlockSteps[1] = 0;
    MenuObjResetPoolMainLoop();
    func_8005DAD4MainLoop();
    func_8005DFA0MainLoop();
    idleFrames = 0;
    if ((u8)gSelectedTrackMainLoop < 0x11U) {
        screenTable = D_800AE178MainLoopSite1[gSelectedTrackMainLoop];
    } else {
        screenTable = *D_800AE178MainLoopSite2;
    }
    activePlayer = 0;
    func_8005E4A4MainLoop(screenTable);
    one = 1;
    two = 2;
    D_800A3608MainLoop = 0;
    exitLoop = 0;
    do {
        {
            s32 randomScale;
            /* The original call retains the incoming a0 and ignores the result. */
            asm("" : "=r"(randomScale));
            RandomScaledGetMainLoop(randomScale);
        }
        func_80057DE8MainLoop();
        func_80057E10MainLoop();
        MenuObjRestorePoolCursorMainLoop();
        argument0 = gScreenStateMainLoop;
        asm("" : "=r"(argument0) : "0"(argument0));
        if (argument0 == 0xFC) {
            PadResetAndInitializeBuffersMainLoop(0);
            func_8006DA40MainLoop();
            D_800A3928MainLoop = 0;
        } else if (argument0 == 9) {
            if (*D_800A3A58MainLoopSite3 == 0) {
                CardEnableAndTestEventsMainLoop();
                if (CardResolveSlotMainLoop() & 0xFF) {
                    CardLoadSaveTableMainLoop(0);
                }
                CardTestAndDisableEventsMainLoop();
            }
            CardMenuCreateRecordTableMainLoop((s32)gSelectedTrackMainLoop);
        } else if (argument0 == 0xA) {
            func_80068CE4MainLoop();
        } else if (argument0 == 0xC) {
            CardMenuCreateStandingsTableMainLoop();
        } else if (argument0 == 0xE) {
            func_80064208MainLoop();
        } else if ((u32)(gScreenStateMainLoop - 0x10) < 2U) {
            func_800697ECMainLoop(argument0 - 0x10);
        } else {
            func_80056C84MainLoop(argument0, activePlayer);
            func_8005C124MainLoop(gScreenStateMainLoop, D_800A3059MainLoop);
        }
        MenuCreateItemRowMainLoop(gScreenStateMainLoop);
        func_80056F04MainLoop((s32)gScreenStateMainLoop);
        switch (gScreenStateMainLoop) {
        case 0:
            idleFrames = 0;
            goto initializePads;
        case 7:
            secondPlayerEnabled = 0;
            argument0 = activePlayer & 0xFF;
            if (((D_800A3950MainLoop == 0xFB) || (D_800A3950MainLoop == 3)) &&
                (D_800A3644MainLoop != 0)) {
                secondPlayerEnabled = 1;
            }
            func_8005ED74MainLoop(argument0, secondPlayerEnabled);
            /* End the old register lifetime before setting the pad index. */
            asm volatile("" : "=r"(index));
            index = 0;
            if (D_800A3950MainLoop == 0xFB) {
            case 1:
                index = 0;
                CardMenuBuildFileListMainLoop();
                currentPadCursor = &newPad[0];
            } else {
                goto resetPadArray;
            }
            break;
        case 2:
        case 8:
            index = 0;
            D_800A3980MainLoop =
                DriverFindIndexByIdMainLoop(gPlayerDriverMainLoop);
            D_800A3981MainLoopSite5[0] =
                DriverFindIndexByIdMainLoop(D_800A36E1MainLoopSite4[0]);
            currentPadCursor = &newPad[0];
            break;
        case 5:
            index = 0;
            func_800606D4MainLoop();
            func_80063180MainLoop((s32)D_800A3076MainLoop);
            currentPadCursor = &newPad[0];
            break;
        case 13:
            func_80060FD8MainLoop();
            /* End the old register lifetime before setting the pad index. */
            asm volatile("" : "=r"(index));
            D_800A3684MainLoopSmall = 0;
            index = 0;
            if (D_800A3644MainLoop != 0) {
                *D_800A3685MainLoopSite6 = 0;
            } else {
                *D_800A3685MainLoopSite7 = two;
            }
            goto resetPadArray;
        case 3:
        case 6:
            RaceBuildQualifyingGridMainLoop(gSelectedTrackMainLoop);
        default:
        initializePads:
            index = 0;
        resetPadArray:
            /* Keep pointer setup in the common reset path. */
            asm volatile("" : "=r"(currentPadCursor));
            currentPadCursor = &newPad[0];
            break;
        }
        previousPadCursor = &oldPad[0];
    readInitialPads:
        InputGetPadButtonsMainLoop(index & 0xFF, previousPadCursor);
        *currentPadCursor = 0;
        currentPadCursor++;
        index += 1;
        previousPadCursor++;
        if (index < 2) {
            goto readInitialPads;
        }
        screenResult = 0;
        D_800A305CMainLoop = 0;
        unlockStep = 0;
        if (gScreenStateMainLoop == 0xC) {
            displayPhase = 0;
        } else {
            displayPhase = 0xFF;
            SetDispMaskMainLoop(1);
        }
        if (!(screenResult & 0xFF)) {
            mode13 = 13;
            do {
                CdStopIfPlaybackChangedMainLoop();
                nextIdleFrames = idleFrames + 1;
                idleFrames = nextIdleFrames;
                if ((gScreenStateMainLoop == 0) && (nextIdleFrames >= 0x709)) {
                    screenResult = 1;
                    gScreenStateMainLoop = 0xFD;
                }
                pulseTick = D_800A3724MainLoop - 1;
                D_800A3724MainLoop = pulseTick;
                if (!(pulseTick & 0xFF)) {
                    pulsePhase = D_800A305AMainLoop + 1;
                    D_800A305AMainLoop = pulsePhase;
                    if ((u32)(pulsePhase & 0xFF) >= 0x15U) {
                        D_800A305AMainLoop = 0;
                    }
                    {
                        register s32 pulseValue asm("v1");
                        s32 magnitude;
                        s32 intensity;
                        pulseValue = D_800A305AMainLoop;
                        /* Intensity is 64 + 8 * abs(pulseValue - 10), modulo 256. */
                        asm(".set\tnoreorder\n\tnop\n\taddiu\t%0,%2,-10\n\tbgez\t%0,1f\n\tsll\t%0,%0,3\n\tori\t%0,$zero,10\n\tsubu\t%0,%0,%2\n\tsll\t%0,%0,3\n1:\n\taddiu\t%0,%0,64\n\tandi\t%1,%0,255"
                            : "=&r"(magnitude), "=r"(intensity)
                            : "r"(pulseValue));
                        MenuSetShadeColorsMainLoop(intensity, intensity, 0x19U);
                    }
                    D_800A3724MainLoop = 3;
                }
                nextBufferIndex = D_800A305CMainLoop == 0;
                orderingTable =
                    (nextBufferIndex << 0xC) + gOrderingTablesMainLoopSite8;
                D_800A305CMainLoop = nextBufferIndex;
                gOrderingTableBankMainLoopSite9[0] = nextBufferIndex;
                gOrderingTableMainLoopSite10[0] = orderingTable;
                ClearOTagRMainLoop(orderingTable, 0x400);
                GraphicsSelectPrimitiveBufferMainLoop(
                    (s32)(u8)D_800A305CMainLoop);
                func_80057DFCMainLoop();
                func_80057DD4MainLoop();
                func_80053C00MainLoop((s32)(u8)D_800A305CMainLoop,
                                      activePlayer & 0xFF);
                DrawSyncMainLoop(0);
                VSyncMainLoop(0);
                GraphicsPutCurrentEnvironmentsMainLoop();
                if (displayPhase == one) {
                    SetDispMaskMainLoop(1);
                    displayPhase = 2;
                }
                D_800A3710MainLoop = -(D_800A305CMainLoop != 0) & 0x140;
                LoadImageMainLoop(&D_800A3710MainLoop, D_800A35F0MainLoop);
                DrawOTagMainLoop(
                    (u32 *)((u8 *)gOrderingTableMainLoopSite11[0] + 0xFFC));
                if (displayPhase == 0) {
                    displayPhase = 1;
                }
                PadResetAndInitializeBuffersMainLoop(0);
                if (newPad[0] != 0) {
                    idleFrames = 0;
                }
                if (gScreenStateMainLoop == 5) {
                    padBits0 = func_80041B7CMainLoop(0);
                    newPad[0] = padBits0;
                    if ((padBits0 & 0x20) && (D_800A3076MainLoop == 0)) {
                        unlockPhase = unlockStep & 0xFF;
                        if (padBits0 & 0xF000) {
                            if (unlockPhase == one) {
                                goto sequenceOne;
                            }
                            if (unlockPhase < 2) {
                                unlockDirectionBits = padBits0 & 0x1000;
                                if (unlockPhase == 0) {
                                    goto advanceUnlockStep;
                                }
                                goto sequenceDone;
                            }
                            if (unlockPhase == two) {
                                goto sequenceTwo;
                            }
                            if (unlockPhase == 3) {
                                goto sequenceLast;
                            }
                            goto sequenceDone;
                        sequenceOne:
                            unlockDirectionBits = padBits0 & 0x8000;
                            goto advanceUnlockStep;
                        sequenceTwo:
                            unlockDirectionBits = padBits0 & 0x4000;
                        advanceUnlockStep:
                            if (unlockDirectionBits != 0) {
                                unlockStep++;
                            }
                            goto sequenceDone;
                        sequenceLast:
                            if (padBits0 & 0x2000) {
                                D_800A3076MainLoop = one;
                                func_80063180MainLoop(1);
                                SoundPlaySlotMainLoop(0, 8);
                                goto resetUnlockStep;
                            }
                        sequenceDone:;
                        }
                    } else {
                    resetUnlockStep:
                        unlockStep = 0;
                    }
                } else if ((gScreenStateMainLoop == two) &&
                           (D_800A3059MainLoop == one)) {
                    index = 0;
                    sequenceCursor = &playerUnlockSteps[0];
                    selectionCursor = &gPlayerDriverMainLoop;
                readPlayerUnlockSequence:
                    if ((index != one) || (D_800A3644MainLoop != 0)) {
                        selection = *selectionCursor;
                        if ((selection == 5) || (selection == two)) {
                            playerPadBits = func_80041B7CMainLoop(index);
                            (&newPad[0])[index] = playerPadBits;
                            if (playerPadBits & 0x40) {
                                if (playerPadBits & 0x5000) {
                                    sequencePhase = *sequenceCursor;
                                    sequenceValue = sequencePhase & 0xFF;
                                    if (sequenceValue == 0) {
                                        goto playerSequenceFirst;
                                    }
                                    if (sequenceValue == one) {
                                        goto playerSequenceSecond;
                                    }
                                    sequenceCursor++;
                                    goto playerSequenceNext;
                                playerSequenceFirst:
                                    if (playerPadBits & 0x1000) {
                                        *sequenceCursor = sequencePhase + 1;
                                    }
                                    goto advancePlayerUnlockSequence;
                                playerSequenceSecond:
                                    if (!(playerPadBits & 0x4000)) {
                                        goto advancePlayerUnlockSequence;
                                    }
                                    currentSelection = *selectionCursor;
                                    if (currentSelection == two) {
                                        func_80063C34MainLoop(2, 0x19);
                                        func_80063AE0MainLoop(index, 2);
                                        D_800A3065MainLoop ^= 1;
                                        *sequenceCursor = 0;
                                        goto advancePlayerUnlockSequence;
                                    }
                                    if (currentSelection == 5) {
                                        func_80063C34MainLoop(5, 0x18);
                                        func_80063AE0MainLoop(index, 5);
                                        D_800A3064MainLoop ^= 1;
                                    }
                                    goto resetPlayerUnlockSequence;
                                } else {
                                    goto advancePlayerUnlockSequence;
                                }
                            } else {
                            resetPlayerUnlockSequence:
                                *sequenceCursor = 0;
                                goto advancePlayerUnlockSequence;
                            }
                        } else {
                        advancePlayerUnlockSequence:
                            sequenceCursor += 1;
                        }
                    playerSequenceNext:
                        index += 1;
                        selectionCursor += 1;
                        if (index < 2) {
                            goto readPlayerUnlockSequence;
                        }
                    }
                }
                if ((gScreenStateMainLoop == mode13) &&
                    (D_800A3684MainLoopSmall == two) &&
                    (ListHasClearFlagsMainLoop(
                         *gPadPictureMenuListsMainLoopSite13) != 0) &&
                    ((D_800A3644MainLoop == 0) ||
                     ((*D_800A3685MainLoopSite12 == two) &&
                      (ListHasClearFlagsMainLoop(*D_800A37DCMainLoopSite14) !=
                       0)))) {
                    screenResult = 1;
                } else {
                    player = 0;
                    asm("" : "=r"(player) : "0"(player));
                    index = player & 0xFF;
                    do {
                        if ((index == 0) || (D_800A3644MainLoop != 0)) {
                            (&newPad[0])[index] = func_80041B7CMainLoop(index);
                            if ((gScreenStateMainLoop == 7) &&
                                (activePlayer == one)) {
                                if (index != 0) {
                                    newPad[0] = newPad[1];
                                    oldPad[0] = oldPad[1];
                                    goto handlePlayerInput;
                                }
                                goto nextPlayer;
                            }
                            if (player & 0xFF) {
                                if (gScreenStateMainLoop != two) {
                                    if (gScreenStateMainLoop == mode13) {
                                        goto handlePlayerInput;
                                    }
                                    goto nextPlayer;
                                }
                                goto handlePlayerSelection;
                            }
                        handlePlayerInput:
                        handlePlayerSelection:
                            if (gScreenStateMainLoop == mode13) {
                                index = player & 0xFF;
                                if (newPad[index] &
                                    ((u16)~oldPad[index] & 0x800)) {
                                    transitionPhase =
                                        D_800A3684MainLoopSite15[index];
                                    if (transitionPhase == 0) {
                                        SoundPlaySlotMainLoop(0, 3);
                                        if (PadTypeNeedsCalibrationMainLoop(
                                                (s32)(u8)gPadTypeMainLoopSite16
                                                    [index]) &
                                            0xFF) {
                                            func_80062874MainLoop(index, 1);
                                            D_800A3684MainLoopSite17[index] =
                                                one;
                                            func_8006DE68MainLoop(
                                                (u32)index,
                                                (u32)(u8)gPadTypeMainLoopSite18
                                                    [index]);
                                            func_80062F04MainLoop(
                                                index,
                                                gPadTypeMainLoopSite20[index],
                                                gPadLayoutMainLoopSite19
                                                    [index]);
                                            animationStartX = -0x140;
                                            animationNodeSlot =
                                                D_800A3888MainLoopSite21;
                                            animationNodeSlot =
                                                (MenuObj *
                                                     *)((index * 4) +
                                                        (u32)animationNodeSlot);
                                            if (index != 0) {
                                                animationStartX = 0x140;
                                            }
                                            animationStepX = 4;
                                            if (index != 0) {
                                                animationStepX = -4;
                                            }
                                            ListSetFieldsAndEnableMainLoop(
                                                *animationNodeSlot,
                                                animationStartX, 0,
                                                animationStepX);
                                        } else {
                                            func_80062874MainLoop(index, 0);
                                            D_800A3684MainLoopSite22[index] =
                                                two;
                                            goto updateSelectionPanel;
                                        }
                                    } else if (transitionPhase == one) {
                                        SoundPlaySlotMainLoop(0, 3);
                                        PadCalibrateCenterMainLoop(
                                            (u32)index,
                                            (u32)(u8)
                                                gPadTypeMainLoopSite24[index],
                                            (u32)(u8)gPadLayoutMainLoopSite23
                                                [index]);
                                        func_80062874MainLoop(index, 0);
                                        animationEndX = 0x140;
                                        animationNodeSlot =
                                            D_800A3888MainLoopSite25;
                                        animationNodeSlot =
                                            (MenuObj **)((index * 4) +
                                                         (u32)
                                                             animationNodeSlot);
                                        if (index != 0) {
                                            animationEndX = -0x140;
                                        }
                                        animationReverseStepX = -4;
                                        if (index != 0) {
                                            animationReverseStepX = 4;
                                        }
                                        ListSetFieldsAndEnableMainLoop(
                                            *animationNodeSlot, 0,
                                            animationEndX,
                                            animationReverseStepX);
                                        D_800A3684MainLoopSite26[index] = two;
                                        D_800A36E4MainLoopSite27[index] = one;
                                    updateSelectionPanel:
                                        if ((D_800A3684MainLoopSmall != 0) &&
                                            (*D_800A3685MainLoopSite28 != 0)) {
                                            ListSetFieldsAndEnableMainLoop(
                                                *D_800A37F8MainLoopSite29, 0,
                                                0x140, 4);
                                        }
                                    }
                                } else if ((PadTypeNeedsCalibrationMainLoop(
                                                (s32)(u8)gPadTypeMainLoopSite31
                                                    [index]) &
                                            0xFF) &&
                                           (D_800A3684MainLoopSite30[index] ==
                                            one)) {
                                    PadCalibrateRangeMainLoop(
                                        (u32)index,
                                        (u32)(u8)gPadTypeMainLoopSite33[index],
                                        (u32)(u8)
                                            gPadLayoutMainLoopSite32[index]);
                                }
                            }
                            {
                                register s32 previousPadZero asm("a2");
                                register s32 currentPadZero asm("a1");
                                /* Read both pads before forming the pressed-edge mask. */
                                asm("lw\t%0,%3\n\tlw\t%1,%4\n\tnor\t%2,$zero,%0"
                                    : "=r"(previousPadZero),
                                      "=r"(currentPadZero),
                                      "=r"(previousPadInverse)
                                    : "m"(oldPad[0]), "m"(newPad[0]));
                                if (currentPadZero &
                                    ((u16)previousPadInverse & 0x40)) {
                                    s32 confirmPivot;
                                    s32 confirmMode;
                                    screenResult = func_80056B5CMainLoop(
                                        (s32)D_800A3059MainLoop,
                                        (s32)gScreenStateMainLoop,
                                        (s32)D_800A3950MainLoop);
                                    if (screenResult & 0xFF) {

                                        if ((u32)(gScreenStateMainLoop -
                                                  0x10) >= 2U) {
                                            SoundPlaySlotMainLoop(0, 3);
                                        }
                                    } else {
                                        confirmPivot = 0x24;
                                        confirmMode = gScreenStateMainLoop;
                                        if (confirmMode == confirmPivot) {
                                            goto confirmMode24;
                                        }
                                        if (confirmMode < 0x25) {
                                            if (confirmMode == 0x21) {
                                                goto confirmMode21;
                                            }
                                            if (confirmMode < 0x22) {
                                                if (confirmMode == one) {
                                                    goto confirmMode1;
                                                }
                                                if (confirmMode == 5) {
                                                    goto confirmMode5;
                                                }
                                                goto finishInput;
                                            }
                                            if (confirmMode == 0x22) {
                                                goto confirmMode22;
                                            }
                                            if (confirmMode == 0x23) {
                                                goto confirmMode23;
                                            }
                                            goto finishInput;
                                        }
                                        if (confirmMode == 0x27) {
                                            goto confirmMode25;
                                        }
                                        if (confirmMode < 0x28) {
                                            if (confirmMode == 0x25) {
                                                goto confirmMode25;
                                            }
                                            if (confirmMode == 0x26) {
                                                goto confirmMode26;
                                            }
                                            goto finishInput;
                                        }
                                        if (confirmMode == 0x28) {
                                            goto confirmMode28;
                                        }
                                        if (confirmMode != 0xFC) {
                                            goto finishInput;
                                        }
                                    confirmModeFC:
                                        {
                                            s32 exitPhase;
                                            s32 exitChannel;
                                            s32 exitTone;
                                            exitPhase = D_800A3928MainLoop;
                                            if (exitPhase == 0) {
                                                goto confirmExitStatus;
                                            }
                                            exitChannel = 0;
                                            if (exitPhase == one) {
                                                goto confirmExitSound;
                                            }
                                            goto finishInput;
                                        confirmExitStatus:
                                            exitPhase =
                                                gCardMenuMessageMainLoop[0];
                                            exitChannel = 0;
                                            if (exitPhase != mode13) {
                                                goto confirmExitSound;
                                            }
                                            exitTone = 4;
                                            goto confirmExit;
                                        confirmExitSound:
                                            exitTone = 3;
                                        confirmExit:
                                            screenResult = 1;
                                            SoundPlaySlotMainLoop(exitChannel,
                                                                  exitTone);
                                            goto finishInput;
                                        }
                                    confirmMode1:
                                        SoundPlaySlotMainLoop(0, 3);
                                        if ((D_800A3059MainLoop == two &&
                                             D_800A3950MainLoop != 0) ||
                                            D_800A3059MainLoop == one) {
                                            CardEnableAndTestEventsMainLoop();
                                            if ((CardProbeSlotsMainLoop() &
                                                 0xFF) == two) {
                                                gScreenStateMainLoop = 0x28;
                                                CardMenuCenterSelectedTextMainLoop(
                                                    5);
                                                menuCode = 1;
                                            } else {
                                                menuCode =
                                                    CardLoadNameListMainLoop(
                                                        0xFF);
                                            }
                                            func_80057008MainLoop(menuCode &
                                                                  0xFF);
                                            CardTestAndDisableEventsMainLoop();
                                            func_80057160MainLoop(1);
                                        } else if (D_800A3059MainLoop == 6) {
                                            if (D_800B9B84MainLoop[0] == 0) {
                                                screenResult = 1;
                                                goto finishInput;
                                            }
                                            CardMenuCenterSelectedTextMainLoop(
                                                2);
                                            gCardMenuMessageMainLoop[0] = 0x15;
                                            CardMenuShowMessageMainLoop(0);
                                            animateX = -0x78;
                                            animateY = 0;
                                            animateStep = 2;
                                            dialogScreen = 0x25;
                                            goto showConfirmDialog;
                                        } else if (D_800A3059MainLoop == 0 &&
                                                   D_800A3950MainLoop != 0) {
                                            CardMenuCenterSelectedTextMainLoop(
                                                4);
                                            gCardMenuMessageMainLoop[0] = 0x18;
                                            CardMenuShowMessageMainLoop(0);
                                            animateX = -0x78;
                                            animateY = 0;
                                            animateStep = 2;
                                            dialogScreen = 0x27;
                                        showConfirmDialog:
                                            gScreenStateMainLoop = dialogScreen;
                                            CardMenuSetColorNodeLayoutMainLoop(
                                                animateX, animateY,
                                                animateStep);
                                            MenuNegateLinkedObjectValuesMainLoop(
                                                0);
                                        }
                                        goto finishInput;
                                    confirmMode5:
                                        if ((u32)(D_800A3059MainLoop - 2) <
                                            2U) {
                                            SoundPlaySlotMainLoop(0, 3);
                                            if (D_800A3059MainLoop == 3) {
                                                SoundRunSlotEnvelopeMainLoop(0,
                                                                             1);
                                                func_8003CCE0MainLoop(0);
                                                gCdAudioEnabledMainLoop[0] = 0;
                                            }
                                            MenuCenterTextMainLoop(
                                                D_800A3059MainLoop - 2);
                                            MenuSetVolumeMainLoop(
                                                (s16)D_800A3690MainLoop
                                                    [D_800A3059MainLoop],
                                                D_800A3059MainLoop - 2);
                                            MenuSetLinkedObjectLayoutMainLoop(
                                                -0x78, 0, 2);
                                            gScreenStateMainLoop = 0x21;
                                            MenuUpdateItemRowMainLoop(0x21);
                                        }
                                        goto finishInput;
                                    confirmMode21:
                                        SoundPlaySlotMainLoop(0, 3);
                                        MenuSetLinkedObjectLayoutMainLoop(
                                            0, -0x78, -2);
                                        gScreenStateMainLoop = 5;
                                        MenuUpdateItemRowMainLoop(5);
                                        if (D_800A3059MainLoop == 3) {
                                            SoundRunSlotEnvelopeMainLoop(2, 1);
                                            CdEnablePlaybackAndSetVolumeMainLoop();
                                        }
                                        goto finishInput;
                                    confirmMode28:
                                        SoundPlaySlotMainLoop(0, 3);
                                        CardEnableAndTestEventsMainLoop();
                                        cardMenuCode = CardLoadNameListMainLoop(
                                            D_800A358CMainLoop[0]);
                                        gScreenStateMainLoop = one;
                                        func_80057008MainLoop(cardMenuCode &
                                                              0xFF);
                                        CardTestAndDisableEventsMainLoop();
                                        func_80057160MainLoop(0);
                                        goto finishInput;
                                    confirmMode22:
                                        SoundPlaySlotMainLoop(0, 3);
                                        gScreenStateMainLoop = 0x23;
                                        CardMenuAppendTrackNameMainLoop();
                                        func_8006C9F8MainLoop();
                                        gCardMenuMessageMainLoop[0] = 0;
                                        MenuUpdateItemRowMainLoop(
                                            gScreenStateMainLoop);
                                        goto finishInput;
                                    confirmMode23:
                                        {
                                            s32 scanPhase;
                                            scanPhase = D_800A3928MainLoop;
                                            returnChannel = 0;
                                            if (scanPhase == 0) {
                                                goto confirmScan;
                                            }
                                            actionSound = 3;
                                            if (scanPhase == one) {
                                                goto returnMainMenu;
                                            }
                                            goto finishInput;
                                        confirmScan:
                                            {
                                                SoundPlaySlotMainLoop(0, 3);
                                                if (func_8006D178MainLoop() ==
                                                    0) {
                                                    SoundStopSlotMainLoop(0);
                                                } else {
                                                    MenuHideCurrentObjectMainLoop();
                                                    if (gCardMenuMessageMainLoop
                                                            [0] == 0) {
                                                        if (CardMenuCheckTrackNameCapacityMainLoop() ==
                                                            one) {
                                                            goto refreshCardMenu;
                                                        }
                                                        if (gCardMenuMessageMainLoop
                                                                [0] == 0) {
                                                            goto updateCardStatus;
                                                        }
                                                    }
                                                    if (gCardMenuMessageMainLoop
                                                            [0] == 0x10) {
                                                    updateCardStatus:
                                                        CardEnableAndTestEventsMainLoop();
                                                        if (!(CardResolveSlotMainLoop() &
                                                              0xFF)) {
                                                            CardMenuShowMessageMainLoop(
                                                                0);
                                                            if (gCardMenuMessageMainLoop
                                                                    [0] !=
                                                                mode13) {
                                                                D_800A3928MainLoop =
                                                                    one;
                                                            }
                                                        }
                                                        CardTestAndDisableEventsMainLoop();
                                                        if (gCardMenuMessageMainLoop
                                                                [0] == mode13) {
                                                            goto finishInput;
                                                        }
                                                    }
                                                    if (gCardMenuMessageMainLoop
                                                            [0] == mode13) {
                                                        SoundStopSlotMainLoop(
                                                            0);
                                                        goto playBackSound;
                                                    }
                                                    goto checkCardMenuReady;
                                                }
                                            }
                                            goto finishInput;
                                        }
                                    confirmMode24:
                                        SoundPlaySlotMainLoop(0, 3);
                                        menuPhase = D_800A3928MainLoop;
                                        if (menuPhase == one) {
                                            goto confirmStageOne;
                                        }
                                        if (menuPhase < 2) {
                                            if (menuPhase == 0) {
                                                goto confirmStageZero;
                                            }
                                            goto finishInput;
                                        }
                                        if (menuPhase == two) {
                                            goto confirmStageTwo;
                                        }
                                        goto finishInput;
                                    confirmStageZero:
                                        gCardMenuMessageMainLoop[0] = 0x17;
                                        cardOperation = 0;
                                        goto startCardOperation;
                                    confirmStageOne:
                                        if (func_8006D258MainLoop() == one) {
                                            gCardMenuMessageMainLoop[0] = 0x12;
                                        }
                                        D_800A3928MainLoop = two;
                                    refreshCardMenu:
                                        CardMenuShowMessageMainLoop(0);
                                        goto finishInput;
                                    confirmStageTwo:
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        if (D_800A3968MainLoop[0] != 0) {
                                            D_800A3950MainLoop = 0x24;
                                        }
                                        goto finishMainMenuReturn;
                                    confirmMode25:
                                        SoundPlaySlotMainLoop(0, 3);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        screenResult = 1;
                                        gScreenStateMainLoop = screenResult;
                                        goto finishInput;
                                    confirmMode26:
                                        SoundPlaySlotMainLoop(0, 3);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        gScreenStateMainLoop = 7;
                                        RaceBuildQualifyingGridMainLoop(
                                            gSelectedTrackMainLoop);
                                        screenResult = 0xFF;
                                        goto finishInput;
                                    }
                                    goto finishInput;
                                }
                                if (currentPadZero &
                                    ((u16)previousPadInverse & 0x10)) {
                                    if (gScreenStateMainLoop == 7) {

                                        if (D_800A3950MainLoop == 0xFB) {
                                            SoundPlaySlotMainLoop(0, 4);
                                            gScreenStateMainLoop = 0x26;
                                            gCardMenuMessageMainLoopSite51[0] =
                                                0x16;
                                            CardMenuShowMessageMainLoop(0);
                                            CardMenuCenterSelectedTextMainLoop(
                                                3);
                                            CardMenuSetColorNodeLayoutMainLoop(
                                                -0x78, 0, 2);
                                        }
                                    } else {
                                        screenResult = func_80056B0CMainLoop(
                                            (s32)gScreenStateMainLoop,
                                            (s32)D_800A3950MainLoop);
                                        if (screenResult & 0xFF) {
                                            SoundPlaySlotMainLoop(0, 4);

                                        } else {
                                            goto storePadStates;
                                        }
                                    }
                                    goto finishInput;
                                }
                                if (currentPadZero &
                                    ((u16)previousPadInverse & 0x80)) {
                                    s32 cancelPivot;
                                    s32 cancelMode;
                                    cancelPivot = 0x25;
                                    cancelMode = gScreenStateMainLoop;
                                    switch (cancelMode) {
                                    case 0xFC:
                                        if (gCardMenuMessageMainLoop[0] !=
                                                two &&
                                            D_800A3928MainLoop == 0) {
                                            s32 cardStatus;
                                            SoundPlaySlotMainLoop(0, 3);
                                            CardEnableAndTestEventsMainLoop();
                                            CardResolveSlotMainLoop();
                                            cardStatus =
                                                func_80069EB8MainLoop() & 0xFF;
                                            if (cardStatus == 0) {
                                                cardStatus = 4;
                                            } else {
                                                cardStatus = 0x13;
                                            }
                                            gCardMenuMessageMainLoop[0] =
                                                cardStatus;
                                            CardTestAndDisableEventsMainLoop();
                                            cardOperation = 1;
                                        startCardOperation:
                                            CardMenuShowMessageMainLoop(
                                                cardOperation);
                                            D_800A3928MainLoop = one;
                                        }
                                        break;
                                    case 0x23:
                                        if (D_800A3928MainLoop == 0) {
                                            if (gCardMenuMessageMainLoop[0] ==
                                                    mode13 ||
                                                (u32)(gCardMenuMessageMainLoop
                                                          [0] -
                                                      0x19) < 2U) {
                                                SoundPlaySlotMainLoop(0, 3);
                                                CardEnableAndTestEventsMainLoop();
                                                if (!(func_80069EB8MainLoop() &
                                                      0xFF)) {
                                                    gCardMenuMessageMainLoop
                                                        [0] = 4;
                                                    CardMenuShowMessageMainLoop(
                                                        0);
                                                    D_800A3928MainLoop = one;
                                                    MenuUpdateItemRowMainLoop(
                                                        0xA);
                                                } else {
                                                    CardTestAndDisableEventsMainLoop();
                                                checkCardMenuReady:
                                                    if (gCardMenuMessageMainLoop
                                                            [0] == 0) {
                                                        CardMenuWriteSaveSlotMainLoop();
                                                        CardMenuShowMessageMainLoop(
                                                            0);
                                                        D_800A3928MainLoop =
                                                            one;
                                                        MenuUpdateItemRowMainLoop(
                                                            0xA);
                                                    }
                                                }
                                            } else {
                                                goto playBackSound;
                                            }
                                        }
                                        break;
                                    case 0x24:
                                    playBackSound:
                                        returnChannel = 0;
                                        actionSound = 4;
                                    returnMainMenu:
                                        SoundPlaySlotMainLoop(returnChannel,
                                                              actionSound);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                    finishMainMenuReturn:
                                        gScreenStateMainLoop = one;
                                        MenuUpdateItemRowMainLoop(1);
                                        break;
                                    case 0x22:
                                    case 0x28:
                                        goto playBackSound;
                                    case 0x25:
                                    case 0x27:
                                        SoundPlaySlotMainLoop(0, 4);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        gScreenStateMainLoop = one;
                                        break;
                                    case 0x26:
                                        SoundPlaySlotMainLoop(0, 4);
                                        CardMenuSetColorNodeLayoutMainLoop(
                                            0, -0x78, -2);
                                        gScreenStateMainLoop = 7;
                                        break;
                                    }
                                    goto finishInput;
                                }
                                /* End the old register lifetime before setting the pad index. */
                                index = player & 0xFF;
                                padBits = newPad[index];
                                if (padBits &
                                    ((u16)previousPadInverse & 0x20)) {

                                    if (gScreenStateMainLoop == 0x23) {
                                        func_8006CE64MainLoop();
                                    }
                                    goto finishInput;
                                }
                                if (padBits & 0x1000) {
                                    register s32 padEdgeUp asm("v0");
                                    s32 blockedModeUp;
                                    s32 cardModeUp;
                                    s32 rawModeUp;
                                    s32 modeUp;
                                    blockedModeUp = 0x21;
                                    /* Retain the raw mode byte and its comparison value. */
                                    rawModeUp = (u8)gScreenStateMainLoop;
                                    modeUp = rawModeUp & 255;
                                    if ((modeUp != blockedModeUp) &&
                                        (modeUp != 0xFC) &&
                                        ((u32)(rawModeUp - 0x25) >= 2U) &&
                                        (modeUp != mode13) &&
                                        (modeUp != 0x27) && (modeUp != 0xE)) {
                                        if (((u32)(rawModeUp - 9) < 2U) ||
                                            (modeUp == 0xC) ||
                                            ((u32)(rawModeUp - 0x10) < 2U)) {
                                            func_80068AC4MainLoop(newPad[0],
                                                                  oldPad[0], 1);

                                            goto finishInput;
                                        }
                                        cardModeUp = 0x23;
                                        if (modeUp == cardModeUp) {
                                            if (D_800A3928MainLoop == one) {
                                                goto nextPlayer;
                                            }
                                            if (D_800A3770MainLoopSite57[0] !=
                                                0) {
                                                goto nextPlayer;
                                            }
                                            menuDirection = 1;
                                            goto moveCardCursor;
                                        }
                                        padEdgeUp = previousPadInverse & 0x1000;
                                        if (currentPadZero & padEdgeUp) {
                                            if ((modeUp == 0x22) ||
                                                (modeUp == 0x24) ||
                                                (modeUp == 0x28)) {
                                                if (D_800A3770MainLoopSite58
                                                        [0] == 0) {
                                                    if (func_8006C700MainLoop(
                                                            0,
                                                            gScreenStateMainLoop ==
                                                                0x22) &
                                                        0xFF) {
                                                        SoundPlaySlotMainLoop(
                                                            0, 0);

                                                    } else {
                                                        goto storePadStates;
                                                    }
                                                    goto finishInput;
                                                }
                                            } else {
                                                SoundPlaySlotMainLoop(0, 0);
                                                wrappedItemUp =
                                                    D_800A3059MainLoop;
                                                if (wrappedItemUp == 0) {
                                                    wrappedItemUp =
                                                        D_800A38E8MainLoopSite59
                                                            [0] -
                                                        1;
                                                } else {
                                                    wrappedItemUp -= 1;
                                                }
                                                do {
                                                    D_800A3059MainLoop =
                                                        wrappedItemUp;
                                                } while (0);

                                                if (gScreenStateMainLoop ==
                                                    two) {

                                                    if (D_800A3988MainLoopSmall ==
                                                        0) {
                                                        if ((u32)(D_800A3059MainLoopPostUp -
                                                                  4) < 2U) {
                                                            D_800A3059MainLoopPostUp =
                                                                3;

                                                        } else {
                                                            goto storePadStates;
                                                        }
                                                    }
                                                    goto finishInput;
                                                }
                                                if ((gScreenStateMainLoop ==
                                                     one) &&
                                                    (D_800A3950MainLoop == 0)) {

                                                    if ((u32)(D_800A3059MainLoopPostUp -
                                                              2) < 4U) {
                                                        D_800A3059MainLoopPostUp =
                                                            one;

                                                    } else {
                                                        goto finishInput;
                                                    }
                                                } else {
                                                    if (gScreenStateMainLoop ==
                                                        3) {

                                                        if (D_800A3644MainLoop !=
                                                            0) {
                                                            itemUp =
                                                                D_800A3059MainLoopPostUp &
                                                                0xFF;
                                                            if (itemUp == 3) {
                                                                D_800A3059MainLoopPostUp -=
                                                                    2;

                                                            } else if (itemUp ==
                                                                       two) {
                                                                D_800A3059MainLoopPostUp -=
                                                                    1;

                                                            } else {
                                                                goto storePadStates;
                                                            }
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if (gScreenStateMainLoop ==
                                                        4) {
                                                        itemCursorUp =
                                                            D_800A3059MainLoopPostUp;

                                                        if (D_800A3988MainLoopSite60
                                                                [itemCursorUp &
                                                                 0xFF] &
                                                            0x80) {
                                                            do {
                                                                nextItemUp =
                                                                    itemCursorUp -
                                                                    1;
                                                                D_800A3059MainLoopPostUp =
                                                                    nextItemUp;
                                                                itemCursorUp =
                                                                    nextItemUp;
                                                            } while (
                                                                D_800A3988MainLoopSite61
                                                                    [nextItemUp &
                                                                     0xFF] &
                                                                0x80);
                                                        }
                                                        goto finishInput;
                                                    }

                                                    if (gScreenStateMainLoop ==
                                                        5) {

                                                        if (D_800A3059MainLoopPostUp ==
                                                            5) {

                                                            if (D_800A3076MainLoop ==
                                                                0) {
                                                                D_800A3059MainLoopPostUp -=
                                                                    1;
                                                            }
                                                            goto finishInput;
                                                        }
                                                    } else {
                                                        goto finishInput;
                                                    }
                                                }
                                                goto updatePreviousPad;
                                            }
                                        } else {
                                            goto storePadStates;
                                        }
                                        goto nextPlayer;
                                    }
                                    goto nextPlayer;
                                }
                                if (padBits & 0x4000) {
                                    register s32 padEdgeDown asm("v0");
                                    s32 blockedModeDown;
                                    s32 cardModeDown;
                                    s32 rawModeDown;
                                    register s32 modeDown;
                                    blockedModeDown = 0x21;
                                    /* Retain the raw mode byte and its comparison value. */
                                    rawModeDown = (u8)gScreenStateMainLoop;
                                    modeDown = rawModeDown & 255;
                                    if ((modeDown != blockedModeDown) &&
                                        (modeDown != 0xFC) &&
                                        ((u32)(rawModeDown - 0x25) >= 2U) &&
                                        (modeDown != mode13) &&
                                        (modeDown != 0x27) &&
                                        (modeDown != 0xE)) {
                                        if (((u32)(rawModeDown - 9) < 2U) ||
                                            (modeDown == 0xC) ||
                                            ((u32)(rawModeDown - 0x10) < 2U)) {
                                            func_80068AC4MainLoop(newPad[0],
                                                                  oldPad[0], 0);

                                            goto finishInput;
                                        }
                                        cardModeDown = 0x23;
                                        if (modeDown == cardModeDown) {
                                            if (D_800A3928MainLoop == one) {
                                                goto nextPlayer;
                                            }
                                            if (D_800A3770MainLoopSite62[0] !=
                                                0) {
                                                goto nextPlayer;
                                            }
                                            menuDirection = 0;
                                        moveCardCursor:
                                            player += 1;
                                            func_8006CB80MainLoop(
                                                menuDirection);
                                            oldPad[0] = newPad[0];
                                        } else {
                                            padEdgeDown =
                                                previousPadInverse & 0x4000;
                                            if (currentPadZero & padEdgeDown) {
                                                if ((modeDown == 0x22) ||
                                                    (modeDown == 0x24) ||
                                                    (modeDown == 0x28)) {
                                                    if (D_800A3770MainLoopSite63
                                                            [0] == 0) {
                                                        if (func_8006C700MainLoop(
                                                                1,
                                                                gScreenStateMainLoop ==
                                                                    0x22) &
                                                            0xFF) {
                                                            SoundPlaySlotMainLoop(
                                                                0, 1);

                                                        } else {
                                                            goto storePadStates;
                                                        }
                                                        goto finishInput;
                                                    }
                                                } else {
                                                    SoundPlaySlotMainLoop(0, 1);
                                                    if ((D_800A3059MainLoop &
                                                         0xFF) ==
                                                        (D_800A38E8MainLoopSite64
                                                             [0] -
                                                         1)) {
                                                        D_800A3059MainLoop = 0;
                                                    } else {
                                                        D_800A3059MainLoop += 1;
                                                    }
                                                    if (gScreenStateMainLoop ==
                                                        two) {

                                                        if (D_800A3988MainLoopSmall ==
                                                            0) {

                                                            if (D_800A3059MainLoopPostDown ==
                                                                4) {
                                                                /* Keep the two skip paths separate until the store. */
                                                                asm volatile(
                                                                    ""
                                                                    :
                                                                    :
                                                                    : "memory");
                                                                goto skipLockedItems;
                                                            }
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if ((gScreenStateMainLoop ==
                                                         one) &&
                                                        (D_800A3950MainLoop ==
                                                         0)) {
                                                        if ((u32)(D_800A3059MainLoopPostDown -
                                                                  2) < 4U) {
                                                        skipLockedItems:
                                                            D_800A3059MainLoopPostDown =
                                                                6;

                                                        } else {
                                                            goto storePadStates;
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if (gScreenStateMainLoop ==
                                                        3) {

                                                        if (D_800A3644MainLoop !=
                                                            0) {
                                                            itemDown =
                                                                D_800A3059MainLoopPostDown &
                                                                0xFF;
                                                            if (itemDown ==
                                                                two) {
                                                                D_800A3059MainLoopPostDown +=
                                                                    2;

                                                            } else if (
                                                                itemDown ==
                                                                gScreenStateMainLoop) {
                                                                D_800A3059MainLoopPostDown +=
                                                                    1;

                                                            } else {
                                                                goto storePadStates;
                                                            }
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if (gScreenStateMainLoop ==
                                                        4) {
                                                        itemCursorDown =
                                                            D_800A3059MainLoopPostDown;

                                                        if (D_800A3988MainLoopSite65
                                                                [itemCursorDown &
                                                                 0xFF] &
                                                            0x80) {
                                                            do {
                                                                nextItemDown =
                                                                    itemCursorDown +
                                                                    1;
                                                                D_800A3059MainLoopPostDown =
                                                                    nextItemDown;
                                                                itemCursorDown =
                                                                    nextItemDown;
                                                            } while (
                                                                D_800A3988MainLoopSite66
                                                                    [nextItemDown &
                                                                     0xFF] &
                                                                0x80);
                                                        }
                                                        goto finishInput;
                                                    }

                                                    if (gScreenStateMainLoop !=
                                                        5) {
                                                        goto finishInput;
                                                    }
                                                    if (D_800A3059MainLoopPostDown !=
                                                        gScreenStateMainLoop) {
                                                        goto finishInput;
                                                    }
                                                    if (D_800A3076MainLoop !=
                                                        0) {
                                                        goto finishInput;
                                                    }
                                                    D_800A3059MainLoopPostDown =
                                                        0;
                                                    goto updatePreviousPad;
                                                }
                                            } else {
                                                goto storePadStates;
                                            }
                                            goto nextPlayer;
                                        }
                                    } else {
                                        goto nextPlayer;
                                    }
                                } else {
                                    if (padBits & 0x8000) {
                                        if (gScreenStateMainLoop == mode13 &&
                                            (padBits &
                                             ((u16)~oldPad[index] & 0x8000))) {
                                            if (!(PadTypeNeedsCalibrationMainLoop(
                                                      (u8)gPadTypeMainLoopSite68
                                                          [index]) &
                                                  0xFF) ||
                                                D_800A3684MainLoopSite67
                                                        [index] != one) {
                                                if (D_800A3684MainLoopSite69
                                                        [index] == 0) {
                                                    SoundPlaySlotMainLoop(0, 2);
                                                    {
                                                        s32 variantCount;
                                                        s32 variantValue;
                                                        s32 countMinusOne;
                                                        s32 variantRemainder;
                                                        variantCount =
                                                            D_800A3080MainLoopSite70
                                                                [gPadTypeMainLoopSite71
                                                                     [index]];
                                                        variantValue =
                                                            gPadLayoutMainLoopSite72
                                                                [index];
                                                        countMinusOne =
                                                            variantCount - 1;
                                                        variantValue +=
                                                            countMinusOne;
                                                        variantRemainder =
                                                            variantValue %
                                                            variantCount;
                                                        gPadLayoutMainLoopSite72
                                                            [index] =
                                                                variantRemainder;
                                                    }
                                                }
                                            }
                                        } else if (gScreenStateMainLoop ==
                                                       two &&
                                                   D_800A3059MainLoop == one) {
                                            MenuHandleOptionsInputMainLoop(
                                                2, 1, 1, newPad[player & 0xFF],
                                                oldPad[player & 0xFF],
                                                player & 0xFF);
                                        } else {
                                            MenuHandleOptionsInputMainLoop(
                                                gScreenStateMainLoop,
                                                D_800A3059MainLoop, 1,
                                                newPad[0], oldPad[0],
                                                activePlayer);
                                        }
                                    } else if (padBits & 0x2000) {
                                        if (gScreenStateMainLoop == mode13 &&
                                            (padBits &
                                             ((u16)~oldPad[index] & 0x2000))) {
                                            if (!(PadTypeNeedsCalibrationMainLoop(
                                                      (u8)gPadTypeMainLoopSite74
                                                          [index]) &
                                                  0xFF) ||
                                                D_800A3684MainLoopSite73
                                                        [index] != one) {
                                                if (D_800A3684MainLoopSite75
                                                        [index] == 0) {
                                                    SoundPlaySlotMainLoop(0, 2);
                                                    gPadLayoutMainLoopSite76[index] =
                                                        (gPadLayoutMainLoopSite76
                                                             [index] +
                                                         1) %
                                                        D_800A3080MainLoopSite77
                                                            [gPadTypeMainLoopSite78
                                                                 [index]];
                                                }
                                            }
                                        } else if (gScreenStateMainLoop ==
                                                       two &&
                                                   D_800A3059MainLoop == one) {
                                            MenuHandleOptionsInputMainLoop(
                                                2, 1, 0, newPad[player & 0xFF],
                                                oldPad[player & 0xFF],
                                                player & 0xFF);
                                        } else {
                                            MenuHandleOptionsInputMainLoop(
                                                gScreenStateMainLoop,
                                                D_800A3059MainLoop, 0,
                                                newPad[0], oldPad[0],
                                                activePlayer);
                                        }
                                    }
                                storePadStates:
                                finishInput:

                                updatePreviousPad:
                                    oldPad[player & 0xFF] =
                                        newPad[player & 0xFF];
                                    goto nextPlayer;
                                }
                            }
                        } else {
                        nextPlayer:
                            player += 1;
                        }
                        index = (u8)player;
                    } while ((u32)(player & 0xFF) < 2U);
                }
            } while (!(screenResult & 0xFF));
        }
        DrawSyncMainLoop(0);
        if (gScreenStateMainLoop == 7) {
            func_80057DE8MainLoop();
        }
        screenResultByte = screenResult & 0xFF;
        if (gScreenStateMainLoop != 0xFD) {
            nextScreen = MenuUpdateScreenStateMainLoop(
                gScreenStateMainLoop, &D_800A3950MainLoop, screenResultByte);
            gScreenStateMainLoop = nextScreen;
            if ((nextScreen & 0xFF) == 7) {
                activePlayer = 0;
            }
            if ((D_800A3950MainLoop == 7) && !(activePlayer & 0xFF) &&
                (D_800A3644MainLoop != 0) && (*D_800A3A25MainLoopSite79 != 0) &&
                (screenResultByte != 0xFF)) {
                activePlayer = 1;
                D_800A3950MainLoop = nextScreen;
                gScreenStateMainLoop = 7;
                D_800A3059MainLoop = 0;
            }
        }
        if ((gScreenStateMainLoop == 0xFF) || (gScreenStateMainLoop == 0xFD) ||
            (gScreenStateMainLoop == 0xF8)) {
            exitLoop = 1;
        }
    } while (exitLoop == 0);
    VSyncMainLoop(0);
    VSyncMainLoop(0);
    do {

    } while (func_8003F4FCMainLoop(0) & 0xFF);
}
#endif

void func_80055AA4(u8 arg0, s32 arg1) {
    extern u8 D_800A3644NM asm("D_800A3644.NON_MATCHING");
    extern u8 gPlayerDriver[];
    extern char *gDriverNamesR[] asm("gDriverNames.NON_MATCHING");
    u8 other;
    u8 val;

    other = arg0 ^ 1;
    if ((u8)arg1 != 0) {
        val = (D_800A3980[arg0] + 23) % 24;
        D_800A3980[arg0] = val;
        if (D_800A3644NM != 0 && val == D_800A3980[other]) {
            val = (val + 23) % 24;
            D_800A3980[arg0] = val;
        }
    } else {
        val = (D_800A3980[arg0] + 1) % 24;
        D_800A3980[arg0] = val;
        if (D_800A3644NM != 0 && val == D_800A3980[other]) {
            val = (val + 1) % 24;
            D_800A3980[arg0] = val;
        }
    }
    gPlayerDriver[arg0] = D_8009AD40[D_800A3980[arg0]];
    MenuSetDriverNameLabel(arg0, gPlayerDriver[arg0]);
    func_80063AE0(arg0, gPlayerDriver[arg0]);
    strcpy(&D_800BB9B4[arg0 * 24], gDriverNamesR[gPlayerDriver[arg0]]);
}

/* The repeated label aliases keep gcc from caching addresses that retail
 * reloads, and func_80055AA4B stops cross-jumping from merging the two
 * func_80055AA4 calls. MenuSetLinkedObjectLayoutByIndexKR is unprototyped on purpose: retail
 * passes its first argument without narrowing it to u8.
 */
void MenuHandleOptionsInput(u8 arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4,
                            u8 arg5) {
    extern u8 D_800A3644NM asm("D_800A3644.NON_MATCHING");
    extern u8 D_800A3988NM asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3073NM asm("D_800A3073.NON_MATCHING");
    extern s8 D_800A3078NM asm("D_800A3078.NON_MATCHING");
    extern u8 gSelectedTrackSmall;
    extern u8 gStereoEnabledNM[] asm("gStereoEnabled.NON_MATCHING");
    extern s8 D_800A3A14NM[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R2[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R3[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R4[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R5[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R6[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R7[] asm("D_800A3A14.NON_MATCHING");
    extern MenuObj *D_800A38FCR2[] asm("D_800A38FC.NON_MATCHING");
    extern MenuObj *D_800A38FCR3[] asm("D_800A38FC.NON_MATCHING");
    extern MenuObj *D_800A38FCR4[] asm("D_800A38FC.NON_MATCHING");
    extern MenuObj *D_800A39A0R2[] asm("D_800A39A0.NON_MATCHING");
    extern MenuObj *D_800A39A0R3[] asm("D_800A39A0.NON_MATCHING");
    extern s8 D_800A39FCR2[] asm("D_800A39FC.NON_MATCHING");
    extern s8 D_800A3594R2[] asm("D_800A3594.NON_MATCHING");
    extern s8 D_800A3944R2[] asm("D_800A3944.NON_MATCHING");
    extern s8 D_800A3944R3[] asm("D_800A3944.NON_MATCHING");
    extern s8 D_800A3944R4[] asm("D_800A3944.NON_MATCHING");
    extern s8 D_800A39DCR2[] asm("D_800A39DC.NON_MATCHING");
    extern s8 D_800A39DCR3[] asm("D_800A39DC.NON_MATCHING");
    extern u8 D_800A3894R2[] asm("D_800A3894.NON_MATCHING");
    extern u8 D_800A3A58NM[] asm("D_800A3A58.NON_MATCHING");
    extern u16 D_800A3690NM[] asm("D_800A3690.NON_MATCHING");
    extern s32 D_800A37D0NM asm("D_800A37D0.NON_MATCHING");
    extern u8 D_800A3988[];
    extern u8 D_800A3988B[] asm("D_800A3988");
    extern u8 D_800A3988C[] asm("D_800A3988");
    extern u8 D_800A3988D[] asm("D_800A3988");
    extern u8 D_800A3988E[] asm("D_800A3988");
    extern u8 D_800A3988F[] asm("D_800A3988");
    extern u8 D_800A3988G[] asm("D_800A3988");
    extern u8 D_800A3988H[] asm("D_800A3988");
    extern u8 D_800A3988I[] asm("D_800A3988");
    extern u8 D_800A3988J[] asm("D_800A3988");
    extern u8 D_800A3988K[] asm("D_800A3988");
    extern u8 D_800A3988L[] asm("D_800A3988");
    extern u8 D_800A3988M[] asm("D_800A3988");
    extern u8 D_800A3988N[] asm("D_800A3988");
    extern u8 D_800A3988O[] asm("D_800A3988");
    extern u8 D_800A3988P[] asm("D_800A3988");
    extern u8 D_800A3988Q[] asm("D_800A3988");
    extern u8 D_800A3988R[] asm("D_800A3988");
    extern u8 D_800A3988S[] asm("D_800A3988");
    extern u8 D_800A3068Pair[][2] asm("D_800A3068");
    extern u8 D_800A3074;
    extern u8 D_800A3076;
    extern u8 D_800A3077;
    extern u8 D_800A306C;
    extern u8 gCdAnnouncerNM asm("gCdAnnouncer.NON_MATCHING");
    extern u8 D_800A306E;
    extern u8 D_800A306F;
    extern u8 D_800A3070;
    extern u8 D_800A3071;
    extern u8 D_800A3072;
    extern u8 D_800A3928;
    extern s32 D_800A37F0;
    extern s32 D_800A3830;
    extern u8 D_8009957C[];
    extern s32 D_800AE178[];
    extern u8 D_80099568[][6];
    extern u8 D_80099574[];
    extern s32 D_800A3744[] asm("D_800A3744.NON_MATCHING");
    extern s32 D_800A360C[] asm("D_800A360C.NON_MATCHING");
    extern s32 D_800A37D4[] asm("D_800A37D4.NON_MATCHING");
    extern s32 D_800A3870[] asm("D_800A3870.NON_MATCHING");
    extern s8 D_800A3594[];
    extern s8 D_800A3594W[] asm("D_800A3594.NON_MATCHING");
    extern s8 D_800A3860Signed[][4] asm("D_800A3860");
    extern s8 D_800A39DC[] asm("D_800A39DC.NON_MATCHING");
    extern s8 D_800A3944[] asm("D_800A3944.NON_MATCHING");
    extern u8 D_800A3894[];
    extern u8 D_800A3894W[] asm("D_800A3894.NON_MATCHING");
    extern s8 D_800A3944W[] asm("D_800A3944.NON_MATCHING");
    extern s8 D_800A39FC[];
    extern s32 func_8005CA4C(void);
    extern void func_80055AA4(u8, s32);
    extern void func_80055AA4B(u8, s32) asm("func_80055AA4");
    extern void func_8005C8D8(s32);
    extern s32 func_8005CCEC(u8, s32);
    extern void func_8005CC34(void);
    extern void MenuRefreshSixEntryValues(void);
    extern void func_8005E4A4(u8 *);
    extern void MenuSetTrackLabel(u8);
    extern void MenuFormatLapCount(u8);
    extern void func_80060008(u8);
    extern void MenuSetLinkedObjectLayoutByIndexKR() asm(
        "MenuSetLinkedObjectLayoutByIndex");
    extern void MenuSetDriverPortrait(s8, s8);
    extern void func_80067F34(s8, u8);
    extern void func_8006894C(s8, s32, s32, s32, s32);
    extern void MenuSetVolume(s16, s32);
    extern void func_8006CF90(u8);
    extern void ListSetRangeFields(MenuObj *, s32, s32, s16);
    s32 limit;
    s32 value;
    s32 tableByte;
    u8 changed;

    if (arg0 != 4) {
        if (arg0 != 7) {
            if (arg0 != 0x21) {
                if (arg0 != 0xB) {
                    goto checkButtons;
                }
            }
        }
    }
    if (arg0 == 4) {
        if ((arg1 & 0xFF) != 0) {
            goto checkButtons;
        }
    }
    if (arg0 == 7) {
        if ((arg1 & 0xFF) < 2U) {
            goto checkButtons;
        }
        if ((arg1 & 0xFF) == 6) {
            goto checkButtons;
        }
    }
    if (arg0 == 0xB) {
        if ((arg1 & 0xFF) == 0) {
            goto checkButtons;
        }
    }
    goto repeatProcessing;
checkButtons:
    if ((arg3 & ((u16)~arg4 & 0x8000)) == 0) {
        if ((arg3 & ((u16)~arg4 & 0x2000)) == 0) {
            return;
        }
    }
    goto dispatch;
repeatProcessing:
    switch (arg0) {
    case 7:
    case 0x21:
        limit = 5;
        break;
    default:
        limit = 0xF;
        break;
    }
    if ((arg3 & ~arg4) != 0) {
        D_800A3830 = 0;
        D_800A37F0 = 1;
    } else {
        D_800A3830 = D_800A3830 + 1;
        if (limit >= D_800A3830) {
            return;
        }
        D_800A37F0 = D_800A37F0 + D_800A37F0 / 2;
    }
dispatch:
    switch (arg0) {
    case 2:
        switch (arg1 & 0xFF) {
        case 0:
            if ((func_8005CA4C() & 0xFF) == 0) {
                return;
            }
            break;
        case 1:
            func_80055AA4(arg5, arg2);
            break;
        case 2:
            if (arg2 != 0) {
                if (gSelectedTrackSmall != 0) {
                    gSelectedTrackSmall = gSelectedTrackSmall - 1;
                } else {
                    gSelectedTrackSmall = 0x10;
                }
                while (D_8009957C[gSelectedTrackSmall] == 0) {
                    if (gSelectedTrackSmall != 0) {
                        gSelectedTrackSmall = gSelectedTrackSmall - 1;
                    } else {
                        gSelectedTrackSmall = 0x10;
                    }
                }
            } else {
                if (gSelectedTrackSmall < 0x10) {
                    gSelectedTrackSmall = gSelectedTrackSmall + 1;
                } else {
                    gSelectedTrackSmall = 0;
                }
                while (D_8009957C[gSelectedTrackSmall] == 0) {
                    if (gSelectedTrackSmall < 0x10) {
                        gSelectedTrackSmall = gSelectedTrackSmall + 1;
                    } else {
                        gSelectedTrackSmall = 0;
                    }
                }
            }
            func_8005E4A4(D_800AE178[gSelectedTrackSmall]);
            MenuSetTrackLabel(gSelectedTrackSmall);
            MenuFormatLapCount(gSelectedTrackSmall);
            break;
        case 4:
            arg1 = arg1 & 0xFF;
            D_800A3988[arg1] = D_800A3988B[arg1] ^ 1;
            func_8005C8D8(arg1);
            D_800A3074 = (D_800A3988C[arg1] == 0);
            break;
        case 5:
            arg1 = arg1 & 0xFF;
            D_800A3988D[arg1] = D_800A3988E[arg1] ^ 1;
            func_8005C8D8(arg1);
            D_800A3073NM = (D_800A3988F[arg1] == 0);
            break;
        default:
            return;
        }
        break;
    case 8:
        if ((arg1 & 0xFF) != 0) {
            return;
        }
        func_80055AA4B(0, arg2);
        break;
    case 4:
        switch (arg1 & 0xFF) {
        case 0:
            if (arg2 != 0) {
                value = D_800A37D0NM - D_800A37F0;
                if (value < 3) {
                    D_800A37D0NM = 3;
                } else {
                    D_800A37D0NM = value;
                    SoundPlaySlot(0, 2);
                }
            } else {
                value = D_800A37D0NM + D_800A37F0;
                if (value < 0x65) {
                    D_800A37D0NM = value;
                    SoundPlaySlot(0, 2);
                } else {
                    D_800A37D0NM = 0x64;
                }
            }
            func_8005CC34();
            MenuFormatLapCount(gSelectedTrackSmall);
            return;
        case 1:
            if (arg2 != 0) {
                if (D_800A3988G[1] != 0) {
                    D_800A3988[1] = D_800A3988G[1] - 1;
                } else {
                    D_800A3988[1] = 2;
                }
            } else {
                if (D_800A3988G[1] == 2) {
                    D_800A3988[1] = 0;
                } else {
                    D_800A3988[1] = D_800A3988G[1] + 1;
                }
            }
            func_8005C8D8(1);
            switch (D_800A3988H[1]) {
            case 1:
                D_800A306E = 0;
                break;
            case 0:
                D_800A306E = 1;
                break;
            case 2:
                D_800A306E = 2;
                break;
            }
            if (D_800A306E == 1) {
                if (D_800A3644NM != 0) {
                    D_800A3071 = 0;
                    D_800A3988[2] = 0x81;
                } else {
                    D_800A3071 = 1;
                    D_800A3988[2] = 0;
                }
                D_800A306F = 1;
                D_800A3988[3] = 0;
            } else {
                D_800A3071 = 0;
                D_800A306F = 0;
                D_800A3988[2] = 0x81;
                D_800A3988[3] = 0x81;
            }
            func_8005C8D8(2);
            func_8005C8D8(3);
            break;
        case 2:
            if (D_800A306E == 1 && D_800A3644NM == 0) {
                D_800A3988[2] = D_800A3988I[2] ^ 1;
                func_8005C8D8(2);
                if (D_800A3988J[2] != 0) {
                    D_800A3071 = 0;
                } else {
                    D_800A3071 = 1;
                }
            }
            break;
        case 3:
            if (D_800A306E == 1) {
                D_800A3988[3] = D_800A3988K[3] ^ 1;
                func_8005C8D8(3);
                if (D_800A3988L[3] != 0) {
                    D_800A306F = 0;
                } else {
                    D_800A306F = 1;
                }
            }
            break;
        case 4:
        case 5:
            arg1 = arg1 & 0xFF;
            D_800A3988M[arg1] = D_800A3988N[arg1] ^ 1;
            func_8005C8D8(arg1);
            if (D_800A3988O[arg1] != 0) {
                switch (arg1) {
                case 4:
                    D_800A3070 = 0;
                    break;
                case 5:
                    D_800A3072 = 0;
                    break;
                }
            } else {
                switch (arg1) {
                case 4:
                    D_800A3070 = 1;
                    break;
                case 5:
                    D_800A3072 = 1;
                    break;
                }
            }
            break;
        default:
            return;
        }
        break;
    case 0xB:
        changed = 1;
        switch (arg1 & 0xFF) {
        case 0:
            if (arg2 != 0) {
                D_800A3988NM = (D_800A3988NM + 2) % 3;
            } else {
                D_800A3988NM = (D_800A3988NM + 1) % 3;
            }
            for (arg1 = 0; arg1 < 5; arg1++) {
                D_800A331C[arg1] = D_80099568[D_800A3988NM][arg1];
            }
            D_800A3078NM = D_800A3988NM;
            break;
        case 6:
            return;
        default:
            if (D_800A3078NM != 2) {
                D_800A3078NM = 2;
                D_800A3988NM = 2;
            }
            if (arg2 != 0) {
                changed = func_8005CCEC(arg1 & 0xFF, -D_800A37F0);
            } else {
                changed = func_8005CCEC(arg1 & 0xFF, D_800A37F0);
            }
            break;
        }
        if (D_800A3078NM == 2) {
            for (arg1 = 0; arg1 < 5; arg1++) {
                D_80099574[arg1] = D_800A331C[arg1];
            }
        }
        MenuRefreshSixEntryValues();
        if ((changed & 0xFF) == 0) {
            return;
        }
        break;
    case 5:
        switch (arg1 & 0xFF) {
        case 1:
            D_800A3988P[1] = D_800A3988[1] ^ 1;
            D_800A306C = D_800A306C ^ 1;
            func_8005C8D8(1);
            if (gCdAnnouncerNM != 0) {
                gStereoEnabledNM[0] = 0;
                SsSetMono();
            } else {
                gStereoEnabledNM[0] = 1;
                SsSetStereo();
            }
            break;
        case 5:
            if (D_800A3076 == 0) {
                return;
            }
            D_800A3988Q[5] = D_800A3988R[5] ^ 1;
            func_8005C8D8(5);
            if (D_800A3988S[5] != 0) {
                D_800A3077 = 0;
            } else {
                D_800A3077 = 1;
            }
            break;
        default:
            return;
        }
        break;
    case 7:
        if ((arg1 & 0xFF) < 0) {
            return;
        }
        if ((arg1 & 0xFF) < 2) {
            D_800A3988[arg1 & 0xFF] = D_800A3988B[arg1 & 0xFF] ^ 1;
            D_800A3068Pair[arg5][arg1 & 0xFF] =
                D_800A3068Pair[arg5][arg1 & 0xFF] ^ 1;
            func_8005C8D8(arg1 & 0xFF);
            break;
        }
        if ((arg1 & 0xFF) >= 6) {
            return;
        }
        if (arg2 != 0) {
            D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] =
                D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] - D_800A37F0;
            if ((s8)D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] < 0) {
                D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] = 0;
            } else {
                SoundPlaySlot(0, 2);
            }
            D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] =
                (s8)D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] / 4 * 4;
        } else {
            D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] =
                D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] + D_800A37F0;
            if ((s8)D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] >= 0x40) {
                D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] = 0x3F;
            } else {
                D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] =
                    ((s8)D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] + 3) / 4 * 4;
                if ((s8)D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] >= 0x40) {
                    D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] = 0x3F;
                }
                SoundPlaySlot(0, 2);
            }
        }
        func_80060008(arg5);
        return;
    case 0xE:
        arg1 = D_800A3A14NM[0];
        D_800A39A0[0] = D_800A38FC[0];
        D_800A3A14R2[0] = D_800A3A14NM[0] ^ 1;
        if (arg2 != 0) {
            D_800A3594W[0] = (D_800A3594[0] + 0x17) % 24;
        } else {
            D_800A3594W[0] = (D_800A3594[0] + 1) % 24;
        }
        tableByte = D_8009AD40[D_800A3594R2[0]];
        D_800A39FC[0] = tableByte;
        MenuSetDriverPortrait(D_800A3A14R3[0], (s8)tableByte);
        func_80063AE0(D_800A3A14R4[0], D_800A39FCR2[0]);
        D_800A38FCR2[0] = (MenuObj *)D_800A3744[D_800A3A14R5[0]];
        if (arg2 == 0) {
            ListSetRangeFields(D_800A39A0R3[0], 0, -0x140, -2);
            MenuSetLinkedObjectLayoutByIndexKR(arg1, 0x34, -0x10C, -2);
            ListSetRangeFields(D_800A38FCR4[0], 0x140, 0, -2);
            MenuSetLinkedObjectLayoutByIndexKR(D_800A3A14R7[0], 0x174, 0x34,
                                               -2);
        } else {
            ListSetRangeFields(D_800A39A0R2[0], 0, 0x140, 2);
            MenuSetLinkedObjectLayoutByIndexKR(arg1, 0x34, 0x174, 2);
            ListSetRangeFields(D_800A38FCR3[0], -0x140, 0, 2);
            MenuSetLinkedObjectLayoutByIndexKR(D_800A3A14R6[0], -0x10C, 0x34,
                                               2);
        }
        SoundPlaySlot(0, 2);
        return;
    case 9:
        if (D_800A3A58NM[0] == 0) {
            return;
        }
        D_800A3870[0] = D_800A37D4[0];
        D_800A39DC[0] = D_800A3944[0];
        D_800A3944W[0] = D_800A3944[0] ^ 1;
        if (arg2 != 0) {
            D_800A3894W[0] = (D_800A3894[0] + 0x10) % 17;
        } else {
            D_800A3894W[0] = (D_800A3894[0] + 1) % 17;
        }
        func_80067F34(D_800A3944R2[0], D_800A3894R2[0]);
        D_800A37D4[0] = D_800A360C[D_800A3944R3[0]];
        if (arg2 != 0) {
            func_8006894C(D_800A39DCR2[0], 0, 0x140, 2, 0);
            func_8006894C(D_800A3944R4[0], -0x140, 0, 2, 1);
        } else {
            func_8006894C(D_800A39DCR3[0], 0, -0x140, -2, 0);
            func_8006894C(D_800A3944R4[0], 0x140, 0, -2, 1);
        }
        break;
    case 0x21:
        if (arg2 != 0) {
            D_800A3690NM[arg1 & 0xFF] = D_800A3690NM[arg1 & 0xFF] - D_800A37F0;
            if (*(s16 *)&D_800A3690NM[arg1 & 0xFF] < 0) {
                D_800A3690NM[arg1 & 0xFF] = 0;
            }
        } else {
            D_800A3690NM[arg1 & 0xFF] = D_800A3690NM[arg1 & 0xFF] + D_800A37F0;
            if (*(s16 *)&D_800A3690NM[arg1 & 0xFF] >= 0x65) {
                D_800A3690NM[arg1 & 0xFF] = 0x64;
            }
        }
        MenuSetVolume(*(s16 *)&D_800A3690NM[arg1 & 0xFF], (arg1 & 0xFF) - 2);
        return;
    case 0x23:
        func_8006CF90(arg2);
        if (D_800A3928 == 0) {
            break;
        }
        return;
    case 0:
    case 1:
    default:
        return;
    }
    SoundPlaySlot(0, 2);
}

s32 func_80056B0C(s32 arg0, s32 arg1) {
    s32 result;

    result = 0;
    switch (gScreenStateSmall) {
    case 2:
    case 3:
    case 6:
    case 8:
    case 15:
    case 16:
    case 17:
        result = 0xFF;
        break;
    case 4:
        if ((arg1 & 0xFF) == 8) {
            result = 0xFF;
        }
        break;
    }
    return result;
}

s32 func_80056B5C(s32 arg0, s32 arg1, s32 arg2) {
    s32 result;

    result = 0;
    switch (gScreenStateSmall) {
    case 2:
        if ((arg0 & 0xFF) == 6) {
            result = 1;
        } else if ((arg0 & 0xFF) == 3) {
            result = 1;
        }
        break;
    case 1:
        if ((arg0 & 0xFF) == 0) {
            if ((arg2 & 0xFF) == 0) {
                result = 1;
            }
        } else if ((arg0 & 0xFF) >= 0) {
            if ((arg0 & 0xFF) < 6) {
                if ((arg0 & 0xFF) > 2) {
                    if ((arg2 & 0xFF) != 0) {
                        result = 1;
                    }
                }
            }
        }
        break;
    case 8:
        switch (arg0 & 0xFF) {
        case 1:
            result = 1;
            break;
        }
        break;
    case 4:
        if ((u32)((arg0 - 6) & 0xFF) < 2) {
            result = 1;
        }
        break;
    case 5:
        if ((arg0 & 0xFF) == 4) {
            result = 1;
        } else if ((arg0 & 0xFF) == 0) {
            result = 1;
        }
        break;
    case 3:
        if ((arg0 & 0xFF) < 8) {
            if ((arg0 & 0xFF) >= 0) {
                result = 1;
            }
        }
        break;
    case 6:
        if ((arg0 & 0xFF) < 6) {
            if ((arg0 & 0xFF) >= 0) {
                result = 1;
            }
        }
        break;
    case 7:
    case 11:
        switch (arg0 & 0xFF) {
        case 6:
            result = 1;
            break;
        }
        break;
    case 0:
    case 9:
    case 10:
    case 12:
    case 14:
    case 15:
    case 16:
    case 17:
        result = 1;
        break;
    }
    return result;
}

/* D_800A3644/3988/3073/3078 are declared array-form elsewhere in this
 * TU; the gp-relative byte accesses here go through the .NON_MATCHING
 * label each nonmatching sdata/bss symbol carries at the same address. */
void func_80056C84(s32 arg0, s32 arg1) {
    extern u8 D_800A3644NM asm("D_800A3644.NON_MATCHING");
    extern u8 D_800A3988NM asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3073NM asm("D_800A3073.NON_MATCHING");
    extern s8 D_800A3078NM asm("D_800A3078.NON_MATCHING");
    extern u8 D_800A3988[];
    extern u8 D_800A3988B[] asm("D_800A3988");
    extern u8 D_800A3988C[] asm("D_800A3988");
    extern u8 D_800A3988D[] asm("D_800A3988");
    extern u8 D_800A3988E[] asm("D_800A3988");
    extern u8 D_800A3988F[] asm("D_800A3988");
    extern u8 D_800A3988G[] asm("D_800A3988");
    extern u8 D_800A3988H[] asm("D_800A3988");
    extern u8 D_800A3988I[] asm("D_800A3988");
    extern u8 D_800A3988J[] asm("D_800A3988");
    extern u8 D_800A3988K[] asm("D_800A3988");
    extern u8 D_800A3988L[] asm("D_800A3988");
    extern u8 D_800A3988M[] asm("D_800A3988");
    extern u8 D_800A3988N[] asm("D_800A3988");
    extern u8 D_800A3988O[] asm("D_800A3988");
    extern u8 D_800A3988P[] asm("D_800A3988");
    extern u8 D_800A398F[];
    extern u8 D_800A306C;
    extern u8 D_800A306E;
    extern u8 D_800A306F;
    extern u8 D_800A3070;
    extern u8 D_800A3071;
    extern u8 D_800A3072;
    extern u8 D_800A3074;
    extern u8 D_800A3076;
    extern u8 D_800A3077;
    s32 m2;
    s32 clearCount;
    u8 *clearPtr;
    s32 tmp;
    s32 idx;

    clearCount = 7;
    clearPtr = D_800A398F;
    do {
        *clearPtr = 0;
        clearCount--;
        clearPtr--;
    } while (clearCount >= 0);

    m2 = 8;
    switch (arg0 & 0xFF) {
    case 2:
        tmp = D_800A3644NM;
        D_800A3988NM = tmp;
        if (tmp != 0) {
            D_800A3988[1] = 1;
        }
        D_800A3988[4] = (D_800A3074 == 0);
        D_800A3988[5] = (D_800A3073NM == 0);
        break;
    case 4:
        switch (D_800A306E) {
        case 0:
            m2 = 1;
            break;
        case 1:
            m2 = 0;
            break;
        case 2:
            m2 = 2;
            break;
        }
        D_800A3988[1] = m2;
        if (D_800A306E == 1) {
            if (D_800A3644NM != 0) {
                D_800A3071 = 0;
                D_800A3988[2] = 0x81;
            } else if (D_800A3071 != 0) {
                D_800A3988[2] = 0;
            } else {
                D_800A3988[2] = 1;
            }
            if (D_800A306F != 0) {
                D_800A3988[3] = 0;
            } else {
                D_800A3988[3] = 1;
            }
        } else {
            D_800A306F = 0;
            D_800A3071 = 0;
            D_800A3988[3] = 0x81;
            D_800A3988[2] = 0x81;
        }
        if (D_800A3070 != 0) {
            D_800A3988[4] = 0;
        } else {
            D_800A3988[4] = 1;
        }
        if (D_800A3644NM != 0) {
            D_800A3072 = 0;
            D_800A3988[5] = 0x81;
        } else if (D_800A3072 != 0) {
            D_800A3988[5] = 0;
        } else {
            D_800A3988[5] = 1;
        }
        break;
    case 11:
        D_800A3988NM = D_800A3078NM;
        break;
    case 5:
        D_800A3988[1] = D_800A306C;
        if (D_800A3076 != 0) {
            D_800A3988[5] = (D_800A3077 == 0);
        }
        break;
    case 7:
        idx = (arg1 & 0xFF) * 2;
        D_800A3988NM = D_800A3073[idx - 0xB];
        D_800A3988[1] = D_800A3073[idx - 0xA];
        break;
    }
}

extern u8 gPlayerDriverSmall;
extern u8 D_800A361C;
extern u8 gSelectedTrackSmall;
void func_80056F04(s32 arg0) {
    extern void func_8005E5BC(s32, s32, s32, s32);
    extern void func_8005E7F8(s32, s32, s32, s32);
    extern void func_8005E644(s32, s32, s32, s32);
    extern void MenuSetLinkedObjectMotion(s32, s32, s32, s32);
    extern void func_800631DC(s32, s32, s32);
    s32 idx;
    s32 flag;

    idx = arg0 & 0xFF;
    switch (idx) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
        flag = idx == 7;
        D_800A361C = 0;
        func_8005E5BC(gSelectedTrackSmall, -0x78, 2, flag);
        func_8005E7F8(gSelectedTrackSmall, -0x78, 2, flag);
        func_8005E644(gSelectedTrackSmall, -0x78, 2, flag);
        MenuSetLinkedObjectMotion(-0x78, 0, 2, flag);
        func_800631DC(-0x3C, 0x3C, 2);
        func_80063AE0(0, gPlayerDriverSmall);
        func_80063AE0(1, D_800A36E1[0]);
        switch (gScreenStateSmall) {
        case 2:
        case 8:
            func_80063538(-0x3C, 0x3C, 2);
            break;
        }
        break;
    default:
        D_800A361C = 0xFF;
        return;
    }
}

extern u8 gCardMenuMessagea[] asm("gCardMenuMessage.NON_MATCHING");
extern u8 gCardMenuMessageb[] asm("D_800A3814.NON_MATCHING");
extern u8 gCardMenuMessagec[] asm("D_800A380C.NON_MATCHING");
extern u8 gCardMenuMessaged[] asm("D_800A3810.NON_MATCHING");
extern u8 D_800A3968a[] asm("D_800A3968.NON_MATCHING");
extern u8 D_800A3950nm asm("D_800A3950.NON_MATCHING");

void func_80057008(s32 arg0) {
    extern void CardMenuShowMessage(s32);
    extern void CardMenuCenterSelectedText(s32);
    s32 m2;
    extern void func_8006BD68(void);
    extern u8 D_800A3928;

    if (gCardMenuMessagea[0] == 2 || !(arg0 & 0xFF)) {
        CardMenuShowMessage(0);
        m2 = D_800A3059;
        D_800A3928 = 1;
        if (m2 == 1) {
            CardMenuCenterSelectedText(1);
            if (D_800A3059 == m2) {
                gScreenStateSmall = 0x24;
                D_800A3928 = 2;
                return;
            }
        }
        gScreenStateSmall = 0x23;
    } else if (gScreenStateSmall != 0x28) {
        if (D_800A3059 == 2) {
            func_8006BD68();
            D_800A3928 = 0;
            gCardMenuMessageAbsoluteU8[0] = 0;
            gScreenStateSmall = 0x22;
            CardMenuCenterSelectedText(0);
        } else if (D_800A3059 == 1) {
            if (D_800A3968a[0] == 0) {
                gCardMenuMessageAbsoluteU8[0] = 0x14;
                CardMenuShowMessage(0);
                D_800A3928 = 2;
                gScreenStateSmall = 0x24;
                CardMenuCenterSelectedText(1);
            } else {
                gCardMenuMessageAbsoluteU8[0] = 0;
                gScreenStateSmall = 0x24;
                if (D_800A3950nm == 0) {
                    D_800A3928 = 1;
                } else {
                    D_800A3928 = 0;
                }
                CardMenuCenterSelectedText(1);
            }
        }
    }
}

extern u8 D_800A3704;

void func_80057160(s32 arg0) {
    extern void MenuHideCurrentObject(void);
    extern void CardMenuSetColorNodeLayout(s32, s32, s32);
    extern void func_8006C2D0(s32);
    extern void func_8006CB40(void);
    extern void MenuNegateLinkedObjectValues(u8);
    extern void MenuUpdateItemRow(u8);
    s32 result;

    D_800A3704 = 1;
    MenuHideCurrentObject();
    result = arg0 & 0xFF;
    if (result != 0) {
        CardMenuSetColorNodeLayout(-0x78, 0, 2);
    }
    if (gCardMenuMessageAbsolute2[0] == 0) {
        func_8006C2D0(D_800A3059 == 2);
        func_8006CB40();
    }
    MenuNegateLinkedObjectValues(0);
    MenuUpdateItemRow(gScreenStateSmall);
}

u8 MenuUpdateScreenState(u8 screen, u8 *previous, u8 action) {
    extern u8 D_800A3644NM asm("D_800A3644.NON_MATCHING");
    extern u8 D_800A35C0;
    extern u8 D_800A3064;
    extern u8 D_800A3065;
    extern u8 D_800A374C;
    extern u8 gPlayerDriver[];
    extern s32 D_800AE178[];
    extern u8 D_800AD974[];
    extern u8 D_800AD974Other[] asm("D_800AD974");
    extern s32 gSessionTypeTransition[] asm("gSessionType.NON_MATCHING");
    extern char D_800B9B73[];
    extern void func_8006BA68(void);
    extern void func_8005E4A4(u8 *);
    extern void func_80063C34(u8, u8);
    extern s32 CardFindSavedDriverRecord(char *);
    extern void CardMenuCopyRecordNames(u8, u8);
    extern void func_8006D684(u8);
    extern void MenuSetTrackLabel(u8);
    extern void MenuFormatLapCount(u8);
    extern void CardMenuClearNameCharacters(u8);
    extern void MediaShowTrackIntro(u8);
    extern void func_8006D708(s32, u8, s32);
    extern void MenuSetAllObjectOrderingDepths(s32);
    extern void MoviePlayIndexedFile(u8);
    extern void MoviePlayIndexedFileAlternate(s32);
    u8 i;
    u8 next;
    u8 selection;
    u8 found;

    selection = 0;
    switch (screen) {
    case 0:
        switch (D_800A3059) {
        case 1:
            D_800A3644NM = 0;
            func_8006BA68();
            BufferClear17Bytes();
            gSelectedTrackSmall = 0;
            func_8005E4A4(D_800AE178[0]);
            if (D_800A3064 != 0) {
                func_80063C34(5, 0x18);
                D_800A3064 = 0;
            }
            if (D_800A3065 != 0) {
                func_80063C34(2, 0x19);
                D_800A3065 = 0;
            }
            next = 1;
            break;
        case 2:
            next = 14;
            break;
        case 4:
            next = 4;
            break;
        case 5:
            next = 15;
            break;
        case 0:
            next = 2;
            break;
        case 3:
            next = 5;
            break;
        default:
            next = 0;
            break;
        }
        break;
    case 2:
        if (action == 0xFF) {
            if (*previous == 0 || *previous == 3) {
                next = *previous;
            } else {
                next = D_800A35C0;
            }
            *previous = 2;
        resetSelection:
            selection = 0;
        } else {
            next = 3;
            if (D_800A3059 == 3) {
                D_800A35C0 = *previous;
                next = 4;
            } else {
                for (i = 0; i < D_800A3644NM + 1; i++) {
                    found = CardFindSavedDriverRecord(
                        gDriverNames[gPlayerDriver[i]]);
                    if (found != 0xFF) {
                        CardMenuCopyRecordNames(i, found);
                    }
                }
                func_8006D684(gSelectedTrackSmall);
            }
        }
        break;
    case 1:
        if (action == 0xFF) {
            next = 0;
            *previous = 1;
            selection = 1;
        } else {
            switch (D_800A3059) {
            case 0:
                next = 8;
                func_8006BA68();
                BufferClear17Bytes();
                gSelectedTrackSmall = 0;
                func_8005E4A4(D_800AE178[0]);
                MenuSetTrackLabel(gSelectedTrackSmall);
                MenuFormatLapCount(gSelectedTrackSmall);
                CardMenuClearNameCharacters(gSelectedTrackSmall);
                break;
            case 5:
                next = 6;
                if (D_800AD974[gSelectedTrackSmall] == 0) {
                    MediaShowTrackIntro(gSelectedTrackSmall);
                    D_800AD974Other[gSelectedTrackSmall] = 1;
                }
                break;
            case 3:
                next = 10;
                break;
            case 4:
                next = 12;
                break;
            default:
                next = 0;
                selection = 1;
                found =
                    CardFindSavedDriverRecord(gDriverNames[gPlayerDriverSmall]);
                if (found != 0xFF) {
                    CardMenuCopyRecordNames(0, found);
                } else {
                    i = 0;
                    do {
                        CardMenuClearNameCharacters(i);
                        i++;
                    } while (i < 17U);
                }
                break;
            }
        }
        break;
    case 8:
        next = 1;
        if (action == 0xFF) {
            *previous = 0;
        } else {
            gSelectedTrackSmall = 0;
            next = 4;
            func_8006BA68();
            D_800B9B73[0] = gPlayerDriverSmall;
            strcpy(D_800B9B73 - 31, gDriverNames[gPlayerDriverSmall]);
        }
        break;
    case 5:
        if (D_800A3059 == 0) {
            next = 13;
        } else {
            next = *previous;
            switch (next) {
            case 3:
                selection = 5;
                break;
            case 0:
                goto selectionThree;
            case 6:
                selection = 4;
                break;
            }
        }
        break;
    case 4:
        if (action == 0xFF) {
            next = 8;
            *previous = 4;
        } else if (D_800A3059 == 6) {
            next = 11;
        } else if (*previous == 8) {
            next = 6;
            MediaShowTrackIntro(gSelectedTrackSmall);
            D_800AD974[gSelectedTrackSmall] = 1;
        } else {
            next = *previous;
            switch (next) {
            case 0:
                selection = 4;
                break;
            case 2:
                selection = 3;
                break;
            }
        }
        break;
    case 11:
        next = 4;
        selection = 6;
        break;
    case 3:
        if (action == 0xFF) {
            next = 0;
            *previous = 3;
        } else {
            switch (D_800A3059) {
            case 7:
                next = 0;
                goto resetSelection;
            case 0:
                next = 2;
                break;
            case 6:
                next = 9;
                break;
            case 1:
                next = 7;
                break;
            case 2:
                gSessionTypeAbsolute[0] = 2;
                next = 0xFF;
                break;
            case 3:
                gSessionTypeTransition[0] = 1;
                next = 0xFF;
                break;
            case 4:
                gSessionTypeAbsolute[0] = 0;
                next = 0xFF;
                break;
            case 5:
                next = 5;
                break;
            }
        }
        break;
    case 6:
        if (action == 0xFF) {
            next = 1;
            *previous = 6;
        } else {
            switch (D_800A3059) {
            case 5:
                next = 1;
                break;
            case 1:
                gSessionTypeAbsolute[0] = 2;
                next = 0xFF;
                break;
            case 2:
                gSessionTypeTransition[0] = 1;
                next = 0xFF;
                break;
            case 0:
                next = 7;
                break;
            case 3:
                gSessionTypeAbsolute[0] = 0;
                next = 0xFF;
                break;
            case 4:
                next = 5;
                break;
            }
        }
        break;
    case 7:
        if (action == 0xFF) {
            *previous = 7;
            selection = 1;
            next = 3;
        } else {
            func_8006D708(0, gSelectedTrackSmall, *previous == 3);
            func_8006D708(1, gSelectedTrackSmall, *previous == 3);
            found = *previous;
            if ((u8)(found + 6) < 2U) {
                gSessionTypeAbsolute[0] = 0;
                next = 0xFF;
            } else {
                next = found;
                switch (next) {
                case 3:
                    *previous = 7;
                    selection = 1;
                    break;
                case 6:
                    goto resetSelection;
                }
            }
        }
        break;
    case 9:
        MenuSetAllObjectOrderingDepths(0);
        next = 3;
        selection = 6;
        break;
    case 10:
        MenuSetAllObjectOrderingDepths(0);
        next = 1;
    selectionThree:
        selection = 3;
        break;
    case 12:
        MenuSetAllObjectOrderingDepths(0);
        next = 1;
        if (*previous == 1) {
            selection = 4;
        } else if (gSelectedTrackSmall < 17U) {
            selection = 5;
        } else {
            if (D_800A374C < 3U) {
                MoviePlayIndexedFile(D_800A374C);
            }
            gSelectedTrackSmall = 0;
            next = 0;
        }
        break;
    case 13:
        next = 5;
        break;
    case 252:
        next = 0;
        *previous = 0;
        break;
    case 14:
        selection = 2;
        next = 0;
        break;
    case 15:
        if (action == 0xFF) {
            next = 0;
        } else {
            switch (D_800A3059) {
            case 0:
                next = 16;
                break;
            case 1:
                next = 17;
                break;
            case 2:
                selection = 5;
                next = 0;
                break;
            }
        }
        break;
    case 16:
    case 17:
        if (action != 0xFF) {
            MoviePlayIndexedFileAlternate(screen == 16);
        }
        selection = screen - 16;
        next = 15;
        MenuSetAllObjectOrderingDepths(0);
        break;
    }
    if (action != 0xFF && screen != 5 && screen != 13 && screen != 7 &&
        screen != 4 && screen != 11) {
        *previous = screen;
    }
    D_800A3059 = selection;
    return next;
}

extern s32 D_800A3654Lui asm("D_800A3654Absolute");
void SceneAllocateRuntimeBuffers(void) {
    gMenuObjectPoolAbsolute2[0] = (s32)HeapAlloc(0x1AB8);
    gMenuObjectPoolCountAbsolute[0] = 0;
    D_800A3654Lui = (s32)HeapAlloc(0x834);
    ((u8 *)D_800A37B4Absolute)[8] = 0;
}

extern void func_80012E28(void);
extern s32 D_800A3548;
extern s32 D_800A3998;
extern s32 D_800A3A18;
extern s32 D_800A39A8;
extern s32 D_800A39CC;
extern s32 D_800A3780;
extern s32 D_800A35B8;
extern s32 D_800A3544;
extern s32 D_800A38EC;
void SceneInitPrimPools(void) {
    POLY_FT4 *poly;
    POLY_F4 *shade;
    u32 count;
    s32 base;

    func_80012E28();
    D_800A3548 = (s32)HeapAlloc(0x4290);
    poly = (POLY_FT4 *)D_800A3548;
    for (count = 0; count < 0x1AA; count++) {
        SetPolyFT4(poly);
        SetShadeTex(poly, 0);
        poly->r0 = 0x80;
        poly->g0 = 0x80;
        poly->b0 = 0x80;
        poly++;
    }
    base = D_800A3548;
    D_800A397CAbsolute[27] = base;
    D_800A3998 = base + 0x3E80;
    D_800A3A18 = base + 0x3E80;
    D_800A39A8 = base + 0x4268;
    D_800A39CC = base + 0x4268;
    D_800A3780 = (s32)HeapAlloc(0x4B0);
    shade = (POLY_F4 *)D_800A3780;
    D_800A35B8 = (s32)shade;
    D_800A3544 = (s32)shade + 0x3C0;
    D_800A38EC = (s32)shade + 0x3C0;
    for (count = 0; count < 0x32; count++) {
        SetPolyF4(shade);
        shade->r0 = 0x80;
        shade->g0 = 0x80;
        shade->b0 = 0x80;
        SetSemiTrans(shade, 0);
        shade++;
    }
    MenuAllocateObjectBuffer();
}

extern s32 gMenuObjectPoolLui asm("gMenuObjectPoolAbsolute");
void func_80057BFC(void) {
    extern void CardMenuFreeResources(void);
    extern void MenuFreeResourceBlock(void);
    extern void MenuFreeObjectBuffer(void);
    extern void func_80014A68(void);
    extern void func_80063A20(void);

    CardMenuFreeResources();
    if (D_800A3780 != 0) {
        HeapFree((void *)D_800A3780);
    }
    D_800A3780 = 0;
    if (D_800A3548 != 0) {
        HeapFree((void *)D_800A3548);
    }
    D_800A3548 = 0;
    MenuFreeResourceBlock();
    MenuFreeObjectBuffer();
    if (gMenuBackground != 0) {
        HeapFree(gMenuBackground);
    }
    gMenuBackground = 0;
    if (gMenuObjectPoolLui != 0) {
        HeapFree((void *)gMenuObjectPoolLui);
    }
    gMenuObjectPoolLui = 0;
    if (D_800A3654Lui != 0) {
        HeapFree((void *)D_800A3654Lui);
    }
    D_800A3654Lui = 0;
    func_80014A68();
    func_80063A20();
}

extern s32 D_800A36EC;
extern s32 D_800A3964;
extern s32 D_800A3580;
extern s32 D_800A3650;

#ifdef NON_MATCHING
/* w9f: gScreenStateSmall unlock works (gp lbu matches). Remaining wall:
 * the then-branch must interleave load,load,add,store,add,store with
 * EC->v1 / A18->v0 (v1 reused for both increment results, anti-dep
 * keeps the second addiu below the first store). Every plain-C form
 * tried (+=, hoisted local, explicit count/next locals, asm("") barrier)
 * gives loads->v0/v1 in C order with both addius before the first store;
 * the asm("") form splits too far (+8, reloads after the store).
 * gPrimitiveCursor[0] += 0x28 also ICEs cc1 at this TU position (0-symbol
 * object); read/store it via gPrimitiveCursorAbsolute[0] instead. */
void GraphicsAllocPolyFT4(s32 arg0) {
    s32 cursor;

    arg0 &= 0xFF;
    if (arg0 != 0) {
        D_800A36EC += 1;
        D_800A3A18 += 0x28;
    } else if (gScreenStateSmall != 0x80) {
        D_800A3964 += 1;
        cursor = gPrimitiveCursorAbsolute[0];
        gPrimitiveCursorAbsolute[0] = cursor + 0x28;
    } else {
        D_800A36D0Absolute[-21] = D_800A36D0Absolute[-21] + 0x28;
    }
}

void GraphicsAllocPolyF4(s32 arg0) {
    s32 cursor;

    arg0 &= 0xFF;
    if (arg0 != 0) {
        D_800A3580 += 1;
        D_800A35B8 += 0x18;
    } else if (gScreenStateSmall != 0x80) {
        D_800A3650 += 1;
        cursor = gPrimitiveCursorAbsolute[0];
        gPrimitiveCursorAbsolute[0] = cursor + 0x28;
    } else {
        D_800A36D0Absolute[-21] = D_800A36D0Absolute[-21] + 0x28;
    }
}
#else

extern s32 gPrimitiveCursorLui asm("gPrimitiveCursorAbsolute");
extern s32 D_800A367CLui asm("D_800A367CAbsolute");
u8 *GraphicsAllocPolyFT4(s32 arg0) {
    u8 *prim;

    arg0 &= 0xFF;
    if (arg0 != 0) {
        prim = (u8 *)D_800A3A18;
        D_800A36EC += 1;
        D_800A3A18 = (s32)prim + 0x28;
        return prim;
    }
    if (gScreenStateSmall == 0x80) {
        prim = (u8 *)D_800A367CAbsolute2[0];
        D_800A367CLui = (s32)prim + 0x28;
        return prim;
    }
    prim = (u8 *)gPrimitiveCursor[0];
    D_800A3964 += 1;
    gPrimitiveCursorLui = (s32)prim + 0x28;
    return prim;
}

u8 *GraphicsAllocPolyF4(s32 arg0) {
    u8 *prim;

    arg0 &= 0xFF;
    if (arg0 != 0) {
        prim = (u8 *)D_800A35B8;
        D_800A3580 += 1;
        D_800A35B8 = (s32)prim + 0x18;
        return prim;
    }
    if (gScreenStateSmall == 0x80) {
        prim = (u8 *)D_800A367CAbsolute2[0];
        D_800A367CLui = (s32)prim + 0x28;
        return prim;
    }
    prim = (u8 *)gPrimitiveCursor[0];
    D_800A3650 += 1;
    gPrimitiveCursorLui = (s32)prim + 0x28;
    return prim;
}

#endif

void func_80057DD4(void) {
    D_800A3650 = 0;
    D_800A3544 = D_800A38EC;
}

void func_80057DE8(void) {
    D_800A3580 = 0;
    D_800A35B8 = D_800A3780;
}

void func_80057DFC(void) {
    D_800A3964 = 0;
    D_800A39CC = D_800A39A8;
}

void func_80057E10(void) {
    D_800A36EC = 0;
    D_800A3A18 = D_800A3998;
}

extern DRAWENV D_800BDD4C[];
extern DISPENV D_800BDE04[];
void GraphicsInitDoubleBufferSwapped(void) {
    s32 height;
    DRAWENV *draw;
    DISPENV *disp;

    height = 0xF0;
    draw = D_800BDD4C;
    SetDefDrawEnv(draw, 0, 0, 0x140, height);
    disp = D_800BDE04;
    SetDefDispEnv(disp, 0x140, 0, 0x140, height);
    draw = (DRAWENV *)((u8 *)draw + 0x5C);
    SetDefDrawEnv(draw, 0x140, 0, 0x140, height);
    disp = (DISPENV *)((u8 *)disp + 0x14);
    SetDefDispEnv(disp, 0, 0, 0x140, height);
    D_800BDD62[0] = 0;
    D_800BDDBE[0] = 0;
    D_800BDDC0[0] = 1;
    D_800BDD64[0] = 1;
    D_800BDD65[0] = 0;
    D_800BDD66[0] = 0;
    D_800BDD67[0] = 0;
    D_800BDDC1[0] = 0;
    D_800BDDC2[0] = 0;
    D_800BDDC3[0] = 0;
    PutDrawEnv(draw);
    PutDispEnv(disp);
}

extern u8 D_800A8C14[];
extern u8 D_800A8B94[];
void GraphicsQueueDrawEnvironment(u8 arg0, s32 arg1, s32 arg2, s32 arg3,
                                  s32 arg4, s32 arg5) {
    u8 *env;
    u32 *ot;
    s32 cond;

    cond = (arg0 != 0);
    arg1 += -cond & 0x140;
    SetDefDrawEnv((DRAWENV *)D_800A8C14, arg1, arg2, arg3, arg4);
    env = D_800A8B94 + arg0 * 0x40;
    SetDrawEnv((DR_ENV *)env, (DRAWENV *)D_800A8C14);
    ot = (u32 *)gOrderingTable[0];
    AddPrim(ot + arg5, env);
}

void GraphicsHideDisplay(s32 hide) {
    if (hide & 0xFF) {
        SetDispMask(0);
        SetGraphDebug(0);
    }
    SetGeomScreen(0x82);
}

void InputGetPadButtons(s32 index, s32 *out) {
    *out = PadGetButtons(index & 0xFF);
}

void GraphicsPutCurrentEnvironments(void) {
    PutDispEnv(&D_800BDE04[D_800A305C]);
    PutDrawEnv(&D_800BDD4C[D_800A305C]);
}

/* Load a file into buf, or into a fresh heap block when buf is 0, and
 * return the buffer. The loop notes from do/while (0) double the weight of
 * the HeapAlloc references, which ranks size ahead of sector for the saved
 * registers, as in retail. */
void *FileLoadOffsetTable(s32 fileId, void **outTable, s32 buf) {
    extern s32 gSceneFileMode[];
    s32 size;
    s32 sector;

    sector = (s32)FileOpen(fileId, gSceneFileMode);
    size = (FileSeek(sector, 0, 2) + 0x7FF) >> 11 << 11;
    if (buf == 0) {
        do {
            buf = (s32)HeapAlloc(size);
        } while (0);
    }
    FileSeek(sector, 0, 0);
    FileRead(buf, 1, size, sector);
    FileClose(sector);
    *outTable = (void *)(buf + 4);
    return (void *)buf;
}

asm(".globl D_800A3814w45S\nD_800A3814w45S = D_800A3814");
asm(".globl D_800A3075w45S\nD_800A3075w45S = D_800A3075");

void func_80058148(void) {
    extern s32 D_800A3814w45S;
    extern u8 D_800A3075w45S;
    extern u8 D_800A3644w45 asm("D_800A3644.NON_MATCHING");
    extern u8 D_800A306E;
    extern u8 D_800A306F;
    extern u8 D_800A3070;
    extern u8 D_800A3072;
    extern u8 D_800A3076;
    extern u8 D_800A3077;
    extern s32 D_800A2CE0w45[] asm("D_800A2CE0.NON_MATCHING");
    extern s32 D_800A2EA8w45[] asm("D_800A2EA8.NON_MATCHING");
    extern s32 gSplitScreenModew45[] asm("gSplitScreenMode.NON_MATCHING");
    extern u8 D_800A2EDCw45[] asm("D_800A2EDC.NON_MATCHING");
    extern u8 D_800A2EE0w45[] asm("D_800A2EE0.NON_MATCHING");
    extern s8 D_800A3A25w45[] asm("D_800A3A25.NON_MATCHING");
    extern u8 D_800A38F0w45[] asm("D_800A38F0.NON_MATCHING");
    extern u8 D_800A3A60w45[] asm("D_800A3A60.NON_MATCHING");
    extern u8 D_800A3688w45[] asm("D_800A3688.NON_MATCHING");
    extern u8 D_800A36E4w45[] asm("D_800A36E4.NON_MATCHING");
    extern u8 gPadTypew45[] asm("gPadType.NON_MATCHING");
    s32 i;

    D_800A2EA8w45[0] = D_800A3814w45S;
    D_800A2CE0w45[0] = gSelectedTrackSmall;
    if (D_800A3644w45 != 0 && D_800A3A25w45[0] == 0) {
        D_800A3644w45 = 0;
    }
    gSplitScreenModew45[0] = D_800A3644w45;
    switch (D_800A306E) {
    case 0:
        D_800A2EDCw45[0] = 0;
        D_800A2EE0w45[0] = 0;
        break;
    case 1:
        D_800A2EDCw45[0] = 1;
        D_800A2EE0w45[0] = 0;
        break;
    case 2:
        D_800A2EDCw45[0] = 1;
        D_800A2EE0w45[0] = 1;
        break;
    }
    D_800A38F0w45[0] = D_800A306F;
    D_800A3A60w45[0] = D_800A3070;
    if (D_800A3644w45 == 0 && D_800A3072 != 0) {
        D_800A3688w45[0] = 1;
    } else {
        D_800A3688w45[0] = 0;
    }
    for (i = 0; i < D_800A3644w45 + 1; i++) {
        if ((PadTypeNeedsCalibration(gPadTypew45[i]) & 0xFF) != 0) {
            if (D_800A36E4w45[i] != 0) {
                func_8006E484(i, (s8)gPadTypew45[i]);
            } else {
                func_8006DD28(i & 0xFF, gPadTypew45[i]);
            }
        } else {
            func_8006DD28(i & 0xFF, 2);
        }
    }
    if (D_800A3076 != 0) {
        D_800A3075w45S = D_800A3077;
    } else {
        D_800A3075w45S = 0;
    }
}

typedef struct {
    s8 id;
    s32 time;
} GridEntry;

extern u8 D_800993D0[][24];
extern u8 D_800B9DA4[];
s32 func_80014398(s32 arg0);

/* Builds the qualifying order for a track: random times, the players at the
 * back, then a selection sort by time. gPlayerDriver is read as a 2-byte array
 * so its loads stay behind the D_800AEB34 stores, as in retail.
 */
void RaceBuildQualifyingGrid(s32 track) {
    extern u8 D_800A3073NM asm("D_800A3073.NON_MATCHING");
    extern u8 gPlayerDriverPair[2] asm("gPlayerDriverSmall");
    extern u8 D_800A36E1Lui asm("D_800A36E1Absolute");
    GridEntry entries[24];
    GridEntry tmp;
    s32 times[24];
    s32 i;
    s32 j;
    s32 best;
    s32 cur;
    s32 bestIndex;
    s32 record;
    s32 base;
    s32 step;
    s32 offset;
    s32 index0;
    s32 index1;

    for (i = 0; i < 24; i++) {
        entries[i].id = D_800993D0[track][i];
        if (entries[i].id == gPlayerDriverPair[0]) {
            index0 = i;
        }
        if (entries[i].id == D_800A36E1Lui) {
            index1 = i;
        }
    }
    for (i = 0; i < 24; i++) {
        entries[i].time = (30 - i) * 10 + RandomScaledGet(100);
    }
    entries[index0].time = 0;
    if (D_800A3644 != 0) {
        entries[index1].time = 1;
    }
    for (i = 0; i < 23; i++) {
        cur = entries[i].time;
        best = 0;
        for (j = i + 1; j < 24; j++) {
            if (best < entries[j].time) {
                best = entries[j].time;
                bestIndex = j;
            }
        }
        if (cur < best) {
            tmp = entries[i];
            entries[i] = entries[bestIndex];
            entries[bestIndex] = tmp;
        }
    }
    for (i = 0; i < 24; i++) {
        gDriverOrder[i] = entries[i].id;
        D_800B9DA4[entries[i].id] = i;
    }
    record = func_80014398(track);
    if (RandomScaledGet(32) < 0) {
        base = record + RandomScaledGet(32);
    } else {
        base = record - RandomScaledGet(32);
    }
    offset = 0;
    step = base / 100;
    for (i = 0; i < 23; i++) {
        if (RandomScaledGet(step) < 0) {
            offset = offset - RandomScaledGet(step) + 1;
        } else {
            offset = offset + RandomScaledGet(step) + 1;
        }
        times[i] = base + offset;
    }
    for (i = 0; i < 23; i++) {
        D_800AEB34[gDriverOrder[i]] = times[i];
        D_800AE1EC[i] = times[i];
    }
    if (D_800A3644 != 0 && D_800A3073NM != 0) {
        if (RandomScaledGet(50) >= 26) {
            D_800B9DA4[D_800A36E1Lui] = 6;
            D_800B9DA4[gPlayerDriverPair[0]] = 7;
            gDriverOrder[6] = D_800A36E1Lui;
            gDriverOrder[7] = gPlayerDriverPair[0];
        } else {
            D_800B9DA4[gPlayerDriverPair[0]] = 6;
            D_800B9DA4[D_800A36E1Lui] = 7;
            gDriverOrder[6] = gPlayerDriverPair[0];
            gDriverOrder[7] = D_800A36E1Lui;
        }
        D_800AEB34[D_800A36E1Lui] = 0x7FFFFFFF;
        D_800AEB34[gPlayerDriverPair[0]] = 0x7FFFFFFF;
        D_800AE1EC[7] = 0x7FFFFFFF;
        D_800AE1EC[6] = 0x7FFFFFFF;
    } else {
        D_800AEB34[gDriverOrder[23]] = 0x7FFFFFFF;
        D_800AE1EC[23] = 0x7FFFFFFF;
    }
}

__inline__ u8 RaceFindDriverPosition(u8 value) {
    s32 i;
    for (i = 0; i < 24; i++) {
        if (gDriverOrder[i] == value) {
            return i;
        }
    }
    return 255;
}

extern u8 D_800A3718;
extern u8 D_800A3074;
extern u8 D_800A3073NM asm("D_800A3073.NON_MATCHING");
extern u8 gPlayerDriverPair[2] asm("gPlayerDriverSmall");
typedef struct {
    s16 qualifyPlace;
    s16 finishPlace;
    u32 bestTime;
    s32 unk8;
} SeasonTrackResult;
extern SeasonTrackResult gSeasonTrackResults[];
extern u16 D_800B9B84[];
extern s32 D_800B0B1C[];
extern s32 D_800995D4[];
extern void CardMenuClearNameCharacters(u8);
extern void func_8006D708(s32, u8, s32);

extern u8 D_800B9B6E[];
void RaceRecordSessionResult(void) {
    s32 i;
    u8 pos;
    s32 m;

    if (gSessionTypeAbsolute[0] >= 0) {
        for (i = 0; i < 2; i++) {
            func_8006D708(i, gSelectedTrackSmall,
                          D_800A3950 == 3 || D_800A3950 == 0xFB);
        }
    }

    switch (gSessionTypeAbsolute[0]) {
    case -2:
    case -1:
        D_800A3950 = 0xFE;
        gScreenStateSmall = 0xF9;
        D_800A3059 = 0;
        gPlayerDriverPair[0] = D_800A3718;
        break;
    case 0:
        if (D_800A3950 == 6 || D_800A3950 == 0xFA) {
            D_800B9B72[0]++;
            pos = RaceFindDriverPosition(gPlayerDriverPair[0]);
            if (D_800B0B1C[pos] == -1) {
                gSeasonTrackResults[gSelectedTrackSmall].finishPlace = -1;
            } else {
                gSeasonTrackResults[gSelectedTrackSmall].finishPlace = pos + 1;
                D_800B9B71[0]++;
            }
            if (D_800AE1EC[pos] <
                gSeasonTrackResults[gSelectedTrackSmall].bestTime) {
                gSeasonTrackResults[gSelectedTrackSmall].bestTime =
                    D_800AE1EC[pos];
            }
            if (pos == 0) {
                D_800B9B6E[0]++;
            }
            if (pos < 5) {
                D_800B9B6F[0]++;
            }
            if (pos < 10) {
                D_800B9B70[0]++;
            }
            for (i = 0; i < 24; i++) {
                D_800B9B84[gDriverOrder[i]] += D_800995D4[i];
            }
            if (gSelectedTrackSmall < 17) {
                gSelectedTrackSmall++;
                if (gSelectedTrackSmall < 17) {
                    CardMenuClearNameCharacters(gSelectedTrackSmall);
                }
            }
            gScreenStateSmall = 12;
            D_800A3950 = 12;
            D_800A3059 = 5;
        } else if (D_800A3950 == 3 || D_800A3950 == 0xFB) {
            CardUpdateDriverRecords(0, D_800A3644 != 0, D_800A3074,
                                    D_800A3644 != 0 && D_800A3073NM == 0);
            gScreenStateSmall = 3;
            D_800A3950 = 3;
            D_800A3059 = 0;
        }
        break;
    case 1:
        gScreenStateSmall = 7;
        if (D_800A3950 == 6) {
            gSeasonTrackResults[gSelectedTrackSmall].qualifyPlace =
                D_800B9DA4[gPlayerDriverPair[0]] + 1;
            pos = RaceFindDriverPosition(gPlayerDriverPair[0]);
            if (D_800AE1EC[pos] <
                gSeasonTrackResults[gSelectedTrackSmall].bestTime) {
                gSeasonTrackResults[gSelectedTrackSmall].bestTime =
                    D_800AE1EC[pos];
            }
            D_800A3950 = 0xFA;
        } else if (D_800A3950 == 3) {
            D_800A3950 = 0xFB;
            CardUpdateDriverRecords(1, 0, 0);
        }
        D_800A3059 = 0;
        pos = RaceFindDriverPosition(gPlayerDriverPair[0]);
        D_800AEB34[gPlayerDriverPair[0]] = D_800B0B1C[pos];
        break;
    case 2:
        if (D_800A3950 == 6) {
            pos = RaceFindDriverPosition(gPlayerDriverPair[0]);
            if (D_800AE1EC[pos] <
                gSeasonTrackResults[gSelectedTrackSmall].bestTime) {
                gSeasonTrackResults[gSelectedTrackSmall].bestTime =
                    D_800AE1EC[pos];
            }
            gScreenStateSmall = 6;
            D_800A3059 = 1;
        } else {
            CardUpdateDriverRecords(2, 0, 0);
            gScreenStateSmall = 3;
            D_800A3950 = 3;
            D_800A3059 = 2;
        }
        break;
    }
}

/* SystemSetGlobalPointer: writes $gp directly; not expressible in C. */
void SystemSetGlobalPointer(s32 gp) {
    /* Retail writes the new global pointer directly; not expressible
     * in plain C. */
    asm("addu $gp, $a0, $zero");
}

void func_80058D14(u16 *src, u16 *dst, s32 arg2) {
    u8 *end;
    u16 bits;
    u32 pixel;
    u8 value;
    s32 shift;
    u8 j;

    end = (u8 *)dst + 0x257FE;
    do {
        bits = *src;
        pixel = 0;
        shift = 0;
        j = 0;
        do {
            value = (u8)(arg2 + (bits & 0x1F));
            if (value >= 0x20) {
                value = 0x1F;
            }
            pixel |= value << shift;
            shift += 5;
            j++;
            bits >>= 5;
        } while ((j & 0xFF) < 3);
        *dst = pixel;
        dst = (u16 *)((u8 *)dst + 2);
        src = (u16 *)((u8 *)src + 2);
    } while (end >= (u8 *)dst);
}

void func_80058D8C(void) {
}

extern POLY_FT4 *D_800A34FC;
extern s32 gOrderingTablestore[] asm("gOrderingTable");
extern s32 gOrderingTabledraw[] asm("gOrderingTable");
extern DISPENV D_800BDE18put[] asm("D_800BDE18");
extern s32 D_800A3904[];
extern u8 D_800A3A48;
extern u8 D_800A3724;
extern u8 gCdAudioEnabled[];
extern DRAWENV D_800BDDA8[];
extern DISPENV D_800BDE18[];
extern s32 D_800A3638;
extern s32 D_800A381C;
extern void MenuStartVBlankEvent(void);
extern void PadResetAndInitializeBuffersScene(s32);
extern s32 RandomScaledGetScene(void);
asm(".globl PadResetAndInitializeBuffersScene\nPadResetAndInitializeBuffersScene = PadResetAndInitializeBuffers");
asm(".globl RandomScaledGetScene\nRandomScaledGetScene = RandomScaledGet");

void func_80058D94(void) {
    extern s32 FileSeekScene(s32, s32, s32) asm("FileSeek");
    extern void FileCloseScene(s32) asm("FileClose");
    extern void TextureLoadTim(void *);
    extern s32 gSceneFileMode[];
    s32 done;
    s32 prevPads;
    RECT rect;
    s32 pad[6];
    s32 *volatile offsets;
    u32 frame;
    s32 fade;
    u8 *texBuf;
    u8 toggle;
    u8 *fileBuf;
    u8 *buf;
    u8 *prim;
    s32 xa;
    s32 xb;
    s32 sector;
    s32 size;
    u8 counter;
    s32 bank;
    u8 *ot;
    u8 *envByte;
    s16 *xy;
    s32 height;
    u16 tpage;
    s32 pads;
    s32 mask;
    s32 cond;
    s32 moveX;
    u16 *src;
    u16 *dst;
    u8 *end;
    u16 bits;
    u32 pixel;
    u8 value;
    s32 shift;
    u8 j;

    (void)&pad;
    if (D_800A3638 == 0) {
        sector = (s32)FileOpen(0, gSceneFileMode);
        size = (FileSeekScene(sector, 0, 2) + 0x7FF) >> 11 << 11;
        buf = HeapAlloc(size);
        FileSeekScene(sector, 0, 0);
        FileRead(buf, 1, size, sector);
        FileCloseScene(sector);
        offsets = (s32 *)(buf + 4);
        fileBuf = buf;
    } else {
        fileBuf = (u8 *)D_800A3638;
        offsets = (s32 *)D_800A381C;
    }
    gMenuBackground = fileBuf + offsets[0];
    texBuf = HeapAlloc(0x25800);
    TextureLoadTim(gMenuBackground);
    D_800A3710[0] = D_800A39B0[0];
    D_800A35F0 = (u16 *)D_800A36B4w6c[0];
    DrawSync(0);
    TextureLoadTim(fileBuf + offsets[1]);
    DrawSync(0);
    TextureLoadTim(fileBuf + offsets[2]);
    DrawSync(0);
    D_800A34FC = (POLY_FT4 *)D_800B9990;
    frame = 0;
    SetPolyFT4((POLY_FT4 *)D_800B9990);
    SetShadeTex(D_800A34FC, 0);
    D_800A34FC->r0 = 0x80;
    D_800A34FC->g0 = 0x80;
    D_800A34FC->b0 = 0x80;
    SetSemiTrans(D_800A34FC, 0);
    tpage = GetTPage(2, 0, 0x100, 0x100);
    prim = (u8 *)D_800A34FC;
    D_800A34FC->u0 = 0x40;
    envByte = (u8 *)D_800A34FC + 0xD;
    ((POLY_FT4 *)prim)->tpage = tpage;
    envByte[0] = 0x24;
    D_800A34FC->u1 = 0xA0;
    D_800A34FC->v1 = 0x24;
    D_800A34FC->u2 = 0x40;
    D_800A34FC->v2 = 0x39;
    D_800A34FC->u3 = 0xA0;
    D_800A34FC->v3 = 0x39;
    xy = (s16 *)D_800A34FC;
    cond = (u32)(gSessionTypeAbsolute[0] + 3) < 2;
    xy[4] = (xa = 0x73);
    xb = 0xD3;
    xy[5] = 0xBC;
    xy[9] = 0xBC;
    xy[8] = xb;
    xy[12] = xa;
    xy[13] = 0xD1;
    xy[16] = xb;
    xy[17] = 0xD1;
    if (cond == 0) {
        SsStart2();
        frame = MoviePlayFile(1, 0, 1);
        if ((frame & 0xFF) != 0 || (D_800A3904[0] & 0x800) <= 0) {
            frame = MoviePlayFile(2, 1, 1);
        }
        SsEnd();
    }
    fade = frame & 0xFF;
    if (fade == 0) {
        SetDispMask(0);
    }
    height = 0xF0;
    SetDefDrawEnv(D_800BDD4C, 0, 0, 0x140, height);
    SetDefDispEnv(D_800BDE04, 0x140, 0, 0x140, height);
    SetDefDrawEnv(D_800BDDA8, 0x140, 0, 0x140, height);
    SetDefDispEnv(D_800BDE18, 0, 0, 0x140, height);
    envByte = D_800BDD64;
    D_800BDD62[0] = 0;
    D_800BDDBE[0] = 0;
    D_800BDDC0[0] = 1;
    envByte[0] = 1;
    D_800BDD65[0] = 0;
    D_800BDD66[0] = 0;
    D_800BDD67[0] = 0;
    D_800BDDC1[0] = 0;
    D_800BDDC2[0] = 0;
    D_800BDDC3[0] = 0;
    PutDrawEnv((DRAWENV *)(envByte + 0x44));
    PutDispEnv(D_800BDE18put);
    fade = -(fade != 0) & 0x1F;
    dst = (u16 *)texBuf;
    src = D_800A35F0;
    end = (u8 *)dst + 0x257FE;
    do {
        bits = *src;
        pixel = 0;
        shift = 0;
        j = 0;
        do {
            value = (u8)(fade + (bits & 0x1F));
            if (value >= 0x20) {
                value = 0x1F;
            }
            pixel |= value << shift;
            shift += 5;
            j++;
            bits >>= 5;
        } while ((j & 0xFF) < 3);
        *dst = pixel;
        dst = (u16 *)((u8 *)dst + 2);
        src = (u16 *)((u8 *)src + 2);
    } while (end >= (u8 *)dst);
    LoadImage(D_800A3710, (u_long *)texBuf);
    frame = 1;
    gCdAudioEnabled[0] = frame;
    CdPlayAudioTrack(5);
    SsSetMVol(0x7F, 0x7F);
    D_800A3724 = frame;
    SetDispMask(1);
    done = 0;
    toggle = 0;
    prevPads = 0;
    D_800A305C = 0;
    frame = -(gSessionTypeAbsolute[0] == -2) & 0xB4;
    do {
        RandomScaledGetScene();
        bank = D_800A305C == 0;
        ot = gOrderingTables + (bank << 12);
        D_800A305C = bank;
        gOrderingTableBankAbsolute[0] = bank;
        gOrderingTablestore[0] = (s32)ot;
        ClearOTagR((OT_TYPE *)ot, 4);
        if ((fade << 24) != 0) {
            fade = fade - 1;
            src = D_800A35F0;
            dst = (u16 *)texBuf;
            end = (u8 *)dst + 0x257FE;
            do {
                bits = *src;
                pixel = 0;
                shift = 0;
                j = 0;
                do {
                    value = (u8)(fade + (bits & 0x1F));
                    if (value >= 0x20) {
                        value = 0x1F;
                    }
                    pixel |= value << shift;
                    shift += 5;
                    j++;
                    bits >>= 5;
                } while ((j & 0xFF) < 3);
                *dst = pixel;
                dst = (u16 *)((u8 *)dst + 2);
                src = (u16 *)((u8 *)src + 2);
            } while (end >= (u8 *)dst);
        } else {
            frame++;
            if (frame >= 0xB5) {
                counter = D_800A3724 - 1;
                D_800A3724 = counter;
                if (counter == 0) {
                    D_800A3724 = 0x3C;
                    toggle = toggle ^ 1;
                }
                if (toggle != 0) {
                    AddPrim((void *)gOrderingTable[0], D_800A34FC);
                }
            }
        }
        DrawSync(0);
        VSync(0);
        PutDispEnv(&D_800BDE04[D_800A305C]);
        PutDrawEnv(&D_800BDD4C[D_800A305C]);
        D_800A3710Small.x = -(D_800A305C != 0) & 0x140;
        LoadImage(D_800A3710, (u_long *)texBuf);
        if ((fade << 24) != 0) {
            continue;
        }
        DrawOTag((OT_TYPE *)(gOrderingTabledraw[0] + 0xC));
        PadResetAndInitializeBuffersScene(0);
        pads = PadGetButtons(0);
        if (frame >= 0xB5) {
            if (gSessionTypeAbsolute[0] == -2) {
                mask = ~prevPads & 0x9F0;
            } else {
                mask = ~prevPads & 0x800;
            }
            if ((pads & mask) != 0) {
                done = 1;
            }
            if ((done & 0xFF) != 0) {
                if (D_800A3A48 != 0xFF) {
                    gScreenStateSmall = D_800A3A48;
                    D_800A3A48 = 0xFF;
                } else {
                    gScreenStateSmall = 0;
                }
            } else {
                if (frame >= 0x709) {
                    done = 1;
                    gScreenStateSmall = 0xFE;
                }
            }
        }
        prevPads = pads;
    } while ((done & 0xFF) == 0);
    if (gScreenStateSmall == 0xFE) {
        func_8005957C();
    } else if (gScreenStateSmall == 0) {
        D_800A3950 = 0xF9;
    }
    rect.x = 0x200;
    rect.y = 0x124;
    rect.w = 0x60;
    rect.h = 0x15;
    moveX = 0x73;
    if (D_800A305C == 0) {
        moveX = 0x1B3;
    }
    MoveImage(&rect, moveX, 0xBC);
    DrawSync(0);
    HeapFree(fileBuf);
    D_800A3638 = 0;
    HeapFree(texBuf);
    if (gScreenStateSmall == 0xFE) {
        MenuStartVBlankEvent();
    }
    HeapResetInitFlag();
}

#ifdef NON_MATCHING
/*
 * w8g: full body reached an exact unit diff EXCEPT data labels: any
 * active C here (even size-identical to the stub) shifts the sdata
 * labels -0xC and a shorter body shifts them differently (see
 * matching.md). text side (all verified, keep these when retrying):
 * - gSessionType=-1 / D_800A2EA8=3 via gSessionTypeAbsolute[0] / [-2]
 * - D_800A2CE0 twice via DISTINCT aliases (A2E24[-0x151] first,
 *   A2EB0Absolute[-0x74] in the arm) or gcc hoists the address into s0
 * - store the arm call result DIRECTLY (`D[...] = RandomScaledGet(0x10);`)
 *   or gcc keeps the old value alive in v1 (`move v1,v0`, bne flipped)
 * - tail: seed=gPlayerDriver (lbu gp), A2EA4/A2EDC/A2EE0 as u8 arrays
 *   (lui), A38F0/A3A60 as u8 arrays (lui), A3064/A3065/A3718 scalar
 *   (gp); u8 arrays DO get lui here, do not cast them (cast form
 *   segfaults cc1 at this TU position)
 * - CAST-FORM STORES `((u8 *)D_800A2EC8Absolute)[n] = v;` DETONATE cc1
 *   here (0-symbol object, exit 0). Direct u8[] externs are fine.
 */
extern u8 D_800A38F0[];
extern u8 D_800A3A60[];
extern u8 D_800A3064;
extern u8 D_800A3065;
extern u8 gPlayerDriver;
void func_8005957C(void) {
    s32 value;
    u8 seed;

    gSessionTypeAbsolute[0] = -1;
    D_800A2EA8Absolute[0] = 3;
    value = RandomScaledGet(0x11);
    D_800A2E24Absolute[-0x151] = value;
    if (value == 0x10) {
        D_800A2CE0Absolute4[0] = RandomScaledGet(0x10);
    }
    seed = gPlayerDriver;
    gSplitScreenMode[0] = 0;
    D_800A2EDC[0] = 0;
    D_800A2EE0[0] = 1;
    D_800A38F0[0] = 0;
    D_800A3A60[0] = 0;
    D_800A3064 = 0;
    D_800A3065 = 0;
    D_800A3718 = seed;
}
#endif
extern u32 gSplitScreenModeNM[] asm("gSplitScreenMode.NON_MATCHING");
extern u8 D_800A2EDCNM[] asm("D_800A2EDC.NON_MATCHING");
extern u8 D_800A2EE0NM[] asm("D_800A2EE0.NON_MATCHING");
extern u8 D_800A38F0NM[] asm("D_800A38F0.NON_MATCHING");
extern u8 D_800A3A60NM[] asm("D_800A3A60.NON_MATCHING");
extern u8 D_800A3064NM asm("D_800A3064.NON_MATCHING");
extern u8 D_800A3065NM asm("D_800A3065.NON_MATCHING");
extern u8 D_800A3718NM asm("D_800A3718.NON_MATCHING");
extern u8 gPlayerDriverNM asm("gPlayerDriver.NON_MATCHING");
void func_8005957C(void) {
    s32 value;
    u8 seed;

    gSessionTypeAbsolute[0] = -1;
    D_800A2EA8Absolute[0] = 3;
    value = RandomScaledGet(0x11);
    D_800A2CE0Absolute3[0] = value;
    if (value == 0x10) {
        D_800A2CE0Absolute4[0] = RandomScaledGet(0x10);
    }
    seed = gPlayerDriverNM;
    gSplitScreenModeNM[0] = 0;
    D_800A2EDCNM[0] = 0;
    D_800A2EE0NM[0] = 1;
    D_800A38F0NM[0] = 0;
    D_800A3A60NM[0] = 0;
    D_800A3064NM = 0;
    D_800A3065NM = 0;
    D_800A3718NM = seed;
}

s32 ColorPack555(s32 red, s32 green, u8 blue) {
    s16 color;
    color =
        (blue >> 3) | (((red << 7) & 0x7C00) | ((green << 2) & 0x3E0)) | -32768;
    return color;
}

#ifdef NON_MATCHING
/* Wall: prologue and loop body match. Retail batches the five pixel
 * constants into five registers (v0,v1,a1,a2,a3) before storing; ours
 * materializes each constant just before its store (single recycled
 * register). Loop uses pointer=v1/counter=v0; retail has them swapped.
 * Permuter candidate. */
void GraphicsLoadPaletteRow(void) {
    RECT rect;
    s16 *pixels;
    s32 i;
    s16 *p;

    rect.x = 0x100;
    rect.y = 0x1FF;
    rect.h = 1;
    rect.w = 0x10;
    pixels = HeapAlloc(0x20);
    p = pixels + 8;
    for (i = 8; i >= 0; i--) {
        *p = -0x3DF0;
        p--;
    }
    pixels[11] = -0x62D7;
    pixels[9] = -0x5674;
    pixels[10] = -0x5A95;
    pixels[12] = -0x6AF8;
    pixels[13] = -0x733A;
    pixels[14] = 0;
    pixels[15] = 0;
    LoadImage(&rect, (u_long *)pixels);
    HeapFree(pixels);
}
#else
void GraphicsLoadPaletteRow(void) {
    RECT rect;
    s16 *pixels;
    s32 i;
    s16 fill;
    s16 *p;
    s16 c1, c2, c3, c4, c5;

    rect.x = 0x100;
    rect.y = 0x1FF;
    rect.h = 1;
    rect.w = 0x10;
    pixels = HeapAlloc(0x20);
    fill = -0x3DF0;
    i = 8;
    p = pixels + 8;
    do {
        do {
            *p = fill;
            p--;
            i--;
        } while (i >= 0);
        c1 = -0x5674;
        c2 = -0x5A95;
        c3 = -0x62D7;
        c4 = -0x6AF8;
    } while (0);
    c5 = -0x733A;
    pixels[9] = c1;
    pixels[10] = c2;
    pixels[11] = c3;
    pixels[12] = c4;
    pixels[13] = c5;
    pixels[14] = 0;
    pixels[15] = 0;
    LoadImage(&rect, (u_long *)pixels);
    HeapFree(pixels);
}

#endif

void CdEnablePlaybackAndSetVolume(void) {
    gCdAudioEnabledAbsolute[0] = 1;
    CdPlayAudioTrack(3);
    CdSetMixVolume(gCdVolume);
}

void CdSetMixVolume(s32 arg) {
    CdlATV vol;
    u8 value;
    value = ((arg & 0xFF) * 125) / 100;
    vol.val0 = value;
    vol.val1 = value;
    vol.val2 = value;
    vol.val3 = value;
    CdMix(&vol);
}

/* The head of the file func_8005978C loads. A TIM image starts timOffset
 * bytes in. */
typedef struct SceneFileHeader {
    u32 unk0;
    u8 unk4[12];   /* 0x04: D_800A381C points here */
    s32 timOffset; /* 0x10 */
} SceneFileHeader;

extern s32 FileSeekArgs(void *, s32, s32);
extern void FileSeekArgsV(void *, s32, s32);
extern void FileCloseArgs(s32);
asm(".globl FileSeekArgs\nFileSeekArgs = FileSeek");
asm(".globl FileSeekArgsV\nFileSeekArgsV = FileSeek");
asm(".globl FileCloseArgs\nFileCloseArgs = FileClose");
void func_8005978C(void) {
    extern void *FileOpen(s32, void *);
    extern void FileRead(s32, s32, s32, s32);
    extern s32 gSceneFileMode[];
    DISPENV env;
    void *sector;
    s32 size;
    s32 buf;
    s32 next;
    s32 tmp;

    sector = FileOpen(0, gSceneFileMode);
    size = (FileSeekArgs(sector, 0, 2) + 0x7FF) >> 11 << 11;
    do {
        tmp = (s32)HeapAlloc(size);
        FileSeekArgsV(sector, 0, 0);
    } while (0);
    buf = tmp;
    FileRead(buf, 1, size, (s32)sector);
    FileCloseArgs((s32)sector);
    next = ((SceneFileHeader *)buf)->timOffset;
    D_800A381C = buf + 4;
    D_800A3638 = buf;
    buf += next;
    gMenuBackground = (void *)buf;
    TextureLoadTim((void *)buf);
    DrawSync(0);
    SetDefDispEnv(&env, 0x140, 0, 0x140, 0xF0);
    PutDispEnv(&env);
    SetDispMask(1);
}
