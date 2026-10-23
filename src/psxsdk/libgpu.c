/* SPDX-License-Identifier: AGPL-3.0-only AND MIT AND GPL-2.0-or-later */
/* SDK C from sotn-decomp d818995ec49ef76e3b1625a96f4360108b3168be. */
#include "common.h"
#include "psxsdk_internal.h"
#include "libpress.h"
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/stdarg.h>

#include <psxsdk/libspu.h>
#include <psxsdk/libgpu.h>
#include <psxsdk/libcd.h>

/* libgpu state, Psy-Q 3.6 layout. The Makefile binds each name. */
typedef struct GpuVtbl {
    const char *rcsid;
    void (*addque)(void (*)(), s32 *, s32);
    s32 (*addque2)(void (*)(), s32 *, s32, s32);
    s32 (*clr)(RECT *, s32);
    void (*ctl)(u32);
    s32 (*cwb)(s32 *, s32);
    void (*cwc)(s32);
    s32 (*drs)(RECT *, s32 *);
    s32 (*dws)(RECT *, s32 *);
    s32 (*exeque)(void);
    s32 (*getctl)(s32);
    s32 (*otc)(s32, s32);
    s32 (*param)(s32);
    s32 (*reset)(s32);
    u32 (*status)(void);
    s32 (*sync)(s32);
} GpuVtbl;

/* Saved copy of the last DISPENV; retail reads its halfwords as unsigned. */
typedef struct SavedDispEnv {
    volatile u16 dispX;
    volatile u16 dispY;
    volatile u16 dispW;
    volatile u16 dispH;
    volatile u16 scrX;
    volatile u16 scrY;
    volatile u16 scrW;
    volatile u16 scrH;
    s32 flags;
} SavedDispEnv;

typedef struct GfxState {
    u8 type;    /* 0: PSX, 1: 1 MB VRAM, 2: debug */
    u8 queue;   /* 1: queued drawing */
    u8 level;   /* debug level */
    u8 reverse; /* upside-down display */
    s16 maxW;
    s16 maxH;
    s32 pad8; /* set while a draw-sync callback is pending */
    void (*drawSyncCb)();
    DRAWENV drawEnv;
    SavedDispEnv dispEnv;
} GfxState;

#define GPU_CLAMP(value, low, high)                                            \
    value < low ? low : (value > high ? high : value)

extern volatile u16 gfxMaxW[];
extern volatile u16 gfxMaxH[];
extern GpuVtbl *gGpu;
extern s32 (*GPU_printf)(const char *, ...);
extern GfxState gGfx;
extern volatile s32 *GPU_DATA;
extern volatile u32 *GPU_STATUS;
extern volatile s32 *DMA2_MADR;
extern volatile s32 *DMA2_BCR;
extern volatile s32 *DMA2_CHCR;
extern volatile s32 *DMA6_MADR;
extern volatile s32 *DMA6_BCR;
extern volatile s32 *DMA6_CHCR;
extern volatile s32 *DPCR;

u_short LoadTPage(u_long *pix, int tp, int abr, int x, int y, int w, int h) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.h = h;
    switch (tp) {
    case 0:
        rect.w = w / 4;
        break;
    case 1:
        rect.w = w / 2;
        break;
    case 2:
        rect.w = w;
        break;
    }
    LoadImage(&rect, pix);

    return GetTPage(tp, abr, x, y);
}

u_short LoadClut(u_long *clut, int x, int y) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = 0x100;
    rect.h = 1;
    LoadImage(&rect, clut);

    return GetClut(x, y);
}

u_short LoadClut2(u_long *clut, int x, int y) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = 0x10;
    rect.h = 1;
    LoadImage(&rect, clut);

    return GetClut(x, y);
}

/* SPDX-License-Identifier: MIT */

extern long GetVideoMode(void);
extern int GetGraphType(void);

DRAWENV *SetDefDrawEnv(DRAWENV *env, s32 x, s32 y, s32 w, s32 h) {
    int videoMode;

    videoMode = GetVideoMode();
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
    if (videoMode != 0) {
        env->dfe = h < 0x121;
    } else {
        env->dfe = h < 0x101;
    }
    env->ofs[0] = x;
    env->ofs[1] = y;
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    env->tpage = 10;
    env->isbg = 0;
    return env;
}

