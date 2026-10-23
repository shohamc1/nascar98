#include "common.h"
#include "libpress.h"
#include "fixed_addrs.h"
#include <psxsdk/libgpu.h>
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/libcd.h>
#include <psxsdk/libgte.h>
#include <psxsdk/libapi.h>
#include <psxsdk/libspu.h>
#include <psxsdk/kernel.h>
#include "game.h"
#include "graphics.h"
#include "util.h"

extern s32 func_8001E7EC(void *, s32, s32);

extern s32 D_800A2EC8nm[] asm("D_800A2EC8.NON_MATCHING");
extern s32 gOTBnm[] asm("gOrderingTableBank.NON_MATCHING");
extern u8 D_800A2EDAnm[] asm("D_800A2EDA.NON_MATCHING");
extern s32 gSplitScreenModenm[] asm("gSplitScreenMode.NON_MATCHING");
extern s32 gOrderingTablenm[] asm("gOrderingTable.NON_MATCHING");
void GraphicsDrawRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5,
                      u8 arg6, s32 arg7);
void func_8001DA48(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* Images and matrix state. */

extern ImageBankTexture *D_800A36CC;

ImageBankTexture *GraphicsGetImageBankTexture(s32 i) {
    return &D_800A36CC[i];
}

void GraphicsLoadImageBank(s32 fileName) {
    extern s32 FileOpen(s32, void *);
    extern void GraphicsInit(void);
    extern u_long *FntFlush(s32);
    extern s32 FileSeek(void *, s32, s32);
    extern void FileRead(s32, s32, s32, s32);
    extern void GraphicsLoadImageWithXOffset(s32);
    extern void FileClose(s32);
    extern u8 gImageFileMode[];
    extern char gErrorImageBankFileOpen[];
    extern void *D_800A368C;
    extern void *D_800A37E4;
    extern u16 D_800A3754;
    extern u16 D_800A3738;
    s32 handle;
    u8 *image;
    s32 size;
    u8 *head;
    u16 w;
    u16 h;
    s32 count;
    s32 i;
    s32 limit;
    u32 base;
    volatile s32 pad[2];

    handle = FileOpen(fileName, gImageFileMode);
    if (handle == 0) {
        GraphicsInit();
        FntPrint(gErrorImageBankFileOpen);
        FntFlush(-1);
        for (;;) {
        }
    }
    size = FileSeek(handle, 0, 2);
    FileSeek(handle, 0, 0);
    D_800A368C = (void *)STACK_BLOCK_80193000;
    FileRead((s32)STACK_BLOCK_80193000, 1, size, handle);
    image = (u8 *)D_800A368C;
    w = *(u16 *)image;
    h = *(u16 *)(image + 2);
    head = image + 4;
    D_800A37E4 = head;
    D_800A3754 = w;
    count = (s16)w;
    D_800A3738 = h;
    D_800A36CC = (ImageBankTexture *)(head + count * 8);
    if (count > 0) {
        i = 0;
        base = (u32)image;
        limit = count;
        do {
            ((u32 *)head)[i + i] += base;
            ((u32 *)head)[i + i + 1] += base;
            i++;
        } while (i < limit);
    }
    GraphicsLoadImageWithXOffset(-0x100);
    FileClose(handle);
}

/* GraphicsSelectImageBank: fixes up the selected image bank's relocation
 * entries, then reloads it if the swap flag is set. The empty asm after
 * i = 0 pins the counter's allocation to a1 (the retail delay-slot move)
 * without blocking the branch delay-slot fill. */
void GraphicsSelectImageBank(s32 index) {
    extern void *D_800A368C;
    extern void *D_800A37E4;
    extern u16 D_800A3754;
    extern u16 D_800A3738;
    extern void GraphicsLoadImageWithXOffset(s32);
    u8 *image;
    s32 i;
    u8 *head;
    u16 w;
    u16 h;
    s32 count;
    s32 limit;
    u32 base;
    volatile s32 pad[2];

    image = (u8 *)D_800B9F44[index];
    D_800A368C = image;
    w = *(u16 *)image;
    h = *(u16 *)(image + 2);
    head = image + 4;
    D_800A37E4 = head;
    D_800A3754 = w;
    count = (s16)w;
    D_800A3738 = h;
    D_800A36CC = (ImageBankTexture *)(head + count * 8);
    i = 0;
    if (count > 0) {
        asm volatile("" : : "r"(i));
        base = (u32)image;
        limit = count;
        do {
            ((u32 *)head)[i + i] += base;
            ((u32 *)head)[i + i + 1] += base;
            i++;
        } while (i < limit);
    }
    if (D_800A2EDAnm[0] != 0) {
        GraphicsLoadImageWithXOffset(0);
    }
}

void func_8001E230(s32 arg0, s32 arg1) {
    extern s32 FileOpen(s32, void *);
    extern void GraphicsInit(void);
    extern u_long *FntFlush(s32);
    extern s32 FileSeek(void *, s32, s32);
    extern void FileRead(s32, s32, s32, s32);
    extern void GraphicsLoadImageWithXOffset(s32);
    extern void FileClose(s32);
    extern u8 gImageFileMode[];
    extern char gErrorImageBankFileOpen[];
    extern void *D_800A368C;
    extern void *D_800A37E4;
    extern u16 D_800A3754;
    extern u16 D_800A3738;
    s32 handle;
    u8 *image;
    s32 size;
    u8 *head;
    u16 w;
    u16 h;
    s32 count;
    s32 i;
    s32 limit;
    u32 base;
    volatile s32 pad[2];

    handle = FileOpen(arg0, gImageFileMode);
    if (handle == 0) {
        GraphicsInit();
        FntPrint(gErrorImageBankFileOpen);
        FntFlush(-1);
        for (;;) {
        }
    }
    size = FileSeek(handle, 0, 2);
    FileSeek(handle, 0, 0);
    size = (size + 0x7FF) >> 11 << 11;
    if (arg1 == 0) {
        D_800A368C = HeapAlloc(size);
    } else {
        D_800A368C = (void *)arg1;
    }
    FileRead((s32)D_800A368C, 1, size, handle);
    image = (u8 *)D_800A368C;
    w = *(u16 *)image;
    h = *(u16 *)(image + 2);
    head = image + 4;
    D_800A37E4 = head;
    D_800A3754 = w;
    count = (s16)w;
    D_800A3738 = h;
    D_800A36CC = (ImageBankTexture *)(head + count * 8);
    if (count > 0) {
        i = 0;
        base = (u32)image;
        limit = count;
        do {
            ((u32 *)head)[i + i] += base;
            ((u32 *)head)[i + i + 1] += base;
            i++;
        } while (i < limit);
    }
    GraphicsLoadImageWithXOffset(0);
    FileClose(handle);
}

extern void *D_800A37E4;
void GraphicsLoadImageWithXOffset(s32 xOffset) {
    RECT rect;
    u8 *image;
    image = *(u8 **)((u8 *)D_800A37E4 + 4);
    rect.x = *(s16 *)(image + 0) + xOffset;
    rect.y = *(s16 *)(image + 2);
    rect.w = *(s16 *)(image + 4);
    rect.h = *(s16 *)(image + 6);
    LoadImage(&rect, (u_long *)(image + 8));
}

extern s32 D_800A2DC8;
extern s32 D_800A33D4;
extern s32 D_800A33D8;
extern DRAWENV D_800A3F7C[];
extern DISPENV D_800A4034[];
extern DRAWENV D_800A405C[][2];
extern DR_ENV D_800A433C[][2];

void GraphicsInitScreen(s32 width, s32 height, s32 screen, u8 show) {
    s32 xOffset;
    s32 i;
    s32 labelX;

    D_800A2DC8 = width;
    xOffset = width == 640 ? 0 : width;
    if (show) {
        SetDispMask(0);
        SetGraphDebug(0);
    }
    SetGeomOffset(width / 2, height / 2 + 10);
    SetGeomScreen(screen);
    SetDefDrawEnv(&D_800A3F7C[0], 0, 0, width, height);
    SetDefDispEnv(&D_800A4034[0], xOffset, 0, width, height);
    SetDefDrawEnv(&D_800A3F7C[1], xOffset, 0, width, height);
    SetDefDispEnv(&D_800A4034[1], 0, 0, width, height);
    D_800A3F7C[0].dtd = D_800A3F7C[1].dtd = 0;
    D_800A3F7C[0].isbg = D_800A3F7C[1].isbg = 1;
    setRGB0(&D_800A3F7C[0], 0, 0, 0);
    setRGB0(&D_800A3F7C[1], 0, 0, 0);
    D_800A33D4 = FntOpen(32, 32, 400, 112, 768, 255);
    D_800A33D8 = FntOpen(32, xOffset + 32, 400, 112, 768, 255);
    if (show) {
        PutDrawEnv(&D_800A3F7C[0]);
        PutDispEnv(&D_800A4034[1]);
    }
    i = 0;
    labelX = 200;
    for (; i < 2; i++) {
        SetDefDrawEnv(&D_800A405C[0][i], i * xOffset, 0, width, height);
        D_800A405C[0][i].dtd = 0;
        D_800A405C[0][i].isbg = 0;
        setRGB0(&D_800A405C[0][i], 40, 106, 2);
        SetDefDrawEnv(&D_800A405C[1][i], i * xOffset, 0, width, height / 2);
        D_800A405C[1][i].dtd = 0;
        D_800A405C[1][i].isbg = 0;
        setRGB0(&D_800A405C[1][i], 40, 106, 2);
        SetDefDrawEnv(&D_800A405C[2][i], i * xOffset, height / 2, width,
                      height / 2);
        D_800A405C[2][i].dtd = 0;
        D_800A405C[2][i].isbg = 0;
        setRGB0(&D_800A405C[2][i], 40, 106, 2);
        SetDefDrawEnv(&D_800A405C[3][i], labelX, 19, 100, 36);
        D_800A405C[3][i].dtd = 0;
        D_800A405C[3][i].isbg = 0;
        setRGB0(&D_800A405C[3][i], 40, 106, 2);
        SetDrawEnv(&D_800A433C[0][i], &D_800A405C[0][i]);
        SetDrawEnv(&D_800A433C[1][i], &D_800A405C[1][i]);
        SetDrawEnv(&D_800A433C[2][i], &D_800A405C[2][i]);
        SetDrawEnv(&D_800A433C[3][i], &D_800A405C[3][i]);
        labelX += xOffset;
    }
}

extern s32 D_800A2DC4w15 asm("D_800A2DC4.NON_MATCHING");
extern s32 D_800A2EC4w15[] asm("D_800A2EC4.NON_MATCHING");
extern s32 D_800A2ED0w15[] asm("D_800A2ED0.NON_MATCHING");
extern u8 D_800A3F7Cw15[] asm("D_800A3F7C.NON_MATCHING");
extern u8 D_800A4034w15[] asm("D_800A4034.NON_MATCHING");
extern u8 D_800A43BCw15[] asm("D_800A43BC.NON_MATCHING");
extern u8 D_800A433Cw15[] asm("D_800A433C.NON_MATCHING");
extern s32 D_800A39C4w15[] asm("D_800A39C4.NON_MATCHING");
extern s32 D_800A39CCw15[] asm("D_800A39CC.NON_MATCHING");

s32 func_8001E7EC(void *arg0, s32 arg1, s32 arg2) {
    u8 *envPtr;

    if (arg2 != 0) {
        FntPrint((const char *)arg1);
        FntFlush(-1);
    }
    D_800A2DC4w15 = gOTBnm[0] / 2;
    DrawSync(0);
    VSync(0);
    if (arg2 == 0) {
        FrameWaitForCounterPhase(0);
    }
    envPtr = D_800A3F7Cw15 + D_800A2DC4w15 * 0x5C;
    PutDrawEnv((DRAWENV *)envPtr);
    PutDispEnv((DISPENV *)(D_800A4034w15 + D_800A2DC4w15 * 0x14));
    if (arg2 != 0) {
        return 0;
    }
    if (gSplitScreenModenm[0] == 2) {
        u8 *otFFC;
        u8 *ot1000;
        u8 *ot1FFC;

        gOrderingTablenm[0] = (s32)arg0;
        GraphicsDrawHorizonForCar(0);
        ot1000 = (u8 *)arg0 + 0x1000;
        D_800A39C4w15[1] = (s32)ot1000;
        GraphicsUpdateAndDrawHorizonForCar(1);
        otFFC = (u8 *)arg0 + 0xFFC;
        AddPrim(otFFC, D_800A43BCw15 + (D_800A2DC4w15 << 6));
        ot1FFC = (u8 *)arg0 + 0x1FFC;
        AddPrim(ot1FFC, D_800A43BCw15 + 0x80 + (D_800A2DC4w15 << 6));
        D_800A39CCw15[-1] = (s32)ot1000;
        if ((D_800A2ED0w15[0] & 8) == 0) {
            GraphicsDrawRect(0, 0x77, 0x140, 2, 8, 8, 8, 0);
        }
        AddPrim(ot1000, D_800A43BCw15 - 0x80 + (D_800A2DC4w15 << 6));
        DrawOTag((OT_TYPE *)otFFC);
        DrawOTag((OT_TYPE *)ot1FFC);
    } else if (D_800A2EC4w15[0] != 0 && D_800A2EC8nm[0] == 0) {
        u8 *otFFC;
        u8 *ot1000;
        u8 *ot1FFC;

        gOrderingTablenm[0] = (s32)arg0;
        GraphicsDrawHorizonForCar(0);
        ot1000 = (u8 *)arg0 + 0x1000;
        GraphicsUpdateSkyAndHorizon(ot1000);
        otFFC = (u8 *)arg0 + 0xFFC;
        AddPrim(otFFC, D_800A433Cw15 + (D_800A2DC4w15 << 6));
        func_8001DA48((u8 *)arg0, 0xC6, 0x12, 0x69, 0x26);
        DrawOTag((OT_TYPE *)otFFC);
        ot1FFC = (u8 *)arg0 + 0x1FFC;
        AddPrim(ot1FFC, D_800A433Cw15 + 0x180 + (D_800A2DC4w15 << 6));
        AddPrim(ot1000, D_800A433Cw15 + (D_800A2DC4w15 << 6));
        DrawOTag((OT_TYPE *)ot1FFC);
    } else {
        GraphicsDrawHorizonForCar(0);
        DrawOTag((OT_TYPE *)((u8 *)arg0 + 0xFFC));
    }
}

void GraphicsSetGeomOffsetForMode(s32 geomOffsetX, s32 mode) {
    switch (mode) {
    case 0:
        SetGeomOffset(D_800A2DC8 / 2, 0x46);
        break;
    case 1:
        SetGeomOffset(D_800A2DC8 / 2, 0x3C);
        break;
    case 3:
        SetGeomOffset(D_800A2DC8 / 2, 0x82);
        break;
    case 4:
        SetGeomOffset(0x32, 0x12);
        break;
    }
}

extern u8 D_800A3F95[];
extern u8 D_800A3F96[];
extern u8 D_800A3F97[];
extern u8 D_800A3FF1[];
extern u8 D_800A3FF2[];
extern u8 D_800A3FF3[];

void GraphicsSetClearColor(u8 r, u8 g, u8 b) {
    D_800A3F95[0] = r;
    D_800A3F96[0] = g;
    D_800A3F97[0] = b;
    D_800A3FF1[0] = r;
    D_800A3FF2[0] = g;
    D_800A3FF3[0] = b;
}

extern DRAWENV gDrawEnvironment;
extern DISPENV gDisplayEnvironment;
void GraphicsApplyDisplayEnvironments(void) {
    VSync(0);
    PutDrawEnv(&gDrawEnvironment);
    PutDispEnv(&gDisplayEnvironment);
}

extern u8 D_800910A4[];
extern u8 *D_800A3668, *D_800A384C, *D_800A3854;
void GraphicsPartitionWorkBuffers(void) {
    D_800A384C = D_800910A4;
    D_800A3854 = D_800910A4 + 0x2000;
    D_800A3A2C = D_800910A4 + 0x4000;
    D_800A3A34 = D_800910A4 + 0x5000;
    D_800A3668 = D_800910A4 + 0x6000;
}

extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
void func_8001EBE8(s32 *transform) {
    s32 a, b, c, d, e, f, g, h, i;
    a = transform[6];
    b = transform[9];
    c = transform[12];
    d = transform[7];
    e = transform[10];
    f = transform[13];
    g = transform[8];
    h = transform[11];
    i = transform[14];
    D_800A36B0 = a;
    D_800A36B8 = b;
    D_800A36C0 = c;
    D_800A36C8 = d;
    D_800A36D0 = e;
    D_800A36D4 = f;
    D_800A36D8 = g;
    D_800A36DC = h;
    D_800A36E8 = i;
}

void MatrixLoadObjectBasis(s32 *transform) {
    D_800A36B0 = transform[0x3C / 4];
    D_800A36B8 = transform[0x48 / 4];
    D_800A36C0 = transform[0x54 / 4];
    D_800A36C8 = transform[0x40 / 4];
    D_800A36D0 = transform[0x4C / 4];
    D_800A36D4 = transform[0x58 / 4];
    D_800A36D8 = transform[0x44 / 4];
    D_800A36DC = transform[0x50 / 4];
    D_800A36E8 = transform[0x5C / 4];
}

void func_8001EC88(s32 *a, s32 *b, s32 *c) {
    s32 value0, value1, value2, value3, value4, value5, value6, value7, value8;
    value0 = a[0];
    value1 = b[0];
    value2 = c[0];
    value3 = a[1];
    value4 = b[1];
    value5 = c[1];
    value6 = a[2];
    value7 = b[2];
    value8 = c[2];
    D_800A36B0 = value0;
    D_800A36B8 = value1;
    D_800A36C0 = value2;
    D_800A36C8 = value3;
    D_800A36D0 = value4;
    D_800A36D4 = value5;
    D_800A36D8 = value6;
    D_800A36DC = value7;
    D_800A36E8 = value8;
}

void func_8001ECD8(void) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = D_800A36B8;
    b = D_800A36C8;
    c = D_800A36D8;
    d = D_800A36DC;
    D_800A36C8 = a;
    a = D_800A36C0;
    D_800A36D8 = a;
    a = D_800A36D4;
    D_800A36B8 = b;
    D_800A36C0 = c;
    D_800A36D4 = d;
    D_800A36DC = a;
}

