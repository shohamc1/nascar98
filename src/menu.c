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

extern u16 D_8009AF1E[];
extern u16 D_8009AF20[];
extern u16 D_8009AF22[];
extern u16 D_8009AF24[];
extern u16 D_8009AF2A[];
extern u8 D_8009AF26[];
extern u8 D_8009AF28[];
extern u8 D_800A35EC;
extern u8 *D_800A3678;
extern u8 *D_800A392C;
extern u8 D_800A39C4;
extern u8 D_800AFDDC[];
extern u8 D_800AE1BC[];
void func_8005DFA0(void) {
    s32 i;
    s32 y;
    s32 primOffset;
    u8 index;
    u8 *object;
    u8 *slot;
    s32 panelH;
    s32 panelB;
    u8 *prim;
    u8 *panel;
    u8 *panelPrim;
    s32 panelY;
    s32 panelW;
    u8 color;
    s32 code;
    s32 panelOffset;

    y = 0xA7;
    panelH = 0x2D;
    panelB = 0x40;
    i = 0;
    primOffset = 0;
again:
    index = D_800A35EC++;
    slot = D_800A3678 + index * 36;
    *(s16 *)(slot + 0x12) = 0;
    object = slot;
    *(s16 *)(object + 0x14) = 0;
    *(s32 *)(object + 0x1C) = 0;
    object[4] = 0;
    object[3] = 0;
    object[2] = 0;
    *(s16 *)(object + 0x1A) = 0;
    *(s16 *)(object + 0) = 1;
    if (i == 0) {
        D_800A392C = object;
    } else {
        *(u8 **)(D_800A392C + 0x1C) = object;
    }
    *(s16 *)(object + 0xA) = 0;
    *(s16 *)(object + 0xC) = y;
    *(s16 *)(object + 8) = y;
    *(s16 *)(object + 0x16) = 0x78;
    *(s16 *)(object + 0x18) = (i == 0) ? 0x18 : 0x15;
    prim = D_800AFDDC + primOffset;
    *(s16 *)(object + 0xE) = 2;
    *(s16 *)(object + 0x10) = 0;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    prim[4] = 0x80;
    prim[5] = 0x80;
    prim[6] = 0x80;
    SetSemiTrans(prim, 1);
    if (i == 0) {
        u16 w;
        u16 h;
        w = *(u16 *)(object + 0x16);
        h = *(u16 *)(object + 0x18);
        *(s16 *)(prim + 0xE) = GetClut(D_8009AF22[0], D_8009AF24[0]);
        *(s16 *)(prim + 0x16) =
            GetTPage(D_8009AF2A[0], 3, D_8009AF1E[0], D_8009AF20[0]);
        prim[0xC] = D_8009AF26[0];
        prim[0xD] = D_8009AF28[0];
        prim[0x14] = *(u8 *)((u8 *)D_8009AF1E + 8) + w;
        prim[0x15] = *(u8 *)((u8 *)D_8009AF1E + 10);
        prim[0x1C] = *(u8 *)((u8 *)D_8009AF22 + 4);
        prim[0x1D] = *(u8 *)((u8 *)D_8009AF22 + 6) + h;
        prim[0x24] = *(u8 *)((u8 *)D_8009AF2A - 4) + w;
        prim[0x25] = *(u8 *)((u8 *)D_8009AF2A - 2) + h;
    } else {
        u16 w;
        w = *(u16 *)(object + 0x16);
        *(s16 *)(prim + 0xE) = GetClut(D_8009AF22[0], D_8009AF24[0]);
        *(s16 *)(prim + 0x16) =
            GetTPage(D_8009AF2A[0], 3, D_8009AF1E[0], D_8009AF20[0]);
        prim[0xC] = D_8009AF26[0];
        prim[0xD] = D_8009AF28[0] + 0x1B;
        prim[0x14] = *(u8 *)((u8 *)D_8009AF1E + 8) + w;
        prim[0x15] = *(u8 *)((u8 *)D_8009AF1E + 10) + 0x1B;
        prim[0x1C] = *(u8 *)((u8 *)D_8009AF22 + 4);
        prim[0x1D] = *(u8 *)((u8 *)D_8009AF22 + 6) + 0x30;
        prim[0x24] = *(u8 *)((u8 *)D_8009AF2A - 4) + w;
        prim[0x25] = *(u8 *)((u8 *)D_8009AF2A - 2) + 0x30;
    }
    y += 0x18;
    primOffset += 0x28;
    i++;
    *(s16 *)(object + 0x1A) = 0x3FC;
    *(u8 **)(object + 0x20) = prim;
    if (i < 2) {
        goto again;
    }
    i = 0;
    panelY = 0xA7;
    panelW = 0x78;
    color = 0x20;
    code = 2;
    panelOffset = 0;
again2:
    index = D_800A35EC;
    panelPrim = D_800AE1BC + panelOffset;
    D_800A35EC = index + 1;
    panel = D_800A3678 + index * 36;
    panel[4] = 0;
    *(s16 *)(panel + 0x18) = panelH;
    *(s16 *)(panel + 0x12) = 0;
    *(s16 *)(panel + 0x14) = 0;
    *(s32 *)(panel + 0x1C) = 0;
    panel[3] = 0;
    panel[2] = 0;
    *(s16 *)(panel + 0x1A) = 0;
    *(s16 *)(panel + 0) = code;
    *(s16 *)(panel + 6) = 0;
    *(s16 *)(panel + 0xA) = 0;
    *(s16 *)(panel + 8) = panelY;
    *(s16 *)(panel + 0xC) = panelY;
    *(s16 *)(panel + 0xE) = 0;
    *(s16 *)(panel + 0x10) = 0;
    *(s16 *)(panel + 0x16) = panelW;
    panel[2] = color;
    panel[3] = color;
    panel[4] = panelB;
    if (panelPrim == 0) {
        panelPrim = func_80057D50(1);
    }
    *(u8 **)(panel + 0x20) = panelPrim;
    SetPolyF4(panelPrim);
    SetSemiTrans(panelPrim, 1);
    panelPrim[4] = color;
    panelPrim[5] = color;
    panelPrim[6] = panelB;
    *(s16 *)(panelPrim + 0x12) = 0xD4;
    *(s16 *)(panelPrim + 0x16) = 0xD4;
    *(s16 *)(panelPrim + 8) = 0;
    *(s16 *)(panelPrim + 0xA) = panelY;
    *(s16 *)(panelPrim + 0xC) = panelW;
    *(s16 *)(panelPrim + 0xE) = panelY;
    *(s16 *)(panelPrim + 0x10) = 0;
    *(s16 *)(panelPrim + 0x14) = panelW;
    *(s16 *)(panel + 0xE) = code;
    *(s16 *)(panel + 0x1A) = 0x3FD;
    *(u8 **)(object + 0x1C) = panel;
    object = panel;
    i++;
    panelOffset += 0x18;
    if (i < 2) {
        goto again2;
    }
    D_800A39C4 = D_800A35EC;
}

extern void *D_800A3954;
void func_8005E3DC(void) {
    if (D_800A3954 != NULL) {
        HeapFree(D_800A3954);
    }
    D_800A3954 = NULL;
}

extern void *D_800A399C[];
extern void HeapFree(void *ptr);
void func_8005E408(void) {
    if (D_800A399C[0] != 0) {
        HeapFree(D_800A399C[0]);
    }
    *(void **)&D_800A3988[0x14] = 0;
}

extern char D_800BA058[], D_800A333C[];
extern u8 *func_80012EA8(s32, u8 *);
extern char *strcat(char *, char *);
void func_8005E43C(s32 value) {
    func_80012EA8(value, D_800BA058);
    strcat(D_800BA058, D_800A333C);
}

extern void *D_800A399C[];
void func_8005E47C(void) {
    D_800A399C[0] = HeapAlloc(0x2580);
}

#ifdef NON_MATCHING
/* Wall: body, registers, stores and lhu/sb shapes all match; retail's
 * frame is 0x30, ours 0x28. Tried: a live s16 local (kept in reg), and
 * volatile s32 x[2] (breaks cc1 wholesale). The inits of i/primOffset
 * must stay INSIDE the if, or i=0 leaves the blez delay slot. */
extern s32 D_800A393C;
extern s32 D_800A38DC;
void func_8005E4A4(u8 *table) {
    s32 count;
    s32 i;
    s32 primOffset;
    u8 *entry;
    u8 *prim;
    s16 color;

    count = *(s32 *)table;
    D_800A393C = (s32)(table + 4);
    D_800A38DC = count;
    if (count > 0) {
        i = 0;
        primOffset = 0;
        do {
            entry = (u8 *)(D_800A393C + i * 32);
            prim = D_800A399C[0] + primOffset;
            SetPolyF4(prim);
            color = *(s16 *)(entry + 6);
            prim[4] = color;
            color = *(s16 *)(entry + 0xE);
            prim[5] = color;
            color = *(s16 *)(entry + 0x16);
            prim[6] = color;
            i++;
            primOffset += 0x18;
        } while (i < D_800A38DC);
    }
}
#endif
extern s32 D_800A393C;
extern s32 D_800A38DC;
void func_8005E4A4(u8 *table) {
    volatile u32 pad[2];
    s32 count;
    s32 i;
    s32 primOffset;
    u8 *entry;
    u8 *prim;
    s16 color;

    count = *(s32 *)table;
    D_800A393C = (s32)(table + 4);
    D_800A38DC = count;
    if (count > 0) {
        i = 0;
        primOffset = 0;
        do {
            entry = (u8 *)(D_800A393C + i * 32);
            prim = D_800A399C[0] + primOffset;
            SetPolyF4(prim);
            color = *(s16 *)(entry + 6);
            prim[4] = color;
            color = *(s16 *)(entry + 0xE);
            prim[5] = color;
            color = *(s16 *)(entry + 0x16);
            prim[6] = color;
            i++;
            primOffset += 0x18;
        } while (i < D_800A38DC);
    }
}

extern u8 *D_800AE178[];
extern void *func_80058094(s32, void **, s32);
void func_8005E550(s32 arg0) {
    void *table;
    void *result;
    u8 i;

    result = func_80058094(arg0, &table, 0);
    D_800A3954 = result;
    for (i = 0; i < 0x11; i++) {
        D_800AE178[i] = result + ((s32 *)table)[i];
    }
}

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

INCLUDE_ASM("asm/nonmatchings/menu", func_8005E644);

void func_8005E7F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 D_8009A31C[];
    u8 index;
    u8 primIndex;
    u8 *object;
    s32 panelH;
    s32 panelB;
    u8 *prim;
    u8 *prim2;
    u8 *cur;
    s32 value;
    s32 word;
    s32 offset;
    s32 stride;

    index = D_800A35EC++;
    object = D_800A3678 + index * 36;
    object[4] = 0;
    object[3] = 0;
    object[2] = 0;
    primIndex = D_800A37BC;
    *(u16 *)(object + 0xA) = arg1;
    *(u16 *)(object + 6) = arg1;
    prim = (u8 *)D_800A3654;
    *(u16 *)(object + 0x12) = 0;
    *(u16 *)(object + 0x14) = 0;
    *(u32 *)(object + 0x1C) = 0;
    *(u16 *)(object + 0x1A) = 0;
    *(u16 *)(object + 0x0) = 0;
    *(u16 *)(object + 0xC) = 0xAB;
    *(u16 *)(object + 0x8) = 0xAB;
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
    prim2 = *(u8 **)(object + 0x20);
    offset = arg0 & 0xFF;
    stride = 4;
    offset = offset * stride;
    D_800A3740 = (s32 **)object;
    prim2[1] = 2;
    prim2[2] = 2;
    value = *(s32 *)((u8 *)D_8009A31C + offset);
    cur = (u8 *)D_800A3740;
    *(s32 *)(prim2 + 8) = value;
    word = *(u16 *)(cur + 6);
    word = word + 5;
    *(u16 *)(cur + 6) = word;
    word = 5;
    *(u16 *)(cur + 0xA) = word;
    if (arg3 & 0xFF) {
        word = 0x82;
        *(u16 *)(cur + 0xA) = word;
    }
    *(u16 *)((u8 *)D_800A3740 + 0xE) = arg2;
}

INCLUDE_ASM("asm/nonmatchings/menu", func_8005E8EC);

#ifdef NON_MATCHING
extern u16 D_8009AF84[];
extern s32 D_800A37D0;
extern s32 D_800A3814;
extern char D_800BA058[];
extern char D_800A333C[];
extern u8 *func_80012EA8(s32, u8 *);
extern char *strcat(char *, char *);
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
extern u8 D_8009AF84[];
extern s32 D_800A3814[];
extern s32 D_800A3814Abs[];
extern char D_800BA058NM[] asm("D_800BA058.NON_MATCHING");
asm(".globl D_800A3814Abs\nD_800A3814Abs = D_800A3814");
void func_8005EC5C(u8 arg0) {
    s32 value;

    value = *(s16 *)&D_8009AF84[(arg0 & 0xFF) * 2] * D_800A37D0[0] / 100;
    *(s32 *)&D_800A3808b[0] = value;
    if (value < 3) {
        D_800A3814[0] = 3;
    }
    func_80012EA8(D_800A3814Abs[0], D_800BA058);
    strcat(D_800BA058NM, D_800A333C);
}

#if 0
/* w7g draft: everything matches except gcc CSEs the two D_800BA058
 * materializations across the func_80012EA8/strcat calls into
 * callee-saved s0 (function 8 bytes short; asm("") does not block
 * cross-call cse). D_800A3814 is reached as D_800A37E8[11] (bss
 * neighbor of an already-array symbol; declaring D_800A3814 drifts
 * labels), and D_8009AF84 needs u8[] + s16 cast (retail strides 2). */
extern u8 D_8009AF84[];
void func_8005EC5C(u8 arg0) {
    s32 value;

    value = *(s16 *)&D_8009AF84[(arg0 & 0xFF) * 2] * D_800A37D0[0] / 100;
    D_800A37E8[11] = value;
    if (value < 3) {
        *(D_800A37E8 + 11) = 3;
    }
    func_80012EA8(D_800A37E8[11], D_800BA058);
    strcat(D_800BA058, D_800A333C);
}
#endif
#endif

extern s32 D_8009A31C[];
extern s32 **D_800A3740;
void func_8005ED04(s32 index) {
    D_800A3740[8][2] = D_8009A31C[index & 0xFF];
}

extern u8 D_800A3860[][4];
s32 func_8005ED28(u8 x, u8 y) {
    u32 scale;
    u32 level;

    level = D_800A3860[x][y];
    scale = ((level << 1) + level) << 2;
    scale += level;
    scale >>= 3;
    if (scale == 0) {
        scale = 1;
    }
    return scale;
}

extern u16 D_8009AEA2[];
extern u16 D_8009AEA6[];
extern u8 D_8009AEAA[];
extern u8 D_8009AEAE[];
extern u16 D_8009AEB2[];
extern u16 D_8009AEBA[];
extern u8 D_8009AEB6[];
extern u8 *D_800B996C[];
extern u8 *D_800B9980[];
extern u8 *D_800BB9F4[];
extern u8 *D_800AE168[];
extern u8 *D_800B60B8[];
extern u8 *D_800A39ACPtr asm("D_800A39AC");
extern s32 D_8009A268[];
extern s32 D_8009A298[];
extern s16 func_8005A84C(void);
extern void func_80060008(u8);
#ifdef NON_MATCHING
/* Keep coordinate calculations wide until the s16 stores. */
/* Permuter find (real-TU verified 10181 -> 8274): reuse pr5 as the
 * &D_8009AEAE[0] temp inside the obj8 GetTPage call, so its address
 * pseudo is born through an existing call-crossing pointer instead of a
 * fresh short-lived one. Frame grew 0x58 -> 0x60 and the s8/s7 saves now
 * lead the prologue like retail; the obj2 loop still allocates one
 * register away from retail (ours c2/k2 in s3/s6, obj2 in s1; retail
 * w2 in s6, obj2 in s0).
 */
