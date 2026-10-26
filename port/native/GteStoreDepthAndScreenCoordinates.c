/* Retail (handwritten): mfc2 a2, $11; swc2 $14, 20(a0); srl; sh a2, 6(a0). */
void GteStoreDepthAndScreenCoordinates(SVECTOR *vertex) {
    u32 depth;

    depth = PortGteRead(11);
    *(u32 *)((u8 *)vertex + 20) = PortGteRead(14);
    vertex->pad = depth >> 2;
}
