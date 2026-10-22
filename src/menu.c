#include "common.h"
#include "libpress.h"
#include "fixed_addrs.h"
#include "menu_obj.h"
#include <psxsdk/libgpu.h>
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/libcd.h>
#include <psxsdk/libgte.h>
#include <psxsdk/libapi.h>
#include <psxsdk/libspu.h>
#include <psxsdk/kernel.h>
#include "game.h"

extern s32 strlen(char *);
extern void func_8001E7EC(void *, s32, s32);

extern s32 gOrderingTable[];
extern s32 D_800A3A2CAbsolute[];
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
extern u8 *gPlayerCar[];
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
extern void HeapFree(void *ptr);
void *HeapAlloc(u32);
extern s32 D_800A38AC[];
extern s32 D_800A37C4Absolute[];
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
extern void SetPolyF4(u8 *prim);
typedef struct {
    s32 words[10];
} Primitive40;
typedef struct {
    s32 words[4];
} Primitive10;
extern s32 D_800A37ACAbsolute[], D_800A37B4Absolute[], D_800A37C4Absolute[];
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
extern void HeapFree(void *);
void func_80082B70(void);
extern void SsSeqSetVol(short seqAccessNum, short leftVolume,
                        short rightVolume);
extern void func_8001F90C(s32, s32, s32, s16 *);
void func_80041AF0();
void InitPAD(void *, s32, void *, s32);
s32 StartPAD(void);
s32 VSync(s32);
void func_80043D6C(void);
extern void func_800328AC(void *arg0, s32 arg1);
typedef struct {
    u32 w[12];
} CopyRow30;
extern void func_800364C4(void);
extern void func_80036540(void);
typedef struct HeapBlock {
    u32 size; /* payload size in bytes; bit 0 set while the block is free */
} HeapBlock;
extern s32 func_80037204(u8 *);
extern s32 func_8003702C(u8 *, u8 *);
extern s32 D_800A37D0[];
void SetPolyFT4(POLY_FT4 *);
extern u8 gCardMenuMessageb[] asm("D_800A3814.NON_MATCHING");
extern u8 D_800BDD62[], D_800BDDBE[], D_800BDDC0[], D_800BDD64[];
extern u8 D_800BDD65[], D_800BDD66[], D_800BDD67[], D_800BDDC1[];
extern u8 D_800BDDC2[], D_800BDDC3[];
extern DRAWENV D_800BDD4C[];
extern DISPENV D_800BDE04[];
s32 PadGetButtons(s32);
extern void CardTestEvents(void);
extern void CardTestEvents(void), func_8005A414(void);
extern void func_8005A818(u8, u8, u8);
extern u8 D_800A35EC;
extern u8 D_800A37BC, D_800A35EC;
extern u8 D_800A39C4, D_800A37BC, D_800A35EC;
extern void SetPolyF3(POLY_F3 *);
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
extern u8 D_800A3988[];
extern u8 D_800A3644[];
extern char *strcat(char *, char *);
extern u8 *TextFormatInt(s32, u8 *);
extern u8 D_800A3078[], D_800A3988[];
extern void func_8005C8D8(u8);
extern void func_8005A9F4(s32, s16, s16, u8, u8, s32, u8, u8);
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
void ReplayReadEffects(u8 *arg0);
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
s32 HudTextWidth(u8 *str);
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
u8 RaceFindGridPosition(u8 value);
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
void CardOpenEvents(void);
void CardCloseEvents(void);
void CardInit(void);
void CardStop(void);
s32 func_80059F0C(s32 arg0);
s32 CardOpenFile(char *path, s32 flags);
s32 CardReadSectors(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 buf);
s32 CardWriteSectors(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 buf);
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
s16 MenuCharWidth(s8 arg0);
s32 func_8005B0E4(s16 arg0, s32 arg1);
s32 TextCountLines(u8 *str);
void func_8005B17C(u8 *dst, u32 idx, u16 dx, u16 dy, u16 ax, u16 ay);
u8 *MenuObjAlloc(void);
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
void func_8005E408(void) {
    if (D_800A399C[0] != 0) {
        HeapFree(D_800A399C[0]);
    }
    *(void **)&D_800A3988[0x14] = 0;
}

extern char D_800BA058[], D_800A333C[];
void MenuFormatLapText(s32 value) {
    TextFormatInt(value, D_800BA058);
    strcat(D_800BA058, D_800A333C);
}

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

extern u8 D_8009AF84[];
extern s32 D_800A3814[];
extern s32 D_800A3814B[] asm("D_800A3814");
extern s32 D_800A3814C[] asm("D_800A3814");
extern char D_800BA058B[] asm("D_800BA058");
extern char D_800BA058C[] asm("D_800BA058");
void func_8005E644(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 count;
    u8 *entry;
    u8 count2;
    u8 *subBase;
    u8 *sub;
    u8 *local;
    s32 value;
    u8 *entry2;

    count = D_800A35EC;
    D_800A35EC = count + 1;
    entry = D_800A3678 + count * 36;
    entry[4] = 0;
    entry[3] = 0;
    entry[2] = 0;
    count2 = D_800A37BC;
    *(s16 *)(entry + 0xA) = arg1;
    *(s16 *)(entry + 6) = arg1;
    subBase = (u8 *)D_800A3654;
    *(s16 *)(entry + 0x12) = 0;
    *(s16 *)(entry + 0x14) = 0;
    *(s32 *)(entry + 0x1C) = 0;
    *(s16 *)(entry + 0x1A) = 0;
    *(s16 *)(entry + 0) = 0;
    *(s16 *)(entry + 0xC) = 0xC8;
    *(s16 *)(entry + 8) = 0xC8;
    *(s16 *)(entry + 0xE) = 0;
    *(s16 *)(entry + 0x10) = 0;
    *(s16 *)(entry + 0x1A) = 0;
    D_800A37BC = count2 + 1;
    sub = subBase + count2 * 12;
    *(u8 **)(entry + 0x20) = sub;
    sub[0] = 0;
    sub[3] = 0;
    *(s32 *)(sub + 4) = 0;
    local = *(u8 **)(entry + 0x20);
    D_800A3788 = (Df50Fields *)entry;
    local[1] = 2;
    local[2] = 2;
    local[3] = 1;
    value = *(s16 *)&D_8009AF84[(arg0 & 0xFF) * 2] * D_800A37D0[0] / 100;
    D_800A3814[0] = value;
    if (value < 3) {
        D_800A3814B[0] = 3;
    }
    TextFormatInt(D_800A3814C[0], D_800BA058);
    strcat(D_800BA058B, D_800A333C);
    entry2 = (u8 *)D_800A3788;
    *(char **)(local + 8) = D_800BA058C;
    *(u16 *)(entry2 + 6) = *(u16 *)(entry2 + 6) + 0x71;
    *(s16 *)(entry2 + 0xA) = 0x71;
    if ((arg3 & 0xFF) != 0) {
        *(s16 *)(entry2 + 0xA) = 0xEE;
    }
    *(s16 *)((u8 *)D_800A3788 + 0xE) = arg2;
}

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

extern s32 D_800A3344;
extern u16 D_8009AFA8[];
extern MATRIX D_800A8C70;
extern u8 D_800A305B[];
/* One model face: three corner vertices plus a fourth, 32 bytes. The pad
 * halfword of each vertex holds the face colour (v[0..2]) or the
 * semi-transparency flag (v[3]). */
typedef struct {
    SVECTOR v[4];
} ModelQuad;

/* Draws the spinning model that sits in a menu window as one POLY_F4 per
 * face. arg0 advances the spin angle, semiTrans forces semi-transparency, and
 * mode picks the full-screen camera (non-zero) or the window at D_800A3634. */
void MenuDrawModel(s32 arg0, s32 semiTrans, s32 mode) {
    SVECTOR angles;
    VECTOR trans;
    s32 *ot;
    u8 *cursor;
    u8 *tmpl;
    ModelQuad *q;
    s32 i;
    s32 otz;
    s32 x;
    s32 y;
    s32 depth;

    cursor = (u8 *)gPrimitiveCursor[0];
    ot = (s32 *)gOrderingTable[0];
    if (mode & 0xFF) {
        x = 0xA0;
        y = 0x64;
        depth = 0xC8;
        switch (D_800A305B[0]) {
        case 1:
            x = 0x9B;
            depth = 0x12C;
            break;
        case 4:
            depth = 0x12C;
            y = 0x73;
            break;
        case 10:
            x = 0xA0;
            break;
        case 7:
        case 11:
            depth = 0x12C;
            y = 0x6E;
            if (D_800A305B[0] != 0xB) {
                break;
            }
        case 9:
        set69:
            y = 0x69;
            break;
        case 12:
            x = 0x96;
            goto set69;
        case 14:
            depth = 0xFA;
        case 2:
        case 3:
        case 5:
        case 13:
        case 15:
            y = 0x6E;
            break;
        case 16:
            x = 0x96;
            y = 0x64;
            break;
        }
        SetGeomOffset(x, y);
        angles.vy = D_8009AFA8[D_800A305B[0]];
        angles.vx = 0x4B0;
        angles.vz = 0;
    } else if (cursor) {
        /* The two arms are identical: cross-jumping merges them. The copy
         * lengthens otz's live range so the allocator ranks it below i and q,
         * as in the original. */
        SetGeomOffset(*(s16 *)((u8 *)D_800A3634 + 6),
                      *(s16 *)((u8 *)D_800A3634 + 8));
        angles.vy = D_800A3344;
        angles.vx = 0xC8;
        angles.vz = 0;
    } else {
        SetGeomOffset(*(s16 *)((u8 *)D_800A3634 + 6),
                      *(s16 *)((u8 *)D_800A3634 + 8));
        angles.vy = D_800A3344;
        angles.vx = 0xC8;
        angles.vz = 0;
    }
    RotMatrix(&angles, &D_800A8C70);
    SetRotMatrix(&D_800A8C70);
    if (arg0 & 0xFF) {
        if (depth) { /* identical arms, see above */
            D_800A3344 = (D_800A3344 + 0x10) % 0x1000;
        } else {
            D_800A3344 = (D_800A3344 + 0x10) % 0x1000;
        }
    }
    trans.vx = 0;
    trans.vy = 0;
    if (mode & 0xFF) {
        trans.vz = depth;
    } else {
        trans.vz = 0x1C2;
    }
    TransMatrix(&D_800A8C70, &trans);
    SetTransMatrix(&D_800A8C70);
    q = (ModelQuad *)D_800A393C;
    tmpl = D_800A399C[0];
    for (i = 0; i < D_800A38DC; i++) {
        gte_ldv3c(&q->v[0]);
        gte_rtpt();
        if ((semiTrans & 0xFF) == 0) {
            SetSemiTrans(tmpl, q->v[3].pad);
        } else {
            SetSemiTrans(tmpl, 1);
        }
        gte_avsz3();
        asm volatile("mfc2 %0, $7" : "=r"(otz) : "0"(otz));
        if (q->v[3].pad != 0) {
            otz += 0x10;
        }
        if (q->v[0].pad == 0 && q->v[1].pad == 0x46 && q->v[2].pad == 0x9A) {
            if (mode & 0xFF) {
                continue;
            }
            otz -= 0x20;
        }
        if (otz < 0) {
            otz = 0;
        }
        gte_stsxy3(tmpl + 8, tmpl + 0xC, tmpl + 0x10);
        gte_ldv0(&q->v[3]);
        gte_rtps();
        gte_stsxy(tmpl + 0x14);
        *(POLY_F4 *)cursor = *(POLY_F4 *)tmpl;
        AddPrim((u8 *)ot + ((otz >> 2) << 2), cursor);
        q++;
        tmpl += 0x18;
        cursor += 0x18;
    }
    gPrimitiveCursor[0] = (u32)cursor;
}

#ifdef NON_MATCHING
extern u16 D_8009AF84[];
extern s32 D_800A37D0;
extern s32 D_800A3814;
extern char D_800BA058[];
extern char D_800A333C[];
extern u8 *TextFormatInt(s32, u8 *);
extern char *strcat(char *, char *);
void func_8005EC5C(s32 arg0) {
    s32 value;
    s32 scaled;
    value = D_8009AF84[arg0 & 0xFF];
    scaled = (value * D_800A37D0) / 100;
    D_800A3814 = scaled;
    if (scaled < 3)
        D_800A3814 = 3;
    TextFormatInt(D_800A3814, D_800BA058);
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
    *(s32 *)&gCardMenuMessageb[0] = value;
    if (value < 3) {
        D_800A3814[0] = 3;
    }
    TextFormatInt(D_800A3814Abs[0], D_800BA058);
    strcat(D_800BA058NM, D_800A333C);
}

#if 0
/* w7g draft: everything matches except gcc CSEs the two D_800BA058
 * materializations across the TextFormatInt/strcat calls into
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
    TextFormatInt(D_800A37E8[11], D_800BA058);
    strcat(D_800BA058, D_800A333C);
}
#endif
#endif

extern s32 D_8009A31C[];
void func_8005ED04(s32 index) {
    D_800A3740[8][2] = D_8009A31C[index & 0xFF];
}

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
extern u16 D_8009AEB2[];
extern u16 D_8009AEBA[];
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
/* Menu screen builder. Each "object" is a 36-byte record taken from
 * D_800A3678; the MenuObj struct matters for the match: member stores are
 * MEM_IN_STRUCT_P, so the scheduler may hoist the scalar D_800A3654 load
 * above them like retail. Retail's constants and register order depend on
 * the locals below (k2b is pinned to $19, the empty asm statements make the
 * primitive pointers function-wide). */
