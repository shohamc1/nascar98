#ifndef TRACK_H
#define TRACK_H

#include "common.h"
#include <psxsdk/libgte.h>

/* A 0x2C model or road face. Bytes 0x04 to 0x17 mirror a POLY_FT4 from
 * r0 on, so draw code copies them a word at a time; road faces keep
 * flags in the pad after v2 and the facing angle after v3. */
typedef struct Face {
    u8 unk0;
    s8 depth; /* 0x01: added to the ordering-table index */
    s8 type;  /* 0x02 */
    u8 len;   /* 0x03: primitive length, copied from the tag */
    u8 r0, g0, b0, code;
    u8 u0, v0;
    u16 clut;
    u8 u1, v1;
    u16 tpage;
    u8 u2, v2;
    u8 vertexCount;     /* 0x12: 3 for a triangle */
    u8 flags;           /* 0x13 */
    u8 u3, v3;
    s16 angle;          /* 0x16: texture index on model faces */
    SVECTOR *vertex[4]; /* 0x18 */
    struct Face *next;  /* 0x28 */
} Face;

/* A 0x58 skid mark from the gSkidMarks pool. Its face is drawn with the
 * track section it lies on, which links it through next. */
typedef struct SkidMark {
    u16 section; /* 0x00: owning track section, or -1 */
    u8 unk2[2];
    s32 depth;             /* 0x04: drawn when the view reaches it */
    Face face;                /* 0x08 */
    SVECTOR vertex[4];        /* 0x34 */
    struct SkidMark *next;    /* 0x54 */
} SkidMark;

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
    struct SkidMark *children; /* 0x74: drawn by func_8002E240 */
    u8 *unk78[6];  /* 0x78 */
} TrackSection;

#endif /* TRACK_H */