void func_8001ED14(s32 *p) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = p[0x24 / 4];
    b = p[0x1C / 4];
    c = p[0x20 / 4];
    d = p[0x2C / 4];
    p[0x1C / 4] = a;
    a = p[0x30 / 4];
    p[0x20 / 4] = a;
    a = p[0x34 / 4];
    p[0x24 / 4] = b;
    p[0x30 / 4] = c;
    p[0x34 / 4] = d;
    p[0x2C / 4] = a;
}

void func_8001ED4C(s32 *p) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = p[0x48 / 4];
    b = p[0x40 / 4];
    c = p[0x44 / 4];
    d = p[0x50 / 4];
    p[0x40 / 4] = a;
    a = p[0x54 / 4];
    p[0x44 / 4] = a;
    a = p[0x58 / 4];
    p[0x48 / 4] = b;
    p[0x54 / 4] = c;
    p[0x58 / 4] = d;
    p[0x50 / 4] = a;
}

void MatrixTransformVector(s32 *vec) {
    s32 x, y, z;
    s32 a, b, c;

    x = vec[0];
    y = vec[1];
    z = vec[2];
    a = (D_800A36B0 * x + D_800A36B8 * y + D_800A36C0 * z) >> 16;
    b = (D_800A36C8 * x + D_800A36D0 * y + D_800A36D4 * z) >> 16;
    c = (D_800A36D8 * x + D_800A36DC * y + D_800A36E8 * z) >> 16;
    vec[0] = a;
    vec[1] = b;
    vec[2] = c;
}

