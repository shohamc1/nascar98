void func_800406D0(Car *arg0, Car *arg1, s32 arg2, s32 arg3) {
    extern u8 D_800A2F9DSmall __asm__("D_800A2F9D");
    Car *car;
    Car *obj;
    s32 camX;
    s32 camY;
    s32 camZ;
    s32 dx;
    s32 dy;
    register s32 dz;
    s32 dist;
    register s32 fog;
    s32 pan;
    s32 q;
    register s32 gain;
    register s32 vol1;
    register s32 vol2;
    s16 out[2];
    register s32 row;
    register s32 scaled;
    register s32 square;
    s32 sum;
    register s32 dySq;
    register s32 prodB;
    register s32 prodA;
    register s32 one;
    register s32 magic;
    register s32 hi;
    register s32 quot;
    s32 sign;

    camX = arg0->pos.x;
    camY = arg0->pos.y;
    camZ = arg0->pos.z;
    car = arg0;
    obj = arg1;
    if (D_800A2F9DSmall == 0) {
        return;
    }
    if (D_800A2EC0nm[0] - D_800BE890w16[0] < 10) {
        return;
    }
    D_800BE890w16[0] = D_800A2EC0nm[0];
    if (func_8003702C(car, obj) < 0) {
        if (-func_8003702C(car, obj) >= 0x29) {
            goto fail;
        }
    } else {
        if (func_8003702C(car, obj) >= 0x29) {
        fail:
            SoundSetSlotVolume((s8)arg2, 0, 0);
            return;
        }
    }
    row = obj->pos.x;
    dx = (row - camX) >> 4;
    row = obj->pos.y;
    dy = (row - camY) >> 4;
    row = obj->pos.z;
    dz = (row - camZ) >> 4;
    sum = dx * dx;
    dySq = dy * dy;
    square = dz * dz;
    sum = sum + dySq;
    dist = MathSqrt(sum + square);
    magic = 0x5D9F0000;
    if (dist >= 0x579) {
        SoundSetSlotVolume((s8)arg2, 0, 0);
        return;
    }
    magic = magic | 0x7391;
    scaled = (dist << 8) - dist;
    /* mult scaled, magic; mfhi hi: the high word of the signed product. */
    sign = scaled >> 31;
    hi = (s32)(((s64)scaled * magic) >> 32);
    quot = hi >> 9;
    fog = quot - sign;
    if (fog >= 0x100) {
        fog = 0xFF;
    }
    VectorRotate2D((0x400 - car->heading) & 0x3FF, dx, dy, out);
    pan = out[1];
    if (pan > 0) {
        q = MathFixedDivide(pan, dist);
        gain = D_80098C00w16[fog];
        one = 0x10000;
        prodA = (q + one) * gain;
        vol2 = prodA >> 16;
        prodB = (one - q) * gain;
        vol1 = prodB >> 16;
    } else {
        if (pan < 0) {
            pan = -pan;
        }
        q = MathFixedDivide(pan, dist);
        gain = D_80098C00w16[fog];
        one = 0x10000;
        prodA = (q + one) * gain;
        vol1 = prodA >> 16;
        prodB = (one - q) * gain;
        vol2 = prodB >> 16;
    }
    if (vol2 >= 0x65) {
        vol2 = 0x64;
    }
    if (vol1 >= 0x65) {
        vol1 = 0x64;
    }
    if (D_800A306Cw16[0] != 0) {
        if (vol1 < vol2) {
            vol1 = vol2;
        } else {
            vol2 = vol1;
        }
    }
    SoundPlaySlot((s8)arg2, (s8)arg3);
    SoundSetSlotVolume((s8)arg2, (u8)vol2, (u8)vol1);
}
