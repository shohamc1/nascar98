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
#include "objects.h"
#include "scene.h"
#include "graphics.h"
#include "util.h"
extern s32 D_800A2D8CAbsolute[];

void HudDrawTime(s32 time, s16 x, s16 y, s8 color, u8 mode);

extern s32 D_800A2EA8w15[] asm("D_800A2EA8.NON_MATCHING");
extern u8 D_800A2EE0w15[] asm("D_800A2EE0.NON_MATCHING");
extern s32 gSplitScreenModew15[] asm("gSplitScreenMode.NON_MATCHING");
extern s8 D_800A3620w18c[] asm("D_800A3620.NON_MATCHING");
extern s32 sprintf(char *, ...);

/* Primitives and text. */

extern s32 gPrimitiveCursorLui asm("gPrimitiveCursorAbsolute");
void GraphicsAddPolyFT4(u8 *arg0) {
    extern s32 gOrderingTable[];
    POLY_FT4 *entry;
    u32 cursor;

    cursor = gPrimitiveCursor[0];
    gPrimitiveCursorLui = cursor + 0x28;
    entry = (POLY_FT4 *)cursor;
    *entry = *(POLY_FT4 *)arg0;
    AddPrim((u8 *)gOrderingTable[0], entry);
}

void func_80017E08(void) {
    extern u8 D_800BA064[];
    extern u8 D_800BA8D4[];
    extern u8 D_800BB144[];
    extern u16 D_80090F0E[];
    POLY_FT4 *prim;
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
        prim = (POLY_FT4 *)(D_800BA064 + offsetA);
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        prim->r0 = shade;
        prim->g0 = shade;
        prim->b0 = shade;
        prim->tpage = GetTPage(2, 0, 0x300, 0);
        x0v = (12 * (i % 4)) + 0xD0;
        y0vA = (16 * (i / 4)) + 0x158;
        asm volatile("" : : "r"(i), "r"(offsetA));
        x1v = (12 * (i % 4)) + 0xDB;
        y2vA = (16 * (i / 4)) + 0x168;
        prim->u0 = x0v;
        prim->v0 = y0vA;
        prim->u2 = x0v;
        prim->u1 = x1v;
        prim->v1 = y0vA;
        prim->v2 = y2vA;
        prim->u3 = x1v;
        prim->v3 = y2vA;
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
        prim = (POLY_FT4 *)(D_800BA8D4 + offsetB);
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        do {
            cB = 0x80;
            prim->r0 = cB;
            prim->g0 = cB;
            prim->b0 = cB;
        } while (0);
        if (x1a < 0x100) {
            prim->tpage = GetTPage(2, 0, 0x100, 0);
            prim->u0 = x0a;
            prim->v0 = y0;
            prim->u1 = x1a;
            prim->v1 = y0;
            prim->u2 = x0a;
            prim->v2 = y2;
            prim->u3 = x1a;
            prim->v3 = y2;
        } else {
            prim->tpage = GetTPage(2, 0, 0x200, 0);
            prim->u0 = x0b;
            prim->v0 = y0;
            prim->u1 = x1b;
            prim->v1 = y0;
            prim->u2 = x0b;
            prim->v2 = y2;
            prim->u3 = x1b;
            prim->v3 = y2;
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
        prim = (POLY_FT4 *)(D_800BB144 + offsetC);
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        prim->r0 = rb;
        prim->g0 = 0x64;
        prim->b0 = rb;
        prim->clut = GetClut(table[0], table[1]);
        prim->tpage = GetTPage(table[4], 0, table[-2], table[-1]);
        xv = xbase + table[2];
        yv = table[3];
        yvDup = yv;
        prim->v0 = yvDup;
        prim->u1 = xv + 4;
        prim->u0 = xv;
        prim->u2 = xv;
        prim->v2 = yv + 7;
        prim->v3 = yv + 7;
        prim->v1 = yv;
        prim->u3 = xv + 4;
        xbase += 5;
        offsetC += 0x28;
    } while (++i < 0xC);
}

extern s16 gFontColorRed, gFontColorGreen, gFontColorBlue;
void FontDrawGlyph(s32 ch, s32 x, s32 y, s32 page) {
    extern s16 D_800A2D78[];
    extern s16 D_800A2D80[];
    extern u8 D_800BA064[];
    extern s32 gOrderingTable[];
    s32 w;
    s32 h;
    s8 tile;
    POLY_FT4 *src;
    s32 pageOffset;
    s32 tileAddr;
    POLY_FT4 *prim;
    s32 cursor;

    w = D_800A2D78[page];
    h = D_800A2D80[page];
    if ((u8)(ch - 0x30) >= 0xA) {
        if (page != 1) {
            if ((s8)ch == ':') {
                tile = 0xA;
            } else if ((s8)ch == '-') {
                tile = 0xB;
            } else {
                return;
            }
        } else {
            if ((u8)(ch - 0x61) < 0x1A) {
                tile = ch - 0x61;
            } else if ((u8)(ch - 0x41) < 0x1A) {
                tile = ch - 0x41;
            } else {
                switch ((s8)(ch - 0x21)) {
                case '.' - 0x21:
                    tile = 0x25;
                    break;
                case ',' - 0x21:
                    tile = 0x26;
                    break;
                case '-' - 0x21:
                    tile = 0x27;
                    break;
                case '+' - 0x21:
                    tile = 0x28;
                    break;
                case '#' - 0x21:
                    tile = 0x29;
                    break;
                case ':' - 0x21:
                    tile = 0x2A;
                    break;
                case '&' - 0x21:
                    tile = 0x2B;
                    break;
                case '?' - 0x21:
                    tile = 0x2C;
                    break;
                case '*' - 0x21:
                    tile = 0x2D;
                    break;
                case '(' - 0x21:
                    tile = 0x2E;
                    break;
                case ')' - 0x21:
                    tile = 0x2F;
                    break;
                case '$' - 0x21:
                    tile = 0x30;
                    break;
                case '@' - 0x21:
                    tile = 0x31;
                    break;
                case '!' - 0x21:
                    tile = 0x32;
                    break;
                case '"' - 0x21:
                    tile = 0x33;
                    break;
                case '\'' - 0x21:
                    tile = 0x34;
                    break;
                default:
                    tile = 0x1A;
                    break;
                }
            }
        }
    } else {
        if (page == 1) {
            tile = ch - 0x15;
        } else {
            tile = ch - 0x30;
        }
    }
    pageOffset = page * 0x870;
    tileAddr = tile * 0x28 + (s32)D_800BA064;
    src = (POLY_FT4 *)((u8 *)(pageOffset + tileAddr));
    *(u16 *)&src->x0 = x;
    *(u16 *)&src->y0 = y;
    *(u16 *)&src->x1 = x + w;
    *(u16 *)&src->y1 = y;
    *(u16 *)&src->x2 = x;
    *(u16 *)&src->y2 = y + h;
    *(u16 *)&src->x3 = x + w;
    *(u16 *)&src->y3 = y + h;
    src->r0 = gFontColorRed;
    src->g0 = gFontColorGreen;
    src->b0 = gFontColorBlue;
    cursor = gPrimitiveCursor[0];
    gPrimitiveCursorLui = cursor + 0x28;
    prim = (POLY_FT4 *)cursor;
    *prim = *src;
    AddPrim((u8 *)gOrderingTable[0], prim);
}

