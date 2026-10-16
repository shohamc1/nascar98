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
extern u32 D_800A38A0;
extern s8 D_800A2D10;
extern void *D_800A3A8C;
extern s32 strlen(char *);
extern u8 gOrderingTables[];
extern s32 gOrderingTableBank;
extern void func_8001E7EC(void *, s32, s32);
extern u8 D_800A39B0[];
extern s32 D_800A36B4;
extern s32 D_800A3948;
extern u16 D_800A38C0[];
extern void GsGetTimInfo(u8 *, u8 *);
extern u16 D_80090ED8[];
extern s32 D_80099590[];
extern u8 D_800A3320Absolute[];
extern u8 D_800A331CAbsolute[];
extern u16 D_80090ED8[];
extern s32 D_80099590[];
extern u8 D_800A3320Absolute[];
extern u8 D_800A331CAbsolute[];
extern s32 D_800A2EB0Absolute[];
extern void func_8003CAE8(s32);
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
extern s32 D_800A2EA4w18c[] asm("D_800A2EA4.NON_MATCHING");
extern s8 D_800A3A24w18c[] asm("D_800A3A24.NON_MATCHING");
extern s8 D_800A3A25w18c[] asm("D_800A3A25.NON_MATCHING");
extern s32 D_800A2EB0w18c[] asm("D_800A2EB0.NON_MATCHING");
extern u8 D_800A2EDAw18c[] asm("D_800A2EDA.NON_MATCHING");
extern s8 D_800A3620w18c[] asm("D_800A3620.NON_MATCHING");
extern s32 D_800A33CCw18c[] asm("D_800A33CC.NON_MATCHING");
extern u32 D_800A33C0w18c asm("D_800A33C0.NON_MATCHING");
extern u32 D_800A33C0addrw18c[];
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
extern u32 gPrimitiveCursorNonMatching asm("gPrimitiveCursor.NON_MATCHING");
extern u32 gPrimitiveCursor_gp asm("gPrimitiveCursor.NON_MATCHING");
extern u32 D_800A3570;
extern s32 D_800A38F4;
extern s32 D_800A2F10[];
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
extern s32 D_800A2D44;
extern void ListPushFront(u8 *, u8 **, u8 **);
extern void func_8001C668(void *, void *);
extern s32 sprintf(char *, u8 *);
extern u8 D_8008CC6C[];
extern long RotTransPers_nom();
extern long RotTransPers3_nom();
extern void func_80033788();
extern void func_8003379C();
extern s32 D_800A2D60;
extern s32 D_800A2D5C;
extern s32 *D_800A2D64;
extern void *HeapAlloc(u32);
extern s32 D_800A2D5C;
extern s32 gOrderingTableBankAbsolute[];
extern s32 D_800A2CF8[];
extern s32 D_800A2D5C;
extern s32 MathMultiplyFixed16(s32, s32);

extern s32 gRandomCount;
extern s32 gRandomCountMark;
extern s32 gRandomSeed;
extern s32 gRandomSeed, gRandomCount;
extern s32 gRandomCountMark;
extern s32 gRandomSeed;
extern s32 gRandomCount;
void SystemShowFatalError(char *message);
u32 MathSqrt(u32 value);
void RandomCountMark(void);
s32 RandomSeedGet(void);
void RandomSeedSet(s32 seed);
s32 RandomScaledGet(s32 scale);

/* Primitives and text. */

extern s32 gPrimitiveCursorLui asm("gPrimitiveCursorAbsolute");
void func_80017D80(u8 *arg0) {
    extern u32 gPrimitiveCursor[];
    extern s32 D_800A39C8[];
    extern s32 D_800A36D0Absolute[];
    POLY_FT4 *entry;
    u32 cursor;

    cursor = gPrimitiveCursor[0];
    gPrimitiveCursorLui = cursor + 0x28;
    entry = (POLY_FT4 *)cursor;
    *entry = *(POLY_FT4 *)arg0;
    AddPrim((u8 *)D_800A39C8[0], entry);
}

