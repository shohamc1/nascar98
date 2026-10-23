#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "menu_obj.h"
#include "car.h"
#include "track.h"

/* A 0x0A font glyph: its texture page position, UV and size. The first
   glyph of a menu font holds the font's line height. */
typedef struct {
    s16 x;      /* 0x00: texture page position */
    s16 y;      /* 0x02 */
    u8 u;       /* 0x04 */
    u8 v;       /* 0x05 */
    s16 width;  /* 0x06 */
    s16 height; /* 0x08 */
} Glyph;

/* Game symbols declared by more than one source file. Types follow the
   decompiled callers; placeholder names stay until their purpose is known. */

/* Data */
extern s32 D_8008CA28[];
extern u8 D_80090F2E[];
extern u8 D_80099230[];
extern u8 D_80099231[];
extern u8 *D_8009A400[];
extern char *gDriverNames[];
extern u8 D_8009AD40[];
extern u8 D_8009AEAA[];
extern u8 D_8009AEAE[];
extern u8 D_8009AEB6[];
extern s32 D_800A2CE0[];
extern s32 D_800A2CF8[];
extern s32 D_800A2E24Absolute[];
extern s32 D_800A2E64[];
extern s32 D_800A2E78[];
extern s32 D_800A2E94[];
extern s32 gSplitScreenMode[];
extern s32 gSplitScreenModeAbsolute[];
extern s32 D_800A2EA8[];
extern s32 D_800A2EACAbsolute[];
extern s32 gSessionType;
extern s32 gSessionTypeAbsolute[];
extern s32 D_800A2EB4[];
extern s32 D_800A2EB8[];
extern s32 D_800A2EC0Absolute[];
extern s32 D_800A2EC8[];
extern s32 D_800A2EC8Absolute[];
extern s32 D_800A2ED4[];
extern u8 D_800A2ED9[];
extern u8 D_800A2EDC[];
extern s32 D_800A2F10[];
extern u8 D_800A2F9DAbsolute[];
extern char gTextPositiveSign[];
extern u8 D_800A3068[];
extern u8 D_800A3069[];
extern u8 D_800A3073[];
extern u8 D_800A308C[];
extern u8 D_800A331C[];
extern u8 D_800A331CAbsolute[];
extern u8 D_800A3320[];
extern s32 D_800A3558[];
extern MenuObj *D_800A35E8[];
extern s32 D_800A3654;
extern s32 D_800A3668Absolute[];
extern MenuObj *gMenuObjectPool;
extern s32 D_800A36D0Absolute[];
extern u8 D_800A36E1[];
extern u8 D_800A37BC;
extern MenuObj *D_800A3854Absolute[];
extern u8 D_800A3860[][4];
extern MenuObj *D_800A38A8;
extern MenuObj *D_800A38FC[];
extern MenuObj *D_800A392C;
extern Car *gCrashCar[];
extern s32 D_800A397CAbsolute[];
extern u8 D_800A3980[];
extern s32 D_800A3984[];
extern MenuObj *D_800A39A0[];
extern RECT D_800A39B0[];
extern u8 D_800A39C4;
extern u8 gScreenState[];
extern u8 gScreenStateAbsolute[];
extern s8 gPadType[];
/* Pointers to the two 0x400-entry 16.16 trig tables. */
extern s32 *D_800A3A2C, *D_800A3A34;
extern s8 D_800A3A25[];
extern s32 D_800A3A2CAbsolute2[];
extern s32 D_800A3A34Absolute2[];
extern void *D_800A3A40;
extern s32 D_800A3A54[];
extern s32 D_800AE1EC[];
extern s16 *D_800AE290[];
extern s32 D_800AE844[];
extern u8 D_800AEE3D[];
extern u8 D_800AEE3E[];
extern u8 D_800B0B7C[];
extern u8 D_800B9990[];
extern s32 D_800B9D54[];
extern s32 D_800B9F44[];
extern char D_800BB9B4[];
extern u8 gDriverOrder[];
extern s32 gTrackSectionCount[];
extern void *D_800BE97C[];
extern s32 gTrackSections[];
extern s32 D_801F3FF8[];
extern s32 gOrderingTableBank;
extern s32 gOrderingTableBankAbsolute[];
extern u8 gOrderingTables[];
extern u32 gPrimitiveCursor[];

