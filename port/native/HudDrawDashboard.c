void HudDrawDashboard(void) {
    /* Preserve the temporary packet layout used by the draw loops. */
    s16 points[16];
    s16 angles[4];
    s16 streakAngles[4];
    s16 *cornerRows[2];
    u32 intensityBytes[2];
    u8 framePad[8];
    register s32 product;
    s32 productY;
    register s32 next;
    s32 cosine;
    s32 sine;
    s32 offset;
    s32 count;
    register s32 vertex;
    register s32 i;
    register s16 *point;
    s16 *corner;
    POLY_F4 *needle;
    register u32 cachedAngle;
    register s32 argA;
    register s32 argB;
    s32 callResult;
    s32 nextVertex;
    register s32 screenY;
    register s16 *baseCorner;

    if (gSplitScreenMode[0] == 0) {
        i = 0;
    copyHud1:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(D_800A8184 + (s16)i * 0x18);
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(gOrderingTable[0] + 0x10), entry);
            next = i + 1;
            do {
                i = next;
            } while (0);

            if ((s16)next < 2)
                goto copyHud1;
        }
        i = 0;
        PushMatrix();
        func_800474A0();
        do {
            baseCorner = D_8009935C;

            cornerRows[0] = baseCorner;
            switch ((s16)i) {
            case 0: {
                Car *car;
                s32 rpm;
                s32 numerator;
                register s32 quotient;
                register s32 trueFactor;
                register s32 falseFactor;
                register s32 trueHigh;
                register s32 falseHigh;
                s64 wideProduct;

                /* Scale the tachometer angle by 585/13250 or 658/13250. */
                car = gPlayerCar[0];
                rpm = car->unk402;
                if (car->automatic != 0 || car->gearIndex == car->unk110) {
                    trueFactor = 0x9E468F35;
                    numerator = rpm * 585;
                    /* mult numerator, trueFactor; mfhi trueHigh */
                    wideProduct = (s64)numerator * trueFactor;
                    trueHigh = (s32)(wideProduct >> 32);
                    quotient = trueHigh + numerator;
                } else {
                    falseFactor = 0x9E468F35;
                    numerator = rpm * 658;
                    /* mult numerator, falseFactor; mfhi falseHigh */
                    wideProduct = (s64)numerator * falseFactor;
                    falseHigh = (s32)(wideProduct >> 32);
                    quotient = falseHigh + numerator;
                }
                quotient >>= 13;
                numerator >>= 31;
                quotient -= numerator;
                quotient += 256;
                do {

                    angles[0] = quotient;
                } while (0);
            }
                baseCorner = D_8009936C;

                cornerRows[0] = baseCorner;
                break;
            case 1:
                if (D_800A2ED4[0] == 0) {
                    if (RandomScaledGet(2)) {
                        productY = -RandomScaledGet(gPlayerCar[0]->speed >> 20);
                    } else {
                        productY = RandomScaledGet(gPlayerCar[0]->speed >> 20);
                    }
                    productY += 0x300;
                    D_800A3494 = productY;
                    angles[0] = productY;
                } else {
                    cachedAngle = D_800A3494;

                    angles[0] = cachedAngle;
                }
                break;
            case 2: {
                s32 speed;
                s32 scaledSpeed;
                register s32 factor;
                register s32 high;
                register s32 angleQuot;
                s64 wideProduct;

                /* Scale speed by 768/16000 for the speedometer angle. */
                speed = gPlayerCar[0]->unk28C;
                factor = 0x10624DD3;
                scaledSpeed = speed * 768;
                /* mult scaledSpeed, factor: mfhi below reads the high word. */
                wideProduct = (s64)scaledSpeed * factor;
                scaledSpeed >>= 31;
                high = (s32)(wideProduct >> 32); /* mfhi */
                angleQuot = high >> 10;
                angleQuot -= scaledSpeed;
                angleQuot += 0x180;
                angleQuot &= 0x3FF;
                angles[0] = angleQuot;
                break;
            }
            case 3:
                angles[0] =
                    ((s32)((u8)gPlayerCar[0]->unk3FD << 24) >> 21) + 0x2D8;
                break;
            }
            vertex = 0;
            {
                register u32 angleWord;
                register s32 index;
                register s32 *cosineTable;
                register s32 *sineTable;
                extern s32 *hudCosine __asm__("gCosTable");
                extern s32 *hudSine __asm__("gSinTable");

                index = i << 16;
                angleWord = *(u16 *)angles;

                offset = index >> 14;
                cosineTable = hudCosine;
                sineTable = hudSine;
                index = (s32)(angleWord << 16) >> 14;
                cosineTable = (s32 *)(index + (u32)cosineTable);
                cosine = *cosineTable;
                sineTable = (s32 *)(index + (u32)sineTable);
                sine = *sineTable;
            }
        rotateCorner:
            {
                register s16 *base;

                base = cornerRows[0];

                count = (s32)(vertex << 16) >> 14;
                corner = (s16 *)(count + (u32)base);

                argB = corner[0];
                argA = cosine;
            }
            callResult = MathMultiplyFixed16(argA, argB << 16);
            argB = corner[1];
            argA = sine;
            product = callResult;
            callResult = MathMultiplyFixed16(argA, argB << 16);
            {
                u32 centerX;

                point = points;

                centerX = *(u16 *)(offset + (u32)D_8009934C);
                point = (s16 *)((u8 *)point + count);
                asm("" : "=r"(point) : "0"(point), "r"(centerX), "r"(product));
                product -= callResult;
                product >>= 16;
                centerX += product;
                point[0] = centerX;
                argB = corner[0];
                argA = sine;
            }
            callResult = MathMultiplyFixed16(argA, argB << 16);
            argB = corner[1];
            argA = cosine;
            product = callResult;
            callResult = MathMultiplyFixed16(argA, argB << 16);
            screenY = (u8)D_800A2FD4[0];

            nextVertex = vertex + 1;
            vertex = nextVertex;
            asm("" : "=r"(nextVertex) : "0"(nextVertex));
            argB = *(u16 *)(offset + (u32)D_8009934E);

            product += callResult;
            product >>= 16;
            nextVertex = (s16)nextVertex < 4;
            point[1] = (s8)screenY + (argB + product);
            if (nextVertex)
                goto rotateCorner;
            {
                register s32 copyIndex;
                s32 copyOffset;
                register u32 needleBase;

                copyIndex = (s16)i;
                needleBase = (u32)D_800A81B4;
                copyOffset = copyIndex << 1;

                argA = *(u16 *)points;
                copyOffset += copyIndex;
                copyOffset <<= 3;
                needle = (POLY_F4 *)(copyOffset + needleBase);
            }
            needle->x0 = argA;
            needle->y0 = points[1];
            needle->x1 = points[2];
            needle->y1 = points[3];
            needle->x2 = points[4];
            needle->y2 = points[5];
            needle->x3 = points[6];
            needle->y3 = points[7];
            next = i + 1;
            do {
                i = next;
            } while (0);

        } while ((s16)next < 4);
        D_800A3008 = D_800A3480 * -15;
        RotMatrix(D_800A3004, D_800A7FC4);
        SetRotMatrix(D_800A7FC4);
        SetTransMatrix(D_800A7FC4);
        {
            u8 *dest;
            register u8 *source;
            register u8 *out;
            u32 *ot;
            s32 count;
            s32 product;
            struct PacketWords {
                s32 w0;
                s32 w1;
                s32 w2;
                s32 w3;
                s32 w4;
            };
            struct PacketWords *from;
            struct PrimitiveWords {
                u32 tag, color, xy0, uv0, xy1, uv1, xy2, uv2, xy3, uv3;
            };
            struct PrimitiveWords *poly;
            register s32 w0;
            s32 w1;
            register s32 w2;
            s32 w3;
            s32 w4;
            register SVECTOR *p0;
            register SVECTOR *p1;
            register SVECTOR *p2;
            /* Project the 36 dashboard quads through the GTE. */
            dest = (u8 *)gHudPrimitiveCursor;
            count = 36;
            source = D_800A7995;
            ot = (u32 *)gOrderingTable[0];
            out = dest + 0x18;
            do {
                p0 = ((Face *)(source - 1))->vertex[0];
                p1 = ((Face *)(source - 1))->vertex[1];
                p2 = ((Face *)(source - 1))->vertex[2];
                gte_ldv3(p0, p1, p2);
                asm volatile(
                    ".set\tnoreorder\n\tnop\n\tnop\n\trtpt\n\t.set\treorder");
                asm volatile(
                    ".set\tnoreorder\n\tnop\n\tnop\n\tavsz3\n\t.set\treorder");
                from = (struct PacketWords *)(source + 3);
                poly = (struct PrimitiveWords *)(out - 0x18);
                w2 = from->w2;
                w0 = from->w0;
                w1 = from->w1;
                w3 = from->w3;
                w4 = from->w4;

                poly->uv1 = w2;
                poly->uv0 = w1;
                poly->color = w0;
                poly->uv2 = w3;
                poly->uv3 = w4;
                gte_stsxy3(dest + 8, dest + 0x10, dest + 0x20);
                p0 = ((Face *)(source - 1))->vertex[3];
                gte_ldv0(p0);
                asm volatile(
                    ".set\tnoreorder\n\tnop\n\tnop\n\trtps\n\t.set\treorder");
                gte_stsxy(out);
                argB = (s32)dest;
                count--;
                product = *(s8 *)source;
                source += 0x2C;
                out += 0x28;
                dest += 0x28;
                GraphicsAddTaggedPrimitive(ot + product, (u32 *)argB,
                                           0x09000000);
            } while (count > 0);
            gHudPrimitiveCursor = (u32)dest;
        }
        i = 0;
    copyHud2:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(D_800A81B4 + (s16)i * 24);
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(gOrderingTable[0] + 8), entry);
            next = i + 1;
            do {
                i = next;
            } while (0);

            if ((s16)next < 4)
                goto copyHud2;
        }
        i = 0;
    copyHud3:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = &D_800A8214[(s16)i];
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(gOrderingTable[0] + 16), entry);
            next = i + 1;
            do {
                i = next;
            } while (0);

            if ((s16)next < 4)
                goto copyHud3;
        }
        i = 0;
    copyHud4:
        {
            u32 raw;
            POLY_FT4 *entry;
            POLY_FT4 *prim;
            prim = (POLY_FT4 *)(D_800A82B4 + (s16)i * 40);
            raw = gHudPrimitiveCursor;
            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
            entry = (POLY_FT4 *)raw;
            *entry = *prim;
            AddPrim((void *)(gOrderingTable[0] + 16), entry);
            next = i + 1;
            do {
                i = next;
            } while (0);

            if ((s16)next < 4)
                goto copyHud4;
        }
        {
            register s32 product;
            s32 productX;
            s32 rotatedX;
            register s32 returnedValue;
            register s32 rowOffset;
            u16 *center;

            register u32 intensityValue;
            register u32 reloadIntensity;
            register u16 rawAngle;
            register u32 shifted;
            s32 signedAngle;
            i = 0;
            streakAngles[0] = (D_800A348C + 0x120) & 0x3FF;
            do {
                rawAngle = *(u16 *)streakAngles;
                asm("" : "=r"(rawAngle) : "0"(rawAngle));
                shifted = (u32)rawAngle << 16;
                signedAngle = (s32)shifted >> 16;
                if (signedAngle < 0x200) {
                    if (signedAngle - 0x100 >= 0) {
                        offset = (u32)(0x200 - signedAngle) >> 2;
                    } else {
                        offset = shifted >> 18;
                    }
                    intensityValue = offset & 0xFF;

                    intensityBytes[0] = intensityValue;
                    if (intensityValue >= 8) {
                        {
                            s32 index;
                            register s32 width;
                            register u32 angleWord;
                            u32 centers;
                            register u32 angleIndex;
                            register u32 centerValue;
                            extern s32 *hudCosine __asm__("gCosTable");
                            extern s32 *hudSine __asm__("gSinTable");

                            index = (s16)i;
                            width = D_800A2FD8[index];
                            asm("" : "=r"(width) : "0"(width));
                            angleWord = *(u16 *)streakAngles;
                            asm("" : "=r"(angleWord) : "0"(angleWord));
                            argB = 0x200;
                            centers = (u32)D_800A2FDC;

                            center = (u16 *)(index * 2 + centers);
                            centerValue = *center;
                            callResult = index * 5;

                            rowOffset = callResult << 3;
                            product = intensityValue >> 1;

                            product <<= 16;
                            width = (s8)width;
                            angleIndex = angleWord;
                            argB -= angleIndex;
                            argB >>= 7;
                            centerValue -= width;
                            centerValue = argB + centerValue;
                            *(s16 *)(rowOffset + (u32)D_800A853C) = centerValue;

                            do {
                                callResult = D_800A2FD8[index];
                            } while (0);

                            asm("" : "=r"(callResult) : "0"(callResult));
                            centerValue = *center;
                            argA = (s32)hudCosine;
                            callResult = (s8)callResult;
                            centerValue += callResult;
                            callResult = (s32)hudSine;
                            angleIndex <<= 2;
                            argB += centerValue;
                            argA = angleIndex + argA;
                            *(s16 *)(rowOffset + (u32)D_800A8544) = argB;
                            cosine = *(s32 *)argA;
                            argB = 0x640000;
                            angleIndex += callResult;

                            sine = *(s32 *)angleIndex;
                        }
                        callResult = MathMultiplyFixed16(cosine, argB);
                        argB = product;
                        productX = callResult;
                        callResult = MathMultiplyFixed16(sine, argB);
                        argA = sine;
                        argB = 0x640000;

                        rotatedX = callResult;
                        HudMultiplyVoid(argA, argB);
                        callResult = returnedValue;
                        argA = cosine;
                        argB = product;
                        product = callResult;
                        HudMultiplyVoid(argA, argB);
                        callResult = returnedValue;
                        argA = *center;
                        screenY = (productX - rotatedX) >> 16;
                        argA += screenY;
                        *(s16 *)(rowOffset + (u32)D_800A854C) = argA;

                        screenY = (u8)D_800A2FD4[0];
                        asm("" : "=r"(screenY) : "0"(screenY));
                        argA = (product + callResult) >> 16;
                        screenY = (s8)screenY;
                        screenY += 0x9E;
                        argA += screenY;
                        *(s16 *)(rowOffset + (u32)D_800A854E) = argA;

                        screenY = *center;
                        productX += rotatedX;
                        productX >>= 16;
                        screenY += productX;
                        *(s16 *)(rowOffset + (u32)D_800A8554) = screenY;

                        do {
                            screenY = (u8)D_800A2FD4[0];
                        } while (0);

                        asm("" : "=r"(screenY) : "0"(screenY));
                        product -= callResult;
                        product >>= 16;
                        screenY = (s8)screenY;
                        screenY += 0x9E;
                        product += screenY;
                        *(s16 *)(rowOffset + (u32)D_800A8556) = product;

                        reloadIntensity = intensityBytes[0];
                        next = reloadIntensity < 33;

                        if (!next)
                            offset = 32;
                        {
                            u32 raw;
                            POLY_FT4 *entry;
                            register POLY_FT4 *prim;
                            prim = (POLY_FT4 *)(rowOffset + (u32)D_800A8534);

                            prim->r0 = offset;
                            prim->g0 = offset;
                            prim->b0 = offset;
                            raw = gHudPrimitiveCursor;
                            gHudPrimitiveCursor = raw + sizeof(POLY_FT4);
                            entry = (POLY_FT4 *)raw;
                            *entry = *prim;
                            AddPrim((void *)(gOrderingTable[0] + 0x10), entry);
                        }
                    }
                }
                {
                    register u32 angleRaw;
                    register u32 angleNext;

                    angleRaw = *(u16 *)streakAngles;

                    angleNext = (angleRaw + 0x3E0) & 0x3FF;
                    streakAngles[0] = angleNext;
                }
                next = i + 1;
                do {
                    i = next;
                } while (0);

            } while ((s16)next < 3);
        }
        PopMatrix();
    }
    i = 0;
