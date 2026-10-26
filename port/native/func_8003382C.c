/*
 * Retail (handwritten) classifies IR1 to IR3 into out[3]. When IR3 is not
 * negative it branches into func_80033704's tail (bgez a2,
 * func_80033704+0x20), which sets 0x1F for a near depth; its own copy of
 * the tail runs only for a negative IR3 (clamped to 0) and sets 0x10.
 */
void func_8003382C(s16 *out) {
    s32 x;
    s32 y;
    s32 z;
    s32 flags;
    s32 nearFlags;

    x = PortGteRead(9);
    y = PortGteRead(10);
    z = PortGteRead(11);
    nearFlags = 0x1F;
    if (z < 0) {
        z = 0;
        nearFlags = 0x10;
    }
    flags = 4;
    if (z >= x) {
        flags = (z < -x) << 1;
    }
    if (z < y) {
        flags |= 1;
    } else if (z < -y) {
        flags |= 8;
    }
    if (z < 500) {
        flags |= 0x100;
        if (z < 5) {
            flags |= nearFlags;
        }
    }
    out[3] = flags;
}
