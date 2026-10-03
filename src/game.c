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

INCLUDE_ASM("asm/nonmatchings/game", func_80012108);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80012B78);

void SystemStopCounterAfterVSync(void) {
    VSync(0);
    StopRCnt(0xF2000001);
}

INCLUDE_ASM("asm/nonmatchings/game", func_80012C30);

INCLUDE_ASM("asm/nonmatchings/game", func_80012D10);

extern void *D_800A3A8C;
void func_80012E00(void) {
    D_800A3A8C = HeapAlloc(0x35B60);
}

INCLUDE_ASM("asm/nonmatchings/game", func_80012E28);

INCLUDE_ASM("asm/nonmatchings/game", func_80012E3C);

INCLUDE_ASM("asm/nonmatchings/game", func_80012EA8);

INCLUDE_ASM("asm/nonmatchings/game", func_80012F94);

#include <psxsdk/kernel.h>
/* Counter and frame control. */

void SystemInitCounter(void) {
    EnterCriticalSection();
    SetRCnt(RCntCNT1, 0xFFFF, 0x2000);
    StartRCnt(RCntCNT1);
    ExitCriticalSection();
    ResetRCnt(RCntCNT1);
}

INCLUDE_ASM("asm/nonmatchings/game", func_800130D4);

INCLUDE_ASM("asm/nonmatchings/game", func_8001317C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80013224);

INCLUDE_ASM("asm/nonmatchings/game", func_800132F8);

#ifdef NON_MATCHING
extern u16 D_80090ED8[];
extern s32 D_80099590[];
extern u8 D_800A3320;
extern u8 D_800A331C;
s32 func_80014398(s32 arg0) {
    s32 source;
    s32 difference;
    s32 adjust;
    s32 value;
    s32 scale;
    source = D_80099590[arg0];
    difference = source - D_80090ED8[arg0];
    adjust = difference * (0x64 - D_800A3320);
    adjust = adjust / 50;
    value = source - adjust;
    scale = D_800A331C + 0xC8;
    scale = scale / 3;
    value = value * (0xC8 - scale);
    return value / 100;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80014398);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80014440);

INCLUDE_ASM("asm/nonmatchings/game", func_800144B4);

INCLUDE_ASM("asm/nonmatchings/game", func_8001475C);

INCLUDE_ASM("asm/nonmatchings/game", func_80014A40);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80014AC8);

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

INCLUDE_ASM("asm/nonmatchings/game", func_800157B0);

INCLUDE_ASM("asm/nonmatchings/game", func_80015870);

INCLUDE_ASM("asm/nonmatchings/game", func_80015930);

void func_80015A74(s32 arg0) {
    extern s32 func_8003C584(s32, void *);
    extern void func_80014BEC(s32 *, s32);
    extern void func_8003C63C(s32);
    extern void SystemShowFatalError(char *);
    extern u8 D_800A2D48[];
    extern char D_8008CC7C[];
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

INCLUDE_ASM("asm/nonmatchings/game", func_80015D10);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80016298);

INCLUDE_ASM("asm/nonmatchings/game", func_8001636C);

INCLUDE_ASM("asm/nonmatchings/game", func_800163E8);

extern s32 D_800A2D5C;
extern s32 *D_800A2D64;
void func_80016724(s32 value, s32 *next, s32 size) {
    s32 *current;
    current = D_800A2D64;
    D_800A2D64 = next;
    current[0x34 / 4] = value;
    D_800A2D5C += size;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80016744);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80017D80);

INCLUDE_ASM("asm/nonmatchings/game", func_80017E08);

INCLUDE_ASM("asm/nonmatchings/game", func_800180C0);

extern s16 gFontColorRed, gFontColorGreen, gFontColorBlue;
void FontSetColor(s16 red, s16 green, s16 blue) {
    gFontColorRed = red;
    gFontColorGreen = green;
    gFontColorBlue = blue;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8001832C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80019A00);

INCLUDE_ASM("asm/nonmatchings/game", func_80019C10);

INCLUDE_ASM("asm/nonmatchings/game", func_8001A4D4);

INCLUDE_ASM("asm/nonmatchings/game", func_8001A778);

INCLUDE_ASM("asm/nonmatchings/game", func_8001AEDC);

INCLUDE_ASM("asm/nonmatchings/game", func_8001B3F0);

INCLUDE_ASM("asm/nonmatchings/game", func_8001B82C);

INCLUDE_ASM("asm/nonmatchings/game", func_8001BA94);

INCLUDE_ASM("asm/nonmatchings/game", func_8001BDBC);

INCLUDE_ASM("asm/nonmatchings/game", func_8001C34C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8001CBD4);

INCLUDE_ASM("asm/nonmatchings/game", func_8001CC7C);

INCLUDE_ASM("asm/nonmatchings/game", func_8001CDDC);

INCLUDE_ASM("asm/nonmatchings/game", func_8001CF38);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8001D108);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8001D914);

INCLUDE_ASM("asm/nonmatchings/game", func_8001DA48);

INCLUDE_ASM("asm/nonmatchings/game", func_8001DB20);

INCLUDE_ASM("asm/nonmatchings/game", func_8001DF60);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8001E230);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8001E7EC);

INCLUDE_ASM("asm/nonmatchings/game", func_8001EA90);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8001ECD8);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8001F198);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8001F5BC);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8001F90C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8001FAC0);

INCLUDE_ASM("asm/nonmatchings/game", func_8001FB28);

INCLUDE_ASM("asm/nonmatchings/game", func_8001FB80);

INCLUDE_ASM("asm/nonmatchings/game", func_8001FBDC);

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
INCLUDE_ASM("asm/nonmatchings/game", VectorGetMagnitude2D);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8001FC6C);

INCLUDE_ASM("asm/nonmatchings/game", func_8001FD44);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80022CA4);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80022FB8);

INCLUDE_ASM("asm/nonmatchings/game", func_80023074);

INCLUDE_ASM("asm/nonmatchings/game", func_80023454);

INCLUDE_ASM("asm/nonmatchings/game", func_80024210);

