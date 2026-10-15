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

/* Startup and display. */

void func_80012000(void) {
}

void GraphicsInit(void) {
    DRAWENV draw;
    DISPENV disp;
    s32 fontIds[2];

    ResetGraph(0);
    SetGraphDebug(0);
    SetDispMask(1);
    SetDefDrawEnv(&draw, 0, 0, 320, 240);
    SetDefDispEnv(&disp, 0, 0, 320, 240);
    draw.isbg = 1;
    draw.r0 = 0;
    draw.g0 = 0;
    draw.b0 = 0;
    FntLoad(960, 256);
    fontIds[0] = FntOpen(32, 32, 400, 112, 0x300, 255);
    fontIds[1] = FntOpen(32, 32, 400, 112, 0x300, 255);
    PutDrawEnv(&draw);
    PutDispEnv(&disp);
    SetDispMask(1);
}

extern u8 D_800A2D0D;
extern u8 D_800A2D0E;
extern u8 D_800A2D0F;
extern u8 D_800A39E4[];
extern u8 D_800A39E4Absolute[];
extern u8 D_800A39E4Absolute2[];
extern s32 D_800A2EB8[];
extern s32 D_800A2EC8[];
extern s32 D_800A2EB0Absolute[];
extern s32 D_800A2EACAbsolute[];
extern void func_80058D94(void);
extern void func_800531B8(void);
extern void func_800122D8(void);
extern void func_80066B08(void);
extern void func_800587A0(void);
extern void func_80059DC4(void);
extern void func_8005978C(void);
extern void func_800535A0(void);

int main(void) __asm__("func_80012108");
int main(void) {
    s32 mode;
    s32 exitCode;

    D_800A2D0D = 0;
    D_800A2EB8[0] = 0;
    D_800A2EB0Absolute[0] = 0;
    ResetCallback();
    mode = 0xF9;
    ResetGraph(0);
    SetDispMask(0);
    SetVideoMode(0);
    DecDCTReset(0);
    SoundInitTables();
    PadInitBuffers();
    func_80059DC4();
    CdInit();
    InitGeom();
    func_8005978C();
    func_800535A0();
    while (1) {
        if (D_800A39E4[0] == mode) {
            func_80058D94();
        }
        if (((D_800A39E4Absolute[0] + 3) & 0xFFU) >= 2U) {
            func_800531B8();
            HeapResetInitFlag();
        }
        func_800122D8();
        D_800A2EACAbsolute[0] = 0;
        D_800A2EC8[0] = 0;
        if (D_800A2D0E != 0 || D_800A2D0F != 0) {
            func_80066B08();
            exitCode = D_800A2D0F;
            D_800A39E4Absolute2[0] = mode;
            if (exitCode != 0) {
                func_800587A0();
                exitCode = -2;
            } else {
                exitCode = -3;
            }
            D_800A2EB0Absolute[0] = exitCode;
            D_800A2D0E = 0;
            D_800A2D0F = 0;
        } else {
            func_800587A0();
        }
    }
}

void GraphicsCompactOrderingTable(s32 tableAddress) {
    u32 linkMask;
    s32 *entry;
    s32 *firstEmpty;
    s32 previousOffset;
    s32 count;

    firstEmpty = NULL;
    count = 0x3FC;
    linkMask = 0xFFFFFF;
    previousOffset = 0xFEC;
    entry = (s32 *)(tableAddress + 0xFF0);
    do {
        if ((*entry & linkMask) !=
            ((tableAddress + previousOffset) & linkMask)) {
            if (firstEmpty != NULL) {
                *firstEmpty = (s32)entry & linkMask;
                firstEmpty = NULL;
            }
        } else if (firstEmpty == NULL) {
            firstEmpty = entry;
        }
        previousOffset -= 4;
        count -= 1;
        entry--;
    } while (count != 0);
}

INCLUDE_ASM("asm/nonmatchings/game", func_800122D8);

void SystemDrainHardware(void) {
    u8 result[16];

    DrawSync(0);
    CdSync(0, result);
    CdFlush();
    VSync(0);
    DrawSync(0);
    StopRCnt(0xF2000000);
    StopRCnt(0xF2000001);
    StopRCnt(0xF2000002);
    StopRCnt(0xF2000003);
    VSync(0);
    VSync(0);
}

void CdSeekToSector(s32 arg0) {
    u8 pos[0x18];
    s8 filter[8];
    u8 result[8];

    CdIntToPos(arg0, pos);
    do {
    } while (CdControl(2, pos, result) == 0);
    do {
    } while (CdControl(0x15, pos, result) == 0);
    CdSync(0, result);
    do {
        filter[0] = -0x80;
    } while (CdControl(0xE, filter, result) == 0);
    CdSync(0, result);
}

void SystemStopCounterAfterVSync(void) {
    VSync(0);
    StopRCnt(0xF2000001);
}

extern s32 D_800A2CFC;
extern s32 D_800A2D00;
extern s32 D_800A2D04;
extern s32 D_800A2D08;
extern s32 D_800A3708;
extern s32 D_800A370C;
extern s32 D_800B9D54[];
extern s32 D_800B9D58;
extern s32 D_800B9D5C;
extern s32 D_800B9D60;

extern void func_8001D220(s32, s32, s32, s32);

void func_80012C30(void) {
    func_8001D220(D_800A370C - D_800A3708, 0xF0, 0x14, 0);
    func_8001D220(D_800A2D00, 0xF0, 0x14, 3);
    func_8001D220(D_800B9D54[0], 0xF0, 0x23, 0);
    func_8001D220(D_800B9D58 + D_800B9D54[0], 0xF0, 0x23, 2);
    func_8001D220(D_800B9D60 + D_800B9D58 + D_800B9D54[0], 0xF0, 0x23, 3);
    func_8001D220(D_800B9D5C, 0xF0, 0x23, 1);
    D_800A2CFC = 0;
    D_800A2D00 = 0;
    D_800A2D04 = 0;
    D_800A2D08 = 0;
}

extern u32 D_800A38A0;
extern s8 D_800A2D10;

void func_80012D10(s32 arg0) {
    u32 frame;

    if (arg0 == 0) {
        D_800A38A0 = GetRCnt(0xF2000001);
        return;
    }
    frame = (u32)(0x107 - (((u32)GetRCnt(0xF2000001) - D_800A38A0) % 263));
    if (frame < 0x1F) {
        return;
    }
    do {
        func_80041AF0(D_800A2D10);
        frame = (u32)(0x107 - (((u32)GetRCnt(0xF2000001) - D_800A38A0) % 263));
    } while (frame >= 0x1F);
}

extern void *D_800A3A8C;
void func_80012E00(void) {
    D_800A3A8C = HeapAlloc(0x35B60);
}

void func_80012E28(void) {
    D_800A3A8C = (void *)STACK_BLOCK_801D6C00;
}

extern s32 strlen(char *);

void func_80012E3C(u8 *arg0) {
    s32 i;
    s32 j;
    u8 ch;

    for (i = 0, j = strlen((char *)arg0) - 1; i < j; i++, j--) {
        ch = arg0[i];
        arg0[i] = arg0[j];
        arg0[j] = ch;
    }
}

u8 *func_80012EA8(s32 value, u8 *buffer) {
    s32 count;
    s32 negative;
    s32 i;
    s32 j;
    u8 ch;

    count = 0;
    negative = 0;
    if (value < 0) {
        negative = 1;
        value = -value;
    }
    do {
        buffer[count] = (value % 10) + '0';
        count++;
        value = value / 10;
    } while (value > 0);
    if (negative != 0) {
        buffer[count] = '-';
        count++;
    }
    buffer[count] = 0;
    for (i = 0, j = strlen((char *)buffer) - 1; i < j; i++, j--) {
        ch = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = ch;
    }
    return buffer;
}

u8 *func_80012F94(s32 value, u8 *buffer) {
    s32 count;
    s32 negative;
    s32 i;
    s32 j;
    u8 ch;

    count = 0;
    negative = 0;
    if (value < 0) {
        negative = 1;
        value = -value;
    }
    do {
        buffer[count] = (value % 10) + '0';
        count++;
        value = value / 10;
    } while (value > 0);
    if (negative != 0) {
        buffer[count] = '-';
        count++;
    }
    buffer[count] = 0;
    for (i = 0, j = strlen((char *)buffer) - 1; i < j; i++, j--) {
        ch = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = ch;
    }
    return buffer;
}

#include <psxsdk/kernel.h>
/* Counter and frame control. */

void SystemInitCounter(void) {
    EnterCriticalSection();
    SetRCnt(RCntCNT1, 0xFFFF, 0x2000);
    StartRCnt(RCntCNT1);
    ExitCriticalSection();
    ResetRCnt(RCntCNT1);
}

