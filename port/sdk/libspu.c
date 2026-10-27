/*
 * Psy-Q libspu for the port, over the SPU in spu.c. Transfers copy at
 * once, and the transfer callback runs before SpuWrite returns: the game
 * busy-waits on the flag that callback clears. A write made inside the
 * callback completes after the callback returns, as the DMA interrupt
 * would. Polling a key's status lets 32 samples pass, since the game
 * waits for a sound to end in a loop with no VSync. There is no reverb.
 */
#include "host.h"
#include "port_spu.h"
#include <psxsdk/libspu.h>

#define MALLOC_START 0x1010 /* after the capture buffers */
#define MALLOC_BLOCKS 32
#define POLL_FRAMES 32
#define AUDIO_FRAMES (8 * PORT_SPU_FRAME)

typedef void (*SpuTransferCallbackProc)(void);

static u32 sTransferAddr;
static SpuTransferCallbackProc sTransferCallback;
static int sTransfersDone, sInTransferCallback;
static int sIrqOn;
static u32 sIrqAddr;
static SpuIRQCallbackProc sIrqCallback;
static s16 sAudio[2 * AUDIO_FRAMES];
static int sAudioFrames; /* mixed since the last VSync */

/* SpuMalloc's blocks, sorted by address. */
static struct {
    u32 addr, size;
} sBlocks[MALLOC_BLOCKS];
static int sBlockCount;

/* Mixes FRAMES more samples into sAudio, handing a full buffer to the host. */
static void Run(int frames)
{
    int i;

    if (sAudioFrames + frames > AUDIO_FRAMES) {
        HostAudioQueue(sAudio, sAudioFrames);
        sAudioFrames = 0;
    }
    for (i = sAudioFrames * 2; i < (sAudioFrames + frames) * 2; i++) {
        sAudio[i] = 0;
    }
    PortSpuMix(sAudio + sAudioFrames * 2, frames);
    sAudioFrames += frames;
}

static void UpdateIrq(void)
{
    PortSpuSetIrq(sIrqOn, sIrqAddr, sIrqCallback);
}

s32 SpuInitMalloc(s32 num, char *top)
{
    PORT_TRACE(SpuInitMalloc);
    sBlockCount = 0;
    return num;
}

/* First fit: the start of sound RAM's first gap of SIZE bytes, or -1. */
s32 SpuMalloc(s32 size)
{
    u32 at = MALLOC_START, need = ((u32)size + 15) & ~15u;
    int i, k;

    PORT_TRACE(SpuMalloc);
    if (sBlockCount == MALLOC_BLOCKS) {
        return -1;
    }
    for (i = 0; i <= sBlockCount; i++) {
        u32 end = i < sBlockCount ? sBlocks[i].addr : PORT_SPU_RAM;

        if (end - at >= need && end >= at) {
            for (k = sBlockCount; k > i; k--) {
                sBlocks[k] = sBlocks[k - 1];
            }
            sBlocks[i].addr = at;
            sBlocks[i].size = need;
            sBlockCount++;
            return (s32)at;
        }
        at = sBlocks[i].addr + sBlocks[i].size;
    }
    return -1;
}

void SpuFree(s32 addr)
{
    int i;

    PORT_TRACE(SpuFree);
    for (i = 0; i < sBlockCount; i++) {
        if (sBlocks[i].addr == (u32)addr) {
            for (; i + 1 < sBlockCount; i++) {
                sBlocks[i] = sBlocks[i + 1];
            }
            sBlockCount--;
            return;
        }
    }
}

static s16 Volume(unsigned short v)
{
    return (s16)(v & 0x7FFF);
}

void SpuSetCommonAttr(SpuCommonAttr *attr)
{
    PORT_TRACE(SpuSetCommonAttr);
    if (attr->mask & SPU_COMMON_MVOLL) {
        gPortSpuMainL = Volume(attr->mvol.left);
    }
    if (attr->mask & SPU_COMMON_MVOLR) {
        gPortSpuMainR = Volume(attr->mvol.right);
    }
}

