#ifndef MENU_H
#define MENU_H

#include "common.h"

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
void func_8005A818(u8, u8, u8);
s16 func_8005A84C(void);
void func_8005B17C(u8 *dst, u32 idx, u16 dx, u16 dy, u16 ax, u16 ay);
u8 *func_8005B598(s32 left, s32 top, s32 right, s32 bottom, s32 depth,
                  u8 texture, u8 semiTrans);
void func_80064000(s32 mode, s32 a, s32 b);
void func_8006DD28(u32 arg0, u32 arg1);
void func_8006E484(u32 arg0, u32 arg1);
s16 MenuStringWidth(s32);
void MenuDrawModel(s32, s32, s32);
void MenuUpdatePadPicture(s32);

#endif /* MENU_H */
