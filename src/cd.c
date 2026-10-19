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

extern s32 D_800A2EC8[];
extern s32 strlen(char *);
extern void func_8001E7EC(void *, s32, s32);
extern void func_8003CAE8(s32);
extern void *HeapAlloc(u32);
extern void SystemShowFatalError(char *);
extern void *D_800BE97C[];
extern void ListPushFront(u8 *, u8 **, u8 **);
extern void func_8001C668(void *, void *);
extern void func_80033788();
extern void func_8003379C();
extern s32 MathMultiplyFixed16(s32, s32);

extern void func_80018588(void *, s32, s32);
typedef struct ListNode28 ListNode28;
typedef struct DoublyLinkedNode {
    struct DoublyLinkedNode *next;
    struct DoublyLinkedNode *previous;
} DoublyLinkedNode;
extern void func_8001F2C4(s32 arg0, s32 arg1, s32 arg2);
extern void func_8001ED84(s32 *vec);
extern void (*D_80091080[])(void *);
extern void func_8003382C();
typedef struct {
    u8 pad[16];
} Unk16;
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A3784, D_800A3790, D_800A3794, D_800A3798, D_800A379C,
    D_800A37A4, D_800A37AC, D_800A37B4, D_800A37C4;
extern s32 D_800A3784, D_800A3790, D_800A3794, D_800A3798, D_800A379C,
    D_800A37A4, D_800A37AC, D_800A37B4, D_800A37C4;
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A3784, D_800A3790, D_800A3794, D_800A3798, D_800A379C,
    D_800A37A4, D_800A37AC, D_800A37B4, D_800A37C4;
extern void func_80025730(u8 *);
s32 func_80024E90(s32, s32, s32 *, s32 *, s32 *);
extern u8 *D_800A3554[];
void func_800229B8(void);
extern void func_80022CA4(void);
s32 func_800246C0(s32, s32, u8 *);
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
s32 func_8003702C(u8 *, u8 *);
void func_800406D0(u8 *, u8 *, s32, s32);
void func_80041848(u8 *, s32);
extern void func_8003644C(s32, s32, s32, s32);
typedef struct {
    u8 unk0[0x90];
    s32 unk90;
} UnkObject90;
void func_80028D80(u8 *);
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
extern void func_8001FAC0(u8 *, s32);
extern s32 D_800A3A04nm[] asm("D_800A3A04.NON_MATCHING");
extern void func_80029CB4(s32 *arg0);
extern void func_80039B74(s32 *arg0, s32 arg1);
s32 func_8003702C(u8 *, u8 *);
s32 func_8002CF24(u8 *, u8 *);
extern void func_8003CDBC();
extern void func_800323F0(s32, s32);
extern void func_80032494(u8 *);
void *HeapAlloc(u32);
extern void func_80028754(u8 *, s32);
extern void func_8002D3EC(u8 *);
void CarPlaceOnStartingGrid(void);
void func_8003B6DC(s32);
void func_80041A28(void);
void exit();
void func_8003B6DC(s32 arg0);
void func_8003B464(void);
void func_8003C1CC(void);
void func_8003C3FC(void);
s32 func_800309DC(s32, s32 *, s32 *);
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vector3;
void OuterProduct0(s32 *, s32 *, s32 *);
void VectorNormal(s32 *, s32 *, s32);
extern void func_80025454(s32);
extern s32 D_800B9F44[];
void func_80025454(s32);
extern s32 func_800337EC(void);
typedef struct {
    s32 words[10];
} Primitive40;
typedef struct {
    s32 words[4];
} Primitive10;
extern s32 D_800A3784Absolute[], D_800A3790Absolute[], D_800A3794Absolute[],
    D_800A3798Absolute[], D_800A379CAbsolute[], D_800A37A4Absolute[],
    D_800A37ACAbsolute[], D_800A37B4Absolute[], D_800A37C4Absolute[];
extern s32 D_800A3790Absolute[], D_800A3798Absolute[], D_800A379CAbsolute[],
    D_800A37A4Absolute[], D_800A37B4Absolute[], D_800A3794Absolute[],
    D_800A3784Absolute[], D_800A37ACAbsolute[], D_800A37C4Absolute[];
void func_80035274(void);
typedef struct {
    u8 pad[0x3E0];
    void *unk3E0;
} Data3554;
void func_80034D64(void);
void func_80035274(void);
void func_8002F0A8(u8 *);
void func_80034D64(void);
void func_80035720(u_long *);
extern s32 D_800BE974[];
void func_8001FAC0(u8 *, s32);
void func_8001FB28(u8 *, s32);
extern s32 D_800A39E0;
extern void func_8003ABC0();
extern void func_80025594(u8 *);
extern void func_8003AA20();
extern void func_8003A880();
extern void func_8003A950();
extern void func_8003AAEC();
void func_800390A0(s32, s32, s32, s32);
void FontDrawPaddedNumber(s32, s32, s32, s32);
void func_8003644C(s32, s32, s32, s32);
extern s32 D_800A2EA8[];
extern s32 D_800AE1EC[];
extern u8 D_800BE70C[];
extern u8 D_800BE70C[], D_800B9DA4[];
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

/* CD control and streaming. */

void func_8003C528(void) {
    u8 index;
    s32 value;
    index = D_800A3554[0][0x376];
    value = *(s32 *)(D_800A3554[0] + 0x25C);
    D_800BE70C[0] = index;
    D_800AE1EC[0] = value;
    D_800B9DA4[index & 0xFF] = 0;
}

extern s32 CdSetDebug(s32 level);
void CdDisableDebug(void) {
    CdSetDebug(0);
}

extern s32 D_800A2F74;
extern s32 D_800A37CC;
extern CdlLOC D_800BDEBC[];
extern s32 D_80098340[];
extern s32 D_800A45A8[];
extern s32 D_800A45AC[];

void *FileOpen(s32 fileId, void *mode) {
    u8 pad[0x40];
    u8 result[8];
    void *pos;
    s32 value;

    if (D_800A2F74 == 0) {
        CdGetToc(D_800BDEBC);
        D_800A2F74 = 1;
    }
    CdIntToPos(D_80098340[fileId * 3] + 0x13C, D_800A45A8);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = D_80098340[fileId * 3 + 1];
    D_800A45AC[0] = value;
    D_800A37CC = fileId;
    pos = &D_800A45AC[-1];
    return pos;
}

void FileClose(void) {
}

/* MATCHED 2026-10-11 (w2i). Two keys beyond the 2026-10-07 draft:
 * 1. The file-table accesses must each use a pairwise-distinct symbol
 *    name for the same address (seek D_80098340, checksum compare
 *    D_80098348.NON_MATCHING, first FntPrint D_80098348, size print
 *    D_80098344.NON_MATCHING, sector print D_80098340.NON_MATCHING):
 *    a shared name let gcc CSE a sym base pointer into a sixth
 *    call-saved reg (s5), squeezing buf out of s2.
 * 2. result[] is 0x10 bytes here (8 elsewhere in cd.c): the extra 8
 *    bytes are the gap before the register homes, frame 0x38.
 * buf is pinned `register s32 buf asm("s2");` with the birth moved
 * after DrawSync(0) (permuter find): that orders the s2 save/move pair
 * before s4's in the mult->mflo window. */
extern char D_8008D110[];
extern char D_8008D144[];
extern char D_8008D16C[];
extern char D_8008D178[];
extern s32 D_80098348nm[] asm("D_80098348.NON_MATCHING");
extern s32 D_80098344nm[] asm("D_80098344.NON_MATCHING");
extern s32 D_80098340w4[] asm("D_80098340.NON_MATCHING");
extern s32 D_80098348fp[] asm("D_80098348");

