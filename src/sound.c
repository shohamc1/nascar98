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

extern s16 D_800B9E24[];
extern u8 D_800A3880;
extern void SoundLoadVab(s32);

void func_8003F060(s32 arg0) {
    u8 i;
    s16 value;

    i = 0;
    value = -1;
again:
    D_800B9E24[i * 6] = value;
    i++;
    if (i < 24) {
        goto again;
    }
    gVabId = -1;
    gSequenceData = 0;
    D_800A3A08 = 0;
    SoundLoadVab(arg0);
    D_800A3880 = 0;
}

extern s16 D_800B9E24[];
extern u8 D_800A3880;
extern void SoundReloadVab(s32);

void func_8003F0CC(s32 arg0) {
    u8 i;
    s32 off;

    for (i = 0; i < 24; i++) {
        off = i;
        off = off * 12;
        *(s16 *)((u8 *)D_800B9E24 + off) = -1;
    }
    gVabId = -1;
    gSequenceData = 0;
    D_800A3A08 = 0;
    SoundReloadVab(arg0);
    D_800A3880 = 1;
}

#ifdef NON_MATCHING
extern void func_8003FA0C(void);
extern s32 SoundVabOpen(s32, s32);

void SoundLoadVab(s32 arg0) {
    s32 value;

    func_8003FA0C();
    if (gVabId != -1)
        SsVabClose(gVabId);
    D_800A3A08 = (s32)func_8003FFF0((void *)(arg0 + 1), 0);
    value = (s32)func_8003FFF0((void *)arg0, 0x80140000);
    D_800A3A00 = (void *)value;
    gVabId = SoundVabOpen(D_800A3A08, value);
}
#else
extern s16 gVabId;
extern void *D_800A3A00;
extern s32 D_800A3A08;
extern s32 func_8003FFF0(void *, void *);
extern s16 SoundVabOpen(void *, void *);
extern void SsVabClose(s16);
extern void func_8003FA0C(void);

void SoundLoadVab(s32 arg0) {
    volatile s32 buf[8];
    s32 body;

    func_8003FA0C();
    if (gVabId != -1) {
        SsVabClose(gVabId);
    }
    D_800A3A08 = func_8003FFF0((void *)(s32 *)arg0 + 1, 0);
    body = func_8003FFF0((void *)arg0, (void *)0x80140000);
    D_800A3A00 = body;
    gVabId = SoundVabOpen((void *)D_800A3A08, (void *)body);
}
#endif

#ifdef NON_MATCHING
void SoundReloadVab(s32 arg0) {
    s32 value;

    func_8003FA0C();
    if (gVabId != -1)
        SsVabClose(gVabId);
    D_800A3A08 = (s32)func_8003FFF0((void *)arg0, 0);
    value = (s32)func_8003FFF0((void *)(arg0 + 1), 0);
    D_800A3A00 = (void *)value;
    gVabId = SoundVabOpen(D_800A3A08, value);
    if (D_800A3A00 != 0) {
        HeapFree(D_800A3A00);
        D_800A3A00 = 0;
    }
}
#else
extern s16 gVabId;
extern void *D_800A3A00;
extern s32 D_800A3A08;
extern s32 func_8003FFF0(void *, void *);
extern s16 SoundVabOpen(void *, void *);
extern void SsVabClose(s16);
extern void HeapFree(void *);
extern void func_8003FA0C(void);

void SoundReloadVab(s32 arg0) {
    volatile s32 buf[8];
    s32 body;

    func_8003FA0C();
    if (gVabId != -1) {
        SsVabClose(gVabId);
    }
    D_800A3A08 = func_8003FFF0((void *)arg0, 0);
    body = func_8003FFF0((void *)(arg0 + 1), 0);
    D_800A3A00 = body;
    gVabId = SoundVabOpen((void *)D_800A3A08, (void *)body);
    if (D_800A3A00 != 0) {
        HeapFree((void *)D_800A3A00);
        D_800A3A00 = 0;
    }
}
#endif

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

extern u8 D_800A2F94;

void func_8003F2AC(s32 arg0, s32 arg1) {
    SsUtSetReverbDepth((s16)((arg0 & 0xFF) * D_800A2F94 / 127),
                       (s16)((arg1 & 0xFF) * D_800A2F94 / 127));
}

extern s32 func_8003FFF0(void *, void *);
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

extern s32 SpuGetKeyStatus(s32);

extern s16 D_800B9E24[];
extern s32 SpuGetKeyStatus(s32);