void TextureLoadAll(void) {
    typedef struct {
        u8 b[8];
    } XBytes;
    extern u8 D_800A2D1CNM[] asm("D_800A2D1C.NON_MATCHING");
    extern void TextureLoadTim();
    extern void func_8003CDBC();
    extern s32 D_800B9F44[];
    XBytes env;
    RECT rect;
    s32 i;

    env = *(XBytes *)D_800A2D1CNM;
    rect.x = 0x3FD;
    rect.y = 0;
    rect.w = 2;
    rect.h = 2;
    LoadImage(&rect, (u_long *)&env);
    func_8003CDBC(0x40, (void *)STACK_BLOCK_80180000);
    for (i = 0; i < 0x16; i++) {
        TextureLoadTim((void *)D_800B9F44[i]);
    }
}

void func_8001317C(s32 arg0) {
    extern void func_8003CA18(s32, s32);
    extern void TextureLoadTim(void *);

    func_8003CA18(STACK_BLOCK_801E0000, arg0);
    TextureLoadTim((void *)STACK_BLOCK_801E0000);
}

extern u8 gOrderingTables[];
extern s32 gOrderingTableBank;

extern void func_8001E7EC(void *, s32, s32);

void GraphicsRenderFrame(s32 arg0) {
    s32 value0;

    SetDispMask(1);
    value0 = (gOrderingTableBank == 0) * 2;
    gOrderingTableBank = value0;
    ClearOTagR(gOrderingTables + (value0 << 12), 0x400);
    func_8001E7EC(gOrderingTables + (gOrderingTableBank << 12), arg0, 1);
    DrawSync(0);
}

extern u8 D_800A39B0[];
extern s32 D_800A36B4;
extern s32 D_800A3948;
extern u16 D_800A38C0[];

extern void GsGetTimInfo(u8 *, u8 *);