s32 FileRead(s32 buffer, s32 size, s32 count, s32 handle) {
    s32 total;
    s32 sectors;
    s32 hnd = handle;
    register s32 buf asm("s2");
    register s32 retries asm("s4");
    u8 result[0x10];
    register s32 status asm("a1");
    s32 *ptr;
    s32 i;
    s32 words;

    asm("" : "=r"(total) : "0"(count));
    retries = 0;
    total = total * size;
    DrawSync(0);
    buf = buffer;
    VSync(0);
    VSync(0);
    total += 0x7FF;
    sectors = total >> 11;
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    total = -1;
retry:
    while (CdControl(2, (u_char *)hnd, 0) == 0) {
    }
    CdSeekToSector(D_80098340[D_800A37CC * 3] + 0x13C);
    CdRead(sectors, buf, 0x80);
    do {
        status = CdReadSync(1, 0);
    } while (status > 0);
    if (status == total) {
        goto retry;
    }
    ptr = (s32 *)buf;
    i = 0;
    words = sectors << 9;
    total = 0;
    if (words > 0) {
        do {
            total += *ptr;
            ptr += 1;
            i += 1;
        } while (i < words);
    }
    retries += 1;
    if (D_80098348nm[D_800A37CC * 3] != total) {
        if (retries < 0x32) {
            CdControl(9, 0, 0);
            CdSync(0, result);
            CdReady(0, result);
            CdInit();
            total = -1;
            goto retry;
        }
        GraphicsInit();
        FntPrint(D_8008D110, D_80098348fp[D_800A37CC * 3], total);
        FntPrint(D_8008D144, buf & 0x7FFFFFFF, D_800A37CC);
        FntPrint(D_8008D16C, D_80098344nm[D_800A37CC * 3]);
        FntPrint(D_8008D178, D_80098340w4[D_800A37CC * 3] + 0x13C);
        FntFlush(-1);
        while (1) {
        }
    }
    return status;
}

INCLUDE_RODATA("asm/nonmatchings/cd", D_8008D110);
INCLUDE_RODATA("asm/nonmatchings/cd", D_8008D144);
INCLUDE_RODATA("asm/nonmatchings/cd", D_8008D16C);
INCLUDE_RODATA("asm/nonmatchings/cd", D_8008D178);

s32 func_8003C8B4(void) {
    return 0;
}

s32 FileSeek(s32 *handle) {
    return handle[1];
}

void func_8003C8C8(u8 *string) {
    s32 length;
    s32 current;
    s32 end;
    u8 value;
    length = strlen((char *)string);
    if (length > 0) {
        current = (s32)string;
        end = length + current;
        do {
            value = *(u8 *)current;
            if ((u32)(value - 'a') < 26) {
                value -= 0x20;
                *(u8 *)current = value;
            }
            current++;
        } while (current < end);
    }
}


void *FileLoadToHeap(s32 arg0) {
    u8 pad[0x40];
    u8 result[8];
    s32 value;
    s32 size;
    void *buffer;

    if (D_800A2F74 == 0) {
        CdGetToc(D_800BDEBC);
        D_800A2F74 = 1;
    }
    CdIntToPos(D_80098340[arg0 * 3] + 0x13C, D_800A45A8);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = D_80098340[arg0 * 3 + 1];
    D_800A37CC = arg0;
    D_800A45AC[0] = value;
    size = (value + 0x7FF) >> 11 << 11;
    buffer = HeapAlloc(size);
    if (buffer != 0) {
        FileRead(buffer, 1, size, D_800A45A8);
    }
    return buffer;
}

void func_8003CA18(s32 arg0, s32 arg1) {
    u8 pad[0x40];
    u8 result[8];
    s32 value;

    if (D_800A2F74 == 0) {
        CdGetToc(D_800BDEBC);
        D_800A2F74 = 1;
    }
    CdIntToPos(D_80098340[arg1 * 3] + 0x13C, D_800A45A8);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = D_80098340[arg1 * 3 + 1];
    D_800A37CC = arg1;
    D_800A45AC[0] = value;
    FileRead(arg0, 1, value, D_800A45A8);
}

/* The retail layout needs four shapes that look odd in C:
 * - filter is a 4-byte array and result a dead 0x30-byte array, so locals land
 *   at 0x10 (vol), 0x18 (filter) and 0x20 (result) in a 0x58 frame.
 * - The remainder is spelled out, so only the final subtract targets remainder.
 * - arg0 = remainder is a real copy: arg0 stays live in s0 into the negate.
 * - remainder = 0 then -= arg0 makes cse forget remainder == arg0, so the
 *   negate reads s0. The store sits in both arms; cross-jumping merges them.
 */
extern s32 CdGetToc(void *);
extern CdlLOC D_800BDEC4[];
extern s32 D_800A2F70;
extern u8 D_800A2F9CAbsolute[];

void func_8003CAE8(s32 arg0) {
    CdlATV vol;
    u8 filter[4];
    volatile u_char result[0x30];
    CdlLOC *lastPos;
    s32 remainder;
    CdlLOC *pos;

    if (CdGetToc(D_800BDEBC) < 2) {
        return;
    }
    filter[0] = 5;
    if (CdControl(0xE, filter, 0) == 0) {
        return;
    }
    CdSetDebug(0);
    remainder = arg0 - arg0 / 6 * 6;
    arg0 = remainder;
    if (arg0 < 0) {
        remainder = 0;
        remainder -= arg0;
        D_800A2F70 = remainder + 2;
    } else {
        D_800A2F70 = remainder + 2;
    }
    pos = &D_800BDEC4[0];
    CdIntToPos(0x19649, pos);
    lastPos = pos + 5;
    CdIntToPos(0x1C4B8, D_800BDEC4 + 1);
    CdIntToPos(0x1F278, D_800BDEC4 + 2);
    CdIntToPos(0x2219A, D_800BDEC4 + 3);
    CdIntToPos(0x250DB, D_800BDEC4 + 4);
    CdIntToPos(0x25EFF, lastPos);
    CdControl(2, (u_char *)(D_800BDEC4 + D_800A2F70 - 2), 0);
    if (D_800A2F9CAbsolute[0] != 0) {
        CdControlB(3, 0, 0);
    }
    vol.val3 = 0x7F;
    vol.val2 = 0x7F;
    vol.val1 = 0x7F;
    vol.val0 = 0x7F;
    CdMix(&vol);
}

extern u8 D_800AE24C[];

void func_8003CC48(void) {
    u_char param[8];
    u_char result[8];

    if (D_800A2F9CAbsolute[0] == 0) {
        return;
    }
    if (D_800A2EC8[0] != 0) {
        return;
    }
    CdControl(1, 0, D_800AE24C);
    param[0] = 0;
    CdControl(0x11, param, result);
    if (result[0] == D_800A2F70) {
        return;
    }
    CdControl(2, (u_char *)&D_800BDEBC[D_800A2F70], 0);
    CdControl(3, 0, 0);
}

void func_8003CCE0(s32 arg0) {
    u_char pad[0x10];
    u_char *status;
    s32 target;

    pad[0] = 0;
    if (arg0 != 0) {
        CdControl(3, 0, 0);
        CdControlB(0xC, 0, 0);
        return;
    }
    status = D_800AE24C;
    CdControlB(1, 0, status);
    if (*(s32 *)status != 0x42) {
        CdControl(9, 0, 0);
        return;
    }
    target = 0x82;
    do {
        CdControl(1, 0, status);
    } while (*(s32 *)status != target);
    CdControl(9, 0, 0);
}

void CdStop(void) {
    CdControl(8, 0, 0);
}


extern char D_8008D188[];

