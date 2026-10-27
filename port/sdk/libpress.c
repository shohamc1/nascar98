/*
 * Psy-Q libpress for the port: a software MDEC, after psx-spx's
 * description. DecDCTin takes a run-level stream whose first word holds
 * its length in words; DecDCTout decodes 16 x 16 macroblocks from it
 * (Cr, Cb, then four Y blocks) as 15-bit or 24-bit pixels, at once,
 * then runs the out callback, which may ask for the next strip. The IDCT
 * is floating point: enhanced, not bit-exact.
 */
#include "host.h"

/* A scratch buffer that input.c fills at run time (see src/psxsdk/libpress.c). */
u8 D_8008CA04[0x4C];

#define MODE_24BIT 1
#define MODE_STP 2

static const u8 kZagZig[64] = {
    0,  1,  8,  16, 9,  2,  3,  10, 17, 24, 32, 25, 18, 11, 4,  5,  12, 19, 26, 33, 40, 48,
    41, 34, 27, 20, 13, 6,  7,  14, 21, 28, 35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23,
    30, 37, 44, 51, 58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63,
};

/* libpress's default table: MPEG-1's intra matrix with a DC step of 2, in raster order. */
static const u8 kQuant[64] = {
    2,  16, 19, 22, 26, 27, 29, 34, 16, 16, 22, 24, 27, 29, 34, 37, 19, 22, 26, 27, 29, 34,
    34, 38, 22, 22, 26, 27, 29, 34, 37, 40, 22, 26, 27, 29, 32, 35, 40, 48, 26, 27, 29, 32,
    35, 40, 48, 58, 26, 27, 29, 34, 38, 46, 56, 69, 27, 29, 35, 38, 46, 56, 69, 83,
};

/* cos((2x + 1) u pi / 16), with C(0) = 1 / sqrt(2) folded in. */
static float sBasis[8][8];
static const u16 *sIn;
static const u16 *sInEnd;
static int sMode;
static void (*sInCallback)(void);
static void (*sOutCallback)(void);
static u32 *sOutBuf;
static int sOutSize;
static int sOutPending;
static int sInOut;

/* cos for the basis: a few Taylor terms, after reducing to [-pi, pi]. */
static float Cos(float x)
{
    const float pi = 3.14159265358979f;
    float x2, term, sum;
    int i;

    while (x > pi) {
        x -= 2 * pi;
    }
    while (x < -pi) {
        x += 2 * pi;
    }
    x2 = x * x;
    term = 1;
    sum = 1;
    for (i = 1; i < 12; i++) {
        term *= -x2 / ((2 * i - 1) * (2 * i));
        sum += term;
    }
    return sum;
}

void DecDCTReset(s32 mode)
{
    int x, u;

    PORT_TRACE(DecDCTReset);
    for (x = 0; x < 8; x++) {
        for (u = 0; u < 8; u++) {
            sBasis[x][u] = Cos((2 * x + 1) * u * 3.14159265358979f / 16) * (u == 0 ? 0.70710678f : 1.0f);
        }
    }
    sIn = sInEnd = 0;
    sOutPending = 0;
}

static int SignExtend10(int v)
{
    return ((v & 0x3FF) ^ 0x200) - 0x200;
}

static int Clamp(int v, int lo, int hi)
{
    return v < lo ? lo : v > hi ? hi : v;
}