void func_80017E08(void) {
    extern u8 D_800BA064[];
    extern u8 D_800BA8D4[];
    extern u8 D_800BB144[];
    extern u16 D_80090F0E[];
    u8 *prim;
    s32 i;
    s32 offsetA;
    s32 shade;
    s32 x1a;
    s32 yvDup;
    s32 x0a;
    s32 x0b;
    s32 x1b;
    s32 offsetB;
    register s32 cB asm("$8");
    s32 y2;
    s32 y0;
    register s32 yv asm("$5");
    s32 xv;
    u16 *table;
    u16 tv;
    s32 xbase;
    s32 offsetC;
    s32 rb;
    s32 x0v;
    s32 y0vA;
    s32 x1v;
    s32 y2vA;
    i = 0;
    shade = 0x80;
    offsetA = 0;
    do {
        prim = D_800BA064 + offsetA;
        SetPolyFT4((POLY_FT4 *)prim);
        SetShadeTex(prim, 0);
        *((u8 *)(prim + 4)) = shade;
        *((u8 *)(prim + 5)) = shade;
        *((u8 *)(prim + 6)) = shade;
        *((u16 *)(prim + 0x16)) = GetTPage(2, 0, 0x300, 0);
        x0v = (12 * (i % 4)) + 0xD0;
        y0vA = (16 * (i / 4)) + 0x158;
        asm volatile("" : : "r"(i), "r"(offsetA));
        x1v = (12 * (i % 4)) + 0xDB;
        y2vA = (16 * (i / 4)) + 0x168;
        *((u8 *)(prim + 0xC)) = x0v;
        *((u8 *)(prim + 0xD)) = y0vA;
        *((u8 *)(prim + 0x1C)) = x0v;
        *((u8 *)(prim + 0x14)) = x1v;
        *((u8 *)(prim + 0x15)) = y0vA;
        *((u8 *)(prim + 0x1D)) = y2vA;
        *((u8 *)(prim + 0x24)) = x1v;
        *((u8 *)(prim + 0x25)) = y2vA;
        offsetA += 0x28;
        i++;
    } while (i < 0xC);
    i = 0;
    y0 = 0xF0;
    y2 = 0xFA;
    x1b = 0xD;
    x0b = 4;
    x1a = 9;
    x0a = 0;
    offsetB = 0;
    do {
        prim = D_800BA8D4 + offsetB;
        SetPolyFT4((POLY_FT4 *)prim);
        SetShadeTex(prim, 0);
        cB = 0x80;
        *((u8 *)(prim + 4)) = cB;
        *((u8 *)(prim + 5)) = cB;
        asm volatile("" : : "r"(x1a));
        *((u8 *)(prim + 6)) = cB;
        if (x1a < 0x100) {
            *((u16 *)(prim + 0x16)) = GetTPage(2, 0, 0x100, 0);
            *((u8 *)(prim + 0xC)) = x0a;
            *((u8 *)(prim + 0xD)) = y0;
            *((u8 *)(prim + 0x14)) = x1a;
            *((u8 *)(prim + 0x15)) = y0;
            *((u8 *)(prim + 0x1C)) = x0a;
            *((u8 *)(prim + 0x1D)) = y2;
            *((u8 *)(prim + 0x24)) = x1a;
            *((u8 *)(prim + 0x25)) = y2;
        } else {
            *((u16 *)(prim + 0x16)) = GetTPage(2, 0, 0x200, 0);
            *((u8 *)(prim + 0xC)) = x0b;
            *((u8 *)(prim + 0xD)) = y0;
            *((u8 *)(prim + 0x14)) = x1b;
            *((u8 *)(prim + 0x15)) = y0;
            *((u8 *)(prim + 0x1C)) = x0b;
            *((u8 *)(prim + 0x1D)) = y2;
            *((u8 *)(prim + 0x24)) = x1b;
            *((u8 *)(prim + 0x25)) = y2;
        }
        cB = 0;
        x1b += 9;
        x0b += 9;
        x1a += 9;
        x0a += 9;
        i++;
        offsetB += 0x28;
    } while (i < 0x36);
    i = 0;
    rb = 0x3C;
    table = D_80090F0E;
    offsetC = 0;
    xbase = 0;
    do {
        prim = D_800BB144 + offsetC;
        SetPolyFT4((POLY_FT4 *)prim);
        SetShadeTex(prim, 0);
        *((u8 *)(prim + 4)) = rb;
        *((u8 *)(prim + 5)) = 0x64;
        *((u8 *)(prim + 6)) = rb;
        *((u16 *)(prim + 0xE)) = GetClut(table[0], table[1]);
        *((u16 *)(prim + 0x16)) = GetTPage(table[4], 0, table[-2], table[-1]);
        xv = xbase + table[2];
        yv = table[3];
        yvDup = yv;
        *((u8 *)(prim + 0xD)) = yvDup;
        *((u8 *)(prim + 0x14)) = xv + 4;
        *((u8 *)(prim + 0xC)) = xv;
        *((u8 *)(prim + 0x1C)) = xv;
        *((u8 *)(prim + 0x1D)) = yv + 7;
        *((u8 *)(prim + 0x25)) = yv + 7;
        *((u8 *)(prim + 0x15)) = yv;
        *((u8 *)(prim + 0x24)) = xv + 4;
        xbase += 5;
        offsetC += 0x28;
    } while (++i < 0xC);
}

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_800180C0);

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

extern void func_80050028Text(s8 *, s16, s16, s8);
void func_800183C0(s32 time, s32 x, s32 y, s32 scale) {
    s8 text[24];
    s32 minutes;
    s32 value;
    s32 hundredths;
    s32 len;
    s16 *base;
    s16 *width;
    s8 *p;
    s32 pen;

    minutes = time / 1200;
    value = time / 20 - minutes * 60;
    hundredths = (time % 20) * 5;
    text[0] = 0;
    len = 0;
    if (minutes < 10) {
        len = 1;
        text[0] = '0';
        text[1] = 0;
    }
    func_80012EA8(minutes, (u8 *)text + len);
    text[2] = ':';
    text[3] = 0;
    len = 3;
    if (value < 10) {
        len = 4;
        text[3] = '0';
        text[4] = 0;
    }
    func_80012EA8(value, (u8 *)text + len);
    text[5] = ':';
    text[6] = 0;
    len = 6;
    if (hundredths < 10) {
        len = 7;
        text[6] = '0';
        text[7] = 0;
    }
    func_80012EA8(hundredths, (u8 *)text + len);
    if (scale == 3) {
        func_80050028Text(text, (s16)x, (s16)y, 0);
        return;
    }
    pen = x;
    p = text;
    if (text[0] != 0) {
        base = D_800A2D88;
        width = base + scale;
        /* Reuse the seconds local for the glyph cursor. */
        value = (s32)p;
        do {
            func_800180C0(*(s8 *)value, pen, y, scale);
            pen += *width;
            value++;
        } while (*(s8 *)value != 0);
    }
}