INCLUDE_ASM("asm/nonmatchings/game", func_80024280);

INCLUDE_ASM("asm/nonmatchings/game", func_800246C0);

INCLUDE_ASM("asm/nonmatchings/game", func_8002482C);

INCLUDE_ASM("asm/nonmatchings/game", func_80024980);

INCLUDE_ASM("asm/nonmatchings/game", func_80024B08);

INCLUDE_ASM("asm/nonmatchings/game", func_80024E90);

INCLUDE_ASM("asm/nonmatchings/game", func_80025370);

INCLUDE_ASM("asm/nonmatchings/game", func_80025454);

void func_80025594(u8 *object) {
    *(s16 *)(object + 0x1BC) = 0;
    *(s16 *)(object + 0x388) = 0;
}

INCLUDE_ASM("asm/nonmatchings/game", func_800255A0);

INCLUDE_ASM("asm/nonmatchings/game", func_80025614);

void func_80025594();

void func_80025720(u8 *obj) {
    *(void (**)())(obj + 0x354) = func_80025594;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80025730);

typedef struct {
    u8 unk0[0x1EC];
    s16 unk1EC;
    u8 unk1EE[0x12];
    s8 unk200;
    u8 unk201[0x153];
    void (*callback)(void);
} Batch0CallbackObject;
extern void func_80025730(void);
void ObjectSetCallbackIfAllowed(Batch0CallbackObject *object,
                                void (*callback)(void)) {
    if (((object->unk1EC != 1) || (callback != func_80025730)) &&
        (object->callback != func_80025730) && (object->unk200 != 4)) {
        object->callback = callback;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80025938);

INCLUDE_ASM("asm/nonmatchings/game", func_80025A38);

INCLUDE_ASM("asm/nonmatchings/game", func_80025DD4);

INCLUDE_ASM("asm/nonmatchings/game", func_80025F40);

INCLUDE_ASM("asm/nonmatchings/game", func_80026074);

INCLUDE_ASM("asm/nonmatchings/game", func_800261F8);

INCLUDE_ASM("asm/nonmatchings/game", func_800270F4);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80028D80);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80028FCC);

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

INCLUDE_ASM("asm/nonmatchings/game", func_800297D0);

INCLUDE_ASM("asm/nonmatchings/game", func_800298E0);

INCLUDE_ASM("asm/nonmatchings/game", func_80029994);

INCLUDE_ASM("asm/nonmatchings/game", func_80029A78);

INCLUDE_ASM("asm/nonmatchings/game", func_80029CB4);

INCLUDE_ASM("asm/nonmatchings/game", func_80029DA8);

void func_80029E2C(void) {
}

void func_80029E34(void) {
}

void func_80029E3C(void) {
}

INCLUDE_ASM("asm/nonmatchings/game", func_80029E44);

INCLUDE_ASM("asm/nonmatchings/game", func_80029EF8);

extern s32 D_800A2E1C, D_800A2E24;
void func_8002A1D0(void) {
    D_800A2E24 = 0x1EF0000 - (D_800A2E1C - 3) * 0x30000;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8002A1FC);

INCLUDE_ASM("asm/nonmatchings/game", func_8002A2F8);

INCLUDE_ASM("asm/nonmatchings/game", func_8002A954);

INCLUDE_ASM("asm/nonmatchings/game", func_8002AAA0);

INCLUDE_ASM("asm/nonmatchings/game", func_8002AAF0);

INCLUDE_ASM("asm/nonmatchings/game", func_8002AD20);

INCLUDE_ASM("asm/nonmatchings/game", func_8002ADE0);

INCLUDE_ASM("asm/nonmatchings/game", func_8002AEB0);

INCLUDE_ASM("asm/nonmatchings/game", func_8002AF94);

INCLUDE_ASM("asm/nonmatchings/game", func_8002B258);

INCLUDE_ASM("asm/nonmatchings/game", func_8002B538);

INCLUDE_ASM("asm/nonmatchings/game", func_8002B63C);

INCLUDE_ASM("asm/nonmatchings/game", func_8002B9AC);

INCLUDE_ASM("asm/nonmatchings/game", func_8002BC88);

INCLUDE_ASM("asm/nonmatchings/game", func_8002BD48);

s32 func_8002CF1C(void) {
    return 2000;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8002CF24);

INCLUDE_ASM("asm/nonmatchings/game", func_8002D16C);

INCLUDE_ASM("asm/nonmatchings/game", func_8002D27C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8002D3EC);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8002DC2C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8002E230);

INCLUDE_ASM("asm/nonmatchings/game", func_8002E240);

INCLUDE_ASM("asm/nonmatchings/game", func_8002E594);

INCLUDE_ASM("asm/nonmatchings/game", func_8002E9AC);

INCLUDE_ASM("asm/nonmatchings/game", func_8002EE88);

INCLUDE_ASM("asm/nonmatchings/game", func_8002EEFC);

INCLUDE_ASM("asm/nonmatchings/game", func_8002F0A8);

INCLUDE_ASM("asm/nonmatchings/game", func_8002F1A0);

INCLUDE_ASM("asm/nonmatchings/game", func_8002F2CC);

INCLUDE_ASM("asm/nonmatchings/game", func_8002F454);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8002F5F4);

void func_8002F66C(void) {
}

INCLUDE_ASM("asm/nonmatchings/game", func_8002F674);

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

INCLUDE_ASM("asm/nonmatchings/game", func_800309DC);

INCLUDE_ASM("asm/nonmatchings/game", func_80030CDC);

INCLUDE_ASM("asm/nonmatchings/game", func_80030D80);

INCLUDE_ASM("asm/nonmatchings/game", func_80030F24);

INCLUDE_ASM("asm/nonmatchings/game", func_800311B4);

INCLUDE_ASM("asm/nonmatchings/game", func_80031264);

INCLUDE_ASM("asm/nonmatchings/game", func_80031874);

INCLUDE_ASM("asm/nonmatchings/game", func_800319D4);

