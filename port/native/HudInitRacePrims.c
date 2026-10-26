void HudInitRacePrims(void) {
    extern u8 D_800B0B7C[]; /* reached only from retail's asm */
    HudTexture *tex;
    POLY_FT4 *prim;
    TILE *p3;
    TILE *p4;
    u8 *f4base;
    s32 tileIndex;
    s32 tileBytes;
    s32 tileX;
    u8 *tileHeightBase;
    POLY_FT4 *heap;
    Glyph *glyph;
    s8 entry;
    s8 col;
    s8 line;
    s8 j;
    s8 row;
    u16 *page;
    s32 markerOffset;
    u8 *driver;
    u8 driverR;
    register s32 line24;
    s8 **slot;
    s8 **lineSlot;
    s32 glyphOffset;
    s32 cornerOffset;
    s32 value;
    u8 *slotBase;
    u8 *coord;
    POLY_FT4 *driverCall;
    u8 *driverBase;
    u32 borderFlag;
    u16 markerPage;
    register u8 *mapCall;
    POLY_FT4 *mapPrim;
    register s32 view;
    register u8 *coordX;
    s32 coordinateValue;
    register u8 *coordY;
    register s32 yOffset;

    D_800A3680[0] = 0;
    D_800A3490 = 0;
    D_800A2FD0[0] = -(gSplitScreenMode[0] != 0) & 0x92;
    for (entry = 0; entry < D_800A3424; entry++) {
        D_800A3485 = 0;
        for (col = 0; col < 6; col++) {
            {
                register u8 *addressBase;

                /* la addressBase, D_8009AE14; addu */
                addressBase = D_8009AE14;
                lineSlot = (s8 **)(addressBase + col * 4);
            }
            D_800A3485 += strlen((char *)*lineSlot);
        }
        D_800A3484Small = D_800A3485 + strlen((char *)D_8009AE2C[0]);
        for (col = 0; col < 3; col += 2) {
            line = 0;
            heap = (POLY_FT4 *)((u8 *)HeapAlloc(D_800A3484Small * 0x28));
            D_800A78C4[(s8)(entry + col)] = (s8 *)heap;
            for (; line < 7; line++) {
                j = 0;
                line24 = line << 24;
                {
                    register u8 *addressBase;

                    /* la addressBase, D_8009AE14; addu */
                    addressBase = D_8009AE14;
                    lineSlot = (s8 **)(addressBase + (line24 >> 22));
                }
                if ((*lineSlot)[0] != 0) {
                    do {
                        {
                            register u8 *addressBase;

                            do {
                                glyphOffset = line24 >> 22;
                            } while (0);
                            addressBase = (u8 *)D_8009AE14;
                            slot =
                                (s8 **)((u32)(glyphOffset) - -(u32)addressBase);
                        }
                        glyph = &gHudGlyphs[(*slot)[j]];
                        SetPolyFT4(heap);
                        heap->clut = GetClut(0x390, 0x3C);
                        heap->r0 = 0x80;
                        heap->g0 = 0x80;
                        heap->b0 = 0xC0;
                        heap->tpage = GetTPage(0, 0, glyph->x, glyph->y);
                        heap->u0 = glyph->u;
                        heap->v0 = glyph->v;
                        heap->u1 = glyph->u + *(u8 *)&glyph->width;
                        heap->v1 = glyph->v;
                        heap->u2 = glyph->u;
                        heap->v2 = glyph->v + *(u8 *)&glyph->height;
                        heap->u3 = glyph->u + *(u8 *)&glyph->width;
                        heap->v3 = glyph->v + *(u8 *)&glyph->height;
                        j++;
                        heap++;
                    } while ((*slot)[j] != 0);
                }
            }
        }
        row = entry;
        func_8004AFE0(row, D_80099298, (u16 *)D_800A78C4[row]);
        {
            register u8 *addressBase;

            /* la addressBase, D_800A78CC; addu */
            addressBase = (u8 *)D_800A78CC;
            slotBase = addressBase + row * 4;
        }
        func_8004AFE0(row, D_80099298, *(u16 **)slotBase);
        D_800A3488 = strlen((char *)((s8 **)D_8009AE14)[0]);
        prim = (POLY_FT4 *)((u8 *)D_800A78D4 + row * 0x28);
        SetPolyFT4(prim);
        SetSemiTrans(prim, 1);
        prim->code |= 1;
        prim->u0 = D_80090FF2[0];
        prim->v0 = D_80090FF4[0];
        prim->u1 = D_80090FF2a[0] + 0x3C;
        prim->v1 = D_80090FF4a[0];
        prim->u2 = D_80090FF2b[0];
        prim->v2 = D_80090FF4b[0] + 0x3C;
        prim->u3 = D_80090FF2c[0] + 0x3C;
        prim->v3 = D_80090FF4c[0] + 0x3C;
        prim->x0 = 0xF5;
        prim->y0 = D_800A2FD0[row] + 0xA0;
        prim->x1 = 0x131;
        prim->y1 = D_800A2FD0[row] + 0xA0;
        prim->x2 = 0xF5;
        prim->y2 = D_800A2FD0[row] + 0xDC;
        prim->x3 = 0x131;
        prim->y3 = D_800A2FD0[row] + 0xDC;
        *(u16 *)((u8 *)D_800A78E2 + row * 0x28) =
            GetClut(D_80090FEE[0], D_80090FF0[0]);
        tex = D_80090FEA;
        asm("" : "=r"(view) : "0"((s32)row));
        *(u16 *)((u8 *)D_800A78EA + row * 0x28) =
            GetTPage(D_80090FF6[0], 0, tex->tpx, D_80090FEC[0]);
        tex -= 14;
        for (col = 0; col < 10; col++) {
            {
                register u8 *addressBase;

                /* la addressBase, D_800A757C; addu with the column offset */
                addressBase = (u8 *)D_800A757C;
                mapCall = addressBase + col * 0x28;
            }
            mapCall = (u8 *)((u32)(view * 0x190) + (u32)mapCall);
            SetPolyFT4((POLY_FT4 *)mapCall);
            SetShadeTex(mapCall, 0);
            {
                register u8 *addressBase;

                /* la addressBase, D_800A757C; addu */
                addressBase = (u8 *)D_800A757C;
                mapPrim = (POLY_FT4 *)(addressBase + view * 0x190 + col * 0x28);
            }
            mapPrim->r0 = 0x40;
            mapPrim->g0 = 0x40;
            mapPrim->b0 = 0x40;
            mapPrim->u0 = tex->u + 0x60;
            mapPrim->v0 = tex->v;
            mapPrim->u1 = tex->u + 0x6F;
            mapPrim->v1 = tex->v;
            mapPrim->u2 = tex->u + 0x60;
            mapPrim->v2 = tex->v + 0xF;
            mapPrim->u3 = tex->u + 0x6F;
            mapPrim->v3 = tex->v + 0xF;
            *(u16 *)(view * 0x190 + col * 0x28 + (u8 *)D_800A7592) =
                GetTPage(tex->tpage, 0, tex->tpx, tex->tpy);
            {
                register s32 cornerPrefix;

                cornerPrefix = col * 12;
                coord = (u8 *)gCosTableAbsolute[0];
                cornerPrefix += col;
                cornerPrefix = cornerPrefix * 8 + 0x828;
                cornerOffset = cornerPrefix;
            }
            value = MathMultiplyFixed16(
                0x370000, *(s32 *)((u32)cornerOffset + (u32)coord));
            coordY = (u8 *)gSinTableMap0[0];
            mapPrim->x0 = (value >> 0x10) + 0x12C;
            coordY = (u8 *)((u32)cornerOffset + (u32)coordY);
            value = MathMultiplyFixed16(0x370000, *(s32 *)coordY);
            asm("" : "=r"(yOffset) : "0"((s32)(u8)D_800A2FD0[view]));
            coordX = (u8 *)gCosTableAbsolute[0];
            value >>= 0x10;
            yOffset = (s8)yOffset + 0xD7;
            coordX = (u8 *)((u32)cornerOffset + (u32)coordX);
            value += yOffset;
            asm("" : "=r"(value) : "0"(value), "r"(coordX));
            mapPrim->y0 = value;
            coordinateValue = *(s32 *)coordX;
            value = MathMultiplyFixed16(0x370000, coordinateValue);
            coordY = (u8 *)gSinTableMap1[0];
            mapPrim->x1 = (value >> 0x10) + 0x130;
            coordY = (u8 *)((u32)cornerOffset + (u32)coordY);
            value = MathMultiplyFixed16(0x370000, *(s32 *)coordY);
            asm("" : "=r"(yOffset) : "0"((s32)(u8)D_800A2FD0[view]));
            coordX = (u8 *)gCosTableAbsolute[0];
            value >>= 0x10;
            yOffset = (s8)yOffset + 0xD7;
            coordX = (u8 *)((u32)cornerOffset + (u32)coordX);
            value += yOffset;
            asm("" : "=r"(value) : "0"(value), "r"(coordX));
            mapPrim->y1 = value;
            coordinateValue = *(s32 *)coordX;
            value = MathMultiplyFixed16(0x370000, coordinateValue);
            coordY = (u8 *)gSinTableMap2[0];
            mapPrim->x2 = (value >> 0x10) + 0x12C;
            coordY = (u8 *)((u32)cornerOffset + (u32)coordY);
            value = MathMultiplyFixed16(0x370000, *(s32 *)coordY);
            coordX = (u8 *)gCosTableAbsolute[0];
            mapPrim->y2 = (value >> 0x10) + D_800A2FD0[view] + 0xDB;
            coordX = (u8 *)((u32)cornerOffset + (u32)coordX);
            coordinateValue = *(s32 *)coordX;
            value = MathMultiplyFixed16(0x370000, coordinateValue);
            coordY = (u8 *)gSinTableMap3[0];
            mapPrim->x3 = (value >> 0x10) + 0x130;
            cornerOffset += (u32)coordY;
            value = MathMultiplyFixed16(0x370000, *(s32 *)cornerOffset);
            mapPrim->y3 = (value >> 0x10) + D_800A2FD0[view] + 0xDB;
        }
        col = 0;
        tileIndex = (s8)entry;
        tileBytes = tileIndex * 0x30;
        f4base = (u8 *)D_800A7924;
        /* Keep these locals multi-set so loop.c does not hoist their values. */
        for (; col < 3; col++) {
            p3 = (TILE *)((u8 *)((u32)(col * 0x10) + (u32)f4base));
            p3 = (TILE *)((u32)tileBytes - -(u32)p3);
            SetTile(p3);
            SetSemiTrans(p3, 1);
            p4 = (TILE *)((u8 *)((u32)tileBytes + (u32)(col * 0x10) +
                                 (u32)f4base));
            tileX = 0xD;
            p4->x0 = tileX;
            tileX = 0;
            p4->y0 = D_800A2FD0[tileIndex] + 0xD3;
            tileHeightBase = (u8 *)D_800A7932;
            *(u16 *)(tileBytes + col * 0x10 + tileHeightBase) = 6;
            tileHeightBase = 0;
        }
        {
            register s32 tileRow;
            u8 *green;
            register u8 *red;
            u8 *back;
            s32 offset;
            s32 color;

            tileRow = (s8)entry;
            red = (u8 *)D_800A7924;
            offset = tileRow * 0x30;
            green = (u8 *)((u32)offset + (u32)red);
            do {
                color = 0xFF;
                red += 0x10;
            } while (0);
            red = (u8 *)((u32)offset + (u32)red);
            {
                register u8 *addressBase;

                addressBase = (u8 *)D_800A7944;
                back = (u8 *)((u32)(offset) - -(u32)addressBase);
            }
            ((TILE *)green)->r0 = 0;
            ((TILE *)green)->g0 = color;
            ((TILE *)green)->b0 = 0;
            ((TILE *)red)->r0 = color;
            ((TILE *)red)->g0 = 0;
            ((TILE *)red)->b0 = 0;
            ((TILE *)back)->r0 = 0;
            ((TILE *)back)->g0 = 0;
            ((TILE *)back)->b0 = 0;
            ((TILE *)back)->x0 = 0xC;
            ((TILE *)back)->y0 = D_800A2FD0[tileRow] + 0xD2;
            ((TILE *)back)->w = 0x2A;
            ((TILE *)back)->h = 8;
        }
    }
    SetPolyFT4((POLY_FT4 *)D_800A789C);
    SetSemiTrans((u8 *)D_800A789C, 1);
    SetShadeTex((u8 *)D_800A789C, 0);
    D_800A78B2[0] = GetTPage(tex->tpage, 3, tex->tpx, tex->tpy);
    D_800A78A8[0] = tex->u + 0x60;
    D_800A78A9[0] = tex->v + 0xF;
    D_800A78B0[0] = tex->u + 0x6F;
    D_800A78B1[0] = tex->v + 0xF;
    D_800A78B8[0] = tex->u + 0x60;
    D_800A78B9[0] = tex->v;
    D_800A78C0[0] = tex->u + 0x6F;
    D_800A78C1[0] = tex->v;
    SetTile(D_800A7984);
    borderFlag = D_800A798B[0];
    driverBase = D_800B0B7C; /* la driverBase, D_800B0B7C */
    D_800A7990[0] = 0x140;
    D_800A798C[0] = 0;
    D_800A798E[0] = 0;
    D_800A7992[0] = 0xF0;
    D_800A798BWrite[0] = borderFlag | 2;
    page = (u16 *)D_80090F32;
    asm("" : "=r"(page) : "0"(page));
    SetPolyF4(D_800A7564);
    for (entry = 0; entry < 2; entry++) {
        for (col = 0; col < 0x18; col++) {
            driverCall =
                (POLY_FT4 *)((u8 *)((u32)(col * 0x28) + (u32)driverBase));
            driverCall = (POLY_FT4 *)((u32)(entry * 0x3C0) - -(u32)driverCall);
            SetPolyFT4(driverCall);
            SetShadeTex(driverCall, 0);
            markerPage = GetTPage(page[0], 0, page[-6], page[-5]);
            markerOffset = (u32)col * 0x28 + (u32)entry * 0x3C0;
            *(u16 *)(markerOffset + (u8 *)D_800B0B92) = markerPage;
            driverR = D_800991E8[col * 3]; /* lbu */
            driver = (u8 *)((u32)markerOffset + (u32)driverBase);
            ((POLY_FT4 *)driver)->r0 = driverR;
            ((POLY_FT4 *)driver)->g0 = D_800991E9[col * 3];
            ((POLY_FT4 *)driver)->b0 = D_800991EA[col * 3];
        }
    }
}