extern u8 D_8008CC9C[];
extern u8 D_8008CCA8[];
extern u8 D_8008CCBC[];
extern u8 D_8008CCD0[];
extern u8 D_8008CCE0[];
extern u8 D_8008CCF0[];
extern s32 D_800A2EACAbsolute[];
extern s32 sprintfArgs(s8 *, u8 *, ...);
asm(".globl sprintfArgs\nsprintfArgs = sprintf");

void func_80018588(void *timeValue, s32 flags, s32 buffer) {
    register s32 time asm("a3");
    s32 noSign;
    register s32 blank asm("v0");
    register s32 hours asm("t2");
    s32 totalSeconds;
    s32 mode;
    register s32 minutes asm("t0");
    register s32 seconds asm("t1");
    s32 rem1000;
    s32 msSign;
    s32 msShift;
    s32 millis;
    s8 *out;
    s32 sign;
    typedef struct {
        u8 bytes[10];
    } TimeText10;

    time = (s32)timeValue;
    out = (s8 *)buffer;
    noSign = 0;
    if (flags < 0) {
        noSign = 1;
        asm("");
    }
    if (time == 0x7FFFFFFF) {
        *(TimeText10 *)out = *(TimeText10 *)D_8008CC9C;
        return;
    }
    blank = noSign;
    if (blank != 0) {
        sign = ' ';
    } else if (time < 0) {
        time = -time;
        sign = '-';
    } else {
        sign = '+';
    }
    asm volatile(
        "\n\tlui\t$2,0x7482\n\tori\t$2,$2,0x296b\n\tmult\t$7,$2\n\tmfhi\t$8\n\tlui\t$4,0x6666\n\tori\t$4,$4,0x6667\n\tmult\t$7,$4\n\tlui\t$3,0x1b4e\n\tori\t$3,$3,0x81b5\n\tmfhi\t$5\n\tsra\t$6,$7,31\n\tsra\t$2,$8,18\n\tmult\t$7,$3\n\tsubu\t$10,$2,$6\n\tsra\t$5,$5,6\n\tsubu\t$5,$5,$6\n\tsll\t$2,$5,2\n\taddu\t$2,$2,$5\n\tsll\t$2,$2,5\n\tsubu\t$2,$7,$2\n\tsll\t$3,$2,5\n\tsubu\t$3,$3,$2\n\tsll\t$3,$3,2\n\taddu\t$3,$3,$2\n\tmfhi\t$8\n\tsll\t$3,$3,3\n\tsll\t$2,$10,4\n\tmult\t$3,$4\n\tsubu\t$2,$2,$10\n\tsll\t$2,$2,2\n\tsra\t$4,$8,10\n\tsubu\t$4,$4,$6\n\tsubu\t$8,$4,$2\n\tsll\t$2,$4,4\n\tsubu\t$2,$2,$4\n\tsll\t$2,$2,2\n\tsubu\t$9,$5,$2"
        : "=r"(hours), "=r"(totalSeconds), "=r"(minutes), "=r"(seconds),
          "=r"(rem1000)
        : "r"(time)
        : "$2", "$4", "$6");
    mode = D_800A2EACAbsolute[0];
    asm volatile("\n\tsra\t$3,$3,31\n\tmfhi\t$14\n\tsra\t$2,$14,6"
                 : "=r"(msSign), "=r"(msShift)
                 : "0"(rem1000)
                 : "$14");
    millis = msShift - msSign;
    if (mode != 0) {
        if (hours != 0) {
            sprintfArgs(out, D_8008CCA8, sign, hours, minutes, seconds);
        } else if (minutes != 0) {
            sprintfArgs(out, D_8008CCBC, sign, minutes, seconds, millis);
        } else {
            sprintfArgs(out, D_8008CCD0, sign, seconds, millis);
        }
    } else if (hours != 0) {
        sprintfArgs(out, D_8008CCE0, hours, minutes, seconds);
    } else {
        sprintfArgs(out, D_8008CCF0, minutes, seconds, millis);
    }
}

extern void func_80018588(void *, s32, s32);
extern void func_80050028Text(s8 *, s16, s16, s8);
asm(".globl func_80050028Text\nfunc_80050028Text = func_80050028");
void func_80018768(void *arg0, s32 x, s32 y, s32 scale) {
    s8 text[24];
    s8 *p;
    s16 *base;
    s16 *width;
    s8 *field;
    s32 pen;

    func_80018588(arg0, scale, text);
    if (scale < 0) {
        scale = -scale;
    }
    if (scale == 3) {
        func_80050028Text(text, (s16)x, (s16)y, 0);
        return;
    }
    pen = x;
    p = text;
    if (text[0] != 0) {
        base = D_800A2D88;
        width = base + scale;
        field = p;
        do {
            func_800180C0(*field, pen, y, scale);
            pen += *width;
            field++;
        } while (*field != 0);
    }
}

extern void func_800183C0(s32, s32, s32, s32);
void func_80018848(void *arg0, s32 arg1, s32 arg2) {
    s32 value;
    func_800183C0(*(s32 *)((u8 *)arg0 + 0x258), arg1, arg2, 0);
    value = *(s32 *)((u8 *)arg0 + 0x25C);
    if (value != 0x7FFFFFFF) {
        func_800183C0(value, arg1, arg2 + 0x10, 0);
    }
}

