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
#include "list.h"
#include "menu.h"
#include "objects.h"
#include "util.h"
#include "graphics.h"
#include "sound.h"

void func_80065838(s32 arg0);
extern s32 D_800A3930Plain asm("D_800A3930");

extern s32 strlen(char *);

extern s32 gOrderingTable[];
extern Car *gPlayerCar[];
extern void HeapFree(void *ptr);
extern s32 D_800A38AC[];
extern s32 D_800A37C4Absolute[];
extern void SetPolyF4(u8 *prim);
void PadResetAndInitializeBuffers(void);
extern s32 D_800A37D0[];
void SetPolyFT4(POLY_FT4 *);
extern u8 gCardMenuMessageb[] asm("D_800A3814.NON_MATCHING");
extern DRAWENV D_800BDD4C[];
extern DISPENV D_800BDE04[];
extern void SetPolyF3(POLY_F3 *);
extern u8 *GraphicsAllocPolyFT4(s32);
extern u8 *GraphicsAllocPolyF4(s32);
extern u8 D_800A3988[];
extern u8 D_800A3644[];
extern char *strcat(char *, char *);
extern void MenuDrawString(u8 *, s16, s16, u8, u8, s32, u8, u8);
void GraphicsDrawRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5,
                      u8 arg6, s32 arg7);
void func_8001E230(s32 arg0, s32 arg1);
void func_8002EEFC(Car *arg0);
void ModelLoadGeometryFromAddress(s32 first, s32 second);
void PadResetAndInitializeBuffers(void);
void SystemSetGlobalPointer(s32 gp);
void MenuFontCopyGlyphPrimitives(u8 id, s32 arg1, void *dest);
s32 MenuTextCenterOffset(s16 arg0, s32 arg1);
s32 TextCountLines(u8 *text);
MenuObj *MenuObjAlloc(void);
void MenuUpdateObjectPosition(MenuObj *first, u8 friction);
void MenuDrawObjectList(MenuObj *object, s32 arg1);

/* Menu entries and panels. */

extern MenuObj *D_800A3634;
extern s32 **D_800A3740;
extern MenuObj *D_800A3788;
extern s32 D_800A3A2CAbsolute[];
void func_8005DF50(s32 arg0, s32 arg1, s32 arg2) {
    MenuObj *p0;
    MenuObj *p1;
    MenuObj *p2;
    MenuObj *p3;
    MenuObj *p4;
    MenuObj *p5;
    p0 = D_800A3634;
    p0->unk5 = arg2;
    p0->velocityX = arg2;
    p1 = D_800A3634;
    p1->targetX = arg1 + 0x3C;
    p2 = (MenuObj *)D_800A3740;
    p2->unk5 = arg2;
    p2->velocityX = arg2;
    p3 = (MenuObj *)D_800A3740;
    p3->targetX = arg1 + 5;
    p4 = D_800A3788;
    p4->unk5 = arg2;
    p4->velocityX = arg2;
    p5 = D_800A3788;
    p5->targetX = arg1 + 0x71;
}

extern u16 D_8009AF1E[];
extern u16 D_8009AF20[];
extern u16 D_8009AF22[];
extern u16 D_8009AF24[];
extern u16 D_8009AF2A[];
extern u8 D_8009AF26[];
extern u8 D_8009AF28[];
extern u8 D_800AFDDC[];
extern u8 D_800AE1BC[];
void func_8005DFA0(void) {
    s32 i;
    s32 y;
    s32 primOffset;
    u8 index;
    MenuObj *object;
    MenuObj *slot;
    s32 panelH;
    s32 panelB;
    POLY_FT4 *prim;
    MenuObj *panel;
    POLY_F4 *panelPrim;
    s32 panelY;
    s32 panelW;
    u8 color;
    s32 code;
    s32 panelOffset;

    y = 0xA7;
    panelH = 0x2D;
    panelB = 0x40;
    i = 0;
    primOffset = 0;
again:
    index = gMenuObjectPoolCount++;
    slot = &gMenuObjectPool[index];
    slot->drawOffsetX = 0;
    object = slot;
    object->drawOffsetY = 0;
    object->next = 0;
    object->blue = 0;
    object->green = 0;
    object->red = 0;
    object->orderingDepth = 0;
    object->kind = 1;
    if (i == 0) {
        D_800A392C = object;
    } else {
        D_800A392C->next = object;
    }
    object->targetX = 0;
    object->targetY = y;
    object->y = y;
    object->width = 0x78;
    object->height = (i == 0) ? 0x18 : 0x15;
    prim = (POLY_FT4 *)(D_800AFDDC + primOffset);
    object->velocityX = 2;
    object->velocityY = 0;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    prim->r0 = 0x80;
    prim->g0 = 0x80;
    prim->b0 = 0x80;
    SetSemiTrans(prim, 1);
    if (i == 0) {
        u16 w;
        u16 h;
        w = (u16)object->width;
        h = (u16)object->height;
        prim->clut = GetClut(D_8009AF22[0], D_8009AF24[0]);
        prim->tpage = GetTPage(D_8009AF2A[0], 3, D_8009AF1E[0], D_8009AF20[0]);
        prim->u0 = D_8009AF26[0];
        prim->v0 = D_8009AF28[0];
        prim->u1 = *(u8 *)((u8 *)D_8009AF1E + 8) + w;
        prim->v1 = *(u8 *)((u8 *)D_8009AF1E + 10);
        prim->u2 = *(u8 *)((u8 *)D_8009AF22 + 4);
        prim->v2 = *(u8 *)((u8 *)D_8009AF22 + 6) + h;
        prim->u3 = *(u8 *)((u8 *)D_8009AF2A - 4) + w;
        prim->v3 = *(u8 *)((u8 *)D_8009AF2A - 2) + h;
    } else {
        u16 w;
        w = (u16)object->width;
        prim->clut = GetClut(D_8009AF22[0], D_8009AF24[0]);
        prim->tpage = GetTPage(D_8009AF2A[0], 3, D_8009AF1E[0], D_8009AF20[0]);
        prim->u0 = D_8009AF26[0];
        prim->v0 = D_8009AF28[0] + 0x1B;
        prim->u1 = *(u8 *)((u8 *)D_8009AF1E + 8) + w;
        prim->v1 = *(u8 *)((u8 *)D_8009AF1E + 10) + 0x1B;
        prim->u2 = *(u8 *)((u8 *)D_8009AF22 + 4);
        prim->v2 = *(u8 *)((u8 *)D_8009AF22 + 6) + 0x30;
        prim->u3 = *(u8 *)((u8 *)D_8009AF2A - 4) + w;
        prim->v3 = *(u8 *)((u8 *)D_8009AF2A - 2) + 0x30;
    }
    y += 0x18;
    primOffset += 0x28;
    i++;
    object->orderingDepth = 0x3FC;
    object->primitive = prim;
    if (i < 2) {
        goto again;
    }
    i = 0;
    panelY = 0xA7;
    panelW = 0x78;
    color = 0x20;
    code = 2;
    panelOffset = 0;
again2:
    index = gMenuObjectPoolCount;
    panelPrim = (POLY_F4 *)(D_800AE1BC + panelOffset);
    gMenuObjectPoolCount = index + 1;
    panel = &gMenuObjectPool[index];
    panel->blue = 0;
    panel->height = panelH;
    panel->drawOffsetX = 0;
    panel->drawOffsetY = 0;
    panel->next = 0;
    panel->green = 0;
    panel->red = 0;
    panel->orderingDepth = 0;
    panel->kind = code;
    panel->x = 0;
    panel->targetX = 0;
    panel->y = panelY;
    panel->targetY = panelY;
    panel->velocityX = 0;
    panel->velocityY = 0;
    panel->width = panelW;
    panel->red = color;
    panel->green = color;
    panel->blue = panelB;
    if (panelPrim == 0) {
        panelPrim = (POLY_F4 *)(GraphicsAllocPolyF4(1));
    }
    panel->primitive = panelPrim;
    SetPolyF4(panelPrim);
    SetSemiTrans(panelPrim, 1);
    panelPrim->r0 = color;
    panelPrim->g0 = color;
    panelPrim->b0 = panelB;
    panelPrim->y2 = 0xD4;
    panelPrim->y3 = 0xD4;
    panelPrim->x0 = 0;
    panelPrim->y0 = panelY;
    panelPrim->x1 = panelW;
    panelPrim->y1 = panelY;
    panelPrim->x2 = 0;
    panelPrim->x3 = panelW;
    panel->velocityX = code;
    panel->orderingDepth = 0x3FD;
    object->next = panel;
    object = panel;
    i++;
    panelOffset += 0x18;
    if (i < 2) {
        goto again2;
    }
    D_800A39C4 = gMenuObjectPoolCount;
}

extern void *D_800A3954;
void MenuFreeResourceBlock(void) {
    if (D_800A3954 != NULL) {
        HeapFree(D_800A3954);
    }
    D_800A3954 = NULL;
}

extern void *D_800A399C[];
void MenuFreeObjectBuffer(void) {
    if (D_800A399C[0] != 0) {
        HeapFree(D_800A399C[0]);
    }
    *(void **)&D_800A3988[0x14] = 0;
}

extern char D_800BA058[], gTextLeadingSpaceLaps[];
void MenuFormatLapText(s32 value) {
    TextFormatInt(value, D_800BA058);
    strcat(D_800BA058, gTextLeadingSpaceLaps);
}

void MenuAllocateObjectBuffer(void) {
    D_800A399C[0] = HeapAlloc(0x2580);
}

/* One model face: three corner vertices plus a fourth, 32 bytes. The pad
 * halfword of each vertex holds the face colour (v[0..2]) or the
 * semi-transparency flag (v[3]). */
typedef struct {
    SVECTOR v[4];
} ModelQuad;

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
    POLY_F4 *prim;
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
            color = ((ModelQuad *)entry)->v[0].pad;
            prim->r0 = color;
            color = ((ModelQuad *)entry)->v[1].pad;
            prim->g0 = color;
            color = ((ModelQuad *)entry)->v[2].pad;
            prim->b0 = color;
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
    POLY_F4 *prim;
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
            color = ((ModelQuad *)entry)->v[0].pad;
            prim->r0 = color;
            color = ((ModelQuad *)entry)->v[1].pad;
            prim->g0 = color;
            color = ((ModelQuad *)entry)->v[2].pad;
            prim->b0 = color;
            i++;
            primOffset += 0x18;
        } while (i < D_800A38DC);
    }
}

extern u8 *D_800AE178[];
void MenuLoadOffsetResources(s32 fileId) {
    void *table;
    void *result;
    u8 i;

    result = FileLoadOffsetTable(fileId, &table, 0);
    D_800A3954 = result;
    for (i = 0; i < 0x11; i++) {
        D_800AE178[i] = result + ((s32 *)table)[i];
    }
}

void func_8005E5BC(s32 unused, s32 x, s16 y, s32 flag) {
    MenuObj *entry;
    u8 count;
    s32 height;
    s32 fieldValue;
    count = gMenuObjectPoolCount;
    gMenuObjectPoolCount = count + 1;
    entry = &gMenuObjectPool[count];
    entry->kind = 3;
    height = 0x3C;
    entry->drawOffsetX = 0;
    entry->drawOffsetY = 0;
    entry->next = 0;
    entry->blue = 0;
    entry->green = 0;
    entry->red = 0;
    entry->orderingDepth = 0;
    D_800A3634 = (MenuObj *)entry;
    entry->x = x + 0x3C;
    entry->targetX = height;
    if (flag & 0xFF) {
        entry->targetX = 0xB9;
    }
    fieldValue = D_800A393C;
    entry->y = 0xB9;
    entry->targetY = 0xB9;
    entry->velocityX = y;
    entry->velocityY = 0;
    entry->primitive = (void *)fieldValue;
}

extern u8 D_8009AF84[];
extern s32 D_800A3814[];
extern s32 D_800A3814B[] asm("D_800A3814");
extern s32 D_800A3814C[] asm("D_800A3814");
extern char D_800BA058B[] asm("D_800BA058");
extern char D_800BA058C[] asm("D_800BA058");
void func_8005E644(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 count;
    MenuObj *entry;
    u8 count2;
    u8 *subBase;
    MenuText *sub;
    u8 *local;
    s32 value;
    MenuObj *entry2;

    count = gMenuObjectPoolCount;
    gMenuObjectPoolCount = count + 1;
    entry = &gMenuObjectPool[count];
    entry->blue = 0;
    entry->green = 0;
    entry->red = 0;
    count2 = D_800A37BC;
    entry->targetX = arg1;
    entry->x = arg1;
    subBase = (u8 *)D_800A3654;
    entry->drawOffsetX = 0;
    entry->drawOffsetY = 0;
    entry->next = 0;
    entry->orderingDepth = 0;
    entry->kind = 0;
    entry->targetY = 0xC8;
    entry->y = 0xC8;
    entry->velocityX = 0;
    entry->velocityY = 0;
    entry->orderingDepth = 0;
    D_800A37BC = count2 + 1;
    sub = subBase + count2 * 12;
    entry->primitive = sub;
    sub->shade = 0;
    sub->center = 0;
    sub->otz = 0;
    local = entry->primitive;
    D_800A3788 = (MenuObj *)entry;
    local[1] = 2;
    local[2] = 2;
    local[3] = 1;
    value = *(s16 *)&D_8009AF84[(arg0 & 0xFF) * 2] * D_800A37D0[0] / 100;
    D_800A3814[0] = value;
    if (value < 3) {
        D_800A3814B[0] = 3;
    }
    TextFormatInt(D_800A3814C[0], D_800BA058);
    strcat(D_800BA058B, gTextLeadingSpaceLaps);
    entry2 = (u8 *)D_800A3788;
    ((MenuText *)local)->text = (s32)D_800BA058C;
    entry2->x = (u16)entry2->x + 0x71;
    entry2->targetX = 0x71;
    if ((arg3 & 0xFF) != 0) {
        entry2->targetX = 0xEE;
    }
    D_800A3788->velocityX = arg2;
}

void func_8005E7F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 D_8009A31C[];
    u8 index;
    u8 primIndex;
    MenuObj *object;
    s32 panelH;
    s32 panelB;
    u8 *prim;
    MenuText *prim2;
    MenuObj *cur;
    s32 value;
    s32 word;
    s32 offset;
    s32 stride;

    index = gMenuObjectPoolCount++;
    object = &gMenuObjectPool[index];
    object->blue = 0;
    object->green = 0;
    object->red = 0;
    primIndex = D_800A37BC;
    *(u16 *)&object->targetX = arg1;
    *(u16 *)&object->x = arg1;
    prim = (u8 *)D_800A3654;
    *(u16 *)&object->drawOffsetX = 0;
    *(u16 *)&object->drawOffsetY = 0;
    *(u32 *)&object->next = 0;
    *(u16 *)&object->orderingDepth = 0;
    *(u16 *)&object->kind = 0;
    *(u16 *)&object->targetY = 0xAB;
    *(u16 *)&object->y = 0xAB;
    *(u16 *)&object->velocityX = 0;
    *(u16 *)&object->velocityY = 0;
    *(u16 *)&object->orderingDepth = 0;
    D_800A37BC = primIndex + 1;
    do {
    } while (0);
    prim += primIndex * 12;
    *(u8 **)&object->primitive = prim;
    ((MenuText *)prim)->shade = 0;
    ((MenuText *)prim)->center = 0;
    ((MenuText *)prim)->otz = 0;
    prim2 = object->primitive;
    offset = arg0 & 0xFF;
    stride = 4;
    offset = offset * stride;
    D_800A3740 = (s32 **)object;
    prim2->font = 2;
    prim2->scale = 2;
    value = *(s32 *)((u8 *)D_8009A31C + offset);
    cur = (u8 *)D_800A3740;
    prim2->text = value;
    word = (u16)cur->x;
    word = word + 5;
    cur->x = word;
    word = 5;
    cur->targetX = word;
    if (arg3 & 0xFF) {
        word = 0x82;
        cur->targetX = word;
    }
    *(u16 *)&((MenuObj *)D_800A3740)->velocityX = arg2;
}

extern s32 D_800A3344;
extern u16 D_8009AFA8[];
extern MATRIX D_800A8C70;
extern u8 gSelectedTrack[];

/* Draws the spinning model that sits in a menu window as one POLY_F4 per
 * face. advanceSpin changes the spin angle, semiTrans forces semi-transparency, and
 * mode picks the full-screen camera (non-zero) or the window at D_800A3634. */
void MenuDrawModel(s32 advanceSpin, s32 semiTrans, s32 fullScreenMode) {
    SVECTOR angles;
    VECTOR trans;
    s32 *ot;
    POLY_F4 *cursor;
    POLY_F4 *tmpl;
    ModelQuad *q;
    s32 i;
    s32 otz;
    s32 x;
    s32 y;
    s32 depth;

    cursor = (POLY_F4 *)((u8 *)gPrimitiveCursor[0]);
    ot = (s32 *)gOrderingTable[0];
    if (fullScreenMode & 0xFF) {
        x = 0xA0;
        y = 0x64;
        depth = 0xC8;
        switch (gSelectedTrack[0]) {
        case 1:
            x = 0x9B;
            depth = 0x12C;
            break;
        case 4:
            depth = 0x12C;
            y = 0x73;
            break;
        case 10:
            x = 0xA0;
            break;
        case 7:
        case 11:
            depth = 0x12C;
            y = 0x6E;
            if (gSelectedTrack[0] != 0xB) {
                break;
            }
        case 9:
        set69:
            y = 0x69;
            break;
        case 12:
            x = 0x96;
            goto set69;
        case 14:
            depth = 0xFA;
        case 2:
        case 3:
        case 5:
        case 13:
        case 15:
            y = 0x6E;
            break;
        case 16:
            x = 0x96;
            y = 0x64;
            break;
        }
        SetGeomOffset(x, y);
        angles.vy = D_8009AFA8[gSelectedTrack[0]];
        angles.vx = 0x4B0;
        angles.vz = 0;
    } else if (cursor) {
        /* The two arms are identical: cross-jumping merges them. The copy
         * lengthens otz's live range so the allocator ranks it below i and q,
         * as in the original. */
        SetGeomOffset(D_800A3634->x, D_800A3634->y);
        angles.vy = D_800A3344;
        angles.vx = 0xC8;
        angles.vz = 0;
    } else {
        SetGeomOffset(D_800A3634->x, D_800A3634->y);
        angles.vy = D_800A3344;
        angles.vx = 0xC8;
        angles.vz = 0;
    }
    RotMatrix(&angles, &D_800A8C70);
    SetRotMatrix(&D_800A8C70);
    if (advanceSpin & 0xFF) {
        if (depth) { /* identical arms, see above */
            D_800A3344 = (D_800A3344 + 0x10) % 0x1000;
        } else {
            D_800A3344 = (D_800A3344 + 0x10) % 0x1000;
        }
    }
    trans.vx = 0;
    trans.vy = 0;
    if (fullScreenMode & 0xFF) {
        trans.vz = depth;
    } else {
        trans.vz = 0x1C2;
    }
    TransMatrix(&D_800A8C70, &trans);
    SetTransMatrix(&D_800A8C70);
    q = (ModelQuad *)D_800A393C;
    tmpl = D_800A399C[0];
    for (i = 0; i < D_800A38DC; i++) {
        gte_ldv3c(&q->v[0]);
        gte_rtpt();
        if ((semiTrans & 0xFF) == 0) {
            SetSemiTrans(tmpl, q->v[3].pad);
        } else {
            SetSemiTrans(tmpl, 1);
        }
        gte_avsz3();
        asm volatile("mfc2 %0, $7" : "=r"(otz) : "0"(otz));
        if (q->v[3].pad != 0) {
            otz += 0x10;
        }
        if (q->v[0].pad == 0 && q->v[1].pad == 0x46 && q->v[2].pad == 0x9A) {
            if (fullScreenMode & 0xFF) {
                continue;
            }
            otz -= 0x20;
        }
        if (otz < 0) {
            otz = 0;
        }
        gte_stsxy3((u8 *)tmpl + 8, (u8 *)tmpl + 0xC, (u8 *)tmpl + 0x10);
        gte_ldv0(&q->v[3]);
        gte_rtps();
        gte_stsxy((u8 *)tmpl + 0x14);
        *cursor = *tmpl;
        AddPrim((u8 *)ot + ((otz >> 2) << 2), cursor);
        q++;
        tmpl++;
        cursor++;
    }
    gPrimitiveCursor[0] = (u32)cursor;
}

#ifdef NON_MATCHING
extern u16 D_8009AF84[];
extern s32 D_800A37D0;
extern s32 D_800A3814;
void MenuFormatLapCount(s32 trackIndex) {
    s32 value;
    s32 scaled;
    value = D_8009AF84[trackIndex & 0xFF];
    scaled = (value * D_800A37D0) / 100;
    D_800A3814 = scaled;
    if (scaled < 3)
        D_800A3814 = 3;
    TextFormatInt(D_800A3814, D_800BA058);
    strcat(D_800BA058, gTextLeadingSpaceLaps);
}
#else
extern s32 D_800A3814Abs[];
extern char D_800BA058NM[] asm("D_800BA058.NON_MATCHING");
asm(".globl D_800A3814Abs\nD_800A3814Abs = D_800A3814");
void MenuFormatLapCount(u8 arg0) {
    s32 value;

    value = *(s16 *)&D_8009AF84[(arg0 & 0xFF) * 2] * D_800A37D0[0] / 100;
    *(s32 *)&gCardMenuMessageb[0] = value;
    if (value < 3) {
        D_800A3814[0] = 3;
    }
    TextFormatInt(D_800A3814Abs[0], D_800BA058);
    strcat(D_800BA058NM, gTextLeadingSpaceLaps);
}

#if 0
/* w7g draft: everything matches except gcc CSEs the two D_800BA058
 * materializations across the TextFormatInt/strcat calls into
 * callee-saved s0 (function 8 bytes short; asm("") does not block
 * cross-call cse). D_800A3814 is reached as D_800A37E8[11] (bss
 * neighbor of an already-array symbol; declaring D_800A3814 drifts
 * labels), and D_8009AF84 needs u8[] + s16 cast (retail strides 2). */
void MenuFormatLapCount(u8 arg0) {
    s32 value;

    value = *(s16 *)&D_8009AF84[(arg0 & 0xFF) * 2] * D_800A37D0[0] / 100;
    D_800A37E8[11] = value;
    if (value < 3) {
        *(D_800A37E8 + 11) = 3;
    }
    TextFormatInt(D_800A37E8[11], D_800BA058);
    strcat(D_800BA058, gTextLeadingSpaceLaps);
}
#endif
#endif

extern s32 D_8009A31C[];
void MenuSetTrackLabel(s32 index) {
    D_800A3740[8][2] = D_8009A31C[index & 0xFF];
}

