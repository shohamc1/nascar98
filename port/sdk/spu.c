/*
 * The port's SPU (port_spu.h), after psx-spx's description: ADPCM blocks
 * with loop flags, pitch counters, and the ADSR envelope's rates and
 * steps. Samples interpolate linearly; there is no reverb or noise.
 */
#include "port_spu.h"

u8 gPortSpuRam[PORT_SPU_RAM];
PortSpuVoice gPortSpuVoices[PORT_SPU_VOICES];
s16 gPortSpuMainL = 0x3FFF, gPortSpuMainR = 0x3FFF;

static int sIrqEnabled;
static u32 sIrqAddr;
static void (*sIrqCallback)(void);
static int sIrqPending;

static const s32 kFilterPos[5] = {0, 60, 115, 98, 122};
static const s32 kFilterNeg[5] = {0, 0, -52, -55, -60};

static s32 Clamp16(s32 v)
{
    return v < -0x8000 ? -0x8000 : v > 0x7FFF ? 0x7FFF : v;
}

void PortSpuDecodeBlock(const u8 *block, s16 *out, s32 *old1, s32 *old2)
{
    int shift = block[0] & 0xF, filter = (block[0] >> 4) & 7, i;

    if (shift > 12) {
        shift = 9;
    }
    if (filter > 4) {
        filter = 4;
    }
    for (i = 0; i < 28; i++) {
        s32 nibble = (block[2 + i / 2] >> (i % 2 * 4)) & 0xF;
        s32 s = (s32)(s16)(nibble << 12) >> shift;

        s += (*old1 * kFilterPos[filter] + *old2 * kFilterNeg[filter] + 32) >> 6;
        s = Clamp16(s);
        out[i] = (s16)s;
        *old2 = *old1;
        *old1 = s;
    }
}

void PortSpuWriteRam(u32 addr, const void *src, u32 size)
{
    const u8 *s = src;
    u32 i;

    for (i = 0; i < size; i++) {
        gPortSpuRam[(addr + i) & (PORT_SPU_RAM - 1)] = s[i];
    }
}

void PortSpuSetIrq(int enabled, u32 addr, void (*callback)(void))
{
    sIrqEnabled = enabled;
    sIrqAddr = addr & (PORT_SPU_RAM - 1);
    sIrqCallback = callback;
}

/* Enters the block at V->addr: loop start, IRQ, decode. */
static void EnterBlock(PortSpuVoice *v)
{
    const u8 *b = &gPortSpuRam[v->addr & (PORT_SPU_RAM - 16)];

    if (b[1] & 4) {
        v->loop = v->addr;
    }
    if (sIrqEnabled && sIrqAddr - (v->addr & (PORT_SPU_RAM - 16)) < 16) {
        sIrqEnabled = 0;
        sIrqPending = 1;
    }
    PortSpuDecodeBlock(b, v->block, &v->old1, &v->old2);
    v->pos = 0;
}

void PortSpuKey(int on, u32 mask)
{
    int i;

    for (i = 0; i < PORT_SPU_VOICES; i++) {
        PortSpuVoice *v = &gPortSpuVoices[i];

        if (!(mask >> i & 1)) {
            continue;
        }
        if (on) {
            v->addr = v->start;
            v->counter = 0;
            v->old1 = v->old2 = v->prev = v->cur = 0;
            v->phase = PORT_SPU_ATTACK;
            v->level = 0;
            v->cycles = 0;
            EnterBlock(v);
            v->cur = v->block[0];
        } else if (v->phase != PORT_SPU_OFF) {
            v->phase = PORT_SPU_RELEASE;
            v->cycles = 0;
        }
    }
}

int PortSpuKeyStatus(int voice)
{
    int phase = gPortSpuVoices[voice].phase;

    return phase == PORT_SPU_OFF ? 0 : phase == PORT_SPU_RELEASE ? 2 : 1;
}