INCLUDE_ASM("asm/nonmatchings/game", func_80031D74);

INCLUDE_ASM("asm/nonmatchings/game", func_80032328);

INCLUDE_ASM("asm/nonmatchings/game", func_800323F0);

void func_80031D74(s32, s32, s32);
extern s32 D_800A3574[];
extern u8 D_800A2D4C[], D_800A2D4D[];
void func_80032450(s32 first, s32 second) {
    func_80031D74(D_800A3574[0], first, second);
    D_800A2D4C[0] = 1;
    D_800A2D4D[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80032494);

#ifdef NON_MATCHING
void GraphicsLinkPrimitive(u32 *orderingTable, u32 *primitive) {
    u32 tag;
    u32 mask;
    u32 upper;

    mask = 0xFFFFFF;
    upper = 0xFF000000;
    tag = *orderingTable;
    *primitive = (*primitive & upper) | (tag & mask);
    *orderingTable = (tag & upper) | ((u32)primitive & mask);
}
#else
INCLUDE_ASM("asm/nonmatchings/game", GraphicsLinkPrimitive);
#endif

void GraphicsAddTaggedPrimitive(u32 *orderingTable, u32 *primitive, u32 tag) {
    *primitive = tag | *orderingTable;
    *orderingTable = (u32)primitive & 0xFFFFFF;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80032544);

INCLUDE_ASM("asm/nonmatchings/game", func_8003271C);

INCLUDE_ASM("asm/nonmatchings/game", func_80032760);

INCLUDE_ASM("asm/nonmatchings/game", func_800328AC);

INCLUDE_ASM("asm/nonmatchings/game", func_80032A90);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80032DEC);

INCLUDE_ASM("asm/nonmatchings/game", func_80033000);

INCLUDE_ASM("asm/nonmatchings/game", func_80033704);

INCLUDE_ASM("asm/nonmatchings/game", func_80033780);

INCLUDE_ASM("asm/nonmatchings/game", func_80033788);

INCLUDE_ASM("asm/nonmatchings/game", func_8003379C);

INCLUDE_ASM("asm/nonmatchings/game", MathMultiplyFixed16);

INCLUDE_ASM("asm/nonmatchings/game", func_800337EC);

INCLUDE_ASM("asm/nonmatchings/game", func_8003382C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_800345E0);

INCLUDE_ASM("asm/nonmatchings/game", func_800346D0);

INCLUDE_ASM("asm/nonmatchings/game", func_80034834);

INCLUDE_ASM("asm/nonmatchings/game", func_80034990);

INCLUDE_ASM("asm/nonmatchings/game", func_80034B90);

INCLUDE_ASM("asm/nonmatchings/game", func_80034C1C);

INCLUDE_ASM("asm/nonmatchings/game", func_80034C94);

INCLUDE_ASM("asm/nonmatchings/game", func_80034CFC);

INCLUDE_ASM("asm/nonmatchings/game", func_80034D64);

INCLUDE_ASM("asm/nonmatchings/game", func_80035274);

INCLUDE_ASM("asm/nonmatchings/game", func_8003565C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80035720);

INCLUDE_ASM("asm/nonmatchings/game", func_8003587C);

INCLUDE_ASM("asm/nonmatchings/game", func_800358EC);

INCLUDE_ASM("asm/nonmatchings/game", func_80035B20);

INCLUDE_ASM("asm/nonmatchings/game", func_80035E8C);

INCLUDE_ASM("asm/nonmatchings/game", func_80035F28);

INCLUDE_ASM("asm/nonmatchings/game", func_80036264);

INCLUDE_ASM("asm/nonmatchings/game", func_8003644C);

INCLUDE_ASM("asm/nonmatchings/game", func_800364C4);

INCLUDE_ASM("asm/nonmatchings/game", func_80036540);

INCLUDE_ASM("asm/nonmatchings/game", func_800365B8);

INCLUDE_ASM("asm/nonmatchings/game", func_8003667C);

INCLUDE_ASM("asm/nonmatchings/game", func_800367DC);

INCLUDE_ASM("asm/nonmatchings/game", func_80036900);

INCLUDE_ASM("asm/nonmatchings/game", func_80036F64);

INCLUDE_ASM("asm/nonmatchings/game", func_80036FC8);

INCLUDE_ASM("asm/nonmatchings/game", func_8003702C);

INCLUDE_ASM("asm/nonmatchings/game", func_800370B8);

INCLUDE_ASM("asm/nonmatchings/game", func_80037130);

INCLUDE_ASM("asm/nonmatchings/game", func_80037204);

INCLUDE_ASM("asm/nonmatchings/game", func_800373B4);

INCLUDE_ASM("asm/nonmatchings/game", func_80038D78);

INCLUDE_ASM("asm/nonmatchings/game", func_80039008);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8003A880);

INCLUDE_ASM("asm/nonmatchings/game", func_8003A950);

INCLUDE_ASM("asm/nonmatchings/game", func_8003AA20);

INCLUDE_ASM("asm/nonmatchings/game", func_8003AAEC);

INCLUDE_ASM("asm/nonmatchings/game", func_8003ABC0);

INCLUDE_ASM("asm/nonmatchings/game", func_8003AC18);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8003BCAC);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8003C584);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8003C928);

INCLUDE_ASM("asm/nonmatchings/game", func_8003CA18);

INCLUDE_ASM("asm/nonmatchings/game", func_8003CAE8);

INCLUDE_ASM("asm/nonmatchings/game", func_8003CC48);

INCLUDE_ASM("asm/nonmatchings/game", func_8003CCE0);

void CdStop(void) {
    CdControl(8, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8003CDBC);

void func_8003CEFC(void) {
}

void func_8003CF04(void) {
}

INCLUDE_ASM("asm/nonmatchings/game", func_8003CF0C);

INCLUDE_ASM("asm/nonmatchings/game", func_8003D25C);

INCLUDE_ASM("asm/nonmatchings/game", func_8003D528);

INCLUDE_ASM("asm/nonmatchings/game", func_8003D5F8);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8003D69C);

