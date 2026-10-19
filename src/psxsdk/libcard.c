/* SPDX-License-Identifier: AGPL-3.0-only AND MIT AND GPL-2.0-or-later */
/* SDK C from sotn-decomp d818995ec49ef76e3b1625a96f4360108b3168be. */
#include "common.h"
#include "psxsdk_internal.h"
#include "libpress.h"
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/stdarg.h>

#include <psxsdk/libspu.h>
#include <psxsdk/libgpu.h>
#include <psxsdk/libcd.h>

void *memmove(u8 *dest, u8 *src, int count) {
    if (dest >= src) {
        while (count-- > 0) {
            dest[count] = src[count];
        }
    } else {
        while (count-- > 0) {
            *dest++ = *src++;
        }
    }

    return dest;
}

extern char *_strtokLast;

char *strtok(char *s, char *delim) {
    u8 c;
    char *spanp;
    s32 found;
    char *tok;

    if (s == 0 && (s = _strtokLast) == 0) {
        return 0;
    }
    while ((c = *s++) != 0) {
        found = 0;
        for (spanp = delim; *spanp != 0; spanp++) {
            if (*spanp == c) {
                found = 1;
                break;
            }
        }
        if (!found) {
            break;
        }
    }
    if (c == 0) {
        _strtokLast = 0;
        return 0;
    }
    tok = s - 1;
    c = *s++;
    while (c != 0) {
        spanp = delim;
        if (*spanp != 0) {
            do {
                if (*spanp++ == c) {
                    s[-1] = 0;
                    _strtokLast = s;
                    return tok;
                }
            } while (*spanp != 0);
        }
        c = *s++;
    }
    _strtokLast = 0;
    return tok;
}

ASM_FUNC(_card_info, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                     "    jr $t2 # maspsx-keep\n"
                     "    addiu $t1, $zero, 0xAB # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

ASM_FUNC(_card_load, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                     "    jr $t2 # maspsx-keep\n"
                     "    addiu $t1, $zero, 0xAC # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

ASM_FUNC(_card_auto, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                     "    jr $t2 # maspsx-keep\n"
                     "    addiu $t1, $zero, 0xAD # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

ASM_FUNC(InitCARD, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                   "    jr $t2 # maspsx-keep\n"
                   "    addiu $t1, $zero, 0x4A # maspsx-keep\n"
                   "    nop # maspsx-keep\n")

ASM_FUNC(StartCARD, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                    "    jr $t2 # maspsx-keep\n"
                    "    addiu $t1, $zero, 0x4B # maspsx-keep\n"
                    "    nop # maspsx-keep\n")

ASM_FUNC(StopCARD, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                   "    jr $t2 # maspsx-keep\n"
                   "    addiu $t1, $zero, 0x4C # maspsx-keep\n"
                   "    nop # maspsx-keep\n")

ASM_FUNC(_card_write, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                      "    jr $t2 # maspsx-keep\n"
                      "    addiu $t1, $zero, 0x4E # maspsx-keep\n"
                      "    nop # maspsx-keep\n")

ASM_FUNC(_card_read, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                     "    jr $t2 # maspsx-keep\n"
                     "    addiu $t1, $zero, 0x4F # maspsx-keep\n"
                     "    nop # maspsx-keep\n")

ASM_FUNC(_new_card, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                    "    jr $t2 # maspsx-keep\n"
                    "    addiu $t1, $zero, 0x50 # maspsx-keep\n"
                    "    nop # maspsx-keep\n")

extern long _new_card(void);
extern long _card_write(long chan, long size, void *data);
long _card_clear(long chan) {
    _new_card();
    return _card_write(chan, 0x3F, 0);
}