void TextureLoadTim(void *arg0) {
    RECT rect;
    u8 image[0x20];
    s32 pixels;
    u8 mode;
    u16 color;

    if (*(u32 *)arg0 == 0x10) {
        GsGetTimInfo(arg0 + 4, image);
        rect.x = *(u16 *)&image[4];
        rect.y = *(u16 *)&image[6];
        rect.w = *(u16 *)&image[8];
        rect.h = *(u16 *)&image[0xA];
        *(RECT *)&D_800A39B0[0] = rect;
        pixels = *(s32 *)&image[0xC];
        D_800A36B4 = pixels;
        mode = *(u8 *)pixels;
        LoadImage((RECT *)&image[4], (u_long *)pixels);
        if ((*(u32 *)&image[0] >> 3) & 1) {
            color = *(u16 *)(*(s32 *)&image[0x18] + mode * 2);
            D_800A3948 = 0x2108;
            D_800A38C0[0] = color;
            LoadImage((RECT *)&image[0x10], (u_long *)*(s32 *)&image[0x18]);
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/game", D_8008CA50);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CA5C);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CA68);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CA74);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CA80);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CA8C);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CA98);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CAA4);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CAB4);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CAC0);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CACC);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CAE0);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CAEC);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CB00);

void TrackLoad(u8 selectTrack) {
    typedef struct {
        s32 first;
        s32 second;
    } NameWords;
    typedef struct {
        s32 first;
        s16 second;
        s8 last;
    } NameShort;
    extern void *D_800A39C8;
    extern s32 D_800A2DE4[];
    extern s32 D_800A2E1C[];
    extern s8 D_800A2E20[];
    extern s32 D_800A2E34[];
    extern s8 D_800A2E5A[];
    extern s32 D_800A2E60[];
    extern s32 D_800A2E64[];
    extern s32 D_800A2E6CLoad asm("D_800A2E6CAbsolute");
    extern s32 D_800A2E70[];
    extern s32 D_800A2E74[];
    extern s32 D_800A2E78[];
    extern s32 D_800A2E90[];
    extern s32 D_800A2EA4[];
    extern s8 D_800A2EE8[];
    extern s32 D_800A2F50Increment asm("D_800A2F50Absolute2");
    extern s32 D_800A2F50Load asm("D_800A2F50Absolute");
    extern s32 D_800A2F84[];
    extern s32 D_800A2F88[];
    extern s32 D_800A2F8C[];
    extern u8 D_800A331E[];
    extern u8 D_800A3320[];
    extern s32 D_800A33C8;
    extern s32 D_800A3560[];
    extern s32 D_800A3598[];
    extern s32 D_800A3720;
    extern s32 D_800A3774[];
    extern s32 D_800A3820[];
    extern s32 D_800A394C[];
    extern s32 D_800A396C[];
    extern s32 D_800A3A74[];
    extern s32 D_800BE974[];
    extern u32 func_800A2CE0;
    extern NameWords D_800A2D24;
    extern NameShort D_800A2D2C;
    extern NameWords D_800A2D34;
    extern NameWords D_800A2D3C;
    extern u16 D_80090DC8[];
    extern u16 D_80090DCA[];
    extern u16 D_80090DCC[];
    extern u16 D_80090DCE[];
    extern u16 D_80090DD0[];
    extern u16 D_80090DD2[];
    extern u16 D_80090DD4[];
    extern u16 D_80090DD6[];
    extern char D_8008CA50[] __attribute__((aligned(4)));
    extern char D_8008CA5C[] __attribute__((aligned(4)));
    extern char D_8008CA68[] __attribute__((aligned(4)));
    extern char D_8008CA74[] __attribute__((aligned(4)));
    extern char D_8008CA80[] __attribute__((aligned(4)));
    extern char D_8008CA8C[] __attribute__((aligned(4)));
    extern char D_8008CA98[] __attribute__((aligned(4)));
    extern char D_8008CAA4[] __attribute__((aligned(4)));
    extern char D_8008CAB4[] __attribute__((aligned(4)));
    extern char D_8008CAC0[] __attribute__((aligned(4)));
    extern char D_8008CACC[] __attribute__((aligned(4)));
    extern char D_8008CAE0[] __attribute__((aligned(4)));
    extern char D_8008CAEC[] __attribute__((aligned(4)));
    extern char D_8008CB00[] __attribute__((aligned(4)));
    extern s32 func_80041D60(s32);
    extern void func_80015A74(s32);
    extern void func_8001E050(s32);
    extern void func_8003CA18(s32, s32);
    extern void func_800367DC(s32);
    extern s32 MathFixedDivide(s32, s32);
    extern void func_8001DF60(s32);
    extern char *strcat(char *, const char *);
    char trackName[256];
    char loadingText[256];
    s32 track;
    s32 previousButtons;
    /* Retail leaves this debug-selector bank uninitialized. */
    s32 bank;
    s32 buttons;
    s32 offset;
    s32 adjustment;
    register s32 product asm("a0");
    s32 base;
    s32 limit;
    s32 scaled;
    s32 setting0;
    s32 setting1;
    s32 enabled;
    register s32 color0 asm("a2");
    register s32 color1 asm("a1");
    register s32 color2 asm("a0");
    s32 setting;
    s32 parameter0;
    s32 parameter1;

    track = 0;
    previousButtons = 0;
    if (selectTrack != 0) {
        do {
            D_800A33C8 = func_80041D60(0);
        } while (D_800A33C8 != 0);
        do {
            bank = bank == 0;
            gOrderingTableBank = bank * 2;
            D_800A39C8 = gOrderingTables + (bank << 13);
            ClearOTagR((u_long *)D_800A39C8, 0x400);
            ClearOTagR((u_long *)(gOrderingTables + 0x1000 +
                                  (gOrderingTableBank << 12)),
                       0x400);
            D_800A33C8 = func_80041D60(0);
            if ((D_800A33C8 & 0x8000) && !(previousButtons & 0x8000)) {
                track = (track + 15) % 16;
            }
            if ((D_800A33C8 & 0x1000) && !(previousButtons & 0x1000)) {
                track = (track + 15) % 16;
            }
            if ((D_800A33C8 & 0x2000) && !(previousButtons & 0x2000)) {
                track = (track + 17) % 16;
            }
            if ((D_800A33C8 & 0x4000) && !(previousButtons & 0x4000)) {
                track = (track + 17) % 16;
            }
            previousButtons = D_800A33C8;
            switch (track) {
            case 0:
                *(NameWords *)trackName = D_800A2D24;
                break;
            case 1:
                __builtin_memcpy(trackName, D_8008CA50, 11);
                break;
            case 2:
                __builtin_memcpy(trackName, D_8008CA5C, 12);
                break;
            case 3:
                __builtin_memcpy(trackName, D_8008CA68, 11);
                break;
            case 4:
                __builtin_memcpy(trackName, D_8008CA74, 12);
                break;
            case 5:
                __builtin_memcpy(trackName, D_8008CA80, 12);
                break;
            case 6:
                __builtin_memcpy(trackName, D_8008CA8C, 9);
                break;
            case 7:
                __builtin_memcpy(trackName, D_8008CA98, 12);
                break;
            case 8:
                __builtin_memcpy(trackName, D_8008CAA4, 13);
                break;
            case 9:
                __builtin_memcpy(trackName, &D_800A2D2C, 7);
                break;
            case 10:
                __builtin_memcpy(trackName, D_8008CAB4, 10);
                break;
            case 11:
                *(NameWords *)trackName = D_800A2D34;
                break;
            case 12:
                __builtin_memcpy(trackName, D_8008CAC0, 10);
                break;
            case 13:
                *(NameWords *)trackName = D_800A2D3C;
                break;
            case 15:
                __builtin_memcpy(trackName, D_8008CACC, 17);
                break;
            case 14:
                __builtin_memcpy(trackName, D_8008CAE0, 12);
                break;
            }
            buttons = D_800A33C8;
            if (buttons & 0x80) {
                break;
            }
            if ((buttons = buttons) & 0x20) {
                break;
            }
            if ((buttons = buttons) & 0x10) {
                break;
            }
            if ((buttons = buttons) & 0x40) {
                break;
            }
            func_8001E7EC(gOrderingTables + (gOrderingTableBank << 12),
                          (s32)trackName, 1);
        } while (1);
        __builtin_memcpy(loadingText, D_8008CAEC, 17);
        strcat(loadingText, trackName);
        if (D_800A2EA4[0] == 2) {
            strcat(loadingText, D_8008CB00);
        }
        func_8001E7EC(gOrderingTables + (gOrderingTableBank << 12),
                      (s32)loadingText, 1);
    } else {
        track = func_800A2CE0;
    }
    D_800A3598[0] = 1;
    D_800A2F8C[0] = 0x1194;
    D_800A2F50Load = 0x1A7;
    D_800A2E5A[0] = 1;
    D_800A2E90[0] = 0;
    D_800A3774[0] = 0;
    D_800A3820[0] = 0;
    D_800A3560[0] = 0;
    D_800A2EE8[0] = 0;
    D_800A2E20[0] = 0;
    D_800A2F84[0] = 0;
    D_800A394C[0] = 0x383838;
    D_800A3A74[0] = 0x104838;
    D_800A396C[0] = 0x808080;
    D_800A2DE4[0] = 0x78;
    D_800A2E78[0] = ((D_800A331E[0] - 0x64) * 7) + 0x15E;
    SetBackColor(0, 0, 0);
    SetFarColor(0xFF, 0xFF, 0xFF);
    SetFogNear(0x4B0, 0x200);
    SetFogFar(0x2710, 0x200);
    offset = track * 8;
    limit = D_80090DCC[offset];
    D_800A2E6CLoad = limit;
    if (limit < 0xFA0) {
        D_800A2E6CLoad = 0xFA0;
    }
    parameter0 = D_80090DCE[offset];
    parameter1 = D_80090DD0[offset];
    D_800A2E70[0] = parameter0;
    D_800A2E34[0] = parameter1;
    switch (track) {
    case 1:
        D_800A3720 = 0xA8;
        func_80015A74(0x41);
        func_8001E050(0x42);
        func_8003CA18(STACK_BLOCK_801E0000, 0x43);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x44);
        func_800367DC(0x45);
        func_800367DC(0x46);
        D_800A2E90[0] = 0x17;
        D_800A2F50Load = 0x1B1;
        D_800A2E1C[0] = 0xA;
        D_800A2F88[0] = 0x4E20;
        D_800A2F84[0] = 1;
        break;
    case 4:
        D_800A3720 = 0xA9;
        func_80015A74(0x47);
        func_8001E050(0x48);
        func_8003CA18(STACK_BLOCK_801E0000, 0x49);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x4A);
        func_800367DC(0x4B);
        func_800367DC(0x4C);
        D_800A2E90[0] = 0x17;
        D_800A2F50Load = 0x1A7;
        D_800A2E1C[0] = 0xA;
        break;
    case 10:
        D_800A3720 = 0xAA;
        func_80015A74(0x4D);
        func_8001E050(0x4E);
        func_8003CA18(STACK_BLOCK_801E0000, 0x4F);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x50);
        func_800367DC(0x51);
        func_800367DC(0x52);
        D_800A2E90[0] = 0x17;
        D_800A2F50Load = 0x19D;
        D_800A2E1C[0] = 0xA;
        D_800A2F84[0] = 1;
        break;
    case 7:
        D_800A3720 = 0xAB;
        func_80015A74(0x53);
        func_8001E050(0x54);
        func_8003CA18(STACK_BLOCK_801E0000, 0x55);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x56);
        func_800367DC(0x57);
        func_800367DC(0x58);
        D_800A2F50Load = 0x198;
        D_800A2E90[0] = 0x17;
        D_800A2E1C[0] = 0xA;
        D_800A2F88[0] = 0x3520;
        break;
    case 15:
        D_800A3720 = 0xAC;
        func_80015A74(0x59);
        func_8001E050(0x5A);
        func_8003CA18(STACK_BLOCK_801E0000, 0x5B);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x5C);
        func_800367DC(0x5D);
        func_800367DC(0x5E);
        D_800A2E90[0] = 0x17;
        D_800A2F50Load = 0x17F;
        D_800A2E1C[0] = 0xA;
        D_800A2F84[0] = 1;
        break;
    case 13:
        D_800A3720 = 0xAD;
        func_80015A74(0x5F);
        func_8001E050(0x60);
        func_8003CA18(STACK_BLOCK_801E0000, 0x61);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x62);
        func_800367DC(0x63);
        func_800367DC(0x64);
        D_800A2E90[0] = 0x17;
        D_800A2F50Load = 0x193;
        D_800A2E1C[0] = 0xA;
        break;
    case 8:
        D_800A3720 = 0xAE;
        func_80015A74(0x65);
        func_8001E050(0x66);
        func_8003CA18(STACK_BLOCK_801E0000, 0x67);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x68);
        func_800367DC(0x69);
        func_800367DC(0x6A);
        D_800A2E1C[0] = 8;
        D_800A2F50Load = 0x1C0;
        D_800A3820[0] = 0x14;
        D_800A3560[0] = 0x14;
        D_800A2E90[0] = 0x17;
        enabled = 1;
        goto trackFlags;
    case 5:
        D_800A3720 = 0xAF;
        func_80015A74(0x6B);
        func_8001E050(0x6C);
        func_8003CA18(STACK_BLOCK_801E0000, 0x6D);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x6E);
        func_800367DC(0x6F);
        func_800367DC(0x70);
        D_800A2E1C[0] = 0xA;
        D_800A2E20[0] = 1;
        D_800A2F50Load = 0x193;
        D_800A3820[0] = 0x14;
        D_800A3560[0] = 2;
        D_800A2E90[0] = 0x17;
        D_800A3774[0] = -0xE;
        break;
    case 12:
        D_800A3720 = 0xB0;
        func_80015A74(0x71);
        func_8001E050(0x72);
        func_8003CA18(STACK_BLOCK_801E0000, 0x73);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x74);
        func_800367DC(0x75);
        func_800367DC(0x76);
        D_800A2F50Load = 0x1B1;
        D_800A2E90[0] = 0x17;
        D_800A2E1C[0] = 0xA;
        D_800A2E20[0] = 1;
        D_800A2F88[0] = 0x44C0;
        D_800A3560[0] = 0x14;
        D_800A2F84[0] = 1;
        break;
    case 11:
        D_800A3720 = 0xB1;
        func_80015A74(0x77);
        func_8001E050(0x78);
        func_8003CA18(STACK_BLOCK_801E0000, 0x79);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x7A);
        func_800367DC(0x7B);
        func_800367DC(0x7C);
        D_800A2E1C[0] = 6;
        D_800A2E20[0] = 1;
        D_800A2F50Load = 0x1C0;
        D_800A2E90[0] = 0x17;
        D_800A3598[0] = 2;
        break;
    case 14:
        D_800A3720 = 0xB2;
        func_80015A74(0x7D);
        func_8001E050(0x7E);
        func_8003CA18(STACK_BLOCK_801E0000, 0x7F);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x80);
        func_800367DC(0x81);
        func_800367DC(0x82);
        D_800A2E1C[0] = 5;
        D_800A2E20[0] = 1;
        D_800A2EE8[0] = 1;
        D_800A2F50Load = 0x1CA;
        D_800A2E90[0] = 0x17;
        D_800A394C[0] = 0x505050;
        D_800A396C[0] = 0xA0A0A0;
        D_800A3598[0] = 2;
        break;
    case 0:
        D_800A3720 = 0xB3;
        func_80015A74(0x83);
        func_8001E050(0x84);
        func_8003CA18(STACK_BLOCK_801E0000, 0x85);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x86);
        func_800367DC(0x87);
        func_800367DC(0x88);
        D_800A2EE8[0] = 1;
        D_800A2F50Load = 0x1B1;
        D_800A2E90[0] = 0x17;
        D_800A2E1C[0] = 0xA;
        D_800A3820[0] = 0xA;
        D_800A3560[0] = 0xA;
        D_800A3A74[0] = 0x383838;
        D_800A3598[0] = 0;
    default:
        break;
    case 6:
        D_800A3720 = 0xB4;
        func_80015A74(0x89);
        func_8001E050(0x8A);
        func_8003CA18(STACK_BLOCK_801E0000, 0x8B);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x8C);
        func_800367DC(0x8D);
        func_800367DC(0x8E);
        D_800A2E1C[0] = 9;
        D_800A2E20[0] = 1;
        D_800A2EE8[0] = 1;
        D_800A2E90[0] = 0x17;
        D_800A2F50Load = 0x193;
        D_800A3598[0] = 0;
        break;
    case 3:
        D_800A3720 = 0xB5;
        func_80015A74(0x8F);
        func_8001E050(0x90);
        func_8003CA18(STACK_BLOCK_801E0000, 0x91);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x92);
        func_800367DC(0x93);
        func_800367DC(0x94);
        color0 = 0x505850;
        color1 = 0x383838;
        color2 = 0x808090;
        setting = 0xA;
        enabled = 1;
        D_800A2E1C[0] = setting;
        D_800A2E90[0] = 0x17;
        D_800A2F50Load = 0x1A7;
        D_800A3820[0] = -0xA;
        D_800A2E20[0] = enabled;
        D_800A2EE8[0] = enabled;
        D_800A3560[0] = -0x44;
        D_800A394C[0] = color0;
        D_800A3A74[0] = color1;
        D_800A396C[0] = color2;
        break;
    case 16:
        D_800A3720 = 0xB6;
        func_80015A74(0x95);
        func_8001E050(0x96);
        func_8003CA18(STACK_BLOCK_801E0000, 0x97);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x98);
        func_800367DC(0x99);
        func_800367DC(0x9A);
        D_800A2E1C[0] = 8;
        D_800A2E20[0] = 1;
        D_800A2E90[0] = 0x17;
        D_800A2F50Load = 0x1B6;
        D_800A2F84[0] = 1;
        D_800A3820[0] = 0x28;
        break;
    case 9:
        D_800A3720 = 0xB7;
        func_80015A74(0x9B);
        func_8001E050(0x9C);
        func_8003CA18(STACK_BLOCK_801E0000, 0x9D);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0x9E);
        func_800367DC(0x9F);
        func_800367DC(0xA0);
        setting = 8;
        enabled = 1;
        D_800A2E1C[0] = setting;
        D_800A2E90[0] = 0x17;
        D_800A2F50Load = 0x1C5;
    trackFlags:
        D_800A2E20[0] = enabled;
        D_800A2EE8[0] = enabled;
        D_800A3598[0] = 2;
        break;
    case 2:
        D_800A3720 = 0xB8;
        func_80015A74(0xA1);
        func_8001E050(0xA2);
        func_8003CA18(STACK_BLOCK_801E0000, 0xA3);
        TextureLoadTim(STACK_BLOCK_801E0000);
        func_800367DC(0xA4);
        func_800367DC(0xA5);
        func_800367DC(0xA6);
        setting = 8;
        enabled = 1;
        D_800A2E1C[0] = setting;
        D_800A2E90[0] = 0x17;
        D_800A2E20[0] = enabled;
        D_800A2F50Load = 0x1C0;
        D_800A2EE8[0] = enabled;
        D_800A3598[0] = 0;
        break;
    }
    offset = track * 8;
    adjustment =
        ((D_80090DCA[offset] - D_80090DC8[offset]) * (100 - D_800A3320[0])) /
        50;
    base = D_80090DCC[offset - 2];
    D_800A2E74[0] = D_800A3320[0];
    D_800A2F50Increment += 20;
    D_800A2F50Load = adjustment;
    {
        s32 quotient;
        register s32 baseSpeed asm("v1");
        quotient = MathFixedDivide(base + adjustment, base);
        baseSpeed = D_80090DCE[offset - 3];
        product = baseSpeed * quotient;
    }
    scaled = D_80090DD2[offset] * D_800BE974[0];
    setting0 = D_80090DD4[offset];
    setting1 = D_80090DD6[offset];
    D_800A2E60[0] = setting0;
    D_800A2E64[0] = setting1;
    D_800A2F50Load = product >> 16;
    D_800A2F88[0] = scaled;
    func_8001DF60(product);
    func_800A2CE0 = track;
}