INCLUDE_ASM("asm/nonmatchings/game", func_8003D6F8);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8003DB5C);

INCLUDE_ASM("asm/nonmatchings/game", func_8003DBA8);

INCLUDE_ASM("asm/nonmatchings/game", func_8003E78C);

INCLUDE_ASM("asm/nonmatchings/game", func_8003EA94);

INCLUDE_ASM("asm/nonmatchings/game", func_8003EAE8);

INCLUDE_ASM("asm/nonmatchings/game", func_8003EBD0);

INCLUDE_ASM("asm/nonmatchings/game", func_8003ECB8);

INCLUDE_ASM("asm/nonmatchings/game", func_8003EDA0);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8003F060);

INCLUDE_ASM("asm/nonmatchings/game", func_8003F0CC);

INCLUDE_ASM("asm/nonmatchings/game", func_8003F13C);

INCLUDE_ASM("asm/nonmatchings/game", func_8003F1B0);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8003F2AC);

extern u8 *func_8003FFF0(void *entry, s32 index);
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

INCLUDE_ASM("asm/nonmatchings/game", func_8003F4FC);

INCLUDE_ASM("asm/nonmatchings/game", func_8003F564);

INCLUDE_ASM("asm/nonmatchings/game", func_8003F914);

INCLUDE_ASM("asm/nonmatchings/game", func_8003FA0C);

INCLUDE_ASM("asm/nonmatchings/game", func_8003FA84);

INCLUDE_ASM("asm/nonmatchings/game", func_8003FC0C);

INCLUDE_ASM("asm/nonmatchings/game", func_8003FDE8);

INCLUDE_ASM("asm/nonmatchings/game", func_8003FEB8);

INCLUDE_ASM("asm/nonmatchings/game", func_8003FF5C);

INCLUDE_ASM("asm/nonmatchings/game", func_8003FFF0);

INCLUDE_ASM("asm/nonmatchings/game", func_800400D8);

extern s8 D_800A2FA4[];
extern s32 D_800BE988[];
extern s32 D_80098D00[];
extern s8 D_800A354C[];
extern s32 D_800BA048[];
extern s8 D_800A39D0;
void func_800401B8(void) {
    s32 i;
    s32 initialized;
    i = 0;
    initialized = 0;
    while (i < 4) {
        if (D_800A354C[i] == 0 && D_800A2FA4[i] == 0) {
            D_800A354C[i] = 1;
            D_80098D00[i] = D_800BA048[initialized];
            D_800BE988[i] = -1;
            D_800A2FA4[i] = 5;
            initialized++;
            if (initialized == D_800A39D0)
                break;
        }
        i++;
    }
}

INCLUDE_ASM("asm/nonmatchings/game", func_80040260);

INCLUDE_ASM("asm/nonmatchings/game", func_800406D0);

INCLUDE_ASM("asm/nonmatchings/game", func_800409A0);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80041564);

void func_80041848(void) {
}

/* Sound startup and shutdown. */

INCLUDE_ASM("asm/nonmatchings/game", func_80041850);

INCLUDE_ASM("asm/nonmatchings/game", func_8004195C);

INCLUDE_ASM("asm/nonmatchings/game", func_80041A28);

void func_80041AF0(void);
/* Controller state and input. */

void func_80041AD0(void) {
    func_80041AF0();
}

INCLUDE_ASM("asm/nonmatchings/game", func_80041AF0);

extern u16 D_8008CA04[];
s32 func_80041B7C(s32 index) {
    return D_8008CA04[index * 4];
}

extern u16 D_8008CA04[];
u16 func_80041B94(s32 index) {
    return D_8008CA04[index];
}

INCLUDE_ASM("asm/nonmatchings/game", func_80041BAC);

INCLUDE_ASM("asm/nonmatchings/game", func_80041BFC);

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
extern s32 gPadBuffers[];
extern u8 D_800B9E00[];
s32 func_80041D60(void) {
    u16 first;
    u16 second;
    u16 value;
    value = *(u16 *)((u8 *)gPadBuffers + 2);
    first = (u16) ~((value >> 8) | ((value & 0xFF) << 8));
    value = *(u16 *)((u8 *)gPadBuffers + 0xE);
    second = (u16) ~((value >> 8) | ((value & 0xFF) << 8));
    if (!(*(u16 *)gPadBuffers & 0xF000))
        first = 0;
    if (!(*(u32 *)D_800B9E00 & 0xF000))
        second = 0;
    return ((u32)second << 16) | first;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80041D60);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80041DEC);

INCLUDE_ASM("asm/nonmatchings/game", func_80041F54);

INCLUDE_ASM("asm/nonmatchings/game", func_800420D8);

INCLUDE_ASM("asm/nonmatchings/game", func_80042218);

