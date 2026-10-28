/*
 * The port's software GTE (see port_gte.h), after psx-spx's "Geometry
 * Transformation Engine" chapter: 32 data and 32 control registers and
 * every command, with the FLAG register's saturation and overflow bits,
 * and the hardware's UNR division.
 */
#include "host.h"
#include "port_gte.h"

s32 sprintf(char *, char *, ...);

/* Data registers (cop2r0 to cop2r31). */
static s16 sV[3][3];       /* VXY0, VZ0, ..., VZ2 */
static u8 sRgbc[4];        /* RGBC */
static u16 sOtz;
static s16 sIr[4];         /* IR0 to IR3 */
static s16 sSxy[3][2];     /* SXY0 to SXY2 */
static u16 sSz[4];         /* SZ0 to SZ3 */
static u8 sRgbFifo[3][4];  /* RGB0 to RGB2 */
static u32 sRes1;
static s32 sMac[4];        /* MAC0 to MAC3 */
static s32 sLzcs;

/* Control registers (cop2r32 to cop2r63). */
static s16 sRt[3][3], sLlm[3][3], sLcm[3][3];
static s32 sTr[3], sBk[3], sFc[3];
static s32 sOfx, sOfy;
static u16 sH;
static s16 sDqa;
static s32 sDqb;
static s16 sZsf3, sZsf4;
static u32 sFlag;

static s64 Mac123(int i, s64 value)
{
    /* MAC1 to MAC3 keep 44 bits; overflow sets bits 30-28 and 27-25. */
    if (value > 0x7FFFFFFFFFFLL) {
        sFlag |= 1u << (31 - i);
    } else if (value < -0x80000000000LL) {
        sFlag |= 1u << (28 - i);
    }
    return value;
}

static s32 SetMac(int i, s64 value, int shift)
{
    Mac123(i, value);
    sMac[i] = (s32)(value >> shift);
    return sMac[i];
}

static s16 SetIr(int i, s32 value, int lm)
{
    s32 lo = lm ? 0 : -0x8000;

    if (value < lo) {
        value = lo;
        sFlag |= 1u << (25 - i);
    } else if (value > 0x7FFF) {
        value = 0x7FFF;
        sFlag |= 1u << (25 - i);
    }
    sIr[i] = (s16)value;
    return sIr[i];
}

static void SetMac0(s64 value)
{
    if (value > 0x7FFFFFFFLL) {
        sFlag |= 1u << 16;
    } else if (value < -0x80000000LL) {
        sFlag |= 1u << 15;
    }
    sMac[0] = (s32)value;
}

static u8 Color(int i, s32 value)
{
    if (value < 0) {
        sFlag |= 1u << (22 - i);
        return 0;
    }
    if (value > 0xFF) {
        sFlag |= 1u << (22 - i);
        return 0xFF;
    }
    return (u8)value;
}

static void PushColor(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        sRgbFifo[i][0] = sRgbFifo[i + 1][0];
        sRgbFifo[i][1] = sRgbFifo[i + 1][1];
        sRgbFifo[i][2] = sRgbFifo[i + 1][2];
        sRgbFifo[i][3] = sRgbFifo[i + 1][3];
    }
    sRgbFifo[2][0] = Color(1, sMac[1] >> 4);
    sRgbFifo[2][1] = Color(2, sMac[2] >> 4);
    sRgbFifo[2][2] = Color(3, sMac[3] >> 4);
    sRgbFifo[2][3] = sRgbc[3];
}

static void PushSz(s32 value)
{
    if (value < 0) {
        value = 0;
        sFlag |= 1u << 18;
    } else if (value > 0xFFFF) {
        value = 0xFFFF;
        sFlag |= 1u << 18;
    }
    sSz[0] = sSz[1];
    sSz[1] = sSz[2];
    sSz[2] = sSz[3];
    sSz[3] = (u16)value;
}

static s16 Screen(s32 value, int bit)
{
    if (value < -0x400) {
        sFlag |= 1u << bit;
        return -0x400;
    }
    if (value > 0x3FF) {
        sFlag |= 1u << bit;
        return 0x3FF;
    }
    return (s16)value;
}

/*
 * H / SZ3 in 16.16, limited to 0x1FFFF, as the hardware divides: a
 * reciprocal from the UNR table and two Newton-Raphson steps (psx-spx).
 * The result can be one off the exact quotient, and screen coordinates
 * follow it.
 */