extern s32 D_800A3784;
extern s32 D_800A3790;
extern s32 D_800A3794;
extern s32 D_800A3798;
extern s32 D_800A379C;
extern s32 D_800A37A4;
extern s32 D_800A37AC;
extern s32 D_800A37B4;
extern s32 D_800A37C4;
void func_8001EE74(s32 *transform) {
    s32 a, b, c, d, e, f, g, h, i;
    a = transform[6];
    b = transform[9];
    c = transform[12];
    d = transform[7];
    e = transform[10];
    f = transform[13];
    g = transform[8];
    h = transform[11];
    i = transform[14];
    D_800A3784 = a;
    D_800A3790 = b;
    D_800A3794 = c;
    D_800A3798 = d;
    D_800A379C = e;
    D_800A37A4 = f;
    D_800A37AC = g;
    D_800A37B4 = h;
    D_800A37C4 = i;
}

void func_8001EEC4(s32 *transform) {
    s32 a, b, c, d, e, f, g, h, i;
    a = transform[15];
    b = transform[18];
    c = transform[21];
    d = transform[16];
    e = transform[19];
    f = transform[22];
    g = transform[17];
    h = transform[20];
    i = transform[23];
    D_800A3784 = a;
    D_800A3790 = b;
    D_800A3794 = c;
    D_800A3798 = d;
    D_800A379C = e;
    D_800A37A4 = f;
    D_800A37AC = g;
    D_800A37B4 = h;
    D_800A37C4 = i;
}

