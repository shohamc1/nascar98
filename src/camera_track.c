#include "common.h"
#include "libpress.h"
#include "memory_map.h"
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
#include "car.h"
#include "cd.h"
#include "graphics.h"
#include "list.h"
#include "objects.h"
#include "scene.h"
#include "sound.h"
#include "util.h"
extern s32 gCrashCarAbsolute2[];
extern s16 gCdVolumeAbsolute3[];
extern s32 D_800A38ACAbsolute2[];
extern s32 D_800A38ACAbsolute3[];
extern s32 D_800A38ACAbsolute4[];
extern s32 D_800A38ACAbsolute5[];
extern char gCdAnnouncerAbsolute2[];
extern s32 D_800A2F3CAbsolute2[];
extern s32 D_800A2D08Absolute3[];
extern s32 D_800A2D08Absolute4[];
extern s32 gReplayLengthAbsolute[];

extern u8 D_800A2F58Absolute[];
extern s32 D_800A36B0Absolute[];
extern s32 D_800A36B8Absolute[];
extern s32 D_800A36C8Absolute[];
extern u8 D_800A2DE1Absolute[];
void func_8003A54C(void);

void func_800365B8(s32 *out);
void SoundStopConditionalSlots(s8 arg0);
void CarUpdateEngineRpm(Car *obj);
void func_8003667C(u32 *list);
void func_80041328(void);
void func_8002B538(Car *arg0);
void CarUpdateDraft(Car *car);
void func_8002B258(Car *arg0);
void func_8003A440(void);
void CarUpdateAi(Car *arg0);
void CarUpdateTrackSideOffsets(void);
void CarUpdateState(Car *object);
void func_80034990(void);
void func_80035B20(void);
void RaceUpdateLapProgress(void);
void CameraUpdateHorizon(void);
void func_80034834(void);

extern u16 D_800A38C0[];
extern s32 D_800A2E90w15[] asm("D_800A2E90.NON_MATCHING");
extern u8 D_800A2EE4w15[] asm("D_800A2EE4.NON_MATCHING");
extern u8 D_800A2EDAw15[] asm("D_800A2EDA.NON_MATCHING");

extern s32 gOrderingTable[];
extern s32 gSplitScreenModenm[] asm("gSplitScreenMode.NON_MATCHING");
extern s32 *gSinTableAbsolute[];

extern Face *D_800A3A40Absolute[];
extern s32 D_800A2EC4w15[] asm("D_800A2EC4.NON_MATCHING");
void func_8001D108(TrackSection *arg0);
void func_8001D1E4(void);
void func_8001ED4C(s32 *p);
void func_8001EEC4(Car *arg0);
void func_8001F198(void);
void func_8001F5BC(s32 arg0, s32 indexA, s32 indexB);
void CameraBuildRotationMatrix(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8001F728(Vec3 *arg0);
void func_8001F828(s32 *p);
void MatrixStoreObjectBasis(Car *arg0);
void MatrixSetRotationFromAngle(Car *arg0, s32 index);
void func_8001FB28(Car *arg0, s32 index);

extern s32 *gCosTableAbsolute[];
s32 VectorGetMagnitude2D(Car *object) {
    s32 dx;
    s32 dy;

    dx = object->toCamera.x;
    dy = object->toCamera.y;
    return MathSqrt(dx * dx + dy * dy);
}

static const char sReplayAllocError[] = "Error: No memory for instant replay!";
extern u32 D_800A38F4Abs[] asm("D_800A38F4.NON_MATCHING");
extern s32 D_800A2DE4Small asm("D_800A2DE4.NON_MATCHING");
extern s32 gReplayBufferSmall asm("gReplayBuffer.NON_MATCHING");
extern s32 D_800A37E8Small asm("D_800A37E8.NON_MATCHING");
extern s32 gReplayHeadSmall asm("gReplayHead.NON_MATCHING");
extern s32 D_800A3804Small asm("D_800A3804.NON_MATCHING");
extern s32 gReplayIndexSmall asm("gReplayIndex.NON_MATCHING");
extern s32 D_800A2DECSmall asm("D_800A2DEC.NON_MATCHING");
extern s32 D_800A397CSmall asm("D_800A397C.NON_MATCHING");
extern s32 D_800A2DF0Small asm("D_800A2DF0.NON_MATCHING");
extern s32 D_800A2DF4Small asm("D_800A2DF4.NON_MATCHING");
extern s32 gReplayLengthSmall asm("gReplayLength.NON_MATCHING");

void ReplayAllocBuffer(void) {
    s32 count;
    void *ptr;
    s32 quotient;

    count = D_800A38F4Abs[0] / 20;
    D_800A2DE4Small = count;
    ptr = HeapAlloc(count * 20);
    gReplayBufferSmall = (s32)ptr;
    if (ptr == 0) {
        SystemShowFatalError(sReplayAllocError);
    }
    quotient = D_800A2DE4Small / (D_800A2E94[0] + 6);
    D_800A37E8Small = 0;
    gReplayHeadSmall = 0;
    D_800A3804Small = 0;
    gReplayIndexSmall = 0;
    D_800A2ED4[0] = 0;
    D_800A2EC8[0] = 0;
    D_800A2DECSmall = 0;
    D_800A397CSmall = 1;
    D_800A2DF0Small = 1;
    D_800A2DF4Small = 1;
    gReplayLengthSmall = quotient;
}

/* Shared layout of a car and the camera that follows it. */

extern u8 D_800A3680[];
extern void func_80025730(Car *);

/* Steps a car to its next camera view. ReplayHandleInput inlines it three times. */
static __inline__ void CameraCycleMode(Car *car) {
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

void CameraCycleModeCallback(Car *car) {
    CameraCycleMode(car);
}

void func_8001FDD0(Car *cam, Car *car) {
    u32 dist3;
    u32 dist2;
    s32 cosPitch;
    s32 sinPitch;
    s32 cosYaw;

    MatrixLoadObjectBasis((s32 *)cam);
    car->toCamera.x = car->pos.x - cam->pos.x;
    car->toCamera.y = car->pos.y - cam->pos.y;
    car->toCamera.z = car->pos.z - cam->pos.z;
    MatrixTransformVector((s32 *)&car->toCamera);
    dist3 = MathSqrt(car->toCamera.x * car->toCamera.x +
                     car->toCamera.y * car->toCamera.y +
                     car->toCamera.z * car->toCamera.z);
    dist2 = MathSqrt(car->toCamera.x * car->toCamera.x +
                     car->toCamera.y * car->toCamera.y);
    cosPitch = MathFixedDivide(dist2, dist3);
    sinPitch = MathFixedDivide(car->toCamera.z, dist3);
    cosYaw = MathFixedDivide(car->toCamera.x, dist2);
    CameraBuildRotationMatrix(cosYaw, MathFixedDivide(car->toCamera.y, dist2),
                              cosPitch, sinPitch);
    func_8001F728(&cam->rot[0]);
    func_8001F728(&cam->rot[1]);
    func_8001F728(&cam->rot[2]);
}

void func_8001FF3C(Car *camera, Car *car) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 value0;
    s32 value1;
    s32 value2;
    s32 value3;
    s32 value4;

    sp18 = -1;
    if ((s16)TrackFindSection(camera->pos.x, camera->pos.y, &sp18, &sp1C,
                              &sp20) == -1) {
        value0 = MathMultiplyFixed16(car->unkDC.x, ((s32)camera->pos.x >> 2)
                                                       << 0x10);
        value4 = MathMultiplyFixed16(car->unkDC.y, ((s32)camera->pos.y >> 2)
                                                       << 0x10);
        value3 = MathMultiplyFixed16(car->unkDC.z, ((s32)camera->pos.z >> 2)
                                                       << 0x10);
        value1 =
            MathMultiplyFixed16(car->unkDC.x, ((s32)car->pos.x >> 2) << 0x10);
        value2 =
            MathMultiplyFixed16(car->unkDC.y, ((s32)car->pos.y >> 2) << 0x10);
        sp1C = ((((s32)camera->pos.z >> 2) -
                 ((s32)((value0 + value4 + value3) -
                        (value1 + value2 +
                         MathMultiplyFixed16(
                             car->unkDC.z, ((s32)car->pos.z >> 2) << 0x10))) >>
                  0x10)) *
                4) +
               0x12C;
    } else {
        sp1C = (sp1C * 4) + 0x12C;
    }
    if (camera->pos.z < sp1C) {
        camera->pos.z = sp1C;
    }
}

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    u8 unkC[0x4C];
} TrackPoint;

