s32 AudioInit(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
              s32 arg6) {
    SpuVoiceAttr va;
    SpuCommonAttr ca;
    SpuCommonAttr *caarg;
    u32 off;
    s32 voice;
    s32 addr;
    u8 val;
    u32 rawVoice;
    s32 base;

    if (arg0 == 0) {
        goto bail;
    }
    if (arg2 == 0) {
        goto bail;
    }
    if (arg4 == 0) {
        goto bail;
    }
    if (arg1 == 0) {
        goto bail;
    }
    if (arg3 == 0) {
        goto bail;
    }
    D_800A351C = (volatile s32 *)arg0;
    bzero(arg0, 0x7B80);
    off = 0;
    val = 2;
    do {
        ((u8 *)D_800A351C + off)[0x7811] = val;
        off = off + 0x10;
    } while (off < 0x300);
    D_800A351C[0x7B3C / 4] = 1;
    D_800A351C[0x7B58 / 4] = 0;
    D_800A351C[0x7B5C / 4] = arg2;
    D_800A351C[0x7B60 / 4] = arg4;
    D_800A351C[0x7B64 / 4] = arg1;
    D_800A351C[0x7B68 / 4] = arg3;
    D_800A351C[0x7B7C / 4] = arg5;
    voice = D_800A351C[0x7B64 / 4];
    addr = D_800A351C[0x7B5C / 4];
    ca.mask = 3;
    ca.mvol.left = 0x3FFF;
    ca.mvol.right = 0x3FFF;
    SpuSetCommonAttr(&ca);
    va.mask = 0xFF93;
    va.voice = voice;
    va.volume.left = -(voice == D_800A351C[0x7B64 / 4]) & 0x3FFF;
    va.volume.right = -(voice == D_800A351C[0x7B68 / 4]) & 0x3FFF;
    va.pitch = arg5;
    va.addr = addr;
    va.a_mode = 1;
    va.s_mode = 1;
    va.r_mode = 3;
    va.ar = 0;
    va.dr = 0;
    va.sr = 0;
    va.rr = 0;
    va.sl = 0xF;
    SpuSetVoiceAttr(&va);
    rawVoice = D_800A351C[0x7B68 / 4];
    voice = rawVoice;
    addr = (base = D_800A351C[0x7B60 / 4]);
    {
        /* addiu caarg, $sp, 0x50: retail's stack slot for ca. */
        caarg = &ca;
        ca.mask = 3;
        ca.mvol.left = 0x3FFF;
        ca.mvol.right = 0x3FFF;
        SpuSetCommonAttr(caarg);
        va.mask = 0xFF93;
        va.voice = voice;
        va.volume.left = -(voice == D_800A351C[0x7B64 / 4]) & 0x3FFF;
        va.volume.right = -(voice == D_800A351C[0x7B68 / 4]) & 0x3FFF;
        va.pitch = arg5;
        va.addr = addr;
        va.a_mode = 1;
        va.s_mode = 1;
        va.r_mode = 3;
        va.ar = 0;
        va.dr = 0;
        va.sr = 0;
        va.rr = 0;
        va.sl = 0xF;
        SpuSetVoiceAttr(&va);
    }
    SwEnterCriticalSection();
    D_800A351C[0x7B14 / 4] = (s32)SpuSetIRQCallback(0);
    D_800A351C[0x7B18 / 4] = (s32)SpuSetTransferCallback(AudioTransferCallback);
    D_800A351C[0x7B1C / 4] = arg6;
    if (arg6 != 0) {
        D_800A351C[0x7B10 / 4] =
            (s32)((Callback (*)(Callback))VSyncCallback)(AudioVSyncCallback);
    } else {
        D_800A351C[0x7B10 / 4] = 0;
    }
    SwExitCriticalSection();
    return 1;
bail:
    return 0;
}