copyHud5:
    {
        register u32 raw;
        u32 mode;
        s32 row;
        register s32 copyOffset;
        s32 modeOffset;
        s32 rowOffset;
        register POLY_FT4 *entry;
        POLY_FT4 *copyDest;
        u32 sourceBase;
        POLY_FT4 *prim;
        mode = D_800A2ED9[0];
        row = (s16)i;

        do {
            raw = gHudPrimitiveCursor;
        } while (0);

        do {
            modeOffset = mode * 240;
        } while (0);

        rowOffset = row * 40;

        copyOffset = modeOffset + rowOffset;
        entry = (POLY_FT4 *)raw;

        copyDest = entry;

        sourceBase = (u32)D_800A8354;
        prim = (POLY_FT4 *)(copyOffset + sourceBase);
        gHudPrimitiveCursor = (u32)entry + sizeof(POLY_FT4);
        *copyDest = *prim;
        AddPrim((void *)(gOrderingTable[0] + 0x10), entry);
        next = i + 1;
        do {
            i = next;
        } while (0);

        if ((s16)next < 6)
            goto copyHud5;
    }
    i = 0;
copyHud6:
    {
        register u32 raw;
        register u32 mode;
        s32 row;
        s32 copyOffset;
        s32 modeOffset;
        register POLY_FT4 *entry;
        POLY_FT4 *copyDest;
        u32 sourceBase;
        POLY_FT4 *prim;
        mode = D_800A2ED9[0];
        row = (s16)i;
        asm volatile("" : "=r"(row) : "0"(row), "r"(mode) : "memory");
        raw = gHudPrimitiveCursor;
        asm("" : "=r"(raw) : "0"(raw));
        modeOffset = mode * 9;

        do {
            copyOffset = row * 3;
        } while (0);

        copyOffset += modeOffset;
        copyOffset <<= 3;
        entry = (POLY_FT4 *)raw;

        copyDest = entry;

        sourceBase = (u32)D_800A80F4;
        prim = (POLY_FT4 *)(copyOffset + sourceBase);
        gHudPrimitiveCursor = (u32)entry + sizeof(POLY_FT4);
        *copyDest = *prim;
        AddPrim((void *)(gOrderingTable[0] + 0x10), entry);
        next = i + 1;
        do {
            i = next;
        } while (0);

        if ((s16)next < 3)
            goto copyHud6;
    }
}
