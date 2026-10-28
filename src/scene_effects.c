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
extern s32 gOrderingTableAbsolute8[];
extern s32 gMenuObjectPoolAbsolute2[];
extern u8 gCardMenuMessageAbsolute2[];
extern s32 D_800A2EB4Absolute2[];
extern s32 gOrderingTableBankAbsolute3[];
extern s32 gOrderingTableBankAbsolute4[];
extern s32 gOrderingTableAbsolute3[];
extern s32 gOrderingTableAbsolute4[];
extern s32 gOrderingTableAbsolute5[];
extern s32 gOrderingTableAbsolute6[];
extern s32 D_800A2CE0Absolute3[];
extern s32 D_800A2CE0Absolute4[];
extern u8 gCardMenuMessageAbsoluteU8[] asm("gCardMenuMessageAbsolute");
extern s32 D_800A2EA8Absolute[];

extern u8 D_800A2F58Absolute[];
extern u8 gMenuObjectPoolCountAbsolute[];

extern void SetPolyFT4(POLY_FT4 *);
extern u8 *D_800A3428View asm("D_800A3428");
void HudDrawTime(s32 time, s16 x, s16 y, s8 color, u8 mode);
void MenuLoadResources(void);
void GraphicsInitDoubleBufferSwapped(void);
void TextureLoadTim(void *timImage);

extern s32 strlen(char *);
extern u8 gSoundEffectsEnabledw15[] asm("gSoundEffectsEnabled.NON_MATCHING");

extern s32 gOrderingTable[];
extern s32 D_800A2EC0nm[] asm("D_800A2EC0.NON_MATCHING");
extern s32 gOrderingTablenm[] asm("gOrderingTable.NON_MATCHING");
extern s32 gReplayIndexAbsolute[];
extern s32 *gSinTableAbsolute[];
extern s32 D_800A397C[];
extern u8 D_800A3680[];
extern void func_80025730(Car *);
extern Car *gPlayerCar[];
s32 func_8003702C(Car *, Car *);
extern void HeapFree(void *ptr);
extern s32 D_800A37B4Absolute[];
extern s32 D_800A359C[];
extern void SetPolyF4(u8 *prim);
extern Car *D_800A35E0[];
extern void CarInitDefaults(Car *car);
extern Car *gCarListnm[] asm("gCarList.NON_MATCHING");
extern void FileRead(s32 buffer, s32 size, s32 count, s32 handle);
extern u8 gCdAudioEnabledAbsolute[];
extern void SoundPlaySlot(s8, s8);
s32 VSync(s32);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern u8 D_800A2EE0[];
void func_80018768(void *arg0, s32 x, s32 y, s32 scale);
void func_80018B18(s32 value, s32 x, s32 y, s32 scale);
void GraphicsDrawRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5,
                      u8 arg6, s32 arg7);
void func_8001EEC4(Car *arg0);
void func_80028FCC(Car *arg0);
void ObjectSetModelDataVariant(Car *object, s32 index);
void GraphicsAddTaggedPrimitive(u32 *orderingTable, u32 *primitive, u32 tag);
s32 func_80037204(Car *obj);
void func_8003A880(Car *car);
void func_8003AA20(Car *car);
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
extern SVECTOR D_800992E4[];
extern SVECTOR D_800992EC[];
extern SVECTOR D_800992F4[];
extern void SetPolyFT3(POLY_FT3 *prim);

extern s32 *gCosTableAbsolute[];
#ifdef NATIVE
void func_80044BCC(s32 arg0) {
    s32 v;
    s32 typeIndex;
    POLY_FT3 *prim;
    s32 otz;
    u32 *ot;

    ot = (u32 *)(gOrderingTable[0] + 0x20);
    prim = (POLY_FT3 *)((u8 *)gPrimitiveCursor[0]);
    typeIndex = (s8)gCarListNM[0][arg0].driver;
    gte_ldv3(D_800992E4, D_800992EC, D_800992F4);
    gte_rtpt();
    SetPolyFT3(prim);
    SetShadeTex(prim, 1);
    prim->clut = GetClut((typeIndex % 16) * 16 + 0x300, 0x3F - typeIndex / 16);
    if (typeIndex < 12) {
        prim->tpage = GetTPage(0, 0, (typeIndex % 4) * 64 + 0x300, 0);
        v = typeIndex / 4;
        v = v * 64 + 0x40;
    } else {
        prim->tpage = GetTPage(0, 0, (typeIndex % 4) * 64 + 0x300, 0x100);
        v = ((typeIndex - 12) / 4) * 64;
    }
    prim->u1 = 0x20;
    prim->u0 = 0;
    prim->v0 = v;
    prim->v1 = v;
    prim->u2 = 0;
    prim->v2 = v + 0x20;
    gte_avsz3();
    /* mfc2 otz, $7: the average Z from avsz3. */
    otz = PortGteRead(7);
    gte_stsxy3((u8 *)prim + 8, (u8 *)prim + 0x10, (u8 *)prim + 0x18);
    GraphicsAddTaggedPrimitive(&ot[otz >> 4], (u32 *)prim, 0x07000000);
    prim++;
    gPrimitiveCursor[0] = (u32)prim;
}
#else
void func_80044BCC(s32 arg0) {
    s32 v;
    s32 typeIndex;
    POLY_FT3 *prim;
    s32 otz;
    u32 *ot;

    ot = (u32 *)(gOrderingTable[0] + 0x20);
    prim = (POLY_FT3 *)((u8 *)gPrimitiveCursor[0]);
    typeIndex = (s8)gCarListNM[0][arg0].driver;
    gte_ldv3(D_800992E4, D_800992EC, D_800992F4);
    gte_rtpt();
    SetPolyFT3(prim);
    SetShadeTex(prim, 1);
    prim->clut = GetClut((typeIndex % 16) * 16 + 0x300, 0x3F - typeIndex / 16);
    if (typeIndex < 12) {
        prim->tpage = GetTPage(0, 0, (typeIndex % 4) * 64 + 0x300, 0);
        v = typeIndex / 4;
        v = v * 64 + 0x40;
    } else {
        prim->tpage = GetTPage(0, 0, (typeIndex % 4) * 64 + 0x300, 0x100);
        v = ((typeIndex - 12) / 4) * 64;
    }
    prim->u1 = 0x20;
    prim->u0 = 0;
    prim->v0 = v;
    prim->v1 = v;
    prim->u2 = 0;
    prim->v2 = v + 0x20;
    gte_avsz3();
    asm volatile("mfc2 %0, $7\n\tnop" : "=r"(otz) : "0"(otz));
    gte_stsxy3((u8 *)prim + 8, (u8 *)prim + 0x10, (u8 *)prim + 0x18);
    GraphicsAddTaggedPrimitive(&ot[otz >> 4], (u32 *)prim, 0x07000000);
    prim++;
    gPrimitiveCursor[0] = (u32)prim;
}
#endif

extern void SetLineF4(u8 *prim);
extern void SetLineF2(u8 *prim);

#ifdef NATIVE
void func_80044DC4(u8 *arg0, s32 arg1, u8 *arg2) {
    register u8 *prim;
    register u8 *walker;
    register u8 *pe;
    s32 count;
    u8 *rgb;
    u8 g;
    u8 b;
    register u8 rv;
    register u8 rtmp;
    register s32 obt;
    register u32 *a0arg;
    register u32 *a1arg;
    u32 a2arg;
    u16 xy0;
    u16 xy1;
    u16 xy2;
    u16 xy3;
    u8 btmp;
    register s32 gte;
    register s32 otEntry;
    volatile struct {
        u8 r;
        u8 pad1[7];
        s32 otBase;
        u8 pad2[4];
    } st;
#define r st.r
#define otBase st.otBase
    register s32 v0_;
    register s32 v1_;
    register s32 v2_;
    register s32 w3;
    register s32 masked;

    otBase = (s32)gOrderingTable[0] + 0x20;
    prim = (u8 *)gPrimitiveCursor[0];
    rgb = arg2;
    count = arg1;
    rtmp = rgb[0];
    r = rtmp;
    g = rgb[1];
    b = rgb[2];
    if (count > 0) {
        walker = arg0 + 0x24;
        pe = prim + 0xE;
        do {
            v0_ = *(s32 *)&((Face *)(walker - 0x24))->vertex[0];
            v1_ = *(s32 *)&((Face *)(walker - 0x24))->vertex[1];
            v2_ = *(s32 *)&((Face *)(walker - 0x24))->vertex[2];
            gte_ldv3(v0_, v1_, v2_);
            gte_rtpt();
            SetLineF4(prim);
            gte_cfc2(gte, 31);
            masked = gte & 0x66000;
            if (masked != 0) {
                goto next;
            }
            gte_nclip();
            rv = r;
            ((LINE_F4 *)(pe - 0xE))->g0 = g;
            ((LINE_F4 *)(pe - 0xE))->b0 = b;
            ((LINE_F4 *)(pe - 0xE))->r0 = rv;
            gte_mfc2(gte, 24);
            if (D_800A2DE0[0] != 0) {
                if (gte < 0) {
                    goto next;
                }
            } else {
                if (gte > 0) {
                    goto next;
                }
            }
            gte_avsz3();
            gte_mfc2(gte, 7);
            gte += (s32)(s8) * (walker - 0x23) * 4;
            gte_stsxy3(prim + 8, prim + 0xC, prim + 0x10);
            w3 = *(s32 *)(walker);
            gte_ldv0(w3);
            gte_rtps();
            gte_stsxy(prim + 0x14);
            otEntry = gte >> 4;
            otEntry = otEntry << 2;
            obt = otBase;
            otEntry = obt + otEntry;
            GraphicsAddTaggedPrimitive((u32 *)otEntry, (u32 *)prim, 0x06000000);
            prim += 0x1C;
            pe += 0x1C;
            SetLineF2(prim);
            xy0 = ((LINE_F4 *)(pe - 0x2A))->y0;
            xy1 = ((LINE_F4 *)(pe - 0x2A))->x3;
            xy2 = ((LINE_F4 *)(pe - 0x2A))->y3;
            ((LINE_F2 *)(pe - 0xE))->r0 = rgb[0];
            xy3 = ((LINE_F4 *)(pe - 0x2A))->x0;
            a0arg = (u32 *)otEntry;
            ((LINE_F2 *)(pe - 0xE))->g0 = rgb[1];
            btmp = rgb[2];
            xy3 = ((LINE_F4 *)(pe - 0x2A))->x0;
            a1arg = (u32 *)prim;
            /* lui a2arg, 0x300 */
            a2arg = 0x3000000;
            prim += 0x10;
            ((LINE_F2 *)(pe - 0xE))->y0 = xy0;
            ((LINE_F2 *)(pe - 0xE))->x1 = xy1;
            ((LINE_F2 *)(pe - 0xE))->y1 = xy2;
            ((LINE_F2 *)(pe - 0xE))->x0 = xy3;
            ((LINE_F2 *)(pe - 0xE))->b0 = btmp;
            GraphicsAddTaggedPrimitive(a0arg, a1arg, a2arg);
            pe += 0x10;
        next:
            walker += 0x2C;
        } while (--count > 0);
    }
    gPrimitiveCursor[0] = (u32)prim;
}
#else
void func_80044DC4(u8 *arg0, s32 arg1, u8 *arg2) {
    register u8 *prim asm("$18");
    register u8 *walker asm("$20");
    register u8 *pe asm("$17");
    s32 count;
    u8 *rgb;
    u8 g;
    u8 b;
    register u8 rv asm("$11");
    register u8 rtmp asm("$10");
    register s32 obt asm("$10");
    register u32 *a0arg asm("$4");
    register u32 *a1arg asm("$5");
    u32 a2arg;
    u16 xy0;
    u16 xy1;
    u16 xy2;
    u16 xy3;
    u8 btmp;
    register s32 gte asm("$19");
    register s32 otEntry asm("$16");
    volatile struct {
        u8 r;
        u8 pad1[7];
        s32 otBase;
        u8 pad2[4];
    } st;
#define r st.r
#define otBase st.otBase
    register s32 v0_ asm("$11");
    register s32 v1_ asm("$12");
    register s32 v2_ asm("$10");
    register s32 w3 asm("$12");
    register s32 masked asm("$2");

    otBase = (s32)gOrderingTable[0] + 0x20;
    prim = (u8 *)gPrimitiveCursor[0];
    rgb = arg2;
    count = arg1;
    rtmp = rgb[0];
    r = rtmp;
    g = rgb[1];
    b = rgb[2];
    if (count > 0) {
        walker = arg0 + 0x24;
        pe = prim + 0xE;
        do {
            v0_ = *(s32 *)&((Face *)(walker - 0x24))->vertex[0];
            v1_ = *(s32 *)&((Face *)(walker - 0x24))->vertex[1];
            v2_ = *(s32 *)&((Face *)(walker - 0x24))->vertex[2];
            gte_ldv3(v0_, v1_, v2_);
            gte_rtpt();
            SetLineF4(prim);
            gte_cfc2(gte, 31);
            masked = gte & 0x66000;
            if (masked != 0) {
                goto next;
            }
            gte_nclip();
            rv = r;
            ((LINE_F4 *)(pe - 0xE))->g0 = g;
            ((LINE_F4 *)(pe - 0xE))->b0 = b;
            ((LINE_F4 *)(pe - 0xE))->r0 = rv;
            gte_mfc2(gte, 24);
            if (D_800A2DE0[0] != 0) {
                if (gte < 0) {
                    goto next;
                }
            } else {
                if (gte > 0) {
                    goto next;
                }
            }
            gte_avsz3();
            gte_mfc2(gte, 7);
            gte += (s32)(s8) * (walker - 0x23) * 4;
            gte_stsxy3(prim + 8, prim + 0xC, prim + 0x10);
            w3 = *(s32 *)(walker);
            gte_ldv0(w3);
            gte_rtps();
            gte_stsxy(prim + 0x14);
            otEntry = gte >> 4;
            otEntry = otEntry << 2;
            obt = otBase;
            otEntry = obt + otEntry;
            GraphicsAddTaggedPrimitive((u32 *)otEntry, (u32 *)prim, 0x06000000);
            prim += 0x1C;
            pe += 0x1C;
            SetLineF2(prim);
            xy0 = ((LINE_F4 *)(pe - 0x2A))->y0;
            xy1 = ((LINE_F4 *)(pe - 0x2A))->x3;
            xy2 = ((LINE_F4 *)(pe - 0x2A))->y3;
            ((LINE_F2 *)(pe - 0xE))->r0 = rgb[0];
            xy3 = ((LINE_F4 *)(pe - 0x2A))->x0;
            a0arg = (u32 *)otEntry;
            ((LINE_F2 *)(pe - 0xE))->g0 = rgb[1];
            btmp = rgb[2];
            xy3 = ((LINE_F4 *)(pe - 0x2A))->x0;
            a1arg = (u32 *)prim;
            asm volatile("lui %0, 0x300" : "=r"(a2arg));
            prim += 0x10;
            ((LINE_F2 *)(pe - 0xE))->y0 = xy0;
            ((LINE_F2 *)(pe - 0xE))->x1 = xy1;
            ((LINE_F2 *)(pe - 0xE))->y1 = xy2;
            ((LINE_F2 *)(pe - 0xE))->x0 = xy3;
            ((LINE_F2 *)(pe - 0xE))->b0 = btmp;
            GraphicsAddTaggedPrimitive(a0arg, a1arg, a2arg);
            pe += 0x10;
        next:
            walker += 0x2C;
        } while (--count > 0);
    }
    gPrimitiveCursor[0] = (u32)prim;
}
#endif

extern s32 D_800A33F0;
extern s32 D_800A33F4;
extern s8 D_800A33F8;
extern s32 D_800A3400;
extern s32 D_800A3404;
extern s32 D_80098184[];
extern s32 D_80098134nm[] asm("D_80098134.NON_MATCHING");
extern s32 D_8009813Cnm[] asm("D_8009813C.NON_MATCHING");
extern u8 D_800A3880nm[] asm("D_800A3880.NON_MATCHING");

void SoundRunSlotEnvelope(s32 arg0, s32 arg1) {
    s32 i;
    s32 off;
    s32 *entry;
    s32 temp;
    s32 vol;
    s32 cur;
    s32 newv;

    i = 0;
    switch (arg0) {
    case 0:
        D_800A3404 = 0;
        D_800A3400 = 0;
        D_800A33F4 = 0;
        D_800A33F0 = 0;
        *(volatile s32 *)&D_800A33F8 = 0x20;
        SoundPlaySlot((s8)arg1, -(D_800A3880nm[0] != 0) & 7);
        SoundSetSlotVolume((s8)arg1, 0x7F, 0x7F);
        return;
    case 1:
        if (D_800A3404 >= D_80098184[0]) {
            D_800A3404 = 0;
            D_800A3400 = 0;
            D_800A33F0 = 0;
        } else {
            D_800A3404 = D_800A3404 + ((D_80098134nm[D_800A33F0 * 6] * 7) >> 2);
        }
        if (D_800A33F4 != 0) {
            D_800A33F4 = D_800A33F4 - 1;
        }
        off = i * 0x18;
        while (D_800A3404 > *(s32 *)((s8 *)D_8009813Cnm + off)) {
            i = i + 1;
            off = off + 0x18;
        }
        entry = (s32 *)((s8 *)D_80098134nm + i * 0x18);
        temp =
            MathFixedDivide(entry[4] - entry[3], (entry[2] - entry[1]) >> 16);
        D_800A3400 =
            entry[3] + (MathMultiplyFixed16(temp, D_800A3404 - entry[1]) >> 16);
        if (D_800A33F0 < i) {
            D_800A33F4 = 0x14;
        }
        D_800A33F0 = i;
        if (D_800A33F4 < 0x12) {
            vol = D_800A3400 / 110;
        } else {
            vol = 0x6E;
        }
        cur = *(volatile s32 *)&D_800A33F8;
        if (cur + 7 < vol) {
            *(volatile s32 *)&D_800A33F8 = cur + 7;
            newv = cur + 7;
        } else if (vol < cur - 5) {
            *(volatile s32 *)&D_800A33F8 = cur - 5;
            newv = cur - 5;
        } else {
            newv = vol;
        }
        *(volatile s32 *)&D_800A33F8 = newv;
        if (newv >= 0x80) {
            *(volatile s32 *)&D_800A33F8 = 0x7F;
        }
        func_8003FA84((s8)arg1, D_800A33F8);
        return;
    case 2:
        SoundStopSlot((s8)arg1);
        return;
    }
}

extern s32 D_800A3960gp;
extern u8 D_800A35F8gp;
extern u8 D_800A3A60gp;
asm(".globl D_800A3960gp\nD_800A3960gp = gCrashCar");
asm(".globl D_800A35F8gp\nD_800A35F8gp = D_800A35F8");
asm(".globl D_800A3A60gp\nD_800A3A60gp = D_800A3A60");

void func_80045288(void) {
    extern s32 D_800A3598[];
    extern u8 *D_800A2FCC;
    extern u8 D_800A3424;
    extern u8 D_800A3590;
    extern u8 D_800A34B0;
    extern u8 gTextColor;
    extern u8 D_800A34AC;
    extern s16 D_800A383C;
    extern s16 D_800A383E[];
    extern s16 D_800A3840;
    extern s16 D_800A3842[];
    extern s16 D_800A3844;
    extern s16 D_800A3846[];
    extern s32 D_800A3428;
    extern u8 D_800A39D4;
    extern u8 D_800A3688;
    extern u32 D_800A34E0;
    extern u8 D_800991E8[];
    void func_80052E18(void);
    void SceneInitProjectiles(void);
    void HudInitPrims(void);
    void HudInitLapSplits(void);
    void SceneInitHandModel(void);
    void func_8004F880(void);
    void HudInitRacePrims(void);
    void SceneCreateSceneryCar(void);
    void SceneInitProjectilePrimitives(void);
    void HudInitFlagOverlay(void);
    void GraphicsInitializeTexturedQuad(void);
    void RaceInitCrashCandidates(void);
    Car *obj;
    u8 *v;
    s32 x;
    s32 flag;
    u8 *row;
    u8 *p;
    s8 i;
    s8 j;
    s32 c;
    s32 flag2;
    s32 w;

    flag = 1;
    if (gSplitScreenMode[0] != 0) {
        flag = 2;
    }
    obj = gPlayerCar[0];
    v = D_800A2FCC;
    x = *(s32 *)&obj->next;
    D_800A3424 = flag;
    D_800A3960gp = 0;
    D_800A3590 = 0;
    D_800A34B0 = 0;
    gTextColor = 0;
    do {
    } while (0);
    D_800A35F8gp = 1;
    D_800A34AC = 60;
    D_800A383E[0] = 1000;
    D_800A383C = 1000;
    D_800A3842[0] = 500;
    D_800A3840 = 500;
    D_800A3846[0] = 75;
    D_800A3844 = 75;
    D_800A3428 = x;
    if (v != 0) {
        for (i = 0; i < 24; i++) {
            j = 0;
            row = D_800991E8 + i * 3;
            for (; j < 3; j++) {
                p = row + j;
                c = *p + 0x30;
                if (c > 0xFF) {
                    c = 0xFF;
                }
                *p = c;
            }
        }
        D_800A2FCC = 0;
    }
    func_80052E18();
    if (D_800A3A60gp != 0) {
        SceneInitProjectiles();
    }
    HudInitPrims();
    HudInitLapSplits();
    SceneInitHandModel();
    func_8004F880();
    HudInitRacePrims();
    SceneCreateSceneryCar();
    SceneInitProjectilePrimitives();
    HudInitFlagOverlay();
    GraphicsInitializeTexturedQuad();
    RaceInitCrashCandidates();
    flag2 = 0;
    if (D_800A3598[0] != 1) {
        goto set_one;
    }
    if (D_800A2CE0[0] == 3) {
        goto set_one;
    }
    goto flag_done;
set_one:
    flag2 = 1;
flag_done:
    w = gSessionTypeAbsolute[0];
    D_800A39D4 = flag2;
    if (w >= 0) {
        if (w == 1) {
            goto hit;
        }
    } else {
        w = -w;
        if (w == 1) {
            D_800A3688 = 0;
        }
    }
    goto fin;
hit:
    D_800A3688 = 0;
fin:
    D_800A34E0 = 0x7FFFFFFF;
}

extern s32 D_800A2F84[];

/* One track surface quad. The vertices hold ground-plane x in vx and z in
 * vy. */
/* One 0x90-byte entry of the array at gTrackSections. */

/* Sorts the quads of one track section across the track and returns +1 or
 * -1 for the side of the dividing line between the middle two that the car
 * is on. Returns 0 if the section doesn't hold four quads. */
