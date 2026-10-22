#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"

typedef struct {
    u8 pad[16];
} Unk16;
void MatrixCombineState(void);
void MatrixRotateVector(s32 *vec);
void func_8001EC38(s32 *arg0);
void func_8001ED84(s32 *vec);
void func_8001F2C4(s32 arg0, s32 arg1, s32 arg2);
void GraphicsAddPolyFT4(u8 *arg0);
void FontSetColor(s16 red, s16 green, s16 blue);
void FontDrawString(s8 *text, s32 x, s32 y, s32 scale);
void FontDrawPaddedNumber(s32, s32, s32, s32);
void FontDrawNumber(s32 value, s32 x, s32 y, s32 scale);
void TextFormatTime(void *timeValue, s32 flags, s32 buffer);
void GraphicsLoadImageBank(s32 fileName);
void GraphicsLoadImageWithXOffset(s32 xOffset);
void GraphicsSetGeomOffsetForMode(s32 geomOffsetX, s32 mode);
void GraphicsSetClearColor(u8 r, u8 g, u8 b);
void GraphicsApplyDisplayEnvironments(void);
void GraphicsPartitionWorkBuffers(void);
void GraphicsInitDoubleBuffer(s32 mode);
void MatrixStoreToObject(s32 *object);
void MatrixSaveState(void);
void MatrixRestoreState(void);

#endif /* GRAPHICS_H */
