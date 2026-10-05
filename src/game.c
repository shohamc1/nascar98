#include "common.h"
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

#ifdef NON_MATCHING
/*
 * Needs lui addressing for D_800A2EAC and D_800A2EB0, but both are
 * scalar-declared (gp addressing) for func_8002F514/func_8002F86C/
 * func_8002DDA0 in this translation unit. One symbol name can only have
 * one addressing mode per TU without a linker alias.
 */
extern u8 D_800A2D0D;
extern u8 D_800A2D0E;
extern u8 D_800A2D0F;
extern u8 D_800A39E4[];
extern s32 D_800A2EB8[];
extern s32 D_800A2EC8[];

extern void DecDCTReset(s32);
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
    D_800A2EC8[-6] = 0;
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
        if (((D_800A39E4[0] + 3) & 0xFF) >= 2) {
            func_800531B8();
            HeapResetInitFlag();
        }
        func_800122D8();
        D_800A2EC8[-7] = 0;
        D_800A2EC8[0] = 0;
        if (D_800A2D0E != 0 || D_800A2D0F != 0) {
            func_80066B08();
            D_800A39E4[0] = mode;
            if (D_800A2D0F == 0) {
                exitCode = -3;
            } else {
                func_800587A0();
                exitCode = -2;
            }
            D_800A2EC8[-6] = exitCode;
            D_800A2D0E = 0;
            D_800A2D0F = 0;
        } else {
            func_800587A0();
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80012108);
#endif

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

void func_80012AF8(void) {
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

void func_80012B78(s32 arg0) {
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
extern s32 D_800B9D58[];
extern s32 D_800B9D5C[];
extern s32 D_800B9D60[];

extern void func_8001D220(s32, s32, s32, s32);

void func_80012C30(void) {
    func_8001D220(D_800A370C - D_800A3708, 0xF0, 0x14, 0);
    func_8001D220(D_800A2D00, 0xF0, 0x14, 3);
    func_8001D220(D_800B9D54[0], 0xF0, 0x23, 0);
    func_8001D220(D_800B9D5C[-1] + D_800B9D54[0], 0xF0, 0x23, 2);
    func_8001D220(D_800B9D60[0] + D_800B9D58[0] + D_800B9D54[0], 0xF0, 0x23, 3);
    func_8001D220(D_800B9D5C[0], 0xF0, 0x23, 1);
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

void func_800130D4(void) {
    typedef struct {
        u8 b[8];
    } XBytes;
    extern u8 D_800A2D1CNM[] asm("D_800A2D1C.NON_MATCHING");
    extern void func_80013224();
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
        func_80013224((void *)D_800B9F44[i]);
    }
}

void func_8001317C(s32 arg0) {
    extern void func_8003CA18(s32, s32);
    extern void func_80013224(void *);

    func_8003CA18(STACK_BLOCK_801E0000, arg0);
    func_80013224((void *)STACK_BLOCK_801E0000);
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

void func_80013224(void *arg0) {
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

INCLUDE_ASM("asm/nonmatchings/game", func_800132F8);
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
INCLUDE_ASM("asm/nonmatchings/game", func_80014398);
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
    register u8 *tbl asm("v1");
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
        mode = D_800A2EB0w15[0] != -1;
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
    asm volatile("lui %0, 0x8001\n\tori %0, %0, 0x1E04" : "=r"(tbl));
    do {
        tbl[0xF] = 0;
        tbl[0x10] = c20;
        tbl[0x11] = c20;
        tbl[0x12] = c20;
        tbl[0x0] = 0;
        *(s16 *)(tbl + 0x14) = c2BC;
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
    } while (i < 4);
    if (mode == 0)
        goto case0;
    if (mode == 1)
        goto case1;
    goto dispatchDone;
case0:
    D_800A2EA4w15[0] = 0;
    goto dispatchShared;
case1:
    D_800A2EA4w15[0] = 2;
dispatchShared:
    D_8008CA28[0] = 0;
dispatchDone:
    func_800132F8(0);
    v = D_800A2EB0w15[0];
    if (v > 0) {
        D_800A2E90w15[0] = 0;
    }
    if (v == -1) {
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
            asm("");
            q = (u8 *)(i + (s32)be70c);
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
    register s32 one asm("$7");

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

#ifdef NON_MATCHING
/* Wall: the D_800A2F10 load lands in v0 and the /40 shift in v1; retail
 * has them swapped (load v1, shift v0). Every source shape tried keeps
 * our allocation. */
extern u32 gPrimitiveCursor[];
extern u32 D_800A3570;
extern s32 D_800A38F4;
extern s32 D_800A2F10[];

s32 func_80014AC8(s32 arg0) {
    s32 usedPrims;

    usedPrims =
        ((gPrimitiveCursor[0] & 0xFFFFFFF) - (D_800A3570 & 0xFFFFFFF)) / 40;
    D_800A38F4 = D_800A2F10[0] - usedPrims;
    return arg0 < D_800A38F4;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80014AC8);
#endif

extern void *HeapAlloc(u32);
extern void SystemShowFatalError(char *);
extern void *D_800A3A40;
extern void *D_800A39A4;
extern s32 D_800BE970[];
extern void *D_800BE97C[];
extern s32 D_800BE984[];
extern char D_8008CB94[];
extern char D_8008CBB4[];
extern char D_8008CBD0[];
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

#ifdef NON_MATCHING
/* Wall: scheduling of the -1 sentinel load, the value preload, and the
 * ListPushFront argument setup differs (base add not in the jal delay). */
s32 func_800157B0(s16 *arg0, void *arg1, u8 *arg2) {
    s32 count;
    s16 *cursor;
    s32 value;

    count = 0;
    if (arg0[0] != -1) {
        cursor = arg0;
        value = cursor[0];
        do {
            ListPushFront(arg2 + value * 0x2C, (u8 **)arg1,
                          (u8 **)((u8 *)arg1 + 4));
            cursor++;
            value = cursor[0];
            count++;
        } while (value != -1);
    }
    if (count != 0) {
        func_8001C668(arg1, (void *)((u8 *)arg1 + 4));
    }
    if ((count & 1) == 0) {
        count += 1;
    }
    return count;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800157B0);
#endif

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
    extern s32 func_8003C584(s32, void *);
    extern void func_80014BEC(s32 *, s32);
    extern void func_8003C63C(s32);
    extern void SystemShowFatalError(char *);
    extern char D_8008CC7C[];
    extern u8 D_800A2D48[];
    extern s32 D_800BE970[];
    extern u8 D_800A2D4C[];
    s32 value0;
    value0 = func_8003C584(arg0, D_800A2D48);
    if (value0 == 0)
        SystemShowFatalError(D_8008CC7C);
    func_80014BEC(D_800BE970, value0);
    D_800A2D4C[0] = 1;
    func_8003C63C(value0);
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
    register s32 b asm("v1");
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
    b = D_800A3794Absolute[0];
    matrix->m[1][2] = (s16)(a >> 4);

    if (b < 0) {
        b += 15;
    }
    a = b >> 4;
    matrix->m[2][2] = (s16)a;
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
    register u8 *vertex asm("s3");
    s32 singles;

    width = (arg0[1] - arg0[0]) + 1;
    singles = width % 3;
    vertex = arg1;
    while (singles > 0) {
        RotTransPers_nom(vertex);
        func_80033788(vertex);
        vertex += 0x14;
        singles--;
        width--;
    }
    singles = width;
    while (singles > 0) {
        RotTransPers3_nom(vertex, vertex + 0x14, vertex + 0x28);
        func_8003379C(vertex, vertex + 0x14, vertex + 0x28);
        vertex += 0x3C;
        singles -= 3;
    }
}

extern s32 D_800A2D60;
extern s32 D_800A2D5C;
extern s32 *D_800A2D64;

extern void *HeapAlloc(u32);

#ifdef NON_MATCHING
/* Wall: gcc folds the post-loop count * 0x38 to a constant, reverses the loop
 * to a down-count, and loses the base register; retail keeps count live
 * (slti up-count), reloads D_800A2D60, and computes count * 0x38 at runtime.
 * A do { } while (count < 0x897) body still gets reversed and folded. */
void func_8001636C(void) {
    s32 count;
    s32 offset;
    u8 *base;
    u8 *entry;

    D_800A2D60 = (s32)HeapAlloc(0x1E140);
    if (D_800A2D60 == 0) {
        return;
    }
    base = (u8 *)D_800A2D60;
    entry = base;
    offset = 0x38;
    count = 0;
    do {
        *(s32 *)(entry + 0x34) = (s32)(base + offset);
        offset += 0x38;
        count += 1;
        entry += 0x38;
    } while (count < 0x897);
    D_800A2D5C = 0x898;
    entry = (u8 *)D_800A2D60 + count * 0x38;
    *(s32 *)(entry + 0x34) = 0;
    D_800A2D64 = (s32 *)entry;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8001636C);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_800163E8);

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

    bank = gOrderingTableBankAbsolute[0];
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
    *(s8 *)(arg0 + ((s32 *)D_800A2CF8)[-1] + 0x41C) = -1;
}

INCLUDE_ASM("asm/nonmatchings/game", func_800167BC);

INCLUDE_ASM("asm/nonmatchings/game", func_800168F8);

INCLUDE_ASM("asm/nonmatchings/game", func_80016ACC);

INCLUDE_ASM("asm/nonmatchings/game", func_80016CD8);

INCLUDE_ASM("asm/nonmatchings/game", func_8001775C);

INCLUDE_ASM("asm/nonmatchings/game", func_800179AC);

/* Fatal error display. */

void SystemShowFatalError(char *message) {
    GraphicsInit();
    FntPrint(message);
    FntFlush(-1);
    for (;;) {
    }
}

/* Math and random numbers. */

u32 MathSqrt(u32 value) {
    u32 result;
    u32 bit;
    u32 rootBitSum;

    result = 0;
    bit = 0x40000000;
    while (bit != 0) {
        rootBitSum = result + bit;
        result >>= 1;
        if (value >= rootBitSum) {
            value -= rootBitSum;
            result += bit;
        }
        bit >>= 2;
    }
    if (result < value) {
        return result + 1;
    }
    return result;
}

extern s32 gRandomCount;
extern s32 gRandomCountMark;

void RandomCountMark(void) {
    gRandomCountMark = gRandomCount;
}

extern s32 gRandomSeed;

s32 RandomSeedGet(void) {
    return gRandomSeed;
}

extern s32 gRandomSeed, gRandomCount;
extern s32 gRandomCountMark;
void RandomSeedSet(s32 seed) {
    gRandomSeed = seed;
    gRandomCount = 0;
    gRandomCountMark = 0;
}

extern s32 gRandomSeed;
extern s32 gRandomCount;

s32 RandomScaledGet(s32 scale) {
    s32 seed;

    gRandomCount++;
    if (gRandomCount >= 1000) {
        gRandomCount = 0;
    }
    seed = (gRandomSeed * 25173 + 13849) & 0xFFFF;
    /* Keep the store and return in one scheduling block. */
    do {
        gRandomSeed = seed;
        return (u32)(seed * scale) >> 16;
    } while (0);
}

/* Primitives and text. */

#ifdef NON_MATCHING
/* Wall (w7a, same as func_80034B90): retail loads gPrimitiveCursor[0]
 * into v0 and then copies it home twice (move t0,v0; move a3,t0); gcc
 * binds the load directly into entry's home register and drops one
 * move (4 bytes short). Tried here IN ADDITION to the sibling's list:
 * a two-local split (cursorVal -> entry) — coalesced the same way.
 * Everything else is exact: 0x10 struct-copy do-while, asm("")-split
 * 8-byte tail, neighbor-symbol store D_800A36D0Absolute[-67] (relocs
 * fold to 0x35c4), AddPrim(D_800A39C8[0], entry). */
typedef struct {
    s32 words[4];
} Primitive16;

extern u32 gPrimitiveCursor[];
extern s32 D_800A39C8[];
extern s32 D_800A36D0Absolute[];
void func_80017D80(u8 *arg0) {
    s32 cursorVal;
    u8 *entry;
    u8 *dst;
    u8 *end;
    s32 tailA;
    s32 tailB;

    cursorVal = gPrimitiveCursor[0];
    entry = (u8 *)cursorVal;
    end = arg0 + 0x20;
    dst = entry;
    ((s32 *)D_800A36D0Absolute)[-67] = cursorVal + 0x28;
    do {
        *(Primitive16 *)dst = *(Primitive16 *)arg0;
        arg0 += 0x10;
        dst += 0x10;
    } while (arg0 != end);
    tailA = *(s32 *)arg0;
    tailB = *(s32 *)(arg0 + 4);
    asm("");
    *(s32 *)dst = tailA;
    *(s32 *)(dst + 4) = tailB;
    AddPrim((u8 *)D_800A39C8[0], entry);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80017D80);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80017E08);

INCLUDE_ASM("asm/nonmatchings/game", func_800180C0);

extern s16 gFontColorRed, gFontColorGreen, gFontColorBlue;
void FontSetColor(s16 red, s16 green, s16 blue) {
    gFontColorRed = red;
    gFontColorGreen = green;
    gFontColorBlue = blue;
}

extern void func_800180C0(s8, s32, s32, s32);
extern s16 D_800A2D88[];

void func_8001832C(s8 *text, s32 x, s32 y, s32 scale) {
    s16 *width;
    s16 *base;
    s8 *p;

    if (*text != 0) {
        base = D_800A2D88;
        width = base + scale;
        p = text;
        do {
            func_800180C0(*p, x, y, scale);
            x += *width;
            p++;
        } while (*p != 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_800183C0);

INCLUDE_ASM("asm/nonmatchings/game", func_80018588);

INCLUDE_ASM("asm/nonmatchings/game", func_80018768);

extern void func_800183C0(s32, s32, s32, s32);
void func_80018848(void *arg0, s32 arg1, s32 arg2) {
    s32 value;
    func_800183C0(*(s32 *)((u8 *)arg0 + 0x258), arg1, arg2, 0);
    value = *(s32 *)((u8 *)arg0 + 0x25C);
    if (value != 0x7FFFFFFF) {
        func_800183C0(value, arg1, arg2 + 0x10, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_800188B0);

extern void func_800180C0(s8, s32, s32, s32);
extern s16 D_800A2D88[];
void FontDrawPaddedNumber(s32 value, s32 x, s32 y, s32 scale) {
    s8 text[24];
    s32 indent;
    s32 i;
    s32 advance;
    value = (s16)value;
    text[0] = 0;
    indent = 0;
    if (value < 1000) {
        indent = 1;
        text[0] = 32;
        text[1] = 0;
    }
    if (value < 100) {
        text[indent] = 32;
        indent += 1;
        text[indent] = 0;
    }
    if (value < 10) {
        text[indent] = 32;
        indent += 1;
        text[indent] = 0;
    }
    func_80012EA8(value, text + indent);
    if (text[0] != 0) {
        i = 0;
        do {
            func_800180C0(text[i], x, y, scale);
            x += D_800A2D88[scale];
            i++;
        } while (text[i] != 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80018B18);

INCLUDE_ASM("asm/nonmatchings/game", func_80018BD4);

INCLUDE_ASM("asm/nonmatchings/game", func_80018C88);

INCLUDE_ASM("asm/nonmatchings/game", func_800197D4);

extern s32 MathMultiplyFixed16(s32, s32);

void func_80019A00(s16 arg0, u8 *arg1, s32 arg2) {

    s32 num;
    s32 den;
    s32 rem;
    s32 product1;
    s32 product2;
    s32 product3;
    s32 result;
    s32 x;
    s32 y;
    s16 *ptrB;
    s16 *ptrA;
    s32 i;
    register s32 radiusB asm("s5");
    register u8 *poly asm("s6");
    s32 radiusA;
    u16 corners[8];
    u16 *corner;
    s32 off;
    extern s16 D_80091072[];
    extern u8 D_800A3A2CAbsolute[];
    extern u8 D_800A3A34Absolute[];

    poly = arg1;
    num = 0x230;
    den = 0x32C8;
    rem = num % den;
    rem = (rem << 15) / den;
    result = MathMultiplyFixed16(rem << 1, (s32)arg0 << 16);
    radiusA = (*(s32 **)D_800A3A2CAbsolute)[((result >> 16) + 0x1D6) & 0x3FF];
    radiusB = (*(s32 **)D_800A3A34Absolute)[((result >> 16) + 0x1D6) & 0x3FF];
    i = 0;
    ptrB = D_80091072;
    ptrA = ptrB - 1;
    for (; i < 4; i++) {
        product1 = MathMultiplyFixed16(radiusA, (s32)*ptrA << 16);
        product2 = MathMultiplyFixed16(radiusB, (s32)*ptrB << 16);
        x = (product1 - product2) >> 16;
        product3 = MathMultiplyFixed16(radiusB, (s32)*ptrA << 16);
        y = (product3 + MathMultiplyFixed16(radiusA, (s32)*ptrB << 16)) >> 16;
        off = i * 4;
        corner = (u16 *)((s32)corners + off);
        *corner = x + 0x2C;
        corner[1] = y + 0xAE;
        if (arg2 != 0) {
            corner[1] = y + 0x4A;
        }
        ptrB += 2;
        ptrA += 2;
    }
    ((u16 *)poly)[4] = corners[0];
    ((u16 *)poly)[5] = corners[1];
    ((u16 *)poly)[8] = corners[2];
    ((u16 *)poly)[9] = corners[3];
    ((u16 *)poly)[12] = corners[4];
    ((u16 *)poly)[13] = corners[5];
    ((u16 *)poly)[16] = corners[6];
    ((u16 *)poly)[17] = corners[7];
}

INCLUDE_ASM("asm/nonmatchings/game", func_80019C10);

INCLUDE_ASM("asm/nonmatchings/game", func_8001A4D4);

INCLUDE_ASM("asm/nonmatchings/game", func_8001A778);

INCLUDE_ASM("asm/nonmatchings/game", func_8001AEDC);

INCLUDE_ASM("asm/nonmatchings/game", func_8001B3F0);

INCLUDE_ASM("asm/nonmatchings/game", func_8001B82C);

INCLUDE_ASM("asm/nonmatchings/game", func_8001BA94);

INCLUDE_ASM("asm/nonmatchings/game", func_8001BDBC);

extern s32 D_800A2EC8nm[] asm("D_800A2EC8.NON_MATCHING");
extern s32 gOTBnm[] asm("gOrderingTableBank.NON_MATCHING");
extern u8 D_800A2EDAnm[] asm("D_800A2EDA.NON_MATCHING");
extern s32 D_800A2EC0nm[] asm("D_800A2EC0.NON_MATCHING");
extern u8 *D_8009AE40nm[] asm("D_8009AE40.NON_MATCHING");
extern s32 D_800A359Cnm[] asm("D_800A359C.NON_MATCHING");
extern s32 D_800A3848small asm("D_800A3848.NON_MATCHING");
extern u8 D_800A2D0Cnm[] asm("D_800A2D0C.NON_MATCHING");
extern u8 *D_800A2ECCnm[] asm("D_800A2ECC.NON_MATCHING");
extern s8 D_800A2ED0nm[] asm("D_800A2ED0.NON_MATCHING");
extern s32 D_800A2EA4nm[] asm("D_800A2EA4.NON_MATCHING");
extern u8 *D_800A3554small asm("D_800A3554.NON_MATCHING");
extern s32 D_800A39C8nm[] asm("D_800A39C8.NON_MATCHING");
extern s32 D_800A397CAbsolute[];
extern s32 D_800A2E24Absolute[];
extern s32 D_800A3A3CAbsolute[];
extern s32 D_800A2EB0Absolute[];
extern s32 D_800A2EACAbsolute[];
extern s32 D_800A3A2CAbsolute[];
extern s32 D_800A3A34Absolute[];
extern s32 D_800A2EC0Absolute[];

void func_8001C34C(void) {
    s32 mode;
    s32 value;
    s32 prim;
    volatile s32 pad[6];

    if (D_800A2EDAnm[0] != 0) {
        if (D_800A2EC0nm[0] % 30 < 0x10) {
            return;
        }
        GraphicsSetColor(0xFF, 0x80, 0x40);
        func_80050028(D_8009AE40nm[0], 0x76, 0x1E, 0);
        func_80044A1C(0x6E, 0x1A, 0x60, 0x12, 0, 0, 0, 1);
        return;
    }
    value = D_800A359Cnm[0];
    if (value != 0) {
        func_8001BDBC(value >= 0x21C);
        if (D_800A3848small < 0xA1) {
            return;
        }
        D_800A2D0Cnm[0] = 1;
        return;
    }
    if (D_800A2EC8nm[0] != 0) {
        if (D_800A397CAbsolute[0] == 2) {
            func_8001B3F0();
        } else {
            func_8001A778((void *)0x80010000, D_800A2ECCnm[0], D_800A2ED0nm[0]);
        }
    } else {
        func_8005098C();
    }
    mode = 2;
    if (D_800A2EA4nm[0] == mode) {
        func_8001AEDC(D_800A3554small, -0xA);
        func_80048EFC(D_800A3554small, -0x6E);
        prim = *(s32 *)(D_800A3554small + 0x3E0);
        D_800A2EB0Absolute[-111] = D_800A2E24Absolute[-76] + 1;
        D_800A3A3CAbsolute[-29] = D_800A397CAbsolute[19] + 0x1004;
        func_8001AEDC(prim, -0x14);
        func_80048EFC(*(s32 *)(D_800A3554small + 0x3E0), -0x7D);
        D_800A2EC0Absolute[-115] = D_800A2EACAbsolute[-110] - 1;
        D_800A3A34Absolute[-27] = D_800A3A2CAbsolute[-25] - 0x1004;
        return;
    }
    func_8001AEDC(D_800A3554small, 0);
    func_80048EFC(D_800A3554small, 0);
    if (*(s8 *)(D_800A3554small + 0x209) == mode) {
        func_8001BA94(0);
    }
}

/* Lists and callbacks. */

void ListInsertBefore(u8 **head, u8 *node, u8 *before) {
    u8 *current;
    u8 *previous;
    if (before == 0) {
        *(u8 **)(node + 0x28) = *head;
        *head = node;
        return;
    }
    current = *head;
    previous = current;
    while (current != 0) {
        if (current == before) {
            if (current == previous) {
                *(u8 **)(node + 0x28) = *head;
                *head = node;
            } else {
                *(u8 **)(node + 0x28) = current;
                *(u8 **)(previous + 0x28) = node;
            }
            return;
        }
        if (current != *head)
            previous = *(u8 **)(previous + 0x28);
        current = *(u8 **)(current + 0x28);
    }
}

void ListRemoveNode(u8 **head, u8 *target) {
    u8 *current;
    u8 *previous;
    current = *head;
    previous = current;
    while (current != 0) {
        if (current == target) {
            if (current == previous) {
                *head = *(u8 **)(current + 0x28);
            } else {
                *(u8 **)(previous + 0x28) = *(u8 **)(current + 0x28);
            }
            return;
        }
        if (current != *head)
            previous = *(u8 **)(previous + 0x28);
        current = *(u8 **)(current + 0x28);
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_8001C668);

void ListPushFront(u8 *node, u8 **head, u8 **tail) {
    u8 *oldHead;
    oldHead = *head;
    if (oldHead == 0) {
        *tail = node;
        *head = node;
        *(u8 **)(node + 0x28) = 0;
    } else {
        *(u8 **)(node + 0x28) = oldHead;
        *head = node;
    }
}

typedef struct ListNode28 ListNode28;
struct ListNode28 {
    u8 unk0[0x28];
    ListNode28 *next;
};
void ListRemoveNodeWithTail(ListNode28 *node, ListNode28 **head,
                            ListNode28 **tail) {
    ListNode28 *previous;
    ListNode28 *current;
    current = *head;
    previous = current;
    if (current != 0) {
    nextNode:
        if (current == node) {
            if (current == previous) {
                *head = current->next;
                if (current == *tail) {
                    *tail = 0;
                }
            } else {
                previous->next = current->next;
                if (current == *tail) {
                    *tail = previous;
                }
            }
        } else {
            if (current != *head) {
                previous = previous->next;
            }
            current = current->next;
            if (current != 0) {
                goto nextNode;
            }
        }
    }
}

typedef struct DoublyLinkedNode {
    struct DoublyLinkedNode *next;
    struct DoublyLinkedNode *previous;
} DoublyLinkedNode;
void ListPushFrontDoublyLinked(DoublyLinkedNode *node, DoublyLinkedNode **last,
                               DoublyLinkedNode **first) {
    if (*first == NULL) {
        *first = node;
        *last = node;
        node->previous = NULL;
        node->next = NULL;
    } else {
        node->previous = NULL;
        node->next = *first;
        (*first)->previous = node;
        *first = node;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_8001C99C);

INCLUDE_ASM("asm/nonmatchings/game", func_8001CAB8);

#ifdef NON_MATCHING
/* Wall (w6a): body, addressing (D_800A2EC0Absolute alias, table=D_800BE97C[0]
   hoisted to t3) and the phantom volatile framePad[2] (8-byte empty frame) all
   match; loop schedule matches. Only the register ASSIGNMENT rotates with every
   init/statement order tried: retail pseudo order is cursor=t0, base-copy=t1,
   strideNeg=t2, table=t3, count=a2, walk=a3; ours permutes base/cursor/walk/
   count between t0/t1/a2/a3 no matter the order of count=0 / cursor / walk /
   strideNeg inits. Same class as the w3a func_8001F728 param-copy wall. */
extern s32 D_800A2EC0Absolute[];
extern void *D_800BE97C[];
void func_8001CBD4(u8 *arg0) {
    s32 temp;
    s32 strideNeg;
    s32 count;
    s32 idx;
    s32 val;
    s32 base;
    u8 *table;
    u8 *cursor;
    u8 *walk;
    volatile s32 framePad[2];

    temp = D_800A2EC0Absolute[0] & 0x3F;
    table = D_800BE97C[0];
    if (temp < 0x20) {
        temp = temp - 0x20;
    } else {
        temp = 0x20 - temp;
    }
    if (*(s16 *)(arg0 + 0xA) > 0) {
        cursor = arg0;
        walk = arg0;
        strideNeg = -(temp * 0x14);
        count = 0;
        do {
            idx = *(u16 *)(walk + 0x10);
            val = *(s16 *)(cursor + 0x94);
            base = *(s32 *)(arg0 + 0x218);
            *(s32 *)(table + idx * 0x14 + 0x10) = val + base + strideNeg;
            cursor += 6;
            count += 1;
            walk += 2;
        } while (count < *(s16 *)(arg0 + 0xA));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8001CBD4);
#endif

#ifdef NON_MATCHING
/* Wall (w7b): unit diff is clean through the second palette arm except the
   if-arm tail: gcc cross-jumps the identical (sb 0x14, sb 0x15) tail into the
   else arm (j + delay into its middle), 4-8 bytes short; retail keeps the
   j-to-join with sb v1,0x15 in the delay slot. Tried: asm("") before/inside
   the tail, volatile on the else tail stores, separate c pseudos per arm
   (that one flips pal to v1 too). Everything else was solved this session:
   (a) base-first expression order gives retail's base=a0/idx=v1 allocation;
   (b) the D_800A2ED9 byte must load into the SAME variable that gets 0x40
   (one `li v0,0x40` speculated into the beqz delay slot, both arms store
   0x40 at +8/+0xC and reuse the variable for 0xBF); (c) the != 0 arm is the
   fall-through; (d) if-arm +0xD/+0x15 store c (0x78), +9/+0x11 store 0;
   (e) gOTB test must be `!= 0` with the 0-arg call as fall-through. */
extern s32 D_800A2EC8Absolute[];
extern ListNode28 *D_800A3A40Absolute[];
extern s32 gOrderingTableBankAbsolute[];

/* Sets up a shade-tex primitive (0x2C entry) from the D_800A3A40 pool:
   entry +0xE tpage, +0xA clut (first arm only), +8..+0x15 palette bytes. */
void func_8001CC7C(u8 *arg0) {
    s32 idx;
    s32 pal;
    s32 c;
    u8 *entry;

    if (*(s16 *)(arg0 + 0xA) != 4) {
        return;
    }
    entry = (u8 *)D_800A3A40Absolute[0] +
            ((*(u16 *)(arg0 + 0x18) * 2 + *(u16 *)(arg0 + 0x18)) * 4 -
             *(u16 *)(arg0 + 0x18)) *
                4;
    SetShadeTex(entry, 1);
    if (D_800A2EC8Absolute[0] != 0) {
        *(s16 *)(entry + 0xE) = GetTPage(1, 0, 0x200, 0x100);
        *(s16 *)(entry + 0xA) = GetClut(0x200, 0x1FF);
        *(u8 *)(entry + 0x8) = 0;
        *(u8 *)(entry + 0x9) = 0xA7;
        *(u8 *)(entry + 0xC) = 0;
        *(u8 *)(entry + 0xD) = 0xFD;
        *(u8 *)(entry + 0x10) = 0x7F;
        *(u8 *)(entry + 0x11) = 0xA7;
        *(u8 *)(entry + 0x14) = 0x7F;
        *(u8 *)(entry + 0x15) = 0xFD;
        return;
    }
    pal = ((u8 *)D_800A2EC8Absolute)[0x11];
    if (pal != 0) {
        pal = 0x40;
        c = 0x78;
        *(u8 *)(entry + 0x8) = pal;
        *(u8 *)(entry + 0xC) = pal;
        pal = 0xBF;
        *(u8 *)(entry + 0x9) = 0;
        *(u8 *)(entry + 0xD) = c;
        *(u8 *)(entry + 0x10) = pal;
        *(u8 *)(entry + 0x11) = 0;
        *(u8 *)(entry + 0x14) = pal;
        *(u8 *)(entry + 0x15) = c;
    } else {
        pal = 0x40;
        c = 0x3C;
        *(u8 *)(entry + 0x8) = pal;
        *(u8 *)(entry + 0xC) = pal;
        pal = 0xBF;
        *(u8 *)(entry + 0x9) = c;
        *(u8 *)(entry + 0xD) = pal;
        *(u8 *)(entry + 0x10) = pal;
        *(u8 *)(entry + 0x11) = c;
        *(u8 *)(entry + 0x14) = pal;
        *(u8 *)(entry + 0x15) = c;
    }
    if (gOrderingTableBankAbsolute[0] != 0) {
        *(s16 *)(entry + 0xE) = GetTPage(2, 0, 0, 0);
    } else {
        *(s16 *)(entry + 0xE) = GetTPage(2, 0, 0x140, 0);
    }
}
#else
extern s32 D_800A2EC8Absolute[];
extern ListNode28 *D_800A3A40Absolute[];

void func_8001CC7C(u8 *arg0) {
    register s32 pal asm("v0");
    register u16 clut asm("v0");
    register s32 c asm("v1");
    register s32 d asm("a0");
    u8 *entry;

    if (*(s16 *)(arg0 + 0xA) != 4) {
        return;
    }
    entry = (u8 *)D_800A3A40Absolute[0] +
            ((*(u16 *)(arg0 + 0x18) * 2 + *(u16 *)(arg0 + 0x18)) * 4 -
             *(u16 *)(arg0 + 0x18)) *
                4;
    SetShadeTex(entry, 1);
    if (D_800A2EC8Absolute[0] != 0) {
        *(s16 *)(entry + 0xE) = GetTPage(1, 0, 0x200, 0x100);
        clut = GetClut(0x200, 0x1FF);
        d = 0xA7;
        c = 0xFD;
        *(s16 *)(entry + 0xA) = clut;
        pal = 0x7F;
        *(u8 *)(entry + 0x8) = 0;
        *(u8 *)(entry + 0x9) = d;
        *(u8 *)(entry + 0xC) = 0;
        *(u8 *)(entry + 0xD) = c;
        *(u8 *)(entry + 0x10) = pal;
        *(u8 *)(entry + 0x11) = d;
        *(u8 *)(entry + 0x14) = pal;
        *(u8 *)(entry + 0x15) = c;
        return;
    }
    pal = ((u8 *)D_800A2EC8Absolute)[0x11];
    if (pal != 0) {
        pal = 0x40;
        c = 0x78;
        *(u8 *)(entry + 0x8) = pal;
        *(u8 *)(entry + 0xC) = pal;
        pal = 0xBF;
        *(u8 *)(entry + 0x9) = 0;
        *(u8 *)(entry + 0xD) = c;
        *(u8 *)(entry + 0x10) = pal;
        *(u8 *)(entry + 0x11) = 0;
        *(u8 *)(entry + 0x14) = pal;
        *(u8 *)(entry + 0x15) = c;
    } else {
        pal = 0x40;
        c = 0x3C;
        *(u8 *)(entry + 0x8) = pal;
        *(u8 *)(entry + 0xC) = pal;
        pal = 0xBF;
        *(u8 *)(entry + 0x9) = c;
        *(u8 *)(entry + 0xD) = pal;
        *(u8 *)(entry + 0x10) = pal;
        *(u8 *)(entry + 0x11) = c;
        *(u8 *)(entry + 0x14) = pal;
        *(u8 *)(entry + 0x15) = pal;
    }
    if (gOrderingTableBankAbsolute[0] != 0) {
        *(s16 *)(entry + 0xE) = GetTPage(2, 0, 0, 0);
    } else {
        *(s16 *)(entry + 0xE) = GetTPage(2, 0, 0x140, 0);
    }
}

#endif
extern s32 D_800A2EC8Absolute[];
extern ListNode28 *D_800A3A40Absolute[];
extern s32 gOrderingTableBankAbsolute[];

void func_8001CDDC(u8 *arg0) {
    register s32 pal asm("$2");
    register s32 c asm("$4");
    s32 d;
    u8 *entry;

    if (*(s16 *)(arg0 + 0xA) != 4) {
        return;
    }
    entry = (u8 *)D_800A3A40Absolute[0] +
            ((*(u16 *)(arg0 + 0x18) * 2 + *(u16 *)(arg0 + 0x18)) * 4 -
             *(u16 *)(arg0 + 0x18)) *
                4;
    SetShadeTex(entry, 1);
    if (D_800A2EC8Absolute[0] != 0) {
        *(s16 *)(entry + 0xE) = GetTPage(1, 0, 0x200, 0x100);
        *(s16 *)(entry + 0xA) = GetClut(0x200, 0x1FF);
        pal = 0x80;
        c = 0xA7;
        d = 0xFD;
        *(u8 *)(entry + 0x8) = pal;
        *(u8 *)(entry + 0xC) = pal;
        pal = 0x9F;
        *(u8 *)(entry + 0x9) = c;
        *(u8 *)(entry + 0xD) = d;
        *(u8 *)(entry + 0x10) = pal;
        *(u8 *)(entry + 0x11) = c;
        *(u8 *)(entry + 0x14) = pal;
        *(u8 *)(entry + 0x15) = d;
        return;
    }
    pal = ((u8 *)D_800A2EC8Absolute)[0x11];
    if (pal != 0) {
        d = 0x78;
        pal = 0x1F;
        *(u8 *)(entry + 0x8) = 0;
        *(u8 *)(entry + 0x9) = 0;
        *(u8 *)(entry + 0xC) = 0;
        *(u8 *)(entry + 0xD) = d;
        *(u8 *)(entry + 0x10) = pal;
        *(u8 *)(entry + 0x11) = 0;
    } else {
        c = 0x3C;
        d = 0xBF;
        pal = 0x1F;
        *(u8 *)(entry + 0x8) = 0;
        *(u8 *)(entry + 0x9) = c;
        *(u8 *)(entry + 0xC) = 0;
        *(u8 *)(entry + 0xD) = d;
        *(u8 *)(entry + 0x10) = pal;
        *(u8 *)(entry + 0x11) = c;
    }
    *(u8 *)(entry + 0x14) = pal;
    *(u8 *)(entry + 0x15) = d;
    if (gOrderingTableBankAbsolute[0] != 0) {
        *(s16 *)(entry + 0xE) = GetTPage(2, 0, 0xC0, 0);
    } else {
        *(s16 *)(entry + 0xE) = GetTPage(2, 0, 0x200, 0);
    }
}

extern s32 D_800A2EC8Absolute[];
extern ListNode28 *D_800A3A40Absolute[];

void func_8001CF38(u8 *arg0) {
    register s32 pal asm("v0");
    s32 c;
    s32 d;
    u8 *entry;

    if (*(s16 *)(arg0 + 0xA) != 4) {
        return;
    }
    entry = (u8 *)D_800A3A40Absolute[0] +
            ((*(u16 *)(arg0 + 0x18) * 2 + *(u16 *)(arg0 + 0x18)) * 4 -
             *(u16 *)(arg0 + 0x18)) *
                4;
    SetShadeTex(entry, 1);
    if (D_800A2EC8Absolute[0] != 0) {
        *(s16 *)(entry + 0xE) = GetTPage(1, 0, 0x200, 0x100);
        *(s16 *)(entry + 0xA) = GetClut(0x200, 0x1FF);
        pal = 0xA0;
        d = 0xA7;
        c = 0xFD;
        *(u8 *)(entry + 0x8) = pal;
        *(u8 *)(entry + 0xC) = pal;
        pal = 0xBF;
        *(u8 *)(entry + 0x9) = d;
        *(u8 *)(entry + 0xD) = c;
        *(u8 *)(entry + 0x10) = pal;
        *(u8 *)(entry + 0x11) = d;
        *(u8 *)(entry + 0x14) = pal;
        *(u8 *)(entry + 0x15) = c;
        return;
    }
    pal = ((u8 *)D_800A2EC8Absolute)[0x11];
    if (pal != 0) {
        pal = 0x20;
        c = 0x78;
        *(u8 *)(entry + 0x8) = pal;
        *(u8 *)(entry + 0xC) = pal;
        pal = 0x3F;
        *(u8 *)(entry + 0x9) = 0;
        *(u8 *)(entry + 0xD) = c;
        *(u8 *)(entry + 0x10) = pal;
        *(u8 *)(entry + 0x11) = 0;
    } else {
        pal = 0x20;
        d = 0x3C;
        c = 0xBF;
        *(u8 *)(entry + 0x8) = pal;
        *(u8 *)(entry + 0xC) = pal;
        pal = 0x3F;
        *(u8 *)(entry + 0x9) = d;
        *(u8 *)(entry + 0xD) = c;
        *(u8 *)(entry + 0x10) = pal;
        *(u8 *)(entry + 0x11) = d;
    }
    *(u8 *)(entry + 0x14) = pal;
    *(u8 *)(entry + 0x15) = c;
    if (gOrderingTableBankAbsolute[0] != 0) {
        *(s16 *)(entry + 0xE) = GetTPage(2, 0, 0xC0, 0);
    } else {
        *(s16 *)(entry + 0xE) = GetTPage(2, 0, 0x200, 0);
    }
}

extern void (*D_80091080[])(void *);
void ListDispatchCallbacks(u8 *arg0) {
    u8 *node;
    void (*callback)(void *);
    node = *(u8 **)(arg0 + 0x30);
    while (node != 0) {
        callback = D_80091080[*(s16 *)(node + 0xC)];
        callback(node);
        node = *(u8 **)node;
    }
}

#ifdef NON_MATCHING
/* Wall (w4a): gcc re-bases the two negative flagPtr reads into a second pointer register
   (s2 = arg0+0x5a kept for the flags read, s0 = arg0+0x58 for vy/vz; 6 saved s-regs, frame
   0x38) while retail keeps ONE flagPtr = arg0+0x5a with lhu -4/-2/0 offsets and 5 saved
   s-regs, frame 0x30. Everything else matches. Tried: u16* q[-2]/q[-1], byte-offset casts,
   u8* base with casts - the re-base survives all three. */
extern long RotTransPers_nom();
extern void func_8003382C();

void func_8001D108(u8 *arg0) {
    s32 flags;
    s32 index;
    u16 *vertexPtr;
    u8 *flagPtr;
    SVECTOR vertex;

    flags = -1;
    index = 0;
    vertexPtr = (u16 *)(arg0 + 0x54);
    flagPtr = arg0 + 0x5A;
    do {
        vertex.vx = vertexPtr[0];
        vertex.vy = *(u16 *)(flagPtr - 4);
        vertex.vz = *(u16 *)(flagPtr - 2);
        RotTransPers_nom(&vertex);
        func_8003382C(vertexPtr);
        flags &= *(u16 *)flagPtr & 0x7EF6;
        index += 1;
        flagPtr += 8;
        vertexPtr += 4;
    } while (index < 4);
    *(s16 *)(arg0 + 0xE) = flags;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8001D108);
#endif

void func_8001D1B0(s32 *destination, s32 *source) {
    s32 first;
    s32 second;
    first = source[0];
    second = source[1];
    destination[0] = first;
    destination[1] = second;
    first = source[2];
    second = source[3];
    destination[3] = first;
    destination[5] = second;
    first = source[4];
    second = source[5];
    destination[7] = first;
    destination[9] = second;
}

extern s32 D_800A2DEC[], D_800A2DF0[], D_800A37E8[], D_800A397C[], D_800A3A3C[];
void func_8001D1E4(void) {
    D_800A2DEC[0] = 0;
    D_800A2DF0[0] = 1;
    D_800A37E8[0] = 0;
    D_800A3A3C[0] = 0;
    D_800A397C[0] = 1;
}

void func_8001D218(void) {
}

INCLUDE_ASM("asm/nonmatchings/game", func_8001D220);

INCLUDE_ASM("asm/nonmatchings/game", func_8001D638);

INCLUDE_ASM("asm/nonmatchings/game", func_8001D778);

#ifdef NON_MATCHING
/* Wall (w8b): cc1 2.7.2 SEGFAULTS (exit 139) on this draft's tail at this
   TU position; removing only the AddPrim statement lets cc1 finish (exit
   33, diagnostics only). Tried (u8*) cast, (void*) cast, no cast, and a
   hoisted otEntry local -- all crash. Statement-stream ICE class
   (func_8001E17C). Externs: D_800A3D0C[] and D_800A2DB8 need first-time
   declarations (sibling func_8001DA48 pattern). */
extern u8 D_800A3D0C[];
extern s32 D_800A2DB8;
void func_8001D914(s16 arg0, s16 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5,
                   u8 arg6, s32 arg7) {
    u8 *entry;

    entry = D_800A3D0C + (D_800A2DB8 * 2 + D_800A2DB8) * 8;
    SetPolyF4(entry);
    D_800A2DB8 = (D_800A2DB8 + 1) % 24;
    *(s16 *)(entry + 0xA) = arg1;
    *(s16 *)(entry + 0xE) = arg1;
    arg3 += arg1;
    *(s16 *)(entry + 8) = arg0;
    arg2 += arg0;
    *(s16 *)(entry + 0xC) = arg2;
    *(s16 *)(entry + 0x10) = arg0;
    *(s16 *)(entry + 0x12) = arg3;
    *(s16 *)(entry + 0x14) = arg2;
    *(s16 *)(entry + 0x16) = arg3;
    if ((arg7 << 0x18) != 0) {
        SetSemiTrans(entry, 1);
    }
    *(u8 *)(entry + 4) = arg4;
    *(u8 *)(entry + 5) = arg5;
    *(u8 *)(entry + 6) = arg6;
    AddPrim((u8 *)D_800A39C8[0], entry);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8001D914);
#endif

#ifdef NON_MATCHING
/* Wall (w6a): semantics fully recovered (entry = D_800A3F4C + D_800A2DBC*24,
   wrap to 0 at >=2; SetPolyF4; ten byte/half stores; AddPrim(arg0, entry)).
   Prologue, gp/lui addressing, counter math and store schedule all match.
   asm("") after the two sums pins retail's x2-addu-before-y2-stores order.
   Remaining wall: the four parameter-copy registers rotate pairwise
   (retail arg0->s3 arg1->s1 arg2->s2 arg3->s4; ours arg0->s4 arg1->s2
   arg2->s1 arg3->s3) under every init/declaration/statement order tried --
   same class as the func_8001CBD4 / w3a func_8001F728 allocation walls. */
extern u8 D_800A3F4C[];
extern s32 D_800A2DBC;
void func_8001DA48(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 counter;
    s32 next;
    u8 *entry;
    s32 x2;
    s32 y2;

    counter = D_800A2DBC;
    next = counter + 1;
    entry = D_800A3F4C + (counter * 2 + counter) * 8;
    D_800A2DBC = next;
    if (next >= 2) {
        D_800A2DBC = 0;
    }
    SetPolyF4(entry);
    x2 = arg1;
    x2 += arg3;
    y2 = arg2;
    y2 += arg4;
    asm("");
    *(s16 *)(entry + 0x12) = y2;
    *(s16 *)(entry + 0x16) = y2;
    *(s16 *)(entry + 8) = arg1;
    *(s16 *)(entry + 0xA) = arg2;
    *(s16 *)(entry + 0xC) = x2;
    *(s16 *)(entry + 0xE) = arg2;
    *(s16 *)(entry + 0x10) = arg1;
    *(s16 *)(entry + 0x14) = x2;
    *(u8 *)(entry + 4) = 2;
    *(u8 *)(entry + 5) = 0;
    *(u8 *)(entry + 6) = 0;
    AddPrim(arg0, entry);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8001DA48);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8001DB20);

#ifdef NON_MATCHING
/* Wall (w4a): only the i/offset s-register pair is flipped (retail i=s0, offset=s1; ours
   i=s1, offset=s0, spill slots 0x10/0x14 vs 0x18/0x1c). Tried: decl order both ways, body
   stmt order both ways, early-return guard shape, i++ fused into the latch (fixed 2
   scheduling rows but not the pair). 6-8 rows allocation-only; length otherwise correct. */
extern s32 D_800BE978[];
extern ListNode28 *D_800A3A40Absolute[];

extern void func_8001DB20(ListNode28 *, s32);

void func_8001DF60(void) {
    s32 count;
    s32 offset;
    s32 i;

    count = D_800BE978[0];
    i = 0;
    if (count <= 0) {
        return;
    }
    offset = 0;
    do {
        func_8001DB20((ListNode28 *)((u8 *)D_800A3A40Absolute[0] + offset), 1);
        offset += 0x2C;
    } while (i++ < count);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8001DF60);
#endif

void func_8001DFC8(void) {
    extern ListNode28 D_800AE8C0[];
    extern void func_8001DB20(ListNode28 *, s32);
    s32 offset;
    s32 i;
    ListNode28 *node;
    i = 0;
    offset = 0;
    do {
        node = *(ListNode28 **)((u8 *)D_800AE8C0 + offset);
        if (node != NULL) {
            do {
                func_8001DB20(node, 0);
                node = node->next;
            } while (node != NULL);
        }
        i += 1;
        offset += 0x44;
    } while (i < 5);
}

/* Images and matrix state. */

typedef struct {
    u8 pad[16];
} Unk16;
extern Unk16 *D_800A36CC;

Unk16 *func_8001E040(s32 i) {
    return &D_800A36CC[i];
}

INCLUDE_ASM("asm/nonmatchings/game", func_8001E050);

INCLUDE_ASM("asm/nonmatchings/game", func_8001E17C);

void func_8001E230(s32 arg0, s32 arg1) {
    extern s32 func_8003C584(s32, void *);
    extern void GraphicsInit(void);
    extern u_long *FntFlush(s32);
    extern s32 func_8003C8BC(void *, s32, s32);
    extern void func_8003C644(s32, s32, s32, s32);
    extern void GraphicsLoadImageWithXOffset(s32);
    extern void func_8003C63C(s32);
    extern u8 D_800A2DC0[];
    extern char D_8008CD0C[];
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

    handle = func_8003C584(arg0, D_800A2DC0);
    if (handle == 0) {
        GraphicsInit();
        FntPrint(D_8008CD0C);
        FntFlush(-1);
        for (;;) {
        }
    }
    size = func_8003C8BC(handle, 0, 2);
    func_8003C8BC(handle, 0, 0);
    size = (size + 0x7FF) >> 11 << 11;
    if (arg1 == 0) {
        D_800A368C = HeapAlloc(size);
    } else {
        D_800A368C = (void *)arg1;
    }
    func_8003C644((s32)D_800A368C, 1, size, handle);
    image = (u8 *)D_800A368C;
    w = *(u16 *)image;
    h = *(u16 *)(image + 2);
    head = image + 4;
    D_800A37E4 = head;
    D_800A3754 = w;
    count = (s16)w;
    D_800A3738 = h;
    D_800A36CC = (Unk16 *)(head + count * 8);
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
    func_8003C63C(handle);
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

INCLUDE_ASM("asm/nonmatchings/game", func_8001E3E0);

extern s32 D_800A2DC4w15 asm("D_800A2DC4.NON_MATCHING");
extern s32 D_800A2EC4w15[] asm("D_800A2EC4.NON_MATCHING");
extern s32 D_800A2ED0w15[] asm("D_800A2ED0.NON_MATCHING");
extern u8 D_800A3F7Cw15[] asm("D_800A3F7C.NON_MATCHING");
extern u8 D_800A4034w15[] asm("D_800A4034.NON_MATCHING");
extern u8 D_800A43BCw15[] asm("D_800A43BC.NON_MATCHING");
extern u8 D_800A433Cw15[] asm("D_800A433C.NON_MATCHING");
extern s32 D_800A39C4w15[] asm("D_800A39C4.NON_MATCHING");
extern s32 D_800A39CCw15[] asm("D_800A39CC.NON_MATCHING");

void func_8001E7EC(void *arg0, s32 arg1, s32 arg2) {
    u8 *envPtr;
    register s32 flag asm("v0");

    if (arg2 != 0) {
        FntPrint((const char *)arg1);
        FntFlush(-1);
    }
    D_800A2DC4w15 = gOTBnm[0] / 2;
    DrawSync(0);
    VSync(0);
    if (arg2 == 0) {
        func_80012D10(0);
    }
    envPtr = D_800A3F7Cw15 + D_800A2DC4w15 * 0x5C;
    PutDrawEnv((DRAWENV *)envPtr);
    PutDispEnv((DISPENV *)(D_800A4034w15 + D_800A2DC4w15 * 0x14));
    if (arg2 == 0) {
        flag = 0;
        asm("" : : "r"(flag));
        if (D_800A2EA4nm[0] == 2) {
            u8 *otFFC;
            u8 *ot1000;
            u8 *ot1FFC;

            D_800A39C8nm[0] = (s32)arg0;
            func_8003565C(0);
            ot1000 = (u8 *)arg0 + 0x1000;
            D_800A39C4w15[1] = (s32)ot1000;
            func_800356A8(1);
            otFFC = (u8 *)arg0 + 0xFFC;
            AddPrim(otFFC, D_800A43BCw15 + (D_800A2DC4w15 << 6));
            ot1FFC = (u8 *)arg0 + 0x1FFC;
            AddPrim(ot1FFC, D_800A43BCw15 + 0x80 + (D_800A2DC4w15 << 6));
            D_800A39CCw15[-1] = (s32)ot1000;
            if ((D_800A2ED0w15[0] & 8) == 0) {
                func_8001D778(0, 0x77, 0x140, 2, 8, 8, 8, 0);
            }
            AddPrim(ot1000, D_800A43BCw15 - 0x80 + (D_800A2DC4w15 << 6));
            DrawOTag((OT_TYPE *)otFFC);
            DrawOTag((OT_TYPE *)ot1FFC);
        } else if (D_800A2EC4w15[0] != 0 && D_800A2EC8nm[0] == 0) {
            u8 *otFFC;
            u8 *ot1000;
            u8 *ot1FFC;

            D_800A39C8nm[0] = (s32)arg0;
            func_8003565C(0);
            ot1000 = (u8 *)arg0 + 0x1000;
            func_8003587C(ot1000);
            otFFC = (u8 *)arg0 + 0xFFC;
            AddPrim(otFFC, D_800A433Cw15 + (D_800A2DC4w15 << 6));
            func_8001DA48((u8 *)arg0, 0xC6, 0x12, 0x69, 0x26);
            DrawOTag((OT_TYPE *)otFFC);
            ot1FFC = (u8 *)arg0 + 0x1FFC;
            AddPrim(ot1FFC, D_800A433Cw15 + 0x180 + (D_800A2DC4w15 << 6));
            AddPrim(ot1000, D_800A433Cw15 + (D_800A2DC4w15 << 6));
            DrawOTag((OT_TYPE *)ot1FFC);
        } else {
            func_8003565C(0);
            DrawOTag((OT_TYPE *)((u8 *)arg0 + 0xFFC));
        }
    }
}

#ifdef NON_MATCHING
/* Wall (w4a): draft is 0x80 bytes, retail 0xAC. gcc cross-jumps the three identical
   D_800A2DC8/2 tails (lw/srl/addu/sra/j) into one shared block (jumping into its middle);
   retail keeps three separate copies with the 0x3C/0x46/0x82 li INSIDE each arm filling
   the lw load delay. Tried: call-per-arm+return (needed for the out-of-line beq-taken
   arms), mode-assign before/after div, volatile extern (no effect on the merge). */
extern s32 D_800A2DC8;

void func_8001EA90(s32 geomOffsetX, s32 mode) {
    if (mode == 1) {
        geomOffsetX = D_800A2DC8 / 2;
        mode = 0x3C;
        SetGeomOffset(geomOffsetX, mode);
        return;
    }
    if (mode >= 2) {
        if (mode == 3) {
            geomOffsetX = D_800A2DC8 / 2;
            mode = 0x82;
            SetGeomOffset(geomOffsetX, mode);
            return;
        }
        if (mode == 4) {
            SetGeomOffset(0x32, 0x12);
            return;
        }
        return;
    }
    if (mode == 0) {
        geomOffsetX = D_800A2DC8 / 2;
        SetGeomOffset(geomOffsetX, 0x46);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8001EA90);
#endif

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
extern u8 *D_800A3668, *D_800A384C, *D_800A3854, *D_800A3A2C, *D_800A3A34;
void GraphicsPartitionWorkBuffers(void) {
    D_800A384C = D_800910A4;
    D_800A3854 = D_800910A4 + 0x2000;
    D_800A3A2C = D_800910A4 + 0x4000;
    D_800A3A34 = D_800910A4 + 0x5000;
    D_800A3668 = D_800910A4 + 0x6000;
}

extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
void func_8001EBE8(s32 *p) {
    s32 a, b, c, d, e, f, g, h, i;
    a = p[6];
    b = p[9];
    c = p[12];
    d = p[7];
    e = p[10];
    f = p[13];
    g = p[8];
    h = p[11];
    i = p[14];
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

extern s32 D_800A36B0;
extern s32 D_800A36B8;
extern s32 D_800A36C0;
extern s32 D_800A36C8;
extern s32 D_800A36D0;
extern s32 D_800A36D4;
extern s32 D_800A36D8;
extern s32 D_800A36DC;
extern s32 D_800A36E8;

void func_8001EC38(s32 *arg0) {
    D_800A36B0 = arg0[0x3C / 4];
    D_800A36B8 = arg0[0x48 / 4];
    D_800A36C0 = arg0[0x54 / 4];
    D_800A36C8 = arg0[0x40 / 4];
    D_800A36D0 = arg0[0x4C / 4];
    D_800A36D4 = arg0[0x58 / 4];
    D_800A36D8 = arg0[0x44 / 4];
    D_800A36DC = arg0[0x50 / 4];
    D_800A36E8 = arg0[0x5C / 4];
}

extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
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

INCLUDE_ASM("asm/nonmatchings/game", func_8001ED84);

extern s32 D_800A3784;
extern s32 D_800A3790;
extern s32 D_800A3794;
extern s32 D_800A3798;
extern s32 D_800A379C;
extern s32 D_800A37A4;
extern s32 D_800A37AC;
extern s32 D_800A37B4;
extern s32 D_800A37C4;
void func_8001EE74(s32 *arg0) {
    s32 a, b, c, d, e, f, g, h, i;
    a = arg0[6];
    b = arg0[9];
    c = arg0[12];
    d = arg0[7];
    e = arg0[10];
    f = arg0[13];
    g = arg0[8];
    h = arg0[11];
    i = arg0[14];
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

extern s32 D_800A3784;
extern s32 D_800A3790;
extern s32 D_800A3794;
extern s32 D_800A3798;
extern s32 D_800A379C;
extern s32 D_800A37A4;
extern s32 D_800A37AC;
extern s32 D_800A37B4;
extern s32 D_800A37C4;
void func_8001EEC4(s32 *arg0) {
    s32 a, b, c, d, e, f, g, h, i;
    a = arg0[15];
    b = arg0[18];
    c = arg0[21];
    d = arg0[16];
    e = arg0[19];
    f = arg0[22];
    g = arg0[17];
    h = arg0[20];
    i = arg0[23];
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

extern s32 MathMultiplyFixed16(s32, s32);
extern s32 D_800A36B0;
extern s32 D_800A36B8;
extern s32 D_800A36C0;
extern s32 D_800A36C8;
extern s32 D_800A36D0;
extern s32 D_800A36D4;
extern s32 D_800A36D8;
extern s32 D_800A36DC;
extern s32 D_800A36E8;
extern s32 D_800A3784;
extern s32 D_800A3790;
extern s32 D_800A3794;
extern s32 D_800A3798;
extern s32 D_800A379C;
extern s32 D_800A37A4;
extern s32 D_800A37AC;
extern s32 D_800A37B4;
extern s32 D_800A37C4;

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

INCLUDE_ASM("asm/nonmatchings/game", func_8001F1D4);

extern s32 MathMultiplyFixed16(s32, s32);
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
void func_8001F2C4(s32 arg0, s32 arg1, s32 arg2) {
    s32 *matrixA;
    s32 *matrixB;
    s32 value00, value02, value10, value12, value20, value22;
    s32 row0, row1, row2;
    s32 cross01, cross11, cross21, cross02, cross12, cross22;
    matrixA = (s32 *)D_800A3A2C;
    matrixB = (s32 *)D_800A3A34;
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

extern s32 MathMultiplyFixed16(s32, s32);
extern s32 D_800A3784, D_800A3790, D_800A3794, D_800A3798, D_800A379C,
    D_800A37A4, D_800A37AC, D_800A37B4, D_800A37C4;
void func_8001F440(s32 arg0, s32 arg1, s32 arg2) {
    s32 *matrixA;
    s32 *matrixB;
    s32 value00, value02, value10, value12, value20;
    s32 row0, row1, cross01, cross11, cross02, cross12;
    matrixA = (s32 *)D_800A3A2C;
    matrixB = (s32 *)D_800A3A34;
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

extern s32 D_800A3784, D_800A3790, D_800A3794, D_800A3798, D_800A379C,
    D_800A37A4, D_800A37AC, D_800A37B4, D_800A37C4;
extern s32 MathMultiplyFixed16(s32, s32);

void func_8001F5BC(s32 arg0, s32 indexA, s32 indexB) {
    s32 valueA;
    s32 slotA;
    s32 slotB;
    s32 valueB;
    s32 product;

    valueA = ((s32 *)D_800A3A2C)[indexA];
    slotA = ((s32 *)D_800A3A34)[indexA];
    valueB = ((s32 *)D_800A3A2C)[indexB];
    slotB = ((s32 *)D_800A3A34)[indexB];

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

void func_8001F684(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 MathMultiplyFixed16(s32, s32);
    extern s32 D_800A36B0;
    extern s32 D_800A36B8;
    extern s32 D_800A36C0;
    extern s32 D_800A36C8;
    extern s32 D_800A36D0;
    extern s32 D_800A36D4;
    extern s32 D_800A36D8;
    extern s32 D_800A36DC;
    extern s32 D_800A36E8;
    D_800A36B0 = MathMultiplyFixed16(arg0, arg2);
    D_800A36B8 = MathMultiplyFixed16(arg1, arg2);
    D_800A36C0 = arg3;
    D_800A36C8 = -arg1;
    D_800A36D0 = arg0;
    D_800A36D4 = 0;
    D_800A36D8 = -MathMultiplyFixed16(arg0, arg3);
    D_800A36DC = -MathMultiplyFixed16(arg1, arg3);
    D_800A36E8 = arg2;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8001F728);

extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
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

extern s32 D_800A36B0;
extern s32 D_800A36B8;
extern s32 D_800A36C0;
extern s32 D_800A36C8;
extern s32 D_800A36D0;
extern s32 D_800A36D4;
extern s32 D_800A36D8;
extern s32 D_800A36DC;
extern s32 D_800A36E8;

void func_8001F874(s32 *arg0) {
    arg0[0x60 / 4] = (s32)D_800A36B0;
    arg0[0x6C / 4] = (s32)D_800A36B8;
    arg0[0x78 / 4] = (s32)D_800A36C0;
    arg0[0x64 / 4] = (s32)D_800A36C8;
    arg0[0x70 / 4] = (s32)D_800A36D0;
    arg0[0x7C / 4] = (s32)D_800A36D4;
    arg0[0x68 / 4] = (s32)D_800A36D8;
    arg0[0x74 / 4] = (s32)D_800A36DC;
    arg0[0x80 / 4] = (s32)D_800A36E8;
}

extern s32 D_800A3784, D_800A3790, D_800A3794, D_800A3798, D_800A379C,
    D_800A37A4, D_800A37AC, D_800A37B4, D_800A37C4;
void func_8001F8C0(s32 *object) {
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
#ifdef NON_MATCHING
void func_8001F90C(s32 arg0, s32 arg1, s32 arg2, s16 *arg3) {
    s32 sinValue;
    s32 cosValue;
    s32 product;

    sinValue = arg1 << 16;
    product = MathMultiplyFixed16(((s32 *)D_800A3A2C)[arg0], sinValue);
    cosValue = arg2 << 16;
    arg3[0] =
        (product -= MathMultiplyFixed16(((s32 *)D_800A3A34)[arg0], cosValue)) >>
        16;
    arg3[1] = (MathMultiplyFixed16(((s32 *)D_800A3A34)[arg0], sinValue) +
               MathMultiplyFixed16(((s32 *)D_800A3A2C)[arg0], cosValue)) >>
              16;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8001F90C);
#endif

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

extern s32 D_800AE868[];
extern s32 D_800AE86C[];
extern s32 D_800AE870[];
extern s32 D_800AE874[];
extern s32 D_800AE878[];
extern s32 D_800AE87C[];
extern s32 D_800AE880[];
extern s32 D_800AE884[];
extern s32 D_800AE888[];

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
void func_8001FAC0(u8 *arg0, s32 index) {
    *(s32 *)((u8 *)arg0 + 0x18) = ((s16 *)D_800A384C)[index] * 4;
    *(s32 *)((u8 *)arg0 + 0x30) = 0;
    *(s32 *)((u8 *)arg0 + 0x24) = ((s16 *)D_800A3854)[index] * 4;
    *(s32 *)((u8 *)arg0 + 0x1C) = -((s16 *)D_800A3854)[index] * 4;
    *(s32 *)((u8 *)arg0 + 0x34) = 0;
    *(s32 *)((u8 *)arg0 + 0x20) = 0;
    *(s32 *)((u8 *)arg0 + 0x2C) = 0;
    *(s32 *)((u8 *)arg0 + 0x38) = 0x10000;
    *(s32 *)((u8 *)arg0 + 0x28) = ((s16 *)D_800A384C)[index] * 4;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8001FAC0);
#endif

#ifdef NON_MATCHING
/* Wall: scheduler places the D_800A3A34 pointer load and the negu differently than retail. */
void func_8001FB28(u8 *arg0, s32 index) {
    s32 *table1;
    s32 *table2;

    table1 = (s32 *)D_800A3A2C;
    table2 = (s32 *)D_800A3A34;
    *(s32 *)(arg0 + 0x60) = table1[index];
    *(s32 *)(arg0 + 0x78) = 0;
    *(s32 *)(arg0 + 0x6C) = table2[index];
    *(s32 *)(arg0 + 0x64) = -table2[index];
    *(s32 *)(arg0 + 0x7C) = 0;
    *(s32 *)(arg0 + 0x68) = 0;
    *(s32 *)(arg0 + 0x74) = 0;
    *(s32 *)(arg0 + 0x80) = 0x10000;
    *(s32 *)(arg0 + 0x70) = table1[index];
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8001FB28);
#endif

#ifdef NON_MATCHING
/* Wall: retail emits each square into a fresh temp (mflo v1/t0...) and recycles v0 for the next load; our compiler reuses the dead operand register for mflo. Also retail spaces the two mults one slot wider. Consistent with the latency-5 compiler profile in kb/psx/toolchain.md. */
s32 func_8001FB80(void *arg0) {
    s32 dx;
    s32 dy;
    s32 dz;

    dx = *(s32 *)((u8 *)arg0 + 0x9C);
    dy = *(s32 *)((u8 *)arg0 + 0xA0);
    dz = *(s32 *)((u8 *)arg0 + 0xA4);
    return MathSqrt(dx * dx + dy * dy + dz * dz);
}
#else
s32 func_8001FB80(void *arg0) {
    register s32 dx asm("v0");
    register s32 dy asm("v0");
    register s32 dz asm("v0");
    register s32 dxSq asm("a1");
    register s32 dySq asm("v1");
    register s32 dzSq asm("a3");
    register s32 sum asm("a0");

    dx = *(s32 *)((u8 *)arg0 + 0x9C);
    asm volatile("mult\t%0,%0" : : "r"(dx) : "hi", "lo");
    dy = *(s32 *)((u8 *)arg0 + 0xA0);
    asm volatile("mflo\t%0" : "=r"(dxSq) : : "lo");
    asm volatile("mult\t%0,%0" : : "r"(dy) : "hi", "lo");
    dz = *(s32 *)((u8 *)arg0 + 0xA4);
    asm volatile("mflo\t%0" : "=r"(dySq) : : "lo");
    asm volatile("mult\t%0,%0" : : "r"(dz) : "hi", "lo");
    sum = dxSq + dySq;
    asm volatile("mflo\t%0" : "=r"(dzSq) : : "lo");
    return MathSqrt(sum + dzSq);
}

#endif

#ifdef NON_MATCHING
/* Wall: retail emits each square into a fresh temp (mflo v1/t0...) and recycles v0 for the next load; our compiler reuses the dead operand register for mflo. Also retail spaces the two mults one slot wider. Consistent with the latency-5 compiler profile in kb/psx/toolchain.md. */
s32 func_8001FBDC(s32 x, s32 y, s32 z) {
    register s32 xSq asm("v1");
    register s32 ySq asm("t0");
    register s32 zSq asm("v0");
    register s32 sum asm("a0");

    xSq = x * x;
    ySq = y * y;
    zSq = z * z;
    sum = xSq + ySq;
    return MathSqrt(sum + zSq);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8001FBDC);
#endif

#ifdef NON_MATCHING
/* Objects and scene state. */

typedef struct CarVector {
    u8 pad[0x9C];
    s32 x;
    s32 y;
} CarVector;

u32 VectorGetMagnitude2D(CarVector *arg0) {
    s32 sum;
    sum = arg0->x * arg0->x;
    sum += arg0->y * arg0->y;
    return MathSqrt((u32)sum);
}
#else
#ifdef NON_MATCHING
/* Wall: retail emits each square into a fresh temp (mflo v1/t0...) and recycles v0 for the next load; our compiler reuses the dead operand register for mflo. Also retail spaces the two mults one slot wider. Consistent with the latency-5 compiler profile in kb/psx/toolchain.md. */
s32 VectorGetMagnitude2D(void *arg0) {
    s32 dx;
    s32 dy;

    dx = *(s32 *)((u8 *)arg0 + 0x9C);
    dy = *(s32 *)((u8 *)arg0 + 0xA0);
    return MathSqrt(dx * dx + dy * dy);
}
#else
s32 VectorGetMagnitude2D(void *arg0) {
    register s32 dx asm("v0");
    register s32 dy asm("v0");
    register s32 dxSq asm("v1");
    register s32 dySq asm("a2");

    dx = *(s32 *)((u8 *)arg0 + 0x9C);
    asm volatile("mult\t%0,%0" : : "r"(dx) : "hi", "lo");
    dy = *(s32 *)((u8 *)arg0 + 0xA0);
    asm volatile("mflo\t%0" : "=r"(dxSq) : : "lo");
    asm volatile("mult\t%0,%0" : : "r"(dy) : "hi", "lo");
    asm volatile("mflo\t%0" : "=r"(dySq) : : "lo");
    return MathSqrt(dxSq + dySq);
}

#endif
#endif

INCLUDE_RODATA("asm/nonmatchings/game", D_8008CF28);
extern char D_8008CF28[];
extern u32 D_800A38F4Abs[] asm("D_800A38F4.NON_MATCHING");
extern s32 D_800A2DE4Small asm("D_800A2DE4.NON_MATCHING");
extern s32 D_800A3A38Small asm("D_800A3A38.NON_MATCHING");
extern s32 D_800A2E94[];
extern s32 D_800A2ED4[];
extern s32 D_800A2EC8[];
extern s32 D_800A37E8Small asm("D_800A37E8.NON_MATCHING");
extern s32 D_800A3550Small asm("D_800A3550.NON_MATCHING");
extern s32 D_800A3804Small asm("D_800A3804.NON_MATCHING");
extern s32 D_800A3A3CSmall asm("D_800A3A3C.NON_MATCHING");
extern s32 D_800A2DECSmall asm("D_800A2DEC.NON_MATCHING");
extern s32 D_800A397CSmall asm("D_800A397C.NON_MATCHING");
extern s32 D_800A2DF0Small asm("D_800A2DF0.NON_MATCHING");
extern s32 D_800A2DF4Small asm("D_800A2DF4.NON_MATCHING");
extern s32 D_800A3A90Small asm("D_800A3A90.NON_MATCHING");

void func_8001FC6C(void) {
    s32 count;
    void *ptr;
    s32 quotient;

    count = D_800A38F4Abs[0] / 20;
    D_800A2DE4Small = count;
    ptr = HeapAlloc(count * 20);
    D_800A3A38Small = (s32)ptr;
    if (ptr == 0) {
        SystemShowFatalError(D_8008CF28);
    }
    quotient = D_800A2DE4Small / (D_800A2E94[0] + 6);
    D_800A37E8Small = 0;
    D_800A3550Small = 0;
    D_800A3804Small = 0;
    D_800A3A3CSmall = 0;
    D_800A2ED4[0] = 0;
    D_800A2EC8[0] = 0;
    D_800A2DECSmall = 0;
    D_800A397CSmall = 1;
    D_800A2DF0Small = 1;
    D_800A2DF4Small = 1;
    D_800A3A90Small = quotient;
}

#ifdef NON_MATCHING
/* Wall (w6a): head matches through the sw to +0x380 (asm("":::"memory") after
   the u8 increment forces retail's fresh lb counter reload; held/mode/count
   read order pins lh/lw/lb/sw). Remaining: gcc cross-jumps the mode==2 and
   mode!=2 -2-store arms into one bnez + shared store (0x10 short; retail keeps
   beqz v0,e594 / li -2 / j / nop + fall-through bnez), and the final value=1
   lands in a1 with a nop in the second bne delay (retail: li v0,1 in both
   delay slots, sb v0). */
extern u8 D_800A3680[];
extern s32 D_800A397CSmall;
extern void func_80025730(u8 *);
void func_8001FD44(u8 *arg0) {
    s32 count;
    s32 held;
    s32 mode;

    if (arg0 == NULL) {
        return;
    }
    *(u8 *)(arg0 + 0x20C) += 1;
    asm("" : : : "memory");
    held = *(s16 *)(arg0 + 0x114);
    mode = D_800A397CSmall;
    count = *(s8 *)(arg0 + 0x20C);
    *(s32 *)(arg0 + 0x380) = held;
    if (mode == 2) {
        if (count >= 7) {
            *(s8 *)(arg0 + 0x20C) = -2;
        }
    } else if (count >= 3) {
        *(s8 *)(arg0 + 0x20C) = -2;
    }
    if (*(s32 *)(arg0 + 0x354) == (s32)func_80025730 &&
        *(s8 *)(arg0 + 0x20C) == -1) {
        *(s8 *)(arg0 + 0x20C) = 0;
    }
    D_800A3680[0] = 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8001FD44);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8001FDD0);

s16 func_80024E90(s32, s32, s32 *, s32 *, s32 *);
s32 MathMultiplyFixed16(s32, s32); /* extern */

void func_8001FF3C(u8 *arg0, u8 *arg1) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 value0;
    s32 value1;
    s32 value2;
    s32 value3;
    s32 value4;

    sp18 = -1;
    if (func_80024E90(*(s32 *)(arg0 + 0x0), *(s32 *)(arg0 + 0x4), &sp18, &sp1C,
                      &sp20) == -1) {
        value0 = MathMultiplyFixed16(
            *(s32 *)(arg1 + 0xDC), ((s32) * (s32 *)(arg0 + 0x0) >> 2) << 0x10);
        value4 = MathMultiplyFixed16(
            *(s32 *)(arg1 + 0xE0), ((s32) * (s32 *)(arg0 + 0x4) >> 2) << 0x10);
        value3 = MathMultiplyFixed16(
            *(s32 *)(arg1 + 0xE4), ((s32) * (s32 *)(arg0 + 0x8) >> 2) << 0x10);
        value1 = MathMultiplyFixed16(
            *(s32 *)(arg1 + 0xDC), ((s32) * (s32 *)(arg1 + 0x0) >> 2) << 0x10);
        value2 = MathMultiplyFixed16(
            *(s32 *)(arg1 + 0xE0), ((s32) * (s32 *)(arg1 + 0x4) >> 2) << 0x10);
        sp1C = ((((s32) * (s32 *)(arg0 + 0x8) >> 2) -
                 ((s32)((value0 + value4 + value3) -
                        (value1 + value2 +
                         MathMultiplyFixed16(*(s32 *)(arg1 + 0xE4),
                                             ((s32) * (s32 *)(arg1 + 0x8) >> 2)
                                                 << 0x10))) >>
                  0x10)) *
                4) +
               0x12C;
    } else {
        sp1C = (sp1C * 4) + 0x12C;
    }
    if (*(s32 *)(arg0 + 0x8) < sp1C) {
        *(s32 *)(arg0 + 0x8) = sp1C;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_800200B0);

INCLUDE_ASM("asm/nonmatchings/game", func_8002267C);

INCLUDE_ASM("asm/nonmatchings/game", func_800229B8);

extern u8 *D_800A3554[];
extern u8 *D_800A3878w15[] asm("D_800A3878.NON_MATCHING");
extern u8 *D_800A3960w15[] asm("D_800A3960.NON_MATCHING");

void func_80022CA4(void) {
    u8 *node;
    register u8 *rec asm("a1");
    u8 *p;
    s32 current;
    s32 count;
    register s32 multL asm("v1");
    u8 *baseAddr;
    s32 offset;
    u32 bits;
    register u32 w2 asm("a2");
    s32 d;
    s32 dm1;
    register u16 val asm("v1");
    s32 v90;
    register s32 t114 asm("a0");
    register s32 z1 asm("a1");
    s32 i;

    current = D_800A3A3CSmall;
    if (current != D_800A3804Small) {
        d = D_800A3A90Small;
        dm1 = d - 1;
        D_800A3A3CSmall = (current + dm1) % d;
    } else {
        D_800A2ED4[0] = 1;
        func_80052FC4(0);
    }
    multL = D_800A3A3CSmall;
    asm volatile("mult %0, %1" : : "r"(multL), "r"(D_800A2E94[0] + 6));
    node = D_800A3878w15[0];
    asm volatile("mflo %0" : "=r"(count));
    if (node != 0) {
        offset = count * 20;
        do {
            if (*(s16 *)(node + 0x1EC) >= 0) {
                rec = (u8 *)D_800A3A38Small;
                rec = (u8 *)(offset + (s32)rec);
                *(s32 *)(node + 0) = *(s32 *)rec;
                *(s32 *)(node + 4) = *(s32 *)(rec + 4);
                func_800442C8(node);
                val = *(u16 *)(u8 *)(offset + D_800A3A38Small + 0xE);
                *(u8 *)(node + 0x410) = val & 0x7F;
                baseAddr = (u8 *)D_800A3A38Small;
                v90 = (val >> 7) << 17;
                *(s32 *)(node + 0x90) = v90;
                bits = *(s32 *)(u8 *)(offset + (s32)baseAddr + 8);
                *(s16 *)(node + 0x116) = (bits >> 22) * 4;
                val = bits >> 22;
                *(s16 *)(node + 0x20E) = ((bits >> 14) & 0xFF) - 0x80;
                *(s16 *)(node + 0x10C) = (bits & 0x3F) >> 4;
                *(u8 *)(node + 0x3B9) = (bits & 0xF) >> 3;
                *(u8 *)(node + 0xF9) = (bits & 7) >> 2;
                *(s16 *)(node + 0x102) = val;
                *(s16 *)(node + 0x114) = val;
                if ((bits & 3) == 1) {
                    D_800A3960w15[0] = D_800A3554[0];
                } else if ((bits & 3) == 2) {
                    D_800A3960w15[0] = *(u8 **)(D_800A3554[0] + 0x3E0);
                } else {
                    D_800A3960w15[0] = 0;
                }
                w2 = *(s32 *)(u8 *)(offset + D_800A3A38Small + 0x10);
                *(s16 *)(node + 0xFE) = ((w2 >> 20) - 0x800) * 2;
                for (i = 0; i < 4; i++) {
                    *(s16 *)(node + 0x2AC + i * 0x28) = *(u16 *)(node + 0xFE);
                }
                t114 = *(s16 *)(node + 0x114);
                asm volatile("addu %0, $zero, $zero" : "=r"(z1));
                *(s16 *)(node + 0x388) = (w2 << 12) >> 22;
                asm("");
                *(s16 *)(node + 0x38A) = w2 & 0x3FF;
                func_8001F2C4(t114, z1, 0);
                func_8001F828((s32 *)node);
                func_8001F874((s32 *)node);
                *(s32 *)(node + 0x228) = 0;
                *(s16 *)(node + 0x104) = *(u16 *)(node + 0x114);
                func_80028980(node);
                offset += 0x14;
                count += 1;
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != 0);
    }
    func_8003667C((u8 *)D_800A3A38Small + count * 20);
    func_80044594((u8 *)D_800A3A38Small + (count * 20 + 0x50));
}

void func_800229B8(void);

void func_80022F48(void) {
    func_800229B8();
    func_800229B8();
    func_800229B8();
    func_800229B8();
}

extern void func_80022CA4(void);
void func_80022F80(void) {
    func_80022CA4();
    func_80022CA4();
    func_80022CA4();
    func_80022CA4();
}

void func_80022FB8(u8 *arg0, s32 arg1) {
    s32 value;
    s16 shortValue;
    s32 value0;
    s32 value1;
    s32 value2;

    value = 0x400 - arg1;
    if (value == 0x400) {
        asm("");
        value = 0;
    }
    func_8001F2C4(value, 0, 0);
    func_8001F874((s32 *)arg0);
    func_8001F828((s32 *)arg0);
    shortValue = value;
    *(s16 *)(arg0 + 0x102) = shortValue;
    *(s16 *)(arg0 + 0x104) = shortValue;
    *(s16 *)(arg0 + 0x114) = shortValue;
    *(s16 *)(arg0 + 0x116) = value * 4;
    asm("");
    value0 = *(s32 *)(arg0 + 0x18);
    value1 = *(s32 *)(arg0 + 0x1C);
    value2 = *(s32 *)(arg0 + 0x20);
    *(s32 *)(arg0 + 0x3C) = value0;
    *(s32 *)(arg0 + 0x40) = value1;
    *(s32 *)(arg0 + 0x44) = value2;
    asm("");
    value0 = *(s32 *)(arg0 + 0x24);
    value1 = *(s32 *)(arg0 + 0x28);
    value2 = *(s32 *)(arg0 + 0x2C);
    *(s32 *)(arg0 + 0x48) = value0;
    *(s32 *)(arg0 + 0x4C) = value1;
    *(s32 *)(arg0 + 0x50) = value2;
    asm("");
    value0 = *(s32 *)(arg0 + 0x30);
    value1 = *(s32 *)(arg0 + 0x34);
    value2 = *(s32 *)(arg0 + 0x38);
    *(s32 *)(arg0 + 0x54) = value0;
    *(s32 *)(arg0 + 0x58) = value1;
    *(s32 *)(arg0 + 0x5C) = value2;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80023074);

INCLUDE_ASM("asm/nonmatchings/game", func_80023454);

extern char D_800A3038[];
extern s32 D_800A3668Absolute[];

void func_80024210(void) {
    CdlATV vol;

    if (D_800A3038[0x35] == 0) {
        vol.val0 = vol.val1 = vol.val2 = vol.val3 =
            ((s16 *)D_800A3668Absolute)[22] * 125 / 100;
        CdMix(&vol);
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80024280);

INCLUDE_ASM("asm/nonmatchings/game", func_800246C0);

extern s32 D_800A2E08;
extern s32 D_800A3838;
s32 func_800246C0(s32, s32, u8 *);

s32 func_8002482C(s32 arg0, s32 arg1, s32 *arg2) {
    s32 index;
    s32 remaining;
    u8 *entry;
    s32 count;

    count = D_800A2E08;
    arg0 = arg0 / 4;
    arg1 = arg1 / 4;
    index = *arg2;
    if (index == -1) {
        asm("");
        index = 0;
    }
    remaining = count;
    entry = (u8 *)D_800A3838 + (index * 0x10);
    if (remaining > 0) {
        do {
            if (index >= count) {
                index = 0;
                entry = (u8 *)D_800A3838;
            }
            if (arg0 >= *(u16 *)(entry + 0) && *(u16 *)(entry + 4) >= arg0 &&
                arg1 >= *(u16 *)(entry + 2) && *(u16 *)(entry + 6) >= arg1 &&
                (func_800246C0(arg0, arg1, entry) & 0xFF) != 0) {
                *arg2 = index;
                if (index == count) {
                    asm("");
                    index = 0;
                }
                return index;
            }
            remaining -= 1;
            index += 1;
            entry += 0x10;
        } while (remaining > 0);
    }
    *arg2 = -1;
    return -1;
}

extern s32 D_800A2E08;
extern s32 D_800A3838;
s32 func_800246C0(s32, s32, u8 *);

s32 func_80024980(s32 arg0, s32 arg1, s32 *arg2) {
    s32 index;
    s32 remaining;
    u8 *entry;
    s32 count;
    s32 countLessOne;

    count = D_800A2E08;
    arg0 = arg0 / 4;
    arg1 = arg1 / 4;
    index = *arg2;
    if (index == -1) {
        index = 0;
    } else {
        countLessOne = count - 1;
        index = (index + countLessOne) % count;
    }
    remaining = count;
    entry = (u8 *)D_800A3838 + (index * 0x10);
    if (remaining > 0) {
        do {
            if (index >= count) {
                index = 0;
                entry = (u8 *)D_800A3838;
            }
            if (arg0 >= *(u16 *)(entry + 0) && *(u16 *)(entry + 4) >= arg0 &&
                arg1 >= *(u16 *)(entry + 2) && *(u16 *)(entry + 6) >= arg1 &&
                (func_800246C0(arg0, arg1, entry) & 0xFF) != 0) {
                *arg2 = index;
                if (index == count) {
                    asm("");
                    index = 0;
                }
                return index;
            }
            remaining -= 1;
            index += 1;
            entry += 0x10;
        } while (remaining > 0);
    }
    *arg2 = -1;
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80024B08);

INCLUDE_ASM("asm/nonmatchings/game", func_80024E90);

#ifdef NON_MATCHING
/* Wall (w7b): 0xE8 vs retail 0xE4. The two func_8003C8BC results interleave:
   retail sinks `move s0,v0` before the second call's argument setup; gcc
   emits the second call's args first. Retail re-reads D_800A3A54 into v1
   after the func_8003C644 call; our volatile read lands in v0 and rotates
   the following addiu pair. Everything else matches (fatal-error arm,
   0x1F4000-total|0x80000000, the four gp-cursor stores, the <<4/<<3 sums). */
extern s32 D_800A3A54Small;
extern s32 D_800A2E14[];
extern s32 D_800A3810;
extern s32 D_800A356C;
extern char D_8008CFC0[];
extern s32 func_8003C584(s32, void *);
extern s32 func_8003C8BC(void *, s32, s32);
extern void func_8003C644(s32, s32, s32, s32);
extern void func_8003C63C(s32);

/* Loads a track resource: resolves a handle, maps its memory, then records
   the loaded row bounds into the small-data cursors. */
void func_80025370(s32 arg0) {
    s32 handle;
    s32 total;
    s32 cursor;
    s32 row0;
    s32 row1;

    handle = func_8003C584(arg0, D_800A2E14);
    if (handle == 0) {
        SystemShowFatalError(D_8008CFC0);
    }
    total = func_8003C8BC(handle, 0, 2);
    func_8003C8BC(handle, 0, 0);
    D_800A3A54Small = (0x1F4000 - total) | 0x80000000;
    func_8003C644(D_800A3A54Small, 1, total, handle);
    cursor = *(volatile s32 *)&D_800A3A54Small;
    D_800A3A54Small = cursor + 4;
    row0 = *(s32 *)cursor;
    D_800A3A54Small = cursor + 8;
    D_800A2E08 = row0;
    row1 = *(s32 *)(cursor + 4);
    D_800A3838 = cursor + 8;
    D_800A3810 = (cursor + 8) + (row0 << 4);
    D_800A356C = D_800A3810 + (row1 << 3);
    func_8003C63C(handle);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80025370);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008CFE0);
#endif

#ifdef NON_MATCHING
/* Whole body matches except: retail loads the s16 count directly into its
 * register (lh t5) and allocates minX/minY/minZ one register later
 * (t6/t7/t8); gcc 2.7.2 routes the s16 lh through a temp (lh v1 + move t8)
 * and shifts the min/max triple one register earlier. Frame is correct
 * (-8) only with the s16 count; s32 count gives a 0 or 0x10 frame. */
void func_80025454(s32 track) {
    s16 count;
    s32 minX;
    s32 minY;
    s32 minZ;
    s32 maxX;
    s32 maxY;
    s32 maxZ;
    s32 x;
    s32 y;
    s32 z;
    s32 i;
    s32 limit;
    s32 *cursor;

    limit = 0;
    minX = 0;
    minY = 0;
    minZ = 0;
    maxX = 0;
    maxY = 0;
    maxZ = 0;
    i = 0;
    count = *(s16 *)((u8 *)track + 0x28);
    cursor = *(s32 **)((u8 *)track + 0x14);
    for (; i < count; i++) {
        x = cursor[2];
        if (x < minX) {
            minX = x;
        }
        y = cursor[3];
        if (y < minY) {
            minY = y;
        }
        z = cursor[4];
        if (z < minZ) {
            minZ = z;
        }
        if (maxX < x) {
            maxX = x;
        }
        if (maxY < y) {
            maxY = y;
        }
        if (maxZ < z) {
            maxZ = z;
        }
        cursor += 5;
    }
    if (limit < -minX) {
        limit = -minX;
    }
    if (limit < maxX) {
        limit = maxX;
    }
    if (limit < -minY) {
        limit = -minY;
    }
    if (limit < maxY) {
        limit = maxY;
    }
    if (limit < -minZ) {
        limit = -minZ;
    }
    if (limit < maxZ) {
        limit = maxZ;
    }
    *(s32 *)((u8 *)track + 0x18) = limit - 5;
    *(s16 *)((u8 *)track + 0x1C) = minX;
    *(s16 *)((u8 *)track + 0x20) = minY;
    *(s16 *)((u8 *)track + 0x24) = minZ;
    *(s16 *)((u8 *)track + 0x1E) = maxX;
    *(s16 *)((u8 *)track + 0x22) = maxY;
    *(s16 *)((u8 *)track + 0x26) = maxZ;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80025454);
#endif

void func_80025594(u8 *object) {
    *(s16 *)(object + 0x1BC) = 0;
    *(s16 *)(object + 0x388) = 0;
}

void func_800255A0(u8 *arg0) {
    u16 temp;

    temp = *(u16 *)(arg0 + 0x1BC);
    *(s32 *)(arg0 + 0x238) = *(s32 *)(arg0 + 0x238) & 0xFFFF7DBF;
    *(u16 *)(arg0 + 0x1BC) = temp + 1;
    switch ((s16)temp) {
    case 0:
        *(s16 *)(arg0 + 0x1C0) = 0;
        *(s16 *)(arg0 + 0x1BE) = 0;
        return;
    case 32:
        *(u16 *)(arg0 + 0x1BC) = 0;
        break;
    default:
        *(s16 *)(arg0 + 0x1D0) = 32;
        return;
    }
    *(s32 *)(arg0 + 0x354) = (s32)func_80025594;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80025614);

void func_80025594();

void func_80025720(u8 *obj) {
    *(void (**)())(obj + 0x354) = func_80025594;
}

void func_80025730(u8 *obj) {
    extern u8 D_800A35F8[];
    extern u8 *D_800A3960[];
    extern s16 D_800A3910[];
    extern u8 D_800A2EDC[];
    extern void func_80042920();
    extern void func_8004419C(u8 *);
    s32 y;
    s32 value;
    s32 dist;
    s32 i;
    u8 *current;
    u8 *p;

    *(u32 *)(obj + 0x238) &= 0xFFFF7D3F;
    *(u8 *)(obj + 0x410) = 0;
    switch (*(s16 *)(obj + 0x1BC)) {
    case 0:
        value = 0x96;
        *(s16 *)(obj + 0x1BC) = 2;
        *(s16 *)(obj + 0x1BE) = 0;
        *(s16 *)(obj + 0x388) = 0;
        *(s16 *)(obj + 0x38A) = 0;
        i = 3;
        p = obj + 0x78;
        do {
            *(s16 *)(p + 0x2B0) = value;
            i--;
            p -= 0x28;
        } while (i >= 0);
        func_800422C0(obj);
        D_800A35F8[0] = 2;
        D_800A3960[0] = obj;
        D_800A3910[0] = 0x7FFF;
        if (*(s8 *)(obj + 0x20C) == -1) {
            y = *(s16 *)(obj + 0x114);
            if (RandomScaledGet(2) == 0) {
                dist = y + 0x300;
            } else {
                dist = y + 0x500;
            }
            *(s32 *)(obj + 0x380) = dist & 0x3FF;
            *(s8 *)(obj + 0x20C) = 1;
        }
        return;
    case 1:
    case 2:
        func_80042920(obj);
        return;
    case 4:
        func_80042920(obj);
        if (*(u8 *)(obj + 0x268) != 0 && D_800A2EDC[0] != 0) {
            func_8004419C(obj);
            return;
        }
        if (*(s16 *)(obj + 0x38A) == 0x200) {
            D_800A35F8[0] = 1;
        }
        return;
    case 3:
        current = D_800A3960[0];
        *(s16 *)(obj + 0x1BC) = 0;
        *(s16 *)(obj + 0x1BE) = 0;
        *(s16 *)(obj + 0x388) = 0;
        *(s16 *)(obj + 0x38A) = 0;
        if (current == obj) {
            extern s32 D_800A3914[];
            D_800A3914[19] = 0;
        }
        if (D_800A3910[0] > 0) {
            extern s16 D_800A3914[];
            D_800A3914[-2] = 0;
        }
        break;
    default:
        break;
    }
    *(s32 *)(obj + 0x354) = (s32)func_80025594;
}

typedef struct {
    u8 unk0[0x1EC];
    s16 unk1EC;
    u8 unk1EE[0x12];
    s8 unk200;
    u8 unk201[0x153];
    void (*callback)(void);
} Batch0CallbackObject;
void ObjectSetCallbackIfAllowed(Batch0CallbackObject *object,
                                void (*callback)(void)) {
    if (((object->unk1EC != 1) || (callback != func_80025730)) &&
        (object->callback != func_80025730) && (object->unk200 != 4)) {
        object->callback = callback;
    }
}

s32 func_80025938(u8 *arg0, u8 *arg1) {
    s32 dist[3];
    s32 dx;
    s32 dy;
    s32 dz;
    s32 zdiff;
    s32 radius;

    radius = *(s32 *)(*(s32 *)(arg0 + 0x370) + 0x18) +
             *(s32 *)(*(s32 *)(arg1 + 0x370) + 0x18);
    dx = *(s32 *)(arg0 + 0) - *(s32 *)(arg1 + 0);
    if (dx < 0) {
        dx = *(s32 *)(arg1 + 0) - *(s32 *)(arg0 + 0);
    }
    dist[0] = dx;
    dy = *(s32 *)(arg0 + 4) - *(s32 *)(arg1 + 4);
    if (dy < 0) {
        dy = *(s32 *)(arg1 + 4) - *(s32 *)(arg0 + 4);
    }
    dist[1] = dy;
    dz = *(s32 *)(arg0 + 8) - *(s32 *)(arg1 + 8);
    if (dz < 0) {
        dz = *(s32 *)(arg1 + 8) - *(s32 *)(arg0 + 8);
    }
    dist[2] = dz;
    if (radius >= dx) {
        if (radius >= dy) {
            if (radius >= dz) {
                if (*(s32 *)(arg0 + 0x354) != (s32)func_80025730 &&
                    *(s32 *)(arg1 + 0x354) != (s32)func_80025730) {
                    return 1;
                }
                zdiff = *(s32 *)(arg0 + 8) - *(s32 *)(arg1 + 8);
                if (zdiff >= 0) {
                    if (zdiff < 501) {
                        asm("");
                        return 1;
                    }
                    return 0;
                }
                zdiff = *(s32 *)(arg1 + 8) - *(s32 *)(arg0 + 8);
                if (zdiff < 501) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

extern u8 *D_800A3554[];
extern s32 D_800A2E94[];
s32 func_8003702C(u8 *, u8 *);
void func_800406D0(u8 *, u8 *, s32, s32);
void func_80041848(u8 *, s32);

s32 func_80025A38(u8 *arg0) {
    u8 *other;
    s32 dist;

    *(s16 *)(arg0 + 0x1CE) = 0;
    if (*(s32 *)(arg0 + 0x3F0) == 0) {
        goto part2;
    }
    other = *(u8 **)(*(s32 *)(arg0 + 0x3F0) + 8);
    if (arg0 == other) {
        return 0;
    }
    if (func_80025938(arg0, other) == 0) {
        goto part2;
    }
    if (func_800261F8(arg0, other) != 0) {
        goto collide;
    }
part2:
    if (*(s32 *)(arg0 + 0x3F4) == 0) {
        goto scan;
    }
    other = *(u8 **)(*(s32 *)(arg0 + 0x3F4) + 8);
    if (arg0 == other) {
        return 0;
    }
    if (func_80025938(arg0, other) == 0) {
        goto scan;
    }
    if (func_800261F8(arg0, other) == 0) {
        goto scan;
    }
collide:
    if (*(s16 *)(arg0 + 0x1EC) == 0) {
        func_800406D0(arg0, other, 6, 1);
        func_80041848(arg0, 0x4E);
    }
    if (*(s16 *)(other + 0x1EC) == 0) {
        func_800406D0(other, arg0, 6, 1);
    }
    if (*(s16 *)(arg0 + 0x1EC) != 0 && *(s16 *)(other + 0x1EC) != 0) {
        func_800406D0(D_800A3554[0], arg0, 6, 1);
    }
    *(s32 *)(arg0 + 0x3D8) = other;
    return 1;
scan:
    if (*(s16 *)(arg0 + 0x1EC) != 0) {
        return 0;
    }
    if (D_800A2E94[0] < 4) {
        return 0;
    }
    other = *(u8 **)(*(s32 *)(*(s32 *)(arg0 + 0x3F0) + 0) + 8);
    if (other != 0) {
        do {
            if (arg0 == other) {
                return 0;
            }
            dist = func_8003702C(arg0, other);
            if (dist < 0) {
                dist = -func_8003702C(arg0, other);
                asm("");
            } else {
                dist = func_8003702C(arg0, other);
            }
            if (dist >= 2) {
                break;
            }
            if (func_80025938(arg0, other) != 0 &&
                func_800261F8(arg0, other) != 0) {
                if (*(s16 *)(arg0 + 0x1EC) == 0) {
                    func_800406D0(arg0, other, 6, 1);
                }
                if (*(s16 *)(other + 0x1EC) == 0) {
                    func_800406D0(other, arg0, 6, 1);
                }
                if (*(s16 *)(arg0 + 0x1EC) != 0 &&
                    *(s16 *)(other + 0x1EC) != 0) {
                    func_800406D0(D_800A3554[0], arg0, 6, 1);
                }
                *(s32 *)(arg0 + 0x3D8) = other;
                func_80041848(arg0, 0x4E);
            }
            other = *(u8 **)(*(s32 *)(other + 0x3F0) + 8);
        } while (other != 0);
    }
    other = *(u8 **)(*(s32 *)(*(s32 *)(arg0 + 0x3F4) + 4) + 8);
    if (other != 0) {
        do {
            if (arg0 == other) {
                return 0;
            }
            dist = func_8003702C(arg0, other);
            if (dist < 0) {
                dist = -func_8003702C(arg0, other);
                asm("");
            } else {
                dist = func_8003702C(arg0, other);
            }
            if (dist >= 2) {
                return 0;
            }
            if (func_80025938(arg0, other) != 0 &&
                func_800261F8(arg0, other) != 0) {
                if (*(s16 *)(arg0 + 0x1EC) == 0) {
                    func_800406D0(arg0, other, 6, 1);
                }
                if (*(s16 *)(other + 0x1EC) == 0) {
                    func_800406D0(other, arg0, 6, 1);
                }
                if (*(s16 *)(arg0 + 0x1EC) != 0 &&
                    *(s16 *)(other + 0x1EC) != 0) {
                    func_800406D0(D_800A3554[0], arg0, 6, 1);
                }
                *(s32 *)(arg0 + 0x3D8) = other;
                func_80041848(arg0, 0x4E);
            }
            other = *(u8 **)(*(s32 *)(other + 0x3F4) + 8);
        } while (other != 0);
    }
    return 0;
}

extern void func_8003644C(s32, s32, s32, s32);

void func_80025DD4(u8 *arg0, u8 *arg1) {
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;

    if (*(s16 *)(arg0 + 0x1EC) == 1 &&
        *(s16 *)(arg1 + 0x1EC) == *(s16 *)(arg0 + 0x1EC)) {
        return;
    }
    x = (*(s32 *)(arg0 + 0) + *(s32 *)(arg1 + 0)) / 2 + RandomScaledGet(100) -
        50;
    y = (*(s32 *)(arg0 + 4) + *(s32 *)(arg1 + 4)) / 2 + RandomScaledGet(100) -
        50;
    func_8003644C(1, x, y,
                  (*(s32 *)(arg0 + 8) + *(s32 *)(arg1 + 8)) / 2 +
                      RandomScaledGet(50) + 75);
    x2 = (*(s32 *)(arg0 + 0) + *(s32 *)(arg1 + 0)) / 2 + RandomScaledGet(100) -
         50;
    y2 = (*(s32 *)(arg0 + 4) + *(s32 *)(arg1 + 4)) / 2 + RandomScaledGet(100) -
         50;
    func_8003644C(1, x2, y2,
                  (*(s32 *)(arg0 + 8) + *(s32 *)(arg1 + 8)) / 2 +
                      RandomScaledGet(50) + 75);
}

extern void func_8003644C(s32, s32, s32, s32);
extern void func_8001EEC4Args(u8 *, s32);
asm(".globl func_8001EEC4Args\nfunc_8001EEC4Args = func_8001EEC4");

void func_80025F40(u8 *arg0, s32 arg1) {
    s32 pos[3];
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;
    u8 *entry;

    entry = (u8 *)(*(s32 *)(*(s32 *)(arg0 + 0x370) + 0x40) +
                   (1 - (arg1 & 0xFF)) * 0x18);
    pos[0] = *(s32 *)(entry + 4);
    pos[1] = *(s32 *)(entry + 8);
    pos[2] = 0x4B;
    func_8001EEC4Args(arg0, arg1 & 0xFF);
    func_8001F1D4(pos);
    pos[0] += *(s32 *)(arg0 + 0);
    pos[1] += *(s32 *)(arg0 + 4);
    pos[2] += *(s32 *)(arg0 + 8);
    x = pos[0] + RandomScaledGet(25);
    y = pos[1] + RandomScaledGet(25);
    func_8003644C(0, x, y, pos[2] + RandomScaledGet(50));
    x2 = pos[0] + RandomScaledGet(25);
    y2 = pos[1] + RandomScaledGet(25);
    func_8003644C(1, x2, y2, pos[2] + RandomScaledGet(50));
}

void func_80026074(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    register s32 ld5 asm("$2");
    register s32 flag asm("$7");
    volatile s32 pad[16];
    register s32 dx asm("$6");

    ld5 = arg5;
    flag = ld5;
    ld5 = ld5 << 24;
    if (ld5 != 0) {
        dx = arg2 << 16;
        *(s32 *)(arg0 + 0xC4) -= dx;
        *(s32 *)(arg0 + 0xC8) -= *(volatile s32 *)&arg3 << 16;
        *(s32 *)(arg0 + 0xD0) -= (*(volatile s32 *)&arg2 << 16) >> 1;
        *(s32 *)(arg0 + 0xD4) -= (*(volatile s32 *)&arg3 << 16) >> 1;
    } else {
        dx = (arg2 << 16) >> 1;
        *(s32 *)(arg0 + 0xC4) -= dx;
        *(s32 *)(arg0 + 0xC8) -= (*(volatile s32 *)&arg3 << 16) >> 1;
        *(s32 *)(arg0 + 0xD0) -= *(volatile s32 *)&arg2 << 16;
        *(s32 *)(arg0 + 0xD4) -= *(volatile s32 *)&arg3 << 16;
    }
    ld5 = flag << 24;
    if (ld5 != 0) {
        *(s32 *)(arg1 + 0xC4) += *(volatile s32 *)&arg2 << 16;
        *(s32 *)(arg1 + 0xC8) += *(volatile s32 *)&arg3 << 16;
        *(s32 *)(arg1 + 0xD0) += (*(volatile s32 *)&arg2 << 16) >> 1;
        *(s32 *)(arg1 + 0xD4) += (*(volatile s32 *)&arg3 << 16) >> 1;
    } else {
        *(s32 *)(arg1 + 0xC4) += (*(volatile s32 *)&arg2 << 16) >> 1;
        *(s32 *)(arg1 + 0xC8) += (*(volatile s32 *)&arg3 << 16) >> 1;
        *(s32 *)(arg1 + 0xD0) += *(volatile s32 *)&arg2 << 16;
        *(s32 *)(arg1 + 0xD4) += *(volatile s32 *)&arg3 << 16;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_800261F8);

s32 func_800270F4(void *arg0, s32 arg1) {
    register s32 sinValue asm("a1");
    register s32 product1 asm("a1");
    register s32 cosValue asm("v1");
    register s32 product2 asm("v1");
    register s32 argVal asm("v1");
    s32 index;
    s32 argVal2;
    s32 result;

    index = (0x400 - arg1) & 0x3FF;
    sinValue = ((s32 **)D_800A3A2CAbsolute)[0][index];
    asm("");
    argVal = *(s32 *)arg0;
    asm volatile("mult %0, %1" : : "r"(sinValue), "r"(argVal) : "lo");
    cosValue = ((s32 **)D_800A3A34Absolute)[0][index];
    argVal2 = *(s32 *)((s32)arg0 + 4);
    asm volatile("mflo %0" : "=r"(product1));
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("mult %0, %1" : : "r"(cosValue), "r"(argVal2) : "lo");
    asm volatile("mflo %0" : "=r"(product2));
    result = product1 - product2;
    result = -(result >> 16) * 3;
    if (result < 0) {
        asm("");
        result += 3;
    }
    return result >> 2;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80027174);

s32 MathGetAngleDelta(s32 arg0, s32 arg1) {
    s32 value0;

    value0 = arg0 - arg1;
    if (value0 >= 0) {
        if (value0 < 0x201) {

        } else {
            goto block_4;
        }
    } else if (-value0 >= 0x201) {
    block_4:
        if (value0 < 0) {
            value0 += 0x400;
        } else {
            value0 -= 0x400;
        }
    }
    return value0;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80028754);

INCLUDE_ASM("asm/nonmatchings/game", func_80028980);

void func_80028D80(u8 *arg0) {
    register u8 *node asm("$17");
    extern void *D_800A3990;
    extern s8 D_800A2E18;
    extern u8 D_800A2EE4nm[] asm("D_800A2EE4.NON_MATCHING");
    s16 mode;
    s32 idx;
    u8 *base;
    u8 *row;
    s32 scale;
    s32 cur;
    s32 lim;
    s32 temp;
    s32 v1;
    register s32 v7 asm("$3");

    node = arg0;
    mode = *(s16 *)(node + 0x1EC);
    if (mode == 0) {
        if (*(s32 *)(node + 0x28C) <= 0 ||
            (*(u16 *)(node + 0x3A4) & 0x1000) != 0) {
            *(s32 *)(node + 0x88) = 0;
            return;
        }
    } else if (mode == 1 && *(s32 *)(node + 0x290) <= 0) {
        *(s32 *)(node + 0x88) = 0;
        if (*(s16 *)(node + 0x1EC) == mode &&
            *(s32 *)(node + 0x90) <= 0x63FFFF) {
            *(s32 *)(node + 0x88) = MathFixedDivide(1, 0xA);
        }
        return;
    }
    idx = *(s16 *)(node + 0x10C);
    base = node + 0x124;
    D_800A3990 = base;
    row = (u8 *)(idx * 0x18 + (s32)base);
    scale = *(s32 *)row;
    if (*(u8 *)(node + 0xF6) == 0) {
        cur = *(s32 *)(node + 0x90);
        lim = *(s32 *)(row + 4);
        if (cur < lim) {
            if ((lim >> 16) != 0) {
                scale = MathMultiplyFixed16(
                    scale, MathFixedDivide((cur >> 16) + 0x50, lim >> 16));
            }
        } else {
            v1 = *(s32 *)(row + 8);
            if (v1 < cur) {
                scale = MathMultiplyFixed16(
                    scale, MathFixedDivide(0x10, ((cur - v1) >> 16) + 0x10));
            } else {
                scale = scale + MathFixedDivide(1, 6);
            }
        }
    } else {
        v1 = *(s32 *)(base + (s32)D_800A2E18 * 0x18 - 0x10);
        cur = *(s32 *)(node + 0x90);
        if (v1 < cur) {
            scale = MathMultiplyFixed16(
                scale, MathFixedDivide(0x10, ((cur - v1) >> 16) + 0x10));
        }
    }
    v7 = scale * 8;
    if (D_800A2EE4nm[0] != 0) {
        if (*(s16 *)(node + 0x1EC) == 0) {
            scale = MathMultiplyFixed16(
                scale, MathFixedDivide(
                           (*(s8 *)(node + 0x205) - 1) * 0x64 + 0x64, 0x64));
            v7 = scale * 8;
        }
    }
    v7 = v7 - scale;
    scale = v7 >> 2;
    *(s32 *)(node + 0x88) = scale + (*(s32 *)(node + 0x22C) >> 4);
    *(s32 *)(node + 0x90) =
        *(s32 *)(node + 0x90) + (scale + (*(s32 *)(node + 0x22C) >> 4));
}

typedef struct {
    u8 unk0[0x90];
    s32 unk90;
} UnkObject90;
void func_80028F98(UnkObject90 *object) {
    object->unk90 -= 0x40000;
}

extern void func_80028980(void *);
void func_80028FAC(void *object) {
    func_80028980(object);
}

void func_80028D80(u8 *);

void func_80028FCC(u8 *arg0) {
    s32 x84;

    if (arg0 != 0) {
        do {
            *(s32 *)(arg0 + 0x94) = *(s32 *)(arg0 + 0x90);
            x84 = *(s32 *)(arg0 + 0x84);
            if (*(s32 *)(arg0 + 0x90) < x84) {
                func_80028D80(arg0);
                if (x84 < *(s32 *)(arg0 + 0x90)) {
                    *(s32 *)(arg0 + 0x90) = x84;
                }
            } else {
                if (x84 < *(s32 *)(arg0 + 0x90)) {
                    *(s32 *)(arg0 + 0x90) = *(s32 *)(arg0 + 0x90) - 0x40000;
                }
            }
            func_80028980(arg0);
            arg0 = *(u8 **)(arg0 + 0x3E0);
        } while (arg0 != 0);
    }
}

extern u8 D_800A2E18;
typedef struct {
    u8 pad0[0xF6];
    u8 state;
    u8 padF7[0x15];
    u16 count;
} Counter;
void SelectionStepForward(Counter *selection) {
    u16 newIndex;
    if (selection->state == 0) {
        newIndex = selection->count + 1;
        selection->count = newIndex;
        if ((s16)newIndex >= (s8)D_800A2E18) {
            selection->count = (u16)((s8)D_800A2E18 - 1);
        }
        func_80028980(selection);
    }
}

typedef struct SelectionState {
    u8 pad0[0xF6];
    u8 unkF6;
    u8 padF7[0x11];
    s16 selectedValue;
    u8 pad10A[2];
    s16 selectionIndex;
} SelectionState;

void SelectionStepBackward(SelectionState *selection) {
    u16 newIndex;
    s32 index;
    s32 value;
    s32 *record;

    if (selection->unkF6 == 0) {
        newIndex = selection->selectionIndex - 1;
        selection->selectionIndex = newIndex;
        if ((s16)newIndex < 0)
            selection->selectionIndex = 0;
        func_80028980(selection);
        index = selection->selectionIndex;
        record = (s32 *)selection;
        record += index * 6;
        value = record[0x130 / 4];
        selection->selectedValue = value;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80029150);

extern void func_80029150(s32 *);
void func_80029450(s32 *p) {
    func_80029150(p);
    p[0] += p[0xB0 / 4];
    p[1] += p[0xB4 / 4];
    p[2] += p[0xB8 / 4];
}

INCLUDE_ASM("asm/nonmatchings/game", func_800294A8);

void func_800297D0(u8 *arg0) {
    extern void func_80031264(void);
    extern void func_800294A8(void *);
    extern void func_800414E0(void *, s32, s32);
    extern void func_80027174(void *);
    extern s32 D_800A2EC8NM[] asm("D_800A2EC8.NON_MATCHING");

    func_80031264();
    *(u8 *)(arg0 + 0x375) = 1;
    func_800294A8(arg0);
    if (D_800A2EB0Absolute[0] <= 0) {
        if (func_80025A38(arg0) != 0) {
            *(s16 *)(arg0 + 0x1E0) = func_8002482C(
                *(s32 *)(arg0 + 0), *(s32 *)(arg0 + 4), (s32 *)(arg0 + 0x1F8));
        }
    }
    if (*(u8 *)(arg0 + 0xF5) != 0 || *(s16 *)(arg0 + 0x1E0) == -1) {
        func_800414E0(arg0, 7, 8);
        if (*(s32 *)(arg0 + 0x354) == (s32)func_80025730 &&
            D_800A2EC8NM[0] == 0) {
            *(s32 *)(arg0 + 0) = *(s32 *)(arg0 + 0xC);
            *(s32 *)(arg0 + 4) = *(s32 *)(arg0 + 0x10);
            *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 0x14);
            *(s32 *)(arg0 + 0x90) = *(s32 *)(arg0 + 0x90) / 2;
            *(u16 *)(arg0 + 0x104) = (*(u16 *)(arg0 + 0x104) + 0x200) & 0x3FF;
        }
        func_80027174(arg0);
        *(u8 *)(arg0 + 0xF5) = 0;
        *(u8 *)(arg0 + 0x375) = 0;
    }
}

#ifdef NON_MATCHING
/* Same length; differs only in store scheduling: retail sinks each result
 * store past the next call's a1 load and materializes the table base into
 * v1, keeping the result live in v0. Our gcc stores early and reuses v0. */
void func_800298E0(s32 *car) {
    s32 index;

    index = ((s16 *)car)[0x8A];
    car[0x31] = MathMultiplyFixed16((*(s32 **)D_800A3A2CAbsolute)[index], car[0x24]);
    car[0x32] = MathMultiplyFixed16((*(s32 **)D_800A3A34Absolute)[index], car[0x24]);
    car[0x34] = MathMultiplyFixed16((*(s32 **)D_800A3A2CAbsolute)[index], car[0x24]);
    car[0x35] = MathMultiplyFixed16((*(s32 **)D_800A3A34Absolute)[index], car[0x24]);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800298E0);
#endif

extern void func_8003644C(s32, s32, s32, s32);

void func_80029994(u8 *arg0, s32 arg1) {
    s32 pos[3];
    s32 x;
    u8 *entry;

    if (*(u8 *)(arg0 + 0xF4) != 0) {
        entry = (u8 *)(*(s32 *)(*(s32 *)(arg0 + 0x370) + 0x40) + arg1 * 0x18);
        pos[0] = *(s32 *)(entry + 4);
        pos[1] = *(s32 *)(entry + 8);
        pos[2] = *(s32 *)(entry + 0xC);
        func_8001EEC4((s32 *)arg0);
        func_8001F1D4(pos);
        pos[0] += *(s32 *)(arg0 + 0);
        pos[1] += *(s32 *)(arg0 + 4);
        pos[2] += *(s32 *)(arg0 + 8);
        x = pos[0] + RandomScaledGet(25);
        func_8003644C(1, x, pos[1] + RandomScaledGet(25), pos[2]);
    }
}

extern void func_8001FAC0(u8 *, s32);
extern s32 D_800A2E1C;

void func_80029A78(u8 *car) {
    s32 angle;
    s32 dist10;
    s32 value;
    s32 scale;
    s32 vy;
    register s32 vxr asm("$2");
    register s32 sq2r asm("$8");
    register s32 sq1r asm("$3");

    *(u16 *)(car + 0x104) = *(u16 *)(car + 0x114);
    func_8001F2C4(*(s16 *)(car + 0x114), 0, 0);
    func_8001F874((s32 *)car);
    if (*(u8 *)(car + 0x410) != 0) {
        *(u16 *)(car + 0x20E) = -*(u16 *)(car + 0x20E);
    }
    angle = *(s16 *)(car + 0x20E);
    if (angle < 0) {
        angle += 0x1000;
    }
    if (*(s32 *)(car + 0xB0) >= 0 ? *(s32 *)(car + 0xB0) < 0x28
                                  : -*(s32 *)(car + 0xB0) < 0x28) {
        if (*(s32 *)(car + 0xB4) >= 0 ? *(s32 *)(car + 0xB4) < 0x28
                                      : -*(s32 *)(car + 0xB4) < 0x28) {
            vxr = *(s32 *)(car + 0xB0);
            asm volatile("mult %0, %0" : : "r"(vxr) : "lo", "hi");
            vy = *(s32 *)(car + 0xB4);
            asm volatile("mflo %0\n\tnop\n\tnop" : "=r"(sq1r));
            asm volatile("mult %0, %0" : : "r"(vy) : "lo", "hi");
            asm volatile("mflo %0" : "=r"(sq2r));
            dist10 = (s32)MathSqrt(sq1r + sq2r) * D_800A2E1C / 10;
            if (*(s16 *)(car + 0x20E) >= 0 ? dist10 < *(s16 *)(car + 0x20E)
                                           : dist10 < -*(s16 *)(car + 0x20E)) {
                if (*(s16 *)(car + 0x20E) >= 0) {
                    angle = dist10;
                } else {
                    angle = (0x1000 - dist10) & 0xFFF;
                }
            }
        }
    }
    *(u16 *)(car + 0x1D0) = angle / 4;
    scale = 1000;
    if (angle >= 0x801) {
        angle -= 0x1000;
    }
    dist10 = angle * scale / 1000;
    *(u16 *)(car + 0x212) = dist10 / 4;
    if (dist10 < 0) {
        dist10 += 0x1000;
    }
    value = (*(u16 *)(car + 0x116) + dist10) & 0xFFF;
    *(u16 *)(car + 0x116) = value;
    *(s16 *)(car + 0x114) = value / 4;
    func_8001FAC0(car, *(s16 *)(car + 0x116));
    if (*(u8 *)(car + 0x410) != 0) {
        *(u16 *)(car + 0x20E) = -*(u16 *)(car + 0x20E);
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80029CB4);

extern void func_80029CB4(s32 *arg0);
extern void func_80039B74(s32 *arg0, s32 arg1);
void func_80029DA8(s32 *car) {
    volatile s32 debugBuffer[16];
    s32 a;
    s32 b;
    s32 c;

    func_8002D16C(car);
    func_8002B538(car);
    func_80029A78(car);
    func_80029150(car);
    a = car[0] + car[0x2C];
    b = car[1] + car[0x2D];
    c = car[2] + car[0x2E];
    car[0] = a;
    car[1] = b;
    car[2] = c;
    func_80029CB4(car);
    func_80039B74(car, 0);
}

void func_80029E2C(void) {
}

void func_80029E34(void) {
}

void func_80029E3C(void) {
}

#ifdef NON_MATCHING
/* Wall (w9c): with D_800A38AC now tracked, the old drift wall is gone.
   Best draft (below) is the same length as retail (0xB4) and differs only
   in scheduling: retail emits lh a0/lh a1 adjacent, then addiu s1/s2, and
   puts addiu s0,s0,0x54 in the jal delay slot with move a2,zero hoisted
   before the register saves; gcc interleaves addiu s1 between the lh pair
   and sinks move a2,zero into the jal delay slot. Locals for the lh args
   add sll/sra pairs (s16 short-local rule). Tried: rowA/rowB before and
   after the call, asm("") between the groups and before the call, h0/h1
   locals. The a2=0 hoist above the register saves looks scheduler-only. */
extern s32 D_800A38AC[];
extern void func_8001F2C4(s32 arg0, s32 arg1, s32 arg2);
extern void func_8001F728(s32 arg0);

void func_80029E44(void) {
    u8 *ptr;
    u8 *rowA;
    u8 *rowB;

    ptr = (u8 *)D_800A38AC[0];
    *(s32 *)(ptr + 0x3C) = *(s32 *)(ptr + 0x18);
    *(s32 *)(ptr + 0x40) = *(s32 *)(ptr + 0x1C);
    *(s32 *)(ptr + 0x44) = *(s32 *)(ptr + 0x20);
    asm("");
    *(s32 *)(ptr + 0x48) = *(s32 *)(ptr + 0x24);
    *(s32 *)(ptr + 0x4C) = *(s32 *)(ptr + 0x28);
    *(s32 *)(ptr + 0x50) = *(s32 *)(ptr + 0x2C);
    asm("");
    *(s32 *)(ptr + 0x54) = *(s32 *)(ptr + 0x30);
    *(s32 *)(ptr + 0x58) = *(s32 *)(ptr + 0x34);
    *(s32 *)(ptr + 0x5C) = *(s32 *)(ptr + 0x38);
    rowA = ptr + 0x3C;
    rowB = ptr + 0x48;
    func_8001F2C4(*(s16 *)(ptr + 0x1C6), *(s16 *)(ptr + 0x1C8), 0);
    ptr += 0x54;
    func_8001F728((s32)rowA);
    func_8001F728((s32)rowB);
    func_8001F728((s32)ptr);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80029E44);
#endif

extern u8 D_800A3A24w15f[] asm("D_800A3A24.NON_MATCHING");
extern u8 D_800A2EE0w15f[] asm("D_800A2EE0.NON_MATCHING");
extern u8 D_800A3764w15f[] asm("D_800A3764.NON_MATCHING");
extern u8 D_800A372Cw15f[] asm("D_800A372C.NON_MATCHING");
extern s16 D_800A35A4w15f[] asm("D_800A35A4.NON_MATCHING");
extern s32 func_8006E770(u8);
extern void func_8006EB18(u8 *);
extern void func_80044114(u8 *);

s32 func_80029EF8(u8 *obj) {
    s32 flags;
    s32 v;
    s32 c4;
    register s32 prod asm("a2");

    c4 = *(s8 *)(obj + 0x3C4);
    v = *(s8 *)(obj + 0x20B);
    if (c4 == 0) {
        obj[0x3C4] = D_800A3A24w15f[v];
    }
    flags = func_8006E770(obj[0x20B]);
    v = *(s8 *)(obj + 0x3C4);
    if (v == 2) {
        goto twoFiveSeven;
    }
    if (v == 5) {
        goto twoFiveSeven;
    }
    if (v != 7) {
        goto notTwoFiveSeven;
    }
twoFiveSeven:
    func_8006EB18(obj);
    asm volatile("mult %0, %1"
                 :
                 : "r"((*(s8 *)(obj + 0x3C5)) << 2), "r"(D_800A2E1C + 2));
    asm volatile("mflo %0" : "=r"(prod));
    *(s16 *)(obj + 0x20E) = -prod / 128;
    *(s32 *)(obj + 0x3BC) = MathFixedDivide(obj[0x3C6], 0xFF);
    *(s32 *)(obj + 0x3C0) = MathFixedDivide(obj[0x3C7], 0x7D0);
    if (obj[0x3C6] < 0x3C) {
        flags &= ~0x40;
    } else {
        flags |= 0x40;
    }
    if (obj[0x3C7] < 0xE6) {
        flags &= ~0x80;
    } else {
        flags |= 0x80;
    }
    v = *(s16 *)(obj + 0x20E);
    if (v >= 2) {
        flags |= 0x8000;
    } else if (v < -1) {
        flags |= 0x200;
    }
    goto afterStatus;
notTwoFiveSeven:
    if (flags & 0x40) {
        *(s32 *)(obj + 0x3BC) += 0x2000;
        if (0x10000 < *(s32 *)(obj + 0x3BC)) {
            *(s32 *)(obj + 0x3BC) = 0x10000;
        }
    } else {
        *(s32 *)(obj + 0x3BC) = 0;
    }
    *(s32 *)(obj + 0x3C0) = 0x10000;
afterStatus:
    if (D_800A2EE0w15f[0] != 0) {
        if (obj[0x3B7] != 0) {
            goto decr3b7;
        }
        if (*(s32 *)(obj + 0x354) == (s32)func_80025594 ||
            *(s16 *)(obj + 0x1BC) == 4) {
            if (flags & 0x40) {
                if ((*(u16 *)(obj + 0x3A4) & 0xF) != 0 ||
                    *(s16 *)(obj + 0x1BC) == 4 ||
                    ((*(u16 *)(obj + 0x3A4) & 0x1000) != 0 &&
                     *(s32 *)(obj + 0x90) == 0)) {
                    func_80044114(obj);
                }
                goto skip3b7;
            }
        }
        if (obj[0x3B7] != 0) {
        decr3b7:
            asm("" : : : "memory");
            obj[0x3B7]--;
        }
    skip3b7:;
    }
    if (*(s32 *)(obj + 0x354) == (s32)func_80025730 || obj[0xF4] == 0 ||
        D_800A3764w15f[0] != 0 ||
        (D_800A372Cw15f[0] != 0 && D_800A35A4w15f[0] >= 0x32)) {
        flags &= ~(0x40 | 0x80 | 0x200 | 0x8000);
        *(s32 *)(obj + 0x3BC) = 0;
    } else if (*(s32 *)(obj + 0x28C) <= 0 ||
               (*(s32 *)(obj + 0x3A4) & 0x100F) != 0) {
        flags &= ~0x40;
        *(s32 *)(obj + 0x3BC) = 0;
    }
    return flags;
}

extern s32 D_800A2E1C, D_800A2E24;
void func_8002A1D0(void) {
    D_800A2E24 = 0x1EF0000 - (D_800A2E1C - 3) * 0x30000;
}

#ifdef NON_MATCHING
/* Wall (w7b): 0xF8 vs retail 0xFC, 4 bytes short, head register rows left.
   Retail keeps the ~status mask in v1 (dead before the func_8001FD44 call)
   and flags in s1 (live to the 0x238 store); gcc gives the mask pseudo an
   s-reg and rotates the two `and` operands (and v0,v0,v1 vs and v0,s1,v0),
   and merges/reorders one instruction somewhere in the call block. Tried:
   mask as a local, mask inlined twice, both orders. Everything else matches
   word for word (the %4 diamond, the xori/sltiu ==3 test, the ^1 arm, the
   always-executed 0x238 store on every path). */
extern s32 D_800A35D4[];
extern s32 D_800A2EC4nm[] asm("D_800A2EC4.NON_MATCHING");
extern s32 D_800A2EA4[];
extern s32 func_80029EF8();
extern void func_8001FD44();

/* Sets bit D_800A2EC4 when the object's 0x209 counter wraps to 3 and the
   0x238 status mask from func_80029EF8 asks for the counter update. */
void func_8002A1FC(u8 *arg0) {
    s32 flags;
    s32 v;
    s32 t;

    flags = func_80029EF8(arg0);
    if (((flags & (~*(s32 *)(arg0 + 0x238) & 0x10)) != 0) ||
        ((flags & (~*(s32 *)(arg0 + 0x238) & 0x4000)) != 0)) {
        func_8001FD44(arg0);
    }
    if (D_800A35D4[0] != 0) {
        *(s32 *)(arg0 + 0x238) = flags;
        return;
    }
    if (((flags & (~*(s32 *)(arg0 + 0x238) & 4)) != 0)) {
        if (((s8 *)D_800A2EA4)[0] != 0) {
            v = *(u8 *)(arg0 + 0x209) ^ 1;
            *(u8 *)(arg0 + 0x209) = v;
        } else {
            t = *(s8 *)(arg0 + 0x209);
            v = (t + 1) % 4;
            *(u8 *)(arg0 + 0x209) = v;
            D_800A2EC4nm[0] = ((s8)v == 3);
        }
        *(s32 *)(arg0 + 0x238) = flags;
    } else {
        *(s32 *)(arg0 + 0x238) = flags;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8002A1FC);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8002A2F8);

INCLUDE_ASM("asm/nonmatchings/game", func_8002A954);

s32 func_8002AAA0(s32 *car) {
    s32 weight;
    s32 total;
    s32 base;

    base = (car[0x14] * 200) >> 16;
    total = (car[0x90] * 35 + car[0x91] * 5) >> 16;
    weight = base + 3000;
    return total + weight;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8002AAF0);

void func_8002AD20(s32 *car, s32 index) {
    s32 entryA;
    s32 entryB;

    entryA = ((s32 **)D_800A3A2CAbsolute)[0][index];
    entryB = ((s32 **)D_800A3A34Absolute)[0][index];
    car[0x31] = MathMultiplyFixed16(entryA, car[0x24]);
    car[0x32] = MathMultiplyFixed16(entryB, car[0x24]);
    car[0x34] = MathMultiplyFixed16(entryA, car[0x24]);
    car[0x35] = MathMultiplyFixed16(entryB, car[0x24]);
    car[0x2C] = MathMultiplyFixed16(entryA, car[0x24]) >> 16;
    car[0x2D] = MathMultiplyFixed16(entryB, car[0x24]) >> 16;
}

void func_8002ADE0(s32 *car, s32 arg1) {
    s32 index;
    s32 entryA;
    s32 entryB;

    index = (((s16 *)car)[0x8A] + 0x200) & 0x3FF;
    entryA = ((s32 **)D_800A3A2CAbsolute)[0][index];
    entryB = ((s32 **)D_800A3A34Absolute)[0][index];
    car[0x31] = car[0x31] + MathMultiplyFixed16(entryA, arg1);
    car[0x32] = car[0x32] + MathMultiplyFixed16(entryB, arg1);
    car[0x34] = car[0x34] + MathMultiplyFixed16(entryA, arg1);
    car[0x35] = car[0x35] + MathMultiplyFixed16(entryB, arg1);
}

#ifdef NON_MATCHING
/* w7c: 0x50 short. Retail spills steer/slide to 0(sp)/4(sp) (frame -0x10),
 * reloads both table entries for the second multiply pair, and issues
 * mult early with the B loads filling the latency window before mflo.
 * gcc 2.7.2 keeps everything in registers (frameless), CSEs the reloads,
 * and emits mflo immediately after mult. sltiu needs the unsigned spelling
 * ((temp & 0xFF) >= 0x65U). Same class as the func_800298E0 scheduling wall.
 */
s32 func_8002AEB0(u8 *arg0) {
    s32 index;
    s32 steer;
    s32 slide;
    s32 temp;

    index = (0x400 - *(s16 *)(arg0 + 0x114)) & 0x3FF;
    steer =
        ((((s32 **)D_800A3A2CAbsolute)[0][index] * *(s32 *)(arg0 + 0xB0)) -
         (((s32 **)D_800A3A34Absolute)[0][index] * *(s32 *)(arg0 + 0xB4))) >>
        16;
    slide =
        ((((s32 **)D_800A3A34Absolute)[0][index] * *(s32 *)(arg0 + 0xB0)) +
         (((s32 **)D_800A3A2CAbsolute)[0][index] * *(s32 *)(arg0 + 0xB4))) >>
        16;
    if (steer < 0) {
        temp = -steer;
        *(u8 *)(arg0 + 0x410) = temp;
        steer = 0;
        if ((temp & 0xFF) >= 0x65U) {
            *(u8 *)(arg0 + 0x410) = 0x64;
        }
    } else {
        *(u8 *)(arg0 + 0x410) = 0;
    }
    return steer << 16;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8002AEB0);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8002AF94);

extern s32 D_800A2E44nm asm("D_800A2E44.NON_MATCHING");
extern s32 D_800A2E48nm asm("D_800A2E48.NON_MATCHING");

void func_8002B258(u8 *arg0) {
    extern u8 D_800A2EE4nm[] asm("D_800A2EE4.NON_MATCHING");
    volatile s32 pad[16];
    s32 speed;
    s32 index;
    s32 scale;
    s32 value;

    if (*(s32 *)(arg0 + 0x238) & 0x80) {
        speed = D_800A2E48nm << 16;
        if (*(s16 *)(arg0 + 0x120) != 0) {
            speed = speed / 3;
        }
        if (*(s8 *)(arg0 + 0x3C4) != 4) {
            *(s32 *)(arg0 + 0x228) =
                MathMultiplyFixed16(speed, *(s32 *)(arg0 + 0x3C0));
        } else {
            *(s32 *)(arg0 + 0x228) += MathFixedDivide(D_800A2E44nm, 100);
            if (speed < *(s32 *)(arg0 + 0x228)) {
                *(s32 *)(arg0 + 0x228) = speed;
            }
        }
        if (*(s32 *)(arg0 + 0x228) > *(s32 *)(arg0 + 0x90)) {
            *(s32 *)(arg0 + 0x228) = *(s32 *)(arg0 + 0x90);
        }
        asm volatile("" : : : "$16");
        scale = *(s32 *)(arg0 + 0x228);
        index = *(s16 *)(arg0 + 0x104);
        if (D_800A2EE4nm[0] != 0) {
            scale = MathMultiplyFixed16(
                scale,
                MathFixedDivide((*(s8 *)(arg0 + 0x205) - 1) * 50 + 100, 100));
            if (*(s32 *)(arg0 + 0x90) < scale) {
                scale = *(s32 *)(arg0 + 0x90);
            }
        }
        if ((*(s32 *)(arg0 + 0xB0) >= 0 ? *(s32 *)(arg0 + 0xB0) < 10
                                        : -*(s32 *)(arg0 + 0xB0) < 10) &&
            (*(s32 *)(arg0 + 0xB4) >= 0 ? *(s32 *)(arg0 + 0xB4) < 10
                                        : -*(s32 *)(arg0 + 0xB4) < 10)) {
            *(s32 *)(arg0 + 0xC4) = 0;
            *(s32 *)(arg0 + 0xC8) = 0;
            *(s32 *)(arg0 + 0xD0) = 0;
            *(s32 *)(arg0 + 0xD4) = 0;
        } else {
            if (scale == 0) {
                scale = 0x50000;
            }
            asm volatile("" : : "r"(index));
            asm volatile("" : : "r"(index));
            asm volatile("" : : "r"(index));
            asm volatile("" : : "r"(index));
            asm volatile("" : : "r"(index));
            asm volatile("" : : "r"(index));
            asm volatile("" : : "r"(index));
            asm volatile("lui $2,%%hi(D_800A3A2CAbsolute)\n\t"
                         "lw $2,%%lo(D_800A3A2CAbsolute)($2)\n\t"
                         "sll $16,$16,2\n\t"
                         "addu $2,$16,$2\n\t"
                         "lw $4,0($2)\n\t"
                         ".set\tnoreorder\n\t"
                         "jal MathMultiplyFixed16\n\t"
                         "addu $5,$18,$0\n\t"
                         ".set\treorder"
                         :
                         :
                         : "$2", "$4", "$5", "$31", "hi", "lo", "memory");
            asm volatile("lw $3,0xC4($17)\n\t"
                         "lui $4,%%hi(D_800A3A34Absolute)\n\t"
                         "lw $4,%%lo(D_800A3A34Absolute)($4)\n\t"
                         "subu $3,$3,$2\n\t"
                         "addu $4,$16,$4\n\t"
                         "sw $3,0xC4($17)\n\t"
                         "lw $4,0($4)\n\t"
                         ".set\tnoreorder\n\t"
                         "jal MathMultiplyFixed16\n\t"
                         "addu $5,$18,$0\n\t"
                         ".set\treorder"
                         :
                         : "r"(scale), "r"(index)
                         : "$2", "$3", "$4", "$5", "$31", "hi", "lo", "memory");
            asm volatile("lw $3,0xC8($17)\n\t"
                         "lui $4,%%hi(D_800A3A2CAbsolute)\n\t"
                         "lw $4,%%lo(D_800A3A2CAbsolute)($4)\n\t"
                         "subu $3,$3,$2\n\t"
                         "addu $4,$16,$4\n\t"
                         "sw $3,0xC8($17)\n\t"
                         "lw $4,0($4)\n\t"
                         ".set\tnoreorder\n\t"
                         "jal MathMultiplyFixed16\n\t"
                         "addu $5,$18,$0\n\t"
                         ".set\treorder"
                         :
                         : "r"(scale), "r"(index)
                         : "$2", "$3", "$4", "$5", "$31", "hi", "lo", "memory");
            asm volatile("lw $3,0xD0($17)\n\t"
                         "lui $4,%%hi(D_800A3A34Absolute)\n\t"
                         "lw $4,%%lo(D_800A3A34Absolute)($4)\n\t"
                         "subu $3,$3,$2\n\t"
                         "addu $16,$16,$4\n\t"
                         "sw $3,0xD0($17)\n\t"
                         "lw $4,0($16)\n\t"
                         ".set\tnoreorder\n\t"
                         "jal MathMultiplyFixed16\n\t"
                         "addu $5,$18,$0\n\t"
                         ".set\treorder\n\t"
                         "lw $3,0xD4($17)\n\t"
                         "subu $3,$3,$2\n\t"
                         "sw $3,0xD4($17)"
                         :
                         : "r"(scale), "r"(index)
                         : "$2", "$3", "$4", "$5", "$31", "hi", "lo", "memory");
        }
        if (*(s32 *)(arg0 + 0x90) > 0x17C0000 && RandomScaledGet(0xA) == 0) {
            value = RandomScaledGet(4);
            if (value < 0) {
                value = -RandomScaledGet(4);
            } else {
                value = RandomScaledGet(4);
            }
            *(s16 *)(arg0 + 0x2D8) = value;
            *(s16 *)(arg0 + 0x2B0) = value;
        }
    } else {
        *(s32 *)(arg0 + 0x228) -= 0x10000;
        if (*(s32 *)(arg0 + 0x228) < 0) {
            *(s32 *)(arg0 + 0x228) = 0;
        }
        *(s16 *)(arg0 + 0x11E) = 0;
        *(s16 *)(arg0 + 0x120) = 0;
        *(s16 *)(arg0 + 0x11C) = 0;
    }
}

void func_8002B538(u8 *arg0) {
    s32 speed;
    s32 half;

    speed = (*(s32 *)(arg0 + 0x90) / *(s16 *)(arg0 + 0x2B4)) >> 16;
    if (*(s16 *)(arg0 + 0x120) != 0 || *(u8 *)(arg0 + 0xF8) != 0) {
        speed = speed * 4;
    }
    *(s32 *)(arg0 + 0x2B8) -= speed;
    *(s32 *)(arg0 + 0x2E0) -= speed;
    half = speed / 2;
    if (*(s32 *)(arg0 + 0x2B8) <= 0x9FFFF) {
        *(s32 *)(arg0 + 0x2B8) = 0xA0000;
    }
    if (*(s32 *)(arg0 + 0x2E0) <= 0x9FFFF) {
        *(s32 *)(arg0 + 0x2E0) = 0xA0000;
    }
    *(s32 *)(arg0 + 0x308) -= half;
    *(s32 *)(arg0 + 0x330) -= half;
    if (*(s32 *)(arg0 + 0x308) <= 0x9FFFF) {
        *(s32 *)(arg0 + 0x308) = 0xA0000;
    }
    if (*(s32 *)(arg0 + 0x330) <= 0x9FFFF) {
        *(s32 *)(arg0 + 0x330) = 0xA0000;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_8002B63C);

INCLUDE_ASM("asm/nonmatchings/game", func_8002B9AC);

INCLUDE_ASM("asm/nonmatchings/game", func_8002BC88);

INCLUDE_ASM("asm/nonmatchings/game", func_8002BD48);

s32 func_8002CF1C(void) {
    return 2000;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8002CF24);

extern s32 D_800A2E94[];
s32 func_8003702C(u8 *, u8 *);
s32 func_8002CF24(u8 *, u8 *);

void func_8002D16C(u8 *arg0) {
    u8 *other;
    s32 flag;
    s32 flag40;
    s32 value;
    s32 newValue;

    *(u8 *)(arg0 + 0x3FC) = 0;
    if (0x8BFFFF < *(s32 *)(arg0 + 0x90)) {
        if (D_800A2E94[0] >= 2) {
            other = *(u8 **)(*(s32 *)(arg0 + 0x3F0) + 8);
            if (other != 0) {
                flag = 1;
                flag40 = 0x28;
                do {
                    if (arg0 == other) {
                        goto decay;
                    }
                    if (func_8003702C(arg0, other) < -0xA) {
                        goto decay;
                    }
                    if ((func_8002CF24(arg0, other) & 0xFF) != 0) {
                        *(u8 *)(arg0 + 0x3FC) = flag;
                        if (*(s16 *)(other + 0x1EC) == 0) {
                            return;
                        }
                        *(u8 *)(other + 0x3FC) = flag40;
                        return;
                    }
                    other = *(u8 **)(*(s32 *)(other + 0x3F0) + 8);
                } while (other != 0);
            }
        decay:
            value = *(s32 *)(arg0 + 0x22C);
            if (value > 0) {
                newValue = value - 0x8000;
                *(s32 *)(arg0 + 0x22C) = newValue;
                if (newValue < 0) {
                    *(s32 *)(arg0 + 0x22C) = 0;
                }
            }
            return;
        }
        *(s32 *)(arg0 + 0x22C) = 0;
    }
}

void func_8002D27C(u8 *arg0) {
    s32 value;

    if (!(0x9FFFF < *(s32 *)(arg0 + 0x90))) {
        *(s16 *)(arg0 + 0x120) = 0;
        *(s16 *)(arg0 + 0x11E) = 0;
    } else {
        if (*(s16 *)(arg0 + 0x120) > 0) {
            *(s16 *)(arg0 + 0x120) = *(s16 *)(arg0 + 0x120) - 1;
            value = RandomScaledGet(4);
            if (value < 0) {
                value = -RandomScaledGet(4);
            } else {
                value = RandomScaledGet(4);
            }
            func_80029994(arg0, value);
        }
        if (*(s32 *)(arg0 + 0x238) & 0x80) {
            if (*(s8 *)(arg0 + 0x3C4) == 4) {
                *(u16 *)(arg0 + 0x11E) += 1;
            } else {
                if (*(s32 *)(arg0 + 0x3C0) >= MathFixedDivide(0xFA, 0x7D0)) {
                    *(u16 *)(arg0 + 0x11E) += 1;
                }
            }
        } else {
            *(s16 *)(arg0 + 0x11E) = 0;
        }
        if (*(s16 *)(arg0 + 0x11E) >= 0x13) {
            *(s16 *)(arg0 + 0x120) = 0x23;
            *(s16 *)(arg0 + 0x11E) = 0;
        }
    }
}

extern s32 D_800A3984[];
extern s32 D_800A2E84;
u8 *func_8002D380(void) {
    s32 index;
    index = D_800A2E84++;
    return (u8 *)D_800A3984[0] + index * 0x500;
}

extern u8 D_800AE88C[];
void func_8002D3A8(u8 *object, s32 index) {
    u8 *data;
    if (index < 0) {
        index = -index;
        data = D_800AE88C + index * 0x44;
    } else {
        data = D_800AE88C;
    }
    *(u8 **)(object + 0x370) = data;
    *(u8 **)(object + 0x36C) = data;
    object[0x374] = 0;
    object[0x200] = index;
}

#ifdef NON_MATCHING
/* w9c: UNLOCK CONFIRMED — with D_800A2E64/E7C/E80 tracked, direct externs
 * give the gp_rel E7C/E80 loads and the lui/lw E64 read with no label
 * drift (the w7c alias workaround is obsolete). Division magic 0x82082083
 * verified numerically as signed /63. Remaining walls (extends the w8
 * func_8006BA68 family): (1) retail computes the E7C-E80 diff into a2
 * (then reuses a2 for the /63 magic) — gcc reuses v1, the destination of
 * the E7C load, and no spelling tried (diff local, compound assign) moves
 * it; (2) retail anchors the loop store group at the arg0 copy
 * (move a1,a3; positive offsets) — gcc re-anchors at max offset
 * (addiu a1,a3,0x2b8; negative offsets), insensitive to store order and
 * sw placement. Draft below is length-exact; only those register rows
 * differ. s16 revs also drops the sra31/subu sign-fix pair (keep s32). */
extern s32 D_800A2E7Cgp asm("D_800A2E7C.NON_MATCHING");
extern s32 D_800A2E80gp asm("D_800A2E80.NON_MATCHING");
extern s32 D_800A2E64[];
extern s8 D_800A3860[][4];
void func_8002D3EC(u8 *arg0) {
    u8 *entry;
    s32 i;
    s32 diff;
    s32 revs;

    diff = D_800A2E7Cgp - D_800A2E80gp;
    *(s32 *)(arg0 + 0x234) =
        D_800A2E80 + diff * D_800A3860[*(s8 *)(arg0 + 0x20B)][0] / 63;
    revs = D_800A2E64[0] - D_800A3860[*(s8 *)(arg0 + 0x20B)][0] * 0xC8 / 63;
    entry = arg0;
    i = 0;
    do {
        *(s16 *)(entry + 0x2B2) = 0;
        *(s16 *)(entry + 0x2B0) = 0;
        *(s16 *)(entry + 0x2AE) = 0;
        *(s16 *)(entry + 0x2B4) = revs;
        *(s32 *)(entry + 0x2B8) = *(s32 *)(arg0 + 0x234);
        i += 1;
        entry += 0x28;
    } while (i < 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8002D3EC);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8002D4CC);

INCLUDE_ASM("asm/nonmatchings/game", func_8002D874);

void func_8002DA30(s32 *arg0) {
    arg0[0x3C / 4] = 0x10000;
    arg0[0x18 / 4] = 0x10000;
    arg0[0x4C / 4] = 0x10000;
    arg0[0x28 / 4] = 0x10000;
    arg0[0x5C / 4] = 0x10000;
    arg0[0x38 / 4] = 0x10000;
    arg0[0x24 / 4] = 0;
    arg0[0x20 / 4] = 0;
    arg0[0x1C / 4] = 0;
    arg0[0x34 / 4] = 0;
    arg0[0x30 / 4] = 0;
    arg0[0x2C / 4] = 0;
    arg0[0x48 / 4] = 0;
    arg0[0x44 / 4] = 0;
    arg0[0x40 / 4] = 0;
    arg0[0x58 / 4] = 0;
    arg0[0x54 / 4] = 0;
    arg0[0x50 / 4] = 0;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8002DA80);

extern s32 D_800A353C_a[] asm("D_800A353C.NON_MATCHING");
extern s32 D_800A353C_b[] asm("D_800A3540.NON_MATCHING");
extern s32 D_800A353C_c[] asm("D_800A3538.NON_MATCHING");
extern s32 D_800A3758_a[] asm("D_800A3758.NON_MATCHING");
extern s32 D_800A3758_b[] asm("D_800A3754.NON_MATCHING");
extern s32 D_800A3758_c[] asm("D_800A3760.NON_MATCHING");
extern u8 *D_800A3574_a[] asm("D_800A3574.NON_MATCHING");
extern u8 *D_800A3574_b[] asm("D_800A3570.NON_MATCHING");
extern s32 D_800A3630_nm asm("D_800A3630.NON_MATCHING");
extern s32 D_800A2F30_nm[] asm("D_800A2F30.NON_MATCHING");
extern u8 D_800AE99C_nm[] asm("D_800AE99C.NON_MATCHING");
extern void func_8003CDBC();
extern void func_8001E17C();
extern void func_800323F0(s32, s32);
extern void func_80032494(u8 *);
void func_8002DC2C(void) {
    u8 *rec;
    s32 cursor;
    s32 n;
    s32 i;
    s32 j;
    s32 row;
    s32 sumv;
    s32 val;
    register s32 minusOne asm("$2");
    register s32 arg0v asm("$4");

    D_800A353C_a[0] = MathFixedDivide(6, 0xF);
    D_800A3758_a[0] = MathFixedDivide(1, 2);
    D_800A3630_nm = 0x18;
    D_800A3758_b[1] = D_800A353C_c[1];
    func_8003CDBC(0xA7, (void *)STACK_BLOCK_801A0000);
    func_8001E17C(6);
    D_800A2F30_nm[0] = 0;
    cursor = 0;
    j = 0;
    row = 0;
    do {
        n = -(j == 0);
        i = 0;
        do {
            sumv = row + i;
            rec = (u8 *)(sumv << 4);
            rec = (u8 *)((u32)rec + (u32)sumv);
            rec = (u8 *)((u32)rec << 2);
            rec = (u8 *)((u32)rec + (u32)D_800AE88C);
            D_800A3574_a[0] = rec;
            func_800323F0(cursor, n);
            cursor++;
            func_80032494(rec);
            minusOne = -1;
            if (n != minusOne) {
                asm("");
                n++;
            }
            i++;
        } while (i < 4);
        j++;
        row += 5;
    } while (j <= 0);
    val = MathFixedDivide(3, 2);
    asm volatile("ori %0, $zero, 4" : "=r"(arg0v));
    rec = D_800AE99C_nm;
    D_800A353C_b[-1] = val;
    D_800A3758_c[-2] = val;
    D_800A3574_b[1] = rec;
    func_800323F0(arg0v, -1);
    func_80032494(rec);
    func_8001DFC8();
}

extern s32 D_800A2EB0;
extern s32 D_800A3984[];
void *HeapAlloc(u32);

s32 func_8002DDA0(void) {
    s32 size;

    size = 0x1900;
    if (D_800A2EB0 <= 0) {
        size = 0x8200;
    }
    D_800A3984[0] = (s32)HeapAlloc(size);
    return D_800A3984[0] == 0;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8002DDD8);

void func_8002E228(void) {
}

void func_8002E230(void) {
    volatile s32 debugBuffer[16];
}

INCLUDE_ASM("asm/nonmatchings/game", func_8002E240);

INCLUDE_ASM("asm/nonmatchings/game", func_8002E594);

INCLUDE_ASM("asm/nonmatchings/game", func_8002E9AC);

extern s32 D_800A2EC8Small;
extern u8 *D_800A3878;
extern void func_8002E9AC(s32 arg0);

void func_8002EE88(void) {
    u8 *node;

    node = D_800A3878;
    if (D_800A2EC8Small != 0) {
        while (node != 0) {
            func_8002E9AC((s32)node);
            node = *(u8 **)(node + 0x3E0);
        }
    } else if (node != 0) {
        do {
            func_8002E9AC((s32)node);
            node = *(u8 **)(node + 0x3E0);
        } while (node != 0);
    }
}

#ifdef NON_MATCHING
/* w8c: structure matches through both arms; ours is 8 bytes short
 * (frame 0x30 vs 0x38, retail has one extra 4-byte slot - likely a
 * phantom local) and retail emits `move s1,a0` in the beqz delay slot
 * with `li s2,0x4` after the branch, ours is reversed. Try a
 * `volatile s32 debugBuffer[1];` for the slot, and per-arm statement
 * order, before guarding again.
 */
extern s32 D_800A38AC[];
extern u8 *D_800A3878;
extern u8 D_800A2ED8;
void func_8002EEFC(u8 *arg0) {
    s32 refX;
    s32 refY;
    s32 refZ;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 dist;
    s32 level;
    s32 b;
    s32 v;
    u8 *node;
    u8 *target;

    refX = *(s32 *)((u8 *)D_800A38AC[0] + 0x0);
    refY = *(s32 *)((u8 *)D_800A38AC[0] + 0x4);
    refZ = *(s32 *)((u8 *)D_800A38AC[0] + 0x8);
    node = D_800A3878;
    if (node == NULL) {
        return;
    }
    level = 4;
    target = arg0;
    do {
        if (node == target && *(s16 *)(node + 0x1EC) == 0 && D_800A2ED8 == 0 &&
            *(s8 *)(node + 0x20C) == 0) {
            *(u8 *)(node + 0x374) = level;
            *(u32 *)(node + 0x36C) = *(u32 *)(node + 0x370) + 0x110;
        } else {
            dx = *(s32 *)(node + 0x0) - refX;
            dy = *(s32 *)(node + 0x4) - refY;
            dz = *(s32 *)(node + 0x8) - refZ;
            dist = MathSqrt(dx * dx + dy * dy + dz * dz);
            if (dist < 0x7D0) {
                *(u8 *)(node + 0x374) = 0;
            } else {
                if (dist < 0x1770) {
                    v = 1;
                } else if (dist < 0x2EE0) {
                    v = 2;
                } else {
                    v = 3;
                }
                *(u8 *)(node + 0x374) = v;
            }
            if (D_800A2ED8 != 0) {
                b = *(s8 *)(node + 0x374);
                if (b < 3) {
                    *(s8 *)(node + 0x374) = b + 1;
                }
            }
            if (*(s8 *)(node + 0x200) == level) {
                *(u8 *)(node + 0x374) = 0;
            }
            if (node == target) {
                *(u8 *)(node + 0x374) = 0;
            }
            b = *(u8 *)(node + 0x374);
            *(u32 *)(node + 0x36C) = *(u32 *)(node + 0x370) + (b * 0x44);
        }
        node = *(u8 **)(node + 0x3E0);
    } while (node != NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8002EEFC);
#endif

extern void *D_800A2EA0Small;
extern u8 D_800A2ED8;
extern s32 D_800A2EC4;
extern s32 D_800A38AC[];
extern s32 D_800A37C4Absolute[];
extern s32 D_800A37B4Absolute[];
extern s32 D_800A37ACAbsolute[];
extern s32 D_800A37A4Absolute[];
void func_8002F0A8(u8 *arg0) {
    s32 local[8];
    u8 *owner;

    D_800A2EA0Small = arg0;
    owner = (u8 *)D_800A38AC[0];
    if (arg0 != owner) {
        *(u16 *)(owner + 0x1E0) = *(u16 *)(arg0 + 0x1E0);
    } else {
        *(u16 *)((u8 *)D_800A38AC[0] + 0x1E0) = func_8002482C(
            *(s32 *)(arg0 + 0), *(s32 *)(arg0 + 4), (s32 *)(arg0 + 0x1F8));
    }
    func_8002DA30((s32 *)D_800A38AC[0]);
    if (D_800A2ED8 != 0) {
        func_800200B0((s32 *)D_800A37C4Absolute[0x3A], arg0, D_800A2EC4 + 4);
    } else {
        func_800200B0((s32 *)D_800A37B4Absolute[0x3E], arg0,
                      *(s8 *)(arg0 + 0x20C));
    }
    func_8001EC38((s32 *)D_800A37ACAbsolute[0x40]);
    MatrixBuildRotationFromTransform((s32 *)D_800A37A4Absolute[0x42],
                                     (s32 *)local);
    local[7] = 0;
    local[6] = 0;
    local[5] = 0;
    SetTransMatrix((MATRIX *)local);
    SetRotMatrix((MATRIX *)local);
    func_8002EEFC(arg0);
}

extern u8 D_800A2F9DAbsolute[];
extern s32 D_800A2EACSmall;
extern u8 *D_800A3878;
void func_8002F1A0(void) {
    u8 *node;

    if (((u8 *)D_800A2F9DAbsolute)[-0x45] != 0) {
        func_8003A440();
        func_80028FCC(D_800A3878);
        return;
    }
    if (D_800A2EACSmall != 0) {
        func_8003A54C();
        func_80028FCC(D_800A3878);
        return;
    }
    func_80041AF0(0);
    if ((func_80050D1C() & 0xFF) == 0) {
        node = D_800A3878;
        if (node != NULL) {
            do {
                func_8003CF0C(node);
                ((void (*)(void *)) * (s32 *)(node + 0x350))(node);
                node = *(u8 **)(node + 0x3E0);
            } while (node != NULL);
        }
        func_80028FCC(D_800A3878);
    }
    func_80039CF4();
    node = D_800A3878;
    if (node != NULL) {
        do {
            if (*(s16 *)(node + 0x1EC) == 0) {
                func_800297D0(node);
            } else if ((*(u16 *)(node + 0x3A4) & 0xF) == 0) {
                func_80038D78(node);
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != NULL);
    }
}

extern u8 D_800A3068[];
extern u8 D_800A3069[];
extern s8 D_800A3860S8[] asm("D_800A3860");
extern s8 D_800A3861[];
extern s8 D_800A3862[];
extern s8 D_800A3863[];
extern s32 D_800A2E7C[];
extern s32 D_800A2E80[];
extern void func_80028754(u8 *, s32);
extern void func_8002D3EC(u8 *);

void func_8002F2CC(void) {
    u8 *node;
    u8 *tableBase;
    s32 carIdx;
    s32 val;

    node = D_800A3878;
    tableBase = (u8 *)0x80011E04;
    if (node != NULL) {
        do {
            if (*(s16 *)(node + 0x1EC) == 0) {
                carIdx = *(s8 *)(node + 0x20B);
                node[0xF6] = D_800A3068[carIdx * 2] < 1;
                node[0xF7] = D_800A3069[carIdx * 2];
                val = D_800A3862[carIdx * 4];
                *(s16 *)(node + 0x2A0) = (val - 0x40) / 4;
                val = D_800A3861[carIdx * 4];
                *(s16 *)(node + 0x2A6) = (val - 0x40) / 4;
                *(s16 *)(node + 0x112) =
                    *(u16 *)(tableBase + carIdx * 22 + 0x14);
                val = D_800A3863[carIdx * 4];
                func_80028754(node, 9 - val * 10 / 64);
                val = D_800A3860S8[carIdx * 4];
                if (val == 0x3F) {
                    *(s32 *)(node + 0x234) = D_800A2E7C[0];
                } else {
                    *(s32 *)(node + 0x234) = D_800A2E80[0];
                }
                func_8002D3EC(node);
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != NULL);
    }
    func_8002A954();
}

#ifdef NON_MATCHING
/* w7c: walled on D_800A2EDA - declaring this untracked sdata byte in C
 * shifts the auto data labels -8 (retail lbu 0x1fa(gp) vs ours 0x1f2(gp)).
 * Needs D_800A2EDA tracked in config/symbol_addrs.txt. Also fix when
 * enabled: split the guard into nested ifs (gcc merged D_800A2EDA==0 &&
 * node!=NULL into sltiu/sltu/and), make carIdx an s32 local assigned from
 * *(s8 *)(node + 0x20B) (an s8 local gave lbu+sll18/sra16), and restate
 * the green clamp flag as an expression in the arm so the slti recomputes
 * instead of folding to li 1.
 */
extern u8 D_800A2EDA;
extern s32 D_800A2EB0;
extern u8 *D_800A3878;
extern u8 D_800A3860[][4];
void func_8002F454(void) {
    u8 *node;
    s32 red;
    s32 green;
    s32 flag;
    s8 carIdx;

    node = D_800A3878;
    if (D_800A2EDA == 0 && node != NULL) {
        do {
            if (*(s16 *)(node + 0x1EC) == 0) {
                carIdx = *(s8 *)(node + 0x20B);
                red = 0x20;
                if (D_800A2EB0 >= 0) {
                    red = (*(s16 *)(node + 0x2A0) << 2) + 0x40;
                    green = (*(s16 *)(node + 0x2A6) << 2) + 0x40;
                    if (red < 0) {
                        asm("");
                        red = 0;
                    }
                    if (red >= 0x40) {
                        red = 0x3F;
                    }
                    flag = green < 0x40;
                    if (green < 0) {
                        asm("");
                        green = 0;
                        flag = 1;
                    }
                    if (flag == 0) {
                        green = 0x3F;
                    }
                } else {
                    green = 0x20;
                }
                D_800A3860[carIdx][1] = green;
                D_800A3860[carIdx][2] = red;
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != NULL);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8002F454);
#endif

extern MATRIX D_800A4548[];
extern s32 D_800A359C[];
extern s32 D_800A2F68[];
extern s32 D_800A2EC0;
extern s32 D_800A2EF8;
extern s32 D_800A2EFC;
extern s32 D_800A2F00;
extern s32 D_800A2EAC;
extern s32 D_800A2EF0;

void func_8002F514(void) {
    VECTOR translation;

    D_800A2EC0 = 0;
    translation.vz = 0;
    translation.vy = 0;
    translation.vx = 0;
    TransMatrix(D_800A4548, &translation);
    SetTransMatrix(D_800A4548);
    func_80035B20();
    func_80042EC0();
    func_80034990();
    func_8002DDD8();
    D_800A2EF8 = 0;
    D_800A2EFC = 0;
    D_800A2F00 = 0;
    D_800A359C[0] = 0;
    D_800A2EAC = 0;
    D_800A2F68[0] = 0;
    D_800A2EF0 = 0;
}

void func_80039DDC(void);
void func_8003B6DC(s32);
void func_8002F5A4(void) {
    func_80039DDC();
    func_8003B6DC(1);
}

void func_80041A28(void);
void exit();
void func_8002F5CC(void) {
    func_80041A28();
    exit();
}

void func_8002F5F4(void) {
    extern s32 D_800A2E9CSmall;
    s32 node;
    s32 f;
    s32 temp;

    node = D_800A2E9CSmall;
    node = *(s32 *)(node + 0x3E0);
    D_800A2E9CSmall = node;
    if (node != 0 && *(s32 *)(node + 0x350) != (s32)func_80029E34) {
        return;
    }
    node = D_800A3878;
    temp = *(s32 *)(node + 0x350);
    f = (s32)func_80029E34;
    D_800A2E9CSmall = node;
    if (temp != f) {
        return;
    }
    do {
        node = D_800A2E9CSmall;
        node = *(s32 *)(node + 0x3E0);
        temp = *(s32 *)(node + 0x350);
        D_800A2E9CSmall = node;
    } while (temp == f);
}

void func_8002F66C(void) {
}

void func_8002F674(void) {
    extern s32 D_800A2EC4;
    extern s32 D_800A2E9CSmall;
    extern s32 D_800A2F14;
    extern s32 D_800A2F18;
    extern s32 D_800A2F1C;
    extern s32 D_800A2F20;
    extern s32 D_800A2F24;
    extern u8 *D_800A3554[];
    extern s32 D_800A3558[];
    extern s32 D_800A35E0[];
    extern u32 RandomGetScaled16(s32);
    s32 value;
    s32 r;

    switch (D_800A2EC4) {
    case 0:
        break;
    case 1:
        D_800A2E9CSmall = (s32)D_800A3554[0];
        break;
    case 2:
        D_800A2E9CSmall = (s32)D_800A3554[0];
        break;
    case 3:
        if (D_800A2F14 != 0) {
            D_800A2F24 = 4;
            D_800A2F1C = 0;
            D_800A2F20 = 0;
            *(u8 *)(D_800A3558[0] + 0x20C) = 4;
            D_800A2F14 = 0;
            D_800A2F18 = 100;
        } else {
            D_800A2F20 += 1;
            D_800A2F1C += 1;
            if (D_800A2F18 > 0) {
                D_800A2F18 -= 1;
            }
            if (D_800A2F20 > 100) {
                value = *(s32 *)(D_800A2E9CSmall + 0x3E0);
                D_800A2F20 = 0;
                D_800A2E9CSmall = value;
                if (value == 0) {
                    D_800A2E9CSmall = (s32)D_800A3554[0];
                }
                *(u8 *)(D_800A3558[0] + 0x20C) = D_800A2F24;
                r = RandomGetScaled16(4);
                if (r < 0) {
                    r = -RandomGetScaled16(4);
                } else {
                    r = RandomGetScaled16(4);
                }
                switch (r) {
                case 0:
                    D_800A2F24 = 11;
                    *(u8 *)(D_800A3558[0] + 0x20C) = 11;
                    break;
                case 1:
                    D_800A2F24 = 4;
                    *(u8 *)(D_800A3558[0] + 0x20C) = 4;
                    break;
                case 2:
                    D_800A2F24 = 4;
                    *(u8 *)(D_800A3558[0] + 0x20C) = 4;
                    break;
                case 3:
                    D_800A2F24 = 6;
                    *(u8 *)(D_800A3558[0] + 0x20C) = 6;
                    break;
                }
            }
        }
        break;
    case 4:
        D_800A2E9CSmall = (s32)D_800A35E0[0];
        break;
    }
    if (D_800A2E9CSmall == 0) {
        D_800A2E9CSmall = (s32)D_800A3554[0];
    }
}

extern s32 D_800A2EAC;
extern u8 D_800A35FC[];
void func_8003B6DC(s32 arg0);
void func_8003B464(void);
void func_8003C1CC(void);
void func_8003C3FC(void);

void func_8002F86C(void *arg0, s32 arg1) {

    func_8003B6DC(1);
    func_8003B464();
    if (arg1 != 2) {
        D_800A2EAC = arg1;
    }
    if (D_800A2EB0 == 1) {
        func_8003C3FC();
        *(u8 *)((u8 *)arg0 + 0x20C) = 3;
    } else {
        func_8003C1CC();
        if (*(s8 *)((u8 *)arg0 + 0x204) == 1) {
            *(u8 *)((u8 *)arg0 + 0x20C) = 0xD;
        } else {
            *(u8 *)((u8 *)arg0 + 0x20C) = 0x10;
        }
    }
    D_800A2EAC = arg1;
    D_800A35FC[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8002F910);

INCLUDE_ASM("asm/nonmatchings/game", func_8002FFB8);

INCLUDE_ASM("asm/nonmatchings/game", func_80030204);

extern s32 D_800A3A80;
#ifdef NON_MATCHING
s32 func_800309DC(s32 arg0, s32 *object, s32 *query) {
    SVECTOR **points;
    SVECTOR *pairB;
    SVECTOR *pairA;
    SVECTOR **points;
    SVECTOR *pointA;
    SVECTOR *pointB;
    SVECTOR *point;
    s32 sampleX;
    s32 sampleY;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 z0;
    s32 z1;
    s32 left;
    s32 right;
    s32 leftHeight;
    s32 result;
    s32 i;

    sampleX = query[0];
    sampleY = query[1];
    pairA = NULL;
    points = (SVECTOR **)(object + 6);
    for (i = 4; i > 0; i--) {
        pointA = points[i & 3];
        pointB = points[i - 1];
        if (pointB->vy < pointA->vy) {
            point = pointA;
            pointA = pointB;
            pointB = point;
        }
        if (sampleY < pointA->vy)
            continue;
        if (sampleY >= pointB->vy)
            continue;
        if (pointA->vy == pointB->vy)
            continue;
        if (pairA == NULL) {
            pairA = pointA;
            pairB = pointB;
            continue;
        }
        x0 = pairA->vx;
        x1 = pairB->vx;
        y0 = pairA->vy;
        y1 = pairB->vy;
        if (y1 == y0) {
            left = x0;
        } else {
            left = x0 + (x1 - x0) * (sampleY - y0) / (y1 - y0);
        }
        x0 = pointA->vx;
        x1 = pointB->vx;
        y0 = pointA->vy;
        y1 = pointB->vy;
        if (y1 == y0) {
            right = x0;
        } else {
            right = x0 + (x1 - x0) * (sampleY - y0) / (y1 - y0);
        }
        if (right < left) {
            result = left;
            left = right;
            right = result;
            point = pairA;
            pairA = pointA;
            pointA = point;
            point = pairB;
            pairB = pointB;
            pointB = point;
        }
        if (sampleX < left - 5)
            return 0;
        if (right + 5 < sampleX)
            return 0;
        z0 = pairA->vz;
        z1 = pairB->vz;
        y0 = pairA->vy;
        y1 = pairB->vy;
        if (y1 == y0) {
            leftHeight = z0;
        } else {
            leftHeight = z0 + (z1 - z0) * (sampleY - y0) / (y1 - y0);
        }
        z0 = pointA->vz;
        z1 = pointB->vz;
        y0 = pointA->vy;
        y1 = pointB->vy;
        if (y1 == y0) {
            result = z0;
        } else {
            result = z0 + (z1 - z0) * (sampleY - y0) / (y1 - y0);
        }
        if (right == left) {
            result = leftHeight;
        } else {
            result = leftHeight +
                     (result - leftHeight) * (sampleX - left) / (right - left);
        }
        query[2] = result;
        D_800A3A80 = object;
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800309DC);
#endif

extern s32 D_800A38AC[];
extern s32 D_800BE980[];
s32 func_800309DC(s32, s32 *, s32 *);
void func_80030CDC(s32 *query, s32 index) {
    s8 *node;
    u8 *entries;

    if (index >= 0) {
        entries = (u8 *)D_800BE980[0];
        entries += index * 0x90;
        node = *(s8 **)(entries + 0x20);
        while ((node != NULL) && (((u8)node[0x13] & 0x80) == 0)) {
            if ((node[2] < 0) &&
                ((func_800309DC(D_800A38AC[0], (s32 *)node, query) & 0xFF) !=
                 0)) {
                return;
            }
            node = *(s8 **)(node + 0x28);
        }
    }
}

extern s32 D_800A3A80;
#ifdef NON_MATCHING
void func_80030D80(u8 *object, s32 *query) {
    s8 *node;
    u8 *entry;
    s16 rot;

    rot = *(s16 *)(object + 0x1E0);
    if (rot >= 0) {
        entry = rot * 0x90 + (u8 *)D_800BE980[0];
        node = *(s8 **)(entry + 0x20);
        D_800A3A80 = 0;
        while ((node != NULL) && (((u8)node[0x13] & 0x80) == 0)) {
            if ((node[2] < 0) &&
                ((func_800309DC((s32 *)object, (s32 *)node, query) & 0xFF) !=
                 0)) {
                return;
            }
            node = *(s8 **)(node + 0x28);
        }
        entry = *(u8 **)(entry + 0);
        *(s16 *)(object + 0x1E0) = *(u16 *)(entry + 8);
        node = *(s8 **)(entry + 0x20);
        while ((node != NULL) && (((u8)node[0x13] & 0x80) == 0)) {
            if ((node[2] < 0) &&
                ((func_800309DC((s32 *)object, (s32 *)node, query) & 0xFF) !=
                 0)) {
                return;
            }
            node = *(s8 **)(node + 0x28);
        }
        entry = *(u8 **)(*(u8 **)(entry + 4) + 4);
        *(s16 *)(object + 0x1E0) = *(u16 *)(entry + 8);
        node = *(s8 **)(entry + 0x20);
        while ((node != NULL) && (((u8)node[0x13] & 0x80) == 0)) {
            if ((node[2] < 0) &&
                ((func_800309DC((s32 *)object, (s32 *)node, query) & 0xFF) !=
                 0)) {
                return;
            }
            node = *(s8 **)(node + 0x28);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80030D80);
#endif

#ifdef NON_MATCHING
/*
 * The D_800A384CAbsolute/D_800A3854Absolute defsym aliases now exist
 * (merger added them); this draft uses them for the two lui/lw pointer
 * loads. Still mismatching: first two s16 reads swap v0/v1, the
 * `move s1,a1` param copy lands after the table loads instead of
 * before, gcc extracts mflo early, and D_800A2F2C needs MIXED access
 * (gp decrement + lui/addiu address argument to func_80024E90) that
 * still needs the neighbor-symbol spelling. While the draft is active
 * and the wrong length, every data symbol in the link drifts, so the
 * alias %lo values here read +4 — judge the alias only from a
 * length-correct build.
 */
extern s32 D_800A2F2C;
extern s32 D_800A384CAbsolute[];
extern s32 D_800A3854Absolute[];
extern s32 D_800AE844[];
extern s32 D_800AE848[];
extern s32 D_800AE84C[];
extern s32 D_800B6094[];
u16 func_80030F24(u8 *object, s32 *pointArray, s32 arg2, s32 arg3) {
    s32 point[3];
    s32 outX;
    s32 outZ;
    s16 *tableA;
    s16 *tableB;
    s32 offset;
    s32 value;
    s32 result;
    s16 result16;

    offset = ((*(s16 *)(object + 0x116) + *(s16 *)(object + 0x118) + 0x1000) &
              0xFFF) *
             2;
    tableA = (s16 *)((u8 *)D_800A384CAbsolute[0] + offset);
    tableB = (s16 *)((u8 *)D_800A3854Absolute[0] + offset);
    pointArray[0] += ((*tableA * arg2 - *tableB * arg3) >> 16) * 4;
    pointArray[2] = 0;
    pointArray[1] += ((*tableB * arg2 + *tableA * arg3) >> 16) * 4;
    if (*(s16 *)(object + 0x1EC) == 0) {
        if (D_800A2F2C > 0) {
            D_800A2F2C = D_800A2F2C - 1;
        }
    }
    *(s16 *)(object + 0x1E0) =
        func_80024E90(pointArray[0], pointArray[1], &D_800A2F2C, &outX, &outZ);
    *(s32 *)(object + 0xDC) = D_800B6094[0];
    *(s32 *)(object + 0xE0) = D_800B6094[1];
    *(s32 *)(object + 0xE4) = D_800B6094[2];
    result16 = *(s16 *)(object + 0x1E0);
    if (result16 == -1) {
        *(u8 *)(object + 0xF5) = 1;
        return 0;
    }
    *(s32 *)(object + 0x1F8) = result16;
    if ((*(s16 *)(object + 0x1EC) == 0) && (outZ == 2)) {
        point[0] = pointArray[0] / 4 - D_800AE844[0];
        point[1] = pointArray[1] / 4 - D_800AE848[0];
        func_80030D80(object, point);
        pointArray[2] = (point[2] + D_800AE84C[0]) * 4;
        if (D_800A3A80 == 0) {
            value = 5;
        } else if ((*(u8 *)((u8 *)D_800A3A80 + 0x13) & 8) != 0) {
            value = 2;
        } else {
            value = 5;
        }
        *(s16 *)(object + 0x360) = value;
        if (D_800A3A80 == 0) {
            pointArray[2] = outX * 4;
        }
    } else {
        pointArray[2] = outX * 4;
        *(s16 *)(object + 0x360) = outZ;
    }
    if (*(s16 *)(object + 0x1E0) < *(s16 *)(object + 0x1E2)) {
        *(s16 *)(object + 0x1E2) = *(s16 *)(object + 0x1E0);
    }
    if (*(s16 *)(object + 0x1E4) < *(s16 *)(object + 0x1E0)) {
        *(s16 *)(object + 0x1E4) = *(s16 *)(object + 0x1E0);
    }
    return *(u16 *)(object + 0x360);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80030F24);
#endif

#ifdef NON_MATCHING
void func_800311B4(s32 x, s32 y, s32 z, s32 *out) {
    register s32 xSq asm("v1");
    register s32 ySq asm("t1");
    register s32 zSq asm("v0");
    register s32 sum asm("a0");
    s32 length;

    xSq = x * x;
    ySq = y * y;
    sum = xSq + ySq;
    zSq = z * z;
    length = MathSqrt(sum + zSq);
    if (length == 0) {
        length = 1;
    }
    out[0] = MathFixedDivide(x, length);
    out[1] = MathFixedDivide(y, length);
    out[2] = MathFixedDivide(z, length);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800311B4);
#endif

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vector3;

#ifdef NON_MATCHING
extern s32 D_800A2F2C;
extern s32 D_800A397C[];
void func_800319D4(u8 *, s32);
void func_8001F198(void);
u16 func_80030F24(u8 *, s32 *, s32, s32, s32);
extern s16 func_8002482Cs16(s32, s32, void *) asm("func_8002482C");
void func_8001F5BC(s32, s32, s32);
void func_80031264(u8 *object) {
    s32 corners[5][4];
    s32 normals[3][4];
    u8 *state;
    u8 *entry;
    s32 length;
    s32 sum;
    s32 sum4;
    s32 result;
    s32 i;
    s32 edgeZ;
    s32 edgeY;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
    s32 crossX;
    s32 crossY;
    s32 crossZ;
    s32 value;

    state = *(u8 **)(object + 0x370);
    if (*(s16 *)(object + 0x1EC) != 0) {
        func_800319D4(object, 0);
        return;
    }
    corners[0][0] = corners[1][0] = corners[2][0] = corners[3][0] =
        corners[4][0] = *(s32 *)(object + 0x0);
    corners[0][1] = corners[1][1] = corners[2][1] = corners[3][1] =
        corners[4][1] = *(s32 *)(object + 0x4);
    corners[0][2] = corners[1][2] = corners[2][2] = corners[3][2] =
        corners[4][2] = *(s32 *)(object + 0x8);
    *(Vector3 *)(object + 0x3C) = *(Vector3 *)(object + 0x18);
    *(Vector3 *)(object + 0x48) = *(Vector3 *)(object + 0x24);
    *(Vector3 *)(object + 0x54) = *(Vector3 *)(object + 0x30);
    func_8001EEC4((s32 *)object);
    func_8001F198();
    *(s16 *)(object + 0x1E2) = 0x7D00;
    *(s16 *)(object + 0x1E4) = -1;
    *(u8 *)(object + 0xF5) = 0;
    D_800A2F2C = *(s32 *)(object + 0x1F8);
    *(s16 *)(object + 0x362) = func_80030F24(
        object, corners[3], *(s16 *)(state + 0x1E), *(s16 *)(state + 0x22), 0);
    *(s16 *)(object + 0x364) = func_80030F24(
        object, corners[0], *(s16 *)(state + 0x1E), *(s16 *)(state + 0x20), 0);
    *(s16 *)(object + 0x366) = func_80030F24(
        object, corners[2], *(s16 *)(state + 0x1C), *(s16 *)(state + 0x22), 0);
    *(s16 *)(object + 0x368) = func_80030F24(
        object, corners[1], *(s16 *)(state + 0x1C), *(s16 *)(state + 0x20), 0);
    *(s16 *)(object + 0x1E0) = func_8002482Cs16(
        *(s32 *)(object + 0x0), *(s32 *)(object + 0x4), object + 0x1F8);
    if (*(u16 *)(object + 0x362) == 0) {
        corners[3][2] = *(s32 *)(object + 0x8);
    }
    if (*(u16 *)(object + 0x364) == 0) {
        corners[0][2] = *(s32 *)(object + 0x8);
    }
    if (*(u16 *)(object + 0x366) == 0) {
        corners[2][2] = *(s32 *)(object + 0x8);
    }
    if (*(u16 *)(object + 0x368) == 0) {
        corners[1][2] = *(s32 *)(object + 0x8);
    }
    *(s32 *)(object + 0x318) = corners[3][2];
    *(s32 *)(object + 0x340) = corners[0][2];
    *(s32 *)(object + 0x2C8) = corners[2][2];
    *(s32 *)(object + 0x2F0) = corners[1][2];
    sum = corners[0][2] + corners[1][2] + corners[2][2] + corners[3][2];
    if (sum < 0) {
        sum += 3;
    }
    sum4 = sum >> 2;
    if ((*(s16 *)(object + 0x1BC) == 0) || (D_800A397C[0] == 2)) {
        corners[0][2] += *(s16 *)(object + 0x324);
        corners[1][2] += *(s16 *)(object + 0x2D4);
        corners[2][2] += *(s16 *)(object + 0x2AC);
        corners[3][2] += *(s16 *)(object + 0x2FC);
        sum = *(s16 *)(object + 0x324) + *(s16 *)(object + 0x2D4) +
              *(s16 *)(object + 0x2AC) + *(s16 *)(object + 0x2FC);
        if (sum < 0) {
            sum += 3;
        }
        result = (u16)(sum >> 2);
    } else {
        i = 0;
        entry = object;
        do {
            i = i + 1;
            *(u16 *)(entry + 0x2AC) = *(u16 *)(object + 0x39A);
            entry = entry + 0x28;
        } while (i < 4);
        result = *(u16 *)(object + 0x39A);
    }
    *(s16 *)(object + 0xFE) = result;
    *(s32 *)(object + 0x8) = *(s16 *)(object + 0xFE) + sum4;
    *(s16 *)(object + 0x1E8) = *(u16 *)(object + 0x1E4);
    *(s16 *)(object + 0x1E6) = *(u16 *)(object + 0x1E2);
    edgeZ = corners[2][2] - corners[1][2];
    a = (corners[0][1] - corners[1][1]) >> 2;
    b = edgeZ >> 2;
    edgeY = corners[2][1] - corners[1][1];
    d = (corners[0][2] - corners[1][2]) >> 2;
    c = edgeY >> 2;
    e = (corners[2][0] - corners[1][0]) >> 2;
    f = (corners[0][0] - corners[1][0]) >> 2;
    crossX = a * b - d * c;
    crossY = d * e - f * b;
    crossZ = f * c - a * e;
    length = MathSqrt(crossX * crossX + crossY * crossY + crossZ * crossZ);
    if (length == 0) {
        length = 1;
    }
    normals[2][0] = MathFixedDivide(crossX, length);
    normals[2][1] = MathFixedDivide(crossY, length);
    normals[2][2] = MathFixedDivide(crossZ, length);
    length = MathSqrt(f * f + a * a + d * d);
    if (length == 0) {
        length = 1;
    }
    normals[0][0] = MathFixedDivide(f, length);
    normals[0][1] = MathFixedDivide(a, length);
    normals[0][2] = MathFixedDivide(d, length);
    length = MathSqrt(e * e + c * c + b * b);
    if (length == 0) {
        length = 1;
    }
    normals[1][0] = MathFixedDivide(e, length);
    normals[1][1] = MathFixedDivide(c, length);
    normals[1][2] = MathFixedDivide(b, length);
    *(s32 *)(object + 0x3C) = normals[0][0];
    *(s32 *)(object + 0x40) = normals[0][1];
    *(s32 *)(object + 0x44) = normals[0][2];
    *(s32 *)(object + 0x48) = normals[1][0];
    *(s32 *)(object + 0x4C) = normals[1][1];
    *(s32 *)(object + 0x50) = normals[1][2];
    *(s32 *)(object + 0x54) = normals[2][0];
    *(s32 *)(object + 0x58) = normals[2][1];
    *(s32 *)(object + 0x5C) = normals[2][2];
    func_8001F5BC(0, (0x3FF - *(s16 *)(object + 0x38A)) & 0x3FF,
                  *(u16 *)(object + 0x388) & 0x3FF);
    func_8001EC38((s32 *)object);
    MatrixCombineState();
    func_8001F8C0((s32 *)object);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80031264);
#endif

#ifdef NON_MATCHING
void OuterProduct0(s32 *, s32 *, s32 *);
void VectorNormal(s32 *, s32 *, s32);
void func_80031874(u8 *quad, s32 *normal) {
    s32 vecA[3];
    s32 vecB[3];
    s32 cross[3];
    s32 crossX;
    s32 crossY;
    s32 crossZ;
    u8 *back;

    if ((quad == NULL) || ((*(u8 *)(quad + 0x13) & 0x20) != 0)) {
        normal[0] = 0;
        normal[1] = 0;
        normal[2] = 0x10000;
        return;
    }
    back = quad + 0x1C;
    vecA[0] = *(s16 *)(*(u8 **)(quad + 0x20) + 0) - *(s16 *)(*(u8 **)back + 0);
    vecA[1] = *(s16 *)(*(u8 **)(quad + 0x20) + 2) - *(s16 *)(*(u8 **)back + 2);
    vecA[2] = *(s16 *)(*(u8 **)(quad + 0x20) + 4) - *(s16 *)(*(u8 **)back + 4);
    vecB[0] = *(s16 *)(*(u8 **)(quad + 0x18) + 0) - *(s16 *)(*(u8 **)back + 0);
    vecB[1] = *(s16 *)(*(u8 **)(quad + 0x18) + 2) - *(s16 *)(*(u8 **)back + 2);
    vecB[2] = *(s16 *)(*(u8 **)(quad + 0x18) + 4) - *(s16 *)(*(u8 **)back + 4);
    OuterProduct0(vecA, vecB, cross);
    crossX = cross[0];
    crossY = cross[1];
    do {
    } while (0);
    crossZ = cross[2];
    cross[0] = crossX >> 6;
    cross[1] = crossY >> 6;
    cross[2] = crossZ >> 6;
    VectorNormal(cross, normal, cross[2]);
    normal[0] = normal[0] * 0x10;
    normal[1] = normal[1] * 0x10;
    normal[2] = normal[2] * 0x10;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80031874);
#endif

#ifdef NON_MATCHING
extern s32 D_800A2F2C;
void func_800319D4(u8 *object, s32 arg1) {
    s32 corners[5][4];
    s32 vecA[3];
    s32 cross[3];
    s32 normalOut[3];
    s32 temp1;
    s32 temp2;
    s32 index;
    s32 sum;
    s32 sum4;
    s32 value;
    u16 result;

    value = *(s32 *)(object + 0x0);
    corners[4][0] = value;
    corners[3][0] = value;
    corners[2][0] = value;
    corners[1][0] = value;
    corners[0][0] = value;
    value = *(s32 *)(object + 0x4);
    corners[4][1] = value;
    corners[3][1] = value;
    corners[2][1] = value;
    corners[1][1] = value;
    corners[0][1] = value;
    value = *(s32 *)(object + 0x8);
    corners[4][2] = value;
    corners[3][2] = value;
    corners[2][2] = value;
    corners[1][2] = value;
    corners[0][2] = value;
    *(Vector3 *)(object + 0x3C) = *(Vector3 *)(object + 0x18);
    *(Vector3 *)(object + 0x48) = *(Vector3 *)(object + 0x24);
    *(Vector3 *)(object + 0x54) = *(Vector3 *)(object + 0x30);
    func_8001EEC4((s32 *)object);
    func_8001F198();
    *(u8 *)(object + 0xF5) = 0;
    *(s16 *)(object + 0x116) = *(s16 *)(object + 0x114) * 4;
    if (arg1 == 0) {
        *(s16 *)(object + 0x1E2) = 0x7D00;
        *(s16 *)(object + 0x1E4) = -1;
        D_800A2F2C = *(s32 *)(object + 0x1F8);
        result = func_80030F24(object, corners[3], 0, 0, 0);
        *(s16 *)(object + 0x362) = result;
        *(s16 *)(object + 0x364) = result;
        *(s16 *)(object + 0x366) = *(u16 *)(object + 0x362);
        *(s16 *)(object + 0x368) = *(u16 *)(object + 0x362);
    }
    vecA[0] = *(s32 *)(object + 0xDC);
    vecA[1] = *(s32 *)(object + 0xE0);
    index = *(s16 *)(object + 0x114) * 4;
    temp1 = (*(s32 *)((u8 *)D_800A3A2C + index) << 8) >> 16;
    temp2 = (*(s32 *)((u8 *)D_800A3A34 + index) << 8) >> 16;
    corners[0][0] = temp1;
    corners[1][1] = temp1;
    corners[0][1] = temp2;
    corners[1][0] = -temp2;
    corners[0][2] = -((vecA[0] * temp1 + vecA[1] * temp2) >> 16);
    corners[1][2] = -((vecA[0] * -temp2 + vecA[1] * temp1) >> 16);
    if (arg1 == 0) {
        corners[0][2] += *(s16 *)(object + 0x324) - *(s16 *)(object + 0x2D4);
        corners[1][2] += *(s16 *)(object + 0x2AC) - *(s16 *)(object + 0x2D4);
        sum = *(s16 *)(object + 0x324) + *(s16 *)(object + 0x2D4) +
              *(s16 *)(object + 0x2AC) + *(s16 *)(object + 0x2FC);
        sum4 = sum / 4;
        *(s16 *)(object + 0x1BE) = sum4;
        *(s32 *)(object + 0x8) = corners[3][2] + (s16)sum4;
        *(s16 *)(object + 0x1E8) = *(u16 *)(object + 0x1E4);
        *(s16 *)(object + 0x1E6) = *(u16 *)(object + 0x1E2);
    } else {
        *(s16 *)(object + 0x1E4) = -1;
        *(s16 *)(object + 0x1E2) = -1;
    }
    OuterProduct0(corners[0], corners[1], cross);
    cross[0] >>= 6;
    cross[1] >>= 6;
    cross[2] >>= 6;
    VectorNormal(cross, normalOut, cross[2]);
    normalOut[0] = normalOut[0] * 16;
    normalOut[1] = normalOut[1] * 16;
    normalOut[2] = normalOut[2] * 16;
    VectorNormal(corners[0], vecA, normalOut[2]);
    VectorNormal(corners[1], cross);
    vecA[0] = vecA[0] * 16;
    vecA[1] = vecA[1] * 16;
    vecA[2] = vecA[2] * 16;
    cross[0] = cross[0] * 16;
    cross[1] = cross[1] * 16;
    cross[2] = cross[2] * 16;
    *(s32 *)(object + 0x3C) = vecA[0];
    *(s32 *)(object + 0x40) = vecA[1];
    *(s32 *)(object + 0x44) = vecA[2];
    *(s32 *)(object + 0x48) = cross[0];
    *(s32 *)(object + 0x4C) = cross[1];
    *(s32 *)(object + 0x50) = cross[2];
    *(s32 *)(object + 0x54) = normalOut[0];
    *(s32 *)(object + 0x58) = normalOut[1];
    *(s32 *)(object + 0x5C) = normalOut[2];
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800319D4);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80031D74);

#ifdef NON_MATCHING
/* w9c: STACK_BLOCK_801C0000 unlock works — the raw lui constant now emits
 * (lui a0/a1,0x801c rows match). Remaining wall: retail allocates TWO
 * s-regs, handle=s1 (first call result) and value=s0 (second call result,
 * captured in the jal delay slot). gcc gives handle=s0 and coalesces the
 * single-use value into v0 (move a1,v0), frame 0x18 vs 0x20. Tried: value
 * declared first, nested call form, value local + plain sequence. No
 * spelling reserved an s-reg for value. Function is otherwise byte-shaped;
 * the -0xc label drift rows (0x2f28, 3c578...) are our own short frame. */
extern s32 func_8003C584(s32, void *);
extern s32 func_8003C8BC(void *, s32, s32);
extern void func_8003C644(s32, s32, s32, s32);
extern void func_8003C63C(s32);
extern void func_80025454(s32);
extern void func_80031D74(s32, s32, s32);
extern char D_8008D08C[];
extern void *D_800A2F34[];
extern s32 D_800A3574[];
extern u8 D_800A2D4C[], D_800A2D4D[];
extern s32 D_800A36D0Absolute[];
void func_80032328(s32 arg0) {
    s32 value;
    s32 handle;

    handle = func_8003C584(arg0, D_800A2F34);
    if (handle == 0) {
        SystemShowFatalError(D_8008D08C);
    }
    func_8003C8BC(handle, 0, 2);
    func_8003C644(STACK_BLOCK_801C0000, func_8003C8BC(handle, 0, 0), 1, handle);
    func_80031D74(D_800A3574[0], STACK_BLOCK_801C0000, -1);
    D_800A2D4C[0] = 1;
    func_80025454(((s32 *)D_800A36D0Absolute)[-87]);
    D_800A2D4D[0] = 0;
    func_8003C63C(handle);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80032328);
#endif

/*
 * The second D_800A3574 read goes through the D_800A36D0Absolute
 * neighbor ((s32 *)0x800A36D0)[-87] so gcc cannot CSE the address
 * materialization across the first call; the -87*4 delta folds into
 * the %lo displacement (0x36D0 - 0x15C = 0x3574).
 */
extern s32 D_800A3574[];
extern s32 D_800B9F44[];
extern u8 D_800A2D4C[], D_800A2D4D[];
extern s32 D_800A36D0Absolute[];
void func_80025454(s32);
void func_80031D74(s32, s32, s32);
void func_800323F0(s32 index, s32 arg1) {
    func_80031D74(D_800A3574[0], *(s32 **)(D_800B9F44 + index), arg1);
    D_800A2D4C[0] = 1;
    func_80025454(((s32 *)D_800A36D0Absolute)[-87]);
    D_800A2D4D[0] = 0;
}

void func_80031D74(s32, s32, s32);
extern s32 D_800A3574[];
extern u8 D_800A2D4C[], D_800A2D4D[];
void func_80032450(s32 first, s32 second) {
    func_80031D74(D_800A3574[0], first, second);
    D_800A2D4C[0] = 1;
    D_800A2D4D[0] = 0;
}

void func_80032494(u8 *object) {
    u8 *node;

    node = *(u8 **)(object + 0x3C);
    if (node != NULL) {
        *(s32 *)(object + 0x34) = 0;
        do {
            if (*(s32 *)(node + 0x8) != 0) {
                *(s32 *)(*(s32 *)(node + 0xC) + 0x28) = *(s32 *)(object + 0x34);
                *(s32 *)(object + 0x34) = *(s32 *)(node + 0x8);
            }
            node = *(u8 **)(node + 0x4);
        } while (node != NULL);
    }
}

void GraphicsLinkPrimitive(u32 *orderingTable, u32 *primitive) {
    u32 old;
    u32 tag;
    old = *orderingTable;
    tag = *primitive;
    tag &= 0xFF000000;
    tag |= old & 0xFFFFFF;
    *primitive = tag;
    *orderingTable = (old & 0xFF000000) | ((u32)primitive & 0xFFFFFF);
}

void GraphicsAddTaggedPrimitive(u32 *orderingTable, u32 *primitive, u32 tag) {
    *primitive = tag | *orderingTable;
    *orderingTable = (u32)primitive & 0xFFFFFF;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80032544);

INCLUDE_ASM("asm/nonmatchings/game", func_8003271C);

INCLUDE_ASM("asm/nonmatchings/game", func_80032760);

INCLUDE_ASM("asm/nonmatchings/game", func_800328AC);

#ifdef NON_MATCHING
/*
 * Wall: retail has a dead 8-byte leaf frame (addiu sp,-8 scheduled into
 * the first bne delay slot, nothing saved) plus a loop counter kept
 * without sign extension (s32 semantics). An s16 counter forces the
 * frame on some shapes (func_80063770) but here adds sll/sra per
 * iteration; an s32 counter compiles frameless. Also: while this draft
 * was ACTIVE and 8 bytes long, sdata shifted +8 and every data symbol
 * (D_800A2CF8 -> 0x800A2D00) read wrong — check data-symbol values in
 * the map before debugging a load offset.
 */
extern s32 D_800A2CF8[];
s32 func_80032A90(u8 *arg0) {
    u8 *entry;
    s32 i;

    if (D_800A2CF8[0] == 2) {
        return 1;
    }
    entry = arg0 + 0x54;
    i = 0;
    do {
        if (*(s16 *)(entry + 4) < 0x9B) {
            return 1;
        }
        i = i + 1;
        entry = entry + 0x14;
    } while (i < 4);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80032A90);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80032AE4);

void func_80032D94(s8 *object) {
    if ((u8)object[0x12] == 4) {
        if (object[2] == 3)
            object[0] = 2;
        else
            object[0] = 1;
    } else {
        if (object[2] == 3)
            object[0] = 3;
        else
            object[0] = 0;
    }
}

extern s32 func_800337EC(void);
extern u32 gPrimitiveCursor[];
extern s32 D_800A39C8[];
extern u32 D_800B022C[];
extern s16 D_800AFE2C[];
extern s32 D_800A2F38NM asm("D_800A2F38.NON_MATCHING");

void func_80032DEC(u8 *arg0, s32 arg1) {
    register s32 *vec0 asm("a3");
    register s32 *vec1 asm("t0");
    register s32 *vec2 asm("t1");
    register s32 w4 asm("v1");
    register s32 w8 asm("a0");
    register s32 wC asm("v0");
    register s32 n0 asm("v1");
    register s32 n1 asm("a0");
    register s32 old asm("a0");
    register s32 tmpa1 asm("a1");
    register s32 sh asm("v1");
    register s32 base asm("v0");
    register u8 *obj asm("s0");
    register u8 *prim18 asm("s1");
    register u8 *prim asm("s2");
    register s32 otz asm("s3");
    register s32 count asm("s4");
    register u32 *objCursor asm("s5");
    register s32 entryCount asm("s6");
    register s16 *zCursor asm("s7");
    register u8 *otBase40;
    register s32 shifted asm("v0");
    register s32 aligned asm("v0");
    register s32 mask asm("a0");
    register s32 diff asm("v1");
    register s32 guard asm("a2");
    register s32 oldEnd asm("v0");
    s32 *normal;
    s32 w10;
    s32 w14;

    obj = arg0;
    old = D_800A2F38NM;
    asm("addu %0, %1, $zero" : "=r"(count) : "r"(arg1));
    guard = count;
    count = count - 1;
    prim = (u8 *)gPrimitiveCursor[0];
    tmpa1 = (s32)D_800A39C8[0];
    otBase40 = (u8 *)tmpa1 + 0x40;
    base = (s32)D_800B022C;
    sh = old * 4;
    objCursor = (u32 *)(sh + base);
    sh = old * 2;
    base = (s32)D_800AFE2C;
    zCursor = (s16 *)(sh + base);
    entryCount = old;
    if (guard > 0) {
        prim18 = prim + 0x18;
        do {
            vec0 = *(s32 **)(obj + 0x18);
            vec1 = *(s32 **)(obj + 0x1C);
            vec2 = *(s32 **)(obj + 0x20);
            asm volatile("lwc2 $0, 0x0(%0)\n\t"
                         "lwc2 $1, 0x4(%0)\n\t"
                         "lwc2 $2, 0x0(%1)\n\t"
                         "lwc2 $3, 0x4(%1)\n\t"
                         "lwc2 $4, 0x0(%2)\n\t"
                         "lwc2 $5, 0x4(%2)"
                         :
                         : "r"(vec0), "r"(vec1), "r"(vec2));
            w4 = *(s32 *)(obj + 0x4);
            w8 = *(s32 *)(obj + 0x8);
            asm volatile("rtpt");
            wC = *(s32 *)(obj + 0xC);
            w10 = *(s32 *)(obj + 0x10);
            w14 = *(s32 *)(obj + 0x14);
            *(s32 *)(prim18 - 0xC) = w8;
            *(s32 *)(prim18 - 0x14) = w4;
            *(s32 *)(prim18 - 4) = wC;
            asm volatile("swc2 $12, 0x0(%0)\n\t"
                         "swc2 $13, 0x0(%1)\n\t"
                         "swc2 $14, 0x0(%2)"
                         :
                         : "r"(prim + 8), "r"(prim + 0x10), "r"(prim + 0x20));
            normal = *(s32 **)(obj + 0x24);
            n0 = normal[0];
            n1 = normal[1];
            asm volatile("avsz3");
            *(s32 *)(prim18 + 4) = w10;
            *(s32 *)(prim18 + 0xC) = w14;
            asm volatile("mfc2 %0, $7" : "=r"(otz));
            asm volatile("mtc2 %0, $0\n\tmtc2 %1, $1" : : "r"(n0), "r"(n1));
            if (otz < 0x9B) {
                asm volatile("rtps");
                if (func_800337EC() != 0 && entryCount < 0x1FF) {
                    otz = otz + *(s8 *)(obj + 1);
                    if (otz >= 0) {
                        entryCount = entryCount + 1;
                        *objCursor = (u32)obj;
                        objCursor = objCursor + 1;
                        shifted = otz << 2;
                        *zCursor = shifted;
                        zCursor = zCursor + 1;
                    }
                    goto nextObj;
                }
            }
            asm volatile("rtps");
            tmpa1 = *(s8 *)(obj + 1);
            aligned = (otz >> 2) << 2;
            aligned = aligned + (s32)otBase40;
            mask = 0xFF0000;
            tmpa1 = tmpa1 * 4 + aligned;
            *(u32 *)prim = *(u32 *)tmpa1 | 0x09000000;
            mask = mask | 0xFFFF;
            *(u32 *)tmpa1 = (u32)prim & mask;
            asm volatile("swc2 $14, 0x0(%0)" : : "r"(prim18));
            prim18 = prim18 + 0x28;
            prim = prim + 0x28;
        nextObj:
            obj = *(u8 **)(obj + 0x28);
        } while (count-- > 0);
    }
    gPrimitiveCursor[0] = (u32)prim;
    oldEnd = D_800A2F38NM;
    diff = (s32)objCursor - (s32)D_800B022C;
    diff = diff - oldEnd * 4;
    D_800A2F38NM = oldEnd + (diff >> 2);
}

INCLUDE_ASM("asm/nonmatchings/game", func_80033000);

void func_80033704(s16 *out) {
    register s32 v1 asm("v1");
    register s32 a2 asm("a2");
    register s32 test asm("v0");
    s32 a3;
    s32 a1;
    s32 neg;

    asm volatile("mfc2 %0, $9" : "=r"(v1));
    asm volatile("mfc2 %0, $10" : "=r"(a3));
    asm volatile("mfc2 %0, $11" : "=r"(a2));
    out[0] = v1;
    out[1] = a3;
    out[2] = a2;
    if (a2 < 0) {
        asm("");
        a2 = 0;
    }
    asm(".L80033724:");
    a1 = 4;
    if (a2 >= v1) {
        asm("subu %0, $0, %1" : "=r"(neg) : "r"(v1));
        a1 = (a2 < neg) << 1;
    }
    if (a2 < a3) {
        a1 |= 1;
    } else if (a2 < -a3) {
        a1 |= 8;
    }
    if (a2 < 0x1F4) {
        a1 |= 0x100;
        test = a2 < 5;
        if (test) {
            a1 |= 0x1F;
        }
    }
    out[3] = a1;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80033780);

void func_80033788(u8 *arg0) {
    register u32 depth asm("$6");

    /* Retail reads GTE IR3 (SZ average) and stores SXY2 for one vertex. */
    asm("mfc2 %0, $11" : "=r"(depth));
    asm("swc2 $14, 0x14($a0)");
    depth >>= 2;
    *(u16 *)(arg0 + 6) = depth;
}

void func_8003379C(u8 *arg0, u8 *arg1, u8 *arg2) {
    register u32 depthA asm("$3");
    register u32 depthB asm("$2");

    /* Retail stores SXY0/1/2 and SZ1/2/3 >> 2 for three vertices after
     * a RotTransPers3; the depth registers rotate v1/v0/v1. */
    asm volatile("mfc2 %0, $17" : "=r"(depthA));
    asm("swc2 $12, 0x14($a0)");
    depthA >>= 2;
    *(u16 *)(arg0 + 6) = depthA;

    asm volatile("mfc2 %0, $18" : "=r"(depthB));
    asm("swc2 $13, 0x14($a1)");
    depthB >>= 2;
    *(u16 *)(arg1 + 6) = depthB;

    asm volatile("mfc2 %0, $19" : "=r"(depthA));
    asm("swc2 $14, 0x14($a2)");
    depthA >>= 2;
    *(u16 *)(arg2 + 6) = depthA;
}

#ifdef NON_MATCHING
/*
 * Every DI-multiply spelling expands mfhi before mflo; retail is
 * mflo-first (mult, mflo, mfhi). Operand swap flips mult to a1,a0
 * without changing the mf order. Two separate s32/DI expressions are
 * not CSEd into one mult.
 */
s32 MathMultiplyFixed16(s32 arg0, s32 arg1) {
    return (s32)(((unsigned long long)arg0 * arg1) >> 16);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", MathMultiplyFixed16);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_800337EC);

void func_8003382C(s16 *out) {
    register s32 v1 asm("v1");
    register s32 a2 asm("a2");
    register s32 test asm("v0");
    s32 a3;
    s32 a1;
    s32 neg;

    asm volatile("mfc2 %0, $9\n\t"
                 "mfc2 %1, $10\n\t"
                 "mfc2 %2, $11\n\tnop\n\t"
                 "bgez %2, func_80033704+0x20"
                 : "=r"(v1), "=r"(a3), "=r"(a2));
    asm("addu %0, $0, $0" : "=r"(a2));
    a1 = 4;
    if (a2 >= v1) {
        asm("subu %0, $0, %1" : "=r"(neg) : "r"(v1));
        a1 = (a2 < neg) << 1;
    }
    if (a2 < a3) {
        a1 |= 1;
    } else if (a2 < -a3) {
        a1 |= 8;
    }
    if (a2 < 0x1F4) {
        a1 |= 0x100;
        test = a2 < 5;
        if (test) {
            a1 |= 0x10;
        }
    }
    out[3] = a1;
}

void func_800338A4(s32 *dst, s32 *src) {
    s32 a, b, c, d, e, f;
    a = src[0];
    b = src[1];
    c = src[2];
    d = src[3];
    e = src[4];
    f = src[5];
    dst[0] = a;
    dst[1] = b;
    dst[3] = c;
    dst[5] = d;
    dst[7] = e;
    dst[9] = f;
}

s32 func_800338D8(u16 *object) {
    u32 flags;
    flags = object[3];
    flags &= object[13];
    flags &= object[23];
    flags &= object[33];
    return (flags & 0x7EFF) == 0;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80033900);

INCLUDE_ASM("asm/nonmatchings/game", func_800342D8);

extern MATRIX D_800A4568[];
extern MATRIX D_800A4588[];

void func_800345E0(void) {
    register s32 reg0 asm("$12");
    register s32 reg1 asm("$13");
    register s32 reg2 asm("$14");
    register s32 *p asm("$8");
    s16 *base;
    s16 *row;
    s16 *p16;
    s32 *tp;
    s32 i;
    s32 j;

    asm("" : "=r"(p) : "0"((s32 *)D_800A4568));
    asm("cfc2 %0, $0"
        "\n\tcfc2 %1, $1"
        : "=r"(reg0), "=r"(reg1));
    p[0] = reg0;
    p[1] = reg1;
    asm("cfc2 %0, $2"
        "\n\tcfc2 %1, $3"
        "\n\tcfc2 %2, $4"
        : "=r"(reg0), "=r"(reg1), "=r"(reg2));
    p[2] = reg0;
    p[3] = reg1;
    p[4] = reg2;
    asm("cfc2 %0, $5"
        "\n\tcfc2 %1, $6"
        "\n\tcfc2 %2, $7"
        : "=r"(reg0), "=r"(reg1), "=r"(reg2));
    p[5] = reg0;
    p[6] = reg1;
    p[7] = reg2;
    asm("" : "=r"(p) : "0"((s32 *)D_800A4588));
    asm("cfc2 %0, $0"
        "\n\tcfc2 %1, $1"
        : "=r"(reg0), "=r"(reg1));
    p[0] = reg0;
    p[1] = reg1;
    asm("cfc2 %0, $2"
        "\n\tcfc2 %1, $3"
        "\n\tcfc2 %2, $4"
        : "=r"(reg0), "=r"(reg1), "=r"(reg2));
    p[2] = reg0;
    p[3] = reg1;
    p[4] = reg2;
    asm("cfc2 %0, $5"
        "\n\tcfc2 %1, $6"
        "\n\tcfc2 %2, $7"
        : "=r"(reg0), "=r"(reg1), "=r"(reg2));
    p[5] = reg0;
    p[6] = reg1;
    p[7] = reg2;
    asm("");
    i = 0;
    base = D_800A4588->m[0];
    tp = (s32 *)&base[10];
    row = base;
    do {
        j = 0;
        p16 = row;
        do {
            *p16 *= 4;
            p16 += 1;
            j += 1;
        } while (j < 3);
        row += 3;
        *tp *= 4;
        tp += 1;
        i += 1;
    } while (i < 3);
}

extern u32 gPrimitiveCursor[];
extern s32 D_800A36D0Absolute[];
extern s32 D_800A3668Absolute[];
extern s32 D_800A2F38[];
extern s32 D_800A3640[];
extern s16 D_800AFE2C[];
extern u32 D_800B022C[];
extern MATRIX D_800A4588[];
extern MATRIX D_800A4568[];

s32 func_800346D0(s32 threshold) {
    s32 i;
    u32 ret;

    if (D_800A2CF8[0] == 3) {
        return 0;
    }
    PushMatrix();
    SetRotMatrix(D_800A4588);
    SetTransMatrix(D_800A4588);
    for (i = 0; i < D_800A2F38[0]; i++) {
        D_800A3640[0] = D_800AFE2C[i];
        ret = func_800342D8(&D_800B022C[i], gPrimitiveCursor[0]);
        ((u32 *)D_800A36D0Absolute)[-67] = ret;
        if (threshold < (s32)(((ret & 0xFFFFFFF) -
                               (((u32 *)D_800A3668Absolute)[-62] & 0xFFFFFFF)) /
                              40)) {
            D_800A2F38[0] = i;
        }
    }
    if (D_800A2CF8[0] < 2) {
        SetRotMatrix(D_800A4568);
        SetTransMatrix(D_800A4568);
        func_80034834();
    }
    PopMatrix();
    return D_800A2F38[0];
}

INCLUDE_ASM("asm/nonmatchings/game", func_80034834);

#ifdef NON_MATCHING
/*
 * WALL (w9d): this draft is byte-exact except for ONE addressing fact:
 * retail reads D_800A38C0 with `lhu %gp_rel(D_800A38C0)($gp)` here, but
 * func_80013224 STORES the same symbol absolute (lui/sw). Declaring
 * D_800A38C0 scalar for the gp read flips func_80013224's store to
 * gp-rel (-4 bytes, whole-EXE shift; the w8b wall). Needs the Makefile
 * defsym alias D_800A38C0Small=D_800A38C0 and an `extern u16
 * D_800A38C0Small;` here -- then this draft should drop in unmodified.
 * Everything else was verified clean by asm-differ: prologue (li s4,
 * 0xA7 / li s3, 0xFD hoisted before the IV init), both FT4 loops (for +
 * (i+1)<<7-1 CSE), and the F4 tail as a do-while with the f4 += 0x18
 * before the test (it lands in the bnez delay slot). cursor = base +
 * car * 0x28 is REQUIRED: spelling the 0xA0 stride as a separate `off`
 * local puts move s5,zero before the li constants and breaks the
 * prologue order.
 */
extern u16 D_800A38C0;
extern u8 *D_800A3850;
extern u8 *D_800A390C;
extern u8 D_800AFBB8[];
extern u8 D_800AFB18[];
extern u8 D_800B1F30[];

void func_80034990(void) {
    u16 color;
    s32 car;
    s32 i;
    u8 *cursor;
    POLY_FT4 *prim;
    POLY_F4 *f4;
    s32 red;
    s32 green;
    s32 blue;

    D_800A3850 = D_800AFBB8;
    color = D_800A38C0;
    for (car = 0; car < 0xC; car += 4) {
        cursor = D_800AFB18 + car * 0x28;
        for (i = 0; i < 2; i++) {
            prim = (POLY_FT4 *)(cursor + i * 0x28);
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            prim->tpage = GetTPage(1, 0, 0x200, 0x100);
            prim->clut = GetClut(0x200, 0x1FF);
            prim->u0 = i << 7;
            prim->v0 = 0xA7;
            prim->u1 = ((i + 1) << 7) - 1;
            prim->v1 = 0xA7;
            prim->u2 = i << 7;
            prim->v2 = 0xFD;
            prim->u3 = ((i + 1) << 7) - 1;
            prim->v3 = 0xFD;
        }
        for (i = 0; i < 2; i++) {
            prim = (POLY_FT4 *)(cursor + 0x50 + i * 0x28);
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            prim->tpage = GetTPage(1, 0, 0x280, 0x100);
            prim->clut = GetClut(0x200, 0x1FF);
            prim->u0 = i << 7;
            prim->v0 = 0xA7;
            prim->u1 = ((i + 1) << 7) - 1;
            prim->v1 = 0xA7;
            prim->u2 = i << 7;
            prim->v2 = 0xFD;
            prim->u3 = ((i + 1) << 7) - 1;
            prim->v3 = 0xFD;
        }
    }
    red = (color & 0x7C00) >> 7;
    green = (color & 0x3E0) >> 2;
    blue = (color & 0x1F) << 3;
    D_800A390C = D_800B1F30;
    i = 0;
    f4 = (POLY_F4 *)(D_800B1F30 - 0x60);
    do {
        SetPolyF4(f4);
        f4->r0 = blue;
        f4->g0 = green;
        f4->b0 = red;
        i++;
        f4 += 0x18;
    } while (i < 8);
}
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80034990);

typedef struct {
    s32 words[10];
} Primitive40;

#ifdef NON_MATCHING
/*
 * WALL: retail loads gPrimitiveCursor[0] into the expression temp v0
 * and then copies it to entry's home (`move t0,v0; move a3,t0`); gcc
 * 2.7.2 binds the load directly into entry's home register (t0) and
 * drops one move, leaving the function 4 bytes short. Tried: volatile
 * read (breaks the whole schedule, +materialization), double read
 * (cse.c still binds the load to entry's home), statement reordering.
 * The rest of the shape below is exact: the do-while 0x10 row struct
 * copy, the asm("")-split 8-byte tail, and the neighbor-symbol store
 * D_800A36D0Absolute[-67] (folds %lo back to 0x35c4) that defeats the
 * load/store address CSE.
 */
typedef struct {
    s32 words[4];
} Primitive10;

extern u32 gPrimitiveCursor[];
extern s32 D_800A39C8[];
extern s32 D_800A36D0Absolute[];
void func_80034B90(u8 *prim) {
    u8 *entry;
    u8 *dst;
    u8 *end;
    s32 tailA;
    s32 tailB;

    entry = (u8 *)gPrimitiveCursor[0];
    end = prim + 0x20;
    dst = entry;
    ((s32 *)D_800A36D0Absolute)[-67] = gPrimitiveCursor[0] + 0x28;
    do {
        *(Primitive10 *)dst = *(Primitive10 *)prim;
        prim += 0x10;
        dst += 0x10;
    } while (prim != end);
    tailA = *(s32 *)prim;
    tailB = *(s32 *)(prim + 4);
    asm("");
    *(s32 *)dst = tailA;
    *(s32 *)(dst + 4) = tailB;
    AddPrim((u8 *)D_800A39C8[0] - 8, entry);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80034B90);
#endif

extern s32 D_800A36D0Absolute[];
extern s32 D_800A3784Absolute[], D_800A3790Absolute[], D_800A3794Absolute[];
extern s32 D_800A3798Absolute[], D_800A379CAbsolute[], D_800A37A4Absolute[];
extern s32 D_800A37ACAbsolute[], D_800A37B4Absolute[], D_800A37C4Absolute[];

void func_80034C1C(void) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = ((s32 *)D_800A36D0Absolute)[-8];
    b = ((s32 *)D_800A36D0Absolute)[-6];
    c = ((s32 *)D_800A36D0Absolute)[-2];
    d = D_800A36D0Absolute[0];
    D_800A3794Absolute[0] = 0;
    D_800A37A4Absolute[0] = 0;
    D_800A37ACAbsolute[0] = 0;
    D_800A37B4Absolute[0] = 0;
    D_800A37C4Absolute[0] = 0x10000;
    D_800A3784Absolute[0] = a;
    D_800A3790Absolute[0] = b;
    D_800A3798Absolute[0] = -c;
    D_800A379CAbsolute[0] = d;
}

extern s32 D_800A36D0Absolute[];
extern s32 D_800A36D4Absolute[];
extern s32 D_800A3784Absolute[], D_800A3790Absolute[], D_800A3794Absolute[],
    D_800A3798Absolute[], D_800A379CAbsolute[], D_800A37A4Absolute[],
    D_800A37ACAbsolute[], D_800A37B4Absolute[], D_800A37C4Absolute[];
void func_80034C94(void) {
    D_800A3784Absolute[0] = 0x10000;
    D_800A3790Absolute[0] = 0;
    D_800A3794Absolute[0] = 0;
    D_800A3798Absolute[0] = 0;
    D_800A37ACAbsolute[0] = 0;
    D_800A379CAbsolute[0] = D_800A36D0Absolute[0];
    D_800A37A4Absolute[0] = D_800A36D4Absolute[0];
    D_800A37B4Absolute[0] = -D_800A36D4Absolute[0];
    D_800A37C4Absolute[0] = D_800A36D0Absolute[0];
}

extern s32 D_800A36C0Absolute[];
extern s32 D_800A36E8Absolute[];
extern s32 D_800A3790Absolute[], D_800A3798Absolute[], D_800A379CAbsolute[],
    D_800A37A4Absolute[], D_800A37B4Absolute[], D_800A3794Absolute[],
    D_800A3784Absolute[], D_800A37ACAbsolute[], D_800A37C4Absolute[];
void func_80034CFC(void) {
    D_800A3790Absolute[0] = 0;
    D_800A3798Absolute[0] = 0;
    D_800A379CAbsolute[0] = 0x10000;
    D_800A37A4Absolute[0] = 0;
    D_800A37B4Absolute[0] = 0;
    D_800A3784Absolute[0] = D_800A36E8Absolute[0];
    D_800A3794Absolute[0] = D_800A36C0Absolute[0];
    D_800A37ACAbsolute[0] = -D_800A36C0Absolute[0];
    D_800A37C4Absolute[0] = D_800A36E8Absolute[0];
}

#ifdef NON_MATCHING
void func_80034C1C(void) {
    D_800A3794[0] = 0;
    D_800A37A4[0] = 0;
    D_800A37AC[0] = 0;
    D_800A37B4[0] = 0;
    D_800A37C4[0] = 0x10000;
    D_800A3784[0] = D_800A36B0;
    D_800A3790[0] = D_800A36B8;
    D_800A3798[0] = -D_800A36C8;
    D_800A379C[0] = D_800A36D0;
}
#else
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80034D64);

INCLUDE_ASM("asm/nonmatchings/game", func_80035274);

extern u8 *D_800A3554[];
extern void *D_800A2EA0[];
void func_80035274(void);
void func_8003565C(s32 arg0) {
    u8 *value;

    if (arg0 == 0) {
        value = D_800A3554[0];
    } else {
        value = *(u8 **)(D_800A3554[0] + 0x3E0);
    }
    D_800A2EA0[0] = (void *)value;
    func_80035274();
}

typedef struct {
    u8 pad[0x3E0];
    void *unk3E0;
} Data3554;

extern u8 *D_800A3554[];
extern void *D_800A2EA0[];
extern s32 D_800A2F3C[];
void func_80034D64(void);
void func_80035274(void);

void func_800356A8(s32 arg0) {
    void *value0;

    D_800A2F3C[0] = 0x3C;
    func_80034D64();
    if (arg0 == 0) {
        value0 = D_800A3554[0];
    } else {
        value0 = ((Data3554 *)D_800A3554[0])->unk3E0;
    }
    D_800A2EA0[0] = value0;
    func_80035274();
    D_800A2F3C[0] = 0x46;
}

#ifdef NON_MATCHING
/*
 * WALL (w9d): clean except the LINE_F4 tail's first li. Retail emits
 * `li v1,0xc8` immediately after the line pointer addu, keeps 0xC8 in
 * v1 across the y/r/g/b constant stores (li v0,0x23 / 0x46 / 0x28 /
 * 0x6a / 0x2), and sinks both x stores (sh v1,8 / sh v1,0x10) to just
 * before AddPrim. Every C spelling tried puts the x stores early in v0
 * (x-first: li v0 then sh v0,8/0x10 at once), or materializes 0xC8 late
 * (y-first, lx-local, chained x0=x2=0xC8 all start with li v0,0x23).
 * Suspect scheduler v0/v1 lifetime choice. The rest is byte-exact:
 * the /2 then /64 rounding chain, the FT4 loop (y++ at body top, clamp
 * y>=8 resets off then y, nx = x + 0x40 computed into v0 then
 * move s0,v0, off IV += 0x28 after the x update), `c`/`nx` locals are
 * load-bearing for the s4/s5 register pair.
 */
extern s32 D_800A2F44;
extern u8 *D_800A3850;
extern u8 *D_800A390C;

void func_80035720(u_long *ot) {
    s32 value;
    s32 x;
    s32 y;
    s32 off;
    s32 i;
    s32 c;
    s32 nx;
    s32 lx;
    POLY_FT4 *prim;
    LINE_F4 *line;
    s32 bank;

    value = D_800A2F44;
    x = (0x200 - value) / 2;
    y = x / 64;
    x = y * 64 - x;
    i = 0;
    c = 0x23;
    off = y * 40;
    for (; i < 5; i++) {
        if (y >= 8) {
            off = 0;
            y = 0;
        }
        prim = (POLY_FT4 *)(D_800A3850 + off);
        y++;
        prim->x0 = x;
        prim->x2 = x;
        nx = x + 0x40;
        x = nx;
        off += 0x28;
        prim->y0 = 0;
        prim->x1 = nx;
        prim->y1 = 0;
        prim->y2 = c;
        prim->x3 = nx;
        prim->y3 = c;
        AddPrim(ot + 0x3FF, prim);
    }
    bank = gOrderingTableBankAbsolute[0];
    line = (LINE_F4 *)(D_800A390C + bank * 24);
    lx = 0xC8;
    line->y0 = 0x23;
    line->y1 = 0x23;
    line->y2 = 0x46;
    line->y3 = 0x46;
    line->x0 = lx;
    line->x1 = 0;
    line->x2 = lx;
    line->x3 = 0;
    line->r0 = 0x28;
    line->g0 = 0x6A;
    line->b0 = 2;
    AddPrim(ot + 0x3FF, line);
}
#endif

extern s32 D_800A2F44;
extern u8 *D_800A3850;
extern u8 *D_800A390C;

void func_80035720(u_long *ot) {
    s32 value;
    s32 x;
    s32 y;
    s32 off;
    s32 i;
    register s32 c asm("s5");
    s32 nx;
    register s32 lx asm("v1");
    s32 bc;
    u_long *arg;
    POLY_FT4 *prim;
    LINE_F4 *line;
    s32 bank;

    value = D_800A2F44;
    x = (0x200 - value) / 2;
    y = x / 64;
    x = y * 64 - x;
    i = 0;
    c = 0x23;
    off = y * 40;
    for (; i < 5; i++) {
        if (y >= 8) {
            off = 0;
            y = 0;
        }
        prim = (POLY_FT4 *)(D_800A3850 + off);
        y++;
        prim->x0 = x;
        prim->x2 = x;
        nx = x + 0x40;
        x = nx;
        off += 0x28;
        prim->y0 = 0;
        prim->x1 = nx;
        prim->y1 = 0;
        prim->y2 = c;
        prim->x3 = nx;
        prim->y3 = c;
        AddPrim(ot + 0x3FF, prim);
    }
    bank = gOrderingTableBankAbsolute[0];
    arg = ot + 0x3FF;
    line = (LINE_F4 *)(D_800A390C + bank * 24);
    lx = 0xC8;
    asm volatile("" : : "r"(lx));
    line->y0 = 0x23;
    line->y1 = 0x23;
    line->y2 = 0x46;
    line->y3 = 0x46;
    line->r0 = 0x28;
    line->g0 = 0x6A;
    bc = 2;
    line->x0 = lx;
    line->x1 = 0;
    line->x2 = lx;
    line->x3 = 0;
    line->b0 = bc;
    AddPrim(arg, line);
}

extern u8 D_800A2DE1[];
extern s32 D_800A2E9C[];
extern s32 D_800A2E24Absolute[];
void func_8002F0A8(u8 *);
void func_80034D64(void);
void func_80035720(u_long *);
void func_8003587C(s32 arg0) {
    /* second stores to each symbol go through existing defsym
     * neighbors so gcc re-materializes lui/at instead of hoisting the
     * addresses into callee-saved registers:
     *   D_800A2E24-0x43 = 0x2DE1, D_800A2E24+70*4 = 0x2F3C */
    D_800A2DE1[0] = 1;
    func_8002F0A8(D_800A2E9C[0]);
    ((u8 *)D_800A2E24Absolute)[-0x43] = 0;
    D_800A2F3C[0] = 0x23;
    func_80034D64();
    func_80035720(arg0);
    ((s32 *)D_800A2E24Absolute)[70] = 0x82;
}

INCLUDE_ASM("asm/nonmatchings/game", func_800358EC);

INCLUDE_ASM("asm/nonmatchings/game", func_80035B20);

void func_80035E8C(s32 *src, s32 *outX, s32 *outY) {
    s32 value;

    value = MathFixedDivide(src[0], src[2]);
    outX[0] = (MathMultiplyFixed16(value & -0x10, 0xD00000) >> 16) + 0xA0;
    value = MathFixedDivide(src[1], src[2]);
    outY[0] =
        (MathMultiplyFixed16(value & -0x10, 0xD00000) >> 16) + D_800A2F3C[0];
}

INCLUDE_ASM("asm/nonmatchings/game", func_80035F28);

INCLUDE_ASM("asm/nonmatchings/game", func_80036264);

#ifdef NON_MATCHING
extern s32 D_800B60E8[];
void func_8003644C(s32 index, s32 arg1, s32 arg2, s32 arg3) {
    u8 *entry;
    s32 i;
    s32 flag;
    s32 longValue;
    s32 shortValue;

    i = 0;
    flag = (index < 2);
    longValue = 0x19;
    shortValue = 0xA;
    entry = (u8 *)D_800B60E8 + index * 0x12C0;
    for (i = 0; i < 0x18; i++) {
        if (*(s16 *)(entry + 0) == 0) {
            *(s32 *)(entry - 0x18) = arg1;
            *(s32 *)(entry - 0x14) = arg2;
            *(s32 *)(entry - 0x10) = arg3;
            if (flag == 0) {
                *(s16 *)(entry + 0) = longValue;
            } else {
                *(s16 *)(entry + 0) = shortValue;
            }
            return;
        }
        entry = entry + 0xC8;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003644C);
#endif

extern s32 D_800AEE50[];
extern s32 D_800B60C8[];
void func_800364C4(void) {
    s32 i;
    s32 offset;
    u8 *dst;
    u8 *src;

    for (i = 0, dst = (u8 *)D_800AEE50, offset = 0, src = (u8 *)D_800B60C8;
         i < 0x48; offset += 0x28, i++, src += 0xC8) {
        *(Primitive40 *)(offset + (u32)dst) = *(Primitive40 *)src;
    }
}

extern s32 D_800AEE50[];
extern s32 D_800B60C8[];
void func_80036540(void) {
    s32 i;

    for (i = 0; i < 0x48; i++) {
        *(Primitive40 *)((u8 *)D_800B60C8 + i * 0xC8) =
            *(Primitive40 *)((u8 *)D_800AEE50 + i * 0x28);
    }
}

#ifdef NON_MATCHING
extern s32 D_800B7398[];
void func_800365B8(s32 *out) {
    s32 i;
    s32 count;
    u8 *entry;
    s32 value;
    s32 temp;

    count = 0;
    entry = (u8 *)D_800B7398;
    for (i = 0; i < 0x18; i++, entry += 0xC8) {
        if (*(s16 *)((u32)entry + 0x10) == 0) {
            continue;
        }
        value = *out;
        value = (value & -0x800) | ((*(s32 *)((u32)entry - 8) >> 7) & 0x7FF);
        *out = value;
        value = (value & 0xFFC007FF) |
                (((*(s32 *)((u32)entry - 4) >> 7) & 0x7FF) << 11);
        *out = value;
        temp = *(s32 *)entry;
        value = (value & 0x3FFFFF) | ((temp / 16) << 22);
        *out = value;
        out = out + 1;
        count = count + 1;
        if (count >= 0x14) {
            return;
        }
    }
    *out = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800365B8);
#endif

extern u8 D_800B7388Base[] asm("D_800B7388.NON_MATCHING");
extern u8 D_800B60C8Base[] asm("D_800B60C8.NON_MATCHING");
extern s32 D_800A2ED4[];

void func_8003667C(u32 *list) {
    u8 *p;
    register s32 i asm("s1");
    s32 tmp;
    s32 flag;
    s32 v;

    p = D_800B7388Base;
    i = 0;
    for (; i < 0x14; i++, list++) {
        if (*list == 0) {
            while (i < 0x18) {
                *(s16 *)(p + 0x20) = 0;
                i++;
                p += 0xC8;
            }
            p = D_800B60C8Base;
            i = 0x17;
            do {
                *(s16 *)(p + 0x20) = 0;
                p += 0xC8;
                i--;
            } while (i >= 0);
            return;
        }
        flag = D_800A2ED4[0];
        *(s16 *)(p + 0x20) = 5;
        if (flag == 0) {
            extern u32 RandomGetScaled16(s32);
            tmp = (*list & 0x7FF) << 7;
            if ((s32)RandomGetScaled16(0x20) < 0) {
                v = tmp - RandomGetScaled16(0x20);
            } else {
                v = tmp + RandomGetScaled16(0x20);
            }
            *(s32 *)(p + 8) = v;
            tmp = ((*list >> 11) & 0x7FF) << 7;
            if ((s32)RandomGetScaled16(0x20) < 0) {
                v = tmp - RandomGetScaled16(0x20);
            } else {
                v = tmp + RandomGetScaled16(0x20);
            }
            *(s32 *)(p + 0xC) = v;
            *(s32 *)(p + 0x10) =
                ((s32)*list >> 22) * 0x10 + RandomGetScaled16(8);
        }
        p += 0xC8;
    }
}

#ifdef NON_MATCHING
extern s32 D_800A2F54;
extern s32 D_800AE154[];
extern s32 D_800B60A4[];
extern s32 D_800B1EA8[];
extern char D_8008D0AC[];
extern char D_8008D0CC[];
void *func_8003C584(void);
s32 func_8003C8BC(void *, s32, s32);
void func_8003C644(s32, s32, s32, void *);
void func_800367DC(void) {
    void *handle;
    void *buffer;
    s32 size;
    s32 idx;
    s32 entry;

    handle = func_8003C584();
    if (handle == NULL) {
        SystemShowFatalError(D_8008D0AC);
    }
    func_8003C8BC(handle, 0, 2);
    size = func_8003C8BC(handle, 0, 0);
    buffer = HeapAlloc(((size + 0x7FF) >> 11) << 11);
    D_800AE154[D_800A2F54] = (s32)buffer;
    if (buffer == NULL) {
        SystemShowFatalError(D_8008D0CC);
    }
    func_8003C644(D_800AE154[D_800A2F54], 1, size, handle);
    idx = D_800A2F54;
    entry = D_800AE154[idx];
    D_800B60A4[idx] = entry;
    D_800B1EA8[idx] = *(s32 *)entry;
    D_800AE154[idx] = entry + 4;
    D_800A2F54 = idx + 1;
    func_8003C63C((s32)handle);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800367DC);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80036900);

#ifdef NON_MATCHING
s32 func_80036F64(s32 *a, s32 *b, s32 arg2) {
    s32 index;
    s32 temp1;
    s32 temp2;

    index = *(s16 *)((u8 *)b + 0x114) * 4;
    temp1 = *(s32 *)((u8 *)D_800A3A2C + index);
    temp2 = *(s32 *)((u8 *)D_800A3A34 + index);
    return arg2 < (((a[0] - b[0]) * temp1 - (a[1] - b[1]) * temp2) >> 16);
}
#else
#ifdef NON_MATCHING
/*
 * Close: everything matches except three register/schedule choices.
 * (1) gcc extracts mflo immediately after the first mult; retail keeps
 * it until after the second table load (mflo t0 + nop). (2) retail
 * reads [arg0+4] into v0 (then [arg1+4] into a0); gcc reuses the dead
 * param register a0 for [arg0+4]. (3) integer-add spelling
 * (idx + (u32)SYM[0]) pins addu v0,a3,v0 — required. The D_*Absolute
 * defsym aliases make both lui/lw pointer loads work in one TU.
 */
extern s32 D_800A3A2CAbsolute[];
extern s32 D_800A3A34Absolute[];

s32 func_80036F64(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 idx;
    s32 diffX;
    s32 diffY;
    s32 crossX;
    s32 crossY;

    idx = *(s16 *)(arg1 + 0x114) << 2;
    diffX = *(s32 *)arg0 - *(s32 *)arg1;
    crossX = *(s32 *)(idx + (u32)D_800A3A2CAbsolute[0]) * diffX;
    diffY = *(s32 *)(arg0 + 4) - *(s32 *)(arg1 + 4);
    crossY = *(s32 *)(idx + (u32)D_800A3A34Absolute[0]) * diffY;
    return arg2 < ((crossX - crossY) >> 16);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80036F64);
#endif
#endif

#ifdef NON_MATCHING
s32 func_80036FC8(s32 *a, s32 *b) {
    s32 index;
    s32 temp1;
    s32 temp2;

    index = *(s16 *)((u8 *)b + 0x114) * 4;
    temp1 = *(s32 *)((u8 *)D_800A3A34 + index);
    temp2 = *(s32 *)((u8 *)D_800A3A2C + index);
    return ((a[0] - b[0]) * temp1 + (a[1] - b[1]) * temp2) >> 16 > 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80036FC8);
#endif

#ifdef NON_MATCHING
extern s32 D_800BE974[];
s32 func_8003702C(u8 *objectA, u8 *objectB) {
    s32 limit;
    s32 diff;
    s32 a;
    s32 b;

    limit = D_800BE974[0];
    diff = *(s16 *)(objectA + 0x1E0) - *(s16 *)(objectB + 0x1E0);
    if (diff >= 0) {
        if (diff < (limit >> 1)) {
            return diff;
        }
    } else {
        if ((limit >> 1) > -diff) {
            return diff;
        }
    }
    a = *(s16 *)(objectA + 0x1E0);
    b = *(s16 *)(objectB + 0x1E0);
    if (b < a) {
        b = b + limit;
        if (b - a < 0) {
            return b - a;
        }
        return a - b;
    }
    a = a + limit;
    if (a - b >= 0) {
        return a - b;
    }
    return b - a;
}
#else
#ifdef NON_MATCHING
/*
 * WALL (w9d): two diffs. (1) gcc copies arg0 to a2 at entry (`move
 * a2,a0`) because the s16 fields are read twice (once for the early
 * |diff| check, once for the wraparound path) and gcc 2.7.2 gives the
 * pointer its own callee pseudo; retail reuses a0/a1 as both base and
 * lh destination. (2) the inner `if (diff < half) return diff;`
 * compiles beqz-to-common where retail has bnez-to-return (branch
 * sense inverted; the ?: spelling was not tried in time). The wrap
 * path shape is right: y >= x vs y < x arms, threshold added to the
 * SMALLER value, sign flip on the negative result. D_800BE974 %lo
 * showed +0x18 drift while this draft was active -- self-inflicted
 * wrong length, not a split problem.
 */
extern s32 D_800BE974[];

s32 func_8003702C(s32 arg0, s32 arg1) {
    s32 diff;
    s32 half;
    s32 x;
    s32 y;

    diff = *(s16 *)(arg0 + 0x1E0) - *(s16 *)(arg1 + 0x1E0);
    half = D_800BE974[0] >> 1;
    if (diff >= 0) {
        if (diff < half) {
            return diff;
        }
    } else {
        if (-diff < half) {
            return diff;
        }
    }
    x = *(s16 *)(arg0 + 0x1E0);
    y = *(s16 *)(arg1 + 0x1E0);
    if (y < x) {
        y += D_800BE974[0];
        diff = x - y;
        if (diff < 0) {
            return diff;
        }
        return x - y;
    }
    x += D_800BE974[0];
    diff = x - y;
    if (diff >= 0) {
        return diff;
    }
    return y - x;
}
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8003702C);
#endif

#ifdef NON_MATCHING
extern s32 D_800BE974[];
s32 func_800370B8(s32 a, s32 b) {
    s32 limit;
    s32 diff;

    limit = D_800BE974[0];
    diff = a - b;
    if (diff >= 0) {
        if (diff < (limit >> 1)) {
            return diff;
        }
    } else {
        if (-diff < (limit >> 1)) {
            return diff;
        }
    }
    if (b < a) {
        b = b + limit;
        if (b - a < 0) {
            return b - a;
        }
        return a - b;
    }
    a = a + limit;
    if (a - b >= 0) {
        return a - b;
    }
    return b - a;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800370B8);
#endif

#ifdef NON_MATCHING
/*
 * WALLS: (1) retail re-reads *(s16 *)(object + 0x92) once per product
 * (three lh) — plain reads CSE into one lh and a volatile s16 read
 * emits lhu + sll16/sra16 instead of lh (extends the w5b entry);
 * (2) retail gaps mult and mflo with the next row's lh/lw (two
 * instructions + hazard nops); gcc 2.7.2 binds mult+mflo as one
 * pattern, so mflo lands immediately after mult. Prologue solved:
 * store-first with a volatile second 0x114 read puts the sh in the
 * jal delay slot, though that read is lhu in ours vs lh in retail.
 * Products map 0xB0=prod(0x60), 0xB4=prod(0x6C), 0xB8=prod(0x78);
 * the volatile reloads of 0xB0/B4/B8 before the adds are exact.
 */
void func_8001FAC0(u8 *, s32);
void func_8001FB28(u8 *, s16);
void func_80037130(u8 *object) {
    s32 prod0;
    s32 prod1;
    s32 prod2;
    s32 sum0;
    s32 sum1;
    s32 sum2;

    *(s16 *)(object + 0x116) = *(volatile s16 *)(object + 0x114) * 4;
    func_8001FAC0(object, *(s16 *)(object + 0x114) * 4);
    func_8001FB28(object, *(s16 *)(object + 0x104));
    prod0 = *(volatile s16 *)(object + 0x92) * *(s32 *)(object + 0x60);
    prod1 = *(volatile s16 *)(object + 0x92) * *(s32 *)(object + 0x6C);
    prod2 = *(volatile s16 *)(object + 0x92) * *(s32 *)(object + 0x78);
    *(s32 *)(object + 0xB0) = prod0 >> 16;
    *(s32 *)(object + 0xB4) = prod1 >> 16;
    *(s32 *)(object + 0xB8) = prod2 >> 16;
    sum0 = *(s32 *)(object + 0x0) + *(volatile s32 *)(object + 0xB0);
    sum1 = *(s32 *)(object + 0x4) + *(volatile s32 *)(object + 0xB4);
    sum2 = *(s32 *)(object + 0x8) + *(volatile s32 *)(object + 0xB8);
    *(s32 *)(object + 0x0) = sum0;
    *(s32 *)(object + 0x4) = sum1;
    *(s32 *)(object + 0x8) = sum2;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80037130);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80037204);

INCLUDE_ASM("asm/nonmatchings/game", func_800373B4);

INCLUDE_ASM("asm/nonmatchings/game", func_80038D78);

s32 func_80039008(u8 *arg0, u8 *arg1) {
    extern s32 func_8003702C();
    volatile s32 pad[4];
    s32 result;

    if (*(s32 *)(arg0 + 0x90) <= *(s32 *)(arg1 + 0x90)) {
        return 0;
    }
    result = func_8003702C(arg0, arg1);
    if (result >= 2) {
        return 0;
    }
    return (*(s32 *)(arg0 + 0x90) - *(s32 *)(arg1 + 0x90)) / 20 >> 16 >= result;
}

INCLUDE_ASM("asm/nonmatchings/game", func_800390A0);

INCLUDE_ASM("asm/nonmatchings/game", func_80039274);

INCLUDE_ASM("asm/nonmatchings/game", func_800395BC);

INCLUDE_ASM("asm/nonmatchings/game", func_80039B74);

#ifdef NON_MATCHING
typedef struct TimingPoint {
    u8 pad0[0x10];
    u16 unk10;
    u16 pad12;
    s32 unk14;
    s32 unk18;
} TimingPoint;
s8 func_80039C68(TimingPoint *arg0, s32 arg1, s32 arg2) {
    s32 index;
    s32 value;
    index = (0x400 - arg0->unk10) & 0x3FF;
    value = *(s32 *)(D_800A3A34 + (index * 4)) * (arg1 - arg0->unk14);
    value += *(s32 *)(D_800A3A2C + (index * 4)) * (arg2 - arg0->unk18);
    return (s8)(-((value >> 16) / 250));
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80039C68);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80039CF4);

INCLUDE_ASM("asm/nonmatchings/game", func_80039DDC);

INCLUDE_ASM("asm/nonmatchings/game", func_8003A440);

INCLUDE_ASM("asm/nonmatchings/game", func_8003A54C);

extern void func_8003ABC0();
extern s16 D_80098254[];

void func_8003A880(s32 car) {
    s32 old;
    s32 new;
    s32 idx;
    s32 turn;
    s32 t;
    s32 t2;
    s32 t3;
    s32 t4;

    if (*(s16 *)(car + 0x102) != 0) {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = -D_80098254[idx];
    } else {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = D_80098254[idx];
    }
    *(u16 *)(car + 0x114) = (*(u16 *)(car + 0x114) + turn + 0x400) & 0x3FF;
    t = *(s32 *)(car + 0x90);
    t2 = t - (t >> 5);
    *(s32 *)(car + 0x90) = t2;
    if (turn != 0) {
        return;
    }
    *(u16 *)(car + 0x1BC) = 0x32;
    t3 = *(s32 *)(car + 0x90);
    t4 = t3 - 0x320000;
    *(s32 *)(car + 0x90) = t4;
    if (t4 < 0) {
        *(s32 *)(car + 0x90) = 0;
    }
    ObjectSetCallbackIfAllowed((Batch0CallbackObject *)car, func_8003ABC0);
}

extern void func_8003ABC0();
extern s16 D_80098294[];

void func_8003A950(s32 car) {
    s32 old;
    s32 new;
    s32 idx;
    s32 turn;
    s32 t;
    s32 t2;
    s32 t3;
    s32 t4;

    if (*(s16 *)(car + 0x102) != 0) {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = -D_80098294[idx];
    } else {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = D_80098294[idx];
    }
    *(u16 *)(car + 0x114) = (*(u16 *)(car + 0x114) + turn + 0x400) & 0x3FF;
    t = *(s32 *)(car + 0x90);
    t2 = t - (t >> 5);
    *(s32 *)(car + 0x90) = t2;
    if (turn != 0) {
        return;
    }
    *(u16 *)(car + 0x1BC) = 0x32;
    t3 = *(s32 *)(car + 0x90);
    t4 = t3 - 0x320000;
    *(s32 *)(car + 0x90) = t4;
    if (t4 < 0) {
        *(s32 *)(car + 0x90) = 0;
    }
    ObjectSetCallbackIfAllowed((Batch0CallbackObject *)car, func_8003ABC0);
}

#ifdef NON_MATCHING
/*
 * Wall (w8d): semantics + statement order complete. Remaining diffs are
 * register allocation: retail keeps the loaded counter in v0 (addiu v1,v0,1
 * with the sh deferred past the sll16/sra15) and pan lives in a1 for its
 * whole life (negu a1 / lh a1); our gcc loads the counter into v1, stores
 * immediately, and puts pan in a2. Tried: u16 vs s32 counter, store-first
 * vs table-first statement orders. The tail (sra7/subu, volatile reload,
 * -0x320000 clamp with branchy if/else, callback) is exact.
 */
extern s16 D_800982D4[];
extern void func_8003ABC0();

void func_8003AA20(u8 *object) {
    s32 counter;
    s32 pan;
    s32 value;

    if (*(s16 *)(object + 0x102) != 0) {
        counter = *(u16 *)(object + 0x1BC);
        *(u16 *)(object + 0x1BC) = counter + 1;
        pan = *(s16 *)(D_800982D4 + (s16)counter);
        pan = -pan;
    } else {
        counter = *(u16 *)(object + 0x1BC);
        *(u16 *)(object + 0x1BC) = counter + 1;
        pan = *(s16 *)(D_800982D4 + (s16)counter);
    }
    *(u16 *)(object + 0x114) = *(u16 *)(object + 0x114) + pan + 0x400 & 0x3FF;
    value = *(s32 *)(object + 0x90);
    value -= value >> 7;
    *(s32 *)(object + 0x90) = value;
    if (pan == 0) {
        value = *(volatile s32 *)(object + 0x90);
        value -= 0x320000;
        *(u16 *)(object + 0x1BC) = 0;
        if (value < 0) {
            *(s32 *)(object + 0x90) = 0;
        } else {
            *(s32 *)(object + 0x90) = value;
        }
        ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                   func_8003ABC0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003AA20);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8003AAEC);

#ifdef NON_MATCHING
/*
 * Wall: retail keeps BOTH the u16 store (in the bnez delay slot) and a
 * separate lh reload; gcc forwards the stored value (sll/sra instead of
 * lh) unless the store is volatile, and a volatile store will not fill
 * the branch delay slot (extra sh + nop, +8 bytes). A volatile s16 load
 * emits lhu + sll/sra, not lh.
 */
extern void func_80025594(void);

void func_8003ABC0(u8 *object) {
    u16 timer;
    u16 mode;

    timer = *(u16 *)(object + 0x1BC);
    mode = *(u16 *)(object + 0x3A4);
    *(u32 *)(object + 0x90) = 0;
    timer = timer + 1;
    *(volatile u16 *)(object + 0x1BC) = timer;
    if ((mode & 0xF) == 0) {
        if (*(s16 *)(object + 0x1BC) >= 0x65) {
            *(u16 *)(object + 0x1BC) = 0;
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_80025594);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003ABC0);
#endif

extern void func_8003AA20();
extern void func_8003A880();
extern void func_8003A950();
extern void func_8003AAEC();

void func_8003AC18(u8 *object, s32 arg1, s32 arg2, s32 arg3) {
    extern void func_8002F66CArgs(void *, s32);

    asm(".globl func_8002F66CArgs\nfunc_8002F66CArgs = func_8002F66C");

    if (*(s16 *)(object + 0x1EC) == 1) {
        *(s16 *)(object + 0x1BC) = 0;
        if ((arg2 = arg2) > 0 && arg3 > 0) {
            *(s16 *)(object + 0x102) = 1;
        } else if ((arg2 = arg2) < 0 && arg3 < 0) {
            *(s16 *)(object + 0x102) = 1;
        } else {
            *(s16 *)(object + 0x102) = 0;
        }
        if (arg1 >= 0xC9) {
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_8003AA20);
            func_8002F66CArgs(object, 1);
            func_80041564(object, 0x29);
        } else if (arg1 >= 0xB0) {
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_8003A880);
            func_80041564(object, 0x29);
        } else if (arg1 >= 0x97) {
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_8003A950);
            func_80041564(object, 0x29);
        } else if (arg1 >= 0x3D) {
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_8003AAEC);
        }
    }
}

extern s32 D_800A3558[];
extern u8 *D_800A3554[];
extern s32 D_800A3730, D_800A3734;
void func_800390A0(s32, s32, s32, s32);
void FontDrawPaddedNumber(s32, s32, s32, s32);
void func_8003644C(s32, s32, s32, s32);
struct Unk_8003AD08 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};
void func_8003AD08(struct Unk_8003AD08 *arg0) {
    func_800390A0(D_800A3558[0], (s32)D_800A3554[0], 0, 0);
    FontDrawPaddedNumber(D_800A3730, 0x64, 0xC8, 0);
    FontDrawPaddedNumber(D_800A3734, 0xC8, 0xC8, 0);
    func_8003644C(1, D_800A3730 + arg0->unk0, D_800A3734 + arg0->unk4,
                  arg0->unk8);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8003AD94);

INCLUDE_ASM("asm/nonmatchings/game", func_8003B464);

INCLUDE_ASM("asm/nonmatchings/game", func_8003B5F8);

INCLUDE_ASM("asm/nonmatchings/game", func_8003B6DC);

#ifdef NON_MATCHING
/*
 * Wall (w8d): everything matches except callee-saved s-reg BOOKING: retail
 * next=s1, count=s2, offset=s0; our gcc insists next=s0 regardless of local
 * declaration order (tried 3 orders). Prologue (head load before the stack
 * adjust), loop body, store order (0,4,8), delay slots and the post-loop
 * head block are otherwise identical. Table reads are BYTE offsets into
 * D_800BE72C/730/738 (cast form). Head read via
 * ((u8 **)D_800A3854Absolute)[9] == D_800A3878 (no alias defsym for it).
 */
extern void func_8002D4CC();
extern void func_8003B6DC(s32 arg0);
extern u8 *D_800A3854Absolute[];
extern s32 D_800BE72C[];
extern s32 D_800BE730[];
extern s16 D_800BE738[];
extern s32 D_800A2F60;
extern s32 D_800A2EACAbsolute[];

void func_8003BCAC(void) {
    register s32 count asm("s2");
    register s32 offset asm("s0");
    u8 *object;

    object = *(u8 **)(((u8 **)D_800A3854Absolute)[9] + 0x3E0);
    if (object != 0) {
        count = 0;
        offset = 0;
        do {
            func_8002D4CC(object);
            *(s32 *)(object + 0) = *(s32 *)((u8 *)D_800BE72C + offset);
            *(s32 *)(object + 4) = *(s32 *)((u8 *)D_800BE730 + offset);
            *(s32 *)(object + 8) = 0;
            func_80022FB8(object, *(s16 *)((u8 *)D_800BE738 + offset));
            object = *(u8 **)(object + 0x3E0);
            count += 1;
            offset += 0x10;
        } while (object != 0);
    }
    object = ((u8 **)D_800A3854Absolute)[9];
    offset = count * 0x10;
    *(s32 *)(object + 0) = *(s32 *)((u8 *)D_800BE72C + offset);
    *(s32 *)(object + 4) = *(s32 *)((u8 *)D_800BE730 + offset);
    *(s32 *)(object + 8) = 0;
    func_8002D4CC(object);
    func_80022FB8(object, *(s16 *)((u8 *)D_800BE738 + offset));
    D_800A2F60 = 0x14;
    func_8001D1E4();
    D_800A2EACAbsolute[0] = 0;
    func_8003B6DC(1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003BCAC);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8003BDBC);

INCLUDE_ASM("asm/nonmatchings/game", func_8003C1CC);

INCLUDE_ASM("asm/nonmatchings/game", func_8003C3FC);

extern u8 *D_800A3554[];
extern u8 D_800BE70C[], D_800B9DA4[];
extern s32 D_800AE1EC[];
/* CD control and streaming. */

void func_8003C528(void) {
    u8 index;
    s32 value;
    index = D_800A3554[0][0x376];
    value = *(s32 *)(D_800A3554[0] + 0x25C);
    D_800BE70C[0] = index;
    D_800AE1EC[0] = value;
    D_800B9DA4[index & 0xFF] = 0;
}

extern s32 CdSetDebug(s32 level);
void CdDisableDebug(void) {
    CdSetDebug(0);
}

extern s32 D_800A2F74;
extern s32 D_800A37CC;
extern CdlLOC D_800BDEBC[];
extern s32 D_80098340[];
extern s32 D_800A45A8[];
extern s32 D_800A45AC[];

void *func_8003C584(s32 arg0, void *arg1) {
    u8 pad[0x40];
    u8 result[8];
    void *pos;
    s32 value;

    if (D_800A2F74 == 0) {
        CdGetToc(D_800BDEBC);
        D_800A2F74 = 1;
    }
    CdIntToPos(D_80098340[arg0 * 3] + 0x13C, D_800A45A8);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = D_80098340[arg0 * 3 + 1];
    D_800A45AC[0] = value;
    D_800A37CC = arg0;
    pos = &D_800A45AC[-1];
    return pos;
}

void func_8003C63C(void) {
}

INCLUDE_ASM("asm/nonmatchings/game", func_8003C644);

s32 func_8003C8B4(void) {
    return 0;
}

s32 func_8003C8BC(s32 *data) {
    return data[1];
}

void func_8003C8C8(u8 *string) {
    s32 length;
    s32 current;
    s32 end;
    u8 value;
    length = strlen((char *)string);
    if (length > 0) {
        current = (s32)string;
        end = length + current;
        do {
            value = *(u8 *)current;
            if ((u32)(value - 'a') < 26) {
                value -= 0x20;
                *(u8 *)current = value;
            }
            current++;
        } while (current < end);
    }
}

extern void *HeapAlloc(u32);

void *func_8003C928(s32 arg0) {
    u8 pad[0x40];
    u8 result[8];
    s32 value;
    s32 size;
    void *buffer;

    if (D_800A2F74 == 0) {
        CdGetToc(D_800BDEBC);
        D_800A2F74 = 1;
    }
    CdIntToPos(D_80098340[arg0 * 3] + 0x13C, D_800A45A8);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = D_80098340[arg0 * 3 + 1];
    D_800A37CC = arg0;
    D_800A45AC[0] = value;
    size = (value + 0x7FF) >> 11 << 11;
    buffer = HeapAlloc(size);
    if (buffer != 0) {
        func_8003C644(buffer, 1, size, D_800A45A8);
    }
    return buffer;
}

extern void func_8003C644();

void func_8003CA18(s32 arg0, s32 arg1) {
    u8 pad[0x40];
    u8 result[8];
    s32 value;

    if (D_800A2F74 == 0) {
        CdGetToc(D_800BDEBC);
        D_800A2F74 = 1;
    }
    CdIntToPos(D_80098340[arg1 * 3] + 0x13C, D_800A45A8);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = D_80098340[arg1 * 3 + 1];
    D_800A37CC = arg1;
    D_800A45AC[0] = value;
    func_8003C644(arg0, 1, value, D_800A45A8);
}

#ifdef NON_MATCHING
/*
 * w6e draft, 4 bytes short (0x15c vs 0x160): the %6 block's register
 * allocation differs - retail keeps the remainder in v0 and copies
 * v0->s0 in the bgez DELAY SLOT (negu reads s0); ours sinks
 * `lui a0,0x19649` into that delay slot instead and swaps v0/v1 in the
 * sra/subu pair. Frame is correct (0x58: volatile u_char result[0x30]
 * at 0x10, u8 filter at 0x18). Retail's two-symbol trick verified:
 * CdGetToc takes D_800BDEBC inline while the six CdIntToPos calls hoist
 * &D_800BDEC4[0] into s0 (overlapping externs; cse does not merge).
 * Next: make the v0->s0 copy a real statement, or permuter.
 */
extern s32 CdGetToc(void *);
extern CdlLOC D_800BDEBC[];
extern CdlLOC D_800BDEC4[];
extern s32 D_800A2F70;
extern u8 D_800A2F9CAbsolute[];

void func_8003CAE8(s32 arg0) {
    volatile u_char result[0x30];
    u8 filter;
    CdlATV vol;
    CdlLOC *pos;
    s32 remainder;

    if (CdGetToc(D_800BDEBC) < 2) {
        return;
    }
    filter = 5;
    if (CdControl(0xE, &filter, 0) == 0) {
        return;
    }
    CdSetDebug(0);
    remainder = arg0 % 6;
    if (remainder < 0) {
        remainder = -remainder;
    }
    D_800A2F70 = remainder + 2;
    pos = &D_800BDEC4[0];
    CdIntToPos(0x19649, pos);
    CdIntToPos(0x1C4B8, pos + 1);
    CdIntToPos(0x1F278, pos + 2);
    CdIntToPos(0x2219A, pos + 3);
    CdIntToPos(0x250DB, pos + 4);
    CdIntToPos(0x25EFF, pos + 5);
    CdControl(2, (u_char *)(pos + D_800A2F70 - 2), 0);
    if (D_800A2F9CAbsolute[0] != 0) {
        CdControlB(3, 0, 0);
    }
    vol.val0 = 0x7F;
    vol.val1 = 0x7F;
    vol.val2 = 0x7F;
    vol.val3 = 0x7F;
    CdMix(&vol);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003CAE8);
#endif

extern s32 D_800A2EC8[];
extern s32 D_800A2F70;
extern u8 D_800A2F9CAbsolute[];
extern u8 D_800AE24C[];

void func_8003CC48(void) {
    u_char param[8];
    u_char result[8];

    if (D_800A2F9CAbsolute[0] == 0) {
        return;
    }
    if (D_800A2EC8[0] != 0) {
        return;
    }
    CdControl(1, 0, D_800AE24C);
    param[0] = 0;
    CdControl(0x11, param, result);
    if (result[0] == D_800A2F70) {
        return;
    }
    CdControl(2, (u_char *)&D_800BDEBC[D_800A2F70], 0);
    CdControl(3, 0, 0);
}

void func_8003CCE0(s32 arg0) {
    u_char pad[0x10];
    u_char *status;
    s32 target;

    pad[0] = 0;
    if (arg0 != 0) {
        CdControl(3, 0, 0);
        CdControlB(0xC, 0, 0);
        return;
    }
    status = D_800AE24C;
    CdControlB(1, 0, status);
    if (*(s32 *)status != 0x42) {
        CdControl(9, 0, 0);
        return;
    }
    target = 0x82;
    do {
        CdControl(1, 0, status);
    } while (*(s32 *)status != target);
    CdControl(9, 0, 0);
}

void CdStop(void) {
    CdControl(8, 0, 0);
}

#ifdef NON_MATCHING
/*
 * cc1 2.7.2 ICE wall (w6e): any `for` loop with a memory STORE in its body
 * in this function segfaults cc1 at this TU position (exit 139, truncated
 * object; repro `for (i = 0; i < count; i++) D_800B9F44[i] = i;` alone).
 * Load-only loops compile. Function shape below diffs clean otherwise
 * (not yet verified end to end). Same class as the func_8001E17C ICE.
 */
extern void *CdGetToc(void *);
extern s32 D_800A2F74;
extern s32 D_800A37CC;
extern CdlLOC D_800BDEBC[];
extern s32 D_800BDEBC[];
extern s32 D_80098340[];
extern s32 D_800A45AC[];
extern char D_8008D188[];

void func_8003CDBC(s32 arg0) {
    u8 result[16];
    s32 *pos;
    s32 value;
    s32 posValue;
    u32 base;
    s32 count;
    s32 i;
    s32 *src;

    if (D_800A2F74 == 0) {
        CdGetToc(D_800BDEBC);
        D_800A2F74 = 1;
    }
    CdIntToPos(D_80098340[arg0 * 3] + 0x13C, &D_800A45AC[-1]);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = D_80098340[arg0 * 3 + 1];
    pos = &D_800A45AC[-1];
    D_800A37CC = arg0;
    D_800A45AC[0] = value;
    if (pos == NULL) {
        SystemShowFatalError(D_8008D188);
    }
    posValue = D_800A45AC[0];
    base = (0x1F4000 - posValue) | 0x80000000;
    func_8003C644(base, posValue, 1, pos);
    count = *(s32 *)base;
    src = (s32 *)(base + 4);
    for (i = 0; i < count; i++) {
        D_800B9F44[i] = src[i] + base;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003CDBC);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008D1A8);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008D1C4);
#endif

void func_8003CEFC(void) {
}

void func_8003CF04(void) {
}

INCLUDE_ASM("asm/nonmatchings/game", func_8003CF0C);

extern s32 D_800A3A04nm[] asm("D_800A3A04.NON_MATCHING");
extern s32 D_800A3A3CAbsolute[];
extern s32 D_800A2F84nm asm("D_800A2F84.NON_MATCHING");
extern void func_800414E0(void *, s32, s32);

void func_8003D25C(u8 *object) {
    s32 i;
    s32 j;
    register s32 value asm("a0");
    s32 count;
    s32 diff;
    u8 flag;

    D_800A3A04nm[0] = 3;
    func_80029CB4(object);
    D_800A3A3CAbsolute[-14] = 0xD;
    flag = 1;
    if (*(u8 *)(object + 0x26A) & 0x10) {
        i = *(u8 *)(object + 0x26A) & 0x40;
        if (D_800A2F84nm != 0) {
            i = !i;
        }
        if (i != 0) {
            *(s16 *)(object + 0x2AC) = *(s16 *)(object + 0x274) * 10;
            *(s16 *)(object + 0x2FC) = *(s16 *)(object + 0x274) * 10;
            *(s16 *)(object + 0x2D4) = *(s16 *)(object + 0x274) * 4;
            *(s16 *)(object + 0x324) = *(s16 *)(object + 0x274) * 4;
        } else {
            *(s16 *)(object + 0x2D4) = *(s16 *)(object + 0x274) * 10;
            *(s16 *)(object + 0x324) = *(s16 *)(object + 0x274) * 10;
            *(s16 *)(object + 0x2AC) = *(s16 *)(object + 0x274) * 4;
            *(s16 *)(object + 0x2FC) = *(s16 *)(object + 0x274) * 4;
        }
        for (i = 0; i < 4; i++) {
            if (*(u8 *)(object + 0x26A) & 0x40) {
                if (i < 2) {
                    continue;
                }
            } else {
                if (i >= 2) {
                    break;
                }
            }
            value = *(u16 *)(object + i * 2 + 0x26C);
            *(u16 *)(object + i * 2 + 0x26C) = value - 1;
            count = (s16)(value - 1);
            if (count == 0x5A) {
                goto special;
            }
            if (count == 5) {
            special:
                if (*(s16 *)(object + 0x1EC) == 0) {
                    func_800414E0(object, 8, 3);
                }
                *(u16 *)(object + i * 2 + 0x26C) =
                    *(u16 *)(object + i * 2 + 0x26C) - 1;
            } else if (count == 0x46) {
                register s32 t asm("v0");
                t = value - 2;
                *(s16 *)(object + i * 2 + 0x26C) = t;
            } else if (count == 0x28) {
                *(s16 *)(object + i * 2 + 0x26C) = value - 2;
                func_8002D3EC(object);
                *(u8 *)(object + i + 0x3A6) = 1;
            }
            if (*(s16 *)(object + i * 2 + 0x26C) > 0) {
                flag = 0;
                asm("");
            }
        }
        if (flag != 0) {
            if (*(u8 *)(object + 0x26A) & 0x40) {
                *(u8 *)(object + 0x26A) &= 0xAE;
            } else {
                *(s16 *)(object + 0x274) = -0x23;
                *(u8 *)(object + 0x26A) =
                    (*(u8 *)(object + 0x26A) | 0x40) & 0xEF;
            }
            j = 3;
            do {
                asm(""
                    :
                    :
                    : "$2", "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11",
                      "$12", "$13", "$14", "$15", "$16", "$17", "$24", "$25");
                *(s16 *)(object + j * 0x28 + 0x2B0) = 0;
                j--;
            } while (j >= 0);
        } else {
            if (*(s16 *)(object + 0x274) < 4) {
                *(s16 *)(object + 0x274) = *(s16 *)(object + 0x274) + 1;
            }
        }
    } else {
        if ((s16)++ * (u16 *)(object + 0x274) == 5) {
            *(u8 *)(object + 0x26A) |= 0x10;
            *(s16 *)(object + 0x274) = 0;
            if (*(u8 *)(object + 0x26A) & 0x40) {
                *(s16 *)(object + 0x270) = 100;
                *(s16 *)(object + 0x272) = 100;
            } else {
                *(s16 *)(object + 0x26C) = 100;
                *(s16 *)(object + 0x26E) = 100;
            }
        }
    }
}

extern s32 func_80029EF8(u8 *);

void func_8003D528(u8 *object) {
    s32 result;
    s32 value;
    s32 mask;

    value = *(s32 *)(object + 0x28C) + 0x4B;
    *(s32 *)(object + 0x28C) = value;
    result = 0;
    if (value >= 0x3E81) {
        *(s32 *)(object + 0x28C) = 0x3E80;
    }
    if (*(s16 *)(object + 0x1EC) == 0) {
        result = func_80029EF8(object);
    }
    if (*(s32 *)(object + 0x28C) == 0x3E80) {
        goto trigger;
    }
    if (*(s16 *)(object + 0x1EC) == 0 && (*(u8 *)(object + 0x26A) & 1) == 0) {
        mask = ~*(s32 *)(object + 0x23C) & 0x40;
        if ((result & mask) != 0) {
        trigger:
            *(s32 *)(object + 0x290) = 0x7D000;
            *(u8 *)(object + 0x26A) &= 0xDD;
        }
    }
    *(s32 *)(object + 0x23C) = result;
}

void func_8003D5F8(u8 *object) {
    u16 flags;
    s32 i;
    u32 total;
    u8 *entry;

    flags = *(u16 *)(object + 0x3A4);
    total = 0;
    if (flags != 0) {
        i = 0;
        do {
            entry = object + i;
            if (*(s8 *)(entry + 0x3A6) == 0) {
                total = total + 0x14;
            }
            if (*(s8 *)(entry + 0x3AE) != 0) {
                total = total + *(s8 *)(entry + 0x3AE) * 3;
            }
            i = i + 1;
        } while (i < 8);
    }
    *(u16 *)(object + 0x280) = total;
}

void func_8003D654(u8 *object) {
    s32 i;
    u16 count;
    count = *(u16 *)(object + 0x280);
    *(u16 *)(object + 0x280) = count - 1;
    if ((s16)count < 0) {
        *(s16 *)(object + 0x3A4) = 0;
        i = 0;
        do {
            *(object + i + 0x3A6) = 1;
            *(object + i + 0x3AE) = 0;
            i++;
        } while (i < 8);
    }
}

void func_8003D69C(u8 *object) {
    s32 value;
    s32 now;

    value = *(volatile u16 *)(object + 0x278);
    now = *(u16 *)(object + 0x278);
    *(u16 *)(object + 0x278) = now - 1;
    *(s16 *)(object + 0x2A2) = (s16)value / 10;
    if ((now << 16) < 0) {
        *(u16 *)(object + 0x2A2) = 0;
        *(u8 *)(object + 0x26A) &= ~0x04;
    }
}

void func_8003D6F8(u8 *object) {
    s32 value;
    s32 now;

    value = *(volatile u16 *)(object + 0x27A);
    now = *(u16 *)(object + 0x27A);
    *(u16 *)(object + 0x27A) = now - 1;
    *(s16 *)(object + 0x2A8) = (s16)value / 10;
    if ((now << 16) < 0) {
        *(u16 *)(object + 0x2A8) = 0;
        *(u8 *)(object + 0x26A) &= ~0x08;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_8003D754);

extern s32 D_800BE974[];
s32 func_8003DAD0(s32 a, s32 b) {
    if (b >= D_800BE974[0]) {
        if (a >= D_800BE974[0] / 2)
            return 0;
        b -= D_800BE974[0];
    }
    return !(a < b);
}

extern s32 D_800BE974[];
s32 func_8003DB18(s32 start, s32 end, s32 value) {
    s32 result;
    s32 offset;
    offset = D_800BE974[0];
    if (value < end) {
        if (value >= start) {
            value += offset;
            return 1;
        }
        value += offset;
    }
    result = 0;
    if (start >= end)
        result = value >= start;
    return result;
}

#ifdef NON_MATCHING
/*
 * Walls: (1) gcc hoists the speculative `slt v0,a0,a1` into the first
 * bnez delay slot and computes it again at the join; retail computes it
 * once at the join with a nop delay. (2) my D_800BE974 reference linked
 * to -0x1688 (0x800BE978) instead of -0x168c (0x800BE978 vs 974) —
 * audit undefined_syms/linker resolution before re-enabling.
 */
s32 func_8003DB5C(s32 arg0, s32 arg1, s32 arg2) {
    s32 limit;

    limit = D_800BE974[0];
    if (arg2 < arg1) {
        if (limit / 2 >= arg0) {
            arg2 = arg2 + limit;
            arg0 = arg0 + limit;
        }
    }
    if (arg0 < arg1) {
        return 0;
    }
    return arg2 >= arg0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003DB5C);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8003DBA8);

#ifdef NON_MATCHING
extern u8 D_800A372C[];
extern s32 D_800A2CE0[];
extern s32 D_800A2EA8[];
extern s32 D_800BE974[];
extern s32 D_800A3560;
extern s32 D_800A376C;
extern s32 D_800A3820;
extern s32 D_800A39E0;

s32 func_8003E78C(u8 *object) {
    s32 laps;
    s32 value;
    s32 start;
    s32 end;
    u8 flag;
    s32 ahead;
    s32 pace;

    if (*(s16 *)(object + 0x288) != 0) {
        if (D_800A372C[0] != 0 && D_800A2CE0[0] == 3 &&
            *(s16 *)(object + 0x1EC) == 0 && *(s16 *)(object + 0x1E0) >= 100) {
            return 1;
        }
        value = (D_800A376C + (D_800A3560 + 8)) % D_800BE974[0];
        end =
            (D_800A39E0 - (D_800A3820 + 0x14) + D_800BE974[0]) % D_800BE974[0];
        start = *(s16 *)(object + 0x1E0);
        if (value < end) {
            if (value >= start) {
                value += D_800BE974[0];
                flag = 1;
            } else {
                value += D_800BE974[0];
                flag = 0;
                if (start >= end)
                    flag = value >= start;
            }
        } else {
            flag = 0;
            if (start >= end)
                flag = value >= start;
        }
        if (flag != 0)
            return 1;
        *(s16 *)(object + 0x288) = 0;
        *(u16 *)(object + 0x284) = *(u16 *)(object + 0x284) + 1;
        return 0;
    }
    laps = *(s16 *)(object + 0x1D6);
    if (laps < 2)
        return 0;
    if (*(s16 *)(object + 0x276) == 0) {
        if ((u32)laps >= (u32) * (s32 *)(object + 0x29C) ||
            D_800A2EA8[0] < laps)
            *(s16 *)(object + 0x276) = 1;
        return 0;
    }
    if (D_800A372C[0] != 0)
        return 0;
    value = (D_800A39E0 - (D_800A3820 + 7) + D_800BE974[0]) % D_800BE974[0];
    end = (D_800A39E0 - (D_800A3820 + 0xF) + D_800BE974[0]) % D_800BE974[0];
    start = *(s16 *)(object + 0x1E0);
    if (value < end) {
        if (value >= start) {
            value += D_800BE974[0];
            flag = 1;
        } else {
            value += D_800BE974[0];
            flag = 0;
            if (start >= end)
                flag = value >= start;
        }
    } else {
        flag = 0;
        if (start >= end)
            flag = value >= start;
    }
    if (flag == 0)
        return 0;
    *(s16 *)(object + 0x288) = 1;
    ahead = *(s16 *)(object + 0x282);
    pace = *(s32 *)(object + 0x29C);
    if (RandomScaledGet(5) < 0)
        value = ahead - RandomScaledGet(5);
    else
        value = ahead + RandomScaledGet(5);
    *(s32 *)(object + 0x29C) = pace - 2 + value;
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003E78C);
#endif

#ifdef NON_MATCHING
/* Walls: retail keeps the walked pointer IN the a1 param register with
 * the +0xc preheader addiu after the single rotated guard; gcc 2.7.2
 * either copies the walk to another register, folds the +0xc into the
 * loop load offsets, or drops the empty 8-byte frame. Closest draft: */
void func_8003EA94(u8 *object, s32 *arg1, s32 arg2) {
    s32 count;
    s32 i;
    s32 *entries;

    count = *(s16 *)(object + 2) - *(s16 *)(object + 0) + 1;
    entries = *(s32 *)(object + 8) + arg2;
    *(s32 *)(object + 8) = entries;
    if (count > 0) {
        entries = arg1 + 3;
        for (i = 0; i < count; i++) {
            *entries += arg2;
            entries += 5;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003EA94);
#endif

#ifdef NON_MATCHING
void func_8003EAE8(u8 *object, s32 index) {
    u8 *group;
    u8 *entry;
    s32 *table;
    s32 count;
    s32 low;
    s32 total;
    s32 *ptr;
    s32 i;

    group = *(u8 **)(object + 0x370);
    entry = *(u8 **)(group + 0x150) + index * 0x18;
    count = *(s32 *)(entry + 8);
    if (count > 0) {
        low = *(s16 *)(entry + 0);
        table = *(s32 **)(group + 0x124);
        total = *(s16 *)(entry + 2) - low + 1;
        *(s32 *)(entry + 8) = count + 0xE;
        for (i = 0, ptr = table + low * 5 + 3; i < total; i++) {
            *ptr += 0xE;
            ptr += 5;
        }
    } else {
        low = *(s16 *)(entry + 0);
        table = *(s32 **)(group + 0x124);
        total = *(s16 *)(entry + 2) - low + 1;
        *(s32 *)(entry + 8) = count - 0xE;
        for (i = 0, ptr = table + low * 5 + 3; i < total; i++) {
            *ptr -= 0xE;
            ptr += 5;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003EAE8);
#endif

#ifdef NON_MATCHING
void func_8003EBD0(u8 *object, s32 index) {
    u8 *group;
    u8 *entry;
    s32 *table;
    s32 count;
    s32 low;
    s32 total;
    s32 *ptr;
    s32 i;

    group = *(u8 **)(object + 0x370);
    entry = *(u8 **)(group + 0x150) + index * 0x18;
    count = *(s32 *)(entry + 8);
    if (count > 0) {
        low = *(s16 *)(entry + 0);
        table = *(s32 **)(group + 0x124);
        *(s32 *)(entry + 8) = count - 0xE;
        total = *(s16 *)(entry + 2) - low + 1;
        for (i = 0, ptr = table + low * 5 + 3; i < total; i++) {
            *ptr -= 0xE;
            ptr += 5;
        }
    } else {
        low = *(s16 *)(entry + 0);
        table = *(s32 **)(group + 0x124);
        *(s32 *)(entry + 8) = count + 0xE;
        total = *(s16 *)(entry + 2) - low + 1;
        for (i = 0, ptr = table + low * 5 + 3; i < total; i++) {
            *ptr += 0xE;
            ptr += 5;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003EBD0);
#endif

#ifdef NON_MATCHING
/* Walls (w8e): (1) retail copies the param (move t1,a0) and loads
 * D_800A3878 into a0; gcc keeps object in a0 and loads the pointer into
 * a1 - no source form produced the copy (needs the D_800A3878 symbol to
 * lui-address: live scalar decl at func_8002EE88 forces gp, hence the
 * D_800A387C-4 neighbor read). (2) src/dst inits hoist above the count
 * check (retail: move t0,t1/move a3,t1 right before the loop).
 * (3) frame is -8 in retail; every all-s32 shape (with or without a
 * volatile pad) gives -0x10, an s16 local gives -8 but adds an
 * lhu+sll/sra pair at the f27C load (+8 bytes). With the s16 ext the
 * loop went clean; all-s32 the loop is clean and the body is 8 SHORT.
 * Nearest drafts below / in git history of the wave notes. */
extern u8 D_800A387C[];
extern s32 D_800AE84C[];

void func_8003ECB8(u8 *object) {
    volatile s32 pad[1];
    u8 *current;
    u8 *base;
    s32 id;
    s32 depth;
    s32 i;
    s32 value;
    s32 extra;
    u16 u16v;
    u8 *row;
    u8 *src;
    u8 *dst;

    current = *(u8 **)(D_800A387C - 4);
    base = D_800BE97C[0];
    if (current != 0) {
        id = *(s16 *)(object + 0xC) - 1;
        for (; current != 0; current = *(u8 **)(current + 0x3E0)) {
            if (*(s16 *)(current + 0x1DE) == id)
                break;
        }
        if (current != 0 && *(s16 *)(current + 0x1EC) != 1 &&
            *(u8 *)(current + 0x268) != 0) {
            depth = *(s16 *)(current + 0x27C);
            for (src = object, dst = object, i = 0; i < *(s16 *)(object + 0xA);
                 i++) {
                value = *(s16 *)(src + 0x94);
                extra = *(s32 *)(object + 0x218);
                u16v = *(u16 *)(dst + 0x10);
                row = base + (u16v << 3);
                value = value + extra - depth;
                if (value < 0) {
                    value += 3;
                }
                *(s16 *)(row + 4) = (value >> 2) - D_800AE84C[0];
                src += 6;
                dst += 2;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003ECB8);
#endif

extern s32 D_800A2EA8[];
extern s32 D_800BE974[];
extern s32 D_800A2F88;

#ifdef NON_MATCHING
void func_8003EDA0(u8 *object) {
    s32 pace;
    s32 dist;
    s32 value;

    dist = D_800BE974[0] * D_800A2EA8[0] / D_800A2F88;
    value = (D_800A2EA8[0] + dist) / (dist + 1) + 1;
    *(s32 *)(object + 0x29C) = value;
    *(s16 *)(object + 0x282) = value;
    if (dist != 0) {
        pace = *(s32 *)(object + 0x29C);
        if (RandomScaledGet(5) < 0)
            pace = pace - 2 - RandomScaledGet(5);
        else
            pace = pace - 2 + RandomScaledGet(5);
        *(s32 *)(object + 0x29C) = pace;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003EDA0);
#endif

extern u8 D_800A2F95;
/* Sound resources and sequences. */

void SoundStart(void) {
    SsStart2();
    SsSetMVol(127, 127);
    if (D_800A2F95 != 0) {
        SsSetStereo();
    } else {
        SsSetMono();
    }
}

extern s16 gSequenceId;
extern s16 gVabId;
extern u8 *gSequenceData;
extern void SsVabClose(s16);
extern void SsEnd(void);
extern s32 D_800A3A08;
void SoundShutdown(void) {
    if (gSequenceId != -1)
        SsSeqClose(gSequenceId);
    if (gVabId != -1) {
        SsVabClose(gVabId);
        gVabId = -1;
    }
    if (D_800A3A08 != 0) {
        HeapFree((void *)D_800A3A08);
        D_800A3A08 = 0;
    }
    if (gSequenceData != 0) {
        HeapFree((void *)gSequenceData);
        gSequenceData = 0;
    }
    SsEnd();
    VSync(0);
    VSync(0);
}

void SoundEnd(void) {
    SsSetMVol(0, 0);
    SsEnd();
}

extern void func_80080758(void);
void func_8003EFC8(void) {
    func_80080758();
}

extern void *D_800A3A00;
extern void HeapFree(void *ptr);
void func_8003EFE8(void) {
    if (D_800A3A00 != 0) {
        HeapFree(D_800A3A00);
        D_800A3A00 = 0;
    }
}

extern void func_80080728(void);
extern char D_800AF990[], D_800B9C88[];
extern s32 SpuInitMalloc(s32, char *);
void SoundInitTables(void) {
    func_80080728();
    SpuInitMalloc(32, D_800AF990);
    SsSetTableSize(D_800B9C88, 1, 1);
    SsSetTickMode(1);
}

#ifdef NON_MATCHING
extern s16 D_800B9E24[];
extern s8 D_800A3880;
extern void func_8003F13C(s32);

void func_8003F060(s32 arg0) {
    u8 i;

    for (i = 0; i < 24; i++) {
        D_800B9E24[i * 6] = -1;
    }
    gVabId = -1;
    gSequenceData = 0;
    D_800A3A08 = 0;
    func_8003F13C(arg0);
    D_800A3880 = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003F060);
#endif

#ifdef NON_MATCHING
void func_8003F0CC(void) {
    u8 i;

    i = 0;
    do {
        D_800B9E24[i * 6] = -1;
        i++;
    } while (i < 24);
    gVabId = -1;
    gSequenceData = 0;
    D_800A3A08 = 0;
    func_8003F1B0();
    D_800A3880 = 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003F0CC);
#endif

#ifdef NON_MATCHING
extern void func_8003FA0C(void);
extern s32 func_8003FF5C(s32, s32);

void func_8003F13C(s32 arg0) {
    s32 value;

    func_8003FA0C();
    if (gVabId != -1)
        SsVabClose(gVabId);
    D_800A3A08 = (s32)func_8003FFF0((void *)(arg0 + 1), 0);
    value = (s32)func_8003FFF0((void *)arg0, 0x80140000);
    D_800A3A00 = (void *)value;
    gVabId = func_8003FF5C(D_800A3A08, value);
}
#else
extern s16 gVabId;
extern void *D_800A3A00;
extern s32 D_800A3A08;
extern s32 func_8003FFF0(void *, void *);
extern s16 func_8003FF5C(void *, void *);
extern void SsVabClose(s16);
extern void func_8003FA0C(void);

void func_8003F13C(s32 arg0) {
    volatile s32 buf[8];
    s32 body;

    func_8003FA0C();
    if (gVabId != -1) {
        SsVabClose(gVabId);
    }
    D_800A3A08 = func_8003FFF0((void *)(s32 *)arg0 + 1, 0);
    body = func_8003FFF0((void *)arg0, (void *)0x80140000);
    D_800A3A00 = body;
    gVabId = func_8003FF5C((void *)D_800A3A08, (void *)body);
}
#endif

#ifdef NON_MATCHING
void func_8003F1B0(s32 arg0) {
    s32 value;

    func_8003FA0C();
    if (gVabId != -1)
        SsVabClose(gVabId);
    D_800A3A08 = (s32)func_8003FFF0((void *)arg0, 0);
    value = (s32)func_8003FFF0((void *)(arg0 + 1), 0);
    D_800A3A00 = (void *)value;
    gVabId = func_8003FF5C(D_800A3A08, value);
    if (D_800A3A00 != 0) {
        HeapFree(D_800A3A00);
        D_800A3A00 = 0;
    }
}
#else
extern s16 gVabId;
extern void *D_800A3A00;
extern s32 D_800A3A08;
extern s32 func_8003FFF0(void *, void *);
extern s16 func_8003FF5C(void *, void *);
extern void SsVabClose(s16);
extern void HeapFree(void *);
extern void func_8003FA0C(void);

void func_8003F1B0(s32 arg0) {
    volatile s32 buf[8];
    s32 body;

    func_8003FA0C();
    if (gVabId != -1) {
        SsVabClose(gVabId);
    }
    D_800A3A08 = func_8003FFF0((void *)arg0, 0);
    body = func_8003FFF0((void *)(arg0 + 1), 0);
    D_800A3A00 = body;
    gVabId = func_8003FF5C((void *)D_800A3A08, (void *)body);
    if (D_800A3A00 != 0) {
        HeapFree((void *)D_800A3A00);
        D_800A3A00 = 0;
    }
}
#endif

void func_80082B70(void);
void func_8003F23C(void) {
    func_80082B70();
}

extern void func_80082B70(void);
extern void func_8003F284(void);
void func_8003F25C(void) {
    func_80082B70();
    func_8003F284();
}

extern void func_80082B50(void);
void func_8003F284(void) {
    SsUtSetReverbType(2);
    func_80082B50();
}

extern u8 D_800A2F94;

void func_8003F2AC(s32 arg0, s32 arg1) {
    SsUtSetReverbDepth((s16)((arg0 & 0xFF) * D_800A2F94 / 127),
                       (s16)((arg1 & 0xFF) * D_800A2F94 / 127));
}

extern s32 func_8003FFF0(void *, void *);
extern s16 gVabId;
extern u8 D_800A2F94;
extern u8 *gSequenceData;
extern s16 gSequenceId;
void SoundOpenSequence(void) {
    u8 entry[32];
    u8 *sequence;
    s16 id;
    sequence = func_8003FFF0(entry, 0);
    gSequenceData = sequence;
    if (sequence != 0) {
        id = SsSeqOpen(sequence, gVabId);
        gSequenceId = id;
        SsSeqSetVol(id, D_800A2F94, D_800A2F94);
    }
}

extern s16 gSequenceId;
extern void SsSetLoop(short seqAccessNum, short para1, short para2);
extern void SsSeqPlay(short seqAccessNum, short playMode, short playCount);
extern void SsSeqReplay(short seqAccessNum);

/* A loop count of -1 means loop forever, which SsSetLoop spells as 0. */
void SoundSetSequenceLoop(s8 loopCount) {
    s32 seqId;

    if (gSequenceId != -1) {
        seqId = gSequenceId;
        if (loopCount == -1) {
            SsSetLoop(seqId, 0, 0);
        } else {
            SsSetLoop(seqId, 0, loopCount);
        }
    }
}

void SoundPauseSequence(void) {
    if (gSequenceId != -1)
        SsSeqPause(gSequenceId);
}

void SoundPlaySequence(s8 playCount, u8 playMode) {
    s16 count;

    if (gSequenceId != -1) {
        if (playCount == -1) {
            count = 0;
        } else {
            count = playCount;
        }
        SsSeqPlay(gSequenceId, playMode != 0, count);
    }
}

void SoundReplaySequence(void) {
    if (gSequenceId != -1) {
        SsSeqReplay(gSequenceId);
    }
}

extern void SsSeqSetVol(short seqAccessNum, short leftVolume,
                        short rightVolume);

void SoundSetSequenceVolume(u8 leftVolume, u8 rightVolume) {
    if (gSequenceId != -1) {
        if (leftVolume == 0) {
            leftVolume = 1;
        }
        if (rightVolume == 0) {
            rightVolume = 1;
        }
        SsSeqSetVol(gSequenceId, leftVolume, rightVolume);
    }
}

void SoundStopSequence(void) {
    if (gSequenceId != -1)
        SsSeqStop(gSequenceId);
}

extern s32 SpuGetKeyStatus(s32);

extern s16 D_800B9E24[];
extern s32 SpuGetKeyStatus(s32);

s32 func_8003F4FC(s32 arg0) {
    s16 voice;
    s32 status;

    voice = D_800B9E24[(s8)arg0 * 6];
    if (voice != -1) {
        status = SpuGetKeyStatus(1 << voice);
        if (status == 1) {
            return 1;
        }
        return status != 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8003F564);

INCLUDE_ASM("asm/nonmatchings/game", func_8003F914);

#ifdef NON_MATCHING
/* Wall: gcc hoists the D_800B9E24 base into s2 across the loop; retail
 * re-materializes lui per iteration. Extra callee-saved reg shifts the
 * stack frame. */
extern s16 D_800B9E24[];
extern void func_8003F914(s8);

void func_8003FA0C(void) {
    s8 i;

    i = 0;
    do {
        if (D_800B9E24[(u8)i * 6] != -1) {
            func_8003F914(i);
        }
        i++;
    } while ((u8)i < 0x18);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003FA0C);
#endif

/* w9e draft: decision tree matches retail exactly (incl. switch-style
 * beq arms for 0x2A/0x2B/0x2C/0x2D/0x29 and the dead 0x29 arm); only
 * preset (ours t1, retail a0) and the raw entry index (ours a0, retail
 * t1) are swapped. gcc refuses to move arg0 out of a0 unless the param
 * itself is assigned, and assigning it rehomes arg1 as well. Round 5
 * (preset declared first) segfaulted cc1. */
#ifdef NON_MATCHING
extern u8 D_800A3880;
extern s16 D_800B9E24[];
extern u8 D_800B9E26[];
extern s16 D_800B9E2A[];
extern s32 SsUtPitchBend(s16, s16, s8, s16, s8);

void func_8003FA84(s32 arg0, s32 arg1, s8 arg2) {
    s32 voice;
    s16 preset;
    u8 t;
    s32 v;

    voice = arg0;
    preset = D_800B9E24[(s8)voice * 6];
    if (preset == -1) {
        return;
    }
    t = D_800B9E26[(s8)voice * 12];
    if (D_800A3880 != 0) {
        arg2 = ((s8)voice == 1) ? 0xF : 0;
    } else {
        v = (s8)t;
        if (v >= 0x40) {
            arg2 = 0xA;
        } else if (v >= 0x20) {
            if (v >= 0x2C) {
                switch (v) {
                case 0x2C:
                    arg2 = 0x24;
                    break;
                case 0x2D:
                    arg2 = 0x26;
                    break;
                case 0x29:
                    arg2 = 0x29;
                    break;
                default:
                    break;
                }
                arg2 -= 0x20;
            } else if (v < 0x2A) {
                arg2 = t - 0x20;
            } else {
                switch (v) {
                case 0x2A:
                    arg2 = 0x12;
                    break;
                case 0x2B:
                    arg2 = 0x13;
                    break;
                default:
                    break;
                }
            }
        } else if ((u32)(t - 0xC) < 4) {
            arg2 = 0x1A - t;
        } else {
            arg2 = 0xF;
        }
    }
    SsUtPitchBend(preset, gVabId, arg2, D_800B9E2A[(s8)voice * 6], (s8)arg1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003FA84);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8003FC0C);

#ifdef NON_MATCHING
/* Wall: retail's unsigned /127 expansion is mult 0x81020409 (SIGNED
 * mult) + mfhi + addu of the dividend + srl 6, with NO sra31/subu
 * sign fixup; our gcc emits either the full signed expansion or the
 * multu 0x02040811 variant, never this hybrid. */
void func_8003FDE8(s8 arg0, s32 arg1, s32 arg2) {
    s16 voice;
    s32 volL;
    s32 volR;

    voice = D_800B9E24[(s8)arg0 * 6];
    if (voice != -1) {
        volL = ((arg1 & 0xFF) * D_800A2F94) / 127U;
        volR = ((arg2 & 0xFF) * D_800A2F94) / 127U;
        if ((u32)(volL & 0xFFFF) >= 0x80U) {
            volL = 0x7F;
        }
        if ((u32)(volR & 0xFFFF) >= 0x7FU) {
            volR = 0x7F;
        }
        SsUtSetVVol(voice, volL, volR);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003FDE8);
#endif

#ifdef NON_MATCHING
/* Wall: gcc hoists the D_800B9E24 base into a 4th callee-saved reg; retail
 * re-materializes lui per iteration with only s0/s1/s2 live. */
extern s16 D_800B9E24[];
extern void SpuGetAllKeysStatus(u8 *);
extern void func_8003F914(s8);

void func_8003FEB8(void) {
    s8 keys[24];
    s8 *keyState;
    s8 i;
    s16 voice;

    SpuGetAllKeysStatus(keys);
    keyState = keys;
    i = 0;
    do {
        voice = D_800B9E24[i * 6];
        if (voice != -1 && keyState[voice] == 3) {
            func_8003F914(i);
        }
        i++;
    } while (i < 0x18);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003FEB8);
#endif

extern char D_8008D1A8[];
extern char D_8008D1C4[];

s16 func_8003FF5C(void *arg0, void *arg1) {
    s16 vabId;
    s16 result;

    vabId = SsVabOpenHead(arg0, -1);
    if (vabId == -1) {
        SystemShowFatalError(D_8008D1A8);
    } else {
        result = SsVabTransBody(arg1, vabId);
        if (result == vabId) {
            SsVabTransCompleted(1);
            return result;
        }
        SystemShowFatalError(D_8008D1C4);
    }
    return -1;
}

#ifdef NON_MATCHING
/* w6f draft: file loader. Shape, length and scheduling all match; ONLY
 * the s1/s2 homes swap (gcc gives the arg1 copy s2 and handle s1,
 * retail the reverse). Tried: declaration orders, K&R definition,
 * explicit buffer local assigned first. Notes:
 * - D_800A2F98 itself is untracked in sdata (declaring it shifts the
 *   sdata labels, see matching.md); reached here as the already-aliased
 *   D_800A2F9CAbsolute minus 4, which folds into %lo identically.
 * - Block-scope FULL prototypes for func_8003C8BC/func_8003C63C are
 *   REQUIRED: the TU's 1-arg/0-arg definitions silently drop the
 *   caller-side argument setups (a1/a2 constants, a0 for C63C) and the
 *   function comes out 0x18 short.
 * - size + 0x800 - size % 0x800 folds algebraically; a padded temp
 *   (padded = size + 0x800; size = padded - size % 0x800) reproduces
 *   retail's addiu v1,s0,0x800 in the bgez delay slot + subu s0,v1,v0. */
extern char D_8008D1DC[];
extern char D_8008D1F8[];
extern u8 D_800A2F9CAbsolute[];

void *func_8003FFF0(s32 arg0, void *arg1) {
    extern s32 func_8003C8BC(void *, s32, s32);
    extern void func_8003C63C(s32);
    void *buffer;
    void *handle;
    s32 padded;
    s32 size;

    buffer = arg1;
    handle = func_8003C584(arg0, (char *)D_800A2F9CAbsolute - 4);
    if (handle == NULL) {
        SystemShowFatalError(D_8008D1DC);
    }
    size = func_8003C8BC(handle, 0, 2);
    func_8003C8BC(handle, 0, 0);
    padded = size + 0x800;
    size = padded - size % 0x800;
    if (buffer == NULL) {
        buffer = HeapAlloc(size);
        if (buffer == NULL) {
            SystemShowFatalError(D_8008D1F8);
        }
    }
    func_8003C644((s32)buffer, 1, size, handle);
    func_8003C63C((s32)handle);
    return buffer;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8003FFF0);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008D21C);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008D228);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008D234);
#endif

extern s32 D_80098D00[];
extern u8 D_800A354C[];
extern s32 D_800BE988[];
extern u8 D_800A2FA4[];
extern u8 D_800A39D0;
extern u8 D_800BA048[];

void func_800400D8(s32 arg0) {
    volatile s32 pad[4];
    s32 i;
    u8 next;

    i = 0;
    do {
        if (D_80098D00[i] == arg0) {
            goto found;
        }
        i++;
    } while (i < 4);
    i = 0;
    do {
        if (D_80098D00[i] == 0) {
            goto empty;
        }
        i++;
    } while (i < 4);
    next = D_800A39D0;
    D_800A39D0 = next + 1;
    *(s32 *)((u8 *)D_800BA048 + (((s32)(s8)next << 24) >> 22)) = arg0;
    return;
found:
    D_800A354C[i] = 1;
    return;
empty:
    D_80098D00[i] = arg0;
    D_800BE988[i] = -1;
    D_800A354C[i] = 1;
    D_800A2FA4[i] = 5;
}

extern s8 D_800A2FA4B[] asm("D_800A2FA4.NON_MATCHING");
extern s32 D_800BE988[];
extern s32 D_80098D00[];
extern s8 D_800A354CB[] asm("D_800A354C.NON_MATCHING");
extern s32 D_800BA048B[] asm("D_800BA048.NON_MATCHING");
extern s8 D_800A39D0B asm("D_800A39D0.NON_MATCHING");
void func_800401B8(void) {
    s32 i;
    s32 initialized;
    i = 0;
    initialized = 0;
    while (i < 4) {
        if (D_800A354CB[i] == 0 && D_800A2FA4B[i] == 0) {
            D_800A354CB[i] = 1;
            D_80098D00[i] = D_800BA048B[initialized];
            D_800BE988[i] = -1;
            D_800A2FA4B[i] = 5;
            initialized++;
            if (initialized == D_800A39D0B)
                break;
        }
        i++;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80040260);

extern s32 D_800BE890w16[] asm("D_800BE890.NON_MATCHING");
extern u8 D_80098C00w16[] asm("D_80098C00.NON_MATCHING");
extern u8 D_800A306Cw16[] asm("D_800A306C.NON_MATCHING");
extern void func_8001F90C(s32, s32, s32, s16 *);
extern void func_8003F564(s8, s8);
extern void func_8003FDE8(s8, s32, s32);

void func_800406D0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    extern u8 D_800A2F9DSmall;
    u8 *car;
    u8 *obj;
    register s32 camX asm("s1");
    register s32 camY asm("s3");
    register s32 camZ asm("s6");
    register s32 dx asm("s2");
    register s32 dy asm("s1");
    register s32 dz asm("s0");
    s32 dist;
    register s32 sum asm("a0");
    register s32 dySq asm("v1");
    register s32 square asm("t1");
    register s32 rowA asm("v0");
    register s32 rowB asm("v0");
    register s32 rowC asm("v0");
    register s32 fog asm("s3");
    register s32 scaled asm("v0");
    register s32 magic asm("v1");
    register s32 hi asm("t0");
    register s32 quot asm("v1");
    s32 sign;
    s32 gate;
    s16 out[2];
    s32 pan;
    register s32 q asm("a1");
    register s32 gain asm("a0");
    register s32 prodA asm("v1");
    s32 spread;
    register s32 prodB asm("t1");
    register s32 vol1 asm("s1");
    register s32 vol2 asm("s2");

    asm volatile("");
    camX = *(s32 *)(arg0 + 0);
    camY = *(s32 *)(arg0 + 4);
    gate = D_800A2F9DSmall;
    camZ = *(s32 *)(arg0 + 8);
    car = arg0;
    obj = arg1;
    if (gate == 0) {
        return;
    }
    if (D_800A2EC0nm[0] - D_800BE890w16[0] < 10) {
        return;
    }
    D_800BE890w16[0] = D_800A2EC0nm[0];
    if (func_8003702C(car, obj) < 0) {
        if (-func_8003702C(car, obj) >= 0x29) {
            goto fail;
        }
    } else {
        if (func_8003702C(car, obj) >= 0x29) {
        fail:
            func_8003FDE8((s8)arg2, 0, 0);
            return;
        }
    }
    rowA = *(s32 *)(obj + 0);
    dx = (rowA - camX) >> 4;
    asm volatile("mult\t%0,%0" : : "r"(dx));
    rowB = *(s32 *)(obj + 4);
    asm volatile("mflo\t%0" : "=r"(sum));
    dy = (rowB - camY) >> 4;
    asm volatile("mult\t%0,%0" : : "r"(dy));
    rowC = *(s32 *)(obj + 8);
    asm volatile("mflo\t%0" : "=r"(dySq));
    dz = (rowC - camZ) >> 4;
    asm volatile("mult\t%0,%0" : : "r"(dz));
    sum = sum + dySq;
    asm volatile("mflo\t%0" : "=r"(square));
    dist = MathSqrt(sum + square);
    magic = 0x5D9F0000;
    if (dist >= 0x579) {
        func_8003FDE8((s8)arg2, 0, 0);
        return;
    }
    magic = magic | 0x7391;
    scaled = (dist << 8) - dist;
    asm volatile("mult\t%0,%1" : : "r"(scaled), "r"(magic));
    sign = scaled >> 31;
    asm volatile("mfhi\t%0" : "=r"(hi));
    quot = hi >> 9;
    fog = quot - sign;
    if (fog >= 0x100) {
        fog = 0xFF;
    }
    func_8001F90C((0x400 - *(s16 *)(car + 0x114)) & 0x3FF, dx, dy, out);
    pan = out[1];
    if (pan > 0) {
        q = MathFixedDivide(pan, dist);
        gain = D_80098C00w16[fog];
        prodA = (q + 0x10000) * gain;
        spread = 0x10000 - q;
        asm volatile("mult\t%0,%1" : : "r"(spread), "r"(gain));
        vol2 = prodA >> 16;
        asm volatile("mflo\t%0" : "=r"(prodB));
        vol1 = prodB >> 16;
    } else {
        if (pan < 0) {
            pan = -pan;
        }
        q = MathFixedDivide(pan, dist);
        gain = D_80098C00w16[fog];
        prodA = (q + 0x10000) * gain;
        spread = 0x10000 - q;
        asm volatile("mult\t%0,%1" : : "r"(spread), "r"(gain));
        vol1 = prodA >> 16;
        asm volatile("mflo\t%0" : "=r"(prodB));
        vol2 = prodB >> 16;
    }
    if (vol2 >= 0x65) {
        vol2 = 0x64;
    }
    if (vol1 >= 0x65) {
        vol1 = 0x64;
    }
    if (D_800A306Cw16[0] != 0) {
        if (vol1 < vol2) {
            vol1 = vol2;
        } else {
            vol2 = vol1;
        }
    }
    func_8003F564((s8)arg2, (s8)arg3);
    func_8003FDE8((s8)arg2, (u8)vol2, (u8)vol1);
}

#ifdef NON_MATCHING
/* Walls: gcc hoists the D_800A3554 base address into callee-saved s1
 * (retail re-materializes lui/lw at each site) and converts the
 * id=0x14/0x15 select into a branchless xor/sltu/negu/andi/ori chain;
 * retail keeps bne + li/li. Frame 0x20 vs 0x18 from the s1 save. The
 * div guard sequence, call shapes and field accesses otherwise match. */
extern u8 D_800A2F9D;
extern s32 D_800A2EA4[];
extern void func_8003FC0C(s32, s32, s32);
extern void func_8003F564(s32, s32);

void func_800409A0(u8 *object) {
    s32 id;

    if (D_800A2F9D == 0) {
        return;
    }
    if (object == D_800A3554[0]) {
        id = 0x14;
    } else {
        id = 0x15;
    }
    func_8003FC0C(
        id, (s8)(*(s16 *)(object + 0x92) * 8 / *(s16 *)(object + 0x9A) + 0x2C),
        0);
    if (*(s8 *)(object + 0x3B8) == 0) {
        if (object == D_800A3554[0]) {
            func_8003F564(0x14, 2);
        } else if (object == *(u8 **)(D_800A3554[0] + 0x3E0) &&
                   D_800A2EA4[0] == 2) {
            func_8003F564(0x15, 2);
        }
    }
    *(u8 *)(object + 0x3B9) = 1;
    if (*(s16 *)(object + 0x120) != 0) {
        *(u8 *)(object + 0x3B8) = 0x17;
    }
    *(u8 *)(object + 0x3B8) = *(u8 *)(object + 0x3B8) + 1;
    if ((s8) * (u8 *)(object + 0x3B8) >= 0x19) {
        *(u8 *)(object + 0x3B8) = 0x18;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800409A0);
#endif

void func_80040AC0(u8 *object) {
    object[0x3B9] = 0;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80040AC8);

INCLUDE_ASM("asm/nonmatchings/game", func_80040CF4);

extern s32 D_800A2EA4[];
extern u8 D_800A2F9D;
extern u8 D_800A2FA8;

void func_80041328(void) {
    if (D_800A2F9D == 0) {
        func_8003FDE8(0, 0, 0);
        if (D_800A2EA4[0] == 2) {
            func_8003FDE8(1, 0, 0);
        }
    } else if (D_800A2FA8 == 0) {
        D_800A2FA8 = 1;
        func_8003FDE8(0, 0x38, 0x38);
        if (D_800A2EA4[0] == 2) {
            func_8003FDE8(1, 0x38, 0x38);
        }
    }
}

extern u8 D_800A2FA8;
extern void func_8003FDE8(s8, s32, s32);
void func_800413C0(void) {
    s32 i;
    if (D_800A2FA8) {
        D_800A2FA8 = 0;
        for (i = 0; i < 5; i++)
            func_8003FDE8((s8)i, 0, 0);
    }
}

void func_80041414(void) {
    extern u8 D_800A2F9C;
    D_800A2F9C = !D_800A2F9C;
}

extern u8 D_800A2F9D;

void func_8004142C(void) {
    D_800A2F9D = D_800A2F9D == 0;
}

void func_80041444(s32 arg0) {
    s32 i;

    for (i = 0; i < 0x14; i++) {
        func_8003FDE8((s8)i, 0, 0);
    }
    if ((arg0 & 0xFF) != 0) {
        func_8003FDE8(0x14, 0, 0);
        func_8003FDE8(0x15, 0, 0);
    }
    func_8003FDE8(0x16, 0, 0);
    func_8003FDE8(0x17, 0, 0);
}

extern s32 D_800A2EC8[];
extern s32 D_800A359C[];
extern void func_8003F564(s8, s8);
extern void func_8003FDE8(s8, s32, s32);
extern u8 D_800A2F9D;

void func_800414E0(void *arg0, s32 arg1, s32 arg2) {
    if (D_800A2F9D == 0) {
        if (D_800A2EC8[0] == 0)
            return;
        if (arg2 == 6)
            goto active;
        if (arg2 != 3)
            return;
    }
active:
    if (D_800A359C[0] != 0)
        return;
    func_8003F564((s8)arg1, (s8)arg2);
    func_8003FDE8((s8)arg1, 0x72, 0x72);
}

void func_80041564(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern u8 D_800A2EDC[];
    extern u8 D_800A2F9D;
    extern s32 D_800A397C[];
    extern u8 *D_800A3554[];
    extern s32 D_800A2EA4[];
    extern s32 D_800A2EC0Absolute[];
    extern u8 D_800A38B0[];
    extern s32 D_800A2E90[];
    extern s32 D_800A2EB0Absolute[];
    extern u8 D_800A2EE0[];
    extern s32 D_800A2EACAbsolute[];
    extern s32 D_800BE86C[];
    extern void func_80025594();
    extern void func_8003F564(s8, s8);
    extern void func_8003FDE8(s8, s32, s32);
    s32 timer;
    s32 *base;
    s32 *slot;

    arg2 = 15;
    arg3 = -1;
    if (((u8 *)D_800A2EDC)[-2] != 0) {
        return;
    }
    if (D_800A2F9D == 0) {
        return;
    }
    if (D_800A397C[0] == 2) {
        return;
    }
    if (*(u8 *)(D_800A3554[0] + 0xF4) == 0 && D_800A2EA4[0] == 0) {
        return;
    }
    timer = D_800A2EC0Absolute[0];
    switch (arg1) {
    case 0x41:
        if (*(s32 *)(arg0 + 0x28C) == 0) {
            return;
        }
        arg3 = 0x4B0;
        arg2 = 0;
        break;
    case 0x44:
        arg3 = 0x14;
        arg2 = 3;
        break;
    case 0x42:
        arg3 = 0xC8;
        arg2 = 2;
        break;
    case 0x48:
        if (*(s32 *)(arg0 + 0x28C) == 0) {
            return;
        }
        arg3 = 0x438;
        arg2 = 1;
        break;
    case 0x43:
        if (*(u8 *)(arg0 + 0xF4) == 0) {
            return;
        }
        /* falls through */
    case 0x40:
    case 0x45:
    case 0x46:
    case 0x47:
        arg2 = 4;
        break;
    case 0x2A:
    case 0x2B:
        arg3 = 0x14;
        arg2 = 5;
        break;
    case 0x27:
        arg3 = 0x7D0;
        arg2 = 5;
        break;
    case 0x25:
        if (*(s32 *)(arg0 + 0x90) <= 0xC7FFFF) {
            return;
        }
        arg3 = 0x12C;
        arg2 = 5;
        break;
    case 0x26:
        if (*(s32 *)(arg0 + 0x354) != (s32)func_80025594) {
            return;
        }
        if (D_800A38B0[0] != 0) {
            return;
        }
        arg2 = 0xF;
        arg3 = 0x190;
        arg1 += *(s32 *)((u8 *)D_800A2EACAbsolute + 0x14) & 1;
        break;
    case 0x24:
        if (D_800A2E90[0] < 6) {
            return;
        }
        /* falls through */
    case 0x23:
        arg3 = 0x708;
        arg2 = 6;
        break;
    case 0x21:
        arg3 = 0;
        if (D_800A2EB0Absolute[0] != 0) {
            return;
        }
        goto setSeven;
    case 0x22:
        arg3 = 0;
        if (D_800A2EB0Absolute[0] == 1) {
            return;
        }
    setSeven:
        asm("");
        arg2 = 7;
        break;
    case 0x28:
        arg3 = 0;
        arg2 = 7;
        if (*(u8 *)(arg0 + 0xF4) == 0) {
            return;
        }
        if (D_800A2EB0Absolute[0] == 1) {
            return;
        }
        break;
    case 0x29:
        if (D_800A2EB0Absolute[0] != 0) {
            return;
        }
        if (D_800A2EE0[0] != 0) {
            return;
        }
        if ((*(u16 *)(arg0 + 0x3A4) & 0xF) == 0) {
            return;
        }
        if (*(u8 *)(arg0 + 0xF4) == 0) {
            return;
        }
        arg3 = 0x12C;
        arg2 = 8;
        break;
    }
    if (D_800A2EACAbsolute[0] != 0) {
        if (arg2 < 2) {
            return;
        }
        if (arg1 == 0x25) {
            return;
        }
    }
    base = D_800BE86C;
    slot = base + arg2;
    if (*slot == -1 || arg3 < timer - *slot) {
        func_8003F564(0x12, (s8)arg1);
        func_8003FDE8(0x12, 0xFF, 0xFF);
        *slot = timer;
    }
}

void func_80041848(u8 *arg0, s32 arg1) {
}

/* Sound startup and shutdown. */

/* w6f WALL (cc1 ICE): adding any function with a branch statement (if,
 * if/else) near this position segfaults cc1 2.7.2 (cpp reports
 * "output pipe has been closed"; the object emits 0 symbols and the
 * link fails with hundreds of undefined references). Reproduced with a
 * 3-line `if` touching only pre-existing symbols, and with the same
 * probe inserted at other TU positions, so it is not positional. A
 * for-loop body in the same function compiled fine. Also reproducible:
 * the crash follows the statement stream, not one statement. Parked as
 * assembly. Draft that produced the near-miss shape (before the ICE
 * blocked iteration) is in kb/games/nascar98-us/notes-w6f.md. */
extern u8 D_8008D21C[];
extern u8 D_8008D228[];
extern u8 D_8008D234[];
extern u8 D_80098BEC[];
extern u8 D_80098BED[];
extern u8 D_80098BEE[];
extern s32 D_800BE8A8[];
extern s32 D_800A2FA0;
extern s32 D_800A2EB8NM[] asm("D_800A2EB8.NON_MATCHING");
extern void func_8003F060(s32);

void func_80041850(void) {
    s32 val;
    s32 i;
    s32 t;
    s32 *p;
    s32 msg;

    val = -1;
    i = 0xF;
    p = D_800BE8A8;
    do {
        *p = val;
        i -= 1;
        p -= 1;
    } while (i >= 0);
    D_800A2FA0 = 0;
    if (D_800A2EB8NM[0] != 0) {
        D_80098BEC[0] = 0x38;
        D_80098BED[0] = 0x36;
        D_80098BEE[0] = 0x40;
        if (RandomScaledGet(3) < 0) {
            t = -RandomScaledGet(3);
        } else {
            t = RandomScaledGet(3);
        }
        switch (t) {
        case 0:
            msg = (s32)D_8008D21C;
            break;
        case 1:
            msg = (s32)D_8008D228;
            break;
        case 2:
            msg = (s32)D_8008D234;
            break;
        default:
            return;
        }
        func_8003F060(msg);
    } else {
        func_8003F060(0x3E);
    }
}

extern void func_8003F284(void);
extern void func_8003F564(s8, s8);
extern void func_8003FDE8(s8, s32, s32);

void func_8004195C(void) {
    SsStart2();
    func_8003F284();
    func_8003F564(0, 0);
    func_8003FDE8(0, 0, 0);
    VSync(0);
    VSync(0);
    VSync(0);
    func_8003F564(1, 0xC);
    func_8003FDE8(1, 0, 0);
    func_8003F564(2, 0xD);
    func_8003FDE8(2, 0, 0);
    func_8003F564(3, 0xE);
    func_8003FDE8(3, 0, 0);
    func_8003F564(4, 0xF);
    func_8003FDE8(4, 0, 0);
}

extern u8 D_800A2F9D;
extern void func_8003FDE8(s8, s32, s32);
extern void SoundShutdown(void);
extern void SsSetMute(s32);

void func_80041A28(void) {
    s32 i;

    i = 0;
    do {
        func_8003FDE8((s8)i, 0, 0);
        i++;
    } while (i < 5);
    func_8003F2AC(0, 0);
    SoundSetSequenceVolume(0, 0);
    func_8003F23C();
    func_8003FA0C();
    SsSetMVol(0, 0);
    VSync(0);
    VSync(0);
    SoundShutdown();
    if (D_800A2F9D == 0) {
        SsSetMute(0);
    }
}

void func_80041AF0();
/* Controller state and input. */

void func_80041AD0(void) {
    func_80041AF0();
}

extern s32 gPadBuffers[];
extern u32 D_8008CA04[];
extern u32 D_8008CA08[];
extern u32 D_8008CA0C[];
extern u32 D_8008CA10[];
extern u32 D_8008CA14[];
extern u32 D_8008CA18[];
extern u32 D_8008CA1C[];
extern u32 D_8008CA20[];
extern u32 D_800B9DF8[];
extern u32 D_800B9E00[];
extern u32 D_800B9E04[];
extern void func_80041F54(s32 *, s32 *, s32, s32);

void func_80041AF0(void) {
    D_8008CA14[0] = 0xFFFF0000;
    D_8008CA18[0] = 0;
    D_8008CA1C[0] = 0xFFFF0000;
    D_8008CA20[0] = 0;
    D_8008CA04[0] = gPadBuffers[0];
    D_8008CA08[0] = D_800B9DF8[0];
    D_8008CA0C[0] = D_800B9E00[0];
    D_8008CA10[0] = D_800B9E04[0];
    func_80041F54(gPadBuffers, D_8008CA04, D_800B9DF8[0], D_800B9E00[0]);
}

extern u16 D_8008CA04U16[] asm("D_8008CA04.NON_MATCHING");
s32 func_80041B7C(s32 index) {
    return D_8008CA04U16[index * 4];
}

extern u16 D_8008CA04U16[] asm("D_8008CA04.NON_MATCHING");
u16 func_80041B94(s32 index) {
    return D_8008CA04U16[index];
}

extern s32 gPadBuffers[];

/* Wall: retail computes the nibble before the 0xFF branch and keeps it
 * in a0 with a final move v0,a0 on both paths; our shapes either go
 * branchless (xori/sltu/negu) or compute after the branch. */
u32 func_80041BAC(s32 arg0) {
    s32 temp;
    s32 result;

    if (arg0 < 0) {
        return 0;
    }
    temp = gPadBuffers[arg0 * 3];
    result = ((u32)(temp & 0xF000)) >> 12;
    if ((temp & 0xFF) == 0xFF) {
        asm("");
        result = 0;
    }
    return result;
}

#ifdef NON_MATCHING
/* Walls (w8e): entry test wants retail's bgez->body with the ret0 block
 * falling through inline (gcc emits bltz to an end-placed ret0 block);
 * retail's dead 8-byte frame is unexplained (s16 bank gives the frame
 * but turns the s8 load into lbu+sll/sra, +12); arm A wants srl24 before
 * the join jump with the 3C8 store shared after it (gcc sinks the store
 * into the arm, or with asm("") past the reloaded byte).
 * Matches except: entry branch layout, frame, srl24 placement,
 * nor operand order (r). D_8008CA08 needs the (u8 *) cast: live u32[]
 * decl at line ~6575 makes +bank*8 scale by 32. */
extern u8 D_8008CA06[];
extern u32 D_8008CA08[];
extern s8 D_800A3A24[];

u16 func_80041BFC(u8 *arg0) {
    s32 bank;
    u32 data;
    u16 pad;
    s32 mode;

    bank = *(s8 *)(arg0 + 0x20B);
    if (bank < 0) {
        return 0;
    }
    data = *(u32 *)((u8 *)D_8008CA08 + bank * 8);
    if (D_800A3A24[bank] == 2) {
        arg0[0x3C6] = data >> 8;
        arg0[0x3C7] = data >> 0x10;
        arg0[0x3C5] = data;
    } else {
        arg0[0x3C6] = data >> 8;
        arg0[0x3C5] = data >> 0x10;
        arg0[0x3C7] = data;
    }
    arg0[0x3C8] = data >> 0x18;
    pad = *(u16 *)(D_8008CA06 + *(s8 *)(arg0 + 0x20B) * 8);
    mode = ~(((pad & 0xFF) << 8) | (pad >> 8));
    if (mode & 0x1000) {
        mode |= 8;
    }
    if (mode & 0x4000) {
        mode |= 2;
    }
    if (mode & 0x2000) {
        mode |= 0x40;
    }
    if (mode & 0x8000) {
        mode |= 0x80;
    }
    return mode & 0xFFFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80041BFC);
#endif

extern s32 gPadBuffers[];
void InitPAD(void *, s32, void *, s32);
s32 StartPAD(void);
s32 VSync(s32);
void PadInitBuffers(void) {
    s32 *cursor;
    s32 wordCount;
    s32 emptyValue;
    cursor = gPadBuffers;
    emptyValue = -1;
    wordCount = 0xB;
    do {
        *cursor = emptyValue;
        wordCount -= 1;
        cursor += 1;
    } while (wordCount >= 0);
    InitPAD(gPadBuffers, 0xC, (u8 *)gPadBuffers + 0xC, 0xC);
    do {
    } while (StartPAD() == 0);
    ChangeClearPAD(0);
    VSync(0);
    VSync(0);
}

#ifdef NON_MATCHING
/* w6f: this w4b shape does NOT hold in the merged tree: both pad loads
 * hoist to the top, the pads+2 offsets fold into %lo, and the final or
 * operand order flips. Re-diff before trusting it. */
extern s32 gPadBuffers[];
extern u32 D_800B9E00[];

s32 func_80041D60(void) {
    volatile u16 pad1;
    volatile u16 pad2;
    u8 *pads;
    u16 value;
    u32 flags;

    pads = (u8 *)gPadBuffers;
    value = *(u16 *)(pads + 2);
    pad1 = ~(((value & 0xFF) << 8) | (value >> 8));
    pads += 0xC;
    value = *(u16 *)(pads + 2);
    flags = *(u32 *)gPadBuffers;
    pad2 = ~(((value & 0xFF) << 8) | (value >> 8));
    if ((flags & 0xF000) == 0) {
        pad1 = 0;
    }
    if ((D_800B9E00[0] & 0xF000) == 0) {
        pad2 = 0;
    }
    return ((u32)pad2 << 16) | pad1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80041D60);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80041DEC);

INCLUDE_ASM("asm/nonmatchings/game", func_80041F54);

INCLUDE_ASM("asm/nonmatchings/game", func_800420D8);

#ifdef NON_MATCHING
/* Wall (w4b): everything matches except retail's entry `move t1,a0`
 * param copy: our gcc 2.7.2 coalesces `src = arg0` (tried s32 param +
 * cast, K&R definition, walk-in-place). The copy frees a0, which retail
 * reuses for the (bits & 0x3C) temp; without it the OR chain lands in
 * v1/v0 homes and shift lands in t1 instead of t2. OR order is
 * X|Y|Z = FC00>>8 | 3C<<10 | 3C0<<14 (accumulator starts at X). */
void func_80042218(u8 *arg0, s32 *arg1, u8 *arg2) {
    u8 *src;
    u8 *dst;
    s32 i;
    s32 shift;
    u16 bits;

    src = arg0;
    dst = arg2;
    *arg1 = 0;
    i = 0;
    shift = -4;
    do {
        *(u32 *)dst = *(u16 *)src;
        bits = *(u16 *)(src + 2);
        *(u32 *)(dst + 4) = ((u32)((bits & 0xFC00) >> 8)) |
                            ((u32)((bits & 0x3C) << 10)) |
                            ((u32)((bits & 0x3C0) << 14));
        if (i >= 2) {
            *arg1 |= (bits & 3) << shift;
        }
        src += 4;
        dst += 8;
        i += 1;
        shift += 2;
    } while (i < 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80042218);
#endif

s32 func_8004229C(s32 arg0) {
    s32 var_v0;
    u32 temp_a0;

    temp_a0 = arg0 & 0xFF;
    if (temp_a0 == 2) {
        var_v0 = 1;
    } else {
        if (temp_a0 < 5U) {
            var_v0 = 0;
            return var_v0;
        }
        var_v0 = 1;
    }
    return var_v0;
}

INCLUDE_ASM("asm/nonmatchings/game", func_800422C0);

INCLUDE_ASM("asm/nonmatchings/game", func_80042508);

INCLUDE_ASM("asm/nonmatchings/game", func_80042920);

extern s32 gRandomSeed16;

/* Scene effects and random numbers. */

u32 RandomGetScaled16(s32 arg0) {
    s32 value0;

    value0 = ((gRandomSeed16 * 0x6255) + 0x3619) & 0xFFFF;
    do {
        gRandomSeed16 = value0;
        return (u32)(value0 * arg0) >> 0x10;
    } while (0);
}

extern u8 D_800AD9CC[];
void func_80043D6C(void);
void func_80042EC0(void) {
    s32 offset;
    offset = 0x750;
    do {
        D_800AD9CC[offset] = 0;
        offset -= 0x30;
    } while (offset >= 0);
    func_80043D6C();
}

INCLUDE_ASM("asm/nonmatchings/game", func_80042EFC);

INCLUDE_ASM("asm/nonmatchings/game", func_800432C0);

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void MulRotMatrix(MATRIX *matrix);
extern void func_800328AC(void *arg0, s32 arg1);
extern void func_80044BCC(s32 arg0);

void func_800436D0(u8 *object) {
    SVECTOR input;
    VECTOR trans;
    MATRIX matrix;
    long lvm[18];
    s32 *camera;
    u8 *node;
    s16 angle1;
    s16 angle2;

    PushMatrix();
    camera = (s32 *)D_800A38AC[0];
    input.vx = *(s32 *)(object + 0) - camera[0];
    input.vy = *(s32 *)(object + 4) - camera[1];
    input.vz = *(s32 *)(object + 8) - camera[2];
    RotTrans(&input, &trans, &lvm[16]);
    TransMatrix(&matrix, &trans);
    if (*(s8 *)(object + 0x1D) == 0xA) {
        input.vx = 0;
        input.vy = *(u16 *)(object + 0x18);
        input.vz = *(u16 *)(object + 0x16);
        RotMatrix(&input, &matrix);
        MulRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        SetRotMatrix(&matrix);
        func_80044BCC(*(s8 *)(object + 0x1E));
    } else {
        input.vx = 0;
        input.vy = 0;
        input.vz = *(u16 *)(object + 0x16);
        RotMatrix(&input, &matrix);
        MulRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        SetRotMatrix(&matrix);
        node = *(u8 **)(object + 0x2C);
        angle1 = *(s16 *)(node + 0x10);
        angle2 = *(s16 *)(node + 0x12);
        func_800328AC((void *)(*(u32 *)(object + 0x28) + angle1 * 44), angle2);
    }
    PopMatrix();
}

INCLUDE_ASM("asm/nonmatchings/game", func_8004382C);

INCLUDE_ASM("asm/nonmatchings/game", func_80043B68);

extern s32 gRandomSeed16;
extern u8 D_800B1A24[];
extern u8 D_800B1A25[];
extern u8 D_800B1A26[];
extern u8 D_800B1A26R[] asm("D_800B1A26.NON_MATCHING");

void func_80043D6C(void) {
    register s32 base asm("a3");
    register s32 m3base asm("s2");
    register s32 m3 asm("t5");
    register s32 m1 asm("t9");
    register s32 m2 asm("t6");
    register s32 d1 asm("s1");
    register s32 d2 asm("s0");
    register s32 d3 asm("t8");
    register s32 d4 asm("t7");
    s32 value;
    register s32 temp asm("a0");
    s32 value2;
    s32 masked;
    register s32 value3 asm("$2");
    s32 prod;
    s32 prodlo;
    register s32 rowOff asm("t4");
    s32 end;
    register s32 midOff asm("t1");
    register s32 mo asm("t0");
    register s32 colOff asm("a1");
    s32 off1;
    s32 off2;
    s32 off3;
    register s32 i asm("t3");
    register s32 j asm("t2");

    i = 0;
    base = 9;
    do {
        j = 0;
        asm volatile("" ::"r"(j));
        rowOff = i * 0x40;
        asm volatile("sll %0, %1, 3" : "=r"(m3base) : "r"(i));
        asm volatile("addu %0, %1, $zero" : "=r"(d1) : "r"(base));
        asm volatile("addu %0, %1, $zero" : "=r"(d2) : "r"(base));
        asm volatile("addu %0, %1, $zero" : "=r"(m1) : "r"(base));
        asm volatile("addu %0, %1, $zero" : "=r"(d3) : "r"(base));
        midOff = 0;
        do {
            asm volatile("addu %0, %1, $zero" : "=r"(mo) : "r"(midOff));
            asm volatile("addu %0, %1, $zero" : "=r"(d4) : "r"(base));
            asm volatile("addu %0, %1, $zero" : "=r"(m2) : "r"(base));
            asm volatile("addiu %0, %1, 8" : "=r"(m3) : "r"(m3base));
            colOff = rowOff;
            do {
                temp = gRandomSeed16;
                asm volatile("addu %0, %1, %2"
                             : "=r"(off1)
                             : "r"(colOff), "r"(mo));
                value = (temp * 0x6255) + 0x3619;
                asm("andi %0, %1, 0xFFFF" : "=r"(masked) : "r"(value));
                gRandomSeed16 = masked;
                asm volatile("" ::: "memory");
                value &= 0xFFFF;
                value2 = ((value * 0x6255) + 0x3619) & 0xFFFF;
                gRandomSeed16 = value2;
                asm volatile("" ::: "memory");
                D_800B1A24[off1] = -(s32)((u32)(value2 * m1) >> 16);
                temp = gRandomSeed16;
                asm volatile("addu %0, %1, %2"
                             : "=r"(off2)
                             : "r"(colOff), "r"(mo));
                value = (temp * 0x6255) + 0x3619;
                asm("andi %0, %1, 0xFFFF" : "=r"(masked) : "r"(value));
                gRandomSeed16 = masked;
                asm volatile("" ::: "memory");
                value &= 0xFFFF;
                value2 = ((value * 0x6255) + 0x3619) & 0xFFFF;
                gRandomSeed16 = value2;
                asm volatile("" ::: "memory");
                D_800B1A25[off2] = -(s32)((u32)(value2 * m2) >> 16);
                temp = gRandomSeed16;
                value3 = ((temp * 0x6255) + 0x3619) & 0xFFFF;
                gRandomSeed16 = value3;
                asm volatile("" ::: "memory");
                asm volatile("mult %0, %1"
                             :
                             : "r"(value3), "r"(m3)
                             : "lo", "hi");
                asm volatile("addu %0, %1, %2"
                             : "=r"(off3)
                             : "r"(colOff), "r"(mo));
                colOff += 4;
                asm volatile("mflo %0" : "=r"(prodlo));
                D_800B1A26R[off3] = (s32)((u32)prodlo >> 16);
                asm volatile("addiu %0, %1, 0x40" : "=r"(end) : "r"(rowOff));
            } while (colOff < end);
            asm("" ::"r"(d4));
            j += 1;
            midOff += 0xC0;
        } while (j < 6);
        asm("" ::"r"(d1));
        asm("" ::"r"(d2));
        asm("" ::"r"(d3));
        i += 1;
        base += 9;
    } while (i < 3);
}

INCLUDE_ASM("asm/nonmatchings/game", func_80043F7C);

#ifdef NON_MATCHING
/* Wall: the loop-1 walker init folds to move (retail keeps addu a0,v1
 * with v1=0); loop-2 strength reduction goes negative-offset. Also:
 * tail load/store of D_800A3960 CSEs into one lui/addiu base across the
 * branch (asm("") does NOT block it); retail has lui+lw %lo then a
 * second lui $at+sw. */
extern u8 D_800A2EE0[];
extern u32 D_800A3960[];

void func_80044114(u8 *arg0) {
    s32 i;
    u8 *slot;
    s32 j;
    u8 *entry;

    *(s16 *)(arg0 + 0x3A4) = 0;
    i = 0;
    slot = arg0;
    do {
        i++;
        slot[0x3A6] = 1;
        slot[0x3AE] = 0;
        slot = arg0 + i;
    } while (i < 8);
    if (D_800A2EE0[0] != 0) {
        *(s16 *)(arg0 + 0x1BC) = 3;
        j = 0;
        entry = arg0;
        do {
            *(s16 *)(entry + 0x2AC) = 0;
            *(s16 *)(entry + 0x2B0) = 0;
            j++;
            entry += 0x28;
        } while (j < 4);
        *(s16 *)(arg0 + 0x10C) = 0;
    }
    if (arg0 == (u8 *)D_800A3960[0]) {
        D_800A3960[0] = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80044114);
#endif

void func_8004419C(u8 *object) {
    s32 i;
    *(volatile s16 *)(object + 0x1BC) = 3;
    for (i = 0; i < 4; i++) {
        *(volatile s16 *)(object + 0x2AC) = 0;
        *(volatile s16 *)(object + 0x2B0) = 0;
        object += 0x28;
    }
}

typedef struct {
    u32 w[12];
} CopyRow30;

extern CopyRow30 D_800AD9B0[];
extern CopyRow30 D_800BBAAC[];
extern void func_800364C4(void);
void func_800441C8(void) {
    s32 row;
    func_800364C4();
    for (row = 0; row < 0x28; row++) {
        D_800BBAAC[row] = D_800AD9B0[row];
    }
}

extern void func_80036540(void);

void func_80044248(void) {
    s32 row;
    func_80036540();
    for (row = 0; row < 0x28; row++) {
        D_800AD9B0[row] = D_800BBAAC[row];
    }
}

extern u8 D_800A2EDC[];

void func_800442C8(u8 *arg0, u8 *arg1) {
    u32 bits;
    s32 i;

    bits = *(u32 *)(arg1 + 8);
    if (D_800A2EDC[0] != 0) {
        i = 0;
        do {
            if ((*(u16 *)(arg1 + 0xC) >> i & 1) != 0) {
                *(u8 *)(arg0 + 0x3A6 + i) = 0;
            } else {
                *(u8 *)(arg0 + 0x3A6 + i) = 1;
            }
            i++;
        } while (i < 8);
        arg0[0x3AE] = (bits & 0x3FFF) >> 12;
        arg0[0x3AF] = (bits & 0xFFF) >> 10;
        arg0[0x3B0] = (bits & 0x3FF) >> 8;
        arg0[0x3B1] = (bits & 0xFF) >> 6;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80044354);

INCLUDE_ASM("asm/nonmatchings/game", func_80044594);

extern u32 D_8009B9C4[];
extern u8 *gHeapBase, *gHeapBreak;
extern s8 gHeapInit;
void HeapInit(void) {
    if (gHeapBase == NULL) {
        gHeapBase = (u8 *)D_8009B9C4[0];
    }
    gHeapInit = 1;
    gHeapBreak = gHeapBase;
}

extern s8 gHeapInit;
void HeapResetInitFlag(void) {
    gHeapInit = 0;
}

/* Heap management. */

typedef struct HeapBlock {
    u32 size; /* payload size in bytes; bit 0 set while the block is free */
} HeapBlock;

extern u32 D_8009B9C4[]; /* heap start address, stored by the startup code */
extern u8 *gHeapBase;
extern s8 gHeapInit;
extern u8 gHeapBigAllocFlag;
extern u8 *gHeapBreak;

/*
 * First-fit allocator. Each block starts with a header word holding the
 * payload size; bit 0 is set while the block is free. A free block splits
 * when the remainder can hold a header and 0x20 bytes.
 */
void *HeapAlloc(u32 size) {
    u32 *block;
    u32 *result;
    u32 hdr;
    u8 found;

    if (gHeapInit == 0) {
        if (gHeapBase == NULL) {
            gHeapBase = (u8 *)D_8009B9C4[0];
        }
        gHeapInit = 1;
        gHeapBreak = gHeapBase;
    }
    size += 3;
    size = size / 4 * 4;
    switch (size) {
    case 0x3D18:
    case 0x4168:
        gHeapBigAllocFlag = 1;
        break;
    }
    if (gHeapBase == gHeapBreak) {
        result = (u32 *)gHeapBase;
        *result++ = size;
        gHeapBreak = (u8 *)result + size;
    } else {
        block = (u32 *)gHeapBase;
        found = 0;
        while (found == 0 && block != (u32 *)gHeapBreak) {
            hdr = *block;
            if ((hdr & 1) != 0 && (hdr ^= 1) >= size) {
                found = 1;
            } else {
                block = (u32 *)((u8 *)block + (hdr + 4));
            }
        }
        if (found != 0) {
            if (hdr >= size + 0x24) {
                hdr -= size + 4;
                hdr |= 1;
                result = block + 1;
                *block = size;
                block = (u32 *)((u8 *)result + size);
                *block = hdr;
            } else {
                *block = hdr;
                result = block + 1;
            }
        } else {
            if ((u32)block + size + 4 > HEAP_LIMIT) {
                return NULL;
            }
            *block = size;
            result = block + 1;
            gHeapBreak = (u8 *)block + size + 4;
        }
    }
    return result;
}

u32 HeapFreeSpaceCount(void) {
    HeapBlock *block;
    u32 total;
    u32 size;

    total = 0;
    block = (HeapBlock *)gHeapBase;
    while (block != (HeapBlock *)gHeapBreak) {
        size = block->size;
        if (size & 1) {
            size ^= 1;
            total += size;
        }
        block = (HeapBlock *)((u8 *)block + (size + 4));
    }
    size = (HEAP_LIMIT - sizeof(HeapBlock)) - (u32)gHeapBreak;
    return total + size;
}

void HeapCoalesce(void) {
    u32 *cur;
    u32 *next;
    u8 *heapEnd;
    u32 size;
    u32 nextSize;
    u8 freeSeen;

    cur = (u32 *)gHeapBase;
    while (cur != (u32 *)gHeapBreak) {
        freeSeen = 0;
        heapEnd = gHeapBreak;
        if (cur == (u32 *)heapEnd) {
            return;
        }
        do {
            size = *cur;
            if (size & 1) {
                freeSeen = 1;
                size ^= 1;
            } else {
                cur = (u32 *)((u8 *)cur + size + 4);
            }
            if (cur == (u32 *)gHeapBreak) {
                return;
            }
        } while (freeSeen == 0);
        if (cur == (u32 *)gHeapBreak) {
            return;
        }
        next = (u32 *)((u8 *)cur + size + 4);
        if (next == (u32 *)gHeapBreak) {
            gHeapBreak = (u8 *)cur;
            return;
        }
        freeSeen = 1;
        while (freeSeen != 0 && next != (u32 *)gHeapBreak) {
            nextSize = *next;
            if (nextSize & 1) {
                nextSize ^= 1;
                size += 4 + nextSize;
                *cur = size | 1;
                next = (u32 *)((u8 *)cur + size + 4);
                if (next == (u32 *)gHeapBreak) {
                    gHeapBreak = (u8 *)cur;
                    break;
                }
            } else {
                freeSeen = 0;
            }
        }
        if (cur == (u32 *)gHeapBreak) {
            return;
        }
        cur = (u32 *)((u8 *)cur + size + 4);
    }
}

void HeapFree(void *ptr) {
    ((HeapBlock *)((u8 *)ptr - 4))->size |= 1;
    HeapCoalesce();
}

INCLUDE_ASM("asm/nonmatchings/game", func_80044A1C);

INCLUDE_ASM("asm/nonmatchings/game", func_80044BCC);

extern s32 D_800A39C8[];
extern u32 gPrimitiveCursor[];
extern u8 D_800A2DE0[];
extern void SetLineF4(u8 *prim);
extern void SetLineF2(u8 *prim);

void func_80044DC4(u8 *arg0, s32 arg1, u8 *arg2) {
    register u8 *prim asm("$18");
    register u8 *walker asm("$20");
    register u8 *pe asm("$17");
    register s32 count asm("$22");
    u8 *rgb;
    u8 g;
    u8 b;
    register u8 rv asm("$11");
    register u8 rtmp asm("$10");
    register s32 obt asm("$10");
    register u32 *a0arg asm("$4");
    register u32 *a1arg asm("$5");
    register u32 a2arg asm("$6");
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

    otBase = (s32)D_800A39C8[0] + 0x20;
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
            v0_ = *(s32 *)(walker - 0xC);
            v1_ = *(s32 *)(walker - 0x8);
            v2_ = *(s32 *)(walker - 0x4);
            asm volatile("lwc2 $0, 0x0(%0)\n\t"
                         "lwc2 $1, 0x4(%0)\n\t"
                         "lwc2 $2, 0x0(%1)\n\t"
                         "lwc2 $3, 0x4(%1)\n\t"
                         "lwc2 $4, 0x0(%2)\n\t"
                         "lwc2 $5, 0x4(%2)\n\t"
                         ".word 0\n\t"
                         ".word 0\n\t"
                         "rtpt"
                         :
                         : "r"(v0_), "r"(v1_), "r"(v2_));
            SetLineF4(prim);
            asm volatile("cfc2 %0, $31\n\t"
                         "nop"
                         : "=r"(gte));
            masked = gte & 0x66000;
            if (masked != 0) {
                goto next;
            }
            asm volatile(".word 0\n\t"
                         ".word 0\n\t"
                         "nclip");
            rv = r;
            *(u8 *)(pe - 0x9) = g;
            *(u8 *)(pe - 0x8) = b;
            *(u8 *)(pe - 0xA) = rv;
            asm volatile("mfc2 %0, $24\n\t"
                         "nop"
                         : "=r"(gte));
            if (D_800A2DE0[0] != 0) {
                if (gte < 0) {
                    goto next;
                }
            } else {
                if (gte > 0) {
                    goto next;
                }
            }
            asm volatile(".word 0\n\t"
                         ".word 0\n\t"
                         "avsz3\n\t"
                         "mfc2 %0, $7\n\t"
                         "nop"
                         : "=r"(gte));
            gte += (s32)(s8) * (walker - 0x23) * 4;
            asm volatile("swc2 $12, 0x0(%0)\n\t"
                         "swc2 $13, 0x0(%1)\n\t"
                         "swc2 $14, 0x0(%2)"
                         :
                         : "r"(prim + 8), "r"(prim + 0xC), "r"(prim + 0x10));
            w3 = *(s32 *)(walker);
            asm volatile("lwc2 $0, 0x0(%0)\n\t"
                         "lwc2 $1, 0x4(%0)\n\t"
                         ".word 0\n\t"
                         ".word 0\n\t"
                         "rtps"
                         :
                         : "r"(w3));
            asm volatile("swc2 $14, 0x0(%0)" : : "r"(prim + 0x14));
            otEntry = gte >> 4;
            otEntry = otEntry << 2;
            obt = otBase;
            otEntry = obt + otEntry;
            GraphicsAddTaggedPrimitive((u32 *)otEntry, (u32 *)prim, 0x06000000);
            prim += 0x1C;
            pe += 0x1C;
            SetLineF2(prim);
            xy0 = *(u16 *)(pe - 0x20);
            xy1 = *(u16 *)(pe - 0x16);
            xy2 = *(u16 *)(pe - 0x14);
            *(u8 *)(pe - 0xA) = rgb[0];
            xy3 = *(u16 *)(pe - 0x22);
            a0arg = (u32 *)otEntry;
            *(u8 *)(pe - 0x9) = rgb[1];
            btmp = rgb[2];
            asm volatile("lhu %0, -0x22(%1)" : "=r"(xy3) : "r"(pe));
            a1arg = (u32 *)prim;
            asm volatile("lui %0, 0x300" : "=r"(a2arg));
            prim += 0x10;
            *(u16 *)(pe - 0x4) = xy0;
            *(u16 *)(pe - 0x2) = xy1;
            *(u16 *)(pe + 0x0) = xy2;
            *(u16 *)(pe - 0x6) = xy3;
            *(u8 *)(pe - 0x8) = btmp;
            GraphicsAddTaggedPrimitive(a0arg, a1arg, a2arg);
            pe += 0x10;
        next:
            walker += 0x2C;
        } while (--count > 0);
    }
    gPrimitiveCursor[0] = (u32)prim;
}

extern s32 D_800A33F0;
extern s32 D_800A33F4;
extern s8 D_800A33F8;
extern s32 D_800A3400;
extern s32 D_800A3404;
extern s32 D_80098184[];
extern s32 D_80098134nm[] asm("D_80098134.NON_MATCHING");
extern s32 D_8009813Cnm[] asm("D_8009813C.NON_MATCHING");
extern u8 D_800A3880nm[] asm("D_800A3880.NON_MATCHING");

void func_80044FF8(s32 arg0, s32 arg1) {
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
        func_8003F564((s8)arg1, -(D_800A3880nm[0] != 0) & 7);
        func_8003FDE8((s8)arg1, 0x7F, 0x7F);
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
        func_8003F914((s8)arg1);
        return;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80045288);

INCLUDE_ASM("asm/nonmatchings/game", func_80045480);

INCLUDE_ASM("asm/nonmatchings/game", func_80045864);

extern u8 D_800A342C[];
extern s32 D_800A3430[];
extern u8 D_80090F32[];
extern u8 D_800991E8[];
extern u8 D_800991E9[];
extern u8 D_800991EA[];

#ifdef NON_MATCHING
/* Wall: size and instruction shape exact (0x214), but gcc pins the
 * HeapAlloc result to s4 (slot 5) instead of fp no matter where buf
 * is declared; retail order is row s0, poly s1, ptr s2, j s3, b2 s4,
 * b1 s5, b0 s6, i s7, buf fp. Decomp-permuter candidate. */
void func_80045F70(void) {
    u8 *buf;
    s8 i;
    u8 b0;
    u8 b1;
    u8 b2;
    s8 j;
    u8 *ptr;
    u8 *poly;
    u8 *row;
    s32 v0;
    s32 v1;

    i = 0;
    if (D_800A2EB0Absolute[1] > 0) {
        ptr = D_80090F32;
        do {
            D_800A342C[i] = 0;
            buf = (u8 *)HeapAlloc(0x500);
            v1 = *(s8 *)(D_800A3984[0] + (i * 5 << 8) + 0x876);
            D_800A3430[i] = (s32)buf;
            j = 0;
            v0 = v1 * 3;
            b0 = D_800991E8[v0];
            b1 = D_800991E9[v0];
            b2 = D_800991EA[v0];
            do {
                row = buf + j * 0x80;
                poly = row + 0x10;
                SetPolyFT4((POLY_FT4 *)poly);
                SetShadeTex((POLY_FT4 *)poly, 0);
                row[0x11] = 0x24;
                *(u32 *)(row + 0x28) = (u32)(row + 0x60);
                *(u32 *)(row + 0x2C) = (u32)(row + 0x68);
                *(u32 *)(row + 0x30) = (u32)(row + 0x78);
                row[0x14] = b0;
                row[0x15] = b1;
                row[0x16] = b2;
                *(u32 *)(row + 0x34) = (u32)(row + 0x70);
                *(s16 *)(row + 0x1E) = GetTPage(
                    *(u16 *)ptr, 0, *(u16 *)(ptr - 0xC), *(u16 *)(ptr - 0xA));
                row[0x18] = ptr[-4] + 0x6F;
                row[0x19] = *(u16 *)(ptr - 2);
                row[0x1C] = ptr[-4] + 0x60;
                row[0x1D] = *(u16 *)(ptr - 2);
                row[0x20] = ptr[-4] + 0x6F;
                row[0x21] = ptr[-2] + 0xF;
                row[0x24] = ptr[-4] + 0x60;
                row[0x25] = ptr[-2] + 0xF;
                row[0x00] = 0;
                j++;
            } while (j < 10);
            i++;
        } while (i < D_800A2EB0Absolute[1]);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80045F70);
#endif

#ifdef NON_MATCHING
/* w8f: structure and instruction stream match retail exactly except three
 * register-allocation diffs: (1) retail keeps count in v1 at entry and
 * copies it to t2 after the guard (mine puts count straight in t2);
 * (2) retail's loop-rotation precondition materializes a fresh li v0,1
 * before slt (mine reuses i's register, 4 bytes short); (3) retail loads
 * D_800BE980 via lui/lw %lo inside the loop (mine hoists its address into
 * t3 via lui/addiu). The li v0,1 guard comes from gcc loop.c for-loop
 * rotation: a for-loop shape produces the guard but still reuses i's reg.
 * func_80032DEC takes TWO args here (s32, s8) - a2/a3 are call residue.
 * Permuter candidate. */
extern s8 D_800A343C;
extern s8 *D_800A3444[];
extern s32 D_800BE980[];

void func_80046184(s8 *arg0) {
    extern void func_80032DEC(s32, s8);
    s8 *base;
    s8 *entry;
    s8 *tail;
    s32 count;
    s32 n;
    s8 i;
    s32 id;
    u16 flag;
    u8 *p;

    count = D_800A343C;
    base = D_800A3444[arg0[0x20B]];
    for (n = 1, i = 1, tail = base + 4; i < count; i++) {
        entry = base + i * 0x58;
        id = *(s16 *)entry;
        p = (u8 *)D_800BE980[0] + id * 0x90;
        flag = *(u16 *)(p + 0xE);
        if (flag != 0) {
            *(s32 *)(tail + 0x28) = (s32)(entry + 4);
            tail = entry + 4;
            n++;
        }
    }
    func_80032DEC((s32)(base + 4), (s8)n);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80046184);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80046258);

INCLUDE_ASM("asm/nonmatchings/game", func_8004658C);

INCLUDE_ASM("asm/nonmatchings/game", func_80046BD4);

INCLUDE_ASM("asm/nonmatchings/game", func_800474A0);

INCLUDE_ASM("asm/nonmatchings/game", func_80048118);

INCLUDE_ASM("asm/nonmatchings/game", func_80048568);

extern u8 *D_800A347C;
extern void *D_800A3728;
extern void func_8002D4CC(u8 *);

void func_80048700(void) {
    D_800A3728 = 0;
    D_800A347C = HeapAlloc(0x500);
    *(s16 *)(D_800A347C + 0x1EC) = 2;
    func_8002DA30((s32 *)D_800A347C);
    func_8002D4CC(D_800A347C);
    func_8002D3A8(D_800A347C, -4);
    *(s32 *)(D_800A347C + 0x10) = -1;
    *(s32 *)(D_800A347C + 0xC) = -1;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8004875C);

extern u8 *D_800A347C;
extern void *D_800A3728;
void func_800488A4(u8 *object) {
    u8 *state;
    state = D_800A347C;
    *(s32 *)(object + 0x90) = 0;
    D_800A3728 = object;
    state[0x401] = 0;
}

INCLUDE_ASM("asm/nonmatchings/game", func_800488B8);

extern u8 D_800A38F0;
extern u8 D_800A35FCnm asm("D_800A35FC.NON_MATCHING");
extern s32 D_800A2EB0Absolute[];
extern s32 D_800A37D0[];
extern s32 D_800A37D4nm[] asm("D_800A37D4.NON_MATCHING");
extern s32 D_800A2E94[];
extern s32 D_800AE1EC[];
extern s32 D_800A2EA8[];
extern s32 D_800A7550[];
extern u8 *D_800A3878nm[] asm("D_800A3878.NON_MATCHING");

void func_80048C90(void) {
    s8 buf[24];
    s8 i;
    s8 j;
    register s8 ni asm("$2");
    s8 idx;
    u8 *node;
    s32 scale;
    register s32 count asm("$18");
    s32 limit;
    register s32 bound asm("$3");
    s32 raw;
    s32 k;
    s32 a1val;
    register s32 slot asm("$18");
    s32 r0;
    s32 r2;
    register s32 cnt asm("$6");

    if (D_800A38F0 == 0 || (count = D_800A2EB0Absolute[0]) != 0) {
        D_800A35FCnm = 0;
        return;
    }
    r0 = RandomScaledGet((D_800A37D0[0] - 1) / 50 + 3);
    cnt = D_800A2E94[0];
    limit = 0x18 / cnt;
    D_800A35FCnm = ((D_800A37D4nm[-1] + 0x18) / 50 + r0) / limit;
    if (count < cnt) {
        i = 0;
        do {
            buf[i] = 0;
            ni = i + 1;
            asm volatile(
                "lui %1, %%hi(D_800A2E94.NON_MATCHING)\n\tlw %1, %%lo(D_800A2E94.NON_MATCHING)(%1)\n\taddu %0, %2, $zero"
                : "=r"(i), "=r"(bound)
                : "r"(ni));
        } while (ni < bound);
    }
    scale = MathFixedDivide(D_800AE1EC[0] * 0x14, 0x7D00);
    for (i = 0; i < D_800A35FCnm; i++) {
        do {
            raw = RandomScaledGet(D_800A2E94[0]);
            idx = (s8)raw;
            slot = raw;
        } while (buf[idx] != 0);
        node = D_800A3878nm[0];
        for (j = 0; j < idx; j++) {
            node = *(u8 **)(node + 0x3E0);
        }
        a1val = D_800A2EA8[0];
        D_800A7550[i] = node;
        r2 = RandomScaledGet(MathMultiplyFixed16(scale, (a1val - 1) << 16) >>
                             16);
        *(s32 *)(node + 0x414) = (scale >> 16) + r2;
        asm("sll %0, %1, 0x18\n\tsra %0, %0, 0x18" : "=r"(k) : "r"(slot));
        buf[k] = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80048EFC);

INCLUDE_ASM("asm/nonmatchings/game", func_8004A0C4);

INCLUDE_ASM("asm/nonmatchings/game", func_8004A510);

extern u8 D_8009AE14[];
extern u8 D_800A2FD0[];
extern u8 D_80098BD0[];

#ifdef NON_MATCHING
/* w8f: size and stream near-exact but 4 bytes short; register map differs
   (missing arg2 entry copy, hoisted D_80098BD0 base, split store cursor).
   Permuter candidate. */
extern s8 *D_8009AE14X[];

void func_8004AFE0(s8 arg0, u16 *arg1, u16 *arg2) {
    s16 *out;
    s8 i;
    s8 j;
    s32 x;
    s32 w;
    s32 t;
    s32 v0;
    s32 v1;
    s32 sum;

    i = 0;
    do {
        j = 0;
        x = arg1[i * 2];
        w = arg1[i * 2 + 1] + (s8)D_800A2FD0[arg0];
        if (D_8009AE14X[i][0] != 0) {
            out = (s16 *)((u8 *)arg2 + 0x22);
            do {
                t = D_8009AE14X[i][j];
                v0 = *(s16 *)&D_80098BD0[t * 10 + 6];
                out[-13] = x;
                out[-12] = w;
                out[-8] = w;
                out[-5] = x;
                sum = x + ((v0 * 3) >> 2);
                out[-9] = sum;
                v1 = *(s16 *)&D_80098BD0[t * 10 + 8];
                out[-1] = sum;
                out[-4] = w + ((v1 * 3) >> 2);
                v1 = *(s16 *)&D_80098BD0[t * 10 + 8];
                out[0] = w + ((v1 * 3) >> 2);
                x = sum;
                j++;
                arg2 += 0x14;
                out += 0x14;
            } while (D_8009AE14X[i][j] != 0);
        }
        i++;
    } while (i < 7);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8004AFE0);
#endif

extern s32 D_800A2E50[];
extern s16 D_800A38E4[];

void func_8004B128(u8 *arg0) {
    s8 value;

    if (arg0[0x3FC] != 0) {
        value = (D_800A2E50[0] - D_800A38E4[0]) * 10 / D_800A2E50[0] + 2;
    } else {
        value = 0;
    }
    if (value >= 0xB) {
        value = 0xA;
    }
    arg0[0x3FD] = value;
    *(s16 *)(arg0 + 0x402) = *(u16 *)(arg0 + 0x108);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8004B1C0);

INCLUDE_ASM("asm/nonmatchings/game", func_8004BDD0);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008D4F4);

#ifdef NON_MATCHING
extern s32 D_800A2E94[3];
extern s32 D_800A2EA4[3];
extern s32 D_800A2EA8[3];
extern s32 D_800A2EAC[3];
extern s32 D_800A2EB0[3];
extern u8 D_800A2FE4;
extern u8 D_800A2FE5;
extern u8 D_800A2FE6;
extern u8 D_800A2FE7;
extern char D_800A301C[];
extern char D_800A3020[];
extern char D_800A3024[];
extern char D_800A302C[];
extern char D_800A3034[];
extern char D_800A3038[];
extern s32 D_800A3554[];
extern s32 D_800A35E0[];
extern u8 D_800A37F4;
extern u8 D_800AE1EC[];
extern u8 D_800BE70C[];
extern s32 D_800BE974[];
extern void *D_8009AC1C[];
extern void *D_8009ADEC[];
extern void *D_8009ADF0[];
extern void *D_8009ADF4[];
extern void *D_8009AE94[];
extern void func_80050028(char *, u8, s32, s32);
extern void func_8004FF90(s16, u8, s32, s32);
extern void func_80050670(void *, u8, s32, s32, s32);
extern void func_8001D778(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 sprintf(char *, const char *, ...);

void func_8004D73C(s8 arg0, s32 arg1) {
    char text[8];
    u8 *entry;
    u8 *car;
    s8 index;
    s8 carIndex;
    s8 rowStart;
    s8 row;
    u8 selected;
    s32 y;

    y = arg1;
    if (D_800A2EB0[0] == 0) {
        entry = (u8 *)D_800A35E0[0];
        index = 0;
        while (index < (u8)arg0) {
            index++;
            entry = *(u8 **)(*(u8 **)(entry + 0x3E8) + 8);
        }
        rowStart = arg0;
        row = 1;
        while (rowStart < D_800A2E94[0] && row != 0xF) {
            func_80050028(*(char **)(entry + 0x34C), D_800A2FE5, (u8)y, 0);
            if (D_800A2EA4[0] != 0) {
                func_8004FF90(*(s16 *)(entry + 0x204), D_800A2FE5 + 6 - 1,
                              (u8)y, 0);
            } else {
                if (*(s8 *)(entry + 0x204) < 0xA) {
                    sprintf(text, D_800A301C, *(s8 *)(entry + 0x204));
                } else {
                    sprintf(text, D_800A3020, *(s8 *)(entry + 0x204));
                }
                D_800A37F4 = 9;
                func_80050028(text, D_800A2FE5 + 3 - 1, (u8)y, 0);
                D_800A37F4 = 0;
            }
            if (*(u8 *)(entry + 0xF4) == 0 &&
                D_800A2EA8[0] >= *(s16 *)(entry + 0x1D6)) {
                func_80050028(D_8009ADF4[0], D_800A2FE7, (u8)y, 0);
            } else {
                D_800A37F4 = 9;
                if (D_800A2EA8[0] < *(s16 *)(entry + 0x1D6)) {
                    sprintf(text, D_800A3024, *(s16 *)D_8009AE94[0]);
                } else if (*(s16 *)(entry + 0x1D6) >= 0x64) {
                    sprintf(text, D_800A3020, *(s16 *)(entry + 0x1D6));
                } else if (*(s16 *)(entry + 0x1D6) >= 0xA) {
                    sprintf(text, D_800A301C, *(s16 *)(entry + 0x1D6));
                } else {
                    sprintf(text, D_800A302C, *(s16 *)(entry + 0x1D6));
                }
                func_80050028(text, D_800A2FE6 - 4, (u8)y, 0);
                if (*(s16 *)(entry + 0x1D6) == 0) {
                    func_80050670((void *)0x7FFFFFFF, D_800A2FE7, (u8)y, 0, 0);
                } else if (entry == (u8 *)D_800A35E0[0]) {
                    func_80050670(*(void **)(entry + 0x260), D_800A2FE7, (u8)y,
                                  0, 0);
                } else {
                    car = (u8 *)D_800A35E0[0];
                    selected = ((*(s16 *)(car + 0x1D6) * D_800BE974[0] +
                                 *(s16 *)(car + 0x1E0)) -
                                (*(s16 *)(entry + 0x1D6) * D_800BE974[0] +
                                 *(s16 *)(entry + 0x1E0))) /
                               D_800BE974[0];
                    D_800A37F4 = 9;
                    if ((s16)selected > 0) {
                        func_80050028(D_800A3034, D_800A2FE7 - 0xA, (u8)y, 0);
                        func_8004FF90((s16)selected, D_800A2FE7, (u8)y, 0);
                        if ((s16)selected == 1) {
                            func_80050028(D_8009ADF0[0], D_800A2FE7 + 0xF,
                                          (u8)y, 0);
                        } else if ((s16)selected < 0xA) {
                            func_80050028(D_8009ADEC[0], D_800A2FE7 + 0xF,
                                          (u8)y, 0);
                        } else if ((s16)selected < 0x64) {
                            func_80050028(D_8009ADEC[0], D_800A2FE7 + 0x19,
                                          (u8)y, 0);
                        } else {
                            func_80050028(D_8009ADEC[0], D_800A2FE7 + 0x23,
                                          (u8)y, 0);
                        }
                    } else {
                        func_80050028(D_800A3038, D_800A2FE7 - 0xA, (u8)y, 0);
                        func_80050670(*(void **)(entry + 0x264), D_800A2FE7,
                                      (u8)y, 0, 1);
                    }
                }
            }
            if (*(s16 *)(entry + 0x1EC) == 0 && D_800A2E94[0] >= 3) {
                func_8001D778(0, (u8)y - 1, 0x140, 0xC, 0, 0, 0x80, 0);
            }
            rowStart++;
            row++;
            entry = *(u8 **)(*(u8 **)(entry + 0x3E8) + 8);
            y += 0xC;
        }
        return;
    }
    selected = 0;
    rowStart = arg0;
    row = 1;
    carIndex = arg0 + 1;
    index = (u8)arg0 + 1;
    do {
        car = (u8 *)D_800A3554[0];
        if (carIndex < 0xA) {
            sprintf(text, D_800A301C, carIndex);
        } else {
            sprintf(text, D_800A3020, carIndex);
        }
        D_800A37F4 = 9;
        func_80050028(text, D_800A2FE4 + 3, (u8)y, 0);
        if (carIndex == *(s8 *)(car + 0x204)) {
            if (selected == 0 && D_800A2EAC[0] == 0) {
                D_800A37F4 = 0;
                func_80050028(*(char **)(car + 0x34C), D_800A2FE5, (u8)y, 0);
                D_800A37F4 = 9;
                func_8004FF90(*(s16 *)(car + 0x1D6), D_800A2FE6 + 8, (u8)y, 0);
                func_80050670(*(void **)(car + 0x25C), D_800A2FE7, (u8)y, 0, 1);
                func_8001D778(0, (u8)y - 1, 0x140, 0xC, 0, 0, 0x80, 0);
                selected = 1;
                if (row == 0xF) {
                    return;
                }
                row++;
                carIndex++;
                D_800A37F4 = 9;
                y += 0xC;
                if (carIndex < 0xA) {
                    sprintf(text, D_800A301C, carIndex);
                } else {
                    sprintf(text, D_800A3020, carIndex);
                }
                func_80050028(text, D_800A2FE4 + 3, (u8)y, 0);
            }
            car = (u8 *)D_800A3554[0];
            if (carIndex == *(s8 *)(car + 0x204) &&
                D_800A2EA8[0] >= *(s16 *)(car + 0x1D6)) {
                func_80050028(D_8009AE94[0], D_800A2FE6 + 8, (u8)y, 0);
            }
        } else {
            func_80050028(D_8009AE94[0], D_800A2FE6 + 8, (u8)y, 0);
        }
        car = (u8 *)D_800A3554[0];
        D_800A37F4 = 0;
        index = rowStart;
        if (*(s8 *)(car + 0x204) < index && D_800A2EAC[0] == 0) {
            index = rowStart - 1;
        }
        func_80050028(D_8009AC1C[D_800BE70C[index]], D_800A2FE5, (u8)y, 0);
        car = (u8 *)D_800A3554[0];
        if (carIndex == *(s8 *)(car + 0x204)) {
            if (*(s16 *)(car + 0x1D6) < 2) {
                func_80050028(D_8009ADF4[0], D_800A2FE7, (u8)y, 0);
                goto nextRow;
            }
        } else {
            goto drawCar;
        }
        selected = 1;
    drawCar:
        func_80050670(D_800AE1EC[index], D_800A2FE7, (u8)y, 0, 1);
    nextRow:
        if (D_800A2EAC[0] != 0 && carIndex == *(s8 *)(car + 0x204)) {
            func_8001D778(0, (u8)y - 1, 0x140, 0xC, 0, 0, 0x80, 0);
        }
        rowStart++;
        row++;
        carIndex++;
        y += 0xC;
    } while (row < 0x10);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8004D73C);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8004DF38);

INCLUDE_ASM("asm/nonmatchings/game", func_8004E294);

#ifdef NON_MATCHING
/* Wall (draft below, 0x104 vs retail 0x108): gcc 2.7.2 CSEs the
 * loop-invariant address p+idx into one register hoisted before the
 * loop; retail recomputes addu a2,t0,t2 inside the loop and reads it
 * twice per iteration. Also missing retail's empty 8-byte frame
 * (addiu sp,-8). Tried: pointer locals q/p, distinct expressions,
 * i*2 array indexing. The s8 counter (sll24/sra24), the guarded div
 * (break 7/6), and the fresh lui/lw before the *2+1 tail all match. */
extern s32 D_800A2CE0;
extern s8 D_800992D0[];
extern s32 D_800A8A2C[];
extern s32 D_800A8A30[];
extern s8 D_800A3498;
extern s8 D_800A349C;
extern s8 D_800A34A8;
extern s16 D_800A34A0;
extern s16 D_800A34A4;
void func_8004E700(void) {
    s32 idx;
    s32 *q;
    s8 *p;
    s8 i;
    s32 a1;

    idx = D_800A2CE0;
    D_800A34A8 = 0;
    D_800A3498 = 0;
    D_800A34A4 = 0;
    D_800A349C = 0x3C;
    if (D_800992D0[idx] > 0) {
        q = &D_800BE974[0];
        p = D_800992D0;
        i = 0;
        do {
            a1 = *q;
            D_800A8A30[i * 2] = 0x7FFFFFFF;
            D_800A8A2C[i * 2] = a1 + a1 * (i + 1) / p[idx];
            i++;
        } while (i < p[idx]);
    }
    D_800A34A0 = D_800BE974[0] * 2 + 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8004E700);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8004E808);

INCLUDE_ASM("asm/nonmatchings/game", func_8004EA34);

INCLUDE_ASM("asm/nonmatchings/game", func_8004EBE4);

INCLUDE_ASM("asm/nonmatchings/game", func_8004F158);

INCLUDE_ASM("asm/nonmatchings/game", func_8004F880);

INCLUDE_ASM("asm/nonmatchings/game", func_8004FCF4);

extern u8 *D_800A3554[];
extern u8 *D_800A8A80[];
void func_8004FF3C(void) {
    D_800A8A80[0][0] = *(u16 *)(D_800A3554[0] + 0x2AA);
    D_800A8A80[0][1] = *(u16 *)(D_800A3554[0] + 0x2A4);
    *(u16 *)(D_800A8A80[0] + 4) = *(u16 *)(D_800A3554[0] + 0x1D6);
}

#ifdef NON_MATCHING
/* Wall: every instruction matches, but gcc allocates arg3->s0, arg1->s1,
 * arg2->s2 (retail: arg1->s0, arg2->s1, arg3->s2) and arg0->t0 (retail
 * v1). Rotation persists across param-type variants. */
extern char D_800A3020[];
extern u8 D_800A37F4;
extern s32 sprintf(char *, const char *, ...);
extern void func_80050028(char *, s16, s16, s8);
void func_8004FF90(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    char text[16];

    if ((s8)arg3 == 1) {
        D_800A37F4 = 6;
    } else {
        D_800A37F4 = 9;
    }
    sprintf(text, D_800A3020, arg0);
    func_80050028(text, (s16)arg1, (s16)arg2, (s8)arg3);
    D_800A37F4 = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8004FF90);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80050028);

INCLUDE_ASM("asm/nonmatchings/game", func_80050670);

void SetPolyFT4(POLY_FT4 *);
extern POLY_FT4 D_800A8AC4[];
extern s16 D_800A8AD2[];
void func_800508E4(void) {
    SetPolyFT4(D_800A8AC4);
    D_800A8AD2[0] = GetClut(0x390, 0x3C);
}

extern u8 D_800A8AC8[], D_800A8AC9[], D_800A8ACA[];
void GraphicsSetColor(u8 red, u8 green, u8 blue) {
    D_800A8AC8[0] = red;
    D_800A8AC9[0] = green;
    D_800A8ACA[0] = blue;
}

#ifdef NON_MATCHING
extern u8 D_80098D16[];
s32 func_80050940(u8 *str) {
    s32 sum;
    u8 c;

    sum = 0;
    if (*str != 0) {
        asm("");
        c = *str;
        do {
            str++;
            sum += *(s16 *)&D_80098D16[(c - 0x20) * 10];
            c = *str;
        } while (c != 0);
    }
    return sum;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80050940);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8005098C);

INCLUDE_ASM("asm/nonmatchings/game", func_80050D1C);

INCLUDE_ASM("asm/nonmatchings/game", func_800511E4);

extern s8 D_800A34CC;
extern s8 D_800A34CD;
extern s8 D_800A34CE;
extern s8 D_800A34CF;
extern s8 D_800A34D0;
extern s8 D_800A34D1;
extern u8 D_800A8B00[];
extern u8 D_800A8B01[];
extern u8 D_800A8B02[];

void func_800514EC(u8 arg0, u8 arg1, u8 arg2) {
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

INCLUDE_ASM("asm/nonmatchings/game", func_8005157C);

INCLUDE_ASM("asm/nonmatchings/game", func_80051874);

extern u8 D_800A34E4;
extern s32 D_800A34F4;
extern u8 D_80090F7A[];

void func_800524A0(u8 *arg0, s8 arg1) {
    u8 *table;
    u8 *entry;
    s32 mode;
    u16 w;
    u32 v;

    arg0 += arg1 * 0x28 + 0x2AC;
    mode = *(s16 *)(arg0 + 0x26);
    arg0[0x24] = 0;
    arg0[0x20] = 0;
    D_800A34E4 = 0;
    if (mode != -1) {
        table = D_80090F7A;
        w = *(u16 *)(arg0 + 0x22);
        entry = (u8 *)D_800A34F4 + (mode * 12 - mode) * 8;
        if (w == 2) {
            table += 0xE;
        }
        *(s16 *)(entry + 0x12) =
            GetClut(*(u16 *)(table + 4), *(u16 *)(table + 6));
        *(s16 *)(entry + 0x16) = GetTPage(
            *(u16 *)(table + 0xC), 0, *(u16 *)(table + 0), *(u16 *)(table + 2));
        v = table[8] + 0x3F;
        entry[0x14] = v;
        entry[0x10] = v;
        v = table[8];
        entry[0x1C] = v;
        entry[0x18] = v;
        v = table[0xA];
        entry[0x19] = v;
        entry[0x11] = v;
        v = table[0xA] + 0x1F;
        entry[0x1D] = v;
        entry[0x15] = v;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_800525A8);

INCLUDE_ASM("asm/nonmatchings/game", func_80052E18);

extern s8 D_800A34EC;
extern s8 D_800A34F0;
extern void func_8003F914(s32);

void func_80052FC4(s8 arg0) {
    if (arg0 < 2) {
        func_8003F914(0x14);
        D_800A34EC = 0;
    }
    if (!(arg0 & 1)) {
        func_8003F914(0x15);
        D_800A34F0 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005301C);

INCLUDE_ASM("asm/nonmatchings/game", func_800531B8);

INCLUDE_ASM("asm/nonmatchings/game", func_800535A0);

extern void func_8005E550(s32);
extern void func_80057AE4(void);
extern void func_80057A9C(void);
extern void func_8005A4E0(void);
extern void func_8005A544(u8, u8);
extern void func_8005A804(u8, u8, u8);
extern void func_80059648(void);
extern void func_800631B4(void);
extern void func_80063E7C(void);
extern void func_80064174(void);
extern void func_80069744(void);
extern void *func_80058094(s32, void **, s32);
extern s32 D_800A37EC;
extern u8 D_800A3724NM asm("D_800A3724.NON_MATCHING");
extern u8 D_800A305ANM asm("D_800A305A.NON_MATCHING");
extern s32 D_800A37F0NM asm("D_800A37F0.NON_MATCHING");
extern s32 D_800A3830NM asm("D_800A3830.NON_MATCHING");

void func_800539F0(void) {
    void *table;
    u8 i;
    void *base;

    D_800A37EC = (s32)HeapAlloc(0x26000);
    func_8003CA18(D_800A37EC, 5);
    func_8005E550(6);
    func_80057AE4();
    i = 0;
    func_800631B4();
    func_80063E7C();
    func_80057A9C();
    func_8005A4E0();
    base = func_80058094(9, &table, 0);
    func_80013224(base + ((s32 *)table)[0xB]);
    DrawSync(0);
    func_80013224(base + ((s32 *)table)[6]);
    DrawSync(0);
    func_80013224(base + ((s32 *)table)[0xA]);
    DrawSync(0);
    while (i < 5) {
        func_80013224(base + ((s32 *)table)[i + 1]);
        DrawSync(0);
        i++;
    }
    i = 0;
    func_80013224(base + ((s32 *)table)[9]);
    DrawSync(0);
    while (i < 2) {
        func_80013224(base + ((s32 *)table)[i + 7]);
        DrawSync(0);
        i++;
    }
    func_80013224(base + ((s32 *)table)[0xC]);
    DrawSync(0);
    func_80013224(base + ((s32 *)table)[0]);
    DrawSync(0);
    func_80059648();
    HeapFree(base);
    func_80064174();
    func_80069744();
    func_8005A544(0, 0);
    func_8005A544(1, 1);
    func_8005A544(2, 2);
    func_8005A804(0xA0, 0xA0, 0x40);
    D_800A3724NM = 3;
    D_800A305ANM = 0;
    D_800A37F0NM = 1;
    D_800A3830NM = 0;
}

#ifdef NON_MATCHING
/* w9f: positional cc1 SIGSEGV (exit 139) whenever this function body is ACTIVE
 * at this TU position: any runtime value in the func_8005D094 call args
 * kills cc1 (constant args compile). Prototype, cast, local-temp and
 * direct-read shapes all crash; D_800A39E4Small/D_800A3059 as call args
 * are fine in func_80057160 earlier in the TU. 64MB stack does not help.
 * Draft below is structurally complete; retest after any TU change. */
extern u8 D_800A3608;

void func_80053C00(s32 arg0, s32 arg1) {
    extern s32 D_800A3914[];
    extern void func_8006DCF0(void);
    extern void func_8005B688(u8 *, u8);
    extern void func_8005B8B8(u8 *, u8);
    extern void func_80064898(void);
    extern void func_800686FC(u8, u8);
    extern void func_8005D094(D_800A39E4Small, D_800A3059, arg1);
    extern s32 func_8005DCF0(void);
    s32 modeB;
    s32 flagB;

    if (D_800A39E4Small == 0xFC) {
        func_8006DCF0();
    } else {
        if (D_800A3914[0] != 0) {
            func_8005B688((u8 *)D_800A3914[0], 1);
        }
        if ((u32)(D_800A39E4Small - 9) < 2 || D_800A39E4Small == 0xC) {
            func_800686FC((u8)D_800A39E4Small, (u8)arg0);
        } else if (D_800A39E4Small == 0xE) {
            func_8005B8B8((u8 *)D_800A3914[0], 0xFF);
            func_80064898();
        } else {
            func_8005B8B8((u8 *)D_800A3914[0], 0xFF);
            modeB = D_800A39E4Small;
            flagB = D_800A3059;
            func_8005D094(modeB, flagB, arg1);
        }
    }
    if (D_800A3608 != 0) {
        D_800A3608 = D_800A3608 - 1;
    } else {
        if ((u32)(D_800A39E4Small - 0x10) < 2 || D_800A39E4Small == 0xE) {
        } else if (func_8005DCF0() == 1) {
            D_800A3608 = 0x78;
        }
    }
}

#else
INCLUDE_ASM("asm/nonmatchings/game", func_80053C00);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80053D40);

INCLUDE_ASM("asm/nonmatchings/game", func_80055AA4);

#ifdef NON_MATCHING
/* gp byte/word accesses to symbols declared array-form elsewhere go
 * through .NON_MATCHING aliases as in func_80056C84 below. */
void func_80055C78(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5) {
    extern u8 D_800A3644NM asm("D_800A3644.NON_MATCHING");
    extern u8 D_800A3988NM asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3073NM asm("D_800A3073.NON_MATCHING");
    extern s8 D_800A3078NM asm("D_800A3078.NON_MATCHING");
    extern u8 D_800A305BNM asm("D_800A305B.NON_MATCHING");
    extern u8 D_800A2F95NM[] asm("D_800A2F95.NON_MATCHING");
    extern s8 D_800A3A14NM[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R2[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R3[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R4[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R5[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R6[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R7[] asm("D_800A3A14.NON_MATCHING");
    extern u8 *D_800A38FCR2[] asm("D_800A38FC.NON_MATCHING");
    extern u8 *D_800A38FCR3[] asm("D_800A38FC.NON_MATCHING");
    extern u8 *D_800A38FCR4[] asm("D_800A38FC.NON_MATCHING");
    extern u8 *D_800A39A0R2[] asm("D_800A39A0.NON_MATCHING");
    extern u8 *D_800A39A0R3[] asm("D_800A39A0.NON_MATCHING");
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
    extern u8 D_800A3988B[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988C[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988D[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988E[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988F[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988G[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988H[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988I[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988J[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988K[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988L[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988M[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988N[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988O[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988P[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3068[];
    extern u8 D_800A3074;
    extern u8 D_800A3076;
    extern u8 D_800A3077;
    extern u8 D_800A306C;
    extern u8 D_800A306D;
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
    extern u8 D_80099568[];
    extern u8 D_800A331C[];
    extern u8 D_80099574[];
    extern u8 D_8009AD40[];
    extern s32 D_800A3744[];
    extern s32 D_800A360C[];
    extern s32 D_800A37D4[];
    extern s32 D_800A3870[];
    extern u8 *D_800A39A0[];
    extern u8 *D_800A38FC[];
    extern s8 D_800A3594[];
    extern s8 D_800A3860[][4];
    extern s8 D_800A39DC[];
    extern s8 D_800A3944[];
    extern u8 D_800A3894[];
    extern s8 D_800A39FC[];
    extern s32 func_8005CA4C(void);
    extern void func_80055AA4(u8, s32);
    extern void func_8005C8D8(s32);
    extern s32 func_8005CCEC(u8, s32);
    extern void func_8005CC34(void);
    extern void func_8005CEDC(void);
    extern void func_8005E4A4(s32);
    extern void func_8005ED04(u8);
    extern void func_8005EC5C(u8);
    extern void func_80060008(u8);
    extern void func_80063694(u8, s16, s16, s16);
    extern void func_800645A4(s8, s8);
    extern void func_80063AE0(s32, s32);
    extern void func_80067F34(s8, u8);
    extern void func_8006894C(s8, s32, s32, s32, s32);
    extern void func_80060F54(s16, s32);
    extern void func_8006CF90(u8);
    extern void ListSetRangeFields(struct UnkNode1C *, s32, s32, s16);
    s32 mode;
    s32 mask;
    s32 limit;
    s32 value;
    s32 tableByte;

    mode = arg0 & 0xFF;
    if (mode != 4) {
        if (mode != 7) {
            if (mode != 0x21) {
                if (mode != 0xB) {
                    goto checkButtons;
                }
            }
        }
    }
    if (mode == 4) {
        if ((arg1 & 0xFF) != 0) {
            goto checkButtons;
        }
    }
    if (mode == 7) {
        if ((arg1 & 0xFF) < 2U) {
            goto checkButtons;
        }
        if ((arg1 & 0xFF) == 6) {
            goto checkButtons;
        }
    }
    if (mode == 0xB) {
        if ((arg1 & 0xFF) == 0) {
            goto checkButtons;
        }
    }
    goto repeatProcessing;
checkButtons:
    mask = ~arg4;
    if (((mask & 0x8000) & arg3) == 0) {
        if (((mask & 0x2000) & arg3) == 0) {
            return;
        }
    }
    goto dispatch;
repeatProcessing:
    switch (mode) {
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
    switch (arg0 & 0xFF) {
    case 2:
        switch (arg1 & 0xFF) {
        case 0:
            if ((func_8005CA4C() & 0xFF) == 0) {
                return;
            }
            break;
        case 1:
            asm("");
            func_80055AA4(arg5, arg2 & 0xFF);
            break;
        case 2:
            if ((arg2 & 0xFF) != 0) {
                if (D_800A305BNM != 0) {
                    value = D_800A305BNM - 1;
                } else {
                    value = 0x10;
                }
                D_800A305BNM = value;
                while (D_8009957C[D_800A305BNM] == 0) {
                    if (D_800A305BNM != 0) {
                        D_800A305BNM = D_800A305BNM - 1;
                    } else {
                        D_800A305BNM = 0x10;
                    }
                }
            } else {
                if (D_800A305BNM < 0x10) {
                    value = D_800A305BNM + 1;
                } else {
                    value = 0;
                }
                D_800A305BNM = value;
                while (D_8009957C[D_800A305BNM] == 0) {
                    if (D_800A305BNM < 0x10) {
                        D_800A305BNM = D_800A305BNM + 1;
                    } else {
                        D_800A305BNM = 0;
                    }
                }
            }
            func_8005E4A4(D_800AE178[D_800A305BNM]);
            func_8005ED04(D_800A305BNM);
            func_8005EC5C(D_800A305BNM);
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
        }
        break;
    case 4:
        switch (arg1 & 0xFF) {
        case 0:
            if ((arg2 & 0xFF) != 0) {
                value = D_800A37D0NM - D_800A37F0;
                if (value < 3) {
                    D_800A37D0NM = 3;
                } else {
                    D_800A37D0NM = value;
                    func_8003F564(0, 2);
                }
            } else {
                value = D_800A37D0NM + D_800A37F0;
                if (value < 0x65) {
                    D_800A37D0NM = value;
                    func_8003F564(0, 2);
                } else {
                    D_800A37D0NM = 0x64;
                }
            }
            func_8005CC34();
            func_8005EC5C(D_800A305BNM);
            return;
        case 1:
            if ((arg2 & 0xFF) != 0) {
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
            if (D_800A306E == 1 && D_800A3644NM == 0) {
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
                if (arg1 == 4) {
                    D_800A3070 = 0;
                } else if (arg1 == 5) {
                    D_800A3072 = 0;
                }
            } else {
                if (arg1 == 4) {
                    D_800A3070 = 1;
                } else if (arg1 == 5) {
                    D_800A3072 = 1;
                }
            }
            break;
        }
        break;
    case 5:
        if ((arg1 & 0xFF) == 1) {
            D_800A3988P[1] = D_800A3988[1] ^ 1;
            D_800A306C = D_800A306C ^ 1;
            func_8005C8D8(1);
            if (D_800A306D != 0) {
                D_800A2F95NM[0] = 0;
                SsSetMono();
            } else {
                D_800A2F95NM[0] = 1;
                SsSetStereo();
            }
        } else if ((arg1 & 0xFF) == 5) {
            if (D_800A3076 == 0) {
                return;
            }
            D_800A3988[5] = D_800A3988[5] ^ 1;
            func_8005C8D8(5);
            if (D_800A3988[5] != 0) {
                D_800A3077 = 0;
            } else {
                D_800A3077 = 1;
            }
        } else {
            return;
        }
        break;
    case 7:
        if ((arg1 & 0xFF) < 0) {
            return;
        }
        if ((arg1 & 0xFF) < 2U) {
            D_800A3988[arg1 & 0xFF] = D_800A3988B[arg1 & 0xFF] ^ 1;
            D_800A3068[arg5 * 2 + (arg1 & 0xFF)] =
                D_800A3068[arg5 * 2 + (arg1 & 0xFF)] ^ 1;
            func_8005C8D8(arg1 & 0xFF);
            break;
        }
        if ((arg1 & 0xFF) >= 6) {
            return;
        }
        if ((arg2 & 0xFF) != 0) {
            D_800A3860[arg5][(arg1 & 0xFF) - 2] =
                D_800A3860[arg5][(arg1 & 0xFF) - 2] - D_800A37F0;
            if ((s8)D_800A3860[arg5][(arg1 & 0xFF) - 2] < 0) {
                D_800A3860[arg5][(arg1 & 0xFF) - 2] = 0;
            } else {
                func_8003F564(0, 2);
            }
            value = (s8)D_800A3860[arg5][(arg1 & 0xFF) - 2];
            D_800A3860[arg5][(arg1 & 0xFF) - 2] = value - value % 4;
        } else {
            D_800A3860[arg5][(arg1 & 0xFF) - 2] =
                D_800A3860[arg5][(arg1 & 0xFF) - 2] + D_800A37F0;
            if ((s8)D_800A3860[arg5][(arg1 & 0xFF) - 2] < 0x40) {
                value = ((s8)D_800A3860[arg5][(arg1 & 0xFF) - 2] + 3) / 4;
                if (value * 4 < 0x40) {
                    D_800A3860[arg5][(arg1 & 0xFF) - 2] = value * 4;
                } else {
                    D_800A3860[arg5][(arg1 & 0xFF) - 2] = 0x3F;
                }
            } else {
                D_800A3860[arg5][(arg1 & 0xFF) - 2] = 0x3F;
            }
            func_8003F564(0, 2);
        }
        func_80060008(arg5);
        return;
    case 8:
        if ((arg1 & 0xFF) != 0) {
            return;
        }
        func_80055AA4(arg5, arg2 & 0xFF);
        break;
    case 9:
        if (D_800A3A58NM[0] == 0) {
            return;
        }
        D_800A39DC[0] = D_800A3944[0];
        D_800A3870[0] = D_800A37D4[0];
        D_800A3944[0] = D_800A3944[0] ^ 1;
        if ((arg2 & 0xFF) != 0) {
            D_800A3894[0] = (D_800A3894[0] + 0x10) % 17;
        } else {
            D_800A3894[0] = (D_800A3894[0] + 1) % 17;
        }
        func_80067F34(D_800A3944R2[0], D_800A3894R2[0]);
        D_800A37D4[0] = D_800A360C[D_800A3944R3[0]];
        if ((arg2 & 0xFF) != 0) {
            func_8006894C(D_800A39DCR2[0], 0, 0x140, 2, 0);
            func_8006894C(D_800A3944R4[0], -0x140, 0, 2, 1);
        } else {
            func_8006894C(D_800A39DCR3[0], 0, -0x140, -2, 0);
            func_8006894C(D_800A3944R4[0], 0x140, 0, -2, 1);
        }
        break;
    case 0xB:
        arg5 = 1;
        if ((arg1 & 0xFF) == 0) {
            if ((arg2 & 0xFF) != 0) {
                D_800A3988NM = (D_800A3988NM + 2) % 3;
            } else {
                D_800A3988NM = (D_800A3988NM + 1) % 3;
            }
            for (arg1 = 0; arg1 < 5; arg1++) {
                D_800A331C[arg1] = D_80099568[D_800A3988NM * 6 + arg1];
            }
            D_800A3078NM = D_800A3988NM;
        } else {
            if ((arg1 & 0xFF) == 6) {
                return;
            }
            if (D_800A3078NM != 2) {
                D_800A3078NM = 2;
                D_800A3988NM = 2;
            }
            if ((arg2 & 0xFF) != 0) {
                arg5 = func_8005CCEC(arg1 & 0xFF, -D_800A37F0);
            } else {
                arg5 = func_8005CCEC(arg1 & 0xFF, D_800A37F0);
            }
        }
        if (D_800A3078NM == 2) {
            for (arg1 = 0; arg1 < 5; arg1++) {
                D_80099574[arg1] = D_800A331C[arg1];
            }
        }
        func_8005CEDC();
        if ((arg5 & 0xFF) == 0) {
            return;
        }
        break;
    case 0xE:
        arg1 = D_800A3A14NM[0];
        D_800A39A0[0] = D_800A38FC[0];
        D_800A3A14R2[0] = arg1 ^ 1;
        if ((arg2 & 0xFF) != 0) {
            D_800A3594[0] = (D_800A3594[0] + 0x17) % 24;
        } else {
            D_800A3594[0] = (D_800A3594[0] + 1) % 24;
        }
        tableByte = D_8009AD40[D_800A3594R2[0]];
        D_800A39FC[0] = tableByte;
        func_800645A4(D_800A3A14R3[0], (s8)tableByte);
        func_80063AE0(D_800A3A14R4[0], D_800A39FCR2[0]);
        D_800A38FCR2[0] = (u8 *)D_800A3744[D_800A3A14R5[0]];
        if ((arg2 & 0xFF) != 0) {
            ListSetRangeFields((struct UnkNode1C *)D_800A39A0R2[0], 0, 0x140,
                               2);
            func_80063694(arg1, 0x34, 0x174, 2);
            ListSetRangeFields((struct UnkNode1C *)D_800A38FCR3[0], -0x140, 0,
                               2);
            func_80063694(D_800A3A14R6[0], -0x10C, 0x34, 2);
        } else {
            ListSetRangeFields((struct UnkNode1C *)D_800A39A0R3[0], 0, -0x140,
                               -2);
            func_80063694(arg1, 0x34, -0x10C, -2);
            ListSetRangeFields((struct UnkNode1C *)D_800A38FCR4[0], 0x140, 0,
                               -2);
            func_80063694(D_800A3A14R7[0], 0x174, 0x34, -2);
        }
        break;
    case 0x21:
        if ((arg2 & 0xFF) != 0) {
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
        func_80060F54(*(s16 *)&D_800A3690NM[arg1 & 0xFF], (arg1 & 0xFF) - 2);
        return;
    case 0x23:
        func_8006CF90(arg2 & 0xFF);
        if (D_800A3928 == 0) {
            break;
        }
        return;
    case 0:
    case 1:
    default:
        return;
    }
    func_8003F564(0, 2);
}

#else
INCLUDE_ASM("asm/nonmatchings/game", func_80055C78);
#endif

s32 func_80056B0C(s32 arg0, s32 arg1) {
    extern u8 D_800A39E4Small;
    s32 result;

    result = 0;
    switch (D_800A39E4Small) {
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
    extern u8 D_800A39E4Small;
    s32 result;

    result = 0;
    switch (D_800A39E4Small) {
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
    extern u8 D_800A3078NM asm("D_800A3078.NON_MATCHING");
    extern u8 D_800A3988[];
    extern u8 D_800A3988B[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988C[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988D[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988E[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988F[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988G[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988H[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988I[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988J[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988K[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988L[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988M[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988N[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988O[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3988P[] asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A398F[];
    extern u8 D_800A3073[];
    extern u8 D_800A306C;
    extern u8 D_800A306E;
    extern u8 D_800A306F;
    extern u8 D_800A3070;
    extern u8 D_800A3071;
    extern u8 D_800A3072;
    extern u8 D_800A3074;
    extern u8 D_800A3076;
    extern u8 D_800A3077;
    s32 clearCount;
    u8 *clearPtr;
    s32 mode;
    s32 tmp;
    s32 idx;

    clearCount = 7;
    clearPtr = D_800A398F;
    do {
        *clearPtr = 0;
        clearCount--;
        clearPtr--;
    } while (clearCount >= 0);

    mode = 8;
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
            mode = 1;
            break;
        case 1:
            mode = 0;
            break;
        case 2:
            mode = 2;
            break;
        }
        D_800A3988[1] = mode;
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

extern u8 D_800A36E0Small;
extern u8 D_800A361C;
extern u8 D_800A305BSmall;
extern u8 D_800A36E1[];
void func_80056F04(s32 arg0) {
    extern void func_8005E5BC(s32, s32, s32, s32);
    extern void func_8005E7F8(s32, s32, s32, s32);
    extern void func_8005E644(s32, s32, s32, s32);
    extern void func_8005DF08(s32, s32, s32, s32);
    extern void func_800631DC(s32, s32, s32);
    extern u8 D_800A39E4Small;
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
        func_8005E5BC(D_800A305BSmall, -0x78, 2, flag);
        func_8005E7F8(D_800A305BSmall, -0x78, 2, flag);
        func_8005E644(D_800A305BSmall, -0x78, 2, flag);
        func_8005DF08(-0x78, 0, 2, flag);
        func_800631DC(-0x3C, 0x3C, 2);
        func_80063AE0(0, D_800A36E0Small);
        func_80063AE0(1, D_800A36E1[0]);
        switch (D_800A39E4Small) {
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

extern u8 D_800A3808a[] asm("D_800A3808.NON_MATCHING");
extern u8 D_800A3808b[] asm("D_800A3814.NON_MATCHING");
extern u8 D_800A3808c[] asm("D_800A380C.NON_MATCHING");
extern u8 D_800A3808d[] asm("D_800A3810.NON_MATCHING");
extern u8 D_800A3968a[] asm("D_800A3968.NON_MATCHING");
extern u8 D_800A3950nm asm("D_800A3950.NON_MATCHING");
extern u8 D_800A3059;
extern u8 D_800A39E4Small;

void func_80057008(s32 arg0) {
    extern void func_8006D8E8(s32);
    extern void func_8006C5E4(s32);
    extern void func_8006BD68(void);
    extern u8 D_800A3928;
    s32 mode;

    if (D_800A3808a[0] == 2 || !(arg0 & 0xFF)) {
        func_8006D8E8(0);
        mode = D_800A3059;
        D_800A3928 = 1;
        if (mode == 1) {
            func_8006C5E4(1);
            if (D_800A3059 == mode) {
                D_800A39E4Small = 0x24;
                D_800A3928 = 2;
                return;
            }
        }
        D_800A39E4Small = 0x23;
    } else if (D_800A39E4Small != 0x28) {
        if (D_800A3059 == 2) {
            func_8006BD68();
            D_800A3928 = 0;
            D_800A3808b[-12] = 0;
            D_800A39E4Small = 0x22;
            func_8006C5E4(0);
        } else if (D_800A3059 == 1) {
            if (D_800A3968a[0] == 0) {
                D_800A3808c[-4] = 0x14;
                func_8006D8E8(0);
                D_800A3928 = 2;
                D_800A39E4Small = 0x24;
                func_8006C5E4(1);
            } else {
                D_800A3808d[-8] = 0;
                D_800A39E4Small = 0x24;
                if (D_800A3950nm == 0) {
                    D_800A3928 = 1;
                } else {
                    D_800A3928 = 0;
                }
                func_8006C5E4(1);
            }
        }
    }
}

extern u8 D_800A3704;
extern u8 D_800A3059;
extern u8 D_800A39E4Small;

void func_80057160(s32 arg0) {
    extern void func_8006C9DC(void);
    extern void func_8006C598(s32, s32, s32);
    extern void func_8006C2D0(s32);
    extern void func_8006CB40(void);
    extern void func_80063770(u8);
    extern void func_80069AFC(u8);
    s32 result;

    D_800A3704 = 1;
    func_8006C9DC();
    result = arg0 & 0xFF;
    if (result != 0) {
        func_8006C598(-0x78, 0, 2);
    }
    if (((u8 *)D_800A36D0Absolute)[0x138] == 0) {
        func_8006C2D0(D_800A3059 == 2);
        func_8006CB40();
    }
    func_80063770(0);
    func_80069AFC(D_800A39E4Small);
}

INCLUDE_ASM("asm/nonmatchings/game", func_800571EC);

extern s32 D_800A3668Absolute[];
void func_80057A9C(void) {
    ((s32 *)D_800A3668Absolute)[4] = (s32)HeapAlloc(0x1AB8);
    ((u8 *)D_800A3668Absolute)[-0x7C] = 0;
    ((s32 *)D_800A3668Absolute)[-5] = (s32)HeapAlloc(0x834);
    ((u8 *)D_800A37B4Absolute)[8] = 0;
}

/* Wall: needs a gp store to D_800A3548 (untracked sdata label, no
 * linker alias). Declaring it shifts every sdata label +0x10 and the
 * full build MISMATCHes. Also needs lui for D_800A39E8, which is
 * scalar-declared (gp) for the TU. */
extern void func_80012E28(void);
extern void *HeapAlloc(u32);
extern s32 D_800A3548;
extern s32 D_800A3998;
extern s32 D_800A3A18;
extern s32 D_800A39A8;
extern s32 D_800A39CC;
extern s32 D_800A3780;
extern s32 D_800A35B8;
extern s32 D_800A3544;
extern s32 D_800A38EC;
extern s32 D_800A397CAbsolute[];
extern void func_8005E47C(void);
/* w9f unguard retry: D_800A3548 tracked extern works now (gp sw/lw match,
 * size 0x118 exact) but the s-reg map is rotated: ours saves an extra s4
 * and runs poly->s0/cursor->s2 vs retail s1/s0; retail pins the 0x80
 * shade byte in s3 across both loops, ours rematerializes the literal.
 * Candidate fix: a local holding 0x80 stored through both loops. Re-guarded. */
#ifdef NON_MATCHING
void func_80057AE4(void) {
    POLY_FT4 *poly;
    POLY_F4 *shade;
    u8 *color;
    u32 count;
    s32 base;

    func_80012E28();
    poly = HeapAlloc(0x4290);
    D_800A3548 = (s32)poly;
    color = (u8 *)poly + 6;
    for (count = 0; count < 0x1AA; count++) {
        SetPolyFT4(poly);
        SetShadeTex(poly, 0);
        color[-2] = 0x80;
        color[-1] = 0x80;
        color[0] = 0x80;
        color += 0x28;
        poly++;
    }
    base = D_800A3548;
    D_800A397CAbsolute[27] = base;
    D_800A3998 = base + 0x3E80;
    D_800A3A18 = base + 0x3E80;
    D_800A39A8 = base + 0x4268;
    D_800A39CC = base + 0x4268;
    shade = HeapAlloc(0x4B0);
    color = (u8 *)shade + 6;
    D_800A3780 = (s32)shade;
    D_800A35B8 = (s32)shade;
    D_800A3544 = (s32)shade + 0x3C0;
    D_800A38EC = (s32)shade + 0x3C0;
    for (count = 0; count < 0x32; count++) {
        SetPolyF4(shade);
        SetSemiTrans(shade, 0);
        color[-2] = 0x80;
        color[-1] = 0x80;
        color[0] = 0x80;
        color += 0x18;
        shade++;
    }
    func_8005E47C();
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80057AE4);
#endif

extern s32 D_800A3548;
extern s32 D_800A3780;
extern s32 D_800A37EC;

void func_80057BFC(void) {
    extern void func_800697B4(void);
    extern void func_8005E3DC(void);
    extern void func_8005E408(void);
    extern void func_80014A68(void);
    extern void func_80063A20(void);

    func_800697B4();
    if (D_800A3780 != 0) {
        HeapFree((void *)D_800A3780);
    }
    D_800A3780 = 0;
    if (D_800A3548 != 0) {
        HeapFree((void *)D_800A3548);
    }
    D_800A3548 = 0;
    func_8005E3DC();
    func_8005E408();
    if (D_800A37EC != 0) {
        HeapFree((void *)D_800A37EC);
    }
    D_800A37EC = 0;
    if (D_800A36D0Absolute[-22] != 0) {
        HeapFree((void *)D_800A36D0Absolute[-22]);
    }
    D_800A36C0Absolute[-18] = 0;
    if (D_800A36D4Absolute[-32] != 0) {
        HeapFree((void *)D_800A36D4Absolute[-32]);
    }
    D_800A36E8Absolute[-37] = 0;
    func_80014A68();
    func_80063A20();
}

extern s32 D_800A36EC;
extern s32 D_800A3A18;
extern s32 D_800A3964;
extern s32 D_800A3580;
extern s32 D_800A35B8;
extern s32 D_800A3650;
extern u8 D_800A39E4Small;

#ifdef NON_MATCHING
/* w9f: D_800A39E4Small unlock works (gp lbu matches). Remaining wall:
 * the then-branch must interleave load,load,add,store,add,store with
 * EC->v1 / A18->v0 (v1 reused for both increment results, anti-dep
 * keeps the second addiu below the first store). Every plain-C form
 * tried (+=, hoisted local, explicit count/next locals, asm("") barrier)
 * gives loads->v0/v1 in C order with both addius before the first store;
 * the asm("") form splits too far (+8, reloads after the store).
 * gPrimitiveCursor[0] += 0x28 also ICEs cc1 at this TU position (0-symbol
 * object); read/store it via D_800A36D0Absolute[-67] instead. */
void func_80057CCC(s32 arg0) {
    s32 cursor;

    arg0 &= 0xFF;
    if (arg0 != 0) {
        D_800A36EC += 1;
        D_800A3A18 += 0x28;
    } else if (D_800A39E4Small != 0x80) {
        D_800A3964 += 1;
        cursor = D_800A36D0Absolute[-67];
        D_800A36D0Absolute[-67] = cursor + 0x28;
    } else {
        D_800A36D0Absolute[-21] = D_800A36D0Absolute[-21] + 0x28;
    }
}

void func_80057D50(s32 arg0) {
    s32 cursor;

    arg0 &= 0xFF;
    if (arg0 != 0) {
        D_800A3580 += 1;
        D_800A35B8 += 0x18;
    } else if (D_800A39E4Small != 0x80) {
        D_800A3650 += 1;
        cursor = D_800A36D0Absolute[-67];
        D_800A36D0Absolute[-67] = cursor + 0x28;
    } else {
        D_800A36D0Absolute[-21] = D_800A36D0Absolute[-21] + 0x28;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80057CCC);

INCLUDE_ASM("asm/nonmatchings/game", func_80057D50);
#endif

extern s32 D_800A38EC, D_800A3650, D_800A3544;
void func_80057DD4(void) {
    D_800A3650 = 0;
    D_800A3544 = D_800A38EC;
}

extern s32 D_800A3580, D_800A35B8, D_800A3780;
void func_80057DE8(void) {
    D_800A3580 = 0;
    D_800A35B8 = D_800A3780;
}

extern s32 D_800A3964, D_800A39A8, D_800A39CC;
void func_80057DFC(void) {
    D_800A3964 = 0;
    D_800A39CC = D_800A39A8;
}

extern s32 D_800A36EC, D_800A3998, D_800A3A18;
void func_80057E10(void) {
    D_800A36EC = 0;
    D_800A3A18 = D_800A3998;
}

extern u8 D_800BDD62[], D_800BDDBE[], D_800BDDC0[], D_800BDD64[];
extern u8 D_800BDD65[], D_800BDD66[], D_800BDD67[], D_800BDDC1[];
extern u8 D_800BDDC2[], D_800BDDC3[];
extern DRAWENV D_800BDD4C[];
extern DISPENV D_800BDE04[];
void func_80057E24(void) {
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
extern s32 D_800A39C8[];
void func_80057F34(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *env;
    u32 *ot;
    s32 cond;

    cond = (arg0 != 0);
    arg1 += -cond & 0x140;
    SetDefDrawEnv((DRAWENV *)D_800A8C14, arg1, arg2, arg3, arg4);
    env = D_800A8B94 + arg0 * 0x40;
    SetDrawEnv((DR_ENV *)env, (DRAWENV *)D_800A8C14);
    ot = (u32 *)D_800A39C8[0];
    AddPrim(ot + arg5, env);
}

void func_80057FC8(s32 hide) {
    if (hide & 0xFF) {
        SetDispMask(0);
        SetGraphDebug(0);
    }
    SetGeomScreen(0x82);
}

s32 func_80041B7C(s32);
void func_80058000(s32 index, s32 *out) {
    *out = func_80041B7C(index & 0xFF);
}

extern s32 D_800A305C;
extern DISPENV D_800BDE04[];
extern DRAWENV D_800BDD4C[];
void func_80058030(void) {
    PutDispEnv(&D_800BDE04[D_800A305C]);
    PutDrawEnv(&D_800BDD4C[D_800A305C]);
}

#if 0
/* Wall: sector/size land in s0/s2, retail has s2/s0. Decl order
 * (sector,size) and (size,sector) both swap; blocks-as-local also swaps.
 * D_800A3090 must be reached as D_800A2EB0Absolute + 120 (declaring the
 * untracked sdata label drifts data labels). asm-differ -m compares the
 * LINKED exe, so run a relink before trusting a unit diff here. */
extern s32 func_8003C584(s32, s32);
extern s32 func_8003C8BC(s32, s32, s32);
extern s32 func_8003C644(s32, s32, s32, s32);
extern s32 func_8003C63C(s32);
extern s32 D_800A2EB0Absolute[];
s32 func_80058094(s32 arg0, s32 *arg1, s32 data) {
    s32 size;
    s32 sector;

    sector = func_8003C584(arg0, D_800A2EB0Absolute + 120);
    size = (func_8003C8BC(sector, 0, 2) + 0x7FF) >> 11 << 11;
    if (data == 0) {
        data = (s32)HeapAlloc(size);
    }
    func_8003C8BC(sector, 0, 0);
    func_8003C644(data, 1, size, sector);
    func_8003C63C(sector);
    *arg1 = data + 4;
    return data;
}
#endif
INCLUDE_ASM("asm/nonmatchings/game", func_80058094);

INCLUDE_ASM("asm/nonmatchings/game", func_80058148);

INCLUDE_ASM("asm/nonmatchings/game", func_8005833C);

extern u8 D_800BE70C[];
u8 TableFindByte(u8 value) {
    s32 i;
    for (i = 0; i < 24; i++) {
        if (D_800BE70C[i] == value) {
            return i;
        }
    }
    return 255;
}

INCLUDE_ASM("asm/nonmatchings/game", func_800587A0);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008D738);

/* func_80058D08: writes $gp directly; not expressible in C. */
void func_80058D08(s32 gp) {
    /* Retail writes the new global pointer directly; not expressible
     * in plain C (see kb/psx/matching.md func_80062874). */
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

INCLUDE_ASM("asm/nonmatchings/game", func_80058D94);

#ifdef NON_MATCHING
/*
 * w8g: full body reached an exact unit diff EXCEPT data labels: any
 * active C here (even size-identical to the stub) shifts the sdata
 * labels -0xC and a shorter body shifts them differently (see
 * matching.md). text side (all verified, keep these when retrying):
 * - D_800A2EB0=-1 / D_800A2EA8=3 via D_800A2EB0Absolute[0] / [-2]
 * - D_800A2CE0 twice via DISTINCT aliases (A2E24[-0x151] first,
 *   A2EB0Absolute[-0x74] in the arm) or gcc hoists the address into s0
 * - store the arm call result DIRECTLY (`D[...] = RandomScaledGet(0x10);`)
 *   or gcc keeps the old value alive in v1 (`move v1,v0`, bne flipped)
 * - tail: seed=D_800A36E0 (lbu gp), A2EA4/A2EDC/A2EE0 as u8 arrays
 *   (lui), A38F0/A3A60 as u8 arrays (lui), A3064/A3065/A3718 scalar
 *   (gp); u8 arrays DO get lui here, do not cast them (cast form
 *   segfaults cc1 at this TU position)
 * - CAST-FORM STORES `((u8 *)D_800A2EC8Absolute)[n] = v;` DETONATE cc1
 *   here (0-symbol object, exit 0). Direct u8[] externs are fine.
 */
extern u8 D_800A2EDC[];
extern u8 D_800A2EE0[];
extern u8 D_800A38F0[];
extern u8 D_800A3A60[];
extern u8 D_800A3064;
extern u8 D_800A3065;
extern u8 D_800A3718;
extern u8 D_800A36E0;
void func_8005957C(void) {
    s32 value;
    u8 seed;

    D_800A2EB0Absolute[0] = -1;
    D_800A2EB0Absolute[-2] = 3;
    value = RandomScaledGet(0x11);
    D_800A2E24Absolute[-0x151] = value;
    if (value == 0x10) {
        D_800A2EB0Absolute[-0x74] = RandomScaledGet(0x10);
    }
    seed = D_800A36E0;
    D_800A2EA4[0] = 0;
    D_800A2EDC[0] = 0;
    D_800A2EE0[0] = 1;
    D_800A38F0[0] = 0;
    D_800A3A60[0] = 0;
    D_800A3064 = 0;
    D_800A3065 = 0;
    D_800A3718 = seed;
}
#endif
extern u32 D_800A2EA4NM[] asm("D_800A2EA4.NON_MATCHING");
extern u8 D_800A2EDCNM[] asm("D_800A2EDC.NON_MATCHING");
extern u8 D_800A2EE0NM[] asm("D_800A2EE0.NON_MATCHING");
extern u8 D_800A38F0NM[] asm("D_800A38F0.NON_MATCHING");
extern u8 D_800A3A60NM[] asm("D_800A3A60.NON_MATCHING");
extern u8 D_800A3064NM asm("D_800A3064.NON_MATCHING");
extern u8 D_800A3065NM asm("D_800A3065.NON_MATCHING");
extern u8 D_800A3718NM asm("D_800A3718.NON_MATCHING");
extern u8 D_800A36E0NM asm("D_800A36E0.NON_MATCHING");
void func_8005957C(void) {
    s32 value;
    u8 seed;

    D_800A2EB0Absolute[0] = -1;
    D_800A2EB0Absolute[-2] = 3;
    value = RandomScaledGet(0x11);
    D_800A2E24Absolute[-0x51] = value;
    if (value == 0x10) {
        D_800A2EB0Absolute[-0x74] = RandomScaledGet(0x10);
    }
    seed = D_800A36E0NM;
    D_800A2EA4NM[0] = 0;
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
extern void *HeapAlloc(u32);
extern void HeapFree(void *);
void func_80059648(void) {
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
INCLUDE_ASM("asm/nonmatchings/game", func_80059648);
#endif

extern u8 D_800A2F9CAbsolute[];
extern u8 D_800A3694;
extern void func_8003CAE8(s32);
extern void CdSetMixVolume(s32);
void func_800596F4(void) {
    D_800A2F9CAbsolute[0] = 1;
    func_8003CAE8(3);
    CdSetMixVolume(D_800A3694);
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

#if 0
/* Wall: only size/buf land in s1/s0 where retail has s0/s1 (same
 * allocator wall as func_80058094); everything else matches.
 * w9g: D_800A3090 is now name-true (direct extern compiles, no drift in
 * unit diffs); retail also sinks the `buf = HeapAlloc(size)` copy into
 * the second func_8003C8BC delay slot after pre-setting a2 one slot
 * earlier - ours emits `move buf,v0` early and fills the delay with
 * `move a2,zero`. Swapping the buf/size decl order does NOT flip the
 * allocation. The *next* load must be written BEFORE the
 * D_800A381C/D_800A3638 stores or the function grows 4 bytes. */
extern s32 D_800A381C, D_800A3638, D_800A37EC;
extern s32 D_800A3090[];
void func_8005978C(void) {
    extern s32 func_8003C584(s32, s32);
    extern s32 func_8003C8BC(s32, s32, s32);
    extern s32 func_8003C644(s32, s32, s32, s32);
    extern s32 func_8003C63C(s32);
    DISPENV env;
    s32 sector;
    s32 size;
    s32 buf;
    s32 next;

    sector = func_8003C584(0, D_800A3090);
    size = (func_8003C8BC(sector, 0, 2) + 0x7FF) >> 11 << 11;
    buf = (s32)HeapAlloc(size);
    func_8003C8BC(sector, 0, 0);
    func_8003C644(buf, 1, size, sector);
    func_8003C63C(sector);
    next = *(s32 *)(buf + 0x10);
    D_800A381C = buf + 4;
    D_800A3638 = buf;
    buf += next;
    D_800A37EC = buf;
    func_80013224((void *)buf);
    DrawSync(0);
    SetDefDispEnv(&env, 0x140, 0, 0x140, 0xF0);
    PutDispEnv(&env);
    SetDispMask(1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8005978C);
#endif

/* Memory card files and events. */

void CardCloseFile(s32 handle) {
    if (handle != -1)
        close(handle);
}

u8 CardDeleteFile(char *path) {
    return delete(path);
}

extern void CardTestEvents(void);
extern void func_8005A414(void);
extern s32 func_800598FC(void);
void func_800598C4(void) {
    CardTestEvents();
    func_8005A414();
    func_800598FC();
    ChangeClearPAD(0);
}

#ifdef NON_MATCHING
extern u32 D_800A3824, D_800A3828, D_800A382C, D_800A3834;
extern s32 D_800A38C8, D_800A38CC, D_800A38D0, D_800A38D4;
extern s32 DisableEvent(s32);
s32 func_800598FC(void) {
    s32 result;
    s32 enabled;

    EnterCriticalSection();
    enabled = DisableEvent(D_800A3824) != 0;
    result = enabled;
    if (enabled == 0) {
        result = 0;
    }
    if (DisableEvent(D_800A3828) == 0) {
        result = 0;
    }
    if (DisableEvent(D_800A382C) == 0) {
        result = 0;
    }
    if (DisableEvent(D_800A3834) == 0) {
        result = 0;
    }
    if (DisableEvent(D_800A38C8) == 0) {
        result = 0;
    }
    if (DisableEvent(D_800A38CC) == 0) {
        result = 0;
    }
    if (DisableEvent(D_800A38D0) == 0) {
        result = 0;
    }
    if (DisableEvent(D_800A38D4) == 0) {
        result = 0;
    }
    ExitCriticalSection();
    return result;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800598FC);
#endif

extern s32 CardEnableEvents(void);
extern void CardTestEvents(void), func_8005A414(void);
extern s32 func_8005A294(void);
void func_800599E4(void) {
    CardEnableEvents();
    CardTestEvents();
    func_8005A414();
}

#ifdef NON_MATCHING
/* Wall: with asm("") in each if-body the branch shape matches; the
 * remaining diff is the first normalize: retail computes
 * sltu v0,zero,v0 (in v0, before the second call) then copies it to
 * s0 in the second jal's delay slot. gcc 2.7.2 coalesces the compare
 * straight into s0 (tried: two locals enabled/result, split
 * `enabled = call(); enabled = enabled != 0;` -- both copy-propagate
 * back to sltu s0,zero,v0). */
extern u32 D_800A3824, D_800A3828, D_800A382C, D_800A3834;
extern s32 D_800A38C8, D_800A38CC, D_800A38D0, D_800A38D4;
s32 CardEnableEvents(void) {
    s32 enabled;
    s32 result;

    EnterCriticalSection();
    enabled = EnableEvent(D_800A3824);
    enabled = enabled != 0;
    result = enabled;
    if (EnableEvent(D_800A3828) == 0) {
        asm("");
        result = 0;
    }
    if (EnableEvent(D_800A382C) == 0) {
        asm("");
        result = 0;
    }
    if (EnableEvent(D_800A3834) == 0) {
        asm("");
        result = 0;
    }
    if (EnableEvent(D_800A38C8) == 0) {
        asm("");
        result = 0;
    }
    if (EnableEvent(D_800A38CC) == 0) {
        asm("");
        result = 0;
    }
    if (EnableEvent(D_800A38D0) == 0) {
        asm("");
        result = 0;
    }
    if (EnableEvent(D_800A38D4) == 0) {
        asm("");
        result = 0;
    }
    ExitCriticalSection();
    return result;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", CardEnableEvents);
#endif

extern s32 func_8005A294(void);
extern void func_8005A414(void);
#ifdef NON_MATCHING
/* Wall (w7a): everything matches except two constant-handling rows.
 * 1) gcc 2.7.2 hoists the compare/return constant into the prologue
 * (li s3,0x3 before sw ra, frame 0x28 vs retail 0x20); retail
 * re-materializes li v0,0x3 at the loop-top compare (in the beqz
 * delay slot) and again at the return-3 merge. Switch form (case 0 /
 * case 3) and if-forms both hoist; the hoist survives every shape
 * tried (4 variants). 2) arg1's test: retail does andi v0,s2,0xff +
 * bnez v0 at the use with s2 holding the raw a1 copy; ours hoists
 * the mask into the prologue (andi s2,a1,0xff) for s32/u32/u8 arg1
 * alike, or drops the andi for a plain s32 `arg1 != 0`. sltiu loop
 * bound requires u32 retries; the (arg0&0xFF)!=0*0x10 channel line
 * and the call/branch schedule match. */
extern s32 func_8005A294(void);
extern void func_8005A414(void);
s32 CardCheckStatus(s32 arg0, u8 arg1) {
    s32 channel;
    u32 retries;
    s32 status;

    channel = ((arg0 & 0xFF) != 0) * 0x10;
    retries = 0;
    do {
        _card_info(channel);
        status = func_8005A294();
        if (status == 0) {
            return 0;
        }
        if (status == 3) {
            func_8005A414();
            _card_clear(channel);
            status = CardWaitForEvent();
            if (arg1 != 0) {
                return 3;
            }
            if (status == 0) {
                return 3;
            }
        }
        retries++;
    } while ((retries & 0xFF) < 8);
    return status & 0xFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", CardCheckStatus);
#endif

s32 CardFindFirstFile(char *path, struct DIRENTRY *entry) {
    return firstfile(path, entry) == entry;
}

extern char D_800A3094[], D_800A309C[];
s32 CardFormat(s32 second) {
    if (!(second & 0xFF))
        return format(D_800A309C) & 0xFF;
    else
        return format(D_800A3094) & 0xFF;
}

void func_80059C2C(void) {
    extern u32 D_800A3824, D_800A3828, D_800A382C, D_800A3834;
    extern s32 D_800A38C8, D_800A38CC, D_800A38D0, D_800A38D4;
    register s32 flag asm("s0");
    s32 value;

    EnterCriticalSection();
    D_800A3824 = OpenEvent(0xF4000001, 4, 0x2000, 0);
    value = OpenEvent(0xF4000001, 0x8000, 0x2000, 0);
    flag = -1;
    D_800A3828 = value;
    asm("" : : "r"(flag) : "memory");
    D_800A382C = OpenEvent(0xF4000001, 0x100, 0x2000, 0);
    asm("" : : : "memory");
    D_800A3834 = OpenEvent(0xF4000001, 0x2000, 0x2000, 0);
    asm("" : : : "memory");
    D_800A38C8 = OpenEvent(0xF0000011, 4, 0x2000, 0);
    asm("" : : : "memory");
    D_800A38CC = OpenEvent(0xF0000011, 0x8000, 0x2000, 0);
    asm("" : : : "memory");
    D_800A38D0 = OpenEvent(0xF0000011, 0x100, 0x2000, 0);
    asm("" : : : "memory");
    D_800A38D4 = OpenEvent(0xF0000011, 0x2000, 0x2000, 0);
    asm("" : : : "memory");
    ExitCriticalSection();
}

extern s32 CloseEvent(s32);
extern u32 D_800A3824;
extern u32 D_800A3828;
extern u32 D_800A382C;
extern u32 D_800A3834;
extern s32 D_800A38C8;
extern s32 D_800A38CC;
extern s32 D_800A38D0;
extern s32 D_800A38D4;

void CardCloseEvents(void) {
    EnterCriticalSection();
    CloseEvent(D_800A3824);
    CloseEvent(D_800A3828);
    CloseEvent(D_800A382C);
    CloseEvent(D_800A3834);
    CloseEvent(D_800A38C8);
    CloseEvent(D_800A38CC);
    CloseEvent(D_800A38D0);
    CloseEvent(D_800A38D4);
    ExitCriticalSection();
}

extern void func_80059C2C(void);
void func_80059DC4(void) {
    func_80059C2C();
    InitCARD(1);
    _card_auto(0);
    StartCARD();
    _bu_init();
    ChangeClearPAD(0);
}

void func_80059E0C(void) {
    extern void StopCARD(void);

    StopCARD();
    EnterCriticalSection();
    DisableEvent(D_800A3824);
    DisableEvent(D_800A3828);
    DisableEvent(D_800A382C);
    DisableEvent(D_800A3834);
    DisableEvent(D_800A38C8);
    DisableEvent(D_800A38CC);
    DisableEvent(D_800A38D0);
    DisableEvent(D_800A38D4);
    ExitCriticalSection();
    EnterCriticalSection();
    CloseEvent(D_800A3824);
    CloseEvent(D_800A3828);
    CloseEvent(D_800A382C);
    CloseEvent(D_800A3834);
    CloseEvent(D_800A38C8);
    CloseEvent(D_800A38CC);
    CloseEvent(D_800A38D0);
    CloseEvent(D_800A38D4);
    ExitCriticalSection();
}

extern s32 func_8005A294(void);
extern void CardTestEvents(void);
extern s32 CardWaitForEvent(void);
extern void func_8005A414(void);
s32 func_80059F0C(s32 arg0) {
    s32 retries = 0;
    register s32 channel asm("s1") = ((arg0 & 0xFF) != 0) * 0x10;
    s32 status;
    do {
        _card_info(channel);
        status = func_8005A294();
        if (status == 3) {
            func_8005A414();
            _card_clear(channel);
            status = CardWaitForEvent();
        }
        if (status == 0) {
            CardTestEvents();
            _card_load(channel);
            status = func_8005A294();
            if (status == 0)
                break;
        }
        asm("");
        retries++;
        if (status == 0)
            break;
    } while ((retries & 0xFF) < 8U);
    return status & 0xFF;
}

s32 CardOpenFile(char *path, s32 flags) {
    if (flags == 0x200) {
        flags = 0x10200;
    }
    return open(path, flags);
}

#ifdef NON_MATCHING
/* w9g draft. Semantics fully mapped; two walls remain.
 * VERIFIED (w9g): the caller-saved limit shape DOES reproduce retail's
 * `addu a2,v0,a2; slt v0,v0,a2` - use `limit = (sector & 0xFFFF) +
 * arg2; if ((sector & 0xFFFF) >= limit) return 1; retries = 0;
 * end = limit;` with the in-place `arg2 = arg2 & 0xFF;` first statement
 * (gives the early prologue andi) and limit declared last.
 * WALL 1: s-reg rotation - sector=s1/retries=s2/offset=s0 where retail
 * has s0/s1/s2 (decl order does not flip it; both orders tried).
 * WALL 2: gcc inverts the limit guard to bnez + folds both early
 * returns into `li v0,1; j` / `move v0,zero; j` copies; retail keeps
 * `beqz v0 -> shared ori v0,1 block` with `move s1,zero` (retries=0)
 * in the branch delay slot, and `move s3,a2` (end) right after the
 * guard where ours sinks it below `move s0,zero`. Same fold family as
 * func_80059F0C - breaks-to-shared-blocks may be the cure here too. */
extern void func_8005A414(void);
extern void _new_card(void);
extern void _card_read(s32, s32, s32);
extern s32 CardWaitForEvent(void);
s32 func_8005A000(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 buf) {
    s32 channel;
    s32 sector;
    s32 offset;
    s32 retries;
    s32 end;
    s32 limit;
    channel = ((arg3 & 0xFF) != 0) * 0x10;
    arg2 = arg2 & 0xFF;
    if (buf == 0)
        return 1;
    offset = 0;
    sector = (arg1 & 0xFF) + *(s32 *)(arg0 + 0x20);
    limit = (sector & 0xFFFF) + arg2;
    if ((sector & 0xFFFF) >= limit)
        return 1;
    retries = 0;
    end = limit;
    do {
        func_8005A414();
        _new_card();
        _card_read(channel, sector & 0xFFFF, buf + offset);
        if (CardWaitForEvent() == 0) {
            sector += 1;
            offset += 0x80;
            retries = 0;
        } else if ((retries & 0xFF) < 0xB) {
            retries += 1;
        } else {
            return 0;
        }
    } while ((sector & 0xFFFF) < end);
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8005A000);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8005A0F0);

#ifdef NON_MATCHING
/* Wall (w7a): whole body matches except a two-register swap: gcc keeps
 * i in s1 and total in s2 under every init/declaration order tried
 * (retail: i=s2, total=s1; count=s3, entry=s0 match). Frame rule found
 * en route: gcc rounds a local DIRENTRY array of 16 up by 0x20 (frame
 * 0x2a8 vs retail 0x288) but leaves 15 alone — retail's locals are
 * 0x260 = 15*0x28 + 8. entries[15] + a volatile s32 framePad[2] gives
 * the exact frame; call-per-arm with the ==0 branch sense reproduces
 * the bnez/per-arm-a0/single-jal merge, i=0 before the blez lands,
 * total=0 fills the blez delay slot. Only the s1/s2 swap remains.
 * (framePad dropped again here — with it gcc renames nothing; without
 * the frame is 8 short but the draft is guarded anyway.) */
extern char D_800A3094[], D_800A309C[];
s32 CardCountOtherFileBlocks(s32 arg0, char *name) {
    struct DIRENTRY entries[15];
    s32 count;
    register u32 total asm("s1");
    s32 i;
    struct DIRENTRY *entry;

    if ((arg0 & 0xFF) == 0) {
        count = CardScanDirectory(D_800A309C, entries);
    } else {
        count = CardScanDirectory(D_800A3094, entries);
    }
    i = 0;
    total = 0;
    if (count > 0) {
        entry = entries;
        do {
            if (strcmp(entry->name, name) != 0) {
                total += entry->size;
            }
            i++;
            entry++;
        } while (i < count);
    }
    return (total >> 13) & 0xFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", CardCountOtherFileBlocks);
#endif

s32 func_8005A294(void) {
    u32 i;

    i = 0;
    do {
        i++;
        if (TestEvent(D_800A3824) == 1) {
            return 0;
        }
        if (TestEvent(D_800A3828) == 1) {
            return 1;
        }
        if (TestEvent(D_800A382C) == 1) {
            return 2;
        }
        if (TestEvent(D_800A3834) == 1) {
            return 3;
        }
    } while (i < 0x40000);
    return 1;
}

extern u32 D_800A3824, D_800A3828, D_800A382C, D_800A3834;
void CardTestEvents(void) {
    TestEvent(D_800A3824);
    TestEvent(D_800A3828);
    TestEvent(D_800A382C);
    TestEvent(D_800A3834);
}

extern s32 D_800A38C8;
extern s32 D_800A38CC;
extern s32 D_800A38D0;
extern s32 D_800A38D4;

s32 CardWaitForEvent(void) {
    u32 tries;

    tries = 0;
    for (;;) {
        tries++;
        if (TestEvent(D_800A38C8) == 1)
            return 0;
        if (TestEvent(D_800A38CC) == 1)
            return 1;
        if (TestEvent(D_800A38D0) == 1)
            return 2;
        if (TestEvent(D_800A38D4) == 1)
            return 3;
        if (tries > 0x3FFFFU)
            return 1;
    }
}

extern s32 D_800A38C8;
extern s32 D_800A38CC;
extern s32 D_800A38D0;
extern s32 D_800A38D4;

void func_8005A414(void) {
    TestEvent(D_800A38C8);
    TestEvent(D_800A38CC);
    TestEvent(D_800A38D0);
    TestEvent(D_800A38D4);
}

extern char D_800A30A4[];

s32 CardScanDirectory(char *path, struct DIRENTRY *entry) {
    char buffer[128];
    struct DIRENTRY *cursor;
    s32 count;

    strcpy(buffer, path);
    strcat(buffer, D_800A30A4);
    cursor = entry;
    count = 0;
    if (firstfile(buffer, cursor) == cursor) {
        do {
            count++;
            cursor++;
        } while (nextfile(cursor) == cursor);
    }
    return count;
}

extern s32 D_800B1EBC[];
extern s32 D_800A39E8;
extern u16 D_800A3874;
extern s32 D_800A3768;
extern void func_8005A818(u8, u8, u8);
void func_8005A4E0(void) {
    u8 i;

    for (i = 0; i < 5; i++) {
        D_800B1EBC[i] = 0;
    }
    D_800A3874 = 0;
    D_800A3768 = D_800A39E8;
    func_8005A818(0xFF, 0x80, 0x40);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005A544);

INCLUDE_ASM("asm/nonmatchings/game", func_8005A6EC);

extern s32 D_800A35A0;
extern u8 D_800A3534;
extern s32 D_800A3750;
extern s32 D_800A35AC;
extern s32 D_800B1EBC[];
extern s32 D_80099FE4[][3];
void func_8005A7B8(u8 arg0, u8 arg1) {
    s32 *entry;
    s32 word;

    word = D_800B1EBC[arg0];
    entry = &D_80099FE4[arg1][0];
    D_800A35A0 = (s32)entry;
    D_800A3534 = arg1;
    D_800A3750 = word;
    D_800A35AC = entry[2];
}

extern u8 D_800A37C8, D_800A37A8, D_800A378C;
void func_8005A804(u8 a, u8 b, u8 c) {
    D_800A37C8 = a;
    D_800A37A8 = b;
    D_800A378C = c;
}

extern u8 D_800A3618;
extern u8 D_800A3624;
extern u8 D_800A364C;

void func_8005A818(u8 first, u8 second, u8 third) {
    D_800A364C = first;
    D_800A3624 = second;
    D_800A3618 = third;
}

extern u8 D_800A3618;
extern u8 D_800A3624;
extern u8 D_800A364C;

void func_8005A82C(void) {
    D_800A364C = 0xFF;
    D_800A3624 = 0x80;
    D_800A3618 = 0x40;
}

extern u8 D_800A3534;
extern s32 D_800A35AC;
s16 func_8005A84C(void) {
    s32 res;
    if (D_800A3534 == 2) {
        res = *(s16 *)(D_800A35AC + 8) * 3;
        if (res < 0)
            res += 3;
        return (s16)((res << 0xE) >> 0x10);
    } else if (D_800A3534 == 4) {
        return (s16)((*(s16 *)(D_800A35AC + 8) * 9 / 10 << 0x10) >> 0x10);
    }
    return *(s16 *)(D_800A35AC + 8);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005A8E0);

INCLUDE_ASM("asm/nonmatchings/game", func_8005A9F4);

INCLUDE_ASM("asm/nonmatchings/game", func_8005AEC8);

s16 func_8005AFF0(s8 arg0) {
    s32 index;
    s32 entry;
    register s32 scaled asm("v0");
    register s32 value asm("v1");
    s32 product;
    s32 quotient;

    entry = *(u16 *)D_800A35A0;
    index = 0;
    if (arg0 >= 0x20 && arg0 < entry + 0x20) {
        index = arg0 - 0x20;
    }
    if (D_800A3534 == 2) {
        scaled = *(s16 *)(D_800A35AC + index * 0xA + 6) * 3;
        value = (u32)scaled >> 2;
        if (scaled < 0) {
            scaled += 3;
            value = (u32)scaled >> 2;
        }
    } else if (D_800A3534 == 4) {
        value = *(s16 *)(D_800A35AC + index * 0xA + 6);
        asm("" ::"r"(value));
        product = value * 9;
        value = product / 10;
    } else {
        value = *(u16 *)(D_800A35AC + index * 0xA + 6);
    }
    if (D_800A3534 < 2U) {
        value -= 1;
    }
    return (s16)value;
}

extern s16 func_8005A8E0(s32);
s32 func_8005B0E4(s16 arg0, s32 arg1) {
    s32 limit;

    limit = func_8005A8E0(arg1);
    if (arg0 < limit) {
        return 0;
    }
    return (arg0 - limit) >> 1;
}

#ifdef NON_MATCHING
s32 func_8005B138(u8 *str) {
    s32 count;
    u8 c;

    count = 0;
    c = *str;
    while (c != 0) {
        if (c == 0xA) {
            count++;
        }
        str++;
        c = *str;
    }
    return count + 1;
}
#else
s32 func_8005B138(u8 *str) {
    s32 count;

    count = 0;
    if (*str != 0) {
        do {
            if (*str == 0xA) {
                asm("");
                count++;
            }
            str++;
        } while (*str != 0);
    }
    return count + 1;
}
#endif

void func_8005B17C(u8 *dst, u32 idx, u16 dx, u16 dy, u16 ax, u16 ay) {
    struct Tab14 {
        u16 f0;
        u16 f2;
        u16 f4;
        u16 f6;
        u8 f8;
        u8 f9;
        u8 fA;
        u8 fB;
        u16 fC;
    };
    extern struct Tab14 D_8009AEA0[];
    struct Tab14 *entry;

    entry = &D_8009AEA0[idx & 0xFF];
    *(u16 *)(dst + 0xE) = GetClut(entry->f4, entry->f6);
    *(u16 *)(dst + 0x16) = GetTPage(entry->fC, 3, entry->f0, entry->f2);
    dst[0xC] = entry->f8 + dx;
    dst[0xD] = entry->fA + dy;
    dst[0x14] = entry->f8 + dx + ax;
    dst[0x15] = entry->fA + dy;
    dst[0x1C] = entry->f8 + dx;
    dst[0x1D] = entry->fA + dy + ay;
    dst[0x24] = entry->f8 + dx + ax;
    dst[0x25] = entry->fA + dy + ay;
}

extern u8 D_800A35EC;
extern u8 *D_800A3678;
u8 *func_8005B2AC(void) {
    u8 index;
    u8 *object;
    index = D_800A35EC++;
    object = D_800A3678 + index * 36;
    *(s16 *)(object + 0x12) = 0;
    *(s16 *)(object + 0x14) = 0;
    *(s32 *)(object + 0x1C) = 0;
    object[4] = 0;
    object[3] = 0;
    object[2] = 0;
    *(s16 *)(object + 0x1A) = 0;
    return object;
}

extern u8 D_800A37BC, D_800A35EC;
void func_8005B2F0(void) {
    D_800A37BC = 0;
    D_800A35EC = 0;
}

extern u8 D_800A39C4, D_800A37BC, D_800A35EC;
void func_8005B300(void) {
    D_800A37BC = 0;
    D_800A35EC = D_800A39C4;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005B314);

INCLUDE_ASM("asm/nonmatchings/game", func_8005B474);

#ifdef NON_MATCHING
/* w7g: everything matches except the store `*(s16 *)(object + 0x10) = 0`
 * must land in the FIRST jal's delay slot. C order call-then-store puts
 * it in the SECOND jal's delay; store-then-call emits sh,jal,nop
 * (function 4 bytes long, 0xF4 vs 0xF0). asm("") after the call breaks
 * the delay fill entirely. Also note func_80057CCC takes the `texture`
 * arg and the whole function is otherwise byte-clean. */
extern u8 D_800A35EC;
extern u8 *D_800A3678;
POLY_FT4 *func_80057CCC(u8);
u8 *func_8005B598(s16 left, s16 top, s16 right, s16 bottom, s32 depth,
                  u8 texture, u8 semiTrans) {
    u8 index;
    u8 *object;
    POLY_FT4 *poly;
    index = D_800A35EC++;
    object = D_800A3678 + index * 36;
    *(s16 *)(object + 0x12) = 0;
    *(s16 *)(object + 0x14) = 0;
    *(s32 *)(object + 0x1C) = 0;
    object[4] = 0;
    object[3] = 0;
    object[2] = 0;
    *(s16 *)(object + 0x1A) = 0;
    *(s16 *)(object + 0x0) = 1;
    *(s16 *)(object + 0xA) = left;
    *(s16 *)(object + 0x6) = left;
    *(s16 *)(object + 0xC) = top;
    *(s16 *)(object + 0x8) = top;
    *(s16 *)(object + 0x16) = right;
    *(s16 *)(object + 0x18) = bottom;
    *(s16 *)(object + 0xE) = 0;
    *(s16 *)(object + 0x10) = 0;
    poly = func_80057CCC(texture);
    SetPolyFT4(poly);
    SetShadeTex(poly, 0);
    ((u8 *)poly)[4] = 0x80;
    ((u8 *)poly)[5] = 0x80;
    ((u8 *)poly)[6] = 0x80;
    SetSemiTrans(poly, semiTrans);
    *(POLY_FT4 **)(object + 0x20) = poly;
    *(s16 *)(object + 0x1A) = depth;
    return object;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8005B598);
#endif

void func_8005B688(u8 *first, u8 friction) {
    u8 *object;
    s16 sum;

    object = first;
    if (object != 0) {
        do {
            if (*(s16 *)(object + 0xE) != 0) {
                sum = *(u16 *)(object + 0x6) + *(s16 *)(object + 0xE);
                *(s16 *)(object + 0x6) = sum;
                if ((*(s16 *)(object + 0xE) < 0 &&
                     sum < *(s16 *)(object + 0xA)) ||
                    (*(s16 *)(object + 0xE) > 0 &&
                     *(s16 *)(object + 0xA) < sum)) {
                    *(s16 *)(object + 0xE) = 0;
                    *(u16 *)(object + 0x6) = *(u16 *)(object + 0xA);
                } else if (friction != 0) {
                    *(u16 *)(object + 0xE) = *(u16 *)(object + 0xE) +
                                             (s16) * (u16 *)(object + 0xE) / 2;
                }
            }
            if (*(s16 *)(object + 0x10) != 0) {
                sum = *(u16 *)(object + 0x8) + *(s16 *)(object + 0x10);
                *(s16 *)(object + 0x8) = sum;
                if ((*(s16 *)(object + 0x10) < 0 &&
                     sum < *(s16 *)(object + 0xC)) ||
                    (*(s16 *)(object + 0x10) > 0 &&
                     *(s16 *)(object + 0xC) < sum)) {
                    *(s16 *)(object + 0x10) = 0;
                    *(u16 *)(object + 0x8) = *(u16 *)(object + 0xC);
                } else if (friction != 0) {
                    *(u16 *)(object + 0x10) =
                        *(u16 *)(object + 0x10) +
                        (s16) * (u16 *)(object + 0x10) / 2;
                }
            }
            object = *(u8 **)(object + 0x1C);
        } while (object != 0);
    }
}

extern s32 D_800A39C8[];
void func_8005B7DC(u8 *object, s32 index, u8 semiTrans) {
    u8 *poly;

    poly = *(u8 **)(object + 0x20);
    *(u16 *)(poly + 0x8) = *(u16 *)(object + 0x6);
    *(u16 *)(poly + 0xA) = *(u16 *)(object + 0x8);
    *(u16 *)(poly + 0xC) = *(u16 *)(object + 0x6) + *(u16 *)(object + 0x16);
    *(u16 *)(poly + 0xE) = *(u16 *)(object + 0x8);
    *(u16 *)(poly + 0x10) = *(u16 *)(object + 0x6);
    *(u16 *)(poly + 0x12) = *(u16 *)(object + 0x8) + *(u16 *)(object + 0x18);
    *(u16 *)(poly + 0x14) = *(u16 *)(object + 0x6) + *(u16 *)(object + 0x16);
    *(u16 *)(poly + 0x16) = *(u16 *)(object + 0x8) + *(u16 *)(object + 0x18);
    if (semiTrans != 0xFF) {
        SetSemiTrans(poly, semiTrans);
    }
    AddPrim(D_800A39C8[0] + index * 4, poly);
}

typedef struct {
    u32 unk0[4];
} UnkQuad;
typedef struct {
    u32 unk0[6];
} UnkPrim18;
typedef struct {
    u32 unk0[5];
} UnkPrim14;
typedef struct {
    u32 unk0[2];
} UnkPrim8;

extern u8 *func_80057CCC(s32);
extern u8 *func_80057D50(s32);
extern void func_8005C020(u8 *, u8 *);
extern void func_8005C0F4(u8 *, s32);
extern void func_8005CF34(u8 *, u8, u8, u8, s32);
extern u8 D_800A39E4Absolute[];

void func_8005B8B8(u8 *object, s32 arg1) {
    u8 *src;
    u8 *poly;
    s32 semiTrans;
    s32 half;
    u8 scratch[0x40];

    if (object == 0) {
        return;
    }
    semiTrans = arg1 & 0xFF;
    for (; object != 0; object = *(u8 **)(object + 0x1C)) {
        if (*(s16 *)(object + 0x1A) >= 0) {
            if (D_800A39E4Absolute[0] != 0xD || *(s8 *)(object + 5) != 0) {
                switch (*(u16 *)(object)) {
                case 1: {
                    u8 *prim;
                    u8 *src;
                    u8 *dst;
                    u8 *end;

                    prim = func_80057CCC(0);
                    src = *(u8 **)(object + 0x20);
                    dst = prim;
                    end = src + 0x20;
                    do {
                        *(UnkQuad *)dst = *(UnkQuad *)src;
                        src += 0x10;
                        dst += 0x10;
                    } while (src != end);
                    *(UnkPrim8 *)dst = *(UnkPrim8 *)src;
                    if (D_800A39E4Absolute[0] == 0xD) {
                        *(u16 *)(prim + 0x8) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x12);
                        *(u16 *)(prim + 0xA) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x14);
                        *(u16 *)(prim + 0x10) = *(u16 *)(object + 0x6) +
                                                *(u16 *)(object + 0x12) +
                                                *(u16 *)(object + 0x16);
                        *(u16 *)(prim + 0x12) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x14);
                        *(u16 *)(prim + 0x18) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x12);
                        *(u16 *)(prim + 0x1A) = *(u16 *)(object + 0x8) +
                                                *(u16 *)(object + 0x14) +
                                                *(u16 *)(object + 0x18);
                        *(u16 *)(prim + 0x20) = *(u16 *)(object + 0x6) +
                                                *(u16 *)(object + 0x12) +
                                                *(u16 *)(object + 0x16);
                        *(u16 *)(prim + 0x22) = *(u16 *)(object + 0x8) +
                                                *(u16 *)(object + 0x14) +
                                                *(u16 *)(object + 0x18);
                    } else {
                        *(u16 *)(prim + 0x8) = *(u16 *)(object + 0x6);
                        *(u16 *)(prim + 0xA) = *(u16 *)(object + 0x8);
                        *(u16 *)(prim + 0x10) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x16);
                        *(u16 *)(prim + 0x12) = *(u16 *)(object + 0x8);
                        *(u16 *)(prim + 0x18) = *(u16 *)(object + 0x6);
                        *(u16 *)(prim + 0x1A) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x18);
                        *(u16 *)(prim + 0x20) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x16);
                        *(u16 *)(prim + 0x22) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x18);
                    }
                    AddPrim(D_800A39C8[0] + *(s16 *)(object + 0x1A) * 4, prim);
                    break;
                }
                case 2: {
                    u8 *src2;

                    poly = func_80057D50(0);
                    src2 = *(u8 **)(object + 0x20);
                    *(UnkPrim18 *)poly = *(UnkPrim18 *)src2;
                    if (D_800A39E4Absolute[0] == 0xD) {
                        if (*(s16 *)(object + 0x16) == 0) {
                            break;
                        }
                        if (*(s16 *)(object + 0x18) == 0) {
                            break;
                        }
                        *(u16 *)(poly + 0x8) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x12);
                        *(u16 *)(poly + 0xA) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x14);
                        *(u16 *)(poly + 0xC) = *(u16 *)(object + 0x6) +
                                               *(u16 *)(object + 0x12) +
                                               *(u16 *)(object + 0x16);
                        *(u16 *)(poly + 0xE) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x14);
                        *(u16 *)(poly + 0x10) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x12);
                        *(u16 *)(poly + 0x12) = *(u16 *)(object + 0x8) +
                                                *(u16 *)(object + 0x14) +
                                                *(u16 *)(object + 0x18);
                        *(u16 *)(poly + 0x14) = *(u16 *)(object + 0x6) +
                                                *(u16 *)(object + 0x12) +
                                                *(u16 *)(object + 0x16);
                        *(u16 *)(poly + 0x16) = *(u16 *)(object + 0x8) +
                                                *(u16 *)(object + 0x14) +
                                                *(u16 *)(object + 0x18);
                    } else {
                        *(u16 *)(poly + 0x8) = *(u16 *)(object + 0x6);
                        *(u16 *)(poly + 0xA) = *(u16 *)(object + 0x8);
                        *(u16 *)(poly + 0xC) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x16);
                        *(u16 *)(poly + 0xE) = *(u16 *)(object + 0x8);
                        *(u16 *)(poly + 0x10) = *(u16 *)(object + 0x6);
                        *(u16 *)(poly + 0x12) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x18);
                        *(u16 *)(poly + 0x14) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x16);
                        *(u16 *)(poly + 0x16) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x18);
                    }
                    if (semiTrans != 0xFF) {
                        SetSemiTrans(poly, semiTrans);
                    }
                    AddPrim(D_800A39C8[0] + *(s16 *)(object + 0x1A) * 4, poly);
                    break;
                }
                case 7:
                case 8:
                    poly = func_80057D50(0);
                    src = *(u8 **)(object + 0x20);
                    *(UnkPrim14 *)poly = *(UnkPrim14 *)src;
                    if (*(u16 *)(object) == 7) {
                        half = *(s16 *)(object + 0x16) / 2;
                        if (*(s16 *)(object + 0x18) < 0) {
                            *(u16 *)(poly + 0x8) = *(u16 *)(object + 0x6) +
                                                   *(u16 *)(object + 0x12);
                            *(u16 *)(poly + 0xA) = *(u16 *)(object + 0x8) +
                                                   *(u16 *)(object + 0x14);
                            *(u16 *)(poly + 0xC) = *(u16 *)(object + 0x6) +
                                                   *(u16 *)(object + 0x12) -
                                                   half;
                            *(u16 *)(poly + 0xE) = *(u16 *)(object + 0x8) +
                                                   *(u16 *)(object + 0x14) +
                                                   *(u16 *)(object + 0x18);
                            *(u16 *)(poly + 0x10) = *(u16 *)(object + 0x6) +
                                                    *(u16 *)(object + 0x12) +
                                                    half;
                            *(u16 *)(poly + 0x12) = *(u16 *)(object + 0x8) +
                                                    *(u16 *)(object + 0x14) +
                                                    *(u16 *)(object + 0x18);
                        } else {
                            *(u16 *)(poly + 0x8) = *(u16 *)(object + 0x6) +
                                                   *(u16 *)(object + 0x12);
                            *(u16 *)(poly + 0xA) = *(u16 *)(object + 0x8) +
                                                   *(u16 *)(object + 0x14);
                            *(u16 *)(poly + 0xC) = *(u16 *)(object + 0x6) +
                                                   *(u16 *)(object + 0x12) +
                                                   half;
                            *(u16 *)(poly + 0xE) = *(u16 *)(object + 0x8) +
                                                   *(u16 *)(object + 0x14) +
                                                   *(u16 *)(object + 0x18);
                            *(u16 *)(poly + 0x10) = *(u16 *)(object + 0x6) +
                                                    *(u16 *)(object + 0x12) -
                                                    half;
                            *(u16 *)(poly + 0x12) = *(u16 *)(object + 0x8) +
                                                    *(u16 *)(object + 0x14) +
                                                    *(u16 *)(object + 0x18);
                        }
                    } else {
                        half = *(s16 *)(object + 0x18) / 2;
                        *(u16 *)(poly + 0x8) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x12);
                        *(u16 *)(poly + 0xA) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x14);
                        *(u16 *)(poly + 0xC) = *(u16 *)(object + 0x6) +
                                               *(u16 *)(object + 0x12) +
                                               *(u16 *)(object + 0x16);
                        *(u16 *)(poly + 0xE) = *(u16 *)(object + 0x8) +
                                               *(u16 *)(object + 0x14) + half;
                        *(u16 *)(poly + 0x10) = *(u16 *)(object + 0x6) +
                                                *(u16 *)(object + 0x12) +
                                                *(u16 *)(object + 0x16);
                        *(u16 *)(poly + 0x12) = *(u16 *)(object + 0x8) +
                                                *(u16 *)(object + 0x14) - half;
                    }
                    if (semiTrans != 0xFF) {
                        SetSemiTrans(poly, semiTrans);
                    }
                    AddPrim(D_800A39C8[0] + *(s16 *)(object + 0x1A) * 4, poly);
                    break;

                case 0:
                    func_8005CF34(object, 0, 0, 0, 0);
                    break;
                case 5:
                    func_8005C020(object, scratch);
                    func_8005CF34(object, 0, 0, 0, (s32)scratch);
                    break;
                case 6:
                    func_8005C0F4(object, (s32)scratch);
                    func_8005CF34(object, 0, 0, 9, (s32)scratch);
                    break;
                }
            }
        }
    }
}

void __maspsx_include_asm_hack_pad_8008F94C(void) {
    __asm__(".section .rodata # maspsx-keep\n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern s32 D_800A3654;
extern u8 D_800A37BC;
s32 func_8005BF68(void) {
    u8 index;
    index = D_800A37BC;
    D_800A37BC = index + 1;
    return D_800A3654 + index * 12;
}

#ifdef NON_MATCHING
/*
 * w4d/w7g/w8g: instructions all match retail except ONE v0/v1 role swap:
 * retail keeps the D_800A3678 load in v0 and the spriteIndex*36 chain in
 * v1 (`addu v0,v0,v1`); gcc gives us base in v1, chain in v0, whatever
 * source shape we try (single expr, operand swap, compound +=, separate
 * base local). Suspect TU-position sensitivity (w4b). The TAIL fix from
 * w8g is verified: `*(s32 *)(prim + 4) = 0;` (not prim[4]) gives
 * retail's `sw zero,4(a0)` sunk into the jr delay slot; prim[4]=0 gave
 * sb after jr.
 */
extern u8 D_800A35EC;
extern u8 *D_800A3678;
extern u8 D_800A37BC;
extern s32 D_800A3654;
void func_8005BF8C(s32 left, s32 top) {
    u8 spriteIndex;
    u8 primIndex;
    u8 *object;
    u8 *prim;
    u8 *base;

    spriteIndex = D_800A35EC++;
    asm("");
    base = D_800A3678;
    object = base + spriteIndex * 36;
    object[4] = 0;
    object[3] = 0;
    object[2] = 0;
    primIndex = D_800A37BC;
    *(u16 *)(object + 0xA) = left;
    *(u16 *)(object + 0x6) = left;
    prim = (u8 *)D_800A3654;
    *(u16 *)(object + 0x12) = 0;
    *(u16 *)(object + 0x14) = 0;
    *(u32 *)(object + 0x1C) = 0;
    *(u16 *)(object + 0x1A) = 0;
    *(u16 *)(object + 0x0) = 0;
    *(u16 *)(object + 0xC) = top;
    *(u16 *)(object + 0x8) = top;
    *(u16 *)(object + 0xE) = 0;
    *(u16 *)(object + 0x10) = 0;
    *(u16 *)(object + 0x1A) = 0;
    D_800A37BC = primIndex + 1;
    asm("");
    prim += primIndex * 12;
    *(u32 *)(object + 0x20) = prim;
    prim[0] = 0;
    prim[3] = 0;
    *(s32 *)(prim + 4) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8005BF8C);
#endif

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} Unk4;
typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
} Unk3;
extern Unk4 D_800A3324[];
extern Unk4 D_800A3328[];
extern Unk3 D_800A332C[];
extern u8 D_800A39E4[];
void func_8005C020(u8 *object, u8 *dest) {
    s32 id;

    id = *(s16 *)(*(u8 **)(object + 0x20) + 8);
    if (D_800A39E4[0] == 0xA) {
        if (id == 0xFF) {
            *(Unk4 *)dest = D_800A3324[0];
            return;
        }
        if (id == -1) {
            *(Unk4 *)dest = D_800A3328[0];
            return;
        }
    } else if (D_800A39E4[0] == 0xC) {
        if (id == 0) {
            *(Unk3 *)dest = D_800A332C[0];
            return;
        }
    }
    func_80012EA8(id, dest);
}

extern void func_80018588(void *, s32, s32);
void func_8005C0F4(u8 *object, s32 value) {
    func_80018588(*(void **)(*(u8 **)(object + 0x20) + 8), -1, value);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005C124);

extern u8 *D_800A36F0;
extern u8 *D_800A3690;
extern u8 *D_800A39C0;
extern u8 *D_800A3A28;
extern u8 D_800A3988[];
extern void func_8005A7B8(u8, u8);
extern s16 func_8005A8E0(s32);
void func_8005C8D8(u8 index) {
    u8 *window;
    u8 *prim;
    s32 i;
    s16 result;
    s16 height;

    window = D_800A36F0;
    for (i = 0; i < index; i++) {
        window += 36;
    }
    prim = *(u8 **)(window + 0x20);
    switch (D_800A3988[index]) {
    case 0:
    case 0x80:
        *(s32 *)(prim + 8) = *(s32 *)(D_800A3690 + index * 4 + 4);
        if (D_800A3988[index] == 0x80) {
            prim[0] |= 2;
        } else {
            prim[0] = 0;
        }
        break;
    case 1:
    case 0x81:
        *(s32 *)(prim + 8) = *(s32 *)(D_800A39C0 + index * 4 + 4);
        if (D_800A3988[index] == 0x81) {
            prim[0] |= 2;
        } else {
            prim[0] = 0;
        }
        break;
    case 2:
        *(s32 *)(prim + 8) = *(s32 *)(D_800A3A28 + index * 4 + 4);
        break;
    }
    func_8005A7B8(0, 0);
    result = func_8005A8E0(*(s32 *)(prim + 8));
    height = 0x131 - result;
    *(s16 *)(window + 0x16) = result;
    *(s16 *)(window + 6) = height;
    *(s16 *)(window + 0xA) = height;
}

extern s16 *D_800AE290[];
extern u8 *D_800AE294[];
extern u8 *D_800AE298[];
extern u8 *D_800A35E8[];
extern u8 D_800A3989[];
extern s8 D_800A3A25[];
extern u8 D_800A3644[];
extern u8 D_800A36E0[];
extern u8 D_800A36E1[];
extern void func_80063694(u8, s16, s16, s16);
extern void func_800636EC(u8, u8);
extern void func_80063AE0(s32, s32);
s32 func_8005CA4C(void) {
    s32 i;
    u8 *prim;
    s16 value;

    if (D_800A3988[0] != 0) {
        *(s16 *)((u8 *)D_800AE290[0] + 8) = 0xF1;
        *(s16 *)(D_800AE294[0] + 8) = 0xF1;
        prim = D_800AE298[0];
        value = *(u16 *)((u8 *)D_800AE290[0] + 0xC);
        D_800A3644[0] = 0;
        *(s16 *)(prim + 8) = value;
    } else {
        if (D_800A3A25[0] == 0) {
            return 0;
        }
        for (i = 0; i < 3; i++) {
            *(s16 *)((u8 *)D_800AE290[i] + 8) =
                *(u16 *)((u8 *)D_800AE290[i] + 0xC);
        }
        D_800A3644[0] = 1;
        if (D_800A36E0[0] == D_800A36E0[1]) {
            D_800A36E1[0] = (D_800A36E0[0] + 1) % 24;
            func_800636EC(1, D_800A36E1[0]);
            func_80063AE0(1, D_800A36E0[1]);
        }
        func_80063694(1, -0x3C, *(s16 *)(D_800A35E8[0] + 0xA), 2);
    }
    D_800A3989[0] = D_800A3988[1] ^ 1;
    D_800A3988[0] = D_800A3989[-1] ^ 1;
    func_8005C8D8(1);
    func_8005C8D8(0);
    return 1;
}

extern u8 D_800A35C8;
extern u8 D_800A35C9[];
extern u8 D_800A3338[];
extern char *strcat(char *, char *);
extern u8 *func_80012EA8(s32, u8 *);
void func_8005CBC8(s32 number) {
    u8 *buffer;
    s32 length;

    buffer = D_800A35C9 - 1;
    D_800A35C8 = 0x20;
    length = 1;
    if (number < 0x64) {
        D_800A35C9[0] = 0x20;
        length = 2;
    }
    D_800A35C9[length - 1] = 0;
    func_80012EA8(number, buffer + length);
    strcat(buffer, D_800A3338);
}

extern u8 *D_800A38F8;
extern s32 D_800A37D0[];
void func_8005CC34(void) {
    u8 *prim;
    u8 *buffer;
    s32 number;
    s32 length;
    s16 result;
    s16 height;

    prim = *(u8 **)(D_800A38F8 + 0x20);
    number = D_800A37D0[0];
    buffer = D_800A35C9 - 1;
    D_800A35C8 = 0x20;
    length = 1;
    if (number < 0x64) {
        D_800A35C9[0] = 0x20;
        length = 2;
    }
    D_800A35C9[length - 1] = 0;
    func_80012EA8(number, buffer + length);
    strcat(buffer, D_800A3338);
    func_8005A7B8(prim[1], prim[2]);
    result = func_8005A8E0(*(s32 *)(prim + 8));
    height = 0x131 - result;
    *(s16 *)(D_800A38F8 + 0x16) = result;
    *(s16 *)(D_800A38F8 + 6) = height;
    *(s16 *)(D_800A38F8 + 0xA) = height;
}

/* buffer is pinned to s1 with an explicit-register local: gcc 2.7.2 hands
 * such variables their hard register directly (make_decl_rtl), so
 * global-alloc never ranks it against the D_800BB9E4[id] slot address
 * temp, which takes s2 as in retail. */
extern u8 D_800A331CAbsolute[];
extern u8 *D_800BB9E4[];
extern char *strcpy(char *, const char *);
s32 func_8005CCEC(s32 id, s32 delta, s32 max, s32 min) {
    u8 *prim;
    register u8 *buffer asm("$17");
    s32 length;
    u8 newValue;
    s16 value;
    s32 inRange;

    switch (id & 0xFF) {
    case 1:
        id = 0;
        min = 0x4B;
        max = 0x73;
        break;
    case 2:
        id = 1;
        min = 0x50;
        max = 0x82;
        break;
    case 3:
        id = 2;
        min = 0x5A;
        max = 0x96;
        break;
    case 4:
        id = 3;
        min = 0x4B;
        max = 0x78;
        break;
    case 5:
        id = 4;
        min = 0x32;
        max = 0x64;
        break;
    }
    newValue = D_800A331CAbsolute[id & 0xFF] + delta;
    D_800A331CAbsolute[id & 0xFF] = newValue;
    inRange = 1;
    if (newValue < min) {
        D_800A331CAbsolute[id & 0xFF] = min;
        inRange = 0;
    } else if (newValue > max) {
        D_800A331CAbsolute[id & 0xFF] = max;
        inRange = 0;
    }
    prim = *(u8 **)(D_800BB9E4[id & 0xFF] + 0x20);
    value = D_800A331CAbsolute[id & 0xFF];
    buffer = D_800A35C9 - 1;
    D_800A35C8 = 0x20;
    length = 1;
    if (value < 0x64) {
        D_800A35C9[0] = 0x20;
        length = 2;
    }
    D_800A35C9[length - 1] = 0;
    func_80012EA8(value, buffer + length);
    strcat(buffer, D_800A3338);
    strcpy(*(char **)(prim + 8), (char *)buffer);
    func_8005A7B8(prim[1], prim[2]);
    *(s16 *)(D_800BB9E4[id & 0xFF] + 0x16) = func_8005A8E0(*(s32 *)(prim + 8));
    *(s16 *)(D_800BB9E4[id & 0xFF] + 6) =
        0x131 - *(s16 *)(D_800BB9E4[id & 0xFF] + 0x16);
    *(s16 *)(D_800BB9E4[id & 0xFF] + 0xA) = *(s16 *)(D_800BB9E4[id & 0xFF] + 6);
    return inRange;
}

/* The original toolchain padded this odd-length jump table with one zero
 * word; the C switch regenerates the table, this restores the pad. */
void __maspsx_include_asm_hack_jtblpad_8005CCEC() {
    __asm__(".section .rodata # maspsx-keep \n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern u8 D_800A3078[], D_800A3988[];
extern void func_8005C8D8(u8);
extern s32 func_8005CCECArgs(u8, s32);
asm(".globl func_8005CCECArgs\nfunc_8005CCECArgs = func_8005CCEC");
void func_8005CEDC(void) {
    s32 i;
    D_800A3988[0] = D_800A3078[0];
    i = 0;
    func_8005C8D8(i);
    i = 1;
    do {
        func_8005CCECArgs(i, 0);
        i++;
    } while (i < 6);
}

#ifdef NON_MATCHING
extern void func_8005A9F4(s32, s16, s16, u8, u8, s32, u8, u8);
void func_8005CF34(u8 *window, u8 code, u8 first, u8 second, s32 textId) {
    u8 *prim;

    prim = *(u8 **)(window + 0x20);
    func_8005A7B8(prim[1], prim[2]);
    prim[0] = code;
    if (textId == 0) {
        textId = *(s32 *)(prim + 8);
    }
    if ((*(s32 *)(window + 0) & 0xFFFF0000) != 0 || window[4] != 0) {
        func_8005A818(window[2], window[3], window[4]);
    } else if (prim[1] == 2) {
        func_8005A818(0xFF, 0x80, 0x40);
    } else {
        func_8005A818(0, 0, 0);
    }
    if (D_800A39E4[0] == 0xD) {
        func_8005A9F4(textId,
                      (s16)(*(u16 *)(window + 6) + *(u16 *)(window + 0x12)),
                      (s16)(*(u16 *)(window + 8) + *(u16 *)(window + 0x14)),
                      prim[3], prim[0], *(s32 *)(prim + 4), first, second);
    } else {
        func_8005A9F4(textId, *(s16 *)(window + 6), *(s16 *)(window + 8),
                      prim[3], prim[0], *(s32 *)(prim + 4), first, second);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8005CF34);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8005D094);

#ifdef NON_MATCHING
extern u8 D_800A35EC;
extern u8 *D_800A3678;
extern u8 D_800B9990[];
extern s16 *D_800B12FC[];
extern u16 D_8009AEDC[];
extern u16 D_8009AEDE[];
extern u16 D_8009AEE4[];
extern u16 D_8009AED8[];
extern u16 D_8009AEDA[];
extern u8 D_8009AEE0[];
extern u8 D_8009AEE2[];
extern u8 D_8009AEA2[];
extern u8 D_8009AEA6[];
extern u8 D_8009AEAA[];
extern u8 D_8009AEAE[];
extern u8 D_8009AEB2[];
extern u8 D_8009AEB6[];
extern u8 D_800A39C4;
void func_8005DAD4(void) {
    s32 i;
    s32 primOffset;
    s32 x;
    u8 index;
    u8 *object;
    u8 *prim;
    u16 value;
    u16 w;
    u16 h;

    x = -0x32;
    i = 0;
    primOffset = 0;
    do {
        index = D_800A35EC;
        prim = D_800B9990 + primOffset;
        D_800A35EC = index + 1;
        object = D_800A3678 + index * 36;
        *(s16 *)(object + 0) = 1;
        *(s16 *)(object + 0x12) = 0;
        *(s16 *)(object + 0x14) = 0;
        *(s32 *)(object + 0x1C) = 0;
        object[4] = 0;
        object[3] = 0;
        object[2] = 0;
        *(s16 *)(object + 0x1A) = 0;
        D_800B12FC[i] = (s16 *)object;
        *(s16 *)(object + 6) = x;
        x = x - 1 - i;
        *(s16 *)(object + 8) = 0x10;
        *(s16 *)(object + 0xC) = 0x10;
        *(s16 *)(object + 0xE) = 2;
        *(s16 *)(object + 0x16) = 0x40;
        *(s16 *)(object + 0x18) = 0x13;
        *(s16 *)(object + 0x10) = 0;
        *(s16 *)(object + 0x1A) = 0;
        value = *(u16 *)(object + 6);
        SetPolyFT4(prim);
        *(s16 *)(object + 0xA) = value;
        SetShadeTex(prim, 0);
        prim[4] = 0x80;
        prim[5] = 0x80;
        prim[6] = 0x80;
        SetSemiTrans(prim, 1);
        w = *(u16 *)(object + 0x16);
        h = *(u16 *)(object + 0x18);
        *(s16 *)(prim + 0xE) = GetClut(D_8009AEDC[0], D_8009AEDE[0]);
        primOffset += 0x28;
        *(s16 *)(prim + 0x16) =
            GetTPage(D_8009AEE4[0], 3, D_8009AED8[0], D_8009AEDA[0]);
        prim[0xC] = D_8009AEE0[0];
        prim[0xD] = D_8009AEE2[0];
        prim[0x14] = D_8009AEA2[62] + w;
        prim[0x15] = D_8009AEAE[52];
        prim[0x1C] = D_8009AEA6[58];
        prim[0x1D] = D_8009AEB2[48] + h;
        prim[0x24] = D_8009AEAA[54] + w;
        prim[0x25] = D_8009AEB6[44] + h;
        i++;
        *(u8 **)(object + 0x20) = prim;
    } while (i < 10);
    D_800A39C4 = D_800A35EC;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8005DAD4);
#endif

extern s16 *D_800B12FC[];
extern u8 *func_80057CCC(s32);
s32 func_8005DCF0(void) {
    u8 done;
    s32 i;
    u8 *object;
    POLY_FT4 *poly;
    s16 sum;

    done = 0;
    i = 9;
    do {
        object = (u8 *)D_800B12FC[i];
        if (*(s16 *)(object + 0xE) != 0) {
            sum = *(u16 *)(object + 6) + *(s16 *)(object + 0xE);
            *(s16 *)(object + 6) = sum;
            if (sum >= 0x141) {
                *(s16 *)(object + 8) = 0xF0;
                if (i == 9) {
                    done = 1;
                }
                if (done != 0) {
                    *(s16 *)(object + 0xE) = 2;
                    *(s16 *)(object + 6) = *(u16 *)(object + 0xA);
                    *(s16 *)(object + 8) = *(u16 *)(object + 0xC);
                }
            }
            if ((s16) * (u16 *)(object + 0xE) < 6) {
                *(u16 *)(object + 0xE) =
                    *(u16 *)(object + 0xE) + (s16) * (u16 *)(object + 0xE) / 2;
            }
        }
        if (done == 0) {
            poly = func_80057CCC(0);
            *poly = *(POLY_FT4 *)*(u8 **)(object + 0x20);
            *(u16 *)((u8 *)poly + 8) = *(u16 *)(object + 6);
            *(u16 *)((u8 *)poly + 0xA) = *(u16 *)(object + 8);
            *(u16 *)((u8 *)poly + 0x10) =
                *(u16 *)(object + 6) + *(u16 *)(object + 0x16);
            *(u16 *)((u8 *)poly + 0x12) = *(u16 *)(object + 8);
            *(u16 *)((u8 *)poly + 0x18) = *(u16 *)(object + 6);
            *(u16 *)((u8 *)poly + 0x1A) =
                *(u16 *)(object + 8) + *(u16 *)(object + 0x18);
            *(u16 *)((u8 *)poly + 0x20) =
                *(u16 *)(object + 6) + *(u16 *)(object + 0x16);
            *(u16 *)((u8 *)poly + 0x22) =
                *(u16 *)(object + 8) + *(u16 *)(object + 0x18);
            AddPrim(D_800A39C8[0] + *(s16 *)(object + 0x1A) * 4, poly);
        }
        i--;
    } while (i != 0);
    return done;
}

extern s16 *D_800B12FC[];
void func_8005DEDC(s16 value) {
    s32 i;
    s16 **entry;
    i = 0;
    entry = D_800B12FC;
    do {
        i++;
        (*entry)[0x1A / 2] = value;
        entry++;
    } while (i < 10);
}

extern u8 *D_800A392C;
void func_8005DF08(s32 a, s32 b, s32 c, u8 flag) {
    u8 *object;
    object = D_800A392C;
    while (object) {
        *(s16 *)(object + 6) = a;
        *(s16 *)(object + 0xE) = c;
        *(s16 *)(object + 0xA) = b;
        object[5] = c;
        if (flag)
            *(s16 *)(object + 0xA) = 125;
        object = *(u8 **)(object + 0x1C);
    }
}

/* Menu entries and panels. */

typedef struct Df50Fields {
    u8 pad0[5];
    s8 unk5;
    u8 pad6[4];
    s16 unkA;
    u8 padC[2];
    s16 unkE;
} Df50Fields;
extern Df50Fields *D_800A3634;
extern s32 **D_800A3740;
extern Df50Fields *D_800A3788;
void func_8005DF50(s32 arg0, s32 arg1, s32 arg2) {
    Df50Fields *p0;
    Df50Fields *p1;
    Df50Fields *p2;
    Df50Fields *p3;
    Df50Fields *p4;
    Df50Fields *p5;
    p0 = D_800A3634;
    p0->unk5 = arg2;
    p0->unkE = arg2;
    p1 = D_800A3634;
    p1->unkA = arg1 + 0x3C;
    p2 = (Df50Fields *)D_800A3740;
    p2->unk5 = arg2;
    p2->unkE = arg2;
    p3 = (Df50Fields *)D_800A3740;
    p3->unkA = arg1 + 5;
    p4 = D_800A3788;
    p4->unk5 = arg2;
    p4->unkE = arg2;
    p5 = D_800A3788;
    p5->unkA = arg1 + 0x71;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005DFA0);

extern void *D_800A3954;
void func_8005E3DC(void) {
    if (D_800A3954 != NULL) {
        HeapFree(D_800A3954);
    }
    D_800A3954 = NULL;
}

extern void *D_800A399C[];
extern void HeapFree(void *ptr);
void func_8005E408(void) {
    if (D_800A399C[0] != 0) {
        HeapFree(D_800A399C[0]);
    }
    *(void **)&D_800A3988[0x14] = 0;
}

extern char D_800BA058[], D_800A333C[];
extern u8 *func_80012EA8(s32, u8 *);
extern char *strcat(char *, char *);
void func_8005E43C(s32 value) {
    func_80012EA8(value, D_800BA058);
    strcat(D_800BA058, D_800A333C);
}

extern void *D_800A399C[];
void func_8005E47C(void) {
    D_800A399C[0] = HeapAlloc(0x2580);
}

#ifdef NON_MATCHING
/* Wall: body, registers, stores and lhu/sb shapes all match; retail's
 * frame is 0x30, ours 0x28. Tried: a live s16 local (kept in reg), and
 * volatile s32 x[2] (breaks cc1 wholesale). The inits of i/primOffset
 * must stay INSIDE the if, or i=0 leaves the blez delay slot. */
extern s32 D_800A393C;
extern s32 D_800A38DC;
void func_8005E4A4(u8 *table) {
    s32 count;
    s32 i;
    s32 primOffset;
    u8 *entry;
    u8 *prim;
    s16 color;

    count = *(s32 *)table;
    D_800A393C = (s32)(table + 4);
    D_800A38DC = count;
    if (count > 0) {
        i = 0;
        primOffset = 0;
        do {
            entry = (u8 *)(D_800A393C + i * 32);
            prim = D_800A399C[0] + primOffset;
            SetPolyF4(prim);
            color = *(s16 *)(entry + 6);
            prim[4] = color;
            color = *(s16 *)(entry + 0xE);
            prim[5] = color;
            color = *(s16 *)(entry + 0x16);
            prim[6] = color;
            i++;
            primOffset += 0x18;
        } while (i < D_800A38DC);
    }
}
#endif
extern s32 D_800A393C;
extern s32 D_800A38DC;
void func_8005E4A4(u8 *table) {
    volatile u32 pad[2];
    s32 count;
    s32 i;
    s32 primOffset;
    u8 *entry;
    u8 *prim;
    s16 color;

    count = *(s32 *)table;
    D_800A393C = (s32)(table + 4);
    D_800A38DC = count;
    if (count > 0) {
        i = 0;
        primOffset = 0;
        do {
            entry = (u8 *)(D_800A393C + i * 32);
            prim = D_800A399C[0] + primOffset;
            SetPolyF4(prim);
            color = *(s16 *)(entry + 6);
            prim[4] = color;
            color = *(s16 *)(entry + 0xE);
            prim[5] = color;
            color = *(s16 *)(entry + 0x16);
            prim[6] = color;
            i++;
            primOffset += 0x18;
        } while (i < D_800A38DC);
    }
}

extern u8 *D_800AE178[];
extern void *func_80058094(s32, void **, s32);
void func_8005E550(s32 arg0) {
    void *table;
    void *result;
    u8 i;

    result = func_80058094(arg0, &table, 0);
    D_800A3954 = result;
    for (i = 0; i < 0x11; i++) {
        D_800AE178[i] = result + ((s32 *)table)[i];
    }
}

extern s32 D_800A393C;
void func_8005E5BC(s32 unused, s32 x, s16 y, s32 flag) {
    u8 *entry;
    u8 count;
    s32 height;
    s32 fieldValue;
    count = D_800A35EC;
    D_800A35EC = count + 1;
    entry = D_800A3678 + count * 36;
    *(s16 *)(entry + 0) = 3;
    height = 0x3C;
    *(s16 *)(entry + 0x12) = 0;
    *(s16 *)(entry + 0x14) = 0;
    *(s32 *)(entry + 0x1C) = 0;
    entry[4] = 0;
    entry[3] = 0;
    entry[2] = 0;
    *(s16 *)(entry + 0x1A) = 0;
    D_800A3634 = (Df50Fields *)entry;
    *(s16 *)(entry + 6) = x + 0x3C;
    *(s16 *)(entry + 0xA) = height;
    if (flag & 0xFF) {
        *(s16 *)(entry + 0xA) = 0xB9;
    }
    fieldValue = D_800A393C;
    *(s16 *)(entry + 8) = 0xB9;
    *(s16 *)(entry + 0xC) = 0xB9;
    *(s16 *)(entry + 0xE) = y;
    *(s16 *)(entry + 0x10) = 0;
    *(s32 *)(entry + 0x20) = fieldValue;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005E644);

INCLUDE_ASM("asm/nonmatchings/game", func_8005E7F8);

INCLUDE_ASM("asm/nonmatchings/game", func_8005E8EC);

#ifdef NON_MATCHING
extern u16 D_8009AF84[];
extern s32 D_800A37D0;
extern s32 D_800A3814;
extern char D_800BA058[];
extern char D_800A333C[];
extern u8 *func_80012EA8(s32, u8 *);
extern char *strcat(char *, char *);
void func_8005EC5C(s32 arg0) {
    s32 value;
    s32 scaled;
    value = D_8009AF84[arg0 & 0xFF];
    scaled = (value * D_800A37D0) / 100;
    D_800A3814 = scaled;
    if (scaled < 3)
        D_800A3814 = 3;
    func_80012EA8(D_800A3814, D_800BA058);
    strcat(D_800BA058, D_800A333C);
}
#else
#ifdef NON_MATCHING
/*
 * Two walls: (a) the new `extern s32 D_800A3814[]` (untracked bss label)
 * shifts the D_8009AF84/D_800A37D0 data labels 4 bytes low via the
 * maspsx_extern interaction (see matching.md); (b) gcc CSEs all three
 * &D_800A3814[0] accesses into one cached lui/addiu base and saves s0,
 * while retail re-materializes `lui at` per store. Distinct-expression
 * forms (`(D_800A3814 + 0)`, `&D_800A3814[0]`) do not split it.
 */
/* w4d: avoid the D_800A3814 extern entirely with the defsym'd neighbor
 * ((s32 *)D_800A37C4Absolute)[20] (= 0x800A3814, [3] = 0x800A37D0); and
 * the missing third argument of func_80012EA8 is the RAW mfhi of the
 * magic multiply - pass ((value * D_800A37D0[0]) * 0x51EB851F) >> 32 so
 * cse shares the one mult (retail: one chain, a2 = mfhi). */
extern s16 D_8009AF84[];
void func_8005EC5C(u8 index) {
    s32 value;
    s32 scaled;

    value = D_8009AF84[index] * D_800A37D0[0];
    scaled = value / 100;
    ((s32 *)D_800A37C4Absolute)[20] = scaled;
    if (scaled < 3) {
        ((s32 *)D_800A37C4Absolute)[20] = 3;
    }
    func_80012EA8(((s32 *)D_800A37C4Absolute)[20], D_800BA058,
                  (value * 0x51EB851F) >> 32);
    strcat(D_800BA058, D_800A333C);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8005EC5C);
#endif

#if 0
/* w7g draft: everything matches except gcc CSEs the two D_800BA058
 * materializations across the func_80012EA8/strcat calls into
 * callee-saved s0 (function 8 bytes short; asm("") does not block
 * cross-call cse). D_800A3814 is reached as D_800A37E8[11] (bss
 * neighbor of an already-array symbol; declaring D_800A3814 drifts
 * labels), and D_8009AF84 needs u8[] + s16 cast (retail strides 2). */
extern u8 D_8009AF84[];
void func_8005EC5C(u8 arg0) {
    s32 value;

    value = *(s16 *)&D_8009AF84[(arg0 & 0xFF) * 2] * D_800A37D0[0] / 100;
    D_800A37E8[11] = value;
    if (value < 3) {
        *(D_800A37E8 + 11) = 3;
    }
    func_80012EA8(D_800A37E8[11], D_800BA058);
    strcat(D_800BA058, D_800A333C);
}
#endif
#endif

extern s32 D_8009A31C[];
extern s32 **D_800A3740;
void func_8005ED04(s32 index) {
    D_800A3740[8][2] = D_8009A31C[index & 0xFF];
}

extern u8 D_800A3860[][4];
s32 func_8005ED28(u8 x, u8 y) {
    u32 scale;
    u32 level;

    level = D_800A3860[x][y];
    scale = ((level << 1) + level) << 2;
    scale += level;
    scale >>= 3;
    if (scale == 0) {
        scale = 1;
    }
    return scale;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005ED74);

INCLUDE_ASM("asm/nonmatchings/game", func_8005FE90);

extern u8 *D_800B9980[];
u8 *func_8005FFA8(u8 x, u8 y) {
    u32 scale;
    u32 level;
    u32 result;
    u8 *node;
    u8 *entry;

    level = D_800A3860[x][y];
    scale = ((level << 1) + level) << 2;
    scale += level;
    result = scale >> 3;
    if (result == 0) {
        result = 1;
    }
    node = D_800B9980[y];
    entry = *(u8 **)(node + 0x1C);
    *(s16 *)(entry + 0x16) = result;
    return entry;
}

extern u8 D_800A3860[][4];
extern u8 D_800A3861U8[][4] asm("D_800A3861.NON_MATCHING");
extern u8 D_800A3862U8[][4] asm("D_800A3862.NON_MATCHING");
extern u8 D_800A3863U8[][4] asm("D_800A3863.NON_MATCHING");
extern u8 *D_800B60B8[];

void func_80060008(u8 arg0) {
    s32 vals[4];
    s32 diff;
    s32 aCol;
    s32 cCol;
    s32 q;
    u8 *node;
    u8 *entry;

    vals[0] = (0x3F - D_800A3861U8[arg0][0]) * 700 / 1000 +
              D_800A3863U8[arg0][0] * 300 / 1000;
    aCol = D_800A3861U8[arg0][0];
    vals[3] = aCol / 5 + (0x3F - D_800A3860[arg0][0]) * 800 / 1000;
    vals[2] =
        D_800A3860[arg0][0] * 600 / 1000 + D_800A3862U8[arg0][0] * 400 / 1000;
    diff = D_800A3862U8[arg0][0] - D_800A3861U8[arg0][0];
    if (diff < 0) {
        asm("");
        diff = 0;
    }
    vals[2] = vals[2] - diff;
    if (vals[2] < 0) {
        vals[2] = 0;
    }
    cCol = D_800A3860[arg0][0];
    vals[1] = (0x3F - D_800A3863U8[arg0][0]) * 600 / 1000 + cCol / 4 +
              (0x3F - D_800A3861U8[arg0][0]) * 150 / 1000;
    diff = 0;
    do {
        q = vals[diff] * 48 / 61;
        if (q > 0x30) {
            q = 0x30;
        }
        if (q < 1) {
            q = 1;
        }
        node = D_800B60B8[diff];
        entry = *(u8 **)(&node[0x1C]);
        *(s16 *)(&entry[0x16]) = q;
        diff++;
    } while (diff < 4);
}

INCLUDE_ASM("asm/nonmatchings/game", func_800602E8);

INCLUDE_ASM("asm/nonmatchings/game", func_800606D4);

typedef struct PanelChild {
    u8 pad0[8];
    s32 value;
} PanelChild;
typedef struct PanelState {
    u8 pad0[0x12];
    s16 y;
    u8 pad14[2];
    s16 height;
    u8 pad18[8];
    PanelChild *child;
} PanelState;
extern s32 D_8009A2B0[];
extern PanelState *D_800A3A68;
extern void func_8005A7B8(u8, u8);
extern s16 func_8005A8E0(s32);
void func_80060E94(s32 arg0) {
    s32 value;
    s32 height;
    s32 centered;
    func_8005A7B8(2, 2);
    value = D_8009A2B0[arg0 & 0xFF];
    D_800A3A68->child->value = value;
    height = func_8005A8E0(value);
    centered = (0x78 - height) / 2;
    D_800A3A68->y = centered;
    D_800A3A68->height = (s16)height;
}

extern u8 *D_800A38A8;
void func_80060F10(s32 a, s32 b, s16 c) {
    u8 *node;
    node = D_800A38A8;
    while (node != 0) {
        *(s16 *)(node + 14) = c;
        *(s16 *)(node + 6) = *(u16 *)(node + 18) + a;
        *(s16 *)(node + 10) = *(u16 *)(node + 18) + b;
        node = *(u8 **)(node + 0x1C);
    }
}

extern u8 D_800A2F9DAbsolute[];
void func_80060F54(s32 arg0, s32 volume) {
    u8 *node;
    u8 x;

    node = *(u8 **)(D_800A38A8 + 0x1C);
    volume &= 0xFF;
    x = arg0;
    *(u16 *)(node + 0x16) = x;
    if (volume != 0) {
        x = arg0;
        D_800A2F9DAbsolute[-9] = (x * 127) / 100;
        func_8003FDE8(1, 0x7F, 0x7F);
    } else {
        CdSetMixVolume(x);
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80060FD8);

void func_80062874(s32 arg0, s32 arg1) {
    u8 *node;
    s16 flag;
    s32 index;

    index = arg0 & 0xFF;
    flag = index != 0;
    if ((arg1 & 0xFF) != 0) {
        node = ((void **)D_800A3A2CAbsolute)[index - 4];
    } else {
        node = ((void **)D_800A37C4Absolute)[index + 5];
    }
    if (node != 0) {
        do {
            if (*(u16 *)(node + 6) < 0x141U) {
                *(u16 *)(node + 0xE) = 2 - flag * 4;
                if (flag != 0) {
                    *(s16 *)(node + 0xA) = -0xA0;
                } else {
                    *(u16 *)(node + 0xA) = 0x1E0;
                }
            }
            node = *(u8 **)(node + 0x1C);
        } while (node != 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80062910);

s32 ListHasClearFlags(u8 *node) {
    while (node != 0) {
        if (*(s16 *)(node + 0xE) != 0)
            return 0;
        node = *(u8 **)(node + 0x1C);
    }
    return 1;
}

void ListSetFieldsAndEnable(u8 *node, s16 a, s16 b, s16 c) {
    while (node != 0) {
        *(s16 *)(node + 6) = a;
        *(s16 *)(node + 10) = b;
        *(s16 *)(node + 14) = c;
        node[5] = 1;
        node = *(u8 **)(node + 0x1C);
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80062D38);

extern u8 *D_800A3A84[];
extern s32 D_8009ABFC[];
void func_80062F04(u8 index, u8 kind, u8 sub) {
    u32 code;
    u8 *object;
    s32 *target;

    if (kind == 2) {
        code = 2;
        if (sub < 4) {
            asm("");
            code = 3;
        }
    } else {
        code = 2;
        if (sub < 2) {
            code = 4;
        }
    }
    object = D_800A3A84[index];
    target = *(s32 **)(object + 0x20);
    *(target + 2) = D_8009ABFC[code];
}

extern u8 *D_800A37FC[];
extern s32 *D_800A37D8[];
extern u8 D_800AEE3D[];
extern u8 D_800AEE3E[];
extern u8 D_800AEE40[];
extern u8 D_800AEE41[];
extern u8 D_800AEE42[];
extern u8 D_800AEE43[];

void func_80062F6C(s32 arg0, s32 arg1) {
    register s32 i asm("t0");
    register u8 *obj asm("t1");
    register s32 offset asm("t2");
    s32 **entry;
    register s32 b42 asm("v1");
    register s32 b43 asm("a0");
    register s32 val asm("a2");
    register s32 lim asm("v0");
    register s32 base2 asm("v0");
    register s32 d asm("v0");
    register s32 a asm("v0");
    register s32 denom asm("v1");
    register s32 b asm("v1");
    register s32 mode asm("v1");
    register s32 delta asm("v1");
    s32 idx;
    s32 base9;
    s32 y;
    s32 j;
    s32 prod;
    s16 sum;

    idx = arg0 & 0xFF;
    obj = (u8 *)D_800A37FC[idx];
    i = 0;
    base9 = idx * 9;
    base2 = (s32)D_800A37D8;
    entry = (s32 **)(idx * 4 + base2);
    offset = -3;
    for (; i < 3; i++) {
        switch (i) {
        case 0:
            b42 = D_800AEE42[base9];
            b43 = D_800AEE43[base9];
            lim = 0x80;
            val = lim - b42;
            val = (val * 103) >> 8;
            y = b43 - 0x80;
            if (val >= 0x68) {
                val = 0x67;
            }
            y = (y * 103) >> 8;
            if (y >= 0x68) {
                y = 0x67;
            }
            sum = val + y;
            *(s16 *)(obj + 0x16) = sum;
            if (sum >= 0x68) {
                *(s16 *)(obj + 0x16) = 0x67;
            }
            *(s16 *)(obj + 0x12) = 0xAC - val;
            break;
        case 1:
        case 2:
            mode = arg1 & 0xFF;
            if (mode == 2) {
                j = offset + base9;
                val = D_800AEE3D[j];
                prod = val * 49;
                asm("sra %0, %1, 0x8" : "=r"(val) : "r"(prod));
                if (val >= 0x32) {
                    val = 0x31;
                }
            } else {
                if (i == 1) {
                    denom = D_800AEE3E[base9];
                    d = D_800AEE3D[base9];
                    val = denom - d;
                } else {
                    a = D_800AEE40[base9];
                    b = D_800AEE41[base9];
                    val = a - b;
                    denom = 0xFF - b;
                }
                prod = val * 48;
                val = prod / denom;
                if (val >= 0x31) {
                    val = 0x30;
                }
            }
            *(s16 *)(obj + 0x18) = val;
            delta = val - 0x38;
            *(s16 *)(obj + 0x14) = *(u16 *)((u8 *)entry[0] + 0x14) - delta;
            break;
        }
        obj = *(u8 **)(obj + 0x1C);
        offset = offset + 3;
    }
}

extern s16 *D_800AE290[];
void func_80063180(s32 enabled) {
    if (enabled & 0xFF) {
        D_800AE290[0][0x1A / 2] = 0;
    } else {
        D_800AE290[0][0x1A / 2] = -1;
    }
}

void func_800631B4(void) {
    D_800A3984[0] = (s32)HeapAlloc(0xF00);
}

INCLUDE_ASM("asm/nonmatchings/game", func_800631DC);

void func_80063538(s32 arg0, s32 arg1) {
    extern u8 *func_8005B474(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                             s32);
    extern u8 *D_800A3628[];
    s32 cmd;
    u8 **table;
    u8 *node;
    u8 *prev;
    s32 i;
    s32 j;
    s32 offs;

    cmd = 0x6A;
    j = 0;
    table = D_800A3628;
    for (; j < 2; j++) {
        for (i = 0; i < 2; i++) {
            offs = 4;
            if (i != 0) {
                asm("");
                offs = -4;
            }
            node =
                func_8005B474(arg1, cmd, offs, 8, 0, 0x28, 0x64, 0xC8, 0, 1, 0);
            *(s16 *)(node + 0x1A) = 0;
            if (i != 0) {
                *(s16 *)(node + 0x12) = 0x2E;
            } else {
                *(s16 *)(node + 0x12) = -0x2E;
            }
            *(s16 *)(node + 0x14) = 0;
            *(s16 *)(node + 0x0E) = 0;
            if (i == 0) {
                *table = node;
            } else {
                *(u8 **)(prev + 0x1C) = node;
            }
            prev = node;
        }
        cmd += 0x33;
        table += 1;
    }
}

extern u8 *D_800A3628[];
void func_80063638(u8 mode) {
    s16 left;
    s16 width;
    u8 *node;
    s32 i;

    if (mode != 0) {
        left = 0x6A;
        width = 0x2E;
    } else {
        left = 0xBA;
        width = 0x37;
    }
    node = D_800A3628[0];
    for (i = 0; i < 2; i++) {
        *(s16 *)(node + 8) = left;
        *(s16 *)(node + 0xC) = left;
        *(s16 *)(node + 0x12) = width;
        if (i == 0) {
            *(s16 *)(node + 0x12) = -width;
        }
        node = *(u8 **)(node + 0x1C);
    }
}

extern u8 *D_800A35E4[];
void func_80063694(u8 index, s16 dx, s16 dy, s16 code) {
    u8 *node;

    node = D_800A35E4[index];
    if (node != 0) {
        do {
            *(s16 *)(node + 6) = *(s16 *)(node + 0x12) + dx;
            *(s16 *)(node + 0xE) = code;
            node[5] = code;
            *(s16 *)(node + 0xA) = *(s16 *)(node + 0x12) + dy;
            node = *(u8 **)(node + 0x1C);
        } while (node != 0);
    }
}

extern char *D_8009AC1C[];
extern u8 *D_800A3868[];
void func_800636EC(u8 index, u8 kind) {
    u8 *node;
    u8 *object;
    s32 value;

    node = D_800A3868[index];
    object = *(u8 **)(node + 0x20);
    *(u8 **)(object + 8) = D_8009AC1C[kind];
    func_8005A7B8(object[1], object[2]);
    value = func_8005B0E4(0x64, *(s32 *)(object + 8));
    *(s16 *)(node + 6) = value + 0xA;
    *(s16 *)(node + 0x12) = value - 0x32;
}

extern u8 *D_800A3868[];
void func_80063770(u8 index) {
    u8 *node;
    s16 value;

    node = D_800A3868[index];
    if (node != 0) {
        do {
            value = *(s16 *)(node + 0x1A);
            if (value > 0) {
                *(s16 *)(node + 0x1A) = -value;
            } else if (value == 0) {
                *(s16 *)(node + 0x1A) = -0x8000;
            }
            node = *(u8 **)(node + 0x1C);
        } while (node != 0);
    }
}

extern u8 *D_800A3868[];
void func_800637D8(u8 index) {
    u8 *node;
    s16 value;

    node = D_800A3868[index];
    if (node != 0) {
        do {
            value = *(s16 *)(node + 0x1A);
            if (value == -0x8000) {
                *(s16 *)(node + 0x1A) = 0;
            } else if (value < 0) {
                *(s16 *)(node + 0x1A) = -value;
            }
            node = *(u8 **)(node + 0x1C);
        } while (node != 0);
    }
}

#ifdef NON_MATCHING
/*
 * Everything matches except one `addiu a2,a2,0`: retail materializes the
 * scratchpad base with a bare `lui` (numeric 0x1F800000 constant, which
 * the repo forbids). Any symbolic gScratchpad reference expands la into
 * lui + addiu 0. Same wall as func_800246C0 (notes-agent2.md).
 */
extern u32 gScratchpad[];
void func_8006383C(void) {
    u32 i;
    u32 greyLevel;

    for (i = 0; i < 0x100; i++) {
        greyLevel = i >> 2;
        gScratchpad[i] = (greyLevel << 0x10) | (greyLevel << 8) | greyLevel;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006383C);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80063874);

void func_80063A20(void) {
}

void func_80063A28(void) {
    RECT rect;
    s32 i;
    s16 srcX;
    s16 tile;

    i = 0;
    tile = 0x40;
    srcX = 0x300;
    while (i < 2) {
        rect.x = (i % 4) * 0x40 + 0x300;
        rect.y = tile;
        rect.h = tile;
        rect.w = tile;
        MoveImage(&rect, i * 0x40, 0x100);
        rect.y = 0x3F;
        rect.h = 1;
        rect.x = srcX;
        rect.w = 0x10;
        MoveImage(&rect, 0, 0x140 + i);
        srcX += 0x10;
        i++;
    }
}

void func_80063AE0(s32 arg0, s32 arg1) {
    RECT rect;

    if (arg1 >= 2) {
        rect.x = (arg1 % 4) * 0x40 + 0x300;
        rect.y = (arg1 / 4) * 0x40 + 0x40;
        rect.h = 0x40;
        rect.w = 0x40;
        MoveImage(&rect, arg0 * 0x40 + 0x300, 0x40);
        rect.x = (arg1 % 16) * 0x10 + 0x300;
        rect.y = 0x3F - arg1 / 16;
        rect.h = 1;
        rect.w = 0x10;
        MoveImage(&rect, arg0 * 0x10 + 0x300, 0x3F);
    } else {
        rect.x = (arg1 % 4) * 0x40;
        rect.y = (arg1 / 4) * 0x40 + 0x100;
        rect.h = 0x40;
        rect.w = 0x40;
        MoveImage(&rect, arg0 * 0x40 + 0x300, 0x40);
        rect.y = arg1 + 0x140;
        rect.h = 1;
        rect.x = 0;
        rect.w = 0x10;
        MoveImage(&rect, arg0 * 0x10 + 0x300, 0x3F);
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80063C34);

INCLUDE_ASM("asm/nonmatchings/game", func_80063E7C);

#ifdef NON_MATCHING
/*
 * Close (whole body + scratchpad loop structurally identical) but 4 bytes
 * long: retail materializes the scratchpad base with a bare `lui`
 * (0x1F800000), while any symbolic gScratchpad reference expands
 * lui + addiu 0. Same wall as func_8006383C and func_800246C0
 * (notes-agent2.md). Second wall: s-reg assignment is offset --
 * retail arg0->s3, arg1->s2, arg2->s1; ours arg0->s2, arg1->s1,
 * arg2->s3 (same copy order, different starting reg).
 */
extern u8 *D_800A35E4[];
extern u32 gScratchpad[];
void func_8003271C(void *arg0, s32 arg1);
void func_8001775C(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80064000(s32 arg0, s32 arg1, s32 arg2) {
    u8 *entry;
    u8 *obj;
    u16 height;
    s32 x;
    u32 i;
    u32 grey;
    u32 *pad;
    s16 t;
    s32 v1;
    s32 v0;
    u16 result;

    entry = D_800A35E4[arg0 & 0xFF];
    height = *(u16 *)(entry + 0xA);
    if (height < 0x140U || *(s16 *)(entry + 6) != (s16)height) {
        obj = *(u8 **)(entry + 0x20);
        x = *(s16 *)(entry + 6);
        if (arg2 & 0xFF) {
            SetGeomOffset(x, 0x2D);
        } else {
            SetGeomOffset(x, *(s16 *)(entry + 8));
        }
        if (arg1 & 0xFF) {
            pad = gScratchpad;
            i = 0;
            do {
                grey = i >> 2;
                pad[0] = (grey << 0x10) | (grey << 8) | grey;
                pad += 1;
                i += 1;
            } while (i < 0x100U);
        } else {
            func_8003271C(0, 0);
        }
        func_8001775C(obj, 0, 0xFA, 0x44C);
        if (!(arg0 & 0xFF) || (arg2 & 0xFF) || D_800A39E4[0] == 0xE) {
            t = *(s16 *)(obj + 0x20E);
            v1 = t + 0xFEC;
            if (v1 < 0) {
                v0 = t + 0x1FEB;
            } else {
                v0 = v1;
            }
            result = v1 - ((v0 >> 0xC) << 0xC);
        } else {
            result = *(u16 *)(D_800A3554[0] + 0x20E);
        }
        *(s16 *)(obj + 0x20E) = result;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80064000);
#endif

void *func_80058094(s32 arg0, void **arg1, s32 arg2);
void func_80013224(void *arg0);

void func_80064174(void) {
    void *data;
    s32 *offsets;
    s32 i;

    data = func_80058094(10, (void **)&offsets, 0);
    for (i = 0; i < 0x18; i++) {
        func_80013224((u8 *)data + offsets[i]);
    }
    DrawSync(0);
    HeapFree(data);
}

extern s32 D_800A3A5C, D_800A3358;
void func_800641EC(void) {
    extern s32 D_800A3378[];
    s32 value;
    value = D_800A3378[0];
    D_800A3A5C = value;
    D_800A3358 = value;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80064208);

INCLUDE_ASM("asm/nonmatchings/game", func_800645A4);

typedef struct UnkNode1C {
    u8 unk0[6];
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 unk12;
    u8 unk14[8];
    struct UnkNode1C *next;
} UnkNode1C;
void ListSetRangeFields(UnkNode1C *node, s32 low, s32 high, s16 value) {
    while (node != NULL) {
        node->unkE = value;
        node->unk6 = node->unk12 + low;
        node->unkA = node->unk12 + high;
        node = node->next;
    }
}

extern u8 *D_800A38FC[];
extern u8 *D_800A3900[];
extern u8 *D_800A39A0[];
extern u8 *D_800A39A4nm[] asm("D_800A39A4.NON_MATCHING");
extern u8 *D_800A39AC[];
extern u8 *D_800A35E4[];
extern u8 *D_800A35E8[];
extern s8 D_800A3A14;
extern void func_8005B688(u8 *first, u8 friction);
extern void func_8005B8B8(u8 *first, s32 value);
extern void func_80064000(s32 mode, s32 a, s32 b);

void func_80064898(void) {
    func_8005B8B8(D_800A38FC[1], 0xFF);
    if (D_800A38FC[0] != 0) {
        func_8005B688(D_800A38FC[0], 1);
        func_8005B8B8(D_800A3900[-1], 0xFF);
    }
    if (D_800A39A0[0] != 0) {
        func_8005B688(D_800A39A0[0], 1);
        func_8005B8B8(D_800A39A4nm[-1], 0xFF);
    }
    func_8005B688(D_800A35E4[0], 1);
    func_8005B8B8(D_800A35E8[-1], 0xFF);
    func_80064000(0, 0, 0);
    if (D_800A3A14 != 0 || D_800A39AC[-3] != 0) {
        func_8005B688(D_800A35E8[0], 1);
        func_8005B8B8(D_800A35E8[0], 0xFF);
        func_80064000(1, 0, 0);
    }
}

void func_8006499C(void) {
    RECT rect;

    rect.x = 0x140;
    rect.y = 0x140;
    rect.h = 0x48;
    rect.w = 0x140;
    MoveImage(&rect, 0x140, 0);
    DrawSync(0);
    rect.x = 0x280;
    rect.y = 0x140;
    rect.h = 0x48;
    rect.w = 0x40;
    MoveImage(&rect, 0x140, 0x48);
    DrawSync(0);
    rect.x = 0x140;
    rect.y = 0x188;
    rect.h = 0x48;
    rect.w = 0x100;
    MoveImage(&rect, 0x180, 0x48);
    rect.x = 0x240;
    rect.y = 0x188;
    rect.h = 0x48;
    rect.w = 0x80;
    MoveImage(&rect, 0x140, 0x90);
    DrawSync(0);
    rect.x = 0x100;
    rect.y = 0x1D0;
    rect.h = 0x18;
    rect.w = 0x100;
    MoveImage(&rect, 0x140, 0xD8);
    DrawSync(0);
}

extern u8 D_8009B00C[];
extern u8 D_8009B028[];
extern u8 D_8009B02A[];
extern u16 D_8009B048[][7];
extern u8 D_8009B04A[];
extern u16 D_8009B050[][7];
extern u16 D_8009B054[][7];

void func_80064AB4(u8 *prim, u8 idx) {
    SetShadeTex(prim, 0);
    ((u8 *)prim)[4] = 0x80;
    ((u8 *)prim)[5] = 0x80;
    ((u8 *)prim)[6] = 0x80;
    SetSemiTrans(prim, 0);
    *(s16 *)(prim + 0xE) = GetClut(0x140, 0xEF - idx);
    *(s16 *)(prim + 0x16) =
        GetTPage(D_8009B054[idx][0], 0, D_8009B048[idx][0], D_8009B048[idx][1]);
    ((u8 *)prim)[0xC] = D_8009B050[idx][0];
    ((u8 *)prim)[0xD] = D_8009B048[idx][5];
    ((u8 *)prim)[0x14] = D_8009B04A[idx * 14 + 6] + 0x3F;
    ((u8 *)prim)[0x15] = D_8009B054[idx][-1];
    ((u8 *)prim)[0x1C] = D_8009B048[idx][4];
    ((u8 *)prim)[0x1D] = D_8009B028[idx * 14 + 0x2A] + 0x47;
    ((u8 *)prim)[0x24] = D_8009B00C[idx * 14 + 0x44] + 0x3F;
    ((u8 *)prim)[0x25] = D_8009B02A[idx * 14 + 0x28] + 0x47;
}

#ifdef NON_MATCHING
/*
 * w7h: cc1 2.7.2 positional ICE -- ANY statement body in this function
 * segfaults cc1 (exit 139) at this TU position (crash lands after
 * func_80064AB4; empty body compiles). Same class as func_8001E17C
 * (kb/psx/matching.md w4a). Externs alone are safe; body content is not.
 */
extern u8 *D_8009A3F0[];
extern u8 *D_8009A400[];
extern u8 *D_8009A418[];
extern u8 D_800A3698;
extern u8 D_800A3A4C;
extern u8 *D_800A39D8;
extern u8 *D_800A369C;
void func_8005A6EC(s32 arg0, s32 arg1, void *arg2);
void func_80064C14(void) {
    extern s32 D_800A2EB0Absolute[];

    D_800A38C4 = (u32 *)gOrderingTables;
    D_800A39C8[0] = gOrderingTables;
    D_800A39D8 = gOrderingTables + 0x20;
    D_800A369C = gOrderingTables + 0x13A8;
    if (D_800A2EB0Absolute[0] == 0) {
        D_800A3698 = strlen(D_8009A3F0[0]);
    } else {
        D_800A3698 = strlen(D_8009A418[0]);
    }
    D_800A3A4C = strlen(D_8009A400[0]);
    D_800A3698 += D_800A3A4C;
    D_800A367C = (s32)(D_800A369C + D_800A3698 * 0x28);
    func_8005A6EC(2, 4, D_800A39D8);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80064C14);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80064CD8);

#ifdef NON_MATCHING
/*
 * w9h draft: scene draw dispatch. func_80065058's first arg re-reads
 * D_800A3778 after the store (volatile-cast read per the w2b recipe).
 * D_800A3778/D_800A35DC are new untracked externs - recheck the map.
 */
void func_80064E6C(void) {
    extern s32 D_800A2EB0[];
    extern u8 D_800A3778;
    extern u8 D_800A35DC;
    extern void func_80064CD8(s32);
    extern void func_80065058(s32, s32);
    extern void func_80065F80(void);
    extern void func_80066080(s32);
    u8 **base;

    ClearOTagR((u32 *)gOrderingTableBank, 4);
    func_80064CD8(1);
    func_8006499C();
    D_800A367C = (s32)D_800A369C;
    func_8005A7B8(2, 4);
    func_8005A818(0x80, 0x80, 0xC0);
    base = D_8009A400;
    func_8005B0E4(0x140, (s32)*base);
    func_8005A9F4((s32)*base, (s16)func_8005B0E4(0x140, (s32)*base), 0xC8, 0, 0,
                  0, 0, 0);
    if (D_800A2EB0[0] != 0) {
        func_8005B0E4(0x140, (s32)D_8009A418[0]);
        func_8005A9F4((s32)D_8009A418[0],
                      (s16)func_8005B0E4(0x140, (s32)D_8009A418[0]), 0xC8, 0, 0,
                      0, 0, 0);
    } else {
        func_8005B0E4(0x140, (s32)D_8009A3F0[0]);
        func_8005A9F4((s32)D_8009A3F0[0],
                      (s16)func_8005B0E4(0x140, (s32)D_8009A3F0[0]), 0xC8, 0, 0,
                      0, 0, 0);
    }
    ClearOTagR((u32 *)gOrderingTableBank, 4);
    D_800A367C = (s32)(D_800A369C + D_800A3698 * 0x28);
    if (D_800A3644[0] != 0 && D_800A3073[0] == 0) {
        func_80065F80();
        func_80066080(1);
    } else {
        func_80065838(1);
        D_800A3778 = 0;
        func_80065058(*(volatile u8 *)&D_800A3778, 1);
        if (D_800A3644[0] != 0 && D_800A3073[0] != 0) {
            D_800A35DC = 3;
        } else {
            D_800A35DC = 0xB;
        }
    }
    D_800A3884 = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80064E6C);
#endif

extern s32 D_800A367C;
s32 func_80065028(void) {
    s32 current;
    current = D_800A367C;
    D_800A367C = current + 0x28;
    return current;
}

s32 func_80065040(void) {
    s32 old;
    old = D_800A367C;
    D_800A367C = old + 0x28;
    return old;
}

#ifdef NON_MATCHING
/* Wall (a6 agent, 2026-10-04): frame and allocation do not converge.
 * Retail frame map (all sp offsets verified): args 0x10-0x1C, entry buffer
 * for func_80018588 at 0x20 (0x40 bytes), slots[2] 0x60, u8 id param home
 * 0x68, yOffset 0x70, (u16)(yOffset+0x17) temp 0x78, saves s0..s7/fp/ra
 * 0x80-0xA4. s-reg map: s0 prim, s1 i, s2 x0 then 0xA2 then x, s3 blue then
 * color, s4 id*2 then height, s5 yBase then 0x5A then &D_8009A3EC[13], s6
 * green then 0xE5 then &D_800AEB34, s7 red then 0xA5, fp x1off then 0x57.
 * Walls found: (1) our gcc caches the D_800A36E0/44/E1 loop-1 load bases
 * into t-regs (lui+addiu hoisted before the loop); retail re-materializes
 * `lui/lbu %hi/%lo` per use. volatile arrays, *(volatile u8*)& spelling and
 * asm("":::"memory") all still cache the base address. (2) volatile s32
 * yOffset reproduces the 0x70 home and reloads but shifts the id home to
 * 0x70 (slot order), and leftX never gets the sw 0x78 / lhu pair. (3) the
 * s16 x local must stay s16-width for the sll/sra pairs at func_8005A9F4
 * calls; s32 drops them. Best state reached: 327 diff rows, function 8
 * bytes short (spills one local fewer than retail).
 */
extern u8 D_800A3950[];
extern u8 D_800A305B[];
extern u8 *D_8009A360[];
extern u8 *D_8009A3A4[];
extern u8 *D_8009A3E8[];
extern u8 *D_8009A41C[];
extern u8 *D_8009A3EC[];
extern u8 *D_8009ACE0[];
extern s32 D_800AEB34[];
extern u8 *D_8009A42C[];
extern u16 D_800A3A44;
extern s16 D_800A3940;
extern u8 D_800A3760;
extern u8 *D_800A3568;
extern u8 *D_800A3970;
extern u32 *D_800A38C4;
extern void func_8005A9F4(s32, s16, s16, u8, u8, s32, u8, u8);
void func_80065058(u8 id, s32 shift) {
    u8 entry[0x40];
    u8 slots[2];
    u8 *cursor;
    u8 *match;
    u8 *prim;
    volatile s32 yOffset;
    s16 leftX;
    s32 i;
    s32 x0;
    s32 x1off;
    s32 height;
    s32 red;
    s32 green;
    s32 blue;
    s32 yBase;
    s32 x;
    u8 color;
    s32 r2;
    s32 g2;
    s32 b2;

    yOffset = -((shift & 0xFF) != 0) & -0x140;
    cursor = slots;
    match = slots;
    for (i = 0; i < 2; i++) {
        *cursor = 0xFF;
        if (D_800BE70C[id * 2 + i] == D_800A36E0[0]) {
            *match = i;
            match++;
        }
        if (D_800A3644[0] != 0 && D_800BE70C[id * 2 + i] == D_800A36E1[0]) {
            *match = i;
            match++;
        }
        cursor++;
    }
    x1off = 0x11C;
    x0 = yOffset + 0x12;
    for (i = 0; i < 3; i++) {
        prim = (u8 *)D_800A367C;
        D_800A367C = (s32)prim + 0x28;
        SetPolyF4((POLY_F4 *)prim);
        SetSemiTrans(prim, 0);
        switch (i) {
        case 0:
            height = 0x1C;
            red = 0;
            green = 0;
            blue = 0x80;
            yBase = 0x3E;
            prim[4] = 0;
            prim[5] = 0;
            prim[6] = blue;
            break;
        case 1:
            height = 0x48;
            red = 0;
            green = 0;
            blue = 0x4C;
            yBase = 0x5A;
            prim[4] = 0;
            prim[5] = 0;
            prim[6] = blue;
            break;
        case 2:
            height = 0x12;
            red = 0;
            green = 0;
            blue = 0xC0;
            yBase = 0xA2;
            prim[4] = 0;
            prim[5] = 0;
            prim[6] = blue;
            break;
        case 3:
            if (slots[0] != 0xFF) {
                height = 0x12;
                red = 0x78;
                green = 0x78;
                blue = 0xEC;
                x1off = 0x8E;
                if (slots[0] == 1) {
                    x0 += 0x8E;
                }
            }
            break;
        case 4:
            if (slots[1] != 0xFF) {
                height = 0x12;
                red = 0x78;
                green = 0x78;
                blue = 0xEC;
                x1off = 0x8E;
                if (slots[0] == 0) {
                    x0 = yOffset + 0x12;
                } else {
                    x0 = yOffset + 0xA0;
                }
            }
            break;
        }
        *(s16 *)(prim + 0x12) = yBase + height;
        *(s16 *)(prim + 0x16) = yBase + height;
        prim[4] = red;
        prim[5] = green;
        prim[6] = blue;
        *(s16 *)(prim + 8) = x0;
        *(s16 *)(prim + 0xA) = yBase;
        *(s16 *)(prim + 0xC) = x0 + x1off;
        *(s16 *)(prim + 0xE) = yBase;
        *(s16 *)(prim + 0x10) = x0;
        *(s16 *)(prim + 0x14) = x0 + x1off;
        if (i < 3) {
            AddPrim((u8 *)D_800A38C4 + 0xC, prim);
        } else {
            AddPrim((u8 *)D_800A38C4 + 8, prim);
        }
    }
    leftX = yOffset + 0x17;
    for (i = 0; i < 2; i++) {
        prim = (u8 *)D_800A367C;
        D_800A367C = (s32)prim + 0x28;
        SetPolyFT4((POLY_FT4 *)prim);
        func_80064AB4(prim, D_800BE70C[id * 2 + i]);
        if (i == 0) {
            *(s16 *)(prim + 0xA) = 0x5A;
            *(s16 *)(prim + 0x10) = yOffset + 0x57;
            *(s16 *)(prim + 0x12) = 0x5A;
            *(s16 *)(prim + 8) = leftX;
            *(s16 *)(prim + 0x1A) = 0xA2;
            *(s16 *)(prim + 0x20) = yOffset + 0x57;
            *(s16 *)(prim + 0x22) = 0xA2;
            *(s16 *)(prim + 0x18) = leftX;
        } else {
            *(s16 *)(prim + 8) = yOffset + 0xA5;
            *(s16 *)(prim + 0xA) = 0x5A;
            *(s16 *)(prim + 0x10) = yOffset + 0xE5;
            *(s16 *)(prim + 0x12) = 0x5A;
            *(s16 *)(prim + 0x18) = yOffset + 0xA5;
            *(s16 *)(prim + 0x1A) = 0xA2;
            *(s16 *)(prim + 0x20) = yOffset + 0xE5;
            *(s16 *)(prim + 0x22) = 0xA2;
        }
        AddPrim((u8 *)D_800A38C4 + 8, prim);
    }
    D_800A3568 = (u8 *)D_800A367C;
    func_8005A7B8(2, 4);
    func_8005A818(0x80, 0x80, 0xC0);
    D_800A39C8[0] += 4;
    switch (D_800A3950[0]) {
    case 0xFB:
    case 3:
        func_8005A9F4((s32)D_8009A360[D_800A305B[0]], 0x17, 0x41, 0, 0, 0, 0,
                      0);
        break;
    default:
        func_8005A9F4((s32)D_8009A3A4[D_800A305B[0]], 0x17, 0x41, 0, 0, 0, 0,
                      0);
        break;
    }
    if (D_800A2EB0Absolute[0] == 0) {
        func_8005A9F4((s32)D_8009A3E8[0], 0x17, 0x4D, 0, 0, 1, 0, 0);
    } else {
        func_8005A9F4((s32)D_8009A41C[0], 0x17, 0x4D, 0, 0, 1, 0, 0);
    }
    if (id + 1 >= 0xA) {
        D_8009A3EC[0][4] = 0x31;
        D_8009A3EC[0][5] = id + 0x27;
        D_8009A3EC[0][6] = 0;
    } else {
        D_8009A3EC[0][4] = id + 0x31;
        D_8009A3EC[0][5] = 0;
    }
    func_8005A9F4((s32)D_8009A3EC[0], 0xFC, 0x4D, 0, 0, 0, 0, 0);
    for (i = 0; i < 2; i++) {
        x = 0xA5;
        if (i == 0) {
            x = 0x17;
        }
        color = D_800BE70C[id * 2 + i];
        if (color == D_800A36E0[0]) {
            r2 = 0xC0;
            g2 = 0x80;
            b2 = 0x40;
        } else if (D_800A3644[0] != 0 && color == D_800A36E1[0]) {
            r2 = 0xC0;
            g2 = 0x80;
            b2 = 0x40;
        } else {
            r2 = 0x80;
            g2 = 0x80;
            b2 = 0xC0;
        }
        func_8005A818(r2, g2, b2);
        func_8005A9F4((s32)D_8009ACE0[color], x, 0xA7, 0, 0, 0, 0, 0);
        func_8005A9F4((s32)D_8009AC1C[color], x + 0x1E, 0xA7, 0, 0, 0, 0, 0);
        if (D_800A2EB0Absolute[0] == 0 && D_800AEB34[color] == 0x7FFFFFFF) {
            func_8005A9F4((s32)D_8009A42C[0], x + 0x45, 0x7E, 0, 0, 0, 0, 0);
        } else {
            func_80018588((void *)D_800AEB34[color], -1, entry);
            func_8005A9F4((s32)entry, x + 0x45, 0x7E, 0, 0, 0, 0, 7);
        }
        if (D_800A2EB0Absolute[0] == 0 && id == 0 && i == 0) {
            func_8005A9F4((s32)D_8009A3EC[13], x + 0x59, 0x61, 0, 0, 0, 0, 0);
            func_8005A9F4((s32)D_8009A3EC[14], x + 0x4F, 0x6B, 0, 0, 0, 0, 0);
        }
    }
    D_800A39C8[0] -= 4;
    D_800A3970 = (u8 *)D_800A367C;
    if (yOffset != 0) {
        if (D_800A3568 != (u8 *)D_800A367C) {
            prim = (u8 *)D_800A3568 + 0x20;
            do {
                *(u16 *)(prim - 0x18) = *(u16 *)(prim - 0x18) + yOffset;
                *(u16 *)(prim - 0x10) = *(u16 *)(prim - 0x10) + yOffset;
                *(u16 *)(prim - 8) = *(u16 *)(prim - 8) + yOffset;
                *(u16 *)(prim) = *(u16 *)(prim) + yOffset;
                prim += 0x28;
            } while (prim != (u8 *)D_800A367C + 0x20);
        }
    }
    D_800A3940 = 2;
    D_800A3A44 = yOffset;
    D_800A3760 = 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80065058);
#endif

extern u8 *D_8009A3F0[];
extern u8 *D_8009A400[];
extern u8 *D_8009A418[];
extern u32 *D_800A38C4;
extern u8 *D_800A369C;
extern u8 D_800A3A4C;
void func_80065838(s32 arg0) {
    extern s32 D_800A2EB0Absolute[];
    u8 *str;
    u8 *ptr;
    s32 count;
    s32 len;
    s32 temp;
    volatile s32 framePad[2];

    ptr = D_800A369C;
    if (arg0 & 0xFF) {
        str = D_8009A400[0];
    } else {
        ptr += D_800A3A4C * 0x28;
        if (D_800A2EB0Absolute[0] == 0) {
            str = D_8009A3F0[0];
        } else {
            str = D_8009A418[0];
        }
    }
    count = 0;
    len = strlen((char *)str);
    if (len > 0) {
        do {
            temp = ptr;
            ptr += 0x28;
            count += 1;
            AddPrim(D_800A38C4, temp);
        } while (count < len);
    }
}

extern u8 D_800A35B4;
extern u8 *D_800A38D8;
extern u32 *D_800A38C4;
void func_800658F0(void) {
    s32 i;
    u8 *primitive;
    primitive = D_800A38D8;
    for (i = 0; i < D_800A35B4; i++) {
        AddPrim(D_800A38C4 + 1, primitive);
        primitive += 0x28;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_8006594C);

INCLUDE_ASM("asm/nonmatchings/game", func_80065C3C);

#ifdef NON_MATCHING
/*
 * w8h: size-exact (0x100) and one scheduling row from matching: retail
 * order is `lw a1,0(s0); li a0,0x140; sb v0->D_800A35B4; jal
 * func_8005B0E4; nop` -- our gcc sinks the sb one slot later and fills
 * the jal delay with the li (`sb; jal; li(delay)`). Also note arg1 of
 * func_8005A9F4 is func_8005B0E4's RETURN (s16)-narrowed, not the
 * strlen result; and the first strlen result goes straight to the sb,
 * never into an s-reg (keeps s1/s2 free: retail s0=count s1=ptr s2=len).
 * Tried: nested-call form shown; direct len arg shuffled s-regs.
 * asm("") after the sb statement untested.
 */
extern void func_8005A7B8(s32 arg0, s32 arg1);
extern void func_8005A818(u8 arg0, u8 arg1, u8 arg2);
extern s32 func_8005B0E4(s16 arg0, s32 arg1);
extern void func_8005A9F4(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4,
                          s32 arg5, u8 arg6, u8 arg7);
extern u8 *D_8009A3FC[];
extern u8 *D_800A38D8;
extern s32 D_800A3538;
extern u8 D_800A3884;
void func_80065F80(void) {
    u8 **entry;
    u8 *str;
    u8 *ptr;
    s32 count;
    s32 len;
    s32 temp;
    volatile s32 framePad[2];

    func_8005A7B8(2, 4);
    func_8005A818(0x80, 0x80, 0xC0);
    entry = D_8009A3FC;
    D_800A38D8 = (u8 *)D_800A367C;
    D_800A35B4 = strlen((char *)entry[0]);
    func_8005A9F4((s32)entry[0], func_8005B0E4(0x140, (s32)entry[0]), 0x7F, 0,
                  0, 0, 0, 0);
    ClearOTagR(D_800A38C4, 4);
    ptr = D_800A369C;
    str = D_8009A400[0];
    D_800A3538 = D_800A367C;
    count = 0;
    len = strlen((char *)str);
    if (len > 0) {
        do {
            temp = ptr;
            ptr += 0x28;
            count += 1;
            AddPrim(D_800A38C4, temp);
        } while (count < len);
    }
    D_800A3884 = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80065F80);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80066080);

#ifdef NON_MATCHING
/*
 * w9h draft: display/OT flip with gp save+restore (GetGp + the w4d
 * inline-asm restore). New block-scope externs D_800A3940/D_800A3760 are
 * untracked - recheck the map at the gate. Watch the redundant
 * `andi 0xFF` after the D_800A3884 lbu (func_800669B8 wall family).
 */
void func_800663B0(void) {
    extern s32 D_800A2EB0[];
    extern u8 D_800A39E4[];
    extern u16 D_800A3940;
    extern u8 D_800A3760;
    extern u8 D_800A3884;
    extern u8 D_800A3A4C;
    extern u8 *D_800A369C;
    extern s32 D_800A3538;
    extern s32 D_800A367C;
    extern volatile u8 D_800A3360;
    extern void func_8006594C(s32, s32);
    extern void func_80066080(s32);
    extern u8 *D_8009A3F0[];
    extern u8 *D_8009A418[];
    s32 oldGp;
    u8 *walk;
    char *text;
    s32 count;
    s32 len;
    s32 i;

    oldGp = GetGp();
    func_80058D08(D_8008CA4C[0]);
    SetDispMask(1);
    if ((u8)(D_800A39E4[0] + 3) < 2) {
        if ((s16)D_800A3940 <= 0) {
            if (D_800A3884 == 1) {
                PutDrawEnv(D_800BDD4C);
                ClearOTagR((u32 *)gOrderingTableBank, 4);
                count = D_800A3A4C;
                walk = (u8 *)D_800A369C + count * 0x28;
                if (D_800A2EB0[0] != 0) {
                    text = (char *)D_8009A418[0];
                } else {
                    text = (char *)D_8009A3F0[0];
                }
                len = strlen(text);
                for (i = 0; i < len; i++) {
                    AddPrim((u32 *)gOrderingTableBank + 3, walk);
                    walk += 0x28;
                }
                D_800A367C = D_800A3538;
                func_80066080(0);
                DrawOTag((u32 *)gOrderingTableBank + 3);
                DrawSync(0);
                D_800A3884 = 2;
            }
        } else {
            PutDrawEnv(D_800BDD4C);
            func_8006594C(D_800A3760, 1);
            DrawOTag((u32 *)gOrderingTableBank + 3);
            DrawSync(0);
        }
    }
    D_800A3360 = 1;
    asm("addu $gp, %0, $zero" : : "r"(oldGp));
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800663B0);
#endif

#ifdef NON_MATCHING
/*
 * w9h draft: F4 gradient quad allocator (2 setup slots, then 7x10 quads
 * walking a 0x18-byte queue, ping-pong source slot per outer pass).
 * Locals are REUSED across phases per retail (s0 walker->x0, s2 &slots[0]
 * ->inner counter, s3 rgb8->selector, s4 rgb0x18->y0, s5 arg1->y2).
 */
void *func_8006654C(void *queue, s32 arg1) {
    extern s32 D_800A39C8[];
    extern u8 *func_80057D50(s32);
    s32 *slots[2];
    s32 *p;
    s32 *start;
    s32 cursor;
    s32 c;
    s32 d;
    s32 y;
    s32 scale;
    s32 n;
    s32 i;
    s32 x;
    s32 *src;
    s32 *dst;

    cursor = (s32)queue;
    y = arg1;
    c = 0x18;
    d = 8;
    start = slots;
    p = start;
    do {
        if (cursor != 0) {
            *p = cursor;
            cursor += 0x18;
        } else {
            *p = (s32)func_80057D50(0);
        }
        SetPolyF4((u_long *)*p);
        SetSemiTrans((u_long *)*p, 1);
        if (p == start) {
            ((u8 *)slots[0])[4] = d;
            ((u8 *)slots[0])[5] = d;
            ((u8 *)slots[0])[6] = d;
        } else {
            ((u8 *)*p)[4] = c;
            ((u8 *)*p)[5] = c;
            ((u8 *)*p)[6] = c;
        }
        p += 1;
    } while (p < start + 2);
    n = 0;
    c = 0;
    scale = y << 2;
    do {
        d = (n & 1) == 0;
        i = 0;
        x = 0;
        y = c + 0x20;
        do {
            if (cursor != 0) {
                dst = (s32 *)cursor;
                cursor += 0x18;
            } else {
                dst = (s32 *)func_80057D50(0);
            }
            src = slots[d];
            d ^= 1;
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            dst[4] = src[4];
            dst[5] = src[5];
            ((u16 *)dst)[4] = x;
            ((u16 *)dst)[8] = x;
            x += 0x20;
            ((u16 *)dst)[5] = c;
            ((u16 *)dst)[6] = x;
            ((u16 *)dst)[7] = c;
            ((u16 *)dst)[9] = y;
            ((u16 *)dst)[10] = x;
            ((u16 *)dst)[11] = y;
            AddPrim((u32 *)D_800A39C8[0] + scale, dst);
            i += 1;
        } while (i < 0xA);
        n += 1;
        c += 0x20;
    } while (n < 7);
    return (void *)cursor;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006654C);
#endif

extern u8 *D_800A39C8Ptr[] asm("D_800A39C8");
extern u8 D_800A305B[];
extern u8 D_800A3884;
extern u8 *D_8009A404[];
extern u8 *D_8009A360[];
extern u8 *D_8009A430[];
extern u8 *D_8009A414[];
extern u8 *D_8009A400[];
extern u8 D_8009B198[];
extern DRAWENV D_800BDDA8[];
extern DRAWENV D_800BDD4C[];
extern DISPENV D_800BDE18[];
extern void func_80064CD8(s32);
extern void *func_8006654C(void *, s32);
extern void func_8005E8EC(s32, s32, s32);
extern void func_8005A7B8S32(s32, s32) asm("func_8005A7B8");
extern void func_8005A818(u8, u8, u8);
extern s16 func_8005A8E0(s32);
extern void func_8005A9F4(s32, s16, s16, u8, u8, s32, u8, u8);
extern s32 func_8005B0E4(s16, s32);
extern s32 func_8005A9F4W();
asm(".globl func_8005A9F4W");
asm("func_8005A9F4W = func_8005A9F4");

void func_80066730(void) {
    u8 **table;
    u8 **q;
    s32 page;
    s32 y;
    u8 **p;
    s32 i;
    s16 y16;
    s32 ret;
    s16 x;
    u8 **pp;
    s32 raw;
    s32 a0v;
    s32 a1v;
    s32 rawT;

    func_80064CD8(0);
    PutDrawEnv(&D_800BDDA8[0]);
    table = D_8009A404;
    q = table + 2;
    for (page = 0; page < 2; page++) {
        ClearOTagR((u32 *)D_800A39C8Ptr[0], 0x3FF);
        func_80014A40(0);
        func_8006654C((void *)0, 0x3FC);
        func_8005E8EC(0, 0, 1);
        func_8005A7B8S32(2, 4);
        func_8005A818(0x80, 0x80, 0xC0);
        y = 0xA0;
        i = 0;
        p = table;
        func_8005A9F4(D_8009A360[D_800A305B[0]], 0x20, 0x23, 0, 0, 0, 0, 0);
        do {
            y16 = (s16)y;
            func_8005A9F4(p[0], 0x20, y16, 0, 0, 0, 0, 0);
            ret = (s32)(s16)func_8005A8E0(p[0]);
            x = (s16)(ret + 0x20);
            switch (i) {
            case 0:
                func_8005A9F4(q[D_8009B198[D_800A305B[0]]], x, y16, 0, 0, 0, 0,
                              0);
                break;
            case 1:
                func_8005A9F4(D_8009A430[D_800A305B[0]], x, y16, 0, 0, 0, 0, 0);
                break;
            }
            y += 0xF;
            i++;
            p++;
        } while (i < 2);
        pp = D_8009A414;
        if (page == 0) {
            pp = D_8009A400;
        }
        raw = func_8005B0E4(0x140, (s32)pp[0]);
        asm volatile("lw %0, 0(%3)\n\tsll %2, %4, 16\n\tsra %1, %2, 16"
                     : "=r"(a0v), "=r"(a1v), "=r"(rawT)
                     : "r"(pp), "2"(raw));
        func_8005A9F4W(a0v, a1v, 0xC8, 0, 0, 0, 0, 0);
        DrawOTag((u32 *)(D_800A39C8Ptr[0] + 0xFFC));
        DrawSync(0);
        if (page == 0) {
            PutDrawEnv(&D_800BDD4C[0]);
        }
    }
    PutDispEnv(&D_800BDE18[0]);
    D_800A3884 = 0;
}

extern s32 GetGp(void);
extern s32 D_8008CA4C[];
extern void func_80058D08(s32 gp);
extern u8 D_800A3884;
extern DISPENV D_800BDE04[];
extern volatile u8 D_800A3360;
#ifdef NON_MATCHING
/*
 * Every instruction matches except one: retail keeps
 * `andi v0,v0,0xff` between `lbu v0,0xba4(gp)` (D_800A3884) and the
 * `bne`. gcc 2.7.2 folds the redundant mask of any byte-typed load
 * (s8 decl, u8 local, s32 local, split with asm("")); cse rewrites
 * sign_extend+and to lbu across the barrier. Shapes needed for the
 * mask survived nowhere. The gp-switch shape is otherwise verified:
 * GetGp() pinned in s0 via the trailing asm("addu $gp, %0, $zero"),
 * D_8008CA4C[0] passed as the SetGp value.
 */
void func_800669B8(void) {
    s32 gp;
    s32 flag;

    gp = GetGp();
    func_80058D08(D_8008CA4C[0]);
    SetDispMask(1);
    flag = D_800A3884;
    asm("");
    if ((flag & 0xFF) == 1) {
        PutDispEnv(D_800BDE04);
    }
    D_800A3360 = 1;
    asm("addu $gp, %0, $zero" : : "r"(gp));
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800669B8);
#endif

extern s32 GetGp(void);
extern s32 D_8008CA4C[];
extern u8 D_800A3073[];
extern s32 D_800A335C;
extern void func_800663B0(void);
extern void func_80065C3C(void);
extern void func_800669B8(void);
void func_80066A24(u8 mode) {
    void (*callback)(void);

    *(s32 *)D_8008CA4C = GetGp();
    if (D_800A3644[0] != 0 && D_800A3073[0] == 0) {
        callback = func_800663B0;
    } else {
        callback = func_80065C3C;
        if (mode == 2) {
            callback = func_800669B8;
        }
    }
    EnterCriticalSection();
    D_800A335C = OpenEvent(0xF2000003, 2, 0x1000, callback);
    EnableEvent(*(volatile s32 *)&D_800A335C);
    SetRCnt(0xF2000003, 1, 0x1000);
    StartRCnt(0xF2000003);
    ExitCriticalSection();
}

extern s32 D_800A335C;
extern volatile u8 D_800A3360;
void func_80066B08(void) {
    if (D_800A335C != 0) {
        D_800A3360 = 0;
        while (D_800A3360 == 0) {
        }
        EnterCriticalSection();
        DisableEvent(D_800A335C);
        CloseEvent(D_800A335C);
        ExitCriticalSection();
        DrawSync(0);
    }
    D_800A335C = 0;
}

#ifdef NON_MATCHING
/*
 * w9h draft: double-buffer env setup (2 iterations, +0x5C DRAWENV stride,
 * +0x14 DISPENV stride; sizeof(DRAWENV)=0x58 so byte offsets). Branchless
 * env-x args per the w7a recipe. D_800A365C/D_800A39F4 are new untracked
 * externs - recheck the map at the gate.
 */
void func_80066B70(void) {
    extern s32 D_800A2EB0[];
    extern s32 D_800A365C;
    extern s32 D_800A39F4;
    s32 i;
    s32 height;
    s32 flag;
    s32 off14;
    s32 off5C;
    u8 *env;

    i = 0;
    height = 0xF0;
    flag = 8;
    off14 = 0;
    off5C = 0;
    D_800A365C = gPrimitiveCursor[0];
    func_80050028(D_8009A400[0], 0x8C, 0xD6, 1);
    D_800A39F4 = gPrimitiveCursor[0];
    func_80050028(D_8009A428[0], 0x82, 0xF1, 1);
    for (i = 0; i < 2; i++) {
        env = (u8 *)D_800BDD4C + off5C;
        SetDefDrawEnv((DRAWENV *)env, (0 - (i != 0)) & 0x140, 0, 0x140, height);
        SetDefDispEnv((DISPENV *)((u8 *)D_800BDE04 + off14),
                      (0 - (i == 0)) & 0x140, 0, 0x140, height);
        D_800BDD62[off5C] = 0;
        if (D_800A2EB0[0] == 2) {
            env[0x1A] = 7;
            env[0x19] = 0;
            env[0x1B] = 0x26;
        } else {
            env[0x19] = flag;
            env[0x1A] = flag;
            env[0x1B] = flag;
        }
        off14 += 0x14;
        off5C += 0x5C;
    }
    if (D_800A2EB0[0] == 2) {
        D_800BDD64[0] = 1;
    }
    PutDrawEnv(D_800BDD4C);
    D_800BDDC0[0] = 1;
    D_800BDD64[0] = 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80066B70);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80066CFC);

#ifdef NON_MATCHING
/*
 * w9h retry with the func_8006709C/679C4 recipe (byte-cursor for loop,
 * compound += of (shift >> 24)): still re-associates. gcc folds
 * shift = delta << 24 + the four >> 24 reads into ONE sll+sra pair on
 * the parameter (retail keeps t3 = sll and emits four per-use sra) and
 * splits the cursor into TWO IVs (a0+0x1A for the -0x18..-8 fields,
 * a0+0x22 for the +0 field; +8 bytes total). The same field pattern in
 * 6709C/679C4 kept one IV - there the walk base/limit came from MEMORY
 * (globals); here they are PARAMETERS. Suspect loop.c ivrs treats
 * param-derived pointers differently. Entry-assigned shift did not help.
 */
void func_80067020(u8 *start, u8 *end, u8 delta) {
    u8 *walk;
    s32 shift;

    if (start < end) {
        shift = delta << 24;
        for (walk = start + 0x22; walk < end + 0x22; walk += 0x28) {
            if (walk[-0x1C] != 0) {
                *(u16 *)(walk - 0x18) += shift >> 24;
                *(u16 *)(walk - 0x10) += shift >> 24;
                *(u16 *)(walk - 0x8) += shift >> 24;
                *(u16 *)(walk + 0) += shift >> 24;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80067020);
#endif

#ifdef NON_MATCHING
/*
 * w9h draft: palette delta walk. SCRATCH_TOP unlock (fixed_address);
 * D_800A3848/3898/389C are newly declared here (untracked - recheck the
 * map at the gate). Retail recomputes (shift >> 24) per field; watch for
 * gcc CSE merging the four sra into one (the func_80067020 wall).
 */
void func_8006709C(u8 arg0) {
    extern s32 D_800A3848[];
    extern u8 D_800A3644[];
    extern u16 *D_800A39C8p[] asm("D_800A39C8.NON_MATCHING");
    extern u16 *D_800A3898;
    extern u16 *D_800A389C[];
    extern u16 SCRATCH_TOP[];
    s32 cur;
    s32 shift;
    s32 arg;
    u16 *base;
    u16 *limit;
    u8 *walk;

    shift = arg0 << 24;
    cur = D_800A3848[0] - (shift >> 23);
    D_800A3848[0] = cur;
    if (cur < 0xA0) {
        D_800A3848[0] = 0xA0;
        return;
    }
    if (cur >= 0x1EB) {
        D_800A3848[0] = 0x1EA;
        return;
    }
    if (D_800A3644[0] != 0) {
        return;
    }
    arg = arg0;
    base = D_800A39C8p[0];
    limit = D_800A3898;
    if (base + 8 < limit) {
        for (walk = (u8 *)base + 0x32; walk < (u8 *)limit + 0x22;
             walk += 0x28) {
            if (walk[-0x1C] != 0) {
                *(u16 *)(walk - 0x18) += shift >> 24;
                *(u16 *)(walk - 0x10) += shift >> 24;
                *(u16 *)(walk - 0x8) += shift >> 24;
                *(u16 *)(walk + 0) += shift >> 24;
            }
        }
    }
    base = D_800A389C[0];
    if (base != 0 && base < (u16 *)SCRATCH_TOP) {
        shift = arg << 24;
        for (walk = (u8 *)base + 0x22; walk < (u8 *)SCRATCH_TOP + 0x22;
             walk += 0x28) {
            if (walk[-0x1C] != 0) {
                *(u16 *)(walk - 0x18) += shift >> 24;
                *(u16 *)(walk - 0x10) += shift >> 24;
                *(u16 *)(walk - 0x8) += shift >> 24;
                *(u16 *)(walk + 0) += shift >> 24;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006709C);
#endif

#ifdef NON_MATCHING
/*
 * w9h draft: two rotated u16 loops over ordering-table bases. Retail
 * reaches D_800A387C/D_800A36BC through $gp (block-scope scalar externs
 * here; D_800A36BC is untracked - recheck the map at the gate) and the
 * D_8009A400/D_8009A428/D_800A39C8 pointer slots absolutely (array form).
 * D_8009A428 = D_8009A400[10] (already-declared neighbor, +0x28).
 */
void func_80067228(void) {
    extern u16 *D_800A387C;
    extern u16 *D_800A36BC;
    extern u16 *D_800A39C8p[] asm("D_800A39C8.NON_MATCHING");
    extern u8 *D_8009A400[];
    u16 *baseA;
    u16 *baseB;
    u16 *baseB2;
    u16 *cursor;
    u16 *end;
    s32 i;
    s32 len;

    len = strlen(D_8009A400[0]);
    baseA = D_800A387C;
    baseB = D_800A39C8p[0];
    baseB2 = baseB + 0x2000;
    i = 0;
    if (len > 0) {
        cursor = baseA + 0x11;
        end = baseB + 0x2011;
        for (i = 0; i < len; i++) {
            cursor[-0xC] = 0xF1;
            cursor[-0x8] = 0xF1;
            cursor[-0x4] = 0xF1;
            cursor[0] = 0xF1;
            if (cursor < end) {
                cursor += 0x14;
            } else {
                cursor -= 0x14;
            }
        }
    }
    baseA = D_800A36BC;
    len = strlen(D_8009A400[10]);
    if (len > 0) {
        cursor = baseA + 0x11;
        end = baseB2 + 0x11;
        for (i = 0; i < len; i++) {
            cursor[-0xC] -= 0x1B;
            cursor[-0x8] -= 0x1B;
            cursor[-0x4] -= 0x1B;
            cursor[0] -= 0x1B;
            if (cursor < end) {
                cursor += 0x14;
            } else {
                cursor -= 0x14;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80067228);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8006733C);

INCLUDE_ASM("asm/nonmatchings/game", func_80067598);

#ifdef NON_MATCHING
/*
 * w9h draft: palette delta walks over two linked lists (+= then -=).
 * Same recipe as the func_8006709C loops; D_800A3568/D_800A3970 are
 * newly declared (untracked - recheck the map at the gate).
 */
void func_800679C4(u8 arg0) {
    extern u16 *D_800A3568;
    extern u16 *D_800A367C;
    extern u16 *D_800A3970;
    s32 shift;
    s32 arg;
    u16 *base;
    u16 *limit;
    u8 *walk;

    arg = arg0;
    base = D_800A3568;
    limit = D_800A367C;
    if (base < limit) {
        shift = arg0 << 24;
        for (walk = (u8 *)base + 0x20; walk < (u8 *)limit + 0x20;
             walk += 0x28) {
            *(u16 *)(walk - 0x18) += shift >> 24;
            *(u16 *)(walk - 0x10) += shift >> 24;
            *(u16 *)(walk - 0x8) += shift >> 24;
            *(u16 *)(walk + 0) += shift >> 24;
        }
    }
    base = D_800A367C;
    limit = D_800A3970;
    if (base < limit) {
        shift = arg << 24;
        for (walk = (u8 *)base + 0x2C; walk < (u8 *)limit + 0x2C;
             walk += 0x34) {
            *(u16 *)(walk - 0x24) -= shift >> 24;
            *(u16 *)(walk - 0x18) -= shift >> 24;
            *(u16 *)(walk - 0xC) -= shift >> 24;
            *(u16 *)(walk + 0) -= shift >> 24;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800679C4);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80067AB4);

/*
 * w4d: this TU position (after the func_80067AB4 slot) matches retail
 * address order; the C body landed on 0x80067AB4 when placed before it.
 */
extern void func_8006733C(void);
extern void func_80067AB4(void);
void func_80067DFC(void) {
    void (*callback)(void);

    *(s32 *)D_8008CA4C = GetGp();
    callback = func_8006733C;
    if (D_800A2EB0Absolute[0] == 2) {
        callback = func_80067AB4;
    }
    EnterCriticalSection();
    D_800A335C = OpenEvent(0xF2000003, 2, 0x1000, callback);
    EnableEvent(*(volatile s32 *)&D_800A335C);
    SetRCnt(0xF2000003, 1, 0x1000);
    StartRCnt(0xF2000003);
    ExitCriticalSection();
}

typedef struct UnkPacket0C {
    u8 unk0, unk1, unk2, unk3;
    s32 unk4, unk8;
} UnkPacket0C;
typedef struct UnkObject24 {
    u8 unk0[0x1A];
    s16 unk1A;
    u8 unk1C[4];
    UnkPacket0C *unk20;
} UnkObject24;
void func_80067EA4(UnkObject24 *obj, u8 a, u8 b, s32 c, u8 d, s32 e) {
    UnkPacket0C *p;
    p = obj->unk20;
    p->unk1 = a;
    p->unk2 = b;
    p->unk8 = c;
    p->unk3 = d;
    p->unk4 = e;
    obj->unk1A = e;
}

extern char *D_8009AC1C[];
u8 func_80067ECC(char *name) {
    s32 i;

    for (i = 0; i < 0x18; i++) {
        if (strcmp(name, D_8009AC1C[i]) == 0) {
            break;
        }
    }
    return i;
}

#ifdef NON_MATCHING
/* Wall (a7): structure matches retail case-for-case (switch table
 * regenerates jtbl_8008FA14 exactly, no pad word needed - even count) but
 * gcc swaps register pairs (obj s7/s6, hdr a0/a2, pkt v1/a0, cursor s4/s7)
 * which cascades ~115 renamed rows plus: the (arg0&0xFF)*4 scale sits after
 * the prologue saves instead of inside them, the D_8009A31C reload after
 * func_8005A8E0 gains a nop, and the (j != 0 && j != 5) flag's else-arm
 * lands at the branch target instead of its delay slot (+4 bytes).
 * Enablers verified: D_800A35F4 must be reached via
 * ((u8 *)D_800A3668Absolute - 0x74) (a direct extern flips to gp-rel via
 * the later scalar decl in maspsx's sdata list); obj loads need the
 * *(T **)(base + off) cast form (array [idx] on a u8 base emits lbu).
 * Permuter candidate. */
void func_80067F34(s32 arg0, s32 arg1) {
    typedef struct UnkTextObj67F34 {
        s16 unk0;
        u8 unk2[4];
        s16 unk6;
        s16 unk8;
        s16 unkA;
        u8 unkC[6];
        s16 unk12;
        u8 unk14[6];
        s16 unk1A;
        struct UnkTextObj67F34 *unk1C;
        UnkPacket0C *unk20;
    } UnkTextObj67F34;
    extern char *D_8009A474[];
    extern char *D_8009A31C[];
    extern void *D_8009AC1C[];
    extern s32 D_8009AC80[];
    extern s32 D_800A3668Absolute[];
    extern u8 *D_800A3854Absolute[];
    extern s32 D_800A3A54[];
    UnkTextObj67F34 *obj;
    UnkTextObj67F34 *next;
    UnkPacket0C *pkt;
    u8 *name;
    u8 *entry;
    s32 value;
    s32 w;
    s32 sum;
    s32 hdr;
    s32 recordOff;
    s32 cursor;
    s32 flag;
    s32 i;
    s32 j;
    s32 k;
    char buf[0x48];

    obj = *(UnkTextObj67F34 **)((u8 *)D_800A3668Absolute - 0x5C +
                                (arg0 & 0xFF) * 4);
    func_8005A7B8S32(2, 3);
    strcpy(buf, D_8009A474[0]);
    strcat(buf, D_8009A31C[arg1 & 0xFF]);
    w = func_8005A8E0((s32)buf);
    sum = (0x140 - w) / 2;
    obj->unk6 = sum;
    obj->unkA = sum;
    obj->unk12 = *(volatile u16 *)&obj->unk6;
    next = obj->unk1C;
    w = func_8005A8E0((s32)D_8009A474[0]);
    sum = obj->unk6 + w;
    hdr = next->unk1A;
    next->unk6 = sum;
    next->unk12 = sum;
    pkt = next->unk20;
    pkt->unk1 = 2;
    pkt->unk2 = 3;
    pkt->unk3 = 0;
    pkt->unk4 = hdr;
    pkt->unk8 = (s32)D_8009A31C[arg1 & 0xFF];
    next->unk1A = hdr;
    obj =
        *(UnkTextObj67F34 **)((u8 *)D_800A3854Absolute + (arg0 & 0xFF) * 4 + 4);
    if (((u8 *)D_800A3A54)[4] > 0) {
        recordOff = (arg1 & 0xFF) * 0xC;
        cursor = 0;
        i = 0;
        do {
            j = 0;
            do {
                switch (j) {
                case 0:
                    k = 0;
                    entry = (u8 *)D_8009AC1C;
                    name = cursor + *(u8 **)((u8 *)D_800A3668Absolute - 0x74);
                    do {
                        if (strcmp((char *)name, *(char **)entry) == 0) {
                            break;
                        }
                        k++;
                        entry += 4;
                    } while (k < 0x18);
                    value = D_8009AC80[k & 0xFF];
                    break;
                case 1:
                    value = *(cursor + recordOff +
                              *(u8 **)((u8 *)D_800A3668Absolute - 0x74) + 0x1C);
                    break;
                case 2:
                    value = *(cursor + recordOff +
                              *(u8 **)((u8 *)D_800A3668Absolute - 0x74) + 0x1D);
                    break;
                case 3:
                    value = *(cursor + recordOff +
                              *(u8 **)((u8 *)D_800A3668Absolute - 0x74) + 0x1E);
                    break;
                case 4:
                    value = *(cursor + recordOff +
                              *(u8 **)((u8 *)D_800A3668Absolute - 0x74) + 0x1F);
                    break;
                case 5:
                    value = *(s32 *)(cursor + recordOff +
                                     *(u8 **)((u8 *)D_800A3668Absolute - 0x74) +
                                     0x20);
                    break;
                }
                if (j == 0) {
                    flag = 0;
                } else {
                    flag = j != 5;
                }
                hdr = obj->unk1A;
                pkt = obj->unk20;
                pkt->unk1 = 2;
                pkt->unk2 = 3;
                pkt->unk8 = value;
                pkt->unk3 = flag;
                pkt->unk4 = hdr;
                obj->unk1A = hdr;
                obj = obj->unk1C;
                j++;
            } while (j < 6);
            cursor += 0xE8;
            i++;
        } while (i < ((u8 *)D_800A3A54)[4]);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80067F34);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80068220);

void func_800686FC(s32 arg0, s32 arg1) {
    extern s32 D_800A3914[];
    extern u8 *D_800A37D4;
    extern u8 *D_800A3870;
    extern s8 D_800A3944;
    extern s8 D_800A39DC;
    extern s32 D_800A3A54[];
    extern u8 *D_800A3854Absolute[];
    extern u8 *D_800A3900Ptr asm("D_800A3900.NON_MATCHING");
    extern u8 *D_800A360C;
    extern u8 *D_800A3858;

    func_8005B8B8(D_800A3900Ptr, 0xFF);
    if ((arg0 & 0xFF) == 9 && ((u8 *)D_800A3A54)[4] != 0) {
        if (D_800A37D4 != 0) {
            func_8005B688(D_800A37D4, 1);
            func_8005B8B8(D_800A37D4, 0xFF);
        }
        if (D_800A3870 != 0) {
            func_8005B688(D_800A3870, 1);
            func_8005B8B8(D_800A3870, 0xFF);
        }
    } else {
        func_8005B8B8(D_800A360C, 0xFF);
    }
    if (D_800A3914[0] != 0) {
        func_8005B8B8((u8 *)D_800A3914[0], 0xFF);
    }
    switch ((arg0 & 0xFF) - 9) {
    case 0:
        if (((u8 *)D_800A3A54)[4] != 0) {
            func_80057F34(arg1 & 0xFF, 0, 0x57, 0x140, 0x7B, 0xA);
        }
        break;
    case 1:
        func_80057F34(arg1 & 0xFF, 0, 0x9D, 0x140, 0x35, 0xA);
        break;
    case 3:
    case 7:
    case 8:
        func_80057F34(arg1 & 0xFF, 0, 0x39, 0x140, 0x99, 0xA);
        break;
    }
    switch (arg0 & 0xFF) {
    case 0xA:
    case 0xC:
        goto hideIt;
    }
    if ((u8)(arg0 - 0x10) < 2) {
    hideIt:
        func_8005B8B8(D_800A3858, 0xFF);
    } else if ((arg0 & 0xFF) == 9) {
        if (((u8 *)D_800A3A54)[4] != 0) {
            if (D_800A37D4 != 0) {
                func_8005B688(D_800A3854Absolute[D_800A3944 + 1], 1);
                func_8005B8B8(D_800A3854Absolute[D_800A3944 + 1], 0xFF);
            }
            if (D_800A3870 != 0) {
                func_8005B688(D_800A3854Absolute[D_800A39DC + 1], 1);
                func_8005B8B8(D_800A3854Absolute[D_800A39DC + 1], 0xFF);
            }
        }
    }
}

/* The original toolchain padded this odd-length jump table with one zero
 * word; the C switch regenerates the table, this restores the pad. */
void __maspsx_include_asm_hack_jtblpad_800686FC() {
    __asm__(".section .rodata # maspsx-keep \n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

#ifdef NON_MATCHING
/*
 * w7h: size-exact (0xF0) and 60/62 rows clean. The two rows: retail has
 * `lh v1,8(v0); lh v0,0xc(v0)` feeding a plain `subu`; ours emits lhu
 * for the same C -- gcc 2.7.2 combine rewrote the sign-extending loads
 * to zero-extending because the difference only feeds addu+sh (extends
 * the w5b "lh only before a multiply" wall to: never after, either).
 * Also load-bearing for the rest of the match: the byte masks at the
 * two table uses must be spelled INLINE (`D_800A360C[arg0 & 0xFF]`,
 * `D_800A3858[arg0 & 0xFF]`) while the dead `index = arg0 & 0xFF`
 * assignments stay -- they give retail's delay-slot andis at 0x8006896C
 * and 0x80068998 (gcc does not CSE-kill them through the loop).
 */
void func_8006894C(s32 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4) {
    extern UnkNode1C *D_800A360C[];
    extern UnkNode1C *D_800A3858[];
    UnkNode1C *node;
    u8 *other;
    s32 index;
    s16 v1;

    index = arg0 & 0xFF;
    node = D_800A360C[arg0 & 0xFF];
    if (node != NULL) {
        do {
            node->unkE = arg3;
            node->unk6 = node->unk12 + arg1;
            node->unkA = node->unk12 + arg2;
            node = node->next;
            index = arg0 & 0xFF;
        } while (node != NULL);
    }
    node = D_800A3858[arg0 & 0xFF];
    if (arg4 != 0) {
        other = (u8 *)D_800A3858[(arg0 ^ 1) & 0xFF];
        v1 = *(s16 *)(other + 8);
        v1 -= *(s16 *)(other + 0xC);
    } else {
        v1 = 0;
    }
    if (node != NULL) {
        do {
            node->unk6 = node->unk12 + arg1;
            if (arg4 != 0) {
                node->unk8 = node->unkC + v1;
            }
            node->unkE = arg3;
            node->unkA = node->unk12 + arg2;
            node = node->next;
        } while (node != NULL);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006894C);
#endif

void func_80068A3C(u8 *head, u8 *other, s32 delta, s32 limit, s32 mid) {
    s16 base;

    if (delta > 0) {
        base = *(s16 *)(head + 8);
        if (limit < base + delta) {
            delta = limit - base;
        }
    } else {
        if (delta < 0) {
            if ((s32) * (s16 *)(other + 8) + delta < mid) {
                delta = mid - *(s16 *)(other + 8);
            }
        }
    }
    if (delta != 0) {
        if (head != 0) {
            do {
                *(u16 *)(head + 8) += delta;
                head = *(u8 **)(head + 0x1C);
            } while (head != 0);
        }
    }
}

extern s32 D_800A3830Absolute[];
extern s32 D_800A3830Absolute2[];
extern s32 D_800A37F0Absolute[];
extern s32 D_800A37F0Absolute2[];
extern s32 D_800A37F0Absolute3[];
extern u8 D_800A39E4NM[] asm("D_800A39E4.NON_MATCHING");
extern u8 D_800A3A58NM[] asm("D_800A3A58.NON_MATCHING");
extern s16 D_800B9B84NM[] asm("D_800B9B84.NON_MATCHING");
extern u8 *D_800A3858NM[] asm("D_800A3858.NON_MATCHING");
extern u8 *D_800A3918NM[] asm("D_800A3918.NON_MATCHING");
extern u8 *D_800A3918NB[] asm("D_800A3918.NON_MATCHING");
void func_80068AC4(s32 arg0, s32 arg1, s32 arg2) {
    extern u8 D_800A3944;
    register s32 delta asm("$8");
    s32 threshold;
    register s32 delta2 asm("$4");
    s32 sum;
    register s32 posflag asm("$2");
    s32 limit;
    s32 limitSave;
    s32 dneg;
    s32 val;
    s32 idx;
    u8 *head;
    u8 *other;
    u8 *walk;

    threshold = 5;
    if (arg0 & ~arg1) {
        D_800A3830Absolute2[0] = 0;
        limitSave = 1;
    } else {
        D_800A3830Absolute[0] = D_800A3830Absolute2[0] + 1;
        if (threshold < D_800A3830Absolute[0]) {
            D_800A37F0Absolute[0] =
                D_800A37F0Absolute2[0] + D_800A37F0Absolute2[0] / 2;
            if (0x41 <= D_800A37F0Absolute[0]) {
                limitSave = 0x40;
            } else {
                goto noStore;
            }
        } else {
            return;
        }
    }
    D_800A37F0Absolute3[0] = limitSave;
noStore:
    if (arg2 & 0xFF) {
        delta = D_800A37F0Absolute3[0];
    } else {
        dneg = D_800A37F0Absolute3[0];
        asm("negu %0, %1" : "=r"(delta) : "r"(dneg));
    }
    val = D_800A39E4NM[0];
    if ((val & 0xFF) == 9) {
        limit = 0x7B;
    } else if ((val & 0xFF) == 0xA) {
        limit = 0x35;
    } else if ((val & 0xFF) == 0xC || (val - 0x10) < 2U) {
        limit = 0x99;
    }
    limit = limit - 0xD;
    if (D_800A39E4NM[0] == 9) {
        if (D_800A3A58NM[0] == 0) {
            return;
        }
    }
    if (D_800A39E4NM[0] == 0xC) {
        if (D_800B9B84NM[0] == 0) {
            return;
        }
    }
    idx = 0;
    if (D_800A39E4NM[0] == 9) {
        idx = D_800A3944;
    }
    head = D_800A3858NM[idx];
    if (*(s16 *)(head + 8) >= 0) {
        if (*(s16 *)(D_800A3918NM[idx] + 8) < limit) {
            return;
        }
    }
    other = D_800A3918NB[idx];
    delta2 = delta;
    if (delta2 > 0) {
        sum = *(s16 *)(head + 8) + delta2;
        asm("slt %0, $zero, %1" : "=r"(posflag) : "r"(sum));
        if (posflag != 0) {
            delta2 = -*(s16 *)(head + 8);
        }
    } else if (delta2 < 0) {
        if (*(s16 *)(other + 8) + delta2 < limit) {
            delta2 = limit - *(s16 *)(other + 8);
        }
    }
    if (delta2 == 0) {
        return;
    }
    walk = head;
    if (walk != 0) {
        do {
            *(u16 *)(walk + 8) += delta2;
            walk = *(u8 **)(walk + 0x1C);
        } while (walk != 0);
    }
}

typedef struct UnkTextObj {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    u8 unkC[6];
    s16 unk12;
    u8 unk14[6];
    s16 unk1A;
    struct UnkTextObj *unk1C;
    UnkPacket0C *unk20;
} UnkTextObj;
extern UnkTextObj *D_800A3900Obj asm("D_800A3900.NON_MATCHING");
extern UnkTextObj *D_800A360C;
extern UnkTextObj *D_800A3858;
extern UnkTextObj *D_800A3918;
UnkTextObj *func_8005B314(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
UnkTextObj *func_8005BF8C(s32, s32);
s32 func_8005B0E4(s16, s32);

#ifdef NON_MATCHING
/* Wall (a7): structure is byte-count correct at 0x4F0 and every basic
 * block matches retail, but gcc allocates the loop temporaries one
 * register off (retail obj=a1/half=v0/i=s5/value=s6; ours obj=v1/half=v1/
 * i=s6/value=s5), which cascades ~220 reg-renamed rows and a stray second
 * spill slot (frame 0xA0 vs 0x98). Declaration order has no effect; the
 * 0x40/0xF0 select needs the per-arm-call form (ternary goes branchless
 * sltu/negu/andi/ori under the r4000 profile); loop B's i==1/2/3 chain
 * compiles identical as switch or else-if. Permuter candidate. */
void func_80068CE4(void) {
    extern char *strcpy(char *, const char *);
    extern char *D_8009A498[];
    extern char *D_8009A4B0[];
    extern s32 D_8009B1C4[];
    extern s32 D_8009A31C[];
    extern char D_800B9B54[];
    extern s8 D_800B9B6E[];
    extern u8 D_800B9BB4[];
    UnkTextObj *obj;
    UnkTextObj *prev;
    UnkTextObj *tail;
    UnkPacket0C *pkt;
    u8 *record;
    char buf[0x40];
    s32 value;
    s32 flag;
    s32 w;
    s32 x;
    s32 y;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        obj = func_8005B314(0, 0x27, 0x140, 0xC8, 0, 0x10, 0x10, 0x10, 1, 1);
        if (i == 0) {
            D_800A3900Obj = obj;
        } else {
            D_800A3900Obj->unk1C = obj;
        }
        obj->unk1A = 0x3FD;
    }
    prev = func_8005BF8C(0, 0x2A);
    D_800A360C = prev;
    func_8005A7B8S32(2, 3);
    strcpy(buf, D_800B9B54);
    y = 0x39;
    strcat(buf, D_8009A498[0]);
    w = func_8005A8E0((s32)buf);
    pkt = prev->unk20;
    x = (0x140 - w) / 2;
    prev->unk6 = x;
    prev->unkA = x;
    prev->unk1A = 0x32;
    pkt->unk1 = 2;
    pkt->unk2 = 3;
    pkt->unk8 = (s32)D_800B9B54;
    pkt->unk3 = 0;
    pkt->unk4 = 0x32;
    prev->unk1A = 0x32;
    obj = func_8005BF8C(prev->unk6 + func_8005A8E0((s32)D_800B9B54), 0x2A);
    obj->unk1A = 0x32;
    value = (s32)D_8009A498[0];
    pkt = obj->unk20;
    pkt->unk1 = 2;
    pkt->unk2 = 3;
    pkt->unk8 = value;
    pkt->unk3 = 0;
    pkt->unk4 = 0x32;
    obj->unk1A = 0x32;
    prev->unk1C = obj;
    tail = obj;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 2; j++) {
            obj = func_8005BF8C(j == 0 ? 0x40 : 0xF0, y);
            obj->unk1A = 0x32;
            if (j == 0) {
                value = (s32)D_8009A498[i + 1];
            } else {
                switch (i) {
                case 0:
                    value = D_800B9B6E[0];
                    break;
                case 1:
                    value = D_800B9B6E[1];
                    break;
                case 2:
                    value = D_800B9B6E[2];
                    break;
                case 3:
                    value = D_800B9B6E[3];
                    break;
                case 4:
                    value = D_800B9B6E[4];
                    break;
                }
                obj->unk0 = 5;
            }
            w = obj->unk1A;
            pkt = obj->unk20;
            pkt->unk1 = 2;
            pkt->unk2 = 3;
            pkt->unk8 = value;
            pkt->unk3 = j;
            pkt->unk4 = w;
            obj->unk1A = w;
            tail->unk1C = obj;
            tail = obj;
        }
        y += 0xF;
    }
    for (i = 0; i < 4; i++) {
        x = D_8009B1C4[i];
        if (i == 2) {
            x += 8;
        } else if (i == 1) {
            x += 4;
        } else if (i == 3) {
            x += 0xA;
        }
        obj = func_8005BF8C(x, 0x89);
        obj->unk1A = 0x32;
        value = (s32)D_8009A4B0[i];
        pkt = obj->unk20;
        pkt->unk1 = 2;
        pkt->unk2 = 3;
        pkt->unk8 = value;
        pkt->unk3 = (u32)(i - 1) < 2;
        pkt->unk4 = 0x32;
        obj->unk1A = 0x32;
        tail->unk1C = obj;
        tail = obj;
    }
    y = 0;
    for (i = 0; i < 0x11; i++) {
        record = &D_800B9BB4[i * 0xC];
        for (j = 0; j < 4; j++) {
            obj = func_8005BF8C(D_8009B1C4[j], y);
            if (i == 0 && j == 0) {
                D_800A3858 = obj;
            } else {
                tail->unk1C = obj;
            }
            obj->unk1A = 0;
            if (j > 0) {
                if (j < 3) {
                    obj->unk0 = 5;
                } else if (j == 3) {
                    obj->unk0 = 6;
                }
            }
            flag = 0;
            switch (j) {
            case 0:
                value = D_8009A31C[i];
                break;
            case 1:
                value = *(s16 *)(record + 4);
                flag = 1;
                break;
            case 2:
                value = *(s16 *)(record + 6);
                flag = 1;
                break;
            case 3:
                value = *(s32 *)(record + 8);
                break;
            }
            pkt = obj->unk20;
            pkt->unk1 = 2;
            pkt->unk2 = 3;
            pkt->unk8 = value;
            pkt->unk3 = flag;
            pkt->unk4 = 0;
            obj->unk1A = 0;
            tail = obj;
        }
        if (i == 0x10) {
            D_800A3918 = tail;
        }
        y += 0xF;
    }
    func_8005DEDC(0x3E8);
}

#else
INCLUDE_ASM("asm/nonmatchings/game", func_80068CE4);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_800691D4);

typedef struct UnkBlockOffsets {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} UnkBlockOffsets;
extern UnkBlockOffsets *D_800A3A30;
extern void *D_800A3A24[];
extern void *D_800A336C;
extern s32 D_800A3370, D_800A3374, D_800A3378Small;

void func_80069744(void) {
    s32 block;

    block = (s32)func_80058094(0xB, (void **)D_800A3A24 + 3, 0);
    D_800A336C = (void *)block;
    if (block != 0) {
        D_800A3370 = block + D_800A3A30->unk0;
        D_800A3374 = block + D_800A3A30->unk4;
        D_800A3378Small = block + D_800A3A30->unk8;
        func_800641EC();
    }
}

extern void *D_800A336C;
extern s32 D_800A3370, D_800A3374, D_800A3378Small;
void func_800697B4(void) {
    if (D_800A336C != 0)
        HeapFree(D_800A336C);
    D_800A336C = 0;
    D_800A3370 = 0;
    D_800A3374 = 0;
    D_800A3378Small = 0;
}

extern u8 D_8009AD40[];
extern s16 func_8005A84C(void);

#ifdef NON_MATCHING
void func_800697EC(u8 mode) {
    UnkTextObj *obj;
    UnkTextObj *prev;
    UnkPacket0C *pkt;
    s8 **table;
    s8 *buf;
    s8 *p;
    s16 i;
    s32 x;
    s32 w;
    s16 width;
    s32 j;
    s8 c;

    j = 0;
    do {
        obj = func_8005B314(0, 0x27, 0x140, 0xC8, 0, 0x10, 0x10, 0x10, 1, 1);
        if (j == 0) {
            D_800A3900Obj = obj;
        } else {
            D_800A3900Obj->unk1C = obj;
        }
        obj->unk1A = 0x3FD;
        j += 1;
    } while (j < 2);

    prev = func_8005BF8C(0, 0x2A);
    D_800A360C = prev;
    func_8005A7B8S32(2, 3);
    table = (s8 **)D_8009AD40 + 2;
    w = func_8005B0E4(0x140, (s32)table[mode]);
    prev->unk6 = w;
    prev->unkA = w;
    prev->unk1A = 0x32;
    pkt = prev->unk20;
    pkt->unk1 = 2;
    pkt->unk2 = 3;
    pkt->unk8 = (s32)table[mode];
    pkt->unk3 = 0;
    pkt->unk4 = 0x32;
    prev->unk1A = 0x32;
    if (mode != 0) {
        buf = (s8 *)D_800A3374;
    } else {
        buf = (s8 *)D_800A3370;
    }
    func_8005A7B8S32(2, 4);
    width = func_8005A84C();
    x = 0;
    i = 0;
    for (;;) {
        p = buf + i;
        c = *p;
        if (c == '%') {
            D_800A3918 = prev;
            break;
        }
        if (c == '\n') {
            x += width / 4;
        } else {
            obj = func_8005BF8C(0, x);
            if (*p == '*') {
                p = buf + i + 1;
                obj->unk2 = 0xF0;
                obj->unk3 = 0x40;
                obj->unk4 = 0x40;
            }
            w = func_8005B0E4(0x140, (s32)p);
            pkt = obj->unk20;
            obj->unk12 = w;
            obj->unk6 = w;
            obj->unkA = w;
            obj->unk1A = 0;
            pkt->unk1 = 2;
            pkt->unk2 = 4;
            pkt->unk8 = (s32)p;
            pkt->unk3 = 0;
            pkt->unk4 = 0;
            if (i != 0) {
                prev->unk1C = obj;
            } else {
                D_800A3858 = obj;
            }
            prev = obj;
        }
        x += width;
        if (buf[i] != 0) {
            do {
                i++;
            } while (buf[i] != 0);
        }
        i++;
    }
    func_8005DEDC(0x3E8);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800697EC);
#endif

s32 func_80069A90(s32 arg0) {
    switch (arg0 & 0xFF) {
    case 0:
    case 1:
    case 3:
    case 6:
    case 15:
        return 0;
    case 2:
    case 4:
    case 5:
    case 7:
    case 8:
    case 11:
        return 1;
    case 10:
        return 3;
    case 12:
    case 16:
    case 17:
        return 4;
    case 34:
    case 36:
    case 40:
        return 5;
    case 35:
        return 6;
    case 9:
    case 14:
    case 33:
        return 7;
    default:
        return 0xFF;
    }
}

/* The original toolchain padded this odd-length jump table with one zero
 * word; the C switch regenerates the table, this restores the pad. */
void __maspsx_include_asm_hack_jtblpad_80069A90() {
    __asm__(".section .rodata # maspsx-keep \n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

void func_80069AFC(s32 arg0) {
    extern void *D_800A3914[];
    extern void *D_800A3A24[];
    extern s8 D_800A307C[];
    extern s32 D_8009A2D4[];
    extern s32 D_8009A2F4[];
    extern s32 func_8005B0E4(s16, s32);
    register s32 group asm("v1");
    s32 index;
    s32 value;
    u8 *obj;
    u8 *child;

    switch (arg0 & 0xFF) {
    case 0:
    case 1:
    case 3:
    case 6:
    case 15:
        group = 0;
        break;
    case 2:
    case 4:
    case 5:
    case 7:
    case 8:
    case 11:
        group = 1;
        break;
    case 10:
        group = 3;
        break;
    case 12:
    case 16:
    case 17:
        group = 4;
        break;
    case 34:
    case 36:
    case 40:
        group = 5;
        break;
    case 35:
        group = 6;
        break;
    case 9:
    case 14:
    case 33:
        group = 7;
        break;
    default:
        group = 0xFF;
        break;
    }
    /* The retail compiler keeps the u8 truncation of the switch result. */
    asm("andi %0, %0, 0xff" : "=r"(group) : "0"(group));
    index = group;
    if (group == 0xFF) {
        register u8 *retObj asm("v1");

        retObj = (u8 *)D_800A3914[0];
        if (retObj != 0) {
            *(s16 *)(retObj + 0x1A) = -0x32;
            return;
        }
    }
    func_8005A7B8S32(2, 2);
    if (((s8 *)D_800A3A24)[0] == 2) {
        value = func_8005B0E4(0x140, D_8009A2F4[index]);
    } else {
        value = func_8005B0E4(0x140, D_8009A2D4[index]);
    }
    obj = (u8 *)D_800A3914[0];
    *(s16 *)(obj + 6) = value;
    *(s16 *)(obj + 0x1A) = 0x32;
    child = *(u8 **)(obj + 0x20);
    if (((s8 *)D_800A3A24)[0] == 2 && D_800A307C[0] != 6) {
        *(s32 *)(child + 8) = D_8009A2F4[index];
    } else {
        *(s32 *)(child + 8) = D_8009A2D4[index];
    }
    /* The retail jump table is followed by a zero pad word at 0x8008FBB8. */
    asm(".rdata");
    asm(".long 0");
    asm(".text");
}

INCLUDE_ASM("asm/nonmatchings/game", func_80069C60);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008FC60);

extern char *D_800A35F4;
extern char *D_800A3604;
extern char *D_800A366C;
extern char *D_800A3978;
extern char *D_800A3A0C;

void func_80069E88(void) {
    D_800A366C = (char *)0x80010000;
    D_800A3978 = (char *)0x8001000C;
    D_800A3A0C = (char *)0x80010AEC;
    D_800A35F4 = (char *)0x8001000C;
    D_800A3604 = (char *)0x80010000;
}

extern u8 D_800A3938;
extern u8 D_800A3808;
extern u8 D_800A337C;
s32 CardCheckStatus(s32 arg0, u8 arg1);

s32 func_80069EB8(void) {
    u8 status;
    u8 formatResult;
    u8 result;

    status = CardCheckStatus(D_800A337C, 0);
    D_800A3938 = status;
    if (status == 1) {
        result = 1;
    } else if (status == 2) {
        result = 2;
    } else {
        formatResult = CardFormat(D_800A337C);
        if (formatResult != 0) {
            D_800A3808 = 0;
            return 1;
        }
        result = 4;
    }
    D_800A3808 = result;
    return 0;
}

#ifdef NON_MATCHING
s32 func_80069F30(void) {
    u8 slot;
    u8 status;

    slot = D_800A337C;
    D_800A3808 = 0;
    if (slot == 0xFF) {
        slot = 0;
    } else {
        slot = slot;
    }
    status = CardCheckStatus(slot, 0);
    D_800A3938 = status;
    if (status == 1) {
        D_800A3808 = 1;
        return 0;
    }
    if (status == 2) {
        if (D_800A337C == 0xFF) {
            status = CardCheckStatus(1, 0);
            D_800A3938 = status;
        }
        switch (D_800A3938) {
        case 1:
            D_800A3808 = 1;
            return 0;
        case 0:
        case 3:
            D_800A337C = 1;
            break;
        case 2:
            D_800A3808 = 2;
            return 0;
        }
    } else {
        D_800A337C = slot;
    }
    status = func_80059F0C(D_800A337C);
    D_800A3938 = status;
    if (status == 2) {
        D_800A3808 = 2;
        return 0;
    }
    if (status == 1) {
        D_800A3808 = 3;
        return 0;
    }
    if (status != 3) {
        return 1;
    }
    D_800A3808 = 0xD;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80069F30);
#endif

extern u8 D_800A3938;
extern u8 D_800A3808;
extern u8 D_800A337C;
s32 CardCheckStatus(s32 arg0, u8 arg1);

s32 func_8006A080(void) {
    s32 count;
    s32 i;
    s8 result;
    s32 status;

    count = 0;
    i = 0;
    do {
        result = CardCheckStatus((u8)i, 0);
        D_800A3938 = result;
        status = result & 0xFF;
        if (status == 1) {
            D_800A3808 = status;
            return 0;
        }
        if (status != 2) {
            count++;
            D_800A337C = i;
        }
        i++;
    } while ((u8)i < 2);
    if ((count & 0xFF) == 2) {
        D_800A337C = 0;
    }
    D_800A3808 = 0;
    return count & 0xFF;
}

extern u8 D_800A337C;
extern char D_8008FC60[];
extern s32 CardCountOtherFileBlocks(s32, char *);
u8 CardGetOtherFileBlocks(void) {
    return CardCountOtherFileBlocks(D_800A337C, D_8008FC60);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8006A15C);

INCLUDE_ASM("asm/nonmatchings/game", func_8006A3E0);

INCLUDE_ASM("asm/nonmatchings/game", func_8006A7C8);

#ifdef NON_MATCHING
/*
 * w9h draft: memory-card save open (find/open/close, three section
 * scans). New untracked block-scope externs D_800A3380/3384/3388/338C
 * (path prefix halves) - recheck the map at the gate.
 */
s32 func_8006AA70(void) {
    extern s32 func_8005A0F0(void *, s32, s32, u8, void *);
    extern s32 D_800A3380;
    extern s16 D_800A3384;
    extern s32 D_800A3388;
    extern s16 D_800A338C;
    char path[0x40];
    struct DIRENTRY entry;
    s32 handle;
    s32 fd;
    s32 ret;

    D_800A3808 = 0;
    if (D_800A337C == 0) {
        *(s32 *)path = D_800A3380;
        *(s16 *)(path + 4) = D_800A3384;
    } else {
        *(s32 *)path = D_800A3388;
        *(s16 *)(path + 4) = D_800A338C;
    }
    strcat(path, D_8008FC60);
    handle = 0;
    if ((CardFindFirstFile(path, &entry) & 0xFF) == 0) {
        fd = CardOpenFile(path, 0x200);
        if (fd == -1) {
            D_800A3808 = 5;
            return 0;
        }
        CardCloseFile(fd);
        handle = 1;
        if ((CardFindFirstFile(path, &entry) & 0xFF) == 0) {
            D_800A3808 = 0xA;
            return 0;
        }
    }
    if (handle != 0) {
        if ((func_8005A0F0(&entry, 0, 4, D_800A337C, D_8009B1E4) & 0xFF) == 0) {
            D_800A3808 = 8;
            return 0;
        }
    }
    if ((func_8005A0F0(&entry, 4, 0x16, D_800A337C, (void *)D_800A3604) &
         0xFF) == 0) {
        D_800A3808 = 8;
        return 0;
    }
    if (handle == 0) {
        return 1;
    }
    *(s32 *)D_800A3A0C = 0;
    *(u8 *)(D_800A3A0C + 4) = 0;
    *(u8 *)(D_800A3A0C + 0x14) = 0;
    *(u8 *)(D_800A3A0C + 0x34) = 0;
    if ((func_8005A0F0(&entry, 0x1A, 3, D_800A337C, (void *)D_800A3A0C) &
         0xFF) == 0) {
        D_800A3808 = 8;
        return 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006AA70);
#endif

#ifdef NON_MATCHING
/* Draft is structurally close but gcc anchors the store base differently:
 * retail keeps v1 = record base with positive offsets (0, 0x19, 0x1C-0x1F,
 * sw -1 at 0x20) and v0 = v1+3 for the descending 0x20 byte fill; our gcc
 * merges base/p into one register and re-anchors at +0x20 with negative
 * offsets. Tried: recomputed p, running p, k-before-q order. */
extern char *D_800A35F4;
extern u8 D_800A3A58;
void func_8006ABF8(void) {
    char *p;
    char *q;
    s32 i;
    s32 j;
    s32 k;

    i = 0;
    do {
        p = D_800A35F4 + i * 0xE8;
        j = 0;
        do {
            p[0] = 0;
            p[0x19] = 0;
            k = 3;
            q = p + 3;
            p[0x1C] = 0;
            p[0x1D] = 0;
            p[0x1E] = 0;
            p[0x1F] = 0;
            *(s32 *)&p[0x20] = -1;
            do {
                q[0x24] = 0x20;
                k--;
                q--;
            } while (k >= 0);
            j += 0xC;
            p += 0xC;
        } while (j < 0xCC);
        i++;
    } while (i < 0xC);
    D_800A3A58 = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006ABF8);
#endif

#ifdef NON_MATCHING
/*
 * w7h: structurally close; gcc 2.7.2 hoists BOTH lui-addressed bases into
 * callee-saved regs (walk table -> s0, string base -> s4, frame grows 4),
 * retail recomputes both per iteration (lui a0 in-loop, addu in the jal
 * delay slot). Single-use expressions do not block the loop-invariant
 * hoist. Register map otherwise: retail s0=index s1=walk s2=mask s3=mask*0x18.
 */
extern char *D_8009AC1C[];
extern char D_800BB9B4[];
void func_8006AC78(s32 arg0) {
    char **walk;
    s32 mask;
    s8 index;

    index = 0;
    mask = arg0 & 0xFF;
    walk = D_8009AC1C;
    do {
        if (strcmp(D_800BB9B4 + mask * 0x18, *walk) == 0) {
            D_800A36E0[mask] = index;
            return;
        }
        index += 1;
        walk += 1;
    } while (index < 0x18);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006AC78);
#endif

extern u8 D_8009AD40[];
u8 func_8006AD0C(u8 value) {
    s32 i;
    for (i = 0; i < 0x18; i++) {
        if (value == D_8009AD40[i])
            return i;
    }
}

/* Memory card menu state. */

extern char *D_800A35F4;
extern u8 D_800A3A58;

s32 func_8006AD44(char *name) {
    s32 i;

    if (D_800A3A58 == 0) {
        return 0xFF;
    }
    i = 0;
    while (i < D_800A3A58) {
        if (strcmp(name, D_800A35F4 + i * 0xE8) == 0) {
            return i & 0xFF;
        }
        i++;
    }
    return 0xFF;
}

extern u8 D_800A3068w17[] asm("D_800A3068.NON_MATCHING");
extern u8 D_800A3069w17[] asm("D_800A3069.NON_MATCHING");
extern u8 D_800A3A24w17[] asm("D_800A3A24.NON_MATCHING");
extern u8 D_800A307Cw17[] asm("D_800A307C.NON_MATCHING");
extern u8 D_800BBA24w17[] asm("D_800BBA24.NON_MATCHING");

void func_8006ADC4(u8 arg0, char *arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5,
                   u8 arg6, u8 arg7) {
    typedef struct {
        s32 words[0x3A];
    } SaveEntry;

    register s32 count asm("$6");
    register s32 iv asm("$9");
    register s32 j asm("$10");
    register s32 k asm("$2");
    register s32 i asm("t2");
    register s32 one asm("t1");
    u32 d3;
    u32 lt5;
    u32 lt10;
    u32 d7;
    u32 lt11;
    u32 table;
    u32 d0;
    u32 d0x16;
    register s32 off asm("t0");
    u8 *rec;
    u8 *src;
    register u32 sum asm("$2");
    s32 jj;

    if (D_800A3A58 != 0) {
        count = D_800A3A58 - 1;
        if (D_800A3A58 == 0xC) {
            count = 10;
        } else {
            D_800A3A58 = D_800A3A58 + 1;
        }
        j = count;
        asm("" : "=r"(j) : "0"(j));
        if (j >= 0) {
            k = j * 29;
            iv = k << 3;
            do {
                *(SaveEntry *)(iv + (u32)D_800A35F4 + 0xE8) =
                    *(SaveEntry *)(iv + (u32)D_800A35F4);
                j--;
                iv -= 0xE8;
            } while (j >= 0);
        }
    } else {
        D_800A3A58 = D_800A3A58 + 1;
    }

    strcpy(D_800A35F4, arg1);

    i = 0;
    one = 1;
    d3 = arg3;
    lt5 = d3 < 5;
    lt10 = d3 < 10;
    d7 = arg7;
    lt11 = d7 < 11;
    table = (u32)D_800BBA24w17;
    D_800A35F4[0x19] = D_800A3068w17[arg0 * 2] | (D_800A3069w17[arg0 * 2] << 1);
    d0 = arg0;
    d0x16 = d0 << 4;
    off = 0x1C;

    do {
        rec = D_800A35F4 + off;
        if (i == arg2) {
            if (arg5 == 0) {
                if ((d3 = d3) == 0 && arg6 == 0) {
                    rec[1] = one;
                } else {
                    rec[1] = 0;
                }
                if (d7 == 2) {
                    rec[2] = 0;
                    rec[3] = 0;
                } else {
                    if (lt5 != 0) {
                        rec[2] = one;
                    } else {
                        rec[2] = 0;
                    }
                    if ((lt10 = lt10) != 0 && lt11 == 0) {
                        rec[3] = one;
                    } else {
                        rec[3] = 0;
                    }
                }
                rec[0] = one;
            } else {
                rec[0] = 0;
                rec[1] = 0;
                rec[2] = 0;
                rec[3] = 0;
            }
            *(s32 *)(rec + 4) = arg4;
        } else {
            rec[0] = 0;
            rec[1] = 0;
            rec[2] = 0;
            rec[3] = 0;
            *(s32 *)(rec + 4) = 0x7FFFFFFF;
        }
        jj = 0;
        asm volatile("addu %0, %1, %2\n\tsll %0, %0, 2\n\taddu %0, %0, %3"
                     : "=r"(sum)
                     : "r"(d0x16), "r"(d0), "r"(table));
        src = (u8 *)(i * 4 + sum);
        for (jj = 0; jj < 4; jj++) {
            *(rec + jj + 8) = src[jj];
        }
        i++;
        off += 0xC;
    } while (i < 17);

    D_800A35F4[0x1A] = D_800A3A24w17[arg0];
    D_800A35F4[0x1B] = D_800A307Cw17[arg0];
}

#ifdef NON_MATCHING
/*
 * w9h draft: delete entry idx by shifting later 0xE8-byte records down
 * one slot through a 0xE8 stack buffer. Leaf, frame == buffer.
 */
void func_8006B088(s32 arg0) {
    s32 buf[0x3A];
    s32 count;
    s32 n;
    char *src;
    char *dst;
    char *end;
    s32 i;

    count = arg0 & 0xFF;
    if (count == 0) {
        return;
    }
    src = D_800A35F4 + count * 0xE8;
    dst = (char *)buf;
    end = src + 0xE0;
    do {
        ((s32 *)dst)[0] = ((s32 *)src)[0];
        ((s32 *)dst)[1] = ((s32 *)src)[1];
        ((s32 *)dst)[2] = ((s32 *)src)[2];
        ((s32 *)dst)[3] = ((s32 *)src)[3];
        src += 0x10;
        dst += 0x10;
    } while (src != end);
    ((s32 *)dst)[0] = ((s32 *)src)[0];
    ((s32 *)dst)[1] = ((s32 *)src)[1];
    n = (arg0 & 0xFF) - 1;
    if (n >= 0) {
        i = n * 0xE8;
        do {
            src = D_800A35F4 + i;
            dst = src + 0xE8;
            end = src + 0xE0;
            do {
                ((s32 *)dst)[0] = ((s32 *)src)[0];
                ((s32 *)dst)[1] = ((s32 *)src)[1];
                ((s32 *)dst)[2] = ((s32 *)src)[2];
                ((s32 *)dst)[3] = ((s32 *)src)[3];
                src += 0x10;
                dst += 0x10;
            } while (src != end);
            ((s32 *)dst)[0] = ((s32 *)src)[0];
            ((s32 *)dst)[1] = ((s32 *)src)[1];
            n -= 1;
            i -= 0xE8;
        } while (n >= 0);
    }
    src = (char *)buf;
    dst = D_800A35F4;
    end = (char *)buf + 0xE0;
    do {
        ((s32 *)dst)[0] = ((s32 *)src)[0];
        ((s32 *)dst)[1] = ((s32 *)src)[1];
        ((s32 *)dst)[2] = ((s32 *)src)[2];
        ((s32 *)dst)[3] = ((s32 *)src)[3];
        src += 0x10;
        dst += 0x10;
    } while (src != end);
    ((s32 *)dst)[0] = ((s32 *)src)[0];
    ((s32 *)dst)[1] = ((s32 *)src)[1];
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006B088);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8006B1CC);

extern u8 D_800BBA24[];
void func_8006B3E0(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    u8 *tbl;
    u8 *src;
    u8 *walk;
    u8 *dst;
    u8 *q;
    s32 off;
    s32 mask2;
    i = 0;
    mask2 = arg2 & 0xFF;
    arg0 &= 0xFF;
    tbl = D_800BBA24;
    src = tbl + arg0 * 0x44;
    arg1 &= 0xFF;
    walk = (u8 *)D_800A35F4 + arg1 * 0xE8;
    off = mask2 * 0xC;
    off += 0x1C;
    dst = walk + off;
    do {
        q = dst + i;
        q[8] = *(src + mask2 * 4 + i);
        i += 1;
    } while (i < 4);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8006B464);

/*
 * Retail re-reads the D_800A3604 pointer (gp) before every
 * store, so the pointer variable is volatile here. The D_800A306C-3072/75
 * bytes are untracked; reached as D_800A3073[-N]/[+2] (already declared
 * in this TU).
 */
extern u8 *volatile D_800A3604Vol asm("D_800A3604.NON_MATCHING");
extern u8 D_800A3073[];
extern u8 D_800A3078[];
extern u16 D_800A3694Absolute[];
extern s32 D_800A37D0[];

void func_8006B5BC(void) {
    s32 i;

    D_800A3604Vol[0] = D_800A3073[-3] << 7 | D_800A3073[-7] << 6 |
                       D_800A3073[-6] << 5 | D_800A3073[-4] << 2 |
                       D_800A3073[-5];
    D_800A3604Vol[0xB] =
        D_800A3073[2] << 2 | D_800A3073[-1] << 1 | D_800A3073[-2] & 1;
    D_800A3604Vol[1] = D_800A3694Absolute[0];
    D_800A3604Vol[2] = D_800A3694Absolute[1];
    D_800A3604Vol[3] = D_800A3078[0];
    for (i = 0; i < 6; i++) {
        (D_800A3604Vol + i)[4] = D_800A331CAbsolute[i];
    }
    D_800A3604Vol[0xA] = D_800A37D0[0];
}

INCLUDE_ASM("asm/nonmatchings/game", func_8006B6B8);

#ifdef NON_MATCHING
/*
 * w8h: 8 bytes long and register-shuffled. Retail keeps ONE induction
 * variable (a0 = entry base, +0xc in the bnez delay slot) with positive
 * store offsets 4/6/8; our gcc creates a SECOND IV anchored at entry+8
 * (`addiu a0,a1,8` + in-body `addiu a0,a0,0xc`) with stores -4/-2/0.
 * Tried: k-first order, running base local, sw through byte+5 alias --
 * all re-anchor (same family as func_8006ABF8's base/p merge).
 * Register shuffle: retail a1=counter both loops, a0=base; ours v1/a2
 * counter, a1 base. Constants land a2/a3/t0 in retail, t0/t1/a3 here.
 */
extern u8 D_800B9B6E[];
extern u8 D_800B9B6F[];
extern u8 D_800B9B70[];
extern u8 D_800B9B71[];
extern u8 D_800B9B72[];
extern u8 D_800B9BB4[];
void func_8006BD68(void);
void func_8006BA68(void) {
    u8 *base;
    u8 *entry;
    u8 *byte;
    s32 i;
    s32 j;
    s32 k;
    s32 ffff;
    s32 fill;
    s32 magic;

    func_8006BD68();
    i = 0x17;
    base = D_800B9B6E;
    entry = base + 0x44;
    base[0] = 0;
    D_800B9B6F[0] = 0;
    D_800B9B70[0] = 0;
    D_800B9B71[0] = 0;
    D_800B9B72[0] = 0;
    do {
        *(s16 *)entry = 0;
        i -= 1;
        entry -= 2;
    } while (i >= 0);
    ffff = 0xFF;
    fill = 0x20;
    magic = 0x7FFFFFFF;
    j = 0;
    entry = D_800B9BB4;
    do {
        k = 3;
        byte = entry + 3;
        *(s16 *)(entry + 4) = ffff;
        *(s16 *)(entry + 6) = ffff;
        *(s32 *)(entry + 8) = magic;
        do {
            *byte = fill;
            k -= 1;
            byte -= 1;
        } while (k >= 0);
        j += 1;
        entry += 0xC;
    } while (j < 0x11);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006BA68);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8006BB1C);

extern char *strcpy(char *, const char *);

void func_8006BD68(void) {
    u8 *dest;
    u8 *rec;
    s32 i;
    s32 srcRow;
    s32 dstRow;
    s32 dst;
    s32 src;
    s32 end;
    extern char *D_8009A31CStr[] asm("D_8009A31C.NON_MATCHING");
    extern char *D_8009AC1C[];
    extern u8 D_800A305B[];
    extern u8 D_800A305BR[] asm("D_800A305B.NON_MATCHING");
    extern u8 D_800A36E0[];
    extern u8 D_800A36E1[];
    extern u8 D_800A3068[];
    extern u8 D_800A3069[];
    extern u8 D_800A306CR[] asm("D_800A306C.NON_MATCHING");
    extern u8 D_800A306D[];
    extern u8 D_800A306ER[] asm("D_800A306E.NON_MATCHING");
    extern u8 D_800A306FR[] asm("D_800A306F.NON_MATCHING");
    extern u8 D_800A3070R[] asm("D_800A3070.NON_MATCHING");
    extern u8 D_800A3071R[] asm("D_800A3071.NON_MATCHING");
    extern u8 D_800A3072R[] asm("D_800A3072.NON_MATCHING");
    extern u8 D_800A3075[];
    extern u8 D_800A3078[];
    extern u8 D_800A307C[];
    extern u16 D_800A3694R[] asm("D_800A3694.NON_MATCHING");
    extern u16 D_800A3696[];
    extern s32 D_800A37D0[];
    extern u8 D_800A331C[];
    extern u8 D_800B9B44[];
    extern u8 D_800B9B73[];
    extern u8 D_800B9B74[];
    extern u8 D_800B9B75[];
    extern u8 D_800B9B76[];
    extern u8 D_800B9B77[];
    extern u8 D_800B9B78[];
    extern u8 D_800B9B79[];
    extern u8 D_800B9B7F[];
    extern u8 D_800B9B80[];
    extern u8 D_800B9B81[];
    extern u8 D_800B9B82[];
    extern u8 D_800BBA24[];

    dest = D_800B9B44;
    strcpy((char *)dest, D_8009A31CStr[D_800A305B[0]]);
    strcpy((char *)dest + 0x10, D_8009AC1C[D_800A36E0[0]]);
    D_800B9B73[0] = D_800A36E1[-1];
    D_800B9B74[0] = D_800A305BR[0];
    D_800B9B75[0] =
        D_800A306ER[0] |
        (D_800A3070R[0] << 7 | D_800A306CR[0] << 6 | D_800A306D[0] << 5 |
         D_800A3068[0] << 4 | D_800A3069[0] << 3 | D_800A306FR[0] << 2);
    D_800B9B82[0] =
        D_800A3075[0] << 2 | D_800A3072R[0] << 1 | D_800A3071R[0] & 1;
    D_800B9B76[0] = D_800A3694R[0];
    D_800B9B77[0] = D_800A3696[0];
    D_800B9B78[0] = D_800A3078[0];
    i = 0;
    do {
        D_800B9B79[i] = D_800A331C[i];
        i += 1;
    } while (i < 6);
    i = 0;
    rec = D_800B9B7F;
    rec[0] = D_800A3A24w17[0];
    D_800B9B80[0] = D_800A307C[0];
    D_800B9B81[0] = D_800A37D0[0];
    srcRow = (s32)D_800BBA24;
    dstRow = (s32)rec + 0x35;
    do {
        dst = dstRow;
        src = srcRow;
        end = dstRow + 4;
        do {
            *(u8 *)dst = *(u8 *)src;
            dst += 1;
            src += 1;
        } while (dst < end);
        srcRow += 4;
        dstRow += 0xC;
        i += 1;
    } while (i < 0x11);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8006BF74);

INCLUDE_ASM("asm/nonmatchings/game", func_8006C2D0);

typedef struct ColorNode {
    u8 unk0[5];
    u8 unk5;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 unk12;
    u8 unk14[8];
    struct ColorNode *next;
} ColorNode;
extern ColorNode *D_800A3A10[];
void func_8006C598(s32 low, s32 high, s32 color) {
    ColorNode *node;
    node = D_800A3A10[0];
    while (node != NULL) {
        node->unk5 = color;
        node->unkE = color;
        node->unk6 = node->unk12 + low;
        node->unkA = node->unk12 + high;
        node = node->next;
    }
}

#ifdef NON_MATCHING
/*
 * w7h: size-exact (0x84) draft; prologue matches incl. the early
 * lui/lw of D_800A3A10 BEFORE addiu sp (put the obj read first).
 * Remaining: store/load order only -- retail reloads *entry after the
 * sll/sra return extension and keeps the second D_800A3A10 lui/lw
 * before the srl/addu/sra divide; ours sinks the reload after it.
 * NOTE: plain asm(""); at this spot makes maspsx emit two hazard nops
 * (+8 bytes) -- do not use it as an order barrier here.
 */
extern s32 D_8009A4C0[];
void func_8006C5E4(s32 arg0) {
    s32 *entry;
    u8 *obj;
    s32 value;

    obj = *(u8 **)((u8 *)D_800A3A10[0] + 0x20);
    entry = &D_8009A4C0[arg0 & 0xFF];
    value = func_8005A8E0(*entry);
    value = (0x78 - value) / 2;
    *(s32 *)(obj + 8) = *entry;
    *(u16 *)((u8 *)D_800A3A10[0] + 0x12) = value;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006C5E4);
#endif

#ifdef NON_MATCHING
/*
 * w8h: retail stores the table ADDRESS as a running pointer (v1 =
 * D_800B0A2C + index*0x10, advanced 0x10 per iteration; sw v1,8(v0)) --
 * the old draft's per-iteration load was wrong; fixed here. Still 4
 * bytes short: retail has two delay-slot moves ours does not --
 * (1) `move v1,a0` in the clamp bnez delay (raw arg0 saved, converted
 * to (s8) AFTER the node load; gcc CSEs the two (s8)arg0 conversions
 * and converts early instead) and (2) `move v1,v0` after the sentinel
 * beq (sentinel loaded in v0, copied to v1 for the second loop's bne;
 * ours loads it into v1 and needs no copy). asm("") between the node
 * load and the conversion did not force (1). Register shuffle r-rows
 * otherwise clean.
 */
extern u8 *D_800A3908[];
extern u8 *D_800A377C[];

extern char D_800B0A2C[];
void func_8006C668(s32 arg0, s32 arg1) {
    s32 index;
    s32 end;
    u8 *node;
    u8 *sentinel;
    u8 *tbl;
    end = arg1;
    if (end >= 6)
        end = (s8)arg0 + 6;
    node = D_800A3908[0];
    asm("");
    index = (s8)arg0;
    if (end >= index) {
        tbl = D_800B0A2C + index * 0x10;
        do {
            *(u32 *)(*(u8 **)(node + 0x20) + 8) = (u32)tbl;
            node = *(u8 **)(node + 0x1C);
            index++;
            tbl += 0x10;
        } while (end >= index);
    }
    sentinel = D_800A377C[0];
    while (node != sentinel) {
        *(u32 *)(*(u8 **)(node + 0x20) + 8) = 0;
        node = *(u8 **)(node + 0x1C);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006C668);
#endif

#ifdef NON_MATCHING
extern u8 *D_800A377C[];
extern u8 *D_800A3908[];
extern u8 D_800A358C;
extern u8 D_800A3968;
extern char D_800B0A2C[];
s32 func_8006C700(s32 arg0, s32 arg1) {
    s32 result;
    s32 target;
    s32 gear;
    u8 *node;
    u8 *walker;
    u8 *sentinel;
    s32 old;
    s32 start;
    s32 limit;
    s32 i;
    s32 tmp;
    char *src;

    if ((arg1 & 0xFF) != 0) {
        target = D_800A3968;
        if (target == 0xF) {
            target = 0xE;
        }
    } else if (D_800A39E4[0] == 0x28) {
        target = 1;
    } else {
        target = D_800A3968 - 1;
    }

    node = D_800A377C[0];
    gear = *(s8 *)(node + 5);
    result = 1;
    if ((arg0 & 0xFF) != 0) {
        if (gear < 6 && gear < target) {
            old = D_800A358C;
            tmp = *(u16 *)(node + 8);
            old = old + 1;
            tmp = tmp + 9;
            *(u16 *)(node + 8) = tmp;
            D_800A358C = old;
            gear = gear + 1;
        } else if (gear == 6 && D_800A358C < target) {
            old = D_800A358C;
            D_800A358C = old + 1;
            start = old - 5;
            if (target < 6) {
                limit = target;
            } else {
                limit = (s8)start + 6;
            }
            walker = D_800A3908[0];
            i = (s8)start;
            if (limit >= i) {
                src = i * 0x10 + D_800B0A2C;
                do {
                    *(u32 *)(*(u32 *)(walker + 0x20) + 8) = (u32)src;
                    i++;
                    walker = (u8 *)(*(u32 *)(walker + 0x1C));
                    src += 0x10;
                } while (limit >= i);
            }
            sentinel = D_800A377C[0];
            if (walker != sentinel) {
                do {
                    *(u32 *)(*(u32 *)(walker + 0x20) + 8) = 0;
                    walker = (u8 *)(*(u32 *)(walker + 0x1C));
                } while (walker != sentinel);
            }
        } else {
            result = 0;
        }
    } else if (gear > 0) {
        old = D_800A358C;
        tmp = *(u16 *)(node + 8);
        gear = gear - 1;
        old = old - 1;
        tmp = tmp - 9;
        D_800A358C = old;
        *(u16 *)(node + 8) = tmp;
    } else {
        old = D_800A358C;
        if (old != 0) {
            D_800A358C = old - 1;
            start = old - 1;
            if (target < 6) {
                limit = target;
            } else {
                limit = (s8)start + 6;
            }
            walker = D_800A3908[0];
            i = (s8)start;
            if (limit >= i) {
                src = i * 0x10 + D_800B0A2C;
                do {
                    *(u32 *)(*(u32 *)(walker + 0x20) + 8) = (u32)src;
                    i++;
                    walker = (u8 *)(*(u32 *)(walker + 0x1C));
                    src += 0x10;
                } while (limit >= i);
            }
            sentinel = D_800A377C[0];
            if (walker != sentinel) {
                do {
                    *(u32 *)(*(u32 *)(walker + 0x20) + 8) = 0;
                    walker = (u8 *)(*(u32 *)(walker + 0x1C));
                } while (walker != sentinel);
            }
        } else {
            result = 0;
        }
    }
    *(s8 *)(D_800A377C[0] + 5) = gear;
    return result;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006C700);
#endif

#ifdef NON_MATCHING
s32 func_8006C94C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s16 *arg4) {
    extern s32 func_8005AEC8(s32, s32);
    extern s32 func_8005AFF0(s32);
    s32 cur = arg3;
    s32 val;
    s32 ret;

    func_8005A7B8S32(arg0 & 0xFF, arg1 & 0xFF);
    val = arg2 & 0xFF;
    if (*(s8 *)cur == 0) {
        *arg4 = func_8005AFF0(0x20);
        return 0;
    }
    ret = func_8005AEC8(val, cur);
    *arg4 = func_8005AFF0(*(s8 *)(cur + val));
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006C94C);
#endif

extern u8 *D_800A377C[];
void func_8006C9DC(void) {
    *(s16 *)(*(u8 **)(D_800A377C[0] + 0x1C) + 0x1A) = -1;
}

#ifdef NON_MATCHING
/* w8i draft, one segment from matching: gcc merges val/status into s0
 * (move s0,v0 before the first store, addiu s0,v0,-1, gp reload in v0)
 * where retail keeps the byte value in v0 (`sb v0,5` twice) and reloads
 * D_800A358C into v1. AEC8 chain (`*(s8 *)(entry + status)` spelling)
 * and the ptr-local tail are verified byte-exact shapes. */
extern u8 D_800A358C;
extern char D_800B0A2C[];
extern s32 func_8005AEC8(s32, s32);
extern s32 func_8005AFF0(s32);
void func_8006C9F8(void) {
    u8 *obj;
    u8 *ptr;
    s8 *entry;
    s32 status;
    s32 val;

    obj = *(u8 **)(D_800A377C[0] + 0x1C);
    entry = (s8 *)D_800B0A2C + D_800A358C * 0x10;
    *(s16 *)(obj + 0x1A) = 1;
    val = strlen((char *)entry);
    *(u8 *)(obj + 5) = val;
    asm("");
    if ((s8)val >= 0xF) {
        *(u8 *)(obj + 5) = 0xE;
    }
    val = *(u8 *)(obj + 5) - 1;
    *(u8 *)(obj + 5) = val;
    entry = (s8 *)D_800B0A2C + D_800A358C * 0x10;
    func_8005A7B8S32(2, 2);
    status = val;
    status &= 0xFF;
    if (*entry == 0) {
        *(s16 *)(obj + 0x16) = func_8005AFF0(0x20);
        status = 0;
    } else {
        val = func_8005AEC8(status, entry);
        *(s16 *)(obj + 0x16) = func_8005AFF0(*(s8 *)(entry + status));
        status = val;
    }
    ptr = *(u8 **)D_800A377C;
    *(s16 *)(obj + 6) = status + 0xA;
    *(s16 *)(obj + 8) = *(u16 *)(ptr + 8) + 9;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006C9F8);
#endif

void func_8006CB00(void) {
    s32 value;
    value = *(s16 *)(D_800A377C[0] + 0x1A);
    if (value > 0)
        value = -value;
    else if (value == 0)
        value = -255;
    *(s16 *)(D_800A377C[0] + 0x1A) = value;
}

extern u8 *D_800A377C[];
void func_8006CB40(void) {
    s32 value;

    value = *(s16 *)(D_800A377C[0] + 0x1A);
    if (value < 0) {
        value = -value;
    } else if (value == -255) {
        asm("");
        value = 0;
    }
    *(s16 *)(D_800A377C[0] + 0x1A) = value;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8006CB80);

#ifdef NON_MATCHING
/* w8i: body byte-exact except the frame: retail -0x20, ours -0x28 (one
 * phantom 8-byte local slot; s32/u8 status and declaration order tried).
 * Branch sense (`if (*entry == 0)` gives retail's bnez) and entry-as-s8*
 * (PSX gcc chars are unsigned) verified. */
extern char D_800B0A2D[];
void func_8006CE64(void) {
    u8 *obj;
    s8 *entry;
    s32 status;

    D_800B0A2C[D_800A358C * 0x10] = 0x41;
    D_800B0A2D[D_800A358C * 0x10] = 0;
    obj = *(u8 **)(D_800A377C[0] + 0x1C);
    *(u8 *)(obj + 5) = 0;
    entry = (s8 *)D_800B0A2C + D_800A358C * 0x10;
    func_8005A7B8S32(2, 2);
    if (*entry == 0) {
        *(s16 *)(obj + 0x16) = func_8005AFF0(0x20);
        status = 0;
    } else {
        status = func_8005AEC8(0, entry);
        *(s16 *)(obj + 0x16) = func_8005AFF0(*entry);
    }
    *(s16 *)(obj + 6) = status + 0xA;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006CE64);
#endif

extern u8 D_800A358C;
extern u8 D_800A3968;
extern u8 D_800A305B[];

extern char D_800B0A2C[];
extern char *strcpy(char *, const char *);
void func_8006CF38(void) {
    if (D_800A358C < D_800A3968) {
        strcpy(D_800B0A2C + D_800A358C * 16, (char *)D_8009A31C[D_800A305B[0]]);
    }
}

void func_8006CF90(u32 mode) {
    extern u8 D_800A3390[];
    extern s32 func_8005AEC8(u32, void *);
    extern s16 func_8005AFF0(s8);
    u8 *node;
    u8 *st;
    char *entry;
    s8 c;
    s8 t;
    s8 ch;
    u8 idx;
    s32 result;

    node = D_800A377C[0];
    st = *(u8 **)(node + 0x1C);
    mode &= 0xFF;
    if (mode != 0) {
        if (*(s8 *)(st + 5) > 0) {
            *(s8 *)(st + 5) = *(s8 *)(st + 5) - 1;
        }
    } else {
        t = *(s8 *)(st + 5);
        c = t;
        if (t < 14) {
            c = c + 1;
            *(s8 *)(st + 5) = c;
            if (c == strlen(&D_800B0A2C[D_800A358C * 16])) {
                strcat(&D_800B0A2C[D_800A358C * 16], D_800A3390);
            }
        }
    }
    idx = *(u8 *)(st + 5);
    entry = D_800B0A2C + D_800A358C * 16;
    func_8005A7B8S32(2, 2);
    ch = *entry;
    if (ch == 0) {
        *(u16 *)(st + 0x16) = func_8005AFF0(0x20);
        result = 0;
    } else {
        result = func_8005AEC8(idx, entry);
        *(u16 *)(st + 0x16) = func_8005AFF0(*(s8 *)(entry + idx));
    }
    *(u16 *)(st + 6) = result + 10;
}

extern u8 D_800A358C, D_800A3968, D_800A3808;
s32 func_8006D0C0(void) {
    if (D_800A358C < D_800A3968) {
        D_800A3808 = 16;
        return 1;
    } else {
        return 0;
    }
}

extern char D_800B0A2C[];
extern char D_800B9B44[];
extern char *strcpy(char *, const char *);
extern s32 func_8006A3E0(char *, s32, u8);
extern void func_800599E4(void);
extern void func_800598C4(void);
void func_8006D0F0(void) {
    s32 isCurrent;
    isCurrent = D_800A358C < D_800A3968;
    strcpy(D_800B9B44, &D_800B0A2C[D_800A358C * 16]);
    func_800599E4();
    if ((func_8006A3E0(D_800B9B44, isCurrent, D_800A358C) & 0xFF) == 1) {
        D_800A3808 = 0x11;
    }
    func_800598C4();
}

extern u8 D_800A358C;
extern char D_800B0A2C[];
#ifdef NON_MATCHING
/* w9i draft: switch on c gives retail's beqz/beq pair (the `== ||` if
 * form goes branchless sltiu/xori/or); single entry test = the while
 * condition only (an extra `if (i >= 0)` duplicates bltz); found=0 must
 * be the FIRST statement (s0=zero before the base materializes);
 * (s8) casts on an s32 i keep gcc's lazy extends (an s8 i materializes).
 * Remaining wall: gcc hoists only idx*16 into a temp and re-adds the s1
 * base via a per-iteration t0 copy, and puts i in a0 / ' ' in a3 where
 * retail has entry=v1=base+idx*16 hoisted, i in a1, ' ' in a0. */
s32 func_8006D178(void) {
    s32 i;
    s8 c;
    u8 found;

    found = 0;
    i = strlen(&D_800B0A2C[D_800A358C * 0x10]);
    while ((s8)i >= 0 && found == 0) {
        c = ((s8 *)&D_800B0A2C[D_800A358C * 0x10])[(s8)i];
        switch (c) {
        case 0:
        case ' ':
            i--;
            break;
        default:
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    ((s8 *)&D_800B0A2C[D_800A358C * 0x10])[(s8)i + 1] = 0;
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006D178);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8006D258);

#ifdef NON_MATCHING
/* w7i: draft to 0xa4 exact length, 7 rows off: entry order and
 * i/j register naming (target: i in a3 inited FIRST at entry, j in a2;
 * both row-pointer temps outer-loop). src[j + 0x24] keeps the +0x24 in
 * the lbu displacement. */
extern u8 D_800BBA24[];
extern char *D_800A35F4;
void func_8006D424(u8 arg0, u8 arg1) {
    char *src;
    u8 *dst;
    u8 i;
    u8 j;

    for (i = 0; i < 0x11; i++) {
        dst = &D_800BBA24[arg0 * 0x44 + i * 4];
        src = D_800A35F4 + arg1 * 0xE8 + i * 0xC;
        for (j = 0; j < 4; j++) {
            dst[j] = src[j + 0x24];
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006D424);
#endif

extern u8 D_800BBA24_nm[] asm("D_800BBA24.NON_MATCHING");
extern u8 D_800A3068_nm[] asm("D_800A3068.NON_MATCHING");
extern u8 D_800A3069_nm[] asm("D_800A3069.NON_MATCHING");
extern u8 D_800A307C_nm[] asm("D_800A307C.NON_MATCHING");
extern u8 D_800A308C_nm[] asm("D_800A308C.NON_MATCHING");
extern s8 D_800A3A24_nm[] asm("D_800A3A24.NON_MATCHING");
void func_8006D4C8(u8 arg0, u8 arg1) {
    u8 i;
    u8 j;
    u8 *dst2;
    u8 *src;
    u8 *p2;
    s32 dstOff;
    s32 srcOff;
    s32 yv;
    s32 x68;
    s32 basep;

    i = 0;
    basep = (s32)D_800BBA24_nm;
    x68 = arg0 * 0x44;
    do {
        asm("" ::"r"(j));
        j = 0;
        asm volatile("addu %0, %1, %2" : "=r"(dstOff) : "r"(x68), "r"(basep));
        dst2 = (u8 *)(i * 4 + dstOff);
        asm volatile("andi %0, %1, 0xff" : "=r"(yv) : "r"(arg1));
        srcOff = yv * 0xE8;
        do {
            p2 = (u8 *)D_800A35F4;
            src = (u8 *)(srcOff + (s32)p2);
            src += i * 0xC;
            dst2[j] = *(src + j + 0x24);
            j++;
        } while (j < 4);
        i++;
    } while (i < 0x11);
    D_800A3068_nm[arg0 * 2] = ((u8 *)D_800A35F4)[arg1 * 0xE8 + 0x19] & 1;
    D_800A3069_nm[arg0 * 2] = (((u8 *)D_800A35F4)[arg1 * 0xE8 + 0x19] >> 1) & 1;
    if (((u8 *)D_800A35F4)[arg1 * 0xE8 + 0x1A] == D_800A3A24_nm[arg0]) {
        D_800A307C_nm[arg0] = ((u8 *)D_800A35F4)[arg1 * 0xE8 + 0x1B];
        D_800A308C_nm[arg0] = ((u8 *)D_800A3A24_nm)[arg0];
    } else {
        D_800A307C_nm[arg0] = 0;
    }
}

extern u8 D_800BBA24[];
void func_8006D634(s32 arg) {
    u8 *base;
    u8 *tbl;
    u8 i;
    s32 offset;

    i = 0;
    offset = arg & 0xFF;
    tbl = D_800BBA24;
    base = tbl + offset * 4;
    do {
        base[i] = 0x20;
        D_800A3860[0][i] = 0x20;
        i += 1;
    } while (i < 4);
}

#ifdef NON_MATCHING
/* w7i: full shape known; closest draft: src row via
 * &D_800BBA24[arg0 * 4 + i * 0x44], D_800A3860 base materialized FIRST,
 * `move a1,zero` (j init) placed before the row math. */
void func_8006D684(u8 arg0) {
    u8 *dst;
    u8 *src;
    u8 i;
    u8 j;

    for (i = 0; i < 2; i++) {
        dst = D_800A3860[i];
        src = &D_800BBA24[arg0 * 4 + i * 0x44];
        for (j = 0; j < 4; j++) {
            dst[j] = src[j];
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006D684);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8006D708);

INCLUDE_ASM("asm/nonmatchings/game", func_8006D8E8);

extern u8 *D_8009AB00nm[] asm("D_8009AB00.NON_MATCHING");
extern u8 *D_8009AB80nm[] asm("D_8009AB80.NON_MATCHING");
extern void *D_800A3908nm[] asm("D_800A3908.NON_MATCHING");
u8 *func_8005B598(s32 left, s32 top, s32 right, s32 bottom, s32 depth,
                  u8 texture, u8 semiTrans);

void func_8006DA40(void) {
    u8 *node;
    u8 *prev;
    u8 *pkt;
    u8 idx;
    s32 err;
    s32 height;
    s32 i;
    s32 y;

    y = 0x50;
    i = 0;
    do {
        node = func_8005B598(0x64, y, 0x78, 0x18, 9, 1, 0);
        if (i == 0) {
            D_800A3A10[0] = (ColorNode *)node;
        } else {
            *(u8 **)(prev + 0x1C) = node;
        }
        pkt = *(u8 **)(node + 0x20);
        *(s16 *)(node + 0xE) = 2;
        *(s16 *)(node + 0x10) = 0;
        *(s16 *)(node + 0x6) = -0x78;
        switch (i) {
        case 0:
            height = 0;
            break;
        case 1:
            height = 0xC;
            break;
        case 2:
            height = 0x18;
            break;
        }
        func_8005B17C(pkt, 9, 0, height, *(u16 *)(node + 0x16),
                      *(u16 *)(node + 0x18));
        y += *(s16 *)(node + 0x18);
        prev = node;
        i += 1;
    } while (i < 3);
    y = 0x50;
    i = 0;
    do {
        node =
            (u8 *)func_8005B314(0x64, y, 0x78, 0x48, 0, 0x20, 0x20, 0x40, 1, 1);
        *(s16 *)(node + 0x6) = -0x78;
        *(s16 *)(node + 0xE) = 2;
        *(s16 *)(node + 0x1A) = 0xA;
        *(u8 **)(prev + 0x1C) = node;
        prev = node;
        i += 1;
    } while (i < 2);
    node = (u8 *)func_8005BF8C(0x71, 0x55);
    err = D_800A3808;
    *(s16 *)(node + 0x1A) = 2;
    if (err == 2) {
        idx = 0x1B;
    } else if (err == 0x1C) {
        idx = 0x1C;
        if (D_800A337C == 1) {
            asm("");
            idx = 0x1D;
        }
    } else if (err == 0xD) {
        idx = 0x19;
        if (D_800A337C == 1) {
            idx = 0x1A;
        }
    }
    if (D_800A3A24_nm[0] == 2) {
        func_80067EA4((UnkObject24 *)node, 2, 2, (s32)D_8009AB80nm[idx], 0,
                      *(s16 *)(node + 0x1A));
    } else {
        func_80067EA4((UnkObject24 *)node, 2, 2, (s32)D_8009AB00nm[idx], 0,
                      *(s16 *)(node + 0x1A));
    }
    *(s16 *)(node + 0xE) = 2;
    *(s16 *)(node + 0x12) = 0xB;
    *(s16 *)(node + 0x6) = -0x6B;
    D_800A3908nm[0] = node;
    *(u8 **)(prev + 0x1C) = node;
}

extern ColorNode *D_800A3A10[];
extern void func_8005B8B8(u8 *first, s32 value);
void func_8006DCF0(void) {
    func_8005B688(D_800A3A10[0], 1);
    func_8005B8B8(((void **)D_800A3A3C)[-11], 0xFF);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8006DD28);

extern u8 D_800AEE3C[];

void func_8006DE68(u32 arg0, u32 mode) {
    if ((mode & 0xFF) == 2) {
        s32 i;
        s32 j;
        s32 m;
        s32 pos;
        s32 end;

        i = 0;
        j = 2;
        m = (u8)arg0;
        pos = m << 3;
        pos += m;
        end = pos + 6;
        do {
            if (i == j) {
                D_800AEE3C[end] = 0x78;
                D_800AEE3C[end + 1] = 0x80;
                D_800AEE3C[end + 2] = 0x88;
            } else {
                D_800AEE3C[pos] = 0;
                D_800AEE3C[pos + 1] = 8;
                D_800AEE3C[pos + 2] = 0;
            }
            i++;
            pos += 3;
        } while (i < 3);
    } else {
        s32 n;
        s32 pos;

        n = (u8)arg0;
        pos = n << 3;
        pos += n;
        D_800AEE3C[pos] = 0x80;
        D_800AEE3C[pos + 1] = 0x78;
        D_800AEE3C[pos + 2] = 0x80;
        D_800AEE3C[pos + 3] = 0x80;
        D_800AEE3C[pos + 4] = 0x88;
        D_800AEE3C[pos + 5] = 0x80;
        D_800AEE3C[pos + 6] = 0x78;
        D_800AEE3C[pos + 7] = 0x88;
        D_800AEE3C[pos + 8] = 0x80;
    }
}

#ifdef NON_MATCHING
/* w9i draft: dispatch structure is EXACT (switch on mode with cases in
0,1,2 source order gives retail's middle-value-first beq a1,1 dispatch;
the a1<2 slti tree; per-case j-to-epilogue with shared 0x3C6/0x3C7 lbu
sites). result/extra locals give the pre-dispatch `li 1` and the raw
arg3 copy. Remaining wall: retail keeps `result` in v0 (ori v0,1 at
top, lbu v0 at every case tail, bare jr) while gcc pins it to v1 with
the 1-load in the first branch's delay slot; statement order, init
order and declaration order all leave it there. */
u8 func_8006DF98(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 mode;
    s32 extra;
    u8 result;

    mode = arg1;
    extra = arg3;
    result = 1;
    switch (mode) {
    case 0:
        if ((u8)arg2 != 2) {
            result = ((u8 *)arg0)[0x3C6];
        } else if ((u8)extra == 0 || (u8)extra == (u8)arg2) {
            result = ((u8 *)arg0)[0x3C7];
        } else {
            result = ((u8 *)arg0)[0x3C6];
        }
        break;
    case 1:
        if ((u8)arg2 != 2) {
            result = ((u8 *)arg0)[0x3C6];
        } else if ((u8)extra != 0 && (u8)extra != (u8)arg2) {
            result = ((u8 *)arg0)[0x3C7];
        } else {
            result = ((u8 *)arg0)[0x3C6];
        }
        break;
    case 2:
        if ((u8)arg2 == mode && (u8)((u8)extra - 2) < 2) {
            result = ~((u8 *)arg0)[0x3C5];
        } else {
            result = ((u8 *)arg0)[0x3C5];
        }
        break;
    }
    return result;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8006DF98);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8006E07C);

INCLUDE_ASM("asm/nonmatchings/game", func_8006E484);

INCLUDE_ASM("asm/nonmatchings/game", func_8006E628);

INCLUDE_ASM("asm/nonmatchings/game", func_8006E770);
INCLUDE_RODATA("asm/nonmatchings/game", D_8008FCA4);

INCLUDE_ASM("asm/nonmatchings/game", func_8006EB18);

extern u8 D_800AD984[];
void func_8006EEBC(void) {
    s32 i;
    u8 *ptr;
    i = 16;
    ptr = D_800AD984;
    do {
        *ptr = 0;
        i--;
        ptr--;
    } while (i >= 0);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8006EEE0);

void func_8006F128(s32 arg0) {
    s32 pad[6];

    if (D_800A2F9CAbsolute[0] != 0) {
        func_8003CCE0(0);
        ((u8 *)D_800A2F9DAbsolute)[-1] = 0;
    }
    func_8006F9C4((arg0 & 0xFF) + 0x3A, 0, 0);
    func_800596F4();
    CdSetMixVolume(((u8 *)D_800A3694Absolute)[0]);
}

extern u8 D_800A2F9CAbsolute[];
extern u8 D_800A2F9DAbsolute[];
extern u8 D_800A3694AbsoluteU8[] asm("D_800A3694Absolute");
extern void func_8003CCE0(s32);
extern s32 func_8006F9C4(s32, s32, s32);
extern void func_800596F4(void);
void func_8006F194(s32 arg) {
    if (D_800A2F9CAbsolute[0] != 0) {
        func_8003CCE0(0);
        ((u8 *)D_800A2F9DAbsolute)[-1] = 0;
    }
    func_8006F9C4((arg & 0xFF) + 0xC, 0, 0);
    func_800596F4();
    CdSetMixVolume(D_800A3694AbsoluteU8[0]);
}

extern s32 D_800A3904w16 asm("D_800A3904.NON_MATCHING");
extern u8 *func_800719FC(s32 *);
extern void func_800718D4(s32);
extern void func_80072750(void);
extern void func_80072A34(void);
extern s32 func_80072A5C(void);
extern s32 func_80072AFC(u32);
extern void func_80072CA8(u8 *);
extern void func_80073100(u8 *);
extern void func_80070750(s32);
extern void func_8007005C(void);
extern void func_80070018Args(u8 *, s32, s32);
asm(".globl func_80070018Args\nfunc_80070018Args = func_80070018");
extern void func_80041AF0Arg(s32);
asm(".globl func_80041AF0Arg\nfunc_80041AF0Arg = func_80041AF0");

s32 func_8006F200(s32 arg0, s32 arg1, u32 arg2) {
    s32 block;
    u8 *p;
    u32 w0;
    u32 w1;
    u32 magic;
    u32 size;
    s32 status;
    u32 idx;
    u32 limit;
    s32 result;
    u32 i;

    block = arg2;
    func_800719FC(&block);
    i = 0;
    result = 1;
    D_800A3904w16 = 0;
    while (1) {
        if (i >= 4) {
            func_80041AF0Arg(0);
            status = func_80041B7C(0);
            if (status & 0x840) {
                D_800A3904w16 = status;
                result = 0;
                break;
            }
        }
        block = 8;
        p = func_800719FC(&block);
        if (p == 0) {
            goto done;
        }
        if (block == 0) {
            goto done;
        }
        w0 = *(u32 *)p;
        asm("" : "=r"(w0) : "0"(w0));
        w1 = *(u32 *)(p + 4);
        magic = (w0 >> 24) | ((w0 >> 8) & 0xFF00) | ((w0 & 0xFF00) << 8) |
                (w0 << 24);
        size = (w1 >> 24) | ((w1 >> 8) & 0xFF00) | ((w1 & 0xFF00) << 8) |
               (w1 << 24);
        if (size < 0x4400) {
            block = size;
            p = func_800719FC(&block);
            if (p == 0) {
                goto done;
            }
            if (block == 0) {
                goto done;
            }
            switch (magic) {
            case 0x564C4330:
                func_80070750((s32)(p + 8));
                break;
            case 0x41643130:
            case 0x41643131:
            case 0x61643130:
            case 0x61643131:
            case 0x61643230:
            case 0x61643231:
                func_80072CA8(p);
                break;
            case 0x61753030:
            case 0x61753031:
                func_80073100(p);
                break;
            case 0x4D444332:
            case 0x4D444543:
                idx = i;
                asm("" : "=r"(idx) : "0"(idx));
                if (idx == 1) {
                    func_80072750();
                }
                func_80072A34();
                i = idx + 1;
                limit = func_80072AFC(idx);
                func_80070018Args(p, arg0, arg1);
                while ((u32)func_80072A5C() < limit) {
                    VSync(0);
                }
                func_8007005C();
                break;
            default:
                block = 4;
                break;
            }
        } else {
            block = 4;
        }
        func_800718D4(block);
    }
done:
    return result;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8006F4DC);

extern void CD_initvol(void);
extern void SsSetMute(s32);
/* Sound output and video. */

void SoundInitOutput(void) {
    CD_initvol();
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, 0x7FFF, 0x7FFF);
    SsSetMute(0);
}

extern u8 D_800A3394[];
extern u8 D_800A3397;
extern u8 D_800A39BC;
extern s32 func_8006F4DC(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_8006F9C4(s32 arg0, s32 arg1, s32 arg2) {
    volatile s32 pad[14];
    void *handle;

    CD_initvol();
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, 0x7FFF, 0x7FFF);
    SsSetMute(0);
    handle = func_8003C584(arg0, D_800A3394);
    D_800A3397 = (u8)arg1;
    D_800A39BC = (u8)arg2;
    return func_8006F4DC((s32)handle, 1, 0x800, 0, 0xA, 1, 0xC8, 0x400) & 0xFF;
}

extern void SpuSetCommonAttr(SpuCommonAttr *);
void SoundSetMasterVolume(s16 left, s16 right) {
    SpuCommonAttr attr;
    attr.mvol.left = left;
    attr.mask = 3;
    attr.mvol.right = right;
    SpuSetCommonAttr(&attr);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8006FAAC);

INCLUDE_ASM("asm/nonmatchings/game", func_8006FBB0);

extern void DecDCTin(u_long *, s32);
extern void DecDCTout(u_long *, s32);
extern s32 DecDCToutSync(s32);
extern void func_800708D8(void *, s32);
extern s32 *D_800A3398;
extern s32 D_800A339C;
extern s32 D_800A33A0;

void func_8006FDDC(u8 *arg0, s32 arg1, s16 arg2) {
    RECT rect;
    volatile s32 pad[2];
    s32 scaleV;
    u32 word;
    u32 wA;
    s32 magic;
    s32 stride;
    s32 height16;
    s32 output;
    u32 i;
    register s32 prod asm("$10");
    s32 wv;
    s32 hv;
    register s32 *str asm("$6");
    register u32 w8 asm("$7");
    register u32 nsectors16 asm("$18");
    register u32 w8hi asm("$2");
    register u32 xoff9 asm("$9");
    register s32 prodr asm("$10");
    register u32 stride160 asm("$2");
    register s32 sq asm("$3");
    register u32 halfv asm("$2");
    register s32 dbl asm("$2");
    u32 n4;
    s32 xv;
    s32 sx;
    u32 b0;
    u32 b1;

    scaleV = D_800A33A0;
    word = *(u32 *)arg0;
    w8 = *(u16 *)(arg0 + 8);
    asm volatile("mult %0, %1" : : "r"(arg1), "r"(scaleV) : "lo", "hi");
    wA = *(u16 *)(arg0 + 0xA);
    asm volatile("srl %0, %1, 0x18" : "=r"(b0) : "r"(word));
    b1 = (word >> 8) & 0xFF00;
    magic = b0 | b1 | ((word & 0xFF00) << 8) | (word << 0x18);
    asm volatile("");
    rect.y = arg2;
    asm volatile("lw %0, D_800A3398" : "=r"(str));
    height16 = (wA >> 8) | ((wA & 0xFF) << 8);
    asm volatile("srl %0, %1, 8" : "=r"(w8hi) : "r"(w8));
    asm volatile("mflo %0" : "=r"(prodr));
    asm volatile("srl $9, %0, 1" : : "r"(prodr));
    rect.x = xoff9;
    nsectors16 = w8hi | ((w8 & 0xFF) << 8);
    if (str[0x45] != 0) {
        register u32 xsum asm("$2");
        stride160 = D_800A33A0 * 0xA0;
        asm volatile("addu %0, %1, %2"
                     : "=r"(xsum)
                     : "r"(xoff9), "r"(stride160));
        rect.x = xsum;
    }
    rect.w = D_800A33A0 * 8;
    rect.h = height16;
    if (str[0x46] == 0) {
        if (magic == 0x4D444543) {
            func_800708D8(arg0 + 0x10,
                          *(s32 *)((s32)str + str[0xC] * 4 + 0x28));
        }
        D_800A3398[0x47] = 0;
        asm volatile("");
    } else {
        output = str[9];
        DecDCTin((u_long *)*(s32 *)((s32)str + (1 - str[0xC]) * 4 + 0x28),
                 D_800A339C);
        stride = D_800A33A0 * 8;
        asm volatile("mult %1, %2\n\tmflo %0"
                     : "=r"(sq)
                     : "r"(height16), "r"(stride)
                     : "lo", "hi");
        n4 = nsectors16 >> 4;
        asm volatile("srl %0, %1, 1" : "=r"(halfv) : "r"(sq));
        DecDCTout((u_long *)output, halfv * n4);
        if (magic == 0x4D444543) {
            func_800708D8(arg0 + 0x10, *(s32 *)((s32)D_800A3398 +
                                                D_800A3398[0xC] * 4 + 0x28));
        }
        DecDCToutSync(0);
        i = 0;
        if (nsectors16 != 0) {
            do {
                LoadImage(&rect, (u_long *)output);
                wv = rect.w;
                hv = rect.h;
                asm volatile("mult %0, %1" : : "r"(wv), "r"(hv) : "lo", "hi");
                i += 0x10;
                xv = (u16)rect.x + D_800A33A0 * 8;
                asm("mflo %0" : "=r"(prod) : "r"(xv));
                dbl = prod * 2;
                output += dbl;
                rect.x = xv;
            } while (i < nsectors16);
        }
        D_800A3398[0x47] = 1;
    }
    DecDCTReset(1);
    D_800A3398[0x46] = D_800A3398[0x46] + 1;
    D_800A3398[0xC] = 1 - D_800A3398[0xC];
}

extern s32 *D_800A3398;
void func_8006FBB0(void);
extern void func_8006FDDCNoArgs(void);
asm(".globl func_8006FDDCNoArgs\nfunc_8006FDDCNoArgs = func_8006FDDC");
void func_80070018(void) {
    if (D_800A3398[0x12C / 4])
        func_8006FBB0();
    else
        func_8006FDDCNoArgs();
}

extern s32 *D_800A3398;
void func_8007005C(void) {
    s32 *s;
    s32 *s2;
    s32 other;

    if (D_800A3398[0x11C / 4] != 0) {
        DrawSync(0);
        VSync(0);
        s = D_800A3398;
        PutDispEnv((DISPENV *)((u8 *)s + (s[0x114 / 4] * 20 + 0xEC)));
        s2 = D_800A3398;
        other = 1 - s2[0x114 / 4];
        s2[0x114 / 4] = other;
        PutDrawEnv((DRAWENV *)((u8 *)s2 + (other * 92 + 0x34)));
    }
}

extern s32 D_800A339C, D_800A33A0;
void func_800700F8(void) {
    D_800A339C = 1;
    D_800A33A0 = 3;
}

extern s32 D_800A339C, D_800A33A0;
void func_80070110(void) {
    D_800A339C = 2;
    D_800A33A0 = 2;
}

s32 func_80070124(void) {
    return 0x130;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8007012C);

INCLUDE_ASM("asm/nonmatchings/game", func_80070248);

INCLUDE_ASM("asm/nonmatchings/game", func_800703D0);

extern u8 *D_800A33A8;
extern u8 *D_800A33AC;
extern u8 D_8009B800[];
extern void func_80070798(u8 *first, u8 *second, u8 *table);
void func_80070750(s32 arg) {
    if (arg != 0) {
        func_80070798(D_800A33A8, D_800A33AC, (u8 *)arg);
    } else {
        func_80070798(D_800A33A8, D_800A33AC, D_8009B800);
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80070798);

INCLUDE_ASM("asm/nonmatchings/game", func_800708D8);

INCLUDE_ASM("asm/nonmatchings/game", func_80070A60);

INCLUDE_ASM("asm/nonmatchings/game", func_80070F40);

INCLUDE_ASM("asm/nonmatchings/game", func_800710D8);

INCLUDE_ASM("asm/nonmatchings/game", func_800711F0);

#ifdef NON_MATCHING
/* Structure matches; remaining wall is register assignment: retail keeps
 * the node pointer in v1, copies the param to a1 (a0 is clobbered by the
 * 0x444 load), and holds `remaining` in a0. Our gcc packs the three loads
 * into a1/a2/a3 and never emits the param copy, so the encoded registers
 * differ even though the instruction sequence is identical. Tried
 * remaining-first declaration order - no effect. */
extern s32 *D_800A3500;
extern void func_800711F0(void);
void func_800718D4(s32 arg) {
    s32 remaining;
    s32 *stream;
    s32 *node;

    stream = D_800A3500;
    node = (s32 *)stream[0x42C / 4];
    remaining = stream[0x444 / 4];
    node[0x4 / 4] += arg;
    remaining = 0x800 - remaining;
    if (arg < remaining) {
        stream[0x444 / 4] = stream[0x444 / 4] + arg;
    } else {
        arg -= remaining;
        stream[0x444 / 4] = arg & 0x7FF;
        stream[0x440 / 4] = stream[0x440 / 4] + (((u32)arg >> 11) + 1);
    }
    func_800711F0();
    stream = D_800A3500;
    node = (s32 *)stream[0x42C / 4];
    if (node[0x4 / 4] == node[0x10 / 4]) {
        if ((s32 *)stream[0x430 / 4] != node) {
            if (stream[0x444 / 4] != 0) {
                stream[0x440 / 4] += 1;
            }
            node = (s32 *)stream[0x430 / 4];
            stream[0x44C / 4] = 0;
            stream[0x42C / 4] = (s32)node;
            stream[0x444 / 4] = node[0x28 / 4];
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800718D4);
#endif

extern s32 *D_800A3500;
s32 func_800719D4(void) {
    return (D_800A3500[0x448 / 4] << 11) -
           ((D_800A3500[0x440 / 4] << 11) + D_800A3500[0x444 / 4]);
}

INCLUDE_ASM("asm/nonmatchings/game", func_800719FC);

INCLUDE_ASM("asm/nonmatchings/game", func_80071BE8);

INCLUDE_ASM("asm/nonmatchings/game", func_80071DCC);

extern s32 D_800A3510;
extern s32 D_800A3514;
extern s32 D_800A3518;
s32 func_80071EC0(s32 index, s32 base, s32 item) {
    D_800A3510 = index;
    index <<= 11;
    index += 0x57C;
    D_800A3514 = base;
    base += index;
    D_800A3518 = item;
    return base + item * 56;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80071EEC);

extern s32 D_800A33B8, D_800A33BC;
void func_800720D0(void) {
    s32 enabled;
    s32 pad[2];

    if (D_800A3500[0x420 / 4] != 0) {
        CdDataCallback((void *)D_800A3500[0x574 / 4]);
        CdReadCallback((void *)D_800A3500[0x578 / 4]);
        SwEnterCriticalSection();
        enabled = D_800A3500[0x420 / 4];
        D_800A3500[0x41C / 4] = 0;
        D_800A3500[0x410 / 4] = 0;
        D_800A3500[0x408 / 4] = 0;
        D_800A3500[0x40C / 4] = 0;
        asm("");
        if (enabled != 0) {
            CdSyncCallback((void *)D_800A33B8);
            CdReadyCallback((void *)D_800A33BC);
            D_800A33B8 = 0;
            D_800A33BC = 0;
            D_800A3500[0x420 / 4] = 0;
        }
        SwExitCriticalSection();
    }
}

extern volatile s32 *D_800A351C;
void func_80072178(void) {
    u8 *src;
    s32 value;
    u32 i;
    s32 old;
    s32 base;
    s32 count;

    if (D_800A351C[0x7B48 / 4] == 1) {
        src = (u8 *)D_800A351C[0x7B50 / 4];
        value = D_800A351C[0x7B54 / 4];
        for (i = 0; i < 0x300; i += 0x10) {
            src[i + 1] = 2;
        }
        if ((D_800A351C[0x7B44 / 4] & 3) == 0) {
            src[1] = 6;
        } else if (((D_800A351C[0x7B44 / 4] + 1) & 3) == 0) {
            src[0x2F1] = 3;
        }
        D_800A351C[0x7B2C / 4 + (D_800A351C[0x7B44 / 4] & 3)] = value;
        old = D_800A351C[0x7B44 / 4];
        base = D_800A351C[0x7B60 / 4];
        D_800A351C[0x7B44 / 4] = D_800A351C[0x7B44 / 4] + 1;
        count = D_800A351C[0x7B44 / 4];
        base += (old & 3) * 0x300;
        SpuSetTransferMode(0);
        SpuSetTransferStartAddr(base);
        SpuWrite(src, 0x300);
        D_800A351C[0x7B48 / 4] = 2;
    } else if (D_800A351C[0x7B48 / 4] == 2) {
        volatile s32 *spu;
        spu = D_800A351C;
        spu[0x7B48 / 4] = 0;
        if (spu[0x7B4C / 4] != 0) {
            spu[0] += 0x300;
            spu[0x7B4C / 4] = 0;
        }
    }
}

extern volatile s32 *D_800A351C;
extern void SpuSetIRQ(s32);
extern void SpuSetIRQAddr(s32);
extern void SpuSetTransferStartAddr(s32);
void func_800722D0(void) {
    u8 *src;
    s32 addr;
    s32 addr2;
    u32 value;
    u32 i;
    s32 mode;
    s32 result;
    s32 base;
    s32 fallback;

    SpuSetIRQ(0);
    SpuSetIRQCallback(0);
    if (D_800A351C[0x7B48 / 4] == 0 &&
        D_800A351C[0x7B44 / 4] * 2 - D_800A351C[0x7B40 / 4] < 6) {
        u32 size;

        size = 0x300;
        if ((u32)(D_800A351C[1] - D_800A351C[0]) > size &&
            D_800A351C[0x7B78 / 4] == 0) {
            addr =
                (s32)((u8 *)D_800A351C + ((u32)D_800A351C[0] % 0x3C00 + 0x10));
        } else {
            addr = 0;
        }
        src = (u8 *)addr;
        if (src != 0) {
            u32 size;

            size = 0x300;
            if ((u32)(D_800A351C[1] - D_800A351C[0]) > size &&
                D_800A351C[0x7B78 / 4] == 0) {
                addr2 = (s32)((u8 *)D_800A351C +
                              ((u32)D_800A351C[0] % 0x3C00 + 0x3C10));
            } else {
                addr2 = 0;
            }
            D_800A351C[0x7B58 / 4] = 1;
            D_800A351C[0x7B4C / 4] = 1;
            D_800A351C[0x7B48 / 4] = 1;
            D_800A351C[0x7B50 / 4] = addr2;
            D_800A351C[0x7B54 / 4] = D_800A351C[0x7B3C / 4];
            value = D_800A351C[0x7B3C / 4];
            for (i = 0; i < 0x300; i += 0x10) {
                src[i + 1] = 2;
            }
            if ((D_800A351C[0x7B44 / 4] & 3) == 0) {
                src[1] = 6;
            } else if (((D_800A351C[0x7B44 / 4] + 1) & 3) == 0) {
                src[0x2F1] = 3;
            }
            D_800A351C[0x7B2C / 4 + (D_800A351C[0x7B44 / 4] & 3)] = value;
            {
                s32 idx;

                idx = D_800A351C[0x7B44 / 4];
                base = D_800A351C[0x7B5C / 4];
                base += (idx & 3) * 0x300;
                SpuSetTransferMode(0);
                SpuSetTransferStartAddr(base);
                SpuWrite(src, 0x300);
                D_800A351C[0x7B3C / 4] = D_800A351C[0x7B3C / 4] + 0x300;
            }
        } else {
            fallback = (s32)((u8 *)D_800A351C + 0x7810);
            asm("addu %0,%1,$0" : "=r"(src) : "r"(fallback));
            D_800A351C[0x7B58 / 4] = 0;
            D_800A351C[0x7B4C / 4] = 0;
            D_800A351C[0x7B48 / 4] = 1;
            D_800A351C[0x7B50 / 4] = (s32)src;
            D_800A351C[0x7B54 / 4] = 0;
            for (i = 0; i < 0x300; i += 0x10) {
                src[i + 1] = 2;
            }
            if ((D_800A351C[0x7B44 / 4] & 3) == 0) {
                src[1] = 6;
            } else if (((D_800A351C[0x7B44 / 4] + 1) & 3) == 0) {
                src[0x2F1] = 3;
            }
            D_800A351C[0x7B2C / 4 + (D_800A351C[0x7B44 / 4] & 3)] = 0;
            {
                s32 idx;

                idx = D_800A351C[0x7B44 / 4];
                base = D_800A351C[0x7B5C / 4];
                base += (idx & 3) * 0x300;
                SpuSetTransferMode(0);
                SpuSetTransferStartAddr(base);
                SpuWrite(src, 0x300);
            }
        }
    }
    if ((D_800A351C[0x7B40 / 4] & 1) == 0) {
        value = *(u32 *)((u8 *)D_800A351C + 0x7B2C +
                         ((D_800A351C[0x7B40 / 4] * 2) & 0xC));
        if (value != 0) {
            mode = D_800A351C[0x7B74 / 4];
            result = 0;
            if (mode != 0) {
                if (mode == 1) {
                    result =
                        (s32)((long long)((unsigned long long)value * 0x40) /
                              0x3F);
                }
            } else {
                if (D_800A351C[0x7B7C / 4] == 0x800) {
                    result =
                        (s32)((long long)((unsigned long long)value * 0x14D0) /
                              0x1117);
                } else {
                    result =
                        (s32)((long long)((unsigned long long)value * 0x6D440) /
                              0x82BA3);
                }
            }
            D_800A351C[0x7B24 / 4] = result;
        }
    }
    D_800A351C[0x7B40 / 4] = D_800A351C[0x7B40 / 4] + 1;
    D_800A351C[0x7B40 / 4];
    SpuSetIRQAddr(D_800A351C[0x7B5C / 4] +
                  (D_800A351C[0x7B40 / 4] & 7) * 0x180);
    SpuSetIRQCallback(func_800722D0);
    SpuSetIRQ(1);
}

extern volatile s32 *D_800A351C;
s32 func_8007270C(void) {
    s32 result;
    result = D_800A351C[0x7B20 / 4];
    if (result != 0) {
        D_800A351C[0x7B24 / 4] += 0x100;
        D_800A351C[0x7B28 / 4] = D_800A351C[0x7B28 / 4] + 1;
        result = D_800A351C[0x7B28 / 4];
    }
    return result;
}

void func_80072750(void) {
    u8 *src;
    s32 addr;
    s32 addr2;
    register u32 value asm("$2");
    u32 size;
    u32 i;
    u32 j;
    s32 base;

    if (D_800A351C[2] == 0) {
        D_800A351C[0x7B3C / 4] = 0x300;
        for (i = 0; i < 3; i++) {
            size = 0x300;
            if ((u32)(D_800A351C[1] - D_800A351C[0]) > size &&
                D_800A351C[0x7B78 / 4] == 0) {
                u32 x;

                x = (u32)D_800A351C[0];
                asm("lui $2,0x8888\n\t"
                    "ori $2,$2,0x8889\n\t"
                    "multu %0,$2\n\t"
                    "mfhi $6\n\t"
                    "srl $3,$6,0xd\n\t"
                    "sll $2,$3,4\n\t"
                    "subu $2,$2,$3\n\t"
                    "sll $2,$2,0xa\n\t"
                    "subu %0,%0,$2"
                    : "=r"(x)
                    : "0"(x)
                    : "$2", "$3", "$6", "hi", "lo");
                x += 0x10;
                addr = (s32)((u8 *)D_800A351C + x);
            } else {
                addr = 0;
            }
            src = (u8 *)addr;
            if (src != 0) {
                if ((u32)(D_800A351C[1] - D_800A351C[0]) > size &&
                    D_800A351C[0x7B78 / 4] == 0) {
                    u32 x;

                    x = (u32)D_800A351C[0];
                    asm("lui $2,0x8888\n\t"
                        "ori $2,$2,0x8889\n\t"
                        "multu %0,$2\n\t"
                        "mfhi $6\n\t"
                        "srl $3,$6,0xd\n\t"
                        "sll $2,$3,4\n\t"
                        "subu $2,$2,$3\n\t"
                        "sll $2,$2,0xa\n\t"
                        "subu %0,%0,$2"
                        : "=r"(x)
                        : "0"(x)
                        : "$2", "$3", "$6", "hi", "lo");
                    x += 0x3C10;
                    addr2 = (s32)((u8 *)D_800A351C + x);
                } else {
                    asm("move %0,$0" : "=r"(addr2));
                }
                addr = addr2;
            } else {
                src = (u8 *)D_800A351C + 0x7810;
                addr = (s32)src;
            }
            j = 0;
            value = 1;
            D_800A351C[0x7B48 / 4] = value;
            D_800A351C[0x7B4C / 4] = value;
            D_800A351C[0x7B50 / 4] = addr;
            D_800A351C[0x7B54 / 4] = value;
            addr = D_800A351C[0x7B3C / 4];
            for (; j < 0x300; j += 0x10) {
                src[j + 1] = 2;
            }
            if ((D_800A351C[0x7B44 / 4] & 3) == 0) {
                src[1] = 6;
            } else if (((D_800A351C[0x7B44 / 4] + 1) & 3) == 0) {
                src[0x2F1] = 3;
            }
            D_800A351C[0x7B2C / 4 + (D_800A351C[0x7B44 / 4] & 3)] = addr;
            base =
                D_800A351C[0x7B5C / 4] + (D_800A351C[0x7B44 / 4] & 3) * 0x300;
            SpuSetTransferMode(0);
            SpuSetTransferStartAddr(base);
            SpuWrite(src, 0x300);
            D_800A351C[0x7B3C / 4] += 0x300;
            do {
            } while (D_800A351C[0x7B48 / 4] != 0);
        }
        D_800A351C[0x7B48 / 4] = 3;
        func_800722D0();
        D_800A351C[0x7B48 / 4] = 0;
        D_800A351C[2] = 1;
    }
    D_800A351C[0x7B6C / 4] = SpuSetReverbVoice(0, D_800A351C[0x7B64 / 4]);
    D_800A351C[0x7B70 / 4] = SpuSetReverbVoice(0, D_800A351C[0x7B68 / 4]);
    SpuSetKey(1, D_800A351C[0x7B64 / 4] | D_800A351C[0x7B68 / 4]);
}

extern volatile s32 *D_800A351C;
void func_80072A20(s32 value) {
    D_800A351C[0x7B74 / 4] = value;
}

extern volatile s32 *D_800A351C;
void func_80072A34(void) {
    D_800A351C[0x7B20 / 4] = 1;
}

extern volatile s32 *D_800A351C;
void func_80072A48(void) {
    D_800A351C[0x7B20 / 4] = 0;
}

extern volatile s32 *D_800A351C;
s32 func_80072A5C(void) {
    return D_800A351C[0x7B24 / 4];
}

#ifdef NON_MATCHING
/* w9i: unit-diff clean at exact 0x8c (multu+mfhi/mflo, __divdi3 x2, both
 * branch arms) under differ/`make build/src/game.c.o`, but the clean-gate
 * build flips allocation: retail lw v1,0x7B24(v0) + ori v0,0x64 + multu
 * v1,v0 vs gate lw v0,0x7B24(v0) + ori a0,0x64 + multu v0,a0 -- 3 bytes,
 * same length. Gate-vs-interactive wall (w7i func_8007005C/720D0 family).
 * NOTE: `(long long)(u32)sym[...] * 100` silently kills cc1 (0-symbol
 * object); the val-local form below is the alive spelling. */
s32 func_80072A70(void) {
    u32 val;
    long long q;
    s32 mode;

    val = D_800A351C[0x7B24 / 4];
    q = (long long)val * 100;
    q = __divdi3(q, 0x100);
    mode = D_800A351C[0x7B74 / 4];
    if (mode != 0) {
        if (mode == 1) {
            q = __divdi3(q, 0x1388);
        }
    } else {
        q = __divdi3(q, 0x176A);
    }
    return (s32)q;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80072A70);
#endif

extern volatile s32 *D_800A351C;
/* Enabled after the maspsx li-$reg,0 wrapper fix; see matching.md. */
extern long long __divdi3(long long dividend, long long divisor);
#ifdef NON_MATCHING
/* w9i: w3c's named early-return recipe and the ==1 draft both now emit a
 * prologue `move a1,a0` param copy (arg->a1, factor->a0) and a beq+j
 * skip path, 8 bytes long, after func_80072A70 went live C above it.
 * TU-context param-copy wall (extends w3a/w4b); the maspsx li-$reg,0
 * wrapper fix in tools/maspsx_extern.py IS present and working. */
s32 func_80072AFC(u32 arg) {
    u32 factor;

    if (D_800A351C[0x7B74 / 4] == 1) {
        factor = (arg << 10) | 0x1000;
        return __divdi3((long long)arg * factor, 0xBB5);
    }
    return arg << 10;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80072AFC);
#endif

extern volatile s32 *D_800A351C;
s32 func_80072B4C(void) {
    volatile s32 *p;
    u32 i;
    s32 count;

    count = 0;
    i = 0;
    p = D_800A351C;
    do {
        if (p[0x7B2C / 4] != 0) {
            asm("");
            count += 1;
        }
        i += 1;
        p += 1;
    } while (i < 4);
    return count;
}

extern volatile s32 *D_800A351C;
s32 func_80072B88(void) {
    return D_800A351C[0];
}

extern volatile s32 *D_800A351C;
s32 func_80072B9C(void) {
    return D_800A351C[1];
}

extern volatile s32 *D_800A351C;
s32 func_80072BB0(s32 *size) {
    s32 difference;
    if (size)
        *size = 0x3C00;
    difference = D_800A351C[1] - 0x3C00;
    return D_800A351C[0] - difference;
}

u32 func_80072BDC(void *arg0) {
    register u32 word asm("a0");
    u32 swapped;
    u32 swapped2;
    register u32 size asm("v0");
    u32 check;

    word = *(u32 *)arg0;
    swapped = (word >> 24) | ((word >> 8) & 0xFF00) | ((word & 0xFF00) << 8) |
              (word << 24);
    check = (swapped & 0xFFFFFF00) == 0x61643200;
    if ((swapped & 0xFFFF0000) == 0x61640000) {
        word = *((u32 *)arg0 + 1);
        swapped2 = (word >> 24) | ((word >> 8) & 0xFF00) |
                   ((word & 0xFF00) << 8) | (word << 24);
        size = swapped2 - 0x10;
    } else {
        word = *((u32 *)arg0 + 1);
        swapped2 = (word >> 24) | ((word >> 8) & 0xFF00) |
                   ((word & 0xFF00) << 8) | (word << 24);
        size = swapped2 - 0xC;
    }
    if (check != 0) {
        size >>= 1;
    }
    if (swapped2) {
        return size;
    }
    return size;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80072CA8);

INCLUDE_ASM("asm/nonmatchings/game", func_80072FE4);

INCLUDE_ASM("asm/nonmatchings/game", func_80073100);

extern volatile s32 *D_800A351C;
void func_80073948(void) {
    volatile s32 *p;
    volatile s32 *field;
    u32 i;

    i = 0;
    p = D_800A351C;
    p[0x7B78 / 4] = 1;
    field = p;
    do {
        field[0x7B2C / 4] = 0;
        i += 1;
        field += 1;
    } while (i < 4);
}

extern volatile s32 *D_800A351C;
void func_80073978(void) {
    D_800A351C[0x7B78 / 4] = 0;
}

extern volatile s32 *D_800A351C;
extern void SwEnterCriticalSection(void);
extern void SwExitCriticalSection(void);

void func_8007398C(void) {
    volatile s32 *field;
    volatile s32 *p;
    u32 i;

    SwEnterCriticalSection();
    i = 0;
    p = D_800A351C;
    p[0] = 0;
    p[1] = 0;
    p[3] = 0;
    field = p;
    do {
        field[0x7B2C / 4] = 0;
        i += 1;
        field += 1;
    } while (i < 4);
    SwExitCriticalSection();
}

void func_800739E0(void) {
    volatile s32 *field;
    volatile s32 *p;
    u32 i;

    SwEnterCriticalSection();
    i = 0;
    p = D_800A351C;
    p[0] = 0;
    p[1] = 0;
    p[3] = 0;
    field = p;
    do {
        field[0x7B2C / 4] = 0;
        i += 1;
        field += 1;
    } while (i < 4);
    D_800A351C[0x7B3C / 4] = 1;
    D_800A351C[0x7B24 / 4] = 0;
    SwExitCriticalSection();
}

extern void SpuSetReverbVoice(s32, s32);

void func_80073A44(void) {
    SpuSetKey(0, D_800A351C[0x7B64 / 4] | D_800A351C[0x7B68 / 4]);
    SpuSetReverbVoice(D_800A351C[0x7B6C / 4], D_800A351C[0x7B64 / 4]);
    SpuSetReverbVoice(D_800A351C[0x7B70 / 4], D_800A351C[0x7B68 / 4]);
}

INCLUDE_ASM("asm/nonmatchings/game", func_80073AA4);

s32 func_80073BC8(void) {
    return 0xC00;
}

s32 func_80073BD0(void) {
    return 0x7B80;
}

extern volatile s32 *D_800A351C;
s32 func_80073BD8(void) {
    return D_800A351C[0x7B58 / 4];
}

extern void bzero(void *, s32);
extern void *SpuSetTransferCallback(void *);

s32 func_80073BEC(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                  s32 arg6) {
    SpuVoiceAttr va;
    SpuCommonAttr ca;
    register SpuCommonAttr *caarg asm("$4");
    u32 off;
    register s32 voice asm("$16");
    register s32 addr asm("$20");
    register s32 a5 asm("$23");
    s32 a6;
    u8 val;

    a5 = arg5;
    a6 = arg6;
    if (arg0 == 0) {
        goto bail;
    }
    if (arg2 == 0) {
        goto bail;
    }
    if (arg4 == 0) {
        goto bail;
    }
    if (arg1 == 0) {
        goto bail;
    }
    if (arg3 == 0) {
        goto bail;
    }
    D_800A351C = (volatile s32 *)arg0;
    bzero(arg0, 0x7B80);
    off = 0;
    val = 2;
    do {
        ((u8 *)D_800A351C + off)[0x7811] = val;
        off = off + 0x10;
    } while (off < 0x300);
    D_800A351C[0x7B3C / 4] = 1;
    D_800A351C[0x7B58 / 4] = 0;
    D_800A351C[0x7B5C / 4] = arg2;
    D_800A351C[0x7B60 / 4] = arg4;
    D_800A351C[0x7B64 / 4] = arg1;
    D_800A351C[0x7B68 / 4] = arg3;
    D_800A351C[0x7B7C / 4] = a5;
    voice = D_800A351C[0x7B64 / 4];
    addr = D_800A351C[0x7B5C / 4];
    ca.mask = 3;
    ca.mvol.left = 0x3FFF;
    ca.mvol.right = 0x3FFF;
    SpuSetCommonAttr(&ca);
    va.mask = 0xFF93;
    va.voice = voice;
    va.volume.left = -(voice == D_800A351C[0x7B64 / 4]) & 0x3FFF;
    va.volume.right = -(voice == D_800A351C[0x7B68 / 4]) & 0x3FFF;
    va.pitch = a5;
    va.addr = addr;
    va.a_mode = 1;
    va.s_mode = 1;
    va.r_mode = 3;
    va.ar = 0;
    va.dr = 0;
    va.sr = 0;
    va.rr = 0;
    va.sl = 0xF;
    SpuSetVoiceAttr(&va);
    voice = D_800A351C[0x7B68 / 4];
    addr = D_800A351C[0x7B60 / 4];
    {
        asm volatile("addiu %0, $sp, 0x50" : "=r"(caarg));
        ca.mask = 3;
        ca.mvol.left = 0x3FFF;
        ca.mvol.right = 0x3FFF;
        SpuSetCommonAttr(caarg);
        va.mask = 0xFF93;
        va.voice = voice;
        va.volume.left = -(voice == D_800A351C[0x7B64 / 4]) & 0x3FFF;
        va.volume.right = -(voice == D_800A351C[0x7B68 / 4]) & 0x3FFF;
        va.pitch = a5;
        va.addr = addr;
        va.a_mode = 1;
        va.s_mode = 1;
        va.r_mode = 3;
        va.ar = 0;
        va.dr = 0;
        va.sr = 0;
        va.rr = 0;
        va.sl = 0xF;
        SpuSetVoiceAttr(&va);
    }
    SwEnterCriticalSection();
    D_800A351C[0x7B14 / 4] = (s32)SpuSetIRQCallback(0);
    D_800A351C[0x7B18 / 4] = (s32)SpuSetTransferCallback(func_80072178);
    D_800A351C[0x7B1C / 4] = a6;
    if (a6 != 0) {
        D_800A351C[0x7B10 / 4] =
            (s32)((Callback (*)(Callback))VSyncCallback)(func_8007270C);
    } else {
        D_800A351C[0x7B10 / 4] = 0;
    }
    SwExitCriticalSection();
    return 1;
bail:
    return 0;
}
