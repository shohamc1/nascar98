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
extern u8 D_800A2F9CLui asm("D_800A2F9CAbsolute");
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
extern void func_80016CD8(u8 *, s32);
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
extern u8 D_800A2F9CLui asm("D_800A2F9CAbsolute");
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
typedef struct UnkBlockOffsets {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} UnkBlockOffsets;
extern UnkBlockOffsets *D_800A3A30;
extern void *D_800A3A24[];
extern void *D_800A336C;
extern s32 D_800A3370, D_800A3374, D_800A3378Small;
extern void *D_800A336C;
extern s32 D_800A3370, D_800A3374, D_800A3378Small;
extern u8 D_8009AD40[];
extern s16 func_8005A84C(void);
extern char *D_800A35F4;
extern char *D_800A3604;
extern char *D_800A366C;
extern char *D_800A3978;
extern char *D_800A3A0C;
extern u8 D_800A3938;
extern u8 D_800A3808;
extern u8 D_800A337C;
s32 CardCheckStatus(s32 arg0, u8 arg1);
extern u8 D_800A3938;
extern u8 D_800A3808;
extern u8 D_800A337C;
s32 CardCheckStatus(s32 arg0, u8 arg1);
extern u8 D_800A337C;
extern char D_8008FC60[];
extern s32 CardCountOtherFileBlocks(s32, char *);
extern char *D_800A35F4;
extern u8 D_800A3A58;
extern char *D_8009AC1C[];
extern char D_800BB9B4[];
extern u8 D_8009AD40[];
extern char *D_800A35F4;
extern u8 D_800A3A58;
extern u8 D_800A3068w17[] asm("D_800A3068.NON_MATCHING");
extern u8 D_800A3069w17[] asm("D_800A3069.NON_MATCHING");
extern u8 D_800A3A24w17[] asm("D_800A3A24.NON_MATCHING");
extern u8 D_800A307Cw17[] asm("D_800A307C.NON_MATCHING");
extern u8 D_800BBA24w17[] asm("D_800BBA24.NON_MATCHING");
typedef struct {
    s32 words[0x3A];
} CardMoveRecord;
extern char *D_800A35F4;
extern u8 D_800BBA24[];
extern u8 *volatile D_800A3604Vol asm("D_800A3604.NON_MATCHING");
extern u8 D_800A3073[];
extern u8 D_800A306D[];
extern u8 D_800A3078[];
extern u8 D_800A2F94R[] asm("D_800A2F94.NON_MATCHING");
extern u8 D_800A2F95R[] asm("D_800A2F95.NON_MATCHING");
extern u8 *volatile D_800A3604Vol asm("D_800A3604.NON_MATCHING");
extern u8 D_800A3073[];
extern u8 D_800A3078[];
extern u16 D_800A3694Absolute[];
extern s32 D_800A37D0[];
extern u8 D_800B9B6E[];
extern u8 D_800B9B6F[];
extern u8 D_800B9B70[];
extern u8 D_800B9B71[];
extern u8 D_800B9B72[];
extern u8 D_800B9BB4[];
extern char *strcpy(char *, const char *);
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
extern s32 D_8009A4C0[];
extern u8 *D_800A3908[];
extern u8 *D_800A377C[];
extern char D_800B0A2C[];
extern u8 *D_800A377C[];
extern u8 *D_800A377C[];
extern char D_800B0A2D[];
extern u8 D_800A358C;
extern char D_800B0A2C[];
extern s32 func_8005AEC8(u32, void *);
extern u8 D_800A358C;
extern u8 D_800A3968;
extern u8 D_800A305B[];
extern char D_800B0A2C[];
extern char *strcpy(char *, const char *);
extern u8 D_800A358C, D_800A3968, D_800A3808;
extern char D_800B0A2C[];
extern char D_800B9B44[];
extern char *strcpy(char *, const char *);
extern s32 func_8006A3E0(char *, s32, u8);
extern void func_800599E4(void);
extern void func_800598C4(void);
extern u8 D_800A358C;
extern char D_800B0A2C[];
extern u8 D_800B9B73[];
extern u8 D_800B9B74[];
extern u8 D_800A3980[];
extern void func_8006BB1C(void);
extern void func_8006EEBC(void);
extern u8 D_800BBA24[];
extern char *D_800A35F4;
extern u8 D_800BBA24_nm[] asm("D_800BBA24.NON_MATCHING");
extern u8 D_800A3068_nm[] asm("D_800A3068.NON_MATCHING");
extern u8 D_800A3069_nm[] asm("D_800A3069.NON_MATCHING");
extern u8 D_800A307C_nm[] asm("D_800A307C.NON_MATCHING");
extern u8 D_800A308C_nm[] asm("D_800A308C.NON_MATCHING");
extern s8 D_800A3A24_nm[] asm("D_800A3A24.NON_MATCHING");
extern u8 D_800BBA24[];
extern u8 D_800B9BB4[];
extern u8 *D_8009AB00nm[] asm("D_8009AB00.NON_MATCHING");
extern u8 *D_8009AB80nm[] asm("D_8009AB80.NON_MATCHING");
extern void *D_800A3908nm[] asm("D_800A3908.NON_MATCHING");
u8 *func_8005B598(s32 left, s32 top, s32 right, s32 bottom, s32 depth,
                  u8 texture, u8 semiTrans);
extern ColorNode *D_800A3A10[];
extern void func_8005B8B8(u8 *first, s32 value);
extern u8 D_800AEE3C[];
extern void func_8006E628(u32 arg0, u32 arg1, u32 arg2);
extern u8 D_800AEE3C[];
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
void func_80067F34(s32 arg0, s32 arg1);
void func_800686FC(s32 arg0, s32 arg1);
void __maspsx_include_asm_hack_jtblpad_800686FC();
void func_8006894C(s32 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4);
void func_80068A3C(u8 *head, u8 *other, s32 delta, s32 limit, s32 mid);
void func_80068AC4(s32 arg0, s32 arg1, s32 arg2);
void func_80069744(void);
void func_800697B4(void);
s32 func_80069A90(s32 arg0);
void __maspsx_include_asm_hack_jtblpad_80069A90();
void func_80069AFC(s32 arg0);
void func_80069E88(void);
s32 func_80069EB8(void);
s32 func_8006A080(void);
u8 CardGetOtherFileBlocks(void);
s32 func_8006AA70(void);
void func_8006ABF8(void);
void func_8006AC78(s32 arg0);
u8 func_8006AD0C(u8 value);
s32 func_8006AD44(char *name);
void func_8006ADC4(u8 arg0, char *arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5,
                   u8 arg6, u8 arg7);
void func_8006B088(s32 arg0);
void func_8006B1CC(u8 arg0, s32 arg1, u8 arg2, u8 arg3, u32 arg4, u8 arg5,
                   u8 arg6, u8 arg7);
void func_8006B3E0(s32 arg0, s32 arg1, s32 arg2);
void func_8006B464(void);
void func_8006B5BC(void);
void func_8006BA68(void);
void func_8006BD68(void);
void func_8006C598(s32 low, s32 high, s32 color);
void func_8006C5E4(s32 arg0);
void func_8006C668(s32 arg0, s32 arg1);
void func_8006C9DC(void);
void func_8006CB00(void);
void func_8006CB40(void);
void func_8006CE64(void);
void func_8006CF38(void);
void func_8006CF90(u32 mode);
s32 func_8006D0C0(void);
void func_8006D0F0(void);
s32 func_8006D258(void);
void func_8006D424(u8 arg0, u8 arg1);
void func_8006D4C8(u8 arg0, u8 arg1);
void func_8006D634(s32 arg);
void func_8006D684(u8 arg0);
void func_8006D708(u8 arg0, u8 arg1, u8 arg2);
void func_8006DA40(void);
void func_8006DCF0(void);
void func_8006DD28(u32 arg0, u32 arg1);
void func_8006DE68(u32 arg0, u32 mode);
void func_8006E484(u32 arg0, u32 arg1);

INCLUDE_ASM("asm/nonmatchings/media", func_8006E770);
INCLUDE_RODATA("asm/nonmatchings/media", D_8008FCA4);

INCLUDE_ASM("asm/nonmatchings/media", func_8006EB18);

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

extern s32 D_800A36B4nm[] asm("D_800A36B4.NON_MATCHING");
extern u8 D_800A3578[];
extern s32 D_8009A2E0[];
extern s32 D_8009A300[];
extern s8 D_800A3A24Absolute[];
extern s32 func_8006F9C4(s32, s32, s32);
extern void func_8005A9F4(s32, s16, s16, u8, u8, s32, u8, u8);
extern s32 RandomScaledGetVoid(void);
extern void func_80041AF0i(s32);
asm(".globl RandomScaledGetVoid\nRandomScaledGetVoid = RandomScaledGet");
asm(".globl func_80041AF0i\nfunc_80041AF0i = func_80041AF0");