s32 CarGetTrackSide(Car *car, s16 offset) {
    s32 lateral[4];
    Face *quads[4];
    s32 center[4][2];
    s32 origin[2];
    TrackSection *entry;
    Face *node;
    s8 i, j;
    s32 tmp;
    s32 cosValue, sinValue;
    s32 dot;
    s32 result;

    entry = (TrackSection *)((u8 *)gTrackSections[0] +
                             ((car->segment + offset + gTrackSectionCount[0]) %
                              gTrackSectionCount[0]) *
                                 0x90);
    i = 0;
    for (node = entry->firstQuad; node != NULL; node = node->next) {
        quads[i] = node;
        center[i][0] = node->vertex[0]->vx + node->vertex[1]->vx +
                       node->vertex[2]->vx + node->vertex[3]->vx +
                       D_800AE844[0] * 4;
        center[i][1] = node->vertex[0]->vy + node->vertex[1]->vy +
                       node->vertex[2]->vy + node->vertex[3]->vy +
                       D_800AE844[1] * 4;
        i++;
    }
    if (i != 4) {
        return 0;
    }
    origin[0] = entry->x;
    origin[1] = entry->z;
    i = 0;
    cosValue = gCosTableAbsolute[0][0x3FF - entry->angle];
    sinValue = gSinTableAbsolute[0][0x3FF - entry->angle];
    do {
        lateral[i] =
            (MathMultiplyFixed16(sinValue, (center[i][0] - origin[0]) << 16) +
             MathMultiplyFixed16(cosValue, (center[i][1] - origin[1]) << 16)) >>
            16;
        i++;
    } while (i < 4);
    /* node and tmp double as the swap temporaries. */
    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            if (lateral[j] < lateral[i]) {
                node = quads[i];
                quads[i] = quads[j];
                quads[j] = node;
                tmp = lateral[i];
                lateral[i] = lateral[j];
                lateral[j] = tmp;
                tmp = center[i][0];
                center[i][0] = center[j][0];
                center[j][0] = tmp;
                tmp = center[i][1];
                center[i][1] = center[j][1];
                center[j][1] = tmp;
            }
        }
    }
    tmp = 0x3FF - ((quads[1]->angle + quads[2]->angle) / 2);
    dot = (MathMultiplyFixed16(gSinTableAbsolute[0][tmp],
                               (car->pos.x - center[1][0]) << 16) +
           MathMultiplyFixed16(gCosTableAbsolute[0][tmp],
                               (car->pos.y - center[1][1]) << 16)) >>
          16;
    if (D_800A2F84[0] != 0) {
        result = -1;
        if (dot < 0) {
            result = 1;
        }
    } else {
        result = -1;
        if (dot > 0) {
            result = 1;
        }
    }
    return result;
}

typedef struct {
    u32 tag;
    u32 color;
    u32 uv[4];
    SVECTOR *vertex[4];
    u32 unk28;
} ProjectileQuad;

typedef struct {
    u8 life;
    u8 pad1[3];
    Vec3 position;
    ProjectileQuad quad;
    Vec3 forward;
    Vec3 right;
    Vec3 up;
    SVECTOR vertex[4];
} Projectile;

extern u8 D_800A2FC8;
extern u8 D_800A372C;
extern u8 gProjectileMode[] asm("D_800A2F58");
extern s8 gProjectileWriteIndex[] asm("D_800A342C");
extern s32 gProjectilePools[] asm("D_800A3430");
extern Car *gProjectileCars[] asm("gCarList");
extern s32 gProjectileOriginX asm("D_800AE844");
extern s32 gProjectileOriginY asm("D_800AE848");
extern s32 gProjectileOriginZ asm("D_800AE84C");

static __inline__ void SceneDrawProjectileQuad(ProjectileQuad *drawQuad,
                                               POLY_FT4 *prim, u32 *ot) {
    register s32 color asm("v0");
    s32 uv0, uv1, uv2, uv3;

    gte_ldv3(drawQuad->vertex[0], drawQuad->vertex[1], drawQuad->vertex[2]);
    gte_rtpt();
    gte_avsz3();
    uv1 = drawQuad->uv[1];

    do {
        color = drawQuad->color;
    } while (0);

    uv0 = drawQuad->uv[0];
    uv2 = drawQuad->uv[2];
    uv3 = drawQuad->uv[3];
    *(u32 *)&prim->u1 = uv1;
    *(u32 *)&prim->u0 = uv0;
    *(u32 *)&prim->r0 = color;
    *(u32 *)&prim->u2 = uv2;
    *(u32 *)&prim->u3 = uv3;
    gte_stsxy3(&prim->x0, &prim->x1, &prim->x3);
    gte_ldv0(drawQuad->vertex[3]);
    gte_rtps();
    gte_stsxy(&prim->x2);
    GraphicsAddTaggedPrimitive(ot + ((s8 *)&drawQuad->tag)[1], (u32 *)prim,
                               0x09000000);
}

void SceneUpdateProjectiles(Car *owner) {
    Car *other;
    s8 player;
    register Projectile *effect asm("s1");
    Projectile *hitEffect;
    s32 travel;
    s32 rightX;
    s32 rightY;
    s32 rightZ;
    s32 leftX;
    s32 leftY;
    s32 upX;
    s32 upY;
    s32 upZ;
    s8 effectIndex;
    s32 leftZ;
    s8 vertexIndex;
    Projectile *pool;
    ProjectileQuad *drawQuad;
    POLY_FT4 *prim;
    u32 *ot;
    s32 renderCount;
    void (*callback)(void);

    if (D_800A2FC8 == 0 || D_800A2EC8[0] != 0 || D_800A372C != 0 ||
        gProjectileMode[0] != 0 || D_800A2EACAbsolute[0] != 0) {
        return;
    }
    player = owner->slot;
    if ((PadGetButtons(player) & 0x10) && owner->callback != func_80025730 &&
        owner->unk268 == 0 && D_800A372C == 0) {
        pool = (Projectile *)(gProjectilePools[player] +
                              gProjectileWriteIndex[player] * 0x80);
        pool->life = 200;
        pool->forward = owner->rot[0];
        pool->right = owner->rot[1];
        pool->up = owner->rot[2];
        pool->position.x = *(s32 *)owner;
        pool->position.y = owner->pos.y;
        pool->position.z = owner->pos.z;
        gProjectileWriteIndex[player] =
            (gProjectileWriteIndex[player] + 1) % 10;
        SoundPlaySlot(10, 9);
    }
    pool = (Projectile *)gProjectilePools[player];
    effectIndex = 0;
    do {
        if (pool[effectIndex].life != 0) {
            other = gProjectileCars[0];
            hitEffect = &pool[effectIndex];
            do {
                if (other != owner &&
                    (hitEffect->position.x - *(s32 *)other >= 0
                         ? hitEffect->position.x - *(s32 *)other < 500
                         : other->pos.x - hitEffect->position.x < 500) &&
                    (hitEffect->position.y - other->pos.y >= 0
                         ? hitEffect->position.y - other->pos.y < 500
                         : other->pos.y - hitEffect->position.y < 500) &&
                    (hitEffect->position.z - other->pos.z >= 0
                         ? hitEffect->position.z - other->pos.z < 500
                         : other->pos.z - hitEffect->position.z < 500)) {
                    if (other->speed != 0) {
                        other->unk102 = RandomScaledGet(2);
                        callback = (void (*)(void))func_8003A880;
                        if (other->type != 0) {
                            callback = (void (*)(void))func_8003AA20;
                        }
                        ObjectSetCallbackIfAllowed(other, callback);
                    }
                    hitEffect->life = 0;
                    goto nextEffect;
                }
                other = other->next;
            } while (other != NULL);
            effect = (Projectile *)(effectIndex * 0x80 + (u32)pool);
            travel = (250 - effect->life) << 20;
            effect->position.x +=
                MathMultiplyFixed16(effect->forward.x, travel) >> 16;
            effect->position.y +=
                MathMultiplyFixed16(effect->forward.y, travel) >> 16;
            effect->position.z +=
                MathMultiplyFixed16(effect->forward.z, travel) >> 16;
            rightX = MathMultiplyFixed16(effect->right.x, -(50 << 16));
            rightY = MathMultiplyFixed16(effect->right.y, -(50 << 16));
            rightZ = MathMultiplyFixed16(effect->right.z, -(50 << 16));
            leftX = MathMultiplyFixed16(effect->right.x, 50 << 16);
            leftY = MathMultiplyFixed16(effect->right.y, 50 << 16);
            leftZ = MathMultiplyFixed16(effect->right.z, 50 << 16);
            upX = MathMultiplyFixed16(effect->up.x, 100 << 16);
            upY = MathMultiplyFixed16(effect->up.y, 100 << 16);
            upZ = MathMultiplyFixed16(effect->up.z, 100 << 16);
            effect->vertex[0].vx =
                (effect->position.x + ((rightX + upX) >> 16)) >> 2;
            effect->vertex[0].vy =
                (effect->position.y + ((rightY + upY) >> 16)) >> 2;
            effect->vertex[0].vz =
                (effect->position.z + ((rightZ + upZ) >> 16)) >> 2;
            effect->vertex[1].vx =
                (effect->position.x + ((leftX + upX) >> 16)) >> 2;
            effect->vertex[1].vy =
                (effect->position.y + ((leftY + upY) >> 16)) >> 2;
            effect->vertex[1].vz =
                (effect->position.z + ((leftZ + upZ) >> 16)) >> 2;
            effect->vertex[2].vx = (effect->position.x + (rightX >> 16)) >> 2;
            effect->vertex[2].vy = (effect->position.y + (rightY >> 16)) >> 2;
            effect->vertex[2].vz = (effect->position.z + (rightZ >> 16)) >> 2;
            effect->vertex[3].vx = (effect->position.x + (leftX >> 16)) >> 2;
            effect->vertex[3].vy = (effect->position.y + (leftY >> 16)) >> 2;
            effect->vertex[3].vz = (effect->position.z + (leftZ >> 16)) >> 2;
            vertexIndex = 0;
            do {
                u32 vertexAddress;

                /* effect stepped by one SVECTOR per vertex, so its vertex[0]
                 * is effect->vertex[vertexIndex]; retail keeps the stepped
                 * pointer. */
                vertexAddress = vertexIndex * 8;
                do {
                    vertexAddress = (u32)effect - -vertexAddress;
                } while (0);
                *(u16 *)&((Projectile *)vertexAddress)->vertex[0].vx -=
                    gProjectileOriginX;
                *(u16 *)&((Projectile *)vertexAddress)->vertex[0].vy -=
                    gProjectileOriginY;
                *(u16 *)&((Projectile *)vertexAddress)->vertex[0].vz -=
                    gProjectileOriginZ;
                vertexIndex++;
            } while (vertexIndex < 4);
            renderCount = 1;
            ot = (u32 *)gOrderingTable[0];
            prim = (POLY_FT4 *)gPrimitiveCursor[0];
            drawQuad =
                (ProjectileQuad *)(effectIndex * 0x80 + (u32)pool + 0x10);
            do {
                SceneDrawProjectileQuad(drawQuad, prim, ot);
                renderCount--;
                drawQuad++;
                prim++;
            } while (renderCount > 0);
            gPrimitiveCursor[0] = (u32)prim;
            pool[effectIndex].life--;
        }
    nextEffect:
        effectIndex++;
    } while (effectIndex < 10);
}

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

extern u8 D_800A342C[];
extern s32 D_800A3430[];
extern u8 D_80090F32[];
extern u8 D_800991E8[];
extern u8 D_800991E9[];
extern u8 D_800991EA[];

/* A 0x80 face in a player's ten-entry pool from
 * SceneInitProjectilePrimitives, tinted with the car's colour. */
typedef struct {
    u8 unk0;
    u8 unk1[0xF];
    Face face; /* 0x10 */
    u8 unk3C[0x24];
    SVECTOR vertex[4]; /* 0x60 */
} ProjectileFace;

#ifdef NON_MATCHING
/* Wall: size and instruction shape exact (0x214), but gcc pins the
 * HeapAlloc result to s4 (slot 5) instead of fp no matter where buf
 * is declared; retail order is row s0, poly s1, ptr s2, j s3, b2 s4,
 * b1 s5, b0 s6, i s7, buf fp. Decomp-permuter candidate. */
void SceneInitProjectilePrimitives(void) {
    u8 *buf;
    s8 i;
    u8 b0;
    u8 b1;
    u8 b2;
    s8 j;
    u8 *ptr;
    POLY_FT4 *poly;
    ProjectileFace *row;
    s32 v0;
    s32 v1;

    i = 0;
    if (D_800A2EB4Absolute2[0] > 0) {
        ptr = D_80090F32;
        do {
            D_800A342C[i] = 0;
            buf = (u8 *)HeapAlloc(0x500);
            v1 = (s8)((Car *)D_800A3984[0])[i + 1].driver;
            D_800A3430[i] = (s32)buf;
            j = 0;
            v0 = v1 * 3;
            b0 = D_800991E8[v0];
            b1 = D_800991E9[v0];
            b2 = D_800991EA[v0];
            do {
                row = (ProjectileFace *)buf + j;
                poly = (POLY_FT4 *)&row->face;
                SetPolyFT4(poly);
                SetShadeTex(poly, 0);
                row->face.depth = 0x24;
                row->face.vertex[0] = &row->vertex[0];
                row->face.vertex[1] = &row->vertex[1];
                row->face.vertex[2] = &row->vertex[3];
                row->face.r0 = b0;
                row->face.g0 = b1;
                row->face.b0 = b2;
                row->face.vertex[3] = &row->vertex[2];
                row->face.tpage =
                    GetTPage(((SceneTexture *)(ptr - 0xC))->tpage, 0,
                             ((SceneTexture *)(ptr - 0xC))->tpx,
                             ((SceneTexture *)(ptr - 0xC))->tpy);
                row->face.u0 = ((SceneTexture *)(ptr - 0xC))->u + 0x6F;
                row->face.v0 = *(u16 *)&((SceneTexture *)(ptr - 0xC))->v;
                row->face.u1 = ((SceneTexture *)(ptr - 0xC))->u + 0x60;
                row->face.v1 = *(u16 *)&((SceneTexture *)(ptr - 0xC))->v;
                row->face.u2 = ((SceneTexture *)(ptr - 0xC))->u + 0x6F;
                row->face.v2 = ((SceneTexture *)(ptr - 0xC))->v + 0xF;
                row->face.u3 = ((SceneTexture *)(ptr - 0xC))->u + 0x60;
                row->face.v3 = ((SceneTexture *)(ptr - 0xC))->v + 0xF;
                row->unk0 = 0;
                j++;
            } while (j < 10);
            i++;
        } while (i < D_800A2EB4Absolute2[0]);
    }
}
#else

void SceneInitProjectilePrimitives(void) {
    u8 *buf;
    s8 i;
    u8 b0;
    u8 b1;
    u8 b2;
    s8 j;
    u8 *ptr;
    POLY_FT4 *poly;
    ProjectileFace *row;
    s32 t;
    s32 u;
    s32 v0;
    s32 v1;

    i = 0;
    if (D_800A2EB4Absolute2[0] > 0) {
        ptr = D_80090F32;
        do {
            D_800A342C[i] = 0;
            t = (s32)HeapAlloc(0x500);
            u = D_800A3984[0];
            D_800A3430[i] = t;
            v1 = (s8)((Car *)((i * 5 << 8) + u))[1].driver;
            buf = (u8 *)t;
            j = 0;
            v0 = v1 * 3;
            b0 = D_800991E8[v0];
            b1 = D_800991E9[v0];
            b2 = D_800991EA[v0];
            do {
                row = (ProjectileFace *)buf + j;
                poly = (POLY_FT4 *)&row->face;
                SetPolyFT4(poly);
                SetShadeTex(poly, 0);
                row->face.depth = 0x24;
                row->face.vertex[0] = &row->vertex[0];
                row->face.vertex[1] = &row->vertex[1];
                row->face.vertex[2] = &row->vertex[3];
                row->face.r0 = b0;
                row->face.g0 = b1;
                row->face.b0 = b2;
                row->face.vertex[3] = &row->vertex[2];
                row->face.tpage =
                    GetTPage(((SceneTexture *)(ptr - 0xC))->tpage, 0,
                             ((SceneTexture *)(ptr - 0xC))->tpx,
                             ((SceneTexture *)(ptr - 0xC))->tpy);
                row->face.u0 = ((SceneTexture *)(ptr - 0xC))->u + 0x6F;
                row->face.v0 = *(u16 *)&((SceneTexture *)(ptr - 0xC))->v;
                row->face.u1 = ((SceneTexture *)(ptr - 0xC))->u + 0x60;
                row->face.v1 = *(u16 *)&((SceneTexture *)(ptr - 0xC))->v;
                row->face.u2 = ((SceneTexture *)(ptr - 0xC))->u + 0x6F;
                row->face.v2 = ((SceneTexture *)(ptr - 0xC))->v + 0xF;
                row->face.u3 = ((SceneTexture *)(ptr - 0xC))->u + 0x60;
                row->face.v3 = ((SceneTexture *)(ptr - 0xC))->v + 0xF;
                row->unk0 = 0;
                j++;
            } while (j < 10);
            i++;
        } while (i < D_800A2EB4Absolute2[0]);
    }
}

#endif

/* A 0x58 face pinned to a track section: one of the per-car pools in
 * D_800A3444, linked for drawing while its section is visible. */
typedef struct {
    s16 section; /* 0x00 */
    u8 unk2[2];
    Face face;         /* 0x04 */
    SVECTOR vertex[4]; /* 0x30 */
    u8 unk50[8];
} SectionDecal;

extern s8 D_800A343C;
extern SectionDecal *D_800A3444[];
extern s32 gTrackSectionsv asm("gTrackSections");

void SceneLinkLiveEntries(Car *car) {
    SectionDecal *base;
    SectionDecal *entry;
    Face *tail;
    s8 count;
    s8 n;
    s8 i;
    s32 id;
    u16 flag;
    TrackSection *p;

    count = D_800A343C;
    base = D_800A3444[car->slot];
    for (n = 1, i = 1, tail = &base->face; i < count; i++) {
        entry = (SectionDecal *)(i * 0x58 + (s32)base);
        id = entry->section;
        p = (TrackSection *)(u8 *)(id * 0x90 + gTrackSectionsv);
        flag = p->culled;
        if (flag != 0) {
            *(s32 *)&tail->next = (s32)&entry->face;
            tail = &entry->face;
            n++;
        }
    }
    func_80032DEC(&base->face, n);
}

extern SceneTexture D_80090F50[];
extern Vec3 *D_800AE15C[];
extern u8 D_800A3424;
extern s8 D_800A3438;

void SceneInitProjectiles(void) {
    extern u16 func_80030F24(Car *, s32 *, s32, s32, s32);
    extern void SetPolyFT4(POLY_FT4 *);
    s32 heights[2];
    s32 point[3];
    Car object;
    SceneTexture *tim;
    SectionDecal *elem;
    Car *objectPtr;
    s32 *pointPtr;
    u8 u;
    u8 v;
    u16 angle;
    s32 dist;
    s16 i;
    s16 j;

    tim = D_80090F50;
    D_800A3438 = 0x40 >> D_800A3424;
    D_800A343C = 0x40 >> (D_800A3424 - 1);
    for (i = 0; i < D_800A3424; i++) {
        D_800A3444[i] = HeapAlloc(D_800A343C * 0x58);
        for (j = 0; j < D_800A343C; j++) {
            elem = &D_800A3444[i][j];
            SetPolyFT4((POLY_FT4 *)&elem->face);
            SetSemiTrans(&elem->face, 1);
            SetShadeTex(&elem->face, 1);
            elem->face.clut = GetClut(tim->clutX, tim->clutY);
            elem->face.vertex[0] = &elem->vertex[0];
            elem->face.vertex[1] = &elem->vertex[1];
            elem->face.vertex[2] = &elem->vertex[3];
            elem->face.depth = 0;
            elem->face.vertex[3] = &elem->vertex[2];
            elem->face.next = 0;
            elem->face.tpage = GetTPage(tim->tpage, 2, tim->tpx, tim->tpy);
            elem->face.type = 0xE;
            u = tim->u;
            elem->face.u1 = u;
            elem->face.u0 = u;
            u = tim->u + 0x3F;
            elem->face.u3 = u;
            elem->face.u2 = u;
            v = tim->v + 0x1F;
            elem->face.v2 = v;
            elem->face.v0 = v;
            v = tim->v;
            elem->face.v3 = v;
            elem->face.v1 = v;
        }
    }
    object.unk118 = 0;
    object.type = 2;
    for (i = 0; i < gTrackSectionCount[0]; i++) {
        objectPtr = &object;
        pointPtr = point;
        angle = gTrackSections[0][i].angle;
        object.heading = angle;
        object.fineHeading = angle * 4;
        for (j = 0; j < 2; j++) {
            point[0] = D_800AE15C[0][i].x;
            point[1] = D_800AE15C[0][i].y;
            dist = 0x96;
            if (j != 0) {
                dist = -0x96;
            }
            func_80030F24(objectPtr, pointPtr, 0, dist, 0);
            heights[j] = point[2];
        }
        *(s32 *)&gTrackSections[0][i].height0 =
            ((heights[0] + 0x4000) << 0x10) | (heights[1] + 0x4000);
    }
    SceneInitRoadStrip();
}

typedef struct SceneRoadQuad {
    u16 section;
    u8 unk2[0x2E];
    SVECTOR points[4];
    struct SceneRoadQuad *next;
    struct SceneRoadQuad *prev;
} SceneRoadQuad;

extern s16 D_800A3440[];
extern SceneRoadQuad *D_800A344C[];
extern SceneRoadQuad *D_800A3454[];
extern s16 D_800A357C[];
extern u8 D_800A2D0C[];
extern MATRIX D_8009931C;
typedef struct {
    s16 x, y, z;
} SceneRoadPoint;
extern SceneRoadPoint D_800A45C0[][2];
extern SceneRoadPoint D_800A45D8[][2];

extern MATRIX D_800992FC[];
extern s16 D_800A45D8X[] asm("D_800A45D8");
extern s16 D_800A45DA[];
extern s16 D_800A45DC[];

