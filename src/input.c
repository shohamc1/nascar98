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
s32 TrackFindSection(s32, s32, s32 *, s32 *, s32 *);
void ReplayStepForward(void);
s32 TrackTestPointInSection(s32, s32, u8 *);
s32 TrackTestPointInSection(s32, s32, u8 *);
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
s32 CarTestDraft(u8 *, u8 *);
void *HeapAlloc(u32);
void CarPlaceOnStartingGrid(void);
void func_80041A28(void);
void exit();
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
void CameraUpdateHorizon(void);
void func_80035274(void);
void func_8002F0A8(u8 *);
void CameraUpdateHorizon(void);
void func_80035720(u_long *);
void func_8001FAC0(u8 *, s32);
void func_8001FB28(u8 *, s32);
extern void func_80025594(u8 *);
void func_800390A0(s32, s32, s32, s32);
void FontDrawPaddedNumber(s32, s32, s32, s32);
void func_8003644C(s32, s32, s32, s32);
extern u8 *gCarListnm[] asm("gCarList.NON_MATCHING");
extern s32 func_80029EF8(u8 *);
extern s16 SoundVabOpen(void *, void *);
void func_80082B70(void);
extern void SsSeqSetVol(short seqAccessNum, short leftVolume,
                        short rightVolume);
extern void func_8001F90C(s32, s32, s32, s16 *);
void func_80041AF0();
void SystemShowFatalError(char *message);
u32 MathSqrt(u32 value);
void RandomCountMark(void);
s32 RandomSeedGet(void);
void RandomSeedSet(s32 seed);
s32 RandomScaledGet(s32 scale);
void GraphicsAddPolyFT4(u8 *arg0);
void FontSetColor(s16 red, s16 green, s16 blue);
void FontDrawString(s8 *text, s32 x, s32 y, s32 scale);
void TextFormatTime(void *timeValue, s32 flags, s32 buffer);
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
void ReplayStepBack(void);
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
void SoundStart(void);
void SoundShutdown(void);
void SoundEnd(void);
void func_8003EFC8(void);
void SoundFreeVabBody(void);
void SoundInitTables(void);
void func_8003F060(s32 arg0);
void func_8003F0CC(s32 arg0);
void SoundLoadVab(s32 arg0);
void SoundReloadVab(s32 arg0);
void func_8003F23C(void);
void func_8003F25C(void);
void func_8003F284(void);
void SoundSetReverbDepth(s32 arg0, s32 arg1);
void SoundOpenSequence(void);
void SoundSetSequenceLoop(s8 loopCount);
void SoundPauseSequence(void);
void SoundPlaySequence(s8 playCount, u8 playMode);
void SoundReplaySequence(void);
void SoundSetSequenceVolume(u8 leftVolume, u8 rightVolume);
void SoundStopSequence(void);
s32 SoundIsSlotActive(s32 arg0);
void func_8003FA0C(void);
void func_8003FEB8(void);
s16 SoundVabOpen(void *arg0, void *arg1);
s32 FileLoadBlock(void *arg0, void *arg1);
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

extern u16 D_8008CA04U16[] asm("D_8008CA04");
s32 PadGetButtons(s32 index) {
    return D_8008CA04U16[index * 4];
}

u16 func_80041B94(s32 index) {
    return D_8008CA04U16[index];
}

/* Wall: retail computes the nibble before the 0xFF branch and keeps it
 * in a0 with a final move v0,a0 on both paths; our shapes either go
 * branchless (xori/sltu/negu) or compute after the branch. */
