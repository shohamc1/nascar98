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
#include "list.h"
#include "util.h"
extern u32 gPrimitiveCursorAbsolute2[];
extern u8 D_800A2ED9Absolute2[];

extern s32 gOrderingTable[];

/* Lists and callbacks. */

void ListInsertBefore(Face **head, Face *node, Face *before) {
    Face *current;
    Face *previous;

    if (before == 0) {
        node->next = *head;
        *head = node;
        return;
    }
    current = *head;
    previous = current;
    while (current != 0) {
        if (current == before) {
            if (current == previous) {
                node->next = *head;
                *head = node;
            } else {
                node->next = current;
                previous->next = node;
            }
            return;
        }
        if (current != *head)
            previous = previous->next;
        current = current->next;
    }
}

void ListRemoveNode(Face **head, Face *target) {
    Face *current;
    Face *previous;

    current = *head;
    previous = current;
    while (current != 0) {
        if (current == target) {
            if (current == previous) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            return;
        }
        if (current != *head)
            previous = previous->next;
        current = current->next;
    }
}

void func_8001C668(void *headPointer, void *tailPointer) {
    u8 **head;
    u8 **tail;
    Face *node;
    Face *next;
    u8 *prevNode;
    u8 *temp;

    head = (u8 **)headPointer;
    tail = (u8 **)tailPointer;
    node = *head;
    next = NULL;
    prevNode = NULL;
    ((Face *)*tail)->next = NULL;
    while (node != NULL) {
        next = node->next;
        while (next != NULL) {
            if ((node->flags & 0x80) != 0 && (next->flags & 0x80) == 0) {
                {
                    Face *current;
                    Face *previous;
                    current = *head;
                    previous = current;
                    while (current != 0) {
                        if (current == node) {
                            if (current == previous) {
                                *head = current->next;
                            } else {
                                previous->next = current->next;
                            }
                            goto remove1Done;
                        }
                        if (current != *head)
                            previous = previous->next;
                        current = current->next;
                    }
                remove1Done:;
                }
                {
                    Face *current;
                    Face *previous;
                    if (next == 0) {
                        node->next = *head;
                        *head = node;
                        goto insert2Done;
                    }
                    current = *head;
                    previous = current;
                    while (current != 0) {
                        if (current == next) {
                            if (current == previous) {
                                node->next = *head;
                                *head = node;
                            } else {
                                node->next = current;
                                previous->next = node;
                            }
                            goto insert2Done;
                        }
                        if (current != *head)
                            previous = previous->next;
                        current = current->next;
                    }
                insert2Done:;
                }
                {
                    Face *current;
                    Face *previous;
                    current = *head;
                    previous = current;
                    while (current != 0) {
                        if (current == next) {
                            if (current == previous) {
                                *head = current->next;
                            } else {
                                previous->next = current->next;
                            }
                            goto remove3Done;
                        }
                        if (current != *head)
                            previous = previous->next;
                        current = current->next;
                    }
                remove3Done:;
                }
                {
                    Face *current;
                    Face *previous;
                    if (prevNode == 0) {
                        next->next = *head;
                        *head = next;
                        goto insert4Done;
                    }
                    current = *head;
                    previous = current;
                    while (current != 0) {
                        if (current == prevNode) {
                            if (current == previous) {
                                next->next = *head;
                                *head = next;
                            } else {
                                next->next = current;
                                previous->next = next;
                            }
                            goto insert4Done;
                        }
                        if (current != *head)
                            previous = previous->next;
                        current = current->next;
                    }
                insert4Done:;
                }
                temp = next;
                next = node;
                node = temp;
            }
            next = next->next;
        }
        prevNode = node;
        next = node;
        node = next->next;
    }
    *tail = next;
}

void ListPushFront(Face *node, u8 **head, u8 **tail) {
    u8 *oldHead;
    oldHead = *head;
    if (oldHead == 0) {
        *tail = node;
        *head = node;
        node->next = 0;
    } else {
        node->next = oldHead;
        *head = node;
    }
}