void func_8003CDBC(s32 arg0) {
    u8 pad[0x40];
    u8 result[8];
    s32 *pos;
    s32 value;
    s32 posValue;
    u32 base;
    s32 count;
    s32 i;
    s32 *src;

    if (D_800A2F74 == 0) {
        CdGetToc(D_800BDEBC);
        D_800A2F74 = 1;
    }
    CdIntToPos(D_80098340[arg0 * 3] + 0x13C, &D_800A45AC[-1]);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = D_80098340[arg0 * 3 + 1];
    pos = &D_800A45AC[-1];
    D_800A37CC = arg0;
    D_800A45AC[0] = value;
    if (pos == NULL) {
        SystemShowFatalError(D_8008D188);
    }
    posValue = D_800A45AC[0];
    base = (0x1F4000 - posValue) | RAM_CACHED_BASE;
    FileRead(base, posValue, 1, pos);
    src = (s32 *)base;
    count = *src++;
    for (i = 0; i < count; i++) {
        D_800B9F44[i] = *src++ + base;
    }
}

INCLUDE_RODATA("asm/nonmatchings/cd", D_8008D188);
INCLUDE_RODATA("asm/nonmatchings/cd", D_8008D1A8);
INCLUDE_RODATA("asm/nonmatchings/cd", D_8008D1C4);

void func_8003CEFC(void) {
}

void func_8003CF04(void) {
}

INCLUDE_ASM("asm/nonmatchings/cd", func_8003CF0C);

extern s32 D_800A2F84nm asm("D_800A2F84.NON_MATCHING");
extern void func_800414E0(void *, s32, s32);
extern s32 func_80041B7C(s32);

extern s32 D_800A3A04Lui asm("D_800A3A04Absolute");
void func_8003D25C(u8 *object) {
    s32 i;
    s32 value;
    s32 count;
    s32 diff;
    u8 flag;

    D_800A3A04nm[0] = 3;
    func_80029CB4(object);
    D_800A3A04Lui = 0xD;
    flag = 1;
    if (*(u8 *)(object + 0x26A) & 0x10) {
        i = *(u8 *)(object + 0x26A) & 0x40;
        if (D_800A2F84nm != 0) {
            i = !i;
        }
        if (i != 0) {
            *(s16 *)(object + 0x2AC) = *(s16 *)(object + 0x274) * 10;
            *(s16 *)(object + 0x2FC) = *(s16 *)(object + 0x274) * 10;
            *(s16 *)(object + 0x2D4) = *(s16 *)(object + 0x274) * 4;
            *(s16 *)(object + 0x324) = *(s16 *)(object + 0x274) * 4;
        } else {
            *(s16 *)(object + 0x2D4) = *(s16 *)(object + 0x274) * 10;
            *(s16 *)(object + 0x324) = *(s16 *)(object + 0x274) * 10;
            *(s16 *)(object + 0x2AC) = *(s16 *)(object + 0x274) * 4;
            *(s16 *)(object + 0x2FC) = *(s16 *)(object + 0x274) * 4;
        }
        for (i = 0; i < 4; i++) {
            if (*(u8 *)(object + 0x26A) & 0x40) {
                if (i < 2) {
                    continue;
                }
            } else {
                if (i >= 2) {
                    break;
                }
            }
            value = *(u16 *)(object + i * 2 + 0x26C);
            *(u16 *)(object + i * 2 + 0x26C) = value - 1;
            count = (s16)(value - 1);
            if (count == 0x5A) {
                goto special;
            }
            if (count == 5) {
            special:
                if (*(s16 *)(object + 0x1EC) == 0) {
                    func_800414E0(object, 8, 3);
                }
                *(u16 *)(object + i * 2 + 0x26C) =
                    *(u16 *)(object + i * 2 + 0x26C) - 1;
            } else if (count == 0x46) {
                diff = value - 2;
                *(s16 *)(object + i * 2 + 0x26C) = diff;
            } else if (count == 0x28) {
                diff = value - 2;
                *(s16 *)(object + i * 2 + 0x26C) = diff;
                func_8002D3EC(object);
                *(u8 *)(object + i + 0x3A6) = 1;
            }
            do {
                if (*(s16 *)(object + i * 2 + 0x26C) > 0) {
                    flag = 0;
                }
            } while (0);
        }
        if (flag != 0) {
            if (*(u8 *)(object + 0x26A) & 0x40) {
                *(u8 *)(object + 0x26A) &= 0xAE;
            } else {
                *(s16 *)(object + 0x274) = -0x23;
                *(u8 *)(object + 0x26A) =
                    (*(u8 *)(object + 0x26A) | 0x40) & 0xEF;
            }
            i = 3;
            do {
                *(s16 *)(object + i * 0x28 + 0x2B0) = 0;
                i--;
            } while (i >= 0);
        } else {
            if (*(s16 *)(object + 0x274) < 4) {
                *(s16 *)(object + 0x274) = *(s16 *)(object + 0x274) + 1;
            }
        }
    } else {
        if ((s16)++ * (u16 *)(object + 0x274) == 5) {
            *(u8 *)(object + 0x26A) |= 0x10;
            *(s16 *)(object + 0x274) = 0;
            if (*(u8 *)(object + 0x26A) & 0x40) {
                *(s16 *)(object + 0x270) = 100;
                *(s16 *)(object + 0x272) = 100;
            } else {
                *(s16 *)(object + 0x26C) = 100;
                *(s16 *)(object + 0x26E) = 100;
            }
        }
    }
}

extern s32 func_80029EF8(u8 *);

void func_8003D528(u8 *object) {
    s32 result;
    s32 value;
    s32 mask;

    value = *(s32 *)(object + 0x28C) + 0x4B;
    *(s32 *)(object + 0x28C) = value;
    result = 0;
    if (value >= 0x3E81) {
        *(s32 *)(object + 0x28C) = 0x3E80;
    }
    if (*(s16 *)(object + 0x1EC) == 0) {
        result = func_80029EF8(object);
    }
    if (*(s32 *)(object + 0x28C) == 0x3E80) {
        goto trigger;
    }
    if (*(s16 *)(object + 0x1EC) == 0 && (*(u8 *)(object + 0x26A) & 1) == 0) {
        mask = ~*(s32 *)(object + 0x23C) & 0x40;
        if ((result & mask) != 0) {
        trigger:
            *(s32 *)(object + 0x290) = 0x7D000;
            *(u8 *)(object + 0x26A) &= 0xDD;
        }
    }
    *(s32 *)(object + 0x23C) = result;
}

void func_8003D5F8(u8 *object) {
    u16 flags;
    s32 i;
    u32 total;
    u8 *entry;

    flags = *(u16 *)(object + 0x3A4);
    total = 0;
    if (flags != 0) {
        i = 0;
        do {
            entry = object + i;
            if (*(s8 *)(entry + 0x3A6) == 0) {
                total = total + 0x14;
            }
            if (*(s8 *)(entry + 0x3AE) != 0) {
                total = total + *(s8 *)(entry + 0x3AE) * 3;
            }
            i = i + 1;
        } while (i < 8);
    }
    *(u16 *)(object + 0x280) = total;
}

void func_8003D654(u8 *object) {
    s32 i;
    u16 count;
    count = *(u16 *)(object + 0x280);
    *(u16 *)(object + 0x280) = count - 1;
    if ((s16)count < 0) {
        *(s16 *)(object + 0x3A4) = 0;
        i = 0;
        do {
            *(object + i + 0x3A6) = 1;
            *(object + i + 0x3AE) = 0;
            i++;
        } while (i < 8);
    }
}

void func_8003D69C(u8 *object) {
    s32 value;
    s32 now;

    value = *(volatile u16 *)(object + 0x278);
    now = *(u16 *)(object + 0x278);
    *(u16 *)(object + 0x278) = now - 1;
    *(s16 *)(object + 0x2A2) = (s16)value / 10;
    if ((now << 16) < 0) {
        *(u16 *)(object + 0x2A2) = 0;
        *(u8 *)(object + 0x26A) &= ~0x04;
    }
}

