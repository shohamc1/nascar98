void TextFormatTime(void *timeValue, s32 flags, s32 buffer) {
    register s32 time;
    s32 noSign;
    register s32 blank;
    register s32 hours;
    s32 totalSeconds;
    s32 mode;
    register s32 minutes;
    register s32 seconds;
    s32 rem1000;
    s32 msSign;
    s32 msShift;
    s32 millis;
    s8 *out;
    s32 sign;
    typedef struct {
        u8 bytes[10];
    } TimeText10;

    time = (s32)timeValue;
    out = (s8 *)buffer;
    noSign = 0;
    if (flags < 0) {
        noSign = 1;
        asm("");
    }
    if (time == 0x7FFFFFFF) {
        *(TimeText10 *)out = *(TimeText10 *)gTimeInvalidText;
        return;
    }
    blank = noSign;
    if (blank != 0) {
        sign = ' ';
    } else if (time < 0) {
        time = -time;
        sign = '-';
    } else {
        sign = '+';
    }
    /*
     * Retail's two asm blocks, register for register. time is in 1/160 s
     * ticks (pinned to $7 in the matching build). The magic multiplies
     * divide by 576000 (hours), 160 (seconds), and 9600 (minutes).
     */
    {
        s32 r2, r3, r4, r5, r6, r8, r10;
        s64 hi3;

        r8 = (s32)(((s64)time * 0x7482296B) >> 32);
        r5 = (s32)(((s64)time * 0x66666667) >> 32);
        r6 = time >> 31;
        r2 = r8 >> 18;
        r8 = (s32)(((s64)time * 0x1B4E81B5) >> 32);
        r10 = r2 - r6;
        r5 = (r5 >> 6) - r6;
        r2 = time - r5 * 160;
        r3 = r2 * 1000;
        hi3 = (s64)r3 * 0x66666667;
        r4 = (r8 >> 10) - r6;
        hours = r10;
        totalSeconds = r5;
        minutes = r4 - r10 * 60;
        seconds = r5 - r4 * 60;
        rem1000 = r3;
        mode = D_800A2EACAbsolute[0];
        msSign = rem1000 >> 31;
        msShift = (s32)(hi3 >> 32) >> 6;
    }
    millis = msShift - msSign;
    if (mode != 0) {
        if (hours != 0) {
            sprintfArgs(out, gTimeFormatSignedHms, sign, hours, minutes,
                        seconds);
        } else if (minutes != 0) {
            sprintfArgs(out, gTimeFormatSignedMinSecMs, sign, minutes, seconds,
                        millis);
        } else {
            sprintfArgs(out, gTimeFormatSignedSecMs, sign, seconds, millis);
        }
    } else if (hours != 0) {
        sprintfArgs(out, gTimeFormatHms, hours, minutes, seconds);
    } else {
        sprintfArgs(out, gTimeFormatMinSecMs, minutes, seconds, millis);
    }
}