DISPENV *SetDefDispEnv(DISPENV *env, s32 x, s32 y, s32 w, s32 h) {
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

extern u32 D_8009D038[];
extern u32 D_8009D03C[];
extern u32 D_8009DA8C[];

void SetDumpFnt(int id) {
    if (id >= 0 && (s32)D_8009D038[0] >= id) {
        D_8009D03C[0] = id;
        D_8009DA8C[0] = (u32)FntPrint;
    }
}

extern u16 D_800AD0DC[];
extern u16 D_800AD0E0[];
extern u32 D_8009D038[];
extern u8 D_8009D040[];

typedef struct {
    u8 unk00[0x1C];
    s32 capacity;
    u8 unk20[4];
    u8 *buffer;
    s32 written;
    u8 unk2C[4];
} FntFont;

extern FntFont D_8009CEB8[];
extern void memset_8008B820();

void FntLoad(int tx, int ty) {
    D_800AD0E0[0] = LoadClut2(D_8009D040, tx, ty + 0x80);
    D_800AD0DC[0] = LoadTPage(D_8009D040 + 0x200, 0, 0, tx, ty, 0x80, 0x20);
    D_8009D038[0] = 0;
    memset_8008B820(D_8009CEB8, 0, 0x180);
}

typedef struct FntStream {
    TILE tile;         /* 0x00 */
    DR_MODE draw_mode; /* 0x10 */
    s32 capacity;      /* 0x1C */
    SPRT_8 *sprites;   /* 0x20 */
    char *buffer;      /* 0x24 */
    s32 written;       /* 0x28 */
    s32 autoWidth;     /* 0x2C: the box grows to fit the text */
} FntStream;

extern FntStream Font[];
extern s32 fntCountX;
extern s32 fntBase;
extern char fntText[];
extern SPRT_8 fntSprt[];
extern u16 fntTpage;
extern u16 fntClut;

/* The tile colour and box go through the libgpu setRGB0, setXY0 and setWH
 * macros: each expansion repeats `&Font[fntCountX].tile`, which gives
 * retail's pointer-based stores and its reload of fntCountX after each byte
 * store. */
/* Opens a text stream n characters long at (x, y). isbg is 0 for no
 * background, 1 for an opaque one and 2 for a semi-transparent one. */
s32 FntOpen(s32 x, s32 y, s32 w, s32 h, s32 isbg, s32 n) {
    RECT tw;
    s32 i;
    SPRT_8 *sprites;

    if (fntCountX >= 8) {
        return -1;
    }
    if (fntCountX == 0) {
        fntBase = 0;
    }
    Font[fntCountX].autoWidth = w == 0;
    if (n + fntBase > 0x400) {
        n = 0x400 - fntBase;
    }
    tw.w = 0x100;
    tw.h = 0x100;
    tw.x = 0;
    tw.y = 0;
    SetDrawMode(&Font[fntCountX].draw_mode, 0, 0, fntTpage, &tw);
    if (isbg != 0) {
        SetTile(&Font[fntCountX].tile);
        setRGB0(&Font[fntCountX].tile, 0, 0, 0);
        SetSemiTrans(&Font[fntCountX].tile, isbg == 2);
    }
    setXY0(&Font[fntCountX].tile, x, y);
    setWH(&Font[fntCountX].tile, w, h);
    Font[fntCountX].capacity = n;
    Font[fntCountX].written = 0;
    Font[fntCountX].buffer = &fntText[fntBase];
    Font[fntCountX].sprites = &fntSprt[fntBase];
    *Font[fntCountX].buffer = 0;
    sprites = Font[fntCountX].sprites;
    for (i = 0; i < n; i++) {
        SetSprt8(sprites);
        sprites->clut = fntClut;
        sprites++;
    }
    fntBase += n;
    return fntCountX++;
}

/* The 3.6 font has colour escapes (`~cRGB`) and an auto-width box, unlike
 * the sotn 3.3 donor. The zero terms `(n << k) & 0xF` are allocator levers:
 * combine folds them away after flow analysis, but their references set
 * register priorities. The ones before the loop add uses of auto_width
 * without a second set, so sched1 still treats its load as a single-set
 * birth and schedules it after max_y, as retail does. The one in the id
 * check is dead (flow deletes it) and leaves sprt a single-set biv. `v` is
 * reused in the colour escape so its second set stops sched1 from moving
 * the v0 shift after the u0 store. */
u_long *FntFlush(s32 id) {
    char *buf;
    s32 x;
    SPRT_8 *sprt;
    FntStream *font;
    s32 line_break;
    s32 y;
    s32 auto_width;
    s32 max_x;
    s32 len;
    DR_MODE *dr;
    s32 min_x;
    s32 max_y;
    s32 r;
    s32 g;
    s32 b;
    s32 ch;
    s32 step;
    s32 u;
    s32 v;

    r = 0x80;
    g = 0x80;
    min_x = 0;
    b = 0x80;
    if (id < 0 || id >= fntCountX) {
        sprt += (x << 4) & 0xF;
        id = D_8009D03C[0];
        if (Font[id].buffer == 0) {
            return 0;
        }
    }
    font = &Font[id];
    dr = &font->draw_mode;
    buf = font->buffer;
    sprt = font->sprites;
    len = font->capacity;
    x = font->tile.x0;
    y = font->tile.y0;
    max_x = x + font->tile.w;
    max_y = y + font->tile.h;
    auto_width = font->autoWidth;
    TermPrim(dr);
    x += (auto_width << 4) & 0xF;
    x += (auto_width << 5) & 0xF;
    x += (auto_width << 6) & 0xF;
    x += (auto_width << 7) & 0xF;
    step = 8; /* an int, so the front end can't narrow `- 8` to 0xFFF8 */
    while (*buf != 0) {
        if (len == 0) {
            break;
        }
        line_break = 0;
        switch (*buf) {
        case '~':
            buf++;
            if (*buf == 'c') {
                buf++;
                v = *buf - '0';
                r = v << 4;
                buf++;
                g = (*buf - '0') << 4;
                buf++;
                b = (*buf - '0') << 4;
            }
            break;
        case '\t':
            x += 0x20;
            goto test;
        default:
            if ((u8)(*buf - 'a') < 26) {
                ch = *buf - 0x40;
            } else {
                ch = *buf - 0x20;
            }
            u = (ch % 16) * 8;
            v = (ch / 16) * 8;
            sprt->u0 = u;
            sprt->v0 = v;
            sprt->x0 = x;
            sprt->y0 = y;
            sprt->r0 = r;
            sprt->g0 = g;
            sprt->b0 = b;
            AddPrim(dr, sprt++);
        case ' ':
            x += 8;
        test:
            max_x += (x << 4) & 0xF;
            if (x >= max_x && auto_width == 0) {
            case '\n':
                line_break = 1;
            }
            break;
        }
        line_break += (x << 6) & 0xF;
        if (line_break) {
            if (min_x < x) {
                min_x = x;
            }
            y += 8;
            x = font->tile.x0;
            if (y >= max_y) {
                break;
            }
        }
        buf++;
        len--;
    }
    if (font->tile.code != 0) {
        AddPrim(dr, &font->tile);
        if (auto_width != 0) {
            font->tile.w = min_x - (u16)font->tile.x0;
            font->tile.h = y - ((u16)font->tile.y0 - step);
        }
    }
    DrawOTag((u_long *)dr);
    font->written = 0;
    *font->buffer = 0;
    return (u_long *)dr;
}

extern u8 *D_8009DA44[];
extern int strlen(const char *);

int FntPrint(const char *fmt, ...) {
    u8 *buf;
    s32 width;
    FntFont *font;
    u8 *str;
    u32 value;
    u32 t;
    s32 ch;
    s32 count;
    u8 zeroPad;
    s32 pctvar;
    u32 magic;
    u32 quot;
    u8 zeroChar;
    u8 spaceChar;
    volatile u8 pad[0x200];
    va_list ap;

    va_start(ap, fmt);
    if ((s32)fmt < 0 || (s32)fmt >= (s32)D_8009D038[0]) {
        str = (u8 *)fmt;
        fmt = (const char *)D_8009D03C[0];
        if (D_8009CEB8[(s32)fmt].buffer == 0) {
            return -1;
        }
    } else {
        str = va_arg(ap, u8 *);
    }
    font = &D_8009CEB8[(s32)fmt];
    if (font->written > font->capacity) {
        return -1;
    }
    ch = *str;
    if (ch != 0) {
        pctvar = '%';
        magic = 0xCCCCCCCD;
        do {
            if (ch != pctvar) {
                goto store;
            }
            str++;
            ch = *str;
            width = 0;
            if (ch != pctvar) {
                goto format;
            }
        store:
            font->buffer[font->written++] = ch;
            if (font->written > font->capacity) {
                return -1;
            }
            goto tail;
        format:
            zeroPad = (ch == '0');
            while (ch >= '0' && ch <= '9') {
                t = width * 10 - '0';
                width = t + ch;
                str++;
                ch = *str;
            }
            buf = (u8 *)&ap;
            if (width <= 0) {
                width = 1;
            }
            switch (ch) {
            case 'd':
                value = va_arg(ap, u32);
                ch = 0;
                if ((s32)value < 0) {
                    value = -(s32)value;
                    ch = '-';
                }
                count = 0;
                do {
                    buf--;
                    count++;
                    quot = value / 10;
                    *buf = value - quot * 10 + '0';
                    value = quot;
                } while (count == 0 || value != 0);
                if (ch != 0) {
                    buf--;
                    *buf = ch;
                    count++;
                }
                break;
            case 'X':
            case 'x':
                count = 0;
                value = va_arg(ap, u32);
                do {
                    buf--;
                    *buf = D_8009DA44[0][value & 0xF];
                    value >>= 4;
                    count++;
                } while (count == 0 || value != 0);
                if (zeroPad) {
                    if (count < width) {
                        zeroChar = '0';
                        do {
                            buf--;
                            *buf = zeroChar;
                            count++;
                        } while (count < width);
                    }
                }
                break;
            case 'c':
                buf--;
                *buf = va_arg(ap, u8);
                count = 1;
                break;
            case 's':
                buf = va_arg(ap, u8 *);
                count = strlen((char *)buf);
                break;
            }
            if (count < width) {
                spaceChar = ' ';
                do {
                    font->buffer[font->written++] = spaceChar;
                    if (font->written > font->capacity) {
                        return -1;
                    }
                    width--;
                } while (count < width);
            }
            while (--count != -1) {
                font->buffer[font->written++] = *buf++;
                if (font->written > font->capacity) {
                    return -1;
                }
            }
        tail:
            str++;
            ch = *str;
        } while (ch != 0);
    }
    font->buffer[font->written] = 0;
    return font->written;
}

u_short GetTPage(int tp, int abr, int x, int y) {
    int t, last;
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        t = ((tp & 0x3) << 9) | ((abr & 0x3) << 7) | ((y & 0x300) >> 3);
        last = (x & 0x3ff) >> 6;
    } else {
        t = ((tp & 0x3) << 7) | ((abr & 0x3) << 5) | ((y & 0x100) >> 4) |
            ((x & 0x3ff) >> 6);
        last = (y & 0x200) << 2;
    }
    return t | last;
}

u16 GetClut(s32 x, s32 y) {
    return getClut(x, y);
}

typedef int (*DebugPrintf)(const char *, ...);
extern u32 D_8009DA8C[];
extern char D_80090548[];

extern u32 D_8009DA8C[];
extern char D_80090548[];

void DumpTPage(u_short tpage) {
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        ((DebugPrintf)D_8009DA8C[0])(D_80090548, (tpage >> 9) & 3,
                                     (tpage >> 7) & 3, (tpage << 6) & 0x7C0,
                                     (tpage * 8) & 0x300);
        return;
    }
    ((DebugPrintf)D_8009DA8C[0])(
        D_80090548, (tpage >> 7) & 3, (tpage >> 5) & 3, (tpage << 6) & 0x7C0,
        ((tpage * 0x10) & 0x100) + ((tpage >> 2) & 0x200));
}

