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
s32 func_80024E90(s32, s32, s32 *, s32 *, s32 *);
extern u8 *D_800A3878w15[] asm("D_800A3878.NON_MATCHING");
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
void *HeapAlloc(u32);
extern s32 D_800A38AC[];
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
extern s32 func_80029EF8(u8 *);
extern s16 SoundVabOpen(void *, void *);
void func_80082B70(void);
extern void SsSeqSetVol(short seqAccessNum, short leftVolume,
                        short rightVolume);
extern void func_8001F90C(s32, s32, s32, s16 *);
void func_80041AF0();
void InitPAD(void *, s32, void *, s32);
s32 StartPAD(void);
s32 VSync(s32);
extern s32 gRandomSeed16;
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
s32 PadGetButtons(s32 index);
u16 func_80041B94(s32 index);
u32 PadGetType(s32 arg0);
void PadInitBuffers(void);
s32 func_80041D60(void);
void func_80041DEC(void);
void func_80042218(u16 *src, s32 *acc, u32 *dst);
s32 func_8004229C(s32 arg0);

/* Scene effects and random numbers. */

__inline__ u32 RandomGetScaled16(s32 arg0) {
    s32 value0;
    value0 = ((gRandomSeed16 * 0x6255) + 0x3619) & 0xFFFF;
    gRandomSeed16 = value0;
    value0 *= arg0;
    return (u32)value0 >> 0x10;
}

extern u8 D_800AD9CC[];
void func_80043D6C(void);
void func_80042EC0(void) {
    s32 offset;
    offset = 0x750;
    do {
        D_800AD9CC[offset] = 0;
        offset -= 0x30;
    } while (offset >= 0);
    func_80043D6C();
}

typedef struct EffectPoint {
    s32 unk0;
    s32 x;
    s32 y;
    s32 z;
    s32 unk10;
    s32 unk14;
} EffectPoint;

typedef struct EffectSlot {
    s32 x;
    s32 y;
    s32 z;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s8 active;
    u8 unk1D;
    u8 unk1E;
    u8 pad1F;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
} EffectSlot;

extern EffectSlot gEffectSlots[] asm("D_800AD9B0");

void func_80042EFC(u8 *object, s32 idx) {
    s32 i;
    s32 j;
    s32 twenty;
    s32 ninetysix;
    EffectPoint *table;
    EffectPoint *entry;

    for (i = 0, twenty = 20, ninetysix = 96; i < 5; i++) {
        for (j = 0; j < 0x28; j++) {
            if (gEffectSlots[j].active == 0) {
                break;
            }
        }
        if (j >= 0x28) {
            return;
        }
        table = *(EffectPoint **)(*(u8 **)(object + 0x370) + 0x40);
        gEffectSlots[j].active = 1;
        gEffectSlots[j].unk1D = 0xA;
        gEffectSlots[j].unk1E = *(u16 *)(object + 0x1DE);
        entry = &table[idx];
        gEffectSlots[j].x = *(s32 *)object + entry->x;
        gEffectSlots[j].y = *(s32 *)(object + 4) + entry->y;
        gEffectSlots[j].z = *(s32 *)(object + 8) + entry->z;
        gEffectSlots[j].unk1A = 0x1E;
        gEffectSlots[j].unk20 = gEffectSlots[j].unk24 =
            *(s16 *)(object + 0x1E0);
        if (idx < 5) {
            gEffectSlots[j].unkE = gEffectSlots[j].z;
        } else {
            gEffectSlots[j].unkE = *(s32 *)(object + 8) + 0xF;
        }
        gEffectSlots[j].unkC = 0;
        gEffectSlots[j].unk10 = RandomGetScaled16(twenty) + 0x1E;
        gEffectSlots[j].unk12 =
            (*(u16 *)(object + 0x114) + 0x400 + RandomGetScaled16(ninetysix)) &
            0x3FF;
        gEffectSlots[j].unk14 = (*(s32 *)(object + 0x90) * 7) / 8 >> 16;
        if (gEffectSlots[j].unk14 < 0x14) {
            gEffectSlots[j].unk14 = twenty;
        }
        gEffectSlots[j].unk28 = *(s32 *)(*(u8 **)(object + 0x370) + 0x38);
        gEffectSlots[j].unk2C =
            *(s32 *)(*(u8 **)(object + 0x370) + 0x40) + 0x90;
        /* ABS evaluates its argument twice: two LCG steps per field. */
        gEffectSlots[j].unk16 = ABS((s32)RandomGetScaled16(0x1000));
        gEffectSlots[j].unk18 = ABS((s32)RandomGetScaled16(0x1000));
    }
}