INCLUDE_RODATA("asm/nonmatchings/game", D_8008CB94);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CBB4);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CBD0);

#ifdef NON_MATCHING
/* Wall: semantics recovered (signed /50 then unsigned /100 final divide; D_80090ED8
 * loaded before D_80099590), but gcc schedules both index shifts above both loads and
 * allocates source into a2 / magic into a3, ours keeps expression order and picks a0/v1.
 * Consistent with the latency-5 scheduling profile. */
extern u16 D_80090ED8[];
extern s32 D_80099590[];
extern u8 D_800A3320Absolute[];
extern u8 D_800A331CAbsolute[];

s32 func_80014398(s32 arg0) {
    s32 source;
    s32 difference;
    s32 adjust;
    s32 value;
    s32 scale;
    s32 tableValue;

    tableValue = D_80090ED8[arg0];
    source = D_80099590[arg0];
    difference = source - tableValue;
    adjust = difference * (0x64 - D_800A3320Absolute[0]);
    adjust = adjust / 50;
    value = source - adjust;
    scale = D_800A331CAbsolute[0] + 0xC8;
    scale = scale / 3;
    value = value * (0xC8 - scale);
    return (u32)value / 100;
}
#else
extern u16 D_80090ED8[];
extern s32 D_80099590[];
extern u8 D_800A3320Absolute[];
extern u8 D_800A331CAbsolute[];

s32 func_80014398(s32 arg0) {
    s32 *srcPtr;
    u16 *tblPtr;
    s32 source;
    s32 tableValue;
    register s32 raw asm("a0");
    register s32 value asm("v1");
    s32 difference;
    s32 adjust;
    s32 scale;
    register s32 prod asm("v0");
    s32 magic;
    s32 sign;
    s32 magic3;
    s32 hi3;
    s32 sign3;

    srcPtr = D_80099590 + arg0;
    tblPtr = D_80090ED8 + arg0;
    tableValue = *tblPtr;
    source = *srcPtr;
    difference = source - tableValue;
    adjust = difference * (0x64 - D_800A3320Absolute[0]);
    magic = 0x51eb << 16;
    do {
    } while (0);
    magic = magic | 0x851f;
    asm volatile("mult\t%0,%1" : : "r"(adjust), "r"(magic));
    raw = D_800A331CAbsolute[0];
    magic3 = 0x5555 << 16;
    asm volatile("mfhi\t%0" : "=r"(value));
    asm volatile("ori\t%0,%1,0x5556" : "=r"(magic3) : "0"(magic3));
    scale = raw + 0xC8;
    asm volatile("mult\t%0,%1" : : "r"(scale), "r"(magic3));
    sign = adjust >> 31;
    do {
    } while (0);
    value >>= 4;
    value -= sign;
    value = source - value;
    sign3 = scale >> 31;
    asm volatile("mfhi\t%0" : "=r"(hi3));
    scale = hi3 - sign3;
    prod = value * (0xC8 - scale);
    asm volatile("nop\n\tnop");
    asm volatile("multu\t%0,%1" : : "r"(prod), "r"(magic));
    asm volatile("mfhi\t%0" : "=r"(value));
    return (u32)value >> 5;
}

#endif

extern s32 D_800A2EB0Absolute[];
extern void func_8003CAE8(s32);

void func_80014440(void) {
    s32 value;

    value = RandomScaledGet(5);
    if (value < 0) {
        value = -RandomScaledGet(5);
    } else {
        value = RandomScaledGet(5);
    }
    if (value == 4) {
        value = 5;
    }
    if (D_800A2EB0Absolute[0] == -1) {
        value = 5;
    }
    func_8003CAE8(value);
}

