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
extern u8 D_800A3680[];
extern s32 D_800A397CSmall;
extern void func_80025730(u8 *);
s16 func_80024E90(s32, s32, s32 *, s32 *, s32 *);
extern u8 *D_800A3554[];
extern u8 *D_800A3878w15[] asm("D_800A3878.NON_MATCHING");
extern u8 *D_800A3960w15[] asm("D_800A3960.NON_MATCHING");
void func_800229B8(void);
extern void func_80022CA4(void);
extern char D_800A3038[];
extern s32 D_800A3668Absolute[];
extern s32 D_800A2E08;
extern s32 D_800A3838;
s32 func_800246C0(s32, s32, u8 *);
extern s32 D_800A2E08;
extern s32 D_800A3838;
s32 func_800246C0(s32, s32, u8 *);
void func_80025594();
typedef struct {
    u8 unk0[0x1EC];
    s16 unk1EC;
    u8 unk1EE[0x12];
    s8 unk200;
    u8 unk201[0x153];
    void (*callback)(void);
} Batch0CallbackObject;
extern u8 *D_800A3554[];
extern s32 D_800A2E94[];
s32 func_8003702C(u8 *, u8 *);
void func_800406D0(u8 *, u8 *, s32, s32);
void func_80041848(u8 *, s32);
extern void func_8003644C(s32, s32, s32, s32);
extern void func_8003644C(s32, s32, s32, s32);
extern void func_8001EEC4Args(u8 *, s32);
extern s32 D_800980A4[];
extern s32 D_80098134[];
extern u8 D_80098194[];
extern u8 D_800981E4[];
extern s32 D_800A2E78[];
typedef struct {
    u8 unk0[0x90];
    s32 unk90;
} UnkObject90;
extern void func_80028980(void *);
void func_80028D80(u8 *);
extern u8 D_800A2E18;
typedef struct {
    u8 pad0[0xF6];
    u8 state;
    u8 padF7[0x15];
    u16 count;
} Counter;
typedef struct SelectionState {
    u8 pad0[0xF6];
    u8 unkF6;
    u8 padF7[0x11];
    s16 selectedValue;
    u8 pad10A[2];
    s16 selectionIndex;
} SelectionState;
extern void func_80029150(s32 *);
extern s32 D_800A3A2CAbsolute2[];
extern s32 D_800A3A34Absolute2[];
extern void func_8003644C(s32, s32, s32, s32);
extern void func_8001FAC0(u8 *, s32);
extern s32 D_800A2E1C;
extern s32 D_800A3A04nm[] asm("D_800A3A04.NON_MATCHING");
extern void func_80029CB4(s32 *arg0);
extern void func_80039B74(s32 *arg0, s32 arg1);
extern u8 D_800A3A24w15f[] asm("D_800A3A24.NON_MATCHING");
extern u8 D_800A2EE0w15f[] asm("D_800A2EE0.NON_MATCHING");
extern u8 D_800A3764w15f[] asm("D_800A3764.NON_MATCHING");
extern u8 D_800A372Cw15f[] asm("D_800A372C.NON_MATCHING");
extern s16 D_800A35A4w15f[] asm("D_800A35A4.NON_MATCHING");
extern s32 func_8006E770(u8);
extern void func_8006EB18(u8 *);
extern void func_80044114(u8 *);
extern s32 D_800A2E1C, D_800A2E24;
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
extern s32 D_800A2E50nm asm("D_800A2E50.NON_MATCHING");
extern s32 D_800A2E44nm asm("D_800A2E44.NON_MATCHING");
extern s32 D_800A2E48nm asm("D_800A2E48.NON_MATCHING");
extern s32 D_800A2E24Absolute[];
extern s32 D_800A2E40;
extern s32 D_800A2E94[];
s32 func_8003702C(u8 *, u8 *);
s32 func_8002CF24(u8 *, u8 *);
extern s32 D_800A3984[];
extern s32 D_800A2E84;
extern u8 D_800AE88C[];
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
extern s32 D_800A2EB0;
extern s32 D_800A3984[];
void *HeapAlloc(u32);
extern s32 D_800A2EC8Small;
extern u8 *D_800A3878;
extern void func_8002E9AC(s32 arg0);
extern s32 D_800A38AC[];
extern u8 *D_800A3878;
extern u8 D_800A2ED8;
extern void *D_800A2EA0Small;
extern u8 D_800A2ED8;
extern s32 D_800A2EC4;
extern s32 D_800A38AC[];
extern s32 D_800A37C4Absolute[];
extern s32 D_800A37B4Absolute[];
extern s32 D_800A37ACAbsolute[];
extern s32 D_800A37A4Absolute[];
extern u8 D_800A2F9DAbsolute[];
extern s32 D_800A2EACSmall;
extern u8 *D_800A3878;
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
extern u8 D_800A2EDA;
extern s32 D_800A2EB0;
extern u8 *D_800A3878;
extern u8 D_800A3860[][4];
extern MATRIX D_800A4548[];
extern s32 D_800A359C[];
extern s32 D_800A2F68[];
extern s32 D_800A2EC0;
extern s32 D_800A2EF8;
extern s32 D_800A2EFC;
extern s32 D_800A2F00;
extern s32 D_800A2EAC;
extern s32 D_800A2EF0;
void func_80039DDC(void);
void func_8003B6DC(s32);
void func_80041A28(void);
void exit();
extern s32 D_800A2EAC;
extern u8 D_800A35FC[];
void func_8003B6DC(s32 arg0);
void func_8003B464(void);
void func_8003C1CC(void);
void func_8003C3FC(void);
extern s32 D_800A3A80;
extern s32 D_800A38AC[];
extern s32 D_800BE980[];
s32 func_800309DC(s32, s32 *, s32 *);
extern s32 D_800A3A80;
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vector3;
void OuterProduct0(s32 *, s32 *, s32 *);
void VectorNormal(s32 *, s32 *, s32);
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
extern s32 D_800A3574[];
extern s32 D_800B9F44[];
extern u8 D_800A2D4C[], D_800A2D4D[];
extern s32 D_800A36D0Absolute[];
void func_80025454(s32);
void func_80031D74(s32, s32, s32);
void func_80031D74(s32, s32, s32);
extern s32 D_800A3574[];
extern u8 D_800A2D4C[], D_800A2D4D[];
extern u32 gPrimitiveCursor[];
extern s32 D_800A39C8[];
extern u8 D_800A2DE0[];
extern void SetPolyF4(u8 *prim);
extern u32 gPrimitiveCursor[];
extern s32 D_800A39C8[];
extern u8 D_800A2DE0[];
extern s32 D_800A2CF8[];
extern s32 func_800337EC(void);
extern u32 gPrimitiveCursor[];
extern s32 D_800A39C8[];
extern u32 D_800B022C[];
extern s16 D_800AFE2C[];
extern s32 D_800A2F38NM asm("D_800A2F38.NON_MATCHING");
extern u8 D_800A2DE0[];
extern s32 D_800A2F08NM[] asm("D_800A2F08.NON_MATCHING");
extern s32 D_800A2CFCNM[] asm("D_800A2CFC.NON_MATCHING");
extern s32 D_800A394CNM asm("D_800A394C.NON_MATCHING");
extern s32 D_800A3A74NM asm("D_800A3A74.NON_MATCHING");
extern s32 D_800A396CNM asm("D_800A396C.NON_MATCHING");
extern u32 gScratchpad[];
extern s32 D_800A3640[];
extern s32 D_800A39C8[];
extern s32 D_800A2EA4Absolute[];
extern u8 D_800A2ED8Abs[] asm("D_800A2ED8.NON_MATCHING");
extern MATRIX D_800A4568[];
extern MATRIX D_800A4588[];
extern u32 gPrimitiveCursor[];
extern s32 D_800A36D0Absolute[];
extern s32 D_800A3668Absolute[];
extern s32 D_800A2F38[];
extern s32 D_800A3640[];
extern s16 D_800AFE2C[];
extern u32 D_800B022C[];
extern MATRIX D_800A4588[];
extern MATRIX D_800A4568[];
extern s32 D_800A39C8[];
extern u32 gPrimitiveCursor[];
extern s32 D_800A2F38[];
extern u32 D_800B022C[];
extern u16 D_800A38C0Small;
extern u8 *D_800A3850;
extern u8 *D_800A390C;
extern u8 D_800AFBB8[];
extern u8 D_800AFB18[];
extern u8 D_800B1F30[];
typedef struct {
    s32 words[10];
} Primitive40;
typedef struct {
    s32 words[4];
} Primitive10;
extern u32 gPrimitiveCursor[];
extern s32 D_800A39C8[];
extern s32 D_800A36D0Absolute[];
extern s32 D_800A36D0Absolute[];
extern s32 D_800A3784Absolute[], D_800A3790Absolute[], D_800A3794Absolute[];
extern s32 D_800A3798Absolute[], D_800A379CAbsolute[], D_800A37A4Absolute[];
extern s32 D_800A37ACAbsolute[], D_800A37B4Absolute[], D_800A37C4Absolute[];
extern s32 D_800A36D0Absolute[];
extern s32 D_800A36D4Absolute[];
extern s32 D_800A3784Absolute[], D_800A3790Absolute[], D_800A3794Absolute[],
    D_800A3798Absolute[], D_800A379CAbsolute[], D_800A37A4Absolute[],
    D_800A37ACAbsolute[], D_800A37B4Absolute[], D_800A37C4Absolute[];
extern s32 D_800A36C0Absolute[];
extern s32 D_800A36E8Absolute[];
extern s32 D_800A3790Absolute[], D_800A3798Absolute[], D_800A379CAbsolute[],
    D_800A37A4Absolute[], D_800A37B4Absolute[], D_800A3794Absolute[],
    D_800A3784Absolute[], D_800A37ACAbsolute[], D_800A37C4Absolute[];
extern u8 *D_800A3554[];
extern void *D_800A2EA0[];
void func_80035274(void);
typedef struct {
    u8 pad[0x3E0];
    void *unk3E0;
} Data3554;
extern u8 *D_800A3554[];
extern void *D_800A2EA0[];
extern s32 D_800A2F3C[];
void func_80034D64(void);
void func_80035274(void);
extern s32 D_800A2F44;
extern u8 *D_800A3850;
extern u8 *D_800A390C;
extern u8 D_800A2DE1[];
extern s32 D_800A2E9C[];
extern s32 D_800A2E24Absolute[];
void func_8002F0A8(u8 *);
void func_80034D64(void);
void func_80035720(u_long *);
extern s32 D_800B60C8[];
extern u8 D_800A2ED9[];
extern u8 D_800A2ED8Arr[];
extern void func_80035F28(u8 *);
extern s32 D_800B60E8[];
extern s32 D_800AEE50[];
extern s32 D_800B60C8[];
extern s32 D_800AEE50[];
extern s32 D_800B60C8[];
extern s32 D_800B7398[];
extern u8 D_800B7388Base[] asm("D_800B7388.NON_MATCHING");
extern u8 D_800B60C8Base[] asm("D_800B60C8.NON_MATCHING");
extern s32 D_800A2ED4[];
extern char D_8008D0AC[];
extern char D_8008D0CC[];
extern void *FileOpenCall367DC(void) asm("FileOpen");
extern s32 FileSeekCall367DC(void *, s32, s32) asm("FileSeek");
extern void FileReadCall367DC(s32, s32, s32, void *) asm("FileRead");
extern void FileCloseCall367DC(s32) asm("FileClose");
extern s32 D_800A3A2CAbsolute[];
extern s32 D_800A3A34Absolute[];
extern s32 D_800A3A2CAbsolute[];
extern s32 D_800A3A34Absolute[];
extern s32 D_800BE974[];
extern s32 D_800BE974[];
void func_8001FAC0(u8 *, s32);
void func_8001FB28(u8 *, s32);
extern s32 D_800A39E0[];
extern s32 D_800BE974[];
extern s32 D_800BE980[];
extern u8 D_800A2F84w44[] asm("D_800A2F84");
extern s32 D_800A3730, D_800A3734;
extern s32 D_800AE154[];
extern s32 D_800BE980[];
extern s32 D_800A2F4C;
extern s32 D_800A36A4;
extern u8 D_800A33E4;
extern u8 D_800A2F58;
extern s32 D_800A2F00nm[] asm("D_800A2F00.NON_MATCHING");
extern s32 D_800A2EFCnm[] asm("D_800A2EFC.NON_MATCHING");
extern s16 D_800A3910nm[] asm("D_800A3910.NON_MATCHING");
extern void func_800373B4(u8 *);
extern void func_8002A1FC(u8 *);
extern void func_8003ABC0();
extern s16 D_80098254[];
extern void func_8003ABC0();
extern s16 D_80098294[];
extern s16 D_800982D4[];
extern void func_8003ABC0();
extern s16 D_80098328[];
extern void func_80025594(u8 *);
extern void func_8003AA20();
extern void func_8003A880();
extern void func_8003A950();
extern void func_8003AAEC();
extern s32 D_800A3558[];
extern u8 *D_800A3554[];
extern s32 D_800A3730, D_800A3734;
void func_800390A0(s32, s32, s32, s32);
void FontDrawPaddedNumber(s32, s32, s32, s32);
void func_8003644C(s32, s32, s32, s32);
extern s32 D_800A2E94[];
extern s32 D_800A2EB0Absolute[];
extern s32 D_800A2EF4[];
extern u8 D_800A2F65;
extern s32 D_800A35E0[];
extern s32 D_800BE980[];
extern s32 D_800BE980[];
extern s32 D_800A3A2CAbsolute[];
extern s32 D_800A3A34Absolute[];
extern void func_8002D4CC();
extern u8 *D_800A3854Absolute[];
extern s32 D_800BE72C[];
extern s32 D_800BE730[];
extern s16 D_800BE738[];
extern s32 D_800A2F60;
extern s32 D_800A2EACAbsolute[];
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
extern u8 *D_800A3554[];
extern u8 D_800BE70C[], D_800B9DA4[];
extern s32 D_800AE1EC[];
extern s32 CdSetDebug(s32 level);
extern s32 D_800A2F74;
extern s32 D_800A37CC;
extern CdlLOC D_800BDEBC[];
extern s32 D_80098340[];
extern s32 D_800A45A8[];
extern s32 D_800A45AC[];
extern void *HeapAlloc(u32);
extern void FileRead();
extern s32 D_800A2EC8[];
extern s32 D_800A2F70;
extern u8 D_800A2F9CAbsolute[];
extern u8 D_800AE24C[];
extern s32 CdGetToc(void *);
extern s32 D_800A2F74;
extern s32 D_800A37CC;
extern CdlLOC D_800BDEBC[];
extern s32 D_80098340[];
extern s32 D_800A45AC[];
extern char D_8008D188[];
extern s32 D_800A3A04nm[] asm("D_800A3A04.NON_MATCHING");
extern s32 D_800A3A3CAbsolute[];
extern s32 D_800A2F84nm asm("D_800A2F84.NON_MATCHING");
extern void func_800414E0(void *, s32, s32);
extern s32 func_80029EF8(u8 *);
extern s32 D_800BE974[];
extern s32 D_800BE974[];
extern s32 D_800A2EA8[];
extern s32 D_800BE974[];
extern s32 D_800A2F88;
extern u8 D_800A2F95;
extern s16 gSequenceId;
extern s16 gVabId;
extern u8 *gSequenceData;
extern void SsVabClose(s16);
extern void SsEnd(void);
extern s32 D_800A3A08;
extern void func_80080758(void);
extern void *D_800A3A00;
extern void HeapFree(void *ptr);
extern void func_80080728(void);
extern char D_800AF990[], D_800B9C88[];
extern s32 SpuInitMalloc(s32, char *);
extern s16 D_800B9E24[];
extern u8 D_800A3880;
extern void SoundLoadVab(s32);
extern s16 D_800B9E24[];
extern u8 D_800A3880;
extern void SoundReloadVab(s32);
extern s16 gVabId;
extern void *D_800A3A00;
extern s32 D_800A3A08;
extern s32 func_8003FFF0(void *, void *);
extern s16 SoundVabOpen(void *, void *);
extern void SsVabClose(s16);
extern void func_8003FA0C(void);
extern s16 gVabId;
extern void *D_800A3A00;
extern s32 D_800A3A08;
extern s32 func_8003FFF0(void *, void *);
extern s16 SoundVabOpen(void *, void *);
extern void SsVabClose(s16);
extern void HeapFree(void *);
extern void func_8003FA0C(void);
void func_80082B70(void);
extern void func_80082B70(void);
extern void func_8003F284(void);
extern void func_80082B50(void);
extern u8 D_800A2F94;
extern s32 func_8003FFF0(void *, void *);
extern s16 gVabId;
extern u8 D_800A2F94;
extern u8 *gSequenceData;
extern s16 gSequenceId;
extern s16 gSequenceId;
extern void SsSetLoop(short seqAccessNum, short para1, short para2);
extern void SsSeqPlay(short seqAccessNum, short playMode, short playCount);
extern void SsSeqReplay(short seqAccessNum);
extern void SsSeqSetVol(short seqAccessNum, short leftVolume,
                        short rightVolume);
extern s32 SpuGetKeyStatus(s32);
extern s16 D_800B9E24[];
extern s32 SpuGetKeyStatus(s32);
extern s16 D_800B9E24[];
extern void func_8003F914(s32);
extern u8 D_800A3880;
extern s16 D_800B9E24[];
extern u8 D_800B9E26[];
extern s16 D_800B9E2A[];
extern s16 D_800B9E2C[];
extern s16 D_800B9E2E[];
extern s8 SsUtChangePitch(s16, s16, s8, s16, s32, s32, s32);
extern s16 D_800B9E24[];
extern void func_8003F914(s32);
extern char D_8008D1A8[];
extern char D_8008D1C4[];
extern char D_8008D1DC[];
extern char D_8008D1F8[];
extern char D_800A2F98[];
extern s32 D_80098D00[];
extern u8 D_800A354C[];
extern s32 D_800BE988[];
extern u8 D_800A2FA4[];
extern u8 D_800A39D0;
extern u8 D_800BA048[];
extern s8 D_800A2FA4B[] asm("D_800A2FA4.NON_MATCHING");
extern s32 D_800BE988[];
extern s32 D_80098D00[];
extern s8 D_800A354CB[] asm("D_800A354C.NON_MATCHING");
extern s32 D_800BA048B[] asm("D_800BA048.NON_MATCHING");
extern s8 D_800A39D0B asm("D_800A39D0.NON_MATCHING");
extern s32 D_800BE890w16[] asm("D_800BE890.NON_MATCHING");
extern u8 D_80098C00w16[] asm("D_80098C00.NON_MATCHING");
extern u8 D_800A306Cw16[] asm("D_800A306C.NON_MATCHING");
extern void func_8001F90C(s32, s32, s32, s16 *);
extern void func_8003F564(s8, s8);
extern void func_8003FDE8(s8, s32, s32);
extern s32 D_800A2EA4[];
extern u8 D_800A2F9D;
extern u8 D_800A2FA8;
extern u8 D_800A2FA8;
extern void func_8003FDE8(s8, s32, s32);
extern u8 D_800A2F9D;
extern s32 D_800A2EC8[];
extern s32 D_800A359C[];
extern void func_8003F564(s8, s8);
extern void func_8003FDE8(s8, s32, s32);
extern u8 D_800A2F9D;
extern u8 D_8008D21C[];
extern u8 D_8008D228[];
extern u8 D_8008D234[];
extern u8 D_80098BEC[];
extern u8 D_80098BED[];
extern u8 D_80098BEE[];
extern s32 D_800BE8A8[];
extern s32 D_800A2FA0;
extern s32 D_800A2EB8NM[] asm("D_800A2EB8.NON_MATCHING");
extern void func_8003F060(s32);
extern void func_8003F284(void);
extern void func_8003F564(s8, s8);
extern void func_8003FDE8(s8, s32, s32);
extern u8 D_800A2F9D;
extern void func_8003FDE8(s8, s32, s32);
extern void SoundShutdown(void);
extern void SsSetMute(s32);
void func_80041AF0();
extern s32 gPadBuffers[];
extern u32 D_8008CA04[];
extern u32 D_8008CA08[];
extern u32 D_8008CA0C[];
extern u32 D_8008CA10[];
extern u32 D_8008CA14[];
extern u32 D_8008CA18[];
extern u32 D_8008CA1C[];
extern u32 D_8008CA20[];
extern u32 D_800B9DF8[];
extern u32 D_800B9E00[];
extern u32 D_800B9E04[];
extern void func_80041F54(s32 *, s32 *, s32, s32);
extern u16 D_8008CA04U16[] asm("D_8008CA04.NON_MATCHING");
extern u16 D_8008CA04U16[] asm("D_8008CA04.NON_MATCHING");
extern s32 gPadBuffers[];
extern s32 gPadBuffers[];
void InitPAD(void *, s32, void *, s32);
s32 StartPAD(void);
s32 VSync(s32);
extern s32 gPadBuffers[];
extern u32 D_800B9E00[];
extern u8 D_800A3A24Small;
extern void *D_800A3A24[];
extern s8 D_800A3A25[];
extern u8 D_800A3A26[];
extern u8 D_800A3A27[];
extern u8 *D_800A3878nm[] asm("D_800A3878.NON_MATCHING");
extern u32 D_8008CA2C[];
extern u32 D_8008CA30[];
extern u32 D_8008CA34[];
extern u32 D_8008CA38[];
extern u32 D_8008CA3C[];
extern u32 D_8008CA40[];
extern u32 D_8008CA44[];
extern u32 D_8008CA48[];
extern s32 gRandomSeed16;
extern u8 D_800AD9CC[];
void func_80043D6C(void);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void MulRotMatrix(MATRIX *matrix);
extern void func_800328AC(void *arg0, s32 arg1);
extern void func_80044BCC(s32 arg0);
extern s32 gRandomSeed16;
extern u8 D_800B1A24[];
extern u8 D_800B1A25[];
extern u8 D_800B1A26[];
extern u8 D_800B1A26R[] asm("D_800B1A26.NON_MATCHING");
extern u8 D_800B19E4[];
extern u8 D_800A2EE0[];
extern u8 *D_800A3960[];
extern u8 *D_800A3960w17[] asm("D_800A3960.NON_MATCHING");
typedef struct {
    u32 w[12];
} CopyRow30;
extern CopyRow30 D_800AD9B0[];
extern CopyRow30 D_800BBAAC[];
extern void func_800364C4(void);
extern void func_80036540(void);
extern u8 D_800A2EDC[];
extern u32 D_8009B9C4[];
extern u8 *gHeapBase, *gHeapBreak;
extern s8 gHeapInit;
extern s8 gHeapInit;
typedef struct HeapBlock {
    u32 size; /* payload size in bytes; bit 0 set while the block is free */
} HeapBlock;
extern u32 D_8009B9C4[]; /* heap start address, stored by the startup code */
extern u8 *gHeapBase;
extern s8 gHeapInit;
extern u8 gHeapBigAllocFlag;
extern u8 *gHeapBreak;
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
s32 VectorGetMagnitude2D(void *arg0);
void func_8001FC6C(void);
void func_8001FD44(u8 *arg0);
s32 MathMultiplyFixed16(s32, s32); /* extern */
void func_8001FF3C(u8 *arg0, u8 *arg1);
void func_80022CA4(void);
void func_80022F48(void);
void func_80022F80(void);
void func_80022FB8(u8 *arg0, s32 arg1);
void func_80024210(void);
s32 func_8002482C(s32 arg0, s32 arg1, s32 *arg2);
s32 func_80024980(s32 arg0, s32 arg1, s32 *arg2);
void func_80025454(s32 track);
void func_80025594(u8 *object);
void func_800255A0(u8 *arg0);
void func_80025614(u8 *arg0);
void func_80025720(u8 *obj);
void func_80025730(u8 *obj);
void ObjectSetCallbackIfAllowed(Batch0CallbackObject *object,
                                void (*callback)(void));
s32 func_80025938(u8 *arg0, u8 *arg1);
s32 func_80025A38(u8 *arg0);
void func_80025DD4(u8 *arg0, u8 *arg1);
void func_80025F40(u8 *arg0, s32 arg1);
void func_80026074(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 func_800270F4(void *arg0, s32 arg1);
s32 MathGetAngleDelta(s32 arg0, s32 arg1);
void func_80028754(u8 *arg0, s32 arg1);
void func_80028D80(u8 *arg0);
void func_80028F98(UnkObject90 *object);
void func_80028FAC(void *object);
void func_80028FCC(u8 *arg0);
void SelectionStepForward(Counter *selection);
void SelectionStepBackward(SelectionState *selection);
void func_80029450(s32 *p);
void func_800297D0(u8 *arg0);
void func_800298E0(s32 *car);
void func_80029994(u8 *arg0, s32 arg1);
void func_80029A78(u8 *car);
void func_80029CB4(s32 *arg0);
void func_80029DA8(s32 *car);
void func_80029E2C(void);
void func_80029E34(void);
void func_80029E3C(void);
s32 func_80029EF8(u8 *obj);
void func_8002A1D0(void);
void func_8002A954(void);
s32 func_8002AAA0(s32 *car);
void func_8002AD20(s32 *car, s32 index);
void func_8002ADE0(s32 *car, s32 arg1);
void func_8002B258(u8 *arg0);
void func_8002B538(u8 *arg0);
void func_8002BC88(u8 *arg0);
s32 func_8002CF1C(void);
void func_8002D16C(u8 *arg0);
void func_8002D27C(u8 *arg0);
u8 *func_8002D380(void);
void func_8002D3A8(u8 *object, s32 index);
void func_8002DA30(s32 *arg0);
void func_8002DA80(void);
void func_8002DC2C(void);
s32 func_8002DDA0(void);
void func_8002E228(void);
void func_8002E230(void);
void func_8002EE88(void);
void func_8002EEFC(u8 *arg0);
void func_8002F0A8(u8 *arg0);
void func_8002F1A0(void);
void func_8002F2CC(void);
void func_8002F454(void);
void func_8002F514(void);
void func_8002F5A4(void);
void func_8002F5CC(void);
void func_8002F5F4(void);
void func_8002F66C(void);
void func_8002F674(void);
void func_8002F86C(void *arg0, s32 arg1);
void func_80030CDC(s32 *query, s32 index);
void func_800311B4(s32 x, s32 y, s32 z, s32 *out);
void func_80031874(u8 *quad, s32 *normal);
void func_80032328(s32 arg0);
void func_800323F0(s32 index, s32 arg1);
void func_80032450(s32 first, s32 second);
void func_80032494(u8 *object);
void GraphicsLinkPrimitive(u32 *orderingTable, u32 *primitive);
void GraphicsAddTaggedPrimitive(u32 *orderingTable, u32 *primitive, u32 tag);
u8 *func_80032544(u8 *arg0, s32 arg1);
void func_8003271C(s32 arg0);
u8 *func_80032760(u8 *arg0, u8 *arg1, s32 arg2);
void func_800328AC(void *arg0, s32 arg1);
s32 func_80032A90(u8 *arg0);
void func_80032D94(s8 *object);
void func_80032DEC(u8 *arg0, s32 arg1);
void func_80033000(u8 *arg0, u8 *arg1, u8 *arg2);
void func_80033704(s16 *out);
void func_80033780(void *arg0);
void func_80033788(u8 *arg0);
void func_8003379C(u8 *arg0, u8 *arg1, u8 *arg2);
s32 MathMultiplyFixed16(s32 arg0, s32 arg1);
s32 func_800337EC(void);
void func_8003382C(s16 *out);
void func_800338A4(s32 *dst, s32 *src);
s32 func_800338D8(u16 *object);
u32 func_800342D8(u32 *entry, u32 primCursor);
void func_800345E0(void);
s32 func_800346D0(s32 threshold);
void func_80034834(void);
void func_80034990(void);
void func_80034B90(u8 *prim);
void func_80034C1C(void);
void func_80034C94(void);
void func_80034CFC(void);
void func_8003565C(s32 arg0);
void func_800356A8(s32 arg0);
void func_80035720(u_long *ot);
void func_8003587C(s32 arg0);
void func_80035E8C(s32 *src, s32 *outX, s32 *outY);
void func_80036264(void);
void func_8003644C(s32 index, s32 arg1, s32 arg2, s32 arg3);
void func_800364C4(void);
void func_80036540(void);
void func_800365B8(s32 *out);
void func_8003667C(u32 *list);
void func_800367DC(void);
s32 func_80036F64(u8 *arg0, u8 *arg1, s32 arg2);
s32 func_80036FC8(s32 *a, s32 *b);
s32 func_8003702C(u8 *objectA, u8 *objectB);
s32 func_800370B8(s32 a, s32 b);
void func_80037130(u8 *object);
s32 func_80037204(u8 *obj);
s32 func_80039008(u8 *arg0, u8 *arg1);
void func_800390A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80039B74(s32 *arg0, s32 arg1);
s8 func_80039C68(u8 *arg0, s32 arg1, s32 arg2);
void func_80039CF4(void);
void func_8003A440(void);
void func_8003A880(s32 car);
void func_8003A950(s32 car);
void func_8003AA20(s32 car);
void func_8003AAEC(s32 car);
void func_8003ABC0(u8 *object);
void func_8003AC18(u8 *object, s32 arg1, s32 arg2, s32 arg3);
void func_8003AD08(struct Unk_8003AD08 *arg0);
void func_8003B464(void);
s32 func_8003B5F8(s32 arg0, s32 arg1);
void func_8003BCAC(void);
void func_8003C1CC(void);
void func_8003C528(void);
void CdDisableDebug(void);
void *FileOpen(s32 fileId, void *mode);
void FileClose(s32 handle);
s32 func_8003C8B4(void);
s32 FileSeek(s32 handle, s32 offset, s32 whence);
void func_8003C8C8(u8 *string);
void *FileLoadToHeap(s32 arg0);
void func_8003CA18(s32 arg0, s32 arg1);
void func_8003CC48(void);
void func_8003CCE0(s32 arg0);
void CdStop(void);
void func_8003CDBC(s32 arg0);
void func_8003CEFC(void);
void func_8003CF04(void);
void func_8003D25C(u8 *object);
void func_8003D528(u8 *object);
void func_8003D5F8(u8 *object);
void func_8003D654(u8 *object);
void func_8003D69C(u8 *object);
void func_8003D6F8(u8 *object);
s32 func_8003DAD0(s32 a, s32 b);
s32 func_8003DB18(s32 start, s32 end, s32 value);
s32 func_8003DB5C(s32 arg0, s32 arg1, s32 arg2);
void func_8003EA94(u8 *object, s32 *arg1, s32 arg2);
void func_8003EAE8(u8 *object, s32 index);
void func_8003EBD0(u8 *object, s32 index);
void SoundStart(void);
void SoundShutdown(void);
void SoundEnd(void);
void func_8003EFC8(void);
void func_8003EFE8(void);
void SoundInitTables(void);
void func_8003F060(s32 arg0);
void func_8003F0CC(s32 arg0);
void SoundLoadVab(s32 arg0);
void SoundReloadVab(s32 arg0);
void func_8003F23C(void);
void func_8003F25C(void);
void func_8003F284(void);
void func_8003F2AC(s32 arg0, s32 arg1);
void SoundOpenSequence(void);
void SoundSetSequenceLoop(s8 loopCount);
void SoundPauseSequence(void);
void SoundPlaySequence(s8 playCount, u8 playMode);
void SoundReplaySequence(void);
void SoundSetSequenceVolume(u8 leftVolume, u8 rightVolume);
void SoundStopSequence(void);
s32 func_8003F4FC(s32 arg0);
void func_8003FA0C(void);
void func_8003FEB8(void);
s16 SoundVabOpen(void *arg0, void *arg1);
s32 func_8003FFF0(void *arg0, void *arg1);
void func_800400D8(s32 arg0);
void func_800401B8(void);
void func_800406D0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
void func_80040AC0(u8 *object);
void func_80040AC8(u8 *object);
void func_80041328(void);
void func_800413C0(void);
void func_80041414(void);
void func_8004142C(void);
void func_80041444(s32 arg0);
void func_800414E0(void *arg0, s32 arg1, s32 arg2);
void func_80041564(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80041848(u8 *arg0, s32 arg1);
void func_80041850(void);
void func_8004195C(void);
void func_80041A28(void);
void func_80041AD0(void);
void func_80041AF0(void);
s32 func_80041B7C(s32 index);
u16 func_80041B94(s32 index);
u32 func_80041BAC(s32 arg0);
void PadInitBuffers(void);
s32 func_80041D60(void);
void func_80041DEC(void);
void func_80042218(u16 *src, s32 *acc, u32 *dst);
s32 func_8004229C(s32 arg0);
u32 RandomGetScaled16(s32 arg0);
void func_80042EC0(void);
void func_800436D0(u8 *object);
void func_80043D6C(void);
void func_80043F7C(u8 *arg0, s16 *arg1);
void func_80044114(u8 *arg0);
void func_8004419C(u8 *object);
void func_800441C8(void);
void func_80044248(void);
void func_800442C8(u8 *arg0, u8 *arg1);
void func_80044594(u8 *arg0);
void HeapInit(void);
void HeapResetInitFlag(void);
void *HeapAlloc(u32 size);
u32 HeapFreeSpaceCount(void);
void HeapCoalesce(void);
void HeapFree(void *ptr);
void func_80044A1C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5,
                   u8 arg6, u8 arg7);

extern u8 *D_800A3878NM[] asm("D_800A3878.NON_MATCHING");
extern SVECTOR D_800992E4[];
extern SVECTOR D_800992EC[];
extern SVECTOR D_800992F4[];
extern s32 D_800A39C8[];
extern u32 gPrimitiveCursor[];
extern void SetPolyFT3(POLY_FT3 *prim);

void func_80044BCC(s32 arg0) {
    s32 v;
    s32 typeIndex;
    u8 *prim;
    s32 otz;
    u32 *ot;

    ot = (u32 *)(D_800A39C8[0] + 0x20);
    prim = (u8 *)gPrimitiveCursor[0];
    typeIndex = *(s8 *)(D_800A3878NM[0] + arg0 * 0x500 + 0x376);
    gte_ldv3(D_800992E4, D_800992EC, D_800992F4);
    gte_rtpt();
    SetPolyFT3((POLY_FT3 *)prim);
    SetShadeTex(prim, 1);
    *(s16 *)(prim + 0xE) =
        GetClut((typeIndex % 16) * 16 + 0x300, 0x3F - typeIndex / 16);
    if (typeIndex < 12) {
        *(s16 *)(prim + 0x16) = GetTPage(0, 0, (typeIndex % 4) * 64 + 0x300, 0);
        v = typeIndex / 4;
        v = v * 64 + 0x40;
    } else {
        *(s16 *)(prim + 0x16) =
            GetTPage(0, 0, (typeIndex % 4) * 64 + 0x300, 0x100);
        v = ((typeIndex - 12) / 4) * 64;
    }
    *(u8 *)(prim + 0x14) = 0x20;
    *(u8 *)(prim + 0xC) = 0;
    *(u8 *)(prim + 0xD) = v;
    *(u8 *)(prim + 0x15) = v;
    *(u8 *)(prim + 0x1C) = 0;
    *(u8 *)(prim + 0x1D) = v + 0x20;
    gte_avsz3();
    asm volatile("mfc2 %0, $7\n\tnop" : "=r"(otz) : "0"(otz));
    gte_stsxy3(prim + 8, prim + 0x10, prim + 0x18);
    GraphicsAddTaggedPrimitive(&ot[otz >> 4], (u32 *)prim, 0x07000000);
    prim += 0x20;
    gPrimitiveCursor[0] = (u32)prim;
}

extern s32 D_800A39C8[];
extern u32 gPrimitiveCursor[];
extern u8 D_800A2DE0[];
extern void SetLineF4(u8 *prim);
extern void SetLineF2(u8 *prim);

void func_80044DC4(u8 *arg0, s32 arg1, u8 *arg2) {
    register u8 *prim asm("$18");
    register u8 *walker asm("$20");
    register u8 *pe asm("$17");
    s32 count;
    u8 *rgb;
    u8 g;
    u8 b;
    register u8 rv asm("$11");
    register u8 rtmp asm("$10");
    register s32 obt asm("$10");
    register u32 *a0arg asm("$4");
    register u32 *a1arg asm("$5");
    u32 a2arg;
    u16 xy0;
    u16 xy1;
    u16 xy2;
    u16 xy3;
    u8 btmp;
    register s32 gte asm("$19");
    register s32 otEntry asm("$16");
    volatile struct {
        u8 r;
        u8 pad1[7];
        s32 otBase;
        u8 pad2[4];
    } st;
#define r st.r
#define otBase st.otBase
    register s32 v0_ asm("$11");
    register s32 v1_ asm("$12");
    register s32 v2_ asm("$10");
    register s32 w3 asm("$12");
    register s32 masked asm("$2");

    otBase = (s32)D_800A39C8[0] + 0x20;
    prim = (u8 *)gPrimitiveCursor[0];
    rgb = arg2;
    count = arg1;
    rtmp = rgb[0];
    r = rtmp;
    g = rgb[1];
    b = rgb[2];
    if (count > 0) {
        walker = arg0 + 0x24;
        pe = prim + 0xE;
        do {
            v0_ = *(s32 *)(walker - 0xC);
            v1_ = *(s32 *)(walker - 0x8);
            v2_ = *(s32 *)(walker - 0x4);
            gte_ldv3(v0_, v1_, v2_);
            gte_rtpt();
            SetLineF4(prim);
            gte_cfc2(gte, 31);
            masked = gte & 0x66000;
            if (masked != 0) {
                goto next;
            }
            gte_nclip();
            rv = r;
            *(u8 *)(pe - 0x9) = g;
            *(u8 *)(pe - 0x8) = b;
            *(u8 *)(pe - 0xA) = rv;
            gte_mfc2(gte, 24);
            if (D_800A2DE0[0] != 0) {
                if (gte < 0) {
                    goto next;
                }
            } else {
                if (gte > 0) {
                    goto next;
                }
            }
            gte_avsz3();
            gte_mfc2(gte, 7);
            gte += (s32)(s8) * (walker - 0x23) * 4;
            gte_stsxy3(prim + 8, prim + 0xC, prim + 0x10);
            w3 = *(s32 *)(walker);
            gte_ldv0(w3);
            gte_rtps();
            gte_stsxy(prim + 0x14);
            otEntry = gte >> 4;
            otEntry = otEntry << 2;
            obt = otBase;
            otEntry = obt + otEntry;
            GraphicsAddTaggedPrimitive((u32 *)otEntry, (u32 *)prim, 0x06000000);
            prim += 0x1C;
            pe += 0x1C;
            SetLineF2(prim);
            xy0 = *(u16 *)(pe - 0x20);
            xy1 = *(u16 *)(pe - 0x16);
            xy2 = *(u16 *)(pe - 0x14);
            *(u8 *)(pe - 0xA) = rgb[0];
            xy3 = *(u16 *)(pe - 0x22);
            a0arg = (u32 *)otEntry;
            *(u8 *)(pe - 0x9) = rgb[1];
            btmp = rgb[2];
            xy3 = *(u16 *)((u8 *)(pe) + -0x22);
            a1arg = (u32 *)prim;
            asm volatile("lui %0, 0x300" : "=r"(a2arg));
            prim += 0x10;
            *(u16 *)(pe - 0x4) = xy0;
            *(u16 *)(pe - 0x2) = xy1;
            *(u16 *)(pe + 0x0) = xy2;
            *(u16 *)(pe - 0x6) = xy3;
            *(u8 *)(pe - 0x8) = btmp;
            GraphicsAddTaggedPrimitive(a0arg, a1arg, a2arg);
            pe += 0x10;
        next:
            walker += 0x2C;
        } while (--count > 0);
    }
    gPrimitiveCursor[0] = (u32)prim;
}

extern s32 D_800A33F0;
extern s32 D_800A33F4;
extern s8 D_800A33F8;
extern s32 D_800A3400;
extern s32 D_800A3404;
extern s32 D_80098184[];
extern s32 D_80098134nm[] asm("D_80098134.NON_MATCHING");
extern s32 D_8009813Cnm[] asm("D_8009813C.NON_MATCHING");
extern u8 D_800A3880nm[] asm("D_800A3880.NON_MATCHING");

void func_80044FF8(s32 arg0, s32 arg1) {
    s32 i;
    s32 off;
    s32 *entry;
    s32 temp;
    s32 vol;
    s32 cur;
    s32 newv;

    i = 0;
    switch (arg0) {
    case 0:
        D_800A3404 = 0;
        D_800A3400 = 0;
        D_800A33F4 = 0;
        D_800A33F0 = 0;
        *(volatile s32 *)&D_800A33F8 = 0x20;
        func_8003F564((s8)arg1, -(D_800A3880nm[0] != 0) & 7);
        func_8003FDE8((s8)arg1, 0x7F, 0x7F);
        return;
    case 1:
        if (D_800A3404 >= D_80098184[0]) {
            D_800A3404 = 0;
            D_800A3400 = 0;
            D_800A33F0 = 0;
        } else {
            D_800A3404 = D_800A3404 + ((D_80098134nm[D_800A33F0 * 6] * 7) >> 2);
        }
        if (D_800A33F4 != 0) {
            D_800A33F4 = D_800A33F4 - 1;
        }
        off = i * 0x18;
        while (D_800A3404 > *(s32 *)((s8 *)D_8009813Cnm + off)) {
            i = i + 1;
            off = off + 0x18;
        }
        entry = (s32 *)((s8 *)D_80098134nm + i * 0x18);
        temp =
            MathFixedDivide(entry[4] - entry[3], (entry[2] - entry[1]) >> 16);
        D_800A3400 =
            entry[3] + (MathMultiplyFixed16(temp, D_800A3404 - entry[1]) >> 16);
        if (D_800A33F0 < i) {
            D_800A33F4 = 0x14;
        }
        D_800A33F0 = i;
        if (D_800A33F4 < 0x12) {
            vol = D_800A3400 / 110;
        } else {
            vol = 0x6E;
        }
        cur = *(volatile s32 *)&D_800A33F8;
        if (cur + 7 < vol) {
            *(volatile s32 *)&D_800A33F8 = cur + 7;
            newv = cur + 7;
        } else if (vol < cur - 5) {
            *(volatile s32 *)&D_800A33F8 = cur - 5;
            newv = cur - 5;
        } else {
            newv = vol;
        }
        *(volatile s32 *)&D_800A33F8 = newv;
        if (newv >= 0x80) {
            *(volatile s32 *)&D_800A33F8 = 0x7F;
        }
        func_8003FA84((s8)arg1, D_800A33F8);
        return;
    case 2:
        func_8003F914((s8)arg1);
        return;
    }
}

extern s32 D_800A3960gp;
extern u8 D_800A35F8gp;
extern u8 D_800A3A60gp;
asm(".globl D_800A3960gp\nD_800A3960gp = D_800A3960");
asm(".globl D_800A35F8gp\nD_800A35F8gp = D_800A35F8");
asm(".globl D_800A3A60gp\nD_800A3A60gp = D_800A3A60");

void func_80045288(void) {
    extern s32 D_800A2EA4[];
    extern u8 *D_800A3554[];
    extern s32 D_800A3598[];
    extern s32 D_800A2CE0[];
    extern s32 D_800A2EB0Absolute[];
    extern u8 *D_800A2FCC;
    extern u8 D_800A3424;
    extern u8 D_800A3590;
    extern u8 D_800A34B0;
    extern u8 gTextColor;
    extern u8 D_800A34AC;
    extern s16 D_800A383C;
    extern s16 D_800A383E[];
    extern s16 D_800A3840;
    extern s16 D_800A3842[];
    extern s16 D_800A3844;
    extern s16 D_800A3846[];
    extern s32 D_800A3428;
    extern u8 D_800A39D4;
    extern u8 D_800A3688;
    extern u32 D_800A34E0;
    extern u8 D_800991E8[];
    void func_80052E18(void);
    void func_80046258(void);
    void HudInitPrims(void);
    void func_8004E700(void);
    void func_80048118(void);
    void func_8004F880(void);
    void func_8004A510(void);
    void func_80048700(void);
    void func_80045F70(void);
    void func_800511E4(void);
    void func_800508E4(void);
    void func_80048C90(void);
    u8 *obj;
    u8 *v;
    s32 x;
    s32 flag;
    u8 *row;
    u8 *p;
    s8 i;
    s8 j;
    s32 c;
    s32 flag2;
    s32 w;

    flag = 1;
    if (D_800A2EA4[0] != 0) {
        flag = 2;
    }
    obj = D_800A3554[0];
    v = D_800A2FCC;
    x = *(s32 *)(obj + 0x3E0);
    D_800A3424 = flag;
    D_800A3960gp = 0;
    D_800A3590 = 0;
    D_800A34B0 = 0;
    gTextColor = 0;
    do {
    } while (0);
    D_800A35F8gp = 1;
    D_800A34AC = 60;
    D_800A383E[0] = 1000;
    D_800A383C = 1000;
    D_800A3842[0] = 500;
    D_800A3840 = 500;
    D_800A3846[0] = 75;
    D_800A3844 = 75;
    D_800A3428 = x;
    if (v != 0) {
        for (i = 0; i < 24; i++) {
            j = 0;
            row = D_800991E8 + i * 3;
            for (; j < 3; j++) {
                p = row + j;
                c = *p + 0x30;
                if (c > 0xFF) {
                    c = 0xFF;
                }
                *p = c;
            }
        }
        D_800A2FCC = 0;
    }
    func_80052E18();
    if (D_800A3A60gp != 0) {
        func_80046258();
    }
    HudInitPrims();
    func_8004E700();
    func_80048118();
    func_8004F880();
    func_8004A510();
    func_80048700();
    func_80045F70();
    func_800511E4();
    func_800508E4();
    func_80048C90();
    flag2 = 0;
    if (D_800A3598[0] != 1) {
        goto set_one;
    }
    if (D_800A2CE0[0] == 3) {
        goto set_one;
    }
    goto flag_done;
set_one:
    flag2 = 1;
flag_done:
    w = D_800A2EB0Absolute[0];
    D_800A39D4 = flag2;
    if (w >= 0) {
        if (w == 1) {
            goto hit;
        }
    } else {
        w = -w;
        if (w == 1) {
            D_800A3688 = 0;
        }
    }
    goto fin;
hit:
    D_800A3688 = 0;
fin:
    D_800A34E0 = 0x7FFFFFFF;
}

INCLUDE_ASM("asm/nonmatchings/scene", func_80045480);

INCLUDE_ASM("asm/nonmatchings/scene", func_80045864);

extern u8 D_800A342C[];
extern s32 D_800A3430[];
extern u8 D_80090F32[];
extern u8 D_800991E8[];
extern u8 D_800991E9[];
extern u8 D_800991EA[];

#ifdef NON_MATCHING
/* Wall: size and instruction shape exact (0x214), but gcc pins the
 * HeapAlloc result to s4 (slot 5) instead of fp no matter where buf
 * is declared; retail order is row s0, poly s1, ptr s2, j s3, b2 s4,
 * b1 s5, b0 s6, i s7, buf fp. Decomp-permuter candidate. */
void func_80045F70(void) {
    u8 *buf;
    s8 i;
    u8 b0;
    u8 b1;
    u8 b2;
    s8 j;
    u8 *ptr;
    u8 *poly;
    u8 *row;
    s32 v0;
    s32 v1;

    i = 0;
    if (D_800A2EB0Absolute[1] > 0) {
        ptr = D_80090F32;
        do {
            D_800A342C[i] = 0;
            buf = (u8 *)HeapAlloc(0x500);
            v1 = *(s8 *)(D_800A3984[0] + (i * 5 << 8) + 0x876);
            D_800A3430[i] = (s32)buf;
            j = 0;
            v0 = v1 * 3;
            b0 = D_800991E8[v0];
            b1 = D_800991E9[v0];
            b2 = D_800991EA[v0];
            do {
                row = buf + j * 0x80;
                poly = row + 0x10;
                SetPolyFT4((POLY_FT4 *)poly);
                SetShadeTex((POLY_FT4 *)poly, 0);
                row[0x11] = 0x24;
                *(u32 *)(row + 0x28) = (u32)(row + 0x60);
                *(u32 *)(row + 0x2C) = (u32)(row + 0x68);
                *(u32 *)(row + 0x30) = (u32)(row + 0x78);
                row[0x14] = b0;
                row[0x15] = b1;
                row[0x16] = b2;
                *(u32 *)(row + 0x34) = (u32)(row + 0x70);
                *(s16 *)(row + 0x1E) = GetTPage(
                    *(u16 *)ptr, 0, *(u16 *)(ptr - 0xC), *(u16 *)(ptr - 0xA));
                row[0x18] = ptr[-4] + 0x6F;
                row[0x19] = *(u16 *)(ptr - 2);
                row[0x1C] = ptr[-4] + 0x60;
                row[0x1D] = *(u16 *)(ptr - 2);
                row[0x20] = ptr[-4] + 0x6F;
                row[0x21] = ptr[-2] + 0xF;
                row[0x24] = ptr[-4] + 0x60;
                row[0x25] = ptr[-2] + 0xF;
                row[0x00] = 0;
                j++;
            } while (j < 10);
            i++;
        } while (i < D_800A2EB0Absolute[1]);
    }
}
#else
extern u8 D_800A342C[];
extern s32 D_800A3430[];
extern u8 D_80090F32[];
extern u8 D_800991E8[];
extern u8 D_800991E9[];
extern u8 D_800991EA[];
extern s32 D_800A2EB0Absolute[];
extern s32 D_800A3984[];
extern void *HeapAlloc(u32);

void func_80045F70(void) {
    u8 *buf;
    s8 i;
    u8 b0;
    u8 b1;
    u8 b2;
    s8 j;
    u8 *ptr;
    u8 *poly;
    u8 *row;
    s32 t;
    s32 u;
    s32 v0;
    s32 v1;

    i = 0;
    if (D_800A2EB0Absolute[1] > 0) {
        ptr = D_80090F32;
        do {
            D_800A342C[i] = 0;
            t = (s32)HeapAlloc(0x500);
            u = D_800A3984[0];
            D_800A3430[i] = t;
            v1 = *(s8 *)((i * 5 << 8) + u + 0x876);
            buf = (u8 *)t;
            j = 0;
            v0 = v1 * 3;
            b0 = D_800991E8[v0];
            b1 = D_800991E9[v0];
            b2 = D_800991EA[v0];
            do {
                row = buf + j * 0x80;
                poly = row + 0x10;
                SetPolyFT4((POLY_FT4 *)poly);
                SetShadeTex((POLY_FT4 *)poly, 0);
                row[0x11] = 0x24;
                *(u32 *)(row + 0x28) = (u32)(row + 0x60);
                *(u32 *)(row + 0x2C) = (u32)(row + 0x68);
                *(u32 *)(row + 0x30) = (u32)(row + 0x78);
                row[0x14] = b0;
                row[0x15] = b1;
                row[0x16] = b2;
                *(u32 *)(row + 0x34) = (u32)(row + 0x70);
                *(s16 *)(row + 0x1E) = GetTPage(
                    *(u16 *)ptr, 0, *(u16 *)(ptr - 0xC), *(u16 *)(ptr - 0xA));
                row[0x18] = ptr[-4] + 0x6F;
                row[0x19] = *(u16 *)(ptr - 2);
                row[0x1C] = ptr[-4] + 0x60;
                row[0x1D] = *(u16 *)(ptr - 2);
                row[0x20] = ptr[-4] + 0x6F;
                row[0x21] = ptr[-2] + 0xF;
                row[0x24] = ptr[-4] + 0x60;
                row[0x25] = ptr[-2] + 0xF;
                row[0x00] = 0;
                j++;
            } while (j < 10);
            i++;
        } while (i < D_800A2EB0Absolute[1]);
    }
}

#endif

extern s8 D_800A343C;
extern s8 *D_800A3444[];
extern s32 D_800BE980v asm("D_800BE980");

void func_80046184(s8 *arg0) {
    s8 *base;
    s8 *entry;
    s8 *tail;
    s8 count;
    s8 n;
    s8 i;
    s32 id;
    u16 flag;
    u8 *p;

    count = D_800A343C;
    base = D_800A3444[arg0[0x20B]];
    for (n = 1, i = 1, tail = base + 4; i < count; i++) {
        entry = (s8 *)(i * 0x58 + (s32)base);
        id = *(s16 *)entry;
        p = (u8 *)(id * 0x90 + D_800BE980v);
        flag = *(u16 *)(p + 0xE);
        if (flag != 0) {
            *(s32 *)(tail + 0x28) = (s32)(entry + 4);
            tail = entry + 4;
            n++;
        }
    }
    func_80032DEC((s32)(base + 4), n);
}

typedef struct {
    u16 tpx;
    u16 tpy;
    u16 clutX;
    u16 clutY;
    u8 u;
    u8 unk9;
    u8 v;
    u8 unkB;
    u16 tpage;
} SceneTexture;

extern SceneTexture D_80090F50[];
extern s8 *D_800A3444[];
extern s32 D_800AE15C[];
extern s32 D_800BE974[];
extern s32 D_800BE980[];
extern u8 D_800A3424;
extern s8 D_800A3438;
extern s8 D_800A343C;

void func_80046258(void) {
    extern u16 func_80030F24(u8 *, s32 *, s32, s32, s32);
    extern void func_8004658C(void);
    extern void SetPolyFT4(POLY_FT4 *);
    s32 heights[2];
    s32 point[3];
    u8 object[0x500];
    SceneTexture *tim;
    u8 *elem;
    u8 *objectPtr;
    s32 *pointPtr;
    u8 u;
    u8 v;
    u16 angle;
    s32 dist;
    s16 i;
    s16 j;

    tim = D_80090F50;
    D_800A3438 = 0x40 >> D_800A3424;
    D_800A343C = 0x40 >> (D_800A3424 - 1);
    for (i = 0; i < D_800A3424; i++) {
        D_800A3444[i] = HeapAlloc(D_800A343C * 0x58);
        for (j = 0; j < D_800A343C; j++) {
            elem = (u8 *)D_800A3444[i] + j * 0x58;
            SetPolyFT4((POLY_FT4 *)(elem + 4));
            SetSemiTrans(elem + 4, 1);
            SetShadeTex(elem + 4, 1);
            *(s16 *)(elem + 0xE) = GetClut(tim->clutX, tim->clutY);
            *(u32 *)(elem + 0x1C) = (u32)(elem + 0x30);
            *(u32 *)(elem + 0x20) = (u32)(elem + 0x38);
            *(u32 *)(elem + 0x24) = (u32)(elem + 0x48);
            *(u8 *)(elem + 0x5) = 0;
            *(u32 *)(elem + 0x28) = (u32)(elem + 0x40);
            *(u32 *)(elem + 0x2C) = 0;
            *(s16 *)(elem + 0x12) = GetTPage(tim->tpage, 2, tim->tpx, tim->tpy);
            *(u8 *)(elem + 0x6) = 0xE;
            u = tim->u;
            *(u8 *)(elem + 0x10) = u;
            *(u8 *)(elem + 0xC) = u;
            u = tim->u + 0x3F;
            *(u8 *)(elem + 0x18) = u;
            *(u8 *)(elem + 0x14) = u;
            v = tim->v + 0x1F;
            *(u8 *)(elem + 0x15) = v;
            *(u8 *)(elem + 0xD) = v;
            v = tim->v;
            *(u8 *)(elem + 0x19) = v;
            *(u8 *)(elem + 0x11) = v;
        }
    }
    *(u16 *)(object + 0x118) = 0;
    *(u16 *)(object + 0x1EC) = 2;
    for (i = 0; i < D_800BE974[0]; i++) {
        objectPtr = object;
        pointPtr = point;
        angle = *(u16 *)((u8 *)D_800BE980[0] + i * 0x90 + 0x10);
        *(u16 *)(object + 0x114) = angle;
        *(u16 *)(object + 0x116) = angle * 4;
        for (j = 0; j < 2; j++) {
            point[0] = *(s32 *)((u8 *)D_800AE15C[0] + i * 12);
            point[1] = *(s32 *)((u8 *)D_800AE15C[0] + i * 12 + 4);
            dist = 0x96;
            if (j != 0) {
                dist = -0x96;
            }
            func_80030F24(objectPtr, pointPtr, 0, dist, 0);
            heights[j] = point[2];
        }
        *(s32 *)((u8 *)D_800BE980[0] + i * 0x90 + 0x1C) =
            ((heights[0] + 0x4000) << 0x10) | (heights[1] + 0x4000);
    }
    func_8004658C();
}

INCLUDE_ASM("asm/nonmatchings/scene", func_8004658C);

INCLUDE_ASM("asm/nonmatchings/scene", func_80046BD4);

extern int abs(int);
extern u8 D_800A2FE8;
extern s8 D_800A3480;
extern s8 D_800A345C;
extern s8 D_800A3460;
extern u16 D_800A3464;
extern u16 D_800A3468;
extern u8 D_800A346C;
extern u8 D_800A3470;
extern u8 D_800A3474;
extern u16 D_80099254[];
extern u16 D_80099256[];
extern u16 D_80099258[];
extern u8 D_800A45F0[];
extern u8 D_800A46A0[];
extern u8 D_800A46A2[];
extern u8 D_800A46A4[];
extern MATRIX D_800A7530[];
extern s32 D_800A2EC8Absolute[];
extern SVECTOR D_800A2FEC;

void func_800474A0(void) {
    u32 *flagScratch = (u32 *)SCRATCHPAD_BASE;
    u32 *padScratch = (u32 *)(SCRATCHPAD_BASE + 0x120);
    u32 *unkScratch = (u32 *)(SCRATCHPAD_BASE + 0x240);
    s32 angleRaw;
    s32 absA3;
    s16 loopIdx;
    s16 segIdx;
    s32 s5v;
    s32 fpVal;
    s32 s4Off;
    s16 s2v;
    s32 s1v;
    u16 rot[3];
    MATRIX mat1;
    MATRIX mat2;
    SVECTOR vec;
    VECTOR out;
    s32 gteFlag;
    s32 t;
    s32 scratchW;
    s32 vyVal;
    s32 multTmp;
    u8 *car;
    u8 *row;
    s32 place;
    s32 c8val;
    s8 count;
    s8 fade;
    u8 *rec;
    u8 *node;
    MATRIX *transPtr;
    u8 *prim;
    u8 *primNext;
    s32 otBaseW;
    SVECTOR **verts;
    s32 primCount;
    s32 angC;

    if (D_800A2FE8 == 0) {
        return;
    }
    angleRaw = D_800A3480;
    flagScratch[0] = 0;
    flagScratch[9] = 1;
    padScratch[0] = 0;
    padScratch[9] = 1;
    unkScratch[0] = 0;
    unkScratch[9] = 2;
    flagScratch[1] = 0;
    flagScratch[10] = 3;
    padScratch[1] = 0;
    padScratch[10] = 0;
    unkScratch[1] = 0;
    unkScratch[10] = 6;
    flagScratch[2] = 0;
    flagScratch[11] = 3;
    padScratch[2] = 0;
    padScratch[11] = 0;
    unkScratch[2] = 0;
    unkScratch[11] = 7;
    flagScratch[3] = 2;
    flagScratch[12] = 3;
    padScratch[3] = 3;
    padScratch[12] = 0;
    unkScratch[3] = 2;
    unkScratch[12] = 8;
    flagScratch[4] = 8;
    flagScratch[13] = 3;
    padScratch[4] = 3;
    padScratch[13] = 0;
    unkScratch[4] = 3;
    unkScratch[13] = 9;
    flagScratch[5] = 0x10;
    flagScratch[14] = 5;
    padScratch[5] = 3;
    padScratch[14] = 0;
    unkScratch[5] = 4;
    unkScratch[14] = 0xa;
    flagScratch[6] = 1;
    flagScratch[15] = 5;
    padScratch[6] = 0;
    padScratch[15] = 0;
    unkScratch[6] = 1;
    unkScratch[15] = 0xb;
    flagScratch[7] = 1;
    flagScratch[16] = 5;
    padScratch[7] = 1;
    padScratch[16] = 0;
    unkScratch[7] = 1;
    unkScratch[16] = 0xc;
    flagScratch[8] = 1;
    flagScratch[17] = 5;
    padScratch[8] = 0;
    padScratch[17] = 0;
    unkScratch[8] = 2;
    unkScratch[17] = 0xd;
    c8val = D_800A2EC8Absolute[0];
    absA3 = abs(angleRaw);
    if (c8val != 0) {
        D_800A3468 = 0;
        D_800A3474 = 0;
        D_800A3460 = 0;
        D_800A3470 = 0;
    } else {
        if (D_800A345C < 0xA) {
            car = D_800A3554[0];
            place = *(s16 *)(car + 0x10C);
            if (place != 0) {
                row = car + place * 24;
                if (*(s16 *)(car + 0x108) < *(s32 *)(row + 0x130) + 0x3E8) {
                    D_800A346C = 1;
                    goto afterCounter;
                }
            }
            if (place < 3 && *(s16 *)(car + 0x108) >= 0x2EE1) {
                D_800A346C = 1;
            }
        }
    afterCounter:
        if (D_800A346C != 0) {
            count = ++D_800A345C;
        } else if (D_800A345C != 0) {
            count = --D_800A345C;
        } else {
            count = 0;
        }
        D_800A345C = count;
        if (count >= 0xA) {
            D_800A346C = 0;
        }
        if ((func_80041B7C(0) & 0x10) != 0 && D_800A345C == 0) {
            D_800A3470 = 1;
        } else {
            D_800A3468 = 0;
            D_800A3474 = 0;
            D_800A3460 = 0;
            D_800A3470 = 0;
        }
        if (D_800A3470 != 0) {
            if (D_800A3460 < 0xA) {
                fade = ++D_800A3460;
            } else {
                fade = 0xA;
            }
        } else {
            fade = 0;
        }
        D_800A3460 = fade;
    }
    loopIdx = 0;
    do {
        if (loopIdx != 0) {
            if (D_800A345C != 0) {
                multTmp = D_800A345C * (D_800A3480 << 2);
                rot[0] =
                    D_80099254[(s16)loopIdx * 3] - ((s16)absA3 >> 1) + multTmp;
                multTmp = D_800A345C * (0x40 - D_800A3480 * 2);
                rot[1] = D_80099256[(s16)loopIdx * 3];
                rot[2] = D_80099258[(s16)loopIdx * 3] - multTmp;
                D_800A2FEC.vz = D_800A3480 - D_800A3480 * 16;
                RotMatrix(&D_800A2FEC, (MATRIX *)D_800A7530);
                goto afterRot;
            }
        } else {
            if (D_800A3460 != 0) {
                rot[0] = D_80099254[0] - D_800A3460 * 64;
                rot[1] = D_80099256[0] + D_800A3460 * 32;
                rot[2] = (D_80099258[0] + (D_800A3460 << 5)) & 0xFFF;
                if (D_800A3460 == 0xA) {
                    if (D_800A2EC8Absolute[0] == 0) {
                        if (D_800A3474 != 0) {
                            D_800A3468 = D_800A3468 - 0x20;
                            if ((D_800A3468 << 16) == 0) {
                                D_800A3474 = 0;
                            }
                        } else {
                            D_800A3468 = D_800A3468 + 0x20;
                            if ((D_800A3468 << 16 >> 16) == 0x100) {
                                D_800A3474 = 1;
                            }
                        }
                    }
                    rot[2] = rot[2] - D_800A3468;
                }
                D_800A2FEC.vz = 0;
                RotMatrix(&D_800A2FEC, (MATRIX *)D_800A7530);
                goto afterRot;
            }
        }
        rot[0] = D_80099254[(s16)loopIdx * 3] - ((s16)absA3 >> 1);
        rot[1] = D_80099256[(s16)loopIdx * 3];
        rot[2] = D_80099258[(s16)loopIdx * 3];
        angC = D_800A3480;
        D_800A2FEC.vz = angC - angC * 16;
        RotMatrix(&D_800A2FEC, (MATRIX *)D_800A7530);
    afterRot:
        if (loopIdx != 0) {
            if (D_800A3480 < 0) {
                goto doSub;
            }
        } else if (D_800A3480 > 0) {
            goto doSub;
        } else {
            goto vecSetup;
        }
        goto vecSetup;
    doSub:
        rot[0] = rot[0] - ((s16)absA3 >> 1);
    vecSetup:
        vec.vx = 0x1000 - rot[0];
        vec.vy = 0x1000 - rot[1];
        vec.vz = 0x1000 - rot[2];
        RotMatrix(&vec, &mat1);
        segIdx = 0;
        s5v = (s16)loopIdx;
        t = s5v * 2;
        fpVal = t - 1;
        t = t + s5v;
        s4Off = ((t << 6) - t) << 5;
        do {
            s2v = D_800A3464;
            if (s5v != 0) {
                if (D_800A345C != 0) {
                    if (D_800A345C < 3) {
                        D_800A3464 = s2v - D_800A345C * 160;
                    } else {
                        D_800A3464 = 0x80;
                    }
                }
            } else {
                if (D_800A3460 != 0) {
                    D_800A3464 = s2v - D_800A3460 * 36;
                }
            }
            vec.vx = 0x1000 - (s16)D_800A3464 * flagScratch[(s16)segIdx] *
                                  (flagScratch[(s16)segIdx] & 1);
            scratchW = flagScratch[(s16)segIdx];
            if ((scratchW & 1) == 0) {
                vyVal = ((s16)D_800A3464 >> 3) * scratchW * fpVal;
            } else {
                vyVal = 0;
            }
            vec.vy = vyVal;
            if (s5v == 0 && (s16)segIdx != 0 && D_800A3460 == 0xA) {
                vec.vz = D_800A3468 << 16 >> 17;
            } else {
                vec.vz = 0;
            }
            RotMatrix(&vec, &mat2);
            MulMatrix2(&mat1, &mat2);
            SetRotMatrix(&mat2);
            if ((s16)segIdx != 0) {
                mat1.t[0] = ((
                    s16 *)D_800A46A0)[(padScratch[(s16)segIdx] * 20 +
                                       unkScratch[(s16)segIdx] * 336 + s4Off) /
                                      2];
                mat1.t[1] = ((
                    s16 *)D_800A46A2)[(padScratch[(s16)segIdx] * 20 +
                                       unkScratch[(s16)segIdx] * 336 + s4Off) /
                                      2];
                mat1.t[2] = ((
                    s16 *)D_800A46A4)[(padScratch[(s16)segIdx] * 20 +
                                       unkScratch[(s16)segIdx] * 336 + s4Off) /
                                      2];
            } else {
                mat1.t[2] = 0;
                mat1.t[1] = 0;
                mat1.t[0] = 0;
            }
            SetTransMatrix(&mat1);
            D_800A3464 = s2v;
            if ((s16)segIdx != 0 || (s5v == 0 && D_800A3460 != 0)) {
                s2v = 0;
                s1v = (s16)segIdx;
            vtxLoopA:
                do {
                    rec =
                        s4Off + D_800A45F0 + s1v * 336 + ((s16)s2v * 20 + 0xB0);
                    vec.vx = *(u32 *)(rec + 8);
                    vec.vy = *(u32 *)(rec + 0xC);
                    vec.vz = *(u32 *)(rec + 0x10);
                    RotTrans(&vec, &out, &gteFlag);
                    *(u16 *)rec = out.vx;
                    *(u16 *)(rec + 2) = out.vy;
                } while (0);
                *(u16 *)(rec + 4) = out.vz;
                s2v += 1;
                if (s2v < 8) {
                    goto vtxLoopA;
                }
            } else {
                s2v = 0;
                s1v = (s16)segIdx;
            vtxLoopB:
                do {
                    rec =
                        s4Off + D_800A45F0 + s1v * 336 + ((s16)s2v * 20 + 0xB0);
                    vec.vx = *(u32 *)(rec + 8);
                    vec.vy = *(u32 *)(rec + 0xC);
                    if ((u16)(s2v - 2) < 2 || (u16)(s2v - 6) < 2) {
                        vec.vz = *(u32 *)(rec + 0x10) + (s16)absA3 * 3 - 0x1E;
                    } else {
                        vec.vz = *(u32 *)(rec + 0x10);
                    }
                    RotTrans(&vec, &out, &gteFlag);
                    *(u16 *)rec = out.vx;
                    *(u16 *)(rec + 2) = out.vy;
                } while (0);
                *(u16 *)(rec + 4) = out.vz;
                s2v += 1;
                if (s2v < 8) {
                    goto vtxLoopB;
                }
            }
            segIdx += 1;
        } while (segIdx < 0x12);
        SetRotMatrix((MATRIX *)D_800A7530);
        if (loopIdx == 0 && D_800A3460 != 0) {
            transPtr = &mat1;
            mat1.t[0] = D_800A3460 * 4;
            mat1.t[1] = D_800A3460 * 8 + 0x64;
            mat1.t[2] = D_800A3460 * 16;
        } else {
            transPtr = (MATRIX *)D_800A7530;
        }
        SetTransMatrix(transPtr);
        if (loopIdx != 0 && D_800A345C >= 5) {
            ;
        } else {
            prim = (u8 *)gPrimitiveCursor[0];
            node = D_800A45F0 + (s16)loopIdx * 6048;
            primCount = 0x48;
            otBaseW = D_800A39C8[0];
            primNext = prim + 0x10;
            do {
                verts = (SVECTOR **)(node + 0x18);
                gte_ldv3(verts[0], verts[1], verts[2]);
                gte_rtpt();
                gte_avsz3();
                *(u32 *)(primNext - 0xC) = *(u32 *)(node + 4);
                gte_stsxy3(prim + 8, prim + 0xC, prim + 0x14);
                gte_ldv0(verts[3]);
                gte_rtps();
                gte_stsxy(primNext);
                GraphicsAddTaggedPrimitive(
                    (u32 *)(otBaseW + *(s8 *)(node + 1) * 4), (u32 *)prim,
                    0x05000000);
                node = *(u8 **)(node + 0x28);
                primCount--;
                primNext += 0x18;
                prim += 0x18;
            } while (primCount > 0);
            gPrimitiveCursor[0] = (u32)prim;
        }
        loopIdx += 1;
    } while (loopIdx < 2);
}

INCLUDE_ASM("asm/nonmatchings/scene", func_80048118);

extern s32 D_800A2EC0nm[] asm("D_800A2EC0.NON_MATCHING");
extern s32 D_800A3550[];
extern u8 *D_800A3554[];
extern s32 D_800A397C[];
extern s32 D_800A3A3C[];
extern s32 D_800A3A90[];
extern s16 D_800A35A4w40;
extern u8 *D_800A347C;
extern void *D_800A3728;
extern void func_80016CD8(u8 *, s32);
extern s32 func_80037204(u8 *);
extern s32 func_8003702C(u8 *, u8 *);
extern void func_8004875C(void);
extern u8 *D_800A3554again[];
asm(".globl D_800A3554again\nD_800A3554again = D_800A3554");
asm(".globl D_800A35A4w40\nD_800A35A4w40 = D_800A35A4");

void func_80048568(void) {
    s32 target;

    if (D_800A397C[0] == 2) {
        if (D_800A3A3C[0] < D_800A3550[0]) {
            target = D_800A2EC0nm[0] - (D_800A3550[0] - D_800A3A3C[0]) + 1;
        } else {
            target = D_800A2EC0nm[0] -
                     (D_800A3550[0] + (D_800A3A90[0] - D_800A3A3C[0])) + 1;
        }
        if (target >= *(s32 *)(D_800A347C + 0xC) &&
            *(s32 *)(D_800A347C + 0x10) >= target) {
            func_80016CD8(D_800A347C, 0);
        }
    } else if (D_800A3728 != 0) {
        if (D_800A347C[0x401] != 0) {
            func_80016CD8(D_800A347C, 0);
            if (D_800A35A4w40 <= 0 && func_80037204((u8 *)D_800A3728) != 0) {
                D_800A3728 = 0;
                *(s32 *)(D_800A347C + 0x10) = D_800A2EC0nm[0];
            }
        } else {
            if (func_8003702C((u8 *)D_800A3728, D_800A3554[0]) < 0) {
                if (-func_8003702C((u8 *)D_800A3728, D_800A3554again[0]) >=
                    0x19) {
                    goto fail;
                }
            } else {
                if (func_8003702C((u8 *)D_800A3728, D_800A3554again[0]) >=
                    0x19) {
                fail:
                    func_8004875C();
                }
            }
        }
    }
}

extern u8 *D_800A347C;
extern void *D_800A3728;
extern void func_8002D4CC(u8 *);

void func_80048700(void) {
    D_800A3728 = 0;
    D_800A347C = HeapAlloc(0x500);
    *(s16 *)(D_800A347C + 0x1EC) = 2;
    func_8002DA30((s32 *)D_800A347C);
    func_8002D4CC(D_800A347C);
    func_8002D3A8(D_800A347C, -4);
    *(s32 *)(D_800A347C + 0x10) = -1;
    *(s32 *)(D_800A347C + 0xC) = -1;
}

#ifdef NON_MATCHING
/* 2026-10-11 parked at 5230 (0x158 vs 0x148). Structure, calls, table load,
 * copies and all three multiply blocks decode cleanly; Ghidra's retail
 * decompile supplied the call shapes (func_80031264 takes a0 only). Residual:
 * retail shares one D_800A347C base pseudo across the first store and the
 * next call's argument (store sinks into the call's delay slot); this gcc's
 * cse never reuses a gp-load across a store-through-pointer (probed), so the
 * draft emits an extra base load (+4 bytes) and the final-block register
 * ties follow from it. */
void func_8004875C(void) {
    extern s32 D_800BE980[];
    extern void func_80031264(u8 * object);
    extern void func_80037130(u8 * object);
    extern s32 MathMultiplyFixed16(s32, s32);
    extern s32 D_800A2EC0Absolute[];
    u8 *src;
    u8 *dst;
    u16 val;

    val = *(u16 *)((u8 *)D_800BE980[0] + *(s16 *)(D_800A3728 + 0x1E0) * 0x90 +
                   0x10);
    *(u16 *)(D_800A3728 + 0x114) = val;
    *(u16 *)(D_800A3728 + 0x104) = val;
    *(u16 *)(D_800A3728 + 0x116) = *(u16 *)(D_800A3728 + 0x114) * 4;
    func_80031264(D_800A3728);
    func_80037130(D_800A3728);
    src = D_800A3728;
    dst = D_800A347C;
    *(u32 *)(dst + 0) = *(u32 *)(src + 0);
    *(u32 *)(dst + 4) = *(u32 *)(src + 4);
    *(u32 *)(dst + 8) = *(u32 *)(src + 8);
    *(u16 *)(dst + 0x104) = *(u16 *)(dst + 0x114) = *(u16 *)(src + 0x114);
    *(u16 *)(dst + 0x116) = *(u16 *)(src + 0x116);
    func_80037130(dst);
    func_80031264(D_800A347C);
    *(s32 *)(D_800A347C + 0) +=
        MathMultiplyFixed16(*(s32 *)(D_800A347C + 0x3C), 0x3200000) >> 16;
    *(s32 *)(D_800A347C + 4) +=
        MathMultiplyFixed16(*(s32 *)(D_800A347C + 0x40), 0x3200000) >> 16;
    *(s32 *)(D_800A347C + 8) +=
        MathMultiplyFixed16(*(s32 *)(D_800A347C + 0x44), 0x3200000) >> 16;
    *(u8 *)(D_800A347C + 0x401) = 1;
    *(s32 *)(D_800A347C + 0xC) = D_800A2EC0Absolute[0];
    *(s32 *)(D_800A347C + 0x10) = 0x7FFFFFFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/scene", func_8004875C);
#endif

extern u8 *D_800A347C;
extern void *D_800A3728;
void func_800488A4(u8 *object) {
    u8 *state;
    state = D_800A347C;
    *(s32 *)(object + 0x90) = 0;
    D_800A3728 = object;
    state[0x401] = 0;
}

INCLUDE_ASM("asm/nonmatchings/scene", func_800488B8);

extern u8 D_800A38F0;
extern u8 D_800A35FCnm asm("D_800A35FC.NON_MATCHING");
extern s32 D_800A2EB0Absolute[];
extern s32 D_800A37D0[];
extern s32 D_800A37D4nm[] asm("D_800A37D4.NON_MATCHING");
extern s32 D_800A2E94[];
extern s32 D_800AE1EC[];
extern s32 D_800A2EA8[];
extern s32 D_800A7550[];
extern u8 *D_800A3878nm[] asm("D_800A3878.NON_MATCHING");

void func_80048C90(void) {
    extern s32 D_800A2E94nm[] asm("D_800A2E94.NON_MATCHING");
    s8 buf[24];
    s8 *p;
    s8 i;
    s8 j;
    s8 idx;
    u8 *node;
    s32 scale;
    s32 count;
    s32 limit;
    register s32 raw asm("$2");
    s32 a1val;
    s32 r0;
    s32 r2;
    s32 cnt;

    if (D_800A38F0 == 0 || (count = D_800A2EB0Absolute[0]) != 0) {
        D_800A35FCnm = 0;
        return;
    }
    r0 = RandomScaledGet((D_800A37D0[0] - 1) / 50 + 3);
    cnt = D_800A2E94[0];
    limit = 0x18 / cnt;
    D_800A35FCnm = ((D_800A37D4nm[-1] + 0x18) / 50 + r0) / limit;
    if (count < cnt) {
        i = 0;
        p = buf;
    clear:
        p[i] = 0;
        i++;
        if (i < D_800A2E94nm[0]) {
            goto clear;
        }
    }
    scale = MathFixedDivide(D_800AE1EC[0] * 0x14, 0x7D00);
    for (i = 0; i < D_800A35FCnm; i++) {
        do {
            raw = RandomScaledGet(D_800A2E94[0]);
            idx = (s8)raw;
        } while (buf[idx] != 0);
        count = raw;
        node = D_800A3878nm[0];
        for (j = 0; j < idx; j++) {
            node = *(u8 **)(node + 0x3E0);
        }
        a1val = D_800A2EA8[0];
        D_800A7550[i] = node;
        r2 = RandomScaledGet(MathMultiplyFixed16(scale, (a1val - 1) << 16) >>
                             16);
        *(s32 *)(node + 0x414) = (scale >> 16) + r2;
        buf[(s8)count] = 1;
    }
}

/* Draws the race HUD for one car: the tachometer segments, speed bar and
 * needle, lap and place text, and the driver warning messages. yOffset moves
 * the whole layout vertically (split screen). The field names are placeholders
 * until the full Car layout is known. */
typedef struct HudCar {
    u8 unk0[0x84];
    s32 unk84;
    u8 unk88[0x90 - 0x88];
    s32 unk90;
    u8 unk94[0xF4 - 0x94];
    u8 unkF4;
    u8 unkF5;
    u8 unkF6;
    u8 unkF7;
    u8 unkF8;
    u8 unkF9;
    u8 unkFA[0x108 - 0xFA];
    s16 unk108;
    u8 unk10A[0x10C - 0x10A];
    s16 unk10C;
    u8 unk10E[0x110 - 0x10E];
    s16 unk110;
    u8 unk112[0x114 - 0x112];
    s16 unk114;
    u8 unk116[0x1BC - 0x116];
    s16 unk1BC;
    u8 unk1BE[0x1D6 - 0x1BE];
    s16 lap;
    u8 unk1D8[0x1E0 - 0x1D8];
    s16 unk1E0;
    u8 unk1E2[0x204 - 0x1E2];
    s8 place;
    u8 unk205[0x209 - 0x205];
    s8 unk209;
    u8 unk20A;
    u8 unk20B;
    s8 unk20C;
    u8 unk20D;
    s16 unk20E;
    u8 unk210[0x258 - 0x210];
    s32 unk258;
    s32 unk25C;
    u8 unk260[0x268 - 0x260];
    u8 unk268;
    u8 unk269[0x28C - 0x269];
    s32 unk28C;
    u8 unk290[0x2B8 - 0x290];
    s32 unk2B8;
    u8 unk2BC[0x354 - 0x2BC];
    void (*unk354)(u8 *);
    u8 unk358[0x3A4 - 0x358];
    u32 unk3A4;
    u8 unk3A8[0x3B7 - 0x3A8];
    u8 unk3B7;
    u8 unk3B8[0x3FC - 0x3B8];
    u8 unk3FC;
    s8 unk3FD;
    u8 unk3FE[0x401 - 0x3FE];
    u8 unk401;
    s16 unk402;
    u8 unk404[0x40C - 0x404];
    s32 unk40C;
    u8 unk410;
    u8 unk411[0x414 - 0x411];
    s32 unk414;
} HudCar;

typedef struct HudLayout {
    s16 unk0;
    s16 unk2;
    u8 unk4[4];
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    u8 unk1C[0x1C];
} HudLayout;

typedef struct HudPoint {
    u16 x;
    u16 y;
} HudPoint;

typedef struct HudVertex {
    s16 x;
    s16 y;
} HudVertex;

typedef struct HudNode {
    u8 unk0[0x10];
    u16 unk10;
    u8 unk12[0x90 - 0x12];
} HudNode;

extern s16 D_800A38E4[];
extern s32 D_800A39C8Absolute[];
extern s32 D_800A39C4nm[] asm("D_800A39C4.NON_MATCHING");
extern s32 D_800A39CCnm[] asm("D_800A39CC.NON_MATCHING");
extern s32 D_800A2E50[];
extern s8 *D_800A78C4[];
extern u8 D_800A372C;
extern u8 D_800A3490;
extern u8 D_800A3485;
extern u8 D_800A3488;
extern u8 D_800A3484[];
extern u8 D_800A3680Small asm("D_800A3680.NON_MATCHING");
extern s32 D_800A2ED0Hud[] asm("D_800A2ED0.NON_MATCHING");
extern s16 D_800A3910;
extern u8 D_80099260[][0x38];
extern HudLayout D_8009927C[];
extern HudVertex D_8009933C[];
extern u8 D_800A7568[];
extern u8 D_800A7569[];
extern u8 D_800A756A[];
extern u16 D_800A756C[];
extern u16 D_800A756E[];
extern u16 D_800A7570[];
extern u16 D_800A7572[];
extern u16 D_800A7574[];
extern u16 D_800A7576[];
extern u16 D_800A7578[];
extern u16 D_800A757A[];
extern POLY_FT4 D_800A757C[];
extern POLY_FT4 D_800A770C[];
extern TILE D_800A7924[];
extern TILE D_800A7954[];
extern u8 D_800A78D4[];
extern u8 D_800A78FC[];
extern char D_800A2FF4[];
extern char D_800A2FF8[];
extern char D_800A2FFC[];
extern char *D_8009ADD8[];
extern char *D_8009ADF8[];
extern char *D_8009ADFC[];
extern char *D_8009AE00[];
extern char *D_8009AE0C[];
extern char *D_8009AE10[];
extern s32 sprintfHud(char *, char *, ...) asm("sprintf");
extern void func_8004AFE0(s8, u16 *, u16 *);
extern void func_800188B0(s32, s32, s32, s32, s32);
extern void func_80044A1C(s16, s16, s16, s16, u8, u8, u8, u8);
extern void GraphicsSetColor(u8, u8, u8);
extern s16 HudTextWidth(u8 *) asm("func_80050940");
extern void HudDrawText(char *, s32, s16, s32) asm("func_80050028");
extern void func_80052FC4(s8);
extern void func_80041564Hud(HudCar *, s32) asm("func_80041564");

/* Value that D_800A3480 follows, the field at 0x20E of the car in
 * D_800A3554. */
#define HUD_STEER_TARGET (((HudCar *)D_800A3554[0])->unk20E)

/* Centred warning text with a box behind it. */
#define HUD_MESSAGE(text, ty)                                                  \
    {                                                                          \
        s16 w;                                                                 \
        s32 x;                                                                 \
        w = HudTextWidth((u8 *)(text)[0]);                                     \
        x = (0x140 - w) >> 1;                                                  \
        HudDrawText((text)[0], x, yOffset + (ty), 0);                          \
        func_80044A1C(x - 0xA, yOffset + (ty) - 1, w + 0x14, 0xD, 0, 0, 0, 1); \
    }

void HudDrawCar(HudCar *car, s16 yOffset) {
    char buf[8];
    HudPoint pts[4];
    u16 ang;
    u8 flag;
    u8 split;
    s8 level;
    s8 cur;
    s8 nv;
    s16 i;
    POLY_FT4 *seg;
    TILE *tiles;
    u8 *needle;
    u8 *prim;
    u8 count;
    s16 tw;
    s32 sinV;
    s32 cosV;
    s16 idx;
    s32 scaled;
    s32 green;
    u8 red;
    s32 frac;
    HudLayout *layout;

    split = 0;
    flag = 0;
    if (car->unk20C != 0 || D_800A2EA4[0] != 0) {
        split = 1;
    }
    if (D_800A2ED4[0] == 0) {
        if (car->unk3FC != 0) {
            level =
                (s32)((D_800A2E50[0] - D_800A38E4[0]) * 10) / D_800A2E50[0] + 2;
        } else {
            level = 0;
        }
        if (level >= 11) {
            level = 10;
        }
        cur = car->unk3FD;
        if (cur < level) {
            car->unk3FD = cur + 1;
        } else if (level < cur) {
            car->unk3FD = cur - 1;
        }
        if (D_800A372C != 0 && car->unk401 != 0) {
            car->unk402 =
                car->unk402 <= car->unk108 - 0x64
                    ? car->unk402 + 0x64
                    : (car->unk402 >= car->unk108 + 0x64 ? car->unk402 - 0x64
                                                         : car->unk108);
            car->unk40C = car->unk90 - 0x10000 >= car->unk40C
                              ? car->unk40C + 0x10000
                              : (car->unk40C >= car->unk90 + 0x10000
                                     ? car->unk40C - 0x10000
                                     : car->unk90);
        } else {
            car->unk402 =
                car->unk402 <= car->unk108 - 0x3E8
                    ? car->unk402 + 0x3E8
                    : (car->unk402 >= car->unk108 + 0x3E8 ? car->unk402 - 0x3E8
                                                          : car->unk108);
            car->unk40C = car->unk90 - 0x140000 >= car->unk40C
                              ? car->unk40C + 0x140000
                              : (car->unk40C >= car->unk90 + 0x140000
                                     ? car->unk40C - 0x140000
                                     : car->unk90);
        }
        /* D_800A3480 eases toward the target by 1, 4 or 8 a frame and is then
         * clamped. The three stores in the first arms name the byte three ways
         * so that gcc does not cross-jump them into the shared store. */
        i = ABS(D_800A3480 - HUD_STEER_TARGET);
        if (i < 5) {
            if (D_800A3480 < HUD_STEER_TARGET) {
                nv = D_800A3480 + 1;
                (&D_800A3460)[0x20] = nv;
            } else if (HUD_STEER_TARGET < D_800A3480) {
                nv = D_800A3480 - 1;
                (&D_800A345C)[0x24] = nv;
            } else {
                nv = HUD_STEER_TARGET;
                D_800A3480 = nv;
            }
        } else if (i < 13) {
            nv =
                D_800A3480 < HUD_STEER_TARGET ? D_800A3480 + 4 : D_800A3480 - 4;
            D_800A3480 = nv;
        } else {
            nv =
                D_800A3480 < HUD_STEER_TARGET ? D_800A3480 + 8 : D_800A3480 - 8;
            D_800A3480 = nv;
        }
        if (nv >= 0x35) {
            D_800A3480 = 0x34;
        } else if (nv < -0x34) {
            D_800A3480 = -0x34;
        }
    }
    if (D_800A2EA4[0] == 0) {
        if (D_800A3680Small != 0) {
            func_8004AFE0(0, (u16 *)D_80099260[split],
                          (u16 *)D_800A78C4[gOrderingTableBankAbsolute[0]]);
            D_800A3490 = 1;
            D_800A3680Small = 0;
        } else if (D_800A3490 != 0) {
            func_8004AFE0(0, (u16 *)D_80099260[split],
                          (u16 *)D_800A78C4[gOrderingTableBankAbsolute[0]]);
            D_800A3490 = 0;
        }
    }
    if (D_800A2EACAbsolute[0] == 0 && D_800A2ED0Hud[0] == 0 &&
        D_800A397C[0] != 2) {
        if (car->unk209 != 0) {
            D_800A39C8Absolute[0] = D_800A39C8[0] + 4;
            if (split) {
                if (car == (HudCar *)D_800A3554[0]) {
                    seg = D_800A757C;
                    needle = D_800A78D4;
                    tiles = D_800A7924;
                } else {
                    seg = D_800A770C;
                    needle = D_800A78FC;
                    tiles = D_800A7954;
                }
                for (i = 0; i < car->unk3FD; i++) {
                    seg[i].b0 = 0xFF;
                    func_80017D80((u8 *)&seg[i]);
                }
                for (i = car->unk3FD; i < 10; i++) {
                    seg[i].b0 = 0x40;
                    func_80017D80((u8 *)&seg[i]);
                }
                tw = car->unk28C / 400;
                tiles[1].x0 = tw + 0xD;
                tiles[0].w = tw;
                tiles[1].w = 0x28 - tw;
                for (i = 0; i < 3; i++) {
                    func_80017D80((u8 *)&tiles[i]);
                }
                ang = (car->unk402 * 0x1F40) / 13250 + 0x3E8;
                scaled = (s16)ang << 8;
                idx = (car->unkF6 != 0 || car->unk10C == car->unk110 ||
                               ((u8 *)D_800A2F9DAbsolute)[-0x45] != 0
                           ? scaled / 10000
                           : scaled / 9000) +
                      0x200;
                sinV = ((s32 *)D_800A3A2CAbsolute[0])[idx];
                cosV = ((s32 *)D_800A3A34Absolute[0])[idx];
                for (i = 0; i < 4; i++) {
                    pts[i].x =
                        ((MathMultiplyFixed16(sinV, D_8009933C[i].x << 16) -
                          MathMultiplyFixed16(cosV, D_8009933C[i].y << 16)) >>
                         16) +
                        0x12C;
                    pts[i].y =
                        ((MathMultiplyFixed16(cosV, D_8009933C[i].x << 16) +
                          MathMultiplyFixed16(sinV, D_8009933C[i].y << 16)) >>
                         16) +
                        (yOffset + 0xD6);
                }
                if ((s16)ang < 3000) {
                    D_800A7568[0] = 0;
                    green = 0x80;
                } else {
                    frac = ((s16)((s16)ang % 3000) << 7) / 3000;
                    red = frac; /* separate byte copy of the quotient */
                    if ((s16)ang < 6000) {
                        D_800A7568[0] = red;
                        green = 0x80;
                    } else {
                        D_800A7568[0] = 0x80;
                        green = 0x80 - frac;
                    }
                }
                D_800A7569[0] = green;
                D_800A756A[0] = 0;
                /* Ends the scheduling block: the stores above stay ahead of
                 * the loads below. The branch itself is removed. */
                if (i == -1) {
                    i = 0;
                }
                D_800A756C[0] = pts[0].x;
                D_800A756E[0] = pts[0].y;
                D_800A7570[0] = pts[1].x;
                D_800A7572[0] = pts[1].y;
                D_800A7574[0] = pts[2].x;
                D_800A7576[0] = pts[2].y;
                D_800A7578[0] = pts[3].x;
                D_800A757A[0] = pts[3].y;
                func_80017D80((u8 *)D_800A756C - 8);
                func_80017D80(needle);
                count = D_800A3484[split];
                prim = (u8 *)D_800A78C4[gOrderingTableBankAbsolute[0]];
            } else {
                count = D_800A3485 - D_800A3488;
                prim = (u8 *)D_800A78C4[gOrderingTableBankAbsolute[0]] +
                       D_800A3488 * 0x28;
            }
            FontSetColor(0x80, 0x80, 0x40);
            for (i = 0; i < count; i++) {
                AddPrim((void *)D_800A39C8[0], prim);
                prim += 0x28;
            }
            layout = &D_8009927C[split];
            if (D_800A2EB0Absolute[0] == 2) {
                func_8001832C(D_800A2FF4, layout->unk8, layout->unkA + yOffset,
                              2);
                sprintfHud(buf, D_800A2FF8, car->lap);
            } else {
                func_80018B18(car->place,
                              layout->unk8 + (D_800A2EA4[0] != 0 ? 5 : 0),
                              layout->unkA + yOffset, 2);
                sprintfHud(buf, D_800A2FFC, car->lap, D_800A2EA8[0]);
            }
            func_8001832C(buf, layout->unkC, layout->unkE + yOffset, 2);
            func_80018768((void *)(car->lap != 0 ? car->unk258 : 0x7FFFFFFF),
                          layout->unk10, layout->unk12 + yOffset, 2);
            func_80018768((void *)car->unk25C, layout->unk14,
                          layout->unk16 + yOffset, 2);
            if (split) {
                func_800188B0(car->unk40C, car->unkF7, layout->unk0,
                              layout->unk2 + yOffset, 2);
                func_80018B18(car->unk10C + 1, layout->unk18,
                              layout->unk1A + yOffset, 2);
            } else {
                D_800A39C8Absolute[0] = D_800A39C8nm[0] + 0x2C;
                FontSetColor(0x40, 0x40, 0x40);
                func_80018B18(car->unk10C + 1, layout->unk18,
                              layout->unk1A + yOffset, 2);
                D_800A39CCnm[-1] = D_800A39C4nm[1] - 0x2C;
            }
            D_800A39C8Absolute[0] = D_800A39C8[0] - 4;
        }
        if (D_800A2EC8[0] == 0) {
            if (D_800A2EDC[0] != 0 && car->unkF4 != 0 &&
                (car->unk354 != func_80025730 ? (car->unk3A4 & 0x100F) != 0
                                              : car->unk1BC == 4)) {
                if (D_800A2EE0[0] != 0) {
                    if (car->unk3B7 == 0) {
                        GraphicsSetColor(0xFF, 0x40, 0x40);
                        HUD_MESSAGE(D_8009ADD8, 0xA5);
                    }
                } else if (car->unk90 == 0) {
                    car->unkF9 = 0;
                    car->unk90 = 0;
                    car->unk84 = 0;
                    car->unk410 = 0;
                    car->unk414 = -1;
                    func_80052FC4(0);
                    func_80041564Hud(car, 0x44);
                    car->unkF4 = 0;
                }
                flag = 1;
                D_800A3910 = 0x7FFF;
            }
            if (D_800A2EA4[0] != 0 && D_800A2EDC[0] != 0 &&
                D_800A2EE0[0] == 0 && (car->unk3A4 & 0x100F)) {
                GraphicsSetColor(0xFF, 0x40, 0x40);
                HUD_MESSAGE(D_8009AE10, 0xD2);
                return;
            }
            if (car->unk268 == 0) {
                if (car->unk28C == 0) {
                    GraphicsSetColor(0xFF, 0x40, 0x40);
                    HUD_MESSAGE(D_8009ADFC, 0xB4);
                    if (car->unkF4 != 0 && car->unk90 == 0) {
                        car->unk414 = -1;
                        func_8003F914((s8)(car->unk20B * 2 + 0xE));
                        func_80041564Hud(car, 0x44);
                        car->unkF4 = 0;
                    }
                } else if (flag == 0) {
                    if (car->unk28C < 0x800) {
                        GraphicsSetColor(0xFF, (car->unk28C >> 4) + 0x40, 0x40);
                        HUD_MESSAGE(D_8009AE0C, 0xB4);
                        func_80041564Hud(car, 0x41);
                    }
                    if (car->unk2B8 <= 0xCE3FF) {
                        GraphicsSetColor(
                            0xFF,
                            (((car->unk2B8 - 0xA0000) << 7) / 189440) + 0x40,
                            0x40);
                        HUD_MESSAGE(D_8009ADF8, 0xC3);
                        func_80041564Hud(car, 0x48);
                    }
                    if (ABS(MathGetAngleDelta(
                            car->unk114,
                            ((HudNode *)D_800BE980[0])[car->unk1E0].unk10)) >
                        0x120) {
                        GraphicsSetColor(0xFF, 0x40, 0x40);
                        HUD_MESSAGE(D_8009AE00, 0xD2);
                        func_80041564Hud(car, 0x25);
                    }
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/scene", func_8004A0C4);

#ifdef NON_MATCHING
/* Retry 2026-10-11: fix the 14-byte texture stride, remove the counter
 * pins, and keep the final page table in one call-preserved pointer.
 * Current active-TU text is 0xaf0 bytes; retail is 0xad0. The glyph loop
 * still hoists its string slot, and the remaining loops differ in register
 * allocation and instruction order. Keep the assembly fallback. */
typedef struct {
    u16 tpx;
    u16 tpy;
    u16 clutX;
    u16 clutY;
    u16 u;
    u16 v;
    u16 tpage;
} HudTexture;

extern u8 D_800A3680[1];
extern u8 D_800A3490;
extern u8 D_800A2FD0[3];
extern s32 D_800A2EA4[];
extern u8 D_800A3484;
extern u8 D_800A3485;
extern s8 D_800A3488;
extern s8 *D_8009AE2C[];

extern u8 D_8009AE14[];
extern u8 D_80098BD0[];
extern s8 *D_800A78C4[];
extern s8 *D_800A78CC[];
extern u8 D_800A78D4[];
extern u16 D_800A78E2[];
extern u16 D_800A78EA[];
extern POLY_FT4 D_800A789C[];
extern u8 D_800A78A8[];
extern u8 D_800A78A9[];
extern u8 D_800A78B0[];
extern u8 D_800A78B1[];
extern u8 D_800A78B8[];
extern u8 D_800A78B9[];
extern u8 D_800A78C0[];
extern u8 D_800A78C1[];
extern u16 D_800A78B2[];
extern HudTexture D_80090FEA[];
extern u16 D_80090FEC[];
extern u16 D_80090FEE[];
extern u16 D_80090FF0[];
extern u16 D_80090FF2[];
extern u16 D_80090FF4[];
extern u16 D_80090FF6[];
extern u8 D_800A757C[];
extern u16 D_800A7592[];
extern TILE D_800A7924[][3];
extern u8 D_800A7932[];
extern u8 D_800A7944[];
extern TILE D_800A7984[];
extern u8 D_800A798B[];
extern u16 D_800A798C[];
extern u16 D_800A798E[];
extern u16 D_800A7990[];
extern u16 D_800A7992[];
extern u8 D_800A7564[];
extern u8 D_800B0B7C[];
extern u16 D_800B0B92[];
extern u16 D_80099298[];
extern void SetPolyFT4(POLY_FT4 *);
extern void func_8004AFE0(s8, u16 *, u16 *);
asm(".globl D_80090FF2a\nD_80090FF2a = D_80090FF2");
asm(".globl D_80090FF2b\nD_80090FF2b = D_80090FF2");
asm(".globl D_80090FF2c\nD_80090FF2c = D_80090FF2");
asm(".globl D_80090FF4a\nD_80090FF4a = D_80090FF4");
asm(".globl D_80090FF4b\nD_80090FF4b = D_80090FF4");
asm(".globl D_80090FF4c\nD_80090FF4c = D_80090FF4");
asm(".globl D_800A757Ca\nD_800A757Ca = D_800A757C");
extern u16 D_80090FF2a[];
extern u16 D_80090FF2b[];
extern u16 D_80090FF2c[];
extern u16 D_80090FF4a[];
extern u16 D_80090FF4b[];
extern u16 D_80090FF4c[];
extern u8 D_800A757Ca[];

void func_8004A510(void) {
    HudTexture *tex;
    u8 *prim;
    u8 *prim2;
    u8 *p0;
    u8 *p1;
    u8 *p2;
    u8 *p3;
    u8 *p4;
    u8 *p5;
    u8 *f4base;
    s16 *pts;
    u8 *heap;
    u8 *glyph;
    s8 entry;
    s8 col;
    s8 line;
    s8 j;
    s8 row;
    u16 *page;
    s32 line24;

    D_800A3680[0] = 0;
    D_800A3490 = 0;
    D_800A2FD0[0] = -(D_800A2EA4[0] != 0) & 0x92;
    for (entry = 0; entry < D_800A3424; entry++) {
        D_800A3485 = 0;
        for (col = 0; col < 6; col++) {
            D_800A3485 += strlen((char *)((s8 **)D_8009AE14)[col]);
        }
        D_800A3484 = D_800A3485 + strlen((char *)D_8009AE2C[0]);
        for (col = 0; col < 3; col += 2) {
            line = 0;
            heap = (u8 *)HeapAlloc(D_800A3484 * 0x28);
            D_800A78C4[(s8)(entry + col)] = (s8 *)heap;
            for (; line < 7; line++) {
                j = 0;
                line24 = line << 24;
                if (((s8 **)D_8009AE14)[line24 >> 24][0] != 0) {
                    do {
                        glyph =
                            &D_80098BD0[((s8 **)D_8009AE14)[line24 >> 24][j] *
                                        10];
                        SetPolyFT4((POLY_FT4 *)heap);
                        *(s16 *)(heap + 0xE) = GetClut(0x390, 0x3C);
                        *(u8 *)(heap + 4) = 0x80;
                        *(u8 *)(heap + 5) = 0x80;
                        *(u8 *)(heap + 6) = 0xC0;
                        *(s16 *)(heap + 0x16) = GetTPage(
                            0, 0, *(s16 *)&glyph[0], *(s16 *)&glyph[2]);
                        *(u8 *)(heap + 0xC) = glyph[4];
                        *(u8 *)(heap + 0xD) = glyph[5];
                        *(u8 *)(heap + 0x14) = glyph[4] + glyph[6];
                        *(u8 *)(heap + 0x15) = glyph[5];
                        *(u8 *)(heap + 0x1C) = glyph[4];
                        *(u8 *)(heap + 0x1D) = glyph[5] + glyph[8];
                        *(u8 *)(heap + 0x24) = glyph[4] + glyph[6];
                        *(u8 *)(heap + 0x25) = glyph[5] + glyph[8];
                        j++;
                        heap += 0x28;
                    } while (((s8 **)D_8009AE14)[line24 >> 24][j] != 0);
                }
            }
        }
        row = entry;
        func_8004AFE0(row, D_80099298, (u16 *)D_800A78C4[row]);
        prim = (u8 *)D_800A78CC;
        func_8004AFE0(row, D_80099298, *(u16 **)(prim + row * 4));
        D_800A3488 = strlen((char *)((s8 **)D_8009AE14)[0]);
        prim = (u8 *)D_800A78D4 + row * 0x28;
        SetPolyFT4((POLY_FT4 *)prim);
        SetSemiTrans(prim, 1);
        *(u8 *)(prim + 7) |= 1;
        *(u8 *)(prim + 0xC) = D_80090FF2[0];
        *(u8 *)(prim + 0xD) = D_80090FF4[0];
        *(u8 *)(prim + 0x14) = D_80090FF2a[0] + 0x3C;
        *(u8 *)(prim + 0x15) = D_80090FF4a[0];
        *(u8 *)(prim + 0x1C) = D_80090FF2b[0];
        *(u8 *)(prim + 0x1D) = D_80090FF4b[0] + 0x3C;
        *(u8 *)(prim + 0x24) = D_80090FF2c[0] + 0x3C;
        *(u8 *)(prim + 0x25) = D_80090FF4c[0] + 0x3C;
        *(s16 *)(prim + 8) = 0xF5;
        *(s16 *)(prim + 0xA) = (s8)D_800A2FD0[row] + 0xA0;
        *(s16 *)(prim + 0x10) = 0x131;
        *(s16 *)(prim + 0x12) = (s8)D_800A2FD0[row] + 0xA0;
        *(s16 *)(prim + 0x18) = 0xF5;
        *(s16 *)(prim + 0x1A) = (s8)D_800A2FD0[row] + 0xDC;
        *(s16 *)(prim + 0x20) = 0x131;
        *(s16 *)(prim + 0x22) = (s8)D_800A2FD0[row] + 0xDC;
        *(u16 *)((u8 *)D_800A78E2 + row * 0x28) =
            GetClut(D_80090FEE[0], D_80090FF0[0]);
        tex = D_80090FEA;
        *(u16 *)((u8 *)D_800A78EA + row * 0x28) =
            GetTPage(D_80090FF6[0], 0, tex->tpx, D_80090FEC[0]);
        tex -= 14;
        for (col = 0; col < 10; col++) {
            SetPolyFT4(
                (POLY_FT4 *)((u8 *)D_800A757C + row * 0x190 + col * 0x28));
            SetShadeTex((u8 *)D_800A757C + row * 0x190 + col * 0x28, 0);
            prim2 = (u8 *)D_800A757Ca + row * 0x190 + col * 0x28;
            *(u8 *)(prim2 + 4) = 0x40;
            *(u8 *)(prim2 + 5) = 0x40;
            *(u8 *)(prim2 + 6) = 0x40;
            *(u8 *)(prim2 + 0xC) = tex->u + 0x60;
            *(u8 *)(prim2 + 0xD) = tex->v;
            *(u8 *)(prim2 + 0x14) = tex->u + 0x6F;
            *(u8 *)(prim2 + 0x15) = tex->v;
            *(u8 *)(prim2 + 0x1C) = tex->u + 0x60;
            *(u8 *)(prim2 + 0x1D) = tex->v + 0xF;
            *(u8 *)(prim2 + 0x24) = tex->u + 0x6F;
            *(u8 *)(prim2 + 0x25) = tex->v + 0xF;
            *(u16 *)(row * 0x190 + col * 0x28 + (u8 *)D_800A7592) =
                GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
            *(s16 *)(prim2 + 8) =
                (MathMultiplyFixed16(0x370000,
                                     *(s32 *)((u8 *)D_800A3A2CAbsolute[0] +
                                              col * 0x68 + 0x828)) >>
                 0x10) +
                0x12C;
            *(s16 *)(prim2 + 0xA) =
                (MathMultiplyFixed16(0x370000,
                                     *(s32 *)((u8 *)D_800A3A34Absolute[0] +
                                              col * 0x68 + 0x828)) >>
                 0x10) +
                ((s8)D_800A2FD0[row] + 0xD7);
            *(s16 *)(prim2 + 0x10) =
                (MathMultiplyFixed16(0x370000,
                                     *(s32 *)((u8 *)D_800A3A2CAbsolute[0] +
                                              col * 0x68 + 0x828)) >>
                 0x10) +
                0x130;
            *(s16 *)(prim2 + 0x12) =
                (MathMultiplyFixed16(0x370000,
                                     *(s32 *)((u8 *)D_800A3A34Absolute[0] +
                                              col * 0x68 + 0x828)) >>
                 0x10) +
                ((s8)D_800A2FD0[row] + 0xD7);
            *(s16 *)(prim2 + 0x18) =
                (MathMultiplyFixed16(0x370000,
                                     *(s32 *)((u8 *)D_800A3A2CAbsolute[0] +
                                              col * 0x68 + 0x828)) >>
                 0x10) +
                0x12C;
            *(s16 *)(prim2 + 0x1A) =
                (MathMultiplyFixed16(0x370000,
                                     *(s32 *)((u8 *)D_800A3A34Absolute[0] +
                                              col * 0x68 + 0x828)) >>
                 0x10) +
                (s8)D_800A2FD0[row] + 0xDB;
            *(s16 *)(prim2 + 0x20) =
                (MathMultiplyFixed16(0x370000,
                                     *(s32 *)((u8 *)D_800A3A2CAbsolute[0] +
                                              col * 0x68 + 0x828)) >>
                 0x10) +
                0x130;
            *(s16 *)(prim2 + 0x22) =
                (MathMultiplyFixed16(0x370000,
                                     *(s32 *)((u8 *)D_800A3A34Absolute[0] +
                                              col * 0x68 + 0x828)) >>
                 0x10) +
                (s8)D_800A2FD0[row] + 0xDB;
        }
        for (col = 0; col < 3; col++) {
            SetTile((TILE *)((u8 *)D_800A7924 + col * 0x10 + entry * 0x30));
            SetSemiTrans((u8 *)D_800A7924 + col * 0x10 + entry * 0x30, 1);
            *(s16 *)(entry * 0x30 + col * 0x10 + (u8 *)D_800A7924 + 8) = 0xD;
            *(s16 *)(entry * 0x30 + col * 0x10 + (u8 *)D_800A7924 + 0xA) =
                (s8)D_800A2FD0[entry] + 0xD3;
            *(u16 *)(entry * 0x30 + col * 0x10 + (u8 *)D_800A7932) = 6;
        }
        prim = (u8 *)D_800A7924;
        *(u8 *)(prim + entry * 0x30 + 4) = 0;
        *(u8 *)(prim + entry * 0x30 + 5) = 0xFF;
        *(u8 *)(prim + entry * 0x30 + 6) = 0;
        *(u8 *)(prim + 0x10 + entry * 0x30 + 4) = 0xFF;
        *(u8 *)(prim + 0x10 + entry * 0x30 + 5) = 0;
        *(u8 *)(prim + 0x10 + entry * 0x30 + 6) = 0;
        prim2 = (u8 *)D_800A7944;
        *(u8 *)(prim2 + entry * 0x30 + 4) = 0;
        *(u8 *)(prim2 + entry * 0x30 + 5) = 0;
        *(u8 *)(prim2 + entry * 0x30 + 6) = 0;
        *(s16 *)(prim2 + entry * 0x30 + 8) = 0xC;
        *(s16 *)(prim2 + entry * 0x30 + 0xA) = (s8)D_800A2FD0[entry] + 0xD2;
        *(s16 *)(prim2 + entry * 0x30 + 0xC) = 0x2A;
        *(s16 *)(prim2 + entry * 0x30 + 0xE) = 8;
    }
    SetPolyFT4((POLY_FT4 *)D_800A789C);
    SetSemiTrans((u8 *)D_800A789C, 1);
    SetShadeTex((u8 *)D_800A789C, 0);
    D_800A78B2[0] = GetTPage(tex->tpage, 3, tex->tpx, tex->tpy);
    D_800A78A8[0] = tex->u + 0x60;
    D_800A78A9[0] = tex->v + 0xF;
    D_800A78B0[0] = tex->u + 0x6F;
    D_800A78B1[0] = tex->v + 0xF;
    D_800A78B8[0] = tex->u + 0x60;
    D_800A78B9[0] = tex->v;
    D_800A78C0[0] = tex->u + 0x6F;
    D_800A78C1[0] = tex->v;
    SetTile(D_800A7984);
    D_800A7990[0] = 0x140;
    D_800A798C[0] = 0;
    D_800A798E[0] = 0;
    D_800A7992[0] = 0xF0;
    D_800A798B[0] |= 2;
    page = (u16 *)D_80090F32;
    asm("" : "=r"(page) : "0"(page));
    SetPolyF4(D_800A7564);
    for (entry = 0; entry < 2; entry++) {
        for (col = 0; col < 0x18; col++) {
            SetPolyFT4(
                (POLY_FT4 *)((u8 *)D_800B0B7C + entry * 0x3C0 + col * 0x28));
            SetShadeTex((u8 *)D_800B0B7C + entry * 0x3C0 + col * 0x28, 0);
            *(u16 *)(col * 0x28 + entry * 0x3C0 + (u8 *)D_800B0B92) =
                GetTPage(page[0], 0, page[-6], page[-5]);
            *(u8 *)(col * 0x28 + entry * 0x3C0 + (u8 *)D_800B0B7C + 4) =
                D_800991E8[col * 3];
            *(u8 *)(col * 0x28 + entry * 0x3C0 + (u8 *)D_800B0B7C + 5) =
                D_800991E9[col * 3];
            *(u8 *)(col * 0x28 + entry * 0x3C0 + (u8 *)D_800B0B7C + 6) =
                D_800991EA[col * 3];
        }
    }
}
extern u8 D_800A2FD0[];
extern u8 D_80098BD0[];

#else
INCLUDE_ASM("asm/nonmatchings/scene", func_8004A510);
#endif

/* Parked 2026-10-14: corrected the inner table index to a byte offset.
 * Size exact; honest score 90. Two outer address adds and the inner add
 * commute differently; x loads before the lbu address setup. */
#ifdef NON_MATCHING
void func_8004AFE0(s8 arg0, u16 *arg1, u16 *arg2) {
    extern u8 D_800A2FD0[];
    extern u8 D_8009AE14[];
    extern u8 D_80098BD0[];
    s16 *out;
    u16 *xy0;
    u16 *cursor;
    s8 i;
    s8 j;
    s32 x;
    u8 *table;
    s32 w;
    s32 t;
    s32 v0;
    s32 v1;
    s32 sum;
    s32 i24;
    s32 padByte;
    s8 **a914;
    s16 *glyph;
    s32 arg0e;
    do {
        asm volatile("" : "=r"(cursor) : "0"(arg2));
        table = D_8009AE14;
    } while (0);
    i = 0;
    arg0e = (s8)arg0;
    a914 = (s8 **)table;
    do {
        j = 0;
        i24 = i << 24;
        asm("" : "=r"(padByte) : "0"(D_800A2FD0[arg0e]));
        xy0 = (u16 *)((i24 >> 22) + ((char *)arg1));
        x = xy0[0];
        w = xy0[1] + ((padByte << 24) >> 24);
        if ((*((s8 **)(((char *)a914) + (i24 >> 22))))[0] != 0) {
            out = (s16 *)(((u8 *)cursor) + 0x22);
        inner:
            do {
                t = (*((s8 **)(((u8 *)a914) + (i24 >> 22))))[j];
                glyph = (s16 *)(&D_80098BD0[t * 10]);
                v0 = glyph[3];
                out[-13] = x;
                out[-12] = w;
                out[-8] = w;
                out[-5] = x;
                sum = x + ((v0 * 3) >> 2);
                out[-9] = sum;
                v1 = glyph[4];
                out[-1] = sum;
                out[-4] = w + ((v1 * 3) >> 2);
                out[0] = w + ((glyph[4] * 3) >> 2);
            } while (0);

            j++;
            cursor += 0x14;
            x = sum;
            out += 0x14;
            if ((*((s8 **)(((u8 *)a914) + (i24 >> 22))))[j] != 0) {
                goto inner;
            }
        }
        i++;
    } while (i < 7);
}
#else
INCLUDE_ASM("asm/nonmatchings/scene", func_8004AFE0);
#endif

extern s32 D_800A2E50[];
extern s16 D_800A38E4[];

void func_8004B128(u8 *arg0) {
    s8 value;

    if (arg0[0x3FC] != 0) {
        value = (D_800A2E50[0] - D_800A38E4[0]) * 10 / D_800A2E50[0] + 2;
    } else {
        value = 0;
    }
    if (value >= 0xB) {
        value = 0xA;
    }
    arg0[0x3FD] = value;
    *(s16 *)(arg0 + 0x402) = *(u16 *)(arg0 + 0x108);
}

/* These calls keep the preceding result in the delay slot. */
extern void HudMultiplyVoid(s32, s32) asm("MathMultiplyFixed16");
extern u32 gHudPrimitiveCursor asm("gPrimitiveCursorAbsolute");
extern u8 D_800A8184[], D_800A81B4[], D_800A8214[], D_800A82B4[];
extern u8 D_800A80F4[], D_800A8354[], D_800A8534[], D_800A7995[];
extern u16 D_8009934C[], D_8009934E[];
extern s16 D_8009935C[], D_8009936C[];
extern s16 D_800A3008;
extern SVECTOR D_800A3004[];
extern MATRIX D_800A7FC4[];
extern u16 D_800A348C, D_800A3494;
extern u8 D_800A2FD4[4], D_800A2FD8[], D_800A2FDC[];
extern u8 D_800A2ED9[];
extern s16 D_800A853C[], D_800A8544[], D_800A854C[], D_800A854E[];
extern s16 D_800A8554[], D_800A8556[];

void HudDrawDashboard(void) {
    /* Preserve the temporary packet layout used by the draw loops. */
    s16 points[16];
    s16 angles[4];
    s16 streakAngles[4];
    s16 *cornerRows[2];
    u32 intensityBytes[2];
    u8 framePad[8];
    register s32 product asm("s0");
    s32 productY;
    register s32 next asm("v0");
    s32 cosine;
    s32 sine;
    s32 offset;
    s32 count;
    register s32 vertex asm("s4");
    register s32 i asm("s7");
    register s16 *point asm("s3");
    s16 *corner;
    POLY_F4 *needle;
    register u32 cachedAngle asm("t3");
    register s32 argA asm("a0");
    register s32 argB asm("a1");
    s32 callResult;
    s32 nextVertex;
    register s32 screenY asm("v1");
    register s16 *baseCorner asm("t2");

    if (D_800A2EA4[0] == 0) {
        i = 0;
    copyHud1:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(D_800A8184 + (s16)i * 0x18);
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(D_800A39C8[0] + 0x10), entry);
            next = i + 1;
            i = next;
            asm("" : "=r"(next) : "0"(next));
            if ((s16)next < 2)
                goto copyHud1;
        }
        i = 0;
        PushMatrix();
        func_800474A0();
        do {
            baseCorner = D_8009935C;

            cornerRows[0] = baseCorner;
            switch ((s16)i) {
            case 0: {
                u8 *car;
                s32 rpm;
                s32 numerator;
                register s32 quotient asm("$3");
                register s32 trueFactor asm("$4");
                register s32 falseFactor asm("$3");
                register s32 trueHigh asm("$11");
                register s32 falseHigh asm("$12");
                s64 wideProduct;

                /* Scale the tachometer angle by 585/13250 or 658/13250. */
                car = D_800A3554[0];
                rpm = *(s16 *)(car + 0x402);
                if (*(u8 *)(car + 0xF6) != 0 ||
                    *(s16 *)(car + 0x10C) == *(s16 *)(car + 0x110)) {
                    trueFactor = 0x9E468F35;
                    numerator = rpm * 585;
                    asm("mult %2,%3\n\tmfhi %0"
                        : "=r"(trueHigh), "=x"(wideProduct)
                        : "r"(numerator), "r"(trueFactor)
                        : "accum");
                    quotient = trueHigh + numerator;
                } else {
                    falseFactor = 0x9E468F35;
                    numerator = rpm * 658;
                    asm("mult %2,%3\n\tmfhi %0"
                        : "=r"(falseHigh), "=x"(wideProduct)
                        : "r"(numerator), "r"(falseFactor)
                        : "accum");
                    quotient = falseHigh + numerator;
                }
                quotient >>= 13;
                numerator >>= 31;
                quotient -= numerator;
                quotient += 256;

                angles[0] = quotient;
                asm("" : : "m"(angles[0]) : "$10", "memory");
            }
                baseCorner = D_8009936C;

                cornerRows[0] = baseCorner;
                break;
            case 1:
                if (D_800A2ED4[0] == 0) {
                    if (RandomScaledGet(2)) {
                        productY = -RandomScaledGet(
                            *(s32 *)(D_800A3554[0] + 0x90) >> 20);
                    } else {
                        productY = RandomScaledGet(
                            *(s32 *)(D_800A3554[0] + 0x90) >> 20);
                    }
                    productY += 0x300;
                    D_800A3494 = productY;
                    angles[0] = productY;
                } else {
                    cachedAngle = D_800A3494;

                    angles[0] = cachedAngle;
                }
                break;
            case 2: {
                s32 speed;
                s32 scaledSpeed;
                register s32 factor asm("a0");
                register s32 high asm("t4");
                register s32 angleQuot asm("v1");
                s64 wideProduct;

                /* Scale speed by 768/16000 for the speedometer angle. */
                speed = *(s32 *)(D_800A3554[0] + 0x28C);
                factor = 0x10624DD3;
                scaledSpeed = speed * 768;
                asm("mult %1,%2"
                    : "=x"(wideProduct)
                    : "r"(scaledSpeed), "r"(factor)
                    : "accum");
                scaledSpeed >>= 31;
                asm("mfhi %0"
                    : "=r"(high)
                    : "x"(wideProduct), "r"(scaledSpeed));
                angleQuot = high >> 10;
                angleQuot -= scaledSpeed;
                angleQuot += 0x180;
                angleQuot &= 0x3FF;
                angles[0] = angleQuot;
                break;
            }
            case 3:
                angles[0] = ((s32)(D_800A3554[0][0x3FD] << 24) >> 21) + 0x2D8;
                break;
            }
            vertex = 0;
            {
                register u32 angleWord asm("t2");
                register s32 index asm("v0");
                register s32 *cosineTable asm("v1");
                register s32 *sineTable asm("a0");
                extern s32 *hudCosine asm("D_800A3A2CAbsolute");
                extern s32 *hudSine asm("D_800A3A34Absolute");

                index = i << 16;
                angleWord = *(u16 *)angles;

                offset = index >> 14;
                cosineTable = hudCosine;
                sineTable = hudSine;
                index = (s32)(angleWord << 16) >> 14;
                cosineTable = (s32 *)(index + (u32)cosineTable);
                cosine = *cosineTable;
                sineTable = (s32 *)(index + (u32)sineTable);
                sine = *sineTable;
            }
        rotateCorner:
            {
                register s16 *base asm("t3");

                base = cornerRows[0];

                count = (s32)(vertex << 16) >> 14;
                corner = (s16 *)(count + (u32)base);

                argB = corner[0];
                argA = cosine;
            }
            callResult = MathMultiplyFixed16(argA, argB << 16);
            argB = corner[1];
            argA = sine;
            product = callResult;
            callResult = MathMultiplyFixed16(argA, argB << 16);
            {
                u32 centerX;

                point = points;

                centerX = *(u16 *)(offset + (u32)D_8009934C);
                point = (s16 *)((u8 *)point + count);
                asm("" : "=r"(point) : "0"(point), "r"(centerX), "r"(product));
                product -= callResult;
                product >>= 16;
                centerX += product;
                point[0] = centerX;
                argB = corner[0];
                argA = sine;
            }
            callResult = MathMultiplyFixed16(argA, argB << 16);
            argB = corner[1];
            argA = cosine;
            product = callResult;
            callResult = MathMultiplyFixed16(argA, argB << 16);
            screenY = D_800A2FD4[0];

            nextVertex = vertex + 1;
            vertex = nextVertex;
            asm("" : "=r"(nextVertex) : "0"(nextVertex));
            argB = *(u16 *)(offset + (u32)D_8009934E);

            product += callResult;
            product >>= 16;
            nextVertex = (s16)nextVertex < 4;
            point[1] = (s8)screenY + (argB + product);
            if (nextVertex)
                goto rotateCorner;
            {
                register s32 copyIndex asm("v0");
                s32 copyOffset;
                register u32 needleBase asm("a1");

                copyIndex = (s16)i;
                needleBase = (u32)D_800A81B4;
                copyOffset = copyIndex << 1;

                argA = *(u16 *)points;
                copyOffset += copyIndex;
                copyOffset <<= 3;
                needle = (POLY_F4 *)(copyOffset + needleBase);
            }
            needle->x0 = argA;
            needle->y0 = points[1];
            needle->x1 = points[2];
            needle->y1 = points[3];
            needle->x2 = points[4];
            needle->y2 = points[5];
            needle->x3 = points[6];
            needle->y3 = points[7];
            next = i + 1;
            i = next;
            asm("" : "=r"(next) : "0"(next));
        } while ((s16)next < 4);
        D_800A3008 = D_800A3480 * -15;
        RotMatrix(D_800A3004, D_800A7FC4);
        SetRotMatrix(D_800A7FC4);
        SetTransMatrix(D_800A7FC4);
        {
            u8 *dest;
            register u8 *source asm("s0");
            register u8 *out asm("s1");
            u32 *ot;
            s32 count;
            s32 product;
            struct PacketWords {
                s32 w0;
                s32 w1;
                s32 w2;
                s32 w3;
                s32 w4;
            };
            struct PacketWords *from;
            struct PrimitiveWords {
                u32 tag, color, xy0, uv0, xy1, uv1, xy2, uv2, xy3, uv3;
            };
            struct PrimitiveWords *poly;
            register s32 w0 asm("v0");
            s32 w1;
            register s32 w2 asm("a0");
            s32 w3;
            s32 w4;
            register SVECTOR *p0 asm("t4");
            register SVECTOR *p1 asm("t2");
            register SVECTOR *p2 asm("t3");
            /* Project the 36 dashboard quads through the GTE. */
            dest = (u8 *)gHudPrimitiveCursor;
            count = 36;
            source = D_800A7995;
            ot = (u32 *)D_800A39C8[0];
            out = dest + 0x18;
            do {
                p0 = *(SVECTOR **)(source + 0x17);
                p1 = *(SVECTOR **)(source + 0x1B);
                p2 = *(SVECTOR **)(source + 0x1F);
                gte_ldv3(p0, p1, p2);
                asm volatile(
                    ".set\tnoreorder\n\tnop\n\tnop\n\trtpt\n\t.set\treorder");
                asm volatile(
                    ".set\tnoreorder\n\tnop\n\tnop\n\tavsz3\n\t.set\treorder");
                from = (struct PacketWords *)(source + 3);
                poly = (struct PrimitiveWords *)(out - 0x18);
                w2 = from->w2;
                w0 = from->w0;
                w1 = from->w1;
                w3 = from->w3;
                w4 = from->w4;

                poly->uv1 = w2;
                poly->uv0 = w1;
                poly->color = w0;
                poly->uv2 = w3;
                poly->uv3 = w4;
                gte_stsxy3(dest + 8, dest + 0x10, dest + 0x20);
                p0 = *(SVECTOR **)(source + 0x23);
                gte_ldv0(p0);
                asm volatile(
                    ".set\tnoreorder\n\tnop\n\tnop\n\trtps\n\t.set\treorder");
                gte_stsxy(out);
                argB = (s32)dest;
                count--;
                product = *(s8 *)source;
                source += 0x2C;
                out += 0x28;
                dest += 0x28;
                GraphicsAddTaggedPrimitive(ot + product, (u32 *)argB,
                                           0x09000000);
            } while (count > 0);
            gHudPrimitiveCursor = (u32)dest;
        }
        i = 0;
    copyHud2:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(D_800A81B4 + (s16)i * 24);
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(D_800A39C8[0] + 8), entry);
            next = i + 1;
            i = next;
            asm("" : "=r"(next) : "0"(next));
            if ((s16)next < 4)
                goto copyHud2;
        }
        i = 0;
    copyHud3:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(D_800A8214 + (s16)i * 40);
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(D_800A39C8[0] + 16), entry);
            next = i + 1;
            i = next;
            asm("" : "=r"(next) : "0"(next));
            if ((s16)next < 4)
                goto copyHud3;
        }
        i = 0;
    copyHud4:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(D_800A82B4 + (s16)i * 40);
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(D_800A39C8[0] + 16), entry);
            next = i + 1;
            i = next;
            asm("" : "=r"(next) : "0"(next));
            if ((s16)next < 4)
                goto copyHud4;
        }
        {
            register s32 product asm("s0");
            s32 productX;
            s32 rotatedX;
            register s32 returnedValue asm("v0");
            register s32 rowOffset asm("s4");
            u16 *center;

            register u32 intensityValue asm("t3");
            register u32 reloadIntensity asm("t2");
            register u16 rawAngle asm("t2");
            register u32 shifted asm("a0");
            s32 signedAngle;
            i = 0;
            streakAngles[0] = (D_800A348C + 0x120) & 0x3FF;
            do {
                rawAngle = *(u16 *)streakAngles;
                asm("" : "=r"(rawAngle) : "0"(rawAngle));
                shifted = (u32)rawAngle << 16;
                signedAngle = (s32)shifted >> 16;
                if (signedAngle < 0x200) {
                    if (signedAngle - 0x100 >= 0) {
                        offset = (u32)(0x200 - signedAngle) >> 2;
                    } else {
                        offset = shifted >> 18;
                    }
                    intensityValue = offset & 0xFF;

                    intensityBytes[0] = intensityValue;
                    if (intensityValue >= 8) {
                        {
                            s32 index;
                            register s32 width asm("a2");
                            register u32 angleWord asm("t4");
                            u32 centers;
                            register u32 angleIndex asm("a3");
                            register u32 centerValue asm("v1");
                            extern s32 *hudCosine asm("D_800A3A2CAbsolute");
                            extern s32 *hudSine asm("D_800A3A34Absolute");

                            index = (s16)i;
                            width = D_800A2FD8[index];
                            asm("" : "=r"(width) : "0"(width));
                            angleWord = *(u16 *)streakAngles;
                            asm("" : "=r"(angleWord) : "0"(angleWord));
                            argB = 0x200;
                            centers = (u32)D_800A2FDC;

                            center = (u16 *)(index * 2 + centers);
                            centerValue = *center;
                            callResult = index * 5;

                            rowOffset = callResult << 3;
                            product = intensityValue >> 1;

                            product <<= 16;
                            width = (s8)width;
                            angleIndex = angleWord;
                            argB -= angleIndex;
                            argB >>= 7;
                            centerValue -= width;
                            centerValue = argB + centerValue;
                            *(s16 *)(rowOffset + (u32)D_800A853C) = centerValue;
                            asm volatile("" : : : "memory");
                            callResult = D_800A2FD8[index];
                            asm("" : "=r"(callResult) : "0"(callResult));
                            centerValue = *center;
                            argA = (s32)hudCosine;
                            callResult = (s8)callResult;
                            centerValue += callResult;
                            callResult = (s32)hudSine;
                            angleIndex <<= 2;
                            argB += centerValue;
                            argA = angleIndex + argA;
                            *(s16 *)(rowOffset + (u32)D_800A8544) = argB;
                            cosine = *(s32 *)argA;
                            argB = 0x640000;
                            angleIndex += callResult;

                            sine = *(s32 *)angleIndex;
                        }
                        callResult = MathMultiplyFixed16(cosine, argB);
                        argB = product;
                        productX = callResult;
                        callResult = MathMultiplyFixed16(sine, argB);
                        argA = sine;
                        argB = 0x640000;

                        rotatedX = callResult;
                        HudMultiplyVoid(argA, argB);
                        callResult = returnedValue;
                        argA = cosine;
                        argB = product;
                        product = callResult;
                        HudMultiplyVoid(argA, argB);
                        callResult = returnedValue;
                        argA = *center;
                        screenY = (productX - rotatedX) >> 16;
                        argA += screenY;
                        *(s16 *)(rowOffset + (u32)D_800A854C) = argA;

                        screenY = D_800A2FD4[0];
                        asm("" : "=r"(screenY) : "0"(screenY));
                        argA = (product + callResult) >> 16;
                        screenY = (s8)screenY;
                        screenY += 0x9E;
                        argA += screenY;
                        *(s16 *)(rowOffset + (u32)D_800A854E) = argA;

                        screenY = *center;
                        productX += rotatedX;
                        productX >>= 16;
                        screenY += productX;
                        *(s16 *)(rowOffset + (u32)D_800A8554) = screenY;
                        asm volatile("" : : : "memory");
                        screenY = D_800A2FD4[0];
                        asm("" : "=r"(screenY) : "0"(screenY));
                        product -= callResult;
                        product >>= 16;
                        screenY = (s8)screenY;
                        screenY += 0x9E;
                        product += screenY;
                        *(s16 *)(rowOffset + (u32)D_800A8556) = product;

                        reloadIntensity = intensityBytes[0];
                        next = reloadIntensity < 33;

                        if (!next)
                            offset = 32;
                        {
                            u32 raw;
                            POLY_FT4 *entry;
                            register POLY_FT4 *prim asm("v0");
                            prim = (POLY_FT4 *)(rowOffset + (u32)D_800A8534);

                            prim->r0 = offset;
                            prim->g0 = offset;
                            prim->b0 = offset;
                            raw = gHudPrimitiveCursor;
                            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
                            entry = (POLY_FT4 *)raw;
                            *entry = *prim;
                            AddPrim((void *)(D_800A39C8[0] + 0x10), entry);
                        }
                    }
                }
                {
                    register u32 angleRaw asm("t3");
                    register u32 angleNext asm("v0");

                    angleRaw = *(u16 *)streakAngles;

                    angleNext = (angleRaw + 0x3E0) & 0x3FF;
                    streakAngles[0] = angleNext;
                }
                next = i + 1;
                i = next;
                asm("" : "=r"(next) : "0"(next));
            } while ((s16)next < 3);
        }
        PopMatrix();
    }
    i = 0;
copyHud5:
    {
        register u32 raw asm("a1");
        register u32 mode asm("v0");
        s32 row;
        register s32 copyOffset asm("v1");
        register s32 modeOffset asm("v1");
        s32 rowOffset;
        register POLY_FT4 *entry asm("t0");
        POLY_FT4 *copyDest;
        u32 sourceBase;
        POLY_FT4 *prim;
        mode = D_800A2ED9[0];
        row = (s16)i;
        asm volatile("" : "=r"(row) : "0"(row), "r"(mode) : "memory");
        raw = gHudPrimitiveCursor;
        asm("" : "=r"(raw) : "0"(raw));
        modeOffset = mode * 240;

        rowOffset = row * 40;

        copyOffset = modeOffset + rowOffset;
        entry = (POLY_FT4 *)raw;

        copyDest = entry;

        sourceBase = (u32)D_800A8354;
        prim = (POLY_FT4 *)(copyOffset + sourceBase);
        gHudPrimitiveCursor = (u32)entry + sizeof(POLY_FT4);
        *copyDest = *prim;
        AddPrim((void *)(D_800A39C8[0] + 0x10), entry);
        next = i + 1;
        i = next;
        asm("" : "=r"(next) : "0"(next));
        if ((s16)next < 6)
            goto copyHud5;
    }
    i = 0;
copyHud6:
    {
        register u32 raw asm("a1");
        register u32 mode asm("v0");
        register s32 row asm("v1");
        s32 copyOffset;
        s32 modeOffset;
        register POLY_FT4 *entry asm("t0");
        POLY_FT4 *copyDest;
        u32 sourceBase;
        POLY_FT4 *prim;
        mode = D_800A2ED9[0];
        row = (s16)i;
        asm volatile("" : "=r"(row) : "0"(row), "r"(mode) : "memory");
        raw = gHudPrimitiveCursor;
        asm("" : "=r"(raw) : "0"(raw));
        modeOffset = mode * 9;
        asm("" : "=r"(modeOffset) : "0"(modeOffset));
        copyOffset = row * 3;

        copyOffset += modeOffset;
        copyOffset <<= 3;
        entry = (POLY_FT4 *)raw;

        copyDest = entry;

        sourceBase = (u32)D_800A80F4;
        prim = (POLY_FT4 *)(copyOffset + sourceBase);
        gHudPrimitiveCursor = (u32)entry + sizeof(POLY_FT4);
        *copyDest = *prim;
        AddPrim((void *)(D_800A39C8[0] + 0x10), entry);
        next = i + 1;
        i = next;
        asm("" : "=r"(next) : "0"(next));
        if ((s16)next < 3)
            goto copyHud6;
    }
}

void __maspsx_include_asm_hack_D_8008D4CC(void) {
    __asm__(".section .rodata # maspsx-keep \n"
            "dlabel D_8008D4CC # maspsx-keep\n"
            "    .word 0x003200DC # maspsx-keep\n"
            "    .word 0x003200EB # maspsx-keep\n"
            "    .word 0x0020013F # maspsx-keep\n"
            "    .word 0x003B013F # maspsx-keep\n"
            "    .word 0x0080013F # maspsx-keep\n"
            "    .word 0x0087013F # maspsx-keep\n"
            "dlabel D_8008D4E4 # maspsx-keep\n"
            "    .word 0x00050000 # maspsx-keep\n"
            "    .word 0x00050037 # maspsx-keep\n"
            "    .word 0xFFFB0000 # maspsx-keep\n"
            "    .word 0xFFFB0037 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

typedef struct {
    u16 tpx;
    u16 tpy;
    u16 clutX;
    u16 clutY;
    u16 u;
    u16 v;
    u16 tpage;
} SceneTexInfo;

typedef struct {
    s16 a[3];
} SceneRotTable;
typedef struct {
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} SceneSeg;
typedef struct {
    SceneSeg s[3];
} SceneQuadTable;
typedef struct {
    s16 x;
    s16 y;
} ScenePt;
typedef struct {
    u16 x;
    u16 y;
} ScenePt16;
typedef struct {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} SceneVert;
typedef struct {
    ScenePt p[4];
} ScenePairTable;
typedef struct {
    s16 a[4];
} SceneTailTable;

extern SceneTexInfo D_80090FCE[];
extern SceneTexInfo D_80091014;
extern SceneRotTable D_800A300C[];
extern SceneQuadTable D_8008D4CC;
extern ScenePairTable D_8008D4E4;
extern SceneTailTable D_800A3014[];
extern u8 D_800A2FD4[4];
extern u8 D_800A2FD8[];
extern u8 D_800A2FDC[];
extern u16 D_800A3494;
extern u16 D_80090F28[];
extern u8 D_80090F2E[];
extern u8 D_80090F30[];
extern u16 D_80091016[];
extern u16 D_80091018[];
extern u16 D_8009101A[];
extern u16 D_8009101C[];
extern u16 D_8009101E[];
extern u16 D_80091020[];
extern u8 D_800A7994[];
extern u8 D_800A7995[];
extern u8 D_800A799C[];
extern u8 D_800A799D[];
extern u8 D_800A799E[];
extern u8 D_800A79A0[];
extern u8 D_800A79A1[];
extern u8 D_800A79A2[];
extern u8 D_800A79A4[];
extern u8 D_800A79A5[];
extern u8 D_800A79A8[];
extern u8 D_800A79A9[];
extern u8 D_800A79AC[];
extern u8 D_800A79B0[];
extern u8 D_800A79B4[];
extern u8 D_800A79B8[];
extern u8 D_800A7F14[];
extern u8 D_800A7F18[];
extern u8 D_800A7F19[];
extern u8 D_800A7F1A[];
extern u8 D_800A7F1C[];
extern u8 D_800A7F1D[];
extern u8 D_800A7F20[];
extern u8 D_800A7F21[];
extern u16 D_800A7F22[];
extern u8 D_800A7F24[];
extern u8 D_800A7F25[];
extern u8 D_800A7F28[];
extern u8 D_800A7F29[];
extern s32 D_800A7FD8[];
extern s32 D_800A7FDC[];
extern s32 D_800A7FE0[];
extern ScenePt16 D_800A7FE4[];
extern u8 D_800A80F4[];
extern u8 D_800A8184[];
extern u8 D_800A8188[];
extern u8 D_800A8189[];
extern u8 D_800A818A[];
extern s16 D_800A818C[];
extern s16 D_800A818E[];
extern s16 D_800A8190[];
extern s16 D_800A8192[];
extern s16 D_800A8194[];
extern s16 D_800A8196[];
extern s16 D_800A8198[];
extern s16 D_800A819A[];
extern u8 D_800A81A0[];
extern u8 D_800A81A1[];
extern u8 D_800A81A2[];
extern s16 D_800A81A4[];
extern s16 D_800A81A6[];
extern s16 D_800A81A8[];
extern s16 D_800A81AA[];
extern s16 D_800A81AC[];
extern s16 D_800A81AE[];
extern s16 D_800A81B0[];
extern s16 D_800A81B2[];
extern u8 D_800A81B4[];
extern u8 D_800A8214[];
extern s16 D_800A821C[];
extern s16 D_800A821E[];
extern u8 D_800A8220[];
extern u8 D_800A8221[];
extern u8 D_800A8222[];
extern s16 D_800A8224[];
extern s16 D_800A8226[];
extern u8 D_800A8228[];
extern u8 D_800A8229[];
extern u8 D_800A822A[];
extern s16 D_800A822C[];
extern s16 D_800A822E[];
extern u8 D_800A8230[];
extern u8 D_800A8231[];
extern s16 D_800A8234[];
extern s16 D_800A8236[];
extern u8 D_800A8238[];
extern u8 D_800A8239[];
extern u8 D_800A82B4[];
extern s16 D_800A82BC[];
extern s16 D_800A82BE[];
extern u8 D_800A82C0[];
extern u8 D_800A82C1[];
extern u16 D_800A82C2[];
extern s16 D_800A82C4[];
extern s16 D_800A82C6[];
extern u8 D_800A82C8[];
extern u8 D_800A82C9[];
extern u16 D_800A82CA[];
extern s16 D_800A82CC[];
extern s16 D_800A82CE[];
extern u8 D_800A82D0[];
extern u8 D_800A82D1[];
extern s16 D_800A82D4[];
extern s16 D_800A82D6[];
extern u8 D_800A82D8[];
extern u8 D_800A82D9[];
extern s16 D_800A8334[];
extern s16 D_800A8336[];
extern s16 D_800A833C[];
extern s16 D_800A833E[];
extern s16 D_800A8344[];
extern s16 D_800A8346[];
extern s16 D_800A834C[];
extern s16 D_800A834E[];
extern u8 D_800A8354[];
extern u8 D_800A8362[];
extern u8 D_800A836A[];
extern u8 D_800A83DA[];
extern u8 D_800A83E2[];
extern u8 D_800A8402[];
extern u8 D_800A840A[];
extern u8 D_800A842A[];
extern u8 D_800A8432[];
extern u8 D_800A8534[];
extern u8 D_800A853E[];
extern u8 D_800A854A[];
extern SceneVert D_800A85AC[][4];
extern s16 D_800A89AC[];
extern s16 D_800A89AE[];
extern s16 D_800A89B4[];
extern s16 D_800A89B6[];
extern s16 D_800A89BC[];
extern s16 D_800A89BE[];
extern s16 D_800A89C4[];
extern s16 D_800A89C6[];

extern s32 D_800A3A2CSmall[];
extern s32 D_800A3A34Small[];

void HudInitPrims(void) {
    SceneTexInfo *tex;
    s32 idx;
    s32 rowOff;
    SceneRotTable rot;
    SceneQuadTable quads;
    ScenePairTable corners;
    SceneTailTable tail;
    u8 *prim2;
    u8 *prim3;
    u8 *p0;
    u8 *p1;
    u8 *p2;
    u8 *p3;
    u8 *p4;
    u8 *p5;
    u8 *f4base;
    u16 *primC;
    u8 *poly;
    u16 u;
    u16 v;
    u16 u2;
    u16 v2;
    u8 u3;
    u8 v3;
    s8 i;
    s8 j;
    s8 k;
    s32 matA;
    s32 matB;
    s16 yv;
    s32 xl;
    s32 xa;
    s32 xb;

    rot = D_800A300C[0];
    quads = D_8008D4CC;
    corners = D_8008D4E4;
    tail = D_800A3014[0];
    D_800A2FD4[0] = -(D_800A2EA4[0] != 0) & 0xD8;
    for (i = 0; i < D_800A3424; i++) {
        tex = D_80090FCE;
        for (j = 0; j < 6; j++) {
            s32 rowOff;
            s32 tmp;
            u8 *prim;
            s32 idx;
            rowOff = i * 0xF0;
            idx = j * 0x28;
            tmp = idx + (s32)D_800A8354;
            prim = (u8 *)(rowOff + tmp);
            SetPolyFT4((POLY_FT4 *)prim);
            SetShadeTex(prim, 1);
            idx += rowOff;
            *(u16 *)(D_800A8362 + idx) = GetClut(tex->clutX, tex->clutY);
            *(u16 *)(D_800A836A + idx) =
                GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
            prim2 = idx + D_800A8354;
            prim2[0xC] = tex->u;
            prim2[0xD] = tex->v;
            prim2[0x14] = tex->u + 0x50;
            prim2[0x15] = tex->v;
            prim2[0x1C] = tex->u;
            prim2[0x1D] = tex->v + 0x33;
            prim2[0x24] = tex->u + 0x50;
            prim2[0x25] = tex->v + 0x33;
        }
        p0 = i * 0xF0 + D_800A8354;
        *(s16 *)(p0 + 0x8) = 0x11C;
        *(s16 *)(p0 + 0xA) = (s8)D_800A2FD4[i];
        *(s16 *)(p0 + 0x10) = 0x16C;
        *(s16 *)(p0 + 0x12) = (s8)D_800A2FD4[i];
        *(s16 *)(p0 + 0x18) = 0x11C;
        *(s16 *)(p0 + 0x1A) = (s8)D_800A2FD4[i] + 0x33;
        *(s16 *)(p0 + 0x20) = 0x16C;
        *(s16 *)(p0 + 0x22) = (s8)D_800A2FD4[i] + 0x33;
        p1 = i * 0xF0 + (D_800A8354 + 0x28);
        *(s16 *)(p1 + 0x8) = 0xCC;
        *(s16 *)(p1 + 0xA) = (s8)D_800A2FD4[i];
        *(s16 *)(p1 + 0x10) = 0x11C;
        *(s16 *)(p1 + 0x12) = (s8)D_800A2FD4[i];
        *(s16 *)(p1 + 0x18) = 0xCC;
        *(s16 *)(p1 + 0x1A) = (s8)D_800A2FD4[i] + 0x33;
        *(s16 *)(p1 + 0x20) = 0x11C;
        *(s16 *)(p1 + 0x22) = (s8)D_800A2FD4[i] + 0x33;
        p2 = i * 0xF0 + (D_800A8354 + 0x50);
        *(s16 *)(p2 + 0x8) = 0x7C;
        *(s16 *)(p2 + 0xA) = (s8)D_800A2FD4[i];
        *(s16 *)(p2 + 0x10) = 0xCC;
        *(s16 *)(p2 + 0x12) = (s8)D_800A2FD4[i];
        *(s16 *)(p2 + 0x18) = 0x7C;
        *(s16 *)(p2 + 0x1A) = (s8)D_800A2FD4[i] + 0x33;
        *(s16 *)(p2 + 0x20) = 0xCC;
        *(s16 *)(p2 + 0x22) = (s8)D_800A2FD4[i] + 0x33;
        tex = &D_80090FCE[1];
        *(u16 *)(D_800A83DA + i * 0xF0) = GetClut(tex->clutX, tex->clutY);
        *(u16 *)(D_800A83E2 + i * 0xF0) =
            GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
        p3 = i * 0xF0 + (D_800A8354 + 0x78);
        p3[0xC] = tex->u;
        p3[0xD] = tex->v;
        p3[0x14] = tex->u + 0x7C;
        p3[0x15] = tex->v;
        p3[0x1C] = tex->u;
        p3[0x1D] = tex->v + 0x3B;
        p3[0x24] = tex->u + 0x7C;
        p3[0x25] = tex->v + 0x3B;
        *(s16 *)(p3 + 0x8) = 0;
        *(s16 *)(p3 + 0xA) = (s8)D_800A2FD4[i];
        *(s16 *)(p3 + 0x10) = 0x7C;
        *(s16 *)(p3 + 0x12) = (s8)D_800A2FD4[i];
        *(s16 *)(p3 + 0x18) = 0;
        *(s16 *)(p3 + 0x1A) = (s8)D_800A2FD4[i] + 0x3B;
        *(s16 *)(p3 + 0x20) = 0x7C;
        *(s16 *)(p3 + 0x22) = (s8)D_800A2FD4[i] + 0x3B;
        tex += 5;
        *(u16 *)(D_800A8402 + i * 0xF0) = GetClut(tex->clutX, tex->clutY);
        *(u16 *)(D_800A840A + i * 0xF0) =
            GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
        p4 = i * 0xF0 + (D_800A8354 + 0xA0);
        p4[0xC] = tex->u;
        p4[0xD] = tex->v + 0x4B;
        p4[0x14] = tex->u;
        p4[0x15] = tex->v;
        p4[0x1C] = tex->u + 0xB1;
        p4[0x1D] = tex->v + 0x4B;
        p4[0x24] = tex->u + 0xB1;
        p4[0x25] = tex->v;
        *(s16 *)(p4 + 0x8) = 0;
        *(s16 *)(p4 + 0xA) = (s8)D_800A2FD4[i] + 0x3B;
        *(s16 *)(p4 + 0x10) = 0x4C;
        *(s16 *)(p4 + 0x12) = (s8)D_800A2FD4[i] + 0x3B;
        *(s16 *)(p4 + 0x18) = 0;
        *(s16 *)(p4 + 0x1A) = (s8)D_800A2FD4[i] + 0xEC;
        *(s16 *)(p4 + 0x20) = 0x4C;
        *(s16 *)(p4 + 0x22) = (s8)D_800A2FD4[i] + 0xEC;
        tex -= 17;
        *(u16 *)(D_800A842A + i * 0xF0) = GetClut(tex->clutX, tex->clutY);
        *(u16 *)(D_800A8432 + i * 0xF0) =
            GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
        p5 = i * 0xF0 + (D_800A8354 + 0xC8);
        p5[0xC] = tex->u;
        p5[0xD] = tex->v;
        p5[0x14] = tex->u + 0xF4;
        p5[0x15] = tex->v;
        p5[0x1C] = tex->u;
        p5[0x1D] = tex->v + 0x12;
        p5[0x24] = tex->u + 0xF4;
        p5[0x25] = tex->v + 0x12;
        *(s16 *)(p5 + 0x8) = 0x4C;
        *(s16 *)(p5 + 0xA) = (s8)D_800A2FD4[i] + 0x9A;
        *(s16 *)(p5 + 0x10) = 0x140;
        *(s16 *)(p5 + 0x12) = (s8)D_800A2FD4[i] + 0x9A;
        *(s16 *)(p5 + 0x18) = 0x4C;
        *(s16 *)(p5 + 0x1A) = (s8)D_800A2FD4[i] + 0xAC;
        *(s16 *)(p5 + 0x20) = 0x140;
        *(s16 *)(p5 + 0x22) = (s8)D_800A2FD4[i] + 0xAC;
        f4base = D_800A80F4;
        for (j = 0; j < 3; j++) {
            u8 *prim;
            u8 *prim3;
            s32 t;
            s32 t2;
            t = j * 0x18 + (s32)f4base;
            prim = (u8 *)(i * 0x48 + t);
            SetPolyF4((POLY_F4 *)prim);
            t2 = i * 0x48 + j * 0x18;
            prim3 = (u8 *)(t2 + (s32)f4base);
            prim3[4] = 8;
            prim3[5] = 8;
            prim3[6] = 8;
            *(s16 *)(prim3 + 8) = quads.s[j].x0;
            *(s16 *)(prim3 + 0xA) = quads.s[j].y0 + (s8)D_800A2FD4[i];
            *(s16 *)(prim3 + 0xC) = quads.s[j].x1;
            *(s16 *)(prim3 + 0xE) = quads.s[j].y1 + (s8)D_800A2FD4[i];
            *(s16 *)(prim3 + 0x10) =
                *(u16 *)(D_800A2FDC + j * 2) - (s8)D_800A2FD8[j];
            *(s16 *)(prim3 + 0x12) = (s8)D_800A2FD4[i] + 0x9E;
            *(s16 *)(prim3 + 0x14) =
                *(u16 *)(D_800A2FDC + j * 2) + (s8)D_800A2FD8[j];
            *(s16 *)(prim3 + 0x16) = (s8)D_800A2FD4[i] + 0x9E;
        }
    }
    if (D_800A2EA4[0] == 0) {
        tex = &D_80090FCE[4];
        for (i = 0; i < 4; i++) {
            u8 *prim;
            prim = i * 0x28 + D_800A8214;
            SetPolyFT4((POLY_FT4 *)prim);
            SetShadeTex(prim, 1);
            *(u16 *)(D_800A8222 + i * 0x28) = GetClut(tex->clutX, tex->clutY);
            *(u16 *)(D_800A822A + i * 0x28) =
                GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
            prim[0xC] = tex->u;
            prim[0xD] = tex->v;
            prim[0x14] = tex->u + 0x30;
            prim[0x15] = tex->v;
            prim[0x1C] = tex->u;
            prim[0x1D] = tex->v + 0x40;
            prim[0x24] = tex->u + 0x30;
            prim[0x25] = tex->v + 0x40;
        }
        *(u16 *)(D_800A8214 + 0xE) = GetClut(D_80091018[0], D_8009101A[0]);
        *(u16 *)(D_800A8214 + 0x16) =
            GetTPage(D_80091020[0], 0, D_80091014.tpx, D_80091016[0]);
        u = D_8009101C[0];
        v = D_8009101E[0];
        D_800A8220[0] = u;
        D_800A8221[0] = v;
        D_800A8228[0] = u + 0x40;
        D_800A8229[0] = v;
        D_800A8230[0] = u;
        D_800A8231[0] = v + 0x40;
        D_800A8238[0] = u + 0x40;
        D_800A8239[0] = v + 0x40;
        D_800A821C[0] = 0x7C;
        D_800A821E[0] = (s8)D_800A2FD4[0] + 0xAC;
        D_800A8224[0] = 0xBC;
        D_800A8226[0] = (s8)D_800A2FD4[0] + 0xAC;
        D_800A822C[0] = 0x7C;
        D_800A822E[0] = (s8)D_800A2FD4[0] + 0xEC;
        D_800A8234[0] = 0xBC;
        D_800A8236[0] = (s8)D_800A2FD4[0] + 0xEC;
        *(s16 *)(D_800A8214 + 0x30) = 0x3C;
        *(s16 *)(D_800A8214 + 0x32) = (s8)D_800A2FD4[0] + 0xAC;
        *(s16 *)(D_800A8214 + 0x38) = 0x6C;
        *(s16 *)(D_800A8214 + 0x3A) = (s8)D_800A2FD4[0] + 0xAC;
        *(s16 *)(D_800A8214 + 0x40) = 0x3C;
        *(s16 *)(D_800A8214 + 0x42) = (s8)D_800A2FD4[0] + 0xEC;
        *(s16 *)(D_800A8214 + 0x48) = 0x6C;
        *(s16 *)(D_800A8214 + 0x4A) = (s8)D_800A2FD4[0] + 0xEC;
        *(s16 *)(D_800A8214 + 0x58) = 0xE0;
        *(s16 *)(D_800A8214 + 0x5A) = (s8)D_800A2FD4[0] + 0xAC;
        *(s16 *)(D_800A8214 + 0x60) = 0x110;
        *(s16 *)(D_800A8214 + 0x62) = (s8)D_800A2FD4[0] + 0xAC;
        *(s16 *)(D_800A8214 + 0x68) = 0xE0;
        *(s16 *)(D_800A8214 + 0x6A) = (s8)D_800A2FD4[0] + 0xEC;
        *(s16 *)(D_800A8214 + 0x70) = 0x110;
        *(s16 *)(D_800A8214 + 0x72) = (s8)D_800A2FD4[0] + 0xEC;
        *(s16 *)(D_800A8214 + 0x80) = 0x110;
        *(s16 *)(D_800A8214 + 0x82) = (s8)D_800A2FD4[0] + 0xAC;
        *(s16 *)(D_800A8214 + 0x88) = 0x140;
        *(s16 *)(D_800A8214 + 0x8A) = (s8)D_800A2FD4[0] + 0xAC;
        *(s16 *)(D_800A8214 + 0x90) = 0x110;
        *(s16 *)(D_800A8214 + 0x92) = (s8)D_800A2FD4[0] + 0xEC;
        *(s16 *)(D_800A8214 + 0x98) = 0x140;
        *(s16 *)(D_800A8214 + 0x9A) = (s8)D_800A2FD4[0] + 0xEC;
        for (i = 0; i < 4; i++) {
            u8 *prim;
            prim = i * 0x28 + D_800A82B4;
            SetPolyFT4((POLY_FT4 *)prim);
            SetShadeTex(prim, 1);
        }
        tex = &D_80091014;
        primC = D_800A82C2;
        j = 0;
        primC[0] = GetClut(D_80091014.clutX, D_80091014.clutY);
        D_800A82CA[0] = GetTPage(D_80091014.tpage, 0, tex->tpx, D_80091014.tpy);
        u2 = D_8009101C[0];
        poly = (u8 *)primC + 0x1A;
        tex++;
        v2 = D_8009101E[0];
        D_800A82C0[0] = u2;
        D_800A82C1[0] = v2;
        D_800A82C8[0] = u2 + 1;
        D_800A82C9[0] = v2;
        D_800A82D0[0] = u2;
        D_800A82D1[0] = v2 + 0x40;
        D_800A82D8[0] = u2 + 1;
        D_800A82D9[0] = v2 + 0x40;
        D_800A82BC[0] = 0xBC;
        D_800A82BE[0] = (s8)D_800A2FD4[0] + 0xAC;
        D_800A82C4[0] = 0xC4;
        D_800A82C6[0] = (s8)D_800A2FD4[0] + 0xAC;
        D_800A82CC[0] = 0xBC;
        D_800A82CE[0] = (s8)D_800A2FD4[0] + 0xEC;
        D_800A82D4[0] = 0xC4;
        D_800A82D6[0] = (s8)D_800A2FD4[0] + 0xEC;
        for (; j < 3; j++) {
            u8 *prim;
            s32 next;
            s32 idx;
            u16 clut;
            clut = GetClut(tex->clutX, tex->clutY);
            next = j + 1;
            idx = next * 0x28;
            *(u16 *)((u8 *)D_800A82C2 + idx) = clut;
            *(u16 *)((u8 *)D_800A82CA + idx) =
                GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
            prim = (u8 *)(j * 0x28 + (s32)poly);
            prim[0xC] = tex->u + 0x71;
            prim[0xD] = tex->v + 0x10;
            prim[0x14] = tex->u + 0x71;
            prim[0x15] = tex->v;
            prim[0x1C] = tex->u + 0xB1;
            prim[0x1D] = tex->v + 0x10;
            prim[0x24] = tex->u + 0xB1;
            prim[0x25] = tex->v;
            *(s16 *)(prim + 8) = (j << 4) + 0xC0;
            *(s16 *)(prim + 0xA) = (s8)D_800A2FD4[0] + 0xAC;
            *(s16 *)(prim + 0x10) = (j << 4) + 0xD0;
            *(s16 *)(prim + 0x12) = (s8)D_800A2FD4[0] + 0xAC;
            *(s16 *)(prim + 0x18) = (j << 4) + 0xC0;
            *(s16 *)(prim + 0x1A) = (s8)D_800A2FD4[0] + 0xEC;
            *(s16 *)(prim + 0x20) = (j << 4) + 0xD0;
            *(s16 *)(prim + 0x22) = (s8)D_800A2FD4[0] + 0xEC;
        }
        D_800A8334[0] = 0x6C;
        D_800A833C[0] = 0x7C;
        D_800A8344[0] = 0x6C;
        D_800A834C[0] = 0x7C;
        D_800A8336[0] = (s8)D_800A2FD4[0] + 0xAC;
        D_800A833E[0] = (s8)D_800A2FD4[0] + 0xAC;
        D_800A8346[0] = (s8)D_800A2FD4[0] + 0xEC;
        D_800A834E[0] = (s8)D_800A2FD4[0] + 0xEC;
        for (i = 0; i < 4; i++) {
            u8 *prim;
            prim = i * 0x18 + D_800A81B4;
            SetPolyF4((POLY_F4 *)prim);
            prim[4] = 0xFF;
            prim[5] = 0;
            prim[6] = 0;
        }
        tex = D_80090FCE;
        for (i = 35; i >= 0; i--) {
            poly = i * 0x2C + D_800A7994;
            SetPolyFT4((POLY_FT4 *)poly);
            SetShadeTex(poly, 1);
            *(u16 *)(D_800A799E + i * 0x2C) = GetClut(tex->clutX, tex->clutY);
            *(u8 *)(D_800A7995 + i * 0x2C) = 2;
            *(u32 *)(D_800A79AC + i * 0x2C) = (u32)&D_800A85AC[i][0];
            *(u32 *)(D_800A79B0 + i * 0x2C) = (u32)&D_800A85AC[i][1];
            *(u32 *)(D_800A79B4 + i * 0x2C) = (u32)&D_800A85AC[i][3];
            *(u32 *)(D_800A79B8 + i * 0x2C) = (u32)&D_800A85AC[i][2];
            *(u16 *)(D_800A79A2 + i * 0x2C) =
                GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
            *(u8 *)(D_800A799C + i * 0x2C) = tex->u + 0x4F;
            *(u8 *)(D_800A799D + i * 0x2C) = tex->v + 0x2F;
            *(u8 *)(D_800A79A0 + i * 0x2C) = tex->u + 0x12;
            *(u8 *)(D_800A79A1 + i * 0x2C) = tex->v + 0x2F;
            *(u8 *)(D_800A79A4 + i * 0x2C) = tex->u + 0x4F;
            *(u8 *)(D_800A79A5 + i * 0x2C) = tex->v;
            *(u8 *)(D_800A79A8 + i * 0x2C) = tex->u + 0x12;
            *(u8 *)(D_800A79A9 + i * 0x2C) = tex->v;
        }
        for (i = 0; i < 0x20; i++) {
            D_800A7FE4[i].x =
                MathMultiplyFixed16(
                    0x3C0000,
                    *(s32 *)(*(u8 **)D_800A3A2CAbsolute2 + i * 128)) >>
                16;
            D_800A7FE4[i].y =
                MathMultiplyFixed16(
                    0x3C0000,
                    *(s32 *)(*(u8 **)D_800A3A34Absolute2 + i * 128)) >>
                16;
            D_800A7FE4[i + 0x20].x =
                MathMultiplyFixed16(
                    0x320000, *(s32 *)(*(u8 **)D_800A3A2CAbsolute + i * 128)) >>
                16;
            D_800A7FE4[i + 0x20].y =
                MathMultiplyFixed16(
                    0x320000, *(s32 *)(*(u8 **)D_800A3A34Absolute + i * 128)) >>
                16;
        }
        for (i = 0; i < 0x24; i++) {
            for (j = 0; j < 4; j++) {
                D_800A85AC[i][j].vz = 0x64;
            }
        }
        for (i = 0; i < 0x20; i++) {
            D_800A85AC[i][0].vx = D_800A7FE4[(i + 1) % 32].x;
            D_800A85AC[i][0].vy = D_800A7FE4[(i + 1) % 32].y;
            D_800A85AC[i][1].vx = D_800A7FE4[i].x;
            D_800A85AC[i][1].vy = D_800A7FE4[i].y;
            D_800A85AC[i][2].vx = D_800A7FE4[(i + 1) % 32 + 0x20].x;
            D_800A85AC[i][2].vy = D_800A7FE4[(i + 1) % 32 + 0x20].y;
            D_800A85AC[i][3].vx = D_800A7FE4[i + 0x20].x;
            D_800A85AC[i][3].vy = D_800A7FE4[i + 0x20].y;
        }
        D_800A89AC[0] = -0xA;
        D_800A89AE[0] = 0xA;
        D_800A89B4[0] = 0xA;
        D_800A89B6[0] = 0xA;
        D_800A89BC[0] = -0xA;
        D_800A89BE[0] = -0xA;
        D_800A89C4[0] = 0xA;
        D_800A89C6[0] = -0xA;
        SetShadeTex(D_800A7F14, 0);
        D_800A7F18[0] = 0x30;
        D_800A7F19[0] = 0x30;
        D_800A7F1A[0] = 0x30;
        tex = &D_80090FCE[-12];
        D_800A7F22[0] =
            GetTPage(*(u16 *)D_80090F32, 0, tex->tpx, D_80090F28[0]);
        tex += 12;
        u3 = D_80090F2E[0];
        v3 = D_80090F30[0];
        D_800A7F1C[0] = u3 + 0x60;
        D_800A7F1D[0] = v3 + 0xF;
        D_800A7F20[0] = u3 + 0x6F;
        D_800A7F21[0] = v3 + 0xF;
        D_800A7F24[0] = u3 + 0x60;
        D_800A7F25[0] = v3;
        D_800A7F28[0] = u3 + 0x6F;
        D_800A7F29[0] = v3;
        for (i = 0x21, j = 0; j < 3; j++, i++) {
            matA = *(s32 *)(*(u8 **)D_800A3A2CSmall + rot.a[j] * 4);
            matB = *(s32 *)(*(u8 **)D_800A3A34Small + rot.a[j] * 4);
            for (k = 0; k < 4; k++) {
                D_800A85AC[i][k].vx =
                    (MathMultiplyFixed16(corners.p[k].x << 16, matA) >> 16) -
                    (MathMultiplyFixed16(corners.p[k].y << 16, matB) >> 16);
                D_800A85AC[i][k].vy =
                    (MathMultiplyFixed16(corners.p[k].x << 16, matB) >> 16) +
                    (MathMultiplyFixed16(corners.p[k].y << 16, matA) >> 16);
            }
            idx = i * 0x2C;
            *(u8 *)(D_800A799C + idx) = tex->u + 0x12;
            *(u8 *)(D_800A799D + idx) = tex->v + 0x2F;
            *(u8 *)(D_800A79A0 + idx) = tex->u + 0x12;
            *(u8 *)(D_800A79A1 + idx) = tex->v;
            *(u8 *)(D_800A79A4 + idx) = tex->u + 0x4F;
            *(u8 *)(D_800A79A5 + idx) = tex->v + 0x2F;
            *(u8 *)(D_800A79A8 + idx) = tex->u + 0x4F;
            *(u8 *)(D_800A79A9 + idx) = tex->v;
        }
        D_800A3494 = 0x300;
        for (i = 0; i < 3; i++) {
            u8 *prim;
            prim = i * 0x28 + D_800A8534;
            SetPolyFT4((POLY_FT4 *)prim);
            SetSemiTrans(prim, 1);
            prim[7] = prim[7] & 0xFE;
            *(u16 *)(D_800A854A + i * 0x28) = GetTPage(2, 2, 0x300, 0);
            prim[0xC] = 0xFD;
            prim[0xD] = 0;
            prim[0x14] = 0xFE;
            prim[0x15] = 0;
            prim[0x1C] = 0xFD;
            prim[0x1D] = 1;
            prim[0x24] = 0xFE;
            prim[0x25] = 1;
            yv = (s8)D_800A2FD4[0] + 0x9E;
            *(s16 *)(prim + 0x12) = yv;
            *(u16 *)(D_800A853E + i * 0x28) = yv;
        }
        for (i = 0; i < 2; i++) {
            SetPolyF4((POLY_F4 *)(D_800A8184 + i * 0x18));
        }
        D_800A8188[0] = 8;
        D_800A8189[0] = 8;
        D_800A818A[0] = 8;
        D_800A818C[0] = 0;
        D_800A818E[0] = 0xEC;
        D_800A8190[0] = 0x1F;
        D_800A8192[0] = 0xEC;
        D_800A8194[0] = 0;
        D_800A8196[0] = 0xF0;
        D_800A8198[0] = 0x1F;
        D_800A819A[0] = 0xF0;
        D_800A81A0[0] = 0x10;
        D_800A81A1[0] = 0x10;
        D_800A81A2[0] = 0x10;
        D_800A81A4[0] = 0x1F;
        D_800A81A6[0] = 0xEC;
        D_800A81A8[0] = 0x140;
        D_800A81AA[0] = 0xEC;
        D_800A81AC[0] = 0x1F;
        D_800A81AE[0] = 0xF0;
        D_800A81B0[0] = 0x140;
        D_800A81B2[0] = 0xF0;
        D_800A7FD8[0] = 0;
        D_800A7FDC[0] = 0x64;
        D_800A7FE0[0] = 0x64;
    }
}

INCLUDE_RODATA("asm/nonmatchings/scene", D_8008D4F4);

extern s32 D_800A2E94[];
extern s32 D_800A2EA4[];
extern s32 D_800A2EA8[];
extern s32 D_800A2EACAbsolute[];
extern s32 D_800A2EB0Absolute[];
extern u8 gStandingsPlaceX;
extern u8 gStandingsNameX;
extern u8 gStandingsNameXAbsolute[];
extern u8 gStandingsLapX;
extern u8 gStandingsTimeX;
extern char D_800A301C[];
extern char D_800A3020[];
extern char D_800A3024[];
extern char D_800A302C[];
extern char D_800A3034[];
extern char D_800A3038[];
extern u8 *D_800A3554[];
extern s32 D_800A35E0[];
extern u8 gTextColor;
extern u8 D_800BE70C[];
extern s32 D_800BE974[];
extern s32 D_800AE1EC[];
extern char *D_8009AC1C[];
extern char *D_8009ADEC[];
extern char *D_8009ADF0[];
extern char *D_8009ADF4[];
extern char *D_8009AE94[];
typedef struct Car {
    u8 unk0[0xF4];
    u8 unkF4;
    u8 unkF5[0x1D6 - 0xF5];
    s16 lap;
    u8 unk1D8[0x1E0 - 0x1D8];
    s16 unk1E0;
    u8 unk1E2[0x1EC - 0x1E2];
    s16 unk1EC;
    u8 unk1EE[0x204 - 0x1EE];
    s8 place;
    u8 unk205[0x25C - 0x205];
    s32 unk25C;
    s32 unk260;
    s32 unk264;
    u8 unk268[0x34C - 0x268];
    char *name;
    u8 unk350[0x3E8 - 0x350];
    struct CarLink *unk3E8;
} Car;

typedef struct CarLink {
    u8 unk0[8];
    Car *next;
} CarLink;

extern s32 sprintfRow(char *, char *, ...) asm("sprintf");
extern void func_80050028Row(char *, s32, s32, s32);
asm(".globl func_80050028Row\nfunc_80050028Row = func_80050028");
extern void func_8004FF90Row(s16, s32, s32, s32) asm("func_8004FF90");
extern void func_80050670Row(s32, s32, s32, s32, s32) asm("func_80050670");

void HudDrawStandings(s8 arg0, s32 y) {
    char text[8];
    Car *entry;
    s8 index;
    s8 rowStart;
    s8 row;
    s8 carIndex;
    u8 selected;
    s32 gap;
    s32 limit;
    u8 *column;
    s32 textY;

    if (D_800A2EB0Absolute[0] != 0) {
        selected = 0;
        rowStart = arg0;
        row = 1;
        carIndex = arg0 + 1;
        do {
            sprintfRow(text, carIndex < 10 ? D_800A301C : D_800A3020, carIndex);
            gTextColor = 9;
            textY = (u8)y;
            func_80050028Row(text, gStandingsPlaceX + 3, textY, 0);
            if (carIndex == ((Car *)D_800A3554[0])->place) {
                if (selected == 0 && D_800A2EACAbsolute[0] == 0) {
                    gTextColor = 0;
                    func_80050028Row(((Car *)D_800A3554[0])->name,
                                     gStandingsNameX, textY, 0);
                    gTextColor = 9;
                    func_8004FF90Row(((Car *)D_800A3554[0])->lap,
                                     gStandingsLapX + 8, textY, 0);
                    func_80050670Row(((Car *)D_800A3554[0])->unk25C,
                                     gStandingsTimeX, textY, 0, 1);
                    func_8001D778(0, (y & 0xFF) - 1, 0x140, 0xC, 0, 0, 0x80, 0);
                    if (row == 15) {
                        return;
                    }
                    selected = 1;
                    row++;
                    carIndex++;
                    gTextColor = 9;
                    y += 12;
                    sprintfRow(text, carIndex < 10 ? D_800A301C : D_800A3020,
                               carIndex);
                    func_80050028Row(text, gStandingsPlaceX + 3, (u8)y, 0);
                }
                if (carIndex == ((Car *)D_800A3554[0])->place &&
                    D_800A2EA8[0] >= ((Car *)D_800A3554[0])->lap) {
                    goto skipBlank;
                }
            }
            func_80050028Row(D_8009AE94[0], gStandingsLapX + 8, (u8)y, 0);
        skipBlank:
            gTextColor = 0;
            limit = (u8)arg0 + 1;
            index = rowStart;
            if (((Car *)D_800A3554[0])->place < limit &&
                D_800A2EACAbsolute[0] == 0) {
                index = rowStart - 1;
            }
            textY = (u8)y;
            func_80050028Row(D_8009AC1C[D_800BE70C[index]], gStandingsNameX,
                             textY, 0);
            if (carIndex == ((Car *)D_800A3554[0])->place &&
                ((Car *)D_800A3554[0])->lap < 2) {
                func_80050028Row(D_8009ADF4[0], gStandingsTimeX, textY, 0);
            } else {
                func_80050670Row(D_800AE1EC[index], gStandingsTimeX, (u8)y, 0,
                                 1);
            }
            if (D_800A2EACAbsolute[0] != 0 &&
                carIndex == ((Car *)D_800A3554[0])->place) {
                func_8001D778(0, (y & 0xFF) - 1, 0x140, 0xC, 0, 0, 0x80, 0);
            }
            rowStart++;
            row++;
            carIndex++;
            y += 12;
        } while (row < 16);
        return;
    }
    entry = (Car *)D_800A35E0[0];
    for (rowStart = 0; rowStart < (u8)arg0; rowStart++) {
        entry = entry->unk3E8->next;
    }
    rowStart = arg0;
    row = 1;
    if (rowStart < D_800A2E94[0]) {
        column = gStandingsNameXAbsolute;
        do {
            func_80050028Row(entry->name, gStandingsNameX, (u8)y, 0);
            if (D_800A2EA4[0] != 0) {
                func_8004FF90Row(entry->place, column[-1] + 6, (u8)y, 0);
            } else {
                sprintfRow(text, entry->place < 10 ? D_800A301C : D_800A3020,
                           entry->place);
                gTextColor = 9;
                func_80050028Row(text, column[-1] + 3, (u8)y, 0);
                gTextColor = 0;
            }
            if (entry->unkF4 == 0 && D_800A2EA8[0] >= entry->lap) {
                func_80050028Row(D_8009ADF4[0], gStandingsTimeX, (u8)y, 0);
            } else {
                s32 lap;

                lap = entry->lap;
                gTextColor = 9;
                if (D_800A2EA8[0] < lap) {
                    sprintfRow(text, D_800A3024, D_8009AE94[0]);
                } else if (lap >= 100) {
                    sprintfRow(text, D_800A3020, lap);
                } else if (lap >= 10) {
                    sprintfRow(text, D_800A301C, lap);
                } else {
                    sprintfRow(text, D_800A302C, lap);
                }
                textY = (u8)y;
                func_80050028Row(text, gStandingsLapX - 4, textY, 0);
                if (entry->lap == 0) {
                    func_80050670Row(0x7FFFFFFF, gStandingsTimeX, textY, 0, 0);
                } else if (entry == (Car *)D_800A35E0[0]) {
                    func_80050670Row(entry->unk260, gStandingsTimeX, textY, 0,
                                     0);
                } else {
                    gap = (s16)(((((Car *)D_800A35E0[0])->lap * D_800BE974[0] +
                                  ((Car *)D_800A35E0[0])->unk1E0) -
                                 (entry->lap * D_800BE974[0] + entry->unk1E0)) /
                                D_800BE974[0]);
                    gTextColor = 9;
                    if (gap > 0) {
                        func_80050028Row(D_800A3034, gStandingsTimeX - 10,
                                         textY, 0);
                        func_8004FF90Row(gap, gStandingsTimeX, textY, 0);
                        if (gap == 1) {
                            func_80050028Row(D_8009ADF0[0],
                                             gStandingsTimeX + 15, textY, 0);
                        } else if (gap < 10) {
                            func_80050028Row(D_8009ADEC[0],
                                             gStandingsTimeX + 15, textY, 0);
                        } else if (gap < 100) {
                            func_80050028Row(D_8009ADEC[0],
                                             gStandingsTimeX + 25, textY, 0);
                        } else {
                            func_80050028Row(D_8009ADEC[0],
                                             gStandingsTimeX + 35, textY, 0);
                        }
                    } else {
                        func_80050028Row(D_800A3038, gStandingsTimeX - 10,
                                         textY, 0);
                        func_80050670Row(entry->unk264, gStandingsTimeX, textY,
                                         0, 1);
                    }
                }
            }
            if (entry->unk1EC == 0 && D_800A2E94[0] >= 3) {
                func_8001D778(0, (y & 0xFF) - 1, 0x140, 0xC, 0, 0, 0x80, 0);
            }
            if (row == 15) {
                return;
            }
            rowStart++;
            row++;
            entry = entry->unk3E8->next;
            y += 12;
        } while (rowStart < D_800A2E94[0]);
    }
}

INCLUDE_ASM("asm/nonmatchings/scene", func_8004DF38);

INCLUDE_ASM("asm/nonmatchings/scene", func_8004E294);

extern s32 D_800A2CE0[];
extern s8 D_800992D0[];
extern s32 D_800A8A2C[];
extern s32 D_800A8A30[];
extern s8 D_800A3498;
extern s8 D_800A349C;
extern s8 D_800A34A8;
extern s16 D_800A34A0;
extern s16 D_800A34A4;
void func_8004E700(void) {
    s32 idx;
    s32 *q;
    s8 *p;
    s32 pm;
    s32 base;
    s32 inf;
    s8 i;

    idx = D_800A2CE0[0];
    D_800A34A8 = 0;
    D_800A3498 = 0;
    D_800A34A4 = 0;
    D_800A349C = 0x3C;
    p = D_800992D0;
    i = 0;
    if (p[idx] > 0) {
        q = &D_800BE974[0];
        pm = (s32)p;
        inf = 0x7FFFFFFF;
    loop:
        base = *q;
        /* The do-while (0) doubles the refs of the loop locals, which swaps
         * the a0/a1/a2 and t0/t1 allocation to retail's. */
        do {
            D_800A8A2C[i * 2] = base + base * (i + 1) / *(s8 *)(idx + pm);
            D_800A8A30[i * 2] = inf;
            i++;
            if (i < *(s8 *)(idx + pm)) {
                goto loop;
            }
        } while (0);
    }
    D_800A34A0 = D_800BE974[0] * 2 + 1;
}

extern s8 D_800A349C;
extern u8 D_800A34AC;
extern u8 D_800A34B0;
extern s32 D_800A34B4;
extern s32 D_800A34B8;
extern s32 D_800A34BC;
extern s32 D_800A34C0;
extern u8 *D_800A3554[];
extern u8 *D_8009AE4C[];
extern void func_8004EA34(void);
extern void func_80050028Lbl(char *, s16, s16, s8);
asm(".globl func_80050028Lbl\nfunc_80050028Lbl = func_80050028");

void func_8004E808(void) {
    if (D_800A349C < 0x3C) {
        return;
    }
    if (D_800A34B0 != 0) {
        if ((s8)D_800A34AC == 0x3C) {
            func_8004EA34();
            if (D_800A34BC == 0 && D_800A34C0 == 0) {
                D_800A34B0 = 0;
                return;
            }
        }
        if ((s8)D_800A34AC > 0) {
            D_800A34AC = (s8)D_800A34AC - 4;
        }
        D_800A34B0 = D_800A34B0 - 1;
        goto display;
    }
    if ((s8)D_800A34AC < 0x3C) {
        D_800A34AC = (s8)D_800A34AC + 4;
    display:
        if (*(u8 *)(D_800A3554[0] + 0x268) == 0) {
            GraphicsSetColor(0x80, 0x80, 0xC0);
            func_80050028Lbl((char *)D_8009AE4C[0], 0x50, (s8)D_800A34AC + 0xB9,
                             0);
            GraphicsSetColor(0x80, 0xC0, 0x80);
            if (D_800A34BC != 0) {
                func_80050028Lbl((char *)D_800A34B4, 0x50,
                                 (s8)D_800A34AC + 0xC3, 0);
                func_80050670((void *)D_800A34BC, 0x96,
                              (s16)((s8)D_800A34AC + 0xC3), 0, 1);
            }
            if (D_800A34C0 != 0) {
                func_80050028Lbl((char *)D_800A34B8, 0x50,
                                 (s8)D_800A34AC + 0xCD, 0);
                func_80050670((void *)D_800A34C0, 0x96,
                              (s16)((s8)D_800A34AC + 0xCD), 0, 1);
            }
            func_80044A1C(0x4B, (s8)D_800A34AC + 0xB4, 0xA0, 0x28, 0, 0, 0, 1);
        }
    }
}

extern s32 D_800A35E0[];
extern u8 *D_800A3554[];
extern s32 D_800BE974[];
extern s32 D_800A34B4;
extern s32 D_800A34B8;
extern s32 D_800A34BC;
extern s32 D_800A34C0;
extern char D_800A8A4C[];
extern char D_800A8A60[];
extern char D_800A303C[];
extern char *strcpy(char *, const char *);
extern char *strtok(char *, const char *);

void func_8004EA34(void) {
    register s32 len asm("v1");
    register u8 *car asm("a1");
    u8 *e0;
    register s32 prod2 asm("$8");
    s32 prod1;
    s32 refDist;
    s32 rel;
    s32 e01d6;
    s32 car1d6;
    s32 e0dist;
    s32 cardist;
    s32 other1d6;
    s32 otherdist;
    char *name2;
    s32 t1;
    s32 t2;

    e0 = (u8 *)D_800A35E0[0];
    len = D_800BE974[0];
    e01d6 = *(s16 *)(e0 + 0x1D6);
    asm volatile("mult\t%0, %1" : : "r"(e01d6), "r"(len));
    car = D_800A3554[0];
    car1d6 = *(s16 *)(car + 0x1D6);
    asm volatile("mflo %0" : "=r"(prod1));
    asm volatile("mult\t%0, %1" : : "r"(car1d6), "r"(len));
    e0dist = *(s16 *)((u8 *)(e0) + 0x1E0);
    cardist = *(s16 *)((u8 *)(car) + 0x1E0);
    asm volatile("sw\t$zero, %gp_rel(D_800A34C0)($gp)");
    asm volatile("sw\t$zero, %gp_rel(D_800A34BC)($gp)");
    refDist = prod1 + e0dist;
    asm volatile("mflo %0" : "=r"(prod2));
    asm volatile("addu %0, %2, %1" : "=r"(cardist) : "0"(cardist), "r"(prod2));
    if (refDist - cardist < len) {
        if (*(s8 *)(car + 0x204) >= 2) {
            e0 = *(u8 **)(*(u8 **)(car + 0x3E4) + 8);
            t1 = *(s32 *)(car + 0x264);
            t2 = *(s32 *)(e0 + 0x264);
            car = *(s32 *)((u8 *)(e0) + 0x34C);
            D_800A34BC = t1 - t2;
            strcpy(D_800A8A4C, (char *)car);
            D_800A34B4 = (s32)strtok(D_800A8A4C, D_800A303C);
            D_800A34B4 = (s32)strtok((char *)0, D_800A303C);
        }
        asm volatile("" : : : "memory");
        if (*(s32 *)(D_800A3554[0] + 0x3E8) != 0) {
            e0 = *(u8 **)(*(u8 **)(D_800A3554[0] + 0x3E8) + 8);
            len = D_800BE974[0];
            other1d6 = *(s16 *)(e0 + 0x1D6);
            asm volatile("mult\t%0, %1" : : "r"(other1d6), "r"(len));
            otherdist = *(s16 *)(e0 + 0x1E0);
            asm volatile("mflo $7\n\taddu %0, $7, %1"
                         : "=r"(otherdist)
                         : "0"(otherdist));
            if (refDist - otherdist < len) {
                rel = *(s32 *)(e0 + 0x264);
                if (*(s8 *)(D_800A3554[0] + 0x204) != 1) {
                    rel -= *(s32 *)(D_800A3554[0] + 0x264);
                }
                name2 = *(char **)(e0 + 0x34C);
                D_800A34C0 = rel;
                strcpy(D_800A8A60, name2);
                D_800A34B8 = (s32)strtok(D_800A8A60, D_800A303C);
                D_800A34B8 = (s32)strtok((char *)0, D_800A303C);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/scene", func_8004EBE4);

INCLUDE_ASM("asm/nonmatchings/scene", func_8004F158);

typedef struct {
    u16 tpx;
    u16 tpy;
    u16 clutX;
    u16 clutY;
    u8 u;
    u8 unk9;
    u16 v;
    u16 tpage;
} TrackTexture;
extern TrackTexture D_80090F26[];
extern void SetPolyFT4(POLY_FT4 *);
extern POLY_FT4 D_800A8A84[];
extern u8 D_800A8A88[];
extern u8 D_800A8A89[];
extern u8 D_800A8A8A[];
extern u8 D_800A8A90[];
extern u8 D_800A8A91[];
extern u8 D_800A8A98[];
extern u8 D_800A8A99[];
extern u8 D_800A8AA0[];
extern u8 D_800A8AA1[];
extern u8 D_800A8AA8[];
extern u8 D_800A8AA9[];
extern u16 D_800A8A9A[];
extern u8 *D_800A8A74[];
extern u8 *D_800A8AB0[];
extern u8 *D_800A8AB0nm[] asm("D_800A8AB0.NON_MATCHING");
extern u8 D_800A8AB4[];
extern u8 D_800A8AB6[];
extern s32 D_800A2CE0[];
extern s8 D_800992D0[];
extern u8 D_80099230[];
extern u8 D_80099231[];
extern u8 D_800A3614;
extern u8 D_800A380C;
extern u8 D_800A3924;
extern u8 D_800A35A8;
extern s16 D_800A34C4;
extern s32 D_801F3FF8[];

void func_8004F880(void) {
    TrackTexture *tim;
    u8 *car;
    s8 *p;
    s8 *pb;
    s8 *pj;
    s32 pm;
    s32 *q;
    s32 uvBase;
    s32 distBase;
    s32 stride;
    s32 idx;
    s32 x;
    s32 lim;
    s32 inf;
    s32 w;
    s8 i;
    s8 j;
    s32 pad[2];

    (void)&pad;
    tim = D_80090F26;
    D_800A3614 = 0;
    D_800A380C = 0;
    D_800A3924 = 0;
    D_800A35A8 = 0;
    D_800A8AB0[0] = HeapAlloc(0xC0);
    for (i = 0; i < 4; i++) {
        lim = 0x7FFF;
        pb = D_800992D0;
        do {
            stride = i * 0x30;
            *(u8 *)(stride + (s32)D_800A8AB0[0]) = 0x7F;
            uvBase = stride + (s32)D_800A8AB0[0];
            p = (s8 *)D_800A2CE0[0];
        } while (0);
        p = (s8 *)((s32)p + (s32)pb);
        *(u16 *)(uvBase + 4) = lim;
        *(u16 *)(uvBase + 2) = lim;
        j = 0;
        if (j < p[0]) {
            pj = p;
        innerJ:
            inf = 0x7FFFFFFF;
            *(u16 *)(stride + (s32)D_800A8AB0[0] + 6 + j * 2) = lim;
            distBase = j * 4 + (stride + (s32)D_800A8AB0nm[0]);
            *(s32 *)(distBase + 0x20) = inf;
            *(s32 *)(distBase + 0x10) = inf;
            j++;
            if (j < pj[0]) {
                goto innerJ;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        D_800A8A74[i] = D_800A8AB0[0] + i * 0x30;
    }
    x = D_801F3FF8[0];
    D_800A34C4 = x * 4;
    idx = D_800A2CE0[0];
    p = D_800992D0;
    if (D_800992D0[idx] > 0) {
        i = 0;
        q = &D_800BE974[0];
        pm = (s32)p;
        w = (x << 18) >> 16;
    loopM:
        *(u16 *)(D_800A8AB4 + i * 4) =
            0x12C - D_80099230[idx * 2] -
            *(s32 *)((u8 *)D_800BE980[0] +
                     (i * q[0] / *(s8 *)(idx + pm)) * 0x90 + 0x14) /
                w -
            4;
        uvBase = q[0];
        *(u16 *)(D_800A8AB6 + i * 4) =
            D_80099231[idx * 2] +
            *(s32 *)((u8 *)D_800BE980[0] +
                     (i * uvBase / *(s8 *)(idx + pm)) * 0x90 + 0x18) /
                w +
            0xE;
        i++;
        if (i < *(s8 *)(idx + pm)) {
            goto loopM;
        }
    }
    SetPolyFT4(D_800A8A84);
    SetShadeTex(D_800A8A84, 0);
    D_800A8A88[0] = 0x80;
    D_800A8A89[0] = 0x80;
    D_800A8A8A[0] = 0xC0;
    D_800A8A90[0] = tim->u + 0x60;
    D_800A8A91[0] = tim->v;
    D_800A8A98[0] = tim->u + 0x6F;
    D_800A8A99[0] = tim->v;
    D_800A8AA0[0] = tim->u + 0x60;
    D_800A8AA1[0] = (u8)tim->v + 0xF;
    D_800A8AA8[0] = tim->u + 0x6F;
    D_800A8AA9[0] = (u8)tim->v + 0xF;
    D_800A8A9A[0] = GetTPage(tim->tpage, 0, tim->tpx, tim->tpy);
    car = D_800A3554[0];
    *(u16 *)(car + 0x2A4) = *(u16 *)(car + 0x2A0) + 8;
    *(u16 *)(car + 0x2AA) = *(u16 *)(car + 0x2A6) + 8;
}

INCLUDE_ASM("asm/nonmatchings/scene", func_8004FCF4);

extern u8 *D_800A3554[];
extern u8 *D_800A8A80[];
void func_8004FF3C(void) {
    D_800A8A80[0][0] = *(u16 *)(D_800A3554[0] + 0x2AA);
    D_800A8A80[0][1] = *(u16 *)(D_800A3554[0] + 0x2A4);
    *(u16 *)(D_800A8A80[0] + 4) = *(u16 *)(D_800A3554[0] + 0x1D6);
}

extern s8 gTextColorS asm("gTextColor.NON_MATCHING");
extern char D_800A3020nm[] asm("D_800A3020.NON_MATCHING");
extern u8 gTextColorNm asm("gTextColor.NON_MATCHING");
extern void func_80050028Args(char *, s16, s16, s8);
asm(".globl func_80050028Args\nfunc_80050028Args = func_80050028");
extern s32 sprintfTextArgs(char *, char *, ...);
asm(".globl sprintfTextArgs\nsprintfTextArgs = sprintf");
void func_8004FF90(s32 arg0, s32 arg1, s32 arg2, s8 arg3) {
    char text[16];

    if (arg3 == 1) {
        gTextColorNm = 6;
    } else {
        gTextColorNm = 9;
    }
    sprintfTextArgs(text, D_800A3020nm, arg0);
    func_80050028Args(text, (s16)arg1, (s16)arg2, arg3);
    gTextColorNm = 0;
}

extern u8 D_800A34C8[3];
extern u8 D_800A8AC8[];
extern u8 D_800A8AC9[];
extern u8 D_800A8ACA[];
extern u8 D_800A36FC;
extern u8 D_800A3700;
extern u8 D_80098D18[];
extern POLY_FT4 D_800A8AC4[];
extern POLY_FT4 D_800A8AC4nm[] asm("D_800A8AC4.NON_MATCHING");
extern u8 D_800A8ADA[];

#ifdef NON_MATCHING
void func_80050028(u8 *text, s32 x, s32 y, s8 mode) {
    extern u8 D_80098BD0[];
    POLY_FT4 *prim;
    u8 *p;
    u8 *cp;
    u8 *glyph;
    u16 w;
    u8 i;
    s32 lineH;
    s32 newX;
    s32 rightX;
    u8 v3;
    s32 tc;
    u8 color;
    s32 ySum;
    s16 *x3p;
    u8 *cp2;
    s16 *x0p;

    i = 0;
    if (mode == 1) {
        lineH = (u32)(*(s16 *)&D_80098D18[0] * 3) >> 2;
    } else {
        lineH = *(u16 *)&D_80098D18[0];
    }
    if (mode >= 2) {
        u8 sr;
        u8 sg;
        u8 sb;

        do {
            asm("" : "=r"(cp) : "0"(D_800A8AC8));
            sr = cp[0];
            sg = cp[1];
            sb = cp[2];
            D_800A34C8[0] = sr;
            D_800A34C8[1] = sg;
            D_800A34C8[2] = sb;
            if (mode == 2) {
                color = D_800A36FC;
            } else {
                color = D_800A3700;
            }
            cp[0] = color;
            cp[1] = color;
            cp[2] = color;
        } while (0);
        prim = D_800A8AC4nm;
        SetSemiTrans(prim, 1);
        p = (u8 *)prim + 0x16;
        if (text[i] != 0) {
            lineH = y + lineH;
            do {
                glyph = &D_80098BD0[text[i] * 10];
                tc = GetTPage(0, 1, *(s16 *)(glyph + 0), *(s16 *)(glyph + 2));
                *(u16 *)p = tc;
                w = *(u16 *)(glyph + 6);
                *(u8 *)(p - 0xA) = glyph[4];
                *(u8 *)(p - 0x9) = glyph[5];
                *(u8 *)(p - 0x2) = glyph[4] + w;
                *(u8 *)(p - 0x1) = glyph[5];
                *(u8 *)(p + 0x6) = glyph[4];
                *(u8 *)(p + 0x7) = glyph[5] + glyph[8];
                *(u8 *)(p + 0xE) = glyph[4] + w;
                tc = gTextColorS;
                v3 = glyph[5] + glyph[8];
                *(u8 *)(p + 0xF) = v3;
                if (tc != 0) {
                    newX = x + ((tc - (s16)w) >> 1);
                    x = x + tc;
                    rightX = w + newX;
                    *(s16 *)(p - 0xE) = newX;
                    *(s16 *)(p - 0xC) = y;
                    *(s16 *)(p - 0x6) = rightX;
                    *(s16 *)(p - 0x4) = y;
                    *(s16 *)(p + 0x2) = newX;
                    *(s16 *)(p + 0x4) = lineH;
                    x3p = (s16 *)(p + 0xA);
                    *x3p = rightX;
                } else {
                    rightX = x + w;
                    *(s16 *)(p - 0xE) = x;
                    *(s16 *)(p + 0x2) = x;
                    x = rightX;
                    *(s16 *)(p - 0xC) = y;
                    *(s16 *)(p - 0x6) = rightX;
                    *(s16 *)(p - 0x4) = y;
                    *(s16 *)(p + 0x4) = lineH;
                    *(s16 *)(p + 0xA) = rightX;
                }
                *(s16 *)(p + 0xC) = lineH;
                func_80017D80((u8 *)D_800A8AC4);
                i++;
            } while (text[i] != 0);
        }
        D_800A8AC8[0] = D_800A34C8[0];
        D_800A8AC9[0] = D_800A34C8[1];
        D_800A8ACA[0] = D_800A34C8[2];
        SetSemiTrans(D_800A8AC8 - 4, 0);
        return;
    }
    if (mode == 1) {
        if (text[i] != 0) {
            p = D_800A8ADA;
            do {
                glyph = &D_80098BD0[text[i] * 10];
                *(u16 *)p =
                    GetTPage(0, 0, *(s16 *)(glyph + 0), *(s16 *)(glyph + 2));
                *(u8 *)(p - 0xA) = glyph[4];
                *(u8 *)(p - 0x9) = glyph[5];
                *(u8 *)(p - 0x2) = glyph[4] + glyph[6];
                *(u8 *)(p - 0x1) = glyph[5];
                *(u8 *)(p + 0x6) = glyph[4];
                *(u8 *)(p + 0x7) = glyph[5] + glyph[8];
                *(u8 *)(p + 0xE) = glyph[4] + glyph[6];
                *(u8 *)(p + 0xF) = glyph[5] + glyph[8];
                rightX = x + ((*(s16 *)(glyph + 6) * 3) >> 2);
                ySum = y + lineH;
                x0p = (s16 *)(p - 0xE);
                *x0p = x;
                *(s16 *)(p - 0xC) = y;
                *(s16 *)(p - 0x4) = y;
                *(s16 *)(p + 0x2) = x;
                *(s16 *)(p + 0x4) = ySum;
                *(s16 *)(p + 0xC) = ySum;
                x = rightX;
                *(s16 *)(p - 0x6) = rightX;
                *(s16 *)(p + 0xA) = rightX;
                func_80017D80(p - 0x16);
                i++;
            } while (text[i] != 0);
        }
        return;
    }
    if (gTextColorS != 0) {
        if (text[i] != 0) {
            do {
                glyph = &D_80098BD0[text[i] * 10];
                *(u16 *)D_800A8ADA =
                    GetTPage(0, 0, *(s16 *)(glyph + 0), *(s16 *)(glyph + 2));
                w = *(u16 *)(glyph + 6);
                *(u8 *)(D_800A8ADA - 0xA) = glyph[4];
                *(u8 *)(D_800A8ADA - 0x9) = glyph[5];
                *(u8 *)(D_800A8ADA - 0x2) = glyph[4] + w;
                cp2 = D_800A8ADA;
                *(u8 *)(D_800A8ADA - 0x1) = glyph[5];
                *(u8 *)(D_800A8ADA + 0x6) = glyph[4];
                *(u8 *)(D_800A8ADA + 0x7) = glyph[5] + glyph[8];
                *(u8 *)(D_800A8ADA + 0xE) = glyph[4] + w;
                *(u8 *)(D_800A8ADA + 0xF) = glyph[5] + glyph[8];
                newX = x + ((gTextColorS - (s16)w) >> 1);
                x = x + gTextColorS;
                rightX = w + newX;
                ySum = y + lineH;
                *(s16 *)(D_800A8ADA - 0xC) = y;
                *(s16 *)(D_800A8ADA - 0x4) = y;
                *(s16 *)(cp2 - 0xE) = newX;
                *(s16 *)(D_800A8ADA + 0x2) = newX;
                *(s16 *)(D_800A8ADA - 0x6) = rightX;
                *(s16 *)(D_800A8ADA + 0x4) = ySum;
                *(s16 *)(D_800A8ADA + 0xA) = rightX;
                *(s16 *)(D_800A8ADA + 0xC) = ySum;
                func_80017D80(D_800A8ADA - 0x16);
                i++;
            } while (text[i] != 0);
        }
        return;
    }
    if (text[i] != 0) {
        if (i) {
            lineH = y + lineH;
            p = D_800A8ADA;
        } else {
            lineH = y + lineH;
            p = D_800A8ADA;
        }
        do {
            glyph = &D_80098BD0[text[i] * 10];
            *(u16 *)p =
                GetTPage(0, 0, *(s16 *)(glyph + 0), *(s16 *)(glyph + 2));
            w = *(u16 *)(glyph + 6);
            *(u8 *)(p - 0xA) = glyph[4];
            *(u8 *)(p - 0x9) = glyph[5];
            *(u8 *)(p - 0x2) = glyph[4] + w;
            *(u8 *)(p - 0x1) = glyph[5];
            *(u8 *)(p + 0x6) = glyph[4];
            *(u8 *)(p + 0x7) = glyph[5] + glyph[8];
            *(u8 *)(p + 0xE) = glyph[4] + w;
            v3 = glyph[5] + glyph[8];
            rightX = x + w;
            *(s16 *)(p - 0xE) = x;
            *(s16 *)(p + 0x2) = x;
            x = rightX;
            *(s16 *)(p - 0xC) = y;
            *(s16 *)(p - 0x6) = rightX;
            *(s16 *)(p - 0x4) = y;
            *(s16 *)(p + 0x4) = lineH;
            *(s16 *)(p + 0xA) = rightX;
            *(s16 *)(p + 0xC) = lineH;
            *(u8 *)(p + 0xF) = v3;
            func_80017D80(p - 0x16);
            i++;
        } while (text[i] != 0);
    }
}

#else
INCLUDE_ASM("asm/nonmatchings/scene", func_80050028);
#endif
INCLUDE_ASM("asm/nonmatchings/scene", func_80050670);

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

extern u8 D_80098D16[];
s32 func_80050940(u8 *str) {
    s32 sum;
    u8 c;
    s32 offset;

    sum = 0;
    if (*(volatile u8 *)str != 0) {
        c = *str;
        do {
            str++;
            offset = c;
            offset = offset - 0x20;
            offset = offset * 10;
            sum += *(s16 *)&D_80098D16[offset];
            c = *str;
        } while (c != 0);
    }
    return sum;
}

INCLUDE_ASM("asm/nonmatchings/scene", func_8005098C);

INCLUDE_ASM("asm/nonmatchings/scene", func_80050D1C);

extern u8 D_800A34D4, D_800A39F8, D_800A3764, D_800A38B0, D_800A372C,
    D_800A38B8, D_800A35D4, D_800A38E0, D_800A3A94;
extern s16 D_800A3910, D_800A35A4;
extern u8 D_800A8AFC[], D_800A8B14[], D_800A8B2C[];
extern POLY_FT4 D_800A8B44[], D_800A8B6C[];
typedef struct TextureInfo {
    u16 tpx;
    u16 tpy;
    u16 clutX;
    u16 clutY;
    u16 u;
    u16 v;
    u16 u2;
    u16 v2;
    u16 u3;
    u16 v3;
} TextureInfo;
extern TextureInfo D_80090F96[];
extern u8 D_800A8B50[], D_800A8B51[], D_800A8B58[], D_800A8B59[];
extern u8 D_800A8B60[], D_800A8B61[], D_800A8B68[], D_800A8B69[];
extern u8 D_800A8B78[], D_800A8B79[], D_800A8B80[], D_800A8B81[];
extern u8 D_800A8B88[], D_800A8B89[], D_800A8B90[], D_800A8B91[];
extern u16 D_800A8B52[], D_800A8B7A[], D_800A8B5A[], D_800A8B82[];
extern s16 D_800A8AEC[], D_800A8AEE[], D_800A8AF0[], D_800A8AF2[];
extern s16 D_800A8AF4[], D_800A8AF6[], D_800A8AF8[], D_800A8AFA[];

void func_800511E4(void) {
    u16 x;
    u16 y;

    D_800A34D4 = 0x50;
    D_800A3910 = -1;
    D_800A39F8 = 0;
    D_800A3764 = 0;
    D_800A38B0 = 0;
    D_800A372C = 0;
    D_800A38B8 = 0;
    D_800A35D4 = 0;
    D_800A38E0 = 1;
    D_800A3A94 = 1;
    D_800A35A4 = 0;
    SetPolyF4(D_800A8AFC);
    SetPolyF4(D_800A8B14);
    SetPolyF4(D_800A8B2C);
    SetPolyFT4(D_800A8B44);
    SetPolyFT4(D_800A8B6C);
    SetShadeTex(D_800A8B44, 1);
    SetShadeTex(D_800A8B6C, 1);
    D_800A8B5A[0] = GetTPage(0, 0, D_80090F96[0].tpx, D_80090F96[0].tpy);
    D_800A8B82[0] = GetTPage(0, 0, D_80090F96[0].tpx, D_80090F96[0].tpy);
    D_800A8B52[0] = GetClut(D_80090F96[0].clutX, D_80090F96[0].clutY);
    D_800A8B7A[0] = GetClut(D_80090F96[0].clutX, D_80090F96[0].clutY);
    x = D_80090F96[0].u;
    y = D_80090F96[0].v;
    D_800A8B50[0] = x;
    D_800A8B51[0] = y;
    D_800A8B59[0] = y;
    D_800A8B58[0] = x + 0x20;
    D_800A8B60[0] = x;
    D_800A8B61[0] = y + 0x18;
    D_800A8B68[0] = x + 0x20;
    D_800A8B69[0] = y + 0x18;
    D_800A8B78[0] = x;
    D_800A8B79[0] = y;
    D_800A8B80[0] = x + 0x20;
    D_800A8B81[0] = y;
    D_800A8B88[0] = x;
    D_800A8B89[0] = y + 0x18;
    D_800A8B90[0] = x + 0x20;
    D_800A8B91[0] = y + 0x18;
    D_800A8AEC[0] =
        (MathMultiplyFixed16(0x2D0000, *(s32 *)((u8 *)D_800A3A24[2] + 0x600)) >>
         0x10) +
        0x122;
    D_800A8AEE[0] =
        (MathMultiplyFixed16(0x2D0000, *(s32 *)((u8 *)D_800A3A24[4] + 0x600)) >>
         0x10) +
        0x3C;
    D_800A8AF0[0] =
        (MathMultiplyFixed16(0x140000, *(s32 *)((u8 *)D_800A3A24[2] + 0x600)) >>
         0x10) +
        0x122;
    D_800A8AF2[0] =
        (MathMultiplyFixed16(0x140000, *(s32 *)((u8 *)D_800A3A24[4] + 0x600)) >>
         0x10) +
        0x3C;
    D_800A8AF4[0] =
        (MathMultiplyFixed16(0x2D0000, *(s32 *)((u8 *)D_800A3A24[2] + 0xA00)) >>
         0x10) +
        0x122;
    D_800A8AF6[0] =
        (MathMultiplyFixed16(0x2D0000, *(s32 *)((u8 *)D_800A3A24[4] + 0xA00)) >>
         0x10) +
        0x3C;
    D_800A8AF8[0] =
        (MathMultiplyFixed16(0x140000, *(s32 *)((u8 *)D_800A3A24[2] + 0xA00)) >>
         0x10) +
        0x122;
    D_800A8AFA[0] =
        (MathMultiplyFixed16(0x140000, *(s32 *)((u8 *)D_800A3A24[4] + 0xA00)) >>
         0x10) +
        0x3C;
}

extern s8 D_800A34CC;
extern s8 D_800A34CD;
extern s8 D_800A34CE;
extern s8 D_800A34CF;
extern s8 D_800A34D0;
extern s8 D_800A34D1;
extern u8 D_800A8B00[];
extern u8 D_800A8B01[];
extern u8 D_800A8B02[];

void func_800514EC(u8 arg0, u8 arg1, u8 arg2) {
    D_800A34CC = arg0;
    D_800A34CD = arg1;
    D_800A34CE = arg2;
    if (arg0 >= 0x40) {
        D_800A34CF = arg0 - 0x40;
    } else {
        D_800A34CF = 0;
    }
    if (arg1 >= 0x40) {
        D_800A34D0 = arg1 - 0x40;
    } else {
        D_800A34D0 = 0;
    }
    if (arg2 >= 0x40) {
        D_800A34D1 = arg2 - 0x40;
    } else {
        D_800A34D1 = 0;
    }
    D_800A8B00[0] = arg0;
    D_800A8B01[0] = arg1;
    D_800A8B02[0] = arg2;
}

INCLUDE_ASM("asm/nonmatchings/scene", func_8005157C);

extern s16 D_800A34D8;
extern u8 D_800A34DC;
extern s32 D_800A2EA4Absolute[];
extern u8 D_800A8B18[];
extern u8 D_800A8B19[];
extern u8 D_800A8B1A[];
extern u8 D_800A8B30[];
extern u8 D_800A8B31[];
extern u8 D_800A8B32[];
extern u16 D_800A8B04[];
extern u16 D_800A8B0C[];
extern u16 D_800A8B0E[];
extern u16 D_800A8B10[];
extern u16 D_800A8B12[];
extern u16 D_800A8B1C[];
extern u16 D_800A8B1E[];
extern u16 D_800A8B20[];
extern u16 D_800A8B22[];
extern u16 D_800A8B24[];
extern u16 D_800A8B26[];
extern u16 D_800A8B28[];
extern u16 D_800A8B2A[];
extern u16 D_800A8B34[];
extern u16 D_800A8B36[];
extern u16 D_800A8B38[];
extern u16 D_800A8B3A[];
extern u16 D_800A8B3C[];
extern u16 D_800A8B3E[];
extern u16 D_800A8B40[];
extern u16 D_800A8B42[];
extern u16 D_800A8B4C[];
extern u16 D_800A8B5C[];
extern u16 D_800A8B5E[];
extern u16 D_800A8B64[];
extern u16 D_800A8B66[];
extern u16 D_800A8B74[];
extern u16 D_800A8B76[];
extern u16 D_800A8B7C[];
extern u16 D_800A8B7E[];
extern u16 D_800A8B84[];
extern u16 D_800A8B86[];
extern u16 D_800A8B8C[];
extern u16 D_800A8B8E[];
extern s32 D_8009937C[];
extern s32 D_80099380[];
extern s32 D_80099384[];
extern s32 D_80099394[];
extern s32 D_800993A4[];
extern s32 D_800993B4[];
extern s32 MathFixedDivide(s32 numerator, s32 denominator);
extern s32 D_800A2DF4Absolute[];
extern s32 D_800A2DF0Absolute[];
extern s32 gOrderingTableBankSmall[];
void SceneSkyFadeDraw(void) {
    extern s32 D_800A2F00wC[] asm("D_800A2F00");
    extern u8 *D_800A3A2CwC[] asm("D_800A3A2C");
    extern u8 *D_800A3A34wC[] asm("D_800A3A34");
    extern s32 D_800A2DF4Absolute[];
    extern s32 D_800A2DF0Absolute[];
    extern s32 gOrderingTableBankSmall[];

    extern u8 *D_800A3A34Next[] asm("D_800A3A34.NON_MATCHING");

    /* The homes follow the observed stack offsets. The tail is compiler storage. */
    struct {
        s16 buf[8];
        u16 fadeVal;
        u8 reserved12[6];
        s32 entryA;
        s32 reserved1C;
        s32 entryB;
        u8 reserved24[20];
    } home;
    typedef char SkyFadeHomesSizeCheck[(sizeof(home) == 0x38) ? 1 : -1];
    register s32 argument asm("$4");
    register s32 result asm("$2");
    register s32 byteValue asm("$3");
    register s32 factor asm("$5");
    register s32 idx asm("$16");
    register s32 shade asm("$17");
    register u8 switched asm("$19");
    s32 gradA;
    s32 gradB;
    register s32 yBase asm("$23");
    s32 yStep;
    s32 m;
    s32 bank;

    /* shortcut: these pins require the qualified PSX compiler. Replace them
     * when a pure C form produces the same bytes. */
    switched = 0;
    /* The two fade directions use mirrored colors and screen offsets. */
    if (D_800A34DC != 0) {
        {
            u8 *table;
            s32 level;

            result = D_800A34D8;
            level = result;
            asm("" : "=r"(level) : "0"(level));

            if (result >= 0x259) {
                result = 0x500 - level;
                home.fadeVal = result;
                result += 0x200;
                idx = result & 0x3FF;
                shade = 0x140000;
                D_800A8B30[0] = 0x10;
                D_800A8B31[0] = 0x10;
                D_800A8B32[0] = 0x10;
                D_800A8B00[0] = D_800A34CC;
                D_800A8B01[0] = D_800A34CD;
                D_800A8B02[0] = D_800A34CE;
                D_800A8B18[0] = D_800A34CF;
                D_800A8B19[0] = D_800A34D0;
                D_800A8B1A[0] = D_800A34D1;
                switched = 1;
            } else {
                result = level + 0x200;
                idx = result & 0x3FF;
                shade = 0xFFEC0000;
            }
            result = (u8)D_800A34D4;
            argument = D_800A34D8;
            asm("" : "=r"(result) : "0"(result), "r"(argument));
            result = (s8)result;
            yBase = result + 0x122;
            result = 0x280 - argument;
            yStep = 0x3C;
            if (result >= 0) {
                table = D_800A3A34wC[0];
            } else {
                table = D_800A3A34wC[0];
                result = argument - 0x280;
            }
            result <<= 4;
            table += result;
            asm("" : "=r"(table) : "0"(table));
            argument = *(s32 *)table;
        }
        result = MathMultiplyFixed16(argument, 0x80000);
        {
            u8 *table;

            argument = D_800A34D8;
            byteValue = 0x2D0000;
            gradA = result + byteValue;
            result = 0x280 - argument;
            if (result >= 0) {
                result <<= 4;
                table = D_800A3A34wC[0];
            } else {
                table = D_800A3A34wC[0];
                result = (argument - 0x280) << 4;
            }
            asm("" : "=r"(table) : "0"(table), "r"(result));
            table += result;
            asm("" : "=r"(table) : "0"(table));
            argument = *(s32 *)table;
        }
        result = MathMultiplyFixed16(argument, 0x40000);
        byteValue = 0x140000;
        gradB = result + byteValue;
        result = switched & 0xFF;
        if (result != 0) {
            D_800A34D8 -= 8;
        } else {
            D_800A34D8 -= 0x10;
        }
        result = D_800A34D8;
        if (result < 0x181) {
            D_800A34D8 = 0x180;
            D_800A34DC = 0;
        }
    } else {
        {
            s32 level;
            u8 topRed, topGreen, topBlue;
            u8 bottomRed, bottomGreen, bottomBlue;
            result = D_800A34D8;
            level = result;
            asm("" : "=r"(level) : "0"(level));
            if (result < 0x1A8) {
                result = 0x300 - level;
                home.fadeVal = result;
                result += 0x200;
                idx = result & 0x3FF;
                topRed = D_800A34CF;
                topGreen = D_800A34D0;
                topBlue = D_800A34D1;
                bottomRed = D_800A34CC;
                bottomGreen = D_800A34CD;
                bottomBlue = D_800A34CE;
                shade = 0xFFEC0000;
                D_800A8B30[0] = 0;
                D_800A8B31[0] = 0;
                D_800A8B32[0] = 0;
                D_800A8B00[0] = topRed;
                D_800A8B01[0] = topGreen;
                D_800A8B02[0] = topBlue;
                D_800A8B18[0] = bottomRed;
                D_800A8B19[0] = bottomGreen;
                D_800A8B1A[0] = bottomBlue;
                switched = 1;
            } else {
                result = level + 0x200;
                idx = result & 0x3FF;
                shade = 0x140000;
            }
            result = D_800A34D8;
            factor = 0x80000;
            asm("" : "=r"(result), "=r"(factor) : "0"(result), "1"(factor));
            argument = (s32)D_800A3A34wC[0];
            byteValue = (u8)D_800A34D4;
            asm(""
                : "=r"(argument), "=r"(byteValue)
                : "0"(argument), "1"(byteValue));
            result -= 0x180;
            result <<= 4;
            result += argument;
            argument = *(s32 *)result;
            byteValue = (s8)byteValue;
            yBase = byteValue + 0x122;
        }
        result = MathMultiplyFixed16(argument, factor);
        {
            asm volatile("" : : : "fp");
            byteValue = D_800A34D8;
            argument = (s32)D_800A3A34Next[0];
            asm(""
                : "=r"(byteValue), "=r"(argument)
                : "0"(byteValue), "1"(argument), "r"(result));
            yStep = 0x3C;
            asm(""
                : "=r"(yStep)
                : "0"(yStep), "r"(byteValue), "r"(argument), "r"(result));
            byteValue -= 0x180;
            byteValue <<= 4;
            byteValue += argument;
            argument = *(s32 *)byteValue;
            factor = 0x40000;
            byteValue = 0x2D0000;
            asm(""
                : "=r"(factor), "=r"(byteValue)
                : "0"(factor), "1"(byteValue), "r"(argument), "r"(result));
            gradA = result + byteValue;
            result = MathMultiplyFixed16(argument, factor);
        }
        byteValue = 0x140000;
        gradB = result + byteValue;
        result = switched & 0xFF;
        if (result != 0) {
            D_800A34D8 += 8;
        } else {
            D_800A34D8 += 0x10;
        }
        result = D_800A34D8;
        if (result >= 0x280) {
            D_800A34D8 = 0x280;
            D_800A34DC = 1;
        }
    }
    factor = D_800A34D8;
    byteValue = (s32)D_800A3A2CwC[0];
    argument = (s32)D_800A3A34wC[0];
    result = factor << 2;
    byteValue = result + byteValue;
    byteValue = *(s32 *)byteValue;
    result += argument;
    home.entryA = byteValue;
    result = *(s32 *)result;
    home.entryB = result;
    result = factor - 0x200;
    if (result >= 0) {
        result = 0x380;
        argument = result - factor;
    } else {
        argument = factor - 0x80;
    }
    result = MathFixedDivide(argument, 0x180);
    shade = MathMultiplyFixed16(shade, result);
    {
        register s32 t2 asm("$18");
        register u16 *primitive asm("$20");
        if (D_800A2F00wC[0] == 0) {
            result = MathMultiplyFixed16(gradA, home.entryA);
            argument = gradA;
            factor = home.entryB;
            primitive = D_800A8B4C;
            asm(""
                : "=r"(factor), "=r"(primitive)
                : "0"(factor), "1"(primitive), "r"(argument), "r"(result));
            primitive[0] = yBase + (result >> 16);
            result = MathMultiplyFixed16(argument, factor);
            factor = home.entryA;
            argument = gradB;
            primitive[1] = yStep + (result >> 16);
            result = MathMultiplyFixed16(argument, factor);
            factor = home.entryB;
            argument = gradB;
            primitive[4] = yBase + (result >> 16);
            result = MathMultiplyFixed16(argument, factor);
            {
                s32 tableAddress;
                tableAddress = (s32)D_800A3A34wC[0];
                result = yStep + (result >> 16);
                idx <<= 2;
                primitive[5] = result;
                /* Preserve the retail operand order of this commutative add. */
                asm("addu %0,%1,%0"
                    : "=r"(tableAddress)
                    : "r"(idx), "0"(tableAddress), "m"(primitive[5]));
                argument = *(s32 *)tableAddress;
            }
            result = MathMultiplyFixed16(argument, shade);
            {
                s32 tableAddress;
                tableAddress = (s32)D_800A3A2CwC[0];
                idx += tableAddress;
                argument = *(s32 *)idx;
                factor = shade;
            }
            t2 = result >> 16;
            m = MathMultiplyFixed16(argument, factor);
            shade = m >> 16;
            result = switched & 0xFF;
            {
                register s32 xShift asm("$7");
                xShift = t2 << 24;
                if (result != 0) {
                    u16 *secondPrimitive;
                    {
                        register s32 paletteOffset asm("a1");
                        register s32 screenShift asm("a0");
                        s32 value;
                        register u32 fade asm("t4");
                        paletteOffset = D_800A34DC;
                        screenShift = (u8)D_800A34D4;
                        paletteOffset <<= 3;
                        value = *(u16 *)((u8 *)D_800A8AEC + paletteOffset);
                        secondPrimitive = D_800A8B74;
                        screenShift <<= 24;
                        result = (s32)screenShift >> 24;
                        value += result;
                        secondPrimitive[0] = value;
                        D_800A8B5C[0] = value;
                        result = *(u16 *)((u8 *)D_800A8AEE + paletteOffset);
                        D_800A8B76[0] = result;
                        D_800A8B5E[0] = result;
                        result = *(u16 *)((u8 *)D_800A8AF0 + paletteOffset);
                        fade = home.fadeVal;
                        asm(""
                            : "=r"(screenShift), "=r"(fade)
                            : "0"(screenShift), "1"(fade));
                        screenShift >>= 24;
                        result += screenShift;
                        D_800A8B7C[0] = result;
                        D_800A8B64[0] = result;
                        result = (s32)D_800A3A2CwC[0];
                        value = *(u16 *)((u8 *)D_800A8AF2 + paletteOffset);
                        idx = (s32)(fade << 16) >> 14;
                        asm("" : : "r"(fade));
                        result = idx + result;
                        D_800A8B7E[0] = value;
                        D_800A8B66[0] = value;
                        factor = *(s32 *)result;
                    }
                    result = MathMultiplyFixed16(gradA, factor);
                    {
                        register s32 table asm("v1");
                        asm("" : "=r"(t2) : "0"(t2), "r"(result));
                        t2 <<= 24;
                        argument = t2 >> 24;
                        asm(""
                            : "=r"(t2), "=r"(argument)
                            : "0"(t2), "1"(argument));
                        table = (s32)D_800A3A34wC[0];
                        result >>= 16;
                        result = yBase + result;
                        result -= argument;
                        D_800A8B84[0] = result;
                        table = idx + table;
                        factor = *(s32 *)table;
                    }
                    result = MathMultiplyFixed16(gradA, factor);
                    {
                        shade <<= 24;
                        byteValue = shade >> 24;
                        asm(""
                            : "=r"(shade), "=r"(byteValue)
                            : "0"(shade), "1"(byteValue));
                        argument = (s32)D_800A3A2CwC[0];
                        result >>= 16;
                        result = yStep + result;
                        byteValue += result;
                        D_800A8B86[0] = byteValue;
                        argument = idx + argument;
                        factor = *(s32 *)argument;
                    }
                    m = MathMultiplyFixed16(gradB, factor);
                    t2 >>= 24;
                    D_800A8B8C[0] = yBase + (m >> 16) - t2;
                    idx += (s32)D_800A3A34wC[0];
                    result = MathMultiplyFixed16(gradB, *(s32 *)idx);
                    shade >>= 24;
                    idx = (s32)primitive - 8;
                    result >>= 16;
                    result = yStep + result;
                    shade += result;
                    D_800A8B8E[0] = shade;
                    func_80017D80((u8 *)idx);
                    func_80017D80((u8 *)secondPrimitive - 8);
                    if (D_800A2EA4Absolute[0] != 0) {
                        D_800A2DF0Absolute[-63] = D_800A2DF4Absolute[-64] + 1;
                        D_800A3A3CAbsolute[-29] =
                            D_800A397CAbsolute[19] + 0x1004;
                        func_80017D80((u8 *)idx);
                        func_80017D80((u8 *)secondPrimitive - 8);
                        gOrderingTableBankSmall[0] =
                            gOrderingTableBankAbsolute[0] - 1;
                        D_800A3A34Absolute[-27] =
                            D_800A3A2CAbsolute[-25] - 0x1004;
                    }
                } else {
                    {
                        register s32 dx asm("t1");
                        s32 dy;
                        register s32 yBits asm("t0");
                        register u32 x0 asm("v0");
                        register u32 y0 asm("v1");
                        register u32 x1 asm("a1");
                        register u32 y1 asm("a2");
                        dx = xShift >> 24;
                        yBits = shade << 24;
                        dy = yBits >> 24;
                        asm(""
                            : "=r"(xShift), "=r"(yBits)
                            : "0"(xShift), "1"(yBits), "r"(dx), "r"(dy));
                        xShift >>= 24;
                        yBits >>= 24;
                        x0 = primitive[0];
                        y0 = primitive[1];
                        x1 = primitive[4];
                        y1 = primitive[5];
                        idx = (s32)primitive - 8;
                        D_800A8B5C[0] = x0 - dx;
                        D_800A8B5E[0] = y0 + dy;
                        D_800A8B64[0] = x1 - xShift;
                        D_800A8B66[0] = y1 + yBits;
                    }
                    argument = idx;
                    func_80017D80((u8 *)argument);
                    if (D_800A2EA4Absolute[0] != 0) {
                        D_800A2DF0Absolute[-63] = D_800A2DF4Absolute[-64] + 1;
                        D_800A3A3CAbsolute[-29] =
                            D_800A397CAbsolute[19] + 0x1004;
                        func_80017D80((u8 *)idx);
                        gOrderingTableBankSmall[0] =
                            gOrderingTableBankAbsolute[0] - 1;
                        D_800A3A34Absolute[-27] =
                            D_800A3A2CAbsolute[-25] - 0x1004;
                    }
                }
            }
        } else {
            result = MathMultiplyFixed16(gradA, home.entryA);
            argument = gradA;
            factor = home.entryB;
            primitive = D_800A8B04;
            asm(""
                : "=r"(factor), "=r"(primitive)
                : "0"(factor), "1"(primitive), "r"(argument), "r"(result));
            primitive[0] = yBase + (result >> 16);
            result = MathMultiplyFixed16(argument, factor);
            factor = home.entryA;
            argument = gradB;
            primitive[1] = yStep + (result >> 16);
            result = MathMultiplyFixed16(argument, factor);
            factor = home.entryB;
            argument = gradB;
            primitive[2] = yBase + (result >> 16);
            result = MathMultiplyFixed16(argument, factor);
            {
                s32 tableAddress;
                tableAddress = (s32)D_800A3A34wC[0];
                result = yStep + (result >> 16);
                idx <<= 2;
                primitive[3] = result;
                /* Preserve the retail operand order of this commutative add. */
                asm("addu %0,%1,%0"
                    : "=r"(tableAddress)
                    : "r"(idx), "0"(tableAddress), "m"(primitive[3]));
                argument = *(s32 *)tableAddress;
            }
            result = MathMultiplyFixed16(argument, shade);
            {
                s32 tableAddress;
                tableAddress = (s32)D_800A3A2CwC[0];
                idx += tableAddress;
                argument = *(s32 *)idx;
                factor = shade;
            }
            t2 = result >> 16;
            m = MathMultiplyFixed16(argument, factor);
            shade = m >> 16;
            result = switched & 0xFF;
            {
                register s32 xShift asm("$7");
                xShift = t2 << 24;
                if (result != 0) {
                    u16 *secondPrimitive;
                    {
                        register s32 paletteOffset asm("a1");
                        register s32 screenShift asm("a0");
                        s32 value;
                        register u32 fade asm("t4");
                        paletteOffset = D_800A34DC;
                        screenShift = (u8)D_800A34D4;
                        paletteOffset <<= 3;
                        value = *(u16 *)((u8 *)D_800A8AEC + paletteOffset);
                        secondPrimitive = D_800A8B1C;
                        screenShift <<= 24;
                        result = (s32)screenShift >> 24;
                        value += result;
                        secondPrimitive[0] = value;
                        D_800A8B0C[0] = value;
                        result = *(u16 *)((u8 *)D_800A8AEE + paletteOffset);
                        D_800A8B1E[0] = result;
                        D_800A8B0E[0] = result;
                        result = *(u16 *)((u8 *)D_800A8AF0 + paletteOffset);
                        fade = home.fadeVal;
                        asm(""
                            : "=r"(screenShift), "=r"(fade)
                            : "0"(screenShift), "1"(fade));
                        screenShift >>= 24;
                        result += screenShift;
                        D_800A8B20[0] = result;
                        D_800A8B10[0] = result;
                        result = (s32)D_800A3A2CwC[0];
                        value = *(u16 *)((u8 *)D_800A8AF2 + paletteOffset);
                        idx = (s32)(fade << 16) >> 14;
                        asm("" : : "r"(fade));
                        result = idx + result;
                        D_800A8B22[0] = value;
                        D_800A8B12[0] = value;
                        factor = *(s32 *)result;
                    }
                    result = MathMultiplyFixed16(gradA, factor);
                    {
                        register s32 table asm("v1");
                        asm("" : "=r"(t2) : "0"(t2), "r"(result));
                        t2 <<= 24;
                        argument = t2 >> 24;
                        asm(""
                            : "=r"(t2), "=r"(argument)
                            : "0"(t2), "1"(argument));
                        table = (s32)D_800A3A34wC[0];
                        result >>= 16;
                        result = yBase + result;
                        result -= argument;
                        D_800A8B24[0] = result;
                        table = idx + table;
                        factor = *(s32 *)table;
                    }
                    result = MathMultiplyFixed16(gradA, factor);
                    {
                        shade <<= 24;
                        byteValue = shade >> 24;
                        asm(""
                            : "=r"(shade), "=r"(byteValue)
                            : "0"(shade), "1"(byteValue));
                        argument = (s32)D_800A3A2CwC[0];
                        result >>= 16;
                        result = yStep + result;
                        byteValue += result;
                        D_800A8B26[0] = byteValue;
                        argument = idx + argument;
                        factor = *(s32 *)argument;
                    }
                    m = MathMultiplyFixed16(gradB, factor);
                    t2 >>= 24;
                    D_800A8B28[0] = yBase + (m >> 16) - t2;
                    idx += (s32)D_800A3A34wC[0];
                    result = MathMultiplyFixed16(gradB, *(s32 *)idx);
                    shade >>= 24;
                    idx = (s32)primitive - 8;
                    result >>= 16;
                    result = yStep + result;
                    shade += result;
                    D_800A8B2A[0] = shade;
                    func_80017D80((u8 *)idx);
                    func_80017D80((u8 *)secondPrimitive - 8);
                    if (D_800A2EA4Absolute[0] != 0) {
                        D_800A2DF0Absolute[-63] = D_800A2DF4Absolute[-64] + 1;
                        D_800A3A3CAbsolute[-29] =
                            D_800A397CAbsolute[19] + 0x1004;
                        func_80017D80((u8 *)idx);
                        func_80017D80((u8 *)secondPrimitive - 8);
                        gOrderingTableBankSmall[0] =
                            gOrderingTableBankAbsolute[0] - 1;
                        D_800A3A34Absolute[-27] =
                            D_800A3A2CAbsolute[-25] - 0x1004;
                    }
                } else {
                    {
                        register s32 dx asm("t1");
                        s32 dy;
                        register s32 yBits asm("t0");
                        register u32 x0 asm("v0");
                        register u32 y0 asm("v1");
                        register u32 x1 asm("a1");
                        register u32 y1 asm("a2");
                        dx = xShift >> 24;
                        yBits = shade << 24;
                        dy = yBits >> 24;
                        asm(""
                            : "=r"(xShift), "=r"(yBits)
                            : "0"(xShift), "1"(yBits), "r"(dx), "r"(dy));
                        xShift >>= 24;
                        yBits >>= 24;
                        x0 = primitive[0];
                        y0 = primitive[1];
                        x1 = primitive[2];
                        y1 = primitive[3];
                        idx = (s32)primitive - 8;
                        argument = idx;
                        D_800A8B0C[0] = x0 - dx;
                        D_800A8B0E[0] = y0 + dy;
                        D_800A8B10[0] = x1 - xShift;
                        D_800A8B12[0] = y1 + yBits;
                    }
                    func_80017D80((u8 *)argument);
                    if (D_800A2EA4Absolute[0] != 0) {
                        D_800A2DF0Absolute[-63] = D_800A2DF4Absolute[-64] + 1;
                        D_800A3A3CAbsolute[-29] =
                            D_800A397CAbsolute[19] + 0x1004;
                        func_80017D80((u8 *)idx);
                        gOrderingTableBankSmall[0] =
                            gOrderingTableBankAbsolute[0] - 1;
                        D_800A3A34Absolute[-27] =
                            D_800A3A2CAbsolute[-25] - 0x1004;
                    }
                }
            }
        }
    }
    {
        /* Rotate the four sky corners around the screen origin. */
        s32 loopI;
        register s32 signedI asm("s1");
        register s32 lookupOffset asm("s2");
        s16 *buf;
        register s32 accum asm("s0");
        s32 argA;
        s32 argB;
        register s32 scratch0 asm("v0");
        register s32 scratch1 asm("v1");
        s32 callOut;
        s32 nextI;
        loopI = 0;
        D_800993B4[0] = gradB;
        D_800993A4[0] = gradB;
        D_80099394[0] = gradB;
        D_80099384[0] = gradB;
    gradLoop:
        scratch0 = D_800A34DC;
        signedI = (s8)loopI;
        lookupOffset = signedI << 3;
        argA = home.entryA;
        scratch0 <<= 5;
        scratch0 = lookupOffset + scratch0;
        argB = *(s32 *)((u8 *)D_8009937C + scratch0);
        signedI <<= 2;
        callOut = MathMultiplyFixed16(argA, argB);
        scratch1 = D_800A34DC;
        argA = home.entryB;
        scratch1 <<= 5;
        scratch1 = lookupOffset + scratch1;
        argB = *(s32 *)((u8 *)D_80099380 + scratch1);
        accum = callOut;
        callOut = MathMultiplyFixed16(argA, argB);
        buf = (s16 *)((u8 *)home.buf + signedI);
        asm(""
            : "=r"(buf), "=r"(accum)
            : "0"(buf), "1"(accum), "r"(callOut)
            : "memory");
        scratch1 = D_800A34DC;
        accum -= callOut;
        accum >>= 16;
        accum = yBase + accum;
        buf[0] = accum;
        argA = home.entryB;
        scratch1 <<= 5;
        scratch1 = lookupOffset + scratch1;
        argB = *(s32 *)((u8 *)D_8009937C + scratch1);
        callOut = MathMultiplyFixed16(argA, argB);
        scratch1 = D_800A34DC;
        argA = home.entryA;
        scratch1 <<= 5;
        lookupOffset += scratch1;
        argB = *(s32 *)((u8 *)D_80099380 + lookupOffset);
        accum = callOut;
        callOut = MathMultiplyFixed16(argA, argB);
        nextI = loopI + 1;
        loopI = nextI;
        asm("" : "=r"(loopI) : "0"(loopI));
        accum += callOut;
        accum >>= 16;
        accum = yStep + accum;
        buf[1] = accum;
        if ((s8)nextI < 4)
            goto gradLoop;
    }
    D_800A8B34[0] = home.buf[0];
    D_800A8B36[0] = home.buf[1];
    D_800A8B38[0] = home.buf[2];
    D_800A8B3A[0] = home.buf[3];
    D_800A8B3C[0] = home.buf[4];
    D_800A8B3E[0] = home.buf[5];
    D_800A8B40[0] = home.buf[6];
    D_800A8B42[0] = home.buf[7];
    func_80017D80((u8 *)D_800A8B34 - 8);
    func_8001D778((s8)D_800A34D4 + 0xEB, 0x14, 0x46, 0x50, 0, 0, 0, 1);
    if (D_800A2EA4Absolute[0] != 0) {
        D_800A2DF0Absolute[-63] = D_800A2DF4Absolute[-64] + 1;
        D_800A3A3CAbsolute[-29] = D_800A397CAbsolute[19] + 0x1004;
        func_80017D80((u8 *)D_800A8B34 - 8);
        func_8001D778((s8)D_800A34D4 + 0xEB, 0x14, 0x46, 0x50, 0, 0, 0, 1);
        bank = gOrderingTableBankAbsolute[0] - 1;
        gOrderingTableBankSmall[0] = bank;
        D_800A3A34Absolute[-27] = D_800A3A2CAbsolute[-25] - 0x1004;
    }
}

extern s8 D_800A34E4;
extern s32 D_800A34F4;
extern u8 D_80090F7A[];

void func_800524A0(u8 *arg0, s8 arg1) {
    u8 *table;
    u8 *entry;
    u16 w;
    u32 v;
    s32 m2;

    arg0 += arg1 * 0x28 + 0x2AC;
    m2 = *(s16 *)(arg0 + 0x26);
    arg0[0x24] = 0;
    arg0[0x20] = 0;
    D_800A34E4 = 0;
    if (m2 != -1) {
        table = D_80090F7A;
        w = *(u16 *)(arg0 + 0x22);
        entry = (u8 *)D_800A34F4 + (m2 * 12 - m2) * 8;
        if (w == 2) {
            table += 0xE;
        }
        *(s16 *)(entry + 0x12) =
            GetClut(*(u16 *)(table + 4), *(u16 *)(table + 6));
        *(s16 *)(entry + 0x16) = GetTPage(
            *(u16 *)(table + 0xC), 0, *(u16 *)(table + 0), *(u16 *)(table + 2));
        v = table[8] + 0x3F;
        entry[0x14] = v;
        entry[0x10] = v;
        v = table[8];
        entry[0x1C] = v;
        entry[0x18] = v;
        v = table[0xA];
        entry[0x19] = v;
        entry[0x11] = v;
        v = table[0xA] + 0x1F;
        entry[0x1D] = v;
        entry[0x15] = v;
    }
}

extern s16 D_800A34E8;
extern s32 D_800BE980[];
extern s32 D_800AE844[];
extern s32 D_800A2EC0Absolute[];
extern u8 D_80090F5E[], D_80090F6C[], D_80090F88[];

#ifdef NON_MATCHING
/* 2026-10-11 w3f: frame hole decoded and fixed. Retail's frame is 0xa0 with
 * 8 dead bytes between `m` (0x38) and `rot` (0x60); the draft was 0x98 with
 * rot at 0x58. An unused local is dropped entirely, but an ADDRESS-TAKEN
 * local whose only reference sits inside `if (0)` keeps its stack slot:
 * parse sets TREE_ADDRESSABLE, expand_decl allocates the slot in decl
 * order, and the dead branch never expands, so the slot is silent.
 * `SVECTOR padRot;` between m and rot + the `if (0)` RotMatrix below
 * reproduces the hole and shifts every prologue/epilogue/rot/out/flag
 * offset back onto retail. Retry 2026-10-11 keeps the permuter pointer
 * assignment at the trail-node store: 151 differing bytes, size 0x870.
 * Remaining (83 words): a0/a1 swaps in the coords
 * loop, the E8->v1 / F4->a0 assignment swap, the 413d8 nop-vs-move s3,a1
 * slot, and the tail interleave (mfhi t1 vs t0, subu a3 vs v0). */
void func_800525A8(u8 *arg0, s8 arg1) {
    s32 new_var2;
    s16 coords[3][4];
    VECTOR vec;
    MATRIX m;
    SVECTOR padRot;
    s32 xoff;
    s32 d;
    SVECTOR rot;
    VECTOR out;
    long flag;
    u8 *entry;
    s32 diff;
    u8 *e;
    s32 m2;
    u16 w;
    u8 *tex;
    u8 *tex2;
    u8 *new_var;
    u8 *q;
    u8 *p;
    u16 *new_var3;
    u32 v;
    s8 side1;
    s8 side2;
    u8 *new_var4;
    s32 *ref;
    s8 i;
    s8 j;
    SceneTexture *tim;
    u8 u;
    u8 uv;
    u8 *node;

    s32 w2;
    s32 n;

    diff = *(u16 *)(arg0 + 0x104) - *(u16 *)(arg0 + 0x114);
    entry = arg0 + (arg1 * 0x28 + 0x2AC);
    if (*(u16 *)(arg0 + 0x362) == 0 || *(u16 *)(arg0 + 0x364) == 0 ||
        *(u16 *)(arg0 + 0x366) == 0 || *(u16 *)(arg0 + 0x368) == 0) {
        for (i = 0; i < 4; i++) {
            if (arg0[i * 0x28 + 0x2CC] != 0) {
                e = arg0 + (i * 0x28 + 0x2AC);
                m2 = *(s16 *)(e + 0x26);
                e[0x24] = 0;
                e[0x20] = 0;
                D_800A34E4 = 0;
                if (m2 != -1) {
                    d = (s32)D_80090F7A;
                    p = (u8 *)d + 0xA;
                    asm("" : "=r"(q) : "0"((u8 *)d));
                    tex = (u8 *)D_800A34F4 + (m2 * 12 - m2) * 8;
                    w = *(u16 *)(e + 0x22);
                    if (w == 2) {
                        p = q + 0x18;
                        q += 0xE;
                    }
                    *(s16 *)(tex + 0x12) =
                        GetClut(*(u16 *)(p - 6), *(u16 *)(p - 4));
                    *(s16 *)(tex + 0x16) = GetTPage(*(u16 *)(p + 2), 0,
                                                    *(u16 *)q, *(u16 *)(p - 8));
                    v = p[-2] + 0x3F;
                    tex[0x14] = v;
                    tex[0x10] = v;
                    v = p[-2];
                    tex[0x1C] = v;
                    tex[0x18] = v;
                    v = p[0];
                    tex[0x19] = v;
                    tex[0x11] = v;
                    v = p[0] + 0x1F;
                    tex[0x1D] = v;
                    tex[0x15] = v;
                }
            }
        }
        return;
    }
    if (arg1 == 0) {
        if (entry[0x20] == 0 && *(s16 *)(arg0 + 0x20E) != 0 &&
            D_800A34E4 == 0) {
            if (*(s16 *)(arg0 + 0x20E) > 0) {
                D_800A34E4 = 1;
            }
            if (*(s16 *)(arg0 + 0x20E) < 0) {
                D_800A34E4 = -1;
            }
        } else {
            D_800A34E4 = 0;
        }
    }
    switch (arg1) {
    case 2:
        d = (s16)diff;
        if (d < 0) {
            d = -d;
        }
        side2 = 1;
        if (d < 0x40) {
            arg0[0x31C] = 0;
            return;
        }
        side1 = 1;
        break;
    case 3:
        d = (s16)diff;
        if (d < 0) {
            d = -d;
        }
        side1 = 1;
        if (d < 0x40) {
            arg0[0x344] = 0;
            return;
        }
        side2 = -1;
        break;
    case 0:
        if (D_800A34E4 < 0) {
            return;
        }
        side1 = -1;
        side2 = 1;
        break;
    case 1:
        if (D_800A34E4 > 0) {
            return;
        }
        side2 = -1;
        side1 = -1;
        break;
    default:
        return;
    }
    rot.vx = 0;
    rot.vy = diff * 4;
    rot.vz = 0;
    RotMatrix(&rot, &m);
    SetRotMatrix(&m);
    if (0) {
        RotMatrix(&padRot, &m);
    }
    i = 0;
    xoff = side1 * 220;
    ref = D_800AE844;
loop2:
    if (i == 0) {
        rot.vx = 0x28;
    } else {
        rot.vx = -0x28;
    }
    rot.vy = 0;
    rot.vz = 0;
    RotTrans(&rot, &out, &flag);
    vec.vx = xoff + out.vz;
    vec.vy = side2 * 120 + out.vx;
    vec.vz = 0;
    func_8001ED84((s32 *)&vec);
    coords[0][i] = ((*(s32 *)(arg0 + 0) + vec.vx) >> 2) - ref[0];
    coords[1][i] = ((*(s32 *)(arg0 + 4) + vec.vy) >> 2) - ref[1];
    coords[2][i] = ((*(s32 *)(arg0 + 8) + vec.vz) >> 2) - ref[2];
    i++;
    if (i < 2) {
        goto loop2;
    }
    if (entry[0x20] == 0) {
        *(u16 *)(entry + 0x10) = coords[0][0];
        *(u16 *)(entry + 0x12) = coords[1][0];
        *(u16 *)(entry + 0x14) = coords[2][0];
        *(u16 *)(entry + 0x16) = coords[0][1];
        *(u16 *)(entry + 0x18) = coords[1][1];
        *(u16 *)(entry + 0x1A) = coords[2][1];
        entry[0x20] = 1;
    } else {
        tex2 = (u8 *)D_800A34F4 + (D_800A34E8 * 12 - D_800A34E8) * 8;
        *(u16 *)(tex2 + 0x44) = *(u16 *)(entry + 0x10);
        *(u16 *)(tex2 + 0x46) = *(u16 *)(entry + 0x12);
        *(u16 *)(tex2 + 0x48) = *(u16 *)(entry + 0x14);
        w = coords[0][0];
        *(new_var3 = (u16 *)(entry + 0x10)) = w;
        *(u16 *)(tex2 + 0x34) = w;
        w = coords[1][0];
        *(u16 *)(entry + 0x12) = w;
        *(u16 *)(tex2 + 0x36) = w;
        w = coords[2][0];
        *(u16 *)(entry + 0x14) = w;
        *(u16 *)(tex2 + 0x38) = w;
        *(u16 *)(tex2 + 0x4C) = *(u16 *)(entry + 0x16);
        *(u16 *)(tex2 + 0x4E) = *(u16 *)(entry + 0x18);
        *(u16 *)(tex2 + 0x50) = *(u16 *)(entry + 0x1A);
        w = coords[0][1];
        *(u16 *)(entry + 0x16) = w;
        *(u16 *)(tex2 + 0x3C) = w;
        w = coords[1][1];
        *(u16 *)(entry + 0x18) = w;
        *(u16 *)(tex2 + 0x3E) = w;
        w = (*(u16 *)(entry + 0x1A) = coords[2][1]);
        *(u16 *)(tex2 + 0x40) = w;
        if (*(s16 *)tex2 != -1) {
            node = *(u8 **)((u8 *)D_800BE980[0] + *(s16 *)tex2 * 0x90 + 0x74);
            if (*(u8 **)(node + 0x54) == 0) {
                *(u8 **)((u8 *)D_800BE980[0] + *(s16 *)tex2 * 0x90 + 0x74) = 0;
            } else {
                while (*(u8 **)(*(u8 **)(node + 0x54) + 0x54) != 0) {
                    node = *(u8 **)(node + 0x54);
                }
                *(u8 **)(node + 0x54) = 0;
            }
        }
        tex2 = (u8 *)D_800A34F4 + (D_800A34E8 * 12 - D_800A34E8) * 8;
        n = *(u16 *)(arg0 + 0x1E0);
        new_var = (u8 *)D_800A34F4;
        *(u16 *)(new_var4 = tex2) = n;
        *(u8 **)(tex2 + 0x54) =
            *(u8 **)((u8 *)D_800BE980[0] + (s16)n * 0x90 + 0x74);
        *(u8 **)((u8 *)D_800BE980[0] + (s16)n * 0x90 + 0x74) = tex2;
        if (*(u16 *)(entry + 0x22) == 2) {
            if (entry[0x24] != 0) {
                tim = (SceneTexture *)D_80090F6C;
            } else {
                tim = (SceneTexture *)D_80090F88;
                entry[0x24] = 1;
            }
        } else {
            if (entry[0x24] != 0) {
                tim = (SceneTexture *)D_80090F5E;
            } else {
                tim = (SceneTexture *)D_80090F7A;
                entry[0x24] = 1;
            }
        }
        tex2 =
            (new_var4 = (u8 *)D_800A34F4 + (D_800A34E8 * 12 - D_800A34E8) * 8);
        *(s16 *)(tex2 + 0x12) = GetClut(tim->clutX, tim->clutY);
        *(s16 *)(tex2 + 0x16) = GetTPage(tim->tpage, 0, tim->tpx, tim->tpy);
        u = tim->u;
        tex2[0x14] = u;
        tex2[0x10] = u;
        u = tim->u + 0x3F;
        tex2[0x1C] = u;
        tex2[(new_var2 = 0x18)] = u;
        uv = tim->v + 0x1F;
        tex2[0x19] = uv;
        tex2[0x11] = uv;
        uv = tim->v;
        tex2[0x1D] = uv;
        tex2[0x15] = uv;
        asm("" : "=r"(w) : "0"((u16)D_800A34E8));
        w2 = (s16)w;
        tex2 = new_var + (w2 * 12 - w2) * 8;
        *(u16 *)(entry + 0x26) = w;
        n = (s16)(w + 1);
        *(s32 *)(tex2 + 4) = D_800A2EC0Absolute[0];
        new_var4 = (arg0 + arg1 * 0x28) + 0x2B4;
        *(s32 *)(arg0 + arg1 * 0x28 + 0x2B8) -= (0x12C - *(s16 *)new_var4) >> 3;
        D_800A34E8 = n % 100;
    }
    switch (arg1) {
    case 2:
        *(u16 *)(entry + 0x22) = *(u16 *)(arg0 + 0x362);
        break;
    case 3:
        *(u16 *)(entry + 0x22) = *(u16 *)(arg0 + 0x364);
        break;
    case 0:
        *(u16 *)(entry + 0x22) = *(u16 *)(arg0 + 0x366);
        break;
    case 1:
        *(u16 *)(entry + 0x22) = *(u16 *)(arg0 + 0x368);
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/scene", func_800525A8);
#endif

extern s16 D_800A34E8;
extern s8 D_800A34EC;
extern s8 D_800A34F0;
extern s32 D_800A34F4;
extern s32 D_800BE974[];
extern s32 D_800BE980[];
extern u8 *D_800A3878NM[] asm("D_800A3878.NON_MATCHING");

void func_80052E18(void) {
    s16 i;
    u8 *elem;
    u8 *poly;
    u8 *p;
    u8 *entry;

    D_800A34E8 = 0;
    D_800A34F0 = 0;
    D_800A34EC = 0;
    D_800A34F4 = (s32)HeapAlloc(0x2260);
    i = 0;
    do {
        elem = (u8 *)D_800A34F4 + i * 0x58;
        poly = elem + 8;
        SetPolyFT4((POLY_FT4 *)poly);
        SetSemiTrans(poly, 1);
        SetShadeTex(poly, 1);
        elem[9] = 0x10;
        *(u32 *)(elem + 0x20) = (u32)(elem + 0x34);
        *(u32 *)(elem + 0x24) = (u32)(elem + 0x3C);
        *(u32 *)(elem + 0x28) = (u32)(elem + 0x4C);
        *(u32 *)(elem + 0x2C) = (u32)(elem + 0x44);
        elem[0xA] = 0xD;
        *(s32 *)(elem + 0x30) = 0;
        *(s16 *)elem = -1;
        i++;
    } while (i < 100);
    i = 0;
    while (i < D_800BE974[0]) {
        *(s32 *)((u8 *)D_800BE980[0] + i * 0x90 + 0x74) = 0;
        i++;
    }
    p = D_800A3878NM[0];
    while (p != 0) {
        for (i = 0; i < 4; i++) {
            entry = p + i * 0x28;
            *(s16 *)(entry + 0x2D2) = -1;
            entry[0x2D0] = 0;
            entry[0x2CC] = 0;
        }
        p[0x3B9] = 0;
        p = *(u8 **)(p + 0x3E0);
    }
}

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

extern void func_8003FC0C(s32, s32, s32);

void func_8005301C(void) {
    u8 *obj;

    if (D_800A2F9Dw15[0] == 0) {
        return;
    }
    obj = D_800A3554[0];
    if (*(s8 *)(obj + 0x3B9) != 0) {
        func_8003FC0C(
            0x14, (s8)(*(s16 *)(obj + 0x92) * 8 / *(s16 *)(obj + 0x9A) + 0x2C),
            0);
        if (*(u8 *)&D_800A34EC == 0) {
            func_8003F564(0x14, 2);
            D_800A34EC = 1;
        }
    } else if (*(u8 *)&D_800A34EC != 0) {
        func_8003F914(0x14);
        D_800A34EC = 0;
    }
    if (D_800A2EA4Absolute[0] == 0) {
        return;
    }
    obj = *(u8 **)(D_800A3554[0] + 0x3E0);
    if (*(s8 *)(obj + 0x3B9) != 0) {
        func_8003FC0C(
            0x15, (s8)(*(s16 *)(obj + 0x92) * 8 / *(s16 *)(obj + 0x9A) + 0x2C),
            0);
        if (*(u8 *)&D_800A34F0 == 0) {
            func_8003F564(0x15, 2);
            D_800A34F0 = 1;
        }
    } else if (*(u8 *)&D_800A34F0 != 0) {
        func_8003F914(0x15);
        D_800A34F0 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/scene", func_800531B8);

INCLUDE_ASM("asm/nonmatchings/scene", func_800535A0);

extern void func_8005E550(s32);
extern void func_80057AE4(void);
extern void func_80057A9C(void);
extern void func_8005A4E0(void);
extern void func_8005A544(u8, u8);
extern void func_8005A804(u8, u8, u8);
extern void func_80059648(void);
extern void func_800631B4(void);
extern void func_80063E7C(void);
extern void func_80064174(void);
extern void func_80069744(void);
extern void *func_80058094(s32, void **, s32);
extern s32 D_800A37EC;
extern u8 D_800A3724NM asm("D_800A3724.NON_MATCHING");
extern u8 D_800A305ANM asm("D_800A305A.NON_MATCHING");
extern s32 D_800A37F0NM asm("D_800A37F0.NON_MATCHING");
extern s32 D_800A3830NM asm("D_800A3830.NON_MATCHING");

void func_800539F0(void) {
    void *table;
    u8 i;
    void *base;

    D_800A37EC = (s32)HeapAlloc(0x26000);
    func_8003CA18(D_800A37EC, 5);
    func_8005E550(6);
    func_80057AE4();
    i = 0;
    func_800631B4();
    func_80063E7C();
    func_80057A9C();
    func_8005A4E0();
    base = func_80058094(9, &table, 0);
    TextureLoadTim(base + ((s32 *)table)[0xB]);
    DrawSync(0);
    TextureLoadTim(base + ((s32 *)table)[6]);
    DrawSync(0);
    TextureLoadTim(base + ((s32 *)table)[0xA]);
    DrawSync(0);
    while (i < 5) {
        TextureLoadTim(base + ((s32 *)table)[i + 1]);
        DrawSync(0);
        i++;
    }
    i = 0;
    TextureLoadTim(base + ((s32 *)table)[9]);
    DrawSync(0);
    while (i < 2) {
        TextureLoadTim(base + ((s32 *)table)[i + 7]);
        DrawSync(0);
        i++;
    }
    TextureLoadTim(base + ((s32 *)table)[0xC]);
    DrawSync(0);
    TextureLoadTim(base + ((s32 *)table)[0]);
    DrawSync(0);
    func_80059648();
    HeapFree(base);
    func_80064174();
    func_80069744();
    func_8005A544(0, 0);
    func_8005A544(1, 1);
    func_8005A544(2, 2);
    func_8005A804(0xA0, 0xA0, 0x40);
    D_800A3724NM = 3;
    D_800A305ANM = 0;
    D_800A37F0NM = 1;
    D_800A3830NM = 0;
}

extern u8 D_800A3608;

extern u8 D_800A39E4Small;
extern u8 D_800A3059;
void func_80053C00(s32 arg0, s32 arg1) {
    extern s32 D_800A3914[];
    extern s32 D_800A3914NM[] asm("D_800A3914.NON_MATCHING");
    extern void func_8006DCF0(void);
    extern void func_8005B688(u8 *, u8);
    extern void func_8005B8B8(u8 *, u8);
    extern void func_80064898(void);
    extern void func_800686FC(u8, u8);
    extern void func_8005D094(s32, u8, u8);
    extern s32 func_8005DCF0(void);

    if (D_800A39E4Small == 0xFC) {
        func_8006DCF0();
    } else {
        if (D_800A3914[0] != 0) {
            func_8005B688((u8 *)D_800A3914[0], 1);
        }
        if ((D_800A39E4Small >= 9 && D_800A39E4Small <= 10) ||
            D_800A39E4Small == 12 ||
            (D_800A39E4Small >= 16 && D_800A39E4Small <= 17)) {
            func_800686FC(D_800A39E4Small, arg0);
        } else if (D_800A39E4Small == 14) {
            func_8005B8B8((u8 *)D_800A3914NM[0], 0xFF);
            func_80064898();
        } else {
            func_8005B8B8((u8 *)D_800A3914NM[0], 0xFF);
            func_8005D094(D_800A39E4Small, D_800A3059, arg1);
        }
    }
    if (D_800A3608 != 0) {
        D_800A3608 = D_800A3608 - 1;
    } else if (!((D_800A39E4Small >= 16 && D_800A39E4Small <= 17) ||
                 D_800A39E4Small == 14) &&
               func_8005DCF0() == 1) {
        D_800A3608 = 0x78;
    }
}

__asm__("D_800A2F9C.MainLoop = D_800A2F9C\n"
        "D_800A3059.MainLoop = D_800A3059\n"
        "D_800A305A.MainLoop = D_800A305A\n"
        "D_800A305B.MainLoop = D_800A305B\n"
        "D_800A305C.MainLoop = D_800A305C\n"
        "D_800A3064.MainLoop = D_800A3064\n"
        "D_800A3065.MainLoop = D_800A3065\n"
        "D_800A3076.MainLoop = D_800A3076\n"
        "D_800A358C.MainLoop = D_800A358C\n"
        "D_800A35F0.MainLoop = D_800A35F0\n"
        "D_800A3608.MainLoop = D_800A3608\n"
        "D_800A3644.MainLoop = D_800A3644\n"
        "D_800A3690.MainLoop = D_800A3690\n"
        "D_800A36E0.MainLoop = D_800A36E0\n"
        "D_800A3710.MainLoop = D_800A3710\n"
        "D_800A3724.MainLoop = D_800A3724\n"
        "D_800A3808.MainLoop = D_800A3808\n"
        "D_800A3928.MainLoop = D_800A3928\n"
        "D_800A3950.MainLoop = D_800A3950\n"
        "D_800A3968.MainLoop = D_800A3968\n"
        "D_800A3980.MainLoop = D_800A3980\n"
        "D_800A39E4.MainLoop = D_800A39E4\n"
        "D_800B9B84.MainLoop = D_800B9B84\n"
        "D_800A3684.MainLoopSmall = D_800A3684\n"
        "D_800A3988.MainLoopSmall = D_800A3988\n"
        "D_800AE178.MainLoop1 = D_800AE178\n"
        "D_800AE178.MainLoop2 = D_800AE178\n"
        "D_800A3A58.MainLoop3 = D_800A3A58\n"
        "D_800A36E1.MainLoop4 = D_800A36E1\n"
        "D_800A3981.MainLoop5 = D_800A3981\n"
        "D_800A3685.MainLoop6 = D_800A3685\n"
        "D_800A3685.MainLoop7 = D_800A3685\n"
        "gOrderingTables.MainLoop8 = gOrderingTables\n"
        "gOrderingTableBank.MainLoop9 = gOrderingTableBank\n"
        "D_800A39C8.MainLoop10 = D_800A39C8\n"
        "D_800A39C8.MainLoop11 = D_800A39C8\n"
        "D_800A3685.MainLoop12 = D_800A3685\n"
        "D_800A37D8.MainLoop13 = D_800A37D8\n"
        "D_800A37DC.MainLoop14 = D_800A37DC\n"
        "D_800A3684.MainLoop15 = D_800A3684\n"
        "D_800A3A24.MainLoop16 = D_800A3A24\n"
        "D_800A3684.MainLoop17 = D_800A3684\n"
        "D_800A3A24.MainLoop18 = D_800A3A24\n"
        "D_800A307C.MainLoop19 = D_800A307C\n"
        "D_800A3A24.MainLoop20 = D_800A3A24\n"
        "D_800A3888.MainLoop21 = D_800A3888\n"
        "D_800A3684.MainLoop22 = D_800A3684\n"
        "D_800A307C.MainLoop23 = D_800A307C\n"
        "D_800A3A24.MainLoop24 = D_800A3A24\n"
        "D_800A3888.MainLoop25 = D_800A3888\n"
        "D_800A3684.MainLoop26 = D_800A3684\n"
        "D_800A36E4.MainLoop27 = D_800A36E4\n"
        "D_800A3685.MainLoop28 = D_800A3685\n"
        "D_800A37F8.MainLoop29 = D_800A37F8\n"
        "D_800A3684.MainLoop30 = D_800A3684\n"
        "D_800A3A24.MainLoop31 = D_800A3A24\n"
        "D_800A307C.MainLoop32 = D_800A307C\n"
        "D_800A3A24.MainLoop33 = D_800A3A24\n"
        "D_800A3808.MainLoop51 = D_800A3808\n"
        "D_800A3770.MainLoop57 = D_800A3770\n"
        "D_800A3770.MainLoop58 = D_800A3770\n"
        "D_800A38E8.MainLoop59 = D_800A38E8\n"
        "D_800A3988.MainLoop60 = D_800A3988\n"
        "D_800A3988.MainLoop61 = D_800A3988\n"
        "D_800A3770.MainLoop62 = D_800A3770\n"
        "D_800A3770.MainLoop63 = D_800A3770\n"
        "D_800A38E8.MainLoop64 = D_800A38E8\n"
        "D_800A3988.MainLoop65 = D_800A3988\n"
        "D_800A3988.MainLoop66 = D_800A3988\n"
        "D_800A3684.MainLoop67 = D_800A3684\n"
        "D_800A3A24.MainLoop68 = D_800A3A24\n"
        "D_800A3684.MainLoop69 = D_800A3684\n"
        "D_800A3080.MainLoop70 = D_800A3080\n"
        "D_800A3A24.MainLoop71 = D_800A3A24\n"
        "D_800A307C.MainLoop72 = D_800A307C\n"
        "D_800A3684.MainLoop73 = D_800A3684\n"
        "D_800A3A24.MainLoop74 = D_800A3A24\n"
        "D_800A3684.MainLoop75 = D_800A3684\n"
        "D_800A307C.MainLoop76 = D_800A307C\n"
        "D_800A3080.MainLoop77 = D_800A3080\n"
        "D_800A3A24.MainLoop78 = D_800A3A24\n"
        "D_800A3A25.MainLoop79 = D_800A3A25\n"
        "D_800A3059.MainLoopPostUp = D_800A3059\n"
        "D_800A3059.MainLoopPostDown = D_800A3059\n");

s32 ListHasClearFlagsMainLoop(u8 *node) asm("ListHasClearFlags");
void ListSetFieldsAndEnableMainLoop(u8 *, s32, s32,
                                    s32) asm("ListSetFieldsAndEnable");
void func_80014A40MainLoop(s32 arg0) asm("func_80014A40");
void func_8003CC48MainLoop(void) asm("func_8003CC48");
void func_8003CCE0MainLoop(s32 arg0) asm("func_8003CCE0");
s32 func_8003F4FCMainLoop(s32 arg0) asm("func_8003F4FC");
/* All loop sound arguments fit s8. Pins already hold their extended values. */
void func_8003F564MainLoop(s32, s32) asm("func_8003F564");
void func_8003F914MainLoop(s32) asm("func_8003F914");
s32 func_80041B7CMainLoop(s32) asm("func_80041B7C");
s32 func_8004229CMainLoop(s32 arg0) asm("func_8004229C");
void func_80044FF8MainLoop(s32 arg0, s32 arg1) asm("func_80044FF8");
void func_80055C78MainLoop() asm("func_80055C78");
s32 func_80056B0CMainLoop(s32 arg0, s32 arg1) asm("func_80056B0C");
s32 func_80056B5CMainLoop(s32 arg0, s32 arg1, s32 arg2) asm("func_80056B5C");
void func_80056C84MainLoop(s32 arg0, s32 arg1) asm("func_80056C84");
void func_80056F04MainLoop(s32 arg0) asm("func_80056F04");
void func_80057008MainLoop(s32 arg0) asm("func_80057008");
void func_80057160MainLoop(s32 arg0) asm("func_80057160");
void func_80057DD4MainLoop(void) asm("func_80057DD4");
void func_80057DE8MainLoop(void) asm("func_80057DE8");
void func_80057DFCMainLoop(void) asm("func_80057DFC");
void func_80057E10MainLoop(void) asm("func_80057E10");
void func_80058000MainLoop(s32 index, s32 *out) asm("func_80058000");
void func_80058030MainLoop(void) asm("func_80058030");
void func_800596F4MainLoop(void) asm("func_800596F4");
void func_800598C4MainLoop(void) asm("func_800598C4");
void func_800599E4MainLoop(void) asm("func_800599E4");
/* Intensity is masked to u8 in the pulse block before these calls. */
void func_8005A804MainLoop(s32, s32, s32) asm("func_8005A804");
void func_8005B2F0MainLoop(void) asm("func_8005B2F0");
void func_8005B300MainLoop(void) asm("func_8005B300");
void func_8005E4A4MainLoop(u8 *table) asm("func_8005E4A4");
void func_80060E94MainLoop(s32 arg0) asm("func_80060E94");
void func_80060F10MainLoop(s32 a, s32 b, s16 c) asm("func_80060F10");
void func_80060F54MainLoop(s32 arg0, s32 volume) asm("func_80060F54");
void func_80062874MainLoop(s32 arg0, s32 arg1) asm("func_80062874");
void func_80062F04MainLoop() asm("func_80062F04");
void func_80063180MainLoop(s32 enabled) asm("func_80063180");
void func_80063770MainLoop(u8 index) asm("func_80063770");
void func_80063AE0MainLoop(s32, s32) asm("func_80063AE0");
void func_80068AC4MainLoop(s32 arg0, s32 arg1, s32 arg2) asm("func_80068AC4");
void func_80069AFCMainLoop(s32 arg0) asm("func_80069AFC");
s32 func_80069EB8MainLoop(void) asm("func_80069EB8");
s32 func_8006A080MainLoop(void) asm("func_8006A080");
u8 func_8006AD0CMainLoop(u8 value) asm("func_8006AD0C");
void func_8006C598MainLoop(s32 low, s32 high, s32 color) asm("func_8006C598");
void func_8006C5E4MainLoop(s32 arg0) asm("func_8006C5E4");
void func_8006C9DCMainLoop(void) asm("func_8006C9DC");
void func_8006CE64MainLoop(void) asm("func_8006CE64");
void func_8006CF38MainLoop(void) asm("func_8006CF38");
s32 func_8006D0C0MainLoop(void) asm("func_8006D0C0");
void func_8006D0F0MainLoop(void) asm("func_8006D0F0");
s32 func_8006D258MainLoop(void) asm("func_8006D258");
void func_8006DA40MainLoop(void) asm("func_8006DA40");
void func_8006DE68MainLoop(u32 arg0, u32 mode) asm("func_8006DE68");
void func_80041AF0MainLoop(s32) asm("func_80041AF0");
void ClearOTagRMainLoop(u32 *, s32) asm("ClearOTagR");
void DrawOTagMainLoop(u32 *) asm("DrawOTag");
s32 DrawSyncMainLoop(s32) asm("DrawSync");
s32 LoadImageMainLoop(s16 *, u32 *) asm("LoadImage");
s32 RandomScaledGetMainLoop(s32 scale) asm("RandomScaledGet");
void SetDispMaskMainLoop(s32) asm("SetDispMask");
s32 VSyncMainLoop(s32) asm("VSync");
void func_80053C00MainLoop(s32, s32) asm("func_80053C00");
u8 func_800571ECMainLoop(u8, u8 *, s32) asm("func_800571EC");
void func_8005DAD4MainLoop(void) asm("func_8005DAD4");
void func_8005DFA0MainLoop(void) asm("func_8005DFA0");
void func_8005ED74MainLoop() asm("func_8005ED74");
void func_800606D4MainLoop(void) asm("func_800606D4");
void func_80060FD8MainLoop(void) asm("func_80060FD8");
void func_80063C34MainLoop(u8, u8) asm("func_80063C34");
void func_80064208MainLoop(void) asm("func_80064208");
void func_80068220MainLoop(s32) asm("func_80068220");
void func_80068CE4MainLoop(void) asm("func_80068CE4");
void func_800691D4MainLoop(void) asm("func_800691D4");
void func_800697ECMainLoop(s32) asm("func_800697EC");
void func_80069C60MainLoop(u8) asm("func_80069C60");
s32 func_80069F30MainLoop(void) asm("func_80069F30");
s32 func_8006A15CMainLoop(s32) asm("func_8006A15C");
void func_8006A7C8MainLoop(s32) asm("func_8006A7C8");
void func_8006BF74MainLoop(void) asm("func_8006BF74");
s32 func_8006C700MainLoop(s32, s32) asm("func_8006C700");
void func_8006C9F8MainLoop(void) asm("func_8006C9F8");
void func_8006CB80MainLoop(s32) asm("func_8006CB80");
s32 func_8006D178MainLoop(void) asm("func_8006D178");
void func_8006D8E8MainLoop(s32) asm("func_8006D8E8");
void func_8006E07CMainLoop(u32, u32, u32) asm("func_8006E07C");
void func_8006E628MainLoop(u32, u32, u32) asm("func_8006E628");
void func_8005833CMainLoop(u8) asm("func_8005833C");
void func_8005C124MainLoop(u8, u8) asm("func_8005C124");
extern s8 D_800A2F9CMainLoop[] asm("D_800A2F9C.MainLoop");
extern u8 D_800A3059MainLoop asm("D_800A3059.MainLoop");
extern u8 D_800A305AMainLoop asm("D_800A305A.MainLoop");
extern u8 D_800A305BMainLoop asm("D_800A305B.MainLoop");
extern s32 D_800A305CMainLoop asm("D_800A305C.MainLoop");
extern u8 D_800A3064MainLoop asm("D_800A3064.MainLoop");
extern u8 D_800A3065MainLoop asm("D_800A3065.MainLoop");
extern u8 D_800A3076MainLoop asm("D_800A3076.MainLoop");
extern u8 D_800A358CMainLoop[] asm("D_800A358C.MainLoop");
extern u32 *D_800A35F0MainLoop asm("D_800A35F0.MainLoop");
extern u8 D_800A3608MainLoop asm("D_800A3608.MainLoop");
extern u8 D_800A3644MainLoop asm("D_800A3644.MainLoop");
extern u16 D_800A3690MainLoop[] asm("D_800A3690.MainLoop");
extern u8 D_800A36E0MainLoop asm("D_800A36E0.MainLoop");
extern s16 D_800A3710MainLoop asm("D_800A3710.MainLoop");
extern u8 D_800A3724MainLoop asm("D_800A3724.MainLoop");
extern u8 D_800A3808MainLoop[] asm("D_800A3808.MainLoop");
extern u8 D_800A3928MainLoop asm("D_800A3928.MainLoop");
extern u8 D_800A3950MainLoop asm("D_800A3950.MainLoop");
extern u8 D_800A3968MainLoop[] asm("D_800A3968.MainLoop");
extern s8 D_800A3980MainLoop asm("D_800A3980.MainLoop");
extern u8 D_800A39E4MainLoop asm("D_800A39E4.MainLoop");
extern s16 D_800B9B84MainLoop[] asm("D_800B9B84.MainLoop");
extern u8 D_800A3684MainLoopSmall asm("D_800A3684.MainLoopSmall");
extern u8 D_800A3988MainLoopSmall asm("D_800A3988.MainLoopSmall");
extern u8 *D_800AE178MainLoopSite1[] asm("D_800AE178.MainLoop1");
extern u8 *D_800AE178MainLoopSite2[] asm("D_800AE178.MainLoop2");
extern u8 D_800A3A58MainLoopSite3[] asm("D_800A3A58.MainLoop3");
extern u8 D_800A36E1MainLoopSite4[] asm("D_800A36E1.MainLoop4");
extern s8 D_800A3981MainLoopSite5[] asm("D_800A3981.MainLoop5");
extern u8 D_800A3685MainLoopSite6[] asm("D_800A3685.MainLoop6");
extern u8 D_800A3685MainLoopSite7[] asm("D_800A3685.MainLoop7");
extern u8 gOrderingTablesMainLoopSite8[] asm("gOrderingTables.MainLoop8");
extern s32
    gOrderingTableBankMainLoopSite9[] asm("gOrderingTableBank.MainLoop9");
extern u32 *D_800A39C8MainLoopSite10[] asm("D_800A39C8.MainLoop10");
extern u32 *D_800A39C8MainLoopSite11[] asm("D_800A39C8.MainLoop11");
extern u8 D_800A3685MainLoopSite12[] asm("D_800A3685.MainLoop12");
extern u8 *D_800A37D8MainLoopSite13[] asm("D_800A37D8.MainLoop13");
extern u8 *D_800A37DCMainLoopSite14[] asm("D_800A37DC.MainLoop14");
extern u8 D_800A3684MainLoopSite15[] asm("D_800A3684.MainLoop15");
extern s8 D_800A3A24MainLoopSite16[] asm("D_800A3A24.MainLoop16");
extern u8 D_800A3684MainLoopSite17[] asm("D_800A3684.MainLoop17");
extern s8 D_800A3A24MainLoopSite18[] asm("D_800A3A24.MainLoop18");
extern s8 D_800A307CMainLoopSite19[] asm("D_800A307C.MainLoop19");
extern s8 D_800A3A24MainLoopSite20[] asm("D_800A3A24.MainLoop20");
extern u8 *D_800A3888MainLoopSite21[] asm("D_800A3888.MainLoop21");
extern u8 D_800A3684MainLoopSite22[] asm("D_800A3684.MainLoop22");
extern s8 D_800A307CMainLoopSite23[] asm("D_800A307C.MainLoop23");
extern s8 D_800A3A24MainLoopSite24[] asm("D_800A3A24.MainLoop24");
extern u8 *D_800A3888MainLoopSite25[] asm("D_800A3888.MainLoop25");
extern u8 D_800A3684MainLoopSite26[] asm("D_800A3684.MainLoop26");
extern u8 D_800A36E4MainLoopSite27[] asm("D_800A36E4.MainLoop27");
extern u8 D_800A3685MainLoopSite28[] asm("D_800A3685.MainLoop28");
extern u8 *D_800A37F8MainLoopSite29[] asm("D_800A37F8.MainLoop29");
extern u8 D_800A3684MainLoopSite30[] asm("D_800A3684.MainLoop30");
extern s8 D_800A3A24MainLoopSite31[] asm("D_800A3A24.MainLoop31");
extern s8 D_800A307CMainLoopSite32[] asm("D_800A307C.MainLoop32");
extern s8 D_800A3A24MainLoopSite33[] asm("D_800A3A24.MainLoop33");
extern u8 D_800A3808MainLoopSite51[] asm("D_800A3808.MainLoop51");
extern u8 D_800A3770MainLoopSite57[] asm("D_800A3770.MainLoop57");
extern u8 D_800A3770MainLoopSite58[] asm("D_800A3770.MainLoop58");
extern u8 D_800A38E8MainLoopSite59[] asm("D_800A38E8.MainLoop59");
extern u8 D_800A3988MainLoopSite60[] asm("D_800A3988.MainLoop60");
extern u8 D_800A3988MainLoopSite61[] asm("D_800A3988.MainLoop61");
extern u8 D_800A3770MainLoopSite62[] asm("D_800A3770.MainLoop62");
extern u8 D_800A3770MainLoopSite63[] asm("D_800A3770.MainLoop63");
extern u8 D_800A38E8MainLoopSite64[] asm("D_800A38E8.MainLoop64");
extern u8 D_800A3988MainLoopSite65[] asm("D_800A3988.MainLoop65");
extern u8 D_800A3988MainLoopSite66[] asm("D_800A3988.MainLoop66");
extern u8 D_800A3684MainLoopSite67[] asm("D_800A3684.MainLoop67");
extern s8 D_800A3A24MainLoopSite68[] asm("D_800A3A24.MainLoop68");
extern u8 D_800A3684MainLoopSite69[] asm("D_800A3684.MainLoop69");
extern s8 D_800A3080MainLoopSite70[] asm("D_800A3080.MainLoop70");
extern s8 D_800A3A24MainLoopSite71[] asm("D_800A3A24.MainLoop71");
extern s8 D_800A307CMainLoopSite72[] asm("D_800A307C.MainLoop72");
extern u8 D_800A3684MainLoopSite73[] asm("D_800A3684.MainLoop73");
extern s8 D_800A3A24MainLoopSite74[] asm("D_800A3A24.MainLoop74");
extern u8 D_800A3684MainLoopSite75[] asm("D_800A3684.MainLoop75");
extern s8 D_800A307CMainLoopSite76[] asm("D_800A307C.MainLoop76");
extern s8 D_800A3080MainLoopSite77[] asm("D_800A3080.MainLoop77");
extern s8 D_800A3A24MainLoopSite78[] asm("D_800A3A24.MainLoop78");
extern s8 D_800A3A25MainLoopSite79[] asm("D_800A3A25.MainLoop79");
extern u8 D_800A3059MainLoopPostUp asm("D_800A3059.MainLoopPostUp");
extern u8 D_800A3059MainLoopPostDown asm("D_800A3059.MainLoopPostDown");

void func_80053D40(void) {
    s32 newPad[2];
    s32 oldPad[2];
    u8 playerUnlockSteps[2];
    register s32 one asm("s3");
    register s32 two asm("s5");
    register s32 mode13 asm("s6");
    u8 exitLoop;
    u8 displayPhase;
    s32 idleFrames;
    s32 animationStartX;
    s32 animationEndX;
    s32 animationStepX;
    s32 animationReverseStepX;
    s32 *previousPadCursor;
    register s32 *currentPadCursor asm("s2");
    s32 argument0;
    s32 menuPhase;
    register s32 animateX asm("a0");
    register s32 animateY asm("a1");
    register s32 animateStep asm("a2");
    register u8 **animationNodeSlot asm("v0");
    s32 padBits;
    register s32 previousPadInverse asm("a3");
    s32 nextIdleFrames;
    s32 cardMenuCode;
    s32 nextBufferIndex;
    s32 padBits0;
    s32 playerPadBits;
    s32 sequenceValue;
    s32 unlockPhase;
    s32 itemUp;
    s32 itemDown;
    s32 cardOperation;
    s32 menuDirection;
    s32 activePlayer;
    register s32 index asm("s0");
    register s32 player asm("s2");
    register s32 screenResult asm("s4");
    register s32 unlockStep asm("s7");
    s32 unlockDirectionBits;
    s32 dialogScreen;
    register s32 actionSound asm("a1");
    register s32 returnChannel asm("a0");
    u32 *orderingTable;
    u8 *screenTable;
    register u8 *sequenceCursor asm("s1");
    register u8 *selectionCursor asm("s2");
    register s32 screenResultByte asm("s1");
    u8 pulseTick;
    u8 transitionPhase;
    u8 nextItemUp;
    u8 nextItemDown;
    u8 nextScreen;
    u8 pulsePhase;
    u8 selection;
    u8 currentSelection;
    u8 sequencePhase;
    u8 itemCursorUp;
    u8 itemCursorDown;
    u8 secondPlayerEnabled;
    u8 menuCode;
    register s32 wrappedItemUp asm("v0");

    playerUnlockSteps[0] = 0;
    playerUnlockSteps[1] = 0;
    func_8005B2F0MainLoop();
    func_8005DAD4MainLoop();
    func_8005DFA0MainLoop();
    idleFrames = 0;
    if ((u8)D_800A305BMainLoop < 0x11U) {
        screenTable = D_800AE178MainLoopSite1[D_800A305BMainLoop];
    } else {
        screenTable = *D_800AE178MainLoopSite2;
    }
    activePlayer = 0;
    func_8005E4A4MainLoop(screenTable);
    asm("" : "=r"(activePlayer) : "0"(activePlayer));
    one = 1;
    two = 2;
    asm("" : : "r"(one), "r"(two));
    D_800A3608MainLoop = 0;
    exitLoop = 0;
    do {
        {
            register s32 randomScale asm("a0");
            /* The original call retains the incoming a0 and ignores the result. */
            asm("" : "=r"(randomScale));
            RandomScaledGetMainLoop(randomScale);
        }
        func_80057DE8MainLoop();
        func_80057E10MainLoop();
        func_8005B300MainLoop();
        argument0 = D_800A39E4MainLoop;
        asm("" : "=r"(argument0) : "0"(argument0));
        if (argument0 == 0xFC) {
            func_80041AF0MainLoop(0);
            func_8006DA40MainLoop();
            D_800A3928MainLoop = 0;
        } else if (argument0 == 9) {
            if (*D_800A3A58MainLoopSite3 == 0) {
                func_800599E4MainLoop();
                if (func_80069F30MainLoop() & 0xFF) {
                    func_8006A7C8MainLoop(0);
                }
                func_800598C4MainLoop();
            }
            func_80068220MainLoop((s32)D_800A305BMainLoop);
        } else if (argument0 == 0xA) {
            func_80068CE4MainLoop();
        } else if (argument0 == 0xC) {
            func_800691D4MainLoop();
        } else if (argument0 == 0xE) {
            func_80064208MainLoop();
        } else if ((u32)(D_800A39E4MainLoop - 0x10) < 2U) {
            func_800697ECMainLoop(argument0 - 0x10);
        } else {
            func_80056C84MainLoop(argument0, activePlayer);
            func_8005C124MainLoop(D_800A39E4MainLoop, D_800A3059MainLoop);
        }
        func_80069C60MainLoop(D_800A39E4MainLoop);
        func_80056F04MainLoop((s32)D_800A39E4MainLoop);
        switch (D_800A39E4MainLoop) {
        case 0:
            idleFrames = 0;
            goto initializePads;
        case 7:
            secondPlayerEnabled = 0;
            argument0 = activePlayer & 0xFF;
            if (((D_800A3950MainLoop == 0xFB) || (D_800A3950MainLoop == 3)) &&
                (D_800A3644MainLoop != 0)) {
                secondPlayerEnabled = 1;
            }
            func_8005ED74MainLoop(argument0, secondPlayerEnabled);
            /* End the old register lifetime before setting the pad index. */
            asm volatile("" : "=r"(index));
            asm volatile("" : : : "memory");
            index = 0;
            if (D_800A3950MainLoop == 0xFB) {
            case 1:
                index = 0;
                func_8006BF74MainLoop();
                currentPadCursor = &newPad[0];
            } else {
                goto resetPadArray;
            }
            break;
        case 2:
        case 8:
            index = 0;
            D_800A3980MainLoop = func_8006AD0CMainLoop(D_800A36E0MainLoop);
            D_800A3981MainLoopSite5[0] =
                func_8006AD0CMainLoop(D_800A36E1MainLoopSite4[0]);
            currentPadCursor = &newPad[0];
            break;
        case 5:
            index = 0;
            func_800606D4MainLoop();
            func_80063180MainLoop((s32)D_800A3076MainLoop);
            currentPadCursor = &newPad[0];
            break;
        case 13:
            func_80060FD8MainLoop();
            /* End the old register lifetime before setting the pad index. */
            asm volatile("" : "=r"(index));
            asm volatile("" : : : "memory");
            D_800A3684MainLoopSmall = 0;
            index = 0;
            if (D_800A3644MainLoop != 0) {
                *D_800A3685MainLoopSite6 = 0;
            } else {
                *D_800A3685MainLoopSite7 = two;
            }
            goto resetPadArray;
        case 3:
        case 6:
            func_8005833CMainLoop(D_800A305BMainLoop);
        default:
        initializePads:
            index = 0;
        resetPadArray:
            /* Keep pointer setup in the common reset path. */
            asm volatile("" : "=r"(currentPadCursor));
            currentPadCursor = &newPad[0];
            break;
        }
        previousPadCursor = &oldPad[0];
        asm("" : "=r"(currentPadCursor) : "0"(currentPadCursor));
    readInitialPads:
        func_80058000MainLoop(index & 0xFF, previousPadCursor);
        *currentPadCursor = 0;
        currentPadCursor++;
        index += 1;
        previousPadCursor++;
        if (index < 2) {
            goto readInitialPads;
        }
        screenResult = 0;
        D_800A305CMainLoop = 0;
        unlockStep = 0;
        if (D_800A39E4MainLoop == 0xC) {
            displayPhase = 0;
        } else {
            displayPhase = 0xFF;
            SetDispMaskMainLoop(1);
        }
        asm(""
            : "=r"(screenResult), "=r"(unlockStep)
            : "0"(screenResult), "1"(unlockStep));
        if (!(screenResult & 0xFF)) {
            mode13 = 13;
            asm("" : : "r"(mode13));
            do {
                func_8003CC48MainLoop();
                nextIdleFrames = idleFrames + 1;
                idleFrames = nextIdleFrames;
                if ((D_800A39E4MainLoop == 0) && (nextIdleFrames >= 0x709)) {
                    screenResult = 1;
                    D_800A39E4MainLoop = 0xFD;
                }
                pulseTick = D_800A3724MainLoop - 1;
                D_800A3724MainLoop = pulseTick;
                if (!(pulseTick & 0xFF)) {
                    pulsePhase = D_800A305AMainLoop + 1;
                    D_800A305AMainLoop = pulsePhase;
                    if ((u32)(pulsePhase & 0xFF) >= 0x15U) {
                        D_800A305AMainLoop = 0;
                    }
                    {
                        register s32 pulseValue asm("v1");
                        register s32 magnitude asm("v0");
                        register s32 intensity asm("a0");
                        pulseValue = D_800A305AMainLoop;
                        /* Intensity is 64 + 8 * abs(pulseValue - 10), modulo 256. */
                        asm(".set\tnoreorder\n\tnop\n\taddiu\t%0,%2,-10\n\tbgez\t%0,1f\n\tsll\t%0,%0,3\n\tori\t%0,$zero,10\n\tsubu\t%0,%0,%2\n\tsll\t%0,%0,3\n1:\n\taddiu\t%0,%0,64\n\tandi\t%1,%0,255"
                            : "=&r"(magnitude), "=r"(intensity)
                            : "r"(pulseValue));
                        func_8005A804MainLoop(intensity, intensity, 0x19U);
                    }
                    D_800A3724MainLoop = 3;
                }
                nextBufferIndex = D_800A305CMainLoop == 0;
                orderingTable =
                    (nextBufferIndex << 0xC) + gOrderingTablesMainLoopSite8;
                D_800A305CMainLoop = nextBufferIndex;
                gOrderingTableBankMainLoopSite9[0] = nextBufferIndex;
                D_800A39C8MainLoopSite10[0] = orderingTable;
                ClearOTagRMainLoop(orderingTable, 0x400);
                func_80014A40MainLoop((s32)(u8)D_800A305CMainLoop);
                func_80057DFCMainLoop();
                func_80057DD4MainLoop();
                func_80053C00MainLoop((s32)(u8)D_800A305CMainLoop,
                                      activePlayer & 0xFF);
                DrawSyncMainLoop(0);
                VSyncMainLoop(0);
                func_80058030MainLoop();
                if (displayPhase == one) {
                    SetDispMaskMainLoop(1);
                    displayPhase = 2;
                }
                D_800A3710MainLoop = -(D_800A305CMainLoop != 0) & 0x140;
                LoadImageMainLoop(&D_800A3710MainLoop, D_800A35F0MainLoop);
                DrawOTagMainLoop(
                    (u32 *)((u8 *)D_800A39C8MainLoopSite11[0] + 0xFFC));
                if (displayPhase == 0) {
                    displayPhase = 1;
                }
                func_80041AF0MainLoop(0);
                if (newPad[0] != 0) {
                    idleFrames = 0;
                }
                if (D_800A39E4MainLoop == 5) {
                    padBits0 = func_80041B7CMainLoop(0);
                    newPad[0] = padBits0;
                    if ((padBits0 & 0x20) && (D_800A3076MainLoop == 0)) {
                        unlockPhase = unlockStep & 0xFF;
                        if (padBits0 & 0xF000) {
                            if (unlockPhase == one) {
                                goto sequenceOne;
                            }
                            if (unlockPhase < 2) {
                                unlockDirectionBits = padBits0 & 0x1000;
                                if (unlockPhase == 0) {
                                    goto advanceUnlockStep;
                                }
                                goto sequenceDone;
                            }
                            if (unlockPhase == two) {
                                goto sequenceTwo;
                            }
                            if (unlockPhase == 3) {
                                goto sequenceLast;
                            }
                            goto sequenceDone;
                        sequenceOne:
                            unlockDirectionBits = padBits0 & 0x8000;
                            goto advanceUnlockStep;
                        sequenceTwo:
                            unlockDirectionBits = padBits0 & 0x4000;
                        advanceUnlockStep:
                            if (unlockDirectionBits != 0) {
                                unlockStep++;
                            }
                            goto sequenceDone;
                        sequenceLast:
                            if (padBits0 & 0x2000) {
                                D_800A3076MainLoop = one;
                                func_80063180MainLoop(1);
                                func_8003F564MainLoop(0, 8);
                                goto resetUnlockStep;
                            }
                        sequenceDone:;
                        }
                    } else {
                    resetUnlockStep:
                        unlockStep = 0;
                    }
                } else if ((D_800A39E4MainLoop == two) &&
                           (D_800A3059MainLoop == one)) {
                    index = 0;
                    sequenceCursor = &playerUnlockSteps[0];
                    asm("" : "=r"(sequenceCursor) : "0"(sequenceCursor));
                    selectionCursor = &D_800A36E0MainLoop;
                    asm("" : "=r"(selectionCursor) : "0"(selectionCursor));
                readPlayerUnlockSequence:
                    if ((index != one) || (D_800A3644MainLoop != 0)) {
                        selection = *selectionCursor;
                        if ((selection == 5) || (selection == two)) {
                            playerPadBits = func_80041B7CMainLoop(index);
                            (&newPad[0])[index] = playerPadBits;
                            if (playerPadBits & 0x40) {
                                if (playerPadBits & 0x5000) {
                                    sequencePhase = *sequenceCursor;
                                    sequenceValue = sequencePhase & 0xFF;
                                    if (sequenceValue == 0) {
                                        goto playerSequenceFirst;
                                    }
                                    if (sequenceValue == one) {
                                        goto playerSequenceSecond;
                                    }
                                    sequenceCursor++;
                                    goto playerSequenceNext;
                                playerSequenceFirst:
                                    if (playerPadBits & 0x1000) {
                                        *sequenceCursor = sequencePhase + 1;
                                    }
                                    goto advancePlayerUnlockSequence;
                                playerSequenceSecond:
                                    if (!(playerPadBits & 0x4000)) {
                                        goto advancePlayerUnlockSequence;
                                    }
                                    currentSelection = *selectionCursor;
                                    if (currentSelection == two) {
                                        func_80063C34MainLoop(2, 0x19);
                                        func_80063AE0MainLoop(index, 2);
                                        D_800A3065MainLoop ^= 1;
                                        *sequenceCursor = 0;
                                        goto advancePlayerUnlockSequence;
                                    }
                                    if (currentSelection == 5) {
                                        func_80063C34MainLoop(5, 0x18);
                                        func_80063AE0MainLoop(index, 5);
                                        D_800A3064MainLoop ^= 1;
                                    }
                                    goto resetPlayerUnlockSequence;
                                } else {
                                    goto advancePlayerUnlockSequence;
                                }
                            } else {
                            resetPlayerUnlockSequence:
                                *sequenceCursor = 0;
                                goto advancePlayerUnlockSequence;
                            }
                        } else {
                        advancePlayerUnlockSequence:
                            sequenceCursor += 1;
                        }
                    playerSequenceNext:
                        index += 1;
                        selectionCursor += 1;
                        if (index < 2) {
                            goto readPlayerUnlockSequence;
                        }
                    }
                }
                if ((D_800A39E4MainLoop == mode13) &&
                    (D_800A3684MainLoopSmall == two) &&
                    (ListHasClearFlagsMainLoop(*D_800A37D8MainLoopSite13) !=
                     0) &&
                    ((D_800A3644MainLoop == 0) ||
                     ((*D_800A3685MainLoopSite12 == two) &&
                      (ListHasClearFlagsMainLoop(*D_800A37DCMainLoopSite14) !=
                       0)))) {
                    screenResult = 1;
                } else {
                    player = 0;
                    asm("" : "=r"(player) : "0"(player));
                    index = player & 0xFF;
                    do {
                        if ((index == 0) || (D_800A3644MainLoop != 0)) {
                            (&newPad[0])[index] = func_80041B7CMainLoop(index);
                            if ((D_800A39E4MainLoop == 7) &&
                                (activePlayer == one)) {
                                if (index != 0) {
                                    newPad[0] = newPad[1];
                                    oldPad[0] = oldPad[1];
                                    goto handlePlayerInput;
                                }
                                goto nextPlayer;
                            }
                            if (player & 0xFF) {
                                if (D_800A39E4MainLoop != two) {
                                    if (D_800A39E4MainLoop == mode13) {
                                        goto handlePlayerInput;
                                    }
                                    goto nextPlayer;
                                }
                                goto handlePlayerSelection;
                            }
                        handlePlayerInput:
                        handlePlayerSelection:
                            if (D_800A39E4MainLoop == mode13) {
                                index = player & 0xFF;
                                if (newPad[index] &
                                    ((u16)~oldPad[index] & 0x800)) {
                                    transitionPhase =
                                        D_800A3684MainLoopSite15[index];
                                    if (transitionPhase == 0) {
                                        func_8003F564MainLoop(0, 3);
                                        if (func_8004229CMainLoop((
                                                s32)(u8)D_800A3A24MainLoopSite16
                                                                      [index]) &
                                            0xFF) {
                                            func_80062874MainLoop(index, 1);
                                            D_800A3684MainLoopSite17[index] =
                                                one;
                                            func_8006DE68MainLoop(
                                                (u32)index,
                                                (u32)(u8)
                                                    D_800A3A24MainLoopSite18
                                                        [index]);
                                            func_80062F04MainLoop(
                                                index,
                                                D_800A3A24MainLoopSite20[index],
                                                D_800A307CMainLoopSite19
                                                    [index]);
                                            animationStartX = -0x140;
                                            animationNodeSlot =
                                                D_800A3888MainLoopSite21;
                                            asm(""
                                                : "=r"(animationNodeSlot)
                                                : "0"(animationNodeSlot));
                                            animationNodeSlot =
                                                (u8 **)((index * 4) +
                                                        (u32)animationNodeSlot);
                                            if (index != 0) {
                                                animationStartX = 0x140;
                                            }
                                            animationStepX = 4;
                                            if (index != 0) {
                                                animationStepX = -4;
                                            }
                                            ListSetFieldsAndEnableMainLoop(
                                                *animationNodeSlot,
                                                animationStartX, 0,
                                                animationStepX);
                                        } else {
                                            func_80062874MainLoop(index, 0);
                                            D_800A3684MainLoopSite22[index] =
                                                two;
                                            goto updateSelectionPanel;
                                        }
                                    } else if (transitionPhase == one) {
                                        func_8003F564MainLoop(0, 3);
                                        func_8006E628MainLoop(
                                            (u32)index,
                                            (u32)(u8)
                                                D_800A3A24MainLoopSite24[index],
                                            (u32)(u8)D_800A307CMainLoopSite23
                                                [index]);
                                        func_80062874MainLoop(index, 0);
                                        animationEndX = 0x140;
                                        animationNodeSlot =
                                            D_800A3888MainLoopSite25;
                                        asm(""
                                            : "=r"(animationNodeSlot)
                                            : "0"(animationNodeSlot));
                                        animationNodeSlot =
                                            (u8 **)((index * 4) +
                                                    (u32)animationNodeSlot);
                                        if (index != 0) {
                                            animationEndX = -0x140;
                                        }
                                        animationReverseStepX = -4;
                                        if (index != 0) {
                                            animationReverseStepX = 4;
                                        }
                                        ListSetFieldsAndEnableMainLoop(
                                            *animationNodeSlot, 0,
                                            animationEndX,
                                            animationReverseStepX);
                                        D_800A3684MainLoopSite26[index] = two;
                                        D_800A36E4MainLoopSite27[index] = one;
                                    updateSelectionPanel:
                                        if ((D_800A3684MainLoopSmall != 0) &&
                                            (*D_800A3685MainLoopSite28 != 0)) {
                                            ListSetFieldsAndEnableMainLoop(
                                                *D_800A37F8MainLoopSite29, 0,
                                                0x140, 4);
                                        }
                                    }
                                } else if ((func_8004229CMainLoop((
                                                s32)(u8)D_800A3A24MainLoopSite31
                                                                      [index]) &
                                            0xFF) &&
                                           (D_800A3684MainLoopSite30[index] ==
                                            one)) {
                                    func_8006E07CMainLoop(
                                        (u32)index,
                                        (u32)(u8)
                                            D_800A3A24MainLoopSite33[index],
                                        (u32)(u8)
                                            D_800A307CMainLoopSite32[index]);
                                }
                            }
                            {
                                register s32 previousPadZero asm("a2");
                                register s32 currentPadZero asm("a1");
                                /* Read both pads before forming the pressed-edge mask. */
                                asm("lw\t%0,%3\n\tlw\t%1,%4\n\tnor\t%2,$zero,%0"
                                    : "=r"(previousPadZero),
                                      "=r"(currentPadZero),
                                      "=r"(previousPadInverse)
                                    : "m"(oldPad[0]), "m"(newPad[0]));
                                if (currentPadZero &
                                    ((u16)previousPadInverse & 0x40)) {
                                    register s32 confirmPivot asm("v0");
                                    register s32 confirmMode asm("v1");
                                    screenResult = func_80056B5CMainLoop(
                                        (s32)D_800A3059MainLoop,
                                        (s32)D_800A39E4MainLoop,
                                        (s32)D_800A3950MainLoop);
                                    if (screenResult & 0xFF) {

                                        if ((u32)(D_800A39E4MainLoop - 0x10) >=
                                            2U) {
                                            func_8003F564MainLoop(0, 3);
                                        }
                                    } else {
                                        confirmPivot = 0x24;
                                        asm("" : : "r"(confirmPivot));
                                        confirmMode = D_800A39E4MainLoop;
                                        asm("" : : "r"(confirmMode));
                                        if (confirmMode == confirmPivot) {
                                            goto confirmMode24;
                                        }
                                        if (confirmMode < 0x25) {
                                            if (confirmMode == 0x21) {
                                                goto confirmMode21;
                                            }
                                            if (confirmMode < 0x22) {
                                                if (confirmMode == one) {
                                                    goto confirmMode1;
                                                }
                                                if (confirmMode == 5) {
                                                    goto confirmMode5;
                                                }
                                                goto finishInput;
                                            }
                                            if (confirmMode == 0x22) {
                                                goto confirmMode22;
                                            }
                                            if (confirmMode == 0x23) {
                                                goto confirmMode23;
                                            }
                                            goto finishInput;
                                        }
                                        if (confirmMode == 0x27) {
                                            goto confirmMode25;
                                        }
                                        if (confirmMode < 0x28) {
                                            if (confirmMode == 0x25) {
                                                goto confirmMode25;
                                            }
                                            if (confirmMode == 0x26) {
                                                goto confirmMode26;
                                            }
                                            goto finishInput;
                                        }
                                        if (confirmMode == 0x28) {
                                            goto confirmMode28;
                                        }
                                        if (confirmMode != 0xFC) {
                                            goto finishInput;
                                        }
                                    confirmModeFC:
                                        {
                                            register s32 exitPhase asm("v0");
                                            register s32 exitChannel asm("a0");
                                            register s32 exitTone asm("a1");
                                            exitPhase = D_800A3928MainLoop;
                                            asm("" : : "r"(exitPhase));
                                            if (exitPhase == 0) {
                                                goto confirmExitStatus;
                                            }
                                            exitChannel = 0;
                                            if (exitPhase == one) {
                                                goto confirmExitSound;
                                            }
                                            goto finishInput;
                                        confirmExitStatus:
                                            exitPhase = D_800A3808MainLoop[0];
                                            asm(""
                                                : "=r"(exitPhase)
                                                : "0"(exitPhase));
                                            exitChannel = 0;
                                            if (exitPhase != mode13) {
                                                goto confirmExitSound;
                                            }
                                            exitTone = 4;
                                            goto confirmExit;
                                        confirmExitSound:
                                            exitTone = 3;
                                        confirmExit:
                                            asm(""
                                                :
                                                : "r"(exitChannel),
                                                  "r"(exitTone));
                                            screenResult = 1;
                                            func_8003F564MainLoop(exitChannel,
                                                                  exitTone);
                                            goto finishInput;
                                        }
                                    confirmMode1:
                                        func_8003F564MainLoop(0, 3);
                                        if ((D_800A3059MainLoop == two &&
                                             D_800A3950MainLoop != 0) ||
                                            D_800A3059MainLoop == one) {
                                            func_800599E4MainLoop();
                                            if ((func_8006A080MainLoop() &
                                                 0xFF) == two) {
                                                D_800A39E4MainLoop = 0x28;
                                                func_8006C5E4MainLoop(5);
                                                menuCode = 1;
                                            } else {
                                                menuCode =
                                                    func_8006A15CMainLoop(0xFF);
                                            }
                                            func_80057008MainLoop(menuCode &
                                                                  0xFF);
                                            func_800598C4MainLoop();
                                            func_80057160MainLoop(1);
                                        } else if (D_800A3059MainLoop == 6) {
                                            if (D_800B9B84MainLoop[0] == 0) {
                                                screenResult = 1;
                                                goto finishInput;
                                            }
                                            func_8006C5E4MainLoop(2);
                                            D_800A3808MainLoop[0] = 0x15;
                                            func_8006D8E8MainLoop(0);
                                            animateX = -0x78;
                                            animateY = 0;
                                            animateStep = 2;
                                            asm(""
                                                : "=r"(animateX),
                                                  "=r"(animateY),
                                                  "=r"(animateStep)
                                                : "0"(animateX), "1"(animateY),
                                                  "2"(animateStep));
                                            dialogScreen = 0x25;
                                            goto showConfirmDialog;
                                        } else if (D_800A3059MainLoop == 0 &&
                                                   D_800A3950MainLoop != 0) {
                                            func_8006C5E4MainLoop(4);
                                            D_800A3808MainLoop[0] = 0x18;
                                            func_8006D8E8MainLoop(0);
                                            animateX = -0x78;
                                            animateY = 0;
                                            animateStep = 2;
                                            asm(""
                                                : "=r"(animateX),
                                                  "=r"(animateY),
                                                  "=r"(animateStep)
                                                : "0"(animateX), "1"(animateY),
                                                  "2"(animateStep));
                                            dialogScreen = 0x27;
                                        showConfirmDialog:
                                            D_800A39E4MainLoop = dialogScreen;
                                            func_8006C598MainLoop(animateX,
                                                                  animateY,
                                                                  animateStep);
                                            func_80063770MainLoop(0);
                                        }
                                        goto finishInput;
                                    confirmMode5:
                                        if ((u32)(D_800A3059MainLoop - 2) <
                                            2U) {
                                            func_8003F564MainLoop(0, 3);
                                            if (D_800A3059MainLoop == 3) {
                                                func_80044FF8MainLoop(0, 1);
                                                func_8003CCE0MainLoop(0);
                                                D_800A2F9CMainLoop[0] = 0;
                                            }
                                            func_80060E94MainLoop(
                                                D_800A3059MainLoop - 2);
                                            func_80060F54MainLoop(
                                                (s16)D_800A3690MainLoop
                                                    [D_800A3059MainLoop],
                                                D_800A3059MainLoop - 2);
                                            func_80060F10MainLoop(-0x78, 0, 2);
                                            D_800A39E4MainLoop = 0x21;
                                            func_80069AFCMainLoop(0x21);
                                        }
                                        goto finishInput;
                                    confirmMode21:
                                        func_8003F564MainLoop(0, 3);
                                        func_80060F10MainLoop(0, -0x78, -2);
                                        D_800A39E4MainLoop = 5;
                                        func_80069AFCMainLoop(5);
                                        if (D_800A3059MainLoop == 3) {
                                            func_80044FF8MainLoop(2, 1);
                                            func_800596F4MainLoop();
                                        }
                                        goto finishInput;
                                    confirmMode28:
                                        func_8003F564MainLoop(0, 3);
                                        func_800599E4MainLoop();
                                        cardMenuCode = func_8006A15CMainLoop(
                                            D_800A358CMainLoop[0]);
                                        D_800A39E4MainLoop = one;
                                        func_80057008MainLoop(cardMenuCode &
                                                              0xFF);
                                        func_800598C4MainLoop();
                                        func_80057160MainLoop(0);
                                        goto finishInput;
                                    confirmMode22:
                                        func_8003F564MainLoop(0, 3);
                                        D_800A39E4MainLoop = 0x23;
                                        func_8006CF38MainLoop();
                                        func_8006C9F8MainLoop();
                                        D_800A3808MainLoop[0] = 0;
                                        func_80069AFCMainLoop(
                                            D_800A39E4MainLoop);
                                        goto finishInput;
                                    confirmMode23:
                                        {
                                            register s32 scanPhase asm("v0");
                                            scanPhase = D_800A3928MainLoop;
                                            asm("" : : "r"(scanPhase));
                                            returnChannel = 0;
                                            if (scanPhase == 0) {
                                                goto confirmScan;
                                            }
                                            actionSound = 3;
                                            if (scanPhase == one) {
                                                goto returnMainMenu;
                                            }
                                            goto finishInput;
                                        confirmScan:
                                            {
                                                func_8003F564MainLoop(0, 3);
                                                if (func_8006D178MainLoop() ==
                                                    0) {
                                                    func_8003F914MainLoop(0);
                                                } else {
                                                    func_8006C9DCMainLoop();
                                                    if (D_800A3808MainLoop[0] ==
                                                        0) {
                                                        if (func_8006D0C0MainLoop() ==
                                                            one) {
                                                            goto refreshCardMenu;
                                                        }
                                                        if (D_800A3808MainLoop
                                                                [0] == 0) {
                                                            goto updateCardStatus;
                                                        }
                                                    }
                                                    if (D_800A3808MainLoop[0] ==
                                                        0x10) {
                                                    updateCardStatus:
                                                        func_800599E4MainLoop();
                                                        if (!(func_80069F30MainLoop() &
                                                              0xFF)) {
                                                            func_8006D8E8MainLoop(
                                                                0);
                                                            if (D_800A3808MainLoop
                                                                    [0] !=
                                                                mode13) {
                                                                D_800A3928MainLoop =
                                                                    one;
                                                            }
                                                        }
                                                        func_800598C4MainLoop();
                                                        if (D_800A3808MainLoop
                                                                [0] == mode13) {
                                                            goto finishInput;
                                                        }
                                                    }
                                                    if (D_800A3808MainLoop[0] ==
                                                        mode13) {
                                                        func_8003F914MainLoop(
                                                            0);
                                                        goto playBackSound;
                                                    }
                                                    goto checkCardMenuReady;
                                                }
                                            }
                                            goto finishInput;
                                        }
                                    confirmMode24:
                                        func_8003F564MainLoop(0, 3);
                                        menuPhase = D_800A3928MainLoop;
                                        asm(""
                                            : "=r"(menuPhase)
                                            : "0"(menuPhase));
                                        if (menuPhase == one) {
                                            goto confirmStageOne;
                                        }
                                        if (menuPhase < 2) {
                                            if (menuPhase == 0) {
                                                goto confirmStageZero;
                                            }
                                            goto finishInput;
                                        }
                                        if (menuPhase == two) {
                                            goto confirmStageTwo;
                                        }
                                        goto finishInput;
                                    confirmStageZero:
                                        D_800A3808MainLoop[0] = 0x17;
                                        cardOperation = 0;
                                        goto startCardOperation;
                                    confirmStageOne:
                                        if (func_8006D258MainLoop() == one) {
                                            D_800A3808MainLoop[0] = 0x12;
                                        }
                                        D_800A3928MainLoop = two;
                                    refreshCardMenu:
                                        func_8006D8E8MainLoop(0);
                                        goto finishInput;
                                    confirmStageTwo:
                                        func_8006C598MainLoop(0, -0x78, -2);
                                        if (D_800A3968MainLoop[0] != 0) {
                                            D_800A3950MainLoop = 0x24;
                                        }
                                        goto finishMainMenuReturn;
                                    confirmMode25:
                                        func_8003F564MainLoop(0, 3);
                                        func_8006C598MainLoop(0, -0x78, -2);
                                        screenResult = 1;
                                        D_800A39E4MainLoop = screenResult;
                                        goto finishInput;
                                    confirmMode26:
                                        func_8003F564MainLoop(0, 3);
                                        func_8006C598MainLoop(0, -0x78, -2);
                                        D_800A39E4MainLoop = 7;
                                        func_8005833CMainLoop(
                                            D_800A305BMainLoop);
                                        screenResult = 0xFF;
                                        goto finishInput;
                                    }
                                    goto finishInput;
                                }
                                if (currentPadZero &
                                    ((u16)previousPadInverse & 0x10)) {
                                    if (D_800A39E4MainLoop == 7) {

                                        if (D_800A3950MainLoop == 0xFB) {
                                            func_8003F564MainLoop(0, 4);
                                            D_800A39E4MainLoop = 0x26;
                                            D_800A3808MainLoopSite51[0] = 0x16;
                                            func_8006D8E8MainLoop(0);
                                            func_8006C5E4MainLoop(3);
                                            func_8006C598MainLoop(-0x78, 0, 2);
                                        }
                                    } else {
                                        screenResult = func_80056B0CMainLoop(
                                            (s32)D_800A39E4MainLoop,
                                            (s32)D_800A3950MainLoop);
                                        if (screenResult & 0xFF) {
                                            func_8003F564MainLoop(0, 4);

                                        } else {
                                            goto storePadStates;
                                        }
                                    }
                                    goto finishInput;
                                }
                                if (currentPadZero &
                                    ((u16)previousPadInverse & 0x80)) {
                                    register s32 cancelPivot asm("v0");
                                    register s32 cancelMode asm("v1");
                                    cancelPivot = 0x25;
                                    asm("" : : "r"(cancelPivot));
                                    cancelMode = D_800A39E4MainLoop;
                                    asm("" : : "r"(cancelMode));
                                    switch (cancelMode) {
                                    case 0xFC:
                                        if (D_800A3808MainLoop[0] != two &&
                                            D_800A3928MainLoop == 0) {
                                            register s32 cardStatus asm("v0");
                                            func_8003F564MainLoop(0, 3);
                                            func_800599E4MainLoop();
                                            func_80069F30MainLoop();
                                            cardStatus =
                                                func_80069EB8MainLoop() & 0xFF;
                                            if (cardStatus == 0) {
                                                cardStatus = 4;
                                            } else {
                                                cardStatus = 0x13;
                                            }
                                            asm("" : : "r"(cardStatus));
                                            D_800A3808MainLoop[0] = cardStatus;
                                            func_800598C4MainLoop();
                                            cardOperation = 1;
                                        startCardOperation:
                                            func_8006D8E8MainLoop(
                                                cardOperation);
                                            D_800A3928MainLoop = one;
                                        }
                                        break;
                                    case 0x23:
                                        if (D_800A3928MainLoop == 0) {
                                            if (D_800A3808MainLoop[0] ==
                                                    mode13 ||
                                                (u32)(D_800A3808MainLoop[0] -
                                                      0x19) < 2U) {
                                                func_8003F564MainLoop(0, 3);
                                                func_800599E4MainLoop();
                                                if (!(func_80069EB8MainLoop() &
                                                      0xFF)) {
                                                    D_800A3808MainLoop[0] = 4;
                                                    func_8006D8E8MainLoop(0);
                                                    D_800A3928MainLoop = one;
                                                    func_80069AFCMainLoop(0xA);
                                                } else {
                                                    func_800598C4MainLoop();
                                                checkCardMenuReady:
                                                    if (D_800A3808MainLoop[0] ==
                                                        0) {
                                                        func_8006D0F0MainLoop();
                                                        func_8006D8E8MainLoop(
                                                            0);
                                                        D_800A3928MainLoop =
                                                            one;
                                                        func_80069AFCMainLoop(
                                                            0xA);
                                                    }
                                                }
                                            } else {
                                                goto playBackSound;
                                            }
                                        }
                                        break;
                                    case 0x24:
                                    playBackSound:
                                        returnChannel = 0;
                                        actionSound = 4;
                                    returnMainMenu:
                                        asm(""
                                            :
                                            : "r"(returnChannel),
                                              "r"(actionSound));
                                        func_8003F564MainLoop(returnChannel,
                                                              actionSound);
                                        func_8006C598MainLoop(0, -0x78, -2);
                                    finishMainMenuReturn:
                                        D_800A39E4MainLoop = one;
                                        func_80069AFCMainLoop(1);
                                        break;
                                    case 0x22:
                                    case 0x28:
                                        goto playBackSound;
                                    case 0x25:
                                    case 0x27:
                                        func_8003F564MainLoop(0, 4);
                                        func_8006C598MainLoop(0, -0x78, -2);
                                        D_800A39E4MainLoop = one;
                                        break;
                                    case 0x26:
                                        func_8003F564MainLoop(0, 4);
                                        func_8006C598MainLoop(0, -0x78, -2);
                                        D_800A39E4MainLoop = 7;
                                        break;
                                    }
                                    goto finishInput;
                                }
                                /* End the old register lifetime before setting the pad index. */
                                asm volatile("" : "=r"(index));
                                index = player & 0xFF;
                                padBits = newPad[index];
                                if (padBits &
                                    ((u16)previousPadInverse & 0x20)) {

                                    if (D_800A39E4MainLoop == 0x23) {
                                        func_8006CE64MainLoop();
                                    }
                                    goto finishInput;
                                }
                                if (padBits & 0x1000) {
                                    register s32 padEdgeUp asm("v0");
                                    register s32 blockedModeUp asm("v0");
                                    register s32 cardModeUp asm("v0");
                                    register s32 rawModeUp asm("a0");
                                    register s32 modeUp asm("v1");
                                    blockedModeUp = 0x21;
                                    asm(""
                                        : "=r"(blockedModeUp)
                                        : "0"(blockedModeUp));
                                    /* Retain the raw mode byte and its comparison value. */
                                    asm volatile(
                                        "lbu\t%0,D_800A39E4.MainLoop\n\tnop\n\tandi\t%1,%0,0xff"
                                        : "=r"(rawModeUp), "=r"(modeUp)
                                        : "m"(D_800A39E4MainLoop));
                                    if ((modeUp != blockedModeUp) &&
                                        (modeUp != 0xFC) &&
                                        ((u32)(rawModeUp - 0x25) >= 2U) &&
                                        (modeUp != mode13) &&
                                        (modeUp != 0x27) && (modeUp != 0xE)) {
                                        if (((u32)(rawModeUp - 9) < 2U) ||
                                            (modeUp == 0xC) ||
                                            ((u32)(rawModeUp - 0x10) < 2U)) {
                                            asm("" : : "r"(rawModeUp));
                                            func_80068AC4MainLoop(newPad[0],
                                                                  oldPad[0], 1);

                                            goto finishInput;
                                        }
                                        cardModeUp = 0x23;
                                        asm(""
                                            : "=r"(cardModeUp)
                                            : "0"(cardModeUp), "r"(rawModeUp));
                                        if (modeUp == cardModeUp) {
                                            if (D_800A3928MainLoop == one) {
                                                goto nextPlayer;
                                            }
                                            if (D_800A3770MainLoopSite57[0] !=
                                                0) {
                                                goto nextPlayer;
                                            }
                                            menuDirection = 1;
                                            goto moveCardCursor;
                                        }
                                        padEdgeUp = previousPadInverse & 0x1000;
                                        asm(""
                                            : "=r"(padEdgeUp)
                                            : "0"(padEdgeUp));
                                        if (currentPadZero & padEdgeUp) {
                                            if ((modeUp == 0x22) ||
                                                (modeUp == 0x24) ||
                                                (modeUp == 0x28)) {
                                                if (D_800A3770MainLoopSite58
                                                        [0] == 0) {
                                                    if (func_8006C700MainLoop(
                                                            0,
                                                            D_800A39E4MainLoop ==
                                                                0x22) &
                                                        0xFF) {
                                                        func_8003F564MainLoop(
                                                            0, 0);

                                                    } else {
                                                        goto storePadStates;
                                                    }
                                                    goto finishInput;
                                                }
                                            } else {
                                                func_8003F564MainLoop(0, 0);
                                                wrappedItemUp =
                                                    D_800A3059MainLoop;
                                                if (wrappedItemUp == 0) {
                                                    wrappedItemUp =
                                                        D_800A38E8MainLoopSite59
                                                            [0] -
                                                        1;
                                                } else {
                                                    wrappedItemUp -= 1;
                                                }
                                                asm("" : : "r"(wrappedItemUp));
                                                D_800A3059MainLoop =
                                                    wrappedItemUp;
                                                asm volatile(
                                                    ""
                                                    :
                                                    : "m"(D_800A3059MainLoop)
                                                    : "memory");
                                                if (D_800A39E4MainLoop == two) {

                                                    if (D_800A3988MainLoopSmall ==
                                                        0) {
                                                        if ((u32)(D_800A3059MainLoopPostUp -
                                                                  4) < 2U) {
                                                            D_800A3059MainLoopPostUp =
                                                                3;

                                                        } else {
                                                            goto storePadStates;
                                                        }
                                                    }
                                                    goto finishInput;
                                                }
                                                if ((D_800A39E4MainLoop ==
                                                     one) &&
                                                    (D_800A3950MainLoop == 0)) {

                                                    if ((u32)(D_800A3059MainLoopPostUp -
                                                              2) < 4U) {
                                                        D_800A3059MainLoopPostUp =
                                                            one;

                                                    } else {
                                                        goto finishInput;
                                                    }
                                                } else {
                                                    if (D_800A39E4MainLoop ==
                                                        3) {

                                                        if (D_800A3644MainLoop !=
                                                            0) {
                                                            itemUp =
                                                                D_800A3059MainLoopPostUp &
                                                                0xFF;
                                                            if (itemUp == 3) {
                                                                D_800A3059MainLoopPostUp -=
                                                                    2;

                                                            } else if (itemUp ==
                                                                       two) {
                                                                D_800A3059MainLoopPostUp -=
                                                                    1;

                                                            } else {
                                                                goto storePadStates;
                                                            }
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if (D_800A39E4MainLoop ==
                                                        4) {
                                                        itemCursorUp =
                                                            D_800A3059MainLoopPostUp;

                                                        if (D_800A3988MainLoopSite60
                                                                [itemCursorUp &
                                                                 0xFF] &
                                                            0x80) {
                                                            do {
                                                                nextItemUp =
                                                                    itemCursorUp -
                                                                    1;
                                                                D_800A3059MainLoopPostUp =
                                                                    nextItemUp;
                                                                itemCursorUp =
                                                                    nextItemUp;
                                                            } while (
                                                                D_800A3988MainLoopSite61
                                                                    [nextItemUp &
                                                                     0xFF] &
                                                                0x80);
                                                        }
                                                        goto finishInput;
                                                    }

                                                    if (D_800A39E4MainLoop ==
                                                        5) {

                                                        if (D_800A3059MainLoopPostUp ==
                                                            5) {

                                                            if (D_800A3076MainLoop ==
                                                                0) {
                                                                D_800A3059MainLoopPostUp -=
                                                                    1;
                                                            }
                                                            goto finishInput;
                                                        }
                                                    } else {
                                                        goto finishInput;
                                                    }
                                                }
                                                goto updatePreviousPad;
                                            }
                                        } else {
                                            goto storePadStates;
                                        }
                                        goto nextPlayer;
                                    }
                                    goto nextPlayer;
                                }
                                if (padBits & 0x4000) {
                                    register s32 padEdgeDown asm("v0");
                                    register s32 blockedModeDown asm("v0");
                                    register s32 cardModeDown asm("v0");
                                    register s32 rawModeDown asm("a0");
                                    register s32 modeDown asm("v1");
                                    blockedModeDown = 0x21;
                                    asm(""
                                        : "=r"(blockedModeDown)
                                        : "0"(blockedModeDown));
                                    /* Retain the raw mode byte and its comparison value. */
                                    asm volatile(
                                        "lbu\t%0,D_800A39E4.MainLoop\n\tnop\n\tandi\t%1,%0,0xff"
                                        : "=r"(rawModeDown), "=r"(modeDown)
                                        : "m"(D_800A39E4MainLoop));
                                    if ((modeDown != blockedModeDown) &&
                                        (modeDown != 0xFC) &&
                                        ((u32)(rawModeDown - 0x25) >= 2U) &&
                                        (modeDown != mode13) &&
                                        (modeDown != 0x27) &&
                                        (modeDown != 0xE)) {
                                        if (((u32)(rawModeDown - 9) < 2U) ||
                                            (modeDown == 0xC) ||
                                            ((u32)(rawModeDown - 0x10) < 2U)) {
                                            asm("" : : "r"(rawModeDown));
                                            func_80068AC4MainLoop(newPad[0],
                                                                  oldPad[0], 0);

                                            goto finishInput;
                                        }
                                        cardModeDown = 0x23;
                                        asm(""
                                            : "=r"(cardModeDown)
                                            : "0"(cardModeDown),
                                              "r"(rawModeDown));
                                        if (modeDown == cardModeDown) {
                                            if (D_800A3928MainLoop == one) {
                                                goto nextPlayer;
                                            }
                                            if (D_800A3770MainLoopSite62[0] !=
                                                0) {
                                                goto nextPlayer;
                                            }
                                            menuDirection = 0;
                                        moveCardCursor:
                                            player += 1;
                                            func_8006CB80MainLoop(
                                                menuDirection);
                                            oldPad[0] = newPad[0];
                                        } else {
                                            padEdgeDown =
                                                previousPadInverse & 0x4000;
                                            asm(""
                                                : "=r"(padEdgeDown)
                                                : "0"(padEdgeDown));
                                            if (currentPadZero & padEdgeDown) {
                                                if ((modeDown == 0x22) ||
                                                    (modeDown == 0x24) ||
                                                    (modeDown == 0x28)) {
                                                    if (D_800A3770MainLoopSite63
                                                            [0] == 0) {
                                                        if (func_8006C700MainLoop(
                                                                1,
                                                                D_800A39E4MainLoop ==
                                                                    0x22) &
                                                            0xFF) {
                                                            func_8003F564MainLoop(
                                                                0, 1);

                                                        } else {
                                                            goto storePadStates;
                                                        }
                                                        goto finishInput;
                                                    }
                                                } else {
                                                    func_8003F564MainLoop(0, 1);
                                                    if ((D_800A3059MainLoop &
                                                         0xFF) ==
                                                        (D_800A38E8MainLoopSite64
                                                             [0] -
                                                         1)) {
                                                        D_800A3059MainLoop = 0;
                                                    } else {
                                                        D_800A3059MainLoop += 1;
                                                    }
                                                    if (D_800A39E4MainLoop ==
                                                        two) {

                                                        if (D_800A3988MainLoopSmall ==
                                                            0) {

                                                            if (D_800A3059MainLoopPostDown ==
                                                                4) {
                                                                /* Keep the two skip paths separate until the store. */
                                                                asm volatile(
                                                                    ""
                                                                    :
                                                                    :
                                                                    : "memory");
                                                                goto skipLockedItems;
                                                            }
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if ((D_800A39E4MainLoop ==
                                                         one) &&
                                                        (D_800A3950MainLoop ==
                                                         0)) {
                                                        if ((u32)(D_800A3059MainLoopPostDown -
                                                                  2) < 4U) {
                                                        skipLockedItems:
                                                            D_800A3059MainLoopPostDown =
                                                                6;

                                                        } else {
                                                            goto storePadStates;
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if (D_800A39E4MainLoop ==
                                                        3) {

                                                        if (D_800A3644MainLoop !=
                                                            0) {
                                                            itemDown =
                                                                D_800A3059MainLoopPostDown &
                                                                0xFF;
                                                            if (itemDown ==
                                                                two) {
                                                                D_800A3059MainLoopPostDown +=
                                                                    2;

                                                            } else if (
                                                                itemDown ==
                                                                D_800A39E4MainLoop) {
                                                                D_800A3059MainLoopPostDown +=
                                                                    1;

                                                            } else {
                                                                goto storePadStates;
                                                            }
                                                        }
                                                        goto finishInput;
                                                    }
                                                    if (D_800A39E4MainLoop ==
                                                        4) {
                                                        itemCursorDown =
                                                            D_800A3059MainLoopPostDown;

                                                        if (D_800A3988MainLoopSite65
                                                                [itemCursorDown &
                                                                 0xFF] &
                                                            0x80) {
                                                            do {
                                                                nextItemDown =
                                                                    itemCursorDown +
                                                                    1;
                                                                D_800A3059MainLoopPostDown =
                                                                    nextItemDown;
                                                                itemCursorDown =
                                                                    nextItemDown;
                                                            } while (
                                                                D_800A3988MainLoopSite66
                                                                    [nextItemDown &
                                                                     0xFF] &
                                                                0x80);
                                                        }
                                                        goto finishInput;
                                                    }

                                                    if (D_800A39E4MainLoop !=
                                                        5) {
                                                        goto finishInput;
                                                    }
                                                    if (D_800A3059MainLoopPostDown !=
                                                        D_800A39E4MainLoop) {
                                                        goto finishInput;
                                                    }
                                                    if (D_800A3076MainLoop !=
                                                        0) {
                                                        goto finishInput;
                                                    }
                                                    D_800A3059MainLoopPostDown =
                                                        0;
                                                    goto updatePreviousPad;
                                                }
                                            } else {
                                                goto storePadStates;
                                            }
                                            goto nextPlayer;
                                        }
                                    } else {
                                        goto nextPlayer;
                                    }
                                } else {
                                    if (padBits & 0x8000) {
                                        if (D_800A39E4MainLoop == mode13 &&
                                            (padBits &
                                             ((u16)~oldPad[index] & 0x8000))) {
                                            if (!(func_8004229CMainLoop(
                                                      (u8)D_800A3A24MainLoopSite68
                                                          [index]) &
                                                  0xFF) ||
                                                D_800A3684MainLoopSite67
                                                        [index] != one) {
                                                if (D_800A3684MainLoopSite69
                                                        [index] == 0) {
                                                    func_8003F564MainLoop(0, 2);
                                                    {
                                                        register s32
                                                            variantCount asm(
                                                                "a0");
                                                        register s32
                                                            variantValue asm(
                                                                "v0");
                                                        register s32
                                                            countMinusOne asm(
                                                                "v1");
                                                        register s32
                                                            variantRemainder asm(
                                                                "v1");
                                                        variantCount =
                                                            D_800A3080MainLoopSite70
                                                                [D_800A3A24MainLoopSite71
                                                                     [index]];
                                                        asm(""
                                                            :
                                                            : "r"(
                                                                variantCount));
                                                        variantValue =
                                                            D_800A307CMainLoopSite72
                                                                [index];
                                                        countMinusOne =
                                                            variantCount - 1;
                                                        asm(""
                                                            :
                                                            : "r"(variantValue),
                                                              "r"(countMinusOne));
                                                        variantValue +=
                                                            countMinusOne;
                                                        asm(""
                                                            :
                                                            : "r"(
                                                                variantValue));
                                                        variantRemainder =
                                                            variantValue %
                                                            variantCount;
                                                        asm(""
                                                            :
                                                            : "r"(
                                                                variantRemainder));
                                                        D_800A307CMainLoopSite72
                                                            [index] =
                                                                variantRemainder;
                                                    }
                                                }
                                            }
                                        } else if (D_800A39E4MainLoop == two &&
                                                   D_800A3059MainLoop == one) {
                                            func_80055C78MainLoop(
                                                2, 1, 1, newPad[player & 0xFF],
                                                oldPad[player & 0xFF],
                                                player & 0xFF);
                                        } else {
                                            func_80055C78MainLoop(
                                                D_800A39E4MainLoop,
                                                D_800A3059MainLoop, 1,
                                                newPad[0], oldPad[0],
                                                activePlayer);
                                        }
                                    } else if (padBits & 0x2000) {
                                        if (D_800A39E4MainLoop == mode13 &&
                                            (padBits &
                                             ((u16)~oldPad[index] & 0x2000))) {
                                            if (!(func_8004229CMainLoop(
                                                      (u8)D_800A3A24MainLoopSite74
                                                          [index]) &
                                                  0xFF) ||
                                                D_800A3684MainLoopSite73
                                                        [index] != one) {
                                                if (D_800A3684MainLoopSite75
                                                        [index] == 0) {
                                                    func_8003F564MainLoop(0, 2);
                                                    D_800A307CMainLoopSite76[index] =
                                                        (D_800A307CMainLoopSite76
                                                             [index] +
                                                         1) %
                                                        D_800A3080MainLoopSite77
                                                            [D_800A3A24MainLoopSite78
                                                                 [index]];
                                                }
                                            }
                                        } else if (D_800A39E4MainLoop == two &&
                                                   D_800A3059MainLoop == one) {
                                            func_80055C78MainLoop(
                                                2, 1, 0, newPad[player & 0xFF],
                                                oldPad[player & 0xFF],
                                                player & 0xFF);
                                        } else {
                                            func_80055C78MainLoop(
                                                D_800A39E4MainLoop,
                                                D_800A3059MainLoop, 0,
                                                newPad[0], oldPad[0],
                                                activePlayer);
                                        }
                                    }
                                storePadStates:
                                finishInput:

                                updatePreviousPad:
                                    oldPad[player & 0xFF] =
                                        newPad[player & 0xFF];
                                    goto nextPlayer;
                                }
                            }
                        } else {
                        nextPlayer:
                            player += 1;
                        }
                        index = (u8)player;
                    } while ((u32)(player & 0xFF) < 2U);
                }
            } while (!(screenResult & 0xFF));
        }
        DrawSyncMainLoop(0);
        if (D_800A39E4MainLoop == 7) {
            func_80057DE8MainLoop();
        }
        screenResultByte = screenResult & 0xFF;
        if (D_800A39E4MainLoop != 0xFD) {
            nextScreen = func_800571ECMainLoop(
                D_800A39E4MainLoop, &D_800A3950MainLoop, screenResultByte);
            D_800A39E4MainLoop = nextScreen;
            if ((nextScreen & 0xFF) == 7) {
                activePlayer = 0;
            }
            if ((D_800A3950MainLoop == 7) && !(activePlayer & 0xFF) &&
                (D_800A3644MainLoop != 0) && (*D_800A3A25MainLoopSite79 != 0) &&
                (screenResultByte != 0xFF)) {
                activePlayer = 1;
                D_800A3950MainLoop = nextScreen;
                D_800A39E4MainLoop = 7;
                D_800A3059MainLoop = 0;
            }
        }
        if ((D_800A39E4MainLoop == 0xFF) || (D_800A39E4MainLoop == 0xFD) ||
            (D_800A39E4MainLoop == 0xF8)) {
            exitLoop = 1;
        }
    } while (exitLoop == 0);
    VSyncMainLoop(0);
    VSyncMainLoop(0);
    do {

    } while (func_8003F4FCMainLoop(0) & 0xFF);
}

void func_80055AA4(u8 arg0, s32 arg1) {
    extern u8 D_800A3644NM asm("D_800A3644.NON_MATCHING");
    extern u8 D_800A3980[];
    extern u8 D_800A36E0[];
    extern u8 D_8009AD40[];
    extern char *D_8009AC1CR[] asm("D_8009AC1C.NON_MATCHING");
    extern char D_800BB9B4[];
    extern void func_800636EC(u8, u8);
    extern void func_80063AE0(s32, s32);
    u8 other;
    u8 val;

    other = arg0 ^ 1;
    if ((u8)arg1 != 0) {
        val = (D_800A3980[arg0] + 23) % 24;
        D_800A3980[arg0] = val;
        if (D_800A3644NM != 0 && val == D_800A3980[other]) {
            val = (val + 23) % 24;
            D_800A3980[arg0] = val;
        }
    } else {
        val = (D_800A3980[arg0] + 1) % 24;
        D_800A3980[arg0] = val;
        if (D_800A3644NM != 0 && val == D_800A3980[other]) {
            val = (val + 1) % 24;
            D_800A3980[arg0] = val;
        }
    }
    D_800A36E0[arg0] = D_8009AD40[D_800A3980[arg0]];
    func_800636EC(arg0, D_800A36E0[arg0]);
    func_80063AE0(arg0, D_800A36E0[arg0]);
    strcpy(&D_800BB9B4[arg0 * 24], D_8009AC1CR[D_800A36E0[arg0]]);
}

/* The repeated label aliases keep gcc from caching addresses that retail
 * reloads, and func_80055AA4B stops cross-jumping from merging the two
 * func_80055AA4 calls. func_80063694KR is unprototyped on purpose: retail
 * passes its first argument without narrowing it to u8.
 */
void func_80055C78(u8 arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4, u8 arg5) {
    extern u8 D_800A3644NM asm("D_800A3644.NON_MATCHING");
    extern u8 D_800A3988NM asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3073NM asm("D_800A3073.NON_MATCHING");
    extern s8 D_800A3078NM asm("D_800A3078.NON_MATCHING");
    extern u8 D_800A305BSmall;
    extern u8 D_800A2F95NM[] asm("D_800A2F95.NON_MATCHING");
    extern s8 D_800A3A14NM[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R2[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R3[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R4[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R5[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R6[] asm("D_800A3A14.NON_MATCHING");
    extern s8 D_800A3A14R7[] asm("D_800A3A14.NON_MATCHING");
    extern u8 *D_800A38FCR2[] asm("D_800A38FC.NON_MATCHING");
    extern u8 *D_800A38FCR3[] asm("D_800A38FC.NON_MATCHING");
    extern u8 *D_800A38FCR4[] asm("D_800A38FC.NON_MATCHING");
    extern u8 *D_800A39A0R2[] asm("D_800A39A0.NON_MATCHING");
    extern u8 *D_800A39A0R3[] asm("D_800A39A0.NON_MATCHING");
    extern s8 D_800A39FCR2[] asm("D_800A39FC.NON_MATCHING");
    extern s8 D_800A3594R2[] asm("D_800A3594.NON_MATCHING");
    extern s8 D_800A3944R2[] asm("D_800A3944.NON_MATCHING");
    extern s8 D_800A3944R3[] asm("D_800A3944.NON_MATCHING");
    extern s8 D_800A3944R4[] asm("D_800A3944.NON_MATCHING");
    extern s8 D_800A39DCR2[] asm("D_800A39DC.NON_MATCHING");
    extern s8 D_800A39DCR3[] asm("D_800A39DC.NON_MATCHING");
    extern u8 D_800A3894R2[] asm("D_800A3894.NON_MATCHING");
    extern u8 D_800A3A58NM[] asm("D_800A3A58.NON_MATCHING");
    extern u16 D_800A3690NM[] asm("D_800A3690.NON_MATCHING");
    extern s32 D_800A37D0NM asm("D_800A37D0.NON_MATCHING");
    extern u8 D_800A3988[];
    extern u8 D_800A3988B[] asm("D_800A3988");
    extern u8 D_800A3988C[] asm("D_800A3988");
    extern u8 D_800A3988D[] asm("D_800A3988");
    extern u8 D_800A3988E[] asm("D_800A3988");
    extern u8 D_800A3988F[] asm("D_800A3988");
    extern u8 D_800A3988G[] asm("D_800A3988");
    extern u8 D_800A3988H[] asm("D_800A3988");
    extern u8 D_800A3988I[] asm("D_800A3988");
    extern u8 D_800A3988J[] asm("D_800A3988");
    extern u8 D_800A3988K[] asm("D_800A3988");
    extern u8 D_800A3988L[] asm("D_800A3988");
    extern u8 D_800A3988M[] asm("D_800A3988");
    extern u8 D_800A3988N[] asm("D_800A3988");
    extern u8 D_800A3988O[] asm("D_800A3988");
    extern u8 D_800A3988P[] asm("D_800A3988");
    extern u8 D_800A3988Q[] asm("D_800A3988");
    extern u8 D_800A3988R[] asm("D_800A3988");
    extern u8 D_800A3988S[] asm("D_800A3988");
    extern u8 D_800A3068Pair[][2] asm("D_800A3068");
    extern u8 D_800A3074;
    extern u8 D_800A3076;
    extern u8 D_800A3077;
    extern u8 D_800A306C;
    extern u8 D_800A306DNM asm("D_800A306D.NON_MATCHING");
    extern u8 D_800A306E;
    extern u8 D_800A306F;
    extern u8 D_800A3070;
    extern u8 D_800A3071;
    extern u8 D_800A3072;
    extern u8 D_800A3928;
    extern s32 D_800A37F0;
    extern s32 D_800A3830;
    extern u8 D_8009957C[];
    extern s32 D_800AE178[];
    extern u8 D_80099568[][6];
    extern u8 D_800A331C[];
    extern u8 D_80099574[];
    extern u8 D_8009AD40[];
    extern s32 D_800A3744[] asm("D_800A3744.NON_MATCHING");
    extern s32 D_800A360C[] asm("D_800A360C.NON_MATCHING");
    extern s32 D_800A37D4[] asm("D_800A37D4.NON_MATCHING");
    extern s32 D_800A3870[] asm("D_800A3870.NON_MATCHING");
    extern u8 *D_800A39A0[];
    extern u8 *D_800A38FC[];
    extern s8 D_800A3594[];
    extern s8 D_800A3594W[] asm("D_800A3594.NON_MATCHING");
    extern s8 D_800A3860Signed[][4] asm("D_800A3860");
    extern s8 D_800A39DC[] asm("D_800A39DC.NON_MATCHING");
    extern s8 D_800A3944[] asm("D_800A3944.NON_MATCHING");
    extern u8 D_800A3894[];
    extern u8 D_800A3894W[] asm("D_800A3894.NON_MATCHING");
    extern s8 D_800A3944W[] asm("D_800A3944.NON_MATCHING");
    extern s8 D_800A39FC[];
    extern s32 func_8005CA4C(void);
    extern void func_80055AA4(u8, s32);
    extern void func_80055AA4B(u8, s32) asm("func_80055AA4");
    extern void func_8005C8D8(s32);
    extern s32 func_8005CCEC(u8, s32);
    extern void func_8005CC34(void);
    extern void func_8005CEDC(void);
    extern void func_8005E4A4(s32);
    extern void func_8005ED04(u8);
    extern void func_8005EC5C(u8);
    extern void func_80060008(u8);
    extern void func_80063694KR() asm("func_80063694");
    extern void func_800645A4(s8, s8);
    extern void func_80063AE0(s32, s32);
    extern void func_80067F34(s8, u8);
    extern void func_8006894C(s8, s32, s32, s32, s32);
    extern void func_80060F54(s16, s32);
    extern void func_8006CF90(u8);
    extern void ListSetRangeFields(struct UnkNode1C *, s32, s32, s16);
    s32 limit;
    s32 value;
    s32 tableByte;
    u8 changed;

    if (arg0 != 4) {
        if (arg0 != 7) {
            if (arg0 != 0x21) {
                if (arg0 != 0xB) {
                    goto checkButtons;
                }
            }
        }
    }
    if (arg0 == 4) {
        if ((arg1 & 0xFF) != 0) {
            goto checkButtons;
        }
    }
    if (arg0 == 7) {
        if ((arg1 & 0xFF) < 2U) {
            goto checkButtons;
        }
        if ((arg1 & 0xFF) == 6) {
            goto checkButtons;
        }
    }
    if (arg0 == 0xB) {
        if ((arg1 & 0xFF) == 0) {
            goto checkButtons;
        }
    }
    goto repeatProcessing;
checkButtons:
    if ((arg3 & ((u16)~arg4 & 0x8000)) == 0) {
        if ((arg3 & ((u16)~arg4 & 0x2000)) == 0) {
            return;
        }
    }
    goto dispatch;
repeatProcessing:
    switch (arg0) {
    case 7:
    case 0x21:
        limit = 5;
        break;
    default:
        limit = 0xF;
        break;
    }
    if ((arg3 & ~arg4) != 0) {
        D_800A3830 = 0;
        D_800A37F0 = 1;
    } else {
        D_800A3830 = D_800A3830 + 1;
        if (limit >= D_800A3830) {
            return;
        }
        D_800A37F0 = D_800A37F0 + D_800A37F0 / 2;
    }
dispatch:
    switch (arg0) {
    case 2:
        switch (arg1 & 0xFF) {
        case 0:
            if ((func_8005CA4C() & 0xFF) == 0) {
                return;
            }
            break;
        case 1:
            func_80055AA4(arg5, arg2);
            break;
        case 2:
            if (arg2 != 0) {
                if (D_800A305BSmall != 0) {
                    D_800A305BSmall = D_800A305BSmall - 1;
                } else {
                    D_800A305BSmall = 0x10;
                }
                while (D_8009957C[D_800A305BSmall] == 0) {
                    if (D_800A305BSmall != 0) {
                        D_800A305BSmall = D_800A305BSmall - 1;
                    } else {
                        D_800A305BSmall = 0x10;
                    }
                }
            } else {
                if (D_800A305BSmall < 0x10) {
                    D_800A305BSmall = D_800A305BSmall + 1;
                } else {
                    D_800A305BSmall = 0;
                }
                while (D_8009957C[D_800A305BSmall] == 0) {
                    if (D_800A305BSmall < 0x10) {
                        D_800A305BSmall = D_800A305BSmall + 1;
                    } else {
                        D_800A305BSmall = 0;
                    }
                }
            }
            func_8005E4A4(D_800AE178[D_800A305BSmall]);
            func_8005ED04(D_800A305BSmall);
            func_8005EC5C(D_800A305BSmall);
            break;
        case 4:
            arg1 = arg1 & 0xFF;
            D_800A3988[arg1] = D_800A3988B[arg1] ^ 1;
            func_8005C8D8(arg1);
            D_800A3074 = (D_800A3988C[arg1] == 0);
            break;
        case 5:
            arg1 = arg1 & 0xFF;
            D_800A3988D[arg1] = D_800A3988E[arg1] ^ 1;
            func_8005C8D8(arg1);
            D_800A3073NM = (D_800A3988F[arg1] == 0);
            break;
        default:
            return;
        }
        break;
    case 8:
        if ((arg1 & 0xFF) != 0) {
            return;
        }
        func_80055AA4B(0, arg2);
        break;
    case 4:
        switch (arg1 & 0xFF) {
        case 0:
            if (arg2 != 0) {
                value = D_800A37D0NM - D_800A37F0;
                if (value < 3) {
                    D_800A37D0NM = 3;
                } else {
                    D_800A37D0NM = value;
                    func_8003F564(0, 2);
                }
            } else {
                value = D_800A37D0NM + D_800A37F0;
                if (value < 0x65) {
                    D_800A37D0NM = value;
                    func_8003F564(0, 2);
                } else {
                    D_800A37D0NM = 0x64;
                }
            }
            func_8005CC34();
            func_8005EC5C(D_800A305BSmall);
            return;
        case 1:
            if (arg2 != 0) {
                if (D_800A3988G[1] != 0) {
                    D_800A3988[1] = D_800A3988G[1] - 1;
                } else {
                    D_800A3988[1] = 2;
                }
            } else {
                if (D_800A3988G[1] == 2) {
                    D_800A3988[1] = 0;
                } else {
                    D_800A3988[1] = D_800A3988G[1] + 1;
                }
            }
            func_8005C8D8(1);
            switch (D_800A3988H[1]) {
            case 1:
                D_800A306E = 0;
                break;
            case 0:
                D_800A306E = 1;
                break;
            case 2:
                D_800A306E = 2;
                break;
            }
            if (D_800A306E == 1) {
                if (D_800A3644NM != 0) {
                    D_800A3071 = 0;
                    D_800A3988[2] = 0x81;
                } else {
                    D_800A3071 = 1;
                    D_800A3988[2] = 0;
                }
                D_800A306F = 1;
                D_800A3988[3] = 0;
            } else {
                D_800A3071 = 0;
                D_800A306F = 0;
                D_800A3988[2] = 0x81;
                D_800A3988[3] = 0x81;
            }
            func_8005C8D8(2);
            func_8005C8D8(3);
            break;
        case 2:
            if (D_800A306E == 1 && D_800A3644NM == 0) {
                D_800A3988[2] = D_800A3988I[2] ^ 1;
                func_8005C8D8(2);
                if (D_800A3988J[2] != 0) {
                    D_800A3071 = 0;
                } else {
                    D_800A3071 = 1;
                }
            }
            break;
        case 3:
            if (D_800A306E == 1) {
                D_800A3988[3] = D_800A3988K[3] ^ 1;
                func_8005C8D8(3);
                if (D_800A3988L[3] != 0) {
                    D_800A306F = 0;
                } else {
                    D_800A306F = 1;
                }
            }
            break;
        case 4:
        case 5:
            arg1 = arg1 & 0xFF;
            D_800A3988M[arg1] = D_800A3988N[arg1] ^ 1;
            func_8005C8D8(arg1);
            if (D_800A3988O[arg1] != 0) {
                switch (arg1) {
                case 4:
                    D_800A3070 = 0;
                    break;
                case 5:
                    D_800A3072 = 0;
                    break;
                }
            } else {
                switch (arg1) {
                case 4:
                    D_800A3070 = 1;
                    break;
                case 5:
                    D_800A3072 = 1;
                    break;
                }
            }
            break;
        default:
            return;
        }
        break;
    case 0xB:
        changed = 1;
        switch (arg1 & 0xFF) {
        case 0:
            if (arg2 != 0) {
                D_800A3988NM = (D_800A3988NM + 2) % 3;
            } else {
                D_800A3988NM = (D_800A3988NM + 1) % 3;
            }
            for (arg1 = 0; arg1 < 5; arg1++) {
                D_800A331C[arg1] = D_80099568[D_800A3988NM][arg1];
            }
            D_800A3078NM = D_800A3988NM;
            break;
        case 6:
            return;
        default:
            if (D_800A3078NM != 2) {
                D_800A3078NM = 2;
                D_800A3988NM = 2;
            }
            if (arg2 != 0) {
                changed = func_8005CCEC(arg1 & 0xFF, -D_800A37F0);
            } else {
                changed = func_8005CCEC(arg1 & 0xFF, D_800A37F0);
            }
            break;
        }
        if (D_800A3078NM == 2) {
            for (arg1 = 0; arg1 < 5; arg1++) {
                D_80099574[arg1] = D_800A331C[arg1];
            }
        }
        func_8005CEDC();
        if ((changed & 0xFF) == 0) {
            return;
        }
        break;
    case 5:
        switch (arg1 & 0xFF) {
        case 1:
            D_800A3988P[1] = D_800A3988[1] ^ 1;
            D_800A306C = D_800A306C ^ 1;
            func_8005C8D8(1);
            if (D_800A306DNM != 0) {
                D_800A2F95NM[0] = 0;
                SsSetMono();
            } else {
                D_800A2F95NM[0] = 1;
                SsSetStereo();
            }
            break;
        case 5:
            if (D_800A3076 == 0) {
                return;
            }
            D_800A3988Q[5] = D_800A3988R[5] ^ 1;
            func_8005C8D8(5);
            if (D_800A3988S[5] != 0) {
                D_800A3077 = 0;
            } else {
                D_800A3077 = 1;
            }
            break;
        default:
            return;
        }
        break;
    case 7:
        if ((arg1 & 0xFF) < 0) {
            return;
        }
        if ((arg1 & 0xFF) < 2) {
            D_800A3988[arg1 & 0xFF] = D_800A3988B[arg1 & 0xFF] ^ 1;
            D_800A3068Pair[arg5][arg1 & 0xFF] =
                D_800A3068Pair[arg5][arg1 & 0xFF] ^ 1;
            func_8005C8D8(arg1 & 0xFF);
            break;
        }
        if ((arg1 & 0xFF) >= 6) {
            return;
        }
        if (arg2 != 0) {
            D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] =
                D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] - D_800A37F0;
            if ((s8)D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] < 0) {
                D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] = 0;
            } else {
                func_8003F564(0, 2);
            }
            D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] =
                (s8)D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] / 4 * 4;
        } else {
            D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] =
                D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] + D_800A37F0;
            if ((s8)D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] >= 0x40) {
                D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] = 0x3F;
            } else {
                D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] =
                    ((s8)D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] + 3) / 4 * 4;
                if ((s8)D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] >= 0x40) {
                    D_800A3860Signed[arg5][(arg1 & 0xFF) - 2] = 0x3F;
                }
                func_8003F564(0, 2);
            }
        }
        func_80060008(arg5);
        return;
    case 0xE:
        arg1 = D_800A3A14NM[0];
        D_800A39A0[0] = D_800A38FC[0];
        D_800A3A14R2[0] = D_800A3A14NM[0] ^ 1;
        if (arg2 != 0) {
            D_800A3594W[0] = (D_800A3594[0] + 0x17) % 24;
        } else {
            D_800A3594W[0] = (D_800A3594[0] + 1) % 24;
        }
        tableByte = D_8009AD40[D_800A3594R2[0]];
        D_800A39FC[0] = tableByte;
        func_800645A4(D_800A3A14R3[0], (s8)tableByte);
        func_80063AE0(D_800A3A14R4[0], D_800A39FCR2[0]);
        D_800A38FCR2[0] = (u8 *)D_800A3744[D_800A3A14R5[0]];
        if (arg2 == 0) {
            ListSetRangeFields((struct UnkNode1C *)D_800A39A0R3[0], 0, -0x140,
                               -2);
            func_80063694KR(arg1, 0x34, -0x10C, -2);
            ListSetRangeFields((struct UnkNode1C *)D_800A38FCR4[0], 0x140, 0,
                               -2);
            func_80063694KR(D_800A3A14R7[0], 0x174, 0x34, -2);
        } else {
            ListSetRangeFields((struct UnkNode1C *)D_800A39A0R2[0], 0, 0x140,
                               2);
            func_80063694KR(arg1, 0x34, 0x174, 2);
            ListSetRangeFields((struct UnkNode1C *)D_800A38FCR3[0], -0x140, 0,
                               2);
            func_80063694KR(D_800A3A14R6[0], -0x10C, 0x34, 2);
        }
        func_8003F564(0, 2);
        return;
    case 9:
        if (D_800A3A58NM[0] == 0) {
            return;
        }
        D_800A3870[0] = D_800A37D4[0];
        D_800A39DC[0] = D_800A3944[0];
        D_800A3944W[0] = D_800A3944[0] ^ 1;
        if (arg2 != 0) {
            D_800A3894W[0] = (D_800A3894[0] + 0x10) % 17;
        } else {
            D_800A3894W[0] = (D_800A3894[0] + 1) % 17;
        }
        func_80067F34(D_800A3944R2[0], D_800A3894R2[0]);
        D_800A37D4[0] = D_800A360C[D_800A3944R3[0]];
        if (arg2 != 0) {
            func_8006894C(D_800A39DCR2[0], 0, 0x140, 2, 0);
            func_8006894C(D_800A3944R4[0], -0x140, 0, 2, 1);
        } else {
            func_8006894C(D_800A39DCR3[0], 0, -0x140, -2, 0);
            func_8006894C(D_800A3944R4[0], 0x140, 0, -2, 1);
        }
        break;
    case 0x21:
        if (arg2 != 0) {
            D_800A3690NM[arg1 & 0xFF] = D_800A3690NM[arg1 & 0xFF] - D_800A37F0;
            if (*(s16 *)&D_800A3690NM[arg1 & 0xFF] < 0) {
                D_800A3690NM[arg1 & 0xFF] = 0;
            }
        } else {
            D_800A3690NM[arg1 & 0xFF] = D_800A3690NM[arg1 & 0xFF] + D_800A37F0;
            if (*(s16 *)&D_800A3690NM[arg1 & 0xFF] >= 0x65) {
                D_800A3690NM[arg1 & 0xFF] = 0x64;
            }
        }
        func_80060F54(*(s16 *)&D_800A3690NM[arg1 & 0xFF], (arg1 & 0xFF) - 2);
        return;
    case 0x23:
        func_8006CF90(arg2);
        if (D_800A3928 == 0) {
            break;
        }
        return;
    case 0:
    case 1:
    default:
        return;
    }
    func_8003F564(0, 2);
}

s32 func_80056B0C(s32 arg0, s32 arg1) {
    extern u8 D_800A39E4Small;
    s32 result;

    result = 0;
    switch (D_800A39E4Small) {
    case 2:
    case 3:
    case 6:
    case 8:
    case 15:
    case 16:
    case 17:
        result = 0xFF;
        break;
    case 4:
        if ((arg1 & 0xFF) == 8) {
            result = 0xFF;
        }
        break;
    }
    return result;
}

s32 func_80056B5C(s32 arg0, s32 arg1, s32 arg2) {
    extern u8 D_800A39E4Small;
    s32 result;

    result = 0;
    switch (D_800A39E4Small) {
    case 2:
        if ((arg0 & 0xFF) == 6) {
            result = 1;
        } else if ((arg0 & 0xFF) == 3) {
            result = 1;
        }
        break;
    case 1:
        if ((arg0 & 0xFF) == 0) {
            if ((arg2 & 0xFF) == 0) {
                result = 1;
            }
        } else if ((arg0 & 0xFF) >= 0) {
            if ((arg0 & 0xFF) < 6) {
                if ((arg0 & 0xFF) > 2) {
                    if ((arg2 & 0xFF) != 0) {
                        result = 1;
                    }
                }
            }
        }
        break;
    case 8:
        switch (arg0 & 0xFF) {
        case 1:
            result = 1;
            break;
        }
        break;
    case 4:
        if ((u32)((arg0 - 6) & 0xFF) < 2) {
            result = 1;
        }
        break;
    case 5:
        if ((arg0 & 0xFF) == 4) {
            result = 1;
        } else if ((arg0 & 0xFF) == 0) {
            result = 1;
        }
        break;
    case 3:
        if ((arg0 & 0xFF) < 8) {
            if ((arg0 & 0xFF) >= 0) {
                result = 1;
            }
        }
        break;
    case 6:
        if ((arg0 & 0xFF) < 6) {
            if ((arg0 & 0xFF) >= 0) {
                result = 1;
            }
        }
        break;
    case 7:
    case 11:
        switch (arg0 & 0xFF) {
        case 6:
            result = 1;
            break;
        }
        break;
    case 0:
    case 9:
    case 10:
    case 12:
    case 14:
    case 15:
    case 16:
    case 17:
        result = 1;
        break;
    }
    return result;
}

/* D_800A3644/3988/3073/3078 are declared array-form elsewhere in this
 * TU; the gp-relative byte accesses here go through the .NON_MATCHING
 * label each nonmatching sdata/bss symbol carries at the same address. */
void func_80056C84(s32 arg0, s32 arg1) {
    extern u8 D_800A3644NM asm("D_800A3644.NON_MATCHING");
    extern u8 D_800A3988NM asm("D_800A3988.NON_MATCHING");
    extern u8 D_800A3073NM asm("D_800A3073.NON_MATCHING");
    extern u8 D_800A3078NM asm("D_800A3078.NON_MATCHING");
    extern u8 D_800A3988[];
    extern u8 D_800A3988B[] asm("D_800A3988");
    extern u8 D_800A3988C[] asm("D_800A3988");
    extern u8 D_800A3988D[] asm("D_800A3988");
    extern u8 D_800A3988E[] asm("D_800A3988");
    extern u8 D_800A3988F[] asm("D_800A3988");
    extern u8 D_800A3988G[] asm("D_800A3988");
    extern u8 D_800A3988H[] asm("D_800A3988");
    extern u8 D_800A3988I[] asm("D_800A3988");
    extern u8 D_800A3988J[] asm("D_800A3988");
    extern u8 D_800A3988K[] asm("D_800A3988");
    extern u8 D_800A3988L[] asm("D_800A3988");
    extern u8 D_800A3988M[] asm("D_800A3988");
    extern u8 D_800A3988N[] asm("D_800A3988");
    extern u8 D_800A3988O[] asm("D_800A3988");
    extern u8 D_800A3988P[] asm("D_800A3988");
    extern u8 D_800A398F[];
    extern u8 D_800A3073[];
    extern u8 D_800A306C;
    extern u8 D_800A306E;
    extern u8 D_800A306F;
    extern u8 D_800A3070;
    extern u8 D_800A3071;
    extern u8 D_800A3072;
    extern u8 D_800A3074;
    extern u8 D_800A3076;
    extern u8 D_800A3077;
    s32 m2;
    s32 clearCount;
    u8 *clearPtr;
    s32 tmp;
    s32 idx;

    clearCount = 7;
    clearPtr = D_800A398F;
    do {
        *clearPtr = 0;
        clearCount--;
        clearPtr--;
    } while (clearCount >= 0);

    m2 = 8;
    switch (arg0 & 0xFF) {
    case 2:
        tmp = D_800A3644NM;
        D_800A3988NM = tmp;
        if (tmp != 0) {
            D_800A3988[1] = 1;
        }
        D_800A3988[4] = (D_800A3074 == 0);
        D_800A3988[5] = (D_800A3073NM == 0);
        break;
    case 4:
        switch (D_800A306E) {
        case 0:
            m2 = 1;
            break;
        case 1:
            m2 = 0;
            break;
        case 2:
            m2 = 2;
            break;
        }
        D_800A3988[1] = m2;
        if (D_800A306E == 1) {
            if (D_800A3644NM != 0) {
                D_800A3071 = 0;
                D_800A3988[2] = 0x81;
            } else if (D_800A3071 != 0) {
                D_800A3988[2] = 0;
            } else {
                D_800A3988[2] = 1;
            }
            if (D_800A306F != 0) {
                D_800A3988[3] = 0;
            } else {
                D_800A3988[3] = 1;
            }
        } else {
            D_800A306F = 0;
            D_800A3071 = 0;
            D_800A3988[3] = 0x81;
            D_800A3988[2] = 0x81;
        }
        if (D_800A3070 != 0) {
            D_800A3988[4] = 0;
        } else {
            D_800A3988[4] = 1;
        }
        if (D_800A3644NM != 0) {
            D_800A3072 = 0;
            D_800A3988[5] = 0x81;
        } else if (D_800A3072 != 0) {
            D_800A3988[5] = 0;
        } else {
            D_800A3988[5] = 1;
        }
        break;
    case 11:
        D_800A3988NM = D_800A3078NM;
        break;
    case 5:
        D_800A3988[1] = D_800A306C;
        if (D_800A3076 != 0) {
            D_800A3988[5] = (D_800A3077 == 0);
        }
        break;
    case 7:
        idx = (arg1 & 0xFF) * 2;
        D_800A3988NM = D_800A3073[idx - 0xB];
        D_800A3988[1] = D_800A3073[idx - 0xA];
        break;
    }
}

extern u8 D_800A36E0Small;
extern u8 D_800A361C;
extern u8 D_800A305BSmall;
extern u8 D_800A36E1[];
void func_80056F04(s32 arg0) {
    extern void func_8005E5BC(s32, s32, s32, s32);
    extern void func_8005E7F8(s32, s32, s32, s32);
    extern void func_8005E644(s32, s32, s32, s32);
    extern void func_8005DF08(s32, s32, s32, s32);
    extern void func_800631DC(s32, s32, s32);
    extern u8 D_800A39E4Small;
    s32 idx;
    s32 flag;

    idx = arg0 & 0xFF;
    switch (idx) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
        flag = idx == 7;
        D_800A361C = 0;
        func_8005E5BC(D_800A305BSmall, -0x78, 2, flag);
        func_8005E7F8(D_800A305BSmall, -0x78, 2, flag);
        func_8005E644(D_800A305BSmall, -0x78, 2, flag);
        func_8005DF08(-0x78, 0, 2, flag);
        func_800631DC(-0x3C, 0x3C, 2);
        func_80063AE0(0, D_800A36E0Small);
        func_80063AE0(1, D_800A36E1[0]);
        switch (D_800A39E4Small) {
        case 2:
        case 8:
            func_80063538(-0x3C, 0x3C, 2);
            break;
        }
        break;
    default:
        D_800A361C = 0xFF;
        return;
    }
}

extern u8 D_800A3808a[] asm("D_800A3808.NON_MATCHING");
extern u8 D_800A3808b[] asm("D_800A3814.NON_MATCHING");
extern u8 D_800A3808c[] asm("D_800A380C.NON_MATCHING");
extern u8 D_800A3808d[] asm("D_800A3810.NON_MATCHING");
extern u8 D_800A3968a[] asm("D_800A3968.NON_MATCHING");
extern u8 D_800A3950nm asm("D_800A3950.NON_MATCHING");
extern u8 D_800A3059;
extern u8 D_800A39E4Small;

void func_80057008(s32 arg0) {
    extern void func_8006D8E8(s32);
    extern void func_8006C5E4(s32);
    s32 m2;
    extern void func_8006BD68(void);
    extern u8 D_800A3928;

    if (D_800A3808a[0] == 2 || !(arg0 & 0xFF)) {
        func_8006D8E8(0);
        m2 = D_800A3059;
        D_800A3928 = 1;
        if (m2 == 1) {
            func_8006C5E4(1);
            if (D_800A3059 == m2) {
                D_800A39E4Small = 0x24;
                D_800A3928 = 2;
                return;
            }
        }
        D_800A39E4Small = 0x23;
    } else if (D_800A39E4Small != 0x28) {
        if (D_800A3059 == 2) {
            func_8006BD68();
            D_800A3928 = 0;
            D_800A3808b[-12] = 0;
            D_800A39E4Small = 0x22;
            func_8006C5E4(0);
        } else if (D_800A3059 == 1) {
            if (D_800A3968a[0] == 0) {
                D_800A3808c[-4] = 0x14;
                func_8006D8E8(0);
                D_800A3928 = 2;
                D_800A39E4Small = 0x24;
                func_8006C5E4(1);
            } else {
                D_800A3808d[-8] = 0;
                D_800A39E4Small = 0x24;
                if (D_800A3950nm == 0) {
                    D_800A3928 = 1;
                } else {
                    D_800A3928 = 0;
                }
                func_8006C5E4(1);
            }
        }
    }
}

extern u8 D_800A3704;
extern u8 D_800A3059;
extern u8 D_800A39E4Small;

void func_80057160(s32 arg0) {
    extern void func_8006C9DC(void);
    extern void func_8006C598(s32, s32, s32);
    extern void func_8006C2D0(s32);
    extern void func_8006CB40(void);
    extern void func_80063770(u8);
    extern void func_80069AFC(u8);
    s32 result;

    D_800A3704 = 1;
    func_8006C9DC();
    result = arg0 & 0xFF;
    if (result != 0) {
        func_8006C598(-0x78, 0, 2);
    }
    if (((u8 *)D_800A36D0Absolute)[0x138] == 0) {
        func_8006C2D0(D_800A3059 == 2);
        func_8006CB40();
    }
    func_80063770(0);
    func_80069AFC(D_800A39E4Small);
}

INCLUDE_ASM("asm/nonmatchings/scene", func_800571EC);

extern s32 D_800A3668Absolute[];
extern s32 D_800A3654Lui asm("D_800A3654Absolute");
void func_80057A9C(void) {
    ((s32 *)D_800A3668Absolute)[4] = (s32)HeapAlloc(0x1AB8);
    ((u8 *)D_800A3668Absolute)[-0x7C] = 0;
    D_800A3654Lui = (s32)HeapAlloc(0x834);
    ((u8 *)D_800A37B4Absolute)[8] = 0;
}

extern void func_80012E28(void);
extern void *HeapAlloc(u32);
extern s32 D_800A3548;
extern s32 D_800A3998;
extern s32 D_800A3A18;
extern s32 D_800A39A8;
extern s32 D_800A39CC;
extern s32 D_800A3780;
extern s32 D_800A35B8;
extern s32 D_800A3544;
extern s32 D_800A38EC;
extern s32 D_800A397CAbsolute[];
extern void func_8005E47C(void);
void func_80057AE4(void) {
    POLY_FT4 *poly;
    POLY_F4 *shade;
    u32 count;
    s32 base;

    func_80012E28();
    D_800A3548 = (s32)HeapAlloc(0x4290);
    poly = (POLY_FT4 *)D_800A3548;
    for (count = 0; count < 0x1AA; count++) {
        SetPolyFT4(poly);
        SetShadeTex(poly, 0);
        poly->r0 = 0x80;
        poly->g0 = 0x80;
        poly->b0 = 0x80;
        poly++;
    }
    base = D_800A3548;
    D_800A397CAbsolute[27] = base;
    D_800A3998 = base + 0x3E80;
    D_800A3A18 = base + 0x3E80;
    D_800A39A8 = base + 0x4268;
    D_800A39CC = base + 0x4268;
    D_800A3780 = (s32)HeapAlloc(0x4B0);
    shade = (POLY_F4 *)D_800A3780;
    D_800A35B8 = (s32)shade;
    D_800A3544 = (s32)shade + 0x3C0;
    D_800A38EC = (s32)shade + 0x3C0;
    for (count = 0; count < 0x32; count++) {
        SetPolyF4(shade);
        shade->r0 = 0x80;
        shade->g0 = 0x80;
        shade->b0 = 0x80;
        SetSemiTrans(shade, 0);
        shade++;
    }
    func_8005E47C();
}

extern s32 D_800A3548;
extern s32 D_800A3780;
extern s32 D_800A37EC;

extern s32 D_800A3678Lui asm("D_800A3678Absolute");
void func_80057BFC(void) {
    extern void func_800697B4(void);
    extern void func_8005E3DC(void);
    extern void func_8005E408(void);
    extern void func_80014A68(void);
    extern void func_80063A20(void);

    func_800697B4();
    if (D_800A3780 != 0) {
        HeapFree((void *)D_800A3780);
    }
    D_800A3780 = 0;
    if (D_800A3548 != 0) {
        HeapFree((void *)D_800A3548);
    }
    D_800A3548 = 0;
    func_8005E3DC();
    func_8005E408();
    if (D_800A37EC != 0) {
        HeapFree((void *)D_800A37EC);
    }
    D_800A37EC = 0;
    if (D_800A3678Lui != 0) {
        HeapFree((void *)D_800A3678Lui);
    }
    D_800A3678Lui = 0;
    if (D_800A3654Lui != 0) {
        HeapFree((void *)D_800A3654Lui);
    }
    D_800A3654Lui = 0;
    func_80014A68();
    func_80063A20();
}

extern s32 D_800A36EC;
extern s32 D_800A3A18;
extern s32 D_800A3964;
extern s32 D_800A3580;
extern s32 D_800A35B8;
extern s32 D_800A3650;
extern u8 D_800A39E4Small;

#ifdef NON_MATCHING
/* w9f: D_800A39E4Small unlock works (gp lbu matches). Remaining wall:
 * the then-branch must interleave load,load,add,store,add,store with
 * EC->v1 / A18->v0 (v1 reused for both increment results, anti-dep
 * keeps the second addiu below the first store). Every plain-C form
 * tried (+=, hoisted local, explicit count/next locals, asm("") barrier)
 * gives loads->v0/v1 in C order with both addius before the first store;
 * the asm("") form splits too far (+8, reloads after the store).
 * gPrimitiveCursor[0] += 0x28 also ICEs cc1 at this TU position (0-symbol
 * object); read/store it via D_800A36D0Absolute[-67] instead. */
void func_80057CCC(s32 arg0) {
    s32 cursor;

    arg0 &= 0xFF;
    if (arg0 != 0) {
        D_800A36EC += 1;
        D_800A3A18 += 0x28;
    } else if (D_800A39E4Small != 0x80) {
        D_800A3964 += 1;
        cursor = D_800A36D0Absolute[-67];
        D_800A36D0Absolute[-67] = cursor + 0x28;
    } else {
        D_800A36D0Absolute[-21] = D_800A36D0Absolute[-21] + 0x28;
    }
}

void func_80057D50(s32 arg0) {
    s32 cursor;

    arg0 &= 0xFF;
    if (arg0 != 0) {
        D_800A3580 += 1;
        D_800A35B8 += 0x18;
    } else if (D_800A39E4Small != 0x80) {
        D_800A3650 += 1;
        cursor = D_800A36D0Absolute[-67];
        D_800A36D0Absolute[-67] = cursor + 0x28;
    } else {
        D_800A36D0Absolute[-21] = D_800A36D0Absolute[-21] + 0x28;
    }
}
#else
extern s32 D_800A36EC;
extern s32 D_800A3A18;
extern s32 D_800A3964;
extern u8 D_800A39E4Small;
extern u32 gPrimitiveCursor[];
extern s32 D_800A36D0Absolute[];
extern s32 D_800A3668Absolute[];

extern s32 gPrimitiveCursorLui asm("gPrimitiveCursorAbsolute");
extern s32 D_800A367CLui asm("D_800A367CAbsolute");
u8 *func_80057CCC(s32 arg0) {
    u8 *prim;

    arg0 &= 0xFF;
    if (arg0 != 0) {
        prim = (u8 *)D_800A3A18;
        D_800A36EC += 1;
        D_800A3A18 = (s32)prim + 0x28;
        return prim;
    }
    if (D_800A39E4Small == 0x80) {
        prim = (u8 *)D_800A3668Absolute[5];
        D_800A367CLui = (s32)prim + 0x28;
        return prim;
    }
    prim = (u8 *)gPrimitiveCursor[0];
    D_800A3964 += 1;
    gPrimitiveCursorLui = (s32)prim + 0x28;
    return prim;
}

extern s32 D_800A3580;
extern s32 D_800A35B8;
extern s32 D_800A3650;
extern u8 D_800A39E4Small;
extern u32 gPrimitiveCursor[];
extern s32 D_800A36D0Absolute[];
extern s32 D_800A3668Absolute[];

u8 *func_80057D50(s32 arg0) {
    u8 *prim;

    arg0 &= 0xFF;
    if (arg0 != 0) {
        prim = (u8 *)D_800A35B8;
        D_800A3580 += 1;
        D_800A35B8 = (s32)prim + 0x18;
        return prim;
    }
    if (D_800A39E4Small == 0x80) {
        prim = (u8 *)D_800A3668Absolute[5];
        D_800A367CLui = (s32)prim + 0x28;
        return prim;
    }
    prim = (u8 *)gPrimitiveCursor[0];
    D_800A3650 += 1;
    gPrimitiveCursorLui = (s32)prim + 0x28;
    return prim;
}

#endif

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

extern u8 D_800BDD62[], D_800BDDBE[], D_800BDDC0[], D_800BDD64[];
extern u8 D_800BDD65[], D_800BDD66[], D_800BDD67[], D_800BDDC1[];
extern u8 D_800BDDC2[], D_800BDDC3[];
extern DRAWENV D_800BDD4C[];
extern DISPENV D_800BDE04[];
void GraphicsInitDoubleBufferSwapped(void) {
    s32 height;
    DRAWENV *draw;
    DISPENV *disp;

    height = 0xF0;
    draw = D_800BDD4C;
    SetDefDrawEnv(draw, 0, 0, 0x140, height);
    disp = D_800BDE04;
    SetDefDispEnv(disp, 0x140, 0, 0x140, height);
    draw = (DRAWENV *)((u8 *)draw + 0x5C);
    SetDefDrawEnv(draw, 0x140, 0, 0x140, height);
    disp = (DISPENV *)((u8 *)disp + 0x14);
    SetDefDispEnv(disp, 0, 0, 0x140, height);
    D_800BDD62[0] = 0;
    D_800BDDBE[0] = 0;
    D_800BDDC0[0] = 1;
    D_800BDD64[0] = 1;
    D_800BDD65[0] = 0;
    D_800BDD66[0] = 0;
    D_800BDD67[0] = 0;
    D_800BDDC1[0] = 0;
    D_800BDDC2[0] = 0;
    D_800BDDC3[0] = 0;
    PutDrawEnv(draw);
    PutDispEnv(disp);
}

extern u8 D_800A8C14[];
extern u8 D_800A8B94[];
extern s32 D_800A39C8[];
void func_80057F34(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *env;
    u32 *ot;
    s32 cond;

    cond = (arg0 != 0);
    arg1 += -cond & 0x140;
    SetDefDrawEnv((DRAWENV *)D_800A8C14, arg1, arg2, arg3, arg4);
    env = D_800A8B94 + arg0 * 0x40;
    SetDrawEnv((DR_ENV *)env, (DRAWENV *)D_800A8C14);
    ot = (u32 *)D_800A39C8[0];
    AddPrim(ot + arg5, env);
}

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

extern s32 D_800A305C;
extern DISPENV D_800BDE04[];
extern DRAWENV D_800BDD4C[];
void func_80058030(void) {
    PutDispEnv(&D_800BDE04[D_800A305C]);
    PutDrawEnv(&D_800BDD4C[D_800A305C]);
}

/* Load a file into buf, or into a fresh heap block when buf is 0, and
 * return the buffer. The loop notes from do/while (0) double the weight of
 * the HeapAlloc references, which ranks size ahead of sector for the saved
 * registers, as in retail. */
void *func_80058094(s32 fileId, void **outTable, s32 buf) {
    extern s32 D_800A3090[];
    s32 size;
    s32 sector;

    sector = (s32)FileOpen(fileId, D_800A3090);
    size = (FileSeek(sector, 0, 2) + 0x7FF) >> 11 << 11;
    if (buf == 0) {
        do {
            buf = (s32)HeapAlloc(size);
        } while (0);
    }
    FileSeek(sector, 0, 0);
    FileRead(buf, 1, size, sector);
    FileClose(sector);
    *outTable = (void *)(buf + 4);
    return (void *)buf;
}

extern void func_8006DD28(u32 arg0, u32 arg1);
extern void func_8006E484(u32 arg0, u32 arg1);
asm(".globl D_800A3814w45S\nD_800A3814w45S = D_800A3814");
asm(".globl D_800A3075w45S\nD_800A3075w45S = D_800A3075");

void func_80058148(void) {
    extern s32 D_800A3814w45S;
    extern u8 D_800A3075w45S;
    extern u8 D_800A3644w45 asm("D_800A3644.NON_MATCHING");
    extern u8 D_800A306E;
    extern u8 D_800A306F;
    extern u8 D_800A3070;
    extern u8 D_800A3072;
    extern u8 D_800A3076;
    extern u8 D_800A3077;
    extern s32 D_800A2CE0w45[] asm("D_800A2CE0.NON_MATCHING");
    extern s32 D_800A2EA8w45[] asm("D_800A2EA8.NON_MATCHING");
    extern s32 D_800A2EA4w45[] asm("D_800A2EA4.NON_MATCHING");
    extern u8 D_800A2EDCw45[] asm("D_800A2EDC.NON_MATCHING");
    extern u8 D_800A2EE0w45[] asm("D_800A2EE0.NON_MATCHING");
    extern s8 D_800A3A25w45[] asm("D_800A3A25.NON_MATCHING");
    extern u8 D_800A38F0w45[] asm("D_800A38F0.NON_MATCHING");
    extern u8 D_800A3A60w45[] asm("D_800A3A60.NON_MATCHING");
    extern u8 D_800A3688w45[] asm("D_800A3688.NON_MATCHING");
    extern u8 D_800A36E4w45[] asm("D_800A36E4.NON_MATCHING");
    extern u8 D_800A3A24w45[] asm("D_800A3A24.NON_MATCHING");
    s32 i;

    D_800A2EA8w45[0] = D_800A3814w45S;
    D_800A2CE0w45[0] = D_800A305BSmall;
    if (D_800A3644w45 != 0 && D_800A3A25w45[0] == 0) {
        D_800A3644w45 = 0;
    }
    D_800A2EA4w45[0] = D_800A3644w45;
    switch (D_800A306E) {
    case 0:
        D_800A2EDCw45[0] = 0;
        D_800A2EE0w45[0] = 0;
        break;
    case 1:
        D_800A2EDCw45[0] = 1;
        D_800A2EE0w45[0] = 0;
        break;
    case 2:
        D_800A2EDCw45[0] = 1;
        D_800A2EE0w45[0] = 1;
        break;
    }
    D_800A38F0w45[0] = D_800A306F;
    D_800A3A60w45[0] = D_800A3070;
    if (D_800A3644w45 == 0 && D_800A3072 != 0) {
        D_800A3688w45[0] = 1;
    } else {
        D_800A3688w45[0] = 0;
    }
    for (i = 0; i < D_800A3644w45 + 1; i++) {
        if ((func_8004229C(D_800A3A24w45[i]) & 0xFF) != 0) {
            if (D_800A36E4w45[i] != 0) {
                func_8006E484(i, (s8)D_800A3A24w45[i]);
            } else {
                func_8006DD28(i & 0xFF, D_800A3A24w45[i]);
            }
        } else {
            func_8006DD28(i & 0xFF, 2);
        }
    }
    if (D_800A3076 != 0) {
        D_800A3075w45S = D_800A3077;
    } else {
        D_800A3075w45S = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/scene", func_8005833C);

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

INCLUDE_ASM("asm/nonmatchings/scene", func_800587A0);
INCLUDE_RODATA("asm/nonmatchings/scene", D_8008D738);

/* func_80058D08: writes $gp directly; not expressible in C. */
void func_80058D08(s32 gp) {
    /* Retail writes the new global pointer directly; not expressible
     * in plain C (see kb/psx/matching.md func_80062874). */
    asm("addu $gp, $a0, $zero");
}

void func_80058D14(u16 *src, u16 *dst, s32 arg2) {
    u8 *end;
    u16 bits;
    u32 pixel;
    u8 value;
    s32 shift;
    u8 j;

    end = (u8 *)dst + 0x257FE;
    do {
        bits = *src;
        pixel = 0;
        shift = 0;
        j = 0;
        do {
            value = (u8)(arg2 + (bits & 0x1F));
            if (value >= 0x20) {
                value = 0x1F;
            }
            pixel |= value << shift;
            shift += 5;
            j++;
            bits >>= 5;
        } while ((j & 0xFF) < 3);
        *dst = pixel;
        dst = (u16 *)((u8 *)dst + 2);
        src = (u16 *)((u8 *)src + 2);
    } while (end >= (u8 *)dst);
}

void func_80058D8C(void) {
}

extern u8 D_800B9990[];
extern u8 *D_800A34FC;
extern u16 *D_800A35F0;
extern RECT D_800A3710[2];
extern RECT D_800A3710Small asm("D_800A3710");
extern s32 D_800A39C8store[] asm("D_800A39C8");
extern s32 D_800A39C8draw[] asm("D_800A39C8");
extern DISPENV D_800BDE18put[] asm("D_800BDE18");
extern s32 D_800A3904[];
extern u8 D_800A3A48;
extern u8 D_800A3950;
extern u8 D_800A3724;
extern u8 D_800A2F9C[];
extern DRAWENV D_800BDDA8[];
extern DISPENV D_800BDE18[];
extern s32 D_800A3638;
extern s32 D_800A381C;
extern s32 D_800A36B4w6c[] asm("D_800A36B4");
extern void SsStart2(void);
extern void func_8005957C(void);
extern void func_80066A24(void);
extern s32 func_8006F9C4(s32, s32, s32);
extern void func_80041AF0Scene(s32);
extern s32 RandomScaledGetScene(void);
asm(".globl func_80041AF0Scene\nfunc_80041AF0Scene = func_80041AF0");
asm(".globl RandomScaledGetScene\nRandomScaledGetScene = RandomScaledGet");

void func_80058D94(void) {
    extern s32 FileSeekScene(s32, s32, s32) asm("FileSeek");
    extern void FileCloseScene(s32) asm("FileClose");
    extern void TextureLoadTim(void *);
    extern s32 D_800A3090[];
    s32 done;
    s32 prevPads;
    RECT rect;
    s32 pad[6];
    s32 *volatile offsets;
    u32 frame;
    s32 fade;
    u8 *texBuf;
    u8 toggle;
    u8 *fileBuf;
    u8 *buf;
    u8 *prim;
    s32 xa;
    s32 xb;
    s32 sector;
    s32 size;
    u8 counter;
    s32 bank;
    u8 *ot;
    u8 *envByte;
    s16 *xy;
    s32 height;
    u16 tpage;
    s32 pads;
    s32 mask;
    s32 cond;
    s32 moveX;
    u16 *src;
    u16 *dst;
    u8 *end;
    u16 bits;
    u32 pixel;
    u8 value;
    s32 shift;
    u8 j;

    (void)&pad;
    if (D_800A3638 == 0) {
        sector = (s32)FileOpen(0, D_800A3090);
        size = (FileSeekScene(sector, 0, 2) + 0x7FF) >> 11 << 11;
        buf = HeapAlloc(size);
        FileSeekScene(sector, 0, 0);
        FileRead(buf, 1, size, sector);
        FileCloseScene(sector);
        offsets = (s32 *)(buf + 4);
        fileBuf = buf;
    } else {
        fileBuf = (u8 *)D_800A3638;
        offsets = (s32 *)D_800A381C;
    }
    D_800A37EC = (s32)(fileBuf + offsets[0]);
    texBuf = HeapAlloc(0x25800);
    TextureLoadTim((void *)D_800A37EC);
    D_800A3710[0] = *(RECT *)&D_800A39B0[0];
    D_800A35F0 = (u16 *)D_800A36B4w6c[0];
    DrawSync(0);
    TextureLoadTim(fileBuf + offsets[1]);
    DrawSync(0);
    TextureLoadTim(fileBuf + offsets[2]);
    DrawSync(0);
    D_800A34FC = D_800B9990;
    frame = 0;
    SetPolyFT4((POLY_FT4 *)D_800B9990);
    SetShadeTex(D_800A34FC, 0);
    *(u8 *)(D_800A34FC + 4) = 0x80;
    *(u8 *)(D_800A34FC + 5) = 0x80;
    *(u8 *)(D_800A34FC + 6) = 0x80;
    SetSemiTrans(D_800A34FC, 0);
    tpage = GetTPage(2, 0, 0x100, 0x100);
    prim = D_800A34FC;
    *(u8 *)(D_800A34FC + 0xC) = 0x40;
    envByte = D_800A34FC + 0xD;
    *(u16 *)(prim + 0x16) = tpage;
    envByte[0] = 0x24;
    *(u8 *)(D_800A34FC + 0x14) = 0xA0;
    *(u8 *)(D_800A34FC + 0x15) = 0x24;
    *(u8 *)(D_800A34FC + 0x1C) = 0x40;
    *(u8 *)(D_800A34FC + 0x1D) = 0x39;
    *(u8 *)(D_800A34FC + 0x24) = 0xA0;
    *(u8 *)(D_800A34FC + 0x25) = 0x39;
    xy = (s16 *)D_800A34FC;
    cond = (u32)(D_800A2EB0Absolute[0] + 3) < 2;
    xy[4] = (xa = 0x73);
    xb = 0xD3;
    xy[5] = 0xBC;
    xy[9] = 0xBC;
    xy[8] = xb;
    xy[12] = xa;
    xy[13] = 0xD1;
    xy[16] = xb;
    xy[17] = 0xD1;
    if (cond == 0) {
        SsStart2();
        frame = func_8006F9C4(1, 0, 1);
        if ((frame & 0xFF) != 0 || (D_800A3904[0] & 0x800) <= 0) {
            frame = func_8006F9C4(2, 1, 1);
        }
        SsEnd();
    }
    fade = frame & 0xFF;
    if (fade == 0) {
        SetDispMask(0);
    }
    height = 0xF0;
    SetDefDrawEnv(D_800BDD4C, 0, 0, 0x140, height);
    SetDefDispEnv(D_800BDE04, 0x140, 0, 0x140, height);
    SetDefDrawEnv(D_800BDDA8, 0x140, 0, 0x140, height);
    SetDefDispEnv(D_800BDE18, 0, 0, 0x140, height);
    envByte = D_800BDD64;
    D_800BDD62[0] = 0;
    D_800BDDBE[0] = 0;
    D_800BDDC0[0] = 1;
    envByte[0] = 1;
    D_800BDD65[0] = 0;
    D_800BDD66[0] = 0;
    D_800BDD67[0] = 0;
    D_800BDDC1[0] = 0;
    D_800BDDC2[0] = 0;
    D_800BDDC3[0] = 0;
    PutDrawEnv((DRAWENV *)(envByte + 0x44));
    PutDispEnv(D_800BDE18put);
    fade = -(fade != 0) & 0x1F;
    dst = (u16 *)texBuf;
    src = D_800A35F0;
    end = (u8 *)dst + 0x257FE;
    do {
        bits = *src;
        pixel = 0;
        shift = 0;
        j = 0;
        do {
            value = (u8)(fade + (bits & 0x1F));
            if (value >= 0x20) {
                value = 0x1F;
            }
            pixel |= value << shift;
            shift += 5;
            j++;
            bits >>= 5;
        } while ((j & 0xFF) < 3);
        *dst = pixel;
        dst = (u16 *)((u8 *)dst + 2);
        src = (u16 *)((u8 *)src + 2);
    } while (end >= (u8 *)dst);
    LoadImage(D_800A3710, (u_long *)texBuf);
    frame = 1;
    D_800A2F9C[0] = frame;
    func_8003CAE8(5);
    SsSetMVol(0x7F, 0x7F);
    D_800A3724 = frame;
    SetDispMask(1);
    done = 0;
    toggle = 0;
    prevPads = 0;
    D_800A305C = 0;
    frame = -(D_800A2EB0Absolute[0] == -2) & 0xB4;
    do {
        RandomScaledGetScene();
        bank = D_800A305C == 0;
        ot = gOrderingTables + (bank << 12);
        D_800A305C = bank;
        gOrderingTableBankAbsolute[0] = bank;
        D_800A39C8store[0] = (s32)ot;
        ClearOTagR((OT_TYPE *)ot, 4);
        if ((fade << 24) != 0) {
            fade = fade - 1;
            src = D_800A35F0;
            dst = (u16 *)texBuf;
            end = (u8 *)dst + 0x257FE;
            do {
                bits = *src;
                pixel = 0;
                shift = 0;
                j = 0;
                do {
                    value = (u8)(fade + (bits & 0x1F));
                    if (value >= 0x20) {
                        value = 0x1F;
                    }
                    pixel |= value << shift;
                    shift += 5;
                    j++;
                    bits >>= 5;
                } while ((j & 0xFF) < 3);
                *dst = pixel;
                dst = (u16 *)((u8 *)dst + 2);
                src = (u16 *)((u8 *)src + 2);
            } while (end >= (u8 *)dst);
        } else {
            frame++;
            if (frame >= 0xB5) {
                counter = D_800A3724 - 1;
                D_800A3724 = counter;
                if (counter == 0) {
                    D_800A3724 = 0x3C;
                    toggle = toggle ^ 1;
                }
                if (toggle != 0) {
                    AddPrim((void *)D_800A39C8[0], D_800A34FC);
                }
            }
        }
        DrawSync(0);
        VSync(0);
        PutDispEnv(&D_800BDE04[D_800A305C]);
        PutDrawEnv(&D_800BDD4C[D_800A305C]);
        D_800A3710Small.x = -(D_800A305C != 0) & 0x140;
        LoadImage(D_800A3710, (u_long *)texBuf);
        if ((fade << 24) != 0) {
            continue;
        }
        DrawOTag((OT_TYPE *)(D_800A39C8draw[0] + 0xC));
        func_80041AF0Scene(0);
        pads = func_80041B7C(0);
        if (frame >= 0xB5) {
            if (D_800A2EB0Absolute[0] == -2) {
                mask = ~prevPads & 0x9F0;
            } else {
                mask = ~prevPads & 0x800;
            }
            if ((pads & mask) != 0) {
                done = 1;
            }
            if ((done & 0xFF) != 0) {
                if (D_800A3A48 != 0xFF) {
                    D_800A39E4Small = D_800A3A48;
                    D_800A3A48 = 0xFF;
                } else {
                    D_800A39E4Small = 0;
                }
                prevPads = pads;
            } else {
                if (frame >= 0x709) {
                    done = 1;
                    D_800A39E4Small = 0xFE;
                }
                prevPads = pads;
            }
        } else {
            prevPads = pads;
        }
        /* Keep the loop flag live across the pad-state update. */
        asm("" : "=r"(done) : "0"(done), "r"(done));
    } while ((done & 0xFF) == 0);
    if (D_800A39E4Small == 0xFE) {
        func_8005957C();
    } else if (D_800A39E4Small == 0) {
        D_800A3950 = 0xF9;
    }
    rect.x = 0x200;
    rect.y = 0x124;
    rect.w = 0x60;
    rect.h = 0x15;
    moveX = 0x73;
    if (D_800A305C == 0) {
        moveX = 0x1B3;
    }
    MoveImage(&rect, moveX, 0xBC);
    DrawSync(0);
    HeapFree(fileBuf);
    D_800A3638 = 0;
    HeapFree(texBuf);
    if (D_800A39E4Small == 0xFE) {
        func_80066A24();
    }
    HeapResetInitFlag();
}

#ifdef NON_MATCHING
/*
 * w8g: full body reached an exact unit diff EXCEPT data labels: any
 * active C here (even size-identical to the stub) shifts the sdata
 * labels -0xC and a shorter body shifts them differently (see
 * matching.md). text side (all verified, keep these when retrying):
 * - D_800A2EB0=-1 / D_800A2EA8=3 via D_800A2EB0Absolute[0] / [-2]
 * - D_800A2CE0 twice via DISTINCT aliases (A2E24[-0x151] first,
 *   A2EB0Absolute[-0x74] in the arm) or gcc hoists the address into s0
 * - store the arm call result DIRECTLY (`D[...] = RandomScaledGet(0x10);`)
 *   or gcc keeps the old value alive in v1 (`move v1,v0`, bne flipped)
 * - tail: seed=D_800A36E0 (lbu gp), A2EA4/A2EDC/A2EE0 as u8 arrays
 *   (lui), A38F0/A3A60 as u8 arrays (lui), A3064/A3065/A3718 scalar
 *   (gp); u8 arrays DO get lui here, do not cast them (cast form
 *   segfaults cc1 at this TU position)
 * - CAST-FORM STORES `((u8 *)D_800A2EC8Absolute)[n] = v;` DETONATE cc1
 *   here (0-symbol object, exit 0). Direct u8[] externs are fine.
 */
extern u8 D_800A2EDC[];
extern u8 D_800A2EE0[];
extern u8 D_800A38F0[];
extern u8 D_800A3A60[];
extern u8 D_800A3064;
extern u8 D_800A3065;
extern u8 D_800A3718;
extern u8 D_800A36E0;
void func_8005957C(void) {
    s32 value;
    u8 seed;

    D_800A2EB0Absolute[0] = -1;
    D_800A2EB0Absolute[-2] = 3;
    value = RandomScaledGet(0x11);
    D_800A2E24Absolute[-0x151] = value;
    if (value == 0x10) {
        D_800A2EB0Absolute[-0x74] = RandomScaledGet(0x10);
    }
    seed = D_800A36E0;
    D_800A2EA4[0] = 0;
    D_800A2EDC[0] = 0;
    D_800A2EE0[0] = 1;
    D_800A38F0[0] = 0;
    D_800A3A60[0] = 0;
    D_800A3064 = 0;
    D_800A3065 = 0;
    D_800A3718 = seed;
}
#endif
extern u32 D_800A2EA4NM[] asm("D_800A2EA4.NON_MATCHING");
extern u8 D_800A2EDCNM[] asm("D_800A2EDC.NON_MATCHING");
extern u8 D_800A2EE0NM[] asm("D_800A2EE0.NON_MATCHING");
extern u8 D_800A38F0NM[] asm("D_800A38F0.NON_MATCHING");
extern u8 D_800A3A60NM[] asm("D_800A3A60.NON_MATCHING");
extern u8 D_800A3064NM asm("D_800A3064.NON_MATCHING");
extern u8 D_800A3065NM asm("D_800A3065.NON_MATCHING");
extern u8 D_800A3718NM asm("D_800A3718.NON_MATCHING");
extern u8 D_800A36E0NM asm("D_800A36E0.NON_MATCHING");
void func_8005957C(void) {
    s32 value;
    u8 seed;

    D_800A2EB0Absolute[0] = -1;
    D_800A2EB0Absolute[-2] = 3;
    value = RandomScaledGet(0x11);
    D_800A2E24Absolute[-0x51] = value;
    if (value == 0x10) {
        D_800A2EB0Absolute[-0x74] = RandomScaledGet(0x10);
    }
    seed = D_800A36E0NM;
    D_800A2EA4NM[0] = 0;
    D_800A2EDCNM[0] = 0;
    D_800A2EE0NM[0] = 1;
    D_800A38F0NM[0] = 0;
    D_800A3A60NM[0] = 0;
    D_800A3064NM = 0;
    D_800A3065NM = 0;
    D_800A3718NM = seed;
}

s32 ColorPack555(s32 red, s32 green, u8 blue) {
    s16 color;
    color =
        (blue >> 3) | (((red << 7) & 0x7C00) | ((green << 2) & 0x3E0)) | -32768;
    return color;
}

#ifdef NON_MATCHING
/* Wall: prologue and loop body match. Retail batches the five pixel
 * constants into five registers (v0,v1,a1,a2,a3) before storing; ours
 * materializes each constant just before its store (single recycled
 * register). Loop uses pointer=v1/counter=v0; retail has them swapped.
 * Permuter candidate. */
extern void *HeapAlloc(u32);
extern void HeapFree(void *);
void func_80059648(void) {
    RECT rect;
    s16 *pixels;
    s32 i;
    s16 *p;

    rect.x = 0x100;
    rect.y = 0x1FF;
    rect.h = 1;
    rect.w = 0x10;
    pixels = HeapAlloc(0x20);
    p = pixels + 8;
    for (i = 8; i >= 0; i--) {
        *p = -0x3DF0;
        p--;
    }
    pixels[11] = -0x62D7;
    pixels[9] = -0x5674;
    pixels[10] = -0x5A95;
    pixels[12] = -0x6AF8;
    pixels[13] = -0x733A;
    pixels[14] = 0;
    pixels[15] = 0;
    LoadImage(&rect, (u_long *)pixels);
    HeapFree(pixels);
}
#else
void func_80059648(void) {
    RECT rect;
    s16 *pixels;
    s32 i;
    s16 fill;
    s16 *p;
    s16 c1, c2, c3, c4, c5;

    rect.x = 0x100;
    rect.y = 0x1FF;
    rect.h = 1;
    rect.w = 0x10;
    pixels = HeapAlloc(0x20);
    fill = -0x3DF0;
    i = 8;
    p = pixels + 8;
    do {
        do {
            *p = fill;
            p--;
            i--;
        } while (i >= 0);
        c1 = -0x5674;
        c2 = -0x5A95;
        c3 = -0x62D7;
        c4 = -0x6AF8;
    } while (0);
    c5 = -0x733A;
    pixels[9] = c1;
    pixels[10] = c2;
    pixels[11] = c3;
    pixels[12] = c4;
    pixels[13] = c5;
    pixels[14] = 0;
    pixels[15] = 0;
    LoadImage(&rect, (u_long *)pixels);
    HeapFree(pixels);
}

#endif

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

extern s32 D_800A381C;
extern s32 D_800A3638;
extern s32 FileSeekArgs(void *, s32, s32);
extern void FileSeekArgsV(void *, s32, s32);
extern void FileCloseArgs(s32);
asm(".globl FileSeekArgs\nFileSeekArgs = FileSeek");
asm(".globl FileSeekArgsV\nFileSeekArgsV = FileSeek");
asm(".globl FileCloseArgs\nFileCloseArgs = FileClose");
void func_8005978C(void) {
    extern void *FileOpen(s32, void *);
    extern void FileRead(s32, s32, s32, s32);
    extern s32 D_800A3090[];
    DISPENV env;
    s32 sector;
    s32 size;
    s32 buf;
    s32 next;
    s32 tmp;

    sector = (s32)FileOpen(0, D_800A3090);
    size = (FileSeekArgs((void *)sector, 0, 2) + 0x7FF) >> 11 << 11;
    do {
        tmp = (s32)HeapAlloc(size);
        FileSeekArgsV((void *)sector, 0, 0);
    } while (0);
    buf = tmp;
    FileRead(buf, 1, size, sector);
    FileCloseArgs(sector);
    next = *(s32 *)(buf + 0x10);
    D_800A381C = buf + 4;
    D_800A3638 = buf;
    buf += next;
    D_800A37EC = buf;
    TextureLoadTim((void *)buf);
    DrawSync(0);
    SetDefDispEnv(&env, 0x140, 0, 0x140, 0xF0);
    PutDispEnv(&env);
    SetDispMask(1);
}