s32 MenuGetGridScale(u8 x, u8 y) {
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

extern u16 D_8009AEA2[];
extern u16 D_8009AEA6[];
extern u16 D_8009AEB2[];
extern u16 D_8009AEBA[];
extern MenuObj *D_800B996C[];
extern MenuObj *D_800B9980[];
extern MenuObj *D_800BB9F4[];
extern MenuObj *D_800AE168[];
extern MenuObj *D_800B60B8[];
extern MenuObj *D_800A39ACPtr asm("D_800A39AC");
extern s32 D_8009A268[];
extern s32 D_8009A298[];
extern void func_80060008(u8);
/* Menu screen builder. Each "object" is a 36-byte record taken from
 * gMenuObjectPool; the MenuObj struct matters for the match: member stores are
 * MEM_IN_STRUCT_P, so the scheduler may hoist the scalar D_800A3654 load
 * above them like retail. Retail's constants and register order depend on
 * the locals below (k2b is pinned to $19, the empty asm statements make the
 * primitive pointers function-wide). */
void func_8005ED74(u8 arg0, u8 arg1) {
    extern s32 func_8005A8EI(u8 *) asm("MenuStringWidth");
    register s32 k2b asm("$19");
    u8 ix1;
    u8 ix11;
    u8 ix2;
    u8 ix3;
    u8 ix4;
    u8 ix5;
    u8 ix6;
    u8 ix7;
    u8 ix8;
    u8 ix9;
    u8 ixB10;
    MenuObj *obj1;
    MenuObj *obj11;
    MenuObj *obj2;
    MenuObj *obj3;
    MenuObj *obj4;
    MenuObj *obj5;
    MenuObj *obj6;
    MenuObj *obj7;
    MenuObj *obj8;
    MenuObj *objB8;
    MenuObj *objB9;
    MenuObj *objC10;
    MenuObj *objC9;
    u8 *pq3;
    POLY_FT4 *pr1;
    POLY_F4 *pr2;
    u8 *pr3;
    POLY_FT4 *pr4;
    POLY_F4 *pr5;
    POLY_FT4 *pr6;
    POLY_F4 *pr7;
    POLY_FT4 *pr8;
    u8 *prC8;
    POLY_F4 *prC9;
    MenuText *prD10;
    u8 *prD7;
    s16 w2, c2, k2, g2, b2;
    s16 w4, g4, z4;
    s16 k41, k32, k7;
    s16 k3, k9, k30;
    s32 m;
    s16 w1, g1, z1;
    POLY_FT4 *prim2;
    s32 i;
    s32 j;
    s32 yBase;
    s32 h;
    s32 x1;
    s32 x4;
    s32 x6;
    s32 value;
    MenuObj *entry;
    s32 *strP;
    MenuObj **list;

    h = 0;
    yBase = 0x5C;
    i = 0;
    list = D_800B996C;
    do {
        s32 y1;
        MenuObj **listSlot;
        x1 = yBase;
        j = 0;
        listSlot = list;
        w1 = 0x78;
        g1 = 0xF;
        z1 = 0x3FC;
    a1_L:
        {
            ix1 = gMenuObjectPoolCount;
            gMenuObjectPoolCount = ix1 + 1;
            obj1 = &gMenuObjectPool[ix1];
            obj1->drawOffsetX = 0;
            obj1->drawOffsetY = 0;
            obj1->next = 0;
            obj1->blue = 0;
            obj1->green = 0;
            obj1->red = 0;
            obj1->orderingDepth = 0;
            obj1->kind = 1;
            obj1->width = w1;
            obj1->targetX = h;
            obj1->x = h;
            obj1->targetY = x1;
            obj1->y = x1;
            obj1->height = g1;
            obj1->velocityX = 0;
            obj1->velocityY = 0;
            pr1 = (POLY_FT4 *)(GraphicsAllocPolyFT4(1));
            SetPolyFT4(pr1);
            SetShadeTex(pr1, 0);
            pr1->r0 = 0x80;
            pr1->g0 = 0x80;
            pr1->b0 = 0x80;
            SetSemiTrans(pr1, 0);
            entry = obj1;
            entry->primitive = pr1;
            entry->orderingDepth = z1;
            if (j == 0) {
                *listSlot = entry;
            } else {
                (*listSlot)->next = entry;
            }
            prim2 = entry->primitive;
            entry->x = -0xF5;
            entry->velocityX = 2;
            if (j == 0) {
                u16 w;
                u8 v;
                w = (u16)entry->width;
                prim2->clut = GetClut(D_8009AF22[0], ((u16 *)D_8009AF22)[1]);
                prim2->tpage = GetTPage(D_8009AF2A[0], 3, D_8009AF1E[0],
                                        ((u16 *)D_8009AF1E)[1]);
                prim2->u0 = *(u8 *)((u8 *)D_8009AF22 + 4);
                prim2->v0 = *(u8 *)((u8 *)D_8009AF22 + 6);
                prim2->u1 = *(u8 *)((u8 *)D_8009AF2A - 4) + w;
                prim2->v1 = *(u8 *)((u8 *)D_8009AF1E + 10);
                prim2->u2 = *(u8 *)((u8 *)D_8009AF1E + 8);
                prim2->v2 = *(u8 *)((u8 *)D_8009AF2A - 2) + 0xF;
                prim2->u3 = D_8009AF26[0] + w;
                v = *(u8 *)((u8 *)D_8009AF26 + 2) + 0xF;
                prim2->v3 = v;
            } else {
                u16 w;
                u8 v;
                w = (u16)entry->width;
                prim2->clut = GetClut(D_8009AF22[0], ((u16 *)D_8009AF22)[1]);
                prim2->tpage = GetTPage(D_8009AF2A[0], 3, D_8009AF1E[0],
                                        ((u16 *)D_8009AF1E)[1]);
                prim2->u0 = *(u8 *)((u8 *)D_8009AF22 + 4);
                prim2->v0 = *(u8 *)((u8 *)D_8009AF22 + 6) + 0x21;
                prim2->u1 = *(u8 *)((u8 *)D_8009AF2A - 4) + w;
                prim2->v1 = *(u8 *)((u8 *)D_8009AF1E + 10) + 0x21;
                prim2->u2 = *(u8 *)((u8 *)D_8009AF1E + 8);
                prim2->v2 = *(u8 *)((u8 *)D_8009AF2A - 2) + 0x30;
                prim2->u3 = D_8009AF26[0] + w;
                v = *(u8 *)((u8 *)D_8009AF26 + 2) + 0x30;
                prim2->v3 = v;
            }
            j++;
            x1 += 0xF;
        }
        if (j < 2) {
            goto a1_L;
        }
        j = 0;
        w2 = 0x78;
        c2 = 0x20;
        k2 = 2;
        g2 = 0x1E;
        b2 = 0x40;
    a2_L:
        {
            ix2 = gMenuObjectPoolCount;
            gMenuObjectPoolCount = ix2 + 1;
            obj2 = &gMenuObjectPool[ix2];
            obj2->blue = 0;
            obj2->height = g2;
            obj2->drawOffsetX = 0;
            obj2->drawOffsetY = 0;
            obj2->next = 0;
            obj2->green = 0;
            obj2->red = 0;
            obj2->orderingDepth = 0;
            obj2->kind = k2;
            obj2->x = 0;
            obj2->targetX = 0;
            obj2->y = yBase;
            obj2->targetY = yBase;
            obj2->velocityX = 0;
            obj2->velocityY = 0;
            obj2->width = w2;
            obj2->red = c2;
            obj2->green = c2;
            obj2->blue = b2;
            pr2 = (POLY_F4 *)(GraphicsAllocPolyF4(1));
            obj2->primitive = pr2;
            SetPolyF4(pr2);
            SetSemiTrans(pr2, 1);
            y1 = yBase + 0x1E;
            pr2->r0 = c2;
            pr2->g0 = c2;
            pr2->b0 = b2;
            pr2->x0 = 0;
            pr2->y0 = yBase;
            pr2->x1 = w2;
            pr2->y1 = yBase;
            pr2->x2 = 0;
            pr2->y2 = y1;
            pr2->x3 = w2;
            pr2->y3 = y1;
            obj2->orderingDepth = 0x3FD;
            obj2->velocityX = k2;
            obj2->x = -0xF5;
            obj2->velocityX = k2;
            entry->next = obj2;
            entry = obj2;
            j++;
        }
        if (j < 2) {
            goto a2_L;
        }
        asm("" : : "r"(pr2));
        list++;
        yBase = y1;
        i++;
    } while (i < 4);
    {
        s32 n;
        n = 0;
        i = 0;
        do {
            s16 yLoad;
            MenuObj *node;
            node = D_800B996C[i];
            m = 0;
            yLoad = node->targetY;
            yBase = yLoad + 3;
            do {
                u8 primIdx;
                MenuText *textPrim;
                MenuText *primLoad;
                MenuFontSet(2, 2);
                value = (s16)func_8005A8EI(D_8009A268[n]);
                switch (m) {
                case 0:
                    h = (0x78 - value) / 2;
                    break;
                case 1:
                    h = 8;
                    break;
                case 2:
                    h = 0x70 - value;
                    break;
                }
                ix3 = gMenuObjectPoolCount;
                gMenuObjectPoolCount = ix3 + 1;
                obj3 = &gMenuObjectPool[ix3];
                obj3->blue = 0;
                obj3->green = 0;
                obj3->red = 0;
                primIdx = D_800A37BC;
                entry = obj3;
                entry->drawOffsetX = 0;
                entry->drawOffsetY = 0;
                entry->next = 0;
                entry->orderingDepth = 0;
                entry->kind = 0;
                entry->targetX = h;
                entry->x = h;
                entry->targetY = yBase;
                entry->y = yBase;
                entry->velocityX = 0;
                entry->velocityY = 0;
                entry->orderingDepth = 0;
                D_800A37BC = primIdx + 1;
                textPrim = (u8 *)D_800A3654 + primIdx * 12;
                entry->primitive = textPrim;
                textPrim->shade = 0;
                textPrim->center = 0;
                textPrim->otz = 0;
                D_800BB9F4[n] = entry;
                entry->velocityX = 2;
                entry->width = value;
                entry->x = (u16)entry->targetX - 0xF5;
                entry->height = MenuFontLineHeight();
                primLoad = entry->primitive;
                primLoad->font = 2;
                primLoad->scale = 2;
                primLoad->text = D_8009A268[n];
                n++;
                if (m == 0) {
                    yBase += 0x10;
                }
                m++;
            } while (m < 3);
            i++;
        } while (i < 4);
    }
    {
        MenuObj *obj3;
        u8 *pr3;
        u8 *pq3;
        yBase = D_800B996C[0]->targetY + 0xD;
        k3 = 3;
        k9 = 9;
        w4 = 0x68;
        g4 = 5;
        z4 = 0x3F2;
        h = 8;
        i = 0;
        do {
            MenuObj **slot;
            MenuObj **tbl;
            u16 w;
            u16 hh;
            u32 scale;
            u32 level;
            ix4 = gMenuObjectPoolCount;
            gMenuObjectPoolCount = ix4 + 1;
            obj4 = &gMenuObjectPool[ix4];
            obj4->kind = 1;
            obj4->width = w4;
            obj4->drawOffsetX = 0;
            obj4->drawOffsetY = 0;
            obj4->next = 0;
            obj4->blue = 0;
            obj4->green = 0;
            obj4->red = 0;
            obj4->orderingDepth = 0;
            obj4->targetX = h;
            obj4->x = h;
            obj4->targetY = yBase;
            obj4->y = yBase;
            obj4->height = g4;
            obj4->velocityX = 0;
            obj4->velocityY = 0;
            pr4 = (POLY_FT4 *)(GraphicsAllocPolyFT4(1));
            SetPolyFT4(pr4);
            SetShadeTex(pr4, 0);
            pr4->r0 = 0x80;
            pr4->g0 = 0x80;
            pr4->b0 = 0x80;
            SetSemiTrans(pr4, 0);
            entry = obj4;
            entry->primitive = pr4;
            entry->orderingDepth = z4;
            tbl = D_800B9980;
            slot = tbl + i;
            *slot = entry;
            prim2 = entry->primitive;
            entry->x = -0xF5;
            entry->velocityX = 2;
            w = (u16)entry->width;
            hh = (u16)entry->height;
            prim2->clut = GetClut(D_8009AEA2[1], D_8009AEA6[0]);
            prim2->tpage =
                GetTPage(*(u16 *)((u8 *)D_8009AEAA + 2), 3,
                         *(u16 *)((u8 *)D_8009AEA2 - 2), D_8009AEA2[0]);
            prim2->u0 = *(u8 *)((u8 *)D_8009AEAA - 2);
            prim2->v0 = D_8009AEAA[0];
            prim2->u1 = *(u8 *)((u8 *)D_8009AEA2 + 6) + w;
            prim2->v1 = *(u8 *)((u8 *)D_8009AEA6 + 4);
            prim2->u2 = *(u8 *)((u8 *)D_8009AEA6 + 2);
            prim2->v2 = *(u8 *)((u8 *)D_8009AEA2 + 8) + hh;
            prim2->u3 = *(u8 *)((u8 *)D_8009AEAE - 6) + w;
            prim2->v3 = *(u8 *)((u8 *)D_8009AEAE - 4) + hh;
            level = D_800A3860[arg0][(u8)i];
            scale = ((((level << 1) + level) << 2) + level) >> 3;
            if (scale == 0) {
                scale = 1;
            }
            x4 = yBase + 1;
            {
                s16 y2;
                ix5 = gMenuObjectPoolCount;
                gMenuObjectPoolCount = ix5 + 1;
                obj5 = &gMenuObjectPool[ix5];
                obj5->kind = 2;
                obj5->x = k9;
                obj5->targetX = k9;
                obj5->red = 0;
                obj5->height = k3;
                obj5->blue = 0;
                obj5->red = 0x40;
                obj5->drawOffsetX = 0;
                obj5->drawOffsetY = 0;
                obj5->next = 0;
                obj5->green = 0;
                obj5->orderingDepth = 0;
                obj5->y = x4;
                obj5->targetY = x4;
                obj5->velocityX = 0;
                obj5->velocityY = 0;
                obj5->width = scale;
                obj5->green = 0x60;
                obj5->blue = 0x80;
                pr5 = (POLY_F4 *)(GraphicsAllocPolyF4(1));
                obj5->primitive = pr5;
                SetPolyF4(pr5);
                SetSemiTrans(pr5, 1);
                pr5->r0 = 0x40;
                entry = obj5;
                do {
                    pr5->b0 = 0x80;
                } while (0);
                pr5->x0 = k9;
                pr5->g0 = 0x60;
                pr5->y0 = x4;
                y2 = scale + k9;
                pr5->x1 = y2;
                i++;
                pr5->y1 = x4;
                pr5->x2 = k9;
                pr5->y2 = yBase + 4;
                pr5->y3 = yBase + 4;
                pr5->x3 = y2;
                entry->orderingDepth = 0x3E8;
                (*slot)->next = entry;
                entry->x = -0xF5;
                entry->velocityX = 2;
            }
            yBase += 0x1E;
        } while (i < 4);
    }
    {
        u16 w;
        u16 hh;
        ix6 = gMenuObjectPoolCount;
        gMenuObjectPoolCount = ix6 + 1;
        obj6 = &gMenuObjectPool[ix6];
        obj6->drawOffsetX = 0;
        obj6->drawOffsetY = 0;
        obj6->next = 0;
        obj6->blue = 0;
        obj6->green = 0;
        obj6->red = 0;
        obj6->orderingDepth = 0;
        obj6->kind = 1;
        obj6->targetY = 0x2A;
        obj6->targetX = 0;
        obj6->y = 0x2A;
        obj6->width = 0x78;
        obj6->x = 0;
        obj6->height = 0x30;
        obj6->velocityX = 0;
        obj6->velocityY = 0;
        pr6 = (POLY_FT4 *)(GraphicsAllocPolyFT4(1));
        SetPolyFT4(pr6);
        SetShadeTex(pr6, 0);
        pr6->r0 = 0x80;
        pr6->g0 = 0x80;
        pr6->b0 = 0x80;
        SetSemiTrans(pr6, 0);
        entry = obj6;
        entry->primitive = pr6;
        entry->orderingDepth = 0x3FC;
        do {
        } while (0);
        prim2 = entry->primitive;
        w = (u16)entry->width;
        hh = (u16)entry->height;
        entry->velocityX = 2;
        j = 0;
        D_800A39ACPtr = entry;
        entry->velocityY = 0;
        prim2->clut = GetClut(D_8009AF22[0], ((u16 *)D_8009AF22)[1]);
        prim2->tpage =
            GetTPage(D_8009AF2A[0], 3, D_8009AF1E[0], ((u16 *)D_8009AF1E)[1]);
        prim2->u0 = *(u8 *)((u8 *)D_8009AF22 + 4);
        prim2->v0 = *(u8 *)((u8 *)D_8009AF22 + 6);
        prim2->u1 = *(u8 *)((u8 *)D_8009AF2A - 4) + w;
        prim2->v1 = *(u8 *)((u8 *)D_8009AF1E + 10);
        prim2->u2 = *(u8 *)((u8 *)D_8009AF1E + 8);
        prim2->v2 = *(u8 *)((u8 *)D_8009AF2A - 2) + hh;
        prim2->u3 = D_8009AF26[0] + w;
        prim2->v3 = *(u8 *)((u8 *)D_8009AF26 + 2) + hh;
    }
    yBase = 0x2A;
    h = 0x78;
    k2b = 2;
    k30 = 0x30;
    D_800A39ACPtr->x = -0x7D;
    D_800A39ACPtr->velocityX = 2;
    do {
        ix7 = gMenuObjectPoolCount;
        gMenuObjectPoolCount = ix7 + 1;
        obj7 = &gMenuObjectPool[ix7];
        obj7->blue = 0;
        obj7->height = k30;
        obj7->drawOffsetX = 0;
        obj7->drawOffsetY = 0;
        obj7->next = 0;
        obj7->green = 0;
        obj7->red = 0;
        obj7->orderingDepth = 0;
        obj7->kind = k2b;
        obj7->x = 0;
        obj7->targetX = 0;
        obj7->y = yBase;
        obj7->targetY = yBase;
        obj7->velocityX = 0;
        obj7->velocityY = 0;
        obj7->width = h;
        obj7->red = 0x20;
        obj7->green = 0x20;
        obj7->blue = 0x40;
        pr7 = (POLY_F4 *)(GraphicsAllocPolyF4(1));
        obj7->primitive = pr7;
        SetPolyF4(pr7);
        SetSemiTrans(pr7, 1);
        pr7->r0 = 0x20;
        pr7->g0 = 0x20;
        pr7->b0 = 0x40;
        pr7->y2 = 0x5A;
        pr7->y3 = 0x5A;
        pr7->x0 = 0;
        pr7->y0 = yBase;
        pr7->x1 = h;
        pr7->y1 = yBase;
        pr7->x2 = 0;
        pr7->x3 = h;
        obj7->orderingDepth = 0x3FD;
        obj7->velocityX = k2b;
        obj7->x = -0x7D;
        obj7->velocityX = k2b;
        entry->next = obj7;
        entry = obj7;
        j++;
    } while (j < 2);
    asm("" : : "r"(pr7));
    k41 = 0x41;
    k32 = 0x32;
    k7 = 7;
    yBase = 0x2F;
    i = 0;
    do {
        s32 iOff;
        MenuObj **slot;
        u8 *prD7;
        u16 w;
        u16 hh;
        ix8 = gMenuObjectPoolCount;
        gMenuObjectPoolCount = ix8 + 1;
        obj8 = &gMenuObjectPool[ix8];
        obj8->kind = 1;
        obj8->targetX = k41;
        obj8->x = k41;
        obj8->width = k32;
        obj8->drawOffsetX = 0;
        obj8->drawOffsetY = 0;
        obj8->next = 0;
        obj8->blue = 0;
        obj8->green = 0;
        obj8->red = 0;
        obj8->orderingDepth = 0;
        obj8->targetY = yBase;
        obj8->y = yBase;
        obj8->height = k7;
        obj8->velocityX = 0;
        obj8->velocityY = 0;
        pr8 = (POLY_FT4 *)(GraphicsAllocPolyFT4(1));
        SetPolyFT4(pr8);
        SetShadeTex(pr8, 0);
        pr8->r0 = 0x80;
        pr8->g0 = 0x80;
        pr8->b0 = 0x80;
        SetSemiTrans(pr8, 0);
        entry = obj8;
        entry->primitive = pr8;
        entry->orderingDepth = 1;
        slot = &D_800B60B8[i];
        *slot = entry;
        prim2 = entry->primitive;
        entry->velocityX = 2;
        entry->x = -0x7D;
        w = (u16)entry->width;
        hh = (u16)entry->height;
        x6 = yBase + 1;
        prim2->clut = GetClut(D_8009AEB2[0], *(u16 *)((u8 *)D_8009AEB2 + 2));
        prim2->tpage = GetTPage(D_8009AEBA[0], 3, *(u16 *)D_8009AEAE,
                                *(u16 *)((u8 *)D_8009AEB2 - 2));
        prim2->u0 = D_8009AEB6[0];
        prim2->v0 = *(u8 *)((u8 *)D_8009AEB2 + 6);
        prim2->u1 = *(u8 *)&D_8009AEAE[8] + w;
        prim2->v1 = *(u8 *)&D_8009AEAE[10];
        prim2->u2 = *(u8 *)((u8 *)D_8009AEB2 + 4);
        prim2->v2 = *(u8 *)((u8 *)D_8009AEBA - 2) + hh;
        prim2->u3 = *(u8 *)((u8 *)D_8009AEBA - 4) + w;
        prim2->v3 = *(u8 *)&D_8009AEB6[2] + hh;
        {
            MenuObj *objB8;
            u8 *prC8;
            s16 y2;
            ix9 = gMenuObjectPoolCount;
            gMenuObjectPoolCount = ix9 + 1;
            objB9 = &gMenuObjectPool[ix9];
            objB9->kind = 2;
            objB9->x = 0x42;
            objB9->drawOffsetX = 0;
            objB9->drawOffsetY = 0;
            objB9->next = 0;
            objB9->blue = 0;
            objB9->green = 0;
            objB9->red = 0;
            objB9->orderingDepth = 0;
            objB9->targetX = 0x42;
            objB9->y = x6;
            objB9->targetY = x6;
            objB9->velocityX = 0;
            objB9->velocityY = 0;
            objB9->width = 0x30;
            objB9->height = 5;
            objB9->red = 0x40;
            objB9->green = 0x60;
            objB9->blue = 0x80;
            prC9 = (POLY_F4 *)(GraphicsAllocPolyF4(1));
            objB9->primitive = prC9;
            SetPolyF4(prC9);
            SetSemiTrans(prC9, 0);
            prC9->b0 = 0x80;
            prC9->x0 = 0x42;
            prC9->r0 = 0x40;
            prC9->g0 = 0x60;
            prC9->y0 = x6;
            prC9->x1 = 0x72;
            prC9->y1 = x6;
            prC9->x2 = 0x42;
            {
                s32 y6;
                y6 = yBase + 6;
                prC9->y2 = y6;
                prC9->x3 = 0x72;
                prC9->y3 = y6;
            }
            entry = objB9;
            (*slot)->next = entry;
            entry->x = -0x7D;
            entry->velocityX = 2;
            entry->orderingDepth = 0;
        }
        MenuFontSet(2, 2);
        strP = &D_8009A298[i];
        value = (s16)func_8005A8EI(*strP);
        {
            u8 primIdx;
            MenuObj *objC9;
            MenuText *textPrim;
            ixB10 = gMenuObjectPoolCount;
            gMenuObjectPoolCount = ixB10 + 1;
            objC10 = &gMenuObjectPool[ixB10];
            objC10->blue = 0;
            objC10->green = 0;
            objC10->red = 0;
            primIdx = D_800A37BC;
            entry = objC10;
            h = 0x3E - value;
            entry->drawOffsetX = 0;
            entry->drawOffsetY = 0;
            entry->next = 0;
            entry->orderingDepth = 0;
            entry->kind = 0;
            entry->targetX = h;
            entry->x = h;
            entry->targetY = yBase;
            entry->y = yBase;
            entry->velocityX = 0;
            entry->velocityY = 0;
            entry->orderingDepth = 0;
            D_800A37BC = primIdx + 1;
            textPrim = (u8 *)D_800A3654 + primIdx * 12;
            entry->primitive = textPrim;
            textPrim->shade = 0;
            textPrim->center = 0;
            textPrim->otz = 0;
            D_800AE168[i] = entry;
            entry->velocityX = 2;
            entry->width = value;
            entry->x = entry->targetX - 0xAD;
            entry->height = MenuFontLineHeight();
            prD10 = entry->primitive;
            prD10->font = 2;
            prD10->scale = 2;
        }
        i++;
        prD10->text = *strP;
        yBase += 0xA;
    } while (i < 4);
    if (arg1 != 0) {
        u8 primIdx;
        MenuText *textPrim;
        MenuText *primLoad;
        ix11 = gMenuObjectPoolCount;
        gMenuObjectPoolCount = ix11 + 1;
        obj11 = &gMenuObjectPool[ix11];
        obj11->blue = 0;
        obj11->green = 0;
        obj11->red = 0;
        primIdx = D_800A37BC;
        m = (s32)obj11;
        ((MenuObj *)m)->targetX = 5;
        ((MenuObj *)m)->drawOffsetX = 0;
        ((MenuObj *)m)->drawOffsetY = 0;
        ((MenuObj *)m)->next = 0;
        ((MenuObj *)m)->orderingDepth = 0;
        ((MenuObj *)m)->kind = 0;
        ((MenuObj *)m)->x = 5;
        ((MenuObj *)m)->targetY = 0x20;
        ((MenuObj *)m)->y = 0x20;
        ((MenuObj *)m)->velocityX = 0;
        ((MenuObj *)m)->velocityY = 0;
        ((MenuObj *)m)->orderingDepth = 0;
        D_800A37BC = primIdx + 1;
        textPrim = (u8 *)D_800A3654 + primIdx * 12;
        ((MenuObj *)m)->primitive = textPrim;
        textPrim->shade = 0;
        textPrim->center = 0;
        textPrim->otz = 0;
        ((MenuObj *)m)->velocityX = 2;
        ((MenuObj *)m)->width = value;
        ((MenuObj *)m)->x = (u16)((MenuObj *)m)->targetX - 0xAD;
        ((MenuObj *)m)->height = MenuFontLineHeight();
        primLoad = ((MenuObj *)m)->primitive;
        primLoad->font = 2;
        primLoad->scale = 2;
        primLoad->text = D_8009A298[arg0 + 4];
        entry->next = (MenuObj *)m;
    }
    func_80060008(arg0);
}

void MenuUpdateObjectGroups(void) {
    extern MenuObj *D_800A39ACSmall asm("D_800A39AC.NON_MATCHING");
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        MenuUpdateObjectPosition(D_800B996C[i], 1);
        MenuUpdateObjectPosition(D_800B9980[i], 1);
        for (j = 0; j < 3; j++) {
            MenuUpdateObjectPosition(D_800BB9F4[i * 3 + j], 1);
        }
    }
    MenuUpdateObjectPosition(D_800A39ACSmall, 1);
    for (i = 0; i < 4; i++) {
        MenuUpdateObjectPosition(D_800AE168[i], 1);
        MenuUpdateObjectPosition(D_800B60B8[i], 1);
    }
}

MenuObj *MenuSetGridObjectScale(u8 x, u8 y) {
    u32 scale;
    u32 level;
    u32 result;
    MenuObj *node;
    MenuObj *entry;

    level = D_800A3860[x][y];
    scale = ((level << 1) + level) << 2;
    scale += level;
    result = scale >> 3;
    if (result == 0) {
        result = 1;
    }
    node = D_800B9980[y];
    entry = node->next;
    entry->width = result;
    return entry;
}

extern u8 D_800A3861U8[][4] asm("D_800A3861.NON_MATCHING");
extern u8 D_800A3862U8[][4] asm("D_800A3862.NON_MATCHING");
extern u8 D_800A3863U8[][4] asm("D_800A3863.NON_MATCHING");

void func_80060008(u8 arg0) {
    s32 vals[4];
    s32 diff;
    s32 aCol;
    s32 cCol;
    s32 q;
    MenuObj *node;
    u8 *entry;

    vals[0] = (0x3F - D_800A3861U8[arg0][0]) * 700 / 1000 +
              D_800A3863U8[arg0][0] * 300 / 1000;
    aCol = D_800A3861U8[arg0][0];
    vals[3] = aCol / 5 + (0x3F - D_800A3860[arg0][0]) * 800 / 1000;
    vals[2] =
        D_800A3860[arg0][0] * 600 / 1000 + D_800A3862U8[arg0][0] * 400 / 1000;
    diff = D_800A3862U8[arg0][0] - D_800A3861U8[arg0][0];
    if (diff < 0) {
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
        entry = *(u8 **)(&*(u8 *)&node->next);
        *(s16 *)(&entry[0x16]) = q;
        diff++;
    } while (diff < 4);
}

/* Same body as func_8005CF34. Retail emits it out of line there and inlines
 * it at each call site below; the inline parameter copies place the moves
 * in the loop. */