#ifdef NATIVE
void SceneInitRoadStrip(void) {
    u8 first[2];
    SVECTOR rotation;
    VECTOR result;
    long flag;
    s8 slot;
    u16 nextSection;
    s32 slotIndex;
    s8 **base;
    u8 *firstSlot;
    u8 *firstBase;
    u16 section;
    s32 sectionIndex;
    s8 index;
    s8 *(*quadSlots)[];
    s8 side;
    register s8 otherSide;
    TrackSection *node;
    SceneRoadQuad *quad;
    register s32 *origin;
    s32 row;
    register s16 x;
    s16 y;
    s32 z;
    Car *car;
    register s16 *sectionPtr;
    register s16 *sectionBase;
    s32 lookBehind;
    s32 sectionPosition;
    s32 count;

    do {
        quadSlots = &D_800A3444;
    } while (0);

    first[0] = 1;
    first[1] = 1;
    PushMatrix();
    slot = 0;
    if (D_800A3424 != 0) {
        firstBase = first;
        origin = D_800AE844;
        do {
            sectionBase = D_800A3440;
            sectionPtr = sectionBase + slot;
            if (slot != 0) {
                car = D_800A3428View;
            } else {
                car = gPlayerCar[0];
            }
            section = (u16)car->segment;
            lookBehind = D_800A3438;
            *sectionPtr = section;
            sectionPosition =
                ((s16)section + lookBehind - 1) % gTrackSectionCount[0];
            count = D_800A343C;
            node = gTrackSections[0] + sectionPosition;
            index = 0;
            if (count > 0) {
                s32 slotBits;
                s32 slotOffset;

                slotBits = (u32)(u8)slot << 24;
                slotIndex = slotBits >> 24;
                slotOffset = slotIndex * 4;
                /* la base, D_800A3444 */
                base = (s8 **)D_800A3444;
                /* Unsigned negation preserves the address-add operand order. */
                base = (s8 **)(slotOffset - -(u32)base);
                firstSlot = firstBase + slotIndex;
                do {
                    s32 sectionValue;
                    register s8 *quadBase;
                    TrackSection *nodes;
                    SVECTOR *rotationPtr;
                    TrackSection *previousNode;

                    previousNode = node->prev;
                    section = node->section;
                    nextSection = previousNode->section;
                    quadBase = *base;
                    rotation.vx = 0;
                    rotationPtr = &rotation;
                    nodes = gTrackSections[0];
                    sectionValue = (s16)section;
                    rotation.vy = nodes[sectionValue].angle * 4;
                    sectionIndex = sectionValue;
                    quad = (SceneRoadQuad *)quadBase + index;
                    rotation.vz = 0;
                    RotMatrix(rotationPtr, D_800992FC);
                    SetRotMatrix(D_800992FC);
                    SetTransMatrix(D_800992FC);
                    side = 0;
                    rotation.vy = 0;
                    row = slotIndex * 12;
                sideLoop:
                    {
                        otherSide = side + 2;
                        rotation.vx = side ? -150 : 150;
                        RotTrans(&rotation, &result, &flag);
                        if (*firstSlot != 0) {
                            register u8 *firstPoint;
                            register SceneRoadPoint *firstCache;
                            s32 cameraZ;

                            x = (D_800AE15C[0][sectionIndex].x + result.vz >>
                                 2) -
                                origin[0];
                            firstPoint = (u8 *)quad + side * sizeof(SVECTOR);
                            firstCache = (SceneRoadPoint *)((u8 *)D_800A45C0 +
                                                            (side * 6 + row));
                            firstCache->x = x;
                            ((SVECTOR *)(firstPoint + 0x30))->vx = x;
                            y = (D_800AE15C[0][sectionIndex].y + result.vx >>
                                 2) -
                                origin[1];
                            firstCache->y = y;
                            ((SVECTOR *)(firstPoint + 0x30))->vy = y;
                            cameraZ = origin[2];
                            if (side) {
                                z = gTrackSections[0][sectionIndex].height0 -
                                    0x4000;
                            } else {
                                z = gTrackSections[0][sectionIndex].height1 -
                                    0x4000;
                            }
                            firstCache->z = (z >> 2) - cameraZ;
                            ((SVECTOR *)(firstPoint + 0x30))->vz =
                                firstCache->z =
                                    ((volatile SceneRoadPoint *)firstCache)->z;
                            if (side) {
                                *firstSlot = 0;
                            }
                        } else {
                            register u8 *oldPoint;
                            register s32 oldOffset;

                            oldOffset = side * 6 + row;
                            oldPoint = (u8 *)quad + side * sizeof(SVECTOR);
                            ((SVECTOR *)(oldPoint + 0x30))->vx =
                                *(s16 *)((u8 *)D_800A45D8X + oldOffset);
                            ((SVECTOR *)(oldPoint + 0x30))->vy =
                                *(s16 *)((u8 *)D_800A45DA + oldOffset);
                            ((SVECTOR *)(oldPoint + 0x30))->vz =
                                *(s16 *)((u8 *)D_800A45DC + oldOffset);
                        }
                        {
                            register u8 *nextPoint;
                            register SceneRoadPoint *nextCache;
                            s32 cacheOffset;
                            s32 cameraZ;
                            s32 nextSectionIndex;

                            nextSectionIndex = (s16)nextSection;
                            x = (D_800AE15C[0][nextSectionIndex].x +
                                     result.vz >>
                                 2) -
                                origin[0];
                            cacheOffset = side * 6 + row;
                            asm(""
                                : "=r"(cacheOffset)
                                : "0"(cacheOffset), "r"(x));
                            nextCache = (SceneRoadPoint *)((u8 *)D_800A45D8 +
                                                           cacheOffset);
                            asm("" : "=r"(nextCache) : "0"(nextCache));
                            nextPoint =
                                (u8 *)quad + otherSide * sizeof(SVECTOR);
                            nextCache->x = x;
                            ((SVECTOR *)(nextPoint + 0x30))->vx = x;
                            y = (D_800AE15C[0][nextSectionIndex].y +
                                     result.vx >>
                                 2) -
                                origin[1];
                            nextCache->y = y;
                            ((SVECTOR *)(nextPoint + 0x30))->vy = y;
                            cameraZ = origin[2];
                            if (side) {
                                z = gTrackSections[0][nextSectionIndex]
                                        .height0 -
                                    0x4000;
                            } else {
                                z = gTrackSections[0][nextSectionIndex]
                                        .height1 -
                                    0x4000;
                            }
                            nextCache->z = (z >> 2) - cameraZ;
                            ((SVECTOR *)(nextPoint + 0x30))->vz = nextCache->z =
                                ((volatile SceneRoadPoint *)nextCache)->z;
                        }
                        asm("" : : "r"(node), "r"(index), "r"(section));
                        side++;
                    }
                    if (side < 2) {
                        goto sideLoop;
                    }
                    {
                        s32 previous;
                        register s32 following;
                        s32 currentIndex;
                        s32 last;
                        s8 *previousBase;

                        count = D_800A343C;
                        currentIndex = index;
                        last = count - 1;
                        previous = (currentIndex + last) % count;
                        following = (currentIndex + 1) % count;
                        quad->next = (SceneRoadQuad *)*base + previous;
                        previousBase = *base;
                        index++;
                        quad->section = section;
                        quad->prev = (SceneRoadQuad *)previousBase + following;
                    }
                    node = node->prev;
                } while (index < count);
            }
            {
                s32 tailCount;
                s32 endOffset;

                asm("" : : "r"((u8)slot), "r"(quadSlots) : "memory");
                tailCount = D_800A343C;
                D_800A344C[slot] = (SceneRoadQuad *)(*quadSlots)[slot];
                endOffset = tailCount * 0x58 - 0x58;
                D_800A3454[slot] =
                    (SceneRoadQuad *)((u8 *)(*quadSlots)[slot] + endOffset);
                slot++;
            }
        } while (slot < D_800A3424);
    }
    PopMatrix();
}
#else
void SceneInitRoadStrip(void) {
    u8 first[2];
    SVECTOR rotation;
    VECTOR result;
    long flag;
    s8 slot;
    u16 nextSection;
    s32 slotIndex;
    s8 **base;
    u8 *firstSlot;
    u8 *firstBase;
    u16 section;
    s32 sectionIndex;
    s8 index;
    s8 *(*quadSlots)[];
    s8 side;
    register s8 otherSide asm("s5");
    TrackSection *node;
    SceneRoadQuad *quad;
    register s32 *origin asm("s7");
    s32 row;
    register s16 x asm("v1");
    s16 y;
    s32 z;
    Car *car;
    register s16 *sectionPtr asm("v1");
    register s16 *sectionBase asm("a0");
    s32 lookBehind;
    s32 sectionPosition;
    s32 count;

    do {
        quadSlots = &D_800A3444;
    } while (0);

    first[0] = 1;
    first[1] = 1;
    PushMatrix();
    slot = 0;
    if (D_800A3424 != 0) {
        firstBase = first;
        origin = D_800AE844;
        do {
            sectionBase = D_800A3440;
            sectionPtr = sectionBase + slot;
            if (slot != 0) {
                car = D_800A3428View;
            } else {
                car = gPlayerCar[0];
            }
            section = (u16)car->segment;
            lookBehind = D_800A3438;
            *sectionPtr = section;
            sectionPosition =
                ((s16)section + lookBehind - 1) % gTrackSectionCount[0];
            count = D_800A343C;
            node = gTrackSections[0] + sectionPosition;
            index = 0;
            if (count > 0) {
                s32 slotBits;
                s32 slotOffset;

                slotBits = (u32)(u8)slot << 24;
                slotIndex = slotBits >> 24;
                slotOffset = slotIndex * 4;
                asm("la %0, %1"
                    : "=&r"(base)
                    : "i"(D_800A3444), "r"(slotOffset));
                /* Unsigned negation preserves the address-add operand order. */
                base = (s8 **)(slotOffset - -(u32)base);
                firstSlot = firstBase + slotIndex;
                do {
                    s32 sectionValue;
                    register s8 *quadBase asm("a2");
                    TrackSection *nodes;
                    SVECTOR *rotationPtr;
                    TrackSection *previousNode;

                    previousNode = node->prev;
                    section = node->section;
                    nextSection = previousNode->section;
                    quadBase = *base;
                    rotation.vx = 0;
                    rotationPtr = &rotation;
                    nodes = gTrackSections[0];
                    sectionValue = (s16)section;
                    rotation.vy = nodes[sectionValue].angle * 4;
                    sectionIndex = sectionValue;
                    quad = (SceneRoadQuad *)quadBase + index;
                    rotation.vz = 0;
                    RotMatrix(rotationPtr, D_800992FC);
                    SetRotMatrix(D_800992FC);
                    SetTransMatrix(D_800992FC);
                    side = 0;
                    rotation.vy = 0;
                    row = slotIndex * 12;
                sideLoop:
                    {
                        otherSide = side + 2;
                        rotation.vx = side ? -150 : 150;
                        RotTrans(&rotation, &result, &flag);
                        if (*firstSlot != 0) {
                            register u8 *firstPoint asm("a2");
                            register SceneRoadPoint *firstCache asm("a0");
                            s32 cameraZ;

                            x = (D_800AE15C[0][sectionIndex].x + result.vz >>
                                 2) -
                                origin[0];
                            firstPoint = (u8 *)quad + side * sizeof(SVECTOR);
                            firstCache = (SceneRoadPoint *)((u8 *)D_800A45C0 +
                                                            (side * 6 + row));
                            firstCache->x = x;
                            ((SVECTOR *)(firstPoint + 0x30))->vx = x;
                            y = (D_800AE15C[0][sectionIndex].y + result.vx >>
                                 2) -
                                origin[1];
                            firstCache->y = y;
                            ((SVECTOR *)(firstPoint + 0x30))->vy = y;
                            cameraZ = origin[2];
                            if (side) {
                                z = gTrackSections[0][sectionIndex].height0 -
                                    0x4000;
                            } else {
                                z = gTrackSections[0][sectionIndex].height1 -
                                    0x4000;
                            }
                            firstCache->z = (z >> 2) - cameraZ;
                            ((SVECTOR *)(firstPoint + 0x30))->vz =
                                firstCache->z =
                                    ((volatile SceneRoadPoint *)firstCache)->z;
                            if (side) {
                                *firstSlot = 0;
                            }
                        } else {
                            register u8 *oldPoint asm("a0");
                            register s32 oldOffset asm("v1");

                            oldOffset = side * 6 + row;
                            oldPoint = (u8 *)quad + side * sizeof(SVECTOR);
                            ((SVECTOR *)(oldPoint + 0x30))->vx =
                                *(s16 *)((u8 *)D_800A45D8X + oldOffset);
                            ((SVECTOR *)(oldPoint + 0x30))->vy =
                                *(s16 *)((u8 *)D_800A45DA + oldOffset);
                            ((SVECTOR *)(oldPoint + 0x30))->vz =
                                *(s16 *)((u8 *)D_800A45DC + oldOffset);
                        }
                        {
                            register u8 *nextPoint asm("a0");
                            register SceneRoadPoint *nextCache asm("a1");
                            s32 cacheOffset;
                            s32 cameraZ;
                            s32 nextSectionIndex;

                            nextSectionIndex = (s16)nextSection;
                            x = (D_800AE15C[0][nextSectionIndex].x +
                                     result.vz >>
                                 2) -
                                origin[0];
                            cacheOffset = side * 6 + row;
                            asm(""
                                : "=r"(cacheOffset)
                                : "0"(cacheOffset), "r"(x)
                                : "v0");
                            nextCache = (SceneRoadPoint *)((u8 *)D_800A45D8 +
                                                           cacheOffset);
                            asm("" : "=r"(nextCache) : "0"(nextCache) : "a0");
                            nextPoint =
                                (u8 *)quad + otherSide * sizeof(SVECTOR);
                            nextCache->x = x;
                            ((SVECTOR *)(nextPoint + 0x30))->vx = x;
                            y = (D_800AE15C[0][nextSectionIndex].y +
                                     result.vx >>
                                 2) -
                                origin[1];
                            nextCache->y = y;
                            ((SVECTOR *)(nextPoint + 0x30))->vy = y;
                            cameraZ = origin[2];
                            if (side) {
                                z = gTrackSections[0][nextSectionIndex]
                                        .height0 -
                                    0x4000;
                            } else {
                                z = gTrackSections[0][nextSectionIndex]
                                        .height1 -
                                    0x4000;
                            }
                            nextCache->z = (z >> 2) - cameraZ;
                            ((SVECTOR *)(nextPoint + 0x30))->vz = nextCache->z =
                                ((volatile SceneRoadPoint *)nextCache)->z;
                        }
                        asm("" : : "r"(node), "r"(index), "r"(section));
                        side++;
                    }
                    if (side < 2) {
                        goto sideLoop;
                    }
                    {
                        s32 previous;
                        register s32 following asm("a2");
                        s32 currentIndex;
                        s32 last;
                        s8 *previousBase;

                        count = D_800A343C;
                        currentIndex = index;
                        last = count - 1;
                        previous = (currentIndex + last) % count;
                        following = (currentIndex + 1) % count;
                        quad->next = (SceneRoadQuad *)*base + previous;
                        previousBase = *base;
                        index++;
                        quad->section = section;
                        quad->prev = (SceneRoadQuad *)previousBase + following;
                    }
                    node = node->prev;
                } while (index < count);
            }
            {
                s32 tailCount;
                s32 endOffset;

                asm("" : : "r"((u8)slot), "r"(quadSlots) : "memory");
                tailCount = D_800A343C;
                D_800A344C[slot] = (SceneRoadQuad *)(*quadSlots)[slot];
                endOffset = tailCount * 0x58 - 0x58;
                D_800A3454[slot] =
                    (SceneRoadQuad *)((u8 *)(*quadSlots)[slot] + endOffset);
                slot++;
            }
        } while (slot < D_800A3424);
    }
    PopMatrix();
}
#endif

void SceneUpdateRoadStrip(Car *car) {
    SVECTOR rotation;
    VECTOR result;
    long flag;
    s8 count;
    s8 slot;
    s16 distance;
    u16 section;
    register s16 x asm("v1");
    s16 y;
    s32 z;
    s8 side;
    s8 otherSide;
    TrackSection *node;
    SceneRoadQuad *quad;
    SVECTOR *points;
    SceneRoadPoint *cache;
    register s32 row asm("a2");
    SVECTOR *heightPoint;
    s32 mode;

    slot = car->slot;
    section = (u16)car->segment;
    distance = section - D_800A3440[slot];
    if (distance != 0 && (s16)section != -1 && D_800A359C[0] == 0 &&
        D_800A2D0C[0] == 0) {
        PushMatrix();
        if (ABS(distance) >= 14) {
            if (distance > 0) {
                distance -= gTrackSectionCount[0];
            } else {
                distance += gTrackSectionCount[0];
            }
        }
        if (distance > 0) {
            /* Keep the offset and address in the same register. */
            SVECTOR *point;
            register s32 pointOffset asm("a1");
            s32 *origin;
            s32 cameraZ;

            count = 0;
            node = gTrackSections[0] +
                   (D_800A3440[slot] + D_800A3438) % gTrackSectionCount[0];
            while (count < distance) {
                section = node->section;
                rotation.vx = 0;
                rotation.vy = gTrackSections[0][(s16)section].angle * 4;
                rotation.vz = 0;
                RotMatrix(&rotation, &D_8009931C);
                SetRotMatrix(&D_8009931C);
                SetTransMatrix(&D_8009931C);
                side = 0;
                rotation.vy = 0;
                D_800A344C[slot] = quad = D_800A3454[slot];
                points = quad->points;
                origin = D_800AE844;
                do {
                    otherSide = side + 2;
                    rotation.vx = side ? -150 : 150;
                    RotTrans(&rotation, &result, &flag);
                    points[otherSide].vx = D_800A45C0[slot][side].x;
                    points[otherSide].vy = D_800A45C0[slot][side].y;
                    points[otherSide].vz = D_800A45C0[slot][side].z;
                    x = (D_800AE15C[0][(s16)section].x + result.vz >> 2) -
                        origin[0];
                    row = slot * 12 + side * 6;
                    /* Build the cache pointer after x is ready. */
                    asm("" : "=r"(row) : "0"(row), "r"(x) : "v0", "a1");
                    cache = (SceneRoadPoint *)((u8 *)D_800A45C0 + row);
                    pointOffset = side * 8;
                    point = (SVECTOR *)(pointOffset + (u32)points);
                    cache->x = x;
                    point->vx = x;
                    y = (D_800AE15C[0][(s16)section].y + result.vx >> 2) -
                        origin[1];
                    cache->y = y;
                    point->vy = y;
                    cameraZ = origin[2];
                    if (side) {
                        z = gTrackSections[0][(s16)section].height0 - 0x4000;
                    } else {
                        z = gTrackSections[0][(s16)section].height1 - 0x4000;
                    }
                    cache->z = (z >> 2) - cameraZ;
                    /* Reload the cached height before both stores. */
                    point->vz = cache->z =
                        ((volatile SceneRoadPoint *)cache)->z;
                    D_800A45D8[slot][side].x =
                        D_800A3454[slot]->next->points[otherSide].vx;
                    D_800A45D8[slot][side].y =
                        D_800A3454[slot]->next->points[otherSide].vy;
                    D_800A45D8[slot][side].z =
                        D_800A3454[slot]->next->points[otherSide].vz;
                    side++;
                } while (side < 2);
                D_800A344C[slot]->section = section;
                node = node->next;
                count++;
                D_800A3454[slot] = D_800A3454[slot]->next;
                origin = 0;
            }
        } else {
            s32 *origin;
            s32 lastSection;
            s32 sectionIndex;
            s32 length;
            s32 cameraZ;
            register SVECTOR *point;
            register s32 pointOffset;

            count = 0;
            sectionIndex = D_800A3440[slot] - D_800A3438;
            length = gTrackSectionCount[0];
            lastSection = length - 1;
            sectionIndex += lastSection;
            node = gTrackSections[0] + sectionIndex % length;
            distance = -distance;
            while (count < distance) {
                section = node->section;
                rotation.vx = 0;
                rotation.vy = gTrackSections[0][(s16)section].angle * 4;
                rotation.vz = 0;
                RotMatrix(&rotation, &D_8009931C);
                SetRotMatrix(&D_8009931C);
                SetTransMatrix(&D_8009931C);
                side = 0;
                rotation.vy = 0;
                D_800A3454[slot] = quad = D_800A344C[slot];
                points = quad->points;
                origin = D_800AE844;
                do {
                    otherSide = side + 2;
                    rotation.vx = side ? -150 : 150;
                    RotTrans(&rotation, &result, &flag);
                    points[side].vx = D_800A45D8[slot][side].x;
                    points[side].vy = D_800A45D8[slot][side].y;
                    points[side].vz = D_800A45D8[slot][side].z;
                    x = (D_800AE15C[0][(s16)section].x + result.vz >> 2) -
                        origin[0];
                    row = slot * 12 + side * 6;
                    asm("" : "=r"(row) : "0"(row), "r"(x) : "v0", "a0");
                    cache = (SceneRoadPoint *)((u8 *)D_800A45D8 + row);
                    pointOffset = otherSide * 8;
                    point = (SVECTOR *)(pointOffset + (u32)points);
                    cache->x = x;
                    point->vx = x;
                    y = (D_800AE15C[0][(s16)section].y + result.vx >> 2) -
                        origin[1];
                    cache->y = y;
                    heightPoint = point;
                    heightPoint->vy = y;
                    cameraZ = origin[2];
                    if (side) {
                        z = gTrackSections[0][(s16)section].height0 - 0x4000;
                    } else {
                        z = gTrackSections[0][(s16)section].height1 - 0x4000;
                    }
                    cache->z = (z >> 2) - cameraZ;
                    heightPoint->vz = cache->z =
                        ((volatile SceneRoadPoint *)cache)->z;
                    D_800A45C0[slot][side].x =
                        D_800A344C[slot]->prev->points[side].vx;
                    D_800A45C0[slot][side].y =
                        D_800A344C[slot]->prev->points[side].vy;
                    D_800A45C0[slot][side].z =
                        D_800A344C[slot]->prev->points[side].vz;
                    side++;
                } while (side < 2);
                D_800A344C[slot] = D_800A344C[slot]->prev;
                node = node->prev;
                count++;
                D_800A3454[slot]->section = section;
                origin = 0;
            }
        }
        mode = D_800A397C[0];
        D_800A3440[slot] = car->segment;
        if (mode != 2) {
            D_800A357C[slot] = car->segment;
        }
        PopMatrix();
    }
}

extern int abs(int);
extern u8 D_800A2FE8;
extern s8 D_800A3480;
extern s8 D_800A345C;
extern s8 D_800A3460;
extern u16 D_800A3464;
extern u16 D_800A3468;
extern u8 D_800A346C;
extern u8 D_800A3470;
extern u8 D_800A3474;
extern u16 D_80099254[];
extern u16 D_80099256[];
extern u16 D_80099258[];
extern u8 gHandSegments[];
extern u8 D_800A46A0[];
extern u8 D_800A46A2[];
extern u8 D_800A46A4[];
extern MATRIX D_800A7530[];
extern SVECTOR D_800A2FEC;

