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

extern s32 gOrderingTable[];

/* Lists and callbacks. */

struct RenderListNode {
    u8 unk0[0x28];
    RenderListNode *next;
};

void ListInsertBefore(RenderListNode **head, RenderListNode *node,
                      RenderListNode *before) {
    RenderListNode *current;
    RenderListNode *previous;

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

void ListRemoveNode(RenderListNode **head, RenderListNode *target) {
    RenderListNode *current;
    RenderListNode *previous;

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
    u8 *node;
    u8 *next;
    u8 *prevNode;
    u8 *temp;

    head = (u8 **)headPointer;
    tail = (u8 **)tailPointer;
    node = *head;
    next = NULL;
    prevNode = NULL;
    *(u8 **)(*tail + 0x28) = 0;
    while (node != NULL) {
        next = *(u8 **)(node + 0x28);
        while (next != NULL) {
            if ((node[0x13] & 0x80) != 0 && (next[0x13] & 0x80) == 0) {
                {
                    u8 *current;
                    u8 *previous;
                    current = *head;
                    previous = current;
                    while (current != 0) {
                        if (current == node) {
                            if (current == previous) {
                                *head = *(u8 **)(current + 0x28);
                            } else {
                                *(u8 **)(previous + 0x28) =
                                    *(u8 **)(current + 0x28);
                            }
                            goto remove1Done;
                        }
                        if (current != *head)
                            previous = *(u8 **)(previous + 0x28);
                        current = *(u8 **)(current + 0x28);
                    }
                remove1Done:;
                }
                {
                    u8 *current;
                    u8 *previous;
                    if (next == 0) {
                        *(u8 **)(node + 0x28) = *head;
                        *head = node;
                        goto insert2Done;
                    }
                    current = *head;
                    previous = current;
                    while (current != 0) {
                        if (current == next) {
                            if (current == previous) {
                                *(u8 **)(node + 0x28) = *head;
                                *head = node;
                            } else {
                                *(u8 **)(node + 0x28) = current;
                                *(u8 **)(previous + 0x28) = node;
                            }
                            goto insert2Done;
                        }
                        if (current != *head)
                            previous = *(u8 **)(previous + 0x28);
                        current = *(u8 **)(current + 0x28);
                    }
                insert2Done:;
                }
                {
                    u8 *current;
                    u8 *previous;
                    current = *head;
                    previous = current;
                    while (current != 0) {
                        if (current == next) {
                            if (current == previous) {
                                *head = *(u8 **)(current + 0x28);
                            } else {
                                *(u8 **)(previous + 0x28) =
                                    *(u8 **)(current + 0x28);
                            }
                            goto remove3Done;
                        }
                        if (current != *head)
                            previous = *(u8 **)(previous + 0x28);
                        current = *(u8 **)(current + 0x28);
                    }
                remove3Done:;
                }
                {
                    u8 *current;
                    u8 *previous;
                    if (prevNode == 0) {
                        *(u8 **)(next + 0x28) = *head;
                        *head = next;
                        goto insert4Done;
                    }
                    current = *head;
                    previous = current;
                    while (current != 0) {
                        if (current == prevNode) {
                            if (current == previous) {
                                *(u8 **)(next + 0x28) = *head;
                                *head = next;
                            } else {
                                *(u8 **)(next + 0x28) = current;
                                *(u8 **)(previous + 0x28) = next;
                            }
                            goto insert4Done;
                        }
                        if (current != *head)
                            previous = *(u8 **)(previous + 0x28);
                        current = *(u8 **)(current + 0x28);
                    }
                insert4Done:;
                }
                temp = next;
                next = node;
                node = temp;
            }
            next = *(u8 **)(next + 0x28);
        }
        prevNode = node;
        next = node;
        node = *(u8 **)(next + 0x28);
    }
    *tail = next;
}

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

void ListRemoveNodeWithTail(RenderListNode *node, RenderListNode **head,
                            RenderListNode **tail) {
    RenderListNode *previous;
    RenderListNode *current;
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

void RenderTransformVerticesWithOffset(u8 *object) {
    s32 i;
    s32 *vec;
    u8 *el;
    u8 *base;

    base = D_800BE97C[0];
    vec = (s32 *)(object + 0x210);
    func_8001F2C4(0, 0, (D_800A2EC0Absolute[0] & 0x1F) << 5);
    for (i = 0; i < *(s16 *)(object + 0xA); i++) {
        el = base + *(u16 *)(object + 0x10 + i * 2) * 0x14;
        *(u16 *)(el + 0) = *(u16 *)(object + 0x90 + i * 6);
        *(u16 *)(el + 2) = *(u16 *)(object + 0x92 + i * 6);
        *(u16 *)(el + 4) = *(u16 *)(object + 0x94 + i * 6);
        MatrixTransformVector((s32 *)el);
        *(s32 *)(el + 8) = *(s16 *)(el + 0) + vec[0];
        *(s32 *)(el + 12) = *(s16 *)(el + 2) + vec[1];
        *(s32 *)(el + 16) = *(s16 *)(el + 4) + vec[2];
    }
}

void func_8001CAB8(u8 *arg0) {
    s32 i;
    s32 *vec;
    u8 *el;
    u8 *base;
    s32 temp;

    temp = (D_800A2EC0Absolute[0] & 0x1F) << 5;
    base = D_800BE97C[0];
    vec = (s32 *)(arg0 + 0x210);
    func_8001F2C4(temp, 0, temp);
    for (i = 0; i < *(s16 *)(arg0 + 0xA); i++) {
        el = base + *(u16 *)(arg0 + 0x10 + i * 2) * 0x14;
        *(u16 *)(el + 0) = *(u16 *)(arg0 + 0x90 + i * 6);
        *(u16 *)(el + 2) = *(u16 *)(arg0 + 0x92 + i * 6);
        *(u16 *)(el + 4) = *(u16 *)(arg0 + 0x94 + i * 6);
        MatrixTransformVector((s32 *)el);
        *(s32 *)(el + 8) = *(s16 *)(el + 0) + vec[0];
        *(s32 *)(el + 12) = *(s16 *)(el + 2) + vec[1];
        *(s32 *)(el + 16) = *(s16 *)(el + 4) + vec[2];
    }
}

void func_8001CBD4(u8 *arg0) {
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
    if ((*((s16 *)(arg0 + 0xA))) > 0) {
        do {
            i = 0;
            strideNeg = -(temp * 0x14);
        } while (0);
        do {
            idx = *((u16 *)((arg0 + 0x10) + (i * 2)));
            val = *((s16 *)((arg0 + 0x94) + (i * 6)));
            base = *((s32 *)(arg0 + 0x218));
            *((s32 *)((table + (idx * 0x14)) + 0x10)) =
                (val + base) + strideNeg;
            i += 1;
        } while (i < (*((s16 *)(arg0 + 0xA))));
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
extern RenderListNode *D_800A3A40Absolute[];

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
extern RenderListNode *D_800A3A40Absolute[];

void func_8001CC7C(u8 *arg0) {
    s32 pal;
    u16 clut;
    s32 c;
    s32 d;
    u8 *entry;
    if ((*((s16 *)(arg0 + 0xA))) != 4) {
        return;
    }
    entry =
        ((u8 *)D_800A3A40Absolute[0]) +
        ((((((*((u16 *)(arg0 + 0x18))) * 2) + (*((u16 *)(arg0 + 0x18)))) * 4) -
          (*((u16 *)(arg0 + 0x18)))) *
         4);
    SetShadeTex(entry, 1);
    if (D_800A2EC8Absolute[0] != 0) {
        *((s16 *)(entry + 0xE)) = GetTPage(1, 0, 0x200, 0x100);
        clut = GetClut(0x200, 0x1FF);
        d = 0xA7;
        c = 0xFD;
        *((s16 *)(entry + 0xA)) = clut;
        pal = 0x7F;
        *((u8 *)(entry + 0x8)) = 0;
        *((u8 *)(entry + 0x9)) = d;
        *((u8 *)(entry + 0xC)) = 0;
        *((u8 *)(entry + 0xD)) = 0xFD;
        *((u8 *)(entry + 0x10)) = 0x7F;
        *((u8 *)(entry + 0x11)) = d;
        *((u8 *)(entry + 0x14)) = pal;
        *((u8 *)(entry + 0x15)) = c;
        return;
    }
    pal = ((u8 *)D_800A2EC8Absolute)[0x11];
    if (pal != 0) {
        pal = 0x40;
        c = 0x78;
        *((u8 *)(entry + 0x8)) = pal;
        *((u8 *)(entry + 0xC)) = pal;
        pal = 0xBF;
        *((u8 *)(entry + 0x9)) = 0;
        *((u8 *)(entry + 0xD)) = c;
        *((u8 *)(entry + 0x10)) = pal;
        *((u8 *)(entry + 0x11)) = 0;
        *((u8 *)(entry + 0x14)) = pal;
        *((u8 *)(entry + 0x15)) = c;
    } else {
        pal = 0x40;
        c = 0x3C;
        *((u8 *)(entry + 0x8)) = pal;
        *((u8 *)(entry + 0xC)) = pal;
        pal = 0xBF;
        *((u8 *)(entry + 0x9)) = c;
        *((u8 *)(entry + 0xD)) = pal;
        *((u8 *)(entry + 0x10)) = pal;
        *((u8 *)(entry + 0x11)) = c;
        *((u8 *)(entry + 0x14)) = pal;
        *((u8 *)(entry + 0x15)) = pal;
    }
    if (gOrderingTableBankAbsolute[0] != 0) {
        *((s16 *)(entry + 0xE)) = GetTPage(2, 0, 0, 0);
    } else {
        *((s16 *)(entry + 0xE)) = GetTPage(2, 0, 0x140, 0);
    }
}

#endif
extern RenderListNode *D_800A3A40Absolute[];

void func_8001CDDC(u8 *arg0) {
    s32 pal;
    s32 c;
    s32 d;
    u8 *entry;
    if ((*((s16 *)(arg0 + 0xA))) != 4) {
        return;
    }
    entry =
        ((u8 *)D_800A3A40Absolute[0]) +
        ((((((*((u16 *)(arg0 + 0x18))) * 2) + (*((u16 *)(arg0 + 0x18)))) * 4) -
          (*((u16 *)(arg0 + 0x18)))) *
         4);
    SetShadeTex(entry, 1);
    if (D_800A2EC8Absolute[0] != 0) {
        d = 0x100;
        do {
            *((s16 *)(entry + 0xE)) = GetTPage(1, 0, 0x200, d);
            *((s16 *)(entry + 0xA)) = GetClut(0x200, 0x1FF);
        } while (0);
        pal = 0x80;
        c = 0xA7;
        d = 0xFD;
        *((u8 *)(entry + 0x8)) = pal;
        *((u8 *)(entry + 0xC)) = pal;
        pal = 0x9F;
        *((u8 *)(entry + 0x9)) = c;
        *((u8 *)(entry + 0xD)) = d;
        *((u8 *)(entry + 0x10)) = pal;
        *((u8 *)(entry + 0x11)) = c;
        *((u8 *)(entry + 0x14)) = pal;
        *((u8 *)(entry + 0x15)) = d;
        return;
    }
    pal = ((u8 *)D_800A2EC8Absolute)[0x11];
    if (pal != 0) {
        d = 0x78;
        pal = 0x1F;
        *((u8 *)(entry + 0x8)) = 0;
        *((u8 *)(entry + 0x9)) = 0;
        *((u8 *)(entry + 0xC)) = 0;
        *((u8 *)(entry + 0xD)) = d;
        *((u8 *)(entry + 0x10)) = pal;
        *((u8 *)(entry + 0x11)) = 0;
    } else {
        c = 0x3C;
        d = 0xBF;
        pal = 0x1F;
        *((u8 *)(entry + 0x8)) = 0;
        *((u8 *)(entry + 0x9)) = c;
        *((u8 *)(entry + 0xC)) = 0;
        *((u8 *)(entry + 0xD)) = d;
        *((u8 *)(entry + 0x10)) = pal;
        *((u8 *)(entry + 0x11)) = c;
    }
    *((u8 *)(entry + 0x14)) = pal;
    *((u8 *)(entry + 0x15)) = d;
    if (gOrderingTableBankAbsolute[0] != 0) {
        *((s16 *)(entry + 0xE)) = GetTPage(2, 0, 0xC0, 0);
    } else {
        *((s16 *)(entry + 0xE)) = GetTPage(2, 0, 0x200, 0);
    }
}

void func_8001CF38(u8 *arg0) {
    s32 pal;
    s32 c;
    s32 d;
    u8 *entry;
    if ((*((s16 *)(arg0 + 0xA))) != 4) {
        return;
    }
    entry =
        ((u8 *)D_800A3A40Absolute[0]) +
        ((((((*((u16 *)(arg0 + 0x18))) * 2) + (*((u16 *)(arg0 + 0x18)))) * 4) -
          (*((u16 *)(arg0 + 0x18)))) *
         4);
    SetShadeTex(entry, 1);
    if (D_800A2EC8Absolute[0] != 0) {
        *((s16 *)(entry + 0xE)) = GetTPage(1, 0, 0x200, 0x100);
        *((s16 *)(entry + 0xA)) = GetClut(0x200, 0x1FF);
        do {
            pal = 0xA0;
            d = 0xA7;
            c = 0xFD;
            *((u8 *)(entry + 0x8)) = pal;
            *((u8 *)(entry + 0xC)) = pal;
            pal = 0xBF;
        } while (0);
        *((u8 *)(entry + 0x9)) = d;
        *((u8 *)(entry + 0xD)) = c;
        *((u8 *)(entry + 0x10)) = pal;
        *((u8 *)(entry + 0x11)) = d;
        *((u8 *)(entry + 0x14)) = pal;
        *((u8 *)(entry + 0x15)) = c;
        return;
    }
    pal = ((u8 *)D_800A2EC8Absolute)[0x11];
    if (pal != 0) {
        pal = 0x20;
        c = 0x78;
        *((u8 *)(entry + 0x8)) = pal;
        *((u8 *)(entry + 0xC)) = pal;
        pal = 0x3F;
        *((u8 *)(entry + 0x9)) = 0;
        *((u8 *)(entry + 0xD)) = c;
        *((u8 *)(entry + 0x10)) = pal;
        *((u8 *)(entry + 0x11)) = 0;
    } else {
        pal = 0x20;
        d = 0x3C;
        c = 0xBF;
        *((u8 *)(entry + 0x8)) = pal;
        *((u8 *)(entry + 0xC)) = pal;
        pal = 0x3F;
        *((u8 *)(entry + 0x9)) = d;
        *((u8 *)(entry + 0xD)) = c;
        *((u8 *)(entry + 0x10)) = pal;
        *((u8 *)(entry + 0x11)) = d;
    }
    *((u8 *)(entry + 0x14)) = pal;
    *((u8 *)(entry + 0x15)) = c;
    if (gOrderingTableBankAbsolute[0] != 0) {
        *((s16 *)(entry + 0xE)) = GetTPage(2, 0, 0xC0, 0);
    } else {
        *((s16 *)(entry + 0xE)) = GetTPage(2, 0, 0x200, 0);
    }
}

extern void (*D_80091080[])(void *);
void ListDispatchCallbacks(TrackSection *owner) {
    u8 *node;
    void (*callback)(void *);
    node = owner->callbacks;
    while (node != 0) {
        callback = D_80091080[*(s16 *)(node + 0xC)];
        callback(node);
        node = *(u8 **)node;
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
    vertex.vx = *(u16 *)vertexPtr;
    vertex.vy = *(u16 *)(flagPtr - 4);
    vertex.vz = *(u16 *)(flagPtr - 2);
    RotTransPers_nom(&vertex);
    func_8003382C(vertexPtr);
    masked = flags & 0x7EF6;
    flags = *(u16 *)flagPtr & masked;
    flagPtr += 8;
    vertexPtr += 8;
    if (++index < 4) {
        goto again;
    }
    *(s16 *)(obj + 0xE) = flags;
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
    D_800A35C0[1] = cursor + sizeof(POLY_FT4);
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
        D_800A35C0[1] = cursor2 + sizeof(POLY_FT4);
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
    D_800A35C0[1] = cursor + sizeof(POLY_FT4);
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
    D_800A35C0[1] = cursor + sizeof(POLY_FT4);
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

void func_8001DB20(RenderListNode *arg0, s32 arg1) {
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

    flag = *(u8 *)((u8 *)arg0 + 0x13);
    mode = arg1;
    vert = (u8 *)arg0;
    if ((flag & 1) != 0) {
        return;
    }
    prim = &poly;
    if (*(u8 *)((u8 *)arg0 + 0x12) != 3) {
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
    if (*(s16 *)((u8 *)arg0 + 0x16) >= 0) {
        tex = GraphicsGetImageBankTexture(*(s16 *)((u8 *)arg0 + 0x16));
    }
    saved = *(s8 *)((u8 *)arg0 + 1);
    if (tex != 0) {
        if (mode != 0) {
            prim->tpage = GetTPage(*(u16 *)((u8 *)tex + 0), 0,
                                   *(u16 *)((u8 *)tex + 2) - 0x100,
                                   *(u16 *)((u8 *)tex + 4));
            x = *(u16 *)((u8 *)tex + 0xA);
            x = x - 0x100;
            y = *(u16 *)((u8 *)tex + 0xC);
        } else {
            prim->tpage =
                GetTPage(*(u16 *)((u8 *)tex + 0), 0, *(u16 *)((u8 *)tex + 2),
                         *(u16 *)((u8 *)tex + 4));
            x = *(u16 *)((u8 *)tex + 0xA);
            y = *(u16 *)((u8 *)tex + 0xC);
        }
        prim->clut = GetClut(x, y);
        for (i = 0; i < 4; i++) {
            vert[i * 4 + 8] = vert[i * 4 + 8] + tex->pad[6];
            vert[i * 4 + 9] = vert[i * 4 + 9] + tex->pad[8];
        }
        if (*(s32 *)((u8 *)arg0 + 4) < 0) {
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
            *(u8 *)((u8 *)arg0 + 2) = 3;
            *(u8 *)((u8 *)arg0 + 1) = 0;
            r = *(u8 *)((u8 *)arg0 + 6);
            g = *(u8 *)((u8 *)arg0 + 5);
            b = *(u8 *)((u8 *)arg0 + 4);
            prim->r0 = r;
            prim->g0 = g;
            prim->b0 = b;
            if (*(u8 *)((u8 *)arg0 + 0x12) != 3) {
                SetPolyF4((POLY_F4 *)prim);
                if (*(s32 *)((u8 *)arg0 + 4) < 0) {
                    SetSemiTrans(prim, 1);
                }
                *(u8 *)((u8 *)arg0 + 1) = 0x10;
            } else {
                SetPolyF3((POLY_F3 *)prim);
                if (*(s32 *)((u8 *)arg0 + 4) < 0) {
                    SetSemiTrans(prim, 1);
                }
            }
        }
    }
    if (mode != 0) {
        if (*(u8 *)((u8 *)arg0 + 0x12) == 3) {
            SetPolyFT4(prim);
            *(s32 *)((u8 *)arg0 + 0x24) = *(s32 *)((u8 *)arg0 + 0x20);
            *(XyPair *)(vert + 0x14) = *(XyPair *)(vert + 0x10);
        }
    } else {
        if (*(u8 *)((u8 *)arg0 + 0x12) == 3) {
            *(s32 *)((u8 *)arg0 + 0x24) = *(s32 *)((u8 *)arg0 + 0x20);
            *(XyPair *)(vert + 0x14) = *(XyPair *)(vert + 0x10);
            if (*(s8 *)((u8 *)arg0 + 2) == 6) {
                *(u8 *)((u8 *)arg0 + 7) = *(u8 *)((u8 *)arg0 + 6);
            }
        }
        if (*(s8 *)((u8 *)arg0 + 2) < 3) {
            SetPolyGT4((POLY_GT4 *)prim);
            *(u8 *)((u8 *)arg0 + 2) = 6;
            *(s32 *)((u8 *)arg0 + 4) = 0x80808080;
        }
    }
    r = *(u8 *)((u8 *)arg0 + 6);
    g = *(u8 *)((u8 *)arg0 + 5);
    b = *(u8 *)((u8 *)arg0 + 4);
    prim->r0 = r;
    prim->g0 = g;
    prim->b0 = b;
    if (*(s32 *)((u8 *)arg0 + 4) < 0) {
        SetSemiTrans(prim, 1);
    }
    if (*(s32 *)((u8 *)arg0 + 4) == 0xADADAD ||
        *(s32 *)((u8 *)arg0 + 4) == 0xFFFFFF) {
        *(u8 *)((u8 *)arg0 + 0x13) = *(u8 *)((u8 *)arg0 + 0x13) & 0xEF;
    } else {
        *(u8 *)((u8 *)arg0 + 0x13) = *(u8 *)((u8 *)arg0 + 0x13) | 0x10;
    }
    *(u8 *)((u8 *)arg0 + 3) = *(u8 *)((u8 *)prim + 3);
    if (*(s8 *)((u8 *)arg0 + 2) != 6) {
        *(s32 *)((u8 *)arg0 + 4) = *(s32 *)&prim->r0;
    }
    *(u16 *)((u8 *)arg0 + 0xA) = prim->clut;
    *(u16 *)((u8 *)arg0 + 0xE) = prim->tpage;
    if (mode == 0) {
        *(u8 *)((u8 *)arg0 + 1) = saved;
    }
    func_80032D94((s8 *)arg0);
}

extern s32 D_800BE978[];

extern void func_8001DB20(RenderListNode *, s32);

void RenderDrawGeometryList(void) {
    s32 count;
    s32 i;

    count = D_800BE978[0];
    i = 0;
    while (i < count) {
        func_8001DB20(
            (RenderListNode *)((u8 *)D_800A3A40Absolute[0] + i * 0x2C), 1);
        i += 1;
    }
}

void RenderDrawFiveLinkedLists(void) {
    extern RenderListNode D_800AE8C0[];
    s32 offset;
    s32 i;
    RenderListNode *node;
    i = 0;
    offset = 0;
    do {
        node = *(RenderListNode **)((u8 *)D_800AE8C0 + offset);
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
