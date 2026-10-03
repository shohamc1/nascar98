/* SPDX-License-Identifier: MIT */
#ifndef N98_PSXSDK_INTERNAL_H
#define N98_PSXSDK_INTERNAL_H
#include "common.h"
struct SeqStruct {
    u8 unk0; u8 pad1[3];
    u8* readPos; u8* nextSepPos; u8* loopPos;
    u8 unk10; u8 eventStatus; u8 channel; u8 unk13; u8 unk14; u8 unk15; u8 unk16;
    u8 panpot[16];
    u8 unk27; u8 unk28; u8 unk29; u8 unk2A; u8 unk2B;
    u8 programs[16]; u8 unk3C; u8 pad3D;
    s16 unk3E; s16 unk40; s16 unk42; s16 unk44; s16 loopCount; s16 loopIndex; s16 unk4A; s16 unk4C;
    s16 vol[16];
    s16 unk6E; s16 unk70; s16 unk72;
    u16 leftVolume; u16 rightVolume; s16 unk78; s16 unk7A;
    s32 unk7C; u32 unk80; s32 unk84; s32 deltaValue; s32 unk8C; s32 unk90;
    u32 unk94; u32 unk98; s32 unk9C; u32 unkA0; u32 unkA4;
    s16 unkA8; s16 unkAA;
};
typedef char SeqStruct_must_be_0xAC[(sizeof(struct SeqStruct) == 0xAC) ? 1 : -1];
extern struct SeqStruct *D_800BDE3C[];
#endif