void func_8003D6F8(u8 *object) {
    s32 value;
    s32 now;

    value = *(volatile u16 *)(object + 0x27A);
    now = *(u16 *)(object + 0x27A);
    *(u16 *)(object + 0x27A) = now - 1;
    *(s16 *)(object + 0x2A8) = (s16)value / 10;
    if ((now << 16) < 0) {
        *(u16 *)(object + 0x2A8) = 0;
        *(u8 *)(object + 0x26A) &= ~0x08;
    }
}

void func_8003D754(u8 *object) {
    s32 buttons;

    buttons = func_80041B7C(*(s8 *)(object + 0x20B));
    if (buttons & ((u16) ~*(s32 *)(object + 0x238) & 0x1000)) {
        *(u8 *)(object + 0x26B) -= 1;
        func_800414E0(object, 10, 6);
    } else if (buttons & ((u16) ~*(s32 *)(object + 0x238) & 0x4000)) {
        *(u8 *)(object + 0x26B) += 1;
        func_800414E0(object, 10, 6);
    }
    *(u8 *)(object + 0x26B) = (*(u8 *)(object + 0x26B) + 4) % 4;
    if (buttons & ((u16) ~*(s32 *)(object + 0x238) & 0x8000)) {
        func_800414E0(object, 10, 6);
        switch (*(u8 *)(object + 0x26B)) {
        case 0:
            if (*(u8 *)(object + 0x26A) & 1) {
                *(u8 *)(object + 0x26A) &= 0xFE;
            } else {
                *(u8 *)(object + 0x26A) |= 1;
            }
            break;
        case 1:
            if (*(u8 *)(object + 0x26A) & 2) {
                *(u8 *)(object + 0x26A) &= 0xFD;
            } else {
                *(u8 *)(object + 0x26A) |= 2;
            }
            break;
        case 2:
            if (*(s16 *)(object + 0x2AA) >= -7) {
                *(u16 *)(object + 0x2A8) -= 1;
                *(u16 *)(object + 0x2AA) -= 1;
            }
            break;
        case 3:
            if (*(s16 *)(object + 0x2A4) >= -7) {
                *(u16 *)(object + 0x2A2) -= 1;
                *(u16 *)(object + 0x2A4) -= 1;
            }
            break;
        }
        if (*(s16 *)(object + 0x2A2) < -16) {
            *(s16 *)(object + 0x2A2) = -16;
        }
        if (*(s16 *)(object + 0x2A8) < -16) {
            *(s16 *)(object + 0x2A8) = -16;
        }
    }
    if (buttons & ((u16) ~*(s32 *)(object + 0x238) & 0x2000)) {
        func_800414E0(object, 10, 6);
        switch (*(u8 *)(object + 0x26B)) {
        case 0:
            if (*(u8 *)(object + 0x26A) & 1) {
                *(u8 *)(object + 0x26A) &= 0xFE;
            } else {
                *(u8 *)(object + 0x26A) |= 1;
            }
            break;
        case 1:
            if (*(u8 *)(object + 0x26A) & 2) {
                *(u8 *)(object + 0x26A) &= 0xFD;
            } else {
                *(u8 *)(object + 0x26A) |= 2;
            }
            break;
        case 2:
            if (*(s16 *)(object + 0x2AA) < 8) {
                *(u16 *)(object + 0x2A8) += 1;
                *(u16 *)(object + 0x2AA) += 1;
            }
            break;
        case 3:
            if (*(s16 *)(object + 0x2A4) < 8) {
                *(u16 *)(object + 0x2A2) += 1;
                *(u16 *)(object + 0x2A4) += 1;
            }
            break;
        }
        if (*(s16 *)(object + 0x2A2) >= 17) {
            *(s16 *)(object + 0x2A2) = 16;
        }
        if (*(s16 *)(object + 0x2A8) >= 17) {
            *(s16 *)(object + 0x2A8) = 16;
        }
    }
    *(u8 *)(object + 0x26A) &= 0xF3;
    if (*(s16 *)(object + 0x2A2) != 0) {
        *(u8 *)(object + 0x26A) |= 4;
    }
    if (*(s16 *)(object + 0x2A8) != 0) {
        *(u8 *)(object + 0x26A) |= 8;
    }
    *(s32 *)(object + 0x238) = buttons;
}

s32 func_8003DAD0(s32 a, s32 b) {
    if (b >= D_800BE974[0]) {
        if (a >= D_800BE974[0] / 2)
            return 0;
        b -= D_800BE974[0];
    }
    return !(a < b);
}

s32 func_8003DB18(s32 start, s32 end, s32 value) {
    s32 result;
    s32 offset;
    offset = D_800BE974[0];
    if (value < end) {
        if (value >= start) {
            value += offset;
            return 1;
        }
        value += offset;
    }
    result = 0;
    if (start >= end)
        result = value >= start;
    return result;
}

s32 func_8003DB5C(s32 arg0, s32 arg1, s32 arg2) {
    s32 cmp;
    s32 result;
    s32 offset;
    offset = D_800BE974[0];
    if (arg2 < arg1) {
        arg2 += offset;
        if ((offset / 2) >= arg0) {
            arg0 += offset;
        }
    }
    result = 0;
    offset = arg0 < arg1;
    cmp = offset;
    if (cmp == 0) {
        result = arg2 >= arg0;
    }
    return result;
}

extern void func_8003D754(u8 *);
extern s32 func_800358EC(s32 *);
extern void CarSteerTowardHeading(u8 *, s32);
extern void func_80041564(u8 *, s32);
extern s32 D_800A2EA8CarState[] asm("D_800A2EA8");
extern s32 D_800A2EACCarState[] asm("D_800A2EAC");
extern s32 D_800A2EB0CarState[] asm("D_800A2EB0");
extern u8 D_800A2EE0CarState[] asm("D_800A2EE0");
extern s32 D_800A2F4CCarState[] asm("D_800A2F4C");
extern u8 *D_800A3554CarState[] asm("D_800A3554");
extern u8 *D_800A3960CarState[] asm("D_800A3960");
extern s32 D_800A39E0CarState asm("D_800A39E0");
extern s32 D_800A3A04CarState[] asm("D_800A3A04");
extern s32 D_800BE974CarState[] asm("D_800BE974");
extern u8 *D_800BE980CarState[] asm("D_800BE980");