void MatrixCombineState(void) {
    s32 matrix21;
    s32 matrix22;
    s32 matrix20;
    s32 product00A;
    s32 product01A;
    s32 product02A;
    s32 product10A;
    s32 product11A;
    s32 product12A;
    s32 product20A;
    s32 product21A;
    s32 product22A;
    s32 product00B;
    s32 product01B;
    s32 product02B;
    s32 product10B;
    s32 product11B;
    s32 product12B;
    s32 product20B;
    s32 product21B;
    s32 product22B;
    s32 matrix00;
    s32 matrix01;
    s32 matrix02;
    s32 matrix10;
    s32 matrix11;
    s32 matrix12;

    matrix00 = D_800A3784;
    matrix10 = D_800A3790;
    matrix20 = D_800A3794;
    matrix01 = D_800A3798;
    matrix11 = D_800A379C;
    matrix21 = D_800A37A4;
    matrix02 = D_800A37AC;
    matrix12 = D_800A37B4;
    matrix22 = D_800A37C4;
    product00A = MathMultiplyFixed16(matrix00, D_800A36B0);
    product00B = MathMultiplyFixed16(matrix01, D_800A36B8);
    D_800A3784 =
        product00A + product00B + MathMultiplyFixed16(matrix02, D_800A36C0);
    product01A = MathMultiplyFixed16(matrix10, D_800A36B0);
    product01B = MathMultiplyFixed16(matrix11, D_800A36B8);
    D_800A3790 =
        product01A + product01B + MathMultiplyFixed16(matrix12, D_800A36C0);
    product02A = MathMultiplyFixed16(matrix20, D_800A36B0);
    product02B = MathMultiplyFixed16(matrix21, D_800A36B8);
    D_800A3794 =
        product02A + product02B + MathMultiplyFixed16(matrix22, D_800A36C0);
    product10A = MathMultiplyFixed16(matrix00, D_800A36C8);
    product10B = MathMultiplyFixed16(matrix01, D_800A36D0);
    D_800A3798 =
        product10A + product10B + MathMultiplyFixed16(matrix02, D_800A36D4);
    product11A = MathMultiplyFixed16(matrix10, D_800A36C8);
    product11B = MathMultiplyFixed16(matrix11, D_800A36D0);
    D_800A379C =
        product11A + product11B + MathMultiplyFixed16(matrix12, D_800A36D4);
    product12A = MathMultiplyFixed16(matrix20, D_800A36C8);
    product12B = MathMultiplyFixed16(matrix21, D_800A36D0);
    D_800A37A4 =
        product12A + product12B + MathMultiplyFixed16(matrix22, D_800A36D4);
    product20A = MathMultiplyFixed16(matrix00, D_800A36D8);
    product20B = MathMultiplyFixed16(matrix01, D_800A36DC);
    D_800A37AC =
        product20A + product20B + MathMultiplyFixed16(matrix02, D_800A36E8);
    product21A = MathMultiplyFixed16(matrix10, D_800A36D8);
    product21B = MathMultiplyFixed16(matrix11, D_800A36DC);
    D_800A37B4 =
        product21A + product21B + MathMultiplyFixed16(matrix12, D_800A36E8);
    product22A = MathMultiplyFixed16(matrix20, D_800A36D8);
    product22B = MathMultiplyFixed16(matrix21, D_800A36DC);
    D_800A37C4 =
        product22A + product22B + MathMultiplyFixed16(matrix22, D_800A36E8);
}

