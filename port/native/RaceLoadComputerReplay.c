/* The matching C drops the file ID; the asm passes its a0 straight to FileOpen. */
void RaceLoadComputerReplay(s32 fileId) {
    extern s32 D_800A2F54;
    extern s32 D_800AE154[];
    extern s32 D_800B1EA8[];
    extern s32 D_800B60A4[];
    void *handle;
    void *buffer;
    s32 size;
    s32 idx;
    s32 entry;

    handle = FileOpenCall367DC(fileId, 0);
    if (handle == NULL) {
        SystemShowFatalError(gErrorRaceDataFileOpen);
    }
    size = FileSeekCall367DC(handle);
    FileSeekCall367DC(handle);
    buffer = HeapAlloc(((size + 0x7FF) >> 11) << 11);
    D_800AE154[D_800A2F54] = (s32)buffer;
    if (buffer == NULL) {
        SystemShowFatalError(gErrorComputerReplayMemory);
    }
    FileReadCall367DC(D_800AE154[D_800A2F54], 1, size, handle);
    idx = D_800A2F54;
    entry = D_800AE154[idx];
    D_800B60A4[idx] = entry;
    D_800B1EA8[idx] = *(s32 *)entry;
    D_800AE154[idx] = entry + 4;
    D_800A2F54 = idx + 1;
    FileCloseCall367DC();
}