void func_8006EEE0(s32 arg0) {
    RECT rect;
    DISPENV disp;
    DRAWENV draw;
    s32 idx;
    void *heap;
    s32 pixptr;
    s32 countdown;
    u8 flag;
    s32 buttons;
    s32 textId;

    idx = arg0 * 2;
    heap = FileLoadToHeap(idx + 0xE);
    func_8006F9C4(idx + 0xF, 2, 0);
    SetDispMask(0);
    TextureLoadTim(heap);
    rect = *(RECT *)&D_800A39B0[0];
    pixptr = D_800A36B4nm[0];
    SetDefDispEnv(&disp, 0, 0, 0x140, 0xF0);
    if (D_800A3578[0] == 1) {
        rect.x = 0x140;
        LoadImage(&rect, (u_long *)pixptr);
        SetDefDispEnv(&disp, 0x140, 0, 0x140, 0xF0);
    } else {
        SetDefDrawEnv(&draw, 0, 0, 0x140, 0xF0);
        PutDrawEnv(&draw);
    }
    DrawSync(0);
    ClearOTagR((OT_TYPE *)D_800A39C8[0], 0x400);
    func_8005A7B8(2, 2);
    if (D_800A3A24Absolute[0] == 2) {
        textId = D_8009A300[0];
    } else {
        textId = D_8009A2E0[0];
    }
    func_8005A9F4(textId, 0x131, 0xD8, 1, 0, 0, 0, 0);
    DrawOTag((OT_TYPE *)(D_800A39C8[0] + 0xC));
    PutDispEnv(&disp);
    SetDispMask(1);
    func_800596F4();
    do {
        func_80041AF0i(0);
    } while (func_80041B7C(0) != 0);
    flag = 0;
    countdown = 0x384;
    do {
        RandomScaledGetVoid();
        VSync(0);
        func_80041AF0i(0);
        buttons = func_80041B7C(0);
        if ((buttons = buttons) & 0x800 || (buttons = buttons) & 0x40 ||
            countdown == 0) {
            flag = 1;
        } else {
            countdown--;
        }
    } while (flag == 0);
    HeapFree(heap);
    func_8003F564(0, 3);
}

void func_8006F128(s32 arg0) {
    s32 pad[6];

    if (D_800A2F9CLui != 0) {
        func_8003CCE0(0);
        D_800A2F9CLui = 0;
    }
    func_8006F9C4((arg0 & 0xFF) + 0x3A, 0, 0);
    func_800596F4();
    CdSetMixVolume(((u8 *)D_800A3694Absolute)[0]);
}

extern u8 D_800A2F9CAbsolute[];
extern u8 D_800A2F9CLui asm("D_800A2F9CAbsolute");
extern u8 D_800A2F9DAbsolute[];
extern u8 D_800A3694AbsoluteU8[] asm("D_800A3694Absolute");
extern void func_8003CCE0(s32);
extern s32 func_8006F9C4(s32, s32, s32);
extern void func_800596F4(void);
void func_8006F194(s32 arg) {
    if (D_800A2F9CLui != 0) {
        func_8003CCE0(0);
        D_800A2F9CLui = 0;
    }
    func_8006F9C4((arg & 0xFF) + 0xC, 0, 0);
    func_800596F4();
    CdSetMixVolume(D_800A3694AbsoluteU8[0]);
}

extern s32 D_800A3904w16 asm("D_800A3904.NON_MATCHING");
extern u8 *func_800719FC(s32 *);
extern void func_800718D4(s32);
extern void func_80072750(void);
extern void func_80072A34(void);
extern s32 func_80072A5C(void);
extern s32 func_80072AFC(u32);
extern void func_80072CA8(u8 *);
extern void func_80073100(u8 *);
extern void func_80070750(s32);
extern void func_8007005C(void);
extern void func_80070018Args(u8 *, s32, s32);
asm(".globl func_80070018Args\nfunc_80070018Args = func_80070018");
extern void func_80041AF0Arg(s32);
asm(".globl func_80041AF0Arg\nfunc_80041AF0Arg = func_80041AF0");

s32 func_8006F200(s32 arg0, s32 arg1, u32 arg2) {
    s32 block;
    u8 *p;
    u32 w0;
    u32 w1;
    u32 magic;
    u32 size;
    s32 status;
    u32 idx;
    u32 limit;
    s32 result;
    u32 i;
    block = arg2;
    func_800719FC(&block);
    i = 0;
    result = 1;
    D_800A3904w16 = 0;
    while (1) {
        if (i >= 4) {
            func_80041AF0Arg(0);
            status = func_80041B7C(0);
            if ((status & 0x840)) {
                D_800A3904w16 = status;
                result = 0;
                break;
            }
        }
        block = 8;
        p = func_800719FC(&block);
        if (p == 0) {
            goto done;
        }
        if (block == 0) {
            goto done;
        }
        idx = 8;
        w0 = *((u32 *)p);
        magic = (((w0 >> 24) | ((w0 >> 8) & 0xFF00)) | ((w0 & 0xFF00) << 8)) |
                (w0 << 24);
        w1 = *((u32 *)(p + 4));
        size = (((w1 >> 24) | ((w1 >> 8) & 0xFF00)) | ((w1 & 0xFF00) << 8)) |
               (w1 << 24);
        if (size < 0x4400) {
            block = size;
            p = func_800719FC(&block);
            if (p == 0) {
                goto done;
            }
            if (block == 0) {
                goto done;
            }
            switch (magic) {
            case 0x564C4330:
                func_80070750((s32)(p + 8));
                break;

            case 0x41643130:

            case 0x41643131:

            case 0x61643130:

            case 0x61643131:

            case 0x61643230:

            case 0x61643231:
                func_80072CA8(p);
                break;

            case 0x61753030:

            case 0x61753031:
                func_80073100(p);
                break;

            case 0x4D444332:

            case 0x4D444543:
                idx = i;
                if (idx == 1) {
                    func_80072750();
                }
                func_80072A34();
                i = idx + 1;
                limit = func_80072AFC(idx);
                func_80070018Args(p, arg0, arg1);
                while (((u32)func_80072A5C()) < limit) {
                    VSync(0);
                }

                func_8007005C();
                break;

            default:
                block = 4;
                break;
            }

        } else {
            block = 4;
        }
        func_800718D4(block);
    }

done:
    return result;
}

INCLUDE_ASM("asm/nonmatchings/media", func_8006F4DC);

extern void CD_initvol(void);
extern void SsSetMute(s32);
/* Sound output and video. */

void SoundInitOutput(void) {
    CD_initvol();
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, 0x7FFF, 0x7FFF);
    SsSetMute(0);
}

extern u8 D_800A3394[];
extern u8 D_800A3397;
extern u8 D_800A39BC;
extern s32 func_8006F4DC(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_8006F9C4(s32 arg0, s32 arg1, s32 arg2) {
    volatile s32 pad[14];
    void *handle;

    CD_initvol();
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, 0x7FFF, 0x7FFF);
    SsSetMute(0);
    handle = FileOpen(arg0, D_800A3394);
    D_800A3397 = (u8)arg1;
    D_800A39BC = (u8)arg2;
    return func_8006F4DC((s32)handle, 1, 0x800, 0, 0xA, 1, 0xC8, 0x400) & 0xFF;
}

extern void SpuSetCommonAttr(SpuCommonAttr *);
void SoundSetMasterVolume(s16 left, s16 right) {
    SpuCommonAttr attr;
    attr.mvol.left = left;
    attr.mask = 3;
    attr.mvol.right = right;
    SpuSetCommonAttr(&attr);
}

extern s32 *D_800A3398;
extern s32 D_800A33A0;
void func_8006FAAC(void) {
    typedef struct {
        RECT unk0[2];
        s32 unk10;
        s32 unk14;
        s32 unk18;
        u16 unk1C;
        u16 unk1E;
        u16 unk20;
        u16 unk22;
        u_long *unk24;
        u8 unk28[0xF4];
        s32 unk11C;
    } StreamVram;
    volatile StreamVram *st;
    volatile StreamVram *st2;
    s16 *ex;
    s16 *ew;
    s32 xv;
    s32 a;
    s32 b;
    s32 w;
    s32 h;
    u_long *buf;
    s32 n;

    st = (volatile StreamVram *)D_800A3398;
    LoadImage((RECT *)&st->unk1C, st->unk24);
    st2 = (volatile StreamVram *)D_800A3398;
    st2->unk1C = st2->unk1C + D_800A33A0 * 8;
    xv = (s16)st2->unk1C;
    ex = &st2->unk0[st2->unk10].x;
    a = *ex;
    ew = &st2->unk0[st2->unk10].w;
    b = *ew;
    if (xv < a + b) {
        w = (s16)st2->unk20;
        h = (s16)st2->unk22;
        buf = st2->unk24;
        n = w * h;
        DecDCTout(buf, n / 2);
    } else {
        st2->unk11C = 1;
        st2->unk10 = !st2->unk10;
        st2->unk1C = (u16)st2->unk0[st2->unk10].x;
        st2->unk1E = (u16)st2->unk0[st2->unk10].y;
    }
}