extern u8 *D_8009AD68[][6];
extern s32 D_800A2D5C;
extern s32 *D_800A2D64;
extern u8 D_800A2DE0[];
extern u8 gMenuObjectPoolCount;
extern s32 D_800AE84C[];
extern s32 D_800AEB34[];
extern u8 D_800B9B6F[];
extern u8 D_800B9B70[];
extern u8 D_800B9B71[];
extern u8 D_800B9B72[];
extern u8 D_800BDD62[];
extern u8 D_800BDD64[];
extern u8 D_800BDD65[];
extern u8 D_800BDD66[];
extern u8 D_800BDD67[];
extern u8 D_800BDDBE[];
extern u8 D_800BDDC0[];
extern u8 D_800BDDC1[];
extern u8 D_800BDDC2[];
extern u8 D_800BDDC3[];
extern s32 gReplayIndex[];

/* Functions */
extern s32 CardEnableEvents(void);
extern s32 CardWaitForEvent(void);
extern void CdSetMixVolume(s32);
extern s32 CloseEvent(s32);
extern void *HeapAlloc(u32);
extern long RotTransPers_nom();
extern void SceneInitRoadStrip(void);
extern void SsEnd(void);
extern void func_8001C668(void *, void *);
extern void DebugDrawMeterBar(s32, s32, s32, s32);
extern void ReplayStepBack(void);
extern void func_80023074(void);
extern void func_80025454(s32);
extern void func_80028754(u8 *, s32);
extern void func_8002D3EC(Car *);
extern void ModelLoadGeometryByIndex(s32, s32);
extern void ModelBuildReverseLinks(u8 *);
extern void GteStoreDepthAndScreenCoordinates(SVECTOR *vertex);
extern void func_8003379C(SVECTOR *arg0, SVECTOR *arg1, SVECTOR *arg2);
extern s32 func_800337EC(void);
extern void func_8003382C(s16 *out);
extern s32 func_800358EC(s32 *);
extern void func_8003644C(s32, s32, s32, s32);
extern void func_8003A880(Car *);
extern void func_8003A950(Car *);
extern void func_8003AA20(Car *);
extern void func_8003AAEC(Car *);
extern void CarAdvanceResetTimer(Car *);
extern void func_8003CAE8(s32);
extern void GraphicsLoadImagePointerTable();
extern void SoundLoadVabAndResetSlots(s32);
extern void SoundSetReverbType(void);
extern void SoundStopActiveSlots(void);
extern void func_8003FC0C(s32, s32, s32);
extern s32 FileLoadBlock(void *, void *);
extern void SoundPlaySlotAtVolume(void *, s32, s32);
extern s32 PadGetButtons(s32);
extern void func_80044114(Car *);
extern void HudUpdateTrafficGapData(void);
extern void MenuRunFrontEnd(void);
extern void GameInitDefaults(void);
extern void SceneAllocateRuntimeBuffers(void);
extern void *FileLoadOffsetTable(s32, void **, s32);
extern void func_800587A0(void);
extern void func_80058D94(void);
extern void GraphicsLoadPaletteRow(void);
extern void func_8005978C(void);
extern void CardOpenEvents(void);
extern void CardInit(void);
extern s32 CardPollStatusEvents(void);
extern void CardTestTransferEvents(void);
extern void MenuFontReset(void);
extern void MenuFontBuildPrimitives(u8, u8);
extern void MenuFontSet(u8, u8);
extern void MenuSetShadeColors(u8, u8, u8);
extern s32 MenuDrawStringW();
extern void func_8005C020(MenuObj *, u8 *);
extern void MenuFormatTimeObject(MenuObj *, s32);
extern void func_8005CF34(MenuObj *, u8, u8, u8, s32);
extern void MenuAllocateObjectBuffer(void);
extern void MenuLoadOffsetResources(s32);
extern void MenuAllocateObjectList(void);
extern void MenuSetLinkedObjectLayoutByIndex(u8, s16, s16, s16);
extern void MenuSetDriverNameLabel(u8, u8);
extern void func_80063874(void);
extern void func_80063AE0(s32, s32);
extern void func_80063E7C(void);
extern void MenuLoadTextureTable(void);
extern void func_800663B0(void);
extern void MenuShowDisplay(void);
extern void MenuStopVBlankEvent(void);
extern void CardMenuLoadResources(void);
extern s32 PadMapButtons(u8);
extern void func_8006EB18(Car *);
extern void BufferClear17Bytes(void);
extern s32 MoviePlayFile(s32, s32, s32);
extern void func_80082B70(void);

#endif /* GAME_H */
