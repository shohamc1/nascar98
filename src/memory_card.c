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
extern u8 D_800A361C[];
extern u8 D_800A305BSmall;
extern u8 D_800A36E1[];
extern u8 D_800A3808a[] asm("D_800A3808.NON_MATCHING");
extern u8 D_800A3808b[] asm("D_800A3814.NON_MATCHING");
extern u8 D_800A3808c[] asm("D_800A380C.NON_MATCHING");
extern u8 D_800A3808d[] asm("D_800A3810.NON_MATCHING");
extern u8 D_800A3968a[] asm("D_800A3968.NON_MATCHING");
extern u8 D_800A3950nm asm("D_800A3950.NON_MATCHING");
extern u8 D_800A3059[];
extern u8 D_800A39E4Small;
extern u8 D_800A3704;
extern u8 D_800A3059[];
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
extern s32 CardDisableEvents(void);
void func_800598C4(void) {
    CardTestEvents();
    func_8005A414();
    CardDisableEvents();
    ChangeClearPAD(0);
}

extern u32 D_800A3824, D_800A3828, D_800A382C, D_800A3834;
extern s32 D_800A38C8, D_800A38CC, D_800A38D0, D_800A38D4;
extern s32 DisableEvent(s32);
s32 CardDisableEvents(void) {
    s32 enabled;
    s16 result;

    EnterCriticalSection();
    enabled = DisableEvent(D_800A3824);
    enabled = enabled != 0;
    result = enabled;
    if (DisableEvent(D_800A3828) == 0) {
        result = 0;
    }
    if (DisableEvent(D_800A382C) == 0) {
        result = 0;
    }
    if (DisableEvent(D_800A3834) == 0) {
        result = 0;
    }
    if (DisableEvent(D_800A38C8) == 0) {
        result = 0;
    }
    if (DisableEvent(D_800A38CC) == 0) {
        result = 0;
    }
    if (DisableEvent(D_800A38D0) == 0) {
        result = 0;
    }
    if (DisableEvent(D_800A38D4) == 0) {
        result = 0;
    }
    ExitCriticalSection();
    return result;
}

extern s32 CardEnableEvents(void);
extern void CardTestEvents(void), func_8005A414(void);
extern s32 func_8005A294(void);
void func_800599E4(void) {
    CardEnableEvents();
    CardTestEvents();
    func_8005A414();
}

/* result is s16: the narrowing keeps the first compare in v0 and copies
 * it to s0 in the second jal delay slot (found by the permuter). */
extern u32 D_800A3824, D_800A3828, D_800A382C, D_800A3834;
extern s32 D_800A38C8, D_800A38CC, D_800A38D0, D_800A38D4;
s32 CardEnableEvents(void) {
    s32 enabled;
    s16 result;

    EnterCriticalSection();
    enabled = EnableEvent(D_800A3824);
    enabled = enabled != 0;
    result = enabled;
    if (EnableEvent(D_800A3828) == 0) {
        result = 0;
    }
    if (EnableEvent(D_800A382C) == 0) {
        result = 0;
    }
    if (EnableEvent(D_800A3834) == 0) {
        result = 0;
    }
    if (EnableEvent(D_800A38C8) == 0) {
        result = 0;
    }
    if (EnableEvent(D_800A38CC) == 0) {
        result = 0;
    }
    if (EnableEvent(D_800A38D0) == 0) {
        result = 0;
    }
    if (EnableEvent(D_800A38D4) == 0) {
        result = 0;
    }
    ExitCriticalSection();
    return result;
}

extern s32 func_8005A294(void);
extern void func_8005A414(void);
s32 CardCheckStatus(s32 arg0, u8 arg1) {
    s32 channel;
    u32 retries;
    s32 status;

    channel = ((arg0 & 0xFF) != 0) * 0x10;
    retries = 0;
again:
    _card_info(channel);
    status = func_8005A294();
    switch (status) {
    case 0:
        return 0;
    case 3:
        func_8005A414();
        _card_clear(channel);
        status = CardWaitForEvent();
        if (arg1 != 0) {
            return 3;
        }
        if (status == 0) {
            return 3;
        }
    }
    retries++;
    if ((retries & 0xFF) < 8) {
        goto again;
    }
    return status & 0xFF;
}

s32 CardFindFirstFile(char *path, struct DIRENTRY *entry) {
    return firstfile(path, entry) == entry;
}

extern char gMemoryCardDevice2[], gMemoryCardDevice1[];
s32 CardFormat(s32 second) {
    if (!(second & 0xFF))
        return format(gMemoryCardDevice1) & 0xFF;
    else
        return format(gMemoryCardDevice2) & 0xFF;
}

void func_80059C2C(void) {
    extern u32 D_800A3824, D_800A3828, D_800A382C, D_800A3834;
    extern s32 D_800A38C8, D_800A38CC, D_800A38D0, D_800A38D4;
    s32 event;

    EnterCriticalSection();
    D_800A3824 = OpenEvent(0xF4000001, 4, 0x2000, 0);
    event = OpenEvent(0xF4000001, 0x8000, 0x2000, 0);
    D_800A3828 = event;
    if (event == -1) {
        event = 0;
    }
    event = OpenEvent(0xF4000001, 0x100, 0x2000, 0);
    D_800A382C = event;
    if (event == -1) {
        event = 0;
    }
    event = OpenEvent(0xF4000001, 0x2000, 0x2000, 0);
    D_800A3834 = event;
    if (event == -1) {
        event = 0;
    }
    event = OpenEvent(0xF0000011, 4, 0x2000, 0);
    D_800A38C8 = event;
    if (event == -1) {
        event = 0;
    }
    event = OpenEvent(0xF0000011, 0x8000, 0x2000, 0);
    D_800A38CC = event;
    if (event == -1) {
        event = 0;
    }
    event = OpenEvent(0xF0000011, 0x100, 0x2000, 0);
    D_800A38D0 = event;
    if (event == -1) {
        event = 0;
    }
    D_800A38D4 = OpenEvent(0xF0000011, 0x2000, 0x2000, 0);
    ExitCriticalSection();
}

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

void func_80059E0C(void) {
    extern void StopCARD(void);

    StopCARD();
    EnterCriticalSection();
    DisableEvent(D_800A3824);
    DisableEvent(D_800A3828);
    DisableEvent(D_800A382C);
    DisableEvent(D_800A3834);
    DisableEvent(D_800A38C8);
    DisableEvent(D_800A38CC);
    DisableEvent(D_800A38D0);
    DisableEvent(D_800A38D4);
    ExitCriticalSection();
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

extern s32 func_8005A294(void);
extern void CardTestEvents(void);
extern s32 CardWaitForEvent(void);
extern void func_8005A414(void);
s32 func_80059F0C(s32 arg0) {
    s32 retries = 0;
    s32 channel = ((arg0 & 0xFF) != 0) * 0x10;
    s32 status;
    do {
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
            if (status == 0) {
                break;
            }
        }
        retries++;
        if (status == 0) {
            break;
        }
    } while ((retries & 0xFF) < 8U);
    retries = status;
    return retries & 0xFF;
}

s32 CardOpenFile(char *path, s32 flags) {
    if (flags == 0x200) {
        flags = 0x10200;
    }
    return open(path, flags);
}

extern void func_8005A414(void);
extern void _new_card(void);
extern void _card_read(s32, s32, s32);
extern s32 CardWaitForEvent(void);
s32 func_8005A000(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 buf) {
    s32 channel;
    s32 sector;
    s32 offset;
    s32 retries;
    s32 end;
    s32 limit;
    channel = ((arg3 & 0xFF) != 0) * 0x10;
    arg2 = arg2 & 0xFF;
    if (buf == 0)
        goto success;
    retries = offset = 0;
    sector = (arg1 & 0xFF) + *(s32 *)(arg0 + 0x20);
    limit = (sector & 0xFFFF) + arg2;
    if ((sector & 0xFFFF) >= limit)
        goto success;
    end = limit;
    do {
        func_8005A414();
        _new_card();
        _card_read(channel, sector & 0xFFFF, buf + offset);
        if (CardWaitForEvent() == 0) {
            sector += 1;
            offset += 0x80;
            retries = 0;
        } else if ((u32)(retries & 0xFF) < 0xBU) {
            retries += 1;
        } else {
            return 0;
        }
    } while ((sector & 0xFFFF) < end);
success:
    return 1;
}

extern void _new_card(void);
extern void _card_write(s32, s32, s32);
s32 func_8005A0F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 buf) {
    s32 sector;
    u32 retries;
    s32 offset;
    s32 end;
    s32 limit;
    s32 channel;

    offset = 0;
    retries = 0;
    sector = (arg1 & 0xFF) + *(s32 *)(arg0 + 0x20);
    channel = ((arg3 & 0xFF) != 0) * 0x10;
    limit = (sector & 0xFFFF) + (arg2 & 0xFF);
    if ((sector & 0xFFFF) < limit) {
        end = limit;
        do {
            func_8005A414();
            _new_card();
            _card_write(channel, sector & 0xFFFF, buf + offset);
            if (CardWaitForEvent() == 0) {
                sector += 1;
                offset += 0x80;
                retries = 0;
            } else if ((retries & 0xFF) < 0xB) {
                retries += 1;
            } else {
                return 0;
            }
        } while ((sector & 0xFFFF) < end);
    }
    return 1;
}

/* gcc rounds a DIRENTRY[16] frame up by 0x20 but leaves [15] alone;
 * retail's locals are 15*0x28 + 8. The call-per-arm with the ==0 branch
 * sense reproduces the bnez/per-arm-a0/single-jal merge, and i=0 before
 * the blez lets total=0 fill its delay slot. */
