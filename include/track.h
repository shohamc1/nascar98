#ifndef TRACK_H
#define TRACK_H

#include "common.h"
#include <psxsdk/libgte.h>

/* A road quad in a section's list: four vertices and its facing. */
typedef struct TrackQuad {
    u8 unk0[0x13];
    u8 flags;               /* 0x13 */
    u8 unk14[2];
    s16 angle;              /* 0x16 */
    SVECTOR *vertex[4];     /* 0x18 */
    struct TrackQuad *next; /* 0x28 */
} TrackQuad;

/* A 0x90-byte track section. gTrackSections[0] points to the array, and
 * prev and next link each section to its neighbours. */
typedef struct TrackSection {
    struct TrackSection *prev; /* 0x00 */
    struct TrackSection *next; /* 0x04 */
    u16 section;               /* 0x08 */
    u8 unkA[4];
    u16 culled;                  /* 0x0E */
    u16 angle;                   /* 0x10 */
    u8 unk12[2];                 /* point index in bits 1 to 7 of 0x12 */
    s32 x;                       /* 0x14 */
    s32 z;                       /* 0x18 */
    u16 height0;                 /* 0x1C */
    s16 height1;                 /* 0x1E */
    u8 *unk20;                   /* 0x20 */
    u8 unk24[4];
    struct TrackQuad *firstQuad; /* 0x28 */
    u8 unk2C[4];
    u8 *callbacks; /* 0x30: nodes run by ListDispatchCallbacks */
    u8 unk34[0x1C];
    s32 unk50; /* 0x50 */
    u8 unk54[0x20];
    u8 *children;  /* 0x74: drawn by func_8002E240, linked at + 0x54 */
    u8 *unk78[6];  /* 0x78 */
} TrackSection;

#endif /* TRACK_H */
