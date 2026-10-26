void HudDrawCarPanel(Car *car, s32 bank, s32 hideTimes) {
    s8 text[24];
    register s32 byteValue;
    s32 lapValue;
    void *helperTime;
    register s32 helperMode;
    register s32 helperBuffer;
    register POLY_FT4 *copyFrom;
    POLY_FT4 *copyTo;
    u8 *copyEnd;
    register s32 numberArg;
    s32 shiftedLap;
    register s8 *start;
    register s8 *string;
    s32 len;
    s32 number;
    register s32 lap;
    s32 fixedSpeed;
    s32 yOffset;
    s32 i;
    s32 offset;
    s32 x;
    s32 y;
    s32 baseY;
    s32 width;
    register s32 right;
    register s32 barX;
    register s32 bankOffset;
    register u8 *quadBase;
    s32 bottom;
    s8 *p;
    register u8 *quad;
    POLY_F4 *barQuad;
    s32 barY;
    POLY_FT4 *prim;
    u32 cursor;
    register s16 *glyphWidth;
    s32 scale;

    if (car->cameraMode == 0 || D_800A2EACAbsolute[0] != 0) {
        return;
    }
    switch (car->unk209) {
    case 1:
    case 3:
        hideTimes = 1;
        break;
    }
    gFontColorRed = 60;
    gFontColorGreen = 100;
    gFontColorBlue = 60;
    byteValue = (u8)car->place;
    len = 0;
    yOffset = -(bank != 0) & 100;
    y = 135 - yOffset;
    /* Keep the byte conversion before the width tests. */
    /* sll byteValue, 24; sra number, byteValue, 24 */
    byteValue = (u32)byteValue << 24;
    number = (s32)byteValue >> 24;
    text[0] = 0;
    if (number < 1000) {
        len = 1;
        text[0] = ' ';
        text[1] = 0;
    }
    if (number < 100) {
        text[len++] = ' ';
        text[len] = 0;
    }
    if (number < 10) {
        text[len++] = ' ';
        text[len] = 0;
    }
    numberArg = number;
    p = text;
    TextFormatInt(numberArg, (u8 *)p + len);
    x = 8;
    if (text[0] != 0) {
        do {
            FontDrawGlyph(*p, x, y, 2);
            p++;
            x += D_800A2D8C;
        } while (*p != 0);
    }
    lap = car->lap;
    if (lap < 0)
        lap = 0;
    if (D_800A2EA8w15[0] < lap)
        lap = D_800A2EA8w15[0];
    len = 0;
    y = 135 - yOffset;
    /* Keep the full lap load before its signed halfword conversion. */
    shiftedLap = (u32)lap << 16; /* sll */
    lapValue = shiftedLap >> 16;
    text[0] = 0;
    if (lapValue < 1000) {
        len = 1;
        text[0] = ' ';
        text[1] = 0;
    }
    if (lapValue < 100) {
        text[len++] = ' ';
        text[len] = 0;
    }
    if (lapValue < 10) {
        text[len++] = ' ';
        text[len] = 0;
    }
    numberArg = lapValue;
    p = text;
    TextFormatInt(numberArg, (u8 *)p + len);
    x = 23;
    if (text[0] != 0) {
        do {
            FontDrawGlyph(*p, x, y, 2);
            p++;
            x += D_800A2D8C;
        } while (*p != 0);
    }
    baseY = 135 - yOffset;
    FontDrawGlyph('-', 47, baseY, 2);
    numberArg = D_800A2EA8w15[0];
    text[0] = 0;

    TextFormatInt((s16)numberArg, (u8 *)text);
    x = 53;
    y = baseY;
    start = text;
    if (text[0] != 0) {
        p = start;
        do {
            FontDrawGlyph(*p, x, y, 2);
            p++;
            x += D_800A2D8C;
        } while (*p != 0);
    }
    fixedSpeed = car->speed;
    y = 181 - yOffset;
    byteValue = car->unkF7;
    if (fixedSpeed < 0)
        fixedSpeed = 0;
    /* Retail keeps this mask after the byte load. */
    byteValue &= 255;
    if (byteValue == 1)
        number = ((fixedSpeed >> 16) * 336) / 550;
    else
        number = ((fixedSpeed >> 16) * 210) / 550;
    len = 0;
    text[0] = 0;
    if (number < 100) {
        len = 1;
        text[0] = ' ';
        text[1] = 0;
    }
    if (number < 10) {
        text[len++] = ' ';
        text[len] = 0;
    }
    numberArg = number;
    p = text;
    TextFormatInt(numberArg, (u8 *)p + len);
    x = 34;
    if (text[0] != 0) {
        do {
            FontDrawGlyph(*p, x, y, 2);
            p++;
            x += D_800A2D8C;
        } while (*p != 0);
    }
    FontDrawGlyph((s8)((u8)car->gearIndex + '1'), 60, 190 - yOffset, 2);
    if (hideTimes == 0) {
        helperTime = (void *)car->unk258;
        helperMode = 2;
        helperBuffer = (s32)text;
        asm("" : : "r"(helperTime), "r"(helperMode), "r"(helperBuffer));
        y = 135 - yOffset;
        TextFormatTime(helperTime, helperMode, helperBuffer);
        x = 252;
        scale = 2;
        start = text;
        if (text[0] != 0) {
            glyphWidth = (s16 *)&D_800A2D8CAbsolute[0];
            p = start;
            do {
                FontDrawGlyph(*p, x, y, scale);
                p++;
                x += *glyphWidth;
            } while (*p != 0);
        }
        helperTime = (void *)car->time;
        helperMode = 2;
        if ((s32)helperTime != 0x7FFFFFFF) {
            helperBuffer = (s32)text;
            asm("" : : "r"(helperTime), "r"(helperMode), "r"(helperBuffer));
            y = 159 - yOffset;
            TextFormatTime(helperTime, helperMode, helperBuffer);
            x = 252;
            scale = 2;
            start = text;
            if (text[0] != 0) {
                glyphWidth = (s16 *)&D_800A2D8CAbsolute[0];
                p = start;
                do {
                    FontDrawGlyph(*p, x, y, scale);
                    p++;
                    x += *glyphWidth;
                } while (*p != 0);
            }
        } else {
            x = 258;
            y = 159 - yOffset;
            string = gTimeBlankText;
            if (*string != 0) {
                p = string;
                do {
                    FontDrawGlyph(*p, x, y, 2);
                    p++;
                    x += D_800A2D8C;
                } while (*p != 0);
            }
        }
        func_800183C0(car->unk260, 258, 183 - yOffset, 2);
    }
    i = 17;

    offset = 680;
    do {
        bankOffset = bank * 720;
        quadBase = offset + (u8 *)D_800AE29C;
        quad = (u8 *)(bankOffset + (s32)quadBase);
        barQuad = (POLY_F4 *)quad;
        switch (i) {
        case 2:
            func_80019A00(car->rpm, quad, bank);
            goto queue;
        case 8:
            if (car->wheel[0].unkC > 0xCE400)
                goto next;
            goto queue;
        case 13:
            width = (car->unk28C * 34) / 16000;
            barY = 204;
            barX = 31;
            if (bank != 0)
                barY = 104;
            if (width >= 34)
                width = 33;
            right = width + 31;
            width = 31;
            asm("" : "=r"(width) : "0"(width));
            barQuad->x2 = width;
            barQuad->x0 = barX;
            bottom = barY + 2;
            barQuad->y0 = barY;
            barQuad->x1 = right;
            barQuad->y1 = barY;
            barQuad->y2 = bottom;
            barQuad->x3 = right;
            barQuad->y3 = bottom;
            goto queue;
        case 4:
        case 5:
        case 6:
        case 10:
        case 11:
        case 12:
            if (hideTimes != 0)
                goto next;
            goto queue;
        case 15:
            if (car->unk28C > 0)
                goto next;
            goto queue;
        case 16:
            if (car->segment == -1)
                break;
            if (MathGetAngleDelta(car->heading,
                                  gTrackSections[0][car->segment].angle) < 0) {
                if (-MathGetAngleDelta(car->heading,
                                       gTrackSections[0][car->segment].angle) <
                    300)
                    goto next;
            } else {
                if (MathGetAngleDelta(car->heading,
                                      gTrackSections[0][car->segment].angle) <
                    300)
                    goto next;
            }
            goto queue;
        case 17:
            if (D_800A2EE0w15[0] == 0 || D_800A2EC8[0] != 0)
                break;
            if (car->unk3B7 != 0 || (car->unk3A4 & 15) == 0) {
                if (*(void (**)(u8 *))((u8 *)car + 0x354) != func_80025730 ||
                    car->unk1BC != 4)
                    break;
            }
            string = D_8009ADD8[0];
            x = 85;
            y = 142 - yOffset;
            if (*string != 0) {
                p = string;
                do {
                    FontDrawGlyph(*p, x, y, 1);
                    p++;
                    x += D_800A2D8A;
                } while (*p != 0);
            }
            goto queue;
        default:
        queue:
            cursor = gPrimitiveCursor[0];
            copyFrom = (POLY_FT4 *)quad;
            copyEnd = (u8 *)copyFrom + 32;
            asm("" : "=r"(prim) : "0"(cursor));
            copyTo = prim;
            gPrimitiveCursorLui = (u32)prim + 40;
            asm("" : "=r"(copyTo) : "r"(copyFrom), "0"(copyTo));
            *copyTo = *copyFrom;

            AddPrim((u8 *)gOrderingTable[0], prim);
            break;
        }
    next:
        i--;
        offset -= 40;
    } while (i >= 0);
    gFontColorRed = 128;
    gFontColorGreen = 128;
    gFontColorBlue = 128;
}