extern char gMemoryCardDevice2[], gMemoryCardDevice1[];
s32 CardCountOtherFileBlocks(s32 arg0, char *name) {
    s32 zero;
    struct DIRENTRY entries[15];
    s32 count;
    u32 total;
    s32 i;
    struct DIRENTRY *entry;

    if ((arg0 & 0xFF) == 0) {
        count = CardScanDirectory(gMemoryCardDevice1, entries);
    } else {
        count = CardScanDirectory(gMemoryCardDevice2, entries);
    }
    i = 0;
    zero = 0;
    total = zero;
    if (count > zero) {
        entry = entries;
        do {
            if (strcmp(entry->name, name) != 0) {
                total += entry->size;
            }
            i++;
            entry++;
        } while (i < count);
    }
    return (total >> 13) & 0xFF;
}

s32 func_8005A294(void) {
    u32 i;

    i = 0;
    do {
        i++;
        if (TestEvent(D_800A3824) == 1) {
            return 0;
        }
        if (TestEvent(D_800A3828) == 1) {
            return 1;
        }
        if (TestEvent(D_800A382C) == 1) {
            return 2;
        }
        if (TestEvent(D_800A3834) == 1) {
            return 3;
        }
    } while (i < 0x40000);
    return 1;
}

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

extern char gMemoryCardWildcard[];

