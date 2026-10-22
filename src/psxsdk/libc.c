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

ASM_FUNC(exit, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
               "    jr $t2 # maspsx-keep\n"
               "    addiu $t1, $zero, 0x38 # maspsx-keep\n"
               "    nop # maspsx-keep\n")

ASM_FUNC(puts, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
               "    jr $t2 # maspsx-keep\n"
               "    addiu $t1, $zero, 0x3F # maspsx-keep\n"
               "    nop # maspsx-keep\n")

ASM_FUNC(setjmp, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x13 # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(strcat, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x15 # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(strcmp, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x17 # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(strcpy, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x19 # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(strlen, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x1B # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(bzero, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                "    jr $t2 # maspsx-keep\n"
                "    addiu $t1, $zero, 0x28 # maspsx-keep\n"
                "    nop # maspsx-keep\n")

ASM_FUNC(memcpy, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x2A # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

ASM_FUNC(memset_8008B820, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                          "    jr $t2 # maspsx-keep\n"
                          "    addiu $t1, $zero, 0x2B # maspsx-keep\n"
                          "    nop # maspsx-keep\n")

ASM_FUNC(printf, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x3F # maspsx-keep\n"
                 "    nop # maspsx-keep\n")

typedef struct SprintfFormat {
    unsigned left : 1;
    unsigned plus : 1;
    unsigned alternate : 1;
    unsigned zero : 1;
    unsigned precisionSet : 1;
    unsigned shortArg : 1;
    unsigned longArg : 1;
    unsigned longDouble : 1;
    u8 sign;
    s32 width;
    s32 precision;
} SprintfFormat;
extern SprintfFormat gSprintfDefaultFormat[];
extern void *memchr(const void *, s32, s32);
extern void *memmove(u8 *, u8 *, s32);
static const char sSprintfUpperDigits[] = "0123456789ABCDEF";
static const char sSprintfLowerDigits[] = "0123456789abcdef";

s32 sprintf(char *out, char *f, ...) {
    char buf[0x200];
    SprintfFormat info;
    va_list args;
    char *hexChars;
    s32 written;
    s32 num;
    s32 len;
    char *bufPtr;
    u32 ch;

    va_start(args, f);
    ch = *f;
    written = 0;
    for (; ch = *f, ch != 0; ++f) {
        if (ch != '%') {
            out[written++] = ch;
            continue;
        }
        info = gSprintfDefaultFormat[0];

        while (1) {
            ch = *++f;
            if (ch == '-') {
                info.left = 1;
            } else if (ch == '+') {
                info.plus = 1;
            } else if (ch == ' ') {
                info.sign = ' ';
            } else if (ch == '#') {
                info.alternate = 1;
            } else if (ch == '0') {
                info.zero = 1;
            } else {
                break;
            }
        }

        if (ch == '*') {
            info.width = va_arg(args, s32);
            if (info.width < 0) {
                info.width = -info.width;
                info.left = 1;
            }
            ch = *++f;
        } else {
            while (ch >= '0' && ch <= '9') {
                info.width = (info.width * 10) + (ch - '0');
                ch = *++f;
            }
        }
        if (ch == '.') {
            ch = *++f;
            if (ch == '*') {
                info.precision = va_arg(args, s32);
                ch = *++f;
            } else {
                while (ch >= '0' && ch <= '9') {
                    info.precision = (info.precision * 10) + (ch - '0');
                    ch = *++f;
                }
            }
            if (info.precision >= 0) {
                info.precisionSet = 1;
            }
        }

        bufPtr = (char *)&args - sizeof(SprintfFormat) - 4;

        if (info.left) {
            info.zero = 0;
        }

    loop_30:
        switch (ch) {
        case 'h':
            info.shortArg = 1;
            ch = *++f;
            goto loop_30;

        case 'l':
            info.longArg = 1;
            ch = *++f;
            goto loop_30;

        case 'L':
            info.longDouble = 1;
            ch = *++f;
            goto loop_30;

        case 'd':
        case 'i':
            num = va_arg(args, s32);
            do {
                if (info.shortArg) {
                    num = (s16)num;
                }
            } while (0);
            if (num < 0) {
                num = -num;
                info.sign = '-';
            } else {
                do {
                    if (info.plus) {
                        info.sign = '+';
                    }
                } while (0);
            }
            goto printDec;

        case 'u':
            num = va_arg(args, u32);
            do {
                if (info.shortArg) {
                    num = (u16)num;
                }
            } while (0);
            info.sign = '\0';
        printDec:
            if (!info.precisionSet) {
                if (info.zero) {
                    info.precision = info.width;
                    if (info.sign != '\0') {
                        info.precision = info.width - 1;
                    }
                }
                if (info.precision <= 0) {
                    info.precision = 1;
                }
            }
            len = 0;
            while (num != 0) {
                *--bufPtr = (num % 10U) + '0';
                num /= 10U;
                len++;
            }
            while (len < info.precision) {
                *--bufPtr = '0';
                len++;
            }
            if (info.sign != '\0') {
                *--bufPtr = info.sign;
                len++;
            }
            break;

        case 'o':
            num = va_arg(args, u32);
            do {
                if (info.shortArg) {
                    num = (u16)num;
                }
            } while (0);
            if (!info.precisionSet) {
                if (info.zero) {
                    info.precision = info.width;
                }
                if (info.precision <= 0) {
                    info.precision = 1;
                }
            }
            len = 0;
            while (num != 0) {
                *--bufPtr = (num % 8U) + '0';
                num /= 8U;
                len++;
            }
            if (info.alternate && (len != 0) && (*bufPtr != '0')) {
                *--bufPtr = '0';
                len++;
            }
            while (len < info.precision) {
                *--bufPtr = '0';
                len++;
            }
            break;

        case 'p':
            info.precision = 8;
            info.precisionSet = 1;
            info.longArg = 1;
        case 'X':
            hexChars = (char *)sSprintfUpperDigits;
            goto printHex;
        case 'x':
            hexChars = (char *)sSprintfLowerDigits;
        printHex:
            num = va_arg(args, u32);
            do {
                if (info.shortArg) {
                    num = (u16)num;
                }
            } while (0);
            if (!info.precisionSet) {
                if (info.zero) {
                    info.precision = info.width;
                    if (info.alternate) {
                        info.precision = info.width - 2;
                    }
                }
                if (info.precision <= 0) {
                    info.precision = 1;
                }
            }
            len = 0;
            while (num != 0) {
                *--bufPtr = hexChars[num % 16U];
                num /= 16U;
                len++;
            }
            while (len < info.precision) {
                *--bufPtr = '0';
                len++;
            }
            if (info.alternate) {
                *--bufPtr = ch;
                *--bufPtr = '0';
                len += 2;
            }
            break;

        case 'c':
            *--bufPtr = va_arg(args, char);
            len = 1;
            break;

        case 's':
            bufPtr = va_arg(args, char *);
            if (info.alternate) {
                len = *bufPtr++;
                if (info.precisionSet) {
                    if (info.precision < len) {
                        len = info.precision;
                    }
                }
            } else if (!info.precisionSet) {
                len = strlen(bufPtr);
            } else {
                char *ptr = memchr(bufPtr, 0, info.precision);
                len = ptr - bufPtr;
                if (ptr == 0) {
                    len = info.precision;
                }
            }
            break;

        case 'n':
            bufPtr = va_arg(args, char *);
            if (info.shortArg) {
                *(u16 *)bufPtr = written;
            } else if (info.longArg) {
                LOW(*bufPtr) = written;
            } else if (info.longDouble) {
                LOW(*bufPtr) = written;
            } else {
                LOW(*bufPtr) = written;
            }
            continue;

        default:
            if (ch == '%') {
                out[written++] = ch;
                continue;
            } else {
                goto end;
            }
        }
        if (len < info.width && !info.left) {
            while (len < info.width) {
                out[written++] = ' ';
                info.width--;
            }
        }
        memmove(&out[written], bufPtr, len);
        written += len;
        while (len < info.width) {
            out[written++] = ' ';
            len++;
        }
    }
end:
    out[written] = 0;
    return written;
}

ASM_FUNC(memchr, "    addiu $t2, $zero, 0xA0 # maspsx-keep\n"
                 "    jr $t2 # maspsx-keep\n"
                 "    addiu $t1, $zero, 0x2E # maspsx-keep\n"
                 "    nop # maspsx-keep\n")