/* One 0x90-byte entry of the array at gTrackSections. */
/* TrackSection as the route code reads it: the word at 0x10 holds the
 * angle in its low 16 bits and the point index in bits 17 to 23. */
typedef struct {
    u8 unk0[0x10];
    u32 unk10 : 17;
    u32 point : 7;
    u32 unk10Top : 8;
    s32 x;
    s32 z;
    u8 unk1C[0x4];
    u8 *unk20;
    u8 unk24[0x6C];
} TrackSectionPoint;

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
extern FarVar gFarMode2EA4 asm("gSplitScreenMode");
extern FarVar gFarMode2CE0 asm("D_800A2CE0.NON_MATCHING");
extern FarVar gFarBlend2EAC asm("D_800A2EAC.NON_MATCHING");
extern FarVar gFarTrack asm("gTrackSections");
extern FarVar gFarPlayer asm("D_800A38AC");
extern FarVar gFarOffsetX asm("D_800AE844");
extern FarVar gFarOffsetY asm("D_800AE848");
extern FarVar gFarOffsetZ asm("D_800AE84C");
extern FarVar gFarCosTable asm("gCosTableAbsolute");
extern FarVar gFarSinTable asm("gSinTableAbsolute");
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
        MatrixLoadObjectBasis((s32 *)(cam));                                   \
        (car)->toCamera.x = (car)->pos.x - (cam)->pos.x;                       \
        (car)->toCamera.y = (car)->pos.y - (cam)->pos.y;                       \
        (car)->toCamera.z = (car)->pos.z - (cam)->pos.z;                       \
        MatrixTransformVector((s32 *)&(car)->toCamera);                        \
        dist3 = MathSqrt((car)->toCamera.x * (car)->toCamera.x +               \
                         (car)->toCamera.y * (car)->toCamera.y +               \
                         (car)->toCamera.z * (car)->toCamera.z);               \
        dist2 = MathSqrt((car)->toCamera.x * (car)->toCamera.x +               \
                         (car)->toCamera.y * (car)->toCamera.y);               \
        cosPitch = MathFixedDivide(dist2, dist3);                              \
        sinPitch = MathFixedDivide((car)->toCamera.z, dist3);                  \
        cosYaw = MathFixedDivide((car)->toCamera.x, dist2);                    \
        CameraBuildRotationMatrix(cosYaw,                                      \
                                  MathFixedDivide((car)->toCamera.y, dist2),   \
                                  cosPitch, sinPitch);                         \
        func_8001F728((s32)(row0));                                            \
        func_8001F728((s32)(row1));                                            \
        func_8001F728((s32)(row2));                                            \
    }

