#include "common.h"
#include "libpress.h"
#include "fixed_addrs.h"
#include <psxsdk/libgpu.h>
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/libcd.h>
#include <psxsdk/libgte.h>
#include "gte.h"
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
typedef struct {
    u8 pad[16];
} Unk16;
extern Unk16 *D_800A36CC;
extern void *D_800A37E4;
extern s32 D_800A2DC4w15 asm("D_800A2DC4.NON_MATCHING");
extern s32 D_800A2EC4w15[] asm("D_800A2EC4.NON_MATCHING");
extern s32 D_800A2ED0w15[] asm("D_800A2ED0.NON_MATCHING");
extern u8 D_800A3F7Cw15[] asm("D_800A3F7C.NON_MATCHING");
extern u8 D_800A4034w15[] asm("D_800A4034.NON_MATCHING");
extern u8 D_800A43BCw15[] asm("D_800A43BC.NON_MATCHING");
extern u8 D_800A433Cw15[] asm("D_800A433C.NON_MATCHING");
extern s32 D_800A39C4w15[] asm("D_800A39C4.NON_MATCHING");
extern s32 D_800A39CCw15[] asm("D_800A39CC.NON_MATCHING");
extern s32 D_800A2DC8;
extern u8 D_800A3F95[];
extern u8 D_800A3F96[];
extern u8 D_800A3F97[];
extern u8 D_800A3FF1[];
extern u8 D_800A3FF2[];
extern u8 D_800A3FF3[];
extern DRAWENV gDrawEnvironment;
extern DISPENV gDisplayEnvironment;
extern u8 D_800910A4[];
extern u8 *D_800A3668, *D_800A384C, *D_800A3854, *D_800A3A2C, *D_800A3A34;
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A36B0;
extern s32 D_800A36B8;
extern s32 D_800A36C0;
extern s32 D_800A36C8;
extern s32 D_800A36D0;
extern s32 D_800A36D4;
extern s32 D_800A36D8;
extern s32 D_800A36DC;
extern s32 D_800A36E8;
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A3784;
extern s32 D_800A3790;
extern s32 D_800A3794;
extern s32 D_800A3798;
extern s32 D_800A379C;
extern s32 D_800A37A4;
extern s32 D_800A37AC;
extern s32 D_800A37B4;
extern s32 D_800A37C4;
extern s32 D_800A3784;
extern s32 D_800A3790;
extern s32 D_800A3794;
extern s32 D_800A3798;
extern s32 D_800A379C;
extern s32 D_800A37A4;
extern s32 D_800A37AC;
extern s32 D_800A37B4;
extern s32 D_800A37C4;
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
extern s32 D_800A3784;
extern s32 D_800A3790;
extern s32 D_800A3794;
extern s32 D_800A3798;
extern s32 D_800A379C;
extern s32 D_800A37A4;
extern s32 D_800A37AC;
extern s32 D_800A37B4;
extern s32 D_800A37C4;
extern s32 MathMultiplyFixed16(s32, s32);
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 MathMultiplyFixed16(s32, s32);
extern s32 D_800A3784, D_800A3790, D_800A3794, D_800A3798, D_800A379C,
    D_800A37A4, D_800A37AC, D_800A37B4, D_800A37C4;
extern s32 D_800A3784, D_800A3790, D_800A3794, D_800A3798, D_800A379C,
    D_800A37A4, D_800A37AC, D_800A37B4, D_800A37C4;
extern s32 MathMultiplyFixed16(s32, s32);
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A36B0;
extern s32 D_800A36B8;
extern s32 D_800A36C0;
extern s32 D_800A36C8;
extern s32 D_800A36D0;
extern s32 D_800A36D4;
extern s32 D_800A36D8;
extern s32 D_800A36DC;
extern s32 D_800A36E8;
extern s32 D_800A3784, D_800A3790, D_800A3794, D_800A3798, D_800A379C,
    D_800A37A4, D_800A37AC, D_800A37B4, D_800A37C4;
extern s32 D_800AE868[];
extern s32 D_800AE86C[];
extern s32 D_800AE870[];
extern s32 D_800AE874[];
extern s32 D_800AE878[];
extern s32 D_800AE87C[];
extern s32 D_800AE880[];
extern s32 D_800AE884[];
extern s32 D_800AE888[];
extern s32 D_800AE868[];
extern s32 D_800AE86C[];
extern s32 D_800AE870[];
extern s32 D_800AE874[];
extern s32 D_800AE878[];
extern s32 D_800AE87C[];
extern s32 D_800AE880[];
extern s32 D_800AE884[];
extern s32 D_800AE888[];
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
Unk16 *func_8001E040(s32 i);
void func_8001E050(s32 fileName);
void func_8001E230(s32 arg0, s32 arg1);
void GraphicsLoadImageWithXOffset(s32 xOffset);
void func_8001E7EC(void *arg0, s32 arg1, s32 arg2);
void GraphicsSetGeomOffsetForMode(s32 geomOffsetX, s32 mode);
void GraphicsSetClearColor(u8 r, u8 g, u8 b);
void GraphicsApplyDisplayEnvironments(void);
void GraphicsPartitionWorkBuffers(void);
void func_8001EBE8(s32 *p);
void func_8001EC38(s32 *arg0);
void func_8001EC88(s32 *a, s32 *b, s32 *c);
void func_8001ECD8(void);
void func_8001ED14(s32 *p);
void func_8001ED4C(s32 *p);
void func_8001ED84(s32 *vec);
void func_8001EE74(s32 *arg0);
void func_8001EEC4(s32 *arg0);
void MatrixCombineState(void);
void func_8001F198(void);
void func_8001F1D4(s32 *vec);
void func_8001F2C4(s32 arg0, s32 arg1, s32 arg2);
void func_8001F440(s32 arg0, s32 arg1, s32 arg2);
void func_8001F5BC(s32 arg0, s32 indexA, s32 indexB);
void func_8001F684(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8001F728(s32 arg0);
void func_8001F828(s32 *p);
void func_8001F874(s32 *arg0);
void func_8001F8C0(s32 *object);
void func_8001F90C(s32 arg0, s32 arg1, s32 arg2, s16 *arg3);
void MatrixSaveState(void);
void MatrixRestoreState(void);
void func_8001FAC0(u8 *arg0, s32 index);
void func_8001FB28(u8 *arg0, s32 index);
s32 func_8001FB80(void *arg0);
s32 func_8001FBDC(s32 x, s32 y, s32 z);

s32 VectorGetMagnitude2D(void *arg0) {
    s32 dx;
    s32 dy;

    dx = *(s32 *)((u8 *)arg0 + 0x9C);
    dy = *(s32 *)((u8 *)arg0 + 0xA0);
    return MathSqrt(dx * dx + dy * dy);
}

INCLUDE_RODATA("asm/nonmatchings/objects", D_8008CF28);
extern char D_8008CF28[];
extern u32 D_800A38F4Abs[] asm("D_800A38F4.NON_MATCHING");
extern s32 D_800A2DE4Small asm("D_800A2DE4.NON_MATCHING");
extern s32 D_800A3A38Small asm("D_800A3A38.NON_MATCHING");
extern s32 D_800A2E94[];
extern s32 D_800A2ED4[];
extern s32 D_800A2EC8[];
extern s32 D_800A37E8Small asm("D_800A37E8.NON_MATCHING");
extern s32 D_800A3550Small asm("D_800A3550.NON_MATCHING");
extern s32 D_800A3804Small asm("D_800A3804.NON_MATCHING");
extern s32 D_800A3A3CSmall asm("D_800A3A3C.NON_MATCHING");
extern s32 D_800A2DECSmall asm("D_800A2DEC.NON_MATCHING");
extern s32 D_800A397CSmall asm("D_800A397C.NON_MATCHING");
extern s32 D_800A2DF0Small asm("D_800A2DF0.NON_MATCHING");
extern s32 D_800A2DF4Small asm("D_800A2DF4.NON_MATCHING");
extern s32 D_800A3A90Small asm("D_800A3A90.NON_MATCHING");

void func_8001FC6C(void) {
    s32 count;
    void *ptr;
    s32 quotient;

    count = D_800A38F4Abs[0] / 20;
    D_800A2DE4Small = count;
    ptr = HeapAlloc(count * 20);
    D_800A3A38Small = (s32)ptr;
    if (ptr == 0) {
        SystemShowFatalError(D_8008CF28);
    }
    quotient = D_800A2DE4Small / (D_800A2E94[0] + 6);
    D_800A37E8Small = 0;
    D_800A3550Small = 0;
    D_800A3804Small = 0;
    D_800A3A3CSmall = 0;
    D_800A2ED4[0] = 0;
    D_800A2EC8[0] = 0;
    D_800A2DECSmall = 0;
    D_800A397CSmall = 1;
    D_800A2DF0Small = 1;
    D_800A2DF4Small = 1;
    D_800A3A90Small = quotient;
}

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

/* Shared layout of a car and the camera that follows it. */
typedef struct {
    Vec3 pos;               /* 0x000 */
    u8 unkC[0xC];           /* 0x00C */
    Vec3 basis[3];          /* 0x018 */
    Vec3 rot[3];            /* 0x03C */
    u8 unk60[0x3C];         /* 0x060 */
    Vec3 toCamera;          /* 0x09C */
    u8 unkA8[0x6C];         /* 0x0A8 */
    s16 heading;            /* 0x114 */
    u8 unk116[0xCA];        /* 0x116 */
    s16 unk1E0;             /* 0x1E0 */
    u8 unk1E2[0x1E];        /* 0x1E2 */
    s8 unk200;              /* 0x200 */
    u8 unk201[0xA];         /* 0x201 */
    s8 slot;                /* 0x20B */
    s8 cameraMode;          /* 0x20C */
    u8 unk20D[0x7];         /* 0x20D */
    s16 orbitAngle;         /* 0x214 */
    u8 unk216[0x13E];       /* 0x216 */
    void (*callback)(u8 *); /* 0x354 */
    u8 unk358[0x28];        /* 0x358 */
    s32 cameraAngle;        /* 0x380 */
    u8 unk384[0x4];         /* 0x384 */
    s16 unk388;             /* 0x388 */
    s16 unk38A;             /* 0x38A */
    u8 unk38C[0x14];        /* 0x38C */
    s32 unk3A0;             /* 0x3A0 */
} RaceObject;

extern u8 D_800A3680[];
extern void func_80025730(u8 *);
void func_8001FD44(RaceObject *car) {
    s32 count;

    if (car == NULL) {
        return;
    }
    car->cameraMode++;
    car->cameraAngle = car->heading;
    count = car->cameraMode;
    if ((D_800A397CSmall == 2 && count >= 7) ||
        (D_800A397CSmall != 2 && count >= 3)) {
        car->cameraMode = -2;
    }
    if (car->callback == func_80025730 && car->cameraMode == -1) {
        car->cameraMode = 0;
    }
    D_800A3680[0] = 1;
}

void func_8001FDD0(RaceObject *cam, RaceObject *car) {
    u32 dist3;
    u32 dist2;
    s32 cosPitch;
    s32 sinPitch;
    s32 cosYaw;

    func_8001EC38((s32 *)cam);
    car->toCamera.x = car->pos.x - cam->pos.x;
    car->toCamera.y = car->pos.y - cam->pos.y;
    car->toCamera.z = car->pos.z - cam->pos.z;
    func_8001ED84((s32 *)&car->toCamera);
    dist3 = MathSqrt(car->toCamera.x * car->toCamera.x +
                     car->toCamera.y * car->toCamera.y +
                     car->toCamera.z * car->toCamera.z);
    dist2 = MathSqrt(car->toCamera.x * car->toCamera.x +
                     car->toCamera.y * car->toCamera.y);
    cosPitch = MathFixedDivide(dist2, dist3);
    sinPitch = MathFixedDivide(car->toCamera.z, dist3);
    cosYaw = MathFixedDivide(car->toCamera.x, dist2);
    func_8001F684(cosYaw, MathFixedDivide(car->toCamera.y, dist2), cosPitch,
                  sinPitch);
    func_8001F728((s32)&cam->rot[0]);
    func_8001F728((s32)&cam->rot[1]);
    func_8001F728((s32)&cam->rot[2]);
}

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

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    u8 unkC[0x4C];
} TrackPoint;

/* One 0x90-byte entry of the array at D_800BE980. */
typedef struct {
    u8 unk0[0x10];
    u32 unk10 : 17;
    u32 point : 7;
    u32 unk10Top : 8;
    s32 unk14;
    s32 unk18;
    u8 unk1C[0x4];
    u8 *unk20;
    u8 unk24[0x6C];
} TrackRacer;

s32 MathFixedDivide(s32 numerator, s32 denominator);
s32 MathGetAngleDelta(s32 arg0, s32 arg1);
void func_8002DA30(s32 *arg0);
extern s32 D_800A2DCCSmall asm("D_800A2DCC.NON_MATCHING");
extern s32 D_800A2DD0Small asm("D_800A2DD0.NON_MATCHING");
extern s32 D_800A2DD4Small asm("D_800A2DD4.NON_MATCHING");
extern s32 D_800A2DD8Small asm("D_800A2DD8.NON_MATCHING");
extern s32 D_800A2DDCSmall asm("D_800A2DDC.NON_MATCHING");
extern u8 D_800A2DE0Small asm("D_800A2DE0.NON_MATCHING");
extern u8 D_800A2DE1Small asm("D_800A2DE1.NON_MATCHING");
extern s32 D_800A2DE8Small asm("D_800A2DE8.NON_MATCHING");
/* A global seen through a 16-byte type: gcc reads it as a plain scalar for
 * alias analysis, but its size keeps it out of $gp addressing. */
typedef struct {
    s32 unk[4];
} FarVar;
#define FAR_VAR(type, var) (*(type *)&(var))
extern FarVar gFarFlag2ED8 asm("D_800A2ED8.NON_MATCHING");
extern FarVar gFarFlag2EE8 asm("D_800A2EE8");
extern FarVar gFarFlag39D4 asm("D_800A39D4");
extern FarVar gFarFlag2EDA asm("D_800A2EDA.NON_MATCHING");
extern FarVar gFarPaused asm("D_800A2ED4");
extern FarVar gFarMode2EA4 asm("D_800A2EA4");
extern FarVar gFarMode2CE0 asm("D_800A2CE0.NON_MATCHING");
extern FarVar gFarBlend2EAC asm("D_800A2EAC.NON_MATCHING");
extern FarVar gFarTrack asm("D_800BE980");
extern FarVar gFarPlayer asm("D_800A38AC");
extern FarVar gFarOffsetX asm("D_800AE844");
extern FarVar gFarOffsetY asm("D_800AE848");
extern FarVar gFarOffsetZ asm("D_800AE84C");
extern FarVar gFarCosTable asm("D_800A3A2CAbsolute");
extern FarVar gFarSinTable asm("D_800A3A34Absolute");
extern s32 D_800A3584nm[] asm("D_800A3584.NON_MATCHING");
extern u8 D_800A363Cnm[] asm("D_800A363C.NON_MATCHING");
extern s16 D_800A383Cnm[] asm("D_800A383C.NON_MATCHING");
extern s16 D_800A3840nm[] asm("D_800A3840.NON_MATCHING");
extern s16 D_800A3844nm[] asm("D_800A3844.NON_MATCHING");
extern TrackPoint D_800B1348nm[] asm("D_800B1348.NON_MATCHING");
extern Vec3 D_800B9954nm[] asm("D_800B9954.NON_MATCHING");

#define COS_TABLE FAR_VAR(s32 *, gFarCosTable)
#define SIN_TABLE FAR_VAR(s32 *, gFarSinTable)

/* Aims the camera at the car: stores the car-to-camera vector and rebuilds
 * the camera's rotation rows from its yaw and pitch. */
#define CAMERA_LOOK_AT(cam, car, row0, row1, row2)                             \
    {                                                                          \
        u32 dist3;                                                             \
        u32 dist2;                                                             \
        s32 cosPitch;                                                          \
        s32 sinPitch;                                                          \
        s32 cosYaw;                                                            \
                                                                               \
        func_8001EC38((s32 *)(cam));                                           \
        (car)->toCamera.x = (car)->pos.x - (cam)->pos.x;                       \
        (car)->toCamera.y = (car)->pos.y - (cam)->pos.y;                       \
        (car)->toCamera.z = (car)->pos.z - (cam)->pos.z;                       \
        func_8001ED84((s32 *)&(car)->toCamera);                                \
        dist3 = MathSqrt((car)->toCamera.x * (car)->toCamera.x +               \
                         (car)->toCamera.y * (car)->toCamera.y +               \
                         (car)->toCamera.z * (car)->toCamera.z);               \
        dist2 = MathSqrt((car)->toCamera.x * (car)->toCamera.x +               \
                         (car)->toCamera.y * (car)->toCamera.y);               \
        cosPitch = MathFixedDivide(dist2, dist3);                              \
        sinPitch = MathFixedDivide((car)->toCamera.z, dist3);                  \
        cosYaw = MathFixedDivide((car)->toCamera.x, dist2);                    \
        func_8001F684(cosYaw, MathFixedDivide((car)->toCamera.y, dist2),       \
                      cosPitch, sinPitch);                                     \
        func_8001F728((s32)(row0));                                            \
        func_8001F728((s32)(row1));                                            \
        func_8001F728((s32)(row2));                                            \
    }