void func_8001F198(void) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = D_800A3790;
    b = D_800A3798;
    c = D_800A37AC;
    d = D_800A37B4;
    D_800A3798 = a;
    a = D_800A3794;
    D_800A37AC = a;
    a = D_800A37A4;
    D_800A3790 = b;
    D_800A3794 = c;
    D_800A37A4 = d;
    D_800A37B4 = a;
}

void MatrixRotateVector(s32 *vec) {
    s32 x, y, z;
    s32 a, b, c;

    x = vec[0];
    y = vec[1];
    z = vec[2];
    a = (D_800A3784 * x + D_800A3790 * y + D_800A3794 * z) >> 16;
    b = (D_800A3798 * x + D_800A379C * y + D_800A37A4 * z) >> 16;
    c = (D_800A37AC * x + D_800A37B4 * y + D_800A37C4 * z) >> 16;
    vec[0] = a;
    vec[1] = b;
    vec[2] = c;
}

void func_8001F2C4(s32 arg0, s32 arg1, s32 arg2) {
    s32 *matrixA;
    s32 *matrixB;
    s32 value00, value02, value10, value12, value20, value22;
    s32 row0, row1, row2;
    s32 cross01, cross11, cross21, cross02, cross12, cross22;
    matrixA = D_800A3A2C;
    matrixB = D_800A3A34;
    value00 = matrixA[arg0];
    value02 = matrixB[arg2];
    value10 = matrixB[arg0];
    value12 = matrixA[arg1];
    value20 = matrixB[arg1];
    row0 = MathMultiplyFixed16(value00, value02);
    row1 = MathMultiplyFixed16(value10, value02);
    cross01 = MathMultiplyFixed16(value00, matrixA[arg2]);
    cross11 = MathMultiplyFixed16(value10, matrixA[arg2]);
    D_800A36B0 = MathMultiplyFixed16(value00, value12);
    D_800A36B8 = MathMultiplyFixed16(value10, value12);
    D_800A36C0 = value20;
    cross02 = MathMultiplyFixed16(row0, value20);
    D_800A36C8 = -cross11 - cross02;
    cross12 = MathMultiplyFixed16(row1, value20);
    D_800A36D0 = cross01 - cross12;
    D_800A36D4 = MathMultiplyFixed16(value12, value02);
    D_800A36D8 = row1 - MathMultiplyFixed16(cross01, value20);
    D_800A36DC = -row0 - MathMultiplyFixed16(cross11, value20);
    D_800A36E8 = MathMultiplyFixed16(value12, matrixA[arg2]);
}