extern u8 D_800A364Cw15[] asm("D_800A364C.NON_MATCHING");
extern s32 D_800A2EB0w15[] asm("D_800A2EB0.NON_MATCHING");
extern s32 D_800A2E90w15[] asm("D_800A2E90.NON_MATCHING");
extern s32 D_800A2EA8w15[] asm("D_800A2EA8.NON_MATCHING");
extern s16 D_800A3696w15[] asm("D_800A3696.NON_MATCHING");
extern s16 D_800A3694w15[] asm("D_800A3694.NON_MATCHING");
extern u8 D_800A2F9Dw15[] asm("D_800A2F9D.NON_MATCHING");
extern u8 D_800A2F9Cw15[] asm("D_800A2F9C.NON_MATCHING");
extern u8 D_800A2EDCw15[] asm("D_800A2EDC.NON_MATCHING");
extern u8 D_800A2EE0w15[] asm("D_800A2EE0.NON_MATCHING");
extern u8 D_800A2EE4w15[] asm("D_800A2EE4.NON_MATCHING");
extern u8 D_800A2EDBw15[] asm("D_800A2EDB.NON_MATCHING");
extern u8 D_800A3074w15[] asm("D_800A3074.NON_MATCHING");
extern u8 D_800A3073w15[] asm("D_800A3073.NON_MATCHING");
extern u8 D_800A36E1w15[] asm("D_800A36E1.NON_MATCHING");
extern u8 D_800B9DA4w15[] asm("D_800B9DA4.NON_MATCHING");
extern u8 D_800BE70Cw15[] asm("D_800BE70C.NON_MATCHING");
extern s32 D_8008CA28[];
extern s32 D_800A2EA4w15[] asm("D_800A2EA4.NON_MATCHING");
extern u8 D_800A2EDAw15[] asm("D_800A2EDA.NON_MATCHING");

void func_800144B4(void) {
    volatile s32 pad[128];
    u8 *tbl;
    u8 *p;
    u8 *be70c;
    u8 *q;
    s32 mode;
    s32 i;
    s32 v;
    s32 c20;
    s32 c2BC;
    s32 c6;
    s32 c7;
    s32 c4;
    s32 c5;
    s32 c2;
    s32 c3;
    s32 c1;
    mode = 0;
    be70c = D_800BE70Cw15;
    if (D_800A364Cw15[-8] == 1) {
        mode = D_800A2EB0w15[0] != (-1);
    }
    i = 0;
    c20 = 0x20;
    c2BC = 0x2BC;
    c6 = 6;
    c7 = 7;
    c4 = 4;
    c5 = 5;
    c2 = 2;
    c3 = 3;
    c1 = 1;
    tbl = (u8 *)LOW_RAM_TABLE_80011E04;
loop:
    tbl[0xF] = 0;

    do {
        tbl[0x10] = c20;
        tbl[0x11] = c20;
        tbl[0x12] = c20;
        tbl[0x0] = 0;
    } while (0);
    *((s16 *)(tbl + 0x14)) = c2BC;
    tbl[0x7] = c6;
    tbl[0x8] = c7;
    tbl[0x6] = c4;
    tbl[0x5] = c5;
    tbl[0xC] = c2;
    tbl[0xB] = c3;
    tbl[0xD] = c1;
    tbl[0xE] = 0;
    tbl = tbl + 0x16;
    i = i + 1;
    if (i < 4) {
        goto loop;
    }
    if (mode == 0) {
        goto case0;
    }
    if (mode == 1) {
        goto case1;
    }
    goto dispatchDone;
case0:
    D_800A2EA4w15[0] = 0;

    goto dispatchShared;
case1:
    D_800A2EA4w15[0] = 2;

dispatchShared:
    D_8008CA28[0] = 0;

dispatchDone:
    TrackLoad(0);

    v = D_800A2EB0w15[0];
    if (v > 0) {
        D_800A2E90w15[0] = 0;
    }
    if (v == (-1)) {
        D_800A2EDAw15[0] = 1;
    } else {
        D_800A2EDAw15[0] = 0;
    }
    v = D_800A2EB0w15[0];
    if (v == 1) {
        D_800A2EA8w15[0] = v;
    }
    if (v == 2) {
        D_800A2EA8w15[0] = 999;
    }
    if (D_800A3696w15[0] != 0) {
        D_800A2F9Dw15[0] = 1;
    } else {
        D_800A2F9Dw15[0] = 0;
    }
    if (D_800A3694w15[0] != 0) {
        D_800A2F9Cw15[0] = 1;
    } else {
        D_800A2F9Cw15[0] = 0;
    }
    if (D_800A2EDCw15[0] == 0) {
        D_800A2EE0w15[0] = 0;
    }
    if (D_800A2EA4w15[0] == 2) {
        D_800A2EE4w15[0] = D_800A3074w15[0];
        D_800A2EDBw15[0] = D_800A3074w15[-1];
    } else {
        D_800A2EE4w15[0] = 0;
        D_800A2EDBw15[0] = 0;
    }
    if (D_800A2EDAw15[0] != 0) {
        D_800A2EA8w15[0] = 10;
        if (RandomScaledGet(0x18) < 0) {
            D_800A36E1w15[-1] = -RandomScaledGet(0x18);
        } else {
            D_800A36E1w15[-1] = RandomScaledGet(0x18);
        }
        i = 0;
        p = D_800B9DA4w15;
        do {
            p[0] = i;
            do {
            } while (0);
            q = (u8 *)(i + ((s32)be70c));
            q[1] = i - 1;
            i = i + 1;
            p = p + 1;
        } while (i < 0x18);
    }
}

extern s32 D_800A2EA4w18c[] asm("D_800A2EA4.NON_MATCHING");
extern s8 D_800A3A24w18c[] asm("D_800A3A24.NON_MATCHING");
extern s8 D_800A3A25w18c[] asm("D_800A3A25.NON_MATCHING");
extern s32 D_800A2EB0w18c[] asm("D_800A2EB0.NON_MATCHING");
extern u8 D_800A2EDAw18c[] asm("D_800A2EDA.NON_MATCHING");
extern s8 D_800A3620w18c[] asm("D_800A3620.NON_MATCHING");
extern s32 D_800A33CCw18c[] asm("D_800A33CC.NON_MATCHING");
extern u32 D_800A33C0w18c asm("D_800A33C0.NON_MATCHING");
extern u32 D_800A33C0addrw18c[];
asm(".globl D_800A33C0addrw18c\nD_800A33C0addrw18c = D_800A33C0.NON_MATCHING");
extern u32 D_800A33C4w18c asm("D_800A33C4.NON_MATCHING");
extern u32 D_800A2D14w18c asm("D_800A2D14.NON_MATCHING");
extern u32 D_800A2D18w18c asm("D_800A2D18.NON_MATCHING");
extern u32 D_800A359Cw18c;
extern u8 D_800A2D0Cw18c;
extern u8 D_800A2D0Ew18c asm("D_800A2D0E.NON_MATCHING");
extern u8 D_800A2D0Fw18c asm("D_800A2D0F.NON_MATCHING");
extern s32 D_800A2EC8w18c[] asm("D_800A2EC8.NON_MATCHING");
extern s32 func_80041B7C(s32);
extern void func_80023074(void);
asm(".globl D_800A359Cw18c\nD_800A359Cw18c = D_800A359C.NON_MATCHING");
asm(".globl D_800A2D0Cw18c\nD_800A2D0Cw18c = D_800A2D0C.NON_MATCHING");

