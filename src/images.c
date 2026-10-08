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
extern s32 func_8001E7EC(void *, s32, s32);
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
extern s16 gFontColorRed, gFontColorGreen, gFontColorBlue;
extern void func_800180C0(s8, s32, s32, s32);
extern s16 D_800A2D88[];
extern u8 D_8008CC9C[];
extern u8 D_8008CCA8[];
extern u8 D_8008CCBC[];
extern u8 D_8008CCD0[];
extern u8 D_8008CCE0[];
extern u8 D_8008CCF0[];
extern s32 D_800A2EACAbsolute[];
extern s32 sprintfArgs(s8 *, u8 *, ...);
extern void func_80018588(void *, s32, s32);
extern void func_80050028Text(s8 *, s16, s16, s8);
extern void func_800183C0(s32, s32, s32, s32);
extern void func_800180C0(s8, s32, s32, s32);
extern s16 D_800A2D88[];
extern void func_800180C0(s8, s32, s32, s32);
extern s16 D_800A2D88[];
extern void func_800180C0(s8, s32, s32, s32);
extern s16 D_800A2D88[];
extern u32 gPrimitiveCursor[];
extern s32 D_800A2EC8[];
extern s32 D_800A39C8[];
extern s32 D_800A397CAbsolute[];
extern s32 D_800A36D0Absolute[];
extern s32 MathMultiplyFixed16(s32, s32);
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
typedef struct ListNode28 ListNode28;
typedef struct DoublyLinkedNode {
    struct DoublyLinkedNode *next;
    struct DoublyLinkedNode *previous;
} DoublyLinkedNode;
extern void func_8001F2C4(s32 arg0, s32 arg1, s32 arg2);
extern void func_8001ED84(s32 *vec);
extern s32 D_800A2EC8Absolute[];
extern ListNode28 *D_800A3A40Absolute[];
extern s32 D_800A2EC8Absolute[];
extern ListNode28 *D_800A3A40Absolute[];
extern s32 gOrderingTableBankAbsolute[];
extern s32 D_800A2EC8Absolute[];
extern ListNode28 *D_800A3A40Absolute[];
extern void (*D_80091080[])(void *);
extern long RotTransPers_nom();
extern void func_8003382C();
extern s32 D_800A2DEC[], D_800A2DF0[], D_800A37E8[], D_800A397C[], D_800A3A3C[];
extern u8 D_800A3C6C[];
extern s32 gOrderingTableBankAbsolute[];
extern u32 gPrimitiveCursor[];
extern s32 D_800A39C8[];
extern s32 D_800A36D0Absolute[];
extern u8 D_800A3F4C[];
extern s32 D_800A2DBC;
extern s32 D_800BE978[];
extern ListNode28 *D_800A3A40Absolute[];
extern void func_8001DB20(ListNode28 *, s32);
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
void ListInsertBefore(u8 **head, u8 *node, u8 *before);
void ListRemoveNode(u8 **head, u8 *target);
void func_8001C668(void *arg0, void *arg1);
void ListPushFront(u8 *node, u8 **head, u8 **tail);
void ListRemoveNodeWithTail(ListNode28 *node, ListNode28 **head,
                            ListNode28 **tail);
void ListPushFrontDoublyLinked(DoublyLinkedNode *node, DoublyLinkedNode **last,
                               DoublyLinkedNode **first);
void func_8001C99C(u8 *arg0);
void func_8001CAB8(u8 *arg0);
void func_8001CBD4(u8 *arg0);
void func_8001CC7C(u8 *arg0);
void func_8001CDDC(u8 *arg0);
void func_8001CF38(u8 *arg0);
void ListDispatchCallbacks(u8 *arg0);
void func_8001D108(u8 *arg0);
void func_8001D1B0(s32 *destination, s32 *source);
void func_8001D1E4(void);
void func_8001D218(void);
void func_8001D778(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5,
                   u8 arg6, s32 arg7);