/* Update the camera for one car and camera mode. */
void CameraUpdateForCar(RaceObject *cam, RaceObject *car, s32 mode) {
    s32 pos[3];
    s32 unused[4];
    s8 slot;
    s32 speed;
    s32 delta;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 recip;
    s32 count;
    s32 index;
    s32 point;
    u32 dist;
    s16 *from;
    s16 *to;
    TrackRacer *track;
    s16 *rate;
    Vec3 *row0;
    Vec3 *row1;
    Vec3 *row2;
    Vec3 *aimRow0;
    Vec3 *aimRow1;
    Vec3 *aimRow2;

    slot = car->slot;
    D_800A2DE0Small = 0;
    if (FAR_VAR(u8, gFarFlag2ED8) == 0) {
        if (FAR_VAR(s32, gFarMode2EA4) == 2) {
            D_800A2DCCSmall = 0x320;
            D_800A2DD0Small = 0x4B0;
            D_800A2DD4Small = 0xF0;
            D_800A2DD8Small = 0x78;
            D_800A2DDCSmall = 0x82;
        } else {
            D_800A2DCCSmall = 0x2EE;
            D_800A2DD0Small = 0x3E8;
            D_800A2DD4Small = 0xFA;
            D_800A2DD8Small = 0x3C;
            D_800A2DDCSmall = 0x32;
        }
        speed = D_800A2DE8Small;
        car->unk3A0++;
        if (car->unk3A0 >= 2) {
            car->unk3A0 = 0;
        }
        if (mode == 5) {
            mode = 11;
        }
    } else {
        D_800A2DCCSmall = 0x4B0;
        D_800A2DD0Small = 0x708;
        D_800A2DD4Small = 0x1F4;
        D_800A2DD8Small = 0x96;
        speed = 0x5DC;
        if (mode == 7) {
            mode = cam->cameraMode;
        }
        if (mode == 5) {
            D_800A2DE0Small = 1;
        }
    }

    switch (mode) {
    case 0:
        car->orbitAngle = 0;
        cam->basis[0] = car->basis[0];
        cam->basis[1] = car->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[0] = car->rot[0];
        cam->rot[1] = car->rot[1];
        cam->rot[2] = car->rot[2];
        func_8001ED4C((s32 *)cam);
        delta = (car->unk38A + car->unk388) -
                (car->unk38A + car->unk388) / 1024 * 1024;
        recip =
            (0x96 - (delta - 0x200 >= 0 ? (0x400 - delta) >> 2 : delta >> 2))
            << 16;
        cam->pos.x =
            car->pos.x + ((MathMultiplyFixed16(cam->rot[0].y, 100 << 16) +
                           MathMultiplyFixed16(cam->rot[0].z, recip)) >>
                          16);
        cam->pos.y =
            car->pos.y + ((MathMultiplyFixed16(cam->rot[1].y, 100 << 16) +
                           MathMultiplyFixed16(cam->rot[1].z, recip)) >>
                          16);
        cam->pos.z =
            car->pos.z + ((MathMultiplyFixed16(cam->rot[2].y, 100 << 16) +
                           MathMultiplyFixed16(cam->rot[2].z, recip)) >>
                          16);
        break;
    case -1:
        cam->basis[0] = car->basis[0];
        cam->basis[1] = car->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[0] = car->rot[0];
        cam->rot[1] = car->rot[1];
        cam->rot[2] = car->rot[2];
        func_8001ED4C((s32 *)cam);
        if (car->unk200 == 4) {
            cam->pos.x =
                car->pos.x + ((MathMultiplyFixed16(cam->rot[0].x, -500 << 16) +
                               MathMultiplyFixed16(cam->rot[0].z, 400 << 16)) >>
                              16);
            cam->pos.y =
                car->pos.y + ((MathMultiplyFixed16(cam->rot[1].x, -500 << 16) +
                               MathMultiplyFixed16(cam->rot[1].z, 400 << 16)) >>
                              16);
            cam->pos.z =
                car->pos.z + ((MathMultiplyFixed16(cam->rot[2].x, -500 << 16) +
                               MathMultiplyFixed16(cam->rot[2].z, 400 << 16)) >>
                              16);
        } else if (FAR_VAR(s32, gFarMode2EA4) != 0) {
            cam->pos.x =
                car->pos.x + ((MathMultiplyFixed16(cam->rot[0].x, -100 << 16) +
                               MathMultiplyFixed16(cam->rot[0].z, 225 << 16)) >>
                              16);
            cam->pos.y =
                car->pos.y + ((MathMultiplyFixed16(cam->rot[1].x, -100 << 16) +
                               MathMultiplyFixed16(cam->rot[1].z, 225 << 16)) >>
                              16);
            cam->pos.z =
                car->pos.z + ((MathMultiplyFixed16(cam->rot[2].x, -100 << 16) +
                               MathMultiplyFixed16(cam->rot[2].z, 225 << 16)) >>
                              16);
        } else {
            cam->pos.x =
                car->pos.x + ((MathMultiplyFixed16(cam->rot[0].x, -250 << 16) +
                               MathMultiplyFixed16(cam->rot[0].z, 375 << 16)) >>
                              16);
            cam->pos.y =
                car->pos.y + ((MathMultiplyFixed16(cam->rot[1].x, -250 << 16) +
                               MathMultiplyFixed16(cam->rot[1].z, 375 << 16)) >>
                              16);
            cam->pos.z =
                car->pos.z + ((MathMultiplyFixed16(cam->rot[2].x, -250 << 16) +
                               MathMultiplyFixed16(cam->rot[2].z, 375 << 16)) >>
                              16);
        }
        dx = car->pos.x;
        dy = car->pos.y;
        dz = car->pos.z;
        car->pos.x += MathMultiplyFixed16(car->rot[0].x, 1500 << 16) >> 16;
        car->pos.y += MathMultiplyFixed16(car->rot[0].y, 1500 << 16) >> 16;
        car->pos.z += MathMultiplyFixed16(car->rot[0].z, 1500 << 16) >> 16;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        car->pos.x = dx;
        car->pos.y = dy;
        car->pos.z = dz;
        break;
    case -2:
        car->orbitAngle = 0;
        cam->basis[0] = car->basis[0];
        cam->basis[1] = car->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[0] = car->rot[0];
        cam->rot[1] = car->rot[1];
        cam->rot[2] = car->rot[2];
        func_8001ED4C((s32 *)cam);
        delta = (car->unk38A + car->unk388) -
                (car->unk38A + car->unk388) / 1024 * 1024;
        recip =
            (0x64 - (delta - 0x200 >= 0 ? (0x400 - delta) >> 2 : delta >> 2))
            << 16;
        cam->pos.x =
            car->pos.x + ((MathMultiplyFixed16(cam->rot[0].x, 250 << 16) +
                           MathMultiplyFixed16(cam->rot[0].z, recip)) >>
                          16);
        cam->pos.y =
            car->pos.y + ((MathMultiplyFixed16(cam->rot[1].x, 250 << 16) +
                           MathMultiplyFixed16(cam->rot[1].z, recip)) >>
                          16);
        cam->pos.z =
            car->pos.z + ((MathMultiplyFixed16(cam->rot[2].x, 250 << 16) +
                           MathMultiplyFixed16(cam->rot[2].z, recip)) >>
                          16);
        break;
    case 1:
        if (FAR_VAR(s32, gFarPaused) == 0 && D_800A2DE1Small == 0) {
            delta = MathGetAngleDelta(car->cameraAngle, car->heading);
            if (delta < 0) {
                delta = delta / 10 - 1;
            } else if (delta > 0) {
                delta = delta / 10 + 1;
            }
            car->cameraAngle = (car->cameraAngle - delta + 0x400) & 0x3FF;
        }
        cam->pos.x =
            car->pos.x - (MathMultiplyFixed16(COS_TABLE[car->cameraAngle],
                                              D_800A2DCCSmall << 16) >>
                          16);
        cam->pos.y =
            car->pos.y - (MathMultiplyFixed16(SIN_TABLE[car->cameraAngle],
                                              D_800A2DCCSmall << 16) >>
                          16);
        cam->pos.z = car->pos.z + D_800A2DD4Small;
        if (FAR_VAR(u8, gFarFlag2EE8) != 0) {
            cam->rot[0] = car->rot[0];
            cam->rot[1] = car->rot[1];
            cam->rot[2] = car->rot[2];
            func_8001ED4C((s32 *)cam);
            dz = car->pos.z -
                 (MathMultiplyFixed16(cam->rot[2].x, D_800A2DCCSmall << 16) >>
                  16) +
                 D_800A2DD4Small * 3 / 4;
            if (cam->pos.z < dz) {
                cam->pos.z = dz;
            }
            cam->rot[0] = cam->basis[0];
            cam->rot[1] = cam->basis[1];
            cam->rot[2] = cam->basis[2];
        }
        if (D_800A397CSmall == 2 && FAR_VAR(u8, gFarFlag39D4) != 0) {
            func_8001FF3C((u8 *)cam, (u8 *)car);
        }
        car->pos.z += D_800A2DD8Small;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        car->pos.z -= D_800A2DD8Small;
        break;
    case 2:
        if (FAR_VAR(s32, gFarPaused) == 0 && D_800A2DE1Small == 0) {
            delta = MathGetAngleDelta(car->cameraAngle, car->heading);
            if (delta < 0) {
                delta = delta / 8 - 1;
            } else if (delta > 0) {
                delta = delta / 8 + 1;
            }
            car->cameraAngle = (car->cameraAngle - delta + 0x400) & 0x3FF;
        }
        cam->pos.x =
            car->pos.x - (MathMultiplyFixed16(COS_TABLE[car->cameraAngle],
                                              D_800A2DD0Small << 16) >>
                          16);
        cam->pos.y =
            car->pos.y - (MathMultiplyFixed16(SIN_TABLE[car->cameraAngle],
                                              D_800A2DD0Small << 16) >>
                          16);
        cam->pos.z = car->pos.z + 0x1C2;
        if (FAR_VAR(u8, gFarFlag2EE8) != 0) {
            cam->rot[0] = car->rot[0];
            cam->rot[1] = car->rot[1];
            cam->rot[2] = car->rot[2];
            func_8001ED4C((s32 *)cam);
            dz = car->pos.z -
                 (MathMultiplyFixed16(cam->rot[2].x, D_800A2DD0Small << 16) >>
                  16) +
                 0x142;
            if (cam->pos.z < dz) {
                cam->pos.z = dz;
            }
            cam->rot[0] = cam->basis[0];
            cam->rot[1] = cam->basis[1];
            cam->rot[2] = cam->basis[2];
        }
        if (D_800A397CSmall == 2 && FAR_VAR(u8, gFarFlag39D4) != 0) {
            func_8001FF3C((u8 *)cam, (u8 *)car);
        }
        car->pos.z += D_800A2DDCSmall;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        car->pos.z -= D_800A2DDCSmall;
        break;
    case 11:
        cam->basis[0] = car->basis[0];
        cam->basis[1] = car->basis[1];
        cam->basis[2] = car->basis[2];
        if (FAR_VAR(u8, gFarFlag2EDA) != 0) {
            delta = MathGetAngleDelta(car->cameraAngle,
                                      (car->heading + 0x200) & 0x3FF);
            if (delta < 0) {
                delta = delta / 8 - 1;
            } else if (delta > 0) {
                delta = delta / 8 + 1;
            }
            car->cameraAngle = (car->cameraAngle - delta + 0x400) & 0x3FF;
            cam->pos.x =
                car->pos.x - (MathMultiplyFixed16(COS_TABLE[car->cameraAngle],
                                                  D_800A2DCCSmall << 16) >>
                              16);
            cam->pos.y =
                car->pos.y - (MathMultiplyFixed16(SIN_TABLE[car->cameraAngle],
                                                  D_800A2DCCSmall << 16) >>
                              16);
            cam->pos.z = car->pos.z + 0xFA;
        } else {
            cam->pos.x =
                car->pos.x +
                (MathMultiplyFixed16(cam->basis[0].x, D_800A2DCCSmall << 16) >>
                 16);
            cam->pos.y =
                car->pos.y +
                (MathMultiplyFixed16(cam->basis[1].x, D_800A2DCCSmall << 16) >>
                 16);
            cam->pos.z =
                car->pos.z +
                (MathMultiplyFixed16(cam->basis[2].x, D_800A2DCCSmall << 16) >>
                 16) +
                0xFA;
        }
        if (FAR_VAR(u8, gFarFlag39D4) != 0) {
            func_8001FF3C((u8 *)cam, (u8 *)car);
        }
        car->pos.z += D_800A2DD8Small;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        car->pos.z -= D_800A2DD8Small;
        break;
    case 3:
        cam->basis[0] = car->basis[0];
        cam->rot[0] = cam->basis[0];
        cam->basis[1] = car->basis[1];
        cam->rot[1] = cam->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[2] = cam->basis[2];
        if (FAR_VAR(s32, gFarPaused) == 0 && FAR_VAR(u8, gFarFlag2ED8) == 0) {
            car->orbitAngle = (car->orbitAngle + 6) & 0x3FF;
        }
        cam->pos.x =
            car->pos.x - (MathMultiplyFixed16(COS_TABLE[car->orbitAngle],
                                              D_800A2DCCSmall << 16) >>
                          16);
        cam->pos.y =
            car->pos.y - (MathMultiplyFixed16(SIN_TABLE[car->orbitAngle],
                                              D_800A2DCCSmall << 16) >>
                          16);
        cam->pos.z = car->pos.z + D_800A2DD4Small;
        if (FAR_VAR(u8, gFarFlag39D4) != 0) {
            func_8001FF3C((u8 *)cam, (u8 *)car);
        }
        car->pos.z += D_800A2DD8Small;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        car->pos.z -= D_800A2DD8Small;
        break;
    case 4:
    case 7:
    case 8:
    case 18:
        cam->basis[0] = car->basis[0];
        cam->rot[0] = cam->basis[0];
        cam->basis[1] = car->basis[1];
        cam->rot[1] = cam->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[2] = cam->basis[2];
        index = car->unk1E0;
        if (index >= 0) {
            point = FAR_VAR(TrackRacer *, gFarTrack)[index].point;
        } else {
            point = 0;
        }
        cam->pos.x = D_800B1348nm[point].x;
        cam->pos.y = D_800B1348nm[point].y;
        cam->pos.z = D_800B1348nm[point].z;
        dx = car->pos.x - cam->pos.x;
        dy = car->pos.y - cam->pos.y;
        dz = car->pos.z - cam->pos.z;
        dx = dx > 0x7FFF ? 0x7FFF : (dx < -0x7FFF ? -0x7FFF : dx);
        dy = dy > 0x7FFF ? 0x7FFF : (dy < -0x7FFF ? -0x7FFF : dy);
        recip = MathFixedDivide(speed, MathSqrt(dx * dx + dy * dy + dz * dz));
        cam->pos.x = car->pos.x - (MathMultiplyFixed16(dx << 16, recip) >> 16);
        cam->pos.y = car->pos.y - (MathMultiplyFixed16(dy << 16, recip) >> 16);
        cam->pos.z = car->pos.z - (MathMultiplyFixed16(dz << 16, recip) >> 16);
        func_8002DA30((s32 *)cam);
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        break;
    case 5:
        cam->basis[0] = car->basis[0];
        cam->basis[1] = car->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[0] = car->rot[0];
        cam->rot[1] = car->rot[1];
        cam->rot[2] = car->rot[2];
        func_8001ED4C((s32 *)cam);
        cam->pos.x =
            car->pos.x + ((MathMultiplyFixed16(cam->rot[0].y, 100 << 16) +
                           MathMultiplyFixed16(cam->rot[0].z, 150 << 16)) >>
                          16);
        cam->pos.y =
            car->pos.y + ((MathMultiplyFixed16(cam->rot[1].y, 100 << 16) +
                           MathMultiplyFixed16(cam->rot[1].z, 150 << 16)) >>
                          16);
        cam->pos.z =
            car->pos.z + ((MathMultiplyFixed16(cam->rot[2].y, 100 << 16) +
                           MathMultiplyFixed16(cam->rot[2].z, 150 << 16)) >>
                          16);
        func_8001F2C4(0x200, 0, 0);
        func_8001F728((s32)&cam->rot[0]);
        func_8001F728((s32)&cam->rot[1]);
        func_8001F728((s32)&cam->rot[2]);
        cam->rot[0].y = -cam->rot[0].y;
        cam->rot[1].y = -cam->rot[1].y;
        cam->rot[2].y = -cam->rot[2].y;
        break;
    case 6:
        cam->pos.x =
            car->pos.x -
            (MathMultiplyFixed16(cam->basis[0].x, D_800A2DCCSmall << 16) >> 16);
        cam->pos.y =
            car->pos.y -
            (MathMultiplyFixed16(cam->basis[1].x, D_800A2DCCSmall << 16) >> 16);
        cam->pos.z =
            car->pos.z -
            (MathMultiplyFixed16(cam->basis[2].x, D_800A2DCCSmall << 16) >>
             16) +
            0x9C4;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        break;
    case 12:
        cam->basis[0] = car->basis[0];
        cam->rot[0] = cam->basis[0];
        cam->basis[1] = car->basis[1];
        cam->rot[1] = cam->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[2] = cam->basis[2];
        index = car->slot;
        if ((car->unk1E0 >= D_800A3584nm[index] + 1 ||
             D_800A363Cnm[index] != 0) &&
            FAR_VAR(s32, gFarPaused) == 0) {
            count = D_800A363Cnm[index]++;
            dx = car->pos.x - (MathMultiplyFixed16(COS_TABLE[car->heading],
                                                   D_800A2DCCSmall << 16) >>
                               16);
            dy = car->pos.y - (MathMultiplyFixed16(SIN_TABLE[car->heading],
                                                   D_800A2DCCSmall << 16) >>
                               16);
            dz = car->pos.z + D_800A2DD4Small;
            dx = D_800B9954nm[car->slot].x - dx;
            dy = D_800B9954nm[car->slot].y - dy;
            dz = D_800B9954nm[car->slot].z - dz;
            if (count >= 0x1F) {
                count = 0x1E;
                car->cameraMode = 1;
            }
            D_800B9954nm[car->slot].x -= dx * count / 30;
            D_800B9954nm[car->slot].y -= dy * count / 30;
            D_800B9954nm[car->slot].z -= dz * count / 30;
            car->cameraAngle = car->heading;
        }
        cam->pos.x = D_800B9954nm[car->slot].x;
        cam->pos.y = D_800B9954nm[car->slot].y;
        cam->pos.z = D_800B9954nm[car->slot].z;
        func_8002DA30((s32 *)cam);
        car->pos.z += D_800A2DD8Small;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        car->pos.z -= D_800A2DD8Small;
        break;
    case 13:
        cam->basis[0] = car->basis[0];
        cam->basis[1] = car->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[0] = car->rot[0];
        cam->rot[1] = car->rot[1];
        cam->rot[2] = car->rot[2];
        func_8001ED4C((s32 *)cam);
        cam->pos.x =
            car->pos.x +
            ((MathMultiplyFixed16(cam->rot[0].x, D_800A383Cnm[slot] << 16) -
              MathMultiplyFixed16(cam->rot[0].y, D_800A3840nm[slot] << 16) +
              MathMultiplyFixed16(cam->rot[0].z, D_800A3844nm[slot] << 16)) >>
             16);
        cam->pos.y =
            car->pos.y +
            ((MathMultiplyFixed16(cam->rot[1].x, D_800A383Cnm[slot] << 16) -
              MathMultiplyFixed16(cam->rot[1].y, D_800A3840nm[slot] << 16) +
              MathMultiplyFixed16(cam->rot[1].z, D_800A3844nm[slot] << 16)) >>
             16);
        cam->pos.z =
            car->pos.z +
            ((MathMultiplyFixed16(cam->rot[2].x, D_800A383Cnm[slot] << 16) -
              MathMultiplyFixed16(cam->rot[2].y, D_800A3840nm[slot] << 16) +
              MathMultiplyFixed16(cam->rot[2].z, D_800A3844nm[slot] << 16)) >>
             16);
        row0 = &cam->rot[0];
        row1 = &cam->rot[1];
        row2 = &cam->rot[2];
        if (D_800A383Cnm[slot] >= -0x15D) {
            cam->rot[0] = car->rot[1];
            cam->rot[1].x = -car->rot[0].x;
            cam->rot[1].y = -car->rot[0].y;
            cam->rot[1].z = -car->rot[0].z;
            cam->rot[2] = car->rot[2];
            func_8001ED4C((s32 *)cam);
        } else {
            dx = MathMultiplyFixed16(cam->rot[0].x, 350 << 16) >> 16;
            dy = MathMultiplyFixed16(cam->rot[1].x, 350 << 16) >> 16;
            car->pos.x -= dx;
            car->pos.y -= dy;
            car->pos.z += 0x4B;
            CAMERA_LOOK_AT(cam, car, row0, row1, row2);
            car->pos.x += dx;
            car->pos.y += dy;
            car->pos.z -= 0x4B;
            if (FAR_VAR(s32, gFarPaused) == 0) {
                rate = &D_800A3840nm[slot];
                *rate = *rate > 0 ? *rate - 10 : 0;
                D_800A3844nm[slot] =
                    D_800A3844nm[slot] >= 0xFA ? 0xFA : D_800A3844nm[slot] + 5;
            }
        }
        if (FAR_VAR(s32, gFarPaused) == 0) {
            D_800A383Cnm[slot] -= 20;
        }
        break;
    case 16:
        cam->basis[0] = car->basis[0];
        cam->rot[0] = cam->basis[0];
        cam->basis[1] = car->basis[1];
        cam->rot[1] = cam->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[2] = cam->basis[2];
        if (FAR_VAR(s32, gFarMode2CE0) == 10) {
            to = *(s16 **)(FAR_VAR(u8 *, gFarTrack) + 0xB28);
            from = *(s16 **)(FAR_VAR(u8 *, gFarTrack) + 0xB3C);
        } else {
            to = *(s16 **)(FAR_VAR(u8 *, gFarTrack) + 0xFA8);
            from = *(s16 **)(FAR_VAR(u8 *, gFarTrack) + 0xFBC);
        }
        dx = from[0] + (to[0] - from[0]) * FAR_VAR(s32, gFarBlend2EAC) / 120;
        dy = from[1] + (to[1] - from[1]) * FAR_VAR(s32, gFarBlend2EAC) / 120;
        dz = from[2] + (to[2] - from[2]) * FAR_VAR(s32, gFarBlend2EAC) / 120;
        /* Array-member reads retain dependencies on the camera stores. */
        cam->pos.x = (dx + gFarOffsetX.unk[0]) * 4;
        cam->pos.y = (dy + gFarOffsetY.unk[0]) * 4;
        cam->pos.z = (dz + gFarOffsetZ.unk[0]) * 4 + 0x640;
        dx = (car->pos.x - cam->pos.x) / 4;
        dy = (car->pos.y - cam->pos.y) / 4;
        dz = (car->pos.z - cam->pos.z) / 4;
        dist = MathSqrt(dx * dx + dy * dy + dz * dz);
        if (dist > 0x4E20) {
            if (dist > 0x7F58) {
                dist = 0x7F58;
            }
            recip = MathFixedDivide(0x4E20, dist);
            cam->pos.x =
                (car->pos.x - MathMultiplyFixed16(dx << 16, recip)) >> 14;
            cam->pos.y =
                (car->pos.y - MathMultiplyFixed16(dy << 16, recip)) >> 14;
            cam->pos.z =
                (car->pos.z - MathMultiplyFixed16(dz << 16, recip)) >> 14;
        }
        cam->pos.x = car->pos.x - dx;
        cam->pos.y = car->pos.y - dy;
        cam->pos.z = car->pos.z - dz;
        func_8002DA30((s32 *)cam);
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        break;
    case 17:
        cam->basis[0] = car->basis[0];
        cam->rot[0] = cam->basis[0];
        cam->basis[1] = car->basis[1];
        cam->rot[1] = cam->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[2] = cam->basis[2];
        track = FAR_VAR(TrackRacer *, gFarTrack);
        point = track->point;
        pos[0] = track->unk14;
        pos[1] = track->unk18;
        pos[2] = *(s16 *)(*(u8 **)(track->unk20 + 0x18) + 4);
        pos[2] = (pos[2] + FAR_VAR(s32, gFarOffsetZ)) * 4;
        dx = pos[0] - D_800B1348nm[point].x;
        dy = pos[1] - D_800B1348nm[point].y;
        delta = pos[2] - 1000;
        dz = delta - D_800B1348nm[point].z;
        dist = MathSqrt(dx * dx + dy * dy + dz * dz);
        aimRow0 = &cam->rot[0];
        aimRow1 = &cam->rot[1];
        aimRow2 = &cam->rot[2];
        if (dist > 0x32C8) {
            dist = 0x32C8;
        }
        recip = MathFixedDivide(speed, dist);
        D_800A2DE8Small += 20;
        cam->pos.x = pos[0] - (MathMultiplyFixed16(dx << 16, recip) >> 16);
        cam->pos.y = pos[1] - (MathMultiplyFixed16(dy << 16, recip) >> 16);
        cam->pos.z = pos[2] - (MathMultiplyFixed16(dz << 16, recip) >> 16);
        {
            s32 stepX;
            s32 stepY;
            s32 stepZ;

            stepX = MathMultiplyFixed16(dx << 16, recip) >> 16;
            stepY = MathMultiplyFixed16(dy << 16, recip) >> 16;
            stepZ = MathMultiplyFixed16(dz << 16, recip) >> 16;
            MathSqrt(stepX * stepX + stepY * stepY + stepZ * stepZ);
        }
        func_8002DA30((s32 *)cam);
        dx = car->pos.x;
        dy = car->pos.y;
        dz = car->pos.z;
        car->pos.x = pos[0];
        car->pos.y = pos[1];
        car->pos.z = pos[2];
        CAMERA_LOOK_AT(cam, car, aimRow0, aimRow1, aimRow2);
        car->pos.x = dx;
        car->pos.y = dy;
        car->pos.z = dz;
        *(s16 *)(FAR_VAR(u8 *, gFarPlayer) + 0x1E0) = 0;
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002267C);

INCLUDE_ASM("asm/nonmatchings/objects", func_800229B8);

extern u8 *D_800A3554[];
extern u8 *D_800A3878w15[] asm("D_800A3878.NON_MATCHING");
extern u8 *D_800A3960w15[] asm("D_800A3960.NON_MATCHING");

void func_80022CA4(void) {
    u8 *node;
    register u8 *rec asm("a1");
    u8 *p;
    s32 current;
    s32 count;
    u8 *baseAddr;
    s32 offset;
    u32 bits;
    u32 w2;
    s32 d;
    s32 dm1;
    register u16 val asm("v1");
    s32 v90;
    s32 t114;
    s32 i;

    current = D_800A3A3CSmall;
    if (current != D_800A3804Small) {
        d = D_800A3A90Small;
        dm1 = d - 1;
        D_800A3A3CSmall = (current + dm1) % d;
    } else {
        D_800A2ED4[0] = 1;
        func_80052FC4(0);
    }
    count = D_800A3A3CSmall * (D_800A2E94[0] + 6);
    node = D_800A3878w15[0];
    if (node != 0) {
        offset = count * 20;
        do {
            if (*(s16 *)(node + 0x1EC) >= 0) {
                rec = (u8 *)D_800A3A38Small;
                rec = (u8 *)(offset + (s32)rec);
                *(s32 *)(node + 0) = *(s32 *)rec;
                *(s32 *)(node + 4) = *(s32 *)(rec + 4);
                func_800442C8(node);
                val = *(u16 *)(u8 *)(offset + D_800A3A38Small + 0xE);
                *(u8 *)(node + 0x410) = val & 0x7F;
                baseAddr = (u8 *)D_800A3A38Small;
                v90 = (val >> 7) << 17;
                *(s32 *)(node + 0x90) = v90;
                bits = *(s32 *)(u8 *)(offset + (s32)baseAddr + 8);
                *(s16 *)(node + 0x116) = (bits >> 22) * 4;
                val = bits >> 22;
                *(s16 *)(node + 0x20E) = ((bits >> 14) & 0xFF) - 0x80;
                *(s16 *)(node + 0x10C) = (bits & 0x3F) >> 4;
                *(u8 *)(node + 0x3B9) = (bits & 0xF) >> 3;
                *(u8 *)(node + 0xF9) = (bits & 7) >> 2;
                *(s16 *)(node + 0x102) = val;
                *(s16 *)(node + 0x114) = val;
                if ((bits & 3) == 1) {
                    D_800A3960w15[0] = D_800A3554[0];
                } else if ((bits & 3) == 2) {
                    D_800A3960w15[0] = *(u8 **)(D_800A3554[0] + 0x3E0);
                } else {
                    D_800A3960w15[0] = 0;
                }
                w2 = *(s32 *)(u8 *)(offset + D_800A3A38Small + 0x10);
                *(s16 *)(node + 0xFE) = ((w2 >> 20) - 0x800) * 2;
                for (i = 0; i < 4; i++) {
                    *(s16 *)(node + 0x2AC + i * 0x28) = *(u16 *)(node + 0xFE);
                }
                t114 = *(s16 *)(node + 0x114);
                *(s16 *)(node + 0x388) = (w2 << 12) >> 22;
                *(s16 *)(node + 0x38A) = w2 & 0x3FF;
                func_8001F2C4(t114, 0, 0);
                func_8001F828((s32 *)node);
                func_8001F874((s32 *)node);
                *(s32 *)(node + 0x228) = 0;
                *(s16 *)(node + 0x104) = *(u16 *)(node + 0x114);
                func_80028980(node);
                offset += 0x14;
                count += 1;
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != 0);
    }
    func_8003667C((u8 *)D_800A3A38Small + count * 20);
    func_80044594((u8 *)D_800A3A38Small + (count * 20 + 0x50));
}

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

void func_80022FB8(u8 *arg0, s32 arg1) {
    s32 value;
    s16 shortValue;
    s32 value0;
    s32 value1;
    s32 value2;

    value = 0x400 - arg1;
    if (value == 0x400) {
        value = 0;
    }
    func_8001F2C4(value, 0, 0);
    func_8001F874((s32 *)arg0);
    func_8001F828((s32 *)arg0);
    shortValue = value;
    *(s16 *)(arg0 + 0x102) = shortValue;
    *(s16 *)(arg0 + 0x104) = shortValue;
    *(s16 *)(arg0 + 0x114) = shortValue;
    *(s16 *)(arg0 + 0x116) = value * 4;
    do {
    } while (0);
    value0 = *(s32 *)(arg0 + 0x18);
    value1 = *(s32 *)(arg0 + 0x1C);
    value2 = *(s32 *)(arg0 + 0x20);
    *(s32 *)(arg0 + 0x3C) = value0;
    *(s32 *)(arg0 + 0x40) = value1;
    *(s32 *)(arg0 + 0x44) = value2;
    do {
    } while (0);
    value0 = *(s32 *)(arg0 + 0x24);
    value1 = *(s32 *)(arg0 + 0x28);
    value2 = *(s32 *)(arg0 + 0x2C);
    *(s32 *)(arg0 + 0x48) = value0;
    *(s32 *)(arg0 + 0x4C) = value1;
    *(s32 *)(arg0 + 0x50) = value2;
    do {
    } while (0);
    value0 = *(s32 *)(arg0 + 0x30);
    value1 = *(s32 *)(arg0 + 0x34);
    value2 = *(s32 *)(arg0 + 0x38);
    *(s32 *)(arg0 + 0x54) = value0;
    *(s32 *)(arg0 + 0x58) = value1;
    *(s32 *)(arg0 + 0x5C) = value2;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80023074);

INCLUDE_ASM("asm/nonmatchings/objects", func_80023454);

extern char D_800A3038[];
extern s32 D_800A3668Absolute[];

void func_80024210(void) {
    CdlATV vol;

    if (D_800A3038[0x35] == 0) {
        vol.val0 = vol.val1 = vol.val2 = vol.val3 =
            ((s16 *)D_800A3668Absolute)[22] * 125 / 100;
        CdMix(&vol);
    }
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80024280);

INCLUDE_ASM("asm/nonmatchings/objects", func_800246C0);

extern s32 D_800A2E08;
extern s32 D_800A3838;
s32 func_800246C0(s32, s32, u8 *);

s32 func_8002482C(s32 arg0, s32 arg1, s32 *arg2) {
    s32 index;
    s32 remaining;
    u8 *entry;
    s32 count;

    count = D_800A2E08;
    arg0 = arg0 / 4;
    arg1 = arg1 / 4;
    index = *arg2;
    if (index == -1) {
        index = 0;
    }
    remaining = count;
    entry = (u8 *)D_800A3838 + (index * 0x10);
    if (remaining > 0) {
        do {
            if (index >= count) {
                index = 0;
                entry = (u8 *)D_800A3838;
            }
            if (arg0 >= *(u16 *)(entry + 0) && *(u16 *)(entry + 4) >= arg0 &&
                arg1 >= *(u16 *)(entry + 2) && *(u16 *)(entry + 6) >= arg1 &&
                (func_800246C0(arg0, arg1, entry) & 0xFF) != 0) {
                *arg2 = index;
                if (index == count) {
                    index = 0;
                }
                return index;
            }
            remaining -= 1;
            index += 1;
            entry += 0x10;
        } while (remaining > 0);
    }
    *arg2 = -1;
    return -1;
}

extern s32 D_800A2E08;
extern s32 D_800A3838;
s32 func_800246C0(s32, s32, u8 *);

s32 func_80024980(s32 arg0, s32 arg1, s32 *arg2) {
    s32 index;
    s32 remaining;
    u8 *entry;
    s32 count;
    s32 countLessOne;

    count = D_800A2E08;
    arg0 = arg0 / 4;
    arg1 = arg1 / 4;
    index = *arg2;
    if (index == -1) {
        index = 0;
    } else {
        countLessOne = count - 1;
        index = (index + countLessOne) % count;
    }
    remaining = count;
    entry = (u8 *)D_800A3838 + (index * 0x10);
    if (remaining > 0) {
        do {
            if (index >= count) {
                index = 0;
                entry = (u8 *)D_800A3838;
            }
            if (arg0 >= *(u16 *)(entry + 0) && *(u16 *)(entry + 4) >= arg0 &&
                arg1 >= *(u16 *)(entry + 2) && *(u16 *)(entry + 6) >= arg1 &&
                (func_800246C0(arg0, arg1, entry) & 0xFF) != 0) {
                *arg2 = index;
                if (index == count) {
                    index = 0;
                }
                return index;
            }
            remaining -= 1;
            index += 1;
            entry += 0x10;
        } while (remaining > 0);
    }
    *arg2 = -1;
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80024B08);

INCLUDE_ASM("asm/nonmatchings/objects", func_80024E90);

extern s32 D_800A3A54Small;
extern s32 D_800A2E14[];
extern s32 D_800A3810;
extern s32 D_800A356C;
extern char D_8008CFC0[];
extern s32 FileOpenCall(s32, void *) asm("FileOpen");
extern s32 FileSeekCall(void *, s32, s32) asm("FileSeek");
extern void FileRead(s32, s32, s32, s32);
extern void FileCloseCall(s32) asm("FileClose");

/* Loads a track resource: resolves a handle, maps its memory, then records
   the loaded row bounds into the small-data cursors. */
void func_80025370(s32 arg0) {
    s32 handle;
    s32 total;
    int headerSize;
    s32 cursor;
    s32 row0;
    register s32 row1 asm("$16");
    register s32 row1Shift asm("$3");
    handle = FileOpenCall(arg0, D_800A2E14);
    if (handle == 0) {
        SystemShowFatalError(D_8008CFC0);
    }
    total = FileSeekCall(handle, 0, 2);
    asm volatile("" : : "r"(total));
    FileSeekCall(handle, 0, 0);
    D_800A3A54Small = (RAM_RESOURCE_BOUNDARY - total) | RAM_CACHED_BASE;
    FileRead(D_800A3A54Small, 1, total, handle);
    cursor = *((volatile s32 *)(&D_800A3A54Small));
    D_800A3A54Small = cursor + 4;
    row0 = *((s32 *)cursor);
    D_800A3A54Small = cursor + 8;
    D_800A2E08 = row0;
    headerSize = 8;
    row1 = *((s32 *)(cursor + 4));
    D_800A3838 = cursor + headerSize;
    D_800A3810 = (cursor + headerSize) + (row0 << 4);
    row1Shift = row1 << 3;
    D_800A356C = D_800A3810 + row1Shift;
    FileCloseCall(handle);
}
INCLUDE_RODATA("asm/nonmatchings/objects", D_8008CFC0);
INCLUDE_RODATA("asm/nonmatchings/objects", D_8008CFE0);

void func_80025454(s32 track) {
    s32 count;
    s32 minX;
    s32 minY;
    s32 minZ;
    s32 maxX;
    s32 maxY;
    s32 maxZ;
    s32 x;
    s32 y;
    s32 z;
    s32 i;
    s32 limit;
    s32 *cursor;

    limit = 0;
    minZ = 0;
    maxY = 0;
    minY = 0;
    maxX = 0;
    minX = 0;
    i = 0;
    maxZ = 0;
    count = *(s16 *)((u8 *)track + 0x28);
    cursor = *(s32 **)((u8 *)track + 0x14);
    for (; i < count; i++) {
        x = cursor[2];
        if (x < minX) {
            minX = x;
        }
        y = cursor[3];
        if (y < minY) {
            minY = y;
        }
        z = cursor[4];
        if (z < minZ) {
            minZ = z;
        }
        if (maxX < x) {
            maxX = x;
        }
        if (maxY < y) {
            maxY = y;
        }
        if (maxZ < z) {
            maxZ = z;
        }
        cursor += 5;
    }
    if (limit < -minX) {
        limit = -minX;
    }
    if (limit < maxX) {
        limit = maxX;
    }
    if (limit < -minY) {
        limit = -minY;
    }
    if (limit < maxY) {
        limit = maxY;
    }
    if (limit < -minZ) {
        limit = -minZ;
    }
    if (limit < maxZ) {
        limit = maxZ;
    }
    *(s32 *)((u8 *)track + 0x18) = limit - 5;
    *(s16 *)((u8 *)track + 0x1C) = minX;
    *(s16 *)((u8 *)track + 0x20) = minY;
    *(s16 *)((u8 *)track + 0x24) = minZ;
    *(s16 *)((u8 *)track + 0x1E) = maxX;
    *(s16 *)((u8 *)track + 0x22) = maxY;
    *(s16 *)((u8 *)track + 0x26) = maxZ;
}

void func_80025594(u8 *object) {
    *(s16 *)(object + 0x1BC) = 0;
    *(s16 *)(object + 0x388) = 0;
}

void func_800255A0(u8 *arg0) {
    u16 temp;

    temp = *(u16 *)(arg0 + 0x1BC);
    *(s32 *)(arg0 + 0x238) = *(s32 *)(arg0 + 0x238) & 0xFFFF7DBF;
    *(u16 *)(arg0 + 0x1BC) = temp + 1;
    switch ((s16)temp) {
    case 0:
        *(s16 *)(arg0 + 0x1C0) = 0;
        *(s16 *)(arg0 + 0x1BE) = 0;
        return;
    case 32:
        *(u16 *)(arg0 + 0x1BC) = 0;
        break;
    default:
        *(s16 *)(arg0 + 0x1D0) = 32;
        return;
    }
    *(s32 *)(arg0 + 0x354) = (s32)func_80025594;
}

void func_80025614(u8 *arg0) {
    s32 heading;
    s32 *table1;
    s32 *table2;
    s32 index;

    *(s32 *)(arg0 + 0x238) = *(s32 *)(arg0 + 0x238) & 0xFFFF7DBF;
    *(s16 *)(arg0 + 0x2B0) = ABS(RandomScaledGet(10)) + 20;
    *(s16 *)(arg0 + 0x2D8) = ABS(RandomScaledGet(10)) + 20;
    heading = *(s16 *)(arg0 + 0x114);
    table1 = *(s32 **)D_800A3A2CAbsolute;
    table2 = *(s32 **)D_800A3A34Absolute;
    *(s16 *)(arg0 + 0x1BC) = 0;
    index = (0x480 - heading) & 0x3FF;
    *(s32 *)(arg0 + 0xC4) += table1[index] * 20;
    *(s32 *)(arg0 + 0xC8) += table2[index] * 20;
    *(s32 *)(arg0 + 0x354) = (s32)func_80025594;
}

void func_80025594();

void func_80025720(u8 *obj) {
    *(void (**)())(obj + 0x354) = func_80025594;
}

void func_80025730(u8 *obj) {
    extern u8 D_800A35F8[];
    extern u8 *D_800A3960[];
    extern s16 D_800A3910[];
    extern u8 D_800A2EDC[];
    extern void func_80042920();
    extern void func_8004419C(u8 *);
    s32 y;
    s32 value;
    s32 dist;
    s32 i;
    u8 *current;
    u8 *p;

    *(u32 *)(obj + 0x238) &= 0xFFFF7D3F;
    *(u8 *)(obj + 0x410) = 0;
    switch (*(s16 *)(obj + 0x1BC)) {
    case 0:
        value = 0x96;
        *(s16 *)(obj + 0x1BC) = 2;
        *(s16 *)(obj + 0x1BE) = 0;
        *(s16 *)(obj + 0x388) = 0;
        *(s16 *)(obj + 0x38A) = 0;
        i = 3;
        p = obj + 0x78;
        do {
            *(s16 *)(p + 0x2B0) = value;
            i--;
            p -= 0x28;
        } while (i >= 0);
        func_800422C0(obj);
        D_800A35F8[0] = 2;
        D_800A3960[0] = obj;
        D_800A3910[0] = 0x7FFF;
        if (*(s8 *)(obj + 0x20C) == -1) {
            y = *(s16 *)(obj + 0x114);
            if (RandomScaledGet(2) == 0) {
                dist = y + 0x300;
            } else {
                dist = y + 0x500;
            }
            *(s32 *)(obj + 0x380) = dist & 0x3FF;
            *(s8 *)(obj + 0x20C) = 1;
        }
        return;
    case 1:
    case 2:
        func_80042920(obj);
        return;
    case 4:
        func_80042920(obj);
        if (*(u8 *)(obj + 0x268) != 0 && D_800A2EDC[0] != 0) {
            func_8004419C(obj);
            return;
        }
        if (*(s16 *)(obj + 0x38A) == 0x200) {
            D_800A35F8[0] = 1;
        }
        return;
    case 3:
        current = D_800A3960[0];
        *(s16 *)(obj + 0x1BC) = 0;
        *(s16 *)(obj + 0x1BE) = 0;
        *(s16 *)(obj + 0x388) = 0;
        *(s16 *)(obj + 0x38A) = 0;
        if (current == obj) {
            extern s32 D_800A3914[];
            D_800A3914[19] = 0;
        }
        if (D_800A3910[0] > 0) {
            extern s16 D_800A3914[];
            D_800A3914[-2] = 0;
        }
        break;
    default:
        break;
    }
    *(s32 *)(obj + 0x354) = (s32)func_80025594;
}

typedef struct {
    u8 unk0[0x1EC];
    s16 unk1EC;
    u8 unk1EE[0x12];
    s8 unk200;
    u8 unk201[0x153];
    void (*callback)(void);
} Batch0CallbackObject;
void ObjectSetCallbackIfAllowed(Batch0CallbackObject *object,
                                void (*callback)(void)) {
    if (((object->unk1EC != 1) || (callback != func_80025730)) &&
        (object->callback != func_80025730) && (object->unk200 != 4)) {
        object->callback = callback;
    }
}

s32 func_80025938(u8 *arg0, u8 *arg1) {
    s32 dist[3];
    s32 radius;

    radius = *(s32 *)(*(s32 *)(arg0 + 0x370) + 0x18) +
             *(s32 *)(*(s32 *)(arg1 + 0x370) + 0x18);
    dist[0] = (*(s32 *)(arg0 + 0) - *(s32 *)(arg1 + 0) < 0
                   ? *(s32 *)(arg1 + 0) - *(s32 *)(arg0 + 0)
                   : *(s32 *)(arg0 + 0) - *(s32 *)(arg1 + 0));
    dist[1] = (*(s32 *)(arg0 + 4) - *(s32 *)(arg1 + 4) < 0
                   ? *(s32 *)(arg1 + 4) - *(s32 *)(arg0 + 4)
                   : *(s32 *)(arg0 + 4) - *(s32 *)(arg1 + 4));
    dist[2] = (*(s32 *)(arg0 + 8) - *(s32 *)(arg1 + 8) < 0
                   ? *(s32 *)(arg1 + 8) - *(s32 *)(arg0 + 8)
                   : *(s32 *)(arg0 + 8) - *(s32 *)(arg1 + 8));
    if (radius >= dist[0] && radius >= dist[1] && radius >= dist[2]) {
        if (*(s32 *)(arg0 + 0x354) != (s32)func_80025730 &&
            *(s32 *)(arg1 + 0x354) != (s32)func_80025730) {
            return 1;
        }
        if ((*(s32 *)(arg0 + 8) - *(s32 *)(arg1 + 8) < 0
                 ? *(s32 *)(arg1 + 8) - *(s32 *)(arg0 + 8)
                 : *(s32 *)(arg0 + 8) - *(s32 *)(arg1 + 8)) >= 501) {
            return 0;
        }
        return 1;
    }
    return 0;
}

extern u8 *D_800A3554[];
extern s32 D_800A2E94[];
s32 func_8003702C(u8 *, u8 *);
void func_800406D0(u8 *, u8 *, s32, s32);
void func_80041848(u8 *, s32);

s32 func_80025A38(u8 *arg0) {
    u8 *other;
    s32 dist;

    *(s16 *)(arg0 + 0x1CE) = 0;
    if (*(s32 *)(arg0 + 0x3F0) == 0) {
        goto part2;
    }
    other = *(u8 **)(*(s32 *)(arg0 + 0x3F0) + 8);
    if (arg0 == other) {
        return 0;
    }
    if (func_80025938(arg0, other) == 0) {
        goto part2;
    }
    if (func_800261F8(arg0, other) != 0) {
        goto collide;
    }
part2:
    if (*(s32 *)(arg0 + 0x3F4) == 0) {
        goto scan;
    }
    other = *(u8 **)(*(s32 *)(arg0 + 0x3F4) + 8);
    if (arg0 == other) {
        return 0;
    }
    if (func_80025938(arg0, other) == 0) {
        goto scan;
    }
    if (func_800261F8(arg0, other) == 0) {
        goto scan;
    }
collide:
    if (*(s16 *)(arg0 + 0x1EC) == 0) {
        func_800406D0(arg0, other, 6, 1);
        func_80041848(arg0, 0x4E);
    }
    if (*(s16 *)(other + 0x1EC) == 0) {
        func_800406D0(other, arg0, 6, 1);
    }
    if (*(s16 *)(arg0 + 0x1EC) != 0 && *(s16 *)(other + 0x1EC) != 0) {
        func_800406D0(D_800A3554[0], arg0, 6, 1);
    }
    *(s32 *)(arg0 + 0x3D8) = other;
    return 1;
scan:
    if (*(s16 *)(arg0 + 0x1EC) != 0) {
        return 0;
    }
    if (D_800A2E94[0] < 4) {
        return 0;
    }
    other = *(u8 **)(*(s32 *)(*(s32 *)(arg0 + 0x3F0) + 0) + 8);
    if (other != 0) {
        do {
            if (arg0 == other) {
                return 0;
            }
            dist = func_8003702C(arg0, other);
            if (dist < 0) {
                dist = -func_8003702C(arg0, other);
                asm("");
            } else {
                dist = func_8003702C(arg0, other);
            }
            if (dist >= 2) {
                break;
            }
            if (func_80025938(arg0, other) != 0 &&
                func_800261F8(arg0, other) != 0) {
                if (*(s16 *)(arg0 + 0x1EC) == 0) {
                    func_800406D0(arg0, other, 6, 1);
                }
                if (*(s16 *)(other + 0x1EC) == 0) {
                    func_800406D0(other, arg0, 6, 1);
                }
                if (*(s16 *)(arg0 + 0x1EC) != 0 &&
                    *(s16 *)(other + 0x1EC) != 0) {
                    func_800406D0(D_800A3554[0], arg0, 6, 1);
                }
                *(s32 *)(arg0 + 0x3D8) = other;
                func_80041848(arg0, 0x4E);
            }
            other = *(u8 **)(*(s32 *)(other + 0x3F0) + 8);
        } while (other != 0);
    }
    other = *(u8 **)(*(s32 *)(*(s32 *)(arg0 + 0x3F4) + 4) + 8);
    if (other != 0) {
        do {
            if (arg0 == other) {
                return 0;
            }
            dist = func_8003702C(arg0, other);
            if (dist < 0) {
                dist = -func_8003702C(arg0, other);
                asm("");
            } else {
                dist = func_8003702C(arg0, other);
            }
            if (dist >= 2) {
                return 0;
            }
            if (func_80025938(arg0, other) != 0 &&
                func_800261F8(arg0, other) != 0) {
                if (*(s16 *)(arg0 + 0x1EC) == 0) {
                    func_800406D0(arg0, other, 6, 1);
                }
                if (*(s16 *)(other + 0x1EC) == 0) {
                    func_800406D0(other, arg0, 6, 1);
                }
                if (*(s16 *)(arg0 + 0x1EC) != 0 &&
                    *(s16 *)(other + 0x1EC) != 0) {
                    func_800406D0(D_800A3554[0], arg0, 6, 1);
                }
                *(s32 *)(arg0 + 0x3D8) = other;
                func_80041848(arg0, 0x4E);
            }
            other = *(u8 **)(*(s32 *)(other + 0x3F4) + 8);
        } while (other != 0);
    }
    return 0;
}

extern void func_8003644C(s32, s32, s32, s32);

void func_80025DD4(u8 *arg0, u8 *arg1) {
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;

    if (*(s16 *)(arg0 + 0x1EC) == 1 &&
        *(s16 *)(arg1 + 0x1EC) == *(s16 *)(arg0 + 0x1EC)) {
        return;
    }
    x = (*(s32 *)(arg0 + 0) + *(s32 *)(arg1 + 0)) / 2 + RandomScaledGet(100) -
        50;
    y = (*(s32 *)(arg0 + 4) + *(s32 *)(arg1 + 4)) / 2 + RandomScaledGet(100) -
        50;
    func_8003644C(1, x, y,
                  (*(s32 *)(arg0 + 8) + *(s32 *)(arg1 + 8)) / 2 +
                      RandomScaledGet(50) + 75);
    x2 = (*(s32 *)(arg0 + 0) + *(s32 *)(arg1 + 0)) / 2 + RandomScaledGet(100) -
         50;
    y2 = (*(s32 *)(arg0 + 4) + *(s32 *)(arg1 + 4)) / 2 + RandomScaledGet(100) -
         50;
    func_8003644C(1, x2, y2,
                  (*(s32 *)(arg0 + 8) + *(s32 *)(arg1 + 8)) / 2 +
                      RandomScaledGet(50) + 75);
}

extern void func_8003644C(s32, s32, s32, s32);
extern void func_8001EEC4Args(u8 *, s32);
asm(".globl func_8001EEC4Args\nfunc_8001EEC4Args = func_8001EEC4");

void func_80025F40(u8 *arg0, s32 arg1) {
    s32 pos[3];
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;
    u8 *entry;

    entry = (u8 *)(*(s32 *)(*(s32 *)(arg0 + 0x370) + 0x40) +
                   (1 - (arg1 & 0xFF)) * 0x18);
    pos[0] = *(s32 *)(entry + 4);
    pos[1] = *(s32 *)(entry + 8);
    pos[2] = 0x4B;
    func_8001EEC4Args(arg0, arg1 & 0xFF);
    func_8001F1D4(pos);
    pos[0] += *(s32 *)(arg0 + 0);
    pos[1] += *(s32 *)(arg0 + 4);
    pos[2] += *(s32 *)(arg0 + 8);
    x = pos[0] + RandomScaledGet(25);
    y = pos[1] + RandomScaledGet(25);
    func_8003644C(0, x, y, pos[2] + RandomScaledGet(50));
    x2 = pos[0] + RandomScaledGet(25);
    y2 = pos[1] + RandomScaledGet(25);
    func_8003644C(1, x2, y2, pos[2] + RandomScaledGet(50));
}

void func_80026074(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 ld5;
    s32 flag;
    volatile s32 pad[16];
    s32 dx;

    ld5 = arg5;
    flag = ld5;
    ld5 = ld5 << 24;
    if (ld5 != 0) {
        dx = arg2 << 16;
        *(s32 *)(arg0 + 0xC4) -= dx;
        *(s32 *)(arg0 + 0xC8) -= *(volatile s32 *)&arg3 << 16;
        *(s32 *)(arg0 + 0xD0) -= (*(volatile s32 *)&arg2 << 16) >> 1;
        *(s32 *)(arg0 + 0xD4) -= (*(volatile s32 *)&arg3 << 16) >> 1;
    } else {
        dx = arg2 << 16;
        dx = dx >> 1;
        *(s32 *)(arg0 + 0xC4) -= dx;
        *(s32 *)(arg0 + 0xC8) -= (*(volatile s32 *)&arg3 << 16) >> 1;
        *(s32 *)(arg0 + 0xD0) -= *(volatile s32 *)&arg2 << 16;
        *(s32 *)(arg0 + 0xD4) -= *(volatile s32 *)&arg3 << 16;
    }
    ld5 = flag << 24;
    if (ld5 != 0) {
        *(s32 *)(arg1 + 0xC4) += *(volatile s32 *)&arg2 << 16;
        *(s32 *)(arg1 + 0xC8) += *(volatile s32 *)&arg3 << 16;
        *(s32 *)(arg1 + 0xD0) += (*(volatile s32 *)&arg2 << 16) >> 1;
        *(s32 *)(arg1 + 0xD4) += (*(volatile s32 *)&arg3 << 16) >> 1;
    } else {
        *(s32 *)(arg1 + 0xC4) += (*(volatile s32 *)&arg2 << 16) >> 1;
        *(s32 *)(arg1 + 0xC8) += (*(volatile s32 *)&arg3 << 16) >> 1;
        *(s32 *)(arg1 + 0xD0) += *(volatile s32 *)&arg2 << 16;
        *(s32 *)(arg1 + 0xD4) += *(volatile s32 *)&arg3 << 16;
    }
}

INCLUDE_ASM("asm/nonmatchings/objects", func_800261F8);

s32 func_800270F4(void *arg0, s32 arg1) {
    s32 index;
    s32 product;
    s32 result;

    index = (0x400 - arg1) & 0x3FF;
    product = ((s32 **)D_800A3A2CAbsolute)[0][index];
    product *= *(s32 *)arg0;
    result = product -
             ((s32 **)D_800A3A34Absolute)[0][index] * *(s32 *)((s32)arg0 + 4);
    result = -(result >> 16) * 3;
    if (result < 0) {
        result += 3;
    }
    return result >> 2;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80027174);

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

extern s32 D_800980A4[];
extern s32 D_80098134[];
extern u8 D_80098194[];
extern u8 D_800981E4[];
extern s32 D_800A2E78[];

void func_80028754(u8 *arg0, s32 arg1) {
    extern s8 D_800A2E18;
    u8 *dst;
    s32 i;
    s32 scale;
    s32 offset;
    s32 *cur;
    s32 *table;
    u16 *arr1E4;
    u16 *arr194;
    s32 *src;
    s32 count;
    s32 limit;
    s32 flag;
    u16 v;
    s32 pad[4];

    flag = D_800A2EB8[0];
    table = D_800980A4;
    *(s16 *)(arg0 + 0x10E) = arg1;
    if (flag == 0) {
        D_800A2E18 = 4;
        table = D_80098134;
    }
    if (*(s16 *)(arg0 + 0x1EC) != 0) {
        if (D_800A2E18 > 0) {
            i = 0;
            count = D_800A2E18;
            src = table;
        loop1:
            *(s32 *)(arg0 + 0x124) = src[0];
            *(s32 *)(arg0 + 0x128) = src[1];
            *(s32 *)(arg0 + 0x12C) = src[2];
            *(s32 *)(arg0 + 0x130) = src[3];
            *(s32 *)(arg0 + 0x134) = src[4];
            *(s32 *)(arg0 + 0x138) = src[5];
            src += 6;
            arg0 += 0x18;
            i++;
            if (i < count) {
                goto loop1;
            }
        }
    } else if (D_800A2E18 > 0) {
        i = 0;
        cur = table;
        dst = arg0;
        offset = 0;
        arr194 = (u16 *)&D_80098194[arg1 * 8];
        arr1E4 = (u16 *)&D_800981E4[arg1 * 8];
    loop2:
        if (D_800A2EB8[0] == 0) {
            v = *arr1E4;
        } else {
            scale = *arr194;
            v = scale;
        }
        scale = MathFixedDivide(v, 0x3E8);
        do {
        } while (0);
        *(s32 *)(dst + 0x124) =
            MathMultiplyFixed16(MathFixedDivide(D_800A2E78[0], 0x4D), scale);
        if (i > 0) {
            *(s32 *)(dst + 0x128) = *(s32 *)(offset + (s32)table + 4) -
                                    (*(s32 *)(offset + (s32)table - 0x10) -
                                     *(s32 *)(offset + (s32)table - 0x14)) /
                                        5;
        } else {
            *(s32 *)(dst + 0x128) = *(s32 *)(offset + (s32)table + 4);
        }
        *(s32 *)(dst + 0x12C) = cur[2];
        *(s32 *)(dst + 0x130) = cur[3];
        *(s32 *)(dst + 0x134) = 0x32C8;
        MathMultiplyFixed16(0x17700000, scale);
        offset += 0x18;
        arr194++;
        arr1E4++;
        cur += 6;
        limit = D_800A2E18;
        *(s32 *)(dst + 0x138) = i;
        dst += 0x18;
        i++;
        if (i < limit) {
            goto loop2;
        }
    }
    (void)&pad;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80028980);

void func_80028D80(u8 *arg0) {
    u8 *node;
    extern void *D_800A3990;
    extern s8 D_800A2E18;
    extern u8 D_800A2EE4nm[] asm("D_800A2EE4.NON_MATCHING");
    s16 mode;
    s32 idx;
    u8 *base;
    u8 *row;
    s32 scale;
    s32 cur;
    s32 lim;
    s32 temp;
    s32 v1;
    s32 v7;

    node = arg0;
    mode = *(s16 *)(node + 0x1EC);
    if (mode == 0) {
        if (*(s32 *)(node + 0x28C) <= 0 ||
            (*(u16 *)(node + 0x3A4) & 0x1000) != 0) {
            *(s32 *)(node + 0x88) = 0;
            return;
        }
    } else if (mode == 1 && *(s32 *)(node + 0x290) <= 0) {
        *(s32 *)(node + 0x88) = 0;
        if (*(s16 *)(node + 0x1EC) == mode &&
            *(s32 *)(node + 0x90) <= 0x63FFFF) {
            *(s32 *)(node + 0x88) = MathFixedDivide(1, 0xA);
        }
        return;
    }
    idx = *(s16 *)(node + 0x10C);
    base = node + 0x124;
    D_800A3990 = base;
    row = (u8 *)(idx * 0x18 + (s32)base);
    scale = *(s32 *)row;
    if (*(u8 *)(node + 0xF6) == 0) {
        cur = *(s32 *)(node + 0x90);
        lim = *(s32 *)(row + 4);
        if (cur < lim) {
            if ((lim >> 16) != 0) {
                scale = MathMultiplyFixed16(
                    scale, MathFixedDivide((cur >> 16) + 0x50, lim >> 16));
            }
        } else {
            v1 = *(s32 *)(row + 8);
            if (v1 < cur) {
                scale = MathMultiplyFixed16(
                    scale, MathFixedDivide(0x10, ((cur - v1) >> 16) + 0x10));
            } else {
                scale = scale + MathFixedDivide(1, 6);
            }
        }
    } else {
        v1 = *(s32 *)(base + (s32)D_800A2E18 * 0x18 - 0x10);
        cur = *(s32 *)(node + 0x90);
        if (v1 < cur) {
            scale = MathMultiplyFixed16(
                scale, MathFixedDivide(0x10, ((cur - v1) >> 16) + 0x10));
        }
    }
    if (D_800A2EE4nm[0] != 0) {
        if (*(s16 *)(node + 0x1EC) == 0) {
            scale = MathMultiplyFixed16(
                scale, MathFixedDivide(
                           (*(s8 *)(node + 0x205) - 1) * 0x64 + 0x64, 0x64));
        }
    }
    v7 = scale * 8;
    v7 = v7 - scale;
    scale = v7 >> 2;
    *(s32 *)(node + 0x88) = scale + (*(s32 *)(node + 0x22C) >> 4);
    *(s32 *)(node + 0x90) =
        *(s32 *)(node + 0x90) + (scale + (*(s32 *)(node + 0x22C) >> 4));
}

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

void func_80028D80(u8 *);

void func_80028FCC(u8 *arg0) {
    s32 x84;

    if (arg0 != 0) {
        do {
            *(s32 *)(arg0 + 0x94) = *(s32 *)(arg0 + 0x90);
            x84 = *(s32 *)(arg0 + 0x84);
            if (*(s32 *)(arg0 + 0x90) < x84) {
                func_80028D80(arg0);
                if (x84 < *(s32 *)(arg0 + 0x90)) {
                    *(s32 *)(arg0 + 0x90) = x84;
                }
            } else {
                if (x84 < *(s32 *)(arg0 + 0x90)) {
                    *(s32 *)(arg0 + 0x90) = *(s32 *)(arg0 + 0x90) - 0x40000;
                }
            }
            func_80028980(arg0);
            arg0 = *(u8 **)(arg0 + 0x3E0);
        } while (arg0 != 0);
    }
}

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

INCLUDE_ASM("asm/nonmatchings/objects", func_80029150);

extern void func_80029150(s32 *);
void func_80029450(s32 *p) {
    func_80029150(p);
    p[0] += p[0xB0 / 4];
    p[1] += p[0xB4 / 4];
    p[2] += p[0xB8 / 4];
}

INCLUDE_ASM("asm/nonmatchings/objects", func_800294A8);

void func_800297D0(u8 *arg0) {
    extern void func_80031264(void);
    extern void func_800294A8(void *);
    extern void func_800414E0(void *, s32, s32);
    extern void func_80027174(void *);
    extern s32 D_800A2EC8NM[] asm("D_800A2EC8.NON_MATCHING");

    func_80031264();
    *(u8 *)(arg0 + 0x375) = 1;
    func_800294A8(arg0);
    if (D_800A2EB0Absolute[0] <= 0) {
        if (func_80025A38(arg0) != 0) {
            *(s16 *)(arg0 + 0x1E0) = func_8002482C(
                *(s32 *)(arg0 + 0), *(s32 *)(arg0 + 4), (s32 *)(arg0 + 0x1F8));
        }
    }
    if (*(u8 *)(arg0 + 0xF5) != 0 || *(s16 *)(arg0 + 0x1E0) == -1) {
        func_800414E0(arg0, 7, 8);
        if (*(s32 *)(arg0 + 0x354) == (s32)func_80025730 &&
            D_800A2EC8NM[0] == 0) {
            *(s32 *)(arg0 + 0) = *(s32 *)(arg0 + 0xC);
            *(s32 *)(arg0 + 4) = *(s32 *)(arg0 + 0x10);
            *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 0x14);
            *(s32 *)(arg0 + 0x90) = *(s32 *)(arg0 + 0x90) / 2;
            *(u16 *)(arg0 + 0x104) = (*(u16 *)(arg0 + 0x104) + 0x200) & 0x3FF;
        }
        func_80027174(arg0);
        *(u8 *)(arg0 + 0xF5) = 0;
        *(u8 *)(arg0 + 0x375) = 0;
    }
}

extern s32 D_800A3A2CAbsolute2[];
extern s32 D_800A3A34Absolute2[];
void func_800298E0(s32 *car) {
    s32 index;

    index = ((s16 *)car)[0x8A];
    car[0x31] =
        MathMultiplyFixed16((*(s32 **)D_800A3A2CAbsolute)[index], car[0x24]);
    car[0x32] =
        MathMultiplyFixed16((*(s32 **)D_800A3A34Absolute)[index], car[0x24]);
    car[0x34] =
        MathMultiplyFixed16((*(s32 **)D_800A3A2CAbsolute2)[index], car[0x24]);
    car[0x35] =
        MathMultiplyFixed16((*(s32 **)D_800A3A34Absolute2)[index], car[0x24]);
}

extern void func_8003644C(s32, s32, s32, s32);

void func_80029994(u8 *arg0, s32 arg1) {
    s32 pos[3];
    s32 x;
    u8 *entry;

    if (*(u8 *)(arg0 + 0xF4) != 0) {
        entry = (u8 *)(*(s32 *)(*(s32 *)(arg0 + 0x370) + 0x40) + arg1 * 0x18);
        pos[0] = *(s32 *)(entry + 4);
        pos[1] = *(s32 *)(entry + 8);
        pos[2] = *(s32 *)(entry + 0xC);
        func_8001EEC4((s32 *)arg0);
        func_8001F1D4(pos);
        pos[0] += *(s32 *)(arg0 + 0);
        pos[1] += *(s32 *)(arg0 + 4);
        pos[2] += *(s32 *)(arg0 + 8);
        x = pos[0] + RandomScaledGet(25);
        func_8003644C(1, x, pos[1] + RandomScaledGet(25), pos[2]);
    }
}

extern void func_8001FAC0(u8 *, s32);
extern s32 D_800A2E1C;

void func_80029A78(u8 *car) {
    s32 angle;
    s32 dist10;
    s32 value;
    s32 scale;
    s32 vx;
    s32 vy;

    *(u16 *)(car + 0x104) = *(u16 *)(car + 0x114);
    func_8001F2C4(*(s16 *)(car + 0x114), 0, 0);
    func_8001F874((s32 *)car);
    if (*(u8 *)(car + 0x410) != 0) {
        *(u16 *)(car + 0x20E) = -*(u16 *)(car + 0x20E);
    }
    angle = *(s16 *)(car + 0x20E);
    if (angle < 0) {
        angle += 0x1000;
    }
    if (*(s32 *)(car + 0xB0) >= 0 ? *(s32 *)(car + 0xB0) < 0x28
                                  : -*(s32 *)(car + 0xB0) < 0x28) {
        if (*(s32 *)(car + 0xB4) >= 0 ? *(s32 *)(car + 0xB4) < 0x28
                                      : -*(s32 *)(car + 0xB4) < 0x28) {
            vx = *(s32 *)(car + 0xB0);
            vy = *(s32 *)(car + 0xB4);
            dist10 = (s32)MathSqrt(vx * vx + vy * vy) * D_800A2E1C / 10;
            if (*(s16 *)(car + 0x20E) >= 0 ? dist10 < *(s16 *)(car + 0x20E)
                                           : dist10 < -*(s16 *)(car + 0x20E)) {
                if (*(s16 *)(car + 0x20E) >= 0) {
                    angle = dist10;
                } else {
                    angle = (0x1000 - dist10) & 0xFFF;
                }
            }
        }
    }
    *(u16 *)(car + 0x1D0) = angle / 4;
    scale = 1000;
    if (angle >= 0x801) {
        angle -= 0x1000;
    }
    dist10 = angle * scale / 1000;
    *(u16 *)(car + 0x212) = dist10 / 4;
    if (dist10 < 0) {
        dist10 += 0x1000;
    }
    value = (*(u16 *)(car + 0x116) + dist10) & 0xFFF;
    *(u16 *)(car + 0x116) = value;
    *(s16 *)(car + 0x114) = value / 4;
    func_8001FAC0(car, *(s16 *)(car + 0x116));
    if (*(u8 *)(car + 0x410) != 0) {
        *(u16 *)(car + 0x20E) = -*(u16 *)(car + 0x20E);
    }
}

extern s32 D_800A3A04nm[] asm("D_800A3A04.NON_MATCHING");

void func_80029CB4(s32 *arg0) {
    s32 speed;
    s32 limit;
    s32 i;
    s32 off;
    s16 *entry;
    s16 angle;

    speed = D_800A3A04nm[0];
    limit = speed * 4;
    for (i = 0; i < 4; i++) {
        off = 0x2AC + i * 0x28;
        entry = (s16 *)((u8 *)arg0 + off);
        if (entry[2] != 0 || entry[0] != 0) {
            entry[0] += entry[2];
            if (entry[0] < 0) {
                entry[0] = 0;
                if (entry[2] >= 0 ? limit >= entry[2] : limit >= -entry[2]) {
                    entry[2] = 0;
                } else {
                    entry[2] = -entry[2] / 2;
                }
            } else {
                entry[2] -= speed;
            }
            angle = entry[0];
            if (angle >= 0x101) {
                angle = 0x100;
                entry[0] = angle;
            }
        }
    }
}

extern void func_80029CB4(s32 *arg0);
extern void func_80039B74(s32 *arg0, s32 arg1);
void func_80029DA8(s32 *car) {
    volatile s32 debugBuffer[16];
    s32 a;
    s32 b;
    s32 c;

    func_8002D16C(car);
    func_8002B538(car);
    func_80029A78(car);
    func_80029150(car);
    a = car[0] + car[0x2C];
    b = car[1] + car[0x2D];
    c = car[2] + car[0x2E];
    car[0] = a;
    car[1] = b;
    car[2] = c;
    func_80029CB4(car);
    func_80039B74(car, 0);
}

void func_80029E2C(void) {
}

void func_80029E34(void) {
}

void func_80029E3C(void) {
}

/* The volatile asm births the zero passed to func_8001F2C4 early, and being
 * volatile it holds move a2,zero in retail's slot. The reads of the three
 * words copied down (and their order) set sched1's load order and the
 * local-alloc reference counts; the second asm is a zero-byte anchor that
 * keeps the v0/v1 handout on the 0x18/0x1C pair like retail. */
extern s32 D_800A38AC[];
extern void func_8001F2C4(s32 arg0, s32 arg1, s32 arg2);
extern void func_8001F728(s32 arg0);

void func_80029E44(void) {
    s32 *sourceRow;
    u8 *secondRow;
    u8 *ptr;
    u8 *rowA;
    u8 *rowB;
    s32 zero;
    s32 x;
    s32 y;
    s32 valA;
    s32 valC;
    s32 valB;
    ptr = (u8 *)D_800A38AC[0];
    asm volatile("" : "=r"(zero) : "0"(0));
    sourceRow = (s32 *)(ptr + 0x18);
    valA = *((s32 *)(ptr + 0x20));
    valB = *sourceRow;
    valC = *((s32 *)(ptr + 0x1C));
    asm("" : : "r"(valB), "r"(valB), "r"(valC));
    *((s32 *)(ptr + 0x3C)) = valB;
    *((s32 *)(ptr + 0x40)) = valC;
    *((s32 *)(ptr + 0x44)) = valA;
    asm("");
    *((s32 *)(ptr + 0x48)) = *((s32 *)(ptr + 0x24));
    *((s32 *)(ptr + 0x4C)) = *((s32 *)(ptr + 0x28));
    *((s32 *)(ptr + 0x50)) = *((s32 *)(ptr + 0x2C));
    asm("");
    *((s32 *)(ptr + 0x54)) = *((s32 *)(ptr + 0x30));
    *((s32 *)(ptr + 0x58)) = *((s32 *)(ptr + 0x34));
    *((s32 *)(ptr + 0x5C)) = *((s32 *)(ptr + 0x38));
    asm("");
    x = *((s16 *)(ptr + 0x1C6));
    y = *((s16 *)(ptr + 0x1C8));
    rowA = ptr + 0x3C;
    secondRow = ptr + 0x48;
    rowB = secondRow;
    ptr += 0x54;
    func_8001F2C4(x, y, zero);
    func_8001F728((s32)rowA);
    func_8001F728((s32)rowB);
    func_8001F728((s32)ptr);
}

extern u8 D_800A3A24w15f[] asm("D_800A3A24.NON_MATCHING");
extern u8 D_800A2EE0w15f[] asm("D_800A2EE0.NON_MATCHING");
extern u8 D_800A3764w15f[] asm("D_800A3764.NON_MATCHING");
extern u8 D_800A372Cw15f[] asm("D_800A372C.NON_MATCHING");
extern s16 D_800A35A4w15f[] asm("D_800A35A4.NON_MATCHING");
extern s32 func_8006E770(u8);
extern void func_8006EB18(u8 *);
extern void func_80044114(u8 *);

s32 func_80029EF8(u8 *obj) {
    s32 flags;
    s32 v;
    s32 c4;

    c4 = *(s8 *)(obj + 0x3C4);
    v = *(s8 *)(obj + 0x20B);
    if (c4 == 0) {
        obj[0x3C4] = D_800A3A24w15f[v];
    }
    flags = func_8006E770(obj[0x20B]);
    v = *(s8 *)(obj + 0x3C4);
    if (v == 2) {
        goto twoFiveSeven;
    }
    if (v == 5) {
        goto twoFiveSeven;
    }
    if (v != 7) {
        goto notTwoFiveSeven;
    }
twoFiveSeven:
    func_8006EB18(obj);
    *(s16 *)(obj + 0x20E) =
        -((*(s8 *)(obj + 0x3C5) << 2) * (D_800A2E1C + 2)) / 128;
    *(s32 *)(obj + 0x3BC) = MathFixedDivide(obj[0x3C6], 0xFF);
    *(s32 *)(obj + 0x3C0) = MathFixedDivide(obj[0x3C7], 0x7D0);
    if (obj[0x3C6] < 0x3C) {
        flags &= ~0x40;
    } else {
        flags |= 0x40;
    }
    if (obj[0x3C7] < 0xE6) {
        flags &= ~0x80;
    } else {
        flags |= 0x80;
    }
    v = *(s16 *)(obj + 0x20E);
    if (v >= 2) {
        flags |= 0x8000;
    } else if (v < -1) {
        flags |= 0x200;
    }
    goto afterStatus;
notTwoFiveSeven:
    if (flags & 0x40) {
        *(s32 *)(obj + 0x3BC) += 0x2000;
        if (0x10000 < *(s32 *)(obj + 0x3BC)) {
            *(s32 *)(obj + 0x3BC) = 0x10000;
        }
    } else {
        *(s32 *)(obj + 0x3BC) = 0;
    }
    *(s32 *)(obj + 0x3C0) = 0x10000;
afterStatus:
    if (D_800A2EE0w15f[0] != 0) {
        if (obj[0x3B7] != 0) {
            goto decr3b7;
        }
        if (*(s32 *)(obj + 0x354) == (s32)func_80025594 ||
            *(s16 *)(obj + 0x1BC) == 4) {
            if (flags & 0x40) {
                if ((*(u16 *)(obj + 0x3A4) & 0xF) != 0 ||
                    *(s16 *)(obj + 0x1BC) == 4 ||
                    ((*(u16 *)(obj + 0x3A4) & 0x1000) != 0 &&
                     *(s32 *)(obj + 0x90) == 0)) {
                    func_80044114(obj);
                }
                goto skip3b7;
            }
        }
        if (obj[0x3B7] != 0) {
        decr3b7:
            obj[0x3B7]--;
        }
    skip3b7:;
    }
    if (*(s32 *)(obj + 0x354) == (s32)func_80025730 || obj[0xF4] == 0 ||
        D_800A3764w15f[0] != 0 ||
        (D_800A372Cw15f[0] != 0 && D_800A35A4w15f[0] >= 0x32)) {
        flags &= ~(0x40 | 0x80 | 0x200 | 0x8000);
        *(s32 *)(obj + 0x3BC) = 0;
    } else if (*(s32 *)(obj + 0x28C) <= 0 ||
               (*(s32 *)(obj + 0x3A4) & 0x100F) != 0) {
        flags &= ~0x40;
        *(s32 *)(obj + 0x3BC) = 0;
    }
    return flags;
}

extern s32 D_800A2E1C, D_800A2E24;
void func_8002A1D0(void) {
    D_800A2E24 = 0x1EF0000 - (D_800A2E1C - 3) * 0x30000;
}

extern s32 D_800A35D4[];
extern s32 D_800A2EA4[];
extern s32 func_80029EF8();
extern void func_8001FD44();

/* Sets bit D_800A2EC4 when the object's 0x209 counter wraps to 3 and the
   0x238 status mask from func_80029EF8 asks for the counter update.
   The (u16) casts keep `~status & MASK` as a unit that flags is ANDed
   with; without them fold reassociates it into `(flags & MASK) & ~status`. */
void func_8002A1FC(u8 *arg0) {
    s32 flags;
    s32 v;
    s32 t;

    flags = func_80029EF8(arg0);
    if (((flags & ((u16) ~*(s32 *)(arg0 + 0x238) & 0x10)) != 0) ||
        ((flags & ((u16) ~*(s32 *)(arg0 + 0x238) & 0x4000)) != 0)) {
        func_8001FD44(arg0);
    }
    if (*(u8 *)D_800A35D4 != 0) {
        *(s32 *)(arg0 + 0x238) = flags;
        return;
    }
    if ((flags & ((u16) ~*(s32 *)(arg0 + 0x238) & 4)) != 0) {
        if (D_800A2EA4[0] != 0) {
            v = *(u8 *)(arg0 + 0x209) ^ 1;
            *(u8 *)(arg0 + 0x209) = v;
        } else {
            t = *(s8 *)(arg0 + 0x209);
            v = (t + 1) % 4;
            *(u8 *)(arg0 + 0x209) = v;
            D_800A2EC4w15[0] = ((s8)v == 3);
        }
        *(s32 *)(arg0 + 0x238) = flags;
    } else {
        *(s32 *)(arg0 + 0x238) = flags;
    }
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002A2F8);

extern u8 D_800A331C[];
extern u8 D_800A331D[];
extern u8 D_800A331F[];
extern u8 D_800A3320[];
extern u8 D_800A2E20[];
extern s32 D_800A2E30;
extern s32 D_800A2E38;
extern s32 D_800A2E3C;
extern s32 D_800A2E44;
extern s32 D_800A2E48;
extern s32 D_800A2E4C;
extern s32 D_800A2E54;
extern s16 D_800A2E58;
extern s32 D_800A2E5C;
extern s32 D_800A3A04;
extern s32 D_800A2E50;

void func_8002A954(void) {
    D_800A2E44 = 0x5D;
    D_800A2E48 = 0x1A;
    D_800A2E50 = (D_800A331D[0] - 0x32) * 0x50;
    D_800A2E20[0] = D_800A3320[0];
    D_800A2E54 = (0x70 - D_800A331F[0]) * 0x10000;
    D_800A2E4C = (D_800A331C[0] + 0xC8) / 3;
    D_800A2E58 = 0x3A98 / (D_800A331D[0] - 0x46);
    D_800A2E5C = 0x28A0000 / (D_800A331F[0] - 0x14);
    if (D_800A331F[0] > 0x64) {
        D_800A2E54 = 0xC0000 - (D_800A331F[0] - 0x64) * 0x10000 / 5;
    }
    D_800A2E30 = 0x10CC;
    D_800A2E38 = 0x23;
    D_800A2E3C = 0x23;
    D_800A3A04 = 0xD;
}

s32 func_8002AAA0(s32 *car) {
    s32 weight;
    s32 total;
    s32 base;

    base = (car[0x14] * 200) >> 16;
    total = (car[0x90] * 35 + car[0x91] * 5) >> 16;
    weight = base + 3000;
    return total + weight;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002AAF0);

void func_8002AD20(s32 *car, s32 index) {
    s32 entryA;
    s32 entryB;

    entryA = ((s32 **)D_800A3A2CAbsolute)[0][index];
    entryB = ((s32 **)D_800A3A34Absolute)[0][index];
    car[0x31] = MathMultiplyFixed16(entryA, car[0x24]);
    car[0x32] = MathMultiplyFixed16(entryB, car[0x24]);
    car[0x34] = MathMultiplyFixed16(entryA, car[0x24]);
    car[0x35] = MathMultiplyFixed16(entryB, car[0x24]);
    car[0x2C] = MathMultiplyFixed16(entryA, car[0x24]) >> 16;
    car[0x2D] = MathMultiplyFixed16(entryB, car[0x24]) >> 16;
}

void func_8002ADE0(s32 *car, s32 arg1) {
    s32 index;
    s32 entryA;
    s32 entryB;

    index = (((s16 *)car)[0x8A] + 0x200) & 0x3FF;
    entryA = ((s32 **)D_800A3A2CAbsolute)[0][index];
    entryB = ((s32 **)D_800A3A34Absolute)[0][index];
    car[0x31] = car[0x31] + MathMultiplyFixed16(entryA, arg1);
    car[0x32] = car[0x32] + MathMultiplyFixed16(entryB, arg1);
    car[0x34] = car[0x34] + MathMultiplyFixed16(entryA, arg1);
    car[0x35] = car[0x35] + MathMultiplyFixed16(entryB, arg1);
}

s32 func_8002AEB0(u8 *arg0) {
    s32 index;
    VECTOR rotated;
    s32 value;
    s32 temp;
    s32 product;

    index = (0x400 - *(s16 *)(arg0 + 0x114)) & 0x3FF;
    product = ((s32 **)D_800A3A2CAbsolute)[0][index] * *(s32 *)(arg0 + 0xB0);
    rotated.vx = (product - (((s32 **)D_800A3A34Absolute)[0][index] *
                             *(s32 *)(arg0 + 0xB4))) >>
                 16;
    product = ((s32 **)D_800A3A34Absolute)[0][index] * *(s32 *)(arg0 + 0xB0);
    rotated.vy = (product + (((s32 **)D_800A3A2CAbsolute)[0][index] *
                             *(s32 *)(arg0 + 0xB4))) >>
                 16;
    value = rotated.vx;
    if (value < 0) {
        temp = -value;
        *(u8 *)(arg0 + 0x410) = temp;
        value = 0;
        if ((temp & 0xFF) >= 0x65U) {
            *(u8 *)(arg0 + 0x410) = 0x64;
        }
    } else {
        *(u8 *)(arg0 + 0x410) = 0;
    }
    return value << 16;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002AF94);

extern s32 D_800A2E44nm asm("D_800A2E44.NON_MATCHING");
extern s32 D_800A2E48nm asm("D_800A2E48.NON_MATCHING");

void func_8002B258(u8 *arg0) {
    extern u8 D_800A2EE4nm[] asm("D_800A2EE4.NON_MATCHING");
    extern s32 D_800A3A2CAbsoluteB[] asm("D_800A3A2CAbsolute");
    extern s32 D_800A3A34AbsoluteB[] asm("D_800A3A34Absolute");
    volatile s32 pad[16];
    s32 speed;
    s32 index;
    s32 scale;
    s32 value;
    s32 p;
    s32 *q;
    s32 v;
    s32 x;

    if (*(s32 *)(arg0 + 0x238) & 0x80) {
        speed = D_800A2E48nm << 16;
        if (*(s16 *)(arg0 + 0x120) != 0) {
            speed = speed / 3;
        }
        if (*(s8 *)(arg0 + 0x3C4) != 4) {
            *(s32 *)(arg0 + 0x228) =
                MathMultiplyFixed16(speed, *(s32 *)(arg0 + 0x3C0));
        } else {
            *(s32 *)(arg0 + 0x228) += MathFixedDivide(D_800A2E44nm, 100);
            if (speed < *(s32 *)(arg0 + 0x228)) {
                *(s32 *)(arg0 + 0x228) = speed;
            }
        }
        if (*(s32 *)(arg0 + 0x228) > *(s32 *)(arg0 + 0x90)) {
            *(s32 *)(arg0 + 0x228) = *(s32 *)(arg0 + 0x90);
        }
        scale = *(s32 *)(arg0 + 0x228);
        index = *(s16 *)(arg0 + 0x104);
        if (D_800A2EE4nm[0] != 0) {
            scale = MathMultiplyFixed16(
                scale,
                MathFixedDivide((*(s8 *)(arg0 + 0x205) - 1) * 50 + 100, 100));
            if (*(s32 *)(arg0 + 0x90) < scale) {
                scale = *(s32 *)(arg0 + 0x90);
            }
        }
        if ((*(s32 *)(arg0 + 0xB0) >= 0 ? *(s32 *)(arg0 + 0xB0) < 10
                                        : -*(s32 *)(arg0 + 0xB0) < 10) &&
            (*(s32 *)(arg0 + 0xB4) >= 0 ? *(s32 *)(arg0 + 0xB4) < 10
                                        : -*(s32 *)(arg0 + 0xB4) < 10)) {
            *(s32 *)(arg0 + 0xC4) = 0;
            *(s32 *)(arg0 + 0xC8) = 0;
            *(s32 *)(arg0 + 0xD0) = 0;
            *(s32 *)(arg0 + 0xD4) = 0;
        } else {
            if (scale == 0) {
                scale = 0x50000;
            }
            v = MathMultiplyFixed16((*(s32 **)D_800A3A2CAbsolute)[index],
                                    scale);
            x = *(s32 *)(arg0 + 0xC4);
            p = *(s32 *)D_800A3A34Absolute;
            x -= v;
            *(s32 *)(arg0 + 0xC4) = x;
            q = (s32 *)(index * 4 + p);
            v = MathMultiplyFixed16(*q, scale);
            x = *(s32 *)(arg0 + 0xC8);
            p = *(s32 *)D_800A3A2CAbsoluteB;
            x -= v;
            *(s32 *)(arg0 + 0xC8) = x;
            q = (s32 *)(index * 4 + p);
            v = MathMultiplyFixed16(*q, scale);
            x = *(s32 *)(arg0 + 0xD0);
            p = *(s32 *)D_800A3A34AbsoluteB;
            x -= v;
            *(s32 *)(arg0 + 0xD0) = x;
            *(s32 *)(arg0 + 0xD4) -=
                MathMultiplyFixed16(*(s32 *)(index * 4 + p), scale);
        }
        if (*(s32 *)(arg0 + 0x90) > 0x17C0000 && RandomScaledGet(0xA) == 0) {
            value = RandomScaledGet(4);
            if (value < 0) {
                value = -RandomScaledGet(4);
            } else {
                value = RandomScaledGet(4);
            }
            *(s16 *)(arg0 + 0x2D8) = value;
            *(s16 *)(arg0 + 0x2B0) = value;
        }
    } else {
        *(s32 *)(arg0 + 0x228) -= 0x10000;
        if (*(s32 *)(arg0 + 0x228) < 0) {
            *(s32 *)(arg0 + 0x228) = 0;
        }
        *(s16 *)(arg0 + 0x11E) = 0;
        *(s16 *)(arg0 + 0x120) = 0;
        *(s16 *)(arg0 + 0x11C) = 0;
    }
}

void func_8002B538(u8 *arg0) {
    s32 speed;
    s32 half;

    speed = (*(s32 *)(arg0 + 0x90) / *(s16 *)(arg0 + 0x2B4)) >> 16;
    if (*(s16 *)(arg0 + 0x120) != 0 || *(u8 *)(arg0 + 0xF8) != 0) {
        speed = speed * 4;
    }
    *(s32 *)(arg0 + 0x2B8) -= speed;
    *(s32 *)(arg0 + 0x2E0) -= speed;
    half = speed / 2;
    if (*(s32 *)(arg0 + 0x2B8) <= 0x9FFFF) {
        *(s32 *)(arg0 + 0x2B8) = 0xA0000;
    }
    if (*(s32 *)(arg0 + 0x2E0) <= 0x9FFFF) {
        *(s32 *)(arg0 + 0x2E0) = 0xA0000;
    }
    *(s32 *)(arg0 + 0x308) -= half;
    *(s32 *)(arg0 + 0x330) -= half;
    if (*(s32 *)(arg0 + 0x308) <= 0x9FFFF) {
        *(s32 *)(arg0 + 0x308) = 0xA0000;
    }
    if (*(s32 *)(arg0 + 0x330) <= 0x9FFFF) {
        *(s32 *)(arg0 + 0x330) = 0xA0000;
    }
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002B63C);

INCLUDE_ASM("asm/nonmatchings/objects", func_8002B9AC);

extern s32 D_800A2E24Absolute[];
extern s32 D_800A2E40;

void func_8002BC88(u8 *arg0) {
    s32 y;
    s32 val;
    s32 result;
    s32 d;
    y = (*(s16 *)(arg0 + 0x2A6) + 1) * 75 << 16;
    val = D_800A2E24Absolute[0] + *(s32 *)(arg0 + 0x22C) -
          (*(s16 *)(arg0 + 0x10E) << 17) - y / 15;
    result = MathFixedDivide(*(s32 *)(arg0 + 0x28C), 16000);
    d = D_800A2E40;
    val -= result * d - ((d / 2) << 16);
    *(s32 *)(arg0 + 0x98) = val;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002BD48);

s32 func_8002CF1C(void) {
    return 2000;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002CF24);

extern s32 D_800A2E94[];
s32 func_8003702C(u8 *, u8 *);
s32 func_8002CF24(u8 *, u8 *);

void func_8002D16C(u8 *arg0) {
    u8 *other;
    s32 flag;
    s32 flag40;
    s32 value;
    s32 newValue;

    *(u8 *)(arg0 + 0x3FC) = 0;
    if (0x8BFFFF < *(s32 *)(arg0 + 0x90)) {
        if (D_800A2E94[0] >= 2) {
            other = *(u8 **)(*(s32 *)(arg0 + 0x3F0) + 8);
            if (other != 0) {
                flag = 1;
                flag40 = 0x28;
                do {
                    if (arg0 == other) {
                        goto decay;
                    }
                    if (func_8003702C(arg0, other) < -0xA) {
                        goto decay;
                    }
                    if ((func_8002CF24(arg0, other) & 0xFF) != 0) {
                        *(u8 *)(arg0 + 0x3FC) = flag;
                        if (*(s16 *)(other + 0x1EC) == 0) {
                            return;
                        }
                        *(u8 *)(other + 0x3FC) = flag40;
                        return;
                    }
                    other = *(u8 **)(*(s32 *)(other + 0x3F0) + 8);
                } while (other != 0);
            }
        decay:
            value = *(s32 *)(arg0 + 0x22C);
            if (value > 0) {
                newValue = value - 0x8000;
                *(s32 *)(arg0 + 0x22C) = newValue;
                if (newValue < 0) {
                    *(s32 *)(arg0 + 0x22C) = 0;
                }
            }
            return;
        }
        *(s32 *)(arg0 + 0x22C) = 0;
    }
}

void func_8002D27C(u8 *arg0) {
    s32 value;

    if (!(0x9FFFF < *(s32 *)(arg0 + 0x90))) {
        *(s16 *)(arg0 + 0x120) = 0;
        *(s16 *)(arg0 + 0x11E) = 0;
    } else {
        if (*(s16 *)(arg0 + 0x120) > 0) {
            *(s16 *)(arg0 + 0x120) = *(s16 *)(arg0 + 0x120) - 1;
            value = RandomScaledGet(4);
            if (value < 0) {
                value = -RandomScaledGet(4);
            } else {
                value = RandomScaledGet(4);
            }
            func_80029994(arg0, value);
        }
        if (*(s32 *)(arg0 + 0x238) & 0x80) {
            if (*(s8 *)(arg0 + 0x3C4) == 4) {
                *(u16 *)(arg0 + 0x11E) += 1;
            } else {
                if (*(s32 *)(arg0 + 0x3C0) >= MathFixedDivide(0xFA, 0x7D0)) {
                    *(u16 *)(arg0 + 0x11E) += 1;
                }
            }
        } else {
            *(s16 *)(arg0 + 0x11E) = 0;
        }
        if (*(s16 *)(arg0 + 0x11E) >= 0x13) {
            *(s16 *)(arg0 + 0x120) = 0x23;
            *(s16 *)(arg0 + 0x11E) = 0;
        }
    }
}

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

extern s32 D_800A2E7Cgp asm("D_800A2E7C.NON_MATCHING");
extern s32 D_800A2E80gp asm("D_800A2E80.NON_MATCHING");
extern s32 D_800A2E64[];
extern u8 D_800A3860[][4];

void func_8002D3EC(u8 *arg0) {
    u8 *entry;
    s32 i;
    s32 diff;

    diff = D_800A2E7Cgp - D_800A2E80gp;
    i = diff;
    *(s32 *)(arg0 + 0x234) =
        D_800A2E80gp + i * (s8)D_800A3860[*(s8 *)(arg0 + 0x20B)][0] / 63;
    diff = D_800A2E64[0] - (s8)D_800A3860[*(s8 *)(arg0 + 0x20B)][0] * 0xC8 / 63;
    entry = arg0;
    i = 0;
    do {
        *(s16 *)(arg0 + i * 0x28 + 0x2B2) = 0;
        *(s16 *)(arg0 + i * 0x28 + 0x2B0) = 0;
        *(s16 *)(arg0 + i * 0x28 + 0x2AE) = 0;
        *(s16 *)(arg0 + i * 0x28 + 0x2B4) = diff;
        *(s32 *)(arg0 + i * 0x28 + 0x2B8) = *(s32 *)(arg0 + 0x234);
        i += 1;
        entry += 0x28;
    } while (i < 4);
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002D4CC);

#ifdef NON_MATCHING
/* 2026-10-11 parked at 1893 (fresh pure-C draft from Ghidra's retail decompile).
 * Semantics fully decoded: 0x500 pool entry (D_800A2E84 counter), func_8002D3A8-
 * style negative-index table setup, callback dispatch on arg0 (a0-only
 * func_8002DA30 call confirmed from retail), per-type tables via off = arg1*16.
 * Residual: retail folds each D_800A2E94 access into its own lui+%lo pair
 * (three single-use addresses) and materialises D_800A2EB4's read/write
 * separately; this gcc cse-shares the (symbol,0) address pseudo instead, and
 * allocates arg0 to s1 where retail has off (s1/s2 swap). Neighbor-symbol
 * spellings would need new symbol_addrs entries (image-shift risk). */
void func_8002D874(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 D_800A2E88;
    extern s32 D_800A2E94[];
    extern s32 D_800A2EB4[];
    extern s32 D_800BE72C[];
    extern s32 D_800BE730[];
    extern s16 D_800BE738[];
    extern void func_8002A2F8(u8 *);
    extern void func_800373B4(u8 *);
    extern void func_80029E34(void);
    extern void func_80025594(u8 *);
    extern void func_8002D4CC();
    u8 *entry;
    u8 *data;
    s32 index;
    s32 off;
    s32 b;
    s32 w;

    index = D_800A2E84++;
    entry = (u8 *)D_800A3984[0] + index * 0x500;
    if (arg3 < 0) {
        arg3 = -arg3;
        data = D_800AE88C + arg3 * 0x44;
    } else {
        data = D_800AE88C;
    }
    *(u8 **)(entry + 0x370) = data;
    *(u8 **)(entry + 0x36C) = data;
    entry[0x374] = 0;
    entry[0x200] = arg3;
    func_8002DA30((s32 *)entry);
    *(s16 *)(entry + 0x1EC) = arg0;
    if (arg0 == 0) {
        *(u32 *)(entry + 0x350) = (u32)func_8002A2F8;
        D_800A2EB4[0] = D_800A2EB4[0] + 1;
    } else if (arg0 == 1) {
        *(u32 *)(entry + 0x350) = (u32)func_800373B4;
    } else {
        *(u32 *)(entry + 0x350) = (u32)func_80029E34;
    }
    *(u32 *)(entry + 0x354) = (u32)func_80025594;
    off = arg1 * 16;
    *(u32 *)(entry + 0) = *(u32 *)((u8 *)D_800BE72C + off);
    *(u32 *)(entry + 4) = *(u32 *)((u8 *)D_800BE730 + off);
    *(u32 *)(entry + 8) = 0;
    if (arg0 == 0) {
        b = D_800A2E88;
        D_800A2E88 = b + 1;
        entry[0x20B] = b;
    }
    func_8002D4CC(entry);
    func_80028754(entry, 5);
    func_80022FB8(entry, *(s16 *)((u8 *)D_800BE738 + off));
    w = D_800A2E94[0];
    b = arg1 + 1;
    entry[0x204] = b;
    entry[0x205] = b;
    entry[0x3C9] = b;
    *(s16 *)(entry + 0x28A) = arg2;
    *(s16 *)(entry + 0x1DE) = w;
    D_800A2E94[0] = D_800A2E94[0] + 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/objects", func_8002D874);
#endif

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

extern void HeapFree(void *ptr);
extern void *D_800BE980_w42[] asm("D_800BE980.NON_MATCHING");
extern void *D_800A3A40_w42[] asm("D_800A3A40.NON_MATCHING");
extern void *D_800A39A4_w42[] asm("D_800A39A4.NON_MATCHING");
extern void *D_800A3A8C_w42[] asm("D_800A3A8C.NON_MATCHING");
extern void *D_800A39A4Absolute[];
extern void *D_800A3A8CAbsolute[];
extern void *D_800A3A38p[] asm("D_800A3A38");
extern void *D_800B60A4_w42[] asm("D_800B60A4.NON_MATCHING");
extern u8 D_800AE8A0_w42[] asm("D_800AE8A0.NON_MATCHING");
extern u8 D_800AE8C4_w42[] asm("D_800AE8C4.NON_MATCHING");
extern u8 D_800AE8CC_w42[] asm("D_800AE8CC.NON_MATCHING");
extern u8 D_800AE8A0p[] asm("D_800AE8A0");
extern u8 D_800AE8CCp[] asm("D_800AE8CC");
extern s32 D_800A2F54_w42[] asm("D_800A2F54.NON_MATCHING");
extern s32 D_800A3630_w42b asm("D_800A3630.NON_MATCHING");
extern s32 D_800A2EC8Small;
extern s32 D_800A2ED4_w42 asm("D_800A2ED4.NON_MATCHING");

extern s32 D_800A3A38Lui asm("D_800A3A38Absolute");
void func_8002DA80(void) {
    void **p;
    u8 *q;
    s32 off;
    s32 i;
    void *ptr;
    s32 pad[2];

    i = 0;
    p = D_800BE97C;
    HeapFree(p[0]);
    ptr = D_800A3A40_w42[0];
    p[0] = 0;
    HeapFree(ptr);
    D_800A3A40Absolute[0] = 0;
    HeapFree(D_800A39A4_w42[0]);
    D_800A39A4Absolute[0] = 0;
    HeapFree(D_800BE980_w42[0]);
    D_800BE97C[1] = 0;
    HeapFree((void *)D_800A3A38Lui);
    D_800A3A38Lui = 0;
    HeapFree(D_800A3A8C_w42[0]);
    D_800A3A8CAbsolute[0] = 0;
    p = D_800B60A4_w42;
    do {
        if (p[0] != 0) {
            HeapFree(p[0]);
            p[0] = 0;
        }
        i += 1;
        p += 1;
    } while (i < 2);

    i = 0;
    if (D_800A3630_w42b * 5 > 0) {
        q = D_800AE8C4_w42;
        do {
            off = i * 0x44;
            if (i < 5) {
                HeapFree(*(void **)(D_800AE8A0_w42 + off));
                *(void **)(D_800AE8A0p + off) = 0;
            }
            HeapFree(*(void **)q);
            *(void **)q = 0;
            if (*(void **)(D_800AE8CC_w42 + off) != 0) {
                HeapFree(*(void **)(D_800AE8CC_w42 + off));
                *(void **)(D_800AE8CCp + off) = 0;
            }
            q += 0x44;
            i += 1;
        } while (i < D_800A3630_w42b * 5);
    }
    D_800A2EC8Small = 0;
    D_800A2ED4_w42 = 0;
    D_800A2F54_w42[0] = 0;
    (void)&pad;
}

extern s32 D_800A353C_a[] asm("D_800A353C.NON_MATCHING");
extern s32 D_800A353C_b[] asm("D_800A3540.NON_MATCHING");
extern s32 D_800A353C_c[] asm("D_800A3538.NON_MATCHING");
extern s32 D_800A3758_a[] asm("D_800A3758.NON_MATCHING");
extern s32 D_800A3758_b[] asm("D_800A3754.NON_MATCHING");
extern s32 D_800A3758_c[] asm("D_800A3760.NON_MATCHING");
extern u8 *D_800A3574_a[] asm("D_800A3574.NON_MATCHING");
extern u8 *D_800A3574_b[] asm("D_800A3570.NON_MATCHING");
extern s32 D_800A3630_nm asm("D_800A3630.NON_MATCHING");
extern s32 D_800A2F30_nm[] asm("D_800A2F30.NON_MATCHING");
extern u8 D_800AE99C_nm[] asm("D_800AE99C.NON_MATCHING");
extern void func_8003CDBC();
extern void func_8001E17C();
extern void func_800323F0(s32, s32);
extern void func_80032494(u8 *);
void func_8002DC2C(void) {
    u8 *entry;
    s32 cursor;
    s32 sel;
    s32 slot;
    s32 page;
    s32 first;
    s32 ratio;
    s32 none;

    D_800A353C_a[0] = MathFixedDivide(6, 0xF);
    D_800A3758_a[0] = MathFixedDivide(1, 2);
    D_800A3630_nm = 0x18;
    D_800A3758_b[1] = D_800A353C_c[1];
    func_8003CDBC(0xA7, (void *)STACK_BLOCK_801A0000);
    func_8001E17C(6);
    D_800A2F30_nm[0] = 0;
    cursor = 0;
    for (page = 0, first = 0; page < 1; page++, first += 5) {
        sel = (page == 0) ? -1 : 0;
        for (slot = 0; slot < 4; slot++) {
            entry = D_800AE88C + (first + slot) * 0x44;
            D_800A3574_a[0] = entry;
            func_800323F0(cursor, sel);
            cursor++;
            func_80032494(entry);
            /* A second store makes `none` multi-set, so loop.c keeps the
               constant in the loop (retail reloads -1 each pass). */
            none = -1;
            if (sel != none) {
                sel++;
            }
            none = 0;
        }
    }
    ratio = MathFixedDivide(3, 2);
    D_800A353C_b[-1] = ratio;
    D_800A3758_c[-2] = ratio;
    D_800A3574_b[1] = D_800AE99C_nm;
    func_800323F0(4, -1);
    func_80032494(D_800AE99C_nm);
    func_8001DFC8();
}

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

INCLUDE_ASM("asm/nonmatchings/objects", func_8002DDD8);

void func_8002E228(void) {
}

void func_8002E230(void) {
    volatile s32 debugBuffer[16];
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002E240);

INCLUDE_ASM("asm/nonmatchings/objects", func_8002E594);

INCLUDE_ASM("asm/nonmatchings/objects", func_8002E9AC);

extern s32 D_800A2EC8Small;
extern u8 *D_800A3878;
extern void func_8002E9AC(s32 arg0);

void func_8002EE88(void) {
    u8 *node;

    node = D_800A3878;
    if (D_800A2EC8Small != 0) {
        while (node != 0) {
            func_8002E9AC((s32)node);
            node = *(u8 **)(node + 0x3E0);
        }
    } else if (node != 0) {
        do {
            func_8002E9AC((s32)node);
            node = *(u8 **)(node + 0x3E0);
        } while (node != 0);
    }
}

extern s32 D_800A38AC[];
extern u8 *D_800A3878;
extern u8 D_800A2ED8;

void func_8002EEFC(u8 *arg0) {
    s32 refX;
    s32 refY;
    s32 refZ;
    s32 level;
    s32 lod;
    u8 *node;
    s32 dist;
    s32 delta;
    s32 ySq;
    s32 zSq;

    refX = *(s32 *)((u8 *)D_800A38AC[0] + 0x0);
    refY = *(s32 *)((u8 *)D_800A38AC[0] + 0x4);
    refZ = *(s32 *)((u8 *)D_800A38AC[0] + 0x8);
    node = D_800A3878;
    if (node == NULL) {
        return;
    }
    level = 4;
    do {
        if (node == arg0 && *(s16 *)(node + 0x1EC) == 0 && D_800A2ED8 == 0 &&
            *(s8 *)(node + 0x20C) == 0) {
            *(u8 *)(node + 0x374) = level;
            *(u32 *)(node + 0x36C) = *(u32 *)(node + 0x370) + 0x110;
        } else {
            delta = *(s32 *)(node + 0x0);
            dist = delta - refX;
            dist = dist * dist;
            delta = *(s32 *)(node + 0x4);
            delta = delta - refY;
            ySq = delta * delta;
            delta = *(s32 *)(node + 0x8);
            delta = delta - refZ;
            zSq = delta * delta;
            dist = dist + ySq;
            dist = MathSqrt(dist + zSq);
            if (dist < 0x7D0) {
                *(u8 *)(node + 0x374) = 0;
            } else if (dist < 0x1770) {
                *(u8 *)(node + 0x374) = 1;
            } else if (dist < 0x2EE0) {
                *(u8 *)(node + 0x374) = 2;
            } else {
                *(u8 *)(node + 0x374) = 3;
            }
            if (D_800A2ED8 != 0) {
                if (*(s8 *)(node + 0x374) < 3) {
                    (*(s8 *)(node + 0x374))++;
                }
            }
            if (*(s8 *)(node + 0x200) == level) {
                *(u8 *)(node + 0x374) = 0;
            }
            if (node == arg0) {
                *(u8 *)(node + 0x374) = 0;
            }
            lod = *(s8 *)(node + 0x374);
            *(u32 *)(node + 0x36C) = *(u32 *)(node + 0x370) + (lod * 0x44);
        }
        node = *(u8 **)(node + 0x3E0);
    } while (node != NULL);
}

extern void *D_800A2EA0Small;
extern u8 D_800A2ED8;
extern s32 D_800A2EC4;
extern s32 D_800A38AC[];
extern s32 D_800A37C4Absolute[];
extern s32 D_800A37B4Absolute[];
extern s32 D_800A37ACAbsolute[];
extern s32 D_800A37A4Absolute[];
void func_8002F0A8(u8 *arg0) {
    s32 local[8];
    u8 *owner;

    D_800A2EA0Small = arg0;
    owner = (u8 *)D_800A38AC[0];
    if (arg0 != owner) {
        *(u16 *)(owner + 0x1E0) = *(u16 *)(arg0 + 0x1E0);
    } else {
        *(u16 *)((u8 *)D_800A38AC[0] + 0x1E0) = func_8002482C(
            *(s32 *)(arg0 + 0), *(s32 *)(arg0 + 4), (s32 *)(arg0 + 0x1F8));
    }
    func_8002DA30((s32 *)D_800A38AC[0]);
    if (D_800A2ED8 != 0) {
        CameraUpdateForCar((RaceObject *)D_800A37C4Absolute[0x3A],
                           (RaceObject *)arg0, D_800A2EC4 + 4);
    } else {
        CameraUpdateForCar((RaceObject *)D_800A37B4Absolute[0x3E],
                           (RaceObject *)arg0, *(s8 *)(arg0 + 0x20C));
    }
    func_8001EC38((s32 *)D_800A37ACAbsolute[0x40]);
    MatrixBuildRotationFromTransform((s32 *)D_800A37A4Absolute[0x42],
                                     (s32 *)local);
    local[7] = 0;
    local[6] = 0;
    local[5] = 0;
    SetTransMatrix((MATRIX *)local);
    SetRotMatrix((MATRIX *)local);
    func_8002EEFC(arg0);
}

extern u8 D_800A2F9DAbsolute[];
extern s32 D_800A2EACSmall;
extern u8 *D_800A3878;
void func_8002F1A0(void) {
    u8 *node;

    if (((u8 *)D_800A2F9DAbsolute)[-0x45] != 0) {
        func_8003A440();
        func_80028FCC(D_800A3878);
        return;
    }
    if (D_800A2EACSmall != 0) {
        func_8003A54C();
        func_80028FCC(D_800A3878);
        return;
    }
    func_80041AF0(0);
    if ((func_80050D1C() & 0xFF) == 0) {
        node = D_800A3878;
        if (node != NULL) {
            do {
                func_8003CF0C(node);
                ((void (*)(void *)) * (s32 *)(node + 0x350))(node);
                node = *(u8 **)(node + 0x3E0);
            } while (node != NULL);
        }
        func_80028FCC(D_800A3878);
    }
    func_80039CF4();
    node = D_800A3878;
    if (node != NULL) {
        do {
            if (*(s16 *)(node + 0x1EC) == 0) {
                func_800297D0(node);
            } else if ((*(u16 *)(node + 0x3A4) & 0xF) == 0) {
                func_80038D78(node);
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != NULL);
    }
}

extern u8 D_800A3068[];
extern u8 D_800A3069[];
extern s8 D_800A3860S8[] asm("D_800A3860");
extern s8 D_800A3861[];
extern s8 D_800A3862[];
extern s8 D_800A3863[];
extern s32 D_800A2E7C[];
extern s32 D_800A2E80[];
extern void func_80028754(u8 *, s32);
extern void func_8002D3EC(u8 *);

void func_8002F2CC(void) {
    u8 *node;
    u8 *tableBase;
    s32 carIdx;
    s32 val;

    node = D_800A3878;
    tableBase = (u8 *)0x80011E04;
    if (node != NULL) {
        do {
            if (*(s16 *)(node + 0x1EC) == 0) {
                carIdx = *(s8 *)(node + 0x20B);
                node[0xF6] = D_800A3068[carIdx * 2] < 1;
                node[0xF7] = D_800A3069[carIdx * 2];
                val = D_800A3862[carIdx * 4];
                *(s16 *)(node + 0x2A0) = (val - 0x40) / 4;
                val = D_800A3861[carIdx * 4];
                *(s16 *)(node + 0x2A6) = (val - 0x40) / 4;
                *(s16 *)(node + 0x112) =
                    *(u16 *)(tableBase + carIdx * 22 + 0x14);
                val = D_800A3863[carIdx * 4];
                func_80028754(node, 9 - val * 10 / 64);
                val = D_800A3860S8[carIdx * 4];
                if (val == 0x3F) {
                    *(s32 *)(node + 0x234) = D_800A2E7C[0];
                } else {
                    *(s32 *)(node + 0x234) = D_800A2E80[0];
                }
                func_8002D3EC(node);
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != NULL);
    }
    func_8002A954();
}

extern u8 D_800A2EDA;
extern s32 D_800A2EB0;
extern u8 *D_800A3878;
extern u8 D_800A3860[][4];
void func_8002F454(void) {
    s32 red;
    u8 *node;
    s32 green;
    s32 carIdx;

    node = D_800A3878;
    if (D_800A2EDA != 0) {
        return;
    }
    if (node != NULL) {
        do {
            if (*(s16 *)(node + 0x1EC) == 0) {
                carIdx = *(s8 *)(node + 0x20B);
                red = 0x20;
                if (D_800A2EB0 >= 0) {
                    red = (*(s16 *)(node + 0x2A0) << 2) + 0x40;
                    green = (*(s16 *)(node + 0x2A6) << 2) + 0x40;
                    if (red < 0) {
                        red = 0;
                    }
                    if (red >= 0x40) {
                        red = 0x3F;
                    }
                    if (green < 0) {
                        green = 0;
                    }
                    if (green >= 0x40) {
                        green = 0x3F;
                    }
                } else {
                    green = 0x20;
                }
                D_800A3860[carIdx][1] = green;
                D_800A3860[carIdx][2] = red;
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != NULL);
    }
}

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

void func_8002F5F4(void) {
    extern s32 D_800A2E9CSmall;
    s32 node;
    s32 f;
    s32 temp;

    node = D_800A2E9CSmall;
    node = *(s32 *)(node + 0x3E0);
    D_800A2E9CSmall = node;
    if (node != 0 && *(s32 *)(node + 0x350) != (s32)func_80029E34) {
        return;
    }
    node = D_800A3878;
    temp = *(s32 *)(node + 0x350);
    f = (s32)func_80029E34;
    D_800A2E9CSmall = node;
    if (temp != f) {
        return;
    }
    do {
        node = D_800A2E9CSmall;
        node = *(s32 *)(node + 0x3E0);
        temp = *(s32 *)(node + 0x350);
        D_800A2E9CSmall = node;
    } while (temp == f);
}

void func_8002F66C(void) {
}

void func_8002F674(void) {
    extern s32 D_800A2EC4;
    extern s32 D_800A2E9CSmall;
    extern s32 D_800A2F14;
    extern s32 D_800A2F18;
    extern s32 D_800A2F1C;
    extern s32 D_800A2F20;
    extern s32 D_800A2F24;
    extern u8 *D_800A3554[];
    extern s32 D_800A3558[];
    extern s32 D_800A35E0[];
    extern u32 RandomGetScaled16(s32);
    s32 value;
    s32 r;

    switch (D_800A2EC4) {
    case 0:
        break;
    case 1:
        D_800A2E9CSmall = (s32)D_800A3554[0];
        break;
    case 2:
        D_800A2E9CSmall = (s32)D_800A3554[0];
        break;
    case 3:
        if (D_800A2F14 != 0) {
            D_800A2F24 = 4;
            D_800A2F1C = 0;
            D_800A2F20 = 0;
            *(u8 *)(D_800A3558[0] + 0x20C) = 4;
            D_800A2F14 = 0;
            D_800A2F18 = 100;
        } else {
            D_800A2F20 += 1;
            D_800A2F1C += 1;
            if (D_800A2F18 > 0) {
                D_800A2F18 -= 1;
            }
            if (D_800A2F20 > 100) {
                value = *(s32 *)(D_800A2E9CSmall + 0x3E0);
                D_800A2F20 = 0;
                D_800A2E9CSmall = value;
                if (value == 0) {
                    D_800A2E9CSmall = (s32)D_800A3554[0];
                }
                *(u8 *)(D_800A3558[0] + 0x20C) = D_800A2F24;
                r = RandomGetScaled16(4);
                if (r < 0) {
                    r = -RandomGetScaled16(4);
                } else {
                    r = RandomGetScaled16(4);
                }
                switch (r) {
                case 0:
                    D_800A2F24 = 11;
                    *(u8 *)(D_800A3558[0] + 0x20C) = 11;
                    break;
                case 1:
                    D_800A2F24 = 4;
                    *(u8 *)(D_800A3558[0] + 0x20C) = 4;
                    break;
                case 2:
                    D_800A2F24 = 4;
                    *(u8 *)(D_800A3558[0] + 0x20C) = 4;
                    break;
                case 3:
                    D_800A2F24 = 6;
                    *(u8 *)(D_800A3558[0] + 0x20C) = 6;
                    break;
                }
            }
        }
        break;
    case 4:
        D_800A2E9CSmall = (s32)D_800A35E0[0];
        break;
    }
    if (D_800A2E9CSmall == 0) {
        D_800A2E9CSmall = (s32)D_800A3554[0];
    }
}

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

INCLUDE_ASM("asm/nonmatchings/objects", func_8002F910);

INCLUDE_ASM("asm/nonmatchings/objects", func_8002FFB8);

INCLUDE_ASM("asm/nonmatchings/objects", func_80030204);

extern s32 D_800A3A80;
#ifdef NON_MATCHING
/* Retry 2026-10-11: 768 bytes, 33 bytes differ. Point/pair allocation and
 * quotient temporaries remain different. Keep the assembly fallback. */
s32 func_800309DC(s32 arg0, s32 *object, s32 *query) {
    SVECTOR **points;
    SVECTOR *pairB;
    SVECTOR *pairA;
    SVECTOR *pointA;
    SVECTOR *pointB;
    SVECTOR *point;
    s32 sampleX;
    s32 sampleY;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 z0;
    s32 z1;
    s32 left;
    s32 right;
    s32 leftHeight;
    s32 result;
    int heightSpan;
    s32 i;
    sampleX = query[0];
    sampleY = query[1];
    pairA = 0;
    points = (SVECTOR **)(object + 6);
    for (i = 4; i > 0; i--) {
        pointA = points[i & 3];
        pointB = points[i - 1];
        if (pointB->vy < pointA->vy) {
            point = pointA;
            pointA = pointB;
            pointB = point;
        }
        if (sampleY < pointA->vy) {
            continue;
        }
        if (sampleY >= pointB->vy) {
            continue;
        }
        if (pointA->vy == pointB->vy) {
            continue;
        }
        if (pairA == 0) {
            pairA = pointA;
            pairB = pointB;
            continue;
        }
        x0 = pairA->vx;
        x1 = pairB->vx;
        y0 = pairA->vy;
        y1 = pairB->vy;
        if (y1 == y0) {
            left = x0;
        } else {
            left = x0 + (((x1 - x0) * (sampleY - y0)) / (y1 - y0));
        }
        x0 = pointA->vx;
        x1 = pointB->vx;
        y0 = pointA->vy;
        y1 = pointB->vy;
        if (y1 == y0) {
            right = x0;
        } else {
            right = x0 + (((x1 - x0) * (sampleY - y0)) / (y1 - y0));
        }
        if (right < left) {
            result = left;
            left = right;
            right = result;
            point = pairA;
            pairA = pointA;
            pointA = point;
            point = pairB;
            pairB = pointB;
            pointB = point;
        }
        if (sampleX < (left - 5)) {
            return 0;
        }
        if ((right + 5) < sampleX) {
            return 0;
        }
        z0 = pairA->vz;
        z1 = pairB->vz;
        y0 = pairA->vy;
        y1 = pairB->vy;
        if (y1 == y0) {
            leftHeight = z0;
        } else {
            heightSpan = y1 - y0;
            leftHeight = sampleY;
            leftHeight = z0 + (((z1 - z0) * (leftHeight - y0)) / heightSpan);
        }
        z1 = pointB->vz;
        y0 = pointA->vy;
        z0 = pointA->vz;
        y1 = pointB->vy;
        if (y1 == y0) {
            result = z0;
        } else {
            result = (z1 - z0) * (sampleY - y0);
            result = z0 + (result / (y1 - y0));
        }
        if (right == left) {
            result = leftHeight;
        } else {
            result = leftHeight + (((result - leftHeight) * (sampleX - left)) /
                                   (right - left));
        }
        query[2] = result;
        D_800A3A80 = object;
        return 1;
    }

    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/objects", func_800309DC);
#endif

extern s32 D_800A38AC[];
extern s32 D_800BE980[];
s32 func_800309DC(s32, s32 *, s32 *);
void func_80030CDC(s32 *query, s32 index) {
    s8 *node;
    u8 *entries;

    if (index >= 0) {
        entries = (u8 *)D_800BE980[0];
        entries += index * 0x90;
        node = *(s8 **)(entries + 0x20);
        while ((node != NULL) && (((u8)node[0x13] & 0x80) == 0)) {
            if ((node[2] < 0) &&
                ((func_800309DC(D_800A38AC[0], (s32 *)node, query) & 0xFF) !=
                 0)) {
                return;
            }
            node = *(s8 **)(node + 0x28);
        }
    }
}

extern s32 D_800A3A80;
/* The D_800A3A80 store sits before the second unk1E0 read so cse reloads it.
 * Struct-typed reads (unk1E0, unk20) carry no dependence on that store, so
 * sched sinks it below the unk20 load as retail does. */
void func_80030D80(RaceObject *object, s32 *query) {
    s8 *node;
    u8 *entry;
    s16 rot;

    rot = object->unk1E0;
    if (rot >= 0) {
        D_800A3A80 = 0;
        entry = object->unk1E0 * 0x90 + (u8 *)D_800BE980[0];
        node = (s8 *)((TrackRacer *)entry)->unk20;
        while ((node != NULL) && (((u8)node[0x13] & 0x80) == 0)) {
            if ((node[2] < 0) &&
                ((func_800309DC((s32 *)object, (s32 *)node, query) & 0xFF) !=
                 0)) {
                return;
            }
            node = *(s8 **)(node + 0x28);
        }
        entry = *(u8 **)(entry + 0);
        object->unk1E0 = *(u16 *)(entry + 8);
        node = *(s8 **)(entry + 0x20);
        while ((node != NULL) && (((u8)node[0x13] & 0x80) == 0)) {
            if ((node[2] < 0) &&
                ((func_800309DC((s32 *)object, (s32 *)node, query) & 0xFF) !=
                 0)) {
                return;
            }
            node = *(s8 **)(node + 0x28);
        }
        entry = *(u8 **)(*(u8 **)(entry + 4) + 4);
        object->unk1E0 = *(u16 *)(entry + 8);
        node = *(s8 **)(entry + 0x20);
        while ((node != NULL) && (((u8)node[0x13] & 0x80) == 0)) {
            if ((node[2] < 0) &&
                ((func_800309DC((s32 *)object, (s32 *)node, query) & 0xFF) !=
                 0)) {
                return;
            }
            node = *(s8 **)(node + 0x28);
        }
    }
}

extern s32 D_800A2F2C;
extern s32 D_800A2F2CAbsolute[];
extern s32 D_800A384CAbsolute[];
extern u8 *D_800A3854Absolute[];
extern s32 D_800AE844[];
extern s32 D_800AE848[];
extern s32 D_800AE84C[];
extern s32 D_800B6094[];
u16 func_80030F24(u8 *object, s32 *pointArray, s32 arg2, s32 arg3, s32 arg4) {
    s32 point[3];
    s32 outX;
    s32 outZ;
    s16 *tableA;
    s16 *tableB;
    s32 offset;
    s32 value;
    s16 result16;

    offset =
        (*(s16 *)(object + 0x116) + *(s16 *)(object + 0x118) + 0x1000) & 0xFFF;
    tableA = (s16 *)D_800A384CAbsolute[0];
    tableB = (s16 *)D_800A3854Absolute[0];
    pointArray[0] +=
        ((tableA[offset] * arg2 - tableB[offset] * arg3) >> 16) * 4;
    pointArray[1] +=
        ((tableB[offset] * arg2 + tableA[offset] * arg3) >> 16) * 4;
    pointArray[2] = 0;
    if (*(s16 *)(object + 0x1EC) == 0) {
        if (D_800A2F2C > 0) {
            D_800A2F2C = D_800A2F2C - 1;
        }
    }
    *(s16 *)(object + 0x1E0) = func_80024E90(pointArray[0], pointArray[1],
                                             D_800A2F2CAbsolute, &outX, &outZ);
    *(Vec3 *)(object + 0xDC) = *(Vec3 *)D_800B6094;
    result16 = *(s16 *)(object + 0x1E0);
    if (result16 == -1) {
        *(u8 *)(object + 0xF5) = 1;
        return 0;
    }
    *(s32 *)(object + 0x1F8) = result16;
    if ((*(s16 *)(object + 0x1EC) == 0) && (outZ == 2)) {
        point[0] = pointArray[0] / 4 - D_800AE844[0];
        point[1] = pointArray[1] / 4 - D_800AE848[0];
        func_80030D80((RaceObject *)object, point);
        pointArray[2] = (point[2] + D_800AE84C[0]) * 4;
        if (D_800A3A80 == 0 || (*(u8 *)((u8 *)D_800A3A80 + 0x13) & 8) == 0) {
            value = 5;
        } else {
            value = 2;
        }
        *(s16 *)(object + 0x360) = value;
        if (D_800A3A80 == 0) {
            pointArray[2] = outX * 4;
        }
    } else {
        pointArray[2] = outX * 4;
        *(s16 *)(object + 0x360) = outZ;
    }
    if (*(s16 *)(object + 0x1E0) < *(s16 *)(object + 0x1E2)) {
        *(s16 *)(object + 0x1E2) = *(s16 *)(object + 0x1E0);
    }
    if (*(s16 *)(object + 0x1E4) < *(s16 *)(object + 0x1E0)) {
        *(s16 *)(object + 0x1E4) = *(s16 *)(object + 0x1E0);
    }
    return *(u16 *)(object + 0x360);
}

void func_800311B4(s32 x, s32 y, s32 z, s32 *out) {
    s32 length;

    length = MathSqrt(x * x + y * y + z * z);
    if (length == 0) {
        length = 1;
    }
    out[0] = MathFixedDivide(x, length);
    out[1] = MathFixedDivide(y, length);
    out[2] = MathFixedDivide(z, length);
}

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vector3;

extern s32 D_800A2F2C;
extern s32 D_800A397C[];
void func_800319D4(u8 *, s32);
void func_8001F198(void);
u16 func_80030F24(u8 *, s32 *, s32, s32, s32);
extern s16 func_8002482Cs16(s32, s32, void *) asm("func_8002482C");
void func_8001F5BC(s32, s32, s32);
typedef struct {
    u8 pad[0x1C];
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
} ObjectBounds;

void func_80031264(u8 *object) {
    s32 corners[5][4];
    s32 normals[3][4];
    ObjectBounds *state;
    s32 length;
    s32 sum;
    s32 result;
    s32 i;
    s32 a;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
    s32 sum4;
    s32 crossX;
    s32 crossY;
    s32 crossZ;

    state = *(ObjectBounds **)(object + 0x370);
    if (*(s16 *)(object + 0x1EC) != 0) {
        func_800319D4(object, 0);
        return;
    }
    corners[0][0] = corners[1][0] = corners[2][0] = corners[3][0] =
        corners[4][0] = *(s32 *)(object + 0x0);
    corners[0][1] = corners[1][1] = corners[2][1] = corners[3][1] =
        corners[4][1] = *(s32 *)(object + 0x4);
    corners[0][2] = corners[1][2] = corners[2][2] = corners[3][2] =
        corners[4][2] = *(s32 *)(object + 0x8);
    *(Vector3 *)(object + 0x3C) = *(Vector3 *)(object + 0x18);
    *(Vector3 *)(object + 0x48) = *(Vector3 *)(object + 0x24);
    *(Vector3 *)(object + 0x54) = *(Vector3 *)(object + 0x30);
    func_8001EEC4((s32 *)object);
    func_8001F198();
    *(s16 *)(object + 0x1E2) = 0x7D00;
    *(s16 *)(object + 0x1E4) = -1;
    *(u8 *)(object + 0xF5) = 0;
    D_800A2F2C = *(s32 *)(object + 0x1F8);
    *(s16 *)(object + 0x362) =
        func_80030F24(object, corners[3], state->unk1E, state->unk22, 0);
    *(s16 *)(object + 0x364) =
        func_80030F24(object, corners[0], state->unk1E, state->unk20, 0);
    *(s16 *)(object + 0x366) =
        func_80030F24(object, corners[2], state->unk1C, state->unk22, 0);
    *(s16 *)(object + 0x368) =
        func_80030F24(object, corners[1], state->unk1C, state->unk20, 0);
    *(s16 *)(object + 0x1E0) = func_8002482Cs16(
        *(s32 *)(object + 0x0), *(s32 *)(object + 0x4), object + 0x1F8);
    if (*(u16 *)(object + 0x362) == 0) {
        corners[3][2] = *(s32 *)(object + 0x8);
    }
    if (*(u16 *)(object + 0x364) == 0) {
        corners[0][2] = *(s32 *)(object + 0x8);
    }
    if (*(u16 *)(object + 0x366) == 0) {
        corners[2][2] = *(s32 *)(object + 0x8);
    }
    if (*(u16 *)(object + 0x368) == 0) {
        corners[1][2] = *(s32 *)(object + 0x8);
    }
    *(s32 *)(object + 0x318) = corners[3][2];
    *(s32 *)(object + 0x340) = corners[0][2];
    *(s32 *)(object + 0x2C8) = corners[2][2];
    *(s32 *)(object + 0x2F0) = corners[1][2];
    sum = corners[0][2] + corners[1][2] + corners[2][2] + corners[3][2];
    if (sum < 0) {
        sum += 3;
    }
    sum4 = sum >> 2;
    if ((*(s16 *)(object + 0x1BC) == 0) || (D_800A397C[0] == 2)) {
        corners[0][2] += *(s16 *)(object + 0x324);
        corners[1][2] += *(s16 *)(object + 0x2D4);
        corners[2][2] += *(s16 *)(object + 0x2AC);
        corners[3][2] += *(s16 *)(object + 0x2FC);
        result = *(s16 *)(object + 0x324) + *(s16 *)(object + 0x2D4) +
                 *(s16 *)(object + 0x2AC) + *(s16 *)(object + 0x2FC);
        if (result < 0) {
            result += 3;
        }
        result >>= 2;
        *(s16 *)(object + 0xFE) = result;
    } else {
        for (i = 0; i < 4; i++) {
            *(u16 *)(object + i * 0x28 + 0x2AC) = *(u16 *)(object + 0x39A);
        }
        *(s16 *)(object + 0xFE) = *(u16 *)(object + 0x39A);
    }
    *(s32 *)(object + 0x8) = *(s16 *)(object + 0xFE) + sum4;
    *(s16 *)(object + 0x1E8) = *(u16 *)(object + 0x1E4);
    *(s16 *)(object + 0x1E6) = *(u16 *)(object + 0x1E2);
    c = corners[2][1] - corners[1][1];
    sum4 = corners[2][2] - corners[1][2];
    a = corners[0][1] - corners[1][1];
    d = corners[0][2] - corners[1][2];
    e = corners[2][0] - corners[1][0];
    f = corners[0][0] - corners[1][0];
    a >>= 2;
    sum4 >>= 2;
    c >>= 2;
    d >>= 2;
    e >>= 2;
    f >>= 2;
    crossX = a * sum4 - d * c;
    crossY = d * e - f * sum4;
    crossZ = f * c - a * e;
    length = MathSqrt(crossX * crossX + crossY * crossY + crossZ * crossZ);
    if (length == 0) {
        length = 1;
    }
    normals[2][0] = MathFixedDivide(crossX, length);
    normals[2][1] = MathFixedDivide(crossY, length);
    normals[2][2] = MathFixedDivide(crossZ, length);
    length = MathSqrt(f * f + a * a + d * d);
    if (length == 0) {
        length = 1;
    }
    normals[0][0] = MathFixedDivide(f, length);
    normals[0][1] = MathFixedDivide(a, length);
    normals[0][2] = MathFixedDivide(d, length);
    length = MathSqrt(e * e + c * c + sum4 * sum4);
    if (length == 0) {
        length = 1;
    }
    normals[1][0] = MathFixedDivide(e, length);
    normals[1][1] = MathFixedDivide(c, length);
    normals[1][2] = MathFixedDivide(sum4, length);
    *(Vector3 *)(object + 0x3C) = *(Vector3 *)normals[0];
    *(Vector3 *)(object + 0x48) = *(Vector3 *)normals[1];
    *(Vector3 *)(object + 0x54) = *(Vector3 *)normals[2];
    func_8001F5BC(0, (0x3FF - *(s16 *)(object + 0x38A)) & 0x3FF,
                  *(u16 *)(object + 0x388) & 0x3FF);
    func_8001EC38((s32 *)object);
    MatrixCombineState();
    func_8001F8C0((s32 *)object);
}

void OuterProduct0(s32 *, s32 *, s32 *);
void VectorNormal(s32 *, s32 *, s32);
void func_80031874(u8 *quad, s32 *normal) {
    s32 vecA[3];
    s32 vecB[3];
    s32 cross[3];
    s32 crossX;
    s32 crossY;
    s32 crossZ;
    u8 *back;

    if ((quad == NULL) || ((*(u8 *)(quad + 0x13) & 0x20) != 0)) {
        normal[0] = 0;
        normal[1] = 0;
        normal[2] = 0x10000;
        return;
    }
    back = quad + 0x1C;
    vecA[0] = *(s16 *)(*(u8 **)(quad + 0x20) + 0) - *(s16 *)(*(u8 **)back + 0);
    vecA[1] = *(s16 *)(*(u8 **)(quad + 0x20) + 2) - *(s16 *)(*(u8 **)back + 2);
    vecA[2] = *(s16 *)(*(u8 **)(quad + 0x20) + 4) - *(s16 *)(*(u8 **)back + 4);
    vecB[0] = *(s16 *)(*(u8 **)(quad + 0x18) + 0) - *(s16 *)(*(u8 **)back + 0);
    vecB[1] = *(s16 *)(*(u8 **)(quad + 0x18) + 2) - *(s16 *)(*(u8 **)back + 2);
    vecB[2] = *(s16 *)(*(u8 **)(quad + 0x18) + 4) - *(s16 *)(*(u8 **)back + 4);
    OuterProduct0(vecA, vecB, cross);
    crossX = cross[0];
    crossY = cross[1];
    crossZ = cross[2];
    cross[0] = (crossX >>= 6);
    cross[1] = (crossY >>= 6);
    cross[2] = (crossZ >>= 6);
    VectorNormal(cross, normal, crossZ);
    normal[0] = normal[0] * 0x10;
    normal[1] = normal[1] * 0x10;
    normal[2] = normal[2] * 0x10;
}

/* VectorNormal reads two arguments here; a third one changes the load order
 * before its call. The three-axis copies at the end are Vector3 assignments. */
extern s32 D_800A2F2C;
extern void VectorNormal2(s32 *, s32 *) asm("VectorNormal");
void func_800319D4(u8 *object, s32 arg1) {
    s32 corners[5][4];
    s32 vecA[3];
    s32 cross[3];
    s32 normalOut[3];
    s32 temp1;
    s32 temp2;
    s32 index;
    s32 sum;
    s32 sum4;
    s32 value;
    u16 result;

    value = *(s32 *)(object + 0x0);
    corners[4][0] = value;
    corners[3][0] = value;
    corners[2][0] = value;
    corners[1][0] = value;
    corners[0][0] = value;
    value = *(s32 *)(object + 0x4);
    corners[4][1] = value;
    corners[3][1] = value;
    corners[2][1] = value;
    corners[1][1] = value;
    corners[0][1] = value;
    value = *(s32 *)(object + 0x8);
    corners[4][2] = value;
    corners[3][2] = value;
    corners[2][2] = value;
    corners[1][2] = value;
    corners[0][2] = value;
    *(Vector3 *)(object + 0x3C) = *(Vector3 *)(object + 0x18);
    *(Vector3 *)(object + 0x48) = *(Vector3 *)(object + 0x24);
    *(Vector3 *)(object + 0x54) = *(Vector3 *)(object + 0x30);
    func_8001EEC4((s32 *)object);
    func_8001F198();
    *(u8 *)(object + 0xF5) = 0;
    *(s16 *)(object + 0x116) = *(s16 *)(object + 0x114) * 4;
    if (arg1 == 0) {
        *(s16 *)(object + 0x1E2) = 0x7D00;
        *(s16 *)(object + 0x1E4) = -1;
        D_800A2F2C = *(s32 *)(object + 0x1F8);
        result = func_80030F24(object, corners[3], 0, 0, 0);
        *(s16 *)(object + 0x362) = result;
        *(s16 *)(object + 0x364) = result;
        *(s16 *)(object + 0x366) = *(u16 *)(object + 0x362);
        *(s16 *)(object + 0x368) = *(u16 *)(object + 0x362);
    }
    vecA[0] = *(s32 *)(object + 0xDC);
    vecA[1] = *(s32 *)(object + 0xE0);
    index = *(s16 *)(object + 0x114) * 4;
    temp1 = (*(s32 *)(index + (u32)D_800A3A2CAbsolute[0]) << 8) >> 16;
    temp2 = (*(s32 *)(index + (u32)D_800A3A34Absolute[0]) << 8) >> 16;
    corners[0][0] = temp1;
    corners[1][1] = temp1;
    corners[0][1] = temp2;
    corners[1][0] = -temp2;
    corners[0][2] = -((vecA[0] * temp1 + vecA[1] * temp2) >> 16);
    corners[1][2] = -((vecA[0] * -temp2 + vecA[1] * temp1) >> 16);
    if (arg1 == 0) {
        corners[0][2] += *(s16 *)(object + 0x324) - *(s16 *)(object + 0x2D4);
        corners[1][2] += *(s16 *)(object + 0x2AC) - *(s16 *)(object + 0x2D4);
        sum = *(s16 *)(object + 0x324) + *(s16 *)(object + 0x2D4) +
              *(s16 *)(object + 0x2AC) + *(s16 *)(object + 0x2FC);
        sum4 = sum / 4;
        *(s16 *)(object + 0x1BE) = sum4;
        *(s32 *)(object + 0x8) = corners[3][2] + (s16)sum4;
        *(s16 *)(object + 0x1E8) = *(u16 *)(object + 0x1E4);
        *(s16 *)(object + 0x1E6) = *(u16 *)(object + 0x1E2);
    } else {
        *(s16 *)(object + 0x1E4) = -1;
        *(s16 *)(object + 0x1E2) = -1;
    }
    OuterProduct0(corners[0], corners[1], cross);
    cross[0] >>= 6;
    cross[1] >>= 6;
    cross[2] >>= 6;
    VectorNormal2(cross, normalOut);
    normalOut[0] = normalOut[0] * 16;
    normalOut[1] = normalOut[1] * 16;
    normalOut[2] = normalOut[2] * 16;
    VectorNormal2(corners[0], vecA);
    VectorNormal2(corners[1], cross);
    vecA[0] = vecA[0] * 16;
    vecA[1] = vecA[1] * 16;
    vecA[2] = vecA[2] * 16;
    cross[0] = cross[0] * 16;
    cross[1] = cross[1] * 16;
    cross[2] = cross[2] * 16;
    *(Vector3 *)(object + 0x3C) = *(Vector3 *)vecA;
    *(Vector3 *)(object + 0x48) = *(Vector3 *)cross;
    *(Vector3 *)(object + 0x54) = *(Vector3 *)normalOut;
}
extern s32 D_800A3574Lui asm("D_800A3574Absolute");

INCLUDE_ASM("asm/nonmatchings/objects", func_80031D74);

extern s32 FileOpenCall32328(s32, void *) asm("FileOpen");
extern s32 FileSeekCall32328(void *, s32, s32) asm("FileSeek");
extern void FileReadCall32328(s32, s32, s32, s32) asm("FileRead");
extern void FileCloseCall32328(s32) asm("FileClose");
extern void func_80025454(s32);
extern void func_80031D74(s32, s32, s32);
extern char D_8008D08C[];
extern void *D_800A2F34[];
extern s32 D_800A3574[];
extern u8 D_800A2D4C[], D_800A2D4D[];
extern s32 D_800A36D0Absolute[];
void func_80032328(s32 arg0) {
    s32 value;
    s32 handle;

    handle = FileOpenCall32328(arg0, D_800A2F34);
    if (handle == 0) {
        SystemShowFatalError(D_8008D08C);
    }
    value = FileSeekCall32328(handle, 0, 2);
    FileSeekCall32328(handle, 0, 0);
    FileReadCall32328(STACK_BLOCK_801C0000, value, 1, handle);
    func_80031D74(D_800A3574Lui, STACK_BLOCK_801C0000, -1);
    D_800A2D4C[0] = 1;
    func_80025454(D_800A3574Lui);
    D_800A2D4D[0] = 0;
    FileCloseCall32328(handle);
}

INCLUDE_RODATA("asm/nonmatchings/objects", D_8008D08C);

/*
 * The second D_800A3574 read goes through the D_800A36D0Absolute
 * neighbor ((s32 *)0x800A36D0)[-87] so gcc cannot CSE the address
 * materialization across the first call; the -87*4 delta folds into
 * the %lo displacement (0x36D0 - 0x15C = 0x3574).
 */
extern s32 D_800A3574[];
extern s32 D_800B9F44[];
extern u8 D_800A2D4C[], D_800A2D4D[];
extern s32 D_800A36D0Absolute[];
void func_80025454(s32);
void func_80031D74(s32, s32, s32);
void func_800323F0(s32 index, s32 arg1) {
    func_80031D74(D_800A3574Lui, *(s32 **)(D_800B9F44 + index), arg1);
    D_800A2D4C[0] = 1;
    func_80025454(D_800A3574Lui);
    D_800A2D4D[0] = 0;
}

void func_80031D74(s32, s32, s32);
extern s32 D_800A3574[];
extern u8 D_800A2D4C[], D_800A2D4D[];
void func_80032450(s32 first, s32 second) {
    func_80031D74(D_800A3574[0], first, second);
    D_800A2D4C[0] = 1;
    D_800A2D4D[0] = 0;
}

void func_80032494(u8 *object) {
    u8 *node;

    node = *(u8 **)(object + 0x3C);
    if (node != NULL) {
        *(s32 *)(object + 0x34) = 0;
        do {
            if (*(s32 *)(node + 0x8) != 0) {
                *(s32 *)(*(s32 *)(node + 0xC) + 0x28) = *(s32 *)(object + 0x34);
                *(s32 *)(object + 0x34) = *(s32 *)(node + 0x8);
            }
            node = *(u8 **)(node + 0x4);
        } while (node != NULL);
    }
}

void GraphicsLinkPrimitive(u32 *orderingTable, u32 *primitive) {
    u32 old;
    u32 tag;
    old = *orderingTable;
    tag = *primitive;
    tag &= 0xFF000000;
    tag |= old & 0xFFFFFF;
    *primitive = tag;
    *orderingTable = (old & 0xFF000000) | ((u32)primitive & 0xFFFFFF);
}

void GraphicsAddTaggedPrimitive(u32 *orderingTable, u32 *primitive, u32 tag) {
    *primitive = tag | *orderingTable;
    *orderingTable = (u32)primitive & 0xFFFFFF;
}

extern u32 gPrimitiveCursor[];
extern s32 D_800A39C8[];
extern u8 D_800A2DE0[];
extern void SetPolyF4(u8 *prim);

u8 *func_80032544(u8 *obj, s32 count) {
    u8 *prim;
    u32 *ot;
    s32 gte;
    u32 *otEntry;

    ot = (u32 *)(D_800A39C8[0] + 0x20);
    prim = (u8 *)gPrimitiveCursor[0];
    while (count > 0) {
        gte_ldv3(*(s32 **)(obj + 0x18), *(s32 **)(obj + 0x1C),
                 *(s32 **)(obj + 0x20));
        gte_rtpt();
        SetPolyF4(prim);
        SetSemiTrans(prim, 1);
        gte_ReadFlag(gte);
        if (gte & 0x66000) {
            goto next;
        }
        gte_nclip();
        prim[4] = 16;
        prim[5] = 16;
        prim[6] = 16;
        gte_mfc2(gte, 24);
        if (D_800A2DE0[0] != 0) {
            if (gte >= 0) {
                goto draw;
            }
            goto next;
        } else if (gte > 0) {
            goto next;
        }
    draw:
        gte_avsz3();
        gte_mfc2(gte, 7);
        gte += *(s8 *)(obj + 1) * 4;
        gte_stsxy3(prim + 8, prim + 0xC, prim + 0x14);
        gte_ldv0(*(s32 **)(obj + 0x24));
        gte_rtps();
        gte_stsxy(prim + 0x10);
        otEntry = (u32 *)(((gte >> 4) << 2) + (s32)ot);
        *(u32 *)prim = *otEntry | 0x05000000;
        *otEntry = (u32)prim & 0xFFFFFF;
        prim += 0x18;
    next:
        count--;
        obj += 0x2C;
    }
    gPrimitiveCursor[0] = (u32)prim;
    prim = obj;
    return prim;
}

void func_8003271C(s32 arg0) {
    u32 i;
    u32 *pad;

    i = 0;
    pad = (u32 *)SCRATCHPAD_BASE;
    do {
        if (arg0 < 0) {
            pad[0] = 0;
        } else {
            pad[0] = (i << 0x10) | (i << 8) | i;
        }
        pad += 1;
        i += 1;
        arg0 += 1;
    } while (i < 0x100U);
}

/*
 * Handwritten-GTE textured triangle renderer: rtpt on three vertices,
 * backface cull on nclip gated by the D_800A2DE0 double-sided flag, then
 * link one primitive into the ordering table at D_800A39C8[0] + 0x20.
 */
u8 *func_80032760(u8 *obj, u8 *prim, s32 count) {
    u8 *ot;
    u32 doubleSided;
    s32 gte;
    s32 depthBias;
    u8 *nextPrim;
    u32 *otEntry;
    s32 flagMask;

    ot = (u8 *)D_800A39C8[0] + 0x20;
    doubleSided = D_800A2DE0[0];
    flagMask = 0x66000;
    while (count > 0) {
        gte_ldv3(*(s32 **)(obj + 0x18), *(s32 **)(obj + 0x1C),
                 *(s32 **)(obj + 0x20));
        gte_rtpt();
        depthBias = *(s8 *)(obj + 1) * 4;
        nextPrim = *(u8 **)(prim + 0x34);
        gte_ReadFlag(gte);
        if (gte & flagMask) {
            goto next;
        }
        gte_op(nclip);
        gte_mfc2_nonop(gte, 24);
        if (doubleSided != 0) {
            if (gte >= 0) {
                goto draw;
            }
            goto next;
        } else if (gte > 0) {
            goto next;
        }
    draw:
        gte_op(avsz3);
        gte_stsxy3(prim + 8, prim + 0x14, prim + 0x2C);
        gte_ldv0(*(s32 **)(obj + 0x24));
        gte_mfc2(gte, 7);
        gte = (gte + depthBias) >> 4;
        gte_op(rtps);
        otEntry = (u32 *)(gte * 4 + (s32)ot);
        *(u32 *)prim = *otEntry | 0x0C000000;
        *otEntry = (u32)prim & 0xFFFFFF;
        gte_stsxy(prim + 0x20);
    next:
        count--;
        obj += 0x2C;
        prim = nextPrim;
    }
    return obj;
}

extern u32 gPrimitiveCursor[];
extern s32 D_800A39C8[];
extern u8 D_800A2DE0[];

void func_800328AC(void *arg0, s32 arg1) {
    register s32 v0s asm("v0");
    u8 *ret;
    u8 *prim;
    u32 doublesided;
    u8 *spad;
    u32 flagMask;
    u32 codeConst;
    register u8 *ot asm("t7");
    register u8 *obj asm("a2");
    register u8 *prim20 asm("a3");
    s32 *vec0;
    s32 *vec1;
    s32 *vec2;
    s32 gteWord;
    register s32 w8 asm("v1");
    register s32 wC asm("t1");
    register s32 w10 asm("t0");
    register s32 w14 asm("a0");

    ret = arg0;
    asm("" : "=r"(ret) : "0"(ret));
    v0s = D_800A39C8[0];
    prim = (u8 *)gPrimitiveCursor[0];
    doublesided = D_800A2DE0[0];
    flagMask = 0x66000;
    asm("lui %0, 0x1F80" : "=r"(spad));
    asm volatile(".set\tnoreorder\n\t"
                 "blez %1, func_800328AC+0x1C0\n\t"
                 "addiu %0, %2, 0x20\n\t"
                 ".set\treorder"
                 : "=r"(ot)
                 : "r"(arg1), "r"(v0s));
    codeConst = 0x0C000000;
    obj = (u8 *)arg0 + 1;
    prim20 = prim + 0x20;
    do {
        vec0 = *(s32 **)(obj + 0x17);
        vec1 = *(s32 **)(obj + 0x1B);
        vec2 = *(s32 **)(obj + 0x1F);
        gte_ldv3(vec0, vec1, vec2);
        w8 = *(s32 *)(obj + 0x7);
        wC = *(s32 *)(obj + 0xB);
        gte_op(rtpt);
        w10 = *(s32 *)(obj + 0xF);
        w14 = *(s32 *)(obj + 0x13);
        *(s32 *)(prim20 - 0x14) = w8;
        *(s32 *)(prim20 - 0x8) = wC;
        *(s32 *)(prim20 + 0x4) = w10;
        *(s32 *)(prim20 + 0x10) = w14;
        gte_cfc2(gteWord, 31);
        v0s = gteWord & flagMask;
        if (v0s != 0) {
            goto incr;
        }
        gte_op(nclip);
        w8 = *(s32 *)(obj + 0x3);
        asm volatile("nop");
        wC = w8 & 0xFF;
        w8 >>= 8;
        w10 = w8 & 0xFF;
        w8 >>= 8;
        w14 = w8 & 0xFF;
        v0s = wC << 2;
        v0s = v0s + (s32)spad;
        wC = *(u32 *)v0s;
        v0s = w10 << 2;
        v0s = v0s + (s32)spad;
        w10 = *(u32 *)v0s;
        v0s = w14 << 2;
        v0s = v0s + (s32)spad;
        w14 = *(u32 *)v0s;
        v0s = (w8 >> 6) & 0x3FC;
        v0s = v0s + (s32)spad;
        w8 = *(u32 *)v0s;
        gte_mfc2_nonop(gteWord, 24);
        if (doublesided != 0) {
            if (gteWord >= 0) {
                goto ok;
            }
            goto incr;
        } else if (gteWord > 0) {
            goto incr;
        }
    ok:
        gte_op(avsz3);
        v0s = 0x3C000000;
        v0s = wC | v0s;
        *(u32 *)(prim20 + 0x8) = w14;
        *(u32 *)(prim20 - 0x4) = w8;
        *(u32 *)(prim20 - 0x1C) = v0s;
        *(u32 *)(prim20 - 0x10) = w10;
        gte_stsxy3(prim + 0x8, prim + 0x14, prim + 0x2C);
        vec0 = *(s32 **)(obj + 0x23);
        gte_ldv0(vec0);
        gte_mfc2_nonop(gteWord, 7);
        v0s = *(s8 *)obj;
        asm volatile("nop");
        gteWord = gteWord + v0s * 4;
        gte_op(rtps);
        w14 = gteWord >> 4;
        w14 = w14 << 2;
        w14 = w14 + (s32)ot;
        v0s = *(u32 *)w14;
        w8 = 0xFFFFFF;
        w8 = (u32)prim & w8;
        v0s = v0s | codeConst;
        *(u32 *)prim = v0s;
        *(u32 *)w14 = w8;
        gte_stsxy(prim20);
        prim20 += 0x34;
        prim += 0x34;
    incr:
        arg1--;
        obj += 0x2C;
        ret += 0x2C;
    } while (arg1 > 0);
    gPrimitiveCursor[0] = (u32)prim;
    asm volatile("addu $2, %0, $0" : : "r"(ret));
}

extern s32 D_800A2CF8[];
s32 func_80032A90(u8 *arg0) {
    u8 *entry;
    s32 i;
    s16 result;
    s32 pad[2];

    (void)&pad;
    if (D_800A2CF8[0] == 2) {
        result = 1;
        goto done;
    }
    entry = arg0 + 0x54;
    i = 0;
    do {
        if (*(s16 *)(entry + 4) < 0x9B) {
            result = 1;
            goto done;
        }
        i = i + 1;
        entry = entry + 0x14;
    } while (i < 4);
    result = 0;
done:
    return result;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80032AE4);

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

extern s32 func_800337EC(void);
extern u32 gPrimitiveCursor[];
extern s32 D_800A39C8[];
extern u32 D_800B022C[];
extern s16 D_800AFE2C[];
extern s32 D_800A2F38NM asm("D_800A2F38.NON_MATCHING");

void func_80032DEC(u8 *arg0, s32 arg1) {
    register s32 w4 asm("v1");
    s32 w8;
    register s32 wC asm("v0");
    register s32 n0 asm("v1");
    register s32 n1 asm("a0");
    register s32 old asm("a0");
    register s32 tmpa1 asm("a1");
    register s32 sh asm("v1");
    s32 base;
    u8 *obj;
    register u8 *prim18 asm("s1");
    u8 *prim;
    register s32 otz asm("s3");
    s32 count;
    u32 *objCursor;
    s32 entryCount;
    s16 *zCursor;
    register u8 *otBase40;
    register s32 shifted asm("v0");
    register s32 aligned asm("v0");
    s32 mask;
    s32 diff;
    register s32 guard asm("a2");
    s32 oldEnd;
    s32 *normal;
    s32 w10;
    s32 w14;

    obj = arg0;
    old = D_800A2F38NM;
    count = arg1;
    guard = count;
    count = count - 1;
    prim = (u8 *)gPrimitiveCursor[0];
    tmpa1 = (s32)D_800A39C8[0];
    otBase40 = (u8 *)tmpa1 + 0x40;
    base = (s32)D_800B022C;
    sh = old * 4;
    objCursor = (u32 *)(sh + base);
    sh = old * 2;
    base = (s32)D_800AFE2C;
    zCursor = (s16 *)(sh + base);
    entryCount = old;
    if (guard > 0) {
        prim18 = prim + 0x18;
        do {
            gte_ldv3(*(s32 **)(obj + 0x18), *(s32 **)(obj + 0x1C),
                     *(s32 **)(obj + 0x20));
            w4 = *(s32 *)(obj + 0x4);
            w8 = *(s32 *)(obj + 0x8);
            gte_op(rtpt);
            wC = *(s32 *)(obj + 0xC);
            w10 = *(s32 *)(obj + 0x10);
            w14 = *(s32 *)(obj + 0x14);
            *(s32 *)(prim18 - 0xC) = w8;
            *(s32 *)(prim18 - 0x14) = w4;
            *(s32 *)(prim18 - 4) = wC;
            gte_stsxy3(prim + 8, prim + 0x10, prim + 0x20);
            normal = *(s32 **)(obj + 0x24);
            n0 = normal[0];
            n1 = normal[1];
            gte_op(avsz3);
            *(s32 *)(prim18 + 4) = w10;
            *(s32 *)(prim18 + 0xC) = w14;
            gte_mfc2_nonop(otz, 7);
            gte_mtc2(n0, 0);
            gte_mtc2(n1, 1);
            if (otz < 0x9B) {
                gte_op(rtps);
                if (func_800337EC() != 0 && entryCount < 0x1FF) {
                    otz = otz + *(s8 *)(obj + 1);
                    if (otz >= 0) {
                        entryCount = entryCount + 1;
                        *objCursor = (u32)obj;
                        objCursor = objCursor + 1;
                        shifted = otz << 2;
                        *zCursor = shifted;
                        zCursor = zCursor + 1;
                    }
                    goto nextObj;
                }
            }
            gte_op(rtps);
            tmpa1 = *(s8 *)(obj + 1);
            aligned = (otz >> 2) << 2;
            aligned = aligned + (s32)otBase40;
            mask = 0xFF0000;
            tmpa1 = tmpa1 * 4 + aligned;
            *(u32 *)prim = *(u32 *)tmpa1 | 0x09000000;
            mask = mask | 0xFFFF;
            *(u32 *)tmpa1 = (u32)prim & mask;
            gte_stsxy2(prim18);
            prim18 = prim18 + 0x28;
            prim = prim + 0x28;
        nextObj:
            obj = *(u8 **)(obj + 0x28);
        } while (count-- > 0);
    }
    gPrimitiveCursor[0] = (u32)prim;
    oldEnd = D_800A2F38NM;
    diff = (s32)objCursor - (s32)D_800B022C;
    diff = diff - oldEnd * 4;
    D_800A2F38NM = oldEnd + (diff >> 2);
}

extern u8 D_800A2DE0[];
extern s32 D_800A2F08NM[] asm("D_800A2F08.NON_MATCHING");
extern s32 D_800A2CFCNM[] asm("D_800A2CFC.NON_MATCHING");
extern s32 D_800A394CNM asm("D_800A394C.NON_MATCHING");
extern s32 D_800A3A74NM asm("D_800A3A74.NON_MATCHING");
extern s32 D_800A396CNM asm("D_800A396C.NON_MATCHING");

/* Draws the track groups between two list cursors: listA follows each
 * group's +0 link and listB its +4 link, alternating sides. A group is
 * drawn once (+0xE done flag). Past the D_800A2F08 object budget a group
 * draws as five flat quads; otherwise its objects draw as textured
 * triangles, the first +0x13 of them without backface culling. Near
 * triangles that func_800337EC accepts go to the depth-sorted list at
 * D_800B022C/D_800AFE2C instead of the ordering table.
 *
 * word0 and word1 are scratch words reused for colour words, the fourth
 * vertex, and the next object's vertex list. */
void func_80033000(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 *prim;
    u8 *listA;
    u8 *listB;
    s32 count;
    u32 *otCursor;
    s16 *zCursor;
    u8 *group;
    register u8 *obj asm("s0");
    u8 *poly;
    s32 i;
    s32 n;
    s32 otz;
    register s32 word0 asm("s2");
    register s32 word1 asm("s1");
    u8 *vec;
    u8 *verts;
    s32 wC;
    s32 w10;
    s32 w14;
    s32 old;
    s32 diff;
    u32 *ot;
    s32 counter;
    s32 lod;
    s32 mode;

    prim = (u8 *)gPrimitiveCursor[0];
    old = D_800A2F38NM;
    count = 0;
    counter = 0;
    mode = 1;
    listA = arg2;
    listB = *(u8 **)listA;
    otCursor = (u32 *)((u8 *)D_800B022C + old * 4);
    lod = D_800A2F08NM[0];
    ot = (u32 *)D_800A39C8[0] + 0x10;
    zCursor = (s16 *)((u8 *)D_800AFE2C + old * 2);
    if ((listA = listA) != arg1 || (listB = listB) != arg0) {
        do {
            if (counter & 1) {
                if (listA == arg1) {
                    listB = *(u8 **)(listB + 4);
                    group = listB;
                } else {
                    listA = *(u8 **)listA;
                    group = listA;
                }
            } else {
                if (listB != arg0) {
                    listB = *(u8 **)(listB + 4);
                    group = listB;
                } else {
                    listA = *(u8 **)listA;
                    group = listA;
                }
            }
            counter = counter + 1;
            if (*(u16 *)(group + 0xE) != 0) {
                /* Already drawn. */
            } else if (lod < count) {
                for (i = 0; i < 5; i++) {
                    if (mode) {
                        gte_ldv3(((u8 **)(*(u8 **)group + 0x78))[i],
                                 ((u8 **)(*(u8 **)(*(u8 **)(group + 4) + 4) +
                                          0x78))[i],
                                 ((u8 **)(*(u8 **)(*(u8 **)(group + 4) + 4) +
                                          0x78))[i + 1]);
                    } else {
                        gte_ldv3(((u8 **)(group + 0x78))[i],
                                 ((u8 **)(*(u8 **)(group + 4) + 0x78))[i],
                                 ((u8 **)(*(u8 **)(group + 4) + 0x78))[i + 1]);
                    }
                    poly = prim;
                    gte_rtpt();
                    if (i == 2) {
                        *(s32 *)(prim + 4) = D_800A394CNM;
                    } else if (i & 1) {
                        *(s32 *)(prim + 4) = D_800A3A74NM;
                    } else {
                        *(s32 *)(prim + 4) = D_800A396CNM;
                    }
                    SetPolyF4(poly);
                    gte_cfc2_nonop(otz, 31);
                    gte_stsxy3(poly + 8, poly + 0xC, poly + 0x14);
                    if (otz & 0x6000) {
                        continue;
                    }
                    gte_avsz3();
                    if (mode) {
                        vec = *(u8 **)(*(u8 **)group + (i << 2) + 0x7C);
                    } else {
                        vec = ((u8 **)(group + 0x78))[i + 1];
                    }
                    word0 = *(s32 *)vec;
                    word1 = *(s32 *)(vec + 4);
                    gte_mfc2_nonop(otz, 7);
                    gte_mtc2(word0, 0);
                    gte_mtc2(word1, 1);
                    if (otz < 0x9B) {
                        continue;
                    }
                    gte_op(rtps);
                    if (otz >= 0xF3D) {
                        otz = 0xF3C;
                    }
                    *(u32 *)prim = ot[otz >> 2] | 0x05000000;
                    ot[otz >> 2] = (u32)prim & 0xFFFFFF;
                    gte_stsxy(poly + 0x10);
                    prim = prim + 0x28;
                }
                mode = 0;
                *(u16 *)(group + 0xE) = 1;
            } else {
                n = *(u8 *)(group + 0x13);
                obj = *(u8 **)(group + 0x20);
                count = count + n;
                while (n-- > 0) {
                    gte_ldv3(*(u8 **)(obj + 0x18), *(u8 **)(obj + 0x1C),
                             *(u8 **)(obj + 0x20));
                    word0 = *(s32 *)(obj + 4);
                    word1 = *(s32 *)(obj + 8);
                    gte_op(rtpt);
                    wC = *(s32 *)(obj + 0xC);
                    w10 = *(s32 *)(obj + 0x10);
                    w14 = *(s32 *)(obj + 0x14);
                    *(s32 *)(prim + 0x14) = wC;
                    *(s32 *)(prim + 4) = word0;
                    *(s32 *)(prim + 0xC) = word1;
                    gte_stsxy3(prim + 8, prim + 0x10, prim + 0x20);
                    vec = *(u8 **)(obj + 0x24);
                    word0 = *(s32 *)vec;
                    word1 = *(s32 *)(vec + 4);
                    gte_op(avsz3);
                    *(s32 *)(prim + 0x1C) = w10;
                    *(s32 *)(prim + 0x24) = w14;
                    gte_mfc2_nonop(otz, 7);
                    gte_mtc2(word0, 0);
                    gte_mtc2(word1, 1);
                    if (otz < 0x9B) {
                        gte_op(rtps);
                        if (func_800337EC() != 0) {
                            otz = otz + *(s8 *)(obj + 1) * 2;
                            if (otz >= 0) {
                                *otCursor++ = (u32)obj;
                                *zCursor++ = otz << 2;
                            }
                            goto next1;
                        }
                    }
                    gte_op(rtps);
                    otz = (otz >> 2) + *(s8 *)(obj + 1);
                    if (otz >= 0x3B7) {
                        otz = 0x3B6;
                    }
                    *(u32 *)prim = ot[otz] | 0x09000000;
                    ot[otz] = (u32)prim & 0xFFFFFF;
                    gte_stsxy(prim + 0x18);
                    prim = prim + 0x28;
                next1:
                    obj = *(u8 **)(obj + 0x28);
                }
                /* n now holds the backface-cull mode. */
                n = D_800A2DE0[0];
                word0 = (s32)(obj + 0x18);
                while (obj != 0) {
                    count++;
                    verts = (u8 *)word0;
                    gte_ldv3(*(u8 **)verts, *(u8 **)(verts + 4),
                             *(u8 **)(verts + 8));
                    word0 = *(s32 *)(obj + 4);
                    word1 = *(s32 *)(obj + 8);
                    gte_op(rtpt);
                    wC = *(s32 *)(obj + 0xC);
                    w10 = *(s32 *)(obj + 0x10);
                    w14 = *(s32 *)(obj + 0x14);
                    *(s32 *)(prim + 4) = word0;
                    *(s32 *)(prim + 0xC) = word1;
                    *(s32 *)(prim + 0x14) = wC;
                    gte_cfc2_nonop(otz, 31);
                    gte_stsxy3(prim + 8, prim + 0x10, prim + 0x20);
                    if (otz & 0x6000) {
                        goto skip;
                    }
                    gte_op(nclip);
                    vec = *(u8 **)(verts + 0xC);
                    word0 = *(s32 *)vec;
                    word1 = *(s32 *)(vec + 4);
                    *(s32 *)(prim + 0x1C) = w10;
                    *(s32 *)(prim + 0x24) = w14;
                    gte_mfc2_nonop(otz, 24);
                    gte_mtc2(word0, 0);
                    gte_mtc2(word1, 1);
                    if (n != 0) {
                        if (otz < 0) {
                            goto skip;
                        }
                    } else if (otz > 0) {
                        goto skip;
                    }
                    goto draw;
                skip:
                    word1 = *(s32 *)(obj + 0x28);
                    word0 = word1 + 0x18;
                    goto next2;
                draw:
                    gte_op(avsz3);
                    word1 = *(s32 *)(obj + 0x28);
                    word0 = word1 + 0x18;
                    gte_mfc2(otz, 7);
                    if (otz < 0x9B) {
                        gte_op(rtps);
                        if (func_800337EC() != 0) {
                            otz = otz + *(s8 *)(obj + 1);
                            if (otz >= 0) {
                                *otCursor++ = (u32)obj;
                                *zCursor++ = otz << 2;
                            }
                            goto next2;
                        }
                    }
                    gte_op(rtps);
                    otz = (otz >> 2) + *(s8 *)(obj + 1);
                    if (otz < 0x4B1) {
                        if (otz >= 0x3B7) {
                            otz = 0x3B6;
                        }
                        *(u32 *)prim = ot[otz] | 0x09000000;
                        ot[otz] = (u32)prim & 0xFFFFFF;
                        gte_stsxy(prim + 0x18);
                        prim = prim + 0x28;
                    }
                next2:
                    obj = (u8 *)word1;
                }
                *(u16 *)(group + 0xE) = 1;
            }
        } while ((listA = listA) != arg1 || (listB = listB) != arg0);
    }
    diff = (s32)otCursor - (s32)D_800B022C;
    D_800A2CFCNM[0] = count;
    gPrimitiveCursor[0] = (u32)prim;
    D_800A2F38NM = D_800A2F38NM + ((diff - D_800A2F38NM * 4) >> 2);
}

/*
 * Handwritten GTE module: func_80033704 through func_8003382C.
 *
 * These seven functions came from an assembly source file, not C. Don't
 * try to rewrite them as plain C or strip their register pins and asm.
 * The retail code has three shapes no C compiler emits:
 *
 * - func_80033780 has no delay slot of its own. Its `jr ra` uses the
 *   first instruction of func_80033788.
 * - func_8003382C branches into the middle of func_80033704
 *   (`bgez a2, func_80033704+0x20`).
 * - func_800337EC has an `mfc2` in a branch delay slot. gcc 2.7.2 never
 *   puts an asm insn in a delay slot, and this is the only such site in
 *   the EXE.
 *
 * func_80033788, func_8003379C and MathMultiplyFixed16 sit between
 * handwritten functions, so they belong to the same object file.
 * func_800338A4 onwards shows none of these shapes and is plain C.
 */
void func_80033704(s16 *out) {
    register s32 v1 asm("v1");
    register s32 a2 asm("a2");
    register s32 test asm("v0");
    s32 a3;
    s32 a1;
    s32 neg;

    asm volatile("mfc2 %0, $9" : "=r"(v1));
    asm volatile("mfc2 %0, $10" : "=r"(a3));
    asm volatile("mfc2 %0, $11" : "=r"(a2));
    out[0] = v1;
    out[1] = a3;
    out[2] = a2;
    if (a2 < 0) {
        asm("");
        a2 = 0;
    }
    asm(".L80033724:");
    a1 = 4;
    if (a2 >= v1) {
        asm("subu %0, $0, %1" : "=r"(neg) : "r"(v1));
        a1 = (a2 < neg) << 1;
    }
    if (a2 < a3) {
        a1 |= 1;
    } else if (a2 < -a3) {
        a1 |= 8;
    }
    if (a2 < 0x1F4) {
        a1 |= 0x100;
        test = a2 < 5;
        if (test) {
            a1 |= 0x1F;
        }
    }
    out[3] = a1;
}

void func_80033780(void *arg0) {
    asm volatile("swc2 $14, 0x8(%0)\n\t.set\tnoreorder" : : "r"(arg0));
}

void func_80033788(u8 *arg0) {
    register u32 depth asm("$6");

    /* Retail reads GTE IR3 (SZ average) and stores SXY2 for one vertex. */
    asm("mfc2 %0, $11" : "=r"(depth));
    asm("swc2 $14, 0x14($a0)");
    depth >>= 2;
    *(u16 *)(arg0 + 6) = depth;
}

void func_8003379C(u8 *arg0, u8 *arg1, u8 *arg2) {
    register u32 depthA asm("$3");
    register u32 depthB asm("$2");

    /* Retail stores SXY0/1/2 and SZ1/2/3 >> 2 for three vertices after
     * a RotTransPers3; the depth registers rotate v1/v0/v1. */
    asm volatile("mfc2 %0, $17" : "=r"(depthA));
    asm("swc2 $12, 0x14($a0)");
    depthA >>= 2;
    *(u16 *)(arg0 + 6) = depthA;

    asm volatile("mfc2 %0, $18" : "=r"(depthB));
    asm("swc2 $13, 0x14($a1)");
    depthB >>= 2;
    *(u16 *)(arg1 + 6) = depthB;

    asm volatile("mfc2 %0, $19" : "=r"(depthA));
    asm("swc2 $14, 0x14($a2)");
    depthA >>= 2;
    *(u16 *)(arg2 + 6) = depthA;
}

s32 MathMultiplyFixed16(s32 arg0, s32 arg1) {
    u32 lo;
    u32 hi;

    asm volatile("mult\t%0,%1" : : "r"(arg0), "r"(arg1) : "hi", "lo");
    asm volatile("mflo\t%0" : "=r"(lo) : : "lo");
    asm volatile("mfhi\t%0" : "=r"(hi) : : "hi");
    return (lo >> 16) | (hi << 16);
}

s32 func_800337EC(void) {
    s32 sz0;
    s32 sz1;
    s32 test1;
    s32 test2;
    register s32 sz2 asm("v1");
    register s32 sz3 asm("a0");
    register s32 test3 asm("v0");

    asm volatile("mfc2 %0, $16" : "=r"(sz0));
    asm volatile("mfc2 %0, $17" : "=r"(sz1));
    test1 = sz0 < 0x12C;
    test2 = sz1 < 0x12C;
    if (test1) {
        goto out;
    }
    asm volatile(".set\tnoreorder\n\t"
                 "bne %0, $0, func_800337EC+0x38\n\t"
                 "mfc2 %1, $18\n\t"
                 ".set\treorder"
                 : "=r"(sz2)
                 : "r"(test2));
    asm volatile("mfc2 %0, $19" : "=r"(sz3));
    test3 = sz2 < 0x12C;
    if (test3) {
        goto out;
    }
    asm volatile(".set\tnoreorder\n\t"
                 "slti $2, %0, 0x12C\n\t"
                 "j $31\n\t"
                 "nop\n\t"
                 ".set\treorder"
                 :
                 : "r"(sz3));
out:
    return 1;
}

void func_8003382C(s16 *out) {
    register s32 v1 asm("v1");
    register s32 a2 asm("a2");
    register s32 test asm("v0");
    s32 a3;
    s32 a1;
    s32 neg;

    asm volatile("mfc2 %0, $9\n\t"
                 "mfc2 %1, $10\n\t"
                 "mfc2 %2, $11\n\tnop\n\t"
                 "bgez %2, func_80033704+0x20"
                 : "=r"(v1), "=r"(a3), "=r"(a2));
    asm("addu %0, $0, $0" : "=r"(a2));
    a1 = 4;
    if (a2 >= v1) {
        asm("subu %0, $0, %1" : "=r"(neg) : "r"(v1));
        a1 = (a2 < neg) << 1;
    }
    if (a2 < a3) {
        a1 |= 1;
    } else if (a2 < -a3) {
        a1 |= 8;
    }
    if (a2 < 0x1F4) {
        a1 |= 0x100;
        test = a2 < 5;
        if (test) {
            a1 |= 0x10;
        }
    }
    out[3] = a1;
}

/* End of the handwritten GTE module. */

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

INCLUDE_ASM("asm/nonmatchings/objects", func_80033900);
extern u32 gScratchpad[];
extern s32 D_800A3640[];
extern s32 D_800A39C8[];
extern s32 D_800A2EA4Absolute[];
extern u8 D_800A2ED8Abs[] asm("D_800A2ED8.NON_MATCHING");

u32 func_800342D8(u32 *entry, u32 primCursor) {
    u8 *obj;
    register s32 *spad asm("s1");
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
    s32 w5;
    s32 *v18base;
    u8 *p8;
    u16 *quad;
    s32 *v18p;
    s32 *v1Cp;
    s32 *v24p;
    s32 *v20p;
    s32 *vec;
    register s32 flags asm("v0");
    s32 t;
    s32 kind;
    s32 u1;

    obj = *(u8 **)entry;
    asm volatile("lui %0, %%hi(gScratchpad)" : "=r"(spad));
    quad = (u16 *)0x1F80001C;
    asm volatile("addiu %0, %1, 0x18" : "=r"(v18base) : "r"(obj));
    p8 = obj + 8;

    vec = v18base[0];
    gte_ldv0(vec);
    w0 = *(s32 *)(obj + 0);
    w1 = *(s32 *)(obj + 4);
    gte_op(rtps);
    w2 = *(s32 *)(obj + 8);
    w3 = *(s32 *)(obj + 0xC);
    w4 = *(s32 *)(obj + 0x10);
    w5 = *(s32 *)(obj + 0x14);
    vec = v18base[1];
    gte_ldv0(vec);
    func_80033704((s16 *)0x1F80001C);
    gte_op(rtps);
    spad[0] = w0;
    gScratchpad[1] = w1;
    gScratchpad[2] = w2;
    gScratchpad[3] = w3;
    vec = v18base[3];
    gte_ldv0(vec);
    func_80033704((s16 *)0x1F800030);
    gte_op(rtps);
    gScratchpad[4] = w4;
    gScratchpad[5] = w5;
    v18p = *(s32 **)(obj + 0x18);
    vec = v18base[2];
    w0 = v18p[0];
    w4 = v18p[1];
    gte_ldv0(vec);
    func_80033704((s16 *)0x1F800044);
    gte_op(rtps);
    v1Cp = *(s32 **)(obj + 0x1C);
    v24p = *(s32 **)(obj + 0x24);
    w1 = v1Cp[0];
    w5 = v1Cp[1];
    w2 = v24p[0];
    obj = (u8 *)v24p[1];
    func_80033704((s16 *)0x1F800058);

    flags = ((u16 *)gScratchpad)[0x11];
    flags &= ((u16 *)gScratchpad)[0x1B];
    flags &= ((u16 *)gScratchpad)[0x25];
    flags &= ((u16 *)gScratchpad)[0x2F];
    flags &= 0x7EFF;
    if (flags != 0) {
        flags = 0;
    } else {
        flags = 1;
    }
    flags &= 0xFF;
    if (flags == 0) {
        flags = 0;
        *entry = flags;
        return primCursor;
    }

    t = D_800A3640[0];
    if (t < 0) {
        spad[6] = D_800A39C8[0] + 0x40;
    } else {
        spad[6] = D_800A39C8[0] + ((t >> 4) << 2) + 0x40;
    }
    v20p = v18base[2];
    w3 = v20p[0];
    u1 = v20p[1];
    spad = &spad[7];
    spad[0] = w0;
    spad[1] = w4;
    spad[8] = w1;
    spad[9] = w5;
    spad[0x18] = w2;
    spad[0x19] = obj;
    spad[0x20] = w3;
    spad[0x21] = u1;

    w0 = *(u16 *)p8;
    w1 = *(u16 *)(p8 + 4);
    w2 = *(u16 *)(p8 + 8);
    w3 = *(u16 *)(p8 + 0xC);
    quad[3] = w0;
    quad[0x13] = w1;
    quad[0x33] = w2;
    quad[0x43] = w3;

    kind = *(s8 *)(*(u8 **)entry + 2);
    if (kind >= 13) {
        if (kind == 13) {
            *entry = 0;
            return func_80033900(spad, primCursor, 2);
        } else {
            *entry = 0;
            return func_80033900(spad, primCursor, 1);
        }
    } else {
        if (D_800A2EA4Absolute[0] != 0 || D_800A2ED8Abs[0] != 0) {
            return func_80033900(spad, primCursor, 2);
        } else {
            return func_80033900(spad, primCursor, 0);
        }
    }
}

extern MATRIX D_800A4568[];
extern MATRIX D_800A4588[];

void func_800345E0(void) {
    s16 *base;
    s16 *row;
    s16 *p16;
    s32 *tp;
    s32 i;
    s32 j;

    gte_ReadRotMatrix(D_800A4568);
    gte_ReadRotMatrix(D_800A4588);
    i = 0;
    base = D_800A4588->m[0];
    tp = (s32 *)&base[10];
    row = base;
    do {
        j = 0;
        p16 = row;
        do {
            *p16 *= 4;
            p16 += 1;
            j += 1;
        } while (j < 3);
        row += 3;
        *tp *= 4;
        tp += 1;
        i += 1;
    } while (i < 3);
}

extern u32 gPrimitiveCursor[];
extern s32 D_800A36D0Absolute[];
extern s32 D_800A3668Absolute[];
extern s32 D_800A2F38[];
extern s32 D_800A3640[];
extern s16 D_800AFE2C[];
extern u32 D_800B022C[];
extern MATRIX D_800A4588[];
extern MATRIX D_800A4568[];

extern u32 D_800A3570Lui asm("D_800A3570Absolute");
extern u32 gPrimitiveCursorLui asm("gPrimitiveCursorAbsolute");
s32 func_800346D0(s32 threshold) {
    s32 i;
    u32 ret;

    if (D_800A2CF8[0] == 3) {
        return 0;
    }
    PushMatrix();
    SetRotMatrix(D_800A4588);
    SetTransMatrix(D_800A4588);
    for (i = 0; i < D_800A2F38[0]; i++) {
        D_800A3640[0] = D_800AFE2C[i];
        ret = func_800342D8(&D_800B022C[i], gPrimitiveCursor[0]);
        gPrimitiveCursorLui = ret;
        if (threshold <
            (s32)(((ret & 0xFFFFFFF) - (D_800A3570Lui & 0xFFFFFFF)) / 40)) {
            D_800A2F38[0] = i;
        }
    }
    if (D_800A2CF8[0] < 2) {
        SetRotMatrix(D_800A4568);
        SetTransMatrix(D_800A4568);
        func_80034834();
    }
    PopMatrix();
    return D_800A2F38[0];
}

extern s32 D_800A39C8[];
extern u32 gPrimitiveCursor[];
extern s32 D_800A2F38[];
extern u32 D_800B022C[];

void func_80034834(void) {
    u8 *prim;
    u8 *ot;
    s32 i;
    u8 *obj;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;

    ot = (u8 *)D_800A39C8[0] + 0x80;
    prim = (u8 *)gPrimitiveCursor[0];
    for (i = 0; i < D_800A2F38[0]; i++) {
        obj = (u8 *)D_800B022C[i];
        if (obj != 0 && (*(u8 *)(obj + 0x13) & 0x80) == 0) {
            gte_ldv3(*(u32 **)(obj + 0x18), *(u32 **)(obj + 0x1C),
                     *(u32 **)(obj + 0x20));
            /*
             * t0 to t2 are reused for the normal vector load below: that
             * gives each value two live ranges, so global allocation
             * (not local) picks their registers, as in retail.
             */
            t0 = *(s32 *)(obj + 0x4);
            t1 = *(s32 *)(obj + 0x8);
            gte_op(rtpt);
            t2 = *(s32 *)(obj + 0xC);
            t3 = *(s32 *)(obj + 0x10);
            t4 = *(s32 *)(obj + 0x14);
            *(s32 *)(prim + 0x4) = t0;
            *(s32 *)(prim + 0xC) = t1;
            *(s32 *)(prim + 0x14) = t2;
            gte_stsxy3(prim + 8, prim + 0x10, prim + 0x20);
            t2 = *(s32 *)(obj + 0x24);
            t0 = *(s32 *)(t2 + 0);
            t1 = *(s32 *)(t2 + 4);
            *(s32 *)(prim + 0x1C) = t3;
            *(s32 *)(prim + 0x24) = t4;
            gte_mtc2(t0, 0);
            gte_mtc2(t1, 1);
            gte_rtps();
            GraphicsAddTaggedPrimitive((u32 *)(ot + 0xC0), (u32 *)prim,
                                       0x09000000);
            gte_stsxy(prim + 0x18);
            prim += 0x28;
        }
    }
    gPrimitiveCursor[0] = (u32)prim;
}

#ifdef NON_MATCHING
/*
 * WALL (w9d): this draft is byte-exact except for ONE addressing fact:
 * retail reads D_800A38C0 with `lhu %gp_rel(D_800A38C0)($gp)` here, but
 * TextureLoadTim STORES the same symbol absolute (lui/sw). Declaring
 * D_800A38C0 scalar for the gp read flips TextureLoadTim's store to
 * gp-rel (-4 bytes, whole-EXE shift; the w8b wall). Needs the Makefile
 * defsym alias D_800A38C0Small=D_800A38C0 and an `extern u16
 * D_800A38C0Small;` here -- then this draft should drop in unmodified.
 * Everything else was verified clean by asm-differ: prologue (li s4,
 * 0xA7 / li s3, 0xFD hoisted before the IV init), both FT4 loops (for +
 * (i+1)<<7-1 CSE), and the F4 tail as a do-while with the f4 += 0x18
 * before the test (it lands in the bnez delay slot). cursor = base +
 * car * 0x28 is REQUIRED: spelling the 0xA0 stride as a separate `off`
 * local puts move s5,zero before the li constants and breaks the
 * prologue order.
 */
extern u16 D_800A38C0;
extern u8 *D_800A3850;
extern u8 *D_800A390C;
extern u8 D_800AFBB8[];
extern u8 D_800AFB18[];
extern u8 D_800B1F30[];

void func_80034990(void) {
    u16 color;
    s32 car;
    s32 i;
    u8 *cursor;
    POLY_FT4 *prim;
    POLY_F4 *f4;
    s32 red;
    s32 green;
    s32 blue;

    D_800A3850 = D_800AFBB8;
    color = D_800A38C0;
    for (car = 0; car < 0xC; car += 4) {
        cursor = D_800AFB18 + car * 0x28;
        for (i = 0; i < 2; i++) {
            prim = (POLY_FT4 *)(cursor + i * 0x28);
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            prim->tpage = GetTPage(1, 0, 0x200, 0x100);
            prim->clut = GetClut(0x200, 0x1FF);
            prim->u0 = i << 7;
            prim->v0 = 0xA7;
            prim->u1 = ((i + 1) << 7) - 1;
            prim->v1 = 0xA7;
            prim->u2 = i << 7;
            prim->v2 = 0xFD;
            prim->u3 = ((i + 1) << 7) - 1;
            prim->v3 = 0xFD;
        }
        for (i = 0; i < 2; i++) {
            prim = (POLY_FT4 *)(cursor + 0x50 + i * 0x28);
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            prim->tpage = GetTPage(1, 0, 0x280, 0x100);
            prim->clut = GetClut(0x200, 0x1FF);
            prim->u0 = i << 7;
            prim->v0 = 0xA7;
            prim->u1 = ((i + 1) << 7) - 1;
            prim->v1 = 0xA7;
            prim->u2 = i << 7;
            prim->v2 = 0xFD;
            prim->u3 = ((i + 1) << 7) - 1;
            prim->v3 = 0xFD;
        }
    }
    red = (color & 0x7C00) >> 7;
    green = (color & 0x3E0) >> 2;
    blue = (color & 0x1F) << 3;
    D_800A390C = D_800B1F30;
    i = 0;
    f4 = (POLY_F4 *)(D_800B1F30 - 0x60);
    do {
        SetPolyF4(f4);
        f4->r0 = blue;
        f4->g0 = green;
        f4->b0 = red;
        i++;
        f4 += 0x18;
    } while (i < 8);
}
#endif

extern u16 D_800A38C0Small;
extern u8 *D_800A3850;
extern u8 *D_800A390C;
extern u8 D_800AFBB8[];
extern u8 D_800AFB18[];
extern u8 D_800B1F30[];

void func_80034990(void) {
    u16 color;
    s32 car;
    s32 i;
    u8 *cursor;
    POLY_FT4 *prim;
    POLY_F4 *f4;
    s32 red;
    s32 green;
    s32 blue;

    D_800A3850 = D_800AFBB8;
    color = D_800A38C0Small;
    for (car = 0; car < 0xC; car += 4) {
        cursor = D_800AFB18 + car * 0x28;
        for (i = 0; i < 2; i++) {
            prim = (POLY_FT4 *)(cursor + i * 0x28);
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            prim->tpage = GetTPage(1, 0, 0x200, 0x100);
            prim->clut = GetClut(0x200, 0x1FF);
            prim->u0 = i << 7;
            prim->v0 = 0xA7;
            prim->u1 = ((i + 1) << 7) - 1;
            prim->v1 = 0xA7;
            prim->u2 = i << 7;
            prim->v2 = 0xFD;
            prim->u3 = ((i + 1) << 7) - 1;
            prim->v3 = 0xFD;
        }
        for (i = 0; i < 2; i++) {
            prim = (POLY_FT4 *)(cursor + 0x50 + i * 0x28);
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            prim->tpage = GetTPage(1, 0, 0x280, 0x100);
            prim->clut = GetClut(0x200, 0x1FF);
            prim->u0 = i << 7;
            prim->v0 = 0xA7;
            prim->u1 = ((i + 1) << 7) - 1;
            prim->v1 = 0xA7;
            prim->u2 = i << 7;
            prim->v2 = 0xFD;
            prim->u3 = ((i + 1) << 7) - 1;
            prim->v3 = 0xFD;
        }
    }
    red = (color & 0x7C00) >> 7;
    green = (color & 0x3E0) >> 2;
    blue = (color & 0x1F) << 3;
    D_800A390C = D_800B1F30;
    i = 0;
    f4 = (POLY_F4 *)(D_800B1F30 - 0x60);
    do {
        SetPolyF4(f4 + i);
        f4[i].r0 = blue;
        f4[i].g0 = green;
        f4[i].b0 = red;
        i++;
    } while (i < 8);
}

typedef struct {
    s32 words[10];
} Primitive40;

extern u32 gPrimitiveCursor[];
extern s32 D_800A39C8[];
extern s32 D_800A36D0Absolute[];
void func_80034B90(u8 *prim) {
    POLY_FT4 *entry;
    u32 cursor;

    cursor = gPrimitiveCursor[0];
    ((s32 *)D_800A36D0Absolute)[-67] = cursor + sizeof(POLY_FT4);
    entry = (POLY_FT4 *)cursor;
    *entry = *(POLY_FT4 *)prim;
    AddPrim((u8 *)D_800A39C8[0] + 0xFF8, entry);
}

extern s32 D_800A36D0Absolute[];
extern s32 D_800A3784Absolute[], D_800A3790Absolute[], D_800A3794Absolute[];
extern s32 D_800A3798Absolute[], D_800A379CAbsolute[], D_800A37A4Absolute[];
extern s32 D_800A37ACAbsolute[], D_800A37B4Absolute[], D_800A37C4Absolute[];

void func_80034C1C(void) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = ((s32 *)D_800A36D0Absolute)[-8];
    b = ((s32 *)D_800A36D0Absolute)[-6];
    c = ((s32 *)D_800A36D0Absolute)[-2];
    d = D_800A36D0Absolute[0];
    D_800A3794Absolute[0] = 0;
    D_800A37A4Absolute[0] = 0;
    D_800A37ACAbsolute[0] = 0;
    D_800A37B4Absolute[0] = 0;
    D_800A37C4Absolute[0] = 0x10000;
    D_800A3784Absolute[0] = a;
    D_800A3790Absolute[0] = b;
    D_800A3798Absolute[0] = -c;
    D_800A379CAbsolute[0] = d;
}

extern s32 D_800A36D0Absolute[];
extern s32 D_800A36D4Absolute[];
extern s32 D_800A3784Absolute[], D_800A3790Absolute[], D_800A3794Absolute[],
    D_800A3798Absolute[], D_800A379CAbsolute[], D_800A37A4Absolute[],
    D_800A37ACAbsolute[], D_800A37B4Absolute[], D_800A37C4Absolute[];
void func_80034C94(void) {
    D_800A3784Absolute[0] = 0x10000;
    D_800A3790Absolute[0] = 0;
    D_800A3794Absolute[0] = 0;
    D_800A3798Absolute[0] = 0;
    D_800A37ACAbsolute[0] = 0;
    D_800A379CAbsolute[0] = D_800A36D0Absolute[0];
    D_800A37A4Absolute[0] = D_800A36D4Absolute[0];
    D_800A37B4Absolute[0] = -D_800A36D4Absolute[0];
    D_800A37C4Absolute[0] = D_800A36D0Absolute[0];
}

extern s32 D_800A36C0Absolute[];
extern s32 D_800A36E8Absolute[];
extern s32 D_800A3790Absolute[], D_800A3798Absolute[], D_800A379CAbsolute[],
    D_800A37A4Absolute[], D_800A37B4Absolute[], D_800A3794Absolute[],
    D_800A3784Absolute[], D_800A37ACAbsolute[], D_800A37C4Absolute[];
void func_80034CFC(void) {
    D_800A3790Absolute[0] = 0;
    D_800A3798Absolute[0] = 0;
    D_800A379CAbsolute[0] = 0x10000;
    D_800A37A4Absolute[0] = 0;
    D_800A37B4Absolute[0] = 0;
    D_800A3784Absolute[0] = D_800A36E8Absolute[0];
    D_800A3794Absolute[0] = D_800A36C0Absolute[0];
    D_800A37ACAbsolute[0] = -D_800A36C0Absolute[0];
    D_800A37C4Absolute[0] = D_800A36E8Absolute[0];
}

#ifdef NON_MATCHING
void func_80034C1C(void) {
    D_800A3794[0] = 0;
    D_800A37A4[0] = 0;
    D_800A37AC[0] = 0;
    D_800A37B4[0] = 0;
    D_800A37C4[0] = 0x10000;
    D_800A3784[0] = D_800A36B0;
    D_800A3790[0] = D_800A36B8;
    D_800A3798[0] = -D_800A36C8;
    D_800A379C[0] = D_800A36D0;
}
#else
#endif

INCLUDE_ASM("asm/nonmatchings/objects", func_80034D64);

INCLUDE_ASM("asm/nonmatchings/objects", func_80035274);

extern u8 *D_800A3554[];
extern void *D_800A2EA0[];
void func_80035274(void);
void func_8003565C(s32 arg0) {
    u8 *value;

    if (arg0 == 0) {
        value = D_800A3554[0];
    } else {
        value = *(u8 **)(D_800A3554[0] + 0x3E0);
    }
    D_800A2EA0[0] = (void *)value;
    func_80035274();
}

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

extern s32 D_800A2F44;
extern u8 *D_800A3850;
extern u8 *D_800A390C;

void func_80035720(u_long *ot) {
    s32 value;
    s32 x;
    s32 y;
    s32 off;
    s32 i;
    s32 c;
    s32 nx;
    POLY_FT4 *prim;
    LINE_F4 *line;
    s32 bank;

    value = D_800A2F44;
    x = (0x200 - value) / 2;
    y = x / 64;
    x = y * 64 - x;
    i = 0;
    c = 0x23;
    off = y * 40;
    for (; i < 5; i++) {
        if (y >= 8) {
            off = 0;
            y = 0;
        }
        prim = (POLY_FT4 *)(D_800A3850 + off);
        y++;
        prim->x0 = x;
        prim->x2 = x;
        nx = x + 0x40;
        x = nx;
        off += 0x28;
        prim->y0 = 0;
        prim->x1 = nx;
        prim->y1 = 0;
        prim->y2 = c;
        prim->x3 = nx;
        prim->y3 = c;
        AddPrim(ot + 0x3FF, prim);
    }
    bank = gOrderingTableBankAbsolute[0];
    line = (LINE_F4 *)(D_800A390C + bank * 24);
    setXY4(line, 0xC8, 0x23, 0, 0x23, 0xC8, 0x46, 0, 0x46);
    setRGB0(line, 0x28, 0x6A, 2);
    AddPrim(ot + 0x3FF, line);
}

extern u8 D_800A2DE1[];
extern s32 D_800A2E9C[];
extern s32 D_800A2E24Absolute[];
void func_8002F0A8(u8 *);
void func_80034D64(void);
void func_80035720(u_long *);
void func_8003587C(s32 arg0) {
    /* second stores to each symbol go through existing defsym
     * neighbors so gcc re-materializes lui/at instead of hoisting the
     * addresses into callee-saved registers:
     *   D_800A2E24-0x43 = 0x2DE1, D_800A2E24+70*4 = 0x2F3C */
    D_800A2DE1[0] = 1;
    func_8002F0A8(D_800A2E9C[0]);
    ((u8 *)D_800A2E24Absolute)[-0x43] = 0;
    D_800A2F3C[0] = 0x23;
    func_80034D64();
    func_80035720(arg0);
    ((s32 *)D_800A2E24Absolute)[70] = 0x82;
}

#ifdef NON_MATCHING
/* Parked 2026-10-12: the opening mult chain, the MathSqrt and MathFixedDivide
 * calls and the block order match retail (12 rows, 8 bytes short). Left: the
 * `li v0,0x200` constants and the angle register in the four quadrant arms.
 * `new_var = 0x200;` is a permuter find (315 against 855). The old note about
 * a mult-window wall no longer applies to this shape. */
extern s32 D_800A38A4;
extern u8 D_800A2F48;
s32 func_800358EC(s32 *vec) {
    s32 len;
    s32 x;
    s32 y;
    s32 ax;
    s32 ay;
    s32 angle;
    int new_var;

    len = MathSqrt(vec[0] * vec[0] + vec[1] * vec[1]);
    D_800A38A4 = len;
    D_800A2F48 = 0;
    if (len < 5) {
        D_800A2F48 = 1;
        return 0;
    }
    if (vec[0] >= len) {
        len = vec[0] + 1;
    }
    if (vec[1] >= len) {
        len = vec[1] + 1;
    }
    x = MathFixedDivide(vec[0], len);
    y = MathFixedDivide(vec[1], len);
    if (y > 0x10000) {
        y = 0xFFFF;
    } else if (-y > 0x10000) {
        y = -0x10001;
    }
    new_var = 0x200;
    if (x >= 0 && y >= 0) {
        if (x >= y) {
            angle = ((u8 *)D_800A3668Absolute[0])[y >> 4];
        } else {
            angle = 0x100 - ((u8 *)D_800A3668Absolute[0])[x >> 4];
        }
    } else if (x < 0 && y >= 0) {
        ax = -x;
        if (ax >= y) {
            angle = 0x200 - ((u8 *)D_800A3668Absolute[0])[y >> 4];
        } else {
            angle = ((u8 *)D_800A3668Absolute[0])[ax >> 4] + 0x100;
        }
    } else if (x >= 0 && y < 0) {
        ay = -y;
        if (x >= ay) {
            angle = 0x200 - ((u8 *)D_800A3668Absolute[0])[ay >> 4];
        } else {
            angle = ((u8 *)D_800A3668Absolute[0])[x >> 4] + 0x100;
        }
        angle += 0x200;
    } else {
        ax = -x;
        ay = -y;
        if (ax >= ay) {
            angle = ((u8 *)D_800A3668Absolute[0])[ay >> 4] + 0x200;
        } else {
            angle = 0x100 - ((u8 *)D_800A3668Absolute[0])[ax >> 4];
            angle += new_var;
        }
    }
    return angle & 0x3FF;
}
#else
INCLUDE_ASM("asm/nonmatchings/objects", func_800358EC);
#endif

extern u16 D_80090F24[];
extern u16 D_80091004[];
extern s32 D_800B60C8[];

/* Initialise the 0x48-entry 0xC8-stride tile table at D_800B60C8: three
 * banks of 24 entries. poly[1..4] of each entry become textured POLY_FT4s;
 * the 4 u16s at entry+0x20 prime poly[0]'s tail (counter/type/uv). Bank 0
 * takes 16x16 tiles from D_80090F24; banks 1-2 take translucent 64x64
 * tiles from D_80091004 (v3 = u+0x3F here is the original's quirk). */
void func_80035B20(void) {
    u8 *entry;
    u8 *prim;
    u16 *tex;
    s32 i;
    s32 j;

    entry = (u8 *)D_800B60C8;
    i = 0;
    tex = D_80090F24;
    do {
        *(u16 *)(entry + 0x20) = 0;
        *(u16 *)(entry + 0x22) = 0;
        *(u16 *)(entry + 0x24) = 0x10;
        *(u16 *)(entry + 0x26) = 0x10;
        j = 0;
        do {
            prim = entry + 0x28 + j * 0x28;
            SetPolyFT4((POLY_FT4 *)prim);
            SetShadeTex(prim, 1);
            *(u16 *)(prim + 0x16) = GetTPage(tex[0], 0, tex[-6], tex[-5]);
            *(u8 *)(prim + 0xC) = tex[-2];
            *(u8 *)(prim + 0xD) = tex[-1];
            *(u8 *)(prim + 0x14) = tex[-2] + 0xF;
            *(u8 *)(prim + 0x15) = tex[-1];
            *(u8 *)(prim + 0x1C) = tex[-2];
            *(u8 *)(prim + 0x1D) = tex[-1] + 0xF;
            *(u8 *)(prim + 0x24) = tex[-2] + 0xF;
            *(u8 *)(prim + 0x25) = tex[-1] + 0xF;
            j++;
        } while (j < 4);
        entry += 0xC8;
        i++;
    } while (i < 0x18);

    i = 0;
    tex = D_80091004;
    do {
        *(u16 *)(entry + 0x22) = 1;
        *(u16 *)(entry + 0x24) = 0x80;
        *(u16 *)(entry + 0x20) = 0;
        *(u16 *)(entry + 0x26) = 0x100;
        j = 0;
        do {
            prim = entry + 0x28 + j * 0x28;
            SetPolyFT4((POLY_FT4 *)prim);
            SetShadeTex(prim, 1);
            *(u16 *)(prim + 0x16) = GetTPage(tex[0], 3, tex[-6], tex[-5]);
            *(u16 *)(prim + 0xE) = GetClut(tex[-4], tex[-3]);
            SetSemiTrans(prim, 1);
            *(u8 *)(prim + 0xC) = tex[-2];
            *(u8 *)(prim + 0xD) = tex[-1];
            *(u8 *)(prim + 0x14) = tex[-2] + 0x3F;
            *(u8 *)(prim + 0x15) = tex[-1];
            *(u8 *)(prim + 0x1C) = tex[-2];
            *(u8 *)(prim + 0x1D) = tex[-1] + 0x3F;
            *(u8 *)(prim + 0x24) = tex[-2] + 0x3F;
            *(u8 *)(prim + 0x25) = tex[-2] + 0x3F;
            j++;
        } while (j < 4);
        entry += 0xC8;
        i++;
    } while (i < 0x18);

    i = 0;
    tex = D_80091004;
    do {
        *(u16 *)(entry + 0x22) = 2;
        *(u16 *)(entry + 0x24) = 0x80;
        *(u16 *)(entry + 0x20) = 0;
        *(u16 *)(entry + 0x26) = 0x100;
        j = 0;
        do {
            prim = entry + 0x28 + j * 0x28;
            SetPolyFT4((POLY_FT4 *)prim);
            SetShadeTex(prim, 1);
            *(u16 *)(prim + 0x16) = GetTPage(tex[0], 3, tex[-6], tex[-5]);
            *(u16 *)(prim + 0xE) = GetClut(tex[-4], tex[-3]);
            SetSemiTrans(prim, 1);
            *(u8 *)(prim + 0xC) = tex[-2];
            *(u8 *)(prim + 0xD) = tex[-1];
            *(u8 *)(prim + 0x14) = tex[-2] + 0x3F;
            *(u8 *)(prim + 0x15) = tex[-1];
            *(u8 *)(prim + 0x1C) = tex[-2];
            *(u8 *)(prim + 0x1D) = tex[-1] + 0x3F;
            *(u8 *)(prim + 0x24) = tex[-2] + 0x3F;
            *(u8 *)(prim + 0x25) = tex[-2] + 0x3F;
            j++;
        } while (j < 4);
        i++;
        entry += 0xC8;
    } while (i < 0x18);
}

void func_80035E8C(s32 *src, s32 *outX, s32 *outY) {
    s32 value;

    value = MathFixedDivide(src[0], src[2]);
    outX[0] = (MathMultiplyFixed16(value & -0x10, 0xD00000) >> 16) + 0xA0;
    value = MathFixedDivide(src[1], src[2]);
    outY[0] =
        (MathMultiplyFixed16(value & -0x10, 0xD00000) >> 16) + D_800A2F3C[0];
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80035F28);

extern s32 D_800B60C8[];
extern u8 D_800A2ED9[];
extern u8 D_800A2ED8Arr[];
extern void func_80035F28(u8 *);

asm(".globl D_800A2ED8Arr\nD_800A2ED8Arr = D_800A2ED8");

/* Per-frame update of the 0xC8-stride entry table at D_800B60C8: builds a
 * camera-relative SVECTOR, ages the active counter, transforms the position
 * and hands visible entries to func_80035F28. */
void func_80036264(void) {
    u8 *p;
    s32 i;
    register s32 dz asm("v0");
    s32 *camera;
    s32 flagval;
    register s32 cx asm("a1");
    register s32 cy asm("a2");
    register s32 dx asm("a3");
    register s32 dy asm("t0");
    u16 count;
    SVECTOR sv;
    long flag;

    for (p = (u8 *)D_800B60C8, i = 0; i < 0x48; i++, p += 0xC8) {
        if (*(s16 *)(p + 0x20) == 0) {
            continue;
        }
        dz = *(s32 *)(p + 0x10);
        camera = (s32 *)D_800A38AC[0];
        flagval = D_800A2ED4[0];
        cx = camera[0];
        cy = camera[1];
        dz = dz - camera[2];
        dx = *(s32 *)(p + 0x8) - cx;
        dy = *(s32 *)(p + 0xC) - cy;
        sv.vz = dz;
        sv.vx = dx;
        sv.vy = dy;
        if (flagval == 0 && D_800A2ED8Arr[0] == 0 && D_800A2ED9[0] == 0) {
            count = *(u16 *)(p + 0x20) - 1;
            *(s16 *)(p + 0x20) = count;
            if (*(s16 *)(p + 0x22) >= 2) {
                *(s32 *)(p + 0x10) =
                    *(s32 *)(p + 0x10) + ((0x2D - (s16)count) * 2);
            } else {
                if ((s16)count >= 6) {
                    *(s32 *)(p + 0x10) = *(s32 *)(p + 0x10) + 5;
                } else {
                    *(s32 *)(p + 0x10) = *(s32 *)(p + 0x10) - 5;
                }
            }
        }
        dz = dx >= 0 ? dx < 0x3E81 : -dx < 0x3E81;
        if (dz) {
            dz = dy >= 0 ? dy < 0x3E81 : -dy < 0x3E81;
            if (dz) {
                RotTrans(&sv, (VECTOR *)(p + 0x14), &flag);
                if (*(s32 *)(p + 0x1C) >= 0x14) {
                    if (2 * *(s32 *)(p + 0x1C) < (*(s32 *)(p + 0x14) < 0
                                                      ? -*(s32 *)(p + 0x14)
                                                      : *(s32 *)(p + 0x14))) {
                        continue;
                    }
                    if (2 * *(s32 *)(p + 0x1C) < (*(s32 *)(p + 0x18) < 0
                                                      ? -*(s32 *)(p + 0x18)
                                                      : *(s32 *)(p + 0x18))) {
                        continue;
                    }
                    func_80035F28(p);
                }
            }
        }
    }
}

extern s32 D_800B60E8[];
void func_8003644C(s32 index, s32 arg1, s32 arg2, s32 arg3) {
    u8 *entry;
    u8 *base;
    s32 i;
    s32 flag;
    s32 longValue;
    s32 shortValue;

    i = 0;
    flag = (index < 2);
    longValue = 0x19;
    shortValue = 0xA;
    base = (u8 *)D_800B60E8 + index * 0x12C0;
    for (i = 0; i < 0x18; i++) {
        entry = base + i * 0xC8;
        if (*(s16 *)(entry + 0) == 0) {
            *(s32 *)(entry - 0x18) = arg1;
            *(s32 *)(entry - 0x14) = arg2;
            *(s32 *)(entry - 0x10) = arg3;
            if (flag == 0) {
                *(s16 *)(entry + 0) = longValue;
            } else {
                *(s16 *)(entry + 0) = shortValue;
            }
            return;
        }
    }
}

extern s32 D_800AEE50[];
extern s32 D_800B60C8[];
void func_800364C4(void) {
    s32 i;
    s32 offset;
    u8 *dst;
    u8 *src;

    for (i = 0, dst = (u8 *)D_800AEE50, offset = 0, src = (u8 *)D_800B60C8;
         i < 0x48; offset += 0x28, i++, src += 0xC8) {
        *(Primitive40 *)(offset + (u32)dst) = *(Primitive40 *)src;
    }
}

extern s32 D_800AEE50[];
extern s32 D_800B60C8[];
void func_80036540(void) {
    s32 i;

    for (i = 0; i < 0x48; i++) {
        *(Primitive40 *)((u8 *)D_800B60C8 + i * 0xC8) =
            *(Primitive40 *)((u8 *)D_800AEE50 + i * 0x28);
    }
}

#ifdef NON_MATCHING
extern s32 D_800B7398[];
void func_800365B8(s32 *out) {
    s32 i;
    s32 count;
    u8 *entry;
    s32 value;
    s32 temp;

    count = 0;
    entry = (u8 *)D_800B7398;
    for (i = 0; i < 0x18; i++, entry += 0xC8) {
        if (*(s16 *)((u32)entry + 0x10) == 0) {
            continue;
        }
        value = *out;
        value = (value & -0x800) | ((*(s32 *)((u32)entry - 8) >> 7) & 0x7FF);
        *out = value;
        value = (value & 0xFFC007FF) |
                (((*(s32 *)((u32)entry - 4) >> 7) & 0x7FF) << 11);
        *out = value;
        temp = *(s32 *)entry;
        value = (value & 0x3FFFFF) | ((temp / 16) << 22);
        *out = value;
        out = out + 1;
        count = count + 1;
        if (count >= 0x14) {
            return;
        }
    }
    *out = 0;
}
#else
extern s32 D_800B7398[];
void func_800365B8(s32 *out) {
    s32 i;
    s32 count;
    s32 mask1;
    s32 mask2;
    s32 mask3;
    u8 *entry;
    s32 value;
    s32 temp;

    count = 0;
    i = 0;
    mask1 = -0x800;
    mask2 = 0xFFC007FF;
    mask3 = 0x3FFFFF;
    entry = (u8 *)D_800B7398;
head:
    if (*(s16 *)(entry + 0x10) == 0) {
        goto tail;
    }
    value = *out;
    value = (value & mask1) | ((*(s32 *)(entry - 8) >> 7) & 0x7FF);
    *out = value;
    value = (value & mask2) | (((*(s32 *)(entry - 4) >> 7) & 0x7FF) << 11);
    *out = value;
    temp = *(s32 *)entry;
    if (temp < 0) {
        temp = temp + 15;
    }
    value = (value & mask3) | ((temp >> 4) << 22);
    *out = value;
    out = out + 1;
    count = count + 1;
tail:
    i = i + 1;
    if (i < 0x18) {
        goto check;
    }
    *out = 0;
    return;
check:
    if (count < 0x14) {
        entry = entry + 0xC8;
        goto head;
    }
}

#endif

extern u8 D_800B7388Base[] asm("D_800B7388.NON_MATCHING");
extern u8 D_800B60C8Base[] asm("D_800B60C8.NON_MATCHING");
extern s32 D_800A2ED4[];

void func_8003667C(u32 *list) {
    u8 *p;
    s32 i;
    s32 tmp;
    s32 flag;
    s32 v;

    p = D_800B7388Base;
    i = 0;
    for (; i < 0x14; i++, list++) {
        if (*list == 0) {
            while (i < 0x18) {
                *(s16 *)(p + 0x20) = 0;
                i++;
                p += 0xC8;
            }
            p = D_800B60C8Base;
            i = 0x17;
            do {
                *(s16 *)(p + 0x20) = 0;
                p += 0xC8;
                i--;
            } while (i >= 0);
            return;
        }
        flag = D_800A2ED4[0];
        *(s16 *)(p + 0x20) = 5;
        if (flag == 0) {
            extern u32 RandomGetScaled16(s32);
            tmp = (*list & 0x7FF) << 7;
            if ((s32)RandomGetScaled16(0x20) < 0) {
                v = tmp - RandomGetScaled16(0x20);
            } else {
                v = tmp + RandomGetScaled16(0x20);
            }
            *(s32 *)(p + 8) = v;
            tmp = ((*list >> 11) & 0x7FF) << 7;
            if ((s32)RandomGetScaled16(0x20) < 0) {
                v = RandomGetScaled16(0x20);
                v = tmp - v;
            } else {
                v = tmp + RandomGetScaled16(0x20);
            }
            *(s32 *)(p + 0xC) = v;
            *(s32 *)(p + 0x10) =
                ((s32)*list >> 22) * 0x10 + RandomGetScaled16(8);
        }
        p += 0xC8;
    }
}

extern char D_8008D0AC[];
extern char D_8008D0CC[];

extern void *FileOpenCall367DC(void) asm("FileOpen");
extern s32 FileSeekCall367DC(void *, s32, s32) asm("FileSeek");
extern void FileReadCall367DC(s32, s32, s32, void *) asm("FileRead");
extern void FileCloseCall367DC(s32) asm("FileClose");
void func_800367DC(void) {
    extern s32 D_800A2F54;
    extern s32 D_800AE154[];
    extern s32 D_800B1EA8[];
    extern s32 D_800B60A4[];
    void *handle;
    void *buffer;
    s32 size;
    s32 idx;
    s32 entry;

    handle = FileOpenCall367DC();
    if (handle == NULL) {
        SystemShowFatalError(D_8008D0AC);
    }
    size = FileSeekCall367DC(handle, 0, 2);
    FileSeekCall367DC(handle, 0, 0);
    buffer = HeapAlloc(((size + 0x7FF) >> 11) << 11);
    D_800AE154[D_800A2F54] = (s32)buffer;
    if (buffer == NULL) {
        SystemShowFatalError(D_8008D0CC);
    }
    FileReadCall367DC(D_800AE154[D_800A2F54], 1, size, handle);
    idx = D_800A2F54;
    entry = D_800AE154[idx];
    D_800B60A4[idx] = entry;
    D_800B1EA8[idx] = *(s32 *)entry;
    D_800AE154[idx] = entry + 4;
    D_800A2F54 = idx + 1;
    FileCloseCall367DC((s32)handle);
}

INCLUDE_RODATA("asm/nonmatchings/objects", D_8008D0AC);
INCLUDE_RODATA("asm/nonmatchings/objects", D_8008D0CC);

INCLUDE_ASM("asm/nonmatchings/objects", func_80036900);

s32 func_80036F64(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 idx;
    s32 tA;
    s32 tB;
    s32 dx;
    s32 dy;

    idx = (*((s16 *)(arg1 + 0x114))) << 2;
    dx = *(s32 *)arg0 - *(s32 *)arg1;
    tA = *((s32 *)(idx + ((u32)D_800A3A2CAbsolute[0])));
    dy = *(s32 *)(arg0 + 4) - *(s32 *)(arg1 + 4);
    tB = *((s32 *)(idx + ((u32)D_800A3A34Absolute[0])));
    return arg2 < ((tA * dx - tB * dy) >> 16);
}

extern s32 D_800A3A2CAbsolute[];
extern s32 D_800A3A34Absolute[];

s32 func_80036FC8(s32 *a, s32 *b) {
    s32 index;
    s32 t1;
    s32 t2;
    s32 x;
    s32 y;

    index = *(s16 *)(((u8 *)b) + 0x114) << 2;
    x = a[0] - b[0];
    t1 = *(s32 *)(index + (u32)D_800A3A34Absolute[0]);
    y = a[1] - b[1];
    t2 = *(s32 *)(index + (u32)D_800A3A2CAbsolute[0]);
    return ((t1 * x + t2 * y) >> 16) > 0;
}

#ifdef NON_MATCHING
extern s32 D_800BE974[];
s32 func_8003702C(u8 *objectA, u8 *objectB) {
    s32 limit;
    s32 diff;
    s32 a;
    s32 b;

    limit = D_800BE974[0];
    diff = *(s16 *)(objectA + 0x1E0) - *(s16 *)(objectB + 0x1E0);
    if (diff >= 0) {
        if (diff < (limit >> 1)) {
            return diff;
        }
    } else {
        if ((limit >> 1) > -diff) {
            return diff;
        }
    }
    a = *(s16 *)(objectA + 0x1E0);
    b = *(s16 *)(objectB + 0x1E0);
    if (b < a) {
        b = b + limit;
        if (b - a < 0) {
            return b - a;
        }
        return a - b;
    }
    a = a + limit;
    if (a - b >= 0) {
        return a - b;
    }
    return b - a;
}
#else
#ifdef NON_MATCHING
/*
 * WALL (w9d): two diffs. (1) gcc copies arg0 to a2 at entry (`move
 * a2,a0`) because the s16 fields are read twice (once for the early
 * |diff| check, once for the wraparound path) and gcc 2.7.2 gives the
 * pointer its own callee pseudo; retail reuses a0/a1 as both base and
 * lh destination. (2) the inner `if (diff < half) return diff;`
 * compiles beqz-to-common where retail has bnez-to-return (branch
 * sense inverted; the ?: spelling was not tried in time). The wrap
 * path shape is right: y >= x vs y < x arms, threshold added to the
 * SMALLER value, sign flip on the negative result. D_800BE974 %lo
 * showed +0x18 drift while this draft was active -- self-inflicted
 * wrong length, not a split problem.
 */
extern s32 D_800BE974[];

s32 func_8003702C(s32 arg0, s32 arg1) {
    s32 diff;
    s32 half;
    s32 x;
    s32 y;

    diff = *(s16 *)(arg0 + 0x1E0) - *(s16 *)(arg1 + 0x1E0);
    half = D_800BE974[0] >> 1;
    if (diff >= 0) {
        if (diff < half) {
            return diff;
        }
    } else {
        if (-diff < half) {
            return diff;
        }
    }
    x = *(s16 *)(arg0 + 0x1E0);
    y = *(s16 *)(arg1 + 0x1E0);
    if (y < x) {
        y += D_800BE974[0];
        diff = x - y;
        if (diff < 0) {
            return diff;
        }
        return x - y;
    }
    x += D_800BE974[0];
    diff = x - y;
    if (diff >= 0) {
        return diff;
    }
    return y - x;
}
#endif

extern s32 D_800BE974[];

s32 func_8003702C(u8 *objectA, u8 *objectB) {
    s32 limit;
    s32 diff;
    s32 half;
    s32 a;
    s32 b;

    limit = D_800BE974[0];
    diff = *(s16 *)(objectA + 0x1E0) - *(s16 *)(objectB + 0x1E0);
    half = limit >> 1;
    if ((diff < 0 ? -diff : diff) < half) {
        return diff;
    }
    a = *(s16 *)(objectA + 0x1E0);
    b = *(s16 *)(objectB + 0x1E0);
    if (b < a) {
        b = b + limit;
        if (b - a < 0) {
            return b - a;
        }
        return a - b;
    }
    a = a + limit;
    if (a - b >= 0) {
        return a - b;
    }
    return b - a;
}

#endif

#ifdef NON_MATCHING
extern s32 D_800BE974[];
s32 func_800370B8(s32 a, s32 b) {
    s32 limit;
    s32 diff;

    limit = D_800BE974[0];
    diff = a - b;
    if (diff >= 0) {
        if (diff < (limit >> 1)) {
            return diff;
        }
    } else {
        if (-diff < (limit >> 1)) {
            return diff;
        }
    }
    if (b < a) {
        b = b + limit;
        if (b - a < 0) {
            return b - a;
        }
        return a - b;
    }
    a = a + limit;
    if (a - b >= 0) {
        return a - b;
    }
    return b - a;
}
#else
extern s32 D_800BE974[];

s32 func_800370B8(s32 a, s32 b) {
    s32 limit;
    s32 diff;
    s32 half;

    limit = D_800BE974[0];
    diff = a - b;
    half = limit >> 1;
    if ((diff < 0 ? -diff : diff) < half) {
        return diff;
    }
    if (b < a) {
        b = b + limit;
        if (b - a < 0) {
            return b - a;
        }
        return a - b;
    }
    a = a + limit;
    if (a - b >= 0) {
        return a - b;
    }
    return b - a;
}

#endif

#ifdef NON_MATCHING
/*
 * WALLS: (1) retail re-reads *(s16 *)(object + 0x92) once per product
 * (three lh) — plain reads CSE into one lh and a volatile s16 read
 * emits lhu + sll16/sra16 instead of lh (extends the w5b entry);
 * (2) retail gaps mult and mflo with the next row's lh/lw (two
 * instructions + hazard nops); gcc 2.7.2 binds mult+mflo as one
 * pattern, so mflo lands immediately after mult. Prologue solved:
 * store-first with a volatile second 0x114 read puts the sh in the
 * jal delay slot, though that read is lhu in ours vs lh in retail.
 * Products map 0xB0=prod(0x60), 0xB4=prod(0x6C), 0xB8=prod(0x78);
 * the volatile reloads of 0xB0/B4/B8 before the adds are exact.
 */
void func_8001FAC0(u8 *, s32);
void func_8001FB28(u8 *, s16);
void func_80037130(u8 *object) {
    s32 prod0;
    s32 prod1;
    s32 prod2;
    s32 sum0;
    s32 sum1;
    s32 sum2;

    *(s16 *)(object + 0x116) = *(volatile s16 *)(object + 0x114) * 4;
    func_8001FAC0(object, *(s16 *)(object + 0x114) * 4);
    func_8001FB28(object, *(s16 *)(object + 0x104));
    prod0 = *(volatile s16 *)(object + 0x92) * *(s32 *)(object + 0x60);
    prod1 = *(volatile s16 *)(object + 0x92) * *(s32 *)(object + 0x6C);
    prod2 = *(volatile s16 *)(object + 0x92) * *(s32 *)(object + 0x78);
    *(s32 *)(object + 0xB0) = prod0 >> 16;
    *(s32 *)(object + 0xB4) = prod1 >> 16;
    *(s32 *)(object + 0xB8) = prod2 >> 16;
    sum0 = *(s32 *)(object + 0x0) + *(volatile s32 *)(object + 0xB0);
    sum1 = *(s32 *)(object + 0x4) + *(volatile s32 *)(object + 0xB4);
    sum2 = *(s32 *)(object + 0x8) + *(volatile s32 *)(object + 0xB8);
    *(s32 *)(object + 0x0) = sum0;
    *(s32 *)(object + 0x4) = sum1;
    *(s32 *)(object + 0x8) = sum2;
}
#else
void func_8001FAC0(u8 *, s32);
void func_8001FB28(u8 *, s32);
void func_80037130(u8 *object) {
    *(s16 *)(object + 0x116) = *(s16 *)(object + 0x114) * 4;
    func_8001FAC0(object, *(s16 *)(object + 0x114) * 4);
    func_8001FB28(object, *(s16 *)(object + 0x104));
    *(s32 *)(object + 0xB0) =
        (*(s32 *)(object + 0x60) * *(s16 *)(object + 0x92)) >> 16;
    *(s32 *)(object + 0xB4) =
        (*(s32 *)(object + 0x6C) * *(s16 *)(object + 0x92)) >> 16;
    *(s32 *)(object + 0xB8) =
        (*(s32 *)(object + 0x78) * *(s16 *)(object + 0x92)) >> 16;
    *(s32 *)(object + 0x0) += *(s32 *)(object + 0xB0);
    *(s32 *)(object + 0x4) += *(s32 *)(object + 0xB4);
    *(s32 *)(object + 0x8) += *(s32 *)(object + 0xB8);
}

#endif

extern s32 D_800A39E0[];
extern s32 D_800BE974[];
extern s32 D_800BE980[];

s32 func_80037204(u8 *obj) {
    extern u8 *D_800A3960[];
    extern void *D_800BE980z[] asm("D_800BE980");
    u8 *node;
    s32 tmp;
    s32 heading;
    s32 num;
    s32 den;
    s32 rem;
    u8 *base;
    register s32 t asm("v1");
    register s32 idx asm("v0");
    u8 *b2;
    u8 *addr;
    u8 *entry;
    u16 counter;
    u16 val;

    node = D_800A3878w15[0];
    tmp = *(s32 *)(obj + 0x3CC);
    *(s32 *)(obj + 0x414) = -1;
    *(s32 *)(obj + 0x354) = (s32)func_80025594;
    *(s32 *)(obj + 0x90) = 0;
    *(s32 *)(obj + 0x84) = 0;
    if (tmp > 0) {
        goto fail;
    }
    while (node != 0 && *(s16 *)(node + 0x1EC) == 0) {
        if (func_8003702C(node, obj) < 0) {
            if (-func_8003702C(node, obj) < 25) {
                goto fail;
            }
        } else {
            if (func_8003702C(node, obj) < 25) {
            fail:
                return 0;
            }
        }
        node = *(u8 **)(node + 0x3E0);
    }
    if (*(u8 *)(obj + 0xF4) != 0) {
        func_80041848(obj, 12);
        heading = *(s16 *)(obj + 0x28A);
        *(u8 *)(obj + 0xF4) = 0;
        num = D_800A39E0[0] + heading;
        den = D_800BE974[0];
        rem = num % den;
        base = (u8 *)D_800BE980[0];
        idx = rem * 0x90;
        entry = base + idx;
        t = *(s32 *)(entry + 0x48);
        *(s32 *)(obj + 0x0) = t;
        t = *(s32 *)(entry + 0x4C);
        *(s32 *)(obj + 0x4) = t;
        b2 = (u8 *)D_800BE980z[0];
        val = *(u16 *)(idx + (s32)b2 + 0x10);
        counter = *(u16 *)(obj + 0x1D6);
        counter = counter - 2;
        *(u16 *)(obj + 0x1D6) = counter;
        *(u16 *)(obj + 0x104) = val;
        *(u16 *)(obj + 0x114) = val;
        if ((s16)counter < 0) {
            *(u16 *)(obj + 0x1D6) = 0;
        }
        if (obj == D_800A3960w15[0]) {
            D_800A3960[0] = 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_800373B4);

INCLUDE_ASM("asm/nonmatchings/objects", func_80038D78);

s32 func_80039008(u8 *arg0, u8 *arg1) {
    extern s32 func_8003702C();
    volatile s32 pad[4];
    s32 result;

    if (*(s32 *)(arg0 + 0x90) <= *(s32 *)(arg1 + 0x90)) {
        return 0;
    }
    result = func_8003702C(arg0, arg1);
    if (result >= 2) {
        return 0;
    }
    return (*(s32 *)(arg0 + 0x90) - *(s32 *)(arg1 + 0x90)) / 20 >> 16 >= result;
}

extern u8 D_800A2F84w44[] asm("D_800A2F84");
extern s32 D_800A3730, D_800A3734;

void func_800390A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 idx;
    register s32 i asm("a3");
    s32 n;
    s32 rem;
    u8 *p;
    u16 heading;
    s32 index;
    s32 var_a3;
    register s32 temp_t0 asm("t0");
    s32 temp_v1;
    s32 var_a0;
    s32 x;
    s32 y;
    register s32 newY asm("v0");
    s32 old30;
    s32 old34;
    s8 check;

    idx = *(s16 *)((u8 *)arg1 + 0x1E0);
    if (idx == -1) {
        return;
    }
    asm("" : "=r"(i) : "0"(idx));
    n = D_800BE974[0] - 1;
    rem = (i + n) % D_800BE974[0];
    p = (u8 *)D_800BE980[0] + i * 0x90;
    *(s16 *)((u8 *)arg0 + 0x24E) = rem;
    heading = *(u16 *)(p + 0x10);
    index = ((0x400 - heading) & 0x3FF) << 2;
    temp_t0 = *(s32 *)(index + (u32)D_800A3A2CAbsolute[0]);
    temp_v1 = *(s32 *)(index + (u32)D_800A3A34Absolute[0]);
    if (*(s16 *)((u8 *)arg0 + 0x288) != 0) {
        var_a3 = (temp_v1 * 0x6D6) >> 16;
        var_a0 = (temp_t0 * 0x6D6) >> 16;
        arg2 = D_800A2F84w44[0];
    } else {
        var_a3 = (temp_v1 * 0x6D6) >> 16;
        var_a0 = (temp_t0 * 0x6D6) >> 16;
    }
    if (*(s16 *)((u8 *)arg0 + 0x288) == 0) {
        check = *(s8 *)((u8 *)arg1 + 0x203);
        if (check >= 0) {
            if (check >= 7) {
                goto bad;
            }
            goto ok;
        } else {
            if (-check < 7) {
                goto ok;
            }
        }
    bad:
        *(s16 *)((u8 *)arg0 + 0x24E) = -1;
        return;
    }
ok:
    x = *(s32 *)((u8 *)arg1);
    y = *(s32 *)((u8 *)arg1 + 4);
    if ((arg2 & 0xFF) == 0) {
        D_800A3730 = x + var_a3;
        newY = y + var_a0;
    } else {
        D_800A3730 = x - var_a3;
        newY = y - var_a0;
    }
    *(volatile s32 *)&D_800A3734 = newY;
    old30 = *(volatile s32 *)&D_800A3730;
    old34 = *(volatile s32 *)&D_800A3734;
    D_800A3730 = var_a3;
    D_800A3734 = var_a0;
    *(s32 *)((u8 *)arg0 + 0x250) = old30;
    *(s32 *)((u8 *)arg0 + 0x254) = old34;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80039274);

INCLUDE_ASM("asm/nonmatchings/objects", func_800395BC);

extern s32 D_800AE154[];

void func_80039B74(s32 *arg0, s32 arg1) {
    u8 *obj = (u8 *)arg0;
    s16 idx;
    s32 result;
    s32 base;
    s32 off12;
    register s32 objX asm("a1");
    s32 entryX;
    s32 entryY;
    register s32 objY asm("v1");
    s32 w;
    s32 value;
    s32 tableA;
    s32 prod;
    register s32 prod2 asm("v0");
    register s32 neg asm("v1");
    u8 *eptr;
    u8 *entryAddr;
    u8 *ptr;

    idx = *(s16 *)(obj + 0x1E0);
    if (idx == -1) {
        result = 10;
    } else {
        base = D_800AE154[arg1];
        off12 = idx * 12;
        objX = *(s32 *)obj;
        eptr = *(u8 **)D_800BE980;
        entryAddr = (u8 *)(off12 + base);
        entryX = *(s32 *)entryAddr;
        ptr = eptr + idx * 0x90;
        w = (0x400 - *(u16 *)(ptr + 0x10)) & 0x3FF;
        tableA = ((s32 **)D_800A3A34Absolute)[0][w];
        prod = tableA * (objX - entryX);
        entryY = *(s32 *)(entryAddr + 4);
        objY = *(s32 *)(obj + 4);
        prod2 = ((s32 **)D_800A3A2CAbsolute)[0][w] * (objY - entryY);
        value = prod + prod2;
        neg = -(value >> 16);
        if (neg < 0) {
            result = (neg - 0xFA) / 500;
        } else {
            result = (neg + 0xFA) / 500;
        }
    }
    *(u8 *)(obj + 0x206) = result;
}

s8 func_80039C68(u8 *arg0, s32 arg1, s32 arg2) {
    s32 heading;
    s32 x;
    s32 index;
    s32 y;

    heading = *(u16 *)(arg0 + 0x10);
    x = *(s32 *)(arg0 + 0x14);
    index = (0x400 - heading) & 0x3FF;
    y = *(s32 *)(arg0 + 0x18);
    return -((((s32 **)D_800A3A34Absolute)[0][index] * (arg1 - x) +
              ((s32 **)D_800A3A2CAbsolute)[0][index] * (arg2 - y)) >>
             16) /
           250;
}

extern s32 D_800BE980[];

void func_80039CF4(void) {
    u8 *node;
    u8 *track;
    s32 index;
    s32 id;
    s32 angle;
    s32 heading;
    s32 objX;
    s32 entryX;
    s32 entryY;
    s32 objY;
    s32 tableA;
    s32 tableB;
    s32 prodA;
    s32 value;

    node = (u8 *)D_800A3984[0] + 0x500;
    while (node != NULL) {
        id = *(s16 *)(node + 0x1E0);
        if (id != -1) {
            track = *(u8 **)D_800BE980;
            track += id * 0x90;
            heading = *(u16 *)(track + 0x10);
            objX = *(s32 *)node;
            entryX = *(s32 *)(track + 0x14);
            angle = heading;
            index = ((0x400 - angle) & 0x3FF) << 2;
            tableA = *(s32 *)(index + (u32)D_800A3A34Absolute[0]);
            prodA = tableA * (objX - entryX);
            objY = *(s32 *)(node + 4);
            entryY = *(s32 *)(track + 0x18);
            tableB = *(s32 *)(index + (u32)D_800A3A2CAbsolute[0]);
            value = prodA + tableB * (objY - entryY);
            *(s8 *)(node + 0x203) = (-(value >> 16)) / 250;
        }
        node = *(u8 **)(node + 0x3E0);
    }
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80039DDC);

extern s32 D_800A2F4C;
extern s32 D_800A36A4;
extern u8 D_800A33E4;
extern u8 D_800A2F58;
extern s32 D_800A2F00nm[] asm("D_800A2F00.NON_MATCHING");
extern s32 D_800A2EFCnm[] asm("D_800A2EFC.NON_MATCHING");
extern s16 D_800A3910nm[] asm("D_800A3910.NON_MATCHING");
extern void func_800373B4(u8 *);
extern void func_8002A1FC(u8 *);

void func_8003A440(void) {
    u8 *node;
    s32 counter;
    s32 one;

    node = D_800A3878w15[0];
    D_800A2F4C = 12;
    if (node != NULL) {
        counter = 10;
        do {
            func_800373B4(node);
            if (*(s16 *)(node + 0x1EC) == 0) {
                func_8002AD20((s32 *)node, *(s16 *)(node + 0x114));
                if (D_800A2EACAbsolute[0] == 0) {
                    if (D_800A36A4 < 11) {
                        if (D_800A36A4 == counter) {
                            one = 1;
                            *(u8 *)(node + 0x20C) = one;
                            one = 0;
                        }
                        func_8002A1FC(node);
                    }
                }
                *(s32 *)(node + 0x40C) = *(s32 *)(node + 0x90);
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != NULL);
    }
    if (D_800A36A4-- > 0) {
        return;
    }
    D_800A2F00nm[0] = 1;
    D_800A2EFCnm[0] = 0x50;
    D_800A2F4C = 0x14;
    D_800A2F58 = 0;
    D_800A3910nm[0] = 0;
    D_800A2EE4w15[0] = D_800A33E4;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8003A54C);

extern void func_8003ABC0();
extern s16 D_80098254[];

void func_8003A880(s32 car) {
    s32 old;
    s32 new;
    s32 idx;
    s32 turn;
    s32 t;
    s32 t2;
    s32 t3;
    s32 t4;

    if (*(s16 *)(car + 0x102) != 0) {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = -D_80098254[idx];
    } else {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = D_80098254[idx];
    }
    *(u16 *)(car + 0x114) = (*(u16 *)(car + 0x114) + turn + 0x400) & 0x3FF;
    t = *(s32 *)(car + 0x90);
    t2 = t - (t >> 5);
    *(s32 *)(car + 0x90) = t2;
    if (turn != 0) {
        return;
    }
    *(u16 *)(car + 0x1BC) = 0x32;
    t3 = *(s32 *)(car + 0x90);
    t4 = t3 - 0x320000;
    *(s32 *)(car + 0x90) = t4;
    if (t4 < 0) {
        *(s32 *)(car + 0x90) = 0;
    }
    ObjectSetCallbackIfAllowed((Batch0CallbackObject *)car, func_8003ABC0);
}

extern void func_8003ABC0();
extern s16 D_80098294[];

void func_8003A950(s32 car) {
    s32 old;
    s32 new;
    s32 idx;
    s32 turn;
    s32 t;
    s32 t2;
    s32 t3;
    s32 t4;

    if (*(s16 *)(car + 0x102) != 0) {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = -D_80098294[idx];
    } else {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = D_80098294[idx];
    }
    *(u16 *)(car + 0x114) = (*(u16 *)(car + 0x114) + turn + 0x400) & 0x3FF;
    t = *(s32 *)(car + 0x90);
    t2 = t - (t >> 5);
    *(s32 *)(car + 0x90) = t2;
    if (turn != 0) {
        return;
    }
    *(u16 *)(car + 0x1BC) = 0x32;
    t3 = *(s32 *)(car + 0x90);
    t4 = t3 - 0x320000;
    *(s32 *)(car + 0x90) = t4;
    if (t4 < 0) {
        *(s32 *)(car + 0x90) = 0;
    }
    ObjectSetCallbackIfAllowed((Batch0CallbackObject *)car, func_8003ABC0);
}

extern s16 D_800982D4[];
extern void func_8003ABC0();

void func_8003AA20(s32 car) {
    s32 old;
    s32 new;
    s32 idx;
    s32 turn;
    s32 t;
    s32 t2;
    s32 t3;
    s32 t4;

    if (*(s16 *)(car + 0x102) != 0) {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = -D_800982D4[idx];
    } else {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = D_800982D4[idx];
    }
    *(u16 *)(car + 0x114) = (*(u16 *)(car + 0x114) + turn + 0x400) & 0x3FF;
    t = *(s32 *)(car + 0x90);
    t2 = t - (t >> 7);
    *(s32 *)(car + 0x90) = t2;
    if (turn != 0) {
        return;
    }
    *(u16 *)(car + 0x1BC) = 0;
    t3 = *(s32 *)(car + 0x90);
    t4 = t3 - 0x320000;
    *(s32 *)(car + 0x90) = t4;
    if (t4 < 0) {
        *(s32 *)(car + 0x90) = 0;
    }
    ObjectSetCallbackIfAllowed((Batch0CallbackObject *)car, func_8003ABC0);
}

extern s16 D_80098328[];

void func_8003AAEC(s32 car) {
    s32 old;
    s32 new;
    s32 idx;
    s32 turn;
    s32 t;
    s32 t2;
    s32 mode;

    if (*(s16 *)(car + 0x102) != 0) {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = -D_80098328[idx];
    } else {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = D_80098328[idx];
    }
    *(u16 *)(car + 0x114) = (*(u16 *)(car + 0x114) + turn + 0x400) & 0x3FF;
    t = *(s32 *)(car + 0x90);
    t2 = t - (t >> 9);
    *(s32 *)(car + 0x90) = t2;
    if (*(u16 *)(car + 0x360) == 2) {
        *(s32 *)(car + 0x90) = t2 - (t2 >> 3);
    }
    if (turn != 0) {
        return;
    }
    *(u16 *)(car + 0x1BC) = 0;
    ObjectSetCallbackIfAllowed((Batch0CallbackObject *)car, func_80025594);
}

extern void func_80025594(u8 *);

void func_8003ABC0(u8 *object) {
    *(u16 *)(object + 0x1BC) += 1;
    *(u32 *)(object + 0x90) = 0;
    if ((*(u16 *)(object + 0x3A4) & 0xF) == 0) {
        if (*(s16 *)(object + 0x1BC) >= 0x65) {
            *(u16 *)(object + 0x1BC) = 0;
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_80025594);
        }
    }
}

extern void func_8003AA20();
extern void func_8003A880();
extern void func_8003A950();
extern void func_8003AAEC();

void func_8003AC18(u8 *object, s32 arg1, s32 arg2, s32 arg3) {
    if (*(s16 *)(object + 0x1EC) == 1) {
        *(s16 *)(object + 0x1BC) = 0;
        if ((arg2 = arg2) > 0 && arg3 > 0) {
            *(s16 *)(object + 0x102) = 1;
        } else if ((arg2 = arg2) < 0 && arg3 < 0) {
            *(s16 *)(object + 0x102) = 1;
        } else {
            *(s16 *)(object + 0x102) = 0;
        }
        if (arg1 >= 0xC9) {
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_8003AA20);
            ((void (*)(void *, s32))func_8002F66C)(object, 1);
            func_80041564(object, 0x29);
        } else if (arg1 >= 0xB0) {
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_8003A880);
            func_80041564(object, 0x29);
        } else if (arg1 >= 0x97) {
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_8003A950);
            func_80041564(object, 0x29);
        } else if (arg1 >= 0x3D) {
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_8003AAEC);
        }
    }
}

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

INCLUDE_ASM("asm/nonmatchings/objects", func_8003AD94);

extern s32 D_800A2E94[];
extern s32 D_800A2EB0Absolute[];
extern s32 D_800A2EF4[];
extern u8 D_800A2F65;
extern s32 D_800A35E0[];
extern s32 D_800BE980[];

void func_8003B464(void) {
    u8 *obj;
    s32 scaled;
    s32 rank;
    s32 startPos;
    s32 next;
    u8 *other;

    if (D_800A2E94[0] == 1) {
        return;
    }
    if (D_800A2EB0Absolute[0] == 1) {
        return;
    }
    obj = (u8 *)D_800A35E0[0];
    while (obj != 0) {
        rank = *(s16 *)(obj + 0x1D6);
        startPos = *(s16 *)(obj + 0x1E0);
        if ((rank = rank) > 0 && startPos >= 0 && *(s8 *)(obj + 0x204) != 1) {
            if (*(s32 *)(obj + 0x3CC) == 0) {
                s32 temp;
                s32 result;
                s32 otherVal;

                temp = D_800A2EF4[0] -
                       *(s32 *)((u8 *)D_800BE980[0] + startPos * 0x90 + 0x50);
                scaled = temp << 3;
                *(s32 *)(obj + 0x264) = temp;
                temp = RandomScaledGet(8);
                if (temp < 0) {
                    result = scaled - RandomScaledGet(8);
                } else {
                    result = scaled + RandomScaledGet(8);
                }
                next = *(s32 *)(obj + 0x3E4);
                *(s32 *)(obj + 0x264) = result;
                other = *(u8 **)(next + 8);
                otherVal = *(s32 *)(other + 0x264);
                if ((u32)otherVal >= (u32)result &&
                    other != (u8 *)D_800A35E0[0]) {
                    *(s32 *)(obj + 0x264) = otherVal + 1;
                }
            } else {
                s32 otherVal;
                s32 objVal;

                next = *(s32 *)(obj + 0x3E4);
                other = *(u8 **)(next + 8);
                if (other == (u8 *)D_800A35E0[0]) {
                    *(s32 *)(other + 0x264) = 0;
                }
                objVal = *(s32 *)(obj + 0x264);
                otherVal = *(s32 *)(other + 0x264);
                if (otherVal >= objVal) {
                    *(s32 *)(obj + 0x264) = otherVal + 1;
                }
            }
        }
        next = *(s32 *)(obj + 0x3E8);
        if (next == 0) {
            break;
        }
        obj = *(u8 **)(next + 8);
    }
    D_800A2F65 = 0;
}

extern s32 D_800BE980[];
extern s32 D_800A3A2CAbsolute[];
extern s32 D_800A3A34Absolute[];

s32 func_8003B5F8(s32 arg0, s32 arg1) {
    volatile s32 pad[2];
    register s32 t2 asm("t2");
    s32 p2;
    register s32 v0 asm("v0");
    register s32 v1 asm("v1");
    register s32 a0 asm("a0");
    register s32 a1 asm("a1");
    register s32 a2 asm("a2");
    register s32 a3 asm("a3");

    v1 = *(s16 *)((u8 *)arg0 + 0x1E0);
    if (arg0 == arg1) {
        return 0;
    }
    if (v1 == -1) {
        return 0;
    }
    a1 = D_800BE980[0];
    v0 = (v1 << 3) + v1;
    v0 = v0 << 4;
    a1 = a1 + v0;
    a0 = *(u16 *)((u8 *)a1 + 0x10);
    v1 = D_800A3A2CAbsolute[0];
    v0 = 0x400;
    a2 = *(s32 *)((u8 *)a1 + 0x14);
    v0 = v0 - a0;
    v0 = v0 & 0x3FF;
    v0 = v0 << 2;
    v1 = v0 + v1;
    asm volatile("" : : "r"(v1));
    a0 = *(s32 *)((u8 *)arg0 + 0);
    a3 = *(s32 *)(u8 *)v1;
    v1 = a0 - a2;
    asm volatile("mult\t%0, %1" : : "r"(a3), "r"(v1) : "hi", "lo");
    v1 = D_800A3A34Absolute[0];
    a0 = *(s32 *)((u8 *)a1 + 0x18);
    v0 = v0 + v1;
    v1 = *(s32 *)((u8 *)arg0 + 4);
    a1 = *(s32 *)(u8 *)v0;
    asm volatile("mflo\t%0" : "=r"(t2) : : "lo");
    v0 = v1 - a0;
    asm volatile("mult\t%0, %1" : : "r"(a1), "r"(v0) : "hi", "lo");
    v0 = *(s32 *)((u8 *)arg1 + 0);
    asm volatile("mflo\t%0" : "=r"(p2) : : "lo");
    v1 = v0 - a2;
    asm volatile("mult\t%0, %1" : : "r"(a3), "r"(v1) : "hi", "lo");
    v0 = *(s32 *)((u8 *)arg1 + 4);
    asm volatile("mflo\t%0" : "=r"(a2) : : "lo");
    v0 = v0 - a0;
    asm volatile("mult\t%0, %1" : : "r"(a1), "r"(v0) : "hi", "lo");
    v1 = t2 - p2;
    v1 = v1 >> 16;
    asm volatile("mflo\t%0" : "=r"(a3) : : "lo");
    v0 = a2 - a3;
    v0 = v0 >> 16;
    return v0 < v1;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8003B6DC);

extern void func_8002D4CC();
extern u8 *D_800A3854Absolute[];
extern s32 D_800BE72C[];
extern s32 D_800BE730[];
extern s16 D_800BE738[];
extern s32 D_800A2F60;
extern s32 D_800A2EACAbsolute[];

void func_8003BCAC(void) {
    s32 count;
    s32 offset;
    u8 *object;

    object = *(u8 **)(((u8 **)D_800A3854Absolute)[9] + 0x3E0);
    count = 0;
    if (object != 0) {
        offset = 0;
        do {
            func_8002D4CC(object);
            *(s32 *)(object + 0) = *(s32 *)((u8 *)D_800BE72C + offset);
            *(s32 *)(object + 4) = *(s32 *)((u8 *)D_800BE730 + offset);
            *(s32 *)(object + 8) = 0;
            func_80022FB8(object, *(s16 *)((u8 *)D_800BE738 + offset));
            object = *(u8 **)(object + 0x3E0);
            count += 1;
            offset += 0x10;
        } while (object != 0);
    }
    object = ((u8 **)D_800A3854Absolute)[9];
    *(s32 *)(object + 0) = *(s32 *)((u8 *)D_800BE72C + count * 0x10);
    *(s32 *)(object + 4) = *(s32 *)((u8 *)D_800BE730 + count * 0x10);
    *(s32 *)(object + 8) = 0;
    func_8002D4CC(object);
    func_80022FB8(object, *(s16 *)((u8 *)D_800BE738 + count * 0x10));
    D_800A2F60 = 0x14;
    func_8001D1E4();
    D_800A2EACAbsolute[0] = 0;
    func_8003B6DC(1);
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8003BDBC);

extern s32 D_800A2EB0Absolute[];
extern s32 D_800A2EA4[];
extern s32 D_800A2EA8[];
extern s32 D_800A2E94[];
extern s32 D_800A35E0[];
extern u8 *D_800A3554[];
extern u8 *D_800A3878nm[] asm("D_800A3878.NON_MATCHING");
extern s32 D_800AE1EC[];
extern u8 D_800BE70C[];
extern u8 D_800B0B1C[];
extern void func_8003BDBC(void);

void func_8003C1CC(void) {
    u8 *car;
    u8 *base;
    u8 *dst;
    s32 *out2;
    s32 *out3;
    u8 *out1;
    s32 off;
    s32 rank;
    s32 idx;
    s32 slot;
    s32 mode;
    u8 *head;
    s32 val;
    s32 laps;

    func_8002F454();
    base = D_800B0B1C;
    if (D_800A2EB0Absolute[0] == 0) {
        rank = 0;
        if (D_800A2EA4[0] == 0) {
            rank = D_800A2EA8[0] >= *(s16 *)(D_800A3554[0] + 0x1D6);
        } else {
            head = D_800A3554[0];
            if (D_800A2EA8[0] >= *(s16 *)(head + 0x1D6) &&
                D_800A2EA8[0] >= *(s16 *)(*(u8 **)(head + 0x3E0) + 0x1D6)) {
                rank = 1;
            }
        }
        if (rank == 1) {
            func_8003BDBC();
        }
        rank = 0;
        if (rank < D_800A2E94[0]) {
            out3 = (s32 *)base;
            off = 0;
            out2 = D_800AE1EC;
            out1 = D_800BE70C;
            idx = 1;
            do {
                car = D_800A3878nm[0];
                slot = idx;
                if (*(s8 *)(car + 0x204) != idx) {
                    do {
                        car = *(u8 **)(car + 0x3E0);
                    } while (*(s8 *)(car + 0x204) != slot);
                }
                *out1 = *(u8 *)(car + 0x376);
                val = *(s32 *)(car + 0x25C);
                mode = D_800A2EA4[0];
                *out2 = val;
                if (mode == 2) {
                    if (*(u8 *)(car + 0xF4) != 0) {
                        if (*(s16 *)(car + 0x1D6) == 0) {
                            dst = (u8 *)(off + (s32)base);
                            asm volatile("" : "=r"(dst) : "0"(dst));
                            *(s32 *)dst =
                                -*(s16 *)((u8 *)D_800A35E0[0] + 0x1D6);
                            goto tailSkip;
                        }
                        goto general;
                    }
                    val = -1;
                } else {
                general:
                    if (*(u8 *)(car + 0xF4) != 0) {
                        laps = *(s16 *)(car + 0x1D6) -
                               *(s16 *)((u8 *)D_800A35E0[0] + 0x1D6);
                        val = laps + 1;
                        if (*(u16 *)(car + 0x41A) != 0) {
                            val = laps;
                        }
                        if (val < 0) {
                            val = val - 1;
                        } else if (*(s8 *)(car + 0x204) == 1) {
                            val = *(s32 *)(car + 0x260) << 3;
                        } else {
                            *out3 = *(s32 *)(car + 0x264);
                            goto tailSkip;
                        }
                    } else {
                        *out3 = -1;
                        goto tailSkip;
                    }
                }
                *out3 = val;
            tailSkip:
                out3 += 1;
                off += 4;
                out2 += 1;
                out1 += 1;
                idx += 1;
                rank += 1;
            } while (rank < D_800A2E94[0]);
        }
    }
}

extern u8 *D_800A3554[];
extern s32 D_800AE1EC[];
extern u8 D_800BE70C[];
extern u8 D_800B9DA4[];
/* A second name keeps cse from sharing one la across the reads. */
extern u8 *D_800A3554nm[] asm("D_800A3554.NON_MATCHING");

/*
 * The search and rebuild loops are goto loops on purpose: without loop notes
 * count's refs aren't weighted, so i outranks it in global-alloc (a1, a2).
 * i is set a third time by count + 1, which keeps sched1 from sinking it.
 */
void func_8003C3FC(void) {
    s32 *words;
    u8 *bytes;
    s32 *p;
    s32 *out;
    s32 *wp;
    u8 *bp;
    u8 *obj;
    s32 limit;
    s32 count;
    s32 i;

    bytes = D_800BE70C;
    words = D_800AE1EC;
    func_8002F454();
    limit = *(s32 *)(D_800A3554[0] + 0x25C);
    count = 0;
    p = words;
head:
    if ((u32)*p >= (u32)limit) {
        goto done;
    }
    count += 1;
    p += 1;
    if (count < 0x17) {
        goto head;
    }
done:
    if (count < 0x17) {
        i = 0x17;
        do {
            bytes[i] = bytes[i - 1];
            words[i] = words[i - 1];
            i -= 1;
        } while (count < i);
    }
    bytes[count] = *(u8 *)(D_800A3554[0] + 0x376);
    obj = D_800A3554nm[0];
    words[count] = *(s32 *)(obj + 0x25C);
    i = count + 1;
    *(u8 *)(obj + 0x204) = i;
    out = (s32 *)D_800B0B1C;
    wp = words;
    bp = bytes;
    count = 0;
loop:
    D_800B9DA4[*bp] = count;
    *out = *wp;
    bp += 1;
    wp += 1;
    out += 1;
    count += 1;
    if (count < 0x18) {
        goto loop;
    }
}