static inline void MenuObjDrawText(MenuObj *window, u8 code, u8 first,
                                   u8 second, s32 textId) {
    MenuText *prim;

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

void MenuDrawLevelBars(s8 selectedColumn, u8 player) {
    s32 i;
    s32 j;
    s32 first;
    s8 sel;
    u32 level;
    u32 scale;
    MenuObj *node;
    MenuObj *window;
    MenuText *prim;

    sel = selectedColumn - 2;
    for (i = 0; i < 4; i++) {
        level = D_800A3860[player][(u8)i];
        scale = ((((level << 1) + level) << 2) + level) >> 3;
        if (scale == 0) {
            scale = 1;
        }
        D_800B9980[(u8)i]->next->width = scale;
        MenuDrawObjectList(D_800B996C[i], 0xFF);
        MenuDrawObjectList(D_800B9980[i], i != sel);
        first = i != sel;
        for (j = 0; j < 3; j++) {
            window = D_800BB9F4[i * 3 + j];
            prim = window->primitive;
            if (i == sel) {
                prim->otz = 0;
            } else {
                prim->otz = 0x3ED;
            }
            MenuObjDrawText(window, 0, first, 0, 0);
        }
    }
    MenuDrawObjectList(D_800A39ACPtr, 0xFF);
    for (i = 0; i < 4; i++) {
        MenuDrawObjectList(D_800B60B8[i], 0xFF);
        MenuObjDrawText(D_800AE168[i], 0, 0, 0, 0);
    }
    node = D_800AE168[3]->next;
    if (node != 0) {
        MenuDrawObjectList(node, 0xFF);
    }
}

extern MenuObj *D_800A3A68Store asm("D_800A3A68");
extern s32 D_8009A2B0[];
extern s32 D_8009A2BC[];
void func_800606D4(void) {
    MenuObj *entry;
    MenuObj *cur;
    MenuObj *row;
    POLY_FT4 *prim2;
    u16 width;
    MenuObj *sign;
    int new_var3;
    s16 *new_var2;
    u8 *mark;
    u8 *cell;
    u8 *writeEnd;
    u8 idx2;
    u8 primIdx2;
    s32 i;
    s32 *p;
    s32 two;
    s32 *table;
    {
        u8 index;
        MenuObj *object;
        u8 *prim;
        u16 w;
        u16 h;
        index = gMenuObjectPoolCount++;
        object = &gMenuObjectPool[index];
        object->kind = 1;
        object->targetY = 0xA7;
        object->y = 0xA7;
        object->width = 0x78;
        object->drawOffsetX = 0;
        object->drawOffsetY = 0;
        object->next = 0;
        object->blue = 0;
        object->green = 0;
        object->red = 0;
        new_var3 = 2;
        object->orderingDepth = 0;
        object->targetX = 0;
        idx2 = 0x30;
        object->x = 0;
        object->height = idx2;
        object->velocityX = 0;
        object->velocityY = 0;
        prim = GraphicsAllocPolyFT4(1);
        SetPolyFT4((POLY_FT4 *)prim);
        SetShadeTex(prim, 0);
        prim[4] = 0x80;
        prim[5] = 0x80;
        prim[6] = 0x80;
        SetSemiTrans(prim, 0);
        entry = object;
        entry->primitive = prim;
        do {
            entry->orderingDepth = new_var3;
        } while (0);

        prim2 = (POLY_FT4 *)((u8 *)entry->primitive);
        entry->velocityX = 0;
        entry->velocityY = 0;
        entry->x = -0x78;
        w = (u16)entry->width;
        h = (u16)entry->height;
        D_800A38A8 = entry;
        prim2->clut = GetClut(D_8009AF22[0], ((u16 *)D_8009AF22)[1]);
        prim2->tpage =
            GetTPage(D_8009AF2A[0], 3, D_8009AF1E[0], ((u16 *)D_8009AF1E)[1]);
        prim2->u0 = D_8009AF26[0];
        prim2->v0 = *(u8 *)(((u8 *)D_8009AF22) + 6);
        prim2->u1 = *(u8 *)(((u8 *)D_8009AF1E) + 8) + w;
        prim2->v1 = *(u8 *)(((u8 *)D_8009AF1E) + 10);
        prim2->u2 = *(u8 *)(((u8 *)D_8009AF22) + 4);
        prim2->v2 = *(u8 *)(((u8 *)D_8009AF2A) - 2) + h;
        prim2->u3 = *(u8 *)(((u8 *)D_8009AF2A) - 4) + w;
        prim2->v3 = *(u8 *)(((u8 *)D_8009AF26) + 2) + h;
    }
    {
        u8 index;
        MenuObj *object;
        u8 *prim;
        index = gMenuObjectPoolCount++;
        object = &gMenuObjectPool[index];
        object->drawOffsetX = 0;
        object->drawOffsetY = 0;
        object->next = 0;
        object->blue = 0;
        object->green = 0;
        object->red = 0;
        new_var3 = 2;
        object->orderingDepth = 0;
        object->kind = 2;
        object->x = 0xA;
        object->targetX = 0xA;
        object->y = 0xC6;
        object->targetY = 0xC6;
        object->velocityX = 0;
        object->velocityY = 0;
        object->width = 0x32;
        object->height = 3;
        object->red = 0x40;
        object->green = 0x60;
        object->blue = 0x80;
        prim = GraphicsAllocPolyF4(1);
        object->primitive = prim;
        SetPolyF4(prim);
        SetSemiTrans(prim, 0);
        cur = object;
        prim[4] = 0x40;
        prim[5] = 0x60;
        prim[6] = 0x80;
        ((POLY_F4 *)prim)->x0 = 0xA;
        ((POLY_F4 *)prim)->y0 = 0xC6;
        ((POLY_F4 *)prim)->x1 = 0x3C;
        ((POLY_F4 *)prim)->y1 = 0xC6;
        ((POLY_F4 *)prim)->x2 = 0xA;
        ((POLY_F4 *)prim)->y2 = 0xC9;
        ((POLY_F4 *)prim)->x3 = 0x3C;
        ((POLY_F4 *)prim)->y3 = 0xC9;
        cur->drawOffsetX = 9;
        cur->velocityX = 2;
        cur->orderingDepth = 0;
        entry->next = cur;
        entry = cur;
    }
    i = 0;
    for (i = 0; i < 2; i++) {
        u8 index;
        u8 *prim;
        index = gMenuObjectPoolCount++;
        row = &gMenuObjectPool[index];
        row->kind = 2;
        row->y = 0xA7;
        row->targetY = 0xA7;
        row->width = 0x78;
        row->blue = 0;
        row->height = idx2;
        row->drawOffsetX = 0;
        row->drawOffsetY = 0;
        row->next = 0;
        row->green = 0;
        row->red = 0;
        row->orderingDepth = 0;
        row->x = 0;
        row->targetX = 0;
        row->velocityX = 0;
        row->velocityY = 0;
        row->red = 0x20;
        row->green = 0x20;
        row->blue = 0x40;
        prim = GraphicsAllocPolyF4(1);
        row->primitive = prim;
        SetPolyF4(prim);
        SetSemiTrans(prim, 1);
        cur = row;
        prim[6] = 0x40;
        ((POLY_F4 *)prim)->y0 = 0xA7;
        ((POLY_F4 *)prim)->x1 = 0x78;
        ((POLY_F4 *)prim)->y1 = 0xA7;
        ((POLY_F4 *)prim)->y2 = 0xD7;
        ((POLY_F4 *)prim)->y3 = 0xD7;
        prim[4] = 0x20;
        prim[5] = 0x20;
        ((POLY_F4 *)prim)->x0 = 0;
        ((POLY_F4 *)prim)->x2 = 0;
        ((POLY_F4 *)prim)->x3 = 0x78;
        cur->x = -0x78;
        cur->velocityX = 2;
        cur->orderingDepth = 3;
        entry->next = cur;
        entry = cur;
    }

    {
        u8 index;
        u8 primIndex;
        MenuObj *panel;
        POLY_FT4 *face;
        MenuObj *frame;
        u8 *tile;
        u8 *tile2;
        u16 w;
        u16 h;
        s16 x3;
        index = gMenuObjectPoolCount++;
        panel = &gMenuObjectPool[index];
        panel->targetX = 8;
        panel->x = 8;
        panel->targetY = 0xC5;
        panel->y = 0xC5;
        panel->width = 0x68;
        panel->drawOffsetX = 0;
        panel->drawOffsetY = 0;
        panel->next = 0;
        panel->blue = 0;
        panel->green = 0;
        panel->red = 0;
        panel->orderingDepth = 0;
        panel->kind = 1;
        panel->height = 5;
        panel->velocityX = 0;
        panel->velocityY = 0;
        face = (POLY_FT4 *)(GraphicsAllocPolyFT4(1));
        SetPolyFT4(face);
        SetShadeTex(face, 0);
        face->r0 = 0x80;
        face->g0 = 0x80;
        face->b0 = 0x80;
        SetSemiTrans(face, 0);
        cur = panel;
        asm("" : "=r"(cur) : "0"(cur));
        panel->primitive = face;
        panel->orderingDepth = 1;
        prim2 = (POLY_FT4 *)((u8 *)cur->primitive);
        cur->velocityX = 2;
        asm("" : "=r"(x3) : "0"(8));
        cur->drawOffsetX = x3;
        w = (u16)cur->width;
        h = (u16)cur->height;
        prim2->clut = GetClut(((u16 *)D_8009AEA2)[1], D_8009AEA6[0]);
        *(s16 *)&prim2->tpage =
            GetTPage(((u16 *)D_8009AEAA)[1], 3,
                     *(u16 *)(((u8 *)D_8009AEA2) - 2), D_8009AEA2[0]);
        prim2->u0 = *(u8 *)(((u8 *)D_8009AEAA) - 2);
        prim2->v0 = D_8009AEAA[0];
        prim2->u1 = *(u8 *)(((u8 *)D_8009AEA2) + 6) + w;
        prim2->v1 = *(u8 *)(((u8 *)D_8009AEA6) + 4);
        prim2->u2 = *(u8 *)(((u8 *)D_8009AEA6) + 2);
        prim2->v2 = *(u8 *)(((u8 *)D_8009AEA2) + 8) + h;
        prim2->u3 = *(u8 *)(((u8 *)D_8009AEAE) - 6) + w;
        prim2->v3 = *(u8 *)(((u8 *)D_8009AEAE) - 4) + h;
        index = gMenuObjectPoolCount;
        frame = &gMenuObjectPool[index];
        row->next = cur;
        gMenuObjectPoolCount = index + 1;
        frame->drawOffsetX = 0;
        frame->drawOffsetY = 0;
        frame->next = 0;
        frame->blue = 0;
        frame->green = 0;
        frame->red = 0;
        frame->orderingDepth = 0;
        frame->kind = 0;
        frame->targetX = 0;
        frame->x = 0;
        frame->targetY = 0xB1;
        frame->y = 0xB1;
        frame->velocityX = 0;
        primIndex = D_800A37BC;
        asm volatile("" : : "r"(cur));
        cur = frame;
        asm volatile("" : : "r"(cur), "r"(primIndex));
        tile = (u8 *)D_800A3654;
        cur->velocityY = 0;
        cur->orderingDepth = 0;
        asm volatile("" : : "r"(primIndex));
        D_800A37BC = primIndex + 1;
        tile += primIndex * 12;
        cur->primitive = tile;
        tile[0] = 0;
        tile[3] = 0;
        ((MenuText *)tile)->otz = 0;
        tile2 = cur->primitive;
        width = 0xCA;
        two = 2;
        D_800A3A68Store = cur;
        cur->orderingDepth = 0;
        tile2[1] = 2;
        tile2[2] = 2;
        do {
        } while (0);
        ((MenuText *)tile2)->text = D_8009A2B0[0];
        table = D_8009A2BC;
        asm("" : "=r"(p) : "0"(table));
        p = table;
        entry = cur;
        panel->next = entry;
    }
    do {
        s32 x;
        s32 value;
        MenuFontSet(2, 2);
        value = (s16)MenuStringWidth(*p);
        do {
            if (p != table) {
                x = 0x70 - value;
            } else {
                x = 8;
            }
            idx2 = gMenuObjectPoolCount++;
            sign = &gMenuObjectPool[idx2];
            sign->blue = 0;
            sign->green = 0;
            sign->red = 0;
            primIdx2 = D_800A37BC;
        } while (0);
        cur = sign;
        mark = (u8 *)D_800A3654;
        cur->drawOffsetX = 0;
        cur->drawOffsetY = 0;
        cur->next = 0;
        new_var2 = &cur->orderingDepth;
        *new_var2 = 0;
        cur->kind = 0;
        cur->targetX = x;
        cur->x = x;
        cur->targetY = width;
        cur->y = width;
        cur->velocityX = 0;
        cur->velocityY = 0;
        *new_var2 = 0;
        asm volatile("" ::: "memory");
        D_800A37BC = primIdx2 + 1;
        mark += primIdx2 * 12;
        cur->primitive = mark;
        mark[0] = 0;
        mark[3] = 0;
        ((MenuText *)mark)->otz = 0;
        cur->drawOffsetX = x;
        cur->width = value;
        cur->height = MenuFontLineHeight();
        cell = cur->primitive;
        cur->velocityX = two;
        *new_var2 = 0;
        cell[1] = two;
        cell[2] = two;
        ((MenuText *)cell)->text = *p;
        p++;
        entry->next = cur;
        entry = cur;
    } while ((s32)p < (s32)(table + 2));
    asm("" : : "r"(two), "r"(two));
}

typedef struct PanelChild {
    u8 pad0[8];
    s32 text;
} PanelChild;
extern MenuObj *D_800A3A68;
void MenuCenterText(s32 textIndex) {
    s32 text;
    s32 textWidth;
    s32 textX;
    MenuFontSet(2, 2);
    text = D_8009A2B0[textIndex & 0xFF];
    ((PanelChild *)D_800A3A68->primitive)->text = text;
    textWidth = MenuStringWidth(text);
    textX = (0x78 - textWidth) / 2;
    D_800A3A68->drawOffsetX = textX;
    D_800A3A68->width = (s16)textWidth;
}

void MenuSetLinkedObjectLayout(s32 a, s32 b, s16 c) {
    MenuObj *node;
    node = D_800A38A8;
    while (node != 0) {
        node->velocityX = c;
        node->x = (u16)node->drawOffsetX + a;
        node->targetX = (u16)node->drawOffsetX + b;
        node = node->next;
    }
}

extern u8 gMusicVolumeScaledLui asm("gMusicVolumeScaledAbsolute");
void MenuSetVolume(s32 volumePercent, s32 volumeSettingIndex) {
    MenuObj *node;
    u8 x;

    node = (u8 *)D_800A38A8->next;
    volumeSettingIndex &= 0xFF;
    x = volumePercent;
    node->width = x;
    if (volumeSettingIndex != 0) {
        x = volumePercent;
        gMusicVolumeScaledLui = (x * 127) / 100;
        SoundSetSlotVolume(1, 0x7F, 0x7F);
    } else {
        CdSetMixVolume(x);
    }
}

typedef union {
    s32 value;
    s64 home;
} MenuWordHome;
typedef union {
    s8 value;
    s64 home;
} MenuCounterHome;
typedef struct {
    s8 tab[7];
} MenuRowList;
extern s8 D_800A3348[];
extern MenuObj *gPadPictureMenuLists[];
extern u8 *D_800A3A1C[];
extern MenuObj *D_800A3888[];
extern u8 *D_800A3A84[];
extern u8 *D_800A37FC[];
extern void *D_800A37F8;
extern s32 D_8009AC00[3];
extern s32 D_8009AC08[];
extern s32 D_8009AC10[];
extern s32 D_8009A314[];
extern u16 D_8009AEA0[];
extern u16 D_8009AEA4[];
extern u16 D_8009AEAC[];
extern u8 D_8009AEA8[];
extern void MenuSetTextObject(MenuObj *, u8, u8, s32, u8, s32);
extern void ListSetFieldsAndEnable(MenuObj *, s16, s16, s16);
extern u8 D_800A3644[9];

void func_80060FD8(void) {
    /* These are the observed fifth and sixth stack argument homes. */
    struct {
        s32 fifth;
        s32 sixth;
    } labelArgs;
    register MenuObj *currentNode asm("$22");
    MenuObj *previousNode;
    MenuRowList rowList;
    MenuCounterHome panelIndex;
    s8 backgroundIndex;
    s8 borderIndex;
    s8 textIndex;
    s32 panelState;
    s8 rowSide;
    s8 rowItem;
    MenuWordHome packetWidth;
    MenuWordHome packetHeight;
    MenuWordHome textureRow;
    MenuWordHome colorHome;
    MenuWordHome stripPanel;
    MenuWordHome sideOffset;
    MenuWordHome markerPanel;
    MenuWordHome triangleOffset;
    MenuWordHome shadeHome;
    s32 backgroundShade;
    register s32 textCenterX asm("$17");
    s32 initialShade;
    u32 panelMode;
    register s32 textLeftX asm("$19");
    s64 callAccumulator;
    register s32 panelTableBase asm("$12");
    register s32 previousPanelByte asm("$12");
    register s32 nextPanel asm("$2");

    {
        register u32 initialIndex asm("$4");
        register MenuText *cell asm("$16");
        s32 centered;
        initialIndex = gMenuObjectPoolCount;
        rowList = *(MenuRowList *)D_800A3348;
        /* These slots reproduce observed compiler spill homes.
         * They do not imply original source struct types. */
        asm volatile(""
                     : "=m"(panelIndex.value), "=m"(packetWidth.value),
                       "=m"(packetHeight.value), "=m"(textureRow.value),
                       "=m"(colorHome.value));
        asm volatile(""
                     : "=m"(stripPanel.value), "=m"(sideOffset.value),
                       "=m"(markerPanel.value), "=m"(triangleOffset.value),
                       "=m"(shadeHome.value));
        /* Keep the allocation and pool loads in their retail order. */
        asm volatile(".set\tnoreorder\n"
                     "lw         $v1, gMenuObjectPool\n"
                     "addiu      $v0, $a0, 0x1\n"
                     "sb         $v0, gMenuObjectPoolCount\n"
                     "sll        $v0, $a0, 3\n"
                     "addu       $v0, $v0, $a0\n"
                     "sll        $v0, $v0, 2\n"
                     "addu       $v1, $v1, $v0\n"
                     "sb         $zero, 0x4($v1)\n"
                     "sb         $zero, 0x3($v1)\n"
                     "sb         $zero, 0x2($v1)\n"
                     "lbu        $a0, D_800A37BC\n"
                     "addu       %0, $v1, $zero\n"
                     "lw         $v1, D_800A3654\n"
                     "sh         $zero, 0x12(%0)\n"
                     "sh         $zero, 0x14(%0)\n"
                     "sw         $zero, 0x1C(%0)\n"
                     "sh         $zero, 0x1A(%0)\n"
                     "sh         $zero, 0x0(%0)\n"
                     "sh         $zero, 0xA(%0)\n"
                     "sh         $zero, 0x6(%0)\n"
                     "sh         $zero, 0xC(%0)\n"
                     "sh         $zero, 0x8(%0)\n"
                     "sh         $zero, 0xE(%0)\n"
                     "sh         $zero, 0x10(%0)\n"
                     "sh         $zero, 0x1A(%0)\n"
                     "addiu      $v0, $a0, 0x1\n"
                     "sb         $v0, D_800A37BC\n"
                     "sll        $v0, $a0, 1\n"
                     "addu       $v0, $v0, $a0\n"
                     "sll        $v0, $v0, 2\n"
                     "addu       $v1, $v1, $v0\n"
                     "sw         $v1, 0x20(%0)\n"
                     "sb         $zero, 0x0($v1)\n"
                     "sb         $zero, 0x3($v1)\n"
                     "sw         $zero, 0x4($v1)\n"
                     "lw         %1, 0x20(%0)\n"
                     "ori        $v0, $zero, 0x1\n"
                     "sh         $v0, 0x1A(%0)\n"
                     "ori        $v0, $zero, 0xDA\n"
                     "sh         $v0, 0x14(%0)\n"
                     "ori        $v0, $zero, 0x2\n"
                     "sb         $v0, 0x2(%1)\n"
                     "sb         $v0, 0x1(%1)\n"
                     "lui        $v0, %%hi(D_8009AC00)\n"
                     "lw         $v0, %%lo(D_8009AC00)($v0)\n"
                     "ori        $a1, $zero, 0x2\n"
                     "ori        $a0, $zero, 0x2\n"
                     "jal        MenuFontSet\n"
                     "sw        $v0, 0x8(%1)\n"
                     ".set\tnoreorder\n"
                     ".set\treorder\n"
                     : "=r"(currentNode), "=r"(cell)
                     : "r"(initialIndex)
                     : "$2", "$3", "$4", "$5", "$31", "memory");
        centered = MenuTextCenterOffset(0x140, cell->text);
        asm volatile("lui $a0,%%hi(D_800A3644)\n"
                     "lbu $a0,%%lo(D_800A3644)($a0)\n"
                     "sh $v0,0x12($s6)\n"
                     "sw $s6,D_800A37F8\n"
                     "bnez $a0,1f\n"
                     "ori $v1,$zero,0x3c\n"
                     "ori $v1,$zero,0x55\n"
                     "1:\n"
                     ".set\treorder\n"
                     : "=r"(panelMode), "=r"(initialShade)
                     : "r"(centered), "r"(currentNode)
                     : "memory");
    }
    {
        s32 condition;
        asm volatile("addiu $v0,$a0,1\n"
                     ".set\treorder\n"
                     : "=r"(condition)
                     : "r"(panelMode));
        panelIndex.value = 0;
        if (condition == 0) {
            goto panelsDone;
        }
    }
    initialShade = (u32)initialShade << 24;
    colorHome.value = initialShade;
panelLoop:
    {
        {
            MenuObj *node;
            register u8 *primitive asm("$17");
            s32 panelNumber;
            s32 panelByteOffset;
            s32 packetMode;
            s32 loopCondition;
            asm volatile(".set\tnoreorder\n"
                         "lbu $t3,%4\n"
                         "addu $s7,$zero,$zero\n"
                         "ori $a2,$zero,0x20\n"
                         "sll $v0,$t3,24\n"
                         "sra $s2,$v0,24\n"
                         "sll $s3,$s2,2\n"
                         ".set\treorder\n"
                         : "=r"(backgroundIndex), "=r"(backgroundShade),
                           "=r"(panelNumber), "=r"(panelByteOffset)
                         : "m"(panelIndex.value)
                         : "$2", "$11");
            do {
                asm volatile(".set\tnoreorder\n"
                             "lbu        $v1, gMenuObjectPoolCount\n"
                             "lw         $s0, gMenuObjectPool\n"
                             "ori        $a0, $zero, 0x1\n"
                             "addiu      $v0, $v1, 0x1\n"
                             "sb         $v0, gMenuObjectPoolCount\n"
                             "sll        $v0, $v1, 3\n"
                             "addu       $v0, $v0, $v1\n"
                             "sll        $v0, $v0, 2\n"
                             "addu       $s0, $s0, $v0\n"
                             "ori        $t4, $zero, 0x2\n"
                             "ori        $t3, $zero, 0x140\n"
                             "sh         $t4, 0x0($s0)\n"
                             "ori        $t4, $zero, 0x4A\n"
                             "sb         $zero, 0x4($s0)\n"
                             "sh         $t3, 0x16($s0)\n"
                             "ori        $t3, $zero, 0x40\n"
                             "sh         $zero, 0x12($s0)\n"
                             "sh         $zero, 0x14($s0)\n"
                             "sw         $zero, 0x1C($s0)\n"
                             "sb         $zero, 0x3($s0)\n"
                             "sb         $zero, 0x2($s0)\n"
                             "sh         $zero, 0x1A($s0)\n"
                             "sh         $zero, 0x6($s0)\n"
                             "sh         $zero, 0xA($s0)\n"
                             "sh         $zero, 0x8($s0)\n"
                             "sh         $zero, 0xC($s0)\n"
                             "sh         $zero, 0xE($s0)\n"
                             "sh         $zero, 0x10($s0)\n"
                             "sh         $t4, 0x18($s0)\n"
                             "sb         $a2, 0x2($s0)\n"
                             "sb         $a2, 0x3($s0)\n"
                             "sb         $t3, 0x4($s0)\n"
                             "jal        GraphicsAllocPolyF4\n"
                             "sw        $a2, 0x68($sp)\n"
                             "addu       $s1, $v0, $zero\n"
                             "addu $a0,$s1,$zero\n"
                             "jal SetPolyF4\n"
                             "sw $s1,0x20($s0)\n"
                             ".set\tnoreorder\n"
                             ".set\treorder\n"
                             : "=r"(node), "=r"(primitive),
                               "=m"(shadeHome.value)
                             : "r"(backgroundShade)
                             : "$2", "$3", "$4", "$11", "$12", "$31", "memory");
                SetSemiTrans(primitive, 1);
                asm volatile(".set\tnoreorder\n"
                             "lw         $a2, 0x68($sp)\n"
                             "addu       $s6, $s0, $zero\n"
                             "ori        $t4, $zero, 0x40\n"
                             "ori        $t3, $zero, 0x140\n"
                             "sb         $t4, 0x6($s1)\n"
                             "ori        $t4, $zero, 0x4A\n"
                             "sh         $t3, 0xC($s1)\n"
                             "sh         $t4, 0x12($s1)\n"
                             "ori        $v0, $zero, 0x3\n"
                             "sh         $zero, 0x8($s1)\n"
                             "sh         $zero, 0xA($s1)\n"
                             "sh         $zero, 0xE($s1)\n"
                             "sh         $zero, 0x10($s1)\n"
                             "sh         $t3, 0x14($s1)\n"
                             "sh         $t4, 0x16($s1)\n"
                             "sb         $a2, 0x4($s1)\n"
                             "sb         $a2, 0x5($s1)\n"
                             ".set\tnoreorder\n"
                             ".set\treorder\n"
                             : "=r"(currentNode), "=r"(backgroundShade),
                               "=r"(packetMode)
                             : "r"(node), "r"(primitive), "m"(shadeHome.value)
                             : "$11", "$12", "memory");
                asm volatile("sh $v0,0x1a($s6)\n"
                             "addiu $v0,$zero,-0xa0\n"
                             "sh $v0,0x12($s6)\n"
                             "addu $v0,$s3,$s2\n"
                             "sll $v0,$v0,2\n"
                             "subu $v0,$v0,$s2\n"
                             "sll $v0,$v0,2\n"
                             "addiu $v0,$v0,3\n"
                             "sh $v0,0x14($s6)\n"
                             ".set\treorder\n"
                             :
                             : "r"(packetMode), "r"(currentNode),
                               "r"(panelNumber), "r"(panelByteOffset)
                             : "$2", "memory");
                asm volatile(".set\tnoreorder\n"
                             "sll $v0,$s7,24\n"
                             "bnez $v0,1f\n"
                             "nop\n"
                             "lui $t3,%%hi(gPadPictureMenuLists)\n"
                             "addiu $t3,$t3,%%lo(gPadPictureMenuLists)\n"
                             "addu $v0,$s3,$t3\n"
                             "j 2f\n"
                             "sw $s6,0($v0)\n"
                             "1: sw $s6,0x1c($s5)\n"
                             "2:\n"
                             ".set\treorder\n"
                             :
                             : "r"(backgroundIndex), "r"(panelByteOffset),
                               "r"(currentNode), "r"(previousNode)
                             : "$2", "$11", "memory");
                asm volatile("addiu $v0,$s7,1\n"
                             "addu $s7,$v0,$zero\n"
                             "sll $v0,$v0,24\n"
                             "sra $v0,$v0,24\n"
                             "slti $v0,$v0,2\n"
                             ".set\treorder\n"
                             : "=r"(backgroundIndex), "=r"(loopCondition)
                             : "0"(backgroundIndex));
                previousNode = currentNode;
            } while (loopCondition != 0);
        }
        {
            s32 borderYBase;
            s32 tone;
            s32 loopCondition;

            asm volatile(".set\tnoreorder\n"
                         "lbu        $t4, 0x20($sp)\n"
                         "addu       $s7, $zero, $zero\n"
                         "ori        $s1, $zero, 0x40\n"
                         "sll        $v1, $t4, 24\n"
                         "sra        $v1, $v1, 24\n"
                         "sll        $v0, $v1, 2\n"
                         "addu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "subu       $v0, $v0, $v1\n"
                         "sll        $s3, $v0, 2\n"
                         ".set\treorder\n"
                         : "=r"(borderIndex), "=r"(tone), "=r"(borderYBase)
                         : "m"(panelIndex.value)
                         : "$2", "$3", "$12");
            do {
                /* Border allocation and placement retain their saved-register path. */
                asm volatile(
                    ".set\tnoreorder\n"
                    "sll        $v0, $s7, 24\n"
                    "sra        $v1, $v0, 24\n"
                    "slti       $v0, $v1, 0x3\n"
                    "beqz       $v0, 1f\n"
                    "ori       $t3, $zero, 0x3\n"
                    "bgtz       $v1, 4f\n"
                    "ori       $t3, $zero, 0x4C\n"
                    "beqz       $v1, 2f\n"
                    "ori       $t4, $zero, 0x142\n"
                    "j          9f\n"
                    "nop\n"
                    "1:\n"
                    "bne        $v1, $t3, 9f\n"
                    "ori       $t4, $zero, 0x142\n"
                    "2:\n"
                    "ori        $t3, $zero, 0x2\n"
                    "addiu      $fp, $zero, -0xA1\n"
                    "sll        $v0, $s7, 24\n"
                    "sw         $t4, 0x28($sp)\n"
                    "bnez       $v0, 3f\n"
                    "sw        $t3, 0x30($sp)\n"
                    "j          9f\n"
                    "addiu     $s4, $s3, 0x1\n"
                    "3:\n"
                    "j          9f\n"
                    "addiu     $s4, $s3, 0x4D\n"
                    "4:\n"
                    "ori        $t4, $zero, 0x2\n"
                    "addiu      $s4, $s3, 0x2\n"
                    "ori        $fp, $zero, 0xA0\n"
                    "sw         $t4, 0x28($sp)\n"
                    "ori        $t4, $zero, 0x1\n"
                    "bne        $v1, $t4, 9f\n"
                    "sw        $t3, 0x30($sp)\n"
                    "addiu      $fp, $zero, -0xA2\n"
                    "9:\n"
                    "lbu        $v1, gMenuObjectPoolCount\n"
                    "lw         $a1, gMenuObjectPool\n"
                    "addiu      $v0, $v1, 0x1\n"
                    "sb         $v0, gMenuObjectPoolCount\n"
                    "sll        $v0, $v1, 3\n"
                    "addu       $v0, $v0, $v1\n"
                    "sll        $v0, $v0, 2\n"
                    "addu       $s2, $a1, $v0\n"
                    "ori        $t3, $zero, 0x2\n"
                    "sh         $zero, 0x12($s2)\n"
                    "sh         $zero, 0x14($s2)\n"
                    "sw         $zero, 0x1C($s2)\n"
                    "sb         $zero, 0x4($s2)\n"
                    "sb         $zero, 0x3($s2)\n"
                    "sb         $zero, 0x2($s2)\n"
                    "sh         $zero, 0x1A($s2)\n"
                    "sh         $t3, 0x0($s2)\n"
                    "sh         $zero, 0x6($s2)\n"
                    "sh         $zero, 0xA($s2)\n"
                    "sh         $zero, 0x8($s2)\n"
                    "sh         $zero, 0xC($s2)\n"
                    "sh         $zero, 0xE($s2)\n"
                    "sh         $zero, 0x10($s2)\n"
                    "lhu        $t4, 0x28($sp)\n"
                    "nop\n"
                    "sh         $t4, 0x16($s2)\n"
                    "lhu        $t3, 0x30($sp)\n"
                    "ori        $a0, $zero, 0x1\n"
                    "sb         $s1, 0x2($s2)\n"
                    "sb         $s1, 0x3($s2)\n"
                    "sb         $s1, 0x4($s2)\n"
                    "jal        GraphicsAllocPolyF4\n"
                    "sh        $t3, 0x18($s2)\n"
                    "addu       $s0, $v0, $zero\n"
                    "addu       $a0, $s0, $zero\n"
                    "jal        SetPolyF4\n"
                    "sw        $s0, 0x20($s2)\n"
                    "addu       $a0, $s0, $zero\n"
                    "jal        SetSemiTrans\n"
                    "addu      $a1, $zero, $zero\n"
                    "sb         $s1, 0x4($s0)\n"
                    "sb         $s1, 0x5($s0)\n"
                    "sb         $s1, 0x6($s0)\n"
                    "sh         $zero, 0x8($s0)\n"
                    "sh         $zero, 0xA($s0)\n"
                    "lhu        $v1, 0x28($sp)\n"
                    "sh         $zero, 0xE($s0)\n"
                    "sh         $zero, 0x10($s0)\n"
                    "sh         $v1, 0xC($s0)\n"
                    "lhu        $v0, 0x30($sp)\n"
                    "addu       $s6, $s2, $zero\n"
                    "sh         $v1, 0x14($s0)\n"
                    "sh         $v0, 0x12($s0)\n"
                    "sh         $v0, 0x16($s0)\n"
                    "ori        $t4, $zero, 0x3\n"
                    "sh         $t4, 0x1A($s6)\n"
                    "sh $fp,0x12($s6)\n"
                    "sh $s4,0x14($s6)\n"
                    "sw $s6,0x1c($s5)\n"
                    ".set\treorder\n"
                    : "=r"(currentNode), "=m"(packetWidth.value),
                      "=m"(packetHeight.value), "=r"(panelState)
                    : "r"(borderIndex), "r"(borderYBase), "r"(tone),
                      "r"(previousNode)
                    /* These three verified leaf callees preserve the other GPRs and HI/LO. */
                    : "$2", "$3", "$4", "$5", "$11", "$12", "$16", "$20", "$30",
                      "$31", "memory");
                asm volatile("addiu $v0,$s7,1\n"
                             "addu $s7,$v0,$zero\n"
                             "sll $v0,$v0,24\n"
                             "sra $v0,$v0,24\n"
                             "slti $v0,$v0,4\n"
                             ".set\treorder\n"
                             : "=r"(borderIndex), "=r"(loopCondition)
                             : "0"(borderIndex)
                             : "memory");
                previousNode = currentNode;
            } while (loopCondition != 0);
        }
        {
            s32 textWord;
            /* Header texture and two black quads share allocation registers. */
            asm volatile(".set\tnoreorder\n"
                         "ori        $a1, $zero, 0x74\n"
                         "lbu        $v1, gMenuObjectPoolCount\n"
                         "lw         $s1, gMenuObjectPool\n"
                         "ori        $a0, $zero, 0x1\n"
                         "addiu      $v0, $v1, 0x1\n"
                         "sb         $v0, gMenuObjectPoolCount\n"
                         "sll        $v0, $v1, 3\n"
                         "addu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $s1, $s1, $v0\n"
                         "ori        $t3, $zero, 0x1\n"
                         "ori        $v0, $zero, 0x50\n"
                         "sh         $zero, 0x12($s1)\n"
                         "sh         $zero, 0x14($s1)\n"
                         "sw         $zero, 0x1C($s1)\n"
                         "sb         $zero, 0x4($s1)\n"
                         "sb         $zero, 0x3($s1)\n"
                         "sb         $zero, 0x2($s1)\n"
                         "sh         $zero, 0x1A($s1)\n"
                         "sh         $t3, 0x0($s1)\n"
                         "sh         $zero, 0xA($s1)\n"
                         "sh         $zero, 0x6($s1)\n"
                         "sh         $zero, 0xC($s1)\n"
                         "sh         $zero, 0x8($s1)\n"
                         "sh         $a1, 0x16($s1)\n"
                         "sh         $v0, 0x18($s1)\n"
                         "sh         $zero, 0xE($s1)\n"
                         "jal        GraphicsAllocPolyFT4\n"
                         "sh        $zero, 0x10($s1)\n"
                         "addu       $s0, $v0, $zero\n"
                         "jal        SetPolyFT4\n"
                         "addu      $a0, $s0, $zero\n"
                         "addu       $a0, $s0, $zero\n"
                         "jal        SetShadeTex\n"
                         "addu      $a1, $zero, $zero\n"
                         "addu       $a0, $s0, $zero\n"
                         "addu       $a1, $zero, $zero\n"
                         "ori        $v0, $zero, 0x80\n"
                         "sb         $v0, 0x4($s0)\n"
                         "sb         $v0, 0x5($s0)\n"
                         "jal        SetSemiTrans\n"
                         "sb        $v0, 0x6($s0)\n"
                         "addu       $s6, $s1, $zero\n"
                         "ori        $t4, $zero, 0x2\n"
                         "addiu      $v0, $zero, -0x3A\n"
                         "sw         $s0, 0x20($s1)\n"
                         "sh         $t4, 0x1A($s1)\n"
                         "sh         $v0, 0x12($s6)\n"
                         "lbu        $t3, %6\n"
                         "lbu        $v1, gMenuObjectPoolCount\n"
                         "sll        $s5, $t3, 24\n"
                         "sra        $s5, $s5, 24\n"
                         "sll        $v0, $s5, 2\n"
                         "addu       $s4, $v0, $s5\n"
                         "sll        $s4, $s4, 2\n"
                         "subu       $s4, $s4, $s5\n"
                         "sll        $s4, $s4, 2\n"
                         "sh         $s4, 0x14($s6)\n"
                         "sw         $s6, 0x1C($s2)\n"
                         "lw         $s2, gMenuObjectPool\n"
                         "ori        $a0, $zero, 0x1\n"
                         "ori        $s3, $zero, 0x4\n"
                         "lui        $at, %%hi(D_800A3A1C)\n"
                         "addu       $at, $at, $v0\n"
                         "sw         $s6, %%lo(D_800A3A1C)($at)\n"
                         "addiu      $v0, $v1, 0x1\n"
                         "sb         $v0, gMenuObjectPoolCount\n"
                         "sll        $v0, $v1, 3\n"
                         "addu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $s2, $s2, $v0\n"
                         "ori        $t3, $zero, 0x1\n"
                         "sh         $zero, 0x12($s2)\n"
                         "sh         $zero, 0x14($s2)\n"
                         "sw         $zero, 0x1C($s2)\n"
                         "sb         $zero, 0x4($s2)\n"
                         "sb         $zero, 0x3($s2)\n"
                         "sb         $zero, 0x2($s2)\n"
                         "sh         $zero, 0x1A($s2)\n"
                         "sh         $t4, 0x0($s2)\n"
                         "sh         $zero, 0x6($s2)\n"
                         "sh         $zero, 0xA($s2)\n"
                         "sh         $zero, 0x8($s2)\n"
                         "sh         $zero, 0xC($s2)\n"
                         "sh         $zero, 0xE($s2)\n"
                         "sh         $zero, 0x10($s2)\n"
                         "sh         $s3, 0x16($s2)\n"
                         "sh         $t3, 0x18($s2)\n"
                         "sb         $zero, 0x2($s2)\n"
                         "sb         $zero, 0x3($s2)\n"
                         "jal        GraphicsAllocPolyF4\n"
                         "sb        $zero, 0x4($s2)\n"
                         "addu       $s0, $v0, $zero\n"
                         "addu       $a0, $s0, $zero\n"
                         "jal        SetPolyF4\n"
                         "sw        $s0, 0x20($s2)\n"
                         "addu       $a0, $s0, $zero\n"
                         "jal        SetSemiTrans\n"
                         "ori       $a1, $zero, 0x1\n"
                         "sb         $zero, 0x4($s0)\n"
                         "sb         $zero, 0x5($s0)\n"
                         "sb         $zero, 0x6($s0)\n"
                         "lbu        $v1, gMenuObjectPoolCount\n"
                         "addu       $s7, $zero, $zero\n"
                         "addu       $s6, $s2, $zero\n"
                         "ori        $t4, $zero, 0x1\n"
                         "ori        $t3, $zero, 0x1\n"
                         "sh         $zero, 0x8($s0)\n"
                         "sh         $zero, 0xA($s0)\n"
                         "sh         $s3, 0xC($s0)\n"
                         "sh         $zero, 0xE($s0)\n"
                         "sh         $zero, 0x10($s0)\n"
                         "sh         $t4, 0x12($s0)\n"
                         "sh         $s3, 0x14($s0)\n"
                         "sh         $t3, 0x16($s0)\n"
                         "lw         $s0, gMenuObjectPool\n"
                         "ori        $a0, $zero, 0x1\n"
                         "addiu      $v0, $zero, -0x2\n"
                         "sh         $v0, 0x12($s6)\n"
                         "addiu      $v0, $s4, 0x35\n"
                         "sh         $t4, 0x1A($s6)\n"
                         "sh         $v0, 0x14($s6)\n"
                         "sw         $s6, 0x1C($s1)\n"
                         "addiu      $v0, $v1, 0x1\n"
                         "sb         $v0, gMenuObjectPoolCount\n"
                         "sll        $v0, $v1, 3\n"
                         "addu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $s0, $s0, $v0\n"
                         "ori        $t3, $zero, 0x2\n"
                         "ori        $t4, $zero, 0x140\n"
                         "sh         $zero, 0x12($s0)\n"
                         "sh         $zero, 0x14($s0)\n"
                         "sw         $zero, 0x1C($s0)\n"
                         "sb         $zero, 0x4($s0)\n"
                         "sb         $zero, 0x3($s0)\n"
                         "sb         $zero, 0x2($s0)\n"
                         "sh         $zero, 0x1A($s0)\n"
                         "sh         $t3, 0x0($s0)\n"
                         "sh         $zero, 0x6($s0)\n"
                         "sh         $zero, 0xA($s0)\n"
                         "sh         $zero, 0x8($s0)\n"
                         "sh         $zero, 0xC($s0)\n"
                         "sh         $zero, 0xE($s0)\n"
                         "sh         $zero, 0x10($s0)\n"
                         "ori        $t3, $zero, 0x4A\n"
                         "sh         $t4, 0x16($s0)\n"
                         "sh         $t3, 0x18($s0)\n"
                         "sb         $zero, 0x2($s0)\n"
                         "sb         $zero, 0x3($s0)\n"
                         "jal        GraphicsAllocPolyF4\n"
                         "sb        $zero, 0x4($s0)\n"
                         "addu       $s1, $v0, $zero\n"
                         "addu       $a0, $s1, $zero\n"
                         "jal        SetPolyF4\n"
                         "sw        $s1, 0x20($s0)\n"
                         "addu       $a0, $s1, $zero\n"
                         "jal        SetSemiTrans\n"
                         "ori       $a1, $zero, 0x1\n"
                         "addu       $s6, $s0, $zero\n"
                         "ori        $a0, $zero, 0x2\n"
                         "ori        $a1, $zero, 0x2\n"
                         "ori        $t4, $zero, 0x140\n"
                         "ori        $t3, $zero, 0x4A\n"
                         "sh         $t4, 0xC($s1)\n"
                         "sh         $t3, 0x12($s1)\n"
                         "addiu      $v0, $zero, -0xA0\n"
                         "addiu      $s4, $s4, 0x3\n"
                         "sb         $zero, 0x4($s1)\n"
                         "sb         $zero, 0x5($s1)\n"
                         "sb         $zero, 0x6($s1)\n"
                         "sh         $zero, 0x8($s1)\n"
                         "sh         $zero, 0xA($s1)\n"
                         "sh         $zero, 0xE($s1)\n"
                         "sh         $zero, 0x10($s1)\n"
                         "sh         $t4, 0x14($s1)\n"
                         "sh         $t3, 0x16($s1)\n"
                         "sh         $zero, 0x1A($s6)\n"
                         "sh         $v0, 0x12($s6)\n"
                         "sh         $s4, 0x14($s6)\n"
                         "jal        MenuFontSet\n"
                         "sw        $s6, 0x1C($s2)\n"
                         "lui        $a1, %%hi(D_8009A314)\n"
                         "lw         $a1, %%lo(D_8009A314)($a1)\n"
                         "addu       $s2, $s5, $zero\n"
                         "addu       $s5, $s6, $zero\n"
                         ".set\treorder\n"
                         : "=r"(currentNode), "=r"(previousNode),
                           "=r"(panelState), "=r"(textIndex), "=r"(textWord)
                         : "2"(panelState), "m"(panelIndex.value)
                         : "$2", "$3", "$4", "$11", "$12", "$16", "$17", "$19",
                           "$20", "$31", "memory");
            textCenterX = MenuTextCenterOffset(0x140, textWord) - 0xA0;
        }
        asm volatile("" : "=r"(textCenterX) : "0"(textCenterX));
        textLeftX = textCenterX - 5;
    loopC:
        {
            MenuText *cell;
            /* Text object and cell pools must be loaded independently. */
            asm volatile(".set\tnoreorder\n"
                         "lbu        $a0, gMenuObjectPoolCount\n"
                         "lw         $v1, gMenuObjectPool\n"
                         "addiu      $v0, $a0, 0x1\n"
                         "sb         $v0, gMenuObjectPoolCount\n"
                         "sll        $v0, $a0, 3\n"
                         "addu       $v0, $v0, $a0\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $v1, $v1, $v0\n"
                         "sb         $zero, 0x4($v1)\n"
                         "sb         $zero, 0x3($v1)\n"
                         "sb         $zero, 0x2($v1)\n"
                         "lbu        $a0, D_800A37BC\n"
                         "addu       $s6, $v1, $zero\n"
                         "lw         $v1, D_800A3654\n"
                         "sh         $zero, 0x12($s6)\n"
                         "sh         $zero, 0x14($s6)\n"
                         "sw         $zero, 0x1C($s6)\n"
                         "sh         $zero, 0x1A($s6)\n"
                         "sh         $zero, 0x0($s6)\n"
                         "sh         $zero, 0xA($s6)\n"
                         "sh         $zero, 0x6($s6)\n"
                         "sh         $zero, 0xC($s6)\n"
                         "sh         $zero, 0x8($s6)\n"
                         "sh         $zero, 0xE($s6)\n"
                         "sh         $zero, 0x10($s6)\n"
                         "sh         $zero, 0x1A($s6)\n"
                         "addiu      $v0, $a0, 0x1\n"
                         "sb         $v0, D_800A37BC\n"
                         "sll        $v0, $a0, 1\n"
                         "addu       $v0, $v0, $a0\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $v1, $v1, $v0\n"
                         "sw         $v1, 0x20($s6)\n"
                         "sb         $zero, 0x0($v1)\n"
                         "sb         $zero, 0x3($v1)\n"
                         "sw         $zero, 0x4($v1)\n"
                         "lw         $s0, 0x20($s6)\n"
                         "ori        $t4, $zero, 0x1\n"
                         "sll        $v0, $s2, 2\n"
                         "addu       $v0, $v0, $s2\n"
                         "sll        $v0, $v0, 2\n"
                         "subu       $v0, $v0, $s2\n"
                         "sll        $v0, $v0, 2\n"
                         "addiu      $v0, $v0, 0x5\n"
                         "sh         $v0, 0x14($s6)\n"
                         "ori        $v0, $zero, 0x2\n"
                         "sh         $t4, 0x1A($s6)\n"
                         "sh         $s3, 0x12($s6)\n"
                         "sb         $v0, 0x2($s0)\n"
                         "sb         $v0, 0x1($s0)\n"
                         ".set\treorder\n"
                         : "=r"(currentNode), "=r"(cell)
                         : "r"(panelState), "r"(textLeftX)
                         : "$2", "$3", "$4", "$12", "memory");
            /* Each text arm retains its own word store and call delay. */
            asm volatile(".set\tnoreorder\n"
                         "sll        $v0, $s7, 24\n"
                         "beqz       $v0, 1f\n"
                         "sb        $zero, 0x3($s0)\n"
                         "lui        $a0, %%hi(D_8009A314)\n"
                         "lw         $a0, %%lo(D_8009A314)($a0)\n"
                         "jal        MenuStringWidth\n"
                         "nop\n"
                         "addu       $v0, $v0, $s1\n"
                         "sh         $v0, 0x12($s6)\n"
                         "ori        $v0, $zero, 0x5\n"
                         "sh         $v0, 0x0($s6)\n"
                         "ori        $t3, $zero, 0x1\n"
                         "j          2f\n"
                         "sw        $t3, 0x8($s0)\n"
                         "1:\n"
                         "sh         $s3, 0x12($s6)\n"
                         "lui        $v0, %%hi(D_8009A314)\n"
                         "lw         $v0, %%lo(D_8009A314)($v0)\n"
                         "nop\n"
                         "sw         $v0, 0x8($s0)\n"
                         "2:\n"
                         "sw         $s6, 0x1C($s5)\n"
                         ".set\treorder\n"
                         : "=x"(callAccumulator)
                         : "r"(textIndex), "r"(cell), "r"(currentNode),
                           "r"(textCenterX), "r"(textLeftX), "r"(previousNode)
                         : "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9",
                           "$10", "$11", "$31", "memory");
            {
                s32 loopCondition;
                textIndex++;
                loopCondition = (s8)textIndex < 2;
                previousNode = currentNode;
                if (loopCondition != 0) {
                    goto loopC;
                }
            }
        }

        {
            s32 rowPanelIndex;
            s32 panelTimes20;
            s32 rowX;
            s32 rowY;
            s32 rowMode;
            s32 rowAlign;
            s32 rowCondition;
            s32 sideCondition;
            /* The copied row list starts at the verified local home sp+0x18. */
            asm volatile(".set\tnoreorder\n"
                         "lbu        $t4, %3\n"
                         "addu       $s7, $zero, $zero\n"
                         "sll        $v0, $t4, 24\n"
                         "sra        $a1, $v0, 24\n"
                         "sll        $v0, $a1, 2\n"
                         "addu       $v0, $v0, $a1\n"
                         "sll        $t2, $v0, 2\n"
                         ".set\treorder\n"
                         : "=r"(rowSide), "=r"(rowPanelIndex),
                           "=r"(panelTimes20)
                         : "m"(panelIndex.value)
                         : "$2", "$12");
            do {
                asm volatile(".set\tnoreorder\n"
                             "addu       $s2, $zero, $zero\n"
                             "sll        $a0, $s7, 24\n"
                             "sra        $a0, $a0, 24\n"
                             "sll        $v0, $a0, 1\n"
                             "addiu      $v0, $v0, -0x1\n"
                             "sll        $v1, $v0, 6\n"
                             "subu       $t1, $v1, $v0\n"
                             "subu       $v0, $t2, $a1\n"
                             "sll        $t0, $v0, 2\n"
                             "ori        $a2, $zero, 0x2\n"
                             "sltiu      $a0, $a0, 0x1\n"
                             "addu       $a3, $a0, $zero\n"
                             ".set\treorder\n"
                             : "=r"(rowItem), "=r"(rowX), "=r"(rowY),
                               "=r"(rowMode), "=r"(rowAlign)
                             : "r"(rowSide), "r"(rowPanelIndex),
                               "r"(panelTimes20)
                             : "$2", "$3", "$4");
                do {
                    /* Allocate one text cell, place it, then test the row counter. */
                    asm volatile(
                        ".set\tnoreorder\n"
                        "lbu        $a0, gMenuObjectPoolCount\n"
                        "lw         $v1, gMenuObjectPool\n"
                        "addiu      $v0, $a0, 0x1\n"
                        "sb         $v0, gMenuObjectPoolCount\n"
                        "sll        $v0, $a0, 3\n"
                        "addu       $v0, $v0, $a0\n"
                        "sll        $v0, $v0, 2\n"
                        "addu       $v1, $v1, $v0\n"
                        "sb         $zero, 0x4($v1)\n"
                        "sb         $zero, 0x3($v1)\n"
                        "sb         $zero, 0x2($v1)\n"
                        "lbu        $a0, D_800A37BC\n"
                        "addu       $s6, $v1, $zero\n"
                        "lw         $v1, D_800A3654\n"
                        "sh         $zero, 0x12($s6)\n"
                        "sh         $zero, 0x14($s6)\n"
                        "sw         $zero, 0x1C($s6)\n"
                        "sh         $zero, 0x1A($s6)\n"
                        "sh         $zero, 0x0($s6)\n"
                        "sh         $zero, 0xA($s6)\n"
                        "sh         $zero, 0x6($s6)\n"
                        "sh         $zero, 0xC($s6)\n"
                        "sh         $zero, 0x8($s6)\n"
                        "sh         $zero, 0xE($s6)\n"
                        "sh         $zero, 0x10($s6)\n"
                        "sh         $zero, 0x1A($s6)\n"
                        "addiu      $v0, $a0, 0x1\n"
                        "sb         $v0, D_800A37BC\n"
                        "sll        $v0, $a0, 1\n"
                        "addu       $v0, $v0, $a0\n"
                        "sll        $v0, $v0, 2\n"
                        "addu       $v1, $v1, $v0\n"
                        "sw         $v1, 0x20($s6)\n"
                        "sb         $zero, 0x0($v1)\n"
                        "sb         $zero, 0x3($v1)\n"
                        "sw         $zero, 0x4($v1)\n"
                        "ori        $t3, $zero, 0x1\n"
                        "sll        $v0, $s2, 24\n"
                        "sra        $v0, $v0, 24\n"
                        "addu       $v0, $sp, $v0\n"
                        "sh         $t3, 0x1A($s6)\n"
                        "sh         $t1, 0x12($s6)\n"
                        "lbu        $v0, 0x18($v0)\n"
                        "addiu      $v1, $s2, 0x1\n"
                        "addu       $s2, $v1, $zero\n"
                        "lw         $s0, 0x20($s6)\n"
                        "sll        $v1, $v1, 24\n"
                        "sra        $v1, $v1, 24\n"
                        "slti       $v1, $v1, 0x7\n"
                        "sll        $v0, $v0, 24\n"
                        "sra        $v0, $v0, 24\n"
                        "addu       $v0, $v0, $t0\n"
                        "sh         $v0, 0x14($s6)\n"
                        "sb         $a2, 0x2($s0)\n"
                        "sb         $a3, 0x3($s0)\n"
                        "sb         $a2, 0x1($s0)\n"
                        "sw         $s6, 0x1C($s5)\n"
                        ".set\treorder\n"
                        : "=r"(currentNode), "=r"(rowItem), "=r"(rowCondition)
                        : "1"(rowItem), "r"(rowX), "r"(rowY), "r"(rowMode),
                          "r"(rowAlign), "r"(previousNode), "m"(rowList)
                        : "$2", "$4", "$11", "$16", "memory");
                    previousNode = currentNode;
                } while (rowCondition != 0);
                asm volatile(".set\tnoreorder\n"
                             "addiu      $v0, $s7, 0x1\n"
                             "addu       $s7, $v0, $zero\n"
                             "sll        $v0, $v0, 24\n"
                             "sra        $v0, $v0, 24\n"
                             "slti       $v0, $v0, 0x2\n"
                             ".set\treorder\n"
                             : "=r"(rowSide), "=r"(sideCondition)
                             : "0"(rowSide));
            } while (sideCondition != 0);
        }
        {
            /* Set the animation fields while walking the panel's node chain. */
            asm volatile(".set\tnoreorder\n"
                         "lbu        $t4, %2\n"
                         "lui        $t3, %%hi(gPadPictureMenuLists)\n"
                         "addiu      $t3, $t3, %%lo(gPadPictureMenuLists)\n"
                         "sll        $v0, $t4, 24\n"
                         "sra        $a0, $v0, 24\n"
                         "sll        $v1, $a0, 2\n"
                         "addu       $v0, $v1, $t3\n"
                         "lw         $s5, 0x0($v0)\n"
                         "ori        $t4, $zero, 0x2\n"
                         "beqz       $s5, 2f\n"
                         "subu      $a1, $t4, $v1\n"
                         "addu       $v0, $v1, $a0\n"
                         "sll        $a3, $v0, 6\n"
                         "sll        $v0, $a0, 1\n"
                         "addiu      $a2, $v0, -0x1\n"
                         "sll        $a0, $a1, 24\n"
                         "ori        $a1, $zero, 0xA0\n"
                         "1:\n"
                         "lh         $v0, 0x12($s5)\n"
                         "nop\n"
                         "addiu      $v0, $v0, 0xA2\n"
                         "mult       $a2, $v0\n"
                         "lw         $t3, %3\n"
                         "ori        $t4, $zero, 0x1\n"
                         "sb         $t4, 0x5($s5)\n"
                         "sh         $a1, 0xA($s5)\n"
                         "sra        $v1, $t3, 24\n"
                         "sra        $v0, $a0, 24\n"
                         "sh         $v1, 0x8($s5)\n"
                         "sh         $v0, 0xE($s5)\n"
                         "sh         $v1, 0xC($s5)\n"
                         "mflo       $t3\n"
                         "addu       $v0, $a3, $t3\n"
                         "sh         $v0, 0x6($s5)\n"
                         "lw         $s5, 0x1C($s5)\n"
                         "nop\n"
                         "bnez       $s5, 1b\n"
                         "nop\n"
                         "2:\n"
                         ".set\treorder\n"
                         : "=r"(previousNode), "=x"(callAccumulator)
                         : "m"(panelIndex.value), "m"(colorHome.value)
                         : "$2", "$3", "$4", "$5", "$6", "$7", "$11", "$12",
                           "memory");
        }
    walkDone:
        {
            register s32 textureOffset asm("$20");
            textureOffset = 0;
            MenuUpdatePadPicture((u8)panelIndex.value);
            /* Keep the texture cases, leaf calls, UV reloads, and links. */
            asm volatile(".set\tnoreorder\n"
                         "lw         $t4, %7\n"
                         "lbu        $t3, %8\n"
                         "addu       $s7, $zero, $zero\n"
                         "sra        $fp, $t4, 24\n"
                         "sll        $v0, $t3, 24\n"
                         "sra        $v0, $v0, 24\n"
                         "sll        $s3, $v0, 2\n"
                         "sw         $v0, %4\n"
                         ".LtextureStage80061A8C:\n"
                         "sll        $v0, $s7, 24\n"
                         "sra        $v1, $v0, 24\n"
                         "ori        $t4, $zero, 0x1\n"
                         "beq        $v1, $t4, .LtextureStage80061AD8\n"
                         "slti      $v0, $v1, 0x2\n"
                         "beqz       $v0, .LtextureStage80061AB8\n"
                         "nop\n"
                         "beqz       $v1, .LtextureStage80061ACC\n"
                         "ori       $t4, $zero, 0x2\n"
                         "j          .LtextureStage80061AF0\n"
                         "nop\n"
                         ".LtextureStage80061AB8:\n"
                         "ori        $t3, $zero, 0x2\n"
                         "beq        $v1, $t3, .LtextureStage80061AE8\n"
                         "ori       $t4, $zero, 0x3\n"
                         "j          .LtextureStage80061AF0\n"
                         "nop\n"
                         ".LtextureStage80061ACC:\n"
                         "sw         $t4, %2\n"
                         "j          .LtextureStage80061AF0\n"
                         "sw        $zero, %3\n"
                         ".LtextureStage80061AD8:\n"
                         "ori        $t3, $zero, 0x6\n"
                         "ori        $t4, $zero, 0x1\n"
                         "j          .LtextureStage80061AEC\n"
                         "sw        $t3, %2\n"
                         ".LtextureStage80061AE8:\n"
                         "sw         $t3, %2\n"
                         ".LtextureStage80061AEC:\n"
                         "sw         $t4, %3\n"
                         ".LtextureStage80061AF0:\n"
                         "lbu        $v1, gMenuObjectPoolCount\n"
                         "lw         $s0, gMenuObjectPool\n"
                         "addiu      $v0, $v1, 0x1\n"
                         "sb         $v0, gMenuObjectPoolCount\n"
                         "sll        $v0, $v1, 3\n"
                         "addu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $s0, $s0, $v0\n"
                         "ori        $t3, $zero, 0x1\n"
                         "ori        $t4, $zero, 0x68\n"
                         "sh         $zero, 0x12($s0)\n"
                         "sh         $zero, 0x14($s0)\n"
                         "sw         $zero, 0x1C($s0)\n"
                         "sb         $zero, 0x4($s0)\n"
                         "sb         $zero, 0x3($s0)\n"
                         "sb         $zero, 0x2($s0)\n"
                         "sh         $zero, 0x1A($s0)\n"
                         "sh         $t3, 0x0($s0)\n"
                         "sh         $zero, 0xA($s0)\n"
                         "sh         $zero, 0x6($s0)\n"
                         "sh         $fp, 0xC($s0)\n"
                         "sh         $fp, 0x8($s0)\n"
                         "sh         $t4, 0x16($s0)\n"
                         "lhu        $t3, %2\n"
                         "ori        $a0, $zero, 0x1\n"
                         "sh         $zero, 0xE($s0)\n"
                         "sh         $zero, 0x10($s0)\n"
                         "jal        GraphicsAllocPolyFT4\n"
                         "sh        $t3, 0x18($s0)\n"
                         "addu       $s1, $v0, $zero\n"
                         "jal        SetPolyFT4\n"
                         "addu      $a0, $s1, $zero\n"
                         "addu       $a0, $s1, $zero\n"
                         "jal        SetShadeTex\n"
                         "addu      $a1, $zero, $zero\n"
                         "addu       $a0, $s1, $zero\n"
                         "addu       $a1, $zero, $zero\n"
                         "ori        $v0, $zero, 0x80\n"
                         "sb         $v0, 0x4($s1)\n"
                         "sb         $v0, 0x5($s1)\n"
                         "jal        SetSemiTrans\n"
                         "sb        $v0, 0x6($s1)\n"
                         "addu       $s6, $s0, $zero\n"
                         "ori        $t4, $zero, 0x2\n"
                         "sll        $v0, $s7, 24\n"
                         "sw         $s1, 0x20($s6)\n"
                         "bnez       $v0, .LtextureStage80061BC4\n"
                         "sh        $t4, 0x1A($s6)\n"
                         "lui        $at, %%hi(D_800A3888)\n"
                         "addu       $at, $at, $s3\n"
                         "sw         $s6, %%lo(D_800A3888)($at)\n"
                         "j          .LtextureStage80061BC8\n"
                         "nop\n"
                         ".LtextureStage80061BC4:\n"
                         "sw         $s6, 0x1C($s5)\n"
                         ".LtextureStage80061BC8:\n"
                         "lw         $t3, %4\n"
                         "nop\n"
                         "beqz       $t3, .LtextureStage80061BE0\n"
                         "ori       $t4, $zero, 0x140\n"
                         "j          .LtextureStage80061BE8\n"
                         "sh        $t4, 0x6($s6)\n"
                         ".LtextureStage80061BE0:\n"
                         "addiu      $v0, $zero, -0x140\n"
                         "sh         $v0, 0x6($s6)\n"
                         ".LtextureStage80061BE8:\n"
                         "lui        $t3, %%hi(gPadPictureMenuLists)\n"
                         "addiu      $t3, $t3, %%lo(gPadPictureMenuLists)\n"
                         "addu       $v0, $s3, $t3\n"
                         "lw         $v0, 0x0($v0)\n"
                         "lw         $s2, 0x20($s6)\n"
                         "lhu        $v1, 0x14($v0)\n"
                         "ori        $t4, $zero, 0x1\n"
                         "ori        $v0, $zero, 0x78\n"
                         "sh         $v0, 0x12($s6)\n"
                         "addiu      $v0, %6, 0x3A\n"
                         "addu       $v1, $v1, $v0\n"
                         "sll        $v0, $s7, 24\n"
                         "sra        $v0, $v0, 24\n"
                         "bne        $v0, $t4, .LtextureStage80061D0C\n"
                         "sh        $v1, 0x14($s6)\n"
                         "lui        $a0, %%hi(D_8009AEA4)\n"
                         "lhu        $a0, %%lo(D_8009AEA4)($a0)\n"
                         "lui        $a1, %%hi(D_8009AEA6)\n"
                         "lhu        $a1, %%lo(D_8009AEA6)($a1)\n"
                         "lhu        $s0, 0x16($s6)\n"
                         "jal        GetClut\n"
                         "nop\n"
                         "sh         $v0, 0xE($s2)\n"
                         "lui        $a0, %%hi(D_8009AEAC)\n"
                         "lhu        $a0, %%lo(D_8009AEAC)($a0)\n"
                         "lui        $a2, %%hi(D_8009AEA0)\n"
                         "lhu        $a2, %%lo(D_8009AEA0)($a2)\n"
                         "lui        $a3, %%hi(D_8009AEA2)\n"
                         "lhu        $a3, %%lo(D_8009AEA2)($a3)\n"
                         "jal        GetTPage\n"
                         "ori       $a1, $zero, 0x3\n"
                         "sh         $v0, 0x16($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "sb         $v0, 0xC($s2)\n"
                         "lhu        $v1, %3\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "sb         $v0, 0xD($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $s0\n"
                         "sb         $v0, 0x14($s2)\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "sb         $v0, 0x15($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "sb         $v0, 0x1C($s2)\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "addiu      $v0, $v0, 0x1\n"
                         "sb         $v0, 0x1D($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $s0\n"
                         "sb         $v0, 0x24($s2)\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "j          .LtextureStage80061DF4\n"
                         "addiu     $v0, $v0, 0x1\n"
                         ".LtextureStage80061D0C:\n"
                         "lui        $a0, %%hi(D_8009AEA4)\n"
                         "lhu        $a0, %%lo(D_8009AEA4)($a0)\n"
                         "lui        $a1, %%hi(D_8009AEA6)\n"
                         "lhu        $a1, %%lo(D_8009AEA6)($a1)\n"
                         "lhu        $s0, 0x16($s6)\n"
                         "lhu        $s1, 0x18($s6)\n"
                         "jal        GetClut\n"
                         "nop\n"
                         "sh         $v0, 0xE($s2)\n"
                         "lui        $a0, %%hi(D_8009AEAC)\n"
                         "lhu        $a0, %%lo(D_8009AEAC)($a0)\n"
                         "lui        $a2, %%hi(D_8009AEA0)\n"
                         "lhu        $a2, %%lo(D_8009AEA0)($a2)\n"
                         "lui        $a3, %%hi(D_8009AEA2)\n"
                         "lhu        $a3, %%lo(D_8009AEA2)($a3)\n"
                         "jal        GetTPage\n"
                         "ori       $a1, $zero, 0x3\n"
                         "sh         $v0, 0x16($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "sb         $v0, 0xC($s2)\n"
                         "lhu        $v1, %3\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "sb         $v0, 0xD($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $s0\n"
                         "sb         $v0, 0x14($s2)\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "sb         $v0, 0x15($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "sb         $v0, 0x1C($s2)\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "addu       $v0, $v0, $s1\n"
                         "sb         $v0, 0x1D($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $s0\n"
                         "sb         $v0, 0x24($s2)\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "addu       $v0, $v0, $s1\n"
                         ".LtextureStage80061DF4:\n"
                         "sb         $v0, 0x25($s2)\n"
                         "lh         $v1, 0x18($s6)\n"
                         "addu       $s5, $s6, $zero\n"
                         "addiu      $v0, $s7, 0x1\n"
                         "addu       $s7, $v0, $zero\n"
                         "sll        $v0, $v0, 24\n"
                         "sra        $v0, $v0, 24\n"
                         "slti       $v0, $v0, 0x3\n"
                         "bnez       $v0, .LtextureStage80061A8C\n"
                         "addu      %6, %6, $v1\n"
                         "lw         $t3, %7\n"
                         "lbu        $t4, %8\n"
                         "addu       $s7, $zero, $zero\n"
                         "lui        $s3, %%hi(D_8009AEB2)\n"
                         "addiu      $s3, $s3, %%lo(D_8009AEB2)\n"
                         "sra        %6, $t3, 24\n"
                         "sll        $v0, $t4, 24\n"
                         "sra        $fp, $v0, 24\n"
                         "sll        $t3, $fp, 2\n"
                         "sw         $t3, %5\n"
                         ".LtextureStage80061E44:\n"
                         "lbu        $v1, gMenuObjectPoolCount\n"
                         "lw         $s0, gMenuObjectPool\n"
                         "ori        $a0, $zero, 0x1\n"
                         "addiu      $v0, $v1, 0x1\n"
                         "sb         $v0, gMenuObjectPoolCount\n"
                         "sll        $v0, $v1, 3\n"
                         "addu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $s0, $s0, $v0\n"
                         "ori        $t4, $zero, 0x1\n"
                         "ori        $t3, $zero, 0xE\n"
                         "sh         $t4, 0x0($s0)\n"
                         "ori        $t4, $zero, 0x32\n"
                         "sh         $zero, 0x12($s0)\n"
                         "sh         $zero, 0x14($s0)\n"
                         "sw         $zero, 0x1C($s0)\n"
                         "sb         $zero, 0x4($s0)\n"
                         "sb         $zero, 0x3($s0)\n"
                         "sb         $zero, 0x2($s0)\n"
                         "sh         $zero, 0x1A($s0)\n"
                         "sh         $zero, 0xA($s0)\n"
                         "sh         $zero, 0x6($s0)\n"
                         "sh         %6, 0xC($s0)\n"
                         "sh         %6, 0x8($s0)\n"
                         "sh         $t3, 0x16($s0)\n"
                         "sh         $t4, 0x18($s0)\n"
                         "sh         $zero, 0xE($s0)\n"
                         "jal        GraphicsAllocPolyFT4\n"
                         "sh        $zero, 0x10($s0)\n"
                         "addu       $s1, $v0, $zero\n"
                         "jal        SetPolyFT4\n"
                         "addu      $a0, $s1, $zero\n"
                         "addu       $a0, $s1, $zero\n"
                         "jal        SetShadeTex\n"
                         "addu      $a1, $zero, $zero\n"
                         "addu       $a0, $s1, $zero\n"
                         "addu       $a1, $zero, $zero\n"
                         "ori        $v0, $zero, 0x80\n"
                         "sb         $v0, 0x4($s1)\n"
                         "sb         $v0, 0x5($s1)\n"
                         "jal        SetSemiTrans\n"
                         "sb        $v0, 0x6($s1)\n"
                         "addu       $s6, $s0, $zero\n"
                         "ori        $t3, $zero, 0x2\n"
                         "sw         $s1, 0x20($s6)\n"
                         "beqz       $fp, .LtextureStage80061F0C\n"
                         "sh        $t3, 0x1A($s6)\n"
                         "ori        $t4, $zero, 0x140\n"
                         "j          .LtextureStage80061F14\n"
                         "sh        $t4, 0x6($s6)\n"
                         ".LtextureStage80061F0C:\n"
                         "addiu      $v0, $zero, -0x140\n"
                         "sh         $v0, 0x6($s6)\n"
                         ".LtextureStage80061F14:\n"
                         "sll        $v0, $s7, 24\n"
                         "sra        $v0, $v0, 19\n"
                         "addiu      $v0, $v0, 0xFA\n"
                         "sh         $v0, 0x12($s6)\n"
                         "lw         $t3, %5\n"
                         "lui        $t4, %%hi(gPadPictureMenuLists)\n"
                         "addiu      $t4, $t4, %%lo(gPadPictureMenuLists)\n"
                         "addu       $v0, $t3, $t4\n"
                         "lw         $v0, 0x0($v0)\n"
                         "nop\n"
                         "lhu        $v0, 0x14($v0)\n"
                         "nop\n"
                         "addiu      $v0, $v0, 0x7\n"
                         "sh         $v0, 0x14($s6)\n"
                         "lhu        $a0, 0x0($s3)\n"
                         "lhu        $a1, 0x2($s3)\n"
                         "lw         $s2, 0x20($s6)\n"
                         "jal        GetClut\n"
                         "nop\n"
                         "sh         $v0, 0xE($s2)\n"
                         "lhu        $a0, 0x8($s3)\n"
                         "lhu        $a2, -0x4($s3)\n"
                         "lhu        $a3, -0x2($s3)\n"
                         "jal        GetTPage\n"
                         "addu      $a1, $zero, $zero\n"
                         "sh         $v0, 0x16($s2)\n"
                         "lhu        $v0, 0x4($s3)\n"
                         "nop\n"
                         "sb         $v0, 0xC($s2)\n"
                         "lbu        $v0, 0x6($s3)\n"
                         "nop\n"
                         "addiu      $v0, $v0, 0x6\n"
                         "sb         $v0, 0xD($s2)\n"
                         "lhu        $v0, 0x4($s3)\n"
                         "nop\n"
                         "sb         $v0, 0x14($s2)\n"
                         "lhu        $v0, 0x6($s3)\n"
                         "nop\n"
                         "sb         $v0, 0x15($s2)\n"
                         "lbu        $v0, 0x4($s3)\n"
                         "nop\n"
                         "addiu      $v0, $v0, 0x32\n"
                         "sb         $v0, 0x1C($s2)\n"
                         "lbu        $v0, 0x6($s3)\n"
                         "nop\n"
                         "addiu      $v0, $v0, 0x6\n"
                         "sb         $v0, 0x1D($s2)\n"
                         "lbu        $v0, 0x4($s3)\n"
                         "nop\n"
                         "addiu      $v0, $v0, 0x32\n"
                         "sb         $v0, 0x24($s2)\n"
                         "lhu        $v1, 0x6($s3)\n"
                         "addiu      $v0, $s7, 0x1\n"
                         "addu       $s7, $v0, $zero\n"
                         "sll        $v0, $v0, 24\n"
                         "sra        $v0, $v0, 24\n"
                         "slti       $v0, $v0, 0x2\n"
                         "sb         $v1, 0x25($s2)\n"
                         "sw         $s6, 0x1C($s5)\n"
                         "bnez       $v0, .LtextureStage80061E44\n"
                         "addu      $s5, $s6, $zero\n"
                         ".set\treorder\n"
                         : "=r"(currentNode), "=r"(previousNode),
                           "=m"(packetHeight.value), "=m"(textureRow.value),
                           "=m"(stripPanel.value), "=m"(sideOffset.value),
                           "=r"(textureOffset)
                         : "m"(colorHome.value), "m"(panelIndex.value),
                           "r"(textureOffset)
                         : "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$11",
                           "$12", "$16", "$17", "$18", "$19", "$23", "$30",
                           "$31", "memory");
        }
        {
            /* The leaf setter reads its fifth and sixth arguments here. */
            asm volatile(
                ".set\tnoreorder\n"
                "lbu        $a0, gMenuObjectPoolCount\n"
                "lw         $v1, gMenuObjectPool\n"
                "addiu      $v0, $a0, 0x1\n"
                "sb         $v0, gMenuObjectPoolCount\n"
                "sll        $v0, $a0, 3\n"
                "addu       $v0, $v0, $a0\n"
                "sll        $v0, $v0, 2\n"
                "addu       $v1, $v1, $v0\n"
                "sb         $zero, 0x4($v1)\n"
                "sb         $zero, 0x3($v1)\n"
                "sb         $zero, 0x2($v1)\n"
                "lbu        $a0, D_800A37BC\n"
                "addu       $s6, $v1, $zero\n"
                "sh         $zero, 0x12($s6)\n"
                "sh         $zero, 0x14($s6)\n"
                "sw         $zero, 0x1C($s6)\n"
                "sh         $zero, 0x1A($s6)\n"
                "sh         $zero, 0x0($s6)\n"
                "sh         $zero, 0xA($s6)\n"
                "sh         $zero, 0x6($s6)\n"
                "lw         $t3, %4\n"
                "lw         $v1, D_800A3654\n"
                "sh         $zero, 0xE($s6)\n"
                "sh         $zero, 0x10($s6)\n"
                "sh         $zero, 0x1A($s6)\n"
                "sra        $v0, $t3, 24\n"
                "sh         $v0, 0xC($s6)\n"
                "sh         $v0, 0x8($s6)\n"
                "addiu      $v0, $a0, 0x1\n"
                "sb         $v0, D_800A37BC\n"
                "sll        $v0, $a0, 1\n"
                "addu       $v0, $v0, $a0\n"
                "sll        $v0, $v0, 2\n"
                "addu       $v1, $v1, $v0\n"
                "sw         $v1, 0x20($s6)\n"
                "sb         $zero, 0x0($v1)\n"
                "sb         $zero, 0x3($v1)\n"
                "sw         $zero, 0x4($v1)\n"
                "lbu        $t4, %5\n"
                "nop\n"
                "sll        $v0, $t4, 24\n"
                "beqz       $v0, .LlabelStage800620BC\n"
                "ori       $t3, $zero, 0x140\n"
                "j          .LlabelStage800620C4\n"
                "sh        $t3, 0x6($s6)\n"
                ".LlabelStage800620BC:\n"
                "addiu      $v0, $zero, -0x140\n"
                "sh         $v0, 0x6($s6)\n"
                ".LlabelStage800620C4:\n"
                "ori        $v0, $zero, 0x8\n"
                "sh         $v0, 0x12($s6)\n"
                "lbu        $t4, %5\n"
                "lui        $t3, %%hi(gPadPictureMenuLists)\n"
                "addiu      $t3, $t3, %%lo(gPadPictureMenuLists)\n"
                "sll        $v1, $t4, 24\n"
                "sra        $v1, $v1, 24\n"
                "sll        $s0, $v1, 2\n"
                "addu       $t0, $s0, $t3\n"
                "lw         $v0, 0x0($t0)\n"
                "addu       $a0, $s6, $zero\n"
                "lhu        $v0, 0x14($v0)\n"
                "ori        $a1, $zero, 0x2\n"
                "ori        $a2, $zero, 0x2\n"
                "addu       $s7, $zero, $zero\n"
                "addiu      $v0, $v0, 0x5\n"
                "sh         $v0, 0x14($s6)\n"
                "lui        $a3, %%hi(D_8009AC08)\n"
                "lw         $a3, %%lo(D_8009AC08)($a3)\n"
                "lw         $t4, %4\n"
                "addu       $s3, $v1, $zero\n"
                "addu       $s1, $t0, $zero\n"
                "ori        $t3, $zero, 0x1\n"
                "sw         $zero, %2\n"
                "sw         $t3, %3\n"
                "jal        MenuSetTextObject\n"
                "sra       $s2, $t4, 24\n"
                "sw         $s6, 0x1C($s5)\n"
                "addu       $s5, $s6, $zero\n"
                "lui        $at, %%hi(D_800A3A84)\n"
                "addu       $at, $at, $s0\n"
                "sw         $s5, %%lo(D_800A3A84)($at)\n"
                ".LlabelStage80062144:\n"
                "lbu        $a0, gMenuObjectPoolCount\n"
                "lw         $v1, gMenuObjectPool\n"
                "addiu      $v0, $a0, 0x1\n"
                "sb         $v0, gMenuObjectPoolCount\n"
                "sll        $v0, $a0, 3\n"
                "addu       $v0, $v0, $a0\n"
                "sll        $v0, $v0, 2\n"
                "addu       $v1, $v1, $v0\n"
                "sb         $zero, 0x4($v1)\n"
                "sb         $zero, 0x3($v1)\n"
                "sb         $zero, 0x2($v1)\n"
                "lbu        $a0, D_800A37BC\n"
                "addu       $s6, $v1, $zero\n"
                "lw         $v1, D_800A3654\n"
                "sh         $zero, 0x12($s6)\n"
                "sh         $zero, 0x14($s6)\n"
                "sw         $zero, 0x1C($s6)\n"
                "sh         $zero, 0x1A($s6)\n"
                "sh         $zero, 0x0($s6)\n"
                "sh         $zero, 0xA($s6)\n"
                "sh         $zero, 0x6($s6)\n"
                "sh         $s2, 0xC($s6)\n"
                "sh         $s2, 0x8($s6)\n"
                "sh         $zero, 0xE($s6)\n"
                "sh         $zero, 0x10($s6)\n"
                "sh         $zero, 0x1A($s6)\n"
                "addiu      $v0, $a0, 0x1\n"
                "sb         $v0, D_800A37BC\n"
                "sll        $v0, $a0, 1\n"
                "addu       $v0, $v0, $a0\n"
                "sll        $v0, $v0, 2\n"
                "addu       $v1, $v1, $v0\n"
                "sw         $v1, 0x20($s6)\n"
                "sb         $zero, 0x0($v1)\n"
                "sb         $zero, 0x3($v1)\n"
                "beqz       $s3, .LlabelStage800621E4\n"
                "sw        $zero, 0x4($v1)\n"
                "ori        $t4, $zero, 0x140\n"
                "j          .LlabelStage800621EC\n"
                "sh        $t4, 0x6($s6)\n"
                ".LlabelStage800621E4:\n"
                "addiu      $v0, $zero, -0x140\n"
                "sh         $v0, 0x6($s6)\n"
                ".LlabelStage800621EC:\n"
                "sll        $v0, $s7, 24\n"
                "sra        $v1, $v0, 24\n"
                "beqz       $v1, .LlabelStage80062210\n"
                "ori       $v0, $zero, 0x46\n"
                "bltz       $v1, .LlabelStage8006222C\n"
                "slti      $v0, $v1, 0x3\n"
                "beqz       $v0, .LlabelStage8006222C\n"
                "sll       $v0, $v1, 5\n"
                "addiu      $v0, $v0, 0xD5\n"
                ".LlabelStage80062210:\n"
                "sh         $v0, 0x12($s6)\n"
                "lw         $v0, 0x0($s1)\n"
                "nop\n"
                "lhu        $v0, 0x14($v0)\n"
                "nop\n"
                "addiu      $v0, $v0, 0x3C\n"
                "sh         $v0, 0x14($s6)\n"
                ".LlabelStage8006222C:\n"
                "ori        $t3, $zero, 0x1\n"
                "sll        $v0, $s7, 24\n"
                "sra        $v0, $v0, 22\n"
                "sw         $zero, %2\n"
                "sw         $t3, %3\n"
                "lui        $at, %%hi(D_8009AC10)\n"
                "addu       $at, $at, $v0\n"
                "lw         $a3, %%lo(D_8009AC10)($at)\n"
                "addu       $a0, $s6, $zero\n"
                "ori        $a1, $zero, 0x2\n"
                "jal        MenuSetTextObject\n"
                "ori       $a2, $zero, 0x2\n"
                "sw         $s6, 0x1C($s5)\n"
                "addiu      $v0, $s7, 0x1\n"
                "addu       $s7, $v0, $zero\n"
                "sll        $v0, $v0, 24\n"
                "sra        $v0, $v0, 24\n"
                "slti       $v0, $v0, 0x3\n"
                "bnez       $v0, .LlabelStage80062144\n"
                "addu      $s5, $s6, $zero\n"
                ".set\treorder\n"
                : "=r"(currentNode), "=r"(previousNode), "=m"(labelArgs.fifth),
                  "=m"(labelArgs.sixth)
                : "m"(colorHome.value), "m"(panelIndex.value), "1"(previousNode)
                : "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$11", "$12",
                  "$16", "$17", "$18", "$19", "$23", "$31", "memory");
        }
        {
            /* Allocate and place the tall red marker and its two thin rows.
             * The shared column offset stays inside this block in hardware FP. */
            asm volatile(
                ".set\tnoreorder\n"
                "lbu        $v1, gMenuObjectPoolCount\n"
                "lw         $s0, gMenuObjectPool\n"
                "ori        $a0, $zero, 0x1\n"
                "addiu      $v0, $v1, 0x1\n"
                "sb         $v0, gMenuObjectPoolCount\n"
                "sll        $v0, $v1, 3\n"
                "addu       $v0, $v0, $v1\n"
                "sll        $v0, $v0, 2\n"
                "addu       $s0, $s0, $v0\n"
                "ori        $v0, $zero, 0x2\n"
                "sh         $zero, 0x12($s0)\n"
                "sh         $zero, 0x14($s0)\n"
                "sw         $zero, 0x1C($s0)\n"
                "sb         $zero, 0x4($s0)\n"
                "sb         $zero, 0x3($s0)\n"
                "sb         $zero, 0x2($s0)\n"
                "sh         $zero, 0x1A($s0)\n"
                "sh         $v0, 0x0($s0)\n"
                "sh         $zero, 0x6($s0)\n"
                "sh         $zero, 0xA($s0)\n"
                "lw         $t4, %5\n"
                "ori        $s4, $zero, 0x6\n"
                "ori        $s3, $zero, 0x80\n"
                "ori        $v0, $zero, 0x8\n"
                "sh         $zero, 0xE($s0)\n"
                "sh         $zero, 0x10($s0)\n"
                "sh         $s4, 0x16($s0)\n"
                "sh         $v0, 0x18($s0)\n"
                "sb         $s3, 0x2($s0)\n"
                "sb         $zero, 0x3($s0)\n"
                "sb         $zero, 0x4($s0)\n"
                "sra        $s2, $t4, 24\n"
                "sh         $s2, 0x8($s0)\n"
                "jal        GraphicsAllocPolyF4\n"
                "sh        $s2, 0xC($s0)\n"
                "addu       $s1, $v0, $zero\n"
                "addu       $a0, $s1, $zero\n"
                "jal        SetPolyF4\n"
                "sw        $s1, 0x20($s0)\n"
                "addu       $a0, $s1, $zero\n"
                "jal        SetSemiTrans\n"
                "addu      $a1, $zero, $zero\n"
                "addu       $s6, $s0, $zero\n"
                "sh         $s2, 0xA($s1)\n"
                "sh         $s2, 0xE($s1)\n"
                "addiu      $s2, $s2, 0x8\n"
                "sb         $s3, 0x4($s1)\n"
                "sb         $zero, 0x5($s1)\n"
                "sb         $zero, 0x6($s1)\n"
                "sh         $zero, 0x8($s1)\n"
                "sh         $s4, 0xC($s1)\n"
                "sh         $zero, 0x10($s1)\n"
                "sh         $s2, 0x12($s1)\n"
                "sh         $s4, 0x14($s1)\n"
                "sh         $s2, 0x16($s1)\n"
                "sh         $zero, 0x1A($s6)\n"
                "lbu        $t3, %4\n"
                "nop\n"
                "sll        $v0, $t3, 24\n"
                "beqz       $v0, 1f\n"
                "ori       $t4, $zero, 0x140\n"
                "j          2f\n"
                "sh        $t4, 0x6($s6)\n"
                "1:\n"
                "addiu      $v0, $zero, -0x140\n"
                "sh         $v0, 0x6($s6)\n"
                "2:\n"
                "ori        $v0, $zero, 0xA9\n"
                "sh         $v0, 0x12($s6)\n"
                "lbu        $t3, %4\n"
                "lui        $t4, %%hi(gPadPictureMenuLists)\n"
                "addiu      $t4, $t4, %%lo(gPadPictureMenuLists)\n"
                "sll        $v1, $t3, 24\n"
                "sra        $v1, $v1, 24\n"
                "sll        $a0, $v1, 2\n"
                "addu       $v0, $a0, $t4\n"
                "lw         $v0, 0x0($v0)\n"
                "addu       $s7, $zero, $zero\n"
                "lw         $t3, %5\n"
                "ori        $s4, $zero, 0xB\n"
                "lhu        $v0, 0x14($v0)\n"
                "addu       $fp, $a0, $zero\n"
                "sra        $s2, $t3, 24\n"
                "addiu      $s3, $s2, 0x1\n"
                "sw         $v1, %2\n"
                "addiu      $v0, $v0, 0x3B\n"
                "sh         $v0, 0x14($s6)\n"
                "sw         $s6, 0x1C($s5)\n"
                "addu       $s5, $s6, $zero\n"
                "lui        $at, %%hi(D_800A37FC)\n"
                "addu       $at, $at, $fp\n"
                "sw         $s5, %%lo(D_800A37FC)($at)\n"
                "3:\n"
                "lbu        $v1, gMenuObjectPoolCount\n"
                "lw         $s0, gMenuObjectPool\n"
                "ori        $a0, $zero, 0x1\n"
                "addiu      $v0, $v1, 0x1\n"
                "sb         $v0, gMenuObjectPoolCount\n"
                "sll        $v0, $v1, 3\n"
                "addu       $v0, $v0, $v1\n"
                "sll        $v0, $v0, 2\n"
                "addu       $s0, $s0, $v0\n"
                "ori        $v0, $zero, 0x2\n"
                "ori        $t4, $zero, 0x1\n"
                "sb         $zero, 0x2($s0)\n"
                "ori        $t3, $zero, 0x80\n"
                "sh         $zero, 0x12($s0)\n"
                "sh         $zero, 0x14($s0)\n"
                "sw         $zero, 0x1C($s0)\n"
                "sb         $zero, 0x4($s0)\n"
                "sb         $zero, 0x3($s0)\n"
                "sh         $zero, 0x1A($s0)\n"
                "sh         $v0, 0x0($s0)\n"
                "sh         $zero, 0x6($s0)\n"
                "sh         $zero, 0xA($s0)\n"
                "sh         $s2, 0x8($s0)\n"
                "sh         $s2, 0xC($s0)\n"
                "sh         $zero, 0xE($s0)\n"
                "sh         $zero, 0x10($s0)\n"
                "sh         $s4, 0x16($s0)\n"
                "sh         $t4, 0x18($s0)\n"
                "sb         $t3, 0x2($s0)\n"
                "sb         $zero, 0x3($s0)\n"
                "jal        GraphicsAllocPolyF4\n"
                "sb        $zero, 0x4($s0)\n"
                "addu       $s1, $v0, $zero\n"
                "addu       $a0, $s1, $zero\n"
                "jal        SetPolyF4\n"
                "sw        $s1, 0x20($s0)\n"
                "addu       $a0, $s1, $zero\n"
                "jal        SetSemiTrans\n"
                "addu      $a1, $zero, $zero\n"
                "addu       $s6, $s0, $zero\n"
                "ori        $t4, $zero, 0x80\n"
                "sb         $t4, 0x4($s1)\n"
                "sb         $zero, 0x5($s1)\n"
                "sb         $zero, 0x6($s1)\n"
                "sh         $zero, 0x8($s1)\n"
                "sh         $s2, 0xA($s1)\n"
                "sh         $s4, 0xC($s1)\n"
                "sh         $s2, 0xE($s1)\n"
                "sh         $zero, 0x10($s1)\n"
                "sh         $s3, 0x12($s1)\n"
                "sh         $s4, 0x14($s1)\n"
                "sh         $s3, 0x16($s1)\n"
                "sh         $zero, 0x1A($s6)\n"
                "lw         $t3, %2\n"
                "nop\n"
                "beqz       $t3, 4f\n"
                "ori       $t4, $zero, 0x140\n"
                "j          5f\n"
                "sh        $t4, 0x6($s6)\n"
                "4:\n"
                "addiu      $v0, $zero, -0x140\n"
                "sh         $v0, 0x6($s6)\n"
                "5:\n"
                "sll        $v0, $s7, 24\n"
                "bnez       $v0, 6f\n"
                "ori       $v0, $zero, 0xFC\n"
                "ori        $v0, $zero, 0x11C\n"
                "6:\n"
                "sh         $v0, 0x12($s6)\n"
                "lui        $t3, %%hi(gPadPictureMenuLists)\n"
                "addiu      $t3, $t3, %%lo(gPadPictureMenuLists)\n"
                "addu       $v0, $fp, $t3\n"
                "lw         $v0, 0x0($v0)\n"
                "nop\n"
                "lhu        $v1, 0x14($v0)\n"
                "addiu      $v0, $s7, 0x1\n"
                "addu       $s7, $v0, $zero\n"
                "sll        $v0, $v0, 24\n"
                "sra        $v0, $v0, 24\n"
                "slti       $v0, $v0, 0x2\n"
                "addiu      $v1, $v1, 0x37\n"
                "sh         $v1, 0x14($s6)\n"
                "sw         $s6, 0x1C($s5)\n"
                "bnez       $v0, 3b\n"
                "addu      $s5, $s6, $zero\n"
                ".set\treorder\n"
                : "=r"(currentNode), "=r"(previousNode), "=m"(markerPanel.value)
                : "1"(previousNode), "m"(panelIndex.value), "m"(colorHome.value)
                : "$1", "$2", "$3", "$4", "$5", "$11", "$12", "$16", "$17",
                  "$18", "$19", "$20", "$23", "$30", "$31", "memory");
        }
        {
            register s32 colorS asm("$19");
            register s32 panelValue asm("$20");
            s32 initialRow;
            register s8 initialColumn asm("$18");
            register s32 triangleRow asm("$23");
            s32 nextRow;
            s8 triangleColumn;
            s32 rowX;
            register s32 widthDelta asm("$5");
            s32 allocateMode;
            register s32 nodeBlue asm("$12");
            MenuObj *node;
            register u8 *primitive asm("$17");
            MenuObj *panelNode;
            asm volatile(".set\tnoreorder\n"
                         "lw\t$t4, 0x40($sp)\n"
                         "lbu\t$t3, 0x20($sp)\n"
                         "addu\t$s7, $zero, $zero\n"
                         "sra\t$s3, $t4, 24\n"
                         "sll\t$v0, $t3, 24\n"
                         "sra\t$s4, $v0, 24\n"
                         : "=r"(colorS), "=r"(panelValue), "=r"(initialRow)
                         : "m"(colorHome.value), "m"(panelIndex.value)
                         : "$2", "$11", "$12");
            triangleRow = initialRow;
            do {
                rowX = 0xFA;
                if ((s8)triangleRow == 0) {
                    rowX = 0x11A;
                }
                initialColumn = 0;
                asm("" : : "r"(initialColumn));
                triangleColumn = initialColumn;
                panelTableBase = panelValue * 4;
                triangleOffset.value = panelTableBase;
                do {
                    widthDelta = triangleColumn != 0 ? 3 : -3;
                    asm volatile(".set\tnoreorder\n"
                                 "lbu\t$v1, gMenuObjectPoolCount\n"
                                 "lw\t$s0, gMenuObjectPool\n"
                                 "ori\t$a0, $zero, 0x1\n"
                                 "addiu\t$v0, $v1, 0x1\n"
                                 "sb\t$v0, gMenuObjectPoolCount\n"
                                 "sll\t$v0, $v1, 3\n"
                                 "addu\t$v0, $v0, $v1\n"
                                 "sll\t$v0, $v0, 2\n"
                                 "addu\t$s0, $s0, $v0\n"
                                 "ori\t$v0, $zero, 0x8\n"
                                 "ori\t$t3, $zero, 0x6\n"
                                 "sb\t$zero, 0x2($s0)\n"
                                 "ori\t$t4, $zero, 0xFF\n"
                                 "sb\t$zero, 0x3($s0)\n"
                                 "sh\t$t3, 0x18($s0)\n"
                                 "ori\t$t3, $zero, 0x80\n"
                                 "sb\t$zero, 0x4($s0)\n"
                                 "sb\t$t4, 0x2($s0)\n"
                                 "ori\t$t4, $zero, 0x40\n"
                                 "sh\t$zero, 0x12($s0)\n"
                                 "sh\t$zero, 0x14($s0)\n"
                                 "sw\t$zero, 0x1C($s0)\n"
                                 "sh\t$zero, 0x1A($s0)\n"
                                 "sh\t$v0, 0x0($s0)\n"
                                 "sh\t$zero, 0x6($s0)\n"
                                 "sh\t$zero, 0xA($s0)\n"
                                 "sh\t$s3, 0x8($s0)\n"
                                 "sh\t$s3, 0xC($s0)\n"
                                 "sh\t$zero, 0xE($s0)\n"
                                 "sh\t$zero, 0x10($s0)\n"
                                 "sh\t$a1, 0x16($s0)\n"
                                 "sb\t$t3, 0x3($s0)\n"
                                 : "=r"(node), "=r"(allocateMode),
                                   "=r"(nodeBlue)
                                 : "r"(widthDelta), "r"(colorS)
                                 : "$2", "$3", "$11", "memory");
                    node->blue = nodeBlue;
                    primitive = GraphicsAllocPolyF4(allocateMode);
                    node->primitive = primitive;
                    SetPolyF3(primitive);
                    SetSemiTrans(primitive, 0);
                    asm volatile("" : "=r"(currentNode) : "0"(node));
                    asm volatile(
                        ".set\tnoreorder\nori $t3,$zero,0xFF\nori $t4,$zero,0x80\nsb $t3,4($s1)\nori $t3,$zero,0x40\nsb $t4,5($s1)\nsb $t3,6($s1)"
                        :
                        : "r"(primitive)
                        : "$11", "$12", "memory");
                    asm volatile(".set\tnoreorder\n"
                                 "beqz\t$s4, .LTriangleNestedC60_14\n"
                                 "sh\t$zero, 0x1A($s6)\n"
                                 "ori\t$t4, $zero, 0x140\n"
                                 "j\t.LTriangleNestedC60_1c\n"
                                 "sh\t$t4, 0x6($s6)\n"
                                 ".LTriangleNestedC60_14:\n"
                                 "addiu\t$v0, $zero, -0x140\n"
                                 "sh\t$v0, 0x6($s6)\n"
                                 ".LTriangleNestedC60_1c:\n"
                                 :
                                 : "r"(currentNode), "r"(panelValue)
                                 : "$2", "$12", "memory");
                    currentNode->drawOffsetX = rowX;
                    asm volatile(
                        ".set\tnoreorder\nlw $t3,%2\nlui $t4,%%hi(gPadPictureMenuLists)\naddiu $t4,$t4,%%lo(gPadPictureMenuLists)\naddu $v0,$t3,$t4\nlw $v0,0($v0)"
                        : "=r"(panelNode), "=r"(panelTableBase)
                        : "m"(triangleOffset.value)
                        : "$11");
                    rowX += 0xF;
                    asm volatile("" : : "r"(rowX) : "memory");
                    currentNode->drawOffsetY =
                        (u16)panelNode->drawOffsetY + 0x37;
                    previousNode->next = currentNode;
                    previousNode = currentNode;
                    triangleColumn++;
                } while (triangleColumn < 2);
                nextRow = triangleRow + 1;
                triangleRow = nextRow;
                asm("" : "=r"(nextRow) : "0"(nextRow));
            } while ((s8)nextRow < 2);
        }
        {
            s32 colorS;
            register s32 xpos asm("$20");
            register s32 blue asm("$19");
            register s8 initialArrowIndex asm("$23");
            s8 arrowIndex;
            register s32 heightDelta asm("$5");
            s32 allocateMode;
            MenuObj *node;
            register u8 *primitive asm("$17");
            register s32 red asm("$12");
            register s32 green asm("$11");
            asm volatile(".set\tnoreorder\n"
                         "lbu\t$t3, 0x20($sp)\n"
                         "nop\t\n"
                         "sll\t$v0, $t3, 24\n"
                         "sra\t$v0, $v0, 22\n"
                         "addu\t$v0, $v0, $t4\n"
                         "lw\t$v0, 0x0($v0)\n"
                         "lw\t$t4, 0x40($sp)\n"
                         "lh\t$v0, 0x14($v0)\n"
                         "addu\t$s7, $zero, $zero\n"
                         "ori\t$s3, $zero, 0x40\n"
                         "sra\t$s2, $t4, 24\n"
                         "addiu\t$s4, $v0, 0x3A\n"
                         ".set\treorder\n"
                         : "=r"(colorS), "=r"(xpos), "=r"(blue),
                           "=r"(initialArrowIndex), "=r"(panelTableBase)
                         : "m"(panelIndex.value), "m"(colorHome.value),
                           "4"(panelTableBase)
                         : "$2", "$3", "$11", "memory");
            arrowIndex = initialArrowIndex;
            do {
                heightDelta = arrowIndex != 0 ? 3 : -3;
                asm volatile(".set\tnoreorder\n"
                             "lbu\t$v1, gMenuObjectPoolCount\n"
                             "lw\t$s0, gMenuObjectPool\n"
                             "ori\t$a0, $zero, 0x1\n"
                             "addiu\t$v0, $v1, 0x1\n"
                             "sb\t$v0, gMenuObjectPoolCount\n"
                             "sll\t$v0, $v1, 3\n"
                             "addu\t$v0, $v0, $v1\n"
                             "sll\t$v0, $v0, 2\n"
                             "addu\t$s0, $s0, $v0\n"
                             "ori\t$v0, $zero, 0x7\n"
                             "ori\t$t3, $zero, 0x6\n"
                             "sb\t$zero, 0x2($s0)\n"
                             "ori\t$t4, $zero, 0xFF\n"
                             "sb\t$zero, 0x3($s0)\n"
                             "sh\t$t3, 0x16($s0)\n"
                             "ori\t$t3, $zero, 0x80\n"
                             "sh\t$zero, 0x12($s0)\n"
                             "sh\t$zero, 0x14($s0)\n"
                             "sw\t$zero, 0x1C($s0)\n"
                             "sb\t$zero, 0x4($s0)\n"
                             "sh\t$zero, 0x1A($s0)\n"
                             "sh\t$v0, 0x0($s0)\n"
                             "sh\t$zero, 0x6($s0)\n"
                             "sh\t$zero, 0xA($s0)\n"
                             "sh\t$s2, 0x8($s0)\n"
                             "sh\t$s2, 0xC($s0)\n"
                             "sh\t$zero, 0xE($s0)\n"
                             "sh\t$zero, 0x10($s0)\n"
                             "sh\t$a1, 0x18($s0)\n"
                             "sb\t$t4, 0x2($s0)\n"
                             "sb\t$t3, 0x3($s0)\n"
                             ".set\treorder\n"
                             : "=r"(node), "=r"(allocateMode)
                             : "r"(heightDelta), "r"(colorS), "r"(blue)
                             : "$2", "$3", "$11", "$12", "memory");
                node->blue = blue;
                primitive = GraphicsAllocPolyF4(allocateMode);
                node->primitive = primitive;
                SetPolyF3(primitive);
                SetSemiTrans(primitive, 0);
                asm volatile("" : "=r"(currentNode) : "0"(node));
                red = 0xFF;
                green = 0x80;
                primitive[4] = red;
                primitive[5] = green;
                primitive[6] = blue;
                currentNode->orderingDepth = 0;
                asm volatile(".set\tnoreorder\n"
                             "lbu\t$t4, 0x20($sp)\n"
                             "nop\t\n"
                             "sll\t$v0, $t4, 24\n"
                             "beqz\t$v0, .LTriangleFinal60_1c\n"
                             "ori\t$t3, $zero, 0x140\n"
                             "j\t.LTriangleFinal60_24\n"
                             "sh\t$t3, 0x6($s6)\n"
                             ".LTriangleFinal60_1c:\n"
                             "addiu\t$v0, $zero, -0x140\n"
                             "sh\t$v0, 0x6($s6)\n"
                             ".LTriangleFinal60_24:\n"
                             ".set\treorder\n"
                             :
                             : "r"(currentNode), "m"(panelIndex.value)
                             : "$2", "$11", "$12", "memory");
                currentNode->drawOffsetX = 0xAC;
                currentNode->drawOffsetY = xpos;
                previousNode->next = currentNode;
                previousNode = currentNode;
                arrowIndex++;
                xpos += 0xC;
            } while (arrowIndex < 2);
        }
    }
    previousPanelByte = (u8)panelIndex.value;
    nextPanel = previousPanelByte + 1;
    panelIndex.value = nextPanel;
    if (panelIndex.value < D_800A3644[0] + 1) {
        goto panelLoop;
    }
panelsDone:
    ListSetFieldsAndEnable(D_800A37F8, -0x140, 0, 4);
}

void func_80062874(s32 arg0, s32 arg1) {
    MenuObj *node;
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
            if ((u16)node->x < 0x141U) {
                node->velocityX = 2 - flag * 4;
                if (flag != 0) {
                    node->targetX = -0xA0;
                } else {
                    node->targetX = 0x1E0;
                }
            }
            node = node->next;
        } while (node != 0);
    }
}

extern u8 gPadLayout[];
extern u8 D_800A3088[];
extern u8 D_800A3350[];
extern s32 D_8009A4E0[][7][14];
extern u8 D_8009B00C[];
extern u8 D_8009B028[];
extern u8 D_8009B02A[];

void MenuUpdatePadPicture(s32 playerSlot) {
    MenuObj *node;
    POLY_FT4 *prim;
    s32 a;
    s32 c;
    u8 uc;
    s32 ghost;
    s32 id;
    s32 off;
    s32 f;
    u8 *chars;
    s32 fontId;
    s8 i;
    s8 j;
    s32 idx;
    MenuText *prim2;

    node = (u8 *)gPadPictureMenuLists[playerSlot & 0xFF];
    while (*(u16 *)node != 1) {
        node = node->next;
    }
    prim = (POLY_FT4 *)((u8 *)node->primitive);
    if (gPadType[playerSlot & 0xFF] != ((s8 *)D_800A308C)[playerSlot & 0xFF] &&
        gPadType[playerSlot & 0xFF] != 0) {
        ((s8 *)gPadLayout)[playerSlot & 0xFF] = 0;
    }
    if (gPadType[playerSlot & 0xFF] != 0) {
        ((s8 *)D_800A308C)[playerSlot & 0xFF] = gPadType[playerSlot & 0xFF];
    }
    idx = playerSlot & 0xFF;
    a = gPadType[idx];
    if (a != 0) {
        fontId = ((s8 *)D_800A3350)[a];
        chars = D_8009B00C;
        c = *(chars + 7 * fontId + ((s8 *)gPadLayout)[idx]);
    } else {
        c = D_800A3088[idx];
    }
    id = (s8)c;
    off = id * 6;
    D_800A3088[idx] = c;
    prim->clut = GetClut(0x100, *(s16 *)&D_8009B028[off + 4]);
    prim->tpage =
        GetTPage(1, 0, *(s16 *)&D_8009B028[off], *(s16 *)&D_8009B02A[off]);
    prim->u0 = 0;
    prim->v0 = *(u16 *)&D_8009B02A[off];
    prim->u1 = (u16)node->width;
    prim->v1 = *(u16 *)&D_8009B02A[off];
    prim->u2 = 0;
    prim->v2 = D_8009B02A[off] + ((u8 *)node)[0x18];
    prim->u3 = (u16)node->width;
    prim->v3 = D_8009B02A[off] + ((u8 *)node)[0x18];
    node = node->next;
    prim = (POLY_FT4 *)((u8 *)node->primitive);
    if (id == 1 && (gPadType[playerSlot & 0xFF] == 5 ||
                    gPadType[playerSlot & 0xFF] == 7)) {
        prim->r0 = -(gPadType[playerSlot & 0xFF] == 7);
        prim->g0 = -(gPadType[playerSlot & 0xFF] == 5);
        prim->b0 = 0;
        node->unk5 = 1;
    } else {
        node->unk5 = 0;
    }
    node = node->next;
    node->unk5 = !gPadType[playerSlot & 0xFF];
    node = node->next;
    node = node->next;
    prim2 = (u8 *)node->primitive;
    prim2->text = ((s8 *)gPadLayout)[playerSlot & 0xFF] + 1;
    uc = gPadType[playerSlot & 0xFF];
    c = gPadType[playerSlot & 0xFF];
    ghost = c;
    if (uc == 0) {
        c = D_800A308C[playerSlot & 0xFF];
    }
    /* Both terms are zero; combine folds them after flow, so `ghost` stays
       a dead copy that fills the bnez slot. */
    c = c + ((ghost << 24) & 0xFF) + ((ghost << 25) & 0x1FF);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 7; j++) {
            node = node->next;
            f = ((s8 *)D_800A3350)[(s8)c];
            prim2 = (u8 *)node->primitive;
            prim2->text =
                D_8009A4E0[f][((s8 *)gPadLayout)[(u8)playerSlot]][7 * i + j];
        }
    }
}

s32 ListHasClearFlags(MenuObj *node) {
    while (node != 0) {
        if (node->velocityX != 0)
            return 0;
        node = node->next;
    }
    return 1;
}

void ListSetFieldsAndEnable(MenuObj *node, s16 field6, s16 fieldA, s16 fieldE) {
    while (node != 0) {
        node->x = field6;
        node->targetX = fieldA;
        node->velocityX = fieldE;
        node->unk5 = 1;
        node = node->next;
    }
}

extern u8 D_800AEE41[];

void func_80062D38(s32 arg0, s32 arg1, u8 *arg2) {
    MenuObj *obj;
    s32 j;
    s32 i;
    s32 base9;
    s32 idx;
    s32 mode;
    s32 val;
    s32 tmp;
    u8 *p;
    s32 **entry;

    obj = D_800A37FC[arg0 & 0xFF];
    for (i = 2; i >= 0; i--) {
        obj = obj->next;
    }
    for (i = 0; i < 3; i++) {
        mode = arg1 & 0xFF;
        idx = arg0 & 0xFF;
        base9 = idx * 9;
        j = 0;
        /*
         * p is set twice, so the loop pass doesn't strength-reduce
         * arg2 + i. val and tmp also hold the table address and index:
         * with two live ranges each, the entry chain stays in the loop
         * and takes v1/v0 as in retail.
         */
        p = arg2;
        p += i;
        val = (s32)gPadPictureMenuLists;
        tmp = idx << 2;
        entry = (s32 **)(val + tmp);
        do {
            switch (i) {
            case 0:
            case 1:
                if (mode == 2) {
                    val = (p[0] * 49) >> 8;
                    if (val >= 0x32) {
                        val = 0x31;
                    }
                } else {
                    if (i == 0) {
                        if (D_800AEE3E[base9] < arg2[0]) {
                            arg2[0] = D_800AEE3E[base9];
                        }
                        val = D_800AEE3E[base9] - arg2[0];
                    } else {
                        if (p[0] < D_800AEE41[base9]) {
                            p[0] = D_800AEE41[base9];
                        }
                        val = p[0] - D_800AEE41[base9];
                    }
                    val = (val * 3) >> 3;
                    if (val >= 0x31) {
                        val = 0x30;
                    }
                }
                val -= 0x37;
                tmp = *(u16 *)&((MenuObj *)entry[0])->drawOffsetY;
                obj->drawOffsetY = tmp - val;
                break;
            case 2:
                val = (arg2[2] * 103) >> 8;
                if (val >= 0x68) {
                    val = 0x67;
                }
                obj->drawOffsetX = val + 0x78;
                break;
            }
            obj = obj->next;
            j++;
        } while (j < 2);
    }
}

extern s32 D_8009ABFC[];
void func_80062F04(u8 index, u8 kind, u8 sub) {
    u32 code;
    u8 *object;
    s32 *target;

    if (kind == 2) {
        code = 2;
        if (sub < 4) {
            code = 3;
        }
    } else {
        code = 2;
        if (sub < 2) {
            code = 4;
        }
    }
    object = D_800A3A84[index];
    target = *(s32 **)&((MenuObj *)object)->primitive;
    *(target + 2) = D_8009ABFC[code];
}

extern u8 D_800AEE40[];
extern u8 D_800AEE42[];
extern u8 D_800AEE43[];

void func_80062F6C(s32 arg0, s32 arg1) {
    s32 i;
    MenuObj *obj;
    s32 offset;
    s32 **entry;
    s32 b42;
    s32 b43;
    s32 val;
    s32 lim;
    s32 base2;
    s32 d;
    s32 a;
    s32 denom;
    s32 b;
    s32 delta;
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
    base2 = (s32)gPadPictureMenuLists;
    entry = (s32 **)(idx * 4 + base2);
    offset = -3;
    for (; i < 3; i++) {
        switch (i) {
        case 0:
            b42 = D_800AEE42[base9];
            do {
                b43 = D_800AEE43[base9];
                lim = 0x80;
                val = lim - b42;
                val = (val * 103) >> 8;
                y = b43 - 0x80;
                if (val >= 0x68) {
                    val = 0x67;
                }
                y = (y * 103) >> 8;
            } while (0);
            if (y >= 0x68) {
                y = 0x67;
            }
            sum = val + y;
            obj->width = sum;
            if (sum >= 0x68) {
                obj->width = 0x67;
            }
            obj->drawOffsetX = 0xAC - val;
            break;
        case 1:
        case 2:
            delta = arg1 & 0xFF;
            if (delta == 2) {
                j = offset + base9;
                val = D_800AEE3D[j];
                prod = val * 49;
                val = (s32)prod >> 0x8;
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
            obj->height = val;
            delta = val - 0x38;
            obj->drawOffsetY =
                *(u16 *)&((MenuObj *)entry[0])->drawOffsetY - delta;
            break;
        }
        obj = (u8 *)obj->next;
        offset = offset + 3;
    }
}

void func_80063180(s32 enabled) {
    if (enabled & 0xFF) {
        D_800AE290[0][0x1A / 2] = 0;
    } else {
        D_800AE290[0][0x1A / 2] = -1;
    }
}

void MenuAllocateObjectList(void) {
    D_800A3984[0] = (s32)HeapAlloc(0xF00);
}

extern MenuObj *D_800A35E4[];
extern MenuObj *D_800A3868[];
extern MenuObj *MenuCreateTextObject(s32, s32);
extern MenuObj *MenuCreateFlatRect(s32, s32, s32, s32, s32, u8, u8, u8, u8, u8);
extern u8 gPlayerDriver[];

void func_800631DC(s32 left, s32 top, s32 code) {
    MenuObj *node;
    Car *entry;
    s32 mode;
    s32 base;
    s32 x;
    MenuObj *object;
    s32 xoff;
    s32 y;
    s32 dx;
    s32 dy;
    s32 i;
    s32 j;
    register s32 k asm("$18");
    u8 *packet;
    s32 width;

    MenuFontSet(2, 2);
    if (gScreenState[0] == 0xE) {
        base = 0x9E;
    } else {
        base = 0x3A;
    }
    entry = gPlayerCar[0];
    for (i = 0; i < 2; i++) {
        node = MenuObjAlloc();
        mode = gScreenState[0];
        D_800A35E4[i] = node;
        node->kind = 4;
        node->x = left;
        node->targetX = top;
        node->y = base;
        node->targetY = base;
        node->velocityX = code;
        node->velocityY = 0;
        if (mode != 0xE) {
            base += 0x33;
        }
        node->primitive = entry;
        entry = entry->next;
        if (mode == 7 || mode == 0xE) {
            continue;
        }
        x = MenuTextCenterOffset(0x64, (s32)gDriverNames[gPlayerDriver[i]]) -
            0x32;
        object = MenuCreateTextObject(left + x, base - 6);
        object->targetX = top + x;
        object->drawOffsetX = x;
        object->velocityX = code;
        MenuSetTextObject((MenuObj *)object, 2, 2,
                          (s32)gDriverNames[gPlayerDriver[i]], 0, 0);
        node->next = object;
        node = object;
        D_800A3868[i] = node;
        width = 0x32;
        for (j = 0; j < 4; j++) {
            xoff = -0x32;
            y = base - 9;
            switch (j) {
            case 0:
                dx = 0;
                dy = 0;
                break;
            case 1:
                y = base - 2;
                dx = 0;
                dy = 0x29;
                break;
            case 2:
                xoff = 0;
                dx = 0x46;
                dy = 0;
                break;
            case 3:
                xoff = 0;
                y = base - 2;
                dx = 0x46;
                dy = 0x29;
                break;
            }
            object = MenuCreateTexturedRect(left + xoff, y, width, 7, 1, 1, 0);
            packet = object->primitive;
            object->drawOffsetX = xoff;
            object->targetX = top + xoff;
            object->velocityX = code;
            MenuSetTexturedQuad(packet, 9, dx, dy, width, 7);
            node->next = object;
            node = object;
        }
        for (k = 0; k < 2; k++) {
            object = MenuCreateFlatRect(left - 0x32, base - 9, 0x64, 0xE, 0,
                                        0x20, 0x20, 0x40, 1, 1);
            object->orderingDepth = 3;
            object->drawOffsetX = -0x32;
            object->targetX = top - 0x32;
            object->velocityX = code;
            node->next = object;
            node = object;
        }
    }
}

void func_80063538(s32 arg0, s32 arg1) {
    extern MenuObj *MenuCreateFlatTriangle(s32, s32, s32, s32, s32, s32, s32,
                                           s32, s32, s32, s32);
    extern MenuObj *D_800A3628[];
    s32 cmd;
    MenuObj **table;
    MenuObj *node;
    MenuObj *prev;
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
                offs = -4;
            }
            node = MenuCreateFlatTriangle(arg1, cmd, offs, 8, 0, 0x28, 0x64,
                                          0xC8, 0, 1, 0);
            node->orderingDepth = 0;
            if (i != 0) {
                node->drawOffsetX = 0x2E;
            } else {
                node->drawOffsetX = -0x2E;
            }
            node->drawOffsetY = 0;
            node->velocityX = 0;
            if (i == 0) {
                *table = node;
            } else {
                prev->next = node;
            }
            prev = node;
        }
        cmd += 0x33;
        table += 1;
    }
}