void func_8001F440(s32 arg0, s32 arg1, s32 arg2) {
    s32 *matrixA;
    s32 *matrixB;
    s32 value00, value02, value10, value12, value20;
    s32 row0, row1, cross01, cross11, cross02, cross12;
    matrixA = D_800A3A2C;
    matrixB = D_800A3A34;
    value00 = matrixA[arg0];
    value02 = matrixB[arg2];
    value10 = matrixB[arg0];
    value12 = matrixA[arg1];
    value20 = matrixB[arg1];
    row0 = MathMultiplyFixed16(value00, value02);
    row1 = MathMultiplyFixed16(value10, value02);
    cross01 = MathMultiplyFixed16(value00, matrixA[arg2]);
    cross11 = MathMultiplyFixed16(value10, matrixA[arg2]);
    D_800A3784 = MathMultiplyFixed16(value00, value12);
    D_800A3790 = MathMultiplyFixed16(value10, value12);
    D_800A3794 = value20;
    cross02 = MathMultiplyFixed16(row0, value20);
    D_800A3798 = -cross11 - cross02;
    cross12 = MathMultiplyFixed16(row1, value20);
    D_800A379C = cross01 - cross12;
    D_800A37A4 = MathMultiplyFixed16(value12, value02);
    D_800A37AC = row1 - MathMultiplyFixed16(cross01, value20);
    D_800A37B4 = -row0 - MathMultiplyFixed16(cross11, value20);
    D_800A37C4 = MathMultiplyFixed16(value12, matrixA[arg2]);
}

void func_8001F5BC(s32 arg0, s32 indexA, s32 indexB) {
    s32 valueA;
    s32 slotA;
    s32 slotB;
    s32 valueB;
    s32 product;

    valueA = D_800A3A2C[indexA];
    slotA = D_800A3A34[indexA];
    valueB = D_800A3A2C[indexB];
    slotB = D_800A3A34[indexB];

    D_800A3784 = valueA;
    product = MathMultiplyFixed16(slotA, slotB);
    D_800A3790 = -product;
    product = MathMultiplyFixed16(slotA, valueB);
    D_800A3794 = -product;
    D_800A3798 = 0;
    D_800A379C = valueB;
    D_800A37A4 = -slotB;
    D_800A37AC = slotA;
    product = MathMultiplyFixed16(valueA, slotB);
    D_800A37B4 = product;
    product = MathMultiplyFixed16(valueA, valueB);
    D_800A37C4 = product;
}

