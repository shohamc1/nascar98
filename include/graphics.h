#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"

/* The header of an image bank file. One ImageBankEntry per image follows,
 * then the ImageBankTexture table. */
typedef struct {
    u16 imageCount;   /* 0x00 */
    u16 textureCount; /* 0x02 */
} ImageBankHeader;

/* One image in a loaded bank: two file offsets, made into pointers on load.
 * image points at a RECT followed by the pixels. */
typedef struct {
    u8 *unk0;
    u8 *image; /* 0x04 */
} ImageBankEntry;

/* A 0x10 texture in the loaded image bank: its texture page, the UV
 * offset within the page and its CLUT position. */
typedef struct {
    u16 mode; /* 0x00: texture page colour mode */
    u16 x;    /* 0x02: page position in VRAM */
    u16 y;    /* 0x04 */
    u8 u;     /* 0x06 */
    u8 unk7;
    u8 v; /* 0x08 */
    u8 unk9;
    u16 clutX; /* 0x0A */
    u16 clutY; /* 0x0C */
    u8 unkE[2];
} ImageBankTexture;
void MatrixCombineState(void);
void MatrixRotateVector(s32 *vec);
void MatrixLoadObjectBasis(s32 *transform);
void MatrixTransformVector(s32 *vec);
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
void MatrixStoreToObject(Car *object);
void MatrixSaveState(void);
void MatrixRestoreState(void);

#endif /* GRAPHICS_H */
