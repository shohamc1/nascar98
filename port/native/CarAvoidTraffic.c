s32 CarAvoidTraffic(Car *car, s32 keepTarget) {
    s32 maxDistance;
    s32 count;
    Car *other;
    s32 value;
    s32 forward;
    s32 lateral;
    s8 leftAllowed;
    s32 routeDistance;
    s32 angle;
    s32 cosine;
    register s32 *cosTable;
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
    other = gCarListAbsolute[0];
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
        routeDistance = func_8003702C(other, car);
        if (keepTarget & 0xFF) {
            if (routeDistance < 3) {
                return 0;
            }
        } else if (routeDistance < -1 || maxDistance < routeDistance) {
            continue;
        }
        if (car->unk26C[14] == 0) {
            if (ABS(other->unk203) >= 7) {
                car->targetSegment = -1;
                continue;
            }
        }
        angle = 0x400;
        angle -= car->heading;
        cosTable = gCosTableAbsolute[0];
        /* Keep the x loads after the table base and entry address. */
        dx = other->pos.x;
        maxDistance = angle & 0x3FF;
        cosTable = (s32 *)((maxDistance * 4) + (u32)cosTable);
        /* lw carX, pos.x; cosTable is unchanged. */
        carX = car->pos.x;
        cosine = *cosTable;
        dx -= carX;
        sine = gSinTableAbsolute[0][maxDistance];
        dy = other->pos.y - car->pos.y;
        forward = (cosine * dx - sine * dy) >> 16;
        lateral = (sine * dx + cosine * dy) >> 16;
        routeDistance = ABS(MathGetAngleDelta(car->heading, other->heading));
        sideScale = (gSinTableAbsolute[0][routeDistance] * 250) >> 16;
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
                    func_80039B74(car, 0);
                    maxDistance = (car->segment + 4) % gTrackSectionCount[0];
                    flags = *(u32 *)&((RoutePoint *)D_800AE154[0])[maxDistance]
                                 .speed >>
                            30;
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