/* Update the camera for one car and camera mode. */
void CameraUpdateForCar(Car *cam, Car *car, s32 mode) {
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
    TrackSectionPoint *track;
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
        if (car->mode == 4) {
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
            func_8001FF3C(cam, car);
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
            func_8001FF3C(cam, car);
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
            func_8001FF3C(cam, car);
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
            func_8001FF3C(cam, car);
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
        index = car->segment;
        if (index >= 0) {
            point = FAR_VAR(TrackSectionPoint *, gFarTrack)[index].point;
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
        MatrixSetIdentity((s32 *)cam);
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
        func_8001F728(&cam->rot[0]);
        func_8001F728(&cam->rot[1]);
        func_8001F728(&cam->rot[2]);
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
        if ((car->segment >= D_800A3584nm[index] + 1 ||
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
        MatrixSetIdentity((s32 *)cam);
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
            to = (s16 *)((TrackSection *)FAR_VAR(u8 *, gFarTrack))[19].unk78[0];
            from =
                (s16 *)((TrackSection *)FAR_VAR(u8 *, gFarTrack))[19].unk78[5];
        } else {
            to = (s16 *)((TrackSection *)FAR_VAR(u8 *, gFarTrack))[27].unk78[0];
            from =
                (s16 *)((TrackSection *)FAR_VAR(u8 *, gFarTrack))[27].unk78[5];
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
        MatrixSetIdentity((s32 *)cam);
        CAMERA_LOOK_AT(cam, car, &cam->rot[0], &cam->rot[1], &cam->rot[2]);
        break;
    case 17:
        cam->basis[0] = car->basis[0];
        cam->rot[0] = cam->basis[0];
        cam->basis[1] = car->basis[1];
        cam->rot[1] = cam->basis[1];
        cam->basis[2] = car->basis[2];
        cam->rot[2] = cam->basis[2];
        track = FAR_VAR(TrackSectionPoint *, gFarTrack);
        point = track->point;
        pos[0] = track->x;
        pos[1] = track->z;
        pos[2] = ((Face *)track->unk20)->vertex[0]->vz;
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
        MatrixSetIdentity((s32 *)cam);
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
        ((Car *)FAR_VAR(u8 *, gFarPlayer))->segment = 0;
        break;
    }
}

extern s32 D_800A37E0Record asm("D_800A37E0.NON_MATCHING");
extern Car *gCarListRecord[] asm("gCarList.NON_MATCHING");
extern Car *D_800A3960Record[] asm("gCrashCar.NON_MATCHING");
extern Car *gPlayerCarRecord[] asm("gPlayerCar.NON_MATCHING");

void func_8002267C(void) {
    Car *node;
    s32 base;
    Car *curCar;
    Car *car;
    ReplayFrame *rec;
    u32 bits;

    node = gCarListRecord[0];
    if (D_800A397CSmall != 1) {
        return;
    }
    if (node != 0) {
        base = (s32)gReplayBufferSmall;
        curCar = D_800A3960Record[0];
        car = gPlayerCarRecord[0];
        do {
            if (node->type >= 0) {
                rec = (u8 *)(D_800A37E8Small * 20 + base);
                *(s32 *)rec = node->pos.x;
                rec->y = node->pos.y;
                rec->unkC = node->unk3A4;
                rec->speed =
                    ((node->speed / 2 >> 16) << 7) | node->reverseSpeed;
                bits = (node->heading << 22) | ((node->steering + 0x80) << 14) |
                       ((node->unk3AE[0] & 3) << 12) |
                       ((node->unk3AE[1] & 3) << 10) |
                       ((node->unk3AE[2] & 3) << 8) |
                       ((node->unk3AE[3] & 3) << 6) | (node->gearIndex << 4) |
                       ((s8)node->unk3B9 << 3) | (node->sliding << 2);
                if (curCar == car) {
                    bits |= 1;
                } else if (gSplitScreenModenm[0] != 0 && curCar == car->next) {
                    bits |= 0x10;
                }
                ((ReplayFrame *)(D_800A37E8Small * 20 + base))->state = bits;
                ((ReplayFrame *)(D_800A37E8Small * 20 + base))->unk10 =
                    ((((u16)node->unkFE << 16) >> 17) + 0x800 << 20) |
                    (node->unk388 << 10) | node->unk38A;
                if (node->type == 1) {
                    if (node->segment != -1) {
                        node->unkC = node->pos.x;
                        node->unk10 = node->pos.y;
                        node->unk14 = node->pos.z;
                    }
                } else if (node->segment != -1 &&
                           node->frontRightContact != 0 &&
                           node->frontLeftContact != 0 &&
                           node->rearRightContact != 0 &&
                           node->rearLeftContact != 0) {
                    node->unkC = node->pos.x;
                    node->unk10 = node->pos.y;
                    node->unk14 = node->pos.z;
                }
                D_800A37E8Small = D_800A37E8Small + 1;
                D_800A37E0Record = D_800A37E8Small;
            }
            node = node->next;
        } while (node != 0);
    }
    func_800365B8((u8 *)gReplayBufferSmall + D_800A37E8Small * 20);
    ReplayWriteEffects((u8 *)gReplayBufferSmall +
                       (D_800A37E8Small * 20 + 0x50));
    gReplayHeadSmall = (gReplayHeadSmall + 1) % gReplayLengthSmall;
    D_800A37E8Small = D_800A37E8Small + 6;
    D_800A37E0Record = D_800A37E8Small;
    D_800A37E8Small = gReplayHeadSmall * (D_800A2E94[0] + 6);
    if (D_800A3804Small == gReplayHeadSmall) {
        D_800A3804Small = (D_800A3804Small + 1) % gReplayLengthSmall;
    }
}

extern Car *gCarListw15[] asm("gCarList.NON_MATCHING");
extern Car *D_800A3960w15[] asm("gCrashCar.NON_MATCHING");
extern Car *gPlayerCar[];

#ifdef NATIVE
/* The matching C drops func_800442C8's frame; the asm leaves it in a1. */
void ReplayStepForward(void) {
    Car *node;
    u8 *baseAddr;
    register u8 *rec;
    s32 count;
    s32 offset;
    u32 bits;
    u32 w2;
    register u16 val;
    s32 v90;
    s32 t114;
    s32 i;

    count = gReplayIndexSmall;
    gReplayIndexSmall = (count + 1) % gReplayLengthSmall;
    if (gReplayIndexSmall == gReplayHeadSmall) {
        gReplayIndexSmall = count;
        D_800A2ED4[0] = 1;
        SoundStopConditionalSlots(0);
        return;
    }
    count = gReplayIndexSmall * (D_800A2E94[0] + 6);
    node = gCarListw15[0];
    if (node != 0) {
        offset = count * 20;
        do {
            if (node->type >= 0) {
                rec = (u8 *)gReplayBufferSmall;
                rec = (u8 *)(offset + (s32)rec);
                node->pos.x = ((ReplayFrame *)rec)->x;
                node->pos.y = ((ReplayFrame *)rec)->y;
                func_800442C8(node, (ReplayFrame *)rec);
                val = *(u16 *)(u8 *)(offset + gReplayBufferSmall + 0xE);
                node->reverseSpeed = val & 0x7F;
                baseAddr = (u8 *)gReplayBufferSmall;
                v90 = (val >> 7) << 17;
                node->speed = v90;
                bits = *(s32 *)(u8 *)(offset + (s32)baseAddr + 8);
                node->fineHeading = (bits >> 22) * 4;
                val = bits >> 22;
                node->steering = ((bits >> 14) & 0xFF) - 0x80;
                node->gearIndex = (bits & 0x3F) >> 4;
                node->unk3B9 = (bits & 0xF) >> 3;
                node->sliding = (bits & 7) >> 2;
                node->unk102 = val;
                node->heading = val;
                if ((bits & 3) == 1) {
                    D_800A3960w15[0] = gPlayerCar[0];
                } else if ((bits & 3) == 2) {
                    D_800A3960w15[0] = gPlayerCar[0]->next;
                } else {
                    D_800A3960w15[0] = 0;
                }
                w2 = *(s32 *)(u8 *)(offset + gReplayBufferSmall + 0x10);
                node->unkFE = ((w2 >> 20) - 0x800) * 2;
                for (i = 0; i < 4; i++) {
                    node->wheel[i].unk0 = (u16)node->unkFE;
                }
                t114 = node->heading;
                node->unk388 = (w2 << 12) >> 22;
                node->unk38A = w2 & 0x3FF;
                func_8001F2C4(t114, 0, 0);
                func_8001F828((s32 *)node);
                MatrixStoreObjectBasis(node);
                node->unk228 = 0;
                node->movementHeading = (u16)node->heading;
                CarUpdateEngineRpm(node);
                offset += 0x14;
                count += 1;
            }
            node = node->next;
        } while (node != 0);
    }
    i = (gReplayIndexSmall + 1) % gReplayLengthSmall;
    if (i == gReplayHeadSmall) {
        D_800A2ED4[0] = 1;
    }
    func_8003667C((u8 *)gReplayBufferSmall + count * 20);
    ReplayReadEffects((u8 *)gReplayBufferSmall + (count * 20 + 0x50));
}
#else
void ReplayStepForward(void) {
    Car *node;
    u8 *baseAddr;
    register u8 *rec asm("a1");
    s32 count;
    s32 offset;
    u32 bits;
    u32 w2;
    register u16 val asm("v1");
    s32 v90;
    s32 t114;
    s32 i;

    count = gReplayIndexSmall;
    gReplayIndexSmall = (count + 1) % gReplayLengthSmall;
    if (gReplayIndexSmall == gReplayHeadSmall) {
        gReplayIndexSmall = count;
        D_800A2ED4[0] = 1;
        SoundStopConditionalSlots(0);
        return;
    }
    count = gReplayIndexSmall * (D_800A2E94[0] + 6);
    node = gCarListw15[0];
    if (node != 0) {
        offset = count * 20;
        do {
            if (node->type >= 0) {
                rec = (u8 *)gReplayBufferSmall;
                rec = (u8 *)(offset + (s32)rec);
                node->pos.x = ((ReplayFrame *)rec)->x;
                node->pos.y = ((ReplayFrame *)rec)->y;
                func_800442C8(node);
                val = *(u16 *)(u8 *)(offset + gReplayBufferSmall + 0xE);
                node->reverseSpeed = val & 0x7F;
                baseAddr = (u8 *)gReplayBufferSmall;
                v90 = (val >> 7) << 17;
                node->speed = v90;
                bits = *(s32 *)(u8 *)(offset + (s32)baseAddr + 8);
                node->fineHeading = (bits >> 22) * 4;
                val = bits >> 22;
                node->steering = ((bits >> 14) & 0xFF) - 0x80;
                node->gearIndex = (bits & 0x3F) >> 4;
                node->unk3B9 = (bits & 0xF) >> 3;
                node->sliding = (bits & 7) >> 2;
                node->unk102 = val;
                node->heading = val;
                if ((bits & 3) == 1) {
                    D_800A3960w15[0] = gPlayerCar[0];
                } else if ((bits & 3) == 2) {
                    D_800A3960w15[0] = gPlayerCar[0]->next;
                } else {
                    D_800A3960w15[0] = 0;
                }
                w2 = *(s32 *)(u8 *)(offset + gReplayBufferSmall + 0x10);
                node->unkFE = ((w2 >> 20) - 0x800) * 2;
                for (i = 0; i < 4; i++) {
                    node->wheel[i].unk0 = (u16)node->unkFE;
                }
                t114 = node->heading;
                node->unk388 = (w2 << 12) >> 22;
                node->unk38A = w2 & 0x3FF;
                func_8001F2C4(t114, 0, 0);
                func_8001F828((s32 *)node);
                MatrixStoreObjectBasis(node);
                node->unk228 = 0;
                node->movementHeading = (u16)node->heading;
                CarUpdateEngineRpm(node);
                offset += 0x14;
                count += 1;
            }
            node = node->next;
        } while (node != 0);
    }
    i = (gReplayIndexSmall + 1) % gReplayLengthSmall;
    if (i == gReplayHeadSmall) {
        D_800A2ED4[0] = 1;
    }
    func_8003667C((u8 *)gReplayBufferSmall + count * 20);
    ReplayReadEffects((u8 *)gReplayBufferSmall + (count * 20 + 0x50));
}
#endif

#ifdef NATIVE
/* The matching C drops func_800442C8's frame; the asm leaves it in a1. */
void ReplayStepBack(void) {
    Car *node;
    register u8 *rec;
    u8 *p;
    s32 current;
    s32 count;
    u8 *baseAddr;
    s32 offset;
    u32 bits;
    u32 w2;
    s32 d;
    s32 dm1;
    register u16 val;
    s32 v90;
    s32 t114;
    s32 i;

    current = gReplayIndexSmall;
    if (current != D_800A3804Small) {
        d = gReplayLengthSmall;
        dm1 = d - 1;
        gReplayIndexSmall = (current + dm1) % d;
    } else {
        D_800A2ED4[0] = 1;
        SoundStopConditionalSlots(0);
    }
    count = gReplayIndexSmall * (D_800A2E94[0] + 6);
    node = gCarListw15[0];
    if (node != 0) {
        offset = count * 20;
        do {
            if (node->type >= 0) {
                rec = (u8 *)gReplayBufferSmall;
                rec = (u8 *)(offset + (s32)rec);
                node->pos.x = ((ReplayFrame *)rec)->x;
                node->pos.y = ((ReplayFrame *)rec)->y;
                func_800442C8(node, (ReplayFrame *)rec);
                val = *(u16 *)(u8 *)(offset + gReplayBufferSmall + 0xE);
                node->reverseSpeed = val & 0x7F;
                baseAddr = (u8 *)gReplayBufferSmall;
                v90 = (val >> 7) << 17;
                node->speed = v90;
                bits = *(s32 *)(u8 *)(offset + (s32)baseAddr + 8);
                node->fineHeading = (bits >> 22) * 4;
                val = bits >> 22;
                node->steering = ((bits >> 14) & 0xFF) - 0x80;
                node->gearIndex = (bits & 0x3F) >> 4;
                node->unk3B9 = (bits & 0xF) >> 3;
                node->sliding = (bits & 7) >> 2;
                node->unk102 = val;
                node->heading = val;
                if ((bits & 3) == 1) {
                    D_800A3960w15[0] = gPlayerCar[0];
                } else if ((bits & 3) == 2) {
                    D_800A3960w15[0] = gPlayerCar[0]->next;
                } else {
                    D_800A3960w15[0] = 0;
                }
                w2 = *(s32 *)(u8 *)(offset + gReplayBufferSmall + 0x10);
                node->unkFE = ((w2 >> 20) - 0x800) * 2;
                for (i = 0; i < 4; i++) {
                    node->wheel[i].unk0 = (u16)node->unkFE;
                }
                t114 = node->heading;
                node->unk388 = (w2 << 12) >> 22;
                node->unk38A = w2 & 0x3FF;
                func_8001F2C4(t114, 0, 0);
                func_8001F828((s32 *)node);
                MatrixStoreObjectBasis(node);
                node->unk228 = 0;
                node->movementHeading = (u16)node->heading;
                CarUpdateEngineRpm(node);
                offset += 0x14;
                count += 1;
            }
            node = node->next;
        } while (node != 0);
    }
    func_8003667C((u8 *)gReplayBufferSmall + count * 20);
    ReplayReadEffects((u8 *)gReplayBufferSmall + (count * 20 + 0x50));
}
#else
void ReplayStepBack(void) {
    Car *node;
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

    current = gReplayIndexSmall;
    if (current != D_800A3804Small) {
        d = gReplayLengthSmall;
        dm1 = d - 1;
        gReplayIndexSmall = (current + dm1) % d;
    } else {
        D_800A2ED4[0] = 1;
        SoundStopConditionalSlots(0);
    }
    count = gReplayIndexSmall * (D_800A2E94[0] + 6);
    node = gCarListw15[0];
    if (node != 0) {
        offset = count * 20;
        do {
            if (node->type >= 0) {
                rec = (u8 *)gReplayBufferSmall;
                rec = (u8 *)(offset + (s32)rec);
                node->pos.x = ((ReplayFrame *)rec)->x;
                node->pos.y = ((ReplayFrame *)rec)->y;
                func_800442C8(node);
                val = *(u16 *)(u8 *)(offset + gReplayBufferSmall + 0xE);
                node->reverseSpeed = val & 0x7F;
                baseAddr = (u8 *)gReplayBufferSmall;
                v90 = (val >> 7) << 17;
                node->speed = v90;
                bits = *(s32 *)(u8 *)(offset + (s32)baseAddr + 8);
                node->fineHeading = (bits >> 22) * 4;
                val = bits >> 22;
                node->steering = ((bits >> 14) & 0xFF) - 0x80;
                node->gearIndex = (bits & 0x3F) >> 4;
                node->unk3B9 = (bits & 0xF) >> 3;
                node->sliding = (bits & 7) >> 2;
                node->unk102 = val;
                node->heading = val;
                if ((bits & 3) == 1) {
                    D_800A3960w15[0] = gPlayerCar[0];
                } else if ((bits & 3) == 2) {
                    D_800A3960w15[0] = gPlayerCar[0]->next;
                } else {
                    D_800A3960w15[0] = 0;
                }
                w2 = *(s32 *)(u8 *)(offset + gReplayBufferSmall + 0x10);
                node->unkFE = ((w2 >> 20) - 0x800) * 2;
                for (i = 0; i < 4; i++) {
                    node->wheel[i].unk0 = (u16)node->unkFE;
                }
                t114 = node->heading;
                node->unk388 = (w2 << 12) >> 22;
                node->unk38A = w2 & 0x3FF;
                func_8001F2C4(t114, 0, 0);
                func_8001F828((s32 *)node);
                MatrixStoreObjectBasis(node);
                node->unk228 = 0;
                node->movementHeading = (u16)node->heading;
                CarUpdateEngineRpm(node);
                offset += 0x14;
                count += 1;
            }
            node = node->next;
        } while (node != 0);
    }
    func_8003667C((u8 *)gReplayBufferSmall + count * 20);
    ReplayReadEffects((u8 *)gReplayBufferSmall + (count * 20 + 0x50));
}
#endif

void ReplayStepForward(void);

void ReplayStepForwardFourFrames(void) {
    ReplayStepForward();
    ReplayStepForward();
    ReplayStepForward();
    ReplayStepForward();
}

void ReplayStepBackwardFourFrames(void) {
    ReplayStepBack();
    ReplayStepBack();
    ReplayStepBack();
    ReplayStepBack();
}

s32 ObjectSetHeading(Car *object, s32 heading) {
    s32 value;
    s16 shortValue;
    s32 value0;
    s32 value1;
    s32 value2;

    value = 0x400 - heading;
    if (value == 0x400) {
        value = 0;
    }
    func_8001F2C4(value, 0, 0);
    MatrixStoreObjectBasis(object);
    func_8001F828((s32 *)object);
    shortValue = value;
    object->unk102 = shortValue;
    object->movementHeading = shortValue;
    object->heading = shortValue;
    object->fineHeading = value * 4;
    do {
    } while (0);
    value0 = object->basis[0].x;
    value1 = object->basis[0].y;
    value2 = object->basis[0].z;
    object->rot[0].x = value0;
    object->rot[0].y = value1;
    object->rot[0].z = value2;
    do {
    } while (0);
    value0 = object->basis[1].x;
    value1 = object->basis[1].y;
    value2 = object->basis[1].z;
    object->rot[1].x = value0;
    object->rot[1].y = value1;
    object->rot[1].z = value2;
    do {
    } while (0);
    value0 = object->basis[2].x;
    value1 = object->basis[2].y;
    value2 = object->basis[2].z;
    object->rot[2].x = value0;
    object->rot[2].y = value1;
    object->rot[2].z = value2;
}

extern Car *gPlayerCarLui asm("gPlayerCarAbsolute");
extern s32 gSplitScreenModeLui asm("gSplitScreenModeAbsolute");
extern s32 D_800A2EC8Lui asm("D_800A2EC8Absolute");
extern FarVar gFarFlag3A60 asm("D_800A3A60");
extern FarVar gFarWord357C asm("D_800A357C");
extern FarVar gFarWord357E asm("D_800A357E");
extern FarVar gFarFlag306D asm("gCdAnnouncer");
extern FarVar gFarFlag2F9D asm("gSoundEffectsEnabled");
extern s32 D_800A2ECC[];
extern s32 D_800A2ED0[];
extern s8 D_800A3620;
extern s32 D_800A2DF8;
extern u8 D_800A39F0;
extern void func_8004B128(Car *);
extern void SoundPlaySlot(s8, s8);
extern void EffectRestoreSlots(void);
extern s32 TrackFindSectionForward(s32, s32, s32 *);
extern u32 PadGetType(s32);
extern void SoundStopConditionalSlots(s8);
extern void func_8005301C(void);
extern void SoundMuteAllSlots(s32);
extern void SsSetMute(u8);

/* The plain D_800A2F58 and D_800A36A4 names carry a small .extern elsewhere
 * in this file, which pulls every access through $gp. Separate lui views. */
asm(".globl D_800A2F58Absolute2\nD_800A2F58Absolute2 = D_800A2F58\n"
    ".globl D_800A36A4Absolute2\nD_800A36A4Absolute2 = D_800A36A4\n"
    ".globl gPlayerCarAbsolute2\ngPlayerCarAbsolute2 = gPlayerCar\n");
extern u8 D_800A2F58Absolute2;
extern s32 D_800A36A4Absolute2;
extern Car *gPlayerCarAbsolute2;

void func_80023074(void) {
    s32 mode;
    s32 offset;

    if (D_800A2F58Absolute2 != 0 && D_800A36A4Absolute2 >= 0x51) {
        return;
    }
    mode = 1;
    D_800A2ED4[0] = mode;
    func_8004B128(gPlayerCarLui);
    if (gSplitScreenModeLui != 0) {
        func_8004B128(gPlayerCarLui->next);
    }
    if (D_800A2EC8Lui != 0) {
        mode = D_800A397CSmall;
        if (mode == 2) {
            SoundPlaySlot(0xA, 0xB);
            offset = gReplayLengthSmall - 2;
            gReplayIndexSmall =
                (gReplayHeadSmall + offset) % gReplayLengthSmall;
            ReplayStepForward();
            EffectRestoreSlots();
            {
                Car *car = gPlayerCarLui;
                u8 copy;

                copy = 0;
                if (car->unk268 == 0) {
                    copy = car->unk20D;
                }
                car->cameraMode = copy;
            }
            gPlayerCarLui->segment = TrackFindSectionForward(
                *(s32 *)gPlayerCarLui, gPlayerCarLui->pos.y,
                &gPlayerCarLui->regionIndex);
            func_8004B128(gPlayerCarLui);
            {
                Car *car = gPlayerCarLui;
                s32 split;

                split = gSplitScreenModeLui;
                car->cameraAngle = car->heading;
                if (split == mode) {
                    Car *other = (u8 *)car->next;
                    u8 copy;

                    copy = 0;
                    if (other->unk268 == 0) {
                        copy = other->unk20D;
                    }
                    other->cameraMode = copy;
                    gPlayerCarLui->next->segment = TrackFindSectionForward(
                        *(s32 *)(u8 *)gPlayerCarLui->next,
                        gPlayerCarLui->next->pos.y,
                        &gPlayerCarLui->next->regionIndex);
                    func_8004B128(gPlayerCarLui->next);
                    gPlayerCarLui->next->cameraAngle =
                        gPlayerCarLui->next->heading;
                }
            }
            if (FAR_VAR(u8, gFarFlag3A60) != 0) {
                Car *car = gPlayerCarAbsolute2;
                u16 word;
                s32 split2;

                word = FAR_VAR(u16, gFarWord357C);
                split2 = gSplitScreenModeLui;
                car->segment = word;
                if (split2 != 0) {
                    car->next->segment = FAR_VAR(u16, gFarWord357E);
                }
                SceneInitRoadStrip();
            }
            if (PadGetType(D_800A3620) == 2) {
                D_800A2DF8 = PadGetButtons(D_800A3620);
            }
            D_800A397CSmall = 1;
            SoundStopConditionalSlots(0);
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
        Car *car = gPlayerCarLui;

        if (car->unk268 == 0) {
            car->unk20D = (u8)car->cameraMode;
        }
    }
    if (gSplitScreenModeLui == 2) {
        Car *other = (u8 *)gPlayerCarLui->next;

        if (other->unk268 == 0) {
            other->unk20D = (u8)other->cameraMode;
        }
    }
    offset = gReplayLengthSmall - 1;
    gReplayIndexSmall = (gReplayHeadSmall + offset) % gReplayLengthSmall;
    SoundMuteAllSlots(0);
    SoundStopConditionalSlots(0);
    if (FAR_VAR(u8, gFarFlag306D) == 0) {
        func_8003CCE0(0);
    }
    if (FAR_VAR(u8, gFarFlag2F9D) == 0) {
        SsSetMute(0);
    }
    D_800A2DF8 = PadGetButtons(D_800A3620);
    D_800A39F0 = 0;
}

extern void CdApplyMixVolume(void);
extern void func_8002F86C(Car *, s32);
extern s8 D_800A2D0CControl asm("D_800A2D0CAbsolute");
extern s32 D_800A2DF8Control asm("D_800A2DF8");
extern s32 gSplitScreenModeControl asm("gSplitScreenModeAbsolute");
extern s32 D_800A2EACControl asm("D_800A2EACAbsolute");
extern s32 gSessionTypeControl asm("gSessionTypeAbsolute");
extern s32 D_800A2EB4Control asm("D_800A2EB4Absolute");
extern s32 D_800A2EC4Control asm("D_800A2EC4Absolute");
extern s32 D_800A2EC8Control asm("D_800A2EC8Absolute");
extern s32 D_800A2ECCControl asm("D_800A2ECCAbsolute");
extern s32 D_800A2ED0Control asm("D_800A2ED0Absolute");
extern s32 D_800A2ED4Control asm("D_800A2ED4Absolute");
extern u8 gStereoEnabledControl asm("gStereoEnabledAbsolute");
extern u8 gCdAudioEnabledControl asm("gCdAudioEnabledAbsolute");
extern u8 gSoundEffectsEnabledControl asm("gSoundEffectsEnabledAbsolute");
extern s8 D_800A2FC8Control asm("D_800A2FC8Absolute");
extern u8 D_800A306CControl asm("D_800A306CAbsolute");
extern u8 gCdAnnouncerControl asm("gCdAnnouncerAbsolute");
extern Car *gPlayerCarControl asm("gPlayerCarAbsolute");
extern s8 D_800A3590Control asm("D_800A3590Absolute");
extern s8 D_800A3620Control asm("D_800A3620");
extern s16 gCdVolumeControl asm("gCdVolumeAbsolute");
extern s16 gMusicVolumeControl asm("gMusicVolumeAbsolute");
extern u8 D_800A36FCControl asm("D_800A36FCAbsolute");
extern u8 D_800A3700Control asm("D_800A3700Absolute");
extern Car *gCarListControl asm("gCarListAbsolute");
extern s32 D_800A397CControl asm("D_800A397C.NON_MATCHING");
extern s8 D_800A39F0Control asm("D_800A39F0");
extern s8 D_800A3A94Control asm("D_800A3A94Absolute");

extern s8 gMusicVolumeScaledControl asm("gMusicVolumeScaledAbsolute");
extern u8 D_800A3614Control asm("D_800A3614Absolute");
extern u8 D_800A3924Control asm("D_800A3924Absolute");
extern u8 D_800A380CControl asm("D_800A380CAbsolute");
extern u8 D_800A35A8Control asm("D_800A35A8Absolute");
extern s16 gMusicVolumeControlPointer[] asm("gMusicVolumeAbsolute2");
extern s16 gCdVolumeControlPointer[] asm("gCdVolumeAbsolute2");

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
    register s32 toneChannel;
    s32 playerCount;
    s32 parentSelection;
    register s32 selectionIndex asm("$3");
    s32 navigationState;
    u8 monoMode;
    Car *otherObject;
    Car *object;

    /* Keep retail's frame gap and the switch table's 8-byte alignment. */
    asm(".section .rodata\n\t.align 3\n\t.text" : : "m"(frameGap[0]));
    if (D_800A397CControl != 2) {
        buttons = PadGetButtons(D_800A3620Control);
        if (!(D_800A2ED0Control & 0xC)) {
            buttonBits = ~D_800A2DF8Control;
            keyMask = buttonBits & 0x1000;
            keyMask = buttons & keyMask;
            toneChannel = 10;
            if (keyMask) {
                SoundPlaySlot(toneChannel, 9);
                if (D_800A39F0Control == 1 && D_800A2ECCControl == 3 &&
                    gCdAnnouncerControl == 0 && gCdAudioEnabledControl != 0) {
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
                playerCount = gSessionTypeControl;
                if (playerCount == 2 && selectionIndex == playerCount) {
                    D_800A2ECCControl = previousStateOne;
                }
                if (gSplitScreenModeControl != 0 && D_800A2ECCControl == 3) {
                    selection = 2;
                    goto setSelection;
                }
                goto done;
            previousSoundState:
                if (selectionIndex == navigationState &&
                    gSoundEffectsEnabledControl != 0) {
                handleSlider:
                    SoundRunSlotEnvelope(0, 10);
                    goto done;
                }
                if (D_800A2ECCControl == 3 && gCdAnnouncerControl == 0) {
                startMusic:
                    func_8003CCE0(1);
                }
                goto done;
            } else {
                keyMask = buttonBits & 0x4000;
                keyMask = buttons & keyMask;
                if (!keyMask)
                    goto block_49;
                SoundPlaySlot(toneChannel, 9);
                if (D_800A39F0Control == 1 && D_800A2ECCControl == 3 &&
                    gCdAnnouncerControl == 0 && gCdAudioEnabledControl != 0) {
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
                playerCount = gSessionTypeControl;
                if (playerCount == 2 && selectionIndex == playerCount) {
                    D_800A2ECCControl = 3;
                }
                if (gSplitScreenModeControl != 0 && D_800A2ECCControl == 3) {
                    selection = 4;
                    goto setSelection;
                }
                goto done;
            nextSoundState:
                if (selectionIndex == navigationState &&
                    gSoundEffectsEnabledControl != 0)
                    goto handleSlider;
                asm("" : : : "memory");
                if (D_800A2ECCControl == 3 && gCdAnnouncerControl == 0 &&
                    gCdAudioEnabledControl != 0)
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
            keyMask = ~buttonBits & 0x840;
            if (buttons & keyMask) {
                if (buttons & 0x800) {
                    keyMask = buttonBits & 0x100;
                    if (!(buttons & keyMask)) {
                        if ((D_800A39F0Control == 1) &&
                            (D_800A2ECCControl == D_800A39F0Control)) {
                            SoundRunSlotEnvelope(2, 0xA);
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
                            if (gSoundEffectsEnabledControl == 0) {
                                SsSetMute(1);
                            }
                            func_80041328();
                            if (gCdAnnouncerControl == 0) {
                                func_8003CCE0(gCdAudioEnabledControl);
                            }
                            if (gPlayerCarControl->unk268 == 0) {
                                gPlayerCarControl->cameraMode =
                                    (u8)gPlayerCarControl->unk20D;
                            }
                            if (gSplitScreenModeControl == 2) {
                                otherObject = (u8 *)gPlayerCarControl->next;
                                if (otherObject->unk268 == 0) {
                                    otherObject->cameraMode =
                                        (u8)otherObject->unk20D;
                                }
                            }
                            break;
                        case 1:
                            SoundPlaySlot(0xA, 0xB);
                            EffectSaveSlots();
                            object = gCarListControl;
                            D_800A397CControl = 2;
                            objectIndex = 0;
                            if (D_800A2EB4Control > 0) {
                                activeState = 1;
                            objectLoop:
                                value = object->cameraMode;
                                if (value >= 3) {
                                    value = object->heading;
                                    object->cameraMode = activeState;
                                    object->cameraAngle = value;
                                }
                                nextObjectIndex = objectIndex + 1;
                                objectIndex = nextObjectIndex;
                                object = object->next;
                                if (nextObjectIndex < D_800A2EB4Control)
                                    goto objectLoop;
                            }
                            break;
                        case 2:
                            SoundPlaySlot(10, 11);
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
                            SoundPlaySlot(10, 11);
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
                            SoundPlaySlot(0xA, 0xB);
                            D_800A39F0Control = 1;
                            D_800A2ECCControl = 0;
                            break;
                        case 5:
                            SoundPlaySlot(0xA, 0xB);
                            D_800A39F0Control = 2;
                            D_800A2ECCControl = 3;
                            break;
                        }
                        break;
                    case 1:
                        if (D_800A2ECCControl == 5) {
                            SoundPlaySlot(0xA, 0xB);
                            parentSelection = 4;
                            goto closeSubmenu;
                        }
                        break;
                    case 2:
                        SoundPlaySlot(0xA, 0xB);
                        if (D_800A2ECCControl == 3) {
                            parentSelection = 5;
                        closeSubmenu:
                            D_800A39F0Control = 0;
                            D_800A2ECCControl = parentSelection;
                            break;
                        }
                        if (gSessionTypeControl == menuState) {
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
                            if (gPlayerCarControl->unk268 != 0) {
                                gPlayerCarControl->unk268 = 0U;
                                gPlayerCarControl->unkF4 = 0;
                                gPlayerCarControl->speed = 0;
                            }
                            D_800A2EC8Control = 0;
                            D_800A2ED4Control = 0;
                            SoundMuteAllSlots(1);
                            if (gCdAnnouncerControl == 0) {
                                func_8003CCE0(gCdAudioEnabledControl);
                            }
                            D_800A3A94Control = 0;
                            if (D_800A2EACControl == 0) {
                                func_8002F86C(gPlayerCarControl, 2);
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
                        (gSoundEffectsEnabledControl != 0)) {
                        SoundRunSlotEnvelope(1, 0xA);
                    }
                    keyMask = ~D_800A2DF8Control & 0xA000;
                    if (buttons & keyMask) {
                        switch (D_800A2ECCControl) {
                        case 0:
                            SoundPlaySlot(10, 10);
                            func_8004142C();
                            enabledVolume =
                                -(gSoundEffectsEnabledControl != 0) & 50;
                            gMusicVolumeControl = enabledVolume;
                            gMusicVolumeScaledControl =
                                enabledVolume * 127 / 100;
                            break;
                        case 2:
                            SoundPlaySlot(10, 10);
                            func_80041414();
                            if (gCdAudioEnabledControl == 0) {
                                gCdVolumeControl = 0;
                            } else {
                                gCdVolumeControl = 50;
                            }
                            CdApplyMixVolume();
                            break;
                        case 4:
                            SoundPlaySlot(10, 10);
                            gStereoEnabledControl = gStereoEnabledControl == 0;
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
                            if (gSoundEffectsEnabledControl != 0) {
                                volume = gMusicVolumeControlPointer;
                                if (buttons & 0x8000) {
                                    volumeResult = gMusicVolumeControl;
                                    volumeValue = volumeResult;
                                    if (volumeResult > 0) {
                                        volumeResult = volumeValue - 1;
                                        gMusicVolumeControl = volumeResult;
                                        *volume = volumeResult;
                                    } else {
                                        volumeResult = 0;
                                        goto setMusicVolume;
                                    }
                                } else {
                                    volumeResult = gMusicVolumeControl;
                                    volumeValue = volumeResult;
                                    volumeResult = volumeResult < 100;
                                    if (volumeResult != 0) {
                                        volumeResult = volumeValue + 1;
                                        gMusicVolumeControl = volumeResult;
                                        *volume = volumeResult;
                                    } else {
                                        volumeResult = 100;
                                    setMusicVolume:
                                        *volume = volumeResult;
                                    }
                                }
                                gMusicVolumeScaledControl =
                                    gMusicVolumeControl * 127 / 100;
                                SoundSetSlotVolume(10, 127, 127);
                            }
                            break;
                        case 3:
                            if (gCdAudioEnabledControl != 0) {
                                volume = gCdVolumeControlPointer;
                                if (buttons & 0x8000) {
                                    volumeResult = gCdVolumeControl;
                                    volumeValue = volumeResult;
                                    if (volumeResult > 0) {
                                        volumeResult = volumeValue - 1;
                                        gCdVolumeControl = volumeResult;
                                    } else {
                                        volumeResult = 0;
                                    }
                                } else {
                                    volumeResult = gCdVolumeControl;
                                    volumeValue = volumeResult;
                                    volumeResult = volumeResult < 100;
                                    if (volumeResult != 0) {
                                        volumeResult = volumeValue + 1;
                                        gCdVolumeControl = volumeResult;
                                    } else {
                                        volumeResult = 100;
                                    }
                                }
                                *volume = volumeResult;
                                CdApplyMixVolume();
                                SoundPlaySlot(10, 10);
                            }
                            break;
                        }
                    }
                }
                if (D_800A2ED0Control & 4) {
                    keyMask = ~D_800A2DF8Control & 0x10;
                    if (keyMask & buttons) {
                        fadeFlag = D_800A36FCControl;
                        D_800A3924Control = D_800A3614Control;
                        D_800A3614Control = ((s8)D_800A3614Control + 1) % 3;
                        if (fadeFlag == 0)
                            fadeFlag = 128;
                        D_800A3700Control = fadeFlag;
                    }
                    keyMask = ~D_800A2DF8Control & 0x80;
                    if (keyMask & buttons) {
                        D_800A36FCControl = 128;
                        D_800A35A8Control = D_800A380CControl;
                        D_800A380CControl = ((s8)D_800A380CControl + 2) % 3;
                        if (D_800A3700Control == 0)
                            D_800A3700Control = 128;
                    }
                    keyMask = ~D_800A2DF8Control & 0x20;
                    if (keyMask & buttons) {
                        D_800A36FCControl = 128;
                        D_800A35A8Control = D_800A380CControl;
                        D_800A380CControl = ((s8)D_800A380CControl + 1) % 3;
                        if (D_800A3700Control == 0)
                            D_800A3700Control = 128;
                    }
                }
                if (D_800A2ED0Control & 8) {
                    if (gSplitScreenModeControl == 0) {
                        if (buttons & 0x1000) {
                            if (D_800A3590Control != 0)
                                D_800A3590Control -= 2;
                        }
                        if ((buttons & 0x4000) && D_800A3590Control < 120) {
                            D_800A3590Control += 2;
                        }
                    }
                    newButtonMask = ~D_800A2DF8Control;
                    keyMask = newButtonMask & 4;
                    if (!(buttons & keyMask))
                        goto done;
                    keyMask = newButtonMask & 1;
                    if (!(buttons & keyMask))
                        goto done;
                    keyMask = newButtonMask & 8;
                    if (!(buttons & keyMask))
                        goto done;
                    keyMask = newButtonMask & 2;
                    if (buttons & keyMask) {
                        D_800A2FC8Control = 1;
                        SoundPlaySlot(0xA, 0xB);
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

    if (gCdAnnouncerAbsolute2[0] == 0) {
        vol.val0 = vol.val1 = vol.val2 = vol.val3 =
            gCdVolumeAbsolute3[0] * 125 / 100;
        CdMix(&vol);
    }
}

extern s32 D_800A2DFC;
extern s32 gReplayPrevButtons;
extern s32 gReplayPrevButtons2;
extern void func_80041328(void);
extern void SoundMuteFiveSlots(void);

void ReplayHandleInput(void) {
    s32 buttons;

    D_800A2ED4[0] = 0;
    buttons = PadGetButtons(D_800A3620);
    D_800A2DFC = 0;
    if ((buttons & 0x100) || (gPadType[D_800A3620] == 2 && (buttons & 0x800))) {
        D_800A2DF8 = buttons;
        func_80023074();
        return;
    }
    if (buttons & 0x40) {
        D_800A2DFC = 8;
        func_80041328();
        func_8005301C();
        ReplayStepForward();
    } else if (buttons & 0x80) {
        D_800A2DFC = 2;
        func_80041328();
        func_8005301C();
        ReplayStepBack();
        ReplayStepBack();
        ReplayStepBack();
        ReplayStepBack();
    } else if (buttons & 0x10) {
        D_800A2DFC = 1;
        func_80041328();
        func_8005301C();
        ReplayStepForward();
        ReplayStepForward();
        ReplayStepForward();
        ReplayStepForward();
    } else {
        SoundMuteFiveSlots();
        SoundStopConditionalSlots(0);
        D_800A2ED4[0] = 1;
    }
    if (buttons & ((u16)~gReplayPrevButtons & 0x20)) {
        D_800A2DFC = 4;
        if (PadGetButtons(D_800A3620) & 0x20) {
            SoundPlaySlot(0xA, 0xB);
            CameraCycleMode(D_800A3620 != 0 ? gPlayerCar[0]->next
                                            : gPlayerCar[0]);
        }
        if (gSplitScreenMode[0] != 0) {
            if (PadGetButtons(1) & 0x20) {
                SoundPlaySlot(0xA, 0xB);
                CameraCycleMode(gPlayerCar[0]->next);
            }
        }
    }
    gReplayPrevButtons = buttons;
    if (gSplitScreenMode[0] != 0) {
        buttons = PadGetButtons(D_800A3620 == 0);
        if (buttons & ((u16)~gReplayPrevButtons2 & 0x20)) {
            D_800A2DFC = 4;
            if (PadGetButtons(D_800A3620 == 0) & 0x20) {
                SoundPlaySlot(0xA, 0xB);
                CameraCycleMode(D_800A3620 == 0 ? gPlayerCar[0]->next
                                                : gPlayerCar[0]);
            }
        }
        gReplayPrevButtons2 = buttons;
    }
}

typedef struct {
    u16 base;
    u16 lo;
    u8 zHi;
    u8 zLo;
    u16 hi;
    s32 scale;
} CurveSeg;

extern CurveSeg *D_800A356C;

s32 TrackTestPointInSection(s32 x, s32 y, TrackSection *section) {
    CurveSeg *seg;
    s32 *crossingXs;
    s32 segmentCount;
    s32 crossingCount;
    s32 insertIndex;
    s32 k;
    s32 i;
    s32 crossingX;

    crossingCount = 0;
    crossingXs = (s32 *)SCRATCHPAD_BASE;
    seg = D_800A356C + section->section;
    segmentCount = *(u8 *)&section->culled;
    for (i = segmentCount; i > 0; i--, seg++) {
        if (y >= seg->lo && y < seg->hi) {
            crossingX = seg->base + ((seg->scale * (y - seg->lo)) >> 16);
            for (insertIndex = 0; insertIndex < crossingCount; insertIndex++) {
                if (crossingX < crossingXs[insertIndex]) {
                    break;
                }
            }
            crossingCount++;
            for (k = crossingCount - 1; insertIndex < k; k--) {
                crossingXs[k] = crossingXs[k - 1];
            }
            crossingXs[insertIndex] = crossingX;
        }
    }
    if (crossingCount >= 2) {
        if (crossingCount & 1) {
            return 0;
        }
        for (i = 0; i < crossingCount; i += 2) {
            if (x < crossingXs[i]) {
                return 0;
            }
            if (x < crossingXs[i + 1]) {
                return 1;
            }
        }
    }
    return 0;
}

extern s32 D_800A2E08;
extern s32 D_800A3838;
s32 TrackTestPointInSection(s32, s32, TrackSection *);

typedef struct {
    u8 unk0;
    u8 count;
    s16 a;
    s16 b;
    s16 c;
} GroupRec;

/* A 0x10 track-lookup cell: its bounding box and its segment groups. */
typedef struct {
    u16 minX; /* 0x00 */
    u16 minY;
    u16 maxX;
    u16 maxY;
    u16 segIndex;
    u16 groupIndex;
    s16 base;
    u8 unkE;
    u8 groupCount;
} SecRec;

s32 TrackFindSectionForward(s32 x, s32 y, s32 *indexPtr) {
    s32 index;
    s32 remaining;
    SecRec *entry;
    s32 count;

    count = D_800A2E08;
    x = x / 4;
    y = y / 4;
    index = *indexPtr;
    if (index == -1) {
        index = 0;
    }
    remaining = count;
    entry = (SecRec *)D_800A3838 + index;
    if (remaining > 0) {
        do {
            if (index >= count) {
                index = 0;
                entry = (SecRec *)D_800A3838;
            }
            if (x >= entry->minX && entry->maxX >= x && y >= entry->minY &&
                entry->maxY >= y &&
                (TrackTestPointInSection(x, y, entry) & 0xFF) != 0) {
                *indexPtr = index;
                if (index == count) {
                    index = 0;
                }
                return index;
            }
            remaining -= 1;
            index += 1;
            entry++;
        } while (remaining > 0);
    }
    *indexPtr = -1;
    return -1;
}

s32 TrackFindSectionFromPrevious(s32 x, s32 y, s32 *indexPtr) {
    s32 index;
    s32 remaining;
    SecRec *entry;
    s32 count;
    s32 countLessOne;

    count = D_800A2E08;
    x = x / 4;
    y = y / 4;
    index = *indexPtr;
    if (index == -1) {
        index = 0;
    } else {
        countLessOne = count - 1;
        index = (index + countLessOne) % count;
    }
    remaining = count;
    entry = (SecRec *)D_800A3838 + index;
    if (remaining > 0) {
        do {
            if (index >= count) {
                index = 0;
                entry = (SecRec *)D_800A3838;
            }
            if (x >= entry->minX && entry->maxX >= x && y >= entry->minY &&
                entry->maxY >= y &&
                (TrackTestPointInSection(x, y, entry) & 0xFF) != 0) {
                *indexPtr = index;
                if (index == count) {
                    index = 0;
                }
                return index;
            }
            remaining -= 1;
            index += 1;
            entry++;
        } while (remaining > 0);
    }
    *indexPtr = -1;
    return -1;
}

extern s32 D_800A3810;
extern u32 D_800A2E0C;
extern u32 D_800A2E10;
extern s32 D_800B6094[];

s32 TrackSampleSection(s32 x, s32 y, SecRec *section) {
    CurveSeg *seg;
    GroupRec *group;
    s32 groupCount;
    s32 i;
    s32 found;
    s32 x0;
    s32 z0;
    s32 x1;
    s32 z1;

    seg = D_800A356C + section->segIndex;
    group = (GroupRec *)D_800A3810 + section->groupIndex;
    for (groupCount = section->groupCount; groupCount > 0;
         groupCount--, group++) {
        found = 0;
        for (i = group->count; i > 0; i--, seg++) {
            if (y < seg->lo || y >= seg->hi) {
                continue;
            }
            x1 = seg->base + ((seg->scale * (y - seg->lo)) >> 16);
            if (found == 0) {
                s32 a;
                s32 b;
                s32 za;
                s32 zb;

                x0 = x1;
                a = seg->zLo * 2;
                b = seg->zHi * 2;
                za = a + section->base;
                zb = b + section->base;
                if (seg->hi == seg->lo) {
                    z0 = za;
                } else {
                    z0 = za + ((zb - za) * (y - seg->lo)) / (seg->hi - seg->lo);
                }
                found = 1;
                continue;
            }
            if (x1 < x0) {
                s32 lo;
                s32 hi;
                s32 a;
                s32 b;
                s32 za;
                s32 zb;

                if (x >= x1 && x < x0) {
                    D_800A2E10 = group->unk0;
                    a = seg->zLo * 2;
                    b = seg->zHi * 2;
                    za = a + section->base;
                    zb = b + section->base;
                    lo = seg->lo;
                    hi = seg->hi;
                    if (hi != lo) {
                        z1 = za + ((zb - za) * (y - lo)) / (hi - lo);
                    } else {
                        z1 = za;
                    }
                    if (x0 != x1) {
                        z1 += ((z0 - z1) * (x - x1)) / (x0 - x1);
                    }
                    D_800B6094[0] = group->a * 4;
                    D_800B6094[1] = group->b * 4;
                    D_800B6094[2] = group->c * 4;
                    D_800A2E0C = z1;
                    return 1;
                } else {
                    seg += i;
                    break;
                }
            } else {
                s32 lo;
                s32 hi;
                s32 a;
                s32 b;
                s32 za;
                s32 zb;

                if (x >= x0 && x < x1) {
                    D_800A2E10 = group->unk0;
                    a = seg->zLo * 2;
                    b = seg->zHi * 2;
                    za = a + section->base;
                    zb = b + section->base;
                    lo = seg->lo;
                    hi = seg->hi;
                    if (hi != lo) {
                        z1 = za + ((zb - za) * (y - lo)) / (hi - lo);
                    } else {
                        z1 = za;
                    }
                    if (x1 == x0) {
                        z1 = z0;
                    } else {
                        z1 = z0 + ((z1 - z0) * (x - x0)) / (x1 - x0);
                    }
                    D_800B6094[0] = group->a * 4;
                    D_800B6094[1] = group->b * 4;
                    D_800B6094[2] = group->c * 4;
                    D_800A2E0C = z1;
                    return 1;
                } else {
                    seg += i;
                    break;
                }
            }
        }
    }
    return 0;
}

static inline s32 SectionSample(s32 x, s32 y, SecRec *sec) {
    CurveSeg *seg;
    GroupRec *group;
    s32 groupCount;
    s32 i;
    s32 found;
    s32 x0;
    s32 z0;
    s32 x1;
    s32 z1;
    s32 zf;

    seg = D_800A356C + sec->segIndex;
    group = (GroupRec *)D_800A3810 + sec->groupIndex;
    for (groupCount = sec->groupCount; groupCount > 0; groupCount--, group++) {
        found = 0;
        for (i = group->count; i > 0; i--, seg++) {
            if (y < seg->lo || y >= seg->hi) {
                continue;
            }
            x1 = seg->base + ((seg->scale * (y - seg->lo)) >> 16);
            if (found == 0) {
                s32 a;
                s32 b;
                s32 za;
                s32 zb;

                x0 = x1;
                a = seg->zLo * 2;
                b = seg->zHi * 2;
                za = a + sec->base;
                zb = b + sec->base;
                if (seg->hi == seg->lo) {
                    z0 = za;
                } else {
                    z0 = za + ((zb - za) * (y - seg->lo)) / (seg->hi - seg->lo);
                }
                found = 1;
                continue;
            }
            if (x1 < x0) {
                s32 lo;
                s32 hi;
                s32 a;
                s32 b;
                s32 za;
                s32 zb;

                if (x >= x1 && x < x0) {
                    D_800A2E10 = group->unk0;
                    a = seg->zLo * 2;
                    lo = seg->lo;
                    b = seg->zHi * 2;
                    hi = seg->hi;
                    za = a + sec->base;
                    zb = b + sec->base;
                    if (hi == lo) {
                        z1 = za;
                    } else {
                        z1 = za + ((zb - za) * (y - lo)) / (hi - lo);
                    }
                    if (x0 == x1) {
                        zf = z1;
                    } else {
                        zf = z1 + ((z0 - z1) * (x - x1)) / (x0 - x1);
                    }
                    D_800B6094[0] = group->a * 4;
                    D_800B6094[1] = group->b * 4;
                    D_800B6094[2] = group->c * 4;
                    D_800A2E0C = zf;
                    return 1;
                } else {
                    seg += i;
                    break;
                }
            } else {
                s32 lo;
                s32 hi;
                s32 a;
                s32 b;
                s32 za;
                s32 zb;

                if (x >= x0 && x < x1) {
                    D_800A2E10 = group->unk0;
                    a = seg->zLo * 2;
                    lo = seg->lo;
                    b = seg->zHi * 2;
                    hi = seg->hi;
                    za = a + sec->base;
                    zb = b + sec->base;
                    if (hi == lo) {
                        z1 = za;
                    } else {
                        z1 = za + ((zb - za) * (y - lo)) / (hi - lo);
                    }
                    if (x1 == x0) {
                        zf = z0;
                    } else {
                        zf = z0 + ((z1 - z0) * (x - x0)) / (x1 - x0);
                    }
                    D_800B6094[0] = group->a * 4;
                    D_800B6094[1] = group->b * 4;
                    D_800B6094[2] = group->c * 4;
                    D_800A2E0C = zf;
                    return 1;
                } else {
                    seg += i;
                    break;
                }
            }
        }
    }
    return 0;
}

s32 TrackFindSection(s32 x, s32 y, s32 *indexPtr, s32 *outZ, s32 *outType) {
    s32 index;
    s32 remaining;
    SecRec *entry;
    s32 count;

    count = D_800A2E08;
    x = x / 4;
    y = y / 4;
    index = *indexPtr;
    if (index == -1) {
        index = 0;
    }
    D_800A2E0C = 0;
    remaining = count;
    entry = (SecRec *)D_800A3838 + index;
    if (remaining > 0) {
        do {
            if (index >= count) {
                index = 0;
                entry = (SecRec *)D_800A3838;
            }
            if (x >= entry->minX && entry->maxX >= x && y >= entry->minY &&
                entry->maxY >= y && (SectionSample(x, y, entry) & 0xFF) != 0) {
                *indexPtr = index;
                *outZ = D_800A2E0C;
                *outType = D_800A2E10;
                if (index == count) {
                    index = 0;
                }
                return index;
            }
            remaining -= 1;
            index += 1;
            entry++;
        } while (remaining > 0);
    }
    *indexPtr = -1;
    return -1;
}