u32 PadGetType(s32 arg0) {
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

/* Retail keeps an empty 8-byte frame; `framePad` reproduces it. The `u16 mode`
 * keeps the nor result and the or-accumulator in separate registers, and the
 * 0x3C8 store sits in both arms so jump2 cross-jumps only the final sb. */
u16 PadReadObjectState(u8 *arg0) {
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
    if (((s8 *)gPadType)[bank] == 2) {
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

extern u8 gPadTypeSmall;
extern u8 D_800A3A26[];
extern u8 D_800A3A27[];
extern u32 D_8008CA2C[];
extern u32 D_8008CA30[];
extern u32 D_8008CA34[];
extern u32 D_8008CA38[];
extern u32 D_8008CA3C[];
extern u32 D_8008CA40[];
extern u32 D_8008CA44[];
extern u32 D_8008CA48[];

void PadRefreshTypes(void) {
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
    gPadTypeSmall = padType;
    padWord = D_800B9E00[0];
    do {
        padType = padWord & 0xF000;
        if ((padWord & 0xFF) == noPad) {
            padType = 0;
        } else {
            padType = padType >> 12;
        }
    } while (0);
    node = gCarListnm[0];
    D_800A3A25[0] = padType;
    D_800A3A26[0] = 0;
    D_800A3A27[0] = 0;
    if (node != 0) {
        do {
            if (*(s16 *)(node + 0x1EC) == 0) {
                node[0x3C4] = ((u8 *)gPadType)[*(s8 *)(node + 0x20B)];
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

void func_80041F54(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 *w;
    u16 hs;
    u16 swap;
    u16 out;
    u32 word;
    u32 w2;
    s32 j;
    s32 i;
    s32 type;
    s32 b1;
    s32 b2;
    s32 b3;
    u32 mask2;
    u32 mask3;

    w = arg0;
    for (j = 7; j >= 0; j--) {
        arg1[j] = 0;
    }
    arg1[1] = w[1];
    arg1[3] = w[4];
    mask2 = 0xFF0000;
    mask3 = 0xFF000000;
    for (i = 0; i < 2; i++) {
        word = *w;
        w2 = *(u32 *)((u16 *)w + 2);
        hs = ((u16 *)w)[1];
        swap = ~(((hs & 0xFF) << 8) | (hs >> 8));
        ((s8 *)gPadType)[i] = (word & 0xF000) >> 12;
        out = swap;
        if ((word & 0xFF) == 0xFF) {
            ((s8 *)gPadType)[i] = 0;
        }
        type = ((s8 *)gPadType)[i];
        if (type == 2) {
            b1 = (w2 & 0xFF00) >> 8;
            b2 = (w2 & mask2) >> 16;
            b3 = (w2 & mask3) >> 24;
            if (b3 > 0x80) {
                out = swap | 4;
            }
            if (b1 > 0x40) {
                out |= 0x40;
            }
            if (b2 > 0x40) {
                out |= 0x80;
            }
        } else if (type >= 5) {
            if (type == 5) {
                if (swap & 8) {
                    out = (swap & 0xFFF7) | 0x10;
                } else if (swap & 4) {
                    out = (swap & 0xFFFB) | 0x80;
                } else if (swap & 0x10) {
                    out = (swap & 0xFFEF) | 8;
                } else if (swap & 0x80) {
                    out = (swap & 0xFF7F) | 2;
                } else if (swap & 2) {
                    out = (swap & 0xFFFD) | 4;
                }
            }
        } else if (type != 4) {
            out = 0;
        }
        *arg1 = out;
        w += 3;
        arg1 += 2;
    }
}

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
    mode = (u8 *)gPadType;
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

typedef struct BoxCorner {
    s16 sx, sy, sz, pad;
    s32 vx, vy, vz;
} BoxCorner;
extern BoxCorner D_800B1FF0[8];

void CarInitTumble(u8 *obj) {
    s32 i;
    register s32 height asm("t1");
    s16 y;
    register BoxCorner *c asm("a1");
    register s32 *pvx asm("t0");
    register s32 *pvz asm("a3");
    register BoxCorner *cb asm("v0");
    s32 *vxb;
    s32 *vzb;

    *(s16 *)(obj + 0x398) =
        ABS(*(s16 *)(obj + 0x104) - *(s16 *)(obj + 0x114) + 0x400) & 0x3FF;
    *(s16 *)(obj + 0x388) = 0;
    *(s16 *)(obj + 0x38A) = 0;
    *(s16 *)(obj + 0x39A) = *(u16 *)(obj + 0xFE) + 4;
    *(s16 *)(obj + 0x38C) = RandomScaledGet(0x20);
    if (*(s16 *)(obj + 0x38C) == 0) {
        *(s16 *)(obj + 0x38C) = 1;
    }
    *(s16 *)(obj + 0x38E) = ABS(RandomScaledGet(0x20));
    *(s16 *)(obj + 0x396) = 1;
    *(s16 *)(obj + 0x394) = ABS(RandomScaledGet(0x32)) + 0x4B;
    i = 0;
    cb = D_800B1FF0;
    vxb = &cb->vx;
    vzb = &cb->vz;
    height = *(s16 *)(*(u8 **)(obj + 0x370) + 0x26);
    pvx = vxb;
    c = cb;
    pvz = vzb;
    for (; i < 8; pvx += 5, c++, pvz += 5, i++) {
        /* Keep the byte-offset induction register ahead of the switch index. */
        asm("" : : "r"(i * 20));
        switch (i) {
        case 0:
        case 4:
            c->sz = *(u16 *)(*(u8 **)(obj + 0x370) + 0x1E);
            *pvz = c->sz;
            c->sx = *(u16 *)(*(u8 **)(obj + 0x370) + 0x20);
            *pvx = c->sx;
            y = (i / 4) * height;
            c->sy = y;
            break;
        case 1:
        case 5:
            c->sz = *(u16 *)(*(u8 **)(obj + 0x370) + 0x1E);
            *pvz = c->sz;
            c->sx = *(u16 *)(*(u8 **)(obj + 0x370) + 0x22);
            *pvx = c->sx;
            y = (i / 4) * height;
            c->sy = y;
            break;
        case 2:
        case 6:
            c->sz = *(u16 *)(*(u8 **)(obj + 0x370) + 0x1C);
            *pvz = c->sz;
            c->sx = *(u16 *)(*(u8 **)(obj + 0x370) + 0x22);
            *pvx = c->sx;
            y = (i / 4) * height;
            c->sy = y;
            break;
        case 3:
        case 7:
            c->sz = *(u16 *)(*(u8 **)(obj + 0x370) + 0x1C);
            *pvz = c->sz;
            c->sx = *(u16 *)(*(u8 **)(obj + 0x370) + 0x20);
            *pvx = c->sx;
            y = (i / 4) * height;
            c->sy = y;
            break;
        default:
            continue;
        }
        D_800B1FF0[i].vy = y;
    }
}

extern s32 D_800A3A2CAbsolute[];
extern s32 D_800A3A34Absolute[];
extern void EffectSpawnAtCarPoint(u8 *, s32);
extern void func_80043B68(u8 *, s32);

void CarCheckGroundContact(u8 *obj) {
    s32 i;
    s32 best;
    s32 bestIdx;
    s32 t;
    s32 x;
    s32 z;
    s32 idxA;
    s32 idxB;
    s32 idxC;
    BoxCorner *c;
    s32 *sinTab;
    s32 *cosTab;

    best = 0x7FFF;
    bestIdx = 0;
    sinTab = *(s32 **)D_800A3A2CAbsolute;
    cosTab = *(s32 **)D_800A3A34Absolute;
    idxA = *(s16 *)(obj + 0x388);
    idxB = *(s16 *)(obj + 0x38A);
    c = D_800B1FF0;
    for (i = 0; i < 8; c++, i++) {
        z = c->vz;
        c->sx = c->vx;
        c->sy = c->vy;
        t = (sinTab[idxA] * c->sx - cosTab[idxA] * c->sy) >> 16;
        x = (cosTab[idxA] * c->sx + sinTab[idxA] * c->sy) >> 16;
        c->sz = (sinTab[idxB] * z - cosTab[idxB] * x) >> 16;
        c->sy = (cosTab[idxB] * z + sinTab[idxB] * x) >> 16;
        c->sx = t;
        idxC = *(s16 *)(obj + 0x398);
        z = ((sinTab[idxC] * c->sz - cosTab[idxC] * t) >> 16) + *(s32 *)obj;
        c->sx = ((cosTab[idxC] * c->sz + sinTab[idxC] * t) >> 16) +
                *(s32 *)(obj + 4);
        c->sz = z;
        if (c->sy < best) {
            best = c->sy;
            bestIdx = i;
        }
    }
    if (best <= 0 && -best >= *(s16 *)(obj + 0x39A)) {
        *(s16 *)(obj + 0x39A) = -best;
        *(s16 *)(obj + 0x1C0) = 0;
        *(u16 *)(obj + 0x396) |= 8;
        if (RandomScaledGet(3) < 0) {
            t = -RandomScaledGet(3);
        } else {
            t = RandomScaledGet(3);
        }
        if (ABS(*(s16 *)(obj + 0x394)) < 0x3C) {
            t += 2;
        }
        switch (bestIdx % 4) {
        case 3:
            if (t == 0) {
                EffectSpawnAtCarPoint(obj, 0);
            }
            if (t < 3) {
                EffectSpawnAtCarPoint(obj, 5);
            }
            func_80043B68(obj, 0);
            break;
        case 2:
            if (t == 0) {
                EffectSpawnAtCarPoint(obj, 1);
            }
            if (t < 3) {
                EffectSpawnAtCarPoint(obj, 6);
            }
            func_80043B68(obj, 1);
            break;
        case 1:
            if (t == 0) {
                EffectSpawnAtCarPoint(obj, 2);
            }
            if (t < 3) {
                EffectSpawnAtCarPoint(obj, 7);
            }
            func_80043B68(obj, 2);
            break;
        case 0:
            if (t == 0) {
                EffectSpawnAtCarPoint(obj, 3);
            }
            if (t < 3) {
                EffectSpawnAtCarPoint(obj, 7);
            }
            func_80043B68(obj, 3);
            break;
        }
    } else {
        *(s16 *)(obj + 0x1C0) = -1;
        *(u16 *)(obj + 0x396) &= ~8;
    }
    for (i = 0; i < 4; i++) {
        *(u16 *)(obj + 0x2AC + i * 0x28) = *(u16 *)(obj + 0x39A);
        *(u16 *)(obj + 0x2B0 + i * 0x28) = 0;
    }
}

extern s32 D_800A3A34Absolute2[];
extern s32 D_800A3A34Small[];

void CarUpdateTumble(u8 *obj) {
    s32 heading;
    s32 t;
    s32 i;
    s16 r;
    s32 d;

    CarCheckGroundContact(obj);
    if (!(*(u16 *)(obj + 0x396) & 8)) {
        *(s16 *)(obj + 0x39A) += *(s16 *)(obj + 0x394);
        *(s16 *)(obj + 0x394) -= 8;
        *(s32 *)(obj + 0x90) -= 0x8000;
        if (*(s32 *)(obj + 0x90) < 0) {
            *(s32 *)(obj + 0x90) = 0;
        }
    } else {
        if (*(s32 *)(obj + 0x90) < 0x320000 ||
            ABS(*(s16 *)(obj + 0x394)) < 0x14) {
            if (*(u16 *)(obj + 0x396) & 1) {
                *(u16 *)(obj + 0x396) = (*(u16 *)(obj + 0x396) & ~1) | 2;
            }
        }
        *(s16 *)(obj + 0x394) = -*(s16 *)(obj + 0x394) / 2 - 10;
        *(s16 *)(obj + 0x39A) += *(s16 *)(obj + 0x394);
        if (*(u16 *)(obj + 0x396) & 1) {
            r = *(s16 *)(obj + 0x388) % 512;
            heading = *(s16 *)(obj + 0x398);
            t = MathMultiplyFixed16((*(s32 **)D_800A3A34Absolute)[r],
                                    *(s32 *)(obj + 0x90) / 3);
            t = MathMultiplyFixed16((*(s32 **)D_800A3A34Absolute2)[heading], t);
            *(s16 *)(obj + 0x38C) = t >> 16;
            if (*(u16 *)(obj + 0x38A) > 0x100 &&
                *(u16 *)(obj + 0x38A) < 0x300) {
                *(s16 *)(obj + 0x38C) = -*(s16 *)(obj + 0x38C);
            }
            r = *(s16 *)(obj + 0x38A) % 512;
            t = MathMultiplyFixed16((*(s32 **)D_800A3A34Small)[r],
                                    *(s32 *)(obj + 0x90) / 3);
            t = MathMultiplyFixed16((*(s32 **)D_800A3A2CAbsolute)[heading], t);
            *(s16 *)(obj + 0x38E) = t >> 16;
            *(s32 *)(obj + 0x90) = *(s32 *)(obj + 0x90) * 9 / 10;
            if (*(s32 *)(obj + 0x90) < 0) {
                *(s32 *)(obj + 0x90) = 0;
            }
        }
    }
    if (*(u16 *)(obj + 0x396) & 3) {
        *(u16 *)(obj + 0x388) =
            (*(u16 *)(obj + 0x388) + *(u16 *)(obj + 0x38C) + 0x400) & 0x3FF;
        *(u16 *)(obj + 0x38A) =
            (*(u16 *)(obj + 0x38A) + *(u16 *)(obj + 0x38E) + 0x400) & 0x3FF;
        if (*(u16 *)(obj + 0x396) & 8) {
            func_800414E0(obj, 6, 1);
        }
    }
    if (*(u16 *)(obj + 0x396) & 2) {
        r = *(u16 *)(obj + 0x388) & 0x1FF;
        d = r - 0x100;
        if (d > 0x40 || (d > -0x40 && d < 0)) {
            *(s16 *)(obj + 0x390) = *(u16 *)(obj + 0x388) - r + 0x200;
            *(s16 *)(obj + 0x38C) = 1;
        } else {
            *(s16 *)(obj + 0x390) = *(u16 *)(obj + 0x388) - r;
            *(s16 *)(obj + 0x38C) = -1;
        }
        r = *(u16 *)(obj + 0x38A) & 0x1FF;
        if (r > 0x100) {
            *(s16 *)(obj + 0x392) = *(u16 *)(obj + 0x38A) - r + 0x200;
            *(s16 *)(obj + 0x38E) = 1;
        } else {
            *(s16 *)(obj + 0x392) = *(u16 *)(obj + 0x38A) - r;
            *(s16 *)(obj + 0x38E) = -1;
        }
        *(u16 *)(obj + 0x396) = (*(u16 *)(obj + 0x396) & ~2) | 4;
    }
    if (*(u16 *)(obj + 0x396) & 4) {
        *(s16 *)(obj + 0x388) += *(s16 *)(obj + 0x38C) / 2;
        if ((*(s16 *)(obj + 0x38C) > 0 &&
             *(s16 *)(obj + 0x388) >= *(s16 *)(obj + 0x390)) ||
            (*(s16 *)(obj + 0x38C) <= 0 &&
             *(s16 *)(obj + 0x388) <= *(s16 *)(obj + 0x390))) {
            *(s16 *)(obj + 0x38C) = 0;
            *(s16 *)(obj + 0x388) = *(s16 *)(obj + 0x390) & 0x3FF;
        } else if (*(s16 *)(obj + 0x38C) > 0) {
            *(s16 *)(obj + 0x38C) += 1;
        } else {
            *(s16 *)(obj + 0x38C) -= 1;
        }
        *(s16 *)(obj + 0x38A) += *(s16 *)(obj + 0x38E) / 2;
        if ((*(s16 *)(obj + 0x38E) > 0 &&
             *(s16 *)(obj + 0x38A) >= *(s16 *)(obj + 0x392)) ||
            (*(s16 *)(obj + 0x38E) <= 0 &&
             *(s16 *)(obj + 0x38A) <= *(s16 *)(obj + 0x392))) {
            *(s16 *)(obj + 0x38E) = 0;
            *(s16 *)(obj + 0x38A) = *(s16 *)(obj + 0x392) & 0x3FF;
        } else if (*(s16 *)(obj + 0x38E) > 0) {
            *(s16 *)(obj + 0x38E) += 1;
        } else {
            *(s16 *)(obj + 0x38E) -= 1;
        }
        d = *(s16 *)(obj + 0x390) & 0x3FF;
        heading = *(s16 *)(obj + 0x392) & 0x3FF;
        if (*(s16 *)(obj + 0x388) == d && *(s16 *)(obj + 0x38A) == heading) {
            if (!D_800A2EDC[0] || d + heading == 0 ||
                *(s16 *)(obj + 0x1EC) == 1) {
                *(s16 *)(obj + 0x1BC) = 3;
                for (i = 0; i < 4; i++) {
                    *(s16 *)(obj + 0x2B0 + i * 0x28) =
                        *(s16 *)(obj + 0x394) / 2;
                }
                return;
            }
            if (*(s16 *)(obj + 0x1BC) != 4) {
                *(u8 *)(obj + 0x3B7) = 0x14;
            }
            *(s16 *)(obj + 0x1BC) = 4;
        }
    }
    func_8002AD20((s32 *)obj, *(s16 *)(obj + 0x104));
}