void CameraBuildRotationMatrix(s32 cosYaw, s32 sinYaw, s32 cosPitch,
                               s32 sinPitch) {
    D_800A36B0 = MathMultiplyFixed16(cosYaw, cosPitch);
    D_800A36B8 = MathMultiplyFixed16(sinYaw, cosPitch);
    D_800A36C0 = sinPitch;
    D_800A36C8 = -sinYaw;
    D_800A36D0 = cosYaw;
    D_800A36D4 = 0;
    D_800A36D8 = -MathMultiplyFixed16(cosYaw, sinPitch);
    D_800A36DC = -MathMultiplyFixed16(sinYaw, sinPitch);
    D_800A36E8 = cosPitch;
}

void func_8001F728(s32 arg0) {
    typedef struct {
        s32 x;
        s32 y;
        s32 z;
    } Vec3;
    Vec3 *v;
    s32 x;
    s32 y;
    s32 z;
    extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
        D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;

    v = (Vec3 *)arg0;
    x = v->x;
    y = v->y;
    z = v->z;
    v->x = MathMultiplyFixed16(D_800A36B0, x) +
           MathMultiplyFixed16(D_800A36B8, y) +
           MathMultiplyFixed16(D_800A36C0, z);
    v->y = MathMultiplyFixed16(D_800A36C8, x) +
           MathMultiplyFixed16(D_800A36D0, y) +
           MathMultiplyFixed16(D_800A36D4, z);
    v->z = MathMultiplyFixed16(D_800A36D8, x) +
           MathMultiplyFixed16(D_800A36DC, y) +
           MathMultiplyFixed16(D_800A36E8, z);
}

void func_8001F828(s32 *p) {
    s32 a, b, c, d, e, f, g, h, i;
    a = D_800A36B0;
    b = D_800A36B8;
    c = D_800A36C0;
    d = D_800A36C8;
    e = D_800A36D0;
    f = D_800A36D4;
    g = D_800A36D8;
    h = D_800A36DC;
    i = D_800A36E8;
    p[6] = a;
    p[9] = b;
    p[12] = c;
    p[7] = d;
    p[10] = e;
    p[13] = f;
    p[8] = g;
    p[11] = h;
    p[14] = i;
}

void MatrixStoreObjectBasis(s32 *object) {
    object[0x60 / 4] = (s32)D_800A36B0;
    object[0x6C / 4] = (s32)D_800A36B8;
    object[0x78 / 4] = (s32)D_800A36C0;
    object[0x64 / 4] = (s32)D_800A36C8;
    object[0x70 / 4] = (s32)D_800A36D0;
    object[0x7C / 4] = (s32)D_800A36D4;
    object[0x68 / 4] = (s32)D_800A36D8;
    object[0x74 / 4] = (s32)D_800A36DC;
    object[0x80 / 4] = (s32)D_800A36E8;
}

void MatrixStoreToObject(s32 *object) {
    s32 value0, value1, value2, value3, value4, value5, value6, value7, value8;
    value0 = D_800A3784;
    value1 = D_800A3790;
    value2 = D_800A3794;
    value3 = D_800A3798;
    value4 = D_800A379C;
    value5 = D_800A37A4;
    value6 = D_800A37AC;
    value7 = D_800A37B4;
    value8 = D_800A37C4;
    object[15] = value0;
    object[18] = value1;
    object[21] = value2;
    object[16] = value3;
    object[19] = value4;
    object[22] = value5;
    object[17] = value6;
    object[20] = value7;
    object[23] = value8;
}

/* Wall: gcc schedules the second D_800A3A34 value reload (needed for the
 * third read) AFTER the subu/sra/sh chain instead of directly after the
 * call as retail does, so it needs a hazard nop (+4 bytes). The product
 * save (move s0,v0) is also emitted before the cos shift instead of in
 * the second jal's delay slot. Three source shapes tried. */
void VectorRotate2D(s32 angleIndex, s32 x, s32 y, s16 *rotatedPoint) {
    s32 *matrixB;
    s32 productA;
    s32 productB;

    productA = MathMultiplyFixed16(D_800A3A2C[angleIndex], x << 16);
    productB = MathMultiplyFixed16(D_800A3A34[angleIndex], y << 16);
    matrixB = D_800A3A34;
    rotatedPoint[0] = (productA - productB) >> 16;
    rotatedPoint[1] = (MathMultiplyFixed16(matrixB[angleIndex], x << 16) +
                       MathMultiplyFixed16(D_800A3A2C[angleIndex], y << 16)) >>
                      16;
}