s32 CardScanDirectory(char *path, struct DIRENTRY *entry) {
    char buffer[128];
    struct DIRENTRY *cursor;
    s32 count;

    strcpy(buffer, path);
    strcat(buffer, gMemoryCardWildcard);
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

extern s32 D_800B1EBC[];
extern s32 D_800A39E8;
extern u16 D_800A3874;
extern s32 D_800A3768;
extern void func_8005A818(u8, u8, u8);
void func_8005A4E0(void) {
    u8 i;

    for (i = 0; i < 5; i++) {
        D_800B1EBC[i] = 0;
    }
    D_800A3874 = 0;
    D_800A3768 = D_800A39E8;
    func_8005A818(0xFF, 0x80, 0x40);
}

void func_8005A544(u8 arg0, u8 arg1) {
    typedef struct {
        s16 x;
        s16 y;
        u8 w;
        u8 h;
        u8 ax;
        u8 pad;
        u8 ay;
    } Dim;
    typedef struct {
        u8 count;
        u8 pad;
        u16 x;
        u16 y;
        Dim *table;
    } Entry;
    typedef struct {
        u8 b[0x28];
    } Prim28;
    extern Entry D_80099FE4_g1b[] asm("D_80099FE4");
    extern Prim28 *D_800A3768_g1b asm("D_800A3768");
    Entry *entry;
    Dim *table;
    Dim *dim;
    s32 *slot;
    s32 *base;
    u32 idx;
    u8 *prim;
    u8 *p;
    u16 i;
    Prim28 *old;
    u8 n;
    u16 count;
    u32 total;
    u32 bound;
    u16 w;

    entry = &D_80099FE4_g1b[arg1];
    n = entry->count;
    idx = arg0;
    old = D_800A3768_g1b;
    base = D_800B1EBC;
    slot = idx + base;
    do {
    } while (0);
    w = D_800A3874;
    *slot = (s32)old;
    count = n;
    prim = *(u8 *volatile *)slot;
    D_800A3874 = w + count;
    D_800A3768_g1b = old + n;
    table = (Dim *)entry->table;
    total = count;
    if (total != 0) {
        i = 0;
        bound = total;
        do {
            p = prim + 0x25;
            *(u16 *)(p - 0x17) = GetClut(entry->x, entry->y);
            dim = (Dim *)(i * 10 + (s32)table);
            *(u16 *)(p - 0xF) = GetTPage(0, 0, dim->x, dim->y);
            p[-0x19] = dim->w;
            p[-0x18] = dim->h;
            p[-0x11] = dim->w + dim->ax;
            p[-0x10] = dim->h;
            p[-0x9] = dim->w;
            p[-0x8] = dim->h + dim->ay;
            p[-0x1] = dim->w + dim->ax;
            p[0] = dim->h + dim->ay;
            SetSemiTrans(prim, 1);
            prim += 0x28;
            i++;
        } while (i < bound);
    }
}

void func_8005A6EC(u8 id, s32 arg1, void *dest) {
    typedef struct {
        u32 w[4];
    } W16;
    typedef struct {
        u32 w[2];
    } W8;
    extern s32 D_800B1EBCx[] asm("D_800B1EBC");
    extern u8 *D_800A35A0p asm("D_800A35A0");
    extern u8 *D_800A3750p asm("D_800A3750");
    u8 *src;
    volatile u8 *d;
    u8 *s;
    u8 *e;
    volatile u32 pad[2];
    s32 count;
    s32 i;
    s32 n;
    volatile u8 *cursor;

    func_8005A7B8(id & 0xFF, arg1 & 0xFF);
    count = *D_800A35A0p;
    src = D_800A3750p;
    cursor = (volatile u8 *)dest;
    i = 0;
    if (count > 0) {
        n = count;
        do {
            d = cursor;
            s = src;
            e = s + 0x20;
            do {
                *(W16 *)d = *(W16 *)s;
                s += 0x10;
                d += 0x10;
            } while (s != e);
            *(W8 *)d = *(W8 *)s;
            src += 0x28;
            cursor += 0x28;
            i++;
        } while (i < n);
    }
    D_800B1EBCx[id & 0xFF] = (s32)dest;
}

extern s32 D_800A35A0;
extern u8 D_800A3534;
extern s32 D_800A3750;
extern s32 D_800A35AC;
extern s32 D_800B1EBC[];
extern s32 D_80099FE4[][3];
void func_8005A7B8(u8 arg0, u8 arg1) {
    s32 *entry;
    s32 word;

    word = D_800B1EBC[arg0];
    entry = &D_80099FE4[arg1][0];
    D_800A35A0 = (s32)entry;
    D_800A3534 = arg1;
    D_800A3750 = word;
    D_800A35AC = entry[2];
}

extern u8 D_800A37C8, D_800A37A8, D_800A378C;
void func_8005A804(u8 a, u8 b, u8 c) {
    D_800A37C8 = a;
    D_800A37A8 = b;
    D_800A378C = c;
}

extern u8 D_800A3618;
extern u8 D_800A3624;
extern u8 D_800A364C;

void func_8005A818(u8 first, u8 second, u8 third) {
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

extern u8 D_800A3534;
extern s32 D_800A35AC;
s16 func_8005A84C(void) {
    s32 res;
    if (D_800A3534 == 2) {
        res = *(s16 *)(D_800A35AC + 8) * 3;
        if (res < 0)
            res += 3;
        return (s16)((res << 0xE) >> 0x10);
    } else if (D_800A3534 == 4) {
        return (s16)((*(s16 *)(D_800A35AC + 8) * 9 / 10 << 0x10) >> 0x10);
    }
    return *(s16 *)(D_800A35AC + 8);
}

s16 func_8005A8E0(s32 text) {
    s32 total;
    s32 idx;
    s32 glyphCount;
    s32 limit;
    u8 ch;
    s32 i;

    glyphCount = *(u16 *)D_800A35A0;
    i = 0;
    total = 0;
    if (*(u8 *)text != 0) {
        limit = glyphCount + 0x20;
        do {
            ch = ((u8 *)text)[i];
            idx = 0;
            if (ch >= 0x20) {
                if (ch < limit) {
                    idx = ch - 0x20;
                }
            }
            if (D_800A3534 == 2) {
                total += *(s16 *)(D_800A35AC + idx * 10 + 6) * 3 / 4;
            } else if (D_800A3534 == 4) {
                total += *(s16 *)(D_800A35AC + idx * 10 + 6) * 9 / 10;
            } else {
                total += *(u16 *)(D_800A35AC + idx * 10 + 6);
            }
            if (D_800A3534 < 2) {
                total -= 1;
            }
            i++;
        } while (((u8 *)text)[i] != 0);
    }
    return total;
}

INCLUDE_ASM("asm/nonmatchings/memory_card", func_8005A9F4);

/* Sums the glyph widths of the first count characters of str. The glyph
   table (D_800A35AC) holds 10-byte records with the width at offset 6;
   D_800A3534 picks the scale (2 = 3/4, 4 = 9/10) and subtracts 1 per
   character when below 2. */
s16 func_8005AEC8(u8 count, u8 *str) {
    s32 total;
    s32 i;
    s32 idx;
    s32 glyphCount;
    s32 limit;
    u8 ch;

    glyphCount = *(u16 *)D_800A35A0;
    i = 0;
    total = 0;
    if (*str != 0) {
        limit = glyphCount + 0x20;
        while (str[i] != 0 && i < count) {
            ch = str[i];
            idx = 0;
            if (ch >= 0x20) {
                if (ch < limit) {
                    idx = ch - 0x20;
                }
            }
            if (D_800A3534 == 2) {
                total += *(s16 *)(D_800A35AC + idx * 10 + 6) * 3 / 4;
            } else if (D_800A3534 == 4) {
                total += *(s16 *)(D_800A35AC + idx * 10 + 6) * 9 / 10;
            } else {
                total += *(u16 *)(D_800A35AC + idx * 10 + 6);
            }
            if (D_800A3534 < 2) {
                total -= 1;
            }
            i++;
        }
    }
    return total;
}

s16 func_8005AFF0(s8 arg0) {
    s32 index;
    s32 entry;
    s32 scaled;
    short value;
    s32 product;
    s32 quotient;
    entry = *((u16 *)D_800A35A0);
    index = 0;
    if ((arg0 >= 0x20) && (arg0 < (entry + 0x20))) {
        index = arg0 - 0x20;
    }
    if (D_800A3534 == 2) {
        scaled = (*((s16 *)((D_800A35AC + (index * 0xA)) + 6))) * 3;
        value = ((u32)scaled) >> 2;
        if (scaled < 0) {
            scaled += 3;
            value = ((u32)scaled) >> 2;
        }
    } else if (D_800A3534 == 4) {
        value = *((s16 *)((D_800A35AC + (index * 0xA)) + 6));
        product = value * 9;
        value = product / 10;
    } else {
        value = *((u16 *)((D_800A35AC + (index * 0xA)) + 6));
    }
    if (D_800A3534 < 2U) {
        value -= 1;
    }
    return (s16)value;
}

extern s16 func_8005A8E0(s32);
s32 func_8005B0E4(s16 arg0, s32 arg1) {
    s32 limit;

    limit = func_8005A8E0(arg1);
    if (arg0 < limit) {
        return 0;
    }
    return (arg0 - limit) >> 1;
}

#ifdef NON_MATCHING
s32 func_8005B138(u8 *str) {
    s32 count;
    u8 c;

    count = 0;
    c = *str;
    while (c != 0) {
        if (c == 0xA) {
            count++;
        }
        str++;
        c = *str;
    }
    return count + 1;
}
#else
s32 func_8005B138(u8 *str) {
    s32 count;

    count = 0;
    if (*str != 0) {
        do {
            if (*str == 0xA) {
                count++;
            }
            str++;
        } while (*str != 0);
    }
    return count + 1;
}
#endif

void func_8005B17C(u8 *dst, u32 idx, u16 dx, u16 dy, u16 ax, u16 ay) {
    struct Tab14 {
        u16 f0;
        u16 f2;
        u16 f4;
        u16 f6;
        u8 f8;
        u8 f9;
        u8 fA;
        u8 fB;
        u16 fC;
    };
    extern struct Tab14 D_8009AEA0[];
    struct Tab14 *entry;

    entry = &D_8009AEA0[idx & 0xFF];
    *(u16 *)(dst + 0xE) = GetClut(entry->f4, entry->f6);
    *(u16 *)(dst + 0x16) = GetTPage(entry->fC, 3, entry->f0, entry->f2);
    dst[0xC] = entry->f8 + dx;
    dst[0xD] = entry->fA + dy;
    dst[0x14] = entry->f8 + dx + ax;
    dst[0x15] = entry->fA + dy;
    dst[0x1C] = entry->f8 + dx;
    dst[0x1D] = entry->fA + dy + ay;
    dst[0x24] = entry->f8 + dx + ax;
    dst[0x25] = entry->fA + dy + ay;
}

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

struct UnkTextObj *func_8005B314(x, y, width, height, poly, red, green, blue,
                                 semiTrans, texture)
s32 x;
s32 y;
s32 width;
s32 height;
s32 poly;
u8 red;
u8 green;
u8 blue;
u8 semiTrans;
u8 texture;
{
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
    *(s16 *)(object + 0x0) = 2;
    *(s16 *)(object + 0x6) = x;
    *(s16 *)(object + 0xA) = x;
    *(s16 *)(object + 0x8) = y;
    *(s16 *)(object + 0xC) = y;
    *(s16 *)(object + 0xE) = 0;
    *(s16 *)(object + 0x10) = 0;
    *(s16 *)(object + 0x16) = width;
    *(s16 *)(object + 0x18) = height;
    object[2] = red;
    object[3] = green;
    object[4] = blue;
    if (poly == 0) {
        poly = (s32)func_80057D50(texture);
    }
    *(u8 **)(object + 0x20) = (u8 *)poly;
    SetPolyF4((u8 *)poly);
    SetSemiTrans((void *)poly, semiTrans);
    ((u8 *)poly)[4] = red;
    ((u8 *)poly)[5] = green;
    ((u8 *)poly)[6] = blue;
    *(s16 *)((u8 *)poly + 0x8) = x;
    *(s16 *)((u8 *)poly + 0xA) = y;
    *(s16 *)((u8 *)poly + 0xC) = x + width;
    *(s16 *)((u8 *)poly + 0xE) = y;
    *(s16 *)((u8 *)poly + 0x10) = x;
    *(s16 *)((u8 *)poly + 0x12) = y + height;
    *(s16 *)((u8 *)poly + 0x14) = x + width;
    *(s16 *)((u8 *)poly + 0x16) = y + height;
    return (struct UnkTextObj *)object;
}

extern void SetPolyF3(POLY_F3 *);
u8 *func_8005B474(x, y, width, height, poly, red, green, blue, semiTrans,
                  texture, mode)
s32 x;
s32 y;
s32 width;
s32 height;
s32 poly;
u8 red;
u8 green;
u8 blue;
u8 semiTrans;
u8 texture;
u8 mode;
{
    u8 index;
    u8 *fresh;
    u8 *object;

    index = D_800A35EC++;
    fresh = D_800A3678 + index * 36;
    asm("" : "=r"(object) : "0"(fresh));
    *(s16 *)(fresh + 0x12) = 0;
    *(s16 *)(fresh + 0x14) = 0;
    *(s32 *)(fresh + 0x1C) = 0;
    fresh[4] = 0;
    fresh[3] = 0;
    fresh[2] = 0;
    *(s16 *)(fresh + 0x1A) = 0;
    *(s16 *)(object + 0x0) = mode != 0 ? 7 : 8;
    *(s16 *)(object + 0x6) = x;
    *(s16 *)(object + 0xA) = x;
    *(s16 *)(object + 0x8) = y;
    *(s16 *)(object + 0xC) = y;
    *(s16 *)(object + 0xE) = 0;
    *(s16 *)(object + 0x10) = 0;
    *(s16 *)(object + 0x16) = width;
    *(s16 *)(object + 0x18) = height;
    object[2] = red;
    object[3] = green;
    object[4] = blue;
    if (poly == 0) {
        poly = (s32)func_80057D50(texture);
    }
    *(u8 **)(object + 0x20) = (u8 *)poly;
    SetPolyF3((POLY_F3 *)poly);
    SetSemiTrans((void *)poly, semiTrans);
    ((u8 *)poly)[4] = red;
    ((u8 *)poly)[5] = green;
    ((u8 *)poly)[6] = blue;
    return object;
}

u8 *func_8005B598(s32 left, s32 top, s32 right, s32 bottom, s32 depth,
                  u8 texture, u8 semiTrans) {
    u8 index;
    u8 *object;
    POLY_FT4 *poly;
    index = D_800A35EC++;
    object = D_800A3678 + index * 36;
    *(s16 *)(object + 0x12) = 0;
    *(s16 *)(object + 0x14) = 0;
    *(s32 *)(object + 0x1C) = 0;
    object[4] = 0;
    object[3] = 0;
    object[2] = 0;
    *(s16 *)(object + 0x1A) = 0;
    *(s16 *)(object + 0x0) = 1;
    *(s16 *)(object + 0xA) = left;
    *(s16 *)(object + 0x6) = left;
    *(s16 *)(object + 0xC) = top;
    *(s16 *)(object + 0x8) = top;
    *(s16 *)(object + 0x16) = right;
    *(s16 *)(object + 0x18) = bottom;
    *(s16 *)(object + 0xE) = 0;
    *(s16 *)(object + 0x10) = 0;
    poly = func_80057CCC(texture);
    SetPolyFT4(poly);
    SetShadeTex(poly, 0);
    ((u8 *)poly)[4] = 0x80;
    ((u8 *)poly)[5] = 0x80;
    ((u8 *)poly)[6] = 0x80;
    SetSemiTrans(poly, semiTrans);
    *(POLY_FT4 **)(object + 0x20) = poly;
    *(s16 *)(object + 0x1A) = depth;
    return object;
}

void func_8005B688(u8 *first, u8 friction) {
    u8 *object;
    s16 sum;

    object = first;
    if (object != 0) {
        do {
            if (*(s16 *)(object + 0xE) != 0) {
                sum = *(u16 *)(object + 0x6) + *(s16 *)(object + 0xE);
                *(s16 *)(object + 0x6) = sum;
                if ((*(s16 *)(object + 0xE) < 0 &&
                     sum < *(s16 *)(object + 0xA)) ||
                    (*(s16 *)(object + 0xE) > 0 &&
                     *(s16 *)(object + 0xA) < sum)) {
                    *(s16 *)(object + 0xE) = 0;
                    *(u16 *)(object + 0x6) = *(u16 *)(object + 0xA);
                } else if (friction != 0) {
                    *(u16 *)(object + 0xE) = *(u16 *)(object + 0xE) +
                                             (s16) * (u16 *)(object + 0xE) / 2;
                }
            }
            if (*(s16 *)(object + 0x10) != 0) {
                sum = *(u16 *)(object + 0x8) + *(s16 *)(object + 0x10);
                *(s16 *)(object + 0x8) = sum;
                if ((*(s16 *)(object + 0x10) < 0 &&
                     sum < *(s16 *)(object + 0xC)) ||
                    (*(s16 *)(object + 0x10) > 0 &&
                     *(s16 *)(object + 0xC) < sum)) {
                    *(s16 *)(object + 0x10) = 0;
                    *(u16 *)(object + 0x8) = *(u16 *)(object + 0xC);
                } else if (friction != 0) {
                    *(u16 *)(object + 0x10) =
                        *(u16 *)(object + 0x10) +
                        (s16) * (u16 *)(object + 0x10) / 2;
                }
            }
            object = *(u8 **)(object + 0x1C);
        } while (object != 0);
    }
}

extern s32 D_800A39C8[];
void func_8005B7DC(u8 *object, s32 index, u8 semiTrans) {
    u8 *poly;

    poly = *(u8 **)(object + 0x20);
    *(u16 *)(poly + 0x8) = *(u16 *)(object + 0x6);
    *(u16 *)(poly + 0xA) = *(u16 *)(object + 0x8);
    *(u16 *)(poly + 0xC) = *(u16 *)(object + 0x6) + *(u16 *)(object + 0x16);
    *(u16 *)(poly + 0xE) = *(u16 *)(object + 0x8);
    *(u16 *)(poly + 0x10) = *(u16 *)(object + 0x6);
    *(u16 *)(poly + 0x12) = *(u16 *)(object + 0x8) + *(u16 *)(object + 0x18);
    *(u16 *)(poly + 0x14) = *(u16 *)(object + 0x6) + *(u16 *)(object + 0x16);
    *(u16 *)(poly + 0x16) = *(u16 *)(object + 0x8) + *(u16 *)(object + 0x18);
    if (semiTrans != 0xFF) {
        SetSemiTrans(poly, semiTrans);
    }
    AddPrim(D_800A39C8[0] + index * 4, poly);
}

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

void func_8005B8B8(u8 *object, s32 arg1) {
    u8 *src;
    u8 *poly;
    s32 semiTrans;
    s32 half;
    u8 scratch[0x40];

    if (object == 0) {
        return;
    }
    semiTrans = arg1 & 0xFF;
    for (; object != 0; object = *(u8 **)(object + 0x1C)) {
        if (*(s16 *)(object + 0x1A) >= 0) {
            if (D_800A39E4Absolute[0] != 0xD || *(s8 *)(object + 5) != 0) {
                switch (*(u16 *)(object)) {
                case 1: {
                    u8 *prim;
                    u8 *src;
                    u8 *dst;
                    u8 *end;

                    prim = func_80057CCC(0);
                    src = *(u8 **)(object + 0x20);
                    dst = prim;
                    end = src + 0x20;
                    do {
                        *(UnkQuad *)dst = *(UnkQuad *)src;
                        src += 0x10;
                        dst += 0x10;
                    } while (src != end);
                    *(UnkPrim8 *)dst = *(UnkPrim8 *)src;
                    if (D_800A39E4Absolute[0] == 0xD) {
                        *(u16 *)(prim + 0x8) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x12);
                        *(u16 *)(prim + 0xA) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x14);
                        *(u16 *)(prim + 0x10) = *(u16 *)(object + 0x6) +
                                                *(u16 *)(object + 0x12) +
                                                *(u16 *)(object + 0x16);
                        *(u16 *)(prim + 0x12) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x14);
                        *(u16 *)(prim + 0x18) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x12);
                        *(u16 *)(prim + 0x1A) = *(u16 *)(object + 0x8) +
                                                *(u16 *)(object + 0x14) +
                                                *(u16 *)(object + 0x18);
                        *(u16 *)(prim + 0x20) = *(u16 *)(object + 0x6) +
                                                *(u16 *)(object + 0x12) +
                                                *(u16 *)(object + 0x16);
                        *(u16 *)(prim + 0x22) = *(u16 *)(object + 0x8) +
                                                *(u16 *)(object + 0x14) +
                                                *(u16 *)(object + 0x18);
                    } else {
                        *(u16 *)(prim + 0x8) = *(u16 *)(object + 0x6);
                        *(u16 *)(prim + 0xA) = *(u16 *)(object + 0x8);
                        *(u16 *)(prim + 0x10) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x16);
                        *(u16 *)(prim + 0x12) = *(u16 *)(object + 0x8);
                        *(u16 *)(prim + 0x18) = *(u16 *)(object + 0x6);
                        *(u16 *)(prim + 0x1A) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x18);
                        *(u16 *)(prim + 0x20) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x16);
                        *(u16 *)(prim + 0x22) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x18);
                    }
                    AddPrim(D_800A39C8[0] + *(s16 *)(object + 0x1A) * 4, prim);
                    break;
                }
                case 2: {
                    u8 *src2;

                    poly = func_80057D50(0);
                    src2 = *(u8 **)(object + 0x20);
                    *(UnkPrim18 *)poly = *(UnkPrim18 *)src2;
                    if (D_800A39E4Absolute[0] == 0xD) {
                        if (*(s16 *)(object + 0x16) == 0) {
                            break;
                        }
                        if (*(s16 *)(object + 0x18) == 0) {
                            break;
                        }
                        *(u16 *)(poly + 0x8) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x12);
                        *(u16 *)(poly + 0xA) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x14);
                        *(u16 *)(poly + 0xC) = *(u16 *)(object + 0x6) +
                                               *(u16 *)(object + 0x12) +
                                               *(u16 *)(object + 0x16);
                        *(u16 *)(poly + 0xE) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x14);
                        *(u16 *)(poly + 0x10) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x12);
                        *(u16 *)(poly + 0x12) = *(u16 *)(object + 0x8) +
                                                *(u16 *)(object + 0x14) +
                                                *(u16 *)(object + 0x18);
                        *(u16 *)(poly + 0x14) = *(u16 *)(object + 0x6) +
                                                *(u16 *)(object + 0x12) +
                                                *(u16 *)(object + 0x16);
                        *(u16 *)(poly + 0x16) = *(u16 *)(object + 0x8) +
                                                *(u16 *)(object + 0x14) +
                                                *(u16 *)(object + 0x18);
                    } else {
                        *(u16 *)(poly + 0x8) = *(u16 *)(object + 0x6);
                        *(u16 *)(poly + 0xA) = *(u16 *)(object + 0x8);
                        *(u16 *)(poly + 0xC) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x16);
                        *(u16 *)(poly + 0xE) = *(u16 *)(object + 0x8);
                        *(u16 *)(poly + 0x10) = *(u16 *)(object + 0x6);
                        *(u16 *)(poly + 0x12) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x18);
                        *(u16 *)(poly + 0x14) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x16);
                        *(u16 *)(poly + 0x16) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x18);
                    }
                    if (semiTrans != 0xFF) {
                        SetSemiTrans(poly, semiTrans);
                    }
                    AddPrim(D_800A39C8[0] + *(s16 *)(object + 0x1A) * 4, poly);
                    break;
                }
                case 7:
                case 8:
                    poly = func_80057D50(0);
                    src = *(u8 **)(object + 0x20);
                    *(UnkPrim14 *)poly = *(UnkPrim14 *)src;
                    if (*(u16 *)(object) == 7) {
                        half = *(s16 *)(object + 0x16) / 2;
                        if (*(s16 *)(object + 0x18) < 0) {
                            *(u16 *)(poly + 0x8) = *(u16 *)(object + 0x6) +
                                                   *(u16 *)(object + 0x12);
                            *(u16 *)(poly + 0xA) = *(u16 *)(object + 0x8) +
                                                   *(u16 *)(object + 0x14);
                            *(u16 *)(poly + 0xC) = *(u16 *)(object + 0x6) +
                                                   *(u16 *)(object + 0x12) -
                                                   half;
                            *(u16 *)(poly + 0xE) = *(u16 *)(object + 0x8) +
                                                   *(u16 *)(object + 0x14) +
                                                   *(u16 *)(object + 0x18);
                            *(u16 *)(poly + 0x10) = *(u16 *)(object + 0x6) +
                                                    *(u16 *)(object + 0x12) +
                                                    half;
                            *(u16 *)(poly + 0x12) = *(u16 *)(object + 0x8) +
                                                    *(u16 *)(object + 0x14) +
                                                    *(u16 *)(object + 0x18);
                        } else {
                            *(u16 *)(poly + 0x8) = *(u16 *)(object + 0x6) +
                                                   *(u16 *)(object + 0x12);
                            *(u16 *)(poly + 0xA) = *(u16 *)(object + 0x8) +
                                                   *(u16 *)(object + 0x14);
                            *(u16 *)(poly + 0xC) = *(u16 *)(object + 0x6) +
                                                   *(u16 *)(object + 0x12) +
                                                   half;
                            *(u16 *)(poly + 0xE) = *(u16 *)(object + 0x8) +
                                                   *(u16 *)(object + 0x14) +
                                                   *(u16 *)(object + 0x18);
                            *(u16 *)(poly + 0x10) = *(u16 *)(object + 0x6) +
                                                    *(u16 *)(object + 0x12) -
                                                    half;
                            *(u16 *)(poly + 0x12) = *(u16 *)(object + 0x8) +
                                                    *(u16 *)(object + 0x14) +
                                                    *(u16 *)(object + 0x18);
                        }
                    } else {
                        half = *(s16 *)(object + 0x18) / 2;
                        *(u16 *)(poly + 0x8) =
                            *(u16 *)(object + 0x6) + *(u16 *)(object + 0x12);
                        *(u16 *)(poly + 0xA) =
                            *(u16 *)(object + 0x8) + *(u16 *)(object + 0x14);
                        *(u16 *)(poly + 0xC) = *(u16 *)(object + 0x6) +
                                               *(u16 *)(object + 0x12) +
                                               *(u16 *)(object + 0x16);
                        *(u16 *)(poly + 0xE) = *(u16 *)(object + 0x8) +
                                               *(u16 *)(object + 0x14) + half;
                        *(u16 *)(poly + 0x10) = *(u16 *)(object + 0x6) +
                                                *(u16 *)(object + 0x12) +
                                                *(u16 *)(object + 0x16);
                        *(u16 *)(poly + 0x12) = *(u16 *)(object + 0x8) +
                                                *(u16 *)(object + 0x14) - half;
                    }
                    if (semiTrans != 0xFF) {
                        SetSemiTrans(poly, semiTrans);
                    }
                    AddPrim(D_800A39C8[0] + *(s16 *)(object + 0x1A) * 4, poly);
                    break;

                case 0:
                    func_8005CF34(object, 0, 0, 0, 0);
                    break;
                case 5:
                    func_8005C020(object, scratch);
                    func_8005CF34(object, 0, 0, 0, (s32)scratch);
                    break;
                case 6:
                    func_8005C0F4(object, (s32)scratch);
                    func_8005CF34(object, 0, 0, 9, (s32)scratch);
                    break;
                }
            }
        }
    }
}