void func_8005ED74(u8 arg0, u8 arg1) {
    extern s32 func_8005A8EI(s32) asm("func_8005A8E0");
    u8 ix1;
    u8 ix11;
    u8 ix2;
    u8 ix3;
    u8 ix4;
    u8 ix5;
    u8 ix6;
    u8 ix7;
    u8 ix8;
    u8 ix9;
    u8 ixB10;
    u8 *obj1;
    u8 *obj10;
    u8 *obj11;
    u8 *obj2;
    u8 *obj3;
    u8 *obj4;
    u8 *obj5;
    u8 *obj6;
    u8 *obj7;
    u8 *obj8;
    u8 *objB8;
    u8 *objB9;
    u8 *objC10;
    u8 *objC9;
    u8 *pq3;
    u8 *pr1;
    u8 *pr2;
    u8 *pr3;
    u8 *pr4;
    u8 *pr5;
    u8 *pr6;
    u8 *pr7;
    u8 *pr8;
    u8 *prC8;
    u8 *prC9;
    u8 *prD10;
    u8 *prD7;
    s16 w2, c2, k2, g2, b2;
    s32 half;
    s16 w1, g1, z1;
    u8 *prim2;
    s32 i;
    s32 j;
    s32 yBase;
    s32 h;
    s16 x;
    s32 x4;
    s32 x6;
    s32 value;
    u8 *entry;
    s32 *strP;
    u8 **list;

    h = 0;
    yBase = 0x5C;
    i = 0;
    list = D_800B996C;
    do {
        s32 y1;
        u8 **listSlot;
        j = 0;
        listSlot = list;
        w1 = 0x78;
        g1 = 0xF;
        z1 = 0x3FC;
        do {
            ix1 = D_800A35EC;
            D_800A35EC = ix1 + 1;
            obj1 = D_800A3678 + ix1 * 36;
            *(s16 *)(obj1 + 0x16) = w1;
            *(s16 *)(obj1 + 0x12) = 0;
            *(s16 *)(obj1 + 0x14) = 0;
            *(s32 *)(obj1 + 0x1C) = 0;
            obj1[4] = 0;
            obj1[3] = 0;
            obj1[2] = 0;
            *(s16 *)(obj1 + 0x1A) = 0;
            *(s16 *)(obj1 + 0) = 1;
            *(s16 *)(obj1 + 0xA) = h;
            *(s16 *)(obj1 + 6) = h;
            *(s16 *)(obj1 + 0xC) = yBase + j * 0xF;
            *(s16 *)(obj1 + 8) = yBase + j * 0xF;
            *(s16 *)(obj1 + 0x18) = g1;
            *(s16 *)(obj1 + 0xE) = 0;
            *(s16 *)(obj1 + 0x10) = 0;
            pr1 = func_80057CCC(1);
            SetPolyFT4((POLY_FT4 *)pr1);
            SetShadeTex(pr1, 0);
            pr1[4] = 0x80;
            pr1[5] = 0x80;
            pr1[6] = 0x80;
            SetSemiTrans(pr1, 0);
            entry = obj1;
            *(u8 **)(entry + 0x20) = pr1;
            *(s16 *)(entry + 0x1A) = z1;
            if (j == 0) {
                *listSlot = entry;
            } else {
                *(u8 **)(*listSlot + 0x1C) = entry;
            }
            prim2 = *(u8 **)(entry + 0x20);
            *(s16 *)(entry + 6) = -0xF5;
            *(s16 *)(entry + 0xE) = 2;
            if (j == 0) {
                u16 w;
                u8 v;
                w = *(u16 *)(entry + 0x16);
                *(s16 *)(prim2 + 0xE) =
                    GetClut(D_8009AF22[0], ((u16 *)D_8009AF22)[1]);
                *(s16 *)(prim2 + 0x16) = GetTPage(
                    D_8009AF2A[0], 3, D_8009AF1E[0], ((u16 *)D_8009AF1E)[1]);
                prim2[0xC] = *(u8 *)((u8 *)D_8009AF22 + 4);
                prim2[0xD] = *(u8 *)((u8 *)D_8009AF22 + 6);
                prim2[0x14] = *(u8 *)((u8 *)D_8009AF2A - 4) + w;
                prim2[0x15] = *(u8 *)((u8 *)D_8009AF1E + 10);
                prim2[0x1C] = *(u8 *)((u8 *)D_8009AF1E + 8);
                prim2[0x1D] = *(u8 *)((u8 *)D_8009AF2A - 2) + 0xF;
                prim2[0x24] = D_8009AF26[0] + w;
                v = *(u8 *)((u8 *)D_8009AF26 + 2) + 0xF;
                prim2[0x25] = v;
            } else {
                u16 w;
                u8 v;
                w = *(u16 *)(entry + 0x16);
                *(s16 *)(prim2 + 0xE) =
                    GetClut(D_8009AF22[0], ((u16 *)D_8009AF22)[1]);
                *(s16 *)(prim2 + 0x16) = GetTPage(
                    D_8009AF2A[0], 3, D_8009AF1E[0], ((u16 *)D_8009AF1E)[1]);
                prim2[0xC] = *(u8 *)((u8 *)D_8009AF22 + 4);
                prim2[0xD] = *(u8 *)((u8 *)D_8009AF22 + 6) + 0x21;
                prim2[0x14] = *(u8 *)((u8 *)D_8009AF2A - 4) + w;
                prim2[0x15] = *(u8 *)((u8 *)D_8009AF1E + 10) + 0x21;
                prim2[0x1C] = *(u8 *)((u8 *)D_8009AF1E + 8);
                prim2[0x1D] = *(u8 *)((u8 *)D_8009AF2A - 2) + 0x30;
                prim2[0x24] = D_8009AF26[0] + w;
                v = *(u8 *)((u8 *)D_8009AF26 + 2) + 0x30;
                prim2[0x25] = v;
            }
            j++;
        } while (j < 2);
        j = 0;
        w2 = 0x78;
        asm("" : "=r"(w2) : "0"(w2));
        c2 = 0x20;
        k2 = 2;
        g2 = 0x1E;
        b2 = 0x40;
        do {
            j++;
            ix2 = D_800A35EC;
            D_800A35EC = ix2 + 1;
            obj2 = D_800A3678 + ix2 * 36;
            obj2[4] = 0;
            *(s16 *)(obj2 + 0x18) = g2;
            *(s16 *)(obj2 + 0x12) = 0;
            *(s16 *)(obj2 + 0x14) = 0;
            *(s32 *)(obj2 + 0x1C) = 0;
            obj2[3] = 0;
            obj2[2] = 0;
            *(s16 *)(obj2 + 0x1A) = 0;
            *(s16 *)(obj2 + 0) = k2;
            *(s16 *)(obj2 + 6) = 0;
            *(s16 *)(obj2 + 0xA) = 0;
            *(s16 *)(obj2 + 8) = yBase;
            *(s16 *)(obj2 + 0xC) = yBase;
            *(s16 *)(obj2 + 0xE) = 0;
            *(s16 *)(obj2 + 0x10) = 0;
            *(s16 *)(obj2 + 0x16) = w2;
            obj2[2] = c2;
            obj2[3] = c2;
            obj2[4] = b2;
            pr2 = func_80057D50(1);
            *(u8 **)(obj2 + 0x20) = pr2;
            SetPolyF4(pr2);
            SetSemiTrans(pr2, 1);
            y1 = yBase + 0x1E;
            pr2[4] = c2;
            pr2[5] = c2;
            pr2[6] = b2;
            *(s16 *)(pr2 + 8) = 0;
            *(s16 *)(pr2 + 0xA) = yBase;
            *(s16 *)(pr2 + 0xC) = w2;
            *(s16 *)(pr2 + 0xE) = yBase;
            *(s16 *)(pr2 + 0x10) = 0;
            *(s16 *)(pr2 + 0x12) = y1;
            *(s16 *)(pr2 + 0x14) = w2;
            *(s16 *)(pr2 + 0x16) = y1;
            *(s16 *)(obj2 + 0x1A) = 0x3FD;
            *(s16 *)(obj2 + 0xE) = k2;
            *(s16 *)(obj2 + 6) = -0xF5;
            *(s16 *)(obj2 + 0xE) = k2;
            *(u8 **)(entry + 0x1C) = obj2;
            entry = obj2;
        } while (j < 2);
        list++;
        yBase = y1;
        i++;
    } while (i < 4);
    {
        s32 n;
        s32 m;
        n = 0;
        i = 0;
    textouter_L:
        {
            s16 yLoad;
            u8 *node;
            node = D_800B996C[i];
            m = 0;
            yLoad = *(s16 *)(node + 0xC);
            yBase = yLoad + 3;
            do {
                u8 primIdx;
                u8 *textPrim;
                u8 *primLoad;
                func_8005A7B8(2, 2);
                value = (s16)func_8005A8EI(D_8009A268[n]);
                switch (m) {
                case 0:
                    h = (0x78 - value) / 2;
                    break;
                case 1:
                    h = 8;
                    break;
                case 2:
                    h = 0x70 - value;
                    break;
                }
                ix3 = D_800A35EC;
                D_800A35EC = ix3 + 1;
                obj3 = D_800A3678 + ix3 * 36;
                obj3[4] = 0;
                obj3[3] = 0;
                obj3[2] = 0;
                primIdx = D_800A37BC;
                entry = obj3;
                *(s16 *)(entry + 0x12) = 0;
                *(s16 *)(entry + 0x14) = 0;
                *(s32 *)(entry + 0x1C) = 0;
                *(s16 *)(entry + 0x1A) = 0;
                *(s16 *)(entry + 0) = 0;
                *(s16 *)(entry + 0xA) = h;
                *(s16 *)(entry + 6) = h;
                *(s16 *)(entry + 0xC) = yBase;
                *(s16 *)(entry + 8) = yBase;
                *(s16 *)(entry + 0xE) = 0;
                *(s16 *)(entry + 0x10) = 0;
                *(s16 *)(entry + 0x1A) = 0;
                D_800A37BC = primIdx + 1;
                textPrim = (u8 *)D_800A3654 + primIdx * 12;
                *(u8 **)(entry + 0x20) = textPrim;
                textPrim[0] = 0;
                textPrim[3] = 0;
                *(s32 *)(textPrim + 4) = 0;
                D_800BB9F4[n] = entry;
                *(s16 *)(entry + 0xE) = 2;
                *(s16 *)(entry + 0x16) = value;
                *(s16 *)(entry + 6) = *(u16 *)(entry + 0xA) - 0xF5;
                *(s16 *)(entry + 0x18) = func_8005A84C();
                primLoad = *(u8 **)(entry + 0x20);
                primLoad[1] = 2;
                primLoad[2] = 2;
                *(s32 *)(primLoad + 8) = D_8009A268[n];
                n++;
                if (m == 0) {
                    yBase += 0x10;
                }
                m++;
            } while (m < 3);
            i++;
            if (i < 4) {
                goto textouter_L;
            }
        }
    }
    {
        u8 *obj3;
        u8 *pr3;
        u8 *pq3;
        yBase = *(s16 *)(D_800B996C[0] + 0xC) + 0xD;
        h = 8;
        i = 0;
        do {
            u8 **slot;
            u16 w;
            u16 hh;
            u32 scale;
            u32 level;
            ix4 = D_800A35EC;
            D_800A35EC = ix4 + 1;
            obj4 = D_800A3678 + ix4 * 36;
            *(s16 *)(obj4 + 0) = 1;
            *(s16 *)(obj4 + 0x16) = 0x68;
            *(s16 *)(obj4 + 0x12) = 0;
            *(s16 *)(obj4 + 0x14) = 0;
            *(s32 *)(obj4 + 0x1C) = 0;
            obj4[4] = 0;
            obj4[3] = 0;
            obj4[2] = 0;
            *(s16 *)(obj4 + 0x1A) = 0;
            *(s16 *)(obj4 + 0xA) = h;
            *(s16 *)(obj4 + 6) = h;
            *(s16 *)(obj4 + 0xC) = yBase;
            *(s16 *)(obj4 + 8) = yBase;
            *(s16 *)(obj4 + 0x18) = 5;
            *(s16 *)(obj4 + 0xE) = 0;
            *(s16 *)(obj4 + 0x10) = 0;
            pr4 = func_80057CCC(1);
            SetPolyFT4((POLY_FT4 *)pr4);
            SetShadeTex(pr4, 0);
            pr4[4] = 0x80;
            pr4[5] = 0x80;
            pr4[6] = 0x80;
            SetSemiTrans(pr4, 0);
            entry = obj4;
            *(u8 **)(entry + 0x20) = pr4;
            *(s16 *)(entry + 0x1A) = 0x3F2;
            slot = &D_800B9980[i];
            *slot = entry;
            prim2 = *(u8 **)(entry + 0x20);
            *(s16 *)(entry + 6) = -0xF5;
            *(s16 *)(entry + 0xE) = 2;
            w = *(u16 *)(entry + 0x16);
            hh = *(u16 *)(entry + 0x18);
            *(s16 *)(prim2 + 0xE) =
                GetClut(*(u16 *)((u8 *)D_8009AEA2 + 2), D_8009AEA6[0]);
            *(s16 *)(prim2 + 0x16) =
                GetTPage(*(u16 *)((u8 *)D_8009AEAA + 2), 3,
                         *(u16 *)((u8 *)D_8009AEA2 - 2), D_8009AEA2[0]);
            prim2[0xC] = *(u8 *)((u8 *)D_8009AEAA - 2);
            prim2[0xD] = D_8009AEAA[0];
            prim2[0x14] = *(u8 *)((u8 *)D_8009AEA2 + 6) + w;
            prim2[0x15] = *(u8 *)((u8 *)D_8009AEA6 + 4);
            prim2[0x1C] = *(u8 *)((u8 *)D_8009AEA6 + 2);
            prim2[0x1D] = *(u8 *)((u8 *)D_8009AEA2 + 8) + hh;
            prim2[0x24] = *(u8 *)((u8 *)D_8009AEAE - 6) + w;
            prim2[0x25] = *(u8 *)((u8 *)D_8009AEAE - 4) + hh;
            level = D_800A3860[arg0][i];
            scale = ((level << 1) + level) << 2;
            scale += level;
            scale >>= 3;
            if (scale == 0) {
                scale = 1;
            }
            x4 = yBase + 1;
            {
                s16 y2;
                ix5 = D_800A35EC;
                D_800A35EC = ix5 + 1;
                obj5 = D_800A3678 + ix5 * 36;
                *(s16 *)(obj5 + 0) = 2;
                *(s16 *)(obj5 + 6) = 9;
                *(s16 *)(obj5 + 0xA) = 9;
                obj5[2] = 0;
                *(s16 *)(obj5 + 0x18) = 3;
                obj5[4] = 0;
                obj5[2] = 0x40;
                *(s16 *)(obj5 + 0x12) = 0;
                *(s16 *)(obj5 + 0x14) = 0;
                *(s32 *)(obj5 + 0x1C) = 0;
                obj5[3] = 0;
                *(s16 *)(obj5 + 0x1A) = 0;
                *(s16 *)(obj5 + 8) = x4;
                *(s16 *)(obj5 + 0xC) = x4;
                *(s16 *)(obj5 + 0xE) = 0;
                *(s16 *)(obj5 + 0x10) = 0;
                *(s16 *)(obj5 + 0x16) = scale;
                obj5[3] = 0x60;
                obj5[4] = 0x80;
                pr5 = func_80057D50(1);
                *(u8 **)(obj5 + 0x20) = pr5;
                SetPolyF4(pr5);
                SetSemiTrans(pr5, 1);
                pr5[4] = 0x40;
                pr5[6] = 0x80;
                *(s16 *)(pr5 + 8) = 9;
                y2 = scale + 9;
                *(s16 *)(pr5 + 0x12) = yBase + 4;
                *(s16 *)(pr5 + 0x16) = yBase + 4;
                pr5[5] = 0x60;
                *(s16 *)(pr5 + 0xA) = x4;
                *(s16 *)(pr5 + 0xC) = y2;
                *(s16 *)(pr5 + 0xE) = x4;
                *(s16 *)(pr5 + 0x10) = 9;
                *(s16 *)(pr5 + 0x14) = y2;
                *(s16 *)(obj5 + 0x1A) = 0x3E8;
                i++;
                *(u8 **)(*slot + 0x1C) = obj5;
                *(s16 *)(obj5 + 6) = -0xF5;
                *(s16 *)(obj5 + 0xE) = 2;
            }
            yBase += 0x1E;
        } while (i < 4);
    }
    {
        u16 w;
        u16 hh;
        ix6 = D_800A35EC;
        D_800A35EC = ix6 + 1;
        obj6 = D_800A3678 + ix6 * 36;
        *(s16 *)(obj6 + 0xC) = 0x2A;
        *(s16 *)(obj6 + 8) = 0x2A;
        *(s16 *)(obj6 + 0x16) = 0x78;
        *(s16 *)(obj6 + 0x12) = 0;
        *(s16 *)(obj6 + 0x14) = 0;
        *(s32 *)(obj6 + 0x1C) = 0;
        obj6[4] = 0;
        obj6[3] = 0;
        obj6[2] = 0;
        *(s16 *)(obj6 + 0x1A) = 0;
        *(s16 *)(obj6 + 0) = 1;
        *(s16 *)(obj6 + 0xA) = 0;
        *(s16 *)(obj6 + 6) = 0;
        *(s16 *)(obj6 + 0x18) = 0x30;
        *(s16 *)(obj6 + 0xE) = 0;
        *(s16 *)(obj6 + 0x10) = 0;
        pr6 = func_80057CCC(1);
        SetPolyFT4((POLY_FT4 *)pr6);
        SetShadeTex(pr6, 0);
        pr6[4] = 0x80;
        pr6[5] = 0x80;
        pr6[6] = 0x80;
        SetSemiTrans(pr6, 0);
        entry = obj6;
        *(u8 **)(entry + 0x20) = pr6;
        *(s16 *)(entry + 0x1A) = 0x3FC;
        prim2 = *(u8 **)(entry + 0x20);
        *(s16 *)(entry + 0xE) = 2;
        *(s16 *)(entry + 0x10) = 0;
        w = *(u16 *)(entry + 0x16);
        hh = *(u16 *)(entry + 0x18);
        D_800A39ACPtr = entry;
        j = 0;
        *(s16 *)(prim2 + 0xE) = GetClut(D_8009AF22[0], ((u16 *)D_8009AF22)[1]);
        *(s16 *)(prim2 + 0x16) =
            GetTPage(D_8009AF2A[0], 3, D_8009AF1E[0], ((u16 *)D_8009AF1E)[1]);
        prim2[0xC] = *(u8 *)((u8 *)D_8009AF22 + 4);
        prim2[0xD] = *(u8 *)((u8 *)D_8009AF22 + 6);
        prim2[0x14] = *(u8 *)((u8 *)D_8009AF2A - 4) + w;
        prim2[0x15] = *(u8 *)((u8 *)D_8009AF1E + 10);
        prim2[0x1C] = *(u8 *)((u8 *)D_8009AF1E + 8);
        prim2[0x1D] = *(u8 *)((u8 *)D_8009AF2A - 2) + hh;
        prim2[0x24] = D_8009AF26[0] + w;
        prim2[0x25] = *(u8 *)((u8 *)D_8009AF26 + 2) + hh;
    }
    yBase = 0x2A;
    h = 0x78;
    *(s16 *)(D_800A39ACPtr + 6) = -0x7D;
    *(s16 *)(D_800A39ACPtr + 0xE) = 2;
    do {
        j++;
        ix7 = D_800A35EC;
        D_800A35EC = ix7 + 1;
        obj7 = D_800A3678 + ix7 * 36;
        obj7[4] = 0;
        *(s16 *)(obj7 + 0x18) = 0x30;
        *(s16 *)(obj7 + 0x12) = 0;
        *(s16 *)(obj7 + 0x14) = 0;
        *(s32 *)(obj7 + 0x1C) = 0;
        obj7[3] = 0;
        obj7[2] = 0;
        *(s16 *)(obj7 + 0x1A) = 0;
        *(s16 *)(obj7 + 0) = 2;
        *(s16 *)(obj7 + 6) = 0;
        *(s16 *)(obj7 + 0xA) = 0;
        *(s16 *)(obj7 + 8) = yBase;
        *(s16 *)(obj7 + 0xC) = yBase;
        *(s16 *)(obj7 + 0xE) = 0;
        *(s16 *)(obj7 + 0x10) = 0;
        *(s16 *)(obj7 + 0x16) = h;
        obj7[2] = 0x20;
        obj7[3] = 0x20;
        obj7[4] = 0x40;
        pr7 = func_80057D50(1);
        *(u8 **)(obj7 + 0x20) = pr7;
        SetPolyF4(pr7);
        SetSemiTrans(pr7, 1);
        *(s16 *)(pr7 + 0x12) = 0x5A;
        *(s16 *)(pr7 + 0x16) = 0x5A;
        pr7[4] = 0x20;
        pr7[5] = 0x20;
        pr7[6] = 0x40;
        *(s16 *)(pr7 + 8) = 0;
        *(s16 *)(pr7 + 0xA) = yBase;
        *(s16 *)(pr7 + 0xC) = h;
        *(s16 *)(pr7 + 0xE) = yBase;
        *(s16 *)(pr7 + 0x10) = 0;
        *(s16 *)(pr7 + 0x14) = h;
        *(s16 *)(obj7 + 0x1A) = 0x3FD;
        *(s16 *)(obj7 + 0xE) = 2;
        *(s16 *)(obj7 + 6) = -0x7D;
        *(s16 *)(obj7 + 0xE) = 2;
        *(u8 **)(entry + 0x1C) = obj7;
        entry = obj7;
    } while (j < 2);
    yBase = 0x2F;
    i = 0;
    do {
        s32 iOff;
        u8 **slot;
        u8 *prD7;
        u16 w;
        u16 hh;
        ix8 = D_800A35EC;
        D_800A35EC = ix8 + 1;
        obj8 = D_800A3678 + ix8 * 36;
        *(s16 *)(obj8 + 0) = 1;
        *(s16 *)(obj8 + 0xA) = 0x41;
        *(s16 *)(obj8 + 6) = 0x41;
        *(s16 *)(obj8 + 0x16) = 0x32;
        *(s16 *)(obj8 + 0x12) = 0;
        *(s16 *)(obj8 + 0x14) = 0;
        *(s32 *)(obj8 + 0x1C) = 0;
        obj8[4] = 0;
        obj8[3] = 0;
        obj8[2] = 0;
        *(s16 *)(obj8 + 0x1A) = 0;
        *(s16 *)(obj8 + 0xC) = yBase;
        *(s16 *)(obj8 + 8) = yBase;
        *(s16 *)(obj8 + 0x18) = 7;
        *(s16 *)(obj8 + 0xE) = 0;
        *(s16 *)(obj8 + 0x10) = 0;
        pr8 = func_80057CCC(1);
        SetPolyFT4((POLY_FT4 *)pr8);
        SetShadeTex(pr8, 0);
        pr8[4] = 0x80;
        pr8[5] = 0x80;
        pr8[6] = 0x80;
        SetSemiTrans(pr8, 0);
        entry = obj8;
        *(u8 **)(entry + 0x20) = pr8;
        *(s16 *)(entry + 0x1A) = 1;
        iOff = i * 4;
        slot = (u8 **)((u8 *)D_800B60B8 + iOff);
        *slot = entry;
        prim2 = *(u8 **)(entry + 0x20);
        *(s16 *)(entry + 0xE) = 2;
        *(s16 *)(entry + 6) = -0x7D;
        w = *(u16 *)(entry + 0x16);
        hh = *(u16 *)(entry + 0x18);
        x6 = yBase + 1;
        *(s16 *)(prim2 + 0xE) =
            GetClut(D_8009AEB2[0], *(u16 *)((u8 *)D_8009AEB2 + 2));
        *(s16 *)(prim2 + 0x16) =
            GetTPage(D_8009AEBA[0], 3, *(u16 *)(pr5 = &D_8009AEAE[0]),
                     *(u16 *)((u8 *)D_8009AEB2 - 2));
        prim2[0xC] = D_8009AEB6[0];
        prim2[0xD] = *(u8 *)((u8 *)D_8009AEB2 + 6);
        prim2[0x14] = *(u8 *)&D_8009AEAE[8] + w;
        prim2[0x15] = *(u8 *)&D_8009AEAE[10];
        prim2[0x1C] = *(u8 *)((u8 *)D_8009AEB2 + 4);
        prim2[0x1D] = *(u8 *)((u8 *)D_8009AEBA - 2) + hh;
        prim2[0x24] = *(u8 *)((u8 *)D_8009AEBA - 4) + w;
        prim2[0x25] = *(u8 *)&D_8009AEB6[2] + hh;
        {
            u8 *objB8;
            u8 *prC8;
            s16 y2;
            ix9 = D_800A35EC;
            D_800A35EC = ix9 + 1;
            objB9 = D_800A3678 + ix9 * 36;
            *(s16 *)(objB9 + 0) = 2;
            *(s16 *)(objB9 + 6) = 0x42;
            *(s16 *)(objB9 + 0x12) = 0;
            *(s16 *)(objB9 + 0x14) = 0;
            *(s32 *)(objB9 + 0x1C) = 0;
            objB9[4] = 0;
            objB9[3] = 0;
            objB9[2] = 0;
            *(s16 *)(objB9 + 0x1A) = 0;
            *(s16 *)(objB9 + 0xA) = 0x42;
            *(s16 *)(objB9 + 8) = x6;
            *(s16 *)(objB9 + 0xC) = x6;
            *(s16 *)(objB9 + 0xE) = 0;
            *(s16 *)(objB9 + 0x10) = 0;
            *(s16 *)(objB9 + 0x18) = 5;
            *(s16 *)(objB9 + 0x16) = 0x30;
            objB9[2] = 0x40;
            objB9[3] = 0x60;
            objB9[4] = 0x80;
            prC9 = func_80057D50(1);
            *(u8 **)(objB9 + 0x20) = prC9;
            SetPolyF4(prC9);
            SetSemiTrans(prC9, 0);
            prC9[6] = 0x80;
            *(s16 *)(prC9 + 8) = 0x42;
            y2 = yBase + 6;
            prC9[4] = 0x40;
            prC9[5] = 0x60;
            *(s16 *)(prC9 + 0xA) = x6;
            *(s16 *)(prC9 + 0xC) = 0x72;
            *(s16 *)(prC9 + 0xE) = x6;
            *(s16 *)(prC9 + 0x10) = 0x42;
            *(s16 *)(prC9 + 0x12) = y2;
            *(s16 *)(prC9 + 0x14) = 0x72;
            *(s16 *)(prC9 + 0x16) = y2;
            *(u8 **)(*slot + 0x1C) = objB9;
            *(s16 *)(objB9 + 6) = -0x7D;
            *(s16 *)(objB9 + 0xE) = 2;
            *(s16 *)(objB9 + 0x1A) = 0;
            entry = objB9;
        }
        func_8005A7B8(2, 2);
        strP = (s32 *)((u8 *)D_8009A298 + iOff);
        value = (s16)func_8005A8EI(*strP);
        {
            u8 primIdx;
            u8 *objC9;
            u8 *textPrim;
            ixB10 = D_800A35EC;
            D_800A35EC = ixB10 + 1;
            objC10 = D_800A3678 + ixB10 * 36;
            objC10[4] = 0;
            objC10[3] = 0;
            objC10[2] = 0;
            primIdx = D_800A37BC;
            h = 0x3E - value;
            *(s16 *)(objC10 + 0x12) = 0;
            *(s16 *)(objC10 + 0x14) = 0;
            *(s32 *)(objC10 + 0x1C) = 0;
            *(s16 *)(objC10 + 0x1A) = 0;
            *(s16 *)(objC10 + 0) = 0;
            *(s16 *)(objC10 + 0xA) = h;
            *(s16 *)(objC10 + 6) = h;
            *(s16 *)(objC10 + 0xC) = yBase;
            *(s16 *)(objC10 + 8) = yBase;
            *(s16 *)(objC10 + 0xE) = 0;
            *(s16 *)(objC10 + 0x10) = 0;
            *(s16 *)(objC10 + 0x1A) = 0;
            D_800A37BC = primIdx + 1;
            textPrim = (u8 *)D_800A3654 + primIdx * 12;
            *(u8 **)(objC10 + 0x20) = textPrim;
            textPrim[0] = 0;
            textPrim[3] = 0;
            *(s32 *)(textPrim + 4) = 0;
            *(u8 **)((u8 *)D_800AE168 + iOff) = objC10;
            *(s16 *)(objC10 + 0xE) = 2;
            *(s16 *)(objC10 + 0x16) = value;
            *(s16 *)(objC10 + 6) = *(u16 *)(objC10 + 0xA) - 0xAD;
            *(s16 *)(objC10 + 0x18) = func_8005A84C();
            prD10 = *(u8 **)(objC10 + 0x20);
            prD10[1] = 2;
            prD10[2] = 2;
            entry = objC10;
        }
        i++;
        *(s32 *)(prD10 + 8) = *strP;
        yBase += 0xA;
    } while (i < 4);
    if (arg1 != 0) {
        u8 primIdx;
        u8 *obj10;
        u8 *textPrim;
        u8 *primLoad;
        ix11 = D_800A35EC;
        D_800A35EC = ix11 + 1;
        obj11 = D_800A3678 + ix11 * 36;
        obj11[4] = 0;
        obj11[3] = 0;
        obj11[2] = 0;
        primIdx = D_800A37BC;
        *(s16 *)(obj11 + 0xA) = 5;
        *(s16 *)(obj11 + 0x12) = 0;
        *(s16 *)(obj11 + 0x14) = 0;
        *(s32 *)(obj11 + 0x1C) = 0;
        *(s16 *)(obj11 + 0x1A) = 0;
        *(s16 *)(obj11 + 0) = 0;
        *(s16 *)(obj11 + 6) = 5;
        *(s16 *)(obj11 + 0xC) = 0x20;
        *(s16 *)(obj11 + 8) = 0x20;
        *(s16 *)(obj11 + 0xE) = 0;
        *(s16 *)(obj11 + 0x10) = 0;
        *(s16 *)(obj11 + 0x1A) = 0;
        D_800A37BC = primIdx + 1;
        textPrim = (u8 *)D_800A3654 + primIdx * 12;
        *(u8 **)(obj11 + 0x20) = textPrim;
        textPrim[0] = 0;
        textPrim[3] = 0;
        *(s32 *)(textPrim + 4) = 0;
        *(s16 *)(obj11 + 0xE) = 2;
        *(s16 *)(obj11 + 0x16) = value;
        *(s16 *)(obj11 + 6) = *(u16 *)(obj11 + 0xA) - 0xAD;
        *(s16 *)(obj11 + 0x18) = func_8005A84C();
        primLoad = *(u8 **)(obj11 + 0x20);
        primLoad[1] = 2;
        primLoad[2] = 2;
        *(s32 *)(primLoad + 8) = *(s32 *)((u8 *)D_8009A298 + arg0 * 4 + 0x10);
        *(u8 **)(entry + 0x1C) = obj11;
    }
    func_80060008(arg0);
}

