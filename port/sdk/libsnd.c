/*
 * Psy-Q libsnd for the port. VABs and the SsUt voice calls drive the SPU
 * in spu.c; the SEQ calls and the rest are stubs that log their first
 * call and return 0.
 */
#include "host.h"
#include "port_spu.h"
#include <psxsdk/libsnd.h>

#define VABS 16

s32 SpuMalloc(s32 size);
void SpuFree(s32 addr);

/* A VAB's header in main RAM: programs at 0x20, tones at 0x820, then VAG sizes. */
typedef struct {
    const u8 *head;
    u32 base;           /* the body in sound RAM, or 0 */
    u32 vag[256];       /* each VAG's sound RAM address */
} Vab;

/* What a voice was keyed on with, for the pitch and volume calls. */
typedef struct {
    int center, shift, pbmin, pbmax;
    s32 gain; /* tone volume x VAB volume, of 127 x 127 */
} VoiceTone;

static Vab sVabs[VABS];
static VoiceTone sVoiceTones[PORT_SPU_VOICES];

/* 2^(k/12) in 16.16, k = 0..11. */
static const u32 kSemitone[12] = {65536, 69433, 73562, 77936, 82570, 87480,
                                  92682, 98193, 104032, 110218, 116772, 123715};

static u16 Read16(const u8 *p)
{
    return (u16)(p[0] | p[1] << 8);
}

/* The pitch that plays a tone centred on CENTER.SHIFT at NOTE.FINE (1/128 semitones). */
static u16 NotePitch(int note, int fine, int center, int shift)
{
    s32 d = (note - center) * 128 + fine - shift;
    s32 octave = d >= 0 ? d / 1536 : -((-d + 1535) / 1536);
    s32 rest = d - octave * 1536;
    u32 ratio = kSemitone[rest / 128];
    u32 pitch;

    ratio += (u32)((u64)ratio * (rest % 128) * 451 / 1000000); /* 2^(x/1536) ~ 1 + 0.000451x */
    pitch = octave >= 0 ? (0x1000u * ratio >> 16) << octave : (0x1000u * ratio >> 16) >> -octave;
    return (u16)(pitch > 0x3FFF ? 0x3FFF : pitch);
}

static s16 VoiceVolume(int voice, int vol)
{
    return (s16)(vol * sVoiceTones[voice].gain / (127 * 127) * 0x3FFF / 127);
}

/* The 32-byte tone attributes of PROG's TONE: blocks of 16 for each program with tones. */
static const u8 *Tone(const Vab *vab, int prog, int tone)
{
    int block = 0, i;

    if (prog < 0 || prog >= 128 || tone < 0 || tone >= vab->head[0x20 + prog * 16]) {
        return 0;
    }
    for (i = 0; i < prog; i++) {
        block += vab->head[0x20 + i * 16] != 0;
    }
    return vab->head + 0x820 + (block * 16 + tone) * 32;
}

s32 SsVabOpenHead(u8 *addr, s32 vabId)
{
    Vab *vab;
    const u8 *sizes;
    u32 total = 0, at;
    int i;

    PORT_TRACE(SsVabOpenHead);
    if (Read16(addr) != 0x4270 || Read16(addr + 2) != 0x5641) { /* "pBAV" */
        return -1;
    }
    if (vabId < 0) {
        for (vabId = 0; vabId < VABS && sVabs[vabId].head; vabId++) {
        }
    }
    if (vabId >= VABS) {
        return -1;
    }
    vab = &sVabs[vabId];
    vab->head = addr;
    sizes = addr + 0x820 + Read16(addr + 0x12) * 16 * 32;
    for (i = 1; i < 256; i++) {
        total += (u32)Read16(sizes + i * 2) << 3;
    }
    vab->base = (u32)SpuMalloc((s32)total);
    at = vab->base;
    for (i = 1; i < 256; i++) {
        vab->vag[i] = at;
        at += (u32)Read16(sizes + i * 2) << 3;
    }
    return vabId;
}

s32 SsVabTransBody(u8 *addr, s32 vabId)
{
    const Vab *vab;
    u32 total = 0;
    int i;

    PORT_TRACE(SsVabTransBody);
    if (vabId < 0 || vabId >= VABS || !sVabs[vabId].head) {
        return -1;
    }
    vab = &sVabs[vabId];
    for (i = 1; i < 256; i++) {
        total += (u32)Read16(vab->head + 0x820 + Read16(vab->head + 0x12) * 16 * 32 + i * 2) << 3;
    }
    PortSpuWriteRam(vab->base, addr, total);
    return vabId;
}

s32 SsVabTransCompleted(short immediateFlag)
{
    PORT_TRACE(SsVabTransCompleted);
    return 1;
}

void SsVabClose(s32 vabId)
{
    PORT_TRACE(SsVabClose);
    if (vabId >= 0 && vabId < VABS && sVabs[vabId].head) {
        SpuFree((s32)sVabs[vabId].base);
        sVabs[vabId].head = 0;
    }
}

