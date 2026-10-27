/*
 * MIPS O32 passes CollisionApplyImpulse's Vec3 by value in a2, a3, and the
 * first stack word, so func_80026074 reads it as three s32s and the first
 * flag as its sixth argument. wasm32 passes the struct by pointer instead.
 */
s32 CarHandlePairCollision(Car *firstCar, Car *secondCar) {
#define PortApplyImpulse(a, b, v, f, g) func_80026074(a, b, (v).x, (v).y, (v).z, f)
    Vec3 separation;
    Vec3 direction;
    Vec3 velocity;
    Vec3 original;
    Vec3 midpoint;
    register s32 tmp0;
    register s32 tmp1;
    register s32 productX;
    register s32 callA0;
    register s32 callA1;
    register s32 productY;
    s32 impulseX;
    s32 impulseY;
    register s32 impulsePart;
    s32 nextCallback;
    s32 effectFlag;
    register s32 beyondFar;
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
    register s32 work1;
    register s32 work2;
    register s32 work3;
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
    Car *car;
    Car *otherCar;

    car = firstCar;

    otherCar = secondCar;

    if (D_8008CA28[0] == 0) {
        tmp0 = (s32)gPlayerCar[0];
        if (otherCar == (u8 *)tmp0) {
            otherCar = car;
            car = (Car *)tmp0;
        }
    }
    separation.x = (otherCar->pos.x) - (car->pos.x);
    separation.y = (otherCar->pos.y) - (car->pos.y);
    separation.z = (otherCar->pos.z) - (car->pos.z);
    original = separation;
    midpoint.x = (s32)((otherCar->pos.x) + (car->pos.x)) / 2;
    midpoint.y = (s32)((otherCar->pos.y) + (car->pos.y)) / 2;
    if (car->callback == (s32)func_80025730) {
        contactAngle = (car->unk38A);
        angleFromHalfTurn = contactAngle - 0x200;
        if (angleFromHalfTurn >= 0) {
            if (angleFromHalfTurn < 0x100) {
                goto block_8;
            }
            goto block_9;
        }
        if ((0x200 - contactAngle) < 0x100) {
        block_8:
            tmp1 = car->heading;
            tmp0 = 0x600 - tmp1;
            work6 = tmp0 & 0x3FF;

        } else {
            goto block_9;
        }
    } else {
    block_9:
        tmp1 = car->heading;
        tmp0 = 0x3FF;
        work6 = tmp0 - tmp1;
    }
    tmp0 = (s32)gCosTableAbsolute[0];
    work1 = work6 << 2;
    callA1 = original.x;
    tmp0 = work1 + tmp0;
    callA0 = *(s32 *)tmp0;
    tmp0 = MathMultiplyFixed16(callA0, callA1 << 16);
    tmp1 = (s32)gSinTableAbsolute[0];
    callA1 = original.y;
    tmp1 = work1 + tmp1;
    callA0 = *(s32 *)tmp1;
    work0 = tmp0;
    tmp0 = MathMultiplyFixed16(callA0, callA1 << 16);
    tmp1 = gSinTableAbsolute2[0];
    callA1 = original.x;
    work0 -= tmp0;
    work0 >>= 16;
    separation.x = work0;
    tmp1 = work1 + tmp1;
    callA0 = *(s32 *)tmp1;
    tmp0 = MathMultiplyFixed16(callA0, callA1 << 16);
    tmp1 = gCosTableAbsolute2[0];
    callA1 = original.y;
    work1 += tmp1;
    asm("" : "=r"(work1) : "0"(work1));
    callA0 = *(s32 *)work1;
    work0 = tmp0;
    work0 += MathMultiplyFixed16(callA0, callA1 << 16);
    work0 >>= 16;
    separation.y = work0;
    tmp0 = (s32)car->shape;
    tmp0 = ((Model *)tmp0)->maxX;
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
        work3 = MathMultiplyFixed16((otherCar->basis[0].x), 0xFA0);

        work2 = MathMultiplyFixed16((otherCar->basis[1].x), 0xFA0);

        tmp0 = MathMultiplyFixed16(otherCar->basis[2].x, 0xFA0);
        tmp1 = pairCosTable3[0];
        work1 = work6 << 2;
        direction.z = tmp0;
        tmp1 = work1 + tmp1;
        callA0 = *(s32 *)tmp1;
        work3 <<= 16;
        tmp0 = MathMultiplyFixed16(callA0, work3);
        tmp1 = pairSinTable3[0];
        tmp1 = work1 + tmp1;
        do {
            callA0 = *(s32 *)tmp1;
        } while (0);

        work2 <<= 16;
        do {
            callA1 = work2;
        } while (0);

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
        tmp0 = car->velocityX;
        productX = otherCar->velocityX;
        tmp1 = direction.x;
        scratchA0 = (s32)D_800A3668Absolute[0];
        tmp0 -= productX;
        productX = tmp0 * tmp0;
        tmp1 = __builtin_abs(tmp1);
        scratchA0 += tmp1;
        work6 = *(u8 *)scratchA0;
        velocity.x = tmp0;
        tmp0 = car->velocityY;
        tmp1 = otherCar->velocityY;
        tmp0 -= tmp1;
        productY = tmp0 * tmp0;
        velocity.y = tmp0;
        tmp1 = otherCar->velocityZ;
        tmp0 = car->velocityZ;
        tmp0 -= tmp1;
        velocity.z = tmp0;
        tmp0 = MathSqrt(productX + productY);
        relativeSpeed = tmp0;
        tmp1 = separation.y;
        scratchA0 = car->type;
        tmp0 = 1;
        work2 = tmp1;
        if (tmp1 < 0) {
            work2 = -work2;
        }
        if ((scratchA0 == tmp0) && ((otherCar->type) == scratchA0)) {
            tmp0 = (s32)car->shape;
            tmp0 = ((Model *)tmp0)->maxY;
            scratchV1 = tmp0 - 0x1E;
        } else {
            tmp0 = (s32)car->shape;
            tmp0 = ((Model *)tmp0)->maxY;
            scratchV1 = tmp0 - 0xF;
        }
        (car->unk1CE) = 0;
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
                    tmp0 = car->type;
                    goto block_125;
                }
                if (separation.x >= 0) {
                    (car->unk1CE) = 2;
                    tmp0 = collisionHalfWidth << 3;
                    tmp1 = tmp0 + collisionHalfWidth;
                    if (tmp1 < 0) {
                        tmp1 += 3;
                    }
                    tmp0 = separation.x;
                    callA0 = car->basis[0].x;
                    tmp1 >>= 2;
                    tmp0 -= tmp1;
                    tmp1 = (u32)tmp0 >> 31;
                    tmp0 += tmp1;
                    work3 = tmp0 >> 1;
                    (car->pos.x) = (s32)((car->pos.x) +
                                         MathMultiplyFixed16(callA0, work3));
                    (car->pos.y) =
                        (s32)((car->pos.y) +
                              MathMultiplyFixed16((car->basis[1].x), work3));
                    (otherCar->pos.x) =
                        (s32)((otherCar->pos.x) -
                              MathMultiplyFixed16((car->basis[0].x), work3));
                    (otherCar->pos.y) =
                        (s32)((otherCar->pos.y) -
                              MathMultiplyFixed16((car->basis[1].x), work3));
                    if (direction.x > 0) {
                        speedSumA = (otherCar->speed) + (car->speed);
                        meanSpeedA =
                            (s32)(speedSumA + (speedSumA >> 0x1F)) >> 1;
                        if ((otherCar->type) != 0) {
                            (otherCar->speed) = (s32)(meanSpeedA + 0xA0000);
                        }
                        if ((car->type) != 0) {
                            newSpeedA = meanSpeedA + 0xFFF60000;
                            goto block_40;
                        }
                    } else {
                        tmp0 = otherCar->speed;
                        tmp1 = car->speed;
                        scratchA0 = otherCar->type;
                        tmp0 += tmp1;
                        if (tmp0 < 0) {
                            tmp0 = -tmp0;
                        }
                        tmp1 = (u32)tmp0 >> 31;
                        tmp0 += tmp1;
                        tmp1 = tmp0 >> 1;
                        if (scratchA0 != 0) {
                            (otherCar->speed) = (s32)(tmp1 + 0xFFF60000);
                        }
                        if ((car->type) != 0) {
                            newSpeedA = tmp1 + 0xA0000;
                        block_40:
                            (car->speed) = newSpeedA;
                        }
                    }
                    func_80025DD4(otherCar, car);
                    work0 = 1;
                    if (relativeSpeed >= 0x2E) {
                        if (relativeSpeed >= 0x79) {
                            EffectSpawnAtCarPoint(otherCar, 7);
                            if (RandomScaledGet(0xA) == 0) {
                                callA1 = 0;
                                if (separation.y > 0) {
                                    callA0 = (s32)car;
                                } else {
                                    callA0 = (s32)car;
                                    callA1 = 1;
                                }
                                EffectSpawnAtCarPoint((void *)callA0, callA1);
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
                            EffectSpawnAtCarPoint((void *)callA0, callA1);
                        }
                        func_80043B68(car, 0);
                        func_80043B68(car, 1);
                        func_80043B68(otherCar, 2);
                        func_80043B68(otherCar, 3);
                        work0 = 1;
                    }
                    PortApplyImpulse(car, otherCar, velocity, work0, work0);
                    tmp0 = car->heading;
                    tmp1 = (s32)gCosTableAbsolute[0];
                    tmp0 += 0x200;
                    work6 = tmp0 & 0x3FF;
                    scratchA0 = work6 << 2;
                    tmp1 = scratchA0 + tmp1;
                    tmp0 = *(s32 *)tmp1;
                    impulseX = relativeSpeed * tmp0;
                    tmp1 = (s32)gSinTableAbsolute[0];
                    tmp0 = car->frontVelocityX;
                    scratchA0 += tmp1;
                    asm(""
                        : "=r"(impulsePart)
                        : "0"(impulseX), "r"(tmp0), "r"(scratchA0));
                    tmp0 += impulsePart;
                    car->frontVelocityX = tmp0;
                    tmp0 = *(s32 *)scratchA0;
                    impulseY = relativeSpeed * tmp0;
                    tmp0 = car->frontVelocityY;
                    asm("" : "=r"(impulsePart) : "0"(impulseY), "r"(tmp0));
                    tmp0 += impulsePart;
                    car->frontVelocityY = tmp0;
                    result = 2;
                    if ((otherCar->type) == work0) {
                        func_8003AC18(otherCar, relativeSpeed, separation.x,
                                      separation.y);
                        asm("# collision response 1");
                        return 2;
                    }
                    return result;
                }
                (car->unk1CE) = 3;
                tmp1 = separation.x;
                tmp0 = collisionHalfWidth << 3;
                tmp0 += collisionHalfWidth;
                tmp1 = -tmp1;
                if (tmp0 < 0) {
                    tmp0 += 3;
                }
                callA0 = car->basis[0].x;
                tmp0 >>= 2;
                tmp0 = tmp1 - tmp0;
                tmp1 = (u32)tmp0 >> 31;
                tmp0 += tmp1;
                work3 = tmp0 >> 1;
                (car->pos.x) =
                    (s32)((car->pos.x) - MathMultiplyFixed16(callA0, work3));
                (car->pos.y) =
                    (s32)((car->pos.y) -
                          MathMultiplyFixed16((car->basis[1].x), work3));
                (otherCar->pos.x) =
                    (s32)((otherCar->pos.x) +
                          MathMultiplyFixed16((car->basis[0].x), work3));
                (otherCar->pos.y) =
                    (s32)((otherCar->pos.y) +
                          MathMultiplyFixed16((car->basis[1].x), work3));
                if (direction.x > 0) {
                    speedSumB = (otherCar->speed) + (car->speed);
                    meanSpeedB = (s32)(speedSumB + (speedSumB >> 0x1F)) >> 1;
                    if ((otherCar->type) != 0) {
                        (otherCar->speed) = (s32)(meanSpeedB + 0xA0000);
                    }
                    if ((car->type) != 0) {
                        newSpeedB = meanSpeedB + 0xFFF60000;
                        goto block_69;
                    }
                } else {
                    tmp0 = otherCar->speed;
                    tmp1 = car->speed;
                    scratchA0 = otherCar->type;
                    tmp0 += tmp1;
                    if (tmp0 < 0) {
                        tmp0 = -tmp0;
                    }
                    tmp1 = (u32)tmp0 >> 31;
                    tmp0 += tmp1;
                    tmp1 = tmp0 >> 1;
                    if (scratchA0 != 0) {
                        (otherCar->speed) = (s32)(tmp1 + 0xFFF60000);
                    }
                    if ((car->type) != 0) {
                        newSpeedB = tmp1 + 0xA0000;
                    block_69:
                        (car->speed) = newSpeedB;
                    }
                }
                func_80025DD4(otherCar, car);
                if (relativeSpeed < 0x2E) {
                    effectFlag = 1;
                    goto effectsDoneNegative;
                }

                if (relativeSpeed >= 0x79) {
                    EffectSpawnAtCarPoint(otherCar, 7);
                    if (RandomScaledGet(0xA) == 0) {
                        callA1 = 0;
                        if (separation.y > 0) {
                            callA0 = (s32)car;
                        } else {
                            callA0 = (s32)car;
                            callA1 = 1;
                        }
                        EffectSpawnAtCarPoint((void *)callA0, callA1);
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
                    EffectSpawnAtCarPoint((void *)callA0, callA1);
                }
                func_80043B68(car, 0);
                func_80043B68(car, 1);
                func_80043B68(otherCar, 2);
                func_80043B68(otherCar, 3);
                effectFlag = 1;

            effectsDoneNegative:
                PortApplyImpulse(car, otherCar, velocity, 0, effectFlag);
                return 2;
            }
            if (work2 < scratchA1) {
                (car->unk1CE) = 4;
                work2 = scratchA1 - work2;
                work3 = 1;
                if (separation.y > 0) {
                    work2 = -work2;
                }
                work1 = MathMultiplyFixed16((car->basis[0].y), work2);

                (car->pos.x) = (s32)((car->pos.x) + work1);
                work0 = MathMultiplyFixed16((car->basis[1].y), work2);

                (car->pos.y) = (s32)((car->pos.y) + work0);
                (otherCar->pos.x) =
                    (s32)((otherCar->pos.x) -
                          MathMultiplyFixed16((car->basis[0].y), work2));
                (otherCar->pos.y) =
                    (s32)((otherCar->pos.y) -
                          MathMultiplyFixed16((car->basis[1].y), work2));
                func_80025DD4(otherCar, car);
                nextCallback = (s32)ObjectSetResetCallback;
                if ((((car->type) != work3) ||
                     (nextCallback != (s32)func_80025730)) &&
                    (((s32)car->callback) != (s32)func_80025730) &&
                    ((car->mode) != 4)) {
                    car->callback = (void (*)(Car *))nextCallback;
                }
                if ((car->type) == 0) {
                    if ((otherCar->type) != 0) {
                        carHeading = (car->heading);
                        headingDifference = carHeading - (otherCar->heading);
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
                        (otherCar->heading) = otherHeading;
                        otherCar->fineHeading =
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
                    (car->frontVelocityX) =
                        (s32)((car->frontVelocityX) + (work1 << 0x11));
                    (car->frontVelocityY) =
                        (s32)((car->frontVelocityY) + (work0 << 0x11));
                }
                tmp0 = separation.x;
                tmp0 = collisionHalfWidth < tmp0;
                if (tmp0 != 0) {
                    return 1;
                }
                tmp1 = car->rearVelocityX;
                callA0 = car->rearVelocityY;
                scratchA1 = car->type;
                tmp0 = work1 << 16;
                tmp1 += tmp0;
                tmp0 = work0 << 16;
                callA0 += tmp0;
                car->rearVelocityX = tmp1;
                car->rearVelocityY = callA0;
                if (scratchA1 != 0) {
                    goto sideReturnOne;
                }
                tmp1 = otherCar->type;
                tmp0 = 1;
                if (tmp1 == tmp0) {
                    tmp1 = 0xFFFB0000;
                    tmp0 = otherCar->speed;
                    tmp0 += tmp1;
                    otherCar->speed = tmp0;
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
                    tmp0 = car->type;
                    responseCode = 5;
                block_125:
                    callA0 = (s32)func_80025730;
                    (car->unk1CE) = responseCode;
                    if ((tmp0 != 1) && (((s32)car->callback) != callA0) &&
                        ((car->mode) != 4)) {
                        car->callback = (void (*)(Car *))callA0;
                    }
                    if (((otherCar->type) == 0)) {
                        tmp0 = (s32)otherCar->callback;
                        callA0 = (s32)func_80025730;
                        if ((tmp0 != callA0) && ((otherCar->mode) != 4)) {
                            otherCar->callback = (void (*)(Car *))callA0;
                        }
                    }
                    result = 4;
                    if ((car->type) == 0) {
                        func_8003AC18(otherCar, relativeSpeed, separation.x,
                                      separation.y);
                        return 4;
                    }
                    return result;
                }
                (car->unk1CE) = 6;
                tmp0 = original.x;
                tmp1 = tmp0 * tmp0;
                tmp0 = original.y;
                productY = tmp0 * tmp0;
                work3 = MathSqrt(tmp1 + productY);
                (car->pos.x) =
                    (s32)(midpoint.x +
                          ((s32)(MathFixedDivide((car->pos.x) - midpoint.x,
                                                 work3) *
                                 0x320) >>
                           0x10));
                (car->pos.y) =
                    (s32)(midpoint.y +
                          ((s32)(MathFixedDivide((car->pos.y) - midpoint.y,
                                                 work3) *
                                 0x320) >>
                           0x10));
                (otherCar->pos.x) =
                    (s32)(midpoint.x +
                          ((s32)(MathFixedDivide((otherCar->pos.x) - midpoint.x,
                                                 work3) *
                                 0x320) >>
                           0x10));
                otherPositionY =
                    midpoint.y +
                    ((s32)(MathFixedDivide((otherCar->pos.y) - midpoint.y,
                                           work3) *
                           0x320) >>
                     0x10);
                (otherCar->pos.y) = otherPositionY;
                func_80025DD4(otherCar, car);
                tmp1 = separation.x;
                if (tmp1 >= -collisionHalfWidth) {
                    PortApplyImpulse(car, otherCar, velocity, 1, 0);
                    if ((separation.x < 0) && ((otherCar->type) != 0)) {
                        (otherCar->speed) = 0;
                    }
                } else {
                    beyondFar = collisionHalfWidth < tmp1;
                    if (beyondFar == 0) {
                        tmp0 = otherCar->velocityX;
                        tmp1 = otherCar->velocityY;
                        scratchA0 = (u32)tmp0 >> 31;
                        tmp0 = (tmp0 + scratchA0) >> 1;
                        work1 = tmp0 << 16;
                        tmp0 = (u32)tmp1 >> 31;
                        tmp1 += tmp0;
                        tmp1 >>= 1;
                        work0 = tmp1 << 16;
                        asm volatile("" : : "r"(work1), "r"(work0));
                        PortApplyImpulse(car, otherCar, velocity, 0, 1);
                    }
                }
                nextCallback = (s32)CarApplyRandomHeadingImpulse;
                if ((((car->type) != 1) ||
                     (nextCallback != (s32)func_80025730)) &&
                    (((s32)car->callback) != (s32)func_80025730) &&
                    ((car->mode) != 4)) {
                    car->callback = (void (*)(Car *))nextCallback;
                }
                result = 2;
                if ((car->type) == 0) {
                    func_8003AC18(otherCar, relativeSpeed, separation.x,
                                  separation.y);
                    return 2;
                }
                return result;
            }
            if ((tmp0 = work2 < scratchA1) != 0) {
                (car->unk1CE) = 7;
                result = 3;
                if ((otherCar->type) == 1) {
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
#undef PortApplyImpulse
}
