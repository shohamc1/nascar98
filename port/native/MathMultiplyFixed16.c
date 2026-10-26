s32 MathMultiplyFixed16(s32 arg0, s32 arg1) {
    s64 product;
    u32 lo;
    u32 hi;

    /* mult arg0, arg1; mflo lo; mfhi hi */
    product = (s64)arg0 * arg1;
    lo = (u32)product;
    hi = (u32)(product >> 32);
    return (lo >> 16) | (hi << 16);
}