INCLUDE_ASM("asm/nonmatchings/effects", func_800432C0);

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void MulRotMatrix(MATRIX *matrix);
extern void func_800328AC(void *arg0, s32 arg1);
extern void func_80044BCC(s32 arg0);

void func_800436D0(u8 *object) {
    SVECTOR input;
    VECTOR trans;
    MATRIX matrix;
    long lvm[18];
    s32 *camera;
    u8 *node;
    s16 angle1;
    s16 angle2;

    PushMatrix();
    camera = (s32 *)D_800A38AC[0];
    input.vx = *(s32 *)(object + 0) - camera[0];
    input.vy = *(s32 *)(object + 4) - camera[1];
    input.vz = *(s32 *)(object + 8) - camera[2];
    RotTrans(&input, &trans, &lvm[16]);
    TransMatrix(&matrix, &trans);
    if (*(s8 *)(object + 0x1D) == 0xA) {
        input.vx = 0;
        input.vy = *(u16 *)(object + 0x18);
        input.vz = *(u16 *)(object + 0x16);
        RotMatrix(&input, &matrix);
        MulRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        SetRotMatrix(&matrix);
        func_80044BCC(*(s8 *)(object + 0x1E));
    } else {
        input.vx = 0;
        input.vy = 0;
        input.vz = *(u16 *)(object + 0x16);
        RotMatrix(&input, &matrix);
        MulRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        SetRotMatrix(&matrix);
        node = *(u8 **)(object + 0x2C);
        angle1 = *(s16 *)(node + 0x10);
        angle2 = *(s16 *)(node + 0x12);
        func_800328AC((void *)(*(u32 *)(object + 0x28) + angle1 * 44), angle2);
    }
    PopMatrix();
}

