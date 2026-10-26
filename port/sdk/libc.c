/* Psy-Q libc for the port: the string functions the game calls, and exit. */
#include "host.h"
#include <psxsdk/libc.h>

int abs(int x)
{
    return x < 0 ? -x : x;
}

void bzero(s32 dst, s32 size)
{
    u8 *p = (u8 *)dst;

    while (size-- > 0) {
        *p++ = 0;
    }
}

void exit(void)
{
    HostExit(0);
}

void *memcpy(void *dst, const void *src, size_t size)
{
    u8 *d = dst;
    const u8 *s = src;

    while (size--) {
        *d++ = *s++;
    }
    return dst;
}

char *strcat(char *dst, char *src)
{
    strcpy(dst + strlen(dst), src);
    return dst;
}

int strcmp(const char *a, const char *b)
{
    while (*a && *a == *b) {
        a++;
        b++;
    }
    return (u8)*a - (u8)*b;
}

char *strcpy(const char *dst, const char *src)
{
    char *d = (char *)dst;

    while ((*d++ = *src++) != 0) {
    }
    return (char *)dst;
}

int strlen(const char *s)
{
    int n = 0;

    while (s[n]) {
        n++;
    }
    return n;
}

static int Contains(const char *set, char c)
{
    while (*set) {
        if (*set++ == c) {
            return 1;
        }
    }
    return 0;
}

/* Psy-Q's strtok lives in libcard; the game calls it from memory_card.c. */
char *strtok(char *s, char *delims)
{
    static char *next;
    char *start;

    if (s == 0) {
        s = next;
    }
    if (s == 0) {
        return 0;
    }
    while (*s && Contains(delims, *s)) {
        s++;
    }
    if (*s == 0) {
        next = 0;
        return 0;
    }
    start = s;
    while (*s && !Contains(delims, *s)) {
        s++;
    }
    next = *s ? s + 1 : 0;
    *s = 0;
    return start;
}

/* Writes VALUE in BASE into OUT, reversed; returns the digit count. */
static int Digits(char *out, u32 value, u32 base, int upper)
{
    const char *set = upper ? "0123456789ABCDEF" : "0123456789abcdef";
    int n = 0;

    do {
        out[n++] = set[value % base];
        value /= base;
    } while (value);
    return n;
}

/* %d %i %u %x %X %s %c %%, with a width and the 0 flag: every format in src/. */
s32 sprintf(char *dst, char *fmt, ...)
{
    __builtin_va_list args;
    char *out = dst;
    char digits[12];
    const char *s;
    int width, zero, n, negative;
    s32 value;

    __builtin_va_start(args, fmt);
    for (; *fmt; fmt++) {
        if (*fmt != '%') {
            *out++ = *fmt;
            continue;
        }
        fmt++;
        zero = *fmt == '0';
        for (width = 0; *fmt >= '0' && *fmt <= '9'; fmt++) {
            width = width * 10 + *fmt - '0';
        }
        negative = 0;
        switch (*fmt) {
        case 'd':
        case 'i':
            value = __builtin_va_arg(args, s32);
            negative = value < 0;
            n = Digits(digits, negative ? -(u32)value : (u32)value, 10, 0);
            break;
        case 'u':
            n = Digits(digits, __builtin_va_arg(args, u32), 10, 0);
            break;
        case 'x':
        case 'X':
            n = Digits(digits, __builtin_va_arg(args, u32), 16, *fmt == 'X');
            break;
        case 's':
            s = __builtin_va_arg(args, const char *);
            for (n = strlen(s); n < width; width--) {
                *out++ = ' ';
            }
            while (*s) {
                *out++ = *s++;
            }
            continue;
        case 'c':
            *out++ = (char)__builtin_va_arg(args, s32);
            continue;
        default: /* %% */
            *out++ = *fmt;
            continue;
        }
        if (negative && zero) {
            *out++ = '-';
        }
        for (width -= n + negative; width > 0; width--) {
            *out++ = zero ? '0' : ' ';
        }
        if (negative && !zero) {
            *out++ = '-';
        }
        while (n) {
            *out++ = digits[--n];
        }
    }
    __builtin_va_end(args);
    *out = 0;
    return out - dst;
}
