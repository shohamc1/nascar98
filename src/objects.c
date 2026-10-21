#include "common.h"
#include "libpress.h"
#include "fixed_addrs.h"
#include <psxsdk/libgpu.h>
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/libcd.h>
#include <psxsdk/libgte.h>
#include "gte.h"
#include <psxsdk/libapi.h>
#include <psxsdk/libspu.h>
#include <psxsdk/libc.h>
#include <psxsdk/kernel.h>
#include "game.h"

extern s32 D_800B9D5C[];
extern void func_8001E7EC(void *, s32, s32);
extern u16 D_800A38C0[];
extern s32 D_800A2E90w15[] asm("D_800A2E90.NON_MATCHING");
extern u8 D_800A2EE4w15[] asm("D_800A2EE4.NON_MATCHING");
extern u8 D_800A2EDAw15[] asm("D_800A2EDA.NON_MATCHING");

extern s32 D_800A39C8[];
extern s32 D_800A2EA4nm[] asm("D_800A2EA4.NON_MATCHING");
extern s32 D_800A3A2CAbsolute[];
extern s32 D_800A3A34Absolute[];
typedef struct ListNode28 ListNode28;
typedef struct DoublyLinkedNode {
    struct DoublyLinkedNode *next;
    struct DoublyLinkedNode *previous;
} DoublyLinkedNode;
extern void func_8001F2C4(s32 arg0, s32 arg1, s32 arg2);
extern void func_8001ED84(s32 *vec);
extern ListNode28 *D_800A3A40Absolute[];
extern void (*D_80091080[])(void *);
typedef struct {
    u8 pad[16];
} Unk16;
extern s32 D_800A2EC4w15[] asm("D_800A2EC4.NON_MATCHING");
extern u8 *D_800A3668, *D_800A384C, *D_800A3854, *D_800A3A2C, *D_800A3A34;
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A36B0;
extern s32 D_800A36B8;
extern s32 D_800A36C8;
extern s32 D_800A36D0;
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A3784;
extern s32 D_800A3790;
extern s32 D_800A3794;
extern s32 D_800A3798;
extern s32 D_800A379C;
extern s32 D_800A37A4;
extern s32 D_800A37AC;
extern s32 D_800A37B4;
extern s32 D_800A37C4;
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A3784, D_800A3790, D_800A3794, D_800A3798, D_800A379C,
    D_800A37A4, D_800A37AC, D_800A37B4, D_800A37C4;
extern s32 D_800A3784, D_800A3790, D_800A3794, D_800A3798, D_800A379C,
    D_800A37A4, D_800A37AC, D_800A37B4, D_800A37C4;
extern s32 D_800A36B0, D_800A36B8, D_800A36C0, D_800A36C8, D_800A36D0,
    D_800A36D4, D_800A36D8, D_800A36DC, D_800A36E8;
extern s32 D_800A3784, D_800A3790, D_800A3794, D_800A3798, D_800A379C,
    D_800A37A4, D_800A37AC, D_800A37B4, D_800A37C4;
void SystemShowFatalError(char *message);
u32 MathSqrt(u32 value);
void RandomCountMark(void);
s32 RandomSeedGet(void);
void RandomSeedSet(s32 seed);
s32 RandomScaledGet(s32 scale);
void GraphicsAddPolyFT4(u8 *arg0);
void FontSetColor(s16 red, s16 green, s16 blue);
void FontDrawString(s8 *text, s32 x, s32 y, s32 scale);
void func_80018588(void *timeValue, s32 flags, s32 buffer);
void func_80018768(void *arg0, s32 x, s32 y, s32 scale);
void func_80018848(void *arg0, s32 arg1, s32 arg2);
void FontDrawPaddedNumber(s32 value, s32 x, s32 y, s32 scale);
void func_80018B18(s32 value, s32 x, s32 y, s32 scale);
void FontDrawNumber(s32 value, s32 x, s32 y, s32 scale);
void func_800197D4(s32 kind, s32 x, s32 y);
void func_80019A00(s16 arg0, u8 *arg1, s32 arg2);
void func_8001C34C(void);
void ListInsertBefore(ListNode28 **head, ListNode28 *node, ListNode28 *before);
void ListRemoveNode(ListNode28 **head, ListNode28 *target);
void func_8001C668(void *arg0, void *arg1);
void ListPushFront(u8 *node, u8 **head, u8 **tail);
void ListRemoveNodeWithTail(ListNode28 *node, ListNode28 **head,
                            ListNode28 **tail);
void ListPushFrontDoublyLinked(DoublyLinkedNode *node, DoublyLinkedNode **last,
                               DoublyLinkedNode **first);
void func_8001C99C(u8 *arg0);
void func_8001CAB8(u8 *arg0);
void func_8001CBD4(u8 *arg0);
void func_8001CC7C(u8 *arg0);
void func_8001CDDC(u8 *arg0);
void func_8001CF38(u8 *arg0);
void ListDispatchCallbacks(u8 *arg0);
void func_8001D108(u8 *arg0);
void func_8001D1B0(s32 *destination, s32 *source);
void func_8001D1E4(void);
void func_8001D218(void);
void func_8001D778(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5,
                   u8 arg6, s32 arg7);
void func_8001DA48(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_8001DF60(void);
void func_8001DFC8(void);
Unk16 *func_8001E040(s32 i);
void GraphicsLoadImageBank(s32 fileName);
void func_8001E230(s32 arg0, s32 arg1);
void GraphicsLoadImageWithXOffset(s32 xOffset);
void func_8001E7EC(void *arg0, s32 arg1, s32 arg2);
void GraphicsSetGeomOffsetForMode(s32 geomOffsetX, s32 mode);
void GraphicsSetClearColor(u8 r, u8 g, u8 b);
void GraphicsApplyDisplayEnvironments(void);
void GraphicsPartitionWorkBuffers(void);
void func_8001EBE8(s32 *p);
void func_8001EC38(s32 *arg0);
void func_8001EC88(s32 *a, s32 *b, s32 *c);
void func_8001ECD8(void);
void func_8001ED14(s32 *p);
void func_8001ED4C(s32 *p);
void func_8001ED84(s32 *vec);
void func_8001EE74(s32 *arg0);
void func_8001EEC4(s32 *arg0);
void MatrixCombineState(void);
void func_8001F198(void);
void MatrixRotateVector(s32 *vec);
void func_8001F2C4(s32 arg0, s32 arg1, s32 arg2);
void func_8001F440(s32 arg0, s32 arg1, s32 arg2);
void func_8001F5BC(s32 arg0, s32 indexA, s32 indexB);
void func_8001F684(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8001F728(s32 arg0);
void func_8001F828(s32 *p);
void func_8001F874(s32 *arg0);
void MatrixStoreToObject(s32 *object);
void func_8001F90C(s32 arg0, s32 arg1, s32 arg2, s16 *arg3);
void MatrixSaveState(void);
void MatrixRestoreState(void);
void func_8001FAC0(u8 *arg0, s32 index);
void func_8001FB28(u8 *arg0, s32 index);
s32 func_8001FB80(void *arg0);
s32 VectorGetMagnitude3D(s32 x, s32 y, s32 z);

s32 VectorGetMagnitude2D(void *arg0) {
    s32 dx;
    s32 dy;

    dx = *(s32 *)((u8 *)arg0 + 0x9C);
    dy = *(s32 *)((u8 *)arg0 + 0xA0);
    return MathSqrt(dx * dx + dy * dy);
}

INCLUDE_RODATA("asm/nonmatchings/objects", D_8008CF28);
extern char D_8008CF28[];
extern u32 D_800A38F4Abs[] asm("D_800A38F4.NON_MATCHING");
extern s32 D_800A2DE4Small asm("D_800A2DE4.NON_MATCHING");
extern s32 D_800A3A38Small asm("D_800A3A38.NON_MATCHING");
extern s32 D_800A37E8Small asm("D_800A37E8.NON_MATCHING");
extern s32 D_800A3550Small asm("D_800A3550.NON_MATCHING");
extern s32 D_800A3804Small asm("D_800A3804.NON_MATCHING");
extern s32 D_800A3A3CSmall asm("D_800A3A3C.NON_MATCHING");
extern s32 D_800A2DECSmall asm("D_800A2DEC.NON_MATCHING");
extern s32 D_800A397CSmall asm("D_800A397C.NON_MATCHING");
extern s32 D_800A2DF0Small asm("D_800A2DF0.NON_MATCHING");
extern s32 D_800A2DF4Small asm("D_800A2DF4.NON_MATCHING");
extern s32 D_800A3A90Small asm("D_800A3A90.NON_MATCHING");

void ReplayAllocBuffer(void) {
    s32 count;
    void *ptr;
    s32 quotient;

    count = D_800A38F4Abs[0] / 20;
    D_800A2DE4Small = count;
    ptr = HeapAlloc(count * 20);
    D_800A3A38Small = (s32)ptr;
    if (ptr == 0) {
        SystemShowFatalError(D_8008CF28);
    }
    quotient = D_800A2DE4Small / (D_800A2E94[0] + 6);
    D_800A37E8Small = 0;
    D_800A3550Small = 0;
    D_800A3804Small = 0;
    D_800A3A3CSmall = 0;
    D_800A2ED4[0] = 0;
    D_800A2EC8[0] = 0;
    D_800A2DECSmall = 0;
    D_800A397CSmall = 1;
    D_800A2DF0Small = 1;
    D_800A2DF4Small = 1;
    D_800A3A90Small = quotient;
}

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

/* Shared layout of a car and the camera that follows it. */
typedef struct {
    Vec3 pos;               /* 0x000 */
    u8 unkC[0xC];           /* 0x00C */
    Vec3 basis[3];          /* 0x018 */
    Vec3 rot[3];            /* 0x03C */
    u8 unk60[0x3C];         /* 0x060 */
    Vec3 toCamera;          /* 0x09C */
    u8 unkA8[0x6C];         /* 0x0A8 */
    s16 heading;            /* 0x114 */
    u8 unk116[0xCA];        /* 0x116 */
    s16 unk1E0;             /* 0x1E0 */
    u8 unk1E2[0x1E];        /* 0x1E2 */
    s8 unk200;              /* 0x200 */
    u8 unk201[0xA];         /* 0x201 */
    s8 slot;                /* 0x20B */
    s8 cameraMode;          /* 0x20C */
    u8 unk20D[0x7];         /* 0x20D */
    s16 orbitAngle;         /* 0x214 */
    u8 unk216[0x13E];       /* 0x216 */
    void (*callback)(u8 *); /* 0x354 */
    u8 unk358[0x28];        /* 0x358 */
    s32 cameraAngle;        /* 0x380 */
    u8 unk384[0x4];         /* 0x384 */
    s16 unk388;             /* 0x388 */
    s16 unk38A;             /* 0x38A */
    u8 unk38C[0x14];        /* 0x38C */
    s32 unk3A0;             /* 0x3A0 */
} RaceObject;

extern u8 D_800A3680[];
extern void func_80025730(u8 *);
void func_8001FD44(RaceObject *car) {
    s32 count;

    if (car == NULL) {
        return;
    }
    car->cameraMode++;
    car->cameraAngle = car->heading;
    count = car->cameraMode;
    if ((D_800A397CSmall == 2 && count >= 7) ||
        (D_800A397CSmall != 2 && count >= 3)) {
        car->cameraMode = -2;
    }
    if (car->callback == func_80025730 && car->cameraMode == -1) {
        car->cameraMode = 0;
    }
    D_800A3680[0] = 1;
}

void func_8001FDD0(RaceObject *cam, RaceObject *car) {
    u32 dist3;
    u32 dist2;
    s32 cosPitch;
    s32 sinPitch;
    s32 cosYaw;

    func_8001EC38((s32 *)cam);
    car->toCamera.x = car->pos.x - cam->pos.x;
    car->toCamera.y = car->pos.y - cam->pos.y;
    car->toCamera.z = car->pos.z - cam->pos.z;
    func_8001ED84((s32 *)&car->toCamera);
    dist3 = MathSqrt(car->toCamera.x * car->toCamera.x +
                     car->toCamera.y * car->toCamera.y +
                     car->toCamera.z * car->toCamera.z);
    dist2 = MathSqrt(car->toCamera.x * car->toCamera.x +
                     car->toCamera.y * car->toCamera.y);
    cosPitch = MathFixedDivide(dist2, dist3);
    sinPitch = MathFixedDivide(car->toCamera.z, dist3);
    cosYaw = MathFixedDivide(car->toCamera.x, dist2);
    func_8001F684(cosYaw, MathFixedDivide(car->toCamera.y, dist2), cosPitch,
                  sinPitch);
    func_8001F728((s32)&cam->rot[0]);
    func_8001F728((s32)&cam->rot[1]);
    func_8001F728((s32)&cam->rot[2]);
}

s32 func_80024E90(s32, s32, s32 *, s32 *, s32 *);
s32 MathMultiplyFixed16(s32, s32); /* extern */

void func_8001FF3C(u8 *arg0, u8 *arg1) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 value0;
    s32 value1;
    s32 value2;
    s32 value3;
    s32 value4;

    sp18 = -1;
    if ((s16)func_80024E90(*(s32 *)(arg0 + 0x0), *(s32 *)(arg0 + 0x4), &sp18,
                           &sp1C, &sp20) == -1) {
        value0 = MathMultiplyFixed16(
            *(s32 *)(arg1 + 0xDC), ((s32) * (s32 *)(arg0 + 0x0) >> 2) << 0x10);
        value4 = MathMultiplyFixed16(
            *(s32 *)(arg1 + 0xE0), ((s32) * (s32 *)(arg0 + 0x4) >> 2) << 0x10);
        value3 = MathMultiplyFixed16(
            *(s32 *)(arg1 + 0xE4), ((s32) * (s32 *)(arg0 + 0x8) >> 2) << 0x10);
        value1 = MathMultiplyFixed16(
            *(s32 *)(arg1 + 0xDC), ((s32) * (s32 *)(arg1 + 0x0) >> 2) << 0x10);
        value2 = MathMultiplyFixed16(
            *(s32 *)(arg1 + 0xE0), ((s32) * (s32 *)(arg1 + 0x4) >> 2) << 0x10);
        sp1C = ((((s32) * (s32 *)(arg0 + 0x8) >> 2) -
                 ((s32)((value0 + value4 + value3) -
                        (value1 + value2 +
                         MathMultiplyFixed16(*(s32 *)(arg1 + 0xE4),
                                             ((s32) * (s32 *)(arg1 + 0x8) >> 2)
                                                 << 0x10))) >>
                  0x10)) *
                4) +
               0x12C;
    } else {
        sp1C = (sp1C * 4) + 0x12C;
    }
    if (*(s32 *)(arg0 + 0x8) < sp1C) {
        *(s32 *)(arg0 + 0x8) = sp1C;
    }
}

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    u8 unkC[0x4C];
} TrackPoint;

/* One 0x90-byte entry of the array at D_800BE980. */
typedef struct {
    u8 unk0[0x10];
    u32 unk10 : 17;
    u32 point : 7;
    u32 unk10Top : 8;
    s32 unk14;
    s32 unk18;
    u8 unk1C[0x4];
    u8 *unk20;
    u8 unk24[0x6C];
} TrackRacer;

s32 MathFixedDivide(s32 numerator, s32 denominator);
s32 MathGetAngleDelta(s32 arg0, s32 arg1);
void func_8002DA30(s32 *arg0);
extern s32 D_800A2DCCSmall asm("D_800A2DCC.NON_MATCHING");
extern s32 D_800A2DD0Small asm("D_800A2DD0.NON_MATCHING");
extern s32 D_800A2DD4Small asm("D_800A2DD4.NON_MATCHING");
extern s32 D_800A2DD8Small asm("D_800A2DD8.NON_MATCHING");
extern s32 D_800A2DDCSmall asm("D_800A2DDC.NON_MATCHING");
extern u8 D_800A2DE0Small asm("D_800A2DE0.NON_MATCHING");
extern u8 D_800A2DE1Small asm("D_800A2DE1.NON_MATCHING");
extern s32 D_800A2DE8Small asm("D_800A2DE8.NON_MATCHING");
/* A global seen through a 16-byte type: gcc reads it as a plain scalar for
 * alias analysis, but its size keeps it out of $gp addressing. */
typedef struct {
    s32 unk[4];
} FarVar;
#define FAR_VAR(type, var) (*(type *)&(var))
extern FarVar gFarFlag2ED8 asm("D_800A2ED8.NON_MATCHING");
extern FarVar gFarFlag2EE8 asm("D_800A2EE8");
extern FarVar gFarFlag39D4 asm("D_800A39D4");
extern FarVar gFarFlag2EDA asm("D_800A2EDA.NON_MATCHING");
extern FarVar gFarPaused asm("D_800A2ED4");
extern FarVar gFarMode2EA4 asm("D_800A2EA4");
extern FarVar gFarMode2CE0 asm("D_800A2CE0.NON_MATCHING");
extern FarVar gFarBlend2EAC asm("D_800A2EAC.NON_MATCHING");
extern FarVar gFarTrack asm("D_800BE980");
extern FarVar gFarPlayer asm("D_800A38AC");
extern FarVar gFarOffsetX asm("D_800AE844");
extern FarVar gFarOffsetY asm("D_800AE848");
extern FarVar gFarOffsetZ asm("D_800AE84C");
extern FarVar gFarCosTable asm("D_800A3A2CAbsolute");
extern FarVar gFarSinTable asm("D_800A3A34Absolute");
extern s32 D_800A3584nm[] asm("D_800A3584.NON_MATCHING");
extern u8 D_800A363Cnm[] asm("D_800A363C.NON_MATCHING");
extern s16 D_800A383Cnm[] asm("D_800A383C.NON_MATCHING");
extern s16 D_800A3840nm[] asm("D_800A3840.NON_MATCHING");
extern s16 D_800A3844nm[] asm("D_800A3844.NON_MATCHING");
extern TrackPoint D_800B1348nm[] asm("D_800B1348.NON_MATCHING");
extern Vec3 D_800B9954nm[] asm("D_800B9954.NON_MATCHING");

#define COS_TABLE FAR_VAR(s32 *, gFarCosTable)
#define SIN_TABLE FAR_VAR(s32 *, gFarSinTable)

/* Aims the camera at the car: stores the car-to-camera vector and rebuilds
 * the camera's rotation rows from its yaw and pitch. */
#define CAMERA_LOOK_AT(cam, car, row0, row1, row2)                             \
    {                                                                          \
        u32 dist3;                                                             \
        u32 dist2;                                                             \
        s32 cosPitch;                                                          \
        s32 sinPitch;                                                          \
        s32 cosYaw;                                                            \
                                                                               \
        func_8001EC38((s32 *)(cam));                                           \
        (car)->toCamera.x = (car)->pos.x - (cam)->pos.x;                       \
        (car)->toCamera.y = (car)->pos.y - (cam)->pos.y;                       \
        (car)->toCamera.z = (car)->pos.z - (cam)->pos.z;                       \
        func_8001ED84((s32 *)&(car)->toCamera);                                \
        dist3 = MathSqrt((car)->toCamera.x * (car)->toCamera.x +               \
                         (car)->toCamera.y * (car)->toCamera.y +               \
                         (car)->toCamera.z * (car)->toCamera.z);               \
        dist2 = MathSqrt((car)->toCamera.x * (car)->toCamera.x +               \
                         (car)->toCamera.y * (car)->toCamera.y);               \
        cosPitch = MathFixedDivide(dist2, dist3);                              \
        sinPitch = MathFixedDivide((car)->toCamera.z, dist3);                  \
        cosYaw = MathFixedDivide((car)->toCamera.x, dist2);                    \
        func_8001F684(cosYaw, MathFixedDivide((car)->toCamera.y, dist2),       \
                      cosPitch, sinPitch);                                     \
        func_8001F728((s32)(row0));                                            \
        func_8001F728((s32)(row1));                                            \
        func_8001F728((s32)(row2));                                            \
    }

/* Update the camera for one car and camera mode. */
void CameraUpdateForCar(RaceObject *cam, RaceObject *car, s32 mode) {
    s32 pos[3];
    s32 unused[4];
    s8 slot;
    s32 speed;
    s32 delta;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 recip;
    s32 count;
    s32 index;
    s32 point;
    u32 dist;
    s16 *from;
    s16 *to;
    TrackRacer *track;
    s16 *rate;
    Vec3 *row0;
    Vec3 *row1;
    Vec3 *row2;
    Vec3 *aimRow0;
    Vec3 *aimRow1;
    Vec3 *aimRow2;

    slot = car->slot;
    D_800A2DE0Small = 0;
    if (FAR_VAR(u8, gFarFlag2ED8) == 0) {
        if (FAR_VAR(s32, gFarMode2EA4) == 2) {
            D_800A2DCCSmall = 0x320;
            D_800A2DD0Small = 0x4B0;
            D_800A2DD4Small = 0xF0;
            D_800A2DD8Small = 0x78;
            D_800A2DDCSmall = 0x82;
        } else {
            D_800A2DCCSmall = 0x2EE;
            D_800A2DD0Small = 0x3E8;
            D_800A2DD4Small = 0xFA;
            D_800A2DD8Small = 0x3C;
            D_800A2DDCSmall = 0x32;
        }
        speed = D_800A2DE8Small;
        car->unk3A0++;
        if (car->unk3A0 >= 2) {
            car->unk3A0 = 0;
        }
        if (mode == 5) {
            mode = 11;
        }
    } else {
        D_800A2DCCSmall = 0x4B0;
        D_800A2DD0Small = 0x708;
        D_800A2DD4Small = 0x1F4;
        D_800A2DD8Small = 0x96;
        speed = 0x5DC;
        if (mode == 7) {
            mode = cam->cameraMode;
        }
        if (mode == 5) {
            D_800A2DE0Small = 1;
        }
    }

    switch (mode) {
    case 0:
        car->orbitAngle = 0;
        cam->basis[0] = car->basis[0];
        cam->basis[1] = car->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[0] = car->rot[0];
        cam->rot[1] = car->rot[1];
        cam->rot[2] = car->rot[2];
        func_8001ED4C((s32 *)cam);
        delta = (car->unk38A + car->unk388) -
                (car->unk38A + car->unk388) / 1024 * 1024;
        recip =
            (0x96 - (delta - 0x200 >= 0 ? (0x400 - delta) >> 2 : delta >> 2))
            << 16;
        cam->pos.x =
            car->pos.x + ((MathMultiplyFixed16(cam->rot[0].y, 100 << 16) +
                           MathMultiplyFixed16(cam->rot[0].z, recip)) >>
                          16);
        cam->pos.y =
            car->pos.y + ((MathMultiplyFixed16(cam->rot[1].y, 100 << 16) +
                           MathMultiplyFixed16(cam->rot[1].z, recip)) >>
                          16);
        cam->pos.z =
            car->pos.z + ((MathMultiplyFixed16(cam->rot[2].y, 100 << 16) +
                           MathMultiplyFixed16(cam->rot[2].z, recip)) >>
                          16);
        break;
    case -1:
        cam->basis[0] = car->basis[0];
        cam->basis[1] = car->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[0] = car->rot[0];
        cam->rot[1] = car->rot[1];
        cam->rot[2] = car->rot[2];
        func_8001ED4C((s32 *)cam);
        if (car->unk200 == 4) {
            cam->pos.x =
                car->pos.x + ((MathMultiplyFixed16(cam->rot[0].x, -500 << 16) +
                               MathMultiplyFixed16(cam->rot[0].z, 400 << 16)) >>
                              16);
            cam->pos.y =
                car->pos.y + ((MathMultiplyFixed16(cam->rot[1].x, -500 << 16) +
                               MathMultiplyFixed16(cam->rot[1].z, 400 << 16)) >>
                              16);
            cam->pos.z =
                car->pos.z + ((MathMultiplyFixed16(cam->rot[2].x, -500 << 16) +
                               MathMultiplyFixed16(cam->rot[2].z, 400 << 16)) >>
                              16);
        } else if (FAR_VAR(s32, gFarMode2EA4) != 0) {
            cam->pos.x =
                car->pos.x + ((MathMultiplyFixed16(cam->rot[0].x, -100 << 16) +
                               MathMultiplyFixed16(cam->rot[0].z, 225 << 16)) >>
                              16);
            cam->pos.y =
                car->pos.y + ((MathMultiplyFixed16(cam->rot[1].x, -100 << 16) +
                               MathMultiplyFixed16(cam->rot[1].z, 225 << 16)) >>
                              16);
            cam->pos.z =
                car->pos.z + ((MathMultiplyFixed16(cam->rot[2].x, -100 << 16) +
                               MathMultiplyFixed16(cam->rot[2].z, 225 << 16)) >>
                              16);
        } else {
            cam->pos.x =
                car->pos.x + ((MathMultiplyFixed16(cam->rot[0].x, -250 << 16) +
                               MathMultiplyFixed16(cam->rot[0].z, 375 << 16)) >>
                              16);
            cam->pos.y =
                car->pos.y + ((MathMultiplyFixed16(cam->rot[1].x, -250 << 16) +
                               MathMultiplyFixed16(cam->rot[1].z, 375 << 16)) >>
                              16);
            cam->pos.z =
                car->pos.z + ((MathMultiplyFixed16(cam->rot[2].x, -250 << 16) +
                               MathMultiplyFixed16(cam->rot[2].z, 375 << 16)) >>
                              16);
        }
        dx = car->pos.x;
        dy = car->pos.y;
        dz = car->pos.z;
        car->pos.x += MathMultiplyFixed16(car->rot[0].x, 1500 << 16) >> 16;
        car->pos.y += MathMultiplyFixed16(car->rot[0].y, 1500 << 16) >> 16;
        car->pos.z += MathMultiplyFixed16(car->rot[0].z, 1500 << 16) >> 16;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        car->pos.x = dx;
        car->pos.y = dy;
        car->pos.z = dz;
        break;
    case -2:
        car->orbitAngle = 0;
        cam->basis[0] = car->basis[0];
        cam->basis[1] = car->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[0] = car->rot[0];
        cam->rot[1] = car->rot[1];
        cam->rot[2] = car->rot[2];
        func_8001ED4C((s32 *)cam);
        delta = (car->unk38A + car->unk388) -
                (car->unk38A + car->unk388) / 1024 * 1024;
        recip =
            (0x64 - (delta - 0x200 >= 0 ? (0x400 - delta) >> 2 : delta >> 2))
            << 16;
        cam->pos.x =
            car->pos.x + ((MathMultiplyFixed16(cam->rot[0].x, 250 << 16) +
                           MathMultiplyFixed16(cam->rot[0].z, recip)) >>
                          16);
        cam->pos.y =
            car->pos.y + ((MathMultiplyFixed16(cam->rot[1].x, 250 << 16) +
                           MathMultiplyFixed16(cam->rot[1].z, recip)) >>
                          16);
        cam->pos.z =
            car->pos.z + ((MathMultiplyFixed16(cam->rot[2].x, 250 << 16) +
                           MathMultiplyFixed16(cam->rot[2].z, recip)) >>
                          16);
        break;
    case 1:
        if (FAR_VAR(s32, gFarPaused) == 0 && D_800A2DE1Small == 0) {
            delta = MathGetAngleDelta(car->cameraAngle, car->heading);
            if (delta < 0) {
                delta = delta / 10 - 1;
            } else if (delta > 0) {
                delta = delta / 10 + 1;
            }
            car->cameraAngle = (car->cameraAngle - delta + 0x400) & 0x3FF;
        }
        cam->pos.x =
            car->pos.x - (MathMultiplyFixed16(COS_TABLE[car->cameraAngle],
                                              D_800A2DCCSmall << 16) >>
                          16);
        cam->pos.y =
            car->pos.y - (MathMultiplyFixed16(SIN_TABLE[car->cameraAngle],
                                              D_800A2DCCSmall << 16) >>
                          16);
        cam->pos.z = car->pos.z + D_800A2DD4Small;
        if (FAR_VAR(u8, gFarFlag2EE8) != 0) {
            cam->rot[0] = car->rot[0];
            cam->rot[1] = car->rot[1];
            cam->rot[2] = car->rot[2];
            func_8001ED4C((s32 *)cam);
            dz = car->pos.z -
                 (MathMultiplyFixed16(cam->rot[2].x, D_800A2DCCSmall << 16) >>
                  16) +
                 D_800A2DD4Small * 3 / 4;
            if (cam->pos.z < dz) {
                cam->pos.z = dz;
            }
            cam->rot[0] = cam->basis[0];
            cam->rot[1] = cam->basis[1];
            cam->rot[2] = cam->basis[2];
        }
        if (D_800A397CSmall == 2 && FAR_VAR(u8, gFarFlag39D4) != 0) {
            func_8001FF3C((u8 *)cam, (u8 *)car);
        }
        car->pos.z += D_800A2DD8Small;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        car->pos.z -= D_800A2DD8Small;
        break;
    case 2:
        if (FAR_VAR(s32, gFarPaused) == 0 && D_800A2DE1Small == 0) {
            delta = MathGetAngleDelta(car->cameraAngle, car->heading);
            if (delta < 0) {
                delta = delta / 8 - 1;
            } else if (delta > 0) {
                delta = delta / 8 + 1;
            }
            car->cameraAngle = (car->cameraAngle - delta + 0x400) & 0x3FF;
        }
        cam->pos.x =
            car->pos.x - (MathMultiplyFixed16(COS_TABLE[car->cameraAngle],
                                              D_800A2DD0Small << 16) >>
                          16);
        cam->pos.y =
            car->pos.y - (MathMultiplyFixed16(SIN_TABLE[car->cameraAngle],
                                              D_800A2DD0Small << 16) >>
                          16);
        cam->pos.z = car->pos.z + 0x1C2;
        if (FAR_VAR(u8, gFarFlag2EE8) != 0) {
            cam->rot[0] = car->rot[0];
            cam->rot[1] = car->rot[1];
            cam->rot[2] = car->rot[2];
            func_8001ED4C((s32 *)cam);
            dz = car->pos.z -
                 (MathMultiplyFixed16(cam->rot[2].x, D_800A2DD0Small << 16) >>
                  16) +
                 0x142;
            if (cam->pos.z < dz) {
                cam->pos.z = dz;
            }
            cam->rot[0] = cam->basis[0];
            cam->rot[1] = cam->basis[1];
            cam->rot[2] = cam->basis[2];
        }
        if (D_800A397CSmall == 2 && FAR_VAR(u8, gFarFlag39D4) != 0) {
            func_8001FF3C((u8 *)cam, (u8 *)car);
        }
        car->pos.z += D_800A2DDCSmall;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        car->pos.z -= D_800A2DDCSmall;
        break;
    case 11:
        cam->basis[0] = car->basis[0];
        cam->basis[1] = car->basis[1];
        cam->basis[2] = car->basis[2];
        if (FAR_VAR(u8, gFarFlag2EDA) != 0) {
            delta = MathGetAngleDelta(car->cameraAngle,
                                      (car->heading + 0x200) & 0x3FF);
            if (delta < 0) {
                delta = delta / 8 - 1;
            } else if (delta > 0) {
                delta = delta / 8 + 1;
            }
            car->cameraAngle = (car->cameraAngle - delta + 0x400) & 0x3FF;
            cam->pos.x =
                car->pos.x - (MathMultiplyFixed16(COS_TABLE[car->cameraAngle],
                                                  D_800A2DCCSmall << 16) >>
                              16);
            cam->pos.y =
                car->pos.y - (MathMultiplyFixed16(SIN_TABLE[car->cameraAngle],
                                                  D_800A2DCCSmall << 16) >>
                              16);
            cam->pos.z = car->pos.z + 0xFA;
        } else {
            cam->pos.x =
                car->pos.x +
                (MathMultiplyFixed16(cam->basis[0].x, D_800A2DCCSmall << 16) >>
                 16);
            cam->pos.y =
                car->pos.y +
                (MathMultiplyFixed16(cam->basis[1].x, D_800A2DCCSmall << 16) >>
                 16);
            cam->pos.z =
                car->pos.z +
                (MathMultiplyFixed16(cam->basis[2].x, D_800A2DCCSmall << 16) >>
                 16) +
                0xFA;
        }
        if (FAR_VAR(u8, gFarFlag39D4) != 0) {
            func_8001FF3C((u8 *)cam, (u8 *)car);
        }
        car->pos.z += D_800A2DD8Small;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        car->pos.z -= D_800A2DD8Small;
        break;
    case 3:
        cam->basis[0] = car->basis[0];
        cam->rot[0] = cam->basis[0];
        cam->basis[1] = car->basis[1];
        cam->rot[1] = cam->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[2] = cam->basis[2];
        if (FAR_VAR(s32, gFarPaused) == 0 && FAR_VAR(u8, gFarFlag2ED8) == 0) {
            car->orbitAngle = (car->orbitAngle + 6) & 0x3FF;
        }
        cam->pos.x =
            car->pos.x - (MathMultiplyFixed16(COS_TABLE[car->orbitAngle],
                                              D_800A2DCCSmall << 16) >>
                          16);
        cam->pos.y =
            car->pos.y - (MathMultiplyFixed16(SIN_TABLE[car->orbitAngle],
                                              D_800A2DCCSmall << 16) >>
                          16);
        cam->pos.z = car->pos.z + D_800A2DD4Small;
        if (FAR_VAR(u8, gFarFlag39D4) != 0) {
            func_8001FF3C((u8 *)cam, (u8 *)car);
        }
        car->pos.z += D_800A2DD8Small;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        car->pos.z -= D_800A2DD8Small;
        break;
    case 4:
    case 7:
    case 8:
    case 18:
        cam->basis[0] = car->basis[0];
        cam->rot[0] = cam->basis[0];
        cam->basis[1] = car->basis[1];
        cam->rot[1] = cam->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[2] = cam->basis[2];
        index = car->unk1E0;
        if (index >= 0) {
            point = FAR_VAR(TrackRacer *, gFarTrack)[index].point;
        } else {
            point = 0;
        }
        cam->pos.x = D_800B1348nm[point].x;
        cam->pos.y = D_800B1348nm[point].y;
        cam->pos.z = D_800B1348nm[point].z;
        dx = car->pos.x - cam->pos.x;
        dy = car->pos.y - cam->pos.y;
        dz = car->pos.z - cam->pos.z;
        dx = dx > 0x7FFF ? 0x7FFF : (dx < -0x7FFF ? -0x7FFF : dx);
        dy = dy > 0x7FFF ? 0x7FFF : (dy < -0x7FFF ? -0x7FFF : dy);
        recip = MathFixedDivide(speed, MathSqrt(dx * dx + dy * dy + dz * dz));
        cam->pos.x = car->pos.x - (MathMultiplyFixed16(dx << 16, recip) >> 16);
        cam->pos.y = car->pos.y - (MathMultiplyFixed16(dy << 16, recip) >> 16);
        cam->pos.z = car->pos.z - (MathMultiplyFixed16(dz << 16, recip) >> 16);
        func_8002DA30((s32 *)cam);
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        break;
    case 5:
        cam->basis[0] = car->basis[0];
        cam->basis[1] = car->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[0] = car->rot[0];
        cam->rot[1] = car->rot[1];
        cam->rot[2] = car->rot[2];
        func_8001ED4C((s32 *)cam);
        cam->pos.x =
            car->pos.x + ((MathMultiplyFixed16(cam->rot[0].y, 100 << 16) +
                           MathMultiplyFixed16(cam->rot[0].z, 150 << 16)) >>
                          16);
        cam->pos.y =
            car->pos.y + ((MathMultiplyFixed16(cam->rot[1].y, 100 << 16) +
                           MathMultiplyFixed16(cam->rot[1].z, 150 << 16)) >>
                          16);
        cam->pos.z =
            car->pos.z + ((MathMultiplyFixed16(cam->rot[2].y, 100 << 16) +
                           MathMultiplyFixed16(cam->rot[2].z, 150 << 16)) >>
                          16);
        func_8001F2C4(0x200, 0, 0);
        func_8001F728((s32)&cam->rot[0]);
        func_8001F728((s32)&cam->rot[1]);
        func_8001F728((s32)&cam->rot[2]);
        cam->rot[0].y = -cam->rot[0].y;
        cam->rot[1].y = -cam->rot[1].y;
        cam->rot[2].y = -cam->rot[2].y;
        break;
    case 6:
        cam->pos.x =
            car->pos.x -
            (MathMultiplyFixed16(cam->basis[0].x, D_800A2DCCSmall << 16) >> 16);
        cam->pos.y =
            car->pos.y -
            (MathMultiplyFixed16(cam->basis[1].x, D_800A2DCCSmall << 16) >> 16);
        cam->pos.z =
            car->pos.z -
            (MathMultiplyFixed16(cam->basis[2].x, D_800A2DCCSmall << 16) >>
             16) +
            0x9C4;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        break;
    case 12:
        cam->basis[0] = car->basis[0];
        cam->rot[0] = cam->basis[0];
        cam->basis[1] = car->basis[1];
        cam->rot[1] = cam->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[2] = cam->basis[2];
        index = car->slot;
        if ((car->unk1E0 >= D_800A3584nm[index] + 1 ||
             D_800A363Cnm[index] != 0) &&
            FAR_VAR(s32, gFarPaused) == 0) {
            count = D_800A363Cnm[index]++;
            dx = car->pos.x - (MathMultiplyFixed16(COS_TABLE[car->heading],
                                                   D_800A2DCCSmall << 16) >>
                               16);
            dy = car->pos.y - (MathMultiplyFixed16(SIN_TABLE[car->heading],
                                                   D_800A2DCCSmall << 16) >>
                               16);
            dz = car->pos.z + D_800A2DD4Small;
            dx = D_800B9954nm[car->slot].x - dx;
            dy = D_800B9954nm[car->slot].y - dy;
            dz = D_800B9954nm[car->slot].z - dz;
            if (count >= 0x1F) {
                count = 0x1E;
                car->cameraMode = 1;
            }
            D_800B9954nm[car->slot].x -= dx * count / 30;
            D_800B9954nm[car->slot].y -= dy * count / 30;
            D_800B9954nm[car->slot].z -= dz * count / 30;
            car->cameraAngle = car->heading;
        }
        cam->pos.x = D_800B9954nm[car->slot].x;
        cam->pos.y = D_800B9954nm[car->slot].y;
        cam->pos.z = D_800B9954nm[car->slot].z;
        func_8002DA30((s32 *)cam);
        car->pos.z += D_800A2DD8Small;
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        car->pos.z -= D_800A2DD8Small;
        break;
    case 13:
        cam->basis[0] = car->basis[0];
        cam->basis[1] = car->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[0] = car->rot[0];
        cam->rot[1] = car->rot[1];
        cam->rot[2] = car->rot[2];
        func_8001ED4C((s32 *)cam);
        cam->pos.x =
            car->pos.x +
            ((MathMultiplyFixed16(cam->rot[0].x, D_800A383Cnm[slot] << 16) -
              MathMultiplyFixed16(cam->rot[0].y, D_800A3840nm[slot] << 16) +
              MathMultiplyFixed16(cam->rot[0].z, D_800A3844nm[slot] << 16)) >>
             16);
        cam->pos.y =
            car->pos.y +
            ((MathMultiplyFixed16(cam->rot[1].x, D_800A383Cnm[slot] << 16) -
              MathMultiplyFixed16(cam->rot[1].y, D_800A3840nm[slot] << 16) +
              MathMultiplyFixed16(cam->rot[1].z, D_800A3844nm[slot] << 16)) >>
             16);
        cam->pos.z =
            car->pos.z +
            ((MathMultiplyFixed16(cam->rot[2].x, D_800A383Cnm[slot] << 16) -
              MathMultiplyFixed16(cam->rot[2].y, D_800A3840nm[slot] << 16) +
              MathMultiplyFixed16(cam->rot[2].z, D_800A3844nm[slot] << 16)) >>
             16);
        row0 = &cam->rot[0];
        row1 = &cam->rot[1];
        row2 = &cam->rot[2];
        if (D_800A383Cnm[slot] >= -0x15D) {
            cam->rot[0] = car->rot[1];
            cam->rot[1].x = -car->rot[0].x;
            cam->rot[1].y = -car->rot[0].y;
            cam->rot[1].z = -car->rot[0].z;
            cam->rot[2] = car->rot[2];
            func_8001ED4C((s32 *)cam);
        } else {
            dx = MathMultiplyFixed16(cam->rot[0].x, 350 << 16) >> 16;
            dy = MathMultiplyFixed16(cam->rot[1].x, 350 << 16) >> 16;
            car->pos.x -= dx;
            car->pos.y -= dy;
            car->pos.z += 0x4B;
            CAMERA_LOOK_AT(cam, car, row0, row1, row2);
            car->pos.x += dx;
            car->pos.y += dy;
            car->pos.z -= 0x4B;
            if (FAR_VAR(s32, gFarPaused) == 0) {
                rate = &D_800A3840nm[slot];
                *rate = *rate > 0 ? *rate - 10 : 0;
                D_800A3844nm[slot] =
                    D_800A3844nm[slot] >= 0xFA ? 0xFA : D_800A3844nm[slot] + 5;
            }
        }
        if (FAR_VAR(s32, gFarPaused) == 0) {
            D_800A383Cnm[slot] -= 20;
        }
        break;
    case 16:
        cam->basis[0] = car->basis[0];
        cam->rot[0] = cam->basis[0];
        cam->basis[1] = car->basis[1];
        cam->rot[1] = cam->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[2] = cam->basis[2];
        if (FAR_VAR(s32, gFarMode2CE0) == 10) {
            to = *(s16 **)(FAR_VAR(u8 *, gFarTrack) + 0xB28);
            from = *(s16 **)(FAR_VAR(u8 *, gFarTrack) + 0xB3C);
        } else {
            to = *(s16 **)(FAR_VAR(u8 *, gFarTrack) + 0xFA8);
            from = *(s16 **)(FAR_VAR(u8 *, gFarTrack) + 0xFBC);
        }
        dx = from[0] + (to[0] - from[0]) * FAR_VAR(s32, gFarBlend2EAC) / 120;
        dy = from[1] + (to[1] - from[1]) * FAR_VAR(s32, gFarBlend2EAC) / 120;
        dz = from[2] + (to[2] - from[2]) * FAR_VAR(s32, gFarBlend2EAC) / 120;
        /* Array-member reads retain dependencies on the camera stores. */
        cam->pos.x = (dx + gFarOffsetX.unk[0]) * 4;
        cam->pos.y = (dy + gFarOffsetY.unk[0]) * 4;
        cam->pos.z = (dz + gFarOffsetZ.unk[0]) * 4 + 0x640;
        dx = (car->pos.x - cam->pos.x) / 4;
        dy = (car->pos.y - cam->pos.y) / 4;
        dz = (car->pos.z - cam->pos.z) / 4;
        dist = MathSqrt(dx * dx + dy * dy + dz * dz);
        if (dist > 0x4E20) {
            if (dist > 0x7F58) {
                dist = 0x7F58;
            }
            recip = MathFixedDivide(0x4E20, dist);
            cam->pos.x =
                (car->pos.x - MathMultiplyFixed16(dx << 16, recip)) >> 14;
            cam->pos.y =
                (car->pos.y - MathMultiplyFixed16(dy << 16, recip)) >> 14;
            cam->pos.z =
                (car->pos.z - MathMultiplyFixed16(dz << 16, recip)) >> 14;
        }
        cam->pos.x = car->pos.x - dx;
        cam->pos.y = car->pos.y - dy;
        cam->pos.z = car->pos.z - dz;
        func_8002DA30((s32 *)cam);
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        break;
    case 17:
        cam->basis[0] = car->basis[0];
        cam->rot[0] = cam->basis[0];
        cam->basis[1] = car->basis[1];
        cam->rot[1] = cam->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[2] = cam->basis[2];
        track = FAR_VAR(TrackRacer *, gFarTrack);
        point = track->point;
        pos[0] = track->unk14;
        pos[1] = track->unk18;
        pos[2] = *(s16 *)(*(u8 **)(track->unk20 + 0x18) + 4);
        pos[2] = (pos[2] + FAR_VAR(s32, gFarOffsetZ)) * 4;
        dx = pos[0] - D_800B1348nm[point].x;
        dy = pos[1] - D_800B1348nm[point].y;
        delta = pos[2] - 1000;
        dz = delta - D_800B1348nm[point].z;
        dist = MathSqrt(dx * dx + dy * dy + dz * dz);
        aimRow0 = &cam->rot[0];
        aimRow1 = &cam->rot[1];
        aimRow2 = &cam->rot[2];
        if (dist > 0x32C8) {
            dist = 0x32C8;
        }
        recip = MathFixedDivide(speed, dist);
        D_800A2DE8Small += 20;
        cam->pos.x = pos[0] - (MathMultiplyFixed16(dx << 16, recip) >> 16);
        cam->pos.y = pos[1] - (MathMultiplyFixed16(dy << 16, recip) >> 16);
        cam->pos.z = pos[2] - (MathMultiplyFixed16(dz << 16, recip) >> 16);
        {
            s32 stepX;
            s32 stepY;
            s32 stepZ;

            stepX = MathMultiplyFixed16(dx << 16, recip) >> 16;
            stepY = MathMultiplyFixed16(dy << 16, recip) >> 16;
            stepZ = MathMultiplyFixed16(dz << 16, recip) >> 16;
            MathSqrt(stepX * stepX + stepY * stepY + stepZ * stepZ);
        }
        func_8002DA30((s32 *)cam);
        dx = car->pos.x;
        dy = car->pos.y;
        dz = car->pos.z;
        car->pos.x = pos[0];
        car->pos.y = pos[1];
        car->pos.z = pos[2];
        CAMERA_LOOK_AT(cam, car, aimRow0, aimRow1, aimRow2);
        car->pos.x = dx;
        car->pos.y = dy;
        car->pos.z = dz;
        *(s16 *)(FAR_VAR(u8 *, gFarPlayer) + 0x1E0) = 0;
        break;
    }
}

extern s32 D_800A37E0Record asm("D_800A37E0.NON_MATCHING");
extern u8 *D_800A3878Record[] asm("D_800A3878.NON_MATCHING");
extern u8 *D_800A3960Record[] asm("D_800A3960.NON_MATCHING");
extern u8 *D_800A3554Record[] asm("D_800A3554.NON_MATCHING");

void func_8002267C(void) {
    u8 *node;
    s32 base;
    u8 *curCar;
    u8 *car;
    u8 *rec;
    u32 bits;

    node = D_800A3878Record[0];
    if (D_800A397CSmall != 1) {
        return;
    }
    if (node != 0) {
        base = (s32)D_800A3A38Small;
        curCar = D_800A3960Record[0];
        car = D_800A3554Record[0];
        do {
            if (*(s16 *)(node + 0x1EC) >= 0) {
                rec = (u8 *)(D_800A37E8Small * 20 + base);
                *(s32 *)rec = *(s32 *)(node + 0);
                *(s32 *)(rec + 4) = *(s32 *)(node + 4);
                *(u16 *)(rec + 0xC) = *(u16 *)(node + 0x3A4);
                *(u16 *)(rec + 0xE) = ((*(s32 *)(node + 0x90) / 2 >> 16) << 7) |
                                      *(u8 *)(node + 0x410);
                bits = (*(s16 *)(node + 0x114) << 22) |
                       ((*(s16 *)(node + 0x20E) + 0x80) << 14) |
                       ((*(u8 *)(node + 0x3AE) & 3) << 12) |
                       ((*(u8 *)(node + 0x3AF) & 3) << 10) |
                       ((*(u8 *)(node + 0x3B0) & 3) << 8) |
                       ((*(u8 *)(node + 0x3B1) & 3) << 6) |
                       (*(s16 *)(node + 0x10C) << 4) |
                       (*(s8 *)(node + 0x3B9) << 3) |
                       (*(u8 *)(node + 0xF9) << 2);
                if (curCar == car) {
                    bits |= 1;
                } else if (D_800A2EA4nm[0] != 0 &&
                           curCar == *(u8 **)(car + 0x3E0)) {
                    bits |= 0x10;
                }
                *(s32 *)((u8 *)(D_800A37E8Small * 20 + base) + 8) = bits;
                *(s32 *)((u8 *)(D_800A37E8Small * 20 + base) + 0x10) =
                    (((*(u16 *)(node + 0xFE) << 16) >> 17) + 0x800 << 20) |
                    (*(s16 *)(node + 0x388) << 10) | *(s16 *)(node + 0x38A);
                if (*(s16 *)(node + 0x1EC) == 1) {
                    if (*(s16 *)(node + 0x1E0) != -1) {
                        *(s32 *)(node + 0xC) = *(s32 *)(node + 0);
                        *(s32 *)(node + 0x10) = *(s32 *)(node + 4);
                        *(s32 *)(node + 0x14) = *(s32 *)(node + 8);
                    }
                } else if (*(s16 *)(node + 0x1E0) != -1 &&
                           *(u16 *)(node + 0x362) != 0 &&
                           *(u16 *)(node + 0x364) != 0 &&
                           *(u16 *)(node + 0x366) != 0 &&
                           *(u16 *)(node + 0x368) != 0) {
                    *(s32 *)(node + 0xC) = *(s32 *)(node + 0);
                    *(s32 *)(node + 0x10) = *(s32 *)(node + 4);
                    *(s32 *)(node + 0x14) = *(s32 *)(node + 8);
                }
                D_800A37E8Small = D_800A37E8Small + 1;
                D_800A37E0Record = D_800A37E8Small;
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != 0);
    }
    func_800365B8((u8 *)D_800A3A38Small + D_800A37E8Small * 20);
    func_80044354((u8 *)D_800A3A38Small + (D_800A37E8Small * 20 + 0x50));
    D_800A3550Small = (D_800A3550Small + 1) % D_800A3A90Small;
    D_800A37E8Small = D_800A37E8Small + 6;
    D_800A37E0Record = D_800A37E8Small;
    D_800A37E8Small = D_800A3550Small * (D_800A2E94[0] + 6);
    if (D_800A3804Small == D_800A3550Small) {
        D_800A3804Small = (D_800A3804Small + 1) % D_800A3A90Small;
    }
}

INCLUDE_ASM("asm/nonmatchings/objects", func_800229B8);

extern u8 *D_800A3554[];
extern u8 *D_800A3878w15[] asm("D_800A3878.NON_MATCHING");
extern u8 *D_800A3960w15[] asm("D_800A3960.NON_MATCHING");

void func_80022CA4(void) {
    u8 *node;
    register u8 *rec asm("a1");
    u8 *p;
    s32 current;
    s32 count;
    u8 *baseAddr;
    s32 offset;
    u32 bits;
    u32 w2;
    s32 d;
    s32 dm1;
    register u16 val asm("v1");
    s32 v90;
    s32 t114;
    s32 i;

    current = D_800A3A3CSmall;
    if (current != D_800A3804Small) {
        d = D_800A3A90Small;
        dm1 = d - 1;
        D_800A3A3CSmall = (current + dm1) % d;
    } else {
        D_800A2ED4[0] = 1;
        func_80052FC4(0);
    }
    count = D_800A3A3CSmall * (D_800A2E94[0] + 6);
    node = D_800A3878w15[0];
    if (node != 0) {
        offset = count * 20;
        do {
            if (*(s16 *)(node + 0x1EC) >= 0) {
                rec = (u8 *)D_800A3A38Small;
                rec = (u8 *)(offset + (s32)rec);
                *(s32 *)(node + 0) = *(s32 *)rec;
                *(s32 *)(node + 4) = *(s32 *)(rec + 4);
                func_800442C8(node);
                val = *(u16 *)(u8 *)(offset + D_800A3A38Small + 0xE);
                *(u8 *)(node + 0x410) = val & 0x7F;
                baseAddr = (u8 *)D_800A3A38Small;
                v90 = (val >> 7) << 17;
                *(s32 *)(node + 0x90) = v90;
                bits = *(s32 *)(u8 *)(offset + (s32)baseAddr + 8);
                *(s16 *)(node + 0x116) = (bits >> 22) * 4;
                val = bits >> 22;
                *(s16 *)(node + 0x20E) = ((bits >> 14) & 0xFF) - 0x80;
                *(s16 *)(node + 0x10C) = (bits & 0x3F) >> 4;
                *(u8 *)(node + 0x3B9) = (bits & 0xF) >> 3;
                *(u8 *)(node + 0xF9) = (bits & 7) >> 2;
                *(s16 *)(node + 0x102) = val;
                *(s16 *)(node + 0x114) = val;
                if ((bits & 3) == 1) {
                    D_800A3960w15[0] = D_800A3554[0];
                } else if ((bits & 3) == 2) {
                    D_800A3960w15[0] = *(u8 **)(D_800A3554[0] + 0x3E0);
                } else {
                    D_800A3960w15[0] = 0;
                }
                w2 = *(s32 *)(u8 *)(offset + D_800A3A38Small + 0x10);
                *(s16 *)(node + 0xFE) = ((w2 >> 20) - 0x800) * 2;
                for (i = 0; i < 4; i++) {
                    *(s16 *)(node + 0x2AC + i * 0x28) = *(u16 *)(node + 0xFE);
                }
                t114 = *(s16 *)(node + 0x114);
                *(s16 *)(node + 0x388) = (w2 << 12) >> 22;
                *(s16 *)(node + 0x38A) = w2 & 0x3FF;
                func_8001F2C4(t114, 0, 0);
                func_8001F828((s32 *)node);
                func_8001F874((s32 *)node);
                *(s32 *)(node + 0x228) = 0;
                *(s16 *)(node + 0x104) = *(u16 *)(node + 0x114);
                func_80028980(node);
                offset += 0x14;
                count += 1;
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != 0);
    }
    func_8003667C((u8 *)D_800A3A38Small + count * 20);
    func_80044594((u8 *)D_800A3A38Small + (count * 20 + 0x50));
}

void func_800229B8(void);

void func_80022F48(void) {
    func_800229B8();
    func_800229B8();
    func_800229B8();
    func_800229B8();
}

void func_80022F80(void) {
    func_80022CA4();
    func_80022CA4();
    func_80022CA4();
    func_80022CA4();
}

void func_80022FB8(u8 *arg0, s32 arg1) {
    s32 value;
    s16 shortValue;
    s32 value0;
    s32 value1;
    s32 value2;

    value = 0x400 - arg1;
    if (value == 0x400) {
        value = 0;
    }
    func_8001F2C4(value, 0, 0);
    func_8001F874((s32 *)arg0);
    func_8001F828((s32 *)arg0);
    shortValue = value;
    *(s16 *)(arg0 + 0x102) = shortValue;
    *(s16 *)(arg0 + 0x104) = shortValue;
    *(s16 *)(arg0 + 0x114) = shortValue;
    *(s16 *)(arg0 + 0x116) = value * 4;
    do {
    } while (0);
    value0 = *(s32 *)(arg0 + 0x18);
    value1 = *(s32 *)(arg0 + 0x1C);
    value2 = *(s32 *)(arg0 + 0x20);
    *(s32 *)(arg0 + 0x3C) = value0;
    *(s32 *)(arg0 + 0x40) = value1;
    *(s32 *)(arg0 + 0x44) = value2;
    do {
    } while (0);
    value0 = *(s32 *)(arg0 + 0x24);
    value1 = *(s32 *)(arg0 + 0x28);
    value2 = *(s32 *)(arg0 + 0x2C);
    *(s32 *)(arg0 + 0x48) = value0;
    *(s32 *)(arg0 + 0x4C) = value1;
    *(s32 *)(arg0 + 0x50) = value2;
    do {
    } while (0);
    value0 = *(s32 *)(arg0 + 0x30);
    value1 = *(s32 *)(arg0 + 0x34);
    value2 = *(s32 *)(arg0 + 0x38);
    *(s32 *)(arg0 + 0x54) = value0;
    *(s32 *)(arg0 + 0x58) = value1;
    *(s32 *)(arg0 + 0x5C) = value2;
}

extern u8 *D_800A3554Lui asm("D_800A3554Absolute");
extern s32 D_800A2EA4Lui asm("D_800A2EA4Absolute");
extern s32 D_800A2EC8Lui asm("D_800A2EC8Absolute");
extern FarVar gFarFlag3A60 asm("D_800A3A60");
extern FarVar gFarWord357C asm("D_800A357C");
extern FarVar gFarWord357E asm("D_800A357E");
extern FarVar gFarFlag306D asm("D_800A306D");
extern FarVar gFarFlag2F9D asm("D_800A2F9D");
extern s32 D_800A2ECC[];
extern s32 D_800A2ED0[];
extern s8 D_800A3620;
extern s32 D_800A2DF8;
extern u8 D_800A39F0;
extern void func_8004B128(u8 *);
extern void func_8003F564(s8, s8);
extern void func_800229B8(void);
extern void func_80044248(void);
extern s32 func_8002482C(s32, s32, s32 *);
extern u32 PadGetType(s32);
extern void func_80052FC4(s8);
extern void func_8005301C(void);
extern void func_80041444(s32);
extern void SsSetMute(u8);

/* The plain D_800A2F58 and D_800A36A4 names carry a small .extern elsewhere
 * in this file, which pulls every access through $gp. Separate lui views. */
asm(".globl D_800A2F58Absolute2\nD_800A2F58Absolute2 = D_800A2F58\n"
    ".globl D_800A36A4Absolute2\nD_800A36A4Absolute2 = D_800A36A4\n"
    ".globl D_800A3554Absolute2\nD_800A3554Absolute2 = D_800A3554\n");
extern u8 D_800A2F58Absolute2;
extern s32 D_800A36A4Absolute2;
extern u8 *D_800A3554Absolute2;

void func_80023074(void) {
    s32 mode;
    s32 offset;

    if (D_800A2F58Absolute2 != 0 && D_800A36A4Absolute2 >= 0x51) {
        return;
    }
    mode = 1;
    D_800A2ED4[0] = mode;
    func_8004B128(D_800A3554Lui);
    if (D_800A2EA4Lui != 0) {
        func_8004B128(*(u8 **)(D_800A3554Lui + 0x3E0));
    }
    if (D_800A2EC8Lui != 0) {
        mode = D_800A397CSmall;
        if (mode == 2) {
            func_8003F564(0xA, 0xB);
            offset = D_800A3A90Small - 2;
            D_800A3A3CSmall = (D_800A3550Small + offset) % D_800A3A90Small;
            func_800229B8();
            func_80044248();
            {
                u8 *car = D_800A3554Lui;
                u8 copy;

                copy = 0;
                if (*(u8 *)(car + 0x268) == 0) {
                    copy = *(u8 *)(car + 0x20D);
                }
                *(u8 *)(car + 0x20C) = copy;
            }
            *(s16 *)(D_800A3554Lui + 0x1E0) = func_8002482C(
                *(s32 *)D_800A3554Lui, *(s32 *)(D_800A3554Lui + 4),
                (s32 *)(D_800A3554Lui + 0x1F8));
            func_8004B128(D_800A3554Lui);
            {
                u8 *car = D_800A3554Lui;
                s32 split;

                split = D_800A2EA4Lui;
                *(s32 *)(car + 0x380) = *(s16 *)(car + 0x114);
                if (split == mode) {
                    u8 *other = *(u8 **)(car + 0x3E0);
                    u8 copy;

                    copy = 0;
                    if (*(u8 *)(other + 0x268) == 0) {
                        copy = *(u8 *)(other + 0x20D);
                    }
                    *(u8 *)(other + 0x20C) = copy;
                    *(s16 *)(*(u8 **)(D_800A3554Lui + 0x3E0) + 0x1E0) =
                        func_8002482C(
                            *(s32 *)*(u8 **)(D_800A3554Lui + 0x3E0),
                            *(s32 *)(*(u8 **)(D_800A3554Lui + 0x3E0) + 4),
                            (s32 *)(*(u8 **)(D_800A3554Lui + 0x3E0) + 0x1F8));
                    func_8004B128(*(u8 **)(D_800A3554Lui + 0x3E0));
                    *(s32 *)(*(u8 **)(D_800A3554Lui + 0x3E0) + 0x380) =
                        *(s16 *)(*(u8 **)(D_800A3554Lui + 0x3E0) + 0x114);
                }
            }
            if (FAR_VAR(u8, gFarFlag3A60) != 0) {
                u8 *car = D_800A3554Absolute2;
                u16 word;
                s32 split2;

                word = FAR_VAR(u16, gFarWord357C);
                split2 = D_800A2EA4Lui;
                *(u16 *)(car + 0x1E0) = word;
                if (split2 != 0) {
                    *(u16 *)(*(u8 **)(car + 0x3E0) + 0x1E0) =
                        FAR_VAR(u16, gFarWord357E);
                }
                SceneInitRoadStrip();
            }
            if (PadGetType(D_800A3620) == 2) {
                D_800A2DF8 = PadGetButtons(D_800A3620);
            }
            D_800A397CSmall = 1;
            func_80052FC4(0);
        } else {
            func_8005301C();
        }
        D_800A2ED0[0] = 0;
        D_800A3680[0] = 1;
        return;
    }
    D_800A2EC8[0] = mode;
    D_800A2ECC[0] = 0;
    D_800A2ED0[0] = 0;
    {
        u8 *car = D_800A3554Lui;

        if (*(u8 *)(car + 0x268) == 0) {
            *(u8 *)(car + 0x20D) = *(u8 *)(car + 0x20C);
        }
    }
    if (D_800A2EA4Lui == 2) {
        u8 *other = *(u8 **)(D_800A3554Lui + 0x3E0);

        if (*(u8 *)(other + 0x268) == 0) {
            *(u8 *)(other + 0x20D) = *(u8 *)(other + 0x20C);
        }
    }
    offset = D_800A3A90Small - 1;
    D_800A3A3CSmall = (D_800A3550Small + offset) % D_800A3A90Small;
    func_80041444(0);
    func_80052FC4(0);
    if (FAR_VAR(u8, gFarFlag306D) == 0) {
        func_8003CCE0(0);
    }
    if (FAR_VAR(u8, gFarFlag2F9D) == 0) {
        SsSetMute(0);
    }
    D_800A2DF8 = PadGetButtons(D_800A3620);
    D_800A39F0 = 0;
}

extern void func_8003CCE0(s32);
extern void CdApplyMixVolume(void);
extern void func_8002F86C(void *, s32);
extern void func_80044FF8(s32, s32);
extern s8 D_800A2D0CControl asm("D_800A2D0CAbsolute");
extern s32 D_800A2DF8Control asm("D_800A2DF8");
extern s32 D_800A2EA4Control asm("D_800A2EA4Absolute");
extern s32 D_800A2EACControl asm("D_800A2EACAbsolute");
extern s32 D_800A2EB0Control asm("D_800A2EB0Absolute");
extern s32 D_800A2EB4Control asm("D_800A2EB4Absolute");
extern s32 D_800A2EC4Control asm("D_800A2EC4Absolute");
extern s32 D_800A2EC8Control asm("D_800A2EC8Absolute");
extern s32 D_800A2ECCControl asm("D_800A2ECCAbsolute");
extern s32 D_800A2ED0Control asm("D_800A2ED0Absolute");
extern s32 D_800A2ED4Control asm("D_800A2ED4Absolute");
extern u8 D_800A2F95Control asm("D_800A2F95Absolute");
extern u8 D_800A2F9CControl asm("D_800A2F9CAbsolute");
extern u8 D_800A2F9DControl asm("D_800A2F9DAbsolute");
extern s8 D_800A2FC8Control asm("D_800A2FC8Absolute");
extern u8 D_800A306CControl asm("D_800A306CAbsolute");
extern u8 D_800A306DControl asm("D_800A306DAbsolute");
extern u8 *D_800A3554Control asm("D_800A3554Absolute");
extern s8 D_800A3590Control asm("D_800A3590Absolute");
extern s8 D_800A3620Control asm("D_800A3620");
extern s16 D_800A3694Control asm("D_800A3694Absolute");
extern s16 D_800A3696Control asm("D_800A3696Absolute");
extern u8 D_800A36FCControl asm("D_800A36FCAbsolute");
extern u8 D_800A3700Control asm("D_800A3700Absolute");
extern u8 *D_800A3878Control asm("D_800A3878Absolute");
extern s32 D_800A397CControl asm("D_800A397C.NON_MATCHING");
extern s8 D_800A39F0Control asm("D_800A39F0");
extern s8 D_800A3A94Control asm("D_800A3A94Absolute");

extern s8 D_800A2F94Control asm("D_800A2F94Absolute");
extern u8 D_800A3614Control asm("D_800A3614Absolute");
extern u8 D_800A3924Control asm("D_800A3924Absolute");
extern u8 D_800A380CControl asm("D_800A380CAbsolute");
extern u8 D_800A35A8Control asm("D_800A35A8Absolute");
extern s16 D_800A3696ControlPointer[] asm("D_800A3696Absolute2");
extern s16 D_800A3694ControlPointer[] asm("D_800A3694Absolute2");

void func_80023454(void) {
    u8 frameGap[0x20];
    s16 enabledVolume;
    register s32 selectionDividend asm("$4");
    s32 fadeFlag;
    s16 *volume;
    register s32 volumeValue asm("$3");
    s32 volumeResult;
    s32 activeState;
    s32 buttons;
    register s32 value asm("$2");
    s32 buttonBits;
    register s32 keyMask asm("$2");
    s32 newButtonMask;
    s32 waitCount;
    s32 otherWaitCount;
    s32 flagBits;
    s32 heldDirections;
    s32 debugFlags;
    s8 menuState;
    s8 objectIndex;
    s8 nextObjectIndex;
    s32 selection;
    register s32 previousStateOne asm("$4");
    s32 nextStateOne;
    register s32 toneChannel asm("$4");
    s32 playerCount;
    s32 parentSelection;
    register s32 selectionIndex asm("$3");
    s32 navigationState;
    u8 monoMode;
    u8 *otherObject;
    u8 *object;

    /* Keep retail's frame gap and the switch table's 8-byte alignment. */
    asm(".section .rodata\n\t.align 3\n\t.text" : : "m"(frameGap[0]));
    if (D_800A397CControl != 2) {
        buttons = PadGetButtons(D_800A3620Control);
        if (!(D_800A2ED0Control & 0xC)) {
            buttonBits = ~D_800A2DF8Control;
            asm volatile(""
                         : "=r"(keyMask)
                         : "0"(buttonBits & 0x1000), "r"(buttons));
            keyMask = buttons & keyMask;
            toneChannel = 10;
            if (keyMask) {
                func_8003F564(toneChannel, 9);
                if (D_800A39F0Control == 1 && D_800A2ECCControl == 3 &&
                    D_800A306DControl == 0 && D_800A2F9CControl != 0) {
                    func_8003CCE0(0);
                }
                selectionDividend = D_800A2ECCControl + 5;
                selectionIndex = selectionDividend / 6;
                asm("" : "=r"(selectionIndex) : "0"(selectionIndex));
                selectionIndex = selectionDividend - selectionIndex * 6;
                navigationState = D_800A39F0Control;
                previousStateOne = 1;
                D_800A2ECCControl = selectionIndex;
                if (navigationState == previousStateOne)
                    goto previousSoundState;
                if (navigationState >= 2)
                    goto navigationStateRange;
                if (navigationState != 0)
                    goto done;
                playerCount = D_800A2EB0Control;
                if (playerCount == 2 && selectionIndex == playerCount) {
                    D_800A2ECCControl = previousStateOne;
                }
                if (D_800A2EA4Control != 0 && D_800A2ECCControl == 3) {
                    selection = 2;
                    goto setSelection;
                }
                goto done;
            previousSoundState:
                if (selectionIndex == navigationState &&
                    D_800A2F9DControl != 0) {
                handleSlider:
                    func_80044FF8(0, 10);
                    goto done;
                }
                if (D_800A2ECCControl == 3 && D_800A306DControl == 0) {
                startMusic:
                    func_8003CCE0(1);
                }
                goto done;
            } else {
                asm volatile(""
                             : "=r"(keyMask)
                             : "0"(buttonBits & 0x4000), "r"(buttons));
                keyMask = buttons & keyMask;
                if (!keyMask)
                    goto block_49;
                func_8003F564(toneChannel, 9);
                if (D_800A39F0Control == 1 && D_800A2ECCControl == 3 &&
                    D_800A306DControl == 0 && D_800A2F9CControl != 0) {
                    func_8003CCE0(0);
                }
                selectionDividend = D_800A2ECCControl + 1;
                selectionIndex = selectionDividend / 6;
                asm("" : "=r"(selectionIndex) : "0"(selectionIndex));
                selectionIndex = selectionDividend - selectionIndex * 6;
                navigationState = D_800A39F0Control;
                nextStateOne = 1;
                D_800A2ECCControl = selectionIndex;
                if (navigationState == nextStateOne)
                    goto nextSoundState;
                if (navigationState < 2) {
                    if (navigationState == 0)
                        goto nextGameState;
                    goto done;
                }
            navigationStateRange:
                if (navigationState == 2)
                    goto paritySelection;
                goto done;
            nextGameState:
                playerCount = D_800A2EB0Control;
                if (playerCount == 2 && selectionIndex == playerCount) {
                    D_800A2ECCControl = 3;
                }
                if (D_800A2EA4Control != 0 && D_800A2ECCControl == 3) {
                    selection = 4;
                    goto setSelection;
                }
                goto done;
            nextSoundState:
                if (selectionIndex == navigationState && D_800A2F9DControl != 0)
                    goto handleSlider;
                asm("" : : : "memory");
                if (D_800A2ECCControl == 3 && D_800A306DControl == 0 &&
                    D_800A2F9CControl != 0)
                    goto startMusic;
                goto done;
            paritySelection:
                selection = 4 - (selectionIndex & 1);
            setSelection:
                D_800A2ECCControl = selection;
                goto done;
            }
        } else {
        block_49:
            buttonBits = D_800A2DF8Control;
            asm("" : "=r"(keyMask) : "0"(~buttonBits & 0x840));
            if (buttons & keyMask) {
                if (buttons & 0x800) {
                    asm("" : "=r"(keyMask) : "0"(buttonBits & 0x100));
                    if (!(buttons & keyMask)) {
                        if ((D_800A39F0Control == 1) &&
                            (D_800A2ECCControl == D_800A39F0Control)) {
                            func_80044FF8(2, 0xA);
                        }
                        D_800A39F0Control = 0;
                        D_800A2ECCControl = 0;
                        goto block_56;
                    }
                } else {
                block_56:
                    menuState = D_800A39F0Control;
                    switch (menuState) {
                    case 0:
                        switch (D_800A2ECCControl) {
                        case 0:
                            D_800A2EC8Control = 0;
                            D_800A2ED4Control = 0;
                            if (D_800A2F9DControl == 0) {
                                SsSetMute(1);
                            }
                            func_80041328();
                            if (D_800A306DControl == 0) {
                                func_8003CCE0(D_800A2F9CControl);
                            }
                            if (*(u8 *)(D_800A3554Control + 0x268) == 0) {
                                *(s8 *)(D_800A3554Control + 0x20C) =
                                    (u8) * (u8 *)(D_800A3554Control + 0x20D);
                            }
                            if (D_800A2EA4Control == 2) {
                                otherObject =
                                    *(u8 **)(D_800A3554Control + 0x3E0);
                                if (*(u8 *)(otherObject + 0x268) == 0) {
                                    *(s8 *)(otherObject + 0x20C) =
                                        (u8) * (u8 *)(otherObject + 0x20D);
                                }
                            }
                            break;
                        case 1:
                            func_8003F564(0xA, 0xB);
                            func_800441C8();
                            object = D_800A3878Control;
                            D_800A397CControl = 2;
                            objectIndex = 0;
                            if (D_800A2EB4Control > 0) {
                                activeState = 1;
                            objectLoop:
                                value = *(s8 *)(object + 0x20C);
                                if (value >= 3) {
                                    value = *(s16 *)(object + 0x114);
                                    *(s8 *)(object + 0x20C) = activeState;
                                    *(s32 *)(object + 0x380) = value;
                                }
                                nextObjectIndex = objectIndex + 1;
                                objectIndex = nextObjectIndex;
                                object = *(u8 **)(object + 0x3E0);
                                if (nextObjectIndex < D_800A2EB4Control)
                                    goto objectLoop;
                            }
                            break;
                        case 2:
                            func_8003F564(10, 11);
                            value = D_800A2ED0Control;
                            debugFlags = value & ~128;
                            value &= 8;
                            D_800A2ED0Control = debugFlags;
                            if (value != 0) {
                                flagBits = -9;
                                goto clearFlags;
                            }
                            flagBits = debugFlags | 8;
                            D_800A2ED0Control = flagBits;
                            break;
                        case 3:
                            func_8003F564(10, 11);
                            debugFlags = D_800A2ED0Control;
                            if (debugFlags & 4) {
                                flagBits = -5;
                            clearFlags:
                                D_800A2ED0Control = debugFlags & flagBits;
                            } else {
                                flagBits = debugFlags | 4;
                                D_800A2ED0Control = flagBits;
                                D_800A3700Control = 0;
                                D_800A36FCControl = 0;
                            }
                            break;
                        case 4:
                            func_8003F564(0xA, 0xB);
                            D_800A39F0Control = 1;
                            D_800A2ECCControl = 0;
                            break;
                        case 5:
                            func_8003F564(0xA, 0xB);
                            D_800A39F0Control = 2;
                            D_800A2ECCControl = 3;
                            break;
                        }
                        break;
                    case 1:
                        if (D_800A2ECCControl == 5) {
                            func_8003F564(0xA, 0xB);
                            parentSelection = 4;
                            goto closeSubmenu;
                        }
                        break;
                    case 2:
                        func_8003F564(0xA, 0xB);
                        if (D_800A2ECCControl == 3) {
                            parentSelection = 5;
                        closeSubmenu:
                            D_800A39F0Control = 0;
                            D_800A2ECCControl = parentSelection;
                            break;
                        }
                        if (D_800A2EB0Control == menuState) {
                            D_800A2D0CControl = 1;
                            waitCount = 1;
                            do {
                                VSync(0);
                            } while (waitCount++ < 0x1E);
                        } else {
                            otherWaitCount = 1;
                            do {
                                VSync(0);
                            } while (otherWaitCount++ < 0x1E);
                            if (*(u8 *)(D_800A3554Control + 0x268) != 0) {
                                *(u8 *)(D_800A3554Control + 0x268) = 0U;
                                *(u8 *)(D_800A3554Control + 0xF4) = 0;
                                *(s32 *)(D_800A3554Control + 0x90) = 0;
                            }
                            D_800A2EC8Control = 0;
                            D_800A2ED4Control = 0;
                            func_80041444(1);
                            if (D_800A306DControl == 0) {
                                func_8003CCE0(D_800A2F9CControl);
                            }
                            D_800A3A94Control = 0;
                            if (D_800A2EACControl == 0) {
                                func_8002F86C(D_800A3554Control, 2);
                            } else {
                                D_800A2EACControl = 2;
                            }
                            D_800A2EC4Control = 0;
                        }
                        break;
                    }
                    goto block_104;
                }
            } else {
            block_104:
                if (D_800A39F0Control == 1) {
                    if ((D_800A2ECCControl == D_800A39F0Control) &&
                        (D_800A2F9DControl != 0)) {
                        func_80044FF8(1, 0xA);
                    }
                    asm("" : "=r"(keyMask) : "0"(~D_800A2DF8Control & 0xA000));
                    if (buttons & keyMask) {
                        switch (D_800A2ECCControl) {
                        case 0:
                            func_8003F564(10, 10);
                            func_8004142C();
                            enabledVolume = -(D_800A2F9DControl != 0) & 50;
                            D_800A3696Control = enabledVolume;
                            D_800A2F94Control = enabledVolume * 127 / 100;
                            break;
                        case 2:
                            func_8003F564(10, 10);
                            func_80041414();
                            if (D_800A2F9CControl == 0) {
                                D_800A3694Control = 0;
                            } else {
                                D_800A3694Control = 50;
                            }
                            CdApplyMixVolume();
                            break;
                        case 4:
                            func_8003F564(10, 10);
                            D_800A2F95Control = D_800A2F95Control == 0;
                            monoMode = D_800A306CControl == 0;
                            D_800A306CControl = monoMode;
                            if (monoMode & 0xFF) {
                                SsSetMono();
                            } else {
                                SsSetStereo();
                            }
                            break;
                        }
                    }
                    heldDirections = buttons & 0xA000;
                    if (heldDirections != 0) {
                        switch (D_800A2ECCControl) {
                        case 1:
                            if (D_800A2F9DControl != 0) {
                                volume = D_800A3696ControlPointer;
                                if (buttons & 0x8000) {
                                    volumeResult = D_800A3696Control;
                                    volumeValue = volumeResult;
                                    if (volumeResult > 0) {
                                        volumeResult = volumeValue - 1;
                                        D_800A3696Control = volumeResult;
                                        *volume = volumeResult;
                                    } else {
                                        volumeResult = 0;
                                        goto setMusicVolume;
                                    }
                                } else {
                                    volumeResult = D_800A3696Control;
                                    volumeValue = volumeResult;
                                    volumeResult = volumeResult < 100;
                                    if (volumeResult != 0) {
                                        volumeResult = volumeValue + 1;
                                        D_800A3696Control = volumeResult;
                                        *volume = volumeResult;
                                    } else {
                                        volumeResult = 100;
                                    setMusicVolume:
                                        *volume = volumeResult;
                                    }
                                }
                                D_800A2F94Control =
                                    D_800A3696Control * 127 / 100;
                                SoundSetSlotVolume(10, 127, 127);
                            }
                            break;
                        case 3:
                            if (D_800A2F9CControl != 0) {
                                volume = D_800A3694ControlPointer;
                                if (buttons & 0x8000) {
                                    volumeResult = D_800A3694Control;
                                    volumeValue = volumeResult;
                                    if (volumeResult > 0) {
                                        volumeResult = volumeValue - 1;
                                        D_800A3694Control = volumeResult;
                                    } else {
                                        volumeResult = 0;
                                    }
                                } else {
                                    volumeResult = D_800A3694Control;
                                    volumeValue = volumeResult;
                                    volumeResult = volumeResult < 100;
                                    if (volumeResult != 0) {
                                        volumeResult = volumeValue + 1;
                                        D_800A3694Control = volumeResult;
                                    } else {
                                        volumeResult = 100;
                                    }
                                }
                                *volume = volumeResult;
                                CdApplyMixVolume();
                                func_8003F564(10, 10);
                            }
                            break;
                        }
                    }
                }
                if (D_800A2ED0Control & 4) {
                    asm("" : "=r"(keyMask) : "0"(~D_800A2DF8Control & 0x10));
                    if (keyMask & buttons) {
                        fadeFlag = D_800A36FCControl;
                        D_800A3924Control = D_800A3614Control;
                        D_800A3614Control = ((s8)D_800A3614Control + 1) % 3;
                        if (fadeFlag == 0)
                            fadeFlag = 128;
                        D_800A3700Control = fadeFlag;
                    }
                    asm("" : "=r"(keyMask) : "0"(~D_800A2DF8Control & 0x80));
                    if (keyMask & buttons) {
                        D_800A36FCControl = 128;
                        D_800A35A8Control = D_800A380CControl;
                        D_800A380CControl = ((s8)D_800A380CControl + 2) % 3;
                        if (D_800A3700Control == 0)
                            D_800A3700Control = 128;
                    }
                    asm("" : "=r"(keyMask) : "0"(~D_800A2DF8Control & 0x20));
                    if (keyMask & buttons) {
                        D_800A36FCControl = 128;
                        D_800A35A8Control = D_800A380CControl;
                        D_800A380CControl = ((s8)D_800A380CControl + 1) % 3;
                        if (D_800A3700Control == 0)
                            D_800A3700Control = 128;
                    }
                }
                if (D_800A2ED0Control & 8) {
                    if (D_800A2EA4Control == 0) {
                        if (buttons & 0x1000) {
                            if (D_800A3590Control != 0)
                                D_800A3590Control -= 2;
                        }
                        if ((buttons & 0x4000) && D_800A3590Control < 120) {
                            D_800A3590Control += 2;
                        }
                    }
                    newButtonMask = ~D_800A2DF8Control;
                    asm("" : "=r"(keyMask) : "0"(newButtonMask & 4));
                    if (!(buttons & keyMask))
                        goto done;
                    asm("" : "=r"(keyMask) : "0"(newButtonMask & 1));
                    if (!(buttons & keyMask))
                        goto done;
                    asm("" : "=r"(keyMask) : "0"(newButtonMask & 8));
                    if (!(buttons & keyMask))
                        goto done;
                    asm("" : "=r"(keyMask) : "0"(newButtonMask & 2));
                    if (buttons & keyMask) {
                        D_800A2FC8Control = 1;
                        func_8003F564(0xA, 0xB);
                    }
                }
            }
        }
    done:
        D_800A2DF8Control = buttons;
    }
}

void CdApplyMixVolume(void) {
    CdlATV vol;

    if (D_800A3038[0x35] == 0) {
        vol.val0 = vol.val1 = vol.val2 = vol.val3 =
            ((s16 *)D_800A3668Absolute)[22] * 125 / 100;
        CdMix(&vol);
    }
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80024280);

INCLUDE_ASM("asm/nonmatchings/objects", func_800246C0);

extern s32 D_800A2E08;
extern s32 D_800A3838;
s32 func_800246C0(s32, s32, u8 *);

s32 func_8002482C(s32 arg0, s32 arg1, s32 *arg2) {
    s32 index;
    s32 remaining;
    u8 *entry;
    s32 count;

    count = D_800A2E08;
    arg0 = arg0 / 4;
    arg1 = arg1 / 4;
    index = *arg2;
    if (index == -1) {
        index = 0;
    }
    remaining = count;
    entry = (u8 *)D_800A3838 + (index * 0x10);
    if (remaining > 0) {
        do {
            if (index >= count) {
                index = 0;
                entry = (u8 *)D_800A3838;
            }
            if (arg0 >= *(u16 *)(entry + 0) && *(u16 *)(entry + 4) >= arg0 &&
                arg1 >= *(u16 *)(entry + 2) && *(u16 *)(entry + 6) >= arg1 &&
                (func_800246C0(arg0, arg1, entry) & 0xFF) != 0) {
                *arg2 = index;
                if (index == count) {
                    index = 0;
                }
                return index;
            }
            remaining -= 1;
            index += 1;
            entry += 0x10;
        } while (remaining > 0);
    }
    *arg2 = -1;
    return -1;
}

s32 func_800246C0(s32, s32, u8 *);

s32 func_80024980(s32 arg0, s32 arg1, s32 *arg2) {
    s32 index;
    s32 remaining;
    u8 *entry;
    s32 count;
    s32 countLessOne;

    count = D_800A2E08;
    arg0 = arg0 / 4;
    arg1 = arg1 / 4;
    index = *arg2;
    if (index == -1) {
        index = 0;
    } else {
        countLessOne = count - 1;
        index = (index + countLessOne) % count;
    }
    remaining = count;
    entry = (u8 *)D_800A3838 + (index * 0x10);
    if (remaining > 0) {
        do {
            if (index >= count) {
                index = 0;
                entry = (u8 *)D_800A3838;
            }
            if (arg0 >= *(u16 *)(entry + 0) && *(u16 *)(entry + 4) >= arg0 &&
                arg1 >= *(u16 *)(entry + 2) && *(u16 *)(entry + 6) >= arg1 &&
                (func_800246C0(arg0, arg1, entry) & 0xFF) != 0) {
                *arg2 = index;
                if (index == count) {
                    index = 0;
                }
                return index;
            }
            remaining -= 1;
            index += 1;
            entry += 0x10;
        } while (remaining > 0);
    }
    *arg2 = -1;
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80024B08);

INCLUDE_ASM("asm/nonmatchings/objects", func_80024E90);

extern s32 D_800A3A54Small;
extern s32 D_800A2E14[];
extern s32 D_800A3810;
extern s32 D_800A356C;
extern char D_8008CFC0[];
extern s32 FileOpenCall(s32, void *) asm("FileOpen");
extern s32 FileSeekCall(void *, s32, s32) asm("FileSeek");
extern void FileRead(s32, s32, s32, s32);
extern void FileCloseCall(s32) asm("FileClose");

/* Loads a track resource: resolves a handle, maps its memory, then records
   the loaded row bounds into the small-data cursors. */
void func_80025370(s32 arg0) {
    s32 handle;
    s32 total;
    int headerSize;
    s32 cursor;
    s32 row0;
    register s32 row1 asm("$16");
    register s32 row1Shift asm("$3");
    handle = FileOpenCall(arg0, D_800A2E14);
    if (handle == 0) {
        SystemShowFatalError(D_8008CFC0);
    }
    total = FileSeekCall(handle, 0, 2);
    asm volatile("" : : "r"(total));
    FileSeekCall(handle, 0, 0);
    D_800A3A54Small = (RAM_RESOURCE_BOUNDARY - total) | RAM_CACHED_BASE;
    FileRead(D_800A3A54Small, 1, total, handle);
    cursor = *((volatile s32 *)(&D_800A3A54Small));
    D_800A3A54Small = cursor + 4;
    row0 = *((s32 *)cursor);
    D_800A3A54Small = cursor + 8;
    D_800A2E08 = row0;
    headerSize = 8;
    row1 = *((s32 *)(cursor + 4));
    D_800A3838 = cursor + headerSize;
    D_800A3810 = (cursor + headerSize) + (row0 << 4);
    row1Shift = row1 << 3;
    D_800A356C = D_800A3810 + row1Shift;
    FileCloseCall(handle);
}
INCLUDE_RODATA("asm/nonmatchings/objects", D_8008CFC0);
INCLUDE_RODATA("asm/nonmatchings/objects", D_8008CFE0);

void func_80025454(s32 track) {
    s32 count;
    s32 minX;
    s32 minY;
    s32 minZ;
    s32 maxX;
    s32 maxY;
    s32 maxZ;
    s32 x;
    s32 y;
    s32 z;
    s32 i;
    s32 limit;
    s32 *cursor;

    limit = 0;
    minZ = 0;
    maxY = 0;
    minY = 0;
    maxX = 0;
    minX = 0;
    i = 0;
    maxZ = 0;
    count = *(s16 *)((u8 *)track + 0x28);
    cursor = *(s32 **)((u8 *)track + 0x14);
    for (; i < count; i++) {
        x = cursor[2];
        if (x < minX) {
            minX = x;
        }
        y = cursor[3];
        if (y < minY) {
            minY = y;
        }
        z = cursor[4];
        if (z < minZ) {
            minZ = z;
        }
        if (maxX < x) {
            maxX = x;
        }
        if (maxY < y) {
            maxY = y;
        }
        if (maxZ < z) {
            maxZ = z;
        }
        cursor += 5;
    }
    if (limit < -minX) {
        limit = -minX;
    }
    if (limit < maxX) {
        limit = maxX;
    }
    if (limit < -minY) {
        limit = -minY;
    }
    if (limit < maxY) {
        limit = maxY;
    }
    if (limit < -minZ) {
        limit = -minZ;
    }
    if (limit < maxZ) {
        limit = maxZ;
    }
    *(s32 *)((u8 *)track + 0x18) = limit - 5;
    *(s16 *)((u8 *)track + 0x1C) = minX;
    *(s16 *)((u8 *)track + 0x20) = minY;
    *(s16 *)((u8 *)track + 0x24) = minZ;
    *(s16 *)((u8 *)track + 0x1E) = maxX;
    *(s16 *)((u8 *)track + 0x22) = maxY;
    *(s16 *)((u8 *)track + 0x26) = maxZ;
}

void func_80025594(u8 *object) {
    *(s16 *)(object + 0x1BC) = 0;
    *(s16 *)(object + 0x388) = 0;
}

void func_800255A0(u8 *arg0) {
    u16 temp;

    temp = *(u16 *)(arg0 + 0x1BC);
    *(s32 *)(arg0 + 0x238) = *(s32 *)(arg0 + 0x238) & 0xFFFF7DBF;
    *(u16 *)(arg0 + 0x1BC) = temp + 1;
    switch ((s16)temp) {
    case 0:
        *(s16 *)(arg0 + 0x1C0) = 0;
        *(s16 *)(arg0 + 0x1BE) = 0;
        return;
    case 32:
        *(u16 *)(arg0 + 0x1BC) = 0;
        break;
    default:
        *(s16 *)(arg0 + 0x1D0) = 32;
        return;
    }
    *(s32 *)(arg0 + 0x354) = (s32)func_80025594;
}

void func_80025614(u8 *arg0) {
    s32 heading;
    s32 *table1;
    s32 *table2;
    s32 index;

    *(s32 *)(arg0 + 0x238) = *(s32 *)(arg0 + 0x238) & 0xFFFF7DBF;
    *(s16 *)(arg0 + 0x2B0) = ABS(RandomScaledGet(10)) + 20;
    *(s16 *)(arg0 + 0x2D8) = ABS(RandomScaledGet(10)) + 20;
    heading = *(s16 *)(arg0 + 0x114);
    table1 = *(s32 **)D_800A3A2CAbsolute;
    table2 = *(s32 **)D_800A3A34Absolute;
    *(s16 *)(arg0 + 0x1BC) = 0;
    index = (0x480 - heading) & 0x3FF;
    *(s32 *)(arg0 + 0xC4) += table1[index] * 20;
    *(s32 *)(arg0 + 0xC8) += table2[index] * 20;
    *(s32 *)(arg0 + 0x354) = (s32)func_80025594;
}

void func_80025594();

void func_80025720(u8 *obj) {
    *(void (**)())(obj + 0x354) = func_80025594;
}

void func_80025730(u8 *obj) {
    extern u8 D_800A35F8[];
    extern s16 D_800A3910[];
    extern void func_80042920();
    extern void func_8004419C(u8 *);
    s32 y;
    s32 value;
    s32 dist;
    s32 i;
    u8 *current;
    u8 *p;

    *(u32 *)(obj + 0x238) &= 0xFFFF7D3F;
    *(u8 *)(obj + 0x410) = 0;
    switch (*(s16 *)(obj + 0x1BC)) {
    case 0:
        value = 0x96;
        *(s16 *)(obj + 0x1BC) = 2;
        *(s16 *)(obj + 0x1BE) = 0;
        *(s16 *)(obj + 0x388) = 0;
        *(s16 *)(obj + 0x38A) = 0;
        i = 3;
        p = obj + 0x78;
        do {
            *(s16 *)(p + 0x2B0) = value;
            i--;
            p -= 0x28;
        } while (i >= 0);
        func_800422C0(obj);
        D_800A35F8[0] = 2;
        D_800A3960[0] = obj;
        D_800A3910[0] = 0x7FFF;
        if (*(s8 *)(obj + 0x20C) == -1) {
            y = *(s16 *)(obj + 0x114);
            if (RandomScaledGet(2) == 0) {
                dist = y + 0x300;
            } else {
                dist = y + 0x500;
            }
            *(s32 *)(obj + 0x380) = dist & 0x3FF;
            *(s8 *)(obj + 0x20C) = 1;
        }
        return;
    case 1:
    case 2:
        func_80042920(obj);
        return;
    case 4:
        func_80042920(obj);
        if (*(u8 *)(obj + 0x268) != 0 && D_800A2EDC[0] != 0) {
            func_8004419C(obj);
            return;
        }
        if (*(s16 *)(obj + 0x38A) == 0x200) {
            D_800A35F8[0] = 1;
        }
        return;
    case 3:
        current = D_800A3960[0];
        *(s16 *)(obj + 0x1BC) = 0;
        *(s16 *)(obj + 0x1BE) = 0;
        *(s16 *)(obj + 0x388) = 0;
        *(s16 *)(obj + 0x38A) = 0;
        if (current == obj) {
            extern s32 D_800A3914[];
            D_800A3914[19] = 0;
        }
        if (D_800A3910[0] > 0) {
            extern s16 D_800A3914[];
            D_800A3914[-2] = 0;
        }
        break;
    default:
        break;
    }
    *(s32 *)(obj + 0x354) = (s32)func_80025594;
}

typedef struct {
    u8 unk0[0x1EC];
    s16 unk1EC;
    u8 unk1EE[0x12];
    s8 unk200;
    u8 unk201[0x153];
    void (*callback)(void);
} Batch0CallbackObject;
void ObjectSetCallbackIfAllowed(Batch0CallbackObject *object,
                                void (*callback)(void)) {
    if (((object->unk1EC != 1) || (callback != func_80025730)) &&
        (object->callback != func_80025730) && (object->unk200 != 4)) {
        object->callback = callback;
    }
}

s32 func_80025938(u8 *arg0, u8 *arg1) {
    s32 dist[3];
    s32 radius;

    radius = *(s32 *)(*(s32 *)(arg0 + 0x370) + 0x18) +
             *(s32 *)(*(s32 *)(arg1 + 0x370) + 0x18);
    dist[0] = (*(s32 *)(arg0 + 0) - *(s32 *)(arg1 + 0) < 0
                   ? *(s32 *)(arg1 + 0) - *(s32 *)(arg0 + 0)
                   : *(s32 *)(arg0 + 0) - *(s32 *)(arg1 + 0));
    dist[1] = (*(s32 *)(arg0 + 4) - *(s32 *)(arg1 + 4) < 0
                   ? *(s32 *)(arg1 + 4) - *(s32 *)(arg0 + 4)
                   : *(s32 *)(arg0 + 4) - *(s32 *)(arg1 + 4));
    dist[2] = (*(s32 *)(arg0 + 8) - *(s32 *)(arg1 + 8) < 0
                   ? *(s32 *)(arg1 + 8) - *(s32 *)(arg0 + 8)
                   : *(s32 *)(arg0 + 8) - *(s32 *)(arg1 + 8));
    if (radius >= dist[0] && radius >= dist[1] && radius >= dist[2]) {
        if (*(s32 *)(arg0 + 0x354) != (s32)func_80025730 &&
            *(s32 *)(arg1 + 0x354) != (s32)func_80025730) {
            return 1;
        }
        if ((*(s32 *)(arg0 + 8) - *(s32 *)(arg1 + 8) < 0
                 ? *(s32 *)(arg1 + 8) - *(s32 *)(arg0 + 8)
                 : *(s32 *)(arg0 + 8) - *(s32 *)(arg1 + 8)) >= 501) {
            return 0;
        }
        return 1;
    }
    return 0;
}

s32 func_8003702C(u8 *, u8 *);
void func_800406D0(u8 *, u8 *, s32, s32);
void func_80041848(u8 *, s32);

s32 func_80025A38(u8 *arg0) {
    u8 *other;
    s32 dist;

    *(s16 *)(arg0 + 0x1CE) = 0;
    if (*(s32 *)(arg0 + 0x3F0) == 0) {
        goto part2;
    }
    other = *(u8 **)(*(s32 *)(arg0 + 0x3F0) + 8);
    if (arg0 == other) {
        return 0;
    }
    if (func_80025938(arg0, other) == 0) {
        goto part2;
    }
    if (CarHandlePairCollision(arg0, other) != 0) {
        goto collide;
    }
part2:
    if (*(s32 *)(arg0 + 0x3F4) == 0) {
        goto scan;
    }
    other = *(u8 **)(*(s32 *)(arg0 + 0x3F4) + 8);
    if (arg0 == other) {
        return 0;
    }
    if (func_80025938(arg0, other) == 0) {
        goto scan;
    }
    if (CarHandlePairCollision(arg0, other) == 0) {
        goto scan;
    }
collide:
    if (*(s16 *)(arg0 + 0x1EC) == 0) {
        func_800406D0(arg0, other, 6, 1);
        func_80041848(arg0, 0x4E);
    }
    if (*(s16 *)(other + 0x1EC) == 0) {
        func_800406D0(other, arg0, 6, 1);
    }
    if (*(s16 *)(arg0 + 0x1EC) != 0 && *(s16 *)(other + 0x1EC) != 0) {
        func_800406D0(D_800A3554[0], arg0, 6, 1);
    }
    *(s32 *)(arg0 + 0x3D8) = other;
    return 1;
scan:
    if (*(s16 *)(arg0 + 0x1EC) != 0) {
        return 0;
    }
    if (D_800A2E94[0] < 4) {
        return 0;
    }
    other = *(u8 **)(*(s32 *)(*(s32 *)(arg0 + 0x3F0) + 0) + 8);
    if (other != 0) {
        do {
            if (arg0 == other) {
                return 0;
            }
            dist = func_8003702C(arg0, other);
            if (dist < 0) {
                dist = -func_8003702C(arg0, other);
                asm("");
            } else {
                dist = func_8003702C(arg0, other);
            }
            if (dist >= 2) {
                break;
            }
            if (func_80025938(arg0, other) != 0 &&
                CarHandlePairCollision(arg0, other) != 0) {
                if (*(s16 *)(arg0 + 0x1EC) == 0) {
                    func_800406D0(arg0, other, 6, 1);
                }
                if (*(s16 *)(other + 0x1EC) == 0) {
                    func_800406D0(other, arg0, 6, 1);
                }
                if (*(s16 *)(arg0 + 0x1EC) != 0 &&
                    *(s16 *)(other + 0x1EC) != 0) {
                    func_800406D0(D_800A3554[0], arg0, 6, 1);
                }
                *(s32 *)(arg0 + 0x3D8) = other;
                func_80041848(arg0, 0x4E);
            }
            other = *(u8 **)(*(s32 *)(other + 0x3F0) + 8);
        } while (other != 0);
    }
    other = *(u8 **)(*(s32 *)(*(s32 *)(arg0 + 0x3F4) + 4) + 8);
    if (other != 0) {
        do {
            if (arg0 == other) {
                return 0;
            }
            dist = func_8003702C(arg0, other);
            if (dist < 0) {
                dist = -func_8003702C(arg0, other);
                asm("");
            } else {
                dist = func_8003702C(arg0, other);
            }
            if (dist >= 2) {
                return 0;
            }
            if (func_80025938(arg0, other) != 0 &&
                CarHandlePairCollision(arg0, other) != 0) {
                if (*(s16 *)(arg0 + 0x1EC) == 0) {
                    func_800406D0(arg0, other, 6, 1);
                }
                if (*(s16 *)(other + 0x1EC) == 0) {
                    func_800406D0(other, arg0, 6, 1);
                }
                if (*(s16 *)(arg0 + 0x1EC) != 0 &&
                    *(s16 *)(other + 0x1EC) != 0) {
                    func_800406D0(D_800A3554[0], arg0, 6, 1);
                }
                *(s32 *)(arg0 + 0x3D8) = other;
                func_80041848(arg0, 0x4E);
            }
            other = *(u8 **)(*(s32 *)(other + 0x3F4) + 8);
        } while (other != 0);
    }
    return 0;
}

void func_80025DD4(u8 *arg0, u8 *arg1) {
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;

    if (*(s16 *)(arg0 + 0x1EC) == 1 &&
        *(s16 *)(arg1 + 0x1EC) == *(s16 *)(arg0 + 0x1EC)) {
        return;
    }
    x = (*(s32 *)(arg0 + 0) + *(s32 *)(arg1 + 0)) / 2 + RandomScaledGet(100) -
        50;
    y = (*(s32 *)(arg0 + 4) + *(s32 *)(arg1 + 4)) / 2 + RandomScaledGet(100) -
        50;
    func_8003644C(1, x, y,
                  (*(s32 *)(arg0 + 8) + *(s32 *)(arg1 + 8)) / 2 +
                      RandomScaledGet(50) + 75);
    x2 = (*(s32 *)(arg0 + 0) + *(s32 *)(arg1 + 0)) / 2 + RandomScaledGet(100) -
         50;
    y2 = (*(s32 *)(arg0 + 4) + *(s32 *)(arg1 + 4)) / 2 + RandomScaledGet(100) -
         50;
    func_8003644C(1, x2, y2,
                  (*(s32 *)(arg0 + 8) + *(s32 *)(arg1 + 8)) / 2 +
                      RandomScaledGet(50) + 75);
}

extern void func_8001EEC4Args(u8 *, s32);
asm(".globl func_8001EEC4Args\nfunc_8001EEC4Args = func_8001EEC4");

void func_80025F40(u8 *arg0, s32 arg1) {
    s32 pos[3];
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;
    u8 *entry;

    entry = (u8 *)(*(s32 *)(*(s32 *)(arg0 + 0x370) + 0x40) +
                   (1 - (arg1 & 0xFF)) * 0x18);
    pos[0] = *(s32 *)(entry + 4);
    pos[1] = *(s32 *)(entry + 8);
    pos[2] = 0x4B;
    func_8001EEC4Args(arg0, arg1 & 0xFF);
    MatrixRotateVector(pos);
    pos[0] += *(s32 *)(arg0 + 0);
    pos[1] += *(s32 *)(arg0 + 4);
    pos[2] += *(s32 *)(arg0 + 8);
    x = pos[0] + RandomScaledGet(25);
    y = pos[1] + RandomScaledGet(25);
    func_8003644C(0, x, y, pos[2] + RandomScaledGet(50));
    x2 = pos[0] + RandomScaledGet(25);
    y2 = pos[1] + RandomScaledGet(25);
    func_8003644C(1, x2, y2, pos[2] + RandomScaledGet(50));
}

void func_80026074(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 ld5;
    s32 flag;
    volatile s32 pad[16];
    s32 dx;

    ld5 = arg5;
    flag = ld5;
    ld5 = ld5 << 24;
    if (ld5 != 0) {
        dx = arg2 << 16;
        *(s32 *)(arg0 + 0xC4) -= dx;
        *(s32 *)(arg0 + 0xC8) -= *(volatile s32 *)&arg3 << 16;
        *(s32 *)(arg0 + 0xD0) -= (*(volatile s32 *)&arg2 << 16) >> 1;
        *(s32 *)(arg0 + 0xD4) -= (*(volatile s32 *)&arg3 << 16) >> 1;
    } else {
        dx = arg2 << 16;
        dx = dx >> 1;
        *(s32 *)(arg0 + 0xC4) -= dx;
        *(s32 *)(arg0 + 0xC8) -= (*(volatile s32 *)&arg3 << 16) >> 1;
        *(s32 *)(arg0 + 0xD0) -= *(volatile s32 *)&arg2 << 16;
        *(s32 *)(arg0 + 0xD4) -= *(volatile s32 *)&arg3 << 16;
    }
    ld5 = flag << 24;
    if (ld5 != 0) {
        *(s32 *)(arg1 + 0xC4) += *(volatile s32 *)&arg2 << 16;
        *(s32 *)(arg1 + 0xC8) += *(volatile s32 *)&arg3 << 16;
        *(s32 *)(arg1 + 0xD0) += (*(volatile s32 *)&arg2 << 16) >> 1;
        *(s32 *)(arg1 + 0xD4) += (*(volatile s32 *)&arg3 << 16) >> 1;
    } else {
        *(s32 *)(arg1 + 0xC4) += (*(volatile s32 *)&arg2 << 16) >> 1;
        *(s32 *)(arg1 + 0xC8) += (*(volatile s32 *)&arg3 << 16) >> 1;
        *(s32 *)(arg1 + 0xD0) += *(volatile s32 *)&arg2 << 16;
        *(s32 *)(arg1 + 0xD4) += *(volatile s32 *)&arg3 << 16;
    }
}

extern s32 pairCosTable3[] asm("D_800A3A2CSmall");
extern s32 pairSinTable3[] asm("D_800A3A34Small");
extern s32 pairCosTable4[] asm("D_800A3A2C");
extern s32 pairSinTable4[] asm("D_800A3A34");
extern void func_800432C0(void *, s32);
extern void func_80043B68(void *, s32);
extern void func_8003AC18(u8 *, s32, s32, s32);
extern void CollisionApplyImpulse(u8 *, u8 *, Vec3, s32,
                                  s32) asm("func_80026074");

/* Resolves car-to-car contact and applies separation and velocity impulses.
 * Empty asm constraints retain the retail compiler register lifetimes.
 */
s32 CarHandlePairCollision(u8 *firstCar, u8 *secondCar) {
    Vec3 separation;
    Vec3 direction;
    Vec3 velocity;
    Vec3 original;
    Vec3 midpoint;
    register s32 tmp0 asm("v0");
    register s32 tmp1 asm("v1");
    register s32 productX asm("a1");
    register s32 callA0 asm("a0");
    register s32 callA1 asm("a1");
    register s32 productY asm("t1");
    s32 impulseX;
    s32 impulseY;
    register s32 impulsePart asm("t0");
    s32 nextCallback;
    s32 effectFlag;
    register s32 beyondFar asm("v0");
    s32 scratchA0;
    s32 carHeading;
    s32 contactAngle;
    s32 otherHeading;
    s32 responseCode;
    s32 headingDifference;
    s32 collisionExtent;
    s32 scratchA1;
    s32 otherPositionY;
    s32 relativeSpeed;
    s32 work0;
    register s32 work1 asm("s1");
    register s32 work2 asm("s2");
    register s32 work3 asm("s3");
    s32 collisionHalfWidth;
    s32 angleFromHalfTurn;
    s32 meanSpeedA;
    s32 meanSpeedB;
    s32 wrappedHeadingDifference;
    s32 work6;
    s32 result;
    s32 responseXInRange;
    s32 overlapLimit;
    s32 outsideCollisionWidth;
    s32 newSpeedA;
    s32 newSpeedB;
    s32 responseYInRange;
    s32 roundedHeadingDifference;
    s32 scratchV1;
    u32 speedSumA;
    u32 speedSumB;
    u8 *car;
    u8 *otherCar;

    car = firstCar;

    otherCar = secondCar;

    if (D_8008CA28[0] == 0) {
        tmp0 = (s32)D_800A3554[0];
        if (otherCar == (u8 *)tmp0) {
            otherCar = car;
            car = (u8 *)tmp0;
        }
    }
    separation.x = (*(s32 *)(otherCar + 0x0)) - (*(s32 *)(car + 0x0));
    separation.y = (*(s32 *)(otherCar + 0x4)) - (*(s32 *)(car + 0x4));
    separation.z = (*(s32 *)(otherCar + 0x8)) - (*(s32 *)(car + 0x8));
    original = separation;
    midpoint.x = (s32)((*(s32 *)(otherCar + 0x0)) + (*(s32 *)(car + 0x0))) / 2;
    midpoint.y = (s32)((*(s32 *)(otherCar + 0x4)) + (*(s32 *)(car + 0x4))) / 2;
    if ((*(s32 *)(car + 0x354)) == (s32)func_80025730) {
        contactAngle = (*(s16 *)(car + 0x38A));
        angleFromHalfTurn = contactAngle - 0x200;
        if (angleFromHalfTurn >= 0) {
            if (angleFromHalfTurn < 0x100) {
                goto block_8;
            }
            goto block_9;
        }
        if ((0x200 - contactAngle) < 0x100) {
        block_8:
            tmp1 = *(s16 *)(car + 0x114);
            tmp0 = 0x600 - tmp1;
            work6 = tmp0 & 0x3FF;

        } else {
            goto block_9;
        }
    } else {
    block_9:
        tmp1 = *(s16 *)(car + 0x114);
        tmp0 = 0x3FF;
        work6 = tmp0 - tmp1;
    }
    tmp0 = D_800A3A2CAbsolute[0];
    work1 = work6 << 2;
    callA1 = original.x;
    tmp0 = work1 + tmp0;
    callA0 = *(s32 *)tmp0;
    tmp0 = MathMultiplyFixed16(callA0, callA1 << 16);
    tmp1 = D_800A3A34Absolute[0];
    callA1 = original.y;
    tmp1 = work1 + tmp1;
    callA0 = *(s32 *)tmp1;
    work0 = tmp0;
    tmp0 = MathMultiplyFixed16(callA0, callA1 << 16);
    tmp1 = D_800A3A34Absolute2[0];
    callA1 = original.x;
    work0 -= tmp0;
    work0 >>= 16;
    separation.x = work0;
    tmp1 = work1 + tmp1;
    callA0 = *(s32 *)tmp1;
    tmp0 = MathMultiplyFixed16(callA0, callA1 << 16);
    tmp1 = D_800A3A2CAbsolute2[0];
    callA1 = original.y;
    work1 += tmp1;
    asm("" : "=r"(work1) : "0"(work1));
    callA0 = *(s32 *)work1;
    work0 = tmp0;
    work0 += MathMultiplyFixed16(callA0, callA1 << 16);
    work0 >>= 16;
    separation.y = work0;
    tmp0 = *(s32 *)(car + 0x370);
    tmp0 = *(s16 *)(tmp0 + 0x1E);
    tmp1 = separation.x;
    collisionHalfWidth = tmp0 - 10;
    tmp0 = collisionHalfWidth << 1;
    scratchA0 = tmp0;
    if (tmp1 >= 0) {
        tmp0 = tmp0 < tmp1;
    } else {
        tmp0 = scratchA0 < -tmp1;
    }
    outsideCollisionWidth = tmp0;
    result = 0;
    if (outsideCollisionWidth == 0) {
        work3 = MathMultiplyFixed16((*(s32 *)(otherCar + 0x18)), 0xFA0);

        work2 = MathMultiplyFixed16((*(s32 *)(otherCar + 0x24)), 0xFA0);

        tmp0 = MathMultiplyFixed16(*(s32 *)(otherCar + 0x30), 0xFA0);
        tmp1 = pairCosTable3[0];
        work1 = work6 << 2;
        direction.z = tmp0;
        tmp1 = work1 + tmp1;
        callA0 = *(s32 *)tmp1;
        work3 <<= 16;
        tmp0 = MathMultiplyFixed16(callA0, work3);
        tmp1 = pairSinTable3[0];
        tmp1 = work1 + tmp1;
        callA0 = *(s32 *)tmp1;
        asm("" : "=r"(work2) : "0"(work2), "r"(callA0));
        work2 <<= 16;
        callA1 = work2;
        asm("" : "=r"(tmp0) : "0"(tmp0), "r"(callA0), "r"(callA1));
        work0 = tmp0;
        tmp0 = MathMultiplyFixed16(callA0, callA1);
        tmp1 = pairSinTable4[0];
        work0 -= tmp0;
        work0 >>= 16;
        direction.x = work0;
        tmp1 = work1 + tmp1;
        callA0 = *(s32 *)tmp1;
        tmp0 = MathMultiplyFixed16(callA0, work3);
        tmp1 = pairCosTable4[0];
        work1 += tmp1;
        asm("" : "=r"(work1) : "0"(work1));
        callA0 = *(s32 *)work1;
        callA1 = work2;
        work0 = tmp0;
        work0 += MathMultiplyFixed16(callA0, callA1);
        work0 >>= 16;
        direction.y = work0;
        tmp0 = *(s32 *)(car + 0xB0);
        productX = *(s32 *)(otherCar + 0xB0);
        tmp1 = direction.x;
        scratchA0 = D_800A3668Absolute[0];
        tmp0 -= productX;
        productX = tmp0 * tmp0;
        tmp1 = __builtin_abs(tmp1);
        scratchA0 += tmp1;
        work6 = *(u8 *)scratchA0;
        velocity.x = tmp0;
        tmp0 = *(s32 *)(car + 0xB4);
        tmp1 = *(s32 *)(otherCar + 0xB4);
        tmp0 -= tmp1;
        productY = tmp0 * tmp0;
        velocity.y = tmp0;
        tmp1 = *(s32 *)(otherCar + 0xB8);
        tmp0 = *(s32 *)(car + 0xB8);
        tmp0 -= tmp1;
        velocity.z = tmp0;
        tmp0 = MathSqrt(productX + productY);
        relativeSpeed = tmp0;
        tmp1 = separation.y;
        scratchA0 = *(s16 *)(car + 0x1EC);
        tmp0 = 1;
        work2 = tmp1;
        if (tmp1 < 0) {
            work2 = -work2;
        }
        if ((scratchA0 == tmp0) &&
            ((*(s16 *)(otherCar + 0x1EC)) == scratchA0)) {
            tmp0 = *(s32 *)(car + 0x370);
            tmp0 = *(s16 *)(tmp0 + 0x22);
            scratchV1 = tmp0 - 0x1E;
        } else {
            tmp0 = *(s32 *)(car + 0x370);
            tmp0 = *(s16 *)(tmp0 + 0x22);
            scratchV1 = tmp0 - 0xF;
        }
        (*(s16 *)(car + 0x1CE)) = 0;
        tmp0 = (u32)work6 < 0xA1;
        scratchA1 = scratchV1 << 1;
        if (tmp0 == 0) {
            tmp0 = scratchA1 + scratchV1;
            scratchV1 = (u32)tmp0 >> 31;
            tmp0 = (tmp0 + scratchV1) >> 1;
            tmp0 = work2 < tmp0;
            if (tmp0 != 0) {
                responseCode = 1;
                if (relativeSpeed >= 0x12D) {
                    tmp0 = *(s16 *)(car + 0x1EC);
                    goto block_125;
                }
                if (separation.x >= 0) {
                    (*(s16 *)(car + 0x1CE)) = 2;
                    tmp0 = collisionHalfWidth << 3;
                    tmp1 = tmp0 + collisionHalfWidth;
                    if (tmp1 < 0) {
                        tmp1 += 3;
                    }
                    tmp0 = separation.x;
                    callA0 = *(s32 *)(car + 0x18);
                    tmp1 >>= 2;
                    tmp0 -= tmp1;
                    tmp1 = (u32)tmp0 >> 31;
                    tmp0 += tmp1;
                    work3 = tmp0 >> 1;
                    (*(s32 *)(car + 0x0)) =
                        (s32)((*(s32 *)(car + 0x0)) +
                              MathMultiplyFixed16(callA0, work3));
                    (*(s32 *)(car + 0x4)) =
                        (s32)((*(s32 *)(car + 0x4)) +
                              MathMultiplyFixed16((*(s32 *)(car + 0x24)),
                                                  work3));
                    (*(s32 *)(otherCar + 0x0)) =
                        (s32)((*(s32 *)(otherCar + 0x0)) -
                              MathMultiplyFixed16((*(s32 *)(car + 0x18)),
                                                  work3));
                    (*(s32 *)(otherCar + 0x4)) =
                        (s32)((*(s32 *)(otherCar + 0x4)) -
                              MathMultiplyFixed16((*(s32 *)(car + 0x24)),
                                                  work3));
                    if (direction.x > 0) {
                        speedSumA = (*(s32 *)(otherCar + 0x90)) +
                                    (*(s32 *)(car + 0x90));
                        meanSpeedA =
                            (s32)(speedSumA + (speedSumA >> 0x1F)) >> 1;
                        if ((*(s16 *)(otherCar + 0x1EC)) != 0) {
                            (*(s32 *)(otherCar + 0x90)) =
                                (s32)(meanSpeedA + 0xA0000);
                        }
                        if ((*(s16 *)(car + 0x1EC)) != 0) {
                            newSpeedA = meanSpeedA + 0xFFF60000;
                            goto block_40;
                        }
                    } else {
                        tmp0 = *(s32 *)(otherCar + 0x90);
                        tmp1 = *(s32 *)(car + 0x90);
                        scratchA0 = *(s16 *)(otherCar + 0x1EC);
                        tmp0 += tmp1;
                        if (tmp0 < 0) {
                            tmp0 = -tmp0;
                        }
                        tmp1 = (u32)tmp0 >> 31;
                        tmp0 += tmp1;
                        tmp1 = tmp0 >> 1;
                        if (scratchA0 != 0) {
                            (*(s32 *)(otherCar + 0x90)) =
                                (s32)(tmp1 + 0xFFF60000);
                        }
                        if ((*(s16 *)(car + 0x1EC)) != 0) {
                            newSpeedA = tmp1 + 0xA0000;
                        block_40:
                            (*(s32 *)(car + 0x90)) = newSpeedA;
                        }
                    }
                    func_80025DD4(otherCar, car);
                    work0 = 1;
                    if (relativeSpeed >= 0x2E) {
                        if (relativeSpeed >= 0x79) {
                            func_800432C0(otherCar, 7);
                            if (RandomScaledGet(0xA) == 0) {
                                callA1 = 0;
                                if (separation.y > 0) {
                                    callA0 = (s32)car;
                                } else {
                                    callA0 = (s32)car;
                                    callA1 = 1;
                                }
                                func_800432C0((void *)callA0, callA1);
                            }
                        }
                        if (RandomScaledGet(0xA) == 0) {
                            callA0 = (s32)car;
                            if (separation.y > 0) {
                                asm("# positive contact side");
                                callA1 = 5;
                            } else {
                                callA1 = 6;
                            }
                            func_800432C0((void *)callA0, callA1);
                        }
                        func_80043B68(car, 0);
                        func_80043B68(car, 1);
                        func_80043B68(otherCar, 2);
                        func_80043B68(otherCar, 3);
                        work0 = 1;
                    }
                    CollisionApplyImpulse(car, otherCar, velocity, work0,
                                          work0);
                    tmp0 = *(s16 *)(car + 0x114);
                    tmp1 = D_800A3A2CAbsolute[0];
                    tmp0 += 0x200;
                    work6 = tmp0 & 0x3FF;
                    scratchA0 = work6 << 2;
                    tmp1 = scratchA0 + tmp1;
                    tmp0 = *(s32 *)tmp1;
                    impulseX = relativeSpeed * tmp0;
                    tmp1 = D_800A3A34Absolute[0];
                    tmp0 = *(s32 *)(car + 0xC4);
                    scratchA0 += tmp1;
                    asm(""
                        : "=r"(impulsePart)
                        : "0"(impulseX), "r"(tmp0), "r"(scratchA0));
                    tmp0 += impulsePart;
                    *(s32 *)(car + 0xC4) = tmp0;
                    tmp0 = *(s32 *)scratchA0;
                    impulseY = relativeSpeed * tmp0;
                    tmp0 = *(s32 *)(car + 0xC8);
                    asm("" : "=r"(impulsePart) : "0"(impulseY), "r"(tmp0));
                    tmp0 += impulsePart;
                    *(s32 *)(car + 0xC8) = tmp0;
                    result = 2;
                    if ((*(s16 *)(otherCar + 0x1EC)) == work0) {
                        func_8003AC18(otherCar, relativeSpeed, separation.x,
                                      separation.y);
                        asm("# collision response 1");
                        return 2;
                    }
                    return result;
                }
                (*(s16 *)(car + 0x1CE)) = 3;
                tmp1 = separation.x;
                tmp0 = collisionHalfWidth << 3;
                tmp0 += collisionHalfWidth;
                tmp1 = -tmp1;
                if (tmp0 < 0) {
                    tmp0 += 3;
                }
                callA0 = *(s32 *)(car + 0x18);
                tmp0 >>= 2;
                tmp0 = tmp1 - tmp0;
                tmp1 = (u32)tmp0 >> 31;
                tmp0 += tmp1;
                work3 = tmp0 >> 1;
                (*(s32 *)(car + 0x0)) =
                    (s32)((*(s32 *)(car + 0x0)) -
                          MathMultiplyFixed16(callA0, work3));
                (*(s32 *)(car + 0x4)) =
                    (s32)((*(s32 *)(car + 0x4)) -
                          MathMultiplyFixed16((*(s32 *)(car + 0x24)), work3));
                (*(s32 *)(otherCar + 0x0)) =
                    (s32)((*(s32 *)(otherCar + 0x0)) +
                          MathMultiplyFixed16((*(s32 *)(car + 0x18)), work3));
                (*(s32 *)(otherCar + 0x4)) =
                    (s32)((*(s32 *)(otherCar + 0x4)) +
                          MathMultiplyFixed16((*(s32 *)(car + 0x24)), work3));
                if (direction.x > 0) {
                    speedSumB =
                        (*(s32 *)(otherCar + 0x90)) + (*(s32 *)(car + 0x90));
                    meanSpeedB = (s32)(speedSumB + (speedSumB >> 0x1F)) >> 1;
                    if ((*(s16 *)(otherCar + 0x1EC)) != 0) {
                        (*(s32 *)(otherCar + 0x90)) =
                            (s32)(meanSpeedB + 0xA0000);
                    }
                    if ((*(s16 *)(car + 0x1EC)) != 0) {
                        newSpeedB = meanSpeedB + 0xFFF60000;
                        goto block_69;
                    }
                } else {
                    tmp0 = *(s32 *)(otherCar + 0x90);
                    tmp1 = *(s32 *)(car + 0x90);
                    scratchA0 = *(s16 *)(otherCar + 0x1EC);
                    tmp0 += tmp1;
                    if (tmp0 < 0) {
                        tmp0 = -tmp0;
                    }
                    tmp1 = (u32)tmp0 >> 31;
                    tmp0 += tmp1;
                    tmp1 = tmp0 >> 1;
                    if (scratchA0 != 0) {
                        (*(s32 *)(otherCar + 0x90)) = (s32)(tmp1 + 0xFFF60000);
                    }
                    if ((*(s16 *)(car + 0x1EC)) != 0) {
                        newSpeedB = tmp1 + 0xA0000;
                    block_69:
                        (*(s32 *)(car + 0x90)) = newSpeedB;
                    }
                }
                func_80025DD4(otherCar, car);
                if (relativeSpeed < 0x2E) {
                    effectFlag = 1;
                    goto effectsDoneNegative;
                }

                if (relativeSpeed >= 0x79) {
                    func_800432C0(otherCar, 7);
                    if (RandomScaledGet(0xA) == 0) {
                        callA1 = 0;
                        if (separation.y > 0) {
                            callA0 = (s32)car;
                        } else {
                            callA0 = (s32)car;
                            callA1 = 1;
                        }
                        func_800432C0((void *)callA0, callA1);
                    }
                }
                if (RandomScaledGet(0xA) == 0) {
                    callA0 = (s32)car;
                    if (separation.y > 0) {
                        asm("# positive contact side");
                        callA1 = 5;
                    } else {
                        callA1 = 6;
                    }
                    func_800432C0((void *)callA0, callA1);
                }
                func_80043B68(car, 0);
                func_80043B68(car, 1);
                func_80043B68(otherCar, 2);
                func_80043B68(otherCar, 3);
                effectFlag = 1;

            effectsDoneNegative:
                CollisionApplyImpulse(car, otherCar, velocity, 0, effectFlag);
                return 2;
            }
            if (work2 < scratchA1) {
                (*(s16 *)(car + 0x1CE)) = 4;
                work2 = scratchA1 - work2;
                work3 = 1;
                if (separation.y > 0) {
                    work2 = -work2;
                }
                work1 = MathMultiplyFixed16((*(s32 *)(car + 0x1C)), work2);

                (*(s32 *)(car + 0x0)) = (s32)((*(s32 *)(car + 0x0)) + work1);
                work0 = MathMultiplyFixed16((*(s32 *)(car + 0x28)), work2);

                (*(s32 *)(car + 0x4)) = (s32)((*(s32 *)(car + 0x4)) + work0);
                (*(s32 *)(otherCar + 0x0)) =
                    (s32)((*(s32 *)(otherCar + 0x0)) -
                          MathMultiplyFixed16((*(s32 *)(car + 0x1C)), work2));
                (*(s32 *)(otherCar + 0x4)) =
                    (s32)((*(s32 *)(otherCar + 0x4)) -
                          MathMultiplyFixed16((*(s32 *)(car + 0x28)), work2));
                func_80025DD4(otherCar, car);
                nextCallback = (s32)func_80025720;
                if ((((*(s16 *)(car + 0x1EC)) != work3) ||
                     (nextCallback != (s32)func_80025730)) &&
                    ((*(s32 *)(car + 0x354)) != (s32)func_80025730) &&
                    ((*(s8 *)(car + 0x200)) != 4)) {
                    (*(s32 *)(car + 0x354)) = nextCallback;
                }
                if ((*(s16 *)(car + 0x1EC)) == 0) {
                    if ((*(s16 *)(otherCar + 0x1EC)) != 0) {
                        carHeading = (*(s16 *)(car + 0x114));
                        headingDifference =
                            carHeading - (*(s16 *)(otherCar + 0x114));
                        wrappedHeadingDifference = headingDifference + 0x400;
                        roundedHeadingDifference = wrappedHeadingDifference;
                        if (wrappedHeadingDifference < 0) {
                            roundedHeadingDifference =
                                headingDifference + 0x7FF;
                        }
                        if ((u32)((wrappedHeadingDifference -
                                   ((roundedHeadingDifference >> 0xA) << 0xA)) -
                                  0x101) < 0x1FFU) {
                            otherHeading = (carHeading + 0x200) & 0x3FF;
                        } else {
                            otherHeading = carHeading;
                        }
                        (*(s16 *)(otherCar + 0x114)) = otherHeading;
                        (*(s16 *)(otherCar + 0x116)) =
                            (s16)((s32)(otherHeading << 0x10) >> 0xE);
                    }
                    responseYInRange = work1 < 0x33;
                } else {
                    responseYInRange = work1 < 0x33;
                }
                if (responseYInRange == 0) {
                    work1 = 0x32;

                    goto block_105;
                }
                if (work1 < -0x32) {
                    work1 = -0x32;
                }
            block_105:
                responseXInRange = work0 < 0x33;
                if (responseXInRange == 0) {
                    work0 = 0x32;

                } else if (work0 < -0x32) {
                    work0 = -0x32;
                }
                if (separation.x >= -collisionHalfWidth) {
                    (*(s32 *)(car + 0xC4)) =
                        (s32)((*(s32 *)(car + 0xC4)) + (work1 << 0x11));
                    (*(s32 *)(car + 0xC8)) =
                        (s32)((*(s32 *)(car + 0xC8)) + (work0 << 0x11));
                }
                tmp0 = separation.x;
                tmp0 = collisionHalfWidth < tmp0;
                if (tmp0 != 0) {
                    return 1;
                }
                tmp1 = *(s32 *)(car + 0xD0);
                callA0 = *(s32 *)(car + 0xD4);
                scratchA1 = *(s16 *)(car + 0x1EC);
                tmp0 = work1 << 16;
                tmp1 += tmp0;
                tmp0 = work0 << 16;
                callA0 += tmp0;
                *(s32 *)(car + 0xD0) = tmp1;
                *(s32 *)(car + 0xD4) = callA0;
                if (scratchA1 != 0) {
                    goto sideReturnOne;
                }
                tmp1 = *(s16 *)(otherCar + 0x1EC);
                tmp0 = 1;
                if (tmp1 == tmp0) {
                    tmp1 = 0xFFFB0000;
                    tmp0 = *(s32 *)(otherCar + 0x90);
                    tmp0 += tmp1;
                    *(s32 *)(otherCar + 0x90) = tmp0;
                sideReturnOne:
                    asm("# side return one");
                    tmp0 = 1;
                }
                return tmp0;
            }
            goto block_151;
        }
        tmp0 = separation.x;
        collisionExtent = collisionHalfWidth + scratchV1;
        if (tmp0 >= 0) {
            asm("" : "=r"(scratchV1) : "0"(scratchV1));
            tmp0 = collisionExtent < tmp0;
            if (tmp0 != 0) {
                asm("# positive lateral rejection");
                return 0;
            }
            overlapLimit = collisionHalfWidth + scratchV1;
            goto block_122;
        }
        asm("" : "=r"(scratchV1) : "0"(scratchV1));
        tmp0 = -tmp0;
        tmp0 = collisionExtent < tmp0;
        result = 0;
        if (tmp0 == 0) {
            overlapLimit = collisionHalfWidth + scratchV1;
        block_122:
            if (work2 < overlapLimit) {
                if (relativeSpeed >= 0x12D) {
                    tmp0 = *(s16 *)(car + 0x1EC);
                    responseCode = 5;
                block_125:
                    asm("" : "=r"(callA0) : "0"((s32)func_80025730));
                    (*(s16 *)(car + 0x1CE)) = responseCode;
                    if ((tmp0 != 1) && ((*(s32 *)(car + 0x354)) != callA0) &&
                        ((*(s8 *)(car + 0x200)) != 4)) {
                        (*(s32 *)(car + 0x354)) = callA0;
                    }
                    if (((*(s16 *)(otherCar + 0x1EC)) == 0)) {
                        tmp0 = *(s32 *)(otherCar + 0x354);
                        callA0 = (s32)func_80025730;
                        if ((tmp0 != callA0) &&
                            ((*(s8 *)(otherCar + 0x200)) != 4)) {
                            (*(s32 *)(otherCar + 0x354)) = callA0;
                        }
                    }
                    result = 4;
                    if ((*(s16 *)(car + 0x1EC)) == 0) {
                        func_8003AC18(otherCar, relativeSpeed, separation.x,
                                      separation.y);
                        return 4;
                    }
                    return result;
                }
                (*(s16 *)(car + 0x1CE)) = 6;
                tmp0 = original.x;
                tmp1 = tmp0 * tmp0;
                tmp0 = original.y;
                productY = tmp0 * tmp0;
                work3 = MathSqrt(tmp1 + productY);
                (*(s32 *)(car + 0x0)) =
                    (s32)(midpoint.x +
                          ((s32)(MathFixedDivide((*(s32 *)(car + 0x0)) -
                                                     midpoint.x,
                                                 work3) *
                                 0x320) >>
                           0x10));
                (*(s32 *)(car + 0x4)) =
                    (s32)(midpoint.y +
                          ((s32)(MathFixedDivide((*(s32 *)(car + 0x4)) -
                                                     midpoint.y,
                                                 work3) *
                                 0x320) >>
                           0x10));
                (*(s32 *)(otherCar + 0x0)) =
                    (s32)(midpoint.x +
                          ((s32)(MathFixedDivide((*(s32 *)(otherCar + 0x0)) -
                                                     midpoint.x,
                                                 work3) *
                                 0x320) >>
                           0x10));
                otherPositionY =
                    midpoint.y +
                    ((s32)(MathFixedDivide(
                               (*(s32 *)(otherCar + 0x4)) - midpoint.y, work3) *
                           0x320) >>
                     0x10);
                (*(s32 *)(otherCar + 0x4)) = otherPositionY;
                func_80025DD4(otherCar, car);
                tmp1 = separation.x;
                if (tmp1 >= -collisionHalfWidth) {
                    CollisionApplyImpulse(car, otherCar, velocity, 1, 0);
                    if ((separation.x < 0) &&
                        ((*(s16 *)(otherCar + 0x1EC)) != 0)) {
                        (*(s32 *)(otherCar + 0x90)) = 0;
                    }
                } else {
                    beyondFar = collisionHalfWidth < tmp1;
                    if (beyondFar == 0) {
                        tmp0 = *(s32 *)(otherCar + 0xB0);
                        tmp1 = *(s32 *)(otherCar + 0xB4);
                        scratchA0 = (u32)tmp0 >> 31;
                        tmp0 = (tmp0 + scratchA0) >> 1;
                        work1 = tmp0 << 16;
                        tmp0 = (u32)tmp1 >> 31;
                        tmp1 += tmp0;
                        tmp1 >>= 1;
                        work0 = tmp1 << 16;
                        asm volatile("" : : "r"(work1), "r"(work0));
                        CollisionApplyImpulse(car, otherCar, velocity, 0, 1);
                    }
                }
                nextCallback = (s32)func_80025614;
                if ((((*(s16 *)(car + 0x1EC)) != 1) ||
                     (nextCallback != (s32)func_80025730)) &&
                    ((*(s32 *)(car + 0x354)) != (s32)func_80025730) &&
                    ((*(s8 *)(car + 0x200)) != 4)) {
                    (*(s32 *)(car + 0x354)) = nextCallback;
                }
                result = 2;
                if ((*(s16 *)(car + 0x1EC)) == 0) {
                    func_8003AC18(otherCar, relativeSpeed, separation.x,
                                  separation.y);
                    return 2;
                }
                return result;
            }
            if ((tmp0 = work2 < scratchA1) != 0) {
                (*(s16 *)(car + 0x1CE)) = 7;
                result = 3;
                if ((*(s16 *)(otherCar + 0x1EC)) == 1) {
                    func_8003AC18(otherCar, relativeSpeed, separation.x,
                                  separation.y);
                    return 3;
                }
                return result;
            }
        block_151:
            result = 0;
            return result;
        }
        return result;
    }
    return result;
}
s32 func_800270F4(void *arg0, s32 arg1) {
    s32 index;
    s32 product;
    s32 result;

    index = (0x400 - arg1) & 0x3FF;
    product = ((s32 **)D_800A3A2CAbsolute)[0][index];
    product *= *(s32 *)arg0;
    result = product -
             ((s32 **)D_800A3A34Absolute)[0][index] * *(s32 *)((s32)arg0 + 4);
    result = -(result >> 16) * 3;
    if (result < 0) {
        result += 3;
    }
    return result >> 2;
}

typedef struct {
    s16 x, y, z, pad;
} ContactPoint;
typedef struct TrackContact {
    u8 unk0[19];
    u8 flags;
    u8 unk14[2];
    s16 heading;
    ContactPoint *point0;
    ContactPoint *point1;
    ContactPoint *point2;
    ContactPoint *point3;
    struct TrackContact *next;
} TrackContact;
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
typedef struct ContactCar {
    s32 x;
    s32 y;
    s32 z;
    u8 unkC[12];
    s32 axisXX;
    s32 axisXY;
    u8 unk20[4];
    s32 axisYX;
    s32 axisYY;
    u8 unk2C[4];
    s32 axisZX;
    s32 axisZY;
    u8 unk38[88];
    s32 speed;
    u8 unk94[28];
    s32 velocityX;
    s32 velocityY;
    u8 unkB8[12];
    s32 frontVelocityX;
    s32 frontVelocityY;
    u8 unkCC[4];
    s32 rearVelocityX;
    s32 rearVelocityY;
    u8 unkD8[29];
    u8 collisionPending;
    u8 unkF6[12];
    s16 unk102;
    u8 unk104[16];
    s16 heading;
    u8 unk116[202];
    s16 trackIndex;
    u8 unk1E2[10];
    s16 unk1EC;
    u8 unk1EE[6];
    s32 oldTrackIndex;
    s32 regionIndex;
    u8 unk1FC[4];
    s8 mode;
    u8 unk201[13];
    s16 unk20E;
    u8 unk210[8];
    s32 lateralSpeed;
    u8 unk21C[148];
    s16 frontLeftEffect;
    u8 unk2B2[38];
    s16 frontRightEffect;
    u8 unk2DA[38];
    s16 rearLeftEffect;
    u8 unk302[38];
    s16 rearRightEffect;
    u8 unk32A[42];
    void (*callback)(u8 *);
    u8 unk358[10];
    u16 frontRightContact;
    u16 frontLeftContact;
    u16 rearRightContact;
    u16 rearLeftContact;
    u8 unk36A[6];
    ContactShape *shape;
} ContactCar;
typedef struct ContactRegion {
    u16 minX;
    u16 minY;
    u16 maxX;
    u16 maxY;
    u8 unk8[8];
} ContactRegion;
typedef struct ContactTrack {
    u8 unk0[40];
    TrackContact *contacts;
    u8 unk2C[100];
} ContactTrack;
extern char D_8008CFE0[];
extern s32 *gContactCosTable asm("D_800A3A2CAbsolute2");
extern s32 *gContactSinTable asm("D_800A3A34Absolute2");

/* Resolves the nearest track-edge contact and applies wheel impulses. */
s32 CarHandleWallCollision(void *object) {
    ContactCar *car;
    /* Keep the coordinates and effect vector in their retail stack slots. */
    struct {
        s32 reserved0[4];
        s32 point[3];
        s32 reserved1[9];
        s32 effect[3];
        s32 reserved2;
    } workspace;
    register ContactCorner *corners asm("$3");
    register ContactCorner *corners2 asm("$3");
    ContactPoint *wallPoint;
    register ContactRegion *region asm("$16");
    register TrackContact *nearestContact asm("$17");
    register TrackContact *contact asm("$19");
    register s32 heading asm("$5");
    register s32 impulse asm("$22");
    s32 trackIndex;
    register s32 effectValue asm("$3");
    register s32 effectValue2 asm("$3");
    register s32 *forwardSinEntry asm("$5");
    register s32 *normalSinEntry asm("$5");
    register s32 *forwardCosEntry asm("$3");
    register s32 *normalCosEntry asm("$3");
    register s32 positiveDelta asm("$4");
    s32 firstProjection;
    register s32 shiftedPoint asm("$5");
    register s32 angleLoss asm("$3");
    s32 coefficient;
    register s32 yVelocity asm("$3");
    register s32 halfProduct asm("$2");
    register s32 halfSign asm("$5");
    register s32 frontCoefficient asm("$2");
    register s32 carHeading asm("$2");
    register s32 tailSpeed asm("$6");
    register s32 tailSpeed2 asm("$2");
    register s32 basisValue asm("$4");
    register s32 shapeExtent asm("$2");
    register ContactRegion *regionBase asm("$3");
    register s32 *sinSubtract asm("$4");
    register ContactTrack *track asm("$4");
    register s32 rowOffset asm("$2");
    register s32 originX asm("$3");
    register s32 originY asm("$2");
    register s32 speedQuarter asm("$4");
    register ContactCar *callbackCar asm("$4");
    s32 impulseX;
    register s32 normalAddress asm("$3");
    register s32 rearNormalAddress asm("$5");
    s32 secondProjection;
    register ContactShape *shape asm("$3");
    register s32 shapeWidth asm("$3");
    register s32 projectedVelocity asm("$2");
    register s32 *cosTable asm("$6");
    register s32 *sinTable asm("$5");
    register s32 *rearCosTable asm("$7");
    register s32 *rearSinTable asm("$6");
    register void (*nextCallback)(u8 *) asm("$4");
    register s32 value0 asm("$16");
    register s32 value1 asm("$17");
    register s32 value4 asm("$20");
    register s32 value5 asm("$21");
    register s32 regionCount asm("$23");
    s32 sumX;
    register s32 reverseHeading3 asm("$2");
    register s32 reverseHeading4 asm("$2");
    register s32 reverseHeading5 asm("$2");
    register s32 reverseHeading6 asm("$2");
    s32 meanY;
    register s32 dx asm("$2");
    register s32 absDx asm("$2");
    s32 dy;
    register s32 previousSpeed asm("$2");
    s32 nextSpeed;
    register s32 reverseHeading asm("$2");
    register s32 reverseHeading2 asm("$2");
    register s32 headingDelta asm("$3");
    register s32 normalAngleSum asm("$3");
    s32 speedLimit;
    register s32 normalImpulse asm("$4");
    register s32 normalImpulse2 asm("$4");
    register s32 normalImpulse3 asm("$4");
    register s32 normalImpulse4 asm("$4");
    register s32 normalImpulse5 asm("$4");
    register s32 currentY asm("$5");
    register s32 absDy asm("$5");
    register s32 angleDifference asm("$5");
    register s32 effectWheel asm("$5");
    register s32 effectWheel2 asm("$5");
    s32 centerX;
    register s32 squareX asm("$4");
    register s32 remainingRegions asm("$19");
    register s32 roundedDistance2 asm("$2");
    s32 leftFrontEffect;
    s32 leftRearEffect;
    register s32 normalHeading2 asm("$2");
    s32 roundedX;
    s32 roundedY;
    register s32 normalHeading3 asm("$2");
    register s32 lightImpact asm("$2");
    register s32 normalHeading4 asm("$2");
    register s32 currentX asm("$2");
    register s32 roundedHeadingDelta asm("$2");
    register s32 roundedNormalAngle asm("$2");
    register s32 roundedDistance asm("$2");
    s32 rightFrontEffect;
    s32 rightRearEffect;
    register s32 normalHeading asm("$2");
    register s32 regionResult asm("$3");
    register s32 impactSpeed asm("$3");
    register u32 distance asm("$4");
    register s32 quarterY asm("$3");
    s32 *regionHome;

    car = (ContactCar *)object;
    value4 = 0x0FFFFFFF;
    trackIndex = car->trackIndex;
    nearestContact = NULL;
    if (trackIndex == -1) {
        trackIndex = car->oldTrackIndex;
        if (trackIndex == -1) {
            return 0;
        }
    }
    {
        /* All four contact flags can retain the incoming impulse register. */
        asm("" : "=r"(impulse));
        track = FAR_VAR(ContactTrack *, gFarTrack);
        rowOffset = trackIndex * 0x90;
        rowOffset = (s32)track + rowOffset;
        contact = *(TrackContact **)(rowOffset + 0x28);
        if (contact == NULL) {
            contact = track->contacts;
        }
        currentX = car->x;
        if (currentX < 0) {
            currentX += 3;
        }
        currentY = car->y;
        currentX >>= 2;
        originX = FAR_VAR(s32, gFarOffsetX);
        value5 = currentX - originX;
        if (currentY < 0) {
            currentY += 3;
        }
        originY = FAR_VAR(s32, gFarOffsetY);
        quarterY = currentY >> 2;
        value0 = quarterY - originY;
        if (contact != NULL) {
            do {

                sumX = contact->point0->x + contact->point1->x +
                       contact->point2->x + contact->point3->x;
                centerX = sumX >> 2;
                if (sumX < 0) {
                    centerX = (s32)(sumX + 3) >> 2;
                }
                workspace.point[0] = centerX;
                meanY = (s32)(contact->point0->y + contact->point1->y +
                              contact->point2->y + contact->point3->y) /
                        4;
                absDy = meanY - value0;
                workspace.point[1] = meanY;
                if (absDy < 0) {
                    absDy = value0 - meanY;
                }
                dx = centerX - value5;
                if (dx < 0) {
                    absDx = value5 - centerX;
                    squareX = absDx * absDx;
                } else {
                    squareX = dx * dx;
                }
                dy = workspace.point[1] - value0;
                if (dy < 0) {
                    distance = MathSqrt(squareX +
                                        absDy * (value0 - workspace.point[1]));
                } else {
                    distance = MathSqrt(squareX + absDy * dy);
                }
                if ((nearestContact == NULL) || ((s32)distance < value4)) {
                    value4 = (s32)distance;
                    nearestContact = contact;
                }
                contact = contact->next;
            } while (contact != NULL);
        }
        contact = nearestContact;
        if (nearestContact == NULL) {
            SystemShowFatalError(D_8008CFE0);
        }
        wallPoint = contact->point0;
        workspace.point[0] =
            ((wallPoint->x + FAR_VAR(s32, gFarOffsetX)) * 4) - car->x;
        workspace.point[1] =
            ((wallPoint->y + FAR_VAR(s32, gFarOffsetY)) * 4) - car->y;
        headingDelta = contact->heading;
        asm volatile("" : "=r"(headingDelta) : "0"(headingDelta) : "memory");
        carHeading = car->heading;
        headingDelta -= carHeading;
        positiveDelta = headingDelta + 0x400;
        roundedHeadingDelta = positiveDelta;
        if (positiveDelta < 0) {
            roundedHeadingDelta = headingDelta + 0x7FF;
        }
        value0 = roundedHeadingDelta >> 0xA;
        roundedHeadingDelta = value0 << 0xA;
        value0 = positiveDelta - roundedHeadingDelta;
        if ((u32)(value0 - 0x101) < 0x1FFU) {
            if (value0 < 0x200) {
                value0 += 0x200;
            } else {
                value0 -= 0x200;
            }
        }
        angleDifference = value0;
        if (value0 >= 0x201) {
            projectedVelocity = 0x400;
            asm("" : "=r"(projectedVelocity) : "0"(projectedVelocity));
            angleDifference = projectedVelocity - value0;
        }
        carHeading = car->heading;
        asm("" : "=r"(carHeading) : "0"(carHeading));
        normalAngleSum = value0 + carHeading;
        roundedNormalAngle = normalAngleSum;
        if (normalAngleSum < 0) {
            roundedNormalAngle = normalAngleSum + 0x3FF;
        }
        value0 = roundedNormalAngle >> 0xA;
        roundedNormalAngle = value0 << 0xA;
        value0 = normalAngleSum - roundedNormalAngle;
        projectedVelocity = 0x400 - value0;
        value0 = projectedVelocity & 0x3FF;
        asm volatile("" : "=r"(value0) : "0"(value0) : "memory");
        if (angleDifference < 0x8C) {
            previousSpeed = car->speed;
            car->unk20E = 0;
            angleLoss = angleDifference << 17;
            speedQuarter = previousSpeed >> 4;
            angleLoss += speedQuarter;
            nextSpeed = previousSpeed - angleLoss;
            car->speed = nextSpeed;
            if (nextSpeed < 0) {
                car->speed = 0;
            }
            if ((car->frontRightContact == 0) || (car->rearRightContact == 0)) {
                value0 = value0 << 2;
                firstProjection = MathMultiplyFixed16(
                    *(s32 *)(value0 + (s32)gContactSinTable),
                    workspace.point[0] << 16);
                value0 += (s32)gContactCosTable;
                coefficient = *(s32 *)value0;
                shiftedPoint = workspace.point[1] << 16;
                value0 = firstProjection;
                secondProjection =
                    MathMultiplyFixed16(coefficient, shiftedPoint);
                shape = car->shape;
                value0 += secondProjection;
                value1 = value0 >> 16;
                shapeWidth = shape->halfWidth;
                roundedDistance = value1;
                if (value1 < 0) {
                    roundedDistance = value1 + 3;
                }
                value1 = shapeWidth + (roundedDistance >> 2);
                car->x -= MathMultiplyFixed16(car->axisXY, value1);
                car->y -= MathMultiplyFixed16(car->axisYY, value1);
                car->z -= MathMultiplyFixed16(car->axisZY, value1);
                corners = car->shape->corners;
                workspace.effect[0] = corners->x;
                workspace.effect[1] = corners->y;
                workspace.effect[2] = 0x4B;
                func_8001EEC4((s32 *)car);
                MatrixRotateVector(&workspace.effect[0]);
                workspace.effect[0] += car->x;
                workspace.effect[1] += car->y;
                workspace.effect[2] += car->z;
                value1 = workspace.effect[0] + RandomScaledGet(0x19);
                value0 = workspace.effect[1] + RandomScaledGet(0x19);
                func_8003644C(0, value1, value0,
                              workspace.effect[2] + RandomScaledGet(0x32));
                value1 = workspace.effect[0] + RandomScaledGet(0x19);
                value0 = workspace.effect[1] + RandomScaledGet(0x19);
                func_8003644C(1, value1, value0,
                              workspace.effect[2] + RandomScaledGet(0x32));
                if (car->lateralSpeed < -0x64) {
                    if (RandomScaledGet(8) < 0) {
                        rightFrontEffect = -RandomScaledGet(8);
                    } else {
                        rightFrontEffect = RandomScaledGet(8);
                    }
                    car->frontRightEffect = rightFrontEffect + 0xA;
                    if (RandomScaledGet(8) < 0) {
                        rightRearEffect = -RandomScaledGet(8);
                    } else {
                        rightRearEffect = RandomScaledGet(8);
                    }
                    car->rearRightEffect = rightRearEffect + 0xA;
                }
                car->lateralSpeed = 0;
                if (contact->flags & 2) {
                    normalHeading = contact->heading + 0x300;
                } else {
                    normalHeading = contact->heading + 0x100;
                }
                value1 = normalHeading & 0x3FF;
                asm volatile("" : "=r"(value1) : "0"(value1) : "memory");
                if (car->frontRightContact == 0) {
                    s32 impulseX;
                    register s32 normalCoefficient asm("$2");

                    reverseHeading = (0x400 - value1) & 0x3FF;
                    cosTable = gContactCosTable;
                    sinTable = gContactSinTable;
                    /* Keep the projected-velocity loads in retail order. */
                    normalImpulse =
                        *(volatile s32 *)(cosTable + reverseHeading);
                    normalAddress = *(volatile s32 *)&car->velocityX;
                    normalImpulse *= normalAddress;
                    normalAddress =
                        *(volatile s32 *)(sinTable + reverseHeading);
                    projectedVelocity = *(volatile s32 *)&car->velocityY;
                    normalAddress *= projectedVelocity;
                    projectedVelocity = (normalImpulse - normalAddress) >> 16;
                    projectedVelocity = -projectedVelocity;
                    normalAddress = projectedVelocity << 1;
                    normalImpulse = normalAddress + projectedVelocity;
                    normalAddress = value1 << 2;
                    if (normalImpulse < 0) {
                        normalImpulse += 3;
                    }
                    normalCoefficient = normalAddress + (s32)cosTable;
                    asm("" : "=r"(normalCoefficient) : "0"(normalCoefficient));
                    normalCoefficient = *(volatile s32 *)normalCoefficient;
                    impulse = normalImpulse >> 2;
                    impulseX = normalCoefficient * impulse;
                    normalAddress += (s32)sinTable;
                    car->frontVelocityX += impulseX;
                    car->frontVelocityY += *(s32 *)normalAddress * impulse;
                    if (impulse >= 0xB0) {
                        if (RandomScaledGet((0x1F4 - impulse) / 100) == 0) {
                            func_800432C0(car, 0);
                        }
                    }
                    if (impulse >= 0x65) {
                        func_800432C0(car, 5);
                    }
                    if (impulse >= 0x33) {
                        func_80043B68(car, 0);
                    }
                }
                if (car->rearRightContact == 0) {
                    s32 impulseX;
                    register s32 normalCoefficient asm("$2");

                    reverseHeading2 = 0x400;
                    asm volatile(""
                                 : "=r"(reverseHeading2)
                                 : "0"(reverseHeading2)
                                 : "memory");
                    reverseHeading2 = (reverseHeading2 - value1) & 0x3FF;
                    cosTable = gContactCosTable;
                    sinTable = gContactSinTable;
                    normalImpulse2 =
                        *(volatile s32 *)(cosTable + reverseHeading2);
                    normalAddress = *(volatile s32 *)&car->velocityX;
                    normalImpulse2 *= normalAddress;
                    normalAddress =
                        *(volatile s32 *)(sinTable + reverseHeading2);
                    projectedVelocity = *(volatile s32 *)&car->velocityY;
                    normalAddress *= projectedVelocity;
                    projectedVelocity = (normalImpulse2 - normalAddress) >> 16;
                    projectedVelocity = -projectedVelocity;
                    normalAddress = projectedVelocity << 1;
                    normalImpulse2 = normalAddress + projectedVelocity;
                    normalAddress = value1 << 2;
                    if (normalImpulse2 < 0) {
                        normalImpulse2 += 3;
                    }
                    normalCoefficient = normalAddress + (s32)cosTable;
                    asm("" : "=r"(normalCoefficient) : "0"(normalCoefficient));
                    normalCoefficient = *(volatile s32 *)normalCoefficient;
                    impulse = normalImpulse2 >> 2;
                    impulseX = normalCoefficient * impulse;
                    normalAddress += (s32)sinTable;
                    car->rearVelocityX += impulseX;
                    car->rearVelocityY += *(s32 *)normalAddress * impulse;
                    if (impulse >= 0xB0) {
                        if (RandomScaledGet((0x1F4 - impulse) / 100) == 0) {
                            func_800432C0(car, 2);
                        }
                    }
                    if (impulse >= 0x79) {
                        func_800432C0(car, 7);
                    }
                    if (impulse >= 0x33) {
                        callbackCar = car;
                        asm("" : "=r"(callbackCar) : "0"(callbackCar));
                        effectWheel = 2;
                        goto sideEffect;
                    }
                }
            } else if ((car->frontLeftContact == 0) ||
                       (car->rearLeftContact == 0)) {
                value0 = value0 << 2;
                firstProjection = MathMultiplyFixed16(
                    *(s32 *)(value0 + (s32)gContactSinTable),
                    workspace.point[0] << 16);
                value0 += (s32)gContactCosTable;
                coefficient = *(s32 *)value0;
                shiftedPoint = workspace.point[1] << 16;
                value0 = firstProjection;
                secondProjection =
                    MathMultiplyFixed16(coefficient, shiftedPoint);
                shape = car->shape;
                value0 += secondProjection;
                value1 = value0 >> 16;
                shapeWidth = shape->halfWidth;
                roundedDistance2 = value1;
                if (value1 < 0) {
                    roundedDistance2 = value1 + 3;
                }
                value1 = shapeWidth + (roundedDistance2 >> 2);
                car->x += MathMultiplyFixed16(car->axisXY, value1);
                car->y += MathMultiplyFixed16(car->axisYY, value1);
                car->z += MathMultiplyFixed16(car->axisZY, value1);
                if (car->lateralSpeed >= 0x65) {
                    if (RandomScaledGet(8) < 0) {
                        leftFrontEffect = -RandomScaledGet(8);
                    } else {
                        leftFrontEffect = RandomScaledGet(8);
                    }
                    car->frontLeftEffect = leftFrontEffect + 0xA;
                    if (RandomScaledGet(8) < 0) {
                        leftRearEffect = -RandomScaledGet(8);
                    } else {
                        leftRearEffect = RandomScaledGet(8);
                    }
                    car->rearLeftEffect = leftRearEffect + 0xA;
                }
                car->lateralSpeed = 0;
                corners2 = car->shape->corners;
                workspace.effect[0] = corners2[1].x;
                workspace.effect[1] = corners2[1].y;
                workspace.effect[2] = 0x4B;
                func_8001EEC4((s32 *)car);
                MatrixRotateVector(&workspace.effect[0]);
                workspace.effect[0] += car->x;
                workspace.effect[1] += car->y;
                workspace.effect[2] += car->z;
                value1 = workspace.effect[0] + RandomScaledGet(0x19);
                value0 = workspace.effect[1] + RandomScaledGet(0x19);
                func_8003644C(0, value1, value0,
                              workspace.effect[2] + RandomScaledGet(0x32));
                value1 = workspace.effect[0] + RandomScaledGet(0x19);
                value0 = workspace.effect[1] + RandomScaledGet(0x19);
                func_8003644C(1, value1, value0,
                              workspace.effect[2] + RandomScaledGet(0x32));
                if (contact->flags & 2) {
                    normalHeading2 = contact->heading + 0x300;
                } else {
                    normalHeading2 = contact->heading + 0x100;
                }
                value1 = normalHeading2 & 0x3FF;
                asm volatile("" : "=r"(value1) : "0"(value1) : "memory");
                if (car->frontLeftContact == 0) {
                    s32 impulseX;
                    register s32 normalCoefficient asm("$2");

                    reverseHeading3 = (0x400 - value1) & 0x3FF;
                    cosTable = gContactCosTable;
                    sinTable = gContactSinTable;
                    normalImpulse3 =
                        *(volatile s32 *)(cosTable + reverseHeading3);
                    normalAddress = *(volatile s32 *)&car->velocityX;
                    normalImpulse3 *= normalAddress;
                    normalAddress =
                        *(volatile s32 *)(sinTable + reverseHeading3);
                    projectedVelocity = *(volatile s32 *)&car->velocityY;
                    normalAddress *= projectedVelocity;
                    projectedVelocity = (normalImpulse3 - normalAddress) >> 16;
                    projectedVelocity = -projectedVelocity;
                    normalAddress = projectedVelocity << 1;
                    normalImpulse3 = normalAddress + projectedVelocity;
                    normalAddress = value1 << 2;
                    if (normalImpulse3 < 0) {
                        normalImpulse3 += 3;
                    }
                    normalCoefficient = normalAddress + (s32)cosTable;
                    asm("" : "=r"(normalCoefficient) : "0"(normalCoefficient));
                    normalCoefficient = *(volatile s32 *)normalCoefficient;
                    impulse = normalImpulse3 >> 2;
                    impulseX = normalCoefficient * impulse;
                    normalAddress += (s32)sinTable;
                    car->frontVelocityX += impulseX;
                    car->frontVelocityY += *(s32 *)normalAddress * impulse;
                    if (impulse >= 0xB0) {
                        if (RandomScaledGet((0x1F4 - impulse) / 100) == 0) {
                            func_800432C0(car, 1);
                        }
                    }
                    if (impulse >= 0x65) {
                        func_800432C0(car, 6);
                    }
                    if (impulse >= 0x33) {
                        func_80043B68(car, 1);
                    }
                }
                if (car->rearLeftContact == 0) {
                    s32 impulseX;
                    register s32 normalCoefficient asm("$2");

                    reverseHeading4 = 0x400;
                    asm volatile(""
                                 : "=r"(reverseHeading4)
                                 : "0"(reverseHeading4)
                                 : "memory");
                    reverseHeading4 = (reverseHeading4 - value1) & 0x3FF;
                    cosTable = gContactCosTable;
                    sinTable = gContactSinTable;
                    normalImpulse4 =
                        *(volatile s32 *)(cosTable + reverseHeading4);
                    normalAddress = *(volatile s32 *)&car->velocityX;
                    normalImpulse4 *= normalAddress;
                    normalAddress =
                        *(volatile s32 *)(sinTable + reverseHeading4);
                    projectedVelocity = *(volatile s32 *)&car->velocityY;
                    normalAddress *= projectedVelocity;
                    projectedVelocity = (normalImpulse4 - normalAddress) >> 16;
                    projectedVelocity = -projectedVelocity;
                    normalAddress = projectedVelocity << 1;
                    normalImpulse4 = normalAddress + projectedVelocity;
                    normalAddress = value1 << 2;
                    if (normalImpulse4 < 0) {
                        normalImpulse4 += 3;
                    }
                    normalCoefficient = normalAddress + (s32)cosTable;
                    asm("" : "=r"(normalCoefficient) : "0"(normalCoefficient));
                    normalCoefficient = *(volatile s32 *)normalCoefficient;
                    impulse = normalImpulse4 >> 2;
                    impulseX = normalCoefficient * impulse;
                    normalAddress += (s32)sinTable;
                    car->rearVelocityX += impulseX;
                    car->rearVelocityY += *(s32 *)normalAddress * impulse;
                    if (impulse >= 0xB0) {
                        if (RandomScaledGet((0x1F4 - impulse) / 100) == 0) {
                            func_800432C0(car, 3);
                        }
                    }
                    if (impulse >= 0x79) {
                        func_800432C0(car, 7);
                    }
                    if (impulse >= 0x33) {
                        callbackCar = car;
                        asm("" : "=r"(callbackCar) : "0"(callbackCar));
                        effectWheel = 3;
                    sideEffect:
                        func_80043B68(callbackCar, effectWheel);
                    }
                }
            }
            value5 = car->x;
            value4 = car->y;
            regionHome = &car->regionIndex;
            asm("" : "=r"(regionHome) : "0"(regionHome));
            car->collisionPending = 0;
            regionCount = D_800A2E08;
            roundedX = value5;
            if (value5 < 0) {
                roundedX = value5 + 3;
            }
            value5 = roundedX >> 2;
            roundedY = value4;
            if (value4 < 0) {
                roundedY = value4 + 3;
            }
            value1 = car->regionIndex;
            value4 = roundedY >> 2;
            if (value1 == -1) {
                value1 = 0;
            }
            remainingRegions = regionCount;
            regionBase = (ContactRegion *)D_800A3838;
            rowOffset = value1 << 4;
            asm("" : "=r"(rowOffset) : "0"(rowOffset));
            region = (ContactRegion *)((s32)regionBase + rowOffset);
            if (remainingRegions > 0) {
            findRegion:
                if (value1 >= regionCount) {
                    value1 = 0;
                    region = ((ContactRegion *)D_800A3838);
                }
                if ((value5 >= (s32)region->minX) &&
                    ((s32)region->maxX >= value5) &&
                    (value4 >= (s32)region->minY) &&
                    ((s32)region->maxY >= value4) &&
                    (func_800246C0(value5, value4, (u8 *)region) & 0xFF)) {
                    *regionHome = value1;
                    if (value1 == regionCount) {
                        value1 = 0;
                    }
                    regionResult = value1;
                } else {
                    remainingRegions -= 1;
                    value1 += 1;
                    region++;
                    if (remainingRegions <= 0) {
                        goto noRegion;
                    }
                    goto findRegion;
                }
            } else {
            noRegion:
                *regionHome = -1;
                regionResult = -1;
            }
            if (regionResult == -1) {
                return 0;
            }
            nextCallback = func_80025720;
            car->unk102 = 0;
            if (((car->unk1EC != 1) || (nextCallback != func_80025730)) &&
                (car->callback != func_80025730) && (car->mode != 4)) {
                car->callback = nextCallback;
            }
            speedLimit = car->speed;
            if (speedLimit < (impulse << 0x10)) {
                impulse = speedLimit >> 0x10;
            }
            heading = car->heading;
            forwardCosEntry = (s32 *)((heading << 2) + (s32)gContactCosTable);
            asm("" : "=r"(forwardCosEntry) : "0"(forwardCosEntry));
            sinSubtract = gContactSinTable;
            forwardSinEntry = (s32 *)((heading << 2) + (s32)sinSubtract);
            asm("" : "=r"(forwardSinEntry) : "0"(forwardSinEntry));
            car->frontVelocityX -= *forwardCosEntry * impulse;
            car->frontVelocityY -= *forwardSinEntry * impulse;
            car->rearVelocityX -= *forwardCosEntry * impulse;
            car->rearVelocityY -= *forwardSinEntry * impulse;
            goto done;
        }
        if ((car->frontRightContact == 0) || (car->frontLeftContact == 0)) {
            value0 = value0 << 2;
            firstProjection =
                MathMultiplyFixed16(*(s32 *)(value0 + (s32)gContactSinTable),
                                    workspace.point[0] << 16);
            value0 += (s32)gContactCosTable;
            coefficient = *(s32 *)value0;
            shiftedPoint = workspace.point[1] << 16;
            value0 = firstProjection;
            secondProjection = MathMultiplyFixed16(coefficient, shiftedPoint);
            shape = car->shape;
            value0 += secondProjection;
            value1 = value0 >> 16;
            basisValue = car->axisXX;
            shapeExtent = shape->frontExtent;
            value0 = (u32)value0 >> 31;
            value0 = value1 + value0;
            value0 >>= 1;
            value1 = shapeExtent - value0;
            car->x += MathMultiplyFixed16(basisValue, value1);
            car->y += MathMultiplyFixed16(car->axisYX, value1);
            car->z += MathMultiplyFixed16(car->axisZX, value1);
            if (contact->flags & 2) {
                normalHeading3 = contact->heading + 0x300;
            } else {
                normalHeading3 = contact->heading + 0x100;
            }
            value1 = normalHeading3 & 0x3FF;
            asm volatile("" : "=r"(value1) : "0"(value1) : "memory");
            reverseHeading5 = 0x400;
            asm volatile(""
                         : "=r"(reverseHeading5)
                         : "0"(reverseHeading5)
                         : "memory");
            reverseHeading5 = (reverseHeading5 - value1) & 0x3FF;
            cosTable = gContactCosTable;
            sinTable = gContactSinTable;
            normalImpulse = *(volatile s32 *)(cosTable + reverseHeading5);
            normalAddress = *(volatile s32 *)&car->velocityX;
            normalImpulse *= normalAddress;
            normalAddress = *(volatile s32 *)(sinTable + reverseHeading5);
            projectedVelocity = *(volatile s32 *)&car->velocityY;
            normalAddress *= projectedVelocity;
            projectedVelocity = (normalImpulse - normalAddress) >> 16;
            projectedVelocity = -projectedVelocity;
            normalAddress = projectedVelocity << 1;
            impactSpeed = normalAddress + projectedVelocity;
            if (impactSpeed < 0) {
                impactSpeed += 3;
            }
            impactSpeed >>= 2;
            projectedVelocity = impactSpeed << 1;
            impactSpeed = projectedVelocity + impactSpeed;
            if (impactSpeed < 0) {
                impactSpeed += 3;
            }
            impulse = impactSpeed >> 2;
            if (car->frontRightContact == 0) {
                normalAddress = value1 << 2;
                frontCoefficient = normalAddress + (s32)cosTable;
                asm("" : "=r"(frontCoefficient) : "0"(frontCoefficient));
                frontCoefficient = *(volatile s32 *)frontCoefficient;
                car->frontVelocityX += frontCoefficient * impulse;
                car->frontVelocityY +=
                    *(s32 *)(normalAddress + (s32)sinTable) * impulse;
            }
            if (car->frontLeftContact == 0) {
                car->frontVelocityX += gContactCosTable[value1] * impulse;
                car->frontVelocityY += gContactSinTable[value1] * impulse;
            }
            frontCoefficient = (s32)gContactCosTable;
            normalAddress = value1 << 2;
            frontCoefficient = normalAddress + frontCoefficient;
            frontCoefficient = *(volatile s32 *)frontCoefficient;
            impulseX = frontCoefficient * impulse;
            sinSubtract = gContactSinTable;
            normalAddress += (s32)sinSubtract;
            car->rearVelocityX += impulseX;
            car->rearVelocityY += *(s32 *)normalAddress * impulse;
            impulse = ((s16 *)&car->speed)[1];
            if (impulse >= 0x173) {
                nextCallback = func_80025730;
                if (car->unk1EC != 1 && car->callback != nextCallback &&
                    car->mode != 4) {
                    car->callback = nextCallback;
                }
            }
            if (car->frontRightContact == 0) {
                if (impulse >= 0xC9) {
                    if (RandomScaledGet((0x1F4 - impulse) / 50) == 0) {
                        func_800432C0(car, 0);
                    }
                    func_800432C0(car, 5);
                }
                if (impulse >= 0x65) {
                    func_80043B68(car, 0);
                }
            }
            if (car->frontLeftContact == 0) {
                if (impulse >= 0xC9) {
                    if (RandomScaledGet((0x1F4 - impulse) / 50) == 0) {
                        func_800432C0(car, 1);
                    }
                    func_800432C0(car, 6);
                    asm("" : "=r"(impulse) : "0"(impulse));
                    lightImpact = impulse < 0x65;
                } else {
                    lightImpact = impulse < 0x65;
                }
                if (lightImpact == 0) {
                    callbackCar = car;
                    asm("" : "=r"(callbackCar) : "0"(callbackCar));
                    effectWheel2 = 1;
                    goto longitudinalEffect;
                }
            }
        } else if ((car->rearRightContact == 0) ||
                   (car->rearLeftContact == 0)) {
            value0 = value0 << 2;
            firstProjection =
                MathMultiplyFixed16(*(s32 *)(value0 + (s32)gContactSinTable),
                                    workspace.point[0] << 16);
            value0 += (s32)gContactCosTable;
            coefficient = *(s32 *)value0;
            shiftedPoint = workspace.point[1] << 16;
            value0 = firstProjection;
            secondProjection = MathMultiplyFixed16(coefficient, shiftedPoint);
            shape = car->shape;
            value0 += secondProjection;
            value1 = value0 >> 16;
            basisValue = car->axisXX;
            shapeExtent = shape->rearExtent;
            value0 = (u32)value0 >> 31;
            value0 = value1 + value0;
            value0 >>= 1;
            value1 = shapeExtent + value0;
            car->x += MathMultiplyFixed16(basisValue, value1);
            car->y += MathMultiplyFixed16(car->axisYX, value1);
            car->z += MathMultiplyFixed16(car->axisZX, value1);
            if (contact->flags & 2) {
                normalHeading4 = contact->heading + 0x300;
            } else {
                normalHeading4 = contact->heading + 0x100;
            }
            value1 = normalHeading4 & 0x3FF;
            asm volatile("" : "=r"(value1) : "0"(value1) : "memory");
            reverseHeading6 = 0x400;
            asm volatile(""
                         : "=r"(reverseHeading6)
                         : "0"(reverseHeading6)
                         : "memory");
            reverseHeading6 = (reverseHeading6 - value1) & 0x3FF;
            rearCosTable = gContactCosTable;
            rearSinTable = gContactSinTable;
            normalImpulse5 = *(volatile s32 *)(rearCosTable + reverseHeading6);
            normalAddress = *(volatile s32 *)&car->velocityX;
            normalImpulse5 *= normalAddress;
            normalAddress = *(volatile s32 *)(rearSinTable + reverseHeading6);
            projectedVelocity = *(volatile s32 *)&car->velocityY;
            normalAddress *= projectedVelocity;
            projectedVelocity = (normalImpulse5 - normalAddress) >> 16;
            projectedVelocity = -projectedVelocity;
            normalAddress = projectedVelocity << 1;
            normalImpulse5 = normalAddress + projectedVelocity;
            rearNormalAddress = value1 << 2;
            if (normalImpulse5 < 0) {
                normalImpulse5 += 3;
            }
            normalCosEntry = (s32 *)(rearNormalAddress + (s32)rearCosTable);
            asm("" : "=r"(normalCosEntry) : "0"(normalCosEntry));
            impulse = normalImpulse5 >> 2;
            normalSinEntry = (s32 *)(rearNormalAddress + (s32)rearSinTable);
            car->rearVelocityX += *normalCosEntry * impulse;
            car->rearVelocityY += *normalSinEntry * impulse;
            car->frontVelocityX += (s32)(*normalCosEntry * impulse) / 2;
            halfProduct = *normalSinEntry * impulse;
            tailSpeed = car->speed;
            value0 = tailSpeed >> 0x14;
            yVelocity = car->frontVelocityY;
            halfSign = (u32)halfProduct >> 31;
            halfProduct = (halfProduct + halfSign) >> 1;
            yVelocity += halfProduct;
            car->frontVelocityY = yVelocity;
            if (RandomScaledGet(5) < 0) {
                effectValue = value0 - RandomScaledGet(5);
            } else {
                effectValue = value0 + RandomScaledGet(5);
            }
            car->rearLeftEffect = effectValue;
            tailSpeed2 = car->speed;
            value0 = tailSpeed2 >> 0x14;
            if (RandomScaledGet(5) < 0) {
                effectValue2 = value0 - RandomScaledGet(5);
            } else {
                effectValue2 = value0 + RandomScaledGet(5);
            }
            car->rearRightEffect = effectValue2;
            if (car->rearRightContact == 0) {
                value1 = impulse < 0xC9;
                value0 = impulse < 0x65;
                if (value1 == 0) {
                    func_800432C0(car, 2);
                    func_800432C0(car, 7);
                    asm("" : "=r"(impulse) : "0"(impulse));
                    value0 = impulse < 0x65;
                }
                if (value0 == 0) {
                    callbackCar = car;
                    asm(""
                        : "=r"(callbackCar), "=r"(value0)
                        : "0"(callbackCar), "1"(value0));
                    func_80043B68(callbackCar, 0);
                }
                /* Retail checks the rear-right contact again here. */
                if (car->rearRightContact == 0) {
                    if (value1 == 0) {
                        func_800432C0(car, 3);
                        func_800432C0(car, 7);
                    }
                    if (value0 == 0) {
                        callbackCar = car;
                        asm("" : "=r"(callbackCar) : "0"(callbackCar));
                        effectWheel2 = 3;
                    longitudinalEffect:
                        func_80043B68(callbackCar, effectWheel2);
                    }
                }
            }
        }
        car->collisionPending = 0;
    done:
        asm volatile("" : : "r"(impulse));
        return 1;
    }
}

s32 MathGetAngleDelta(s32 arg0, s32 arg1) {
    s32 value0;

    value0 = arg0 - arg1;
    if (value0 >= 0) {
        if (value0 < 0x201) {

        } else {
            goto block_4;
        }
    } else if (-value0 >= 0x201) {
    block_4:
        if (value0 < 0) {
            value0 += 0x400;
        } else {
            value0 -= 0x400;
        }
    }
    return value0;
}

extern s32 D_800980A4[];
extern s32 D_80098134[];
extern u8 D_80098194[];
extern u8 D_800981E4[];

void func_80028754(u8 *arg0, s32 arg1) {
    extern s8 D_800A2E18;
    u8 *dst;
    s32 i;
    s32 scale;
    s32 offset;
    s32 *cur;
    s32 *table;
    u16 *arr1E4;
    u16 *arr194;
    s32 *src;
    s32 count;
    s32 limit;
    s32 flag;
    u16 v;
    s32 pad[4];

    flag = D_800A2EB8[0];
    table = D_800980A4;
    *(s16 *)(arg0 + 0x10E) = arg1;
    if (flag == 0) {
        D_800A2E18 = 4;
        table = D_80098134;
    }
    if (*(s16 *)(arg0 + 0x1EC) != 0) {
        if (D_800A2E18 > 0) {
            i = 0;
            count = D_800A2E18;
            src = table;
        loop1:
            *(s32 *)(arg0 + 0x124) = src[0];
            *(s32 *)(arg0 + 0x128) = src[1];
            *(s32 *)(arg0 + 0x12C) = src[2];
            *(s32 *)(arg0 + 0x130) = src[3];
            *(s32 *)(arg0 + 0x134) = src[4];
            *(s32 *)(arg0 + 0x138) = src[5];
            src += 6;
            arg0 += 0x18;
            i++;
            if (i < count) {
                goto loop1;
            }
        }
    } else if (D_800A2E18 > 0) {
        i = 0;
        cur = table;
        dst = arg0;
        offset = 0;
        arr194 = (u16 *)&D_80098194[arg1 * 8];
        arr1E4 = (u16 *)&D_800981E4[arg1 * 8];
    loop2:
        if (D_800A2EB8[0] == 0) {
            v = *arr1E4;
        } else {
            scale = *arr194;
            v = scale;
        }
        scale = MathFixedDivide(v, 0x3E8);
        do {
        } while (0);
        *(s32 *)(dst + 0x124) =
            MathMultiplyFixed16(MathFixedDivide(D_800A2E78[0], 0x4D), scale);
        if (i > 0) {
            *(s32 *)(dst + 0x128) = *(s32 *)(offset + (s32)table + 4) -
                                    (*(s32 *)(offset + (s32)table - 0x10) -
                                     *(s32 *)(offset + (s32)table - 0x14)) /
                                        5;
        } else {
            *(s32 *)(dst + 0x128) = *(s32 *)(offset + (s32)table + 4);
        }
        *(s32 *)(dst + 0x12C) = cur[2];
        *(s32 *)(dst + 0x130) = cur[3];
        *(s32 *)(dst + 0x134) = 0x32C8;
        MathMultiplyFixed16(0x17700000, scale);
        offset += 0x18;
        arr194++;
        arr1E4++;
        cur += 6;
        limit = D_800A2E18;
        *(s32 *)(dst + 0x138) = i;
        dst += 0x18;
        i++;
        if (i < limit) {
            goto loop2;
        }
    }
    (void)&pad;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80028980);

void func_80028D80(u8 *arg0) {
    u8 *node;
    extern void *D_800A3990;
    extern s8 D_800A2E18;
    extern u8 D_800A2EE4nm[] asm("D_800A2EE4.NON_MATCHING");
    s16 mode;
    s32 idx;
    u8 *base;
    u8 *row;
    s32 scale;
    s32 cur;
    s32 lim;
    s32 temp;
    s32 v1;
    s32 v7;

    node = arg0;
    mode = *(s16 *)(node + 0x1EC);
    if (mode == 0) {
        if (*(s32 *)(node + 0x28C) <= 0 ||
            (*(u16 *)(node + 0x3A4) & 0x1000) != 0) {
            *(s32 *)(node + 0x88) = 0;
            return;
        }
    } else if (mode == 1 && *(s32 *)(node + 0x290) <= 0) {
        *(s32 *)(node + 0x88) = 0;
        if (*(s16 *)(node + 0x1EC) == mode &&
            *(s32 *)(node + 0x90) <= 0x63FFFF) {
            *(s32 *)(node + 0x88) = MathFixedDivide(1, 0xA);
        }
        return;
    }
    idx = *(s16 *)(node + 0x10C);
    base = node + 0x124;
    D_800A3990 = base;
    row = (u8 *)(idx * 0x18 + (s32)base);
    scale = *(s32 *)row;
    if (*(u8 *)(node + 0xF6) == 0) {
        cur = *(s32 *)(node + 0x90);
        lim = *(s32 *)(row + 4);
        if (cur < lim) {
            if ((lim >> 16) != 0) {
                scale = MathMultiplyFixed16(
                    scale, MathFixedDivide((cur >> 16) + 0x50, lim >> 16));
            }
        } else {
            v1 = *(s32 *)(row + 8);
            if (v1 < cur) {
                scale = MathMultiplyFixed16(
                    scale, MathFixedDivide(0x10, ((cur - v1) >> 16) + 0x10));
            } else {
                scale = scale + MathFixedDivide(1, 6);
            }
        }
    } else {
        v1 = *(s32 *)(base + (s32)D_800A2E18 * 0x18 - 0x10);
        cur = *(s32 *)(node + 0x90);
        if (v1 < cur) {
            scale = MathMultiplyFixed16(
                scale, MathFixedDivide(0x10, ((cur - v1) >> 16) + 0x10));
        }
    }
    if (D_800A2EE4nm[0] != 0) {
        if (*(s16 *)(node + 0x1EC) == 0) {
            scale = MathMultiplyFixed16(
                scale, MathFixedDivide(
                           (*(s8 *)(node + 0x205) - 1) * 0x64 + 0x64, 0x64));
        }
    }
    v7 = scale * 8;
    v7 = v7 - scale;
    scale = v7 >> 2;
    *(s32 *)(node + 0x88) = scale + (*(s32 *)(node + 0x22C) >> 4);
    *(s32 *)(node + 0x90) =
        *(s32 *)(node + 0x90) + (scale + (*(s32 *)(node + 0x22C) >> 4));
}

typedef struct {
    u8 unk0[0x90];
    s32 unk90;
} UnkObject90;
void func_80028F98(UnkObject90 *object) {
    object->unk90 -= 0x40000;
}

extern void func_80028980(void *);
void func_80028FAC(void *object) {
    func_80028980(object);
}

void func_80028D80(u8 *);

void func_80028FCC(u8 *arg0) {
    s32 x84;

    if (arg0 != 0) {
        do {
            *(s32 *)(arg0 + 0x94) = *(s32 *)(arg0 + 0x90);
            x84 = *(s32 *)(arg0 + 0x84);
            if (*(s32 *)(arg0 + 0x90) < x84) {
                func_80028D80(arg0);
                if (x84 < *(s32 *)(arg0 + 0x90)) {
                    *(s32 *)(arg0 + 0x90) = x84;
                }
            } else {
                if (x84 < *(s32 *)(arg0 + 0x90)) {
                    *(s32 *)(arg0 + 0x90) = *(s32 *)(arg0 + 0x90) - 0x40000;
                }
            }
            func_80028980(arg0);
            arg0 = *(u8 **)(arg0 + 0x3E0);
        } while (arg0 != 0);
    }
}

extern u8 D_800A2E18;
typedef struct {
    u8 pad0[0xF6];
    u8 state;
    u8 padF7[0x15];
    u16 count;
} Counter;
void SelectionStepForward(Counter *selection) {
    u16 newIndex;
    if (selection->state == 0) {
        newIndex = selection->count + 1;
        selection->count = newIndex;
        if ((s16)newIndex >= (s8)D_800A2E18) {
            selection->count = (u16)((s8)D_800A2E18 - 1);
        }
        func_80028980(selection);
    }
}

typedef struct SelectionState {
    u8 pad0[0xF6];
    u8 unkF6;
    u8 padF7[0x11];
    s16 selectedValue;
    u8 pad10A[2];
    s16 selectionIndex;
} SelectionState;

void SelectionStepBackward(SelectionState *selection) {
    u16 newIndex;
    s32 index;
    s32 value;
    s32 *record;

    if (selection->unkF6 == 0) {
        newIndex = selection->selectionIndex - 1;
        selection->selectionIndex = newIndex;
        if ((s16)newIndex < 0)
            selection->selectionIndex = 0;
        func_80028980(selection);
        index = selection->selectionIndex;
        record = (s32 *)selection;
        record += index * 6;
        value = record[0x130 / 4];
        selection->selectedValue = value;
    }
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80029150);

extern void func_80029150(s32 *);
void func_80029450(s32 *p) {
    func_80029150(p);
    p[0] += p[0xB0 / 4];
    p[1] += p[0xB4 / 4];
    p[2] += p[0xB8 / 4];
}

void func_800294A8(void *arg0) {
    extern s32 D_800A2EC0Lui asm("D_800A2EC0Absolute");
    extern s32 D_800A2E28;
    extern void func_800409A0(u8 * object);
    extern void func_80040AC0(u8 * object);
    extern void func_800524A0(u8 * arg0, s8 arg1);
    extern void func_800525A8(u8 * arg0, s8 arg1);
    extern void func_80029994(u8 * arg0, s32 arg1);
    volatile s32 pad[8];
    s32 delta;
    s32 value;
    s32 i;
    s32 shade;
    s32 shade2;
    u8 *car = arg0;

    delta = (*(s16 *)(car + 0x104) - *(s16 *)(car + 0x114) + 0x400) & 0x3FF;
    if (delta >= 0x201) {
        delta = (0x400 - delta) & 0x3FF;
    }
    func_8001EC38((s32 *)car);
    if (delta >= 0) {
        if (delta >= 0x1A) {
            goto Far;
        }
        goto Checks;
    }
    if (-delta < 0x1A) {
        goto Checks;
    }
Far:
    if (*(s32 *)(car + 0x90) > 0x320000) {
        goto Visible;
    }
Checks:
    if ((*(s16 *)(car + 0x120) == 0 && *(u8 *)(car + 0xF9) == 0) ||
        D_800A2EACAbsolute[0] != 0) {
        goto Other;
    }
Visible:
    if (*(u8 *)(car + 0xF9) == 0) {
        if (RandomScaledGet(4) < 0) {
            value = -RandomScaledGet(4);
        } else {
            value = RandomScaledGet(4);
        }
        func_80029994(car, value);
        if (RandomScaledGet(4) < 0) {
            value = -RandomScaledGet(4);
        } else {
            value = RandomScaledGet(4);
        }
        func_80029994(car, value);
    }
    func_800409A0(car);
    for (i = 0, shade = 0; i < 4; shade += 0x1000000, i++) {
        if (*(s16 *)(car + i * 0x28 + 0x2AC) == 0 &&
            *(s8 *)(car + i + 0x3A6) != 0) {
            func_800525A8(car, shade >> 24);
            if (D_800A2EC0Lui - D_800A2E28 >= 0x191) {
                func_80041848(car, 0x57);
            }
            D_800A2E28 = D_800A2EC0Lui;
        } else if (*(u8 *)(car + i * 0x28 + 0x2CC) != 0) {
            func_800524A0(car, shade >> 24);
        }
    }
    return;
Other:
    if (*(s16 *)(car + 0x1C4) > 0) {
        *(s16 *)(car + 0x1C4) = 0;
        if (*(s8 *)(car + 0x3B8) >= 0xB) {
            *(u8 *)(car + 0x3B8) = 5;
        }
        func_800409A0(car);
        for (i = 0, shade2 = 0; i < 4; shade2 += 0x1000000, i++) {
            if (*(s16 *)(car + i * 0x28 + 0x2AC) == 0 &&
                *(s8 *)(car + i + 0x3A6) != 0) {
                func_800525A8(car, shade2 >> 24);
                if (D_800A2EC0Lui - D_800A2E28 >= 0x191) {
                    func_80041848(car, 0x57);
                }
                D_800A2E28 = D_800A2EC0Lui;
            } else if (*(u8 *)(car + i * 0x28 + 0x2CC) != 0) {
                func_800524A0(car, shade2 >> 24);
            }
        }
        return;
    }
    func_80040AC0(car);
    for (i = 0; i < 4; i++) {
        if (*(u8 *)(car + i * 0x28 + 0x2CC) != 0) {
            func_800524A0(car, i);
        }
    }
}

void func_800297D0(u8 *arg0) {
    extern void func_80031264(void);
    extern void func_800294A8(void *);
    extern s32 CarHandleWallCollision(void *);
    extern s32 D_800A2EC8NM[] asm("D_800A2EC8.NON_MATCHING");

    func_80031264();
    *(u8 *)(arg0 + 0x375) = 1;
    func_800294A8(arg0);
    if (D_800A2EB0Absolute[0] <= 0) {
        if (func_80025A38(arg0) != 0) {
            *(s16 *)(arg0 + 0x1E0) = func_8002482C(
                *(s32 *)(arg0 + 0), *(s32 *)(arg0 + 4), (s32 *)(arg0 + 0x1F8));
        }
    }
    if (*(u8 *)(arg0 + 0xF5) != 0 || *(s16 *)(arg0 + 0x1E0) == -1) {
        func_800414E0(arg0, 7, 8);
        if (*(s32 *)(arg0 + 0x354) == (s32)func_80025730 &&
            D_800A2EC8NM[0] == 0) {
            *(s32 *)(arg0 + 0) = *(s32 *)(arg0 + 0xC);
            *(s32 *)(arg0 + 4) = *(s32 *)(arg0 + 0x10);
            *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 0x14);
            *(s32 *)(arg0 + 0x90) = *(s32 *)(arg0 + 0x90) / 2;
            *(u16 *)(arg0 + 0x104) = (*(u16 *)(arg0 + 0x104) + 0x200) & 0x3FF;
        }
        CarHandleWallCollision(arg0);
        *(u8 *)(arg0 + 0xF5) = 0;
        *(u8 *)(arg0 + 0x375) = 0;
    }
}

void func_800298E0(s32 *car) {
    s32 index;

    index = ((s16 *)car)[0x8A];
    car[0x31] =
        MathMultiplyFixed16((*(s32 **)D_800A3A2CAbsolute)[index], car[0x24]);
    car[0x32] =
        MathMultiplyFixed16((*(s32 **)D_800A3A34Absolute)[index], car[0x24]);
    car[0x34] =
        MathMultiplyFixed16((*(s32 **)D_800A3A2CAbsolute2)[index], car[0x24]);
    car[0x35] =
        MathMultiplyFixed16((*(s32 **)D_800A3A34Absolute2)[index], car[0x24]);
}

void func_80029994(u8 *arg0, s32 arg1) {
    s32 pos[3];
    s32 x;
    u8 *entry;

    if (*(u8 *)(arg0 + 0xF4) != 0) {
        entry = (u8 *)(*(s32 *)(*(s32 *)(arg0 + 0x370) + 0x40) + arg1 * 0x18);
        pos[0] = *(s32 *)(entry + 4);
        pos[1] = *(s32 *)(entry + 8);
        pos[2] = *(s32 *)(entry + 0xC);
        func_8001EEC4((s32 *)arg0);
        MatrixRotateVector(pos);
        pos[0] += *(s32 *)(arg0 + 0);
        pos[1] += *(s32 *)(arg0 + 4);
        pos[2] += *(s32 *)(arg0 + 8);
        x = pos[0] + RandomScaledGet(25);
        func_8003644C(1, x, pos[1] + RandomScaledGet(25), pos[2]);
    }
}

extern void func_8001FAC0(u8 *, s32);
extern s32 D_800A2E1C;

void func_80029A78(u8 *car) {
    s32 angle;
    s32 dist10;
    s32 value;
    s32 scale;
    s32 vx;
    s32 vy;

    *(u16 *)(car + 0x104) = *(u16 *)(car + 0x114);
    func_8001F2C4(*(s16 *)(car + 0x114), 0, 0);
    func_8001F874((s32 *)car);
    if (*(u8 *)(car + 0x410) != 0) {
        *(u16 *)(car + 0x20E) = -*(u16 *)(car + 0x20E);
    }
    angle = *(s16 *)(car + 0x20E);
    if (angle < 0) {
        angle += 0x1000;
    }
    if (*(s32 *)(car + 0xB0) >= 0 ? *(s32 *)(car + 0xB0) < 0x28
                                  : -*(s32 *)(car + 0xB0) < 0x28) {
        if (*(s32 *)(car + 0xB4) >= 0 ? *(s32 *)(car + 0xB4) < 0x28
                                      : -*(s32 *)(car + 0xB4) < 0x28) {
            vx = *(s32 *)(car + 0xB0);
            vy = *(s32 *)(car + 0xB4);
            dist10 = (s32)MathSqrt(vx * vx + vy * vy) * D_800A2E1C / 10;
            if (*(s16 *)(car + 0x20E) >= 0 ? dist10 < *(s16 *)(car + 0x20E)
                                           : dist10 < -*(s16 *)(car + 0x20E)) {
                if (*(s16 *)(car + 0x20E) >= 0) {
                    angle = dist10;
                } else {
                    angle = (0x1000 - dist10) & 0xFFF;
                }
            }
        }
    }
    *(u16 *)(car + 0x1D0) = angle / 4;
    scale = 1000;
    if (angle >= 0x801) {
        angle -= 0x1000;
    }
    dist10 = angle * scale / 1000;
    *(u16 *)(car + 0x212) = dist10 / 4;
    if (dist10 < 0) {
        dist10 += 0x1000;
    }
    value = (*(u16 *)(car + 0x116) + dist10) & 0xFFF;
    *(u16 *)(car + 0x116) = value;
    *(s16 *)(car + 0x114) = value / 4;
    func_8001FAC0(car, *(s16 *)(car + 0x116));
    if (*(u8 *)(car + 0x410) != 0) {
        *(u16 *)(car + 0x20E) = -*(u16 *)(car + 0x20E);
    }
}

extern s32 D_800A3A04nm[] asm("D_800A3A04.NON_MATCHING");

void func_80029CB4(s32 *arg0) {
    s32 speed;
    s32 limit;
    s32 i;
    s32 off;
    s16 *entry;
    s16 angle;

    speed = D_800A3A04nm[0];
    limit = speed * 4;
    for (i = 0; i < 4; i++) {
        off = 0x2AC + i * 0x28;
        entry = (s16 *)((u8 *)arg0 + off);
        if (entry[2] != 0 || entry[0] != 0) {
            entry[0] += entry[2];
            if (entry[0] < 0) {
                entry[0] = 0;
                if (entry[2] >= 0 ? limit >= entry[2] : limit >= -entry[2]) {
                    entry[2] = 0;
                } else {
                    entry[2] = -entry[2] / 2;
                }
            } else {
                entry[2] -= speed;
            }
            angle = entry[0];
            if (angle >= 0x101) {
                angle = 0x100;
                entry[0] = angle;
            }
        }
    }
}

extern void func_80029CB4(s32 *arg0);
extern void func_80039B74(s32 *arg0, s32 arg1);
void func_80029DA8(s32 *car) {
    volatile s32 debugBuffer[16];
    s32 a;
    s32 b;
    s32 c;

    func_8002D16C(car);
    func_8002B538(car);
    func_80029A78(car);
    func_80029150(car);
    a = car[0] + car[0x2C];
    b = car[1] + car[0x2D];
    c = car[2] + car[0x2E];
    car[0] = a;
    car[1] = b;
    car[2] = c;
    func_80029CB4(car);
    func_80039B74(car, 0);
}

void func_80029E2C(void) {
}

void func_80029E34(void) {
}

void func_80029E3C(void) {
}

/* The volatile asm births the zero passed to func_8001F2C4 early, and being
 * volatile it holds move a2,zero in retail's slot. The reads of the three
 * words copied down (and their order) set sched1's load order and the
 * local-alloc reference counts; the second asm is a zero-byte anchor that
 * keeps the v0/v1 handout on the 0x18/0x1C pair like retail. */
extern s32 D_800A38AC[];
extern void func_8001F728(s32 arg0);

void func_80029E44(void) {
    s32 *sourceRow;
    u8 *secondRow;
    u8 *ptr;
    u8 *rowA;
    u8 *rowB;
    s32 zero;
    s32 x;
    s32 y;
    s32 valA;
    s32 valC;
    s32 valB;
    ptr = (u8 *)D_800A38AC[0];
    asm volatile("" : "=r"(zero) : "0"(0));
    sourceRow = (s32 *)(ptr + 0x18);
    valA = *((s32 *)(ptr + 0x20));
    valB = *sourceRow;
    valC = *((s32 *)(ptr + 0x1C));
    asm("" : : "r"(valB), "r"(valB), "r"(valC));
    *((s32 *)(ptr + 0x3C)) = valB;
    *((s32 *)(ptr + 0x40)) = valC;
    *((s32 *)(ptr + 0x44)) = valA;
    asm("");
    *((s32 *)(ptr + 0x48)) = *((s32 *)(ptr + 0x24));
    *((s32 *)(ptr + 0x4C)) = *((s32 *)(ptr + 0x28));
    *((s32 *)(ptr + 0x50)) = *((s32 *)(ptr + 0x2C));
    asm("");
    *((s32 *)(ptr + 0x54)) = *((s32 *)(ptr + 0x30));
    *((s32 *)(ptr + 0x58)) = *((s32 *)(ptr + 0x34));
    *((s32 *)(ptr + 0x5C)) = *((s32 *)(ptr + 0x38));
    asm("");
    x = *((s16 *)(ptr + 0x1C6));
    y = *((s16 *)(ptr + 0x1C8));
    rowA = ptr + 0x3C;
    secondRow = ptr + 0x48;
    rowB = secondRow;
    ptr += 0x54;
    func_8001F2C4(x, y, zero);
    func_8001F728((s32)rowA);
    func_8001F728((s32)rowB);
    func_8001F728((s32)ptr);
}

extern u8 D_800A3A24w15f[] asm("D_800A3A24.NON_MATCHING");
extern u8 D_800A2EE0w15f[] asm("D_800A2EE0.NON_MATCHING");
extern u8 D_800A3764w15f[] asm("D_800A3764.NON_MATCHING");
extern u8 D_800A372Cw15f[] asm("D_800A372C.NON_MATCHING");
extern s16 D_800A35A4w15f[] asm("D_800A35A4.NON_MATCHING");

s32 func_80029EF8(u8 *obj) {
    s32 flags;
    s32 v;
    s32 c4;

    c4 = *(s8 *)(obj + 0x3C4);
    v = *(s8 *)(obj + 0x20B);
    if (c4 == 0) {
        obj[0x3C4] = D_800A3A24w15f[v];
    }
    flags = func_8006E770(obj[0x20B]);
    v = *(s8 *)(obj + 0x3C4);
    if (v == 2) {
        goto twoFiveSeven;
    }
    if (v == 5) {
        goto twoFiveSeven;
    }
    if (v != 7) {
        goto notTwoFiveSeven;
    }
twoFiveSeven:
    func_8006EB18(obj);
    *(s16 *)(obj + 0x20E) =
        -((*(s8 *)(obj + 0x3C5) << 2) * (D_800A2E1C + 2)) / 128;
    *(s32 *)(obj + 0x3BC) = MathFixedDivide(obj[0x3C6], 0xFF);
    *(s32 *)(obj + 0x3C0) = MathFixedDivide(obj[0x3C7], 0x7D0);
    if (obj[0x3C6] < 0x3C) {
        flags &= ~0x40;
    } else {
        flags |= 0x40;
    }
    if (obj[0x3C7] < 0xE6) {
        flags &= ~0x80;
    } else {
        flags |= 0x80;
    }
    v = *(s16 *)(obj + 0x20E);
    if (v >= 2) {
        flags |= 0x8000;
    } else if (v < -1) {
        flags |= 0x200;
    }
    goto afterStatus;
notTwoFiveSeven:
    if (flags & 0x40) {
        *(s32 *)(obj + 0x3BC) += 0x2000;
        if (0x10000 < *(s32 *)(obj + 0x3BC)) {
            *(s32 *)(obj + 0x3BC) = 0x10000;
        }
    } else {
        *(s32 *)(obj + 0x3BC) = 0;
    }
    *(s32 *)(obj + 0x3C0) = 0x10000;
afterStatus:
    if (D_800A2EE0w15f[0] != 0) {
        if (obj[0x3B7] != 0) {
            goto decr3b7;
        }
        if (*(s32 *)(obj + 0x354) == (s32)func_80025594 ||
            *(s16 *)(obj + 0x1BC) == 4) {
            if (flags & 0x40) {
                if ((*(u16 *)(obj + 0x3A4) & 0xF) != 0 ||
                    *(s16 *)(obj + 0x1BC) == 4 ||
                    ((*(u16 *)(obj + 0x3A4) & 0x1000) != 0 &&
                     *(s32 *)(obj + 0x90) == 0)) {
                    func_80044114(obj);
                }
                goto skip3b7;
            }
        }
        if (obj[0x3B7] != 0) {
        decr3b7:
            obj[0x3B7]--;
        }
    skip3b7:;
    }
    if (*(s32 *)(obj + 0x354) == (s32)func_80025730 || obj[0xF4] == 0 ||
        D_800A3764w15f[0] != 0 ||
        (D_800A372Cw15f[0] != 0 && D_800A35A4w15f[0] >= 0x32)) {
        flags &= ~(0x40 | 0x80 | 0x200 | 0x8000);
        *(s32 *)(obj + 0x3BC) = 0;
    } else if (*(s32 *)(obj + 0x28C) <= 0 ||
               (*(s32 *)(obj + 0x3A4) & 0x100F) != 0) {
        flags &= ~0x40;
        *(s32 *)(obj + 0x3BC) = 0;
    }
    return flags;
}

extern s32 D_800A2E1C, D_800A2E24;
void func_8002A1D0(void) {
    D_800A2E24 = 0x1EF0000 - (D_800A2E1C - 3) * 0x30000;
}

extern s32 D_800A35D4[];
extern s32 func_80029EF8();
extern void func_8001FD44();

/* Sets bit D_800A2EC4 when the object's 0x209 counter wraps to 3 and the
   0x238 status mask from func_80029EF8 asks for the counter update.
   The (u16) casts keep `~status & MASK` as a unit that flags is ANDed
   with; without them fold reassociates it into `(flags & MASK) & ~status`. */
void func_8002A1FC(u8 *arg0) {
    s32 flags;
    s32 v;
    s32 t;

    flags = func_80029EF8(arg0);
    if (((flags & ((u16) ~*(s32 *)(arg0 + 0x238) & 0x10)) != 0) ||
        ((flags & ((u16) ~*(s32 *)(arg0 + 0x238) & 0x4000)) != 0)) {
        func_8001FD44(arg0);
    }
    if (*(u8 *)D_800A35D4 != 0) {
        *(s32 *)(arg0 + 0x238) = flags;
        return;
    }
    if ((flags & ((u16) ~*(s32 *)(arg0 + 0x238) & 4)) != 0) {
        if (D_800A2EA4[0] != 0) {
            v = *(u8 *)(arg0 + 0x209) ^ 1;
            *(u8 *)(arg0 + 0x209) = v;
        } else {
            t = *(s8 *)(arg0 + 0x209);
            v = (t + 1) % 4;
            *(u8 *)(arg0 + 0x209) = v;
            D_800A2EC4w15[0] = ((s8)v == 3);
        }
        *(s32 *)(arg0 + 0x238) = flags;
    } else {
        *(s32 *)(arg0 + 0x238) = flags;
    }
}

/* Separate symbol views preserve the retail GP and absolute accesses. */
asm(".globl D_800A2E1CPlayerStep\nD_800A2E1CPlayerStep = D_800A2E1C\n"
    ".globl D_800A2E24PlayerStep\nD_800A2E24PlayerStep = D_800A2E24\n"
    ".globl D_800A2E6CPlayerStep\nD_800A2E6CPlayerStep = D_800A2E6C\n"
    ".globl D_800A2E70PlayerStep\nD_800A2E70PlayerStep = D_800A2E70\n"
    ".globl D_800A2E74PlayerStep\nD_800A2E74PlayerStep = D_800A2E74\n"
    ".globl D_800A2EA4PlayerStep\nD_800A2EA4PlayerStep = D_800A2EA4\n"
    ".globl D_800A2EC0PlayerStep\nD_800A2EC0PlayerStep = D_800A2EC0\n"
    ".globl D_800A2EC4PlayerStep\nD_800A2EC4PlayerStep = D_800A2EC4\n"
    ".globl D_800A2EC8PlayerStep\nD_800A2EC8PlayerStep = D_800A2EC8\n"
    ".globl D_800A3598PlayerStep\nD_800A3598PlayerStep = D_800A3598\n"
    ".globl D_800A35D4PlayerStep\nD_800A35D4PlayerStep = D_800A35D4\n"
    ".globl D_800A397CPlayerStep\nD_800A397CPlayerStep = D_800A397C\n");
extern s32 D_800A2E1CPlayerStep;
extern s32 D_800A2E24PlayerStep;
extern s32 D_800A2E6CPlayerStep[];
extern s32 D_800A2E70PlayerStep[];
extern s32 D_800A2E74PlayerStep[];
extern s32 D_800A2EA4PlayerStep[];
extern s32 D_800A2EC0PlayerStep[];
extern s32 D_800A2EC4PlayerStep[];
extern s32 D_800A2EC8PlayerStep[];
extern s32 D_800A3598PlayerStep[];
extern u8 D_800A35D4PlayerStep[];
extern s32 D_800A397CPlayerStep[];

void CarUpdatePlayer(u8 *object) {
    u8 frameScratch[0x48];
    u8 *car;
    register s32 zeroRoll asm("s5");
    register s32 zeroPitch asm("s4");
    s16 speed;
    register s32 steeringValue asm("v0");
    register s32 centerAngle asm("v1");
    s32 positionX;
    s32 positionY;
    s32 positionZ;
    s32 steeringSlope;
    s32 controlFlags;
    register s32 quarterAngle asm("v0");
    s32 analogSample;
    register s32 centeredAnalog asm("v0");
    register s32 work asm("v0");
    s32 unkF8;
    s32 throttlePressed;
    s32 nextCameraMode;
    s32 steeringDivisor;
    s32 steeringFactor;
    s32 angleWork;
    s32 turnWork;
    s32 headingInput;
    s32 analogProduct;
    register s32 incomingS1 asm("s1");
    s32 steeringLimit;
    s32 cameraQuotientInput;
    s32 headingQuotientInput;
    s32 headingBase;
    s8 cameraMode;
    s8 leftStep;
    s8 rightStep;
    s8 nextLeftStep;
    s8 nextRightStep;
    register s32 centerRightAngle asm("v0");
    u16 leftAngle;
    register u16 rightAngle asm("v0");
    register s32 centerLeftAngle asm("v0");
    u8 nextCamera;

    car = object;
    /* Preserve the unused retail frame and the caller argument reloads. */
    asm("" : : "r"(car), "m"(frameScratch[0]) : "a0");
    if (D_800A2EC8PlayerStep[0] != 0) {
        func_80023454();
        return;
    }
    if ((*(u8 *)(car + 0x268)) != 0) {
        func_8003DBA8(car);
        return;
    }
    controlFlags = func_80029EF8(car);
    if ((controlFlags & ((u16) ~*(s32 *)(car + 0x238) & 0x10)) ||
        (controlFlags & ((u16) ~*(s32 *)(car + 0x238) & 0x4000))) {
        func_8001FD44((RaceObject *)car);
    }
    if (D_800A397CPlayerStep[0] == 2) {
        (*(s32 *)(car + 0x238)) = controlFlags;
        return;
    }
    if ((D_800A35D4PlayerStep[0] == 0) &&
        (controlFlags & ((u16) ~*(s32 *)(car + 0x238) & 4))) {
        if (D_800A2EA4PlayerStep[0] != 0) {
            (*(u8 *)(car + 0x209)) = (u8)((*(u8 *)(car + 0x209)) ^ 1);
        } else {
            cameraMode = (s8)(*(u8 *)(car + 0x209));
            nextCameraMode = cameraMode + 1;
            cameraQuotientInput = nextCameraMode;
            if (nextCameraMode < 0) {
                cameraQuotientInput = cameraMode + 4;
            }
            nextCamera = nextCameraMode - ((cameraQuotientInput >> 2) * 4);
            (*(u8 *)(car + 0x209)) = nextCamera;
            D_800A2EC4PlayerStep[0] = (s8)nextCamera == 3;
        }
    }
    if (controlFlags & ((u16) ~*(s32 *)(car + 0x238) & 1)) {
        SelectionStepForward((Counter *)car);
    }
    if (controlFlags & ((u16) ~*(s32 *)(car + 0x238) & 2)) {
        SelectionStepBackward((SelectionState *)car);
    }
    (*(s32 *)(car + 0x238)) = controlFlags;
    (*(void (**)(u8 *))(car + 0x354))(car);
    /* Retail keeps incoming s1 when unkF8 is nonzero. Earlier calls
     * preserve s1. Capture that register input before using C locals. */
    asm("" : "=r"(incomingS1));
    steeringLimit = incomingS1;
    D_800A2E24PlayerStep = 0x01EF0000 - ((D_800A2E1CPlayerStep - 3) * 0x30000);
    unkF8 = *(u8 *)(car + 0xF8);
    asm("" : : "r"(unkF8) : "s3");
    controlFlags = (*(s32 *)(car + 0x238));
    asm("" : : "r"(controlFlags) : "s5", "s4");
    zeroRoll = 0;
    zeroPitch = 0;
    if (unkF8 == 0) {
        steeringLimit = D_800A2E1CPlayerStep;
        if (D_800A3598PlayerStep[0] == 1) {
            if (controlFlags & 0x800) {
                work = steeringLimit * 3;
                steeringLimit = work >> 2;
                if (work < 0) {
                    work += 3;
                    steeringLimit = work >> 2;
                }
            }
            if (controlFlags & 0x1000) {
                work = D_800A2E1CPlayerStep * 4;
                steeringLimit = work / 3;
            }
        }
    }
    /* Scale the steering limit with speed and the steering setting. */
    steeringSlope = (((D_800A2E70PlayerStep[0] - D_800A2E6CPlayerStep[0]) *
                      (D_800A2E74PlayerStep[0] - 0x32)) /
                     50) +
                    D_800A2E6CPlayerStep[0];
    steeringDivisor = func_8002AAA0((s32 *)car);
    speed = (*(s16 *)(car + 0x92));
    steeringLimit *= 4;
    if (speed > 0xC8) {
        steeringFactor =
            1000 - ((speed - 200) * steeringSlope) / steeringDivisor;
        if (steeringFactor > 1000) {
            steeringFactor = 1000;
        }
    } else {
        steeringFactor = 1000;
    }
    work = steeringLimit * steeringFactor;
    steeringFactor = work / 1000;
    steeringLimit = steeringFactor;
    if (steeringLimit < 8) {
        steeringLimit = 8;
    }
    /* Digital steering ramps toward either limit and returns to center. */
    if ((*(s8 *)(car + 0x3C4)) == 4) {
        if (controlFlags & 0x8000) {
            leftStep = (*(s8 *)(car + 0x207));
            if (leftStep == 0) {
                nextLeftStep = 4;
            } else {
                nextLeftStep = leftStep + 3;
            }
            (*(s8 *)(car + 0x207)) = nextLeftStep;
            asm("" : : : "memory");
            if ((*(s8 *)(car + 0x207)) >= 0xC) {
                (*(s8 *)(car + 0x207)) = 0xC;
            }
            (*(s8 *)(car + 0x208)) = 0;
            angleWork = *(u16 *)(car + 0x20E);
            steeringValue = *(u8 *)(car + 0x207);
            asm(""
                : "=r"(steeringValue)
                : "0"(steeringValue), "m"(*(s8 *)(car + 0x208)));
            steeringValue = (s8)steeringValue;
            angleWork += 4;
            leftAngle = steeringValue + angleWork;
            (*(u16 *)(car + 0x20E)) = leftAngle;
            if (steeringLimit < (s16)leftAngle) {
                (*(u16 *)(car + 0x20E)) = (u16)steeringLimit;
            }
        } else if (controlFlags & 0x200) {
            rightStep = (*(s8 *)(car + 0x208));
            if (rightStep == 0) {
                nextRightStep = 4;
            } else {
                nextRightStep = rightStep + 3;
            }
            (*(s8 *)(car + 0x208)) = nextRightStep;
            asm("" : : : "memory");
            if ((*(s8 *)(car + 0x208)) >= 0xC) {
                (*(s8 *)(car + 0x208)) = 0xC;
            }
            (*(s8 *)(car + 0x207)) = 0;
            rightAngle = *(u16 *)(car + 0x20E);
            turnWork = *(u8 *)(car + 0x208);
            asm("" : "=r"(turnWork) : "0"(turnWork), "m"(*(s8 *)(car + 0x207)));
            turnWork = (s8)turnWork;
            rightAngle -= 4;
            rightAngle -= turnWork;
            (*(u16 *)(car + 0x20E)) = rightAngle;
            steeringValue = (s16)rightAngle;
            turnWork = -steeringLimit;
            if (steeringValue < turnWork) {
                (*(u16 *)(car + 0x20E)) = (u16)turnWork;
            }
        } else {
            steeringValue = *(s16 *)(car + 0x20E);
            (*(s8 *)(car + 0x207)) = 0;
            (*(s8 *)(car + 0x208)) = 0;
            centerAngle = steeringValue;
            if (steeringValue > 0) {
                centerLeftAngle = centerAngle - 8;
                (*(u16 *)(car + 0x20E)) = centerLeftAngle;
                if ((centerLeftAngle << 16) < 0) {
                    (*(u16 *)(car + 0x20E)) = 0U;
                }
            } else {
                centerRightAngle = centerAngle + 8;
                (*(u16 *)(car + 0x20E)) = centerRightAngle;
                if ((centerRightAngle << 0x10) > 0) {
                    (*(u16 *)(car + 0x20E)) = 0U;
                }
            }
        }
    } else {
        /* Retail retains a second analog read and a discarded offset. */
        analogProduct = -((*(s8 *)(car + 0x3C5)) * steeringLimit);
        asm("" : "=r"(car) : "0"(car), "r"(analogProduct));
        analogSample = *(s8 *)(car + 0x3C5);
        (*(u16 *)(car + 0x20E)) = (u16)(analogProduct / 112);
        asm("" : : "r"(analogSample), "m"(*(u16 *)(car + 0x20E)) : "v0");
        centeredAnalog = analogSample - 128;
        asm("" : : "r"(centeredAnalog));
    }
    if ((*(s32 *)(car + 0x90)) >= 0) {
        quarterAngle = (s16)(*(u16 *)(car + 0x20E)) / 4;
        headingInput = quarterAngle;
        (*(s16 *)(car + 0x212)) = (s16)quarterAngle;
        if (headingInput >= 0) {
            if (headingInput != 1) {

            } else {
                goto clearQuarterAngle;
            }
        } else if (-headingInput == 1) {
        clearQuarterAngle:
            (*(s16 *)(car + 0x212)) = 0;
        }
    } else {
        asm("" : : : "a0");
        headingInput = 0;
    }
    headingBase = headingInput + 0x400;
    if (((*(u8 *)(car + 0xF8)) != 0) && (controlFlags & 0x40)) {
        work = headingInput * 5;
        headingInput = work >> 2;
        if (work < 0) {
            work += 3;
            headingInput = work >> 2;
        }
        headingBase = headingInput + 0x400;
    }
    headingQuotientInput = headingBase;
    if (headingBase < 0) {
        headingQuotientInput = headingInput + 0x7FF;
    }
    headingInput = headingQuotientInput >> 10;
    work = headingInput << 10;
    headingInput = headingBase - work;
    (*(s16 *)(car + 0x1D0)) = (s16)headingInput;
    (*(s16 *)(car + 0x1D2)) = zeroPitch;
    (*(s16 *)(car + 0x1D4)) = zeroRoll;
    throttlePressed = controlFlags & 0x40;
    if (throttlePressed) {
        work = D_800A2E24PlayerStep;
        (*(s32 *)(car + 0x37C)) = 0;
        (*(s32 *)(car + 0x84)) = work;
    } else {
        work = *(s32 *)(car + 0x37C);
        (*(s32 *)(car + 0x84)) = 0;
        work++;
        (*(s32 *)(car + 0x37C)) = work;
    }
    func_8002B258(car);
    func_8002D16C(car);
    func_8002B538(car);
    func_80029A78(car);
    func_80029150(car);
    positionX = *(s32 *)(car + 0) + *(s32 *)(car + 0xB0);
    positionY = *(s32 *)(car + 4) + *(s32 *)(car + 0xB4);
    positionZ = *(s32 *)(car + 8) + *(s32 *)(car + 0xB8);
    *(s32 *)(car + 0) = positionX;
    *(s32 *)(car + 4) = positionY;
    *(s32 *)(car + 8) = positionZ;
    func_80029CB4((s32 *)car);
    func_80039B74((s32 *)car, 0);
    if ((*(s8 *)(car + 0x204)) == 1) {
        (*(s32 *)(car + 0x3D0)) = (s32)D_800A2EC0PlayerStep[0];
    }
}

extern u8 D_800A331D[];
extern u8 D_800A331F[];
extern u8 D_800A2E20[];
extern s32 D_800A2E30;
extern s32 D_800A2E38;
extern s32 D_800A2E3C;
extern s32 D_800A2E44;
extern s32 D_800A2E48;
extern s32 D_800A2E4C;
extern s32 D_800A2E54;
extern s16 D_800A2E58;
extern s32 D_800A2E5C;
extern s32 D_800A3A04;
extern s32 D_800A2E50;

void func_8002A954(void) {
    D_800A2E44 = 0x5D;
    D_800A2E48 = 0x1A;
    D_800A2E50 = (D_800A331D[0] - 0x32) * 0x50;
    D_800A2E20[0] = D_800A3320[0];
    D_800A2E54 = (0x70 - D_800A331F[0]) * 0x10000;
    D_800A2E4C = (D_800A331C[0] + 0xC8) / 3;
    D_800A2E58 = 0x3A98 / (D_800A331D[0] - 0x46);
    D_800A2E5C = 0x28A0000 / (D_800A331F[0] - 0x14);
    if (D_800A331F[0] > 0x64) {
        D_800A2E54 = 0xC0000 - (D_800A331F[0] - 0x64) * 0x10000 / 5;
    }
    D_800A2E30 = 0x10CC;
    D_800A2E38 = 0x23;
    D_800A2E3C = 0x23;
    D_800A3A04 = 0xD;
}

s32 func_8002AAA0(s32 *car) {
    s32 weight;
    s32 total;
    s32 base;

    base = (car[0x14] * 200) >> 16;
    total = (car[0x90] * 35 + car[0x91] * 5) >> 16;
    weight = base + 3000;
    return total + weight;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002AAF0);

void func_8002AD20(s32 *car, s32 index) {
    s32 entryA;
    s32 entryB;

    entryA = ((s32 **)D_800A3A2CAbsolute)[0][index];
    entryB = ((s32 **)D_800A3A34Absolute)[0][index];
    car[0x31] = MathMultiplyFixed16(entryA, car[0x24]);
    car[0x32] = MathMultiplyFixed16(entryB, car[0x24]);
    car[0x34] = MathMultiplyFixed16(entryA, car[0x24]);
    car[0x35] = MathMultiplyFixed16(entryB, car[0x24]);
    car[0x2C] = MathMultiplyFixed16(entryA, car[0x24]) >> 16;
    car[0x2D] = MathMultiplyFixed16(entryB, car[0x24]) >> 16;
}

void func_8002ADE0(s32 *car, s32 arg1) {
    s32 index;
    s32 entryA;
    s32 entryB;

    index = (((s16 *)car)[0x8A] + 0x200) & 0x3FF;
    entryA = ((s32 **)D_800A3A2CAbsolute)[0][index];
    entryB = ((s32 **)D_800A3A34Absolute)[0][index];
    car[0x31] = car[0x31] + MathMultiplyFixed16(entryA, arg1);
    car[0x32] = car[0x32] + MathMultiplyFixed16(entryB, arg1);
    car[0x34] = car[0x34] + MathMultiplyFixed16(entryA, arg1);
    car[0x35] = car[0x35] + MathMultiplyFixed16(entryB, arg1);
}

s32 func_8002AEB0(u8 *arg0) {
    s32 index;
    VECTOR rotated;
    s32 value;
    s32 temp;
    s32 product;

    index = (0x400 - *(s16 *)(arg0 + 0x114)) & 0x3FF;
    product = ((s32 **)D_800A3A2CAbsolute)[0][index] * *(s32 *)(arg0 + 0xB0);
    rotated.vx = (product - (((s32 **)D_800A3A34Absolute)[0][index] *
                             *(s32 *)(arg0 + 0xB4))) >>
                 16;
    product = ((s32 **)D_800A3A34Absolute)[0][index] * *(s32 *)(arg0 + 0xB0);
    rotated.vy = (product + (((s32 **)D_800A3A2CAbsolute)[0][index] *
                             *(s32 *)(arg0 + 0xB4))) >>
                 16;
    value = rotated.vx;
    if (value < 0) {
        temp = -value;
        *(u8 *)(arg0 + 0x410) = temp;
        value = 0;
        if ((temp & 0xFF) >= 0x65U) {
            *(u8 *)(arg0 + 0x410) = 0x64;
        }
    } else {
        *(u8 *)(arg0 + 0x410) = 0;
    }
    return value << 16;
}

typedef struct {
    u8 unk0[0x44];
    s32 dragScale;
    u8 unk48[0x40];
    s32 driveScale;
    u8 unk8C[0x4];
    s32 speed;
    u8 unk94[0x4];
    s32 maxSpeed;
    u8 unk9C[0x14];
    s32 velocityX;
    s32 velocityY;
    u8 unkB8[0xC];
    s32 frontVelocityX;
    s32 frontVelocityY;
    u8 unkCC[0x4];
    s32 rearVelocityX;
    s32 rearVelocityY;
    u8 unkD8[0x1C];
    u8 unkF4;
    u8 unkF5[0x4];
    u8 sliding;
    u8 unkFA[0xA];
    s16 movementHeading;
    u8 unk106[0x4];
    s16 unk10A;
    s16 unk10C;
    s16 unk10E;
    u8 unk110[0x4];
    s16 heading;
    u16 fineHeading;
    u8 unk118[0x8];
    s16 unk120;
    u8 unk122[0xE3];
    s8 assistRank;
    u8 unk206[0x8];
    u16 steering;
    u8 unk210[0x1C];
    s32 speedBoost;
    u8 unk230[0x8];
    s32 flags;
    u8 unk23C[0x4];
    s32 frontGrip;
    s32 rearGrip;
    u8 unk248[0x44];
    s32 unk28C;
    u8 unk290[0x10];
    s16 unk2A0;
    u8 unk2A2[0x4];
    s16 unk2A6;
    u8 unk2A8[0x4];
    s16 unk2AC;
    u8 unk2AE[0xA];
    s32 unk2B8;
    u8 unk2BC[0x18];
    s16 unk2D4;
    u8 unk2D6[0xA];
    s32 unk2E0;
    u8 unk2E4[0x18];
    s16 unk2FC;
    u8 unk2FE[0xA];
    s32 unk308;
    u8 unk30C[0x18];
    s16 unk324;
    u8 unk326[0xA];
    s32 unk330;
    u8 unk334[0x20];
    void (*callback)(u8 *);
    u8 unk358[0xA];
    s16 unk362;
    s16 unk364;
    s16 unk366;
    s16 unk368;
    u8 unk36A[0x3A];
    u16 unk3A4;
    u8 unk3A6[0x16];
    s32 driveInput;
    u8 unk3C0[0x24];
    u8 *raceNode;
    u8 unk3E8[0x28];
    u8 reverseSpeed;
} CarDynamics;

void func_8002AF94(CarDynamics *car) {
    extern u8 *trigA asm("D_800A3A2CAbsolute");
    extern u8 *trigB asm("D_800A3A34Absolute");
    u32 unused[8]; /* retail reserves 32 bytes of locals nothing touches */
    VECTOR front;
    VECTOR rear;
    s32 diff;
    s32 index;

    index = (0x400 - car->heading) & 0x3FF;
    front.vx = MathMultiplyFixed16(((s32 *)trigA)[index], car->frontVelocityX) -
               MathMultiplyFixed16(((s32 *)trigB)[index], car->frontVelocityY);
    front.vy = MathMultiplyFixed16(((s32 *)trigB)[index], car->frontVelocityX) +
               MathMultiplyFixed16(((s32 *)trigA)[index], car->frontVelocityY);
    rear.vx = MathMultiplyFixed16(((s32 *)trigA)[index], car->rearVelocityX) -
              MathMultiplyFixed16(((s32 *)trigB)[index], car->rearVelocityY);
    rear.vy = MathMultiplyFixed16(((s32 *)trigB)[index], car->rearVelocityX) +
              MathMultiplyFixed16(((s32 *)trigA)[index], car->rearVelocityY);
    diff = front.vx - rear.vx;
    if (abs(diff) > 0x50000) {
        front.vx = front.vx + -diff * 4 / 10;
        rear.vx = rear.vx + diff * 6 / 10;
        index = car->heading;
        car->frontVelocityX =
            MathMultiplyFixed16(((s32 *)trigA)[index], front.vx) -
            MathMultiplyFixed16(((s32 *)trigB)[index], front.vy);
        car->frontVelocityY =
            MathMultiplyFixed16(((s32 *)trigB)[index], front.vx) +
            MathMultiplyFixed16(((s32 *)trigA)[index], front.vy);
        car->rearVelocityX =
            MathMultiplyFixed16(((s32 *)trigA)[index], rear.vx) -
            MathMultiplyFixed16(((s32 *)trigB)[index], rear.vy);
        car->rearVelocityY =
            MathMultiplyFixed16(((s32 *)trigB)[index], rear.vx) +
            MathMultiplyFixed16(((s32 *)trigA)[index], rear.vy);
    }
}

extern s32 D_800A2E44nm asm("D_800A2E44.NON_MATCHING");
extern s32 D_800A2E48nm asm("D_800A2E48.NON_MATCHING");

void func_8002B258(u8 *arg0) {
    extern u8 D_800A2EE4nm[] asm("D_800A2EE4.NON_MATCHING");
    extern s32 D_800A3A2CAbsoluteB[] asm("D_800A3A2CAbsolute");
    extern s32 D_800A3A34AbsoluteB[] asm("D_800A3A34Absolute");
    volatile s32 pad[16];
    s32 speed;
    s32 index;
    s32 scale;
    s32 value;
    s32 p;
    s32 *q;
    s32 v;
    s32 x;

    if (*(s32 *)(arg0 + 0x238) & 0x80) {
        speed = D_800A2E48nm << 16;
        if (*(s16 *)(arg0 + 0x120) != 0) {
            speed = speed / 3;
        }
        if (*(s8 *)(arg0 + 0x3C4) != 4) {
            *(s32 *)(arg0 + 0x228) =
                MathMultiplyFixed16(speed, *(s32 *)(arg0 + 0x3C0));
        } else {
            *(s32 *)(arg0 + 0x228) += MathFixedDivide(D_800A2E44nm, 100);
            if (speed < *(s32 *)(arg0 + 0x228)) {
                *(s32 *)(arg0 + 0x228) = speed;
            }
        }
        if (*(s32 *)(arg0 + 0x228) > *(s32 *)(arg0 + 0x90)) {
            *(s32 *)(arg0 + 0x228) = *(s32 *)(arg0 + 0x90);
        }
        scale = *(s32 *)(arg0 + 0x228);
        index = *(s16 *)(arg0 + 0x104);
        if (D_800A2EE4nm[0] != 0) {
            scale = MathMultiplyFixed16(
                scale,
                MathFixedDivide((*(s8 *)(arg0 + 0x205) - 1) * 50 + 100, 100));
            if (*(s32 *)(arg0 + 0x90) < scale) {
                scale = *(s32 *)(arg0 + 0x90);
            }
        }
        if ((*(s32 *)(arg0 + 0xB0) >= 0 ? *(s32 *)(arg0 + 0xB0) < 10
                                        : -*(s32 *)(arg0 + 0xB0) < 10) &&
            (*(s32 *)(arg0 + 0xB4) >= 0 ? *(s32 *)(arg0 + 0xB4) < 10
                                        : -*(s32 *)(arg0 + 0xB4) < 10)) {
            *(s32 *)(arg0 + 0xC4) = 0;
            *(s32 *)(arg0 + 0xC8) = 0;
            *(s32 *)(arg0 + 0xD0) = 0;
            *(s32 *)(arg0 + 0xD4) = 0;
        } else {
            if (scale == 0) {
                scale = 0x50000;
            }
            v = MathMultiplyFixed16((*(s32 **)D_800A3A2CAbsolute)[index],
                                    scale);
            x = *(s32 *)(arg0 + 0xC4);
            p = *(s32 *)D_800A3A34Absolute;
            x -= v;
            *(s32 *)(arg0 + 0xC4) = x;
            q = (s32 *)(index * 4 + p);
            v = MathMultiplyFixed16(*q, scale);
            x = *(s32 *)(arg0 + 0xC8);
            p = *(s32 *)D_800A3A2CAbsoluteB;
            x -= v;
            *(s32 *)(arg0 + 0xC8) = x;
            q = (s32 *)(index * 4 + p);
            v = MathMultiplyFixed16(*q, scale);
            x = *(s32 *)(arg0 + 0xD0);
            p = *(s32 *)D_800A3A34AbsoluteB;
            x -= v;
            *(s32 *)(arg0 + 0xD0) = x;
            *(s32 *)(arg0 + 0xD4) -=
                MathMultiplyFixed16(*(s32 *)(index * 4 + p), scale);
        }
        if (*(s32 *)(arg0 + 0x90) > 0x17C0000 && RandomScaledGet(0xA) == 0) {
            value = RandomScaledGet(4);
            if (value < 0) {
                value = -RandomScaledGet(4);
            } else {
                value = RandomScaledGet(4);
            }
            *(s16 *)(arg0 + 0x2D8) = value;
            *(s16 *)(arg0 + 0x2B0) = value;
        }
    } else {
        *(s32 *)(arg0 + 0x228) -= 0x10000;
        if (*(s32 *)(arg0 + 0x228) < 0) {
            *(s32 *)(arg0 + 0x228) = 0;
        }
        *(s16 *)(arg0 + 0x11E) = 0;
        *(s16 *)(arg0 + 0x120) = 0;
        *(s16 *)(arg0 + 0x11C) = 0;
    }
}

void func_8002B538(u8 *arg0) {
    s32 speed;
    s32 half;

    speed = (*(s32 *)(arg0 + 0x90) / *(s16 *)(arg0 + 0x2B4)) >> 16;
    if (*(s16 *)(arg0 + 0x120) != 0 || *(u8 *)(arg0 + 0xF8) != 0) {
        speed = speed * 4;
    }
    *(s32 *)(arg0 + 0x2B8) -= speed;
    *(s32 *)(arg0 + 0x2E0) -= speed;
    half = speed / 2;
    if (*(s32 *)(arg0 + 0x2B8) <= 0x9FFFF) {
        *(s32 *)(arg0 + 0x2B8) = 0xA0000;
    }
    if (*(s32 *)(arg0 + 0x2E0) <= 0x9FFFF) {
        *(s32 *)(arg0 + 0x2E0) = 0xA0000;
    }
    *(s32 *)(arg0 + 0x308) -= half;
    *(s32 *)(arg0 + 0x330) -= half;
    if (*(s32 *)(arg0 + 0x308) <= 0x9FFFF) {
        *(s32 *)(arg0 + 0x308) = 0xA0000;
    }
    if (*(s32 *)(arg0 + 0x330) <= 0x9FFFF) {
        *(s32 *)(arg0 + 0x330) = 0xA0000;
    }
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002B63C);

void func_8002B9AC(CarDynamics *car, s32 *frontGrip, s32 *rearGrip) {
    extern s32 func_8002B63C(CarDynamics *, s32, s32);
    extern s32 MathFixedDivide(s32, s32);
    extern s8 D_800A2E5B;
    s32 grip;
    s32 num;
    s32 cnt;
    s32 count;
    s32 flags;
    s32 ratio;

    D_800A2E5B = 0;
    grip = func_8002B63C(car, car->unk362, 0);
    grip = grip + func_8002B63C(car, car->unk364, 1);
    grip = MathMultiplyFixed16(car->unk308 + car->unk330, grip);
    count = car->unk2A0;
    flags = car->unk3A4;
    cnt = count + 1;
    if (flags & 0x20) {
        cnt = count - 1;
    }
    if (flags & 0x40) {
        cnt = cnt - 2;
    }
    num = cnt * D_800A2E38;
    if (cnt < -7) {
        num = D_800A2E38 * -7 + (cnt + 7) * 20;
    }
    grip = grip + MathMultiplyFixed16(grip, MathFixedDivide(num, 0x3E8));
    *frontGrip = grip;
    grip = func_8002B63C(car, car->unk366, 2);
    grip = grip + func_8002B63C(car, car->unk368, 3);
    grip = MathMultiplyFixed16(car->unk2B8 + car->unk2E0, grip);
    if (D_800A2E5B == 4) {
        func_80041848((u8 *)car, 3);
    }
    count = car->unk2A6;
    cnt = count + 1;
    if (car->unk3A4 & 0x80) {
        cnt = count - 2;
    }
    num = cnt * D_800A2E3C;
    if (cnt < -7) {
        num = D_800A2E3C * -7 + (cnt + 7) * 20;
    }
    grip = grip + MathMultiplyFixed16(grip, MathFixedDivide(num, 0x3E8));
    *rearGrip = grip;
    car->unk10A = 0;
    if (car->unk2FC != 0 || car->unk324 != 0) {
        *frontGrip = 0;
    }
    if (car->unk2AC != 0 || car->unk2D4 != 0) {
        *rearGrip = 0;
        if (car->flags & 0x40) {
            car->unk10A += 0xFA0;
        }
    }
    if (D_800A2EE4w15[0] != 0) {
        ratio = MathFixedDivide((car->assistRank - 1) * 50 + 0x64, 0x64);
        *frontGrip = MathMultiplyFixed16(*frontGrip, ratio);
        ratio = MathFixedDivide((car->assistRank - 1) * 50 + 0x64, 0x64);
        *rearGrip = MathMultiplyFixed16(*rearGrip, ratio);
    }
    car->frontGrip = *frontGrip;
    car->rearGrip = *rearGrip;
    if (car->unk120 != 0) {
        *frontGrip = *frontGrip / 2;
        *rearGrip = 0;
    }
}

extern s32 D_800A2E40;

void func_8002BC88(u8 *arg0) {
    s32 y;
    s32 val;
    s32 result;
    s32 d;
    y = (*(s16 *)(arg0 + 0x2A6) + 1) * 75 << 16;
    val = D_800A2E24Absolute[0] + *(s32 *)(arg0 + 0x22C) -
          (*(s16 *)(arg0 + 0x10E) << 17) - y / 15;
    result = MathFixedDivide(*(s32 *)(arg0 + 0x28C), 16000);
    d = D_800A2E40;
    val -= result * d - ((d / 2) << 16);
    *(s32 *)(arg0 + 0x98) = val;
}

extern s32 D_800A3598Physics[] asm("D_800A3598.NON_MATCHING");
extern s32 D_800A453CPhysics[] asm("D_800A453C.NON_MATCHING");
extern s32 func_8002AAF0(u8 *, VECTOR *, s32);
extern void func_8002AF94(CarDynamics *);
extern void func_8002B9AC(CarDynamics *, s32 *, s32 *);
extern void func_8002D27C(u8 *);
extern s32 func_8003702C(u8 *, u8 *);

#define CAR_OFFSET(field) ((u32) & ((CarDynamics *)0)->field)
typedef char CheckVectorSize[(sizeof(VECTOR) == 16) ? 1 : -1];
typedef char CheckCarDrag[(CAR_OFFSET(dragScale) == 0x44) ? 1 : -1];
typedef char CheckCarDrive[(CAR_OFFSET(driveScale) == 0x88) ? 1 : -1];
typedef char CheckCarSpeed[(CAR_OFFSET(speed) == 0x90) ? 1 : -1];
typedef char CheckCarMaxSpeed[(CAR_OFFSET(maxSpeed) == 0x98) ? 1 : -1];
typedef char CheckCarVelocityX[(CAR_OFFSET(velocityX) == 0xB0) ? 1 : -1];
typedef char CheckCarFrontX[(CAR_OFFSET(frontVelocityX) == 0xC4) ? 1 : -1];
typedef char CheckCarRearX[(CAR_OFFSET(rearVelocityX) == 0xD0) ? 1 : -1];
typedef char CheckCarFlag[(CAR_OFFSET(unkF4) == 0xF4) ? 1 : -1];
typedef char CheckCarSlide[(CAR_OFFSET(sliding) == 0xF9) ? 1 : -1];
typedef char CheckCarMovement[(CAR_OFFSET(movementHeading) == 0x104) ? 1 : -1];
typedef char CheckCarHeading[(CAR_OFFSET(heading) == 0x114) ? 1 : -1];
typedef char CheckCarFineHeading[(CAR_OFFSET(fineHeading) == 0x116) ? 1 : -1];
typedef char CheckCarRank[(CAR_OFFSET(assistRank) == 0x205) ? 1 : -1];
typedef char CheckCarSteering[(CAR_OFFSET(steering) == 0x20E) ? 1 : -1];
typedef char CheckCarSpeedBoost[(CAR_OFFSET(speedBoost) == 0x22C) ? 1 : -1];
typedef char CheckCarFlags[(CAR_OFFSET(flags) == 0x238) ? 1 : -1];
typedef char CheckCarLoad[(CAR_OFFSET(unk28C) == 0x28C) ? 1 : -1];
typedef char CheckCarGrip[(CAR_OFFSET(unk2A6) == 0x2A6) ? 1 : -1];
typedef char CheckCarFrontGrip[(CAR_OFFSET(unk2AC) == 0x2AC) ? 1 : -1];
typedef char CheckCarRearGrip[(CAR_OFFSET(unk2D4) == 0x2D4) ? 1 : -1];
typedef char CheckCarCallback[(CAR_OFFSET(callback) == 0x354) ? 1 : -1];
typedef char CheckCarDriveInput[(CAR_OFFSET(driveInput) == 0x3BC) ? 1 : -1];
typedef char CheckCarRaceNode[(CAR_OFFSET(raceNode) == 0x3E4) ? 1 : -1];
typedef char CheckCarReverseSpeed[(CAR_OFFSET(reverseSpeed) == 0x410) ? 1 : -1];
#undef CAR_OFFSET

void func_8002BD48(u8 *carBytes) {
    register CarDynamics *car asm("s2");
    struct {
        VECTOR force;
        VECTOR axleVelocity;
        VECTOR frontVelocity;
        VECTOR rearVelocity;
        VECTOR unused[5];
        s32 frontGrip;
        s32 rearGrip;
        VECTOR velocity;
        s32 frontForward;
        s32 unusedBC;
        s32 rearForward;
        s32 unusedC4;
        s32 frontSide;
        s32 unusedCC;
        s32 yawDivisor;
        s32 unusedD4;
        s32 drag;
        s32 unusedDC;
    } local;
    register s32 tableOffset asm("s1");
    register s32 steeringRaw asm("a0");
    register s32 steeringHalf asm("v1");
    s64 multiplyState;
    s64 yawMultiplyState;
    s64 velocityMultiplyState;
    s64 heightMultiplyState;
    s64 slideMultiplyState;
    register s32 initialDriverLoad asm("a0");
    register s32 initialDivisor asm("a1");
    register s32 slideYawDivisor asm("v0");
    register s32 forwardSpeed asm("s1");
    s32 averageGrip;
    s32 fixedValue;
    register s32 gripBase asm("v1");
    register s32 assist asm("v0");
    register s32 initialYaw asm("t0");
    register s32 rearHeading asm("s0");
    register s32 limitedRearHeading asm("s0");
    register s32 speedHigh asm("s1");
    s32 rearDriveHeading;
    register s32 *cosRow asm("a1");
    register s32 *sinRow asm("v0");
    s32 velocityX;
    register s32 speedCap asm("a0");
    register s32 frontLongitudinalSpeed asm("a1");
    register s32 rearLongitudinalSpeed asm("a1");
    register s32 rearDragValue asm("t1");
    register s32 baseSpeed asm("s0");
    register s32 frontDrag asm("s0");
    register s32 frontInverseHeading asm("s0");
    s32 frontXLocal;
    s32 frontYLocal;
    register s32 limitedFrontHeading asm("s0");
    s32 limitedFrontXProduct;
    s32 limitedFrontYProduct;
    register s32 rearIndex asm("s0");
    s32 rearYProduct;
    register s32 rearFourthProduct asm("v0");
    register s32 frontGripValue asm("a0");
    register s32 rearGripValue asm("a1");
    register s32 ratioHigh asm("t1");
    register s32 rearPositiveGrip asm("a0");
    register s32 firstCos asm("a0");
    register s32 frontXValue asm("a1");
    s32 rearXProduct;
    s32 rearYProductAfter;
    register s32 rearDrag asm("s0");
    register s32 rearInverseHeading asm("s0");
    s32 rearXLocal;
    s32 rearYLocal;
    s32 limitedRearXProduct;
    s32 limitedRearYProduct;
    register s32 frontOffset asm("s0");
    s32 frontYProduct;
    register s32 frontYBefore asm("s0");
    register s32 firstRandomRange asm("s0");
    register s32 frontHeading asm("s0");
    s32 frontXProduct;
    s32 frontYProductAfter;
    register s32 frontXProductBefore asm("s1");
    register s32 frontXBefore asm("s1");
    register s32 rearXProductBefore asm("s1");
    register s32 rearXBefore asm("s1");
    register s32 gripCos asm("s4");
    register s32 sideState asm("s7");
    s32 leaderDistance;
    s32 reverseSpeed;
    register s32 forwardSpeedFixed asm("v0");
    register s32 driveThreshold asm("v0");
    register s32 driveInputValue asm("v1");
    s32 limitedFrontX;
    s32 limitedRearX;
    register s32 tableIndex asm("v0");
    s32 dragScale;
    s32 rearLateralSpeed;
    register s32 turnTorque asm("v1");
    register s32 torqueReturn asm("v0");
    register s32 distanceAdjusted asm("a0");
    register s32 frontDriveScale asm("a0");
    register s32 rearDriveScale asm("a0");
    register s32 frontDriveDisabled asm("v0");
    register s32 frictionLimit asm("v0");
    register s32 headingValue asm("v0");
    register s32 cosBase asm("v1");
    register s32 frontDragValue asm("t0");
    s32 longitudinalDifference;
    register s32 yawDenominator asm("a0");
    s32 frontSin;
    s32 rearSin;
    s32 yawForce;
    register s32 deltaMagnitude asm("s0");
    register s32 angleDelta asm("s6");
    register s32 gripAngle asm("s0");
    register s32 secondRandomRange asm("s0");
    s32 frontDriveHeading;
    register s32 turnDelta asm("s0");
    register s32 frontFriction asm("s1");
    s32 frontDriveMagnitude;
    register s32 frontDragLimit asm("s1");
    register s32 rearFriction asm("s1");
    register s32 rearDriveMagnitude asm("s1");
    register s32 rearDragLimit asm("s1");
    register s32 turnMultiplier asm("s1");
    register s32 driveForce asm("s3");
    register s32 speedLimit asm("s5");
    register s32 turnLimit asm("s6");
    s32 dragTerm;
    s32 *sinAnchor;
    register s32 thirdTableAddress asm("v1");
    s32 frontGripMagnitude;
    s32 rearGripMagnitude;
    s32 newFineHeading;
    register s32 assistRankMinusOne asm("v1");
    s32 turnScale;
    register s32 forwardSpeedLocal asm("v1");
    register s32 assistScale asm("v0");
    register s32 assistBoost asm("t1");
    u32 velocitySumX;
    u32 velocitySumY;
    u8 *leader;
    register u8 *node asm("v0");
    asm("" : "=r"(car) : "0"(carBytes));
    initialYaw = D_800A2E5C;
    local.yawDivisor = initialYaw;
    func_8002D27C(carBytes);
    /* Compute the base speed and the signed division of the load term.
     * baseSpeed = base + speedBoost - (unk10E << 17)
     *             - (((unk2A6 + 1) * 75 << 16) / 15). */
    asm volatile("lh $v1,0x2A6(%5)\n\t"
                 "lui %2,0x8888\n\t"
                 "ori %2,%2,0x8889\n\t"
                 "addiu $v1,$v1,1\n\t"
                 "sll %1,$v1,2\n\t"
                 "addu %1,%1,$v1\n\t"
                 "sll $v1,%1,4\n\t"
                 "subu $v1,$v1,%1\n\t"
                 "sll $v1,$v1,16\n\t"
                 "mult $v1,%2\n\t"
                 "lui %0,%%hi(D_800A2E24)\n\t"
                 "lw %0,%%lo(D_800A2E24)(%0)\n\t"
                 "lw $a2,0x22C(%5)\n\t"
                 "lh %1,0x10E(%5)\n\t"
                 "li %3,16000\n\t"
                 "lw %2,0x28C(%5)\n\t"
                 "addu %0,%0,$a2\n\t"
                 "sll %1,%1,17\n\t"
                 "subu %0,%0,%1\n\t"
                 "mfhi $t1\n\t"
                 "addu %1,$t1,$v1\n\t"
                 "sra %1,%1,3\n\t"
                 "sra $v1,$v1,31\n\t"
                 "subu %1,%1,$v1"
                 : "=&r"(baseSpeed), "=&r"(tableIndex),
                   "=&r"(initialDriverLoad), "=&r"(initialDivisor),
                   "=x"(heightMultiplyState)
                 : "r"(car)
                 : "v1", "a2", "t1", "accum", "memory");
    baseSpeed -= tableIndex;
    assist = MathFixedDivide(initialDriverLoad, initialDivisor);
    gripBase = D_800A2E40;
    /* Scale the speed reduction. Keep its multiply result in LO until the
     * assist flag is loaded. */
    asm volatile("mult %1,%0\n\t"
                 "srl %1,%0,31\n\t"
                 "addu %0,%0,%1\n\t"
                 "sra %0,%0,1\n\t"
                 "sll %0,%0,16\n\t"
                 "lui %1,%%hi(D_800A2EE4)\n\t"
                 "lbu %1,%%lo(D_800A2EE4)(%1)\n\t"
                 "mflo %3\n\t"
                 "subu %0,%3,%0\n\t"
                 "subu %2,%2,%0"
                 : "=r"(gripBase), "=r"(assist), "=r"(baseSpeed),
                   "=r"(initialYaw), "=x"(multiplyState)
                 : "0"(gripBase), "1"(assist), "2"(baseSpeed)
                 : "accum");
    speedLimit = baseSpeed >> 16;
    car->maxSpeed = baseSpeed;
    if (assist != 0) {
        assistRankMinusOne = car->assistRank;
        if (assistRankMinusOne == 2) {
            assistRankMinusOne--;
            node = car->raceNode;
            goto nextCar;
        findCar:
            node = *((u8 **)(leader + 0x3E4));

        nextCar:
            leader = *((u8 **)(node + 8));

            if ((*((s16 *)(leader + 0x1EC))) != 0) {
                goto findCar;
            }
            leaderDistance = func_8003702C(leader, (u8 *)car);
            asm("" : "=r"(distanceAdjusted) : "0"(leaderDistance));
            if (((u32)(distanceAdjusted + 2)) < 0xAU) {
                distanceAdjusted -= 3;
                if (distanceAdjusted <= 0) {
                    distanceAdjusted = 0;
                }
                assistRankMinusOne = car->assistRank - 1;
                asm("" : "=r"(assistRankMinusOne) : "0"(assistRankMinusOne));
                assistScale = assistRankMinusOne * 20;
                asm("" : "=r"(assistScale) : "0"(assistScale));
                assistBoost = assistScale * distanceAdjusted;
                asm("" : "=r"(assistBoost) : "0"(assistBoost));
                speedLimit += assistBoost;
            } else {
                assistRankMinusOne = car->assistRank - 1;
                goto addAssistBoost;
            }
        } else {
            assistRankMinusOne--;
        addAssistBoost:
            speedLimit = speedLimit + assistRankMinusOne * 0x64;
        }
    }
    dragScale = car->dragScale;
    dragTerm = dragScale * 2;
    if (dragScale <= 0) {
        dragTerm = dragScale * 6;
    }
    local.drag = -dragTerm;
    steeringRaw = car->steering;
    steeringHalf = ((s16)steeringRaw) / 2;
    asm("negu %0,%1" : "=r"(sideState) : "r"(steeringHalf));
    tableIndex = ((car->heading - sideState) + 1024) & 1023;
    gripBase = 1024;
    steeringRaw = gFarCosTable.unk[0];
    gripBase -= tableIndex;
    asm("andi %0,%1,1023" : "=r"(frontOffset) : "r"(gripBase));
    frontOffset <<= 2;
    steeringRaw = frontOffset + steeringRaw;
    frontXProductBefore =
        MathMultiplyFixed16(*((s32 *)steeringRaw), car->frontVelocityX);
    frontXBefore =
        frontXProductBefore -
        MathMultiplyFixed16(*((s32 *)(frontOffset + gFarSinTable.unk[0])),
                            car->frontVelocityY);
    local.frontForward = frontXBefore;
    local.axleVelocity.vx = frontXBefore;
    thirdTableAddress = frontOffset + gFarSinTable.unk[0];
    asm("" : : "r"(thirdTableAddress));
    frontYProduct =
        MathMultiplyFixed16(*((s32 *)thirdTableAddress), car->frontVelocityX);
    frontYBefore =
        frontYProduct +
        MathMultiplyFixed16(*((s32 *)(frontOffset + gFarCosTable.unk[0])),
                            car->frontVelocityY);
    local.frontSide = frontYBefore;
    local.axleVelocity.vy = frontYBefore;
    if (MathGetAngleDelta(car->heading, car->movementHeading) < 0) {
        deltaMagnitude = -MathGetAngleDelta(car->heading, car->movementHeading);
    } else {
        deltaMagnitude = MathGetAngleDelta(car->heading, car->movementHeading);
    }
    turnScale = ((s32)car->speed) / ((s32)D_800A2E54);
    angleDelta = deltaMagnitude;
    if (turnScale < 0xF) {
        turnScale = 0xF;
    }
    gripAngle = deltaMagnitude * turnScale;
    if (gripAngle >= 0xFF) {
        gripAngle = 0xFE;
    }
    func_8002B9AC(car, &local.frontGrip, &local.rearGrip);
    averageGrip = (local.frontGrip + local.rearGrip) / 2;
    if (D_800A3598Physics[0] != 1) {
        yawForce = func_8002AAF0((u8 *)car, &local.force, averageGrip);
    } else {
        yawForce = 0;
    }
    tableIndex = gripAngle << 2;
    tableIndex += gFarCosTable.unk[0];
    asm("" : : "r"(tableIndex));
    gripCos = *((s32 *)tableIndex);
    if (MathMultiplyFixed16(local.frontGrip, gripCos) < 0) {
        frontGripMagnitude = -MathMultiplyFixed16(local.frontGrip, gripCos);
    } else {
        frontGripMagnitude = MathMultiplyFixed16(local.frontGrip, gripCos);
    }
    local.frontGrip = frontGripMagnitude;
    if (MathMultiplyFixed16(local.rearGrip, gripCos) < 0) {
        rearGripMagnitude = -MathMultiplyFixed16(local.rearGrip, gripCos);
    } else {
        rearGripMagnitude = MathMultiplyFixed16(local.rearGrip, gripCos);
    }
    local.rearGrip = rearGripMagnitude;
    car->sliding = 0;
    if (((((car->unkF4 != 0) && (car->callback != func_80025730)) &&
          (car->flags & 0x40)) &&
         (car->unk10C == 0))) {
        driveInputValue = car->driveInput;
        asm("li %0,0xC000" : "=r"(driveThreshold) : "r"(driveInputValue));
        if (driveInputValue <= driveThreshold) {
            goto noSliding;
        }
        speedHigh = *((s16 *)(((u8 *)car) + 0x92));
        if (speedHigh < 0x96) {
            /* Scale front and rear grip by (speedHigh + 50), then divide
             * the two signed products by 200 and 400. */
            asm volatile("lw $v1,%6\n\t"
                         "addiu %2,%5,50\n\t"
                         "mult $v1,%2\n\t"
                         "lw $a1,%7\n\t"
                         "mflo $v1\n\t"
                         "nop\n\t"
                         "nop\n\t"
                         "mult $a1,%2\n\t"
                         "mflo $a1\n\t"
                         "lui %2,0x51EB\n\t"
                         "ori %2,%2,0x851F\n\t"
                         "mult $v1,%2\n\t"
                         "mfhi $a3\n\t"
                         "nop\n\t"
                         "nop\n\t"
                         "mult $a1,%2\n\t"
                         "addiu %0,%5,1\n\t"
                         "addu %1,%0,$zero\n\t"
                         "sra $v1,$v1,31\n\t"
                         "sra %2,$a3,6\n\t"
                         "subu %2,%2,$v1\n\t"
                         "sra $a1,$a1,31\n\t"
                         "sw %2,%3\n\t"
                         "mfhi $a2\n\t"
                         "sra %2,$a2,7\n\t"
                         "subu %2,%2,$a1"
                         : "=&r"(firstRandomRange), "=&r"(steeringRaw),
                           "=&r"(tableIndex), "=m"(local.frontGrip),
                           "=x"(slideMultiplyState)
                         : "r"(speedHigh), "m"(local.frontGrip),
                           "m"(local.rearGrip)
                         : "v1", "a1", "a2", "a3", "accum", "memory");
            local.rearGrip = tableIndex;
            if (RandomScaledGet(steeringRaw) < 0) {
                if ((-RandomScaledGet(firstRandomRange)) >= 0xB) {
                    secondRandomRange = speedHigh + 1;
                } else {
                    goto firstSlideEvent;
                }
            } else {
                if (RandomScaledGet(firstRandomRange) < 0xB) {
                firstSlideEvent:
                    func_80029994((u8 *)car, 0);
                }
                secondRandomRange = speedHigh + 1;
            }
            if (RandomScaledGet(secondRandomRange) < 0) {
                if ((-RandomScaledGet(secondRandomRange)) >= 0xB) {
                } else {
                    goto secondSlideEvent;
                }
            } else if (RandomScaledGet(secondRandomRange) < 0xB) {
            secondSlideEvent:
                func_80029994((u8 *)car, 1);
            }
            slideYawDivisor = D_800A2E5C;
            asm("" : "=r"(slideYawDivisor) : "0"(slideYawDivisor));
            car->sliding = 1;
            local.yawDivisor = slideYawDivisor / 2;
        }
    }
noSliding:
    frontFriction = 0;
    if (local.axleVelocity.vy > 0) {
        frontFriction = -local.axleVelocity.vy;
        if (local.axleVelocity.vy >= local.frontGrip) {
            frontFriction = -local.frontGrip;
        }
    } else if (local.axleVelocity.vy < 0) {
        frictionLimit = local.frontGrip;
        asm("addu %0,%1,$zero" : "=&r"(frontFriction) : "r"(frictionLimit));
        if ((-frontFriction) < local.axleVelocity.vy) {
            frontFriction = -local.axleVelocity.vy;
        }
    }
    frontLongitudinalSpeed = local.axleVelocity.vx;
    asm volatile("" : : "r"(frontLongitudinalSpeed));
    frontDragValue = local.drag;
    asm("" : : "r"(frontDragValue));
    frontLongitudinalSpeed += frontDragValue;
    local.axleVelocity.vx = frontLongitudinalSpeed;
    local.axleVelocity.vy += frontFriction;
    sinAnchor = gFarSinTable.unk;
    headingValue = car->heading;
    cosBase = gFarCosTable.unk[0];
    headingValue = (headingValue - sideState) + 1024;
    asm("andi %0,%1,1023" : "=r"(frontHeading) : "r"(headingValue));
    tableOffset = frontHeading << 2;
    cosBase = tableOffset + cosBase;
    asm("" : : "r"(cosBase));
    frontXProduct =
        MathMultiplyFixed16(*((s32 *)cosBase), local.axleVelocity.vx);
    car->frontVelocityX =
        (s32)(frontXProduct -
              MathMultiplyFixed16(*((s32 *)(tableOffset + gFarSinTable.unk[0])),
                                  local.axleVelocity.vy));
    thirdTableAddress = tableOffset + sinAnchor[0];
    asm("" : : "r"(thirdTableAddress));
    frontYProductAfter =
        MathMultiplyFixed16(*((s32 *)thirdTableAddress), local.axleVelocity.vx);
    car->frontVelocityY =
        (s32)(frontYProductAfter +
              MathMultiplyFixed16(*((s32 *)(tableOffset + gFarCosTable.unk[0])),
                                  local.axleVelocity.vy));
    do {
        local.force.vy = 0;
        local.force.vx = 0;
        frontDriveDisabled = car->unk2AC;
        asm volatile("" : "=r"(driveForce) : "r"(frontDriveDisabled));
        driveForce = 0;
        if ((frontDriveDisabled != 0) || (car->unk2D4 != 0)) {
            local.rearGrip = 0;
        } else {
            driveForce = MathMultiplyFixed16(car->driveScale, car->driveInput);
        }
    } while (0);
    if (car->flags & 0x40) {
        if (D_800A2EB8[0] == 0) {
            frontDriveHeading = ((car->heading - sideState) + 0x400) & 0x3FF;
            frontDriveMagnitude = MathMultiplyFixed16(driveForce, gripCos);
        } else {
            MathMultiplyFixed16(
                driveForce,
                ((s32 *)gFarCosTable
                     .unk[0])[((car->heading - car->movementHeading) + 0x400) &
                              0x3FF]);
            MathMultiplyFixed16(
                driveForce,
                ((s32 *)gFarCosTable
                     .unk[0])[((car->heading - car->movementHeading) + 0x400) &
                              0x3FF]);
            frontDriveMagnitude = driveForce;
            frontDriveHeading = ((car->heading - sideState) + 0x400) & 0x3FF;
        }
        local.force.vx = MathMultiplyFixed16(
            frontDriveMagnitude,
            ((s32 *)gFarCosTable.unk[0])[frontDriveHeading]);
        frontSin = ((s32 *)gFarSinTable.unk[0])[frontDriveHeading];
        frontDriveScale = frontDriveMagnitude;
        goto addFrontForce;
    }
    frontDragLimit = 0x10000;
    if (local.axleVelocity.vx > 0) {
        if (local.axleVelocity.vx < frontDragLimit) {
            frontDragLimit = local.axleVelocity.vx;
        }
        frontDrag = -frontDragLimit;
        local.force.vx = MathMultiplyFixed16(
            frontDrag, ((s32 *)gFarCosTable.unk[0])[car->heading]);
        frontSin = ((s32 *)gFarSinTable.unk[0])[car->heading];
        asm("addu %0,%1,$zero"
            : "=r"(frontDriveScale)
            : "r"(frontDrag), "r"(frontSin));
    addFrontForce:
        local.force.vy = MathMultiplyFixed16(frontDriveScale, frontSin);
    }
    /* Add the front force, then form the inverse axle angle and table row.
     * The address pins retain the retail load order around the car stores. */
    asm volatile("lw $v0,0xC4(%4)\n\t"
                 "lw $v1,%5\n\t"
                 "lw %0,0xC8(%4)\n\t"
                 "li $t1,1024\n\t"
                 "addu $v0,$v0,$v1\n\t"
                 "sw $v0,0xC4(%4)\n\t"
                 "lh $v0,0x114(%4)\n\t"
                 "lw %1,0xC4(%4)\n\t"
                 "lw $a2,%6\n\t"
                 "lui $v1,%%hi(D_800A3A2C)\n\t"
                 "lw $v1,%%lo(D_800A3A2C)($v1)\n\t"
                 "subu $v0,$v0,%7\n\t"
                 "addiu $v0,$v0,1024\n\t"
                 "andi $v0,$v0,1023\n\t"
                 "subu $v0,$t1,$v0\n\t"
                 "andi %2,$v0,1023\n\t"
                 "addu %0,%0,$a2\n\t"
                 "sll %3,%2,2\n\t"
                 "addu $v1,%3,$v1\n\t"
                 "sw %0,0xC8(%4)\n\t"
                 "lw %0,0($v1)"
                 : "=&r"(firstCos), "=&r"(frontXValue),
                   "=&r"(frontInverseHeading), "=&r"(tableOffset)
                 : "r"(car), "m"(local.force.vx), "m"(local.force.vy),
                   "r"(sideState)
                 : "v0", "v1", "a2", "t1", "memory");
    frontXLocal = MathMultiplyFixed16(firstCos, frontXValue);
    local.axleVelocity.vx =
        frontXLocal -
        MathMultiplyFixed16(*((s32 *)(tableOffset + gFarSinTable.unk[0])),
                            car->frontVelocityY);
    thirdTableAddress = tableOffset + gFarSinTable.unk[0];
    asm("" : : "r"(thirdTableAddress));
    frontYLocal =
        MathMultiplyFixed16(*((s32 *)thirdTableAddress), car->frontVelocityX);
    local.axleVelocity.vy =
        frontYLocal +
        MathMultiplyFixed16(*((s32 *)(tableOffset + gFarCosTable.unk[0])),
                            car->frontVelocityY);
    forwardSpeed = ((s16 *)(&local.axleVelocity.vx))[1];
    if (speedLimit < forwardSpeed) {
        limitedFrontX = MathMultiplyFixed16(
            MathFixedDivide(speedLimit, forwardSpeed), local.axleVelocity.vx);
        local.axleVelocity.vx = limitedFrontX;
        gripBase = car->heading;
        steeringRaw = gFarCosTable.unk[0];
        gripBase = (gripBase - sideState) + 1024;
        asm("andi %0,%1,1023" : "=r"(limitedFrontHeading) : "r"(gripBase));
        tableOffset = limitedFrontHeading << 2;
        asm("addu %0,%1,%0"
            : "=r"(steeringRaw)
            : "r"(tableOffset), "0"(steeringRaw));
        limitedFrontXProduct =
            MathMultiplyFixed16(*((s32 *)steeringRaw), limitedFrontX);
        fixedValue =
            MathMultiplyFixed16(*((s32 *)(tableOffset + gFarSinTable.unk[0])),
                                local.axleVelocity.vy);
        gripBase = gFarSinTable.unk[0];
        asm("" : : "r"(gripBase));
        car->frontVelocityX = limitedFrontXProduct - fixedValue;
        frontXValue = local.axleVelocity.vx;
        asm("addu %0,%1,%0"
            : "=r"(gripBase)
            : "r"(tableOffset), "0"(gripBase), "r"(frontXValue));
        limitedFrontYProduct =
            MathMultiplyFixed16(*((s32 *)gripBase), frontXValue);
        car->frontVelocityY =
            (s32)(limitedFrontYProduct +
                  MathMultiplyFixed16(
                      *((s32 *)(tableOffset + gFarCosTable.unk[0])),
                      local.axleVelocity.vy));
    }
    headingValue = car->heading;
    frontXValue = car->rearVelocityX;
    asm volatile("" : : "r"(headingValue), "r"(frontXValue));
    cosBase = gFarCosTable.unk[0];
    initialYaw = 1024;
    asm("" : "=r"(initialYaw) : "0"(initialYaw));
    headingValue = initialYaw - headingValue;
    asm("andi %0,%1,1023" : "=r"(rearIndex) : "r"(headingValue));
    rearIndex <<= 2;
    cosBase = rearIndex + cosBase;
    asm("" : : "r"(cosBase));
    rearXProductBefore = MathMultiplyFixed16(*((s32 *)cosBase), frontXValue);
    rearXBefore =
        rearXProductBefore -
        MathMultiplyFixed16(*((s32 *)(rearIndex + gFarSinTable.unk[0])),
                            car->rearVelocityY);
    local.rearForward = rearXBefore;
    local.axleVelocity.vx = rearXBefore;
    thirdTableAddress = rearIndex + gFarSinTable.unk[0];
    asm("" : : "r"(thirdTableAddress));
    rearYProduct =
        MathMultiplyFixed16(*((s32 *)thirdTableAddress), car->rearVelocityX);
    rearFourthProduct = MathMultiplyFixed16(
        *((s32 *)(rearIndex + gFarCosTable.unk[0])), car->rearVelocityY);
    asm("addu %0,%1,%2"
        : "=&r"(sideState)
        : "r"(rearYProduct), "r"(rearFourthProduct));
    local.axleVelocity.vy = sideState;
    rearGripValue = local.rearGrip;
    frontGripValue = local.frontGrip;
    asm("" : : "r"(rearGripValue), "r"(frontGripValue));
    if (rearGripValue < frontGripValue) {
        /* Scale yaw by the grip difference, with a limit of 2000.
         * yawForce = yawForce * min((frontGrip - rearGrip) / 170, 2000)
         *            / 1000. The retail block keeps the product in LO. */
        asm volatile("lui %0,0x6060\n\t"
                     "ori %0,%0,0x6061\n\t"
                     "subu %1,%6,%7\n\t"
                     "mult %1,%0\n\t"
                     "sra %1,%1,31\n\t"
                     "mfhi %2\n\t"
                     "sra %0,%2,6\n\t"
                     "subu %0,%0,%1\n\t"
                     "slti %1,%0,2001\n\t"
                     "bnez %1,1f\n\t"
                     "mult %4,%0\n\t"
                     "li %0,2000\n\t"
                     "mult %4,%0\n"
                     "1:\n\t"
                     "mflo %1\n\t"
                     "lui %0,0x1062\n\t"
                     "ori %0,%0,0x4DD3\n\t"
                     "mult %1,%0\n\t"
                     "sra %1,%1,31\n\t"
                     "mfhi %3\n\t"
                     "sra %0,%3,6\n\t"
                     "subu %4,%0,%1"
                     : "=r"(gripBase), "=r"(tableIndex), "=r"(ratioHigh),
                       "=r"(initialYaw), "=r"(yawForce), "=x"(yawMultiplyState)
                     : "r"(frontGripValue), "r"(rearGripValue), "4"(yawForce)
                     : "accum", "memory");
    }
    rearFriction = 0;
    rearLateralSpeed = *((volatile s32 *)&local.axleVelocity.vy) + yawForce;
    local.axleVelocity.vy = rearLateralSpeed;
    if (rearLateralSpeed > 0) {
        rearPositiveGrip = *((volatile s32 *)&local.rearGrip);
        asm("" : : "r"(rearPositiveGrip));
        rearFriction = -rearLateralSpeed;
        if (rearLateralSpeed >= rearPositiveGrip) {
            rearFriction = -rearPositiveGrip;
        }
    } else if (rearLateralSpeed < 0) {
        frictionLimit = *((volatile s32 *)&local.rearGrip);
        asm("addu %0,%1,$zero" : "=&r"(rearFriction) : "r"(frictionLimit));
        if ((-rearFriction) < rearLateralSpeed) {
            rearFriction = -rearLateralSpeed;
        }
    }
    if (local.axleVelocity.vx < 0) {
        local.axleVelocity.vx = MathMultiplyFixed16(
            local.axleVelocity.vx, MathFixedDivide(0x1F, 0x20));
    }
    rearLongitudinalSpeed = local.axleVelocity.vx;
    asm volatile("" : : "r"(rearLongitudinalSpeed));
    rearDragValue = local.drag;
    asm("" : : "r"(rearDragValue));
    rearLongitudinalSpeed += rearDragValue;
    local.axleVelocity.vx = rearLongitudinalSpeed;
    local.axleVelocity.vy += rearFriction;
    rearHeading = car->heading;
    tableOffset = rearHeading << 2;
    rearXProduct = MathMultiplyFixed16(
        *((s32 *)(tableOffset + gFarCosTable.unk[0])), local.axleVelocity.vx);
    fixedValue = MathMultiplyFixed16(
        *((s32 *)(tableOffset + gFarSinTable.unk[0])), local.axleVelocity.vy);
    gripBase = gFarSinTable.unk[0];
    asm("" : : "r"(gripBase));
    car->rearVelocityX = rearXProduct - fixedValue;
    frontXValue = local.axleVelocity.vx;
    asm("addu %0,%1,%0"
        : "=r"(gripBase)
        : "r"(tableOffset), "0"(gripBase), "r"(frontXValue));
    rearYProductAfter = MathMultiplyFixed16(*((s32 *)gripBase), frontXValue);
    car->rearVelocityY =
        (s32)(rearYProductAfter +
              MathMultiplyFixed16(*((s32 *)(tableOffset + gFarCosTable.unk[0])),
                                  local.axleVelocity.vy));
    *((Vec3 *)D_800A453CPhysics) = *((Vec3 *)(&local.force));
    local.force.vy = 0;
    local.force.vx = 0;
    if (car->flags & 0x40) {
        if (D_800A2EB8[0] == 0) {
            if (MathGetAngleDelta(car->heading, car->movementHeading) < 0) {
                register s32 deadDeltaReturn asm("v0");
                deadDeltaReturn =
                    MathGetAngleDelta(car->heading, car->movementHeading);
                /* End the previous s0 lifetime before the negative result. */
                asm volatile("" : "=r"(deltaMagnitude));
                deltaMagnitude = -deadDeltaReturn;
            } else {
                deltaMagnitude =
                    MathGetAngleDelta(car->heading, car->movementHeading);
            }
            asm("" : : "r"(deltaMagnitude));
            rearDriveHeading = car->movementHeading;
            rearDriveMagnitude = MathMultiplyFixed16(driveForce, gripCos);
        } else {
            MathMultiplyFixed16(
                driveForce,
                ((s32 *)gFarCosTable
                     .unk[0])[((car->heading - car->movementHeading) + 0x400) &
                              0x3FF]);
            MathMultiplyFixed16(
                driveForce,
                ((s32 *)gFarCosTable
                     .unk[0])[((car->heading - car->movementHeading) + 0x400) &
                              0x3FF]);
            rearDriveMagnitude = driveForce;
            rearDriveHeading = car->heading;
        }
        asm("" : : "r"(rearDriveMagnitude));
        local.force.vx = MathMultiplyFixed16(
            rearDriveMagnitude, ((s32 *)gFarCosTable.unk[0])[rearDriveHeading]);
        rearSin = ((s32 *)gFarSinTable.unk[0])[rearDriveHeading];
        rearDriveScale = rearDriveMagnitude;
        goto addRearForce;
    }
    rearDragLimit = 0x10000;
    if (local.axleVelocity.vx > 0) {
        if (local.axleVelocity.vx < rearDragLimit) {
            rearDragLimit = local.axleVelocity.vx;
        }
        rearDrag = -rearDragLimit;
        local.force.vx = MathMultiplyFixed16(
            rearDrag, ((s32 *)gFarCosTable.unk[0])[car->heading]);
        rearSin = ((s32 *)gFarSinTable.unk[0])[car->heading];
        asm("addu %0,%1,$zero"
            : "=r"(rearDriveScale)
            : "r"(rearDrag), "r"(rearSin));
    addRearForce:
        local.force.vy = MathMultiplyFixed16(rearDriveScale, rearSin);
    }
    /* Add the rear force and select the inverse heading row. */
    asm volatile("lw $v0,0xD0(%4)\n\t"
                 "lw $v1,%5\n\t"
                 "lw %0,0xD4(%4)\n\t"
                 "lh $a2,0x114(%4)\n\t"
                 "addu $v0,$v0,$v1\n\t"
                 "sw $v0,0xD0(%4)\n\t"
                 "lw %1,0xD0(%4)\n\t"
                 "lw $a3,%6\n\t"
                 "li $v0,1024\n\t"
                 "lui $v1,%%hi(D_800A3A2C)\n\t"
                 "lw $v1,%%lo(D_800A3A2C)($v1)\n\t"
                 "subu $v0,$v0,$a2\n\t"
                 "andi %2,$v0,1023\n\t"
                 "sll %3,%2,2\n\t"
                 "addu %0,%0,$a3\n\t"
                 "addu $v1,%3,$v1\n\t"
                 "sw %0,0xD4(%4)\n\t"
                 "lw %0,0($v1)"
                 : "=&r"(firstCos), "=&r"(frontXValue),
                   "=&r"(rearInverseHeading), "=&r"(tableOffset)
                 : "r"(car), "m"(local.force.vx), "m"(local.force.vy)
                 : "v0", "v1", "a2", "a3", "memory");
    rearXLocal = MathMultiplyFixed16(firstCos, frontXValue);
    local.axleVelocity.vx =
        rearXLocal -
        MathMultiplyFixed16(*((s32 *)(tableOffset + gFarSinTable.unk[0])),
                            car->rearVelocityY);
    thirdTableAddress = tableOffset + gFarSinTable.unk[0];
    asm("" : : "r"(thirdTableAddress));
    rearYLocal =
        MathMultiplyFixed16(*((s32 *)thirdTableAddress), car->rearVelocityX);
    local.axleVelocity.vy =
        rearYLocal +
        MathMultiplyFixed16(*((s32 *)(tableOffset + gFarCosTable.unk[0])),
                            car->rearVelocityY);
    forwardSpeed = ((s16 *)(&local.axleVelocity.vx))[1];
    if (speedLimit < forwardSpeed) {
        limitedRearX = MathMultiplyFixed16(
            MathFixedDivide(speedLimit, forwardSpeed), local.axleVelocity.vx);
        local.axleVelocity.vx = limitedRearX;
        limitedRearHeading = car->heading;
        tableOffset = limitedRearHeading << 2;
        limitedRearXProduct = MathMultiplyFixed16(
            *((s32 *)(tableOffset + gFarCosTable.unk[0])), limitedRearX);
        fixedValue =
            MathMultiplyFixed16(*((s32 *)(tableOffset + gFarSinTable.unk[0])),
                                local.axleVelocity.vy);
        asm("lui %0,%%hi(D_800A3A34)\n\tlw %0,%%lo(D_800A3A34)(%0)"
            : "=r"(gripBase));
        car->rearVelocityX = limitedRearXProduct - fixedValue;
        frontXValue = local.axleVelocity.vx;
        asm("addu %0,%1,%0"
            : "=r"(gripBase)
            : "r"(tableOffset), "0"(gripBase), "r"(frontXValue));
        limitedRearYProduct =
            MathMultiplyFixed16(*((s32 *)gripBase), frontXValue);
        car->rearVelocityY =
            (s32)(limitedRearYProduct +
                  MathMultiplyFixed16(
                      *((s32 *)(tableOffset + gFarCosTable.unk[0])),
                      local.axleVelocity.vy));
    }
    /* Save the axle velocities before the heading update. */
    asm volatile("lw %1,0xC4(%5)\n\t"
                 "lw $t0,%6\n\t"
                 "lw $t1,%7\n\t"
                 "sw %1,%2\n\t"
                 "lw %1,0xC8(%5)\n\t"
                 "nop\n\t"
                 "sw %1,%3\n\t"
                 "lw %1,0xD0(%5)\n\t"
                 "nop\n\t"
                 "sw %1,%4\n\t"
                 "lw %1,0xD4(%5)\n\t"
                 "subu %0,$t0,$t1"
                 : "=&r"(steeringRaw), "=&r"(tableIndex),
                   "=m"(local.frontVelocity.vx), "=m"(local.frontVelocity.vy),
                   "=m"(local.rearVelocity.vx)
                 : "r"(car), "m"(local.frontForward), "m"(local.rearForward)
                 : "t0", "t1", "memory");
    longitudinalDifference = steeringRaw;
    local.rearVelocity.vy = tableIndex;
    if (longitudinalDifference < 0) {
        longitudinalDifference += 0x3F;
    }
    turnMultiplier = longitudinalDifference >> 6;
    if (turnMultiplier <= 0xFFFF) {
        turnMultiplier = 0x10000;
    }
    initialYaw = local.frontSide;
    asm("" : : "r"(initialYaw));
    torqueReturn = MathMultiplyFixed16(initialYaw - sideState, turnMultiplier);
    yawDenominator = local.yawDivisor;
    asm volatile(""
                 : "=r"(turnTorque)
                 : "r"(torqueReturn), "r"(yawDenominator));
    turnTorque = torqueReturn;
    if (yawDenominator < 0) {
        yawDenominator += 3;
    }
    tableIndex = angleDelta << 2;
    asm("" : : "r"(tableIndex));
    turnLimit = tableIndex + 16;
    tableIndex = yawDenominator >> 2;
    asm("" : : "r"(tableIndex), "r"(turnTorque));
    turnDelta = turnTorque / tableIndex;
    if (turnLimit >= 0x41) {
        turnLimit = 0x40;
    }
    if (turnDelta >= 0) {
        if (turnLimit < turnDelta) {
            goto clampTurn;
        }
    } else if (turnLimit < (-turnDelta)) {
    clampTurn:
        if (turnDelta > 0) {
            turnDelta = turnLimit;
        } else {
            turnDelta = -turnLimit;
        }
    }
    newFineHeading = ((car->fineHeading + turnDelta) + 0x1000) & 0xFFF;
    asm("" : "=r"(newFineHeading) : "0"(newFineHeading));
    car->fineHeading = (u16)newFineHeading;
    if (newFineHeading < 0) {
        newFineHeading += 3;
    }
    car->heading = (s16)(newFineHeading >> 2);
    func_8002AF94(car);
    velocitySumX = ((s32)local.frontVelocity.vx) + ((s32)local.rearVelocity.vx);
    car->velocityX =
        (s32)(((s32)(velocitySumX + (velocitySumX >> 0x1F))) >> 0x11);
    velocityX = *((volatile s32 *)(((u8 *)car) + 0xB0));
    velocitySumY = local.frontVelocity.vy + local.rearVelocity.vy;
    car->velocityY =
        (s32)(((s32)(velocitySumY + (velocitySumY >> 0x1F))) >> 0x11);
    if (((velocityX >= 0) ? (velocityX < 3) : ((-velocityX) < 3)) &&
        ((car->velocityY >= 0) ? (car->velocityY < 3)
                               : ((-car->velocityY) < 3))) {
        car->velocityY = 0;
        car->velocityX = 0;
    }
    car->movementHeading = func_800358EC((s32 *)(((u8 *)car) + 0xB0));
    gripBase = car->heading;
    tableIndex = 1024;
    asm volatile("" : : "r"(gripBase), "r"(tableIndex));
    cosRow = (s32 *)gFarCosTable.unk[0];
    tableIndex = (tableIndex - gripBase) & 1023;
    tableIndex <<= 2;
    asm("addu %0,%1,%0" : "=r"(cosRow) : "r"(tableIndex), "0"(cosRow));
    /* Project world velocity onto the car's forward and side axes.
     * The forward value is shifted after the four integer products. */
    asm volatile("lw $a0,0(%2)\n\t"
                 "lw %0,0xB0(%7)\n\t"
                 "nop\n\t"
                 "mult $a0,%0\n\t"
                 "lui %0,%%hi(D_800A3A34)\n\t"
                 "lw %0,%%lo(D_800A3A34)(%0)\n\t"
                 "nop\n\t"
                 "addu %1,%1,%0\n\t"
                 "lw $a0,0(%1)\n\t"
                 "lw %0,0xB4(%7)\n\t"
                 "mflo $a2\n\t"
                 "nop\n\t"
                 "nop\n\t"
                 "mult $a0,%0\n\t"
                 "mflo %0\n\t"
                 "subu %0,$a2,%0\n\t"
                 "sra %0,%0,16\n\t"
                 "sw %0,%3\n\t"
                 "lw $a0,0(%1)\n\t"
                 "lw %1,0xB0(%7)\n\t"
                 "nop\n\t"
                 "mult $a0,%1\n\t"
                 "lw $a0,0(%2)\n\t"
                 "lw %1,0xB4(%7)\n\t"
                 "mflo $a2\n\t"
                 "nop\n\t"
                 "nop\n\t"
                 "mult $a0,%1\n\t"
                 "mflo $a3\n\t"
                 "addu %1,$a2,$a3\n\t"
                 "sra %1,%1,16"
                 : "=&r"(forwardSpeedLocal), "=r"(sinRow), "=r"(cosRow),
                   "=m"(local.velocity.vx), "=x"(velocityMultiplyState)
                 : "2"(cosRow), "1"(tableIndex), "r"(car)
                 : "a0", "a2", "a3", "accum", "memory");
    local.velocity.vy = (s32)sinRow;
    if (forwardSpeedLocal < 0) {
        reverseSpeed = -forwardSpeedLocal;
        car->reverseSpeed = (s8)reverseSpeed;
        forwardSpeedLocal = 0;
        if (((u32)(reverseSpeed & 0xFF)) >= 0x65U) {
            car->reverseSpeed = 0x64;
        }
    } else {
        car->reverseSpeed = 0;
    }
    speedCap = car->maxSpeed;
    forwardSpeedFixed = forwardSpeedLocal << 0x10;
    asm("" : : "r"(speedCap), "r"(forwardSpeedFixed));
    car->speed = forwardSpeedFixed;
    if (speedCap < forwardSpeedFixed) {
        car->speed = speedCap;
    }
}

s32 func_8002CF1C(void) {
    return 2000;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002CF24);

s32 func_8003702C(u8 *, u8 *);
s32 func_8002CF24(u8 *, u8 *);

void func_8002D16C(u8 *arg0) {
    u8 *other;
    s32 flag;
    s32 flag40;
    s32 value;
    s32 newValue;

    *(u8 *)(arg0 + 0x3FC) = 0;
    if (0x8BFFFF < *(s32 *)(arg0 + 0x90)) {
        if (D_800A2E94[0] >= 2) {
            other = *(u8 **)(*(s32 *)(arg0 + 0x3F0) + 8);
            if (other != 0) {
                flag = 1;
                flag40 = 0x28;
                do {
                    if (arg0 == other) {
                        goto decay;
                    }
                    if (func_8003702C(arg0, other) < -0xA) {
                        goto decay;
                    }
                    if ((func_8002CF24(arg0, other) & 0xFF) != 0) {
                        *(u8 *)(arg0 + 0x3FC) = flag;
                        if (*(s16 *)(other + 0x1EC) == 0) {
                            return;
                        }
                        *(u8 *)(other + 0x3FC) = flag40;
                        return;
                    }
                    other = *(u8 **)(*(s32 *)(other + 0x3F0) + 8);
                } while (other != 0);
            }
        decay:
            value = *(s32 *)(arg0 + 0x22C);
            if (value > 0) {
                newValue = value - 0x8000;
                *(s32 *)(arg0 + 0x22C) = newValue;
                if (newValue < 0) {
                    *(s32 *)(arg0 + 0x22C) = 0;
                }
            }
            return;
        }
        *(s32 *)(arg0 + 0x22C) = 0;
    }
}

void func_8002D27C(u8 *arg0) {
    s32 value;

    if (!(0x9FFFF < *(s32 *)(arg0 + 0x90))) {
        *(s16 *)(arg0 + 0x120) = 0;
        *(s16 *)(arg0 + 0x11E) = 0;
    } else {
        if (*(s16 *)(arg0 + 0x120) > 0) {
            *(s16 *)(arg0 + 0x120) = *(s16 *)(arg0 + 0x120) - 1;
            value = RandomScaledGet(4);
            if (value < 0) {
                value = -RandomScaledGet(4);
            } else {
                value = RandomScaledGet(4);
            }
            func_80029994(arg0, value);
        }
        if (*(s32 *)(arg0 + 0x238) & 0x80) {
            if (*(s8 *)(arg0 + 0x3C4) == 4) {
                *(u16 *)(arg0 + 0x11E) += 1;
            } else {
                if (*(s32 *)(arg0 + 0x3C0) >= MathFixedDivide(0xFA, 0x7D0)) {
                    *(u16 *)(arg0 + 0x11E) += 1;
                }
            }
        } else {
            *(s16 *)(arg0 + 0x11E) = 0;
        }
        if (*(s16 *)(arg0 + 0x11E) >= 0x13) {
            *(s16 *)(arg0 + 0x120) = 0x23;
            *(s16 *)(arg0 + 0x11E) = 0;
        }
    }
}

extern s32 D_800A2E84;
u8 *func_8002D380(void) {
    s32 index;
    index = D_800A2E84++;
    return (u8 *)D_800A3984[0] + index * 0x500;
}

extern u8 D_800AE88C[];
void func_8002D3A8(u8 *object, s32 index) {
    u8 *data;
    if (index < 0) {
        index = -index;
        data = D_800AE88C + index * 0x44;
    } else {
        data = D_800AE88C;
    }
    *(u8 **)(object + 0x370) = data;
    *(u8 **)(object + 0x36C) = data;
    object[0x374] = 0;
    object[0x200] = index;
}

extern s32 D_800A2E7Cgp asm("D_800A2E7C.NON_MATCHING");
extern s32 D_800A2E80gp asm("D_800A2E80.NON_MATCHING");

void func_8002D3EC(u8 *arg0) {
    u8 *entry;
    s32 i;
    s32 diff;

    diff = D_800A2E7Cgp - D_800A2E80gp;
    i = diff;
    *(s32 *)(arg0 + 0x234) =
        D_800A2E80gp + i * (s8)D_800A3860[*(s8 *)(arg0 + 0x20B)][0] / 63;
    diff = D_800A2E64[0] - (s8)D_800A3860[*(s8 *)(arg0 + 0x20B)][0] * 0xC8 / 63;
    entry = arg0;
    i = 0;
    do {
        *(s16 *)(arg0 + i * 0x28 + 0x2B2) = 0;
        *(s16 *)(arg0 + i * 0x28 + 0x2B0) = 0;
        *(s16 *)(arg0 + i * 0x28 + 0x2AE) = 0;
        *(s16 *)(arg0 + i * 0x28 + 0x2B4) = diff;
        *(s32 *)(arg0 + i * 0x28 + 0x2B8) = *(s32 *)(arg0 + 0x234);
        i += 1;
        entry += 0x28;
    } while (i < 4);
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002D4CC);

typedef struct PoolObject {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u8 pad0C[0x1DE - 0x0C];
    s16 unk1DE;
    u8 pad1E0[0x1EC - 0x1E0];
    s16 type;
    u8 pad1EE[0x200 - 0x1EE];
    u8 unk200;
    u8 pad201[3];
    u8 unk204;
    u8 unk205;
    u8 pad206[0x20B - 0x206];
    u8 unk20B;
    u8 pad20C[0x28A - 0x20C];
    s16 unk28A;
    u8 pad28C[0x350 - 0x28C];
    u32 update;
    u32 unk354;
    u8 pad358[0x36C - 0x358];
    u8 *unk36C;
    u8 *unk370;
    u8 unk374;
    u8 pad375[0x3C9 - 0x375];
    u8 unk3C9;
    u8 pad3CA[0x500 - 0x3CA];
} PoolObject;

PoolObject *func_8002D874(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 D_800A2E88;
    extern s32 D_800A2E94Lui asm("D_800A2E94Absolute");
    extern s32 D_800A2EB4Lui asm("D_800A2EB4Absolute");
    extern struct {
        u32 unk0;
        u32 unk4;
        u32 unk8;
        s16 unkC;
        s16 unkE;
    } D_800BE72C[];
    extern void CarUpdatePlayer(u8 *);
    extern void func_800373B4(u8 *);
    extern void func_80029E34(void);
    extern void func_80025594(u8 *);
    extern void func_8002D4CC();
    PoolObject *entry;
    /* Retail stores the tail fields through the return register: obj is
     * v0 from the copy on. No plain-C spelling found yet. */
    register PoolObject *obj asm("$2");
    u8 *data;
    s32 index;
    s32 b;
    s32 w;

    index = D_800A2E84++;
    entry = (PoolObject *)((u8 *)D_800A3984[0] + index * 0x500);
    if (arg3 < 0) {
        arg3 = -arg3;
        data = D_800AE88C + arg3 * 0x44;
    } else {
        data = D_800AE88C;
    }
    entry->unk370 = data;
    entry->unk36C = data;
    entry->unk374 = 0;
    entry->unk200 = arg3;
    func_8002DA30((s32 *)entry);
    entry->type = arg0;
    if (arg0 == 0) {
        entry->update = (u32)CarUpdatePlayer;
        D_800A2EB4Lui = D_800A2EB4Lui + 1;
    } else if (arg0 == 1) {
        entry->update = (u32)func_800373B4;
    } else {
        entry->update = (u32)func_80029E34;
    }
    entry->unk354 = (u32)func_80025594;
    entry->unk0 = D_800BE72C[arg1].unk0;
    entry->unk4 = D_800BE72C[arg1].unk4;
    entry->unk8 = 0;
    if (arg0 == 0) {
        entry->unk20B = D_800A2E88++;
    }
    func_8002D4CC(entry);
    func_80028754((u8 *)entry, 5);
    func_80022FB8((u8 *)entry, D_800BE72C[arg1].unkC);
    w = D_800A2E94Lui;
    b = arg1 + 1;
    entry->unk204 = b;
    entry->unk205 = b;
    entry->unk3C9 = b;
    obj = entry;
    obj->unk28A = arg2;
    obj->unk1DE = w;
    D_800A2E94Lui = D_800A2E94Lui + 1;
    return obj;
}

void func_8002DA30(s32 *arg0) {
    arg0[0x3C / 4] = 0x10000;
    arg0[0x18 / 4] = 0x10000;
    arg0[0x4C / 4] = 0x10000;
    arg0[0x28 / 4] = 0x10000;
    arg0[0x5C / 4] = 0x10000;
    arg0[0x38 / 4] = 0x10000;
    arg0[0x24 / 4] = 0;
    arg0[0x20 / 4] = 0;
    arg0[0x1C / 4] = 0;
    arg0[0x34 / 4] = 0;
    arg0[0x30 / 4] = 0;
    arg0[0x2C / 4] = 0;
    arg0[0x48 / 4] = 0;
    arg0[0x44 / 4] = 0;
    arg0[0x40 / 4] = 0;
    arg0[0x58 / 4] = 0;
    arg0[0x54 / 4] = 0;
    arg0[0x50 / 4] = 0;
}

extern void HeapFree(void *ptr);
extern void *D_800BE980_w42[] asm("D_800BE980.NON_MATCHING");
extern void *D_800A3A40_w42[] asm("D_800A3A40.NON_MATCHING");
extern void *D_800A39A4_w42[] asm("D_800A39A4.NON_MATCHING");
extern void *D_800A3A8C_w42[] asm("D_800A3A8C.NON_MATCHING");
extern void *D_800A39A4Absolute[];
extern void *D_800A3A8CAbsolute[];
extern void *D_800B60A4_w42[] asm("D_800B60A4.NON_MATCHING");
extern u8 D_800AE8A0_w42[] asm("D_800AE8A0.NON_MATCHING");
extern u8 D_800AE8C4_w42[] asm("D_800AE8C4.NON_MATCHING");
extern u8 D_800AE8CC_w42[] asm("D_800AE8CC.NON_MATCHING");
extern u8 D_800AE8A0p[] asm("D_800AE8A0");
extern u8 D_800AE8CCp[] asm("D_800AE8CC");
extern s32 D_800A2F54_w42[] asm("D_800A2F54.NON_MATCHING");
extern s32 D_800A3630_w42b asm("D_800A3630.NON_MATCHING");
extern s32 D_800A2EC8Small;
extern s32 D_800A2ED4_w42 asm("D_800A2ED4.NON_MATCHING");

extern s32 D_800A3A38Lui asm("D_800A3A38Absolute");
void func_8002DA80(void) {
    void **p;
    u8 *q;
    s32 off;
    s32 i;
    void *ptr;
    s32 pad[2];

    i = 0;
    p = D_800BE97C;
    HeapFree(p[0]);
    ptr = D_800A3A40_w42[0];
    p[0] = 0;
    HeapFree(ptr);
    D_800A3A40Absolute[0] = 0;
    HeapFree(D_800A39A4_w42[0]);
    D_800A39A4Absolute[0] = 0;
    HeapFree(D_800BE980_w42[0]);
    D_800BE97C[1] = 0;
    HeapFree((void *)D_800A3A38Lui);
    D_800A3A38Lui = 0;
    HeapFree(D_800A3A8C_w42[0]);
    D_800A3A8CAbsolute[0] = 0;
    p = D_800B60A4_w42;
    do {
        if (p[0] != 0) {
            HeapFree(p[0]);
            p[0] = 0;
        }
        i += 1;
        p += 1;
    } while (i < 2);

    i = 0;
    if (D_800A3630_w42b * 5 > 0) {
        q = D_800AE8C4_w42;
        do {
            off = i * 0x44;
            if (i < 5) {
                HeapFree(*(void **)(D_800AE8A0_w42 + off));
                *(void **)(D_800AE8A0p + off) = 0;
            }
            HeapFree(*(void **)q);
            *(void **)q = 0;
            if (*(void **)(D_800AE8CC_w42 + off) != 0) {
                HeapFree(*(void **)(D_800AE8CC_w42 + off));
                *(void **)(D_800AE8CCp + off) = 0;
            }
            q += 0x44;
            i += 1;
        } while (i < D_800A3630_w42b * 5);
    }
    D_800A2EC8Small = 0;
    D_800A2ED4_w42 = 0;
    D_800A2F54_w42[0] = 0;
    (void)&pad;
}

extern s32 D_800A353C_a[] asm("D_800A353C.NON_MATCHING");
extern s32 D_800A353C_b[] asm("D_800A3540.NON_MATCHING");
extern s32 D_800A353C_c[] asm("D_800A3538.NON_MATCHING");
extern s32 D_800A3758_a[] asm("D_800A3758.NON_MATCHING");
extern s32 D_800A3758_b[] asm("D_800A3754.NON_MATCHING");
extern s32 D_800A3758_c[] asm("D_800A3760.NON_MATCHING");
extern u8 *D_800A3574_a[] asm("D_800A3574.NON_MATCHING");
extern u8 *D_800A3574_b[] asm("D_800A3570.NON_MATCHING");
extern s32 D_800A3630_nm asm("D_800A3630.NON_MATCHING");
extern s32 D_800A2F30_nm[] asm("D_800A2F30.NON_MATCHING");
extern u8 D_800AE99C_nm[] asm("D_800AE99C.NON_MATCHING");
extern void GraphicsSelectImageBank();
void func_8002DC2C(void) {
    u8 *entry;
    s32 cursor;
    s32 sel;
    s32 slot;
    s32 page;
    s32 first;
    s32 ratio;
    s32 none;

    D_800A353C_a[0] = MathFixedDivide(6, 0xF);
    D_800A3758_a[0] = MathFixedDivide(1, 2);
    D_800A3630_nm = 0x18;
    D_800A3758_b[1] = D_800A353C_c[1];
    func_8003CDBC(0xA7, (void *)STACK_BLOCK_801A0000);
    GraphicsSelectImageBank(6);
    D_800A2F30_nm[0] = 0;
    cursor = 0;
    for (page = 0, first = 0; page < 1; page++, first += 5) {
        sel = (page == 0) ? -1 : 0;
        for (slot = 0; slot < 4; slot++) {
            entry = D_800AE88C + (first + slot) * 0x44;
            D_800A3574_a[0] = entry;
            func_800323F0(cursor, sel);
            cursor++;
            func_80032494(entry);
            /* A second store makes `none` multi-set, so loop.c keeps the
               constant in the loop (retail reloads -1 each pass). */
            none = -1;
            if (sel != none) {
                sel++;
            }
            none = 0;
        }
    }
    ratio = MathFixedDivide(3, 2);
    D_800A353C_b[-1] = ratio;
    D_800A3758_c[-2] = ratio;
    D_800A3574_b[1] = D_800AE99C_nm;
    func_800323F0(4, -1);
    func_80032494(D_800AE99C_nm);
    func_8001DFC8();
}

void *HeapAlloc(u32);

s32 func_8002DDA0(void) {
    s32 size;

    size = 0x1900;
    if (D_800A2EB0 <= 0) {
        size = 0x8200;
    }
    D_800A3984[0] = (s32)HeapAlloc(size);
    return D_800A3984[0] == 0;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002DDD8);

void func_8002E228(void) {
}

void func_8002E230(void) {
    volatile s32 debugBuffer[16];
}

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void func_80033000(u8 *arg0, u8 *arg1, u8 *arg2);
extern void func_80046184(u8 *arg0);
extern void func_80032DEC(u8 *arg0, s32 arg1);
extern void SceneUpdateProjectiles(u8 *arg0);
extern void func_800345E0(void);
extern void func_8003271C(s32 arg0);
extern void func_800179AC(s32 arg0);
extern s32 func_800346D0(s32 arg0);
extern void func_80048568(void);
extern s32 D_800A2F38[];
extern s32 D_800A2D0CScene[] asm("D_800A2D0C.NON_MATCHING");
extern s32 D_800A2D0CStore[] asm("D_800A2D0CAbsolute");
extern s32 D_800A3A94Scene[] asm("D_800A3A94Absolute");
extern u8 *D_800A3554Absolute[];
extern u8 D_800A3A60RaceStep1[];
extern u8 D_800A3075Frame[];
extern s32 D_800A2F0CFrame;
extern s32 D_800A2EC0;
extern u8 D_80098234[];
extern s32 D_800B9D74[];
extern s32 D_800A397C[];
extern s32 D_800A3A3C[];
extern s32 D_800B9D60[];

void func_8002E240(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    SVECTOR rotation;
    VECTOR translation;
    long flag[2];
    MATRIX *matrix;
    s32 *camera;
    u8 *node;
    u8 *child;
    u8 *tail;
    s32 count;
    s32 depth;

    camera = (s32 *)D_800A38AC[0];
    count = 0;
    tail = NULL;
    rotation.vx = FAR_VAR(s32, gFarOffsetX) - camera[0] / 4;
    rotation.vy = FAR_VAR(s32, gFarOffsetY) - camera[1] / 4;
    rotation.vz = FAR_VAR(s32, gFarOffsetZ) - camera[2] / 4;
    RotTrans(&rotation, &translation, flag);
    matrix = (MATRIX *)D_80098234;
    TransMatrix(matrix, &translation);
    PushMatrix();
    SetTransMatrix(matrix);
    D_800A2F38[0] = 0;
    node = arg1;
    if (D_800A397C[0] == 2) {
        if (arg1 != arg2) {
            do {
                ListDispatchCallbacks(node);
                if (*(u16 *)(node + 0xE) == 0) {
                    child = *(u8 **)(node + 0x74);
                    D_800A2D0CStore[-1] = D_800A2D0CScene[-1] + 1;
                    if (D_800A3A3C[0] < ((s32 *)D_800A3554Absolute)[-1]) {
                        depth =
                            D_800A2EC0 -
                            (((s32 *)D_800A3554Absolute)[-1] - D_800A3A3C[0]) +
                            1;
                    } else {
                        depth = D_800A2EC0 -
                                (((s32 *)D_800A3554Absolute)[-1] +
                                 (D_800A3A94Scene[-1] - D_800A3A3C[0])) +
                                1;
                    }
                    if (child != NULL) {
                        do {
                            if (*(s32 *)(child + 4) <= depth) {
                                *(u8 **)(child + 0x30) = tail;
                                tail = child + 8;
                                count = count + 1;
                            }
                            child = *(u8 **)(child + 0x54);
                        } while (child != NULL);
                    }
                }
                node = *(u8 **)node;
            } while (node != arg2);
        }
    } else {
        if (arg1 != arg2) {
            do {
                ListDispatchCallbacks(node);
                if (*(u16 *)(node + 0xE) == 0) {
                    child = *(u8 **)(node + 0x74);
                    D_800A2D0CStore[-1] = D_800A2D0CScene[-1] + 1;
                    if (child != NULL) {
                        do {
                            *(u8 **)(child + 0x30) = tail;
                            tail = child + 8;
                            child = *(u8 **)(child + 0x54);
                            count = count + 1;
                        } while (child != NULL);
                    }
                }
                node = *(u8 **)node;
            } while (node != arg2);
        }
    }
    func_80033000(arg1, arg2, arg3);
    if (D_800A3A60RaceStep1[0] != 0 && D_800A3075Frame[0] == 0) {
        func_80046184(arg0);
    }
    if (count != 0) {
        func_80032DEC(tail, count);
    }
    SceneUpdateProjectiles(arg0);
    func_800345E0();
    PopMatrix();
    func_8003271C(0);
    func_800179AC(0);
    func_800346D0(D_800A2F0CFrame);
    D_800B9D74[0] = GetRCnt(0xF2000001);
    func_80048568();
    if (arg1 != arg2) {
        do {
            *(u16 *)(arg1 + 0xE) = 0;
            arg1 = *(u8 **)arg1;
        } while (arg1 != arg2);
    }
    D_800B9D60[0] += GetRCnt(0xF2000001) - D_800B9D74[0];
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8002E594);

INCLUDE_ASM("asm/nonmatchings/objects", func_8002E9AC);

extern u8 *D_800A3878;
extern void func_8002E9AC(s32 arg0);

void func_8002EE88(void) {
    u8 *node;

    node = D_800A3878;
    if (D_800A2EC8Small != 0) {
        while (node != 0) {
            func_8002E9AC((s32)node);
            node = *(u8 **)(node + 0x3E0);
        }
    } else if (node != 0) {
        do {
            func_8002E9AC((s32)node);
            node = *(u8 **)(node + 0x3E0);
        } while (node != 0);
    }
}

extern u8 D_800A2ED8;

void func_8002EEFC(u8 *arg0) {
    s32 refX;
    s32 refY;
    s32 refZ;
    s32 level;
    s32 lod;
    u8 *node;
    s32 dist;
    s32 delta;
    s32 ySq;
    s32 zSq;

    refX = *(s32 *)((u8 *)D_800A38AC[0] + 0x0);
    refY = *(s32 *)((u8 *)D_800A38AC[0] + 0x4);
    refZ = *(s32 *)((u8 *)D_800A38AC[0] + 0x8);
    node = D_800A3878;
    if (node == NULL) {
        return;
    }
    level = 4;
    do {
        if (node == arg0 && *(s16 *)(node + 0x1EC) == 0 && D_800A2ED8 == 0 &&
            *(s8 *)(node + 0x20C) == 0) {
            *(u8 *)(node + 0x374) = level;
            *(u32 *)(node + 0x36C) = *(u32 *)(node + 0x370) + 0x110;
        } else {
            delta = *(s32 *)(node + 0x0);
            dist = delta - refX;
            dist = dist * dist;
            delta = *(s32 *)(node + 0x4);
            delta = delta - refY;
            ySq = delta * delta;
            delta = *(s32 *)(node + 0x8);
            delta = delta - refZ;
            zSq = delta * delta;
            dist = dist + ySq;
            dist = MathSqrt(dist + zSq);
            if (dist < 0x7D0) {
                *(u8 *)(node + 0x374) = 0;
            } else if (dist < 0x1770) {
                *(u8 *)(node + 0x374) = 1;
            } else if (dist < 0x2EE0) {
                *(u8 *)(node + 0x374) = 2;
            } else {
                *(u8 *)(node + 0x374) = 3;
            }
            if (D_800A2ED8 != 0) {
                if (*(s8 *)(node + 0x374) < 3) {
                    (*(s8 *)(node + 0x374))++;
                }
            }
            if (*(s8 *)(node + 0x200) == level) {
                *(u8 *)(node + 0x374) = 0;
            }
            if (node == arg0) {
                *(u8 *)(node + 0x374) = 0;
            }
            lod = *(s8 *)(node + 0x374);
            *(u32 *)(node + 0x36C) = *(u32 *)(node + 0x370) + (lod * 0x44);
        }
        node = *(u8 **)(node + 0x3E0);
    } while (node != NULL);
}

extern void *D_800A2EA0Small;
extern s32 D_800A2EC4;
extern s32 D_800A37C4Absolute[];
extern s32 D_800A37B4Absolute[];
extern s32 D_800A37ACAbsolute[];
extern s32 D_800A37A4Absolute[];
void func_8002F0A8(u8 *arg0) {
    s32 local[8];
    u8 *owner;

    D_800A2EA0Small = arg0;
    owner = (u8 *)D_800A38AC[0];
    if (arg0 != owner) {
        *(u16 *)(owner + 0x1E0) = *(u16 *)(arg0 + 0x1E0);
    } else {
        *(u16 *)((u8 *)D_800A38AC[0] + 0x1E0) = func_8002482C(
            *(s32 *)(arg0 + 0), *(s32 *)(arg0 + 4), (s32 *)(arg0 + 0x1F8));
    }
    func_8002DA30((s32 *)D_800A38AC[0]);
    if (D_800A2ED8 != 0) {
        CameraUpdateForCar((RaceObject *)D_800A37C4Absolute[0x3A],
                           (RaceObject *)arg0, D_800A2EC4 + 4);
    } else {
        CameraUpdateForCar((RaceObject *)D_800A37B4Absolute[0x3E],
                           (RaceObject *)arg0, *(s8 *)(arg0 + 0x20C));
    }
    func_8001EC38((s32 *)D_800A37ACAbsolute[0x40]);
    MatrixBuildRotationFromTransform((s32 *)D_800A37A4Absolute[0x42],
                                     (s32 *)local);
    local[7] = 0;
    local[6] = 0;
    local[5] = 0;
    SetTransMatrix((MATRIX *)local);
    SetRotMatrix((MATRIX *)local);
    func_8002EEFC(arg0);
}

extern s32 D_800A2EACSmall;
void func_8002F1A0(void) {
    u8 *node;

    if (((u8 *)D_800A2F9DAbsolute)[-0x45] != 0) {
        func_8003A440();
        func_80028FCC(D_800A3878);
        return;
    }
    if (D_800A2EACSmall != 0) {
        func_8003A54C();
        func_80028FCC(D_800A3878);
        return;
    }
    func_80041AF0(0);
    if ((func_80050D1C() & 0xFF) == 0) {
        node = D_800A3878;
        if (node != NULL) {
            do {
                func_8003CF0C(node);
                ((void (*)(void *)) * (s32 *)(node + 0x350))(node);
                node = *(u8 **)(node + 0x3E0);
            } while (node != NULL);
        }
        func_80028FCC(D_800A3878);
    }
    func_80039CF4();
    node = D_800A3878;
    if (node != NULL) {
        do {
            if (*(s16 *)(node + 0x1EC) == 0) {
                func_800297D0(node);
            } else if ((*(u16 *)(node + 0x3A4) & 0xF) == 0) {
                func_80038D78(node);
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != NULL);
    }
}

extern s8 D_800A3860S8[] asm("D_800A3860");
extern s8 D_800A3861[];
extern s8 D_800A3862[];
extern s8 D_800A3863[];
extern s32 D_800A2E7C[];
extern s32 D_800A2E80[];

void func_8002F2CC(void) {
    u8 *node;
    u8 *tableBase;
    s32 carIdx;
    s32 val;

    node = D_800A3878;
    tableBase = (u8 *)0x80011E04;
    if (node != NULL) {
        do {
            if (*(s16 *)(node + 0x1EC) == 0) {
                carIdx = *(s8 *)(node + 0x20B);
                node[0xF6] = D_800A3068[carIdx * 2] < 1;
                node[0xF7] = D_800A3069[carIdx * 2];
                val = D_800A3862[carIdx * 4];
                *(s16 *)(node + 0x2A0) = (val - 0x40) / 4;
                val = D_800A3861[carIdx * 4];
                *(s16 *)(node + 0x2A6) = (val - 0x40) / 4;
                *(s16 *)(node + 0x112) =
                    *(u16 *)(tableBase + carIdx * 22 + 0x14);
                val = D_800A3863[carIdx * 4];
                func_80028754(node, 9 - val * 10 / 64);
                val = D_800A3860S8[carIdx * 4];
                if (val == 0x3F) {
                    *(s32 *)(node + 0x234) = D_800A2E7C[0];
                } else {
                    *(s32 *)(node + 0x234) = D_800A2E80[0];
                }
                func_8002D3EC(node);
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != NULL);
    }
    func_8002A954();
}

extern u8 D_800A2EDA;
void func_8002F454(void) {
    s32 red;
    u8 *node;
    s32 green;
    s32 carIdx;

    node = D_800A3878;
    if (D_800A2EDA != 0) {
        return;
    }
    if (node != NULL) {
        do {
            if (*(s16 *)(node + 0x1EC) == 0) {
                carIdx = *(s8 *)(node + 0x20B);
                red = 0x20;
                if (D_800A2EB0 >= 0) {
                    red = (*(s16 *)(node + 0x2A0) << 2) + 0x40;
                    green = (*(s16 *)(node + 0x2A6) << 2) + 0x40;
                    if (red < 0) {
                        red = 0;
                    }
                    if (red >= 0x40) {
                        red = 0x3F;
                    }
                    if (green < 0) {
                        green = 0;
                    }
                    if (green >= 0x40) {
                        green = 0x3F;
                    }
                } else {
                    green = 0x20;
                }
                D_800A3860[carIdx][1] = green;
                D_800A3860[carIdx][2] = red;
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != NULL);
    }
}

extern MATRIX D_800A4548[];
extern s32 D_800A359C[];
extern s32 D_800A2F68[];
extern s32 D_800A2EC0;
extern s32 D_800A2EF8;
extern s32 D_800A2EFC;
extern s32 D_800A2F00;
extern s32 D_800A2EAC;
extern s32 D_800A2EF0;

void func_8002F514(void) {
    VECTOR translation;

    D_800A2EC0 = 0;
    translation.vz = 0;
    translation.vy = 0;
    translation.vx = 0;
    TransMatrix(D_800A4548, &translation);
    SetTransMatrix(D_800A4548);
    func_80035B20();
    func_80042EC0();
    func_80034990();
    func_8002DDD8();
    D_800A2EF8 = 0;
    D_800A2EFC = 0;
    D_800A2F00 = 0;
    D_800A359C[0] = 0;
    D_800A2EAC = 0;
    D_800A2F68[0] = 0;
    D_800A2EF0 = 0;
}

void CarPlaceOnStartingGrid(void);
void func_8003B6DC(s32);
void func_8002F5A4(void) {
    CarPlaceOnStartingGrid();
    func_8003B6DC(1);
}

void func_80041A28(void);
void exit();
void func_8002F5CC(void) {
    func_80041A28();
    exit();
}

void func_8002F5F4(void) {
    extern s32 D_800A2E9CSmall;
    s32 node;
    s32 f;
    s32 temp;

    node = D_800A2E9CSmall;
    node = *(s32 *)(node + 0x3E0);
    D_800A2E9CSmall = node;
    if (node != 0 && *(s32 *)(node + 0x350) != (s32)func_80029E34) {
        return;
    }
    node = D_800A3878;
    temp = *(s32 *)(node + 0x350);
    f = (s32)func_80029E34;
    D_800A2E9CSmall = node;
    if (temp != f) {
        return;
    }
    do {
        node = D_800A2E9CSmall;
        node = *(s32 *)(node + 0x3E0);
        temp = *(s32 *)(node + 0x350);
        D_800A2E9CSmall = node;
    } while (temp == f);
}

void func_8002F66C(void) {
}

void func_8002F674(void) {
    extern s32 D_800A2E9CSmall;
    extern s32 D_800A2F14;
    extern s32 D_800A2F18;
    extern s32 D_800A2F1C;
    extern s32 D_800A2F20;
    extern s32 D_800A2F24;
    extern s32 D_800A35E0[];
    extern u32 RandomGetScaled16(s32);
    s32 value;
    s32 r;

    switch (D_800A2EC4) {
    case 0:
        break;
    case 1:
        D_800A2E9CSmall = (s32)D_800A3554[0];
        break;
    case 2:
        D_800A2E9CSmall = (s32)D_800A3554[0];
        break;
    case 3:
        if (D_800A2F14 != 0) {
            D_800A2F24 = 4;
            D_800A2F1C = 0;
            D_800A2F20 = 0;
            *(u8 *)(D_800A3558[0] + 0x20C) = 4;
            D_800A2F14 = 0;
            D_800A2F18 = 100;
        } else {
            D_800A2F20 += 1;
            D_800A2F1C += 1;
            if (D_800A2F18 > 0) {
                D_800A2F18 -= 1;
            }
            if (D_800A2F20 > 100) {
                value = *(s32 *)(D_800A2E9CSmall + 0x3E0);
                D_800A2F20 = 0;
                D_800A2E9CSmall = value;
                if (value == 0) {
                    D_800A2E9CSmall = (s32)D_800A3554[0];
                }
                *(u8 *)(D_800A3558[0] + 0x20C) = D_800A2F24;
                r = RandomGetScaled16(4);
                if (r < 0) {
                    r = -RandomGetScaled16(4);
                } else {
                    r = RandomGetScaled16(4);
                }
                switch (r) {
                case 0:
                    D_800A2F24 = 11;
                    *(u8 *)(D_800A3558[0] + 0x20C) = 11;
                    break;
                case 1:
                    D_800A2F24 = 4;
                    *(u8 *)(D_800A3558[0] + 0x20C) = 4;
                    break;
                case 2:
                    D_800A2F24 = 4;
                    *(u8 *)(D_800A3558[0] + 0x20C) = 4;
                    break;
                case 3:
                    D_800A2F24 = 6;
                    *(u8 *)(D_800A3558[0] + 0x20C) = 6;
                    break;
                }
            }
        }
        break;
    case 4:
        D_800A2E9CSmall = (s32)D_800A35E0[0];
        break;
    }
    if (D_800A2E9CSmall == 0) {
        D_800A2E9CSmall = (s32)D_800A3554[0];
    }
}

extern u8 D_800A35FC[];
void func_8003B6DC(s32 arg0);
void func_8003B464(void);
void func_8003C1CC(void);
void func_8003C3FC(void);

void func_8002F86C(void *arg0, s32 arg1) {

    func_8003B6DC(1);
    func_8003B464();
    if (arg1 != 2) {
        D_800A2EAC = arg1;
    }
    if (D_800A2EB0 == 1) {
        func_8003C3FC();
        *(u8 *)((u8 *)arg0 + 0x20C) = 3;
    } else {
        func_8003C1CC();
        if (*(s8 *)((u8 *)arg0 + 0x204) == 1) {
            *(u8 *)((u8 *)arg0 + 0x20C) = 0xD;
        } else {
            *(u8 *)((u8 *)arg0 + 0x20C) = 0x10;
        }
    }
    D_800A2EAC = arg1;
    D_800A35FC[0] = 0;
}

/* Separate symbol views preserve the retail GP and absolute accesses. */
extern void func_80023454RaceStep(u8 *) asm("func_80023454");
asm(".globl D_800A2EA4RaceStep\nD_800A2EA4RaceStep = D_800A2EA4\n"
    ".globl D_800A2EA8RaceStep\nD_800A2EA8RaceStep = D_800A2EA8\n"
    ".globl D_800A2EACRaceStep\nD_800A2EACRaceStep = D_800A2EAC\n"
    ".globl D_800A2EB0RaceStep\nD_800A2EB0RaceStep = D_800A2EB0\n"
    ".globl D_800A2EB4RaceStep\nD_800A2EB4RaceStep = D_800A2EB4\n"
    ".globl D_800A2EC0RaceStep\nD_800A2EC0RaceStep = D_800A2EC0\n"
    ".globl D_800A2EC8RaceStep\nD_800A2EC8RaceStep = D_800A2EC8\n"
    ".globl D_800A2EFCRaceStep\nD_800A2EFCRaceStep = D_800A2EFC\n"
    ".globl D_800A2F00RaceStep\nD_800A2F00RaceStep = D_800A2F00\n"
    ".globl D_800A3878RaceStep\nD_800A3878RaceStep = D_800A3878\n"
    ".globl D_800A2D0CRaceStep1\nD_800A2D0CRaceStep1 = D_800A2D0C\n"
    ".globl D_800A2F58RaceStep1\nD_800A2F58RaceStep1 = D_800A2F58\n"
    ".globl D_800A3554RaceStep1\nD_800A3554RaceStep1 = D_800A3554\n"
    ".globl D_800A3554RaceStep2\nD_800A3554RaceStep2 = D_800A3554\n"
    ".globl D_800A3554RaceStep3\nD_800A3554RaceStep3 = D_800A3554\n"
    ".globl D_800A3554RaceStep5\nD_800A3554RaceStep5 = D_800A3554\n"
    ".globl D_800A3554RaceStep6\nD_800A3554RaceStep6 = D_800A3554\n"
    ".globl D_800A3554RaceStep7\nD_800A3554RaceStep7 = D_800A3554\n"
    ".globl D_800A3554RaceStep9\nD_800A3554RaceStep9 = D_800A3554\n"
    ".globl D_800A359CRaceStep1\nD_800A359CRaceStep1 = D_800A359C\n"
    ".globl D_800A359CRaceStep2\nD_800A359CRaceStep2 = D_800A359C\n"
    ".globl D_800A359CRaceStep3\nD_800A359CRaceStep3 = D_800A359C\n"
    ".globl D_800A359CRaceStep4\nD_800A359CRaceStep4 = D_800A359C\n"
    ".globl D_800A359CRaceStep5\nD_800A359CRaceStep5 = D_800A359C\n"
    ".globl D_800A359CRaceStep6\nD_800A359CRaceStep6 = D_800A359C\n"
    ".globl D_800A35A4RaceStep1\nD_800A35A4RaceStep1 = D_800A35A4\n"
    ".globl D_800A35A4RaceStep2\nD_800A35A4RaceStep2 = D_800A35A4\n"
    ".globl D_800A35FCRaceStep1\nD_800A35FCRaceStep1 = D_800A35FC\n"
    ".globl D_800A35FCRaceStep2\nD_800A35FCRaceStep2 = D_800A35FC\n"
    ".globl D_800A38E0RaceStep1\nD_800A38E0RaceStep1 = D_800A38E0\n"
    ".globl D_800A38E0RaceStep2\nD_800A38E0RaceStep2 = D_800A38E0\n"
    ".globl D_800A397CRaceStep1\nD_800A397CRaceStep1 = D_800A397C\n"
    ".globl D_800A39F8RaceStep1\nD_800A39F8RaceStep1 = D_800A39F8\n"
    ".globl D_800A39F8RaceStep2\nD_800A39F8RaceStep2 = D_800A39F8\n"
    ".globl D_800A3A60RaceStep1\nD_800A3A60RaceStep1 = D_800A3A60\n"
    ".globl D_800A3A94RaceStep1\nD_800A3A94RaceStep1 = D_800A3A94\n"
    ".globl D_800A3A94RaceStep2\nD_800A3A94RaceStep2 = D_800A3A94\n"
    ".globl D_800A2EA8RaceStepRepeat\nD_800A2EA8RaceStepRepeat = D_800A2EA8\n");
extern s32 D_800A2EA4RaceStep;
extern s32 D_800A2EA8RaceStep;
extern s32 D_800A2EACRaceStep;
extern s32 D_800A2EB0RaceStep;
extern s32 D_800A2EB4RaceStep;
extern s32 D_800A2EC0RaceStep;
extern s32 D_800A2EC8RaceStep;
extern s32 D_800A2EFCRaceStep;
extern s32 D_800A2F00RaceStep;
extern u8 *D_800A3878RaceStep;
extern s8 D_800A2D0CRaceStep1[];
extern u8 D_800A2F58RaceStep1[];
extern u8 *D_800A3554RaceStep1[];
extern u8 *D_800A3554RaceStep2[];
extern u8 *D_800A3554RaceStep3[];
extern u8 *D_800A3554RaceStep5[];
extern u8 *D_800A3554RaceStep6[];
extern u8 *D_800A3554RaceStep7[];
extern u8 *D_800A3554RaceStep9[];
extern s32 D_800A359CRaceStep1[];
extern s32 D_800A359CRaceStep2[];
extern s32 D_800A359CRaceStep3[];
extern s32 D_800A359CRaceStep4[];
extern s32 D_800A359CRaceStep5[];
extern s32 D_800A359CRaceStep6[];
extern s16 D_800A35A4RaceStep1[];
extern s16 D_800A35A4RaceStep2[];
extern s8 D_800A35FCRaceStep1[];
extern s8 D_800A35FCRaceStep2[];
extern u8 D_800A38E0RaceStep1[];
extern u8 D_800A38E0RaceStep2[];
extern s32 D_800A397CRaceStep1[];
extern u8 D_800A39F8RaceStep1[];
extern u8 D_800A39F8RaceStep2[];
extern u8 D_800A3A60RaceStep1[];
extern u8 D_800A3A94RaceStep1[];
extern u8 D_800A3A94RaceStep2[];
extern s32 D_800A2EA8RaceStepRepeat;

void RaceUpdateFrame(void) {
    s16 savedSections[2];
    s32 noticeFrames;
    RaceObject *head;
    u8 *savedCar;
    s32 currentLap;
    s32 lapLimit;
    register s32 morePlayers asm("v0");
    register s16 playerIndex asm("s1");
    s16 nextPlayerIndex;
    s32 raceActive;
    s32 finishDelay;
    s32 finishFrames;
    s32 activeMask;
    s32 replayFrames;
    s32 passedLap;
    s32 cameraMode;
    register u16 savedSection asm("s1");
    u8 *playerCar;
    u8 *object;

    playerCar = D_800A3554RaceStep1[0];
    raceActive = 0;
    if (D_800A2EC8RaceStep != 0) {
        func_80023454RaceStep(playerCar);
        if (D_800A397CRaceStep1[0] == 2) {
            func_80024280();
        }
        object = D_800A3878RaceStep;
        if (D_800A2EC8RaceStep != 0) {
            if (object != NULL) {
            pausedList:
                func_8002E9AC(object);
                object = (*(u8 **)(object + 0x3E0));
                if (object != NULL) {
                    goto pausedList;
                }
            }
        } else if (object != NULL) {
        pausedListAfterChange:
            func_8002E9AC(object);
            object = (*(u8 **)(object + 0x3E0));
            if (object != NULL) {
                goto pausedListAfterChange;
            }
        }
        goto finishUpdate;
    }
    D_800A2EC0RaceStep += 1;
    if (D_800A2F58RaceStep1[0] != 0) {
        func_8003A440();
        goto updateList;
    }
    if (D_800A2EACRaceStep != 0) {
        func_8003A54C();
    updateList:
        func_80028FCC(D_800A3878RaceStep);
    } else {
        func_80041AF0(0);
        if (!(func_80050D1C() & 0xFF)) {
            object = D_800A3878RaceStep;
            if (object != NULL) {
                do {
                    func_8003CF0C(object);
                    (*(void (**)(u8 *))(object + 0x350))(object);
                    object = (*(u8 **)(object + 0x3E0));
                } while (object != NULL);
            }
            func_80028FCC(D_800A3878RaceStep);
        }
        func_80039CF4();
        object = D_800A3878RaceStep;
        if (object != NULL) {
            do {
                if ((*(s16 *)(object + 0x1EC)) == 0) {
                    func_800297D0(object);
                } else if (!((*(u16 *)(object + 0x3A4)) & 0xF)) {
                    func_80038D78(object);
                }
                object = (*(u8 **)(object + 0x3E0));
            } while (object != NULL);
        }
    }
    object = D_800A3878RaceStep;
    if (D_800A2EC8RaceStep != 0) {
        if (object != NULL) {
        postUpdateList:
            func_8002E9AC(object);
            object = (*(u8 **)(object + 0x3E0));
            if (object != NULL) {
                goto postUpdateList;
            }
        }
    } else if (object != NULL) {
        do {
            func_8002E9AC(object);
            object = (*(u8 **)(object + 0x3E0));
        } while (object != NULL);
    }
    if (D_800A2EACRaceStep != 0) {
        if (D_800A359CRaceStep1[0] != 0) {
            func_8002267C();
            replayFrames = D_800A359CRaceStep2[0] - 1;
            D_800A359CRaceStep3[0] = replayFrames;
            if (replayFrames == 0) {
                D_800A2D0CRaceStep1[0] = 1;
                return;
            }
            D_800A2EA4RaceStep = 0;
            GraphicsSetGeomOffsetForMode(0, 3);
            goto finishUpdate;
        }
        func_8002267C();
        if (D_800A2EB0RaceStep == 0) {
            RaceUpdateLapProgress();
        }
        finishFrames = D_800A2EACRaceStep - 1;
        D_800A2EACRaceStep = finishFrames;
        if (finishFrames == 1) {
            if (D_800A2EB0RaceStep == 2) {
                D_800A359CRaceStep4[0] = finishFrames;
            } else {
                D_800A359CRaceStep5[0] = 0x21C;
                (*(s8 *)(D_800A3554RaceStep2[0] + 0x20C)) = 0x11;
                func_80041444(1);
                if (D_800A3A60RaceStep1[0] != 0) {
                    savedCar = D_800A3554RaceStep3[0];
                    savedSection = *(u16 *)(savedCar + 0x1E0);
                    *(u16 *)(savedCar + 0x1E0) = 0;
                    SceneInitRoadStrip();
                    (*(u16 *)(D_800A3554RaceStep5[0] + 0x1E0)) = savedSection;
                }
            }
        }
        goto finishUpdate;
    }
    func_800488B8();
    func_8002267C();
    RaceUpdateLapProgress();
    object = D_800A3878RaceStep;
    if (object != NULL) {
        noticeFrames = 0x50;
        do {
            if ((*(s16 *)(object + 0x1EC)) == 0) {
                if (D_800A2EA8RaceStep < (*(s16 *)(object + 0x1D6))) {
                    func_8003B6DC(1);
                    finishDelay = 0x78;
                    func_8003B464();
                    D_800A2EACRaceStep = finishDelay;
                    if (D_800A2EB0RaceStep == 1) {
                        func_8003C3FC();
                        cameraMode = 3;
                    } else {
                        func_8003C1CC();
                        cameraMode = *(s8 *)(object + 0x204);
                        if (cameraMode == 1) {
                            cameraMode = 0xD;
                        } else {
                            cameraMode = 0x10;
                        }
                    }
                    (*(s8 *)(object + 0x20C)) = cameraMode;
                    D_800A2EACRaceStep = finishDelay;
                    D_800A35FCRaceStep1[0] = 0;
                    if (D_800A2EB0RaceStep == 1) {
                        raceActive = 1;
                    }
                }
                if ((*(u8 *)(object + 0xF4)) == 1) {
                    raceActive = 1;
                }
            }
            if (D_800A2EB0RaceStep != 1) {
                currentLap = (*(s16 *)(object + 0x1D6));
                /* Keep the current-lap read before the lap-limit read. */
                asm("" : : "r"(currentLap) : "memory");
                lapLimit = D_800A2EA8RaceStep;
                if (currentLap == lapLimit) {
                    if (D_800A38E0RaceStep1[0] != 0) {
                        D_800A38E0RaceStep2[0] = 0;
                        if ((D_800A2EFCRaceStep == 0) &&
                            (D_800A39F8RaceStep1[0] == 0) &&
                            (D_800A35A4RaceStep1[0] == 0)) {
                            D_800A2EFCRaceStep = noticeFrames;
                            D_800A2F00RaceStep = 2;
                        }
                    } else {
                        passedLap = D_800A2EA8RaceStepRepeat < currentLap;
                        goto testLapPassed;
                    }
                } else {
                    passedLap = lapLimit < currentLap;
                    goto testLapPassed;
                }
            } else {
                passedLap =
                    D_800A2EA8RaceStepRepeat < (*(s16 *)(object + 0x1D6));
            testLapPassed:
                if ((passedLap != 0) && (D_800A3A94RaceStep1[0] != 0)) {
                    D_800A3A94RaceStep2[0] = 0;
                    if ((D_800A2EFCRaceStep == 0) &&
                        (D_800A39F8RaceStep2[0] == 0) &&
                        (D_800A35A4RaceStep2[0] == 0)) {
                        D_800A2EFCRaceStep = noticeFrames;
                        D_800A2F00RaceStep = 0;
                    }
                }
            }
            object = (*(u8 **)(object + 0x3E0));
        } while (object != NULL);
    }
    /* Retain the retail byte mask after the active-state test. */
    asm("" : "=r"(raceActive) : "0"(raceActive));
    activeMask = raceActive & 0xFF;
    if ((activeMask == 0) && (D_800A2EB0RaceStep >= 0)) {
        D_800A2EACRaceStep = 0x78;
        if (D_800A2EB0RaceStep == 1) {
            func_8003C3FC();
        }
        if (D_800A2EB0RaceStep == 2) {
            func_8003C528();
        }
        object = D_800A3554RaceStep6[0];
        playerIndex = 0;
        morePlayers = activeMask < D_800A2EB4RaceStep;
        if (morePlayers) {
            do {
                (*(s8 *)(object + 0x20C)) = 3;
                savedSections[(*(s8 *)(object + 0x20B))] =
                    (*(u16 *)(object + 0x1E0));
                nextPlayerIndex = playerIndex + 1;
                playerIndex = nextPlayerIndex;
                (*(u16 *)(object + 0x1E0)) =
                    (u16)(0x1E - (s8)(*(s8 *)(object + 0x204)));
                object = (*(u8 **)(object + 0x3E0));
            } while (nextPlayerIndex < D_800A2EB4RaceStep);
        }
        if (D_800A2EB0RaceStep == 0) {
            func_8003C1CC();
        }
        head = (RaceObject *)D_800A3554RaceStep7[0];
        head->unk1E0 = savedSections[0];
        if (D_800A2EA4RaceStep != 0) {
            ((RaceObject *)*(u8 **)((u8 *)head + 0x3E0))->unk1E0 =
                savedSections[1];
        }
        D_800A35FCRaceStep2[0] = 0;
    }
finishUpdate:
    if (D_800A359CRaceStep6[0] == 0) {
        SoundUpdateCar(playerCar);
        if (D_800A2EA4RaceStep == 2) {
            SoundUpdateCar((*(u8 **)(D_800A3554RaceStep9[0] + 0x3E0)));
        }
    }
}

extern u32 D_800A2EEC;
extern u32 D_800A2F28;
extern u32 gPrimitiveCursor2[] asm("gPrimitiveCursor");
extern u32 gPrimitiveCursor3[] asm("gPrimitiveCursor");
extern u32 gPrimitiveCursor4[] asm("gPrimitiveCursor");
extern u32 gPrimitiveCursor5[] asm("gPrimitiveCursor");
extern u32 gPrimitiveCursor6[] asm("gPrimitiveCursor");
extern u32 gPrimitiveCursor7[] asm("gPrimitiveCursor");
extern s32 D_800A39C8b[] asm("D_800A39C8");
extern s32 D_800A39C8c[] asm("D_800A39C8");
extern s32 D_800A39C8d[] asm("D_800A39C8");
extern s32 D_800A39C8e[] asm("D_800A39C8");
extern void SetPolyF4(u8 *prim);
extern void SetSemiTrans(void *p, s32 abe);
extern void AddPrim(void *ot, void *p);
void func_8002FFB8(s32 arg0) {
    u8 *prim;
    s32 cursorVal;
    s32 grey;
    s32 red;
    s32 green;

    grey = 100;
    red = 0x96;
    green = 0x8C;
    if (D_800A2EEC != 0) {
        D_800A2F28 = arg0;
        if (arg0 != 0) {
            if (arg0 == 1) {
                cursorVal = gPrimitiveCursor[0];
                asm("" : "=r"(prim) : "0"(cursorVal));
                gPrimitiveCursor2[0] = (u32)prim + 0x28;
                SetPolyF4(prim);
                prim[4] = grey;
                prim[5] = grey;
                prim[6] = grey;
                *(s16 *)(prim + 8) = 0;
                *(s16 *)(prim + 0xA) = 0;
                *(s16 *)(prim + 0xC) = 0x140;
                *(s16 *)(prim + 0xE) = 0;
                *(s16 *)(prim + 0x10) = 0;
                *(s16 *)(prim + 0x12) = 0xF0;
                *(s16 *)(prim + 0x14) = 0x140;
                *(s16 *)(prim + 0x16) = 0xF0;
                SetSemiTrans(prim, 1);
                AddPrim((void *)(D_800A39C8b[0] + 0xC), prim);
                cursorVal = gPrimitiveCursor3[0];
                asm("" : "=r"(prim) : "0"(cursorVal));
                gPrimitiveCursor4[0] = (u32)prim + 0x28;
                SetPolyF4(prim);
                prim[4] = grey;
                prim[5] = grey;
                prim[6] = grey;
                *(s16 *)(prim + 8) = 0;
                *(s16 *)(prim + 0xA) = 0;
                *(s16 *)(prim + 0xC) = 0x140;
                *(s16 *)(prim + 0xE) = 0;
                *(s16 *)(prim + 0x10) = 0;
                *(s16 *)(prim + 0x12) = 0xF0;
                *(s16 *)(prim + 0x14) = 0x140;
                *(s16 *)(prim + 0x16) = 0xF0;
                SetSemiTrans(prim, 1);
                AddPrim((void *)(D_800A39C8c[0] + 0x190), prim);
                grey = 0x50;
                cursorVal = gPrimitiveCursor5[0];
                asm("" : "=r"(prim) : "0"(cursorVal));
                gPrimitiveCursor6[0] = (u32)prim + 0x28;
                SetPolyF4(prim);
                prim[4] = grey;
                prim[5] = grey;
                prim[6] = grey;
                *(s16 *)(prim + 8) = 0;
                *(s16 *)(prim + 0xA) = 0;
                *(s16 *)(prim + 0xC) = 0x140;
                *(s16 *)(prim + 0xE) = 0;
                *(s16 *)(prim + 0x10) = 0;
                *(s16 *)(prim + 0x12) = 0xF0;
                *(s16 *)(prim + 0x14) = 0x140;
                *(s16 *)(prim + 0x16) = 0xF0;
                SetSemiTrans(prim, 1);
                AddPrim((void *)(D_800A39C8d[0] + 0x320), prim);
            } else {
                SetFarColor(red, green, grey);
                SetFogFar(0x7D0, grey);
                cursorVal = gPrimitiveCursor7[0];
                asm("" : "=r"(prim) : "0"(cursorVal));
                gPrimitiveCursor6[0] = (u32)prim + 0x28;
                SetPolyF4(prim);
                prim[4] = red;
                prim[5] = green;
                prim[6] = grey;
                *(s16 *)(prim + 8) = 0;
                *(s16 *)(prim + 0xA) = 0;
                *(s16 *)(prim + 0xC) = 0x140;
                *(s16 *)(prim + 0xE) = 0;
                *(s16 *)(prim + 0x10) = 0;
                *(s16 *)(prim + 0x12) = 0xF0;
                *(s16 *)(prim + 0x14) = 0x140;
                *(s16 *)(prim + 0x16) = 0xF0;
                SetSemiTrans(prim, 1);
                AddPrim((void *)(D_800A39C8e[0] + 0xAF0), prim);
            }
        }
    }
}

/* Separate symbol views preserve this routine's GP and absolute accesses. */
asm(".globl D_800A2E8CFrame\nD_800A2E8CFrame = D_800A2E8C\n"
    ".globl D_800A2E98Frame\nD_800A2E98Frame = D_800A2E98\n"
    ".globl D_800A2E9CFrame\nD_800A2E9CFrame = D_800A2E9C\n"
    ".globl D_800A2EA0Frame\nD_800A2EA0Frame = D_800A2EA0\n"
    ".globl D_800A2EA4Frame\nD_800A2EA4Frame = D_800A2EA4\n"
    ".globl D_800A2EBCFrame\nD_800A2EBCFrame = D_800A2EBC\n"
    ".globl D_800A2EC0Frame\nD_800A2EC0Frame = D_800A2EC0\n"
    ".globl D_800A2EC4Frame\nD_800A2EC4Frame = D_800A2EC4\n"
    ".globl D_800A2EC8Frame\nD_800A2EC8Frame = D_800A2EC8\n"
    ".globl D_800A2ED8Frame\nD_800A2ED8Frame = D_800A2ED8\n"
    ".globl D_800A2ED9Frame\nD_800A2ED9Frame = D_800A2ED9\n"
    ".globl D_800A2EDAFrame\nD_800A2EDAFrame = D_800A2EDA\n"
    ".globl D_800A2F08Frame\nD_800A2F08Frame = D_800A2F08\n"
    ".globl D_800A2F0CFrame\nD_800A2F0CFrame = D_800A2F0C\n"
    ".globl D_800A2F10Frame\nD_800A2F10Frame = D_800A2F10\n"
    ".globl D_800A3075Frame\nD_800A3075Frame = D_800A3075\n"
    ".globl D_800A3554Frame\nD_800A3554Frame = D_800A3554\n"
    ".globl D_800A3558Frame\nD_800A3558Frame = D_800A3558\n"
    ".globl D_800A3774Frame\nD_800A3774Frame = D_800A3774\n"
    ".globl D_800A37B0Frame\nD_800A37B0Frame = D_800A37B0\n"
    ".globl D_800A3984Frame\nD_800A3984Frame = D_800A3984\n"
    ".globl D_800B9D54Frame\nD_800B9D54Frame = D_800B9D54\n"
    ".globl D_800B9D5CFrame\nD_800B9D5CFrame = D_800B9D5C\n"
    ".globl D_800A38ACFrame1\nD_800A38ACFrame1 = D_800A38AC\n"
    ".globl D_800A38ACFrame2\nD_800A38ACFrame2 = D_800A38AC\n"
    ".globl D_800A38ACFrame3\nD_800A38ACFrame3 = D_800A38AC\n"
    ".globl D_800A38ACFrame5\nD_800A38ACFrame5 = D_800A38AC\n"
    ".globl D_800A38ACFrame6\nD_800A38ACFrame6 = D_800A38AC\n"
    ".globl D_800A38ACFrame7\nD_800A38ACFrame7 = D_800A38AC\n"
    ".globl D_800A38ACFrame8\nD_800A38ACFrame8 = D_800A38AC\n"
    ".globl D_800A38ACFrame9\nD_800A38ACFrame9 = D_800A38AC\n"
    ".globl D_800A38ACFrame11\nD_800A38ACFrame11 = D_800A38AC\n"
    ".globl D_800A38ACFrame12\nD_800A38ACFrame12 = D_800A38AC\n"
    ".globl D_800A38ACFrame13\nD_800A38ACFrame13 = D_800A38AC\n"
    ".globl D_800A38ACFrame14\nD_800A38ACFrame14 = D_800A38AC\n"
    ".globl D_800A38ACFrame15\nD_800A38ACFrame15 = D_800A38AC\n"
    ".globl D_800A38ACFrame17\nD_800A38ACFrame17 = D_800A38AC\n"
    ".globl D_800A38ACFrame18\nD_800A38ACFrame18 = D_800A38AC\n"
    ".globl D_800A2F3CFrame1\nD_800A2F3CFrame1 = D_800A2F3C\n"
    ".globl D_800A2F3CFrame2\nD_800A2F3CFrame2 = D_800A2F3C\n"
    ".globl D_800A2F3CFrame3\nD_800A2F3CFrame3 = D_800A2F3C\n"
    ".globl D_800A2F3CFrame4\nD_800A2F3CFrame4 = D_800A2F3C\n"
    ".globl D_800A2F3CFrame5\nD_800A2F3CFrame5 = D_800A2F3C\n"
    ".globl D_800A2F3CFrame6\nD_800A2F3CFrame6 = D_800A2F3C\n"
    ".globl D_800A2F3CFrame7\nD_800A2F3CFrame7 = D_800A2F3C\n"
    ".globl D_800A39C8Frame1\nD_800A39C8Frame1 = D_800A39C8\n"
    ".globl D_800A39C8Frame2\nD_800A39C8Frame2 = D_800A39C8\n"
    ".globl D_800A39C8Frame3\nD_800A39C8Frame3 = D_800A39C8\n"
    ".globl D_800A39C8Frame4\nD_800A39C8Frame4 = D_800A39C8\n"
    ".globl D_800A39C8Frame5\nD_800A39C8Frame5 = D_800A39C8\n"
    ".globl D_800A39C8Frame6\nD_800A39C8Frame6 = D_800A39C8\n"
    ".globl D_800A39C8Frame7\nD_800A39C8Frame7 = D_800A39C8\n"
    ".globl D_800A39C8Frame8\nD_800A39C8Frame8 = D_800A39C8\n"
    ".globl gOrderingTableBankFrame1\ngOrderingTableBankFrame1 = gOrderingTableBank\n"
    ".globl gOrderingTableBankFrame2\ngOrderingTableBankFrame2 = gOrderingTableBank\n"
    ".globl gOrderingTableBankFrame3\ngOrderingTableBankFrame3 = gOrderingTableBank\n"
    ".globl gOrderingTableBankFrame4\ngOrderingTableBankFrame4 = gOrderingTableBank\n"
    ".globl gOrderingTableBankFrame5\ngOrderingTableBankFrame5 = gOrderingTableBank\n"
    ".globl gOrderingTableBankFrame6\ngOrderingTableBankFrame6 = gOrderingTableBank\n"
    ".globl gOrderingTableBankFrame7\ngOrderingTableBankFrame7 = gOrderingTableBank\n"
    ".globl gOrderingTableBankFrame8\ngOrderingTableBankFrame8 = gOrderingTableBank\n"
    ".globl gOrderingTableBankFrame9\ngOrderingTableBankFrame9 = gOrderingTableBank\n"
    ".globl gOrderingTableBankFrame10\ngOrderingTableBankFrame10 = gOrderingTableBank\n"
    ".globl D_800A38ACFrameCam1A\nD_800A38ACFrameCam1A = D_800A38AC\n"
    ".globl D_800A38ACFrameCam1B\nD_800A38ACFrameCam1B = D_800A38AC\n"
    ".globl D_800A38ACFrameCam2A\nD_800A38ACFrameCam2A = D_800A38AC\n"
    ".globl D_800A38ACFrameCam2B\nD_800A38ACFrameCam2B = D_800A38AC\n"
    ".globl D_800A38ACFrameCam3A\nD_800A38ACFrameCam3A = D_800A38AC\n"
    ".globl D_800A38ACFrameCam3B\nD_800A38ACFrameCam3B = D_800A38AC\n"
    ".globl gOrderingTableBankFrame3Read\ngOrderingTableBankFrame3Read = gOrderingTableBank\n"
    ".globl D_800A39C8Frame3Read\nD_800A39C8Frame3Read = D_800A39C8\n"
    ".globl gOrderingTableBankFrame8Read\ngOrderingTableBankFrame8Read = gOrderingTableBank\n"
    ".globl D_800A39C8Frame4Read\nD_800A39C8Frame4Read = D_800A39C8\n"
    ".globl D_800A39C8Frame5Read\nD_800A39C8Frame5Read = D_800A39C8\n"
    ".globl D_800A39C8Frame8Read\nD_800A39C8Frame8Read = D_800A39C8\n");
extern s32 D_800A2E8CFrame;
extern s32 D_800A2E98Frame;
extern u8 *D_800A2E9CFrame;
extern u8 *D_800A2EA0Frame;
extern s32 D_800A2EA4Frame;
extern s32 D_800A2EBCFrame;
extern s32 D_800A2EC0Frame;
extern s32 D_800A2EC4Frame;
extern s32 D_800A2EC8Frame;
extern u8 D_800A2ED8Frame;
extern s8 D_800A2ED9Frame;
extern u8 D_800A2EDAFrame;
extern s32 D_800A2F08Frame;
extern s32 D_800A2F0CFrame;
extern s32 D_800A2F10Frame;
extern u8 D_800A3075Frame[];
extern u8 *D_800A3554Frame[];
extern u8 *D_800A3558Frame[];
extern s32 D_800A3774Frame;
extern s32 D_800A37B0Frame;
extern u8 *D_800A3984Frame[];
extern s32 D_800B9D54Frame[];
extern s32 D_800B9D5CFrame[];
extern u8 *D_800A38ACFrame1[];
extern u8 *D_800A38ACFrame2[];
extern u8 *D_800A38ACFrame3[];
extern u8 *D_800A38ACFrame5[];
extern u8 *D_800A38ACFrame6[];
extern u8 *D_800A38ACFrame7[];
extern u8 *D_800A38ACFrame8[];
extern u8 *D_800A38ACFrame9[];
extern u8 *D_800A38ACFrame11[];
extern u8 *D_800A38ACFrame12[];
extern u8 *D_800A38ACFrame13[];
extern u8 *D_800A38ACFrame14[];
extern u8 *D_800A38ACFrame15[];
extern u8 *D_800A38ACFrame17[];
extern u8 *D_800A38ACFrame18[];
extern s32 D_800A2F3CFrame1[];
extern s32 D_800A2F3CFrame2[];
extern s32 D_800A2F3CFrame3[];
extern s32 D_800A2F3CFrame4[];
extern s32 D_800A2F3CFrame5[];
extern s32 D_800A2F3CFrame6[];
extern s32 D_800A2F3CFrame7[];
extern s32 D_800A39C8Frame1[];
extern s32 D_800A39C8Frame2[];
extern s32 D_800A39C8Frame3[];
extern s32 D_800A39C8Frame4[];
extern s32 D_800A39C8Frame5[];
extern s32 D_800A39C8Frame6[];
extern s32 D_800A39C8Frame7[];
extern s32 D_800A39C8Frame8[];
extern s32 gOrderingTableBankFrame1[];
extern s32 gOrderingTableBankFrame2[];
extern s32 gOrderingTableBankFrame3[];
extern s32 gOrderingTableBankFrame4[];
extern s32 gOrderingTableBankFrame5[];
extern s32 gOrderingTableBankFrame6[];
extern s32 gOrderingTableBankFrame7[];
extern s32 gOrderingTableBankFrame8[];
extern s32 gOrderingTableBankFrame9[];
extern s32 gOrderingTableBankFrame10[];
extern u8 *D_800A38ACFrameCam1A[];
extern u8 *D_800A38ACFrameCam1B[];
extern u8 *D_800A38ACFrameCam2A[];
extern u8 *D_800A38ACFrameCam2B[];
extern u8 *D_800A38ACFrameCam3A[];
extern u8 *D_800A38ACFrameCam3B[];
extern s32 gOrderingTableBankFrame3Read[];
extern s32 D_800A39C8Frame3Read[];
extern s32 gOrderingTableBankFrame8Read[];
extern s32 D_800A39C8Frame4Read[];
extern s32 D_800A39C8Frame5Read[];
extern s32 D_800A39C8Frame8Read[];

void GraphicsDrawRaceViews(void) {
    MATRIX rotation;
    register s32 previousCount asm("v0");
    u8 *drawCar;
    s32 bank;
    u8 *mainCamera;
    u8 *secondCamera;
    u8 *insetCamera;
    s32 secondTable;
    s32 tableOffset;
    s32 ticks;
    s32 bankAfterDraw;
    s32 bankAfterInset;
    register s32 randomIndex asm("v0");
    register s32 viewLimit asm("v0");
    u8 *car;
    u8 *insetCar;
    u8 *focusCar;

    focusCar = D_800A3554Frame[0];
    func_8002FFB8(1);
    if (D_800A2EDAFrame != 0) {
        focusCar = D_800A2E9CFrame;
        if (D_800A2EC0Frame >= 0x349) {
            if ((*(s8 *)(focusCar + 0x20C)) != 5) {
                (*(s32 *)(focusCar + 0x380)) =
                    (s32)(((*(s16 *)(focusCar + 0x114)) + 0x200) & 0x3FF);
            }
            (*(s8 *)(focusCar + 0x20C)) = 5;
        } else if (D_800A2EC0Frame >= 0x169) {
            (*(s8 *)(focusCar + 0x20C)) = 3;
        }
        if (D_800A2EC0Frame == ((D_800A2EC0Frame / 120) * 0x78)) {
            if (RandomScaledGet(0x18) < 0) {
                randomIndex = -RandomScaledGet(0x18);
            } else {
                randomIndex = RandomScaledGet(0x18);
            }
            D_800A2E9CFrame = D_800A3984Frame[0] + ((randomIndex + 1) * 0x500);
        }
    }
    ticks = GetRCnt(RCntCNT1);
    D_800A2EA0Frame = focusCar;
    D_800B9D54Frame[0] = ticks - D_800B9D54Frame[0];
    mainCamera = D_800A38ACFrame1[0];
    if (focusCar != mainCamera) {
        (*(u16 *)(mainCamera + 0x1E0)) = (u16)(*(u16 *)(focusCar + 0x1E0));
    } else {
        (*(u16 *)(D_800A38ACFrame2[0] + 0x1E0)) = func_8002482C(
            (*(s32 *)(focusCar + 0x0)), (*(s32 *)(focusCar + 0x4)),
            (s32 *)(focusCar + 0x1F8));
    }
    func_8002DA30((s32 *)D_800A38ACFrame3[0]);
    if (D_800A2ED8Frame != 0) {
        CameraUpdateForCar((RaceObject *)D_800A38ACFrameCam1A[0],
                           (RaceObject *)focusCar, D_800A2EC4Frame + 4);
    } else {
        CameraUpdateForCar((RaceObject *)D_800A38ACFrameCam1B[0],
                           (RaceObject *)focusCar, *(s8 *)(focusCar + 0x20C));
    }
    func_8001EC38((s32 *)D_800A38ACFrame5[0]);
    MatrixBuildRotationFromTransform((s32 *)D_800A38ACFrame6[0],
                                     (s32 *)&rotation);
    rotation.t[2] = 0;
    rotation.t[1] = 0;
    rotation.t[0] = 0;
    SetTransMatrix(&rotation);
    SetRotMatrix(&rotation);
    func_8002EEFC(focusCar);
    func_80034D64();
    previousCount = D_800A2E98Frame;
    D_800A2EBCFrame = 0;
    D_800A37B0Frame = previousCount;
    viewLimit = 0x352;
    if (D_800A3075Frame[0] == 0) {
        viewLimit = 0x44C;
    }
    D_800A2F08Frame = viewLimit;
    asm volatile("" : : : "memory");
    D_800A2E98Frame = 0;
    if (D_800A2EA4Frame == 2) {
        D_800A2F0CFrame = 0x4E2;
        D_800A2F10Frame = 0x44C;
        D_800A2F08Frame = (D_800A2F08Frame * 0x46) / 100;
        SetGeomScreen(0xD0);
        D_800A2E8CFrame = 0x23;
        GraphicsSetGeomOffsetForMode(gOrderingTableBankFrame1[0] == 0, 0);
        D_800A2F3CFrame1[0] = 0x46;
        func_8002E594(D_800A3554Frame[0]);
        car = D_800A3558Frame[0];
        if (car != NULL) {
            do {
                if ((*(s16 *)(car + 0x1EC)) >= 0) {
                    (*(u16 *)(car + 0x1E2)) = (u16)(*(u16 *)(car + 0x1E6));
                    (*(u16 *)(car + 0x1E4)) = (u16)(*(u16 *)(car + 0x1E8));
                }
                car = (*(u8 **)(car + 0x3E0));
            } while (car != NULL);
        }
        focusCar = (*(u8 **)(D_800A3554Frame[0] + 0x3E0));
        D_800A2F0CFrame = 0xA28;
        D_800A2F10Frame = 0x992;
        D_800A2ED9Frame = 1;
        D_800A2EA0Frame = focusCar;
        secondCamera = D_800A38ACFrame7[0];
        if (focusCar != secondCamera) {
            (*(u16 *)(secondCamera + 0x1E0)) =
                (u16)(*(u16 *)(focusCar + 0x1E0));
        } else {
            (*(u16 *)(D_800A38ACFrame8[0] + 0x1E0)) = func_8002482C(
                (*(s32 *)(focusCar + 0x0)), (*(s32 *)(focusCar + 0x4)),
                (s32 *)(focusCar + 0x1F8));
        }
        func_8002DA30((s32 *)D_800A38ACFrame9[0]);
        if (D_800A2ED8Frame != 0) {
            CameraUpdateForCar((RaceObject *)D_800A38ACFrameCam2A[0],
                               (RaceObject *)focusCar, D_800A2EC4Frame + 4);
        } else {
            CameraUpdateForCar((RaceObject *)D_800A38ACFrameCam2B[0],
                               (RaceObject *)focusCar,
                               *(s8 *)(focusCar + 0x20C));
        }
        func_8001EC38((s32 *)D_800A38ACFrame11[0]);
        MatrixBuildRotationFromTransform((s32 *)D_800A38ACFrame12[0],
                                         (s32 *)&rotation);
        rotation.t[2] = 0;
        rotation.t[1] = 0;
        rotation.t[0] = 0;
        SetTransMatrix(&rotation);
        SetRotMatrix(&rotation);
        func_8002EEFC(focusCar);
        GraphicsSetGeomOffsetForMode(gOrderingTableBankFrame2[0] == 0, 1);
        drawCar = *(u8 **)(D_800A3554Frame[0] + 0x3E0);
        bank = gOrderingTableBankFrame3Read[0] + 1;
        secondTable = D_800A39C8Frame1[0] + 0x1000;
        D_800A2F3CFrame2[0] = 0x3C;
        gOrderingTableBankFrame3[0] = bank;
        D_800A39C8Frame2[0] = secondTable;
        func_8002E594(drawCar);
        D_800A2ED9Frame = 0;
        bankAfterDraw = gOrderingTableBankFrame4[0] - 1;
        gOrderingTableBankFrame5[0] = bankAfterDraw;
        D_800A39C8Frame3[0] = D_800A39C8Frame3Read[0] - 0x1000;
        GraphicsSetGeomOffsetForMode(bankAfterDraw == 0, 2);
        D_800A2F3CFrame3[0] = 0x46;
    } else if ((D_800A2EC4Frame != 0) && (D_800A2EC8Frame == 0)) {
        D_800A2F10Frame = 0x578;
        D_800A2F0CFrame = 0x708;
        D_800A2F08Frame = (D_800A2F08Frame * 0x41) / 100;
        SetGeomScreen(0xD0);
        D_800A2E8CFrame = 0x23;
        GraphicsSetGeomOffsetForMode(gOrderingTableBankFrame6[0] == 0, 3);
        D_800A2F3CFrame4[0] = 0x82;
        func_8002E594(D_800A3554Frame[0]);
        insetCar = D_800A3558Frame[0];
        if (insetCar != NULL) {
            do {
                if ((*(s16 *)(insetCar + 0x1EC)) >= 0) {
                    (*(u16 *)(insetCar + 0x1E2)) =
                        (u16)(*(u16 *)(insetCar + 0x1E6));
                    (*(u16 *)(insetCar + 0x1E4)) =
                        (u16)(*(u16 *)(insetCar + 0x1E8));
                }
                insetCar = (*(u8 **)(insetCar + 0x3E0));
            } while (insetCar != NULL);
        }
        D_800A2ED8Frame = 1;
        SetGeomScreen(0x64);
        D_800A2E8CFrame = 0xA;
        GraphicsSetGeomOffsetForMode(gOrderingTableBankFrame7[0] == 0, 4);
        D_800A2F3CFrame5[0] = 0x1E;
        D_800A2F0CFrame = 0xA28;
        D_800A2F10Frame = 0x9C4;
        D_800A2F08Frame = (D_800A2F08Frame * 0x23) / 100;
        func_8002F674();
        focusCar = D_800A2E9CFrame;
        D_800A2EA0Frame = focusCar;
        insetCamera = D_800A38ACFrame13[0];
        if (focusCar != insetCamera) {
            (*(u16 *)(insetCamera + 0x1E0)) = (u16)(*(u16 *)(focusCar + 0x1E0));
        } else {
            (*(u16 *)(D_800A38ACFrame14[0] + 0x1E0)) = func_8002482C(
                (*(s32 *)(focusCar + 0x0)), (*(s32 *)(focusCar + 0x4)),
                (s32 *)(focusCar + 0x1F8));
        }
        func_8002DA30((s32 *)D_800A38ACFrame15[0]);
        if (D_800A2ED8Frame != 0) {
            CameraUpdateForCar((RaceObject *)D_800A38ACFrameCam3A[0],
                               (RaceObject *)focusCar, D_800A2EC4Frame + 4);
        } else {
            CameraUpdateForCar((RaceObject *)D_800A38ACFrameCam3B[0],
                               (RaceObject *)focusCar,
                               *(s8 *)(focusCar + 0x20C));
        }
        func_8001EC38((s32 *)D_800A38ACFrame17[0]);
        MatrixBuildRotationFromTransform((s32 *)D_800A38ACFrame18[0],
                                         (s32 *)&rotation);
        rotation.t[2] = 0;
        rotation.t[1] = 0;
        rotation.t[0] = 0;
        SetTransMatrix(&rotation);
        SetRotMatrix(&rotation);
        func_8002EEFC(focusCar);
        gOrderingTableBankFrame8[0] = gOrderingTableBankFrame8Read[0] + 1;
        D_800A39C8Frame4[0] = D_800A39C8Frame4Read[0] + 0x1000;
        func_8002FFB8(1);
        func_8002E594(D_800A2E9CFrame);
        bankAfterInset = gOrderingTableBankFrame9[0] - 1;
        gOrderingTableBankFrame10[0] = bankAfterInset;
        D_800A39C8Frame5[0] = D_800A39C8Frame5Read[0] - 0x1000;
        GraphicsSetGeomOffsetForMode(bankAfterInset == 0, 3);
        D_800A2F3CFrame6[0] = 0x82;
        D_800A2ED8Frame = 0;
    } else {
        D_800A2F0CFrame = 0xA28;
        D_800A2F10Frame = 0x898;
        SetGeomScreen(0xD0);
        D_800A2F3CFrame7[0] = 0x82;
        D_800A2E8CFrame = D_800A3774Frame + 0x32;
        tableOffset = D_800A39C8Frame6[0] + 0x28;
        D_800A39C8Frame7[0] = tableOffset;
        func_8002E594(focusCar);
        D_800A39C8Frame8[0] = D_800A39C8Frame8Read[0] - 0x28;
    }
    D_800B9D5CFrame[0] = GetRCnt(RCntCNT1) - D_800B9D5CFrame[0];
}

extern s32 D_800A3A80;
/* The right-height block uses its own endpoint locals so leftHeight keeps
 * retail's register; the pinned span keeps the divisor in v0. */
s32 func_800309DC(s32 arg0, s32 *object, s32 *query) {
    SVECTOR **points;
    s32 vyA;
    s32 vyB;
    SVECTOR *pairB;
    SVECTOR *pairA;
    SVECTOR *pointA;
    SVECTOR *pointB;
    SVECTOR *point;
    s32 sampleX;
    s32 sampleY;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 z0;
    s32 z1;
    s32 left;
    s32 right;
    s32 leftHeight;
    s32 result;
    int heightSpan;
    s32 i;
    sampleX = query[0];
    sampleY = query[1];
    pairA = 0;
    points = (SVECTOR **)(object + 6);
    for (i = 4; i > 0; i--) {
        pointA = points[i & 3];
        pointB = points[i - 1];
        vyB = pointB->vy;
        vyA = pointA->vy;
        if (vyA < vyB) {
            point = pointB;
            pointB = pointA;
            pointA = point;
        }
        if (sampleY < pointB->vy) {
            continue;
        }
        if (sampleY >= pointA->vy) {
            continue;
        }
        if (pointB->vy == pointA->vy) {
            continue;
        }
        if (pairA == 0) {
            pairA = pointB;
            pairB = pointA;
            continue;
        }
        x0 = pairA->vx;
        x1 = pairB->vx;
        y0 = pairA->vy;
        y1 = pairB->vy;
        if (y1 == y0) {
            left = x0;
        } else {
            left = x0 + (((x1 - x0) * (sampleY - y0)) / (y1 - y0));
        }
        x0 = pointB->vx;
        x1 = pointA->vx;
        y0 = pointB->vy;
        y1 = pointA->vy;
        if (y1 == y0) {
            right = x0;
        } else if (pointA) {
            /* Identical arms retain the permuter-found endpoint allocation. */
            right = x0 + (((x1 - x0) * (sampleY - y0)) / (y1 - y0));
        } else {
            right = x0 + (((x1 - x0) * (sampleY - y0)) / (y1 - y0));
        }
        if (right < left) {
            y1 = left;
            left = right;
            right = y1;
            point = pairA;
            pairA = pointB;
            pointB = point;
            point = pairB;
            pairB = pointA;
            pointA = point;
        }
        if (sampleX < (left - 5)) {
            return 0;
        }
        if ((right + 5) < sampleX) {
            return 0;
        }
        z0 = pairA->vz;
        z1 = pairB->vz;
        y0 = pairA->vy;
        y1 = pairB->vy;
        if (y1 == y0) {
            leftHeight = z0;
        } else {
            heightSpan = y1 - y0;
            leftHeight = sampleY;
            leftHeight = z0 + (((z1 - z0) * (leftHeight - y0)) / heightSpan);
        }
        {
            s32 endY;
            register s32 span asm("$2");
            s32 endZ;

            z0 = pointB->vz;
            endZ = pointA->vz;
            y0 = pointB->vy;
            endY = pointA->vy;
            if (endY == y0) {
                result = z0;
            } else {
                result = (endZ - z0) * (sampleY - y0);
                span = endY - y0;
                result = z0 + (result / span);
            }
        }
        if (right == left) {
            result = leftHeight;
        } else {
            result = leftHeight + (((result - leftHeight) * (sampleX - left)) /
                                   (right - left));
        }
        query[2] = result;
        D_800A3A80 = object;
        return 1;
    }

    return 0;
}

s32 func_800309DC(s32, s32 *, s32 *);
void func_80030CDC(s32 *query, s32 index) {
    s8 *node;
    u8 *entries;

    if (index >= 0) {
        entries = (u8 *)D_800BE980[0];
        entries += index * 0x90;
        node = *(s8 **)(entries + 0x20);
        while ((node != NULL) && (((u8)node[0x13] & 0x80) == 0)) {
            if ((node[2] < 0) &&
                ((func_800309DC(D_800A38AC[0], (s32 *)node, query) & 0xFF) !=
                 0)) {
                return;
            }
            node = *(s8 **)(node + 0x28);
        }
    }
}

/* The D_800A3A80 store sits before the second unk1E0 read so cse reloads it.
 * Struct-typed reads (unk1E0, unk20) carry no dependence on that store, so
 * sched sinks it below the unk20 load as retail does. */
void func_80030D80(RaceObject *object, s32 *query) {
    s8 *node;
    u8 *entry;
    s16 rot;

    rot = object->unk1E0;
    if (rot >= 0) {
        D_800A3A80 = 0;
        entry = object->unk1E0 * 0x90 + (u8 *)D_800BE980[0];
        node = (s8 *)((TrackRacer *)entry)->unk20;
        while ((node != NULL) && (((u8)node[0x13] & 0x80) == 0)) {
            if ((node[2] < 0) &&
                ((func_800309DC((s32 *)object, (s32 *)node, query) & 0xFF) !=
                 0)) {
                return;
            }
            node = *(s8 **)(node + 0x28);
        }
        entry = *(u8 **)(entry + 0);
        object->unk1E0 = *(u16 *)(entry + 8);
        node = *(s8 **)(entry + 0x20);
        while ((node != NULL) && (((u8)node[0x13] & 0x80) == 0)) {
            if ((node[2] < 0) &&
                ((func_800309DC((s32 *)object, (s32 *)node, query) & 0xFF) !=
                 0)) {
                return;
            }
            node = *(s8 **)(node + 0x28);
        }
        entry = *(u8 **)(*(u8 **)(entry + 4) + 4);
        object->unk1E0 = *(u16 *)(entry + 8);
        node = *(s8 **)(entry + 0x20);
        while ((node != NULL) && (((u8)node[0x13] & 0x80) == 0)) {
            if ((node[2] < 0) &&
                ((func_800309DC((s32 *)object, (s32 *)node, query) & 0xFF) !=
                 0)) {
                return;
            }
            node = *(s8 **)(node + 0x28);
        }
    }
}

extern s32 D_800A2F2C;
extern s32 D_800A2F2CAbsolute[];
extern s32 D_800A384CAbsolute[];
extern s32 D_800AE848[];
extern s32 D_800AE84C[];
extern s32 D_800B6094[];
u16 func_80030F24(u8 *object, s32 *pointArray, s32 arg2, s32 arg3, s32 arg4) {
    s32 point[3];
    s32 outX;
    s32 outZ;
    s16 *tableA;
    s16 *tableB;
    s32 offset;
    s32 value;
    s16 result16;

    offset =
        (*(s16 *)(object + 0x116) + *(s16 *)(object + 0x118) + 0x1000) & 0xFFF;
    tableA = (s16 *)D_800A384CAbsolute[0];
    tableB = (s16 *)D_800A3854Absolute[0];
    pointArray[0] +=
        ((tableA[offset] * arg2 - tableB[offset] * arg3) >> 16) * 4;
    pointArray[1] +=
        ((tableB[offset] * arg2 + tableA[offset] * arg3) >> 16) * 4;
    pointArray[2] = 0;
    if (*(s16 *)(object + 0x1EC) == 0) {
        if (D_800A2F2C > 0) {
            D_800A2F2C = D_800A2F2C - 1;
        }
    }
    *(s16 *)(object + 0x1E0) = (s16)func_80024E90(
        pointArray[0], pointArray[1], D_800A2F2CAbsolute, &outX, &outZ);
    *(Vec3 *)(object + 0xDC) = *(Vec3 *)D_800B6094;
    result16 = *(s16 *)(object + 0x1E0);
    if (result16 == -1) {
        *(u8 *)(object + 0xF5) = 1;
        return 0;
    }
    *(s32 *)(object + 0x1F8) = result16;
    if ((*(s16 *)(object + 0x1EC) == 0) && (outZ == 2)) {
        point[0] = pointArray[0] / 4 - D_800AE844[0];
        point[1] = pointArray[1] / 4 - D_800AE848[0];
        func_80030D80((RaceObject *)object, point);
        pointArray[2] = (point[2] + D_800AE84C[0]) * 4;
        if (D_800A3A80 == 0 || (*(u8 *)((u8 *)D_800A3A80 + 0x13) & 8) == 0) {
            value = 5;
        } else {
            value = 2;
        }
        *(s16 *)(object + 0x360) = value;
        if (D_800A3A80 == 0) {
            pointArray[2] = outX * 4;
        }
    } else {
        pointArray[2] = outX * 4;
        *(s16 *)(object + 0x360) = outZ;
    }
    if (*(s16 *)(object + 0x1E0) < *(s16 *)(object + 0x1E2)) {
        *(s16 *)(object + 0x1E2) = *(s16 *)(object + 0x1E0);
    }
    if (*(s16 *)(object + 0x1E4) < *(s16 *)(object + 0x1E0)) {
        *(s16 *)(object + 0x1E4) = *(s16 *)(object + 0x1E0);
    }
    return *(u16 *)(object + 0x360);
}

void func_800311B4(s32 x, s32 y, s32 z, s32 *out) {
    s32 length;

    length = MathSqrt(x * x + y * y + z * z);
    if (length == 0) {
        length = 1;
    }
    out[0] = MathFixedDivide(x, length);
    out[1] = MathFixedDivide(y, length);
    out[2] = MathFixedDivide(z, length);
}

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vector3;

extern s32 D_800A397C[];
void func_800319D4(u8 *, s32);
void func_8001F198(void);
u16 func_80030F24(u8 *, s32 *, s32, s32, s32);
extern s16 func_8002482Cs16(s32, s32, void *) asm("func_8002482C");
void func_8001F5BC(s32, s32, s32);
typedef struct {
    u8 pad[0x1C];
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
} ObjectBounds;

void func_80031264(u8 *object) {
    s32 corners[5][4];
    s32 normals[3][4];
    ObjectBounds *state;
    s32 length;
    s32 sum;
    s32 result;
    s32 i;
    s32 a;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
    s32 sum4;
    s32 crossX;
    s32 crossY;
    s32 crossZ;

    state = *(ObjectBounds **)(object + 0x370);
    if (*(s16 *)(object + 0x1EC) != 0) {
        func_800319D4(object, 0);
        return;
    }
    corners[0][0] = corners[1][0] = corners[2][0] = corners[3][0] =
        corners[4][0] = *(s32 *)(object + 0x0);
    corners[0][1] = corners[1][1] = corners[2][1] = corners[3][1] =
        corners[4][1] = *(s32 *)(object + 0x4);
    corners[0][2] = corners[1][2] = corners[2][2] = corners[3][2] =
        corners[4][2] = *(s32 *)(object + 0x8);
    *(Vector3 *)(object + 0x3C) = *(Vector3 *)(object + 0x18);
    *(Vector3 *)(object + 0x48) = *(Vector3 *)(object + 0x24);
    *(Vector3 *)(object + 0x54) = *(Vector3 *)(object + 0x30);
    func_8001EEC4((s32 *)object);
    func_8001F198();
    *(s16 *)(object + 0x1E2) = 0x7D00;
    *(s16 *)(object + 0x1E4) = -1;
    *(u8 *)(object + 0xF5) = 0;
    D_800A2F2C = *(s32 *)(object + 0x1F8);
    *(s16 *)(object + 0x362) =
        func_80030F24(object, corners[3], state->unk1E, state->unk22, 0);
    *(s16 *)(object + 0x364) =
        func_80030F24(object, corners[0], state->unk1E, state->unk20, 0);
    *(s16 *)(object + 0x366) =
        func_80030F24(object, corners[2], state->unk1C, state->unk22, 0);
    *(s16 *)(object + 0x368) =
        func_80030F24(object, corners[1], state->unk1C, state->unk20, 0);
    *(s16 *)(object + 0x1E0) = func_8002482Cs16(
        *(s32 *)(object + 0x0), *(s32 *)(object + 0x4), object + 0x1F8);
    if (*(u16 *)(object + 0x362) == 0) {
        corners[3][2] = *(s32 *)(object + 0x8);
    }
    if (*(u16 *)(object + 0x364) == 0) {
        corners[0][2] = *(s32 *)(object + 0x8);
    }
    if (*(u16 *)(object + 0x366) == 0) {
        corners[2][2] = *(s32 *)(object + 0x8);
    }
    if (*(u16 *)(object + 0x368) == 0) {
        corners[1][2] = *(s32 *)(object + 0x8);
    }
    *(s32 *)(object + 0x318) = corners[3][2];
    *(s32 *)(object + 0x340) = corners[0][2];
    *(s32 *)(object + 0x2C8) = corners[2][2];
    *(s32 *)(object + 0x2F0) = corners[1][2];
    sum = corners[0][2] + corners[1][2] + corners[2][2] + corners[3][2];
    if (sum < 0) {
        sum += 3;
    }
    sum4 = sum >> 2;
    if ((*(s16 *)(object + 0x1BC) == 0) || (D_800A397C[0] == 2)) {
        corners[0][2] += *(s16 *)(object + 0x324);
        corners[1][2] += *(s16 *)(object + 0x2D4);
        corners[2][2] += *(s16 *)(object + 0x2AC);
        corners[3][2] += *(s16 *)(object + 0x2FC);
        result = *(s16 *)(object + 0x324) + *(s16 *)(object + 0x2D4) +
                 *(s16 *)(object + 0x2AC) + *(s16 *)(object + 0x2FC);
        if (result < 0) {
            result += 3;
        }
        result >>= 2;
        *(s16 *)(object + 0xFE) = result;
    } else {
        for (i = 0; i < 4; i++) {
            *(u16 *)(object + i * 0x28 + 0x2AC) = *(u16 *)(object + 0x39A);
        }
        *(s16 *)(object + 0xFE) = *(u16 *)(object + 0x39A);
    }
    *(s32 *)(object + 0x8) = *(s16 *)(object + 0xFE) + sum4;
    *(s16 *)(object + 0x1E8) = *(u16 *)(object + 0x1E4);
    *(s16 *)(object + 0x1E6) = *(u16 *)(object + 0x1E2);
    c = corners[2][1] - corners[1][1];
    sum4 = corners[2][2] - corners[1][2];
    a = corners[0][1] - corners[1][1];
    d = corners[0][2] - corners[1][2];
    e = corners[2][0] - corners[1][0];
    f = corners[0][0] - corners[1][0];
    a >>= 2;
    sum4 >>= 2;
    c >>= 2;
    d >>= 2;
    e >>= 2;
    f >>= 2;
    crossX = a * sum4 - d * c;
    crossY = d * e - f * sum4;
    crossZ = f * c - a * e;
    length = MathSqrt(crossX * crossX + crossY * crossY + crossZ * crossZ);
    if (length == 0) {
        length = 1;
    }
    normals[2][0] = MathFixedDivide(crossX, length);
    normals[2][1] = MathFixedDivide(crossY, length);
    normals[2][2] = MathFixedDivide(crossZ, length);
    length = MathSqrt(f * f + a * a + d * d);
    if (length == 0) {
        length = 1;
    }
    normals[0][0] = MathFixedDivide(f, length);
    normals[0][1] = MathFixedDivide(a, length);
    normals[0][2] = MathFixedDivide(d, length);
    length = MathSqrt(e * e + c * c + sum4 * sum4);
    if (length == 0) {
        length = 1;
    }
    normals[1][0] = MathFixedDivide(e, length);
    normals[1][1] = MathFixedDivide(c, length);
    normals[1][2] = MathFixedDivide(sum4, length);
    *(Vector3 *)(object + 0x3C) = *(Vector3 *)normals[0];
    *(Vector3 *)(object + 0x48) = *(Vector3 *)normals[1];
    *(Vector3 *)(object + 0x54) = *(Vector3 *)normals[2];
    func_8001F5BC(0, (0x3FF - *(s16 *)(object + 0x38A)) & 0x3FF,
                  *(u16 *)(object + 0x388) & 0x3FF);
    func_8001EC38((s32 *)object);
    MatrixCombineState();
    MatrixStoreToObject((s32 *)object);
}

void OuterProduct0(s32 *, s32 *, s32 *);
void VectorNormal(s32 *, s32 *, s32);
void func_80031874(u8 *quad, s32 *normal) {
    s32 vecA[3];
    s32 vecB[3];
    s32 cross[3];
    s32 crossX;
    s32 crossY;
    s32 crossZ;
    u8 *back;

    if ((quad == NULL) || ((*(u8 *)(quad + 0x13) & 0x20) != 0)) {
        normal[0] = 0;
        normal[1] = 0;
        normal[2] = 0x10000;
        return;
    }
    back = quad + 0x1C;
    vecA[0] = *(s16 *)(*(u8 **)(quad + 0x20) + 0) - *(s16 *)(*(u8 **)back + 0);
    vecA[1] = *(s16 *)(*(u8 **)(quad + 0x20) + 2) - *(s16 *)(*(u8 **)back + 2);
    vecA[2] = *(s16 *)(*(u8 **)(quad + 0x20) + 4) - *(s16 *)(*(u8 **)back + 4);
    vecB[0] = *(s16 *)(*(u8 **)(quad + 0x18) + 0) - *(s16 *)(*(u8 **)back + 0);
    vecB[1] = *(s16 *)(*(u8 **)(quad + 0x18) + 2) - *(s16 *)(*(u8 **)back + 2);
    vecB[2] = *(s16 *)(*(u8 **)(quad + 0x18) + 4) - *(s16 *)(*(u8 **)back + 4);
    OuterProduct0(vecA, vecB, cross);
    crossX = cross[0];
    crossY = cross[1];
    crossZ = cross[2];
    cross[0] = (crossX >>= 6);
    cross[1] = (crossY >>= 6);
    cross[2] = (crossZ >>= 6);
    VectorNormal(cross, normal, crossZ);
    normal[0] = normal[0] * 0x10;
    normal[1] = normal[1] * 0x10;
    normal[2] = normal[2] * 0x10;
}

/* VectorNormal reads two arguments here; a third one changes the load order
 * before its call. The three-axis copies at the end are Vector3 assignments. */
extern void VectorNormal2(s32 *, s32 *) asm("VectorNormal");
void func_800319D4(u8 *object, s32 arg1) {
    s32 corners[5][4];
    s32 vecA[3];
    s32 cross[3];
    s32 normalOut[3];
    s32 temp1;
    s32 temp2;
    s32 index;
    s32 sum;
    s32 sum4;
    s32 value;
    u16 result;

    value = *(s32 *)(object + 0x0);
    corners[4][0] = value;
    corners[3][0] = value;
    corners[2][0] = value;
    corners[1][0] = value;
    corners[0][0] = value;
    value = *(s32 *)(object + 0x4);
    corners[4][1] = value;
    corners[3][1] = value;
    corners[2][1] = value;
    corners[1][1] = value;
    corners[0][1] = value;
    value = *(s32 *)(object + 0x8);
    corners[4][2] = value;
    corners[3][2] = value;
    corners[2][2] = value;
    corners[1][2] = value;
    corners[0][2] = value;
    *(Vector3 *)(object + 0x3C) = *(Vector3 *)(object + 0x18);
    *(Vector3 *)(object + 0x48) = *(Vector3 *)(object + 0x24);
    *(Vector3 *)(object + 0x54) = *(Vector3 *)(object + 0x30);
    func_8001EEC4((s32 *)object);
    func_8001F198();
    *(u8 *)(object + 0xF5) = 0;
    *(s16 *)(object + 0x116) = *(s16 *)(object + 0x114) * 4;
    if (arg1 == 0) {
        *(s16 *)(object + 0x1E2) = 0x7D00;
        *(s16 *)(object + 0x1E4) = -1;
        D_800A2F2C = *(s32 *)(object + 0x1F8);
        result = func_80030F24(object, corners[3], 0, 0, 0);
        *(s16 *)(object + 0x362) = result;
        *(s16 *)(object + 0x364) = result;
        *(s16 *)(object + 0x366) = *(u16 *)(object + 0x362);
        *(s16 *)(object + 0x368) = *(u16 *)(object + 0x362);
    }
    vecA[0] = *(s32 *)(object + 0xDC);
    vecA[1] = *(s32 *)(object + 0xE0);
    index = *(s16 *)(object + 0x114) * 4;
    temp1 = (*(s32 *)(index + (u32)D_800A3A2CAbsolute[0]) << 8) >> 16;
    temp2 = (*(s32 *)(index + (u32)D_800A3A34Absolute[0]) << 8) >> 16;
    corners[0][0] = temp1;
    corners[1][1] = temp1;
    corners[0][1] = temp2;
    corners[1][0] = -temp2;
    corners[0][2] = -((vecA[0] * temp1 + vecA[1] * temp2) >> 16);
    corners[1][2] = -((vecA[0] * -temp2 + vecA[1] * temp1) >> 16);
    if (arg1 == 0) {
        corners[0][2] += *(s16 *)(object + 0x324) - *(s16 *)(object + 0x2D4);
        corners[1][2] += *(s16 *)(object + 0x2AC) - *(s16 *)(object + 0x2D4);
        sum = *(s16 *)(object + 0x324) + *(s16 *)(object + 0x2D4) +
              *(s16 *)(object + 0x2AC) + *(s16 *)(object + 0x2FC);
        sum4 = sum / 4;
        *(s16 *)(object + 0x1BE) = sum4;
        *(s32 *)(object + 0x8) = corners[3][2] + (s16)sum4;
        *(s16 *)(object + 0x1E8) = *(u16 *)(object + 0x1E4);
        *(s16 *)(object + 0x1E6) = *(u16 *)(object + 0x1E2);
    } else {
        *(s16 *)(object + 0x1E4) = -1;
        *(s16 *)(object + 0x1E2) = -1;
    }
    OuterProduct0(corners[0], corners[1], cross);
    cross[0] >>= 6;
    cross[1] >>= 6;
    cross[2] >>= 6;
    VectorNormal2(cross, normalOut);
    normalOut[0] = normalOut[0] * 16;
    normalOut[1] = normalOut[1] * 16;
    normalOut[2] = normalOut[2] * 16;
    VectorNormal2(corners[0], vecA);
    VectorNormal2(corners[1], cross);
    vecA[0] = vecA[0] * 16;
    vecA[1] = vecA[1] * 16;
    vecA[2] = vecA[2] * 16;
    cross[0] = cross[0] * 16;
    cross[1] = cross[1] * 16;
    cross[2] = cross[2] * 16;
    *(Vector3 *)(object + 0x3C) = *(Vector3 *)vecA;
    *(Vector3 *)(object + 0x48) = *(Vector3 *)cross;
    *(Vector3 *)(object + 0x54) = *(Vector3 *)normalOut;
}
extern s32 D_800A3574Lui asm("D_800A3574Absolute");

typedef struct ModelVector {
    SVECTOR point;
    s32 x;
    s32 y;
    s32 z;
} ModelVector;

typedef struct ModelFace {
    u8 unk0;
    s8 depthOffset;
    u8 mode;
    u8 unk3;
    u32 color;
    u8 u0, v0;
    u16 unkA;
    u8 u1, v1;
    u16 unkE;
    u8 u2, v2;
    u8 vertexCount;
    u8 flags;
    u8 u3, v3;
    u16 tpage;
    ModelVector *vectors[4];
    struct ModelFace *next;
} ModelFace;

typedef struct ModelOffset {
    s16 first;
    s16 last;
    s32 x;
    s32 y;
    s32 z;
    s16 unk10;
    s16 unk12;
    s16 type;
    s16 unk16;
} ModelOffset;

typedef struct ModelGeometry {
    u8 unk0[0x14];
    ModelVector *vectors;
    u8 unk18[0x10];
    s16 vectorCount;
    s16 faceCount;
    u16 offsetCount;
    s16 specialOffset;
    s16 unk30;
    s16 unk32;
    ModelFace *faces;
    ModelFace *faceStorage;
    void *unk3C;
    ModelOffset *offsets;
} ModelGeometry;

extern s32 D_800A353CLui asm("D_800A353CAbsolute");
extern s32 D_800A3758Lui asm("D_800A3758Absolute");
extern s32 D_800A2F30;
extern ModelVector *D_800AE130[];
extern char sObjectVectorsAllocationError[], sObjectFacesAllocationError[],
    sObjectOffsetsAllocationError[];

void ObjectLoadGeometry(ModelGeometry *model, u8 *data, s32 reuse) {
    ModelFace *faceTable[1436];
    s32 offsetCount;
    u8 *offsetData;
    ModelVector *vector;
    s16 *sourceVector;
    u8 *sourceFace;
    ModelFace *faces;
    s32 vectorCount;
    s32 faceCount;
    s32 i;
    s32 j;
    s32 count;
    ModelFace *face;
    ModelOffset *offset;
    s32 span;
    s32 x;
    s32 y;
    s32 z;
    u32 vectorOffset;
    u32 faceOffset;
    u32 offsetsOffset;
    u8 *offsetSource;

    vectorCount = *(s16 *)data;
    vectorOffset = *(u32 *)(data + 8);
    faceOffset = *(u32 *)(data + 12);
    offsetsOffset = *(u32 *)(data + 16);
    model->vectorCount = vectorCount;
    faceCount = *(s16 *)(data + 2);
    model->faceCount = faceCount;
    sourceVector = (s16 *)(data + vectorOffset);
    sourceFace = data + faceOffset;
    offsetCount = (*(u32 *)(data + 20) - *(u32 *)(data + 16)) / 24;
    offsetData = data + offsetsOffset;
    model->unk32 = 0;
    model->unk30 = -1;
    model->offsetCount = offsetCount;
    if (reuse == -1) {
        vector = HeapAlloc((vectorCount + 2) * sizeof(ModelVector));
        if (vector == NULL) {
            SystemShowFatalError(sObjectVectorsAllocationError);
        }
        model->vectors = vector;
        D_800AE130[D_800A2F30++] = vector;
    } else {
        vector = D_800AE130[reuse];
        model->vectors = vector;
    }
    faces = HeapAlloc(faceCount * sizeof(ModelFace));
    if (faces == NULL) {
        SystemShowFatalError(sObjectFacesAllocationError);
    }
    model->faceStorage = faces;
    if (offsetCount != 0) {
        model->offsets = HeapAlloc(offsetCount * sizeof(ModelOffset));
        if (model->offsets == NULL) {
            SystemShowFatalError(sObjectOffsetsAllocationError);
        }
    } else {
        model->offsets = NULL;
    }
    if (reuse == -1) {
        for (i = 0; i < vectorCount; i++) {
            vector->y =
                -(MathMultiplyFixed16(sourceVector[0] << 16, D_800A3758Lui) >>
                  16);
            vector->x =
                MathMultiplyFixed16(sourceVector[1] << 16, D_800A353CLui) >> 16;
            vector->z =
                MathMultiplyFixed16(sourceVector[2] << 16, D_800A353CLui) >> 16;
            /* Keep one vector cursor and reload all three coordinates. */
            asm("" : "=r"(vector) : "0"(vector));
            x = vector->x;
            y = vector->y;
            z = vector->z;
            vector->point.vx = x;
            vector->point.vy = y;
            vector->point.vz = z;
            sourceVector += 3;
            vector++;
        }
    }
    model->faces = NULL;
    for (i = 0; i < faceCount; i++) {
        face = faces + i;
        faceTable[i] = face;
        face->next = model->faces;
        model->faces = face;
        if (sourceFace[0] & 1) {
            count = 4;
            face->vertexCount = 4;
        } else {
            count = 3;
            face->vertexCount = 3;
        }
        if (sourceFace[0] & 2) {
            if (sourceFace[0] & 8) {
                face->mode = 6;
            } else {
                face->mode = 0;
            }
        } else if (sourceFace[0] & 8) {
            face->mode = 5;
        } else if (sourceFace[0] & 4) {
            face->mode = 4;
        } else {
            face->mode = 3;
        }
        face->color = *(u32 *)(sourceFace + 20);
        face->depthOffset = sourceFace[1];
        face->flags = 0;
        for (j = 0; j < count; j++) {
            face->vectors[j] = model->vectors + ((s16 *)sourceFace)[j + 1];
        }
        if (j == 3) {
            face->vectors[3] = face->vectors[0];
        }
        face->tpage = *(u16 *)(sourceFace + 10);
        for (j = 0; j < 3; j++) {
            ((u8 *)face)[8 + j * 4] = sourceFace[12 + j * 2];
            ((u8 *)face)[9 + j * 4] = sourceFace[13 + j * 2];
        }
        if (face->vertexCount >= 4) {
            face->u2 = sourceFace[18];
            face->v2 = sourceFace[19];
            face->u3 = sourceFace[16];
            face->v3 = sourceFace[17];
        }
        sourceFace += 24;
    }
    model->unk3C = NULL;
    for (i = 0; i < offsetCount; i++) {
        offsetSource = offsetData + i * 24;
        model->offsets[i].first = *(u16 *)(offsetSource + 0);
        model->offsets[i].last = *(u16 *)(offsetSource + 2);
        model->offsets[i].unk10 = *(u16 *)(offsetSource + 16);
        model->offsets[i].unk12 = *(u16 *)(offsetSource + 18);
        model->offsets[i].type = *(u16 *)(offsetSource + 20);
        model->offsets[i].y =
            -(MathMultiplyFixed16(*(s32 *)(offsetSource + 4) << 16,
                                  D_800A3758Lui) >>
              16);
        model->offsets[i].x =
            MathMultiplyFixed16(*(s32 *)(offsetSource + 8) << 16,
                                D_800A353CLui) >>
            16;
        model->offsets[i].z =
            MathMultiplyFixed16(*(s32 *)(offsetSource + 12) << 16,
                                D_800A353CLui) >>
            16;
        if (*(s16 *)(offsetSource + 20) < 0) {
            if (*(s16 *)(offsetSource + 20) == -1) {
                model->specialOffset = i;
            }
        } else {
            offset = model->offsets + i;
            vector = model->vectors + offset->first;
            span = offset->last - offset->first + 1;
            if (offset->type != 10) {
                for (count = 0; count < span; count++) {
                    vector->point.vx = vector->x - offset->x;
                    vector->point.vy = vector->y - offset->y;
                    vector->point.vz = vector->z - offset->z;
                    vector++;
                }
            }
        }
    }
}
INCLUDE_RODATA("asm/nonmatchings/objects", sObjectVectorsAllocationError);
INCLUDE_RODATA("asm/nonmatchings/objects", sObjectFacesAllocationError);
INCLUDE_RODATA("asm/nonmatchings/objects", sObjectOffsetsAllocationError);

extern s32 FileOpenCall32328(s32, void *) asm("FileOpen");
extern s32 FileSeekCall32328(void *, s32, s32) asm("FileSeek");
extern void FileReadCall32328(s32, s32, s32, s32) asm("FileRead");
extern void FileCloseCall32328(s32) asm("FileClose");
extern void ObjectLoadGeometry(ModelGeometry *, u8 *, s32);
extern char D_8008D08C[];
extern void *D_800A2F34[];
extern s32 D_800A3574[];
extern u8 D_800A2D4C[], D_800A2D4D[];
void func_80032328(s32 arg0) {
    s32 value;
    s32 handle;

    handle = FileOpenCall32328(arg0, D_800A2F34);
    if (handle == 0) {
        SystemShowFatalError(D_8008D08C);
    }
    value = FileSeekCall32328(handle, 0, 2);
    FileSeekCall32328(handle, 0, 0);
    FileReadCall32328(STACK_BLOCK_801C0000, value, 1, handle);
    ObjectLoadGeometry((ModelGeometry *)D_800A3574Lui,
                       (u8 *)STACK_BLOCK_801C0000, -1);
    D_800A2D4C[0] = 1;
    func_80025454(D_800A3574Lui);
    D_800A2D4D[0] = 0;
    FileCloseCall32328(handle);
}

INCLUDE_RODATA("asm/nonmatchings/objects", D_8008D08C);

/*
 * The second D_800A3574 read goes through the D_800A36D0Absolute
 * neighbor ((s32 *)0x800A36D0)[-87] so gcc cannot CSE the address
 * materialization across the first call; the -87*4 delta folds into
 * the %lo displacement (0x36D0 - 0x15C = 0x3574).
 */
void func_80025454(s32);
void ObjectLoadGeometry(ModelGeometry *, u8 *, s32);
void func_800323F0(s32 index, s32 arg1) {
    ObjectLoadGeometry((ModelGeometry *)D_800A3574Lui,
                       *(u8 **)(D_800B9F44 + index), arg1);
    D_800A2D4C[0] = 1;
    func_80025454(D_800A3574Lui);
    D_800A2D4D[0] = 0;
}

void ObjectLoadGeometry(ModelGeometry *, u8 *, s32);
void func_80032450(s32 first, s32 second) {
    ObjectLoadGeometry((ModelGeometry *)D_800A3574[0], (u8 *)first, second);
    D_800A2D4C[0] = 1;
    D_800A2D4D[0] = 0;
}

void func_80032494(u8 *object) {
    u8 *node;

    node = *(u8 **)(object + 0x3C);
    if (node != NULL) {
        *(s32 *)(object + 0x34) = 0;
        do {
            if (*(s32 *)(node + 0x8) != 0) {
                *(s32 *)(*(s32 *)(node + 0xC) + 0x28) = *(s32 *)(object + 0x34);
                *(s32 *)(object + 0x34) = *(s32 *)(node + 0x8);
            }
            node = *(u8 **)(node + 0x4);
        } while (node != NULL);
    }
}

void GraphicsLinkPrimitive(u32 *orderingTable, u32 *primitive) {
    u32 old;
    u32 tag;
    old = *orderingTable;
    tag = *primitive;
    tag &= 0xFF000000;
    tag |= old & 0xFFFFFF;
    *primitive = tag;
    *orderingTable = (old & 0xFF000000) | ((u32)primitive & 0xFFFFFF);
}

void GraphicsAddTaggedPrimitive(u32 *orderingTable, u32 *primitive, u32 tag) {
    *primitive = tag | *orderingTable;
    *orderingTable = (u32)primitive & 0xFFFFFF;
}

extern u8 D_800A2DE0[];

u8 *func_80032544(u8 *obj, s32 count) {
    u8 *prim;
    u32 *ot;
    s32 gte;
    u32 *otEntry;

    ot = (u32 *)(D_800A39C8[0] + 0x20);
    prim = (u8 *)gPrimitiveCursor[0];
    while (count > 0) {
        gte_ldv3(*(s32 **)(obj + 0x18), *(s32 **)(obj + 0x1C),
                 *(s32 **)(obj + 0x20));
        gte_rtpt();
        SetPolyF4(prim);
        SetSemiTrans(prim, 1);
        gte_ReadFlag(gte);
        if (gte & 0x66000) {
            goto next;
        }
        gte_nclip();
        prim[4] = 16;
        prim[5] = 16;
        prim[6] = 16;
        gte_mfc2(gte, 24);
        if (D_800A2DE0[0] != 0) {
            if (gte >= 0) {
                goto draw;
            }
            goto next;
        } else if (gte > 0) {
            goto next;
        }
    draw:
        gte_avsz3();
        gte_mfc2(gte, 7);
        gte += *(s8 *)(obj + 1) * 4;
        gte_stsxy3(prim + 8, prim + 0xC, prim + 0x14);
        gte_ldv0(*(s32 **)(obj + 0x24));
        gte_rtps();
        gte_stsxy(prim + 0x10);
        otEntry = (u32 *)(((gte >> 4) << 2) + (s32)ot);
        *(u32 *)prim = *otEntry | 0x05000000;
        *otEntry = (u32)prim & 0xFFFFFF;
        prim += 0x18;
    next:
        count--;
        obj += 0x2C;
    }
    gPrimitiveCursor[0] = (u32)prim;
    prim = obj;
    return prim;
}

void func_8003271C(s32 arg0) {
    u32 i;
    u32 *pad;

    i = 0;
    pad = (u32 *)SCRATCHPAD_BASE;
    do {
        if (arg0 < 0) {
            pad[0] = 0;
        } else {
            pad[0] = (i << 0x10) | (i << 8) | i;
        }
        pad += 1;
        i += 1;
        arg0 += 1;
    } while (i < 0x100U);
}

/*
 * Handwritten-GTE textured triangle renderer: rtpt on three vertices,
 * backface cull on nclip gated by the D_800A2DE0 double-sided flag, then
 * link one primitive into the ordering table at D_800A39C8[0] + 0x20.
 */
u8 *func_80032760(u8 *obj, u8 *prim, s32 count) {
    u8 *ot;
    u32 doubleSided;
    s32 gte;
    s32 depthBias;
    u8 *nextPrim;
    u32 *otEntry;
    s32 flagMask;

    ot = (u8 *)D_800A39C8[0] + 0x20;
    doubleSided = D_800A2DE0[0];
    flagMask = 0x66000;
    while (count > 0) {
        gte_ldv3(*(s32 **)(obj + 0x18), *(s32 **)(obj + 0x1C),
                 *(s32 **)(obj + 0x20));
        gte_rtpt();
        depthBias = *(s8 *)(obj + 1) * 4;
        nextPrim = *(u8 **)(prim + 0x34);
        gte_ReadFlag(gte);
        if (gte & flagMask) {
            goto next;
        }
        gte_op(nclip);
        gte_mfc2_nonop(gte, 24);
        if (doubleSided != 0) {
            if (gte >= 0) {
                goto draw;
            }
            goto next;
        } else if (gte > 0) {
            goto next;
        }
    draw:
        gte_op(avsz3);
        gte_stsxy3(prim + 8, prim + 0x14, prim + 0x2C);
        gte_ldv0(*(s32 **)(obj + 0x24));
        gte_mfc2(gte, 7);
        gte = (gte + depthBias) >> 4;
        gte_op(rtps);
        otEntry = (u32 *)(gte * 4 + (s32)ot);
        *(u32 *)prim = *otEntry | 0x0C000000;
        *otEntry = (u32)prim & 0xFFFFFF;
        gte_stsxy(prim + 0x20);
    next:
        count--;
        obj += 0x2C;
        prim = nextPrim;
    }
    return obj;
}

void func_800328AC(void *arg0, s32 arg1) {
    register s32 v0s asm("v0");
    u8 *ret;
    u8 *prim;
    u32 doublesided;
    u8 *spad;
    u32 flagMask;
    u32 codeConst;
    register u8 *ot asm("t7");
    register u8 *obj asm("a2");
    register u8 *prim20 asm("a3");
    s32 *vec0;
    s32 *vec1;
    s32 *vec2;
    s32 gteWord;
    register s32 w8 asm("v1");
    register s32 wC asm("t1");
    register s32 w10 asm("t0");
    register s32 w14 asm("a0");

    ret = arg0;
    asm("" : "=r"(ret) : "0"(ret));
    v0s = D_800A39C8[0];
    prim = (u8 *)gPrimitiveCursor[0];
    doublesided = D_800A2DE0[0];
    flagMask = 0x66000;
    asm("lui %0, 0x1F80" : "=r"(spad));
    asm volatile(".set\tnoreorder\n\t"
                 "blez %1, func_800328AC+0x1C0\n\t"
                 "addiu %0, %2, 0x20\n\t"
                 ".set\treorder"
                 : "=r"(ot)
                 : "r"(arg1), "r"(v0s));
    codeConst = 0x0C000000;
    obj = (u8 *)arg0 + 1;
    prim20 = prim + 0x20;
    do {
        vec0 = *(s32 **)(obj + 0x17);
        vec1 = *(s32 **)(obj + 0x1B);
        vec2 = *(s32 **)(obj + 0x1F);
        gte_ldv3(vec0, vec1, vec2);
        w8 = *(s32 *)(obj + 0x7);
        wC = *(s32 *)(obj + 0xB);
        gte_op(rtpt);
        w10 = *(s32 *)(obj + 0xF);
        w14 = *(s32 *)(obj + 0x13);
        *(s32 *)(prim20 - 0x14) = w8;
        *(s32 *)(prim20 - 0x8) = wC;
        *(s32 *)(prim20 + 0x4) = w10;
        *(s32 *)(prim20 + 0x10) = w14;
        gte_cfc2(gteWord, 31);
        v0s = gteWord & flagMask;
        if (v0s != 0) {
            goto incr;
        }
        gte_op(nclip);
        w8 = *(s32 *)(obj + 0x3);
        asm volatile("nop");
        wC = w8 & 0xFF;
        w8 >>= 8;
        w10 = w8 & 0xFF;
        w8 >>= 8;
        w14 = w8 & 0xFF;
        v0s = wC << 2;
        v0s = v0s + (s32)spad;
        wC = *(u32 *)v0s;
        v0s = w10 << 2;
        v0s = v0s + (s32)spad;
        w10 = *(u32 *)v0s;
        v0s = w14 << 2;
        v0s = v0s + (s32)spad;
        w14 = *(u32 *)v0s;
        v0s = (w8 >> 6) & 0x3FC;
        v0s = v0s + (s32)spad;
        w8 = *(u32 *)v0s;
        gte_mfc2_nonop(gteWord, 24);
        if (doublesided != 0) {
            if (gteWord >= 0) {
                goto ok;
            }
            goto incr;
        } else if (gteWord > 0) {
            goto incr;
        }
    ok:
        gte_op(avsz3);
        v0s = 0x3C000000;
        v0s = wC | v0s;
        *(u32 *)(prim20 + 0x8) = w14;
        *(u32 *)(prim20 - 0x4) = w8;
        *(u32 *)(prim20 - 0x1C) = v0s;
        *(u32 *)(prim20 - 0x10) = w10;
        gte_stsxy3(prim + 0x8, prim + 0x14, prim + 0x2C);
        vec0 = *(s32 **)(obj + 0x23);
        gte_ldv0(vec0);
        gte_mfc2_nonop(gteWord, 7);
        v0s = *(s8 *)obj;
        asm volatile("nop");
        gteWord = gteWord + v0s * 4;
        gte_op(rtps);
        w14 = gteWord >> 4;
        w14 = w14 << 2;
        w14 = w14 + (s32)ot;
        v0s = *(u32 *)w14;
        w8 = 0xFFFFFF;
        w8 = (u32)prim & w8;
        v0s = v0s | codeConst;
        *(u32 *)prim = v0s;
        *(u32 *)w14 = w8;
        gte_stsxy(prim20);
        prim20 += 0x34;
        prim += 0x34;
    incr:
        arg1--;
        obj += 0x2C;
        ret += 0x2C;
    } while (arg1 > 0);
    gPrimitiveCursor[0] = (u32)prim;
    asm volatile("addu $2, %0, $0" : : "r"(ret));
}

s32 func_80032A90(u8 *arg0) {
    u8 *entry;
    s32 i;
    s16 result;
    s32 pad[2];

    (void)&pad;
    if (D_800A2CF8[0] == 2) {
        result = 1;
        goto done;
    }
    entry = arg0 + 0x54;
    i = 0;
    do {
        if (*(s16 *)(entry + 4) < 0x9B) {
            result = 1;
            goto done;
        }
        i = i + 1;
        entry = entry + 0x14;
    } while (i < 4);
    result = 0;
done:
    return result;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80032AE4);

void func_80032D94(s8 *object) {
    if ((u8)object[0x12] == 4) {
        if (object[2] == 3)
            object[0] = 2;
        else
            object[0] = 1;
    } else {
        if (object[2] == 3)
            object[0] = 3;
        else
            object[0] = 0;
    }
}

extern u32 D_800B022C[];
extern s16 D_800AFE2C[];
extern s32 D_800A2F38NM asm("D_800A2F38.NON_MATCHING");

void func_80032DEC(u8 *arg0, s32 arg1) {
    register s32 w4 asm("v1");
    s32 w8;
    register s32 wC asm("v0");
    register s32 n0 asm("v1");
    register s32 n1 asm("a0");
    register s32 old asm("a0");
    register s32 tmpa1 asm("a1");
    register s32 sh asm("v1");
    s32 base;
    u8 *obj;
    register u8 *prim18 asm("s1");
    u8 *prim;
    register s32 otz asm("s3");
    s32 count;
    u32 *objCursor;
    s32 entryCount;
    s16 *zCursor;
    register u8 *otBase40;
    register s32 shifted asm("v0");
    register s32 aligned asm("v0");
    s32 mask;
    s32 diff;
    register s32 guard asm("a2");
    s32 oldEnd;
    s32 *normal;
    s32 w10;
    s32 w14;

    obj = arg0;
    old = D_800A2F38NM;
    count = arg1;
    guard = count;
    count = count - 1;
    prim = (u8 *)gPrimitiveCursor[0];
    tmpa1 = (s32)D_800A39C8[0];
    otBase40 = (u8 *)tmpa1 + 0x40;
    base = (s32)D_800B022C;
    sh = old * 4;
    objCursor = (u32 *)(sh + base);
    sh = old * 2;
    base = (s32)D_800AFE2C;
    zCursor = (s16 *)(sh + base);
    entryCount = old;
    if (guard > 0) {
        prim18 = prim + 0x18;
        do {
            gte_ldv3(*(s32 **)(obj + 0x18), *(s32 **)(obj + 0x1C),
                     *(s32 **)(obj + 0x20));
            w4 = *(s32 *)(obj + 0x4);
            w8 = *(s32 *)(obj + 0x8);
            gte_op(rtpt);
            wC = *(s32 *)(obj + 0xC);
            w10 = *(s32 *)(obj + 0x10);
            w14 = *(s32 *)(obj + 0x14);
            *(s32 *)(prim18 - 0xC) = w8;
            *(s32 *)(prim18 - 0x14) = w4;
            *(s32 *)(prim18 - 4) = wC;
            gte_stsxy3(prim + 8, prim + 0x10, prim + 0x20);
            normal = *(s32 **)(obj + 0x24);
            n0 = normal[0];
            n1 = normal[1];
            gte_op(avsz3);
            *(s32 *)(prim18 + 4) = w10;
            *(s32 *)(prim18 + 0xC) = w14;
            gte_mfc2_nonop(otz, 7);
            gte_mtc2(n0, 0);
            gte_mtc2(n1, 1);
            if (otz < 0x9B) {
                gte_op(rtps);
                if (func_800337EC() != 0 && entryCount < 0x1FF) {
                    otz = otz + *(s8 *)(obj + 1);
                    if (otz >= 0) {
                        entryCount = entryCount + 1;
                        *objCursor = (u32)obj;
                        objCursor = objCursor + 1;
                        shifted = otz << 2;
                        *zCursor = shifted;
                        zCursor = zCursor + 1;
                    }
                    goto nextObj;
                }
            }
            gte_op(rtps);
            tmpa1 = *(s8 *)(obj + 1);
            aligned = (otz >> 2) << 2;
            aligned = aligned + (s32)otBase40;
            mask = 0xFF0000;
            tmpa1 = tmpa1 * 4 + aligned;
            *(u32 *)prim = *(u32 *)tmpa1 | 0x09000000;
            mask = mask | 0xFFFF;
            *(u32 *)tmpa1 = (u32)prim & mask;
            gte_stsxy2(prim18);
            prim18 = prim18 + 0x28;
            prim = prim + 0x28;
        nextObj:
            obj = *(u8 **)(obj + 0x28);
        } while (count-- > 0);
    }
    gPrimitiveCursor[0] = (u32)prim;
    oldEnd = D_800A2F38NM;
    diff = (s32)objCursor - (s32)D_800B022C;
    diff = diff - oldEnd * 4;
    D_800A2F38NM = oldEnd + (diff >> 2);
}

extern s32 D_800A2F08NM[] asm("D_800A2F08.NON_MATCHING");
extern s32 D_800A2CFCNM[] asm("D_800A2CFC.NON_MATCHING");
extern s32 D_800A394CNM asm("D_800A394C.NON_MATCHING");
extern s32 D_800A3A74NM asm("D_800A3A74.NON_MATCHING");
extern s32 D_800A396CNM asm("D_800A396C.NON_MATCHING");

/* Draws the track groups between two list cursors: listA follows each
 * group's +0 link and listB its +4 link, alternating sides. A group is
 * drawn once (+0xE done flag). Past the D_800A2F08 object budget a group
 * draws as five flat quads; otherwise its objects draw as textured
 * triangles, the first +0x13 of them without backface culling. Near
 * triangles that func_800337EC accepts go to the depth-sorted list at
 * D_800B022C/D_800AFE2C instead of the ordering table.
 *
 * word0 and word1 are scratch words reused for colour words, the fourth
 * vertex, and the next object's vertex list. */
void func_80033000(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 *prim;
    u8 *listA;
    u8 *listB;
    s32 count;
    u32 *otCursor;
    s16 *zCursor;
    u8 *group;
    register u8 *obj asm("s0");
    u8 *poly;
    s32 i;
    s32 n;
    s32 otz;
    register s32 word0 asm("s2");
    register s32 word1 asm("s1");
    u8 *vec;
    u8 *verts;
    s32 wC;
    s32 w10;
    s32 w14;
    s32 old;
    s32 diff;
    u32 *ot;
    s32 counter;
    s32 lod;
    s32 mode;

    prim = (u8 *)gPrimitiveCursor[0];
    old = D_800A2F38NM;
    count = 0;
    counter = 0;
    mode = 1;
    listA = arg2;
    listB = *(u8 **)listA;
    otCursor = (u32 *)((u8 *)D_800B022C + old * 4);
    lod = D_800A2F08NM[0];
    ot = (u32 *)D_800A39C8[0] + 0x10;
    zCursor = (s16 *)((u8 *)D_800AFE2C + old * 2);
    if ((listA = listA) != arg1 || (listB = listB) != arg0) {
        do {
            if (counter & 1) {
                if (listA == arg1) {
                    listB = *(u8 **)(listB + 4);
                    group = listB;
                } else {
                    listA = *(u8 **)listA;
                    group = listA;
                }
            } else {
                if (listB != arg0) {
                    listB = *(u8 **)(listB + 4);
                    group = listB;
                } else {
                    listA = *(u8 **)listA;
                    group = listA;
                }
            }
            counter = counter + 1;
            if (*(u16 *)(group + 0xE) != 0) {
                /* Already drawn. */
            } else if (lod < count) {
                for (i = 0; i < 5; i++) {
                    if (mode) {
                        gte_ldv3(((u8 **)(*(u8 **)group + 0x78))[i],
                                 ((u8 **)(*(u8 **)(*(u8 **)(group + 4) + 4) +
                                          0x78))[i],
                                 ((u8 **)(*(u8 **)(*(u8 **)(group + 4) + 4) +
                                          0x78))[i + 1]);
                    } else {
                        gte_ldv3(((u8 **)(group + 0x78))[i],
                                 ((u8 **)(*(u8 **)(group + 4) + 0x78))[i],
                                 ((u8 **)(*(u8 **)(group + 4) + 0x78))[i + 1]);
                    }
                    poly = prim;
                    gte_rtpt();
                    if (i == 2) {
                        *(s32 *)(prim + 4) = D_800A394CNM;
                    } else if (i & 1) {
                        *(s32 *)(prim + 4) = D_800A3A74NM;
                    } else {
                        *(s32 *)(prim + 4) = D_800A396CNM;
                    }
                    SetPolyF4(poly);
                    gte_cfc2_nonop(otz, 31);
                    gte_stsxy3(poly + 8, poly + 0xC, poly + 0x14);
                    if (otz & 0x6000) {
                        continue;
                    }
                    gte_avsz3();
                    if (mode) {
                        vec = *(u8 **)(*(u8 **)group + (i << 2) + 0x7C);
                    } else {
                        vec = ((u8 **)(group + 0x78))[i + 1];
                    }
                    word0 = *(s32 *)vec;
                    word1 = *(s32 *)(vec + 4);
                    gte_mfc2_nonop(otz, 7);
                    gte_mtc2(word0, 0);
                    gte_mtc2(word1, 1);
                    if (otz < 0x9B) {
                        continue;
                    }
                    gte_op(rtps);
                    if (otz >= 0xF3D) {
                        otz = 0xF3C;
                    }
                    *(u32 *)prim = ot[otz >> 2] | 0x05000000;
                    ot[otz >> 2] = (u32)prim & 0xFFFFFF;
                    gte_stsxy(poly + 0x10);
                    prim = prim + 0x28;
                }
                mode = 0;
                *(u16 *)(group + 0xE) = 1;
            } else {
                n = *(u8 *)(group + 0x13);
                obj = *(u8 **)(group + 0x20);
                count = count + n;
                while (n-- > 0) {
                    gte_ldv3(*(u8 **)(obj + 0x18), *(u8 **)(obj + 0x1C),
                             *(u8 **)(obj + 0x20));
                    word0 = *(s32 *)(obj + 4);
                    word1 = *(s32 *)(obj + 8);
                    gte_op(rtpt);
                    wC = *(s32 *)(obj + 0xC);
                    w10 = *(s32 *)(obj + 0x10);
                    w14 = *(s32 *)(obj + 0x14);
                    *(s32 *)(prim + 0x14) = wC;
                    *(s32 *)(prim + 4) = word0;
                    *(s32 *)(prim + 0xC) = word1;
                    gte_stsxy3(prim + 8, prim + 0x10, prim + 0x20);
                    vec = *(u8 **)(obj + 0x24);
                    word0 = *(s32 *)vec;
                    word1 = *(s32 *)(vec + 4);
                    gte_op(avsz3);
                    *(s32 *)(prim + 0x1C) = w10;
                    *(s32 *)(prim + 0x24) = w14;
                    gte_mfc2_nonop(otz, 7);
                    gte_mtc2(word0, 0);
                    gte_mtc2(word1, 1);
                    if (otz < 0x9B) {
                        gte_op(rtps);
                        if (func_800337EC() != 0) {
                            otz = otz + *(s8 *)(obj + 1) * 2;
                            if (otz >= 0) {
                                *otCursor++ = (u32)obj;
                                *zCursor++ = otz << 2;
                            }
                            goto next1;
                        }
                    }
                    gte_op(rtps);
                    otz = (otz >> 2) + *(s8 *)(obj + 1);
                    if (otz >= 0x3B7) {
                        otz = 0x3B6;
                    }
                    *(u32 *)prim = ot[otz] | 0x09000000;
                    ot[otz] = (u32)prim & 0xFFFFFF;
                    gte_stsxy(prim + 0x18);
                    prim = prim + 0x28;
                next1:
                    obj = *(u8 **)(obj + 0x28);
                }
                /* n now holds the backface-cull mode. */
                n = D_800A2DE0[0];
                word0 = (s32)(obj + 0x18);
                while (obj != 0) {
                    count++;
                    verts = (u8 *)word0;
                    gte_ldv3(*(u8 **)verts, *(u8 **)(verts + 4),
                             *(u8 **)(verts + 8));
                    word0 = *(s32 *)(obj + 4);
                    word1 = *(s32 *)(obj + 8);
                    gte_op(rtpt);
                    wC = *(s32 *)(obj + 0xC);
                    w10 = *(s32 *)(obj + 0x10);
                    w14 = *(s32 *)(obj + 0x14);
                    *(s32 *)(prim + 4) = word0;
                    *(s32 *)(prim + 0xC) = word1;
                    *(s32 *)(prim + 0x14) = wC;
                    gte_cfc2_nonop(otz, 31);
                    gte_stsxy3(prim + 8, prim + 0x10, prim + 0x20);
                    if (otz & 0x6000) {
                        goto skip;
                    }
                    gte_op(nclip);
                    vec = *(u8 **)(verts + 0xC);
                    word0 = *(s32 *)vec;
                    word1 = *(s32 *)(vec + 4);
                    *(s32 *)(prim + 0x1C) = w10;
                    *(s32 *)(prim + 0x24) = w14;
                    gte_mfc2_nonop(otz, 24);
                    gte_mtc2(word0, 0);
                    gte_mtc2(word1, 1);
                    if (n != 0) {
                        if (otz < 0) {
                            goto skip;
                        }
                    } else if (otz > 0) {
                        goto skip;
                    }
                    goto draw;
                skip:
                    word1 = *(s32 *)(obj + 0x28);
                    word0 = word1 + 0x18;
                    goto next2;
                draw:
                    gte_op(avsz3);
                    word1 = *(s32 *)(obj + 0x28);
                    word0 = word1 + 0x18;
                    gte_mfc2(otz, 7);
                    if (otz < 0x9B) {
                        gte_op(rtps);
                        if (func_800337EC() != 0) {
                            otz = otz + *(s8 *)(obj + 1);
                            if (otz >= 0) {
                                *otCursor++ = (u32)obj;
                                *zCursor++ = otz << 2;
                            }
                            goto next2;
                        }
                    }
                    gte_op(rtps);
                    otz = (otz >> 2) + *(s8 *)(obj + 1);
                    if (otz < 0x4B1) {
                        if (otz >= 0x3B7) {
                            otz = 0x3B6;
                        }
                        *(u32 *)prim = ot[otz] | 0x09000000;
                        ot[otz] = (u32)prim & 0xFFFFFF;
                        gte_stsxy(prim + 0x18);
                        prim = prim + 0x28;
                    }
                next2:
                    obj = (u8 *)word1;
                }
                *(u16 *)(group + 0xE) = 1;
            }
        } while ((listA = listA) != arg1 || (listB = listB) != arg0);
    }
    diff = (s32)otCursor - (s32)D_800B022C;
    D_800A2CFCNM[0] = count;
    gPrimitiveCursor[0] = (u32)prim;
    D_800A2F38NM = D_800A2F38NM + ((diff - D_800A2F38NM * 4) >> 2);
}

/*
 * Handwritten GTE module: func_80033704 through func_8003382C.
 *
 * These seven functions came from an assembly source file, not C. Don't
 * try to rewrite them as plain C or strip their register pins and asm.
 * The retail code has three shapes no C compiler emits:
 *
 * - func_80033780 has no delay slot of its own. Its `jr ra` uses the
 *   first instruction of func_80033788.
 * - func_8003382C branches into the middle of func_80033704
 *   (`bgez a2, func_80033704+0x20`).
 * - func_800337EC has an `mfc2` in a branch delay slot. gcc 2.7.2 never
 *   puts an asm insn in a delay slot, and this is the only such site in
 *   the EXE.
 *
 * func_80033788, func_8003379C and MathMultiplyFixed16 sit between
 * handwritten functions, so they belong to the same object file.
 * func_800338A4 onwards shows none of these shapes and is plain C.
 */
void func_80033704(s16 *out) {
    register s32 v1 asm("v1");
    register s32 a2 asm("a2");
    register s32 test asm("v0");
    s32 a3;
    s32 a1;
    s32 neg;

    asm volatile("mfc2 %0, $9" : "=r"(v1));
    asm volatile("mfc2 %0, $10" : "=r"(a3));
    asm volatile("mfc2 %0, $11" : "=r"(a2));
    out[0] = v1;
    out[1] = a3;
    out[2] = a2;
    if (a2 < 0) {
        asm("");
        a2 = 0;
    }
    asm(".L80033724:");
    a1 = 4;
    if (a2 >= v1) {
        asm("subu %0, $0, %1" : "=r"(neg) : "r"(v1));
        a1 = (a2 < neg) << 1;
    }
    if (a2 < a3) {
        a1 |= 1;
    } else if (a2 < -a3) {
        a1 |= 8;
    }
    if (a2 < 0x1F4) {
        a1 |= 0x100;
        test = a2 < 5;
        if (test) {
            a1 |= 0x1F;
        }
    }
    out[3] = a1;
}

void func_80033780(void *arg0) {
    asm volatile("swc2 $14, 0x8(%0)\n\t.set\tnoreorder" : : "r"(arg0));
}

void func_80033788(u8 *arg0) {
    register u32 depth asm("$6");

    /* Retail reads GTE IR3 (SZ average) and stores SXY2 for one vertex. */
    asm("mfc2 %0, $11" : "=r"(depth));
    asm("swc2 $14, 0x14($a0)");
    depth >>= 2;
    *(u16 *)(arg0 + 6) = depth;
}

void func_8003379C(u8 *arg0, u8 *arg1, u8 *arg2) {
    register u32 depthA asm("$3");
    register u32 depthB asm("$2");

    /* Retail stores SXY0/1/2 and SZ1/2/3 >> 2 for three vertices after
     * a RotTransPers3; the depth registers rotate v1/v0/v1. */
    asm volatile("mfc2 %0, $17" : "=r"(depthA));
    asm("swc2 $12, 0x14($a0)");
    depthA >>= 2;
    *(u16 *)(arg0 + 6) = depthA;

    asm volatile("mfc2 %0, $18" : "=r"(depthB));
    asm("swc2 $13, 0x14($a1)");
    depthB >>= 2;
    *(u16 *)(arg1 + 6) = depthB;

    asm volatile("mfc2 %0, $19" : "=r"(depthA));
    asm("swc2 $14, 0x14($a2)");
    depthA >>= 2;
    *(u16 *)(arg2 + 6) = depthA;
}

s32 MathMultiplyFixed16(s32 arg0, s32 arg1) {
    u32 lo;
    u32 hi;

    asm volatile("mult\t%0,%1" : : "r"(arg0), "r"(arg1) : "hi", "lo");
    asm volatile("mflo\t%0" : "=r"(lo) : : "lo");
    asm volatile("mfhi\t%0" : "=r"(hi) : : "hi");
    return (lo >> 16) | (hi << 16);
}

s32 func_800337EC(void) {
    s32 sz0;
    s32 sz1;
    s32 test1;
    s32 test2;
    register s32 sz2 asm("v1");
    register s32 sz3 asm("a0");
    register s32 test3 asm("v0");

    asm volatile("mfc2 %0, $16" : "=r"(sz0));
    asm volatile("mfc2 %0, $17" : "=r"(sz1));
    test1 = sz0 < 0x12C;
    test2 = sz1 < 0x12C;
    if (test1) {
        goto out;
    }
    asm volatile(".set\tnoreorder\n\t"
                 "bne %0, $0, func_800337EC+0x38\n\t"
                 "mfc2 %1, $18\n\t"
                 ".set\treorder"
                 : "=r"(sz2)
                 : "r"(test2));
    asm volatile("mfc2 %0, $19" : "=r"(sz3));
    test3 = sz2 < 0x12C;
    if (test3) {
        goto out;
    }
    asm volatile(".set\tnoreorder\n\t"
                 "slti $2, %0, 0x12C\n\t"
                 "j $31\n\t"
                 "nop\n\t"
                 ".set\treorder"
                 :
                 : "r"(sz3));
out:
    return 1;
}

void func_8003382C(s16 *out) {
    register s32 v1 asm("v1");
    register s32 a2 asm("a2");
    register s32 test asm("v0");
    s32 a3;
    s32 a1;
    s32 neg;

    asm volatile("mfc2 %0, $9\n\t"
                 "mfc2 %1, $10\n\t"
                 "mfc2 %2, $11\n\tnop\n\t"
                 "bgez %2, func_80033704+0x20"
                 : "=r"(v1), "=r"(a3), "=r"(a2));
    asm("addu %0, $0, $0" : "=r"(a2));
    a1 = 4;
    if (a2 >= v1) {
        asm("subu %0, $0, %1" : "=r"(neg) : "r"(v1));
        a1 = (a2 < neg) << 1;
    }
    if (a2 < a3) {
        a1 |= 1;
    } else if (a2 < -a3) {
        a1 |= 8;
    }
    if (a2 < 0x1F4) {
        a1 |= 0x100;
        test = a2 < 5;
        if (test) {
            a1 |= 0x10;
        }
    }
    out[3] = a1;
}

/* End of the handwritten GTE module. */

void func_800338A4(s32 *dst, s32 *src) {
    s32 a, b, c, d, e, f;
    a = src[0];
    b = src[1];
    c = src[2];
    d = src[3];
    e = src[4];
    f = src[5];
    dst[0] = a;
    dst[1] = b;
    dst[3] = c;
    dst[5] = d;
    dst[7] = e;
    dst[9] = f;
}

s32 func_800338D8(u16 *object) {
    u32 flags;
    flags = object[3];
    flags &= object[13];
    flags &= object[23];
    flags &= object[33];
    return (flags & 0x7EFF) == 0;
}

#define SUBDIVISION_STORE_DEPTH3(a, b, c)                                      \
    asm volatile("swc2 $17, 0(%0)\n\tswc2 $18, 0(%1)\n\tswc2 $19, 0(%2)"       \
                 :                                                             \
                 : "r"(a), "r"(b), "r"(c)                                      \
                 : "memory")

typedef struct SubdivisionVertex {
    s16 x, y, z;
    u8 u, v;
    s32 screen;
    s16 depth, pad;
} SubdivisionVertex;
extern u32 gSubdivisionTemplate0[] asm("gScratchpad+0");
extern u32 gSubdivisionTemplate1[] asm("gScratchpad+4");
extern u32 gSubdivisionTemplate2[] asm("gScratchpad+8");
extern u32 gSubdivisionTemplate3[] asm("gScratchpad+12");
extern u32 gSubdivisionTemplate4[] asm("gScratchpad+16");
extern u32 gSubdivisionTemplate5[] asm("gScratchpad+20");
extern u32 *gSubdivisionOt[] asm("gScratchpad+24");

u8 *GraphicsSubdivideTexturedQuad(SubdivisionVertex *vertices, u8 *primCursor,
                                  s32 recursionLevel) {
    register SubdivisionVertex *grid asm("s0");
    register u8 *prim asm("t5");
    register s32 level asm("s2");
    s32 limit;
    register SubdivisionVertex *row1 asm("t3");
    register SubdivisionVertex *row2 asm("t2");
    register SubdivisionVertex *center asm("t1");
    register SubdivisionVertex *right asm("t0");
    register s32 work0 asm("v0");
    register s32 work1 asm("v1");
    register s32 work2 asm("a0");
    register s32 work3 asm("a1");
    register s32 work4 asm("a2");
    register s32 work5 asm("a3");
    register s32 work6 asm("t0");
    register s32 work7 asm("t1");
    register s32 w0 asm("v0");
    register s32 w1 asm("v1");
    register s32 w2 asm("a3");
    register s32 w3 asm("t0");
    register s32 w4 asm("t1");
    register s32 w5 asm("t2");
    register s32 w6 asm("t3");
    register s32 w7 asm("t4");
    register u32 word0 asm("v1");
    register u32 word1 asm("a0");
    register u32 word2 asm("a1");
    register u32 word3 asm("a2");
    register u32 word4 asm("a3");
    register u32 word5 asm("t0");
    register u32 *ot asm("t1");
    register u32 mask asm("t2");
    register u16 uv asm("v0");
    register SubdivisionVertex *mid asm("a1");
    register u8 *packet asm("v0");
    grid = vertices;
    asm("" : : "r"(grid) : "t5");
    prim = primCursor;
    level = recursionLevel;
    asm volatile("" : : "r"(grid), "r"(prim), "r"(level));
    /* Reuse the eight scratch values in the GTE routine's order. The empty
   * constraints keep the UV arithmetic and corner loads in that order. */
    work0 = grid[0].x;
    work1 = grid[2].x;
    work3 = grid[2].y;
    work5 = grid[2].u;
    work4 = grid[0].v;
    work6 = grid[2].v;
    work7 = grid[6].x;
    work0 += work1;
    work1 = grid[0].y;
    work2 = (u32)work0 >> 31;
    work0 += work2;
    work2 = grid[0].z;
    work4 += work6;
    asm volatile("" : "=r"(work4) : "0"(work4) : "memory");
    work4 >>= 1;
    grid[1].v = work4;
    work4 = grid[2].v;
    work6 = grid[6].v;
    work0 >>= 1;
    grid[1].x = work0;
    work1 += work3;
    work3 = grid[2].z;
    work0 = (u32)work1 >> 31;
    work1 += work0;
    work1 >>= 1;
    grid[1].y = work1;
    work1 = grid[0].u;
    work2 += work3;
    work3 = grid[2].x;
    work0 = (u32)work2 >> 31;
    work2 += work0;
    work0 = grid[2].y;
    work2 >>= 1;
    work1 += work5;
    asm volatile("" : "=r"(work1) : "0"(work1) : "memory");
    grid[1].z = work2;
    work2 = grid[6].y;
    work5 = grid[6].u;
    row1 = grid + 6;
    row2 = grid + 8;
    work1 >>= 1;
    grid[1].u = work1;
    /* Interpolate the center of the diagonal from vertices 2 and 6. */
    work3 += work7;
    work0 += work2;
    work2 = grid[2].z;
    work1 = (u32)work3 >> 31;
    work3 += work1;
    work3 >>= 1;
    grid[4].x = work3;
    work3 = grid[6].z;
    work1 = (u32)work0 >> 31;
    work0 += work1;
    work1 = grid[2].u;
    work7 = grid[8].x;
    asm volatile("" : : "r"(work7) : "memory");
    work4 += work6;
    work4 >>= 1;
    work0 >>= 1;
    grid[4].y = work0;
    work2 += work3;
    work3 = grid[2].x;
    work0 = (u32)work2 >> 31;
    work2 += work0;
    work2 >>= 1;
    grid[4].z = work2;
    asm volatile("" : : "m"(grid[4].z) : "memory");
    work0 = grid[2].y;
    work2 = grid[8].y;
    right = grid + 5;
    work1 += work5;
    work1 >>= 1;
    grid[4].u = work1;
    grid[4].v = work4;
    /* Interpolate the right edge from vertices 2 and 8. */
    work3 += work7;
    work1 = (u32)work3 >> 31;
    work3 += work1;
    work3 >>= 1;
    work0 += work2;
    work1 = (u32)work0 >> 31;
    work0 += work1;
    work0 >>= 1;
    grid[5].x = work3;
    grid[5].y = work0;
    asm volatile("" : : "m"(grid[5].y) : "memory");
    work0 = grid[2].z;
    asm volatile("" : : "r"(work0) : "memory");
    work1 = grid[8].z;
    asm volatile("" : : "r"(work1) : "memory");
    work2 = grid[2].u;
    asm volatile("" : : "r"(work2) : "memory");
    work4 = grid[8].u;
    asm volatile("" : : "r"(work4) : "memory");
    work3 = grid[2].v;
    asm volatile("" : : "r"(work3) : "memory");
    work5 = grid[8].v;
    asm volatile("" : : "r"(work5) : "memory");
    center = grid + 4;
    grid[5].z = (work0 + work1) / 2;
    grid[5].u = (work2 + work4) >> 1;
    grid[5].v = (work3 + work5) >> 1;
    limit = (0x8C - (level << 6)) * 4;
    gte_ldv3(&grid[0], &grid[1], &grid[2]);
    gte_rtpt();
    grid[3].x = (grid[0].x + grid[6].x) / 2;
    grid[3].y = (grid[0].y + grid[6].y) / 2;
    grid[3].z = (grid[0].z + grid[6].z) / 2;
    grid[3].u = (grid[0].u + grid[6].u) >> 1;
    grid[3].v = (grid[0].v + grid[6].v) >> 1;
    asm volatile("addiu %0, %1, 0x30"
                 : "=r"(mid)
                 : "r"(grid), "r"(&grid[0].screen), "r"(&grid[1].screen),
                   "r"(&grid[2].screen));
    gte_stsxy3(&grid[0].screen, &grid[1].screen, &grid[2].screen);
    SUBDIVISION_STORE_DEPTH3(&grid[0].depth, &grid[1].depth, &grid[2].depth);
    gte_ldv3(mid, center, right);
    gte_rtpt();
    grid[7].x = (grid[6].x + grid[8].x) / 2;
    grid[7].y = (grid[6].y + grid[8].y) / 2;
    grid[7].z = (grid[6].z + grid[8].z) / 2;
    grid[7].u = (grid[6].u + grid[8].u) >> 1;
    grid[7].v = (grid[6].v + grid[8].v) >> 1;
    asm volatile("addiu %0, %1, 0x70"
                 : "=r"(mid)
                 : "r"(grid), "r"(&grid[3].screen), "r"(&grid[4].screen),
                   "r"(&grid[5].screen));
    gte_stsxy3(&grid[3].screen, &grid[4].screen, &grid[5].screen);
    SUBDIVISION_STORE_DEPTH3(&grid[3].depth, &grid[4].depth, &grid[5].depth);
    gte_ldv3(row1, mid, row2);
    gte_rtpt();
    gte_stsxy3(&grid[6].screen, &grid[7].screen, &grid[8].screen);
    SUBDIVISION_STORE_DEPTH3(&grid[6].depth, &grid[7].depth, &grid[8].depth);
    if ((grid[0].depth < limit || grid[1].depth < limit ||
         grid[3].depth < limit || grid[4].depth < limit) &&
        level < 2) {
        w0 = ((s32 *)&grid[0])[0];
        w1 = ((s32 *)&grid[0])[1];
        w2 = ((s32 *)&grid[1])[0];
        w3 = ((s32 *)&grid[1])[1];
        w4 = ((s32 *)&grid[3])[0];
        w5 = ((s32 *)&grid[3])[1];
        w6 = ((s32 *)&grid[4])[0];
        w7 = ((s32 *)&grid[4])[1];
        ((s32 *)&grid[9])[0] = w0;
        ((s32 *)&grid[9])[1] = w1;
        ((s32 *)&grid[11])[0] = w2;
        ((s32 *)&grid[11])[1] = w3;
        ((s32 *)&grid[15])[0] = w4;
        ((s32 *)&grid[15])[1] = w5;
        ((s32 *)&grid[17])[0] = w6;
        ((s32 *)&grid[17])[1] = w7;
        prim = GraphicsSubdivideTexturedQuad(grid + 9, prim, level + 1);
    } else {
        word0 = gSubdivisionTemplate0[0];
        *(s32 *)(prim + 8) = grid[0].screen;
        *(s32 *)(prim + 16) = grid[1].screen;
        *(s32 *)(prim + 24) = grid[3].screen;
        *(s32 *)(prim + 32) = grid[4].screen;
        uv = *(u16 *)&grid[0].u;
        word1 = gSubdivisionTemplate1[0];
        asm volatile("sh %0, gScratchpad+8" : : "r"(uv) : "memory");
        uv = *(u16 *)&grid[1].u;
        word2 = gSubdivisionTemplate2[0];
        asm volatile("sh %0, gScratchpad+12" : : "r"(uv) : "memory");
        uv = *(u16 *)&grid[3].u;
        word3 = gSubdivisionTemplate3[0];
        asm volatile("sh %0, gScratchpad+16" : : "r"(uv) : "memory");
        uv = *(u16 *)&grid[4].u;
        word4 = gSubdivisionTemplate4[0];
        asm volatile("sh %0, gScratchpad+20" : : "r"(uv) : "memory");
        word5 = gSubdivisionTemplate5[0];
        packet = prim;
        *(s32 *)packet = word0;
        ot = gSubdivisionOt[0];
        mask = 0xFFFFFF;
        *(s32 *)(packet + 4) = word1;
        *(s32 *)(packet + 12) = word2;
        *(s32 *)(packet + 20) = word3;
        *(s32 *)(packet + 28) = word4;
        *(s32 *)(packet + 36) = word5;
        prim += 0x28;
        *(u32 *)packet = *ot | 0x09000000;
        *ot = (u32)packet & mask;
    }
    if ((grid[1].depth < limit || grid[2].depth < limit ||
         grid[4].depth < limit || grid[5].depth < limit) &&
        level < 2) {
        w0 = ((s32 *)&grid[1])[0];
        w1 = ((s32 *)&grid[1])[1];
        w2 = ((s32 *)&grid[2])[0];
        w3 = ((s32 *)&grid[2])[1];
        w4 = ((s32 *)&grid[4])[0];
        w5 = ((s32 *)&grid[4])[1];
        w6 = ((s32 *)&grid[5])[0];
        w7 = ((s32 *)&grid[5])[1];
        ((s32 *)&grid[9])[0] = w0;
        ((s32 *)&grid[9])[1] = w1;
        ((s32 *)&grid[11])[0] = w2;
        ((s32 *)&grid[11])[1] = w3;
        ((s32 *)&grid[15])[0] = w4;
        ((s32 *)&grid[15])[1] = w5;
        ((s32 *)&grid[17])[0] = w6;
        ((s32 *)&grid[17])[1] = w7;
        prim = GraphicsSubdivideTexturedQuad(grid + 9, prim, level + 1);
    } else {
        word0 = gSubdivisionTemplate0[0];
        *(s32 *)(prim + 8) = grid[1].screen;
        *(s32 *)(prim + 16) = grid[2].screen;
        *(s32 *)(prim + 24) = grid[4].screen;
        *(s32 *)(prim + 32) = grid[5].screen;
        uv = *(u16 *)&grid[1].u;
        word1 = gSubdivisionTemplate1[0];
        asm volatile("sh %0, gScratchpad+8" : : "r"(uv) : "memory");
        uv = *(u16 *)&grid[2].u;
        word2 = gSubdivisionTemplate2[0];
        asm volatile("sh %0, gScratchpad+12" : : "r"(uv) : "memory");
        uv = *(u16 *)&grid[4].u;
        word3 = gSubdivisionTemplate3[0];
        asm volatile("sh %0, gScratchpad+16" : : "r"(uv) : "memory");
        uv = *(u16 *)&grid[5].u;
        word4 = gSubdivisionTemplate4[0];
        asm volatile("sh %0, gScratchpad+20" : : "r"(uv) : "memory");
        word5 = gSubdivisionTemplate5[0];
        packet = prim;
        *(s32 *)packet = word0;
        ot = gSubdivisionOt[0];
        mask = 0xFFFFFF;
        *(s32 *)(packet + 4) = word1;
        *(s32 *)(packet + 12) = word2;
        *(s32 *)(packet + 20) = word3;
        *(s32 *)(packet + 28) = word4;
        *(s32 *)(packet + 36) = word5;
        prim += 0x28;
        *(u32 *)packet = *ot | 0x09000000;
        *ot = (u32)packet & mask;
    }
    if ((grid[3].depth < limit || grid[4].depth < limit ||
         grid[6].depth < limit || grid[7].depth < limit) &&
        level < 2) {
        w0 = ((s32 *)&grid[3])[0];
        w1 = ((s32 *)&grid[3])[1];
        w2 = ((s32 *)&grid[4])[0];
        w3 = ((s32 *)&grid[4])[1];
        w4 = ((s32 *)&grid[6])[0];
        w5 = ((s32 *)&grid[6])[1];
        w6 = ((s32 *)&grid[7])[0];
        w7 = ((s32 *)&grid[7])[1];
        ((s32 *)&grid[9])[0] = w0;
        ((s32 *)&grid[9])[1] = w1;
        ((s32 *)&grid[11])[0] = w2;
        ((s32 *)&grid[11])[1] = w3;
        ((s32 *)&grid[15])[0] = w4;
        ((s32 *)&grid[15])[1] = w5;
        ((s32 *)&grid[17])[0] = w6;
        ((s32 *)&grid[17])[1] = w7;
        prim = GraphicsSubdivideTexturedQuad(grid + 9, prim, level + 1);
    } else {
        word0 = gSubdivisionTemplate0[0];
        *(s32 *)(prim + 8) = grid[3].screen;
        *(s32 *)(prim + 16) = grid[4].screen;
        *(s32 *)(prim + 24) = grid[6].screen;
        *(s32 *)(prim + 32) = grid[7].screen;
        uv = *(u16 *)&grid[3].u;
        word1 = gSubdivisionTemplate1[0];
        asm volatile("sh %0, gScratchpad+8" : : "r"(uv) : "memory");
        uv = *(u16 *)&grid[4].u;
        word2 = gSubdivisionTemplate2[0];
        asm volatile("sh %0, gScratchpad+12" : : "r"(uv) : "memory");
        uv = *(u16 *)&grid[6].u;
        word3 = gSubdivisionTemplate3[0];
        asm volatile("sh %0, gScratchpad+16" : : "r"(uv) : "memory");
        uv = *(u16 *)&grid[7].u;
        word4 = gSubdivisionTemplate4[0];
        asm volatile("sh %0, gScratchpad+20" : : "r"(uv) : "memory");
        word5 = gSubdivisionTemplate5[0];
        packet = prim;
        *(s32 *)packet = word0;
        ot = gSubdivisionOt[0];
        mask = 0xFFFFFF;
        *(s32 *)(packet + 4) = word1;
        *(s32 *)(packet + 12) = word2;
        *(s32 *)(packet + 20) = word3;
        *(s32 *)(packet + 28) = word4;
        *(s32 *)(packet + 36) = word5;
        prim += 0x28;
        *(u32 *)packet = *ot | 0x09000000;
        *ot = (u32)packet & mask;
    }
    if ((grid[4].depth < limit || grid[5].depth < limit ||
         grid[7].depth < limit || grid[8].depth < limit) &&
        level < 2) {
        w0 = ((s32 *)&grid[4])[0];
        w1 = ((s32 *)&grid[4])[1];
        w2 = ((s32 *)&grid[5])[0];
        w3 = ((s32 *)&grid[5])[1];
        w4 = ((s32 *)&grid[7])[0];
        w5 = ((s32 *)&grid[7])[1];
        w6 = ((s32 *)&grid[8])[0];
        w7 = ((s32 *)&grid[8])[1];
        ((s32 *)&grid[9])[0] = w0;
        ((s32 *)&grid[9])[1] = w1;
        ((s32 *)&grid[11])[0] = w2;
        ((s32 *)&grid[11])[1] = w3;
        ((s32 *)&grid[15])[0] = w4;
        ((s32 *)&grid[15])[1] = w5;
        ((s32 *)&grid[17])[0] = w6;
        ((s32 *)&grid[17])[1] = w7;
        prim = GraphicsSubdivideTexturedQuad(grid + 9, prim, level + 1);
    } else {
        word0 = gSubdivisionTemplate0[0];
        *(s32 *)(prim + 8) = grid[4].screen;
        *(s32 *)(prim + 16) = grid[5].screen;
        *(s32 *)(prim + 24) = grid[7].screen;
        *(s32 *)(prim + 32) = grid[8].screen;
        uv = *(u16 *)&grid[4].u;
        word1 = gSubdivisionTemplate1[0];
        asm volatile("sh %0, gScratchpad+8" : : "r"(uv) : "memory");
        uv = *(u16 *)&grid[5].u;
        word2 = gSubdivisionTemplate2[0];
        asm volatile("sh %0, gScratchpad+12" : : "r"(uv) : "memory");
        uv = *(u16 *)&grid[7].u;
        word3 = gSubdivisionTemplate3[0];
        asm volatile("sh %0, gScratchpad+16" : : "r"(uv) : "memory");
        uv = *(u16 *)&grid[8].u;
        word4 = gSubdivisionTemplate4[0];
        asm volatile("sh %0, gScratchpad+20" : : "r"(uv) : "memory");
        word5 = gSubdivisionTemplate5[0];
        packet = prim;
        *(s32 *)packet = word0;
        ot = gSubdivisionOt[0];
        mask = 0xFFFFFF;
        *(s32 *)(packet + 4) = word1;
        *(s32 *)(packet + 12) = word2;
        *(s32 *)(packet + 20) = word3;
        *(s32 *)(packet + 28) = word4;
        *(s32 *)(packet + 36) = word5;
        prim += 0x28;
        *(u32 *)packet = *ot | 0x09000000;
        *ot = (u32)packet & mask;
    }
    return prim;
}
extern u32 gScratchpad[];
extern s32 D_800A3640[];
extern u8 D_800A2ED8Abs[] asm("D_800A2ED8.NON_MATCHING");

u32 func_800342D8(u32 *entry, u32 primCursor) {
    u8 *obj;
    register s32 *spad asm("s1");
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
    s32 w5;
    s32 *v18base;
    u8 *p8;
    u16 *quad;
    s32 *v18p;
    s32 *v1Cp;
    s32 *v24p;
    s32 *v20p;
    s32 *vec;
    register s32 flags asm("v0");
    s32 t;
    s32 kind;
    s32 u1;

    obj = *(u8 **)entry;
    asm volatile("lui %0, %%hi(gScratchpad)" : "=r"(spad));
    quad = (u16 *)0x1F80001C;
    asm volatile("addiu %0, %1, 0x18" : "=r"(v18base) : "r"(obj));
    p8 = obj + 8;

    vec = v18base[0];
    gte_ldv0(vec);
    w0 = *(s32 *)(obj + 0);
    w1 = *(s32 *)(obj + 4);
    gte_op(rtps);
    w2 = *(s32 *)(obj + 8);
    w3 = *(s32 *)(obj + 0xC);
    w4 = *(s32 *)(obj + 0x10);
    w5 = *(s32 *)(obj + 0x14);
    vec = v18base[1];
    gte_ldv0(vec);
    func_80033704((s16 *)0x1F80001C);
    gte_op(rtps);
    spad[0] = w0;
    gScratchpad[1] = w1;
    gScratchpad[2] = w2;
    gScratchpad[3] = w3;
    vec = v18base[3];
    gte_ldv0(vec);
    func_80033704((s16 *)0x1F800030);
    gte_op(rtps);
    gScratchpad[4] = w4;
    gScratchpad[5] = w5;
    v18p = *(s32 **)(obj + 0x18);
    vec = v18base[2];
    w0 = v18p[0];
    w4 = v18p[1];
    gte_ldv0(vec);
    func_80033704((s16 *)0x1F800044);
    gte_op(rtps);
    v1Cp = *(s32 **)(obj + 0x1C);
    v24p = *(s32 **)(obj + 0x24);
    w1 = v1Cp[0];
    w5 = v1Cp[1];
    w2 = v24p[0];
    obj = (u8 *)v24p[1];
    func_80033704((s16 *)0x1F800058);

    flags = ((u16 *)gScratchpad)[0x11];
    flags &= ((u16 *)gScratchpad)[0x1B];
    flags &= ((u16 *)gScratchpad)[0x25];
    flags &= ((u16 *)gScratchpad)[0x2F];
    flags &= 0x7EFF;
    if (flags != 0) {
        flags = 0;
    } else {
        flags = 1;
    }
    flags &= 0xFF;
    if (flags == 0) {
        flags = 0;
        *entry = flags;
        return primCursor;
    }

    t = D_800A3640[0];
    if (t < 0) {
        spad[6] = D_800A39C8[0] + 0x40;
    } else {
        spad[6] = D_800A39C8[0] + ((t >> 4) << 2) + 0x40;
    }
    v20p = v18base[2];
    w3 = v20p[0];
    u1 = v20p[1];
    spad = &spad[7];
    spad[0] = w0;
    spad[1] = w4;
    spad[8] = w1;
    spad[9] = w5;
    spad[0x18] = w2;
    spad[0x19] = obj;
    spad[0x20] = w3;
    spad[0x21] = u1;

    w0 = *(u16 *)p8;
    w1 = *(u16 *)(p8 + 4);
    w2 = *(u16 *)(p8 + 8);
    w3 = *(u16 *)(p8 + 0xC);
    quad[3] = w0;
    quad[0x13] = w1;
    quad[0x33] = w2;
    quad[0x43] = w3;

    kind = *(s8 *)(*(u8 **)entry + 2);
    if (kind >= 13) {
        if (kind == 13) {
            *entry = 0;
            return (u32)GraphicsSubdivideTexturedQuad((SubdivisionVertex *)spad,
                                                      (u8 *)primCursor, 2);
        } else {
            *entry = 0;
            return (u32)GraphicsSubdivideTexturedQuad((SubdivisionVertex *)spad,
                                                      (u8 *)primCursor, 1);
        }
    } else {
        if (D_800A2EA4Absolute[0] != 0 || D_800A2ED8Abs[0] != 0) {
            return (u32)GraphicsSubdivideTexturedQuad((SubdivisionVertex *)spad,
                                                      (u8 *)primCursor, 2);
        } else {
            return (u32)GraphicsSubdivideTexturedQuad((SubdivisionVertex *)spad,
                                                      (u8 *)primCursor, 0);
        }
    }
}

extern MATRIX D_800A4568[];
extern MATRIX D_800A4588[];

void func_800345E0(void) {
    s16 *base;
    s16 *row;
    s16 *p16;
    s32 *tp;
    s32 i;
    s32 j;

    gte_ReadRotMatrix(D_800A4568);
    gte_ReadRotMatrix(D_800A4588);
    i = 0;
    base = D_800A4588->m[0];
    tp = (s32 *)&base[10];
    row = base;
    do {
        j = 0;
        p16 = row;
        do {
            *p16 *= 4;
            p16 += 1;
            j += 1;
        } while (j < 3);
        row += 3;
        *tp *= 4;
        tp += 1;
        i += 1;
    } while (i < 3);
}

extern s32 D_800A2F38[];

extern u32 D_800A3570Lui asm("D_800A3570Absolute");
extern u32 gPrimitiveCursorLui asm("gPrimitiveCursorAbsolute");
s32 func_800346D0(s32 threshold) {
    s32 i;
    u32 ret;

    if (D_800A2CF8[0] == 3) {
        return 0;
    }
    PushMatrix();
    SetRotMatrix(D_800A4588);
    SetTransMatrix(D_800A4588);
    for (i = 0; i < D_800A2F38[0]; i++) {
        D_800A3640[0] = D_800AFE2C[i];
        ret = func_800342D8(&D_800B022C[i], gPrimitiveCursor[0]);
        gPrimitiveCursorLui = ret;
        if (threshold <
            (s32)(((ret & 0xFFFFFFF) - (D_800A3570Lui & 0xFFFFFFF)) / 40)) {
            D_800A2F38[0] = i;
        }
    }
    if (D_800A2CF8[0] < 2) {
        SetRotMatrix(D_800A4568);
        SetTransMatrix(D_800A4568);
        func_80034834();
    }
    PopMatrix();
    return D_800A2F38[0];
}

void func_80034834(void) {
    u8 *prim;
    u8 *ot;
    s32 i;
    u8 *obj;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;

    ot = (u8 *)D_800A39C8[0] + 0x80;
    prim = (u8 *)gPrimitiveCursor[0];
    for (i = 0; i < D_800A2F38[0]; i++) {
        obj = (u8 *)D_800B022C[i];
        if (obj != 0 && (*(u8 *)(obj + 0x13) & 0x80) == 0) {
            gte_ldv3(*(u32 **)(obj + 0x18), *(u32 **)(obj + 0x1C),
                     *(u32 **)(obj + 0x20));
            /*
             * t0 to t2 are reused for the normal vector load below: that
             * gives each value two live ranges, so global allocation
             * (not local) picks their registers, as in retail.
             */
            t0 = *(s32 *)(obj + 0x4);
            t1 = *(s32 *)(obj + 0x8);
            gte_op(rtpt);
            t2 = *(s32 *)(obj + 0xC);
            t3 = *(s32 *)(obj + 0x10);
            t4 = *(s32 *)(obj + 0x14);
            *(s32 *)(prim + 0x4) = t0;
            *(s32 *)(prim + 0xC) = t1;
            *(s32 *)(prim + 0x14) = t2;
            gte_stsxy3(prim + 8, prim + 0x10, prim + 0x20);
            t2 = *(s32 *)(obj + 0x24);
            t0 = *(s32 *)(t2 + 0);
            t1 = *(s32 *)(t2 + 4);
            *(s32 *)(prim + 0x1C) = t3;
            *(s32 *)(prim + 0x24) = t4;
            gte_mtc2(t0, 0);
            gte_mtc2(t1, 1);
            gte_rtps();
            GraphicsAddTaggedPrimitive((u32 *)(ot + 0xC0), (u32 *)prim,
                                       0x09000000);
            gte_stsxy(prim + 0x18);
            prim += 0x28;
        }
    }
    gPrimitiveCursor[0] = (u32)prim;
}

#ifdef NON_MATCHING
/*
 * WALL (w9d): this draft is byte-exact except for ONE addressing fact:
 * retail reads D_800A38C0 with `lhu %gp_rel(D_800A38C0)($gp)` here, but
 * TextureLoadTim STORES the same symbol absolute (lui/sw). Declaring
 * D_800A38C0 scalar for the gp read flips TextureLoadTim's store to
 * gp-rel (-4 bytes, whole-EXE shift; the w8b wall). Needs the Makefile
 * defsym alias D_800A38C0Small=D_800A38C0 and an `extern u16
 * D_800A38C0Small;` here -- then this draft should drop in unmodified.
 * Everything else was verified clean by asm-differ: prologue (li s4,
 * 0xA7 / li s3, 0xFD hoisted before the IV init), both FT4 loops (for +
 * (i+1)<<7-1 CSE), and the F4 tail as a do-while with the f4 += 0x18
 * before the test (it lands in the bnez delay slot). cursor = base +
 * car * 0x28 is REQUIRED: spelling the 0xA0 stride as a separate `off`
 * local puts move s5,zero before the li constants and breaks the
 * prologue order.
 */
extern u16 D_800A38C0;
extern u8 *D_800A3850;
extern u8 *D_800A390C;
extern u8 D_800AFBB8[];
extern u8 D_800AFB18[];
extern u8 D_800B1F30[];

void func_80034990(void) {
    u16 color;
    s32 car;
    s32 i;
    u8 *cursor;
    POLY_FT4 *prim;
    POLY_F4 *f4;
    s32 red;
    s32 green;
    s32 blue;

    D_800A3850 = D_800AFBB8;
    color = D_800A38C0;
    for (car = 0; car < 0xC; car += 4) {
        cursor = D_800AFB18 + car * 0x28;
        for (i = 0; i < 2; i++) {
            prim = (POLY_FT4 *)(cursor + i * 0x28);
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            prim->tpage = GetTPage(1, 0, 0x200, 0x100);
            prim->clut = GetClut(0x200, 0x1FF);
            prim->u0 = i << 7;
            prim->v0 = 0xA7;
            prim->u1 = ((i + 1) << 7) - 1;
            prim->v1 = 0xA7;
            prim->u2 = i << 7;
            prim->v2 = 0xFD;
            prim->u3 = ((i + 1) << 7) - 1;
            prim->v3 = 0xFD;
        }
        for (i = 0; i < 2; i++) {
            prim = (POLY_FT4 *)(cursor + 0x50 + i * 0x28);
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            prim->tpage = GetTPage(1, 0, 0x280, 0x100);
            prim->clut = GetClut(0x200, 0x1FF);
            prim->u0 = i << 7;
            prim->v0 = 0xA7;
            prim->u1 = ((i + 1) << 7) - 1;
            prim->v1 = 0xA7;
            prim->u2 = i << 7;
            prim->v2 = 0xFD;
            prim->u3 = ((i + 1) << 7) - 1;
            prim->v3 = 0xFD;
        }
    }
    red = (color & 0x7C00) >> 7;
    green = (color & 0x3E0) >> 2;
    blue = (color & 0x1F) << 3;
    D_800A390C = D_800B1F30;
    i = 0;
    f4 = (POLY_F4 *)(D_800B1F30 - 0x60);
    do {
        SetPolyF4(f4);
        f4->r0 = blue;
        f4->g0 = green;
        f4->b0 = red;
        i++;
        f4 += 0x18;
    } while (i < 8);
}
#endif

extern u16 D_800A38C0Small;
extern u8 *D_800A3850;
extern u8 *D_800A390C;
extern u8 D_800AFBB8[];
extern u8 D_800AFB18[];
extern u8 D_800B1F30[];

void func_80034990(void) {
    u16 color;
    s32 car;
    s32 i;
    u8 *cursor;
    POLY_FT4 *prim;
    POLY_F4 *f4;
    s32 red;
    s32 green;
    s32 blue;

    D_800A3850 = D_800AFBB8;
    color = D_800A38C0Small;
    for (car = 0; car < 0xC; car += 4) {
        cursor = D_800AFB18 + car * 0x28;
        for (i = 0; i < 2; i++) {
            prim = (POLY_FT4 *)(cursor + i * 0x28);
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            prim->tpage = GetTPage(1, 0, 0x200, 0x100);
            prim->clut = GetClut(0x200, 0x1FF);
            prim->u0 = i << 7;
            prim->v0 = 0xA7;
            prim->u1 = ((i + 1) << 7) - 1;
            prim->v1 = 0xA7;
            prim->u2 = i << 7;
            prim->v2 = 0xFD;
            prim->u3 = ((i + 1) << 7) - 1;
            prim->v3 = 0xFD;
        }
        for (i = 0; i < 2; i++) {
            prim = (POLY_FT4 *)(cursor + 0x50 + i * 0x28);
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            prim->tpage = GetTPage(1, 0, 0x280, 0x100);
            prim->clut = GetClut(0x200, 0x1FF);
            prim->u0 = i << 7;
            prim->v0 = 0xA7;
            prim->u1 = ((i + 1) << 7) - 1;
            prim->v1 = 0xA7;
            prim->u2 = i << 7;
            prim->v2 = 0xFD;
            prim->u3 = ((i + 1) << 7) - 1;
            prim->v3 = 0xFD;
        }
    }
    red = (color & 0x7C00) >> 7;
    green = (color & 0x3E0) >> 2;
    blue = (color & 0x1F) << 3;
    D_800A390C = D_800B1F30;
    i = 0;
    f4 = (POLY_F4 *)(D_800B1F30 - 0x60);
    do {
        SetPolyF4(f4 + i);
        f4[i].r0 = blue;
        f4[i].g0 = green;
        f4[i].b0 = red;
        i++;
    } while (i < 8);
}

typedef struct {
    s32 words[10];
} Primitive40;

void func_80034B90(u8 *prim) {
    POLY_FT4 *entry;
    u32 cursor;

    cursor = gPrimitiveCursor[0];
    ((s32 *)D_800A36D0Absolute)[-67] = cursor + sizeof(POLY_FT4);
    entry = (POLY_FT4 *)cursor;
    *entry = *(POLY_FT4 *)prim;
    AddPrim((u8 *)D_800A39C8[0] + 0xFF8, entry);
}

extern s32 D_800A3784Absolute[], D_800A3790Absolute[], D_800A3794Absolute[];
extern s32 D_800A3798Absolute[], D_800A379CAbsolute[], D_800A37A4Absolute[];
extern s32 D_800A37ACAbsolute[], D_800A37B4Absolute[], D_800A37C4Absolute[];

void func_80034C1C(void) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = ((s32 *)D_800A36D0Absolute)[-8];
    b = ((s32 *)D_800A36D0Absolute)[-6];
    c = ((s32 *)D_800A36D0Absolute)[-2];
    d = D_800A36D0Absolute[0];
    D_800A3794Absolute[0] = 0;
    D_800A37A4Absolute[0] = 0;
    D_800A37ACAbsolute[0] = 0;
    D_800A37B4Absolute[0] = 0;
    D_800A37C4Absolute[0] = 0x10000;
    D_800A3784Absolute[0] = a;
    D_800A3790Absolute[0] = b;
    D_800A3798Absolute[0] = -c;
    D_800A379CAbsolute[0] = d;
}

extern s32 D_800A36D4Absolute[];
extern s32 D_800A3784Absolute[], D_800A3790Absolute[], D_800A3794Absolute[],
    D_800A3798Absolute[], D_800A379CAbsolute[], D_800A37A4Absolute[],
    D_800A37ACAbsolute[], D_800A37B4Absolute[], D_800A37C4Absolute[];
void func_80034C94(void) {
    D_800A3784Absolute[0] = 0x10000;
    D_800A3790Absolute[0] = 0;
    D_800A3794Absolute[0] = 0;
    D_800A3798Absolute[0] = 0;
    D_800A37ACAbsolute[0] = 0;
    D_800A379CAbsolute[0] = D_800A36D0Absolute[0];
    D_800A37A4Absolute[0] = D_800A36D4Absolute[0];
    D_800A37B4Absolute[0] = -D_800A36D4Absolute[0];
    D_800A37C4Absolute[0] = D_800A36D0Absolute[0];
}

extern s32 D_800A36C0Absolute[];
extern s32 D_800A36E8Absolute[];
extern s32 D_800A3790Absolute[], D_800A3798Absolute[], D_800A379CAbsolute[],
    D_800A37A4Absolute[], D_800A37B4Absolute[], D_800A3794Absolute[],
    D_800A3784Absolute[], D_800A37ACAbsolute[], D_800A37C4Absolute[];
void func_80034CFC(void) {
    D_800A3790Absolute[0] = 0;
    D_800A3798Absolute[0] = 0;
    D_800A379CAbsolute[0] = 0x10000;
    D_800A37A4Absolute[0] = 0;
    D_800A37B4Absolute[0] = 0;
    D_800A3784Absolute[0] = D_800A36E8Absolute[0];
    D_800A3794Absolute[0] = D_800A36C0Absolute[0];
    D_800A37ACAbsolute[0] = -D_800A36C0Absolute[0];
    D_800A37C4Absolute[0] = D_800A36E8Absolute[0];
}

#ifdef NON_MATCHING
void func_80034C1C(void) {
    D_800A3794[0] = 0;
    D_800A37A4[0] = 0;
    D_800A37AC[0] = 0;
    D_800A37B4[0] = 0;
    D_800A37C4[0] = 0x10000;
    D_800A3784[0] = D_800A36B0;
    D_800A3790[0] = D_800A36B8;
    D_800A3798[0] = -D_800A36C8;
    D_800A379C[0] = D_800A36D0;
}
#else
#endif

INCLUDE_ASM("asm/nonmatchings/objects", func_80034D64);

extern s32 D_800A2F44;
extern s32 D_800A38B4;
extern s32 D_800A38BC;
extern s32 D_800A36A8;
extern s32 D_800A36AC;
extern void *D_800A2EA0[];
extern s16 D_800B1ED8[], D_800B1EDA[], D_800B1EDC[], D_800B1EDE[];
extern s16 D_800B1EE0[], D_800B1EE2[], D_800B1EE4[], D_800B1EE6[];
extern u8 D_800B1ED0[];
extern POLY_FT4 D_800AFB18Wall[] asm("D_800AFB18");
extern u32 gPrimitiveCursorAdv1[] asm("gPrimitiveCursor");
extern u32 gPrimitiveCursorAdv2[] asm("gPrimitiveCursor");
extern u32 gPrimitiveCursorAdv3[] asm("gPrimitiveCursor");

void func_80035274(void) {
    u8 *obj;
    u8 *tpl;
    POLY_FT4 *prim;
    s32 x;
    s32 w;
    s32 ly;
    s32 ry;
    register s32 e1 asm("$3");
    s32 e0;
    register s32 rym2 asm("$6");
    register u32 drawCursor asm("$4");
    register POLY_FT4 *drawPrim asm("$7");
    register POLY_FT4 *entry asm("$8");
    register u32 cursorLoop asm("$3");
    register u32 cursorEnd asm("$2");
    register s32 yFixed asm("$18");
    register s32 nextY asm("$6");
    register s32 step asm("$2");
    s32 y0v;
    s32 y1t;
    register s32 ytmp asm("$2");
    register s32 dza asm("$4");
    s32 dz;
    s32 modq;
    s32 offX;
    register s32 offY asm("$23");
    register s32 yInt asm("$19");
    s32 scale;
    s32 mod;
    s32 idx;
    register s32 nextIdx asm("$5");
    s32 count;

    obj = (u8 *)D_800A2EA0[0];
    if (*(s16 *)(obj + 0x1EC) == 0 && *(s8 *)(obj + 0x20C) <= 0 &&
        ((*(s32 *)(obj + 0x354) == (s32)func_80025730 && D_800A397C[0] != 2) ||
         (D_800A397C[0] == 2 && *(s32 *)(obj + 0x388) != 0))) {
        tpl = D_800B1ED0;
        D_800B1ED8[0] = 0;
        D_800B1EDA[0] = 0;
        D_800B1EDC[0] = 0x140;
        D_800B1EDE[0] = 0;
        D_800B1EE0[0] = 0;
        D_800B1EE2[0] = 0xF0;
        D_800B1EE4[0] = 0x140;
        D_800B1EE6[0] = 0xF0;
        drawCursor = gPrimitiveCursor[0];
        drawPrim = (POLY_FT4 *)drawCursor;
        gPrimitiveCursorAdv1[0] = drawCursor + 0x28;
        *drawPrim = *(POLY_FT4 *)tpl;
        AddPrim((u8 *)D_800A39C8[0] + 0xFF8, drawPrim);
        return;
    }
    ly = D_800A38B4;
    ry = D_800A38BC;
    x = -0x20;
    w = 0x160;
    e0 = 0;
    e1 = 0;
    offX = D_800A36A8;
    offY = D_800A36AC;
    yInt = ly - 2;
    rym2 = ry - 2;
    if (yInt < 0) {
        e1 = yInt;
        x = 0;
    }
    if (rym2 < 0) {
        e0 = rym2;
        w = 0x140;
    }
    D_800B1EE2[0] = yInt;
    yInt = ly;
    D_800B1ED8[0] = 0;
    D_800B1EDA[0] = e1;
    D_800B1EDC[0] = 0x140;
    D_800B1EDE[0] = e0;
    D_800B1EE0[0] = x;
    D_800B1EE4[0] = w;
    D_800B1EE6[0] = rym2;
    scale = MathFixedDivide(ry - yInt, 0x180);
    tpl = D_800B1ED0;
    x = -0x20;
    dz = D_800A2F44;
    if (dz < 0) {
        dza = dz + 0x7F;
    } else {
        dza = dz;
    }
    idx = dza >> 7;
    mod = dz - (idx << 7);
    x = x - mod;
    count = 0;
    ytmp = yInt << 16;
    yFixed = ytmp - scale * mod;
    yInt = yFixed >> 16;
    do {
        step = scale << 7;
        nextY = yFixed + step;
        prim = &D_800AFB18Wall[idx];
        y0v = yInt + offY;
        prim->x2 = x;
        prim->y0 = y0v;
        prim->x0 = x + offX;
        prim->x1 = x + offX + 0x80;
        y1t = offY;
        prim->y1 = (nextY >> 16) + y1t;
        prim->y2 = yInt;
        prim->x3 = x + 0x80;
        prim->y3 = nextY >> 16;
        x = x + 0x80;
        yFixed = nextY;
        nextIdx = idx + 1;
        modq = nextIdx;
        if (nextIdx < 0) {
            modq = idx + 4;
        }
        idx = modq >> 2;
        mod = idx << 2;
        idx = nextIdx - mod;
        cursorLoop = gPrimitiveCursor[0];
        entry = (POLY_FT4 *)cursorLoop;
        gPrimitiveCursorAdv2[0] = (u32)entry + 0x28;
        *entry = *prim;
        AddPrim((u8 *)D_800A39C8[0] + 0xFF8, entry);
        count++;
    } while (yInt = yFixed >> 16, count < 6);
    cursorEnd = gPrimitiveCursor[0];
    gPrimitiveCursorAdv3[0] = cursorEnd + 0x28;
    entry = (POLY_FT4 *)cursorEnd;
    *entry = *(POLY_FT4 *)tpl;
    AddPrim((u8 *)D_800A39C8[0] + 0xFF8, entry);
}

extern void *D_800A2EA0[];
void func_80035274(void);
void func_8003565C(s32 arg0) {
    u8 *value;

    if (arg0 == 0) {
        value = D_800A3554[0];
    } else {
        value = *(u8 **)(D_800A3554[0] + 0x3E0);
    }
    D_800A2EA0[0] = (void *)value;
    func_80035274();
}

typedef struct {
    u8 pad[0x3E0];
    void *unk3E0;
} Data3554;

extern s32 D_800A2F3C[];
void func_80034D64(void);
void func_80035274(void);

void func_800356A8(s32 arg0) {
    void *value0;

    D_800A2F3C[0] = 0x3C;
    func_80034D64();
    if (arg0 == 0) {
        value0 = D_800A3554[0];
    } else {
        value0 = ((Data3554 *)D_800A3554[0])->unk3E0;
    }
    D_800A2EA0[0] = value0;
    func_80035274();
    D_800A2F3C[0] = 0x46;
}

extern s32 D_800A2F44;

void func_80035720(u_long *ot) {
    s32 value;
    s32 x;
    s32 y;
    s32 off;
    s32 i;
    s32 c;
    s32 nx;
    POLY_FT4 *prim;
    LINE_F4 *line;
    s32 bank;

    value = D_800A2F44;
    x = (0x200 - value) / 2;
    y = x / 64;
    x = y * 64 - x;
    i = 0;
    c = 0x23;
    off = y * 40;
    for (; i < 5; i++) {
        if (y >= 8) {
            off = 0;
            y = 0;
        }
        prim = (POLY_FT4 *)(D_800A3850 + off);
        y++;
        prim->x0 = x;
        prim->x2 = x;
        nx = x + 0x40;
        x = nx;
        off += 0x28;
        prim->y0 = 0;
        prim->x1 = nx;
        prim->y1 = 0;
        prim->y2 = c;
        prim->x3 = nx;
        prim->y3 = c;
        AddPrim(ot + 0x3FF, prim);
    }
    bank = gOrderingTableBankAbsolute[0];
    line = (LINE_F4 *)(D_800A390C + bank * 24);
    setXY4(line, 0xC8, 0x23, 0, 0x23, 0xC8, 0x46, 0, 0x46);
    setRGB0(line, 0x28, 0x6A, 2);
    AddPrim(ot + 0x3FF, line);
}

extern u8 D_800A2DE1[];
extern s32 D_800A2E9C[];
void func_8002F0A8(u8 *);
void func_80034D64(void);
void func_80035720(u_long *);
void func_8003587C(s32 arg0) {
    /* second stores to each symbol go through existing defsym
     * neighbors so gcc re-materializes lui/at instead of hoisting the
     * addresses into callee-saved registers:
     *   D_800A2E24-0x43 = 0x2DE1, D_800A2E24+70*4 = 0x2F3C */
    D_800A2DE1[0] = 1;
    func_8002F0A8(D_800A2E9C[0]);
    ((u8 *)D_800A2E24Absolute)[-0x43] = 0;
    D_800A2F3C[0] = 0x23;
    func_80034D64();
    func_80035720(arg0);
    ((s32 *)D_800A2E24Absolute)[70] = 0x82;
}

/* D_800A38A4 is reached through $gp here but through lui in
 * CarSteerTowardHeading, so this function uses a gp-sized alias. */
extern s32 D_800A38A4Small;
asm(".globl D_800A38A4Small\nD_800A38A4Small = D_800A38A4\n");
extern u8 D_800A2F48;
s32 func_800358EC(s32 *vec) {
    s32 len;
    s32 x;
    s32 y;
    s32 ax;
    s32 ay;
    s32 angle;

    len = MathSqrt(vec[0] * vec[0] + vec[1] * vec[1]);
    D_800A38A4Small = len;
    D_800A2F48 = 0;
    if (len < 5) {
        D_800A2F48 = 1;
        return 0;
    }
    if (vec[0] >= len) {
        len = vec[0] + 1;
    }
    if (vec[1] >= len) {
        len = vec[1] + 1;
    }
    x = MathFixedDivide(vec[0], len);
    y = MathFixedDivide(vec[1], len);
    if (y > 0x10000) {
        y = 0xFFFF;
    } else if (-y > 0x10000) {
        y = -0x10001;
    }
    if (x >= 0 && y >= 0) {
        if (x >= y) {
            angle = ((u8 *)D_800A3668Absolute[0])[y >> 4];
        } else {
            angle = 0x100 - ((u8 *)D_800A3668Absolute[0])[x >> 4];
        }
    } else if (x < 0 && y >= 0) {
        ax = -x;
        if (ax >= y) {
            angle = 0x200 - ((u8 *)D_800A3668Absolute[0])[y >> 4];
        } else {
            angle = ((u8 *)D_800A3668Absolute[0])[ax >> 4] + 0x100;
        }
    } else if (x >= 0 && y < 0) {
        ay = -y;
        if (x >= ay) {
            angle = 0x200 - ((u8 *)D_800A3668Absolute[0])[ay >> 4];
        } else {
            angle = ((u8 *)D_800A3668Absolute[0])[x >> 4] + 0x100;
        }
        angle += 0x200;
    } else {
        if (-y <= -x) {
            angle = ((u8 *)D_800A3668Absolute[0])[-y >> 4];
        } else {
            angle = 0x100 - ((u8 *)D_800A3668Absolute[0])[-x >> 4];
        }
        angle += 0x200;
    }
    return angle & 0x3FF;
}

extern u16 D_80090F24[];
extern u16 D_80091004[];
extern s32 D_800B60C8[];

/* Initialise the 0x48-entry 0xC8-stride tile table at D_800B60C8: three
 * banks of 24 entries. poly[1..4] of each entry become textured POLY_FT4s;
 * the 4 u16s at entry+0x20 prime poly[0]'s tail (counter/type/uv). Bank 0
 * takes 16x16 tiles from D_80090F24; banks 1-2 take translucent 64x64
 * tiles from D_80091004 (v3 = u+0x3F here is the original's quirk). */
void func_80035B20(void) {
    u8 *entry;
    u8 *prim;
    u16 *tex;
    s32 i;
    s32 j;

    entry = (u8 *)D_800B60C8;
    i = 0;
    tex = D_80090F24;
    do {
        *(u16 *)(entry + 0x20) = 0;
        *(u16 *)(entry + 0x22) = 0;
        *(u16 *)(entry + 0x24) = 0x10;
        *(u16 *)(entry + 0x26) = 0x10;
        j = 0;
        do {
            prim = entry + 0x28 + j * 0x28;
            SetPolyFT4((POLY_FT4 *)prim);
            SetShadeTex(prim, 1);
            *(u16 *)(prim + 0x16) = GetTPage(tex[0], 0, tex[-6], tex[-5]);
            *(u8 *)(prim + 0xC) = tex[-2];
            *(u8 *)(prim + 0xD) = tex[-1];
            *(u8 *)(prim + 0x14) = tex[-2] + 0xF;
            *(u8 *)(prim + 0x15) = tex[-1];
            *(u8 *)(prim + 0x1C) = tex[-2];
            *(u8 *)(prim + 0x1D) = tex[-1] + 0xF;
            *(u8 *)(prim + 0x24) = tex[-2] + 0xF;
            *(u8 *)(prim + 0x25) = tex[-1] + 0xF;
            j++;
        } while (j < 4);
        entry += 0xC8;
        i++;
    } while (i < 0x18);

    i = 0;
    tex = D_80091004;
    do {
        *(u16 *)(entry + 0x22) = 1;
        *(u16 *)(entry + 0x24) = 0x80;
        *(u16 *)(entry + 0x20) = 0;
        *(u16 *)(entry + 0x26) = 0x100;
        j = 0;
        do {
            prim = entry + 0x28 + j * 0x28;
            SetPolyFT4((POLY_FT4 *)prim);
            SetShadeTex(prim, 1);
            *(u16 *)(prim + 0x16) = GetTPage(tex[0], 3, tex[-6], tex[-5]);
            *(u16 *)(prim + 0xE) = GetClut(tex[-4], tex[-3]);
            SetSemiTrans(prim, 1);
            *(u8 *)(prim + 0xC) = tex[-2];
            *(u8 *)(prim + 0xD) = tex[-1];
            *(u8 *)(prim + 0x14) = tex[-2] + 0x3F;
            *(u8 *)(prim + 0x15) = tex[-1];
            *(u8 *)(prim + 0x1C) = tex[-2];
            *(u8 *)(prim + 0x1D) = tex[-1] + 0x3F;
            *(u8 *)(prim + 0x24) = tex[-2] + 0x3F;
            *(u8 *)(prim + 0x25) = tex[-2] + 0x3F;
            j++;
        } while (j < 4);
        entry += 0xC8;
        i++;
    } while (i < 0x18);

    i = 0;
    tex = D_80091004;
    do {
        *(u16 *)(entry + 0x22) = 2;
        *(u16 *)(entry + 0x24) = 0x80;
        *(u16 *)(entry + 0x20) = 0;
        *(u16 *)(entry + 0x26) = 0x100;
        j = 0;
        do {
            prim = entry + 0x28 + j * 0x28;
            SetPolyFT4((POLY_FT4 *)prim);
            SetShadeTex(prim, 1);
            *(u16 *)(prim + 0x16) = GetTPage(tex[0], 3, tex[-6], tex[-5]);
            *(u16 *)(prim + 0xE) = GetClut(tex[-4], tex[-3]);
            SetSemiTrans(prim, 1);
            *(u8 *)(prim + 0xC) = tex[-2];
            *(u8 *)(prim + 0xD) = tex[-1];
            *(u8 *)(prim + 0x14) = tex[-2] + 0x3F;
            *(u8 *)(prim + 0x15) = tex[-1];
            *(u8 *)(prim + 0x1C) = tex[-2];
            *(u8 *)(prim + 0x1D) = tex[-1] + 0x3F;
            *(u8 *)(prim + 0x24) = tex[-2] + 0x3F;
            *(u8 *)(prim + 0x25) = tex[-2] + 0x3F;
            j++;
        } while (j < 4);
        i++;
        entry += 0xC8;
    } while (i < 0x18);
}

void func_80035E8C(s32 *src, s32 *outX, s32 *outY) {
    s32 value;

    value = MathFixedDivide(src[0], src[2]);
    outX[0] = (MathMultiplyFixed16(value & -0x10, 0xD00000) >> 16) + 0xA0;
    value = MathFixedDivide(src[1], src[2]);
    outY[0] =
        (MathMultiplyFixed16(value & -0x10, 0xD00000) >> 16) + D_800A2F3C[0];
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80035F28);

extern u8 D_800A2ED8Arr[];
extern void func_80035F28(u8 *);

asm(".globl D_800A2ED8Arr\nD_800A2ED8Arr = D_800A2ED8");

/* Per-frame update of the 0xC8-stride entry table at D_800B60C8: builds a
 * camera-relative SVECTOR, ages the active counter, transforms the position
 * and hands visible entries to func_80035F28. */
void func_80036264(void) {
    u8 *p;
    s32 i;
    register s32 dz asm("v0");
    s32 *camera;
    s32 flagval;
    register s32 cx asm("a1");
    register s32 cy asm("a2");
    register s32 dx asm("a3");
    register s32 dy asm("t0");
    u16 count;
    SVECTOR sv;
    long flag;

    for (p = (u8 *)D_800B60C8, i = 0; i < 0x48; i++, p += 0xC8) {
        if (*(s16 *)(p + 0x20) == 0) {
            continue;
        }
        dz = *(s32 *)(p + 0x10);
        camera = (s32 *)D_800A38AC[0];
        flagval = D_800A2ED4[0];
        cx = camera[0];
        cy = camera[1];
        dz = dz - camera[2];
        dx = *(s32 *)(p + 0x8) - cx;
        dy = *(s32 *)(p + 0xC) - cy;
        sv.vz = dz;
        sv.vx = dx;
        sv.vy = dy;
        if (flagval == 0 && D_800A2ED8Arr[0] == 0 && D_800A2ED9[0] == 0) {
            count = *(u16 *)(p + 0x20) - 1;
            *(s16 *)(p + 0x20) = count;
            if (*(s16 *)(p + 0x22) >= 2) {
                *(s32 *)(p + 0x10) =
                    *(s32 *)(p + 0x10) + ((0x2D - (s16)count) * 2);
            } else {
                if ((s16)count >= 6) {
                    *(s32 *)(p + 0x10) = *(s32 *)(p + 0x10) + 5;
                } else {
                    *(s32 *)(p + 0x10) = *(s32 *)(p + 0x10) - 5;
                }
            }
        }
        dz = dx >= 0 ? dx < 0x3E81 : -dx < 0x3E81;
        if (dz) {
            dz = dy >= 0 ? dy < 0x3E81 : -dy < 0x3E81;
            if (dz) {
                RotTrans(&sv, (VECTOR *)(p + 0x14), &flag);
                if (*(s32 *)(p + 0x1C) >= 0x14) {
                    if (2 * *(s32 *)(p + 0x1C) < (*(s32 *)(p + 0x14) < 0
                                                      ? -*(s32 *)(p + 0x14)
                                                      : *(s32 *)(p + 0x14))) {
                        continue;
                    }
                    if (2 * *(s32 *)(p + 0x1C) < (*(s32 *)(p + 0x18) < 0
                                                      ? -*(s32 *)(p + 0x18)
                                                      : *(s32 *)(p + 0x18))) {
                        continue;
                    }
                    func_80035F28(p);
                }
            }
        }
    }
}

extern s32 D_800B60E8[];
void func_8003644C(s32 index, s32 arg1, s32 arg2, s32 arg3) {
    u8 *entry;
    u8 *base;
    s32 i;
    s32 flag;
    s32 longValue;
    s32 shortValue;

    i = 0;
    flag = (index < 2);
    longValue = 0x19;
    shortValue = 0xA;
    base = (u8 *)D_800B60E8 + index * 0x12C0;
    for (i = 0; i < 0x18; i++) {
        entry = base + i * 0xC8;
        if (*(s16 *)(entry + 0) == 0) {
            *(s32 *)(entry - 0x18) = arg1;
            *(s32 *)(entry - 0x14) = arg2;
            *(s32 *)(entry - 0x10) = arg3;
            if (flag == 0) {
                *(s16 *)(entry + 0) = longValue;
            } else {
                *(s16 *)(entry + 0) = shortValue;
            }
            return;
        }
    }
}

extern s32 D_800AEE50[];
void func_800364C4(void) {
    s32 i;
    s32 offset;
    u8 *dst;
    u8 *src;

    for (i = 0, dst = (u8 *)D_800AEE50, offset = 0, src = (u8 *)D_800B60C8;
         i < 0x48; offset += 0x28, i++, src += 0xC8) {
        *(Primitive40 *)(offset + (u32)dst) = *(Primitive40 *)src;
    }
}

void func_80036540(void) {
    s32 i;

    for (i = 0; i < 0x48; i++) {
        *(Primitive40 *)((u8 *)D_800B60C8 + i * 0xC8) =
            *(Primitive40 *)((u8 *)D_800AEE50 + i * 0x28);
    }
}

#ifdef NON_MATCHING
extern s32 D_800B7398[];
void func_800365B8(s32 *out) {
    s32 i;
    s32 count;
    u8 *entry;
    s32 value;
    s32 temp;

    count = 0;
    entry = (u8 *)D_800B7398;
    for (i = 0; i < 0x18; i++, entry += 0xC8) {
        if (*(s16 *)((u32)entry + 0x10) == 0) {
            continue;
        }
        value = *out;
        value = (value & -0x800) | ((*(s32 *)((u32)entry - 8) >> 7) & 0x7FF);
        *out = value;
        value = (value & 0xFFC007FF) |
                (((*(s32 *)((u32)entry - 4) >> 7) & 0x7FF) << 11);
        *out = value;
        temp = *(s32 *)entry;
        value = (value & 0x3FFFFF) | ((temp / 16) << 22);
        *out = value;
        out = out + 1;
        count = count + 1;
        if (count >= 0x14) {
            return;
        }
    }
    *out = 0;
}
#else
extern s32 D_800B7398[];
void func_800365B8(s32 *out) {
    s32 i;
    s32 count;
    s32 mask1;
    s32 mask2;
    s32 mask3;
    u8 *entry;
    s32 value;
    s32 temp;

    count = 0;
    i = 0;
    mask1 = -0x800;
    mask2 = 0xFFC007FF;
    mask3 = 0x3FFFFF;
    entry = (u8 *)D_800B7398;
head:
    if (*(s16 *)(entry + 0x10) == 0) {
        goto tail;
    }
    value = *out;
    value = (value & mask1) | ((*(s32 *)(entry - 8) >> 7) & 0x7FF);
    *out = value;
    value = (value & mask2) | (((*(s32 *)(entry - 4) >> 7) & 0x7FF) << 11);
    *out = value;
    temp = *(s32 *)entry;
    if (temp < 0) {
        temp = temp + 15;
    }
    value = (value & mask3) | ((temp >> 4) << 22);
    *out = value;
    out = out + 1;
    count = count + 1;
tail:
    i = i + 1;
    if (i < 0x18) {
        goto check;
    }
    *out = 0;
    return;
check:
    if (count < 0x14) {
        entry = entry + 0xC8;
        goto head;
    }
}

#endif

extern u8 D_800B7388Base[] asm("D_800B7388.NON_MATCHING");
extern u8 D_800B60C8Base[] asm("D_800B60C8.NON_MATCHING");

void func_8003667C(u32 *list) {
    u8 *p;
    s32 i;
    s32 tmp;
    s32 flag;
    s32 v;

    p = D_800B7388Base;
    i = 0;
    for (; i < 0x14; i++, list++) {
        if (*list == 0) {
            while (i < 0x18) {
                *(s16 *)(p + 0x20) = 0;
                i++;
                p += 0xC8;
            }
            p = D_800B60C8Base;
            i = 0x17;
            do {
                *(s16 *)(p + 0x20) = 0;
                p += 0xC8;
                i--;
            } while (i >= 0);
            return;
        }
        flag = D_800A2ED4[0];
        *(s16 *)(p + 0x20) = 5;
        if (flag == 0) {
            extern u32 RandomGetScaled16(s32);
            tmp = (*list & 0x7FF) << 7;
            if ((s32)RandomGetScaled16(0x20) < 0) {
                v = tmp - RandomGetScaled16(0x20);
            } else {
                v = tmp + RandomGetScaled16(0x20);
            }
            *(s32 *)(p + 8) = v;
            tmp = ((*list >> 11) & 0x7FF) << 7;
            if ((s32)RandomGetScaled16(0x20) < 0) {
                v = RandomGetScaled16(0x20);
                v = tmp - v;
            } else {
                v = tmp + RandomGetScaled16(0x20);
            }
            *(s32 *)(p + 0xC) = v;
            *(s32 *)(p + 0x10) =
                ((s32)*list >> 22) * 0x10 + RandomGetScaled16(8);
        }
        p += 0xC8;
    }
}

extern char D_8008D0AC[];
extern char D_8008D0CC[];

extern void *FileOpenCall367DC(void) asm("FileOpen");
extern s32 FileSeekCall367DC(void *, s32, s32) asm("FileSeek");
extern void FileReadCall367DC(s32, s32, s32, void *) asm("FileRead");
extern void FileCloseCall367DC(s32) asm("FileClose");
void func_800367DC(void) {
    extern s32 D_800A2F54;
    extern s32 D_800AE154[];
    extern s32 D_800B1EA8[];
    extern s32 D_800B60A4[];
    void *handle;
    void *buffer;
    s32 size;
    s32 idx;
    s32 entry;

    handle = FileOpenCall367DC();
    if (handle == NULL) {
        SystemShowFatalError(D_8008D0AC);
    }
    size = FileSeekCall367DC(handle, 0, 2);
    FileSeekCall367DC(handle, 0, 0);
    buffer = HeapAlloc(((size + 0x7FF) >> 11) << 11);
    D_800AE154[D_800A2F54] = (s32)buffer;
    if (buffer == NULL) {
        SystemShowFatalError(D_8008D0CC);
    }
    FileReadCall367DC(D_800AE154[D_800A2F54], 1, size, handle);
    idx = D_800A2F54;
    entry = D_800AE154[idx];
    D_800B60A4[idx] = entry;
    D_800B1EA8[idx] = *(s32 *)entry;
    D_800AE154[idx] = entry + 4;
    D_800A2F54 = idx + 1;
    FileCloseCall367DC((s32)handle);
}

INCLUDE_RODATA("asm/nonmatchings/objects", D_8008D0AC);
INCLUDE_RODATA("asm/nonmatchings/objects", D_8008D0CC);

extern s32 D_800A2F4C;
extern u8 D_800A2F58;
extern u8 D_800A372C[];
extern u8 D_800A38B8[];
extern s32 gSteeringVectorLength[] asm("D_800A38A4");
extern u8 *gTrackForSteering[] asm("D_800BE980");

void CarSteerTowardHeading(u8 *car, s32 targetHeading) {
    s32 maxStep;
    s32 delta;
    s32 speed;
    s32 divisor;
    s32 value;
    s32 numerator;
    s32 result;
    s32 headingSum;

    delta = *(s16 *)(car + 0x114) - targetHeading;
    if (delta >= 0 ? delta >= 0x200 : -delta >= 0x200) {
        if (delta < 0) {
            delta += 0x400;
        } else {
            delta -= 0x400;
        }
    }
    if (*(u8 *)(car + 0x268) == 0) {
        maxStep = D_800A2F4C;
        if (*(u16 *)(car + 0x3A4) & 0x20) {
            maxStep = maxStep * 17 / 20;
        }
        if (*(u16 *)(car + 0x3A4) & 0x40) {
            maxStep = D_800A2F4C * 17 / 20;
        }
        if (*(u16 *)(car + 0x3A4) & 0x80) {
            maxStep = D_800A2F4C * 15 / 20;
        }
        if (*(s16 *)(car + 0x24E) == -1) {
            value = 1000 - ((*(s16 *)(car + 0x92) - 250) * 12000) / 5500;
            maxStep = maxStep * value / 1000;
        }
        speed = *(s16 *)(car + 0x92);
        if (speed != 0) {
            if (D_800A372C[0] != 0) {
                if (D_800A38B8[0] == 0) {
                    if ((ABS(MathGetAngleDelta(
                             *(s16 *)(car + 0x114),
                             *(u16 *)(gTrackForSteering[0] +
                                      *(s16 *)(car + 0x1E0) * 0x90 + 0x10))) <
                         65) != 0) {
                        goto scaleSteering;
                    }
                }
                divisor = 1;
            } else {
            scaleSteering:
                divisor = gSteeringVectorLength[0] / speed;
            }
            if (divisor >= 2) {
                divisor--;
            }
            if (divisor != 0) {
                *(s16 *)(car + 0x20E) = -delta / divisor;
                if (*(s16 *)(car + 0x20E) >= 0
                        ? *(s16 *)(car + 0x20E) > maxStep
                        : -*(s16 *)(car + 0x20E) > maxStep) {
                    if (*(s16 *)(car + 0x20E) > maxStep) {
                        *(s16 *)(car + 0x20E) = maxStep;
                    } else {
                        *(s16 *)(car + 0x20E) = -maxStep;
                    }
                    if (*(s16 *)(car + 0x20E) >= 0) {
                        numerator = maxStep - (*(s16 *)(car + 0x20E) - maxStep);
                    } else {
                        numerator = maxStep * 2 + *(s16 *)(car + 0x20E);
                    }
                    result = MathMultiplyFixed16(
                        *(s32 *)(car + 0x90),
                        MathFixedDivide(numerator, maxStep + 3));
                    if (*(s32 *)(car + 0x90) - result > 0x140000) {
                        *(s32 *)(car + 0x90) -= 0x140000;
                    } else {
                        *(s32 *)(car + 0x90) = result;
                    }
                }
            } else {
                *(s16 *)(car + 0x20E) = 0;
            }
        } else {
            *(s16 *)(car + 0x20E) = 0;
        }
    } else {
        if (D_800A2F58 != 0) {
            if (*(s32 *)(car + 0x90) > 0x960000) {
                maxStep =
                    (D_800A2F4C *
                     MathFixedDivide(50, (*(s32 *)(car + 0x90) >> 16) - 150)) >>
                    16;
            } else {
                maxStep = D_800A2F4C;
            }
            if (maxStep > D_800A2F4C) {
                maxStep = D_800A2F4C;
            }
            if (maxStep < 3) {
                maxStep = 3;
            }
            result = maxStep * 2;
            if ((delta >= 0 ? delta > result : -delta > result) &&
                (*(s32 *)(car + 0x90) >> 16) >= 241) {
                *(s32 *)(car + 0x90) -= 0x90000;
            }
        } else {
            maxStep = D_800A2F4C;
        }
        *(s16 *)(car + 0x20E) /= 4;
        if (delta < 0) {
            if (D_800A2F58 != 0) {
                (*(u8 *)(car + 0x207))++;
                if (*(s8 *)(car + 0x207) >= 3) {
                    *(u8 *)(car + 0x207) = 3;
                }
            } else {
                *(u8 *)(car + 0x207) = 5;
            }
            *(u8 *)(car + 0x208) = 0;
            *(s16 *)(car + 0x20E) += *(s8 *)(car + 0x207);
            if (*(s16 *)(car + 0x20E) > maxStep) {
                *(s16 *)(car + 0x20E) = maxStep;
            }
            if (*(s16 *)(car + 0x20E) < -delta) {
                *(s16 *)(car + 0x20E) = -delta;
            }
            if (delta < -maxStep) {
                *(s16 *)(car + 0x20E) = maxStep;
            } else {
                *(s16 *)(car + 0x20E) = -delta;
            }
        } else if (delta > 0) {
            if (D_800A2F58 != 0) {
                (*(u8 *)(car + 0x208))++;
                if (*(s8 *)(car + 0x208) >= 3) {
                    *(u8 *)(car + 0x208) = 3;
                }
            } else {
                *(u8 *)(car + 0x208) = 5;
            }
            *(u8 *)(car + 0x207) = 0;
            *(s16 *)(car + 0x20E) -= *(s8 *)(car + 0x208);
            if (*(s16 *)(car + 0x20E) < -maxStep) {
                *(s16 *)(car + 0x20E) = -maxStep;
            }
            if (-delta < *(s16 *)(car + 0x20E)) {
                *(s16 *)(car + 0x20E) = -delta;
            }
            if (delta > maxStep) {
                *(s16 *)(car + 0x20E) = -maxStep;
            } else {
                *(s16 *)(car + 0x20E) = -delta;
            }
        } else {
            *(u8 *)(car + 0x208) = *(u8 *)(car + 0x207) = 0;
            if (*(s16 *)(car + 0x20E) > 0) {
                *(s16 *)(car + 0x20E) -= 3;
                if (*(s16 *)(car + 0x20E) < 0) {
                    *(s16 *)(car + 0x20E) = 0;
                }
            } else {
                *(s16 *)(car + 0x20E) += 3;
                if (*(s16 *)(car + 0x20E) > 0) {
                    *(s16 *)(car + 0x20E) = 0;
                }
            }
            *(s16 *)(car + 0x20E) = 0;
        }
    }
    value = *(s16 *)(car + 0x20E) + 1024;
    headingSum = *(s16 *)(car + 0x114) + value;
    delta = headingSum / 1024;
    *(s16 *)(car + 0x11A) = headingSum - delta * 1024;
    *(s16 *)(car + 0x114) = *(s16 *)(car + 0x11A);
    *(s16 *)(car + 0x20E) *= 4;
}

s32 func_80036F64(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 idx;
    s32 tA;
    s32 tB;
    s32 dx;
    s32 dy;

    idx = (*((s16 *)(arg1 + 0x114))) << 2;
    dx = *(s32 *)arg0 - *(s32 *)arg1;
    tA = *((s32 *)(idx + ((u32)D_800A3A2CAbsolute[0])));
    dy = *(s32 *)(arg0 + 4) - *(s32 *)(arg1 + 4);
    tB = *((s32 *)(idx + ((u32)D_800A3A34Absolute[0])));
    return arg2 < ((tA * dx - tB * dy) >> 16);
}

s32 func_80036FC8(s32 *a, s32 *b) {
    s32 index;
    s32 t1;
    s32 t2;
    s32 x;
    s32 y;

    index = *(s16 *)(((u8 *)b) + 0x114) << 2;
    x = a[0] - b[0];
    t1 = *(s32 *)(index + (u32)D_800A3A34Absolute[0]);
    y = a[1] - b[1];
    t2 = *(s32 *)(index + (u32)D_800A3A2CAbsolute[0]);
    return ((t1 * x + t2 * y) >> 16) > 0;
}

#ifdef NON_MATCHING
extern s32 D_800BE974[];
s32 func_8003702C(u8 *objectA, u8 *objectB) {
    s32 limit;
    s32 diff;
    s32 a;
    s32 b;

    limit = D_800BE974[0];
    diff = *(s16 *)(objectA + 0x1E0) - *(s16 *)(objectB + 0x1E0);
    if (diff >= 0) {
        if (diff < (limit >> 1)) {
            return diff;
        }
    } else {
        if ((limit >> 1) > -diff) {
            return diff;
        }
    }
    a = *(s16 *)(objectA + 0x1E0);
    b = *(s16 *)(objectB + 0x1E0);
    if (b < a) {
        b = b + limit;
        if (b - a < 0) {
            return b - a;
        }
        return a - b;
    }
    a = a + limit;
    if (a - b >= 0) {
        return a - b;
    }
    return b - a;
}
#else
#ifdef NON_MATCHING
/*
 * WALL (w9d): two diffs. (1) gcc copies arg0 to a2 at entry (`move
 * a2,a0`) because the s16 fields are read twice (once for the early
 * |diff| check, once for the wraparound path) and gcc 2.7.2 gives the
 * pointer its own callee pseudo; retail reuses a0/a1 as both base and
 * lh destination. (2) the inner `if (diff < half) return diff;`
 * compiles beqz-to-common where retail has bnez-to-return (branch
 * sense inverted; the ?: spelling was not tried in time). The wrap
 * path shape is right: y >= x vs y < x arms, threshold added to the
 * SMALLER value, sign flip on the negative result. D_800BE974 %lo
 * showed +0x18 drift while this draft was active -- self-inflicted
 * wrong length, not a split problem.
 */
extern s32 D_800BE974[];

s32 func_8003702C(s32 arg0, s32 arg1) {
    s32 diff;
    s32 half;
    s32 x;
    s32 y;

    diff = *(s16 *)(arg0 + 0x1E0) - *(s16 *)(arg1 + 0x1E0);
    half = D_800BE974[0] >> 1;
    if (diff >= 0) {
        if (diff < half) {
            return diff;
        }
    } else {
        if (-diff < half) {
            return diff;
        }
    }
    x = *(s16 *)(arg0 + 0x1E0);
    y = *(s16 *)(arg1 + 0x1E0);
    if (y < x) {
        y += D_800BE974[0];
        diff = x - y;
        if (diff < 0) {
            return diff;
        }
        return x - y;
    }
    x += D_800BE974[0];
    diff = x - y;
    if (diff >= 0) {
        return diff;
    }
    return y - x;
}
#endif

extern s32 D_800BE974[];

s32 func_8003702C(u8 *objectA, u8 *objectB) {
    s32 limit;
    s32 diff;
    s32 half;
    s32 a;
    s32 b;

    limit = D_800BE974[0];
    diff = *(s16 *)(objectA + 0x1E0) - *(s16 *)(objectB + 0x1E0);
    half = limit >> 1;
    if ((diff < 0 ? -diff : diff) < half) {
        return diff;
    }
    a = *(s16 *)(objectA + 0x1E0);
    b = *(s16 *)(objectB + 0x1E0);
    if (b < a) {
        b = b + limit;
        if (b - a < 0) {
            return b - a;
        }
        return a - b;
    }
    a = a + limit;
    if (a - b >= 0) {
        return a - b;
    }
    return b - a;
}

#endif

#ifdef NON_MATCHING
extern s32 D_800BE974[];
s32 func_800370B8(s32 a, s32 b) {
    s32 limit;
    s32 diff;

    limit = D_800BE974[0];
    diff = a - b;
    if (diff >= 0) {
        if (diff < (limit >> 1)) {
            return diff;
        }
    } else {
        if (-diff < (limit >> 1)) {
            return diff;
        }
    }
    if (b < a) {
        b = b + limit;
        if (b - a < 0) {
            return b - a;
        }
        return a - b;
    }
    a = a + limit;
    if (a - b >= 0) {
        return a - b;
    }
    return b - a;
}
#else
extern s32 D_800BE974[];

s32 func_800370B8(s32 a, s32 b) {
    s32 limit;
    s32 diff;
    s32 half;

    limit = D_800BE974[0];
    diff = a - b;
    half = limit >> 1;
    if ((diff < 0 ? -diff : diff) < half) {
        return diff;
    }
    if (b < a) {
        b = b + limit;
        if (b - a < 0) {
            return b - a;
        }
        return a - b;
    }
    a = a + limit;
    if (a - b >= 0) {
        return a - b;
    }
    return b - a;
}

#endif

#ifdef NON_MATCHING
/*
 * WALLS: (1) retail re-reads *(s16 *)(object + 0x92) once per product
 * (three lh) — plain reads CSE into one lh and a volatile s16 read
 * emits lhu + sll16/sra16 instead of lh (extends the w5b entry);
 * (2) retail gaps mult and mflo with the next row's lh/lw (two
 * instructions + hazard nops); gcc 2.7.2 binds mult+mflo as one
 * pattern, so mflo lands immediately after mult. Prologue solved:
 * store-first with a volatile second 0x114 read puts the sh in the
 * jal delay slot, though that read is lhu in ours vs lh in retail.
 * Products map 0xB0=prod(0x60), 0xB4=prod(0x6C), 0xB8=prod(0x78);
 * the volatile reloads of 0xB0/B4/B8 before the adds are exact.
 */
void func_8001FAC0(u8 *, s32);
void func_8001FB28(u8 *, s16);
void func_80037130(u8 *object) {
    s32 prod0;
    s32 prod1;
    s32 prod2;
    s32 sum0;
    s32 sum1;
    s32 sum2;

    *(s16 *)(object + 0x116) = *(volatile s16 *)(object + 0x114) * 4;
    func_8001FAC0(object, *(s16 *)(object + 0x114) * 4);
    func_8001FB28(object, *(s16 *)(object + 0x104));
    prod0 = *(volatile s16 *)(object + 0x92) * *(s32 *)(object + 0x60);
    prod1 = *(volatile s16 *)(object + 0x92) * *(s32 *)(object + 0x6C);
    prod2 = *(volatile s16 *)(object + 0x92) * *(s32 *)(object + 0x78);
    *(s32 *)(object + 0xB0) = prod0 >> 16;
    *(s32 *)(object + 0xB4) = prod1 >> 16;
    *(s32 *)(object + 0xB8) = prod2 >> 16;
    sum0 = *(s32 *)(object + 0x0) + *(volatile s32 *)(object + 0xB0);
    sum1 = *(s32 *)(object + 0x4) + *(volatile s32 *)(object + 0xB4);
    sum2 = *(s32 *)(object + 0x8) + *(volatile s32 *)(object + 0xB8);
    *(s32 *)(object + 0x0) = sum0;
    *(s32 *)(object + 0x4) = sum1;
    *(s32 *)(object + 0x8) = sum2;
}
#else
void func_8001FAC0(u8 *, s32);
void func_8001FB28(u8 *, s32);
void func_80037130(u8 *object) {
    *(s16 *)(object + 0x116) = *(s16 *)(object + 0x114) * 4;
    func_8001FAC0(object, *(s16 *)(object + 0x114) * 4);
    func_8001FB28(object, *(s16 *)(object + 0x104));
    *(s32 *)(object + 0xB0) =
        (*(s32 *)(object + 0x60) * *(s16 *)(object + 0x92)) >> 16;
    *(s32 *)(object + 0xB4) =
        (*(s32 *)(object + 0x6C) * *(s16 *)(object + 0x92)) >> 16;
    *(s32 *)(object + 0xB8) =
        (*(s32 *)(object + 0x78) * *(s16 *)(object + 0x92)) >> 16;
    *(s32 *)(object + 0x0) += *(s32 *)(object + 0xB0);
    *(s32 *)(object + 0x4) += *(s32 *)(object + 0xB4);
    *(s32 *)(object + 0x8) += *(s32 *)(object + 0xB8);
}

#endif

extern s32 D_800A39E0[];

s32 func_80037204(u8 *obj) {
    extern void *D_800BE980z[] asm("D_800BE980");
    u8 *node;
    s32 tmp;
    s32 heading;
    s32 num;
    s32 den;
    s32 rem;
    u8 *base;
    register s32 t asm("v1");
    register s32 idx asm("v0");
    u8 *b2;
    u8 *addr;
    u8 *entry;
    u16 counter;
    u16 val;

    node = D_800A3878w15[0];
    tmp = *(s32 *)(obj + 0x3CC);
    *(s32 *)(obj + 0x414) = -1;
    *(s32 *)(obj + 0x354) = (s32)func_80025594;
    *(s32 *)(obj + 0x90) = 0;
    *(s32 *)(obj + 0x84) = 0;
    if (tmp > 0) {
        goto fail;
    }
    while (node != 0 && *(s16 *)(node + 0x1EC) == 0) {
        if (func_8003702C(node, obj) < 0) {
            if (-func_8003702C(node, obj) < 25) {
                goto fail;
            }
        } else {
            if (func_8003702C(node, obj) < 25) {
            fail:
                return 0;
            }
        }
        node = *(u8 **)(node + 0x3E0);
    }
    if (*(u8 *)(obj + 0xF4) != 0) {
        func_80041848(obj, 12);
        heading = *(s16 *)(obj + 0x28A);
        *(u8 *)(obj + 0xF4) = 0;
        num = D_800A39E0[0] + heading;
        den = D_800BE974[0];
        rem = num % den;
        base = (u8 *)D_800BE980[0];
        idx = rem * 0x90;
        entry = base + idx;
        t = *(s32 *)(entry + 0x48);
        *(s32 *)(obj + 0x0) = t;
        t = *(s32 *)(entry + 0x4C);
        *(s32 *)(obj + 0x4) = t;
        b2 = (u8 *)D_800BE980z[0];
        val = *(u16 *)(idx + (s32)b2 + 0x10);
        counter = *(u16 *)(obj + 0x1D6);
        counter = counter - 2;
        *(u16 *)(obj + 0x1D6) = counter;
        *(u16 *)(obj + 0x104) = val;
        *(u16 *)(obj + 0x114) = val;
        if ((s16)counter < 0) {
            *(u16 *)(obj + 0x1D6) = 0;
        }
        if (obj == D_800A3960w15[0]) {
            D_800A3960[0] = 0;
        }
    }
    return 1;
}

INCLUDE_RODATA("asm/nonmatchings/objects", D_8008D0F8);

typedef struct {
    u8 *cars[6];
} AiNearbyCars373B4;
extern const AiNearbyCars373B4 D_8008D0F8;
extern s32 D_800A2E4C373B4[];
extern s32 D_800A2E90373B4[];
extern s32 D_800A2E94373B4[];
extern s32 D_800A2EA4373B4[];
extern s32 D_800A2EAC373B4[];
extern s32 D_800A2EB0373B4[];
extern u8 D_800A2EDC373B4[];
extern u8 D_800A2EE0373B4[];
extern u8 D_800A2F48373B4[];
extern s32 D_800A2F50373B4;
extern s32 D_800A2F54373B4;
extern u8 D_800A2F58373B4;
extern s32 D_800A2F5C373B4;
extern s32 D_800A2F84373B4[];
extern u8 D_800A3071373B4[];
extern u8 D_800A3320373B4[];
extern u8 *D_800A3554373B4[];
extern s8 D_800A3564373B4[];
extern s32 D_800A3598373B4[];
extern u8 *D_800A35E0373B4[];
extern u8 D_800A3670373B4[];
extern s32 D_800A36A4373B4;
extern u8 *D_800A3728373B4[];
extern u8 D_800A372C373B4[];
extern s8 D_800A3764373B4[];
extern u8 *D_800A37C0373B4[];
extern u8 *D_800A3878373B4[];
extern s16 D_800A3910373B4[];
extern u8 *D_800A3960373B4[];
extern s32 *D_800A3A2C373B4[];
extern s32 *D_800A3A34373B4[];
extern u8 *D_800A3A64373B4[];
extern u8 *D_800AE154373B4[];
extern s32 D_800B1EA8373B4[];
extern s32 D_800BE974373B4[];
extern u8 *D_800BE980373B4[];
extern s32 func_800A2CE0373B4[];
extern s32 MathFixedDivide373B4(s32, s32) asm("MathFixedDivide");
extern s32 MathMultiplyFixed16373B4(s32, s32) asm("MathMultiplyFixed16");
extern void ObjectSetCallbackIfAllowed373B4(u8 *, void (*)(void)) asm(
    "ObjectSetCallbackIfAllowed");
extern s32 RandomScaledGet373B4(s32) asm("RandomScaledGet");
extern void func_8001FAC0373B4(u8 *, s32) asm("func_8001FAC0");
extern void func_8001FB28373B4(u8 *, s16) asm("func_8001FB28");
extern void func_80029CB4373B4(u8 *) asm("func_80029CB4");
extern void func_8002A1D0373B4(u8 *) asm("func_8002A1D0");
extern void func_8002BC88373B4(u8 *) asm("func_8002BC88");
extern void func_8002D16C373B4(u8 *) asm("func_8002D16C");
extern s32 func_800358EC373B4(s32 *) asm("func_800358EC");
extern void CarSteerTowardHeading373B4(u8 *, s32) asm("CarSteerTowardHeading");
extern s32 func_8003702C373B4(u8 *, u8 *) asm("func_8003702C");
extern s32 func_80037204373B4(u8 *) asm("func_80037204");
extern s32 CarAvoidTraffic373B4(u8 *, s32) asm("CarAvoidTraffic");
extern void func_8003DBA8373B4(u8 *) asm("func_8003DBA8");
extern u8 func_8003E78C373B4(u8 *) asm("func_8003E78C");
extern void func_80044114373B4(u8 *) asm("func_80044114");
extern s8 func_80045480373B4(u8 *, s32) asm("func_80045480");
extern void func_800488A4373B4(u8 *) asm("func_800488A4");
extern void func_80025594373B4(void) asm("func_80025594");
extern void func_80025730373B4(void) asm("func_80025730");
extern void func_8003AA20373B4(void) asm("func_8003AA20");
__asm__(
    ".globl D_800A2E4C373B4\nD_800A2E4C373B4 = D_800A2E4C\n.globl D_800A2E90373B4\nD_800A2E90373B4 = D_800A2E90\n.globl D_800A2E94373B4\nD_800A2E94373B4 = D_800A2E94\n.globl D_800A2EA4373B4\nD_800A2EA4373B4 = D_800A2EA4\n.globl D_800A2EAC373B4\nD_800A2EAC373B4 = D_800A2EAC\n.globl D_800A2EB0373B4\nD_800A2EB0373B4 = D_800A2EB0\n.globl D_800A2EDC373B4\nD_800A2EDC373B4 = D_800A2EDC\n.globl D_800A2EE0373B4\nD_800A2EE0373B4 = D_800A2EE0\n.globl D_800A2F48373B4\nD_800A2F48373B4 = D_800A2F48\n.globl D_800A2F50373B4\nD_800A2F50373B4 = D_800A2F50\n.globl D_800A2F54373B4\nD_800A2F54373B4 = D_800A2F54\n.globl D_800A2F58373B4\nD_800A2F58373B4 = D_800A2F58\n.globl D_800A2F5C373B4\nD_800A2F5C373B4 = D_800A2F5C\n.globl D_800A2F84373B4\nD_800A2F84373B4 = D_800A2F84\n.globl D_800A3071373B4\nD_800A3071373B4 = D_800A3071\n.globl D_800A3320373B4\nD_800A3320373B4 = D_800A3320\n.globl D_800A3554373B4\nD_800A3554373B4 = D_800A3554\n.globl D_800A3564373B4\nD_800A3564373B4 = D_800A3564\n.globl D_800A3598373B4\nD_800A3598373B4 = D_800A3598\n.globl D_800A35E0373B4\nD_800A35E0373B4 = D_800A35E0\n.globl D_800A3670373B4\nD_800A3670373B4 = D_800A3670\n.globl D_800A36A4373B4\nD_800A36A4373B4 = D_800A36A4\n.globl D_800A3728373B4\nD_800A3728373B4 = D_800A3728\n.globl D_800A372C373B4\nD_800A372C373B4 = D_800A372C\n.globl D_800A3764373B4\nD_800A3764373B4 = D_800A3764\n.globl D_800A37C0373B4\nD_800A37C0373B4 = D_800A37C0\n.globl D_800A3878373B4\nD_800A3878373B4 = D_800A3878\n.globl D_800A3910373B4\nD_800A3910373B4 = D_800A3910\n.globl D_800A3960373B4\nD_800A3960373B4 = D_800A3960\n.globl D_800A3A2C373B4\nD_800A3A2C373B4 = D_800A3A2C\n.globl D_800A3A34373B4\nD_800A3A34373B4 = D_800A3A34\n.globl D_800A3A64373B4\nD_800A3A64373B4 = D_800A3A64\n.globl D_800AE154373B4\nD_800AE154373B4 = D_800AE154\n.globl D_800B1EA8373B4\nD_800B1EA8373B4 = D_800B1EA8\n.globl D_800BE974373B4\nD_800BE974373B4 = D_800BE974\n.globl D_800BE980373B4\nD_800BE980373B4 = D_800BE980\n.globl func_800A2CE0373B4\nfunc_800A2CE0373B4 = func_800A2CE0\n");

/* Update AI route speed, pace following, nearby lanes, and steering. */
void func_800373B4(u8 *object) {
    register u8 *car asm("$18");
    register u8 *middleOther asm("$4");
    register u32 middleOne asm("$9");
    register s32 middleFlag asm("$2");
    register s32 middleRandomLimit asm("$4");

    register s32 collisionCarX asm("$7");
    register s32 collisionCarY asm("$8");
    register s32 collisionArgument0 asm("$4");
    register s32 collisionArgument1 asm("$5");
    register s32 collisionNeighborY asm("$6");
    register s32 collisionTableBase asm("$3");
    register s32 collisionTableOffset asm("$16");
    register s32 collisionReturn asm("$2");
    register s32 collisionWidthCopy asm("$4");
    register s32 collisionNeighborOrder asm("$3");
    register s32 collisionCarOrder asm("$2");

    register u32 active asm("$2");
    register s32 paceMatch asm("$19");
    register s32 paceCarGap asm("$6");
    register s32 paceDistance asm("$16");
    register s32 paceBase asm("$9");
    register u32 trackCenterFlag asm("$9");
    register u32 peerFollowFlag asm("$2");
    register s32 pressureTimerValue asm("$2");
    register s32 standingTest asm("$2");
    register s32 paceTimer asm("$2");
    register s32 timerBase asm("$6");
    register s32 tireAge2 asm("$3");
    register s32 counterScale asm("$3");
    register s32 speedResult asm("$2");
    register u8 *playerCar asm("$2");
    register s32 slowDelta asm("$3");
    register u32 routeRaceMode asm("$2");
    register u32 routeLeftFlag asm("$3");
    register s32 routeDenominator asm("$5");
    s64 multiplierState;
    register s32 routeSelection asm("$7");
    struct {
        s32 delta[3];
        s32 reserved1C;
        AiNearbyCars373B4 nearby;
        s32 targetX;
        s32 reserved3C;
        s32 targetY;
        s32 reserved44;
        s32 heading;
        s32 reserved4C;
        u8 allowRight;
        u8 reserved51[7];
        u8 allowLeft;
        u8 reserved59[7];
        s32 paceSpeed;
        s32 reserved64;
        u8 useTrackCenter;
        u8 reserved69[7];
        u8 useSameSegment;
        u8 reserved71[7];
        /* Stack-layout pin: retail reserves these compiler stack words
         * through sp+0x9F, before the saved s0 home at sp+0xA0. */
        s32 reserved78[10];
    } workspace;

    void (*tempV118)(u8 *, s32);
    register s32 tempA22 asm("$6");
    register s32 tempV114 asm("$3");
    register s32 tailMinusOne asm("$2");
    register s32 tailSegment asm("$4");
    register s32 tailRouteLength asm("$7");
    register s32 tailTargetValue asm("$9");
    register u8 *tailCarArg asm("$4");
    register s32 tailPositionZ asm("$5");

    register s32 varV04 asm("$2");
    register s32 tempA012 asm("$4");
    register s32 tempA02 asm("$4");
    register s32 tempS0 asm("$16");
    register s32 tempS03 asm("$16");
    register s32 lateralSinProduct asm("$16");
    register s32 longitudinalGap asm("$16");
    register s32 deltaX asm("$20");
    register s32 reverseAngle asm("$21");
    register s32 deltaY asm("$22");
    register s32 lateralGap asm("$2");
    register s32 tempV018 asm("$2");
    register s32 tempV020 asm("$2");
    register s32 tempV021 asm("$2");
    register s32 tempV03 asm("$2");
    register s32 tempV04 asm("$2");
    register s32 tempV112 asm("$3");
    register s32 tempV113 asm("$3");
    register s32 tempV115 asm("$3");
    register s32 tempV116 asm("$3");
    register s32 tempV117 asm("$3");
    register s32 tempV16 asm("$3");
    register s32 tempV17 asm("$3");
    register s32 varA0 asm("$4");
    register s32 varA02 asm("$4");
    register s32 varA1 asm("$5");
    register s32 varA12 asm("$5");
    register s32 varA13 asm("$5");
    register s32 varA14 asm("$5");
    register s32 varA15 asm("$5");
    register s32 varA16 asm("$5");
    register s32 varA17 asm("$5");
    register s32 varA18 asm("$5");
    register s32 varA19 asm("$5");
    s32 nearbyLaneMask;
    register s32 overlapIndex asm("$19");
    register s32 blockedLaneMask asm("$21");
    register s32 paceGap asm("$22");
    register s32 nearbyCount asm("$23");
    register s32 varV0 asm("$2");
    register s32 varV011 asm("$2");
    register s32 overlapOffset asm("$2");
    register s32 varV016 asm("$2");
    register s32 varV017 asm("$2");
    register s32 varV02 asm("$2");
    register s32 varV03 asm("$2");
    register s32 varV06 asm("$2");
    register s32 varV07 asm("$2");
    register s32 varV1 asm("$3");
    register s32 varV13 asm("$3");
    register s32 varV14 asm("$3");
    register s32 varV15 asm("$3");
    register s32 varV17 asm("$3");
    register s32 tempA07 asm("$4");
    register s8 tempV0 asm("$2");
    register s32 tempV010 asm("$2");
    register s32 tempV011 asm("$2");
    register s8 tempV014 asm("$2");
    register s8 tempV017 asm("$2");
    register s32 tempV09 asm("$2");
    register s32 tempV13 asm("$3");
    register s32 tempV18 asm("$3");
    register s32 tempV19 asm("$3");
    register s32 desiredLane asm("$19");
    register s32 varV012 asm("$2");
    register u16 tempA13 asm("$5");
    u8 **tempA1;
    register u8 *aheadOfFollowingCar asm("$16");
    register u8 *followingCar asm("$17");
    register u8 *paceLeader asm("$17");
    register u8 *forwardNeighbor asm("$17");
    register u8 *backwardNeighbor asm("$17");
    register u8 *blockingCar asm("$17");
    register u8 *paceAheadCar asm("$17");
    register u8 tempA06 asm("$4");
    register u8 tempV015 asm("$2");
    register u8 tempV016 asm("$2");
    register u8 followAllowed asm("$20");
    register s32 varV08 asm("$2");
    register s32 varV09 asm("$2");
    register u8 varV12 asm("$3");
    register s32 varV16 asm("$3");
    register void *tempA03 asm("$4");
    register void *tempA08 asm("$4");
    register void *tempA09 asm("$4");
    register u8 *overlappingCar asm("$17");
    register void *tempV02 asm("$2");

    car = object;
    asm("" : "=r"(car) : "0"(car) : "memory");
    workspace.nearby = D_8008D0F8;
    asm volatile("lbu\t%0,0xF4(%1)" : "=r"(active) : "r"(car) : "memory");
    asm volatile("addu\t%0,$0,$0\n\taddu\t%1,$0,$0\n\taddu\t%2,$0,$0"
                 : "=r"(nearbyCount), "=r"(blockedLaneMask),
                   "=r"(nearbyLaneMask)
                 :
                 : "memory");
    workspace.useTrackCenter = 0;
    workspace.useSameSegment = 0;
    if (active != 0) {
        if ((*(s16 *)((u8 *)car + 0x1EC)) == 0) {
            if ((*(void (**)(u8 *, s32))(car + 0x354)) == func_80025730373B4) {
                (*(void (**)(u8 *))(car + 0x350))(car);
                return;
            }
            func_8002D16C373B4(car);
            goto block_5;
        }
    block_5:
        if ((*(u8 *)((u8 *)car + 0x268)) != 0) {
            func_8003DBA8373B4(car);
            (*(s16 *)((u8 *)car + 0x288)) = 1;
            return;
        }
        D_800A2F54373B4 = 0;
        if (func_8003E78C373B4(car) & 0xFF) {
            if (D_800A2EAC373B4[0] == 0) {
                D_800A2F54373B4 = 1;
                goto block_10;
            }
            goto block_11;
        }
    block_10:
        if (D_800A2EAC373B4[0] != 0) {
        block_11:
            if ((*(u16 *)((u8 *)car + 0x360)) == 4) {
                tempV0 = func_80045480373B4(car, 0);
                if (tempV0 == 1) {
                    D_800A2F54373B4 = (s32)tempV0;
                }
            }
        }
        /* Route index, target coordinates, and lane permission bits. */
        asm volatile(".set noat\n\t"
                     ".set\tnoreorder\n\t"
                     "lw\t$7,D_800A2F54373B4\n\t"
                     "lh\t$2,0x1E0(%9)\n\t"
                     "sll\t$5,$7,2\n\t"
                     "lui\t$1,%%hi(D_800B1EA8)\n\t"
                     "addu\t$1,$1,$5\n\t"
                     "lw\t$3,%%lo(D_800B1EA8)($1)\n\t"
                     "addiu\t$2,$2,2\n\t"
                     "div\t$0,$2,$3\n\t"
                     "bnez\t$3,1f\n\t"
                     "sll\t$0,$0,0\n\t"
                     "break\t0x1C00\n\t"
                     "1:\n\t"
                     "addiu\t$1,$0,-1\n\t"
                     "bne\t$3,$1,2f\n\t"
                     "lui\t$1,0x8000\n\t"
                     "bne\t$2,$1,2f\n\t"
                     "sll\t$0,$0,0\n\t"
                     "break\t0x1800\n\t"
                     "2:\n\t"
                     "mfhi\t$6\n\t"
                     "lui\t$2,%%hi(D_800AE154)\n\t"
                     "addiu\t$2,$2,%%lo(D_800AE154)\n\t"
                     "addu\t$5,$5,$2\n\t"
                     "lw\t$4,0($5)\n\t"
                     "sll\t$3,$6,1\n\t"
                     "addu\t$3,$3,$6\n\t"
                     "sll\t$3,$3,2\n\t"
                     "addu\t$4,$3,$4\n\t"
                     "lw\t$9,0($4)\n\t"
                     "sll\t$0,$0,0\n\t"
                     "sw\t$9,%0\n\t"
                     "lw\t$9,4($4)\n\t"
                     "sll\t$0,$0,0\n\t"
                     "sw\t$9,%1\n\t"
                     "lh\t$2,8($4)\n\t"
                     "lhu\t$4,10($4)\n\t"
                     "sll\t$2,$2,16\n\t"
                     "sw\t$4,%2\n\t"
                     "sw\t$2,0x84(%9)\n\t"
                     "lw\t$2,0($5)\n\t"
                     "sll\t$0,$0,0\n\t"
                     "addu\t$3,$3,$2\n\t"
                     "lw\t$3,8($3)\n\t"
                     "lw\t$9,%2\n\t"
                     "srl\t$2,$3,30\n\t"
                     "xori\t$2,$2,1\n\t"
                     "andi\t$2,$2,1\n\t"
                     "sb\t$2,%3\n\t"
                     "lbu\t$2,D_800A2F58373B4\n\t"
                     "ori\t$5,$0,0x198\n\t"
                     "andi\t$9,$9,0x3FFF\n\t"
                     "sw\t$9,%2\n\t"
                     "srl\t$3,$3,31\n\t"
                     "xori\t$3,$3,1\n\t"
                     ".set at\n\t"
                     : "=m"(workspace.targetX), "=m"(workspace.targetY),
                       "=m"(workspace.heading), "=m"(workspace.allowRight),
                       "=r"(routeRaceMode), "=r"(routeLeftFlag),
                       "=r"(routeDenominator), "=r"(routeSelection),
                       "=x"(multiplierState)
                     : "r"(car)
                     : "$1", "$4", "$6", "$9", "accum", "memory");
        workspace.allowLeft = routeLeftFlag;
        if (routeRaceMode != 0) {
            if (D_800A2EB0373B4[0] == 1) {
                (*(s32 *)((u8 *)car + 0x84)) = MathMultiplyFixed16373B4(
                    (*(s32 *)((u8 *)car + 0x84)),
                    MathFixedDivide373B4(D_800A2F50373B4 + 0x28,
                                         routeDenominator));
                func_8002A1D0373B4(car);
                func_8002BC88373B4(car);
                tempA02 = (*(s32 *)((u8 *)car + 0x98));
                if ((tempA02 >> 0x10) < (*(s16 *)((u8 *)car + 0x86))) {
                    (*(s32 *)((u8 *)car + 0x84)) = tempA02;
                }
                if (((*(s32 *)((u8 *)car + 0x98)) >> 0x10) <
                    (*(s16 *)((u8 *)car + 0x92))) {
                    (*(s32 *)((u8 *)car + 0x90)) = (*(s32 *)((u8 *)car + 0x98));
                }
            } else {
                varA0 = 2;
                if (D_800A36A4373B4 >= 0x29) {
                    varA1 = 3;
                } else {
                    varA0 = D_800A2F50373B4;
                    varA1 = 0x1A7;
                }
                (*(s32 *)((u8 *)car + 0x84)) = MathMultiplyFixed16373B4(
                    (*(s32 *)((u8 *)car + 0x84)),
                    MathFixedDivide373B4(varA0, varA1));
            }
            playerCar = D_800A35E0373B4[0];
            (*(s32 *)((u8 *)car + 0x22C)) = 0;
            if (car != playerCar) {
                tempV02 = (*(u8 **)((u8 *)car + 0x3E4));
                if (tempV02 != NULL) {
                    tempA03 = (*(u8 **)((u8 *)tempV02 + 8));
                    if ((*(s16 *)((u8 *)car + 0x1E0)) ==
                        (*(s16 *)((u8 *)tempA03 + 0x1E0))) {
                        slowDelta = -0x40000;
                        tempV03 = (*(s32 *)((u8 *)tempA03 + 0x90));
                        tempV03 += slowDelta;
                        (*(s32 *)((u8 *)car + 0x90)) = tempV03;
                        (*(s32 *)((u8 *)car + 0x84)) = tempV03;
                    }
                }
            }
            if ((D_800A2EB0373B4[0] != 1) && (func_800A2CE0373B4[0] == 5)) {
                (*(s32 *)((u8 *)car + 0x84)) =
                    MathMultiplyFixed16373B4((*(s32 *)((u8 *)car + 0x84)),
                                             MathFixedDivide373B4(0x41, 0x64));
            }
        } else {
            if (((*(s16 *)((u8 *)D_800A35E0373B4[0] + 0x1EC)) == 0) &&
                ((*(s16 *)((u8 *)D_800A35E0373B4[0] + 0x284)) >=
                 (*(s16 *)((u8 *)car + 0x284))) &&
                (routeSelection != 1) &&
                (tempV04 = D_800A2F5C373B4 + 1, D_800A2F5C373B4 = tempV04,
                 (tempV04 >= 0))) {
                /* Tire-age penalty and driver aggression. */
                asm volatile(".set noat\n\t"
                             ".set\tnoreorder\n\t"
                             "lh\t$6,0xFA(%3)\n\t"
                             "sll\t$0,$0,0\n\t"
                             "slti\t$2,$6,16\n\t"
                             "beqz\t$2,3f\n\t"
                             "sll\t$2,$6,2\n\t"
                             "lw\t$3,D_800A2F50373B4\n\t"
                             "lui\t$4,%%hi(D_800A3320)\n\t"
                             "lbu\t$4,%%lo(D_800A3320)($4)\n\t"
                             "j\t4f\n\t"
                             "sll\t$3,$3,3\n\t"
                             "3:\n\t"
                             "lw\t$3,D_800A2F50373B4\n\t"
                             "sll\t$2,$6,1\n\t"
                             "addu\t$2,$2,$6\n\t"
                             "lui\t$4,%%hi(D_800A3320)\n\t"
                             "lbu\t$4,%%lo(D_800A3320)($4)\n\t"
                             "sll\t$2,$2,2\n\t"
                             "sll\t$3,$3,3\n\t"
                             "4:\n\t"
                             "subu\t$3,$3,$2\n\t"
                             ".set at\n\t"
                             : "=r"(varV0), "=r"(varV1), "=r"(varA0)
                             : "r"(car)
                             : "$6", "memory");
                varV0 = 0x96 - varA0;
                varV0 <<= 1;
                asm("addu\t%0,%1,%2" : "=r"(varV0) : "r"(varV1), "r"(varV0));
                asm volatile("" : : "r"(varV0));
                speedResult = MathMultiplyFixed16373B4(
                    *(s32 *)(car + 0x84),
                    MathFixedDivide373B4(varV0, routeDenominator << 3));
                counterScale = D_800A2E94373B4[0];
                *(s32 *)(car + 0x84) = speedResult;
                *(s32 *)(car + 0x22C) = 0x1E0000;
                D_800A2F5C373B4 = counterScale * 0x190;
            } else {
                paceTimer = D_800A2F5C373B4;
                if (paceTimer > 0) {
                    timerBase = D_800A2F50373B4;
                    tireAge2 = *(s16 *)(car + 0xFA);
                    varA0 = D_800A3320373B4[0];
                    routeDenominator <<= 3;
                    paceTimer -= 1;
                    D_800A2F5C373B4 = paceTimer;
                    asm volatile("" : : "r"(paceTimer));
                    varV0 = 0x66;
                    timerBase <<= 3;
                    tireAge2 <<= 2;
                    timerBase -= tireAge2;
                    varV0 -= varA0;
                    varA0 = varV0 * 3;
                    *(s32 *)(car + 0x84) = MathMultiplyFixed16373B4(
                        *(s32 *)(car + 0x84),
                        MathFixedDivide373B4(timerBase + varA0,
                                             routeDenominator));
                    varV02 = 0x140000;
                } else {
                    if (paceTimer >= 0) {
                        D_800A2F5C373B4 = -(D_800A2E94373B4[0] * 0x258);
                    }
                    tempV13 = (*(s8 *)((u8 *)D_800A3878373B4[0] + 0x204));
                    if (tempV13 >= 0x15) {
                        varV03 = (*(s16 *)((u8 *)car + 0xFA)) * 0x10;
                    } else {
                        asm("slti\t%0,%1,0xD"
                            : "=r"(standingTest)
                            : "r"(tempV13));
                        if (standingTest == 0) {
                            varV03 = (*(s16 *)((u8 *)car + 0xFA)) * 0xA;
                        } else {
                            varV03 = (*(s16 *)((u8 *)car + 0xFA)) * 4;
                        }
                    }
                    (*(s32 *)((u8 *)car + 0x84)) = MathMultiplyFixed16373B4(
                        (*(s32 *)((u8 *)car + 0x84)),
                        MathFixedDivide373B4((D_800A2F50373B4 * 8) - varV03,
                                             routeDenominator << 3));
                    varV02 = 0xA0000;
                }
                (*(s32 *)((u8 *)car + 0x22C)) = varV02;
            }
            if (D_800A2F5C373B4 < -(D_800A2E94373B4[0] * 0xC8)) {
                (*(u8 *)((u8 *)car + 0x3FC)) = 0U;
                tempV04 = D_800A2F5C373B4;
                (*(s32 *)((u8 *)car + 0x22C)) = 0;
                tempV04 += 1;
                D_800A2F5C373B4 = tempV04;
                (*(s32 *)((u8 *)car + 0x84)) =
                    MathMultiplyFixed16373B4((*(s32 *)((u8 *)car + 0x84)),
                                             MathFixedDivide373B4(0x60, 0x64));
            }
            if ((*(u8 *)((u8 *)car + 0x3FC)) != 0) {
                if (D_800A2EA4373B4[0] == 0) {
                    (*(s32 *)((u8 *)car + 0x84)) =
                        (s32)((*(s32 *)((u8 *)car + 0x84)) +
                              (*(s32 *)((u8 *)D_800A3554373B4[0] + 0x22C)));
                } else {
                    (*(s32 *)((u8 *)car + 0x84)) =
                        (s32)((*(s32 *)((u8 *)car + 0x84)) + 0xC0000);
                }
                (*(u8 *)((u8 *)car + 0x3FC)) =
                    (u8)((*(u8 *)((u8 *)car + 0x3FC)) - 1);
            }
        }
        (*(s32 *)((u8 *)car + 0x84)) = MathMultiplyFixed16373B4(
            (*(s32 *)((u8 *)car + 0x84)),
            MathFixedDivide373B4(D_800A2E4C373B4[0], 0x64));
        if ((*(u16 *)((u8 *)car + 0x3A4)) & 0x1000) {
            (*(s32 *)((u8 *)car + 0x84)) = MathMultiplyFixed16373B4(
                (*(s32 *)((u8 *)car + 0x84)), MathFixedDivide373B4(1, 2));
        }
        if ((*(s32 *)((u8 *)car + 0x84)) <= 0x31FFFF) {
            (*(s32 *)((u8 *)car + 0x84)) = 0x320000;
        }
        if (D_800A372C373B4[0] != 0) {
            D_800A2F5C373B4 = -(D_800A2E94373B4[0] * 0x190);
            if (D_800A2F54373B4 == 0) {
                asm("ori\t%0,$0,1" : "=r"(trackCenterFlag));
                workspace.useTrackCenter = trackCenterFlag;
            }
            if (*(u16 *)(car + 0x3A4) & 0xF) {
                *(s32 *)(car + 0x84) = 0;
            } else {
                paceMatch = 0;
                if (car == D_800A3A64373B4[0]) {
                    *(s32 *)(car + 0x84) = 0xAC0000;
                } else {
                    paceLeader = *(u8 **)(*(u8 **)(car + 0x3F0) + 8);
                    asm("lh\t%0,0x288(%1)"
                        : "=r"(varV04)
                        : "r"(paceLeader)
                        : "$20");
                    followAllowed = 0;
                    goto paceLevelCheck;
                paceNextCar:
                    paceLeader = *(u8 **)(*(u8 **)(paceLeader + 0x3F0) + 8);
                    varV04 = *(s16 *)(paceLeader + 0x288);
                paceLevelCheck:
                    if (varV04 != 0)
                        goto paceNextCar;
                    if (*(u16 *)(paceLeader + 0x3A4) & 0xF)
                        goto paceNextCar;
                    if (*(void (**)(void))(paceLeader + 0x354) !=
                        func_80025594373B4)
                        goto paceNextCar;
                    tempS0 = func_8003702C373B4(paceLeader, car);
                    paceGap = tempS0;
                    paceCarGap = func_8003702C373B4(D_800A3A64373B4[0], car);
                    asm volatile("" : : "r"(paceGap));
                    /* Select the leader or pace car and retain their gap.
                     * The C distance calls preserve both saved flags. */
                    asm volatile(".set noat\n\t"
                                 ".set\tnoreorder\n\t"
                                 "andi\t$2,%6,0xFFFF\n\t"
                                 "sltiu\t$2,$2,11\n\t"
                                 "beqz\t$2,10f\n\t"
                                 "sll\t$2,%7,16\n\t"
                                 "lb\t$4,0x408(%5)\n\t"
                                 "lb\t$5,0x408(%4)\n\t"
                                 "sll\t$0,$0,0\n\t"
                                 "slt\t$2,$4,$5\n\t"
                                 "beqz\t$2,10f\n\t"
                                 "sll\t$2,%7,16\n\t"
                                 "lb\t$3,0x3FE(%5)\n\t"
                                 "lb\t$2,0x3FE(%4)\n\t"
                                 "sll\t$0,$0,0\n\t"
                                 "bne\t$3,$2,10f\n\t"
                                 "sll\t$2,%7,16\n\t"
                                 "addiu\t$2,%6,-1\n\t"
                                 "andi\t$2,$2,0xFFFF\n\t"
                                 "sltiu\t$2,$2,2\n\t"
                                 "beqz\t$2,11f\n\t"
                                 "addiu\t$2,$4,1\n\t"
                                 "bne\t$5,$2,11f\n\t"
                                 "sll\t$0,$0,0\n\t"
                                 "ori\t%2,$0,1\n\t"
                                 "11:\n\t"
                                 "lw\t$9,0x84(%5)\n\t"
                                 "ori\t%1,$0,1\n\t"
                                 "j\t14f\n\t"
                                 "sw\t$9,%0\n\t"
                                 "10:\n\t"
                                 "sra\t$3,$2,16\n\t"
                                 "bltz\t$3,.LpaceChoice373B4\n\t"
                                 "andi\t$2,%1,0xFF\n\t"
                                 "lb\t$4,0x408(%4)\n\t"
                                 "sll\t$0,$0,0\n\t"
                                 "addiu\t$2,$4,10\n\t"
                                 "slt\t$2,$2,$3\n\t"
                                 "bnez\t$2,.LpaceChoice373B4\n\t"
                                 "andi\t$2,%1,0xFF\n\t"
                                 "lui\t$2,%%hi(D_800A37C0)\n\t"
                                 "lw\t$2,%%lo(D_800A37C0)($2)\n\t"
                                 "subu\t$3,%7,$4\n\t"
                                 "bne\t%4,$2,12f\n\t"
                                 "addu\t%3,$3,$0\n\t"
                                 "addiu\t$2,$3,-1\n\t"
                                 "andi\t$2,$2,0xFFFF\n\t"
                                 "sltiu\t$2,$2,2\n\t"
                                 "beqz\t$2,13f\n\t"
                                 "lui\t$9,0xAC\n\t"
                                 "ori\t%2,$0,1\n\t"
                                 "12:\n\t"
                                 "lui\t$9,0xAC\n\t"
                                 "13:\n\t"
                                 "sw\t$9,%0\n\t"
                                 "ori\t%1,$0,1\n\t"
                                 "14:\n\t"
                                 ".set at\n\t"
                                 ".set\treorder\n\t"
                                 : "=m"(workspace.paceSpeed), "=r"(paceMatch),
                                   "=r"(followAllowed), "=r"(paceGap)
                                 : "r"(car), "r"(paceLeader), "r"(tempS0),
                                   "r"(paceCarGap), "1"(paceMatch),
                                   "2"(followAllowed)
                                 : "$2", "$3", "$4", "$5", "$9", "memory");
                    asm("andi %0,%1,0xFF\n.LpaceChoice373B4:"
                        : "=r"(varV06)
                        : "r"(paceMatch));
                    if (varV06 != 0) {
                        asm volatile("" : : : "memory");
                        if (D_800A3670373B4[0] != 0) {
                            asm volatile("" : : : "memory");
                            *(u8 *)(car + 0x401) = followAllowed;
                        } else {
                            peerFollowFlag = *(u8 *)(paceLeader + 0x401);
                            varV12 = 0;
                            if (peerFollowFlag != 0) {
                                varV12 = followAllowed;
                                asm("");
                            }
                            *(u8 *)(car + 0x401) = varV12;
                        }
                        asm("sll\t$2,%1,16\n\tsra\t%0,$2,16"
                            : "=r"(paceDistance)
                            : "r"(paceGap)
                            : "$2");
                        if (paceDistance >= 2) {
                            varV0 = MathFixedDivide373B4(paceDistance - 1, 9);
                            varA0 = *(s32 *)(car + 0x84);
                            paceBase = workspace.paceSpeed;
                            varA1 = varV0;
                            varV0 = MathMultiplyFixed16373B4(varA0 - paceBase,
                                                             varA1);
                            paceBase = workspace.paceSpeed;
                            varV0 = paceBase + varV0;
                            *(s32 *)(car + 0x84) = varV0;
                        } else {
                            speedResult = MathMultiplyFixed16373B4(
                                workspace.paceSpeed,
                                MathFixedDivide373B4(9, 10));
                            varA02 = 5;
                            *(s32 *)(car + 0x84) = speedResult;
                            if (paceDistance != 0)
                                varA02 = 9;
                            *(s32 *)(car + 0x90) = MathMultiplyFixed16373B4(
                                *(s32 *)(paceLeader + 0x90),
                                MathFixedDivide373B4(varA02, 10));
                        }
                    }
                }
            }
        }
        if ((D_800A2EDC373B4[0] != 0) &&
            (tempA13 = (*(u16 *)((u8 *)car + 0x3A4)), ((tempA13 & 0xF) != 0))) {
            tempA06 = (*(u8 *)((u8 *)car + 0x3B7));
            if (tempA06 != 0) {
                if (((*(void (**)(u8 *, s32))(car + 0x354)) ==
                     func_80025594373B4) &&
                    (tempA06 == 0x64) && ((*(s16 *)((u8 *)car + 0x1EC)) != 0)) {
                    if (tempA13 & 3) {
                        (*(s16 *)((u8 *)car + 0x102)) = 0;
                    } else {
                        (*(s16 *)((u8 *)car + 0x102)) = 1;
                    }
                    asm volatile("" : : "r"(tempA13));
                    ObjectSetCallbackIfAllowed373B4(car, func_8003AA20373B4);
                }
                (*(u8 *)((u8 *)car + 0x3B7)) =
                    (u8)((*(u8 *)((u8 *)car + 0x3B7)) - 1);
                goto block_120;
            }
            if (D_800A2EE0373B4[0] != 0) {
                func_80044114373B4(car);
                goto block_120;
            }
            if ((D_800A3071373B4[0] != 0) && (D_800A3910373B4[0] == 0) &&
                (D_800A3960373B4[0] == NULL) && (D_800A2EB0373B4[0] == 0)) {
                func_800488A4373B4(car);
                D_800A3764373B4[0] = 1;
                goto block_120;
            }
            if (car != D_800A3728373B4[0]) {
                if (!(func_80037204373B4(car) & 0xFF)) {
                    D_800A3564373B4[0] = 1;
                    goto block_120;
                }
            } else {
            block_120:
                (*(s32 *)((u8 *)car + 0x84)) = MathMultiplyFixed16373B4(
                    (*(s32 *)((u8 *)car + 0x84)),
                    MathFixedDivide373B4((s32)(*(u8 *)((u8 *)car + 0x3B7)),
                                         0x64));
                goto block_121;
            }
        } else {
        block_121:
            if ((D_800A2E90373B4[0] != 0) && (D_800A2EB0373B4[0] != 1)) {
                if (D_800A2F54373B4 != 1) {
                    asm("lbu %0,%1"
                        : "=r"(trackCenterFlag)
                        : "m"(workspace.allowRight));
                    asm("addu %0,%1,$0" : "=r"(varV07) : "r"(trackCenterFlag));
                    if (varV07 == 0) {
                        blockedLaneMask |= 1;
                    }
                    asm("lbu %0,%1"
                        : "=r"(trackCenterFlag)
                        : "m"(workspace.allowLeft)
                        : "$17");
                    asm("addu %0,%1,$0" : "=r"(varV07) : "r"(trackCenterFlag));
                    forwardNeighbor = car;
                    if (varV07 == 0) {
                        blockedLaneMask |= 4;
                    }
                loop_128:
                    /* Keep the capped link walk and filter order. */
                    asm volatile(".set\tnoreorder\n"
                                 ".LnearbyForward80037EF4:\n"
                                 "lw         $v0, 0x3F0(%0)\n"
                                 "nop\n"
                                 "lw         %0, 0x8($v0)\n"
                                 "nop\n"
                                 "lbu        $v0, 0x268(%0)\n"
                                 "nop\n"
                                 "beqz       $v0, .LnearbyForward80037F44\n"
                                 "addu      %1, $zero, $zero\n"
                                 "addu       $v0, %1, $zero\n"
                                 ".LnearbyForward80037F18:\n"
                                 "slti       $v0, $v0, 0x3\n"
                                 "beqz       $v0, .LnearbyForward80037F44\n"
                                 "addiu     %1, %1, 0x1\n"
                                 "lw         $v0, 0x3F0(%0)\n"
                                 "nop\n"
                                 "lw         %0, 0x8($v0)\n"
                                 "nop\n"
                                 "lbu        $v0, 0x268(%0)\n"
                                 "nop\n"
                                 "bnez       $v0, .LnearbyForward80037F18\n"
                                 "addu      $v0, %1, $zero\n"
                                 ".LnearbyForward80037F44:\n"
                                 ".set\tnoreorder\n"
                                 : "=r"(forwardNeighbor), "=r"(varV13)
                                 : "0"(forwardNeighbor)
                                 : "$2", "memory");
                    if (func_8003702C373B4(forwardNeighbor, car) < 0) {
                        varA12 = -func_8003702C373B4(forwardNeighbor, car);
                    } else {
                        varA12 = func_8003702C373B4(forwardNeighbor, car);
                    }
                    asm("slti %0,%1,2" : "=r"(varV07) : "r"(varA12));
                    if (varV07 != 0) {
                        tempV16 = 1;
                        asm("lb %0,0x206(%1)"
                            : "=r"(varV07)
                            : "r"(forwardNeighbor)
                            : "memory");
                        varV07 += 1;
                        asm("sllv %0,%0,%2"
                            : "=r"(tempV16)
                            : "0"(tempV16), "r"(varV07));
                        blockedLaneMask |= tempV16;
                        nearbyLaneMask |= tempV16;
                        if (nearbyCount < 6) {
                            workspace.nearby.cars[nearbyCount] =
                                forwardNeighbor;
                            nearbyCount += 1;
                            goto loop_128;
                        }
                    }
                    backwardNeighbor = car;
                loop_139:
                    /* Keep the capped link walk and filter order. */
                    asm volatile(".set\tnoreorder\n"
                                 ".LnearbyBackward80037FBC:\n"
                                 "lw         $v0, 0x3F4(%0)\n"
                                 "nop\n"
                                 "lw         %0, 0x8($v0)\n"
                                 "nop\n"
                                 "lbu        $v0, 0x268(%0)\n"
                                 "j          .LnearbyBackward80037FF8\n"
                                 "addu      %1, $zero, $zero\n"
                                 ".LnearbyBackward80037FD8:\n"
                                 "slti       $v0, $v0, 0x2\n"
                                 "beqz       $v0, .LnearbyBackward80038014\n"
                                 "addiu     %1, %1, 0x1\n"
                                 "lw         $v0, 0x3F4(%0)\n"
                                 "nop\n"
                                 "lw         %0, 0x8($v0)\n"
                                 "nop\n"
                                 "lbu        $v0, 0x268(%0)\n"
                                 ".LnearbyBackward80037FF8:\n"
                                 "nop\n"
                                 "bnez       $v0, .LnearbyBackward80037FD8\n"
                                 "addu      $v0, %1, $zero\n"
                                 "lh         $v0, 0x1EC(%0)\n"
                                 "nop\n"
                                 "beqz       $v0, .LnearbyBackward80037FD8\n"
                                 "addu      $v0, %1, $zero\n"
                                 ".LnearbyBackward80038014:\n"
                                 ".set\tnoreorder\n"
                                 : "=r"(backwardNeighbor), "=r"(varV14)
                                 : "0"(backwardNeighbor)
                                 : "$2", "memory");
                    if (func_8003702C373B4(backwardNeighbor, car) < 0) {
                        varA13 = -func_8003702C373B4(backwardNeighbor, car);
                    } else {
                        varA13 = func_8003702C373B4(backwardNeighbor, car);
                    }
                    asm("slti %0,%1,2" : "=r"(varV08) : "r"(varA13));
                    if (varV08 != 0) {
                        tempV17 = 1;
                        asm("lb %0,0x206(%1)"
                            : "=r"(varV08)
                            : "r"(backwardNeighbor)
                            : "memory");
                        varV08 += 1;
                        asm("sllv %0,%0,%2"
                            : "=r"(tempV17)
                            : "0"(tempV17), "r"(varV08));
                        blockedLaneMask |= tempV17;
                        nearbyLaneMask |= tempV17;
                        if (nearbyCount < 6) {
                            workspace.nearby.cars[nearbyCount] =
                                backwardNeighbor;
                            nearbyCount += 1;
                            goto loop_139;
                        }
                    }

                    if ((blockedLaneMask & 2) ||
                        ((desiredLane = 0, (D_800A2F58373B4 != 0)) &&
                         (D_800A3598373B4[0] == 0))) {
                        tempA07 = (*(s8 *)(car + 0x206));
                        varV09 = 1;
                        tempV18 = tempA07 + 1;
                        asm("sllv %0,%0,%2"
                            : "=r"(varV09)
                            : "0"(varV09), "r"(tempV18));
                        varV09 = blockedLaneMask & varV09;
                        desiredLane = tempA07;
                        if (varV09 != 0) {
                            /* Skip up to three unavailable cars ahead. */
                            asm volatile(".set\tnoreorder\n\t"
                                         "lw\t$2,0x3F0(%2)\n\t"
                                         "sll\t$0,$0,0\n\t"
                                         "lw\t%0,8($2)\n\t"
                                         "sll\t$0,$0,0\n\t"
                                         "lbu\t$2,0x268(%0)\n\t"
                                         "j\t32f\n\t"
                                         "addu\t%1,$0,$0\n\t"
                                         "31:\n\t"
                                         "slti\t$2,$2,3\n\t"
                                         "beqz\t$2,33f\n\t"
                                         "addiu\t%1,%1,1\n\t"
                                         "lw\t$2,0x3F0(%0)\n\t"
                                         "sll\t$0,$0,0\n\t"
                                         "lw\t%0,8($2)\n\t"
                                         "sll\t$0,$0,0\n\t"
                                         "lbu\t$2,0x268(%0)\n\t"
                                         "32:\n\t"
                                         "sll\t$0,$0,0\n\t"
                                         "bnez\t$2,31b\n\t"
                                         "addu\t$2,%1,$0\n\t"
                                         "lh\t$2,0x1EC(%0)\n\t"
                                         "sll\t$0,$0,0\n\t"
                                         "beqz\t$2,31b\n\t"
                                         "addu\t$2,%1,$0\n\t"
                                         "33:\n\t"
                                         ".set\treorder\n\t"
                                         : "=r"(blockingCar), "=r"(varV15)
                                         : "r"(car)
                                         : "$2", "memory");
                            asm("lh $2,0x92(%1)\n\tlh $3,0x92(%2)\n\tsll $0,$0,0\n\tsubu %0,$2,$3"
                                : "=r"(tempS0)
                                : "r"(car), "r"(blockingCar)
                                : "$2", "$3", "memory");
                            if (tempS0 >= 0x10) {
                                if (func_8003702C373B4(blockingCar, car) < 0) {
                                    varA14 =
                                        -func_8003702C373B4(blockingCar, car);
                                } else {
                                    varA14 =
                                        func_8003702C373B4(blockingCar, car);
                                }
                                /* Change the lane only when its mask permits it.
                                     * Cars already in an outer lane follow a slower leader. */
                                asm volatile(".set\tnoreorder\n\t"
                                             "slti\t$2,%6,2\n\t"
                                             "beqz\t$2,38f\n\t"
                                             "ori\t$2,$0,7\n\t"
                                             "beq\t%3,$2,36f\n\t"
                                             "sll\t$0,$0,0\n\t"
                                             "lb\t$3,0x206(%1)\n\t"
                                             "sll\t$0,$0,0\n\t"
                                             "beqz\t$3,35f\n\t"
                                             "sll\t$0,$0,0\n\t"
                                             "bgtz\t$3,34f\n\t"
                                             "ori\t$2,$0,1\n\t"
                                             "addiu\t$2,$0,-1\n\t"
                                             "beq\t$3,$2,37f\n\t"
                                             "slti\t$2,%4,100\n\t"
                                             "j\t38f\n\t"
                                             "sll\t$0,$0,0\n\t"
                                             "34:\n\t"
                                             "beq\t$3,$2,37f\n\t"
                                             "slti\t$2,%4,100\n\t"
                                             "j\t38f\n\t"
                                             "sll\t$0,$0,0\n\t"
                                             "35:\n\t"
                                             "andi\t$2,%3,1\n\t"
                                             "bnez\t$2,38f\n\t"
                                             "ori\t%0,$0,1\n\t"
                                             "j\t38f\n\t"
                                             "addiu\t%0,$0,-1\n\t"
                                             "36:\n\t"
                                             "slti\t$2,%4,100\n\t"
                                             "37:\n\t"
                                             "beqz\t$2,38f\n\t"
                                             "lui\t$3,0xFFFF\n\t"
                                             "lw\t$2,0x90(%2)\n\t"
                                             "sll\t$0,$0,0\n\t"
                                             "addu\t$2,$2,$3\n\t"
                                             "sw\t$2,0x90(%1)\n\t"
                                             "38:\n\t"
                                             ".set\treorder\n\t"
                                             : "=r"(desiredLane)
                                             : "r"(car), "r"(blockingCar),
                                               "r"(blockedLaneMask),
                                               "r"(tempS0), "0"(desiredLane),
                                               "r"(varA14)
                                             : "$2", "$3", "memory");
                            }
                        }
                    }
                    tempA08 = (*(u8 **)((u8 *)car + 0x3F4));
                    if (tempA08 != NULL) {
                        followingCar = (*(u8 **)((u8 *)tempA08 + 8));
                        followAllowed = 1;
                        if ((*(s16 *)((u8 *)followingCar + 0x1EC)) == 0) {
                            if (func_8003702C373B4(followingCar, car) < 0) {
                                varA15 = -func_8003702C373B4(followingCar, car);
                            } else {
                                varA15 = func_8003702C373B4(followingCar, car);
                            }
                            asm("addiu %0,%1,-2\n\tsltiu %0,%0,4"
                                : "=r"(varV011)
                                : "r"(varA15));
                            if (varV011 == 0)
                                goto pressureNotAllowed;
                            asm("lw %0,0x90(%2)\n\tlw %1,0x90(%3)"
                                : "=r"(tempV112), "=r"(varV011)
                                : "r"(followingCar), "r"(car)
                                : "memory");
                            if (varV011 >= tempV112)
                                goto pressureNotAllowed;
                            tempA09 = *(u8 **)(car + 0x3F0);
                            if (tempA09 != NULL) {
                                aheadOfFollowingCar =
                                    (*(u8 **)((u8 *)tempA09 + 8));
                                if (func_8003702C373B4(aheadOfFollowingCar,
                                                       car) < 0) {
                                    varA16 = -func_8003702C373B4(
                                        aheadOfFollowingCar, car);
                                } else {
                                    varA16 = func_8003702C373B4(
                                        aheadOfFollowingCar, car);
                                }
                                asm("slti %0,%1,2"
                                    : "=r"(varV011)
                                    : "r"(varA16));
                                if (varV011 == 0)
                                    goto pressureAllowed;
                            }
                        pressureNotAllowed:
                            followAllowed = 0;
                        pressureAllowed:
                            varV011 = followAllowed & 0xFF;
                            if ((varV011 != 0) &&
                                ((*(s32 *)((u8 *)car + 0x90)) > 0x01720000)) {
                                pressureTimerValue = *(s8 *)(car + 0x205);
                                if (pressureTimerValue != 0)
                                    goto pressureTimerCheck;
                                {
                                    /* Move one lane toward the faster following car,
                                     * then clamp to either outer lane. */
                                    asm volatile(".set\tnoreorder\n\t"
                                                 "lb\t$3,0x203(%1)\n\t"
                                                 "lb\t$4,0x203(%2)\n\t"
                                                 "sll\t$0,$0,0\n\t"
                                                 "slt\t$2,$3,$4\n\t"
                                                 "beqz\t$2,41f\n\t"
                                                 "slt\t$2,$4,$3\n\t"
                                                 "lbu\t$2,0x206(%1)\n\t"
                                                 "sll\t$0,$0,0\n\t"
                                                 "addiu\t$2,$2,-1\n\t"
                                                 "sb\t$2,0x206(%1)\n\t"
                                                 "sll\t$2,$2,24\n\t"
                                                 "sra\t$2,$2,24\n\t"
                                                 "slti\t$2,$2,-1\n\t"
                                                 "beqz\t$2,42f\n\t"
                                                 "addiu\t$2,$0,-1\n\t"
                                                 "j\t42f\n\t"
                                                 "sb\t$2,0x206(%1)\n\t"
                                                 "41:\n\t"
                                                 "beqz\t$2,42f\n\t"
                                                 "sll\t$0,$0,0\n\t"
                                                 "lbu\t$2,0x206(%1)\n\t"
                                                 "sll\t$0,$0,0\n\t"
                                                 "addiu\t$2,$2,1\n\t"
                                                 "sb\t$2,0x206(%1)\n\t"
                                                 "sll\t$2,$2,24\n\t"
                                                 "sra\t$2,$2,24\n\t"
                                                 "slti\t$2,$2,2\n\t"
                                                 "bnez\t$2,42f\n\t"
                                                 "ori\t$2,$0,1\n\t"
                                                 "sb\t$2,0x206(%1)\n\t"
                                                 "42:\n\t"
                                                 "lhu\t$2,0x248(%1)\n\t"
                                                 "lb\t%0,0x206(%1)\n\t"
                                                 "sb\t$2,0x205(%1)\n\t"
                                                 ".set\treorder\n\t"
                                                 : "=r"(desiredLane)
                                                 : "r"(car), "r"(followingCar)
                                                 : "$2", "$3", "$4", "memory");
                                }
                            }
                            asm volatile("" : : "r"(followAllowed));
                            pressureTimerValue = *(s8 *)(car + 0x205);
                        pressureTimerCheck:
                            tempV19 = pressureTimerValue;
                            if (pressureTimerValue > 0) {
                                tempV018 = tempV19 - 1;
                                *(s8 *)(car + 0x205) = tempV018;
                            }
                        }
                    }
                    if ((*(u16 *)((u8 *)car + 0x3A4)) & 0x1000) {
                        desiredLane = 2;
                        if (D_800A2F84373B4[0] != 0) {
                            desiredLane = -2;
                        }
                        asm("ori %0,$zero,1" : "=r"(middleOne));
                        workspace.useTrackCenter = middleOne;
                    } else {
                        asm volatile(
                            "lui %0,%%hi(D_800A3960)\n\tlw %0,%%lo(D_800A3960)(%0)"
                            : "=r"(middleOther)
                            :
                            : "memory");
                        if ((middleOther != NULL) &&
                            (*(s16 *)(middleOther + 0x1EC) != 0)) {
                            if (func_8003702C373B4(middleOther, car) < 0) {
                                asm volatile(
                                    "lui %0,%%hi(D_800A3960)\n\tlw %0,%%lo(D_800A3960)(%0)"
                                    : "=r"(middleOther)
                                    :
                                    : "memory");
                                if (-func_8003702C373B4(middleOther, car) < 5) {
                                    goto block_212;
                                }
                            } else {
                                asm volatile(
                                    "lui %0,%%hi(D_800A3960)\n\tlw %0,%%lo(D_800A3960)(%0)"
                                    : "=r"(middleOther)
                                    :
                                    : "memory");
                                if (func_8003702C373B4(middleOther, car) < 5) {
                                block_212:
                                    if (desiredLane == 0) {
                                        if (D_800A2F84373B4[0] != 0) {
                                            asm volatile(
                                                "lbu $9,%1\n\tnop\n\taddu %0,$9,$zero"
                                                : "=r"(middleFlag)
                                                : "m"(workspace.allowRight)
                                                : "$9", "memory");
                                            if (middleFlag == 0) {
                                                desiredLane = 1;
                                            }
                                        } else {
                                            asm volatile(
                                                "lbu $9,%1\n\tnop\n\taddu %0,$9,$zero"
                                                : "=r"(middleFlag)
                                                : "m"(workspace.allowLeft)
                                                : "$9", "memory");
                                            if (middleFlag == 0) {
                                                desiredLane = -1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (D_800A372C373B4[0] != 0) {
                        tempV09 = (*(s8 *)((u8 *)D_800A3728373B4[0] + 0x203));
                        if (tempV09 >= 0) {
                            if (tempV09 < 4) {
                                goto block_223;
                            }
                            goto block_229;
                        }
                        if (-tempV09 < 4) {
                        block_223:
                            asm volatile(
                                "lui %0,%%hi(D_800A3728)\n\tlw %0,%%lo(D_800A3728)(%0)"
                                : "=r"(middleOther)
                                :
                                : "memory");
                            func_8003702C373B4(middleOther, car);
                            asm volatile(
                                "lui %0,%%hi(D_800A3728)\n\tlw %0,%%lo(D_800A3728)(%0)"
                                : "=r"(middleOther)
                                :
                                : "memory");
                            if (func_8003702C373B4(middleOther, car) < 5) {
                                tempV010 =
                                    (*(s8 *)((u8 *)D_800A3728373B4[0] + 0x203));
                                if (tempV010 != 0) {
                                    desiredLane = -1;
                                    if (tempV010 > 0) {
                                        desiredLane = 1;
                                    }
                                } else {
                                    desiredLane = (*(s8 *)((u8 *)car + 0x3FE));
                                }
                                asm("ori %0,$zero,1" : "=r"(middleOne));
                                workspace.useSameSegment = middleOne;
                            } else {
                                goto block_229;
                            }
                        } else {
                        block_229:
                            if ((*(u8 *)((u8 *)car + 0x401)) != 0) {
                                tempV011 = (*(s8 *)((u8 *)car + 0x400));
                                varV16 = tempV011;
                                if (tempV011 == 0) {
                                    varV16 = 0;
                                    if ((*(s8 *)((u8 *)car + 0x3FF)) == 0) {
                                        varV16 =
                                            (u8)(*(s8 *)((u8 *)car + 0x3FE));
                                    }
                                    asm volatile(
                                        "lb %0,0x409(%2)\n\tori %1,$zero,10"
                                        : "=r"(varV012), "=r"(middleRandomLimit)
                                        : "r"(car)
                                        : "memory");
                                    (*(s8 *)((u8 *)car + 0x3FF)) = (s8)varV16;
                                    tempS03 = varV012 - 5;
                                    if (RandomScaledGet373B4(
                                            middleRandomLimit) < 0) {
                                        varV012 =
                                            tempS03 - RandomScaledGet373B4(0xA);
                                    } else {
                                        varV012 =
                                            tempS03 + RandomScaledGet373B4(0xA);
                                    }
                                } else {
                                    varV012 = varV16 - 1;
                                }
                                (*(s8 *)((u8 *)car + 0x400)) = varV012;
                            }
                            desiredLane = (*(s8 *)((u8 *)car + 0x3FF));
                        }
                    }
                    asm volatile(
                        ".set\tnoreorder\n"
                        ".set\tnoat\n"
                        ".LmiddleCenter800385C4:\n"
                        "lbu        $v0, %5\n"
                        "nop\n"
                        "beqz       $v0, .LmiddleCenter80038668\n"
                        "nop\n"
                        "lbu        $v0, %6\n"
                        "ori        $t1, $zero, 0x1\n"
                        "sb         $t1, %2\n"
                        "sb         $t1, %3\n"
                        "lh         $a0, 0x1E0(%4)\n"
                        "lui        $v1, %%hi(D_800BE974)\n"
                        "lw         $v1, %%lo(D_800BE974)($v1)\n"
                        "bnez       $v0, .LmiddleCenter8003860C\n"
                        "addiu     $v0, $a0, 0x2\n"
                        "lh         $v0, 0x1EC(%4)\n"
                        "nop\n"
                        "bnez       $v0, .LmiddleCenter8003860C\n"
                        "addiu     $v0, $a0, 0x2\n"
                        "addiu      $v0, $a0, 0x3\n"
                        ".LmiddleCenter8003860C:\n"
                        "div        $0,$v0,$v1\n"
                        "bnez       $v1, .LmiddleCenter8003861C\n"
                        "nop\n"
                        "break      7168\n"
                        ".LmiddleCenter8003861C:\n"
                        "addiu      $at, $zero, -0x1\n"
                        "bne        $v1, $at, .LmiddleCenter80038634\n"
                        "lui       $at, (0x80000000 >> 16)\n"
                        "bne        $v0, $at, .LmiddleCenter80038634\n"
                        "nop\n"
                        "break      6144\n"
                        ".LmiddleCenter80038634:\n"
                        "mfhi       $a2\n"
                        "lui        $v1, %%hi(D_800BE980)\n"
                        "lw         $v1, %%lo(D_800BE980)($v1)\n"
                        "sll        $v0, $a2, 3\n"
                        "addu       $v0, $v0, $a2\n"
                        "sll        $v0, $v0, 4\n"
                        "addu       $v0, $v0, $v1\n"
                        "lw         $t1, 0x14($v0)\n"
                        "nop\n"
                        "sw         $t1, %0\n"
                        "lw         $v0, 0x18($v0)\n"
                        "nop\n"
                        "sw         $v0, %1\n"
                        ".LmiddleCenter80038668:\n"
                        ".set\tat\n"
                        ".set\tnoreorder\n"
                        : "=m"(workspace.targetX), "=m"(workspace.targetY),
                          "=m"(workspace.allowLeft), "=m"(workspace.allowRight)
                        : "r"(car), "m"(workspace.useTrackCenter),
                          "m"(workspace.useSameSegment), "m"(workspace)
                        : "$1", "$2", "$3", "$4", "$6", "$9", "hi", "lo",
                          "memory");
                    asm volatile(".set\tnoreorder\n"
                                 ".LmiddlePropagate80038668:\n"
                                 "beqz       %0, .LmiddlePropagate800386B0\n"
                                 "nop\n"
                                 "bgez       %0, .LmiddlePropagate8003868C\n"
                                 "nop\n"
                                 "lbu        $t1, %5\n"
                                 "nop\n"
                                 "addu       $v0, $t1, $zero\n"
                                 "beqz       $v0, .LmiddlePropagate800386B0\n"
                                 "nop\n"
                                 ".LmiddlePropagate8003868C:\n"
                                 "blez       %0, .LmiddlePropagate800386A8\n"
                                 "nop\n"
                                 "lbu        $t1, %6\n"
                                 "nop\n"
                                 "addu       $v0, $t1, $zero\n"
                                 "beqz       $v0, .LmiddlePropagate800386B0\n"
                                 "nop\n"
                                 ".LmiddlePropagate800386A8:\n"
                                 "j          .LmiddlePropagate800386B4\n"
                                 "sb        %0, 0x206(%2)\n"
                                 ".LmiddlePropagate800386B0:\n"
                                 "sb         $zero, 0x206(%2)\n"
                                 ".LmiddlePropagate800386B4:\n"
                                 "lb         $v0, 0x206(%2)\n"
                                 "nop\n"
                                 "bgez       $v0, .LmiddlePropagate80038720\n"
                                 "nop\n"
                                 "lbu        $t1, %5\n"
                                 "nop\n"
                                 "addu       $v0, $t1, $zero\n"
                                 "bnez       $v0, .LmiddlePropagate8003871C\n"
                                 "andi      $v0, %3, 0x2\n"
                                 "beqz       $v0, .LmiddlePropagate8003871C\n"
                                 "sb        $zero, 0x206(%2)\n"
                                 "blez       %4, .LmiddlePropagate8003871C\n"
                                 "addu      %0, $zero, $zero\n"
                                 "ori        $a1, $zero, 0x1\n"
                                 "addiu      $a0, $sp, 0x10\n"
                                 ".LmiddlePropagate800386F0:\n"
                                 "lw         $v1, 0x10($a0)\n"
                                 "nop\n"
                                 "lb         $v0, 0x206($v1)\n"
                                 "nop\n"
                                 "bnez       $v0, .LmiddlePropagate8003870C\n"
                                 "nop\n"
                                 "sb         $a1, 0x206($v1)\n"
                                 ".LmiddlePropagate8003870C:\n"
                                 "addiu      %0, %0, 0x1\n"
                                 "slt        $v0, %0, %4\n"
                                 "bnez       $v0, .LmiddlePropagate800386F0\n"
                                 "addiu     $a0, $a0, 0x4\n"
                                 ".LmiddlePropagate8003871C:\n"
                                 "lb         $v0, 0x206(%2)\n"
                                 ".LmiddlePropagate80038720:\n"
                                 "nop\n"
                                 "blez       $v0, .LmiddlePropagate80038784\n"
                                 "nop\n"
                                 "lbu        $t1, %6\n"
                                 "nop\n"
                                 "addu       $v0, $t1, $zero\n"
                                 "bnez       $v0, .LmiddlePropagate80038784\n"
                                 "andi      $v0, %3, 0x2\n"
                                 "beqz       $v0, .LmiddlePropagate80038784\n"
                                 "sb        $zero, 0x206(%2)\n"
                                 "blez       %4, .LmiddlePropagate80038784\n"
                                 "addu      %0, $zero, $zero\n"
                                 "addiu      $a1, $zero, -0x1\n"
                                 "addiu      $a0, $sp, 0x10\n"
                                 ".LmiddlePropagate80038758:\n"
                                 "lw         $v1, 0x10($a0)\n"
                                 "nop\n"
                                 "lb         $v0, 0x206($v1)\n"
                                 "nop\n"
                                 "bnez       $v0, .LmiddlePropagate80038774\n"
                                 "nop\n"
                                 "sb         $a1, 0x206($v1)\n"
                                 ".LmiddlePropagate80038774:\n"
                                 "addiu      %0, %0, 0x1\n"
                                 "slt        $v0, %0, %4\n"
                                 "bnez       $v0, .LmiddlePropagate80038758\n"
                                 "addiu     $a0, $a0, 0x4\n"
                                 ".LmiddlePropagate80038784:\n"
                                 ".set\tnoreorder\n"
                                 : "=r"(desiredLane)
                                 : "0"(desiredLane), "r"(car),
                                   "r"(nearbyLaneMask), "r"(nearbyCount),
                                   "m"(workspace.allowRight),
                                   "m"(workspace.allowLeft), "m"(workspace)
                                 : "$2", "$3", "$4", "$5", "$9", "memory");
                    overlapIndex = 0;
                    if (nearbyCount > 0) {
                    loop_270:
                        asm volatile(
                            "addu %0,$sp,%0\n\t"
                            "lw %1,0x20(%0)\n\t"
                            "lw %2,0(%9)\n\t"
                            "lw %3,4(%9)\n\t"
                            "lh %4,0x114(%9)\n\t"
                            "lui %5,%%hi(D_800A3A2C373B4)\n\t"
                            "lw %5,%%lo(D_800A3A2C373B4)(%5)\n\t"
                            "li %0,0x3FF\n\t"
                            "lw %6,0(%1)\n\t"
                            "lw %7,4(%1)"
                            : "=r"(overlapOffset), "=r"(overlappingCar),
                              "=r"(collisionCarX), "=r"(collisionCarY),
                              "=r"(collisionArgument0),
                              "=r"(collisionTableBase),
                              "=r"(collisionArgument1), "=r"(collisionNeighborY)
                            : "0"(overlapIndex * 4), "r"(car)
                            : "memory");
                        reverseAngle = overlapOffset - collisionArgument0;
                        collisionTableOffset = reverseAngle << 2;
                        collisionTableBase =
                            collisionTableOffset + collisionTableBase;
                        collisionArgument0 = *(s32 *)collisionTableBase;
                        deltaX = collisionCarX - collisionArgument1;
                        collisionArgument1 = deltaX << 16;
                        deltaY = collisionCarY - collisionNeighborY;
                        collisionReturn = MathMultiplyFixed16373B4(
                            collisionArgument0, collisionArgument1);
                        asm volatile("lui %0,%%hi(D_800A3A34373B4)\n\t"
                                     "lw %0,%%lo(D_800A3A34373B4)(%0)\n\t"
                                     "addu %3,%3,%0\n\t"
                                     "lw %1,0(%3)\n\t"
                                     "sll %2,%5,16"
                                     : "=r"(collisionTableBase),
                                       "=r"(collisionArgument0),
                                       "=r"(collisionArgument1),
                                       "=r"(collisionTableOffset)
                                     : "3"(collisionTableOffset), "r"(deltaY)
                                     : "memory");
                        lateralSinProduct = collisionReturn;
                        collisionReturn = MathMultiplyFixed16373B4(
                            collisionArgument0, collisionArgument1);
                        lateralSinProduct -= collisionReturn;
                        lateralGap = lateralSinProduct >> 16;
                        tempV112 = (*(s16 *)(*(u8 **)(car + 0x36C) + 0x1E)) * 2;
                        collisionWidthCopy = tempV112;
                        if (lateralGap >= 0) {
                            if (lateralGap >= tempV112) {
                                overlapIndex += 1;
                                goto block_290;
                            }
                            goto block_274;
                        }
                        if (-lateralGap < collisionWidthCopy) {
                        block_274:
                            collisionTableOffset = reverseAngle << 2;
                            collisionArgument0 =
                                D_800A3A34373B4[0][reverseAngle];
                            collisionArgument1 = deltaX << 16;
                            collisionReturn = MathMultiplyFixed16373B4(
                                collisionArgument0, collisionArgument1);
                            asm volatile("lui %0,%%hi(D_800A3A2C373B4)\n\t"
                                         "lw %0,%%lo(D_800A3A2C373B4)(%0)\n\t"
                                         "addu %3,%3,%0\n\t"
                                         "lw %1,0(%3)\n\t"
                                         "sll %2,%5,16"
                                         : "=r"(collisionTableBase),
                                           "=r"(collisionArgument0),
                                           "=r"(collisionArgument1),
                                           "=r"(collisionTableOffset)
                                         : "3"(collisionTableOffset),
                                           "r"(deltaY)
                                         : "memory");
                            longitudinalGap = collisionReturn;
                            collisionReturn = MathMultiplyFixed16373B4(
                                collisionArgument0, collisionArgument1);
                            longitudinalGap += collisionReturn;
                            longitudinalGap >>= 16;
                            tempV113 =
                                (*(s16 *)(*(u8 **)(car + 0x36C) + 0x22)) * 2;
                            collisionWidthCopy = tempV113;
                            if (longitudinalGap >= 0) {
                                asm("slt %0,%1,%2"
                                    : "=r"(lateralGap)
                                    : "r"(longitudinalGap), "r"(tempV113));
                                if (lateralGap == 0) {
                                    overlapIndex += 1;
                                    goto block_290;
                                }
                                goto block_278;
                            }
                            if (-longitudinalGap < collisionWidthCopy) {
                            block_278:
                                if (longitudinalGap < 0) {
                                    tempV014 =
                                        (u8)(*(s8 *)((u8 *)car + 0x206)) - 1;
                                    (*(s8 *)((u8 *)car + 0x206)) = tempV014;
                                    if ((s8)tempV014 < -1) {
                                        (*(s8 *)((u8 *)car + 0x206)) = -1;
                                    }
                                    tempV015 = (*(s8 *)((u8 *)overlappingCar +
                                                        0x206)) +
                                               1;
                                    (*(s8 *)((u8 *)overlappingCar + 0x206)) =
                                        tempV015;
                                    if ((s8)tempV015 >= 2) {
                                        (*(s8 *)((u8 *)overlappingCar +
                                                 0x206)) = 1U;
                                    }
                                } else {
                                    tempV016 = (*(s8 *)((u8 *)overlappingCar +
                                                        0x206)) -
                                               1;
                                    (*(s8 *)((u8 *)overlappingCar + 0x206)) =
                                        tempV016;
                                    if ((s8)tempV016 < -1) {
                                        (*(s8 *)((u8 *)overlappingCar +
                                                 0x206)) = -1U;
                                    }
                                    tempV017 =
                                        (u8)(*(s8 *)((u8 *)car + 0x206)) + 1;
                                    (*(s8 *)((u8 *)car + 0x206)) = tempV017;
                                    if ((s8)tempV017 >= 2) {
                                        (*(s8 *)((u8 *)car + 0x206)) = 1;
                                    }
                                }
                                asm volatile(
                                    "lh %0,0x248(%2)\n\tlh %1,0x248(%3)"
                                    : "=r"(collisionNeighborOrder),
                                      "=r"(collisionCarOrder)
                                    : "r"(overlappingCar), "r"(car)
                                    : "memory");
                                if (collisionCarOrder <
                                    collisionNeighborOrder) {
                                    goto collisionSlowCar;
                                }
                                *(s32 *)(overlappingCar + 0x90) -= 0x10000;
                                goto collisionDone;
                            } else {
                                goto block_289;
                            }
                        } else {
                        block_289:
                            overlapIndex += 1;
                        block_290:
                            if (overlapIndex >= nearbyCount) {

                            } else {
                                goto loop_270;
                            }
                        }
                    }
                } else {
                    goto block_293;
                }
            } else if (D_800A2F54373B4 == 1) {
            block_293:
                /* Clear the lane and find an active car ahead, with a cap of three. */
                asm volatile(".set\tnoreorder\n\t"
                             "lw\t$2,0x3F0(%2)\n\t"
                             "sb\t$0,0x206(%2)\n\t"
                             "lw\t%0,8($2)\n\t"
                             "sll\t$0,$0,0\n\t"
                             "lbu\t$2,0x268(%0)\n\t"
                             "j\t52f\n\t"
                             "addu\t%1,$0,$0\n\t"
                             "51:\n\t"
                             "slti\t$2,$2,3\n\t"
                             "beqz\t$2,53f\n\t"
                             "addiu\t%1,%1,1\n\t"
                             "lw\t$2,0x3F0(%0)\n\t"
                             "sll\t$0,$0,0\n\t"
                             "lw\t%0,8($2)\n\t"
                             "sll\t$0,$0,0\n\t"
                             "lbu\t$2,0x268(%0)\n\t"
                             "52:\n\t"
                             "sll\t$0,$0,0\n\t"
                             "bnez\t$2,51b\n\t"
                             "addu\t$2,%1,$0\n\t"
                             "lh\t$2,0x1EC(%0)\n\t"
                             "sll\t$0,$0,0\n\t"
                             "beqz\t$2,51b\n\t"
                             "addu\t$2,%1,$0\n\t"
                             "53:\n\t"
                             ".set\treorder\n\t"
                             : "=r"(paceAheadCar), "=r"(varV17)
                             : "r"(car)
                             : "$2", "memory");
                if (func_8003702C373B4(paceAheadCar, car) < 0) {
                    varA17 = -func_8003702C373B4(paceAheadCar, car);
                    goto collisionPaceResume;
                collisionSlowCar:
                    *(s32 *)(car + 0x90) -= 0x10000;
                    goto collisionDone;
                } else {
                    varA17 = func_8003702C373B4(paceAheadCar, car);
                }
            collisionPaceResume:
                asm("slti %0,%1,2" : "=r"(tempV018) : "r"(varA17));
                if (tempV018 != 0) {
                    tempA012 = (*(s32 *)((u8 *)paceAheadCar + 0x90));
                    if (tempA012 > 0x640000) {
                        tempV018 = tempA012 + 0xFFFB0000;
                        (*(s32 *)((u8 *)car + 0x90)) = tempV018;
                        (*(s32 *)((u8 *)car + 0x84)) = tempV018;
                    }
                }
            }
        collisionDone:
            asm volatile(".set\tnoreorder\n"
                         "lw         $t1, %1\n"
                         "lui        $v1, %%hi(D_800A3A2C)\n"
                         "lw         $v1, %%lo(D_800A3A2C)($v1)\n"
                         "addiu      $v0, $t1, 0x300\n"
                         "andi       $v0, $v0, 0x3FF\n"
                         "sw         $v0, %1\n"
                         "sll        $a0, $v0, 2\n"
                         "addu       $v1, $a0, $v1\n"
                         "lw         $v1, 0x0($v1)\n"
                         "lb         $a1, 0x206(%6)\n"
                         "sll        $v0, $v1, 5\n"
                         "subu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "lui        $v1, %%hi(D_800A3A34)\n"
                         "lw         $v1, %%lo(D_800A3A34)($v1)\n"
                         "sra        $v0, $v0, 16\n"
                         "negu       $a1, $a1\n"
                         "mult       $v0, $a1\n"
                         "addu       $a0, $a0, $v1\n"
                         "lw         $v1, 0x0($a0)\n"
                         "nop\n"
                         "sll        $v0, $v1, 5\n"
                         "subu       $v0, $v0, $v1\n"
                         "sll        $v0, $v0, 2\n"
                         "addu       $v0, $v0, $v1\n"
                         "mflo       $a2\n"
                         "sll        $v0, $v0, 2\n"
                         "sra        $v0, $v0, 16\n"
                         "mult       $v0, $a1\n"
                         "lw         $t1, %2\n"
                         "lh         $v1, 0x24E(%6)\n"
                         "addu       $t1, $t1, $a2\n"
                         "sw         $t1, %2\n"
                         "lw         $t1, %9\n"
                         "addiu      $v0, $zero, -0x1\n"
                         "mflo       $a3\n"
                         "addu       $t1, $t1, $a3\n"
                         ".set\tnoreorder\n"
                         : "=r"(tempV114), "=m"(workspace.heading),
                           "=m"(workspace.targetX), "=r"(tailTargetValue),
                           "=r"(tailMinusOne), "=x"(multiplierState)
                         : "r"(car), "m"(workspace.heading),
                           "m"(workspace.targetX), "m"(workspace.targetY)
                         : "$4", "$5", "$6", "$7", "accum", "memory");
            workspace.targetY = tailTargetValue;
            if (tempV114 != tailMinusOne) {
                tempA22 = (*(s16 *)((u8 *)car + 0x1E0));
                tailRouteLength = D_800BE974373B4[0];
                tailSegment = tempV114;
                varA18 = tempA22 - tailSegment;
                tempV115 = tailRouteLength >> 1;
                if (varA18 >= 0) {
                    varV016 = varA18 < tempV115;
                } else {
                    varV016 = -varA18 < tempV115;
                }
                if (varV016 == 0) {
                    tempV116 = tailSegment + tailRouteLength;
                    if (tailSegment < tempA22) {
                        tempV020 = tempV116 - tempA22;
                        varA18 = tempV020;
                        if (tempV020 >= 0) {
                            varV017 = tempA22 - tempV116;
                            goto block_315;
                        }
                    } else {
                        tempV117 = tempA22 + tailRouteLength;
                        tempV021 = tempV117 - tailSegment;
                        varA18 = tempV021;
                        if (tempV021 < 0) {
                            varV017 = tailSegment - tempV117;
                        block_315:
                            varA18 = varV017;
                        }
                    }
                }
                if ((varA18 > 0) || (tailTargetValue = *(s32 *)(car + 0x250),
                                     workspace.targetX = tailTargetValue,
                                     tailTargetValue = *(s32 *)(car + 0x254),
                                     workspace.targetY = tailTargetValue,
                                     (CarAvoidTraffic373B4(car, 1) == 0))) {
                    (*(s16 *)((u8 *)car + 0x24E)) = -1;
                }
            } else if (CarAvoidTraffic373B4(car, 0) != 0) {
                tailTargetValue = *(s32 *)(car + 0x250);
                workspace.targetX = tailTargetValue;
                tailTargetValue = *(s32 *)(car + 0x254);
                workspace.targetY = tailTargetValue;
            }
            asm volatile(".set\tnoreorder\n"
                         "lw         $v0, 0x0(%4)\n"
                         "lw         $t1, %2\n"
                         "nop\n"
                         "subu       $v0, $t1, $v0\n"
                         "sw         $v0, %0\n"
                         "lw         $v0, 0x4(%4)\n"
                         "lw         $t1, %3\n"
                         "nop\n"
                         "subu       $v0, $t1, $v0\n"
                         "sw         $v0, %1\n"
                         ".set\tnoreorder\n"
                         : "=m"(workspace.delta[0]), "=m"(workspace.delta[1])
                         : "m"(workspace.targetX), "m"(workspace.targetY),
                           "r"(car)
                         : "$2", "$9", "memory");
            workspace.delta[2] = -(*(s32 *)((u8 *)car + 0x8));
            varA19 = func_800358EC373B4(&workspace.delta[0]);
            if (D_800A2F48373B4[0] != 0) {
                varA19 = (s32)(*(s16 *)((u8 *)car + 0x114));
                (*(u8 *)((u8 *)car + 0x201)) = 1;
            } else {
                (*(u8 *)((u8 *)car + 0x201)) = 0;
            }
            tempV118 = (*(void (**)(u8 *, s32))(car + 0x354));
            if (tempV118 == func_80025594373B4) {
                CarSteerTowardHeading373B4(car, varA19);
                (*(s16 *)((u8 *)car + 0x104)) =
                    (u16)(*(s16 *)((u8 *)car + 0x114));
            } else {
                tempV118(car, varA19);
            }
            (*(s16 *)((u8 *)car + 0x116)) =
                (s16)((*(s16 *)((u8 *)car + 0x114)) * 4);
            func_8001FAC0373B4(car, (*(s16 *)((u8 *)car + 0x114)) * 4);
            func_8001FB28373B4(car, (s16)(*(s16 *)((u8 *)car + 0x104)));
            /* Keep the three low-product windows and position stores. */
            asm volatile(".set\tnoreorder\n"
                         "lh         $v1, 0x92(%3)\n"
                         "lw         $v0, 0x60(%3)\n"
                         "nop\n"
                         "mult       $v0, $v1\n"
                         "lh         $v1, 0x92(%3)\n"
                         "lw         $v0, 0x6C(%3)\n"
                         "mflo       $a1\n"
                         "nop\n"
                         "nop\n"
                         "mult       $v0, $v1\n"
                         "lh         $v1, 0x92(%3)\n"
                         "lw         $v0, 0x78(%3)\n"
                         "mflo       $a0\n"
                         "nop\n"
                         "nop\n"
                         "mult       $v0, $v1\n"
                         "sra        $v0, $a1, 16\n"
                         "sw         $v0, 0xB0(%3)\n"
                         "lw         $a2, 0xB0(%3)\n"
                         "sra        $v0, $a0, 16\n"
                         "sw         $v0, 0xB4(%3)\n"
                         "lw         $a3, 0xB4(%3)\n"
                         "lw         $a1, 0x8(%3)\n"
                         "mflo       $v1\n"
                         "sra        $v0, $v1, 16\n"
                         "sw         $v0, 0xB8(%3)\n"
                         "lw         $v0, 0x0(%3)\n"
                         "lw         $v1, 0x4(%3)\n"
                         "lw         $t0, 0xB8(%3)\n"
                         "addu       $a0, %3, $zero\n"
                         "addu       $v0, $v0, $a2\n"
                         "addu       $v1, $v1, $a3\n"
                         "addu       $a1, $a1, $t0\n"
                         "sw         $v0, 0x0($a0)\n"
                         "sw         $v1, 0x4($a0)\n"
                         ".set\tnoreorder\n"
                         : "=r"(tailCarArg), "=r"(tailPositionZ),
                           "=x"(multiplierState)
                         : "r"(car)
                         : "$2", "$3", "$6", "$7", "$8", "accum", "memory");
            *(s32 *)(tailCarArg + 8) = tailPositionZ;
            func_80029CB4373B4(tailCarArg);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/objects", func_80038D78);

s32 func_80039008(u8 *arg0, u8 *arg1) {
    extern s32 func_8003702C();
    volatile s32 pad[4];
    s32 result;

    if (*(s32 *)(arg0 + 0x90) <= *(s32 *)(arg1 + 0x90)) {
        return 0;
    }
    result = func_8003702C(arg0, arg1);
    if (result >= 2) {
        return 0;
    }
    return (*(s32 *)(arg0 + 0x90) - *(s32 *)(arg1 + 0x90)) / 20 >> 16 >= result;
}

extern u8 D_800A2F84w44[] asm("D_800A2F84");
extern s32 D_800A3730, D_800A3734;

void func_800390A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 idx;
    register s32 i asm("a3");
    s32 n;
    s32 rem;
    u8 *p;
    u16 heading;
    s32 index;
    s32 var_a3;
    register s32 temp_t0 asm("t0");
    s32 temp_v1;
    s32 var_a0;
    s32 x;
    s32 y;
    register s32 newY asm("v0");
    s32 old30;
    s32 old34;
    s8 check;

    idx = *(s16 *)((u8 *)arg1 + 0x1E0);
    if (idx == -1) {
        return;
    }
    asm("" : "=r"(i) : "0"(idx));
    n = D_800BE974[0] - 1;
    rem = (i + n) % D_800BE974[0];
    p = (u8 *)D_800BE980[0] + i * 0x90;
    *(s16 *)((u8 *)arg0 + 0x24E) = rem;
    heading = *(u16 *)(p + 0x10);
    index = ((0x400 - heading) & 0x3FF) << 2;
    temp_t0 = *(s32 *)(index + (u32)D_800A3A2CAbsolute[0]);
    temp_v1 = *(s32 *)(index + (u32)D_800A3A34Absolute[0]);
    if (*(s16 *)((u8 *)arg0 + 0x288) != 0) {
        var_a3 = (temp_v1 * 0x6D6) >> 16;
        var_a0 = (temp_t0 * 0x6D6) >> 16;
        arg2 = D_800A2F84w44[0];
    } else {
        var_a3 = (temp_v1 * 0x6D6) >> 16;
        var_a0 = (temp_t0 * 0x6D6) >> 16;
    }
    if (*(s16 *)((u8 *)arg0 + 0x288) == 0) {
        check = *(s8 *)((u8 *)arg1 + 0x203);
        if (check >= 0) {
            if (check >= 7) {
                goto bad;
            }
            goto ok;
        } else {
            if (-check < 7) {
                goto ok;
            }
        }
    bad:
        *(s16 *)((u8 *)arg0 + 0x24E) = -1;
        return;
    }
ok:
    x = *(s32 *)((u8 *)arg1);
    y = *(s32 *)((u8 *)arg1 + 4);
    if ((arg2 & 0xFF) == 0) {
        D_800A3730 = x + var_a3;
        newY = y + var_a0;
    } else {
        D_800A3730 = x - var_a3;
        newY = y - var_a0;
    }
    *(volatile s32 *)&D_800A3734 = newY;
    old30 = *(volatile s32 *)&D_800A3730;
    old34 = *(volatile s32 *)&D_800A3734;
    D_800A3730 = var_a3;
    D_800A3734 = var_a0;
    *(s32 *)((u8 *)arg0 + 0x250) = old30;
    *(s32 *)((u8 *)arg0 + 0x254) = old34;
}

typedef struct TrafficCar {
    s32 x, y;
    u8 unk8[0x88];
    s32 speed;
    u8 unk94[0x80];
    s16 heading;
    u8 unk116[0xCA];
    s16 segment;
    u8 unk1E2[0x21];
    s8 unk203;
    u8 unk204[2];
    s8 lane;
    u8 unk207[7];
    s16 headingOffset;
    u8 unk210[0x3E];
    s16 targetSegment;
    s32 avoidX;
    s32 avoidY;
    u8 unk258[0x30];
    s16 unk288;
    u8 unk28A[0x156];
    struct TrafficCar *next;
} TrafficCar;

s32 func_80039274(TrafficCar *car, TrafficCar *other, u8 side) {
    s32 cosine;
    s32 sine;
    s32 oldX;
    s32 oldY;
    s32 result;
    s32 y;
    register s32 x asm("$3");
    s32 newY;
    u8 *section;
    s16 segment;

    segment = other->segment;
    if (segment != -1) {
        section = (u8 *)D_800BE980[0] + segment * 0x90;
        if (MathGetAngleDelta(other->heading, *(u16 *)(section + 0x10)) < 0) {
            result =
                -MathGetAngleDelta(other->heading, *(u16 *)(section + 0x10));
        } else {
            result =
                MathGetAngleDelta(other->heading, *(u16 *)(section + 0x10));
        }
        if (result < 60) {
            result = (other->heading + other->headingOffset + 0x400) % 1023;
        } else {
            result = *(u16 *)(section + 0x10);
        }
        cosine = ((s32 **)D_800A3A2CAbsolute)[0][result];
        sine = ((s32 **)D_800A3A34Absolute)[0][result];
        if (side) {
            x = (cosine * 1600 + sine * 350) >> 16;
            y = (sine * 1600 - cosine * 350) >> 16;
        } else {
            x = (cosine * 1600 - sine * 350) >> 16;
            y = (sine * 1600 + cosine * 350) >> 16;
        }
        oldX = other->x;
        oldY = other->y;
        x = oldX + x;
        newY = oldY + y;
        D_800A3734 = newY;
        car->avoidY = newY;
        D_800A3730 = x;
        car->avoidX = x;
        car->targetSegment = -1;
        result = car->segment;
        if (side) {
            x = oldX + ((cosine * 3200 + sine * 350) >> 16);
            y = oldY + ((sine * 3200 - cosine * 350) >> 16);
        } else {
            x = oldX + ((cosine * 3200 - sine * 350) >> 16);
            y = oldY + ((sine * 3200 + cosine * 350) >> 16);
        }
        func_80024E90(x, y, &result, &oldX, &oldY);
        if (result != -1) {
            if (oldY == 1) {
                return 0;
            }
            asm("");
        }
        return 1;
    }
    return 0;
}

extern s32 D_800A2EB4Absolute[];
extern u8 *D_800A3878Absolute[];
extern s32 D_800AE154[];
extern s32 func_80039274(TrafficCar *, TrafficCar *, u8);
extern void func_80039B74(s32 *, s32);

s32 CarAvoidTraffic(TrafficCar *car, s32 keepTarget) {
    s32 maxDistance;
    s32 count;
    TrafficCar *other;
    s32 value;
    s32 forward;
    s32 lateral;
    s8 leftAllowed;
    s32 routeDistance;
    s32 angle;
    s32 cosine;
    register s32 *cosTable asm("v1");
    s32 sine;
    s32 dx;
    s32 carX;
    s32 dy;
    s32 sideLimit;
    s32 sideScale;
    s32 backLimit;
    s32 lateralLimit;
    u32 flags;
    s8 otherLane;

    if (D_800A2F58 != 0) {
        return 0;
    }
    if (car->speed == 0) {
        return 0;
    }
    other = (TrafficCar *)D_800A3878Absolute[0];
    for (count = 0; count < D_800A2EB4Absolute[0];
         count++, other = other->next) {
        if (car == other) {
            continue;
        }
        value = car->speed - other->speed;
        maxDistance = (value >> 16) / 50 + 1;
        if (maxDistance >= 6) {
            maxDistance = 5;
        }
        routeDistance = func_8003702C((u8 *)other, (u8 *)car);
        if (keepTarget & 0xFF) {
            if (routeDistance < 3) {
                return 0;
            }
        } else if (routeDistance < -1 || maxDistance < routeDistance) {
            continue;
        }
        if (car->unk288 == 0) {
            if (ABS(other->unk203) >= 7) {
                car->targetSegment = -1;
                continue;
            }
        }
        angle = 0x400;
        angle -= car->heading;
        cosTable = (s32 *)D_800A3A2CAbsolute[0];
        /* Keep the x loads after the table base and entry address. */
        asm("lw %0,%1" : "=r"(dx) : "m"(other->x), "r"(cosTable));
        maxDistance = angle & 0x3FF;
        cosTable = (s32 *)((maxDistance * 4) + (u32)cosTable);
        asm("lw %0,%2"
            : "=r"(carX), "=r"(cosTable)
            : "m"(car->x), "1"(cosTable));
        cosine = *cosTable;
        dx -= carX;
        sine = ((s32 **)D_800A3A34Absolute)[0][maxDistance];
        dy = other->y - car->y;
        forward = (cosine * dx - sine * dy) >> 16;
        lateral = (sine * dx + cosine * dy) >> 16;
        routeDistance = ABS(MathGetAngleDelta(car->heading, other->heading));
        sideScale =
            (((s32 **)D_800A3A34Absolute)[0][routeDistance] * 250) >> 16;
        if (sideScale < 0) {
            sideScale = -sideScale;
        }
        sideLimit = sideScale + 400;
        if (lateral >= 0 ? lateral >= 201 : -lateral >= 201) {
            if (ABS(value) <= 0x36FFFF) {
                if (value > 0) {
                    backLimit = ((value >> 16) * 4) - 230;
                } else {
                    backLimit = -230;
                }
                lateralLimit = sideLimit + 20;
                if ((lateral >= 0 ? lateral < lateralLimit
                                  : -lateral < lateralLimit) &&
                    backLimit < forward && forward < 1350 &&
                    !(keepTarget & 0xFF)) {
                    value = car->lane;
                    func_80039B74((s32 *)car, 0);
                    maxDistance = (car->segment + 4) % D_800BE974[0];
                    flags = ((u32 *)D_800AE154[0])[maxDistance * 3 + 2] >> 30;
                    leftAllowed = flags & 1;
                    maxDistance = flags & 2;
                    if (lateral > 0) {
                        otherLane = other->lane;
                        if (otherLane < car->lane && otherLane < -1) {
                            car->lane = value;
                            continue;
                        }
                        backLimit = func_80039274(car, other, 1);
                        if (car->lane > 0 && maxDistance == 0) {
                            backLimit = 1;
                        }
                    } else {
                        otherLane = other->lane;
                        if (otherLane > car->lane && otherLane >= 2) {
                            car->lane = value;
                            continue;
                        }
                        backLimit = func_80039274(car, other, 0);
                        if (car->lane < 0 && leftAllowed == 0) {
                            backLimit = 1;
                        }
                    }
                    car->lane = value;
                    if ((s8)backLimit != 0) {
                        if (forward < 0) {
                            car->speed = other->speed + 0x280000;
                        } else {
                            car->speed = other->speed - 0x280000;
                        }
                    }
                    return 1;
                }
            }
            if (sideLimit < ABS(lateral)) {
                if (car->targetSegment != -1) {
                    return 1;
                }
                continue;
            }
        }
        if (value < 0 && other->speed > 0x320000) {
            continue;
        }
        if (!(keepTarget & 0xFF)) {
            if (routeDistance < 0) {
                continue;
            }
            if (value > 0x460000) {
                if (other->unk203 < 0) {
                    func_800390A0((s32)car, (s32)other, 1, 1);
                } else {
                    func_800390A0((s32)car, (s32)other, 0, 1);
                }
            }
        }
        if ((u32)(forward - 1001) < 349) {
            if (other->speed > 0xC80000) {
                car->speed = other->speed - 0x10000;
            } else if (other->speed > 0x3C0000) {
                car->speed -= value / 20;
            }
        }
        if (car->targetSegment != -1) {
            if (car->speed < 0) {
                car->speed = 0xA0000;
            }
            return 1;
        }
    }
    return 0;
}

void func_80039B74(s32 *arg0, s32 arg1) {
    u8 *obj = (u8 *)arg0;
    s16 idx;
    s32 result;
    s32 base;
    s32 off12;
    register s32 objX asm("a1");
    s32 entryX;
    s32 entryY;
    register s32 objY asm("v1");
    s32 w;
    s32 value;
    s32 tableA;
    s32 prod;
    register s32 prod2 asm("v0");
    register s32 neg asm("v1");
    u8 *eptr;
    u8 *entryAddr;
    u8 *ptr;

    idx = *(s16 *)(obj + 0x1E0);
    if (idx == -1) {
        result = 10;
    } else {
        base = D_800AE154[arg1];
        off12 = idx * 12;
        objX = *(s32 *)obj;
        eptr = *(u8 **)D_800BE980;
        entryAddr = (u8 *)(off12 + base);
        entryX = *(s32 *)entryAddr;
        ptr = eptr + idx * 0x90;
        w = (0x400 - *(u16 *)(ptr + 0x10)) & 0x3FF;
        tableA = ((s32 **)D_800A3A34Absolute)[0][w];
        prod = tableA * (objX - entryX);
        entryY = *(s32 *)(entryAddr + 4);
        objY = *(s32 *)(obj + 4);
        prod2 = ((s32 **)D_800A3A2CAbsolute)[0][w] * (objY - entryY);
        value = prod + prod2;
        neg = -(value >> 16);
        if (neg < 0) {
            result = (neg - 0xFA) / 500;
        } else {
            result = (neg + 0xFA) / 500;
        }
    }
    *(u8 *)(obj + 0x206) = result;
}

s8 func_80039C68(u8 *arg0, s32 arg1, s32 arg2) {
    s32 heading;
    s32 x;
    s32 index;
    s32 y;

    heading = *(u16 *)(arg0 + 0x10);
    x = *(s32 *)(arg0 + 0x14);
    index = (0x400 - heading) & 0x3FF;
    y = *(s32 *)(arg0 + 0x18);
    return -((((s32 **)D_800A3A34Absolute)[0][index] * (arg1 - x) +
              ((s32 **)D_800A3A2CAbsolute)[0][index] * (arg2 - y)) >>
             16) /
           250;
}

void func_80039CF4(void) {
    u8 *node;
    u8 *track;
    s32 index;
    s32 id;
    s32 angle;
    s32 heading;
    s32 objX;
    s32 entryX;
    s32 entryY;
    s32 objY;
    s32 tableA;
    s32 tableB;
    s32 prodA;
    s32 value;

    node = (u8 *)D_800A3984[0] + 0x500;
    while (node != NULL) {
        id = *(s16 *)(node + 0x1E0);
        if (id != -1) {
            track = *(u8 **)D_800BE980;
            track += id * 0x90;
            heading = *(u16 *)(track + 0x10);
            objX = *(s32 *)node;
            entryX = *(s32 *)(track + 0x14);
            angle = heading;
            index = ((0x400 - angle) & 0x3FF) << 2;
            tableA = *(s32 *)(index + (u32)D_800A3A34Absolute[0]);
            prodA = tableA * (objX - entryX);
            objY = *(s32 *)(node + 4);
            entryY = *(s32 *)(track + 0x18);
            tableB = *(s32 *)(index + (u32)D_800A3A2CAbsolute[0]);
            value = prodA + tableB * (objY - entryY);
            *(s8 *)(node + 0x203) = (-(value >> 16)) / 250;
        }
        node = *(u8 **)(node + 0x3E0);
    }
}

/* Separate absolute aliases preserve the original access lifetimes. */
extern FarVar gGridSavedRead;
extern FarVar gGridSavedWrite;
asm(".globl gGridSavedRead\ngGridSavedRead = D_800A2EE4\n"
    ".globl gGridSavedWrite\ngGridSavedWrite = D_800A2EE4");
extern s32 D_800A2DE8Grid[] asm("D_800A2DE8");
extern s32 D_800A36A4;
extern u8 D_800A33E4;
extern s32 D_800A2F5C;

extern s32 gGridCameraX0[];
extern s32 gGridCameraY0[];
extern s32 gGridCameraX3[];
extern s32 gGridCameraY3[];
extern s32 gGridCameraX4[];
extern s32 gGridCameraY4[];
extern s32 gGridCameraX5[];
extern s32 gGridCameraY5[];
extern s32 gGridCameraX6[];
extern s32 gGridCameraY6[];
extern s32 gGridCameraX7[];
extern s32 gGridCameraY7[];
extern s32 gGridCameraZ0[];
asm(".globl gGridCameraX0\ngGridCameraX0 = D_800B9954\n"
    ".globl gGridCameraY0\ngGridCameraY0 = D_800B9958\n"
    ".globl gGridCameraX3\ngGridCameraX3 = D_800B9954\n"
    ".globl gGridCameraY3\ngGridCameraY3 = D_800B9958\n"
    ".globl gGridCameraX4\ngGridCameraX4 = D_800B9954\n"
    ".globl gGridCameraY4\ngGridCameraY4 = D_800B9958\n"
    ".globl gGridCameraX5\ngGridCameraX5 = D_800B9954\n"
    ".globl gGridCameraY5\ngGridCameraY5 = D_800B9958\n"
    ".globl gGridCameraX6\ngGridCameraX6 = D_800B9954\n"
    ".globl gGridCameraY6\ngGridCameraY6 = D_800B9958\n"
    ".globl gGridCameraX7\ngGridCameraX7 = D_800B9954\n"
    ".globl gGridCameraY7\ngGridCameraY7 = D_800B9958\n"
    ".globl gGridCameraZ0\ngGridCameraZ0 = D_800B995C\n");
void CarPlaceOnStartingGrid(void) {
    volatile VECTOR position;
    VECTOR ground;
    s32 section;
    register s32 cameraOffset asm("a0");
    s32 gridSpeed;
    s32 product;
    s32 workValue;
    s32 cameraWork;
    register s32 tableWork asm("a2");
    s32 lastGridSection;
    s32 sectionOffset;
    s32 cameraSectionOffset;
    s32 groundSection;
    s32 cameraSection;
    s32 spacing;
    s32 viewX;
    s32 viewY;
    s32 retryX;
    s32 retryY;
    s8 gridRow;
    s32 side;
    u8 savedFlag;
    u8 *car;

    car = D_800A3878w15[0];
    savedFlag = FAR_VAR(u8, gGridSavedRead);
    spacing = 2;
    D_800A36A4 = 0x78;
    D_800A2F58 = 1;
    D_800A2DE8Grid[0] = 0x4B0;
    FAR_VAR(u8, gGridSavedWrite) = 0;
    D_800A33E4 = savedFlag;
    D_800A2F5C = -(D_800A2E94[0] * 0x258);
    if (FAR_VAR(s32, gFarMode2EA4) == spacing) {
        spacing = 3;
    }
    lastGridSection = D_800BE974[0] - 0x23;
    if (car != NULL) {
        do {
            gridRow = (*(s8 *)(car + 0x204));
            section = lastGridSection - (gridRow * spacing);
            if (gridRow & 1) {
                /* Preserve the two branch delay slots. */
                asm("" : : "r"(car));
                side = 1;
            } else {
                side = -1;
            }
            (*(s8 *)(car + 0x206)) = side;
            if (D_800A2EB0Absolute[0] > 0) {
                (*(s8 *)(car + 0x206)) = 0;
            }
            if (FAR_VAR(s32, gFarMode2EA4) == 2) {
                (*(s8 *)(car + 0x206)) = 0;
            }
            sectionOffset = section * 0xC;
            (*(s32 *)(car + 0x0)) =
                (s32) * (s32 *)(sectionOffset + D_800AE154[0]);
            (*(s32 *)(car + 0x4)) =
                (s32)(*(s32 *)(sectionOffset + D_800AE154[0] + 0x4));
            func_80022FB8(
                car, 0x400 - ((*(u16 *)(sectionOffset + D_800AE154[0] + 0xA)) &
                              0x3FFF));
            (*(s32 *)(car + 0x90)) =
                (s32)(((*(s16 *)(sectionOffset + D_800AE154[0] + 0x8))
                       << 0x11) /
                      3);
            gridSpeed = (*(s16 *)(sectionOffset + D_800AE154[0] + 0x8)) << 0x10;
            (*(s16 *)(car + 0x1E0)) = section;
            (*(s32 *)(car + 0x1F4)) = (s32)(s16)section;
            (*(s32 *)(car + 0x90)) = gridSpeed;
            if (((*(s16 *)(car + 0x1EC)) == 0) ||
                ((D_800A2EDAw15[0] != 0) && (car == D_800A3554[0]))) {
                (*(u8 *)(car + 0x20C)) = 0xC;
                (*(s16 *)(car + 0xFA)) = (s16)(s8)(u8)(*(s8 *)(car + 0x204));
                cameraSection = (s32)(section + 0xC) % (s32)D_800BE974[0];
                cameraSectionOffset = cameraSection * 0xC;
                *(s32 *)(((u8 *)gGridCameraX0) +
                         ((*(s8 *)(car + 0x20B)) * 0xC)) =
                    *(s32 *)(cameraSectionOffset + D_800AE154[0]);
                *(s32 *)(((u8 *)gGridCameraY0) +
                         ((*(s8 *)(car + 0x20B)) * 0xC)) =
                    (*(s32 *)(cameraSectionOffset + D_800AE154[0] + 0x4));
                workValue = *(u16 *)(cameraSectionOffset + D_800AE154[0] + 0xA);
                cameraWork = *(s8 *)(car + 0x20B);
                workValue &= 0x3FFF;
                workValue += 0x300;
                workValue &= 0x3FF;
                tableWork = workValue * 4;
                cameraOffset = cameraWork * 12;
                workValue = *(s32 *)(tableWork + D_800A3A2CAbsolute[0]);
                product = workValue * 1000;
                workValue = *(s32 *)(((u8 *)gGridCameraX0) + cameraOffset);
                cameraWork = D_800A3A34Absolute[0];
                workValue -= product >> 16;
                *(s32 *)(((u8 *)gGridCameraX0) + cameraOffset) = workValue;
                cameraOffset = (*(s8 *)(car + 0x20B)) * 0xC;
                tableWork += cameraWork;
                cameraWork = *(s32 *)tableWork;
                /* (124 + 1) * 8 keeps the camera load between scales. */
                product = cameraWork * 124;
                asm volatile("" : "=r"(product) : "0"(product));
                workValue = *(s32 *)(((u8 *)gGridCameraY0) + cameraOffset);
                product = (product + cameraWork) * 8;
                workValue -= product >> 16;
                *(s32 *)(((u8 *)gGridCameraY0) + cameraOffset) = workValue;
                viewX = *(s32 *)(((u8 *)gGridCameraX3) +
                                 ((*(s8 *)(car + 0x20B)) * 0xC));
                if (viewX < 0) {
                    viewX += 3;
                }
                position.vx = (viewX >> 2) - D_800AE844[0];
                viewY = *(s32 *)(((u8 *)gGridCameraY3) +
                                 ((*(s8 *)(car + 0x20B)) * 0xC));
                if (viewY < 0) {
                    viewY += 3;
                }
                position.vy = (viewY >> 2) - D_800AE844[1];
                position.vx = *(s32 *)(((u8 *)gGridCameraX4) +
                                       ((*(s8 *)(car + 0x20B)) * 0xC));
                position.vy = *(s32 *)(((u8 *)gGridCameraY4) +
                                       ((*(s8 *)(car + 0x20B)) * 0xC));
                ground.vx = cameraSection;
                groundSection =
                    func_80024E90(position.vx, position.vy, &ground.vx,
                                  &ground.vy, &ground.vz);
                ground.vz = groundSection;
                if (groundSection == -1) {
                    *(s32 *)(((u8 *)gGridCameraX5) +
                             ((*(s8 *)(car + 0x20B)) * 0xC)) =
                        *(s32 *)(cameraSectionOffset + D_800AE154[0]);
                    *(s32 *)(((u8 *)gGridCameraY5) +
                             ((*(s8 *)(car + 0x20B)) * 0xC)) =
                        (*(s32 *)(cameraSectionOffset + D_800AE154[0] + 0x4));
                    retryX = *(s32 *)(((u8 *)gGridCameraX6) +
                                      ((*(s8 *)(car + 0x20B)) * 0xC));
                    if (retryX < 0) {
                        retryX += 3;
                    }
                    position.vx = (retryX >> 2) - D_800AE844[0];
                    retryY = *(s32 *)(((u8 *)gGridCameraY6) +
                                      ((*(s8 *)(car + 0x20B)) * 0xC));
                    if (retryY < 0) {
                        retryY += 3;
                    }
                    position.vy = (retryY >> 2) - D_800AE844[1];
                    position.vx = *(s32 *)(((u8 *)gGridCameraX7) +
                                           ((*(s8 *)(car + 0x20B)) * 0xC));
                    position.vy = *(s32 *)(((u8 *)gGridCameraY7) +
                                           ((*(s8 *)(car + 0x20B)) * 0xC));
                    cameraSection =
                        func_80024E90(position.vx, position.vy, &ground.vx,
                                      &ground.vy, &ground.vz);
                }
                *(s32 *)(((u8 *)gGridCameraZ0) +
                         ((*(s8 *)(car + 0x20B)) * 0xC)) =
                    (ground.vy * 4) + 0xE6;
                *(s32 *)(((u8 *)D_800A3584nm) + ((*(s8 *)(car + 0x20B)) * 4)) =
                    cameraSection;
                *(((u8 *)D_800A363Cnm) + (*(s8 *)(car + 0x20B))) = 0;
            }
            car = (*(u8 **)(car + 0x3E0));
        } while (car != NULL);
    }
}

extern s32 D_800A2F00nm[] asm("D_800A2F00.NON_MATCHING");
extern s32 D_800A2EFCnm[] asm("D_800A2EFC.NON_MATCHING");
extern s16 D_800A3910nm[] asm("D_800A3910.NON_MATCHING");
extern void func_800373B4(u8 *);
extern void func_8002A1FC(u8 *);

void func_8003A440(void) {
    u8 *node;
    s32 counter;
    s32 one;

    node = D_800A3878w15[0];
    D_800A2F4C = 12;
    if (node != NULL) {
        counter = 10;
        do {
            func_800373B4(node);
            if (*(s16 *)(node + 0x1EC) == 0) {
                func_8002AD20((s32 *)node, *(s16 *)(node + 0x114));
                if (D_800A2EACAbsolute[0] == 0) {
                    if (D_800A36A4 < 11) {
                        if (D_800A36A4 == counter) {
                            one = 1;
                            *(u8 *)(node + 0x20C) = one;
                            one = 0;
                        }
                        func_8002A1FC(node);
                    }
                }
                *(s32 *)(node + 0x40C) = *(s32 *)(node + 0x90);
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != NULL);
    }
    if (D_800A36A4-- > 0) {
        return;
    }
    D_800A2F00nm[0] = 1;
    D_800A2EFCnm[0] = 0x50;
    D_800A2F4C = 0x14;
    D_800A2F58 = 0;
    D_800A3910nm[0] = 0;
    D_800A2EE4w15[0] = D_800A33E4;
}

extern void func_80041564(u8 *, s32);
extern void func_800294A8(void *);
extern void func_8003CF0C(u8 *);
extern u8 *D_800A3554Absolute[];
extern u32 D_800A2F50;
extern u8 D_800A39F8nm[] asm("D_800A39F8.NON_MATCHING");
extern u8 D_800A38B8nm[] asm("D_800A38B8.NON_MATCHING");

void func_8003A54C(void) {
    u8 *node;
    u8 *object;
    u8 *player;
    s32 mode;
    s32 nodeState;
    s32 nodeIndex;
    s8 place;

    node = D_800A3878Absolute[0];
    D_800A2F4C = 0x14;
    D_800A2EE4w15[0] = 0;
    if (D_800A2EACAbsolute[0] == 0x77) {
        mode = D_800A2EB0Absolute[0];
        D_800A2EC4w15[0] = 0;
        if (mode == 0) {
            object = D_800A3554Absolute[0];
            if (D_800A2EA4Absolute[0] == 2) {
                *(u8 *)(*(u8 **)(object + 0x3E0) + 0x410) = 0;
                player = D_800A3554[0];
                if (*(u8 *)(player + 0xF4) == 0 &&
                    *(u8 *)(*(u8 **)(player + 0x3E0) + 0xF4) == 0) {
                    goto store410;
                }
                if (*(s8 *)(player + 0x204) <
                    *(s8 *)(*(u8 **)(player + 0x3E0) + 0x204)) {
                    object = player;
                } else {
                    object = *(u8 **)(player + 0x3E0);
                }
            }
            if (*(s8 *)(object + 0x204) == 1) {
                func_80041564(object, 0x28);
            } else if (*(s8 *)(object + 0x204) < 6 && D_800A2E90w15[0] >= 6) {
                func_80041564(object, 0x43);
            }
        } else if (mode == 1) {
            u8 *racer;

            racer = D_800A3554Absolute[0];
            if (*(u8 *)(racer + 0xF4) == 0) {
                goto afterStore;
            }
            if (*(s8 *)(racer + 0x204) < 6 && *(s8 *)(racer + 0x204) != mode) {
                func_80041564(racer, 0x46);
            } else if (*(s8 *)(racer + 0x204) >= 0xC) {
                func_80041564(racer, 0x40);
            }
        } else {
            goto afterStore;
        }
    store410:
        *(u8 *)(D_800A3554Absolute[0] + 0x410) = 0;
    afterStore:
        D_800A3910nm[0] = 0x7FFF;
        if (D_800A35A4w15f[0] != 0) {
            D_800A39F8nm[0] = 0;
            D_800A3764w15f[0] = 0;
            D_800A372Cw15f[0] = 0;
            D_800A2EFCnm[0] = 0;
            D_800A38B8nm[0] = 0;
        }
    }
    if (node != NULL) {
        do {
            nodeState = *(s16 *)(node + 0x1EC);
            D_800A2F50 = D_800A2EACAbsolute[0] / 2 + 0x172;
            if (nodeState == 0) {
                if (*(u8 *)(node + 0xF4) == 0 || *(u8 *)(node + 0xF4) == 2 ||
                    *(s32 *)(node + 0x354) != (s32)func_80025594) {
                    *(s32 *)(node + 0x84) = 0;
                    func_80029CB4((s32 *)node);
                    (*(void (**)(u8 *))(node + 0x354))(node);
                } else {
                    *(s16 *)(node + 0x120) = 0;
                    *(s32 *)(node + 0x228) = 0;
                    if (*(s32 *)(node + 0x90) > 0x1B80000) {
                        *(s32 *)(node + 0x90) = 0x1B80000;
                    }
                    if (D_800A2EB4Absolute[0] >= 2) {
                        place = *(u8 *)(node + 0x204);
                        *(s8 *)(node + 0x206) = place % 3 - 1;
                    } else {
                        *(s8 *)(node + 0x206) = 0;
                    }
                    D_800A2F4C = 0x14;
                    func_8003CF0C(node);
                    func_800373B4(node);
                    nodeIndex = *(s16 *)(node + 0x114);
                    D_800A2F4C = 0x14;
                    func_8002AD20((s32 *)node, nodeIndex);
                    func_800294A8(node);
                }
            } else {
                func_8003CF0C(node);
                func_800373B4(node);
            }
            node = *(u8 **)(node + 0x3E0);
        } while (node != NULL);
    }
    func_80039CF4();
}

extern s16 D_80098254[];

void func_8003A880(s32 car) {
    s32 old;
    s32 new;
    s32 idx;
    s32 turn;
    s32 t;
    s32 t2;
    s32 t3;
    s32 t4;

    if (*(s16 *)(car + 0x102) != 0) {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = -D_80098254[idx];
    } else {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = D_80098254[idx];
    }
    *(u16 *)(car + 0x114) = (*(u16 *)(car + 0x114) + turn + 0x400) & 0x3FF;
    t = *(s32 *)(car + 0x90);
    t2 = t - (t >> 5);
    *(s32 *)(car + 0x90) = t2;
    if (turn != 0) {
        return;
    }
    *(u16 *)(car + 0x1BC) = 0x32;
    t3 = *(s32 *)(car + 0x90);
    t4 = t3 - 0x320000;
    *(s32 *)(car + 0x90) = t4;
    if (t4 < 0) {
        *(s32 *)(car + 0x90) = 0;
    }
    ObjectSetCallbackIfAllowed((Batch0CallbackObject *)car, func_8003ABC0);
}

extern s16 D_80098294[];

void func_8003A950(s32 car) {
    s32 old;
    s32 new;
    s32 idx;
    s32 turn;
    s32 t;
    s32 t2;
    s32 t3;
    s32 t4;

    if (*(s16 *)(car + 0x102) != 0) {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = -D_80098294[idx];
    } else {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = D_80098294[idx];
    }
    *(u16 *)(car + 0x114) = (*(u16 *)(car + 0x114) + turn + 0x400) & 0x3FF;
    t = *(s32 *)(car + 0x90);
    t2 = t - (t >> 5);
    *(s32 *)(car + 0x90) = t2;
    if (turn != 0) {
        return;
    }
    *(u16 *)(car + 0x1BC) = 0x32;
    t3 = *(s32 *)(car + 0x90);
    t4 = t3 - 0x320000;
    *(s32 *)(car + 0x90) = t4;
    if (t4 < 0) {
        *(s32 *)(car + 0x90) = 0;
    }
    ObjectSetCallbackIfAllowed((Batch0CallbackObject *)car, func_8003ABC0);
}

extern s16 D_800982D4[];

void func_8003AA20(s32 car) {
    s32 old;
    s32 new;
    s32 idx;
    s32 turn;
    s32 t;
    s32 t2;
    s32 t3;
    s32 t4;

    if (*(s16 *)(car + 0x102) != 0) {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = -D_800982D4[idx];
    } else {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = D_800982D4[idx];
    }
    *(u16 *)(car + 0x114) = (*(u16 *)(car + 0x114) + turn + 0x400) & 0x3FF;
    t = *(s32 *)(car + 0x90);
    t2 = t - (t >> 7);
    *(s32 *)(car + 0x90) = t2;
    if (turn != 0) {
        return;
    }
    *(u16 *)(car + 0x1BC) = 0;
    t3 = *(s32 *)(car + 0x90);
    t4 = t3 - 0x320000;
    *(s32 *)(car + 0x90) = t4;
    if (t4 < 0) {
        *(s32 *)(car + 0x90) = 0;
    }
    ObjectSetCallbackIfAllowed((Batch0CallbackObject *)car, func_8003ABC0);
}

extern s16 D_80098328[];

void func_8003AAEC(s32 car) {
    s32 old;
    s32 new;
    s32 idx;
    s32 turn;
    s32 t;
    s32 t2;
    s32 mode;

    if (*(s16 *)(car + 0x102) != 0) {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = -D_80098328[idx];
    } else {
        old = *(u16 *)(car + 0x1BC);
        new = old + 1;
        idx = (s16)old;
        *(u16 *)(car + 0x1BC) = new;
        turn = D_80098328[idx];
    }
    *(u16 *)(car + 0x114) = (*(u16 *)(car + 0x114) + turn + 0x400) & 0x3FF;
    t = *(s32 *)(car + 0x90);
    t2 = t - (t >> 9);
    *(s32 *)(car + 0x90) = t2;
    if (*(u16 *)(car + 0x360) == 2) {
        *(s32 *)(car + 0x90) = t2 - (t2 >> 3);
    }
    if (turn != 0) {
        return;
    }
    *(u16 *)(car + 0x1BC) = 0;
    ObjectSetCallbackIfAllowed((Batch0CallbackObject *)car, func_80025594);
}

extern void func_80025594(u8 *);

void func_8003ABC0(u8 *object) {
    *(u16 *)(object + 0x1BC) += 1;
    *(u32 *)(object + 0x90) = 0;
    if ((*(u16 *)(object + 0x3A4) & 0xF) == 0) {
        if (*(s16 *)(object + 0x1BC) >= 0x65) {
            *(u16 *)(object + 0x1BC) = 0;
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_80025594);
        }
    }
}

void func_8003AC18(u8 *object, s32 arg1, s32 arg2, s32 arg3) {
    if (*(s16 *)(object + 0x1EC) == 1) {
        *(s16 *)(object + 0x1BC) = 0;
        if ((arg2 = arg2) > 0 && arg3 > 0) {
            *(s16 *)(object + 0x102) = 1;
        } else if ((arg2 = arg2) < 0 && arg3 < 0) {
            *(s16 *)(object + 0x102) = 1;
        } else {
            *(s16 *)(object + 0x102) = 0;
        }
        if (arg1 >= 0xC9) {
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_8003AA20);
            ((void (*)(void *, s32))func_8002F66C)(object, 1);
            func_80041564(object, 0x29);
        } else if (arg1 >= 0xB0) {
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_8003A880);
            func_80041564(object, 0x29);
        } else if (arg1 >= 0x97) {
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_8003A950);
            func_80041564(object, 0x29);
        } else if (arg1 >= 0x3D) {
            ObjectSetCallbackIfAllowed((Batch0CallbackObject *)object,
                                       func_8003AAEC);
        }
    }
}

void func_800390A0(s32, s32, s32, s32);
void FontDrawPaddedNumber(s32, s32, s32, s32);
void func_8003644C(s32, s32, s32, s32);
struct Unk_8003AD08 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};
void func_8003AD08(struct Unk_8003AD08 *arg0) {
    func_800390A0(D_800A3558[0], (s32)D_800A3554[0], 0, 0);
    FontDrawPaddedNumber(D_800A3730, 0x64, 0xC8, 0);
    FontDrawPaddedNumber(D_800A3734, 0xC8, 0xC8, 0);
    func_8003644C(1, D_800A3730 + arg0->unk0, D_800A3734 + arg0->unk4,
                  arg0->unk8);
}

extern s32 D_800A2E60Lap asm("D_800A2E60Absolute");
extern s32 D_800A2EA8Lap asm("D_800A2EA8Absolute");
extern s32 D_800A2EACLap asm("D_800A2EACAbsolute");
extern s32 D_800A2EB0Lap asm("D_800A2EB0Absolute");
extern s32 D_800A2EC0Lap asm("D_800A2EC0Absolute");
extern s32 D_800A2EF4Lap asm("D_800A2EF4Absolute");
extern s8 D_800A2F65Lap asm("D_800A2F65");
extern s32 D_800A2F68Lap asm("D_800A2F68Small");
extern s16 D_800A35A4Lap asm("D_800A35A4Absolute");
extern u8 *D_800A35E0Lap asm("D_800A35E0Absolute");
extern u8 D_800A372CLap asm("D_800A372CAbsolute");
extern s16 D_800A3910Lap asm("D_800A3910Absolute");
extern u8 *D_800BE980Lap asm("D_800BE980");
extern void func_8003EDA0(u8 *);
extern void func_8003CEFC(void);
extern void func_8004E294(void);
extern void func_8004FF3C(void);
extern void func_8003B464(void);

void RaceUpdateLapProgress(void) {
    u8 *car;
    s32 section;
    s16 lastSegment;
    u32 lapTime;
    u32 nextLapTime;
    s32 noPlayerLap;
    s32 fuel;
    u32 currentLapTime;
    u32 bestLapTime;
    s32 lapLimit;
    s16 advancingLap;
    s32 tick;
    s32 totalFuel;
    u8 consumeFuel;
    s32 previousSegment;
    s16 lap;
    u16 playerLap;
    s32 oldProgress;
    s32 progress;
    s32 lapNumber;
    s32 end;

    car = D_800A3878Control;
    D_800A2EF4Lap++;
    noPlayerLap = 1;
    while (car != 0) {
        fuel = 0;
        if (*(s16 *)(car + 0x1EC) == 0) {
            if (!(D_800A2EC0Lap & 31)) {
                /* Compiler control: reserve the shared time temporary. */
                asm("" : "=r"(lapTime));
                fuel = *(s16 *)(car + 0x108) / D_800A2E60Lap;
            }
            if (*(s16 *)(car + 0x1D6) == 2) {
                *(s32 *)(car + 0x294) += fuel;
            }
        }
        totalFuel = *(s32 *)(car + 0x298) + fuel;
        consumeFuel = D_800A372CLap;
        *(s32 *)(car + 0x298) = totalFuel;
        if (consumeFuel == 0) {
            *(s32 *)(car + 0x28C) -= fuel;
        }
        if (*(s32 *)(car + 0x28C) < 0) {
            *(s32 *)(car + 0x28C) = 0;
        }
        section = *(s16 *)(car + 0x1E0);
        if (section == -1) {
            previousSegment = *(s32 *)(car + 0x1F4);
            /* Keep the word load before its signed-short conversion. */
            asm("" : "=r"(previousSegment) : "0"(previousSegment));
            section = (s16)previousSegment;
            *(s16 *)(car + 0x1E0) = previousSegment;
        }
        if (*(s32 *)(car + 0x1F4) == 0 && section >= 11) {
            lap = *(u16 *)(car + 0x1D6) - 1;
            *(s16 *)(car + 0x1D6) = lap;
            if (lap < 0) {
                *(s16 *)(car + 0x1D6) = 0;
            }
        }
        if ((u32)section < 5 && *(s32 *)(car + 0x1F4) >= 11) {
            if (*(s16 *)(car + 0x1D6) == 1) {
                func_8003EDA0(car);
            }
            if (D_800A2EB0Lap == 0 &&
                (lapLimit = D_800A2EA8Lap) < *(s16 *)(D_800A35E0Lap + 0x1D6) &&
                (advancingLap = *(s16 *)(car + 0x1D6)) < lapLimit) {
                *(s16 *)(car + 0x1D6) = advancingLap + 1;
                *(s16 *)(car + 0x41A) = 1;
                if (*(s16 *)(car + 0x1EC) == 0) {
                    func_8002F86C(car, 120);
                }
            } else {
                *(s16 *)(car + 0x1D6) = *(u16 *)(car + 0x1D6) + 1;
            }
            lap = *(s16 *)(car + 0x1D6);
            if (*(s16 *)(car + 0x1D8) < lap) {
                bestLapTime = *(u32 *)(car + 0x25C);
                currentLapTime = *(u32 *)(car + 0x258);
                *(s16 *)(car + 0x1D8) = lap;
                if (currentLapTime < bestLapTime && D_800A2EACLap == 0) {
                    *(u32 *)(car + 0x25C) = currentLapTime;
                    func_8003CEFC();
                }
            }
            if (*(s16 *)(car + 0x1EC) == 0) {
                noPlayerLap = 0;
                func_8004E294();
                func_8004FF3C();
                if (D_800A2EA8Lap >= *(s16 *)(car + 0x1D6)) {
                    if (*(s8 *)(car + 0x204) == 2) {
                        func_80041848(car, 16);
                    } else if (*(s8 *)(car + 0x204) == 3) {
                        func_80041848(car, 18);
                    }
                } else {
                    goto markFinished;
                }
            }
            if (D_800A2EA8Lap < *(s16 *)(car + 0x1D6)) {
            markFinished:
                *(s32 *)(car + 0x414) = -1;
            }
            if (car == D_800A35E0Lap) {
                playerLap = *(u16 *)(car + 0x1D6);
                if (D_800A2EA8Lap < (s16)playerLap) {
                    D_800A3910Lap = 32767;
                    *(u32 *)(car + 0x258) = 0;
                    goto nextCar;
                }
                if ((s16)playerLap < D_800A2EA8Lap && D_800A35A4Lap == 0) {
                    if ((s16)playerLap < 50) {
                        if (((*(s16 *)(car + 0x1D6) % 5) << 16) == 0 &&
                            ((s16)playerLap + 5) % 15 != 0) {
                            func_80041848(
                                car, (s16)(*(s16 *)(car + 0x1D6) / 5) + 29);
                            goto doneLapAnnounce;
                        }
                        lap = *(s16 *)(car + 0x1D6);
                        if ((lap + 4) % 15 == 0) {
                            func_80041848(car, (lap - 1) / 5 + 29);
                            goto doneLapAnnounce;
                        }
                    } else if ((s16)playerLap < 100 &&
                               ((*(s16 *)(car + 0x1D6) % 10) << 16) == 0) {
                        func_80041848(car, ((s16)playerLap - 50) / 10 + 39);
                    }
                }
            }
        doneLapAnnounce:
            *(u32 *)(car + 0x258) = 0;
        }
    nextCar:
        car = *(u8 **)(car + 0x3E0);
    }
    if ((noPlayerLap & 255) && D_800A2EACLap == 0) {
        func_8004E294();
    }
    func_8003B6DC(0);
    car = D_800A3878Control;
    oldProgress = D_800A2F68Lap;
    while (car != 0) {
        section = *(s16 *)(car + 0x1E0);
        lapTime = ((*(u32 *)(car + 0x258) >> 3) + 1) * 8;
        if (RandomScaledGet(8) < 0) {
            nextLapTime = lapTime - RandomScaledGet(8);
        } else {
            nextLapTime = lapTime + RandomScaledGet(8);
        }
        *(u32 *)(car + 0x258) = nextLapTime;
        if (*(s16 *)(car + 0x1D6) > 0) {
            if (D_800A2EA8Lap >= *(s16 *)(car + 0x1D6)) {
                (*(s32 *)(car + 0x260))++;
            }
            if (section >= 0) {
                progress = *(s16 *)(car + 0x1D6) * 1000 + section;
                if (progress >= D_800A2F68Lap) {
                    D_800A2F68Lap = progress;
                    *(s32 *)(D_800BE980Lap + section * 144 + 0x50) =
                        D_800A2EF4Lap;
                }
            }
        }
        car = *(u8 **)(car + 0x3E0);
    }
    if (oldProgress + 1 < D_800A2F68Lap) {
        lapNumber = D_800A2F68Lap / 1000;
        if (lapNumber == oldProgress / 1000) {
            section = oldProgress - lapNumber * 1000 + 1;
            end = D_800A2F68Lap % 1000;
            if (section < end) {
                tick = D_800A2EF4Lap;
                do {
                    *(s32 *)(D_800BE980Lap + section * 144 + 0x50) = tick;
                    section++;
                } while (section < end);
            }
        }
    }
    if (D_800A2F65Lap != 0) {
        func_8003B464();
    }
    car = D_800A3878Control;
    while (car != 0) {
        lastSegment = *(s16 *)(car + 0x1E0);
        if (lastSegment >= 0) {
            *(s32 *)(car + 0x1F4) = lastSegment;
        }
        car = *(u8 **)(car + 0x3E0);
    }
}

extern s32 D_800A2EF4[];
extern u8 D_800A2F65;
extern s32 D_800A35E0[];

void func_8003B464(void) {
    u8 *obj;
    s32 scaled;
    s32 rank;
    s32 startPos;
    s32 next;
    u8 *other;

    if (D_800A2E94[0] == 1) {
        return;
    }
    if (D_800A2EB0Absolute[0] == 1) {
        return;
    }
    obj = (u8 *)D_800A35E0[0];
    while (obj != 0) {
        rank = *(s16 *)(obj + 0x1D6);
        startPos = *(s16 *)(obj + 0x1E0);
        if ((rank = rank) > 0 && startPos >= 0 && *(s8 *)(obj + 0x204) != 1) {
            if (*(s32 *)(obj + 0x3CC) == 0) {
                s32 temp;
                s32 result;
                s32 otherVal;

                temp = D_800A2EF4[0] -
                       *(s32 *)((u8 *)D_800BE980[0] + startPos * 0x90 + 0x50);
                scaled = temp << 3;
                *(s32 *)(obj + 0x264) = temp;
                temp = RandomScaledGet(8);
                if (temp < 0) {
                    result = scaled - RandomScaledGet(8);
                } else {
                    result = scaled + RandomScaledGet(8);
                }
                next = *(s32 *)(obj + 0x3E4);
                *(s32 *)(obj + 0x264) = result;
                other = *(u8 **)(next + 8);
                otherVal = *(s32 *)(other + 0x264);
                if ((u32)otherVal >= (u32)result &&
                    other != (u8 *)D_800A35E0[0]) {
                    *(s32 *)(obj + 0x264) = otherVal + 1;
                }
            } else {
                s32 otherVal;
                s32 objVal;

                next = *(s32 *)(obj + 0x3E4);
                other = *(u8 **)(next + 8);
                if (other == (u8 *)D_800A35E0[0]) {
                    *(s32 *)(other + 0x264) = 0;
                }
                objVal = *(s32 *)(obj + 0x264);
                otherVal = *(s32 *)(other + 0x264);
                if (otherVal >= objVal) {
                    *(s32 *)(obj + 0x264) = otherVal + 1;
                }
            }
        }
        next = *(s32 *)(obj + 0x3E8);
        if (next == 0) {
            break;
        }
        obj = *(u8 **)(next + 8);
    }
    D_800A2F65 = 0;
}

s32 func_8003B5F8(s32 arg0, s32 arg1) {
    volatile s32 pad[2];
    register s32 t2 asm("t2");
    s32 p2;
    register s32 v0 asm("v0");
    register s32 v1 asm("v1");
    register s32 a0 asm("a0");
    register s32 a1 asm("a1");
    register s32 a2 asm("a2");
    register s32 a3 asm("a3");

    v1 = *(s16 *)((u8 *)arg0 + 0x1E0);
    if (arg0 == arg1) {
        return 0;
    }
    if (v1 == -1) {
        return 0;
    }
    a1 = D_800BE980[0];
    v0 = (v1 << 3) + v1;
    v0 = v0 << 4;
    a1 = a1 + v0;
    a0 = *(u16 *)((u8 *)a1 + 0x10);
    v1 = D_800A3A2CAbsolute[0];
    v0 = 0x400;
    a2 = *(s32 *)((u8 *)a1 + 0x14);
    v0 = v0 - a0;
    v0 = v0 & 0x3FF;
    v0 = v0 << 2;
    v1 = v0 + v1;
    asm volatile("" : : "r"(v1));
    a0 = *(s32 *)((u8 *)arg0 + 0);
    a3 = *(s32 *)(u8 *)v1;
    v1 = a0 - a2;
    asm volatile("mult\t%0, %1" : : "r"(a3), "r"(v1) : "hi", "lo");
    v1 = D_800A3A34Absolute[0];
    a0 = *(s32 *)((u8 *)a1 + 0x18);
    v0 = v0 + v1;
    v1 = *(s32 *)((u8 *)arg0 + 4);
    a1 = *(s32 *)(u8 *)v0;
    asm volatile("mflo\t%0" : "=r"(t2) : : "lo");
    v0 = v1 - a0;
    asm volatile("mult\t%0, %1" : : "r"(a1), "r"(v0) : "hi", "lo");
    v0 = *(s32 *)((u8 *)arg1 + 0);
    asm volatile("mflo\t%0" : "=r"(p2) : : "lo");
    v1 = v0 - a2;
    asm volatile("mult\t%0, %1" : : "r"(a3), "r"(v1) : "hi", "lo");
    v0 = *(s32 *)((u8 *)arg1 + 4);
    asm volatile("mflo\t%0" : "=r"(a2) : : "lo");
    v0 = v0 - a0;
    asm volatile("mult\t%0, %1" : : "r"(a1), "r"(v0) : "hi", "lo");
    v1 = t2 - p2;
    v1 = v1 >> 16;
    asm volatile("mflo\t%0" : "=r"(a3) : : "lo");
    v0 = a2 - a3;
    v0 = v0 >> 16;
    return v0 < v1;
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8003B6DC);

extern void func_8002D4CC();
extern s32 D_800BE72C[];
extern s32 D_800BE730[];
extern s16 D_800BE738[];
extern s32 D_800A2F60;

void func_8003BCAC(void) {
    s32 count;
    s32 offset;
    u8 *object;

    object = *(u8 **)(((u8 **)D_800A3854Absolute)[9] + 0x3E0);
    count = 0;
    if (object != 0) {
        offset = 0;
        do {
            func_8002D4CC(object);
            *(s32 *)(object + 0) = *(s32 *)((u8 *)D_800BE72C + offset);
            *(s32 *)(object + 4) = *(s32 *)((u8 *)D_800BE730 + offset);
            *(s32 *)(object + 8) = 0;
            func_80022FB8(object, *(s16 *)((u8 *)D_800BE738 + offset));
            object = *(u8 **)(object + 0x3E0);
            count += 1;
            offset += 0x10;
        } while (object != 0);
    }
    object = ((u8 **)D_800A3854Absolute)[9];
    *(s32 *)(object + 0) = *(s32 *)((u8 *)D_800BE72C + count * 0x10);
    *(s32 *)(object + 4) = *(s32 *)((u8 *)D_800BE730 + count * 0x10);
    *(s32 *)(object + 8) = 0;
    func_8002D4CC(object);
    func_80022FB8(object, *(s16 *)((u8 *)D_800BE738 + count * 0x10));
    D_800A2F60 = 0x14;
    func_8001D1E4();
    D_800A2EACAbsolute[0] = 0;
    func_8003B6DC(1);
}

INCLUDE_ASM("asm/nonmatchings/objects", func_8003BDBC);

extern u8 *D_800A3878nm[] asm("D_800A3878.NON_MATCHING");
extern u8 D_800B0B1C[];
extern void func_8003BDBC(void);

void func_8003C1CC(void) {
    u8 *car;
    u8 *base;
    u8 *dst;
    s32 *out2;
    s32 *out3;
    u8 *out1;
    s32 off;
    s32 rank;
    s32 idx;
    s32 slot;
    s32 mode;
    u8 *head;
    s32 val;
    s32 laps;

    func_8002F454();
    base = D_800B0B1C;
    if (D_800A2EB0Absolute[0] == 0) {
        rank = 0;
        if (D_800A2EA4[0] == 0) {
            rank = D_800A2EA8[0] >= *(s16 *)(D_800A3554[0] + 0x1D6);
        } else {
            head = D_800A3554[0];
            if (D_800A2EA8[0] >= *(s16 *)(head + 0x1D6) &&
                D_800A2EA8[0] >= *(s16 *)(*(u8 **)(head + 0x3E0) + 0x1D6)) {
                rank = 1;
            }
        }
        if (rank == 1) {
            func_8003BDBC();
        }
        rank = 0;
        if (rank < D_800A2E94[0]) {
            out3 = (s32 *)base;
            off = 0;
            out2 = D_800AE1EC;
            out1 = D_800BE70C;
            idx = 1;
            do {
                car = D_800A3878nm[0];
                slot = idx;
                if (*(s8 *)(car + 0x204) != idx) {
                    do {
                        car = *(u8 **)(car + 0x3E0);
                    } while (*(s8 *)(car + 0x204) != slot);
                }
                *out1 = *(u8 *)(car + 0x376);
                val = *(s32 *)(car + 0x25C);
                mode = D_800A2EA4[0];
                *out2 = val;
                if (mode == 2) {
                    if (*(u8 *)(car + 0xF4) != 0) {
                        if (*(s16 *)(car + 0x1D6) == 0) {
                            dst = (u8 *)(off + (s32)base);
                            asm volatile("" : "=r"(dst) : "0"(dst));
                            *(s32 *)dst =
                                -*(s16 *)((u8 *)D_800A35E0[0] + 0x1D6);
                            goto tailSkip;
                        }
                        goto general;
                    }
                    val = -1;
                } else {
                general:
                    if (*(u8 *)(car + 0xF4) != 0) {
                        laps = *(s16 *)(car + 0x1D6) -
                               *(s16 *)((u8 *)D_800A35E0[0] + 0x1D6);
                        val = laps + 1;
                        if (*(u16 *)(car + 0x41A) != 0) {
                            val = laps;
                        }
                        if (val < 0) {
                            val = val - 1;
                        } else if (*(s8 *)(car + 0x204) == 1) {
                            val = *(s32 *)(car + 0x260) << 3;
                        } else {
                            *out3 = *(s32 *)(car + 0x264);
                            goto tailSkip;
                        }
                    } else {
                        *out3 = -1;
                        goto tailSkip;
                    }
                }
                *out3 = val;
            tailSkip:
                out3 += 1;
                off += 4;
                out2 += 1;
                out1 += 1;
                idx += 1;
                rank += 1;
            } while (rank < D_800A2E94[0]);
        }
    }
}

extern u8 D_800B9DA4[];
/* A second name keeps cse from sharing one la across the reads. */
extern u8 *D_800A3554nm[] asm("D_800A3554.NON_MATCHING");

/*
 * The search and rebuild loops are goto loops on purpose: without loop notes
 * count's refs aren't weighted, so i outranks it in global-alloc (a1, a2).
 * i is set a third time by count + 1, which keeps sched1 from sinking it.
 */
void func_8003C3FC(void) {
    s32 *words;
    u8 *bytes;
    s32 *p;
    s32 *out;
    s32 *wp;
    u8 *bp;
    u8 *obj;
    s32 limit;
    s32 count;
    s32 i;

    bytes = D_800BE70C;
    words = D_800AE1EC;
    func_8002F454();
    limit = *(s32 *)(D_800A3554[0] + 0x25C);
    count = 0;
    p = words;
head:
    if ((u32)*p >= (u32)limit) {
        goto done;
    }
    count += 1;
    p += 1;
    if (count < 0x17) {
        goto head;
    }
done:
    if (count < 0x17) {
        i = 0x17;
        do {
            bytes[i] = bytes[i - 1];
            words[i] = words[i - 1];
            i -= 1;
        } while (count < i);
    }
    bytes[count] = *(u8 *)(D_800A3554[0] + 0x376);
    obj = D_800A3554nm[0];
    words[count] = *(s32 *)(obj + 0x25C);
    i = count + 1;
    *(u8 *)(obj + 0x204) = i;
    out = (s32 *)D_800B0B1C;
    wp = words;
    bp = bytes;
    count = 0;
loop:
    D_800B9DA4[*bp] = count;
    *out = *wp;
    bp += 1;
    wp += 1;
    out += 1;
    count += 1;
    if (count < 0x18) {
        goto loop;
    }
}