static u32 Divide(void)
{
    static u8 sUnr[0x101];
    u32 n, d, u;
    int z;

    if (sSz[3] == 0 || sH >= sSz[3] * 2u) {
        sFlag |= 1u << 17;
        return 0x1FFFF;
    }
    if (sUnr[0] == 0) {
        for (z = 0; z < 0x101; z++) {
            s32 v = (0x40000 / (z + 0x100) + 1) / 2 - 0x101;
            sUnr[z] = v < 0 ? 0 : (u8)v;
        }
    }
    for (z = 0; !(sSz[3] << z & 0x8000); z++) {
    }
    n = (u32)sH << z;
    d = (u32)sSz[3] << z;
    u = sUnr[(d - 0x7FC0) >> 7] + 0x101;
    d = (0x2000080 - d * u) >> 8;
    d = (0x80 + d * u) >> 8;
    n = (u32)(((u64)n * d + 0x8000) >> 16);
    return n > 0x1FFFF ? 0x1FFFF : n;
}

/* RTPS on vertex V; LAST says to finish with the depth cue. */
static void Rtps(int v, int sf, int lm, int last)
{
    int i;
    s64 mac3;
    u32 div;

    for (i = 0; i < 3; i++) {
        s64 sum = ((s64)sTr[i] << 12) + (s64)sRt[i][0] * sV[v][0] + (s64)sRt[i][1] * sV[v][1] +
                  (s64)sRt[i][2] * sV[v][2];

        SetIr(i + 1, SetMac(i + 1, sum, sf ? 12 : 0), lm);
        if (i == 2) {
            mac3 = sum;
        }
    }
    PushSz((s32)(mac3 >> 12));
    div = Divide();
    sSxy[0][0] = sSxy[1][0];
    sSxy[0][1] = sSxy[1][1];
    sSxy[1][0] = sSxy[2][0];
    sSxy[1][1] = sSxy[2][1];
    SetMac0((s64)div * sIr[1] + sOfx);
    sSxy[2][0] = Screen(sMac[0] >> 16, 14);
    SetMac0((s64)div * sIr[2] + sOfy);
    sSxy[2][1] = Screen(sMac[0] >> 16, 13);
    if (last) {
        s32 ir0;

        SetMac0((s64)div * sDqa + sDqb);
        ir0 = sMac[0] >> 12;
        if (ir0 < 0) {
            ir0 = 0;
            sFlag |= 1u << 12;
        } else if (ir0 > 0x1000) {
            ir0 = 0x1000;
            sFlag |= 1u << 12;
        }
        sIr[0] = (s16)ir0;
    }
}

/* MAC = matrix M times vector V (three s16) plus TX << 12, shifted. */
static void MatrixVector(s16 m[3][3], const s32 v[3], const s32 *tx, int sf, int lm)
{
    int i;

    for (i = 0; i < 3; i++) {
        s64 sum = (tx ? (s64)tx[i] << 12 : 0) + (s64)m[i][0] * v[0] + (s64)m[i][1] * v[1] + (s64)m[i][2] * v[2];

        SetIr(i + 1, SetMac(i + 1, sum, sf ? 12 : 0), lm);
    }
}

static void IrVector(s32 v[3])
{
    v[0] = sIr[1];
    v[1] = sIr[2];
    v[2] = sIr[3];
}

/* Depth cue: MAC = MAC + (FC - MAC) * IR0, on the << 12 scale. */
static void DepthCue(s64 mac[3], int sf, int lm)
{
    int i;
    s32 ir[3];

    for (i = 0; i < 3; i++) {
        s64 diff = ((s64)sFc[i] << 12) - mac[i];

        Mac123(i + 1, diff);
        ir[i] = SetIr(i + 1, (s32)(diff >> (sf ? 12 : 0)), 0);
    }
    for (i = 0; i < 3; i++) {
        SetIr(i + 1, SetMac(i + 1, mac[i] + (s64)ir[i] * sIr[0], sf ? 12 : 0), lm);
    }
}

/* Light (LLM), then colour (BK + LCM), on vertex V or on IR when V < 0. */
static void Light(int v, int sf, int lm)
{
    s32 vec[3];

    if (v >= 0) {
        vec[0] = sV[v][0];
        vec[1] = sV[v][1];
        vec[2] = sV[v][2];
        MatrixVector(sLlm, vec, 0, sf, lm);
    }
    IrVector(vec);
    MatrixVector(sLcm, vec, sBk, sf, lm);
}