extern u8 *D_800A3960CarStateStore[] asm("D_800A3960");
extern s32 D_800A3A04CarStateStore[] asm("D_800A3A04");
void func_8003DBA8(u8 *object) {
    s32 delta[3];
    s32 ringResult;
    s32 ringV1;
    s32 ringA0;
    s32 ringA1;
    register s32 ringA2 asm("a2");
    register s32 ringA3 asm("a3");
    s32 sectionCount;
    s32 centerSection;
    s32 mask;
    s32 previousOffset;
    s32 earlierOffset;
    s32 trailingOffset;
    s32 offset;
    s32 section;
    u8 *earlier;
    s32 coordinate;
    s32 coordinateY;
    s32 targetX;
    s32 targetY;
    s32 trailingX;
    s32 direction;
    s32 steerAmount;
    s32 otherSteerAmount;
    register s32 trailingSection asm("a1");
    s32 charge;
    register s32 angleDelta asm("a1");
    s32 trailingY;
    s32 control;
    s32 i;
    s32 buttons;
    s32 earlierSection;
    s32 angle;
    s32 turnLimit;
    s32 j;
    s8 severity;
    u16 oldSteerTime;
    u16 oldOtherSteerTime;
    u16 brake;
    u16 oldWait;
    u16 newBrake;
    u16 oldDamageTime;
    u16 steerTime;
    u16 otherSteerTime;
    s32 damageTime;
    s32 state;
    u8 flags;
    u8 nextState;
    u8 *trailing;
    u8 *entry;
    u8 *targets;
    u8 *previous;
    u8 *damage;

    sectionCount = D_800BE974CarState[0];
    section = *(s16 *)(object + 0x1E0);
    if ((sectionCount < section) || (section < 0)) {
        section = 0;
    }
    entry = D_800BE980CarState[0] + (section * 0x90);
    targets = entry + 0x34;
    if (*(s16 *)(entry + 0x34) != section) {
        *(s16 *)(entry + 0x34) = section;
        *(s16 *)(entry + 0x36) = 0;
        previousOffset = D_800BE974CarState[0] - 1;
        earlierOffset = D_800BE974CarState[0] - 2;
        earlierSection =
            (s32)(section + earlierOffset) % (s32)D_800BE974CarState[0];
        previous =
            D_800BE980CarState[0] +
            (((s32)(section + previousOffset) % (s32)D_800BE974CarState[0]) *
             0x90);
        earlier = D_800BE980CarState[0] + (earlierSection * 0x90);
        coordinate = *(s32 *)(previous + 0x40);
        *(s32 *)(entry + 0x40) =
            (s32)((coordinate - *(s32 *)(earlier + 0x40)) + coordinate);
        coordinateY = *(s32 *)(previous + 0x44);
        *(s32 *)(entry + 0x44) =
            (s32)((coordinateY - *(s32 *)(earlier + 0x44)) + coordinateY);
        targetX = *(s32 *)(previous + 0x38);
        *(s32 *)(entry + 0x38) =
            (s32)((targetX - *(s32 *)(earlier + 0x38)) + targetX);
        targetY = *(s32 *)(previous + 0x3C);
        *(s32 *)(entry + 0x3C) =
            (s32)((targetY - *(s32 *)(earlier + 0x3C)) + targetY);
        trailingX = *(s32 *)(previous + 0x48);
        *(s32 *)(entry + 0x48) =
            (s32)((trailingX - *(s32 *)(earlier + 0x48)) + trailingX);
        trailingY = *(s32 *)(previous + 0x4C);
        *(s32 *)(entry + 0x4C) =
            (s32)((trailingY - *(s32 *)(earlier + 0x4C)) + trailingY);
    }
    state = *(u8 *)(object + 0x269);
    offset = *(s16 *)(object + 0x28A);
    *(s32 *)(object + 0x84) = 0xAA0000;
    *(s32 *)(object + 0x22C) = 0;
    switch (state) {
    case 0x0:
        delta[0] = *(s32 *)(entry + 0x38) - *(s32 *)(object + 0x0);
        delta[1] = *(s32 *)(entry + 0x3C) - *(s32 *)(object + 0x4);
        delta[2] = 0;
        *(u16 *)(object + 0x276) = 0xFU;
        *(u16 *)(object + 0x278) = 0U;
        *(u16 *)(object + 0x27E) = 0U;
        if ((*(s16 *)(object + 0x1EC) == 0) &&
            ((D_800A2EE0CarState[0] != 0) ||
             !(*(s32 *)(object + 0x3A4) & 0x100F))) {
            func_8003D754(object);
        }
        if (MathGetAngleDelta(*(s16 *)(object + 0x114),
                              *(u16 *)(D_800BE980CarState[0] +
                                       *(s16 *)(object + 0x1E0) * 0x90 +
                                       0x10)) < 0) {
            if (-MathGetAngleDelta(*(s16 *)(object + 0x114),
                                   *(u16 *)(D_800BE980CarState[0] +
                                            *(s16 *)(object + 0x1E0) * 0x90 +
                                            0x10)) < 0x15) {
                turnLimit = 4;
            } else {
                turnLimit = 0x14;
            }
        } else {
            if (MathGetAngleDelta(*(s16 *)(object + 0x114),
                                  *(u16 *)(D_800BE980CarState[0] +
                                           *(s16 *)(object + 0x1E0) * 0x90 +
                                           0x10)) >= 0x15) {
                turnLimit = 0x14;
            } else {
                turnLimit = 4;
            }
        }
        ringResult = D_800A39E0CarState;
        D_800A2F4CCarState[0] = turnLimit;
        asm("" : "=r"(ringResult) : "0"(ringResult) : "memory");
        ringV1 = D_800BE974CarState[0];
        ringA1 = *(s16 *)(object + 0x1E0);
        {
            const s32 section = ringA1;
            s32 end = ringResult + offset - 4;
            s32 count;
            count = ringV1;
            if (end >= count) {
                if (section >= count / 2) {
                    ringResult = 0;
                } else {
                    end -= count;
                    ringResult = !(section < end);
                }
            } else {
                ringResult = !(section < end);
            }
        }
        if ((u8)ringResult) {
            nextState = 2;
            if (*(u8 *)(object + 0x26A) != 0) {
                nextState = 1;
            }
            *(u8 *)(object + 0x269) = nextState;
        }
        if ((D_800A2EB0CarState[0] == 0) && (*(s8 *)(object + 0x204) == 1) &&
            (D_800A2EA8CarState[0] >= *(s16 *)(object + 0x1D6))) {
            func_80041564(D_800A3554CarState[0], 0x23);
        }
        goto updateMotion;
    case 0x1:
        if ((*(s16 *)(object + 0x1EC) == 0) &&
            ((D_800A2EE0CarState[0] != 0) ||
             !(*(s32 *)(object + 0x3A4) & 0x100F))) {
            func_8003D754(object);
        }
        delta[0] = *(s32 *)(targets + 0x14) - *(s32 *)(object + 0);
        ringResult = *(s32 *)(targets + 0x18);
        ringV1 = *(s32 *)(object + 4);
        ringResult -= ringV1;
        ringV1 = D_800A39E0CarState;
        delta[2] = 0;
        delta[1] = ringResult;
        *(s32 *)(object + 0x84) = 0x6B0000;
        ringA0 = D_800BE974CarState[0];
        ringA1 = *(s16 *)(object + 0x1E0);
        D_800A2F4CCarState[0] = 8;
        {
            const s32 section = ringA1;
            s32 end = ringV1 + offset;
            const s32 count = ringA0;
            if (end >= count) {
                if (section >= count / 2) {
                    ringResult = 0;
                } else {
                    end -= count;
                    ringResult = !(section < end);
                }
            } else {
                ringResult = !(section < end);
            }
        }
        if ((u8)ringResult) {
            *(s32 *)(object + 0x84) = 0x3D0000;
            brake = *(u16 *)(object + 0x27C) + 0x14;
            *(u16 *)(object + 0x27C) = brake;
            if ((s16)brake >= 0x15F) {
                *(u16 *)(object + 0x27C) = 0x15EU;
            }
        }
        {
            const s32 section = *(s16 *)(object + 0x1E0);
            s32 end = D_800A39E0CarState + offset + 1;
            register s32 count asm("v1");
            count = D_800BE974CarState[0];
            if (end >= count) {
                if (section >= count / 2) {
                    ringResult = 0;
                } else {
                    end -= count;
                    ringResult = !(section < end);
                }
            } else {
                ringResult = !(section < end);
            }
        }
        if ((u8)ringResult) {
            ringResult = 3;
            ringV1 = *(s16 *)(object + 0x2A2);
            *(u8 *)(object + 0x269) = ringResult;
            *(u16 *)(object + 0x274) = 0;
            if (ringV1 < 0)
                ringV1 = -ringV1;
            ringResult = ringV1 * 10;
            asm("" : "=r"(ringResult) : "0"(ringResult) : "memory");
            ringV1 = *(s16 *)(object + 0x2A8);
            *(u16 *)(object + 0x278) = ringResult;
            if (ringV1 < 0)
                ringV1 = -ringV1;
            ringResult = ringV1 * 5;
            ringA3 = ringResult * 2;
            ringResult = *(u16 *)(object + 0x2A0);
            ringA0 = *(u16 *)(object + 0x2A2);
            ringV1 = *(u16 *)(object + 0x2A6);
            ringA1 = *(u16 *)(object + 0x2A8);
            ringA2 = *(s32 *)(object + 0x28C);
            *(u16 *)(object + 0x27A) = ringA3;
            ringResult += ringA0;
            ringV1 += ringA1;
            *(u16 *)(object + 0x2A0) = ringResult;
            *(u16 *)(object + 0x2A6) = ringV1;
            if (ringA2 == 0) {
                *(s32 *)(object + 0x28C) = 0x64;
            }
            damageTime = 0;
            if (*(u16 *)(object + 0x3A4) != 0) {
                i = 0;
                do {
                    damage = object + i;
                    if (*(s8 *)(damage + 0x3A6) == 0) {
                        damageTime += 0x14;
                    }
                    severity = *(s8 *)(damage + 0x3AE);
                    if (severity != 0) {
                        damageTime += severity * 3;
                    }
                    i += 1;
                } while (i < 8);
            }
            *(u16 *)(object + 0x280) = damageTime;
        }
        goto updateMotion;
    case 0x2:
        delta[0] = *(s32 *)(entry + 0x40) - *(s32 *)(object + 0x0);
        delta[1] = *(s32 *)(entry + 0x44) - *(s32 *)(object + 0x4);
        D_800A2F4CCarState[0] = 4;
        delta[2] = 0;
        *(u16 *)(object + 0x276) = 0U;
        goto updateMotion;
    case 0x3:
        ringResult = *(u16 *)(object + 0x27E);
        ringV1 = D_800A2EACCarState[0];
        *(s32 *)(object + 0x90) = 0;
        *(s32 *)(object + 0x84) = 0;
        *(u16 *)(object + 0x108) = 0;
        ringResult += 1;
        *(u16 *)(object + 0x27E) = ringResult;
        if (ringV1 == 0) {
            if (*(s32 *)(object + 0x3A4) & 0x100F) {
                if (object == D_800A3960CarState[0]) {
                    D_800A3960CarStateStore[0] = 0;
                }
                if (D_800A2EE0CarState[0] == 0) {
                    *(u8 *)(object + 0xF4) = 0;
                    *(s32 *)(object + 0x414) = -1;
                    func_80041848(object, 0xC);
                    return;
                }
                goto block_74;
            }
        block_74:
            if (*(u8 *)(object + 0x26A) == 0) {
                if (*(u16 *)(object + 0x3A4) == 0) {
                    if (*(s16 *)(object + 0x1D6) <
                        (D_800A2EA8CarState[0] + 1)) {
                        D_800A3A04CarStateStore[0] = 3;
                        func_80029CB4(object);
                        control = *(s16 *)(object + 0x1EC);
                        D_800A3A04CarState[0] = 0xD;
                        if (control == 0) {
                            func_80041564(object, 0x42);
                        }
                        oldWait = *(u16 *)(object + 0x276);
                        *(u16 *)(object + 0x276) = (u16)(oldWait - 1);
                        if ((oldWait << 0x10) <= 0) {
                            *(u8 *)(object + 0x269) = 2U;
                        }
                        newBrake = *(u16 *)(object + 0x27C) - 0x1E;
                        *(u16 *)(object + 0x27C) = newBrake;
                        if ((newBrake << 16) < 0) {
                            *(u16 *)(object + 0x27C) = 0U;
                        }
                    }
                    goto block_83;
                }
                goto block_84;
            }
        block_83:
            if (*(u16 *)(object + 0x3A4) != 0) {
            block_84:
                oldDamageTime = *(u16 *)(object + 0x280);
                *(u16 *)(object + 0x280) = (u16)(oldDamageTime - 1);
                if ((oldDamageTime << 16) < 0) {
                    *(u16 *)(object + 0x3A4) = 0;
                    j = 0;
                    do {
                        *(object + j + 0x3A6) = 1;
                        *(object + j + 0x3AE) = 0;
                        j++;
                    } while (j < 8);
                }
            } else {
                flags = *(u8 *)(object + 0x26A);
                if (flags & 1) {
                    func_8003D25C(object);
                } else {
                    if (flags & 4) {
                        steerTime = *(u16 *)(object + 0x278);
                        steerAmount = (s16)steerTime / 10;
                        oldSteerTime = (*(volatile u16 *)(object + 0x278));

                        *(u16 *)(object + 0x278) = (u16)(oldSteerTime - 1);
                        *(s16 *)(object + 0x2A2) = (s16)steerAmount;
                        if ((oldSteerTime << 16) < 0) {
                            *(s16 *)(object + 0x2A2) = 0;
                            *(u8 *)(object + 0x26A) =
                                (u8)(*(u8 *)(object + 0x26A) & 0xFB);
                        }
                    }
                    if (*(u8 *)(object + 0x26A) & 8) {
                        otherSteerTime = *(u16 *)(object + 0x27A);
                        otherSteerAmount = (s16)otherSteerTime / 10;
                        oldOtherSteerTime = (*(volatile u16 *)(object + 0x27A));

                        *(u16 *)(object + 0x27A) = (u16)(oldOtherSteerTime - 1);
                        *(s16 *)(object + 0x2A8) = (s16)otherSteerAmount;
                        if ((oldOtherSteerTime << 16) < 0) {
                            *(s16 *)(object + 0x2A8) = 0;
                            *(u8 *)(object + 0x26A) =
                                (u8)(*(u8 *)(object + 0x26A) & 0xF7);
                        }
                    }
                }
            }
            if (*(u8 *)(object + 0x26A) & 2) {
                charge = *(s32 *)(object + 0x28C) + 0x4B;
                *(s32 *)(object + 0x28C) = charge;
                buttons = 0;
                if (charge >= 0x3E81) {
                    *(s32 *)(object + 0x28C) = 0x3E80;
                }
                if (*(s16 *)(object + 0x1EC) == 0) {
                    buttons = func_80029EF8(object);
                }
                if (*(s32 *)(object + 0x28C) == 0x3E80)
                    goto pulse;
                if (*(s16 *)(object + 0x1EC) == 0 &&
                    (*(u8 *)(object + 0x26A) & 1) == 0) {
                    mask = ~*(s32 *)(object + 0x23C) & 0x40;
                    if ((buttons & mask) != 0) {
                    pulse:
                        *(s32 *)(object + 0x290) = 0x7D000;
                        *(u8 *)(object + 0x26A) &= 0xDD;
                    }
                }
                *(s32 *)(object + 0x23C) = buttons;
                return;
            }
        }
        return;
    case 0xFF:
        ringV1 = *(s32 *)(object + 0x90);
        D_800A2F4CCarState[0] = 0xA;
        if (ringV1 > 0x140000) {
            trailingOffset = sectionCount - 3;
            trailingSection =
                (s32)(*(s16 *)(object + 0x1E0) + trailingOffset) % sectionCount;
            *(s32 *)(object + 0x84) = 0xA0000;
            trailing = D_800BE980CarState[0] + (trailingSection * 0x90);
            if (*(s16 *)(trailing + 0x34) == trailingSection) {
                delta[0] = *(s32 *)(trailing + 0x38) - *(s32 *)(object + 0x0);
                delta[1] = *(s32 *)(trailing + 0x3C) - *(s32 *)(object + 0x4);
                delta[2] = 0;
                goto updateMotion;
            }
        } else {
            angleDelta = MathGetAngleDelta(
                *(s16 *)(object + 0x114),
                *(u16 *)(D_800BE980CarState[0] +
                         *(s16 *)(object + 0x1E0) * 0x90 + 0x10));
            if (angleDelta >= 0) {
                if (angleDelta < 0x14) {
                    goto block_114;
                }
                goto block_115;
            }
            if (-angleDelta < 0x14) {
            block_114:
                ringV1 = *(u16 *)(D_800BE980CarState[0] +
                                  *(s16 *)(object + 0x1E0) * 0x90 + 0x10);
                *(u8 *)(object + 0x269) = 2U;
                *(s16 *)(object + 0x114) = ringV1;
            } else {
            block_115:
                if (angleDelta > 0) {
                    angle = (u16) * (s16 *)(object + 0x114) + 0x3EC;
                } else {
                    angle = (u16) * (s16 *)(object + 0x114) + 0x14;
                }
                *(s16 *)(object + 0x114) = (s16)(angle & 0x3FF);
            }
            *(s32 *)(object + 0x90) = 0;
            *(s16 *)(object + 0x116) = (s16)(*(s16 *)(object + 0x114) * 4);
            func_80037130(object);
            func_80029CB4(object);
            (*(void (**)(u8 *))(object + 0x354))(object);
            return;
        }
        return;
    default:
        /* Retail also reaches updateMotion with delta unset for unknown states. */
        break;
    }
updateMotion:
    ringResult = *(s32 *)(object + 0x90);
    ringV1 = *(s32 *)(object + 0x84);
    ringA0 = 0x20000;
    ringV1 = ringV1 < ringResult;
    *(s32 *)(object + 0x88) = ringA0;
    if (ringV1) {
        func_80028F98(object);
    }
    if ((*(u8 *)(object + 0x269) == 1) &&
        (*(s32 *)(object + 0x90) <= 0xA0000)) {
        *(s32 *)(object + 0x90) = 0xA0000;
    }
    func_800298E0(object);
    direction = func_800358EC(delta);
    if (*(s16 *)(object + 0x1EC) == 1) {
        D_800A2F4CCarState[0] = 0xE;
    }
    CarSteerTowardHeading(object, direction);
    ringV1 = *(u16 *)(object + 0x114);
    D_800A2F4CCarState[0] = 0x14;
    *(u16 *)(object + 0x104) = ringV1;
    func_80037130(object);
    func_80029CB4(object);
    (*(void (**)(u8 *))(object + 0x354))(object);
    if (*(u8 *)(object + 0x269) == 3) {
        *(s16 *)(object + 0x20E) = 0;
    }
}

