void func_8006FBB0Args(MovieFrame *frameData, s32 x, s16 y) {
    MovieContext *st;
    MovieContext *st2;
    register u32 bsw;
    u32 nsec;
    u32 w8;
    u32 cnt;
    u32 word;
    register u32 wA;
    u32 w8hi;
    u32 wAlo;
    u32 w8lo;
    u32 xv;
    u32 mdecId;
    register u32 prod;
    volatile MovieContext *vst;
    u32 mdecId2;
    s32 magic;
    u32 h16u;
    s32 prod2;
    u_long *outp;
    s32 w32;
    s32 h32;
    u32 i;

    word = frameData->header;
    st = gMovieContext;

    bsw = word >> 0x18;
    bsw = bsw | ((word >> 8) & 0xFF00);
    bsw = bsw | ((word & 0xFF00) << 8);
    magic = bsw | (word << 0x18);
    wA = frameData->height;
    cnt = wA >> 8; /* srl */
    wAlo = wA & 0xFF;
    w8 = frameData->width;
    wAlo = wAlo << 8;
    bsw = cnt | wAlo;
    cnt = st->unk118;
    w8hi = w8 >> 8; /* srl */
    w8lo = w8 & 0xFF;
    w8lo = w8lo << 8;
    nsec = w8hi | w8lo;
    if (cnt == 0) {
        wA = D_800A33A0;
        mdecId = 0x4D444543;
        asm("" : "=r"(xv) : "0"(x));
        st->uploadRects[0].x = x;
        st->uploadRects[0].y = y;
        st->uploadRects[0].h = bsw;
        st->uploadRects[1].y = y;
        st->uploadRects[1].h = bsw;
        /* mult nsec, wA: mflo below reads the product. */
        st->uploadX = xv;
        st->uploadY = y;
        do {
        } while (0);
        st->uploadRects[1].x = x + wA * 0xA0;
        st->imageWidth = wA * 8;
        st->imageHeight = bsw;
        st->activeRect = 0;
        prod = nsec * wA; /* mflo */
        w8 = prod >> 1;
        st->uploadRects[0].w = w8;
        st->uploadRects[1].w = w8;
        if (magic == mdecId) {
            func_800708D8((u8 *)frameData + 0x10,
                          (s32)st->decodeBuffers[st->decodeBufferIndex]);
        }
        ((volatile MovieContext *)gMovieContext)->uploadComplete = 0;
    } else {
        st->uploadComplete = 0;
        DecDCTin((u_long *)st->decodeBuffers[1 - st->decodeBufferIndex],
                 D_800A339C);
        st2 = gMovieContext;
        bsw = *(u16 *)((u8 *)st2 + 0x20);  /* lhu */
        h16u = *(u16 *)((u8 *)st2 + 0x22); /* lhu */
        w32 = (s16)bsw;
        h32 = (s16)h16u;
        /* mult w32, h32: mflo below reads the product. */
        outp = st2->imageBuffer;
        prod2 = w32 * h32; /* mflo */
        DecDCTout(outp, prod2 / 2);
        mdecId2 = 0x4D444543;
        if (magic == mdecId2) {
            st2 = gMovieContext;
            func_800708D8((u8 *)frameData + 0x10,
                          (s32)st2->decodeBuffers[st2->decodeBufferIndex]);
        }
        DecDCToutSync(0);
        vst = (volatile MovieContext *)gMovieContext;
        i = 0;
        if (vst->uploadComplete == 0) {
            bsw = 0x30D40;
        again:
            if (i > bsw) {
                goto done;
            }
            i++;
            if (vst->uploadComplete == 0) {
                goto again;
            }
        }
    }
done:
    DecDCTReset(1);
    gMovieContext->unk118 = gMovieContext->unk118 + 1;
    gMovieContext->decodeBufferIndex = 1 - gMovieContext->decodeBufferIndex;
}
