#ifndef MENU_OBJ_H
#define MENU_OBJ_H

#include "common.h"

/* A 0x0C text primitive: the primitive of a MenuObj that draws text. */
typedef struct {
    u8 shade;  /* 0x00 */
    u8 font;   /* 0x01: font 2 draws text as a number */
    u8 scale;  /* 0x02 */
    u8 center; /* 0x03 */
    s32 otz;   /* 0x04 */
    s32 text;  /* 0x08: string pointer, or the number to draw */
} MenuText;

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
    void *primitive;
} MenuObj;

#endif /* MENU_OBJ_H */
