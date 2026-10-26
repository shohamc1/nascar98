void func_80044BCC(s32 arg0) {
    s32 v;
    s32 typeIndex;
    POLY_FT3 *prim;
    s32 otz;
    u32 *ot;

    ot = (u32 *)(gOrderingTable[0] + 0x20);
    prim = (POLY_FT3 *)((u8 *)gPrimitiveCursor[0]);
    typeIndex = (s8)gCarListNM[0][arg0].driver;
    gte_ldv3(D_800992E4, D_800992EC, D_800992F4);
    gte_rtpt();
    SetPolyFT3(prim);
    SetShadeTex(prim, 1);
    prim->clut = GetClut((typeIndex % 16) * 16 + 0x300, 0x3F - typeIndex / 16);
    if (typeIndex < 12) {
        prim->tpage = GetTPage(0, 0, (typeIndex % 4) * 64 + 0x300, 0);
        v = typeIndex / 4;
        v = v * 64 + 0x40;
    } else {
        prim->tpage = GetTPage(0, 0, (typeIndex % 4) * 64 + 0x300, 0x100);
        v = ((typeIndex - 12) / 4) * 64;
    }
    prim->u1 = 0x20;
    prim->u0 = 0;
    prim->v0 = v;
    prim->v1 = v;
    prim->u2 = 0;
    prim->v2 = v + 0x20;
    gte_avsz3();
    /* mfc2 otz, $7: the average Z from avsz3. */
    otz = PortGteRead(7);
    gte_stsxy3((u8 *)prim + 8, (u8 *)prim + 0x10, (u8 *)prim + 0x18);
    GraphicsAddTaggedPrimitive(&ot[otz >> 4], (u32 *)prim, 0x07000000);
    prim++;
    gPrimitiveCursor[0] = (u32)prim;
}
