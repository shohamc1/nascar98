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

/* Controller state and input. */

void func_80041AD0(void) {
    func_80041AF0();
}

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

void func_80041AF0(void) {
    D_8008CA14[0] = 0xFFFF0000;
    D_8008CA18[0] = 0;
    D_8008CA1C[0] = 0xFFFF0000;
    D_8008CA20[0] = 0;
    D_8008CA04[0] = gPadBuffers[0];
    D_8008CA08[0] = D_800B9DF8[0];
    D_8008CA0C[0] = D_800B9E00[0];
    D_8008CA10[0] = D_800B9E04[0];
    func_80041F54(gPadBuffers, D_8008CA04, D_800B9DF8[0], D_800B9E00[0]);
}

extern u16 D_8008CA04U16[] asm("D_8008CA04.NON_MATCHING");
s32 func_80041B7C(s32 index) {
    return D_8008CA04U16[index * 4];
}

extern u16 D_8008CA04U16[] asm("D_8008CA04.NON_MATCHING");
u16 func_80041B94(s32 index) {
    return D_8008CA04U16[index];
}

extern s32 gPadBuffers[];

/* Wall: retail computes the nibble before the 0xFF branch and keeps it
 * in a0 with a final move v0,a0 on both paths; our shapes either go
 * branchless (xori/sltu/negu) or compute after the branch. */
u32 func_80041BAC(s32 arg0) {
    s32 temp;
    s32 result;

    if (arg0 < 0) {
        return 0;
    }
    temp = gPadBuffers[arg0 * 3];
    result = ((u32)(temp & 0xF000)) >> 12;
    if ((temp & 0xFF) == 0xFF) {
        temp = 0;
        result = temp;
    }
    return result;
}

extern u8 D_8008CA06[];
extern u32 D_8008CA08[];
extern void *D_800A3A24[];

/* Retail keeps an empty 8-byte frame; `framePad` reproduces it. The `u16 mode`
 * keeps the nor result and the or-accumulator in separate registers, and the
 * 0x3C8 store sits in both arms so jump2 cross-jumps only the final sb. */
u16 func_80041BFC(u8 *arg0) {
    s32 bank;
    u32 data;
    u16 pad;
    u16 mode;
    volatile s32 framePad[2];

    bank = *(s8 *)(arg0 + 0x20B);
    if (bank < 0) {
        return 0;
    }
    data = *(u32 *)((u8 *)D_8008CA08 + bank * 8);
    if (((s8 *)D_800A3A24)[bank] == 2) {
        arg0[0x3C6] = data >> 8;
        arg0[0x3C7] = data >> 0x10;
        arg0[0x3C5] = data;
        arg0[0x3C8] = data >> 0x18;
    } else {
        arg0[0x3C6] = data >> 8;
        arg0[0x3C5] = data >> 0x10;
        arg0[0x3C7] = data;
        arg0[0x3C8] = data >> 0x18;
    }
    pad = *(u16 *)(D_8008CA06 + *(s8 *)(arg0 + 0x20B) * 8);
    mode = ~(((pad & 0xFF) << 8) | (pad >> 8));
    if (mode & 0x1000) {
        mode |= 8;
    }
    if (mode & 0x4000) {
        mode |= 2;
    }
    if (mode & 0x2000) {
        mode |= 0x40;
    }
    if (mode & 0x8000) {
        mode |= 0x80;
    }
    return mode;
}

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

extern s32 gPadBuffers[];
extern u32 D_800B9E00[];

s32 func_80041D60(void) {
    u16 pads[2];
    u8 *cursor;
    u16 value1;
    u16 value2;

    cursor = (u8 *)gPadBuffers;
    asm("" : "=r"(cursor) : "0"(cursor));
    value1 = *(u16 *)(cursor + 2);
    pads[0] = ~(((value1 & 0xFF) << 8) | (value1 >> 8));
    cursor += 0xC;
    asm("" : "=r"(cursor) : "0"(cursor));
    value2 = *(u16 *)(cursor + 2);
    pads[1] = ~(((value2 & 0xFF) << 8) | (value2 >> 8));
    if ((*(u32 *)gPadBuffers & 0xF000) == 0) {
        pads[0] = 0;
    }
    if ((D_800B9E00[0] & 0xF000) == 0) {
        pads[1] = 0;
    }
    return ((u32)pads[1] << 16) | pads[0];
}

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