void func_800474A0(void) {
    u32 *flagScratch = (u32 *)SCRATCHPAD_BASE;
    u32 *padScratch = (u32 *)(SCRATCHPAD_BASE + 0x120);
    u32 *unkScratch = (u32 *)(SCRATCHPAD_BASE + 0x240);
    s32 angleRaw;
    s32 absA3;
    s16 loopIdx;
    s16 segIdx;
    s32 s5v;
    s32 fpVal;
    s32 s4Off;
    s16 s2v;
    s32 s1v;
    u16 rot[3];
    MATRIX mat1;
    MATRIX mat2;
    SVECTOR vec;
    VECTOR out;
    s32 gteFlag;
    s32 t;
    s32 scratchW;
    s32 vyVal;
    s32 multTmp;
    Car *car;
    s32 place;
    s32 c8val;
    s8 count;
    s8 fade;
    ModelVertex *rec;
    Face *node;
    MATRIX *transPtr;
    u8 *prim;
    u8 *primNext;
    s32 otBaseW;
    SVECTOR **verts;
    s32 primCount;
    s32 angC;

    if (D_800A2FE8 == 0) {
        return;
    }
    angleRaw = D_800A3480;
    flagScratch[0] = 0;
    flagScratch[9] = 1;
    padScratch[0] = 0;
    padScratch[9] = 1;
    unkScratch[0] = 0;
    unkScratch[9] = 2;
    flagScratch[1] = 0;
    flagScratch[10] = 3;
    padScratch[1] = 0;
    padScratch[10] = 0;
    unkScratch[1] = 0;
    unkScratch[10] = 6;
    flagScratch[2] = 0;
    flagScratch[11] = 3;
    padScratch[2] = 0;
    padScratch[11] = 0;
    unkScratch[2] = 0;
    unkScratch[11] = 7;
    flagScratch[3] = 2;
    flagScratch[12] = 3;
    padScratch[3] = 3;
    padScratch[12] = 0;
    unkScratch[3] = 2;
    unkScratch[12] = 8;
    flagScratch[4] = 8;
    flagScratch[13] = 3;
    padScratch[4] = 3;
    padScratch[13] = 0;
    unkScratch[4] = 3;
    unkScratch[13] = 9;
    flagScratch[5] = 0x10;
    flagScratch[14] = 5;
    padScratch[5] = 3;
    padScratch[14] = 0;
    unkScratch[5] = 4;
    unkScratch[14] = 0xa;
    flagScratch[6] = 1;
    flagScratch[15] = 5;
    padScratch[6] = 0;
    padScratch[15] = 0;
    unkScratch[6] = 1;
    unkScratch[15] = 0xb;
    flagScratch[7] = 1;
    flagScratch[16] = 5;
    padScratch[7] = 1;
    padScratch[16] = 0;
    unkScratch[7] = 1;
    unkScratch[16] = 0xc;
    flagScratch[8] = 1;
    flagScratch[17] = 5;
    padScratch[8] = 0;
    padScratch[17] = 0;
    unkScratch[8] = 2;
    unkScratch[17] = 0xd;
    c8val = D_800A2EC8Absolute[0];
    absA3 = abs(angleRaw);
    if (c8val != 0) {
        D_800A3468 = 0;
        D_800A3474 = 0;
        D_800A3460 = 0;
        D_800A3470 = 0;
    } else {
        if (D_800A345C < 0xA) {
            car = gPlayerCar[0];
            place = car->gearIndex;
            if (place != 0) {
                if (car->rpm < car->gear[place].lowRpm + 0x3E8) {
                    D_800A346C = 1;
                    goto afterCounter;
                }
            }
            if (place < 3 && car->rpm >= 0x2EE1) {
                D_800A346C = 1;
            }
        }
    afterCounter:
        if (D_800A346C != 0) {
            count = ++D_800A345C;
        } else if (D_800A345C != 0) {
            count = --D_800A345C;
        } else {
            count = 0;
        }
        D_800A345C = count;
        if (count >= 0xA) {
            D_800A346C = 0;
        }
        if ((PadGetButtons(0) & 0x10) != 0 && D_800A345C == 0) {
            D_800A3470 = 1;
        } else {
            D_800A3468 = 0;
            D_800A3474 = 0;
            D_800A3460 = 0;
            D_800A3470 = 0;
        }
        if (D_800A3470 != 0) {
            if (D_800A3460 < 0xA) {
                fade = ++D_800A3460;
            } else {
                fade = 0xA;
            }
        } else {
            fade = 0;
        }
        D_800A3460 = fade;
    }
    loopIdx = 0;
    do {
        if (loopIdx != 0) {
            if (D_800A345C != 0) {
                multTmp = D_800A345C * (D_800A3480 << 2);
                rot[0] =
                    D_80099254[(s16)loopIdx * 3] - ((s16)absA3 >> 1) + multTmp;
                multTmp = D_800A345C * (0x40 - D_800A3480 * 2);
                rot[1] = D_80099256[(s16)loopIdx * 3];
                rot[2] = D_80099258[(s16)loopIdx * 3] - multTmp;
                D_800A2FEC.vz = D_800A3480 - D_800A3480 * 16;
                RotMatrix(&D_800A2FEC, D_800A7530);
                goto afterRot;
            }
        } else {
            if (D_800A3460 != 0) {
                rot[0] = D_80099254[0] - D_800A3460 * 64;
                rot[1] = D_80099256[0] + D_800A3460 * 32;
                rot[2] = (D_80099258[0] + (D_800A3460 << 5)) & 0xFFF;
                if (D_800A3460 == 0xA) {
                    if (D_800A2EC8Absolute[0] == 0) {
                        if (D_800A3474 != 0) {
                            D_800A3468 = D_800A3468 - 0x20;
                            if ((D_800A3468 << 16) == 0) {
                                D_800A3474 = 0;
                            }
                        } else {
                            D_800A3468 = D_800A3468 + 0x20;
                            if ((D_800A3468 << 16 >> 16) == 0x100) {
                                D_800A3474 = 1;
                            }
                        }
                    }
                    rot[2] = rot[2] - D_800A3468;
                }
                D_800A2FEC.vz = 0;
                RotMatrix(&D_800A2FEC, D_800A7530);
                goto afterRot;
            }
        }
        rot[0] = D_80099254[(s16)loopIdx * 3] - ((s16)absA3 >> 1);
        rot[1] = D_80099256[(s16)loopIdx * 3];
        rot[2] = D_80099258[(s16)loopIdx * 3];
        angC = D_800A3480;
        D_800A2FEC.vz = angC - angC * 16;
        RotMatrix(&D_800A2FEC, D_800A7530);
    afterRot:
        if (loopIdx != 0) {
            if (D_800A3480 < 0) {
                goto doSub;
            }
        } else if (D_800A3480 > 0) {
            goto doSub;
        } else {
            goto vecSetup;
        }
        goto vecSetup;
    doSub:
        rot[0] = rot[0] - ((s16)absA3 >> 1);
    vecSetup:
        vec.vx = 0x1000 - rot[0];
        vec.vy = 0x1000 - rot[1];
        vec.vz = 0x1000 - rot[2];
        RotMatrix(&vec, &mat1);
        segIdx = 0;
        s5v = (s16)loopIdx;
        t = s5v * 2;
        fpVal = t - 1;
        t = t + s5v;
        s4Off = ((t << 6) - t) << 5;
        do {
            s2v = D_800A3464;
            if (s5v != 0) {
                if (D_800A345C != 0) {
                    if (D_800A345C < 3) {
                        D_800A3464 = s2v - D_800A345C * 160;
                    } else {
                        D_800A3464 = 0x80;
                    }
                }
            } else {
                if (D_800A3460 != 0) {
                    D_800A3464 = s2v - D_800A3460 * 36;
                }
            }
            vec.vx = 0x1000 - (s16)D_800A3464 * flagScratch[(s16)segIdx] *
                                  (flagScratch[(s16)segIdx] & 1);
            scratchW = flagScratch[(s16)segIdx];
            if ((scratchW & 1) == 0) {
                vyVal = ((s16)D_800A3464 >> 3) * scratchW * fpVal;
            } else {
                vyVal = 0;
            }
            vec.vy = vyVal;
            if (s5v == 0 && (s16)segIdx != 0 && D_800A3460 == 0xA) {
                vec.vz = D_800A3468 << 16 >> 17;
            } else {
                vec.vz = 0;
            }
            RotMatrix(&vec, &mat2);
            MulMatrix2(&mat1, &mat2);
            SetRotMatrix(&mat2);
            if ((s16)segIdx != 0) {
                mat1.t[0] = ((
                    s16 *)D_800A46A0)[(padScratch[(s16)segIdx] * 20 +
                                       unkScratch[(s16)segIdx] * 336 + s4Off) /
                                      2];
                mat1.t[1] = ((
                    s16 *)D_800A46A2)[(padScratch[(s16)segIdx] * 20 +
                                       unkScratch[(s16)segIdx] * 336 + s4Off) /
                                      2];
                mat1.t[2] = ((
                    s16 *)D_800A46A4)[(padScratch[(s16)segIdx] * 20 +
                                       unkScratch[(s16)segIdx] * 336 + s4Off) /
                                      2];
            } else {
                mat1.t[2] = 0;
                mat1.t[1] = 0;
                mat1.t[0] = 0;
            }
            SetTransMatrix(&mat1);
            D_800A3464 = s2v;
            if ((s16)segIdx != 0 || (s5v == 0 && D_800A3460 != 0)) {
                s2v = 0;
                s1v = (s16)segIdx;
            vtxLoopA:
                do {
                    rec = s4Off + gHandSegments + s1v * 336 +
                          ((s16)s2v * 20 + 0xB0);
                    vec.vx = (u32)rec->world.x;
                    vec.vy = (u32)rec->world.y;
                    vec.vz = (u32)rec->world.z;
                    RotTrans(&vec, &out, &gteFlag);
                    *(u16 *)rec = out.vx;
                    rec->local.vy = out.vy;
                } while (0);
                rec->local.vz = out.vz;
                s2v += 1;
                if (s2v < 8) {
                    goto vtxLoopA;
                }
            } else {
                s2v = 0;
                s1v = (s16)segIdx;
            vtxLoopB:
                do {
                    rec = s4Off + gHandSegments + s1v * 336 +
                          ((s16)s2v * 20 + 0xB0);
                    vec.vx = (u32)rec->world.x;
                    vec.vy = (u32)rec->world.y;
                    if ((u16)(s2v - 2) < 2 || (u16)(s2v - 6) < 2) {
                        vec.vz = (u32)rec->world.z + (s16)absA3 * 3 - 0x1E;
                    } else {
                        vec.vz = (u32)rec->world.z;
                    }
                    RotTrans(&vec, &out, &gteFlag);
                    *(u16 *)rec = out.vx;
                    rec->local.vy = out.vy;
                } while (0);
                rec->local.vz = out.vz;
                s2v += 1;
                if (s2v < 8) {
                    goto vtxLoopB;
                }
            }
            segIdx += 1;
        } while (segIdx < 0x12);
        SetRotMatrix(D_800A7530);
        if (loopIdx == 0 && D_800A3460 != 0) {
            transPtr = &mat1;
            mat1.t[0] = D_800A3460 * 4;
            mat1.t[1] = D_800A3460 * 8 + 0x64;
            mat1.t[2] = D_800A3460 * 16;
        } else {
            transPtr = D_800A7530;
        }
        SetTransMatrix(transPtr);
        if (loopIdx != 0 && D_800A345C >= 5) {
            ;
        } else {
            prim = (u8 *)gPrimitiveCursor[0];
            node = gHandSegments + (s16)loopIdx * 6048;
            primCount = 0x48;
            otBaseW = gOrderingTable[0];
            primNext = prim + 0x10;
            do {
                verts = &node->vertex[0];
                gte_ldv3(verts[0], verts[1], verts[2]);
                gte_rtpt();
                gte_avsz3();
                *(u32 *)&((POLY_F4 *)(primNext - 0x10))->r0 = *(u32 *)&node->r0;
                gte_stsxy3(prim + 8, prim + 0xC, prim + 0x14);
                gte_ldv0(verts[3]);
                gte_rtps();
                gte_stsxy(primNext);
                GraphicsAddTaggedPrimitive((u32 *)(otBaseW + node->depth * 4),
                                           (u32 *)prim, 0x05000000);
                node = node->next;
                primCount--;
                primNext += 0x18;
                prim += 0x18;
            } while (primCount > 0);
            gPrimitiveCursor[0] = (u32)prim;
        }
        loopIdx += 1;
    } while (loopIdx < 2);
}

extern s32 D_800A7544;
extern s32 D_800A7548;
extern s32 D_800A754C;

typedef struct {
    SVECTOR s;
    s32 lx;
    s32 ly;
    s32 lz;
} HandVertex;

typedef struct HandFace {
    POLY_F4 poly;
    HandVertex *verts[4];
    struct HandFace *next;
} HandFace;

typedef struct {
    HandFace faces[4];
    HandVertex verts[8];
} HandSegment;

void SceneInitHandModel(void) {
    s8 faceVerts[6][4] = {
        {1, 0, 2, 3}, {0, 4, 6, 2}, {5, 1, 3, 7},
        {4, 5, 7, 6}, {0, 1, 5, 4}, {3, 2, 6, 7},
    };
    s16 segSize[18][4][3] = {
        {{-76, -80, 6}, {-60, -80, 6}, {-76, -20, 12}, {-60, -20, 12}},
        {{-2, -20, 3}, {8, -20, 3}, {-2, -10, 4}, {0, 0, 6}},
        {{8, -20, 3}, {18, -20, 3}, {0, 0, 6}, {16, 0, 6}},
        {{2, -20, 3}, {4, -10, 4}, {0, 0, 6}, {4, -1, 5}},
        {{0, -9, 4}, {6, -11, 3}, {0, 0, 5}, {6, -6, 3}},
        {{0, -5, 3}, {4, -7, 3}, {0, 0, 3}, {5, -4, 3}},
        {{0, -6, 3}, {4, -6, 3}, {0, 0, 3}, {5, 0, 3}},
        {{-5, -8, 3}, {-1, -8, 3}, {-5, 0, 3}, {0, 0, 3}},
        {{0, -10, 3}, {4, -10, 3}, {0, 0, 3}, {5, 0, 3}},
        {{-5, -8, 3}, {-1, -8, 3}, {-5, 0, 3}, {0, 0, 3}},
        {{0, -4, 3}, {4, -4, 3}, {0, 0, 3}, {4, 0, 3}},
        {{0, -6, 3}, {4, -6, 3}, {0, 0, 3}, {4, 0, 3}},
        {{0, -6, 3}, {4, -6, 3}, {0, 0, 3}, {4, 0, 3}},
        {{0, -6, 3}, {4, -6, 3}, {0, 0, 3}, {4, 0, 3}},
        {{1, -4, 3}, {4, -4, 3}, {0, 0, 3}, {4, 0, 3}},
        {{1, -4, 3}, {4, -4, 3}, {0, 0, 3}, {4, 0, 3}},
        {{1, -4, 3}, {4, -4, 3}, {0, 0, 3}, {4, 0, 3}},
        {{0, -4, 3}, {3, -4, 3}, {0, 0, 3}, {4, 0, 3}},
    };
    HandFace *prev;
    s8 i;
    s8 j;
    s8 k;
    s8 m;
    HandSegment *seg;
    HandFace *face;

    prev = NULL;
    D_800A7548 = 100;
    D_800A7544 = 0;
    D_800A754C = 0;
    D_800A3464 = 0x1C0;
    D_800A3474 = 0;
    D_800A3470 = 0;
    D_800A346C = 0;
    D_800A3468 = 0;
    D_800A3460 = 0;
    D_800A345C = 0;
    for (i = 1; i >= 0; i--) {
        for (j = 17; j >= 0; j--) {
            seg = &((HandSegment(*)[18])gHandSegments)[i][j];
            for (k = 3; k >= 0; k--) {
                face = &seg->faces[k];
                SetPolyF4((u8 *)face);
                face->next = prev;
                prev = face;
                prev->poly.r0 = 8;
                prev->poly.g0 = 8;
                prev->poly.b0 = 8;
                ((u8 *)&prev->poly)[1] = 2;
            }
            for (k = 0; k < 4; k++) {
                for (m = 0; m < 4; m++) {
                    seg->faces[k].verts[m] = &seg->verts[faceVerts[k][m]];
                }
            }
            for (k = 0; k < 4; k++) {
                m = k + 4;
                seg->verts[k].lx = seg->verts[k].s.vx = seg->verts[m].lx =
                    seg->verts[m].s.vx = (i ? -1 : 1) * (segSize[j][k][0] << 1);
                seg->verts[k].ly = seg->verts[k].s.vy = seg->verts[m].ly =
                    seg->verts[m].s.vy = segSize[j][k][1] << 1;
                seg->verts[k].lz = seg->verts[k].s.vz = 0;
                seg->verts[m].lz = seg->verts[m].s.vz = segSize[j][k][2] << 1;
            }
        }
    }
}

extern s32 gReplayHead[];
extern s32 gReplayLength[];
extern s16 D_800A35A4w40;
extern Car *D_800A347C;
extern Car *D_800A3728;
extern u8 CarDrawModel(Car *, s32);
extern void func_8004875C(void);
extern Car *gPlayerCaragain[];
asm(".globl gPlayerCaragain\ngPlayerCaragain = gPlayerCar");
asm(".globl D_800A35A4w40\nD_800A35A4w40 = D_800A35A4");

void func_80048568(void) {
    s32 target;

    if (D_800A397C[0] == 2) {
        if (gReplayIndex[0] < gReplayHead[0]) {
            target = D_800A2EC0nm[0] - (gReplayHead[0] - gReplayIndex[0]) + 1;
        } else {
            target = D_800A2EC0nm[0] -
                     (gReplayHead[0] + (gReplayLength[0] - gReplayIndex[0])) +
                     1;
        }
        if (target >= D_800A347C->unkC && D_800A347C->unk10 >= target) {
            CarDrawModel(D_800A347C, 0);
        }
    } else if (D_800A3728 != 0) {
        if ((u8)D_800A347C->unk401 != 0) {
            CarDrawModel(D_800A347C, 0);
            if (D_800A35A4w40 <= 0 && func_80037204(D_800A3728) != 0) {
                D_800A3728 = 0;
                D_800A347C->unk10 = D_800A2EC0nm[0];
            }
        } else {
            if (func_8003702C(D_800A3728, gPlayerCar[0]) < 0) {
                if (-func_8003702C(D_800A3728, gPlayerCaragain[0]) >= 0x19) {
                    goto fail;
                }
            } else {
                if (func_8003702C(D_800A3728, gPlayerCaragain[0]) >= 0x19) {
                fail:
                    func_8004875C();
                }
            }
        }
    }
}

extern void CarInitDefaults(Car *);

void SceneCreateSceneryCar(void) {
    D_800A3728 = 0;
    D_800A347C = HeapAlloc(0x500);
    D_800A347C->type = 2;
    MatrixSetIdentity((s32 *)D_800A347C);
    CarInitDefaults(D_800A347C);
    ObjectSetModelDataVariant(D_800A347C, -4);
    D_800A347C->unk10 = -1;
    D_800A347C->unkC = -1;
}

void func_8004875C(void) {
    extern void func_80031264(Car * object);
    extern void ObjectAdvanceAlongHeading(Car * object);
    extern s32 MathMultiplyFixed16(s32, s32);
    extern s32 D_800A2EC0Absolute[];
    Car *src;
    Car *dst;
    u16 val;
    s32 t;
    Car *p;
    Car *q;
    Car *w;
    s32 e;

    val = gTrackSections[0][D_800A3728->segment].angle;
    D_800A3728->heading = val;
    D_800A3728->movementHeading = val;
    D_800A3728->fineHeading = (u16)D_800A3728->heading * 4;
    func_80031264(D_800A3728);
    ObjectAdvanceAlongHeading(D_800A3728);
    src = D_800A3728;
    dst = D_800A347C;
    dst->pos.x = (u32)src->pos.x;
    dst->pos.y = (u32)src->pos.y;
    dst->pos.z = (u32)src->pos.z;
    dst->movementHeading = dst->heading = (u16)src->heading;
    dst->fineHeading = src->fineHeading;
    ObjectAdvanceAlongHeading(dst);
    func_80031264(D_800A347C);
    t = MathMultiplyFixed16(D_800A347C->rot[0].x, 0x3200000);
    p = D_800A347C;
    p->pos.x += t >> 16;
    t = MathMultiplyFixed16(p->rot[0].y, 0x3200000);
    p = D_800A347C;
    p->pos.y += t >> 16;
    t = MathMultiplyFixed16(p->rot[0].z, 0x3200000);
    q = D_800A347C;
    q->unk401 = 1;
    t = q->pos.z + (t >> 16);
    w = D_800A347C;
    e = D_800A2EC0Absolute[0];
    q->pos.z = t;
    w->unkC = e;
    w->unk10 = 0x7FFFFFFF;
}

void SceneSetCameraTarget(Car *object) {
    Car *state;
    state = D_800A347C;
    object->speed = 0;
    D_800A3728 = object;
    state->unk401 = 0;
}

typedef struct CrashBox {
    u8 unk0[4];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 unk10[0x1C - 0x10];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
} CrashBox;

typedef struct {
    u8 unk0[0x20];
    s16 unk20;
    u8 unk22[0xC8 - 0x22];
} Unk800B8648;

extern Car *D_800A7550p[] asm("D_800A7550");
extern Car *gCrashCarSmall asm("gCrashCar");
extern u8 D_800A35F8;
extern u8 D_800A35FC;
extern s32 D_800A2F50Absolute[];
extern s32 D_800A3804Nm[] asm("D_800A3804.NON_MATCHING");
extern Unk800B8648 D_800B8648[];

void RaceUpdateCrashTrigger(void) {
    s32 pos[3];
    s8 i;
    Car *car;
    CrashBox *box;
    Unk800B8648 *row;

    if (D_800A35FC != 0 &&
        D_800A2EC0Absolute[0] == D_800A2EC0Absolute[0] / 200 * 200 &&
        D_800A2EC8[0] == 0) {
        if (gCrashCarSmall == NULL) {
            if (D_800A372C == 0) {
                for (i = 0; i < D_800A35FC; i++) {
                    car = D_800A7550p[i];
                    if (car->unk414 != -1) {
                        if (car->unk268 == 0) {
                            if (car->unk414 != 0) {
                                car->unk414 -= 1;
                            } else if (car->type != 0
                                           ? D_800A2F50Absolute[0] * 9 / 10 <
                                                 ((s16 *)&car->speed)[1]
                                           : car->maxSpeed - 0xA0000 <
                                                 car->speed) {
                                D_800A35F8 = 1;
                                car->unk414 = -1;
                                car->unk26C[5] = 1;
                                car->unk3A4 |= 0x1000;
                                func_80041848(car, 13);
                                gCrashCarSmall = car;
                            }
                        }
                    }
                }
            }
        }
    }
    if (gCrashCarSmall == NULL || D_800A2ED4[0] != 0) {
        if (D_800A397C[0] == 2 && gCrashCarSmall == NULL &&
            gReplayIndex[0] == D_800A3804Nm[0]) {
            row = D_800B8648;
            for (i = 0; i < 24; i++) {
                row->unk20 = 0;
                row++;
            }
        }
    } else {
        if (gCrashCarSmall->unkF4 == 0) {
            gCrashCarSmall = NULL;
            return;
        }
        if (D_800A397C[0] == 2 &&
            (gCrashCarSmall->speed != 0 || gCrashCarSmall->unk38A != 0x200)) {
            row = D_800B8648;
            for (i = 0; i < 24; i++) {
                row->unk20 = 0;
                row++;
            }
            if (gCrashCarSmall->unk38A != 0x200) {
                return;
            }
        }
        box = (CrashBox *)gCrashCarSmall->shape->parts;
        pos[0] = (box->unk4 + box->unk1C) >> 1;
        pos[1] = (box->unk8 + box->unk20) >> 1;
        pos[2] = (box->unkC + box->unk24) >> 1;
        func_8001EEC4(gCrashCarSmall);
        MatrixRotateVector(pos);
        pos[0] += gCrashCarSmall->pos.x + RandomScaledGet(200) - 100;
        pos[1] += gCrashCarSmall->pos.y + RandomScaledGet(200) - 100;
        pos[2] += gCrashCarSmall->pos.z + 100;
        func_8003644C(D_800A35F8 == 1 ? 2 : 1, pos[0], pos[1], pos[2]);
    }
}

