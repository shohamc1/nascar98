void MenuDrawPausePanel(void *unused, s32 selection, s32 flags) {
    s32 frameExtent[2];
    s32 y;
    s32 arrowX;
    s8 i;
    s32 index;
    s32 offset;
    s32 x;
    s32 rowY;
    s32 rowY2;
    s32 rowY3;
    s32 cursorY;
    s32 rowBias;
    s32 arrowArg;
    s32 volumeLimit;
    u8 **labels;
    u8 **choices;
    u8 **volumeChoices;
    register u8 **volumeLabels;

    y = 40;
    arrowX = 80;
    if (flags & 8) {
        MenuDrawStatistics();
        return;
    }
    if (flags & 4) {
        MenuDrawTimingAndScoring();
        return;
    }
    if (gSplitScreenModew15[0] != 0) {
        y = 20;
        if (D_800A3620w18c[0] != 0) {
            gOrderingTableLui += 0x1004;
        } else {
            y = 30;
        }
    }
    GraphicsSetColor(128, 128, 128);
    switch (D_800A39F0[0]) {
    case 0:
        i = 0;
        labels = (u8 **)D_8009AD60;
        do {
            /* Keep the signed byte index in one register. */
            index = (u32)i << 24;
            index >>= 24;
            offset = index * 4;
            x = (s16)(((u32)(158 - HudTextWidth(*(
                                       u8 **)(offset + (gSessionTypepanel * 24 +
                                                        (s32)labels)))) >>
                       1) +
                      81);
            offset += gSessionTypepanel * 24 + (s32)labels;
            HudDrawText(*(u8 **)offset, x, index * 12 + y, 0);
            i++;
        } while ((s8)i < 2);
        i = 4;
        labels = (u8 **)D_8009AD60;
        do {
            /* Keep the signed byte index in one register. */
            index = (s32)((u32)i << 24) >> 24; /* sll; sra */
            offset = index * 4;
            x = (s16)(((u32)(158 - HudTextWidth(*(
                                       u8 **)(offset + (gSessionTypepanel * 24 +
                                                        (s32)labels)))) >>
                       1) +
                      81);
            offset += gSessionTypepanel * 24 + (s32)labels;
            HudDrawText(*(u8 **)offset, x, index * 12 + y, 0);
            i++;
        } while ((s8)i < 6);
        if (gSessionTypepanel == 2) {
            GraphicsSetColor(32, 32, 32);
        }
        x = (s16)(((u32)(158 -
                         HudTextWidth(D_8009AD68[gSessionTypepanel][0])) >>
                   1) +
                  81);
        HudDrawText(D_8009AD68[gSessionTypepanel][0], x, y + 24, 0);
        GraphicsSetColor(128, 128, 128);
        if (gSplitScreenModew15[0] != 0) {
            GraphicsSetColor(32, 32, 32);
        }
        x = (s16)(((u32)(158 -
                         HudTextWidth(D_8009AD6C[gSessionTypepanel][0])) >>
                   1) +
                  81);
        HudDrawText(D_8009AD6C[gSessionTypepanel][0], x, y + 36, 0);
        break;
    case 1:
        choices = D_8009ADA8;
        rowY = y;
        asm("" : "=r"(rowY) : "0"(rowY));
        HudDrawText(choices[0], 90, rowY, 0);
        choices += 5;
        cursorY = 13;
        x = (s16)(230 - HudTextWidth(choices[D_800A2F9Dpanel]));
        HudDrawText(choices[D_800A2F9Dpanel], x, rowY, 0);
        GraphicsDrawRect(110, y + cursorY, gMusicVolumeAbsolute[0], 8, 0, 0,
                         D_800A2F9Dpanel ? -128 : 0, 1);
        GraphicsDrawRect(109, y + 12, 102, 10, -1, -1, -1, 1);
        rowY2 = y + 24;
        HudDrawText(D_8009ADAC[D_800A306Dpanel], 90, rowY2, 0);
        x = (s16)(230 - HudTextWidth(D_8009ADBC[D_800A2F9Cpanel]));
        HudDrawText(D_8009ADBC[D_800A2F9Cpanel], x, rowY2, 0);
        GraphicsDrawRect(110, y + 37, gCdVolumeAbsolute[0], 8, 0, 0,
                         D_800A2F9Cpanel ? -128 : 0, 1);
        GraphicsDrawRect(109, y + 36, 102, 10, -1, -1, -1, 1);
        rowY3 = y + 48;
        volumeLabels = D_8009ADB4;
        asm("" : "=r"(volumeLabels) : "0"(volumeLabels));
        HudDrawText(volumeLabels[0], 90, rowY3, 0);
        volumeLimit = 8;
        volumeChoices = volumeLabels - 3;
        x = (s16)(230 -
                  HudTextWidth(volumeChoices[volumeLimit - D_800A306Cpanel]));
        HudDrawText(volumeChoices[volumeLimit - D_800A306Cpanel], x, rowY3, 0);
        x = (s16)(((u32)(158 - HudTextWidth(volumeLabels[1])) >> 1) + 81);
        HudDrawText(volumeLabels[1], x, y + 60, 0);
        break;
    case 2:
        x = (s16)(((u32)(158 - HudTextWidth(D_8009ADCC[0])) >> 1) + 81);
        HudDrawText(D_8009ADCC[0], x, y + 12, 0);
        x = (s16)(((u32)(158 - HudTextWidth(D_8009ADD0)) >> 1) + 81);
        HudDrawText(D_8009ADD0, x, y + 36, 0);
        x = (s16)(((u32)(158 - HudTextWidth(D_8009ADD4)) >> 1) + 81);
        HudDrawText(D_8009ADD4, x, y + 48, 0);
        break;
    }
    GraphicsDrawDoubleBorderRect(81, y - 1, 158, 73, 0, 0, 0, 1);
    arrowArg = arrowX - 1;
    asm("" : : "r"(arrowArg));
    cursorY = selection * 12;
    rowBias = y + 5;
    cursorY += rowBias;
    MenuDrawArrow(arrowArg, cursorY, 0, 5);
    MenuDrawArrow(arrowX | 160, cursorY, 1, 5);
    if (D_800A3620w18c[0] != 0) {
        gOrderingTableLui -= 0x1004;
    }
    /* Compiler control: preserve the retail frame extent. */
}