extern s32 pairTable4382C[] asm("D_800A3A2C");
extern s32 pairTable4382CA[] asm("D_800A3A34");
extern u8 D_800AD9B0p[] asm("D_800AD9B0");
extern s8 D_800AD9CCp[] asm("D_800AD9CC");
extern s32 D_800A38ACw38[] asm("D_800A38AC");
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u16 unkC;
    u8 pad0E[2];
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    u8 unk1C;
    s8 unk1D;
    u8 pad1E[6];
    s32 unk24;
} EffectRow30;
void func_8004382C(void) {
    EffectRow30 *fx;
    s32 i;
    s8 *flagPtr;
    s32 x;
    s32 y;
    s32 idx4;
    s32 dx;
    s32 dy;
    s32 ground;
    s32 f10v;
    s32 value;
    s32 f10;
    s32 oldSection;
    s32 scratch[6];

    flagPtr = D_800AD9CCp;
    for (i = 0; i < 0x28; i++) {
        if (flagPtr[i * 0x30] == 0) {
            continue;
        }
        fx = (EffectRow30 *)(D_800AD9B0p + i * 0x30);
        if (D_800A2ED4[0] == 0) {
            if ((s16)fx->unk1A-- < 0) {
                flagPtr[i * 0x30] = 0;
                continue;
            }
            x = *(volatile s32 *)fx;
            dx = x - ((s32 *)D_800A38AC[0])[0];
            if (dx < 0) {
                dx = ((s32 *)D_800A38AC[0])[0] - x;
            }
            if (dx >= 0x3E81) {
                continue;
            }
            y = *(volatile s32 *)((u8 *)fx + 4);
            dy = y - ((s32 *)D_800A38ACw38[0])[1];
            if (dy < 0) {
                dy = ((s32 *)D_800A38ACw38[0])[1] - y;
            }
            if (dy >= 0x3E81) {
                continue;
            }
            idx4 = (s16)fx->unk12 * 4;
            scratch[0] = fx->unk0;
            scratch[1] = fx->unk4;
            scratch[0] =
                scratch[0] +
                ((*(s32 *)(idx4 + pairTable4382C[0]) * (s16)fx->unk14) >> 16);
            scratch[1] =
                scratch[1] +
                ((*(s32 *)(idx4 + pairTable4382CA[0]) * (s16)fx->unk14) >> 16);
            oldSection = fx->unk24;
            if (func_80024E90(scratch[0], scratch[1], &fx->unk24, &scratch[2],
                              &scratch[4]) == -1) {
                fx->unk24 = oldSection;
                scratch[0] = fx->unk0;
                scratch[1] = fx->unk4;
                fx->unk14 = (s16)fx->unk14 * 2 / 3;
                fx->unk12 = (fx->unk12 + 0x200) & 0x3FF;
            }
            f10v = fx->unk10;
            *(volatile s32 *)&fx->unk0 = scratch[0];
            *(volatile s32 *)&fx->unk4 = scratch[1];
            ground = scratch[2] * 4 + (s16)fx->unkC;
            value = *(volatile u16 *)&fx->unkC + f10v;
            fx->unkC = value;
            fx->unk8 = ground;
            if ((s16)value <= 0) {
                fx->unkC = 0;
                f10 = -((s16)fx->unk10 * 2 / 3) - 2;
                fx->unk10 = f10;
                if ((s16)f10 < 0) {
                    fx->unk10 = 0;
                } else {
                    fx->unk14 = (s16)fx->unk14 * 3 / 4;
                }
                if (fx->unk1D >= 5) {
                    fx->unk14 = (s16)fx->unk14 * 3 / 4;
                }
            } else {
                fx->unk10 = fx->unk10 - 8;
            }
            if (fx->unk1D < 5) {
                fx->unk16 = (s16)fx->unk12 * 4;
            } else {
                fx->unk16 = (fx->unk16 + fx->unk14 * 4) & 0xFFF;
            }
            fx->unk18 = (fx->unk18 + 0x80) & 0xFFF;
        }
        func_800436D0((u8 *)fx);
    }
}

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u8 pad[14];
} FxVertex;

void func_80043B68(u8 *object, s32 idx) {
    u8 *fx;
    u8 *row;
    FxVertex *prim;
    s32 i;
    s32 limit;
    s32 start;
    u16 flags;
    s32 base;
    s32 dcheck;
    u8 *table;
    u8 *verts;

    fx = *(u8 **)(object + 0x370);
    if (*(s8 *)(object + 0x3B6) == 0) {
        return;
    }
    if (*(s8 *)(object + 0x200) == 4) {
        return;
    }
    row = object + idx;
    if ((s8)++row[0x3AE] >= 4) {
        row[0x3AE] = 3;
    }
    flags = *(u16 *)(object + 0x3A4);
    dcheck = D_800A2EB8[0];
    *(u16 *)(object + 0x3A4) = flags | 0x8000;
    if (dcheck == 0 && *(s8 *)(row + 0x3AE) == 3) {
        if (idx == 3) {
            *(u16 *)(object + 0x3A4) = flags | 0x8080;
        } else {
            *(u16 *)(object + 0x3A4) = flags | 0x8000 | (1 << (idx + 5));
        }
    }
    base = *(s16 *)(fx + 0x2E);
    table = *(u8 **)(fx + 0x40);
    if (idx >= 0) {
        base += idx;
    } else {
        base -= idx;
    }
    row = table + base * 24;
    start = *(s16 *)row;
    verts = *(u8 **)(fx + 0x14);
    limit = *(s16 *)(row + 2) - start + 1;
    prim = (FxVertex *)(verts + start * 20);
    for (i = 0; i < limit; i++) {
        prim->x += (u8)RandomGetScaled16(5);
        prim->y += (u8)RandomGetScaled16(5);
        prim->z += (u8)RandomGetScaled16(5);
        prim++;
    }
}

