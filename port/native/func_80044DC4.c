void func_80044DC4(u8 *arg0, s32 arg1, u8 *arg2) {
    register u8 *prim;
    register u8 *walker;
    register u8 *pe;
    s32 count;
    u8 *rgb;
    u8 g;
    u8 b;
    register u8 rv;
    register u8 rtmp;
    register s32 obt;
    register u32 *a0arg;
    register u32 *a1arg;
    u32 a2arg;
    u16 xy0;
    u16 xy1;
    u16 xy2;
    u16 xy3;
    u8 btmp;
    register s32 gte;
    register s32 otEntry;
    volatile struct {
        u8 r;
        u8 pad1[7];
        s32 otBase;
        u8 pad2[4];
    } st;
#define r st.r
#define otBase st.otBase
    register s32 v0_;
    register s32 v1_;
    register s32 v2_;
    register s32 w3;
    register s32 masked;

    otBase = (s32)gOrderingTable[0] + 0x20;
    prim = (u8 *)gPrimitiveCursor[0];
    rgb = arg2;
    count = arg1;
    rtmp = rgb[0];
    r = rtmp;
    g = rgb[1];
    b = rgb[2];
    if (count > 0) {
        walker = arg0 + 0x24;
        pe = prim + 0xE;
        do {
            v0_ = *(s32 *)&((Face *)(walker - 0x24))->vertex[0];
            v1_ = *(s32 *)&((Face *)(walker - 0x24))->vertex[1];
            v2_ = *(s32 *)&((Face *)(walker - 0x24))->vertex[2];
            gte_ldv3(v0_, v1_, v2_);
            gte_rtpt();
            SetLineF4(prim);
            gte_cfc2(gte, 31);
            masked = gte & 0x66000;
            if (masked != 0) {
                goto next;
            }
            gte_nclip();
            rv = r;
            ((LINE_F4 *)(pe - 0xE))->g0 = g;
            ((LINE_F4 *)(pe - 0xE))->b0 = b;
            ((LINE_F4 *)(pe - 0xE))->r0 = rv;
            gte_mfc2(gte, 24);
            if (D_800A2DE0[0] != 0) {
                if (gte < 0) {
                    goto next;
                }
            } else {
                if (gte > 0) {
                    goto next;
                }
            }
            gte_avsz3();
            gte_mfc2(gte, 7);
            gte += (s32)(s8) * (walker - 0x23) * 4;
            gte_stsxy3(prim + 8, prim + 0xC, prim + 0x10);
            w3 = *(s32 *)(walker);
            gte_ldv0(w3);
            gte_rtps();
            gte_stsxy(prim + 0x14);
            otEntry = gte >> 4;
            otEntry = otEntry << 2;
            obt = otBase;
            otEntry = obt + otEntry;
            GraphicsAddTaggedPrimitive((u32 *)otEntry, (u32 *)prim, 0x06000000);
            prim += 0x1C;
            pe += 0x1C;
            SetLineF2(prim);
            xy0 = ((LINE_F4 *)(pe - 0x2A))->y0;
            xy1 = ((LINE_F4 *)(pe - 0x2A))->x3;
            xy2 = ((LINE_F4 *)(pe - 0x2A))->y3;
            ((LINE_F2 *)(pe - 0xE))->r0 = rgb[0];
            xy3 = ((LINE_F4 *)(pe - 0x2A))->x0;
            a0arg = (u32 *)otEntry;
            ((LINE_F2 *)(pe - 0xE))->g0 = rgb[1];
            btmp = rgb[2];
            xy3 = ((LINE_F4 *)(pe - 0x2A))->x0;
            a1arg = (u32 *)prim;
            /* lui a2arg, 0x300 */
            a2arg = 0x3000000;
            prim += 0x10;
            ((LINE_F2 *)(pe - 0xE))->y0 = xy0;
            ((LINE_F2 *)(pe - 0xE))->x1 = xy1;
            ((LINE_F2 *)(pe - 0xE))->y1 = xy2;
            ((LINE_F2 *)(pe - 0xE))->x0 = xy3;
            ((LINE_F2 *)(pe - 0xE))->b0 = btmp;
            GraphicsAddTaggedPrimitive(a0arg, a1arg, a2arg);
            pe += 0x10;
        next:
            walker += 0x2C;
        } while (--count > 0);
    }
    gPrimitiveCursor[0] = (u32)prim;
}
