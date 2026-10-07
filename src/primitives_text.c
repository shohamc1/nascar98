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

void func_80017D80(u8 *arg0) {
    typedef struct {
        s32 words[4];
    } Primitive16;
    extern u32 gPrimitiveCursor[];
    extern s32 D_800A39C8[];
    extern s32 D_800A36D0Absolute[];
    s32 cursorVal;
    u8 *entry;
    u8 *dst;
    u8 *end;
    s32 tailA;
    s32 tailB;

    end = arg0 + 0x20;
    cursorVal = gPrimitiveCursor[0];
    asm("");
    entry = (u8 *)cursorVal;
    dst = entry;
    asm volatile("" : : "r"(cursorVal));
    ((s32 *)D_800A36D0Absolute)[-67] = (s32)entry + 0x28;
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

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_80017E08);

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

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_800183C0);

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
    register s32 totalSeconds asm("a1");
    register s32 mode asm("a0");
    register s32 minutes asm("t0");
    register s32 seconds asm("t1");
    register s32 rem1000 asm("v1");
    register s32 msSign asm("v1");
    register s32 msShift asm("v0");
    register s32 millis asm("v0");
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

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_800188B0);

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

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_80018C88);

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
    ((s32 *)D_800A36D0Absolute)[-67] = cursor + 0x28;
    asm("");
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

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_80019C10);

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_8001A4D4);

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_8001A778);

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_8001AEDC);

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_8001B3F0);

INCLUDE_ASM("asm/nonmatchings/primitives_text", func_8001B82C);

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