/* Decodes one 8 x 8 block into OUT (signed samples); 0 at the stream's end. */
static int DecodeBlock(int *out)
{
    float coef[64], row[64];
    int k, n, q, val, x, y, u, v;

    for (k = 0; k < 64; k++) {
        coef[k] = 0;
    }
    do {
        if (sIn >= sInEnd) {
            return 0;
        }
        n = *sIn++;
    } while (n == 0xFE00);
    q = (n >> 10) & 0x3F;
    val = SignExtend10(n) * (q ? kQuant[0] : 2);
    k = 0;
    for (;;) {
        coef[q ? kZagZig[k] : k] = (float)Clamp(val, -0x400, 0x3FF);
        if (sIn >= sInEnd) {
            break;
        }
        n = *sIn++;
        k += ((n >> 10) & 0x3F) + 1;
        if (k > 63) {
            break;
        }
        val = (SignExtend10(n) * kQuant[kZagZig[k]] * q + 4) / 8;
    }
    /* Separable IDCT: rows, then columns. */
    for (v = 0; v < 8; v++) {
        for (x = 0; x < 8; x++) {
            float sum = 0;

            for (u = 0; u < 8; u++) {
                sum += coef[v * 8 + u] * sBasis[x][u];
            }
            row[v * 8 + x] = sum / 2;
        }
    }
    for (y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++) {
            float sum = 0;

            for (v = 0; v < 8; v++) {
                sum += row[v * 8 + x] * sBasis[y][v];
            }
            sum /= 2;
            out[y * 8 + x] = Clamp((int)(sum < 0 ? sum - 0.5f : sum + 0.5f), -128, 127);
        }
    }
    return 1;
}

/* Writes one macroblock at OUT; returns the words written. */
static int DecodeMacroblock(u32 *out)
{
    int cr[64], cb[64], y[4][64], i, px, py;
    u16 *out16 = (u16 *)out;
    u8 *out8 = (u8 *)out;

    if (!DecodeBlock(cr) || !DecodeBlock(cb)) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (!DecodeBlock(y[i])) {
            return 0;
        }
    }
    for (py = 0; py < 16; py++) {
        for (px = 0; px < 16; px++) {
            int c = (py / 2) * 8 + px / 2;
            int l = y[(py / 8) * 2 + px / 8][(py % 8) * 8 + px % 8];
            float r = 1.402f * cr[c], g = -0.3437f * cb[c] - 0.7143f * cr[c], b = 1.772f * cb[c];
            int R = Clamp(l + (int)r, -128, 127) + 128;
            int G = Clamp(l + (int)g, -128, 127) + 128;
            int B = Clamp(l + (int)b, -128, 127) + 128;

            if (sMode & MODE_24BIT) {
                u8 *p = out8 + (py * 16 + px) * 3;

                p[0] = (u8)R;
                p[1] = (u8)G;
                p[2] = (u8)B;
            } else {
                out16[py * 16 + px] = (u16)(R >> 3 | (G >> 3) << 5 | (B >> 3) << 10 | (sMode & MODE_STP ? 0x8000 : 0));
            }
        }
    }
    return sMode & MODE_24BIT ? 192 : 128;
}

void DecDCTin(u32 *buf, s32 mode)
{
    u32 words = buf[0] & 0xFFFF;

    PORT_TRACE(DecDCTin);
    if (sBasis[0][0] == 0) {
        DecDCTReset(0);
    }
    sMode = mode;
    sIn = (const u16 *)(buf + 1);
    sInEnd = sIn + (words ? words * 2 : 0x20000);
    if (sInCallback) {
        sInCallback();
    }
}

/* Decodes SIZE words; a call from the out callback queues the next strip. */
void DecDCTout(u32 *buf, s32 size)
{
    PORT_TRACE(DecDCTout);
    sOutBuf = buf;
    sOutSize = size;
    sOutPending = 1;
    if (sInOut) {
        return;
    }
    sInOut = 1;
    while (sOutPending) {
        u32 *out = sOutBuf;
        int left = sOutSize;

        sOutPending = 0;
        while (left > 0) {
            int n = DecodeMacroblock(out);

            if (n == 0) {
                while (left-- > 0) {
                    *out++ = 0;
                }
                break;
            }
            out += n;
            left -= n;
        }
        if (sOutCallback) {
            sOutCallback();
        }
    }
    sInOut = 0;
}

s32 DecDCTinSync(s32 mode)
{
    return 0;
}

s32 DecDCToutSync(s32 mode)
{
    return 0;
}

s32 DecDCTinCallback(void (*func)(void))
{
    void (*old)(void) = sInCallback;

    sInCallback = func;
    return (s32)old;
}

s32 DecDCToutCallback(void (*func)(void))
{
    void (*old)(void) = sOutCallback;

    sOutCallback = func;
    return (s32)old;
}
