void EffectInitRandomOffsetTables(void) {
    s32 base;
    s32 m3base;
    s32 m3;
    u16 m1;
    u16 m2;
    register s32 d1;
    register s32 d2;
    register s32 d3;
    s32 d4;
    s32 value;
    register s32 temp;
    s32 value2;
    u16 masked;
    s32 value3;
    s32 prod;
    s32 prodlo;
    s32 rowOff;
    s32 end;
    s32 midOff;
    s32 mo;
    register s32 colOff;
    s32 off1;
    s32 off2;
    s32 off3;
    s32 i;
    s32 j;

    i = 0;
    base = 9;
    do {
        j = 0;
        rowOff = i * 0x40;
        m3base = i << 3;
        d1 = base;
        d2 = base; /* addu */
        m1 = base;
        d3 = base; /* addu */
        midOff = 0;
        do {
            mo = midOff;
            d4 = base; /* addu */
            m2 = base;
            m3 = m3base + 8;
            colOff = rowOff;
            do {
                temp = gRandomSeed16;
                off1 = colOff + mo;
                do {
                } while (0);
                value = (temp * 0x6255) + 0x3619;
                masked = (u16)value;
                gRandomSeed16 = masked;
                asm volatile("" ::: "memory");
                value &= 0xFFFF;
                m2 = base;
                value2 = ((value * 0x6255) + 0x3619) & 0xFFFF;
                gRandomSeed16 = value2;
                /* mult value2, m1: mflo below reads the product. */
                prodlo = value2 * m1; /* mflo */
                D_800B1A24[off1] = -(s32)((u32)prodlo >> 16);
                temp = gRandomSeed16;
                off2 = colOff + mo; /* addu */
                value = (temp * 0x6255) + 0x3619;
                masked = (u16)value;
                gRandomSeed16 = masked;
                asm volatile("" ::: "memory");
                value &= 0xFFFF;
                value2 = ((value * 0x6255) + 0x3619) & 0xFFFF;
                gRandomSeed16 = value2;
                /* mult value2, m2: mflo below reads the product. */
                prodlo = value2 * m2; /* mflo */
                D_800B1A25[off2] = -(s32)((u32)prodlo >> 16);
                temp = gRandomSeed16;
                m3 = m3base + 8;
                value3 = ((temp * 0x6255) + 0x3619) & 0xFFFF;
                gRandomSeed16 = value3;
                /* mult value3, m3: mflo below reads the product. */
                off3 = (u32)colOff - -(u32)mo;
                colOff += 4;
                prodlo = value3 * m3; /* mflo */
                D_800B1A26R[off3] = (s32)((u32)prodlo >> 16);
                end = rowOff + 0x40; /* addiu */
            } while (colOff < end);
            asm("" ::"r"(d4));
            j += 1;
            midOff += 0xC0;
        } while (j < 6);
        asm("" ::"r"(d1));
        asm("" ::"r"(d2));
        i += 1;
        base += 9;
    } while (i < 3);
}
