#ifndef MENU_H
#define MENU_H

#include "common.h"

typedef struct MenuObjectNode {
    u8 unk0[6];
    u16 x;
    u16 y;
    u16 targetX;
    u16 targetY;
    u16 velocityX;
    u16 velocityY;
    u16 drawOffsetX;
    u8 unk14[8];
    struct MenuObjectNode *next;
} MenuObjectNode;

typedef struct MenuTextPacket {
    u8 unk0, unk1, unk2, unk3;
    s32 orderingDepth, text;
} MenuTextPacket;

typedef struct MenuTextObjectView {
    u8 unk0[0x1A];
    s16 orderingDepth;
    u8 unk1C[4];
    MenuTextPacket *textPacket;
} MenuTextObjectView;
void MenuSetTextColor(u8, u8, u8);
s16 MenuFontLineHeight(void);
void MenuSetTexturedQuad(u8 *dst, u32 idx, u16 dx, u16 dy, u16 ax, u16 ay);
u8 *MenuCreateTexturedRect(s32 left, s32 top, s32 right, s32 bottom, s32 depth,
                           u8 texture, u8 semiTrans);
void func_80064000(s32 mode, s32 a, s32 b);
void func_8006DD28(u32 arg0, u32 arg1);
void func_8006E484(u32 arg0, u32 arg1);
s16 MenuStringWidth(s32);
void MenuDrawModel(s32, s32, s32);
void MenuUpdatePadPicture(s32);

#endif /* MENU_H */