extern MenuObj *D_800A3628[];
void func_80063638(u8 mode) {
    s16 left;
    s16 width;
    MenuObj *node;
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
        node->y = left;
        node->targetY = left;
        node->drawOffsetX = width;
        if (i == 0) {
            node->drawOffsetX = -width;
        }
        node = node->next;
    }
}

void MenuSetLinkedObjectLayoutByIndex(u8 index, s16 dx, s16 dy, s16 code) {
    MenuObj *node;

    node = D_800A35E4[index];
    if (node != 0) {
        do {
            node->x = node->drawOffsetX + dx;
            node->velocityX = code;
            node->unk5 = code;
            node->targetX = node->drawOffsetX + dy;
            node = node->next;
        } while (node != 0);
    }
}

void MenuSetDriverNameLabel(u8 index, u8 kind) {
    MenuObj *node;
    MenuText *object;
    s32 value;

    node = D_800A3868[index];
    object = node->primitive;
    object->text = gDriverNames[kind];
    MenuFontSet(object->font, object->scale);
    value = MenuTextCenterOffset(0x64, object->text);
    node->x = value + 0xA;
    node->drawOffsetX = value - 0x32;
}

void MenuNegateLinkedObjectValues(u8 index) {
    MenuObj *node;
    s16 value;

    node = D_800A3868[index];
    if (node != 0) {
        do {
            value = node->orderingDepth;
            if (value > 0) {
                node->orderingDepth = -value;
            } else if (value == 0) {
                node->orderingDepth = -0x8000;
            }
            node = node->next;
        } while (node != 0);
    }
}