void func_8001475C(void) {
    s32 *p;
    u32 *q;
    s32 i;
    s32 value;
    u32 mask;
    s32 one;

    if (D_800A2EA4w18c[0] == 0) {
        D_800A33C0w18c = func_80041B7C(0);
        D_800A33C4w18c = 0;
        if (D_800A3A24w18c[0] == 0 && D_800A2EB0w18c[0] >= 0) {
            D_800A33C4w18c = 0;
            D_800A33C0w18c = 0;
            if (D_800A2EC8w18c[0] == 0) {
                func_80023074();
            }
        }
    } else if ((D_800A3A24w18c[0] == 0 || D_800A3A25w18c[0] == 0) &&
               D_800A2EB0w18c[0] >= 0) {
        D_800A33C4w18c = 0;
        D_800A33C0w18c = 0;
        if (D_800A3A24w18c[0] == 0) {
            D_800A3620w18c[0] = 0;
        } else {
            D_800A3620w18c[0] = 1;
        }
        if (D_800A2EC8w18c[0] == 0) {
            func_80023074();
        }
    } else {
        if (D_800A2EC8w18c[0] != 0) {
            if (D_800A3620w18c[0] != 0) {
                D_800A33C0w18c = 0;
                D_800A33C4w18c = func_80041B7C(1);
            } else {
                D_800A33C0w18c = func_80041B7C(0);
                D_800A33C4w18c = 0;
            }
        } else {
            D_800A33C0w18c = func_80041B7C(0);
            D_800A33C4w18c = func_80041B7C(1);
        }
    }
b44done:
    mask = ~D_800A2D14w18c & 0x800;
    if (D_800A33C0w18c & mask) {
        if ((D_800A33C0w18c & 0x100) == 0) {
            goto f4;
        }
    }
    mask = ~D_800A2D18w18c & 0x800;
    if ((D_800A33C4w18c & mask) == 0) {
        goto loopy;
    }
    if (D_800A33C4w18c & 0x100) {
        goto loopy;
    }
f4:
    if (D_800A2EDAw18c[0] != 0) {
        D_800A2D0Cw18c = 1;
        D_800A2D0Fw18c = 1;
    } else if (D_800A359Cw18c != 0) {
        if (D_800A2EB0w18c[0] == 2) {
            D_800A2D0Cw18c = 1;
        }
    } else {
        D_800A3620w18c[0] = ((D_800A33C0w18c >> 11) ^ 1) & 1;
        func_80023074();
    }
loopy:
    i = 0;
    one = 1;
    p = D_800A33CCw18c;
    q = D_800A33C0addrw18c;
    for (; i < 2; i++) {
        if (*q & 0x100) {
            if (*q & 0x800) {
                value = *p;
                if (value > 0) {
                    value = value + 1;
                    *p = value;
                    if (value >= 41) {
                        D_800A2D0Cw18c = one;
                        D_800A2D0Ew18c = one;
                    }
                }
            } else {
                *p = one;
            }
        } else {
            *p = 0;
        }
        p++;
        q++;
    }
    if (D_800A2EDAw18c[0] != 0 &&
        (D_800A33C0w18c != 0 || D_800A33C4w18c != 0)) {
        D_800A2D0Fw18c = 1;
        D_800A2D0Cw18c = 1;
    }
}

extern u32 gPrimitiveCursorNonMatching asm("gPrimitiveCursor.NON_MATCHING");

void func_80014A40(s32 arg0) {
    if ((arg0 & 0xFF) != 0) {
        gPrimitiveCursorNonMatching = (u32)STACK_BLOCK_801E6600;
    } else {
        gPrimitiveCursorNonMatching = (u32)STACK_BLOCK_801D6C00;
    }
}

void func_80014A68(void) {
}

void func_80014A70(void) {
    extern s32 D_800A38F4;
    extern s32 D_800A3A54[];
    void *ptr;
    s32 value0;
    ptr = HeapAlloc(2);
    D_800A38F4 = (s32)ptr;
    HeapFree(ptr);
    value0 = D_800A38F4 & 0x0FFFFFFF;
    D_800A38F4 = value0;
    D_800A38F4 = (*((s32 *)D_800A3A54) & 0x0FFFFFFF) - value0;
}

extern u32 gPrimitiveCursor_gp asm("gPrimitiveCursor.NON_MATCHING");
extern u32 D_800A3570;
extern s32 D_800A38F4;
extern s32 D_800A2F10[];

s32 func_80014AC8(s32 arg0) {
    s32 freePrims;
    s32 usedPrims;

    usedPrims =
        ((gPrimitiveCursor_gp & 0xFFFFFFF) - (D_800A3570 & 0xFFFFFFF)) / 40;
    freePrims = D_800A2F10[0];
    usedPrims = freePrims - usedPrims;
    D_800A38F4 = usedPrims;
    return arg0 < D_800A38F4;
}

extern void *HeapAlloc(u32);
extern void SystemShowFatalError(char *);
extern void *D_800A3A40;
extern void *D_800A39A4;
extern s32 D_800BE970[];
extern void *D_800BE97C[];
extern s32 D_800BE984[];
extern char D_8008CB94[] __attribute__((aligned(4)));
extern char D_8008CBB4[] __attribute__((aligned(4)));
extern char D_8008CBD0[] __attribute__((aligned(4)));
/* Resource loading. */

void func_80014B10(s32 arg0, s32 arg1, s32 arg2) {
    void *ptr;
    ptr = HeapAlloc(arg0 * 8);
    D_800BE97C[0] = ptr;
    if (ptr == 0)
        SystemShowFatalError(D_8008CB94);
    ptr = HeapAlloc(arg1 * 0x2C);
    D_800A3A40 = ptr;
    if (ptr == 0)
        SystemShowFatalError(D_8008CBB4);
    D_800BE984[0] = 0;
    D_800BE970[0] = arg0;
    ptr = HeapAlloc(arg2 * 0x21C);
    D_800A39A4 = ptr;
    if (ptr == 0)
        SystemShowFatalError(D_8008CBD0);
}

INCLUDE_ASM("asm/nonmatchings/game", func_80014BEC);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CC6C);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CC7C);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CC9C);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CCA8);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CCBC);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CCD0);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CCE0);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CCF0);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CD00);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CD0C);

extern s32 D_800A2D44;

extern void ListPushFront(u8 *, u8 **, u8 **);
extern void func_8001C668(void *, void *);

s32 func_800157B0(s16 *arg0, void *arg1, u8 *arg2) {
    s32 count;
    s16 *cursor;
    s32 sentinel;

    count = 0;
    if (arg0[0] != -1) {
        sentinel = -1;
        cursor = arg0;
        do {
            ListPushFront(arg2 + *cursor * 0x2C, arg1, (u8 *)arg1 + 4);
            cursor++;
            count++;
        } while (*cursor != sentinel);
    }
    if (count != 0) {
        func_8001C668(arg1, (void *)((u8 *)arg1 + 4));
    }
    if ((count & 1) == 0) {
        count++;
    }
    return count;
}

extern s32 sprintf(char *, u8 *);

extern u8 D_8008CC6C[];

void func_80015870(u8 *arg0, void *arg1) {
    char buffer[0x40];
    u8 *node;
    u8 *next;

    node = *(u8 **)arg0;
    if (node != NULL) {
        do {
            next = *(u8 **)(node + 0x28);
            if (*(u8 *)(node + 0x13) & 1) {
                D_800A2D44 += 1;
                ListRemoveNodeWithTail(node, arg0, arg0 + 4);
                ListPushFront(node, (u8 **)arg1, (u8 **)((u8 *)arg1 + 4));
            }
            if (*(u8 *)(node + 0x12) >= 5) {
                sprintf(buffer, D_8008CC6C);
                GraphicsRenderFrame((s32)buffer);
            }
            node = next;
        } while (node != NULL);
    }
}

void func_80015930(u8 *arg0) {
    s32 minX;
    s32 minY;
    s32 minZ;
    s32 maxX;
    s32 maxY;
    s32 maxZ;
    s16 value;
    u8 *node;
    u8 *point;
    u8 **cursor;
    s32 i;
    u8 count;

    minZ = 0x7FFF;
    minY = 0x7FFF;
    minX = 0x7FFF;
    node = *(u8 **)(arg0 + 0x20);
    maxZ = -0x7D00;
    maxY = -0x7D00;
    maxX = -0x7D00;
    if (node != NULL) {
        do {
            count = *(u8 *)(node + 0x12);
            cursor = (u8 **)(node + 0x18);
            for (i = 0; i < count; i++) {
                point = cursor[i];
                value = *(s16 *)(point + 0);
                if (value < minX) {
                    minX = value;
                }
                if (maxX < value) {
                    maxX = value;
                }
                value = *(s16 *)(point + 2);
                if (value < minY) {
                    minY = value;
                }
                if (maxY < value) {
                    maxY = value;
                }
                value = *(s16 *)(point + 4);
                if (value < minZ) {
                    minZ = value;
                }
                if (maxZ < value) {
                    maxZ = value;
                }
            }
            if (!(*(u8 *)(node + 0x13) & 0x80)) {
                if (*(u32 *)(arg0 + 0x10) & 0x10000) {
                    *(u32 *)(node + 0x4) = 0x4A4A4A;
                }
            }
            node = *(u8 **)(node + 0x28);
        } while (node != NULL);
    }
    *(s16 *)(arg0 + 0x54) = minX;
    *(s16 *)(arg0 + 0x56) = minY;
    *(s16 *)(arg0 + 0x5C) = maxX;
    *(s16 *)(arg0 + 0x5E) = minY;
    *(s16 *)(arg0 + 0x64) = minX;
    *(s16 *)(arg0 + 0x66) = maxY;
    *(s16 *)(arg0 + 0x6C) = maxX;
    *(s16 *)(arg0 + 0x6E) = maxY;
    *(s16 *)(arg0 + 0x58) = 0;
    *(s16 *)(arg0 + 0x60) = 0;
    *(s16 *)(arg0 + 0x68) = 0;
    *(s16 *)(arg0 + 0x70) = 0;
}

