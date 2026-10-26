void func_800328AC(void *objects, s32 count) {
    register s32 v0s;
    u8 *nextObject;
    u8 *primitive;
    u32 doublesided;
    u8 *spad;
    u32 flagMask;
    u32 codeConst;
    register u8 *ot;
    register u8 *object;
    register u8 *prim20;
    s32 *vec0;
    s32 *vec1;
    s32 *vec2;
    s32 gteWord;
    register s32 w8;
    register s32 wC;
    register s32 w10;
    register s32 w14;

    nextObject = objects;
    asm("" : "=r"(nextObject) : "0"(nextObject));
    v0s = gOrderingTable[0];
    primitive = (u8 *)gPrimitiveCursor[0];
    doublesided = D_800A2DE0[0];
    flagMask = 0x66000;
    { u32 port_cond = 0, port_discard = 0; u32 port_hi = 0, port_lo = 0; u64 port_wide = 0; u32 port_o0 = 0; port_o0 = ((u32)8064 << 16); PORT_OUT(spad, port_o0); (void)port_cond; (void)port_discard; (void)port_wide; }
    /* blez count, func_800328AC+0x1C0, with ot = v0s + 0x20 in the delay slot. */
    PORT_OUT(ot, PORT_VAL(v0s) + 0x20);
    if (count <= 0) {
        goto done;
    }
    codeConst = 0x0C000000;
    object = (u8 *)objects + 1;
    prim20 = primitive + 0x20;
    do {
        vec0 = *(s32 **)&((Face *)(object - 0x1))->vertex[0];
        vec1 = *(s32 **)&((Face *)(object - 0x1))->vertex[1];
        vec2 = *(s32 **)&((Face *)(object - 0x1))->vertex[2];
        gte_ldv3(vec0, vec1, vec2);
        w8 = *(s32 *)&((Face *)(object - 0x1))->u0;
        wC = *(s32 *)&((Face *)(object - 0x1))->u1;
        gte_op(rtpt);
        w10 = *(s32 *)&((Face *)(object - 0x1))->u2;
        w14 = *(s32 *)&((Face *)(object - 0x1))->u3;
        *(s32 *)&((POLY_GT4 *)(prim20 - 0x20))->u0 = w8;
        *(s32 *)&((POLY_GT4 *)(prim20 - 0x20))->u1 = wC;
        *(s32 *)&((POLY_GT4 *)(prim20 - 0x20))->u2 = w10;
        *(s32 *)&((POLY_GT4 *)(prim20 - 0x20))->u3 = w14;
        gte_cfc2(gteWord, 31);
        v0s = gteWord & flagMask;
        if (v0s != 0) {
            goto incr;
        }
        gte_op(nclip);
        w8 = *(s32 *)&((Face *)(object - 0x1))->r0;
        wC = w8 & 0xFF;
        w8 >>= 8;
        w10 = w8 & 0xFF;
        w8 >>= 8;
        w14 = w8 & 0xFF;
        v0s = wC << 2;
        v0s = v0s + (s32)spad;
        wC = *(u32 *)v0s;
        v0s = w10 << 2;
        v0s = v0s + (s32)spad;
        w10 = *(u32 *)v0s;
        v0s = w14 << 2;
        v0s = v0s + (s32)spad;
        w14 = *(u32 *)v0s;
        v0s = (w8 >> 6) & 0x3FC;
        v0s = v0s + (s32)spad;
        w8 = *(u32 *)v0s;
        gte_mfc2_nonop(gteWord, 24);
        if (doublesided != 0) {
            if (gteWord >= 0) {
                goto ok;
            }
            goto incr;
        } else if (gteWord > 0) {
            goto incr;
        }
    ok:
        gte_op(avsz3);
        v0s = 0x3C000000;
        v0s = wC | v0s;
        *(u32 *)&((POLY_GT4 *)(prim20 - 0x20))->r3 = w14;
        *(u32 *)&((POLY_GT4 *)(prim20 - 0x20))->r2 = w8;
        *(u32 *)&((POLY_GT4 *)(prim20 - 0x20))->r0 = v0s;
        *(u32 *)&((POLY_GT4 *)(prim20 - 0x20))->r1 = w10;
        gte_stsxy3(primitive + 0x8, primitive + 0x14, primitive + 0x2C);
        vec0 = *(s32 **)&((Face *)(object - 0x1))->vertex[3];
        gte_ldv0(vec0);
        gte_mfc2_nonop(gteWord, 7);
        v0s = ((Face *)(object - 0x1))->depth;
        gteWord = gteWord + v0s * 4;
        gte_op(rtps);
        w14 = gteWord >> 4;
        w14 = w14 << 2;
        w14 = w14 + (s32)ot;
        v0s = *(u32 *)w14;
        w8 = 0xFFFFFF;
        w8 = (u32)primitive & w8;
        v0s = v0s | codeConst;
        *(u32 *)primitive = v0s;
        *(u32 *)w14 = w8;
        gte_stsxy(prim20);
        prim20 += 0x34;
        primitive += 0x34;
    incr:
        count--;
        object += 0x2C;
        nextObject += 0x2C;
    } while (count > 0);
done:
    gPrimitiveCursor[0] = (u32)primitive;
    /* Retail also returns nextObject in $v0; every caller ignores it. */
}