extern u8 D_800A38F0;
extern u8 D_800A35FCnm asm("D_800A35FC.NON_MATCHING");
extern s32 D_800A37D0[];
extern s32 D_800A37D4nm[] asm("D_800A37D4.NON_MATCHING");
extern s32 D_800A7550[];

void RaceInitCrashCandidates(void) {
    extern s32 D_800A2E94nm[] asm("D_800A2E94.NON_MATCHING");
    s8 buf[24];
    s8 *p;
    s8 i;
    s8 j;
    s8 idx;
    Car *node;
    s32 scale;
    s32 count;
    s32 limit;
    register s32 raw asm("$2");
    s32 a1val;
    s32 r0;
    s32 r2;
    s32 cnt;

    if (D_800A38F0 == 0 || (count = gSessionTypeAbsolute[0]) != 0) {
        D_800A35FCnm = 0;
        return;
    }
    r0 = RandomScaledGet((D_800A37D0[0] - 1) / 50 + 3);
    cnt = D_800A2E94[0];
    limit = 0x18 / cnt;
    D_800A35FCnm = ((D_800A37D4nm[-1] + 0x18) / 50 + r0) / limit;
    if (count < cnt) {
        i = 0;
        p = buf;
    clear:
        p[i] = 0;
        i++;
        if (i < D_800A2E94nm[0]) {
            goto clear;
        }
    }
    scale = MathFixedDivide(D_800AE1EC[0] * 0x14, 0x7D00);
    for (i = 0; i < D_800A35FCnm; i++) {
        do {
            raw = RandomScaledGet(D_800A2E94[0]);
            idx = (s8)raw;
        } while (buf[idx] != 0);
        count = raw;
        node = gCarListnm[0];
        for (j = 0; j < idx; j++) {
            node = node->next;
        }
        a1val = D_800A2EA8[0];
        D_800A7550[i] = node;
        r2 = RandomScaledGet(MathMultiplyFixed16(scale, (a1val - 1) << 16) >>
                             16);
        node->unk414 = (scale >> 16) + r2;
        buf[(s8)count] = 1;
    }
}

/* Draws the race HUD for one car: the tachometer segments, speed bar and
 * needle, lap and place text, and the driver warning messages. yOffset moves
 * the whole layout vertically (split screen). The field names are placeholders
 * until the full Car layout is known. */

typedef struct HudLayout {
    s16 unk0;
    s16 unk2;
    u8 unk4[4];
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    u8 unk1C[0x1C];
} HudLayout;

typedef struct HudPoint {
    u16 x;
    u16 y;
} HudPoint;

typedef struct HudVertex {
    s16 x;
    s16 y;
} HudVertex;

extern s16 D_800A38E4[];
extern s32 gOrderingTableAbsolute[];
extern s32 D_800A39C4nm[] asm("D_800A39C4.NON_MATCHING");
extern s32 D_800A39CCnm[] asm("D_800A39CC.NON_MATCHING");
extern s32 D_800A2E50[];
extern s8 *D_800A78C4[];
extern u8 D_800A3490;
extern u8 D_800A3485;
extern u8 D_800A3488;
extern u8 D_800A3484[];
extern u8 D_800A3680Small asm("D_800A3680.NON_MATCHING");
extern s32 D_800A2ED0Hud[] asm("D_800A2ED0.NON_MATCHING");
extern s16 D_800A3910;
extern u8 D_80099260[][0x38];
extern HudLayout D_8009927C[];
extern HudVertex D_8009933C[];
extern u8 D_800A7568[];
extern u8 D_800A7569[];
extern u8 D_800A756A[];
extern u16 D_800A756C[];
extern u16 D_800A756E[];
extern u16 D_800A7570[];
extern u16 D_800A7572[];
extern u16 D_800A7574[];
extern u16 D_800A7576[];
extern u16 D_800A7578[];
extern u16 D_800A757A[];
extern POLY_FT4 D_800A757C[];
extern POLY_FT4 D_800A770C[];
extern TILE D_800A7924[];
extern TILE D_800A7954[];
extern u8 D_800A78D4[];
extern u8 D_800A78FC[];
extern char gTextDoubleDash[];
extern char gFormatWidth3Integer[];
extern char gFormatIntegerDashInteger[];
extern char *D_8009ADD8[];
extern char *D_8009ADF8[];
extern char *D_8009ADFC[];
extern char *D_8009AE00[];
extern char *D_8009AE0C[];
extern char *D_8009AE10[];
extern s32 sprintfHud(char *, char *, ...) asm("sprintf");
extern void func_8004AFE0(s8, u16 *, u16 *);
extern void func_800188B0(s32, s32, s32, s32, s32);
extern void GraphicsSetColor(u8, u8, u8);
extern s16 HudTextWidthS16(u8 *) asm("HudTextWidth");
extern void HudDrawTextS16(char *, s32, s16, s32) asm("HudDrawText");
extern void SoundStopConditionalSlots(s8);
extern void func_80041564Hud(Car *, s32) asm("func_80041564");

/* Value that D_800A3480 follows, the field at 0x20E of the car in
 * gPlayerCar. */
#define HUD_STEER_TARGET (gPlayerCar[0]->steering)

/* Centred warning text with a box behind it. */
#define HUD_MESSAGE(text, ty)                                                  \
    {                                                                          \
        s16 w;                                                                 \
        s32 x;                                                                 \
        w = HudTextWidthS16((u8 *)(text)[0]);                                  \
        x = (0x140 - w) >> 1;                                                  \
        HudDrawTextS16((text)[0], x, yOffset + (ty), 0);                       \
        GraphicsDrawDoubleBorderRect(x - 0xA, yOffset + (ty) - 1, w + 0x14,    \
                                     0xD, 0, 0, 0, 1);                         \
    }

void HudDrawCar(Car *car, s16 yOffset) {
    char buf[8];
    HudPoint pts[4];
    u16 ang;
    u8 flag;
    u8 split;
    s8 level;
    s8 cur;
    s8 nv;
    s16 i;
    POLY_FT4 *seg;
    TILE *tiles;
    u8 *needle;
    u8 *prim;
    u8 count;
    s16 tw;
    s32 cosV;
    s32 sinV;
    s16 idx;
    s32 scaled;
    s32 green;
    u8 red;
    s32 frac;
    HudLayout *layout;

    split = 0;
    flag = 0;
    if (car->cameraMode != 0 || gSplitScreenMode[0] != 0) {
        split = 1;
    }
    if (D_800A2ED4[0] == 0) {
        if (car->unk3FC != 0) {
            level =
                (s32)((D_800A2E50[0] - D_800A38E4[0]) * 10) / D_800A2E50[0] + 2;
        } else {
            level = 0;
        }
        if (level >= 11) {
            level = 10;
        }
        cur = car->unk3FD;
        if (cur < level) {
            car->unk3FD = cur + 1;
        } else if (level < cur) {
            car->unk3FD = cur - 1;
        }
        if (D_800A372C != 0 && (u8)car->unk401 != 0) {
            car->unk402 =
                car->unk402 <= car->rpm - 0x64
                    ? car->unk402 + 0x64
                    : (car->unk402 >= car->rpm + 0x64 ? car->unk402 - 0x64
                                                      : car->rpm);
            car->unk40C = car->speed - 0x10000 >= car->unk40C
                              ? car->unk40C + 0x10000
                              : (car->unk40C >= car->speed + 0x10000
                                     ? car->unk40C - 0x10000
                                     : car->speed);
        } else {
            car->unk402 =
                car->unk402 <= car->rpm - 0x3E8
                    ? car->unk402 + 0x3E8
                    : (car->unk402 >= car->rpm + 0x3E8 ? car->unk402 - 0x3E8
                                                       : car->rpm);
            car->unk40C = car->speed - 0x140000 >= car->unk40C
                              ? car->unk40C + 0x140000
                              : (car->unk40C >= car->speed + 0x140000
                                     ? car->unk40C - 0x140000
                                     : car->speed);
        }
        /* D_800A3480 eases toward the target by 1, 4 or 8 a frame and is then
         * clamped. The three stores in the first arms name the byte three ways
         * so that gcc does not cross-jump them into the shared store. */
        i = ABS(D_800A3480 - HUD_STEER_TARGET);
        if (i < 5) {
            if (D_800A3480 < HUD_STEER_TARGET) {
                nv = D_800A3480 + 1;
                (&D_800A3460)[0x20] = nv;
            } else if (HUD_STEER_TARGET < D_800A3480) {
                nv = D_800A3480 - 1;
                (&D_800A345C)[0x24] = nv;
            } else {
                nv = HUD_STEER_TARGET;
                D_800A3480 = nv;
            }
        } else if (i < 13) {
            nv =
                D_800A3480 < HUD_STEER_TARGET ? D_800A3480 + 4 : D_800A3480 - 4;
            D_800A3480 = nv;
        } else {
            nv =
                D_800A3480 < HUD_STEER_TARGET ? D_800A3480 + 8 : D_800A3480 - 8;
            D_800A3480 = nv;
        }
        if (nv >= 0x35) {
            D_800A3480 = 0x34;
        } else if (nv < -0x34) {
            D_800A3480 = -0x34;
        }
    }
    if (gSplitScreenMode[0] == 0) {
        if (D_800A3680Small != 0) {
            func_8004AFE0(0, (u16 *)D_80099260[split],
                          (u16 *)D_800A78C4[gOrderingTableBankAbsolute[0]]);
            D_800A3490 = 1;
            D_800A3680Small = 0;
        } else if (D_800A3490 != 0) {
            func_8004AFE0(0, (u16 *)D_80099260[split],
                          (u16 *)D_800A78C4[gOrderingTableBankAbsolute[0]]);
            D_800A3490 = 0;
        }
    }
    if (D_800A2EACAbsolute[0] == 0 && D_800A2ED0Hud[0] == 0 &&
        D_800A397C[0] != 2) {
        if (car->unk209 != 0) {
            gOrderingTableAbsolute[0] = gOrderingTable[0] + 4;
            if (split) {
                if (car == gPlayerCar[0]) {
                    seg = D_800A757C;
                    needle = D_800A78D4;
                    tiles = D_800A7924;
                } else {
                    seg = D_800A770C;
                    needle = D_800A78FC;
                    tiles = D_800A7954;
                }
                for (i = 0; i < car->unk3FD; i++) {
                    seg[i].b0 = 0xFF;
                    GraphicsAddPolyFT4((u8 *)&seg[i]);
                }
                for (i = car->unk3FD; i < 10; i++) {
                    seg[i].b0 = 0x40;
                    GraphicsAddPolyFT4((u8 *)&seg[i]);
                }
                tw = car->unk28C / 400;
                tiles[1].x0 = tw + 0xD;
                tiles[0].w = tw;
                tiles[1].w = 0x28 - tw;
                for (i = 0; i < 3; i++) {
                    GraphicsAddPolyFT4((u8 *)&tiles[i]);
                }
                ang = (car->unk402 * 0x1F40) / 13250 + 0x3E8;
                scaled = (s16)ang << 8;
                idx = (car->automatic != 0 || car->gearIndex == car->unk110 ||
                               D_800A2F58Absolute[0] != 0
                           ? scaled / 10000
                           : scaled / 9000) +
                      0x200;
                cosV = gCosTableAbsolute[0][idx];
                sinV = gSinTableAbsolute[0][idx];
                for (i = 0; i < 4; i++) {
                    pts[i].x =
                        ((MathMultiplyFixed16(cosV, D_8009933C[i].x << 16) -
                          MathMultiplyFixed16(sinV, D_8009933C[i].y << 16)) >>
                         16) +
                        0x12C;
                    pts[i].y =
                        ((MathMultiplyFixed16(sinV, D_8009933C[i].x << 16) +
                          MathMultiplyFixed16(cosV, D_8009933C[i].y << 16)) >>
                         16) +
                        (yOffset + 0xD6);
                }
                if ((s16)ang < 3000) {
                    D_800A7568[0] = 0;
                    green = 0x80;
                } else {
                    frac = ((s16)((s16)ang % 3000) << 7) / 3000;
                    red = frac; /* separate byte copy of the quotient */
                    if ((s16)ang < 6000) {
                        D_800A7568[0] = red;
                        green = 0x80;
                    } else {
                        D_800A7568[0] = 0x80;
                        green = 0x80 - frac;
                    }
                }
                D_800A7569[0] = green;
                D_800A756A[0] = 0;
                /* Ends the scheduling block: the stores above stay ahead of
                 * the loads below. The branch itself is removed. */
                if (i == -1) {
                    i = 0;
                }
                D_800A756C[0] = pts[0].x;
                D_800A756E[0] = pts[0].y;
                D_800A7570[0] = pts[1].x;
                D_800A7572[0] = pts[1].y;
                D_800A7574[0] = pts[2].x;
                D_800A7576[0] = pts[2].y;
                D_800A7578[0] = pts[3].x;
                D_800A757A[0] = pts[3].y;
                GraphicsAddPolyFT4((u8 *)D_800A756C - 8);
                GraphicsAddPolyFT4(needle);
                count = D_800A3484[split];
                prim = (u8 *)D_800A78C4[gOrderingTableBankAbsolute[0]];
            } else {
                count = D_800A3485 - D_800A3488;
                prim = (u8 *)D_800A78C4[gOrderingTableBankAbsolute[0]] +
                       D_800A3488 * 0x28;
            }
            FontSetColor(0x80, 0x80, 0x40);
            for (i = 0; i < count; i++) {
                AddPrim((void *)gOrderingTable[0], prim);
                prim += 0x28;
            }
            layout = &D_8009927C[split];
            if (gSessionTypeAbsolute[0] == 2) {
                FontDrawString(gTextDoubleDash, layout->unk8,
                               layout->unkA + yOffset, 2);
                sprintfHud(buf, gFormatWidth3Integer, car->lap);
            } else {
                func_80018B18(car->place,
                              layout->unk8 + (gSplitScreenMode[0] != 0 ? 5 : 0),
                              layout->unkA + yOffset, 2);
                sprintfHud(buf, gFormatIntegerDashInteger, car->lap,
                           D_800A2EA8[0]);
            }
            FontDrawString(buf, layout->unkC, layout->unkE + yOffset, 2);
            func_80018768((void *)(car->lap != 0 ? car->unk258 : 0x7FFFFFFF),
                          layout->unk10, layout->unk12 + yOffset, 2);
            func_80018768((void *)car->time, layout->unk14,
                          layout->unk16 + yOffset, 2);
            if (split) {
                func_800188B0(car->unk40C, car->unkF7, layout->unk0,
                              layout->unk2 + yOffset, 2);
                func_80018B18(car->gearIndex + 1, layout->unk18,
                              layout->unk1A + yOffset, 2);
            } else {
                gOrderingTableAbsolute[0] = gOrderingTablenm[0] + 0x2C;
                FontSetColor(0x40, 0x40, 0x40);
                func_80018B18(car->gearIndex + 1, layout->unk18,
                              layout->unk1A + yOffset, 2);
                gOrderingTableAbsolute3[0] = gOrderingTableAbsolute8[0] - 0x2C;
            }
            gOrderingTableAbsolute[0] = gOrderingTable[0] - 4;
        }
        if (D_800A2EC8[0] == 0) {
            if (D_800A2EDC[0] != 0 && car->unkF4 != 0 &&
                (car->callback != func_80025730
                     ? (*(u32 *)&car->unk3A4 & 0x100F) != 0
                     : car->unk1BC == 4)) {
                if (D_800A2EE0[0] != 0) {
                    if (car->unk3B7 == 0) {
                        GraphicsSetColor(0xFF, 0x40, 0x40);
                        HUD_MESSAGE(D_8009ADD8, 0xA5);
                    }
                } else if (car->speed == 0) {
                    car->sliding = 0;
                    car->speed = 0;
                    car->unk84 = 0;
                    car->reverseSpeed = 0;
                    car->unk414 = -1;
                    SoundStopConditionalSlots(0);
                    func_80041564Hud(car, 0x44);
                    car->unkF4 = 0;
                }
                flag = 1;
                D_800A3910 = 0x7FFF;
            }
            if (gSplitScreenMode[0] != 0 && D_800A2EDC[0] != 0 &&
                D_800A2EE0[0] == 0 && (*(u32 *)&car->unk3A4 & 0x100F)) {
                GraphicsSetColor(0xFF, 0x40, 0x40);
                HUD_MESSAGE(D_8009AE10, 0xD2);
                return;
            }
            if (car->unk268 == 0) {
                if (car->unk28C == 0) {
                    GraphicsSetColor(0xFF, 0x40, 0x40);
                    HUD_MESSAGE(D_8009ADFC, 0xB4);
                    if (car->unkF4 != 0 && car->speed == 0) {
                        car->unk414 = -1;
                        SoundStopSlot((s8)((u8)car->slot * 2 + 0xE));
                        func_80041564Hud(car, 0x44);
                        car->unkF4 = 0;
                    }
                } else if (flag == 0) {
                    if (car->unk28C < 0x800) {
                        GraphicsSetColor(0xFF, (car->unk28C >> 4) + 0x40, 0x40);
                        HUD_MESSAGE(D_8009AE0C, 0xB4);
                        func_80041564Hud(car, 0x41);
                    }
                    if (car->wheel[0].unkC <= 0xCE3FF) {
                        GraphicsSetColor(
                            0xFF,
                            (((car->wheel[0].unkC - 0xA0000) << 7) / 189440) +
                                0x40,
                            0x40);
                        HUD_MESSAGE(D_8009ADF8, 0xC3);
                        func_80041564Hud(car, 0x48);
                    }
                    if (ABS(MathGetAngleDelta(
                            car->heading,
                            gTrackSections[0][car->segment].angle)) > 0x120) {
                        GraphicsSetColor(0xFF, 0x40, 0x40);
                        HUD_MESSAGE(D_8009AE00, 0xD2);
                        func_80041564Hud(car, 0x25);
                    }
                }
            }
        }
    }
}

extern u8 D_800A2ED8[];
extern u16 D_800A348C;
extern POLY_FT4 D_800A789C[];
extern TILE D_800A7984[];
extern s8 D_800A2FD4[4];
extern u32 gGlareCursorLui asm("gPrimitiveCursorAbsolute");
extern s32 D_800A38AC[];