/* KIND 0: NCS (colour as is); 1: NCC (times RGBC); 2: NCD (and depth cue). */
static void NormalColor(int v, int kind, int sf, int lm)
{
    int i;

    Light(v, sf, lm);
    if (kind > 0) {
        s64 mac[3];

        for (i = 0; i < 3; i++) {
            mac[i] = ((s64)sRgbc[i] * sIr[i + 1]) << 4;
        }
        if (kind == 2) {
            DepthCue(mac, sf, lm);
        } else {
            for (i = 0; i < 3; i++) {
                SetIr(i + 1, SetMac(i + 1, mac[i], sf ? 12 : 0), lm);
            }
        }
    }
    PushColor();
}

u32 PortGteRead(int reg)
{
    reg &= 31;
    switch (reg) {
    case 0: case 2: case 4:
        return (u16)sV[reg / 2][0] | (u32)(u16)sV[reg / 2][1] << 16;
    case 1: case 3: case 5:
        return (u32)(s32)sV[reg / 2][2];
    case 6:
        return sRgbc[0] | sRgbc[1] << 8 | sRgbc[2] << 16 | (u32)sRgbc[3] << 24;
    case 7:
        return sOtz;
    case 8: case 9: case 10: case 11:
        return (u32)(s32)sIr[reg - 8];
    case 12: case 13: case 14:
        return (u16)sSxy[reg - 12][0] | (u32)(u16)sSxy[reg - 12][1] << 16;
    case 15:
        return (u16)sSxy[2][0] | (u32)(u16)sSxy[2][1] << 16;
    case 16: case 17: case 18: case 19:
        return sSz[reg - 16];
    case 20: case 21: case 22:
        return sRgbFifo[reg - 20][0] | sRgbFifo[reg - 20][1] << 8 | sRgbFifo[reg - 20][2] << 16 |
               (u32)sRgbFifo[reg - 20][3] << 24;
    case 23:
        return sRes1;
    case 24: case 25: case 26: case 27:
        return (u32)sMac[reg - 24];
    case 28: case 29: {
        int i;
        u32 c = 0;

        for (i = 0; i < 3; i++) {
            s32 x = sIr[i + 1] >> 7;

            c |= (u32)(x < 0 ? 0 : x > 0x1F ? 0x1F : x) << (5 * i);
        }
        return c;
    }
    case 30:
        return (u32)sLzcs;
    default: {
        /* LZCR: leading zeros, or leading ones when LZCS is negative. */
        u32 v = sLzcs < 0 ? ~(u32)sLzcs : (u32)sLzcs;
        int n = 0;

        while (n < 32 && !(v & 0x80000000u)) {
            v <<= 1;
            n++;
        }
        return (u32)n;
    }
    }
}

void PortGteWrite(int reg, u32 value)
{
    reg &= 31;
    switch (reg) {
    case 0: case 2: case 4:
        sV[reg / 2][0] = (s16)value;
        sV[reg / 2][1] = (s16)(value >> 16);
        break;
    case 1: case 3: case 5:
        sV[reg / 2][2] = (s16)value;
        break;
    case 6:
        sRgbc[0] = (u8)value;
        sRgbc[1] = (u8)(value >> 8);
        sRgbc[2] = (u8)(value >> 16);
        sRgbc[3] = (u8)(value >> 24);
        break;
    case 7:
        sOtz = (u16)value;
        break;
    case 8: case 9: case 10: case 11:
        sIr[reg - 8] = (s16)value;
        break;
    case 12: case 13: case 14:
        sSxy[reg - 12][0] = (s16)value;
        sSxy[reg - 12][1] = (s16)(value >> 16);
        break;
    case 15: /* SXYP pushes the FIFO */
        sSxy[0][0] = sSxy[1][0];
        sSxy[0][1] = sSxy[1][1];
        sSxy[1][0] = sSxy[2][0];
        sSxy[1][1] = sSxy[2][1];
        sSxy[2][0] = (s16)value;
        sSxy[2][1] = (s16)(value >> 16);
        break;
    case 16: case 17: case 18: case 19:
        sSz[reg - 16] = (u16)value;
        break;
    case 20: case 21: case 22:
        sRgbFifo[reg - 20][0] = (u8)value;
        sRgbFifo[reg - 20][1] = (u8)(value >> 8);
        sRgbFifo[reg - 20][2] = (u8)(value >> 16);
        sRgbFifo[reg - 20][3] = (u8)(value >> 24);
        break;
    case 23:
        sRes1 = value;
        break;
    case 24: case 25: case 26: case 27:
        sMac[reg - 24] = (s32)value;
        break;
    case 28: /* IRGB sets IR1 to IR3 from 5-bit colours */
        sIr[1] = (s16)((value & 0x1F) << 7);
        sIr[2] = (s16)(((value >> 5) & 0x1F) << 7);
        sIr[3] = (s16)(((value >> 10) & 0x1F) << 7);
        break;
    case 30:
        sLzcs = (s32)value;
        break;
    }
}