extern u8 D_800B1A24[];
extern u8 D_800B1A25[];
extern u8 D_800B1A26R[] asm("D_800B1A26.NON_MATCHING");

void func_80043D6C(void) {
    s32 base;
    s32 m3base;
    s32 m3;
    s32 m1;
    s32 m2;
    register s32 d1 asm("s1");
    register s32 d2 asm("s0");
    register s32 d3 asm("t8");
    s32 d4;
    s32 value;
    register s32 temp asm("a0");
    s32 value2;
    s32 masked;
    s32 value3;
    s32 prod;
    s32 prodlo;
    s32 rowOff;
    s32 end;
    s32 midOff;
    s32 mo;
    register s32 colOff asm("a1");
    s32 off1;
    s32 off2;
    s32 off3;
    s32 i;
    s32 j;

    i = 0;
    base = 9;
    do {
        j = 0;
        rowOff = i * 0x40;
        m3base = i << 3;
        d1 = base;
        asm volatile("addu %0, %1, $zero" : "=r"(d2) : "r"(base));
        asm volatile("addu %0, %1, $zero" : "=r"(m1) : "r"(base));
        asm volatile("addu %0, %1, $zero" : "=r"(d3) : "r"(base));
        midOff = 0;
        do {
            mo = midOff;
            asm volatile("addu %0, %1, $zero" : "=r"(d4) : "r"(base));
            asm volatile("addu %0, %1, $zero" : "=r"(m2) : "r"(base));
            asm volatile("addiu %0, %1, 8" : "=r"(m3) : "r"(m3base));
            colOff = rowOff;
            do {
                temp = gRandomSeed16;
                off1 = colOff + mo;
                do {
                } while (0);
                value = (temp * 0x6255) + 0x3619;
                asm("andi %0, %1, 0xFFFF" : "=r"(masked) : "r"(value));
                gRandomSeed16 = masked;
                asm volatile("" ::: "memory");
                value &= 0xFFFF;
                value2 = ((value * 0x6255) + 0x3619) & 0xFFFF;
                gRandomSeed16 = value2;
                asm volatile("mult %0, %1"
                             :
                             : "r"(value2), "r"(m1)
                             : "lo", "hi");
                asm volatile("mflo %0" : "=r"(prodlo));
                D_800B1A24[off1] = -(s32)((u32)prodlo >> 16);
                temp = gRandomSeed16;
                asm volatile("addu %0, %1, %2"
                             : "=r"(off2)
                             : "r"(colOff), "r"(mo));
                value = (temp * 0x6255) + 0x3619;
                asm("andi %0, %1, 0xFFFF" : "=r"(masked) : "r"(value));
                gRandomSeed16 = masked;
                asm volatile("" ::: "memory");
                value &= 0xFFFF;
                value2 = ((value * 0x6255) + 0x3619) & 0xFFFF;
                gRandomSeed16 = value2;
                asm volatile("mult %0, %1"
                             :
                             : "r"(value2), "r"(m2)
                             : "lo", "hi");
                asm volatile("mflo %0" : "=r"(prodlo));
                D_800B1A25[off2] = -(s32)((u32)prodlo >> 16);
                temp = gRandomSeed16;
                value3 = ((temp * 0x6255) + 0x3619) & 0xFFFF;
                gRandomSeed16 = value3;
                asm volatile("mult %0, %1"
                             :
                             : "r"(value3), "r"(m3)
                             : "lo", "hi");
                asm volatile("addu %0, %1, %2"
                             : "=r"(off3)
                             : "r"(colOff), "r"(mo));
                colOff += 4;
                asm volatile("mflo %0" : "=r"(prodlo));
                D_800B1A26R[off3] = (s32)((u32)prodlo >> 16);
                asm volatile("addiu %0, %1, 0x40" : "=r"(end) : "r"(rowOff));
            } while (colOff < end);
            asm("" ::"r"(d4));
            j += 1;
            midOff += 0xC0;
        } while (j < 6);
        asm("" ::"r"(d1));
        asm("" ::"r"(d2));
        i += 1;
        base += 9;
    } while (i < 3);
}