#ifdef NON_MATCHING
s32 func_8004229C(s32 arg0) {
    u32 value;
    value = arg0 & 0xFF;
    if (value != 2) {
        if (value < 5U)
            return 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_8004229C);
#endif

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

INCLUDE_ASM("asm/nonmatchings/game", func_800436D0);

INCLUDE_ASM("asm/nonmatchings/game", func_8004382C);

INCLUDE_ASM("asm/nonmatchings/game", func_80043B68);

INCLUDE_ASM("asm/nonmatchings/game", func_80043D6C);

INCLUDE_ASM("asm/nonmatchings/game", func_80043F7C);

INCLUDE_ASM("asm/nonmatchings/game", func_80044114);

void func_8004419C(u8 *object) {
    s32 i;
    *(volatile s16 *)(object + 0x1BC) = 3;
    for (i = 0; i < 4; i++) {
        *(volatile s16 *)(object + 0x2AC) = 0;
        *(volatile s16 *)(object + 0x2B0) = 0;
        object += 0x28;
    }
}

#ifdef NON_MATCHING
extern u8 D_800AD9B0[];
extern u8 D_800BBAAC[];
extern void func_800364C4(void);
void func_800441C8(void) {
    u32 *src;
    u32 *dst;
    s32 row;
    s32 word;
    func_800364C4();
    for (row = 0; row < 0x28; row++) {
        src = (u32 *)(D_800AD9B0 + row * 0x30);
        dst = (u32 *)(D_800BBAAC + row * 0x30);
        for (word = 0; word < 12; word++) {
            dst[word] = src[word];
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800441C8);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_80044248);

INCLUDE_ASM("asm/nonmatchings/game", func_800442C8);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80044DC4);

INCLUDE_ASM("asm/nonmatchings/game", func_80044FF8);

INCLUDE_ASM("asm/nonmatchings/game", func_80045288);

INCLUDE_ASM("asm/nonmatchings/game", func_80045480);

INCLUDE_ASM("asm/nonmatchings/game", func_80045864);

INCLUDE_ASM("asm/nonmatchings/game", func_80045F70);

INCLUDE_ASM("asm/nonmatchings/game", func_80046184);

INCLUDE_ASM("asm/nonmatchings/game", func_80046258);

INCLUDE_ASM("asm/nonmatchings/game", func_8004658C);

INCLUDE_ASM("asm/nonmatchings/game", func_80046BD4);

INCLUDE_ASM("asm/nonmatchings/game", func_800474A0);

INCLUDE_ASM("asm/nonmatchings/game", func_80048118);

INCLUDE_ASM("asm/nonmatchings/game", func_80048568);

INCLUDE_ASM("asm/nonmatchings/game", func_80048700);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80048C90);

INCLUDE_ASM("asm/nonmatchings/game", func_80048EFC);

INCLUDE_ASM("asm/nonmatchings/game", func_8004A0C4);

INCLUDE_ASM("asm/nonmatchings/game", func_8004A510);

INCLUDE_ASM("asm/nonmatchings/game", func_8004AFE0);

INCLUDE_ASM("asm/nonmatchings/game", func_8004B128);

INCLUDE_ASM("asm/nonmatchings/game", func_8004B1C0);

INCLUDE_ASM("asm/nonmatchings/game", func_8004BDD0);

INCLUDE_ASM("asm/nonmatchings/game", func_8004D73C);

INCLUDE_ASM("asm/nonmatchings/game", func_8004DF38);

INCLUDE_ASM("asm/nonmatchings/game", func_8004E294);

INCLUDE_ASM("asm/nonmatchings/game", func_8004E700);

INCLUDE_ASM("asm/nonmatchings/game", func_8004E808);

INCLUDE_ASM("asm/nonmatchings/game", func_8004EA34);

INCLUDE_ASM("asm/nonmatchings/game", func_8004EBE4);

INCLUDE_ASM("asm/nonmatchings/game", func_8004F158);

INCLUDE_ASM("asm/nonmatchings/game", func_8004F880);

INCLUDE_ASM("asm/nonmatchings/game", func_8004FCF4);

INCLUDE_ASM("asm/nonmatchings/game", func_8004FF3C);

INCLUDE_ASM("asm/nonmatchings/game", func_8004FF90);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80050940);

INCLUDE_ASM("asm/nonmatchings/game", func_8005098C);

INCLUDE_ASM("asm/nonmatchings/game", func_80050D1C);

INCLUDE_ASM("asm/nonmatchings/game", func_800511E4);

#ifdef NON_MATCHING
extern s8 D_800A34CC;
extern s8 D_800A34CD;
extern s8 D_800A34CE;
extern s8 D_800A34CF;
extern s8 D_800A34D0;
extern s8 D_800A34D1;
extern s8 D_800A8B00;
extern s8 D_800A8B01;
extern s8 D_800A8B02;

void func_800514EC(s8 arg0, s8 arg1, s8 arg2) {
    u32 value0;
    u32 value1;

    D_800A34CC = arg0;
    D_800A34CD = arg1;
    D_800A34CE = arg2;
    if ((u32)(arg0 & 0xFF) >= 0x40U) {
        D_800A34CF = arg0 - 0x40;
        value0 = arg1 & 0xFF;
    } else {
        D_800A34CF = 0;
        value0 = arg1 & 0xFF;
    }
    if (value0 >= 0x40U) {
        D_800A34D0 = arg1 - 0x40;
        value1 = arg2 & 0xFF;
    } else {
        D_800A34D0 = 0;
        value1 = arg2 & 0xFF;
    }
    if (value1 >= 0x40U) {
        D_800A34D1 = arg2 - 0x40;
    } else {
        D_800A34D1 = 0;
    }
    D_800A8B00 = arg0;
    D_800A8B01 = arg1;
    D_800A8B02 = arg2;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_800514EC);
#endif

INCLUDE_ASM("asm/nonmatchings/game", func_8005157C);

INCLUDE_ASM("asm/nonmatchings/game", func_80051874);

INCLUDE_ASM("asm/nonmatchings/game", func_800524A0);

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

INCLUDE_ASM("asm/nonmatchings/game", func_800539F0);

INCLUDE_ASM("asm/nonmatchings/game", func_80053C00);

INCLUDE_ASM("asm/nonmatchings/game", func_80053D40);

INCLUDE_ASM("asm/nonmatchings/game", func_80055AA4);

INCLUDE_ASM("asm/nonmatchings/game", func_80055C78);

INCLUDE_ASM("asm/nonmatchings/game", func_80056B0C);

INCLUDE_ASM("asm/nonmatchings/game", func_80056B5C);

INCLUDE_ASM("asm/nonmatchings/game", func_80056C84);

INCLUDE_ASM("asm/nonmatchings/game", func_80056F04);

INCLUDE_ASM("asm/nonmatchings/game", func_80057008);

INCLUDE_ASM("asm/nonmatchings/game", func_80057160);

INCLUDE_ASM("asm/nonmatchings/game", func_800571EC);

INCLUDE_ASM("asm/nonmatchings/game", func_80057A9C);

INCLUDE_ASM("asm/nonmatchings/game", func_80057AE4);

INCLUDE_ASM("asm/nonmatchings/game", func_80057BFC);

INCLUDE_ASM("asm/nonmatchings/game", func_80057CCC);