static void SetMatrix(s16 m[3][3], int reg, u32 value)
{
    s16 *flat = &m[0][0];

    if (reg == 4) {
        flat[8] = (s16)value;
        return;
    }
    flat[reg * 2] = (s16)value;
    flat[reg * 2 + 1] = (s16)(value >> 16);
}

static u32 GetMatrix(s16 m[3][3], int reg)
{
    s16 *flat = &m[0][0];

    if (reg == 4) {
        return (u32)(s32)flat[8];
    }
    return (u16)flat[reg * 2] | (u32)(u16)flat[reg * 2 + 1] << 16;
}

u32 PortGteReadControl(int reg)
{
    reg &= 31;
    if (reg < 5) {
        return GetMatrix(sRt, reg);
    }
    if (reg < 8) {
        return (u32)sTr[reg - 5];
    }
    if (reg < 13) {
        return GetMatrix(sLlm, reg - 8);
    }
    if (reg < 16) {
        return (u32)sBk[reg - 13];
    }
    if (reg < 21) {
        return GetMatrix(sLcm, reg - 16);
    }
    if (reg < 24) {
        return (u32)sFc[reg - 21];
    }
    switch (reg) {
    case 24:
        return (u32)sOfx;
    case 25:
        return (u32)sOfy;
    case 26:
        return (u32)(s32)(s16)sH; /* the hardware sign-extends H on read */
    case 27:
        return (u32)(s32)sDqa;
    case 28:
        return (u32)sDqb;
    case 29:
        return (u32)(s32)sZsf3;
    case 30:
        return (u32)(s32)sZsf4;
    default:
        return sFlag;
    }
}

void PortGteWriteControl(int reg, u32 value)
{
    reg &= 31;
    if (reg < 5) {
        SetMatrix(sRt, reg, value);
    } else if (reg < 8) {
        sTr[reg - 5] = (s32)value;
    } else if (reg < 13) {
        SetMatrix(sLlm, reg - 8, value);
    } else if (reg < 16) {
        sBk[reg - 13] = (s32)value;
    } else if (reg < 21) {
        SetMatrix(sLcm, reg - 16, value);
    } else if (reg < 24) {
        sFc[reg - 21] = (s32)value;
    } else {
        switch (reg) {
        case 24: sOfx = (s32)value; break;
        case 25: sOfy = (s32)value; break;
        case 26: sH = (u16)value; break;
        case 27: sDqa = (s16)value; break;
        case 28: sDqb = (s32)value; break;
        case 29: sZsf3 = (s16)value; break;
        case 30: sZsf4 = (s16)value; break;
        default: sFlag = value & 0x7FFFF000u; break;
        }
    }
}

static void Average(s32 zsf, int count)
{
    s64 sum = 0;
    int i;

    for (i = 4 - count; i < 4; i++) {
        sum += sSz[i];
    }
    SetMac0((s64)zsf * sum);
    sum = sMac[0] >> 12;
    if (sum < 0 || sum > 0xFFFF) {
        sFlag |= 1u << 18;
        sum = sum < 0 ? 0 : 0xFFFF;
    }
    sOtz = (u16)sum;
}

