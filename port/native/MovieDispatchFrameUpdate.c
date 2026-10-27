/* The asm leaves a0 to a2 alone, so both callees get the caller's frame. */
void MovieDispatchFrameUpdate(MovieFrame *frameData, s32 x, s16 y) {
    if (gMovieContext->unk12C)
        func_8006FBB0Args(frameData, x, y);
    else
        func_8006FDDC(frameData, x, y);
}