void SceneDrawSunGlare(Car *car) {
    VECTOR sunDir;
    MATRIX unused;
    SVECTOR sun;
    SVECTOR flare[3];
    VECTOR screen;
    s32 flag;
    s16 angle;
    s16 glare;
    s16 depth;
    s8 i;
    s32 x;
    s32 y;
    s32 size;
    POLY_FT4 *wash;
    u32 cursor;
    POLY_FT4 *prim;
    u32 entry;

    if (D_800A359C[0] != 0 || gSplitScreenMode[0] != 0 || D_800A2ED8[0] != 0) {
        return;
    }
    MatrixLoadObjectBasis((s32 *)D_800A38AC[0]);
    sunDir.vx = 0x400;
    sunDir.vy = 0;
    sunDir.vz = 0;
    MatrixTransformVector((s32 *)&sunDir);
    angle = 0x3FF - func_800358EC((s32 *)&sunDir);
    D_800A348C = angle;
    if (D_800A2CE0[0] == 3 && D_800A3A60gp != 0) {
        return;
    }
    if (car->cameraMode != 6) {
        if (angle < 0x200) {
            glare = 0xFF - angle;
        } else {
            glare = angle - 0x301;
        }
    } else {
        glare = 0;
    }
    if (glare <= 0) {
        return;
    }
    if (car->cameraMode == 0) {
        D_800A7984[0].r0 = glare;
        D_800A7984[0].g0 = glare;
        D_800A7984[0].b0 = glare;
        cursor = gPrimitiveCursor[0];
        gGlareCursorLui = cursor + sizeof(POLY_FT4);
        wash = (POLY_FT4 *)cursor;
        *wash = *(POLY_FT4 *)D_800A7984;
        AddPrim((void *)(gOrderingTable[0] + 8), wash);
    }
    glare >>= 1;
    sun.vx = D_800AE844[0];
    sun.vy = 0;
    sun.vz = D_800AE84C[0] + 10000;
    RotTrans(&sun, &screen, &flag);
    depth = screen.vz - 200;
    flare[0].vx = screen.vx >> 8;
    flare[0].vy = screen.vy >> 8;
    flare[0].vz = (depth >> 8) + 200;
    flare[1].vx = screen.vx >> 9;
    flare[1].vy = screen.vy >> 9;
    flare[1].vz = (depth >> 9) + 200;
    flare[2].vx = -(screen.vx >> 10);
    flare[2].vy = -(screen.vy >> 10);
    flare[2].vz = -(depth >> 10) + 200;
    for (i = 0; i < 3; i++) {
        x = (MathMultiplyFixed16(
                 MathFixedDivide(flare[i].vx, flare[i].vz) & ~0xF, 0xD00000) >>
             16) +
            0xA0;
        y = (MathMultiplyFixed16(
                 MathFixedDivide(flare[i].vy, flare[i].vz) & ~0xF, 0xD00000) >>
             16) +
            0x78;
        size = (i + 3) * 4;
        if (i == 0) {
            D_800A789C[0].r0 = glare;
            D_800A789C[0].g0 = 0;
            D_800A789C[0].b0 = 0;
        } else if (i == 1) {
            D_800A789C[0].r0 = glare;
            D_800A789C[0].g0 = glare >> 1;
            D_800A789C[0].b0 = 0;
        } else {
            D_800A789C[0].r0 = glare;
            D_800A789C[0].g0 = glare;
            D_800A789C[0].b0 = 0;
        }
        /* Always true, but retail keeps the copy end inside the loop. */
        if (flare != NULL) {
            D_800A789C[0].x0 = x - size;
            D_800A789C[0].y0 = D_800A2FD4[D_800A2ED9[0]] + (y - size);
            D_800A789C[0].x1 = x - size + size * 2;
            D_800A789C[0].y1 = D_800A2FD4[D_800A2ED9[0]] + (y - size);
            D_800A789C[0].x2 = x - size;
            D_800A789C[0].y2 =
                D_800A2FD4[D_800A2ED9[0]] + (y - size) + size * 2;
            D_800A789C[0].x3 = x - size + size * 2;
            D_800A789C[0].y3 =
                D_800A2FD4[D_800A2ED9[0]] + (y - size) + size * 2;
        }
        entry = gGlareCursorLui;
        gGlareCursorLui = entry + sizeof(POLY_FT4);
        prim = (POLY_FT4 *)entry;
        *prim = D_800A789C[0];
        AddPrim((void *)(gOrderingTable[0] + 8), prim);
    }
}

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
void HudInitRacePrims(void) {
    extern u8 D_800B0B7C[]; /* reached only from retail's asm */
    HudTexture *tex;
    POLY_FT4 *prim;
    TILE *p3;
    TILE *p4;
    u8 *f4base;
    s32 tileIndex;
    s32 tileBytes;
    s32 tileX;
    u8 *tileHeightBase;
    POLY_FT4 *heap;
    Glyph *glyph;
    s8 entry;
    s8 col;
    s8 line;
    s8 j;
    s8 row;
    u16 *page;
    s32 markerOffset;
    u8 *driver;
    u8 driverR;
    register s32 line24;
    s8 **slot;
    s8 **lineSlot;
    s32 glyphOffset;
    s32 cornerOffset;
    s32 value;
    u8 *slotBase;
    u8 *coord;
    POLY_FT4 *driverCall;
    u8 *driverBase;
    u32 borderFlag;
    u16 markerPage;
    register u8 *mapCall;
    POLY_FT4 *mapPrim;
    register s32 view;
    register u8 *coordX;
    s32 coordinateValue;
    register u8 *coordY;
    register s32 yOffset;

    D_800A3680[0] = 0;
    D_800A3490 = 0;
    D_800A2FD0[0] = -(gSplitScreenMode[0] != 0) & 0x92;
    for (entry = 0; entry < D_800A3424; entry++) {
        D_800A3485 = 0;
        for (col = 0; col < 6; col++) {
            {
                register u8 *addressBase;

                /* la addressBase, D_8009AE14; addu */
                addressBase = D_8009AE14;
                lineSlot = (s8 **)(addressBase + col * 4);
            }
            D_800A3485 += strlen((char *)*lineSlot);
        }
        D_800A3484Small = D_800A3485 + strlen((char *)D_8009AE2C[0]);
        for (col = 0; col < 3; col += 2) {
            line = 0;
            heap = (POLY_FT4 *)((u8 *)HeapAlloc(D_800A3484Small * 0x28));
            D_800A78C4[(s8)(entry + col)] = (s8 *)heap;
            for (; line < 7; line++) {
                j = 0;
                line24 = line << 24;
                {
                    register u8 *addressBase;

                    /* la addressBase, D_8009AE14; addu */
                    addressBase = D_8009AE14;
                    lineSlot = (s8 **)(addressBase + (line24 >> 22));
                }
                if ((*lineSlot)[0] != 0) {
                    do {
                        {
                            register u8 *addressBase;

                            do {
                                glyphOffset = line24 >> 22;
                            } while (0);
                            addressBase = (u8 *)D_8009AE14;
                            slot =
                                (s8 **)((u32)(glyphOffset) - -(u32)addressBase);
                        }
                        glyph = &gHudGlyphs[(*slot)[j]];
                        SetPolyFT4(heap);
                        heap->clut = GetClut(0x390, 0x3C);
                        heap->r0 = 0x80;
                        heap->g0 = 0x80;
                        heap->b0 = 0xC0;
                        heap->tpage = GetTPage(0, 0, glyph->x, glyph->y);
                        heap->u0 = glyph->u;
                        heap->v0 = glyph->v;
                        heap->u1 = glyph->u + *(u8 *)&glyph->width;
                        heap->v1 = glyph->v;
                        heap->u2 = glyph->u;
                        heap->v2 = glyph->v + *(u8 *)&glyph->height;
                        heap->u3 = glyph->u + *(u8 *)&glyph->width;
                        heap->v3 = glyph->v + *(u8 *)&glyph->height;
                        j++;
                        heap++;
                    } while ((*slot)[j] != 0);
                }
            }
        }
        row = entry;
        func_8004AFE0(row, D_80099298, (u16 *)D_800A78C4[row]);
        {
            register u8 *addressBase;

            /* la addressBase, D_800A78CC; addu */
            addressBase = (u8 *)D_800A78CC;
            slotBase = addressBase + row * 4;
        }
        func_8004AFE0(row, D_80099298, *(u16 **)slotBase);
        D_800A3488 = strlen((char *)((s8 **)D_8009AE14)[0]);
        prim = (POLY_FT4 *)((u8 *)D_800A78D4 + row * 0x28);
        SetPolyFT4(prim);
        SetSemiTrans(prim, 1);
        prim->code |= 1;
        prim->u0 = D_80090FF2[0];
        prim->v0 = D_80090FF4[0];
        prim->u1 = D_80090FF2a[0] + 0x3C;
        prim->v1 = D_80090FF4a[0];
        prim->u2 = D_80090FF2b[0];
        prim->v2 = D_80090FF4b[0] + 0x3C;
        prim->u3 = D_80090FF2c[0] + 0x3C;
        prim->v3 = D_80090FF4c[0] + 0x3C;
        prim->x0 = 0xF5;
        prim->y0 = D_800A2FD0[row] + 0xA0;
        prim->x1 = 0x131;
        prim->y1 = D_800A2FD0[row] + 0xA0;
        prim->x2 = 0xF5;
        prim->y2 = D_800A2FD0[row] + 0xDC;
        prim->x3 = 0x131;
        prim->y3 = D_800A2FD0[row] + 0xDC;
        *(u16 *)((u8 *)D_800A78E2 + row * 0x28) =
            GetClut(D_80090FEE[0], D_80090FF0[0]);
        tex = D_80090FEA;
        asm("" : "=r"(view) : "0"((s32)row));
        *(u16 *)((u8 *)D_800A78EA + row * 0x28) =
            GetTPage(D_80090FF6[0], 0, tex->tpx, D_80090FEC[0]);
        tex -= 14;
        for (col = 0; col < 10; col++) {
            {
                register u8 *addressBase;

                /* la addressBase, D_800A757C; addu with the column offset */
                addressBase = (u8 *)D_800A757C;
                mapCall = addressBase + col * 0x28;
            }
            mapCall = (u8 *)((u32)(view * 0x190) + (u32)mapCall);
            SetPolyFT4((POLY_FT4 *)mapCall);
            SetShadeTex(mapCall, 0);
            {
                register u8 *addressBase;

                /* la addressBase, D_800A757C; addu */
                addressBase = (u8 *)D_800A757C;
                mapPrim = (POLY_FT4 *)(addressBase + view * 0x190 + col * 0x28);
            }
            mapPrim->r0 = 0x40;
            mapPrim->g0 = 0x40;
            mapPrim->b0 = 0x40;
            mapPrim->u0 = tex->u + 0x60;
            mapPrim->v0 = tex->v;
            mapPrim->u1 = tex->u + 0x6F;
            mapPrim->v1 = tex->v;
            mapPrim->u2 = tex->u + 0x60;
            mapPrim->v2 = tex->v + 0xF;
            mapPrim->u3 = tex->u + 0x6F;
            mapPrim->v3 = tex->v + 0xF;
            *(u16 *)(view * 0x190 + col * 0x28 + (u8 *)D_800A7592) =
                GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
            {
                register s32 cornerPrefix;

                cornerPrefix = col * 12;
                coord = (u8 *)gCosTableAbsolute[0];
                cornerPrefix += col;
                cornerPrefix = cornerPrefix * 8 + 0x828;
                cornerOffset = cornerPrefix;
            }
            value = MathMultiplyFixed16(
                0x370000, *(s32 *)((u32)cornerOffset + (u32)coord));
            coordY = (u8 *)gSinTableMap0[0];
            mapPrim->x0 = (value >> 0x10) + 0x12C;
            coordY = (u8 *)((u32)cornerOffset + (u32)coordY);
            value = MathMultiplyFixed16(0x370000, *(s32 *)coordY);
            asm("" : "=r"(yOffset) : "0"((s32)(u8)D_800A2FD0[view]));
            coordX = (u8 *)gCosTableAbsolute[0];
            value >>= 0x10;
            yOffset = (s8)yOffset + 0xD7;
            coordX = (u8 *)((u32)cornerOffset + (u32)coordX);
            value += yOffset;
            asm("" : "=r"(value) : "0"(value), "r"(coordX));
            mapPrim->y0 = value;
            coordinateValue = *(s32 *)coordX;
            value = MathMultiplyFixed16(0x370000, coordinateValue);
            coordY = (u8 *)gSinTableMap1[0];
            mapPrim->x1 = (value >> 0x10) + 0x130;
            coordY = (u8 *)((u32)cornerOffset + (u32)coordY);
            value = MathMultiplyFixed16(0x370000, *(s32 *)coordY);
            asm("" : "=r"(yOffset) : "0"((s32)(u8)D_800A2FD0[view]));
            coordX = (u8 *)gCosTableAbsolute[0];
            value >>= 0x10;
            yOffset = (s8)yOffset + 0xD7;
            coordX = (u8 *)((u32)cornerOffset + (u32)coordX);
            value += yOffset;
            asm("" : "=r"(value) : "0"(value), "r"(coordX));
            mapPrim->y1 = value;
            coordinateValue = *(s32 *)coordX;
            value = MathMultiplyFixed16(0x370000, coordinateValue);
            coordY = (u8 *)gSinTableMap2[0];
            mapPrim->x2 = (value >> 0x10) + 0x12C;
            coordY = (u8 *)((u32)cornerOffset + (u32)coordY);
            value = MathMultiplyFixed16(0x370000, *(s32 *)coordY);
            coordX = (u8 *)gCosTableAbsolute[0];
            mapPrim->y2 = (value >> 0x10) + D_800A2FD0[view] + 0xDB;
            coordX = (u8 *)((u32)cornerOffset + (u32)coordX);
            coordinateValue = *(s32 *)coordX;
            value = MathMultiplyFixed16(0x370000, coordinateValue);
            coordY = (u8 *)gSinTableMap3[0];
            mapPrim->x3 = (value >> 0x10) + 0x130;
            cornerOffset += (u32)coordY;
            value = MathMultiplyFixed16(0x370000, *(s32 *)cornerOffset);
            mapPrim->y3 = (value >> 0x10) + D_800A2FD0[view] + 0xDB;
        }
        col = 0;
        tileIndex = (s8)entry;
        tileBytes = tileIndex * 0x30;
        f4base = (u8 *)D_800A7924;
        /* Keep these locals multi-set so loop.c does not hoist their values. */
        for (; col < 3; col++) {
            p3 = (TILE *)((u8 *)((u32)(col * 0x10) + (u32)f4base));
            p3 = (TILE *)((u32)tileBytes - -(u32)p3);
            SetTile(p3);
            SetSemiTrans(p3, 1);
            p4 = (TILE *)((u8 *)((u32)tileBytes + (u32)(col * 0x10) +
                                 (u32)f4base));
            tileX = 0xD;
            p4->x0 = tileX;
            tileX = 0;
            p4->y0 = D_800A2FD0[tileIndex] + 0xD3;
            tileHeightBase = (u8 *)D_800A7932;
            *(u16 *)(tileBytes + col * 0x10 + tileHeightBase) = 6;
            tileHeightBase = 0;
        }
        {
            register s32 tileRow;
            u8 *green;
            register u8 *red;
            u8 *back;
            s32 offset;
            s32 color;

            tileRow = (s8)entry;
            red = (u8 *)D_800A7924;
            offset = tileRow * 0x30;
            green = (u8 *)((u32)offset + (u32)red);
            do {
                color = 0xFF;
                red += 0x10;
            } while (0);
            red = (u8 *)((u32)offset + (u32)red);
            {
                register u8 *addressBase;

                addressBase = (u8 *)D_800A7944;
                back = (u8 *)((u32)(offset) - -(u32)addressBase);
            }
            ((TILE *)green)->r0 = 0;
            ((TILE *)green)->g0 = color;
            ((TILE *)green)->b0 = 0;
            ((TILE *)red)->r0 = color;
            ((TILE *)red)->g0 = 0;
            ((TILE *)red)->b0 = 0;
            ((TILE *)back)->r0 = 0;
            ((TILE *)back)->g0 = 0;
            ((TILE *)back)->b0 = 0;
            ((TILE *)back)->x0 = 0xC;
            ((TILE *)back)->y0 = D_800A2FD0[tileRow] + 0xD2;
            ((TILE *)back)->w = 0x2A;
            ((TILE *)back)->h = 8;
        }
    }
    SetPolyFT4((POLY_FT4 *)D_800A789C);
    SetSemiTrans((u8 *)D_800A789C, 1);
    SetShadeTex((u8 *)D_800A789C, 0);
    D_800A78B2[0] = GetTPage(tex->tpage, 3, tex->tpx, tex->tpy);
    D_800A78A8[0] = tex->u + 0x60;
    D_800A78A9[0] = tex->v + 0xF;
    D_800A78B0[0] = tex->u + 0x6F;
    D_800A78B1[0] = tex->v + 0xF;
    D_800A78B8[0] = tex->u + 0x60;
    D_800A78B9[0] = tex->v;
    D_800A78C0[0] = tex->u + 0x6F;
    D_800A78C1[0] = tex->v;
    SetTile(D_800A7984);
    borderFlag = D_800A798B[0];
    driverBase = D_800B0B7C; /* la driverBase, D_800B0B7C */
    D_800A7990[0] = 0x140;
    D_800A798C[0] = 0;
    D_800A798E[0] = 0;
    D_800A7992[0] = 0xF0;
    D_800A798BWrite[0] = borderFlag | 2;
    page = (u16 *)D_80090F32;
    asm("" : "=r"(page) : "0"(page));
    SetPolyF4(D_800A7564);
    for (entry = 0; entry < 2; entry++) {
        for (col = 0; col < 0x18; col++) {
            driverCall =
                (POLY_FT4 *)((u8 *)((u32)(col * 0x28) + (u32)driverBase));
            driverCall = (POLY_FT4 *)((u32)(entry * 0x3C0) - -(u32)driverCall);
            SetPolyFT4(driverCall);
            SetShadeTex(driverCall, 0);
            markerPage = GetTPage(page[0], 0, page[-6], page[-5]);
            markerOffset = (u32)col * 0x28 + (u32)entry * 0x3C0;
            *(u16 *)(markerOffset + (u8 *)D_800B0B92) = markerPage;
            driverR = D_800991E8[col * 3]; /* lbu */
            driver = (u8 *)((u32)markerOffset + (u32)driverBase);
            ((POLY_FT4 *)driver)->r0 = driverR;
            ((POLY_FT4 *)driver)->g0 = D_800991E9[col * 3];
            ((POLY_FT4 *)driver)->b0 = D_800991EA[col * 3];
        }
    }
}
#else
void HudInitRacePrims(void) {
    HudTexture *tex;
    POLY_FT4 *prim;
    TILE *p3;
    TILE *p4;
    u8 *f4base;
    s32 tileIndex;
    s32 tileBytes;
    s32 tileX;
    u8 *tileHeightBase;
    POLY_FT4 *heap;
    Glyph *glyph;
    s8 entry;
    s8 col;
    s8 line;
    s8 j;
    s8 row;
    u16 *page;
    s32 markerOffset;
    u8 *driver;
    u8 driverR;
    register s32 line24 asm("$22");
    s8 **slot;
    s8 **lineSlot;
    s32 glyphOffset;
    s32 cornerOffset;
    s32 value;
    u8 *slotBase;
    u8 *coord;
    POLY_FT4 *driverCall;
    u8 *driverBase;
    u32 borderFlag;
    u16 markerPage;
    register u8 *mapCall asm("$16");
    POLY_FT4 *mapPrim;
    register s32 view asm("$22");
    register u8 *coordX asm("a0");
    s32 coordinateValue;
    register u8 *coordY asm("v1");
    register s32 yOffset asm("v1");

    D_800A3680[0] = 0;
    D_800A3490 = 0;
    D_800A2FD0[0] = -(gSplitScreenMode[0] != 0) & 0x92;
    for (entry = 0; entry < D_800A3424; entry++) {
        D_800A3485 = 0;
        for (col = 0; col < 6; col++) {
            {
                register u8 *addressBase asm("$8");

                asm("lui %1,%%hi(D_8009AE14)\naddiu %1,%1,%%lo(D_8009AE14)\naddu %0,%2,%1"
                    : "=r"(lineSlot), "=&r"(addressBase)
                    : "r"(col * 4));
            }
            D_800A3485 += strlen((char *)*lineSlot);
        }
        D_800A3484Small = D_800A3485 + strlen((char *)D_8009AE2C[0]);
        for (col = 0; col < 3; col += 2) {
            line = 0;
            heap = (POLY_FT4 *)((u8 *)HeapAlloc(D_800A3484Small * 0x28));
            D_800A78C4[(s8)(entry + col)] = (s8 *)heap;
            for (; line < 7; line++) {
                j = 0;
                line24 = line << 24;
                {
                    register u8 *addressBase asm("$8");

                    asm("lui %1,%%hi(D_8009AE14)\naddiu %1,%1,%%lo(D_8009AE14)\naddu %0,%2,%1"
                        : "=r"(lineSlot), "=&r"(addressBase)
                        : "r"(line24 >> 22));
                }
                if ((*lineSlot)[0] != 0) {
                    do {
                        {
                            register u8 *addressBase asm("$8");

                            do {
                                glyphOffset = line24 >> 22;
                            } while (0);
                            addressBase = (u8 *)D_8009AE14;
                            slot =
                                (s8 **)((u32)(glyphOffset) - -(u32)addressBase);
                        }
                        glyph = &gHudGlyphs[(*slot)[j]];
                        SetPolyFT4(heap);
                        heap->clut = GetClut(0x390, 0x3C);
                        heap->r0 = 0x80;
                        heap->g0 = 0x80;
                        heap->b0 = 0xC0;
                        heap->tpage = GetTPage(0, 0, glyph->x, glyph->y);
                        heap->u0 = glyph->u;
                        heap->v0 = glyph->v;
                        heap->u1 = glyph->u + *(u8 *)&glyph->width;
                        heap->v1 = glyph->v;
                        heap->u2 = glyph->u;
                        heap->v2 = glyph->v + *(u8 *)&glyph->height;
                        heap->u3 = glyph->u + *(u8 *)&glyph->width;
                        heap->v3 = glyph->v + *(u8 *)&glyph->height;
                        j++;
                        heap++;
                    } while ((*slot)[j] != 0);
                }
            }
        }
        row = entry;
        func_8004AFE0(row, D_80099298, (u16 *)D_800A78C4[row]);
        {
            register u8 *addressBase asm("$8");

            asm("lui %1,%%hi(D_800A78CC)\naddiu %1,%1,%%lo(D_800A78CC)\naddu %0,%2,%1"
                : "=r"(slotBase), "=&r"(addressBase)
                : "r"(row * 4));
        }
        func_8004AFE0(row, D_80099298, *(u16 **)slotBase);
        D_800A3488 = strlen((char *)((s8 **)D_8009AE14)[0]);
        prim = (POLY_FT4 *)((u8 *)D_800A78D4 + row * 0x28);
        SetPolyFT4(prim);
        SetSemiTrans(prim, 1);
        prim->code |= 1;
        prim->u0 = D_80090FF2[0];
        prim->v0 = D_80090FF4[0];
        prim->u1 = D_80090FF2a[0] + 0x3C;
        prim->v1 = D_80090FF4a[0];
        prim->u2 = D_80090FF2b[0];
        prim->v2 = D_80090FF4b[0] + 0x3C;
        prim->u3 = D_80090FF2c[0] + 0x3C;
        prim->v3 = D_80090FF4c[0] + 0x3C;
        prim->x0 = 0xF5;
        prim->y0 = D_800A2FD0[row] + 0xA0;
        prim->x1 = 0x131;
        prim->y1 = D_800A2FD0[row] + 0xA0;
        prim->x2 = 0xF5;
        prim->y2 = D_800A2FD0[row] + 0xDC;
        prim->x3 = 0x131;
        prim->y3 = D_800A2FD0[row] + 0xDC;
        *(u16 *)((u8 *)D_800A78E2 + row * 0x28) =
            GetClut(D_80090FEE[0], D_80090FF0[0]);
        tex = D_80090FEA;
        asm("" : "=r"(view) : "0"((s32)row));
        *(u16 *)((u8 *)D_800A78EA + row * 0x28) =
            GetTPage(D_80090FF6[0], 0, tex->tpx, D_80090FEC[0]);
        tex -= 14;
        for (col = 0; col < 10; col++) {
            {
                register u8 *addressBase asm("$8");

                asm("lui %1,%%hi(D_800A757C)\naddiu %1,%1,%%lo(D_800A757C)\naddu %0,%3,%1"
                    : "=r"(mapCall), "=&r"(addressBase)
                    : "r"(view * 0x190), "r"(col * 0x28));
            }
            mapCall = (u8 *)((u32)(view * 0x190) + (u32)mapCall);
            SetPolyFT4((POLY_FT4 *)mapCall);
            SetShadeTex(mapCall, 0);
            {
                register u8 *addressBase asm("$8");

                asm("lui %1,%%hi(D_800A757C)\naddiu %1,%1,%%lo(D_800A757C)\naddu %0,%2,%1"
                    : "=r"(mapPrim), "=&r"(addressBase)
                    : "r"(view * 0x190 + col * 0x28));
            }
            mapPrim->r0 = 0x40;
            mapPrim->g0 = 0x40;
            mapPrim->b0 = 0x40;
            mapPrim->u0 = tex->u + 0x60;
            mapPrim->v0 = tex->v;
            mapPrim->u1 = tex->u + 0x6F;
            mapPrim->v1 = tex->v;
            mapPrim->u2 = tex->u + 0x60;
            mapPrim->v2 = tex->v + 0xF;
            mapPrim->u3 = tex->u + 0x6F;
            mapPrim->v3 = tex->v + 0xF;
            *(u16 *)(view * 0x190 + col * 0x28 + (u8 *)D_800A7592) =
                GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
            {
                register s32 cornerPrefix asm("s0");

                cornerPrefix = col * 12;
                coord = (u8 *)gCosTableAbsolute[0];
                cornerPrefix += col;
                cornerPrefix = cornerPrefix * 8 + 0x828;
                cornerOffset = cornerPrefix;
            }
            value = MathMultiplyFixed16(
                0x370000, *(s32 *)((u32)cornerOffset + (u32)coord));
            coordY = (u8 *)gSinTableMap0[0];
            mapPrim->x0 = (value >> 0x10) + 0x12C;
            coordY = (u8 *)((u32)cornerOffset + (u32)coordY);
            value = MathMultiplyFixed16(0x370000, *(s32 *)coordY);
            asm("" : "=r"(yOffset) : "0"((s32)(u8)D_800A2FD0[view]));
            coordX = (u8 *)gCosTableAbsolute[0];
            value >>= 0x10;
            yOffset = (s8)yOffset + 0xD7;
            coordX = (u8 *)((u32)cornerOffset + (u32)coordX);
            value += yOffset;
            asm("" : "=r"(value) : "0"(value), "r"(coordX));
            mapPrim->y0 = value;
            coordinateValue = *(s32 *)coordX;
            value = MathMultiplyFixed16(0x370000, coordinateValue);
            coordY = (u8 *)gSinTableMap1[0];
            mapPrim->x1 = (value >> 0x10) + 0x130;
            coordY = (u8 *)((u32)cornerOffset + (u32)coordY);
            value = MathMultiplyFixed16(0x370000, *(s32 *)coordY);
            asm("" : "=r"(yOffset) : "0"((s32)(u8)D_800A2FD0[view]));
            coordX = (u8 *)gCosTableAbsolute[0];
            value >>= 0x10;
            yOffset = (s8)yOffset + 0xD7;
            coordX = (u8 *)((u32)cornerOffset + (u32)coordX);
            value += yOffset;
            asm("" : "=r"(value) : "0"(value), "r"(coordX));
            mapPrim->y1 = value;
            coordinateValue = *(s32 *)coordX;
            value = MathMultiplyFixed16(0x370000, coordinateValue);
            coordY = (u8 *)gSinTableMap2[0];
            mapPrim->x2 = (value >> 0x10) + 0x12C;
            coordY = (u8 *)((u32)cornerOffset + (u32)coordY);
            value = MathMultiplyFixed16(0x370000, *(s32 *)coordY);
            coordX = (u8 *)gCosTableAbsolute[0];
            mapPrim->y2 = (value >> 0x10) + D_800A2FD0[view] + 0xDB;
            coordX = (u8 *)((u32)cornerOffset + (u32)coordX);
            coordinateValue = *(s32 *)coordX;
            value = MathMultiplyFixed16(0x370000, coordinateValue);
            coordY = (u8 *)gSinTableMap3[0];
            mapPrim->x3 = (value >> 0x10) + 0x130;
            cornerOffset += (u32)coordY;
            value = MathMultiplyFixed16(0x370000, *(s32 *)cornerOffset);
            mapPrim->y3 = (value >> 0x10) + D_800A2FD0[view] + 0xDB;
        }
        col = 0;
        tileIndex = (s8)entry;
        tileBytes = tileIndex * 0x30;
        f4base = (u8 *)D_800A7924;
        /* Keep these locals multi-set so loop.c does not hoist their values. */
        for (; col < 3; col++) {
            p3 = (TILE *)((u8 *)((u32)(col * 0x10) + (u32)f4base));
            p3 = (TILE *)((u32)tileBytes - -(u32)p3);
            SetTile(p3);
            SetSemiTrans(p3, 1);
            p4 = (TILE *)((u8 *)((u32)tileBytes + (u32)(col * 0x10) +
                                 (u32)f4base));
            tileX = 0xD;
            p4->x0 = tileX;
            tileX = 0;
            p4->y0 = D_800A2FD0[tileIndex] + 0xD3;
            tileHeightBase = (u8 *)D_800A7932;
            *(u16 *)(tileBytes + col * 0x10 + tileHeightBase) = 6;
            tileHeightBase = 0;
        }
        {
            register s32 tileRow asm("$6");
            u8 *green;
            register u8 *red asm("$3");
            u8 *back;
            s32 offset;
            s32 color;

            tileRow = (s8)entry;
            red = (u8 *)D_800A7924;
            offset = tileRow * 0x30;
            green = (u8 *)((u32)offset + (u32)red);
            do {
                color = 0xFF;
                red += 0x10;
            } while (0);
            red = (u8 *)((u32)offset + (u32)red);
            {
                register u8 *addressBase asm("$8");

                addressBase = (u8 *)D_800A7944;
                back = (u8 *)((u32)(offset) - -(u32)addressBase);
            }
            ((TILE *)green)->r0 = 0;
            ((TILE *)green)->g0 = color;
            ((TILE *)green)->b0 = 0;
            ((TILE *)red)->r0 = color;
            ((TILE *)red)->g0 = 0;
            ((TILE *)red)->b0 = 0;
            ((TILE *)back)->r0 = 0;
            ((TILE *)back)->g0 = 0;
            ((TILE *)back)->b0 = 0;
            ((TILE *)back)->x0 = 0xC;
            ((TILE *)back)->y0 = D_800A2FD0[tileRow] + 0xD2;
            ((TILE *)back)->w = 0x2A;
            ((TILE *)back)->h = 8;
        }
    }
    SetPolyFT4((POLY_FT4 *)D_800A789C);
    SetSemiTrans((u8 *)D_800A789C, 1);
    SetShadeTex((u8 *)D_800A789C, 0);
    D_800A78B2[0] = GetTPage(tex->tpage, 3, tex->tpx, tex->tpy);
    D_800A78A8[0] = tex->u + 0x60;
    D_800A78A9[0] = tex->v + 0xF;
    D_800A78B0[0] = tex->u + 0x6F;
    D_800A78B1[0] = tex->v + 0xF;
    D_800A78B8[0] = tex->u + 0x60;
    D_800A78B9[0] = tex->v;
    D_800A78C0[0] = tex->u + 0x6F;
    D_800A78C1[0] = tex->v;
    SetTile(D_800A7984);
    borderFlag = D_800A798B[0];
    asm volatile("lui %0,%%hi(D_800B0B7C)\naddiu %0,%0,%%lo(D_800B0B7C)"
                 : "=r"(driverBase)
                 :
                 : "memory");
    D_800A7990[0] = 0x140;
    D_800A798C[0] = 0;
    D_800A798E[0] = 0;
    D_800A7992[0] = 0xF0;
    D_800A798BWrite[0] = borderFlag | 2;
    page = (u16 *)D_80090F32;
    asm("" : "=r"(page) : "0"(page));
    SetPolyF4(D_800A7564);
    for (entry = 0; entry < 2; entry++) {
        for (col = 0; col < 0x18; col++) {
            driverCall =
                (POLY_FT4 *)((u8 *)((u32)(col * 0x28) + (u32)driverBase));
            driverCall = (POLY_FT4 *)((u32)(entry * 0x3C0) - -(u32)driverCall);
            SetPolyFT4(driverCall);
            SetShadeTex(driverCall, 0);
            markerPage = GetTPage(page[0], 0, page[-6], page[-5]);
            markerOffset = (u32)col * 0x28 + (u32)entry * 0x3C0;
            *(u16 *)(markerOffset + (u8 *)D_800B0B92) = markerPage;
            asm volatile("lbu %0,D_800991E8(%1)"
                         : "=r"(driverR)
                         : "r"(col * 3)
                         : "memory");
            driver = (u8 *)((u32)markerOffset + (u32)driverBase);
            ((POLY_FT4 *)driver)->r0 = driverR;
            ((POLY_FT4 *)driver)->g0 = D_800991E9[col * 3];
            ((POLY_FT4 *)driver)->b0 = D_800991EA[col * 3];
        }
    }
}
#endif
extern s8 D_800A2FD0[];