#ifdef NON_MATCHING
/* 2026-10-11 (w3e): size exact 0x308, draft-unit diff 393 bytes
 * (from 6885 with size -32). Applied on top of the w2i state:
 * 1) THE THREADING FIX: `asm("" : : "r"(object));` inside the special-case
 *    arm right before `return 1;` blocks jump-threading and reproduces
 *    retail's `bnez v0,skip; nop; j epilogue; li v0,1` (size became exact).
 * 2) flag declared s32 (u8 adds an extra andi at 2 sites; retail 0x308 =
 *    s32 shape + the unthreaded arm).
 * 3) the arms' `value +=` reads the divisor through an in-function alias
 *    `extern s32 D_800BE974R[] asm("D_800BE974");` — retail reloads BE974
 *    for the += instead of reusing the div register.
 * 4) tail `pace - 2 + value` duplicated textually in both
 *    RandomScaledGet arms (retail hoists addiu into both).
 * Left (393 bytes, mostly register placement): first-half divisor in a3 vs
 * retail a0 (value a2 vs a1, end a1 vs v1, flag v1 vs a2/move-v0 cascade);
 * retail's BE974 reload sits BEFORE the start lh, ours inside the true arm;
 * second half: retail keeps `A39E0 - (A3820+7)` un-reassociated
 * (addiu a1,a1,7; subu) while ours folds to (A39E0-7)-A3820, and the
 * `sh 0x276` arm ordering differs. Permuter round from this exact-size
 * base is the next lever.
 * 2026-10-11 (w4d): 5405 -> 5240. (a) half2 now uses FRESH D_800BE974[0]
 * reads for both % divisors (the old `% newVar` kept the half1 divisor
 * pseudo live across half2 and pinned it in a3); (b) each `X + K` /
 * `A39E0 - (A3820 + K)` group is its own single-use named local
 * (t/u/w; +8 group is x) -- multi-use or inline spellings reassociate the
 * addiu onto the wrong operand. Half2 div/mfhi/addiu/subu chain now
 * matches retail exactly. Left: half1 A3560/A376C load regs v0/v1
 * swapped (shape right), mfhi a1/a2/v1 value+end placement, the BE974
 * reload still lands inside the true arm instead of before the start lh,
 * flag cascade (a2+andi vs v1 direct) and the tail s1/s2 swap +
 * `pace-2` addiu duplication.
 * 2026-10-11 (w5d): cc1 -dl/-dg decode of the half1 register map. Pool order
 * is [v1,a0,a1,a2,...] (v0 reserved for the return). Allocation order by
 * priority: flag(77) 12refs/26insns=1.385 -> v1; start(75) 12/30=1.2 -> a0;
 * value(74) 14/42=1.0 -> skips a1 because end's mfhi lands in a1 inside
 * value's range (the conflict self-reinforces) -> a2; end(76) 8/24=1.0 ->
 * a1. Retail = end->v1, start->a0, value->a1, flag->a2, which needs
 * end > start > value > flag in priority. Reaching it takes TWO zero-byte
 * changes at once: raise end above start (duplicate input-only barrier
 * after the end divmod: +2 refs -> 30/24=1.25) and drop flag below value
 * (split half1's cascade onto its own flag1 local: ~6 refs -> ~0.54;
 * half2 must keep the shared flag). Tried alone: output-tied ref-raiser on
 * end + flag1 split gave 8350 — the OUTPUT-tied form leaves a real `nop`
 * (maspsx keeps the move) and end still took a0 because flag1's v1 writes
 * sat inside end's range; permuter round 1 (18 min, 18k iters) found
 * output-2565-1: hoist `x = D_800BE974R[0];` before each half's start lh
 * and `value += x` in all four arms — 2565 in-unit but 6055/6835 in the
 * real TU (half2-only and half1-only bisects both worse); NOT transferred.
 * The priority cascade above remains the best lead.
 * 2026-10-11: computing the RandomScaledGet sum in x before the pace sum
 * reduces the full-TU linked diff from 372 to 371 bytes at 776 bytes.
 * Eight later shapes did not improve it. Both narrowing flag and declaring
 * ahead as s16 add 16 bytes. The assembly fallback remains active. */