extern void func_800708D8(void *, s32);
extern s32 *D_800A3398;
extern s32 D_800A339C;
extern s32 D_800A33A0;

void func_8006FBB0Args(u8 *arg0, s32 arg1, s16 arg2) {
    typedef struct {
        RECT unk0[2];
        s32 unk10;
        s32 unk14;
        s32 unk18;
        u16 unk1C;
        u16 unk1E;
        u16 unk20;
        u16 unk22;
        u_long *unk24;
        u32 unk28[2];
        s32 unk30;
        u8 unk34[0xE4];
        s32 unk118;
        s32 unk11C;
    } StreamVram;
    StreamVram *st;
    StreamVram *st2;
    register u32 bsw asm("$5");
    u32 nsec;
    u32 w8;
    u32 cnt;
    u32 word;
    register u32 wA asm("$3");
    u32 w8hi;
    u32 wAlo;
    u32 w8lo;
    u32 xv;
    u32 mdecId;
    register u32 prod asm("$10");
    volatile StreamVram *vst;
    u32 mdecId2;
    s32 magic;
    u32 h16u;
    s32 prod2;
    u_long *outp;
    s32 w32;
    s32 h32;
    u32 i;

    word = *(u32 *)arg0;
    w8 = *(u16 *)(arg0 + 8);
    st = (StreamVram *)D_800A3398;

    bsw = word >> 0x18;
    bsw = bsw | ((word >> 8) & 0xFF00);
    bsw = bsw | ((word & 0xFF00) << 8);
    magic = bsw | (word << 0x18);
    wA = *(u16 *)(arg0 + 0xA);
    asm volatile("srl %0, %1, 8" : "=r"(cnt) : "r"(wA));
    wAlo = wA & 0xFF;
    asm volatile("lhu %0, 8(%1)" : "=r"(w8) : "r"(arg0));
    wAlo = wAlo << 8;
    bsw = cnt | wAlo;
    cnt = *(s32 *)((u8 *)(st) + 0x118);
    asm volatile("srl %0, %1, 8" : "=r"(w8hi) : "r"(w8));
    w8lo = w8 & 0xFF;
    w8lo = w8lo << 8;
    nsec = w8hi | w8lo;
    if (cnt == 0) {
        wA = D_800A33A0;
        mdecId = 0x4D444543;
        asm("" : "=r"(xv) : "0"(arg1));
        st->unk0[0].x = arg1;
        st->unk0[0].y = arg2;
        st->unk0[0].h = bsw;
        st->unk0[1].y = arg2;
        st->unk0[1].h = bsw;
        asm volatile("mult %0, %1" : : "r"(nsec), "r"(wA) : "lo", "hi");
        st->unk1C = xv;
        st->unk1E = arg2;
        do {
        } while (0);
        st->unk0[1].x = arg1 + wA * 0xA0;
        st->unk20 = wA * 8;
        st->unk22 = bsw;
        st->unk10 = 0;
        asm volatile("mflo %0" : "=r"(prod));
        w8 = prod >> 1;
        st->unk0[0].w = w8;
        st->unk0[1].w = w8;
        if (magic == mdecId) {
            func_800708D8(arg0 + 0x10, (s32)st->unk28[st->unk30]);
        }
        ((volatile s32 *)D_800A3398)[0x47] = 0;
    } else {
        st->unk11C = 0;
        DecDCTin((u_long *)st->unk28[1 - st->unk30], D_800A339C);
        st2 = (StreamVram *)D_800A3398;
        asm volatile("lhu %0, 0x20(%1)" : "=r"(bsw) : "r"(st2));
        asm volatile("lhu %0, 0x22(%1)" : "=r"(h16u) : "r"(st2));
        w32 = (s16)bsw;
        h32 = (s16)h16u;
        asm volatile("mult %0, %1" : : "r"(w32), "r"(h32) : "lo", "hi");
        outp = (u_long *)st2->unk24;
        asm volatile("mflo %0" : "=r"(prod2));
        DecDCTout(outp, prod2 / 2);
        mdecId2 = 0x4D444543;
        if (magic == mdecId2) {
            st2 = (StreamVram *)D_800A3398;
            func_800708D8(arg0 + 0x10, (s32)st2->unk28[st2->unk30]);
        }
        DecDCToutSync(0);
        vst = (volatile StreamVram *)D_800A3398;
        i = 0;
        if (vst->unk11C == 0) {
            bsw = 0x30D40;
        again:
            if (i > bsw) {
                goto done;
            }
            i++;
            if (vst->unk11C == 0) {
                goto again;
            }
        }
    }
done:
    DecDCTReset(1);
    D_800A3398[0x46] = D_800A3398[0x46] + 1;
    D_800A3398[0xC] = 1 - D_800A3398[0xC];
}
asm(".globl func_8006FBB0\nfunc_8006FBB0 = func_8006FBB0Args");

extern void func_800708D8(void *, s32);
extern s32 *D_800A3398;
extern s32 D_800A339C;
extern s32 D_800A33A0;

void func_8006FDDC(u8 *arg0, s32 arg1, s16 arg2) {
    RECT rect;
    volatile s32 pad[2];
    u32 word;
    u32 wA;
    u32 w8;
    s32 magic;
    s32 height16;
    s32 output;
    u32 i;
    s32 *str;
    u32 nsectors16;
    s32 stride;

    word = *(u32 *)arg0;
    w8 = *(u16 *)(arg0 + 8);
    wA = *(u16 *)(arg0 + 0xA);
    magic = (word >> 24) | ((word >> 8) & 0xFF00) | ((word & 0xFF00) << 8) |
            (word << 0x18);
    rect.y = arg2;
    str = D_800A3398;
    height16 = (wA >> 8) | ((wA & 0xFF) << 8);
    rect.x = (u32)(arg1 * D_800A33A0) >> 1;
    nsectors16 = (w8 >> 8) | ((w8 & 0xFF) << 8);
    if (str[0x45] != 0) {
        rect.x = rect.x + D_800A33A0 * 0xA0;
    }
    rect.w = D_800A33A0 * 8;
    rect.h = height16;
    if (str[0x46] == 0) {
        if (magic == 0x4D444543) {
            func_800708D8(arg0 + 0x10,
                          *(s32 *)((s32)str + str[0xC] * 4 + 0x28));
        }
        ((volatile s32 *)D_800A3398)[0x47] = 0;
    } else {
        output = str[9];
        DecDCTin((u_long *)*(s32 *)((s32)str + (1 - str[0xC]) * 4 + 0x28),
                 D_800A339C);
        stride = D_800A33A0 * 8;
        DecDCTout((u_long *)output,
                  ((u32)(height16 * stride) >> 1) * (nsectors16 >> 4));
        if (magic == 0x4D444543) {
            func_800708D8(arg0 + 0x10, *(s32 *)((s32)D_800A3398 +
                                                D_800A3398[0xC] * 4 + 0x28));
        }
        DecDCToutSync(0);
        i = 0;
        if (nsectors16 != 0) {
            do {
                LoadImage(&rect, (u_long *)output);
                i += 0x10;
                rect.x = (u16)rect.x + D_800A33A0 * 8;
                output += rect.w * rect.h * 2;
            } while (i < nsectors16);
        }
        D_800A3398[0x47] = 1;
    }
    DecDCTReset(1);
    D_800A3398[0x46] = D_800A3398[0x46] + 1;
    D_800A3398[0xC] = 1 - D_800A3398[0xC];
}

extern s32 *D_800A3398;
void func_8006FBB0(void);
extern void func_8006FDDCNoArgs(void);
asm(".globl func_8006FDDCNoArgs\nfunc_8006FDDCNoArgs = func_8006FDDC");
void func_80070018(void) {
    if (D_800A3398[0x12C / 4])
        func_8006FBB0();
    else
        func_8006FDDCNoArgs();
}

extern s32 *D_800A3398;
void func_8007005C(void) {
    s32 *s;
    s32 *s2;
    s32 other;

    if (D_800A3398[0x11C / 4] != 0) {
        DrawSync(0);
        VSync(0);
        s = D_800A3398;
        PutDispEnv((DISPENV *)((u8 *)s + (s[0x114 / 4] * 20 + 0xEC)));
        s2 = D_800A3398;
        other = 1 - s2[0x114 / 4];
        s2[0x114 / 4] = other;
        PutDrawEnv((DRAWENV *)((u8 *)s2 + (other * 92 + 0x34)));
    }
}

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

extern u8 D_800A3397;
extern void DrawPrim(void *pri);