void __maspsx_include_asm_hack_pad_8008F94C(void) {
    __asm__(".section .rodata # maspsx-keep\n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern s32 D_800A3654;
extern u8 D_800A37BC;
s32 func_8005BF68(void) {
    u8 index;
    index = D_800A37BC;
    D_800A37BC = index + 1;
    return D_800A3654 + index * 12;
}

extern u8 D_800A35EC;
extern u8 *D_800A3678;
extern u8 D_800A37BC;
extern s32 D_800A3654;
struct UnkTextObj *func_8005BF8C(s32 left, s32 top) {
    u8 spriteIndex;
    u8 primIndex;
    u8 *object;
    u8 *prim;
    u8 *base;

    spriteIndex = D_800A35EC++;
    base = D_800A3678;
    object = base + spriteIndex * 36;
    object[4] = 0;
    object[3] = 0;
    object[2] = 0;
    primIndex = D_800A37BC;
    *(u16 *)(object + 0xA) = left;
    *(u16 *)(object + 0x6) = left;
    prim = (u8 *)D_800A3654;
    *(u16 *)(object + 0x12) = 0;
    *(u16 *)(object + 0x14) = 0;
    *(u32 *)(object + 0x1C) = 0;
    *(u16 *)(object + 0x1A) = 0;
    *(u16 *)(object + 0x0) = 0;
    *(u16 *)(object + 0xC) = top;
    *(u16 *)(object + 0x8) = top;
    *(u16 *)(object + 0xE) = 0;
    *(u16 *)(object + 0x10) = 0;
    *(u16 *)(object + 0x1A) = 0;
    D_800A37BC = primIndex + 1;
    do {
    } while (0);
    prim += primIndex * 12;
    *(u32 *)(object + 0x20) = prim;
    prim[0] = 0;
    prim[3] = 0;
    *(s32 *)(prim + 4) = 0;
    return (struct UnkTextObj *)object;
}

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
void func_8005C020(u8 *object, u8 *dest) {
    s32 id;

    id = *(s16 *)(*(u8 **)(object + 0x20) + 8);
    if (D_800A39E4[0] == 0xA) {
        if (id == 0xFF) {
            *(Unk4 *)dest = D_800A3324[0];
            return;
        }
        if (id == -1) {
            *(Unk4 *)dest = D_800A3328[0];
            return;
        }
    } else if (D_800A39E4[0] == 0xC) {
        if (id == 0) {
            *(Unk3 *)dest = D_800A332C[0];
            return;
        }
    }
    func_80012EA8(id, dest);
}

extern void func_80018588(void *, s32, s32);
void func_8005C0F4(u8 *object, s32 value) {
    func_80018588(*(void **)(*(u8 **)(object + 0x20) + 8), -1, value);
}

extern u8 *D_8009A05C[];
extern u8 *D_8009A078[];
extern u8 *D_8009A098[];
extern u8 *D_8009A0B8[];
extern u8 *D_8009A0D8[];
extern u8 *D_8009A0F4[];
extern u8 *D_8009A110[];
extern u8 *D_8009A134[];
extern u8 *D_8009A158[];
extern u8 *D_8009A17C[];
extern u8 *D_8009A19C[];
extern u8 *D_8009A1BC[];
extern u8 *D_8009A1DC[];
extern u8 *D_8009A200[];
extern u8 *D_8009A21C[];
extern u8 *D_8009A228[];
extern u8 *D_8009A248[];
extern u8 *D_8009A2C4[];
extern u8 *D_8009ABFC[];
extern u8 D_8009AF74[];
extern u8 *D_800A3690;
extern u8 *D_800A39C0;
extern u8 *D_800A3A28;
extern u8 *D_800A39B8;
extern u8 *D_800A36F0;
extern u8 *D_800A38F8;
extern u8 *D_800A3678;
extern s32 D_800A3654;
extern u8 D_800A38E8;
extern u8 D_800A3644[];
extern u8 D_800A3950[];
extern u8 D_800A3988[];
extern u8 D_800A3989[];
extern s32 D_800A37D0[];
extern s16 *D_800AE290[];
extern u8 *D_800AE27C[];
extern u8 *D_800BB9E4[];
extern u8 D_800A331C[];
extern u8 D_800A3330[];
extern u8 D_800AD980[];
extern u8 D_800A35C8Text[] asm("D_800A35C8");
extern void func_8005CBC8(s32);
void func_8005C124(u8 menuId, u8 selRow) {
    s32 slots[3][4];
    u8 *item;
    u8 *entry;
    u8 *text;
    s32 i;
    s32 rows;
    s32 count;
    s32 savedY;
    s32 y;
    s32 x;
    s32 d;
    s32 width;

    count = 0;
    D_800A39C0 = 0;
    D_800A3A28 = 0;
    switch (menuId) {
    case 0:
        D_800A3690 = (u8 *)D_8009A05C;
        break;
    case 1:
        D_800A3690 = (u8 *)D_8009A0B8;
        break;
    case 2:
        D_800A3690 = (u8 *)D_8009A078;
        D_800A39C0 = (u8 *)D_8009A098;
        break;
    case 4:
        D_800A3690 = (u8 *)D_8009A110;
        D_800A39C0 = (u8 *)D_8009A134;
        D_800A3A28 = (u8 *)D_8009A158;
        break;
    case 5:
        D_800A3690 = (u8 *)D_8009A0D8;
        D_800A39C0 = (u8 *)D_8009A0F4;
        break;
    case 3:
        D_800A3690 = (u8 *)D_8009A1DC;
        break;
    case 6:
        D_800A3690 = (u8 *)D_8009A200;
        break;
    case 8:
        D_800A3690 = (u8 *)D_8009A21C;
        break;
    case 7:
        D_800A3690 = (u8 *)D_8009A228;
        D_800A39C0 = (u8 *)D_8009A248;
        break;
    case 13:
        D_800A3690 = (u8 *)D_8009ABFC;
        break;
    case 11:
        D_800A3690 = (u8 *)D_8009A17C;
        D_800A39C0 = (u8 *)D_8009A19C;
        D_800A3A28 = (u8 *)D_8009A1BC;
        break;
    case 15:
        D_800A3690 = (u8 *)D_8009A2C4;
        break;
    case 9:
    case 10:
    case 12:
    case 14:
        break;
    }
    x = 0x20;
    D_800A38E8 = D_8009AF74[menuId];
    y = 0x32;
    if (menuId == 0xD && D_800A3644[0] != 0) {
        y = 0x2A;
    }
    rows = D_800A38E8 + 1;
    if (menuId == 4) {
        rows = D_800A38E8 + 2;
    }
    if (menuId == 0xB) {
        rows += 5;
    }
    for (i = 0; i < rows; i++) {
        {
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
            item = object;
        }
        *(s16 *)(item + 0) = 0;
        *(s16 *)(item + 0x1A) = 0;
        *(s16 *)(item + 0xC) = y;
        *(s16 *)(item + 8) = y;
        if (menuId == 2) {
            if (i >= 5) {
                D_800AE27C[i] = item;
            }
            if (i == 5) {
                savedY = y;
            }
            if (D_800A3988[0] == 0) {
                if (i >= 5) {
                    if (i < 7)
                        goto lowRow;
                    if (i == 7)
                        goto lastRow;
                    goto rowDone;
                lowRow:
                    *(s16 *)(item + 8) = 0xF1;
                    goto rowDone;
                lastRow:
                    *(s16 *)(item + 8) = savedY;
                }
            }
        } else if (menuId == 5 && i == 6) {
            *(s16 *)(item + 8) = y + 0xF;
            *(s16 *)(item + 0xC) = y + 0xF;
            item[2] = 0xC8;
            item[3] = 0x40;
            item[4] = 0x40;
            D_800AE290[0] = (s16 *)item;
        } else {
            *(s16 *)(item + 8) = y;
        }
    rowDone:
        entry = (u8 *)(D_800A3654 + D_800A37BC++ * 0xC);
        *(u8 **)(item + 0x20) = entry;
        if (i == selRow + 1) {
            entry[0] = 1;
        } else {
            entry[0] = 0;
        }
        if (menuId == 1)
            goto check1;
        if (menuId == 0x24)
            goto check1;
        if (menuId == 0x28)
            goto check1;
        if (menuId == 0x25)
            goto check1;
        if (menuId != 0x27)
            goto check3;
    check1:
        if (D_800A3950[0] == 0) {
            if ((u32)(i - 3) < 4)
                goto setFlag;
        }
    check3:
        if (menuId == 3) {
            if (D_800A3644[0] != 0) {
                if ((u32)(i - 3) < 2)
                    goto setFlag;
            }
        }
        if (menuId != 4)
            goto noFlag;
        if (D_800A3644[0] == 0)
            goto noFlag;
        if (i != 6)
            goto noFlag;
    setFlag:
        entry[0] |= 2;
    noFlag:
        entry[3] = 0;
        *(s32 *)(entry + 4) = 0;
        *(s16 *)(item + 0x10) = 0;
        if (i == 0) {
            D_800A39B8 = item;
            func_8005A7B8(1, 1);
            entry[2] = 1;
            entry[1] = 1;
            *(u8 **)(entry + 8) = *(u8 **)D_800A3690;
            *(s16 *)(item + 0xE) = -2;
        } else {
            if (i == 1) {
                D_800A36F0 = item;
                func_8005A7B8(0, 0);
            }
            entry[2] = 0;
            entry[1] = 0;
            if (menuId == 4 && D_800A38E8 < i) {
                D_800A38F8 = item;
                func_8005CBC8(D_800A37D0[0]);
                *(u8 **)(entry + 8) = D_800A35C8Text;
            } else if (menuId == 0xB && (d = D_800A38E8) < i) {
                d = i - d;
                D_800BB9E4[d - 1] = item;
                func_8005CBC8(D_800A331C[d - 1]);
                text = D_800AD980 + (i - D_800A38E8) * 8;
                *(u8 **)(entry + 8) = text;
                strcpy(text, D_800A35C8Text);
            } else {
                switch (D_800A3989[i - 2]) {
                case 0:
                case 0x80:
                    *(u8 **)(entry + 8) = ((u8 **)D_800A3690)[i];
                    if (D_800A3989[i - 2] == 0x80) {
                        entry[0] |= 2;
                    }
                    break;
                case 1:
                case 0x81:
                    *(u8 **)(entry + 8) = ((u8 **)D_800A39C0)[i];
                    if (D_800A3989[i - 2] == 0x81) {
                        entry[0] |= 2;
                    }
                    break;
                case 2:
                    *(u8 **)(entry + 8) = ((u8 **)D_800A3A28)[i];
                    break;
                }
            }
            *(s16 *)(item + 0xE) = 2;
        }
        *(s16 *)(item + 0x16) = func_8005A8E0(*(s32 *)(entry + 8));
        *(s16 *)(item + 0x18) = func_8005A84C();
        *(s16 *)(item + 0xA) = 0x131 - *(u16 *)(item + 0x16);
        *(s16 *)(item + 6) = x - *(u16 *)(item + 0x16);
        if ((menuId == 4 && i == 1) || (menuId == 0xB && (u32)(i - 2) < 5)) {
            width = func_8005A8E0((s32)D_800A3330);
            *(s16 *)(item + 0xA) = *(u16 *)(item + 0xA) - width;
            slots[1][count] = y;
            slots[2][count] = x;
            count++;
            *(s16 *)(item + 6) = *(u16 *)(item + 6) - width;
        }
        y += *(s16 *)(item + 0x18);
        if (i == 0) {
            y += 8;
            *(s16 *)(item + 6) = 0x140;
            *(s16 *)(item + 0xA) = *(u16 *)(item + 0xA) - 10;
        } else {
            if (menuId == 4 || menuId == 0xB) {
                if (D_800A38E8 < i) {
                    *(s16 *)(item + 6) =
                        slots[2][i - D_800A38E8 - 1] - *(u16 *)(item + 0x16);
                    *(s16 *)(item + 0xC) = slots[1][i - D_800A38E8 - 1];
                    *(s16 *)(item + 8) = slots[1][i - D_800A38E8 - 1];
                    if (selRow == 0) {
                        entry[0] = 1;
                    }
                }
            }
            x -= 0x80;
        }
    }
}

extern u8 *D_800A36F0;
extern u8 *D_800A3690;
extern u8 *D_800A39C0;
extern u8 *D_800A3A28;
extern u8 D_800A3988[];
extern void func_8005A7B8(u8, u8);
extern s16 func_8005A8E0(s32);
void func_8005C8D8(u8 index) {
    u8 *window;
    u8 *prim;
    s32 i;
    s16 result;
    s16 height;

    window = D_800A36F0;
    for (i = 0; i < index; i++) {
        window += 36;
    }
    prim = *(u8 **)(window + 0x20);
    switch (D_800A3988[index]) {
    case 0:
    case 0x80:
        *(s32 *)(prim + 8) = *(s32 *)(D_800A3690 + index * 4 + 4);
        if (D_800A3988[index] == 0x80) {
            prim[0] |= 2;
        } else {
            prim[0] = 0;
        }
        break;
    case 1:
    case 0x81:
        *(s32 *)(prim + 8) = *(s32 *)(D_800A39C0 + index * 4 + 4);
        if (D_800A3988[index] == 0x81) {
            prim[0] |= 2;
        } else {
            prim[0] = 0;
        }
        break;
    case 2:
        *(s32 *)(prim + 8) = *(s32 *)(D_800A3A28 + index * 4 + 4);
        break;
    }
    func_8005A7B8(0, 0);
    result = func_8005A8E0(*(s32 *)(prim + 8));
    height = 0x131 - result;
    *(s16 *)(window + 0x16) = result;
    *(s16 *)(window + 6) = height;
    *(s16 *)(window + 0xA) = height;
}

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
s32 func_8005CA4C(void) {
    s32 i;
    u8 *prim;
    s16 value;

    if (D_800A3988[0] != 0) {
        *(s16 *)((u8 *)D_800AE290[0] + 8) = 0xF1;
        *(s16 *)(D_800AE294[0] + 8) = 0xF1;
        prim = D_800AE298[0];
        value = *(u16 *)((u8 *)D_800AE290[0] + 0xC);
        D_800A3644[0] = 0;
        *(s16 *)(prim + 8) = value;
    } else {
        if (D_800A3A25[0] == 0) {
            return 0;
        }
        for (i = 0; i < 3; i++) {
            *(s16 *)((u8 *)D_800AE290[i] + 8) =
                *(u16 *)((u8 *)D_800AE290[i] + 0xC);
        }
        D_800A3644[0] = 1;
        if (D_800A36E0[0] == D_800A36E0[1]) {
            D_800A36E1[0] = (D_800A36E0[0] + 1) % 24;
            func_800636EC(1, D_800A36E1[0]);
            func_80063AE0(1, D_800A36E0[1]);
        }
        func_80063694(1, -0x3C, *(s16 *)(D_800A35E8[0] + 0xA), 2);
    }
    D_800A3989[0] = D_800A3988[1] ^ 1;
    D_800A3988[0] = D_800A3989[-1] ^ 1;
    func_8005C8D8(1);
    func_8005C8D8(0);
    return 1;
}

extern u8 D_800A35C8;
extern u8 D_800A35C9[];
extern u8 D_800A3338[];
extern char *strcat(char *, char *);
extern u8 *func_80012EA8(s32, u8 *);
void func_8005CBC8(s32 number) {
    u8 *buffer;
    s32 length;

    buffer = D_800A35C9 - 1;
    D_800A35C8 = 0x20;
    length = 1;
    if (number < 0x64) {
        D_800A35C9[0] = 0x20;
        length = 2;
    }
    D_800A35C9[length - 1] = 0;
    func_80012EA8(number, buffer + length);
    strcat(buffer, D_800A3338);
}

extern u8 *D_800A38F8;
extern s32 D_800A37D0[];
void func_8005CC34(void) {
    u8 *prim;
    u8 *buffer;
    s32 number;
    s32 length;
    s16 result;
    s16 height;

    prim = *(u8 **)(D_800A38F8 + 0x20);
    number = D_800A37D0[0];
    buffer = D_800A35C9 - 1;
    D_800A35C8 = 0x20;
    length = 1;
    if (number < 0x64) {
        D_800A35C9[0] = 0x20;
        length = 2;
    }
    D_800A35C9[length - 1] = 0;
    func_80012EA8(number, buffer + length);
    strcat(buffer, D_800A3338);
    func_8005A7B8(prim[1], prim[2]);
    result = func_8005A8E0(*(s32 *)(prim + 8));
    height = 0x131 - result;
    *(s16 *)(D_800A38F8 + 0x16) = result;
    *(s16 *)(D_800A38F8 + 6) = height;
    *(s16 *)(D_800A38F8 + 0xA) = height;
}

/* buffer is pinned to s1 with an explicit-register local: gcc 2.7.2 hands
 * such variables their hard register directly (make_decl_rtl), so
 * global-alloc never ranks it against the D_800BB9E4[id] slot address
 * temp, which takes s2 as in retail. */
extern u8 D_800A331CAbsolute[];
extern u8 *D_800BB9E4[];
extern char *strcpy(char *, const char *);
s32 func_8005CCEC(s32 id, s32 delta, s32 max, s32 min) {
    u8 *prim;
    u8 *buffer;
    s32 length;
    u8 newValue;
    s16 value;
    s32 inRange;
    switch (id & 0xFF) {
    case 1:
        id = 0;
        min = 0x4B;
        max = 0x73;
        break;

    case 2:
        id = 1;
        min = 0x50;
        max = 0x82;
        break;

    case 3:
        id = 2;
        min = 0x5A;
        max = 0x96;
        break;

    case 4:
        id = 3;
        min = 0x4B;
        max = 0x78;
        break;

    case 5:
        id = 4;
        min = 0x32;
        max = 0x64;
        break;
    }

    newValue = D_800A331CAbsolute[id & 0xFF] + delta;
    D_800A331CAbsolute[id & 0xFF] = newValue;
    inRange = 1;
    if (newValue < min) {
        D_800A331CAbsolute[id & 0xFF] = min;
        inRange = 0;
    } else if (newValue > max) {
        D_800A331CAbsolute[id & 0xFF] = max;
        inRange = 0;
    }
    prim = *((u8 **)(D_800BB9E4[id & 0xFF] + 0x20));
    value = D_800A331CAbsolute[id & 0xFF];
    buffer = D_800A35C9 - 1;
    D_800A35C8 = 0x20;
    do {
        length = 1;
        if (value < 0x64) {
            D_800A35C9[0] = 0x20;
            length = 2;
        }
        D_800A35C9[length - 1] = 0;
        func_80012EA8(value, buffer + length);
        strcat(buffer, D_800A3338);
        strcpy(*((char **)(prim + 8)), (char *)buffer);
    } while (0);
    func_8005A7B8(prim[1], prim[2]);
    *((s16 *)(D_800BB9E4[id & 0xFF] + 0x16)) =
        func_8005A8E0(*((s32 *)(prim + 8)));
    *((s16 *)(D_800BB9E4[id & 0xFF] + 6)) =
        0x131 - (*((s16 *)(D_800BB9E4[id & 0xFF] + 0x16)));
    *((s16 *)(D_800BB9E4[id & 0xFF] + 0xA)) =
        *((s16 *)(D_800BB9E4[id & 0xFF] + 6));
    return inRange;
}

/* The original toolchain padded this odd-length jump table with one zero
 * word; the C switch regenerates the table, this restores the pad. */
void __maspsx_include_asm_hack_jtblpad_8005CCEC() {
    __asm__(".section .rodata # maspsx-keep \n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern u8 D_800A3078[], D_800A3988[];
extern void func_8005C8D8(u8);
extern s32 func_8005CCECArgs(u8, s32);
asm(".globl func_8005CCECArgs\nfunc_8005CCECArgs = func_8005CCEC");
void func_8005CEDC(void) {
    s32 i;
    D_800A3988[0] = D_800A3078[0];
    i = 0;
    func_8005C8D8(i);
    i = 1;
    do {
        func_8005CCECArgs(i, 0);
        i++;
    } while (i < 6);
}

#ifdef NON_MATCHING
extern void func_8005A9F4(s32, s16, s16, u8, u8, s32, u8, u8);
void func_8005CF34(u8 *window, u8 code, u8 first, u8 second, s32 textId) {
    register u8 *prim asm("s3");

    prim = *(u8 **)(window + 0x20);
    func_8005A7B8(prim[1], prim[2]);
    prim[0] = code;
    if (textId == 0) {
        textId = *(s32 *)(prim + 8);
    }
    if ((*(s32 *)(window + 0) & 0xFFFF0000) != 0 || window[4] != 0) {
        func_8005A818(window[2], window[3], window[4]);
    } else if (prim[1] == 2) {
        func_8005A818(0xFF, 0x80, 0x40);
    } else {
        func_8005A818(0, 0, 0);
    }
    if (D_800A39E4[0] == 0xD) {
        func_8005A9F4(textId,
                      (s16)(*(u16 *)(window + 6) + *(u16 *)(window + 0x12)),
                      (s16)(*(u16 *)(window + 8) + *(u16 *)(window + 0x14)),
                      prim[3], prim[0], *(s32 *)(prim + 4), first, second);
    } else {
        func_8005A9F4(textId, *(s16 *)(window + 6), *(s16 *)(window + 8),
                      prim[3], prim[0], *(s32 *)(prim + 4), first, second);
    }
}
#else
extern void func_8005A9F4(s32, s16, s16, u8, u8, s32, u8, u8);
void func_8005CF34(u8 *window, u8 code, u8 first, u8 second, s32 textId) {
    u8 *prim;
    s32 id;

    prim = *(u8 **)(window + 0x20);
    func_8005A7B8(prim[1], prim[2]);
    prim[0] = code;
    id = textId;
    if (id == 0) {
        id = *(s32 *)(prim + 8);
    }
    if ((*(s32 *)(window + 0) & 0xFFFF0000) != 0 || window[4] != 0) {
        func_8005A818(window[2], window[3], window[4]);
    } else if (prim[1] == 2) {
        func_8005A818(0xFF, 0x80, 0x40);
    } else {
        func_8005A818(0, 0, 0);
    }
    if (D_800A39E4[0] == 0xD) {
        func_8005A9F4(id, (s16)(*(u16 *)(window + 6) + *(u16 *)(window + 0x12)),
                      (s16)(*(u16 *)(window + 8) + *(u16 *)(window + 0x14)),
                      prim[3], prim[0], *(s32 *)(prim + 4), first & 0xFF,
                      second & 0xFF);
    } else {
        func_8005A9F4(id, *(s16 *)(window + 6), *(s16 *)(window + 8), prim[3],
                      prim[0], *(s32 *)(prim + 4), first & 0xFF, second & 0xFF);
    }
}

#endif

extern u8 *D_800A392C;
extern u8 *D_800A35E4;
extern u8 *D_800A3628;
extern u8 *D_800A362C[];
extern u8 *D_800A3634;
extern u8 *D_800A3740;
extern u8 *D_800A3788;
extern u8 *D_800A37D8[];
extern u8 *D_800A37F8;
extern u8 *D_800A3888[];
extern u8 *D_800A38A8;
extern u8 D_800A38E8;
extern u8 *D_800A39B8;
extern u8 *D_800A3A10;
extern u8 D_800A3684[];
extern u8 D_800A3685[];
extern u8 D_800A3950[];
extern u8 D_800A361CStore[] asm("D_800A361C.NON_MATCHING");
extern u8 *D_800A35E8Read[] asm("D_800A35E8.NON_MATCHING");
extern u8 *D_800A362CRead[] asm("D_800A362C.NON_MATCHING");
extern void func_8005E8EC(s32, s32, s32);
extern void func_8005FE90(void);
extern void func_800602E8(s8, u8);
extern void func_80062910(s32);
extern void func_80063638(u8);
extern void func_800637D8(u8);
extern void func_80064000(s32, s32, s32);
void func_8005D094(s32 mode, u8 selection, u8 second) {
    extern u8 D_800A361C[];
    extern u8 D_800A3059[];
    u8 *window;
    s32 count;
    s32 i;
    u8 code;
    u8 active;
    s32 selected;
    u8 **entry;
    u8 **other;
    s32 offset;

    window = D_800A39B8;
    count = D_800A38E8 + 1;
    if ((mode & 0xFF) == 4) {
        count = D_800A38E8 + 2;
    }
    if ((mode & 0xFF) == 11) {
        count += 5;
    }
    for (i = 0; i < count; i++) {
        code = i == selection + 1;
        if ((((mode & 0xFF) == 1 || (mode & 0xFF) == 36 ||
              (mode & 0xFF) == 40 || (mode & 0xFF) == 37 ||
              (mode & 0xFF) == 39) &&
             D_800A3950[0] == 0 && (u32)(i - 3) < 4) ||
            ((mode & 0xFF) == 3 && D_800A3644[0] != 0 && (u32)(i - 3) < 2) ||
            ((mode & 0xFF) == 4 && D_800A3644[0] != 0 && i == 6)) {
            code |= 2;
        }
        if (*(s16 *)(window + 0xE) != 0) {
            func_8005B688(window, 1);
        } else if (i == count - 1 && D_800A361C[0] == 0) {
            D_800A361CStore[0] = 1;
        }
        if ((mode & 0xFF) == 4) {
            if (i == count - 1) {
                code = 1;
                if (selection != 0)
                    code = 0;
            } else if ((**(u8 **)(window + 0x20)) & 2) {
                code |= 2;
            }
        } else if ((mode & 0xFF) == 11 && D_800A38E8 < i) {
            code = 0;
            switch (selection) {
            case 1:
                if (i == D_800A38E8 + 1)
                    code = 1;
                break;
            case 2:
                if (i == D_800A38E8 + 2)
                    code = 1;
                break;
            case 3:
                if (i == D_800A38E8 + 3)
                    code = 1;
                break;
            case 4:
                if (i == D_800A38E8 + 4)
                    code = 1;
                break;
            case 5:
                if (i == D_800A38E8 + 5)
                    code = 1;
                break;
            }
        }
        if (*(s16 *)(window + 0x1A) >= 0) {
            {
                u8 *drawPrim;
                s32 drawId;
                u8 drawFirst;
                drawFirst = i != 0;
                drawPrim = *(u8 **)(window + 0x20);
                func_8005A7B8(drawPrim[1], drawPrim[2]);
                drawPrim[0] = code;
                drawId = *(s32 *)(drawPrim + 8);
                if ((*(s32 *)(window + 0) & 0xFFFF0000) != 0 ||
                    window[4] != 0) {
                    func_8005A818(window[2], window[3], window[4]);
                } else if (drawPrim[1] == 2) {
                    func_8005A818(0xFF, 0x80, 0x40);
                } else {
                    func_8005A818(0, 0, 0);
                }
                if (D_800A39E4[0] == 0xD) {
                    func_8005A9F4(
                        drawId,
                        (s16)(*(u16 *)(window + 6) + *(u16 *)(window + 0x12)),
                        (s16)(*(u16 *)(window + 8) + *(u16 *)(window + 0x14)),
                        drawPrim[3], drawPrim[0], *(s32 *)(drawPrim + 4),
                        drawFirst & 0xFF, 0);
                } else {
                    func_8005A9F4(drawId, *(s16 *)(window + 6),
                                  *(s16 *)(window + 8), drawPrim[3],
                                  drawPrim[0], *(s32 *)(drawPrim + 4),
                                  drawFirst & 0xFF, 0);
                }
            }
        }
        window += 0x24;
    }
    if (D_800A361C[0] == 1) {
        func_8005B688(D_800A392C, 1);
        func_8005B8B8(D_800A392C, 0xFF);
        func_8005B688(D_800A3634, 1);
        active = 1;
        if ((mode & 0xFF) == 2)
            active = selection != 2;
        func_8005E8EC(1, active, 0);
        func_8005B688(D_800A3740, 1);
        {
            u8 *drawWindow;
            u8 *drawPrim;
            s32 drawId;
            drawWindow = D_800A3740;
            drawPrim = *(u8 **)(drawWindow + 0x20);
            func_8005A7B8(drawPrim[1], drawPrim[2]);
            drawPrim[0] = 0;
            drawId = *(s32 *)(drawPrim + 8);
            if ((*(s32 *)(drawWindow + 0) & 0xFFFF0000) != 0 ||
                drawWindow[4] != 0) {
                func_8005A818(drawWindow[2], drawWindow[3], drawWindow[4]);
            } else if (drawPrim[1] == 2) {
                func_8005A818(0xFF, 0x80, 0x40);
            } else {
                func_8005A818(0, 0, 0);
            }
            if (D_800A39E4[0] == 0xD) {
                func_8005A9F4(drawId,
                              (s16)(*(u16 *)(drawWindow + 6) +
                                    *(u16 *)(drawWindow + 0x12)),
                              (s16)(*(u16 *)(drawWindow + 8) +
                                    *(u16 *)(drawWindow + 0x14)),
                              drawPrim[3], drawPrim[0], *(s32 *)(drawPrim + 4),
                              1, 0);
            } else {
                func_8005A9F4(drawId, *(s16 *)(drawWindow + 6),
                              *(s16 *)(drawWindow + 8), drawPrim[3],
                              drawPrim[0], *(s32 *)(drawPrim + 4), 1, 0);
            }
        }
        func_8005B688(D_800A3788, 1);
        {
            u8 *drawWindow;
            u8 *drawPrim;
            s32 drawId;
            drawWindow = D_800A3788;
            drawPrim = *(u8 **)(drawWindow + 0x20);
            func_8005A7B8(drawPrim[1], drawPrim[2]);
            drawPrim[0] = 0;
            drawId = *(s32 *)(drawPrim + 8);
            if ((*(s32 *)(drawWindow + 0) & 0xFFFF0000) != 0 ||
                drawWindow[4] != 0) {
                func_8005A818(drawWindow[2], drawWindow[3], drawWindow[4]);
            } else if (drawPrim[1] == 2) {
                func_8005A818(0xFF, 0x80, 0x40);
            } else {
                func_8005A818(0, 0, 0);
            }
            if (D_800A39E4[0] == 0xD) {
                func_8005A9F4(drawId,
                              (s16)(*(u16 *)(drawWindow + 6) +
                                    *(u16 *)(drawWindow + 0x12)),
                              (s16)(*(u16 *)(drawWindow + 8) +
                                    *(u16 *)(drawWindow + 0x14)),
                              drawPrim[3], drawPrim[0], *(s32 *)(drawPrim + 4),
                              1, 0);
            } else {
                func_8005A9F4(drawId, *(s16 *)(drawWindow + 6),
                              *(s16 *)(drawWindow + 8), drawPrim[3],
                              drawPrim[0], *(s32 *)(drawPrim + 4), 1, 0);
            }
        }
        if ((mode & 0xFF) != 7 || second == 0) {
            func_8005B688(D_800A35E4, 1);
            func_8005B8B8(D_800A35E4, 0xFF);
            func_80064000(0, 0, (mode & 0xFF) == 7);
            if (((mode & 0xFF) == 2 && (u8)(selection - 1) < 2) ||
                ((mode & 0xFF) == 8 && selection == 0)) {
                if ((mode & 0xFF) == 2)
                    func_80063638(selection == 1);
                func_8005B688(D_800A3628, 1);
                func_8005B8B8(D_800A3628, 0xFF);
            }
        }
        if (D_800A3644[0] != 0) {
            if ((mode & 0xFF) != 7 || second == 1) {
                func_8005B688(D_800A35E8[0], 1);
                func_8005B8B8(D_800A35E8Read[0], 0xFF);
                selected = D_800A3A25[0] == 0;
                func_80064000(1, selected, (mode & 0xFF) == 7);
                if ((mode & 0xFF) == 2 && selection == 1) {
                    func_8005B688(D_800A362C[0], 1);
                    if (selected == 0)
                        func_8005B8B8(D_800A362CRead[0], 0xFF);
                }
            }
        }
        if ((mode & 0xFF) == 7) {
            func_8005FE90();
            func_800602E8((s8)selection, second);
        }
        if ((u8)(mode - 34) < 2 || (mode & 0xFF) == 36 || (mode & 0xFF) == 40 ||
            (mode & 0xFF) == 37 || (u8)(mode - 38) < 2 ||
            ((mode & 0xFF) == 1 && *(s16 *)(D_800A3A10 + 0xE) < 0)) {
            func_8005B688(D_800A3A10, 1);
            func_8005B8B8(D_800A3A10, 0xFF);
        }
        if ((mode & 0xFF) == 1 && *(s16 *)(D_800A3A10 + 0xE) == 0) {
            func_800637D8(0);
        }
    }
    if ((mode & 0xFF) != 33) {
        if ((mode & 0xFF) != 5 || *(s16 *)(D_800A38A8 + 0xE) >= 0) {
            goto afterPanel;
        }
    } else {
        if (D_800A3059[0] == 3 && !(VSync(-1) & 3)) {
            func_80044FF8(1, 1);
        }
    }
    func_8005B688(D_800A38A8, 1);
    func_8005B8B8(D_800A38A8, 0xFF);
afterPanel:
    if ((mode & 0xFF) == 13) {
        i = 0;
        if (i < D_800A3644[0] + 1) {
            entry = D_800A37D8;
            do {
                offset = i * 4;
                func_80062910(i & 0xFF);
                func_8005B688(*entry, 1);
                func_8005B8B8(*entry, 0xFF);
                if (D_800A3684[i] == 1) {
                    other = D_800A3888;
                    other = (u8 **)((u8 *)other + offset);
                    func_8005B688(*other, 1);
                    func_8005B8B8(*other, 0xFF);
                }
                i++;
                entry++;
            } while (i < D_800A3644[0] + 1);
        }
        if (D_800A3644[0] != 0) {
            if (D_800A3684[0] == 0 || D_800A3685[0] == 0) {
                func_8005B688(D_800A37F8, 1);
                func_8005B8B8(D_800A37F8, 0xFF);
            }
        } else if (D_800A3684[0] == 0) {
            func_8005B688(D_800A37F8, 1);
            func_8005B8B8(D_800A37F8, 0xFF);
        }
    }
}

void __maspsx_include_asm_hack_jtblpad_8005D094(void) {
    __asm__(".section .rodata # maspsx-keep\n"
            "    .word 0 # maspsx-keep\n"
            "    .section .text # maspsx-keep\n");
}

extern u8 D_800A35EC;
extern u8 *D_800A3678;
extern u8 D_800B9990[];
extern s16 *D_800B12FC[];
extern u16 D_8009AEDC[];
extern u16 D_8009AEDE[];
extern u16 D_8009AEE4[];
extern u16 D_8009AED8[];
extern u16 D_8009AEDA[];
extern u8 D_8009AEE0[];
extern u8 D_8009AEE2[];
extern u8 D_8009AEA2[];
extern u8 D_8009AEA6[];
extern u8 D_8009AEAA[];
extern u8 D_8009AEAE[];
extern u8 D_8009AEB2[];
extern u8 D_8009AEB6[];
extern u8 D_800A39C4;
void func_8005DAD4(void) {
    s32 i;
    s32 primOffset;
    s16 x;
    u8 index;
    u8 *object;
    u8 *prim;
    u16 value;
    u16 w;
    u16 h;

    x = -0x32;
    i = 0;
    primOffset = 0;
    do {
        index = D_800A35EC;
        prim = D_800B9990 + primOffset;
        D_800A35EC = index + 1;
        object = D_800A3678 + index * 36;
        *(s16 *)(object + 0) = 1;
        *(s16 *)(object + 0x12) = 0;
        *(s16 *)(object + 0x14) = 0;
        *(s32 *)(object + 0x1C) = 0;
        object[4] = 0;
        object[3] = 0;
        object[2] = 0;
        *(s16 *)(object + 0x1A) = 0;
        D_800B12FC[i] = (s16 *)object;
        *(s16 *)(object + 6) = x;
        x = x - 1;
        x = x - i;
        *(s16 *)(object + 8) = 0x10;
        *(s16 *)(object + 0xC) = 0x10;
        *(s16 *)(object + 0xE) = 2;
        *(s16 *)(object + 0x16) = 0x40;
        *(s16 *)(object + 0x10) = 0;
        *(s16 *)(object + 0x18) = 0x13;
        *(s16 *)(object + 0x1A) = 0;
        value = *(u16 *)(object + 6);
        *(s16 *)(object + 0xA) = value;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        prim[4] = 0x80;
        prim[5] = 0x80;
        prim[6] = 0x80;
        SetSemiTrans(prim, 1);
        w = *(u16 *)(object + 0x16);
        h = *(u16 *)(object + 0x18);
        *(s16 *)(prim + 0xE) = GetClut(D_8009AEDC[0], D_8009AEDE[0]);
        primOffset += 0x28;
        *(s16 *)(prim + 0x16) =
            GetTPage(D_8009AEE4[0], 3, D_8009AED8[0], D_8009AEDA[0]);
        prim[0xC] = D_8009AEE0[0];
        prim[0xD] = D_8009AEE2[0];
        prim[0x14] = D_8009AEA2[62] + w;
        prim[0x15] = D_8009AEAE[52];
        prim[0x1C] = D_8009AEA6[58];
        prim[0x1D] = D_8009AEB2[48] + h;
        prim[0x24] = D_8009AEAA[54] + w;
        prim[0x25] = D_8009AEB6[44] + h;
        i++;
        *(u8 **)(object + 0x20) = prim;
    } while (i < 10);
    D_800A39C4 = D_800A35EC;
}

extern s16 *D_800B12FC[];
extern u8 *func_80057CCC(s32);
s32 func_8005DCF0(void) {
    u8 done;
    s32 i;
    u8 *object;
    POLY_FT4 *poly;
    s16 sum;

    done = 0;
    i = 9;
    do {
        object = (u8 *)D_800B12FC[i];
        if (*(s16 *)(object + 0xE) != 0) {
            sum = *(u16 *)(object + 6) + *(s16 *)(object + 0xE);
            *(s16 *)(object + 6) = sum;
            if (sum >= 0x141) {
                *(s16 *)(object + 8) = 0xF0;
                if (i == 9) {
                    done = 1;
                }
                if (done != 0) {
                    *(s16 *)(object + 0xE) = 2;
                    *(s16 *)(object + 6) = *(u16 *)(object + 0xA);
                    *(s16 *)(object + 8) = *(u16 *)(object + 0xC);
                }
            }
            if ((s16) * (u16 *)(object + 0xE) < 6) {
                *(u16 *)(object + 0xE) =
                    *(u16 *)(object + 0xE) + (s16) * (u16 *)(object + 0xE) / 2;
            }
        }
        if (done == 0) {
            poly = func_80057CCC(0);
            *poly = *(POLY_FT4 *)*(u8 **)(object + 0x20);
            *(u16 *)((u8 *)poly + 8) = *(u16 *)(object + 6);
            *(u16 *)((u8 *)poly + 0xA) = *(u16 *)(object + 8);
            *(u16 *)((u8 *)poly + 0x10) =
                *(u16 *)(object + 6) + *(u16 *)(object + 0x16);
            *(u16 *)((u8 *)poly + 0x12) = *(u16 *)(object + 8);
            *(u16 *)((u8 *)poly + 0x18) = *(u16 *)(object + 6);
            *(u16 *)((u8 *)poly + 0x1A) =
                *(u16 *)(object + 8) + *(u16 *)(object + 0x18);
            *(u16 *)((u8 *)poly + 0x20) =
                *(u16 *)(object + 6) + *(u16 *)(object + 0x16);
            *(u16 *)((u8 *)poly + 0x22) =
                *(u16 *)(object + 8) + *(u16 *)(object + 0x18);
            AddPrim(D_800A39C8[0] + *(s16 *)(object + 0x1A) * 4, poly);
        }
        i--;
    } while (i != 0);
    return done;
}

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