extern char D_80090560[];

void DumpClut(u_short clut) {
    ((DebugPrintf)D_8009DA8C[0])(D_80090560, (clut & 0x3F) * 0x10, clut >> 6);
}

void *NextPrim(void *p) {
    return nextPrim(p);
}

int IsEndPrim(void *p) {
    return isendprim(p);
}

void AddPrim(void *ot, void *p) {
    addPrim(ot, p);
}

void AddPrims(void *ot, void *p0, void *p1) {
    addPrims(ot, p0, p1);
}

void CatPrim(void *p0, void *p1) {
    catPrim(p0, p1);
}

void TermPrim(void *p) {
    return termPrim(p);
}

void SetSemiTrans(void *p, int abe) {
    return setSemiTrans(p, abe);
}

void SetShadeTex(void *p, int tge) {
    return setShadeTex(p, tge);
}

void SetPolyF3(POLY_F3 *p) {
    setPolyF3(p);
}

void SetPolyFT3(POLY_FT3 *p) {
    setPolyFT3(p);
}

void SetPolyG3(POLY_G3 *p) {
    setPolyG3(p);
}

void SetPolyGT3(POLY_GT3 *p) {
    setPolyGT3(p);
}

void SetPolyF4(POLY_F4 *p) {
    setPolyF4(p);
}

void SetPolyFT4(POLY_FT4 *p) {
    setPolyFT4(p);
}

void SetPolyG4(POLY_G4 *p) {
    setPolyG4(p);
}

void SetPolyGT4(POLY_GT4 *p) {
    setPolyGT4(p);
}

void SetSprt8(SPRT_8 *p) {
    setSprt8(p);
}

void SetSprt16(SPRT_16 *p) {
    setSprt16(p);
}

void SetSprt(SPRT *p) {
    setSprt(p);
}

void SetTile1(TILE_1 *p) {
    setTile1(p);
}

void SetTile8(TILE_8 *p) {
    setTile8(p);
}

void SetTile16(TILE_16 *p) {
    setTile16(p);
}

void SetTile(TILE *p) {
    setTile(p);
}

void SetLineF2(LINE_F2 *p) {
    setLineF2(p);
}

void SetLineG2(LINE_G2 *p) {
    setLineG2(p);
}

void SetLineF3(LINE_F3 *p) {
    setLineF3(p);
}

void SetLineG3(LINE_G3 *p) {
    setLineG3(p);
}

void SetLineF4(LINE_F4 *p) {
    setLineF4(p);
}

void SetLineG4(LINE_G4 *p) {
    setLineG4(p);
}

void SetBlockFill(BLK_FILL *p) {
    setBlockFill(p);
}

/* SPDX-License-Identifier: MIT */

void SetDrawMove(void *packet) {
    *((u8 *)packet + 3) = 5;
    *((u8 *)packet + 7) = 1;
    *((u32 *)packet + 2) = 0x80000000;
}

void SetDrawTPage(void *drtpage, s32 dfe, s32 dtd, s32 tpage) {
    u32 code;

    *((u8 *)drtpage + 3) = 1;
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        u32 mode;
        u32 page;

        mode = 0xE1000000;
        if (dtd != 0) {
            mode |= 0x800;
        }
        code = tpage & 0x27FF;
        page = code;
        if (dfe != 0) {
            do {
                page |= 0x1000;
            } while (0);
            code = mode | page;
        } else {
            code = mode | page;
        }
    } else {
        u32 mode;
        u32 page;

        mode = 0xE1000000;
        if (dtd != 0) {
            mode |= 0x200;
        }
        page = tpage & 0x9FF;
        if (dfe != 0) {
            page |= 0x400;
        }
        code = mode | page;
    }
    *((u32 *)drtpage + 1) = code;
}

void SetDrawLoad(void *dr, RECT *r) {
    s32 half;

    s32 code;

    half = (s32)((s16 *)r)[2] * (s32)((s16 *)r)[3];
    half = (half + 1) / 2;
    code = half + 4;
    if ((u32)(half - 1) >= 0xB) {
        code = 0;
    }
    *((u32 *)dr + 1) = 0x1000000;
    *((u8 *)dr + 3) = code;
    *((u32 *)dr + 2) = 0xA0000000;
    *((u32 *)dr + 3) = ((u32 *)r)[0];
    *((u32 *)dr + 4) = ((u32 *)r)[1];
}

/* SPDX-License-Identifier: MIT */

s32 MargePrim(void *p0, void *p1) {
    s32 len;

    len = *((u8 *)p0 + 3) + *((u8 *)p1 + 3) + 1;
    if (len >= 0x21) {
        return -1;
    }
    *((u8 *)p0 + 3) = len;
    *((u32 *)p1) = 0;
    return 0;
}

extern char D_80090548[];
extern char D_80090570[];
extern char D_80090588[];
extern char D_80090598[];
extern char D_800905B0[];
extern char D_800905BC[];

void DumpDrawEnv(DRAWENV *env) {
    GPU_printf(D_80090570, env->clip.x, env->clip.y, env->clip.w, env->clip.h);
    GPU_printf(D_80090588, env->ofs[0], env->ofs[1]);
    GPU_printf(D_80090598, env->tw.x, env->tw.y, env->tw.w, env->tw.h);
    GPU_printf(D_800905B0, env->dtd);
    GPU_printf(D_800905BC, env->dfe);
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        GPU_printf(D_80090548, (env->tpage >> 9) & 3, (env->tpage >> 7) & 3,
                   (env->tpage << 6) & 0x7C0, (env->tpage * 8) & 0x300);
    } else {
        GPU_printf(D_80090548, (env->tpage >> 7) & 3, (env->tpage >> 5) & 3,
                   (env->tpage << 6) & 0x7C0,
                   ((env->tpage * 0x10) & 0x100) + ((env->tpage >> 2) & 0x200));
    }
}

extern u32 gDispPrintfRead1[];
extern u32 gDispPrintfRead2[];
extern u32 gDispPrintfRead3[];
extern u32 gDispPrintfRead4[];
extern char D_800905C8[];
extern char D_800905E4[];
extern char D_80090600[];
extern char D_8009060C[];

void DumpDispEnv(DISPENV *env) {
    ((DebugPrintf)gDispPrintfRead1[0])(D_800905C8, env->disp.x, env->disp.y,
                                       env->disp.w, env->disp.h);
    ((DebugPrintf)gDispPrintfRead2[0])(D_800905E4, env->screen.x, env->screen.y,
                                       env->screen.w, env->screen.h);
    ((DebugPrintf)gDispPrintfRead3[0])(D_80090600, env->isinter);
    ((DebugPrintf)gDispPrintfRead4[0])(D_8009060C, env->isrgb24);
}

extern char D_8009064C[];
extern char D_8009066C[];
extern char D_8009DA48[];
extern u16 D_8009DB10[][2];
extern u16 D_8009DB24[][2];
extern s32 _reset(s32);
extern void GPU_cw(u32);

s32 ResetGraph(s32 level) {
    s32 mode = level & 7;

    if (mode == 0 || mode == 3) {
        printf(D_8009064C, D_8009DA48, &gGfx);
        memset(&gGfx, 0, sizeof(GfxState));
        ResetCallback();
        GPU_cw((u32)gGpu & 0xFFFFFF);
        gGfx.type = _reset(mode != 0);
        gGfx.queue = 1;
        gGfx.maxW = D_8009DB10[gGfx.type][0];
        gGfx.maxH = D_8009DB24[gGfx.type][0];
        memset(&gGfx.drawEnv, -1, sizeof(DRAWENV));
        memset(&gGfx.dispEnv, -1, sizeof(DISPENV));
        return gGfx.type;
    }
    if (gGfx.level >= 2) {
        GPU_printf(D_8009066C, level);
    }
    return gGpu->reset(1);
}

extern char D_80090680[];

