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
#include "game.h"

extern void func_8001E7EC(void *, s32, s32);

extern s32 D_800A2EC0nm[] asm("D_800A2EC0.NON_MATCHING");
typedef struct ListNode28 ListNode28;
typedef struct DoublyLinkedNode {
    struct DoublyLinkedNode *next;
    struct DoublyLinkedNode *previous;
} DoublyLinkedNode;
extern void func_8001F2C4(s32 arg0, s32 arg1, s32 arg2);
extern void func_8001ED84(s32 *vec);
extern void (*D_80091080[])(void *);
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
extern void func_80029CB4(s32 *arg0);
extern void func_80039B74(s32 *arg0, s32 arg1);
s32 func_8003702C(u8 *, u8 *);
s32 func_8002CF24(u8 *, u8 *);
extern void HeapFree(void *ptr);
void *HeapAlloc(u32);
extern s32 D_800A359C[];
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
void func_80025454(s32);
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
void func_8001FAC0(u8 *, s32);
void func_8001FB28(u8 *, s32);
extern void func_80025594(u8 *);
void func_800390A0(s32, s32, s32, s32);
void FontDrawPaddedNumber(s32, s32, s32, s32);
void func_8003644C(s32, s32, s32, s32);
extern void FileRead();
extern s32 func_80029EF8(u8 *);
extern u8 D_800A2F95;
void SystemShowFatalError(char *message);
u32 MathSqrt(u32 value);
void RandomCountMark(void);
s32 RandomSeedGet(void);
void RandomSeedSet(s32 seed);
s32 RandomScaledGet(s32 scale);
void GraphicsAddPolyFT4(u8 *arg0);
void FontSetColor(s16 red, s16 green, s16 blue);
void FontDrawString(s8 *text, s32 x, s32 y, s32 scale);
void func_80018588(void *timeValue, s32 flags, s32 buffer);
void func_80018768(void *arg0, s32 x, s32 y, s32 scale);
void func_80018848(void *arg0, s32 arg1, s32 arg2);
void FontDrawPaddedNumber(s32 value, s32 x, s32 y, s32 scale);
void func_80018B18(s32 value, s32 x, s32 y, s32 scale);
void FontDrawNumber(s32 value, s32 x, s32 y, s32 scale);
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
void GraphicsLoadImageBank(s32 fileName);
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
void MatrixRotateVector(s32 *vec);
void func_8001F2C4(s32 arg0, s32 arg1, s32 arg2);
void func_8001F440(s32 arg0, s32 arg1, s32 arg2);
void func_8001F5BC(s32 arg0, s32 indexA, s32 indexB);
void func_8001F684(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8001F728(s32 arg0);
void func_8001F828(s32 *p);
void func_8001F874(s32 *arg0);
void MatrixStoreToObject(s32 *object);
void func_8001F90C(s32 arg0, s32 arg1, s32 arg2, s16 *arg3);
void MatrixSaveState(void);
void MatrixRestoreState(void);
void func_8001FAC0(u8 *arg0, s32 index);
void func_8001FB28(u8 *arg0, s32 index);
s32 func_8001FB80(void *arg0);
s32 VectorGetMagnitude3D(s32 x, s32 y, s32 z);
s32 VectorGetMagnitude2D(void *arg0);
void ReplayAllocBuffer(void);
void func_8001FD44(u8 *arg0);
s32 MathMultiplyFixed16(s32, s32); /* extern */
void func_8001FF3C(u8 *arg0, u8 *arg1);
void func_80022CA4(void);
void func_80022F48(void);
void func_80022F80(void);
void func_80022FB8(u8 *arg0, s32 arg1);
void CdApplyMixVolume(void);
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
void TextToUpper(u8 *string);
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
extern s32 gVabHead;
void SoundShutdown(void) {
    if (gSequenceId != -1)
        SsSeqClose(gSequenceId);
    if (gVabId != -1) {
        SsVabClose(gVabId);
        gVabId = -1;
    }
    if (gVabHead != 0) {
        HeapFree((void *)gVabHead);
        gVabHead = 0;
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

extern void *gVabBody;
void SoundFreeVabBody(void) {
    if (gVabBody != 0) {
        HeapFree(gVabBody);
        gVabBody = 0;
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
    gVabHead = 0;
    SoundLoadVab(arg0);
    D_800A3880 = 0;
}

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
    gVabHead = 0;
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
    gVabHead = (s32)func_8003FFF0((void *)(arg0 + 1), 0);
    value = (s32)func_8003FFF0((void *)arg0, 0x80140000);
    gVabBody = (void *)value;
    gVabId = SoundVabOpen(gVabHead, value);
}
#else
extern s16 gVabId;
extern void *gVabBody;
extern s32 gVabHead;
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
    gVabHead = func_8003FFF0((void *)(s32 *)arg0 + 1, 0);
    body = func_8003FFF0((void *)arg0, (void *)0x80140000);
    gVabBody = body;
    gVabId = SoundVabOpen((void *)gVabHead, (void *)body);
}
#endif

#ifdef NON_MATCHING
void SoundReloadVab(s32 arg0) {
    s32 value;

    func_8003FA0C();
    if (gVabId != -1)
        SsVabClose(gVabId);
    gVabHead = (s32)func_8003FFF0((void *)arg0, 0);
    value = (s32)func_8003FFF0((void *)(arg0 + 1), 0);
    gVabBody = (void *)value;
    gVabId = SoundVabOpen(gVabHead, value);
    if (gVabBody != 0) {
        HeapFree(gVabBody);
        gVabBody = 0;
    }
}
#else
extern s16 gVabId;
extern void *gVabBody;
extern s32 gVabHead;
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
    gVabHead = func_8003FFF0((void *)arg0, 0);
    body = func_8003FFF0((void *)(arg0 + 1), 0);
    gVabBody = body;
    gVabId = SoundVabOpen((void *)gVabHead, (void *)body);
    if (gVabBody != 0) {
        HeapFree((void *)gVabBody);
        gVabBody = 0;
    }
}
#endif

void func_80082B70(void);
void func_8003F23C(void) {
    func_80082B70();
}

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

void SoundSetReverbDepth(s32 arg0, s32 arg1) {
    SsUtSetReverbDepth((s16)((arg0 & 0xFF) * D_800A2F94 / 127),
                       (s16)((arg1 & 0xFF) * D_800A2F94 / 127));
}

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

s32 SoundIsSlotActive(s32 arg0) {
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

extern s16 D_800B9E26h[] asm("D_800B9E26");
extern s16 D_800B9E28[];
extern s16 D_800B9E2A[];
extern s16 D_800B9E2C[];
extern s16 D_800B9E2E[];
extern u8 D_80098BF8[];
extern u8 D_80098BEC[];
extern s8 func_8003F914Body(s32) asm("func_8003F914");

/*
 * func_8003F564(id, type) starts sound `type` on voice slot `id` (**guess**).
 * It frees the slot first, picks the VAB program, tone and note from `type`,
 * keys the voice on and records the result in the D_800B9E24 table (six
 * halfwords per slot: voice, type, tone, note, note, 0). The key-status
 * test is an inline helper in the original, and its u8 result is why retail
 * has an `andi` after it.
 */
static inline u8 SoundIsVoiceOn(s32 voice) {
    s32 status;

    status = SpuGetKeyStatus(1 << voice);
    if (status != 1 && status == 0) {
        return 0;
    }
    return 1;
}

void func_8003F564(id, type) s8 id;
s8 type;
{
    u8 tone;
    u8 prog;
    u8 note;
    u8 vol;
    u8 fixedVol;
    u8 i;
    s32 v;
    s32 off;
    s32 row;
    s16 voice;

    tone = 0;
    if (type == 0x20) {
        return;
    }
    voice = D_800B9E24[(s8)id * 6];
    if (voice != -1) {
        if (SoundIsVoiceOn(voice)) {
            tone = func_8003F914Body((s8)id);
        }
    }
    if ((s8)tone == -1) {
        return;
    }
    vol = D_800A2F94;
    if (D_800A3880 != 0) {
        v = (s8)type;
        if (v == 7) {
            prog = 0xF;
            tone = 0;
            note = 0x37;
        } else if (v == 8) {
            prog = 1;
            tone = 0;
            note = 0x30;
            vol = 0x7F;
        } else {
            prog = 0;
            tone = type;
            note = D_80098BF8[(u8)type];
            vol = 0x64;
        }
    } else {
        v = (s8)type;
        if (v >= 0x40) {
            prog = 0xA;
            tone = type - 0x40;
            if (v == 0x42) {
                note = 0x30;
            } else {
                note = 0x2E;
            }
        } else if (v >= 0x20) {
            note = 0x3C;
            if (v >= 0x2C) {
                switch (v) {
                case 0x2C:
                    prog = 0x24;
                    break;
                case 0x2D:
                    prog = 0x26;
                    break;
                case 0x29:
                    prog = 0x29;
                    break;
                default:
                    break;
                }
                tone = 1;
                prog -= 0x20;
            } else if (v >= 0x2A) {
                switch (v) {
                case 0x2A:
                    prog = 0x12;
                    break;
                case 0x2B:
                    prog = 0x13;
                    break;
                default:
                    break;
                }
                tone = 0;
            } else {
                prog = type - 0x20;
                tone = 0;
                if (v == 0x28) {
                    note = 0x2E;
                }
            }
        } else {
            if ((u8)(type - 0xC) < 4) {
                prog = 0x1A - type;
                tone = 0;
            } else {
                fixedVol = (u8)(type - 9) < 3;
                prog = 0xF;
                tone = type;
                if (fixedVol) {
                    vol = 0x64;
                }
            }
            note = D_80098BEC[tone];
        }
    }
    voice = D_800B9E24[(s8)id * 6] =
        SsUtKeyOnV((s8)id, gVabId, prog, tone, note, 0, vol, vol);
    if (voice == -1) {
        return;
    }
    for (i = 0; i < 24; i++) {
        if (i != id) {
            row = i * 12;
            if (*(s16 *)((u8 *)D_800B9E24 + row) == voice) {
                *(s16 *)((u8 *)D_800B9E24 + row) = -1;
            }
        }
    }
    off = (s8)id * 12;
    SsUtSetVVol(*(s16 *)((u8 *)D_800B9E24 + off), vol, vol);
    *(s16 *)((u8 *)D_800B9E28 + off) = tone;
    *(s16 *)((u8 *)D_800B9E26h + off) = type;
    *(s16 *)((u8 *)D_800B9E2A + off) = note;
    *(s16 *)((u8 *)D_800B9E2C + off) = note;
    *(s16 *)((u8 *)D_800B9E2E + off) = 0;
}

extern s8 SsUtKeyOffV(s16);

/*
 * game.h declares func_8003F914 as void, and callers must keep it that way.
 * Retail tests the caller's leftover $v0 on entry: ret is never set.
 */
s8 func_8003F914Body(s32 arg0) asm("func_8003F914");
s8 func_8003F914Body(s32 arg0) {
    s8 ret;
    s32 off;
    s8 key;
    s32 noVoice;
    s32 mask;
    s32 status;
    s16 voice;

    if (ret != 0x20) {
        off = (s8)arg0 * 12;
        voice = *(s16 *)((u8 *)D_800B9E24 + off);
        noVoice = -1;
        if (voice == noVoice) {
            return 0;
        }
        key = SsUtKeyOffV(voice);
        if (key == noVoice) {
            do {
                voice = *(s16 *)((u8 *)D_800B9E24 + off);
                if (voice == key) {
                    goto done;
                }
            } while (0);
            mask = 1 << voice;
            status = SpuGetKeyStatus(mask);
            if (status == 2) {
                VSync(0);
                SpuGetKeyStatus(mask);
                key = 0;
            } else if (status != 0) {
                goto done;
            } else {
                key = 0;
            }
        }
        *(s16 *)((u8 *)D_800B9E24 + off) = -1;
    done:
        return key;
    }
}

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

void SoundSetSlotVolume(s8 arg0, s32 arg1, s32 arg2) {
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

extern const char gSsVabOpenHeadFailedMessage[];
extern const char gSsVabTransBodyFailedMessage[];

s16 SoundVabOpen(void *arg0, void *arg1) {
    s16 vabId;
    s16 result;

    vabId = SsVabOpenHead(arg0, -1);
    if (vabId == -1) {
        SystemShowFatalError(gSsVabOpenHeadFailedMessage);
    } else {
        result = SsVabTransBody(arg1, vabId);
        if (result == vabId) {
            SsVabTransCompleted(1);
            return result;
        }
        SystemShowFatalError(gSsVabTransBodyFailedMessage);
    }
    return -1;
}

/* Loads a whole file into arg1, or into a page-rounded HeapAlloc block when
 * arg1 is NULL. D_800A2F98 is the "rb" mode string for FileOpen. Assigning
 * buffer in both arms keeps the allocation in arg1's register and keeps the
 * first guard's branch on the second test.
 */
static const char sSoundOpenError[] = "unable to open sound file";
static const char sSoundMemoryError[] = "Insufficient memory to load sound";
extern char D_800A2F98[];

s32 func_8003FFF0(void *arg0, void *arg1) {
    void *buffer;
    void *handle;
    s32 padded;
    s32 size;

    handle = FileOpen(arg0, D_800A2F98);
    if (handle == NULL) {
        SystemShowFatalError(sSoundOpenError);
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
        SystemShowFatalError(sSoundMemoryError);
    }
    FileRead((s32)buffer, 1, size, handle);
    ((void (*)(s32))FileClose)((s32)handle);
    return (s32)buffer;
}

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
            SoundSetSlotVolume((s8)arg2, 0, 0);
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
        SoundSetSlotVolume((s8)arg2, 0, 0);
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
    SoundSetSlotVolume((s8)arg2, (u8)vol2, (u8)vol1);
}

extern u8 D_800A2F9D;
extern u8 *D_800A3554nm[] asm("D_800A3554.NON_MATCHING");

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
        SoundSetSlotVolume((s8)id, count1 & 0xFF, count2 & 0xFF);
    } else {
        func_8003F914((s8)id);
    }
    id++;
    if (count3 | count4) {
        func_8003F564((s8)id, 7);
        count3 = (count3 * 30 + 60) * vol >> 6;
        count4 = (count4 * 30 + 60) * vol >> 6;
        SoundSetSlotVolume((s8)id, count3 & 0xFF, count4 & 0xFF);
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
            SoundSetSlotVolume((s8)i, 0, 0);
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
            SoundSetSlotVolume((s8)id, decayVolume, decayVolume);
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
                SoundSetSlotVolume(0, volume & 0xFF, volume & 0xFF);
            } else {
                if (*(s16 *)(D_800A3554[0] + 0x3BA) >= 125 && pitch >= 125) {
                    pitch = 120;
                }
                SoundSetSlotVolume(1, volume & 0xFF, volume & 0xFF);
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

extern u8 D_800A2FA8;

void func_80041328(void) {
    if (D_800A2F9D == 0) {
        SoundSetSlotVolume(0, 0, 0);
        if (D_800A2EA4[0] == 2) {
            SoundSetSlotVolume(1, 0, 0);
        }
    } else if (D_800A2FA8 == 0) {
        D_800A2FA8 = 1;
        SoundSetSlotVolume(0, 0x38, 0x38);
        if (D_800A2EA4[0] == 2) {
            SoundSetSlotVolume(1, 0x38, 0x38);
        }
    }
}

void func_800413C0(void) {
    s32 i;
    if (D_800A2FA8) {
        D_800A2FA8 = 0;
        for (i = 0; i < 5; i++)
            SoundSetSlotVolume((s8)i, 0, 0);
    }
}

void func_80041414(void) {
    extern u8 D_800A2F9C;
    D_800A2F9C = !D_800A2F9C;
}

void func_8004142C(void) {
    D_800A2F9D = D_800A2F9D == 0;
}

void func_80041444(s32 arg0) {
    s32 i;

    for (i = 0; i < 0x14; i++) {
        SoundSetSlotVolume((s8)i, 0, 0);
    }
    if ((arg0 & 0xFF) != 0) {
        SoundSetSlotVolume(0x14, 0, 0);
        SoundSetSlotVolume(0x15, 0, 0);
    }
    SoundSetSlotVolume(0x16, 0, 0);
    SoundSetSlotVolume(0x17, 0, 0);
}

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
    SoundSetSlotVolume((s8)arg1, 0x72, 0x72);
}

void func_80041564(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 D_800A397C[];
    extern u8 D_800A38B0[];
    extern s32 D_800A2E90[];
    extern u8 D_800A2EE0[];
    extern s32 D_800BE86C[];
    extern void func_80025594();
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
        SoundSetSlotVolume(0x12, 0xFF, 0xFF);
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
static const char sSoundPathIndy1[] = "snd/indy1";
static const char sSoundPathIndy2[] = "snd/indy2";
static const char sSoundPathIndy3[] = "snd/indy3";
/* Retail has one zero word here: the jump table that follows is 8-byte
 * aligned within its object. No code reads it. */
asm(".rdata\n.long 0\n.text");
extern u8 D_80098BEC[];
extern u8 D_80098BED[];
extern u8 D_80098BEE[];
extern s32 D_800BE8A8[];
extern s32 D_800A2FA0;
extern s32 D_800A2EB8NM[] asm("D_800A2EB8.NON_MATCHING");

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
            msg = (s32)sSoundPathIndy1;
            break;
        case 1:
            msg = (s32)sSoundPathIndy2;
            break;
        case 2:
            msg = (s32)sSoundPathIndy3;
            break;
        default:
            return;
        }
        func_8003F060(msg);
    } else {
        func_8003F060(0x3E);
    }
}

void func_8004195C(void) {
    SsStart2();
    func_8003F284();
    func_8003F564(0, 0);
    SoundSetSlotVolume(0, 0, 0);
    VSync(0);
    VSync(0);
    VSync(0);
    func_8003F564(1, 0xC);
    SoundSetSlotVolume(1, 0, 0);
    func_8003F564(2, 0xD);
    SoundSetSlotVolume(2, 0, 0);
    func_8003F564(3, 0xE);
    SoundSetSlotVolume(3, 0, 0);
    func_8003F564(4, 0xF);
    SoundSetSlotVolume(4, 0, 0);
}

extern void SsSetMute(s32);

void func_80041A28(void) {
    s32 i;

    i = 0;
    do {
        SoundSetSlotVolume((s8)i, 0, 0);
        i++;
    } while (i < 5);
    SoundSetReverbDepth(0, 0);
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
