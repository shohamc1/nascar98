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
extern void GameRunSession(void);
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
s32 func_80024E90(s32, s32, s32 *, s32 *, s32 *);
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
void CarPlaceOnStartingGrid(void);
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
extern u16 D_8008CA04U16[] asm("D_8008CA04");
extern u16 D_8008CA04U16[] asm("D_8008CA04");
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
extern s32 D_800A39C8[];
extern u32 gPrimitiveCursor[];
extern u8 D_800A2DE0[];
extern void SetLineF4(u8 *prim);
extern void SetLineF2(u8 *prim);
extern s32 D_800A33F0;
extern s32 D_800A33F4;
extern s8 D_800A33F8;
extern s32 D_800A3400;
extern s32 D_800A3404;
extern s32 D_80098184[];
extern s32 D_80098134nm[] asm("D_80098134.NON_MATCHING");
extern s32 D_8009813Cnm[] asm("D_8009813C.NON_MATCHING");
extern u8 D_800A3880nm[] asm("D_800A3880.NON_MATCHING");
extern s32 D_800A3960gp;
extern u8 D_800A35F8gp;
extern u8 D_800A3A60gp;
extern u8 D_800A342C[];
extern s32 D_800A3430[];
extern u8 D_80090F32[];
extern u8 D_800991E8[];
extern u8 D_800991E9[];
extern u8 D_800991EA[];
extern u8 D_800A342C[];
extern s32 D_800A3430[];
extern u8 D_80090F32[];
extern u8 D_800991E8[];
extern u8 D_800991E9[];
extern u8 D_800991EA[];
extern s32 D_800A2EB0Absolute[];
extern s32 D_800A3984[];
extern void *HeapAlloc(u32);
extern s32 D_800A2EC0nm[] asm("D_800A2EC0.NON_MATCHING");
extern s32 D_800A3550[];
extern u8 *D_800A3554[];
extern s32 D_800A397C[];
extern s32 D_800A3A3C[];
extern s32 D_800A3A90[];
extern s16 D_800A35A4w40;
extern u8 *D_800A347C;
extern void *D_800A3728;
extern u8 CarDrawModel(u8 *, s32);
extern s32 func_80037204(u8 *);
extern s32 func_8003702C(u8 *, u8 *);
extern void func_8004875C(void);
extern u8 *D_800A3554again[];
extern u8 *D_800A347C;
extern void *D_800A3728;
extern void func_8002D4CC(u8 *);
extern u8 *D_800A347C;
extern void *D_800A3728;
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
extern u8 D_8009AE14[];
extern u8 D_800A2FD0[];
extern u8 D_80098BD0[];
extern s32 D_800A2E50[];
extern s16 D_800A38E4[];
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
extern void func_80050028Lbl(char *, s16, s16, s8) asm("func_80050028");
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
extern u8 *D_800A3554[];
extern u8 *D_800A8A80[];
extern char D_800A3020nm[] asm("D_800A3020.NON_MATCHING");
extern u8 gTextColorNm asm("gTextColor.NON_MATCHING");
extern void func_80050028Args(char *, s16, s16, s8);
extern s32 sprintfTextArgs(char *, char *, ...);
void SetPolyFT4(POLY_FT4 *);
extern POLY_FT4 D_800A8AC4[];
extern s16 D_800A8AD2[];
extern u8 D_800A8AC8[], D_800A8AC9[], D_800A8ACA[];
extern u8 D_80098D16[];
extern s8 D_800A34CC;
extern s8 D_800A34CD;
extern s8 D_800A34CE;
extern s8 D_800A34CF;
extern s8 D_800A34D0;
extern s8 D_800A34D1;
extern u8 D_800A8B00[];
extern u8 D_800A8B01[];
extern u8 D_800A8B02[];
extern u8 D_800A34E4;
extern s32 D_800A34F4;
extern u8 D_80090F7A[];
extern s16 D_800A34E8;
extern s8 D_800A34EC;
extern s8 D_800A34F0;
extern s32 D_800A34F4;
extern s32 D_800BE974[];
extern s32 D_800BE980[];
extern u8 *D_800A3878NM[] asm("D_800A3878.NON_MATCHING");
extern s8 D_800A34EC;
extern s8 D_800A34F0;
extern void func_8003F914(s32);
extern void func_8003FC0C(s32, s32, s32);
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
extern u8 D_800A36E0Small;
extern u8 D_800A361C;
extern u8 D_800A305BSmall;
extern u8 D_800A36E1[];
extern u8 D_800A3808a[] asm("D_800A3808.NON_MATCHING");
extern u8 D_800A3808b[] asm("D_800A3814.NON_MATCHING");
extern u8 D_800A3808c[] asm("D_800A380C.NON_MATCHING");
extern u8 D_800A3808d[] asm("D_800A3810.NON_MATCHING");
extern u8 D_800A3968a[] asm("D_800A3968.NON_MATCHING");
extern u8 D_800A3950nm asm("D_800A3950.NON_MATCHING");
extern u8 D_800A3059;
extern u8 D_800A39E4Small;
extern u8 D_800A3704;
extern u8 D_800A3059;
extern u8 D_800A39E4Small;
extern s32 D_800A3668Absolute[];
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
extern s32 D_800A3548;
extern s32 D_800A3780;
extern s32 D_800A37EC;
extern s32 D_800A36EC;
extern s32 D_800A3A18;
extern s32 D_800A3964;
extern s32 D_800A3580;
extern s32 D_800A35B8;
extern s32 D_800A3650;
extern u8 D_800A39E4Small;
extern s32 D_800A36EC;
extern s32 D_800A3A18;
extern s32 D_800A3964;
extern u8 D_800A39E4Small;
extern u32 gPrimitiveCursor[];
extern s32 D_800A36D0Absolute[];
extern s32 D_800A3668Absolute[];
extern s32 D_800A3580;
extern s32 D_800A35B8;
extern s32 D_800A3650;
extern u8 D_800A39E4Small;
extern u32 gPrimitiveCursor[];
extern s32 D_800A36D0Absolute[];
extern s32 D_800A3668Absolute[];
extern s32 D_800A38EC, D_800A3650, D_800A3544;
extern s32 D_800A3580, D_800A35B8, D_800A3780;
extern s32 D_800A3964, D_800A39A8, D_800A39CC;
extern s32 D_800A36EC, D_800A3998, D_800A3A18;
extern u8 D_800BDD62[], D_800BDDBE[], D_800BDDC0[], D_800BDD64[];
extern u8 D_800BDD65[], D_800BDD66[], D_800BDD67[], D_800BDDC1[];
extern u8 D_800BDDC2[], D_800BDDC3[];
extern DRAWENV D_800BDD4C[];
extern DISPENV D_800BDE04[];
extern u8 D_800A8C14[];
extern u8 D_800A8B94[];
extern s32 D_800A39C8[];
s32 func_80041B7C(s32);
extern s32 D_800A305C;
extern DISPENV D_800BDE04[];
extern DRAWENV D_800BDD4C[];
extern s32 FileSeekArgs(void *, s32, s32);
extern void FileCloseArgs(s32);
extern void func_8006DD28(u32 arg0, u32 arg1);
extern void func_8006E484(u32 arg0, u32 arg1);
extern u8 D_800BE70C[];
extern u32 D_800A2EA4NM[] asm("D_800A2EA4.NON_MATCHING");
extern u8 D_800A2EDCNM[] asm("D_800A2EDC.NON_MATCHING");
extern u8 D_800A2EE0NM[] asm("D_800A2EE0.NON_MATCHING");
extern u8 D_800A38F0NM[] asm("D_800A38F0.NON_MATCHING");
extern u8 D_800A3A60NM[] asm("D_800A3A60.NON_MATCHING");
extern u8 D_800A3064NM asm("D_800A3064.NON_MATCHING");
extern u8 D_800A3065NM asm("D_800A3065.NON_MATCHING");
extern u8 D_800A3718NM asm("D_800A3718.NON_MATCHING");
extern u8 D_800A36E0NM asm("D_800A36E0.NON_MATCHING");
extern u8 D_800A2F9CAbsolute[];
extern u8 D_800A3694;
extern void func_8003CAE8(s32);
extern void CdSetMixVolume(s32);
extern s32 D_800A381C;
extern s32 D_800A3638;
extern s32 FileSeekArgs(void *, s32, s32);
extern void FileSeekArgsV(void *, s32, s32);
extern void FileCloseArgs(s32);
extern void CardTestEvents(void);
extern void func_8005A414(void);
extern s32 CardDisableEvents(void);
extern s32 CardEnableEvents(void);
extern void CardTestEvents(void), func_8005A414(void);
extern s32 func_8005A294(void);
extern u32 D_800A3824, D_800A3828, D_800A382C, D_800A3834;
extern s32 D_800A38C8, D_800A38CC, D_800A38D0, D_800A38D4;
extern s32 func_8005A294(void);
extern void func_8005A414(void);
extern char gMemoryCardDevice2[], gMemoryCardDevice1[];
extern s32 CloseEvent(s32);
extern u32 D_800A3824;
extern u32 D_800A3828;
extern u32 D_800A382C;
extern u32 D_800A3834;
extern s32 D_800A38C8;
extern s32 D_800A38CC;
extern s32 D_800A38D0;
extern s32 D_800A38D4;
extern void func_80059C2C(void);
extern s32 func_8005A294(void);
extern void CardTestEvents(void);
extern s32 CardWaitForEvent(void);
extern void func_8005A414(void);
extern void func_8005A414(void);
extern void _new_card(void);
extern void _card_read(s32, s32, s32);
extern s32 CardWaitForEvent(void);
extern void _new_card(void);
extern void _card_write(s32, s32, s32);
extern char gMemoryCardDevice2[], gMemoryCardDevice1[];
extern u32 D_800A3824, D_800A3828, D_800A382C, D_800A3834;
extern s32 D_800A38C8;
extern s32 D_800A38CC;
extern s32 D_800A38D0;
extern s32 D_800A38D4;
extern s32 D_800A38C8;
extern s32 D_800A38CC;
extern s32 D_800A38D0;
extern s32 D_800A38D4;
extern char gMemoryCardWildcard[];
extern s32 D_800B1EBC[];
extern s32 D_800A39E8;
extern u16 D_800A3874;
extern s32 D_800A3768;
extern void func_8005A818(u8, u8, u8);
extern s32 D_800A35A0;
extern u8 D_800A3534;
extern s32 D_800A3750;
extern s32 D_800A35AC;
extern s32 D_800B1EBC[];
extern s32 D_80099FE4[][3];
extern u8 D_800A37C8, D_800A37A8, D_800A378C;
extern u8 D_800A3618;
extern u8 D_800A3624;
extern u8 D_800A364C;
extern u8 D_800A3618;
extern u8 D_800A3624;
extern u8 D_800A364C;
extern u8 D_800A3534;
extern s32 D_800A35AC;
extern s16 func_8005A8E0(s32);
extern u8 D_800A35EC;
extern u8 *D_800A3678;
extern u8 D_800A37BC, D_800A35EC;
extern u8 D_800A39C4, D_800A37BC, D_800A35EC;
extern void SetPolyF3(POLY_F3 *);
extern s32 D_800A39C8[];
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
extern u8 *func_80057CCC(s32);
extern u8 *func_80057D50(s32);
extern void func_8005C020(u8 *, u8 *);
extern void func_8005C0F4(u8 *, s32);
extern void func_8005CF34(u8 *, u8, u8, u8, s32);
extern u8 D_800A39E4Absolute[];
extern s32 D_800A3654;
extern u8 D_800A37BC;
extern u8 D_800A35EC;
extern u8 *D_800A3678;
extern u8 D_800A37BC;
extern s32 D_800A3654;
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
extern Unk4 D_800A3324[];
extern Unk4 D_800A3328[];
extern Unk3 D_800A332C[];
extern u8 D_800A39E4[];
extern void func_80018588(void *, s32, s32);
extern u8 *D_800A36F0;
extern u8 *D_800A3690;
extern u8 *D_800A39C0;
extern u8 *D_800A3A28;
extern u8 D_800A3988[];
extern void func_8005A7B8(u8, u8);
extern s16 func_8005A8E0(s32);
extern s16 *D_800AE290[];
extern u8 *D_800AE294[];
extern u8 *D_800AE298[];
extern u8 *D_800A35E8[];
extern u8 D_800A3989[];
extern s8 D_800A3A25[];
extern u8 D_800A3644[];
extern u8 D_800A36E0[];
extern u8 D_800A36E1[];
extern void func_80063694(u8, s16, s16, s16);
extern void func_800636EC(u8, u8);
extern void func_80063AE0(s32, s32);
extern u8 D_800A35C8;
extern u8 D_800A35C9[];
extern u8 D_800A3338[];
extern char *strcat(char *, char *);
extern u8 *func_80012EA8(s32, u8 *);
extern u8 *D_800A38F8;
extern s32 D_800A37D0[];
extern u8 D_800A331CAbsolute[];
extern u8 *D_800BB9E4[];
extern char *strcpy(char *, const char *);
extern u8 D_800A3078[], D_800A3988[];
extern void func_8005C8D8(u8);
extern s32 func_8005CCECArgs(u8, s32);
extern void func_8005A9F4(s32, s16, s16, u8, u8, s32, u8, u8);
extern s16 *D_800B12FC[];
extern u8 *func_80057CCC(s32);
extern s16 *D_800B12FC[];
extern u8 *D_800A392C;
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
extern void *D_800A3954;
extern void *D_800A399C[];
extern void HeapFree(void *ptr);
extern char D_800BA058[], D_800A333C[];
extern u8 *func_80012EA8(s32, u8 *);
extern char *strcat(char *, char *);
extern void *D_800A399C[];
extern s32 D_800A393C;
extern s32 D_800A38DC;
extern u8 *D_800AE178[];
extern void *func_80058094(s32, void **, s32);
extern s32 D_800A393C;
extern u8 D_8009AF84[];
extern s32 D_800A3814[];
extern s32 D_800A3814Abs[];
extern char D_800BA058NM[] asm("D_800BA058.NON_MATCHING");
extern s32 D_8009A31C[];
extern s32 **D_800A3740;
extern u8 D_800A3860[][4];
extern u8 *D_800B9980[];
extern u8 D_800A3860[][4];
extern u8 D_800A3861U8[][4] asm("D_800A3861.NON_MATCHING");
extern u8 D_800A3862U8[][4] asm("D_800A3862.NON_MATCHING");
extern u8 D_800A3863U8[][4] asm("D_800A3863.NON_MATCHING");
extern u8 *D_800B60B8[];
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
extern void func_8005A7B8(u8, u8);
extern s16 func_8005A8E0(s32);
extern u8 *D_800A38A8;
extern u8 D_800A2F9DAbsolute[];
extern u8 *D_800A37FC[];
extern s32 *D_800A37D8[];
extern u8 D_800AEE3E[];
extern u8 D_800AEE41[];
extern u8 *D_800A3A84[];
extern s32 D_8009ABFC[];
extern u8 *D_800A37FC[];
extern s32 *D_800A37D8[];
extern u8 D_800AEE3D[];
extern u8 D_800AEE3E[];
extern u8 D_800AEE40[];
extern u8 D_800AEE41[];
extern u8 D_800AEE42[];
extern u8 D_800AEE43[];
extern s16 *D_800AE290[];
extern u8 *D_800A3628[];
extern u8 *D_800A35E4[];
extern char *D_8009AC1C[];
extern u8 *D_800A3868[];
extern u8 *D_800A3868[];
extern u8 *D_800A3868[];
extern u8 D_800A3658_w42[] asm("D_800A3658.NON_MATCHING");
extern s32 D_800A36F4_w42 asm("D_800A36F4.NON_MATCHING");
extern u8 *D_800A37E4_w42[] asm("D_800A37E4.NON_MATCHING");
extern s32 D_800BE998_w42[] asm("D_800BE998.NON_MATCHING");
extern u8 *D_800A36CC_w42[] asm("D_800A36CC.NON_MATCHING");
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
extern s32 D_800A2E84Absolute[];
extern u8 *func_8002D874(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80063874(void);
void *func_80058094(s32 arg0, void **arg1, s32 arg2);
void TextureLoadTim(void *arg0);
extern s32 D_800A3A5C, D_800A3358;
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
extern u8 *D_800A38FC[];
extern u8 *D_800A3900[];
extern u8 *D_800A39A0[];
extern u8 *D_800A39A4nm[] asm("D_800A39A4.NON_MATCHING");
extern u8 *D_800A39AC[];
extern u8 *D_800A35E4[];
extern u8 *D_800A35E8[];
extern s8 D_800A3A14;
extern void func_8005B688(u8 *first, u8 friction);
extern void func_8005B8B8(u8 *first, s32 value);
extern void func_80064000(s32 mode, s32 a, s32 b);
extern u8 D_8009B00C[];
extern u8 D_8009B028[];
extern u8 D_8009B02A[];
extern u16 D_8009B048[][7];
extern u8 D_8009B04A[];
extern u16 D_8009B050[][7];
extern u16 D_8009B054[][7];
extern u8 *D_8009A3F0[];
extern u8 *D_8009A400[];
extern u8 *D_8009A418[];
extern u8 D_800A3698;
extern u8 D_800A3A4C;
extern u8 *D_800A39D8;
extern u8 *D_800A369C;
extern u8 D_800BDD62[], D_800BDDBE[], D_800BDDC0[], D_800BDD64[];
extern u8 D_800BDD65[], D_800BDD66[], D_800BDD67[], D_800BDDC1[];
extern u8 D_800BDDC2[], D_800BDDC3[];
extern DRAWENV D_800BDD4C[];
extern DISPENV D_800BDE04[];
extern s32 D_800A367C;
extern u8 *D_8009A3F0[];
extern u8 *D_8009A400[];
extern u8 *D_8009A418[];
extern u32 *D_800A38C4;
extern u8 *D_800A369C;
extern u8 D_800A3A4C;
extern u8 D_800A35B4;
extern u8 *D_800A38D8;
extern u32 *D_800A38C4;
extern u8 *D_800A39C8Ptr[] asm("D_800A39C8");
extern u8 D_800A305B[];
extern u8 D_800A3884;
extern u8 *D_8009A404[];
extern u8 *D_8009A360[];
extern u8 *D_8009A430[];
extern u8 *D_8009A414[];
extern u8 *D_8009A400[];
extern u8 D_8009B198[];
extern DRAWENV D_800BDDA8[];
extern DRAWENV D_800BDD4C[];
extern DISPENV D_800BDE18[];
extern void GraphicsInitDoubleBuffer(s32);
extern void *func_8006654C(void *, s32);
extern void func_8005E8EC(s32, s32, s32);
extern void func_8005A7B8S32(s32, s32) asm("func_8005A7B8");
extern void func_8005A818(u8, u8, u8);
extern s16 func_8005A8E0(s32);
extern void func_8005A9F4(s32, s16, s16, u8, u8, s32, u8, u8);
extern s32 func_8005B0E4(s16, s32);
extern s32 func_8005A9F4W();
asm(".globl func_8005A9F4W");
extern s32 GetGp(void);
extern s32 D_8008CA4C[];
extern void func_80058D08(s32 gp);
extern u8 D_800A3884;
extern DISPENV D_800BDE04[];
extern volatile u8 D_800A3360;
extern s32 GetGp(void);
extern s32 D_8008CA4C[];
extern void func_80058D08(s32 gp);
extern u8 D_800A3884;
extern DISPENV D_800BDE04[];
extern volatile u8 D_800A3360;
extern s32 GetGp(void);
extern s32 D_8008CA4C[];
extern u8 D_800A3073[];
extern s32 D_800A335C;
extern void func_800663B0(void);
extern void func_80065C3C(void);
extern void func_800669B8(void);
extern s32 D_800A335C;
extern volatile u8 D_800A3360;
extern void func_8006733C(void);
extern void func_80067AB4(void);
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
extern char *D_8009AC1C[];
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
void ListInsertBefore(ListNode28 **head, ListNode28 *node, ListNode28 *before);
void ListRemoveNode(ListNode28 **head, ListNode28 *target);
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
void FileClose(void);
s32 func_8003C8B4(void);
s32 FileSeek(s32 *handle);
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
void func_80044DC4(u8 *arg0, s32 arg1, u8 *arg2);
void func_80044FF8(s32 arg0, s32 arg1);
void func_80045288(void);
void func_80045F70(void);
void func_80048568(void);
void func_80048700(void);
void func_800488A4(u8 *object);
void func_80048C90(void);
void func_8004B128(u8 *arg0);
void func_8004E808(void);
void func_8004EA34(void);
void func_8004FF3C(void);
void func_8004FF90(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800508E4(void);
void GraphicsSetColor(u8 red, u8 green, u8 blue);
s32 func_80050940(u8 *str);
void func_800514EC(u8 arg0, u8 arg1, u8 arg2);
void func_800524A0(u8 *arg0, s8 arg1);
void func_80052E18(void);
void func_80052FC4(s8 arg0);
void func_8005301C(void);
void func_800539F0(void);
void func_80055AA4(u8 arg0, s32 arg1);
void func_80055C78(u8 arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4, u8 arg5);
s32 func_80056B0C(s32 arg0, s32 arg1);
s32 func_80056B5C(s32 arg0, s32 arg1, s32 arg2);
void func_80056C84(s32 arg0, s32 arg1);
void func_80056F04(s32 arg0);
void func_80057008(s32 arg0);
void func_80057160(s32 arg0);
void func_80057A9C(void);
void func_80057BFC(void);
u8 *func_80057CCC(s32 arg0);
u8 *func_80057D50(s32 arg0);
void func_80057DD4(void);
void func_80057DE8(void);
void func_80057DFC(void);
void func_80057E10(void);
void GraphicsInitDoubleBufferSwapped(void);
void func_80057F34(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_80057FC8(s32 hide);
void func_80058000(s32 index, s32 *out);
void func_80058030(void);
void *func_80058094(s32 arg0, void **arg1, s32 arg2);
void func_80058148(void);
u8 TableFindByte(u8 value);
void func_80058D08(s32 gp);
void func_80058D14(u16 *src, u16 *dst, s32 arg2);
void func_80058D8C(void);
void func_8005957C(void);
s32 ColorPack555(s32 red, s32 green, u8 blue);
void func_80059648(void);
void func_800596F4(void);
void CdSetMixVolume(s32 arg);
void func_8005978C(void);
void CardCloseFile(s32 handle);
u8 CardDeleteFile(char *path);
void func_800598C4(void);
void func_800599E4(void);
s32 CardEnableEvents(void);
s32 CardCheckStatus(s32 arg0, u8 arg1);
s32 CardFindFirstFile(char *path, struct DIRENTRY *entry);
s32 CardFormat(s32 second);
void func_80059C2C(void);
void CardCloseEvents(void);
void func_80059DC4(void);
void func_80059E0C(void);
s32 func_80059F0C(s32 arg0);
s32 CardOpenFile(char *path, s32 flags);
s32 func_8005A000(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 buf);
s32 func_8005A0F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 buf);
s32 CardCountOtherFileBlocks(s32 arg0, char *name);
s32 func_8005A294(void);
void CardTestEvents(void);
s32 CardWaitForEvent(void);
void func_8005A414(void);
s32 CardScanDirectory(char *path, struct DIRENTRY *entry);
void func_8005A4E0(void);
void func_8005A6EC(u8 id, s32 arg1, void *dest);
void func_8005A7B8(u8 arg0, u8 arg1);
void func_8005A804(u8 a, u8 b, u8 c);
void func_8005A818(u8 first, u8 second, u8 third);
void func_8005A82C(void);
s16 func_8005A84C(void);
s16 func_8005AFF0(s8 arg0);
s32 func_8005B0E4(s16 arg0, s32 arg1);
s32 func_8005B138(u8 *str);
void func_8005B17C(u8 *dst, u32 idx, u16 dx, u16 dy, u16 ax, u16 ay);
u8 *func_8005B2AC(void);
void func_8005B2F0(void);
void func_8005B300(void);
u8 *func_8005B598(s32 left, s32 top, s32 right, s32 bottom, s32 depth,
                  u8 texture, u8 semiTrans);
void func_8005B688(u8 *first, u8 friction);
void func_8005B7DC(u8 *object, s32 index, u8 semiTrans);
void func_8005B8B8(u8 *object, s32 arg1);
void __maspsx_include_asm_hack_pad_8008F94C(void);
s32 func_8005BF68(void);
void func_8005C020(u8 *object, u8 *dest);
void func_8005C0F4(u8 *object, s32 value);
void func_8005C8D8(u8 index);
s32 func_8005CA4C(void);
void func_8005CBC8(s32 number);
void func_8005CC34(void);
s32 func_8005CCEC(s32 id, s32 delta, s32 max, s32 min);
void __maspsx_include_asm_hack_jtblpad_8005CCEC();
void func_8005CEDC(void);
void func_8005CF34(u8 *window, u8 code, u8 first, u8 second, s32 textId);
s32 func_8005DCF0(void);
void func_8005DEDC(s16 value);
void func_8005DF08(s32 a, s32 b, s32 c, u8 flag);
void func_8005DF50(s32 arg0, s32 arg1, s32 arg2);
void func_8005E3DC(void);
void func_8005E408(void);
void func_8005E43C(s32 value);
void func_8005E47C(void);
void func_8005E4A4(u8 *table);
void func_8005E550(s32 arg0);
void func_8005E5BC(s32 unused, s32 x, s16 y, s32 flag);
void func_8005E7F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8005EC5C(u8 arg0);
void func_8005ED04(s32 index);
s32 func_8005ED28(u8 x, u8 y);
void func_8005FE90(void);
u8 *func_8005FFA8(u8 x, u8 y);
void func_80060008(u8 arg0);
void func_80060E94(s32 arg0);
void func_80060F10(s32 a, s32 b, s16 c);
void func_80060F54(s32 arg0, s32 volume);
void func_80062874(s32 arg0, s32 arg1);
s32 ListHasClearFlags(u8 *node);
void ListSetFieldsAndEnable(u8 *node, s16 a, s16 b, s16 c);
void func_80062D38(s32 arg0, s32 arg1, u8 *arg2);
void func_80062F04(u8 index, u8 kind, u8 sub);
void func_80062F6C(s32 arg0, s32 arg1);
void func_80063180(s32 enabled);
void func_800631B4(void);
void func_80063538(s32 arg0, s32 arg1);
void func_80063638(u8 mode);
void func_80063694(u8 index, s16 dx, s16 dy, s16 code);
void func_800636EC(u8 index, u8 kind);
void func_80063770(u8 index);
void func_800637D8(u8 index);
void func_8006383C(void);
void func_80063874(void);
void func_80063A20(void);
void func_80063A28(void);
void func_80063AE0(s32 arg0, s32 arg1);
void func_80063E7C(void);
void func_80064174(void);
void func_800641EC(void);
void ListSetRangeFields(UnkNode1C *node, s32 low, s32 high, s16 value);
void func_80064898(void);
void func_8006499C(void);
void func_80064AB4(u8 *prim, u8 idx);
void func_80064C14(void);
void GraphicsInitDoubleBuffer(s32 mode);
s32 func_80065028(void);
s32 func_80065040(void);
void func_80065838(s32 arg0);
void func_800658F0(void);
void func_800663B0(void);
void func_80066730(void);
void func_800669B8(void);
void func_80066A24(u8 mode);
void func_80066B08(void);
void func_80067020(u8 *start, u8 *end, u8 delta);
void func_800679C4(u8 arg0);
void func_80067DFC(void);
void func_80067EA4(UnkObject24 *obj, u8 a, u8 b, s32 c, u8 d, s32 e);
u8 func_80067ECC(char *name);

void func_80067F34(s32 arg0, s32 arg1) {
    typedef struct UnkTextObj67F34 {
        u16 unk0;
        u8 unk2[4];
        u16 unk6;
        u16 unk8;
        u16 unkA;
        u8 unkC[6];
        u16 unk12;
        u8 unk14[6];
        s16 unk1A;
        struct UnkTextObj67F34 *unk1C;
        UnkPacket0C *unk20;
    } UnkTextObj67F34;
    extern char *D_8009A474[];
    extern s32 D_8009A31C[];
    extern char *D_8009AC1C[];
    extern s32 D_8009AC80[];
    extern s32 D_800A3668Absolute[];
    extern u8 *D_800A3854Absolute[];
    extern s32 D_800A3A54[];
    UnkTextObj67F34 *obj;
    UnkTextObj67F34 *next;
    u8 *name;
    u8 *entry;
    s32 value;
    s32 w;
    s32 sum;
    s32 sum2;
    s32 recordOff;
    s32 i;
    s32 j;
    s32 k;
    s32 idx;
    char *string;
    s32 cnt;
    char buf[0x48];

    obj = *(UnkTextObj67F34 **)((u8 *)D_800A3668Absolute - 0x5C +
                                (arg0 & 0xFF) * 4);
    func_8005A7B8S32(2, 3);
    strcpy(buf, D_8009A474[0]);
    strcat(buf, (char *)D_8009A31C[arg1 & 0xFF]);
    w = func_8005A8E0((s32)buf);
    sum = (0x140 - w) / 2;
    obj->unk6 = sum;
    obj->unkA = sum;
    obj->unk12 = obj->unk6;
    next = obj->unk1C;
    w = func_8005A8E0((s32)D_8009A474[0]);
    {
        s32 hdrH;
        UnkPacket0C *pktH;
        hdrH = next->unk1A;
        sum2 = obj->unk6 + w;
        next->unk6 = sum2;
        next->unk12 = sum2;
        string = (char *)D_8009A31C[arg1 & 0xFF];
        pktH = next->unk20;
        pktH->unk1 = 2;
        pktH->unk2 = 3;
        pktH->unk3 = 0;
        cnt = ((u8 *)D_800A3A54)[4];
        pktH->unk4 = hdrH;
        pktH->unk8 = (s32)string;
        next->unk1A = hdrH;
    }
    obj =
        *(UnkTextObj67F34 **)((u8 *)D_800A3854Absolute + (arg0 & 0xFF) * 4 + 4);
    i = 0;
    if (cnt > 0) {
        recordOff = (arg1 & 0xFF) * 0xC;
        do {
            j = 0;
            do {
                s32 hdrL;
                UnkPacket0C *pktL;
                s32 flagL;
                s32 t;
                switch (j) {
                case 0:
                    k = 0;
                    entry = (u8 *)D_8009AC1C;
                    name = (u8 *)(i * 0xE8) +
                           (u32) * (u8 **)((u8 *)D_800A3668Absolute - 0x74);
                    do {
                        if (strcmp((char *)name, *(char **)entry) == 0) {
                            break;
                        }
                        k++;
                        entry += 4;
                    } while (k < 0x18);
                    asm("" : "=r"(idx) : "0"(k));
                    value = D_8009AC80[idx & 0xFF];
                    break;
                case 1:
                    value =
                        *(i * 0xE8 + *(u8 **)((u8 *)D_800A3668Absolute - 0x74) +
                          recordOff + 0x1C);
                    break;
                case 2:
                    value =
                        *(i * 0xE8 + *(u8 **)((u8 *)D_800A3668Absolute - 0x74) +
                          recordOff + 0x1D);
                    break;
                case 3:
                    value =
                        *(i * 0xE8 + *(u8 **)((u8 *)D_800A3668Absolute - 0x74) +
                          recordOff + 0x1E);
                    break;
                case 4:
                    value =
                        *(i * 0xE8 + *(u8 **)((u8 *)D_800A3668Absolute - 0x74) +
                          recordOff + 0x1F);
                    break;
                case 5:
                    value = *(s32 *)(i * 0xE8 +
                                     *(u8 **)((u8 *)D_800A3668Absolute - 0x74) +
                                     recordOff + 0x20);
                    break;
                }
                flagL = 0;
                if (j != 0) {
                    t = j != 5;
                    flagL = t;
                    asm("" : : "r"(t));
                }
                hdrL = obj->unk1A;
                pktL = obj->unk20;
                pktL->unk1 = 2;
                pktL->unk2 = 3;
                pktL->unk8 = value;
                pktL->unk3 = flagL;
                pktL->unk4 = hdrL;
                obj->unk1A = hdrL;
                obj = obj->unk1C;
                j++;
            } while (j < 6);
            i++;
        } while (i < ((u8 *)D_800A3A54)[4]);
    }
}

INCLUDE_ASM("asm/nonmatchings/memory_card_menu", func_80068220);

void func_800686FC(s32 arg0, s32 arg1) {
    extern s32 D_800A3914[];
    extern u8 *D_800A37D4;
    extern u8 *D_800A3870;
    extern s8 D_800A3944;
    extern s8 D_800A39DC;
    extern s32 D_800A3A54[];
    extern u8 *D_800A3854Absolute[];
    extern u8 *D_800A3900Ptr asm("D_800A3900.NON_MATCHING");
    extern u8 *D_800A360C;
    extern u8 *D_800A3858;

    func_8005B8B8(D_800A3900Ptr, 0xFF);
    if ((arg0 & 0xFF) == 9 && ((u8 *)D_800A3A54)[4] != 0) {
        if (D_800A37D4 != 0) {
            func_8005B688(D_800A37D4, 1);
            func_8005B8B8(D_800A37D4, 0xFF);
        }
        if (D_800A3870 != 0) {
            func_8005B688(D_800A3870, 1);
            func_8005B8B8(D_800A3870, 0xFF);
        }
    } else {
        func_8005B8B8(D_800A360C, 0xFF);
    }
    if (D_800A3914[0] != 0) {
        func_8005B8B8((u8 *)D_800A3914[0], 0xFF);
    }
    switch ((arg0 & 0xFF) - 9) {
    case 0:
        if (((u8 *)D_800A3A54)[4] != 0) {
            func_80057F34(arg1 & 0xFF, 0, 0x57, 0x140, 0x7B, 0xA);
        }
        break;
    case 1:
        func_80057F34(arg1 & 0xFF, 0, 0x9D, 0x140, 0x35, 0xA);
        break;
    case 3:
    case 7:
    case 8:
        func_80057F34(arg1 & 0xFF, 0, 0x39, 0x140, 0x99, 0xA);
        break;
    }
    switch (arg0 & 0xFF) {
    case 0xA:
    case 0xC:
        goto hideIt;
    }
    if ((u8)(arg0 - 0x10) < 2) {
    hideIt:
        func_8005B8B8(D_800A3858, 0xFF);
    } else if ((arg0 & 0xFF) == 9) {
        if (((u8 *)D_800A3A54)[4] != 0) {
            if (D_800A37D4 != 0) {
                func_8005B688(D_800A3854Absolute[D_800A3944 + 1], 1);
                func_8005B8B8(D_800A3854Absolute[D_800A3944 + 1], 0xFF);
            }
            if (D_800A3870 != 0) {
                func_8005B688(D_800A3854Absolute[D_800A39DC + 1], 1);
                func_8005B8B8(D_800A3854Absolute[D_800A39DC + 1], 0xFF);
            }
        }
    }
}

/* The original toolchain padded this odd-length jump table with one zero
 * word; the C switch regenerates the table, this restores the pad. */
void __maspsx_include_asm_hack_jtblpad_800686FC() {
    __asm__(".section .rodata # maspsx-keep \n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

void func_8006894C(s32 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4) {
    extern UnkNode1C *D_800A360C[];
    extern UnkNode1C *D_800A3858Absolute[] asm("D_800A3858.NON_MATCHING");
    UnkNode1C *node;
    u8 *other;
    s32 index;
    s32 v1;

    index = arg0 & 0xFF;
    node = D_800A360C[arg0 & 0xFF];
    if (node != NULL) {
        do {
            node->unkE = arg3;
            node->unk6 = node->unk12 + arg1;
            node->unkA = node->unk12 + arg2;
            node = node->next;
            index = arg0 & 0xFF;
        } while (node != NULL);
    }
    node = D_800A3858Absolute[arg0 & 0xFF];
    if (arg4 != 0) {
        other = (u8 *)D_800A3858Absolute[(arg0 ^ 1) & 0xFF];
        v1 = *(s16 *)(other + 8);
        v1 -= *(s16 *)(other + 0xC);
    } else {
        v1 = 0;
    }
    if (node != NULL) {
        do {
            node->unk6 = node->unk12 + arg1;
            if (arg4 != 0) {
                node->unk8 = node->unkC + v1;
            }
            node->unkE = arg3;
            node->unkA = node->unk12 + arg2;
            node = node->next;
        } while (node != NULL);
    }
}

void func_80068A3C(u8 *head, u8 *other, s32 delta, s32 limit, s32 mid) {
    s16 base;

    if (delta > 0) {
        base = *(s16 *)(head + 8);
        if (limit < base + delta) {
            delta = limit - base;
        }
    } else {
        if (delta < 0) {
            if ((s32) * (s16 *)(other + 8) + delta < mid) {
                delta = mid - *(s16 *)(other + 8);
            }
        }
    }
    if (delta != 0) {
        if (head != 0) {
            do {
                *(u16 *)(head + 8) += delta;
                head = *(u8 **)(head + 0x1C);
            } while (head != 0);
        }
    }
}

extern s32 D_800A3830Absolute[];
extern s32 D_800A3830Absolute2[];
extern s32 D_800A37F0Absolute[];
extern s32 D_800A37F0Absolute2[];
extern s32 D_800A37F0Absolute3[];
extern u8 D_800A39E4NM[] asm("D_800A39E4.NON_MATCHING");
extern u8 D_800A3A58NM[] asm("D_800A3A58.NON_MATCHING");
extern s16 D_800B9B84NM[] asm("D_800B9B84.NON_MATCHING");
extern u8 *D_800A3858NM[] asm("D_800A3858.NON_MATCHING");
extern u8 *D_800A3918NM[] asm("D_800A3918.NON_MATCHING");
extern u8 *D_800A3918NB[] asm("D_800A3918.NON_MATCHING");
void func_80068AC4(s32 arg0, s32 arg1, s32 arg2) {
    extern u8 D_800A3944;
    s32 zero;
    s32 delta;
    s32 threshold;
    s32 delta2;
    s32 sum;
    s32 posflag;
    s32 limit;
    s32 limitSave;
    s32 dneg;
    s32 val;
    s32 idx;
    u8 *head;
    u8 *other;
    u8 *walk;
    threshold = 5;
    if (arg0 & (~arg1)) {
        D_800A3830Absolute2[0] = 0;
        limitSave = 1;
    } else {
        D_800A3830Absolute[0] = D_800A3830Absolute2[0] + 1;
        if (threshold < D_800A3830Absolute[0]) {
            D_800A37F0Absolute[0] =
                D_800A37F0Absolute2[0] + (D_800A37F0Absolute2[0] / 2);
            if (0x41 <= D_800A37F0Absolute[0]) {
                limitSave = 0x40;
            } else {
                goto noStore;
            }
        } else {
            return;
        }
    }
    D_800A37F0Absolute3[0] = limitSave;
noStore:
    if (arg2 & 0xFF) {
        delta = D_800A37F0Absolute3[0];
    } else {
        dneg = D_800A37F0Absolute3[0];
        delta = -dneg;
    }

    val = D_800A39E4NM[0];
    if ((val & 0xFF) == 9) {
        limit = 0x7B;
    } else if ((val & 0xFF) == 0xA) {
        limit = 0x35;
    } else if (((val & 0xFF) == 0xC) || ((val - 0x10) < 2U)) {
        limit = 0x99;
    }
    limit = limit - 0xD;
    if (D_800A39E4NM[0] == 9) {
        if (D_800A3A58NM[0] == 0) {
            return;
        }
    }
    if (D_800A39E4NM[0] == 0xC) {
        if (D_800B9B84NM[0] == 0) {
            return;
        }
    }
    idx = 0;
    if (D_800A39E4NM[0] == 9) {
        idx = D_800A3944;
    }
    head = D_800A3858NM[idx];
    if ((*((s16 *)(head + 8))) >= 0) {
        if ((*((s16 *)(D_800A3918NM[idx] + 8))) < limit) {
            return;
        }
    }
    other = D_800A3918NB[idx];
    delta2 = delta;
    zero = (s32)0;
    if (delta2 > 0) {
        sum = (*((s16 *)(head + 8))) + delta2;
        posflag = zero < ((s32)sum);
        if (posflag != 0) {
            delta2 = -(*((s16 *)(head + 8)));
        }
    } else if (delta2 < 0) {
        if (((*((s16 *)(other + 8))) + delta2) < limit) {
            delta2 = limit - (*((s16 *)(other + 8)));
        }
    }
    if (delta2 == 0) {
        return;
    }
    walk = head;
    if (walk != 0) {
        do {
            *((u16 *)(walk + 8)) += delta2;
            walk = *((u8 **)(walk + 0x1C));
        } while (walk != 0);
    }
}

typedef struct UnkTextObj {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    u8 unkC[6];
    s16 unk12;
    u8 unk14[6];
    s16 unk1A;
    struct UnkTextObj *unk1C;
    UnkPacket0C *unk20;
} UnkTextObj;
extern UnkTextObj *D_800A3900Obj asm("D_800A3900.NON_MATCHING");
extern UnkTextObj *D_800A360C;
extern UnkTextObj *D_800A3858;
extern UnkTextObj *D_800A3918;
UnkTextObj *func_8005B314(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
UnkTextObj *func_8005BF8C(s32, s32);
s32 func_8005B0E4(s16, s32);

void func_80068CE4(void) {
    extern char *strcpy(char *, const char *);
    extern char *D_8009A498[];
    extern char *D_8009A4B0[];
    extern s32 D_8009B1C4[];
    extern s32 D_8009A31C[];
    extern char D_800B9B54[];
    extern s8 D_800B9B6E[];
    extern u8 D_800B9BB4[];
    UnkTextObj *obj;
    UnkTextObj *tail;
    /* One packet pointer per section: a single shared pointer takes one
     * register, retail uses a different one in each section. */
    UnkPacket0C *titlePkt;
    UnkPacket0C *subPkt;
    UnkPacket0C *rowPkt;
    UnkPacket0C *hdrPkt;
    UnkPacket0C *cellPkt;
    u8 *record;
    char buf[0x40];
    s32 value;
    s32 flag;
    s32 w;
    s32 label;
    s32 titleW;
    s32 titleX;
    s32 x;
    s32 y;
    s32 i;
    s32 j;
    for (i = 0; i < 2; i++) {
        tail = func_8005B314(0, 0x27, 0x140, 0xC8, 0, 0x10, 0x10, 0x10, 1, 1);
        if (i == 0) {
            D_800A3900Obj = tail;
        } else {
            D_800A3900Obj->unk1C = tail;
        }
        tail->unk1A = 0x3FD;
    }

    tail = func_8005BF8C(0, 0x2A);
    D_800A360C = tail;
    func_8005A7B8S32(2, 3);
    strcpy(buf, D_800B9B54);
    strcat(buf, D_8009A498[0]);
    /* After the call, so the li lands in the call's delay slot. */
    y = 0x39;
    titleW = func_8005A8E0((s32)buf);
    titleX = (0x140 - titleW) / 2;
    tail->unk6 = titleX;
    tail->unkA = titleX;
    tail->unk1A = 0x32;
    titlePkt = tail->unk20;
    titlePkt->unk1 = 2;
    titlePkt->unk2 = 3;
    titlePkt->unk8 = (s32)D_800B9B54;
    titlePkt->unk3 = 0;
    titlePkt->unk4 = 0x32;
    tail->unk1A = 0x32;
    titleW = func_8005A8E0((s32)D_800B9B54);
    obj = func_8005BF8C(tail->unk6 + titleW, 0x2A);
    obj->unk1A = 0x32;
    value = (s32)D_8009A498[0];
    subPkt = obj->unk20;
    subPkt->unk1 = 2;
    subPkt->unk2 = 3;
    subPkt->unk8 = value;
    subPkt->unk3 = 0;
    subPkt->unk4 = 0x32;
    obj->unk1A = 0x32;
    tail->unk1C = obj;
    tail = obj;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 2; j++) {
            obj = func_8005BF8C((j != 0) ? (0xF0) : (0x40), y);
            obj->unk1A = 0x32;
            if (j != 0) {
                switch (i) {
                case 0:
                    value = D_800B9B6E[0];
                    break;

                case 1:
                    value = D_800B9B6E[1];
                    break;

                case 2:
                    value = D_800B9B6E[2];
                    break;

                case 3:
                    value = D_800B9B6E[3];
                    break;

                case 4:
                    value = D_800B9B6E[4];
                    break;
                }

                obj->unk0 = 5;
            } else {
                value = (s32)D_8009A498[i + 1];
            }

            w = obj->unk1A;
            rowPkt = obj->unk20;
            rowPkt->unk1 = 2;
            rowPkt->unk2 = 3;
            rowPkt->unk8 = value;
            rowPkt->unk3 = j;
            rowPkt->unk4 = w;
            obj->unk1A = w;
            tail->unk1C = obj;
            tail = obj;
        }

        y += 0xF;
    }

    for (i = 0; i < 4; i++) {
        x = D_8009B1C4[i];
        switch (i) {
        case 1:
            x += 4;
            break;

        case 2:
            x += 8;
            break;

        case 3:
            x += 0xA;
            break;
        }

        obj = func_8005BF8C(x, 0x89);
        obj->unk1A = 0x32;
        label = (s32)D_8009A4B0[i];
        hdrPkt = obj->unk20;
        hdrPkt->unk1 = 2;
        hdrPkt->unk2 = 3;
        hdrPkt->unk8 = label;
        hdrPkt->unk3 = ((u32)(i - 1)) < 2;
        hdrPkt->unk4 = 0x32;
        obj->unk1A = 0x32;
        tail->unk1C = obj;
        tail = obj;
    }

    y = 0;
    for (i = 0; i < 0x11; i++) {
        record = &D_800B9BB4[i * 0xC];
        for (j = 0; j < 4; j++) {
            obj = func_8005BF8C(D_8009B1C4[j], y);
            if ((i == 0) && (j == 0)) {
                D_800A3858 = obj;
            } else {
                tail->unk1C = obj;
            }
            obj->unk1A = 0;
            switch (j) {
            case 1:
            case 2:
                obj->unk0 = 5;
                break;

            case 3:
                obj->unk0 = 6;
                break;
            }
            flag = 0;
            switch (j) {
            case 0:
                value = D_8009A31C[i];
                break;

            case 1:
                value = *((s16 *)(record + 4));
                flag = 1;
                break;

            case 2:
                value = *((s16 *)(record + 6));
                flag = 1;
                break;

            case 3:
                value = *((s32 *)(record + 8));
                break;
            }

            cellPkt = obj->unk20;
            cellPkt->unk1 = 2;
            cellPkt->unk2 = 3;
            cellPkt->unk8 = value;
            cellPkt->unk3 = flag;
            cellPkt->unk4 = 0;
            obj->unk1A = 0;
            tail = obj;
        }

        if (i == 0x10) {
            D_800A3918 = tail;
        }
        y += 0xF;
    }

    func_8005DEDC(0x3E8);
}

/* The original toolchain padded this odd-length jump table with one zero
 * word; the C switch regenerates the table, this restores the pad. */
void __maspsx_include_asm_hack_jtblpad_80068CE4() {
    __asm__(".section .rodata # maspsx-keep \n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

INCLUDE_ASM("asm/nonmatchings/memory_card_menu", func_800691D4);

typedef struct UnkBlockOffsets {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} UnkBlockOffsets;
extern UnkBlockOffsets *D_800A3A30;
extern void *D_800A3A24[];
extern void *D_800A336C;
extern s32 D_800A3370, D_800A3374, D_800A3378Small;

void func_80069744(void) {
    s32 block;

    block = (s32)func_80058094(0xB, (void **)D_800A3A24 + 3, 0);
    D_800A336C = (void *)block;
    if (block != 0) {
        D_800A3370 = block + D_800A3A30->unk0;
        D_800A3374 = block + D_800A3A30->unk4;
        D_800A3378Small = block + D_800A3A30->unk8;
        func_800641EC();
    }
}

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

extern s8 *D_8009AD58[];
extern s16 func_8005A84C(void);

void func_800697EC(u8 mode) {
    UnkTextObj *obj;
    UnkTextObj *prev;
    /* One packet pointer per section, so each is a block-local pseudo. */
    UnkPacket0C *titlePkt;
    UnkPacket0C *rowPkt;
    s8 *buf;
    s8 *p;
    /* u16, so `i + 1` stays a copy (no biv) and the test below is a shift. */
    u16 i;
    s32 x;
    s32 w;
    s32 title;
    s32 width;
    /* Packet bytes held in locals: retail sets the first at the loop top and
     * hoists the second, and that pins the schedule. */
    s32 pktType;
    s32 pktMode;
    s32 j;
    s8 c;
    /* Unused, but retail's frame has 0x40 bytes of locals. */
    char unused[0x40];

    j = 0;
    do {
        prev = func_8005B314(0, 0x27, 0x140, 0xC8, 0, 0x10, 0x10, 0x10, 1, 1);
        if (j == 0) {
            D_800A3900Obj = prev;
        } else {
            D_800A3900Obj->unk1C = prev;
        }
        prev->unk1A = 0x3FD;
        j += 1;
    } while (j < 2);

    prev = func_8005BF8C(0, 0x2A);
    D_800A360C = prev;
    func_8005A7B8S32(2, 3);
    w = func_8005B0E4(0x140, (s32)D_8009AD58[mode]);
    prev->unk6 = w;
    prev->unkA = w;
    prev->unk1A = 0x32;
    title = (s32)D_8009AD58[mode];
    titlePkt = prev->unk20;
    titlePkt->unk1 = 2;
    titlePkt->unk2 = 3;
    titlePkt->unk8 = title;
    titlePkt->unk3 = 0;
    titlePkt->unk4 = 0x32;
    prev->unk1A = 0x32;
    if (mode == 0) {
        buf = (s8 *)D_800A3370;
    } else {
        buf = (s8 *)D_800A3374;
    }
    func_8005A7B8S32(2, 4);
    width = func_8005A84C();
    i = 0;
    x = 0;
    while (1) {
        pktType = 2;
        p = buf + (s16)i;
        c = *p;
        if (c == '%') {
            D_800A3918 = prev;
            break;
        }
        if (c == '\n') {
            x += width / 4;
        } else {
            obj = func_8005BF8C(0, x);
            if (*p == '*') {
                p = buf + ((s16)i + 1);
                obj->unk2 = 0xF0;
                obj->unk3 = 0x40;
                obj->unk4 = 0x40;
            }
            pktMode = 4;
            w = func_8005B0E4(0x140, (s32)p);
            rowPkt = obj->unk20;
            obj->unk12 = w;
            obj->unk6 = w;
            obj->unkA = w;
            obj->unk1A = 0;
            rowPkt->unk1 = pktType;
            rowPkt->unk2 = pktMode;
            rowPkt->unk8 = (s32)p;
            rowPkt->unk3 = 0;
            rowPkt->unk4 = 0;
            obj->unk1A = 0;
            if ((i << 16) == 0) {
                D_800A3858 = obj;
            } else {
                prev->unk1C = obj;
            }
            prev = obj;
        }
        x += width;
        if (buf[(s16)i] != 0) {
            do {
                i++;
            } while (buf[(s16)i] != 0);
        }
        i++;
    }
    func_8005DEDC(0x3E8);
}

s32 func_80069A90(s32 arg0) {
    switch (arg0 & 0xFF) {
    case 0:
    case 1:
    case 3:
    case 6:
    case 15:
        return 0;
    case 2:
    case 4:
    case 5:
    case 7:
    case 8:
    case 11:
        return 1;
    case 10:
        return 3;
    case 12:
    case 16:
    case 17:
        return 4;
    case 34:
    case 36:
    case 40:
        return 5;
    case 35:
        return 6;
    case 9:
    case 14:
    case 33:
        return 7;
    default:
        return 0xFF;
    }
}

/* The original toolchain padded this odd-length jump table with one zero
 * word; the C switch regenerates the table, this restores the pad. */
void __maspsx_include_asm_hack_jtblpad_80069A90() {
    __asm__(".section .rodata # maspsx-keep \n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

void func_80069AFC(s32 arg0) {
    extern void *D_800A3914[];
    extern void *D_800A3A24[];
    extern s8 D_800A307C[];
    extern s32 D_8009A2D4[];
    extern s32 D_8009A2F4[];
    u8 group8;
    extern s32 func_8005B0E4(s16, s32);
    s32 group;
    s32 index;
    s32 value;
    u8 *obj;
    u8 *child;
    switch (arg0 & 0xFF) {
    case 0:

    case 1:

    case 3:

    case 6:

    case 15:
        group = 0;
        break;

    case 2:

    case 4:
        do {
        } while (0);

    case 5:

    case 7:

    case 8:

    case 11:
        group = 1;
        break;

    case 10:
        group = 3;
        break;

    case 12:

    case 16:

    case 17:
        group = 4;
        break;

    case 34:

    case 36:

    case 40:
        group = 5;
        break;

    case 35:
        group = 6;
        break;

    case 9:

    case 14:

    case 33:
        group = 7;
        break;

    default:
        group = 0xFF;
        break;
    }

    group = group & 0xff;
    group8 = group;
    index = group8;
    if (group == 0xFF) {
        u8 *retObj;
        retObj = (u8 *)D_800A3914[0];
        if (retObj != 0) {
            *((s16 *)(retObj + 0x1A)) = -0x32;
            return;
        }
    }
    func_8005A7B8S32(2, 2);
    if (((s8 *)D_800A3A24)[0] == 2) {
        value = func_8005B0E4(0x140, D_8009A2F4[index]);
    } else {
        value = func_8005B0E4(0x140, D_8009A2D4[index]);
    }
    obj = (u8 *)D_800A3914[0];
    *((s16 *)(obj + 6)) = value;
    *((s16 *)(obj + 0x1A)) = 0x32;
    child = *((u8 **)(obj + 0x20));
    if ((((s8 *)D_800A3A24)[0] == 2) && (D_800A307C[0] != 6)) {
        *((s32 *)(child + 8)) = D_8009A2F4[index];
    } else {
        *((s32 *)(child + 8)) = D_8009A2D4[index];
    }
    asm(".rdata");
    asm(".long 0");
    asm(".text");
}

INCLUDE_ASM("asm/nonmatchings/memory_card_menu", func_80069C60);
INCLUDE_RODATA("asm/nonmatchings/memory_card_menu", D_8008FC60);

extern char *D_800A35F4;
extern char *D_800A3604;
extern char *D_800A366C;
extern char *D_800A3978;
extern char *D_800A3A0C;

void func_80069E88(void) {
    D_800A366C = (char *)0x80010000;
    D_800A3978 = (char *)0x8001000C;
    D_800A3A0C = (char *)0x80010AEC;
    D_800A35F4 = (char *)0x8001000C;
    D_800A3604 = (char *)0x80010000;
}

extern u8 D_800A3938;
extern u8 D_800A3808;
extern u8 D_800A337C;
s32 CardCheckStatus(s32 arg0, u8 arg1);

s32 func_80069EB8(void) {
    u8 status;
    u8 formatResult;
    u8 result;

    status = CardCheckStatus(D_800A337C, 0);
    D_800A3938 = status;
    if (status == 1) {
        result = 1;
    } else if (status == 2) {
        result = 2;
    } else {
        formatResult = CardFormat(D_800A337C);
        if (formatResult != 0) {
            D_800A3808 = 0;
            return 1;
        }
        result = 4;
    }
    D_800A3808 = result;
    return 0;
}

s32 func_80069F30(void) {
    u8 slot;
    u8 status;

    D_800A3808 = 0;
    if (D_800A337C == 0xFF) {
        slot = 0;
    } else {
        slot = D_800A337C;
    }
    status = CardCheckStatus(slot, 0);
    D_800A3938 = status;
    if (status == 1) {
        D_800A3808 = 1;
        return 0;
    }
    if (status == 2) {
        if (D_800A337C == 0xFF) {
            status = CardCheckStatus(1, 0);
            D_800A3938 = status;
        }
        switch (D_800A3938) {
        case 1:
            D_800A3808 = 1;
            return 0;
        case 2:
            D_800A3808 = 2;
            return 0;
        case 0:
        case 3:
            D_800A337C = 1;
            break;
        }
    } else {
        D_800A337C = slot;
    }
    status = func_80059F0C(D_800A337C);
    D_800A3938 = status;
    if (status == 2) {
        D_800A3808 = 2;
        return 0;
    }
    if (status == 1) {
        D_800A3808 = 3;
        return 0;
    }
    if (status == 3) {
        D_800A3808 = 0xD;
        return 0;
    }
    return 1;
}

extern u8 D_800A3938;
extern u8 D_800A3808;
extern u8 D_800A337C;
s32 CardCheckStatus(s32 arg0, u8 arg1);

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
extern s32 CardCountOtherFileBlocks(s32, char *);
u8 CardGetOtherFileBlocks(void) {
    return CardCountOtherFileBlocks(D_800A337C, D_8008FC60);
}

INCLUDE_ASM("asm/nonmatchings/memory_card_menu", func_8006A15C);

INCLUDE_ASM("asm/nonmatchings/memory_card_menu", func_8006A3E0);

INCLUDE_ASM("asm/nonmatchings/memory_card_menu", func_8006A7C8);

s32 func_8006AA70(void) {
    extern s32 D_800A3380[2];
    extern s32 D_800A3388[2];
    extern char D_8009B1E4[];
    extern void *memcpy(void *, const void *, size_t);
    char path[0x40];
    struct DIRENTRY entry;
    u8 created;
    s32 fd;
    s32 result;
    u8 *clear;

    D_800A3808 = 0;
    if (D_800A337C == 0) {
        memcpy(path, D_800A3380, 6);
    } else {
        memcpy(path, D_800A3388, 6);
    }
    strcat(path, D_8008FC60);
    result = CardFindFirstFile(path, &entry);
    created = 0;
    if ((result & 0xFF) == 0) {
        fd = CardOpenFile(path, 0x200);
        if (fd == -1) {
            D_800A3808 = 5;
            return 0;
        }
        CardCloseFile(fd);
        created = 1;
        if ((CardFindFirstFile(path, &entry) & 0xFF) == 0) {
            D_800A3808 = 0xA;
            return 0;
        }
    }
    if (created != 0) {
        if ((func_8005A0F0((s32)&entry, 0, 4, D_800A337C, (s32)D_8009B1E4) &
             0xFF) == 0) {
            D_800A3808 = 8;
            return 0;
        }
    }
    if ((func_8005A0F0((s32)&entry, 4, 0x16, D_800A337C, (s32)D_800A3604) &
         0xFF) == 0) {
        D_800A3808 = 8;
        return 0;
    }
    if (created != 0) {
        *(s32 *)D_800A3A0C = 0;
        clear = (u8 *)D_800A3A0C;
        clear[4] = 0;
        clear[0x14] = 0;
        clear[0x34] = 0;
        if ((func_8005A0F0((s32)&entry, 0x1A, 3, D_800A337C, (s32)D_800A3A0C) &
             0xFF) == 0) {
            D_800A3808 = 8;
            return 0;
        }
    }
    return 1;
}

extern char *D_800A35F4;
extern u8 D_800A3A58;
void func_8006ABF8(void) {
    char *p;
    char *q;
    char *row;
    s32 i;
    s32 j;
    s32 k;

    i = 0;
    do {
        row = D_800A35F4 + i * 0xE8;
        row[0] = 0;
        row[0x19] = 0;
        j = 0;
        do {
            /* Preserve GCC 2.7.2 pointer-induction lowering. */
            p = row - (-j);
            k = 3;
            q = p + 3;
            p[0x1C] = 0;
            p[0x1D] = 0;
            p[0x1E] = 0;
            p[0x1F] = 0;
            *(s32 *)&p[0x20] = -1;
            do {
                q[0x24] = 0x20;
                k--;
                q--;
            } while (k >= 0);
            j += 0xC;
        } while (j < 0xCC);
        i++;
    } while (i < 0xC);
    D_800A3A58 = 0;
}

extern char *D_8009AC1C[];
extern char D_800BB9B4[];
void func_8006AC78(s32 arg0) {
    char *label;
    s32 mask;
    s32 index;

    index = 0;
    mask = arg0 & 0xFF;
    do {
        label = D_8009AC1C[index];
        if (strcmp(D_800BB9B4 + mask * 0x18, label) == 0) {
            D_800A36E0[mask] = index;
            return;
        }
        index += 1;
    } while (index < 0x18);
}

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

extern u8 D_800A3068w17[] asm("D_800A3068.NON_MATCHING");
extern u8 D_800A3069w17[] asm("D_800A3069.NON_MATCHING");
extern u8 D_800A3A24w17[] asm("D_800A3A24.NON_MATCHING");
extern u8 D_800A307Cw17[] asm("D_800A307C.NON_MATCHING");
extern u8 D_800BBA24w17[] asm("D_800BBA24.NON_MATCHING");

void func_8006ADC4(u8 arg0, char *arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5,
                   u8 arg6, u8 arg7) {
    typedef struct {
        s32 words[0x3A];
    } SaveEntry;

    s32 count;
    s32 iv;
    s32 k;
    s32 i;
    s32 one;
    u32 d3;
    u32 lt5;
    u32 lt10;
    u32 d7;
    u32 lt11;
    u32 table;
    u32 d0;
    u32 d0x16;
    s32 off;
    u8 *rec;
    u8 *src;
    u32 sum;

    if (D_800A3A58 != 0) {
        count = D_800A3A58 - 1;
        if (D_800A3A58 == 0xC) {
            count = 10;
        } else {
            D_800A3A58 = D_800A3A58 + 1;
        }
        i = count;
        if (i >= 0) {
            k = i * 29;
            iv = k << 3;
            do {
                *(SaveEntry *)(iv + (u32)D_800A35F4 + 0xE8) =
                    *(SaveEntry *)(iv + (u32)D_800A35F4);
                i--;
                iv -= 0xE8;
            } while (i >= 0);
        }
    } else {
        D_800A3A58 = D_800A3A58 + 1;
    }

    strcpy(D_800A35F4, arg1);

    i = 0;
    one = 1;
    d3 = arg3;
    lt5 = d3 < 5;
    lt10 = d3 < 10;
    d7 = arg7;
    lt11 = d7 < 11;
    table = (u32)D_800BBA24w17;
    D_800A35F4[0x19] = D_800A3068w17[arg0 * 2] | (D_800A3069w17[arg0 * 2] << 1);
    d0 = arg0;
    d0x16 = d0 << 4;
    off = 0x1C;

outer:
    do {
        rec = D_800A35F4 + off;
        if (i == arg2) {
            if (arg5 == 0) {
                if ((d3 = d3) == 0 && arg6 == 0) {
                    rec[1] = one;
                } else {
                    rec[1] = 0;
                }
                if (d7 == 2) {
                    rec[2] = 0;
                    rec[3] = 0;
                } else {
                    if (lt5 != 0) {
                        rec[2] = one;
                    } else {
                        rec[2] = 0;
                    }
                    if ((lt10 = lt10) != 0 && lt11 == 0) {
                        rec[3] = one;
                    } else {
                        rec[3] = 0;
                    }
                }
                rec[0] = one;
            } else {
                rec[0] = 0;
                rec[1] = 0;
                rec[2] = 0;
                rec[3] = 0;
            }
            *(s32 *)(rec + 4) = arg4;
        } else {
            rec[0] = 0;
            rec[1] = 0;
            rec[2] = 0;
            rec[3] = 0;
            *(s32 *)(rec + 4) = 0x7FFFFFFF;
        }
        sum = (d0x16 + d0) * 4 + table;
        src = (u8 *)(i * 4 + sum);
        for (count = 0; count < 4; count++) {
            *(rec + count + 8) = src[count];
        }
        i++;
        off += 0xC;
    } while (0);
    if (i < 17) {
        goto outer;
    }

    D_800A35F4[0x1A] = D_800A3A24w17[arg0];
    D_800A35F4[0x1B] = D_800A307Cw17[arg0];
}

typedef struct {
    s32 words[0x3A];
} CardMoveRecord;
extern char *D_800A35F4;

void func_8006B088(s32 arg0) {
    CardMoveRecord buf;
    s32 n;

    if ((arg0 & 0xFF) == 0) {
        return;
    }
    buf = ((CardMoveRecord *)D_800A35F4)[arg0 & 0xFF];
    n = (arg0 & 0xFF) - 1;
    while (n >= 0) {
        ((CardMoveRecord *)D_800A35F4)[n + 1] =
            ((CardMoveRecord *)D_800A35F4)[n];
        n--;
    }
    *(CardMoveRecord *)D_800A35F4 = buf;
}

void func_8006B1CC(u8 arg0, s32 arg1, u8 arg2, u8 arg3, u32 arg4, u8 arg5,
                   u8 arg6, u8 arg7) {
    u8 j;
    u8 *tbl;
    u8 i;
    s32 slot;
    u8 driver;
    u32 seven;
    s32 m;
    u8 *rec;
    u8 *src;
    s32 row;
    s32 p;
    s32 sum;
    s32 slotM;

    slot = arg1;
    rec = (u8 *)D_800A35F4 + (slot & 0xFF) * 0xE8 + (arg2 * 0xC + 0x1C);
    driver = arg0;
    seven = arg7;
    if (arg5 == 0) {
        rec[0] = rec[0] + 1;
        if (arg3 == 0) {
            if (arg6 == 0) {
                rec[1] = rec[1] + 1;
            }
        }
        if (seven >= 6) {
            if (arg3 < 5) {
                rec[2] = rec[2] + 1;
            }
        }
        if (seven >= 0xB) {
            if (arg3 < 0xA) {
                rec[3] = rec[3] + 1;
            }
        }
    }
    if (arg4 < *(u32 *)(rec + 4)) {
        *(u32 *)(rec + 4) = arg4;
    }
    i = 0;
    row = (slot & 0xFF) * 0xE8;
    tbl = D_800BBA24w17;
    p = driver * 0x11;
outer:
    do {
        j = 0;
        rec = (u8 *)D_800A35F4;
        rec += row;
        m = i;
        rec += m * 0xC + 0x1C;
        sum = p * 4 + (u32)tbl;
        src = (u8 *)(m * 4 + sum);
        do {
            *(rec + j + 8) = src[j];
            j++;
        } while (j < 4);
        i++;
    } while (0);
    if (i < 17) {
        goto outer;
    }
    slotM = slot & 0xFF;
    D_800A35F4[slotM * 0xE8 + 0x19] =
        D_800A3068w17[driver * 2] | (D_800A3069w17[driver * 2] << 1);
    D_800A35F4[slotM * 0xE8 + 0x1A] = D_800A3A24w17[driver];
    D_800A35F4[slotM * 0xE8 + 0x1B] = D_800A307Cw17[driver];
}

extern u8 D_800BBA24[];
void func_8006B3E0(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    u8 *tbl;
    u8 *src;
    u8 *walk;
    u8 *dst;
    u8 *q;
    s32 off;
    s32 mask2;
    i = 0;
    mask2 = arg2 & 0xFF;
    arg0 &= 0xFF;
    tbl = D_800BBA24;
    src = tbl + arg0 * 0x44;
    arg1 &= 0xFF;
    walk = (u8 *)D_800A35F4 + arg1 * 0xE8;
    off = mask2 * 0xC;
    off += 0x1C;
    dst = walk + off;
    do {
        q = dst + i;
        q[8] = *(src + mask2 * 4 + i);
        i += 1;
    } while (i < 4);
}

extern u8 *volatile D_800A3604Vol asm("D_800A3604.NON_MATCHING");
extern u8 D_800A3073[];
extern u8 D_800A306D[];
extern u8 D_800A3078[];
extern u8 D_800A2F94R[] asm("D_800A2F94.NON_MATCHING");
extern u8 D_800A2F95R[] asm("D_800A2F95.NON_MATCHING");

void func_8006B464(void) {
    u8 *rec;
    s32 b0;
    s32 a1;
    u32 bB;
    s32 b2;
    u8 *rec2;
    s32 i;

    rec = D_800A3604Vol;
    b0 = rec[0];
    a1 = b0 & 3;
    do {
    } while (0);
    D_800A3073[-4] = ((u8)b0 >> 2) & 1;
    D_800A3073[-5] = a1;
    D_800A3073[-7] = ((u8)b0 >> 6) & 1;
    D_800A3073[-3] = (u8)b0 >> 7;
    bB = rec[0xB];
    D_800A3073[-2] = bB & 1;
    if ((bB & 1) != 0) {
        if (a1 != 1) {
            D_800A3073[-2] = 0;
        }
    }
    D_800A3073[-1] = (bB >> 1) & 1;
    rec2 = D_800A3604Vol;
    D_800A3694w15[0] = rec2[1];
    b2 = rec2[2];
    D_800A3696w15[0] = b2;
    D_800A2F94R[0] = b2 * 127 / 100;
    if (D_800A306D[-1] != 0) {
        D_800A2F95R[0] = 0;
    } else {
        D_800A2F95R[0] = 1;
    }
    D_800A3078[0] = D_800A3604Vol[3];
    i = 0;
    do {
        D_800A331CAbsolute[i] = (D_800A3604Vol + i)[4];
        i += 1;
    } while (i < 6);
    D_800A37D0[0] = D_800A3604Vol[0xA];
}

/*
 * Retail re-reads the D_800A3604 pointer (gp) before every
 * store, so the pointer variable is volatile here. The D_800A306C-3072/75
 * bytes are untracked; reached as D_800A3073[-N]/[+2] (already declared
 * in this TU).
 */
extern u8 *volatile D_800A3604Vol asm("D_800A3604.NON_MATCHING");
extern u8 D_800A3073[];
extern u8 D_800A3078[];
extern u16 D_800A3694Absolute[];
extern s32 D_800A37D0[];

void func_8006B5BC(void) {
    s32 i;

    D_800A3604Vol[0] = D_800A3073[-3] << 7 | D_800A3073[-7] << 6 |
                       D_800A3073[-6] << 5 | D_800A3073[-4] << 2 |
                       D_800A3073[-5];
    D_800A3604Vol[0xB] =
        D_800A3073[2] << 2 | D_800A3073[-1] << 1 | D_800A3073[-2] & 1;
    D_800A3604Vol[1] = D_800A3694Absolute[0];
    D_800A3604Vol[2] = D_800A3694Absolute[1];
    D_800A3604Vol[3] = D_800A3078[0];
    for (i = 0; i < 6; i++) {
        (D_800A3604Vol + i)[4] = D_800A331CAbsolute[i];
    }
    D_800A3604Vol[0xA] = D_800A37D0[0];
}

INCLUDE_ASM("asm/nonmatchings/memory_card_menu", func_8006B6B8);

extern u8 D_800B9B6E[];
extern u8 D_800B9B6F[];
extern u8 D_800B9B70[];
extern u8 D_800B9B71[];
extern u8 D_800B9B72[];
extern u8 D_800B9BB4[];

void func_8006BA68(void) {
    u8 *base;
    u8 *entry;
    u8 *byte;
    s32 i;
    s32 k;
    s32 ffff;
    s32 fill;
    s32 magic;

    func_8006BD68();
    i = 0x17;
    base = D_800B9B6E;
    entry = base + 0x44;
    base[0] = 0;
    D_800B9B6F[0] = 0;
    D_800B9B70[0] = 0;
    D_800B9B71[0] = 0;
    D_800B9B72[0] = 0;
    do {
        *(s16 *)entry = 0;
        i -= 1;
        entry -= 2;
    } while (i >= 0);
    i = 0;
    ffff = 0xFF;
    magic = 0x7FFFFFFF;
    fill = 0x20;
    do {
        entry = D_800B9BB4 + i * 0xC;
        k = 3;
        byte = entry + 3;
        *(s16 *)(entry + 4) = ffff;
        *(s16 *)(entry + 6) = ffff;
        *(s32 *)(entry + 8) = magic;
        do {
            *byte = fill;
            k -= 1;
            byte -= 1;
        } while (k >= 0);
        i += 1;
    } while (i < 0x11);
}

#ifdef NON_MATCHING
/* Loads the settings record at D_800B9B73 into the menu globals (the
 * inverse of func_8006BD68 below) and spreads the 17 four-character rows
 * into D_800BBA24, keeping the selected row in D_800A3860. */
/* Loads the settings record at D_800B9B73 into the menu globals (the
 * inverse of func_8006BD68 below) and spreads the 17 four-character rows
 * into D_800BBA24, keeping the selected row in D_800A3860. */
void func_8006BB1C(void) {
    u8 *rec;
    u8 *row;
    u8 *table;
    u8 *src;
    u8 *dst;
    register u8 flags asm("v1");
    register u32 v73 asm("a0");
    u32 v74;
    u32 v82;
    s32 level;
    register s32 vol asm("a1");
    u8 value;
    s32 gear;
    s32 entry;
    s32 k;
    s32 i;
    extern u8 D_800B9B73[];
    extern u8 D_800B9B74[];
    extern u8 D_800B9B75[];
    extern u8 D_800B9B76[];
    extern u8 D_800B9B77[];
    extern u8 D_800B9B78[];
    extern u8 D_800B9B79[];
    extern u8 D_800B9B7F[];
    extern u8 D_800B9B80[];
    extern u8 D_800B9B81[];
    extern u8 D_800B9B82[];
    extern u8 D_800BBA24[];
    extern u8 D_800A306C[];
    extern u8 D_800A306E[];
    extern u8 D_800A306F[];
    extern u8 D_800A3070[];
    extern u8 D_800A3071[];
    extern u8 D_800A3071NM[] asm("D_800A3071.NON_MATCHING");
    extern u8 D_800A3072[];
    extern u8 D_800A308C[];
    extern u8 D_800A307C[];
    extern s32 D_800A37D0[];
    extern u8 D_800A2F94R[] asm("D_800A2F94.NON_MATCHING");
    extern u8 D_800A2F95R[] asm("D_800A2F95.NON_MATCHING");
    extern u8 D_800A305BSel[] asm("D_800A305B.NON_MATCHING");

    v73 = D_800B9B73[0];
    flags = D_800B9B75[0];
    v74 = D_800B9B74[0];
    v82 = D_800B9B82[0];
    D_800A36E0[0] = v73;
    level = flags & 3;
    D_800A305B[0] = v74;
    D_800A306F[0] = (flags >> 2) & 1;
    D_800A3069[0] = (flags >> 3) & 1;
    D_800A3068[0] = (flags >> 4) & 1;
    D_800A306C[0] = (flags >> 6) & 1;
    D_800A306E[0] = level;
    D_800A3070[0] = flags >> 7;
    D_800A3071[0] = v82 & 1;
    if ((v82 & 1) != 0 && level != 1) {
        D_800A3071NM[0] = 0;
    }

    vol = D_800B9B77[0];
    D_800A3694w15[0] = D_800B9B76[0];
    gear = D_800A306C[0];
    D_800A3072[0] = (v82 >> 1) & 1;
    D_800A3696w15[0] = vol;
    D_800A2F94R[0] = (vol * 0x7F) / 100;
    if (gear != 0) {
        D_800A2F95R[0] = 0;
    } else {
        D_800A2F95R[0] = 1;
    }

    D_800A3078[0] = D_800B9B78[0];
    for (i = 0; i < 6; i++) {
        D_800A331C[i] = D_800B9B79[i];
    }

    if (D_800B9B7F[0] == D_800A3A24w18c[0]) {
        D_800A308C[0] = D_800A3A24w18c[0];
        D_800A307C[0] = D_800B9B80[0];
    } else {
        D_800A307C[0] = 0;
    }

    rec = D_800B9B81;
    value = rec[0];
    entry = 0;
    table = D_800BBA24;
    row = rec + 0x33;
    D_800A37D0[0] = value;
    for (; entry < 0x11; entry++) {
        k = 0;
        src = row;
        dst = table;
        do {
            *dst = *src;
            if (entry == D_800A305BSel[0]) {
                D_800A3860S8[k] = *src;
            }
            src += 1;
            dst += 1;
            k += 1;
        } while (k < 4);
        table += 4;
        row += 0xC;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/memory_card_menu", func_8006BB1C);
#endif

extern char *strcpy(char *, const char *);

void func_8006BD68(void) {
    u8 *dest;
    u8 *rec;
    s32 i;
    s32 srcRow;
    s32 dstRow;
    s32 dst;
    s32 src;
    s32 end;
    extern char *D_8009A31CStr[] asm("D_8009A31C.NON_MATCHING");
    extern char *D_8009AC1C[];
    extern u8 D_800A305B[];
    extern u8 D_800A305BR[] asm("D_800A305B.NON_MATCHING");
    extern u8 D_800A36E0[];
    extern u8 D_800A36E1[];
    extern u8 D_800A3068[];
    extern u8 D_800A3069[];
    extern u8 D_800A306CR[] asm("D_800A306C.NON_MATCHING");
    extern u8 D_800A306D[];
    extern u8 D_800A306ER[] asm("D_800A306E.NON_MATCHING");
    extern u8 D_800A306FR[] asm("D_800A306F.NON_MATCHING");
    extern u8 D_800A3070R[] asm("D_800A3070.NON_MATCHING");
    extern u8 D_800A3071R[] asm("D_800A3071.NON_MATCHING");
    extern u8 D_800A3072R[] asm("D_800A3072.NON_MATCHING");
    extern u8 D_800A3075[];
    extern u8 D_800A3078[];
    extern u8 D_800A307C[];
    extern u16 D_800A3694R[] asm("D_800A3694.NON_MATCHING");
    extern u16 D_800A3696[];
    extern s32 D_800A37D0[];
    extern u8 D_800A331C[];
    extern u8 D_800B9B44[];
    extern u8 D_800B9B73[];
    extern u8 D_800B9B74[];
    extern u8 D_800B9B75[];
    extern u8 D_800B9B76[];
    extern u8 D_800B9B77[];
    extern u8 D_800B9B78[];
    extern u8 D_800B9B79[];
    extern u8 D_800B9B7F[];
    extern u8 D_800B9B80[];
    extern u8 D_800B9B81[];
    extern u8 D_800B9B82[];
    extern u8 D_800BBA24[];

    dest = D_800B9B44;
    strcpy((char *)dest, D_8009A31CStr[D_800A305B[0]]);
    strcpy((char *)dest + 0x10, D_8009AC1C[D_800A36E0[0]]);
    D_800B9B73[0] = D_800A36E1[-1];
    D_800B9B74[0] = D_800A305BR[0];
    D_800B9B75[0] =
        D_800A306ER[0] |
        (D_800A3070R[0] << 7 | D_800A306CR[0] << 6 | D_800A306D[0] << 5 |
         D_800A3068[0] << 4 | D_800A3069[0] << 3 | D_800A306FR[0] << 2);
    D_800B9B82[0] =
        D_800A3075[0] << 2 | D_800A3072R[0] << 1 | D_800A3071R[0] & 1;
    D_800B9B76[0] = D_800A3694R[0];
    D_800B9B77[0] = D_800A3696[0];
    D_800B9B78[0] = D_800A3078[0];
    i = 0;
    do {
        D_800B9B79[i] = D_800A331C[i];
        i += 1;
    } while (i < 6);
    i = 0;
    rec = D_800B9B7F;
    rec[0] = D_800A3A24w17[0];
    D_800B9B80[0] = D_800A307C[0];
    D_800B9B81[0] = D_800A37D0[0];
    srcRow = (s32)D_800BBA24;
    dstRow = (s32)rec + 0x35;
    do {
        dst = dstRow;
        src = srcRow;
        end = dstRow + 4;
        do {
            *(u8 *)dst = *(u8 *)src;
            dst += 1;
            src += 1;
        } while (dst < end);
        srcRow += 4;
        dstRow += 0xC;
        i += 1;
    } while (i < 0x11);
}

INCLUDE_ASM("asm/nonmatchings/memory_card_menu", func_8006BF74);

extern char *D_8009A31CStr[] asm("D_8009A31C.NON_MATCHING");
extern s32 D_8009A4D8[];
extern u8 D_800A3770;
extern u8 *D_800A3908[];
extern u8 *D_800A377C[];
extern char D_800B0A2C[];
extern u8 D_800A358C;
extern u8 D_800A3968;
extern char *strcpy(char *, const char *);
void func_8006C668(s32 start, s32 arg1);

/* Card-menu mode switch (D_800A39E4 == 0x28) or cursor step: arg0 nonzero
 * steps the cursor, scrolling the row window when it reaches the edge. */
void func_8006C2D0(s32 arg0) {
    s32 i;
    register u8 *node asm("a0");
    u8 *entry;
    u8 *s;
    u8 *sentinel;
    u8 *head;
    u8 *cursor;
    s32 row;
    s32 row16;
    s32 gear;
    s32 mode;

    if (D_800A39E4[0] == 0x28) {
        node = D_800A3908[0];
        for (i = 0; i < 2; i++) {
            entry = *(u8 **)(node + 0x20);
            *(u32 *)(entry + 8) = D_8009A4D8[i];
            if (*(s16 *)(node + 0x1A) < 0) {
                *(s16 *)(node + 0x1A) = -*(s16 *)(node + 0x1A);
            }
            node = *(u8 **)(node + 0x1C);
        }
        s = D_800A377C[0];
        if (node != s) {
            sentinel = s;
            do {
                if (*(s16 *)(node + 0x1A) > 0) {
                    *(s16 *)(node + 0x1A) = -*(s16 *)(node + 0x1A);
                }
                node = *(u8 **)(node + 0x1C);
            } while (node != sentinel);
            s = D_800A377C[0];
        }
        *(u8 *)(s + 5) = 0;
        D_800A358C = 0;
    } else {
        if ((arg0 & 0xFF) != 0) {
            if (D_800A3968 < 0xF) {
                strcpy(D_800A3968 * 0x10 + D_800B0A2C,
                       D_8009A31CStr[D_800A305B[0]]);
                for (i = D_800A3968 + 1; i < 0xF; i++) {
                    row16 = i * 0x10;
                    *(u8 *)(row16 + D_800B0A2C) = 0;
                }
            }
            row = D_800A3968;
        } else {
            row = D_800A3968 - 1;
        }
        D_800A358C = row;
    }

    if (D_800A358C >= 0xF) {
        D_800A358C = 0xE;
    }
    if ((arg0 & 0xFF) != 0 && D_800A39E4[0] != 0x28) {
        if (D_800A358C >= 7) {
            *(u8 *)(D_800A377C[0] + 5) = 6;
        } else {
            *(u8 *)(D_800A377C[0] + 5) = D_800A358C;
        }
        if (D_800A358C < 6) {
            func_8006C668(0, D_800A358C);
        } else {
            func_8006C668((s8)(D_800A358C - 6), D_800A358C);
        }
    } else {
        *(u8 *)(D_800A377C[0] + 5) = 0;
        D_800A358C = 0;
        if (D_800A39E4[0] != 0x28) {
            func_8006C668(0, D_800A3968 - 1);
        }
    }

    cursor = D_800A377C[0];
    gear = *(s8 *)(cursor + 5);
    mode = D_800A39E4[0];
    *(s16 *)(cursor + 8) = gear * 9 + 0x54;
    if (mode != 0x28) {
        head = D_800A3908[0];
        if (head != cursor) {
            do {
                if (*(s16 *)(head + 0x1A) < 0) {
                    *(s16 *)(head + 0x1A) = -*(s16 *)(head + 0x1A);
                }
                head = *(u8 **)(head + 0x1C);
            } while (head != cursor);
        }
    }
    D_800A3770 = 0;
}

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

#ifdef NON_MATCHING
/*
 * w7h: size-exact (0x84) draft; prologue matches incl. the early
 * lui/lw of D_800A3A10 BEFORE addiu sp (put the obj read first).
 * Remaining: store/load order only -- retail reloads *entry after the
 * sll/sra return extension and keeps the second D_800A3A10 lui/lw
 * before the srl/addu/sra divide; ours sinks the reload after it.
 * NOTE: plain asm(""); at this spot makes maspsx emit two hazard nops
 * (+8 bytes) -- do not use it as an order barrier here.
 */
extern s32 D_8009A4C0[];
void func_8006C5E4(s32 arg0) {
    s32 *entry;
    u8 *obj;
    register s32 value asm("v1");

    obj = *(u8 **)((u8 *)D_800A3A10[0] + 0x20);
    entry = &D_8009A4C0[arg0 & 0xFF];
    value = func_8005A8E0(*entry);
    value = (0x78 - value) / 2;
    *(s32 *)(obj + 8) = *entry;
    *(u16 *)((u8 *)D_800A3A10[0] + 0x12) = value;
}
#else
extern s32 D_8009A4C0[];
void func_8006C5E4(s32 arg0) {
    s32 *entry;
    u8 *obj;
    s32 value;
    s32 temp;
    s32 *tbl;
    s32 offset;
    s32 elem;
    ColorNode *node;

    obj = *(u8 **)((u8 *)D_800A3A10[0] + 0x20);
    offset = arg0 & 0xFF;
    tbl = D_8009A4C0;
    entry = tbl + offset;
    value = func_8005A8E0(*entry);
    elem = *entry;
    temp = 0x78 - value;
    node = D_800A3A10[0];
    value = temp / 2;
    *(s32 *)(obj + 8) = elem;
    node->unk12 = value;
}

#endif

extern u8 *D_800A3908[];
extern u8 *D_800A377C[];
extern char D_800B0A2C[];
extern u8 D_800A358C;
extern u8 D_800A3968;

/* func_8006C700 expands this body twice, while func_8006C2D0 calls the
 * out-of-line copy, so both share one macro. */
#define CARD_MENU_SET_ROWS(startArg, limitArg)                                 \
    {                                                                          \
        s8 first = (startArg);                                                 \
        s32 index;                                                             \
        s32 limit;                                                             \
        u8 *node;                                                              \
        u8 *entry;                                                             \
        u8 *s;                                                                 \
        u8 *sentinel;                                                          \
                                                                               \
        if ((limitArg) < 6) {                                                  \
            limit = (limitArg);                                                \
        } else {                                                               \
            limit = first + 6;                                                 \
        }                                                                      \
        node = D_800A3908[0];                                                  \
        index = first;                                                         \
        if (limit >= index) {                                                  \
            do {                                                               \
                entry = *(u8 **)(node + 0x20);                                 \
                *(u32 *)(entry + 8) = (u32)(D_800B0A2C + index * 0x10);        \
                index++;                                                       \
                node = *(u8 **)(node + 0x1C);                                  \
            } while (limit >= index);                                          \
        }                                                                      \
        s = D_800A377C[0];                                                     \
        if (node != s) {                                                       \
            sentinel = s;                                                      \
            do {                                                               \
                entry = *(u8 **)(node + 0x20);                                 \
                *(u32 *)(entry + 8) = 0;                                       \
                node = *(u8 **)(node + 0x1C);                                  \
            } while (node != sentinel);                                        \
        }                                                                      \
    }

void func_8006C668(s32 start, s32 arg1) CARD_MENU_SET_ROWS(start, arg1)

    s32 func_8006C700(s32 arg0, s32 arg1) {
    s32 result;
    s32 target;
    s32 gear;
    u8 *node;
    s32 old;
    s32 start;
    s32 tmp;

    if ((arg1 & 0xFF) != 0) {
        target = D_800A3968;
        if (target == 0xF) {
            target = 0xE;
        }
    } else if (D_800A39E4[0] == 0x28) {
        target = 1;
    } else {
        target = D_800A3968 - 1;
    }

    node = D_800A377C[0];
    gear = *(s8 *)(node + 5);
    result = 1;
    if ((arg0 & 0xFF) != 0) {
        if (gear >= 6)
            goto scrollForward;
        if (gear >= target)
            goto scrollForward;
        {
            old = D_800A358C;
            tmp = *(u16 *)(node + 8);
            old = old + 1;
            tmp = tmp + 9;
            *(u16 *)(node + 8) = tmp;
            D_800A358C = old;
            gear = gear + 1;
            goto finish;
        }
    scrollForward:
        if (gear == 6 && D_800A358C < target) {
            old = D_800A358C;
            D_800A358C = old + 1;
            start = old - 5;
            CARD_MENU_SET_ROWS(start, target)
        } else {
            result = 0;
        }
    } else if (gear > 0) {
        s32 oldBack;
        s32 tmpBack;

        oldBack = D_800A358C;
        tmpBack = *(u16 *)(node + 8);
        gear = gear - 1;
        oldBack = oldBack - 1;
        tmpBack = tmpBack - 9;
        D_800A358C = oldBack;
        *(u16 *)(node + 8) = tmpBack;
    } else {
        s32 oldTop;
        u8 newTop;

        oldTop = D_800A358C;
        if (oldTop != 0) {
            newTop = oldTop - 1;
            D_800A358C = newTop;
            CARD_MENU_SET_ROWS(oldTop - 1, target)
        } else {
            result = 0;
        }
    }
finish:
    *(s8 *)(D_800A377C[0] + 5) = gear;
    return result;
}

extern s32 func_8005AEC8(u32, void *);
/* Expand the cursor helper here and in its caller with the same byte types. */
#define CARD_MENU_CURSOR_BODY(finish, font, size, index, text, cursor, result) \
    {                                                                          \
        func_8005A7B8(font, size);                                             \
        if (*text == 0) {                                                      \
            *cursor = func_8005AFF0(0x20);                                     \
            finish(0);                                                         \
        } else {                                                               \
            result = func_8005AEC8(index, text);                               \
            *cursor = func_8005AFF0(text[index]);                              \
            finish(result);                                                    \
        }                                                                      \
    }
s32 func_8006C94C(u8 arg0, u8 arg1, u8 arg2, s8 *arg3, s16 *arg4) {
    s32 ret;
    CARD_MENU_CURSOR_BODY(return, arg0, arg1, arg2, arg3, arg4, ret);
}

extern u8 *D_800A377C[];
void func_8006C9DC(void) {
    *(s16 *)(*(u8 **)(D_800A377C[0] + 0x1C) + 0x1A) = -1;
}

extern u8 D_800A358C;
extern char D_800B0A2C[];
extern s32 func_8005AEC8(u32, void *);
extern s16 func_8005AFF0(s8);

/* Keep the raw decrement and the byte index in separate values. */
void func_8006C9F8(void) {
    u8 *obj;
    u8 *ptr;
    s8 *entry;
    s32 status;
    s32 val;
    s32 length;
    u8 index;

    obj = *(u8 **)(D_800A377C[0] + 0x1C);
    entry = (s8 *)D_800B0A2C + D_800A358C * 0x10;
    *(s16 *)(obj + 0x1A) = 1;
    length = strlen((char *)entry);
    *(u8 *)(obj + 5) = length;
    if ((s8)length >= 0xF) {
        *(u8 *)(obj + 5) = 0xE;
    }
    val = *(u8 *)(obj + 5) - 1;
    *(u8 *)(obj + 5) = val;
    index = val;
    entry = (s8 *)D_800B0A2C + D_800A358C * 0x10;
    {
        s8 *text = entry;
        s16 *cursor = (s16 *)(obj + 0x16);
        s32 result;
        CARD_MENU_CURSOR_BODY(status =, 2, 2, index, text, cursor, result);
    }
    ptr = *(u8 **)D_800A377C;
    *(s16 *)(obj + 6) = status + 0xA;
    *(s16 *)(obj + 8) = *(u16 *)(ptr + 8) + 9;
}
#undef CARD_MENU_CURSOR_BODY

void func_8006CB00(void) {
    s32 value;
    value = *(s16 *)(D_800A377C[0] + 0x1A);
    if (value > 0)
        value = -value;
    else if (value == 0)
        value = -255;
    *(s16 *)(D_800A377C[0] + 0x1A) = value;
}

extern u8 *D_800A377C[];
void func_8006CB40(void) {
    s32 value;
    s8 zero;
    value = *((s16 *)(D_800A377C[0] + 0x1A));
    if (value < 0) {
        value = -value;
    } else if (value == (-255)) {
        zero = 0;
        value = zero;
    }
    *((s16 *)(D_800A377C[0] + 0x1A)) = value;
}

#ifdef NON_MATCHING
void func_8006CB80(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 D_800A3830Absolute[];
    extern s32 D_800A3830Absolute2[];
    s8 *new_var2;
    extern s32 D_800A37F0Absolute[];
    extern s32 D_800A37F0Absolute2[];
    extern s32 D_800A37F0Absolute3[];
    extern s32 D_800A37F0D[] asm("D_800A37F0.NON_MATCHING");
    s32 threshold;
    char *new_var;
    s32 limitSave;
    s32 ch;
    s32 adj;
    s8 *entry;
    char *blank;
    u8 cursor;
    s32 result;
    threshold = 0xF;
    if (arg1 & (~arg2)) {
        D_800A3830Absolute2[0] = 0;
        limitSave = 1;
    } else {
        D_800A3830Absolute[0] = D_800A3830Absolute2[0] + 1;
        if (threshold < D_800A3830Absolute[0]) {
            D_800A37F0Absolute[0] =
                D_800A37F0Absolute2[0] + (D_800A37F0Absolute2[0] / 2);
            if (0x9 <= D_800A37F0Absolute[0]) {
                limitSave = 8;
            } else {
                goto noStore;
            }
        } else {
            return;
        }
    }
    D_800A37F0Absolute3[0] = limitSave;
noStore:
    entry = *((s8 **)(D_800A377C[0] + 0x1C));

    if ((*((s8 *)(entry + 5))) <
        strlen((char *)((D_800A358C * 0x10) + D_800B0A2C))) {
        goto readChar;
    }
    blank =
        ((char *)((D_800A358C * 0x10) + D_800B0A2C)) + (*((s8 *)(entry + 5)));
    blank[0] = ' ';
    blank =
        ((char *)(((*((volatile u8 *)(&D_800A358C))) * 0x10) + D_800B0A2C)) +
        (*((s8 *)(entry + 5)));
    blank[1] = 0;
    ch = 0x21;
    goto charJoined;
readChar:
    ch = (*((u8 *)((((*((volatile u8 *)(&D_800A358C))) * 0x10) + D_800B0A2C) +
                   (*((s8 *)(entry + 5)))))) -
         0x20;

charJoined:
    if ((arg0 & 0xFF) == 0) {
        adj = ch - D_800A37F0D[0];
        if (((s16)adj) >= 0) {
            ch = adj;
        } else {
            ch = adj + 0x5F;
        }
        if (((u16)(ch - 1)) < 0xF) {
            ch = 0;
        } else if (((u16)(ch - 0x1A)) < 7) {
            ch = 0x19;
        } else if (((u16)(ch - 0x3B)) < 6) {
            ch = 0x3A;
        } else if (((s16)ch) < 0x5B) {
        } else {
            ch = 0x5A;
        }
    } else {
        adj = ch + D_800A37F0D[0];
        if (((s16)adj) < 0x5F) {
            ch = adj;
        } else {
            ch = adj - 0x5F;
        }
        if (((u16)(ch - 1)) < 0xF) {
            ch = 0x10;
        } else if (((u16)(ch - 0x1A)) < 7) {
            ch = 0x21;
        } else if (((u16)(ch - 0x3B)) < 6) {
            ch = 0x41;
        } else if (((s16)ch) < 0x5B) {
        } else {
            ch = 0;
        }
    }

    *((char *)((new_var = (D_800A358C * 0x10) + D_800B0A2C) + (*(entry + 5)))) =
        ch + 0x20;
    new_var2 = (s8 *)((D_800A358C * 0x10) + D_800B0A2C);
    func_8005A7B8(2, 2);
    cursor = *((u8 *)(entry + 5));
    if ((*new_var2) == 0) {
        *((s16 *)(entry + 0x16)) = func_8005AFF0(0x20);
        result = 0;
    } else {
        func_8005AEC8(cursor, new_var);
        result = (*((s16 *)(entry + 0x16)) =
                      func_8005AFF0(*((s8 *)(new_var + cursor))));
    }
    *((s16 *)(entry + 6)) = result + 0xA;
}

#else
INCLUDE_ASM("asm/nonmatchings/memory_card_menu", func_8006CB80);
#endif

extern char D_800B0A2D[];
extern u8 D_800A358C;
extern char D_800B0A2C[];
extern s32 func_8005AEC8(u32, void *);
void func_8006CE64(void) {
    u8 *obj;
    u8 index;
    s32 offset;
    s8 *entry;
    s32 status;
    offset = 0x10 * D_800A358C;
    D_800B0A2C[offset] = 0x41;
    D_800B0A2D[D_800A358C * 0x10] = 0;
    obj = *((u8 **)(D_800A377C[0] + 0x1C));
    *((u8 *)(obj + 5)) = 0;
    entry = ((s8 *)D_800B0A2C) + ((index = D_800A358C) * 0x10);
    func_8005A7B8S32(2, 2);
    if ((*entry) == 0) {
        *((s16 *)(obj + 0x16)) = func_8005AFF0(0x20);
        status = 0;
    } else {
        status = func_8005AEC8(0, entry);
        *((s16 *)(obj + 0x16)) = func_8005AFF0(*entry);
    }
    *((s16 *)(obj + 6)) = status + 0xA;
}

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

void func_8006CF90(u32 mode) {
    extern u8 D_800A3390[];
    extern s32 func_8005AEC8(u32, void *);
    extern s16 func_8005AFF0(s8);
    u8 *node;
    u8 *st;
    char *entry;
    s8 c;
    s8 t;
    s8 ch;
    u8 idx;
    s32 result;

    node = D_800A377C[0];
    st = *(u8 **)(node + 0x1C);
    mode &= 0xFF;
    if (mode != 0) {
        if (*(s8 *)(st + 5) > 0) {
            *(s8 *)(st + 5) = *(s8 *)(st + 5) - 1;
        }
    } else {
        t = *(s8 *)(st + 5);
        c = t;
        if (t < 14) {
            c = c + 1;
            *(s8 *)(st + 5) = c;
            if (c == strlen(&D_800B0A2C[D_800A358C * 16])) {
                strcat(&D_800B0A2C[D_800A358C * 16], D_800A3390);
            }
        }
    }
    idx = *(u8 *)(st + 5);
    entry = D_800B0A2C + D_800A358C * 16;
    func_8005A7B8S32(2, 2);
    ch = *entry;
    if (ch == 0) {
        *(u16 *)(st + 0x16) = func_8005AFF0(0x20);
        result = 0;
    } else {
        result = func_8005AEC8(idx, entry);
        *(u16 *)(st + 0x16) = func_8005AFF0(*(s8 *)(entry + idx));
    }
    *(u16 *)(st + 6) = result + 10;
}

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

extern u8 D_800A358C;

/* The same 16-byte name slots as D_800B0A2C, typed with a 16-byte stride so
 * that gcc hoists the slot address out of the loop. */
typedef struct {
    s8 s[16];
} Nm;
extern Nm D_800B0A2CNm[] asm("D_800B0A2C");

/* Trims trailing spaces off the current name slot. Returns 0 when the slot
 * holds nothing but spaces. */
s32 func_8006D178(void) {
    u8 i;
    u8 found;

    found = 0;
    i = strlen((char *)D_800B0A2CNm[D_800A358C].s);
    while ((s8)i >= 0 && (found & 0xFF) == 0) {
        switch (D_800B0A2CNm[D_800A358C].s[(s8)i]) {
        default:
            found = 1;
            break;
        case 0:
        case ' ':
            i--;
            break;
        }
    }
    if (found) {
        (D_800B0A2CNm + D_800A358C)->s[(s8)i + 1] = 0;
        return 1;
    }
    return 0;
}

extern u8 D_800B9B73[];
extern u8 D_800B9B74[];
extern u8 D_800A3980[];
extern void func_8006BB1C(void);
extern void func_8006EEBC(void);

s32 func_8006D258(void) {
    typedef struct {
        s32 words[0x13C / 4];
    } SaveRec;
    extern u8 D_800A305BR2[] asm("D_800A305B.NON_MATCHING");
    extern u8 D_800A305BR3[] asm("D_800A305B.NON_MATCHING");
    s32 status;
    s32 match;
    s32 i;
    SaveRec *rec;
    u8 idx;
    u8 *paint;

    func_800599E4();
    status = CardCheckStatus(D_800A337C, 1);
    func_800598C4();
    status &= 0xFF;
    if (status == 3) {
        D_800A3808 = 0xF;
        return 0;
    }
    if (status != 0) {
        D_800A3808 = 1;
        return 0;
    }
    rec = (SaveRec *)(D_800A3A0C + 4);
    *(SaveRec *)&D_800B9B44[0] = rec[D_800A358C];
    func_8006BB1C();
    idx = D_800B9B74[0];
    paint = D_800AE178[idx];
    D_800A305B[0] = idx;
    func_8005E4A4(paint);
    func_8005ED04(D_800A305BR2[0]);
    func_8005EC5C(D_800A305BR3[0]);
    D_800A36E0[0] = D_800B9B73[0];
    func_80063AE0(0, D_800A36E0[0]);
    func_800636EC(0, D_800A36E1[-1]);
    for (i = 0; i < 0x18; i++) {
        if (D_800A36E1w15[-1] == D_8009AD40[i]) {
            match = i;
            break;
        }
    }
    D_800A3980[0] = match;
    strcpy(D_800BB9B4, D_8009AC1C[D_800A36E0[0]]);
    func_8006EEBC();
    return 1;
}

#ifdef NON_MATCHING
/* w7i: draft to 0xa4 exact length, 7 rows off: entry order and
 * i/j register naming (target: i in a3 inited FIRST at entry, j in a2;
 * both row-pointer temps outer-loop). src[j + 0x24] keeps the +0x24 in
 * the lbu displacement. */
extern u8 D_800BBA24[];
extern char *D_800A35F4;
void func_8006D424(u8 arg0, u8 arg1) {
    char *src;
    u8 *dst;
    u8 i;
    u8 j;

    for (i = 0; i < 0x11; i++) {
        dst = &D_800BBA24[arg0 * 0x44 + i * 4];
        src = D_800A35F4 + arg1 * 0xE8 + i * 0xC;
        for (j = 0; j < 4; j++) {
            dst[j] = src[j + 0x24];
        }
    }
}
#else
extern u8 D_800BBA24[];
extern char *D_800A35F4;
void func_8006D424(u8 arg0, u8 arg1) {
    u8 i;
    u8 j;
    u8 *dst;
    u8 *src;
    s32 srcOff;
    s32 row;
    s32 base;
    s32 dstOff;

    i = 0;
    base = (s32)D_800BBA24;
    row = arg0 * 0x44;
outer:
    j = 0;
    dstOff = row + base;
    dst = (u8 *)(i * 4 + dstOff);
    srcOff = arg1 * 0xE8;
    do {
        src = (u8 *)(srcOff + (s32)D_800A35F4);
        src += i * 0xC;
        dst[j] = *(src + j + 0x24);
        j++;
    } while (j < 4);
    i++;
    if (i < 0x11) {
        goto outer;
    }
}

#endif

extern u8 D_800BBA24_nm[] asm("D_800BBA24.NON_MATCHING");
extern u8 D_800A3068_nm[] asm("D_800A3068.NON_MATCHING");
extern u8 D_800A3069_nm[] asm("D_800A3069.NON_MATCHING");
extern u8 D_800A307C_nm[] asm("D_800A307C.NON_MATCHING");
extern u8 D_800A308C_nm[] asm("D_800A308C.NON_MATCHING");
extern s8 D_800A3A24_nm[] asm("D_800A3A24.NON_MATCHING");
void func_8006D4C8(u8 arg0, u8 arg1) {
    u8 i;
    u8 j;
    u8 *dst;
    u8 *src;
    s32 bit;
    s32 srcOff;
    s32 row;
    s32 base;
    s32 dstOff;
    i = 0;
    base = (s32)D_800BBA24_nm;
    row = arg0 * 0x44;
outer:
    j = 0;

    dstOff = row + base;
    dst = (u8 *)((i * 4) + dstOff);
    srcOff = arg1 * 0xE8;
    do {
        src = (u8 *)(srcOff + ((s32)D_800A35F4));
        src += i * 0xC;
        dst[j] = *((src + j) + 0x24);
        j++;
    } while (j < 4);
    i++;
    if (i < 0x11) {
        goto outer;
    }
    bit = ((u8 *)D_800A35F4)[(arg1 * 0xE8) + 0x19] & 1;
    D_800A3068_nm[arg0 * 2] = bit;
    D_800A3069_nm[arg0 * 2] =
        (((u8 *)D_800A35F4)[(arg1 * 0xE8) + 0x19] >> 1) & 1;
    if (((u8 *)D_800A35F4)[(arg1 * 0xE8) + 0x1A] == D_800A3A24_nm[arg0]) {
        D_800A307C_nm[arg0] = ((u8 *)D_800A35F4)[(arg1 * 0xE8) + 0x1B];
        D_800A308C_nm[arg0] = ((u8 *)D_800A3A24_nm)[arg0];
    } else {
        D_800A307C_nm[arg0] = 0;
    }
}

extern u8 D_800BBA24[];
void func_8006D634(s32 arg) {
    u8 *base;
    u8 *tbl;
    u8 i;
    s32 offset;

    i = 0;
    offset = arg & 0xFF;
    tbl = D_800BBA24;
    base = tbl + offset * 4;
    do {
        base[i] = 0x20;
        D_800A3860[0][i] = 0x20;
        i += 1;
    } while (i < 4);
}

/* w7i: full shape known; closest draft: src row via
 * &D_800BBA24[arg0 * 4 + i * 0x44], D_800A3860 base materialized FIRST,
 * `move a1,zero` (j init) placed before the row math. */
void func_8006D684(u8 arg0) {
    u8 *srcBase;
    s8(*dstBase)[4];
    u8 i;
    u8 j;

    dstBase = D_800A3860;
    srcBase = D_800BBA24;
    i = 0;
    do {
        do {
            if (1) {
                ;
            }
            for (j = 0; j < 4; j++) {
                dstBase[i][j] = (&srcBase[i * 0x44] + arg0 * 4)[j];
            }
            i++;
        } while (i < 2);
    } while (0);
}

extern u8 D_800B9BB4[];

void func_8006D708(u8 arg0, u8 arg1, u8 arg2) {
    u8 *rowB;
    u8 *src;
    u8 *dst;
    u8 *tbl;
    u8 *q2;
    u8 *walk;
    u8 *p;
    char *name;
    u8 match;
    u8 i;
    s32 n;
    s32 j;
    s32 off;
    s32 q;
    s32 x;
    s32 x2;
    s32 q3;
    u8 *tbl2;
    u8 *rp;

    if (arg2 == 0) {
        if (arg0 == 1) {
            return;
        }
        rowB = D_800B9BB4 + arg1 * 0xC;
    }
    i = 0;
    x = arg0;
    tbl = D_800BBA24;
    q = (u32)tbl + x * 0x44;
    dst = (u8 *)(arg1 * 4 + q);
    q2 = (u8 *)D_800A3860;
    src = x * 4 + q2;
again:
    dst[i] = src[i];
    if (arg2 == 0) {
        rowB[i] = src[i];
    }
    i++;
    if (i < 4) {
        goto again;
    }
    if (arg2 != 0) {
        name = D_8009AC1C[D_800A36E0[arg0]];
        if (D_800A3A58 == 0) {
            match = 0xFF;
        } else {
            n = 0;
            while (n < D_800A3A58) {
                if (strcmp(name, D_800A35F4 + n * 0xE8) == 0) {
                    match = n;
                    goto found;
                }
                n++;
            }
            match = 0xFF;
        }
    found:
        if (match == 0xFF) {
            return;
        }
        j = 0;
        off = arg1;
        x2 = arg0;
        tbl2 = D_800BBA24;
        q3 = (u32)tbl2 + x2 * 0x44;
        src = (u8 *)(off * 4 + q3);
        walk = (u8 *)D_800A35F4 + match * 0xE8;
        p = walk + (off * 0xC + 0x1C);
        do {
            rp = p + j;
            rp[8] = *src;
            src++;
            j++;
        } while (j < 4);
    }
}

#if 1
/* permuter output-0-1 under test */
extern u8 *D_800A3908[];
extern u8 *D_800A377C[];
extern u8 *D_800A3908[];
extern u8 *D_800A377C[];
extern u8 *D_800A377C[];
extern u8 *D_800A377C[];
extern u8 D_800A3808;
extern u8 *D_800A3908[];
extern u8 D_800A3808;
extern u8 D_800A337C;
extern s32 D_8009AB80[];
extern s32 D_8009AB00[];
extern u8 *D_800A377C[];
extern u8 D_800A3770;
extern void *D_800A3A24[];
void func_8006D8E8(s32 arg0) {
    u8 *obj;
    u8 *field20;
    u8 *end;
    u8 menuId;
    s32 val;
    s32 val2;
    obj = D_800A3908[0];
    menuId = D_800A3808;
    field20 = *((u8 **)(obj + 0x20));
    if (menuId == 0x1C) {
        if (D_800A337C != 0) {
            menuId = 0x1D;
        } else {
            menuId = 0x1C;
        }
    } else if (menuId == 0x1E) {
        if (D_800A337C != 0) {
            menuId = 0x1F;
        } else {
            menuId = 0x1E;
        }
    } else if (menuId == 0xD) {
        if (D_800A337C != 0) {
            menuId = 0x1A;
        } else {
            menuId = 0x19;
        }
    }
    if (((s8 *)D_800A3A24)[0] == 2) {
        *((s32 *)(field20 + 8)) = D_8009AB80[menuId];
    } else {
        *((s32 *)(field20 + 8)) = D_8009AB00[menuId];
    }
    if ((arg0 & 0xFF) == 0) {
        obj = *((u8 **)(obj + 0x1C));
        if (obj != D_800A377C[0]) {
            end = D_800A377C[0];
            do {
                val = *((s16 *)(obj + 0x1A));
                if (val > 0) {
                    *((s16 *)(obj + 0x1A)) = -(*((s16 *)(obj + 0x1A)));
                }
                obj = *((u8 **)(obj + 0x1C));
            } while (obj != end);
        }
        val2 = *((s16 *)(D_800A377C[0] + 0x1A));
        if (val2 > 0) {
            val2 = -val2;
        } else if (val2 == 0) {
            val2 = -0xFF;
        }
        *((s16 *)(D_800A377C[0] + 0x1A)) = val2;
    }
    D_800A3770 = 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/memory_card_menu", func_8006D8E8);
#endif

extern u8 *D_8009AB00nm[] asm("D_8009AB00.NON_MATCHING");
extern u8 *D_8009AB80nm[] asm("D_8009AB80.NON_MATCHING");
extern void *D_800A3908nm[] asm("D_800A3908.NON_MATCHING");
u8 *func_8005B598(s32 left, s32 top, s32 right, s32 bottom, s32 depth,
                  u8 texture, u8 semiTrans);

void func_8006DA40(void) {
    u8 *node;
    u8 *prev;
    u8 *pkt;
    u8 *field10;
    u8 idx;
    s32 err;
    s32 height;
    s32 i;
    s32 y;
    y = 0x50;
    i = 0;
    do {
        node = func_8005B598(0x64, y, 0x78, 0x18, 9, 1, 0);
        if (i == 0) {
            D_800A3A10[0] = (ColorNode *)node;
        } else {
            *((u8 **)(prev + 0x1C)) = node;
        }
        field10 = node + 0x10;
        pkt = *((u8 **)(node + 0x20));
        *((s16 *)(node + 0xE)) = 2;
        *((s16 *)field10) = 0;
        *((s16 *)(node + 0x6)) = -0x78;
        switch (i) {
        case 0:
            height = 0;
            break;

        case 1:
            height = 0xC;
            break;

        case 2:
            height = 0x18;
            break;
        }

        func_8005B17C(pkt, 9, 0, height, *((u16 *)(node + 0x16)),
                      *((u16 *)(node + 0x18)));
        y += *((s16 *)(node + 0x18));
        prev = node;
        i += 1;
    } while (i < 3);
    y = 0x50;
    i = 0;
    do {
        node =
            (u8 *)func_8005B314(0x64, y, 0x78, 0x48, 0, 0x20, 0x20, 0x40, 1, 1);
        *((s16 *)(node + 0x6)) = -0x78;
        *((s16 *)(node + 0xE)) = 2;
        *((s16 *)(node + 0x1A)) = 0xA;
        *((u8 **)(prev + 0x1C)) = node;
        prev = node;
        i += 1;
    } while (i < 2);
    node = (u8 *)func_8005BF8C(0x71, 0x55);
    err = D_800A3808;
    *((s16 *)(node + 0x1A)) = 2;
    if (err == 2) {
        idx = 0x1B;
    } else if (err == 0x1C) {
        idx = 0x1C;
        if (D_800A337C == 1) {
            idx = 0x1D;
        }
    } else if (err == 0xD) {
        idx = 0x19;
        if (D_800A337C == 1) {
            idx = 0x1A;
        }
    }
    if (D_800A3A24_nm[0] == 2) {
        func_80067EA4((UnkObject24 *)node, 2, 2, (s32)D_8009AB80nm[idx], 0,
                      *((s16 *)(node + 0x1A)));
    } else {
        func_80067EA4((UnkObject24 *)node, 2, 2, (s32)D_8009AB00nm[idx], 0,
                      *((s16 *)(node + 0x1A)));
    }
    *((s16 *)(node + 0xE)) = 2;
    *((s16 *)(node + 0x12)) = 0xB;
    *((s16 *)(node + 0x6)) = -0x6B;
    D_800A3908nm[0] = node;
    *((u8 **)(prev + 0x1C)) = node;
}

extern ColorNode *D_800A3A10[];
extern void func_8005B8B8(u8 *first, s32 value);
void func_8006DCF0(void) {
    func_8005B688(D_800A3A10[0], 1);
    func_8005B8B8(((void **)D_800A3A3C)[-11], 0xFF);
}

extern u8 D_800AEE3C[];
extern void func_8006E628(u32 arg0, u32 arg1, u32 arg2);

void func_8006DD28(u32 arg0, u32 arg1) {
    s32 i;
    s32 m;
    u32 n;
    s32 pos;
    extern u8 D_800A307C[];
    extern u8 D_800A36E4[];

    m = (u8)arg0;
    n = (u8)arg1;
    func_8006E628(m, n, D_800A307C[m]);
    pos = (m << 3) + m;
    for (i = 0; i < 3; i++) {
        if (i == 2) {
            s32 idx;

            idx = pos + i * 3;
            D_800AEE3C[idx] = 0;
            D_800AEE3D[idx] = 0xFF;
        } else if (n >= 5) {
            if (i == 0) {
                s32 idx;

                idx = pos + i * 3;
                D_800AEE3D[idx] = 0;
                D_800AEE3C[idx] = D_800AEE3E[idx];
            } else {
                s32 idx;

                idx = pos + i * 3;
                D_800AEE3D[idx] = 0xFF;
                D_800AEE3C[idx] = D_800AEE3E[idx];
            }
        } else {
            s32 idx;

            idx = pos + i * 3;
            D_800AEE3C[idx] = 0;
            D_800AEE3D[idx] = 0xFF;
        }
    }
    D_800A36E4[(u8)arg0] = 1;
}

extern u8 D_800AEE3C[];

void func_8006DE68(u32 arg0, u32 mode) {
    if ((mode & 0xFF) == 2) {
        s32 i;
        s32 j;
        s32 m;
        s32 pos;
        s32 end;

        i = 0;
        j = 2;
        m = (u8)arg0;
        pos = m << 3;
        pos += m;
        end = pos + 6;
        do {
            if (i == j) {
                D_800AEE3C[end] = 0x78;
                D_800AEE3C[end + 1] = 0x80;
                D_800AEE3C[end + 2] = 0x88;
            } else {
                D_800AEE3C[pos] = 0;
                D_800AEE3C[pos + 1] = 8;
                D_800AEE3C[pos + 2] = 0;
            }
            i++;
            pos += 3;
        } while (i < 3);
    } else {
        s32 n;
        s32 pos;

        n = (u8)arg0;
        pos = n << 3;
        pos += n;
        D_800AEE3C[pos] = 0x80;
        D_800AEE3C[pos + 1] = 0x78;
        D_800AEE3C[pos + 2] = 0x80;
        D_800AEE3C[pos + 3] = 0x80;
        D_800AEE3C[pos + 4] = 0x88;
        D_800AEE3C[pos + 5] = 0x80;
        D_800AEE3C[pos + 6] = 0x78;
        D_800AEE3C[pos + 7] = 0x88;
        D_800AEE3C[pos + 8] = 0x80;
    }
}

/* A mode above 2 falls off the end of the switch, as in retail: the return
 * value is whatever the dispatch left in v0 (2). The narrow `u8 arg3`
 * parameter makes gcc keep a raw copy of a3 for the mode 0 and 1 tests. */
u8 func_8006DF98(void *arg0, s32 arg1, s32 arg2, u8 arg3) {
    u8 mode;

    mode = arg1;
    switch (mode) {
    case 0:
        if ((u8)arg2 != 2) {
            return ((u8 *)arg0)[0x3C6];
        } else if (arg3 == 0 || arg3 == (u8)arg2) {
            return ((u8 *)arg0)[0x3C7];
        } else {
            return ((u8 *)arg0)[0x3C6];
        }
    case 1:
        if ((u8)arg2 != 2) {
            return ((u8 *)arg0)[0x3C6];
        } else if (arg3 != 0 && arg3 != (u8)arg2) {
            return ((u8 *)arg0)[0x3C7];
        } else {
            return ((u8 *)arg0)[0x3C6];
        }
    case 2:
        if ((u8)arg2 == mode) {
            if ((u8)(arg3 - 2) < 2) {
                return (u8) ~((u8 *)arg0)[0x3C5];
            } else {
                return ((u8 *)arg0)[0x3C5];
            }
        } else {
            return ((u8 *)arg0)[0x3C5];
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/memory_card_menu", func_8006E07C);

void func_8006E484(u32 arg0, u32 arg1) {
    s32 i;
    s32 m;
    u32 n;
    s32 pos;
    s32 maxb;
    s32 white;
    s32 lt;
    s32 p;
    s32 d;
    u8 *q;
    u8 *v;
    i = 0;
    m = (u8)arg0;
    pos = (m << 3) + m;
    do {
        maxb = 0x80;
        white = 0xFF;
        n = (u8)arg1;
        lt = n < 5;
        p = 0;
    loop:
        v = (u8 *)(p + ((s32)D_800AEE3C));
        q = (u8 *)(pos + ((s32)v));
        if (i == 2) {
            if (((u32)(q[2] - 0x60)) >= 0x41) {
                q[2] = maxb;
            }
            d = q[1] - q[2];
            if (d < 9) {
                q[1] = white;
            }
            d = q[2] - q[0];
            if (d < 9) {
                q[0] = 0;
            }
        } else if (!lt) {
            if (((u32)((q[2] - 0x40) & 0xFF)) >= 0x81) {
                q[2] = maxb;
            }
            if (i == 0) {
                d = q[2] - q[1];
                if (d >= 0) {
                    if (d < 9) {
                        goto setg;
                    }
                } else {
                    d = q[1] - q[2];
                    if (d < 9) {
                        goto setg;
                    }
                }
                goto nextg;
            setg:
                q[1] = 0;
            nextg:;
                ;
                ;
            } else {
                d = q[1] - q[2];
                if (d >= 0) {
                    if (d < 9) {
                        goto setw;
                    }
                } else {
                    d = q[2] - q[1];
                    if (d < 9) {
                        q[1] = white;
                    }
                }
            }
        } else {
            if (q[2] >= 0x81) {
                q[2] = 0;
            }
            d = q[1] - q[0];
            if (d < 9) {
                q[0] = 0;
            setw:
                q[1] = white;
            }
        }
        i++;
    } while (0);
    p += 3;
    if (i < 3) {
        goto loop;
    }
}

INCLUDE_ASM("asm/nonmatchings/memory_card_menu", func_8006E628);