void func_80015A74(s32 arg0) {
    extern s32 FileOpen(s32, void *);
    extern void func_80014BEC(s32 *, s32);
    extern void FileClose(s32);
    extern void SystemShowFatalError(char *);
    extern char D_8008CC7C[] __attribute__((aligned(4)));
    extern u8 D_800A2D48[];
    extern s32 D_800BE970[];
    extern u8 D_800A2D4C[];
    s32 value0;
    value0 = FileOpen(arg0, D_800A2D48);
    if (value0 == 0)
        SystemShowFatalError(D_8008CC7C);
    func_80014BEC(D_800BE970, value0);
    D_800A2D4C[0] = 1;
    FileClose(value0);
}

/* Geometry, projection, and drawing buffers. */

void func_80015AE0(s32 *transform, MATRIX *matrix) {
    matrix->m[0][0] = (s16)(-transform[7] / 16);
    matrix->m[1][0] = (s16)(-transform[8] / 16);
    matrix->m[2][0] = (s16)(transform[6] / 16);
    matrix->m[0][1] = (s16)(-transform[10] / 16);
    matrix->m[1][1] = (s16)(-transform[11] / 16);
    matrix->m[2][1] = (s16)(transform[9] / 16);
    matrix->m[0][2] = (s16)(-transform[13] / 16);
    matrix->m[1][2] = (s16)(-transform[14] / 16);
    matrix->m[2][2] = (s16)(transform[12] / 16);
}

void MatrixBuildRotationFromTransform(s32 *transform, MATRIX *matrix) {
    matrix->m[0][0] = (s16)(-transform[16] / 16);
    matrix->m[1][0] = (s16)(-transform[17] / 16);
    matrix->m[2][0] = (s16)(transform[15] / 16);
    matrix->m[0][1] = (s16)(-transform[19] / 16);
    matrix->m[1][1] = (s16)(-transform[20] / 16);
    matrix->m[2][1] = (s16)(transform[18] / 16);
    matrix->m[0][2] = (s16)(-transform[22] / 16);
    matrix->m[1][2] = (s16)(-transform[23] / 16);
    matrix->m[2][2] = (s16)(transform[21] / 16);
}

void func_80015D10(MATRIX *matrix) {
    s32 a;
    s32 b;
    s32 c;

    extern s32 D_800A3798Absolute[];
    extern s32 D_800A37ACAbsolute[];
    extern s32 D_800A3784Absolute[];
    extern s32 D_800A379CAbsolute[];
    extern s32 D_800A37B4Absolute[];
    extern s32 D_800A3790Absolute[];
    extern s32 D_800A37A4Absolute[];
    extern s32 D_800A37C4Absolute[];
    extern s32 D_800A3794Absolute[];

    a = -D_800A3798Absolute[0];
    if (a < 0) {
        a += 15;
    }
    b = D_800A37ACAbsolute[0];
    matrix->m[0][0] = (s16)(a >> 4);

    a = -b;
    if (a < 0) {
        a += 15;
    }
    c = D_800A3784Absolute[0];
    matrix->m[1][0] = (s16)(a >> 4);

    if (c < 0) {
        c += 15;
    }
    b = D_800A379CAbsolute[0];
    matrix->m[2][0] = (s16)(c >> 4);

    a = -b;
    if (a < 0) {
        a += 15;
    }
    b = D_800A37B4Absolute[0];
    matrix->m[0][1] = (s16)(a >> 4);

    a = -b;
    if (a < 0) {
        a += 15;
    }
    c = D_800A3790Absolute[0];
    matrix->m[1][1] = (s16)(a >> 4);

    if (c < 0) {
        c += 15;
    }
    b = D_800A37A4Absolute[0];
    matrix->m[2][1] = (s16)(c >> 4);

    a = -b;
    if (a < 0) {
        a += 15;
    }
    b = D_800A37C4Absolute[0];
    matrix->m[0][2] = (s16)(a >> 4);

    a = -b;
    if (a < 0) {
        a += 15;
    }
    do {
        b = D_800A3794Absolute[0];
        matrix->m[1][2] = (s16)(a >> 4);

        if (b < 0) {
            b += 15;
        }
        a = b >> 4;
        matrix->m[2][2] = (s16)a;
    } while (0);
}

s32 MathFixedDivide(s32 numerator, s32 denominator) {
    s32 quotient;
    s32 remainder;

    if (denominator == 0) {
        return 0x7FFFFFFF;
    }
    quotient = numerator / denominator;
    remainder = numerator % denominator;
    remainder = (remainder << 15) / denominator;
    numerator = remainder << 1;
    return (quotient << 16) + numerator;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80015EAC);

extern long RotTransPers_nom();
extern long RotTransPers3_nom();
extern void func_80033788();
extern void func_8003379C();

void func_80016298(s16 *arg0, u8 *arg1) {
    s32 width;
    s32 singles;

    width = (arg0[1] - arg0[0]) + 1;
    singles = width % 3;
    while (singles > 0) {
        RotTransPers_nom(arg1);
        func_80033788(arg1);
        arg1 += 0x14;
        singles--;
        width--;
    }
    singles = width;
    while (singles > 0) {
        RotTransPers3_nom(arg1, arg1 + 0x14, arg1 + 0x28);
        func_8003379C(arg1, arg1 + 0x14, arg1 + 0x28);
        arg1 += 0x3C;
        singles -= 3;
    }
}

extern s32 D_800A2D60;
extern s32 D_800A2D5C;
extern s32 *D_800A2D64;

extern void *HeapAlloc(u32);

void func_8001636C(void) {
    s32 count;
    s32 offset;
    s32 zero;
    u8 *base;
    u8 *entry;
    u8 *tailp;
    D_800A2D60 = (s32)HeapAlloc(0x1E140);
    if (D_800A2D60 == 0) {
        return;
    }
    count = 0;
    offset = 0x38;
    zero = 0;
    base = (u8 *)D_800A2D60;
    tailp = base;
    entry = tailp;
again:
    *((s32 *)(entry + 0x34)) = (s32)(base + offset);

    offset += 0x38;
    count += 1;
    entry += 0x38;
    if (count < 0x897) {
        goto again;
    }
    entry = (u8 *)D_800A2D60;
    D_800A2D5C = 0x898;
    tailp = (u8 *)((count * 0x38) + ((s32)entry));
    *((s32 *)(tailp + 0x34)) = zero;
    D_800A2D64 = (s32 *)tailp;
}

