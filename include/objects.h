#ifndef OBJECTS_H
#define OBJECTS_H

#include "common.h"

typedef struct {
    u8 unk0[0x1EC];
    s16 unk1EC;
    u8 unk1EE[0x12];
    s8 unk200;
    u8 unk201[0x153];
    void (*callback)(void);
} ObjectCallbackView;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vector3;

typedef struct {
    u8 unk0[0x90];
    s32 speed;
} CarSpeedView;
s32 MathGetAngleDelta(s32 arg0, s32 arg1);
s32 TrackFindSection(s32, s32, s32 *, s32 *, s32 *);
void func_80029CB4(s32 *car);
void func_8002A1FC(u8 *);
void CarSetVelocityFromHeading(s32 *car, s32 index);
void MatrixSetIdentity(s32 *arg0);
void ScratchpadFillPattern(s32 arg0);
void func_80032DEC(u8 *firstObject, s32 objectCount);
void ObjectAdvanceAlongHeading(u8 *object);
void func_800373B4(u8 *);
void ObjectSetCallbackIfAllowed(ObjectCallbackView *object,
                                void (*callback)(void));
void CarReduceSpeed(CarSpeedView *object);

#endif /* OBJECTS_H */