/* The `(u32)index + (u32)base` casts give retail's index-first `addu`
 * operands. The block-local row load and the `asm volatile` barrier keep
 * the row-pointer and pad-byte loads ahead of the x and y loads. */
void func_8004AFE0(s8 arg0, u16 *arg1, u16 *arg2) {
    s16 *out;
    u16 *xy0;
    u16 *cursor;
    s8 i;
    s8 j;
    s32 x;
    u8 *table;
    s32 w;
    s32 t;
    s32 v0;
    s32 v1;
    s32 sum;
    s32 i24;
    s32 padByte;
    s8 **a914;
    s16 *glyph;
    s32 arg0e;
    do {
        cursor = arg2;
        table = D_8009AE14;
    } while (0);
    i = 0;
    arg0e = (s8)arg0;
    a914 = (s8 **)table;
    do {
        s8 *row;

        j = 0;
        i24 = i << 24;
        xy0 = (u16 *)((u32)(i24 >> 22) + (u32)arg1);
        do {
            row = *(s8 **)((u32)(i24 >> 22) + (u32)a914);
            do {
                asm("" : "=r"(padByte) : "0"((u8)D_800A2FD0[arg0e]));
            } while (0);
            x = xy0[0];
            w = xy0[1] + ((padByte << 24) >> 24);
            if (row[0] != 0) {
                out = (s16 *)(((u8 *)cursor) + 0x22);
            inner:
                do {
                    t = (*((s8 **)((u32)(i24 >> 22) + (u32)a914)))[j];
                    glyph = (s16 *)&gHudGlyphs[t];
                    v0 = glyph[3];
                    out[-13] = x;
                    out[-12] = w;
                    out[-8] = w;
                    out[-5] = x;
                    sum = x + ((v0 * 3) >> 2);
                    out[-9] = sum;
                    v1 = glyph[4];
                    out[-1] = sum;
                    out[-4] = w + ((v1 * 3) >> 2);
                    out[0] = w + ((glyph[4] * 3) >> 2);
                } while (0);

                j++;
                cursor += 0x14;
                x = sum;
                out += 0x14;
                if ((*((s8 **)((u32)(i24 >> 22) + (u32)a914)))[j] != 0) {
                    goto inner;
                }
            }
        } while (0);
        i++;
    } while (i < 7);
}

void func_8004B128(Car *arg0) {
    s8 value;

    if (arg0->unk3FC != 0) {
        value = (D_800A2E50[0] - D_800A38E4[0]) * 10 / D_800A2E50[0] + 2;
    } else {
        value = 0;
    }
    if (value >= 0xB) {
        value = 0xA;
    }
    arg0->unk3FD = value;
    arg0->unk402 = (u16)arg0->rpm;
}

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
void HudDrawDashboard(void) {
    /* Preserve the temporary packet layout used by the draw loops. */
    s16 points[16];
    s16 angles[4];
    s16 streakAngles[4];
    s16 *cornerRows[2];
    u32 intensityBytes[2];
    u8 framePad[8];
    register s32 product;
    s32 productY;
    register s32 next;
    s32 cosine;
    s32 sine;
    s32 offset;
    s32 count;
    register s32 vertex;
    register s32 i;
    register s16 *point;
    s16 *corner;
    POLY_F4 *needle;
    register u32 cachedAngle;
    register s32 argA;
    register s32 argB;
    s32 callResult;
    s32 nextVertex;
    register s32 screenY;
    register s16 *baseCorner;

    if (gSplitScreenMode[0] == 0) {
        i = 0;
    copyHud1:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(D_800A8184 + (s16)i * 0x18);
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(gOrderingTable[0] + 0x10), entry);
            next = i + 1;
            do {
                i = next;
            } while (0);

            if ((s16)next < 2)
                goto copyHud1;
        }
        i = 0;
        PushMatrix();
        func_800474A0();
        do {
            baseCorner = D_8009935C;

            cornerRows[0] = baseCorner;
            switch ((s16)i) {
            case 0: {
                Car *car;
                s32 rpm;
                s32 numerator;
                register s32 quotient;
                register s32 trueFactor;
                register s32 falseFactor;
                register s32 trueHigh;
                register s32 falseHigh;
                s64 wideProduct;

                /* Scale the tachometer angle by 585/13250 or 658/13250. */
                car = gPlayerCar[0];
                rpm = car->unk402;
                if (car->automatic != 0 || car->gearIndex == car->unk110) {
                    trueFactor = 0x9E468F35;
                    numerator = rpm * 585;
                    /* mult numerator, trueFactor; mfhi trueHigh */
                    wideProduct = (s64)numerator * trueFactor;
                    trueHigh = (s32)(wideProduct >> 32);
                    quotient = trueHigh + numerator;
                } else {
                    falseFactor = 0x9E468F35;
                    numerator = rpm * 658;
                    /* mult numerator, falseFactor; mfhi falseHigh */
                    wideProduct = (s64)numerator * falseFactor;
                    falseHigh = (s32)(wideProduct >> 32);
                    quotient = falseHigh + numerator;
                }
                quotient >>= 13;
                numerator >>= 31;
                quotient -= numerator;
                quotient += 256;
                do {

                    angles[0] = quotient;
                } while (0);
            }
                baseCorner = D_8009936C;

                cornerRows[0] = baseCorner;
                break;
            case 1:
                if (D_800A2ED4[0] == 0) {
                    if (RandomScaledGet(2)) {
                        productY = -RandomScaledGet(gPlayerCar[0]->speed >> 20);
                    } else {
                        productY = RandomScaledGet(gPlayerCar[0]->speed >> 20);
                    }
                    productY += 0x300;
                    D_800A3494 = productY;
                    angles[0] = productY;
                } else {
                    cachedAngle = D_800A3494;

                    angles[0] = cachedAngle;
                }
                break;
            case 2: {
                s32 speed;
                s32 scaledSpeed;
                register s32 factor;
                register s32 high;
                register s32 angleQuot;
                s64 wideProduct;

                /* Scale speed by 768/16000 for the speedometer angle. */
                speed = gPlayerCar[0]->unk28C;
                factor = 0x10624DD3;
                scaledSpeed = speed * 768;
                /* mult scaledSpeed, factor: mfhi below reads the high word. */
                wideProduct = (s64)scaledSpeed * factor;
                scaledSpeed >>= 31;
                high = (s32)(wideProduct >> 32); /* mfhi */
                angleQuot = high >> 10;
                angleQuot -= scaledSpeed;
                angleQuot += 0x180;
                angleQuot &= 0x3FF;
                angles[0] = angleQuot;
                break;
            }
            case 3:
                angles[0] =
                    ((s32)((u8)gPlayerCar[0]->unk3FD << 24) >> 21) + 0x2D8;
                break;
            }
            vertex = 0;
            {
                register u32 angleWord;
                register s32 index;
                register s32 *cosineTable;
                register s32 *sineTable;
                extern s32 *hudCosine __asm__("gCosTable");
                extern s32 *hudSine __asm__("gSinTable");

                index = i << 16;
                angleWord = *(u16 *)angles;

                offset = index >> 14;
                cosineTable = hudCosine;
                sineTable = hudSine;
                index = (s32)(angleWord << 16) >> 14;
                cosineTable = (s32 *)(index + (u32)cosineTable);
                cosine = *cosineTable;
                sineTable = (s32 *)(index + (u32)sineTable);
                sine = *sineTable;
            }
        rotateCorner:
            {
                register s16 *base;

                base = cornerRows[0];

                count = (s32)(vertex << 16) >> 14;
                corner = (s16 *)(count + (u32)base);

                argB = corner[0];
                argA = cosine;
            }
            callResult = MathMultiplyFixed16(argA, argB << 16);
            argB = corner[1];
            argA = sine;
            product = callResult;
            callResult = MathMultiplyFixed16(argA, argB << 16);
            {
                u32 centerX;

                point = points;

                centerX = *(u16 *)(offset + (u32)D_8009934C);
                point = (s16 *)((u8 *)point + count);
                asm("" : "=r"(point) : "0"(point), "r"(centerX), "r"(product));
                product -= callResult;
                product >>= 16;
                centerX += product;
                point[0] = centerX;
                argB = corner[0];
                argA = sine;
            }
            callResult = MathMultiplyFixed16(argA, argB << 16);
            argB = corner[1];
            argA = cosine;
            product = callResult;
            callResult = MathMultiplyFixed16(argA, argB << 16);
            screenY = (u8)D_800A2FD4[0];

            nextVertex = vertex + 1;
            vertex = nextVertex;
            asm("" : "=r"(nextVertex) : "0"(nextVertex));
            argB = *(u16 *)(offset + (u32)D_8009934E);

            product += callResult;
            product >>= 16;
            nextVertex = (s16)nextVertex < 4;
            point[1] = (s8)screenY + (argB + product);
            if (nextVertex)
                goto rotateCorner;
            {
                register s32 copyIndex;
                s32 copyOffset;
                register u32 needleBase;

                copyIndex = (s16)i;
                needleBase = (u32)D_800A81B4;
                copyOffset = copyIndex << 1;

                argA = *(u16 *)points;
                copyOffset += copyIndex;
                copyOffset <<= 3;
                needle = (POLY_F4 *)(copyOffset + needleBase);
            }
            needle->x0 = argA;
            needle->y0 = points[1];
            needle->x1 = points[2];
            needle->y1 = points[3];
            needle->x2 = points[4];
            needle->y2 = points[5];
            needle->x3 = points[6];
            needle->y3 = points[7];
            next = i + 1;
            do {
                i = next;
            } while (0);

        } while ((s16)next < 4);
        D_800A3008 = D_800A3480 * -15;
        RotMatrix(D_800A3004, D_800A7FC4);
        SetRotMatrix(D_800A7FC4);
        SetTransMatrix(D_800A7FC4);
        {
            u8 *dest;
            register u8 *source;
            register u8 *out;
            u32 *ot;
            s32 count;
            s32 product;
            struct PacketWords {
                s32 w0;
                s32 w1;
                s32 w2;
                s32 w3;
                s32 w4;
            };
            struct PacketWords *from;
            struct PrimitiveWords {
                u32 tag, color, xy0, uv0, xy1, uv1, xy2, uv2, xy3, uv3;
            };
            struct PrimitiveWords *poly;
            register s32 w0;
            s32 w1;
            register s32 w2;
            s32 w3;
            s32 w4;
            register SVECTOR *p0;
            register SVECTOR *p1;
            register SVECTOR *p2;
            /* Project the 36 dashboard quads through the GTE. */
            dest = (u8 *)gHudPrimitiveCursor;
            count = 36;
            source = D_800A7995;
            ot = (u32 *)gOrderingTable[0];
            out = dest + 0x18;
            do {
                p0 = ((Face *)(source - 1))->vertex[0];
                p1 = ((Face *)(source - 1))->vertex[1];
                p2 = ((Face *)(source - 1))->vertex[2];
                gte_ldv3(p0, p1, p2);
                asm volatile(
                    ".set\tnoreorder\n\tnop\n\tnop\n\trtpt\n\t.set\treorder");
                asm volatile(
                    ".set\tnoreorder\n\tnop\n\tnop\n\tavsz3\n\t.set\treorder");
                from = (struct PacketWords *)(source + 3);
                poly = (struct PrimitiveWords *)(out - 0x18);
                w2 = from->w2;
                w0 = from->w0;
                w1 = from->w1;
                w3 = from->w3;
                w4 = from->w4;

                poly->uv1 = w2;
                poly->uv0 = w1;
                poly->color = w0;
                poly->uv2 = w3;
                poly->uv3 = w4;
                gte_stsxy3(dest + 8, dest + 0x10, dest + 0x20);
                p0 = ((Face *)(source - 1))->vertex[3];
                gte_ldv0(p0);
                asm volatile(
                    ".set\tnoreorder\n\tnop\n\tnop\n\trtps\n\t.set\treorder");
                gte_stsxy(out);
                argB = (s32)dest;
                count--;
                product = *(s8 *)source;
                source += 0x2C;
                out += 0x28;
                dest += 0x28;
                GraphicsAddTaggedPrimitive(ot + product, (u32 *)argB,
                                           0x09000000);
            } while (count > 0);
            gHudPrimitiveCursor = (u32)dest;
        }
        i = 0;
    copyHud2:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(D_800A81B4 + (s16)i * 24);
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(gOrderingTable[0] + 8), entry);
            next = i + 1;
            do {
                i = next;
            } while (0);

            if ((s16)next < 4)
                goto copyHud2;
        }
        i = 0;
    copyHud3:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = &D_800A8214[(s16)i];
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(gOrderingTable[0] + 16), entry);
            next = i + 1;
            do {
                i = next;
            } while (0);

            if ((s16)next < 4)
                goto copyHud3;
        }
        i = 0;
    copyHud4:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(D_800A82B4 + (s16)i * 40);
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(gOrderingTable[0] + 16), entry);
            next = i + 1;
            do {
                i = next;
            } while (0);

            if ((s16)next < 4)
                goto copyHud4;
        }
        {
            register s32 product;
            s32 productX;
            s32 rotatedX;
            register s32 rowOffset;
            u16 *center;

            register u32 intensityValue;
            register u32 reloadIntensity;
            register u16 rawAngle;
            register u32 shifted;
            s32 signedAngle;
            i = 0;
            streakAngles[0] = (D_800A348C + 0x120) & 0x3FF;
            do {
                rawAngle = *(u16 *)streakAngles;
                asm("" : "=r"(rawAngle) : "0"(rawAngle));
                shifted = (u32)rawAngle << 16;
                signedAngle = (s32)shifted >> 16;
                if (signedAngle < 0x200) {
                    if (signedAngle - 0x100 >= 0) {
                        offset = (u32)(0x200 - signedAngle) >> 2;
                    } else {
                        offset = shifted >> 18;
                    }
                    intensityValue = offset & 0xFF;

                    intensityBytes[0] = intensityValue;
                    if (intensityValue >= 8) {
                        {
                            s32 index;
                            register s32 width;
                            register u32 angleWord;
                            u32 centers;
                            register u32 angleIndex;
                            register u32 centerValue;
                            extern s32 *hudCosine __asm__("gCosTable");
                            extern s32 *hudSine __asm__("gSinTable");

                            index = (s16)i;
                            width = D_800A2FD8[index];
                            asm("" : "=r"(width) : "0"(width));
                            angleWord = *(u16 *)streakAngles;
                            asm("" : "=r"(angleWord) : "0"(angleWord));
                            argB = 0x200;
                            centers = (u32)D_800A2FDC;

                            center = (u16 *)(index * 2 + centers);
                            centerValue = *center;
                            callResult = index * 5;

                            rowOffset = callResult << 3;
                            product = intensityValue >> 1;

                            product <<= 16;
                            width = (s8)width;
                            angleIndex = angleWord;
                            argB -= angleIndex;
                            argB >>= 7;
                            centerValue -= width;
                            centerValue = argB + centerValue;
                            *(s16 *)(rowOffset + (u32)D_800A853C) = centerValue;

                            do {
                                callResult = D_800A2FD8[index];
                            } while (0);

                            asm("" : "=r"(callResult) : "0"(callResult));
                            centerValue = *center;
                            argA = (s32)hudCosine;
                            callResult = (s8)callResult;
                            centerValue += callResult;
                            callResult = (s32)hudSine;
                            angleIndex <<= 2;
                            argB += centerValue;
                            argA = angleIndex + argA;
                            *(s16 *)(rowOffset + (u32)D_800A8544) = argB;
                            cosine = *(s32 *)argA;
                            argB = 0x640000;
                            angleIndex += callResult;

                            sine = *(s32 *)angleIndex;
                        }
                        callResult = MathMultiplyFixed16(cosine, argB);
                        argB = product;
                        productX = callResult;
                        callResult = MathMultiplyFixed16(sine, argB);
                        argA = sine;
                        argB = 0x640000;

                        rotatedX = callResult;
                        callResult = HudMultiplyVoid(
                            argA, argB); /* retail read it from v0 */
                        argA = cosine;
                        argB = product;
                        product = callResult;
                        callResult = HudMultiplyVoid(
                            argA, argB); /* retail read it from v0 */
                        argA = *center;
                        screenY = (productX - rotatedX) >> 16;
                        argA += screenY;
                        *(s16 *)(rowOffset + (u32)D_800A854C) = argA;

                        screenY = (u8)D_800A2FD4[0];
                        asm("" : "=r"(screenY) : "0"(screenY));
                        argA = (product + callResult) >> 16;
                        screenY = (s8)screenY;
                        screenY += 0x9E;
                        argA += screenY;
                        *(s16 *)(rowOffset + (u32)D_800A854E) = argA;

                        screenY = *center;
                        productX += rotatedX;
                        productX >>= 16;
                        screenY += productX;
                        *(s16 *)(rowOffset + (u32)D_800A8554) = screenY;

                        do {
                            screenY = (u8)D_800A2FD4[0];
                        } while (0);

                        asm("" : "=r"(screenY) : "0"(screenY));
                        product -= callResult;
                        product >>= 16;
                        screenY = (s8)screenY;
                        screenY += 0x9E;
                        product += screenY;
                        *(s16 *)(rowOffset + (u32)D_800A8556) = product;

                        reloadIntensity = intensityBytes[0];
                        next = reloadIntensity < 33;

                        if (!next)
                            offset = 32;
                        {
                            u32 raw;
                            POLY_FT4 *entry;
                            register POLY_FT4 *prim;
                            prim = (POLY_FT4 *)(rowOffset + (u32)D_800A8534);

                            prim->r0 = offset;
                            prim->g0 = offset;
                            prim->b0 = offset;
                            raw = gHudPrimitiveCursor;
                            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
                            entry = (POLY_FT4 *)raw;
                            *entry = *prim;
                            AddPrim((void *)(gOrderingTable[0] + 0x10), entry);
                        }
                    }
                }
                {
                    register u32 angleRaw;
                    register u32 angleNext;

                    angleRaw = *(u16 *)streakAngles;

                    angleNext = (angleRaw + 0x3E0) & 0x3FF;
                    streakAngles[0] = angleNext;
                }
                next = i + 1;
                do {
                    i = next;
                } while (0);

            } while ((s16)next < 3);
        }
        PopMatrix();
    }
    i = 0;