INCLUDE_ASM("asm/nonmatchings/game", func_80057D50);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80057E24);

INCLUDE_ASM("asm/nonmatchings/game", func_80057F34);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80058030);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80058D08);

INCLUDE_ASM("asm/nonmatchings/game", func_80058D14);

void func_80058D8C(void) {
}

INCLUDE_ASM("asm/nonmatchings/game", func_80058D94);

INCLUDE_ASM("asm/nonmatchings/game", func_8005957C);

s32 ColorPack555(s32 red, s32 green, u8 blue) {
    s16 color;
    color =
        (blue >> 3) | (((red << 7) & 0x7C00) | ((green << 2) & 0x3E0)) | -32768;
    return color;
}

INCLUDE_ASM("asm/nonmatchings/game", func_80059648);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8005978C);

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
extern void func_800598FC(void);
void func_800598C4(void) {
    CardTestEvents();
    func_8005A414();
    func_800598FC();
    ChangeClearPAD(0);
}

INCLUDE_ASM("asm/nonmatchings/game", func_800598FC);

extern void CardEnableEvents(void), CardTestEvents(void), func_8005A414(void);
void func_800599E4(void) {
    CardEnableEvents();
    CardTestEvents();
    func_8005A414();
}

INCLUDE_ASM("asm/nonmatchings/game", CardEnableEvents);

INCLUDE_ASM("asm/nonmatchings/game", CardCheckStatus);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80059C2C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80059E0C);

#ifdef NON_MATCHING
extern s32 func_8005A294(void);
extern void CardTestEvents(void);
extern s32 CardWaitForEvent(void);
extern void func_8005A414(void);
s32 func_80059F0C(s32 arg0) {
    s32 channel;
    s32 retries;
    s32 status;
    channel = ((arg0 & 0xFF) != 0) * 0x10;
    retries = 0;
retry:
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
    }
    if (status != 0) {
        retries++;
        if (retries < 8)
            goto retry;
    }
    return status & 0xFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/game", func_80059F0C);
#endif

s32 CardOpenFile(char *path, s32 flags) {
    if (flags == 0x200) {
        flags = 0x10200;
    }
    return open(path, flags);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005A000);

INCLUDE_ASM("asm/nonmatchings/game", func_8005A0F0);

INCLUDE_ASM("asm/nonmatchings/game", CardCountOtherFileBlocks);

INCLUDE_ASM("asm/nonmatchings/game", func_8005A294);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8005A4E0);

INCLUDE_ASM("asm/nonmatchings/game", func_8005A544);

INCLUDE_ASM("asm/nonmatchings/game", func_8005A6EC);

INCLUDE_ASM("asm/nonmatchings/game", func_8005A7B8);

extern u8 D_800A37C8, D_800A37A8, D_800A378C;
void func_8005A804(u8 a, u8 b, u8 c) {
    D_800A37C8 = a;
    D_800A37A8 = b;
    D_800A378C = c;
}

extern u8 D_800A3618;
extern u8 D_800A3624;
extern u8 D_800A364C;

void func_8005A818(s8 first, s8 second, s8 third) {
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

INCLUDE_ASM("asm/nonmatchings/game", func_8005A84C);

INCLUDE_ASM("asm/nonmatchings/game", func_8005A8E0);

INCLUDE_ASM("asm/nonmatchings/game", func_8005A9F4);

INCLUDE_ASM("asm/nonmatchings/game", func_8005AEC8);

INCLUDE_ASM("asm/nonmatchings/game", func_8005AFF0);

INCLUDE_ASM("asm/nonmatchings/game", func_8005B0E4);

INCLUDE_ASM("asm/nonmatchings/game", func_8005B138);

INCLUDE_ASM("asm/nonmatchings/game", func_8005B17C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8005B598);

INCLUDE_ASM("asm/nonmatchings/game", func_8005B688);

INCLUDE_ASM("asm/nonmatchings/game", func_8005B7DC);

INCLUDE_ASM("asm/nonmatchings/game", func_8005B8B8);

extern s32 D_800A3654;
extern u8 D_800A37BC;
s32 func_8005BF68(void) {
    u8 index;
    index = D_800A37BC;
    D_800A37BC = index + 1;
    return D_800A3654 + index * 12;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005BF8C);

INCLUDE_ASM("asm/nonmatchings/game", func_8005C020);

extern void func_80018588(void *, s32, s32);
void func_8005C0F4(u8 *object, s32 value) {
    func_80018588(*(void **)(*(u8 **)(object + 0x20) + 8), -1, value);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005C124);

INCLUDE_ASM("asm/nonmatchings/game", func_8005C8D8);

INCLUDE_ASM("asm/nonmatchings/game", func_8005CA4C);

INCLUDE_ASM("asm/nonmatchings/game", func_8005CBC8);

INCLUDE_ASM("asm/nonmatchings/game", func_8005CC34);

INCLUDE_ASM("asm/nonmatchings/game", func_8005CCEC);

extern u8 D_800A3078[], D_800A3988[];
extern void func_8005C8D8(s32), func_8005CCEC(u8, s32);
void func_8005CEDC(void) {
    s32 i;
    D_800A3988[0] = D_800A3078[0];
    i = 0;
    func_8005C8D8(i);
    i = 1;
    do {
        func_8005CCEC(i, 0);
        i++;
    } while (i < 6);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005CF34);

INCLUDE_ASM("asm/nonmatchings/game", func_8005D094);

INCLUDE_ASM("asm/nonmatchings/game", func_8005DAD4);

INCLUDE_ASM("asm/nonmatchings/game", func_8005DCF0);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8005E408);

extern char D_800BA058[], D_800A333C[];
extern void func_80012EA8(s32, char *);
extern char *strcat(char *, const char *);
void func_8005E43C(s32 value) {
    func_80012EA8(value, D_800BA058);
    strcat(D_800BA058, D_800A333C);
}

extern void *D_800A399C[];
void func_8005E47C(void) {
    D_800A399C[0] = HeapAlloc(0x2580);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005E4A4);

