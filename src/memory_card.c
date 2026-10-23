#include "common.h"
#include "libpress.h"
#include "fixed_addrs.h"
#include "menu_obj.h"
#include <psxsdk/libgpu.h>
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/libcd.h>
#include <psxsdk/libgte.h>
#include <psxsdk/libapi.h>
#include <psxsdk/libspu.h>
#include <psxsdk/kernel.h>
#include "game.h"
#include "menu.h"
#include "scene.h"
#include "util.h"
#include "graphics.h"

extern s32 gOrderingTable[];
extern void SetPolyF4(u8 *prim);
s32 VSync(s32);
extern s32 D_800A37D0[];
extern char *strcpy(char *, const char *);
void SetPolyFT4(POLY_FT4 *);
extern u8 D_800A361C[];
extern u8 D_800A3059[];
u8 *GraphicsAllocPolyFT4(s32 arg0);
u8 *GraphicsAllocPolyF4(s32 arg0);

/* Memory card files and events. */

void CardCloseFile(s32 handle) {
    if (handle != -1)
        close(handle);
}

u8 CardDeleteFile(char *filePath) {
    return delete(filePath);
}

extern void CardTestEvents(void);
extern s32 CardDisableEvents(void);
void CardTestAndDisableEvents(void) {
    CardTestEvents();
    CardTestTransferEvents();
    CardDisableEvents();
    ChangeClearPAD(0);
}