s32 SetGraphReverse(s32 mode) {
    s32 old = gGfx.reverse;

    if (gGfx.level >= 2) {
        GPU_printf(D_80090680, mode);
    }

    gGfx.reverse = mode;
    gGpu->ctl(gGpu->getctl(8) | (gGfx.reverse ? 0x08000080 : 0x08000000));
    if (gGfx.type == 2) {
        gGpu->ctl(gGfx.reverse ? 0x20000501 : 0x20000504);
    }
    return old;
}

extern u8 D_8009DA90[];
extern u8 D_8009DA92[];
extern u8 D_8009DA93[];
extern u32 D_8009DA8C[];
extern char D_80090698[];

int SetGraphDebug(int level) {
    volatile u8 *debug = D_8009DA92;
    u8 old = debug[0];

    debug[0] = level;
    if ((u8)level) {
        ((DebugPrintf)D_8009DA8C[0])(D_80090698, D_8009DA92[0], D_8009DA90[0],
                                     D_8009DA93[0]);
    }
    return old;
}

extern u32 D_8009DA88[];
extern u32 D_8009DA8C[];
extern u8 D_8009DA91[];
extern u8 D_8009DA92[];
extern char D_800906C4[];
int SetGraphQueue(int mode) {
    u8 previousMode;
    previousMode = D_8009DA91[0];
    if (D_8009DA92[0] >= 2) {
        ((int (*)(const char *, ...))D_8009DA8C[0])(D_800906C4, mode);
    }
    if (mode != D_8009DA91[0]) {
        ((void (*)(int))((u32 *)D_8009DA88[0])[13])(1);
        D_8009DA91[0] = mode;
        DMACallback(2, 0);
    }
    return previousMode;
}

extern u8 D_8009DA90[];

int GetGraphType(void) {
    return D_8009DA90[0];
}

extern u8 D_8009DA92[];