void MenuRestoreLinkedObjectValues(u8 index) {
    MenuObj *node;
    s16 value;

    node = D_800A3868[index];
    if (node != 0) {
        do {
            value = node->orderingDepth;
            if (value == -0x8000) {
                node->orderingDepth = 0;
            } else if (value < 0) {
                node->orderingDepth = -value;
            }
            node = node->next;
        } while (node != 0);
    }
}

void ScratchpadFillGrayscaleRamp(void) {
    u32 i;
    u32 greyLevel;

    for (i = 0; i < 0x100; i++) {
        greyLevel = i >> 2;
        ((u32 *)SCRATCHPAD_BASE)[i] =
            (greyLevel << 0x10) | (greyLevel << 8) | greyLevel;
    }
}

extern u8 D_800A3658_w42[] asm("D_800A3658.NON_MATCHING");
extern s32 D_800A36F4_w42 asm("D_800A36F4.NON_MATCHING");
extern u8 *D_800A37E4_w42[] asm("D_800A37E4.NON_MATCHING");
extern s32 D_800BE998_w42[] asm("D_800BE998.NON_MATCHING");
extern u8 *gImageBankTextures_w42[] asm("gImageBankTextures.NON_MATCHING");
extern s32 D_800A353C_w42[] asm("D_800A353C.NON_MATCHING");
extern s32 D_800A3538_w42[] asm("D_800A3538.NON_MATCHING");
extern s32 D_800A3758_w42[] asm("D_800A3758.NON_MATCHING");
extern s32 D_800A3754_w42[] asm("D_800A3754.NON_MATCHING");
extern s32 D_800A3630_w42[] asm("D_800A3630");
extern s32 D_800A2F30_w42[] asm("D_800A2F30.NON_MATCHING");
extern u8 *D_800A3574_w42[] asm("D_800A3574.NON_MATCHING");
extern u8 *D_800A3570_w42[] asm("D_800A3570.NON_MATCHING");
extern u8 D_800AE88C_w42[] asm("D_800AE88C.NON_MATCHING");
extern s32 D_800AE8C0_w42[] asm("D_800AE8C0.NON_MATCHING");