extern u8 D_800A372C[];
extern s32 D_800A2CE0[];
extern s32 D_800A2EA8[];
extern s32 D_800BE974[];
extern s32 D_800A3560;
extern s32 D_800A376C;
extern s32 D_800A3820;

s32 func_8003E78C(u8 *object) {
    extern s32 D_800BE974R[] asm("D_800BE974");
    s32 laps;
    s32 value;
    s32 start;
    s32 end;
    s32 flag;
    s32 newVar;
    s32 t;
    s32 u;
    s32 w;
    s32 x;
    s32 pace;
    s32 ahead;

    if (*(s16 *)(object + 0x288) != 0) {
        if (D_800A372C[0] != 0 && D_800A2CE0[0] == 3 &&
            *(s16 *)(object + 0x1EC) == 0 && *(s16 *)(object + 0x1E0) >= 100) {
            asm("" : : "r"(object));
            return 1;
        }
        newVar = D_800BE974[0];
        x = D_800A3560 + 8;
        value = (x + D_800A376C) % newVar;
        t = D_800A3820 + 0x14;
        end = (D_800A39E0 - t + newVar) % newVar;
        start = *(s16 *)(object + 0x1E0);
        if (value < end) {
            if (value >= start) {
                value += D_800BE974R[0];
                flag = 1;
            } else {
                value += D_800BE974R[0];
                flag = 0;
                if (start >= end)
                    flag = value >= start;
            }
        } else {
            flag = 0;
            if (start >= end)
                flag = value >= start;
        }
        if (flag != 0)
            return 1;
        *(s16 *)(object + 0x288) = 0;
        *(u16 *)(object + 0x284) = *(u16 *)(object + 0x284) + 1;
        return 0;
    }
    laps = *(s16 *)(object + 0x1D6);
    if (laps < 2)
        return 0;
    if (*(s16 *)(object + 0x276) == 0) {
        if ((u32)laps >= (u32) * (s32 *)(object + 0x29C) ||
            D_800A2EA8[0] < laps)
            *(s16 *)(object + 0x276) = 1;
        return 0;
    }
    if (D_800A372C[0] != 0)
        return 0;
    u = D_800A3820 + 7;
    value = (D_800A39E0 - u + D_800BE974[0]) % D_800BE974[0];
    w = D_800A3820 + 0xF;
    end = (D_800A39E0 - w + D_800BE974[0]) % D_800BE974[0];
    start = *(s16 *)(object + 0x1E0);
    if (value < end) {
        if (value >= start) {
            value += D_800BE974R[0];
            flag = 1;
        } else {
            value += D_800BE974R[0];
            flag = 0;
            if (start >= end)
                flag = value >= start;
        }
    } else {
        flag = 0;
        if (start >= end)
            flag = value >= start;
    }
    if (flag == 0)
        return 0;
    *(s16 *)(object + 0x288) = 1;
    ahead = *(s16 *)(object + 0x282);
    pace = *(s32 *)(object + 0x29C);
    if (RandomScaledGet(5) < 0) {
        x = ahead - RandomScaledGet(5);
        *(s32 *)(object + 0x29C) = pace - 2 + x;
    } else {
        x = ahead + RandomScaledGet(5);
        *(s32 *)(object + 0x29C) = pace - 2 + x;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/cd", func_8003E78C);
#endif

void func_8003EA94(u8 *object, s32 *arg1, s32 arg2) {
    s32 *entries;
    s32 count;
    s32 value;
    s32 pad[2];
    s32 i;
    i = 0;
    entries = arg1;
    count = ((*((s16 *)(object + 2))) - (*((s16 *)(object + 0)))) + 1;
    value = (*((s32 *)(object + 8))) + arg2;
    *((s32 *)(object + 8)) = value;
    if (count <= 0) {
        goto done;
    }
    entries += 3;
again:
    *entries += arg2;

    entries += 5;
    i++;
    if (i < count) {
        goto again;
    }
done:
    (void)(&pad);
}

void func_8003EAE8(u8 *object, s32 index) {
    s32 pad[4];
    u8 *group;
    u8 *entry;
    s32 count;
    s32 total;
    s32 *base;
    s32 *ptr;
    s32 i;

    group = *(u8 **)(object + 0x370);
    entry = *(u8 **)(group + 0x150);
    entry += index * 0x18;
    count = *(s32 *)(entry + 8);
    if (count > 0) {
        {
            s32 low;
            s32 *table;

            low = *(s16 *)(entry + 0);
            table = *(s32 **)(group + 0x124);
            i = 0;
            *(s32 *)(entry + 8) = count + 0xE;
            {
                s32 high;

                high = *(s16 *)(entry + 2);
                base = (s32 *)(low * 20 + (u32)table);
                total = high - low + 1;
            }
        }
        if (total > 0) {
            ptr = base + 3;
            do {
                *ptr += 0xE;
                ptr += 5;
                i++;
            } while (i < total);
        }
    } else {
        {
            s32 low;
            s32 *table;

            low = *(s16 *)(entry + 0);
            table = *(s32 **)(group + 0x124);
            i = 0;
            *(s32 *)(entry + 8) = count - 0xE;
            {
                s32 high;

                high = *(s16 *)(entry + 2);
                base = (s32 *)(low * 20 + (u32)table);
                total = high - low + 1;
            }
        }
        if (total > 0) {
            ptr = base + 3;
            do {
                *ptr -= 0xE;
                ptr += 5;
                i++;
            } while (i < total);
        }
    }
}

void func_8003EBD0(u8 *object, s32 index) {
    u8 *group;
    u8 *entry;
    s32 count;
    s32 total;
    s32 *base;
    s32 *ptr;
    s32 i;
    volatile s32 pad[4];

    group = *(u8 **)(object + 0x370);
    entry = *(u8 **)(group + 0x150);
    entry += index * 0x18;
    count = *(s32 *)(entry + 8);
    if (count > 0) {
        {
            s32 low;
            s32 *table;

            low = *(s16 *)(entry + 0);
            table = *(s32 **)(group + 0x124);
            i = 0;
            *(s32 *)(entry + 8) = count - 0xE;
            base = (s32 *)(low * 0x14 + (u32)table);
            total = *(s16 *)(entry + 2) - low + 1;
        }
        if (total > 0) {
            ptr = base + 3;
            do {
                *ptr -= 0xE;
                ptr += 5;
                i++;
            } while (i < total);
        }
    } else {
        {
            s32 low;
            s32 *table;

            low = *(s16 *)(entry + 0);
            table = *(s32 **)(group + 0x124);
            i = 0;
            *(s32 *)(entry + 8) = count + 0xE;
            base = (s32 *)(low * 0x14 + (u32)table);
            total = *(s16 *)(entry + 2) - low + 1;
        }
        if (total > 0) {
            ptr = base + 3;
            do {
                *ptr += 0xE;
                ptr += 5;
                i++;
            } while (i < total);
        }
    }
}

extern u8 D_800A387C[];
extern s32 D_800AE84C[];

/* The two pins put base and the src walker in retail's registers. The
 * opaque dst copy keeps cse from copying it out of src, and the explicit
 * `adjust` local keeps the D_800AE84C address ahead of the walker copies. */
void func_8003ECB8(u8 *object) {
    u8 *current;
    register u8 *base asm("$11");
    s32 id;
    s32 depth;
    s32 i;
    s32 value;
    s32 sum;
    s32 moved;
    s32 extra;
    u16 u16v;
    u8 *row;
    register u8 *src asm("$8");
    u8 *dst;

    current = *(u8 **)(D_800A387C - 4);
    base = D_800BE97C[0];
    if (current != 0) {
        id = *(s16 *)(object + 0xC) - 1;
        for (; current != 0; current = *(u8 **)(current + 0x3E0)) {
            if (*(s16 *)(current + 0x1DE) == id) {
                break;
            }
        }
        if (current != 0 && *(s16 *)(current + 0x1EC) != 1 &&
            *(u8 *)(current + 0x268) != 0) {
            depth = *(s16 *)(current + 0x27C);
            i = 0;
            if (i < *(s16 *)(object + 0xA)) {
                s32 *adjust;

                adjust = D_800AE84C;
                src = object;
                asm("" : "=r"(dst) : "0"(object));
                do {
                    current = src;
                    value = *(s16 *)(current + 0x94);
                    extra = *(s32 *)(object + 0x218);
                    u16v = *(u16 *)(dst + 0x10);
                    row = (u8 *)((u32)(u16v << 3) + (u32)base);
                    sum = value + extra;
                    moved = sum - depth;
                    if (moved < 0) {
                        moved += 3;
                    }
                    *(s16 *)(row + 4) = (moved >> 2) - adjust[0];
                    src += 6;
                    dst += 2;
                    i++;
                } while (i < *(s16 *)(object + 0xA));
            }
        }
    }
}

extern s32 D_800A2F88;

extern s32 RandomScaledGet(s32 scale);

void func_8003EDA0(u8 *object) {
    s32 pace;
    s32 dist;
    s32 value;
    s32 delta;
    u8 adjustment;

    dist = D_800BE974[0] * D_800A2EA8[0] / D_800A2F88;
    value = (D_800A2EA8[0] + dist) / (dist + 1) + 1;
    *(s32 *)(object + 0x29C) = value;
    *(s16 *)(object + 0x282) = value;
    if (dist != 0) {
        adjustment = 2;
        pace = *(s32 *)(object + 0x29C);
        if (RandomScaledGet(5) < 0)
            delta = (pace - adjustment) - RandomScaledGet(5);
        else
            delta = (pace - adjustment) + RandomScaledGet(5);
        *(s32 *)(object + 0x29C) = delta;
    }
}