#ifdef NON_MATCHING
void *func_800163E8(u8 *arg0, s32 arg1) {
    extern s32 gOrderingTableBankAbsolute[];
    u8 *polys[250];
    u8 *first;
    u8 *poly;
    u8 *obj;
    u8 *array;
    u8 *src;
    s32 *ot;
    s32 *lut;
    s16 clutCur;
    s32 clutNew;
    s32 clutOld;
    s32 tpage;
    s32 scroll;
    s32 count;
    s32 cba;
    s32 color;
    s32 b0;
    s32 b1;
    s32 b2;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 i;
    s32 off;
    volatile s32 framePad[2];
    u8 **new_var;

    obj = *(u8 **)(arg0 + 0x36C);
    poly = (u8 *)D_800A2D60;
    count = *(s16 *)(obj + 0x2A);
    array = *(u8 **)(obj + 0x38);
    lut = (s32 *)0x1F800000;
    first = poly;
    if (count >= D_800A2D5C) {
        return NULL;
    }
    clutCur = *(s16 *)(obj + 0x30);
    if (clutCur == -1) {
        clutOld = GetClut(0x300, 0x3F);
        *(s16 *)(obj + 0x30) = clutOld;
    } else {
        clutOld = clutCur;
    }
    r1 = 0x3F - (arg1 / 16);
    clutNew = GetClut((arg1 % 16) * 16 + 0x300, r1);
    if (arg1 < 0xC) {
        tpage = GetTPage(0, 0, (arg1 % 4) * 64 + 0x300, 0);
        scroll = (arg1 / 4) * 64;
    } else {
        tpage = GetTPage(0, 0, (arg1 % 4) * 64 + 0x300, 0x100);
        scroll = ((arg1 - 12) / 4) * 64 - 0x40;
    }
    scroll -= *(s16 *)(obj + 0x32);
    src = array + 0x18;
    for (i = 0; i < count; i++) {
        polys[i] = poly;
        w0 = *(s32 *)(src - 0x10);
        w1 = *(s32 *)(src - 0xC);
        w2 = *(s32 *)(src - 8);
        w3 = *(s32 *)(src - 4);
        *(s32 *)(poly + 0xC) = w0;
        *(s32 *)(poly + 0x18) = w1;
        *(s32 *)(poly + 0x24) = w2;
        *(s32 *)(poly + 0x30) = w3;
        color = *(s32 *)(src - 0x14);
        r1 = *(u16 *)(poly + 0xE);
        cba = r1;
        b0 = color & 0xFF;
        color >>= 8;
        b1 = color & 0xFF;
        color >>= 8;
        b2 = color & 0xFF;
        r0 = lut[b0];
        r1 = lut[b1];
        r2 = lut[b2];
        r3 = lut[(color >> 8) & 0xFF];
        *(s32 *)(poly + 0x4) = r0 | 0x3C000000;
        *(s32 *)(poly + 0x10) = r1;
        *(s32 *)(poly + 0x28) = r2;
        *(s32 *)(poly + 0x1C) = r3;
        if (cba == clutOld) {
            *(u16 *)(poly + 0xE) = clutNew;
            *(u16 *)(poly + 0x1A) = tpage;
            *(u8 *)(poly + 0xD) += scroll;
            *(u8 *)(poly + 0x19) += scroll;
            *(u8 *)(poly + 0x25) += scroll;
            *(u8 *)(poly + 0x31) += scroll;
        }
        if (i < count - 1) {
            src += 0x2C;
            poly = *(u8 **)(poly + 0x34);
        }
    }
    if (*(s16 *)(obj + 0x2C) > 0) {
        ot = (s32 *)(gOrderingTableBankAbsolute[0] * 0x30 + (s32)arg0 + 0x440);
        new_var = polys;
        i = 0;
        off = 0;
        do {
            ot[i] = new_var[*(s16 *)(*(u8 **)(obj + 0x40) + off + 0x10)];
            off += 0x18;
            i++;
        } while (i < *(s16 *)(obj + 0x2C));
    }
    i = *(s32 *)(poly + 0x34);
    *(s32 *)(poly + 0x34) = 0;
    D_800A2D5C -= count;
    D_800A2D60 = i;
    *(s32 *)(arg0 + gOrderingTableBankAbsolute[0] * 4 + 0x430) = (s32)poly;
    return first;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800163E8);
#endif

extern s32 D_800A2D5C;
void func_80016724(s32 value, s32 *next, s32 size) {
    s32 *current;
    current = D_800A2D64;
    D_800A2D64 = next;
    current[0x34 / 4] = value;
    D_800A2D5C += size;
}

extern s32 gOrderingTableBankAbsolute[];
extern s32 D_800A2CF8[];
extern s32 gOrderingTableBankLui asm("gOrderingTableBankAbsolute");
extern s32 D_800A2D5C;
void func_80016744(u32 arg0) {
    s32 bank;
    u32 entries;
    s32 oldEntry;
    s32 value;
    s32 offset;
    s32 hw;
    u32 ptr;
    s32 size;
    s32 extra;

    bank = gOrderingTableBankLui;
    entries = (bank << 2) + arg0;
    oldEntry = *(s32 *)(entries + 0x420);
    if (oldEntry != 0) {
        value = *(s8 *)(arg0 + bank + 0x41C);
        offset = value * 0x44 + *(s32 *)(arg0 + 0x370);
        hw = *(s16 *)(offset + 0x2A);
        ptr = (u32)D_800A2D64;
        size = D_800A2D5C;
        extra = *(s32 *)(entries + 0x430);
        *(s32 *)(ptr + 0x34) = oldEntry;
        D_800A2D64 = (s32 *)extra;
        *(s32 *)(entries + 0x420) = 0;
        D_800A2D5C = size + hw;
    }
    *(s8 *)(arg0 + gOrderingTableBankLui + 0x41C) = -1;
}

INCLUDE_ASM("asm/nonmatchings/game", func_800167BC);

void func_800168F8(u8 *arg0, s32 arg1) {
    s32 pad[2];
    s16 clutCur;
    s32 clutNew;
    s32 clutOld;
    s32 tpage;
    s32 scroll;
    s32 count;
    u8 *array;
    u8 *p;
    s32 i;
    u8 x0;
    u8 x1;
    u8 x2;
    u8 x3;

    (void)&pad;
    clutCur = *(s16 *)(arg0 + 0x30);
    count = *(s16 *)(arg0 + 0x2A);
    array = *(u8 **)(arg0 + 0x38);
    if (clutCur == -1) {
        clutOld = GetClut(0x300, 0x3F);
        *(s16 *)(arg0 + 0x30) = clutOld;
        *(s16 *)(arg0 + 0x32) = 0;
    } else {
        clutOld = clutCur;
    }
    clutNew = GetClut((arg1 % 16) * 16 + 0x300, 0x3F - arg1 / 16);
    if (clutOld != clutNew) {
        if (arg1 < 0xC) {
            tpage = GetTPage(0, 0, (arg1 % 4) * 64 + 0x300, 0);
            scroll = (arg1 / 4) * 64;
        } else {
            tpage = GetTPage(0, 0, (arg1 % 4) * 64 + 0x300, 0x100);
            scroll = ((arg1 - 12) / 4) * 64 - 0x40;
        }
        do {
            scroll -= *(s16 *)(arg0 + 0x32);
            i = 0;
            if (count > 0) {
                p = array + 0x15;
            again:
                if (*(s16 *)(p - 0xB) == clutOld) {
                    x0 = *(u8 *)(p - 0xC);
                    x1 = *(u8 *)(p - 0x8);
                    x2 = *(u8 *)(p - 0x4);
                    x3 = *(u8 *)(p);
                    *(s16 *)(p - 0xB) = clutNew;
                    *(s16 *)(p - 0x7) = tpage;
                    *(u8 *)(p - 0xC) = x0 + scroll;
                    *(u8 *)(p - 0x8) = x1 + scroll;
                    *(u8 *)(p - 0x4) = x2 + scroll;
                    *(u8 *)(p) = x3 + scroll;
                }
                i++;
                p += 0x2C;
                if (i < count) {
                    goto again;
                }
            }
        } while (0);
        *(s16 *)(arg0 + 0x30) = clutNew;
        *(s16 *)(arg0 + 0x32) = *(u16 *)(arg0 + 0x32) + scroll;
    }
}

extern s32 MathMultiplyFixed16(s32, s32);

s32 func_80016ACC(u8 *arg0, s16 *arg1) {
    extern s32 D_800A3A34Absolute[];
    s32 pad[4];
    register s32 f asm("a0");
    register s32 fade asm("a1");
    s32 y0;
    s32 y1;
    u8 *base;
    u8 *p;
    s32 count;
    u8 *lp;
    s32 i;
    s32 den;
    s32 den2;
    s32 q;
    s32 rem;
    s32 t;
    s32 q2;
    s32 rem2;
    s32 fdiv1;
    s32 fdiv2;
    s32 x;
    s32 t2;
    s32 w;

    (void)&pad;
    y0 = arg1[0];
    base = *(u8 **)(arg0 + 0x36C);
    f = arg0[0x410];
    p = *(u8 **)(base + 0x14) + y0 * 0x14;
    y1 = arg1[1];
    count = y1 - y0 + 1;
    if (f < 0x31U) {
        goto copyOnly;
    }
    fade = f;
    den = 100;
    q = fade / den;
    rem = fade % den;
    fdiv1 = (q << 0x10) + (((rem << 15) / den) << 1);
    t = fade;
    if (fade < 0) {
        t = fade + 15;
    }
    t = t & 0x1F0;
    t = fade - t;
    den2 = 16;
    q2 = t / den2;
    rem2 = t % den2;
    fdiv2 = (q2 << 0x10) + (((rem2 << 15) / den2) << 1);
    x = MathMultiplyFixed16(0x04000000, fdiv2);
    x = MathMultiplyFixed16(0x640000, (*(s32 **)D_800A3A34Absolute)[x >> 16]);
    x = MathMultiplyFixed16(fdiv1, x);
    x = x >> 16;
    fade = x;
    if (x < 0) {
        fade = -fade;
    }
    t2 = (u32)fade >> 31;
    t2 = fade - -t2;
    fade = t2 >> 1;
    i = 0;
    if (count > 0) {
        lp = p + 4;
        do {
            w = *(s32 *)(lp + 0xC);
            i++;
            w = w + fade;
            *(s16 *)lp = w;
            lp += 0x14;
        } while (i < count);
    }
    return 0;
copyOnly:
    i = 0;
    if (count > 0) {
        lp = p + 4;
        do {
            *(s16 *)lp = *(s32 *)(lp + 0xC);
            i++;
            lp += 0x14;
        } while (i < count);
    }
    return 1;
}
