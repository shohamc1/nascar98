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

extern s32 D_800A39C8[];
void SystemShowFatalError(char *message);
u32 MathSqrt(u32 value);
void RandomCountMark(void);
s32 RandomSeedGet(void);
void RandomSeedSet(s32 seed);
s32 RandomScaledGet(s32 scale);
void func_80017D80(u8 *arg0);
void FontSetColor(s16 red, s16 green, s16 blue);
void func_8001832C(s8 *text, s32 x, s32 y, s32 scale);
void func_80018588(void *timeValue, s32 flags, s32 buffer);
void func_80018768(void *arg0, s32 x, s32 y, s32 scale);
void func_80018848(void *arg0, s32 arg1, s32 arg2);
void FontDrawPaddedNumber(s32 value, s32 x, s32 y, s32 scale);
void func_80018B18(s32 value, s32 x, s32 y, s32 scale);
void func_80018BD4(s32 value, s32 x, s32 y, s32 scale);
void func_800197D4(s32 kind, s32 x, s32 y);
void func_80019A00(s16 arg0, u8 *arg1, s32 arg2);
void func_8001C34C(void);

/* Lists and callbacks. */

typedef struct ListNode28 ListNode28;
struct ListNode28 {
    u8 unk0[0x28];
    ListNode28 *next;
};

void ListInsertBefore(ListNode28 **head, ListNode28 *node, ListNode28 *before) {
    ListNode28 *current;
    ListNode28 *previous;

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

void ListRemoveNode(ListNode28 **head, ListNode28 *target) {
    ListNode28 *current;
    ListNode28 *previous;

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

void func_8001C668(void *arg0, void *arg1) {
    u8 **head;
    u8 **tail;
    u8 *node;
    u8 *next;
    u8 *prevNode;
    u8 *temp;

    head = (u8 **)arg0;
    tail = (u8 **)arg1;
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

extern void func_8001F2C4(s32 arg0, s32 arg1, s32 arg2);
extern void func_8001ED84(s32 *vec);
void func_8001C99C(u8 *arg0) {
    s32 i;
    s32 *vec;
    u8 *el;
    u8 *base;

    base = D_800BE97C[0];
    vec = (s32 *)(arg0 + 0x210);
    func_8001F2C4(0, 0, (D_800A2EC0Absolute[0] & 0x1F) << 5);
    for (i = 0; i < *(s16 *)(arg0 + 0xA); i++) {
        el = base + *(u16 *)(arg0 + 0x10 + i * 2) * 0x14;
        *(u16 *)(el + 0) = *(u16 *)(arg0 + 0x90 + i * 6);
        *(u16 *)(el + 2) = *(u16 *)(arg0 + 0x92 + i * 6);
        *(u16 *)(el + 4) = *(u16 *)(arg0 + 0x94 + i * 6);
        func_8001ED84((s32 *)el);
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
        func_8001ED84((s32 *)el);
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
extern ListNode28 *D_800A3A40Absolute[];

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

INCLUDE_ASM("asm/nonmatchings/list_callbacks", func_8001D220);

INCLUDE_ASM("asm/nonmatchings/list_callbacks", func_8001D638);

extern POLY_FT4 D_800A3C6C[];
extern u32 D_800A35C0[];
void func_8001D778(s32 x, s32 y, s32 w, s32 h, u8 r, u8 g, u8 b,
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
    AddPrim((u8 *)D_800A39C8[0], entry);
}

extern POLY_F4 D_800A3D0C[];
extern s32 D_800A2DB8;
void func_8001D914(s32 x, s32 y, s32 w, s32 h, u8 r, u8 g, u8 b,
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
    AddPrim((u8 *)D_800A39C8[0], poly);
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

typedef struct {
    u8 pad[16];
} Unk16;
extern Unk16 *func_8001E040(s32);
extern void func_80032D94(s8 *);

typedef struct {
    s16 x;
    s16 y;
} XyPair;

void func_8001DB20(ListNode28 *arg0, s32 arg1) {
    POLY_FT4 poly;
    POLY_FT4 *prim;
    Unk16 *tex;
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
        tex = func_8001E040(*(s16 *)((u8 *)arg0 + 0x16));
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

extern void func_8001DB20(ListNode28 *, s32);

void func_8001DF60(void) {
    s32 count;
    s32 i;

    count = D_800BE978[0];
    i = 0;
    while (i < count) {
        func_8001DB20((ListNode28 *)((u8 *)D_800A3A40Absolute[0] + i * 0x2C),
                      1);
        i += 1;
    }
}

void func_8001DFC8(void) {
    extern ListNode28 D_800AE8C0[];
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