void FontSetColor(s16 red, s16 green, s16 blue) {
    gFontColorRed = red;
    gFontColorGreen = green;
    gFontColorBlue = blue;
}

extern s16 D_800A2D88[];

void FontDrawString(s8 *text, s32 x, s32 y, s32 scale) {
    s16 *width;
    s16 *base;
    s8 *p;

    if (*text != 0) {
        base = D_800A2D88;
        width = base + scale;
        p = text;
        do {
            FontDrawGlyph(*p, x, y, scale);
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
    TextFormatInt(minutes, (u8 *)text + len);
    text[2] = ':';
    text[3] = 0;
    len = 3;
    if (value < 10) {
        len = 4;
        text[3] = '0';
        text[4] = 0;
    }
    TextFormatInt(value, (u8 *)text + len);
    text[5] = ':';
    text[6] = 0;
    len = 6;
    if (hundredths < 10) {
        len = 7;
        text[6] = '0';
        text[7] = 0;
    }
    TextFormatInt(hundredths, (u8 *)text + len);
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
            FontDrawGlyph(*(s8 *)value, pen, y, scale);
            pen += *width;
            value++;
        } while (*(s8 *)value != 0);
    }
}

extern u8 gTimeInvalidText[];
extern u8 gTimeFormatSignedHms[];
extern u8 gTimeFormatSignedMinSecMs[];
extern u8 gTimeFormatSignedSecMs[];
extern u8 gTimeFormatHms[];
extern u8 gTimeFormatMinSecMs[];
extern s32 sprintfArgs(s8 *, u8 *, ...);
asm(".globl sprintfArgs\nsprintfArgs = sprintf");

void TextFormatTime(void *timeValue, s32 flags, s32 buffer) {
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
        *(TimeText10 *)out = *(TimeText10 *)gTimeInvalidText;
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
            sprintfArgs(out, gTimeFormatSignedHms, sign, hours, minutes,
                        seconds);
        } else if (minutes != 0) {
            sprintfArgs(out, gTimeFormatSignedMinSecMs, sign, minutes, seconds,
                        millis);
        } else {
            sprintfArgs(out, gTimeFormatSignedSecMs, sign, seconds, millis);
        }
    } else if (hours != 0) {
        sprintfArgs(out, gTimeFormatHms, hours, minutes, seconds);
    } else {
        sprintfArgs(out, gTimeFormatMinSecMs, minutes, seconds, millis);
    }
}

asm(".globl func_80050028Text\nfunc_80050028Text = HudDrawText");
__inline__ void func_80018768(void *arg0, s32 x, s32 y, s32 format) {
    s8 text[24];
    s8 *p;
    s16 *base;
    s16 *width;
    s8 *field;
    s32 pen;
    s32 scale;

    scale = format;
    TextFormatTime(arg0, scale, text);
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
            FontDrawGlyph(*field, pen, y, scale);
            pen += *width;
            field++;
        } while (*field != 0);
    }
}

extern void func_800183C0(s32, s32, s32, s32);
void TextDrawTwoObjectStrings(void *object, s32 x, s32 y) {
    s32 value;
    func_800183C0(((Car *)object)->unk258, x, y, 0);
    value = ((Car *)object)->time;
    if (value != 0x7FFFFFFF) {
        func_800183C0(value, x, y + 0x10, 0);
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
    TextFormatInt(value, text + indent);
    if (text[0] != 0) {
        i = 0;
        do {
            FontDrawGlyph(text[i], x, y, scale);
            x += D_800A2D88[scale];
            i++;
        } while (text[i] != 0);
    }
}

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
    TextFormatInt(value, text + indent);
    if (text[0] != 0) {
        i = 0;
        do {
            FontDrawGlyph(text[i], x, y, scale);
            x += D_800A2D88[scale];
            i++;
        } while (text[i] != 0);
    }
}

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
    TextFormatInt(value, start);
    pen = x;
    if (text[0] != 0) {
        base = D_800A2D88;
        width = base + scale;
        p = start;
        do {
            FontDrawGlyph(*p, pen, y, scale);
            pen += *width;
            p++;
        } while (*p != 0);
    }
}