INCLUDE_ASM("asm/nonmatchings/game", func_8005E550);

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
extern void func_80012EA8(s32, char *);
extern char *strcat(char *, const char *);
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
INCLUDE_ASM("asm/nonmatchings/game", func_8005EC5C);
#endif

extern s32 D_8009A31C[];
extern s32 **D_800A3740;
void func_8005ED04(s32 index) {
    D_800A3740[8][2] = D_8009A31C[index & 0xFF];
}

INCLUDE_ASM("asm/nonmatchings/game", func_8005ED28);

INCLUDE_ASM("asm/nonmatchings/game", func_8005ED74);

INCLUDE_ASM("asm/nonmatchings/game", func_8005FE90);

INCLUDE_ASM("asm/nonmatchings/game", func_8005FFA8);

INCLUDE_ASM("asm/nonmatchings/game", func_80060008);

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
extern void func_8005A7B8(s32, s32);
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

INCLUDE_ASM("asm/nonmatchings/game", func_80060F54);

INCLUDE_ASM("asm/nonmatchings/game", func_80060FD8);

INCLUDE_ASM("asm/nonmatchings/game", func_80062874);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80062F04);

INCLUDE_ASM("asm/nonmatchings/game", func_80062F6C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80063538);

INCLUDE_ASM("asm/nonmatchings/game", func_80063638);

INCLUDE_ASM("asm/nonmatchings/game", func_80063694);

INCLUDE_ASM("asm/nonmatchings/game", func_800636EC);

INCLUDE_ASM("asm/nonmatchings/game", func_80063770);

INCLUDE_ASM("asm/nonmatchings/game", func_800637D8);

INCLUDE_ASM("asm/nonmatchings/game", func_8006383C);

INCLUDE_ASM("asm/nonmatchings/game", func_80063874);

void func_80063A20(void) {
}

INCLUDE_ASM("asm/nonmatchings/game", func_80063A28);

INCLUDE_ASM("asm/nonmatchings/game", func_80063AE0);

INCLUDE_ASM("asm/nonmatchings/game", func_80063C34);

INCLUDE_ASM("asm/nonmatchings/game", func_80063E7C);

INCLUDE_ASM("asm/nonmatchings/game", func_80064000);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80064898);

INCLUDE_ASM("asm/nonmatchings/game", func_8006499C);

INCLUDE_ASM("asm/nonmatchings/game", func_80064AB4);

INCLUDE_ASM("asm/nonmatchings/game", func_80064C14);

INCLUDE_ASM("asm/nonmatchings/game", func_80064CD8);

INCLUDE_ASM("asm/nonmatchings/game", func_80064E6C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80065058);

INCLUDE_ASM("asm/nonmatchings/game", func_80065838);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80065F80);

INCLUDE_ASM("asm/nonmatchings/game", func_80066080);

INCLUDE_ASM("asm/nonmatchings/game", func_800663B0);

INCLUDE_ASM("asm/nonmatchings/game", func_8006654C);

INCLUDE_ASM("asm/nonmatchings/game", func_80066730);

INCLUDE_ASM("asm/nonmatchings/game", func_800669B8);

INCLUDE_ASM("asm/nonmatchings/game", func_80066A24);

INCLUDE_ASM("asm/nonmatchings/game", func_80066B08);

INCLUDE_ASM("asm/nonmatchings/game", func_80066B70);

INCLUDE_ASM("asm/nonmatchings/game", func_80066CFC);

INCLUDE_ASM("asm/nonmatchings/game", func_80067020);

INCLUDE_ASM("asm/nonmatchings/game", func_8006709C);

INCLUDE_ASM("asm/nonmatchings/game", func_80067228);

INCLUDE_ASM("asm/nonmatchings/game", func_8006733C);

INCLUDE_ASM("asm/nonmatchings/game", func_80067598);

INCLUDE_ASM("asm/nonmatchings/game", func_800679C4);

INCLUDE_ASM("asm/nonmatchings/game", func_80067AB4);

INCLUDE_ASM("asm/nonmatchings/game", func_80067DFC);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80067ECC);

INCLUDE_ASM("asm/nonmatchings/game", func_80067F34);

INCLUDE_ASM("asm/nonmatchings/game", func_80068220);

INCLUDE_ASM("asm/nonmatchings/game", func_800686FC);

INCLUDE_ASM("asm/nonmatchings/game", func_8006894C);

INCLUDE_ASM("asm/nonmatchings/game", func_80068A3C);

INCLUDE_ASM("asm/nonmatchings/game", func_80068AC4);

INCLUDE_ASM("asm/nonmatchings/game", func_80068CE4);

INCLUDE_ASM("asm/nonmatchings/game", func_800691D4);

INCLUDE_ASM("asm/nonmatchings/game", func_80069744);

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

INCLUDE_ASM("asm/nonmatchings/game", func_800697EC);

INCLUDE_ASM("asm/nonmatchings/game", func_80069A90);

INCLUDE_ASM("asm/nonmatchings/game", func_80069AFC);

INCLUDE_ASM("asm/nonmatchings/game", func_80069C60);

INCLUDE_ASM("asm/nonmatchings/game", func_80069E88);

INCLUDE_ASM("asm/nonmatchings/game", func_80069EB8);

INCLUDE_ASM("asm/nonmatchings/game", func_80069F30);

extern s8 D_800A3938;
extern u8 D_800A3808;
extern u8 D_800A337C;
s32 CardCheckStatus(s32 arg0, s32 arg1);

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
extern s32 CardCountOtherFileBlocks(u8, char *);
u8 CardGetOtherFileBlocks(void) {
    return CardCountOtherFileBlocks(D_800A337C, D_8008FC60);
}

INCLUDE_ASM("asm/nonmatchings/game", func_8006A15C);

INCLUDE_ASM("asm/nonmatchings/game", func_8006A3E0);

INCLUDE_ASM("asm/nonmatchings/game", func_8006A7C8);

INCLUDE_ASM("asm/nonmatchings/game", func_8006AA70);

INCLUDE_ASM("asm/nonmatchings/game", func_8006ABF8);

