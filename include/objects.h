#ifndef OBJECTS_H
#define OBJECTS_H

#include "common.h"
#include "car.h"

s32 MathGetAngleDelta(s32 arg0, s32 arg1);
s32 TrackFindSection(s32, s32, s32 *, s32 *, s32 *);
void func_80029CB4(s32 *car);
void func_8002A1FC(Car *);
void CarSetVelocityFromHeading(s32 *car, s32 index);
void MatrixSetIdentity(s32 *arg0);
void ScratchpadFillPattern(s32 arg0);
void func_80032DEC(u8 *firstObject, s32 objectCount);
void ObjectAdvanceAlongHeading(u8 *object);
void func_800373B4(u8 *);
void ObjectSetCallbackIfAllowed(Car *object, void (*callback)(void));
void CarReduceSpeed(Car *object);

#endif /* OBJECTS_H */