void func_8001DA48(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_8001DF60(void);
void func_8001DFC8(void);

/* Images and matrix state. */

typedef struct {
    u8 pad[16];
} Unk16;
extern Unk16 *D_800A36CC;

Unk16 *func_8001E040(s32 i) {
    return &D_800A36CC[i];
}

void func_8001E050(s32 fileName) {
    extern s32 FileOpen(s32, void *);
    extern void GraphicsInit(void);
    extern u_long *FntFlush(s32);
    extern s32 FileSeek(void *, s32, s32);
    extern void FileRead(s32, s32, s32, s32);
    extern void GraphicsLoadImageWithXOffset(s32);
    extern void FileClose(s32);
    extern u8 D_800A2DC0[];
    extern char D_8008CD0C[];
    extern void *D_800A368C;
    extern void *D_800A37E4;
    extern u16 D_800A3754;
    extern u16 D_800A3738;
    s32 handle;
    u8 *image;
    s32 size;
    u8 *head;
    u16 w;
    u16 h;
    s32 count;
    s32 i;
    s32 limit;
    u32 base;
    volatile s32 pad[2];

    handle = FileOpen(fileName, D_800A2DC0);
    if (handle == 0) {
        GraphicsInit();
        FntPrint(D_8008CD0C);
        FntFlush(-1);
        for (;;) {
        }
    }
    size = FileSeek(handle, 0, 2);
    FileSeek(handle, 0, 0);
    D_800A368C = (void *)STACK_BLOCK_80193000;
    FileRead((s32)STACK_BLOCK_80193000, 1, size, handle);
    image = (u8 *)D_800A368C;
    w = *(u16 *)image;
    h = *(u16 *)(image + 2);
    head = image + 4;
    D_800A37E4 = head;
    D_800A3754 = w;
    count = (s16)w;
    D_800A3738 = h;
    D_800A36CC = (Unk16 *)(head + count * 8);
    if (count > 0) {
        i = 0;
        base = (u32)image;
        limit = count;
        do {
            ((u32 *)head)[i + i] += base;
            ((u32 *)head)[i + i + 1] += base;
            i++;
        } while (i < limit);
    }
    GraphicsLoadImageWithXOffset(-0x100);
    FileClose(handle);
}

#ifdef NON_MATCHING
/* Wave-33 (2026-10-06): 11 bytes off (4 instructions, register-coalesce of the
 * count sign-extension temp). The old positional-cc1-ICE wall is DEAD at this
 * TU position (block-scope externs + TU shift; ~50 compiles, zero ICEs).
 * gcc-source analysis (reorg.c) says retail's delay-slot fill is unreachable
 * from plain C. Candidate name: GraphicsSelectImageBank. */
void func_8001E17C(s32 index) {
    extern s32 D_800B9F44[];
    extern void *D_800A368C;
    extern void *D_800A37E4;
    extern u16 D_800A3754;
    extern u16 D_800A3738;
    extern void GraphicsLoadImageWithXOffset(s32);
    volatile s32 pad[2];
    register u8 *reg4 asm("$4");
    register u8 *headReg asm("$7");
    register s32 iReg asm("$5");
    register u32 baseReg asm("$6");
    register s32 limitReg asm("$8");
    register s32 count asm("$3");
    register u16 wReg asm("$2");
    u16 h;

    reg4 = (u8 *)D_800B9F44[index];
    D_800A368C = reg4;
    wReg = *(u16 *)reg4;
    h = *(u16 *)(reg4 + 2);
    headReg = reg4 + 4;
    D_800A37E4 = headReg;
    D_800A3754 = wReg;
    count = (s16)wReg;
    D_800A3738 = h;
    D_800A36CC = (Unk16 *)(headReg + count * 8);
    asm volatile(".set\tnoreorder\n"
                 "\tblez\t%0, 9f\n"
                 "\tmove\t%1, $0\n"
                 "\tmove\t%2, %3\n"
                 "\tmove\t%4, %0\n"
                 "\tmove\t%3, %5\n"
                 "\t.set\treorder"
                 :
                 : "r"(count), "r"(iReg), "r"(baseReg), "r"(reg4),
                   "r"(limitReg), "r"(headReg)
                 : "memory");
    do {
        ((u32 *)reg4)[0] += baseReg;
        ((u32 *)reg4)[1] += baseReg;
        iReg += 1;
        reg4 = (u8 *)((u32 *)reg4 + 2);
    } while (iReg < limitReg);
    asm volatile("9:");
    if (D_800A2EDAnm[0] != 0) {
        GraphicsLoadImageWithXOffset(0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/images", func_8001E17C);
#endif

void func_8001E230(s32 arg0, s32 arg1) {
    extern s32 FileOpen(s32, void *);
    extern void GraphicsInit(void);
    extern u_long *FntFlush(s32);
    extern s32 FileSeek(void *, s32, s32);
    extern void FileRead(s32, s32, s32, s32);
    extern void GraphicsLoadImageWithXOffset(s32);
    extern void FileClose(s32);
    extern u8 D_800A2DC0[];
    extern char D_8008CD0C[];
    extern void *D_800A368C;
    extern void *D_800A37E4;
    extern u16 D_800A3754;
    extern u16 D_800A3738;
    s32 handle;
    u8 *image;
    s32 size;
    u8 *head;
    u16 w;
    u16 h;
    s32 count;
    s32 i;
    s32 limit;
    u32 base;
    volatile s32 pad[2];

    handle = FileOpen(arg0, D_800A2DC0);
    if (handle == 0) {
        GraphicsInit();
        FntPrint(D_8008CD0C);
        FntFlush(-1);
        for (;;) {
        }
    }
    size = FileSeek(handle, 0, 2);
    FileSeek(handle, 0, 0);
    size = (size + 0x7FF) >> 11 << 11;
    if (arg1 == 0) {
        D_800A368C = HeapAlloc(size);
    } else {
        D_800A368C = (void *)arg1;
    }
    FileRead((s32)D_800A368C, 1, size, handle);
    image = (u8 *)D_800A368C;
    w = *(u16 *)image;
    h = *(u16 *)(image + 2);
    head = image + 4;
    D_800A37E4 = head;
    D_800A3754 = w;
    count = (s16)w;
    D_800A3738 = h;
    D_800A36CC = (Unk16 *)(head + count * 8);
    if (count > 0) {
        i = 0;
        base = (u32)image;
        limit = count;
        do {
            ((u32 *)head)[i + i] += base;
            ((u32 *)head)[i + i + 1] += base;
            i++;
        } while (i < limit);
    }
    GraphicsLoadImageWithXOffset(0);
    FileClose(handle);
}

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

INCLUDE_ASM("asm/nonmatchings/images", func_8001E3E0);

extern s32 D_800A2DC4w15 asm("D_800A2DC4.NON_MATCHING");
extern s32 D_800A2EC4w15[] asm("D_800A2EC4.NON_MATCHING");
extern s32 D_800A2ED0w15[] asm("D_800A2ED0.NON_MATCHING");
extern u8 D_800A3F7Cw15[] asm("D_800A3F7C.NON_MATCHING");
extern u8 D_800A4034w15[] asm("D_800A4034.NON_MATCHING");
extern u8 D_800A43BCw15[] asm("D_800A43BC.NON_MATCHING");
extern u8 D_800A433Cw15[] asm("D_800A433C.NON_MATCHING");
extern s32 D_800A39C4w15[] asm("D_800A39C4.NON_MATCHING");
extern s32 D_800A39CCw15[] asm("D_800A39CC.NON_MATCHING");

s32 func_8001E7EC(void *arg0, s32 arg1, s32 arg2) {
    u8 *envPtr;

    if (arg2 != 0) {
        FntPrint((const char *)arg1);
        FntFlush(-1);
    }
    D_800A2DC4w15 = gOTBnm[0] / 2;
    DrawSync(0);
    VSync(0);
    if (arg2 == 0) {
        func_80012D10(0);
    }
    envPtr = D_800A3F7Cw15 + D_800A2DC4w15 * 0x5C;
    PutDrawEnv((DRAWENV *)envPtr);
    PutDispEnv((DISPENV *)(D_800A4034w15 + D_800A2DC4w15 * 0x14));
    if (arg2 != 0) {
        return 0;
    }
    if (D_800A2EA4nm[0] == 2) {
        u8 *otFFC;
        u8 *ot1000;
        u8 *ot1FFC;

        D_800A39C8nm[0] = (s32)arg0;
        func_8003565C(0);
        ot1000 = (u8 *)arg0 + 0x1000;
        D_800A39C4w15[1] = (s32)ot1000;
        func_800356A8(1);
        otFFC = (u8 *)arg0 + 0xFFC;
        AddPrim(otFFC, D_800A43BCw15 + (D_800A2DC4w15 << 6));
        ot1FFC = (u8 *)arg0 + 0x1FFC;
        AddPrim(ot1FFC, D_800A43BCw15 + 0x80 + (D_800A2DC4w15 << 6));
        D_800A39CCw15[-1] = (s32)ot1000;
        if ((D_800A2ED0w15[0] & 8) == 0) {
            func_8001D778(0, 0x77, 0x140, 2, 8, 8, 8, 0);
        }
        AddPrim(ot1000, D_800A43BCw15 - 0x80 + (D_800A2DC4w15 << 6));
        DrawOTag((OT_TYPE *)otFFC);
        DrawOTag((OT_TYPE *)ot1FFC);
    } else if (D_800A2EC4w15[0] != 0 && D_800A2EC8nm[0] == 0) {
        u8 *otFFC;
        u8 *ot1000;
        u8 *ot1FFC;

        D_800A39C8nm[0] = (s32)arg0;
        func_8003565C(0);
        ot1000 = (u8 *)arg0 + 0x1000;
        func_8003587C(ot1000);
        otFFC = (u8 *)arg0 + 0xFFC;
        AddPrim(otFFC, D_800A433Cw15 + (D_800A2DC4w15 << 6));
        func_8001DA48((u8 *)arg0, 0xC6, 0x12, 0x69, 0x26);
        DrawOTag((OT_TYPE *)otFFC);
        ot1FFC = (u8 *)arg0 + 0x1FFC;
        AddPrim(ot1FFC, D_800A433Cw15 + 0x180 + (D_800A2DC4w15 << 6));
        AddPrim(ot1000, D_800A433Cw15 + (D_800A2DC4w15 << 6));
        DrawOTag((OT_TYPE *)ot1FFC);
    } else {
        func_8003565C(0);
        DrawOTag((OT_TYPE *)((u8 *)arg0 + 0xFFC));
    }
}

extern s32 D_800A2DC8;

void GraphicsSetGeomOffsetForMode(s32 geomOffsetX, s32 mode) {
    switch (mode) {
    case 0:
        SetGeomOffset(D_800A2DC8 / 2, 0x46);
        break;
    case 1:
        SetGeomOffset(D_800A2DC8 / 2, 0x3C);
        break;
    case 3:
        SetGeomOffset(D_800A2DC8 / 2, 0x82);
        break;
    case 4:
        SetGeomOffset(0x32, 0x12);
        break;
    }
}

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

void func_8001ECD8(void) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = D_800A36B8;
    b = D_800A36C8;
    c = D_800A36D8;
    d = D_800A36DC;
    D_800A36C8 = a;
    a = D_800A36C0;
    D_800A36D8 = a;
    a = D_800A36D4;
    D_800A36B8 = b;
    D_800A36C0 = c;
    D_800A36D4 = d;
    D_800A36DC = a;
}

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

extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;

void func_8001ED84(s32 *vec) {
    s32 x, y, z;
    s32 a, b, c;

    x = vec[0];
    y = vec[1];
    z = vec[2];
    a = (D_800A36B0 * x + D_800A36B8 * y + D_800A36C0 * z) >> 16;
    b = (D_800A36C8 * x + D_800A36D0 * y + D_800A36D4 * z) >> 16;
    c = (D_800A36D8 * x + D_800A36DC * y + D_800A36E8 * z) >> 16;
    vec[0] = a;
    vec[1] = b;
    vec[2] = c;
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

void func_8001F198(void) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = D_800A3790;
    b = D_800A3798;
    c = D_800A37AC;
    d = D_800A37B4;
    D_800A3798 = a;
    a = D_800A3794;
    D_800A37AC = a;
    a = D_800A37A4;
    D_800A3790 = b;
    D_800A3794 = c;
    D_800A37A4 = d;
    D_800A37B4 = a;
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

void func_8001F1D4(s32 *vec) {
    s32 x, y, z;
    s32 a, b, c;

    x = vec[0];
    y = vec[1];
    z = vec[2];
    a = (D_800A3784 * x + D_800A3790 * y + D_800A3794 * z) >> 16;
    b = (D_800A3798 * x + D_800A379C * y + D_800A37A4 * z) >> 16;
    c = (D_800A37AC * x + D_800A37B4 * y + D_800A37C4 * z) >> 16;
    vec[0] = a;
    vec[1] = b;
    vec[2] = c;
}

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

extern s32 D_800A3784, D_800A3790, D_800A3794, D_800A3798, D_800A379C,
    D_800A37A4, D_800A37AC, D_800A37B4, D_800A37C4;
extern s32 MathMultiplyFixed16(s32, s32);

void func_8001F5BC(s32 arg0, s32 indexA, s32 indexB) {
    s32 valueA;
    s32 slotA;
    s32 slotB;
    s32 valueB;
    s32 product;

    valueA = ((s32 *)D_800A3A2C)[indexA];
    slotA = ((s32 *)D_800A3A34)[indexA];
    valueB = ((s32 *)D_800A3A2C)[indexB];
    slotB = ((s32 *)D_800A3A34)[indexB];

    D_800A3784 = valueA;
    product = MathMultiplyFixed16(slotA, slotB);
    D_800A3790 = -product;
    product = MathMultiplyFixed16(slotA, valueB);
    D_800A3794 = -product;
    D_800A3798 = 0;
    D_800A379C = valueB;
    D_800A37A4 = -slotB;
    D_800A37AC = slotA;
    product = MathMultiplyFixed16(valueA, slotB);
    D_800A37B4 = product;
    product = MathMultiplyFixed16(valueA, valueB);
    D_800A37C4 = product;
}

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

void func_8001F728(s32 arg0) {
    typedef struct {
        s32 x;
        s32 y;
        s32 z;
    } Vec3;
    Vec3 *v;
    s32 x;
    s32 y;
    s32 z;
    extern s32 MathMultiplyFixed16(s32, s32);
    extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
        D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;

    v = (Vec3 *)arg0;
    x = v->x;
    y = v->y;
    z = v->z;
    v->x = MathMultiplyFixed16(D_800A36B0, x) +
           MathMultiplyFixed16(D_800A36B8, y) +
           MathMultiplyFixed16(D_800A36C0, z);
    v->y = MathMultiplyFixed16(D_800A36C8, x) +
           MathMultiplyFixed16(D_800A36D0, y) +
           MathMultiplyFixed16(D_800A36D4, z);
    v->z = MathMultiplyFixed16(D_800A36D8, x) +
           MathMultiplyFixed16(D_800A36DC, y) +
           MathMultiplyFixed16(D_800A36E8, z);
}

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

/* Wall: gcc schedules the second D_800A3A34 value reload (needed for the
 * third read) AFTER the subu/sra/sh chain instead of directly after the
 * call as retail does, so it needs a hazard nop (+4 bytes). The product
 * save (move s0,v0) is also emitted before the cos shift instead of in
 * the second jal's delay slot. Three source shapes tried. */
void func_8001F90C(s32 arg0, s32 arg1, s32 arg2, s16 *arg3) {
    s32 *matrixB;
    s32 productA;
    s32 productB;

    productA = MathMultiplyFixed16(((s32 *)D_800A3A2C)[arg0], arg1 << 16);
    productB = MathMultiplyFixed16(((s32 *)D_800A3A34)[arg0], arg2 << 16);
    matrixB = (s32 *)D_800A3A34;
    arg3[0] = (productA - productB) >> 16;
    arg3[1] = (MathMultiplyFixed16(matrixB[arg0], arg1 << 16) +
               MathMultiplyFixed16(((s32 *)D_800A3A2C)[arg0], arg2 << 16)) >>
              16;
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

#ifdef NON_MATCHING
/* Wall: same scheduler wall as func_8001FB28: load/negu placement differs. */
void func_8001FAC0(u8 *arg0, s32 index) {
    *(s32 *)((u8 *)arg0 + 0x18) = ((s16 *)D_800A384C)[index] * 4;
    *(s32 *)((u8 *)arg0 + 0x30) = 0;
    *(s32 *)((u8 *)arg0 + 0x24) = ((s16 *)D_800A3854)[index] * 4;
    *(s32 *)((u8 *)arg0 + 0x1C) = -((s16 *)D_800A3854)[index] * 4;
    *(s32 *)((u8 *)arg0 + 0x34) = 0;
    *(s32 *)((u8 *)arg0 + 0x20) = 0;
    *(s32 *)((u8 *)arg0 + 0x2C) = 0;
    *(s32 *)((u8 *)arg0 + 0x38) = 0x10000;
    *(s32 *)((u8 *)arg0 + 0x28) = ((s16 *)D_800A384C)[index] * 4;
}
#else
void func_8001FAC0(u8 *arg0, s32 index) {
    s16 *table1;
    s16 *table2;
    s32 value1;
    s32 value2;
    s32 value3;

    table1 = (s16 *)D_800A384C;
    value1 = table1[index] * 4;
    table2 = (s16 *)D_800A3854;
    *(s32 *)(arg0 + 0x18) = value1;
    value2 = table2[index] * 4;
    *(s32 *)(arg0 + 0x30) = 0;
    *(s32 *)(arg0 + 0x24) = value2;
    *(s32 *)(arg0 + 0x1C) = -table2[index] * 4;
    value3 = table1[index] * 4;
    *(s32 *)(arg0 + 0x34) = 0;
    *(s32 *)(arg0 + 0x20) = 0;
    *(s32 *)(arg0 + 0x2C) = 0;
    *(s32 *)(arg0 + 0x38) = 0x10000;
    *(s32 *)(arg0 + 0x28) = value3;
}

#endif

void func_8001FB28(u8 *arg0, s32 index) {
    s32 *table1;
    s32 *table2;
    s32 value1;
    s32 value2;
    s32 value3;

    table1 = (s32 *)D_800A3A2C;
    value1 = table1[index];
    table2 = (s32 *)D_800A3A34;
    *(s32 *)(arg0 + 0x60) = value1;
    value2 = table2[index];
    *(s32 *)(arg0 + 0x78) = 0;
    *(s32 *)(arg0 + 0x6C) = value2;
    *(s32 *)(arg0 + 0x64) = -table2[index];
    value3 = table1[index];
    *(s32 *)(arg0 + 0x7C) = 0;
    *(s32 *)(arg0 + 0x68) = 0;
    *(s32 *)(arg0 + 0x74) = 0;
    *(s32 *)(arg0 + 0x80) = 0x10000;
    *(s32 *)(arg0 + 0x70) = value3;
}

s32 func_8001FB80(void *arg0) {
    s32 dx;
    s32 dy;
    s32 dz;

    dx = *(s32 *)((u8 *)arg0 + 0x9C);
    dy = *(s32 *)((u8 *)arg0 + 0xA0);
    dz = *(s32 *)((u8 *)arg0 + 0xA4);
    return MathSqrt(dx * dx + dy * dy + dz * dz);
}

s32 func_8001FBDC(s32 x, s32 y, s32 z) {
    s32 xSq;
    s32 ySq;
    s32 zSq;
    s32 sum;

    xSq = x * x;
    ySq = y * y;
    zSq = z * z;
    sum = xSq + ySq;
    return MathSqrt(sum + zSq);
}
