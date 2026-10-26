/*
 * Retail (handwritten), after a RotTransPers3: each vertex gets its
 * screen XY (SXY0 to SXY2) at byte 20 and its depth (SZ1 to SZ3) >> 2.
 */
void func_8003379C(SVECTOR *arg0, SVECTOR *arg1, SVECTOR *arg2) {
    u32 depth;

    depth = PortGteRead(17);
    *(u32 *)((u8 *)arg0 + 20) = PortGteRead(12);
    arg0->pad = depth >> 2;
    depth = PortGteRead(18);
    *(u32 *)((u8 *)arg1 + 20) = PortGteRead(13);
    arg1->pad = depth >> 2;
    depth = PortGteRead(19);
    *(u32 *)((u8 *)arg2 + 20) = PortGteRead(14);
    arg2->pad = depth >> 2;
}