extern u8 D_800B19E4[];

void func_80043F7C(u8 *arg0, s16 *arg1) {
    s16 first;
    s32 count;
    u8 *e;
    u8 *src;
    s8 delta;
    s32 off;
    s32 i;
    s16 w;
    u8 *b;
    s32 mv;

    first = arg1[0];
    e = *(u8 **)(*(u8 **)(arg0 + 0x36C) + 0x14) + first * 0x14;
    count = arg1[1] - first + 1;
    w = arg1[10];
    if (*(s8 *)((w >= 0) ? (b = arg0 + 0x3AD, b + w) : (arg0 + (0x3AD - w))) !=
        0) {
        w = arg1[10];
        b = arg0 + 0x3AD;
        delta = *(s8 *)((w >= 0) ? (b + w) : (b - w));
        w = arg1[10];
        off = delta * 0x40;
        if (w >= 0) {
            mv = (w - 1) * 0xC0;
            mv += (s32)D_800B19E4;
            src = (u8 *)(mv + off);
        } else {
            mv = (-w - 1) * 0xC0;
            mv += (s32)D_800B19E4;
            src = (u8 *)(mv + off);
        }
        for (i = 0; i < count; i++) {
            *(s16 *)(e + 0) = (s8)src[0] + *(s32 *)(e + 8);
            *(s16 *)(e + 2) = (s8)src[1] + *(s32 *)(e + 12);
            *(s16 *)(e + 4) = (s8)src[2] + *(s32 *)(e + 16);
            src += 4;
            e += 0x14;
        }
    } else {
        for (i = 0; i < count; i++) {
            *(s16 *)(e + 0) = *(s32 *)(e + 8);
            *(s16 *)(e + 2) = *(s32 *)(e + 12);
            *(s16 *)(e + 4) = *(s32 *)(e + 16);
            e += 0x14;
        }
    }
}

extern u8 D_800A2EE0[];
extern u8 *D_800A3960w17[] asm("D_800A3960.NON_MATCHING");

void func_80044114(u8 *arg0) {
    s32 i;
    u8 *entry;

    *(volatile s16 *)(arg0 + 0x3A4) = 0;
    for (i = 0; i < 8; i++) {
        *(volatile u8 *)(arg0 + i + 0x3A6) = 1;
        *(volatile u8 *)(arg0 + i + 0x3AE) = 0;
    }
    if (D_800A2EE0[0] != 0) {
        *(volatile s16 *)(arg0 + 0x1BC) = 3;
        for (i = 0, entry = arg0; i < 4; i++) {
            *(volatile s16 *)(entry + 0x2AC) = 0;
            *(volatile s16 *)(entry + 0x2B0) = 0;
            entry += 0x28;
        }
        *(volatile s16 *)(arg0 + 0x10C) = 0;
    }
    if (arg0 == D_800A3960[0]) {
        D_800A3960w17[0] = 0;
    }
}

void func_8004419C(u8 *object) {
    s32 i;
    *(volatile s16 *)(object + 0x1BC) = 3;
    for (i = 0; i < 4; i++) {
        *(volatile s16 *)(object + 0x2AC) = 0;
        *(volatile s16 *)(object + 0x2B0) = 0;
        object += 0x28;
    }
}

