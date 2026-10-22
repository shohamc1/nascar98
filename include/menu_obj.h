#ifndef MENU_OBJ_H
#define MENU_OBJ_H

#include "common.h"

typedef struct MenuObj {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    struct MenuObj *unk1C;
    u8 *unk20;
} MenuObj;

#endif /* MENU_OBJ_H */