void FontDrawNumber(s32 value, s32 x, s32 y, s32 scale) {
    s8 text[24];
    s8 *start;
    s16 *base;
    s16 *width;
    s8 *p;
    s32 pen;

    start = text;
    text[0] = 0;
    TextFormatLong(value, start);
    pen = x;
    if (text[0] != 0) {
        base = D_800A2D88;
        width = base + scale;
        p = start;
        do {
            FontDrawGlyph(*p, pen, y, scale);
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
        /* Keep phase-one constants inside this loop. */
        u = 0;
        v = 0;
        w = 0;
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

extern s32 gOrderingTable[];

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
        AddPrim((u8 *)gOrderingTable[0], poly);
    }
}

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

extern s16 D_800A2D8C;
extern s16 D_800A2D8A;
extern s8 gTimeBlankText[];
extern s8 *D_8009ADD8[];
extern void func_80025730(Car *);

/* Draw the car place, laps, speed, times, and panel primitives. */
void HudDrawCarPanel(Car *car, s32 bank, s32 hideTimes) {
    s8 text[24];
    register s32 byteValue asm("v1");
    s32 lapValue;
    void *helperTime;
    register s32 helperMode asm("a1");
    register s32 helperBuffer asm("a2");
    register POLY_FT4 *copyFrom asm("a2");
    POLY_FT4 *copyTo;
    u8 *copyEnd;
    register s32 numberArg asm("a0");
    s32 shiftedLap;
    register s8 *start asm("v1");
    register s8 *string asm("a0");
    s32 len;
    s32 number;
    register s32 lap asm("s4");
    s32 fixedSpeed;
    s32 yOffset;
    s32 i;
    s32 offset;
    s32 x;
    s32 y;
    s32 baseY;
    s32 width;
    register s32 right asm("v0");
    register s32 barX asm("a2");
    register s32 bankOffset asm("v1");
    register u8 *quadBase asm("v0");
    s32 bottom;
    s8 *p;
    register u8 *quad asm("s5");
    POLY_F4 *barQuad;
    s32 barY;
    POLY_FT4 *prim;
    u32 cursor;
    register s16 *glyphWidth asm("s4");
    s32 scale;

    if (car->cameraMode == 0 || D_800A2EACAbsolute[0] != 0) {
        return;
    }
    switch (car->unk209) {
    case 1:
    case 3:
        hideTimes = 1;
        break;
    }
    gFontColorRed = 60;
    gFontColorGreen = 100;
    gFontColorBlue = 60;
    byteValue = (u8)car->place;
    len = 0;
    yOffset = -(bank != 0) & 100;
    y = 135 - yOffset;
    /* Keep the byte conversion before the width tests. */
    asm("sll %1,%1,24\n\tsra %0,%1,24"
        : "=&r"(number), "=r"(byteValue)
        : "1"(byteValue));
    text[0] = 0;
    if (number < 1000) {
        len = 1;
        text[0] = ' ';
        text[1] = 0;
    }
    if (number < 100) {
        text[len++] = ' ';
        text[len] = 0;
    }
    if (number < 10) {
        text[len++] = ' ';
        text[len] = 0;
    }
    numberArg = number;
    p = text;
    TextFormatInt(numberArg, (u8 *)p + len);
    x = 8;
    if (text[0] != 0) {
        do {
            FontDrawGlyph(*p, x, y, 2);
            p++;
            x += D_800A2D8C;
        } while (*p != 0);
    }
    lap = car->lap;
    if (lap < 0)
        lap = 0;
    if (D_800A2EA8w15[0] < lap)
        lap = D_800A2EA8w15[0];
    len = 0;
    y = 135 - yOffset;
    /* Keep the full lap load before its signed halfword conversion. */
    asm("sll %0,%1,16" : "=r"(shiftedLap) : "r"(lap) : "memory");
    lapValue = shiftedLap >> 16;
    text[0] = 0;
    if (lapValue < 1000) {
        len = 1;
        text[0] = ' ';
        text[1] = 0;
    }
    if (lapValue < 100) {
        text[len++] = ' ';
        text[len] = 0;
    }
    if (lapValue < 10) {
        text[len++] = ' ';
        text[len] = 0;
    }
    numberArg = lapValue;
    p = text;
    TextFormatInt(numberArg, (u8 *)p + len);
    x = 23;
    if (text[0] != 0) {
        do {
            FontDrawGlyph(*p, x, y, 2);
            p++;
            x += D_800A2D8C;
        } while (*p != 0);
    }
    baseY = 135 - yOffset;
    FontDrawGlyph('-', 47, baseY, 2);
    numberArg = D_800A2EA8w15[0];
    text[0] = 0;

    TextFormatInt((s16)numberArg, (u8 *)text);
    x = 53;
    y = baseY;
    start = text;
    if (text[0] != 0) {
        p = start;
        do {
            FontDrawGlyph(*p, x, y, 2);
            p++;
            x += D_800A2D8C;
        } while (*p != 0);
    }
    fixedSpeed = car->speed;
    y = 181 - yOffset;
    byteValue = car->unkF7;
    if (fixedSpeed < 0)
        fixedSpeed = 0;
    /* Retail keeps this mask after the byte load. */
    byteValue &= 255;
    if (byteValue == 1)
        number = ((fixedSpeed >> 16) * 336) / 550;
    else
        number = ((fixedSpeed >> 16) * 210) / 550;
    len = 0;
    text[0] = 0;
    if (number < 100) {
        len = 1;
        text[0] = ' ';
        text[1] = 0;
    }
    if (number < 10) {
        text[len++] = ' ';
        text[len] = 0;
    }
    numberArg = number;
    p = text;
    TextFormatInt(numberArg, (u8 *)p + len);
    x = 34;
    if (text[0] != 0) {
        do {
            FontDrawGlyph(*p, x, y, 2);
            p++;
            x += D_800A2D8C;
        } while (*p != 0);
    }
    FontDrawGlyph((s8)((u8)car->gearIndex + '1'), 60, 190 - yOffset, 2);
    if (hideTimes == 0) {
        helperTime = (void *)car->unk258;
        helperMode = 2;
        helperBuffer = (s32)text;
        asm("" : : "r"(helperTime), "r"(helperMode), "r"(helperBuffer));
        y = 135 - yOffset;
        TextFormatTime(helperTime, helperMode, helperBuffer);
        x = 252;
        scale = 2;
        start = text;
        if (text[0] != 0) {
            glyphWidth = (s16 *)&D_800A2D8CAbsolute[0];
            p = start;
            do {
                FontDrawGlyph(*p, x, y, scale);
                p++;
                x += *glyphWidth;
            } while (*p != 0);
        }
        helperTime = (void *)car->time;
        helperMode = 2;
        if ((s32)helperTime != 0x7FFFFFFF) {
            helperBuffer = (s32)text;
            asm("" : : "r"(helperTime), "r"(helperMode), "r"(helperBuffer));
            y = 159 - yOffset;
            TextFormatTime(helperTime, helperMode, helperBuffer);
            x = 252;
            scale = 2;
            start = text;
            if (text[0] != 0) {
                glyphWidth = (s16 *)&D_800A2D8CAbsolute[0];
                p = start;
                do {
                    FontDrawGlyph(*p, x, y, scale);
                    p++;
                    x += *glyphWidth;
                } while (*p != 0);
            }
        } else {
            x = 258;
            y = 159 - yOffset;
            string = gTimeBlankText;
            if (*string != 0) {
                p = string;
                do {
                    FontDrawGlyph(*p, x, y, 2);
                    p++;
                    x += D_800A2D8C;
                } while (*p != 0);
            }
        }
        func_800183C0(car->unk260, 258, 183 - yOffset, 2);
    }
    i = 17;

    offset = 680;
    do {
        bankOffset = bank * 720;
        quadBase = offset + (u8 *)D_800AE29C;
        quad = (u8 *)(bankOffset + (s32)quadBase);
        barQuad = (POLY_F4 *)quad;
        switch (i) {
        case 2:
            func_80019A00(car->rpm, quad, bank);
            goto queue;
        case 8:
            if (car->wheel[0].unkC > 0xCE400)
                goto next;
            goto queue;
        case 13:
            width = (car->unk28C * 34) / 16000;
            barY = 204;
            barX = 31;
            if (bank != 0)
                barY = 104;
            if (width >= 34)
                width = 33;
            right = width + 31;
            width = 31;
            asm("" : "=r"(width) : "0"(width));
            barQuad->x2 = width;
            barQuad->x0 = barX;
            bottom = barY + 2;
            barQuad->y0 = barY;
            barQuad->x1 = right;
            barQuad->y1 = barY;
            barQuad->y2 = bottom;
            barQuad->x3 = right;
            barQuad->y3 = bottom;
            goto queue;
        case 4:
        case 5:
        case 6:
        case 10:
        case 11:
        case 12:
            if (hideTimes != 0)
                goto next;
            goto queue;
        case 15:
            if (car->unk28C > 0)
                goto next;
            goto queue;
        case 16:
            if (car->segment == -1)
                break;
            if (MathGetAngleDelta(
                    car->heading,
                    ((TrackSection *)gTrackSections[0])[car->segment].angle) <
                0) {
                if (-MathGetAngleDelta(
                        car->heading,
                        ((TrackSection *)gTrackSections[0])[car->segment]
                            .angle) < 300)
                    goto next;
            } else {
                if (MathGetAngleDelta(
                        car->heading,
                        ((TrackSection *)gTrackSections[0])[car->segment]
                            .angle) < 300)
                    goto next;
            }
            goto queue;
        case 17:
            if (D_800A2EE0w15[0] == 0 || D_800A2EC8[0] != 0)
                break;
            if (car->unk3B7 != 0 || (car->unk3A4 & 15) == 0) {
                if (*(void (**)(u8 *))((u8 *)car + 0x354) != func_80025730 ||
                    car->unk1BC != 4)
                    break;
            }
            string = D_8009ADD8[0];
            x = 85;
            y = 142 - yOffset;
            if (*string != 0) {
                p = string;
                do {
                    FontDrawGlyph(*p, x, y, 1);
                    p++;
                    x += D_800A2D8A;
                } while (*p != 0);
            }
            goto queue;
        default:
        queue:
            cursor = gPrimitiveCursor[0];
            copyFrom = (POLY_FT4 *)quad;
            copyEnd = (u8 *)copyFrom + 32;
            asm("" : "=r"(prim) : "0"(cursor));
            copyTo = prim;
            gPrimitiveCursorLui = (u32)prim + 40;
            asm("" : "=r"(copyTo) : "r"(copyFrom), "0"(copyTo));
            *copyTo = *copyFrom;

            AddPrim((u8 *)gOrderingTable[0], prim);
            break;
        }
    next:
        i--;
        offset -= 40;
    } while (i >= 0);
    gFontColorRed = 128;
    gFontColorGreen = 128;
    gFontColorBlue = 128;
}

extern u8 *D_8009AE50[];
extern void GraphicsSetColor(s32, s32, s32);
extern void HudDrawText(u8 *, s32, s32, s8);
extern void GraphicsDrawRect();
extern void MenuDrawArrow(s32 x, s32 y, s32 dir, s32 size);
extern void GraphicsDrawDoubleBorderRect(s16 x, s16 y, s16 width, s16 height,
                                         u8 red, u8 green, u8 blue,
                                         u8 semiTrans);
void MenuDrawPauseListPanel(void *unused, s32 selection, u8 flags, s32 y) {
    s8 i;
    s32 cursorY;

    GraphicsSetColor(128, 128, 128);
    i = 0;
    do {
        HudDrawText(D_8009AE50[i], 90, (s16)(y + 40 + i * 12), 0);
        i++;
    } while (i < 4);
    if (flags & 1) {
        GraphicsDrawRect(83, y + 39, 154, 1, -128, -128, -1, 1);
        GraphicsDrawRect(82, y + 40, 156, 1, -128, -128, -1, 1);
        GraphicsDrawRect(81, y + 41, 158, 10, -128, -128, -1, 1);
    }
    if (flags & 2) {
        GraphicsDrawRect(81, y + 51, 158, 12, -128, -128, -1, 1);
    }
    if (flags & 4) {
        GraphicsDrawRect(81, y + 63, 158, 12, -128, -128, -1, 1);
    }
    if (flags & 8) {
        GraphicsDrawRect(81, y + 75, 158, 11, -128, -128, -1, 1);
        GraphicsDrawRect(82, y + 86, 156, 1, -128, -128, -1, 1);
        GraphicsDrawRect(83, y + 87, 154, 1, -128, -128, -1, 1);
    }
    GraphicsDrawDoubleBorderRect(81, (s16)(y + 40), 158, 48, 0, 0, 0, 1);
    cursorY = selection * 12;
    MenuDrawArrow(79, y + 45 + cursorY, 0, 5);
    MenuDrawArrow(240, y + 45 + cursorY, 1, 5);
}

extern u8 *D_8009AD60[][6];
extern u8 *D_8009AD6C[][6];
extern u8 *D_8009ADA8[];
extern u8 *D_8009ADAC[];
extern u8 *D_8009ADB4[];
extern u8 *D_8009ADBC[];
extern u8 *D_8009ADCC[];
extern u8 *D_8009ADD0;
extern u8 *D_8009ADD4;
extern s16 gCdVolumeAbsolute[];
extern s16 gMusicVolumeAbsolute[];
extern s8 D_800A39F0[];
extern s32 gSessionTypepanel asm("gSessionTypeAbsolute");
extern u8 D_800A2F9Cpanel asm("D_800A2F9CAbsolute");
extern u8 D_800A2F9Dpanel asm("D_800A2F9DAbsolute");
extern u8 D_800A306Cpanel asm("D_800A306CAbsolute");
extern u8 D_800A306Dpanel asm("D_800A306DAbsolute");
extern s32 gOrderingTableLui asm("gOrderingTableAbsolute");
extern void MenuDrawStatistics(void);
extern void MenuDrawTimingAndScoring(void);
void MenuDrawPausePanel(void *unused, s32 selection, s32 flags) {
    s32 frameExtent[2];
    s32 y;
    s32 arrowX;
    s8 i;
    s32 index;
    s32 offset;
    s32 x;
    s32 rowY;
    s32 rowY2;
    s32 rowY3;
    s32 cursorY;
    s32 rowBias;
    s32 arrowArg;
    s32 volumeLimit;
    u8 **labels;
    u8 **choices;
    u8 **volumeChoices;
    register u8 **volumeLabels asm("s2");

    y = 40;
    arrowX = 80;
    if (flags & 8) {
        MenuDrawStatistics();
        return;
    }
    if (flags & 4) {
        MenuDrawTimingAndScoring();
        return;
    }
    if (gSplitScreenModew15[0] != 0) {
        y = 20;
        if (D_800A3620w18c[0] != 0) {
            gOrderingTableLui += 0x1004;
        } else {
            y = 30;
        }
    }
    GraphicsSetColor(128, 128, 128);
    switch (D_800A39F0[0]) {
    case 0:
        i = 0;
        labels = (u8 **)D_8009AD60;
        do {
            /* Keep the signed byte index in one register. */
            index = (u32)i << 24;
            index >>= 24;
            offset = index * 4;
            x = (s16)(((u32)(158 - HudTextWidth(*(
                                       u8 **)(offset + (gSessionTypepanel * 24 +
                                                        (s32)labels)))) >>
                       1) +
                      81);
            offset += gSessionTypepanel * 24 + (s32)labels;
            HudDrawText(*(u8 **)offset, x, index * 12 + y, 0);
            i++;
        } while ((s8)i < 2);
        i = 4;
        labels = (u8 **)D_8009AD60;
        do {
            /* Keep the signed byte index in one register. */
            asm("sll %0,%1,24\n\tsra %0,%0,24" : "=r"(index) : "r"(i));
            offset = index * 4;
            x = (s16)(((u32)(158 - HudTextWidth(*(
                                       u8 **)(offset + (gSessionTypepanel * 24 +
                                                        (s32)labels)))) >>
                       1) +
                      81);
            offset += gSessionTypepanel * 24 + (s32)labels;
            HudDrawText(*(u8 **)offset, x, index * 12 + y, 0);
            i++;
        } while ((s8)i < 6);
        if (gSessionTypepanel == 2) {
            GraphicsSetColor(32, 32, 32);
        }
        x = (s16)(((u32)(158 -
                         HudTextWidth(D_8009AD68[gSessionTypepanel][0])) >>
                   1) +
                  81);
        HudDrawText(D_8009AD68[gSessionTypepanel][0], x, y + 24, 0);
        GraphicsSetColor(128, 128, 128);
        if (gSplitScreenModew15[0] != 0) {
            GraphicsSetColor(32, 32, 32);
        }
        x = (s16)(((u32)(158 -
                         HudTextWidth(D_8009AD6C[gSessionTypepanel][0])) >>
                   1) +
                  81);
        HudDrawText(D_8009AD6C[gSessionTypepanel][0], x, y + 36, 0);
        break;
    case 1:
        choices = D_8009ADA8;
        rowY = y;
        asm("" : "=r"(rowY) : "0"(rowY));
        HudDrawText(choices[0], 90, rowY, 0);
        choices += 5;
        cursorY = 13;
        x = (s16)(230 - HudTextWidth(choices[D_800A2F9Dpanel]));
        HudDrawText(choices[D_800A2F9Dpanel], x, rowY, 0);
        GraphicsDrawRect(110, y + cursorY, gMusicVolumeAbsolute[0], 8, 0, 0,
                         D_800A2F9Dpanel ? -128 : 0, 1);
        GraphicsDrawRect(109, y + 12, 102, 10, -1, -1, -1, 1);
        rowY2 = y + 24;
        HudDrawText(D_8009ADAC[D_800A306Dpanel], 90, rowY2, 0);
        x = (s16)(230 - HudTextWidth(D_8009ADBC[D_800A2F9Cpanel]));
        HudDrawText(D_8009ADBC[D_800A2F9Cpanel], x, rowY2, 0);
        GraphicsDrawRect(110, y + 37, gCdVolumeAbsolute[0], 8, 0, 0,
                         D_800A2F9Cpanel ? -128 : 0, 1);
        GraphicsDrawRect(109, y + 36, 102, 10, -1, -1, -1, 1);
        rowY3 = y + 48;
        volumeLabels = D_8009ADB4;
        asm("" : "=r"(volumeLabels) : "0"(volumeLabels));
        HudDrawText(volumeLabels[0], 90, rowY3, 0);
        volumeLimit = 8;
        volumeChoices = volumeLabels - 3;
        x = (s16)(230 -
                  HudTextWidth(volumeChoices[volumeLimit - D_800A306Cpanel]));
        HudDrawText(volumeChoices[volumeLimit - D_800A306Cpanel], x, rowY3, 0);
        x = (s16)(((u32)(158 - HudTextWidth(volumeLabels[1])) >> 1) + 81);
        HudDrawText(volumeLabels[1], x, y + 60, 0);
        break;
    case 2:
        x = (s16)(((u32)(158 - HudTextWidth(D_8009ADCC[0])) >> 1) + 81);
        HudDrawText(D_8009ADCC[0], x, y + 12, 0);
        x = (s16)(((u32)(158 - HudTextWidth(D_8009ADD0)) >> 1) + 81);
        HudDrawText(D_8009ADD0, x, y + 36, 0);
        x = (s16)(((u32)(158 - HudTextWidth(D_8009ADD4)) >> 1) + 81);
        HudDrawText(D_8009ADD4, x, y + 48, 0);
        break;
    }
    GraphicsDrawDoubleBorderRect(81, y - 1, 158, 73, 0, 0, 0, 1);
    arrowArg = arrowX - 1;
    asm("" : : "r"(arrowArg));
    cursorY = selection * 12;
    rowBias = y + 5;
    cursorY += rowBias;
    MenuDrawArrow(arrowArg, cursorY, 0, 5);
    MenuDrawArrow(arrowX | 160, cursorY, 1, 5);
    if (D_800A3620w18c[0] != 0) {
        gOrderingTableLui -= 0x1004;
    }
    /* Compiler control: preserve the retail frame extent. */
}

extern s32 D_800A2EAC[];
extern u8 gFormatIntegerDotInteger[];
extern u8 gTextPitTuningNegativeSign[];
extern u8 gTextPitTuningPositiveSign[];
extern u8 gTextColorAbs asm("gTextColorAbsolute");

/* Draws the pit-stop menu for a car in the pits: the rear spoiler (+0x2AA)
 * and wedge (+0x2A4) settings as signed half-unit "%i.%i" readouts, the fuel
 * time (+0x27E), the four row labels, highlight boxes for the chosen services
 * (+0x26A bits) and the cursor arrows for row +0x26B. */
void HudDrawPitMenu(Car *car, s32 y) {
    u8 text[0x18];
    s32 wedgeY;
    s16 value;
    s8 i;
    s32 fuelTime;
    s32 setting;
    s32 spoiler;

    if (D_800A2EC8[0] != 0) {
        return;
    }
    if (D_800A2EAC[0] != 0) {
        return;
    }
    if (D_800A2EE0w15[0] == 0 && (*(s32 *)&car->unk3A4 & 0x100F)) {
        return;
    }
    if (car->unk268 == 0) {
        return;
    }
    if (car->unk269 == 2) {
        return;
    }
    if (car->unk269 == 0xFF) {
        return;
    }
    GraphicsSetColor(0x80, 0xC0, 0x80);

    setting = car->unk2AA;
    value = setting;
    if (setting >= 0) {
        i = value;
    } else {
        i = -value;
    }
    sprintfArgs((s8 *)text, gFormatIntegerDotInteger, i >> 1, (i % 2) * 5);
    HudDrawText(text, 0xD2, (s16)(y + 0x40), 0);

    setting = car->unk2A4;
    value = setting;
    if (setting >= 0) {
        i = value;
    } else {
        i = -value;
    }
    sprintfArgs((s8 *)text, gFormatIntegerDotInteger, i >> 1, (i % 2) * 5);
    wedgeY = (s16)(y + 0x4C);
    HudDrawText(text, 0xD2, wedgeY, 0);

    spoiler = car->unk2AA;
    gTextColorAbs = 9;
    HudDrawText(spoiler < 0 ? gTextPitTuningNegativeSign
                            : gTextPitTuningPositiveSign,
                0xC8, (s16)(y + 0x40), 0);
    HudDrawText(car->unk2A4 < 0 ? gTextPitTuningNegativeSign
                                : gTextPitTuningPositiveSign,
                0xC8, wedgeY, 0);

    fuelTime = (s16)car->unk26C[9];
    if (fuelTime > 0) {
        HudDrawTime(fuelTime, 0x78, (s16)(y + 0x64), 0, 2);
        GraphicsDrawDoubleBorderRect(0x6E, (s16)(y + 0x63), 0x64, 0xC, 0, 0, 0,
                                     1);
    }

    gTextColorAbs = 0;
    GraphicsSetColor(0x80, 0x80, 0x80);

    i = 0;
    do {
        HudDrawText(D_8009AE50[i], 0x5A, (s16)(y + 0x28 + i * 12), 0);
        i++;
    } while (i < 4);
    if (car->unk26A & 1) {
        GraphicsDrawRect(0x53, y + 0x27, 0x9A, 1, 0x40, 0x40, -0x80, 1);
        GraphicsDrawRect(0x52, y + 0x28, 0x9C, 1, 0x40, 0x40, -0x80, 1);
        GraphicsDrawRect(0x51, y + 0x29, 0x9E, 10, 0x40, 0x40, -0x80, 1);
    }
    if (car->unk26A & 2) {
        GraphicsDrawRect(0x51, y + 0x33, 0x9E, 12, 0x40, 0x40, -0x80, 1);
    }
    if (car->unk26A & 8) {
        GraphicsDrawRect(0x51, y + 0x3F, 0x9E, 12, 0x40, 0x40, -0x80, 1);
    }
    if (car->unk26A & 4) {
        GraphicsDrawRect(0x51, y + 0x4B, 0x9E, 11, 0x40, 0x40, -0x80, 1);
        GraphicsDrawRect(0x52, y + 0x56, 0x9C, 1, 0x40, 0x40, -0x80, 1);
        GraphicsDrawRect(0x53, y + 0x57, 0x9A, 1, 0x40, 0x40, -0x80, 1);
    }
    GraphicsDrawDoubleBorderRect(0x51, (s16)(y + 0x27), 0x9E, 0x31, 0, 0, 0, 1);
    if (car->unk269 < 2) {
        MenuDrawArrow(0x4F, y + 0x2D + car->unk26B * 12, 0, 5);
        MenuDrawArrow(0xF0, y + 0x2D + car->unk26B * 12, 1, 5);
    }
}

/* Draws one 16x24 replay button quad at (x, y) and queues a copy. */
static inline void ReplayDrawButton(POLY_FT4 *poly, s16 x, s16 y) {
    POLY_FT4 *prim;
    u32 cursor;

    cursor = gPrimitiveCursor[0];
    gPrimitiveCursorLui = cursor + 0x28;
    prim = (POLY_FT4 *)cursor;
    setXYWH(poly, x, y, 16, 24);
    *prim = *poly;
    AddPrim((u8 *)gOrderingTable[0], prim);
}

/* Draws the instant-replay control buttons. A set bit in D_800A2DFC
   picks the lit variant, six quads before the unlit one. */
void ReplayDrawControls(void) {
    extern u32 D_800A2DFC[];
    extern POLY_FT4 D_800BC4AC[];
    extern POLY_FT4 D_800BC4FC[];
    extern POLY_FT4 D_800BC4D4[];
    extern POLY_FT4 D_800BC524[];
    extern POLY_FT4 D_800BC45C[];
    POLY_FT4 *poly;
    s32 x;
    s32 y;
    s16 buttonX;

    if (D_800A3620w18c[0] != 0) {
        gOrderingTableLui += 0x1004;
        x = -10;
        y = -10;
    } else {
        x = -10;
        y = 0;
    }
    buttonX = x + 60;
    poly = D_800BC4AC;
    if (D_800A2DFC[0] & 1) {
        poly -= 6;
    }
    ReplayDrawButton(poly, buttonX, y + 20);
    buttonX = x + 40;
    poly = D_800BC4FC;
    if (D_800A2DFC[0] & 2) {
        poly -= 6;
    }
    ReplayDrawButton(poly, buttonX, y + 35);
    buttonX = x + 80;
    poly = D_800BC4D4;
    if (D_800A2DFC[0] & 4) {
        poly -= 6;
    }
    ReplayDrawButton(poly, buttonX, y + 35);
    buttonX = x + 60;
    poly = D_800BC524;
    if (D_800A2DFC[0] & 8) {
        poly -= 6;
    }
    ReplayDrawButton(poly, buttonX, y + 50);
    buttonX = x + 20;
    ReplayDrawButton(D_800BC45C, buttonX, y + 35);
    if (D_800A3620w18c[0] != 0) {
        gOrderingTableLui -= 0x1004;
    }
}

extern Car *gPlayerCar;
extern u16 D_80090F30b[] asm("D_80090F30");
extern u16 D_80090F30c[] asm("D_80090F30");
extern u8 D_80090F30d[] asm("D_80090F30");
extern u8 D_80090F30e[] asm("D_80090F30");
extern void AddPrim(void *ot, void *p);
void func_8001B82C(Car *obj, s32 arg1) {
    POLY_FT4 *prim;
    s32 x;
    s32 y;
    u8 uOff;
    u32 width;
    s32 mode;

    x = 300 - *(s32 *)obj / arg1;
    y = obj->pos.y / arg1 + 18;
    prim =
        (POLY_FT4 *)(D_800B0B7C + (gOrderingTableBankAbsolute[0] >> 1) * 0x3C0 +
                     (s8)obj->driver * 0x28);
    if (obj->type == 0) {
        width = 10;
        if (D_800A2EB4[0] >= 2) {
            uOff = obj->unk1DE * 16 + 32;
        } else {
            uOff = 16;
        }
    } else {
        mode = obj->place;
        switch (mode) {
        case 1:
            width = 10;
            uOff = 0;
            break;
        case 2:
            width = 8;
            if (gPlayerCar->place == 1 && D_800A2EB4[0] == gPlayerCar->place) {
                width = 10;
            }
            uOff = 48;
            break;
        case 3:
            width = 8;
            uOff = 64;
            break;
        default:
            width = 6;
            uOff = 96;
            break;
        }
    }
    x -= width >> 1;
    y -= width >> 1;
    prim->x0 = x;
    prim->y0 = y;
    prim->x1 = x + width;
    prim->y1 = y;
    prim->x2 = x;
    prim->y2 = y + width;
    prim->x3 = x + width;
    prim->y3 = y + width;
    prim->u0 = uOff + D_80090F2E[0];
    prim->v0 = D_80090F30b[0];
    prim->u1 = uOff + D_80090F2E[0] + 15;
    prim->v1 = D_80090F30c[0];
    prim->u2 = uOff + D_80090F2E[0];
    prim->v2 = D_80090F30d[0] + 15;
    prim->u3 = uOff + D_80090F2E[0] + 15;
    prim->v3 = D_80090F30e[0] + 15;
    AddPrim((void *)gOrderingTable[0], prim);
}

extern s32 D_801F3FFC[];
extern s32 D_800A2ED0[];
extern void *D_800A35E0;
extern void func_8001B82C(Car *obj, s32 arg1);
void func_8001BA94(s32 arg0) {
    s32 shade;
    u8 mode;
    POLY_F4 *tile;
    Car *node;
    s32 cursor;
    POLY_FT4 *prim;
    s32 xy0;
    s32 xy1;
    s32 xy2;
    s32 xy3;
    s32 idx;
    s32 off;
    s32 count;
    s32 stride;
    s32 i;
    s32 j;

    mode = arg0;
    if (mode == 0) {
        if (D_800A2ED0[0] != 0) {
            return;
        }
        if (D_800A2EACAbsolute[0] != 0) {
            return;
        }
    }
    off = D_801F3FF8[0] * 4;
    count = D_801F3FFC[0];
    if (mode == 0) {
        func_8001B82C(gPlayerCar, off);
        if (D_800A2E94[0] >= 2) {
            node = D_800A35E0;
            for (i = 0; i < D_800A2E94[0]; i++) {
                if (node != gPlayerCar) {
                    func_8001B82C(node, off);
                }
                node = ((CarLink *)node->order.node.previous)->car;
            }
        }
    }
    stride = ((gOrderingTableBankAbsolute[0] / 2) + 1) * 24;
    tile = (u8 *)(RAM_CACHED_BASE |
                  (RAM_RESOURCE_BOUNDARY - 8 - (count * stride)));
    for (j = 0; j < count; j++) {
        shade = 0x80;
        tile->tag = 0x05000000;
        if (mode != 0) {
            tile->r0 = shade;
            tile->g0 = 0xC0;
            tile->b0 = shade;
            idx = D_800A2CE0[0] * 2;
            xy0 = *(u32 *)&tile->x0;
            tile->x0 -= D_80099230[idx];
            tile->y0 += D_80099231[idx];
            xy1 = *(u32 *)&tile->x1;
            tile->x1 -= D_80099230[idx];
            tile->y1 += D_80099231[idx];
            xy2 = *(u32 *)&tile->x2;
            tile->x2 -= D_80099230[idx];
            tile->y2 += D_80099231[idx];
            cursor = gPrimitiveCursorLui;
            xy3 = *(u32 *)&tile->x3;
            tile->x3 -= D_80099230[idx];
            tile->y3 += D_80099231[idx];
            prim = (POLY_FT4 *)cursor;
            gPrimitiveCursorLui = cursor + 0x28;
            *prim = *(POLY_FT4 *)tile;
            AddPrim((void *)gOrderingTable[0], prim);
            *(u32 *)&tile->x0 = xy0;
            *(u32 *)&tile->x1 = xy1;
            *(u32 *)&tile->x2 = xy2;
            *(u32 *)&tile->x3 = xy3;
            tile->r0 = 0;
            tile->g0 = 0;
            tile->b0 = 0;
        } else {
            AddPrim((void *)gOrderingTable[0], tile);
        }
        tile++;
    }
}

extern s32 D_800A2E90[];
extern s32 D_800A3848;
extern s32 D_800B0B1C[];
extern void HudDrawTime(s32, s16, s16, s8, u8);
extern u8 *D_8009AE04[];
extern u8 *D_8009AE08[];
extern u8 *D_8009ADF4[];
extern s32 D_8009ADEC[];
extern s32 D_8009ADF0[];
extern char gFormatIntegerSpaceString[];

void MenuDrawResults(s32 reset) {
    char text[64];
    s32 slide;
    s32 baseY;
    s32 i;
    s32 off;
    void *node;
    s32 *times;
    s32 *timeBase;
    s32 rowY;

    if (gSessionTypeAbsolute[0] == 2) {
        return;
    }
    if (reset != 0) {
        D_800A3848 = 0;
    } else {
        D_800A3848 += 1;
    }
    if (D_800A3848 < 0x14) {
        slide = (D_800A3848 * 0x14) - 0x140;
        baseY = 0;
    } else if (D_800A3848 < 0xA0) {
        slide = (D_800A3848 * 0x14) - 0x140;
        baseY = 0;
    } else {
        slide = (D_800A3848 * 0x14) - 0x140;
        if (D_800A3848 >= 0x1D7) {
            D_800A3848 = 0x1D6;
        }
        baseY = (0xA0 - D_800A3848) / 2;
    }
    gOrderingTableLui += 8;
    i = 0;
    do {
        GraphicsDrawRect(0, 0, 0x140, 0xF0, 0, 0, 0, 1);
        i += 1;
    } while (i < 2);
    off = slide;
    gOrderingTableLui -= 8;
    if (off > 0) {
        off = 0;
    }
    timeBase = D_800B0B1C;
    GraphicsSetColor(0xFF, 0x80, 0x40);
    if (gSessionTypeAbsolute[0] == 0) {
        func_80050028Text(D_8009AE04[0], (s16)(off + 0x78), (s16)(baseY + 0x18),
                          0);
        node = D_800A35E0;
        i = 0;
        timeBase = D_800B0B1C;
        if (D_800A2E90[0] >= 0) {
            times = timeBase;
            do {
                off = slide - ((i + 1) * 0x78);
                if (off < -0x3E8) {
                    off = -0x3E8;
                }
                if (off > 0) {
                    off = 0;
                }
                if (!(i & 1)) {
                    off = -off;
                }
                if (off == 0 && ((Car *)node)->type == 0 &&
                    D_800A2E94[0] >= 3) {
                    gOrderingTableLui += 4;
                    GraphicsDrawRect(0, baseY + (i * 0xE) + 0x25, 0x140, 0xF, 0,
                                     0, -1, 1);
                    gOrderingTableLui -= 4;
                }
                TextFormatInt(i + 1, text);
                func_80050028Text(text, (s16)(off + 0x10),
                                  (s16)(baseY + (i * 0xE) + 0x28), 0);
                func_80050028Text(*(u8 **)&((Car *)node)->name,
                                  (s16)(off + 0x32),
                                  (s16)(baseY + (i * 0xE) + 0x28), 0);
                if (times[i] > -1) {
                    if (i == 0) {
                        func_80018768(timeBase[0], off + 0xD2,
                                      baseY + (i * 0xE) + 0x28, -3);
                    } else {
                        func_80018768(times[i], off + 0xD2,
                                      baseY + (i * 0xE) + 0x28, 3);
                    }
                } else if (times[i] != -1) {
                    if (times[i] + 1 == -1) {
                        sprintf(text, gFormatIntegerSpaceString, -1,
                                D_8009ADF0[0]);
                    } else {
                        sprintf(text, gFormatIntegerSpaceString, times[i] + 1,
                                D_8009ADEC[0]);
                    }
                    func_80050028Text(text, (s16)(off + 0xD2),
                                      (s16)(baseY + (i * 0xE) + 0x28), 0);
                } else {
                    func_80050028Text(D_8009ADF4[0], (s16)(off + 0xD2),
                                      (s16)(baseY + (i * 0xE) + 0x28), 0);
                }
                i++;
                node = *(void **)((u8 *)*(void **)&((Car *)node)
                                      ->order.node.previous +
                                  8);
            } while (D_800A2E90[0] >= i);
        }
    } else {
        func_80050028Text(D_8009AE08[0], (s16)(off + 0x78), (s16)(baseY + 0x18),
                          0);
        i = 0;
        do {
            off = slide - ((i + 1) * 0x78);
            if (off < -0x3E8) {
                off = -0x3E8;
            }
            if (off > 0) {
                off = 0;
            }
            if (!(i & 1)) {
                off = -off;
            }
            if (off == 0 && i == gPlayerCar->place - 1) {
                rowY = baseY + i * 0xE;
                gOrderingTableLui += 4;
                GraphicsDrawRect(0, rowY + 0x25, 0x140, 0xF, 0, 0, -1, 1);
                gOrderingTableLui -= 4;
            }
            TextFormatInt(i + 1, text);
            func_80050028Text(text, (s16)(off + 0x10),
                              (s16)(baseY + (i * 0xE) + 0x28), 0);
            func_80050028Text(gDriverNames[gDriverOrder[i]], (s16)(off + 0x32),
                              (s16)(baseY + (i * 0xE) + 0x28), 0);
            HudDrawTime(timeBase[i], (s16)(off + 0xD2),
                        (s16)(baseY + (i * 0xE) + 0x28), 0, 1);
            i++;
        } while (i < 0x18);
    }
}

extern s32 D_800A2EC8nm[] asm("D_800A2EC8.NON_MATCHING");
extern u8 D_800A2EDAnm[] asm("D_800A2EDA.NON_MATCHING");
extern s32 D_800A2EC0nm[] asm("D_800A2EC0.NON_MATCHING");
extern u8 *D_8009AE40nm[] asm("D_8009AE40.NON_MATCHING");
extern s32 D_800A359Cnm[] asm("D_800A359C.NON_MATCHING");
extern s32 D_800A3848small asm("D_800A3848.NON_MATCHING");
extern u8 D_800A2D0Cnm[] asm("D_800A2D0C.NON_MATCHING");
extern u8 *D_800A2ECCnm[] asm("D_800A2ECC.NON_MATCHING");
extern s8 D_800A2ED0nm[] asm("D_800A2ED0.NON_MATCHING");
extern s32 gSplitScreenModenm[] asm("gSplitScreenMode.NON_MATCHING");
extern Car *gPlayerCarsmall asm("gPlayerCar.NON_MATCHING");
extern u8 D_800A3A34Absolute[];

extern s32 gOrderingTableBankLui asm("gOrderingTableBankAbsolute");
extern u8 D_800A3A2CAbsolute[];
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
        HudDrawText(D_8009AE40nm[0], 0x76, 0x1E, 0);
        GraphicsDrawDoubleBorderRect(0x6E, 0x1A, 0x60, 0x12, 0, 0, 0, 1);
        return;
    }
    value = D_800A359Cnm[0];
    if (value != 0) {
        MenuDrawResults(value >= 0x21C);
        if (D_800A3848small < 0xA1) {
            return;
        }
        D_800A2D0Cnm[0] = 1;
        return;
    }
    if (D_800A2EC8nm[0] != 0) {
        if (D_800A397CAbsolute[0] == 2) {
            ReplayDrawControls();
        } else {
            MenuDrawPausePanel((void *)0x80010000, D_800A2ECCnm[0],
                               D_800A2ED0nm[0]);
        }
    } else {
        HudUpdateFlagOverlay();
    }
    mode = 2;
    if (gSplitScreenModenm[0] == mode) {
        HudDrawPitMenu(gPlayerCarsmall, -0xA);
        HudDrawCar(gPlayerCarsmall, -0x6E);
        prim = *(s32 *)&gPlayerCarsmall->next;
        gOrderingTableBankLui = gOrderingTableBankLui + 1;
        gOrderingTableLui = gOrderingTableLui + 0x1004;
        HudDrawPitMenu(prim, -0x14);
        HudDrawCar(*(s32 *)&gPlayerCarsmall->next, -0x7D);
        gOrderingTableBankLui = gOrderingTableBankLui - 1;
        gOrderingTableLui = gOrderingTableLui - 0x1004;
        return;
    }
    HudDrawPitMenu(gPlayerCarsmall, 0);
    HudDrawCar(gPlayerCarsmall, 0);
    if (gPlayerCarsmall->unk209 == mode) {
        func_8001BA94(0);
    }
}
