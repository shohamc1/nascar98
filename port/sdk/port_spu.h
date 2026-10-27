/*
 * The port's SPU (spu.c): 512 KB of sound RAM and 24 voices that play
 * ADPCM with loop flags, pitch, an ADSR envelope, and left and right
 * volume. libspu.c and libsnd.c drive it; VSync mixes it.
 */
#ifndef PORT_SDK_PORT_SPU_H
#define PORT_SDK_PORT_SPU_H

#include "types.h"

#define PORT_SPU_RAM 0x80000
#define PORT_SPU_VOICES 24
#define PORT_SPU_RATE 44100
#define PORT_SPU_FRAME (PORT_SPU_RATE / 60) /* stereo samples per VSync */

enum { PORT_SPU_OFF, PORT_SPU_ATTACK, PORT_SPU_DECAY, PORT_SPU_SUSTAIN, PORT_SPU_RELEASE };

typedef struct {
    /* Set by libspu and libsnd. Addresses are bytes in sound RAM. */
    u32 start, loop;
    u16 pitch; /* 0x1000 plays at 44,100 Hz */
    u16 adsr1, adsr2;
    s16 volL, volR; /* 0x3FFF is full volume */
    /* Playback state. */
    u32 addr;
    int pos;
    u32 counter;
    s16 block[28];
    s32 old1, old2, prev, cur;
    int phase;
    s32 level;
    u32 cycles;
} PortSpuVoice;

extern u8 gPortSpuRam[PORT_SPU_RAM];
extern PortSpuVoice gPortSpuVoices[PORT_SPU_VOICES];
extern s16 gPortSpuMainL, gPortSpuMainR; /* 0x3FFF is full volume */

/* Decodes one 16-byte ADPCM block into 28 samples, updating the history. */
void PortSpuDecodeBlock(const u8 *block, s16 *out, s32 *old1, s32 *old2);
void PortSpuWriteRam(u32 addr, const void *src, u32 size);
/* Keys the voices in MASK on (ON nonzero) or off. */
void PortSpuKey(int on, u32 mask);
/* 0: off; 1: keyed on; 2: keyed off, envelope still sounding. */
int PortSpuKeyStatus(int voice);
/* IRQ: CALLBACK runs when a voice reaches ADDR while ENABLED. */
void PortSpuSetIrq(int enabled, u32 addr, void (*callback)(void));
/* Adds FRAMES stereo samples to OUT (left, right, ...), saturating. */
void PortSpuMix(s16 *out, int frames);

#endif /* PORT_SDK_PORT_SPU_H */
