#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "menu_obj.h"

void MenuSetTextColor(u8, u8, u8);
s16 MenuFontLineHeight(void);
void MenuSetTexturedQuad(POLY_FT4 *dst, u32 idx, u16 dx, u16 dy, u16 ax,
                         u16 ay);
MenuObj *MenuCreateTexturedRect(s32 left, s32 top, s32 right, s32 bottom,
                                s32 depth, u8 texture, u8 semiTrans);
void func_80064000(s32 mode, s32 a, s32 b);
void func_8006DD28(u32 arg0, u32 arg1);
void func_8006E484(u32 arg0, u32 arg1);
s16 MenuStringWidth(u8 *);
void MenuDrawModel(s32, s32, s32);
void MenuUpdatePadPicture(s32);

#endif /* MENU_H */
