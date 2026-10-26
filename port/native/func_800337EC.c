/*
 * Retail (handwritten): 1 when any of SZ0 to SZ2 is under 300, else
 * whether SZ3 is.
 */
s32 func_800337EC(void) {
    if ((s32)PortGteRead(16) < 300 || (s32)PortGteRead(17) < 300 ||
        (s32)PortGteRead(18) < 300) {
        return 1;
    }
    return (s32)PortGteRead(19) < 300;
}