void func_800188B0(s32 pos, u8 mode, s32 x, s32 y, s32 scale) {
    s8 text[24];
    s32 value;
    s32 indent;
    s32 i;

    if (pos < 0) {
        pos = 0;
    }
    if (mode == 1) {
        value = ((pos >> 16) * 0x150) / 550;
    } else {
        value = ((pos >> 16) * 0xD2) / 550;
    }
    text[0] = (indent = 0);
    if (value < 100) {
        indent = 1;
        text[0] = 32;
        text[1] = 0;
    }
    if (value < 10) {
        /* Both arms are identical on purpose: the test adds references to
         * x and scale, which gives retail's s1/s2 allocation. */
        if (scale || x) {
            text[indent] = 32;
            indent += 1;
            text[indent] = 0;
        } else {
            text[indent] = 32;
            indent += 1;
            text[indent] = 0;
        }
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

extern void func_800180C0(s8, s32, s32, s32);
extern s16 D_800A2D88[];
void func_80018B18(s32 value, s32 x, s32 y, s32 scale) {
    s8 text[24];
    s8 *start;
    s16 *base;
    s16 *width;
    s8 *p;
    s32 pen;

    value = (s16)value;
    start = text;
    text[0] = 0;
    func_80012EA8(value, start);
    pen = x;
    if (text[0] != 0) {
        base = D_800A2D88;
        width = base + scale;
        p = start;
        do {
            func_800180C0(*p, pen, y, scale);
            pen += *width;
            p++;
        } while (*p != 0);
    }
}

extern void func_800180C0(s8, s32, s32, s32);
extern s16 D_800A2D88[];
void func_80018BD4(s32 value, s32 x, s32 y, s32 scale) {
    s8 text[24];
    s8 *start;
    s16 *base;
    s16 *width;
    s8 *p;
    s32 pen;

    start = text;
    text[0] = 0;
    func_80012F94(value, start);
    pen = x;
    if (text[0] != 0) {
        base = D_800A2D88;
        width = base + scale;
        p = start;
        do {
            func_800180C0(*p, pen, y, scale);
            pen += *width;
            p++;
        } while (*p != 0);
    }
}

extern POLY_FT4 D_800AEB94[];
extern POLY_FT4 D_800AE29C[];
extern POLY_FT4 D_800BC22C[];
extern u16 D_80090FC4[];

void func_80018C88(void) {
    POLY_FT4 *prim;
    POLY_F4 *f4;
    u16 *table;
    u16 tpage;
    s32 u;
    s32 v;
    s32 w;
    s32 c;
    s32 i;
    s32 j;
    s32 rowOff;
    s32 uMid;
    s32 vLow;
    s32 glyphW;
    s32 vBase;
    s32 texX;
    s32 uWide1;
    s32 uWide2;
    s32 yShift;
    s32 vTop1;
    s32 vBot1;
    s32 vTop2;
    s32 vBot2;
    s32 k;
    s32 r8;
    s32 r15;
    s32 r16;

    glyphW = 25;
    vBase = 32;
    i = 0;
    uWide1 = -66;
    uWide2 = -8;
    texX = -209;
    do {
        prim = &D_800AEB94[i];
        SetPolyFT4(prim);
        SetShadeTex(prim, 1);
        prim->clut = GetClut(0x300, 0xEA);
        prim->tpage = GetTPage(1, 0, 0x280, 0);
        switch (i) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            v = 0x30;
            u = i * glyphW;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = u + glyphW - 1;
            prim->u2 = u;
            prim->v1 = v;
            prim->u3 = u + glyphW - 1;
            prim->v2 = vBase + 0x30;
            prim->v3 = vBase + 0x30;
            break;
        case 10:
            u = 0;
            v = 0;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = uWide1;
            prim->v1 = v;
            prim->u2 = u;
            prim->v2 = 0x18;
            prim->u3 = uWide1;
            prim->v3 = 0x18;
            break;
        case 11:
        case 12:
        case 13:
        case 14:
            u = texX * 2;
            v = 0x18;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = u + 0x25;
            prim->v1 = v;
            prim->u2 = u;
            prim->v2 = 0x30;
            prim->u3 = u + 0x25;
            prim->v3 = 0x30;
            break;
        case 15:
            u = 0;
            v = 0x50;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = uWide2;
            prim->v1 = v;
            prim->u2 = u;
            prim->v2 = 0x71;
            prim->u3 = uWide2;
            prim->v3 = 0x71;
            break;
        }
        asm("");
        asm("");
        asm("");
        texX += 19;
        i++;
    } while (i < 17);

    uMid = 0xCD;
    vLow = 0xB8;
    yShift = 0;
    j = 0;
    rowOff = 0;
panel:
    i = 0;
    do {
        prim = (POLY_FT4 *)((u8 *)D_800AE29C + rowOff + i * sizeof(POLY_FT4));
        SetPolyFT4(prim);
        SetShadeTex(prim, 1);
        prim->clut = GetClut(0x300, 0xEC);
        prim->tpage = GetTPage(0, 0, 0x340, 0);
        f4 = (POLY_F4 *)prim;
        switch (i) {
        case 0:
            u = 0x70;
            v = 0x88;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = 0x9F;
            prim->v1 = v;
            prim->u2 = 0x70;
            prim->u3 = 0x9F;
            prim->v2 = vLow;
            prim->v3 = vLow;
            u = 0x14;
            v = 0x96 - yShift;
            prim->x0 = u;
            prim->y0 = v;
            prim->x1 = 0x43;
            prim->y1 = v;
            prim->x2 = 0x14;
            prim->y2 = v + 0x30;
            prim->x3 = 0x43;
            prim->y3 = v + 0x30;
            SetSemiTrans(prim, 1);
            break;
        case 1:
            u = 0x40;
            v = 0x88;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = 0x6F;
            prim->v1 = v;
            prim->u2 = 0x40;
            prim->v2 = vLow;
            prim->u3 = 0x6F;
            prim->v3 = vLow;
            u = 0x14;
            v = 0x96 - yShift;
            prim->x0 = u;
            prim->y0 = v;
            prim->x1 = 0x43;
            prim->y1 = v;
            prim->x2 = 0x14;
            prim->y2 = v + 0x30;
            prim->x3 = 0x43;
            prim->y3 = v + 0x30;
            break;
        case 2:
            u = 0xDD;
            v = 0x95;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = 0xEC;
            prim->v1 = v;
            prim->u2 = 0xDD;
            prim->u3 = 0xEC;
            prim->v2 = 0x9B;
            prim->v3 = 0x9B;
            u = 0x29;
            v = 0xAB - yShift;
            prim->x0 = u;
            prim->y0 = v;
            prim->x1 = 0x38;
            prim->y1 = v;
            prim->x2 = 0x29;
            prim->y2 = v + 6;
            prim->x3 = 0x38;
            prim->y3 = v + 6;
            break;
        case 3:
            u = 0xA0;
            v = 0x89;
            prim->u0 = u;
            prim->u1 = uMid;
            prim->u2 = 0xA0;
            prim->u3 = uMid;
            prim->v0 = v;
            prim->v1 = v;
            prim->v2 = 0x92;
            prim->v3 = 0x92;
            u = 0x14;
            v = 0x7D - yShift;
            prim->x0 = u;
            prim->y0 = v;
            prim->x1 = 0x41;
            prim->y1 = v;
            prim->x2 = 0x14;
            prim->y2 = v + 9;
            prim->x3 = 0x41;
            prim->y3 = v + 9;
            k = 0x100;
            w = k - v;
            break;
        case 4:
            u = 0xA0;
            v = 0x93;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = 0xD2;
            prim->v1 = v;
            prim->u2 = 0xA0;
            prim->u3 = 0xD2;
            prim->v2 = 0x9C;
            prim->v3 = 0x9C;
            u = 0x100;
            v = 0x7D - yShift;
            prim->x0 = u;
            prim->y0 = v;
            prim->x1 = 0x132;
            prim->y1 = v;
            prim->x2 = 0x100;
            prim->y2 = v + 9;
            prim->x3 = 0x132;
            prim->y3 = v + 9;
            break;
        case 5:
            u = 0xCD;
            v = 0x89;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = 0xFF;
            prim->v1 = v;
            prim->v2 = 0x92;
            prim->v3 = 0x92;
            prim->u2 = uMid;
            prim->u3 = 0xFF;
            u = 0x100;
            v = 0x95 - yShift;
            prim->x0 = u;
            prim->y0 = v;
            prim->x1 = 0x132;
            prim->y1 = v;
            prim->x2 = 0x100;
            prim->y2 = v + 9;
            prim->x3 = 0x132;
            prim->y3 = v + 9;
            break;
        case 6:
            u = 0xCD;
            v = 0x9D;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = 0xFF;
            prim->v1 = v;
            prim->v2 = 0xA6;
            prim->v3 = 0xA6;
            prim->u2 = uMid;
            prim->u3 = 0xFF;
            u = 0x100;
            v = 0xAD - yShift;
            prim->x0 = u;
            prim->y0 = v;
            prim->x1 = 0x132;
            prim->y1 = v;
            prim->x2 = 0x100;
            prim->y2 = v + 9;
            prim->x3 = 0x132;
            prim->y3 = v + 9;
            break;
        case 7:
            u = 0xA0;
            v = 0x9D;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = uMid;
            prim->v1 = v;
            prim->u2 = 0xA0;
            prim->v2 = 0xAB;
            prim->u3 = uMid;
            prim->v3 = 0xAB;
            u = 0x14;
            v = 0xC8 - yShift;
            prim->x0 = u;
            prim->y0 = v;
            prim->x1 = 0x41;
            prim->y1 = v;
            prim->x2 = 0x14;
            prim->y2 = v + 0xE;
            prim->x3 = 0x41;
            prim->y3 = v + 0xE;
            break;
        case 9:
            SetPolyF4(f4);
            u = 0x14;
            v = 0x86 - yShift;
            f4->x0 = u;
            f4->y0 = v;
            f4->x1 = 0x41;
            f4->y1 = v;
            f4->x2 = 0x14;
            f4->y2 = v + 9;
            f4->x3 = 0x41;
            f4->y3 = v + 9;
            SetSemiTrans(f4, 1);
            setRGB0(f4, 0x1E, 0x1E, 0x1E);
            break;
        case 10:
            SetPolyF4(f4);
            u = 0x100;
            v = 0x86 - yShift;
            f4->x0 = u;
            f4->y0 = v;
            f4->x1 = 0x132;
            f4->y1 = v;
            f4->x2 = 0x100;
            f4->y2 = v + 9;
            f4->x3 = 0x132;
            f4->y3 = v + 9;
            SetSemiTrans(f4, 1);
            setRGB0(f4, 0x1E, 0x1E, 0x1E);
            break;
        case 11:
            SetPolyF4(f4);
            u = 0x100;
            v = 0x9E - yShift;
            f4->x0 = u;
            f4->y0 = v;
            f4->x1 = 0x132;
            f4->y1 = v;
            f4->x2 = 0x100;
            f4->y2 = v + 9;
            f4->x3 = 0x132;
            f4->y3 = v + 9;
            SetSemiTrans(f4, 1);
            setRGB0(f4, 0x1E, 0x1E, 0x1E);
            break;
        case 12:
            SetPolyF4(f4);
            u = 0x100;
            v = 0xB6 - yShift;
            f4->x0 = u;
            f4->y0 = v;
            f4->x1 = 0x132;
            f4->y1 = v;
            f4->x2 = 0x100;
            f4->y2 = v + 9;
            f4->x3 = 0x132;
            f4->y3 = v + 9;
            SetSemiTrans(f4, 1);
            setRGB0(f4, 0x1E, 0x1E, 0x1E);
            break;
        case 13:
            SetPolyF4(f4);
            u = 0x1E;
            v = 0xCC - yShift;
            f4->x0 = u;
            f4->y0 = v;
            f4->x1 = 0x40;
            f4->y1 = v;
            f4->x2 = 0x1E;
            f4->y2 = v + 2;
            f4->x3 = 0x40;
            f4->y3 = v + 2;
            setRGB0(f4, 0x1E, 0xE6, 0x1E);
            break;
        case 14:
            u = 0xD7;
            v = 0x95;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = 0xDC;
            prim->v1 = v;
            prim->u2 = 0xD7;
            prim->v2 = 0x9B;
            prim->u3 = 0xDC;
            prim->v3 = 0x9B;
            u = 0x28;
            v = 0xAB - yShift;
            prim->x0 = u;
            prim->y0 = v;
            prim->x1 = 0x2D;
            prim->y1 = v;
            prim->x2 = 0x28;
            prim->y2 = v + 6;
            prim->x3 = 0x2D;
            prim->y3 = v + 6;
            break;
        case 8:
            u = 0xA0;
            v = 0xAB;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = 0xEE;
            prim->v1 = v;
            prim->u2 = 0xA0;
            prim->u3 = 0xEE;
            prim->v2 = vLow;
            prim->v3 = vLow;
            u = 0x79;
            v = 0xC8 - yShift;
            prim->x0 = u;
            prim->y0 = v;
            r8 = 0;
            r8 = 0xC7;
            prim->x1 = r8;
            prim->y1 = v;
            prim->x2 = 0x79;
            prim->y2 = v + 0xD;
            prim->x3 = r8;
            prim->y3 = v + 0xD;
            break;
        case 15:
            prim->clut = GetClut(0x300, 0xE5);
            prim->tpage = GetTPage(1, 0, 0x280, 0);
            u = 0;
            v = 0xC1;
            prim->u0 = u;
            prim->v0 = v;
            prim->u1 = 0x4E;
            prim->v1 = v;
            prim->v2 = 0xCE;
            prim->v3 = 0xCE;
            prim->u2 = 0;
            prim->u3 = 0x4E;
            u = 0x79;
            v = 0xA0 - yShift;
            prim->x0 = u;
            prim->y0 = v;
            r15 = 0;
            r15 = 0xC7;
            prim->x1 = r15;
            prim->y1 = v;
            prim->x2 = 0x79;
            prim->y2 = v + 0xD;
            prim->x3 = r15;
            prim->y3 = v + 0xD;
            break;
        case 16:
            prim->clut = GetClut(0x300, 0xE5);
            prim->tpage = GetTPage(1, 0, 0x280, 0);
            u = 0;
            v = 0xCE;
            prim->v0 = v;
            prim->u0 = u;
            prim->u1 = 0x4E;
            prim->v1 = v;
            prim->v2 = 0xDB;
            prim->v3 = 0xDB;
            prim->u2 = 0;
            prim->u3 = 0x4E;
            u = 0x79;
            v = 0xB4 - yShift;
            prim->x0 = u;
            prim->y0 = v;
            r16 = 0;
            r16 = 0xC7;
            prim->x1 = r16;
            prim->y1 = v;
            prim->x2 = 0x79;
            prim->y2 = v + 0xD;
            prim->x3 = r16;
            prim->y3 = v + 0xD;
            break;
        case 17:
            SetPolyF4(f4);
            u = 0x55;
            v = 0x8C - yShift;
            f4->x0 = u;
            f4->y0 = v;
            f4->x1 = 0xF0;
            f4->y1 = v;
            f4->x2 = 0x55;
            f4->y2 = v + 0xC;
            f4->x3 = 0xF0;
            f4->y3 = v + 0xC;
            setRGB0(f4, 0xA, 0xA, 0xA);
            break;
        }
        i++;
    } while (i < 18);
    rowOff += 18 * sizeof(POLY_FT4);
    yShift += 100;
    j++;
    if (j < 2) {
        goto panel;
    }

    i = 0;
    table = D_80090FC4;
    vBot2 = 0x164;
    vTop2 = -0x48;
    vBot1 = 0x17C;
    vTop1 = -0x18;
    c = -0x61;
    do {
        prim = &D_800BC22C[i];
        SetPolyFT4(prim);
        SetShadeTex(prim, 1);
        prim->clut = GetClut(0x300, 0xEE);
        switch (i) {
        case 0:
            prim->tpage = GetTPage(1, 0, 0x300, 0);
            setUV4(prim, 0, 0x58, 0x9F, 0x58, 0, 0x88, 0x9F, 0x88);
            break;
        case 1:
            prim->tpage = GetTPage(1, 0, 0x380, 0);
            setUV4(prim, 0, 0x58, 0x9F, 0x58, 0, 0xA0, 0x9F, 0xA0);
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            prim->tpage = GetTPage(1, 0, 0x300, 0);
            v = vTop1 + 0x188;
            setUV4(prim, 0, v, c, v, 0, vBot1, c, vBot1);
            break;
        case 6:
        case 7:
            prim->tpage = GetTPage(1, 0, 0x380, 0);
            v = vTop2 + 0x1A0;
            setUV4(prim, 0, v, c, v, 0, vBot2, c, vBot2);
            break;
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            prim->clut = GetClut(table[0], table[1]);
            prim->tpage = GetTPage(table[4], 0, table[-2], table[-1]);
            w = (i - 8) * 16;
            u = w + table[2];
            v = table[3] + 0x18;
            setUV4(prim, u, v, u + 0xF, v, u, v + 0x18, u + 0xF, v + 0x18);
            break;
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            prim->clut = GetClut(table[0], table[1]);
            prim->tpage = GetTPage(table[4], 0, table[-2], table[-1]);
            w = (i - 14) * 16;
            u = w + table[2];
            v = table[3];
            setUV4(prim, u, v, u + 0xF, v, u, v + 0x18, u + 0xF, v + 0x18);
            break;
        }
        vBot2 += 12;
        vTop2 += 12;
        vBot1 += 12;
        vTop1 += 12;
        i++;
    } while (i < 20);
}

extern u32 gPrimitiveCursor[];
extern s32 D_800A2EC8[];
extern s32 D_800A39C8[];
extern s32 D_800A397CAbsolute[];
extern s32 D_800A36D0Absolute[];

/* Draws a 0x7F x 0x1F sprite quad from the 14-byte table at D_80090EFC.
   kind selects the table row (0 -> 0xC, 1 -> 0xD, 2 -> 0xB). */
void func_800197D4(s32 kind, s32 x, s32 y) {
    typedef struct {
        u16 texX;
        u16 texY;
        u16 clutX;
        u16 clutY;
        u16 colU;
        u16 colV;
        u16 tpage;
    } SpriteDef;
    extern SpriteDef D_80090EFC[];
    POLY_FT4 *poly;
    s32 cursor;
    s32 flag;
    s32 index;

    flag = D_800A2EC8[0];
    cursor = gPrimitiveCursor[0];
    gPrimitiveCursorLui = cursor + 0x28;
    poly = (POLY_FT4 *)cursor;
    if (flag == 0 || D_800A397CAbsolute[0] != 2) {
        switch (kind) {
        case 0:
            index = 0xC;
            break;
        case 1:
            index = 0xD;
            break;
        case 2:
            index = 0xB;
            break;
        }
        SetPolyFT4(poly);
        SetShadeTex(poly, 1);
        poly->tpage = GetTPage(D_80090EFC[index].tpage, 0,
                               D_80090EFC[index].texX, D_80090EFC[index].texY);
        poly->clut = GetClut(D_80090EFC[index].clutX, D_80090EFC[index].clutY);
        poly->x0 = x;
        poly->y0 = y;
        poly->x1 = x + 0x7F;
        poly->y1 = y;
        poly->x2 = x;
        poly->y2 = y + 0x1F;
        poly->x3 = x + 0x7F;
        poly->y3 = y + 0x1F;
        poly->u0 = D_80090EFC[index].colU;
        poly->v0 = D_80090EFC[index].colV;
        poly->u1 = D_80090EFC[index].colU + 0x7F;
        poly->v1 = D_80090EFC[index].colV;
        poly->u2 = D_80090EFC[index].colU;
        poly->v2 = D_80090EFC[index].colV + 0x20;
        poly->u3 = D_80090EFC[index].colU + 0x7F;
        poly->v3 = D_80090EFC[index].colV + 0x20;
        AddPrim((u8 *)D_800A39C8[0], poly);
    }
}

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
    s32 radiusB;
    s32 radiusA;
    u16 corners[8];
    u16 *corner;
    s32 off;
    s32 off3;
    extern s16 D_80091072[];
    extern u8 D_800A3A2CAbsolute[];
    extern u8 D_800A3A34Absolute[];

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
        do {
            product1 = MathMultiplyFixed16(radiusA, (s32)*ptrA << 16);
            product2 = MathMultiplyFixed16(radiusB, (s32)*ptrB << 16);
            x = (product1 - product2) >> 16;
            product3 = MathMultiplyFixed16(radiusB, (s32)*ptrA << 16);
            y = (product3 + MathMultiplyFixed16(radiusA, (s32)*ptrB << 16)) >>
                16;
            off = i * 4;
            corner = (u16 *)((s32)corners + off);
            *corner = x + 0x2C;
            corner[1] = y + 0xAE;
        } while (0);
        if (arg2 != 0) {
            corner[1] = y + 0x4A;
        }
        ptrB += 2;
        ptrA += 2;
    }
    ((u16 *)arg1)[4] = corners[0];
    ((u16 *)arg1)[5] = corners[1];
    ((u16 *)arg1)[8] = corners[2];
    ((u16 *)arg1)[9] = corners[3];
    ((u16 *)arg1)[12] = corners[4];
    ((u16 *)arg1)[13] = corners[5];
    ((u16 *)arg1)[16] = corners[6];
    ((u16 *)arg1)[17] = corners[7];
}

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_80019C10);

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_8001A4D4);

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_8001A778);

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_8001AEDC);

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_8001B3F0);

