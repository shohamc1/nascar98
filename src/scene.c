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

INCLUDE_ASM("asm/nonmatchings/scene", func_80044BCC);

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
    void func_8004BDD0(void);
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
    func_8004BDD0();
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

#ifdef NON_MATCHING
/* Retry 2026-10-05: 208 bytes versus retail 212; 16 differing instruction words
 * by edit distance. Retained as NON_MATCHING; the integrated ASM fallback matches.
 * The existing object/count API clears the conflicting local prototype.
 */
extern s8 D_800A343C;
extern s8 *D_800A3444[];
extern s32 D_800BE980[];

void func_80046184(s8 *arg0) {
    extern void func_80032DEC(u8 *, s32);
    s8 *base;
    s8 *entry;
    s8 *tail;
    s32 count;
    s32 *descriptorBase;
    s32 n;
    s8 i;
    s32 id;
    u16 flag;
    u8 *p;

    descriptorBase = &D_800BE980[0];
    count = D_800A343C;
    base = D_800A3444[arg0[0x20B]];
    for (n = 1, i = 1, tail = base + 4; i < count; i++) {
        entry = base + i * 0x58;
        id = *(s16 *)entry;
        p = (u8 *)*descriptorBase + id * 0x90;
        flag = *(u16 *)(p + 0xE);
        if (flag != 0) {
            *(s32 *)(tail + 0x28) = (s32)(entry + 4);
            tail = entry + 4;
            n++;
        }
    }
    func_80032DEC((s32)(base + 4), (s8)n);
}
#else
INCLUDE_ASM("asm/nonmatchings/scene", func_80046184);
#endif

INCLUDE_ASM("asm/nonmatchings/scene", func_80046258);

INCLUDE_ASM("asm/nonmatchings/scene", func_8004658C);

INCLUDE_ASM("asm/nonmatchings/scene", func_80046BD4);

INCLUDE_ASM("asm/nonmatchings/scene", func_800474A0);

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

INCLUDE_ASM("asm/nonmatchings/scene", func_8004875C);

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

INCLUDE_ASM("asm/nonmatchings/scene", func_80048EFC);

INCLUDE_ASM("asm/nonmatchings/scene", func_8004A0C4);

INCLUDE_ASM("asm/nonmatchings/scene", func_8004A510);

extern u8 D_8009AE14[];
extern u8 D_800A2FD0[];
extern u8 D_80098BD0[];

#ifdef NON_MATCHING
/* Retry 2026-10-05: 324 bytes versus retail 328; 68 differing instruction words
 * by edit distance. Retained as NON_MATCHING; the integrated ASM fallback matches.
 * The draft used an undefined temporary table alias.
 */