void ListRemoveNodeWithTail(Face *node, Face **head, Face **tail) {
    Face *previous;
    Face *current;
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

void RenderTransformVerticesWithOffset(TrackCallback *object) {
    s32 i;
    s32 *vec;
    ModelVertex *el;
    u8 *base;

    base = D_800BE97C[0];
    vec = object->offset;
    func_8001F2C4(0, 0, (D_800A2EC0Absolute[0] & 0x1F) << 5);
    for (i = 0; i < object->count; i++) {
        el = base + object->index[i] * 0x14;
        el->local.vx = (u16)object->coord[i][0];
        el->local.vy = (u16)object->coord[i][1];
        el->local.vz = (u16)object->coord[i][2];
        MatrixTransformVector((s32 *)el);
        el->world.x = el->local.vx + vec[0];
        el->world.y = el->local.vy + vec[1];
        el->world.z = el->local.vz + vec[2];
    }
}

void func_8001CAB8(TrackCallback *arg0) {
    s32 i;
    s32 *vec;
    ModelVertex *el;
    u8 *base;
    s32 temp;

    temp = (D_800A2EC0Absolute[0] & 0x1F) << 5;
    base = D_800BE97C[0];
    vec = arg0->offset;
    func_8001F2C4(temp, 0, temp);
    for (i = 0; i < arg0->count; i++) {
        el = base + arg0->index[i] * 0x14;
        el->local.vx = (u16)arg0->coord[i][0];
        el->local.vy = (u16)arg0->coord[i][1];
        el->local.vz = (u16)arg0->coord[i][2];
        MatrixTransformVector((s32 *)el);
        el->world.x = el->local.vx + vec[0];
        el->world.y = el->local.vy + vec[1];
        el->world.z = el->local.vz + vec[2];
    }
}

void func_8001CBD4(TrackCallback *arg0) {
    s32 temp;
    s32 i;
    s32 idx;
    s32 val;
    s32 base;
    s32 strideNeg;
    u8 *table;
    volatile s32 framePad[2];
    temp = D_800A2EC0Absolute[0] & 0x3F;
    table = D_800BE97C[0];
    if (temp < 0x20) {
        temp = temp - 0x20;
    } else {
        temp = 0x20 - temp;
    }
    if (arg0->count > 0) {
        do {
            i = 0;
            strideNeg = -(temp * 0x14);
        } while (0);
        do {
            idx = arg0->index[i];
            val = arg0->coord[i][2];
            base = arg0->offset[2];
            ((ModelVertex *)table)[idx].world.z = (val + base) + strideNeg;
            i += 1;
        } while (i < arg0->count);
    }
}

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
extern Face *D_800A3A40Absolute[];

/* Sets up a shade-tex primitive (0x2C entry) from the D_800A3A40 pool:
   entry +0xE tpage, +0xA clut (first arm only), +8..+0x15 palette bytes. */
void func_8001CC7C(TrackCallback *arg0) {
    s32 idx;
    s32 pal;
    s32 c;
    Face *entry;

    if (arg0->count != 4) {
        return;
    }
    entry = (u8 *)D_800A3A40Absolute[0] +
            ((arg0->index[4] * 2 + arg0->index[4]) * 4 - arg0->index[4]) * 4;
    SetShadeTex(entry, 1);
    if (D_800A2EC8Absolute[0] != 0) {
        entry->tpage = GetTPage(1, 0, 0x200, 0x100);
        entry->clut = GetClut(0x200, 0x1FF);
        entry->u0 = 0;
        entry->v0 = 0xA7;
        entry->u1 = 0;
        entry->v1 = 0xFD;
        entry->u2 = 0x7F;
        entry->v2 = 0xA7;
        entry->u3 = 0x7F;
        entry->v3 = 0xFD;
        return;
    }
    pal = D_800A2ED9Absolute2[0];
    if (pal != 0) {
        pal = 0x40;
        c = 0x78;
        entry->u0 = pal;
        entry->u1 = pal;
        pal = 0xBF;
        entry->v0 = 0;
        entry->v1 = c;
        entry->u2 = pal;
        entry->v2 = 0;
        entry->u3 = pal;
        entry->v3 = c;
    } else {
        pal = 0x40;
        c = 0x3C;
        entry->u0 = pal;
        entry->u1 = pal;
        pal = 0xBF;
        entry->v0 = c;
        entry->v1 = pal;
        entry->u2 = pal;
        entry->v2 = c;
        entry->u3 = pal;
        entry->v3 = c;
    }
    if (gOrderingTableBankAbsolute[0] != 0) {
        entry->tpage = GetTPage(2, 0, 0, 0);
    } else {
        entry->tpage = GetTPage(2, 0, 0x140, 0);
    }
}
#else
extern Face *D_800A3A40Absolute[];

void func_8001CC7C(TrackCallback *arg0) {
    s32 pal;
    u16 clut;
    s32 c;
    s32 d;
    Face *entry;
    if (arg0->count != 4) {
        return;
    }
    entry =
        ((u8 *)D_800A3A40Absolute[0]) +
        (((((arg0->index[4] * 2) + arg0->index[4]) * 4) - arg0->index[4]) * 4);
    SetShadeTex(entry, 1);
    if (D_800A2EC8Absolute[0] != 0) {
        entry->tpage = GetTPage(1, 0, 0x200, 0x100);
        clut = GetClut(0x200, 0x1FF);
        d = 0xA7;
        c = 0xFD;
        entry->clut = clut;
        pal = 0x7F;
        entry->u0 = 0;
        entry->v0 = d;
        entry->u1 = 0;
        entry->v1 = 0xFD;
        entry->u2 = 0x7F;
        entry->v2 = d;
        entry->u3 = pal;
        entry->v3 = c;
        return;
    }
    pal = D_800A2ED9Absolute2[0];
    if (pal != 0) {
        pal = 0x40;
        c = 0x78;
        entry->u0 = pal;
        entry->u1 = pal;
        pal = 0xBF;
        entry->v0 = 0;
        entry->v1 = c;
        entry->u2 = pal;
        entry->v2 = 0;
        entry->u3 = pal;
        entry->v3 = c;
    } else {
        pal = 0x40;
        c = 0x3C;
        entry->u0 = pal;
        entry->u1 = pal;
        pal = 0xBF;
        entry->v0 = c;
        entry->v1 = pal;
        entry->u2 = pal;
        entry->v2 = c;
        entry->u3 = pal;
        entry->v3 = pal;
    }
    if (gOrderingTableBankAbsolute[0] != 0) {
        entry->tpage = GetTPage(2, 0, 0, 0);
    } else {
        entry->tpage = GetTPage(2, 0, 0x140, 0);
    }
}

#endif
extern Face *D_800A3A40Absolute[];

void func_8001CDDC(TrackCallback *arg0) {
    s32 pal;
    s32 c;
    s32 d;
    Face *entry;
    if (arg0->count != 4) {
        return;
    }
    entry =
        ((u8 *)D_800A3A40Absolute[0]) +
        (((((arg0->index[4] * 2) + arg0->index[4]) * 4) - arg0->index[4]) * 4);
    SetShadeTex(entry, 1);
    if (D_800A2EC8Absolute[0] != 0) {
        d = 0x100;
        do {
            entry->tpage = GetTPage(1, 0, 0x200, d);
            entry->clut = GetClut(0x200, 0x1FF);
        } while (0);
        pal = 0x80;
        c = 0xA7;
        d = 0xFD;
        entry->u0 = pal;
        entry->u1 = pal;
        pal = 0x9F;
        entry->v0 = c;
        entry->v1 = d;
        entry->u2 = pal;
        entry->v2 = c;
        entry->u3 = pal;
        entry->v3 = d;
        return;
    }
    pal = D_800A2ED9Absolute2[0];
    if (pal != 0) {
        d = 0x78;
        pal = 0x1F;
        entry->u0 = 0;
        entry->v0 = 0;
        entry->u1 = 0;
        entry->v1 = d;
        entry->u2 = pal;
        entry->v2 = 0;
    } else {
        c = 0x3C;
        d = 0xBF;
        pal = 0x1F;
        entry->u0 = 0;
        entry->v0 = c;
        entry->u1 = 0;
        entry->v1 = d;
        entry->u2 = pal;
        entry->v2 = c;
    }
    entry->u3 = pal;
    entry->v3 = d;
    if (gOrderingTableBankAbsolute[0] != 0) {
        entry->tpage = GetTPage(2, 0, 0xC0, 0);
    } else {
        entry->tpage = GetTPage(2, 0, 0x200, 0);
    }
}

void func_8001CF38(TrackCallback *arg0) {
    s32 pal;
    s32 c;
    s32 d;
    Face *entry;
    if (arg0->count != 4) {
        return;
    }
    entry =
        ((u8 *)D_800A3A40Absolute[0]) +
        (((((arg0->index[4] * 2) + arg0->index[4]) * 4) - arg0->index[4]) * 4);
    SetShadeTex(entry, 1);
    if (D_800A2EC8Absolute[0] != 0) {
        entry->tpage = GetTPage(1, 0, 0x200, 0x100);
        entry->clut = GetClut(0x200, 0x1FF);
        do {
            pal = 0xA0;
            d = 0xA7;
            c = 0xFD;
            entry->u0 = pal;
            entry->u1 = pal;
            pal = 0xBF;
        } while (0);
        entry->v0 = d;
        entry->v1 = c;
        entry->u2 = pal;
        entry->v2 = d;
        entry->u3 = pal;
        entry->v3 = c;
        return;
    }
    pal = D_800A2ED9Absolute2[0];
    if (pal != 0) {
        pal = 0x20;
        c = 0x78;
        entry->u0 = pal;
        entry->u1 = pal;
        pal = 0x3F;
        entry->v0 = 0;
        entry->v1 = c;
        entry->u2 = pal;
        entry->v2 = 0;
    } else {
        pal = 0x20;
        d = 0x3C;
        c = 0xBF;
        entry->u0 = pal;
        entry->u1 = pal;
        pal = 0x3F;
        entry->v0 = d;
        entry->v1 = c;
        entry->u2 = pal;
        entry->v2 = d;
    }
    entry->u3 = pal;
    entry->v3 = c;
    if (gOrderingTableBankAbsolute[0] != 0) {
        entry->tpage = GetTPage(2, 0, 0xC0, 0);
    } else {
        entry->tpage = GetTPage(2, 0, 0x200, 0);
    }
}

extern void (*D_80091080[])(void *);
void ListDispatchCallbacks(TrackSection *owner) {
    TrackCallback *node;
    void (*callback)(void *);
    node = owner->callbacks;
    while (node != 0) {
        callback = D_80091080[node->callback];
        callback(node);
        node = node->next;
    }
}

void func_8001D108(u8 *arg0) {
    s32 flags;
    u8 *vertexPtr;
    s32 index;
    u8 *flagPtr;
    u8 *obj;
    SVECTOR vertex;
    s32 masked;

    obj = arg0;
    flags = -1;
    vertexPtr = obj + 0x54;
    index = 0;
    flagPtr = obj + 0x5A;
again:
    vertex.vx = ((SVECTOR *)vertexPtr)->vx;
    vertex.vy = ((SVECTOR *)(flagPtr - 6))->vy;
    vertex.vz = ((SVECTOR *)(flagPtr - 6))->vz;
    RotTransPers_nom(&vertex);
    func_8003382C(vertexPtr);
    masked = flags & 0x7EF6;
    flags = *(u16 *)flagPtr & masked;
    flagPtr += 8;
    vertexPtr += 8;
    if (++index < 4) {
        goto again;
    }
    *(s16 *)&((TrackSection *)obj)->culled = flags;
}

void RenderCopyVertexCoordinates(s32 *destination, s32 *source) {
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

extern s32 D_800A2DEC[];
extern s32 D_800A2DF0[];
extern s32 D_800A37E8[];
extern s32 D_800A397C[];
void func_8001D1E4(void) {
    D_800A2DEC[0] = 0;
    D_800A2DF0[0] = 1;
    D_800A37E8[0] = 0;
    gReplayIndex[0] = 0;
    D_800A397C[0] = 1;
}

void func_8001D218(void) {
}

extern s32 D_800A2DB0;
extern s32 D_800A2DB4;
extern POLY_F4 D_800A3BBC[];
extern POLY_F3 D_800A3B58[];
extern u32 D_800A35C0[];

/* Draws a horizontal gauge: one POLY_F4 bar, colorIdx 0 to 3 for green, red,
   yellow or blue, whose length is value / (scale * 4) of 250 pixels, then five
   POLY_F3 markers a quarter of 250 pixels apart. A negative value repeats the
   previous one. The bar cycles through four buffers. */
void DebugDrawMeterBar(s32 value, s32 scale, s32 y, s32 colorIdx) {
    POLY_F4 *bar;
    POLY_F3 *mark;
    POLY_FT4 *entry;
    u32 cursor;
    POLY_FT4 *entry2;
    u32 cursor2;
    s32 den;
    s32 quot;
    s32 rem;
    s32 fixed;
    s32 step;
    s32 x;
    s32 i;
    s32 one;
    s32 four;
    s32 quot2;
    s32 fixed2;

    bar = &D_800A3BBC[D_800A2DB0];
    D_800A2DB0 = D_800A2DB0 + 1;
    if (D_800A2DB0 >= 4) {
        D_800A2DB0 = 0;
    }
    if (value < 0) {
        value = D_800A2DB4;
    } else {
        D_800A2DB4 = value;
    }
    den = scale * 4;
    if (den == 0) {
        fixed = 0x7FFFFFFF;
    } else {
        scale = den;
        quot = value / scale;
        rem = value % scale;
        rem = (rem << 15) / scale;
        rem <<= 1;
        fixed = (quot << 16) + rem;
    }
    step = MathMultiplyFixed16(fixed, 0xFA0000) >> 16;
    SetPolyF4(bar);
    bar->x0 = 0x1E;
    bar->y0 = y;
    bar->x1 = step + 0x1E;
    bar->y1 = y;
    bar->x2 = 0x1E;
    bar->y2 = y + 5;
    bar->x3 = step + 0x1E;
    bar->y3 = y + 5;
    switch (colorIdx) {
    case 1:
        bar->r0 = 0xFF;
        bar->g0 = 0;
        bar->b0 = 0;
        break;
    case 0:
        bar->r0 = 0;
        bar->g0 = 0xFF;
        bar->b0 = 0;
        break;
    case 2:
        bar->r0 = 0xFF;
        bar->g0 = 0xFF;
        bar->b0 = 0;
        break;
    case 3:
        bar->r0 = 0;
        bar->g0 = 0;
        bar->b0 = 0xFF;
        break;
    }
    cursor = gPrimitiveCursor[0];
    gPrimitiveCursorAbsolute2[0] = cursor + sizeof(POLY_FT4);
    entry = (POLY_FT4 *)cursor;
    *entry = *(POLY_FT4 *)bar;
    AddPrim((u8 *)gOrderingTable[0], entry);
    one = 1;
    four = 4;
    quot2 = one / four;
    rem = one % four;
    rem <<= 15;
    rem /= four;
    rem <<= 1;
    fixed2 = (quot2 << 16) + rem;
    step = MathMultiplyFixed16(fixed2, 0xFA0000) >> 16;
    x = 0x1E;
    y = y - 1;
    for (i = 0; i < 5; i++) {
        mark = &D_800A3B58[i];
        SetPolyF3(mark);
        mark->x0 = x;
        mark->y0 = y;
        mark->x1 = x - 4;
        mark->y1 = y - 4;
        mark->x2 = x + 4;
        mark->y2 = y - 4;
        switch (i) {
        case 0:
            mark->r0 = 0;
            mark->g0 = 0xFF;
            mark->b0 = 0;
            break;
        case 1:
            mark->r0 = 0x80;
            mark->g0 = 0xFF;
            mark->b0 = 0;
            break;
        case 2:
            mark->r0 = 0xFF;
            mark->g0 = 0xFF;
            mark->b0 = 0;
            break;
        case 3:
            mark->r0 = 0xFF;
            mark->g0 = 0x80;
            mark->b0 = 0;
            break;
        case 4:
            mark->r0 = 0xFF;
            mark->g0 = 0;
            mark->b0 = 0;
            break;
        }
        cursor2 = gPrimitiveCursor[0];
        gPrimitiveCursorAbsolute2[0] = cursor2 + sizeof(POLY_FT4);
        entry2 = (POLY_FT4 *)cursor2;
        *entry2 = *(POLY_FT4 *)mark;
        AddPrim((u8 *)gOrderingTable[0], entry2);
        x += step;
    }
}

extern POLY_F3 D_800A3C1C[];

/* Draws the selection triangle: apex at (x, y) and base at x +/-
   twice the size, pointing left for dir 0 and right for dir 1. Any
   other dir leaves the SetPolyF3 template's vertices alone. */
void MenuDrawArrow(s32 x, s32 y, s32 dir, s32 size) {
    POLY_F3 *prim;
    POLY_FT4 *entry;
    u32 cursor;
    s32 width;
    s32 x2;
    s32 y1;

    width = size << 1;
    prim = &D_800A3C1C[gOrderingTableBankAbsolute[0]];
    SetPolyF3(prim);
    switch (dir) {
    case 0:
        x2 = x - width;
        prim->x0 = x;
        y1 = y - size;
        prim->x1 = x2;
        prim->x2 = x2;
        prim->y0 = y;
        prim->y1 = y1;
        prim->y2 = y + size;
        break;
    case 1:
        x2 = x + width;
        prim->x0 = x;
        y1 = y - size;
        prim->x1 = x2;
        prim->x2 = x2;
        prim->y0 = y;
        prim->y1 = y1;
        prim->y2 = y + size;
        break;
    default:
        goto color;
    }
color:
    prim->r0 = 0xFF;
    prim->g0 = 0;
    prim->b0 = 0;
    cursor = gPrimitiveCursor[0];
    gPrimitiveCursorAbsolute2[0] = cursor + sizeof(POLY_FT4);
    entry = (POLY_FT4 *)cursor;
    *entry = *(POLY_FT4 *)prim;
    AddPrim((u8 *)gOrderingTable[0], entry);
}
extern POLY_FT4 D_800A3C6C[];
void GraphicsDrawRect(s32 x, s32 y, s32 w, s32 h, u8 r, u8 g, u8 b,
                      s32 semiTrans) {
    POLY_FT4 *prim;
    POLY_FT4 *entry;
    u32 cursor;

    prim = &D_800A3C6C[gOrderingTableBankAbsolute[0]];
    SetPolyFT4(prim);
    prim->y0 = y;
    prim->y1 = y;
    prim->x0 = x;
    prim->x1 = x + w;
    prim->x2 = x;
    prim->y2 = y + h;
    prim->x3 = x + w;
    prim->y3 = y + h;
    prim->tpage = GetTPage(2, 0, 0x300, 0);
    prim->u0 = 0;
    prim->v0 = 0;
    prim->u1 = 1;
    prim->v1 = 0;
    prim->u2 = 0;
    prim->v2 = 1;
    prim->u3 = 1;
    prim->v3 = 1;
    if ((semiTrans << 0x18) != 0) {
        SetSemiTrans(prim, 1);
    }
    prim->r0 = r;
    prim->g0 = g;
    prim->b0 = b;
    cursor = gPrimitiveCursor[0];
    /* Store through the neighbour label: keeps the second lui. */
    gPrimitiveCursorAbsolute2[0] = cursor + sizeof(POLY_FT4);
    entry = (POLY_FT4 *)cursor;
    *entry = *prim;
    AddPrim((u8 *)gOrderingTable[0], entry);
}

extern POLY_F4 D_800A3D0C[];
extern s32 D_800A2DB8;
void GraphicsDrawFlatRect(s32 x, s32 y, s32 w, s32 h, u8 r, u8 g, u8 b,
                          s32 semiTrans) {
    POLY_F4 *poly;

    poly = &D_800A3D0C[D_800A2DB8];
    SetPolyF4(poly);
    D_800A2DB8 = (D_800A2DB8 + 1) % 24;
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + w;
    poly->y1 = y;
    poly->x2 = x;
    poly->y2 = y + h;
    poly->x3 = x + w;
    poly->y3 = y + h;
    if ((semiTrans << 0x18) != 0) {
        SetSemiTrans(poly, 1);
    }
    poly->r0 = r;
    poly->g0 = g;
    poly->b0 = b;
    AddPrim((u8 *)gOrderingTable[0], poly);
}

extern POLY_F4 D_800A3F4C[];
extern s32 D_800A2DBC;
void func_8001DA48(u8 *ot, s32 x, s32 y, s32 w, s32 h) {
    POLY_F4 *poly;
    s32 i;

    i = D_800A2DBC;
    poly = &D_800A3F4C[i];
    D_800A2DBC = i + 1;
    if (i + 1 >= 2) {
        D_800A2DBC = 0;
    }
    SetPolyF4(poly);
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + w;
    poly->y1 = y;
    poly->x2 = x;
    poly->y2 = y + h;
    poly->x3 = x + w;
    poly->y3 = y + h;
    poly->r0 = 2;
    poly->g0 = 0;
    poly->b0 = 0;
    AddPrim(ot, poly);
}

extern ImageBankTexture *GraphicsGetImageBankTexture(s32);
extern void func_80032D94(s8 *);

typedef struct {
    s16 x;
    s16 y;
} XyPair;

void func_8001DB20(Face *arg0, s32 arg1) {
    POLY_FT4 poly;
    POLY_FT4 *prim;
    ImageBankTexture *tex;
    u8 *vert;
    u8 flag;
    u8 r;
    u8 g;
    u8 b;
    s32 i;
    s32 x;
    s32 y;
    s32 mode;
    s32 saved;
    s32 pad[8];

    flag = arg0->flags;
    mode = arg1;
    vert = (u8 *)arg0;
    if ((flag & 1) != 0) {
        return;
    }
    prim = &poly;
    if (arg0->vertexCount != 3) {
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        prim->r0 = 0x80;
        prim->g0 = 0x80;
        prim->b0 = 0x80;
        prim->tpage = GetTPage(2, 0, 0x280, 0);
        prim->u0 = 0x80;
        prim->v0 = 0;
        prim->u1 = 0xFF;
        prim->v1 = 0;
        prim->u2 = 0x80;
        prim->v2 = 0x7F;
        prim->u3 = 0xFF;
        prim->v3 = 0x7F;
    } else {
        SetPolyFT3((POLY_FT3 *)prim);
        SetShadeTex(prim, 0);
        prim->r0 = 0x80;
        prim->g0 = 0x80;
        prim->b0 = 0x80;
        prim->tpage = GetTPage(2, 0, 0x280, 0);
        prim->u0 = 0x80;
        prim->v0 = 0;
        prim->u1 = 0xFF;
        prim->v1 = 0;
        prim->u2 = 0xFF;
        prim->v2 = 0x7F;
    }
    tex = 0;
    if (arg0->angle >= 0) {
        tex = GraphicsGetImageBankTexture(arg0->angle);
    }
    saved = arg0->depth;
    if (tex != 0) {
        if (mode != 0) {
            prim->tpage = GetTPage(tex->mode, 0, tex->x - 0x100, tex->y);
            x = tex->clutX;
            x = x - 0x100;
            y = tex->clutY;
        } else {
            prim->tpage = GetTPage(tex->mode, 0, tex->x, tex->y);
            x = tex->clutX;
            y = tex->clutY;
        }
        prim->clut = GetClut(x, y);
        for (i = 0; i < 4; i++) {
            vert[i * 4 + 8] = vert[i * 4 + 8] + tex->u;
            vert[i * 4 + 9] = vert[i * 4 + 9] + tex->v;
        }
        if (*(s32 *)&arg0->r0 < 0) {
            SetSemiTrans(prim, 1);
        }
    } else {
        for (i = 0; i < 4; i++) {
            vert[i * 4 + 8] = 0;
            vert[i * 4 + 9] = 0;
        }
        vert[8] = 0;
        vert[9] = 0;
        vert[0xC] = 0x7F;
        vert[0xD] = 0;
        vert[0x10] = 0;
        vert[0x11] = 0x7F;
        vert[0x14] = 0x7F;
        vert[0x15] = 0x7F;
        if (mode == 0) {
            arg0->type = 3;
            arg0->depth = 0;
            r = arg0->b0;
            g = arg0->g0;
            b = arg0->r0;
            prim->r0 = r;
            prim->g0 = g;
            prim->b0 = b;
            if (arg0->vertexCount != 3) {
                SetPolyF4((POLY_F4 *)prim);
                if (*(s32 *)&arg0->r0 < 0) {
                    SetSemiTrans(prim, 1);
                }
                arg0->depth = 0x10;
            } else {
                SetPolyF3((POLY_F3 *)prim);
                if (*(s32 *)&arg0->r0 < 0) {
                    SetSemiTrans(prim, 1);
                }
            }
        }
    }
    if (mode != 0) {
        if (arg0->vertexCount == 3) {
            SetPolyFT4(prim);
            arg0->vertex[3] = (s32)arg0->vertex[2];
            /* vert is arg0 as bytes: copy the u2, v2 word over u3, v3.
             * Retail addresses it through vert, not arg0. */
            *(XyPair *)(vert + 0x14) = *(XyPair *)(vert + 0x10);
        }
    } else {
        if (arg0->vertexCount == 3) {
            arg0->vertex[3] = (s32)arg0->vertex[2];
            /* vert is arg0 as bytes: copy the u2, v2 word over u3, v3.
             * Retail addresses it through vert, not arg0. */
            *(XyPair *)(vert + 0x14) = *(XyPair *)(vert + 0x10);
            if (arg0->type == 6) {
                arg0->code = arg0->b0;
            }
        }
        if (arg0->type < 3) {
            SetPolyGT4((POLY_GT4 *)prim);
            arg0->type = 6;
            *(s32 *)&arg0->r0 = 0x80808080;
        }
    }
    r = arg0->b0;
    g = arg0->g0;
    b = arg0->r0;
    prim->r0 = r;
    prim->g0 = g;
    prim->b0 = b;
    if (*(s32 *)&arg0->r0 < 0) {
        SetSemiTrans(prim, 1);
    }
    if (*(s32 *)&arg0->r0 == 0xADADAD || *(s32 *)&arg0->r0 == 0xFFFFFF) {
        arg0->flags = arg0->flags & 0xEF;
    } else {
        arg0->flags = arg0->flags | 0x10;
    }
    arg0->len = ((Face *)prim)->len;
    if (arg0->type != 6) {
        *(s32 *)&arg0->r0 = *(s32 *)&prim->r0;
    }
    arg0->clut = prim->clut;
    arg0->tpage = prim->tpage;
    if (mode == 0) {
        arg0->depth = saved;
    }
    func_80032D94((s8 *)arg0);
}

extern s32 D_800BE978[];

extern void func_8001DB20(Face *, s32);

void RenderDrawGeometryList(void) {
    s32 count;
    s32 i;

    count = D_800BE978[0];
    i = 0;
    while (i < count) {
        func_8001DB20((Face *)((u8 *)D_800A3A40Absolute[0] + i * 0x2C), 1);
        i += 1;
    }
}

void RenderDrawFiveLinkedLists(void) {
    extern Face D_800AE8C0[];
    s32 offset;
    s32 i;
    Face *node;
    i = 0;
    offset = 0;
    do {
        node = *(Face **)((u8 *)D_800AE8C0 + offset);
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