void func_8007012C(void) {
    s32 i;
    TILE tile;
    DRAWENV env;
    DISPENV disp;

    for (i = 0; i < 2; i++) {
        SetDefDrawEnv(&env, (0 - (i != 0)) & 0x140, 0, 0x140, 0xF0);
        PutDrawEnv(&env);
        SetDefDispEnv(&disp, (0 - (i == 0)) & 0x140, 0, 0x140, 0xF0);
        PutDispEnv(&disp);
        setBlockFill(&tile);
        tile.x0 = 0;
        tile.y0 = 0;
        tile.w = 0x140;
        tile.h = 0xF0;
        if (D_800A3397 != 0) {
            tile.r0 = 0xFF;
            tile.g0 = 0xFF;
            tile.b0 = 0xFF;
        } else {
            tile.r0 = 0;
            tile.g0 = 0;
            tile.b0 = 0;
        }
        DrawSync(0);
        VSync(0);
        DrawPrim(&tile);
        DrawSync(0);
    }
}

extern u8 D_800A3578[];
extern void SwEnterCriticalSection(void);
extern void SwExitCriticalSection(void);

void func_80070248(s32 arg0) {
    TILE tile;
    DRAWENV env;
    DISPENV disp;

    if (D_800A3398 != 0) {
        D_800A3578[0] = (u8)D_800A3398[0x45];
        DecDCTinSync(0);
        DecDCToutSync(0);
        DrawSync(0);
        SwEnterCriticalSection();
        DecDCToutCallback((void (*)(void))D_800A3398[0x48]);
        DecDCTinCallback((void (*)(void))D_800A3398[0x49]);
        DrawSyncCallback((void (*)())D_800A3398[0x4A]);
        D_800A3398[0x48] = 0;
        D_800A3398[0x49] = 0;
        D_800A3398[0x4A] = 0;
        SwExitCriticalSection();
        DecDCTReset(1);
        if (D_800A3397 == 1 && (arg0 & 0xFF)) {
            SetDefDrawEnv(&env, 0, 0, 0x140, 0xF0);
            PutDrawEnv(&env);
            setBlockFill(&tile);
            tile.w = 0x140;
            tile.h = 0xF0;
            tile.x0 = 0;
            tile.y0 = 0;
            tile.r0 = 0xFF;
            tile.g0 = 0xFF;
            tile.b0 = 0xFF;
            DrawSync(0);
            VSync(0);
            DrawPrim(&tile);
            DrawSync(0);
            SetDefDispEnv(&disp, 0, 0, 0x140, 0xF0);
            PutDispEnv(&disp);
        } else {
            SetDispMask(0);
        }
        D_800A3398 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/media", func_800703D0);

extern u8 *D_800A33A8;
extern u8 *D_800A33AC;
extern u8 D_8009B800[];
extern s32 func_80070798(u8 *first, u8 *second, u8 *table);
void func_80070750(s32 arg) {
    if (arg != 0) {
        func_80070798(D_800A33A8, D_800A33AC, (u8 *)arg);
    } else {
        func_80070798(D_800A33A8, D_800A33AC, D_8009B800);
    }
}

extern u8 D_8009B480[];
extern u8 D_8009B600[];

/* Builds two decode lookup tables: for each code entry, fills 1 << (bits - len)
   slots with the code's length (u8 array) and value (u16 array after it). */
s32 func_80070798(u8 *dst, u8 *dst2, u8 *src) {
    s32 pad[4];
    u8 *cursor;
    u16 *vals;
    s32 i;

    D_800A33A8 = dst;
    D_800A33AC = dst2;
    if (dst == 0) {
        return -1;
    }
    if (dst2 == 0) {
        return -1;
    }
    vals = (u16 *)(dst + 0x2000);
    if (src == 0) {
        src = D_8009B800;
    }
    {
        u8 *lenPtr;
        u8 *codePtr;
        s32 j;
        s32 count;
        s32 bits;
        s32 one;
        s32 base;
        s32 off;
        u16 val;
        u8 len;
        u8 *entries;

        i = 0;
        bits = 13;
        one = 1;
        entries = D_8009B480;
        codePtr = entries + 2;
        lenPtr = entries;
        cursor = src;
        while (i < 0x60) {
            val = *(u16 *)cursor;
            len = *lenPtr;
            cursor += 2;
            j = 0;
            count = one << (bits - len);
            base = *(u16 *)codePtr >> 3;
            if (count > 0) {
                do {
                    off = base | j;
                    *(u8 *)(dst + off) = len;
                    vals[off] = val;
                    j++;
                } while (j < count);
            }
            codePtr += 4;
            lenPtr += 4;
            i++;
        }
    }
    {
        u8 *lenPtr;
        u8 *codePtr;
        s32 j;
        s32 count;
        s32 bits;
        s32 one;
        s32 base;
        s32 off;
        u16 val;
        u8 len;
        u8 *entries;
        u8 *cursor2;

        dst = dst2;
        vals = (u16 *)(dst + 0x200);
        i = 0;
        bits = 9;
        one = 1;
        entries = D_8009B600;
        codePtr = entries + 2;
        lenPtr = entries;
        cursor2 = cursor;
        while (i < 0x80) {
            val = *(u16 *)cursor2;
            len = *lenPtr;
            cursor2 += 2;
            j = 0;
            count = one << (bits - len);
            base = *(u16 *)codePtr >> 7;
            if (count > 0) {
                do {
                    off = base | j;
                    *(u8 *)(dst + off) = len;
                    vals[off] = val;
                    j++;
                } while (j < count);
            }
            codePtr += 4;
            lenPtr += 4;
            i++;
        }
    }
    return 0;
}

extern u8 *D_800A33A8;
extern u8 *D_800A33AC;

extern s32 func_800708D8Ret(void *arg0, s32 arg1);
asm(".globl func_800708D8\nfunc_800708D8 = func_800708D8Ret");

s32 func_800708D8Ret(void *arg0, s32 arg1) {
    u16 *src;
    u16 *out;
    u8 *tbl1;
    u8 *tbl2;
    u16 *tbl1v;
    u16 *tbl2v;
    u32 bits;
    u32 quant;
    u32 block;
    register u32 nw asm("$7");
    register u32 nw2 asm("$4");
    u32 nwp;
    u32 sym;
    u32 len;
    u32 bitpos;
    u8 *lenp;
    u32 scale;
    u32 hdr;

    src = (u16 *)arg0;
    out = (u16 *)arg1;
    tbl1 = D_800A33A8;
    tbl2 = D_800A33AC;
    bitpos = 0;
    out[0] = src[0];
    nw = src[1];
    tbl1v = (u16 *)(tbl1 + 0x2000);
    tbl2v = (u16 *)(tbl2 + 0x200);
    out++;
    *out++ = nw;
    quant = src[2] << 10;
    nwp = src[4];
    nwp <<= 16;
    nw2 = src[5];
    bits = nwp | nw2;
    src += 6;
    block = bits >> 22;

outer_loop:
    if (block == 0x1FF)
        goto done;
    bitpos += 10;
    bits <<= 10;
    if (bitpos & 0x10) {
        nw = *src;
        bitpos &= 0xF;
        src++;
        bits |= nw << bitpos;
    } else {
        bitpos &= 0xF;
    }
    hdr = block | quant;
    *out++ = hdr;
inner_loop:
    block = bits >> 19;
    if (block < 0x20) {
        bitpos += 8;
        bits <<= 8;
        if (bitpos & 0x10) {
            nw2 = *src;
            bitpos &= 0xF;
            src++;
            bits |= nw2 << bitpos;
        } else {
            bitpos &= 0xF;
        }
        block = bits >> 23;
        lenp = tbl2 + block;
        scale = block * 2;
        nw = (u32)((u8 *)tbl2v + scale);
    } else {
        lenp = tbl1 + block;
        scale = block * 2;
        nw = (u32)((u8 *)tbl1v + scale);
    }
    sym = *(u16 *)nw;
    do {
    } while (0);
    len = *lenp;
    bits <<= len;
    bitpos += len;
    if (bitpos & 0x10) {
        nw2 = *src;
        bitpos &= 0xF;
        src++;
        bits |= nw2 << bitpos;
    } else {
        bitpos &= 0xF;
    }
    if (sym == 0x7C1F)
        goto escape;
    *out++ = sym;
    if (sym != 0xFE00)
        goto inner_loop;
    block = bits >> 22;
    goto outer_loop;
escape:
    *out++ = bits >> 16;
    nw2 = *src++;
    bits <<= 16;
    bits |= nw2 << bitpos;
    goto inner_loop;
done:
    bits = 0x40;
    do {
        *out++ = 0xFE00;
        bits--;
    } while (bits != 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/media", func_80070A60);

extern s32 *D_800A3500;

void func_80070F40(u_char intr, u_char *result) {
    volatile s32 *stream;
    volatile s32 *p;
    s32 cmd;
    s32 parm;
    s32 first;
    s32 second;
    s32 third;
    s32 pad;

    if (intr != CdlComplete) {
        ((volatile s32 *)D_800A3500)[0x424 / 4] =
            ((volatile s32 *)D_800A3500)[0x424 / 4] + 1;
        ((volatile s32 *)D_800A3500)[0x424 / 4];
        return;
    }
    stream = (volatile s32 *)D_800A3500;
    if ((u32)stream[0x424 / 4] < 2) {
        stream[0x424 / 4] = 0;
        if (stream[0x41C / 4] == 0)
            return;
        if (stream[0x410 / 4] == 0)
            return;
        if (stream[0x418 / 4] != 0) {
            stream[0x418 / 4] = stream[0x418 / 4] - 1;
            pad = stream[0x418 / 4];
            if (stream[0x418 / 4] == 0) {
                first = stream[0x450 / 4];
                second = stream[0x454 / 4];
                stream[0x4 / 4] = first;
                stream[0x0 / 4] = second;
                stream[0x414 / 4] = intr;
            }
        }
        stream = (volatile s32 *)D_800A3500;
        stream[0x410 / 4] = stream[0x410 / 4] - 1;
        pad = stream[0x410 / 4];
        stream[0x408 / 4] = stream[0x408 / 4] + 3;
        stream[0x408 / 4] = (u32)stream[0x408 / 4] % 48;
        if (stream[0x410 / 4] != 0) {
            third = stream[stream[0x408 / 4] + 2];
            p = stream + stream[0x408 / 4];
            parm = p[3];
            cmd = third;
            p = stream + stream[0x408 / 4];
            pad = p[4];
            while (CdControlF((u_char)cmd, (u_char *)parm) == 0) {
            }
        }
    }
}

extern s32 D_800A3504;
extern s32 D_800A3508;
extern s32 D_800A350C;
s32 func_800710D8(void) {
    s32 *stream;
    register s32 *base asm("a0");
    u32 index;
    s32 *record;
    s32 *reset;
    s32 *last;
    s32 *lastRecord;
    s32 status;

    stream = D_800A3500;
    status = stream[0x43C / 4];
    if (status != 0) {
        return status;
    }
    index = stream[0x434 / 4];
    if (index < (u32)stream[0x438 / 4]) {
        record = (s32 *)(D_800A3504 + index * 0x38);
        stream[0x430 / 4] = (s32)record;
        if (stream[0x42C / 4] == 0) {
            stream[0x42C / 4] = (s32)record;
        }
        base = D_800A3500;
        record = (s32 *)base[0x430 / 4];
        record[0] = (u32)(record[0x10 / 4] + 0x7FF) >> 11;
        reset = (s32 *)base[0x430 / 4];
        reset[1] = 0;
        reset = (s32 *)base[0x430 / 4];
        reset[2] = 0;
        reset = (s32 *)base[0x430 / 4];
        reset[0x28 / 4] = 0;
        if (base[0x434 / 4] == 0) {
            base[0x444 / 4] = 0;
            base[0x440 / 4] = 0;
            base[0x448 / 4] = 0;
            base[0x44C / 4] = 0;
        }
        last = D_800A3500;
        last[0x434 / 4] += 1;
        lastRecord = (s32 *)last[0x430 / 4];
        lastRecord[0x34 / 4] = 0;
        lastRecord = (s32 *)last[0x430 / 4];
        lastRecord[0x2C / 4] = D_800A3508;
        lastRecord = (s32 *)last[0x430 / 4];
        lastRecord[0x30 / 4] = D_800A350C;
        last[0x43C / 4] = 0;
    } else {
        stream[0x43C / 4] = 2;
    }
    return D_800A3500[0x43C / 4];
}

INCLUDE_ASM("asm/nonmatchings/media", func_800711F0);

/* All registers match after separating stream phases and reloading the
 * global stream before the tail update. An empty compiler barrier keeps the
 * fast-path store out of the jump delay slot. */
extern s32 *D_800A3500;
extern void func_800711F0(void);
void func_800718D4(s32 arg) {
    s32 remaining;
    s32 offset;
    s32 blocks;
    s32 oldBlocks;
    s32 *stream;
    s32 *node;
    s32 *tail;
    s32 *tailNode;
    s32 *current;
    s32 *after;
    stream = D_800A3500;
    node = (s32 *)stream[0x42C / 4];
    do {
        offset = stream[0x444 / 4];
        do {
            node[0x4 / 4] += arg;
        } while (0);
    } while (0);
    remaining = 0x800 - offset;
    if (arg < remaining) {
        do {
            stream[0x444 / 4] = stream[0x444 / 4] + arg;
            asm volatile("");
        } while (0);
    } else {
        arg -= remaining;
        do {
            stream[0x444 / 4] = arg & 0x7FF;
        } while (0);
        oldBlocks = stream[0x440 / 4];
        blocks = (((u32)arg) >> 11) + 1;
        stream[0x440 / 4] = oldBlocks + blocks;
    }
    func_800711F0();
    after = D_800A3500;
    current = (s32 *)after[0x42C / 4];
    if (current[0x4 / 4] == current[0x10 / 4]) {
        if (((s32 *)after[0x430 / 4]) != current) {
            if (after[0x444 / 4] != 0) {
                after[0x440 / 4] += 1;
            }
            tail = D_800A3500;
            tailNode = (s32 *)tail[0x430 / 4];
            tail[0x44C / 4] = 0;
            tail[0x42C / 4] = (s32)tailNode;
            tail[0x444 / 4] = tailNode[0x28 / 4];
        }
    }
}

extern s32 *D_800A3500;
s32 func_800719D4(void) {
    return (D_800A3500[0x448 / 4] << 11) -
           ((D_800A3500[0x440 / 4] << 11) + D_800A3500[0x444 / 4]);
}

extern s32 *D_800A3500;
extern u32 D_800A3510w asm("D_800A3510.NON_MATCHING");
extern void func_800711F0(void);
extern void *memcpy(void *, const void *, size_t);

u8 *func_800719FC(s32 *arg0) {
    volatile s32 *stream;
    volatile s32 *pre;
    s32 *head;
    s32 room;
    s32 avail;
    u32 counter;
    u32 retries;
    u32 x;
    u32 w;
    u32 left;
    u32 tail;
    u32 size;
    u32 first;
    u32 second;
    s32 *node;
    u32 third;
    u8 *result;
    head = (s32 *)((volatile s32 *)D_800A3500)[0x42C / 4];
    room = head[0x10 / 4] - head[0x4 / 4];
    *arg0 = ((*arg0) > room) ? (room) : (*arg0);
    pre = (volatile s32 *)D_800A3500;
    counter = 0;
    retries = 0;
    pre[0x448 / 4];
    pre[0x440 / 4];
    pre[0x444 / 4];
    for (;;) {
        stream = (volatile s32 *)D_800A3500;
        avail = (stream[0x448 / 4] << 11) -
                ((stream[0x440 / 4] << 11) + stream[0x444 / 4]);
        if (avail < 0) {
            avail = (x = 0);
        }
        if (avail < (*arg0)) {
            if (stream[0x43C / 4] != 0) {
                return 0;
            }
            counter = counter + 1;
            if (counter > 4000000) {
                stream[0x424 / 4] = stream[0x424 / 4] + 2;
            }
            if (((volatile s32 *)D_800A3500)[0x414 / 4] != 0) {
                if (((u32)((volatile s32 *)D_800A3500)[0x424 / 4]) < 2) {
                    continue;
                }
            }
            retries = retries + 1;
            if (retries >= 3) {
                return 0;
            }
            counter = 0;
            func_800711F0();
            continue;
        }
        break;
    }

    {
        node = (s32 *)((volatile s32 *)D_800A3500)[0x42C / 4];
        first = ((volatile s32 *)D_800A3500)[0x440 / 4];
        second = ((volatile s32 *)D_800A3500)[0x444 / 4];
        x = ((u32)(((volatile s32 *)D_800A3500)[0x440 / 4] + node[0x34 / 4])) %
            D_800A3510w;
        w = ((u32)first) % D_800A3510w;
        third = ((volatile s32 *)D_800A3500)[0x444 / 4];
        result = (u8 *)(node[0x30 / 4] + ((x << 11) + third));
        left = D_800A3510w - 1;
        tail = ((left - w) << 11) + 0x800;
        size = tail - second;
        if (size < (*arg0)) {
            memcpy(result - (D_800A3510w << 11), result, size);
            result = result - (D_800A3510w << 11);
        }
        return result;
    }
}

extern void bzero(void *, s32);
extern void func_80070F40(u_char, u_char *);
extern void func_80070A60(u_char, u_char *);
extern void SwEnterCriticalSection(void);
extern void SwExitCriticalSection(void);

void func_80071BE8(void) {
    u8 param[0x20];
    u8 result[0x20];
    u8 *resultPtr;
    u8 *resultPtr2;
    u32 i;
    s32 timedOut;
    s32 status;
    s32 retry;
    s32 mode;

    timedOut = 0;
    i = 0;
    if (D_800A3500[0x414 / 4] != 0) {
        do {
            VSync(0);
            i++;
            if (i >= 0xB5) {
                timedOut = 1;
                break;
            }
        } while (D_800A3500[0x414 / 4] != 0);
    }
    if (timedOut == 0) {
        i = 0;
        if (D_800A3500[0] != 0) {
            do {
                VSync(0);
                i++;
                if (i >= 0xB5) {
                    timedOut = 1;
                    break;
                }
            } while (D_800A3500[0] != 0);
        }
        if (timedOut == 0) {
            return;
        }
    }
    i = CdlComplete;
    SwEnterCriticalSection();
    ((volatile s32 *)D_800A3500)[0x410 / 4] = 0;
    ((volatile s32 *)D_800A3500)[0x408 / 4] = 0;
    ((volatile s32 *)D_800A3500)[0x40C / 4] = 0;
    ((volatile s32 *)D_800A3500)[0x41C / 4] = 0;
    CdSyncCallback(0);
    CdReadyCallback(0);
    SwExitCriticalSection();
    CdControl(CdlStop, 0, 0);
    do {
        bzero(param, 0x20);
        resultPtr = result;
        bzero(resultPtr, 0x20);
        resultPtr = 0;
        resultPtr2 = result;
        status = CdControl(CdlNop, param, resultPtr2);
        resultPtr2 = 0;
        if (status != 0) {
            if (result[0] == CdlNoIntr || result[0] == i) {
                retry = 0;
            } else {
                retry = 1;
            }
        } else {
            CdControl(CdlReset, 0, 0);
            retry = 1;
        }
    } while (retry);
    mode = CdlModeSpeed | CdlModeSize1;
    CdControlB(CdlSetmode, (u_char *)&mode, 0);
    SwEnterCriticalSection();
    CdSyncCallback(func_80070F40);
    CdReadyCallback(func_80070A60);
    D_800A3500[0x41C / 4] = 1;
    D_800A3500[0x424 / 4] = 2;
    ((volatile s32 *)D_800A3500)[0x414 / 4] = 0;
    SwExitCriticalSection();
}

extern s32 *D_800A3500;
extern s32 D_800A33B8, D_800A33BC;
extern void func_80070F40(u_char, u_char *);
extern void func_80070A60(u_char, u_char *);
extern void SwEnterCriticalSection(void);
extern void SwExitCriticalSection(void);
void func_80071DCC(s32 enable) {
    u8 mode;
    s32 enabled;

    if (enable != 0) {
        CdSync(0, 0);
        mode = CdlModeSpeed | CdlModeSize1;
        CdControlB(CdlSetmode, &mode, 0);
        SwEnterCriticalSection();
        D_800A3500[0x410 / 4] = 0;
        D_800A3500[0x408 / 4] = 0;
        ((volatile s32 *)D_800A3500)[0x40C / 4] = 0;
        D_800A33B8 = (s32)CdSyncCallback(func_80070F40);
        D_800A33BC = (s32)CdReadyCallback(func_80070A60);
        D_800A3500[0x420 / 4] = 1;
        ((volatile s32 *)D_800A3500)[0x41C / 4] = 1;
    } else {
        SwEnterCriticalSection();
        enabled = D_800A3500[0x420 / 4];
        D_800A3500[0x41C / 4] = 0;
        D_800A3500[0x410 / 4] = 0;
        D_800A3500[0x408 / 4] = 0;
        ((volatile s32 *)D_800A3500)[0x40C / 4] = 0;
        if (enabled != 0) {
            CdSyncCallback((void *)D_800A33B8);
            CdReadyCallback((void *)D_800A33BC);
            D_800A33B8 = 0;
            D_800A33BC = 0;
            D_800A3500[0x420 / 4] = 0;
        }
    }
    SwExitCriticalSection();
}

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

extern s32 D_800A3504;
extern s32 D_800A3508;
extern s32 D_800A350C;
s32 func_80071EEC(s32 *mem, s32 arg1, s32 *src, u32 count) {
    typedef struct {
        s32 w[6];
    } SixWords;
    s32 mode;
    s32 pad1;
    s32 pad2;
    s32 len;
    s32 temp;
    s32 end;
    s32 off;
    u32 i;
    s32 *srcp;
    s32 *dstp;

    len = D_800A3510;
    len <<= 11;
    len += 0x57C;
    (void)&mode;
    (void)&pad1;
    (void)&pad2;
    bzero(mem, D_800A3514 + len + D_800A3518 * 56);
    temp = (s32)mem + 0x57C;
    D_800A3500 = mem;
    D_800A3504 = temp;
    mem[0x570 / 4] = arg1;
    mem[0x414 / 4] = 0;
    mem[0x418 / 4] = 0;
    mem[0x41C / 4] = 0;
    mem[0x43C / 4] = 0;
    mem[0x434 / 4] = 0;
    mem[0x430 / 4] = 0;
    mem[0x42C / 4] = 0;
    mem[0x440 / 4] = 0;
    mem[0x448 / 4] = 0;
    mem[0x44C / 4] = 0;
    end = temp + D_800A3518 * 56;
    D_800A3508 = end;
    D_800A350C = end + D_800A3514;
    if (count != 0) {
        i = 0;
        srcp = src;
        off = 0;
    again:
        dstp = (s32 *)(off + D_800A3504);
        *(SixWords *)&dstp[3] = *(SixWords *)srcp;
        srcp += 6;
        off += 0x38;
        i++;
        if (i < count) {
            goto again;
        }
    }
    ((volatile s32 *)D_800A3500)[0x438 / 4] = count;
    ((volatile s32 *)D_800A3500)[0x424 / 4] = 0;
    ((volatile s32 *)D_800A3500)[0x428 / 4] = 0;
    do {
    } while (0);
    D_800A3500[0x574 / 4] = (s32)CdDataCallback(0);
    D_800A3500[0x578 / 4] = (s32)CdReadCallback(0);
    func_800710D8();
    CdSync(0, 0);
    *(u8 *)&mode = CdlModeSpeed | CdlModeSize1;
    CdControlB(CdlSetmode, (u_char *)&mode, 0);
    SwEnterCriticalSection();
    D_800A3500[0x410 / 4] = 0;
    D_800A3500[0x408 / 4] = 0;
    ((volatile s32 *)D_800A3500)[0x40C / 4] = 0;
    D_800A33B8 = (s32)CdSyncCallback(func_80070F40);
    D_800A33BC = (s32)CdReadyCallback(func_80070A60);
    D_800A3500[0x420 / 4] = 1;
    ((volatile s32 *)D_800A3500)[0x41C / 4] = 1;
    SwExitCriticalSection();
    return 1;
}

extern s32 D_800A33B8, D_800A33BC;
void func_800720D0(void) {
    s32 enabled;
    s32 pad[2];

    if (D_800A3500[0x420 / 4] != 0) {
        CdDataCallback((void *)D_800A3500[0x574 / 4]);
        CdReadCallback((void *)D_800A3500[0x578 / 4]);
        SwEnterCriticalSection();
        enabled = D_800A3500[0x420 / 4];
        D_800A3500[0x41C / 4] = 0;
        D_800A3500[0x410 / 4] = 0;
        D_800A3500[0x408 / 4] = 0;
        ((volatile s32 *)D_800A3500)[0x40C / 4] = 0;
        if (enabled != 0) {
            CdSyncCallback((void *)D_800A33B8);
            CdReadyCallback((void *)D_800A33BC);
            D_800A33B8 = 0;
            D_800A33BC = 0;
            D_800A3500[0x420 / 4] = 0;
        }
        SwExitCriticalSection();
    }
}

extern volatile s32 *D_800A351C;
void func_80072178(void) {
    u8 *src;
    s32 value;
    u32 i;
    s32 old;
    s32 base;
    s32 count;

    if (D_800A351C[0x7B48 / 4] == 1) {
        src = (u8 *)D_800A351C[0x7B50 / 4];
        value = D_800A351C[0x7B54 / 4];
        for (i = 0; i < 0x300; i += 0x10) {
            src[i + 1] = 2;
        }
        if ((D_800A351C[0x7B44 / 4] & 3) == 0) {
            src[1] = 6;
        } else if (((D_800A351C[0x7B44 / 4] + 1) & 3) == 0) {
            src[0x2F1] = 3;
        }
        D_800A351C[0x7B2C / 4 + (D_800A351C[0x7B44 / 4] & 3)] = value;
        old = D_800A351C[0x7B44 / 4];
        base = D_800A351C[0x7B60 / 4];
        D_800A351C[0x7B44 / 4] = D_800A351C[0x7B44 / 4] + 1;
        count = D_800A351C[0x7B44 / 4];
        base += (old & 3) * 0x300;
        SpuSetTransferMode(0);
        SpuSetTransferStartAddr(base);
        SpuWrite(src, 0x300);
        D_800A351C[0x7B48 / 4] = 2;
    } else if (D_800A351C[0x7B48 / 4] == 2) {
        volatile s32 *spu;
        spu = D_800A351C;
        spu[0x7B48 / 4] = 0;
        if (spu[0x7B4C / 4] != 0) {
            spu[0] += 0x300;
            spu[0x7B4C / 4] = 0;
        }
    }
}

extern volatile s32 *D_800A351C;
extern void SpuSetIRQ(s32);
extern void SpuSetIRQAddr(s32);
extern void SpuSetTransferStartAddr(s32);
void func_800722D0(void) {
    u8 *src;
    s32 addr;
    s32 addr2;
    u32 value;
    u32 i;
    s32 mode;
    s32 result;
    s32 base;
    s32 fallback;

    SpuSetIRQ(0);
    SpuSetIRQCallback(0);
    if (D_800A351C[0x7B48 / 4] == 0 &&
        D_800A351C[0x7B44 / 4] * 2 - D_800A351C[0x7B40 / 4] < 6) {
        u32 size;

        size = 0x300;
        if ((u32)(D_800A351C[1] - D_800A351C[0]) > size &&
            D_800A351C[0x7B78 / 4] == 0) {
            addr =
                (s32)((u8 *)D_800A351C + ((u32)D_800A351C[0] % 0x3C00 + 0x10));
        } else {
            addr = 0;
        }
        src = (u8 *)addr;
        if (src != 0) {
            u32 size;

            size = 0x300;
            if ((u32)(D_800A351C[1] - D_800A351C[0]) > size &&
                D_800A351C[0x7B78 / 4] == 0) {
                addr2 = (s32)((u8 *)D_800A351C +
                              ((u32)D_800A351C[0] % 0x3C00 + 0x3C10));
            } else {
                addr2 = 0;
            }
            D_800A351C[0x7B58 / 4] = 1;
            D_800A351C[0x7B4C / 4] = 1;
            D_800A351C[0x7B48 / 4] = 1;
            D_800A351C[0x7B50 / 4] = addr2;
            D_800A351C[0x7B54 / 4] = D_800A351C[0x7B3C / 4];
            value = D_800A351C[0x7B3C / 4];
            for (i = 0; i < 0x300; i += 0x10) {
                src[i + 1] = 2;
            }
            if ((D_800A351C[0x7B44 / 4] & 3) == 0) {
                src[1] = 6;
            } else if (((D_800A351C[0x7B44 / 4] + 1) & 3) == 0) {
                src[0x2F1] = 3;
            }
            D_800A351C[0x7B2C / 4 + (D_800A351C[0x7B44 / 4] & 3)] = value;
            {
                s32 idx;

                idx = D_800A351C[0x7B44 / 4];
                base = D_800A351C[0x7B5C / 4];
                base += (idx & 3) * 0x300;
                SpuSetTransferMode(0);
                SpuSetTransferStartAddr(base);
                SpuWrite(src, 0x300);
                D_800A351C[0x7B3C / 4] = D_800A351C[0x7B3C / 4] + 0x300;
            }
        } else {
            u8 *buf;

            fallback = (s32)((u8 *)D_800A351C + 0x7810);
            D_800A351C[0x7B58 / 4] = 0;
            D_800A351C[0x7B4C / 4] = 0;
            D_800A351C[0x7B48 / 4] = 1;
            D_800A351C[0x7B50 / 4] = fallback;
            buf = (u8 *)fallback;
            D_800A351C[0x7B54 / 4] = 0;
            for (i = 0; i < 0x300; i += 0x10) {
                buf[i + 1] = 2;
            }
            if ((D_800A351C[0x7B44 / 4] & 3) == 0) {
                buf[1] = 6;
            } else if (((D_800A351C[0x7B44 / 4] + 1) & 3) == 0) {
                buf[0x2F1] = 3;
            }
            D_800A351C[0x7B2C / 4 + (D_800A351C[0x7B44 / 4] & 3)] = 0;
            {
                s32 idx;

                idx = D_800A351C[0x7B44 / 4];
                base = D_800A351C[0x7B5C / 4];
                base += (idx & 3) * 0x300;
                SpuSetTransferMode(0);
                SpuSetTransferStartAddr(base);
                SpuWrite(buf, 0x300);
            }
        }
    }
    if ((D_800A351C[0x7B40 / 4] & 1) == 0) {
        value = *(u32 *)((u8 *)D_800A351C + 0x7B2C +
                         ((D_800A351C[0x7B40 / 4] * 2) & 0xC));
        if (value != 0) {
            mode = D_800A351C[0x7B74 / 4];
            result = 0;
            if (mode != 0) {
                if (mode == 1) {
                    result =
                        (s32)((long long)((unsigned long long)value * 0x40) /
                              0x3F);
                }
            } else {
                if (D_800A351C[0x7B7C / 4] == 0x800) {
                    result =
                        (s32)((long long)((unsigned long long)value * 0x14D0) /
                              0x1117);
                } else {
                    result =
                        (s32)((long long)((unsigned long long)value * 0x6D440) /
                              0x82BA3);
                }
            }
            D_800A351C[0x7B24 / 4] = result;
        }
    }
    D_800A351C[0x7B40 / 4] = D_800A351C[0x7B40 / 4] + 1;
    D_800A351C[0x7B40 / 4];
    SpuSetIRQAddr(D_800A351C[0x7B5C / 4] +
                  (D_800A351C[0x7B40 / 4] & 7) * 0x180);
    SpuSetIRQCallback(func_800722D0);
    SpuSetIRQ(1);
}

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

void func_80072750(void) {
    u8 *src;
    s32 addr;
    s32 addr2;
    u32 size;
    u32 i;
    u32 j;
    s32 base;

    if (D_800A351C[2] == 0) {
        D_800A351C[0x7B3C / 4] = 0x300;
        for (i = 0; i < 3; i++) {
            size = 0x300;
            if ((u32)(D_800A351C[1] - D_800A351C[0]) > size &&
                D_800A351C[0x7B78 / 4] == 0) {
                addr = (s32)((u8 *)D_800A351C +
                             ((u32)D_800A351C[0] % 0x3C00 + 0x10));
            } else {
                addr = 0;
            }
            src = (u8 *)addr;
            if (src != 0) {
                if ((u32)(D_800A351C[1] - D_800A351C[0]) > size &&
                    D_800A351C[0x7B78 / 4] == 0) {
                    addr2 = (s32)((u8 *)D_800A351C +
                                  ((u32)D_800A351C[0] % 0x3C00 + 0x3C10));
                } else {
                    addr2 = 0;
                }
                addr = addr2;
            } else {
                src = (u8 *)D_800A351C + 0x7810;
                addr = (s32)src;
            }
            j = 0;
            D_800A351C[0x7B48 / 4] = 1;
            D_800A351C[0x7B4C / 4] = 1;
            D_800A351C[0x7B50 / 4] = addr;
            D_800A351C[0x7B54 / 4] = 1;
            addr = D_800A351C[0x7B3C / 4];
            for (; j < 0x300; j += 0x10) {
                src[j + 1] = 2;
            }
            if ((D_800A351C[0x7B44 / 4] & 3) == 0) {
                src[1] = 6;
            } else if (((D_800A351C[0x7B44 / 4] + 1) & 3) == 0) {
                src[0x2F1] = 3;
            }
            D_800A351C[0x7B2C / 4 + (D_800A351C[0x7B44 / 4] & 3)] = addr;
            base =
                D_800A351C[0x7B5C / 4] + (D_800A351C[0x7B44 / 4] & 3) * 0x300;
            SpuSetTransferMode(0);
            SpuSetTransferStartAddr(base);
            SpuWrite(src, 0x300);
            D_800A351C[0x7B3C / 4] += 0x300;
            do {
            } while (D_800A351C[0x7B48 / 4] != 0);
        }
        D_800A351C[0x7B48 / 4] = 3;
        func_800722D0();
        D_800A351C[0x7B48 / 4] = 0;
        D_800A351C[2] = 1;
    }
    D_800A351C[0x7B6C / 4] = SpuSetReverbVoice(0, D_800A351C[0x7B64 / 4]);
    D_800A351C[0x7B70 / 4] = SpuSetReverbVoice(0, D_800A351C[0x7B68 / 4]);
    SpuSetKey(1, D_800A351C[0x7B64 / 4] | D_800A351C[0x7B68 / 4]);
}

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

extern volatile s32 *D_800A351C;
s32 func_80072A70(void) {
    u32 val;
    long long q;
    s32 mode;

    val = D_800A351C[0x7B24 / 4];
    q = (long long)val * 100 / 0x100;
    /* Retail reloads the pointer after the libcall; gcc treats it as const. */
    mode = (*(volatile s32 *volatile *)&D_800A351C)[0x7B74 / 4];
    if (mode != 0) {
        if (mode == 1) {
            q /= 0x1388;
        }
    } else {
        q /= 0x176A;
    }
    return (s32)q;
}

extern volatile s32 *D_800A351C;
/* Enabled after the maspsx li-$reg,0 wrapper fix; see matching.md. */
extern long long __divdi3(long long dividend, long long divisor);
extern volatile s32 *D_800A351C;
extern long long __divdi3(long long dividend, long long divisor);
s32 func_80072AFC(u32 arg) {
    if (D_800A351C[0x7B74 / 4] == 1) {
        return (long long)arg * 0x271000 / 0xBB5;
    }
    return arg << 10;
}

extern volatile s32 *D_800A351C;
s32 func_80072B4C(void) {
    u16 flag;
    volatile s32 *p;
    u32 i;
    s32 count;
    count = 0;
    i = 0;
    p = D_800A351C;
    do {
        flag = p[0x7B2C / 4] != 0;
        if (flag) {
            flag = 1;
            count += flag;
        }
        i += 1;
        p += 1;
    } while (i < 4);
    return count;
}

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

#define SWAP32(w)                                                              \
    (((w) >> 24) | (((w) >> 8) & 0xFF00) | (((w) & 0xFF00) << 8) | ((w) << 24))

u32 func_80072BDC(u32 *header) {
    u32 swapped;
    u32 size;
    u32 isAd2;

    swapped = SWAP32(header[0]);
    isAd2 = (swapped & 0xFFFFFF00) == 0x61643200;
    if ((swapped & 0xFFFF0000) == 0x61640000) {
        size = SWAP32(header[1]) - 0x10;
    } else {
        size = SWAP32(header[1]) - 0xC;
    }
    if (isAd2) {
        size >>= 1;
    }
    return size;
}

INCLUDE_ASM("asm/nonmatchings/media", func_80072CA8);

void func_80072FE4(u8 *dst, u8 *src, u32 n) {
    u32 i;

    for (i = 0; i < n; i += 15) {
        *dst++ = *src++;
        *dst++ = 0;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
    }
}

INCLUDE_ASM("asm/nonmatchings/media", func_80073100);

extern volatile s32 *D_800A351C;
void func_80073948(void) {
    volatile s32 *p;
    volatile s32 *field;
    u32 i;

    i = 0;
    p = D_800A351C;
    p[0x7B78 / 4] = 1;
    field = p;
    do {
        field[0x7B2C / 4] = 0;
        i += 1;
        field += 1;
    } while (i < 4);
}

extern volatile s32 *D_800A351C;
void func_80073978(void) {
    D_800A351C[0x7B78 / 4] = 0;
}

extern volatile s32 *D_800A351C;
extern void SwEnterCriticalSection(void);
extern void SwExitCriticalSection(void);

void func_8007398C(void) {
    volatile s32 *field;
    volatile s32 *p;
    u32 i;

    SwEnterCriticalSection();
    i = 0;
    p = D_800A351C;
    p[0] = 0;
    p[1] = 0;
    p[3] = 0;
    field = p;
    do {
        field[0x7B2C / 4] = 0;
        i += 1;
        field += 1;
    } while (i < 4);
    SwExitCriticalSection();
}

void func_800739E0(void) {
    volatile s32 *field;
    volatile s32 *p;
    u32 i;

    SwEnterCriticalSection();
    i = 0;
    p = D_800A351C;
    p[0] = 0;
    p[1] = 0;
    p[3] = 0;
    field = p;
    do {
        field[0x7B2C / 4] = 0;
        i += 1;
        field += 1;
    } while (i < 4);
    D_800A351C[0x7B3C / 4] = 1;
    D_800A351C[0x7B24 / 4] = 0;
    SwExitCriticalSection();
}

extern void SpuSetReverbVoice(s32, s32);

void func_80073A44(void) {
    SpuSetKey(0, D_800A351C[0x7B64 / 4] | D_800A351C[0x7B68 / 4]);
    SpuSetReverbVoice(D_800A351C[0x7B6C / 4], D_800A351C[0x7B64 / 4]);
    SpuSetReverbVoice(D_800A351C[0x7B70 / 4], D_800A351C[0x7B68 / 4]);
}

extern void *SpuSetTransferCallback(void *);

void func_80073AA4(void) {
    volatile s32 *field;
    volatile s32 *p;
    u32 i;

    SwEnterCriticalSection();
    SpuSetKey(0, D_800A351C[0x7B64 / 4] | D_800A351C[0x7B68 / 4]);
    SpuSetReverbVoice(D_800A351C[0x7B6C / 4], D_800A351C[0x7B64 / 4]);
    SpuSetReverbVoice(D_800A351C[0x7B70 / 4], D_800A351C[0x7B68 / 4]);
    SpuSetIRQ(0);
    SpuSetIRQCallback((SpuIRQCallbackProc)D_800A351C[0x7B14 / 4]);
    SpuSetTransferCallback((void *)D_800A351C[0x7B18 / 4]);
    D_800A351C[0x7B20 / 4] = 0;
    if (D_800A351C[0x7B1C / 4] != 0) {
        VSyncCallback((Callback)D_800A351C[0x7B10 / 4]);
    }
    D_800A351C[0x7B24 / 4] = 0;
    SwExitCriticalSection();
    SwEnterCriticalSection();
    i = 0;
    p = D_800A351C;
    p[0] = 0;
    p[1] = 0;
    p[3] = 0;
    field = p;
    do {
        field[0x7B2C / 4] = 0;
        i += 1;
        field += 1;
    } while (i < 4);
    D_800A351C[0x7B3C / 4] = 1;
    D_800A351C[0x7B24 / 4] = 0;
    SwExitCriticalSection();
}

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

extern void bzero(void *, s32);
extern void *SpuSetTransferCallback(void *);

s32 func_80073BEC(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                  s32 arg6) {
    SpuVoiceAttr va;
    SpuCommonAttr ca;
    SpuCommonAttr *caarg;
    u32 off;
    register s32 voice asm("$16");
    s32 addr;
    u8 val;
    s32 base;

    if (arg0 == 0) {
        goto bail;
    }
    if (arg2 == 0) {
        goto bail;
    }
    if (arg4 == 0) {
        goto bail;
    }
    if (arg1 == 0) {
        goto bail;
    }
    if (arg3 == 0) {
        goto bail;
    }
    D_800A351C = (volatile s32 *)arg0;
    bzero(arg0, 0x7B80);
    off = 0;
    val = 2;
    do {
        ((u8 *)D_800A351C + off)[0x7811] = val;
        off = off + 0x10;
    } while (off < 0x300);
    D_800A351C[0x7B3C / 4] = 1;
    D_800A351C[0x7B58 / 4] = 0;
    D_800A351C[0x7B5C / 4] = arg2;
    D_800A351C[0x7B60 / 4] = arg4;
    D_800A351C[0x7B64 / 4] = arg1;
    D_800A351C[0x7B68 / 4] = arg3;
    D_800A351C[0x7B7C / 4] = arg5;
    voice = D_800A351C[0x7B64 / 4];
    addr = D_800A351C[0x7B5C / 4];
    ca.mask = 3;
    ca.mvol.left = 0x3FFF;
    ca.mvol.right = 0x3FFF;
    SpuSetCommonAttr(&ca);
    va.mask = 0xFF93;
    va.voice = voice;
    va.volume.left = -(voice == D_800A351C[0x7B64 / 4]) & 0x3FFF;
    va.volume.right = -(voice == D_800A351C[0x7B68 / 4]) & 0x3FFF;
    va.pitch = arg5;
    va.addr = addr;
    va.a_mode = 1;
    va.s_mode = 1;
    va.r_mode = 3;
    va.ar = 0;
    va.dr = 0;
    va.sr = 0;
    va.rr = 0;
    va.sl = 0xF;
    SpuSetVoiceAttr(&va);
    voice = D_800A351C[0x7B68 / 4];
    addr = (base = D_800A351C[0x7B60 / 4]);
    {
        asm volatile("addiu %0, $sp, 0x50" : "=r"(caarg));
        ca.mask = 3;
        ca.mvol.left = 0x3FFF;
        ca.mvol.right = 0x3FFF;
        SpuSetCommonAttr(caarg);
        va.mask = 0xFF93;
        va.voice = voice;
        va.volume.left = -(voice == D_800A351C[0x7B64 / 4]) & 0x3FFF;
        va.volume.right = -(voice == D_800A351C[0x7B68 / 4]) & 0x3FFF;
        va.pitch = arg5;
        va.addr = addr;
        va.a_mode = 1;
        va.s_mode = 1;
        va.r_mode = 3;
        va.ar = 0;
        va.dr = 0;
        va.sr = 0;
        va.rr = 0;
        va.sl = 0xF;
        SpuSetVoiceAttr(&va);
    }
    SwEnterCriticalSection();
    D_800A351C[0x7B14 / 4] = (s32)SpuSetIRQCallback(0);
    D_800A351C[0x7B18 / 4] = (s32)SpuSetTransferCallback(func_80072178);
    D_800A351C[0x7B1C / 4] = arg6;
    if (arg6 != 0) {
        D_800A351C[0x7B10 / 4] =
            (s32)((Callback (*)(Callback))VSyncCallback)(func_8007270C);
    } else {
        D_800A351C[0x7B10 / 4] = 0;
    }
    SwExitCriticalSection();
    return 1;
bail:
    return 0;
}
