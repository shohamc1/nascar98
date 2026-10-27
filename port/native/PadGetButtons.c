/* Not asm: a polling hook. The game waits for buttons in loops with no
 * VSync, reading buffers that the console's VBlank interrupt refreshes;
 * PortPoll lets those interrupts happen (port/sdk/libetc.c). */
void PortPoll(void);

s32 PadGetButtons(s32 index) {
    PortPoll();
    return D_8008CA04U16[index * 4];
}