#else
INCLUDE_ASM("asm/nonmatchings/menu", func_8005ED74);
#endif

void func_8005FE90(void) {
    extern u8 *D_800B996C[];
    extern u8 *D_800B9980[];
    extern u8 *D_800BB9F4[];
    extern u8 *D_800AE168[];
    extern u8 *D_800B60B8[];
    extern u8 *D_800A39ACSmall asm("D_800A39AC.NON_MATCHING");
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        func_8005B688(D_800B996C[i], 1);
        func_8005B688(D_800B9980[i], 1);
        for (j = 0; j < 3; j++) {
            func_8005B688(D_800BB9F4[i * 3 + j], 1);
        }
    }
    func_8005B688(D_800A39ACSmall, 1);
    for (i = 0; i < 4; i++) {
        func_8005B688(D_800AE168[i], 1);
        func_8005B688(D_800B60B8[i], 1);
    }
}

extern u8 *D_800B9980[];
u8 *func_8005FFA8(u8 x, u8 y) {
    u32 scale;
    u32 level;
    u32 result;
    u8 *node;
    u8 *entry;

    level = D_800A3860[x][y];
    scale = ((level << 1) + level) << 2;
    scale += level;
    result = scale >> 3;
    if (result == 0) {
        result = 1;
    }
    node = D_800B9980[y];
    entry = *(u8 **)(node + 0x1C);
    *(s16 *)(entry + 0x16) = result;
    return entry;
}

extern u8 D_800A3860[][4];
extern u8 D_800A3861U8[][4] asm("D_800A3861.NON_MATCHING");
extern u8 D_800A3862U8[][4] asm("D_800A3862.NON_MATCHING");
extern u8 D_800A3863U8[][4] asm("D_800A3863.NON_MATCHING");
extern u8 *D_800B60B8[];

void func_80060008(u8 arg0) {
    s32 vals[4];
    s32 diff;
    s32 aCol;
    s32 cCol;
    s32 q;
    u8 *node;
    u8 *entry;

    vals[0] = (0x3F - D_800A3861U8[arg0][0]) * 700 / 1000 +
              D_800A3863U8[arg0][0] * 300 / 1000;
    aCol = D_800A3861U8[arg0][0];
    vals[3] = aCol / 5 + (0x3F - D_800A3860[arg0][0]) * 800 / 1000;
    vals[2] =
        D_800A3860[arg0][0] * 600 / 1000 + D_800A3862U8[arg0][0] * 400 / 1000;
    diff = D_800A3862U8[arg0][0] - D_800A3861U8[arg0][0];
    if (diff < 0) {
        diff = 0;
    }
    vals[2] = vals[2] - diff;
    if (vals[2] < 0) {
        vals[2] = 0;
    }
    cCol = D_800A3860[arg0][0];
    vals[1] = (0x3F - D_800A3863U8[arg0][0]) * 600 / 1000 + cCol / 4 +
              (0x3F - D_800A3861U8[arg0][0]) * 150 / 1000;
    diff = 0;
    do {
        q = vals[diff] * 48 / 61;
        if (q > 0x30) {
            q = 0x30;
        }
        if (q < 1) {
            q = 1;
        }
        node = D_800B60B8[diff];
        entry = *(u8 **)(&node[0x1C]);
        *(s16 *)(&entry[0x16]) = q;
        diff++;
    } while (diff < 4);
}

INCLUDE_ASM("asm/nonmatchings/menu", func_800602E8);

extern u8 *D_800A38A8;
extern u8 *D_800A3A68Store asm("D_800A3A68");
extern s32 D_8009A2B0[];
extern s32 D_8009A2BC[];
extern u16 D_8009AEA2[];
extern u16 D_8009AEA6[];
extern u8 D_8009AEAA[];
extern u8 D_8009AEAE[];
extern u16 D_8009AF1E[];
extern u16 D_8009AF22[];
extern u16 D_8009AF2A[];
extern u8 D_8009AF26[];
void func_800606D4(void) {
    u8 *entry;
    u8 *cur;
    u8 *row;
    u8 *prim2;
    u16 width;
    u8 *sign;
    int new_var3;
    s16 *new_var2;
    u8 *mark;
    u8 *cell;
    u8 *new_var;
    u8 idx2;
    u8 primIdx2;
    s32 i;
    s32 *p;
    s32 two;
    s32 *table;
    {
        u8 index;
        u8 *object;
        u8 *prim;
        u16 w;
        u16 h;
        index = D_800A35EC++;
        object = D_800A3678 + (index * 36);
        *((s16 *)(object + 0)) = 1;
        *((s16 *)(object + 0xC)) = 0xA7;
        *((s16 *)(object + 8)) = 0xA7;
        *((s16 *)(object + 0x16)) = 0x78;
        *((s16 *)(object + 0x12)) = 0;
        *((s16 *)(object + 0x14)) = 0;
        *((s32 *)(object + 0x1C)) = 0;
        object[4] = 0;
        object[3] = 0;
        object[2] = 0;
        new_var3 = 2;
        *((s16 *)(object + 0x1A)) = 0;
        *((s16 *)(object + 0xA)) = 0;
        idx2 = 0x30;
        *((s16 *)(object + 6)) = 0;
        *((s16 *)(object + 0x18)) = idx2;
        *((s16 *)(object + 0xE)) = 0;
        *((s16 *)(object + 0x10)) = 0;
        prim = func_80057CCC(1);
        SetPolyFT4((POLY_FT4 *)prim);
        SetShadeTex(prim, 0);
        prim[4] = 0x80;
        prim[5] = 0x80;
        prim[6] = 0x80;
        SetSemiTrans(prim, 0);
        entry = object;
        *((u8 **)(entry + 0x20)) = prim;
        *((s16 *)(entry + 0x1A)) = new_var3;
        asm volatile("" : : : "memory");
        prim2 = *((u8 **)(entry + 0x20));
        *((s16 *)(entry + 0xE)) = 0;
        *((s16 *)(entry + 0x10)) = 0;
        *((s16 *)(entry + 6)) = -0x78;
        w = *((u16 *)(entry + 0x16));
        h = *((u16 *)(entry + 0x18));
        D_800A38A8 = entry;
        *((s16 *)(prim2 + 0xE)) =
            GetClut(D_8009AF22[0], ((u16 *)D_8009AF22)[1]);
        *((s16 *)(prim2 + 0x16)) =
            GetTPage(D_8009AF2A[0], 3, D_8009AF1E[0], ((u16 *)D_8009AF1E)[1]);
        prim2[0xC] = D_8009AF26[0];
        prim2[0xD] = *((u8 *)(((u8 *)D_8009AF22) + 6));
        prim2[0x14] = (*((u8 *)(((u8 *)D_8009AF1E) + 8))) + w;
        prim2[0x15] = *((u8 *)(((u8 *)D_8009AF1E) + 10));
        prim2[0x1C] = *((u8 *)(((u8 *)D_8009AF22) + 4));
        prim2[0x1D] = (*((u8 *)(((u8 *)D_8009AF2A) - 2))) + h;
        prim2[0x24] = (*((u8 *)(((u8 *)D_8009AF2A) - 4))) + w;
        prim2[0x25] = (*((u8 *)(((u8 *)D_8009AF26) + 2))) + h;
    }
    {
        u8 index;
        u8 *object;
        u8 *prim;
        index = D_800A35EC++;
        object = D_800A3678 + (index * 36);
        *((s16 *)(object + 0x12)) = 0;
        *((s16 *)(object + 0x14)) = 0;
        *((s32 *)(object + 0x1C)) = 0;
        object[4] = 0;
        object[3] = 0;
        object[2] = 0;
        new_var3 = 2;
        *((s16 *)(object + 0x1A)) = 0;
        *((s16 *)(object + 0)) = 2;
        *((s16 *)(object + 6)) = 0xA;
        *((s16 *)(object + 0xA)) = 0xA;
        *((s16 *)(object + 8)) = 0xC6;
        *((s16 *)(object + 0xC)) = 0xC6;
        *((s16 *)(object + 0xE)) = 0;
        *((s16 *)(object + 0x10)) = 0;
        *((s16 *)(object + 0x16)) = 0x32;
        *((s16 *)(object + 0x18)) = 3;
        object[2] = 0x40;
        object[3] = 0x60;
        object[4] = 0x80;
        prim = func_80057D50(1);
        *((u8 **)(object + 0x20)) = prim;
        SetPolyF4(prim);
        SetSemiTrans(prim, 0);
        cur = object;
        prim[4] = 0x40;
        prim[5] = 0x60;
        prim[6] = 0x80;
        *((s16 *)(prim + 8)) = 0xA;
        *((s16 *)(prim + 0xA)) = 0xC6;
        *((s16 *)(prim + 0xC)) = 0x3C;
        *((s16 *)(prim + 0xE)) = 0xC6;
        *((s16 *)(prim + 0x10)) = 0xA;
        *((s16 *)(prim + 0x12)) = 0xC9;
        *((s16 *)(prim + 0x14)) = 0x3C;
        *((s16 *)(prim + 0x16)) = 0xC9;
        *((s16 *)(cur + 0x12)) = 9;
        *((s16 *)(cur + 0xE)) = 2;
        *((s16 *)(cur + 0x1A)) = 0;
        *((u8 **)(entry + 0x1C)) = cur;
        entry = cur;
    }
    i = 0;
    for (i = 0; i < 2; i++) {
        u8 index;
        u8 *prim;
        index = D_800A35EC++;
        row = D_800A3678 + (index * 36);
        *((s16 *)(row + 0)) = 2;
        *((s16 *)(row + 8)) = 0xA7;
        *((s16 *)(row + 0xC)) = 0xA7;
        *((s16 *)(row + 0x16)) = 0x78;
        row[4] = 0;
        *((s16 *)(row + 0x18)) = idx2;
        *((s16 *)(row + 0x12)) = 0;
        *((s16 *)(row + 0x14)) = 0;
        *((s32 *)(row + 0x1C)) = 0;
        row[3] = 0;
        row[2] = 0;
        *((s16 *)(row + 0x1A)) = 0;
        *((s16 *)(row + 6)) = 0;
        *((s16 *)(row + 0xA)) = 0;
        *((s16 *)(row + 0xE)) = 0;
        *((s16 *)(row + 0x10)) = 0;
        row[2] = 0x20;
        row[3] = 0x20;
        row[4] = 0x40;
        prim = func_80057D50(1);
        *((u8 **)(row + 0x20)) = prim;
        SetPolyF4(prim);
        SetSemiTrans(prim, 1);
        cur = row;
        prim[6] = 0x40;
        *((s16 *)(prim + 0xA)) = 0xA7;
        *((s16 *)(prim + 0xC)) = 0x78;
        *((s16 *)(prim + 0xE)) = 0xA7;
        *((s16 *)(prim + 0x12)) = 0xD7;
        *((s16 *)(prim + 0x16)) = 0xD7;
        prim[4] = 0x20;
        prim[5] = 0x20;
        *((s16 *)(prim + 8)) = 0;
        *((s16 *)(prim + 0x10)) = 0;
        *((s16 *)(prim + 0x14)) = 0x78;
        *((s16 *)(cur + 6)) = -0x78;
        *((s16 *)(cur + 0xE)) = 2;
        *((s16 *)(cur + 0x1A)) = 3;
        *((u8 **)(entry + 0x1C)) = cur;
        entry = cur;
    }

    {
        u8 index;
        u8 primIndex;
        u8 *panel;
        u8 *face;
        u8 *frame;
        u8 *tile;
        u8 *tile2;
        u16 w;
        u16 h;
        s16 x3;
        index = D_800A35EC++;
        panel = D_800A3678 + (index * 36);
        *((s16 *)(panel + 0xA)) = 8;
        *((s16 *)(panel + 6)) = 8;
        *((s16 *)(panel + 0xC)) = 0xC5;
        *((s16 *)(panel + 8)) = 0xC5;
        *((s16 *)(panel + 0x16)) = 0x68;
        *((s16 *)(panel + 0x12)) = 0;
        *((s16 *)(panel + 0x14)) = 0;
        *((s32 *)(panel + 0x1C)) = 0;
        panel[4] = 0;
        panel[3] = 0;
        panel[2] = 0;
        *((s16 *)(panel + 0x1A)) = 0;
        *((s16 *)(panel + 0)) = 1;
        *((s16 *)(panel + 0x18)) = 5;
        *((s16 *)(panel + 0xE)) = 0;
        *((s16 *)(panel + 0x10)) = 0;
        face = func_80057CCC(1);
        SetPolyFT4((POLY_FT4 *)face);
        SetShadeTex(face, 0);
        face[4] = 0x80;
        face[5] = 0x80;
        face[6] = 0x80;
        SetSemiTrans(face, 0);
        cur = panel;
        asm("" : "=r"(cur) : "0"(cur));
        *((u8 **)(panel + 0x20)) = face;
        *((s16 *)(panel + 0x1A)) = 1;
        prim2 = *((u8 **)(cur + 0x20));
        *((s16 *)(cur + 0xE)) = 2;
        asm("" : "=r"(x3) : "0"(8));
        *((s16 *)(cur + 0x12)) = x3;
        w = *((u16 *)(cur + 0x16));
        h = *((u16 *)(cur + 0x18));
        *((s16 *)(prim2 + 0xE)) =
            GetClut(((u16 *)D_8009AEA2)[1], D_8009AEA6[0]);
        *((s16 *)(prim2 + 0x16)) =
            GetTPage(((u16 *)D_8009AEAA)[1], 3,
                     *((u16 *)(((u8 *)D_8009AEA2) - 2)), D_8009AEA2[0]);
        prim2[0xC] = *((u8 *)(((u8 *)D_8009AEAA) - 2));
        prim2[0xD] = D_8009AEAA[0];
        prim2[0x14] = (*((u8 *)(((u8 *)D_8009AEA2) + 6))) + w;
        prim2[0x15] = *((u8 *)(((u8 *)D_8009AEA6) + 4));
        prim2[0x1C] = *((u8 *)(((u8 *)D_8009AEA6) + 2));
        prim2[0x1D] = (*((u8 *)(((u8 *)D_8009AEA2) + 8))) + h;
        prim2[0x24] = (*((u8 *)(((u8 *)D_8009AEAE) - 6))) + w;
        prim2[0x25] = (*((u8 *)(((u8 *)D_8009AEAE) - 4))) + h;
        index = D_800A35EC;
        frame = D_800A3678 + (index * 36);
        *((u8 **)(row + 0x1C)) = cur;
        D_800A35EC = index + 1;
        *((s16 *)(frame + 0x12)) = 0;
        *((s16 *)(frame + 0x14)) = 0;
        *((s32 *)(frame + 0x1C)) = 0;
        frame[4] = 0;
        frame[3] = 0;
        frame[2] = 0;
        *((s16 *)(frame + 0x1A)) = 0;
        *((s16 *)(frame + 0)) = 0;
        *((s16 *)(frame + 0xA)) = 0;
        *((s16 *)(frame + 6)) = 0;
        *((s16 *)(frame + 0xC)) = 0xB1;
        *((s16 *)(frame + 8)) = 0xB1;
        *((s16 *)(frame + 0xE)) = 0;
        primIndex = D_800A37BC;
        asm volatile("" : : "r"(cur));
        cur = frame;
        asm volatile("" : : "r"(cur), "r"(primIndex));
        tile = (u8 *)D_800A3654;
        *((s16 *)(cur + 0x10)) = 0;
        *((s16 *)(cur + 0x1A)) = 0;
        asm volatile("" : : "r"(primIndex));
        D_800A37BC = primIndex + 1;
        tile += primIndex * 12;
        *((u8 **)(cur + 0x20)) = tile;
        tile[0] = 0;
        tile[3] = 0;
        *((s32 *)(tile + 4)) = 0;
        tile2 = *((u8 **)(cur + 0x20));
        width = 0xCA;
        two = 2;
        D_800A3A68Store = cur;
        *((s16 *)(cur + 0x1A)) = 0;
        tile2[1] = 2;
        tile2[2] = 2;
        do {
        } while (0);
        *((s32 *)(tile2 + 8)) = D_8009A2B0[0];
        table = D_8009A2BC;
        asm("" : "=r"(p) : "0"(table));
        p = table;
        entry = cur;
        *((u8 **)(panel + 0x1C)) = entry;
    }
    do {
        s32 x;
        s32 value;
        func_8005A7B8(2, 2);
        value = (s16)func_8005A8E0(*p);
        do {
            if (p != table) {
                x = 0x70 - value;
            } else {
                x = 8;
            }
            idx2 = D_800A35EC++;
            sign = D_800A3678 + (idx2 * 36);
            sign[4] = 0;
            sign[3] = 0;
            sign[2] = 0;
            primIdx2 = D_800A37BC;
        } while (0);
        cur = sign;
        mark = (u8 *)D_800A3654;
        *((s16 *)(cur + 0x12)) = 0;
        *((s16 *)(cur + 0x14)) = 0;
        *((s32 *)(cur + 0x1C)) = 0;
        new_var2 = (s16 *)(cur + 0x1A);
        *new_var2 = 0;
        *((s16 *)(cur + 0)) = 0;
        *((s16 *)(cur + 0xA)) = x;
        *((s16 *)(cur + 6)) = x;
        *((s16 *)(cur + 0xC)) = width;
        *((s16 *)(cur + 8)) = width;
        *((s16 *)(cur + 0xE)) = 0;
        *((s16 *)(cur + 0x10)) = 0;
        *new_var2 = 0;
        asm volatile("" ::: "memory");
        D_800A37BC = primIdx2 + 1;
        mark += primIdx2 * 12;
        *((u8 **)(cur + 0x20)) = mark;
        mark[0] = 0;
        mark[3] = 0;
        *((s32 *)(mark + 4)) = 0;
        *((s16 *)(cur + 0x12)) = x;
        *((s16 *)(cur + 0x16)) = value;
        *((s16 *)(cur + 0x18)) = func_8005A84C();
        cell = *((u8 **)(cur + 0x20));
        *((s16 *)(cur + 0xE)) = two;
        *new_var2 = 0;
        cell[1] = two;
        cell[2] = two;
        *((s32 *)(cell + 8)) = *p;
        p++;
        *((u8 **)(entry + 0x1C)) = cur;
        entry = cur;
    } while ((s32)p < (s32)(table + 2));
    asm("" : : "r"(two), "r"(two));
}

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