/* One envelope tick. RATE is 7 bits; DECREASE and EXPONENTIAL pick the shape. */
static void Envelope(PortSpuVoice *v, int rate, int decrease, int exponential)
{
    int shift = rate >> 2;
    u32 cycles = 1u << (shift > 11 ? shift - 11 : 0);
    s32 step = decrease ? -8 + (rate & 3) : 7 - (rate & 3);

    step = shift < 11 ? step << (11 - shift) : step;
    if (exponential && !decrease && v->level > 0x6000) {
        cycles *= 4;
    }
    if (exponential && decrease) {
        step = step * v->level / 0x8000;
    }
    if (++v->cycles < cycles) {
        return;
    }
    v->cycles = 0;
    v->level += step;
    if (v->level > 0x7FFF) {
        v->level = 0x7FFF;
    } else if (v->level < 0) {
        v->level = 0;
    }
}

static void StepEnvelope(PortSpuVoice *v)
{
    s32 sustain = ((v->adsr1 & 0xF) + 1) * 0x800;

    switch (v->phase) {
    case PORT_SPU_ATTACK:
        Envelope(v, v->adsr1 >> 8 & 0x7F, 0, v->adsr1 >> 15);
        if (v->level >= 0x7FFF) {
            v->phase = PORT_SPU_DECAY;
        }
        break;
    case PORT_SPU_DECAY:
        if (v->level <= sustain) {
            v->phase = PORT_SPU_SUSTAIN;
            break;
        }
        Envelope(v, (v->adsr1 >> 4 & 0xF) * 4, 1, 1);
        break;
    case PORT_SPU_SUSTAIN:
        Envelope(v, v->adsr2 >> 6 & 0x7F, v->adsr2 >> 14 & 1, v->adsr2 >> 15);
        break;
    case PORT_SPU_RELEASE:
        Envelope(v, (v->adsr2 & 0x1F) * 4, 1, v->adsr2 >> 5 & 1);
        if (v->level == 0) {
            v->phase = PORT_SPU_OFF;
        }
        break;
    }
}

/* Moves V on by one source sample, following the block's loop flags. */
static void Advance(PortSpuVoice *v)
{
    v->prev = v->cur;
    if (++v->pos == 28) {
        u8 flags = gPortSpuRam[(v->addr & (PORT_SPU_RAM - 16)) + 1];

        if (flags & 1) {
            v->addr = v->loop;
            if (!(flags & 2)) {
                v->phase = PORT_SPU_OFF;
                v->level = 0;
            }
        } else {
            v->addr += 16;
        }
        EnterBlock(v);
    }
    v->cur = v->block[v->pos];
}

void PortSpuMix(s16 *out, int frames)
{
    int f, i;

    for (f = 0; f < frames; f++) {
        s32 left = 0, right = 0;

        for (i = 0; i < PORT_SPU_VOICES; i++) {
            PortSpuVoice *v = &gPortSpuVoices[i];
            s32 s;

            if (v->phase == PORT_SPU_OFF) {
                continue;
            }
            s = v->prev + (v->cur - v->prev) * (s32)(v->counter & 0xFFF) / 0x1000;
            s = s * v->level >> 15;
            left += s * v->volL >> 14;
            right += s * v->volR >> 14;
            StepEnvelope(v);
            v->counter += v->pitch > 0x3FFF ? 0x3FFF : v->pitch;
            while (v->counter >= 0x1000 && v->phase != PORT_SPU_OFF) {
                v->counter -= 0x1000;
                Advance(v);
            }
        }
        left = out[f * 2] + (left * gPortSpuMainL >> 14);
        right = out[f * 2 + 1] + (right * gPortSpuMainR >> 14);
        out[f * 2] = (s16)Clamp16(left);
        out[f * 2 + 1] = (s16)Clamp16(right);
        if (sIrqPending) {
            sIrqPending = 0;
            if (sIrqCallback) {
                sIrqCallback();
            }
        }
    }
}