/* COMMAND is the whole COP2 word; its low six bits pick the operation. */
void PortGteCommand(u32 command)
{
    int sf = (command >> 19) & 1, lm = (command >> 10) & 1;
    int i;
    s32 vec[3];
    s64 mac[3];

    sFlag = 0;
    switch (command & 0x3F) {
    case 0x01: /* RTPS */
        Rtps(0, sf, lm, 1);
        break;
    case 0x30: /* RTPT */
        Rtps(0, sf, lm, 0);
        Rtps(1, sf, lm, 0);
        Rtps(2, sf, lm, 1);
        break;
    case 0x06: /* NCLIP */
        SetMac0((s64)sSxy[0][0] * sSxy[1][1] + (s64)sSxy[1][0] * sSxy[2][1] + (s64)sSxy[2][0] * sSxy[0][1] -
                (s64)sSxy[0][0] * sSxy[2][1] - (s64)sSxy[1][0] * sSxy[0][1] - (s64)sSxy[2][0] * sSxy[1][1]);
        break;
    case 0x0C: { /* OP: IR cross the RT diagonal */
        s64 d1 = sRt[0][0], d2 = sRt[1][1], d3 = sRt[2][2];

        mac[0] = sIr[3] * d2 - sIr[2] * d3;
        mac[1] = sIr[1] * d3 - sIr[3] * d1;
        mac[2] = sIr[2] * d1 - sIr[1] * d2;
        for (i = 0; i < 3; i++) {
            SetIr(i + 1, SetMac(i + 1, mac[i], sf ? 12 : 0), lm);
        }
        break;
    }
    case 0x10: /* DPCS */
    case 0x2A: /* DPCT */
        for (i = 0; i < ((command & 0x3F) == 0x2A ? 3 : 1); i++) {
            const u8 *c = (command & 0x3F) == 0x2A ? sRgbFifo[0] : sRgbc;
            int k;

            for (k = 0; k < 3; k++) {
                mac[k] = (s64)c[k] << 16;
            }
            DepthCue(mac, sf, lm);
            PushColor();
        }
        break;
    case 0x11: /* INTPL */
        for (i = 0; i < 3; i++) {
            mac[i] = (s64)sIr[i + 1] << 12;
        }
        DepthCue(mac, sf, lm);
        PushColor();
        break;
    case 0x12: { /* MVMVA */
        int mx = (command >> 17) & 3, v = (command >> 15) & 3, cv = (command >> 13) & 3;
        s16 (*m)[3] = mx == 0 ? sRt : mx == 1 ? sLlm : sLcm;
        const s32 *t = cv == 0 ? sTr : cv == 1 ? sBk : cv == 2 ? sFc : 0;

        if (v == 3) {
            IrVector(vec);
        } else {
            vec[0] = sV[v][0];
            vec[1] = sV[v][1];
            vec[2] = sV[v][2];
        }
        MatrixVector(m, vec, t, sf, lm);
        break;
    }
    case 0x13: /* NCDS */
        NormalColor(0, 2, sf, lm);
        break;
    case 0x16: /* NCDT */
        NormalColor(0, 2, sf, lm);
        NormalColor(1, 2, sf, lm);
        NormalColor(2, 2, sf, lm);
        break;
    case 0x1B: /* NCCS */
        NormalColor(0, 1, sf, lm);
        break;
    case 0x3F: /* NCCT */
        NormalColor(0, 1, sf, lm);
        NormalColor(1, 1, sf, lm);
        NormalColor(2, 1, sf, lm);
        break;
    case 0x1E: /* NCS */
        NormalColor(0, 0, sf, lm);
        break;
    case 0x20: /* NCT */
        NormalColor(0, 0, sf, lm);
        NormalColor(1, 0, sf, lm);
        NormalColor(2, 0, sf, lm);
        break;
    case 0x1C: /* CC */
        NormalColor(-1, 1, sf, lm);
        break;
    case 0x14: /* CDP */
        NormalColor(-1, 2, sf, lm);
        break;
    case 0x29: /* DCPL */
        for (i = 0; i < 3; i++) {
            mac[i] = ((s64)sRgbc[i] * sIr[i + 1]) << 4;
        }
        DepthCue(mac, sf, lm);
        PushColor();
        break;
    case 0x28: /* SQR */
        for (i = 0; i < 3; i++) {
            SetIr(i + 1, SetMac(i + 1, (s64)sIr[i + 1] * sIr[i + 1], sf ? 12 : 0), lm);
        }
        break;
    case 0x2D: /* AVSZ3 */
        Average(sZsf3, 3);
        break;
    case 0x2E: /* AVSZ4 */
        Average(sZsf4, 4);
        break;
    case 0x3D: /* GPF */
        for (i = 0; i < 3; i++) {
            SetIr(i + 1, SetMac(i + 1, (s64)sIr[0] * sIr[i + 1], sf ? 12 : 0), lm);
        }
        PushColor();
        break;
    case 0x3E: /* GPL */
        for (i = 0; i < 3; i++) {
            s64 base = (s64)sMac[i + 1] << (sf ? 12 : 0);

            SetIr(i + 1, SetMac(i + 1, base + (s64)sIr[0] * sIr[i + 1], sf ? 12 : 0), lm);
        }
        PushColor();
        break;
    default: {
        static u8 sLogged[64];
        char line[48];

        if (!sLogged[command & 63]) {
            sLogged[command & 63] = 1;
            sprintf(line, "gte: unknown command %X", command);
            HostLog(line);
        }
        break;
    }
    }
    if (sFlag & 0x7F87E000u) {
        sFlag |= 0x80000000u;
    }
}