void func_8005ED74(u8 arg0, u8 arg1) {
    extern s32 func_8005A8EI(s32) asm("MenuStringWidth");
    register s32 k2b asm("$19");
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
    s16 w4, g4, z4;
    s16 k41, k32, k7;
    s16 k3, k9, k30;
    s32 m;
    s16 w1, g1, z1;
    u8 *prim2;
    s32 i;
    s32 j;
    s32 yBase;
    s32 h;
    s32 x1;
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
        x1 = yBase;
        j = 0;
        listSlot = list;
        w1 = 0x78;
        g1 = 0xF;
        z1 = 0x3FC;
    a1_L:
        {
            ix1 = D_800A35EC;
            D_800A35EC = ix1 + 1;
            obj1 = D_800A3678 + ix1 * 36;
            ((MenuObj *)obj1)->unk12 = 0;
            ((MenuObj *)obj1)->unk14 = 0;
            ((MenuObj *)obj1)->unk1C = 0;
            obj1[4] = 0;
            obj1[3] = 0;
            obj1[2] = 0;
            ((MenuObj *)obj1)->unk1A = 0;
            ((MenuObj *)obj1)->unk0 = 1;
            ((MenuObj *)obj1)->unk16 = w1;
            ((MenuObj *)obj1)->unkA = h;
            ((MenuObj *)obj1)->unk6 = h;
            ((MenuObj *)obj1)->unkC = x1;
            ((MenuObj *)obj1)->unk8 = x1;
            ((MenuObj *)obj1)->unk18 = g1;
            ((MenuObj *)obj1)->unkE = 0;
            ((MenuObj *)obj1)->unk10 = 0;
            pr1 = func_80057CCC(1);
            SetPolyFT4((POLY_FT4 *)pr1);
            SetShadeTex(pr1, 0);
            pr1[4] = 0x80;
            pr1[5] = 0x80;
            pr1[6] = 0x80;
            SetSemiTrans(pr1, 0);
            entry = obj1;
            ((MenuObj *)entry)->unk20 = pr1;
            ((MenuObj *)entry)->unk1A = z1;
            if (j == 0) {
                *listSlot = entry;
            } else {
                *(u8 **)(*listSlot + 0x1C) = entry;
            }
            prim2 = ((MenuObj *)entry)->unk20;
            ((MenuObj *)entry)->unk6 = -0xF5;
            ((MenuObj *)entry)->unkE = 2;
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
            x1 += 0xF;
        }
        if (j < 2) {
            goto a1_L;
        }
        j = 0;
        w2 = 0x78;
        c2 = 0x20;
        k2 = 2;
        g2 = 0x1E;
        b2 = 0x40;
    a2_L:
        {
            ix2 = D_800A35EC;
            D_800A35EC = ix2 + 1;
            obj2 = D_800A3678 + ix2 * 36;
            obj2[4] = 0;
            ((MenuObj *)obj2)->unk18 = g2;
            ((MenuObj *)obj2)->unk12 = 0;
            ((MenuObj *)obj2)->unk14 = 0;
            ((MenuObj *)obj2)->unk1C = 0;
            obj2[3] = 0;
            obj2[2] = 0;
            ((MenuObj *)obj2)->unk1A = 0;
            ((MenuObj *)obj2)->unk0 = k2;
            ((MenuObj *)obj2)->unk6 = 0;
            ((MenuObj *)obj2)->unkA = 0;
            ((MenuObj *)obj2)->unk8 = yBase;
            ((MenuObj *)obj2)->unkC = yBase;
            ((MenuObj *)obj2)->unkE = 0;
            ((MenuObj *)obj2)->unk10 = 0;
            ((MenuObj *)obj2)->unk16 = w2;
            obj2[2] = c2;
            obj2[3] = c2;
            obj2[4] = b2;
            pr2 = func_80057D50(1);
            ((MenuObj *)obj2)->unk20 = pr2;
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
            ((MenuObj *)obj2)->unk1A = 0x3FD;
            ((MenuObj *)obj2)->unkE = k2;
            ((MenuObj *)obj2)->unk6 = -0xF5;
            ((MenuObj *)obj2)->unkE = k2;
            *(u8 **)(entry + 0x1C) = obj2;
            entry = obj2;
            j++;
        }
        if (j < 2) {
            goto a2_L;
        }
        asm("" : : "r"(pr2));
        list++;
        yBase = y1;
        i++;
    } while (i < 4);
    {
        s32 n;
        n = 0;
        i = 0;
        do {
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
                ((MenuObj *)entry)->unk12 = 0;
                ((MenuObj *)entry)->unk14 = 0;
                ((MenuObj *)entry)->unk1C = 0;
                ((MenuObj *)entry)->unk1A = 0;
                ((MenuObj *)entry)->unk0 = 0;
                ((MenuObj *)entry)->unkA = h;
                ((MenuObj *)entry)->unk6 = h;
                ((MenuObj *)entry)->unkC = yBase;
                ((MenuObj *)entry)->unk8 = yBase;
                ((MenuObj *)entry)->unkE = 0;
                ((MenuObj *)entry)->unk10 = 0;
                ((MenuObj *)entry)->unk1A = 0;
                D_800A37BC = primIdx + 1;
                textPrim = (u8 *)D_800A3654 + primIdx * 12;
                ((MenuObj *)entry)->unk20 = textPrim;
                textPrim[0] = 0;
                textPrim[3] = 0;
                *(s32 *)(textPrim + 4) = 0;
                D_800BB9F4[n] = entry;
                ((MenuObj *)entry)->unkE = 2;
                ((MenuObj *)entry)->unk16 = value;
                ((MenuObj *)entry)->unk6 = *(u16 *)(entry + 0xA) - 0xF5;
                ((MenuObj *)entry)->unk18 = func_8005A84C();
                primLoad = ((MenuObj *)entry)->unk20;
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
        } while (i < 4);
    }
    {
        u8 *obj3;
        u8 *pr3;
        u8 *pq3;
        yBase = *(s16 *)(D_800B996C[0] + 0xC) + 0xD;
        k3 = 3;
        k9 = 9;
        w4 = 0x68;
        g4 = 5;
        z4 = 0x3F2;
        h = 8;
        i = 0;
        do {
            u8 **slot;
            u8 **tbl;
            u16 w;
            u16 hh;
            u32 scale;
            u32 level;
            ix4 = D_800A35EC;
            D_800A35EC = ix4 + 1;
            obj4 = D_800A3678 + ix4 * 36;
            ((MenuObj *)obj4)->unk0 = 1;
            ((MenuObj *)obj4)->unk16 = w4;
            ((MenuObj *)obj4)->unk12 = 0;
            ((MenuObj *)obj4)->unk14 = 0;
            ((MenuObj *)obj4)->unk1C = 0;
            obj4[4] = 0;
            obj4[3] = 0;
            obj4[2] = 0;
            ((MenuObj *)obj4)->unk1A = 0;
            ((MenuObj *)obj4)->unkA = h;
            ((MenuObj *)obj4)->unk6 = h;
            ((MenuObj *)obj4)->unkC = yBase;
            ((MenuObj *)obj4)->unk8 = yBase;
            ((MenuObj *)obj4)->unk18 = g4;
            ((MenuObj *)obj4)->unkE = 0;
            ((MenuObj *)obj4)->unk10 = 0;
            pr4 = func_80057CCC(1);
            SetPolyFT4((POLY_FT4 *)pr4);
            SetShadeTex(pr4, 0);
            pr4[4] = 0x80;
            pr4[5] = 0x80;
            pr4[6] = 0x80;
            SetSemiTrans(pr4, 0);
            entry = obj4;
            ((MenuObj *)entry)->unk20 = pr4;
            ((MenuObj *)entry)->unk1A = z4;
            tbl = D_800B9980;
            slot = tbl + i;
            *slot = entry;
            prim2 = ((MenuObj *)entry)->unk20;
            ((MenuObj *)entry)->unk6 = -0xF5;
            ((MenuObj *)entry)->unkE = 2;
            w = *(u16 *)(entry + 0x16);
            hh = *(u16 *)(entry + 0x18);
            *(s16 *)(prim2 + 0xE) = GetClut(D_8009AEA2[1], D_8009AEA6[0]);
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
            level = D_800A3860[arg0][(u8)i];
            scale = ((((level << 1) + level) << 2) + level) >> 3;
            if (scale == 0) {
                scale = 1;
            }
            x4 = yBase + 1;
            {
                s16 y2;
                ix5 = D_800A35EC;
                D_800A35EC = ix5 + 1;
                obj5 = D_800A3678 + ix5 * 36;
                ((MenuObj *)obj5)->unk0 = 2;
                ((MenuObj *)obj5)->unk6 = k9;
                ((MenuObj *)obj5)->unkA = k9;
                obj5[2] = 0;
                ((MenuObj *)obj5)->unk18 = k3;
                obj5[4] = 0;
                obj5[2] = 0x40;
                ((MenuObj *)obj5)->unk12 = 0;
                ((MenuObj *)obj5)->unk14 = 0;
                ((MenuObj *)obj5)->unk1C = 0;
                obj5[3] = 0;
                ((MenuObj *)obj5)->unk1A = 0;
                ((MenuObj *)obj5)->unk8 = x4;
                ((MenuObj *)obj5)->unkC = x4;
                ((MenuObj *)obj5)->unkE = 0;
                ((MenuObj *)obj5)->unk10 = 0;
                ((MenuObj *)obj5)->unk16 = scale;
                obj5[3] = 0x60;
                obj5[4] = 0x80;
                pr5 = func_80057D50(1);
                ((MenuObj *)obj5)->unk20 = pr5;
                SetPolyF4(pr5);
                SetSemiTrans(pr5, 1);
                pr5[4] = 0x40;
                entry = obj5;
                do {
                    pr5[6] = 0x80;
                } while (0);
                *(s16 *)(pr5 + 8) = k9;
                pr5[5] = 0x60;
                *(s16 *)(pr5 + 0xA) = x4;
                y2 = scale + k9;
                *(s16 *)(pr5 + 0xC) = y2;
                i++;
                *(s16 *)(pr5 + 0xE) = x4;
                *(s16 *)(pr5 + 0x10) = k9;
                *(s16 *)(pr5 + 0x12) = yBase + 4;
                *(s16 *)(pr5 + 0x16) = yBase + 4;
                *(s16 *)(pr5 + 0x14) = y2;
                ((MenuObj *)entry)->unk1A = 0x3E8;
                *(u8 **)(*slot + 0x1C) = entry;
                ((MenuObj *)entry)->unk6 = -0xF5;
                ((MenuObj *)entry)->unkE = 2;
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
        ((MenuObj *)obj6)->unk12 = 0;
        ((MenuObj *)obj6)->unk14 = 0;
        ((MenuObj *)obj6)->unk1C = 0;
        obj6[4] = 0;
        obj6[3] = 0;
        obj6[2] = 0;
        ((MenuObj *)obj6)->unk1A = 0;
        ((MenuObj *)obj6)->unk0 = 1;
        ((MenuObj *)obj6)->unkC = 0x2A;
        ((MenuObj *)obj6)->unkA = 0;
        ((MenuObj *)obj6)->unk8 = 0x2A;
        ((MenuObj *)obj6)->unk16 = 0x78;
        ((MenuObj *)obj6)->unk6 = 0;
        ((MenuObj *)obj6)->unk18 = 0x30;
        ((MenuObj *)obj6)->unkE = 0;
        ((MenuObj *)obj6)->unk10 = 0;
        pr6 = func_80057CCC(1);
        SetPolyFT4((POLY_FT4 *)pr6);
        SetShadeTex(pr6, 0);
        pr6[4] = 0x80;
        pr6[5] = 0x80;
        pr6[6] = 0x80;
        SetSemiTrans(pr6, 0);
        entry = obj6;
        ((MenuObj *)entry)->unk20 = pr6;
        ((MenuObj *)entry)->unk1A = 0x3FC;
        do {
        } while (0);
        prim2 = ((MenuObj *)entry)->unk20;
        w = *(u16 *)(entry + 0x16);
        hh = *(u16 *)(entry + 0x18);
        ((MenuObj *)entry)->unkE = 2;
        j = 0;
        D_800A39ACPtr = entry;
        ((MenuObj *)entry)->unk10 = 0;
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
    k2b = 2;
    k30 = 0x30;
    *(s16 *)(D_800A39ACPtr + 6) = -0x7D;
    *(s16 *)(D_800A39ACPtr + 0xE) = 2;
    do {
        ix7 = D_800A35EC;
        D_800A35EC = ix7 + 1;
        obj7 = D_800A3678 + ix7 * 36;
        obj7[4] = 0;
        ((MenuObj *)obj7)->unk18 = k30;
        ((MenuObj *)obj7)->unk12 = 0;
        ((MenuObj *)obj7)->unk14 = 0;
        ((MenuObj *)obj7)->unk1C = 0;
        obj7[3] = 0;
        obj7[2] = 0;
        ((MenuObj *)obj7)->unk1A = 0;
        ((MenuObj *)obj7)->unk0 = k2b;
        ((MenuObj *)obj7)->unk6 = 0;
        ((MenuObj *)obj7)->unkA = 0;
        ((MenuObj *)obj7)->unk8 = yBase;
        ((MenuObj *)obj7)->unkC = yBase;
        ((MenuObj *)obj7)->unkE = 0;
        ((MenuObj *)obj7)->unk10 = 0;
        ((MenuObj *)obj7)->unk16 = h;
        obj7[2] = 0x20;
        obj7[3] = 0x20;
        obj7[4] = 0x40;
        pr7 = func_80057D50(1);
        ((MenuObj *)obj7)->unk20 = pr7;
        SetPolyF4(pr7);
        SetSemiTrans(pr7, 1);
        pr7[4] = 0x20;
        pr7[5] = 0x20;
        pr7[6] = 0x40;
        *(s16 *)(pr7 + 0x12) = 0x5A;
        *(s16 *)(pr7 + 0x16) = 0x5A;
        *(s16 *)(pr7 + 8) = 0;
        *(s16 *)(pr7 + 0xA) = yBase;
        *(s16 *)(pr7 + 0xC) = h;
        *(s16 *)(pr7 + 0xE) = yBase;
        *(s16 *)(pr7 + 0x10) = 0;
        *(s16 *)(pr7 + 0x14) = h;
        ((MenuObj *)obj7)->unk1A = 0x3FD;
        ((MenuObj *)obj7)->unkE = k2b;
        ((MenuObj *)obj7)->unk6 = -0x7D;
        ((MenuObj *)obj7)->unkE = k2b;
        *(u8 **)(entry + 0x1C) = obj7;
        entry = obj7;
        j++;
    } while (j < 2);
    asm("" : : "r"(pr7));
    k41 = 0x41;
    k32 = 0x32;
    k7 = 7;
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
        ((MenuObj *)obj8)->unk0 = 1;
        ((MenuObj *)obj8)->unkA = k41;
        ((MenuObj *)obj8)->unk6 = k41;
        ((MenuObj *)obj8)->unk16 = k32;
        ((MenuObj *)obj8)->unk12 = 0;
        ((MenuObj *)obj8)->unk14 = 0;
        ((MenuObj *)obj8)->unk1C = 0;
        obj8[4] = 0;
        obj8[3] = 0;
        obj8[2] = 0;
        ((MenuObj *)obj8)->unk1A = 0;
        ((MenuObj *)obj8)->unkC = yBase;
        ((MenuObj *)obj8)->unk8 = yBase;
        ((MenuObj *)obj8)->unk18 = k7;
        ((MenuObj *)obj8)->unkE = 0;
        ((MenuObj *)obj8)->unk10 = 0;
        pr8 = func_80057CCC(1);
        SetPolyFT4((POLY_FT4 *)pr8);
        SetShadeTex(pr8, 0);
        pr8[4] = 0x80;
        pr8[5] = 0x80;
        pr8[6] = 0x80;
        SetSemiTrans(pr8, 0);
        entry = obj8;
        ((MenuObj *)entry)->unk20 = pr8;
        ((MenuObj *)entry)->unk1A = 1;
        slot = &D_800B60B8[i];
        *slot = entry;
        prim2 = ((MenuObj *)entry)->unk20;
        ((MenuObj *)entry)->unkE = 2;
        ((MenuObj *)entry)->unk6 = -0x7D;
        w = *(u16 *)(entry + 0x16);
        hh = *(u16 *)(entry + 0x18);
        x6 = yBase + 1;
        *(s16 *)(prim2 + 0xE) =
            GetClut(D_8009AEB2[0], *(u16 *)((u8 *)D_8009AEB2 + 2));
        *(s16 *)(prim2 + 0x16) = GetTPage(D_8009AEBA[0], 3, *(u16 *)D_8009AEAE,
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
            ((MenuObj *)objB9)->unk0 = 2;
            ((MenuObj *)objB9)->unk6 = 0x42;
            ((MenuObj *)objB9)->unk12 = 0;
            ((MenuObj *)objB9)->unk14 = 0;
            ((MenuObj *)objB9)->unk1C = 0;
            objB9[4] = 0;
            objB9[3] = 0;
            objB9[2] = 0;
            ((MenuObj *)objB9)->unk1A = 0;
            ((MenuObj *)objB9)->unkA = 0x42;
            ((MenuObj *)objB9)->unk8 = x6;
            ((MenuObj *)objB9)->unkC = x6;
            ((MenuObj *)objB9)->unkE = 0;
            ((MenuObj *)objB9)->unk10 = 0;
            ((MenuObj *)objB9)->unk16 = 0x30;
            ((MenuObj *)objB9)->unk18 = 5;
            objB9[2] = 0x40;
            objB9[3] = 0x60;
            objB9[4] = 0x80;
            prC9 = func_80057D50(1);
            ((MenuObj *)objB9)->unk20 = prC9;
            SetPolyF4(prC9);
            SetSemiTrans(prC9, 0);
            prC9[6] = 0x80;
            *(s16 *)(prC9 + 8) = 0x42;
            prC9[4] = 0x40;
            prC9[5] = 0x60;
            *(s16 *)(prC9 + 0xA) = x6;
            *(s16 *)(prC9 + 0xC) = 0x72;
            *(s16 *)(prC9 + 0xE) = x6;
            *(s16 *)(prC9 + 0x10) = 0x42;
            {
                s32 y6;
                y6 = yBase + 6;
                *(s16 *)(prC9 + 0x12) = y6;
                *(s16 *)(prC9 + 0x14) = 0x72;
                *(s16 *)(prC9 + 0x16) = y6;
            }
            entry = objB9;
            *(u8 **)(*slot + 0x1C) = entry;
            ((MenuObj *)entry)->unk6 = -0x7D;
            ((MenuObj *)entry)->unkE = 2;
            ((MenuObj *)entry)->unk1A = 0;
        }
        func_8005A7B8(2, 2);
        strP = &D_8009A298[i];
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
            entry = objC10;
            h = 0x3E - value;
            ((MenuObj *)entry)->unk12 = 0;
            ((MenuObj *)entry)->unk14 = 0;
            ((MenuObj *)entry)->unk1C = 0;
            ((MenuObj *)entry)->unk1A = 0;
            ((MenuObj *)entry)->unk0 = 0;
            ((MenuObj *)entry)->unkA = h;
            ((MenuObj *)entry)->unk6 = h;
            ((MenuObj *)entry)->unkC = yBase;
            ((MenuObj *)entry)->unk8 = yBase;
            ((MenuObj *)entry)->unkE = 0;
            ((MenuObj *)entry)->unk10 = 0;
            ((MenuObj *)entry)->unk1A = 0;
            D_800A37BC = primIdx + 1;
            textPrim = (u8 *)D_800A3654 + primIdx * 12;
            ((MenuObj *)entry)->unk20 = textPrim;
            textPrim[0] = 0;
            textPrim[3] = 0;
            *(s32 *)(textPrim + 4) = 0;
            D_800AE168[i] = entry;
            ((MenuObj *)entry)->unkE = 2;
            ((MenuObj *)entry)->unk16 = value;
            ((MenuObj *)entry)->unk6 = ((MenuObj *)entry)->unkA - 0xAD;
            ((MenuObj *)entry)->unk18 = func_8005A84C();
            prD10 = ((MenuObj *)entry)->unk20;
            prD10[1] = 2;
            prD10[2] = 2;
        }
        i++;
        *(s32 *)(prD10 + 8) = *strP;
        yBase += 0xA;
    } while (i < 4);
    if (arg1 != 0) {
        u8 primIdx;
        u8 *textPrim;
        u8 *primLoad;
        ix11 = D_800A35EC;
        D_800A35EC = ix11 + 1;
        obj11 = D_800A3678 + ix11 * 36;
        obj11[4] = 0;
        obj11[3] = 0;
        obj11[2] = 0;
        primIdx = D_800A37BC;
        m = (s32)obj11;
        ((MenuObj *)m)->unkA = 5;
        ((MenuObj *)m)->unk12 = 0;
        ((MenuObj *)m)->unk14 = 0;
        ((MenuObj *)m)->unk1C = 0;
        ((MenuObj *)m)->unk1A = 0;
        ((MenuObj *)m)->unk0 = 0;
        ((MenuObj *)m)->unk6 = 5;
        ((MenuObj *)m)->unkC = 0x20;
        ((MenuObj *)m)->unk8 = 0x20;
        ((MenuObj *)m)->unkE = 0;
        ((MenuObj *)m)->unk10 = 0;
        ((MenuObj *)m)->unk1A = 0;
        D_800A37BC = primIdx + 1;
        textPrim = (u8 *)D_800A3654 + primIdx * 12;
        ((MenuObj *)m)->unk20 = textPrim;
        textPrim[0] = 0;
        textPrim[3] = 0;
        *(s32 *)(textPrim + 4) = 0;
        ((MenuObj *)m)->unkE = 2;
        ((MenuObj *)m)->unk16 = value;
        ((MenuObj *)m)->unk6 = *(u16 *)(((u8 *)m) + 0xA) - 0xAD;
        ((MenuObj *)m)->unk18 = func_8005A84C();
        primLoad = ((MenuObj *)m)->unk20;
        primLoad[1] = 2;
        primLoad[2] = 2;
        *(s32 *)(primLoad + 8) = *(s32 *)((u8 *)D_8009A298 + arg0 * 4 + 0x10);
        *(u8 **)(entry + 0x1C) = ((u8 *)m);
    }
    func_80060008(arg0);
}