extern s32 D_800AE868[];
extern s32 D_800AE86C[];
extern s32 D_800AE870[];
extern s32 D_800AE874[];
extern s32 D_800AE878[];
extern s32 D_800AE87C[];
extern s32 D_800AE880[];
extern s32 D_800AE884[];
extern s32 D_800AE888[];

void MatrixSaveState(void) {
    D_800AE868[0] = D_800A36B0;
    D_800AE86C[0] = D_800A36B8;
    D_800AE870[0] = D_800A36C0;
    D_800AE874[0] = D_800A36C8;
    D_800AE878[0] = D_800A36D0;
    D_800AE87C[0] = D_800A36D4;
    D_800AE880[0] = D_800A36D8;
    D_800AE884[0] = D_800A36DC;
    D_800AE888[0] = D_800A36E8;
}

void MatrixRestoreState(void) {
    D_800A36B0 = D_800AE868[0];
    D_800A36B8 = D_800AE86C[0];
    D_800A36C0 = D_800AE870[0];
    D_800A36C8 = D_800AE874[0];
    D_800A36D0 = D_800AE878[0];
    D_800A36D4 = D_800AE87C[0];
    D_800A36D8 = D_800AE880[0];
    D_800A36DC = D_800AE884[0];
    D_800A36E8 = D_800AE888[0];
}

#ifdef NON_MATCHING
/* Wall: same scheduler wall as func_8001FB28: load/negu placement differs. */
void MatrixSetRotationFromAngle(u8 *object, s32 angleIndex) {
    *(s32 *)((u8 *)object + 0x18) = ((s16 *)D_800A384C)[angleIndex] * 4;
    *(s32 *)((u8 *)object + 0x30) = 0;
    *(s32 *)((u8 *)object + 0x24) = ((s16 *)D_800A3854)[angleIndex] * 4;
    *(s32 *)((u8 *)object + 0x1C) = -((s16 *)D_800A3854)[angleIndex] * 4;
    *(s32 *)((u8 *)object + 0x34) = 0;
    *(s32 *)((u8 *)object + 0x20) = 0;
    *(s32 *)((u8 *)object + 0x2C) = 0;
    *(s32 *)((u8 *)object + 0x38) = 0x10000;
    *(s32 *)((u8 *)object + 0x28) = ((s16 *)D_800A384C)[angleIndex] * 4;
}
#else
void MatrixSetRotationFromAngle(u8 *arg0, s32 index) {
    s16 *table1;
    s16 *table2;
    s32 value1;
    s32 value2;
    s32 value3;

    table1 = (s16 *)D_800A384C;
    value1 = table1[index] * 4;
    table2 = (s16 *)D_800A3854;
    *(s32 *)(arg0 + 0x18) = value1;
    value2 = table2[index] * 4;
    *(s32 *)(arg0 + 0x30) = 0;
    *(s32 *)(arg0 + 0x24) = value2;
    *(s32 *)(arg0 + 0x1C) = -table2[index] * 4;
    value3 = table1[index] * 4;
    *(s32 *)(arg0 + 0x34) = 0;
    *(s32 *)(arg0 + 0x20) = 0;
    *(s32 *)(arg0 + 0x2C) = 0;
    *(s32 *)(arg0 + 0x38) = 0x10000;
    *(s32 *)(arg0 + 0x28) = value3;
}

#endif

void func_8001FB28(u8 *arg0, s32 index) {
    s32 *table1;
    s32 *table2;
    s32 value1;
    s32 value2;
    s32 value3;

    table1 = D_800A3A2C;
    value1 = table1[index];
    table2 = D_800A3A34;
    *(s32 *)(arg0 + 0x60) = value1;
    value2 = table2[index];
    *(s32 *)(arg0 + 0x78) = 0;
    *(s32 *)(arg0 + 0x6C) = value2;
    *(s32 *)(arg0 + 0x64) = -table2[index];
    value3 = table1[index];
    *(s32 *)(arg0 + 0x7C) = 0;
    *(s32 *)(arg0 + 0x68) = 0;
    *(s32 *)(arg0 + 0x74) = 0;
    *(s32 *)(arg0 + 0x80) = 0x10000;
    *(s32 *)(arg0 + 0x70) = value3;
}

s32 ObjectGetMagnitude3D(void *object) {
    s32 dx;
    s32 dy;
    s32 dz;

    dx = *(s32 *)((u8 *)object + 0x9C);
    dy = *(s32 *)((u8 *)object + 0xA0);
    dz = *(s32 *)((u8 *)object + 0xA4);
    return MathSqrt(dx * dx + dy * dy + dz * dz);
}

s32 VectorGetMagnitude3D(s32 x, s32 y, s32 z) {
    s32 xSq;
    s32 ySq;
    s32 zSq;
    s32 sum;

    xSq = x * x;
    ySq = y * y;
    zSq = z * z;
    sum = xSq + ySq;
    return MathSqrt(sum + zSq);
}