void func_80041DEC(void) {
    u32 padWord;
    u32 padType;
    u8 *node;
    s32 i;
    u32 pad0;
    u32 pad1;
    u32 pad2;
    u32 pad3;
    s32 *p;
    s32 *cursor;
    u32 noPad;

    /* The do-while (0) wraps raise padType's ref count so it outranks node. */
    padWord = gPadBuffers[0];
    noPad = 0xFF;
    do {
        padType = padWord & 0xF000;
        if ((padWord & 0xFF) == noPad) {
            padType = 0;
        } else {
            padType = padType >> 12;
        }
    } while (0);
    D_800A3A24Small = padType;
    padWord = D_800B9E00[0];
    do {
        padType = padWord & 0xF000;
        if ((padWord & 0xFF) == noPad) {
            padType = 0;
        } else {
            padType = padType >> 12;
        }
    } while (0);
    node = D_800A3878nm[0];
    D_800A3A25[0] = padType;
    D_800A3A26[0] = 0;
    D_800A3A27[0] = 0;
    if (node != 0) {
        do {
            if (*(s16 *)(node + 0x1EC) == 0) {
                node[0x3C4] = ((u8 *)D_800A3A24)[*(s8 *)(node + 0x20B)];
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != 0);
    }
    i = 7;
    /* Keeps the cursor address in a register: the dead if splits the block so
       combine can't fold it into the load, and the wrap raises the ref count
       above 2 so local-alloc doesn't substitute the symbol either. */
    do {
        cursor = gPadBuffers;
    } while (0);
    if (node != 0) {
        pad3 = 0;
    }
    pad0 = cursor[0];
    pad1 = D_800B9DF8[0];
    pad2 = D_800B9E00[0];
    pad3 = D_800B9E04[0];
    p = D_8008CA04;
    D_8008CA3C[0] = 0xFFFF0000;
    D_8008CA14[0] = 0xFFFF0000;
    D_8008CA40[0] = 0;
    D_8008CA18[0] = 0;
    D_8008CA44[0] = 0xFFFF0000;
    D_8008CA1C[0] = 0xFFFF0000;
    D_8008CA48[0] = 0;
    D_8008CA20[0] = 0;
    D_8008CA2C[0] = pad0;
    p[0] = pad0;
    D_8008CA30[0] = pad1;
    D_8008CA08[0] = pad1;
    D_8008CA34[0] = pad2;
    D_8008CA0C[0] = pad2;
    D_8008CA38[0] = pad3;
    D_8008CA10[0] = pad3;
    for (i = 7; i >= 0; i--) {
        /* The wrap raises p's ref count so it takes t0 and i takes t1. */
        do {
            p[i] = 0;
        } while (0);
    }
}

/* 2026-10-11 parked at 2025 (0x184 bytes, size matches). Full semantics decoded
 * from Ghidra's retail decompile: pads the 8-word output, copies arg0[1]/arg0[4],
 * then a 2-entry walk over the D_800A3A24 remap bytes (bound D_800A3A26) reading
 * {u32 word, u16 swapped mask, u32 thresholds} per 12-byte entry and shuffling
 * analog button bits by the type nibble. Residual: zero-loop counter lands in
 * a2 (retail v1); the three threshold byte extractions emit bare srl where
 * retail keeps andi/and+srl with srl (six mask spellings tried); branch-tree
 * layout in the type dispatch. */
#ifdef NON_MATCHING
void func_80041F54(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 *w;
    u16 *h;
    s8 *d;
    u32 *dst;
    u16 hs;
    u16 swap;
    u32 word;
    s32 w2;
    s32 i;
    s32 type;
    s32 b1;
    s32 b2;
    s32 b3;

    w = arg0;
    for (i = 7; i >= 0; i--) {
        arg1[i] = 0;
    }
    arg1[1] = w[1];
    arg1[3] = w[4];
    h = (u16 *)arg0 + 1;
    d = (s8 *)D_800A3A24;
    dst = arg1;
    while (d < (s8 *)D_800A3A26) {
        hs = *h;
        word = *w;
        w2 = *(u32 *)(h + 1);
        swap = ~(((hs & 0xFF) << 8) | (hs >> 8));
        *d = (word & 0xF000) >> 12;
        if ((word & 0xFF) == 0xFF) {
            *d = 0;
        }
        type = *d;
        if (type == 2) {
            hs = w2 & 0xFF00;
            b1 = hs >> 8;
            b2 = (w2 & 0xFF0000) >> 16;
            b3 = (w2 & 0xFF000000) >> 24;
            if (b3 > 0x80) {
                swap |= 4;
            }
            if (b1 > 0x40) {
                swap |= 0x40;
            }
            if (b2 > 0x40) {
                swap |= 0x80;
            }
        } else if (type < 5) {
            if (type != 4) {
                swap = 0;
            }
        } else if (type == 5) {
            if ((swap & 8) != 0) {
                swap = (swap & 0xFFF7) | 0x10;
            } else if ((swap & 4) != 0) {
                swap = (swap & 0xFFFB) | 0x80;
            } else if ((swap & 0x10) != 0) {
                swap = (swap & 0xFFEF) | 8;
            } else if ((swap & 0x80) != 0) {
                swap = (swap & 0xFF7F) | 2;
            } else if ((swap & 2) != 0) {
                swap = (swap & 0xFFFD) | 4;
            }
        }
        *dst = swap;
        h += 6;
        w += 3;
        d += 1;
        dst += 2;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/input", func_80041F54);
#endif

void func_800420D8(u32 *input, u32 flags, u16 *output) {
    u8 *mode;
    u8 *current;
    u8 *settingPtr;
    u32 data;
    u32 fields;
    u32 raw;
    u32 a;
    u32 b;
    u32 c;
    u16 setting;
    u32 state;
    u32 outputState;
    s8 modeValue;

    asm volatile("" : "=r"(current) : "0"((u8 *)input));
    settingPtr = current;
    mode = (u8 *)D_800A3A24;
    settingPtr += 2;
    do {
        setting = *(u16 *)settingPtr;
        data = *(u32 *)current;
        fields = *(u32 *)(settingPtr + 2);
        state = ~(((setting & 0xFF) << 8) | (setting >> 8));
        outputState = state;
        *mode = (data & 0xF000) >> 12;
        if ((data & 0xFF) == 0xFF) {
            *mode = 0;
        }
        modeValue = *(s8 *)mode;
        raw = modeValue;
        if (raw == 2) {
            c = (fields & 0xFF00) >> 8;
            a = (fields >> 16) & 0xFF;
            b = fields & 0xFF;
            if ((s32)(fields >> 24) >= 0x81) {
                outputState |= 4;
            }
            if (outputState & 0x1000) {
                outputState |= 8;
            }
            if (outputState & 0x4000) {
                outputState |= 2;
            }
            if (outputState & 0x2000) {
                outputState |= 0x40;
            }
            if (outputState & 0x8000) {
                outputState |= 0x80;
            }
        } else if (raw == 4) {
            c = 0;
            a = 0;
            b = 0;
        } else {
            c = 0;
            a = 0;
            b = 0;
            outputState = 0;
        }
        output[0] = outputState;
        output[1] = ((((b & 0xFC) << 8) | ((a & 0xF0) << 2)) |
                     (((s32)(c & 0xF0)) >> 2)) |
                    (flags & 3);
        state = 0xC;
        settingPtr += state;
        current += 0xC;
        input = (u32 *)current;
        output = (u16 *)((u8 *)output + 4);
        mode += 1;
        flags >>= 2;
    } while ((s32)(u32)mode < (s32)(u32)D_800A3A26);
}

void func_80042218(u16 *src, s32 *acc, u32 *dst) {
    s32 i;
    s32 shift;
    u32 bits;
    u32 bitsLo;
    u32 bitsHi;

    *acc = 0;
    i = 0;
    shift = -4;
    do {
        dst[0] = src[0];
        bits = src[1];
        bitsLo = (bits & 0x3C) << 10;
        bitsHi = (bits & 0x3C0) << 14;
        dst[1] = ((bits & 0xFC00) >> 8) | bitsLo | bitsHi;
        if (i >= 2) {
            *acc |= (bits & 3) << shift;
        }
        src += 2;
        dst += 2;
        i += 1;
        shift += 2;
    } while (i < 4);
}

s32 func_8004229C(s32 arg0) {
    s32 var_v0;
    u32 temp_a0;

    temp_a0 = arg0 & 0xFF;
    if (temp_a0 == 2) {
        var_v0 = 1;
    } else {
        if (temp_a0 < 5U) {
            var_v0 = 0;
            return var_v0;
        }
        var_v0 = 1;
    }
    return var_v0;
}

INCLUDE_ASM("asm/nonmatchings/input", func_800422C0);

INCLUDE_ASM("asm/nonmatchings/input", func_80042508);

INCLUDE_ASM("asm/nonmatchings/input", func_80042920);

extern s32 gRandomSeed16;
