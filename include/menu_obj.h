#ifndef MENU_OBJ_H
#define MENU_OBJ_H

#include "common.h"

typedef struct MenuObj {
    s16 kind;
    u8 red;
    u8 green;
    u8 blue;
    u8 unk5;
    s16 x;
    s16 y;
    s16 targetX;
    s16 targetY;
    s16 velocityX;
    s16 velocityY;
    s16 drawOffsetX;
    s16 drawOffsetY;
    s16 width;
    s16 height;
    s16 orderingDepth;
    struct MenuObj *next;
    u8 *primitive;
} MenuObj;

#endif /* MENU_OBJ_H */
