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
    s16 unk2;
    s16 effect;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    u8 unk10[0x10];
    u8 unk20;
    u8 unk21;
    u16 unk22;
    u8 unk24;
    u8 unk25;
    s16 unk26;
} Wheel;

/* One 0x18-byte gear record, six from car + 0x124, filled from the
 * gear-ratio setup tables (D_800980A4) by func_80028754. */
typedef struct {
    s32 ratio;      /* 0x00: drive scale in this gear */
    s32 startSpeed; /* 0x04: the gear covers startSpeed to endSpeed */
    s32 endSpeed;   /* 0x08 */
    s32 lowRpm;     /* 0x0C: rpm at startSpeed */
    s32 highRpm;    /* 0x10: rpm at endSpeed */
    s32 index;      /* 0x14 */
} Gear;

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
    s32 unkC; /* 0x00C */
    s32 unk10; /* 0x010 */
    s32 unk14; /* 0x014 */
    Vec3 basis[3]; /* 0x018 */
    Vec3 rot[3]; /* 0x03C: rows saved as a unit; 0x44 (rot[0].z) is the drag slope, once dragScale */
    Vec3 orient[3]; /* 0x060: x column is the velocity direction */
    s32 unk84; /* 0x084 */
    s32 driveScale; /* 0x088 */
    s32 unk8C; /* 0x08C */
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
    u8 automatic; /* 0x0F6: picks gears by speed; manual shifts need 0 */
    u8 unkF7; /* 0x0F7 */
    u8 unkF8; /* 0x0F8 */
    u8 sliding; /* 0x0F9 */
    s16 unkFA; /* 0x0FA */
    s16 unkFC; /* 0x0FC */
    s16 unkFE; /* 0x0FE */
    s16 unk100; /* 0x100 */
    s16 unk102; /* 0x102 */
    s16 movementHeading; /* 0x104 */
    u8 unk106[0x2];
    s16 rpm; /* 0x108 */
    s16 unk10A; /* 0x10A */
    s16 gearIndex; /* 0x10C */
    s16 unk10E; /* 0x10E */
    s16 unk110; /* 0x110 */
    s16 unk112; /* 0x112 */
    s16 heading; /* 0x114 */
    u16 fineHeading; /* 0x116 */
    s16 unk118; /* 0x118 */
    s16 unk11A; /* 0x11A */
    s16 unk11C; /* 0x11C */
    s16 unk11E; /* 0x11E */
    s16 unk120; /* 0x120 */
    u8 unk122[0x2];
    Gear gear[6]; /* 0x124 */
    s16 unk1B4; /* 0x1B4 */
    s16 unk1B6; /* 0x1B6 */
    s16 unk1B8; /* 0x1B8 */
    s16 unk1BA; /* 0x1BA */
    s16 unk1BC; /* 0x1BC */
    s16 unk1BE; /* 0x1BE */
    s16 unk1C0; /* 0x1C0 */
    s16 unk1C2; /* 0x1C2 */
    s16 unk1C4; /* 0x1C4 */
    s16 unk1C6; /* 0x1C6 */
    s16 unk1C8; /* 0x1C8 */
    s16 unk1CA; /* 0x1CA */
    s16 unk1CC; /* 0x1CC */
    s16 unk1CE; /* 0x1CE */
    s16 unk1D0; /* 0x1D0 */
    s16 unk1D2; /* 0x1D2 */
    s16 unk1D4; /* 0x1D4 */
    s16 lap; /* 0x1D6 */
    s16 unk1D8; /* 0x1D8 */
    u8 unk1DA[0x2];
    s16 unk1DC; /* 0x1DC */
    s16 unk1DE; /* 0x1DE */
    s16 segment; /* 0x1E0 */
    s16 unk1E2; /* 0x1E2 */
    s16 unk1E4; /* 0x1E4 */
    u8 unk1E6[0x4];
    s16 unk1EA; /* 0x1EA */
    s16 type; /* 0x1EC */
    u8 unk1EE[0x2];
    s32 sortKey; /* 0x1F0 */
    s32 lastSegment; /* 0x1F4 */
    s32 regionIndex; /* 0x1F8 */
    s32 unk1FC; /* 0x1FC */
    s8 mode; /* 0x200 */
    u8 unk201; /* 0x201 */
    u8 unk202[0x1];
    s8 unk203; /* 0x203 */
    s8 place; /* 0x204 */
    s8 assistRank; /* 0x205 */
    s8 lane; /* 0x206 */
    u8 unk207; /* 0x207 */
    u8 unk208; /* 0x208 */
    s8 unk209; /* 0x209 */
    u8 unk20A; /* 0x20A */
    s8 slot; /* 0x20B */
    s8 cameraMode; /* 0x20C */
    u8 unk20D; /* 0x20D */
    s16 steering; /* 0x20E: offset from heading, also headingOffset */
    s16 unk210; /* 0x210 */
    s16 unk212; /* 0x212 */
    s16 orbitAngle; /* 0x214 */
    u8 unk216[0x2];
    s32 lateralSpeed; /* 0x218 */
    s32 unk21C; /* 0x21C */
    u8 unk220[0x8];
    s32 unk228; /* 0x228 */
    s32 speedBoost; /* 0x22C */
    u8 unk230[0x4];
    s32 unk234; /* 0x234 */
    s32 flags; /* 0x238 */
    s32 unk23C; /* 0x23C */
    s32 frontGrip; /* 0x240 */
    s32 rearGrip; /* 0x244 */
    s16 unk248; /* 0x248 */
    s16 unk24A; /* 0x24A */
    s16 unk24C; /* 0x24C */
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
    s16 unk26C[15]; /* 0x26C */
    s16 unk28A; /* 0x28A */
    s32 unk28C; /* 0x28C */
    s32 unk290; /* 0x290 */
    s32 unk294; /* 0x294 */
    s32 unk298; /* 0x298 */
    s32 unk29C; /* 0x29C */
    s16 unk2A0; /* 0x2A0 */
    s16 unk2A2; /* 0x2A2 */
    s16 unk2A4; /* 0x2A4 */
    s16 unk2A6; /* 0x2A6 */
    s16 unk2A8; /* 0x2A8 */
    s16 unk2AA; /* 0x2AA */
    Wheel wheel[4]; /* 0x2AC */
    char *name; /* 0x34C */
    void (*update)(struct Car *); /* 0x350 */
    void (*callback)(struct Car *); /* 0x354 */
    s8 unk358; /* 0x358 */
    u8 unk359[0x7];
    u16 state; /* 0x360 */
    u16 frontRightContact; /* 0x362 */
    u16 frontLeftContact; /* 0x364 */
    u16 rearRightContact; /* 0x366 */
    u16 rearLeftContact; /* 0x368 */
    u8 unk36A[0x2];
    u8 *unk36C; /* 0x36C */
    struct ContactShape *shape; /* 0x370 */
    u8 unk374; /* 0x374 */
    s8 unk375; /* 0x375 */
    u8 driver; /* 0x376 */
    u8 unk377[0x5];
    s32 unk37C; /* 0x37C */
    s32 cameraAngle; /* 0x380 */
    u8 unk384[0x4];
    s16 unk388; /* 0x388 */
    s16 unk38A; /* 0x38A */
    u8 unk38C[0x14];
    s32 unk3A0; /* 0x3A0 */
    u16 unk3A4; /* 0x3A4 */
    u8 unk3A6[8]; /* 0x3A6 */
    u8 unk3AE[8]; /* 0x3AE */
    s8 unk3B6; /* 0x3B6 */
    u8 unk3B7; /* 0x3B7 */
    s8 unk3B8; /* 0x3B8 */
    u8 unk3B9; /* 0x3B9 */
    s16 unk3BA; /* 0x3BA */
    s32 driveInput; /* 0x3BC */
    s32 unk3C0; /* 0x3C0 */
    s8 unk3C4; /* 0x3C4 */
    s8 unk3C5; /* 0x3C5 */
    u8 unk3C6; /* 0x3C6 */
    u8 unk3C7; /* 0x3C7 */
    u8 unk3C8[0x1];
    u8 unk3C9; /* 0x3C9 */
    s8 unk3CA; /* 0x3CA */
    u8 unk3CB[0x1];
    s32 penalty; /* 0x3CC */
    s32 unk3D0; /* 0x3D0 */
    u8 unk3D4[0x4];
    struct Car *unk3D8; /* 0x3D8 */
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
