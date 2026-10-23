#ifndef CAR_H
#define CAR_H

#include "common.h"
#include "list.h"

/* A 32-bit world vector or one row of a rotation matrix. */
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

/* One 0x28-byte record per wheel, starting at car + 0x2AC. */
typedef struct {
    s16 unk0;
    u8 unk2[0x2];
    s16 effect;
    u8 unk6[0x6];
    s32 unkC;
    u8 unk10[0x18];
} Wheel;

/* The collision outline a car points to at 0x370. */
typedef struct ContactCorner {
    u8 unk0[4];
    s32 x;
    s32 y;
    u8 unkC[12];
} ContactCorner;
typedef struct ContactShape {
    u8 unk0[28];
    s16 frontExtent;
    s16 rearExtent;
    u8 unk20[2];
    s16 halfWidth;
    u8 unk24[28];
    ContactCorner *corners;
} ContactShape;

/* A race-order or section list node, followed by the car that owns it. */
typedef struct CarLink {
    DoublyLinkedNode node;
    struct Car *car;
} CarLink;

/* A 0x500-byte race object in gCarList: player, AI and traffic cars. */
typedef struct Car {
    Vec3 pos; /* 0x000 */
    u8 unkC[0xC];
    Vec3 basis[3]; /* 0x018 */
    Vec3 rot[3]; /* 0x03C */
    u8 unk60[0x4];
    s32 unk64; /* 0x064 */
    u8 unk68[0x8];
    s32 unk70; /* 0x070 */
    u8 unk74[0x8];
    s32 unk7C; /* 0x07C */
    u8 unk80[0x4];
    s32 unk84; /* 0x084 */
    s32 driveScale; /* 0x088 */
    u8 unk8C[0x4];
    s32 speed; /* 0x090 */
    s32 unk94; /* 0x094 */
    s32 maxSpeed; /* 0x098 */
    Vec3 toCamera; /* 0x09C */
    u8 unkA8[0x8];
    s32 velocityX; /* 0x0B0 */
    s32 velocityY; /* 0x0B4 */
    s32 velocityZ; /* 0x0B8 */
    u8 unkBC[0x8];
    s32 frontVelocityX; /* 0x0C4 */
    s32 frontVelocityY; /* 0x0C8 */
    u8 unkCC[0x4];
    s32 rearVelocityX; /* 0x0D0 */
    s32 rearVelocityY; /* 0x0D4 */
    u8 unkD8[0x1C];
    u8 unkF4; /* 0x0F4 */
    u8 collisionPending; /* 0x0F5 */
    u8 unkF6; /* 0x0F6 */
    u8 unkF7; /* 0x0F7 */
    u8 unkF8; /* 0x0F8 */
    u8 sliding; /* 0x0F9 */
    s16 unkFA; /* 0x0FA */
    u8 unkFC[0x6];
    s16 unk102; /* 0x102 */
    s16 movementHeading; /* 0x104 */
    u8 unk106[0x2];
    s16 unk108; /* 0x108 */
    s16 unk10A; /* 0x10A */
    s16 unk10C; /* 0x10C */
    s16 unk10E; /* 0x10E */
    s16 unk110; /* 0x110 */
    u8 unk112[0x2];
    s16 heading; /* 0x114 */
    u16 fineHeading; /* 0x116 */
    u8 unk118[0x8];
    s16 unk120; /* 0x120 */
    u8 unk122[0x9A];
    s16 unk1BC; /* 0x1BC */
    u8 unk1BE[0x6];
    s16 unk1C4; /* 0x1C4 */
    u8 unk1C6[0x10];
    s16 lap; /* 0x1D6 */
    u8 unk1D8[0x4];
    s16 unk1DC; /* 0x1DC */
    s16 unk1DE; /* 0x1DE */
    s16 segment; /* 0x1E0 */
    u8 unk1E2[0xA];
    s16 type; /* 0x1EC */
    u8 unk1EE[0x2];
    s32 sortKey; /* 0x1F0 */
    s32 lastSegment; /* 0x1F4 */
    s32 regionIndex; /* 0x1F8 */
    u8 unk1FC[0x4];
    s8 mode; /* 0x200 */
    u8 unk201[0x2];
    s8 unk203; /* 0x203 */
    s8 place; /* 0x204 */
    s8 assistRank; /* 0x205 */
    s8 lane; /* 0x206 */
    u8 unk207[0x2];
    s8 unk209; /* 0x209 */
    u8 unk20A; /* 0x20A */
    s8 slot; /* 0x20B */
    s8 cameraMode; /* 0x20C */
    u8 unk20D; /* 0x20D */
    s16 steering; /* 0x20E */
    s16 unk210; /* 0x210 */
    s16 unk212; /* 0x212 */
    s16 orbitAngle; /* 0x214 */
    u8 unk216[0x2];
    s32 lateralSpeed; /* 0x218 */
    s32 unk21C; /* 0x21C */
    u8 unk220[0xC];
    s32 speedBoost; /* 0x22C */
    u8 unk230[0x8];
    s32 flags; /* 0x238 */
    s32 unk23C; /* 0x23C */
    s32 frontGrip; /* 0x240 */
    s32 rearGrip; /* 0x244 */
    s16 unk248; /* 0x248 */
    u8 unk24A[0x4];
    s16 targetSegment; /* 0x24E */
    s32 avoidX; /* 0x250 */
    s32 avoidY; /* 0x254 */
    s32 unk258; /* 0x258 */
    s32 time; /* 0x25C */
    s32 unk260; /* 0x260 */
    s32 unk264; /* 0x264 */
    u8 unk268; /* 0x268 */
    u8 unk269; /* 0x269 */
    u8 unk26A; /* 0x26A */
    u8 unk26B; /* 0x26B */
    u8 unk26C[0xA];
    s16 unk276; /* 0x276 */
    u8 unk278[0xC];
    u16 unk284; /* 0x284 */
    s16 unk286; /* 0x286 */
    s16 unk288; /* 0x288 */
    s16 unk28A; /* 0x28A */
    s32 unk28C; /* 0x28C */
    u8 unk290[0x10];
    s16 unk2A0; /* 0x2A0 */
    s16 unk2A2; /* 0x2A2 */
    s16 unk2A4; /* 0x2A4 */
    s16 unk2A6; /* 0x2A6 */
    s16 unk2A8; /* 0x2A8 */
    s16 unk2AA; /* 0x2AA */
    Wheel wheel[4]; /* 0x2AC */
    char *name; /* 0x34C */
    u32 update; /* 0x350 */
    void (*callback)(u8 *); /* 0x354 */
    u8 unk358[0x8];
    u16 state; /* 0x360 */
    u16 frontRightContact; /* 0x362 */
    u16 frontLeftContact; /* 0x364 */
    u16 rearRightContact; /* 0x366 */
    u16 rearLeftContact; /* 0x368 */
    u8 unk36A[0x2];
    u8 *unk36C; /* 0x36C */
    struct ContactShape *shape; /* 0x370 */
    u8 unk374; /* 0x374 */
    u8 unk375[0x1];
    u8 driver; /* 0x376 */
    u8 unk377[0x9];
    s32 cameraAngle; /* 0x380 */
    u8 unk384[0x4];
    s16 unk388; /* 0x388 */
    s16 unk38A; /* 0x38A */
    u8 unk38C[0x14];
    s32 unk3A0; /* 0x3A0 */
    u16 unk3A4; /* 0x3A4 */
    u8 unk3A6[0x11];
    u8 unk3B7; /* 0x3B7 */
    u8 unk3B8[0x1];
    u8 unk3B9; /* 0x3B9 */
    u8 unk3BA[0x2];
    s32 driveInput; /* 0x3BC */
    u8 unk3C0[0x9];
    u8 unk3C9; /* 0x3C9 */
    u8 unk3CA[0x2];
    s32 penalty; /* 0x3CC */
    s32 unk3D0; /* 0x3D0 */
    u8 unk3D4[0x8];
    struct Car *prev; /* 0x3DC */
    struct Car *next; /* 0x3E0 */
    CarLink order; /* 0x3E4 */
    CarLink sectionLink; /* 0x3F0 */
    u8 unk3FC; /* 0x3FC */
    s8 unk3FD; /* 0x3FD */
    s8 unk3FE; /* 0x3FE */
    s8 unk3FF; /* 0x3FF */
    s8 unk400; /* 0x400 */
    s8 unk401; /* 0x401 */
    s16 unk402; /* 0x402 */
    struct Car *unk404; /* 0x404 */
    s8 unk408; /* 0x408 */
    s8 unk409; /* 0x409 */
    u8 unk40A[0x2];
    s32 unk40C; /* 0x40C */
    u8 reverseSpeed; /* 0x410 */
    u8 unk411[0x3];
    s32 unk414; /* 0x414 */
    s8 unk418; /* 0x418 */
    u8 unk419[0x1];
    s16 unk41A; /* 0x41A */
    s8 unk41C[4]; /* 0x41C */
    s32 unk420[4]; /* 0x420 */
    u8 unk430[0xD0];
} Car;

#endif /* CAR_H */
