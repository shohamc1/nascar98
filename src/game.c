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
#include "game.h"

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
extern u8 D_800A39E4Absolute2[];
extern void GameRunSession(void);

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
    CardInit();
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
        GameRunSession();
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

void GameRunSession(void) {
    extern s32 D_800A2F74[];
    extern s32 D_800A2F54[];
    extern s32 D_800A2EC4Absolute[];
    extern u8 D_800A306DAbsolute[];
    extern s16 D_800A3694Absolute[];
    extern s8 D_800A2F9CAbsolute[];
    extern s32 D_800A3720;
    extern s32 D_800A3948;
    extern u8 D_800A3884[];
    extern s32 D_800A2EB0After[] asm("D_800A2EB0.NON_MATCHING");
    extern s32 D_800A33C8;
    extern u8 D_800A2D0C;
    extern s8 D_800A2D10;
    extern s32 D_800A359C;
    extern s32 D_800A33D0;
    extern s32 D_800A33CC;
    extern u8 D_800A2EDAAbsolute[] asm("D_800A2EDA");
    extern void *D_800A39C8;
    extern u8 *D_800A3A8C;
    extern u32 D_800A3570;
    extern u32 gPrimitiveCursorRun asm("gPrimitiveCursor.NON_MATCHING");
    extern s32 D_800A3708;
    extern s32 D_800A370C;
    extern s32 D_800B9DA0[];
    typedef struct {
        s32 first;
        s32 gap;
        s32 second;
        s32 pad[6];
        s32 elapsed;
    } SessionTiming;
    extern SessionTiming D_800B9D58Run asm("D_800B9D58");
    extern s32 D_800A2CFC;
    extern s32 D_800A38F4;
    extern s32 D_800A2D50[];
    extern s32 D_800A2D14;
    extern s32 D_800A2D18;
    extern s32 D_800A33C0;
    extern s32 D_800A33C4;
    extern u8 D_800A3075[];
    extern s32 D_800A2D00;
    extern DRAWENV D_800BDD4C[];
    extern DISPENV D_800BDE04[];
    extern void GraphicsInitScreen(s32, s32, s32, s32);
    extern void GraphicsPartitionWorkBuffers(void);
    extern void func_8002DDA0(void);
    extern void func_80041850(void);
    extern void TextureLoadAll(void);
    extern void func_80017E08(void);
    extern void func_80018C88(void);
    extern void func_800144B4(void);
    extern void func_8002F514(void);
    extern void func_8001636C(void);
    extern void func_80025370(s32);
    extern void func_8002F5A4(void);
    extern void func_80012E00(void);
    extern void func_80014440(void);
    extern void CdApplyMixVolume(void);
    extern void func_8002F2CC(void);
    extern void GraphicsSetClearColor(u32, u32, u32);
    extern void func_80045288(void);
    extern void func_80014A70(void);
    extern void ReplayAllocBuffer(void);
    extern void func_80041DEC(void);
    extern void func_80041AF0Run(s8) asm("func_80041AF0");
    extern void SystemInitCounter(void);
    extern void func_8004195C(void);
    extern void func_80041328(void);
    extern void func_8001475C(void);
    extern void RaceUpdateFrame(void);
    extern void GraphicsDrawRaceViews(void);
    extern void func_8001C34C(void);
    extern void func_8003CC48(void);
    extern void func_8001E7EC(void *, s32 *, s32);
    extern void func_8003CF04(void);
    extern void func_80041A28(void);
    extern void GraphicsSetColor(s32, s32, s32);
    extern s32 HudTextWidth(u8 *);
    extern void HudDrawText(u8 *, s16, s32, s8);
    extern void func_8001D778(s32, s32, s32, s32, s32, s32, s32, s32);
    extern void func_8003C1CC(void);
    extern void func_8003C528(void);
    extern void func_80067598(void);
    extern void func_8001BDBC(s32);
    extern void func_80066CFC(void);
    extern void func_80067DFC(void);
    extern void SystemStopCounterAfterVSync(void);
    register SessionTiming *timings asm("s3");
    u8 *ot;
    u8 *tables;
    u8 *secondTables;
    register s32 mode asm("v1");
    register s32 checkValue asm("v0");
    s32 sync;
    s32 bank;
    s32 timeout;
    s32 firstButtons;
    s32 buttons;
    s32 count;
    s32 *timer;
    s32 ticks;

    D_800A2F74[0] = 0;
    D_8008CA28[0] = 0;
    D_800A2D10 = 0;
    D_800A2F54[0] = 0;
    D_800A2EC4Absolute[0] = 0;
    VSync(0);
    GraphicsInitScreen(320, 240, 160, 0);
    bank = 0;
    GraphicsPartitionWorkBuffers();
    timeout = 1200;
    func_8002DDA0();
    func_80041850();
    TextureLoadAll();
    func_80017E08();
    func_80018C88();
    func_800144B4();
    func_8002F514();
    func_8001636C();
    func_80025370(D_800A3720);
    func_8002F5A4();
    func_80012E00();
    SsSetMVol(127, 127);
    if (D_800A306DAbsolute[0] != 0 && D_800A2EB0Absolute[0] != -1) {
        D_800A2F9CAbsolute[0] = 0;
    } else {
        if (D_800A3694Absolute[0] != 0) {
            D_800A2F9CAbsolute[0] = 1;
        } else {
            D_800A2F9CAbsolute[0] = 0;
        }
        func_80014440();
    }
    CdApplyMixVolume();
    func_8002F2CC();
    GraphicsSetClearColor((u32)(D_800A3948 & 0x7C00) >> 7,
                          (u32)(D_800A3948 & 0x3E0) >> 2,
                          (D_800A3948 & 31) << 3);
    func_80045288();
    func_80014A70();
    ReplayAllocBuffer();
    func_80041DEC();
    D_800A3884[0] = 1;
    if (D_800A2EB0Absolute[0] != -1) {
        D_800A33C8 = 0;
        do {
            func_80041AF0Run(0);
            if (D_800A2EA4Absolute[0] != 0) {
                firstButtons = PadGetButtons(0);
                buttons = firstButtons | PadGetButtons(1);
            } else {
                buttons = PadGetButtons(0);
            }
            D_800A33C8 = buttons;
        } while (!(buttons & 0x800));
    }
    func_80066B08();
    SystemInitCounter();
    GetRCnt(0xF2000001);
    func_8004195C();
    func_80041328();
    SetDispMask(1);
    tables = gOrderingTables;
    secondTables = tables + 0x1000;
    /* Keep the table bases before the timing-pointer assignment. */
    asm("" : : "r"(tables), "r"(secondTables) : "s3");
    timings = &D_800B9D58Run;
    /* Keep the timing base at its first field. */
    asm("" : : "r"(timings));
    D_800A2D0C = 0;
    D_800A359C = 0;
    D_800A33D0 = 0;
    D_800A33CC = 0;
    do {
        if (D_800A2EDAAbsolute[0] != 0 && timeout-- == 0) {
            D_800A2D0C = 1;
        }
        bank = bank == 0;
        D_800A39C8 = (u8 *)((bank << 13) + (u32)tables);
        gOrderingTableBank = bank * 2;
        D_800A3570 = (u32)(D_800A3A8C + bank * 0x1ADB0);
        gPrimitiveCursorRun = D_800A3570;
        ClearOTagR((u_long *)D_800A39C8, 0x400);
        ClearOTagR(
            (u_long *)((u8 *)((gOrderingTableBank << 12) + (u32)secondTables)),
            0x400);
        ticks = GetRCnt(0xF2000001);
        count = 19;
        timer = D_800B9DA0;
        D_800A3708 = ticks;
        do {
            *timer = ticks;
            count--;
            timer--;
        } while (count >= 0);
        timings->second = 0;
        timings->first = 0;
        D_800A2CFC = 0;
        D_800A38F4 = 0;
        D_800A2D50[0] = 0;
        func_8001475C();
        D_800A2D14 = D_800A33C0;
        D_800A2D18 = D_800A33C4;
        RaceUpdateFrame();
        GraphicsDrawRaceViews();
        timings->elapsed = GetRCnt(0xF2000001) - D_800A3708;
        func_8001C34C();
        D_800A370C = GetRCnt(0xF2000001);
        func_8003CC48();
        if (D_800A3075[0] != 0) {
            while ((u32)(GetRCnt(0xF2000001) - D_800A3708) < 270U) {
                func_80041AF0Run(D_800A2D10);
            }
        } else {
            while ((u32)(GetRCnt(0xF2000001) - D_800A3708) < 530U) {
                func_80041AF0Run(D_800A2D10);
            }
        }
        D_800A2D00 = 0;
        GetRCnt(0xF2000001);
        func_80041AF0Run(0);
        {
            u32 linkMask;
            s32 *entry;
            s32 *firstEmpty;
            s32 previousOffset;
            s32 count;
            s32 tableAddress;

            firstEmpty = NULL;
            count = 0x3FC;
            linkMask = 0xFFFFFF;
            previousOffset = 0xFEC;
            tableAddress =
                (s32)((u8 *)((gOrderingTableBank << 12) + (u32)tables));
            entry = (s32 *)(tableAddress + 0xFF0);
            do {
                if ((*entry & linkMask) !=
                    ((tableAddress + previousOffset) & linkMask)) {
                    if (firstEmpty != NULL) {
                        *firstEmpty = (u32)entry & linkMask;
                        firstEmpty = NULL;
                    }
                } else if (firstEmpty == NULL) {
                    firstEmpty = entry;
                }
                previousOffset -= 4;
                count--;
                entry--;
            } while (count != 0);
        }
        DrawSync(0);
        D_800A2D00 = GetRCnt(0xF2000001) - D_800A3708;
        if (D_800A2EACAbsolute[0] != 2 || D_800A2EC8[0] != 0) {
            func_8001E7EC((u8 *)((gOrderingTableBank << 12) + (u32)tables),
                          &sync, 0);
        }
    } while (D_800A2D0C == 0);
    if (D_800A2EB0Absolute[0] == 2) {
        func_8003CF04();
    }
    func_80041A28();
    DrawSync(0);
    if (D_800A2EB0After[0] == -1 && D_800A2D0F == 0) {
        ot = gOrderingTables;
        D_800A3570 = (u32)(D_800A3A8C + bank * 0x1ADB0);
        gPrimitiveCursorRun = D_800A3570;
        ClearOTagR((u_long *)(ot + (gOrderingTableBank << 12)), 0x400);
        GraphicsSetColor(255, 128, 64);
        bank ^= 1;
        HudDrawText(D_8009A400[0],
                    (s16)((320 - HudTextWidth(D_8009A400[0])) << 15 >> 16), 110,
                    0);
        func_8001D778(0, 0, 320, 240, 0, 0, 0, 0);
        /* Keep the base operand first. */
        asm("addu %0, %0, %2"
            : "=r"(ot)
            : "0"(ot), "r"(gOrderingTableBank << 12));
        DrawOTag((u_long *)(ot + 0xFFC));
        /* Keep the table pointer across the GPU call. */
        asm("" : : "r"(ot));
        DrawSync(0);
        VSync(0);
        PutDrawEnv(&D_800BDD4C[bank]);
        PutDispEnv(&D_800BDE04[bank]);
    } else {
        if (D_800A2EACAbsolute[0] != 0) {
            mode = D_800A2EB0Absolute[0];
            checkValue = 2;
            if (mode == checkValue) {
                goto checkMode;
            }
            goto otherDisplay;
        }
        func_8003C1CC();
        SetDispMask(0);
        mode = D_800A2EB0Absolute[0];
        checkValue = 2;
    checkMode:
        /* Keep the mode test on both paths. */
        asm("" : "=r"(mode) : "0"(mode), "r"(checkValue));
        if (mode == checkValue) {
            func_8003C528();
            if (D_800A2D0E == 0) {
                D_800A3570 = (u32)(D_800A3A8C + bank * 0x1ADB0);
                gPrimitiveCursorRun = D_800A3570;
                ClearOTagR(
                    (u_long *)(gOrderingTables + (gOrderingTableBank << 12)),
                    0x400);
                D_800A39C8 = gOrderingTables + (gOrderingTableBank << 12);
                func_80067598();
                goto finishDisplay;
            }
            goto hideDisplay;
        }
        goto displayDone;
    otherDisplay:
        if (D_800A2D0E != 0 || D_800A359C == 0) {
        hideDisplay:
            SetDispMask(0);
            goto displayDone;
        }
        D_800A3570 = (u32)(D_800A3A8C + bank * 0x1ADB0);
        gPrimitiveCursorRun = D_800A3570;
        ClearOTagR((u_long *)(gOrderingTables + (gOrderingTableBank << 12)),
                   0x400);
        func_8001BDBC(D_800A359C >= 540);
        func_80066CFC();
    finishDisplay:
        func_80067DFC();
    }
displayDone:
    SystemStopCounterAfterVSync();
    HeapResetInitFlag();
}

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
extern s32 D_800B9D58;
extern s32 D_800B9D5C;
extern s32 D_800B9D60;

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