void func_8005FE90(void) {
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

extern u8 D_800A3861U8[][4] asm("D_800A3861.NON_MATCHING");
extern u8 D_800A3862U8[][4] asm("D_800A3862.NON_MATCHING");
extern u8 D_800A3863U8[][4] asm("D_800A3863.NON_MATCHING");

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

/* Same body as func_8005CF34. Retail emits it out of line there and inlines
 * it at each call site below; the inline parameter copies place the moves
 * in the loop. */
static inline void MenuObjDrawText(u8 *window, u8 code, u8 first, u8 second,
                                   s32 textId) {
    u8 *prim;

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

void MenuDrawLevelBars(s8 arg0, u8 arg1) {
    s32 i;
    s32 j;
    s32 first;
    s8 sel;
    u32 level;
    u32 scale;
    u8 *node;
    u8 *window;
    u8 *prim;

    sel = arg0 - 2;
    for (i = 0; i < 4; i++) {
        level = D_800A3860[arg1][(u8)i];
        scale = ((((level << 1) + level) << 2) + level) >> 3;
        if (scale == 0) {
            scale = 1;
        }
        *(s16 *)(*(u8 **)(D_800B9980[(u8)i] + 0x1C) + 0x16) = scale;
        func_8005B8B8(D_800B996C[i], 0xFF);
        func_8005B8B8(D_800B9980[i], i != sel);
        first = i != sel;
        for (j = 0; j < 3; j++) {
            window = D_800BB9F4[i * 3 + j];
            prim = *(u8 **)(window + 0x20);
            if (i == sel) {
                *(s32 *)(prim + 4) = 0;
            } else {
                *(s32 *)(prim + 4) = 0x3ED;
            }
            MenuObjDrawText(window, 0, first, 0, 0);
        }
    }
    func_8005B8B8(D_800A39ACPtr, 0xFF);
    for (i = 0; i < 4; i++) {
        func_8005B8B8(D_800B60B8[i], 0xFF);
        MenuObjDrawText(D_800AE168[i], 0, 0, 0, 0);
    }
    node = *(u8 **)(D_800AE168[3] + 0x1C);
    if (node != 0) {
        func_8005B8B8(node, 0xFF);
    }
}

extern u8 *D_800A3A68Store asm("D_800A3A68");
extern s32 D_8009A2B0[];
extern s32 D_8009A2BC[];
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
    u8 *writeEnd;
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
        value = (s16)MenuStringWidth(*p);
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
extern PanelState *D_800A3A68;
void func_80060E94(s32 arg0) {
    s32 value;
    s32 height;
    s32 centered;
    func_8005A7B8(2, 2);
    value = D_8009A2B0[arg0 & 0xFF];
    D_800A3A68->child->value = value;
    height = MenuStringWidth(value);
    centered = (0x78 - height) / 2;
    D_800A3A68->y = centered;
    D_800A3A68->height = (s16)height;
}

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

extern u8 D_800A2F94Lui asm("D_800A2F94Absolute");
void func_80060F54(s32 arg0, s32 volume) {
    u8 *node;
    u8 x;

    node = *(u8 **)(D_800A38A8 + 0x1C);
    volume &= 0xFF;
    x = arg0;
    *(u16 *)(node + 0x16) = x;
    if (volume != 0) {
        x = arg0;
        D_800A2F94Lui = (x * 127) / 100;
        SoundSetSlotVolume(1, 0x7F, 0x7F);
    } else {
        CdSetMixVolume(x);
    }
}

typedef union {
    s32 value;
    s64 home;
} MenuWordHome;
typedef union {
    s8 value;
    s64 home;
} MenuCounterHome;
typedef struct {
    s8 tab[7];
} MenuRowList;
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
extern u16 D_8009AEA0[];
extern u16 D_8009AEA4[];
extern u16 D_8009AEAC[];
extern u8 D_8009AEA8[];
struct UnkObject24;
extern void func_80067EA4(struct UnkObject24 *, u8, u8, s32, u8, s32);
extern void ListSetFieldsAndEnable(u8 *, s16, s16, s16);
extern u8 D_800A3644[9];

void func_80060FD8(void) {
    /* These are the observed fifth and sixth stack argument homes. */
    struct {
        s32 fifth;
        s32 sixth;
    } labelArgs;
    register u8 *currentNode asm("$22");
    register u8 *previousNode asm("$21");
    MenuRowList rowList;
    MenuCounterHome panelIndex;
    register s8 backgroundIndex asm("$23");
    register s8 borderIndex asm("$23");
    register s8 textIndex asm("$23");
    register s32 panelState asm("$18");
    register s8 rowSide asm("$23");
    register s8 rowItem asm("$18");
    MenuWordHome packetWidth;
    MenuWordHome packetHeight;
    MenuWordHome textureRow;
    MenuWordHome colorHome;
    MenuWordHome stripPanel;
    MenuWordHome sideOffset;
    MenuWordHome markerPanel;
    MenuWordHome triangleOffset;
    MenuWordHome shadeHome;
    register s32 backgroundShade asm("$6");
    register s32 textCenterX asm("$17");
    register s32 initialShade asm("$3");
    register u32 panelMode asm("$4");
    register s32 textLeftX asm("$19");
    s64 callAccumulator;
    register s32 panelTableBase asm("$12");
    register s32 previousPanelByte asm("$12");
    register s32 nextPanel asm("$2");

    {
        register u32 initialIndex asm("$4");
        register u8 *cell asm("$16");
        register s32 centered asm("$2");
        initialIndex = D_800A35EC;
        rowList = *(MenuRowList *)D_800A3348;
        /* These slots reproduce observed compiler spill homes.
         * They do not imply original source struct types. */
        asm volatile(""
                     : "=m"(panelIndex.value), "=m"(packetWidth.value),
                       "=m"(packetHeight.value), "=m"(textureRow.value),
                       "=m"(colorHome.value));
        asm volatile(""
                     : "=m"(stripPanel.value), "=m"(sideOffset.value),
                       "=m"(markerPanel.value), "=m"(triangleOffset.value),
                       "=m"(shadeHome.value));
        /* Keep the allocation and pool loads in their retail order. */
        asm volatile(".set\tnoreorder\n"
                     "lw         $v1, D_800A3678\n"
                     "addiu      $v0, $a0, 0x1\n"
                     "sb         $v0, D_800A35EC\n"
                     "sll        $v0, $a0, 3\n"
                     "addu       $v0, $v0, $a0\n"
                     "sll        $v0, $v0, 2\n"
                     "addu       $v1, $v1, $v0\n"
                     "sb         $zero, 0x4($v1)\n"
                     "sb         $zero, 0x3($v1)\n"
                     "sb         $zero, 0x2($v1)\n"
                     "lbu        $a0, D_800A37BC\n"
                     "addu       %0, $v1, $zero\n"
                     "lw         $v1, D_800A3654\n"
                     "sh         $zero, 0x12(%0)\n"
                     "sh         $zero, 0x14(%0)\n"
                     "sw         $zero, 0x1C(%0)\n"
                     "sh         $zero, 0x1A(%0)\n"
                     "sh         $zero, 0x0(%0)\n"
                     "sh         $zero, 0xA(%0)\n"
                     "sh         $zero, 0x6(%0)\n"
                     "sh         $zero, 0xC(%0)\n"
                     "sh         $zero, 0x8(%0)\n"
                     "sh         $zero, 0xE(%0)\n"
                     "sh         $zero, 0x10(%0)\n"
                     "sh         $zero, 0x1A(%0)\n"
                     "addiu      $v0, $a0, 0x1\n"
                     "sb         $v0, D_800A37BC\n"
                     "sll        $v0, $a0, 1\n"
                     "addu       $v0, $v0, $a0\n"
                     "sll        $v0, $v0, 2\n"
                     "addu       $v1, $v1, $v0\n"
                     "sw         $v1, 0x20(%0)\n"
                     "sb         $zero, 0x0($v1)\n"
                     "sb         $zero, 0x3($v1)\n"
                     "sw         $zero, 0x4($v1)\n"
                     "lw         %1, 0x20(%0)\n"
                     "ori        $v0, $zero, 0x1\n"
                     "sh         $v0, 0x1A(%0)\n"
                     "ori        $v0, $zero, 0xDA\n"
                     "sh         $v0, 0x14(%0)\n"
                     "ori        $v0, $zero, 0x2\n"
                     "sb         $v0, 0x2(%1)\n"
                     "sb         $v0, 0x1(%1)\n"
                     "lui        $v0, %%hi(D_8009AC00)\n"
                     "lw         $v0, %%lo(D_8009AC00)($v0)\n"
                     "ori        $a1, $zero, 0x2\n"
                     "ori        $a0, $zero, 0x2\n"
                     "jal        func_8005A7B8\n"
                     "sw        $v0, 0x8(%1)\n"
                     ".set\tnoreorder\n"
                     ".set\treorder\n"
                     : "=r"(currentNode), "=r"(cell)
                     : "r"(initialIndex)
                     : "$2", "$3", "$4", "$5", "$31", "memory");
        centered = func_8005B0E4(0x140, *(s32 *)(cell + 8));
        asm volatile("lui $a0,%%hi(D_800A3644)\n"
                     "lbu $a0,%%lo(D_800A3644)($a0)\n"
                     "sh $v0,0x12($s6)\n"
                     "sw $s6,D_800A37F8\n"
                     "bnez $a0,1f\n"
                     "ori $v1,$zero,0x3c\n"
                     "ori $v1,$zero,0x55\n"
                     "1:\n"
                     ".set\treorder\n"
                     : "=r"(panelMode), "=r"(initialShade)
                     : "r"(centered), "r"(currentNode)
                     : "memory");
    }
    {
        register s32 condition asm("$2");
        asm volatile("addiu $v0,$a0,1\n"
                     ".set\treorder\n"
                     : "=r"(condition)
                     : "r"(panelMode));
        panelIndex.value = 0;
        if (condition == 0) {
            goto panelsDone;
        }
    }
    asm volatile("sll $v1,$v1,24\n"
                 "sw $v1,%0\n"
                 ".set\treorder\n"
                 : "=m"(colorHome.value), "=r"(initialShade)
                 : "1"(initialShade));
panelLoop:
    {
        {
            register u8 *node asm("$16");
            register u8 *primitive asm("$17");
            register s32 panelNumber asm("$18");
            register s32 panelByteOffset asm("$19");
            register s32 packetMode asm("$2");
            register s32 loopCondition asm("$2");
            asm volatile("" : : "m"(colorHome.value));
            asm volatile(".set\tnoreorder\n"
                         "lbu $t3,%4\n"
                         "addu $s7,$zero,$zero\n"
                         "ori $a2,$zero,0x20\n"
                         "sll $v0,$t3,24\n"
                         "sra $s2,$v0,24\n"
                         "sll $s3,$s2,2\n"
                         ".set\treorder\n"
                         : "=r"(backgroundIndex), "=r"(backgroundShade),
                           "=r"(panelNumber), "=r"(panelByteOffset)
                         : "m"(panelIndex.value)
                         : "$2", "$11");
            do {
                asm volatile(".set\tnoreorder\n"
                             "lbu        $v1, D_800A35EC\n"
                             "lw         $s0, D_800A3678\n"
                             "ori        $a0, $zero, 0x1\n"
                             "addiu      $v0, $v1, 0x1\n"
                             "sb         $v0, D_800A35EC\n"
                             "sll        $v0, $v1, 3\n"
                             "addu       $v0, $v0, $v1\n"
                             "sll        $v0, $v0, 2\n"
                             "addu       $s0, $s0, $v0\n"
                             "ori        $t4, $zero, 0x2\n"
                             "ori        $t3, $zero, 0x140\n"
                             "sh         $t4, 0x0($s0)\n"
                             "ori        $t4, $zero, 0x4A\n"
                             "sb         $zero, 0x4($s0)\n"
                             "sh         $t3, 0x16($s0)\n"
                             "ori        $t3, $zero, 0x40\n"
                             "sh         $zero, 0x12($s0)\n"
                             "sh         $zero, 0x14($s0)\n"
                             "sw         $zero, 0x1C($s0)\n"
                             "sb         $zero, 0x3($s0)\n"
                             "sb         $zero, 0x2($s0)\n"
                             "sh         $zero, 0x1A($s0)\n"
                             "sh         $zero, 0x6($s0)\n"
                             "sh         $zero, 0xA($s0)\n"
                             "sh         $zero, 0x8($s0)\n"
                             "sh         $zero, 0xC($s0)\n"
                             "sh         $zero, 0xE($s0)\n"
                             "sh         $zero, 0x10($s0)\n"
                             "sh         $t4, 0x18($s0)\n"
                             "sb         $a2, 0x2($s0)\n"
                             "sb         $a2, 0x3($s0)\n"
                             "sb         $t3, 0x4($s0)\n"
                             "jal        func_80057D50\n"
                             "sw        $a2, 0x68($sp)\n"
                             "addu       $s1, $v0, $zero\n"
                             "addu $a0,$s1,$zero\n"
                             "jal SetPolyF4\n"
                             "sw $s1,0x20($s0)\n"
                             ".set\tnoreorder\n"
                             ".set\treorder\n"
                             : "=r"(node), "=r"(primitive),
                               "=m"(shadeHome.value)
                             : "r"(backgroundShade)
                             : "$2", "$3", "$4", "$11", "$12", "$31", "memory");
                SetSemiTrans(primitive, 1);
                asm volatile(".set\tnoreorder\n"
                             "lw         $a2, 0x68($sp)\n"
                             "addu       $s6, $s0, $zero\n"
                             "ori        $t4, $zero, 0x40\n"
                             "ori        $t3, $zero, 0x140\n"
                             "sb         $t4, 0x6($s1)\n"
                             "ori        $t4, $zero, 0x4A\n"
                             "sh         $t3, 0xC($s1)\n"
                             "sh         $t4, 0x12($s1)\n"
                             "ori        $v0, $zero, 0x3\n"
                             "sh         $zero, 0x8($s1)\n"
                             "sh         $zero, 0xA($s1)\n"
                             "sh         $zero, 0xE($s1)\n"
                             "sh         $zero, 0x10($s1)\n"
                             "sh         $t3, 0x14($s1)\n"
                             "sh         $t4, 0x16($s1)\n"
                             "sb         $a2, 0x4($s1)\n"
                             "sb         $a2, 0x5($s1)\n"
                             ".set\tnoreorder\n"
                             ".set\treorder\n"
                             : "=r"(currentNode), "=r"(backgroundShade),
                               "=r"(packetMode)
                             : "r"(node), "r"(primitive), "m"(shadeHome.value)
                             : "$11", "$12", "memory");
                asm volatile("sh $v0,0x1a($s6)\n"
                             "addiu $v0,$zero,-0xa0\n"
                             "sh $v0,0x12($s6)\n"
                             "addu $v0,$s3,$s2\n"
                             "sll $v0,$v0,2\n"
                             "subu $v0,$v0,$s2\n"
                             "sll $v0,$v0,2\n"
                             "addiu $v0,$v0,3\n"
                             "sh $v0,0x14($s6)\n"
                             ".set\treorder\n"
                             :
                             : "r"(packetMode), "r"(currentNode),
                               "r"(panelNumber), "r"(panelByteOffset)
                             : "$2", "memory");
                asm volatile(".set\tnoreorder\n"
                             "sll $v0,$s7,24\n"
                             "bnez $v0,1f\n"
                             "nop\n"
                             "lui $t3,%%hi(D_800A37D8)\n"
                             "addiu $t3,$t3,%%lo(D_800A37D8)\n"
                             "addu $v0,$s3,$t3\n"
                             "j 2f\n"
                             "sw $s6,0($v0)\n"
                             "1: sw $s6,0x1c($s5)\n"
                             "2:\n"
                             ".set\treorder\n"
                             :
                             : "r"(backgroundIndex), "r"(panelByteOffset),
                               "r"(currentNode), "r"(previousNode)
                             : "$2", "$11", "memory");
                asm volatile("addiu $v0,$s7,1\n"
                             "addu $s7,$v0,$zero\n"
                             "sll $v0,$v0,24\n"
                             "sra $v0,$v0,24\n"
                             "slti $v0,$v0,2\n"
                             ".set\treorder\n"
                             : "=r"(backgroundIndex), "=r"(loopCondition)
                             : "0"(backgroundIndex));
                previousNode = currentNode;
            } while (loopCondition != 0);
        }
        {
            register s32 borderYBase asm("$19");
            register s32 tone asm("$17");
            register s32 loopCondition asm("$2");

            asm volatile(".set\tnoreorder\n"
                         "lbu        $t4, 0x20($sp)\n"
                         "addu       $s7, $zero, $zero\n"
                         "ori        $s1, $zero, 0x40\n"
                         "sll        $v1, $t4, 24\n"
                         "sra        $v1, $v1, 24\n"
                         "sll        $v0, $v1, 2\n"
                         "addu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "subu       $v0, $v0, $v1\n"
                         "sll        $s3, $v0, 2\n"
                         ".set\treorder\n"
                         : "=r"(borderIndex), "=r"(tone), "=r"(borderYBase)
                         : "m"(panelIndex.value)
                         : "$2", "$3", "$12");
            do {
                /* Border allocation and placement retain their saved-register path. */
                asm volatile(
                    ".set\tnoreorder\n"
                    "sll        $v0, $s7, 24\n"
                    "sra        $v1, $v0, 24\n"
                    "slti       $v0, $v1, 0x3\n"
                    "beqz       $v0, 1f\n"
                    "ori       $t3, $zero, 0x3\n"
                    "bgtz       $v1, 4f\n"
                    "ori       $t3, $zero, 0x4C\n"
                    "beqz       $v1, 2f\n"
                    "ori       $t4, $zero, 0x142\n"
                    "j          9f\n"
                    "nop\n"
                    "1:\n"
                    "bne        $v1, $t3, 9f\n"
                    "ori       $t4, $zero, 0x142\n"
                    "2:\n"
                    "ori        $t3, $zero, 0x2\n"
                    "addiu      $fp, $zero, -0xA1\n"
                    "sll        $v0, $s7, 24\n"
                    "sw         $t4, 0x28($sp)\n"
                    "bnez       $v0, 3f\n"
                    "sw        $t3, 0x30($sp)\n"
                    "j          9f\n"
                    "addiu     $s4, $s3, 0x1\n"
                    "3:\n"
                    "j          9f\n"
                    "addiu     $s4, $s3, 0x4D\n"
                    "4:\n"
                    "ori        $t4, $zero, 0x2\n"
                    "addiu      $s4, $s3, 0x2\n"
                    "ori        $fp, $zero, 0xA0\n"
                    "sw         $t4, 0x28($sp)\n"
                    "ori        $t4, $zero, 0x1\n"
                    "bne        $v1, $t4, 9f\n"
                    "sw        $t3, 0x30($sp)\n"
                    "addiu      $fp, $zero, -0xA2\n"
                    "9:\n"
                    "lbu        $v1, D_800A35EC\n"
                    "lw         $a1, D_800A3678\n"
                    "addiu      $v0, $v1, 0x1\n"
                    "sb         $v0, D_800A35EC\n"
                    "sll        $v0, $v1, 3\n"
                    "addu       $v0, $v0, $v1\n"
                    "sll        $v0, $v0, 2\n"
                    "addu       $s2, $a1, $v0\n"
                    "ori        $t3, $zero, 0x2\n"
                    "sh         $zero, 0x12($s2)\n"
                    "sh         $zero, 0x14($s2)\n"
                    "sw         $zero, 0x1C($s2)\n"
                    "sb         $zero, 0x4($s2)\n"
                    "sb         $zero, 0x3($s2)\n"
                    "sb         $zero, 0x2($s2)\n"
                    "sh         $zero, 0x1A($s2)\n"
                    "sh         $t3, 0x0($s2)\n"
                    "sh         $zero, 0x6($s2)\n"
                    "sh         $zero, 0xA($s2)\n"
                    "sh         $zero, 0x8($s2)\n"
                    "sh         $zero, 0xC($s2)\n"
                    "sh         $zero, 0xE($s2)\n"
                    "sh         $zero, 0x10($s2)\n"
                    "lhu        $t4, 0x28($sp)\n"
                    "nop\n"
                    "sh         $t4, 0x16($s2)\n"
                    "lhu        $t3, 0x30($sp)\n"
                    "ori        $a0, $zero, 0x1\n"
                    "sb         $s1, 0x2($s2)\n"
                    "sb         $s1, 0x3($s2)\n"
                    "sb         $s1, 0x4($s2)\n"
                    "jal        func_80057D50\n"
                    "sh        $t3, 0x18($s2)\n"
                    "addu       $s0, $v0, $zero\n"
                    "addu       $a0, $s0, $zero\n"
                    "jal        SetPolyF4\n"
                    "sw        $s0, 0x20($s2)\n"
                    "addu       $a0, $s0, $zero\n"
                    "jal        SetSemiTrans\n"
                    "addu      $a1, $zero, $zero\n"
                    "sb         $s1, 0x4($s0)\n"
                    "sb         $s1, 0x5($s0)\n"
                    "sb         $s1, 0x6($s0)\n"
                    "sh         $zero, 0x8($s0)\n"
                    "sh         $zero, 0xA($s0)\n"
                    "lhu        $v1, 0x28($sp)\n"
                    "sh         $zero, 0xE($s0)\n"
                    "sh         $zero, 0x10($s0)\n"
                    "sh         $v1, 0xC($s0)\n"
                    "lhu        $v0, 0x30($sp)\n"
                    "addu       $s6, $s2, $zero\n"
                    "sh         $v1, 0x14($s0)\n"
                    "sh         $v0, 0x12($s0)\n"
                    "sh         $v0, 0x16($s0)\n"
                    "ori        $t4, $zero, 0x3\n"
                    "sh         $t4, 0x1A($s6)\n"
                    "sh $fp,0x12($s6)\n"
                    "sh $s4,0x14($s6)\n"
                    "sw $s6,0x1c($s5)\n"
                    ".set\treorder\n"
                    : "=r"(currentNode), "=m"(packetWidth.value),
                      "=m"(packetHeight.value), "=r"(panelState)
                    : "r"(borderIndex), "r"(borderYBase), "r"(tone),
                      "r"(previousNode)
                    /* These three verified leaf callees preserve the other GPRs and HI/LO. */
                    : "$2", "$3", "$4", "$5", "$11", "$12", "$16", "$20", "$30",
                      "$31", "memory");
                asm volatile("addiu $v0,$s7,1\n"
                             "addu $s7,$v0,$zero\n"
                             "sll $v0,$v0,24\n"
                             "sra $v0,$v0,24\n"
                             "slti $v0,$v0,4\n"
                             ".set\treorder\n"
                             : "=r"(borderIndex), "=r"(loopCondition)
                             : "0"(borderIndex)
                             : "memory");
                previousNode = currentNode;
            } while (loopCondition != 0);
        }
        {
            register s32 textWord asm("$5");
            /* Header texture and two black quads share allocation registers. */
            asm volatile(".set\tnoreorder\n"
                         "ori        $a1, $zero, 0x74\n"
                         "lbu        $v1, D_800A35EC\n"
                         "lw         $s1, D_800A3678\n"
                         "ori        $a0, $zero, 0x1\n"
                         "addiu      $v0, $v1, 0x1\n"
                         "sb         $v0, D_800A35EC\n"
                         "sll        $v0, $v1, 3\n"
                         "addu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $s1, $s1, $v0\n"
                         "ori        $t3, $zero, 0x1\n"
                         "ori        $v0, $zero, 0x50\n"
                         "sh         $zero, 0x12($s1)\n"
                         "sh         $zero, 0x14($s1)\n"
                         "sw         $zero, 0x1C($s1)\n"
                         "sb         $zero, 0x4($s1)\n"
                         "sb         $zero, 0x3($s1)\n"
                         "sb         $zero, 0x2($s1)\n"
                         "sh         $zero, 0x1A($s1)\n"
                         "sh         $t3, 0x0($s1)\n"
                         "sh         $zero, 0xA($s1)\n"
                         "sh         $zero, 0x6($s1)\n"
                         "sh         $zero, 0xC($s1)\n"
                         "sh         $zero, 0x8($s1)\n"
                         "sh         $a1, 0x16($s1)\n"
                         "sh         $v0, 0x18($s1)\n"
                         "sh         $zero, 0xE($s1)\n"
                         "jal        func_80057CCC\n"
                         "sh        $zero, 0x10($s1)\n"
                         "addu       $s0, $v0, $zero\n"
                         "jal        SetPolyFT4\n"
                         "addu      $a0, $s0, $zero\n"
                         "addu       $a0, $s0, $zero\n"
                         "jal        SetShadeTex\n"
                         "addu      $a1, $zero, $zero\n"
                         "addu       $a0, $s0, $zero\n"
                         "addu       $a1, $zero, $zero\n"
                         "ori        $v0, $zero, 0x80\n"
                         "sb         $v0, 0x4($s0)\n"
                         "sb         $v0, 0x5($s0)\n"
                         "jal        SetSemiTrans\n"
                         "sb        $v0, 0x6($s0)\n"
                         "addu       $s6, $s1, $zero\n"
                         "ori        $t4, $zero, 0x2\n"
                         "addiu      $v0, $zero, -0x3A\n"
                         "sw         $s0, 0x20($s1)\n"
                         "sh         $t4, 0x1A($s1)\n"
                         "sh         $v0, 0x12($s6)\n"
                         "lbu        $t3, %6\n"
                         "lbu        $v1, D_800A35EC\n"
                         "sll        $s5, $t3, 24\n"
                         "sra        $s5, $s5, 24\n"
                         "sll        $v0, $s5, 2\n"
                         "addu       $s4, $v0, $s5\n"
                         "sll        $s4, $s4, 2\n"
                         "subu       $s4, $s4, $s5\n"
                         "sll        $s4, $s4, 2\n"
                         "sh         $s4, 0x14($s6)\n"
                         "sw         $s6, 0x1C($s2)\n"
                         "lw         $s2, D_800A3678\n"
                         "ori        $a0, $zero, 0x1\n"
                         "ori        $s3, $zero, 0x4\n"
                         "lui        $at, %%hi(D_800A3A1C)\n"
                         "addu       $at, $at, $v0\n"
                         "sw         $s6, %%lo(D_800A3A1C)($at)\n"
                         "addiu      $v0, $v1, 0x1\n"
                         "sb         $v0, D_800A35EC\n"
                         "sll        $v0, $v1, 3\n"
                         "addu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $s2, $s2, $v0\n"
                         "ori        $t3, $zero, 0x1\n"
                         "sh         $zero, 0x12($s2)\n"
                         "sh         $zero, 0x14($s2)\n"
                         "sw         $zero, 0x1C($s2)\n"
                         "sb         $zero, 0x4($s2)\n"
                         "sb         $zero, 0x3($s2)\n"
                         "sb         $zero, 0x2($s2)\n"
                         "sh         $zero, 0x1A($s2)\n"
                         "sh         $t4, 0x0($s2)\n"
                         "sh         $zero, 0x6($s2)\n"
                         "sh         $zero, 0xA($s2)\n"
                         "sh         $zero, 0x8($s2)\n"
                         "sh         $zero, 0xC($s2)\n"
                         "sh         $zero, 0xE($s2)\n"
                         "sh         $zero, 0x10($s2)\n"
                         "sh         $s3, 0x16($s2)\n"
                         "sh         $t3, 0x18($s2)\n"
                         "sb         $zero, 0x2($s2)\n"
                         "sb         $zero, 0x3($s2)\n"
                         "jal        func_80057D50\n"
                         "sb        $zero, 0x4($s2)\n"
                         "addu       $s0, $v0, $zero\n"
                         "addu       $a0, $s0, $zero\n"
                         "jal        SetPolyF4\n"
                         "sw        $s0, 0x20($s2)\n"
                         "addu       $a0, $s0, $zero\n"
                         "jal        SetSemiTrans\n"
                         "ori       $a1, $zero, 0x1\n"
                         "sb         $zero, 0x4($s0)\n"
                         "sb         $zero, 0x5($s0)\n"
                         "sb         $zero, 0x6($s0)\n"
                         "lbu        $v1, D_800A35EC\n"
                         "addu       $s7, $zero, $zero\n"
                         "addu       $s6, $s2, $zero\n"
                         "ori        $t4, $zero, 0x1\n"
                         "ori        $t3, $zero, 0x1\n"
                         "sh         $zero, 0x8($s0)\n"
                         "sh         $zero, 0xA($s0)\n"
                         "sh         $s3, 0xC($s0)\n"
                         "sh         $zero, 0xE($s0)\n"
                         "sh         $zero, 0x10($s0)\n"
                         "sh         $t4, 0x12($s0)\n"
                         "sh         $s3, 0x14($s0)\n"
                         "sh         $t3, 0x16($s0)\n"
                         "lw         $s0, D_800A3678\n"
                         "ori        $a0, $zero, 0x1\n"
                         "addiu      $v0, $zero, -0x2\n"
                         "sh         $v0, 0x12($s6)\n"
                         "addiu      $v0, $s4, 0x35\n"
                         "sh         $t4, 0x1A($s6)\n"
                         "sh         $v0, 0x14($s6)\n"
                         "sw         $s6, 0x1C($s1)\n"
                         "addiu      $v0, $v1, 0x1\n"
                         "sb         $v0, D_800A35EC\n"
                         "sll        $v0, $v1, 3\n"
                         "addu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $s0, $s0, $v0\n"
                         "ori        $t3, $zero, 0x2\n"
                         "ori        $t4, $zero, 0x140\n"
                         "sh         $zero, 0x12($s0)\n"
                         "sh         $zero, 0x14($s0)\n"
                         "sw         $zero, 0x1C($s0)\n"
                         "sb         $zero, 0x4($s0)\n"
                         "sb         $zero, 0x3($s0)\n"
                         "sb         $zero, 0x2($s0)\n"
                         "sh         $zero, 0x1A($s0)\n"
                         "sh         $t3, 0x0($s0)\n"
                         "sh         $zero, 0x6($s0)\n"
                         "sh         $zero, 0xA($s0)\n"
                         "sh         $zero, 0x8($s0)\n"
                         "sh         $zero, 0xC($s0)\n"
                         "sh         $zero, 0xE($s0)\n"
                         "sh         $zero, 0x10($s0)\n"
                         "ori        $t3, $zero, 0x4A\n"
                         "sh         $t4, 0x16($s0)\n"
                         "sh         $t3, 0x18($s0)\n"
                         "sb         $zero, 0x2($s0)\n"
                         "sb         $zero, 0x3($s0)\n"
                         "jal        func_80057D50\n"
                         "sb        $zero, 0x4($s0)\n"
                         "addu       $s1, $v0, $zero\n"
                         "addu       $a0, $s1, $zero\n"
                         "jal        SetPolyF4\n"
                         "sw        $s1, 0x20($s0)\n"
                         "addu       $a0, $s1, $zero\n"
                         "jal        SetSemiTrans\n"
                         "ori       $a1, $zero, 0x1\n"
                         "addu       $s6, $s0, $zero\n"
                         "ori        $a0, $zero, 0x2\n"
                         "ori        $a1, $zero, 0x2\n"
                         "ori        $t4, $zero, 0x140\n"
                         "ori        $t3, $zero, 0x4A\n"
                         "sh         $t4, 0xC($s1)\n"
                         "sh         $t3, 0x12($s1)\n"
                         "addiu      $v0, $zero, -0xA0\n"
                         "addiu      $s4, $s4, 0x3\n"
                         "sb         $zero, 0x4($s1)\n"
                         "sb         $zero, 0x5($s1)\n"
                         "sb         $zero, 0x6($s1)\n"
                         "sh         $zero, 0x8($s1)\n"
                         "sh         $zero, 0xA($s1)\n"
                         "sh         $zero, 0xE($s1)\n"
                         "sh         $zero, 0x10($s1)\n"
                         "sh         $t4, 0x14($s1)\n"
                         "sh         $t3, 0x16($s1)\n"
                         "sh         $zero, 0x1A($s6)\n"
                         "sh         $v0, 0x12($s6)\n"
                         "sh         $s4, 0x14($s6)\n"
                         "jal        func_8005A7B8\n"
                         "sw        $s6, 0x1C($s2)\n"
                         "lui        $a1, %%hi(D_8009A314)\n"
                         "lw         $a1, %%lo(D_8009A314)($a1)\n"
                         "addu       $s2, $s5, $zero\n"
                         "addu       $s5, $s6, $zero\n"
                         ".set\treorder\n"
                         : "=r"(currentNode), "=r"(previousNode),
                           "=r"(panelState), "=r"(textIndex), "=r"(textWord)
                         : "2"(panelState), "m"(panelIndex.value)
                         : "$2", "$3", "$4", "$11", "$12", "$16", "$17", "$19",
                           "$20", "$31", "memory");
            textCenterX = func_8005B0E4(0x140, textWord) - 0xA0;
        }
        asm volatile("" : "=r"(textCenterX) : "0"(textCenterX));
        textLeftX = textCenterX - 5;
    loopC:
        {
            register u8 *cell asm("$16");
            /* Text object and cell pools must be loaded independently. */
            asm volatile(".set\tnoreorder\n"
                         "lbu        $a0, D_800A35EC\n"
                         "lw         $v1, D_800A3678\n"
                         "addiu      $v0, $a0, 0x1\n"
                         "sb         $v0, D_800A35EC\n"
                         "sll        $v0, $a0, 3\n"
                         "addu       $v0, $v0, $a0\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $v1, $v1, $v0\n"
                         "sb         $zero, 0x4($v1)\n"
                         "sb         $zero, 0x3($v1)\n"
                         "sb         $zero, 0x2($v1)\n"
                         "lbu        $a0, D_800A37BC\n"
                         "addu       $s6, $v1, $zero\n"
                         "lw         $v1, D_800A3654\n"
                         "sh         $zero, 0x12($s6)\n"
                         "sh         $zero, 0x14($s6)\n"
                         "sw         $zero, 0x1C($s6)\n"
                         "sh         $zero, 0x1A($s6)\n"
                         "sh         $zero, 0x0($s6)\n"
                         "sh         $zero, 0xA($s6)\n"
                         "sh         $zero, 0x6($s6)\n"
                         "sh         $zero, 0xC($s6)\n"
                         "sh         $zero, 0x8($s6)\n"
                         "sh         $zero, 0xE($s6)\n"
                         "sh         $zero, 0x10($s6)\n"
                         "sh         $zero, 0x1A($s6)\n"
                         "addiu      $v0, $a0, 0x1\n"
                         "sb         $v0, D_800A37BC\n"
                         "sll        $v0, $a0, 1\n"
                         "addu       $v0, $v0, $a0\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $v1, $v1, $v0\n"
                         "sw         $v1, 0x20($s6)\n"
                         "sb         $zero, 0x0($v1)\n"
                         "sb         $zero, 0x3($v1)\n"
                         "sw         $zero, 0x4($v1)\n"
                         "lw         $s0, 0x20($s6)\n"
                         "ori        $t4, $zero, 0x1\n"
                         "sll        $v0, $s2, 2\n"
                         "addu       $v0, $v0, $s2\n"
                         "sll        $v0, $v0, 2\n"
                         "subu       $v0, $v0, $s2\n"
                         "sll        $v0, $v0, 2\n"
                         "addiu      $v0, $v0, 0x5\n"
                         "sh         $v0, 0x14($s6)\n"
                         "ori        $v0, $zero, 0x2\n"
                         "sh         $t4, 0x1A($s6)\n"
                         "sh         $s3, 0x12($s6)\n"
                         "sb         $v0, 0x2($s0)\n"
                         "sb         $v0, 0x1($s0)\n"
                         ".set\treorder\n"
                         : "=r"(currentNode), "=r"(cell)
                         : "r"(panelState), "r"(textLeftX)
                         : "$2", "$3", "$4", "$12", "memory");
            /* Each text arm retains its own word store and call delay. */
            asm volatile(".set\tnoreorder\n"
                         "sll        $v0, $s7, 24\n"
                         "beqz       $v0, 1f\n"
                         "sb        $zero, 0x3($s0)\n"
                         "lui        $a0, %%hi(D_8009A314)\n"
                         "lw         $a0, %%lo(D_8009A314)($a0)\n"
                         "jal        MenuStringWidth\n"
                         "nop\n"
                         "addu       $v0, $v0, $s1\n"
                         "sh         $v0, 0x12($s6)\n"
                         "ori        $v0, $zero, 0x5\n"
                         "sh         $v0, 0x0($s6)\n"
                         "ori        $t3, $zero, 0x1\n"
                         "j          2f\n"
                         "sw        $t3, 0x8($s0)\n"
                         "1:\n"
                         "sh         $s3, 0x12($s6)\n"
                         "lui        $v0, %%hi(D_8009A314)\n"
                         "lw         $v0, %%lo(D_8009A314)($v0)\n"
                         "nop\n"
                         "sw         $v0, 0x8($s0)\n"
                         "2:\n"
                         "sw         $s6, 0x1C($s5)\n"
                         ".set\treorder\n"
                         : "=x"(callAccumulator)
                         : "r"(textIndex), "r"(cell), "r"(currentNode),
                           "r"(textCenterX), "r"(textLeftX), "r"(previousNode)
                         : "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9",
                           "$10", "$11", "$31", "memory");
            {
                register s32 loopCondition asm("$2");
                asm volatile("addiu $v0,$s7,1\n"
                             "addu $s7,$v0,$zero\n"
                             "sll $v0,$v0,24\n"
                             "sra $v0,$v0,24\n"
                             "slti $v0,$v0,2\n"
                             ".set\treorder\n"
                             : "=r"(textIndex), "=r"(loopCondition)
                             : "0"(textIndex));
                previousNode = currentNode;
                if (loopCondition != 0) {
                    goto loopC;
                }
            }
        }

        {
            register s32 rowPanelIndex asm("$5");
            register s32 panelTimes20 asm("$10");
            register s32 rowX asm("$9");
            register s32 rowY asm("$8");
            register s32 rowMode asm("$6");
            register s32 rowAlign asm("$7");
            register s32 rowCondition asm("$3");
            register s32 sideCondition asm("$2");
            /* The copied row list starts at the verified local home sp+0x18. */
            asm volatile(".set\tnoreorder\n"
                         "lbu        $t4, %3\n"
                         "addu       $s7, $zero, $zero\n"
                         "sll        $v0, $t4, 24\n"
                         "sra        $a1, $v0, 24\n"
                         "sll        $v0, $a1, 2\n"
                         "addu       $v0, $v0, $a1\n"
                         "sll        $t2, $v0, 2\n"
                         ".set\treorder\n"
                         : "=r"(rowSide), "=r"(rowPanelIndex),
                           "=r"(panelTimes20)
                         : "m"(panelIndex.value)
                         : "$2", "$12");
            do {
                asm volatile(".set\tnoreorder\n"
                             "addu       $s2, $zero, $zero\n"
                             "sll        $a0, $s7, 24\n"
                             "sra        $a0, $a0, 24\n"
                             "sll        $v0, $a0, 1\n"
                             "addiu      $v0, $v0, -0x1\n"
                             "sll        $v1, $v0, 6\n"
                             "subu       $t1, $v1, $v0\n"
                             "subu       $v0, $t2, $a1\n"
                             "sll        $t0, $v0, 2\n"
                             "ori        $a2, $zero, 0x2\n"
                             "sltiu      $a0, $a0, 0x1\n"
                             "addu       $a3, $a0, $zero\n"
                             ".set\treorder\n"
                             : "=r"(rowItem), "=r"(rowX), "=r"(rowY),
                               "=r"(rowMode), "=r"(rowAlign)
                             : "r"(rowSide), "r"(rowPanelIndex),
                               "r"(panelTimes20)
                             : "$2", "$3", "$4");
                do {
                    /* Allocate one text cell, place it, then test the row counter. */
                    asm volatile(
                        ".set\tnoreorder\n"
                        "lbu        $a0, D_800A35EC\n"
                        "lw         $v1, D_800A3678\n"
                        "addiu      $v0, $a0, 0x1\n"
                        "sb         $v0, D_800A35EC\n"
                        "sll        $v0, $a0, 3\n"
                        "addu       $v0, $v0, $a0\n"
                        "sll        $v0, $v0, 2\n"
                        "addu       $v1, $v1, $v0\n"
                        "sb         $zero, 0x4($v1)\n"
                        "sb         $zero, 0x3($v1)\n"
                        "sb         $zero, 0x2($v1)\n"
                        "lbu        $a0, D_800A37BC\n"
                        "addu       $s6, $v1, $zero\n"
                        "lw         $v1, D_800A3654\n"
                        "sh         $zero, 0x12($s6)\n"
                        "sh         $zero, 0x14($s6)\n"
                        "sw         $zero, 0x1C($s6)\n"
                        "sh         $zero, 0x1A($s6)\n"
                        "sh         $zero, 0x0($s6)\n"
                        "sh         $zero, 0xA($s6)\n"
                        "sh         $zero, 0x6($s6)\n"
                        "sh         $zero, 0xC($s6)\n"
                        "sh         $zero, 0x8($s6)\n"
                        "sh         $zero, 0xE($s6)\n"
                        "sh         $zero, 0x10($s6)\n"
                        "sh         $zero, 0x1A($s6)\n"
                        "addiu      $v0, $a0, 0x1\n"
                        "sb         $v0, D_800A37BC\n"
                        "sll        $v0, $a0, 1\n"
                        "addu       $v0, $v0, $a0\n"
                        "sll        $v0, $v0, 2\n"
                        "addu       $v1, $v1, $v0\n"
                        "sw         $v1, 0x20($s6)\n"
                        "sb         $zero, 0x0($v1)\n"
                        "sb         $zero, 0x3($v1)\n"
                        "sw         $zero, 0x4($v1)\n"
                        "ori        $t3, $zero, 0x1\n"
                        "sll        $v0, $s2, 24\n"
                        "sra        $v0, $v0, 24\n"
                        "addu       $v0, $sp, $v0\n"
                        "sh         $t3, 0x1A($s6)\n"
                        "sh         $t1, 0x12($s6)\n"
                        "lbu        $v0, 0x18($v0)\n"
                        "addiu      $v1, $s2, 0x1\n"
                        "addu       $s2, $v1, $zero\n"
                        "lw         $s0, 0x20($s6)\n"
                        "sll        $v1, $v1, 24\n"
                        "sra        $v1, $v1, 24\n"
                        "slti       $v1, $v1, 0x7\n"
                        "sll        $v0, $v0, 24\n"
                        "sra        $v0, $v0, 24\n"
                        "addu       $v0, $v0, $t0\n"
                        "sh         $v0, 0x14($s6)\n"
                        "sb         $a2, 0x2($s0)\n"
                        "sb         $a3, 0x3($s0)\n"
                        "sb         $a2, 0x1($s0)\n"
                        "sw         $s6, 0x1C($s5)\n"
                        ".set\treorder\n"
                        : "=r"(currentNode), "=r"(rowItem), "=r"(rowCondition)
                        : "1"(rowItem), "r"(rowX), "r"(rowY), "r"(rowMode),
                          "r"(rowAlign), "r"(previousNode), "m"(rowList)
                        : "$2", "$4", "$11", "$16", "memory");
                    previousNode = currentNode;
                } while (rowCondition != 0);
                asm volatile(".set\tnoreorder\n"
                             "addiu      $v0, $s7, 0x1\n"
                             "addu       $s7, $v0, $zero\n"
                             "sll        $v0, $v0, 24\n"
                             "sra        $v0, $v0, 24\n"
                             "slti       $v0, $v0, 0x2\n"
                             ".set\treorder\n"
                             : "=r"(rowSide), "=r"(sideCondition)
                             : "0"(rowSide));
            } while (sideCondition != 0);
        }
        {
            /* Set the animation fields while walking the panel's node chain. */
            asm volatile(".set\tnoreorder\n"
                         "lbu        $t4, %2\n"
                         "lui        $t3, %%hi(D_800A37D8)\n"
                         "addiu      $t3, $t3, %%lo(D_800A37D8)\n"
                         "sll        $v0, $t4, 24\n"
                         "sra        $a0, $v0, 24\n"
                         "sll        $v1, $a0, 2\n"
                         "addu       $v0, $v1, $t3\n"
                         "lw         $s5, 0x0($v0)\n"
                         "ori        $t4, $zero, 0x2\n"
                         "beqz       $s5, 2f\n"
                         "subu      $a1, $t4, $v1\n"
                         "addu       $v0, $v1, $a0\n"
                         "sll        $a3, $v0, 6\n"
                         "sll        $v0, $a0, 1\n"
                         "addiu      $a2, $v0, -0x1\n"
                         "sll        $a0, $a1, 24\n"
                         "ori        $a1, $zero, 0xA0\n"
                         "1:\n"
                         "lh         $v0, 0x12($s5)\n"
                         "nop\n"
                         "addiu      $v0, $v0, 0xA2\n"
                         "mult       $a2, $v0\n"
                         "lw         $t3, %3\n"
                         "ori        $t4, $zero, 0x1\n"
                         "sb         $t4, 0x5($s5)\n"
                         "sh         $a1, 0xA($s5)\n"
                         "sra        $v1, $t3, 24\n"
                         "sra        $v0, $a0, 24\n"
                         "sh         $v1, 0x8($s5)\n"
                         "sh         $v0, 0xE($s5)\n"
                         "sh         $v1, 0xC($s5)\n"
                         "mflo       $t3\n"
                         "addu       $v0, $a3, $t3\n"
                         "sh         $v0, 0x6($s5)\n"
                         "lw         $s5, 0x1C($s5)\n"
                         "nop\n"
                         "bnez       $s5, 1b\n"
                         "nop\n"
                         "2:\n"
                         ".set\treorder\n"
                         : "=r"(previousNode), "=x"(callAccumulator)
                         : "m"(panelIndex.value), "m"(colorHome.value)
                         : "$2", "$3", "$4", "$5", "$6", "$7", "$11", "$12",
                           "memory");
        }
    walkDone:
        {
            register s32 textureOffset asm("$20");
            textureOffset = 0;
            MenuUpdatePadPicture((u8)panelIndex.value);
            /* Keep the texture cases, leaf calls, UV reloads, and links. */
            asm volatile(".set\tnoreorder\n"
                         "lw         $t4, %7\n"
                         "lbu        $t3, %8\n"
                         "addu       $s7, $zero, $zero\n"
                         "sra        $fp, $t4, 24\n"
                         "sll        $v0, $t3, 24\n"
                         "sra        $v0, $v0, 24\n"
                         "sll        $s3, $v0, 2\n"
                         "sw         $v0, %4\n"
                         ".LtextureStage80061A8C:\n"
                         "sll        $v0, $s7, 24\n"
                         "sra        $v1, $v0, 24\n"
                         "ori        $t4, $zero, 0x1\n"
                         "beq        $v1, $t4, .LtextureStage80061AD8\n"
                         "slti      $v0, $v1, 0x2\n"
                         "beqz       $v0, .LtextureStage80061AB8\n"
                         "nop\n"
                         "beqz       $v1, .LtextureStage80061ACC\n"
                         "ori       $t4, $zero, 0x2\n"
                         "j          .LtextureStage80061AF0\n"
                         "nop\n"
                         ".LtextureStage80061AB8:\n"
                         "ori        $t3, $zero, 0x2\n"
                         "beq        $v1, $t3, .LtextureStage80061AE8\n"
                         "ori       $t4, $zero, 0x3\n"
                         "j          .LtextureStage80061AF0\n"
                         "nop\n"
                         ".LtextureStage80061ACC:\n"
                         "sw         $t4, %2\n"
                         "j          .LtextureStage80061AF0\n"
                         "sw        $zero, %3\n"
                         ".LtextureStage80061AD8:\n"
                         "ori        $t3, $zero, 0x6\n"
                         "ori        $t4, $zero, 0x1\n"
                         "j          .LtextureStage80061AEC\n"
                         "sw        $t3, %2\n"
                         ".LtextureStage80061AE8:\n"
                         "sw         $t3, %2\n"
                         ".LtextureStage80061AEC:\n"
                         "sw         $t4, %3\n"
                         ".LtextureStage80061AF0:\n"
                         "lbu        $v1, D_800A35EC\n"
                         "lw         $s0, D_800A3678\n"
                         "addiu      $v0, $v1, 0x1\n"
                         "sb         $v0, D_800A35EC\n"
                         "sll        $v0, $v1, 3\n"
                         "addu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $s0, $s0, $v0\n"
                         "ori        $t3, $zero, 0x1\n"
                         "ori        $t4, $zero, 0x68\n"
                         "sh         $zero, 0x12($s0)\n"
                         "sh         $zero, 0x14($s0)\n"
                         "sw         $zero, 0x1C($s0)\n"
                         "sb         $zero, 0x4($s0)\n"
                         "sb         $zero, 0x3($s0)\n"
                         "sb         $zero, 0x2($s0)\n"
                         "sh         $zero, 0x1A($s0)\n"
                         "sh         $t3, 0x0($s0)\n"
                         "sh         $zero, 0xA($s0)\n"
                         "sh         $zero, 0x6($s0)\n"
                         "sh         $fp, 0xC($s0)\n"
                         "sh         $fp, 0x8($s0)\n"
                         "sh         $t4, 0x16($s0)\n"
                         "lhu        $t3, %2\n"
                         "ori        $a0, $zero, 0x1\n"
                         "sh         $zero, 0xE($s0)\n"
                         "sh         $zero, 0x10($s0)\n"
                         "jal        func_80057CCC\n"
                         "sh        $t3, 0x18($s0)\n"
                         "addu       $s1, $v0, $zero\n"
                         "jal        SetPolyFT4\n"
                         "addu      $a0, $s1, $zero\n"
                         "addu       $a0, $s1, $zero\n"
                         "jal        SetShadeTex\n"
                         "addu      $a1, $zero, $zero\n"
                         "addu       $a0, $s1, $zero\n"
                         "addu       $a1, $zero, $zero\n"
                         "ori        $v0, $zero, 0x80\n"
                         "sb         $v0, 0x4($s1)\n"
                         "sb         $v0, 0x5($s1)\n"
                         "jal        SetSemiTrans\n"
                         "sb        $v0, 0x6($s1)\n"
                         "addu       $s6, $s0, $zero\n"
                         "ori        $t4, $zero, 0x2\n"
                         "sll        $v0, $s7, 24\n"
                         "sw         $s1, 0x20($s6)\n"
                         "bnez       $v0, .LtextureStage80061BC4\n"
                         "sh        $t4, 0x1A($s6)\n"
                         "lui        $at, %%hi(D_800A3888)\n"
                         "addu       $at, $at, $s3\n"
                         "sw         $s6, %%lo(D_800A3888)($at)\n"
                         "j          .LtextureStage80061BC8\n"
                         "nop\n"
                         ".LtextureStage80061BC4:\n"
                         "sw         $s6, 0x1C($s5)\n"
                         ".LtextureStage80061BC8:\n"
                         "lw         $t3, %4\n"
                         "nop\n"
                         "beqz       $t3, .LtextureStage80061BE0\n"
                         "ori       $t4, $zero, 0x140\n"
                         "j          .LtextureStage80061BE8\n"
                         "sh        $t4, 0x6($s6)\n"
                         ".LtextureStage80061BE0:\n"
                         "addiu      $v0, $zero, -0x140\n"
                         "sh         $v0, 0x6($s6)\n"
                         ".LtextureStage80061BE8:\n"
                         "lui        $t3, %%hi(D_800A37D8)\n"
                         "addiu      $t3, $t3, %%lo(D_800A37D8)\n"
                         "addu       $v0, $s3, $t3\n"
                         "lw         $v0, 0x0($v0)\n"
                         "lw         $s2, 0x20($s6)\n"
                         "lhu        $v1, 0x14($v0)\n"
                         "ori        $t4, $zero, 0x1\n"
                         "ori        $v0, $zero, 0x78\n"
                         "sh         $v0, 0x12($s6)\n"
                         "addiu      $v0, %6, 0x3A\n"
                         "addu       $v1, $v1, $v0\n"
                         "sll        $v0, $s7, 24\n"
                         "sra        $v0, $v0, 24\n"
                         "bne        $v0, $t4, .LtextureStage80061D0C\n"
                         "sh        $v1, 0x14($s6)\n"
                         "lui        $a0, %%hi(D_8009AEA4)\n"
                         "lhu        $a0, %%lo(D_8009AEA4)($a0)\n"
                         "lui        $a1, %%hi(D_8009AEA6)\n"
                         "lhu        $a1, %%lo(D_8009AEA6)($a1)\n"
                         "lhu        $s0, 0x16($s6)\n"
                         "jal        GetClut\n"
                         "nop\n"
                         "sh         $v0, 0xE($s2)\n"
                         "lui        $a0, %%hi(D_8009AEAC)\n"
                         "lhu        $a0, %%lo(D_8009AEAC)($a0)\n"
                         "lui        $a2, %%hi(D_8009AEA0)\n"
                         "lhu        $a2, %%lo(D_8009AEA0)($a2)\n"
                         "lui        $a3, %%hi(D_8009AEA2)\n"
                         "lhu        $a3, %%lo(D_8009AEA2)($a3)\n"
                         "jal        GetTPage\n"
                         "ori       $a1, $zero, 0x3\n"
                         "sh         $v0, 0x16($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "sb         $v0, 0xC($s2)\n"
                         "lhu        $v1, %3\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "sb         $v0, 0xD($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $s0\n"
                         "sb         $v0, 0x14($s2)\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "sb         $v0, 0x15($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "sb         $v0, 0x1C($s2)\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "addiu      $v0, $v0, 0x1\n"
                         "sb         $v0, 0x1D($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $s0\n"
                         "sb         $v0, 0x24($s2)\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "j          .LtextureStage80061DF4\n"
                         "addiu     $v0, $v0, 0x1\n"
                         ".LtextureStage80061D0C:\n"
                         "lui        $a0, %%hi(D_8009AEA4)\n"
                         "lhu        $a0, %%lo(D_8009AEA4)($a0)\n"
                         "lui        $a1, %%hi(D_8009AEA6)\n"
                         "lhu        $a1, %%lo(D_8009AEA6)($a1)\n"
                         "lhu        $s0, 0x16($s6)\n"
                         "lhu        $s1, 0x18($s6)\n"
                         "jal        GetClut\n"
                         "nop\n"
                         "sh         $v0, 0xE($s2)\n"
                         "lui        $a0, %%hi(D_8009AEAC)\n"
                         "lhu        $a0, %%lo(D_8009AEAC)($a0)\n"
                         "lui        $a2, %%hi(D_8009AEA0)\n"
                         "lhu        $a2, %%lo(D_8009AEA0)($a2)\n"
                         "lui        $a3, %%hi(D_8009AEA2)\n"
                         "lhu        $a3, %%lo(D_8009AEA2)($a3)\n"
                         "jal        GetTPage\n"
                         "ori       $a1, $zero, 0x3\n"
                         "sh         $v0, 0x16($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "sb         $v0, 0xC($s2)\n"
                         "lhu        $v1, %3\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "sb         $v0, 0xD($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $s0\n"
                         "sb         $v0, 0x14($s2)\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "sb         $v0, 0x15($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "sb         $v0, 0x1C($s2)\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "addu       $v0, $v0, $s1\n"
                         "sb         $v0, 0x1D($s2)\n"
                         "lui        $v0, %%hi(D_8009AEA8)\n"
                         "lbu        $v0, %%lo(D_8009AEA8)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $s0\n"
                         "sb         $v0, 0x24($s2)\n"
                         "lui        $v0, %%hi(D_8009AEAA)\n"
                         "lbu        $v0, %%lo(D_8009AEAA)($v0)\n"
                         "nop\n"
                         "addu       $v0, $v0, $v1\n"
                         "addu       $v0, $v0, $s1\n"
                         ".LtextureStage80061DF4:\n"
                         "sb         $v0, 0x25($s2)\n"
                         "lh         $v1, 0x18($s6)\n"
                         "addu       $s5, $s6, $zero\n"
                         "addiu      $v0, $s7, 0x1\n"
                         "addu       $s7, $v0, $zero\n"
                         "sll        $v0, $v0, 24\n"
                         "sra        $v0, $v0, 24\n"
                         "slti       $v0, $v0, 0x3\n"
                         "bnez       $v0, .LtextureStage80061A8C\n"
                         "addu      %6, %6, $v1\n"
                         "lw         $t3, %7\n"
                         "lbu        $t4, %8\n"
                         "addu       $s7, $zero, $zero\n"
                         "lui        $s3, %%hi(D_8009AEB2)\n"
                         "addiu      $s3, $s3, %%lo(D_8009AEB2)\n"
                         "sra        %6, $t3, 24\n"
                         "sll        $v0, $t4, 24\n"
                         "sra        $fp, $v0, 24\n"
                         "sll        $t3, $fp, 2\n"
                         "sw         $t3, %5\n"
                         ".LtextureStage80061E44:\n"
                         "lbu        $v1, D_800A35EC\n"
                         "lw         $s0, D_800A3678\n"
                         "ori        $a0, $zero, 0x1\n"
                         "addiu      $v0, $v1, 0x1\n"
                         "sb         $v0, D_800A35EC\n"
                         "sll        $v0, $v1, 3\n"
                         "addu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $s0, $s0, $v0\n"
                         "ori        $t4, $zero, 0x1\n"
                         "ori        $t3, $zero, 0xE\n"
                         "sh         $t4, 0x0($s0)\n"
                         "ori        $t4, $zero, 0x32\n"
                         "sh         $zero, 0x12($s0)\n"
                         "sh         $zero, 0x14($s0)\n"
                         "sw         $zero, 0x1C($s0)\n"
                         "sb         $zero, 0x4($s0)\n"
                         "sb         $zero, 0x3($s0)\n"
                         "sb         $zero, 0x2($s0)\n"
                         "sh         $zero, 0x1A($s0)\n"
                         "sh         $zero, 0xA($s0)\n"
                         "sh         $zero, 0x6($s0)\n"
                         "sh         %6, 0xC($s0)\n"
                         "sh         %6, 0x8($s0)\n"
                         "sh         $t3, 0x16($s0)\n"
                         "sh         $t4, 0x18($s0)\n"
                         "sh         $zero, 0xE($s0)\n"
                         "jal        func_80057CCC\n"
                         "sh        $zero, 0x10($s0)\n"
                         "addu       $s1, $v0, $zero\n"
                         "jal        SetPolyFT4\n"
                         "addu      $a0, $s1, $zero\n"
                         "addu       $a0, $s1, $zero\n"
                         "jal        SetShadeTex\n"
                         "addu      $a1, $zero, $zero\n"
                         "addu       $a0, $s1, $zero\n"
                         "addu       $a1, $zero, $zero\n"
                         "ori        $v0, $zero, 0x80\n"
                         "sb         $v0, 0x4($s1)\n"
                         "sb         $v0, 0x5($s1)\n"
                         "jal        SetSemiTrans\n"
                         "sb        $v0, 0x6($s1)\n"
                         "addu       $s6, $s0, $zero\n"
                         "ori        $t3, $zero, 0x2\n"
                         "sw         $s1, 0x20($s6)\n"
                         "beqz       $fp, .LtextureStage80061F0C\n"
                         "sh        $t3, 0x1A($s6)\n"
                         "ori        $t4, $zero, 0x140\n"
                         "j          .LtextureStage80061F14\n"
                         "sh        $t4, 0x6($s6)\n"
                         ".LtextureStage80061F0C:\n"
                         "addiu      $v0, $zero, -0x140\n"
                         "sh         $v0, 0x6($s6)\n"
                         ".LtextureStage80061F14:\n"
                         "sll        $v0, $s7, 24\n"
                         "sra        $v0, $v0, 19\n"
                         "addiu      $v0, $v0, 0xFA\n"
                         "sh         $v0, 0x12($s6)\n"
                         "lw         $t3, %5\n"
                         "lui        $t4, %%hi(D_800A37D8)\n"
                         "addiu      $t4, $t4, %%lo(D_800A37D8)\n"
                         "addu       $v0, $t3, $t4\n"
                         "lw         $v0, 0x0($v0)\n"
                         "nop\n"
                         "lhu        $v0, 0x14($v0)\n"
                         "nop\n"
                         "addiu      $v0, $v0, 0x7\n"
                         "sh         $v0, 0x14($s6)\n"
                         "lhu        $a0, 0x0($s3)\n"
                         "lhu        $a1, 0x2($s3)\n"
                         "lw         $s2, 0x20($s6)\n"
                         "jal        GetClut\n"
                         "nop\n"
                         "sh         $v0, 0xE($s2)\n"
                         "lhu        $a0, 0x8($s3)\n"
                         "lhu        $a2, -0x4($s3)\n"
                         "lhu        $a3, -0x2($s3)\n"
                         "jal        GetTPage\n"
                         "addu      $a1, $zero, $zero\n"
                         "sh         $v0, 0x16($s2)\n"
                         "lhu        $v0, 0x4($s3)\n"
                         "nop\n"
                         "sb         $v0, 0xC($s2)\n"
                         "lbu        $v0, 0x6($s3)\n"
                         "nop\n"
                         "addiu      $v0, $v0, 0x6\n"
                         "sb         $v0, 0xD($s2)\n"
                         "lhu        $v0, 0x4($s3)\n"
                         "nop\n"
                         "sb         $v0, 0x14($s2)\n"
                         "lhu        $v0, 0x6($s3)\n"
                         "nop\n"
                         "sb         $v0, 0x15($s2)\n"
                         "lbu        $v0, 0x4($s3)\n"
                         "nop\n"
                         "addiu      $v0, $v0, 0x32\n"
                         "sb         $v0, 0x1C($s2)\n"
                         "lbu        $v0, 0x6($s3)\n"
                         "nop\n"
                         "addiu      $v0, $v0, 0x6\n"
                         "sb         $v0, 0x1D($s2)\n"
                         "lbu        $v0, 0x4($s3)\n"
                         "nop\n"
                         "addiu      $v0, $v0, 0x32\n"
                         "sb         $v0, 0x24($s2)\n"
                         "lhu        $v1, 0x6($s3)\n"
                         "addiu      $v0, $s7, 0x1\n"
                         "addu       $s7, $v0, $zero\n"
                         "sll        $v0, $v0, 24\n"
                         "sra        $v0, $v0, 24\n"
                         "slti       $v0, $v0, 0x2\n"
                         "sb         $v1, 0x25($s2)\n"
                         "sw         $s6, 0x1C($s5)\n"
                         "bnez       $v0, .LtextureStage80061E44\n"
                         "addu      $s5, $s6, $zero\n"
                         ".set\treorder\n"
                         : "=r"(currentNode), "=r"(previousNode),
                           "=m"(packetHeight.value), "=m"(textureRow.value),
                           "=m"(stripPanel.value), "=m"(sideOffset.value),
                           "=r"(textureOffset)
                         : "m"(colorHome.value), "m"(panelIndex.value),
                           "r"(textureOffset)
                         : "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$11",
                           "$12", "$16", "$17", "$18", "$19", "$23", "$30",
                           "$31", "memory");
        }
        {
            /* The leaf setter reads its fifth and sixth arguments here. */
            asm volatile(
                ".set\tnoreorder\n"
                "lbu        $a0, D_800A35EC\n"
                "lw         $v1, D_800A3678\n"
                "addiu      $v0, $a0, 0x1\n"
                "sb         $v0, D_800A35EC\n"
                "sll        $v0, $a0, 3\n"
                "addu       $v0, $v0, $a0\n"
                "sll        $v0, $v0, 2\n"
                "addu       $v1, $v1, $v0\n"
                "sb         $zero, 0x4($v1)\n"
                "sb         $zero, 0x3($v1)\n"
                "sb         $zero, 0x2($v1)\n"
                "lbu        $a0, D_800A37BC\n"
                "addu       $s6, $v1, $zero\n"
                "sh         $zero, 0x12($s6)\n"
                "sh         $zero, 0x14($s6)\n"
                "sw         $zero, 0x1C($s6)\n"
                "sh         $zero, 0x1A($s6)\n"
                "sh         $zero, 0x0($s6)\n"
                "sh         $zero, 0xA($s6)\n"
                "sh         $zero, 0x6($s6)\n"
                "lw         $t3, %4\n"
                "lw         $v1, D_800A3654\n"
                "sh         $zero, 0xE($s6)\n"
                "sh         $zero, 0x10($s6)\n"
                "sh         $zero, 0x1A($s6)\n"
                "sra        $v0, $t3, 24\n"
                "sh         $v0, 0xC($s6)\n"
                "sh         $v0, 0x8($s6)\n"
                "addiu      $v0, $a0, 0x1\n"
                "sb         $v0, D_800A37BC\n"
                "sll        $v0, $a0, 1\n"
                "addu       $v0, $v0, $a0\n"
                "sll        $v0, $v0, 2\n"
                "addu       $v1, $v1, $v0\n"
                "sw         $v1, 0x20($s6)\n"
                "sb         $zero, 0x0($v1)\n"
                "sb         $zero, 0x3($v1)\n"
                "sw         $zero, 0x4($v1)\n"
                "lbu        $t4, %5\n"
                "nop\n"
                "sll        $v0, $t4, 24\n"
                "beqz       $v0, .LlabelStage800620BC\n"
                "ori       $t3, $zero, 0x140\n"
                "j          .LlabelStage800620C4\n"
                "sh        $t3, 0x6($s6)\n"
                ".LlabelStage800620BC:\n"
                "addiu      $v0, $zero, -0x140\n"
                "sh         $v0, 0x6($s6)\n"
                ".LlabelStage800620C4:\n"
                "ori        $v0, $zero, 0x8\n"
                "sh         $v0, 0x12($s6)\n"
                "lbu        $t4, %5\n"
                "lui        $t3, %%hi(D_800A37D8)\n"
                "addiu      $t3, $t3, %%lo(D_800A37D8)\n"
                "sll        $v1, $t4, 24\n"
                "sra        $v1, $v1, 24\n"
                "sll        $s0, $v1, 2\n"
                "addu       $t0, $s0, $t3\n"
                "lw         $v0, 0x0($t0)\n"
                "addu       $a0, $s6, $zero\n"
                "lhu        $v0, 0x14($v0)\n"
                "ori        $a1, $zero, 0x2\n"
                "ori        $a2, $zero, 0x2\n"
                "addu       $s7, $zero, $zero\n"
                "addiu      $v0, $v0, 0x5\n"
                "sh         $v0, 0x14($s6)\n"
                "lui        $a3, %%hi(D_8009AC08)\n"
                "lw         $a3, %%lo(D_8009AC08)($a3)\n"
                "lw         $t4, %4\n"
                "addu       $s3, $v1, $zero\n"
                "addu       $s1, $t0, $zero\n"
                "ori        $t3, $zero, 0x1\n"
                "sw         $zero, %2\n"
                "sw         $t3, %3\n"
                "jal        func_80067EA4\n"
                "sra       $s2, $t4, 24\n"
                "sw         $s6, 0x1C($s5)\n"
                "addu       $s5, $s6, $zero\n"
                "lui        $at, %%hi(D_800A3A84)\n"
                "addu       $at, $at, $s0\n"
                "sw         $s5, %%lo(D_800A3A84)($at)\n"
                ".LlabelStage80062144:\n"
                "lbu        $a0, D_800A35EC\n"
                "lw         $v1, D_800A3678\n"
                "addiu      $v0, $a0, 0x1\n"
                "sb         $v0, D_800A35EC\n"
                "sll        $v0, $a0, 3\n"
                "addu       $v0, $v0, $a0\n"
                "sll        $v0, $v0, 2\n"
                "addu       $v1, $v1, $v0\n"
                "sb         $zero, 0x4($v1)\n"
                "sb         $zero, 0x3($v1)\n"
                "sb         $zero, 0x2($v1)\n"
                "lbu        $a0, D_800A37BC\n"
                "addu       $s6, $v1, $zero\n"
                "lw         $v1, D_800A3654\n"
                "sh         $zero, 0x12($s6)\n"
                "sh         $zero, 0x14($s6)\n"
                "sw         $zero, 0x1C($s6)\n"
                "sh         $zero, 0x1A($s6)\n"
                "sh         $zero, 0x0($s6)\n"
                "sh         $zero, 0xA($s6)\n"
                "sh         $zero, 0x6($s6)\n"
                "sh         $s2, 0xC($s6)\n"
                "sh         $s2, 0x8($s6)\n"
                "sh         $zero, 0xE($s6)\n"
                "sh         $zero, 0x10($s6)\n"
                "sh         $zero, 0x1A($s6)\n"
                "addiu      $v0, $a0, 0x1\n"
                "sb         $v0, D_800A37BC\n"
                "sll        $v0, $a0, 1\n"
                "addu       $v0, $v0, $a0\n"
                "sll        $v0, $v0, 2\n"
                "addu       $v1, $v1, $v0\n"
                "sw         $v1, 0x20($s6)\n"
                "sb         $zero, 0x0($v1)\n"
                "sb         $zero, 0x3($v1)\n"
                "beqz       $s3, .LlabelStage800621E4\n"
                "sw        $zero, 0x4($v1)\n"
                "ori        $t4, $zero, 0x140\n"
                "j          .LlabelStage800621EC\n"
                "sh        $t4, 0x6($s6)\n"
                ".LlabelStage800621E4:\n"
                "addiu      $v0, $zero, -0x140\n"
                "sh         $v0, 0x6($s6)\n"
                ".LlabelStage800621EC:\n"
                "sll        $v0, $s7, 24\n"
                "sra        $v1, $v0, 24\n"
                "beqz       $v1, .LlabelStage80062210\n"
                "ori       $v0, $zero, 0x46\n"
                "bltz       $v1, .LlabelStage8006222C\n"
                "slti      $v0, $v1, 0x3\n"
                "beqz       $v0, .LlabelStage8006222C\n"
                "sll       $v0, $v1, 5\n"
                "addiu      $v0, $v0, 0xD5\n"
                ".LlabelStage80062210:\n"
                "sh         $v0, 0x12($s6)\n"
                "lw         $v0, 0x0($s1)\n"
                "nop\n"
                "lhu        $v0, 0x14($v0)\n"
                "nop\n"
                "addiu      $v0, $v0, 0x3C\n"
                "sh         $v0, 0x14($s6)\n"
                ".LlabelStage8006222C:\n"
                "ori        $t3, $zero, 0x1\n"
                "sll        $v0, $s7, 24\n"
                "sra        $v0, $v0, 22\n"
                "sw         $zero, %2\n"
                "sw         $t3, %3\n"
                "lui        $at, %%hi(D_8009AC10)\n"
                "addu       $at, $at, $v0\n"
                "lw         $a3, %%lo(D_8009AC10)($at)\n"
                "addu       $a0, $s6, $zero\n"
                "ori        $a1, $zero, 0x2\n"
                "jal        func_80067EA4\n"
                "ori       $a2, $zero, 0x2\n"
                "sw         $s6, 0x1C($s5)\n"
                "addiu      $v0, $s7, 0x1\n"
                "addu       $s7, $v0, $zero\n"
                "sll        $v0, $v0, 24\n"
                "sra        $v0, $v0, 24\n"
                "slti       $v0, $v0, 0x3\n"
                "bnez       $v0, .LlabelStage80062144\n"
                "addu      $s5, $s6, $zero\n"
                ".set\treorder\n"
                : "=r"(currentNode), "=r"(previousNode), "=m"(labelArgs.fifth),
                  "=m"(labelArgs.sixth)
                : "m"(colorHome.value), "m"(panelIndex.value), "1"(previousNode)
                : "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$11", "$12",
                  "$16", "$17", "$18", "$19", "$23", "$31", "memory");
        }
        {
            /* Allocate and place the tall red marker and its two thin rows.
             * The shared column offset stays inside this block in hardware FP. */
            asm volatile(
                ".set\tnoreorder\n"
                "lbu        $v1, D_800A35EC\n"
                "lw         $s0, D_800A3678\n"
                "ori        $a0, $zero, 0x1\n"
                "addiu      $v0, $v1, 0x1\n"
                "sb         $v0, D_800A35EC\n"
                "sll        $v0, $v1, 3\n"
                "addu       $v0, $v0, $v1\n"
                "sll        $v0, $v0, 2\n"
                "addu       $s0, $s0, $v0\n"
                "ori        $v0, $zero, 0x2\n"
                "sh         $zero, 0x12($s0)\n"
                "sh         $zero, 0x14($s0)\n"
                "sw         $zero, 0x1C($s0)\n"
                "sb         $zero, 0x4($s0)\n"
                "sb         $zero, 0x3($s0)\n"
                "sb         $zero, 0x2($s0)\n"
                "sh         $zero, 0x1A($s0)\n"
                "sh         $v0, 0x0($s0)\n"
                "sh         $zero, 0x6($s0)\n"
                "sh         $zero, 0xA($s0)\n"
                "lw         $t4, %5\n"
                "ori        $s4, $zero, 0x6\n"
                "ori        $s3, $zero, 0x80\n"
                "ori        $v0, $zero, 0x8\n"
                "sh         $zero, 0xE($s0)\n"
                "sh         $zero, 0x10($s0)\n"
                "sh         $s4, 0x16($s0)\n"
                "sh         $v0, 0x18($s0)\n"
                "sb         $s3, 0x2($s0)\n"
                "sb         $zero, 0x3($s0)\n"
                "sb         $zero, 0x4($s0)\n"
                "sra        $s2, $t4, 24\n"
                "sh         $s2, 0x8($s0)\n"
                "jal        func_80057D50\n"
                "sh        $s2, 0xC($s0)\n"
                "addu       $s1, $v0, $zero\n"
                "addu       $a0, $s1, $zero\n"
                "jal        SetPolyF4\n"
                "sw        $s1, 0x20($s0)\n"
                "addu       $a0, $s1, $zero\n"
                "jal        SetSemiTrans\n"
                "addu      $a1, $zero, $zero\n"
                "addu       $s6, $s0, $zero\n"
                "sh         $s2, 0xA($s1)\n"
                "sh         $s2, 0xE($s1)\n"
                "addiu      $s2, $s2, 0x8\n"
                "sb         $s3, 0x4($s1)\n"
                "sb         $zero, 0x5($s1)\n"
                "sb         $zero, 0x6($s1)\n"
                "sh         $zero, 0x8($s1)\n"
                "sh         $s4, 0xC($s1)\n"
                "sh         $zero, 0x10($s1)\n"
                "sh         $s2, 0x12($s1)\n"
                "sh         $s4, 0x14($s1)\n"
                "sh         $s2, 0x16($s1)\n"
                "sh         $zero, 0x1A($s6)\n"
                "lbu        $t3, %4\n"
                "nop\n"
                "sll        $v0, $t3, 24\n"
                "beqz       $v0, 1f\n"
                "ori       $t4, $zero, 0x140\n"
                "j          2f\n"
                "sh        $t4, 0x6($s6)\n"
                "1:\n"
                "addiu      $v0, $zero, -0x140\n"
                "sh         $v0, 0x6($s6)\n"
                "2:\n"
                "ori        $v0, $zero, 0xA9\n"
                "sh         $v0, 0x12($s6)\n"
                "lbu        $t3, %4\n"
                "lui        $t4, %%hi(D_800A37D8)\n"
                "addiu      $t4, $t4, %%lo(D_800A37D8)\n"
                "sll        $v1, $t3, 24\n"
                "sra        $v1, $v1, 24\n"
                "sll        $a0, $v1, 2\n"
                "addu       $v0, $a0, $t4\n"
                "lw         $v0, 0x0($v0)\n"
                "addu       $s7, $zero, $zero\n"
                "lw         $t3, %5\n"
                "ori        $s4, $zero, 0xB\n"
                "lhu        $v0, 0x14($v0)\n"
                "addu       $fp, $a0, $zero\n"
                "sra        $s2, $t3, 24\n"
                "addiu      $s3, $s2, 0x1\n"
                "sw         $v1, %2\n"
                "addiu      $v0, $v0, 0x3B\n"
                "sh         $v0, 0x14($s6)\n"
                "sw         $s6, 0x1C($s5)\n"
                "addu       $s5, $s6, $zero\n"
                "lui        $at, %%hi(D_800A37FC)\n"
                "addu       $at, $at, $fp\n"
                "sw         $s5, %%lo(D_800A37FC)($at)\n"
                "3:\n"
                "lbu        $v1, D_800A35EC\n"
                "lw         $s0, D_800A3678\n"
                "ori        $a0, $zero, 0x1\n"
                "addiu      $v0, $v1, 0x1\n"
                "sb         $v0, D_800A35EC\n"
                "sll        $v0, $v1, 3\n"
                "addu       $v0, $v0, $v1\n"
                "sll        $v0, $v0, 2\n"
                "addu       $s0, $s0, $v0\n"
                "ori        $v0, $zero, 0x2\n"
                "ori        $t4, $zero, 0x1\n"
                "sb         $zero, 0x2($s0)\n"
                "ori        $t3, $zero, 0x80\n"
                "sh         $zero, 0x12($s0)\n"
                "sh         $zero, 0x14($s0)\n"
                "sw         $zero, 0x1C($s0)\n"
                "sb         $zero, 0x4($s0)\n"
                "sb         $zero, 0x3($s0)\n"
                "sh         $zero, 0x1A($s0)\n"
                "sh         $v0, 0x0($s0)\n"
                "sh         $zero, 0x6($s0)\n"
                "sh         $zero, 0xA($s0)\n"
                "sh         $s2, 0x8($s0)\n"
                "sh         $s2, 0xC($s0)\n"
                "sh         $zero, 0xE($s0)\n"
                "sh         $zero, 0x10($s0)\n"
                "sh         $s4, 0x16($s0)\n"
                "sh         $t4, 0x18($s0)\n"
                "sb         $t3, 0x2($s0)\n"
                "sb         $zero, 0x3($s0)\n"
                "jal        func_80057D50\n"
                "sb        $zero, 0x4($s0)\n"
                "addu       $s1, $v0, $zero\n"
                "addu       $a0, $s1, $zero\n"
                "jal        SetPolyF4\n"
                "sw        $s1, 0x20($s0)\n"
                "addu       $a0, $s1, $zero\n"
                "jal        SetSemiTrans\n"
                "addu      $a1, $zero, $zero\n"
                "addu       $s6, $s0, $zero\n"
                "ori        $t4, $zero, 0x80\n"
                "sb         $t4, 0x4($s1)\n"
                "sb         $zero, 0x5($s1)\n"
                "sb         $zero, 0x6($s1)\n"
                "sh         $zero, 0x8($s1)\n"
                "sh         $s2, 0xA($s1)\n"
                "sh         $s4, 0xC($s1)\n"
                "sh         $s2, 0xE($s1)\n"
                "sh         $zero, 0x10($s1)\n"
                "sh         $s3, 0x12($s1)\n"
                "sh         $s4, 0x14($s1)\n"
                "sh         $s3, 0x16($s1)\n"
                "sh         $zero, 0x1A($s6)\n"
                "lw         $t3, %2\n"
                "nop\n"
                "beqz       $t3, 4f\n"
                "ori       $t4, $zero, 0x140\n"
                "j          5f\n"
                "sh        $t4, 0x6($s6)\n"
                "4:\n"
                "addiu      $v0, $zero, -0x140\n"
                "sh         $v0, 0x6($s6)\n"
                "5:\n"
                "sll        $v0, $s7, 24\n"
                "bnez       $v0, 6f\n"
                "ori       $v0, $zero, 0xFC\n"
                "ori        $v0, $zero, 0x11C\n"
                "6:\n"
                "sh         $v0, 0x12($s6)\n"
                "lui        $t3, %%hi(D_800A37D8)\n"
                "addiu      $t3, $t3, %%lo(D_800A37D8)\n"
                "addu       $v0, $fp, $t3\n"
                "lw         $v0, 0x0($v0)\n"
                "nop\n"
                "lhu        $v1, 0x14($v0)\n"
                "addiu      $v0, $s7, 0x1\n"
                "addu       $s7, $v0, $zero\n"
                "sll        $v0, $v0, 24\n"
                "sra        $v0, $v0, 24\n"
                "slti       $v0, $v0, 0x2\n"
                "addiu      $v1, $v1, 0x37\n"
                "sh         $v1, 0x14($s6)\n"
                "sw         $s6, 0x1C($s5)\n"
                "bnez       $v0, 3b\n"
                "addu      $s5, $s6, $zero\n"
                ".set\treorder\n"
                : "=r"(currentNode), "=r"(previousNode), "=m"(markerPanel.value)
                : "1"(previousNode), "m"(panelIndex.value), "m"(colorHome.value)
                : "$1", "$2", "$3", "$4", "$5", "$11", "$12", "$16", "$17",
                  "$18", "$19", "$20", "$23", "$30", "$31", "memory");
        }
        {
            register s32 colorS asm("$19");
            register s32 panelValue asm("$20");
            register s32 initialRow asm("$23");
            register s8 initialColumn asm("$18");
            register s32 triangleRow asm("$23");
            register s32 nextRow asm("$2");
            s8 triangleColumn;
            s32 rowX;
            register s32 widthDelta asm("$5");
            register s32 allocateMode asm("$4");
            register s32 nodeBlue asm("$12");
            register u8 *node asm("$16");
            register u8 *primitive asm("$17");
            register u8 *panelNode asm("$2");
            asm volatile(".set\tnoreorder\n"
                         "lw\t$t4, 0x40($sp)\n"
                         "lbu\t$t3, 0x20($sp)\n"
                         "addu\t$s7, $zero, $zero\n"
                         "sra\t$s3, $t4, 24\n"
                         "sll\t$v0, $t3, 24\n"
                         "sra\t$s4, $v0, 24\n"
                         : "=r"(colorS), "=r"(panelValue), "=r"(initialRow)
                         : "m"(colorHome.value), "m"(panelIndex.value)
                         : "$2", "$11", "$12");
            triangleRow = initialRow;
            do {
                rowX = 0xFA;
                if ((s8)triangleRow == 0) {
                    rowX = 0x11A;
                }
                initialColumn = 0;
                asm("" : : "r"(initialColumn));
                triangleColumn = initialColumn;
                panelTableBase = panelValue * 4;
                asm("" : : "r"(panelTableBase));
                triangleOffset.value = panelTableBase;
                do {
                    widthDelta = triangleColumn != 0 ? 3 : -3;
                    asm volatile(".set\tnoreorder\n"
                                 "lbu\t$v1, D_800A35EC\n"
                                 "lw\t$s0, D_800A3678\n"
                                 "ori\t$a0, $zero, 0x1\n"
                                 "addiu\t$v0, $v1, 0x1\n"
                                 "sb\t$v0, D_800A35EC\n"
                                 "sll\t$v0, $v1, 3\n"
                                 "addu\t$v0, $v0, $v1\n"
                                 "sll\t$v0, $v0, 2\n"
                                 "addu\t$s0, $s0, $v0\n"
                                 "ori\t$v0, $zero, 0x8\n"
                                 "ori\t$t3, $zero, 0x6\n"
                                 "sb\t$zero, 0x2($s0)\n"
                                 "ori\t$t4, $zero, 0xFF\n"
                                 "sb\t$zero, 0x3($s0)\n"
                                 "sh\t$t3, 0x18($s0)\n"
                                 "ori\t$t3, $zero, 0x80\n"
                                 "sb\t$zero, 0x4($s0)\n"
                                 "sb\t$t4, 0x2($s0)\n"
                                 "ori\t$t4, $zero, 0x40\n"
                                 "sh\t$zero, 0x12($s0)\n"
                                 "sh\t$zero, 0x14($s0)\n"
                                 "sw\t$zero, 0x1C($s0)\n"
                                 "sh\t$zero, 0x1A($s0)\n"
                                 "sh\t$v0, 0x0($s0)\n"
                                 "sh\t$zero, 0x6($s0)\n"
                                 "sh\t$zero, 0xA($s0)\n"
                                 "sh\t$s3, 0x8($s0)\n"
                                 "sh\t$s3, 0xC($s0)\n"
                                 "sh\t$zero, 0xE($s0)\n"
                                 "sh\t$zero, 0x10($s0)\n"
                                 "sh\t$a1, 0x16($s0)\n"
                                 "sb\t$t3, 0x3($s0)\n"
                                 : "=r"(node), "=r"(allocateMode),
                                   "=r"(nodeBlue)
                                 : "r"(widthDelta), "r"(colorS)
                                 : "$2", "$3", "$11", "memory");
                    node[4] = nodeBlue;
                    primitive = func_80057D50(allocateMode);
                    *(u8 **)(node + 0x20) = primitive;
                    SetPolyF3(primitive);
                    SetSemiTrans(primitive, 0);
                    asm volatile("" : "=r"(currentNode) : "0"(node));
                    asm volatile(
                        ".set\tnoreorder\nori $t3,$zero,0xFF\nori $t4,$zero,0x80\nsb $t3,4($s1)\nori $t3,$zero,0x40\nsb $t4,5($s1)\nsb $t3,6($s1)"
                        :
                        : "r"(primitive)
                        : "$11", "$12", "memory");
                    asm volatile(".set\tnoreorder\n"
                                 "beqz\t$s4, .LTriangleNestedC60_14\n"
                                 "sh\t$zero, 0x1A($s6)\n"
                                 "ori\t$t4, $zero, 0x140\n"
                                 "j\t.LTriangleNestedC60_1c\n"
                                 "sh\t$t4, 0x6($s6)\n"
                                 ".LTriangleNestedC60_14:\n"
                                 "addiu\t$v0, $zero, -0x140\n"
                                 "sh\t$v0, 0x6($s6)\n"
                                 ".LTriangleNestedC60_1c:\n"
                                 :
                                 : "r"(currentNode), "r"(panelValue)
                                 : "$2", "$12", "memory");
                    *(s16 *)(currentNode + 0x12) = rowX;
                    asm volatile(
                        ".set\tnoreorder\nlw $t3,%2\nlui $t4,%%hi(D_800A37D8)\naddiu $t4,$t4,%%lo(D_800A37D8)\naddu $v0,$t3,$t4\nlw $v0,0($v0)"
                        : "=r"(panelNode), "=r"(panelTableBase)
                        : "m"(triangleOffset.value)
                        : "$11");
                    rowX += 0xF;
                    asm volatile("" : : "r"(rowX) : "memory");
                    *(s16 *)(currentNode + 0x14) =
                        *(u16 *)(panelNode + 0x14) + 0x37;
                    *(u8 **)(previousNode + 0x1C) = currentNode;
                    previousNode = currentNode;
                    triangleColumn++;
                } while (triangleColumn < 2);
                nextRow = triangleRow + 1;
                asm("" : : "r"(nextRow));
                triangleRow = nextRow;
                asm("" : "=r"(nextRow) : "0"(nextRow));
            } while ((s8)nextRow < 2);
        }
        {
            register s32 colorS asm("$18");
            register s32 xpos asm("$20");
            register s32 blue asm("$19");
            register s8 initialArrowIndex asm("$23");
            s8 arrowIndex;
            register s32 heightDelta asm("$5");
            register s32 allocateMode asm("$4");
            register u8 *node asm("$16");
            register u8 *primitive asm("$17");
            register s32 red asm("$12");
            register s32 green asm("$11");
            asm volatile(".set\tnoreorder\n"
                         "lbu\t$t3, 0x20($sp)\n"
                         "nop\t\n"
                         "sll\t$v0, $t3, 24\n"
                         "sra\t$v0, $v0, 22\n"
                         "addu\t$v0, $v0, $t4\n"
                         "lw\t$v0, 0x0($v0)\n"
                         "lw\t$t4, 0x40($sp)\n"
                         "lh\t$v0, 0x14($v0)\n"
                         "addu\t$s7, $zero, $zero\n"
                         "ori\t$s3, $zero, 0x40\n"
                         "sra\t$s2, $t4, 24\n"
                         "addiu\t$s4, $v0, 0x3A\n"
                         ".set\treorder\n"
                         : "=r"(colorS), "=r"(xpos), "=r"(blue),
                           "=r"(initialArrowIndex), "=r"(panelTableBase)
                         : "m"(panelIndex.value), "m"(colorHome.value),
                           "4"(panelTableBase)
                         : "$2", "$3", "$11", "memory");
            arrowIndex = initialArrowIndex;
            do {
                heightDelta = arrowIndex != 0 ? 3 : -3;
                asm volatile(".set\tnoreorder\n"
                             "lbu\t$v1, D_800A35EC\n"
                             "lw\t$s0, D_800A3678\n"
                             "ori\t$a0, $zero, 0x1\n"
                             "addiu\t$v0, $v1, 0x1\n"
                             "sb\t$v0, D_800A35EC\n"
                             "sll\t$v0, $v1, 3\n"
                             "addu\t$v0, $v0, $v1\n"
                             "sll\t$v0, $v0, 2\n"
                             "addu\t$s0, $s0, $v0\n"
                             "ori\t$v0, $zero, 0x7\n"
                             "ori\t$t3, $zero, 0x6\n"
                             "sb\t$zero, 0x2($s0)\n"
                             "ori\t$t4, $zero, 0xFF\n"
                             "sb\t$zero, 0x3($s0)\n"
                             "sh\t$t3, 0x16($s0)\n"
                             "ori\t$t3, $zero, 0x80\n"
                             "sh\t$zero, 0x12($s0)\n"
                             "sh\t$zero, 0x14($s0)\n"
                             "sw\t$zero, 0x1C($s0)\n"
                             "sb\t$zero, 0x4($s0)\n"
                             "sh\t$zero, 0x1A($s0)\n"
                             "sh\t$v0, 0x0($s0)\n"
                             "sh\t$zero, 0x6($s0)\n"
                             "sh\t$zero, 0xA($s0)\n"
                             "sh\t$s2, 0x8($s0)\n"
                             "sh\t$s2, 0xC($s0)\n"
                             "sh\t$zero, 0xE($s0)\n"
                             "sh\t$zero, 0x10($s0)\n"
                             "sh\t$a1, 0x18($s0)\n"
                             "sb\t$t4, 0x2($s0)\n"
                             "sb\t$t3, 0x3($s0)\n"
                             ".set\treorder\n"
                             : "=r"(node), "=r"(allocateMode)
                             : "r"(heightDelta), "r"(colorS), "r"(blue)
                             : "$2", "$3", "$11", "$12", "memory");
                node[4] = blue;
                primitive = func_80057D50(allocateMode);
                *(u8 **)(node + 0x20) = primitive;
                SetPolyF3(primitive);
                SetSemiTrans(primitive, 0);
                asm volatile("" : "=r"(currentNode) : "0"(node));
                red = 0xFF;
                green = 0x80;
                asm("" : : "r"(red), "r"(green));
                primitive[4] = red;
                primitive[5] = green;
                primitive[6] = blue;
                *(s16 *)(currentNode + 0x1A) = 0;
                asm volatile(".set\tnoreorder\n"
                             "lbu\t$t4, 0x20($sp)\n"
                             "nop\t\n"
                             "sll\t$v0, $t4, 24\n"
                             "beqz\t$v0, .LTriangleFinal60_1c\n"
                             "ori\t$t3, $zero, 0x140\n"
                             "j\t.LTriangleFinal60_24\n"
                             "sh\t$t3, 0x6($s6)\n"
                             ".LTriangleFinal60_1c:\n"
                             "addiu\t$v0, $zero, -0x140\n"
                             "sh\t$v0, 0x6($s6)\n"
                             ".LTriangleFinal60_24:\n"
                             ".set\treorder\n"
                             :
                             : "r"(currentNode), "m"(panelIndex.value)
                             : "$2", "$11", "$12", "memory");
                *(s16 *)(currentNode + 0x12) = 0xAC;
                *(s16 *)(currentNode + 0x14) = xpos;
                *(u8 **)(previousNode + 0x1C) = currentNode;
                previousNode = currentNode;
                arrowIndex++;
                xpos += 0xC;
            } while (arrowIndex < 2);
        }
    }
    asm volatile("lbu\t%0,%1\n"
                 ".set\treorder\n"
                 : "=r"(previousPanelByte)
                 : "m"(panelIndex.value));
    nextPanel = previousPanelByte + 1;
    asm("" : : "r"(nextPanel));
    panelIndex.value = nextPanel;
    if (panelIndex.value < D_800A3644[0] + 1) {
        goto panelLoop;
    }
panelsDone:
    ListSetFieldsAndEnable(D_800A37F8, -0x140, 0, 4);
}

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

extern u8 gPadLayout[];
extern u8 D_800A3088[];
extern u8 D_800A3350[];
extern s32 D_8009A4E0[][7][14];
extern u8 D_8009B00C[];
extern u8 D_8009B028[];
extern u8 D_8009B02A[];

void MenuUpdatePadPicture(s32 arg0) {
    u8 *node;
    u8 *prim;
    s32 a;
    s32 c;
    u8 uc;
    s32 ghost;
    s32 id;
    s32 off;
    s32 f;
    u8 *chars;
    s32 fontId;
    s8 i;
    s8 j;
    s32 idx;
    u8 *prim2;

    node = (u8 *)D_800A37D8[arg0 & 0xFF];
    while (*(u16 *)node != 1) {
        node = *(u8 **)(node + 0x1C);
    }
    prim = *(u8 **)(node + 0x20);
    if (((s8 *)gPadType)[arg0 & 0xFF] != ((s8 *)D_800A308C)[arg0 & 0xFF] &&
        ((s8 *)gPadType)[arg0 & 0xFF] != 0) {
        ((s8 *)gPadLayout)[arg0 & 0xFF] = 0;
    }
    if (((s8 *)gPadType)[arg0 & 0xFF] != 0) {
        ((s8 *)D_800A308C)[arg0 & 0xFF] = ((s8 *)gPadType)[arg0 & 0xFF];
    }
    idx = arg0 & 0xFF;
    a = ((s8 *)gPadType)[idx];
    if (a != 0) {
        fontId = ((s8 *)D_800A3350)[a];
        chars = D_8009B00C;
        c = *(chars + 7 * fontId + ((s8 *)gPadLayout)[idx]);
    } else {
        c = D_800A3088[idx];
    }
    id = (s8)c;
    off = id * 6;
    D_800A3088[idx] = c;
    *(u16 *)(prim + 0xE) = GetClut(0x100, *(s16 *)&D_8009B028[off + 4]);
    *(u16 *)(prim + 0x16) =
        GetTPage(1, 0, *(s16 *)&D_8009B028[off], *(s16 *)&D_8009B02A[off]);
    prim[0xC] = 0;
    prim[0xD] = *(u16 *)&D_8009B02A[off];
    prim[0x14] = *(u16 *)(node + 0x16);
    prim[0x15] = *(u16 *)&D_8009B02A[off];
    prim[0x1C] = 0;
    prim[0x1D] = D_8009B02A[off] + node[0x18];
    prim[0x24] = *(u16 *)(node + 0x16);
    prim[0x25] = D_8009B02A[off] + node[0x18];
    node = *(u8 **)(node + 0x1C);
    prim = *(u8 **)(node + 0x20);
    if (id == 1 && (((s8 *)gPadType)[arg0 & 0xFF] == 5 ||
                    ((s8 *)gPadType)[arg0 & 0xFF] == 7)) {
        prim[4] = -(((s8 *)gPadType)[arg0 & 0xFF] == 7);
        prim[5] = -(((s8 *)gPadType)[arg0 & 0xFF] == 5);
        prim[6] = 0;
        node[5] = 1;
    } else {
        node[5] = 0;
    }
    node = *(u8 **)(node + 0x1C);
    node[5] = !((s8 *)gPadType)[arg0 & 0xFF];
    node = *(u8 **)(node + 0x1C);
    node = *(u8 **)(node + 0x1C);
    prim2 = *(u8 **)(node + 0x20);
    *(s32 *)(prim2 + 8) = ((s8 *)gPadLayout)[arg0 & 0xFF] + 1;
    uc = ((s8 *)gPadType)[arg0 & 0xFF];
    c = ((s8 *)gPadType)[arg0 & 0xFF];
    ghost = c;
    if (uc == 0) {
        c = D_800A308C[arg0 & 0xFF];
    }
    /* Both terms are zero; combine folds them after flow, so `ghost` stays
       a dead copy that fills the bnez slot. */
    c = c + ((ghost << 24) & 0xFF) + ((ghost << 25) & 0x1FF);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 7; j++) {
            node = *(u8 **)(node + 0x1C);
            f = ((s8 *)D_800A3350)[(s8)c];
            prim2 = *(u8 **)(node + 0x20);
            *(s32 *)(prim2 + 8) =
                D_8009A4E0[f][((s8 *)gPadLayout)[(u8)arg0]][7 * i + j];
        }
    }
}

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

extern u8 D_800AEE40[];
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

extern u8 *D_800A35E4[];
extern u8 *D_800A3868[];
extern u8 *func_8005BF8C(s32, s32);
extern u8 *func_8005B314(s32, s32, s32, s32, s32, u8, u8, u8, u8, u8);
extern void func_80067EA4(struct UnkObject24 *, u8, u8, s32, u8, s32);
extern u8 gPlayerDriver[];

void func_800631DC(s32 left, s32 top, s32 code) {
    u8 *node;
    u8 *entry;
    s32 mode;
    s32 base;
    s32 x;
    u8 *object;
    s32 xoff;
    s32 y;
    s32 dx;
    s32 dy;
    s32 i;
    s32 j;
    register s32 k asm("$18");
    u8 *packet;
    s32 width;

    func_8005A7B8(2, 2);
    if (D_800A39E4[0] == 0xE) {
        base = 0x9E;
    } else {
        base = 0x3A;
    }
    entry = gPlayerCar[0];
    for (i = 0; i < 2; i++) {
        node = MenuObjAlloc();
        mode = D_800A39E4[0];
        D_800A35E4[i] = node;
        *(s16 *)(node + 0) = 4;
        *(s16 *)(node + 0x6) = left;
        *(s16 *)(node + 0xA) = top;
        *(s16 *)(node + 0x8) = base;
        *(s16 *)(node + 0xC) = base;
        *(s16 *)(node + 0xE) = code;
        *(s16 *)(node + 0x10) = 0;
        if (mode != 0xE) {
            base += 0x33;
        }
        *(u8 **)(node + 0x20) = entry;
        entry = *(u8 **)(entry + 0x3E0);
        if (mode == 7 || mode == 0xE) {
            continue;
        }
        x = func_8005B0E4(0x64, (s32)gDriverNames[gPlayerDriver[i]]) - 0x32;
        object = func_8005BF8C(left + x, base - 6);
        *(s16 *)(object + 0xA) = top + x;
        *(s16 *)(object + 0x12) = x;
        *(s16 *)(object + 0xE) = code;
        func_80067EA4((struct UnkObject24 *)object, 2, 2,
                      (s32)gDriverNames[gPlayerDriver[i]], 0, 0);
        *(u8 **)(node + 0x1C) = object;
        node = object;
        D_800A3868[i] = node;
        width = 0x32;
        for (j = 0; j < 4; j++) {
            xoff = -0x32;
            y = base - 9;
            switch (j) {
            case 0:
                dx = 0;
                dy = 0;
                break;
            case 1:
                y = base - 2;
                dx = 0;
                dy = 0x29;
                break;
            case 2:
                xoff = 0;
                dx = 0x46;
                dy = 0;
                break;
            case 3:
                xoff = 0;
                y = base - 2;
                dx = 0x46;
                dy = 0x29;
                break;
            }
            object = func_8005B598(left + xoff, y, width, 7, 1, 1, 0);
            packet = *(u8 **)(object + 0x20);
            *(s16 *)(object + 0x12) = xoff;
            *(s16 *)(object + 0xA) = top + xoff;
            *(s16 *)(object + 0xE) = code;
            func_8005B17C(packet, 9, dx, dy, width, 7);
            *(u8 **)(node + 0x1C) = object;
            node = object;
        }
        for (k = 0; k < 2; k++) {
            object = func_8005B314(left - 0x32, base - 9, 0x64, 0xE, 0, 0x20,
                                   0x20, 0x40, 1, 1);
            *(s16 *)(object + 0x1A) = 3;
            *(s16 *)(object + 0x12) = -0x32;
            *(s16 *)(object + 0xA) = top - 0x32;
            *(s16 *)(object + 0xE) = code;
            *(u8 **)(node + 0x1C) = object;
            node = object;
        }
    }
}

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

extern u8 *D_800A3868[];
void func_800636EC(u8 index, u8 kind) {
    u8 *node;
    u8 *object;
    s32 value;

    node = D_800A3868[index];
    object = *(u8 **)(node + 0x20);
    *(u8 **)(object + 8) = gDriverNames[kind];
    func_8005A7B8(object[1], object[2]);
    value = func_8005B0E4(0x64, *(s32 *)(object + 8));
    *(s16 *)(node + 6) = value + 0xA;
    *(s16 *)(node + 0x12) = value - 0x32;
}

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

void func_80063C34(s32 arg0, s32 arg1) {
    RECT rect;
    void *work;
    void *small;
    s32 y1;
    s32 x1;
    s32 x3;
    s32 y3;

    if (arg0 >= 2 && arg1 >= 2) {
        work = HeapAlloc(0x2000);
        small = HeapAlloc(0x20);
        if (work != NULL && small != NULL) {
            x1 = (arg0 % 4) * 0x40 + 0x300;
            y1 = (arg0 / 4) * 0x40 + 0x40;
            rect.x = x1;
            rect.y = y1;
            rect.h = 0x40;
            rect.w = 0x40;
            StoreImage(&rect, (u_long *)work);
            rect.x = (arg0 % 16) * 0x10 + 0x300;
            rect.y = 0x3F - arg0 / 16;
            rect.h = 1;
            rect.w = 0x10;
            StoreImage(&rect, (u_long *)small);
            DrawSync(0);
            x3 = (arg1 % 4) * 0x40 + 0x300; /* anchor: dropping this dead
             * store changes y3's register */
            y3 = (arg1 / 4) * 0x40 + 0x40;
            rect.x = (arg1 % 4) * 0x40 + 0x300;
            rect.y = y3;
            rect.h = 0x40;
            rect.w = 0x40;
            MoveImage(&rect, x1, y1);
            rect.x = (arg1 % 16) * 0x10 + 0x300;
            rect.y = 0x3F - arg1 / 16;
            rect.h = 1;
            rect.w = 0x10;
            MoveImage(&rect, (arg0 % 16) * 0x10 + 0x300, 0x3F - arg0 / 16);
            DrawSync(0);
            rect.x = (arg1 % 4) * 0x40 + 0x300;
            rect.y = y3;
            rect.h = 0x40;
            rect.w = 0x40;
            LoadImage(&rect, (u_long *)work);
            rect.x = (arg1 % 16) * 0x10 + 0x300;
            rect.y = 0x3F - arg1 / 16;
            rect.h = 1;
            rect.w = 0x10;
            LoadImage(&rect, (u_long *)small);
            DrawSync(0);
            HeapFree(work);
            HeapFree(small);
        }
    }
}

extern s32 D_800A2E84Absolute[];
extern u8 *func_8002D874(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

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
    gPlayerCar[0] = entry;
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
void func_8003271C(s32 arg0);
void CarDrawPreviewModel(void *arg0, s32 arg1, s32 arg2, s32 arg3);
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
            CarDrawPreviewModel(obj, 0, 0xFA, 0x44C);
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
                result = *(u16 *)(gPlayerCar[0] + 0x20E);
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

extern u8 D_800A3060[];
extern s8 D_800A39FC;
extern s8 D_800A3594;
extern s8 D_800A3A14;
extern u8 *D_800A3744[];
extern u8 *D_800A3958[];
extern u8 *D_800A38FC[];
extern u8 *D_800A3900[];
extern u8 *D_800A39A0[];
extern u8 *D_800A35E0Alias[] asm("D_800A35E0Absolute");
extern u8 func_8006AD0C(s8);
extern void func_800645A4(s32, s32);
struct UnkNode1C;
extern void ListSetRangeFields(struct UnkNode1C *, s32, s32, s16);

void func_80064208(void) {
    u8 *tail;
    u8 *node;
    u8 *prim;
    u8 *entry;
    u8 *obj;
    u8 **linkSlot;
    s32 y;
    s32 height;
    s32 h;
    s32 i;
    s32 j;
    s32 kind;
    s32 kind2;
    s32 k;
    u8 idx;
    if (D_800A3060[0] != 0) {
        D_800A39FC = gPlayerDriver[0];
    } else {
        D_800A39FC = RandomScaledGet(0x18);
    }
    D_800A3594 = func_8006AD0C(D_800A39FC);
    for (i = 0; i < 2; i++) {
        tail = func_8005B598(0x14, 0x41, 0x40, 0x48, 1, 1, 0);
        D_800A3744[i] = tail;
        *((s16 *)(tail + 0x12)) = 0x14;
        node = func_8005BF8C(0x5F, 0x2D);
        kind = D_800A39FC;
        ((MenuObj *)node)->unk12 = 0x5F;
        func_80067EA4((struct UnkObject24 *)node, 2, 3, gDriverNames[kind], 0,
                      0);
        *((u8 **)(tail + 0x1C)) = node;
        tail = node;
        func_8005A7B8(2, 3);
        height = func_8005A84C();
        y = height + 0x32;
        func_8005A7B8(2, 4);
        height = func_8005A84C();
        for (j = 0; j < 5; j++) {
            node = func_8005BF8C(0x5F, y);
            kind2 = D_800A39FC;
            *((s16 *)(node + 0x12)) = 0x5F;
            func_80067EA4((struct UnkObject24 *)node, 2, 4, gDriverNames[kind2],
                          0, 0);
            y += height;
            *((u8 **)(tail + 0x1C)) = node;
            tail = node;
            if (j == 2) {
                y += 5;
            }
        }

        prim = func_8005B598(0x14, 0x2B, 0x40, 0xC, 1, 1, 0);
        node = prim;
        D_800A3958[i] = prim;
        *((s16 *)(node + 0x12)) = 0x14;
        *((u8 **)(tail + 0x1C)) = node;
        prim = *((u8 **)(prim + 0x20));
        func_8005B17C(prim, 2, 0, 0, 0x40, 0xC);
        *((s16 *)(prim + 8)) = 0x14;
        *((s16 *)(prim + 0xA)) = 0x2D;
        *((s16 *)(prim + 0x10)) = 0x54;
        *((s16 *)(prim + 0x12)) = 0x2D;
        *((s16 *)(prim + 0x18)) = 0x14;
        *((s16 *)(prim + 0x1A)) = 0x39;
        *((s16 *)(prim + 0x20)) = 0x54;
        *((s16 *)(prim + 0x22)) = 0x39;
    }

    for (k = 0; k < 2; k++) {
        tail = func_8005B314(0, 0x27, 0x140, 0xC8, 0, 0x10, 0x10, 0x10, 1, 1);
        if (k == 0) {
            D_800A3900[0] = tail;
        } else {
            *(linkSlot = (u8 **)(D_800A3900[0] + 0x1C)) = tail;
        }
        *((s16 *)(tail + 0x1A)) = 0x3FD;
    }

    idx = (u8)D_800A39FC;
    D_800A3A14 = 0;
    func_800645A4(0, idx);
    entry = D_800A3744[D_800A3A14];
    D_800A39A0[0] = 0;
    D_800A38FC[0] = entry;
    ListSetRangeFields((struct UnkNode1C *)entry, -0x140, 0, 2);
    func_800631DC(-0x10C, 0x34, 2);
    /* D_800A35E4[0] via the D_800A35E0 alias: a distinct symbol keeps the
     * base load below from being shared with the height lookup. */
    obj = D_800A35E0Alias[1];
    h = *((s16 *)(D_800A35E4[D_800A3A14] + 0xA));
    while (obj != 0) {
        node = obj + 0xE;
        *((s16 *)node) = 2;
        obj[5] = 2;
        *((s16 *)(obj + 6)) = (*((u16 *)(obj + 0x12))) - 0x10C;
        *((s16 *)(obj + 0xA)) = (*((u16 *)(obj + 0x12))) + h;
        obj = *(u8 **)(obj + 0x1C);
    }

    func_80063AE0(D_800A3A14, D_800A39FC);
}

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
    u32 quotient;
    u32 u;
    u32 remainder;

    node = D_800A3744[arg0 & 0xFF];
    idx = arg1 & 0xFF;
    prim = *(u8 **)(node + 0x20);
    *(s16 *)(prim + 0xE) = GetClut(0x100, 0x1E7 - idx);
    quotient = idx / 12;
    y = (quotient & 0xFF) * 0x48;
    y += 0x140;
    remainder = idx - quotient * 12;
    remainder <<= 5;
    u = remainder & 0x1F80;
    u += 0x140;
    *(s16 *)(prim + 0x16) = GetTPage(1, 0, u, y);
    /* Keep the mask on idx instead of CSE substituting the original arg1. */
    asm("andi %0,%1,3" : "=r"(q) : "r"(idx));
    u = q << 6;
    prim[0xC] = u;
    prim[0xD] = y;
    q = u + 0x3F;
    prim[0x14] = q;
    prim[0x15] = y;
    prim[0x1C] = u;
    prim[0x1D] = y + 0x47;
    prim[0x24] = q;
    prim[0x25] = y + 0x47;
    node = *(u8 **)(node + 0x1C);
    func_8005A7B8(2, 4);
    h = func_8005A84C();
    x = *(s16 *)(node + 8);
    offset = *(s32 *)(D_800A3A5C + idx * 4);
    for (i = 0; i < 6; i++) {
        prim2 = *(u8 **)(node + 0x20);
        if (i == 0) {
            *(u8 **)(prim2 + 8) = gDriverNames[idx];
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
                y = TextCountLines(*(u8 **)(prim2 + 8)) * h;
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

extern u8 *D_800A3900[];
extern u8 *D_800A39A4nm[] asm("D_800A39A4.NON_MATCHING");
extern u8 *D_800A39AC[];
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
extern u8 *D_8009A418[];
extern u8 D_800A3698;
extern u8 D_800A3A4C;
extern u8 *D_800A39D8;
extern u8 *D_800A369C;
void func_80064C14(void) {
    extern u32 *D_800A38C4;
    extern s32 D_800A367C;

    D_800A38C4 = (u32 *)gOrderingTables;
    gOrderingTable[0] = gOrderingTables;
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
    extern u8 D_800A3884;
    extern s32 D_800A367C;
    extern u32 *D_800A38C4;
    /* The post-call string reads go through the neighbouring symbols so
     * cse can't share one address register with the pre-call reads. */
    extern u8 *D_8009A3EC[];
    extern u8 *D_8009A414[];
    extern u8 D_800A3778;
    extern u8 D_800A35DC;
    extern void func_80065058(s32, s32);
    extern void func_80065F80(void);
    extern void MenuDrawCarPickPair(s32);
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
        MenuDrawCarPickPair(1);
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

inline s32 func_80065040(void) {
    s32 old;
    old = D_800A367C;
    D_800A367C = old + 0x28;
    return old;
}

extern u8 D_800A3950[];
extern u8 D_800A305B[];
extern u8 *gTrackNames[];
extern u8 *D_8009A3A4[];
extern u8 *D_8009A3E8[];
extern u8 *D_8009A41C[];
extern u8 *D_8009A3EC[];
extern u8 *D_8009A3ECLui asm("D_8009A3EC");
extern u8 *D_8009ACE0[];
extern s32 D_800AEB34[];
extern u8 *D_8009A42C[];
extern u8 gPlayerDriverLui asm("gPlayerDriverAbsolute");
extern u8 D_800A36E1Lui asm("D_800A36E1Absolute");
extern u8 D_800A3644Lui asm("D_800A3644Absolute");
extern s32 gOrderingTableLui asm("gOrderingTableAbsolute");
extern volatile u16 D_800A3A44;
extern volatile s16 D_800A3A44Signed asm("D_800A3A44");
extern volatile s16 D_800A3940Signed asm("D_800A3940");
extern volatile u8 D_800A3760;
extern u8 *D_800A3568;
extern u8 *D_800A3970;
extern u32 *D_800A38C4;
void func_80065058(u8 id, s32 shift) {
    u8 entry[0x40];
    u8 slots[2];
    s32 n;
    u8 *prim;
    u8 *end;
    s32 xOffset;
    s32 leftX;
    s32 i;
    s32 x0;
    s32 x1off;
    s32 height;
    s32 red;
    s32 green;
    s32 blue;
    s32 yBase;
    u8 color;
    s32 r2;
    s32 g2;
    s32 b2;

    xOffset = -((shift & 0xFF) != 0) & -0x140;
    n = 1;
    height = id * 2;
    for (i = 0; i < 2; i++) {
        slots[i] = 0xFF;
        if (gGridOrder[height + i] == gPlayerDriverLui) {
            slots[n - 1] = i;
            n++;
        }
        if (D_800A3644Lui != 0 && gGridOrder[height + i] == D_800A36E1Lui) {
            slots[n - 1] = i;
            n++;
        }
    }
    x1off = 0x11C;
    x0 = xOffset + 0x12;
    for (i = 0; i < 3; i++) {
        prim = (u8 *)func_80065040();
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
                height = 0x12;
                red = 0x78;
                green = 0x78;
                blue = 0xEC;
                x1off = 0x8E;
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
                    x0 = xOffset + 0x12;
                } else {
                    x0 = xOffset + 0xA0;
                }
            }
            break;
        }
        prim[4] = red;
        prim[5] = green;
        prim[6] = blue;
        *(s16 *)(prim + 8) = x0;
        *(s16 *)(prim + 0xA) = yBase;
        *(s16 *)(prim + 0xC) = x0 + x1off;
        *(s16 *)(prim + 0xE) = yBase;
        *(s16 *)(prim + 0x10) = x0;
        *(s16 *)(prim + 0x12) = yBase + height;
        *(s16 *)(prim + 0x14) = x0 + x1off;
        *(s16 *)(prim + 0x16) = yBase + height;
        if (i < 3) {
            AddPrim((u8 *)D_800A38C4 + 0xC, prim);
        } else {
            AddPrim((u8 *)D_800A38C4 + 8, prim);
        }
    }
    leftX = xOffset + 0x17;
    height = id * 2;
    for (i = 0; i < 2; i++) {
        color = gGridOrder[height + i];
        prim = (u8 *)func_80065040();
        SetPolyFT4((POLY_FT4 *)prim);
        func_80064AB4(prim, color);
        if (i == 0) {
            *(s16 *)(prim + 8) = leftX;
            *(s16 *)(prim + 0xA) = 0x5A;
            *(s16 *)(prim + 0x10) = xOffset + 0x57;
            *(s16 *)(prim + 0x12) = 0x5A;
            *(s16 *)(prim + 0x18) = leftX;
            *(s16 *)(prim + 0x1A) = 0xA2;
            *(s16 *)(prim + 0x20) = xOffset + 0x57;
            *(s16 *)(prim + 0x22) = 0xA2;
        } else {
            *(s16 *)(prim + 8) = xOffset + 0xA5;
            *(s16 *)(prim + 0xA) = 0x5A;
            *(s16 *)(prim + 0x10) = xOffset + 0xE5;
            *(s16 *)(prim + 0x12) = 0x5A;
            *(s16 *)(prim + 0x18) = xOffset + 0xA5;
            *(s16 *)(prim + 0x1A) = 0xA2;
            *(s16 *)(prim + 0x20) = xOffset + 0xE5;
            *(s16 *)(prim + 0x22) = 0xA2;
        }
        AddPrim((u8 *)D_800A38C4 + 8, prim);
    }
    D_800A3568 = (u8 *)D_800A367C;
    func_8005A7B8(2, 4);
    func_8005A818(0x80, 0x80, 0xC0);
    gOrderingTableLui += 4;
    if (D_800A3950[0] == 0xFB || D_800A3950[0] == 3) {
        func_8005A9F4((s32)gTrackNames[D_800A305B[0]], 0x17, 0x41, 0, 0, 1, 0,
                      0);
    } else {
        func_8005A9F4((s32)D_8009A3A4[D_800A305B[0]], 0x17, 0x41, 0, 0, 1, 0,
                      0);
    }
    if (D_800A2EB0Absolute[0] == 0) {
        func_8005A9F4((s32)D_8009A3E8[0], 0x17, 0x4D, 0, 0, 1, 0, 0);
    } else {
        func_8005A9F4((s32)D_8009A41C[0], 0x17, 0x4D, 0, 0, 1, 0, 0);
    }
    if (id + 1 >= 0xA) {
        D_8009A3ECLui[4] = 0x31;
        D_8009A3ECLui[5] = id + 0x27;
        D_8009A3ECLui[6] = 0;
    } else {
        D_8009A3ECLui[4] = id + 0x31;
        D_8009A3ECLui[5] = 0;
    }
    func_8005A9F4((s32)D_8009A3EC[0], 0xFC, 0x4D, 0, 0, 0, 0, 0);
    height = id * 2;
    for (i = 0; i < 2; i++) {
        x0 = 0xA5;
        if (i == 0) {
            x0 = 0x17;
        }
        color = gGridOrder[height + i];
        if (color == gPlayerDriverLui) {
            r2 = 0xC0;
            g2 = 0x80;
            b2 = 0x40;
        } else if (D_800A3644Lui != 0 && color == D_800A36E1Lui) {
            g2 = 0x80;
            r2 = 0xC0;
            b2 = 0x40;
        } else {
            r2 = 0x80;
            g2 = 0x80;
            b2 = 0xC0;
        }
        func_8005A818(r2, g2, b2);
        func_8005A9F4((s32)D_8009ACE0[color], x0, 0xA7, 0, 0, 0, 0, 0);
        func_8005A9F4((s32)gDriverNames[color], x0 + 0x1E, 0xA7, 0, 0, 0, 0, 0);
        if (D_800A2EB0Absolute[0] == 0 && D_800AEB34[color] == 0x7FFFFFFF) {
            func_8005A9F4((s32)D_8009A42C[0], x0 + 0x45, 0x7E, 0, 0, 0, 0, 0);
        } else {
            TextFormatTime((void *)D_800AEB34[color], -1, entry);
            func_8005A9F4((s32)entry, x0 + 0x45, 0x7E, 0, 0, 0, 0, 7);
        }
        if (D_800A2EB0Absolute[0] == 0 && height == 0 && i == 0) {
            func_8005A9F4((s32)D_8009A3EC[13], x0 + 0x59, 0x61, 0, 0, 0, 0, 0);
            func_8005A9F4((s32)D_8009A3EC[14], x0 + 0x4F, 0x6B, 0, 0, 0, 0, 0);
        }
    }
    gOrderingTableLui -= 4;
    end = (u8 *)D_800A367C;
    D_800A3970 = end;
    if (xOffset != 0) {
        for (prim = D_800A3568; prim != end; prim += 0x28) {
            *(u16 *)(prim + 8) += xOffset;
            *(u16 *)(prim + 0x10) += xOffset;
            *(u16 *)(prim + 0x18) += xOffset;
            *(u16 *)(prim + 0x20) += xOffset;
        }
    }
    D_800A3940Signed = 2;
    D_800A3A44 = xOffset;
    D_800A3760 = 1;
}

void func_80065838(s32 arg0) {
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
void func_800658F0(void) {
    s32 i;
    u8 *primitive;
    primitive = D_800A38D8;
    for (i = 0; i < D_800A35B4; i++) {
        AddPrim(D_800A38C4 + 1, primitive);
        primitive += 0x28;
    }
}

void func_8006594C(s32 arg0, s32 arg1) {
    extern volatile u16 D_800A3940;
    extern s32 D_800A3538;
    extern s32 D_800A3540;
    extern u8 D_800A35B4;
    extern u32 *D_800A38C4;
    extern u8 *D_800A38D8;
    s16 shift;
    POLY_FT4 *quad;
    POLY_FT4 *walk2;
    u8 *primBase;
    s32 i;

    D_800A3A44 = D_800A3A44 + D_800A3940;
    shift = D_800A3940;
    if ((arg0 & 0xFF) != 0) {
        if ((s16)D_800A3A44 <= 0) {
            goto earlyOut;
        }
    } else {
        if ((s16)D_800A3A44 < 0x141) {
            goto earlyOut;
        }
    }
    D_800A3A44 = D_800A3A44 - D_800A3940;
    if ((arg0 & 0xFF) != 0) {
        shift = -D_800A3A44;
    } else {
        shift = 0x140 - D_800A3A44;
    }
    D_800A3A44 = D_800A3A44 + shift;
    D_800A3940 = 0;
    if ((arg1 & 0xFF) != 0) {
        walk2 = (POLY_FT4 *)D_800A38D8;
        for (i = 0; i < D_800A35B4; i++) {
            AddPrim(D_800A38C4 + 1, walk2);
            walk2++;
        }
    }
    goto tailTest;
earlyOut:
    if ((s16)D_800A3940 < 0x20) {
        D_800A3940 = D_800A3940 + (s16)D_800A3940 / 2;
    }
tailTest:
    if (shift == 0) {
        return;
    }
    if ((arg1 & 0xFF) != 0) {
        for (quad = (POLY_FT4 *)D_800A3538; quad != (POLY_FT4 *)D_800A3540;
             quad++) {
            quad->x0 += shift;
            quad->x1 += shift;
            quad->x2 += shift;
            quad->x3 += shift;
        }
        for (; quad != (POLY_FT4 *)D_800A3970; quad++) {
            quad->x0 -= shift;
            quad->x1 -= shift;
            quad->x2 -= shift;
            quad->x3 -= shift;
        }
    } else {
        primBase = D_800A369C + D_800A3698 * 0x28;
        if (((POLY_F4 *)primBase)->code == 0x28) {
            do {
                ((POLY_F4 *)primBase)->x0 += shift;
                ((POLY_F4 *)primBase)->x1 += shift;
                ((POLY_F4 *)primBase)->x2 += shift;
                ((POLY_F4 *)primBase)->x3 += shift;
                primBase += 0x28;
            } while (((POLY_F4 *)primBase)->code == 0x28);
        }
        for (quad = (POLY_FT4 *)primBase; quad != (POLY_FT4 *)D_800A3970;
             quad++) {
            quad->x0 += shift;
            quad->x1 += shift;
            quad->x2 += shift;
            quad->x3 += shift;
        }
    }
}

/* The ", D_800A3940" and ", D_800A3778" tails below are reads of the just
 * stored volatile; retail reloads the byte/word after the store. */
void func_80065C3C(void) {
    extern s32 GetGp(void);
    extern s32 D_8008CA4C[];
    extern volatile u16 D_800A3940;
    extern volatile u8 D_800A3778;
    extern u8 D_800A35DC;
    extern u8 D_800A3884;
    extern volatile u8 D_800A3360;
    extern void func_8006594C(s32, s32);
    extern void func_80065058(u8, s32);
    s32 oldGp;
    u8 *walk;
    char *text;
    s32 len;
    s32 i;

    oldGp = GetGp();
    func_80058D08(D_8008CA4C[0]);
    SetDispMask(1);
    if ((u8)(D_800A39E4[0] + 3) >= 2) {
        PutDrawEnv(D_800BDD4C);
        if ((D_800A3940 << 16) > 0) {
            func_8006594C(D_800A3760, 0);
        } else if (D_800A3760 == 0) {
            D_800A3940Signed = -0xB5;
        } else {
            D_800A3940 = D_800A3940 - 1, D_800A3940;
        }
        if ((s16)D_800A3940 < -0xB4) {
            if (D_800A3778 == D_800A35DC) {
                D_800A3940 = 0;
                if (*(volatile u8 *)&D_800A3884 == 1) {
                    ClearOTagR(D_800A38C4, 4);
                    walk = D_800A369C;
                    walk += D_800A3A4C * 0x28;
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
                    D_800A367C =
                        (s32)(D_800A369C + *(volatile u8 *)&D_800A3698 * 0x28);
                    func_80065058(D_800A3778, 0);
                    D_800A3884 = 2;
                }
            } else {
                D_800A3940 = 2;
                D_800A3760 = D_800A3760 ^ 1;
                if (D_800A3760 == 1) {
                    D_800A3778 = D_800A3778 + 1, D_800A3778;
                    ClearOTagR(D_800A38C4, 4);
                    if (D_800A3884 == 0) {
                        text = (char *)D_8009A400[0];
                        walk = D_800A369C;
                        len = strlen(text);
                        for (i = 0; i < len; i++) {
                            AddPrim(D_800A38C4, walk);
                            walk += 0x28;
                        }
                    } else {
                        walk = D_800A369C;
                        walk += D_800A3A4C * 0x28;
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
                        if (*(volatile u8 *)&D_800A3884 == 1) {
                            D_800A3884 = 2;
                        }
                    }
                    D_800A367C =
                        (s32)(D_800A369C + *(volatile u8 *)&D_800A3698 * 0x28);
                    func_80065058(D_800A3778, 1);
                }
            }
        }
        DrawOTag(D_800A38C4 + 3);
        DrawSync(0);
    }
    D_800A3360 = 1;
    asm("addu $gp, %0, $zero" : : "r"(oldGp));
}

extern void func_8005A818(u8 arg0, u8 arg1, u8 arg2);
extern s32 func_8005B0E4(s16 arg0, s32 arg1);
extern void func_8005A9F4(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4,
                          s32 arg5, u8 arg6, u8 arg7);
extern u8 *D_8009A3FC[];
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

extern s32 D_800A3540;
extern u8 *D_8009A3F4[];
extern u8 *D_8009A3F8;
extern u8 D_800A305BLui asm("D_800A305BAbsolute");
void MenuDrawCarPickPair(s32 arg0) {
    s32 i;
    s32 shift;
    s32 x;
    u8 color;
    POLY_FT4 *prim;

    for (i = 0; i < 2; i++) {
        if ((arg0 & 0xFF) != 0) {
            shift = -0x140;
            if (i != 0) {
                shift = 0x140;
            }
        } else {
            shift = 0;
        }
        color = gPlayerDriver[i];
        prim = (POLY_FT4 *)func_80065040();
        SetPolyFT4(prim);
        func_80064AB4((u8 *)prim, color);
        if (i == 0) {
            prim->x0 = shift + 0x3E;
            prim->y0 = 0x66;
            prim->x1 = shift + 0x7E;
            prim->y1 = 0x66;
            prim->x2 = shift + 0x3E;
            prim->y2 = 0xAE;
            prim->x3 = shift + 0x7E;
            prim->y3 = 0xAE;
        } else {
            prim->x0 = shift + 0xCC;
            prim->y0 = 0x66;
            prim->x1 = shift + 0x10C;
            prim->y1 = 0x66;
            prim->x2 = shift + 0xCC;
            prim->y2 = 0xAE;
            prim->x3 = shift + 0x10C;
            prim->y3 = 0xAE;
            D_800A3540 = (s32)prim;
        }
        AddPrim((u8 *)D_800A38C4 + 8, (u8 *)prim);
        D_800A3568 = (u8 *)D_800A367C;
        x = 0xA5;
        if (i == 0) {
            x = 0x17;
        }
        func_8005A818(0x80, 0x80, 0xC0);
        func_8005A9F4((s32)D_8009ACE0[color], x, 0xB1, 0, 0, 0, 0, 0);
        func_8005A9F4((s32)gDriverNames[color], x + 0x1E, 0xB1, 0, 0, 0, 0, 0);
        D_800A3970 = (u8 *)D_800A367C;
        if (shift != 0) {
            for (prim = (POLY_FT4 *)D_800A3568; prim != (POLY_FT4 *)D_800A3970;
                 prim++) {
                prim->x0 += shift;
                prim->x1 += shift;
                prim->x2 += shift;
                prim->x3 += shift;
            }
        }
    }
    x = func_8005B0E4(0x140, (s32)D_8009A3F4[0]);
    func_8005A9F4((s32)D_8009A3F4[0], x, 0x2A, 0, 0, 0, 0, 0);
    x = func_8005B0E4(0x140, (s32)D_8009A3F8);
    func_8005A9F4((s32)D_8009A3F8, x, 0x3E, 0, 0, 0, 0, 0);
    x = func_8005B0E4(0x140, (s32)gTrackNames[D_800A305BLui]);
    func_8005A9F4((s32)gTrackNames[D_800A305BLui], x, 0x4D, 0, 0, 0, 0, 0);
    D_800A3940Signed = 2;
    if ((arg0 & 0xFF) != 0) {
        D_800A3A44Signed = -0x140;
    } else {
        D_800A3A44 = 0;
    }
    D_800A3760 = 1;
}

void func_800663B0(void) {
    extern s32 D_8008CA4C[];
    extern u16 D_800A3940;
    extern u8 D_800A3760;
    extern volatile u8 D_800A3360;
    extern void func_8006594C(s32, s32);
    extern void MenuDrawCarPickPair(s32);
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
                MenuDrawCarPickPair(0);
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
            AddPrim(((u8 *)(orderTable = gOrderingTable)[0]) + offset, dst);
            i += 1;
        } while (i < 0xA);
        row += 1;
        topY += 0x20;
    } while (row < 7);
    return (void *)cursor;
}

extern u8 *gOrderingTablePtr[] asm("gOrderingTable");
extern u8 *D_8009A404[];
extern u8 *D_8009A430[];
extern u8 *D_8009A414[];
extern u8 D_8009B198[];
extern DRAWENV D_800BDDA8[];
extern DISPENV D_800BDE18[];
extern void *func_8006654C(void *, s32);
extern void func_8005A7B8S32(s32, s32) asm("func_8005A7B8");
extern s32 func_8005B0E4(s16, s32);
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
        ClearOTagR((u32 *)gOrderingTablePtr[0], 0x3FF);
        func_80014A40(0);
        func_8006654C((void *)0, 0x3FC);
        MenuDrawModel(0, 0, 1);
        func_8005A7B8S32(2, 4);
        func_8005A818(0x80, 0x80, 0xC0);
        y = 0xA0;
        i = 0;
        p = table;
        func_8005A9F4(gTrackNames[D_800A305B[0]], 0x20, 0x23, 0, 0, 0, 0, 0);
        do {
            y16 = (s16)y;
            func_8005A9F4(p[0], 0x20, y16, 0, 0, 0, 0, 0);
            ret = (s32)(s16)MenuStringWidth(p[0]);
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
        DrawOTag((u32 *)(gOrderingTablePtr[0] + 0xFFC));
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

extern s32 D_800A335C;
extern void func_80065C3C(void);
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
    HudDrawText(D_8009A400[0], 0x8C, 0xD6, 1);
    D_800A39F4 = gPrimitiveCursor2[0];
    HudDrawText(D_8009A400[10], 0x82, 0xF1, 1);
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

extern u32 gPrimitiveCursor2[] asm("gPrimitiveCursor");
extern u32 D_800A3570Absolute[];
extern u8 *gOtMenuStore[] asm("gOrderingTable");
extern u8 *gOtMenuBase[] asm("gOrderingTable");
extern u8 *gOtMenuLow[] asm("gOrderingTable");
extern u8 *gOtMenuMid[] asm("gOrderingTable");
extern u8 *gOtMenuHigh[] asm("gOrderingTable");
extern u8 *gOtMenuGhost[] asm("gOrderingTable");
extern u16 *D_800A389C[];
extern u16 *D_800A3898;
extern u16 *D_800A387C;
extern u16 *D_800A36BC;
extern s32 D_800A365C;
extern s32 D_800A39F4;
extern u8 D_800A36A0;
extern s32 D_800A3930;
void func_80066CFC(void) {
    POLY_FT4 *dst;
    POLY_FT4 *prim;
    POLY_FT4 *next;
    POLY_FT4 *oldCursor;
    u8 *ot;
    u8 *limit;

    oldCursor = (POLY_FT4 *)gPrimitiveCursor2[0];
    func_8001D778(0, 0xD2, 0x140, 0x1E, 8, 8, 8, 0);
    func_80066B70();
    *(volatile u8 *)&D_800A36A0 = 1;
    gOtMenuStore[0] = gOrderingTables;
    ClearOTagR((u_long *)gOrderingTables, 4);
    ot = gOtMenuBase[0];
    dst = (POLY_FT4 *)(ot + 0x10);
    prim = (POLY_FT4 *)D_800A3570Absolute[0];
    limit = ot + 0x4000;
    if (prim != (POLY_FT4 *)gPrimitiveCursor[0]) {
        next = (POLY_FT4 *)(ot + 0x38);
        while (prim != (POLY_FT4 *)gPrimitiveCursor[0] && (u8 *)next < limit) {
            *dst = *prim;
            if (prim >= (POLY_FT4 *)D_800A365C) {
                if (prim == (POLY_FT4 *)D_800A365C) {
                    D_800A387C = (u16 *)dst;
                } else if (prim == (POLY_FT4 *)D_800A39F4) {
                    D_800A36BC = (u16 *)dst;
                }
                AddPrim(gOtMenuLow[0], dst);
            } else {
                if (prim == oldCursor) {
                    AddPrim(gOtMenuMid[0] + 4, dst);
                } else if (next[-1].r0 != 0xFF) {
                    AddPrim(gOtMenuHigh[0] + 0xC, dst);
                } else {
                    AddPrim(gOtMenuGhost[0] + 8, dst);
                }
            }
            prim++;
            next++;
            dst++;
        }
    }
    D_800A3898 = (u16 *)dst;
    dst = (POLY_FT4 *)(SCRATCH_TOP - 0x28);
    D_800A389C[0] = 0;
    while (prim != (POLY_FT4 *)gPrimitiveCursor[0]) {
        *dst = *prim;
        if (prim >= (POLY_FT4 *)D_800A365C) {
            if (prim == (POLY_FT4 *)D_800A365C) {
                D_800A387C = (u16 *)dst;
            } else if (prim == (POLY_FT4 *)D_800A39F4) {
                D_800A36BC = (u16 *)dst;
            }
            AddPrim(gOtMenuLow[0], dst);
        } else {
            if (prim == oldCursor) {
                AddPrim(gOtMenuMid[0] + 4, dst);
            } else {
                if (dst->r0 != 0xFF) {
                    AddPrim(gOtMenuHigh[0] + 0xC, dst);
                } else {
                    AddPrim(gOtMenuGhost[0] + 8, dst);
                }
                D_800A389C[0] = (u16 *)dst;
            }
        }
        prim++;
        dst--;
    }
    DrawOTag((u32 *)(gOtMenuBase[0] + 0xC));
    DrawSync(0);
    SetDispMask(1);
    D_800A3884 = 0;
    D_800A3930 = 0;
}

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
    extern s32 D_800A3848Lui asm("D_800A3848Absolute");
    s32 cur;
    u8 arg;
    u16 *base;
    u16 *limit;

    arg = arg0;
    cur = D_800A3848Lui - ((s8)arg0 << 1);
    D_800A3848Lui = cur;
    if (cur < 0xA0) {
        D_800A3848Lui = 0xA0;
        return;
    }
    if (cur >= 0x1EB) {
        D_800A3848Lui = 0x1EA;
        return;
    }
    if (D_800A3644[0] != 0) {
        return;
    }
    base = (u16 *)gOrderingTablePtr[0];
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
    u16 *baseA;
    u16 *baseB;
    u16 *baseB2;
    POLY_FT4 *quad;
    POLY_FT4 *quad2;
    s32 i;
    s32 len;
    u32 unused[4]; /* retail reserves 16 bytes of locals nothing touches */

    baseA = D_800A387C;
    baseB = (u16 *)gOrderingTablePtr[0];
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

void func_8006733C(void) {
    extern s32 D_800A3848[];
    extern u8 *D_8009A428[];
    extern volatile s32 D_800A3930;
    extern void func_80058D08(s32);
    extern void func_80041AF0Arg(s32) asm("func_80041AF0");
    extern void func_8006709C();
    s32 oldGp;
    s32 input;
    s8 flag;
    u16 *baseA;
    u16 *baseB;
    u16 *baseB2;
    POLY_FT4 *quad;
    POLY_FT4 *quad2;
    s32 i;
    s32 len;
    u32 unused[4]; /* retail reserves 16 bytes of locals nothing touches */

    oldGp = GetGp();
    func_80058D08(D_8008CA4C[0]);
    if (DrawSync(1) == 0) {
        D_800A3930++;
        func_80041AF0Arg(0);
        input = PadGetButtons(0);
        if (input & 0x1000) {
            flag = 1;
        } else if (input & 0x4000) {
            flag = -1;
        } else {
            flag = -(D_800A3848[0] < 0x1EA);
        }
        if (flag != 0) {
            if ((D_800A3930 & 1) != 0) {
                func_8006709C(flag);
            }
        }
        if (*(volatile u8 *)&D_800A3884 == 1) {
            baseA = D_800A387C;
            baseB = (u16 *)gOrderingTablePtr[0];
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
            len = strlen(D_8009A428[0]);
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
            D_800A3884 = 2;
        }
        PutDispEnv(&D_800BDE04[D_800A36A0]);
        PutDrawEnv(
            (DRAWENV *)((s32)D_800BDD4C + (*(volatile u8 *)&D_800A36A0) * 92));
        DrawOTag((u32 *)(gOrderingTablePtr[0] + 0xC));
        D_800A36A0 ^= 1;
    }
    D_800A3360 = 1;
    asm("addu $gp, %0, $zero" : : "r"(oldGp));
}

extern u8 gTextColorLui[] asm("gTextColor");
extern volatile u16 D_800A3940;
extern u8 D_800A3364[];
extern u32 D_800A3570Lui asm("D_800A3570Absolute");
extern u32 gPrimitiveCursorLui asm("gPrimitiveCursorAbsolute");
extern u8 *gPlayerCarLui asm("gPlayerCarAbsolute");
extern void func_800168F8(u8 *, s32);

void MenuDrawLoadScreen(void) {
    char buf[16];
    u32 textCursor;
    u32 src;
    POLY_FT4 *ft4;
    u32 end;
    s32 depth;
    POLY_GT4 *gt4;
    u8 *car;
    POLY_GT4 *prim;

    func_80066B70();
    textCursor = gPrimitiveCursorLui;
    HudDrawText(gTrackNames[D_800A305B[0]], 0x14, 0x23, 0);
    HudDrawText(gDriverNames[gPlayerDriver[0]], 0xA0, 0xB0, 0);
    HudDrawText(D_8009A400[34], 0xA0, 0xBE, 0);
    HudDrawText(D_800A3364, 0xE0, 0xBE, 0);
    TextFormatTime(*(void **)(gPlayerCarLui + 0x25C), 0, (s32)buf);
    gTextColorLui[0] = 9;
    HudDrawText((u8 *)buf + 1, 0xEA, 0xBE, 0);
    SetGeomOffset(0xAA, 0x1E);
    gPlayerCarLui[0x20C] = 1;
    func_8002EEFC(gPlayerCarLui);
    car = gPlayerCarLui;
    *(s32 *)(car + 0) = 0;
    *(s32 *)(car + 4) = 0;
    *(s32 *)(car + 8) = 0;
    *(u16 *)(car + 0x20E) = 0xA00;
    func_8003271C(0);
    func_800168F8(*(u8 **)(gPlayerCarLui + 0x36C),
                  (s8)(*(s8 *)(gPlayerCarLui + 0x200) / 5));
    end = gPrimitiveCursorLui;
    CarDrawPreviewModel(gPlayerCarLui, 0, 0x15E, 0x320);
    gOrderingTableLui = (s32)gOrderingTables;
    ClearOTagR((u_long *)gOrderingTables, 0x80);
    ft4 = (POLY_FT4 *)(gOrderingTables + 0x208);
    for (src = D_800A3570Lui; src < end; src += sizeof(POLY_FT4)) {
        *ft4 = *(POLY_FT4 *)src;
        if (src == D_800A365C) {
            D_800A387C = (u16 *)ft4;
        } else if (src == D_800A39F4) {
            D_800A36BC = (u16 *)ft4;
        } else if (src >= textCursor) {
            if (src == textCursor) {
                D_800A3568 = (u8 *)ft4;
            }
            ft4->x0 -= 0x140;
            ft4->x1 -= 0x140;
            ft4->x2 -= 0x140;
            ft4->x3 -= 0x140;
        }
        setRGB0(ft4, 0x80, 0x80, 0xC0);
        AddPrim((u_long *)gOrderingTableLui, ft4);
        ft4++;
    }
    gt4 = (POLY_GT4 *)ft4;
    D_800A367C = (s32)gt4;
    depth = 0x78;
    prim = gt4;
    while (end < gPrimitiveCursorLui) {
        *gt4 = *(POLY_GT4 *)end;
        AddPrim((u_long *)gOrderingTableLui + depth, gt4);
        gt4++;
        end += sizeof(POLY_GT4);
        prim->x0 += 0x140;
        prim->x1 += 0x140;
        prim->x2 += 0x140;
        prim->x3 += 0x140;
        prim++;
        depth--;
        if (depth == 0) {
            depth = 1;
        }
    }
    D_800A3970 = (u8 *)gt4;
    D_800A3898 = func_8006654C(gt4, 0x7E);
    DrawOTag((u_long *)(gOrderingTableLui + 0x1FC));
    DrawSync(0);
    SetDispMask(1);
    *(volatile u8 *)&D_800A3884 = 0;
    D_800A3930 = -0x140;
    D_800A3940 = 4;
    D_800A36A0 = 1;
}

void func_800679C4(u8 arg0) {
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

void func_80067AB4(void) {
    extern s32 D_8008CA4C[];
    extern u8 *gOrderingTablePtr[] asm("gOrderingTable");
    extern u8 *D_8009A428[];
    extern DISPENV D_800BDE04[];
    extern DRAWENV D_800BDD4C[];
    extern volatile s32 D_800A3930;
    extern volatile u16 D_800A3940;
    extern u8 *D_800A3568;
    extern s32 D_800A367C;
    extern u8 *D_800A3970;
    extern u16 *D_800A387C;
    extern u16 *D_800A36BC;
    extern u8 D_800A36A0;
    extern u8 D_800A3884;
    extern volatile u8 D_800A3360;
    extern s32 GetGp(void);
    extern void func_80058D08(s32);
    s32 oldGp;
    u16 *baseA;
    u16 *baseB;
    u16 *baseB2;
    POLY_FT4 *quad;
    POLY_FT4 *quad2;
    s32 i;
    s32 len;
    u16 rawShift;
    s8 shift;
    u32 unused[4]; /* retail reserves 16 bytes of locals nothing touches */

    oldGp = GetGp();
    func_80058D08(D_8008CA4C[0]);
    if (DrawSync(1) == 0) {
        if (*(volatile u8 *)&D_800A3884 == 1) {
            baseA = D_800A387C;
            baseB = (u16 *)gOrderingTablePtr[0];
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
            len = strlen(D_8009A428[0]);
            if (len > 0) {
                quad2 = (POLY_FT4 *)baseA;
                i = 0;
                do {
                    quad2->y0 -= 0x1B;
                    quad2->y1 -= 0x1B;
                    quad2->y2 -= 0x1B;
                    quad2->y3 -= 0x1B;
                    if (baseA < baseB2) {
                        quad2++;
                        baseA += 0x14;
                    } else {
                        quad2--;
                        baseA -= 0x14;
                    }
                    i++;
                } while (i < len);
            }
            D_800A3884 = 2;
        }
        PutDispEnv(&D_800BDE04[D_800A36A0]);
        PutDrawEnv(
            (DRAWENV *)((s32)D_800BDD4C + (*(volatile u8 *)&D_800A36A0) * 92));
        if (D_800A3940 != 0) {
            u16 *base;
            u16 *limit;
            rawShift = D_800A3940;
            asm volatile("" ::: "memory");
            base = (u16 *)D_800A3568;
            limit = (u16 *)D_800A367C;
            shift = rawShift;
            if (base < limit) {
                POLY_FT4 *quad3;
                quad3 = (POLY_FT4 *)base;
                do {
                    quad3->x0 += (s8)shift;
                    quad3->x1 += (s8)shift;
                    quad3->x2 += (s8)shift;
                    quad3->x3 += (s8)shift;
                    quad3++;
                } while ((u16 *)quad3 < limit);
            }
            base = (u16 *)D_800A367C;
            limit = (u16 *)D_800A3970;
            if (base < limit) {
                POLY_GT4 *quad4;
                quad4 = (POLY_GT4 *)base;
                do {
                    quad4->x0 -= (s8)shift;
                    quad4->x1 -= (s8)shift;
                    quad4->x2 -= (s8)shift;
                    quad4->x3 -= (s8)shift;
                    quad4++;
                } while ((u16 *)quad4 < limit);
            }
            if (D_800A3930 + (s16)D_800A3940 > 0) {
                D_800A3940 = -D_800A3930;
            } else {
                D_800A3940 = D_800A3940 + (s16)D_800A3940 / 4;
            }
            D_800A3930 = D_800A3930 + (s16)D_800A3940;
        }
        DrawOTag((u32 *)(gOrderingTablePtr[0] + 0x1FC));
        D_800A36A0 ^= 1;
    }
    D_800A3360 = 1;
    asm("addu $gp, %0, $zero" : : "r"(oldGp));
}

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

u8 func_80067ECC(char *name) {
    s32 i;

    for (i = 0; i < 0x18; i++) {
        if (strcmp(name, gDriverNames[i]) == 0) {
            break;
        }
    }
    return i;
}