int GetGraphDebug(void) {
    return D_8009DA92[0];
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009DA92[];
extern u32 D_8009DA9C[];
extern u32 D_8009DA8C[];
extern u8 D_8009DAA0[];
extern char D_800906D8[];

u_long DrawSyncCallback(void (*func)()) {
    Callback old;

    if (D_8009DA92[0] >= 2) {
        ((int (*)(const char *, ...))D_8009DA8C[0])(D_800906D8, func);
    }
    old = D_8009DA9C[0];
    ((u32 *)D_8009DAA0)[-1] = func;
    return old;
}

extern u32 D_8009DA88[];
extern u32 D_8009DA8C[];
extern u8 D_8009DA92[];
extern char D_800906F4[];
void SetDispMask(s32 mode) {
    s32 command;
    u32 *gpu;
    if ((u8)D_8009DA92[0] >= 2U) {
        ((int (*)(const char *, ...))D_8009DA8C[0])(D_800906F4, mode);
    }
    if (mode == 0)
        memset(&D_8009DA92[0x6A], -1, 0x14);
    command = 0x03000001;
    gpu = (u32 *)D_8009DA88[0];
    if (mode != 0)
        command = 0x03000000;
    ((void (*)(int))gpu[4])(command);
}

extern char D_80090708[];
extern u32 D_8009DA88[];
extern u32 D_8009DA8C[];
extern u8 D_8009DA92[];

int DrawSync(int mode) {
    if (D_8009DA92[0] >= 2) {
        ((void (*)())D_8009DA8C[0])(D_80090708, mode);
    }
    return ((int (*)())((u32 *)D_8009DA88[0])[15])(mode);
}

extern u8 D_8009DA92[];
extern s16 D_8009DA94[];
extern s16 D_8009DA96[];

extern char D_8009071C[];
extern char D_8009073C[];
extern char D_80090728[];

extern u8 D_8009DA92[];
extern s16 D_8009DA94[];
extern s16 D_8009DA96[];

extern char D_8009071C[];
extern char D_8009073C[];
extern char D_80090728[];

void checkRECT(RECT *r, RECT *rect) {
    switch (D_8009DA92[0]) {
    case 1:
        if (rect->w > D_8009DA94[0] || rect->w + rect->x > D_8009DA94[0] ||
            rect->y > D_8009DA96[0] || rect->y + rect->h > D_8009DA96[0] ||
            rect->w <= 0 || rect->x < 0 || rect->y < 0 || rect->h <= 0) {
            ((int (*)())D_8009DA8C[0])(D_8009071C, r);
            ((int (*)())((u32 *)D_8009DA90)[-1])(D_80090728, rect->x, rect->y,
                                                 rect->w, rect->h);
            return;
        }
        return;
    case 2:
        ((int (*)())D_8009DA8C[0])(D_8009073C, r);
        ((int (*)())((u32 *)D_8009DA90)[-1])(D_80090728, rect->x, rect->y,
                                             rect->w, rect->h);
        return;
    default:
        return;
    }
}

extern char D_80090740[];
extern u32 D_8009DA88[];

int ClearImage(RECT *rect, u_char r, u_char g, u_char b) {
    checkRECT((RECT *)D_80090740, rect);
    return ((int (*)())((u32 *)D_8009DA88[0])[2])(
        ((u32 *)D_8009DA88[0])[3], rect, 8, (b << 16) | (g << 8) | r);
}

extern char D_8009074C[];
extern u32 D_8009DA88[];

int LoadImage(RECT *rect, u_long *p) {
    checkRECT((RECT *)D_8009074C, rect);
    return ((int (*)())((u32 *)D_8009DA88[0])[2])(((u32 *)D_8009DA88[0])[8],
                                                  rect, 8, p);
}

extern char D_80090758[];

int StoreImage(RECT *rect, u_long *p) {
    checkRECT((RECT *)D_80090758, rect);
    return ((int (*)())((u32 *)D_8009DA88[0])[2])(((u32 *)D_8009DA88[0])[7],
                                                  rect, 8, p);
}

extern char D_80090764[];
extern u32 D_8009DB40[];
extern u32 D_8009DB44[];
extern u32 D_8009DB48[];

int MoveImage(RECT *rect, int x, int y) {
    u32 *gpu;
    u32 *cmd;

    gpu = D_8009DA88;
    checkRECT((RECT *)D_80090764, rect);
    if (rect->w == 0 || rect->h == 0) {
        return -1;
    }
    cmd = (u32 *)gpu[0];
    D_8009DB40[0] = *(u32 *)rect;
    D_8009DB44[0] = (y << 16) | (x & 0xFFFF);
    D_8009DB48[0] = *(u32 *)&rect->w;
    return ((int (*)())cmd[2])(cmd[6], D_8009DB40 - 2, 20, 0);
}

extern u32 D_8009DA8C[];
extern u8 D_8009DA92[];
extern u8 D_8009DB4C[];
extern char D_80090770[];
OT_TYPE *ClearOTag(OT_TYPE *orderingTable, int length) {
    OT_TYPE *temp_a0;
    u32 masked;
    if ((u8)D_8009DA92[0] >= 2U) {
        temp_a0 = (OT_TYPE *)D_80090770;
        ((int (*)(const char *, ...))D_8009DA8C[0])(temp_a0, orderingTable,
                                                    length);
    }
    length -= 1;
    if (length != 0) {
        do {
            length -= 1;
            temp_a0 = (OT_TYPE *)orderingTable + 1;
            ((u8 *)orderingTable)[3] = 0;
            masked = (u32)temp_a0 & 0xFFFFFF;
            orderingTable[0] = (orderingTable[0] & 0xFF000000) | masked;
            orderingTable = temp_a0;
        } while (length != 0);
    }
    *orderingTable = (s32)((u32)D_8009DB4C & 0xFFFFFF);
    return orderingTable;
}

extern u32 D_8009DA88[];
extern u32 D_8009DA8C[];
extern u8 D_8009DA92[];
extern u8 D_8009DB4C[];
extern char D_80090788[];
OT_TYPE *ClearOTagR(OT_TYPE *ot, int n) {
    if (D_8009DA92[0] >= 2) {
        ((int (*)(const char *, ...))D_8009DA8C[0])(D_80090788, ot, n);
    }
    ((void (*)(OT_TYPE *, int))((u32 *)D_8009DA88[0])[11])(ot, n);
    ot[0] = (OT_TYPE)((u32)D_8009DB4C & 0xFFFFFF);
    return ot;
}

int DrawPrim(void *prim) {
    u8 code;

    code = *((u8 *)prim + 3);
    ((int (*)())((u32 *)D_8009DA88[0])[15])(0);
    return ((int (*)())((u32 *)D_8009DA88[0])[5])((u32 *)prim + 1, code);
}

extern char D_800907A0[];

void DrawOTag(OT_TYPE *ot) {
    extern u32 D_8009DA88[];
    extern u32 D_8009DA8C[];
    extern u8 D_8009DA92[];

    if (D_8009DA92[0] >= 2) {
        ((void (*)())D_8009DA8C[0])(D_800907A0, ot);
    }
    ((void (*)())((u32 *)D_8009DA88[0])[2])(((u32 *)D_8009DA88[0])[6], ot, 0,
                                            0);
}

extern void *memcpy();
extern char D_800907B4[];

DRAWENV *PutDrawEnv(DRAWENV *env) {
    s32 size;

    if (gGfx.level >= 2) {
        GPU_printf(D_800907B4, env);
    }

    SetDrawEnv(&env->dr_env, env);
    env->dr_env.tag |= 0xFFFFFF;
    gGpu->addque2(gGpu->cwc, &env->dr_env, sizeof(DR_ENV), 0);
    size = sizeof(DRAWENV);
    memcpy(&gGfx.drawEnv, env, size);

    return env;
}

extern char D_800907CC[];

void DrawOTagEnv(OT_TYPE *ot, DRAWENV *env) {
    s32 size;

    if (gGfx.level >= 2) {
        GPU_printf(D_800907CC, ot, env);
    }

    SetDrawEnv(&env->dr_env, env);
    env->dr_env.tag = (env->dr_env.tag & 0xFF000000) | ((u32)ot & 0xFFFFFF);
    gGpu->addque2(gGpu->cwc, &env->dr_env, sizeof(DR_ENV), 0);
    size = sizeof(DRAWENV);
    memcpy(&gGfx.drawEnv, env, size);
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009DAA0[];
extern void *memcpy();

DRAWENV *GetDrawEnv(DRAWENV *env) {
    s32 size = 0x5C;

    memcpy(env, D_8009DAA0, size);
    return env;
}

extern char D_800907E8[];
extern s32 get_dx();

DISPENV *PutDispEnv(DISPENV *env) {
    s32 h_start;
    s32 v_start;
    s32 cmd;
    s32 v_end;
    s32 h_end;
    s32 size;

    cmd = 0x08000000;
    if (*(volatile u8 *)&gGfx.level >= 2) {
        GPU_printf(D_800907E8, env);
    }
    gGpu->ctl(0x05000000 |
              (gGfx.type == 1 || gGfx.type == 2
                   ? ((env->disp.y & 0xFFF) << 0xC) | (get_dx(env) & 0xFFF)
                   : ((env->disp.y & 0x3FF) << 0xA) | (env->disp.x & 0x3FF)));
    if ((s16)gGfx.dispEnv.scrX != env->screen.x ||
        (s16)gGfx.dispEnv.scrY != env->screen.y ||
        (s16)gGfx.dispEnv.scrW != env->screen.w ||
        (s16)gGfx.dispEnv.scrH != env->screen.h) {
        env->pad0 = GetVideoMode();
        h_start = env->screen.x * 0xA + 0x260;
        v_start = env->screen.y + (env->pad0 ? 0x13 : 0x10);
        h_end = h_start + (env->screen.w ? env->screen.w * 0xA : 0xA00);
        v_end = v_start + (env->screen.h ? env->screen.h : 0xF0);
        h_start = GPU_CLAMP(h_start, 0x1F4, 0xCDA);
        h_end = GPU_CLAMP(h_end, h_start + 0x50, 0xCDA);
        v_start = GPU_CLAMP(v_start, 0x10, (env->pad0 ? 0x136 : 0x100));
        v_end = GPU_CLAMP(v_end, v_start + 2, (env->pad0 ? 0x138 : 0x102));
        gGpu->ctl(0x06000000 | ((h_end & 0xFFF) << 0xC) | (h_start & 0xFFF));
        gGpu->ctl(0x07000000 | ((v_end & 0x3FF) << 0xA) | (v_start & 0x3FF));
    }
    if (gGfx.dispEnv.flags != LOW(env->isinter) ||
        (s16)gGfx.dispEnv.dispX != env->disp.x ||
        (s16)gGfx.dispEnv.dispY != env->disp.y ||
        (s16)gGfx.dispEnv.dispW != env->disp.w ||
        (s16)gGfx.dispEnv.dispH != env->disp.h) {
        env->pad0 = GetVideoMode();
        if (env->pad0 == 1) {
            cmd |= 0x8;
        }
        if (env->isrgb24) {
            cmd |= 0x10;
        }
        if (env->isinter) {
            cmd |= 0x20;
        }
        if (*(volatile u8 *)&gGfx.reverse != 0) {
            cmd |= 0x80;
        }
        if (env->disp.w > 0x118) {
            if (env->disp.w < 0x161) {
                cmd |= 1;
            } else if (env->disp.w < 0x191) {
                cmd |= 0x40;
            } else if (env->disp.w < 0x231) {
                cmd |= 2;
            } else {
                cmd |= 3;
            }
        }
        if (env->disp.h <= (env->pad0 ? 0x120 : 0x100)) {
        } else {
            cmd |= 0x24;
        }
        gGpu->ctl(cmd);
    }
    size = sizeof(DISPENV);
    memcpy(&gGfx.dispEnv, env, size);
    return env;
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009DAFC[];

DISPENV *GetDispEnv(DISPENV *env) {
    s32 size = 0x14;

    memcpy(env, D_8009DAFC, size);
    return env;
}

extern u32 D_8009DA88[];
u32 GetODE(void) {
    s32 (*getOde)(void);
    getOde = (s32 (*)(void))((u32 *)D_8009DA88[0])[14];
    return (u32)getOde() >> 31;
}

/* SPDX-License-Identifier: MIT */

extern u32 get_tw();

void SetTexWindow(void *drtw, RECT *tw) {
    *((u8 *)drtw + 3) = 2;
    *((u32 *)drtw + 1) = get_tw(tw);
    *((u32 *)drtw + 2) = 0;
}

extern u32 get_cs(s16 x, s16 y);
extern u32 get_ce(s16 x, s16 y);

void SetDrawArea(void *drarea, RECT *clip) {
    *((u8 *)drarea + 3) = 2;
    *((u32 *)drarea + 1) = get_cs(clip->x, clip->y);
    *((u32 *)drarea + 2) = get_ce((u16)clip->x + (u16)clip->w - 1,
                                  (u16)clip->y + (u16)clip->h - 1);
}

extern s32 get_ofs();

void SetDrawOffset(void *drofs, s16 *ofs) {
    *((u8 *)drofs + 3) = 2;
    *((u32 *)drofs + 1) = get_ofs(ofs[0], ofs[1]);
    *((u32 *)drofs + 2) = 0;
}

/* SPDX-License-Identifier: MIT */

void SetPriority(void *arg0, s32 arg1, s32 arg2) {
    u32 mode;

    *((u8 *)arg0 + 3) = 2;
    mode = 0xE6000000;
    if (arg1 != 0) {
        mode = 0xE6000002;
    }
    *((u32 *)arg0 + 1) = mode | (arg2 != 0);
    *((u32 *)arg0 + 2) = 0;
}

extern u32 get_tw();
extern s32 get_mode();

void SetDrawMode(DR_MODE *p, s32 dfe, s32 dtd, s32 tpage, RECT *tw) {
    *((u8 *)p + 3) = 2;
    *((u32 *)p + 1) = get_mode(dfe, dtd, (u16)tpage);
    *((u32 *)p + 2) = get_tw(tw);
}

extern s32 get_mode();

void SetDrawEnv(DR_ENV *dr_env_in, DRAWENV *env) {
    s32 w;
    s32 h;
    s32 m;
    s32 n;
    s32 rw;
    s32 rh;
    RECT clip_rect;
    s32 offset;
    DR_ENV *dr_env;

    dr_env = dr_env_in;

    dr_env->code[0] = get_cs(env->clip.x, env->clip.y);
    dr_env->code[1] =
        get_ce(env->clip.w + env->clip.x - 1, env->clip.y + env->clip.h - 1);
    dr_env->code[2] = get_ofs(env->ofs[0], env->ofs[1]);
    dr_env->code[3] = get_mode(env->dfe, env->dtd, env->tpage);
    dr_env->code[4] = get_tw(&env->tw);
    dr_env->code[5] = 0xE6000000;

    offset = 7;
    if (env->isbg != 0) {
        clip_rect.x = env->clip.x;
        clip_rect.y = env->clip.y;
        clip_rect.w = env->clip.w;
        clip_rect.h = env->clip.h;
        w = clip_rect.w;
        rw = w < 0 ? 0
                   : (
                         {
                             m = (s16)gfxMaxW[0] - 1;
                             w > m ? m : w;
                         });
        clip_rect.w = rw;
        h = clip_rect.h;
        rh = h < 0 ? 0
                   : (
                         {
                             n = (s16)gfxMaxH[0] - 1;
                             h > n ? n : h;
                         });
        clip_rect.h = rh;

        if ((clip_rect.x & 0x3F) || (clip_rect.w & 0x3F)) {
            clip_rect.x -= env->ofs[0];
            clip_rect.y -= env->ofs[1];
            *((s32 *)dr_env + offset++) =
                0x60000000 | env->b0 << 0x10 | env->g0 << 8 | env->r0;
            *((s32 *)dr_env + offset++) = LOW(clip_rect.x);
            *((s32 *)dr_env + offset++) = LOW(clip_rect.w);
            clip_rect.x += env->ofs[0];
            clip_rect.y += env->ofs[1];
        } else {
            *((s32 *)dr_env + offset++) =
                0x02000000 | env->b0 << 0x10 | env->g0 << 8 | env->r0;
            *((s32 *)dr_env + offset++) = LOW(clip_rect.x);
            *((s32 *)dr_env + offset++) = LOW(clip_rect.w);
        }
    }

    setlen(dr_env, offset - 1);
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009DA90[];

s32 get_mode(s32 dfe, s32 dtd, s32 tpage) {
    if ((u32)(*(volatile u8 *)&gGfx.type - 1) < 2U) {
        return 0xE1000000 | (dtd ? 0x800 : 0) | (dfe ? 0x1000 : 0) |
               (tpage & 0x27FF);
    } else {
        return 0xE1000000 | (dtd ? 0x200 : 0) | (dfe ? 0x400 : 0) |
               (tpage & 0x9FF);
    }
}

/* SPDX-License-Identifier: MIT */

u32 get_cs(s16 x, s16 y) {
    volatile u16 *px;
    volatile u16 *py;
    register s32 cmdBase asm("$4");
    volatile u8 *pm;
    s32 xmax;
    s32 mx;
    s32 clipX;
    s32 xv;
    s32 yv;
    s32 ymax;
    s32 my;
    s32 clipY;
    s32 word1;
    s32 word0;

    clipX = 0;
    if (x >= 0) {
        px = (volatile u16 *)D_8009DA94;
        xmax = (s16)px[0];
        mx = xmax - 1;
        xv = x;
        if (mx < x) {
            xv = mx;
        }
        clipX = xv;
    }
    x = clipX;
    asm("" : "=r"(x) : "0"(x));
    yv = y;
    clipY = 0;
    if (yv >= 0) {
        py = (volatile u16 *)D_8009DA96;
        ymax = (s16)py[0];
        my = ymax - 1;
        if (my < yv) {
            yv = my;
        }
        clipY = yv;
    }
    pm = D_8009DA90;
    if ((u32)(pm[0] - 1) >= 2) {
        word1 = clipY & 0x3FF;
        word1 = word1 << 0xA;
        word0 = x & 0x3FF;
        cmdBase = 0xE3000000;
    } else {
        word1 = clipY & 0xFFF;
        word1 = word1 << 0xC;
        word0 = x & 0xFFF;
        cmdBase = 0xE3000000;
    }
    if (mx) {
        return word1 | (word0 | cmdBase);
    } else {
        return word1 | (word0 | cmdBase);
    }
}

/* SPDX-License-Identifier: MIT */

u32 get_ce(s16 x, s16 y) {
    volatile u16 *px;
    volatile u16 *py;
    register s32 cmdBase asm("$4");
    volatile u8 *pm;
    s32 xmax;
    s32 mx;
    s32 clipX;
    s32 xv;
    s32 yv;
    s32 ymax;
    s32 my;
    s32 clipY;
    s32 word1;
    s32 word0;

    clipX = 0;
    if (x >= 0) {
        px = (volatile u16 *)D_8009DA94;
        xmax = (s16)px[0];
        mx = xmax - 1;
        xv = x;
        if (mx < x) {
            xv = mx;
        }
        clipX = xv;
    }
    x = clipX;
    asm("" : "=r"(x) : "0"(x));
    yv = y;
    clipY = 0;
    if (yv >= 0) {
        py = (volatile u16 *)D_8009DA96;
        ymax = (s16)py[0];
        my = ymax - 1;
        if (my < yv) {
            yv = my;
        }
        clipY = yv;
    }
    pm = D_8009DA90;
    if ((u32)(pm[0] - 1) >= 2) {
        word1 = clipY & 0x3FF;
        word1 = word1 << 0xA;
        word0 = x & 0x3FF;
        cmdBase = 0xE4000000;
    } else {
        word1 = clipY & 0xFFF;
        word1 = word1 << 0xC;
        word0 = x & 0xFFF;
        cmdBase = 0xE4000000;
    }
    if (mx) {
        return word1 | (word0 | cmdBase);
    } else {
        return word1 | (word0 | cmdBase);
    }
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009DA90[];

s32 get_ofs(s32 x, s32 y) {
    if ((u32)(*(volatile u8 *)&gGfx.type - 1) < 2U) {
        return 0xE5000000 | ((y & 0xFFF) << 12) | (x & 0xFFF);
    } else {
        return 0xE5000000 | ((y & 0x7FF) << 11) | (x & 0x7FF);
    }
}

/* SPDX-License-Identifier: MIT */

u32 get_tw(RECT *tw) {
    /* Keep these values together to preserve the SDK stack layout. */
    struct {
        u32 xOffset, yOffset, widthMask, heightMask;
    } window;

    if (tw != 0) {
        window.xOffset = (tw->x & 0xFF) >> 3;
        window.widthMask = (-tw->w & 0xFF) >> 3;
        window.yOffset = (tw->y & 0xFF) >> 3;
        window.heightMask = (-tw->h & 0xFF) >> 3;
        return (window.yOffset << 15) | 0xE2000000 | (window.xOffset << 10) |
               (window.heightMask << 5) | window.widthMask;
    }
    return 0;
}

s32 get_dx(DISPENV *env) {
    switch (*(volatile u8 *)&gGfx.type) {
    case 1:
        return gGfx.reverse ? 0x400 - env->disp.x - env->disp.w : env->disp.x;
    case 2:
        return gGfx.reverse ? 0x400 - env->disp.x - env->disp.w / 2
                            : env->disp.x / 2;
    default:
        return env->disp.x;
    }
}

/* SPDX-License-Identifier: MIT */

extern s32 *D_8009DB64[];

s32 _status(void) {
    return *(s32 *)D_8009DB64[0];
}

extern void set_alarm(void);
extern s32 get_alarm(void);

s32 _otc(s32 tableAddress, s32 length) {
    *DPCR |= 0x08000000;
    *DMA6_CHCR = 0;
    *DMA6_MADR = tableAddress - 4 + length * 4;
    *DMA6_BCR = length;
    *DMA6_CHCR = 0x11000002;
    set_alarm();
    while (*DMA6_CHCR & 0x01000000) {
        if (get_alarm()) {
            return -1;
        }
    }
    return length;
}

extern s32 gpuClrBuf[];
extern void _cwc(s32);

/* Clears a frame buffer rectangle. */
s32 _clr(RECT *rect, s32 color) {
    s32 w;
    s32 h;
    s32 m;
    s32 n;
    s32 rw;
    s32 rh;
    s32 *ptr;
    w = rect->w;
    rw = w < 0 ? 0
               : (
                     {
                         m = (s16)gfxMaxW[0] - 1;
                         w > m ? m : w;
                     });
    rect->w = rw;
    h = rect->h;
    rh = h < 0 ? 0
               : (
                     {
                         n = (s16)gfxMaxH[0] - 1;
                         h > n ? n : h;
                     });
    rect->h = rh;

    if ((rect->x & 0x3F) || (rect->w & 0x3F)) {
        ptr = &gpuClrBuf[8];
        gpuClrBuf[0] = 0x07000000 | ((s32)ptr & 0xFFFFFF);
        gpuClrBuf[1] = 0xE3000000;
        gpuClrBuf[2] = 0xE4FFFFFF;
        gpuClrBuf[3] = 0xE5000000;
        gpuClrBuf[4] = 0xE6000000;

        gpuClrBuf[5] = (color & 0xFFFFFF) | 0x60000000;
        gpuClrBuf[6] = LOW(rect->x);
        gpuClrBuf[7] = LOW(rect->w);
        gpuClrBuf[8] = 0x03FFFFFF;
        gpuClrBuf[9] = 0xE3000000 | _param(3);
        gpuClrBuf[10] = 0xE4000000 | _param(4);
        gpuClrBuf[11] = 0xE5000000 | _param(5);
    } else {
        gpuClrBuf[0] = 0x04FFFFFF;
        gpuClrBuf[1] = 0xE6000000;

        gpuClrBuf[2] = (color & 0xFFFFFF) | 0x02000000;
        gpuClrBuf[3] = LOW(rect->x);
        gpuClrBuf[4] = LOW(rect->w);
    }
    _cwc(&gpuClrBuf[0]);
    return 0;
}

/* The clamps are written as `r = v; if (v > max) r = max;` inside the
 * non-negative arm: that shape gives retail's single result register. */
/* LoadImage: copies host memory to VRAM. */
s32 _dws(RECT *rect, s32 *source) {
    s16 w;
    s16 h;
    s16 rw;
    s16 rh;
    s32 temp_a0;
    s32 size;
    s32 var_s0;
    s32 var_s4;

    set_alarm();
    var_s4 = 0;

    w = rect->w;
    if (w >= 0) {
        rw = w;
        if (w > (s16)gfxMaxW[0]) {
            rw = gfxMaxW[0];
        }
    } else {
        rw = 0;
    }
    rect->w = rw;
    h = rect->h;
    if (h >= 0) {
        rh = h;
        if (h > (s16)gfxMaxH[0]) {
            rh = gfxMaxH[0];
        }
    } else {
        rh = 0;
    }
    rect->h = rh;

    temp_a0 = ((rect->w * rect->h) + 1) / 2;
    if (temp_a0 <= 0) {
        return -1;
    }
    var_s0 = temp_a0 % 16;
    size = temp_a0 / 16;
    while (!(*GPU_STATUS & 0x04000000)) {
        if (get_alarm()) {
            return -1;
        }
    }

    *GPU_STATUS = 0x04000000;

    *GPU_DATA = 0x01000000;
    *GPU_DATA = var_s4 ? 0xB0000000 : 0xA0000000;
    *GPU_DATA = LOW(rect->x);
    *GPU_DATA = LOW(rect->w);

    while (--var_s0 != -1) {
        *GPU_DATA = *source++;
    }

    if (size != 0) {
        *GPU_STATUS = 0x04000002;
        *DMA2_MADR = (s32)source;
        *DMA2_BCR = (size << 0x10) | 0x10;
        *DMA2_CHCR = 0x01000201;
    }

    return 0;
}

/* StoreImage: copies VRAM to host memory. */
s32 _drs(RECT *rect, s32 *destination) {
    s16 w;
    s16 h;
    s16 rw;
    s16 rh;
    s32 temp_a0;
    s32 size;
    s32 var_s0;

    set_alarm();

    w = rect->w;
    if (w >= 0) {
        rw = w;
        if (w > (s16)gfxMaxW[0]) {
            rw = gfxMaxW[0];
        }
    } else {
        rw = 0;
    }
    rect->w = rw;
    h = rect->h;
    if (h >= 0) {
        rh = h;
        if (h > (s16)gfxMaxH[0]) {
            rh = gfxMaxH[0];
        }
    } else {
        rh = 0;
    }
    rect->h = rh;

    temp_a0 = ((rect->w * rect->h) + 1) / 2;
    if (temp_a0 <= 0) {
        return -1;
    }
    var_s0 = temp_a0 % 16;
    size = temp_a0 / 16;
    while (!(*GPU_STATUS & 0x04000000)) {
        if (get_alarm()) {
            return -1;
        }
    }

    *GPU_STATUS = 0x04000000;

    *GPU_DATA = 0x01000000;
    *GPU_DATA = 0xC0000000;
    *GPU_DATA = LOW(rect->x);
    *GPU_DATA = LOW(rect->w);

    while (!(*GPU_STATUS & 0x08000000)) {
        if (get_alarm()) {
            return -1;
        }
    }

    while (--var_s0 != -1) {
        *destination++ = *GPU_DATA;
    }

    if (size != 0) {
        *GPU_STATUS = 0x04000003;
        *DMA2_MADR = (s32)destination;
        *DMA2_BCR = (size << 0x10) | 0x10;
        *DMA2_CHCR = 0x01000200;
    }

    return 0;
}

/* SPDX-License-Identifier: MIT */

extern u8 D_800AD124[];

void _ctl(u32 arg0) {
    *(u32 *)D_8009DB64[0] = arg0;
    D_800AD124[arg0 >> 24] = arg0;
}

/* SPDX-License-Identifier: MIT */

u8 _getctl(s32 arg0) {
    return D_800AD124[arg0];
}

s32 _cwb(s32 *arg0, s32 arg1) {
    s32 i;
    extern s32 *D_8009DB60[];

    *(volatile u32 *)D_8009DB64[0] = 0x04000000;
    for (i = arg1 - 1; i != -1; i--) {
        *(volatile u32 *)D_8009DB60[0] = *arg0++;
    }
    return 0;
}

void _cwc(s32 arg0) {
    extern s32 *D_8009DB68[];
    extern s32 *D_8009DB6C[];
    extern s32 *D_8009DB70[];

    *(volatile u32 *)D_8009DB64[0] = 0x04000002;
    *(volatile u32 *)D_8009DB68[0] = arg0;
    *(volatile u32 *)D_8009DB6C[0] = 0;
    *(volatile u32 *)D_8009DB70[0] = 0x01000401;
}

s32 _param(s32 arg0) {
    *GPU_STATUS = 0x10000000 | arg0;
    return *GPU_DATA & 0xFFFFFF;
}

/* SPDX-License-Identifier: MIT */

extern s32 D_8009DB94[];
extern s32 D_8009DB98[];
extern s32 D_8009DB9C[];
extern volatile s32 D_8009DA98[];
extern u8 D_8009DA91[];
extern s32 *D_8009DB70[];
extern s32 D_8009DB84[];
extern s32 D_8009DB88[];
extern s32 D_8009DB8C[];
extern s32 D_800BC558[];
extern s32 D_800BC550[];
extern s32 D_800BC554[];
extern s32 D_800BC54C[];
extern void set_alarm(void);
extern s32 get_alarm(void);
extern s32 _exeque(void);
extern s32 SetIntrMaskFull(s32 arg0) asm("SetIntrMask");

s32 _addque2(Callback func, s32 *arg, s32 size, s32 arg2);

s32 _addque(Callback func, s32 *arg, s32 arg2) {
    return _addque2(func, arg, 0, arg2);
}

s32 _addque2(Callback func, s32 *arg, s32 size, s32 arg2) {
    s32 i;
    s32 *cursor;
    s32 *buf;
    s32 old;
    s32 spinMask;
    s32 debugFlag;
    s32 dmaStat;
    s32 status;
    register s32 idxv asm("v1");

    set_alarm();
    while (((D_8009DB94[0] + 1) & 0x3F) == D_8009DB98[0]) {
        if (get_alarm() != 0) {
            return -1;
        }
        _exeque();
    }
    old = SetIntrMaskFull(0);
    D_8009DA98[0] = 1;
    debugFlag = D_8009DA91[0];
    asm("");
    D_8009DB9C[0] = old;
    spinMask = 0x4000000;
    if (debugFlag != 0) {
        if (D_8009DB94[0] != D_8009DB98[0]) {
            goto queue;
        }
        asm("");
        dmaStat = *D_8009DB70[0];
        if ((dmaStat & 0x1000000) != 0) {
            goto queue;
        }
        if (D_8009DA9C[0] != 0) {
            goto queue;
        }
    }
    do {
        status = *(volatile s32 *)D_8009DB64[0];
    } while ((status & spinMask) == 0);
    func(arg, arg2);
    *(volatile Callback *)&D_8009DB84[0] = func;
    D_8009DB88[0] = (s32)arg;
    D_8009DB8C[0] = arg2;
    SetIntrMaskFull(D_8009DB9C[0]);
    return 0;
queue:
    DMACallback(2, _exeque);
    i = 0;
    if (size != 0) {
        buf = D_800BC558;
        cursor = arg;
        asm("" : : "r"(size));
    copyLoop:
        if (i < size / 4) {
            idxv = D_8009DB94[0];
            *(s32 *)(i * 4 + (idxv * 0x60 + (u32)buf)) = *cursor;
            cursor++;
            i++;
            asm("");
            goto copyLoop;
        }
        *(s32 *)((u8 *)D_800BC550 + D_8009DB94[0] * 0x60) =
            D_8009DB94[0] * 0x60 + (u32)D_800BC558;
    } else {
        *(s32 *)((u8 *)D_800BC550 + D_8009DB94[0] * 0x60) = (s32)arg;
    }
    *(s32 *)((u8 *)D_800BC554 + D_8009DB94[0] * 0x60) = arg2;
    *(Callback *)((u8 *)D_800BC54C + D_8009DB94[0] * 0x60) = func;
    ((s32 *)D_8009DB98)[-1] = (D_8009DB94[0] + 1) & 0x3F;
    SetIntrMaskFull(D_8009DB9C[0]);
    _exeque();
    return (((s32 *)D_8009DB9C)[-2] - D_8009DB98[0]) & 0x3F;
}

typedef struct GpuQueueItem {
    void (*func)(s32 *, s32);
    s32 *arg;
    s32 arg2;
    s32 data[21];
} GpuQueueItem;

typedef struct GpuLast {
    void (*func)(s32 *, s32);
    s32 *arg;
    s32 arg2;
} GpuLast;

extern volatile GpuQueueItem gpuQueue[];
extern volatile GpuLast gpuLast;
extern volatile s32 _qin;
extern volatile s32 _qout;
extern s32 gpuSavedMask;
extern s32 gpuSavedMask2;
extern s32 gpuAlarmEnd;
extern s32 gpuAlarmCount;
extern u8 gpuCtlBuf[];

/* Runs queued drawing commands while the GPU DMA is idle. */
s32 _exeque(void) {
    if (*DMA2_CHCR & 0x01000000) {
        return 1;
    }
    gpuSavedMask2 = SetIntrMaskFull(0);
    if (_qin != _qout && !(*DMA2_CHCR & 0x01000000)) {
        do {
            if (((_qout + 1) & 0x3F) == _qin &&
                *(volatile u32 *)&D_8009DA9C[0] == 0) {
                DMACallback(2, 0);
            }
            while (!(*GPU_STATUS & 0x04000000)) {
            }
            gpuQueue[_qout].func(gpuQueue[_qout].arg, gpuQueue[_qout].arg2);
            gpuLast.func = gpuQueue[_qout].func;
            gpuLast.arg = gpuQueue[_qout].arg;
            gpuLast.arg2 = gpuQueue[_qout].arg2;
            _qout = (_qout + 1) & 0x3F;
        } while (_qin != _qout && !(*DMA2_CHCR & 0x01000000));
    }
    SetIntrMaskFull(gpuSavedMask2);
    if (_qin == _qout && !(*DMA2_CHCR & 0x01000000) && gGfx.pad8 != 0 &&
        *(void *volatile *)&gGfx.drawSyncCb != 0) {
        *(volatile s32 *)&gGfx.pad8 = 0;
        (*(void (*volatile *)())&gGfx.drawSyncCb)();
    }
    return (_qin - _qout) & 0x3F;
}

/* Resets the GPU (mode 0 also clears the control shadow and the queue) and
 * flushes the command queue. */
inline s32 _reset(s32 arg0) {
    s32 intrMask;

    intrMask = SetIntrMaskFull(0);
    _qout = 0;
    gpuSavedMask = intrMask;
    _qin = _qout;

    switch (arg0 & 7) {
    case 0:
        *DMA2_CHCR = 0x401;
        *DPCR |= 0x800;
        *GPU_STATUS = 0;
        memset(gpuCtlBuf, 0, 0x100);
        memset(gpuQueue, 0, sizeof(GpuQueueItem) * 64);
        break;
    case 1:
        *DMA2_CHCR = 0x401;
        *DPCR |= 0x800;
        *GPU_STATUS = 0x02000000;
        *GPU_STATUS = 0x01000000;
        break;
    }
    SetIntrMaskFull(gpuSavedMask);
    if ((arg0 & 7) == 0) {
        return _version(arg0);
    }
    return 0;
}

s32 _sync(s32 mode) {
    s32 n;

    if (mode == 0) {
        set_alarm();
        while (_qin != _qout) {
            _exeque();
            if (get_alarm()) {
                return -1;
            }
        }
        while ((*DMA2_CHCR & 0x01000000) || !(*GPU_STATUS & 0x04000000)) {
            if (get_alarm()) {
                return -1;
            }
        }
        return 0;
    }
    n = (_qin - _qout) & 0x3F;
    if (n != 0) {
        _exeque();
    }
    if ((*DMA2_CHCR & 0x01000000) || !(*GPU_STATUS & 0x04000000)) {
        if (n == 0) {
            return 1;
        }
        return n;
    }
    return n;
}

/* SPDX-License-Identifier: MIT */

extern s32 D_8009DBA8[];
extern s32 D_8009DBAC[];

void set_alarm(void) {
    D_8009DBA8[0] = VSync(-1) + 0xF0;
    D_8009DBAC[0] = 0;
}

extern char D_80090800[];
extern char D_80090834[];
s32 get_alarm(void) {
    if (gpuAlarmEnd < VSync(-1) || gpuAlarmCount++ > 0xF0000) {
        *GPU_STATUS;
        printf(D_80090800, (_qin - _qout) & 0x3F, *GPU_STATUS, *DMA2_CHCR,
               *DMA2_MADR);
        printf(D_80090834, *(volatile Callback *)&D_8009DB84[0], D_8009DB88[0],
               D_8009DB8C[0]);
        _reset(1);
        return -1;
    }
    return 0;
}

s32 _version(s32 mode) {
    *GPU_STATUS = 0x10000007;
    if ((*GPU_DATA & 0xFFFFFF) != 2) {
        *GPU_DATA = (*GPU_STATUS & 0x3FFF) | 0xE1001000;
        *GPU_DATA;
        if (!(*GPU_STATUS & 0x1000)) {
            return 0;
        }
        if (!(mode & 8)) {
            return 1;
        }
        *GPU_STATUS = 0x20000504;
        return 2;
    }
    if (!(mode & 8)) {
        return 3;
    }
    *GPU_STATUS = 0x09000001;
    return 4;
}

void MemsetBytes(unsigned char *dest, unsigned char value,
                 int count) asm("memset");
void MemsetBytes(unsigned char *dest, unsigned char value, int count) {
    int remaining;

    remaining = count - 1;
    if (remaining != -1) {
        do {
            *dest = value;
            remaining--;
            dest++;
        } while (remaining != -1);
    }
}

ASM_FUNC(GPU_cw, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x49 # maspsx-keep\n"
                 "    nop # maspsx-keep\n")