/* Psy-Q's mode numbers: 1 and 5 increase, 3 and 7 decrease; 5 to 7 are exponential. */
void SpuSetVoiceAttr(SpuVoiceAttr *arg)
{
    u32 m = arg->mask;
    int i;

    PORT_TRACE(SpuSetVoiceAttr);
    for (i = 0; i < PORT_SPU_VOICES; i++) {
        PortSpuVoice *v = &gPortSpuVoices[i];

        if (!(arg->voice >> i & 1)) {
            continue;
        }
        if (m & SPU_VOICE_VOLL) {
            v->volL = Volume(arg->volume.left);
        }
        if (m & SPU_VOICE_VOLR) {
            v->volR = Volume(arg->volume.right);
        }
        if (m & SPU_VOICE_PITCH) {
            v->pitch = arg->pitch;
        }
        if (m & SPU_VOICE_WDSA) {
            v->start = arg->addr;
        }
        if (m & SPU_VOICE_LSAX) {
            v->loop = arg->loop_addr;
        }
        if (m & SPU_VOICE_ADSR_ADSR1) {
            v->adsr1 = arg->adsr1;
        }
        if (m & SPU_VOICE_ADSR_ADSR2) {
            v->adsr2 = arg->adsr2;
        }
        if (m & SPU_VOICE_ADSR_AMODE) {
            v->adsr1 = (u16)((v->adsr1 & 0x7FFF) | (arg->a_mode == 5) << 15);
        }
        if (m & SPU_VOICE_ADSR_AR) {
            v->adsr1 = (u16)((v->adsr1 & 0x80FF) | (arg->ar & 0x7F) << 8);
        }
        if (m & SPU_VOICE_ADSR_DR) {
            v->adsr1 = (u16)((v->adsr1 & 0xFF0F) | (arg->dr & 0xF) << 4);
        }
        if (m & SPU_VOICE_ADSR_SL) {
            v->adsr1 = (u16)((v->adsr1 & 0xFFF0) | (arg->sl & 0xF));
        }
        if (m & SPU_VOICE_ADSR_SMODE) {
            v->adsr2 = (u16)((v->adsr2 & 0x3FFF) | (arg->s_mode >= 5) << 15 | (arg->s_mode == 3 || arg->s_mode == 7) << 14);
        }
        if (m & SPU_VOICE_ADSR_SR) {
            v->adsr2 = (u16)((v->adsr2 & 0xE03F) | (arg->sr & 0x7F) << 6);
        }
        if (m & SPU_VOICE_ADSR_RMODE) {
            v->adsr2 = (u16)((v->adsr2 & 0xFFDF) | (arg->r_mode == 7) << 5);
        }
        if (m & SPU_VOICE_ADSR_RR) {
            v->adsr2 = (u16)((v->adsr2 & 0xFFE0) | (arg->rr & 0x1F));
        }
    }
}

void SpuSetKey(long on_off, unsigned long voice_bit)
{
    PORT_TRACE(SpuSetKey);
    PortSpuKey(on_off != 0, (u32)voice_bit);
}

s32 SpuGetKeyStatus(s32 voiceBit)
{
    int i;

    PORT_TRACE(SpuGetKeyStatus);
    Run(POLL_FRAMES);
    for (i = 0; i < PORT_SPU_VOICES; i++) {
        if ((u32)voiceBit >> i & 1) {
            return PortSpuKeyStatus(i);
        }
    }
    return 0;
}

void SpuGetAllKeysStatus(char *status)
{
    int i;

    PORT_TRACE(SpuGetAllKeysStatus);
    Run(POLL_FRAMES);
    for (i = 0; i < PORT_SPU_VOICES; i++) {
        status[i] = (char)PortSpuKeyStatus(i);
    }
}

s32 SpuSetReverbVoice(s32 onOff, s32 voiceBit)
{
    PORT_TRACE(SpuSetReverbVoice);
    return 0;
}

long SpuSetTransferMode(long mode)
{
    PORT_TRACE(SpuSetTransferMode);
    return mode;
}

void SpuSetTransferStartAddr(s32 addr)
{
    PORT_TRACE(SpuSetTransferStartAddr);
    sTransferAddr = (u32)addr;
}

SpuTransferCallbackProc SpuSetTransferCallback(SpuTransferCallbackProc func)
{
    SpuTransferCallbackProc old = sTransferCallback;

    PORT_TRACE(SpuSetTransferCallback);
    sTransferCallback = func;
    return old;
}

unsigned long SpuWrite(unsigned char *addr, unsigned long size)
{
    PORT_TRACE(SpuWrite);
    PortSpuWriteRam(sTransferAddr, addr, (u32)size);
    sTransfersDone++;
    if (!sInTransferCallback) {
        sInTransferCallback = 1;
        while (sTransfersDone) {
            sTransfersDone--;
            if (sTransferCallback) {
                sTransferCallback();
            }
        }
        sInTransferCallback = 0;
    }
    return size;
}

void SpuSetIRQ(s32 onOff)
{
    PORT_TRACE(SpuSetIRQ);
    sIrqOn = onOff != 0;
    UpdateIrq();
}

void SpuSetIRQAddr(s32 addr)
{
    PORT_TRACE(SpuSetIRQAddr);
    sIrqAddr = (u32)addr;
    UpdateIrq();
}

SpuIRQCallbackProc SpuSetIRQCallback(SpuIRQCallbackProc func)
{
    SpuIRQCallbackProc old = sIrqCallback;

    PORT_TRACE(SpuSetIRQCallback);
    sIrqCallback = func;
    UpdateIrq();
    return old;
}

/* One VSync of sound: the rest of the frame's samples, to the host. */
void PortAudioTick(void)
{
    if (sAudioFrames < PORT_SPU_FRAME) {
        Run(PORT_SPU_FRAME - sAudioFrames);
    }
    HostAudioQueue(sAudio, sAudioFrames);
    sAudioFrames = 0;
}
