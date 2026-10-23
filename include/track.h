#ifndef TRACK_H
#define TRACK_H

#include "common.h"
#include <psxsdk/libgte.h>

/* A model or road face: the colour and texture words copied into its
 * POLY_FT4, four vertex pointers and the next face. Collision code keeps
 * flags in the pad byte of uv2 and the facing angle in the pad of uv3. */
typedef struct Face {
    u8 unk0;
    s8 kind; /* 0x01 */
    u8 unk2[2];
    u32 rgbCode;        /* 0x04: r, g, b and the GPU code */
    u32 uvClut;         /* 0x08 */
    u32 uvTpage;        /* 0x0C */
    u16 uv2;            /* 0x10 */
    u8 unk12;
    u8 flags;           /* 0x13 */
    u16 uv3;            /* 0x14 */
    s16 angle;          /* 0x16 */
    SVECTOR *vertex[4]; /* 0x18 */
    struct Face *next;  /* 0x28 */
} Face;

/* A 0x90-byte track section. gTrackSections[0] points to the array, and
 * prev and next link each section to its neighbours. */
typedef struct TrackSection {
    struct TrackSection *prev; /* 0x00 */
    struct TrackSection *next; /* 0x04 */
    u16 section;               /* 0x08 */
    u8 unkA[4];
    u16 culled;                  /* 0x0E */
    u16 angle;                   /* 0x10 */
    u8 unk12;                    /* point index in bits 1 to 7 */
    u8 unk13;
    s32 x;                       /* 0x14 */
    s32 z;                       /* 0x18 */
    u16 height0;                 /* 0x1C */
    s16 height1;                 /* 0x1E */
    u8 *unk20;                   /* 0x20 */
    u8 unk24[4];
    struct Face *firstQuad; /* 0x28 */
    u8 unk2C[4];
    u8 *callbacks; /* 0x30: nodes run by ListDispatchCallbacks */
    s16 unk34;
    s16 unk36;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50; /* 0x50 */
    u8 unk54[0x20];
    u8 *children;  /* 0x74: drawn by func_8002E240, linked at + 0x54 */
    u8 *unk78[6];  /* 0x78 */
} TrackSection;

#endif /* TRACK_H */