void func_8004AFE0(s8 arg0, u16 *arg1, u16 *arg2) {
    s16 *out;
    s8 i;
    s8 j;
    s32 x;
    s32 w;
    s32 t;
    s32 v0;
    s32 v1;
    s32 sum;

    i = 0;
    do {
        j = 0;
        x = arg1[i * 2];
        w = arg1[i * 2 + 1] + (s8)D_800A2FD0[arg0];
        if (((s8 **)D_8009AE14)[i][0] != 0) {
            out = (s16 *)((u8 *)arg2 + 0x22);
            do {
                t = ((s8 **)D_8009AE14)[i][j];
                v0 = *(s16 *)&D_80098BD0[t * 10 + 6];
                out[-13] = x;
                out[-12] = w;
                out[-8] = w;
                out[-5] = x;
                sum = x + ((v0 * 3) >> 2);
                out[-9] = sum;
                v1 = *(s16 *)&D_80098BD0[t * 10 + 8];
                out[-1] = sum;
                out[-4] = w + ((v1 * 3) >> 2);
                v1 = *(s16 *)&D_80098BD0[t * 10 + 8];
                out[0] = w + ((v1 * 3) >> 2);
                x = sum;
                j++;
                arg2 += 0x14;
                out += 0x14;
            } while (((s8 **)D_8009AE14)[i][j] != 0);
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

INCLUDE_ASM("asm/nonmatchings/scene", func_8004B1C0);

INCLUDE_ASM("asm/nonmatchings/scene", func_8004BDD0);
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
extern void func_80050028Row(char *, s32, s32, s32) asm("func_80050028");
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

#ifdef NON_MATCHING
/* Retry 2026-10-05: 260 bytes versus retail 264; 42 differing instruction words
 * by edit distance. Retained as NON_MATCHING; the integrated ASM fallback matches.
 * Rebased indexing and local lifetime probes do not resolve the compiler's loop-invariant pointer hoist, missing empty frame and loop access ordering.
 */
extern s32 D_800A2CE0;
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
    s8 i;
    s32 a1;

    idx = D_800A2CE0;
    D_800A34A8 = 0;
    D_800A3498 = 0;
    D_800A34A4 = 0;
    D_800A349C = 0x3C;
    if (D_800992D0[idx] > 0) {
        q = &D_800BE974[0];
        p = &D_800992D0[idx];
        i = 0;
        do {
            a1 = *q;
            D_800A8A30[i * 2] = 0x7FFFFFFF;
            D_800A8A2C[i * 2] = a1 + a1 * (i + 1) / p[0];
            i++;
        } while (i < p[0]);
    }
    D_800A34A0 = D_800BE974[0] * 2 + 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/scene", func_8004E700);
#endif

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

INCLUDE_ASM("asm/nonmatchings/scene", func_8004F880);

INCLUDE_ASM("asm/nonmatchings/scene", func_8004FCF4);

extern u8 *D_800A3554[];
extern u8 *D_800A8A80[];
void func_8004FF3C(void) {
    D_800A8A80[0][0] = *(u16 *)(D_800A3554[0] + 0x2AA);
    D_800A8A80[0][1] = *(u16 *)(D_800A3554[0] + 0x2A4);
    *(u16 *)(D_800A8A80[0] + 4) = *(u16 *)(D_800A3554[0] + 0x1D6);
}

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

INCLUDE_ASM("asm/nonmatchings/scene", func_80050028);

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

INCLUDE_ASM("asm/nonmatchings/scene", func_800511E4);

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

INCLUDE_ASM("asm/nonmatchings/scene", func_80051874);

extern u8 D_800A34E4;
extern s32 D_800A34F4;
extern u8 D_80090F7A[];

void func_800524A0(u8 *arg0, s8 arg1) {
    u8 *table;
    u8 *entry;
    s32 mode;
    u16 w;
    u32 v;

    arg0 += arg1 * 0x28 + 0x2AC;
    mode = *(s16 *)(arg0 + 0x26);
    arg0[0x24] = 0;
    arg0[0x20] = 0;
    D_800A34E4 = 0;
    if (mode != -1) {
        table = D_80090F7A;
        w = *(u16 *)(arg0 + 0x22);
        entry = (u8 *)D_800A34F4 + (mode * 12 - mode) * 8;
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

INCLUDE_ASM("asm/nonmatchings/scene", func_800525A8);

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

#ifdef NON_MATCHING
/* Retry 2026-10-05: 316 bytes versus retail 320; 36 differing instruction words
 * by edit distance. Retained as NON_MATCHING; the integrated ASM fallback matches.
 * The historical positional cc1 crash did not reproduce.
 */
extern u8 D_800A3608;

extern u8 D_800A39E4Small;
extern u8 D_800A3059;
void func_80053C00(s32 arg0, s32 arg1) {
    extern s32 D_800A3914[];
    extern void func_8006DCF0(void);
    extern void func_8005B688(u8 *, u8);
    extern void func_8005B8B8(u8 *, u8);
    extern void func_80064898(void);
    extern void func_800686FC(u8, u8);
    extern void func_8005D094(s32, s32, s32);
    extern s32 func_8005DCF0(void);
    s32 modeB;
    s32 flagB;

    if (D_800A39E4Small == 0xFC) {
        func_8006DCF0();
    } else {
        if (D_800A3914[0] != 0) {
            func_8005B688((u8 *)D_800A3914[0], 1);
        }
        if ((u32)(D_800A39E4Small - 9) < 2 || D_800A39E4Small == 0xC ||
            (u32)(D_800A39E4Small - 0x10) < 2) {
            func_800686FC((u8)D_800A39E4Small, (u8)arg0);
        } else if (D_800A39E4Small == 0xE) {
            func_8005B8B8((u8 *)D_800A3914[0], 0xFF);
            func_80064898();
        } else {
            func_8005B8B8((u8 *)D_800A3914[0], 0xFF);
            modeB = D_800A39E4Small;
            flagB = D_800A3059;
            func_8005D094(modeB, flagB, (u8)arg1);
        }
    }
    if (D_800A3608 != 0) {
        D_800A3608 = D_800A3608 - 1;
    } else {
        if ((u32)(D_800A39E4Small - 0x10) < 2 || D_800A39E4Small == 0xE) {
        } else if (func_8005DCF0() == 1) {
            D_800A3608 = 0x78;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/scene", func_80053C00);
#endif

INCLUDE_ASM("asm/nonmatchings/scene", func_80053D40);

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
    s32 clearCount;
    u8 *clearPtr;
    s32 mode;
    s32 tmp;
    s32 idx;

    clearCount = 7;
    clearPtr = D_800A398F;
    do {
        *clearPtr = 0;
        clearCount--;
        clearPtr--;
    } while (clearCount >= 0);

    mode = 8;
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
            mode = 1;
            break;
        case 1:
            mode = 0;
            break;
        case 2:
            mode = 2;
            break;
        }
        D_800A3988[1] = mode;
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
    extern void func_8006BD68(void);
    extern u8 D_800A3928;
    s32 mode;

    if (D_800A3808a[0] == 2 || !(arg0 & 0xFF)) {
        func_8006D8E8(0);
        mode = D_800A3059;
        D_800A3928 = 1;
        if (mode == 1) {
            func_8006C5E4(1);
            if (D_800A3059 == mode) {
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
void func_80057A9C(void) {
    ((s32 *)D_800A3668Absolute)[4] = (s32)HeapAlloc(0x1AB8);
    ((u8 *)D_800A3668Absolute)[-0x7C] = 0;
    ((s32 *)D_800A3668Absolute)[-5] = (s32)HeapAlloc(0x834);
    ((u8 *)D_800A37B4Absolute)[8] = 0;
}

/* Wall: needs a gp store to D_800A3548 (untracked sdata label, no
 * linker alias). Declaring it shifts every sdata label +0x10 and the
 * full build MISMATCHes. Also needs lui for D_800A39E8, which is
 * scalar-declared (gp) for the TU. */
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
/* w9f unguard retry: D_800A3548 tracked extern works now (gp sw/lw match,
 * size 0x118 exact) but the s-reg map is rotated: ours saves an extra s4
 * and runs poly->s0/cursor->s2 vs retail s1/s0; retail pins the 0x80
 * shade byte in s3 across both loops, ours rematerializes the literal.
 * Candidate fix: a local holding 0x80 stored through both loops. Re-guarded. */
#ifdef NON_MATCHING
void func_80057AE4(void) {
    POLY_FT4 *poly;
    POLY_F4 *shade;
    u8 *color;
    u32 count;
    s32 base;

    func_80012E28();
    poly = HeapAlloc(0x4290);
    D_800A3548 = (s32)poly;
    color = (u8 *)poly + 6;
    for (count = 0; count < 0x1AA; count++) {
        SetPolyFT4(poly);
        SetShadeTex(poly, 0);
        color[-2] = 0x80;
        color[-1] = 0x80;
        color[0] = 0x80;
        color += 0x28;
        poly++;
    }
    base = D_800A3548;
    D_800A397CAbsolute[27] = base;
    D_800A3998 = base + 0x3E80;
    D_800A3A18 = base + 0x3E80;
    D_800A39A8 = base + 0x4268;
    D_800A39CC = base + 0x4268;
    shade = HeapAlloc(0x4B0);
    color = (u8 *)shade + 6;
    D_800A3780 = (s32)shade;
    D_800A35B8 = (s32)shade;
    D_800A3544 = (s32)shade + 0x3C0;
    D_800A38EC = (s32)shade + 0x3C0;
    for (count = 0; count < 0x32; count++) {
        SetPolyF4(shade);
        SetSemiTrans(shade, 0);
        color[-2] = 0x80;
        color[-1] = 0x80;
        color[0] = 0x80;
        color += 0x18;
        shade++;
    }
    func_8005E47C();
}
#else
INCLUDE_ASM("asm/nonmatchings/scene", func_80057AE4);
#endif

extern s32 D_800A3548;
extern s32 D_800A3780;
extern s32 D_800A37EC;

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
    if (D_800A36D0Absolute[-22] != 0) {
        HeapFree((void *)D_800A36D0Absolute[-22]);
    }
    D_800A36C0Absolute[-18] = 0;
    if (D_800A36D4Absolute[-32] != 0) {
        HeapFree((void *)D_800A36D4Absolute[-32]);
    }
    D_800A36E8Absolute[-37] = 0;
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
        D_800A36D0Absolute[-21] = (s32)prim + 0x28;
        return prim;
    }
    prim = (u8 *)gPrimitiveCursor[0];
    D_800A3964 += 1;
    D_800A36D0Absolute[-67] = (s32)prim + 0x28;
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
        D_800A36D0Absolute[-21] = (s32)prim + 0x28;
        return prim;
    }
    prim = (u8 *)gPrimitiveCursor[0];
    D_800A3650 += 1;
    D_800A36D0Absolute[-67] = (s32)prim + 0x28;
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

#if 0
/* Wall: sector/size land in s0/s2, retail has s2/s0. Decl order
 * (sector,size) and (size,sector) both swap; blocks-as-local also swaps.
 * D_800A3090 must be reached as D_800A2EB0Absolute + 120 (declaring the
 * untracked sdata label drifts data labels). asm-differ -m compares the
 * LINKED exe, so run a relink before trusting a unit diff here. */
extern s32 FileOpen(s32, s32);
extern s32 FileSeek(s32, s32, s32);
extern s32 FileRead(s32, s32, s32, s32);
extern s32 FileClose(s32);
extern s32 D_800A2EB0Absolute[];
s32 func_80058094Old(s32 arg0, s32 *arg1, s32 data) {
    s32 size;
    s32 sector;

    sector = FileOpen(arg0, D_800A2EB0Absolute + 120);
    size = (FileSeek(sector, 0, 2) + 0x7FF) >> 11 << 11;
    if (data == 0) {
        data = (s32)HeapAlloc(size);
    }
    FileSeek(sector, 0, 0);
    FileRead(data, 1, size, sector);
    FileClose(sector);
    *arg1 = data + 4;
    return data;
}
#endif
extern s32 FileSeekArgs(void *, s32, s32);
extern void FileCloseArgs(s32);
asm(".globl FileSeekArgs\nFileSeekArgs = FileSeek");
asm(".globl FileCloseArgs\nFileCloseArgs = FileClose");
void *func_80058094(s32 arg0, void **arg1, s32 arg2) {
    extern void *FileOpen(s32, void *);
    extern void FileRead(s32, s32, s32, s32);
    extern s32 D_800A3090[];
    s32 size;
    s32 sector;

    sector = (s32)FileOpen(arg0, D_800A3090);
    size = (FileSeekArgs((void *)sector, 0, 2) + 0x7FF) >> 11 << 11;
    if (arg2 == 0) {
        arg2 = (s32)HeapAlloc(size);
    }
    asm("" : : "r"(size), "r"(arg2));
    FileSeekArgs((void *)sector, 0, 0);
    FileRead(arg2, 1, size, sector);
    FileCloseArgs(sector);
    *arg1 = (void *)(arg2 + 4);
    return (void *)arg2;
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

INCLUDE_ASM("asm/nonmatchings/scene", func_80058D94);

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
