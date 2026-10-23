#ifndef SOUND_H
#define SOUND_H

#include "common.h"

void func_800406D0(u8 *, u8 *, s32, s32);
s32 func_80041848(u8 *, s32);
void SoundShutdownAll(void);
void SoundLoadVab(s32 arg0);
void SoundReloadVab(s32 arg0);
void SoundShutdown(void);
void SoundStopSlot(s32);
void SoundSetSlotVolume(s8, s32, s32);

#endif /* SOUND_H */
