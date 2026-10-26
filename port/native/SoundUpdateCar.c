void SoundUpdateCar(Car *car) {
    extern u32 RandomGetScaled16(s32);
    extern void SoundUpdateOpponentVoice(Car *, s32);
    extern void func_800400D8Pair(Car *, Car *) asm("func_800400D8");
    extern s8 D_800A354F[];
    s32 i;
    s32 distance;
    s32 pitch;
    s32 blend;
    s32 id;
    s32 volume;
    s32 decayVolume;
    s32 unusedHigh;
    s32 sample;
    s32 shiftedRpm;
    s8 *clearFlags;
    u16 rpm;
    CarLink *next;
    CarLink *previous;
    s8 *flags;
    s8 *fade;
    s32 *handles;
    s32 *positions;
    s32 *pending;
    s32 initialized;
    s32 channel;
    s32 one;
    s32 minusOne;
    s32 five;

    if (D_800A2ED4[0] == 1) {
        for (i = 0; i < 5; i++) {
            SoundSetSlotVolume((s8)i, 0, 0);
        }
        for (i = 14; i < 18; i++) {
            SoundStopSlot((s8)i);
        }
        return;
    }
    if (D_800A2EACAbsolute[0] == 0 || D_800A2EACAbsolute[0] >= 3) {
        if (D_800A2EC8[0] == 0 && car->unk3B8 > 0) {
            id = 20;
            if (car != gPlayerCar[0]) {
                id = 21;
            }
            if ((s8)car->unk3B9 == 0) {
                car->unk3B8 -= 3;
                if (car->unk3B8 <= 0) {
                    car->unk3B8 = 0;
                    SoundStopSlot((s8)id);
                }
            }
            decayVolume = (car->unk3B8 * 4 + 31) & 0xFF;
            SoundSetSlotVolume((s8)id, decayVolume, decayVolume);
        }
        func_80040AC8(car);
        if (D_800A2F9D != 0) {
            rpm = (u16)car->rpm;
            pitch = ((s16)rpm + car->unk10A) / 100;
            if ((s16)rpm >= 2001 && car->speed <= 0x95FFFF &&
                D_800A2EC8[0] == 0 &&
                RandomGetScaled16((s16)((s16)rpm / 1000)) == 0) {
                pitch -= pitch / (s16)(car->rpm / 1700);
            }
            /* Retail keeps this unused filter calculation. */
            blend = pitch + car->unk3BA + car->unk3BA + car->unk3BA + 3;
            asm("" : : "r"(blend) : "memory");
            if (car->rpm >= 7001 && D_800A2EC8[0] == 0 &&
                RandomGetScaled16((s16)(car->rpm / 1000)) == 0) {
                /* Retail also keeps this unused signed high product. */
                register s32 magic;
                u16 highRpm;
                highRpm = (u16)car->rpm;
                shiftedRpm = (u32)highRpm << 16;
                asm("" : "=r"(shiftedRpm) : "0"(shiftedRpm));
                sample = shiftedRpm >> 16;
                magic = 0x134679AD;
                /* mult sample, magic: the high word goes to unusedHigh. */
                unusedHigh = (s32)(((s64)sample * magic) >> 32);
                asm("" : : "r"(unusedHigh));
            }
            volume = 100;
            if (car->driveInput >= 4097) {
                volume = 127;
            }
            if (car->unk1CA + 7 < volume) {
                car->unk1CA = car->unk1CA + 7;
            } else if (volume < car->unk1CA - 3) {
                car->unk1CA = car->unk1CA - 3;
            } else {
                car->unk1CA = volume;
            }
            if (car->unk1CA >= 128) {
                car->unk1CA = 127;
            }
            volume = car->unk1CA;
            pitch = (car->rpm + car->unk10A) / 110 - 32;
            if (car->unk3CA >= 18) {
                pitch = 78;
            }
            pitch += car->driveInput >> 11;
            if (car->unk3BA + 7 < pitch) {
                car->unk3BA = car->unk3BA + 7;
            } else if (pitch < car->unk3BA - 5) {
                car->unk3BA = car->unk3BA - 5;
            } else {
                car->unk3BA = pitch;
            }
            if (car->unk3BA >= 128) {
                car->unk3BA = 127;
            }
            pitch = car->unk3BA;
            if (car == gPlayerCar[0]) {
                func_8003FA84(0, (s8)pitch);
                SoundSetSlotVolume(0, volume & 0xFF, volume & 0xFF);
            } else {
                if (gPlayerCar[0]->unk3BA >= 125 && pitch >= 125) {
                    pitch = 120;
                }
                SoundSetSlotVolume(1, volume & 0xFF, volume & 0xFF);
                func_8003FA84(1, (s8)pitch);
            }
            i = 3;
            if (D_800A2E94[0] == 24) {
                next = (CarLink *)car->sectionLink.node.next;
                previous = (CarLink *)car->sectionLink.node.previous;
                clearFlags = D_800A354F;
                D_800A39D0B = 0;
                do {
                    *clearFlags = 0;
                    i--;
                    clearFlags--;
                } while (i >= 0);
                for (i = 0; i < 4; i++) {
                    distance = ABS(func_8003702C(car, next->car));
                    if (distance < ABS(func_8003702C(car, previous->car))) {
                        func_800400D8Pair(next->car, car);
                        next = (CarLink *)next->node.next;
                    } else {
                        func_800400D8Pair(previous->car, car);
                        previous = (CarLink *)previous->node.previous;
                    }
                }
                channel = 0;
                if (D_800A39D0B > 0) {
                    initialized = 0;
                    one = 1;
                    minusOne = -1;
                    five = 5;
                    fade = D_800A2FA4B;
                    handles = D_800BE988;
                    positions = D_80098D00;
                    flags = D_800A354CB;
                    pending = D_800BA048B;
                initializeChannel:
                    if (*flags == 0 && *fade == 0) {
                        *flags = one;
                        *positions = *pending;
                        *handles = minusOne;
                        *fade = five;
                        initialized++;
                        pending++;
                        if (initialized == D_800A39D0B) {
                            goto channelsReady;
                        }
                    }
                    fade++;
                    handles++;
                    positions++;
                    channel++;
                    flags++;
                    if (channel < 4) {
                        goto initializeChannel;
                    }
                }
            channelsReady:
                SoundUpdateOpponentVoice(car, 1);
                SoundUpdateOpponentVoice(car, 2);
                SoundUpdateOpponentVoice(car, 3);
                SoundUpdateOpponentVoice(car, 4);
            }
        }
    }
}