copyHud5:
    {
        register u32 raw;
        u32 mode;
        s32 row;
        register s32 copyOffset;
        s32 modeOffset;
        s32 rowOffset;
        register POLY_FT4 *entry;
        POLY_FT4 *copyDest;
        u32 sourceBase;
        POLY_FT4 *prim;
        mode = D_800A2ED9[0];
        row = (s16)i;

        do {
            raw = gHudPrimitiveCursor;
        } while (0);

        do {
            modeOffset = mode * 240;
        } while (0);

        rowOffset = row * 40;

        copyOffset = modeOffset + rowOffset;
        entry = (POLY_FT4 *)raw;

        copyDest = entry;

        sourceBase = (u32)D_800A8354;
        prim = (POLY_FT4 *)(copyOffset + sourceBase);
        gHudPrimitiveCursor = (u32)entry + sizeof(POLY_FT4);
        *copyDest = *prim;
        AddPrim((void *)(gOrderingTable[0] + 0x10), entry);
        next = i + 1;
        do {
            i = next;
        } while (0);

        if ((s16)next < 6)
            goto copyHud5;
    }
    i = 0;
copyHud6:
    {
        register u32 raw;
        register u32 mode;
        s32 row;
        s32 copyOffset;
        s32 modeOffset;
        register POLY_FT4 *entry;
        POLY_FT4 *copyDest;
        u32 sourceBase;
        POLY_FT4 *prim;
        mode = D_800A2ED9[0];
        row = (s16)i;
        asm volatile("" : "=r"(row) : "0"(row), "r"(mode) : "memory");
        raw = gHudPrimitiveCursor;
        asm("" : "=r"(raw) : "0"(raw));
        modeOffset = mode * 9;

        do {
            copyOffset = row * 3;
        } while (0);

        copyOffset += modeOffset;
        copyOffset <<= 3;
        entry = (POLY_FT4 *)raw;

        copyDest = entry;

        sourceBase = (u32)D_800A80F4;
        prim = (POLY_FT4 *)(copyOffset + sourceBase);
        gHudPrimitiveCursor = (u32)entry + sizeof(POLY_FT4);
        *copyDest = *prim;
        AddPrim((void *)(gOrderingTable[0] + 0x10), entry);
        next = i + 1;
        do {
            i = next;
        } while (0);

        if ((s16)next < 3)
            goto copyHud6;
    }
}
#else
void HudDrawDashboard(void) {
    /* Preserve the temporary packet layout used by the draw loops. */
    s16 points[16];
    s16 angles[4];
    s16 streakAngles[4];
    s16 *cornerRows[2];
    u32 intensityBytes[2];
    u8 framePad[8];
    register s32 product asm("s0");
    s32 productY;
    register s32 next asm("v0");
    s32 cosine;
    s32 sine;
    s32 offset;
    s32 count;
    register s32 vertex asm("s4");
    register s32 i asm("s7");
    register s16 *point asm("s3");
    s16 *corner;
    POLY_F4 *needle;
    register u32 cachedAngle asm("t3");
    register s32 argA asm("a0");
    register s32 argB asm("a1");
    s32 callResult;
    s32 nextVertex;
    register s32 screenY asm("v1");
    register s16 *baseCorner asm("t2");

    if (gSplitScreenMode[0] == 0) {
        i = 0;
    copyHud1:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(D_800A8184 + (s16)i * 0x18);
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(gOrderingTable[0] + 0x10), entry);
            next = i + 1;
            do {
                i = next;
            } while (0);

            if ((s16)next < 2)
                goto copyHud1;
        }
        i = 0;
        PushMatrix();
        func_800474A0();
        do {
            baseCorner = D_8009935C;

            cornerRows[0] = baseCorner;
            switch ((s16)i) {
            case 0: {
                Car *car;
                s32 rpm;
                s32 numerator;
                register s32 quotient asm("$3");
                register s32 trueFactor asm("$4");
                register s32 falseFactor asm("$3");
                register s32 trueHigh asm("$11");
                register s32 falseHigh asm("$12");
                s64 wideProduct;

                /* Scale the tachometer angle by 585/13250 or 658/13250. */
                car = gPlayerCar[0];
                rpm = car->unk402;
                if (car->automatic != 0 || car->gearIndex == car->unk110) {
                    trueFactor = 0x9E468F35;
                    numerator = rpm * 585;
                    asm("mult %2,%3\n\tmfhi %0"
                        : "=r"(trueHigh), "=x"(wideProduct)
                        : "r"(numerator), "r"(trueFactor)
                        : "accum");
                    quotient = trueHigh + numerator;
                } else {
                    falseFactor = 0x9E468F35;
                    numerator = rpm * 658;
                    asm("mult %2,%3\n\tmfhi %0"
                        : "=r"(falseHigh), "=x"(wideProduct)
                        : "r"(numerator), "r"(falseFactor)
                        : "accum");
                    quotient = falseHigh + numerator;
                }
                quotient >>= 13;
                numerator >>= 31;
                quotient -= numerator;
                quotient += 256;
                do {

                    angles[0] = quotient;
                } while (0);
            }
                baseCorner = D_8009936C;

                cornerRows[0] = baseCorner;
                break;
            case 1:
                if (D_800A2ED4[0] == 0) {
                    if (RandomScaledGet(2)) {
                        productY = -RandomScaledGet(gPlayerCar[0]->speed >> 20);
                    } else {
                        productY = RandomScaledGet(gPlayerCar[0]->speed >> 20);
                    }
                    productY += 0x300;
                    D_800A3494 = productY;
                    angles[0] = productY;
                } else {
                    cachedAngle = D_800A3494;

                    angles[0] = cachedAngle;
                }
                break;
            case 2: {
                s32 speed;
                s32 scaledSpeed;
                register s32 factor asm("a0");
                register s32 high asm("t4");
                register s32 angleQuot asm("v1");
                s64 wideProduct;

                /* Scale speed by 768/16000 for the speedometer angle. */
                speed = gPlayerCar[0]->unk28C;
                factor = 0x10624DD3;
                scaledSpeed = speed * 768;
                asm("mult %1,%2"
                    : "=x"(wideProduct)
                    : "r"(scaledSpeed), "r"(factor)
                    : "accum");
                scaledSpeed >>= 31;
                asm("mfhi %0"
                    : "=r"(high)
                    : "x"(wideProduct), "r"(scaledSpeed));
                angleQuot = high >> 10;
                angleQuot -= scaledSpeed;
                angleQuot += 0x180;
                angleQuot &= 0x3FF;
                angles[0] = angleQuot;
                break;
            }
            case 3:
                angles[0] =
                    ((s32)((u8)gPlayerCar[0]->unk3FD << 24) >> 21) + 0x2D8;
                break;
            }
            vertex = 0;
            {
                register u32 angleWord asm("t2");
                register s32 index asm("v0");
                register s32 *cosineTable asm("v1");
                register s32 *sineTable asm("a0");
                extern s32 *hudCosine asm("gCosTableAbsolute");
                extern s32 *hudSine asm("gSinTableAbsolute");

                index = i << 16;
                angleWord = *(u16 *)angles;

                offset = index >> 14;
                cosineTable = hudCosine;
                sineTable = hudSine;
                index = (s32)(angleWord << 16) >> 14;
                cosineTable = (s32 *)(index + (u32)cosineTable);
                cosine = *cosineTable;
                sineTable = (s32 *)(index + (u32)sineTable);
                sine = *sineTable;
            }
        rotateCorner:
            {
                register s16 *base asm("t3");

                base = cornerRows[0];

                count = (s32)(vertex << 16) >> 14;
                corner = (s16 *)(count + (u32)base);

                argB = corner[0];
                argA = cosine;
            }
            callResult = MathMultiplyFixed16(argA, argB << 16);
            argB = corner[1];
            argA = sine;
            product = callResult;
            callResult = MathMultiplyFixed16(argA, argB << 16);
            {
                u32 centerX;

                point = points;

                centerX = *(u16 *)(offset + (u32)D_8009934C);
                point = (s16 *)((u8 *)point + count);
                asm("" : "=r"(point) : "0"(point), "r"(centerX), "r"(product));
                product -= callResult;
                product >>= 16;
                centerX += product;
                point[0] = centerX;
                argB = corner[0];
                argA = sine;
            }
            callResult = MathMultiplyFixed16(argA, argB << 16);
            argB = corner[1];
            argA = cosine;
            product = callResult;
            callResult = MathMultiplyFixed16(argA, argB << 16);
            screenY = (u8)D_800A2FD4[0];

            nextVertex = vertex + 1;
            vertex = nextVertex;
            asm("" : "=r"(nextVertex) : "0"(nextVertex));
            argB = *(u16 *)(offset + (u32)D_8009934E);

            product += callResult;
            product >>= 16;
            nextVertex = (s16)nextVertex < 4;
            point[1] = (s8)screenY + (argB + product);
            if (nextVertex)
                goto rotateCorner;
            {
                register s32 copyIndex asm("v0");
                s32 copyOffset;
                register u32 needleBase asm("a1");

                copyIndex = (s16)i;
                needleBase = (u32)D_800A81B4;
                copyOffset = copyIndex << 1;

                argA = *(u16 *)points;
                copyOffset += copyIndex;
                copyOffset <<= 3;
                needle = (POLY_F4 *)(copyOffset + needleBase);
            }
            needle->x0 = argA;
            needle->y0 = points[1];
            needle->x1 = points[2];
            needle->y1 = points[3];
            needle->x2 = points[4];
            needle->y2 = points[5];
            needle->x3 = points[6];
            needle->y3 = points[7];
            next = i + 1;
            do {
                i = next;
            } while (0);

        } while ((s16)next < 4);
        D_800A3008 = D_800A3480 * -15;
        RotMatrix(D_800A3004, D_800A7FC4);
        SetRotMatrix(D_800A7FC4);
        SetTransMatrix(D_800A7FC4);
        {
            u8 *dest;
            register u8 *source asm("s0");
            register u8 *out asm("s1");
            u32 *ot;
            s32 count;
            s32 product;
            struct PacketWords {
                s32 w0;
                s32 w1;
                s32 w2;
                s32 w3;
                s32 w4;
            };
            struct PacketWords *from;
            struct PrimitiveWords {
                u32 tag, color, xy0, uv0, xy1, uv1, xy2, uv2, xy3, uv3;
            };
            struct PrimitiveWords *poly;
            register s32 w0 asm("v0");
            s32 w1;
            register s32 w2 asm("a0");
            s32 w3;
            s32 w4;
            register SVECTOR *p0 asm("t4");
            register SVECTOR *p1 asm("t2");
            register SVECTOR *p2 asm("t3");
            /* Project the 36 dashboard quads through the GTE. */
            dest = (u8 *)gHudPrimitiveCursor;
            count = 36;
            source = D_800A7995;
            ot = (u32 *)gOrderingTable[0];
            out = dest + 0x18;
            do {
                p0 = ((Face *)(source - 1))->vertex[0];
                p1 = ((Face *)(source - 1))->vertex[1];
                p2 = ((Face *)(source - 1))->vertex[2];
                gte_ldv3(p0, p1, p2);
                asm volatile(
                    ".set\tnoreorder\n\tnop\n\tnop\n\trtpt\n\t.set\treorder");
                asm volatile(
                    ".set\tnoreorder\n\tnop\n\tnop\n\tavsz3\n\t.set\treorder");
                from = (struct PacketWords *)(source + 3);
                poly = (struct PrimitiveWords *)(out - 0x18);
                w2 = from->w2;
                w0 = from->w0;
                w1 = from->w1;
                w3 = from->w3;
                w4 = from->w4;

                poly->uv1 = w2;
                poly->uv0 = w1;
                poly->color = w0;
                poly->uv2 = w3;
                poly->uv3 = w4;
                gte_stsxy3(dest + 8, dest + 0x10, dest + 0x20);
                p0 = ((Face *)(source - 1))->vertex[3];
                gte_ldv0(p0);
                asm volatile(
                    ".set\tnoreorder\n\tnop\n\tnop\n\trtps\n\t.set\treorder");
                gte_stsxy(out);
                argB = (s32)dest;
                count--;
                product = *(s8 *)source;
                source += 0x2C;
                out += 0x28;
                dest += 0x28;
                GraphicsAddTaggedPrimitive(ot + product, (u32 *)argB,
                                           0x09000000);
            } while (count > 0);
            gHudPrimitiveCursor = (u32)dest;
        }
        i = 0;
    copyHud2:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(D_800A81B4 + (s16)i * 24);
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(gOrderingTable[0] + 8), entry);
            next = i + 1;
            do {
                i = next;
            } while (0);

            if ((s16)next < 4)
                goto copyHud2;
        }
        i = 0;
    copyHud3:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = &D_800A8214[(s16)i];
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(gOrderingTable[0] + 16), entry);
            next = i + 1;
            do {
                i = next;
            } while (0);

            if ((s16)next < 4)
                goto copyHud3;
        }
        i = 0;
    copyHud4:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(D_800A82B4 + (s16)i * 40);
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(gOrderingTable[0] + 16), entry);
            next = i + 1;
            do {
                i = next;
            } while (0);

            if ((s16)next < 4)
                goto copyHud4;
        }
        {
            register s32 product asm("s0");
            s32 productX;
            s32 rotatedX;
            register s32 returnedValue asm("v0");
            register s32 rowOffset asm("s4");
            u16 *center;

            register u32 intensityValue asm("t3");
            register u32 reloadIntensity asm("t2");
            register u16 rawAngle asm("t2");
            register u32 shifted asm("a0");
            s32 signedAngle;
            i = 0;
            streakAngles[0] = (D_800A348C + 0x120) & 0x3FF;
            do {
                rawAngle = *(u16 *)streakAngles;
                asm("" : "=r"(rawAngle) : "0"(rawAngle));
                shifted = (u32)rawAngle << 16;
                signedAngle = (s32)shifted >> 16;
                if (signedAngle < 0x200) {
                    if (signedAngle - 0x100 >= 0) {
                        offset = (u32)(0x200 - signedAngle) >> 2;
                    } else {
                        offset = shifted >> 18;
                    }
                    intensityValue = offset & 0xFF;

                    intensityBytes[0] = intensityValue;
                    if (intensityValue >= 8) {
                        {
                            s32 index;
                            register s32 width asm("a2");
                            register u32 angleWord asm("t4");
                            u32 centers;
                            register u32 angleIndex asm("a3");
                            register u32 centerValue asm("v1");
                            extern s32 *hudCosine asm("gCosTableAbsolute");
                            extern s32 *hudSine asm("gSinTableAbsolute");

                            index = (s16)i;
                            width = D_800A2FD8[index];
                            asm("" : "=r"(width) : "0"(width));
                            angleWord = *(u16 *)streakAngles;
                            asm("" : "=r"(angleWord) : "0"(angleWord));
                            argB = 0x200;
                            centers = (u32)D_800A2FDC;

                            center = (u16 *)(index * 2 + centers);
                            centerValue = *center;
                            callResult = index * 5;

                            rowOffset = callResult << 3;
                            product = intensityValue >> 1;

                            product <<= 16;
                            width = (s8)width;
                            angleIndex = angleWord;
                            argB -= angleIndex;
                            argB >>= 7;
                            centerValue -= width;
                            centerValue = argB + centerValue;
                            *(s16 *)(rowOffset + (u32)D_800A853C) = centerValue;

                            do {
                                callResult = D_800A2FD8[index];
                            } while (0);

                            asm("" : "=r"(callResult) : "0"(callResult));
                            centerValue = *center;
                            argA = (s32)hudCosine;
                            callResult = (s8)callResult;
                            centerValue += callResult;
                            callResult = (s32)hudSine;
                            angleIndex <<= 2;
                            argB += centerValue;
                            argA = angleIndex + argA;
                            *(s16 *)(rowOffset + (u32)D_800A8544) = argB;
                            cosine = *(s32 *)argA;
                            argB = 0x640000;
                            angleIndex += callResult;

                            sine = *(s32 *)angleIndex;
                        }
                        callResult = MathMultiplyFixed16(cosine, argB);
                        argB = product;
                        productX = callResult;
                        callResult = MathMultiplyFixed16(sine, argB);
                        argA = sine;
                        argB = 0x640000;

                        rotatedX = callResult;
                        HudMultiplyVoid(argA, argB);
                        callResult = returnedValue;
                        argA = cosine;
                        argB = product;
                        product = callResult;
                        HudMultiplyVoid(argA, argB);
                        callResult = returnedValue;
                        argA = *center;
                        screenY = (productX - rotatedX) >> 16;
                        argA += screenY;
                        *(s16 *)(rowOffset + (u32)D_800A854C) = argA;

                        screenY = (u8)D_800A2FD4[0];
                        asm("" : "=r"(screenY) : "0"(screenY));
                        argA = (product + callResult) >> 16;
                        screenY = (s8)screenY;
                        screenY += 0x9E;
                        argA += screenY;
                        *(s16 *)(rowOffset + (u32)D_800A854E) = argA;

                        screenY = *center;
                        productX += rotatedX;
                        productX >>= 16;
                        screenY += productX;
                        *(s16 *)(rowOffset + (u32)D_800A8554) = screenY;

                        do {
                            screenY = (u8)D_800A2FD4[0];
                        } while (0);

                        asm("" : "=r"(screenY) : "0"(screenY));
                        product -= callResult;
                        product >>= 16;
                        screenY = (s8)screenY;
                        screenY += 0x9E;
                        product += screenY;
                        *(s16 *)(rowOffset + (u32)D_800A8556) = product;

                        reloadIntensity = intensityBytes[0];
                        next = reloadIntensity < 33;

                        if (!next)
                            offset = 32;
                        {
                            u32 raw;
                            POLY_FT4 *entry;
                            register POLY_FT4 *prim asm("v0");
                            prim = (POLY_FT4 *)(rowOffset + (u32)D_800A8534);

                            prim->r0 = offset;
                            prim->g0 = offset;
                            prim->b0 = offset;
                            raw = gHudPrimitiveCursor;
                            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
                            entry = (POLY_FT4 *)raw;
                            *entry = *prim;
                            AddPrim((void *)(gOrderingTable[0] + 0x10), entry);
                        }
                    }
                }
                {
                    register u32 angleRaw asm("t3");
                    register u32 angleNext asm("v0");

                    angleRaw = *(u16 *)streakAngles;

                    angleNext = (angleRaw + 0x3E0) & 0x3FF;
                    streakAngles[0] = angleNext;
                }
                next = i + 1;
                do {
                    i = next;
                } while (0);

            } while ((s16)next < 3);
        }
        PopMatrix();
    }
    i = 0;
copyHud5:
    {
        register u32 raw asm("a1");
        u32 mode;
        s32 row;
        register s32 copyOffset asm("v1");
        s32 modeOffset;
        s32 rowOffset;
        register POLY_FT4 *entry asm("t0");
        POLY_FT4 *copyDest;
        u32 sourceBase;
        POLY_FT4 *prim;
        mode = D_800A2ED9[0];
        row = (s16)i;

        do {
            raw = gHudPrimitiveCursor;
        } while (0);

        do {
            modeOffset = mode * 240;
        } while (0);

        rowOffset = row * 40;

        copyOffset = modeOffset + rowOffset;
        entry = (POLY_FT4 *)raw;

        copyDest = entry;

        sourceBase = (u32)D_800A8354;
        prim = (POLY_FT4 *)(copyOffset + sourceBase);
        gHudPrimitiveCursor = (u32)entry + sizeof(POLY_FT4);
        *copyDest = *prim;
        AddPrim((void *)(gOrderingTable[0] + 0x10), entry);
        next = i + 1;
        do {
            i = next;
        } while (0);

        if ((s16)next < 6)
            goto copyHud5;
    }
    i = 0;
copyHud6:
    {
        register u32 raw asm("a1");
        register u32 mode asm("v0");
        s32 row;
        s32 copyOffset;
        s32 modeOffset;
        register POLY_FT4 *entry asm("t0");
        POLY_FT4 *copyDest;
        u32 sourceBase;
        POLY_FT4 *prim;
        mode = D_800A2ED9[0];
        row = (s16)i;
        asm volatile("" : "=r"(row) : "0"(row), "r"(mode) : "memory");
        raw = gHudPrimitiveCursor;
        asm("" : "=r"(raw) : "0"(raw));
        modeOffset = mode * 9;

        do {
            copyOffset = row * 3;
        } while (0);

        copyOffset += modeOffset;
        copyOffset <<= 3;
        entry = (POLY_FT4 *)raw;

        copyDest = entry;

        sourceBase = (u32)D_800A80F4;
        prim = (POLY_FT4 *)(copyOffset + sourceBase);
        gHudPrimitiveCursor = (u32)entry + sizeof(POLY_FT4);
        *copyDest = *prim;
        AddPrim((void *)(gOrderingTable[0] + 0x10), entry);
        next = i + 1;
        do {
            i = next;
        } while (0);

        if ((s16)next < 3)
            goto copyHud6;
    }
}
#endif