/* Plays PROG's TONE on VOICE at NOTE.FINE: the voice, or -1. */
short SsUtKeyOnV(short voice, short vabId, short prog, short tone, short note, short fine, short voll, short volr)
{
    const u8 *t;
    PortSpuVoice *v;
    VoiceTone *vt;
    int vag;

    PORT_TRACE(SsUtKeyOnV);
    if (voice < 0 || voice >= PORT_SPU_VOICES || vabId < 0 || vabId >= VABS || !sVabs[vabId].head) {
        return -1;
    }
    t = Tone(&sVabs[vabId], prog, tone);
    if (!t) {
        return -1;
    }
    vag = (s16)Read16(t + 0x16);
    if (vag < 1 || vag > 255) {
        return -1;
    }
    vt = &sVoiceTones[voice];
    vt->center = t[4];
    vt->shift = t[5];
    vt->pbmin = t[0xC];
    vt->pbmax = t[0xD];
    vt->gain = t[2] * sVabs[vabId].head[0x18]; /* the program's volume byte reads 0 on this disc */
    v = &gPortSpuVoices[voice];
    v->start = sVabs[vabId].vag[vag];
    v->pitch = NotePitch(note, fine, vt->center, vt->shift);
    v->adsr1 = Read16(t + 0x10);
    v->adsr2 = Read16(t + 0x12);
    v->volL = VoiceVolume(voice, voll);
    v->volR = VoiceVolume(voice, volr);
    PortSpuKey(1, 1u << voice);
    return voice;
}

s32 SsUtKeyOffV(s32 voice)
{
    PORT_TRACE(SsUtKeyOffV);
    if (voice < 0 || voice >= PORT_SPU_VOICES) {
        return -1;
    }
    PortSpuKey(0, 1u << voice);
    return 0;
}

s32 SsUtChangePitch(s32 voice, s32 vabId, s32 prog, s32 oldNote, s32 oldFine, s32 newNote, s32 newFine)
{
    PORT_TRACE(SsUtChangePitch);
    if (voice < 0 || voice >= PORT_SPU_VOICES) {
        return -1;
    }
    gPortSpuVoices[voice].pitch = NotePitch(newNote, newFine, sVoiceTones[voice].center, sVoiceTones[voice].shift);
    return 0;
}

/* PBEND 0..127, 64 centred: up to the tone's pbmax semitones up, pbmin down. */
s32 SsUtPitchBend(s32 voice, s32 vabId, s32 prog, s32 note, s32 pbend)
{
    const VoiceTone *vt;
    s32 fine;

    PORT_TRACE(SsUtPitchBend);
    if (voice < 0 || voice >= PORT_SPU_VOICES) {
        return -1;
    }
    vt = &sVoiceTones[voice];
    fine = (pbend - 64) * (pbend >= 64 ? vt->pbmax : vt->pbmin) * 128 / 64;
    gPortSpuVoices[voice].pitch = NotePitch(note, fine, vt->center, vt->shift);
    return 0;
}

short SsUtSetVVol(short vc, short voll, short volr)
{
    PORT_TRACE(SsUtSetVVol);
    if (vc < 0 || vc >= PORT_SPU_VOICES) {
        return -1;
    }
    gPortSpuVoices[vc].volL = VoiceVolume(vc, voll);
    gPortSpuVoices[vc].volR = VoiceVolume(vc, volr);
    return 0;
}

void SsSetMVol(short voll, short volr)
{
    PORT_TRACE(SsSetMVol);
    gPortSpuMainL = (s16)(voll * 0x3FFF / 127);
    gPortSpuMainR = (s16)(volr * 0x3FFF / 127);
}

void func_80080728(void)
{
    PORT_STUB(func_80080728);
}

void func_80080758(void)
{
    PORT_STUB(func_80080758);
}

void func_80082B50(void)
{
    PORT_STUB(func_80082B50);
}

void func_80082B70(void)
{
    PORT_STUB(func_80082B70);
}

void SsEnd(void)
{
    PORT_STUB(SsEnd);
}

void SsSeqClose(short seq_access_num)
{
    PORT_STUB(SsSeqClose);
}

s32 SsSeqOpen(s32 arg0, s32 arg1)
{
    PORT_STUB(SsSeqOpen);
    return 0;
}

s32 SsSeqPause(s32 arg0)
{
    PORT_STUB(SsSeqPause);
    return 0;
}

void SsSeqPlay(s32 arg0, s32 arg1, s32 arg2)
{
    PORT_STUB(SsSeqPlay);
}

void SsSeqReplay(s32 arg0)
{
    PORT_STUB(SsSeqReplay);
}

void SsSeqSetVol(s32 arg0, s32 arg1, s32 arg2)
{
    PORT_STUB(SsSeqSetVol);
}

void SsSeqStop(short seq_access_num)
{
    PORT_STUB(SsSeqStop);
}

void SsSetLoop(s32 arg0, s32 arg1, s32 arg2)
{
    PORT_STUB(SsSetLoop);
}

void SsSetMono(void)
{
    PORT_STUB(SsSetMono);
}

void SsSetMute(s32 arg0)
{
    PORT_STUB(SsSetMute);
}


void SsSetSerialAttr(char s_num, char attr, char mode)
{
    PORT_STUB(SsSetSerialAttr);
}

void PortCdSetVolume(int left, int right);

/* Serial input 0 is the CD. */
void SsSetSerialVol(short s_num, short voll, short volr)
{
    PORT_TRACE(SsSetSerialVol);
    if (s_num == 0) {
        PortCdSetVolume(voll, volr);
    }
}

void SsSetStereo(void)
{
    PORT_STUB(SsSetStereo);
}

void SsSetTableSize(char* table, short s_max, short t_max)
{
    PORT_STUB(SsSetTableSize);
}

void SsSetTickMode(long tick_mode)
{
    PORT_STUB(SsSetTickMode);
}

void SsStart2(void)
{
    PORT_STUB(SsStart2);
}





void SsUtSetReverbDepth(short ldepth, short rdepth)
{
    PORT_STUB(SsUtSetReverbDepth);
}

void SsUtSetReverbType(short type)
{
    PORT_STUB(SsUtSetReverbType);
}