extern u8 D_800A2F9DAbsolute[];
void func_80060F54(s32 arg0, s32 volume) {
    u8 *node;
    u8 x;

    node = *(u8 **)(D_800A38A8 + 0x1C);
    volume &= 0xFF;
    x = arg0;
    *(u16 *)(node + 0x16) = x;
    if (volume != 0) {
        x = arg0;
        D_800A2F9DAbsolute[-9] = (x * 127) / 100;
        func_8003FDE8(1, 0x7F, 0x7F);
    } else {
        CdSetMixVolume(x);
    }
}

#ifdef NON_MATCHING
typedef struct {
    s8 tab[7];
} RowList;
extern s8 D_800A3348[];
extern s32 *D_800A37D8[];
extern u8 *D_800A3A1C[];
extern u8 *D_800A3888[];
extern u8 *D_800A3A84[];
extern u8 *D_800A37FC[];
extern void *D_800A37F8;
extern s32 D_8009AC00[3];
extern s32 D_8009AC08[];
extern s32 D_8009AC10[];
extern s32 D_8009A314[];
extern u16 D_8009AEA2[];
extern u16 D_8009AEA6[];
extern u8 D_8009AEAA[];
extern u16 D_8009AEB2[];
extern void func_80062910(s32);
struct UnkObject24;
extern void func_80067EA4(struct UnkObject24 *, u8, u8, s32, u8, s32);
extern void ListSetFieldsAndEnable(u8 *, s16, s16, s16);
extern u8 D_800A3644[9];
void func_80060FD8(void) {
    u8 *cur;
    u8 *prev;
    u8 index;
    u8 primIndex;
    RowList row;
    s8 i;
    s8 j;
    s8 k;
    s8 m;
    s8 n;
    s8 r;
    s8 q;
    s32 color;
    s32 shade;
    s32 value;
    s32 ybase;
    u16 w;
    u16 h;
    u16 a;
    u16 b;
    u16 uv2;
    u16 wide;
    u16 high;

    {
        u8 *object;
        u8 *cell;
        u8 *prim2;
        index = D_800A35EC;
        row = *(RowList *)D_800A3348;
        D_800A35EC = index + 1;
        object = D_800A3678 + index * 36;
        object[4] = 0;
        object[3] = 0;
        object[2] = 0;
        cur = object;
        primIndex = D_800A37BC;
        *(s16 *)(cur + 0x12) = 0;
        *(s16 *)(cur + 0x14) = 0;
        *(s32 *)(cur + 0x1C) = 0;
        *(s16 *)(cur + 0x1A) = 0;
        *(s16 *)(cur + 0) = 0;
        *(s16 *)(cur + 0xA) = 0;
        *(s16 *)(cur + 6) = 0;
        *(s16 *)(cur + 8) = 0;
        *(s16 *)(cur + 0xC) = 0;
        *(s16 *)(cur + 0xE) = 0;
        *(s16 *)(cur + 0x10) = 0;
        *(s16 *)(cur + 0x1A) = 0;
        D_800A37BC = primIndex + 1;
        cell = (u8 *)D_800A3654 + primIndex * 12;
        *(u8 **)(cur + 0x20) = cell;
        cell[0] = 0;
        cell[3] = 0;
        *(s32 *)(cell + 4) = 0;
        prim2 = *(u8 **)(cur + 0x20);
        *(s16 *)(cur + 0x1A) = 1;
        *(s16 *)(cur + 0x14) = 0xDA;
        prim2[2] = 2;
        prim2[1] = 2;
        *(s32 *)(prim2 + 8) = D_8009AC00[0];
        func_8005A7B8(2, 2);
        *(s16 *)(cur + 0x12) = func_8005B0E4(0x140, *(s32 *)(prim2 + 8));
        D_800A37F8 = cur;
    }
    value = D_800A3644[0] != 0 ? 0x3C : 0x55;
    color = value << 24;
    for (i = 0; i < D_800A3644[0] + 1; i++) {
        {
            u8 *object;
            u8 *prim;
            j = 0;
            shade = 0x20;
            do {
                object = D_800A3678 + D_800A35EC++ * 36;
                *(s16 *)(object + 0) = 2;
                object[4] = 0;
                *(s16 *)(object + 0x16) = 0x140;
                *(s16 *)(object + 0x12) = 0;
                *(s16 *)(object + 0x14) = 0;
                *(s32 *)(object + 0x1C) = 0;
                object[3] = 0;
                object[2] = 0;
                *(s16 *)(object + 0x1A) = 0;
                *(s16 *)(object + 6) = 0;
                *(s16 *)(object + 0xA) = 0;
                *(s16 *)(object + 8) = 0;
                *(s16 *)(object + 0xC) = 0;
                *(s16 *)(object + 0xE) = 0;
                *(s16 *)(object + 0x10) = 0;
                *(s16 *)(object + 0x18) = 0x4A;
                object[2] = shade;
                object[3] = shade;
                object[4] = 0x40;
                prim = func_80057D50(1);
                *(u8 **)(object + 0x20) = prim;
                SetPolyF4(prim);
                SetSemiTrans(prim, 1);
                cur = object;
                prim[6] = 0x40;
                *(s16 *)(prim + 0xC) = 0x140;
                *(s16 *)(prim + 0x12) = 0x4A;
                *(s16 *)(prim + 8) = 0;
                *(s16 *)(prim + 0xA) = 0;
                *(s16 *)(prim + 0xE) = 0;
                *(s16 *)(prim + 0x10) = 0;
                *(s16 *)(prim + 0x14) = 0x140;
                *(s16 *)(prim + 0x16) = 0x4A;
                prim[4] = shade;
                prim[5] = shade;
                *(s16 *)(cur + 0x1A) = 3;
                *(s16 *)(cur + 0x12) = -0xA0;
                *(s16 *)(cur + 0x14) = i * 76 + 3;
                if (j == 0) {
                    D_800A37D8[i] = (s32 *)cur;
                } else {
                    *(u8 **)(prev + 0x1C) = cur;
                }
                j++;
                prev = cur;
            } while (j < 2);
        }
        {
            s32 xbase;
            s32 tone;
            u8 *object;
            u8 *prim;
            xbase = i * 76;
            tone = 0x40;
            k = 0;
            do {
                switch (k) {
                case 0:
                case 3:
                    ybase = -0xA1;
                    w = 0x142;
                    h = 2;
                    if (k == 0) {
                        value = xbase + 1;
                    } else {
                        value = xbase + 0x4D;
                    }
                    break;
                case 1:
                case 2:
                    w = 2;
                    value = xbase + 2;
                    ybase = 0xA0;
                    h = 3;
                    if (k == 1) {
                        ybase = -0xA2;
                    }
                    break;
                }
                object = D_800A3678 + D_800A35EC++ * 36;
                *(s16 *)(object + 0x12) = 0;
                *(s16 *)(object + 0x14) = 0;
                *(s32 *)(object + 0x1C) = 0;
                object[4] = 0;
                object[3] = 0;
                object[2] = 0;
                *(s16 *)(object + 0x1A) = 0;
                *(s16 *)(object + 0) = 2;
                *(s16 *)(object + 6) = 0;
                *(s16 *)(object + 0xA) = 0;
                *(s16 *)(object + 8) = 0;
                *(s16 *)(object + 0xC) = 0;
                *(s16 *)(object + 0xE) = 0;
                *(s16 *)(object + 0x10) = 0;
                *(s16 *)(object + 0x16) = w;
                object[2] = tone;
                object[3] = tone;
                object[4] = tone;
                *(s16 *)(object + 0x18) = h;
                prim = func_80057D50(1);
                *(u8 **)(object + 0x20) = prim;
                SetPolyF4(prim);
                SetSemiTrans(prim, 0);
                cur = object;
                prim[4] = tone;
                prim[5] = tone;
                prim[6] = tone;
                *(s16 *)(prim + 8) = 0;
                *(s16 *)(prim + 0xA) = 0;
                *(s16 *)(prim + 0xE) = 0;
                *(s16 *)(prim + 0x10) = 0;
                *(s16 *)(prim + 0xC) = w;
                *(s16 *)(prim + 0x14) = w;
                *(s16 *)(prim + 0x12) = h;
                *(s16 *)(prim + 0x16) = h;
                *(s16 *)(cur + 0x1A) = 3;
                *(s16 *)(cur + 0x12) = ybase;
                *(s16 *)(cur + 0x14) = value;
                *(u8 **)(prev + 0x1C) = cur;
                k++;
                prev = cur;
            } while (k < 4);
        }
        {
            u8 *object;
            u8 *prim;
            index = D_800A35EC++;
            object = D_800A3678 + index * 36;
            *(s16 *)(object + 0x12) = 0;
            *(s16 *)(object + 0x14) = 0;
            *(s32 *)(object + 0x1C) = 0;
            object[4] = 0;
            object[3] = 0;
            object[2] = 0;
            *(s16 *)(object + 0x1A) = 0;
            *(s16 *)(object + 0) = 1;
            *(s16 *)(object + 0xA) = 0;
            *(s16 *)(object + 6) = 0;
            *(s16 *)(object + 0xC) = 0;
            *(s16 *)(object + 8) = 0;
            *(s16 *)(object + 0x16) = 0x74;
            *(s16 *)(object + 0x18) = 0x50;
            *(s16 *)(object + 0xE) = 0;
            *(s16 *)(object + 0x10) = 0;
            prim = func_80057CCC(1);
            SetPolyFT4(prim);
            SetShadeTex(prim, 0);
            prim[4] = 0x80;
            prim[5] = 0x80;
            prim[6] = 0x80;
            SetSemiTrans(prim, 0);
            cur = object;
            *(u8 **)(cur + 0x20) = prim;
            *(s16 *)(cur + 0x1A) = 2;
            *(s16 *)(cur + 0x12) = -0x3A;
            *(s16 *)(cur + 0x14) = i * 76;
            *(u8 **)(prev + 0x1C) = cur;
            D_800A3A1C[i] = cur;
        }
        {
            u8 *object;
            u8 *prim;
            index = D_800A35EC++;
            object = D_800A3678 + index * 36;
            *(s16 *)(object + 0x12) = 0;
            *(s16 *)(object + 0x14) = 0;
            *(s32 *)(object + 0x1C) = 0;
            object[4] = 0;
            object[3] = 0;
            object[2] = 0;
            *(s16 *)(object + 0x1A) = 0;
            *(s16 *)(object + 0) = 2;
            *(s16 *)(object + 6) = 0;
            *(s16 *)(object + 0xA) = 0;
            *(s16 *)(object + 8) = 0;
            *(s16 *)(object + 0xC) = 0;
            *(s16 *)(object + 0xE) = 0;
            *(s16 *)(object + 0x10) = 0;
            *(s16 *)(object + 0x16) = 4;
            *(s16 *)(object + 0x18) = 1;
            object[2] = 0;
            object[3] = 0;
            object[4] = 0;
            prim = func_80057D50(1);
            *(u8 **)(object + 0x20) = prim;
            SetPolyF4(prim);
            SetSemiTrans(prim, 1);
            cur = object;
            prim[4] = 0;
            prim[5] = 0;
            prim[6] = 0;
            *(s16 *)(prim + 8) = 0;
            *(s16 *)(prim + 0xA) = 0;
            *(s16 *)(prim + 0xC) = 4;
            *(s16 *)(prim + 0xE) = 0;
            *(s16 *)(prim + 0x10) = 0;
            *(s16 *)(prim + 0x12) = 1;
            *(s16 *)(prim + 0x14) = 4;
            *(s16 *)(prim + 0x16) = 1;
            *(s16 *)(cur + 0x12) = -2;
            *(s16 *)(cur + 0x1A) = 1;
            *(s16 *)(cur + 0x14) = i * 76 + 0x35;
            *(u8 **)(prev + 0x1C) = cur;
        }
        {
            u8 *object;
            u8 *prim;
            index = D_800A35EC++;
            object = D_800A3678 + index * 36;
            *(s16 *)(object + 0x12) = 0;
            *(s16 *)(object + 0x14) = 0;
            *(s32 *)(object + 0x1C) = 0;
            object[4] = 0;
            object[3] = 0;
            object[2] = 0;
            *(s16 *)(object + 0x1A) = 0;
            *(s16 *)(object + 0) = 2;
            *(s16 *)(object + 6) = 0;
            *(s16 *)(object + 0xA) = 0;
            *(s16 *)(object + 8) = 0;
            *(s16 *)(object + 0xC) = 0;
            *(s16 *)(object + 0xE) = 0;
            *(s16 *)(object + 0x10) = 0;
            *(s16 *)(object + 0x16) = 0x140;
            *(s16 *)(object + 0x18) = 0x4A;
            object[2] = 0;
            object[3] = 0;
            object[4] = 0;
            prim = func_80057D50(1);
            *(u8 **)(object + 0x20) = prim;
            SetPolyF4(prim);
            SetSemiTrans(prim, 1);
            cur = object;
            *(s16 *)(prim + 0xC) = 0x140;
            *(s16 *)(prim + 0x12) = 0x4A;
            prim[4] = 0;
            prim[5] = 0;
            prim[6] = 0;
            *(s16 *)(prim + 8) = 0;
            *(s16 *)(prim + 0xA) = 0;
            *(s16 *)(prim + 0xE) = 0;
            *(s16 *)(prim + 0x10) = 0;
            *(s16 *)(prim + 0x14) = 0x140;
            *(s16 *)(prim + 0x16) = 0x4A;
            *(s16 *)(cur + 0x1A) = 0;
            *(s16 *)(cur + 0x12) = -0xA0;
            *(s16 *)(cur + 0x14) = i * 76 + 3;
            *(u8 **)(prev + 0x1C) = cur;
        }
        func_8005A7B8(2, 2);
        value = func_8005B0E4(0x140, D_8009A314[0]) - 0xA0;
        ybase = value - 5;
        m = 0;
    loopC:
        {
            u8 *object;
            u8 *cell;
            u8 *prim2;
            object = D_800A3678 + D_800A35EC++ * 36;
            object[4] = 0;
            object[3] = 0;
            object[2] = 0;
            cur = object;
            primIndex = D_800A37BC;
            *(s16 *)(cur + 0x12) = 0;
            *(s16 *)(cur + 0x14) = 0;
            *(s32 *)(cur + 0x1C) = 0;
            *(s16 *)(cur + 0x1A) = 0;
            *(s16 *)(cur + 0) = 0;
            *(s16 *)(cur + 0xA) = 0;
            *(s16 *)(cur + 6) = 0;
            *(s16 *)(cur + 8) = 0;
            *(s16 *)(cur + 0xC) = 0;
            *(s16 *)(cur + 0xE) = 0;
            *(s16 *)(cur + 0x10) = 0;
            *(s16 *)(cur + 0x1A) = 0;
            D_800A37BC = primIndex + 1;
            cell = (u8 *)D_800A3654 + primIndex * 12;
            *(u8 **)(cur + 0x20) = cell;
            cell[0] = 0;
            cell[3] = 0;
            *(s32 *)(cell + 4) = 0;
            prim2 = *(u8 **)(cur + 0x20);
            *(s16 *)(cur + 0x14) = i * 76 + 5;
            *(s16 *)(cur + 0x1A) = 1;
            *(s16 *)(cur + 0x12) = ybase;
            prim2[2] = 2;
            prim2[1] = 2;
            prim2[3] = 0;
            if (m != 0) {
                *(s16 *)(cur + 0x12) = func_8005A8E0(D_8009A314[0]) + value;
                *(s16 *)(cur + 0) = 5;
                *(s32 *)(prim2 + 8) = 1;
            } else {
                *(s16 *)(cur + 0x12) = ybase;
                *(s32 *)(prim2 + 8) = D_8009A314[0];
            }
            *(u8 **)(prev + 0x1C) = cur;
            m = m + 1;
            prev = cur;
        }
        if (m < 2) {
            goto loopC;
        }
        {
            u8 *object;
            u8 *cell;
            u8 *prim2;
            n = 0;
            do {
                q = 0;
                do {
                    object = D_800A3678 + D_800A35EC++ * 36;
                    object[4] = 0;
                    object[3] = 0;
                    object[2] = 0;
                    cur = object;
                    primIndex = D_800A37BC;
                    *(s16 *)(cur + 0x12) = 0;
                    *(s16 *)(cur + 0x14) = 0;
                    *(s32 *)(cur + 0x1C) = 0;
                    *(s16 *)(cur + 0x1A) = 0;
                    *(s16 *)(cur + 0) = 0;
                    *(s16 *)(cur + 0xA) = 0;
                    *(s16 *)(cur + 6) = 0;
                    *(s16 *)(cur + 8) = 0;
                    *(s16 *)(cur + 0xC) = 0;
                    *(s16 *)(cur + 0xE) = 0;
                    *(s16 *)(cur + 0x10) = 0;
                    *(s16 *)(cur + 0x1A) = 0;
                    D_800A37BC = primIndex + 1;
                    cell = (u8 *)D_800A3654 + primIndex * 12;
                    *(u8 **)(cur + 0x20) = cell;
                    cell[0] = 0;
                    cell[3] = 0;
                    *(s32 *)(cell + 4) = 0;
                    prim2 = *(u8 **)(cur + 0x20);
                    *(s16 *)(cur + 0x1A) = 1;
                    *(s16 *)(cur + 0x12) = (n * 2 - 1) * 63;
                    *(s16 *)(cur + 0x14) = row.tab[q] + i * 76;
                    prim2[2] = 2;
                    prim2[3] = n == 0;
                    prim2[1] = 2;
                    *(u8 **)(prev + 0x1C) = cur;
                    q++;
                    prev = cur;
                } while (q < 7);
                n++;
            } while (n < 2);
        }
        {
            u8 *node;
            node = (u8 *)D_800A37D8[i];
            if (node == NULL) {
                goto walkDone;
            }
        walkAgain:
            node[5] = 1;
            *(s16 *)(node + 0xA) = 0xA0;
            *(s16 *)(node + 8) = color >> 24;
            *(s16 *)(node + 0xE) = (s8)(2 - i * 4);
            *(s16 *)(node + 0xC) = color >> 24;
            *(s16 *)(node + 6) =
                i * 320 + (i * 2 - 1) * (*(s16 *)(node + 0x12) + 0xA2);
            node = *(u8 **)(node + 0x1C);
            if (node != NULL) {
                goto walkAgain;
            }
        }
    walkDone:
        func_80062910((u8)i);
        {
            s32 xoff;
            s32 colorS;
            u8 *object;
            u8 *prim;
            u8 *prim2;
            colorS = color >> 24;
            xoff = 0;
            r = 0;
        loopE:
            {
                switch (r) {
                case 1:
                    a = 6;
                    b = 1;
                    break;
                case 0:
                    a = 1;
                    b = 0;
                    break;
                case 2:
                    a = 2;
                    b = 3;
                    break;
                }
                object = D_800A3678 + D_800A35EC++ * 36;
                *(s16 *)(object + 0x12) = 0;
                *(s16 *)(object + 0x14) = 0;
                *(s32 *)(object + 0x1C) = 0;
                object[4] = 0;
                object[3] = 0;
                object[2] = 0;
                *(s16 *)(object + 0x1A) = 0;
                *(s16 *)(object + 0) = 1;
                *(s16 *)(object + 0xA) = 0;
                *(s16 *)(object + 6) = 0;
                *(s16 *)(object + 0xC) = colorS;
                *(s16 *)(object + 8) = colorS;
                *(s16 *)(object + 0x16) = 0x68;
                *(s16 *)(object + 0x18) = a;
                *(s16 *)(object + 0xE) = 0;
                *(s16 *)(object + 0x10) = 0;
                prim = func_80057CCC(1);
                SetPolyFT4(prim);
                SetShadeTex(prim, 0);
                prim[4] = 0x80;
                prim[5] = 0x80;
                prim[6] = 0x80;
                SetSemiTrans(prim, 0);
                cur = object;
                *(u8 **)(cur + 0x20) = prim;
                *(s16 *)(cur + 0x1A) = 2;
                if (r == 0) {
                    D_800A3888[i] = cur;
                } else {
                    *(u8 **)(prev + 0x1C) = cur;
                }
                if (i != 0) {
                    *(s16 *)(cur + 6) = 0x140;
                } else {
                    *(s16 *)(cur + 6) = -0x140;
                }
                prim2 = *(u8 **)(cur + 0x20);
                *(s16 *)(cur + 0x12) = 0x78;
                *(s16 *)(cur + 0x14) =
                    *((u16 *)((u8 *)D_800A37D8[i] + 0x14)) + (xoff + 0x3A);
                if (r == 1) {
                    wide = *(u16 *)(cur + 0x16);
                    *(s16 *)(prim2 + 0xE) =
                        GetClut(((u16 *)D_8009AEA2)[1], D_8009AEA6[0]);
                    *(s16 *)(prim2 + 0x16) = GetTPage(
                        *((u16 *)((u8 *)D_8009AEA6 + 6)), 3,
                        *((u16 *)(((u8 *)D_8009AEA2) - 2)), D_8009AEA2[0]);
                    prim2[0xC] = *((u8 *)((u8 *)D_8009AEAA - 2));
                    prim2[0xD] = D_8009AEAA[0] + b;
                    prim2[0x14] = *((u8 *)((u8 *)D_8009AEAA - 2)) + wide;
                    prim2[0x15] = D_8009AEAA[0] + b;
                    prim2[0x1C] = *((u8 *)((u8 *)D_8009AEAA - 2));
                    prim2[0x1D] = D_8009AEAA[0] + b + 1;
                    prim2[0x24] = *((u8 *)((u8 *)D_8009AEAA - 2)) + wide;
                    uv2 = D_8009AEAA[0] + b + 1;
                } else {
                    wide = *(u16 *)(cur + 0x16);
                    high = *(u16 *)(cur + 0x18);
                    *(s16 *)(prim2 + 0xE) =
                        GetClut(((u16 *)D_8009AEA2)[1], D_8009AEA6[0]);
                    *(s16 *)(prim2 + 0x16) = GetTPage(
                        *((u16 *)((u8 *)D_8009AEA6 + 6)), 3,
                        *((u16 *)(((u8 *)D_8009AEA2) - 2)), D_8009AEA2[0]);
                    prim2[0xC] = *((u8 *)((u8 *)D_8009AEAA - 2));
                    prim2[0xD] = D_8009AEAA[0] + b;
                    prim2[0x14] = *((u8 *)((u8 *)D_8009AEAA - 2)) + wide;
                    prim2[0x15] = D_8009AEAA[0] + b;
                    prim2[0x1C] = *((u8 *)((u8 *)D_8009AEAA - 2));
                    prim2[0x1D] = D_8009AEAA[0] + b + high;
                    prim2[0x24] = *((u8 *)((u8 *)D_8009AEAA - 2)) + wide;
                    uv2 = D_8009AEAA[0] + b + high;
                }
                prim2[0x25] = uv2;
                prev = cur;
                r++;
                xoff += *(s16 *)(cur + 0x18);
            }
            if (r < 3) {
                goto loopE;
            }
        }
        {
            s32 colorS;
            u8 *object;
            u8 *prim;
            u8 *prim2;
            colorS = color >> 24;
            r = 0;
        loopF:
            {
                object = D_800A3678 + D_800A35EC++ * 36;
                *(s16 *)(object + 0) = 1;
                *(s16 *)(object + 0x12) = 0;
                *(s16 *)(object + 0x14) = 0;
                *(s32 *)(object + 0x1C) = 0;
                object[4] = 0;
                object[3] = 0;
                object[2] = 0;
                *(s16 *)(object + 0x1A) = 0;
                *(s16 *)(object + 0xA) = 0;
                *(s16 *)(object + 6) = 0;
                *(s16 *)(object + 0xC) = colorS;
                *(s16 *)(object + 8) = colorS;
                *(s16 *)(object + 0x16) = 0xE;
                *(s16 *)(object + 0x18) = 0x32;
                *(s16 *)(object + 0xE) = 0;
                *(s16 *)(object + 0x10) = 0;
                prim = func_80057CCC(1);
                SetPolyFT4(prim);
                SetShadeTex(prim, 0);
                prim[4] = 0x80;
                prim[5] = 0x80;
                prim[6] = 0x80;
                SetSemiTrans(prim, 0);
                cur = object;
                *(u8 **)(cur + 0x20) = prim;
                *(s16 *)(cur + 0x1A) = 2;
                if (i != 0) {
                    *(s16 *)(cur + 6) = 0x140;
                } else {
                    *(s16 *)(cur + 6) = -0x140;
                }
                *(s16 *)(cur + 0x12) = (r << 5) + 0xFA;
                *(s16 *)(cur + 0x14) =
                    *((u16 *)((u8 *)D_800A37D8[i] + 0x14)) + 7;
                prim2 = *(u8 **)(cur + 0x20);
                *(s16 *)(prim2 + 0xE) = GetClut(D_8009AEB2[0], D_8009AEB2[1]);
                *(s16 *)(prim2 + 0x16) =
                    GetTPage(D_8009AEB2[4], 0, D_8009AEB2[-2], D_8009AEB2[-1]);
                prim2[0xC] = D_8009AEB2[2];
                prim2[0xD] = *(u8 *)&D_8009AEB2[3] + 6;
                prim2[0x14] = D_8009AEB2[2];
                prim2[0x15] = *(u16 *)&D_8009AEB2[3];
                prim2[0x1C] = *(u8 *)&D_8009AEB2[2] + 0x32;
                prim2[0x1D] = *(u8 *)&D_8009AEB2[3] + 6;
                prim2[0x24] = *(u8 *)&D_8009AEB2[2] + 0x32;
                prim2[0x25] = *(u16 *)&D_8009AEB2[3];
                r++;
                *(u8 **)(prev + 0x1C) = cur;
                prev = cur;
            }
            if (r < 2) {
                goto loopF;
            }
        }
        {
            s32 **slot;
            s32 colorS;
            u8 *object;
            u8 *cell;
            colorS = color >> 24;
            slot = &D_800A37D8[i];
            object = D_800A3678 + D_800A35EC++ * 36;
            object[4] = 0;
            object[3] = 0;
            object[2] = 0;
            cur = object;
            primIndex = D_800A37BC;
            *(s16 *)(cur + 0x12) = 0;
            *(s16 *)(cur + 0x14) = 0;
            *(s32 *)(cur + 0x1C) = 0;
            *(s16 *)(cur + 0x1A) = 0;
            *(s16 *)(cur + 0) = 0;
            *(s16 *)(cur + 0xA) = 0;
            *(s16 *)(cur + 6) = 0;
            *(s16 *)(cur + 0xE) = 0;
            *(s16 *)(cur + 0x10) = 0;
            *(s16 *)(cur + 0x1A) = 0;
            *(s16 *)(cur + 0xC) = colorS;
            *(s16 *)(cur + 8) = colorS;
            D_800A37BC = primIndex + 1;
            cell = (u8 *)D_800A3654 + primIndex * 12;
            *(u8 **)(cur + 0x20) = cell;
            cell[0] = 0;
            cell[3] = 0;
            *(s32 *)(cell + 4) = 0;
            if (i != 0) {
                *(s16 *)(cur + 6) = 0x140;
            } else {
                *(s16 *)(cur + 6) = -0x140;
            }
            *(s16 *)(cur + 0x12) = 8;
            *(s16 *)(cur + 0x14) = *((u16 *)((u8 *)*slot + 0x14)) + 5;
            func_80067EA4((struct UnkObject24 *)cur, 2, 2, D_8009AC08[0], 0, 1);
            *(u8 **)(prev + 0x1C) = cur;
            prev = cur;
            D_800A3A84[i] = cur;
            r = 0;
            do {
                object = D_800A3678 + D_800A35EC++ * 36;
                object[4] = 0;
                object[3] = 0;
                object[2] = 0;
                cur = object;
                primIndex = D_800A37BC;
                *(s16 *)(cur + 0x12) = 0;
                *(s16 *)(cur + 0x14) = 0;
                *(s32 *)(cur + 0x1C) = 0;
                *(s16 *)(cur + 0x1A) = 0;
                *(s16 *)(cur + 0) = 0;
                *(s16 *)(cur + 0xA) = 0;
                *(s16 *)(cur + 6) = 0;
                *(s16 *)(cur + 0xC) = colorS;
                *(s16 *)(cur + 8) = colorS;
                *(s16 *)(cur + 0xE) = 0;
                *(s16 *)(cur + 0x10) = 0;
                *(s16 *)(cur + 0x1A) = 0;
                D_800A37BC = primIndex + 1;
                cell = (u8 *)D_800A3654 + primIndex * 12;
                *(u8 **)(cur + 0x20) = cell;
                cell[0] = 0;
                cell[3] = 0;
                *(s32 *)(cell + 4) = 0;
                if (i != 0) {
                    *(s16 *)(cur + 6) = 0x140;
                } else {
                    *(s16 *)(cur + 6) = -0x140;
                }
                if (r == 0) {
                    *(s16 *)(cur + 0x12) = 0x46;
                } else if (r < 0) {
                    goto skipG;
                } else if (r < 3) {
                    *(s16 *)(cur + 0x12) = (r << 5) + 0xD5;
                } else {
                    goto skipG;
                }
                *(s16 *)(cur + 0x14) = *((u16 *)((u8 *)*slot + 0x14)) + 0x3C;
            skipG:
                func_80067EA4((struct UnkObject24 *)cur, 2, 2, D_8009AC10[r], 0,
                              1);
                *(u8 **)(prev + 0x1C) = cur;
                r++;
                prev = cur;
            } while (r < 3);
        }
        {
            s32 colorS;
            u8 *object;
            u8 *prim;
            colorS = color >> 24;
            object = D_800A3678 + D_800A35EC++ * 36;
            *(s16 *)(object + 0) = 2;
            *(s16 *)(object + 0x12) = 0;
            *(s16 *)(object + 0x14) = 0;
            *(s32 *)(object + 0x1C) = 0;
            object[4] = 0;
            object[3] = 0;
            object[2] = 0;
            *(s16 *)(object + 0x1A) = 0;
            *(s16 *)(object + 6) = 0;
            *(s16 *)(object + 0xA) = 0;
            *(s16 *)(object + 8) = colorS;
            *(s16 *)(object + 0xC) = colorS;
            *(s16 *)(object + 0xE) = 0;
            *(s16 *)(object + 0x10) = 0;
            *(s16 *)(object + 0x16) = 6;
            *(s16 *)(object + 0x18) = 8;
            object[2] = 0x80;
            object[3] = 0;
            object[4] = 0;
            prim = func_80057D50(1);
            *(u8 **)(object + 0x20) = prim;
            SetPolyF4(prim);
            SetSemiTrans(prim, 0);
            cur = object;
            *(s16 *)(prim + 0xA) = colorS;
            *(s16 *)(prim + 0xE) = colorS;
            colorS += 8;
            prim[4] = 0x80;
            prim[5] = 0;
            prim[6] = 0;
            *(s16 *)(prim + 8) = 0;
            *(s16 *)(prim + 0xC) = 6;
            *(s16 *)(prim + 0x10) = 0;
            *(s16 *)(prim + 0x12) = colorS;
            *(s16 *)(prim + 0x14) = 6;
            *(s16 *)(prim + 0x16) = colorS;
            *(s16 *)(cur + 0x1A) = 0;
            if (i != 0) {
                *(s16 *)(cur + 6) = 0x140;
            } else {
                *(s16 *)(cur + 6) = -0x140;
            }
            *(s16 *)(cur + 0x12) = 0xA9;
            *(s16 *)(cur + 0x14) =
                *((u16 *)((u8 *)D_800A37D8[i] + 0x14)) + 0x3B;
            *(u8 **)(prev + 0x1C) = cur;
            prev = cur;
            D_800A37FC[i] = cur;
            {
                s32 colorP1;
                colorP1 = colorS + 1;
                r = 0;
                do {
                    index = D_800A35EC++;
                    object = D_800A3678 + index * 36;
                    object[2] = 0;
                    *(s16 *)(object + 0x12) = 0;
                    *(s16 *)(object + 0x14) = 0;
                    *(s32 *)(object + 0x1C) = 0;
                    object[4] = 0;
                    object[3] = 0;
                    *(s16 *)(object + 0x1A) = 0;
                    *(s16 *)(object + 0) = 2;
                    *(s16 *)(object + 6) = 0;
                    *(s16 *)(object + 0xA) = 0;
                    *(s16 *)(object + 8) = colorS;
                    *(s16 *)(object + 0xC) = colorS;
                    *(s16 *)(object + 0xE) = 0;
                    *(s16 *)(object + 0x10) = 0;
                    *(s16 *)(object + 0x16) = 0xB;
                    *(s16 *)(object + 0x18) = 1;
                    object[2] = 0x80;
                    object[3] = 0;
                    object[4] = 0;
                    prim = func_80057D50(1);
                    *(u8 **)(object + 0x20) = prim;
                    SetPolyF4(prim);
                    SetSemiTrans(prim, 0);
                    cur = object;
                    prim[4] = 0x80;
                    prim[5] = 0;
                    prim[6] = 0;
                    *(s16 *)(prim + 8) = 0;
                    *(s16 *)(prim + 0xA) = colorS;
                    *(s16 *)(prim + 0xC) = 0xB;
                    *(s16 *)(prim + 0xE) = colorS;
                    *(s16 *)(prim + 0x10) = 0;
                    *(s16 *)(prim + 0x12) = colorP1;
                    *(s16 *)(prim + 0x14) = 0xB;
                    *(s16 *)(prim + 0x16) = colorP1;
                    *(s16 *)(cur + 0x1A) = 0;
                    if (i != 0) {
                        *(s16 *)(cur + 6) = 0x140;
                    } else {
                        *(s16 *)(cur + 6) = -0x140;
                    }
                    *(s16 *)(cur + 0x12) = r != 0 ? 0xFC : 0x11C;
                    *(s16 *)(cur + 0x14) =
                        *((u16 *)((u8 *)D_800A37D8[i] + 0x14)) + 0x37;
                    *(u8 **)(prev + 0x1C) = cur;
                    prev = cur;
                    r++;
                } while (r < 2);
            }
        }
        {
            s32 colorS;
            u8 *object;
            u8 *prim;
            colorS = color >> 24;
            r = 0;
            do {
                q = 0;
                do {
                    index = D_800A35EC++;
                    object = D_800A3678 + index * 36;
                    object[2] = 0;
                    object[3] = 0;
                    *(s16 *)(object + 0x18) = 6;
                    object[4] = 0;
                    object[2] = 0xFF;
                    *(s16 *)(object + 0x12) = 0;
                    *(s16 *)(object + 0x14) = 0;
                    *(s32 *)(object + 0x1C) = 0;
                    *(s16 *)(object + 0x1A) = 0;
                    *(s16 *)(object + 0) = 8;
                    *(s16 *)(object + 6) = 0;
                    *(s16 *)(object + 0xA) = 0;
                    *(s16 *)(object + 8) = colorS;
                    *(s16 *)(object + 0xC) = colorS;
                    *(s16 *)(object + 0xE) = 0;
                    *(s16 *)(object + 0x10) = 0;
                    *(s16 *)(object + 0x16) = value;
                    object[3] = 0x80;
                    prim = func_80057D50(1);
                    *(u8 **)(object + 0x20) = prim;
                    SetPolyF3(prim);
                    SetSemiTrans(prim, 0);
                    cur = object;
                    prim[4] = 0xFF;
                    prim[5] = 0x80;
                    prim[6] = 0x40;
                    *(s16 *)(cur + 0x1A) = 0;
                    if (i != 0) {
                        *(s16 *)(cur + 6) = 0x140;
                    } else {
                        *(s16 *)(cur + 6) = -0x140;
                    }
                    *(s16 *)(cur + 0x12) = ybase;
                    ybase += 0xF;
                    *(s16 *)(cur + 0x14) =
                        *((u16 *)((u8 *)D_800A37D8[i] + 0x14)) + 0x37;
                    *(u8 **)(prev + 0x1C) = cur;
                    prev = cur;
                    q++;
                } while (q < 2);
                r++;
            } while (r < 2);
        }
        {
            s32 colorS;
            s32 xpos;
            u8 *object;
            u8 *prim;
            colorS = color >> 24;
            xpos = ((s16 *)(D_800A37D8[i]))[10] + 0x3A;
            r = 0;
            do {
                value = r != 0 ? 3 : -3;
                object = D_800A3678 + D_800A35EC++ * 36;
                object[2] = 0;
                object[3] = 0;
                *(s16 *)(object + 0x16) = 6;
                *(s16 *)(object + 0x12) = 0;
                *(s16 *)(object + 0x14) = 0;
                *(s32 *)(object + 0x1C) = 0;
                object[4] = 0;
                *(s16 *)(object + 0x1A) = 0;
                *(s16 *)(object + 0) = 7;
                *(s16 *)(object + 6) = 0;
                *(s16 *)(object + 0xA) = 0;
                *(s16 *)(object + 8) = colorS;
                *(s16 *)(object + 0xC) = colorS;
                *(s16 *)(object + 0xE) = 0;
                *(s16 *)(object + 0x10) = 0;
                *(s16 *)(object + 0x18) = value;
                object[2] = 0xFF;
                object[3] = 0x80;
                object[4] = 0x40;
                prim = func_80057D50(1);
                *(u8 **)(object + 0x20) = prim;
                SetPolyF3(prim);
                SetSemiTrans(prim, 0);
                cur = object;
                prim[4] = 0xFF;
                prim[5] = 0x80;
                prim[6] = 0x40;
                *(s16 *)(cur + 0x1A) = 0;
                if (i != 0) {
                    *(s16 *)(cur + 6) = 0x140;
                } else {
                    *(s16 *)(cur + 6) = -0x140;
                }
                *(s16 *)(cur + 0x12) = 0xAC;
                *(s16 *)(cur + 0x14) = xpos;
                *(u8 **)(prev + 0x1C) = cur;
                prev = cur;
                r++;
                xpos += 0xC;
            } while (r < 2);
        }
    }
    ListSetFieldsAndEnable(D_800A37F8, -0x140, 0, 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/menu", func_80060FD8);
#endif

void func_80062874(s32 arg0, s32 arg1) {
    u8 *node;
    s16 flag;
    s32 index;

    index = arg0 & 0xFF;
    flag = index != 0;
    if ((arg1 & 0xFF) != 0) {
        node = ((void **)D_800A3A2CAbsolute)[index - 4];
    } else {
        node = ((void **)D_800A37C4Absolute)[index + 5];
    }
    if (node != 0) {
        do {
            if (*(u16 *)(node + 6) < 0x141U) {
                *(u16 *)(node + 0xE) = 2 - flag * 4;
                if (flag != 0) {
                    *(s16 *)(node + 0xA) = -0xA0;
                } else {
                    *(u16 *)(node + 0xA) = 0x1E0;
                }
            }
            node = *(u8 **)(node + 0x1C);
        } while (node != 0);
    }
}

extern s32 *D_800A37D8[];
extern u8 D_800A307C[];
extern u8 D_800A3088[];
extern u8 D_800A308C[];
extern u8 D_800A3350[];
extern u8 D_8009A4E0[];
extern u8 D_8009B00C[];
extern u8 D_8009B028[];

#ifdef NON_MATCHING
void func_80062910(s32 arg0) {
    u8 *node;
    u8 *prim;
    s32 a;
    u8 c;
    s32 id;
    s32 off;
    s32 f;
    u8 *base;
    s32 fontId;
    s32 sel;
    s8 i;
    s8 j;
    s32 idx;
    s32 cc;
    u8 *prim2;
    u8 *tab;
    u8 *new_var;

    node = (u8 *)D_800A37D8[arg0 & 0xFF];
    while (*(u16 *)node != 1) {
        node = *(u8 **)(node + 0x1C);
    }
    prim = *(u8 **)(node + 0x20);
    if (((s8 *)D_800A3A24)[arg0 & 0xFF] != ((s8 *)D_800A308C)[arg0 & 0xFF] &&
        ((s8 *)D_800A3A24)[arg0 & 0xFF] != 0) {
        ((s8 *)D_800A307C)[arg0 & 0xFF] = 0;
    }
    if (((s8 *)D_800A3A24)[arg0 & 0xFF] != 0) {
        ((s8 *)D_800A308C)[arg0 & 0xFF] = ((s8 *)D_800A3A24)[arg0 & 0xFF];
    }
    idx = arg0 & 0xFF;
    asm("" : "=r"(idx) : "0"(idx));
    a = ((s8 *)D_800A3A24)[idx];
    if (a != 0) {
        fontId = ((s8 *)D_800A3350)[a];
        new_var = D_8009B00C;
        base = new_var;
        c = *(base + 7 * fontId + ((s8 *)D_800A307C)[idx]);
    } else {
        c = D_800A3088[idx];
    }
    id = (s8)c;
    off = id * 6;
    D_800A3088[idx] = c;
    *(u16 *)(prim + 0xE) = GetClut(0x100, *(s16 *)&D_8009B028[off + 4]);
    *(u16 *)(prim + 0x16) =
        GetTPage(1, 0, *(s16 *)&D_8009B028[off], *(s16 *)&D_8009B028[off + 2]);
    prim[0xC] = 0;
    prim[0xD] = *(u16 *)&D_8009B028[off + 2];
    prim[0x14] = *(u16 *)(node + 0x16);
    prim[0x15] = *(u16 *)&D_8009B028[off + 2];
    prim[0x1C] = 0;
    prim[0x1D] = D_8009B028[off + 2] + node[0x18];
    prim[0x24] = *(u16 *)(node + 0x16);
    prim[0x25] = D_8009B028[off + 2] + node[0x18];
    node = *(u8 **)(node + 0x1C);
    prim = *(u8 **)(node + 0x20);
    if (id == 1 && (((s8 *)D_800A3A24)[arg0 & 0xFF] == 5 ||
                    ((s8 *)D_800A3A24)[arg0 & 0xFF] == 7)) {
        prim[4] = -(((s8 *)D_800A3A24)[arg0 & 0xFF] == 7);
        prim[5] = -(((s8 *)D_800A3A24)[arg0 & 0xFF] == 5);
        prim[6] = 0;
        node[5] = 1;
    } else {
        node[5] = 0;
    }
    node = *(u8 **)(node + 0x1C);
    node[5] = !((s8 *)D_800A3A24)[arg0 & 0xFF];
    node = *(u8 **)(node + 0x1C);
    node = *(u8 **)(node + 0x1C);
    *(s32 *)(*(u8 **)(node + 0x20) + 8) = ((s8 *)D_800A307C)[arg0 & 0xFF] + 1;
    sel = ((s8 *)D_800A3A24)[arg0 & 0xFF];
    c = ((s8 *)D_800A3A24)[arg0 & 0xFF];
    if (sel == 0) {
        c = D_800A308C[arg0 & 0xFF];
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 7; j++) {
            node = *(u8 **)(node + 0x1C);
            do {
            } while (0);
            f = ((s8 *)D_800A3350)[(s8)c];
            tab = D_8009A4E0;
            cc = ((s8 *)D_800A307C)[(u8)arg0];
            prim2 = *(u8 **)(node + 0x20);
            base = 392 * f + tab;
            base = base + 56 * cc;
            *(s32 *)(prim2 + 8) = *(s32 *)(base + (7 * i + j) * 4);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/menu", func_80062910);
#endif

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

extern u8 *D_800A37FC[];
extern s32 *D_800A37D8[];
extern u8 D_800AEE3E[];
extern u8 D_800AEE41[];

void func_80062D38(s32 arg0, s32 arg1, u8 *arg2) {
    u8 *obj;
    s32 j;
    s32 i;
    s32 base9;
    s32 idx;
    s32 mode;
    s32 val;
    s32 tmp;
    u8 *p;
    s32 **entry;

    obj = D_800A37FC[arg0 & 0xFF];
    for (i = 2; i >= 0; i--) {
        obj = *(u8 **)(obj + 0x1C);
    }
    for (i = 0; i < 3; i++) {
        mode = arg1 & 0xFF;
        idx = arg0 & 0xFF;
        base9 = idx * 9;
        j = 0;
        /*
         * p is set twice, so the loop pass doesn't strength-reduce
         * arg2 + i. val and tmp also hold the table address and index:
         * with two live ranges each, the entry chain stays in the loop
         * and takes v1/v0 as in retail.
         */
        p = arg2;
        p += i;
        val = (s32)D_800A37D8;
        tmp = idx << 2;
        entry = (s32 **)(val + tmp);
        do {
            switch (i) {
            case 0:
            case 1:
                if (mode == 2) {
                    val = (p[0] * 49) >> 8;
                    if (val >= 0x32) {
                        val = 0x31;
                    }
                } else {
                    if (i == 0) {
                        if (D_800AEE3E[base9] < arg2[0]) {
                            arg2[0] = D_800AEE3E[base9];
                        }
                        val = D_800AEE3E[base9] - arg2[0];
                    } else {
                        if (p[0] < D_800AEE41[base9]) {
                            p[0] = D_800AEE41[base9];
                        }
                        val = p[0] - D_800AEE41[base9];
                    }
                    val = (val * 3) >> 3;
                    if (val >= 0x31) {
                        val = 0x30;
                    }
                }
                val -= 0x37;
                tmp = *(u16 *)((u8 *)entry[0] + 0x14);
                *(s16 *)(obj + 0x14) = tmp - val;
                break;
            case 2:
                val = (arg2[2] * 103) >> 8;
                if (val >= 0x68) {
                    val = 0x67;
                }
                *(s16 *)(obj + 0x12) = val + 0x78;
                break;
            }
            obj = *(u8 **)(obj + 0x1C);
            j++;
        } while (j < 2);
    }
}

extern u8 *D_800A3A84[];
extern s32 D_8009ABFC[];
void func_80062F04(u8 index, u8 kind, u8 sub) {
    u32 code;
    u8 *object;
    s32 *target;

    if (kind == 2) {
        code = 2;
        if (sub < 4) {
            code = 3;
        }
    } else {
        code = 2;
        if (sub < 2) {
            code = 4;
        }
    }
    object = D_800A3A84[index];
    target = *(s32 **)(object + 0x20);
    *(target + 2) = D_8009ABFC[code];
}

extern u8 *D_800A37FC[];
extern s32 *D_800A37D8[];
extern u8 D_800AEE3D[];
extern u8 D_800AEE3E[];
extern u8 D_800AEE40[];
extern u8 D_800AEE41[];
extern u8 D_800AEE42[];
extern u8 D_800AEE43[];

void func_80062F6C(s32 arg0, s32 arg1) {
    s32 i;
    u8 *obj;
    s32 offset;
    s32 **entry;
    s32 b42;
    register s32 b43 asm("a0");
    s32 val;
    s32 lim;
    s32 base2;
    s32 d;
    s32 a;
    s32 denom;
    s32 b;
    s32 delta;
    s32 idx;
    s32 base9;
    s32 y;
    s32 j;
    s32 prod;
    s16 sum;

    idx = arg0 & 0xFF;
    obj = (u8 *)D_800A37FC[idx];
    i = 0;
    base9 = idx * 9;
    base2 = (s32)D_800A37D8;
    entry = (s32 **)(idx * 4 + base2);
    offset = -3;
    for (; i < 3; i++) {
        switch (i) {
        case 0:
            b42 = D_800AEE42[base9];
            b43 = D_800AEE43[base9];
            lim = 0x80;
            val = lim - b42;
            val = (val * 103) >> 8;
            y = b43 - 0x80;
            if (val >= 0x68) {
                val = 0x67;
            }
            y = (y * 103) >> 8;
            if (y >= 0x68) {
                y = 0x67;
            }
            sum = val + y;
            *(s16 *)(obj + 0x16) = sum;
            if (sum >= 0x68) {
                *(s16 *)(obj + 0x16) = 0x67;
            }
            *(s16 *)(obj + 0x12) = 0xAC - val;
            break;
        case 1:
        case 2:
            delta = arg1 & 0xFF;
            if (delta == 2) {
                j = offset + base9;
                val = D_800AEE3D[j];
                prod = val * 49;
                val = (s32)prod >> 0x8;
                if (val >= 0x32) {
                    val = 0x31;
                }
            } else {
                if (i == 1) {
                    denom = D_800AEE3E[base9];
                    d = D_800AEE3D[base9];
                    val = denom - d;
                } else {
                    a = D_800AEE40[base9];
                    b = D_800AEE41[base9];
                    val = a - b;
                    denom = 0xFF - b;
                }
                prod = val * 48;
                val = prod / denom;
                if (val >= 0x31) {
                    val = 0x30;
                }
            }
            *(s16 *)(obj + 0x18) = val;
            delta = val - 0x38;
            *(s16 *)(obj + 0x14) = *(u16 *)((u8 *)entry[0] + 0x14) - delta;
            break;
        }
        obj = *(u8 **)(obj + 0x1C);
        offset = offset + 3;
    }
}

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

INCLUDE_ASM("asm/nonmatchings/menu", func_800631DC);

void func_80063538(s32 arg0, s32 arg1) {
    extern u8 *func_8005B474(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                             s32);
    extern u8 *D_800A3628[];
    s32 cmd;
    u8 **table;
    u8 *node;
    u8 *prev;
    s32 i;
    s32 j;
    s32 offs;

    cmd = 0x6A;
    j = 0;
    table = D_800A3628;
    for (; j < 2; j++) {
        for (i = 0; i < 2; i++) {
            offs = 4;
            if (i != 0) {
                offs = -4;
            }
            node =
                func_8005B474(arg1, cmd, offs, 8, 0, 0x28, 0x64, 0xC8, 0, 1, 0);
            *(s16 *)(node + 0x1A) = 0;
            if (i != 0) {
                *(s16 *)(node + 0x12) = 0x2E;
            } else {
                *(s16 *)(node + 0x12) = -0x2E;
            }
            *(s16 *)(node + 0x14) = 0;
            *(s16 *)(node + 0x0E) = 0;
            if (i == 0) {
                *table = node;
            } else {
                *(u8 **)(prev + 0x1C) = node;
            }
            prev = node;
        }
        cmd += 0x33;
        table += 1;
    }
}

extern u8 *D_800A3628[];
void func_80063638(u8 mode) {
    s16 left;
    s16 width;
    u8 *node;
    s32 i;

    if (mode != 0) {
        left = 0x6A;
        width = 0x2E;
    } else {
        left = 0xBA;
        width = 0x37;
    }
    node = D_800A3628[0];
    for (i = 0; i < 2; i++) {
        *(s16 *)(node + 8) = left;
        *(s16 *)(node + 0xC) = left;
        *(s16 *)(node + 0x12) = width;
        if (i == 0) {
            *(s16 *)(node + 0x12) = -width;
        }
        node = *(u8 **)(node + 0x1C);
    }
}

extern u8 *D_800A35E4[];
void func_80063694(u8 index, s16 dx, s16 dy, s16 code) {
    u8 *node;

    node = D_800A35E4[index];
    if (node != 0) {
        do {
            *(s16 *)(node + 6) = *(s16 *)(node + 0x12) + dx;
            *(s16 *)(node + 0xE) = code;
            node[5] = code;
            *(s16 *)(node + 0xA) = *(s16 *)(node + 0x12) + dy;
            node = *(u8 **)(node + 0x1C);
        } while (node != 0);
    }
}

extern char *D_8009AC1C[];
extern u8 *D_800A3868[];
void func_800636EC(u8 index, u8 kind) {
    u8 *node;
    u8 *object;
    s32 value;

    node = D_800A3868[index];
    object = *(u8 **)(node + 0x20);
    *(u8 **)(object + 8) = D_8009AC1C[kind];
    func_8005A7B8(object[1], object[2]);
    value = func_8005B0E4(0x64, *(s32 *)(object + 8));
    *(s16 *)(node + 6) = value + 0xA;
    *(s16 *)(node + 0x12) = value - 0x32;
}

extern u8 *D_800A3868[];
void func_80063770(u8 index) {
    u8 *node;
    s16 value;

    node = D_800A3868[index];
    if (node != 0) {
        do {
            value = *(s16 *)(node + 0x1A);
            if (value > 0) {
                *(s16 *)(node + 0x1A) = -value;
            } else if (value == 0) {
                *(s16 *)(node + 0x1A) = -0x8000;
            }
            node = *(u8 **)(node + 0x1C);
        } while (node != 0);
    }
}

extern u8 *D_800A3868[];
void func_800637D8(u8 index) {
    u8 *node;
    s16 value;

    node = D_800A3868[index];
    if (node != 0) {
        do {
            value = *(s16 *)(node + 0x1A);
            if (value == -0x8000) {
                *(s16 *)(node + 0x1A) = 0;
            } else if (value < 0) {
                *(s16 *)(node + 0x1A) = -value;
            }
            node = *(u8 **)(node + 0x1C);
        } while (node != 0);
    }
}

void func_8006383C(void) {
    u32 i;
    u32 greyLevel;

    for (i = 0; i < 0x100; i++) {
        greyLevel = i >> 2;
        ((u32 *)SCRATCHPAD_BASE)[i] =
            (greyLevel << 0x10) | (greyLevel << 8) | greyLevel;
    }
}

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

void func_80063874(void) {
    void *table;
    u8 *head;
    u8 *src;
    u8 *end;
    u32 count;
    s32 i;
    u8 *elem;
    s32 n;
    s32 first;
    s32 second;

    D_800A36F4_w42 = (s32)func_80058094(7, &table, SCRATCH_TOP);
    if (D_800A3658_w42[0] == 0) {
        func_8001E230(8, STACK_BLOCK_801A0000 + 0x1A000);
        head = D_800A37E4_w42[0];
        src = *(u8 **)head;
        end = *(u8 **)(head + 4);
        count = (u32)(end - src) >> 2;
        for (i = 0; i < count; i++) {
            D_800BE998_w42[i] = ((u32 *)src)[i];
        }
        D_800A3658_w42[0] = 1;
    }
    D_800A36CC_w42[0] = (u8 *)D_800BE998_w42;
    D_800A353C_w42[0] = MathFixedDivide(6, 0xF);
    D_800A3758_w42[0] = MathFixedDivide(1, 2);
    D_800A3630_w42[0] = 2;
    D_800A2F30_w42[0] = 0;
    D_800A3754_w42[1] = D_800A3538_w42[1];
    i = 0;
    elem = D_800AE88C_w42;
    do {
        first = D_800A36F4_w42 + ((s32 *)table)[i];
        second = -(i == 0);
        D_800A3574_w42[0] = elem;
        func_80032450(first, second);
        func_80032494(D_800A3570_w42[1]);
        elem += 0x44;
        do {
        } while (0);
        n = D_800A3630_w42[0];
        i++;
    } while (i < n);
    if ((i = n) < 10) {
        do {
            *(s32 *)((u8 *)D_800AE8C0_w42 + ((i * 17) << 2)) = 0;
            i++;
        } while (i < 10);
    }
    func_8001DFC8();
}

void func_80063A20(void) {
}

void func_80063A28(void) {
    RECT rect;
    s32 i;
    s16 srcX;
    s16 tile;

    i = 0;
    tile = 0x40;
    srcX = 0x300;
    while (i < 2) {
        rect.x = (i % 4) * 0x40 + 0x300;
        rect.y = tile;
        rect.h = tile;
        rect.w = tile;
        MoveImage(&rect, i * 0x40, 0x100);
        rect.y = 0x3F;
        rect.h = 1;
        rect.x = srcX;
        rect.w = 0x10;
        MoveImage(&rect, 0, 0x140 + i);
        srcX += 0x10;
        i++;
    }
}

void func_80063AE0(s32 arg0, s32 arg1) {
    RECT rect;

    if (arg1 >= 2) {
        rect.x = (arg1 % 4) * 0x40 + 0x300;
        rect.y = (arg1 / 4) * 0x40 + 0x40;
        rect.h = 0x40;
        rect.w = 0x40;
        MoveImage(&rect, arg0 * 0x40 + 0x300, 0x40);
        rect.x = (arg1 % 16) * 0x10 + 0x300;
        rect.y = 0x3F - arg1 / 16;
        rect.h = 1;
        rect.w = 0x10;
        MoveImage(&rect, arg0 * 0x10 + 0x300, 0x3F);
    } else {
        rect.x = (arg1 % 4) * 0x40;
        rect.y = (arg1 / 4) * 0x40 + 0x100;
        rect.h = 0x40;
        rect.w = 0x40;
        MoveImage(&rect, arg0 * 0x40 + 0x300, 0x40);
        rect.y = arg1 + 0x140;
        rect.h = 1;
        rect.x = 0;
        rect.w = 0x10;
        MoveImage(&rect, arg0 * 0x10 + 0x300, 0x3F);
    }
}

INCLUDE_ASM("asm/nonmatchings/menu", func_80063C34);

extern s32 D_800A2E84Absolute[];
extern u8 *func_8002D874(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80063874(void);

void func_80063E7C(void) {
    RECT rect;
    u8 *entry;
    u8 *prev1;
    u8 *prev2;
    s32 i;
    s16 srcX;
    s16 tile;

    func_80063874();
    D_800A2E84Absolute[0] = 0;
    entry = func_8002D874(-1, 0, 0, -1);
    *(s32 *)(entry + 0) = -0x2EE;
    *(s32 *)(entry + 4) = 0xC8;
    *(s32 *)(entry + 8) = 0xC8;
    *(u8 *)(entry + 0x20C) = 4;
    D_800A3558[0] = (s32)entry;
    D_800A38AC[0] = (s32)entry;
    *(s32 *)(entry + 0x3DC) = 0;
    D_800A2E94[0] = 0;
    prev1 = entry;
    entry = func_8002D874(0, 0, 0x1B, 0);
    *(s32 *)(entry + 0) = 0x1F4;
    *(s32 *)(entry + 4) = 0;
    *(s32 *)(prev1 + 0x3E0) = (s32)entry;
    *(s32 *)(entry + 0x3DC) = (s32)prev1;
    D_800A3554[0] = entry;
    prev2 = entry;
    entry = func_8002D874(0, 1, 0x18, -1);
    i = 0;
    tile = 0x40;
    srcX = 0x300;
    *(s32 *)(entry + 0) = 0;
    *(s32 *)(entry + 4) = 0;
    *(s32 *)(prev2 + 0x3E0) = (s32)entry;
    *(s32 *)(entry + 0x3DC) = (s32)prev2;
    *(s32 *)(entry + 0x3E0) = 0;
    while (i < 2) {
        rect.x = (i % 4) * 0x40 + 0x300;
        rect.y = tile;
        rect.h = tile;
        rect.w = tile;
        MoveImage(&rect, i * 0x40, 0x100);
        rect.y = 0x3F;
        rect.h = 1;
        rect.x = srcX;
        rect.w = 0x10;
        MoveImage(&rect, 0, 0x140 + i);
        srcX += 0x10;
        i++;
    }
}

/* The empty asm input of arg1 (and where it sits) stretches arg1's live
 * range so global allocation ranks the three parameters arg2, arg1, arg0,
 * handing them s1, s2, s3 like retail. */
extern u8 *D_800A35E4[];
void func_8003271C(s32 arg0);
void func_8001775C(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80064000(s32 arg0, s32 arg1, s32 arg2) {
    u8 *entry;
    u8 *obj;
    u16 height;
    s32 x;
    u32 i;
    u32 grey;
    u32 *pad;
    s16 t;
    s32 v1;
    s32 v0;
    u16 result;

    entry = D_800A35E4[arg0 & 0xFF];
    height = *(u16 *)(entry + 0xA);
    do {
        if (height < 0x140U || *(s16 *)(entry + 6) != (s16)height) {
            obj = *(u8 **)(entry + 0x20);
            if (arg2 & 0xFF) {
                SetGeomOffset(*(s16 *)(entry + 6), 0x2D);
            } else {
                SetGeomOffset(*(s16 *)(entry + 6), *(s16 *)(entry + 8));
            }
            if (arg1 & 0xFF) {
                i = 0;
                pad = (u32 *)SCRATCHPAD_BASE;
                do {
                    grey = i >> 2;
                    pad[0] = (grey << 0x10) | (grey << 8) | grey;
                    pad += 1;
                    i += 1;
                } while (i < 0x100U);
            } else {
                func_8003271C(0);
            }
            func_8001775C(obj, 0, 0xFA, 0x44C);
            if (!(arg0 & 0xFF) || (arg2 & 0xFF) || D_800A39E4[0] == 0xE) {
                asm("" : : "r"(arg1));
                t = *(s16 *)(obj + 0x20E);
                v1 = t + 0xFEC;
                if (v1 < 0) {
                    v0 = t + 0x1FEB;
                } else {
                    v0 = v1;
                }
                result = v1 - ((v0 >> 0xC) << 0xC);
            } else {
                result = *(u16 *)(D_800A3554[0] + 0x20E);
            }
            *(s16 *)(obj + 0x20E) = result;
        }
    } while (0);
}

void *func_80058094(s32 arg0, void **arg1, s32 arg2);
void TextureLoadTim(void *arg0);

void func_80064174(void) {
    void *data;
    s32 *offsets;
    s32 i;

    data = func_80058094(10, (void **)&offsets, 0);
    for (i = 0; i < 0x18; i++) {
        TextureLoadTim((u8 *)data + offsets[i]);
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

INCLUDE_ASM("asm/nonmatchings/menu", func_80064208);

#ifdef NON_MATCHING
extern u8 *D_800A3744[];
extern u8 *D_800A3958[];
void func_800645A4(s32 arg0, s32 arg1) {
    u8 *node;
    u8 *prim;
    u8 *prim2;
    u8 *str;
    u32 idx;
    s32 y;
    s32 offset;
    s32 advance;
    s32 i;
    s32 x;
    s32 h;
    u32 q;

    node = D_800A3744[arg0 & 0xFF];
    idx = arg1 & 0xFF;
    prim = *(u8 **)(node + 0x20);
    *(s16 *)(prim + 0xE) = GetClut(0x100, 0x1E7 - idx);
    q = idx / 12;
    y = (q & 0xFF) * 0x48;
    /* Keep the scaled row in the same register before its base add. */
    asm("" : "=r"(y) : "0"(y));
    y += 0x140;
    q = idx - q * 12;
    *(s16 *)(prim + 0x16) = GetTPage(1, 0, (q << 5 & 0x1F80) + 0x140, y);
    prim[0xC] = (idx & 3) << 6;
    prim[0xD] = y;
    prim[0x14] = ((idx & 3) << 6) + 0x3F;
    prim[0x15] = y;
    asm("" : "=r"(y) : "0"(y));
    prim[0x1C] = (idx & 3) << 6;
    prim[0x1D] = y + 0x47;
    prim[0x24] = ((idx & 3) << 6) + 0x3F;
    prim[0x25] = y + 0x47;
    node = *(u8 **)(node + 0x1C);
    func_8005A7B8(2, 4);
    h = func_8005A84C();
    x = *(s16 *)(node + 8);
    offset = *(s32 *)(D_800A3A5C + idx * 4);
    for (i = 0; i < 6; i++) {
        prim2 = *(u8 **)(node + 0x20);
        if (i == 0) {
            *(u8 **)(prim2 + 8) = D_8009AC1C[idx];
        } else {
            str = (u8 *)(D_800A3358 + offset);
            *(u8 **)(prim2 + 8) = str;
            while (*str != 0) {
                str++;
                offset++;
            }
            offset++;
        }
        *(s16 *)(node + 8) = x;
        if (i == 0) {
            x = h + 0x32;
        } else {
            if (i == 1 || (u32)(i - 4) < 2) {
                y = func_8005B138(*(u8 **)(prim2 + 8)) * h;
            } else {
                y = h;
            }
            x += y;
        }
        if (i == 3) {
            x += 5;
        }
        node = *(u8 **)(node + 0x1C);
    }
    func_80063AE0(arg0 & 0xFF, arg1 & 0xFF);
    if ((arg1 & 0xFF) == 2 || (arg1 & 0xFF) == 5 || (arg1 & 0xFF) == 7 ||
        (u32)((arg1 - 9) & 0xFF) < 2 || (arg1 & 0xFF) == 0x11 ||
        (u32)((arg1 - 0x15) & 0xFF) < 2) {
        str = D_800A3958[arg0 & 0xFF];
        advance = -1;
    } else {
        str = D_800A3958[arg0 & 0xFF];
        advance = 1;
    }
    *(s16 *)(str + 0x1A) = advance;
}
#else
INCLUDE_ASM("asm/nonmatchings/menu", func_800645A4);
#endif

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

void func_80064898(void) {
    func_8005B8B8(D_800A38FC[1], 0xFF);
    if (D_800A38FC[0] != 0) {
        func_8005B688(D_800A38FC[0], 1);
        func_8005B8B8(D_800A3900[-1], 0xFF);
    }
    if (D_800A39A0[0] != 0) {
        func_8005B688(D_800A39A0[0], 1);
        func_8005B8B8(D_800A39A4nm[-1], 0xFF);
    }
    func_8005B688(D_800A35E4[0], 1);
    func_8005B8B8(D_800A35E8[-1], 0xFF);
    func_80064000(0, 0, 0);
    if (D_800A3A14 != 0 || D_800A39AC[-3] != 0) {
        func_8005B688(D_800A35E8[0], 1);
        func_8005B8B8(D_800A35E8[0], 0xFF);
        func_80064000(1, 0, 0);
    }
}

void func_8006499C(void) {
    RECT rect;

    rect.x = 0x140;
    rect.y = 0x140;
    rect.h = 0x48;
    rect.w = 0x140;
    MoveImage(&rect, 0x140, 0);
    DrawSync(0);
    rect.x = 0x280;
    rect.y = 0x140;
    rect.h = 0x48;
    rect.w = 0x40;
    MoveImage(&rect, 0x140, 0x48);
    DrawSync(0);
    rect.x = 0x140;
    rect.y = 0x188;
    rect.h = 0x48;
    rect.w = 0x100;
    MoveImage(&rect, 0x180, 0x48);
    rect.x = 0x240;
    rect.y = 0x188;
    rect.h = 0x48;
    rect.w = 0x80;
    MoveImage(&rect, 0x140, 0x90);
    DrawSync(0);
    rect.x = 0x100;
    rect.y = 0x1D0;
    rect.h = 0x18;
    rect.w = 0x100;
    MoveImage(&rect, 0x140, 0xD8);
    DrawSync(0);
}

extern u8 D_8009B00C[];
extern u8 D_8009B028[];
extern u8 D_8009B02A[];
extern u16 D_8009B048[][7];
extern u8 D_8009B04A[];
extern u16 D_8009B050[][7];
extern u16 D_8009B054[][7];

void func_80064AB4(u8 *prim, u8 idx) {
    SetShadeTex(prim, 0);
    ((u8 *)prim)[4] = 0x80;
    ((u8 *)prim)[5] = 0x80;
    ((u8 *)prim)[6] = 0x80;
    SetSemiTrans(prim, 0);
    *(s16 *)(prim + 0xE) = GetClut(0x140, 0xEF - idx);
    *(s16 *)(prim + 0x16) =
        GetTPage(D_8009B054[idx][0], 0, D_8009B048[idx][0], D_8009B048[idx][1]);
    ((u8 *)prim)[0xC] = D_8009B050[idx][0];
    ((u8 *)prim)[0xD] = D_8009B048[idx][5];
    ((u8 *)prim)[0x14] = D_8009B04A[idx * 14 + 6] + 0x3F;
    ((u8 *)prim)[0x15] = D_8009B054[idx][-1];
    ((u8 *)prim)[0x1C] = D_8009B048[idx][4];
    ((u8 *)prim)[0x1D] = D_8009B028[idx * 14 + 0x2A] + 0x47;
    ((u8 *)prim)[0x24] = D_8009B00C[idx * 14 + 0x44] + 0x3F;
    ((u8 *)prim)[0x25] = D_8009B02A[idx * 14 + 0x28] + 0x47;
}

extern u8 *D_8009A3F0[];
extern u8 *D_8009A400[];
extern u8 *D_8009A418[];
extern u8 D_800A3698;
extern u8 D_800A3A4C;
extern u8 *D_800A39D8;
extern u8 *D_800A369C;
void func_80064C14(void) {
    extern u32 *D_800A38C4;
    extern s32 D_800A367C;
    extern s32 D_800A2EB0Absolute[];

    D_800A38C4 = (u32 *)gOrderingTables;
    D_800A39C8[0] = gOrderingTables;
    D_800A39D8 = gOrderingTables + 0x20;
    D_800A369C = gOrderingTables + 0x13A8;
    if (D_800A2EB0Absolute[0] == 0) {
        D_800A3698 = strlen(D_8009A3F0[0]);
    } else {
        D_800A3698 = strlen(D_8009A418[0]);
    }
    D_800A3A4C = strlen(D_8009A400[0]);
    /* Preserve the byte reloads observed after these stores in retail. */
    D_800A3698 += *(volatile u8 *)&D_800A3A4C;
    D_800A367C = (s32)(D_800A369C + *(volatile u8 *)&D_800A3698 * 0x28);
    func_8005A6EC(2, 4, D_800A39D8);
}

extern u8 D_800BDD62[], D_800BDDBE[], D_800BDDC0[], D_800BDD64[];
extern u8 D_800BDD65[], D_800BDD66[], D_800BDD67[], D_800BDDC1[];
extern u8 D_800BDDC2[], D_800BDDC3[];
extern DRAWENV D_800BDD4C[];
extern DISPENV D_800BDE04[];
void GraphicsInitDoubleBuffer(s32 mode) {
    s32 height;
    DRAWENV *draw;
    DRAWENV *draw2;
    DISPENV *disp;
    u8 *flags;

    height = 0xF0;
    draw = D_800BDD4C;
    SetDefDrawEnv(draw, 0, 0, 0x140, height);
    disp = D_800BDE04;
    SetDefDispEnv(disp, 0, 0, 0x140, height);
    draw2 = (DRAWENV *)((u8 *)draw + 0x5C);
    if ((u8)mode != 0) {
        SetDefDrawEnv(draw2, 0, 0, 0x140, height);
        SetDefDispEnv((DISPENV *)((u8 *)disp + 0x14), 0, 0, 0x140, height);
    } else {
        SetDefDrawEnv(draw2, 0x140, 0, 0x140, height);
        SetDefDispEnv((DISPENV *)((u8 *)disp + 0x14), 0x140, 0, 0x140, height);
    }
    asm("" : "=r"(flags) : "0"(D_800BDD62));
    flags[0] = 0;
    D_800BDDC0[0] = 1;
    D_800BDD64[0] = 1;
    D_800BDDBE[0] = 0;
    if ((u8)mode != 0) {
        D_800BDD65[0] = 0;
        D_800BDD66[0] = 0;
        D_800BDD67[0] = 0xA;
        flags[0x5F] = 0;
        flags[0x60] = 0;
        flags[0x61] = 0xA;
    } else {
        D_800BDD65[0] = 0;
        D_800BDD66[0] = 7;
        D_800BDD67[0] = 0x26;
        D_800BDDC1[0] = 0;
        D_800BDDC2[0] = 7;
        D_800BDDC3[0] = 0x26;
    }
    SetDispMask(0);
    PutDrawEnv(D_800BDD4C);
    PutDispEnv(D_800BDE04);
}

void func_80064E6C(void) {
    extern u8 *D_800A369C;
    extern u8 D_800A3698;
    extern u8 D_800A3073[];
    extern u8 D_800A3884;
    extern s32 D_800A367C;
    extern u32 *D_800A38C4;
    extern u8 *D_8009A3F0[];
    extern u8 *D_8009A400[];
    extern u8 *D_8009A418[];
    /* The post-call string reads go through the neighbouring symbols so
     * cse can't share one address register with the pre-call reads. */
    extern u8 *D_8009A3EC[];
    extern u8 *D_8009A414[];
    extern s32 D_800A2EB0Absolute[];
    extern u8 D_800A3778;
    extern u8 D_800A35DC;
    extern void GraphicsInitDoubleBuffer(s32);
    extern void func_80065058(s32, s32);
    extern void func_80065F80(void);
    extern void func_80066080(s32);
    u8 **base;

    ClearOTagR(D_800A38C4, 4);
    GraphicsInitDoubleBuffer(1);
    func_8006499C();
    D_800A367C = (s32)D_800A369C;
    func_8005A7B8(2, 4);
    func_8005A818(0x80, 0x80, 0xC0);
    base = D_8009A400;
    func_8005A9F4((s32)*base, (s16)func_8005B0E4(0x140, (s32)*base), 0xC8, 0, 0,
                  0, 0, 0);
    if (D_800A2EB0Absolute[0] == 0) {
        func_8005A9F4((s32)D_8009A3EC[1],
                      (s16)func_8005B0E4(0x140, (s32)D_8009A3F0[0]), 0xC8, 0, 0,
                      0, 0, 0);
    } else {
        func_8005A9F4((s32)D_8009A414[1],
                      (s16)func_8005B0E4(0x140, (s32)D_8009A418[0]), 0xC8, 0, 0,
                      0, 0, 0);
    }
    ClearOTagR(D_800A38C4, 4);
    D_800A367C = (s32)(D_800A369C + D_800A3698 * 0x28);
    if (D_800A3644[0] != 0 && D_800A3073[0] == 0) {
        func_80065F80();
        func_80066080(1);
    } else {
        func_80065838(1);
        D_800A3778 = 0;
        func_80065058(*(volatile u8 *)&D_800A3778, 1);
        if (D_800A3644[0] != 0 && D_800A3073[0] != 0) {
            D_800A35DC = 3;
        } else {
            D_800A35DC = 0xB;
        }
    }
    D_800A3884 = 0;
}

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

#ifdef NON_MATCHING
/* 2026-10-11 harvest, real-TU asm-differ 13003 -> 10555:
 * 1. yOffset lost its volatile: one memory home, one value. Volatile
 *    forced a load per read and broke the allocator cascade.
 * 2. Permuter 7760: (a) case 3 duplicates its height/red/green/blue/
 *    x1off arm under if (x0)/else (duplicated-arm barrier);
 *    (b) leftX = 0x17 hoisted before the D_8009A3EC[0] call with
 *    x = leftX in the loop; (c) b2 = (s32)entry routes the
 *    func_80018588 buffer into func_8005A9F4.
 * 3. asm("" : "=r"(match) : "r"(match)) after match = slots slows the
 *    cursor/match CSE.
 * Dead address-taken pad restores retail frame 0xa8 (1596 -> 1585
 * differing text bytes, size 0x7e0). cursor/match still one
 * addiu plus a derived copy where retail has two addiu, and ours reads
 * D_800BE70C/D_800A36E0/D_800A3644 through cached t-reg bases with
 * 0-offset loads where retail uses %hi/%lo displacements off the index.
 */
extern u8 D_800A3950[];
extern u8 D_800A305B[];
extern u8 *D_8009A360[];
extern u8 *D_8009A3A4[];
extern u8 *D_8009A3E8[];
extern u8 *D_8009A41C[];
extern u8 *D_8009A3EC[];
extern u8 *D_8009ACE0[];
extern s32 D_800AEB34[];
extern u8 *D_8009A42C[];
extern u16 D_800A3A44;
extern s16 D_800A3940Signed asm("D_800A3940");
extern u8 D_800A3760;
extern u8 *D_800A3568;
extern u8 *D_800A3970;
extern u32 *D_800A38C4;
extern void func_8005A9F4(s32, s16, s16, u8, u8, s32, u8, u8);
void func_80065058(u8 id, s32 shift) {
    u8 entry[0x40];
    u8 slots[2];
    u8 pad[8];
    u8 *cursor;
    u8 *match;
    u8 *prim;
    s32 yOffset;
    s16 leftX;
    s32 i;
    s32 x0;
    s32 x1off;
    s32 height;
    s32 red;
    s32 green;
    s32 blue;
    s32 yBase;
    s32 x;
    u8 color;
    s32 r2;
    s32 g2;
    s32 b2;

    /* Keep the unused address-taken local in the retail frame. */
    if (0) {
        func_80018588(0, -1, pad);
    }
    yOffset = -((shift & 0xFF) != 0) & -0x140;
    cursor = slots;
    match = slots;
    asm("" : "=r"(match) : "r"(match));
    for (i = 0; i < 2; i++) {
        *cursor = 0xFF;
        if (D_800BE70C[id * 2 + i] == D_800A36E0[0]) {
            *match = i;
            match++;
        }
        if (D_800A3644[0] != 0 && D_800BE70C[id * 2 + i] == D_800A36E1[0]) {
            *match = i;
            match++;
        }
        cursor++;
    }
    x1off = 0x11C;
    x0 = yOffset + 0x12;
    for (i = 0; i < 3; i++) {
        prim = (u8 *)D_800A367C;
        D_800A367C = (s32)prim + 0x28;
        SetPolyF4((POLY_F4 *)prim);
        SetSemiTrans(prim, 0);
        switch (i) {
        case 0:
            height = 0x1C;
            red = 0;
            green = 0;
            blue = 0x80;
            yBase = 0x3E;
            prim[4] = 0;
            prim[5] = 0;
            prim[6] = blue;
            break;
        case 1:
            height = 0x48;
            red = 0;
            green = 0;
            blue = 0x4C;
            yBase = 0x5A;
            prim[4] = 0;
            prim[5] = 0;
            prim[6] = blue;
            break;
        case 2:
            height = 0x12;
            red = 0;
            green = 0;
            blue = 0xC0;
            yBase = 0xA2;
            prim[4] = 0;
            prim[5] = 0;
            prim[6] = blue;
            break;
        case 3:
            if (slots[0] != 0xFF) {
                if (x0) {
                    height = 0x12;
                    red = 0x78;
                    green = 0x78;
                    blue = 0xEC;
                    x1off = 0x8E;
                } else {
                    height = 0x12;
                    red = 0x78;
                    green = 0x78;
                    blue = 0xEC;
                    x1off = 0x8E;
                }
                if (slots[0] == 1) {
                    x0 += 0x8E;
                }
            }
            break;
        case 4:
            if (slots[1] != 0xFF) {
                height = 0x12;
                red = 0x78;
                green = 0x78;
                blue = 0xEC;
                x1off = 0x8E;
                if (slots[0] == 0) {
                    x0 = yOffset + 0x12;
                } else {
                    x0 = yOffset + 0xA0;
                }
            }
            break;
        }
        *(s16 *)(prim + 0x12) = yBase + height;
        *(s16 *)(prim + 0x16) = yBase + height;
        prim[4] = red;
        prim[5] = green;
        prim[6] = blue;
        *(s16 *)(prim + 8) = x0;
        *(s16 *)(prim + 0xA) = yBase;
        *(s16 *)(prim + 0xC) = x0 + x1off;
        *(s16 *)(prim + 0xE) = yBase;
        *(s16 *)(prim + 0x10) = x0;
        *(s16 *)(prim + 0x14) = x0 + x1off;
        if (i < 3) {
            AddPrim((u8 *)D_800A38C4 + 0xC, prim);
        } else {
            AddPrim((u8 *)D_800A38C4 + 8, prim);
        }
    }
    leftX = yOffset + 0x17;
    for (i = 0; i < 2; i++) {
        prim = (u8 *)D_800A367C;
        D_800A367C = (s32)prim + 0x28;
        SetPolyFT4((POLY_FT4 *)prim);
        func_80064AB4(prim, D_800BE70C[id * 2 + i]);
        if (i == 0) {
            *(s16 *)(prim + 0xA) = 0x5A;
            *(s16 *)(prim + 0x10) = yOffset + 0x57;
            *(s16 *)(prim + 0x12) = 0x5A;
            *(s16 *)(prim + 8) = leftX;
            *(s16 *)(prim + 0x1A) = 0xA2;
            *(s16 *)(prim + 0x20) = yOffset + 0x57;
            *(s16 *)(prim + 0x22) = 0xA2;
            *(s16 *)(prim + 0x18) = leftX;
        } else {
            *(s16 *)(prim + 8) = yOffset + 0xA5;
            *(s16 *)(prim + 0xA) = 0x5A;
            *(s16 *)(prim + 0x10) = yOffset + 0xE5;
            *(s16 *)(prim + 0x12) = 0x5A;
            *(s16 *)(prim + 0x18) = yOffset + 0xA5;
            *(s16 *)(prim + 0x1A) = 0xA2;
            *(s16 *)(prim + 0x20) = yOffset + 0xE5;
            *(s16 *)(prim + 0x22) = 0xA2;
        }
        AddPrim((u8 *)D_800A38C4 + 8, prim);
    }
    D_800A3568 = (u8 *)D_800A367C;
    func_8005A7B8(2, 4);
    func_8005A818(0x80, 0x80, 0xC0);
    D_800A39C8[0] += 4;
    switch (D_800A3950[0]) {
    case 0xFB:
    case 3:
        func_8005A9F4((s32)D_8009A360[D_800A305B[0]], 0x17, 0x41, 0, 0, 0, 0,
                      0);
        break;
    default:
        func_8005A9F4((s32)D_8009A3A4[D_800A305B[0]], 0x17, 0x41, 0, 0, 0, 0,
                      0);
        break;
    }
    if (D_800A2EB0Absolute[0] == 0) {
        func_8005A9F4((s32)D_8009A3E8[0], 0x17, 0x4D, 0, 0, 1, 0, 0);
    } else {
        func_8005A9F4((s32)D_8009A41C[0], 0x17, 0x4D, 0, 0, 1, 0, 0);
    }
    if (id + 1 >= 0xA) {
        D_8009A3EC[0][4] = 0x31;
        D_8009A3EC[0][5] = id + 0x27;
        D_8009A3EC[0][6] = 0;
    } else {
        D_8009A3EC[0][4] = id + 0x31;
        D_8009A3EC[0][5] = 0;
    }
    leftX = 0x17;
    func_8005A9F4((s32)D_8009A3EC[0], 0xFC, 0x4D, 0, 0, 0, 0, 0);
    for (i = 0; i < 2; i++) {
        x = 0xA5;
        if (i == 0) {
            x = leftX;
        }
        color = D_800BE70C[id * 2 + i];
        if (color == D_800A36E0[0]) {
            r2 = 0xC0;
            g2 = 0x80;
            b2 = 0x40;
        } else if (D_800A3644[0] != 0 && color == D_800A36E1[0]) {
            r2 = 0xC0;
            g2 = 0x80;
            b2 = 0x40;
        } else {
            r2 = 0x80;
            g2 = 0x80;
            b2 = 0xC0;
        }
        func_8005A818(r2, g2, b2);
        func_8005A9F4((s32)D_8009ACE0[color], x, 0xA7, 0, 0, 0, 0, 0);
        func_8005A9F4((s32)D_8009AC1C[color], x + 0x1E, 0xA7, 0, 0, 0, 0, 0);
        if (D_800A2EB0Absolute[0] == 0 && D_800AEB34[color] == 0x7FFFFFFF) {
            func_8005A9F4((s32)D_8009A42C[0], x + 0x45, 0x7E, 0, 0, 0, 0, 0);
        } else {
            func_80018588((void *)D_800AEB34[color], -1, entry);
            b2 = (s32)entry;
            func_8005A9F4(b2, x + 0x45, 0x7E, 0, 0, 0, 0, 7);
        }
        if (D_800A2EB0Absolute[0] == 0 && id == 0 && i == 0) {
            func_8005A9F4((s32)D_8009A3EC[13], x + 0x59, 0x61, 0, 0, 0, 0, 0);
            func_8005A9F4((s32)D_8009A3EC[14], x + 0x4F, 0x6B, 0, 0, 0, 0, 0);
        }
    }
    D_800A39C8[0] -= 4;
    D_800A3970 = (u8 *)D_800A367C;
    if (yOffset != 0) {
        if (D_800A3568 != (u8 *)D_800A367C) {
            prim = (u8 *)D_800A3568 + 0x20;
            do {
                *(u16 *)(prim - 0x18) = *(u16 *)(prim - 0x18) + yOffset;
                *(u16 *)(prim - 0x10) = *(u16 *)(prim - 0x10) + yOffset;
                *(u16 *)(prim - 8) = *(u16 *)(prim - 8) + yOffset;
                *(u16 *)(prim) = *(u16 *)(prim) + yOffset;
                prim += 0x28;
            } while (prim != (u8 *)D_800A367C + 0x20);
        }
    }
    D_800A3940Signed = 2;
    D_800A3A44 = yOffset;
    D_800A3760 = 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/menu", func_80065058);
#endif

extern u8 *D_8009A3F0[];
extern u8 *D_8009A400[];
extern u8 *D_8009A418[];
extern u32 *D_800A38C4;
extern u8 *D_800A369C;
extern u8 D_800A3A4C;
void func_80065838(s32 arg0) {
    extern s32 D_800A2EB0Absolute[];
    u8 *str;
    u8 *ptr;
    s32 count;
    s32 len;
    s32 temp;
    volatile s32 framePad[2];

    ptr = D_800A369C;
    if (arg0 & 0xFF) {
        str = D_8009A400[0];
    } else {
        ptr += D_800A3A4C * 0x28;
        if (D_800A2EB0Absolute[0] == 0) {
            str = D_8009A3F0[0];
        } else {
            str = D_8009A418[0];
        }
    }
    count = 0;
    len = strlen((char *)str);
    if (len > 0) {
        do {
            temp = ptr;
            ptr += 0x28;
            count += 1;
            AddPrim(D_800A38C4, temp);
        } while (count < len);
    }
}

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

INCLUDE_ASM("asm/nonmatchings/menu", func_8006594C);

INCLUDE_ASM("asm/nonmatchings/menu", func_80065C3C);

extern void func_8005A818(u8 arg0, u8 arg1, u8 arg2);
extern s32 func_8005B0E4(s16 arg0, s32 arg1);
extern void func_8005A9F4(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4,
                          s32 arg5, u8 arg6, u8 arg7);
extern u8 *D_8009A3FC[];
extern u8 *D_800A38D8;
extern s32 D_800A3538;
extern u8 D_800A3884;
void func_80065F80(void) {
    u8 **entry;
    u8 *str;
    u8 *ptr;
    s32 count;
    s32 len;
    s32 temp;
    volatile s32 framePad[2];

    func_8005A7B8(2, 4);
    func_8005A818(0x80, 0x80, 0xC0);
    entry = D_8009A3FC;
    D_800A38D8 = (u8 *)D_800A367C;
    *(volatile u8 *)&D_800A35B4 = strlen((char *)entry[0]);
    func_8005A9F4((s32)entry[0], func_8005B0E4(0x140, (s32)entry[0]), 0x7F, 0,
                  0, 0, 0, 0);
    ClearOTagR(D_800A38C4, 4);
    ptr = D_800A369C;
    str = D_8009A400[0];
    D_800A3538 = D_800A367C;
    count = 0;
    len = strlen((char *)str);
    if (len > 0) {
        do {
            temp = ptr;
            ptr += 0x28;
            count += 1;
            AddPrim(D_800A38C4, temp);
        } while (count < len);
    }
    D_800A3884 = 0;
}

INCLUDE_ASM("asm/nonmatchings/menu", func_80066080);

void func_800663B0(void) {
    extern s32 D_8008CA4C[];
    extern s32 D_800A2EB0Absolute[];
    extern u8 D_800A39E4[];
    extern u16 D_800A3940;
    extern u8 D_800A3760;
    extern u8 D_800A3884;
    extern u8 D_800A3A4C;
    extern u8 *D_800A369C;
    extern s32 D_800A3538;
    extern s32 D_800A367C;
    extern volatile u8 D_800A3360;
    extern void func_8006594C(s32, s32);
    extern void func_80066080(s32);
    extern u8 *D_8009A3F0[];
    extern u8 *D_8009A418[];
    extern u32 *D_800A38C4;
    s32 oldGp;
    u8 *walk;
    char *text;
    s32 count;
    s32 len;
    s32 i;

    oldGp = GetGp();
    func_80058D08(D_8008CA4C[0]);
    SetDispMask(1);
    if ((u8)(D_800A39E4[0] + 3) >= 2) {
        if ((D_800A3940 << 16) > 0) {
            PutDrawEnv(D_800BDD4C);
            func_8006594C(D_800A3760, 1);
            DrawOTag(D_800A38C4 + 3);
            DrawSync(0);
        } else {
            if (*(volatile u8 *)&D_800A3884 == 1) {
                PutDrawEnv(D_800BDD4C);
                ClearOTagR(D_800A38C4, 4);
                count = D_800A3A4C;
                walk = (u8 *)D_800A369C;
                walk += count * 0x28;
                if (D_800A2EB0Absolute[0] == 0) {
                    text = (char *)D_8009A3F0[0];
                } else {
                    text = (char *)D_8009A418[0];
                }
                len = strlen(text);
                for (i = 0; i < len; i++) {
                    AddPrim(D_800A38C4, walk);
                    walk += 0x28;
                }
                D_800A367C = D_800A3538;
                func_80066080(0);
                DrawOTag(D_800A38C4 + 3);
                DrawSync(0);
                D_800A3884 = 2;
            }
        }
    }
    D_800A3360 = 1;
    asm("addu $gp, %0, $zero" : : "r"(oldGp));
}

void *func_8006654C(void *queue, s32 arg1) {
    extern s32 D_800A39C8[];
    extern u8 *func_80057D50(s32);
    s32 *templates[2];
    s32 cursor;
    s32 topY;
    s32 sel;
    s32 depth;
    s32 bottomY;
    s32 offset;
    s32 row;
    s32 i;
    s32 x;
    s32 *src;
    s32 *orderTable;
    s32 *dst;
    cursor = (s32)queue;
    depth = arg1;
    for (i = 0; i < 2; i++) {
        if (cursor == 0) {
            templates[i] = (s32 *)func_80057D50(0);
        } else {
            templates[i] = (s32 *)cursor;
            cursor += 0x18;
        }
        SetPolyF4((u_long *)templates[i]);
        SetSemiTrans((u_long *)templates[i], 1);
        if (i != 0) {
            ((u8 *)templates[i])[4] = 0x18;
            ((u8 *)templates[i])[5] = 0x18;
            ((u8 *)templates[i])[6] = 0x18;
        } else {
            ((u8 *)templates[0])[4] = 8;
            ((u8 *)templates[0])[5] = 8;
            ((u8 *)templates[0])[6] = 8;
        }
    }
    row = 0;
    topY = 0;
    offset = depth << 2;
    do {
        if (row & 1) {
            sel = 0;
        } else {
            sel = 1;
        }
        x = 0;
        i = 0;
        bottomY = topY + 0x20;
        do {
            if (cursor == 0) {
                dst = (s32 *)func_80057D50(0);
            } else {
                dst = (s32 *)cursor;
                cursor += 0x18;
            }
            src = templates[sel];
            sel ^= 1;
            *((POLY_F4 *)dst) = *((POLY_F4 *)src);
            ((u16 *)dst)[4] = x;
            ((u16 *)dst)[8] = x;
            ((u16 *)dst)[5] = topY;
            ((u16 *)dst)[6] = x + 0x20;
            ((u16 *)dst)[7] = topY;
            ((u16 *)dst)[9] = bottomY;
            ((u16 *)dst)[10] = x + 0x20;
            ((u16 *)dst)[11] = bottomY;
            x += 0x20;
            AddPrim(((u8 *)(orderTable = D_800A39C8)[0]) + offset, dst);
            i += 1;
        } while (i < 0xA);
        row += 1;
        topY += 0x20;
    } while (row < 7);
    return (void *)cursor;
}

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
asm("func_8005A9F4W = func_8005A9F4");

void func_80066730(void) {
    u8 **table;
    u8 **q;
    s32 page;
    s32 y;
    u8 **p;
    s32 i;
    s16 y16;
    s32 ret;
    s16 x;
    u8 **pp;
    s32 raw;
    s32 a0v;
    s32 a1v;

    GraphicsInitDoubleBuffer(0);
    PutDrawEnv(&D_800BDDA8[0]);
    table = D_8009A404;
    q = table + 2;
    for (page = 0; page < 2; page++) {
        ClearOTagR((u32 *)D_800A39C8Ptr[0], 0x3FF);
        func_80014A40(0);
        func_8006654C((void *)0, 0x3FC);
        func_8005E8EC(0, 0, 1);
        func_8005A7B8S32(2, 4);
        func_8005A818(0x80, 0x80, 0xC0);
        y = 0xA0;
        i = 0;
        p = table;
        func_8005A9F4(D_8009A360[D_800A305B[0]], 0x20, 0x23, 0, 0, 0, 0, 0);
        do {
            y16 = (s16)y;
            func_8005A9F4(p[0], 0x20, y16, 0, 0, 0, 0, 0);
            ret = (s32)(s16)func_8005A8E0(p[0]);
            x = (s16)(ret + 0x20);
            switch (i) {
            case 0:
                func_8005A9F4(q[D_8009B198[D_800A305B[0]]], x, y16, 0, 0, 0, 0,
                              0);
                break;
            case 1:
                func_8005A9F4(D_8009A430[D_800A305B[0]], x, y16, 0, 0, 0, 0, 0);
                break;
            }
            y += 0xF;
            i++;
            p++;
        } while (i < 2);
        pp = D_8009A414;
        if (page == 0) {
            pp = D_8009A400;
        }
        raw = func_8005B0E4(0x140, (s32)pp[0]);
        a0v = (s32)pp[0];
        a1v = (s16)raw;
        func_8005A9F4W(a0v, a1v, 0xC8, 0, 0, 0, 0, 0);
        DrawOTag((u32 *)(D_800A39C8Ptr[0] + 0xFFC));
        DrawSync(0);
        if (page == 0) {
            PutDrawEnv(&D_800BDD4C[0]);
        }
    }
    PutDispEnv(&D_800BDE18[0]);
    D_800A3884 = 0;
}

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
void func_800669B8(void) {
    s32 gp;

    gp = GetGp();
    func_80058D08(D_8008CA4C[0]);
    SetDispMask(1);
    if (*(volatile u8 *)&D_800A3884 == 1) {
        PutDispEnv(D_800BDE04);
    }
    D_800A3360 = 1;
    asm("addu $gp, %0, $zero" : : "r"(gp));
}

extern s32 GetGp(void);
extern s32 D_8008CA4C[];
extern u8 D_800A3073[];
extern s32 D_800A335C;
extern void func_800663B0(void);
extern void func_80065C3C(void);
extern void func_800669B8(void);
void func_80066A24(u8 mode) {
    void (*callback)(void);

    *(s32 *)D_8008CA4C = GetGp();
    if (D_800A3644[0] != 0 && D_800A3073[0] == 0) {
        callback = func_800663B0;
    } else {
        callback = func_80065C3C;
        if (mode == 2) {
            callback = func_800669B8;
        }
    }
    EnterCriticalSection();
    D_800A335C = OpenEvent(0xF2000003, 2, 0x1000, callback);
    EnableEvent(*(volatile s32 *)&D_800A335C);
    SetRCnt(0xF2000003, 1, 0x1000);
    StartRCnt(0xF2000003);
    ExitCriticalSection();
}

extern s32 D_800A335C;
extern volatile u8 D_800A3360;
void func_80066B08(void) {
    if (D_800A335C != 0) {
        D_800A3360 = 0;
        while (D_800A3360 == 0) {
        }
        EnterCriticalSection();
        DisableEvent(D_800A335C);
        CloseEvent(D_800A335C);
        ExitCriticalSection();
        DrawSync(0);
    }
    D_800A335C = 0;
}

/* Matched 2026-10-11: the two D_800A365C/D_800A39F4 setup pairs come before
 * the i/height/flag/off14/off5C init block, and the second read goes through
 * a second unknown-size array alias of gPrimitiveCursor so gcc emits a fresh
 * lui/lw per read instead of caching the address across the setup calls.
 */
void func_80066B70(void) {
    extern s32 D_800A2EB0Absolute[];
    extern s32 D_800A365C;
    extern s32 D_800A39F4;
    extern u32 gPrimitiveCursor2[] asm("gPrimitiveCursor");
    s32 i;
    s32 height;
    s32 flag;
    s32 off14;
    s32 off5C;
    u8 *env;

    D_800A365C = gPrimitiveCursor[0];
    func_80050028(D_8009A400[0], 0x8C, 0xD6, 1);
    D_800A39F4 = gPrimitiveCursor2[0];
    func_80050028(D_8009A400[10], 0x82, 0xF1, 1);
    i = 0;
    height = 0xF0;
    flag = 8;
    off14 = 0;
    off5C = 0;
    for (i = 0; i < 2; i++) {
        env = (u8 *)D_800BDD4C + off5C;
        SetDefDrawEnv((DRAWENV *)env, (0 - (i != 0)) & 0x140, 0, 0x140, height);
        SetDefDispEnv((DISPENV *)((u8 *)D_800BDE04 + off14),
                      (0 - (i == 0)) & 0x140, 0, 0x140, height);
        D_800BDD62[off5C] = 0;
        if (D_800A2EB0Absolute[0] == 2) {
            env[0x1A] = 7;
            env[0x19] = 0;
            env[0x1B] = 0x26;
        } else {
            env[0x19] = flag;
            env[0x1A] = flag;
            env[0x1B] = flag;
        }
        off14 += 0x14;
        off5C += 0x5C;
    }
    if (D_800A2EB0Absolute[0] == 2) {
        D_800BDD64[0] = 1;
    }
    PutDrawEnv(D_800BDD4C);
    D_800BDDC0[0] = 1;
    D_800BDD64[0] = 1;
}

INCLUDE_ASM("asm/nonmatchings/menu", func_80066CFC);

void func_80067020(u8 *start, u8 *end, u8 delta) {
    POLY_FT4 *quad;
    if (start < end) {
        quad = (POLY_FT4 *)start;
        do {
            if (quad->b0 != 0) {
                quad->y0 += (s8)delta;
                quad->y1 += (s8)delta;
                quad->y2 += (s8)delta;
                quad->y3 += (s8)delta;
            }
            quad++;
        } while ((u8 *)quad < end);
    }
}

void func_8006709C(u8 arg0) {
    /* Retail reaches every D_800A3848 access with its own lui, so each
     * store goes through a neighbour symbol: a shared la base would put
     * the stores in jump delay slots. */
    extern s32 D_800A3848[];
    extern s32 D_800A3844[];
    extern s32 D_800A3840[];
    extern s32 D_800A383C[];
    extern u8 D_800A3644[];
    extern u16 *D_800A3898;
    extern u16 *D_800A389C[];
    s32 cur;
    u8 arg;
    u16 *base;
    u16 *limit;

    arg = arg0;
    cur = D_800A3848[0] - ((s8)arg0 << 1);
    D_800A3844[1] = cur;
    if (cur < 0xA0) {
        D_800A3840[2] = 0xA0;
        return;
    }
    if (cur >= 0x1EB) {
        D_800A383C[3] = 0x1EA;
        return;
    }
    if (D_800A3644[0] != 0) {
        return;
    }
    base = (u16 *)D_800A39C8Ptr[0];
    limit = D_800A3898;
    if (base + 8 < limit) {
        POLY_FT4 *quad;
        quad = (POLY_FT4 *)(base + 8);
        do {
            if (quad->b0 != 0) {
                quad->y0 += (s8)arg0;
                quad->y1 += (s8)arg0;
                quad->y2 += (s8)arg0;
                quad->y3 += (s8)arg0;
            }
            quad++;
        } while ((u16 *)quad < limit);
    }
    if (D_800A389C[0] == 0) {
        return;
    }
    {
        POLY_FT4 *quad;
        u16 *end;
        end = (u16 *)SCRATCH_TOP;
        for (quad = (POLY_FT4 *)D_800A389C[0]; (u16 *)quad < end; quad++) {
            if (quad->b0 != 0) {
                quad->y0 += (s8)arg;
                quad->y1 += (s8)arg;
                quad->y2 += (s8)arg;
                quad->y3 += (s8)arg;
            }
        }
    }
}

void func_80067228(void) {
    extern u16 *D_800A387C;
    extern u16 *D_800A36BC;
    extern u8 *D_8009A400[];
    u16 *baseA;
    u16 *baseB;
    u16 *baseB2;
    POLY_FT4 *quad;
    POLY_FT4 *quad2;
    s32 i;
    s32 len;
    u32 unused[4]; /* retail reserves 16 bytes of locals nothing touches */

    baseA = D_800A387C;
    baseB = (u16 *)D_800A39C8Ptr[0];
    len = strlen(D_8009A400[0]);
    baseB2 = baseB + 0x2000;
    i = 0;
    if (len > 0) {
        quad = (POLY_FT4 *)baseA;
        i = 0;
        do {
            quad->y0 = 0xF1;
            quad->y1 = 0xF1;
            quad->y2 = 0xF1;
            quad->y3 = 0xF1;
            if (quad < (POLY_FT4 *)baseB2) {
                quad++;
            } else {
                quad--;
            }
            i++;
        } while (i < len);
    }
    baseA = D_800A36BC;
    len = strlen(D_8009A400[10]);
    if (len > 0) {
        quad2 = (POLY_FT4 *)baseA;
        i = 0;
        do {
            quad2->y0 -= 0x1B;
            quad2->y1 -= 0x1B;
            quad2->y2 -= 0x1B;
            quad2->y3 -= 0x1B;
            if (quad2 < (POLY_FT4 *)baseB2) {
                quad2++;
            } else {
                quad2--;
            }
            i++;
        } while (i < len);
    }
}

INCLUDE_ASM("asm/nonmatchings/menu", func_8006733C);

INCLUDE_ASM("asm/nonmatchings/menu", func_80067598);

void func_800679C4(u8 arg0) {
    extern u8 *D_800A3568;
    extern u8 *D_800A3970;
    s32 shift;
    u8 arg;
    u16 *base;
    u16 *limit;
    u8 *walk;

    arg = arg0;
    base = (u16 *)D_800A3568;
    limit = (u16 *)D_800A367C;
    if (base < limit) {
        POLY_FT4 *quad;
        quad = (POLY_FT4 *)base;
        do {
            quad->x0 += (s8)arg0;
            quad->x1 += (s8)arg0;
            quad->x2 += (s8)arg0;
            quad->x3 += (s8)arg0;
            quad++;
        } while ((u16 *)quad < limit);
    }
    base = (u16 *)D_800A367C;
    limit = (u16 *)D_800A3970;
    if (base < limit) {
        POLY_GT4 *quad;
        quad = (POLY_GT4 *)base;
        do {
            quad->x0 -= (s8)arg;
            quad->x1 -= (s8)arg;
            quad->x2 -= (s8)arg;
            quad->x3 -= (s8)arg;
            quad++;
        } while ((u16 *)quad < limit);
    }
}

INCLUDE_ASM("asm/nonmatchings/menu", func_80067AB4);

/*
 * w4d: this TU position (after the func_80067AB4 slot) matches retail
 * address order; the C body landed on 0x80067AB4 when placed before it.
 */
extern void func_8006733C(void);
extern void func_80067AB4(void);
void func_80067DFC(void) {
    void (*callback)(void);

    *(s32 *)D_8008CA4C = GetGp();
    callback = func_8006733C;
    if (D_800A2EB0Absolute[0] == 2) {
        callback = func_80067AB4;
    }
    EnterCriticalSection();
    D_800A335C = OpenEvent(0xF2000003, 2, 0x1000, callback);
    EnableEvent(*(volatile s32 *)&D_800A335C);
    SetRCnt(0xF2000003, 1, 0x1000);
    StartRCnt(0xF2000003);
    ExitCriticalSection();
}

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

extern char *D_8009AC1C[];
u8 func_80067ECC(char *name) {
    s32 i;

    for (i = 0; i < 0x18; i++) {
        if (strcmp(name, D_8009AC1C[i]) == 0) {
            break;
        }
    }
    return i;
}