INCLUDE_ASM("asm/nonmatchings/game", func_8006AC78);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8006ADC4);

INCLUDE_ASM("asm/nonmatchings/game", func_8006B088);

INCLUDE_ASM("asm/nonmatchings/game", func_8006B1CC);

INCLUDE_ASM("asm/nonmatchings/game", func_8006B3E0);

INCLUDE_ASM("asm/nonmatchings/game", func_8006B464);

INCLUDE_ASM("asm/nonmatchings/game", func_8006B5BC);

INCLUDE_ASM("asm/nonmatchings/game", func_8006B6B8);

INCLUDE_ASM("asm/nonmatchings/game", func_8006BA68);

INCLUDE_ASM("asm/nonmatchings/game", func_8006BB1C);

INCLUDE_ASM("asm/nonmatchings/game", func_8006BD68);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8006C5E4);

#ifdef NON_MATCHING
extern u8 *D_800A3908[];
extern u8 *D_800A377C[];

extern char D_800B0A2C[];
void func_8006C668(s32 arg0, s32 arg1) {
    s32 index;
    s32 end;
    u8 *node;
    u8 *sentinel;
    end = arg1;
    if (end >= 6)
        end = (s8)arg0 + 6;
    node = D_800A3908[0];
    index = (s8)arg0;
    if (end >= index) {
        do {
            *(u32 *)(*(u8 **)(node + 0x20) + 8) =
                *(u32 *)(D_800B0A2C + index * 0x10);
            node = *(u8 **)(node + 0x1C);
            index++;
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

INCLUDE_ASM("asm/nonmatchings/game", func_8006C700);

INCLUDE_ASM("asm/nonmatchings/game", func_8006C94C);

extern u8 *D_800A377C[];
void func_8006C9DC(void) {
    *(s16 *)(*(u8 **)(D_800A377C[0] + 0x1C) + 0x1A) = -1;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8006C9F8);

void func_8006CB00(void) {
    s32 value;
    value = *(s16 *)(D_800A377C[0] + 0x1A);
    if (value > 0)
        value = -value;
    else if (value == 0)
        value = -255;
    *(s16 *)(D_800A377C[0] + 0x1A) = value;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8006CB40);

INCLUDE_ASM("asm/nonmatchings/game", func_8006CB80);

INCLUDE_ASM("asm/nonmatchings/game", func_8006CE64);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8006CF90);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8006D178);

INCLUDE_ASM("asm/nonmatchings/game", func_8006D258);

INCLUDE_ASM("asm/nonmatchings/game", func_8006D424);

INCLUDE_ASM("asm/nonmatchings/game", func_8006D4C8);

INCLUDE_ASM("asm/nonmatchings/game", func_8006D634);

INCLUDE_ASM("asm/nonmatchings/game", func_8006D684);

INCLUDE_ASM("asm/nonmatchings/game", func_8006D708);

INCLUDE_ASM("asm/nonmatchings/game", func_8006D8E8);

INCLUDE_ASM("asm/nonmatchings/game", func_8006DA40);

INCLUDE_ASM("asm/nonmatchings/game", func_8006DCF0);

INCLUDE_ASM("asm/nonmatchings/game", func_8006DD28);

INCLUDE_ASM("asm/nonmatchings/game", func_8006DE68);

INCLUDE_ASM("asm/nonmatchings/game", func_8006DF98);

INCLUDE_ASM("asm/nonmatchings/game", func_8006E07C);

INCLUDE_ASM("asm/nonmatchings/game", func_8006E484);

INCLUDE_ASM("asm/nonmatchings/game", func_8006E628);

INCLUDE_ASM("asm/nonmatchings/game", func_8006E770);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8006F128);

INCLUDE_ASM("asm/nonmatchings/game", func_8006F194);

INCLUDE_ASM("asm/nonmatchings/game", func_8006F200);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8006F9C4);

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

INCLUDE_ASM("asm/nonmatchings/game", func_8006FDDC);

extern s32 *D_800A3398;
void func_8006FBB0(void);
void func_8006FDDC(void);
void func_80070018(void) {
    if (D_800A3398[0x12C / 4])
        func_8006FBB0();
    else
        func_8006FDDC();
}

INCLUDE_ASM("asm/nonmatchings/game", func_8007005C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80070750);

INCLUDE_ASM("asm/nonmatchings/game", func_80070798);

INCLUDE_ASM("asm/nonmatchings/game", func_800708D8);

INCLUDE_ASM("asm/nonmatchings/game", func_80070A60);

INCLUDE_ASM("asm/nonmatchings/game", func_80070F40);

INCLUDE_ASM("asm/nonmatchings/game", func_800710D8);

INCLUDE_ASM("asm/nonmatchings/game", func_800711F0);

INCLUDE_ASM("asm/nonmatchings/game", func_800718D4);

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

INCLUDE_ASM("asm/nonmatchings/game", func_800720D0);

INCLUDE_ASM("asm/nonmatchings/game", func_80072178);

INCLUDE_ASM("asm/nonmatchings/game", func_800722D0);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80072750);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80072A70);

INCLUDE_ASM("asm/nonmatchings/game", func_80072AFC);

INCLUDE_ASM("asm/nonmatchings/game", func_80072B4C);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80072BDC);

INCLUDE_ASM("asm/nonmatchings/game", func_80072CA8);

INCLUDE_ASM("asm/nonmatchings/game", func_80072FE4);

INCLUDE_ASM("asm/nonmatchings/game", func_80073100);

INCLUDE_ASM("asm/nonmatchings/game", func_80073948);

extern volatile s32 *D_800A351C;
void func_80073978(void) {
    D_800A351C[0x7B78 / 4] = 0;
}

INCLUDE_ASM("asm/nonmatchings/game", func_8007398C);

INCLUDE_ASM("asm/nonmatchings/game", func_800739E0);

INCLUDE_ASM("asm/nonmatchings/game", func_80073A44);

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

INCLUDE_ASM("asm/nonmatchings/game", func_80073BEC);