void func_80063874(void) {
    void *table;
    u8 *head;
    u8 *src;
    u8 *end;
    u32 count;
    s32 i;
    u8 *elem;
    s32 n;
    s32 first;
    s32 second;

    D_800A36F4_w42 = (s32)FileLoadOffsetTable(7, &table, SCRATCH_TOP);
    if (D_800A3658_w42[0] == 0) {
        func_8001E230(8, STACK_BLOCK_801A0000 + 0x1A000);
        head = D_800A37E4_w42[0];
        src = ((u8 **)head)[0];
        end = ((u8 **)head)[1];
        count = (u32)(end - src) >> 2;
        for (i = 0; i < count; i++) {
            D_800BE998_w42[i] = ((u32 *)src)[i];
        }
        D_800A3658_w42[0] = 1;
    }
    gImageBankTextures_w42[0] = (u8 *)D_800BE998_w42;
    D_800A353C_w42[0] = MathFixedDivide(6, 0xF);
    D_800A3758_w42[0] = MathFixedDivide(1, 2);
    D_800A3630_w42[0] = 2;
    D_800A2F30_w42[0] = 0;
    D_800A3754_w42[1] = D_800A3538_w42[1];
    i = 0;
    elem = D_800AE88C_w42;
    do {
        first = D_800A36F4_w42 + ((s32 *)table)[i];
        second = -(i == 0);
        D_800A3574_w42[0] = elem;
        ModelLoadGeometryFromAddress(first, second);
        ModelBuildReverseLinks(D_800A3570_w42[1]);
        elem += 0x44;
        do {
        } while (0);
        n = D_800A3630_w42[0];
        i++;
    } while (i < n);
    if ((i = n) < 10) {
        do {
            *(s32 *)((u8 *)D_800AE8C0_w42 + ((i * 17) << 2)) = 0;
            i++;
        } while (i < 10);
    }
    RenderDrawFiveLinkedLists();
}

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

void func_80063C34(s32 arg0, s32 arg1) {
    RECT rect;
    void *work;
    void *small;
    s32 y1;
    s32 x1;
    s32 x3;
    s32 y3;

    if (arg0 >= 2 && arg1 >= 2) {
        work = HeapAlloc(0x2000);
        small = HeapAlloc(0x20);
        if (work != NULL && small != NULL) {
            x1 = (arg0 % 4) * 0x40 + 0x300;
            y1 = (arg0 / 4) * 0x40 + 0x40;
            rect.x = x1;
            rect.y = y1;
            rect.h = 0x40;
            rect.w = 0x40;
            StoreImage(&rect, (u_long *)work);
            rect.x = (arg0 % 16) * 0x10 + 0x300;
            rect.y = 0x3F - arg0 / 16;
            rect.h = 1;
            rect.w = 0x10;
            StoreImage(&rect, (u_long *)small);
            DrawSync(0);
            x3 = (arg1 % 4) * 0x40 + 0x300; /* anchor: dropping this dead
             * store changes y3's register */
            y3 = (arg1 / 4) * 0x40 + 0x40;
            rect.x = (arg1 % 4) * 0x40 + 0x300;
            rect.y = y3;
            rect.h = 0x40;
            rect.w = 0x40;
            MoveImage(&rect, x1, y1);
            rect.x = (arg1 % 16) * 0x10 + 0x300;
            rect.y = 0x3F - arg1 / 16;
            rect.h = 1;
            rect.w = 0x10;
            MoveImage(&rect, (arg0 % 16) * 0x10 + 0x300, 0x3F - arg0 / 16);
            DrawSync(0);
            rect.x = (arg1 % 4) * 0x40 + 0x300;
            rect.y = y3;
            rect.h = 0x40;
            rect.w = 0x40;
            LoadImage(&rect, (u_long *)work);
            rect.x = (arg1 % 16) * 0x10 + 0x300;
            rect.y = 0x3F - arg1 / 16;
            rect.h = 1;
            rect.w = 0x10;
            LoadImage(&rect, (u_long *)small);
            DrawSync(0);
            HeapFree(work);
            HeapFree(small);
        }
    }
}