void TextReverseString(u8 *arg0) {
    s32 i;
    s32 j;
    u8 ch;

    for (i = 0, j = strlen((char *)arg0) - 1; i < j; i++, j--) {
        ch = arg0[i];
        arg0[i] = arg0[j];
        arg0[j] = ch;
    }
}

u8 *TextFormatInt(s32 value, u8 *buffer) {
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

u8 *TextFormatLong(s32 value, u8 *buffer) {
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

static const char sTrackNameSaltBasin[] = "salt basin";
static const char sTrackNameWillowLane[] = "willow lane";
static const char sTrackNamePineRidge[] = "pine ridge";
static const char sTrackNameRanchTower[] = "ranch tower";
static const char sTrackNameCedarWoods[] = "cedar woods";
static const char sTrackNameMichigan[] = "Michigan";
static const char sTrackNameSearsPoint[] = "Sears Point";
static const char sTrackNameWatkinsGlen[] = "Watkins Glen";
static const char sTrackNameTalladega[] = "Talladega";
static const char sTrackNameCharlotte[] = "Charlotte";
static const char sTrackNameSurfersParadise[] = "surfers paradise";
static const char sTrackNameThunderdome[] = "thunderdome";
static const char sTrackLoadingText[] = "Now Loading ... ";
static const char sTrackTwoPlayersText[] = "\nTwo Players";

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
    extern s32 D_800A2E6CLoad asm("D_800A2E6CAbsolute");
    extern s32 D_800A2E70[];
    extern s32 D_800A2E74[];
    extern s32 D_800A2E90[];
    extern s8 D_800A2EE8[];
    extern s32 D_800A2F50Increment asm("D_800A2F50Absolute2");
    extern s32 D_800A2F50Load asm("D_800A2F50Absolute");
    extern s32 D_800A2F84[];
    extern s32 D_800A2F88[];
    extern s32 D_800A2F8C[];
    extern u8 D_800A331E[];
    extern s32 D_800A33C8;
    extern s32 D_800A3560[];
    extern s32 D_800A3598[];
    extern s32 D_800A3720;
    extern s32 D_800A3774[];
    extern s32 D_800A3820[];
    extern s32 D_800A394C[];
    extern s32 D_800A396C[];
    extern s32 D_800A3A74[];
    extern u32 func_800A2CE0;
    extern NameWords gTrackNameJuniper;
    extern NameShort gTrackNamePocono;
    extern NameWords gTrackNameAtlanta;
    extern NameWords gTrackNameBristol;
    extern u16 D_80090DC8[];
    extern u16 D_80090DCA[];
    extern u16 D_80090DCC[];
    extern u16 D_80090DCE[];
    extern u16 D_80090DD0[];
    extern u16 D_80090DD2[];
    extern u16 D_80090DD4[];
    extern u16 D_80090DD6[];
    extern s32 func_80041D60(s32);
    extern void TrackLoadFromFile(s32);
    extern void GraphicsLoadImageBank(s32);
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
                *(NameWords *)trackName = gTrackNameJuniper;
                break;
            case 1:
                __builtin_memcpy(trackName, sTrackNameSaltBasin, 11);
                break;
            case 2:
                __builtin_memcpy(trackName, sTrackNameWillowLane, 12);
                break;
            case 3:
                __builtin_memcpy(trackName, sTrackNamePineRidge, 11);
                break;
            case 4:
                __builtin_memcpy(trackName, sTrackNameRanchTower, 12);
                break;
            case 5:
                __builtin_memcpy(trackName, sTrackNameCedarWoods, 12);
                break;
            case 6:
                __builtin_memcpy(trackName, sTrackNameMichigan, 9);
                break;
            case 7:
                __builtin_memcpy(trackName, sTrackNameSearsPoint, 12);
                break;
            case 8:
                __builtin_memcpy(trackName, sTrackNameWatkinsGlen, 13);
                break;
            case 9:
                __builtin_memcpy(trackName, &gTrackNamePocono, 7);
                break;
            case 10:
                __builtin_memcpy(trackName, sTrackNameTalladega, 10);
                break;
            case 11:
                *(NameWords *)trackName = gTrackNameAtlanta;
                break;
            case 12:
                __builtin_memcpy(trackName, sTrackNameCharlotte, 10);
                break;
            case 13:
                *(NameWords *)trackName = gTrackNameBristol;
                break;
            case 15:
                __builtin_memcpy(trackName, sTrackNameSurfersParadise, 17);
                break;
            case 14:
                __builtin_memcpy(trackName, sTrackNameThunderdome, 12);
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
        __builtin_memcpy(loadingText, sTrackLoadingText, 17);
        strcat(loadingText, trackName);
        if (D_800A2EA4[0] == 2) {
            strcat(loadingText, sTrackTwoPlayersText);
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
        TrackLoadFromFile(0x41);
        GraphicsLoadImageBank(0x42);
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
        TrackLoadFromFile(0x47);
        GraphicsLoadImageBank(0x48);
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
        TrackLoadFromFile(0x4D);
        GraphicsLoadImageBank(0x4E);
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
        TrackLoadFromFile(0x53);
        GraphicsLoadImageBank(0x54);
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
        TrackLoadFromFile(0x59);
        GraphicsLoadImageBank(0x5A);
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
        TrackLoadFromFile(0x5F);
        GraphicsLoadImageBank(0x60);
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
        TrackLoadFromFile(0x65);
        GraphicsLoadImageBank(0x66);
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
        TrackLoadFromFile(0x6B);
        GraphicsLoadImageBank(0x6C);
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
        TrackLoadFromFile(0x71);
        GraphicsLoadImageBank(0x72);
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
        TrackLoadFromFile(0x77);
        GraphicsLoadImageBank(0x78);
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
        TrackLoadFromFile(0x7D);
        GraphicsLoadImageBank(0x7E);
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
        TrackLoadFromFile(0x83);
        GraphicsLoadImageBank(0x84);
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
        TrackLoadFromFile(0x89);
        GraphicsLoadImageBank(0x8A);
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
        TrackLoadFromFile(0x8F);
        GraphicsLoadImageBank(0x90);
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
        TrackLoadFromFile(0x95);
        GraphicsLoadImageBank(0x96);
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
        TrackLoadFromFile(0x9B);
        GraphicsLoadImageBank(0x9C);
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
        TrackLoadFromFile(0xA1);
        GraphicsLoadImageBank(0xA2);
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

extern u16 D_80090ED8[];
extern s32 D_80099590[];
extern u8 D_800A3320Absolute[];

s32 func_80014398(s32 arg0) {
    s32 *srcPtr;
    u16 *tblPtr;
    s32 source;
    s32 adjust;
    s32 value;
    s32 scale;
    s32 prod;
    s32 tableValue;

    srcPtr = D_80099590 + arg0;
    tblPtr = D_80090ED8 + arg0;
    tableValue = *tblPtr;
    source = *srcPtr;
    adjust = (source - tableValue) * (0x64 - D_800A3320Absolute[0]);
    value = adjust / 50;
    value = source - value;
    scale = D_800A331CAbsolute[0] + 0xC8;
    scale = scale / 3;
    /* Rank anchor: two extra refs keep value in v1 without folding the
     * final product into it, so the product reloads into v0. Emits nothing. */
    asm("" : "=r"(value) : "0"(value));
    prod = value * (0xC8 - scale);
    return (u32)prod / 100;
}

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
extern u8 D_800A36E1w15[] asm("D_800A36E1.NON_MATCHING");
extern u8 D_800B9DA4w15[] asm("D_800B9DA4.NON_MATCHING");
extern u8 D_800BE70Cw15[] asm("D_800BE70C.NON_MATCHING");
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
        D_800A33C0w18c = PadGetButtons(0);
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
                D_800A33C4w18c = PadGetButtons(1);
            } else {
                D_800A33C0w18c = PadGetButtons(0);
                D_800A33C4w18c = 0;
            }
        } else {
            D_800A33C0w18c = PadGetButtons(0);
            D_800A33C4w18c = PadGetButtons(1);
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

extern void *D_800A39A4;
extern s32 D_800BE970[];
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

typedef struct {
    s32 x, y, z;
} FileVertex;
typedef struct {
    s32 vertexCount, objectCount, faceCount;
    u8 *vertices, *objects, *faces;
} TrackResource;
typedef struct {
    s32 w[4];
} TrackCopy16;
typedef struct {
    s32 w[7];
} TrackCopy28;
typedef struct {
    s32 w[135];
} TrackNode;
extern s32 FileSeek(s32, s32, s32);
extern s32 FileRead(void *, s32, s32, s32);
extern s32 sprintf(char *, char *, ...);
extern void func_8001D218(char *, ...);
extern s32 RandomScaledGet(s32);
extern s32 func_800157B0(s16 *, void *, u8 *);
extern void func_80015870(u8 *, void *);
extern void func_80015930(u8 *, void *, s32);
extern s32 D_800A2F80[], D_800A39E0[], D_800A376C[];
extern s32 D_800BE72C[], D_800B1348[], D_800B134C[], D_800B1350[];
extern s32 D_800AE848[], D_800AE84C[];
extern char sTrackInitMessage[];
INCLUDE_RODATA("asm/nonmatchings/game", sTrackInitMessage);
extern char sTrackReadVerticesMessage[];
INCLUDE_RODATA("asm/nonmatchings/game", sTrackReadVerticesMessage);
extern char sTrackReadFacesMessage[];
INCLUDE_RODATA("asm/nonmatchings/game", sTrackReadFacesMessage);
extern char sTrackFaceErrorFormat[];
INCLUDE_RODATA("asm/nonmatchings/game", sTrackFaceErrorFormat);
extern char sTrackReadSuccessMessage[];
INCLUDE_RODATA("asm/nonmatchings/game", sTrackReadSuccessMessage);

void TrackReadData(s32 *trackData, s32 file) {
    register TrackResource *resource asm("s7");
    /* Only the first byte is accessed in the retail function. */
    char scratch[0x220];
    VECTOR maxBounds;
    VECTOR minBounds;
    VECTOR point;
    char errorBuffer[0x40];
    u8 *sectionHeader;
    u8 *objectData;
    s32 objectFaceCount;
    s32 faceCount;
    s32 nodeCount;
    u8 *copy16Data;
    u8 *positionData;
    u8 *nodeData;
    u8 *sectionData;
    u8 *errorText;
    s32 specialFaceColor;
    /* Reserve seven spill homes between the color and object offsets. */
    s32 spillPad0;
    s32 spillPad1;
    s32 spillPad2;
    s32 spillPad3;
    s32 spillPad4;
    s32 spillPad5;
    s32 spillPad6;

    s32 nextObjectOffset;
    s32 prevObjectOffset;
    s32 faceCodeSave;
    u8 *vertexOffset;
    u8 *faceOffset;
    u8 *objectOffset;
    register s32 copy16Offset;
    register s32 positionOffset;
    register u8 *outputVertices;
    register u8 *vertices asm("s4");
    register SVECTOR *outputVertex asm("a0");
    register s32 minimumZ;
    u8 *outputRecord;
    u8 *section;
    s32 vertexCount;
    s32 vertexIndex;
    s32 faceMode;
    register s32 lastCorner asm("v1");
    register s32 nextDataOffset;
    register s32 randomValue;
    register s32 shadeBase;
    s32 nodesOffset;
    s32 sectionsOffset;
    u8 *sectionHeaderData;
    register u8 *outputZ;
    FileVertex *inputVertex;
    register u8 *data asm("s2");
    u8 *fileData;
    s32 sectionCount;
    s32 fileSize;
    register u32 nodeScale asm("a0");
    register char *initText asm("a0");
    s32 positionZ;
    s32 value0;
    s32 value1;
    s32 value2;
    register s32 objectFlags;
    register u32 typeA asm("v0");
    register u32 typeC;
    register s16 *callFirst;
    register u8 *callHead;
    register u8 *callFaces;
    register s32 lastObjectOffset asm("v1");
    s32 scaledY;
    s32 scaledX;
    s32 workValue;
    s32 vertexSlot;
    s32 uvSlot;
    s32 faceCode;
    register s32 runtimeFaceOffset;
    s32 shade;
    s32 i;
    s32 nodeOffset;
    s32 rawX;
    s32 rawY;
    s32 rawZ;
    s32 scaledZ;
    register s32 positionByteOffset;
    u8 *inputIndex;
    u8 *inputUv;
    u8 *diskFace;
    register s32 count asm("s6");
    register s32 objectPolygonCount asm("a1");
    register s32 faceColor;
    register u8 *flagObject;
    u8 faceFlags;
    u8 byteValue;
    u8 modeFlags;
    u8 *allocatedVertices;
    u8 *allocatedFaces;
    u8 *allocatedNodes;
    u8 *allocatedObjects;
    u8 *node;
    u8 *objectFaceIndices;
    u8 *face;
    u8 *nodeDataStart;
    u8 *sectionObject;
    u8 *unusedCursor;
    u8 *inputCopy16;
    u8 *inputPosition;
    u8 *inputNode;
    register u8 *faceFields asm("s2");
    register u8 *diskObject asm("s5");
    u8 *outputIndex;
    u8 *outputUv;
    register u32 boundLimit;

    resource = (TrackResource *)trackData;
    fileSize = FileSeek(file, 0, 2);
    fileData = (u8 *)((0x1F4000 - fileSize) | RAM_CACHED_BASE);
    FileSeek(file, 0, 0);
    FileRead(fileData, fileSize, 1, file);
    vertexOffset = (u8 *)*(s32 *)(fileData + 8);
    faceOffset = (u8 *)*(s32 *)(fileData + 12);
    objectOffset = (u8 *)*(s32 *)(fileData + 16);
    copy16Offset = *(s32 *)(fileData + 20);
    positionOffset = *(s32 *)(fileData + 24);
    nodesOffset = *(s32 *)(fileData + 28);
    sectionsOffset = *(s32 *)(fileData + 32);
    vertexCount = *(s16 *)(fileData + 0);
    asm volatile(""
                 :
                 : "g"(vertexOffset), "g"(faceOffset), "g"(objectOffset),
                   "g"(copy16Offset), "g"(positionOffset), "g"(nodesOffset),
                   "g"(sectionsOffset), "g"(vertexCount)
                 : "memory");
    /* Inverse of 135 for the aligned 540-byte node records. */
    asm volatile("lui %0,0xE1A8\nori %0,%0,0xC537"
                 : "=r"(nodeScale)
                 : "g"(vertexCount)
                 : "memory");
    nodeDataStart = fileData + nodesOffset;
    sectionHeaderData = fileData + sectionsOffset;
    resource->vertexCount = (s32)vertexCount;
    nodeData = nodeDataStart;
    sectionHeader = sectionHeaderData;
    asm volatile("lh %0,%2"
                 : "=r"(faceCount), "=r"(nodeScale)
                 : "m"(*(s16 *)(fileData + 2)), "1"(nodeScale), "g"(nodeData),
                   "g"(sectionHeader), "m"(resource->vertexCount));
    nodeCount =
        (s32)((u32)(sectionHeaderData - nodeDataStart) * nodeScale) >> 2;
    initText = sTrackInitMessage;
    asm("" : "=r"(initText) : "0"(initText));
    data = fileData + (s32)vertexOffset;
    diskFace = fileData + (s32)faceOffset;
    resource->faceCount = (s32)faceCount;
    diskObject = fileData + (s32)objectOffset;
    resource->objectCount = (s32) * (s16 *)(fileData + 4);
    copy16Data = fileData + copy16Offset;
    positionData = fileData + positionOffset;
    func_8001D218(initText, vertexOffset, faceOffset, objectOffset);
    allocatedVertices = HeapAlloc(vertexCount * 8);
    D_800BE97C[0] = allocatedVertices;
    sectionData = sectionHeader + 4;
    if (allocatedVertices == NULL) {
        SystemShowFatalError(&D_8008CB94);
    }
    allocatedFaces = HeapAlloc(faceCount * 0x2C);
    D_800A3A40 = allocatedFaces;
    if (allocatedFaces == NULL) {
        SystemShowFatalError(&D_8008CBB4);
    }
    D_800BE984[0] = 0;
    D_800BE970[0] = (s32)vertexCount;
    allocatedNodes = HeapAlloc(nodeCount * 0x21C);
    D_800A39A4 = allocatedNodes;
    if (allocatedNodes == NULL) {
        SystemShowFatalError(&D_8008CBD0);
    }
    i = 0;
    allocatedObjects = HeapAlloc(resource->objectCount * 0x90);
    objectData = allocatedObjects;
    resource->objects = allocatedObjects;
    func_8001D218(sTrackReadVerticesMessage);
    boundLimit = 0x7FFF0000;
    outputVertices = resource->vertices;
    boundLimit |= 0xFFFF;
    D_800AE84C[0] = 0;
    D_800AE848[0] = 0;
    D_800AE844[0] = 0;
    minBounds.vz = boundLimit;
    minBounds.vy = boundLimit;
    minBounds.vx = boundLimit;
    maxBounds.vz = 0x80000001;
    maxBounds.vy = 0x80000001;
    maxBounds.vx = 0x80000001;
    if (vertexCount > 0) {
        inputVertex = (FileVertex *)data;
    readVertexBounds:
        value0 = inputVertex->x;
        scaledX = value0 >> 2;
        if (value0 < 0) {
            scaledX = (s32)(value0 + 3) >> 2;
        }
        point.vx = scaledX;
        value1 = inputVertex->y;
        scaledY = value1 >> 2;
        if (value1 < 0) {
            scaledY = (s32)(value1 + 3) >> 2;
        }
        point.vy = scaledY;
        rawZ = inputVertex->z;
        if (rawZ < 0) {
            rawZ += 3;
        }
        value2 = rawZ >> 2;
        point.vz = value2;
        if (scaledX < minBounds.vx) {
            minBounds.vx = scaledX;
        }
        if (scaledY < minBounds.vy) {
            minBounds.vy = scaledY;
        }
        if (value2 < minBounds.vz) {
            minBounds.vz = value2;
        }
        if (maxBounds.vx < scaledX) {
            maxBounds.vx = scaledX;
        }
        if (maxBounds.vy < scaledY) {
            maxBounds.vy = scaledY;
        }
        if (maxBounds.vz < value2) {
            maxBounds.vz = value2;
        }
        i += 1;
        inputVertex++;
        if (i < vertexCount)
            goto readVertexBounds;
    }
    value2 = minBounds.vx;
    value1 = maxBounds.vx;
    workValue = maxBounds.vy;
    D_800AE84C[0] = 0;
    D_800AE844[0] = (s32)((s32)(value2 + value1) / 2);
    D_800AE848[0] = (s32)(minBounds.vy + workValue) / 2;
    i = 0;
    if (vertexCount > 0) {
        outputVertex = (SVECTOR *)outputVertices;
        workValue = (s32)(data + 8);
        do {
            rawX = *(s32 *)data;
            if (rawX < 0) {
                rawX += 3;
            }
            outputVertex->vx = (s16)((rawX >> 2) - D_800AE844[0]);
            rawY = *(s32 *)((u8 *)workValue + (-4));
            if (rawY < 0) {
                rawY += 3;
            }
            outputVertex->vy = (s16)((rawY >> 2) - D_800AE844[1]);
            scaledZ = *(s32 *)((u8 *)workValue + (0));
            if (scaledZ < 0) {
                scaledZ += 3;
            }
            workValue += 0xC;
            data += 0xC;
            i += 1;
            outputVertex->vz = (s16)((scaledZ >> 2) - D_800AE844[2]);
            outputVertex++;
        } while (i < vertexCount);
    }
    i = 0;
    func_8001D218(sTrackReadFacesMessage);
    scratch[0] = 0;
    vertices = resource->vertices;
    if (faceCount > 0) {
        errorText = (u8 *)errorBuffer;
        faceCode = 0x40;
        runtimeFaceOffset = 0;
        faceFields = diskFace + 0x13;
        do {
            face = D_800A3A40 + runtimeFaceOffset;
            *(u8 **)((u8 *)face + (40)) = (void *)resource->faces;
            resource->faces = face;
            count = *(s8 *)diskFace;
            *(u8 *)((u8 *)face + (18)) = count;
            if ((u32)count >= 5U) {
                faceCodeSave = faceCode;
                sprintf((char *)errorText, sTrackFaceErrorFormat, i);
                GraphicsRenderFrame((s32)errorText);
            }
            *(s32 *)((u8 *)face + (4)) =
                (s32) * (s32 *)((u8 *)faceFields + (5));
            byteValue = *(u8 *)(faceFields - 18);
            *(u8 *)(face + 19) = 0;
            *(u8 *)(face + 2) = byteValue;
            *(u16 *)((u8 *)face + (22)) =
                (u16) * (s16 *)((u8 *)faceFields + (3));
            if (*(s8 *)((u8 *)faceFields + (-16)) != 0) {
                faceFlags = *(u8 *)((u8 *)face + (19));
                *(u8 *)((u8 *)face + (19)) = (u8)(faceFlags | 1);
                if (*(s8 *)((u8 *)faceFields + (-16)) == 1) {
                    *(u8 *)((u8 *)face + (19)) = (u8)(faceFlags | 3);
                }
            } else {
                *(u16 *)((u8 *)face + (22)) =
                    (u16) * (u16 *)((u8 *)faceFields + (-7));
                if ((s16) * (s16 *)((u8 *)faceFields + (3)) == faceCode) {
                    *(u8 *)((u8 *)face + (19)) =
                        (u8)(*(u8 *)((u8 *)face + (19)) | 4);
                }
            }
            *(s8 *)((u8 *)face + (1)) = 0;
            if (*(s8 *)((u8 *)faceFields + (-17)) != 0x7F) {
                *(u8 *)((u8 *)face + (19)) =
                    (u8)(*(u8 *)((u8 *)face + (19)) | 0x80);
                if ((u8) * (s8 *)((u8 *)faceFields + (-17)) == 0x81) {
                    *(s8 *)((u8 *)face + (1)) = (s8)faceCode;
                }
                if ((u8) * (s8 *)((u8 *)faceFields + (-17)) == 0x82) {
                    *(s8 *)((u8 *)face + (1)) = 0;
                } else {
                    *(s8 *)((u8 *)face + (1)) = (s8)faceCode;
                }
            } else {
                *(s8 *)((u8 *)face + (1)) = (s8)faceCode;
                faceMode = (s16) * (s16 *)((u8 *)faceFields + (3));
                switch (faceMode) {
                case 1:
                    modeFlags = *(u8 *)(face + 19) | 8;
                    break;
                case 2:
                    modeFlags = *(u8 *)(face + 19) | 0x28;
                    break;
                default:
                    goto faceFlagsDone;
                }
                *(u8 *)(face + 19) = modeFlags;
            }
        faceFlagsDone:
            vertexSlot = 0;
            if (count > 0) {
                inputIndex = diskFace;
                outputIndex = face;
                do {
                    vertexIndex = *(s16 *)((u8 *)inputIndex + (4));
                    inputIndex += 2;
                    vertexSlot += 1;
                    *(u8 **)((u8 *)outputIndex + (24)) =
                        (u8 *)(vertices + (vertexIndex * 8));
                    outputIndex += 4;
                } while (vertexSlot < count);
            }
            if (vertexSlot == 3) {
                *(u8 **)((u8 *)face + (36)) =
                    (s32) * (u8 **)((u8 *)face + (24));
            }
            uvSlot = 0;
            inputUv = diskFace;
            outputUv = face;
        readFaceUv:
            *(u8 *)((u8 *)outputUv + (8)) = (u8) * (u8 *)((u8 *)inputUv + (14));
            byteValue = *(u8 *)((u8 *)inputUv + (15));
            uvSlot += 1;
            inputUv += 2;
            *(u8 *)((u8 *)outputUv + (9)) = byteValue;
            outputUv += 4;
            if (uvSlot < 3) {
                goto readFaceUv;
            }
            if ((u8) * (u8 *)((u8 *)face + (18)) >= 4U) {
                *(u8 *)((u8 *)face + (16)) =
                    (u8) * (u8 *)((u8 *)faceFields + (1));
                *(u8 *)((u8 *)face + (17)) =
                    (u8) * (u8 *)((u8 *)faceFields + (2));
                *(u8 *)((u8 *)face + (20)) =
                    (u8) * (u8 *)((u8 *)faceFields + (-1));
                *(u8 *)((u8 *)face + (21)) =
                    (u8) * (u8 *)((u8 *)faceFields + (0));
            }
            faceFields += 0x1C;
            diskFace += 0x1C;
            i += 1;
            runtimeFaceOffset += 0x2C;
        } while (i < faceCount);
    }
    count = resource->objectCount;
    vertices = resource->vertices;
    shade = 0x80;
    i = 0;
    if (count > 0) {
        data = objectData;
        asm volatile(""
                     : "=g"(spillPad0), "=g"(spillPad1), "=g"(spillPad2),
                       "=g"(spillPad3), "=g"(spillPad4), "=g"(spillPad5),
                       "=g"(spillPad6));
        specialFaceColor = 0x4A4A4A;
        nextObjectOffset = 0x90;
        prevObjectOffset = -0x90;
        do {
            *(u8 **)((u8 *)data + (0)) = objectData + prevObjectOffset;
            *(u8 **)((u8 *)data + (4)) =
                (void *)(objectData + nextObjectOffset);
            objectFlags = *(u32 *)((u8 *)data + (16));
            typeA = *(u16 *)diskObject;
            *(u16 *)(data + 10) = typeA;
            typeC = *(u16 *)(diskObject + 2);
            objectFlags &= 0xFFFEFFFF;
            *(s16 *)((u8 *)data + (8)) = i;
            *(u32 *)((u8 *)data + (16)) = objectFlags;
            *(u16 *)(data + 12) = typeC;
            typeA = *(s16 *)(diskObject + 4);
            *(u32 *)((u8 *)data + (16)) =
                (objectFlags & 0xFF01FFFF) | ((typeA & 0x7F) << 17);
            typeA = *(u16 *)(diskObject + 6);
            objectFaceIndices = diskObject + 0x20;
            asm("" : : "r"(typeA), "r"(objectFaceIndices));
            *(u16 *)(data + 16) = typeA;
            *(FileVertex *)(data + 20) = *(FileVertex *)(diskObject + 8);
            asm volatile("" : : : "memory");
            callFaces = D_800A3A40;
            callFirst = (s16 *)objectFaceIndices;
            callHead = data + 32;
            *(u8 **)((u8 *)data + (48)) = 0;
            *(s32 *)((u8 *)data + (80)) = 0;
            *(u16 *)((u8 *)data + (14)) = 0;
            *(s32 *)((u8 *)data + (36)) = 0;
            *(u8 **)((u8 *)data + (32)) = NULL;
            *(s32 *)((u8 *)data + (44)) = 0;
            *(s32 *)((u8 *)data + (40)) = 0;
            *(s16 *)(data + 52) = -1;
            objectFaceCount = func_800157B0(callFirst, callHead, callFaces);
            face = *(u8 **)((u8 *)data + (32));
            objectPolygonCount = 0;
            if ((face != NULL) && !(*(u8 *)((u8 *)face + (19)) & 0x80)) {
                flagObject = data;
                faceColor = 0x808080;
                do {
                    if (*(s32 *)((u8 *)face + (4)) == specialFaceColor) {
                        *(u32 *)((u8 *)flagObject + (16)) |= 0x10000;
                    } else {
                        *(s32 *)((u8 *)face + (4)) = faceColor;
                    }
                    face = *(u8 **)((u8 *)face + (40));
                    objectPolygonCount += 1;
                } while ((face != NULL) &&
                         !(*(u8 *)((u8 *)face + (19)) & 0x80));
            }
            *(s8 *)((u8 *)data + (19)) = objectPolygonCount;
            func_80015870(data + 0x20, data + 0x28);
            randomValue = RandomScaledGet(3);
            shadeBase = shade - 1;
            shade = shadeBase + randomValue;
            if (shade >= 0x81) {
                shade = 0x80;
            } else if (shade < 0x50) {
                shade = 0x50;
            }
            func_80015930(data, resource, shade);
            nextDataOffset = *(s16 *)(diskObject + 26);
            *(u8 **)(data + 120) = vertices + nextDataOffset * 8;
            nextDataOffset = *(s16 *)(diskObject + 24);
            *(u8 **)(data + 124) = vertices + nextDataOffset * 8;
            nextDataOffset = *(s16 *)(diskObject + 20);
            *(u8 **)(data + 128) = vertices + nextDataOffset * 8;
            nextDataOffset = *(s16 *)(diskObject + 22);
            *(u8 **)(data + 132) = vertices + nextDataOffset * 8;
            nextObjectOffset += 0x90;
            prevObjectOffset += 0x90;
            nextDataOffset = *(s16 *)(diskObject + 28);
            *(u8 **)(data + 136) = vertices + nextDataOffset * 8;
            i += 1;
            lastCorner = *(s16 *)(diskObject + 30);
            nextDataOffset = objectFaceCount * 2 + 2;
            diskObject = objectFaceIndices + nextDataOffset;
            lastCorner = (s32)vertices + lastCorner * 8;
            *(u8 **)(data + 140) = (u8 *)lastCorner;
            data += 0x90;
        } while (i < count);
        asm volatile(""
                     :
                     : "g"(spillPad0), "g"(spillPad1), "g"(spillPad2),
                       "g"(spillPad3), "g"(spillPad4), "g"(spillPad5),
                       "g"(spillPad6));
    }
    {
        u8 *objects;
        i -= 1;
        value0 = resource->objectCount;
        lastObjectOffset = i * 8;
        inputCopy16 = copy16Data;
        lastObjectOffset += i;
        i = 0;
        resource->objectCount = value0 - 1;
        objects = objectData;
        /* Keep this address setup after the object count update. */
        asm volatile("lui %1,%%hi(D_800BE72C)\naddiu %1,%1,%%lo(D_800BE72C)"
                     : "=r"(lastObjectOffset), "=&r"(outputRecord)
                     : "0"(lastObjectOffset), "r"(objects),
                       "m"(resource->objectCount)
                     : "memory");
        lastObjectOffset *= 16;
        *(u8 **)objects = objects + (lastObjectOffset - 0x90);
        *(u8 **)(lastObjectOffset + (s32)objects - 140) = objects;
    }
    do {
        *(TrackCopy16 *)outputRecord = *(TrackCopy16 *)inputCopy16;
        outputRecord += 0x10;
        i += 1;
        inputCopy16 += 0x10;
    } while (i < 0x14);
    i = 0;
    minimumZ = 0xFA0;
    outputZ = &D_800B1350;
    inputPosition = positionData;
    positionByteOffset = 0;
copyStart:
    *(s32 *)((u8 *)D_800B1348 + positionByteOffset) =
        *(s32 *)((u8 *)inputPosition + (0));
    *(s32 *)((u8 *)D_800B134C + positionByteOffset) =
        *(s32 *)((u8 *)inputPosition + (4));
    positionZ = *(s32 *)((u8 *)inputPosition + (8));
    *(s32 *)outputZ = positionZ;
    if (positionZ < 0xFA0) {
        *(s32 *)outputZ = minimumZ;
    }
    outputZ += 0x58;
    inputPosition += 0xC;
    i += 1;
    positionByteOffset += 0x58;
    if (i < 0x14)
        goto copyStart;
    i = 0;
    if (nodeCount > 0) {
        nodeOffset = 0;
        inputNode = nodeData;
        do {
            *(TrackNode *)((u8 *)(nodeOffset + (s32)D_800A39A4)) =
                *(TrackNode *)inputNode;
            node = (u8 *)(nodeOffset + (s32)D_800A39A4);
            *(u8 **)((u8 *)node + (0)) =
                (s32) * (u8 **)((*(s16 *)(node + 8) * 0x90) + objectData + 48);
            *(u8 **)((*(s16 *)(node + 8) * 0x90) + objectData + 48) = node;
            inputNode += 0x21C;
            i += 1;
            nodeOffset += 0x21C;
        } while (i < nodeCount);
    }
    sectionCount = *(s32 *)sectionHeader;
    D_800A2F80[0] = sectionCount;
    if (sectionCount == 0) {
        D_800A39E0[0] = 0;
        D_800A376C[0] = 0;
    } else {
        register s32 firstIndex;
        s32 lastIndex;
        firstIndex = *(s16 *)sectionData;
        lastIndex = sectionCount * 0x1C;
        lastIndex = *(s16 *)(lastIndex + (s32)sectionData - 28);
        D_800A39E0[0] = firstIndex;
        D_800A376C[0] = lastIndex;
    }
    i = 0;
    if (D_800A2F80[0] > 0) {
        section = sectionData;
    readSection:
        sectionObject = (u8 *)(*(s16 *)section * 0x90 + (s32)objectData);
        outputRecord = *(s32 *)((u8 *)section + (12));
        *(TrackCopy28 *)(sectionObject + 52) = *(TrackCopy28 *)section;
        i += 1;
        section += 0x1C;
        if (i < D_800A2F80[0])
            goto readSection;
    }
    func_8001D218(sTrackReadSuccessMessage);
}

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

void func_80015930(u8 *arg0, void *arg1, s32 arg2) {
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

void TrackLoadFromFile(s32 arg0) {
    extern s32 FileOpen(s32, void *);
    extern void TrackReadData(s32 *, s32);
    extern void FileClose(s32);
    extern char D_8008CC7C[] __attribute__((aligned(4)));
    extern u8 D_800A2D48[];
    extern u8 D_800A2D4C[];
    s32 value0;
    value0 = FileOpen(arg0, D_800A2D48);
    if (value0 == 0)
        SystemShowFatalError(D_8008CC7C);
    TrackReadData(D_800BE970, value0);
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

void func_80015EAC(u8 *car) {
    typedef struct {
        s32 x;
        s32 y;
        s32 z;
    } Vector3;
    extern void func_800319D4(u8 *, s32);
    extern void func_8001EEC4(u8 *);
    extern void MatrixCombineState(void);
    extern s32 *D_800A38AC;
    extern s32 D_800A3798Absolute[], D_800A37ACAbsolute[], D_800A3784Absolute[];
    extern s32 D_800A379CAbsolute[], D_800A37B4Absolute[], D_800A3790Absolute[];
    extern s32 D_800A37A4Absolute[], D_800A37C4Absolute[], D_800A3794Absolute[];
    extern MATRIX D_800A3A98, D_800A3AB8;
    extern s16 D_800A3A98Half[] asm("D_800A3A98");
    extern s16 D_800A3A9A[], D_800A3A9C[], D_800A3A9E[], D_800A3AA0[];
    extern s16 D_800A3AA2[], D_800A3AA4[], D_800A3AA6[], D_800A3AA8[];
    extern s16 D_800A3AB8Half[] asm("D_800A3AB8");
    extern s16 D_800A3ABA[], D_800A3ABC[], D_800A3ABE[], D_800A3AC0[];
    extern s16 D_800A3AC2[], D_800A3AC4[], D_800A3AC6[], D_800A3AC8[];
    SVECTOR angles;
    VECTOR position;
    VECTOR partPosition; /* Preserve the original stack frame. */
    VECTOR unused;       /* Preserve the original stack frame. */
    VECTOR saved[3];
    s32 flag;
    s32 *camera;

    angles.vx = *(s32 *)(car + 0) - D_800A38AC[0];
    angles.vy = *(s32 *)(car + 4) - D_800A38AC[1];
    angles.vz = *(s32 *)(car + 8) - D_800A38AC[2] - *(u16 *)(car + 0xFE);
    *(Vector3 *)&saved[0] = *(Vector3 *)(car + 0x3C);
    *(Vector3 *)&saved[1] = *(Vector3 *)(car + 0x48);
    *(Vector3 *)&saved[2] = *(Vector3 *)(car + 0x54);
    func_800319D4(car, 1);
    func_8001EEC4(car);
    MatrixCombineState();
    D_800A3A98Half[0] = -D_800A3798Absolute[0] / 16;
    D_800A3A9E[0] = -D_800A37ACAbsolute[0] / 16;
    D_800A3AA4[0] = D_800A3784Absolute[0] / 16;
    D_800A3A9A[0] = -D_800A379CAbsolute[0] / 16;
    D_800A3AA0[0] = -D_800A37B4Absolute[0] / 16;
    D_800A3AA6[0] = D_800A3790Absolute[0] / 16;
    D_800A3A9C[0] = -D_800A37A4Absolute[0] / 16;
    D_800A3AA2[0] = -D_800A37C4Absolute[0] / 16;
    D_800A3AA8[0] = D_800A3794Absolute[0] / 16;
    camera = D_800A38AC;
    D_800A3AB8Half[0] = -camera[0x10] / 16;
    D_800A3ABE[0] = -camera[0x11] / 16;
    D_800A3AC4[0] = camera[0xF] / 16;
    D_800A3ABA[0] = -camera[0x13] / 16;
    D_800A3AC0[0] = -camera[0x14] / 16;
    D_800A3AC6[0] = camera[0x12] / 16;
    D_800A3ABC[0] = -camera[0x16] / 16;
    D_800A3AC2[0] = -camera[0x17] / 16;
    D_800A3AC8[0] = camera[0x15] / 16;
    SetTransMatrix(&D_800A3AB8);
    SetRotMatrix(&D_800A3AB8);
    RotTrans(&angles, &position, &flag);
    TransMatrix(&D_800A3A98, &position);
    SetTransMatrix(&D_800A3A98);
    SetRotMatrix(&D_800A3A98);
    *(Vector3 *)(car + 0x3C) = *(Vector3 *)&saved[0];
    *(Vector3 *)(car + 0x48) = *(Vector3 *)&saved[1];
    *(Vector3 *)(car + 0x54) = *(Vector3 *)&saved[2];
}

extern long RotTransPers3_nom();

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

void func_80016724(s32 value, s32 *next, s32 size) {
    s32 *current;
    current = D_800A2D64;
    D_800A2D64 = next;
    current[0x34 / 4] = value;
    D_800A2D5C += size;
}

extern s32 gOrderingTableBankLui asm("gOrderingTableBankAbsolute");
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

s32 func_800167BC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 bank;
    u32 entries;
    s32 oldEntry;
    s32 value;
    s32 offset;
    s32 hw;
    u32 ptr;
    s32 size;
    register s32 extra asm("$3");
    s32 bank2;
    s8 speed;
    s8 q;
    s32 ret;

    bank = gOrderingTableBankLui;
    value = *(s8 *)((s32)arg0 + bank + 0x41C);
    if (value == *(s8 *)((s32)arg0 + 0x374)) {
        if (*(s32 *)((bank << 2) + (s32)arg0 + 0x420) != 0) {
            return 0;
        }
    } else {
        entries = (bank << 2) + (s32)arg0;
        oldEntry = *(s32 *)(entries + 0x420);
        if (oldEntry != 0) {
            offset = value * 0x44 + *(s32 *)((s32)arg0 + 0x370);
            ptr = (u32)D_800A2D64;
            hw = *(s16 *)(offset + 0x2A);
            extra = *(s32 *)(entries + 0x430);
            size = D_800A2D5C;
            *(s32 *)(ptr + 0x34) = oldEntry;
            *(s32 *)(entries + 0x420) = 0;
            D_800A2D64 = (s32 *)extra;
            D_800A2D5C = size + hw;
        }
    }
    if (*(s8 *)((s32)arg0 + 0x374) == 4) {
        *(s8 *)((s32)arg0 + ((s32 *)D_800A2CF8)[-1] + 0x41C) = -1;
        return 1;
    }
    speed = *(u8 *)((s32)arg0 + 0x200);
    q = speed / 5;
    ret = (s32)func_800163E8(arg0, q);
    bank2 = gOrderingTableBankLui;
    *(s32 *)((bank2 << 2) + (s32)arg0 + 0x420) = ret;
    if (ret == 0) {
        return 1;
    }
    *(s8 *)((s32)arg0 + bank2 + 0x41C) = *(u8 *)((s32)arg0 + 0x374);
    return 0;
}

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