s32 func_8003F4FC(s32 arg0) {
    s16 voice;
    s32 status;

    voice = D_800B9E24[(s8)arg0 * 6];
    if (voice != -1) {
        status = SpuGetKeyStatus(1 << voice);
        if (status == 1) {
            return 1;
        }
        return status != 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/sound", func_8003F564);

INCLUDE_ASM("asm/nonmatchings/sound", func_8003F914);

extern s16 D_800B9E24[];
extern void func_8003F914(s32);

void func_8003FA0C(void) {
    u8 i;
    s32 value;
    s16 voice;

    i = 0;
    value = -1;
again:
    voice = D_800B9E24[i * 6];
    if (voice != value) {
        func_8003F914((s8)i);
    }
    i++;
    if (i < 24) {
        goto again;
    }
}

extern u8 D_800A3880;
extern s16 D_800B9E24[];
extern u8 D_800B9E26[];
extern s16 D_800B9E2A[];
extern s32 SsUtPitchBend(s16, s16, s8, s16, s8);

void func_8003FA84(id, pitch) s8 id;
s8 pitch;
{
    s16 va;
    s32 type;
    s32 v;
    s32 note;

    va = D_800B9E24[(s8)id * 6];
    if (va == -1) {
        return;
    }
    type = D_800B9E26[(s8)id * 12];
    if (D_800A3880 != 0) {
        note = ((s8)id == 1) ? 0xF : 0;
    } else {
        v = (s8)type;
        if (v >= 0x40) {
            note = 0xA;
        } else if (v >= 0x20) {
            if (v >= 0x2C) {
                switch (v) {
                case 0x2C:
                    note = 0x24;
                    break;
                case 0x2D:
                    note = 0x26;
                    break;
                case 0x29:
                    note = 0x29;
                    break;
                default:
                    break;
                }
                note -= 0x20;
            } else if (v >= 0x2A) {
                switch (v) {
                case 0x2A:
                    note = 0x12;
                    break;
                case 0x2B:
                    note = 0x13;
                    break;
                default:
                    break;
                }
            } else {
                note = type - 0x20;
            }
        } else if ((u32)(type - 0xC) < 4) {
            note = 0x1A - type;
        } else {
            note = 0xF;
        }
    }
    SsUtPitchBend(va, gVabId, (s8)note, D_800B9E2A[(s8)id * 6], (s8)pitch);
}

extern s16 D_800B9E2C[];
extern s16 D_800B9E2E[];
extern s8 SsUtChangePitch(s16, s16, s8, s16, s32, s32, s32);

void func_8003FC0C(id, pitch, vol) s8 id;
s8 pitch;
s8 vol;
{
    s16 va;
    s32 type;
    s32 v;
    s32 note;

    va = D_800B9E24[(s8)id * 6];
    if (va == -1) {
        return;
    }
    type = D_800B9E26[(s8)id * 12];
    if (D_800A3880 != 0) {
        note = ((s8)id == 1) ? 0xF : 0;
    } else {
        v = (s8)type;
        if (v >= 0x40) {
            note = 0xA;
        } else if (v >= 0x20) {
            if (v >= 0x2C) {
                switch (v) {
                case 0x2C:
                    note = 0x24;
                    break;
                case 0x2D:
                    note = 0x26;
                    break;
                case 0x29:
                    note = 0x29;
                    break;
                default:
                    break;
                }
                note -= 0x20;
            } else if (v >= 0x2A) {
                switch (v) {
                case 0x2A:
                    note = 0x12;
                    break;
                case 0x2B:
                    note = 0x13;
                    break;
                default:
                    break;
                }
            } else {
                note = type - 0x20;
            }
        } else if ((u32)(type - 0xC) < 4) {
            note = 0x1A - type;
        } else {
            note = 0xF;
        }
    }
    if (SsUtChangePitch(va, gVabId, (s8)note, D_800B9E2A[(s8)id * 6], 0,
                        (s8)pitch, (s8)vol) != -1) {
        D_800B9E2C[(s8)id * 6] = (s8)pitch;
        D_800B9E2E[(s8)id * 6] = (s8)vol;
    }
}

void func_8003FDE8(s8 arg0, s32 arg1, s32 arg2) {
    s16 voice;
    u16 volL;
    u16 volR;

    voice = D_800B9E24[(s8)arg0 * 6];
    if (voice != -1) {
        volL = ((arg1 & 0xFF) * D_800A2F94) / 127;
        volR = ((arg2 & 0xFF) * D_800A2F94) / 127;
        if (volL >= 0x80) {
            volL = 0x7F;
        }
        if (volR >= 0x7F) {
            volR = 0x7F;
        }
        SsUtSetVVol(voice, volL, volR);
    }
}

extern s16 D_800B9E24[];
extern void func_8003F914(s32);

void func_8003FEB8(void) {
    s8 keys[24];
    s8 *keyState;
    s8 i;
    s16 voice;
    s32 noVoice;

    SpuGetAllKeysStatus(keys);
    i = 0;
    noVoice = -1;
    keyState = keys;
again:
    voice = D_800B9E24[i * 6];
    if (voice != noVoice && keyState[voice] == 3) {
        func_8003F914(i);
    }
    i++;
    if (i < 0x18) {
        goto again;
    }
}

extern char D_8008D1A8[];
extern char D_8008D1C4[];

s16 SoundVabOpen(void *arg0, void *arg1) {
    s16 vabId;
    s16 result;

    vabId = SsVabOpenHead(arg0, -1);
    if (vabId == -1) {
        SystemShowFatalError(D_8008D1A8);
    } else {
        result = SsVabTransBody(arg1, vabId);
        if (result == vabId) {
            SsVabTransCompleted(1);
            return result;
        }
        SystemShowFatalError(D_8008D1C4);
    }
    return -1;
}

/* Loads a whole file into arg1, or into a page-rounded HeapAlloc block when
 * arg1 is NULL. D_800A2F98 is the "rb" mode string for FileOpen. Assigning
 * buffer in both arms keeps the allocation in arg1's register and keeps the
 * first guard's branch on the second test.
 */
extern char D_8008D1DC[];
extern char D_8008D1F8[];
extern char D_800A2F98[];

s32 func_8003FFF0(void *arg0, void *arg1) {
    void *buffer;
    void *handle;
    s32 padded;
    s32 size;

    handle = FileOpen(arg0, D_800A2F98);
    if (handle == NULL) {
        SystemShowFatalError(D_8008D1DC);
    }
    size = ((s32 (*)(void *, s32, s32))FileSeek)(handle, 0, 2);
    ((s32 (*)(void *, s32, s32))FileSeek)(handle, 0, 0);
    padded = size + 0x800;
    size = padded - size % 0x800;
    if (arg1 == NULL) {
        buffer = HeapAlloc(size);
    } else {
        buffer = arg1;
    }
    if (buffer == NULL) {
        SystemShowFatalError(D_8008D1F8);
    }
    FileRead((s32)buffer, 1, size, handle);
    ((void (*)(s32))FileClose)((s32)handle);
    return (s32)buffer;
}
INCLUDE_RODATA("asm/nonmatchings/sound", D_8008D1DC);
INCLUDE_RODATA("asm/nonmatchings/sound", D_8008D1F8);
INCLUDE_RODATA("asm/nonmatchings/sound", D_8008D21C);
INCLUDE_RODATA("asm/nonmatchings/sound", D_8008D228);
INCLUDE_RODATA("asm/nonmatchings/sound", D_8008D234);

extern s32 D_80098D00[];
extern u8 D_800A354C[];
extern s32 D_800BE988[];
extern u8 D_800A2FA4[];
extern u8 D_800A39D0;
extern u8 D_800BA048[];

void func_800400D8(s32 arg0) {
    volatile s32 pad[4];
    s32 i;
    u8 next;

    i = 0;
    do {
        if (D_80098D00[i] == arg0) {
            goto found;
        }
        i++;
    } while (i < 4);
    i = 0;
    do {
        if (D_80098D00[i] == 0) {
            goto empty;
        }
        i++;
    } while (i < 4);
    next = D_800A39D0;
    D_800A39D0 = next + 1;
    *(s32 *)((u8 *)D_800BA048 + (((s32)(s8)next << 24) >> 22)) = arg0;
    return;
found:
    D_800A354C[i] = 1;
    return;
empty:
    D_80098D00[i] = arg0;
    D_800BE988[i] = -1;
    D_800A354C[i] = 1;
    D_800A2FA4[i] = 5;
}

extern s8 D_800A2FA4B[] asm("D_800A2FA4.NON_MATCHING");
extern s32 D_800BE988[];
extern s32 D_80098D00[];
extern s8 D_800A354CB[] asm("D_800A354C.NON_MATCHING");
extern s32 D_800BA048B[] asm("D_800BA048.NON_MATCHING");
extern s8 D_800A39D0B asm("D_800A39D0.NON_MATCHING");
void func_800401B8(void) {
    s32 i;
    s32 initialized;
    i = 0;
    initialized = 0;
    while (i < 4) {
        if (D_800A354CB[i] == 0 && D_800A2FA4B[i] == 0) {
            D_800A354CB[i] = 1;
            D_80098D00[i] = D_800BA048B[initialized];
            D_800BE988[i] = -1;
            D_800A2FA4B[i] = 5;
            initialized++;
            if (initialized == D_800A39D0B)
                break;
        }
        i++;
    }
}

INCLUDE_ASM("asm/nonmatchings/sound", func_80040260);

extern s32 D_800BE890w16[] asm("D_800BE890.NON_MATCHING");
extern u8 D_80098C00w16[] asm("D_80098C00.NON_MATCHING");
extern u8 D_800A306Cw16[] asm("D_800A306C.NON_MATCHING");
extern void func_8001F90C(s32, s32, s32, s16 *);
extern void func_8003F564(s8, s8);
extern void func_8003FDE8(s8, s32, s32);

void func_800406D0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    extern u8 D_800A2F9DSmall;
    u8 *car;
    u8 *obj;
    s32 camX;
    s32 camY;
    s32 camZ;
    s32 dx;
    s32 dy;
    register s32 dz asm("s0");
    s32 dist;
    register s32 fog asm("s3");
    s32 pan;
    s32 q;
    register s32 gain asm("a0");
    register s32 vol1 asm("s1");
    register s32 vol2 asm("s2");
    s16 out[2];
    register s32 row asm("v0");
    register s32 scaled asm("v0");
    register s32 square asm("t1");
    s32 sum;
    register s32 dySq asm("v1");
    register s32 prodB asm("t1");
    register s32 prodA asm("v1");
    register s32 one asm("v0");
    register s32 magic asm("v1");
    register s32 hi asm("t0");
    register s32 quot asm("v1");
    s32 sign;

    camX = *(s32 *)(arg0 + 0);
    camY = *(s32 *)(arg0 + 4);
    camZ = *(s32 *)(arg0 + 8);
    car = arg0;
    obj = arg1;
    if (D_800A2F9DSmall == 0) {
        return;
    }
    if (D_800A2EC0nm[0] - D_800BE890w16[0] < 10) {
        return;
    }
    D_800BE890w16[0] = D_800A2EC0nm[0];
    if (func_8003702C(car, obj) < 0) {
        if (-func_8003702C(car, obj) >= 0x29) {
            goto fail;
        }
    } else {
        if (func_8003702C(car, obj) >= 0x29) {
        fail:
            func_8003FDE8((s8)arg2, 0, 0);
            return;
        }
    }
    row = *(s32 *)(obj + 0);
    dx = (row - camX) >> 4;
    row = *(s32 *)(obj + 4);
    dy = (row - camY) >> 4;
    row = *(s32 *)(obj + 8);
    dz = (row - camZ) >> 4;
    sum = dx * dx;
    dySq = dy * dy;
    square = dz * dz;
    sum = sum + dySq;
    dist = MathSqrt(sum + square);
    magic = 0x5D9F0000;
    if (dist >= 0x579) {
        func_8003FDE8((s8)arg2, 0, 0);
        return;
    }
    magic = magic | 0x7391;
    scaled = (dist << 8) - dist;
    asm volatile("mult\t%0,%1" : : "r"(scaled), "r"(magic));
    sign = scaled >> 31;
    asm volatile("mfhi\t%0" : "=r"(hi));
    quot = hi >> 9;
    fog = quot - sign;
    if (fog >= 0x100) {
        fog = 0xFF;
    }
    func_8001F90C((0x400 - *(s16 *)(car + 0x114)) & 0x3FF, dx, dy, out);
    pan = out[1];
    if (pan > 0) {
        q = MathFixedDivide(pan, dist);
        gain = D_80098C00w16[fog];
        one = 0x10000;
        prodA = (q + one) * gain;
        vol2 = prodA >> 16;
        prodB = (one - q) * gain;
        vol1 = prodB >> 16;
    } else {
        if (pan < 0) {
            pan = -pan;
        }
        q = MathFixedDivide(pan, dist);
        gain = D_80098C00w16[fog];
        one = 0x10000;
        prodA = (q + one) * gain;
        vol1 = prodA >> 16;
        prodB = (one - q) * gain;
        vol2 = prodB >> 16;
    }
    if (vol2 >= 0x65) {
        vol2 = 0x64;
    }
    if (vol1 >= 0x65) {
        vol1 = 0x64;
    }
    if (D_800A306Cw16[0] != 0) {
        if (vol1 < vol2) {
            vol1 = vol2;
        } else {
            vol2 = vol1;
        }
    }
    func_8003F564((s8)arg2, (s8)arg3);
    func_8003FDE8((s8)arg2, (u8)vol2, (u8)vol1);
}

extern u8 D_800A2F9D;
extern s32 D_800A2EA4[];
extern u8 *D_800A3554nm[] asm("D_800A3554.NON_MATCHING");
extern void func_8003FC0C(s32, s32, s32);
extern void func_8003F564(s8, s8);

void func_800409A0(u8 *object) {
    s32 id;
    u8 *player;

    if (D_800A2F9D == 0) {
        return;
    }
    if (object == D_800A3554[0]) {
        id = 0x14;
    } else {
        id = 0x15;
    }
    func_8003FC0C(
        id, (s8)(*(s16 *)(object + 0x92) * 8 / *(s16 *)(object + 0x9A) + 0x2C),
        0);
    if (*(s8 *)(object + 0x3B8) == 0) {
        /* A second name for the player table keeps cse from sharing the
         * address register across the call; the local reads it once. */
        player = D_800A3554nm[0];
        if (object == player) {
            func_8003F564(0x14, 2);
        } else if (object == *(u8 **)(player + 0x3E0) && D_800A2EA4[0] == 2) {
            func_8003F564(0x15, 2);
        }
    }
    *(u8 *)(object + 0x3B9) = 1;
    if (*(s16 *)(object + 0x120) != 0) {
        *(u8 *)(object + 0x3B8) = 0x17;
    }
    *(u8 *)(object + 0x3B8) = *(u8 *)(object + 0x3B8) + 1;
    if ((s8) * (u8 *)(object + 0x3B8) >= 0x19) {
        *(u8 *)(object + 0x3B8) = 0x18;
    }
}

void func_80040AC0(u8 *object) {
    object[0x3B9] = 0;
}

void func_80040AC8(u8 *object) {
    s32 id;
    s32 count1;
    s32 count2;
    s32 count3;
    s32 count4;
    s32 vol;

    if (*(s8 *)(object + 0x20B) != 0) {
        id = 0x10;
    } else {
        id = 0xE;
    }
    count1 = 0;
    count2 = 0;
    count3 = 0;
    count4 = 0;
    vol = 0x40;
    if (object[0xF4] != 0) {
        if (*(s32 *)(object + 0x90) <= 0x1FFFFF) {
            vol = *(s32 *)(object + 0x90) >> 15;
            if (vol < 0) {
                vol = 0;
            }
        }
        if (*(u16 *)(object + 0x362) == 2) {
            count1++;
        } else if (*(u16 *)(object + 0x362) == 3) {
            count3++;
        }
        if (*(u16 *)(object + 0x364) == 2) {
            count2++;
        } else if (*(u16 *)(object + 0x364) == 3) {
            count4++;
        }
        if (*(u16 *)(object + 0x366) == 2) {
            count1++;
        } else if (*(u16 *)(object + 0x366) == 3) {
            count3++;
        }
        if (*(u16 *)(object + 0x368) == 2) {
            count2++;
        } else if (*(u16 *)(object + 0x368) == 3) {
            count4++;
        }
    }
    if (count1 | count2) {
        func_8003F564((s8)id, 5);
        count1 = (count1 * 30 + 60) * vol >> 6;
        count2 = (count2 * 30 + 60) * vol >> 6;
        func_8003FDE8((s8)id, count1 & 0xFF, count2 & 0xFF);
    } else {
        func_8003F914((s8)id);
    }
    id++;
    if (count3 | count4) {
        func_8003F564((s8)id, 7);
        count3 = (count3 * 30 + 60) * vol >> 6;
        count4 = (count4 * 30 + 60) * vol >> 6;
        func_8003FDE8((s8)id, count3 & 0xFF, count4 & 0xFF);
    } else {
        func_8003F914((s8)id);
    }
}

typedef struct SoundCarLink {
    struct SoundCarLink *next;
    struct SoundCarLink *previous;
    u8 *car;
} SoundCarLink;

void SoundUpdateCar(u8 *car) {
    extern u32 RandomGetScaled16(s32);
    extern void func_80040260(u8 *, s32);
    extern void func_800400D8Pair(u8 *, u8 *) asm("func_800400D8");
    extern s8 D_800A354F[];
    s32 i;
    s32 distance;
    s32 pitch;
    s32 blend;
    s32 id;
    s32 volume;
    s32 decayVolume;
    s32 unusedHigh;
    s32 sample;
    s32 shiftedRpm;
    s8 *clearFlags;
    u16 rpm;
    SoundCarLink *next;
    SoundCarLink *previous;
    s8 *flags;
    s8 *fade;
    s32 *handles;
    s32 *positions;
    s32 *pending;
    s32 initialized;
    s32 channel;
    s32 one;
    s32 minusOne;
    s32 five;

    if (D_800A2ED4[0] == 1) {
        for (i = 0; i < 5; i++) {
            func_8003FDE8((s8)i, 0, 0);
        }
        for (i = 14; i < 18; i++) {
            func_8003F914((s8)i);
        }
        return;
    }
    if (D_800A2EACAbsolute[0] == 0 || D_800A2EACAbsolute[0] >= 3) {
        if (D_800A2EC8[0] == 0 && *(s8 *)(car + 0x3B8) > 0) {
            id = 20;
            if (car != D_800A3554[0]) {
                id = 21;
            }
            if (*(s8 *)(car + 0x3B9) == 0) {
                *(s8 *)(car + 0x3B8) -= 3;
                if (*(s8 *)(car + 0x3B8) <= 0) {
                    *(s8 *)(car + 0x3B8) = 0;
                    func_8003F914((s8)id);
                }
            }
            decayVolume = (*(s8 *)(car + 0x3B8) * 4 + 31) & 0xFF;
            func_8003FDE8((s8)id, decayVolume, decayVolume);
        }
        func_80040AC8(car);
        if (D_800A2F9D != 0) {
            rpm = *(u16 *)(car + 0x108);
            pitch = ((s16)rpm + *(s16 *)(car + 0x10A)) / 100;
            if ((s16)rpm >= 2001 && *(s32 *)(car + 0x90) <= 0x95FFFF &&
                D_800A2EC8[0] == 0 &&
                RandomGetScaled16((s16)((s16)rpm / 1000)) == 0) {
                pitch -= pitch / (s16)(*(s16 *)(car + 0x108) / 1700);
            }
            /* Retail keeps this unused filter calculation. */
            blend = pitch + *(s16 *)(car + 0x3BA) + *(s16 *)(car + 0x3BA) +
                    *(s16 *)(car + 0x3BA) + 3;
            asm("" : : "r"(blend) : "memory");
            if (*(s16 *)(car + 0x108) >= 7001 && D_800A2EC8[0] == 0 &&
                RandomGetScaled16((s16)(*(s16 *)(car + 0x108) / 1000)) == 0) {
                /* Retail also keeps this unused signed high product. */
                register s32 magic asm("a0");
                u16 highRpm;
                highRpm = *(u16 *)(car + 0x108);
                shiftedRpm = (u32)highRpm << 16;
                asm("" : "=r"(shiftedRpm) : "0"(shiftedRpm) : "v0");
                sample = shiftedRpm >> 16;
                magic = 0x134679AD;
                asm("mult %1,%2"
                    : "=h"(unusedHigh)
                    : "r"(sample), "r"(magic), "r"(shiftedRpm)
                    : "lo");
                asm("" : : "r"(unusedHigh));
            }
            volume = 100;
            if (*(s32 *)(car + 0x3BC) >= 4097) {
                volume = 127;
            }
            if (*(s16 *)(car + 0x1CA) + 7 < volume) {
                *(s16 *)(car + 0x1CA) = *(s16 *)(car + 0x1CA) + 7;
            } else if (volume < *(s16 *)(car + 0x1CA) - 3) {
                *(s16 *)(car + 0x1CA) = *(s16 *)(car + 0x1CA) - 3;
            } else {
                *(s16 *)(car + 0x1CA) = volume;
            }
            if (*(s16 *)(car + 0x1CA) >= 128) {
                *(s16 *)(car + 0x1CA) = 127;
            }
            volume = *(s16 *)(car + 0x1CA);
            pitch = (*(s16 *)(car + 0x108) + *(s16 *)(car + 0x10A)) / 110 - 32;
            if (*(s8 *)(car + 0x3CA) >= 18) {
                pitch = 78;
            }
            pitch += *(s32 *)(car + 0x3BC) >> 11;
            if (*(s16 *)(car + 0x3BA) + 7 < pitch) {
                *(s16 *)(car + 0x3BA) = *(s16 *)(car + 0x3BA) + 7;
            } else if (pitch < *(s16 *)(car + 0x3BA) - 5) {
                *(s16 *)(car + 0x3BA) = *(s16 *)(car + 0x3BA) - 5;
            } else {
                *(s16 *)(car + 0x3BA) = pitch;
            }
            if (*(s16 *)(car + 0x3BA) >= 128) {
                *(s16 *)(car + 0x3BA) = 127;
            }
            pitch = *(s16 *)(car + 0x3BA);
            if (car == D_800A3554[0]) {
                func_8003FA84(0, (s8)pitch);
                func_8003FDE8(0, volume & 0xFF, volume & 0xFF);
            } else {
                if (*(s16 *)(D_800A3554[0] + 0x3BA) >= 125 && pitch >= 125) {
                    pitch = 120;
                }
                func_8003FDE8(1, volume & 0xFF, volume & 0xFF);
                func_8003FA84(1, (s8)pitch);
            }
            i = 3;
            if (D_800A2E94[0] == 24) {
                next = *(SoundCarLink **)(car + 0x3F0);
                previous = *(SoundCarLink **)(car + 0x3F4);
                clearFlags = D_800A354F;
                D_800A39D0B = 0;
                do {
                    *clearFlags = 0;
                    i--;
                    clearFlags--;
                } while (i >= 0);
                for (i = 0; i < 4; i++) {
                    distance = ABS(func_8003702C(car, next->car));
                    if (distance < ABS(func_8003702C(car, previous->car))) {
                        func_800400D8Pair(next->car, car);
                        next = next->next;
                    } else {
                        func_800400D8Pair(previous->car, car);
                        previous = previous->previous;
                    }
                }
                channel = 0;
                if (D_800A39D0B > 0) {
                    initialized = 0;
                    one = 1;
                    minusOne = -1;
                    five = 5;
                    asm("" : : "r"(one), "r"(minusOne), "r"(five));
                    fade = D_800A2FA4B;
                    handles = D_800BE988;
                    positions = D_80098D00;
                    flags = D_800A354CB;
                    pending = D_800BA048B;
                initializeChannel:
                    if (*flags == 0 && *fade == 0) {
                        *flags = one;
                        *positions = *pending;
                        *handles = minusOne;
                        *fade = five;
                        initialized++;
                        pending++;
                        if (initialized == D_800A39D0B) {
                            goto channelsReady;
                        }
                    }
                    fade++;
                    handles++;
                    positions++;
                    channel++;
                    flags++;
                    if (channel < 4) {
                        goto initializeChannel;
                    }
                }
            channelsReady:
                func_80040260(car, 1);
                func_80040260(car, 2);
                func_80040260(car, 3);
                func_80040260(car, 4);
            }
        }
    }
}

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

void func_80041564(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern u8 D_800A2EDC[];
    extern u8 D_800A2F9D;
    extern s32 D_800A397C[];
    extern u8 *D_800A3554[];
    extern s32 D_800A2EA4[];
    extern s32 D_800A2EC0Absolute[];
    extern u8 D_800A38B0[];
    extern s32 D_800A2E90[];
    extern s32 D_800A2EB0Absolute[];
    extern u8 D_800A2EE0[];
    extern s32 D_800A2EACAbsolute[];
    extern s32 D_800BE86C[];
    extern void func_80025594();
    extern void func_8003F564(s8, s8);
    extern void func_8003FDE8(s8, s32, s32);
    s32 timer;
    s32 *base;
    s32 *slot;

    arg2 = 15;
    arg3 = -1;
    if (((u8 *)D_800A2EDC)[-2] != 0) {
        return;
    }
    if (D_800A2F9D == 0) {
        return;
    }
    if (D_800A397C[0] == 2) {
        return;
    }
    if (*(u8 *)(D_800A3554[0] + 0xF4) == 0 && D_800A2EA4[0] == 0) {
        return;
    }
    timer = D_800A2EC0Absolute[0];
    switch (arg1) {
    case 0x41:
        if (*(s32 *)(arg0 + 0x28C) == 0) {
            return;
        }
        arg3 = 0x4B0;
        arg2 = 0;
        break;
    case 0x44:
        arg3 = 0x14;
        arg2 = 3;
        break;
    case 0x42:
        arg3 = 0xC8;
        arg2 = 2;
        break;
    case 0x48:
        if (*(s32 *)(arg0 + 0x28C) == 0) {
            return;
        }
        arg3 = 0x438;
        arg2 = 1;
        break;
    case 0x43:
        if (*(u8 *)(arg0 + 0xF4) == 0) {
            return;
        }
        /* falls through */
    case 0x40:
    case 0x45:
    case 0x46:
    case 0x47:
        arg2 = 4;
        break;
    case 0x2A:
    case 0x2B:
        arg3 = 0x14;
        arg2 = 5;
        break;
    case 0x27:
        arg3 = 0x7D0;
        arg2 = 5;
        break;
    case 0x25:
        if (*(s32 *)(arg0 + 0x90) <= 0xC7FFFF) {
            return;
        }
        arg3 = 0x12C;
        arg2 = 5;
        break;
    case 0x26:
        if (*(s32 *)(arg0 + 0x354) != (s32)func_80025594) {
            return;
        }
        if (D_800A38B0[0] != 0) {
            return;
        }
        arg2 = 0xF;
        arg3 = 0x190;
        arg1 += *(s32 *)((u8 *)D_800A2EACAbsolute + 0x14) & 1;
        break;
    case 0x24:
        if (D_800A2E90[0] < 6) {
            return;
        }
        /* falls through */
    case 0x23:
        arg3 = 0x708;
        arg2 = 6;
        break;
    case 0x21:
        if (D_800A2EB0Absolute[0] != 0) {
            return;
        }
        arg3 = 0;
        arg2 = 7;
        break;
    case 0x22:
        if (D_800A2EB0Absolute[0] == 1) {
            return;
        }
        arg3 = 0;
        arg2 = 7;
        break;
    case 0x28:
        arg3 = 0;
        arg2 = 7;
        if (*(u8 *)(arg0 + 0xF4) == 0) {
            return;
        }
        if (D_800A2EB0Absolute[0] == 1) {
            return;
        }
        break;
    case 0x29:
        if (D_800A2EB0Absolute[0] != 0) {
            return;
        }
        if (D_800A2EE0[0] != 0) {
            return;
        }
        if ((*(u16 *)(arg0 + 0x3A4) & 0xF) == 0) {
            return;
        }
        if (*(u8 *)(arg0 + 0xF4) == 0) {
            return;
        }
        arg3 = 0x12C;
        arg2 = 8;
        break;
    }
    if (D_800A2EACAbsolute[0] != 0) {
        if (arg2 < 2) {
            return;
        }
        if (arg1 == 0x25) {
            return;
        }
    }
    base = D_800BE86C;
    slot = base + arg2;
    if (*slot == -1 || arg3 < timer - *slot) {
        func_8003F564(0x12, (s8)arg1);
        func_8003FDE8(0x12, 0xFF, 0xFF);
        *slot = timer;
    }
}

void func_80041848(u8 *arg0, s32 arg1) {
}

/* Sound startup and shutdown. */

/* w6f WALL (cc1 ICE): adding any function with a branch statement (if,
 * if/else) near this position segfaults cc1 2.7.2 (cpp reports
 * "output pipe has been closed"; the object emits 0 symbols and the
 * link fails with hundreds of undefined references). Reproduced with a
 * 3-line `if` touching only pre-existing symbols, and with the same
 * probe inserted at other TU positions, so it is not positional. A
 * for-loop body in the same function compiled fine. Also reproducible:
 * the crash follows the statement stream, not one statement. Parked as
 * assembly. */
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

void func_80041850(void) {
    s32 val;
    s32 i;
    s32 t;
    s32 *p;
    s32 msg;

    val = -1;
    i = 0xF;
    p = D_800BE8A8;
    do {
        *p = val;
        i -= 1;
        p -= 1;
    } while (i >= 0);
    D_800A2FA0 = 0;
    if (D_800A2EB8NM[0] != 0) {
        D_80098BEC[0] = 0x38;
        D_80098BED[0] = 0x36;
        D_80098BEE[0] = 0x40;
        if (RandomScaledGet(3) < 0) {
            t = -RandomScaledGet(3);
        } else {
            t = RandomScaledGet(3);
        }
        switch (t) {
        case 0:
            msg = (s32)D_8008D21C;
            break;
        case 1:
            msg = (s32)D_8008D228;
            break;
        case 2:
            msg = (s32)D_8008D234;
            break;
        default:
            return;
        }
        func_8003F060(msg);
    } else {
        func_8003F060(0x3E);
    }
}

extern void func_8003F284(void);
extern void func_8003F564(s8, s8);
extern void func_8003FDE8(s8, s32, s32);

void func_8004195C(void) {
    SsStart2();
    func_8003F284();
    func_8003F564(0, 0);
    func_8003FDE8(0, 0, 0);
    VSync(0);
    VSync(0);
    VSync(0);
    func_8003F564(1, 0xC);
    func_8003FDE8(1, 0, 0);
    func_8003F564(2, 0xD);
    func_8003FDE8(2, 0, 0);
    func_8003F564(3, 0xE);
    func_8003FDE8(3, 0, 0);
    func_8003F564(4, 0xF);
    func_8003FDE8(4, 0, 0);
}

extern u8 D_800A2F9D;
extern void func_8003FDE8(s8, s32, s32);
extern void SoundShutdown(void);
extern void SsSetMute(s32);

void func_80041A28(void) {
    s32 i;

    i = 0;
    do {
        func_8003FDE8((s8)i, 0, 0);
        i++;
    } while (i < 5);
    func_8003F2AC(0, 0);
    SoundSetSequenceVolume(0, 0);
    func_8003F23C();
    func_8003FA0C();
    SsSetMVol(0, 0);
    VSync(0);
    VSync(0);
    SoundShutdown();
    if (D_800A2F9D == 0) {
        SsSetMute(0);
    }
}

void func_80041AF0();