extern s32 D_800A2E84Absolute[];
extern Car *func_8002D874(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80063E7C(void) {
    RECT rect;
    Car *entry;
    Car *prev1;
    Car *prev2;
    s32 i;
    s16 srcX;
    s16 tile;

    func_80063874();
    D_800A2E84Absolute[0] = 0;
    entry = func_8002D874(-1, 0, 0, -1);
    entry->pos.x = -0x2EE;
    entry->pos.y = 0xC8;
    entry->pos.z = 0xC8;
    entry->cameraMode = 4;
    D_800A3558[0] = (s32)entry;
    D_800A38AC[0] = (s32)entry;
    entry->prev = 0;
    D_800A2E94[0] = 0;
    prev1 = entry;
    entry = func_8002D874(0, 0, 0x1B, 0);
    entry->pos.x = 0x1F4;
    entry->pos.y = 0;
    prev1->next = entry;
    entry->prev = prev1;
    gPlayerCar[0] = entry;
    prev2 = entry;
    entry = func_8002D874(0, 1, 0x18, -1);
    i = 0;
    tile = 0x40;
    srcX = 0x300;
    entry->pos.x = 0;
    entry->pos.y = 0;
    prev2->next = entry;
    entry->prev = prev2;
    entry->next = 0;
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

/* The empty asm input of arg1 (and where it sits) stretches arg1's live
 * range so global allocation ranks the three parameters arg2, arg1, arg0,
 * handing them s1, s2, s3 like retail. */
void CarDrawPreviewModel(Car *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80064000(s32 arg0, s32 arg1, s32 arg2) {
    MenuObj *entry;
    Car *obj;
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
    height = (u16)entry->targetX;
    do {
        if (height < 0x140U || entry->x != (s16)height) {
            obj = entry->primitive;
            if (arg2 & 0xFF) {
                SetGeomOffset(entry->x, 0x2D);
            } else {
                SetGeomOffset(entry->x, entry->y);
            }
            if (arg1 & 0xFF) {
                i = 0;
                pad = (u32 *)SCRATCHPAD_BASE;
                do {
                    grey = i >> 2;
                    pad[0] = (grey << 0x10) | (grey << 8) | grey;
                    pad += 1;
                    i += 1;
                } while (i < 0x100U);
            } else {
                ScratchpadFillPattern(0);
            }
            CarDrawPreviewModel(obj, 0, 0xFA, 0x44C);
            if (!(arg0 & 0xFF) || (arg2 & 0xFF) || gScreenState[0] == 0xE) {
                asm("" : : "r"(arg1));
                t = obj->steering;
                v1 = t + 0xFEC;
                if (v1 < 0) {
                    v0 = t + 0x1FEB;
                } else {
                    v0 = v1;
                }
                result = v1 - ((v0 >> 0xC) << 0xC);
            } else {
                result = (u16)gPlayerCar[0]->steering;
            }
            obj->steering = result;
        }
    } while (0);
}

void TextureLoadTim(void *arg0);

void MenuLoadTextureTable(void) {
    void *data;
    s32 *offsets;
    s32 i;

    data = FileLoadOffsetTable(10, (void **)&offsets, 0);
    for (i = 0; i < 0x18; i++) {
        TextureLoadTim((u8 *)data + offsets[i]);
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

extern u8 D_800A3060[];
extern s8 D_800A39FC;
extern s8 D_800A3594;
extern s8 D_800A3A14;
extern MenuObj *D_800A3744[];
extern MenuObj *D_800A3958[];
extern MenuObj *D_800A3900[];
extern u8 *D_800A35E0Alias[] asm("D_800A35E0Absolute");
extern u8 DriverFindIndexById(s8);
extern void func_800645A4(s32, s32);
extern void ListSetRangeFields(MenuObj *, s32, s32, s16);

void func_80064208(void) {
    MenuObj *tail;
    MenuObj *node;
    MenuObj *prim;
    MenuObj *entry;
    MenuObj *obj;
    MenuObj **linkSlot;
    s32 y;
    s32 height;
    s32 h;
    s32 i;
    s32 j;
    s32 kind;
    s32 kind2;
    s32 k;
    u8 idx;
    if (D_800A3060[0] != 0) {
        D_800A39FC = gPlayerDriver[0];
    } else {
        D_800A39FC = RandomScaledGet(0x18);
    }
    D_800A3594 = DriverFindIndexById(D_800A39FC);
    for (i = 0; i < 2; i++) {
        tail = MenuCreateTexturedRect(0x14, 0x41, 0x40, 0x48, 1, 1, 0);
        D_800A3744[i] = tail;
        tail->drawOffsetX = 0x14;
        node = MenuCreateTextObject(0x5F, 0x2D);
        kind = D_800A39FC;
        node->drawOffsetX = 0x5F;
        MenuSetTextObject(node, 2, 3, gDriverNames[kind], 0, 0);
        tail->next = node;
        tail = node;
        MenuFontSet(2, 3);
        height = MenuFontLineHeight();
        y = height + 0x32;
        MenuFontSet(2, 4);
        height = MenuFontLineHeight();
        for (j = 0; j < 5; j++) {
            node = MenuCreateTextObject(0x5F, y);
            kind2 = D_800A39FC;
            node->drawOffsetX = 0x5F;
            MenuSetTextObject(node, 2, 4, gDriverNames[kind2], 0, 0);
            y += height;
            tail->next = node;
            tail = node;
            if (j == 2) {
                y += 5;
            }
        }

        prim = MenuCreateTexturedRect(0x14, 0x2B, 0x40, 0xC, 1, 1, 0);
        node = prim;
        D_800A3958[i] = prim;
        node->drawOffsetX = 0x14;
        tail->next = node;
        prim = prim->primitive;
        MenuSetTexturedQuad(prim, 2, 0, 0, 0x40, 0xC);
        ((POLY_FT4 *)prim)->x0 = 0x14;
        ((POLY_FT4 *)prim)->y0 = 0x2D;
        ((POLY_FT4 *)prim)->x1 = 0x54;
        ((POLY_FT4 *)prim)->y1 = 0x2D;
        ((POLY_FT4 *)prim)->x2 = 0x14;
        ((POLY_FT4 *)prim)->y2 = 0x39;
        ((POLY_FT4 *)prim)->x3 = 0x54;
        ((POLY_FT4 *)prim)->y3 = 0x39;
    }

    for (k = 0; k < 2; k++) {
        tail =
            MenuCreateFlatRect(0, 0x27, 0x140, 0xC8, 0, 0x10, 0x10, 0x10, 1, 1);
        if (k == 0) {
            D_800A3900[0] = tail;
        } else {
            *(linkSlot = &D_800A3900[0]->next) = tail;
        }
        tail->orderingDepth = 0x3FD;
    }

    idx = (u8)D_800A39FC;
    D_800A3A14 = 0;
    func_800645A4(0, idx);
    entry = D_800A3744[D_800A3A14];
    D_800A39A0[0] = 0;
    D_800A38FC[0] = entry;
    ListSetRangeFields(entry, -0x140, 0, 2);
    func_800631DC(-0x10C, 0x34, 2);
    /* D_800A35E4[0] via the D_800A35E0 alias: a distinct symbol keeps the
     * base load below from being shared with the height lookup. */
    obj = D_800A35E0Alias[1];
    h = *(&D_800A35E4[D_800A3A14]->targetX);
    while (obj != 0) {
        node = (MenuObj *)&obj->velocityX;
        *((s16 *)node) = 2;
        obj->unk5 = 2;
        obj->x = ((u16)obj->drawOffsetX) - 0x10C;
        obj->targetX = ((u16)obj->drawOffsetX) + h;
        obj = obj->next;
    }

    func_80063AE0(D_800A3A14, D_800A39FC);
}

void func_800645A4(s32 arg0, s32 arg1) {
    MenuObj *node;
    POLY_FT4 *prim;
    MenuText *prim2;
    u8 *str;
    u32 idx;
    s32 y;
    s32 offset;
    s32 advance;
    s32 i;
    s32 x;
    s32 h;
    u32 q;
    u32 quotient;
    u32 u;
    u32 remainder;

    node = D_800A3744[arg0 & 0xFF];
    idx = arg1 & 0xFF;
    prim = (POLY_FT4 *)((u8 *)node->primitive);
    prim->clut = GetClut(0x100, 0x1E7 - idx);
    quotient = idx / 12;
    y = (quotient & 0xFF) * 0x48;
    y += 0x140;
    remainder = idx - quotient * 12;
    remainder <<= 5;
    u = remainder & 0x1F80;
    u += 0x140;
    prim->tpage = GetTPage(1, 0, u, y);
    /* Shift pair keeps the mask on idx; CSE would use arg1. */
    q = (idx << 30) >> 30;
    u = q << 6;
    prim->u0 = u;
    prim->v0 = y;
    q = u + 0x3F;
    prim->u1 = q;
    prim->v1 = y;
    prim->u2 = u;
    prim->v2 = y + 0x47;
    prim->u3 = q;
    prim->v3 = y + 0x47;
    node = node->next;
    MenuFontSet(2, 4);
    h = MenuFontLineHeight();
    x = node->y;
    offset = *(s32 *)(D_800A3A5C + idx * 4);
    for (i = 0; i < 6; i++) {
        prim2 = node->primitive;
        if (i == 0) {
            prim2->text = gDriverNames[idx];
        } else {
            str = (u8 *)(D_800A3358 + offset);
            prim2->text = str;
            while (*str != 0) {
                str++;
                offset++;
            }
            offset++;
        }
        node->y = x;
        if (i == 0) {
            x = h + 0x32;
        } else {
            if (i == 1 || (u32)(i - 4) < 2) {
                y = TextCountLines(*(u8 **)&prim2->text) * h;
            } else {
                y = h;
            }
            x += y;
        }
        if (i == 3) {
            x += 5;
        }
        node = node->next;
    }
    func_80063AE0(arg0 & 0xFF, arg1 & 0xFF);
    if ((arg1 & 0xFF) == 2 || (arg1 & 0xFF) == 5 || (arg1 & 0xFF) == 7 ||
        (u32)((arg1 - 9) & 0xFF) < 2 || (arg1 & 0xFF) == 0x11 ||
        (u32)((arg1 - 0x15) & 0xFF) < 2) {
        str = (u8 *)D_800A3958[arg0 & 0xFF];
        advance = -1;
    } else {
        str = (u8 *)D_800A3958[arg0 & 0xFF];
        advance = 1;
    }
    ((MenuObj *)str)->orderingDepth = advance;
}

void ListSetRangeFields(MenuObj *node, s32 low, s32 high, s16 value) {
    while (node != NULL) {
        node->velocityX = value;
        node->x = node->drawOffsetX + low;
        node->targetX = node->drawOffsetX + high;
        node = node->next;
    }
}

extern MenuObj *D_800A39A4nm[] asm("D_800A39A4.NON_MATCHING");
extern MenuObj *D_800A39AC[];

void MenuDrawObjectGroups(void) {
    MenuDrawObjectList(D_800A38FC[1], 0xFF);
    if (D_800A38FC[0] != 0) {
        MenuUpdateObjectPosition(D_800A38FC[0], 1);
        MenuDrawObjectList(D_800A3900[-1], 0xFF);
    }
    if (D_800A39A0[0] != 0) {
        MenuUpdateObjectPosition(D_800A39A0[0], 1);
        MenuDrawObjectList(D_800A39A4nm[-1], 0xFF);
    }
    MenuUpdateObjectPosition(D_800A35E4[0], 1);
    MenuDrawObjectList(D_800A35E8[-1], 0xFF);
    func_80064000(0, 0, 0);
    if (D_800A3A14 != 0 || D_800A39AC[-3] != 0) {
        MenuUpdateObjectPosition(D_800A35E8[0], 1);
        MenuDrawObjectList(D_800A35E8[0], 0xFF);
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

extern u16 D_8009B048[][7];
extern u8 D_8009B04A[];
extern u16 D_8009B050[][7];
extern u16 D_8009B054[][7];

void MenuInitializeTexturedQuad(POLY_FT4 *prim, u8 idx) {
    SetShadeTex(prim, 0);
    prim->r0 = 0x80;
    prim->g0 = 0x80;
    prim->b0 = 0x80;
    SetSemiTrans(prim, 0);
    prim->clut = GetClut(0x140, 0xEF - idx);
    prim->tpage =
        GetTPage(D_8009B054[idx][0], 0, D_8009B048[idx][0], D_8009B048[idx][1]);
    prim->u0 = D_8009B050[idx][0];
    prim->v0 = D_8009B048[idx][5];
    prim->u1 = D_8009B04A[idx * 14 + 6] + 0x3F;
    prim->v1 = D_8009B054[idx][-1];
    prim->u2 = D_8009B048[idx][4];
    prim->v2 = D_8009B028[idx * 14 + 0x2A] + 0x47;
    prim->u3 = D_8009B00C[idx * 14 + 0x44] + 0x3F;
    prim->v3 = D_8009B02A[idx * 14 + 0x28] + 0x47;
}

extern u8 *D_8009A3F0[];
extern u8 *D_8009A418[];
extern u8 D_800A3698;
extern u8 D_800A3A4C;
extern u8 *D_800A39D8;
extern u8 *D_800A369C;
void MenuInitializeGlyphPrimitiveBuffer(void) {
    extern u32 *D_800A38C4;
    extern s32 D_800A367C;

    D_800A38C4 = (u32 *)gOrderingTables;
    gOrderingTable[0] = gOrderingTables;
    D_800A39D8 = gOrderingTables + 0x20;
    D_800A369C = gOrderingTables + 0x13A8;
    if (gSessionTypeAbsolute[0] == 0) {
        D_800A3698 = strlen(D_8009A3F0[0]);
    } else {
        D_800A3698 = strlen(D_8009A418[0]);
    }
    D_800A3A4C = strlen(D_8009A400[0]);
    /* Preserve the byte reloads observed after these stores in retail. */
    D_800A3698 += *(volatile u8 *)&D_800A3A4C;
    D_800A367C = (s32)(D_800A369C + *(volatile u8 *)&D_800A3698 * 0x28);
    MenuFontCopyGlyphPrimitives(2, 4, D_800A39D8);
}

void GraphicsInitDoubleBuffer(s32 mode) {
    s32 height;
    DRAWENV *draw;
    DRAWENV *draw2;
    DISPENV *disp;
    u8 *flags;

    height = 0xF0;
    draw = D_800BDD4C;
    SetDefDrawEnv(draw, 0, 0, 0x140, height);
    disp = D_800BDE04;
    SetDefDispEnv(disp, 0, 0, 0x140, height);
    draw2 = (DRAWENV *)((u8 *)draw + 0x5C);
    if ((u8)mode != 0) {
        SetDefDrawEnv(draw2, 0, 0, 0x140, height);
        SetDefDispEnv((DISPENV *)((u8 *)disp + 0x14), 0, 0, 0x140, height);
    } else {
        SetDefDrawEnv(draw2, 0x140, 0, 0x140, height);
        SetDefDispEnv((DISPENV *)((u8 *)disp + 0x14), 0x140, 0, 0x140, height);
    }
    asm("" : "=r"(flags) : "0"(D_800BDD62));
    flags[0] = 0;
    D_800BDDC0[0] = 1;
    D_800BDD64[0] = 1;
    D_800BDDBE[0] = 0;
    if ((u8)mode != 0) {
        D_800BDD65[0] = 0;
        D_800BDD66[0] = 0;
        D_800BDD67[0] = 0xA;
        flags[0x5F] = 0;
        flags[0x60] = 0;
        flags[0x61] = 0xA;
    } else {
        D_800BDD65[0] = 0;
        D_800BDD66[0] = 7;
        D_800BDD67[0] = 0x26;
        D_800BDDC1[0] = 0;
        D_800BDDC2[0] = 7;
        D_800BDDC3[0] = 0x26;
    }
    SetDispMask(0);
    PutDrawEnv(D_800BDD4C);
    PutDispEnv(D_800BDE04);
}

void func_80064E6C(void) {
    extern u8 D_800A3884;
    extern s32 D_800A367C;
    extern u32 *D_800A38C4;
    /* The post-call string reads go through the neighbouring symbols so
     * cse can't share one address register with the pre-call reads. */
    extern u8 *D_8009A3EC[];
    extern u8 *D_8009A414[];
    extern u8 D_800A3778;
    extern u8 D_800A35DC;
    extern void MenuDrawCarPick(u8 id, s32 shift);
    extern void func_80065F80(void);
    extern void MenuDrawCarPickPair(s32);
    u8 **base;

    ClearOTagR(D_800A38C4, 4);
    GraphicsInitDoubleBuffer(1);
    func_8006499C();
    D_800A367C = (s32)D_800A369C;
    MenuFontSet(2, 4);
    MenuSetTextColor(0x80, 0x80, 0xC0);
    base = D_8009A400;
    MenuDrawString(*base, (s16)MenuTextCenterOffset(0x140, (s32)*base), 0xC8, 0,
                   0, 0, 0, 0);
    if (gSessionTypeAbsolute[0] == 0) {
        MenuDrawString(D_8009A3EC[1],
                       (s16)MenuTextCenterOffset(0x140, (s32)D_8009A3F0[0]),
                       0xC8, 0, 0, 0, 0, 0);
    } else {
        MenuDrawString(D_8009A414[1],
                       (s16)MenuTextCenterOffset(0x140, (s32)D_8009A418[0]),
                       0xC8, 0, 0, 0, 0, 0);
    }
    ClearOTagR(D_800A38C4, 4);
    D_800A367C = (s32)(D_800A369C + D_800A3698 * 0x28);
    if (D_800A3644[0] != 0 && D_800A3073[0] == 0) {
        func_80065F80();
        MenuDrawCarPickPair(1);
    } else {
        func_80065838(1);
        D_800A3778 = 0;
        MenuDrawCarPick(*(volatile u8 *)&D_800A3778, 1);
        if (D_800A3644[0] != 0 && D_800A3073[0] != 0) {
            D_800A35DC = 3;
        } else {
            D_800A35DC = 0xB;
        }
    }
    D_800A3884 = 0;
}

extern s32 D_800A367C;
s32 MenuAllocateGlyphPrimitive(void) {
    s32 current;
    current = D_800A367C;
    D_800A367C = current + 0x28;
    return current;
}

inline s32 func_80065040(void) {
    s32 old;
    old = D_800A367C;
    D_800A367C = old + 0x28;
    return old;
}

extern u8 D_800A3950[];
extern u8 *gTrackNames[];
extern u8 *D_8009A3A4[];
extern u8 *D_8009A3E8[];
extern u8 *D_8009A41C[];
extern u8 *D_8009A3EC[];
extern u8 *D_8009A3ECLui asm("D_8009A3EC");
extern u8 *D_8009ACE0[];
extern u8 *D_8009A42C[];
extern u8 gPlayerDriverLui asm("gPlayerDriverAbsolute");
extern u8 D_800A36E1Lui asm("D_800A36E1Absolute");
extern u8 D_800A3644Lui asm("D_800A3644Absolute");
extern s32 gOrderingTableLui asm("gOrderingTableAbsolute");
extern volatile u16 D_800A3A44;
extern volatile s16 D_800A3A44Signed asm("D_800A3A44");
extern volatile s16 D_800A3940Signed asm("D_800A3940");
extern volatile u8 D_800A3760;
extern u8 *D_800A3568;
extern u8 *D_800A3970;
extern u32 *D_800A38C4;
void MenuDrawCarPick(u8 id, s32 shift) {
    u8 entry[0x40];
    u8 slots[2];
    s32 n;
    u8 *prim;
    u8 *end;
    s32 xOffset;
    s32 leftX;
    s32 i;
    s32 x0;
    s32 x1off;
    s32 height;
    s32 red;
    s32 green;
    s32 blue;
    s32 yBase;
    u8 color;
    s32 r2;
    s32 g2;
    s32 b2;

    xOffset = -((shift & 0xFF) != 0) & -0x140;
    n = 1;
    height = id * 2;
    for (i = 0; i < 2; i++) {
        slots[i] = 0xFF;
        if (gDriverOrder[height + i] == gPlayerDriverLui) {
            slots[n - 1] = i;
            n++;
        }
        if (D_800A3644Lui != 0 && gDriverOrder[height + i] == D_800A36E1Lui) {
            slots[n - 1] = i;
            n++;
        }
    }
    x1off = 0x11C;
    x0 = xOffset + 0x12;
    for (i = 0; i < 3; i++) {
        prim = (u8 *)func_80065040();
        SetPolyF4((POLY_F4 *)prim);
        SetSemiTrans(prim, 0);
        switch (i) {
        case 0:
            height = 0x1C;
            red = 0;
            green = 0;
            blue = 0x80;
            yBase = 0x3E;
            ((POLY_F4 *)prim)->r0 = 0;
            ((POLY_F4 *)prim)->g0 = 0;
            ((POLY_F4 *)prim)->b0 = blue;
            break;
        case 1:
            height = 0x48;
            red = 0;
            green = 0;
            blue = 0x4C;
            yBase = 0x5A;
            ((POLY_F4 *)prim)->r0 = 0;
            ((POLY_F4 *)prim)->g0 = 0;
            ((POLY_F4 *)prim)->b0 = blue;
            break;
        case 2:
            height = 0x12;
            red = 0;
            green = 0;
            blue = 0xC0;
            yBase = 0xA2;
            ((POLY_F4 *)prim)->r0 = 0;
            ((POLY_F4 *)prim)->g0 = 0;
            ((POLY_F4 *)prim)->b0 = blue;
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
                    x0 = xOffset + 0x12;
                } else {
                    x0 = xOffset + 0xA0;
                }
            }
            break;
        }
        ((POLY_F4 *)prim)->r0 = red;
        ((POLY_F4 *)prim)->g0 = green;
        ((POLY_F4 *)prim)->b0 = blue;
        ((POLY_F4 *)prim)->x0 = x0;
        ((POLY_F4 *)prim)->y0 = yBase;
        ((POLY_F4 *)prim)->x1 = x0 + x1off;
        ((POLY_F4 *)prim)->y1 = yBase;
        ((POLY_F4 *)prim)->x2 = x0;
        ((POLY_F4 *)prim)->y2 = yBase + height;
        ((POLY_F4 *)prim)->x3 = x0 + x1off;
        ((POLY_F4 *)prim)->y3 = yBase + height;
        if (i < 3) {
            AddPrim((u8 *)D_800A38C4 + 0xC, prim);
        } else {
            AddPrim((u8 *)D_800A38C4 + 8, prim);
        }
    }
    leftX = xOffset + 0x17;
    height = id * 2;
    for (i = 0; i < 2; i++) {
        color = gDriverOrder[height + i];
        prim = (u8 *)func_80065040();
        SetPolyFT4((POLY_FT4 *)prim);
        MenuInitializeTexturedQuad(prim, color);
        if (i == 0) {
            ((POLY_FT4 *)prim)->x0 = leftX;
            ((POLY_FT4 *)prim)->y0 = 0x5A;
            ((POLY_FT4 *)prim)->x1 = xOffset + 0x57;
            ((POLY_FT4 *)prim)->y1 = 0x5A;
            ((POLY_FT4 *)prim)->x2 = leftX;
            ((POLY_FT4 *)prim)->y2 = 0xA2;
            ((POLY_FT4 *)prim)->x3 = xOffset + 0x57;
            ((POLY_FT4 *)prim)->y3 = 0xA2;
        } else {
            ((POLY_FT4 *)prim)->x0 = xOffset + 0xA5;
            ((POLY_FT4 *)prim)->y0 = 0x5A;
            ((POLY_FT4 *)prim)->x1 = xOffset + 0xE5;
            ((POLY_FT4 *)prim)->y1 = 0x5A;
            ((POLY_FT4 *)prim)->x2 = xOffset + 0xA5;
            ((POLY_FT4 *)prim)->y2 = 0xA2;
            ((POLY_FT4 *)prim)->x3 = xOffset + 0xE5;
            ((POLY_FT4 *)prim)->y3 = 0xA2;
        }
        AddPrim((u8 *)D_800A38C4 + 8, prim);
    }
    D_800A3568 = (u8 *)D_800A367C;
    MenuFontSet(2, 4);
    MenuSetTextColor(0x80, 0x80, 0xC0);
    gOrderingTableLui += 4;
    if (D_800A3950[0] == 0xFB || D_800A3950[0] == 3) {
        MenuDrawString(gTrackNames[gSelectedTrack[0]], 0x17, 0x41, 0, 0, 1, 0,
                       0);
    } else {
        MenuDrawString(D_8009A3A4[gSelectedTrack[0]], 0x17, 0x41, 0, 0, 1, 0,
                       0);
    }
    if (gSessionTypeAbsolute[0] == 0) {
        MenuDrawString(D_8009A3E8[0], 0x17, 0x4D, 0, 0, 1, 0, 0);
    } else {
        MenuDrawString(D_8009A41C[0], 0x17, 0x4D, 0, 0, 1, 0, 0);
    }
    if (id + 1 >= 0xA) {
        D_8009A3ECLui[4] = 0x31;
        D_8009A3ECLui[5] = id + 0x27;
        D_8009A3ECLui[6] = 0;
    } else {
        D_8009A3ECLui[4] = id + 0x31;
        D_8009A3ECLui[5] = 0;
    }
    MenuDrawString(D_8009A3EC[0], 0xFC, 0x4D, 0, 0, 0, 0, 0);
    height = id * 2;
    for (i = 0; i < 2; i++) {
        x0 = 0xA5;
        if (i == 0) {
            x0 = 0x17;
        }
        color = gDriverOrder[height + i];
        if (color == gPlayerDriverLui) {
            r2 = 0xC0;
            g2 = 0x80;
            b2 = 0x40;
        } else if (D_800A3644Lui != 0 && color == D_800A36E1Lui) {
            g2 = 0x80;
            r2 = 0xC0;
            b2 = 0x40;
        } else {
            r2 = 0x80;
            g2 = 0x80;
            b2 = 0xC0;
        }
        MenuSetTextColor(r2, g2, b2);
        MenuDrawString(D_8009ACE0[color], x0, 0xA7, 0, 0, 0, 0, 0);
        MenuDrawString(gDriverNames[color], x0 + 0x1E, 0xA7, 0, 0, 0, 0, 0);
        if (gSessionTypeAbsolute[0] == 0 && D_800AEB34[color] == 0x7FFFFFFF) {
            MenuDrawString(D_8009A42C[0], x0 + 0x45, 0x7E, 0, 0, 0, 0, 0);
        } else {
            TextFormatTime((void *)D_800AEB34[color], -1, entry);
            MenuDrawString(entry, x0 + 0x45, 0x7E, 0, 0, 0, 0, 7);
        }
        if (gSessionTypeAbsolute[0] == 0 && height == 0 && i == 0) {
            MenuDrawString(D_8009A3EC[13], x0 + 0x59, 0x61, 0, 0, 0, 0, 0);
            MenuDrawString(D_8009A3EC[14], x0 + 0x4F, 0x6B, 0, 0, 0, 0, 0);
        }
    }
    gOrderingTableLui -= 4;
    end = (u8 *)D_800A367C;
    D_800A3970 = end;
    if (xOffset != 0) {
        for (prim = D_800A3568; prim != end; prim += 0x28) {
            *(u16 *)&((POLY_FT4 *)prim)->x0 += xOffset;
            *(u16 *)&((POLY_FT4 *)prim)->x1 += xOffset;
            *(u16 *)&((POLY_FT4 *)prim)->x2 += xOffset;
            *(u16 *)&((POLY_FT4 *)prim)->x3 += xOffset;
        }
    }
    D_800A3940Signed = 2;
    D_800A3A44 = xOffset;
    D_800A3760 = 1;
}

void func_80065838(s32 arg0) {
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
        if (gSessionTypeAbsolute[0] == 0) {
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
void MenuLinkGlyphPrimitives(void) {
    s32 i;
    u8 *primitive;
    primitive = D_800A38D8;
    for (i = 0; i < D_800A35B4; i++) {
        AddPrim(D_800A38C4 + 1, primitive);
        primitive += 0x28;
    }
}

void func_8006594C(s32 arg0, s32 arg1) {
    extern volatile u16 D_800A3940;
    extern s32 D_800A3538;
    extern s32 D_800A3540;
    extern u8 D_800A35B4;
    extern u32 *D_800A38C4;
    extern u8 *D_800A38D8;
    s16 shift;
    POLY_FT4 *quad;
    POLY_FT4 *walk2;
    u8 *primBase;
    s32 i;

    D_800A3A44 = D_800A3A44 + D_800A3940;
    shift = D_800A3940;
    if ((arg0 & 0xFF) != 0) {
        if ((s16)D_800A3A44 <= 0) {
            goto earlyOut;
        }
    } else {
        if ((s16)D_800A3A44 < 0x141) {
            goto earlyOut;
        }
    }
    D_800A3A44 = D_800A3A44 - D_800A3940;
    if ((arg0 & 0xFF) != 0) {
        shift = -D_800A3A44;
    } else {
        shift = 0x140 - D_800A3A44;
    }
    D_800A3A44 = D_800A3A44 + shift;
    D_800A3940 = 0;
    if ((arg1 & 0xFF) != 0) {
        walk2 = (POLY_FT4 *)D_800A38D8;
        for (i = 0; i < D_800A35B4; i++) {
            AddPrim(D_800A38C4 + 1, walk2);
            walk2++;
        }
    }
    goto tailTest;
earlyOut:
    if ((s16)D_800A3940 < 0x20) {
        D_800A3940 = D_800A3940 + (s16)D_800A3940 / 2;
    }
tailTest:
    if (shift == 0) {
        return;
    }
    if ((arg1 & 0xFF) != 0) {
        for (quad = (POLY_FT4 *)D_800A3538; quad != (POLY_FT4 *)D_800A3540;
             quad++) {
            quad->x0 += shift;
            quad->x1 += shift;
            quad->x2 += shift;
            quad->x3 += shift;
        }
        for (; quad != (POLY_FT4 *)D_800A3970; quad++) {
            quad->x0 -= shift;
            quad->x1 -= shift;
            quad->x2 -= shift;
            quad->x3 -= shift;
        }
    } else {
        primBase = D_800A369C + D_800A3698 * 0x28;
        if (((POLY_F4 *)primBase)->code == 0x28) {
            do {
                ((POLY_F4 *)primBase)->x0 += shift;
                ((POLY_F4 *)primBase)->x1 += shift;
                ((POLY_F4 *)primBase)->x2 += shift;
                ((POLY_F4 *)primBase)->x3 += shift;
                primBase += 0x28;
            } while (((POLY_F4 *)primBase)->code == 0x28);
        }
        for (quad = (POLY_FT4 *)primBase; quad != (POLY_FT4 *)D_800A3970;
             quad++) {
            quad->x0 += shift;
            quad->x1 += shift;
            quad->x2 += shift;
            quad->x3 += shift;
        }
    }
}

/* The ", D_800A3940" and ", D_800A3778" tails below are reads of the just
 * stored volatile; retail reloads the byte/word after the store. */
void func_80065C3C(void) {
    extern s32 GetGp(void);
    extern s32 D_8008CA4C[];
    extern volatile u16 D_800A3940;
    extern volatile u8 D_800A3778Vol asm("D_800A3778");
    extern u8 D_800A35DC;
    extern u8 D_800A3884;
    extern volatile u8 D_800A3360;
    extern void func_8006594C(s32, s32);
    extern void MenuDrawCarPick(u8, s32);
    s32 oldGp;
    u8 *walk;
    char *text;
    s32 len;
    s32 i;

    oldGp = GetGp();
    SystemSetGlobalPointer(D_8008CA4C[0]);
    SetDispMask(1);
    if ((u8)(gScreenState[0] + 3) >= 2) {
        PutDrawEnv(D_800BDD4C);
        if ((D_800A3940 << 16) > 0) {
            func_8006594C(D_800A3760, 0);
        } else if (D_800A3760 == 0) {
            D_800A3940Signed = -0xB5;
        } else {
            D_800A3940 = D_800A3940 - 1, D_800A3940;
        }
        if ((s16)D_800A3940 < -0xB4) {
            if (D_800A3778Vol == D_800A35DC) {
                D_800A3940 = 0;
                if (*(volatile u8 *)&D_800A3884 == 1) {
                    ClearOTagR(D_800A38C4, 4);
                    walk = D_800A369C;
                    walk += D_800A3A4C * 0x28;
                    if (gSessionTypeAbsolute[0] == 0) {
                        text = (char *)D_8009A3F0[0];
                    } else {
                        text = (char *)D_8009A418[0];
                    }
                    len = strlen(text);
                    for (i = 0; i < len; i++) {
                        AddPrim(D_800A38C4, walk);
                        walk += 0x28;
                    }
                    D_800A367C =
                        (s32)(D_800A369C + *(volatile u8 *)&D_800A3698 * 0x28);
                    MenuDrawCarPick(D_800A3778Vol, 0);
                    D_800A3884 = 2;
                }
            } else {
                D_800A3940 = 2;
                D_800A3760 = D_800A3760 ^ 1;
                if (D_800A3760 == 1) {
                    D_800A3778Vol = D_800A3778Vol + 1, D_800A3778Vol;
                    ClearOTagR(D_800A38C4, 4);
                    if (D_800A3884 == 0) {
                        text = (char *)D_8009A400[0];
                        walk = D_800A369C;
                        len = strlen(text);
                        for (i = 0; i < len; i++) {
                            AddPrim(D_800A38C4, walk);
                            walk += 0x28;
                        }
                    } else {
                        walk = D_800A369C;
                        walk += D_800A3A4C * 0x28;
                        if (gSessionTypeAbsolute[0] == 0) {
                            text = (char *)D_8009A3F0[0];
                        } else {
                            text = (char *)D_8009A418[0];
                        }
                        len = strlen(text);
                        for (i = 0; i < len; i++) {
                            AddPrim(D_800A38C4, walk);
                            walk += 0x28;
                        }
                        if (*(volatile u8 *)&D_800A3884 == 1) {
                            D_800A3884 = 2;
                        }
                    }
                    D_800A367C =
                        (s32)(D_800A369C + *(volatile u8 *)&D_800A3698 * 0x28);
                    MenuDrawCarPick(D_800A3778Vol, 1);
                }
            }
        }
        DrawOTag(D_800A38C4 + 3);
        DrawSync(0);
    }
    D_800A3360 = 1;
    asm("addu $gp, %0, $zero" : : "r"(oldGp));
}

extern u8 *D_8009A3FC[];
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

    MenuFontSet(2, 4);
    MenuSetTextColor(0x80, 0x80, 0xC0);
    entry = D_8009A3FC;
    D_800A38D8 = (u8 *)D_800A367C;
    *(volatile u8 *)&D_800A35B4 = strlen((char *)entry[0]);
    MenuDrawString(entry[0], MenuTextCenterOffset(0x140, (s32)entry[0]), 0x7F,
                   0, 0, 0, 0, 0);
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

extern s32 D_800A3540;
extern u8 *D_8009A3F4[];
extern u8 *D_8009A3F8;
extern u8 gSelectedTrackLui asm("gSelectedTrackAbsolute");
void MenuDrawCarPickPair(s32 shiftPanels) {
    s32 i;
    s32 shift;
    s32 x;
    u8 color;
    POLY_FT4 *prim;

    for (i = 0; i < 2; i++) {
        if ((shiftPanels & 0xFF) != 0) {
            shift = -0x140;
            if (i != 0) {
                shift = 0x140;
            }
        } else {
            shift = 0;
        }
        color = gPlayerDriver[i];
        prim = (POLY_FT4 *)func_80065040();
        SetPolyFT4(prim);
        MenuInitializeTexturedQuad((u8 *)prim, color);
        if (i == 0) {
            prim->x0 = shift + 0x3E;
            prim->y0 = 0x66;
            prim->x1 = shift + 0x7E;
            prim->y1 = 0x66;
            prim->x2 = shift + 0x3E;
            prim->y2 = 0xAE;
            prim->x3 = shift + 0x7E;
            prim->y3 = 0xAE;
        } else {
            prim->x0 = shift + 0xCC;
            prim->y0 = 0x66;
            prim->x1 = shift + 0x10C;
            prim->y1 = 0x66;
            prim->x2 = shift + 0xCC;
            prim->y2 = 0xAE;
            prim->x3 = shift + 0x10C;
            prim->y3 = 0xAE;
            D_800A3540 = (s32)prim;
        }
        AddPrim((u8 *)D_800A38C4 + 8, (u8 *)prim);
        D_800A3568 = (u8 *)D_800A367C;
        x = 0xA5;
        if (i == 0) {
            x = 0x17;
        }
        MenuSetTextColor(0x80, 0x80, 0xC0);
        MenuDrawString(D_8009ACE0[color], x, 0xB1, 0, 0, 0, 0, 0);
        MenuDrawString(gDriverNames[color], x + 0x1E, 0xB1, 0, 0, 0, 0, 0);
        D_800A3970 = (u8 *)D_800A367C;
        if (shift != 0) {
            for (prim = (POLY_FT4 *)D_800A3568; prim != (POLY_FT4 *)D_800A3970;
                 prim++) {
                prim->x0 += shift;
                prim->x1 += shift;
                prim->x2 += shift;
                prim->x3 += shift;
            }
        }
    }
    x = MenuTextCenterOffset(0x140, (s32)D_8009A3F4[0]);
    MenuDrawString(D_8009A3F4[0], x, 0x2A, 0, 0, 0, 0, 0);
    x = MenuTextCenterOffset(0x140, (s32)D_8009A3F8);
    MenuDrawString(D_8009A3F8, x, 0x3E, 0, 0, 0, 0, 0);
    x = MenuTextCenterOffset(0x140, (s32)gTrackNames[gSelectedTrackLui]);
    MenuDrawString(gTrackNames[gSelectedTrackLui], x, 0x4D, 0, 0, 0, 0, 0);
    D_800A3940Signed = 2;
    if ((shiftPanels & 0xFF) != 0) {
        D_800A3A44Signed = -0x140;
    } else {
        D_800A3A44 = 0;
    }
    D_800A3760 = 1;
}

void func_800663B0(void) {
    extern s32 D_8008CA4C[];
    extern volatile u16 D_800A3940;
    extern volatile u8 D_800A3760;
    extern volatile u8 D_800A3360;
    extern void func_8006594C(s32, s32);
    extern void MenuDrawCarPickPair(s32);
    s32 oldGp;
    u8 *walk;
    char *text;
    s32 count;
    s32 len;
    s32 i;

    oldGp = GetGp();
    SystemSetGlobalPointer(D_8008CA4C[0]);
    SetDispMask(1);
    if ((u8)(gScreenState[0] + 3) >= 2) {
        if ((D_800A3940 << 16) > 0) {
            PutDrawEnv(D_800BDD4C);
            func_8006594C(D_800A3760, 1);
            DrawOTag(D_800A38C4 + 3);
            DrawSync(0);
        } else {
            if (*(volatile u8 *)&D_800A3884 == 1) {
                PutDrawEnv(D_800BDD4C);
                ClearOTagR(D_800A38C4, 4);
                count = D_800A3A4C;
                walk = (u8 *)D_800A369C;
                walk += count * 0x28;
                if (gSessionTypeAbsolute[0] == 0) {
                    text = (char *)D_8009A3F0[0];
                } else {
                    text = (char *)D_8009A418[0];
                }
                len = strlen(text);
                for (i = 0; i < len; i++) {
                    AddPrim(D_800A38C4, walk);
                    walk += 0x28;
                }
                D_800A367C = D_800A3538;
                MenuDrawCarPickPair(0);
                DrawOTag(D_800A38C4 + 3);
                DrawSync(0);
                D_800A3884 = 2;
            }
        }
    }
    D_800A3360 = 1;
    asm("addu $gp, %0, $zero" : : "r"(oldGp));
}

void *func_8006654C(void *queue, s32 arg1) {
    s32 *templates[2];
    s32 cursor;
    s32 topY;
    s32 sel;
    s32 depth;
    s32 bottomY;
    s32 offset;
    s32 row;
    s32 i;
    s32 x;
    s32 *src;
    s32 *orderTable;
    s32 *dst;
    cursor = (s32)queue;
    depth = arg1;
    for (i = 0; i < 2; i++) {
        if (cursor == 0) {
            templates[i] = (s32 *)GraphicsAllocPolyF4(0);
        } else {
            templates[i] = (s32 *)cursor;
            cursor += 0x18;
        }
        SetPolyF4((u_long *)templates[i]);
        SetSemiTrans((u_long *)templates[i], 1);
        if (i != 0) {
            ((u8 *)templates[i])[4] = 0x18;
            ((u8 *)templates[i])[5] = 0x18;
            ((u8 *)templates[i])[6] = 0x18;
        } else {
            ((u8 *)templates[0])[4] = 8;
            ((u8 *)templates[0])[5] = 8;
            ((u8 *)templates[0])[6] = 8;
        }
    }
    row = 0;
    topY = 0;
    offset = depth << 2;
    do {
        if (row & 1) {
            sel = 0;
        } else {
            sel = 1;
        }
        x = 0;
        i = 0;
        bottomY = topY + 0x20;
        do {
            if (cursor == 0) {
                dst = (s32 *)GraphicsAllocPolyF4(0);
            } else {
                dst = (s32 *)cursor;
                cursor += 0x18;
            }
            src = templates[sel];
            sel ^= 1;
            *((POLY_F4 *)dst) = *((POLY_F4 *)src);
            ((u16 *)dst)[4] = x;
            ((u16 *)dst)[8] = x;
            ((u16 *)dst)[5] = topY;
            ((u16 *)dst)[6] = x + 0x20;
            ((u16 *)dst)[7] = topY;
            ((u16 *)dst)[9] = bottomY;
            ((u16 *)dst)[10] = x + 0x20;
            ((u16 *)dst)[11] = bottomY;
            x += 0x20;
            AddPrim(((u8 *)(orderTable = gOrderingTable)[0]) + offset, dst);
            i += 1;
        } while (i < 0xA);
        row += 1;
        topY += 0x20;
    } while (row < 7);
    return (void *)cursor;
}

extern u8 *gOrderingTablePtr[] asm("gOrderingTable");
extern u8 *D_8009A404[];
extern u8 *D_8009A430[];
extern u8 *D_8009A414[];
extern u8 D_8009B198[];
extern DRAWENV D_800BDDA8[];
extern DISPENV D_800BDE18[];
extern void *func_8006654C(void *, s32);
extern void MenuFontSetS32(s32, s32) asm("MenuFontSet");
asm(".globl MenuDrawStringW");
asm("MenuDrawStringW = MenuDrawString");

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

    GraphicsInitDoubleBuffer(0);
    PutDrawEnv(&D_800BDDA8[0]);
    table = D_8009A404;
    q = table + 2;
    for (page = 0; page < 2; page++) {
        ClearOTagR((u32 *)gOrderingTablePtr[0], 0x3FF);
        GraphicsSelectPrimitiveBuffer(0);
        func_8006654C((void *)0, 0x3FC);
        MenuDrawModel(0, 0, 1);
        MenuFontSetS32(2, 4);
        MenuSetTextColor(0x80, 0x80, 0xC0);
        y = 0xA0;
        i = 0;
        p = table;
        MenuDrawString(gTrackNames[gSelectedTrack[0]], 0x20, 0x23, 0, 0, 0, 0,
                       0);
        do {
            y16 = (s16)y;
            MenuDrawString(p[0], 0x20, y16, 0, 0, 0, 0, 0);
            ret = (s32)(s16)MenuStringWidth(p[0]);
            x = (s16)(ret + 0x20);
            switch (i) {
            case 0:
                MenuDrawString(q[D_8009B198[gSelectedTrack[0]]], x, y16, 0, 0,
                               0, 0, 0);
                break;
            case 1:
                MenuDrawString(D_8009A430[gSelectedTrack[0]], x, y16, 0, 0, 0,
                               0, 0);
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
        raw = MenuTextCenterOffset(0x140, (s32)pp[0]);
        a0v = (s32)pp[0];
        a1v = (s16)raw;
        MenuDrawStringW(a0v, a1v, 0xC8, 0, 0, 0, 0, 0);
        DrawOTag((u32 *)(gOrderingTablePtr[0] + 0xFFC));
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
extern volatile u8 D_800A3360;
void MenuShowDisplay(void) {
    s32 gp;

    gp = GetGp();
    SystemSetGlobalPointer(D_8008CA4C[0]);
    SetDispMask(1);
    if (*(volatile u8 *)&D_800A3884 == 1) {
        PutDispEnv(D_800BDE04);
    }
    D_800A3360 = 1;
    asm("addu $gp, %0, $zero" : : "r"(gp));
}

extern s32 D_800A335C;
extern void func_80065C3C(void);
void MenuStartVBlankEvent(u8 mode) {
    void (*callback)(void);

    *(s32 *)D_8008CA4C = GetGp();
    if (D_800A3644[0] != 0 && D_800A3073[0] == 0) {
        callback = func_800663B0;
    } else {
        callback = func_80065C3C;
        if (mode == 2) {
            callback = MenuShowDisplay;
        }
    }
    EnterCriticalSection();
    D_800A335C = OpenEvent(0xF2000003, 2, 0x1000, callback);
    EnableEvent(*(volatile s32 *)&D_800A335C);
    SetRCnt(0xF2000003, 1, 0x1000);
    StartRCnt(0xF2000003);
    ExitCriticalSection();
}

void MenuStopVBlankEvent(void) {
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

/* Matched 2026-10-11: the two D_800A365C/D_800A39F4 setup pairs come before
 * the i/height/flag/off14/off5C init block, and the second read goes through
 * a second unknown-size array alias of gPrimitiveCursor so gcc emits a fresh
 * lui/lw per read instead of caching the address across the setup calls.
 */
void func_80066B70(void) {
    extern s32 D_800A365C;
    extern s32 D_800A39F4;
    extern u32 gPrimitiveCursor2[] asm("gPrimitiveCursor");
    s32 i;
    s32 height;
    s32 flag;
    s32 off14;
    s32 off5C;
    u8 *env;

    D_800A365C = gPrimitiveCursor[0];
    HudDrawText(D_8009A400[0], 0x8C, 0xD6, 1);
    D_800A39F4 = gPrimitiveCursor2[0];
    HudDrawText(D_8009A400[10], 0x82, 0xF1, 1);
    i = 0;
    height = 0xF0;
    flag = 8;
    off14 = 0;
    off5C = 0;
    for (i = 0; i < 2; i++) {
        env = (u8 *)D_800BDD4C + off5C;
        SetDefDrawEnv((DRAWENV *)env, (0 - (i != 0)) & 0x140, 0, 0x140, height);
        SetDefDispEnv((DISPENV *)((u8 *)D_800BDE04 + off14),
                      (0 - (i == 0)) & 0x140, 0, 0x140, height);
        D_800BDD62[off5C] = 0;
        if (gSessionTypeAbsolute[0] == 2) {
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
    if (gSessionTypeAbsolute[0] == 2) {
        D_800BDD64[0] = 1;
    }
    PutDrawEnv(D_800BDD4C);
    D_800BDDC0[0] = 1;
    D_800BDD64[0] = 1;
}

extern u32 gPrimitiveCursor2[] asm("gPrimitiveCursor");
extern u32 D_800A3570Absolute[];
extern u8 *gOtMenuStore[] asm("gOrderingTable");
extern u8 *gOtMenuBase[] asm("gOrderingTable");
extern u8 *gOtMenuLow[] asm("gOrderingTable");
extern u8 *gOtMenuMid[] asm("gOrderingTable");
extern u8 *gOtMenuHigh[] asm("gOrderingTable");
extern u8 *gOtMenuGhost[] asm("gOrderingTable");
extern u16 *D_800A389C[];
extern u16 *D_800A3898;
extern u16 *D_800A387C;
extern u16 *D_800A36BC;
extern s32 D_800A365C;
extern s32 D_800A39F4;
extern u8 D_800A36A0;
void func_80066CFC(void) {
    POLY_FT4 *dst;
    POLY_FT4 *prim;
    POLY_FT4 *next;
    POLY_FT4 *oldCursor;
    u8 *ot;
    u8 *limit;

    oldCursor = (POLY_FT4 *)gPrimitiveCursor2[0];
    GraphicsDrawRect(0, 0xD2, 0x140, 0x1E, 8, 8, 8, 0);
    func_80066B70();
    *(volatile u8 *)&D_800A36A0 = 1;
    gOtMenuStore[0] = gOrderingTables;
    ClearOTagR((u_long *)gOrderingTables, 4);
    ot = gOtMenuBase[0];
    dst = (POLY_FT4 *)(ot + 0x10);
    prim = (POLY_FT4 *)D_800A3570Absolute[0];
    limit = ot + 0x4000;
    if (prim != (POLY_FT4 *)gPrimitiveCursor[0]) {
        next = (POLY_FT4 *)(ot + 0x38);
        while (prim != (POLY_FT4 *)gPrimitiveCursor[0] && (u8 *)next < limit) {
            *dst = *prim;
            if (prim >= (POLY_FT4 *)D_800A365C) {
                if (prim == (POLY_FT4 *)D_800A365C) {
                    D_800A387C = (u16 *)dst;
                } else if (prim == (POLY_FT4 *)D_800A39F4) {
                    D_800A36BC = (u16 *)dst;
                }
                AddPrim(gOtMenuLow[0], dst);
            } else {
                if (prim == oldCursor) {
                    AddPrim(gOtMenuMid[0] + 4, dst);
                } else if (next[-1].r0 != 0xFF) {
                    AddPrim(gOtMenuHigh[0] + 0xC, dst);
                } else {
                    AddPrim(gOtMenuGhost[0] + 8, dst);
                }
            }
            prim++;
            next++;
            dst++;
        }
    }
    D_800A3898 = (u16 *)dst;
    dst = (POLY_FT4 *)(SCRATCH_TOP - 0x28);
    D_800A389C[0] = 0;
    while (prim != (POLY_FT4 *)gPrimitiveCursor[0]) {
        *dst = *prim;
        if (prim >= (POLY_FT4 *)D_800A365C) {
            if (prim == (POLY_FT4 *)D_800A365C) {
                D_800A387C = (u16 *)dst;
            } else if (prim == (POLY_FT4 *)D_800A39F4) {
                D_800A36BC = (u16 *)dst;
            }
            AddPrim(gOtMenuLow[0], dst);
        } else {
            if (prim == oldCursor) {
                AddPrim(gOtMenuMid[0] + 4, dst);
            } else {
                if (dst->r0 != 0xFF) {
                    AddPrim(gOtMenuHigh[0] + 0xC, dst);
                } else {
                    AddPrim(gOtMenuGhost[0] + 8, dst);
                }
                D_800A389C[0] = (u16 *)dst;
            }
        }
        prim++;
        dst--;
    }
    DrawOTag((u32 *)(gOtMenuBase[0] + 0xC));
    DrawSync(0);
    SetDispMask(1);
    D_800A3884 = 0;
    D_800A3930Plain = 0;
}

void MenuOffsetTexturedQuadY(POLY_FT4 *start, u8 *end, u8 delta) {
    POLY_FT4 *quad;
    if (start < end) {
        quad = start;
        do {
            if (quad->b0 != 0) {
                quad->y0 += (s8)delta;
                quad->y1 += (s8)delta;
                quad->y2 += (s8)delta;
                quad->y3 += (s8)delta;
            }
            quad++;
        } while ((u8 *)quad < end);
    }
}

void func_8006709C(u8 arg0) {
    /* Retail reaches every D_800A3848 access with its own lui, so each
     * store goes through a neighbour symbol: a shared la base would put
     * the stores in jump delay slots. */
    extern s32 D_800A3848Lui asm("D_800A3848Absolute");
    s32 cur;
    u8 arg;
    u16 *base;
    u16 *limit;

    arg = arg0;
    cur = D_800A3848Lui - ((s8)arg0 << 1);
    D_800A3848Lui = cur;
    if (cur < 0xA0) {
        D_800A3848Lui = 0xA0;
        return;
    }
    if (cur >= 0x1EB) {
        D_800A3848Lui = 0x1EA;
        return;
    }
    if (D_800A3644[0] != 0) {
        return;
    }
    base = (u16 *)gOrderingTablePtr[0];
    limit = D_800A3898;
    if (base + 8 < limit) {
        POLY_FT4 *quad;
        quad = (POLY_FT4 *)(base + 8);
        do {
            if (quad->b0 != 0) {
                quad->y0 += (s8)arg0;
                quad->y1 += (s8)arg0;
                quad->y2 += (s8)arg0;
                quad->y3 += (s8)arg0;
            }
            quad++;
        } while ((u16 *)quad < limit);
    }
    if (D_800A389C[0] == 0) {
        return;
    }
    {
        POLY_FT4 *quad;
        u16 *end;
        end = (u16 *)SCRATCH_TOP;
        for (quad = (POLY_FT4 *)D_800A389C[0]; (u16 *)quad < end; quad++) {
            if (quad->b0 != 0) {
                quad->y0 += (s8)arg;
                quad->y1 += (s8)arg;
                quad->y2 += (s8)arg;
                quad->y3 += (s8)arg;
            }
        }
    }
}

void func_80067228(void) {
    u16 *baseA;
    u16 *baseB;
    u16 *baseB2;
    POLY_FT4 *quad;
    POLY_FT4 *quad2;
    s32 i;
    s32 len;
    u32 unused[4]; /* retail reserves 16 bytes of locals nothing touches */

    baseA = D_800A387C;
    baseB = (u16 *)gOrderingTablePtr[0];
    len = strlen(D_8009A400[0]);
    baseB2 = baseB + 0x2000;
    i = 0;
    if (len > 0) {
        quad = (POLY_FT4 *)baseA;
        i = 0;
        do {
            quad->y0 = 0xF1;
            quad->y1 = 0xF1;
            quad->y2 = 0xF1;
            quad->y3 = 0xF1;
            if (quad < (POLY_FT4 *)baseB2) {
                quad++;
            } else {
                quad--;
            }
            i++;
        } while (i < len);
    }
    baseA = D_800A36BC;
    len = strlen(D_8009A400[10]);
    if (len > 0) {
        quad2 = (POLY_FT4 *)baseA;
        i = 0;
        do {
            quad2->y0 -= 0x1B;
            quad2->y1 -= 0x1B;
            quad2->y2 -= 0x1B;
            quad2->y3 -= 0x1B;
            if (quad2 < (POLY_FT4 *)baseB2) {
                quad2++;
            } else {
                quad2--;
            }
            i++;
        } while (i < len);
    }
}

/* gcc merges a later volatile redeclaration into the file-scope one, so
 * D_800A3930 is volatile from here to the end of the file. */
extern volatile s32 D_800A3930;
void func_8006733C(void) {
    extern s32 D_800A3848[];
    extern u8 *D_8009A428[];
    extern void SystemSetGlobalPointer(s32);
    extern void PadResetAndInitializeBuffersArg(s32) asm(
        "PadResetAndInitializeBuffers");
    /* Unprototyped view: the u8 prototype would truncate flag. */
    extern void func_8006709CPromoted() asm("func_8006709C");
    s32 oldGp;
    s32 input;
    s8 flag;
    u16 *baseA;
    u16 *baseB;
    u16 *baseB2;
    POLY_FT4 *quad;
    POLY_FT4 *quad2;
    s32 i;
    s32 len;
    u32 unused[4]; /* retail reserves 16 bytes of locals nothing touches */

    oldGp = GetGp();
    SystemSetGlobalPointer(D_8008CA4C[0]);
    if (DrawSync(1) == 0) {
        D_800A3930++;
        PadResetAndInitializeBuffersArg(0);
        input = PadGetButtons(0);
        if (input & 0x1000) {
            flag = 1;
        } else if (input & 0x4000) {
            flag = -1;
        } else {
            flag = -(D_800A3848[0] < 0x1EA);
        }
        if (flag != 0) {
            if ((D_800A3930 & 1) != 0) {
                func_8006709CPromoted(flag);
            }
        }
        if (*(volatile u8 *)&D_800A3884 == 1) {
            baseA = D_800A387C;
            baseB = (u16 *)gOrderingTablePtr[0];
            len = strlen(D_8009A400[0]);
            baseB2 = baseB + 0x2000;
            i = 0;
            if (len > 0) {
                quad = (POLY_FT4 *)baseA;
                i = 0;
                do {
                    quad->y0 = 0xF1;
                    quad->y1 = 0xF1;
                    quad->y2 = 0xF1;
                    quad->y3 = 0xF1;
                    if (quad < (POLY_FT4 *)baseB2) {
                        quad++;
                    } else {
                        quad--;
                    }
                    i++;
                } while (i < len);
            }
            baseA = D_800A36BC;
            len = strlen(D_8009A428[0]);
            if (len > 0) {
                quad2 = (POLY_FT4 *)baseA;
                i = 0;
                do {
                    quad2->y0 -= 0x1B;
                    quad2->y1 -= 0x1B;
                    quad2->y2 -= 0x1B;
                    quad2->y3 -= 0x1B;
                    if (quad2 < (POLY_FT4 *)baseB2) {
                        quad2++;
                    } else {
                        quad2--;
                    }
                    i++;
                } while (i < len);
            }
            D_800A3884 = 2;
        }
        PutDispEnv(&D_800BDE04[D_800A36A0]);
        PutDrawEnv(
            (DRAWENV *)((s32)D_800BDD4C + (*(volatile u8 *)&D_800A36A0) * 92));
        DrawOTag((u32 *)(gOrderingTablePtr[0] + 0xC));
        D_800A36A0 ^= 1;
    }
    D_800A3360 = 1;
    asm("addu $gp, %0, $zero" : : "r"(oldGp));
}

extern u8 gTextColorLui[] asm("gTextColor");
extern volatile u16 D_800A3940;
extern u8 D_800A3364[];
extern u32 D_800A3570Lui asm("D_800A3570Absolute");
extern u32 gPrimitiveCursorLui asm("gPrimitiveCursorAbsolute");
extern Car *gPlayerCarLui asm("gPlayerCarAbsolute");

void MenuDrawLoadScreen(void) {
    char buf[16];
    u32 textCursor;
    u32 src;
    POLY_FT4 *ft4;
    u32 end;
    s32 depth;
    POLY_GT4 *gt4;
    Car *car;
    POLY_GT4 *prim;

    func_80066B70();
    textCursor = gPrimitiveCursorLui;
    HudDrawText(gTrackNames[gSelectedTrack[0]], 0x14, 0x23, 0);
    HudDrawText(gDriverNames[gPlayerDriver[0]], 0xA0, 0xB0, 0);
    HudDrawText(D_8009A400[34], 0xA0, 0xBE, 0);
    HudDrawText(D_800A3364, 0xE0, 0xBE, 0);
    TextFormatTime(*(void **)&gPlayerCarLui->time, 0, (s32)buf);
    gTextColorLui[0] = 9;
    HudDrawText((u8 *)buf + 1, 0xEA, 0xBE, 0);
    SetGeomOffset(0xAA, 0x1E);
    gPlayerCarLui->cameraMode = 1;
    func_8002EEFC(gPlayerCarLui);
    car = gPlayerCarLui;
    car->pos.x = 0;
    car->pos.y = 0;
    car->pos.z = 0;
    car->steering = 0xA00;
    ScratchpadFillPattern(0);
    func_800168F8(gPlayerCarLui->model, (s8)(gPlayerCarLui->mode / 5));
    end = gPrimitiveCursorLui;
    CarDrawPreviewModel(gPlayerCarLui, 0, 0x15E, 0x320);
    gOrderingTableLui = (s32)gOrderingTables;
    ClearOTagR((u_long *)gOrderingTables, 0x80);
    ft4 = (POLY_FT4 *)(gOrderingTables + 0x208);
    for (src = D_800A3570Lui; src < end; src += sizeof(POLY_FT4)) {
        *ft4 = *(POLY_FT4 *)src;
        if (src == D_800A365C) {
            D_800A387C = (u16 *)ft4;
        } else if (src == D_800A39F4) {
            D_800A36BC = (u16 *)ft4;
        } else if (src >= textCursor) {
            if (src == textCursor) {
                D_800A3568 = (u8 *)ft4;
            }
            ft4->x0 -= 0x140;
            ft4->x1 -= 0x140;
            ft4->x2 -= 0x140;
            ft4->x3 -= 0x140;
        }
        setRGB0(ft4, 0x80, 0x80, 0xC0);
        AddPrim((u_long *)gOrderingTableLui, ft4);
        ft4++;
    }
    gt4 = (POLY_GT4 *)ft4;
    D_800A367C = (s32)gt4;
    depth = 0x78;
    prim = gt4;
    while (end < gPrimitiveCursorLui) {
        *gt4 = *(POLY_GT4 *)end;
        AddPrim((u_long *)gOrderingTableLui + depth, gt4);
        gt4++;
        end += sizeof(POLY_GT4);
        prim->x0 += 0x140;
        prim->x1 += 0x140;
        prim->x2 += 0x140;
        prim->x3 += 0x140;
        prim++;
        depth--;
        if (depth == 0) {
            depth = 1;
        }
    }
    D_800A3970 = (u8 *)gt4;
    D_800A3898 = func_8006654C(gt4, 0x7E);
    DrawOTag((u_long *)(gOrderingTableLui + 0x1FC));
    DrawSync(0);
    SetDispMask(1);
    *(volatile u8 *)&D_800A3884 = 0;
    D_800A3930 = -0x140;
    D_800A3940 = 4;
    D_800A36A0 = 1;
}

void func_800679C4(u8 arg0) {
    s32 shift;
    u8 arg;
    u16 *base;
    u16 *limit;
    u8 *walk;

    arg = arg0;
    base = (u16 *)D_800A3568;
    limit = (u16 *)D_800A367C;
    if (base < limit) {
        POLY_FT4 *quad;
        quad = (POLY_FT4 *)base;
        do {
            quad->x0 += (s8)arg0;
            quad->x1 += (s8)arg0;
            quad->x2 += (s8)arg0;
            quad->x3 += (s8)arg0;
            quad++;
        } while ((u16 *)quad < limit);
    }
    base = (u16 *)D_800A367C;
    limit = (u16 *)D_800A3970;
    if (base < limit) {
        POLY_GT4 *quad;
        quad = (POLY_GT4 *)base;
        do {
            quad->x0 -= (s8)arg;
            quad->x1 -= (s8)arg;
            quad->x2 -= (s8)arg;
            quad->x3 -= (s8)arg;
            quad++;
        } while ((u16 *)quad < limit);
    }
}

void func_80067AB4(void) {
    extern s32 D_8008CA4C[];
    extern u8 *gOrderingTablePtr[] asm("gOrderingTable");
    extern u8 *D_8009A428[];
    extern DISPENV D_800BDE04[];
    extern DRAWENV D_800BDD4C[];
    extern volatile u16 D_800A3940;
    extern u8 *D_800A3568;
    extern s32 D_800A367C;
    extern u8 *D_800A3970;
    extern u16 *D_800A387C;
    extern u16 *D_800A36BC;
    extern u8 D_800A36A0;
    extern u8 D_800A3884;
    extern volatile u8 D_800A3360;
    extern s32 GetGp(void);
    extern void SystemSetGlobalPointer(s32);
    s32 oldGp;
    u16 *baseA;
    u16 *baseB;
    u16 *baseB2;
    POLY_FT4 *quad;
    POLY_FT4 *quad2;
    s32 i;
    s32 len;
    u16 rawShift;
    s8 shift;
    u32 unused[4]; /* retail reserves 16 bytes of locals nothing touches */

    oldGp = GetGp();
    SystemSetGlobalPointer(D_8008CA4C[0]);
    if (DrawSync(1) == 0) {
        if (*(volatile u8 *)&D_800A3884 == 1) {
            baseA = D_800A387C;
            baseB = (u16 *)gOrderingTablePtr[0];
            len = strlen(D_8009A400[0]);
            baseB2 = baseB + 0x2000;
            i = 0;
            if (len > 0) {
                quad = (POLY_FT4 *)baseA;
                i = 0;
                do {
                    quad->y0 = 0xF1;
                    quad->y1 = 0xF1;
                    quad->y2 = 0xF1;
                    quad->y3 = 0xF1;
                    if (quad < (POLY_FT4 *)baseB2) {
                        quad++;
                    } else {
                        quad--;
                    }
                    i++;
                } while (i < len);
            }
            baseA = D_800A36BC;
            len = strlen(D_8009A428[0]);
            if (len > 0) {
                quad2 = (POLY_FT4 *)baseA;
                i = 0;
                do {
                    quad2->y0 -= 0x1B;
                    quad2->y1 -= 0x1B;
                    quad2->y2 -= 0x1B;
                    quad2->y3 -= 0x1B;
                    if (baseA < baseB2) {
                        quad2++;
                        baseA += 0x14;
                    } else {
                        quad2--;
                        baseA -= 0x14;
                    }
                    i++;
                } while (i < len);
            }
            D_800A3884 = 2;
        }
        PutDispEnv(&D_800BDE04[D_800A36A0]);
        PutDrawEnv(
            (DRAWENV *)((s32)D_800BDD4C + (*(volatile u8 *)&D_800A36A0) * 92));
        if (D_800A3940 != 0) {
            u16 *base;
            u16 *limit;
            do {
                rawShift = D_800A3940;
            } while (0);
            base = (u16 *)D_800A3568;
            limit = (u16 *)D_800A367C;
            shift = rawShift;
            if (base < limit) {
                POLY_FT4 *quad3;
                quad3 = (POLY_FT4 *)base;
                do {
                    quad3->x0 += (s8)shift;
                    quad3->x1 += (s8)shift;
                    quad3->x2 += (s8)shift;
                    quad3->x3 += (s8)shift;
                    quad3++;
                } while ((u16 *)quad3 < limit);
            }
            base = (u16 *)D_800A367C;
            limit = (u16 *)D_800A3970;
            if (base < limit) {
                POLY_GT4 *quad4;
                quad4 = (POLY_GT4 *)base;
                do {
                    quad4->x0 -= (s8)shift;
                    quad4->x1 -= (s8)shift;
                    quad4->x2 -= (s8)shift;
                    quad4->x3 -= (s8)shift;
                    quad4++;
                } while ((u16 *)quad4 < limit);
            }
            if (D_800A3930 + (s16)D_800A3940 > 0) {
                D_800A3940 = -D_800A3930;
            } else {
                D_800A3940 = D_800A3940 + (s16)D_800A3940 / 4;
            }
            D_800A3930 = D_800A3930 + (s16)D_800A3940;
        }
        DrawOTag((u32 *)(gOrderingTablePtr[0] + 0x1FC));
        D_800A36A0 ^= 1;
    }
    D_800A3360 = 1;
    asm("addu $gp, %0, $zero" : : "r"(oldGp));
}

/*
 * w4d: this TU position (after the func_80067AB4 slot) matches retail
 * address order; the C body landed on 0x80067AB4 when placed before it.
 */
extern void func_8006733C(void);
extern void func_80067AB4(void);
void MenuStartVBlankEventAlternate(void) {
    void (*callback)(void);

    *(s32 *)D_8008CA4C = GetGp();
    callback = func_8006733C;
    if (gSessionTypeAbsolute[0] == 2) {
        callback = func_80067AB4;
    }
    EnterCriticalSection();
    D_800A335C = OpenEvent(0xF2000003, 2, 0x1000, callback);
    EnableEvent(*(volatile s32 *)&D_800A335C);
    SetRCnt(0xF2000003, 1, 0x1000);
    StartRCnt(0xF2000003);
    ExitCriticalSection();
}

void MenuSetTextObject(MenuObj *obj, u8 a, u8 b, s32 c, u8 d, s32 e) {
    MenuTextPacket *p;
    p = obj->primitive;
    p->unk1 = a;
    p->unk2 = b;
    p->text = c;
    p->unk3 = d;
    p->orderingDepth = e;
    obj->orderingDepth = e;
}

u8 DriverFindIndexByName(char *name) {
    s32 i;

    for (i = 0; i < 0x18; i++) {
        if (strcmp(name, gDriverNames[i]) == 0) {
            break;
        }
    }
    return i;
}