#ifdef NON_MATCHING
/* Parked 2026-10-12 at 600 (was 9500 first draft). Matched: div sequences,
 * head load order (bank term hoisted as its own statement is the permuter's),
 * the switch dispatch chain (beq 2 / slti 3 / beq 1 - gcc's balanced tree,
 * body order = source case order 1,2,3), D_800A2EB4[0] >= 2 polarity, and
 * the D_80090F30 tail via four asm-label aliases (2 u16 + 2 u8 reads).
 * Remaining: one head register permutation (y0 t1 vs retail t0, slot a0 vs
 * v1, bankOff v0 vs a0), the case-1 exit pair (j join; move a1,zero)
 * cross-jumped away, and the sh store order. Permuter floor 605; term
 * reorder, decl swaps, and case-1 assignment order all neutral. */
extern s32 D_800A2EB4[];
extern u8 *D_800A3554;
extern u8 D_800B0B7C[];
extern u8 D_80090F2E[];
extern u16 D_80090F30b[] asm("D_80090F30");
extern u16 D_80090F30c[] asm("D_80090F30");
extern u8 D_80090F30d[] asm("D_80090F30");
extern u8 D_80090F30e[] asm("D_80090F30");
extern void AddPrim(void *ot, void *p);
void func_8001B82C(u8 *obj, s32 arg1)
{
  u8 *prim;
  s32 y0;
  s32 y1;
  s32 uOff;
  int new_var;
  u32 width;
  s32 mode;
  new_var = (gOrderingTableBankAbsolute[0] >> 1) * 0x3C0;
  y0 = 0x12C - ((*((s32 *) obj)) / arg1);
  y1 = ((*((s32 *) (obj + 4))) / arg1) - -0x12;
  prim = new_var + (D_800B0B7C + ((*((s8 *) (obj + 0x376))) * 0x28));
  if ((*((s16 *) (obj + 0x1EC))) == 0)
  {
    width = 0xA;
    if (D_800A2EB4[0] >= 2)
    {
      uOff = ((*((s16 *) (obj + 0x1DE))) * 0x10) + 0x20;
    }
    else
    {
      uOff = 0x10;
    }
  }
  else
  {
    mode = *((s8 *) (obj + 0x204));
    switch (mode)
    {
      case 2:
        width = 8;
        if (((*((s8 *) (D_800A3554 + 0x204))) == 1) && (D_800A2EB4[0] == (*((s8 *) (D_800A3554 + 0x204)))))
      {
        width = 0xA;
      }
        uOff = 0x30;
        break;

      case 1:
        width = 0xA;
        uOff = 0;
        break;

      case 3:
        width = 8;
        uOff = 0x40;
        break;

      default:
        width = 6;
        uOff = 0x60;
        break;

    }

  }
  *((s16 *) (prim + 8)) = (y0 -= width >> 1);
  y1 -= width >> 1;
  *((s16 *) (prim + 0x10)) = y0 + width;
  *((s16 *) (prim + 0x20)) = y0 + width;
  *((s16 *) (prim + 0xA)) = y1;
  *((s16 *) (prim + 0x12)) = y1;
  *((s16 *) (prim + 0x18)) = y0;
  *((s16 *) (prim + 0x1A)) = (*((s16 *) (prim + 0x22)) = y1 + width);
  prim[0xC] = uOff + D_80090F2E[0];
  prim[0xD] = D_80090F30b[0];
  prim[0x14] = (uOff + D_80090F2E[0]) + 0xF;
  prim[0x15] = D_80090F30c[0];
  prim[0x1C] = uOff + D_80090F2E[0];
  prim[0x1D] = D_80090F30d[0] + 0xF;
  prim[0x24] = (uOff + D_80090F2E[0]) + 0xF;
  prim[0x25] = D_80090F30e[0] + 0xF;
  AddPrim((void *) D_800A39C8[0], prim);
}
#else
INCLUDE_ASM("asm/nonmatchings/primitives_text", func_8001B82C);
#endif


INCLUDE_ASM("asm/nonmatchings/primitives_text", func_8001BA94);

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_8001BDBC);

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

extern s32 D_800A39C8Lui asm("D_800A39C8Absolute");
extern s32 gOrderingTableBankLui asm("gOrderingTableBankAbsolute");
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
        HudDrawCar(D_800A3554small, -0x6E);
        prim = *(s32 *)(D_800A3554small + 0x3E0);
        gOrderingTableBankLui = gOrderingTableBankLui + 1;
        D_800A39C8Lui = D_800A39C8Lui + 0x1004;
        func_8001AEDC(prim, -0x14);
        HudDrawCar(*(s32 *)(D_800A3554small + 0x3E0), -0x7D);
        gOrderingTableBankLui = gOrderingTableBankLui - 1;
        D_800A39C8Lui = D_800A39C8Lui - 0x1004;
        return;
    }
    func_8001AEDC(D_800A3554small, 0);
    HudDrawCar(D_800A3554small, 0);
    if (*(s8 *)(D_800A3554small + 0x209) == mode) {
        func_8001BA94(0);
    }
}