typedef struct {
    u32 w[12];
} CopyRow30;

extern CopyRow30 D_800AD9B0[];
extern CopyRow30 D_800BBAAC[];
extern void func_800364C4(void);
void func_800441C8(void) {
    s32 row;
    func_800364C4();
    for (row = 0; row < 0x28; row++) {
        D_800BBAAC[row] = D_800AD9B0[row];
    }
}

extern void func_80036540(void);

void func_80044248(void) {
    s32 row;
    func_80036540();
    for (row = 0; row < 0x28; row++) {
        D_800AD9B0[row] = D_800BBAAC[row];
    }
}

void func_800442C8(u8 *arg0, u8 *arg1) {
    u32 bits;
    s32 i;

    bits = *(u32 *)(arg1 + 8);
    if (D_800A2EDC[0] != 0) {
        i = 0;
        do {
            if ((*(u16 *)(arg1 + 0xC) >> i & 1) != 0) {
                *(u8 *)(arg0 + 0x3A6 + i) = 0;
            } else {
                *(u8 *)(arg0 + 0x3A6 + i) = 1;
            }
            i++;
        } while (i < 8);
        arg0[0x3AE] = (bits & 0x3FFF) >> 12;
        arg0[0x3AF] = (bits & 0xFFF) >> 10;
        arg0[0x3B0] = (bits & 0x3FF) >> 8;
        arg0[0x3B1] = (bits & 0xFF) >> 6;
    }
}

INCLUDE_ASM("asm/nonmatchings/effects", func_80044354);

void func_80044594(u8 *arg0) {
    u32 *wp;
    u8 *rec;
    u8 *typ;
    s32 i;
    s8 *bp;
    u8 *fp;
    u32 word;
    u32 src40;
    u32 mode;
    u8 w;
    u32 val38;
    s32 z;

    wp = (u32 *)arg0;
    rec = (u8 *)&D_800AD9B0[0];
    do {
        i = 0;
        bp = (s8 *)arg0 + 2;
        fp = rec + 0x1A;
    loop:
        if (*wp == 0) {
            for (; i < 0x28; i++, fp += 0x30) {
                fp[2] = 0;
            }
            return;
        }
        fp[2] = 1;
        word = *wp;
        typ = D_800A3878w15[0] + ((word >> 24) & 0x1F) * 0x500;
        if ((word & 0xE0000000) == 0x80000000) {
            src40 = *(u32 *)(*(u8 **)(typ + 0x370) + 0x40);
            fp[3] = 10;
        } else {
            do {
                mode = word >> 29;
                src40 = *(u32 *)(*(u8 **)(typ + 0x370) + 0x40) + mode * 0x18;
                fp[3] = mode;
            } while (0);
        }
    } while (0);
    *(s32 *)rec = (*(s8 *)wp << 6) + *(s32 *)typ;
    *(s32 *)(fp - 0x16) = (bp[-1] << 6) + *(s32 *)(typ + 4);
    w = ((u8 *)wp)[3];
    *(u32 *)(fp + 0x12) = src40;
    fp[4] = w & 0x1F;
    val38 = *(u32 *)(*(u8 **)(typ + 0x370) + 0x38);
    i++;
    rec += 0x30;
    *(u32 *)(fp + 0xA) = 0;
    *(u32 *)(fp + 0x6) = 0;
    *(s16 *)(fp - 0x8) = 0;
    *(s16 *)(fp - 0x6) = 0;
    *(u32 *)(fp + 0xE) = val38;
    z = *bp;
    wp++;
    bp += 4;
    *(s16 *)fp = 0xC8;
    *(s16 *)(fp - 0xA) = 0;
    *(s16 *)(fp - 4) = 0;
    *(s16 *)(fp - 2) = 0;
    *(s16 *)(fp - 0xE) = z << 5;
    fp += 0x30;
    if (i < 10) {
        goto loop;
    }
}