extern u32 D_800A3824, D_800A3828, D_800A382C, D_800A3834;
extern s32 D_800A38C8, D_800A38CC, D_800A38D0, D_800A38D4;
extern s32 DisableEvent(s32);
s32 CardDisableEvents(void) {
    s32 enabled;
    s16 result;

    EnterCriticalSection();
    enabled = DisableEvent(D_800A3824);
    enabled = enabled != 0;
    result = enabled;
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

extern void CardTestEvents(void), CardTestTransferEvents(void);
void CardEnableAndTestEvents(void) {
    CardEnableEvents();
    CardTestEvents();
    CardTestTransferEvents();
}

/* result is s16: the narrowing keeps the first compare in v0 and copies
 * it to s0 in the second jal delay slot (found by the permuter). */
s32 CardEnableEvents(void) {
    s32 enabled;
    s16 result;

    EnterCriticalSection();
    enabled = EnableEvent(D_800A3824);
    enabled = enabled != 0;
    result = enabled;
    if (EnableEvent(D_800A3828) == 0) {
        result = 0;
    }
    if (EnableEvent(D_800A382C) == 0) {
        result = 0;
    }
    if (EnableEvent(D_800A3834) == 0) {
        result = 0;
    }
    if (EnableEvent(D_800A38C8) == 0) {
        result = 0;
    }
    if (EnableEvent(D_800A38CC) == 0) {
        result = 0;
    }
    if (EnableEvent(D_800A38D0) == 0) {
        result = 0;
    }
    if (EnableEvent(D_800A38D4) == 0) {
        result = 0;
    }
    ExitCriticalSection();
    return result;
}

s32 CardCheckStatus(s32 slot, u8 returnOnBusy) {
    s32 channel;
    u32 retries;
    s32 status;

    channel = ((slot & 0xFF) != 0) * 0x10;
    retries = 0;
again:
    _card_info(channel);
    status = CardPollStatusEvents();
    switch (status) {
    case 0:
        return 0;
    case 3:
        CardTestTransferEvents();
        _card_clear(channel);
        status = CardWaitForEvent();
        if (returnOnBusy != 0) {
            return 3;
        }
        if (status == 0) {
            return 3;
        }
    }
    retries++;
    if ((retries & 0xFF) < 8) {
        goto again;
    }
    return status & 0xFF;
}

s32 CardFindFirstFile(char *path, struct DIRENTRY *entry) {
    return firstfile(path, entry) == entry;
}

extern char gMemoryCardDevice2[], gMemoryCardDevice1[];
s32 CardFormat(s32 slot) {
    if (!(slot & 0xFF))
        return format(gMemoryCardDevice1) & 0xFF;
    else
        return format(gMemoryCardDevice2) & 0xFF;
}

void CardOpenEvents(void) {
    s32 event;

    EnterCriticalSection();
    D_800A3824 = OpenEvent(0xF4000001, 4, 0x2000, 0);
    event = OpenEvent(0xF4000001, 0x8000, 0x2000, 0);
    D_800A3828 = event;
    if (event == -1) {
        event = 0;
    }
    event = OpenEvent(0xF4000001, 0x100, 0x2000, 0);
    D_800A382C = event;
    if (event == -1) {
        event = 0;
    }
    event = OpenEvent(0xF4000001, 0x2000, 0x2000, 0);
    D_800A3834 = event;
    if (event == -1) {
        event = 0;
    }
    event = OpenEvent(0xF0000011, 4, 0x2000, 0);
    D_800A38C8 = event;
    if (event == -1) {
        event = 0;
    }
    event = OpenEvent(0xF0000011, 0x8000, 0x2000, 0);
    D_800A38CC = event;
    if (event == -1) {
        event = 0;
    }
    event = OpenEvent(0xF0000011, 0x100, 0x2000, 0);
    D_800A38D0 = event;
    if (event == -1) {
        event = 0;
    }
    D_800A38D4 = OpenEvent(0xF0000011, 0x2000, 0x2000, 0);
    ExitCriticalSection();
}

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

void CardInit(void) {
    CardOpenEvents();
    InitCARD(1);
    _card_auto(0);
    StartCARD();
    _bu_init();
    ChangeClearPAD(0);
}

void CardStop(void) {
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

s32 func_80059F0C(s32 slot) {
    s32 retries = 0;
    s32 channel = ((slot & 0xFF) != 0) * 0x10;
    s32 status;
    do {
        _card_info(channel);
        status = CardPollStatusEvents();
        if (status == 3) {
            CardTestTransferEvents();
            _card_clear(channel);
            status = CardWaitForEvent();
        }
        if (status == 0) {
            CardTestEvents();
            _card_load(channel);
            status = CardPollStatusEvents();
            if (status == 0) {
                break;
            }
        }
        retries++;
        if (status == 0) {
            break;
        }
    } while ((retries & 0xFF) < 8U);
    retries = status;
    return retries & 0xFF;
}

s32 CardOpenFile(char *path, s32 flags) {
    if (flags == 0x200) {
        flags = 0x10200;
    }
    return open(path, flags);
}

extern void _new_card(void);
extern void _card_read(s32, s32, s32);
s32 CardReadSectors(s32 entry, s32 firstSector, s32 sectorCount, s32 slot,
                    s32 buffer) {
    s32 channel;
    s32 sector;
    s32 offset;
    s32 retries;
    s32 end;
    s32 limit;
    channel = ((slot & 0xFF) != 0) * 0x10;
    sectorCount = sectorCount & 0xFF;
    if (buffer == 0)
        goto success;
    retries = offset = 0;
    sector = (firstSector & 0xFF) + *(s32 *)(entry + 0x20);
    limit = (sector & 0xFFFF) + sectorCount;
    if ((sector & 0xFFFF) >= limit)
        goto success;
    end = limit;
    do {
        CardTestTransferEvents();
        _new_card();
        _card_read(channel, sector & 0xFFFF, buffer + offset);
        if (CardWaitForEvent() == 0) {
            sector += 1;
            offset += 0x80;
            retries = 0;
        } else if ((u32)(retries & 0xFF) < 0xBU) {
            retries += 1;
        } else {
            return 0;
        }
    } while ((sector & 0xFFFF) < end);
success:
    return 1;
}

extern void _card_write(s32, s32, s32);
s32 CardWriteSectors(s32 entry, s32 firstSector, s32 sectorCount, s32 slot,
                     s32 buffer) {
    s32 sector;
    u32 retries;
    s32 offset;
    s32 end;
    s32 limit;
    s32 channel;

    offset = 0;
    retries = 0;
    sector = (firstSector & 0xFF) + *(s32 *)(entry + 0x20);
    channel = ((slot & 0xFF) != 0) * 0x10;
    limit = (sector & 0xFFFF) + (sectorCount & 0xFF);
    if ((sector & 0xFFFF) < limit) {
        end = limit;
        do {
            CardTestTransferEvents();
            _new_card();
            _card_write(channel, sector & 0xFFFF, buffer + offset);
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
    }
    return 1;
}

/* gcc rounds a DIRENTRY[16] frame up by 0x20 but leaves [15] alone;
 * retail's locals are 15*0x28 + 8. The call-per-arm with the ==0 branch
 * sense reproduces the bnez/per-arm-a0/single-jal merge, and i=0 before
 * the blez lets total=0 fill its delay slot. */
s32 CardCountOtherFileBlocks(s32 slot, char *excludedName) {
    s32 zero;
    struct DIRENTRY entries[15];
    s32 count;
    u32 total;
    s32 i;
    struct DIRENTRY *entry;

    if ((slot & 0xFF) == 0) {
        count = CardScanDirectory(gMemoryCardDevice1, entries);
    } else {
        count = CardScanDirectory(gMemoryCardDevice2, entries);
    }
    i = 0;
    zero = 0;
    total = zero;
    if (count > zero) {
        entry = entries;
        do {
            if (strcmp(entry->name, excludedName) != 0) {
                total += entry->size;
            }
            i++;
            entry++;
        } while (i < count);
    }
    return (total >> 13) & 0xFF;
}

s32 CardPollStatusEvents(void) {
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

void CardTestEvents(void) {
    TestEvent(D_800A3824);
    TestEvent(D_800A3828);
    TestEvent(D_800A382C);
    TestEvent(D_800A3834);
}

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

void CardTestTransferEvents(void) {
    TestEvent(D_800A38C8);
    TestEvent(D_800A38CC);
    TestEvent(D_800A38D0);
    TestEvent(D_800A38D4);
}

extern char gMemoryCardWildcard[];

s32 CardScanDirectory(char *path, struct DIRENTRY *entry) {
    char buffer[128];
    struct DIRENTRY *cursor;
    s32 count;

    strcpy(buffer, path);
    strcat(buffer, gMemoryCardWildcard);
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
void MenuFontReset(void) {
    u8 i;

    for (i = 0; i < 5; i++) {
        D_800B1EBC[i] = 0;
    }
    D_800A3874 = 0;
    D_800A3768 = D_800A39E8;
    MenuSetTextColor(0xFF, 0x80, 0x40);
}

void MenuFontBuildPrimitives(u8 poolIndex, u8 textureIndex) {
    typedef struct {
        s16 x;
        s16 y;
        u8 w;
        u8 h;
        u8 ax;
        u8 pad;
        u8 ay;
    } Dim;
    typedef struct {
        u8 count;
        u8 pad;
        u16 x;
        u16 y;
        Dim *table;
    } Entry;
    typedef struct {
        u8 b[0x28];
    } Prim28;
    extern Entry D_80099FE4_g1b[] asm("D_80099FE4");
    extern Prim28 *D_800A3768_g1b asm("D_800A3768");
    Entry *entry;
    Dim *table;
    Dim *dim;
    s32 *slot;
    s32 *base;
    u32 idx;
    u8 *prim;
    u8 *p;
    u16 i;
    Prim28 *old;
    u8 n;
    u16 count;
    u32 total;
    u32 bound;
    u16 w;

    entry = &D_80099FE4_g1b[textureIndex];
    n = entry->count;
    idx = poolIndex;
    old = D_800A3768_g1b;
    base = D_800B1EBC;
    slot = idx + base;
    do {
    } while (0);
    w = D_800A3874;
    *slot = (s32)old;
    count = n;
    prim = *(u8 *volatile *)slot;
    D_800A3874 = w + count;
    D_800A3768_g1b = old + n;
    table = (Dim *)entry->table;
    total = count;
    if (total != 0) {
        i = 0;
        bound = total;
        do {
            p = prim + 0x25;
            *(u16 *)(p - 0x17) = GetClut(entry->x, entry->y);
            dim = (Dim *)(i * 10 + (s32)table);
            *(u16 *)(p - 0xF) = GetTPage(0, 0, dim->x, dim->y);
            p[-0x19] = dim->w;
            p[-0x18] = dim->h;
            p[-0x11] = dim->w + dim->ax;
            p[-0x10] = dim->h;
            p[-0x9] = dim->w;
            p[-0x8] = dim->h + dim->ay;
            p[-0x1] = dim->w + dim->ax;
            p[0] = dim->h + dim->ay;
            SetSemiTrans(prim, 1);
            prim += 0x28;
            i++;
        } while (i < bound);
    }
}

void MenuFontCopyGlyphPrimitives(u8 fontId, s32 fontScale, void *dest) {
    typedef struct {
        u32 w[4];
    } W16;
    typedef struct {
        u32 w[2];
    } W8;
    extern s32 D_800B1EBCx[] asm("D_800B1EBC");
    extern u8 *D_800A35A0p asm("D_800A35A0");
    extern u8 *D_800A3750p asm("D_800A3750");
    u8 *src;
    volatile u8 *d;
    u8 *s;
    u8 *e;
    volatile u32 pad[2];
    s32 count;
    s32 i;
    s32 n;
    volatile u8 *cursor;

    MenuFontSet(fontId & 0xFF, fontScale & 0xFF);
    count = *D_800A35A0p;
    src = D_800A3750p;
    cursor = (volatile u8 *)dest;
    i = 0;
    if (count > 0) {
        n = count;
        do {
            d = cursor;
            s = src;
            e = s + 0x20;
            do {
                *(W16 *)d = *(W16 *)s;
                s += 0x10;
                d += 0x10;
            } while (s != e);
            *(W8 *)d = *(W8 *)s;
            src += 0x28;
            cursor += 0x28;
            i++;
        } while (i < n);
    }
    D_800B1EBCx[fontId & 0xFF] = (s32)dest;
}

extern s32 D_800A35A0;
extern u8 D_800A3534;
extern s32 D_800A3750;
extern s32 D_800A35AC;
extern s32 D_80099FE4[][3];
void MenuFontSet(u8 fontId, u8 fontScale) {
    s32 *entry;
    s32 word;

    word = D_800B1EBC[fontId];
    entry = &D_80099FE4[fontScale][0];
    D_800A35A0 = (s32)entry;
    D_800A3534 = fontScale;
    D_800A3750 = word;
    D_800A35AC = entry[2];
}

extern u8 D_800A37C8, D_800A37A8, D_800A378C;
void MenuSetShadeColors(u8 red, u8 green, u8 blue) {
    D_800A37C8 = red;
    D_800A37A8 = green;
    D_800A378C = blue;
}

extern u8 D_800A3618;
extern u8 D_800A3624;
extern u8 D_800A364C;

void MenuSetTextColor(u8 red, u8 green, u8 blue) {
    D_800A364C = red;
    D_800A3624 = green;
    D_800A3618 = blue;
}

void MenuResetTextColor(void) {
    D_800A364C = 0xFF;
    D_800A3624 = 0x80;
    D_800A3618 = 0x40;
}

s16 MenuFontLineHeight(void) {
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

s16 MenuStringWidth(u8 *text) {
    s32 total;
    s32 idx;
    s32 glyphCount;
    s32 limit;
    u8 ch;
    s32 i;

    glyphCount = *(u16 *)D_800A35A0;
    i = 0;
    total = 0;
    if (*text != 0) {
        limit = glyphCount + 0x20;
        do {
            ch = text[i];
            idx = 0;
            if (ch >= 0x20) {
                if (ch < limit) {
                    idx = ch - 0x20;
                }
            }
            if (D_800A3534 == 2) {
                total += *(s16 *)(D_800A35AC + idx * 10 + 6) * 3 / 4;
            } else if (D_800A3534 == 4) {
                total += *(s16 *)(D_800A35AC + idx * 10 + 6) * 9 / 10;
            } else {
                total += *(u16 *)(D_800A35AC + idx * 10 + 6);
            }
            if (D_800A3534 < 2) {
                total -= 1;
            }
            i++;
        } while (text[i] != 0);
    }
    return total;
}

/* Draws a string as one POLY_FT4 per glyph, starting at (x, y). The glyph
   templates (D_800A3750) and metrics (D_800A35AC) come from the font loaded
   by the function above; D_800A3534 picks the scale (2 = 3/4 with its own
   CLUT, 4 = 9/10). '\n' returns to x and moves down one line. center
   right-aligns the string to end at x, shade picks the tint, semi sets
   semi-transparency, and advance replaces the glyph width when non-zero. */
void MenuDrawString(u8 *text, s16 x, s16 y, u8 center, u8 shade, s32 otz,
                    u8 semi, u8 advance) {
    s16 penX;
    s32 i;
    u16 clut;
    u16 limit;
    POLY_FT4 *prim;
    POLY_FT4 *tmpl;
    u8 *glyph;
    s16 idx;
    s32 w;
    s32 h;
    u8 ch;
    s16 lineH;

    limit = *(u16 *)D_800A35A0;
    limit += 0x20;
    if (center) {
        penX = x - MenuStringWidth(text);
    } else {
        penX = x;
    }
    if (D_800A3534 == 2) {
        clut = GetClut(0x100, 0x1FF);
    }
    i = 0;
    if (text[0] != 0) {
        do {
            ch = text[i];
            if (ch == '\n') {
                penX = x;
                if (D_800A3534 == 2) {
                    lineH = *(s16 *)(D_800A35AC + 8) * 3 / 4;
                } else if (D_800A3534 == 4) {
                    lineH = *(s16 *)(D_800A35AC + 8) * 9 / 10;
                } else {
                    lineH = *(s16 *)(D_800A35AC + 8);
                }
                y += lineH;
                i++;
            } else {
                if (ch >= 0x20 && ch < limit) {
                    idx = ch - 0x20;
                } else {
                    idx = 0;
                }
                tmpl = (POLY_FT4 *)D_800A3750 + idx;
                glyph = (u8 *)D_800A35AC + idx * 10;
                if (D_800A3534 == 2) {
                    h = *(s16 *)(glyph + 8) * 3 / 4;
                    w = *(s16 *)(glyph + 6) * 3 / 4;
                } else if (D_800A3534 == 4) {
                    h = *(s16 *)(glyph + 8) * 9 / 10;
                    w = *(s16 *)(glyph + 6) * 9 / 10;
                } else {
                    h = *(s16 *)(glyph + 8);
                    w = *(s16 *)(glyph + 6);
                }
                if (penX + w >= 0 && penX < 0x140 && y + h >= 0 && y < 0xF0) {
                    prim = (POLY_FT4 *)GraphicsAllocPolyFT4(0);
                    *prim = *tmpl;
                    if (D_800A3534 == 2) {
                        prim->clut = clut;
                    }
                    SetSemiTrans(prim, semi);
                    prim->x0 = penX;
                    prim->y0 = y;
                    prim->x1 = penX + w;
                    prim->y1 = y;
                    prim->x2 = penX;
                    prim->y2 = y + h;
                    prim->x3 = penX + w;
                    prim->y3 = y + h;
                    if (shade == 3) {
                        SetShadeTex(prim, 0);
                        prim->r0 = D_800A37C8 >> 2;
                        prim->g0 = D_800A37A8 >> 2;
                        prim->b0 = D_800A378C >> 2;
                    } else if (shade == 2) {
                        SetShadeTex(prim, 0);
                        prim->r0 = 0x40;
                        prim->g0 = 0x40;
                        prim->b0 = 0x40;
                    } else if (shade == 1) {
                        SetShadeTex(prim, 0);
                        prim->r0 = D_800A37C8;
                        prim->g0 = D_800A37A8;
                        prim->b0 = D_800A378C;
                    } else {
                        SetShadeTex(prim, 1);
                    }
                    if ((D_800A364C != 0 || D_800A3624 != 0 ||
                         D_800A3618 != 0) &&
                        shade == 0) {
                        SetShadeTex(prim, 0);
                        prim->r0 = D_800A364C;
                        prim->g0 = D_800A3624;
                        prim->b0 = D_800A3618;
                    }
                    AddPrim((u8 *)gOrderingTable[0] + otz * 4, prim);
                }
                if (advance != 0) {
                    penX = advance + penX;
                } else {
                    penX += w;
                }
                if (D_800A3534 < 2) {
                    penX--;
                }
                i++;
            }
        } while (text[i] != 0);
    }
}

/* Sums the glyph widths of the first count characters of str. The glyph
   table (D_800A35AC) holds 10-byte records with the width at offset 6;
   D_800A3534 picks the scale (2 = 3/4, 4 = 9/10) and subtracts 1 per
   character when below 2. */
s16 MenuPrefixWidth(u8 count, u8 *text) {
    s32 total;
    s32 i;
    s32 idx;
    s32 glyphCount;
    s32 limit;
    u8 ch;

    glyphCount = *(u16 *)D_800A35A0;
    i = 0;
    total = 0;
    if (*text != 0) {
        limit = glyphCount + 0x20;
        while (text[i] != 0 && i < count) {
            ch = text[i];
            idx = 0;
            if (ch >= 0x20) {
                if (ch < limit) {
                    idx = ch - 0x20;
                }
            }
            if (D_800A3534 == 2) {
                total += *(s16 *)(D_800A35AC + idx * 10 + 6) * 3 / 4;
            } else if (D_800A3534 == 4) {
                total += *(s16 *)(D_800A35AC + idx * 10 + 6) * 9 / 10;
            } else {
                total += *(u16 *)(D_800A35AC + idx * 10 + 6);
            }
            if (D_800A3534 < 2) {
                total -= 1;
            }
            i++;
        }
    }
    return total;
}

s16 MenuCharWidth(s8 character) {
    s32 index;
    s32 entry;
    s32 scaled;
    short value;
    s32 product;
    s32 quotient;
    entry = *((u16 *)D_800A35A0);
    index = 0;
    if ((character >= 0x20) && (character < (entry + 0x20))) {
        index = character - 0x20;
    }
    if (D_800A3534 == 2) {
        scaled = (*((s16 *)((D_800A35AC + (index * 0xA)) + 6))) * 3;
        value = ((u32)scaled) >> 2;
        if (scaled < 0) {
            scaled += 3;
            value = ((u32)scaled) >> 2;
        }
    } else if (D_800A3534 == 4) {
        value = *((s16 *)((D_800A35AC + (index * 0xA)) + 6));
        product = value * 9;
        value = product / 10;
    } else {
        value = *((u16 *)((D_800A35AC + (index * 0xA)) + 6));
    }
    if (D_800A3534 < 2U) {
        value -= 1;
    }
    return (s16)value;
}

s32 MenuTextCenterOffset(s16 maxWidth, s32 text) {
    s32 limit;

    limit = MenuStringWidth(text);
    if (maxWidth < limit) {
        return 0;
    }
    return (maxWidth - limit) >> 1;
}

#ifdef NON_MATCHING
s32 TextCountLines(u8 *text) {
    s32 count;
    u8 c;

    count = 0;
    c = *text;
    while (c != 0) {
        if (c == 0xA) {
            count++;
        }
        text++;
        c = *text;
    }
    return count + 1;
}
#else
s32 TextCountLines(u8 *text) {
    s32 count;

    count = 0;
    if (*text != 0) {
        do {
            if (*text == 0xA) {
                count++;
            }
            text++;
        } while (*text != 0);
    }
    return count + 1;
}
#endif

void MenuSetTexturedQuad(POLY_FT4 *dst, u32 idx, u16 dx, u16 dy, u16 ax,
                         u16 ay) {
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
    dst->clut = GetClut(entry->f4, entry->f6);
    dst->tpage = GetTPage(entry->fC, 3, entry->f0, entry->f2);
    dst->u0 = entry->f8 + dx;
    dst->v0 = entry->fA + dy;
    dst->u1 = entry->f8 + dx + ax;
    dst->v1 = entry->fA + dy;
    dst->u2 = entry->f8 + dx;
    dst->v2 = entry->fA + dy + ay;
    dst->u3 = entry->f8 + dx + ax;
    dst->v3 = entry->fA + dy + ay;
}

MenuObj *MenuObjAlloc(void) {
    u8 index;
    MenuObj *object;
    index = gMenuObjectPoolCount++;
    object = &gMenuObjectPool[index];
    object->drawOffsetX = 0;
    object->drawOffsetY = 0;
    object->next = 0;
    object->blue = 0;
    object->green = 0;
    object->red = 0;
    object->orderingDepth = 0;
    return object;
}

void MenuObjResetPool(void) {
    D_800A37BC = 0;
    gMenuObjectPoolCount = 0;
}

void MenuObjRestorePoolCursor(void) {
    D_800A37BC = 0;
    gMenuObjectPoolCount = D_800A39C4;
}

MenuObj *MenuCreateFlatRect(x, y, width, height, poly, red, green, blue,
                            semiTrans, texture)
s32 x;
s32 y;
s32 width;
s32 height;
s32 poly;
u8 red;
u8 green;
u8 blue;
u8 semiTrans;
u8 texture;
{
    u8 index;
    MenuObj *object;

    index = gMenuObjectPoolCount++;
    object = &gMenuObjectPool[index];
    object->drawOffsetX = 0;
    object->drawOffsetY = 0;
    object->next = 0;
    object->blue = 0;
    object->green = 0;
    object->red = 0;
    object->orderingDepth = 0;
    object->kind = 2;
    object->x = x;
    object->targetX = x;
    object->y = y;
    object->targetY = y;
    object->velocityX = 0;
    object->velocityY = 0;
    object->width = width;
    object->height = height;
    object->red = red;
    object->green = green;
    object->blue = blue;
    if (poly == 0) {
        poly = (s32)GraphicsAllocPolyF4(texture);
    }
    object->primitive = (u8 *)poly;
    SetPolyF4((u8 *)poly);
    SetSemiTrans((void *)poly, semiTrans);
    ((u8 *)poly)[4] = red;
    ((u8 *)poly)[5] = green;
    ((u8 *)poly)[6] = blue;
    *(s16 *)((u8 *)poly + 0x8) = x;
    *(s16 *)((u8 *)poly + 0xA) = y;
    *(s16 *)((u8 *)poly + 0xC) = x + width;
    *(s16 *)((u8 *)poly + 0xE) = y;
    *(s16 *)((u8 *)poly + 0x10) = x;
    *(s16 *)((u8 *)poly + 0x12) = y + height;
    *(s16 *)((u8 *)poly + 0x14) = x + width;
    *(s16 *)((u8 *)poly + 0x16) = y + height;
    return (MenuObj *)object;
}

extern void SetPolyF3(POLY_F3 *);
MenuObj *MenuCreateFlatTriangle(x, y, width, height, poly, red, green, blue,
                                semiTrans, texture, mode)
s32 x;
s32 y;
s32 width;
s32 height;
s32 poly;
u8 red;
u8 green;
u8 blue;
u8 semiTrans;
u8 texture;
u8 mode;
{
    u8 index;
    MenuObj *fresh;
    MenuObj *object;

    index = gMenuObjectPoolCount++;
    fresh = &gMenuObjectPool[index];
    fresh->drawOffsetX = 0;
    fresh->drawOffsetY = 0;
    fresh->next = 0;
    fresh->blue = 0;
    fresh->green = 0;
    fresh->red = 0;
    fresh->orderingDepth = 0;
    object = fresh;
    object->kind = mode != 0 ? 7 : 8;
    object->x = x;
    object->targetX = x;
    object->y = y;
    object->targetY = y;
    object->velocityX = 0;
    object->velocityY = 0;
    object->width = width;
    object->height = height;
    object->red = red;
    object->green = green;
    object->blue = blue;
    if (poly == 0) {
        poly = (s32)GraphicsAllocPolyF4(texture);
    }
    object->primitive = (u8 *)poly;
    SetPolyF3((POLY_F3 *)poly);
    SetSemiTrans((void *)poly, semiTrans);
    ((u8 *)poly)[4] = red;
    ((u8 *)poly)[5] = green;
    ((u8 *)poly)[6] = blue;
    return object;
}

MenuObj *MenuCreateTexturedRect(s32 left, s32 top, s32 right, s32 bottom,
                                s32 depth, u8 texture, u8 semiTrans) {
    u8 index;
    MenuObj *object;
    POLY_FT4 *poly;
    index = gMenuObjectPoolCount++;
    object = &gMenuObjectPool[index];
    object->drawOffsetX = 0;
    object->drawOffsetY = 0;
    object->next = 0;
    object->blue = 0;
    object->green = 0;
    object->red = 0;
    object->orderingDepth = 0;
    object->kind = 1;
    object->targetX = left;
    object->x = left;
    object->targetY = top;
    object->y = top;
    object->width = right;
    object->height = bottom;
    object->velocityX = 0;
    object->velocityY = 0;
    poly = (POLY_FT4 *)(GraphicsAllocPolyFT4(texture));
    SetPolyFT4(poly);
    SetShadeTex(poly, 0);
    poly->r0 = 0x80;
    poly->g0 = 0x80;
    poly->b0 = 0x80;
    SetSemiTrans(poly, semiTrans);
    object->primitive = poly;
    object->orderingDepth = depth;
    return object;
}

void MenuUpdateObjectPosition(MenuObj *first, u8 friction) {
    MenuObj *object;
    s16 sum;

    object = first;
    if (object != 0) {
        do {
            if (object->velocityX != 0) {
                sum = (u16)object->x + object->velocityX;
                object->x = sum;
                if ((object->velocityX < 0 && sum < object->targetX) ||
                    (object->velocityX > 0 && object->targetX < sum)) {
                    object->velocityX = 0;
                    object->x = (u16)object->targetX;
                } else if (friction != 0) {
                    object->velocityX = (u16)object->velocityX +
                                        (s16)(u16)object->velocityX / 2;
                }
            }
            if (object->velocityY != 0) {
                sum = (u16)object->y + object->velocityY;
                object->y = sum;
                if ((object->velocityY < 0 && sum < object->targetY) ||
                    (object->velocityY > 0 && object->targetY < sum)) {
                    object->velocityY = 0;
                    object->y = (u16)object->targetY;
                } else if (friction != 0) {
                    object->velocityY = (u16)object->velocityY +
                                        (s16)(u16)object->velocityY / 2;
                }
            }
            object = object->next;
        } while (object != 0);
    }
}

void MenuDrawF4Object(MenuObj *object, s32 orderingDepth, u8 semiTrans) {
    POLY_F4 *poly;

    poly = (POLY_F4 *)(u8 *)object->primitive;
    poly->x0 = (u16)object->x;
    poly->y0 = (u16)object->y;
    poly->x1 = (u16)object->x + (u16)object->width;
    poly->y1 = (u16)object->y;
    poly->x2 = (u16)object->x;
    poly->y2 = (u16)object->y + (u16)object->height;
    poly->x3 = (u16)object->x + (u16)object->width;
    poly->y3 = (u16)object->y + (u16)object->height;
    if (semiTrans != 0xFF) {
        SetSemiTrans(poly, semiTrans);
    }
    AddPrim(gOrderingTable[0] + orderingDepth * 4, poly);
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

void MenuDrawObjectList(MenuObj *object, s32 semiTransMode) {
    u8 *src;
    POLY_F4 *poly;
    s32 semiTrans;
    s32 half;
    u8 scratch[0x40];

    if (object == 0) {
        return;
    }
    semiTrans = semiTransMode & 0xFF;
    for (; object != 0; object = object->next) {
        if (object->orderingDepth >= 0) {
            if (gScreenStateAbsolute[0] != 0xD || (s8)object->unk5 != 0) {
                switch (*(u16 *)(object)) {
                case 1: {
                    POLY_FT4 *prim;
                    u8 *src;
                    u8 *dst;
                    u8 *end;

                    prim = (POLY_FT4 *)(GraphicsAllocPolyFT4(0));
                    src = object->primitive;
                    dst = prim;
                    end = src + 0x20;
                    do {
                        *(UnkQuad *)dst = *(UnkQuad *)src;
                        src += 0x10;
                        dst += 0x10;
                    } while (src != end);
                    *(UnkPrim8 *)dst = *(UnkPrim8 *)src;
                    if (gScreenStateAbsolute[0] == 0xD) {
                        prim->x0 = (u16)object->x + (u16)object->drawOffsetX;
                        prim->y0 = (u16)object->y + (u16)object->drawOffsetY;
                        prim->x1 = (u16)object->x + (u16)object->drawOffsetX +
                                   (u16)object->width;
                        prim->y1 = (u16)object->y + (u16)object->drawOffsetY;
                        prim->x2 = (u16)object->x + (u16)object->drawOffsetX;
                        prim->y2 = (u16)object->y + (u16)object->drawOffsetY +
                                   (u16)object->height;
                        prim->x3 = (u16)object->x + (u16)object->drawOffsetX +
                                   (u16)object->width;
                        prim->y3 = (u16)object->y + (u16)object->drawOffsetY +
                                   (u16)object->height;
                    } else {
                        prim->x0 = (u16)object->x;
                        prim->y0 = (u16)object->y;
                        prim->x1 = (u16)object->x + (u16)object->width;
                        prim->y1 = (u16)object->y;
                        prim->x2 = (u16)object->x;
                        prim->y2 = (u16)object->y + (u16)object->height;
                        prim->x3 = (u16)object->x + (u16)object->width;
                        prim->y3 = (u16)object->y + (u16)object->height;
                    }
                    AddPrim(gOrderingTable[0] + object->orderingDepth * 4,
                            prim);
                    break;
                }
                case 2: {
                    u8 *src2;

                    poly = (POLY_F4 *)(GraphicsAllocPolyF4(0));
                    src2 = object->primitive;
                    *(UnkPrim18 *)poly = *(UnkPrim18 *)src2;
                    if (gScreenStateAbsolute[0] == 0xD) {
                        if (object->width == 0) {
                            break;
                        }
                        if (object->height == 0) {
                            break;
                        }
                        poly->x0 = (u16)object->x + (u16)object->drawOffsetX;
                        poly->y0 = (u16)object->y + (u16)object->drawOffsetY;
                        poly->x1 = (u16)object->x + (u16)object->drawOffsetX +
                                   (u16)object->width;
                        poly->y1 = (u16)object->y + (u16)object->drawOffsetY;
                        poly->x2 = (u16)object->x + (u16)object->drawOffsetX;
                        poly->y2 = (u16)object->y + (u16)object->drawOffsetY +
                                   (u16)object->height;
                        poly->x3 = (u16)object->x + (u16)object->drawOffsetX +
                                   (u16)object->width;
                        poly->y3 = (u16)object->y + (u16)object->drawOffsetY +
                                   (u16)object->height;
                    } else {
                        poly->x0 = (u16)object->x;
                        poly->y0 = (u16)object->y;
                        poly->x1 = (u16)object->x + (u16)object->width;
                        poly->y1 = (u16)object->y;
                        poly->x2 = (u16)object->x;
                        poly->y2 = (u16)object->y + (u16)object->height;
                        poly->x3 = (u16)object->x + (u16)object->width;
                        poly->y3 = (u16)object->y + (u16)object->height;
                    }
                    if (semiTrans != 0xFF) {
                        SetSemiTrans(poly, semiTrans);
                    }
                    AddPrim(gOrderingTable[0] + object->orderingDepth * 4,
                            poly);
                    break;
                }
                case 7:
                case 8:
                    poly = (POLY_F4 *)(GraphicsAllocPolyF4(0));
                    src = object->primitive;
                    *(UnkPrim14 *)poly = *(UnkPrim14 *)src;
                    if (*(u16 *)(object) == 7) {
                        half = object->width / 2;
                        if (object->height < 0) {
                            poly->x0 =
                                (u16)object->x + (u16)object->drawOffsetX;
                            poly->y0 =
                                (u16)object->y + (u16)object->drawOffsetY;
                            poly->x1 = (u16)object->x +
                                       (u16)object->drawOffsetX - half;
                            poly->y1 = (u16)object->y +
                                       (u16)object->drawOffsetY +
                                       (u16)object->height;
                            poly->x2 = (u16)object->x +
                                       (u16)object->drawOffsetX + half;
                            poly->y2 = (u16)object->y +
                                       (u16)object->drawOffsetY +
                                       (u16)object->height;
                        } else {
                            poly->x0 =
                                (u16)object->x + (u16)object->drawOffsetX;
                            poly->y0 =
                                (u16)object->y + (u16)object->drawOffsetY;
                            poly->x1 = (u16)object->x +
                                       (u16)object->drawOffsetX + half;
                            poly->y1 = (u16)object->y +
                                       (u16)object->drawOffsetY +
                                       (u16)object->height;
                            poly->x2 = (u16)object->x +
                                       (u16)object->drawOffsetX - half;
                            poly->y2 = (u16)object->y +
                                       (u16)object->drawOffsetY +
                                       (u16)object->height;
                        }
                    } else {
                        half = object->height / 2;
                        poly->x0 = (u16)object->x + (u16)object->drawOffsetX;
                        poly->y0 = (u16)object->y + (u16)object->drawOffsetY;
                        poly->x1 = (u16)object->x + (u16)object->drawOffsetX +
                                   (u16)object->width;
                        poly->y1 =
                            (u16)object->y + (u16)object->drawOffsetY + half;
                        poly->x2 = (u16)object->x + (u16)object->drawOffsetX +
                                   (u16)object->width;
                        poly->y2 =
                            (u16)object->y + (u16)object->drawOffsetY - half;
                    }
                    if (semiTrans != 0xFF) {
                        SetSemiTrans(poly, semiTrans);
                    }
                    AddPrim(gOrderingTable[0] + object->orderingDepth * 4,
                            poly);
                    break;

                case 0:
                    func_8005CF34(object, 0, 0, 0, 0);
                    break;
                case 5:
                    func_8005C020(object, scratch);
                    func_8005CF34(object, 0, 0, 0, (s32)scratch);
                    break;
                case 6:
                    MenuFormatTimeObject(object, (s32)scratch);
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

s32 MenuAllocTextPacket(void) {
    u8 index;
    index = D_800A37BC;
    D_800A37BC = index + 1;
    return D_800A3654 + index * 12;
}

MenuObj *MenuCreateTextObject(s32 left, s32 top) {
    u8 spriteIndex;
    u8 primIndex;
    MenuObj *object;
    u8 *prim;
    MenuObj *base;

    spriteIndex = gMenuObjectPoolCount++;
    base = gMenuObjectPool;
    object = &base[spriteIndex];
    object->blue = 0;
    object->green = 0;
    object->red = 0;
    primIndex = D_800A37BC;
    *(u16 *)&object->targetX = left;
    *(u16 *)&object->x = left;
    prim = (u8 *)D_800A3654;
    *(u16 *)&object->drawOffsetX = 0;
    *(u16 *)&object->drawOffsetY = 0;
    *(u32 *)&object->next = 0;
    *(u16 *)&object->orderingDepth = 0;
    *(u16 *)&object->kind = 0;
    *(u16 *)&object->targetY = top;
    *(u16 *)&object->y = top;
    *(u16 *)&object->velocityX = 0;
    *(u16 *)&object->velocityY = 0;
    *(u16 *)&object->orderingDepth = 0;
    D_800A37BC = primIndex + 1;
    do {
    } while (0);
    prim += primIndex * 12;
    *(u8 **)&object->primitive = prim;
    prim[0] = 0;
    prim[3] = 0;
    *(s32 *)(prim + 4) = 0;
    return (MenuObj *)object;
}

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
extern Unk4 gTextThreeDashes[];
extern Unk4 gTextDnf[];
extern Unk3 gTextTwoSpaces[];
void func_8005C020(MenuObj *object, u8 *dest) {
    s32 id;

    id = *(s16 *)((u8 *)object->primitive + 8);
    if (gScreenState[0] == 0xA) {
        if (id == 0xFF) {
            *(Unk4 *)dest = gTextThreeDashes[0];
            return;
        }
        if (id == -1) {
            *(Unk4 *)dest = gTextDnf[0];
            return;
        }
    } else if (gScreenState[0] == 0xC) {
        if (id == 0) {
            *(Unk3 *)dest = gTextTwoSpaces[0];
            return;
        }
    }
    TextFormatInt(id, dest);
}

void MenuFormatTimeObject(MenuObj *object, s32 value) {
    TextFormatTime(*(void **)((u8 *)object->primitive + 8), -1, value);
}

extern u8 *D_8009A05C[];
extern u8 *D_8009A078[];
extern u8 *D_8009A098[];
extern u8 *D_8009A0B8[];
extern u8 *D_8009A0D8[];
extern u8 *D_8009A0F4[];
extern u8 *D_8009A110[];
extern u8 *D_8009A134[];
extern u8 *D_8009A158[];
extern u8 *D_8009A17C[];
extern u8 *D_8009A19C[];
extern u8 *D_8009A1BC[];
extern u8 *D_8009A1DC[];
extern u8 *D_8009A200[];
extern u8 *D_8009A21C[];
extern u8 *D_8009A228[];
extern u8 *D_8009A248[];
extern u8 *D_8009A2C4[];
extern u8 *D_8009ABFC[];
extern u8 D_8009AF74[];
extern u8 *D_800A3690;
extern u8 *D_800A39C0;
extern u8 *D_800A3A28;
extern MenuObj *D_800A39B8;
extern MenuObj *D_800A36F0;
extern MenuObj *D_800A38F8;
extern u8 D_800A38E8;
extern u8 D_800A3644[];
extern u8 D_800A3950[];
extern u8 D_800A3988[];
extern u8 D_800A3989[];
extern MenuObj *D_800AE27C[];
extern MenuObj *D_800BB9E4[];
extern u8 gFormatLeadingSpacesZeroesPercentWildcard[];
extern u8 D_800AD980[];
extern u8 D_800A35C8Text[] asm("D_800A35C8");
extern void TextFormatPercentage(s32);
void func_8005C124(u8 menuId, u8 selRow) {
    s32 slots[3][4];
    MenuObj *item;
    u8 *entry;
    u8 *text;
    s32 i;
    s32 rows;
    s32 count;
    s32 savedY;
    s32 y;
    s32 x;
    s32 d;
    s32 width;

    count = 0;
    D_800A39C0 = 0;
    D_800A3A28 = 0;
    switch (menuId) {
    case 0:
        D_800A3690 = (u8 *)D_8009A05C;
        break;
    case 1:
        D_800A3690 = (u8 *)D_8009A0B8;
        break;
    case 2:
        D_800A3690 = (u8 *)D_8009A078;
        D_800A39C0 = (u8 *)D_8009A098;
        break;
    case 4:
        D_800A3690 = (u8 *)D_8009A110;
        D_800A39C0 = (u8 *)D_8009A134;
        D_800A3A28 = (u8 *)D_8009A158;
        break;
    case 5:
        D_800A3690 = (u8 *)D_8009A0D8;
        D_800A39C0 = (u8 *)D_8009A0F4;
        break;
    case 3:
        D_800A3690 = (u8 *)D_8009A1DC;
        break;
    case 6:
        D_800A3690 = (u8 *)D_8009A200;
        break;
    case 8:
        D_800A3690 = (u8 *)D_8009A21C;
        break;
    case 7:
        D_800A3690 = (u8 *)D_8009A228;
        D_800A39C0 = (u8 *)D_8009A248;
        break;
    case 13:
        D_800A3690 = (u8 *)D_8009ABFC;
        break;
    case 11:
        D_800A3690 = (u8 *)D_8009A17C;
        D_800A39C0 = (u8 *)D_8009A19C;
        D_800A3A28 = (u8 *)D_8009A1BC;
        break;
    case 15:
        D_800A3690 = (u8 *)D_8009A2C4;
        break;
    case 9:
    case 10:
    case 12:
    case 14:
        break;
    }
    x = 0x20;
    D_800A38E8 = D_8009AF74[menuId];
    y = 0x32;
    if (menuId == 0xD && D_800A3644[0] != 0) {
        y = 0x2A;
    }
    rows = D_800A38E8 + 1;
    if (menuId == 4) {
        rows = D_800A38E8 + 2;
    }
    if (menuId == 0xB) {
        rows += 5;
    }
    for (i = 0; i < rows; i++) {
        {
            u8 index;
            MenuObj *object;

            index = gMenuObjectPoolCount++;
            object = &gMenuObjectPool[index];
            object->drawOffsetX = 0;
            object->drawOffsetY = 0;
            object->next = 0;
            object->blue = 0;
            object->green = 0;
            object->red = 0;
            object->orderingDepth = 0;
            item = object;
        }
        item->kind = 0;
        item->orderingDepth = 0;
        item->targetY = y;
        item->y = y;
        if (menuId == 2) {
            if (i >= 5) {
                D_800AE27C[i] = item;
            }
            if (i == 5) {
                savedY = y;
            }
            if (D_800A3988[0] == 0) {
                if (i >= 5) {
                    if (i < 7)
                        goto lowRow;
                    if (i == 7)
                        goto lastRow;
                    goto rowDone;
                lowRow:
                    item->y = 0xF1;
                    goto rowDone;
                lastRow:
                    item->y = savedY;
                }
            }
        } else if (menuId == 5 && i == 6) {
            item->y = y + 0xF;
            item->targetY = y + 0xF;
            item->red = 0xC8;
            item->green = 0x40;
            item->blue = 0x40;
            D_800AE290[0] = (s16 *)item;
        } else {
            item->y = y;
        }
    rowDone:
        entry = (u8 *)(D_800A3654 + D_800A37BC++ * 0xC);
        item->primitive = entry;
        if (i == selRow + 1) {
            entry[0] = 1;
        } else {
            entry[0] = 0;
        }
        if (menuId == 1)
            goto check1;
        if (menuId == 0x24)
            goto check1;
        if (menuId == 0x28)
            goto check1;
        if (menuId == 0x25)
            goto check1;
        if (menuId != 0x27)
            goto check3;
    check1:
        if (D_800A3950[0] == 0) {
            if ((u32)(i - 3) < 4)
                goto setFlag;
        }
    check3:
        if (menuId == 3) {
            if (D_800A3644[0] != 0) {
                if ((u32)(i - 3) < 2)
                    goto setFlag;
            }
        }
        if (menuId != 4)
            goto noFlag;
        if (D_800A3644[0] == 0)
            goto noFlag;
        if (i != 6)
            goto noFlag;
    setFlag:
        entry[0] |= 2;
    noFlag:
        entry[3] = 0;
        *(s32 *)(entry + 4) = 0;
        item->velocityY = 0;
        if (i == 0) {
            D_800A39B8 = item;
            MenuFontSet(1, 1);
            entry[2] = 1;
            entry[1] = 1;
            *(u8 **)(entry + 8) = *(u8 **)D_800A3690;
            item->velocityX = -2;
        } else {
            if (i == 1) {
                D_800A36F0 = item;
                MenuFontSet(0, 0);
            }
            entry[2] = 0;
            entry[1] = 0;
            if (menuId == 4 && D_800A38E8 < i) {
                D_800A38F8 = item;
                TextFormatPercentage(D_800A37D0[0]);
                *(u8 **)(entry + 8) = D_800A35C8Text;
            } else if (menuId == 0xB && (d = D_800A38E8) < i) {
                d = i - d;
                D_800BB9E4[d - 1] = item;
                TextFormatPercentage(D_800A331C[d - 1]);
                text = D_800AD980 + (i - D_800A38E8) * 8;
                *(u8 **)(entry + 8) = text;
                strcpy(text, D_800A35C8Text);
            } else {
                switch (D_800A3989[i - 2]) {
                case 0:
                case 0x80:
                    *(u8 **)(entry + 8) = ((u8 **)D_800A3690)[i];
                    if (D_800A3989[i - 2] == 0x80) {
                        entry[0] |= 2;
                    }
                    break;
                case 1:
                case 0x81:
                    *(u8 **)(entry + 8) = ((u8 **)D_800A39C0)[i];
                    if (D_800A3989[i - 2] == 0x81) {
                        entry[0] |= 2;
                    }
                    break;
                case 2:
                    *(u8 **)(entry + 8) = ((u8 **)D_800A3A28)[i];
                    break;
                }
            }
            item->velocityX = 2;
        }
        item->width = MenuStringWidth(*(s32 *)(entry + 8));
        item->height = MenuFontLineHeight();
        item->targetX = 0x131 - (u16)item->width;
        item->x = x - (u16)item->width;
        if ((menuId == 4 && i == 1) || (menuId == 0xB && (u32)(i - 2) < 5)) {
            width = MenuStringWidth(gFormatLeadingSpacesZeroesPercentWildcard);
            item->targetX = (u16)item->targetX - width;
            slots[1][count] = y;
            slots[2][count] = x;
            count++;
            item->x = (u16)item->x - width;
        }
        y += item->height;
        if (i == 0) {
            y += 8;
            item->x = 0x140;
            item->targetX = (u16)item->targetX - 10;
        } else {
            if (menuId == 4 || menuId == 0xB) {
                if (D_800A38E8 < i) {
                    item->x = slots[2][i - D_800A38E8 - 1] - (u16)item->width;
                    item->targetY = slots[1][i - D_800A38E8 - 1];
                    item->y = slots[1][i - D_800A38E8 - 1];
                    if (selRow == 0) {
                        entry[0] = 1;
                    }
                }
            }
            x -= 0x80;
        }
    }
}

void func_8005C8D8(u8 index) {
    MenuObj *window;
    MenuText *prim;
    s32 i;
    s16 result;
    s16 height;

    window = D_800A36F0;
    for (i = 0; i < index; i++) {
        window++;
    }
    prim = window->primitive;
    switch (D_800A3988[index]) {
    case 0:
    case 0x80:
        prim->text = *(s32 *)(D_800A3690 + index * 4 + 4);
        if (D_800A3988[index] == 0x80) {
            prim->shade |= 2;
        } else {
            prim->shade = 0;
        }
        break;
    case 1:
    case 0x81:
        prim->text = *(s32 *)(D_800A39C0 + index * 4 + 4);
        if (D_800A3988[index] == 0x81) {
            prim->shade |= 2;
        } else {
            prim->shade = 0;
        }
        break;
    case 2:
        prim->text = *(s32 *)(D_800A3A28 + index * 4 + 4);
        break;
    }
    MenuFontSet(0, 0);
    result = MenuStringWidth(prim->text);
    height = 0x131 - result;
    window->width = result;
    window->x = height;
    window->targetX = height;
}

extern u8 *D_800AE294[];
extern u8 *D_800AE298[];
extern u8 gPlayerDriver[];
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
        if (gPlayerDriver[0] == gPlayerDriver[1]) {
            D_800A36E1[0] = (gPlayerDriver[0] + 1) % 24;
            MenuSetDriverNameLabel(1, D_800A36E1[0]);
            func_80063AE0(1, gPlayerDriver[1]);
        }
        MenuSetLinkedObjectLayoutByIndex(1, -0x3C, D_800A35E8[0]->targetX, 2);
    }
    D_800A3989[0] = D_800A3988[1] ^ 1;
    D_800A3988[0] = D_800A3989[-1] ^ 1;
    func_8005C8D8(1);
    func_8005C8D8(0);
    return 1;
}

extern u8 D_800A35C8;
extern u8 D_800A35C9[];
extern u8 gFormatPercentWildcard[];
extern char *strcat(char *, char *);
void TextFormatPercentage(s32 number) {
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
    TextFormatInt(number, buffer + length);
    strcat(buffer, gFormatPercentWildcard);
}

void func_8005CC34(void) {
    MenuText *prim;
    u8 *buffer;
    s32 number;
    s32 length;
    s16 result;
    s16 height;

    prim = *(u8 **)&D_800A38F8->primitive;
    number = D_800A37D0[0];
    buffer = D_800A35C9 - 1;
    D_800A35C8 = 0x20;
    length = 1;
    if (number < 0x64) {
        D_800A35C9[0] = 0x20;
        length = 2;
    }
    D_800A35C9[length - 1] = 0;
    TextFormatInt(number, buffer + length);
    strcat(buffer, gFormatPercentWildcard);
    MenuFontSet(prim->font, prim->scale);
    result = MenuStringWidth(prim->text);
    height = 0x131 - result;
    D_800A38F8->width = result;
    D_800A38F8->x = height;
    D_800A38F8->targetX = height;
}

/* buffer is pinned to s1 with an explicit-register local: gcc 2.7.2 hands
 * such variables their hard register directly (make_decl_rtl), so
 * global-alloc never ranks it against the D_800BB9E4[id] slot address
 * temp, which takes s2 as in retail. */
s32 func_8005CCEC(s32 id, s32 delta, s32 max, s32 min) {
    u8 *prim;
    u8 *buffer;
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
    prim = *((u8 **)&D_800BB9E4[id & 0xFF]->primitive);
    value = D_800A331CAbsolute[id & 0xFF];
    buffer = D_800A35C9 - 1;
    D_800A35C8 = 0x20;
    do {
        length = 1;
        if (value < 0x64) {
            D_800A35C9[0] = 0x20;
            length = 2;
        }
        D_800A35C9[length - 1] = 0;
        TextFormatInt(value, buffer + length);
        strcat(buffer, gFormatPercentWildcard);
        strcpy(*((char **)(prim + 8)), (char *)buffer);
    } while (0);
    MenuFontSet(prim[1], prim[2]);
    *(&D_800BB9E4[id & 0xFF]->width) = MenuStringWidth(*((s32 *)(prim + 8)));
    *(&D_800BB9E4[id & 0xFF]->x) = 0x131 - (*(&D_800BB9E4[id & 0xFF]->width));
    *(&D_800BB9E4[id & 0xFF]->targetX) = *(&D_800BB9E4[id & 0xFF]->x);
    return inRange;
}

/* The original toolchain padded this odd-length jump table with one zero
 * word; the C switch regenerates the table, this restores the pad. */
void __maspsx_include_asm_hack_jtblpad_8005CCEC() {
    __asm__(".section .rodata # maspsx-keep \n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern u8 D_800A3078[];
extern void func_8005C8D8(u8);
extern s32 func_8005CCECArgs(u8, s32);
asm(".globl func_8005CCECArgs\nfunc_8005CCECArgs = func_8005CCEC");
void MenuRefreshSixEntryValues(void) {
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
extern void MenuDrawString(u8 *, s16, s16, u8, u8, s32, u8, u8);
void func_8005CF34(MenuObj *window, u8 code, u8 first, u8 second, s32 textId) {
    register MenuText *prim asm("s3");

    prim = window->primitive;
    MenuFontSet(prim->font, prim->scale);
    prim->shade = code;
    if (textId == 0) {
        textId = prim->text;
    }
    if ((*(s32 *)&window->kind & 0xFFFF0000) != 0 || window->blue != 0) {
        MenuSetTextColor(window->red, window->green, window->blue);
    } else if (prim->font == 2) {
        MenuSetTextColor(0xFF, 0x80, 0x40);
    } else {
        MenuSetTextColor(0, 0, 0);
    }
    if (gScreenState[0] == 0xD) {
        MenuDrawString(textId, (s16)((u16)window->x + (u16)window->drawOffsetX),
                       (s16)((u16)window->y + (u16)window->drawOffsetY),
                       prim->center, prim->shade, prim->otz, first, second);
    } else {
        MenuDrawString(textId, window->x, window->y, prim->center, prim->shade,
                       prim->otz, first, second);
    }
}
#else
extern void MenuDrawString(u8 *, s16, s16, u8, u8, s32, u8, u8);
void func_8005CF34(MenuObj *window, u8 code, u8 first, u8 second, s32 textId) {
    MenuText *prim;
    s32 id;

    prim = window->primitive;
    MenuFontSet(prim->font, prim->scale);
    prim->shade = code;
    id = textId;
    if (id == 0) {
        id = prim->text;
    }
    if ((*(s32 *)&window->kind & 0xFFFF0000) != 0 || window->blue != 0) {
        MenuSetTextColor(window->red, window->green, window->blue);
    } else if (prim->font == 2) {
        MenuSetTextColor(0xFF, 0x80, 0x40);
    } else {
        MenuSetTextColor(0, 0, 0);
    }
    if (gScreenState[0] == 0xD) {
        MenuDrawString(id, (s16)((u16)window->x + (u16)window->drawOffsetX),
                       (s16)((u16)window->y + (u16)window->drawOffsetY),
                       prim->center, prim->shade, prim->otz, first & 0xFF,
                       second & 0xFF);
    } else {
        MenuDrawString(id, window->x, window->y, prim->center, prim->shade,
                       prim->otz, first & 0xFF, second & 0xFF);
    }
}

#endif

extern MenuObj *D_800A35E4;
extern MenuObj *D_800A3628;
extern MenuObj *D_800A362C[];
extern MenuObj *D_800A3634;
extern MenuObj *D_800A3740;
extern MenuObj *D_800A3788;
extern MenuObj *gPadPictureMenuLists[];
extern MenuObj *D_800A37F8;
extern MenuObj *D_800A3888[];
extern MenuObj *D_800A3A10;
extern u8 D_800A3684[];
extern u8 D_800A3685[];
extern u8 D_800A361CStore[] asm("D_800A361C.NON_MATCHING");
extern MenuObj *D_800A35E8Read[] asm("D_800A35E8.NON_MATCHING");
extern MenuObj *D_800A362CRead[] asm("D_800A362C.NON_MATCHING");
extern void MenuUpdateObjectGroups(void);
extern void MenuDrawLevelBars(s8, u8);
extern void func_80063638(u8);
extern void MenuRestoreLinkedObjectValues(u8);
void func_8005D094(s32 mode, u8 selection, u8 second) {
    MenuObj *window;
    s32 count;
    s32 i;
    u8 code;
    u8 active;
    s32 selected;
    MenuObj **entry;
    MenuObj **other;
    s32 offset;

    window = D_800A39B8;
    count = D_800A38E8 + 1;
    if ((mode & 0xFF) == 4) {
        count = D_800A38E8 + 2;
    }
    if ((mode & 0xFF) == 11) {
        count += 5;
    }
    for (i = 0; i < count; i++) {
        code = i == selection + 1;
        if ((((mode & 0xFF) == 1 || (mode & 0xFF) == 36 ||
              (mode & 0xFF) == 40 || (mode & 0xFF) == 37 ||
              (mode & 0xFF) == 39) &&
             D_800A3950[0] == 0 && (u32)(i - 3) < 4) ||
            ((mode & 0xFF) == 3 && D_800A3644[0] != 0 && (u32)(i - 3) < 2) ||
            ((mode & 0xFF) == 4 && D_800A3644[0] != 0 && i == 6)) {
            code |= 2;
        }
        if (window->velocityX != 0) {
            MenuUpdateObjectPosition(window, 1);
        } else if (i == count - 1 && D_800A361C[0] == 0) {
            D_800A361CStore[0] = 1;
        }
        if ((mode & 0xFF) == 4) {
            if (i == count - 1) {
                code = 1;
                if (selection != 0)
                    code = 0;
            } else if ((*(u8 *)window->primitive) & 2) {
                code |= 2;
            }
        } else if ((mode & 0xFF) == 11 && D_800A38E8 < i) {
            code = 0;
            switch (selection) {
            case 1:
                if (i == D_800A38E8 + 1)
                    code = 1;
                break;
            case 2:
                if (i == D_800A38E8 + 2)
                    code = 1;
                break;
            case 3:
                if (i == D_800A38E8 + 3)
                    code = 1;
                break;
            case 4:
                if (i == D_800A38E8 + 4)
                    code = 1;
                break;
            case 5:
                if (i == D_800A38E8 + 5)
                    code = 1;
                break;
            }
        }
        if (window->orderingDepth >= 0) {
            {
                MenuText *drawPrim;
                s32 drawId;
                u8 drawFirst;
                drawFirst = i != 0;
                drawPrim = window->primitive;
                MenuFontSet(drawPrim->font, drawPrim->scale);
                drawPrim->shade = code;
                drawId = drawPrim->text;
                if ((*(s32 *)&window->kind & 0xFFFF0000) != 0 ||
                    window->blue != 0) {
                    MenuSetTextColor(window->red, window->green, window->blue);
                } else if (drawPrim->font == 2) {
                    MenuSetTextColor(0xFF, 0x80, 0x40);
                } else {
                    MenuSetTextColor(0, 0, 0);
                }
                if (gScreenState[0] == 0xD) {
                    MenuDrawString(
                        drawId,
                        (s16)((u16)window->x + (u16)window->drawOffsetX),
                        (s16)((u16)window->y + (u16)window->drawOffsetY),
                        drawPrim->center, drawPrim->shade, drawPrim->otz,
                        drawFirst & 0xFF, 0);
                } else {
                    MenuDrawString(drawId, window->x, window->y,
                                   drawPrim->center, drawPrim->shade,
                                   drawPrim->otz, drawFirst & 0xFF, 0);
                }
            }
        }
        window++;
    }
    if (D_800A361C[0] == 1) {
        MenuUpdateObjectPosition(D_800A392C, 1);
        MenuDrawObjectList(D_800A392C, 0xFF);
        MenuUpdateObjectPosition(D_800A3634, 1);
        active = 1;
        if ((mode & 0xFF) == 2)
            active = selection != 2;
        MenuDrawModel(1, active, 0);
        MenuUpdateObjectPosition(D_800A3740, 1);
        {
            MenuObj *drawWindow;
            MenuText *drawPrim;
            s32 drawId;
            drawWindow = D_800A3740;
            drawPrim = drawWindow->primitive;
            MenuFontSet(drawPrim->font, drawPrim->scale);
            drawPrim->shade = 0;
            drawId = drawPrim->text;
            if ((*(s32 *)&drawWindow->kind & 0xFFFF0000) != 0 ||
                drawWindow->blue != 0) {
                MenuSetTextColor(drawWindow->red, drawWindow->green,
                                 drawWindow->blue);
            } else if (drawPrim->font == 2) {
                MenuSetTextColor(0xFF, 0x80, 0x40);
            } else {
                MenuSetTextColor(0, 0, 0);
            }
            if (gScreenState[0] == 0xD) {
                MenuDrawString(
                    drawId,
                    (s16)((u16)drawWindow->x + (u16)drawWindow->drawOffsetX),
                    (s16)((u16)drawWindow->y + (u16)drawWindow->drawOffsetY),
                    drawPrim->center, drawPrim->shade, drawPrim->otz, 1, 0);
            } else {
                MenuDrawString(drawId, drawWindow->x, drawWindow->y,
                               drawPrim->center, drawPrim->shade, drawPrim->otz,
                               1, 0);
            }
        }
        MenuUpdateObjectPosition(D_800A3788, 1);
        {
            MenuObj *drawWindow;
            MenuText *drawPrim;
            s32 drawId;
            drawWindow = D_800A3788;
            drawPrim = drawWindow->primitive;
            MenuFontSet(drawPrim->font, drawPrim->scale);
            drawPrim->shade = 0;
            drawId = drawPrim->text;
            if ((*(s32 *)&drawWindow->kind & 0xFFFF0000) != 0 ||
                drawWindow->blue != 0) {
                MenuSetTextColor(drawWindow->red, drawWindow->green,
                                 drawWindow->blue);
            } else if (drawPrim->font == 2) {
                MenuSetTextColor(0xFF, 0x80, 0x40);
            } else {
                MenuSetTextColor(0, 0, 0);
            }
            if (gScreenState[0] == 0xD) {
                MenuDrawString(
                    drawId,
                    (s16)((u16)drawWindow->x + (u16)drawWindow->drawOffsetX),
                    (s16)((u16)drawWindow->y + (u16)drawWindow->drawOffsetY),
                    drawPrim->center, drawPrim->shade, drawPrim->otz, 1, 0);
            } else {
                MenuDrawString(drawId, drawWindow->x, drawWindow->y,
                               drawPrim->center, drawPrim->shade, drawPrim->otz,
                               1, 0);
            }
        }
        if ((mode & 0xFF) != 7 || second == 0) {
            MenuUpdateObjectPosition(D_800A35E4, 1);
            MenuDrawObjectList(D_800A35E4, 0xFF);
            func_80064000(0, 0, (mode & 0xFF) == 7);
            if (((mode & 0xFF) == 2 && (u8)(selection - 1) < 2) ||
                ((mode & 0xFF) == 8 && selection == 0)) {
                if ((mode & 0xFF) == 2)
                    func_80063638(selection == 1);
                MenuUpdateObjectPosition(D_800A3628, 1);
                MenuDrawObjectList(D_800A3628, 0xFF);
            }
        }
        if (D_800A3644[0] != 0) {
            if ((mode & 0xFF) != 7 || second == 1) {
                MenuUpdateObjectPosition(D_800A35E8[0], 1);
                MenuDrawObjectList(D_800A35E8Read[0], 0xFF);
                selected = D_800A3A25[0] == 0;
                func_80064000(1, selected, (mode & 0xFF) == 7);
                if ((mode & 0xFF) == 2 && selection == 1) {
                    MenuUpdateObjectPosition(D_800A362C[0], 1);
                    if (selected == 0)
                        MenuDrawObjectList(D_800A362CRead[0], 0xFF);
                }
            }
        }
        if ((mode & 0xFF) == 7) {
            MenuUpdateObjectGroups();
            MenuDrawLevelBars((s8)selection, second);
        }
        if ((u8)(mode - 34) < 2 || (mode & 0xFF) == 36 || (mode & 0xFF) == 40 ||
            (mode & 0xFF) == 37 || (u8)(mode - 38) < 2 ||
            ((mode & 0xFF) == 1 && D_800A3A10->velocityX < 0)) {
            MenuUpdateObjectPosition(D_800A3A10, 1);
            MenuDrawObjectList(D_800A3A10, 0xFF);
        }
        if ((mode & 0xFF) == 1 && D_800A3A10->velocityX == 0) {
            MenuRestoreLinkedObjectValues(0);
        }
    }
    if ((mode & 0xFF) != 33) {
        if ((mode & 0xFF) != 5 || D_800A38A8->velocityX >= 0) {
            goto afterPanel;
        }
    } else {
        if (D_800A3059[0] == 3 && !(VSync(-1) & 3)) {
            SoundRunSlotEnvelope(1, 1);
        }
    }
    MenuUpdateObjectPosition(D_800A38A8, 1);
    MenuDrawObjectList(D_800A38A8, 0xFF);
afterPanel:
    if ((mode & 0xFF) == 13) {
        i = 0;
        if (i < D_800A3644[0] + 1) {
            entry = gPadPictureMenuLists;
            do {
                offset = i * 4;
                MenuUpdatePadPicture(i & 0xFF);
                MenuUpdateObjectPosition(*entry, 1);
                MenuDrawObjectList(*entry, 0xFF);
                if (D_800A3684[i] == 1) {
                    other = D_800A3888;
                    other = (MenuObj **)((u8 *)other + offset);
                    MenuUpdateObjectPosition(*other, 1);
                    MenuDrawObjectList(*other, 0xFF);
                }
                i++;
                entry++;
            } while (i < D_800A3644[0] + 1);
        }
        if (D_800A3644[0] != 0) {
            if (D_800A3684[0] == 0 || D_800A3685[0] == 0) {
                MenuUpdateObjectPosition(D_800A37F8, 1);
                MenuDrawObjectList(D_800A37F8, 0xFF);
            }
        } else if (D_800A3684[0] == 0) {
            MenuUpdateObjectPosition(D_800A37F8, 1);
            MenuDrawObjectList(D_800A37F8, 0xFF);
        }
    }
}

void __maspsx_include_asm_hack_jtblpad_8005D094(void) {
    __asm__(".section .rodata # maspsx-keep\n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

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
extern u8 D_8009AEB2[];
void func_8005DAD4(void) {
    s32 i;
    s32 primOffset;
    s16 x;
    u8 index;
    MenuObj *object;
    POLY_FT4 *prim;
    u16 value;
    u16 w;
    u16 h;

    x = -0x32;
    i = 0;
    primOffset = 0;
    do {
        index = gMenuObjectPoolCount;
        prim = (POLY_FT4 *)(D_800B9990 + primOffset);
        gMenuObjectPoolCount = index + 1;
        object = &gMenuObjectPool[index];
        object->kind = 1;
        object->drawOffsetX = 0;
        object->drawOffsetY = 0;
        object->next = 0;
        object->blue = 0;
        object->green = 0;
        object->red = 0;
        object->orderingDepth = 0;
        D_800B12FC[i] = (s16 *)object;
        object->x = x;
        x = x - 1;
        x = x - i;
        object->y = 0x10;
        object->targetY = 0x10;
        object->velocityX = 2;
        object->width = 0x40;
        object->velocityY = 0;
        object->height = 0x13;
        object->orderingDepth = 0;
        value = (u16)object->x;
        object->targetX = value;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        prim->r0 = 0x80;
        prim->g0 = 0x80;
        prim->b0 = 0x80;
        SetSemiTrans(prim, 1);
        w = (u16)object->width;
        h = (u16)object->height;
        prim->clut = GetClut(D_8009AEDC[0], D_8009AEDE[0]);
        primOffset += 0x28;
        prim->tpage = GetTPage(D_8009AEE4[0], 3, D_8009AED8[0], D_8009AEDA[0]);
        prim->u0 = D_8009AEE0[0];
        prim->v0 = D_8009AEE2[0];
        prim->u1 = D_8009AEA2[62] + w;
        prim->v1 = D_8009AEAE[52];
        prim->u2 = D_8009AEA6[58];
        prim->v2 = D_8009AEB2[48] + h;
        prim->u3 = D_8009AEAA[54] + w;
        prim->v3 = D_8009AEB6[44] + h;
        i++;
        object->primitive = prim;
    } while (i < 10);
    D_800A39C4 = gMenuObjectPoolCount;
}

s32 func_8005DCF0(void) {
    u8 done;
    s32 i;
    MenuObj *object;
    POLY_FT4 *poly;
    s16 sum;

    done = 0;
    i = 9;
    do {
        object = (u8 *)D_800B12FC[i];
        if (object->velocityX != 0) {
            sum = (u16)object->x + object->velocityX;
            object->x = sum;
            if (sum >= 0x141) {
                object->y = 0xF0;
                if (i == 9) {
                    done = 1;
                }
                if (done != 0) {
                    object->velocityX = 2;
                    object->x = (u16)object->targetX;
                    object->y = (u16)object->targetY;
                }
            }
            if ((s16)(u16)object->velocityX < 6) {
                object->velocityX =
                    (u16)object->velocityX + (s16)(u16)object->velocityX / 2;
            }
        }
        if (done == 0) {
            poly = (POLY_FT4 *)(GraphicsAllocPolyFT4(0));
            *poly = *(POLY_FT4 *)(u8 *)object->primitive;
            poly->x0 = (u16)object->x;
            poly->y0 = (u16)object->y;
            poly->x1 = (u16)object->x + (u16)object->width;
            poly->y1 = (u16)object->y;
            poly->x2 = (u16)object->x;
            poly->y2 = (u16)object->y + (u16)object->height;
            poly->x3 = (u16)object->x + (u16)object->width;
            poly->y3 = (u16)object->y + (u16)object->height;
            AddPrim(gOrderingTable[0] + object->orderingDepth * 4, poly);
        }
        i--;
    } while (i != 0);
    return done;
}

void MenuSetAllObjectOrderingDepths(s16 value) {
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

void MenuSetLinkedObjectMotion(s32 a, s32 b, s32 c, u8 flag) {
    MenuObj *object;
    object = D_800A392C;
    while (object) {
        object->x = a;
        object->velocityX = c;
        object->targetX = b;
        object->unk5 = c;
        if (flag)
            object->targetX = 125;
        object = object->next;
    }
}
