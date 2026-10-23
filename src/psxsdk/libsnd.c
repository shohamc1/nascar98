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

extern void SpuVmSeqKeyOff();

extern s32 SpuSetMute(s32 on_off);

void SsSetMute(u8 on_off) {
    if (on_off != 0) {
        if (on_off == 1) {
            SpuSetMute(1);
        }
    } else {
        SpuSetMute(0);
    }
}

extern long SpuSetCommonAttr(SpuCommonAttr *attr);

void SsSetMVol(short voll, short volr) {
    SpuCommonAttr attr;
    attr.mask = SPU_COMMON_MVOLL | SPU_COMMON_MVOLR;
    attr.mvol.left = 0x81 * voll;
    attr.mvol.right = 0x81 * volr;
    SpuSetCommonAttr(&attr);
}

extern long SpuSetCommonAttr(SpuCommonAttr *attr);

void SsSetSerialAttr(char arg0, char arg1, char arg2) {
    SpuCommonAttr attr;
    if (arg0 == 0) {
        if (arg1 == 0) {
            attr.mask = SPU_COMMON_CDMIX;
            attr.cd.mix = arg2;
        }
        if (arg1 == 1) {
            attr.mask = SPU_COMMON_CDREV;
            attr.cd.reverb = arg2;
        }
    }
    if (arg0 == 1) {
        if (arg1 == 0) {
            attr.mask = SPU_COMMON_EXTMIX;
            attr.ext.mix = arg2;
        }
        if (arg1 == 1) {
            attr.mask = SPU_COMMON_EXTREV;
            attr.ext.reverb = arg2;
        }
    }
    SpuSetCommonAttr(&attr);
}

extern long SpuSetCommonAttr(SpuCommonAttr *attr);

void SsSetSerialVol(short channel, short voll, short volr) {
    SpuCommonAttr attr;
    char s_num;

    s_num = channel;
    if (s_num == 0) {
        attr.mask = 0xC0;
        if (voll > 0x7F) {
            voll = 0x7F;
        }
        if (volr > 0x7F) {
            volr = 0x7F;
        }
        attr.cd.volume.left = voll * 258;
        attr.cd.volume.right = volr * 258;
    }
    if (s_num == 1) {
        attr.mask = 0xC00;
        if (voll > 0x7F) {
            voll = 0x7F;
        }
        if (volr > 0x7F) {
            volr = 0x7F;
        }
        attr.ext.volume.left = voll * 258;
        attr.ext.volume.right = volr * 258;
    }
    SpuSetCommonAttr(&attr);
}

static const char sNotSeqDataMessage[] = "This is not SEQ Data.\n";
static const char sOldSeqFormatMessage[] = "This is an old SEQ Data Format.\n";
s32 _SsReadDeltaValue(s16, s16);

s16 _SsInitSoundSeq(s16 arg0, s16 vab_id, u8 *addr) {
    struct SeqStruct *score = &D_800BDE3C[arg0][0];
    s32 channel;

    score->unk4C = vab_id;
    score->unk4A = 0;
    score->unk13 = 0;
    score->unk14 = 0;
    score->unk29 = 0;
    score->unk15 = 0;
    score->unk16 = 0;
    score->unk2A = 0;
    score->channel = 0;
    score->unk7C = 0;
    score->unk80 = 0;
    score->unk84 = 0;
    score->unk72 = 0U;
    score->loopIndex = 0;
    score->unk2B = 0;
    score->deltaValue = 0;
    score->unk27 = 0;
    score->unk28 = 0;
    score->unk10 = 0;
    score->eventStatus = 0;
    score->unkA8 = 0x7F;
    score->unkAA = 0;
    for (channel = 0; channel < 16; channel++) {
        score->programs[channel] = channel;
        score->panpot[channel] = 0x40;
        score->vol[channel] = 0x7f;
    }
    score->unk6E = 1;
    score->readPos = addr;
    if ((*score->readPos == 'S') || (*score->readPos == 'p')) {
        score->readPos += 8;
        if (addr[7] != 1) {
            printf(sNotSeqDataMessage);
            return -1;
        }
    } else {
        printf(sOldSeqFormatMessage);
        return 0;
    }
    score->unk4A = (*score->readPos++) << 8 | *score->readPos++;
    score->unk84 = (*score->readPos++) << 0x10 | (*score->readPos++) << 8 |
                   *score->readPos++;
    if ((score->unk84 / 2) < (60000000 % score->unk84)) {
        score->unk84 = (60000000 / score->unk84) + 1;
    } else {
        score->unk84 = 60000000 / score->unk84;
    }
    score->unk8C = score->unk84;
    score->readPos += 2;
    score->deltaValue = score->unk7C = _SsReadDeltaValue(arg0, 0);
    score->nextSepPos = score->readPos;
    score->loopPos = score->readPos;

    if ((score->unk4A * score->unk84 * 10) < (VBLANK_MINUS * 60)) {
        score->unk70 = score->unk6E =
            (VBLANK_MINUS * 600) / (score->unk4A * score->unk84);
    } else {
        score->unk6E = -1;
        score->unk70 = (score->unk4A * score->unk84 * 10) / (VBLANK_MINUS * 60);
        if ((VBLANK_MINUS * 30) <
            (score->unk4A * score->unk84 * 10) % (VBLANK_MINUS * 60)) {
            score->unk70++;
        }
    }
    score->unk72 = score->unk70;
    return 0;
}

static const char sSeqOpenFailedMessage[] =
    "Can't Open Sequence data any more\n\n";
s16 _SsInitSoundSeq(s16, s16, u8 *);

s16 SsSeqOpen(u32 addr, s16 vab_id) {
    s16 seq_sep_no;
    u32 bit_pos;
    u8 found;

    if (_snd_openflag == 0xFFFFFFFF) {
        printf(sSeqOpenFailedMessage);
        return -1;
    }
    bit_pos = 0;
    found = 0;
    while (!found) {
        if (!((1 << bit_pos) & _snd_openflag)) {
            seq_sep_no = bit_pos;
            found = 1;
        }
        bit_pos++;
    }
    _snd_openflag |= 1 << seq_sep_no;
    if (_SsInitSoundSeq(seq_sep_no, vab_id, addr) == -1) {
        return -1;
    }
    return seq_sep_no;
}

/* SPDX-License-Identifier: MIT */
void _SsGetSeqData(s16, s16);
void _SsSeqPlay(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    s32 elapsed;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    if (score->deltaValue - score->unk70 > 0) {
        if (score->unk6E > 0) {
            score->unk6E--;
        } else if (score->unk6E == 0) {
            score->unk6E = score->unk70;
            score->deltaValue--;
        } else {
            score->deltaValue -= score->unk70;
        }
    } else if (score->deltaValue <= score->unk70) {
        elapsed = score->deltaValue;
        do {
            do {
                _SsGetSeqData(access, sequence);
            } while (score->deltaValue == 0);
            elapsed += score->deltaValue;
        } while (elapsed < score->unk70);
        score->deltaValue = elapsed - score->unk70;
    }
}

/* SPDX-License-Identifier: MIT */
void _SsGetMetaEvent(s16, s16, u8);
void _SsNoteOn(s16, s16, s32, s32);
s32 _SsReadDeltaValue(s16, s16);
void _SsSetPitchBend(s16, s16);
void _SsSetProgramChange(s16, s16, u8);
void _SsSetControlChange(s16, s16, u8);
void _SsGetSeqData(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    u8 event;
    u8 note;
    u8 velocity;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    event = *score->readPos++;
    if (event & 0x80) {
        score->channel = event & 0xF;
        switch (event & 0xF0) {
        case 0x90:
            score->eventStatus = 0x90;
            note = *score->readPos++;
            velocity = *score->readPos++;
            score->deltaValue = _SsReadDeltaValue(access, sequence);
            _SsNoteOn(access, sequence, note, velocity);
            return;
        case 0xB0:
            score->eventStatus = 0xB0;
            _SsSetControlChange(access, sequence, *score->readPos++);
            return;
        case 0xC0:
            score->eventStatus = 0xC0;
            _SsSetProgramChange(access, sequence, *score->readPos++);
            return;
        case 0xE0:
            score->eventStatus = 0xE0;
            score->readPos++;
            _SsSetPitchBend(access, sequence);
            return;
        case 0xF0:
            score->eventStatus = 0xFF;
            score->channel = event & 0xF;
            _SsGetMetaEvent(access, sequence, *score->readPos++);
            return;
        }
    } else {
        switch (score->eventStatus) {
        case 0x90:
            velocity = *score->readPos++;
            score->deltaValue = _SsReadDeltaValue(access, sequence);
            _SsNoteOn(access, sequence, event, velocity);
            return;
        case 0xB0:
            _SsSetControlChange(access, sequence, event);
            return;
        case 0xC0:
            _SsSetProgramChange(access, sequence, event);
            return;
        case 0xE0:
            _SsSetPitchBend(access, sequence);
            return;
        case 0xFF:
            _SsGetMetaEvent(access, sequence, event);
            return;
        }
    }
}

/* SPDX-License-Identifier: MIT */
s32 SpuVmKeyOn(s16, s16, s16, s32, s32, s32);
void SpuVmKeyOff(s16, s16, u8, s32);
void _SsNoteOn(s16 access, s16 sequence, s32 note, s32 velocity) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    u8 channel;
    s32 volume;
    u8 pan;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    channel = score->channel;
    pan = velocity;
    volume = pan & 0xFF;
    pan = score->panpot[channel];
    if ((score->unkAA >> channel) & 1 || score->leftVolume == 0) {
        return;
    }
    if (velocity & 0xFF) {
        SpuVmKeyOn(access | (sequence << 8), score->unk4C,
                   score->programs[channel], note & 0xFF, volume, pan);
        score->unkA8 = volume;
    } else {
        SpuVmKeyOff(access | (sequence << 8), score->unk4C,
                    score->programs[channel], note & 0xFF);
    }
}

/* SPDX-License-Identifier: MIT */
s32 _SsReadDeltaValue(s16, s16);
void _SsSetProgramChange(s16 access, s16 sequence, u8 program) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    score->programs[score->channel] = program;
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

/* SPDX-License-Identifier: MIT */
void SpuVmSetVol();
s32 SpuVmSetProgVol(s16, s16, s32);
void SpuVmDamperOff(void);
void _SsContDataEntry(s16, s16, u8);
void _SsContPortamento(s16, s16, u8);
void _SsContNrpn1(s16, s16, u8);
void _SsContNrpn2(s16, s16, u8);
void _SsContRpn1(s16, s16, u8);
void _SsContRpn2(s16, s16, u8);
void _SsContResetAll(s16, s16);

void _SsSetControlChange(s16 arg0, s16 arg1, u8 control) {
    struct SeqStruct *score = &D_800BDE3C[arg0][arg1];
    s16 channel = score->channel;
    s16 val = *score->readPos++;

    switch (control) {
    case 0x0:
        score->unk4C = val;
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    case 0x6:
        _SsContDataEntry(arg0, arg1, val);
        break;
    case 0x7:
        SpuVmSetVol((arg1 << 8) | arg0, score->unk4C, score->programs[channel],
                    val, score->panpot[channel]);
        score->vol[channel] = val;
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    case 0xA:
        SpuVmSetVol((arg1 << 8) | arg0, score->unk4C, score->programs[channel],
                    score->vol[channel], val);
        score->panpot[channel] = val;
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    case 0xB:
        SpuVmSetProgVol(score->unk4C, score->programs[channel], val);
        SpuVmSetVol((arg1 << 8) | arg0, score->unk4C, score->programs[channel],
                    score->vol[channel], score->panpot[channel]);
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    case 0x40:
        if (val >= 0 && val < 0x40) {
            SpuVmDamperOff();
        } else {
            SpuVmDamperOn();
        }
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    case 0x41:
        _SsContPortamento(arg0, arg1, val);
        break;
    case 0x5B:
        SsUtSetReverbDepth(val, val);
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    case 0x62:
        _SsContNrpn1(arg0, arg1, val);
        break;
    case 0x63:
        _SsContNrpn2(arg0, arg1, val);
        break;
    case 0x64:
        _SsContRpn1(arg0, arg1, val);
        break;
    case 0x65:
        _SsContRpn2(arg0, arg1, val);
        break;
    case 0x79:
        _SsContResetAll(arg0, arg1);
        break;
    default:
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    }
}
typedef struct {
    u8 tones;
    u8 bytes[15];
} ProgramAttrBuffer;
typedef struct {
    u8 bytes[32];
} ToneAttrBuffer;
s16 SsUtGetProgAtr(s16, s16, u8 *);
s16 SsUtGetVagAtr(s16, s16, s16, VagAtr *);
s16 SsUtSetVagAtr(s16, s16, s16, VagAtr *);
void _SsContModulation(s16 access, s16 sequence, s32 value) {
    struct SeqStruct *score;
    ProgramAttrBuffer progAtr;
    ToneAttrBuffer toneAtr;
    s32 tone;
    s32 row;
    s32 offset;
    u8 channel;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    channel = score->channel;
    SsUtGetProgAtr(score->unk4C, score->programs[channel], (u8 *)&progAtr);
    for (tone = 0; tone < progAtr.tones; tone++) {
        SsUtGetVagAtr(score->unk4C, score->programs[channel], tone,
                      (u8 *)&toneAtr);
        toneAtr.bytes[8] = value;
        SsUtSetVagAtr(score->unk4C, score->programs[channel], tone,
                      (u8 *)&toneAtr);
    }
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

void _SsContPortaTime(s16 access, s16 sequence, s32 value) {
    struct SeqStruct *score;
    ProgramAttrBuffer progAtr;
    ToneAttrBuffer toneAtr;
    s32 tone;
    s32 row;
    s32 offset;
    u8 channel;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    channel = score->channel;
    SsUtGetProgAtr(score->unk4C, score->programs[channel], (u8 *)&progAtr);
    for (tone = 0; tone < progAtr.tones; tone++) {
        SsUtGetVagAtr(score->unk4C, score->programs[channel], tone,
                      (u8 *)&toneAtr);
        toneAtr.bytes[11] = value;
        SsUtSetVagAtr(score->unk4C, score->programs[channel], tone,
                      (u8 *)&toneAtr);
    }
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

void _SsContPortamento(s16 arg0, s16 arg1, u8 arg2) {
    struct SeqStruct *score = &D_800BDE3C[arg0][arg1];
    u8 channel = score->channel;
    ProgAtr progAtr;
    VagAtr vagAtr;
    s32 toneNum;

    SsUtGetProgAtr(score->unk4C, score->programs[channel], (u8 *)&progAtr);
    for (toneNum = 0; toneNum < progAtr.tones; toneNum++) {
        SsUtGetVagAtr(score->unk4C, score->programs[channel], toneNum,
                      (u8 *)&vagAtr);
        if (arg2 >= 0 && arg2 < 0x40) {
            vagAtr.mode = 2;
        } else if (arg2 >= 0x40 && arg2 < 0x80) {
            vagAtr.mode = 0;
        }
        SsUtSetVagAtr(score->unk4C, score->programs[channel], toneNum,
                      (u8 *)&vagAtr);
    }

    score->deltaValue = _SsReadDeltaValue(arg0, arg1);
}

void _SsContResetAll(s16 access, s16 sequence) {
    struct SeqStruct *score;
    score = (struct SeqStruct *)((s32)D_800BDE3C[access] + sequence * 0xAC);
    func_80082B70();
    SpuVmDamperOff();
    score->programs[score->channel] = score->channel;
    score->unk13 = 0;
    score->unk14 = 0;
    score->vol[score->channel] = 0x7F;
    score->panpot[score->channel] = 0x40;
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

void _SsContNrpn1(s16 access, s16 sequence, u8 value) {
    extern s32 D_800BDF0C[][16];
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    s32 (*callback)(s16, s16, s32);
    u8 status;

    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    if (score->unk27 != 1) {
        goto check_status;
    }
    if (score->unk10 != 0) {
        goto check_status;
    }
    score->unk28 = value;
    score->unk10 = 1;
    goto after_status;
check_status:
    status = score->unk16;
    if (status == 0x1E) {
        goto after_status;
    }
    if (status == 0x14) {
        goto after_status;
    }
    score->unk15 = value;
    score->unk2A++;
after_status:
    if (score->unk16 == 0x28) {
        callback = (s32 (*)(s16, s16, s32))D_800BDF0C[access][sequence];
        if (callback != 0) {
            callback(access, sequence, value & 0xFF);
        }
    }
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

void _SsContNrpn2(s16 arg0, s16 arg1, u8 arg2) {
    struct SeqStruct *score = &D_800BDE3C[arg0][arg1];

    switch (arg2) {
    case 0x14:
        score->unk16 = arg2;
        score->unk27 = 1;
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        score->loopPos = score->readPos;
        break;

    case 0x1E:
        score->unk16 = arg2;
        if (score->unk28 == 0) {
            score->unk10 = 0;
            score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        } else if (score->unk28 < 0x7FU) {
            score->unk28--;
            score->deltaValue = _SsReadDeltaValue(arg0, arg1);
            if (score->unk28 != 0) {
                score->readPos = score->loopPos;
            } else {
                score->unk10 = 0;
            }
        } else {
            _SsReadDeltaValue(arg0, arg1);
            score->deltaValue = 0;
            score->readPos = score->loopPos;
        }
        break;

    default:
        score->unk16 = arg2;
        score->unk2A += 1;
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        break;
    }
}

/* SPDX-License-Identifier: MIT */
s32 _SsReadDeltaValue(s16, s16);
void _SsContRpn1(s16 access, s16 sequence, u8 value) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    score->unk13 = value;
    score->unk29 = score->unk29 + 1;
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

/* SPDX-License-Identifier: MIT */
s32 _SsReadDeltaValue(s16, s16);
void _SsContRpn2(s16 access, s16 sequence, u8 value) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    score->unk14 = value;
    score->unk29 = score->unk29 + 1;
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

typedef struct {
    u16 unk0, unk2, unk4, unk6, unk8;
    s16 unkA, unkC, unkE, unk10;
} SsAdsr;
typedef struct {
    u8 prior;
    u8 mode;
    u8 vol;
    u8 pan;
    u8 center;
    u8 shift;
    u8 min;
    u8 max;
    u8 vibW;
    u8 vibT;
    u8 porW;
    u8 porT;
    u8 pbmin;
    u8 pbmax;
    u8 reserved1;
    u8 reserved2;
    u16 adsr1;
    u16 adsr2;
    s16 prog;
    s16 vag;
    s16 reserved[4];
} SdkVagAttr;
void _SsSndSetVabAttr(s16, s16, s16, SdkVagAttr, SsAdsr, s16, u8);
/* The odd terms are allocator levers, not original code: `fine` and
 * `coarse` are retail's dead pitch computations (combine folds their uses,
 * so they stay in s5); `ghost` is a dead copy of `value` whose only use
 * folds to zero, which leaves retail's extra `andi v1,s6,0xFF` in the
 * `beqz` delay slot; the `((x + y) << 4) & 0xF` terms in the three constant
 * stores add one 8-byte phantom frame slot each; the inline helper keeps
 * loop.c from hoisting `value & 0x7F`. */
static __inline__ int SsDataEntryLow7(u8 data) {
    return data & 0x7F;
}
void _SsContDataEntry(s16 access, s16 sequence, u8 value) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    ProgAtr progAtr;
    VagAtr vagAtr;
    SsAdsr adsr;
    u8 channel;
    s32 i;
    u16 fine;
    s32 coarse;
    u16 ghost;

    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    channel = score->channel;
    SsUtGetProgAtr(score->unk4C, score->programs[channel], (u8 *)&progAtr);
    if (score->unk27 == 1 && score->unk10 == 0) {
        score->unk28 = value;
        score->unk10 = 1 + ((((s32)score + channel) << 4) & 0xF);
        score->deltaValue = _SsReadDeltaValue(access, sequence);
        return;
    }
    if (score->unk29 == 2) {
        if (score->unk13 == 0 && score->unk14 == 0) {
            for (i = 0; i < progAtr.tones; i++) {
                SsUtGetVagAtr(score->unk4C, score->programs[channel], i,
                              &vagAtr);
                vagAtr.pbmax = SsDataEntryLow7(value);
                vagAtr.pbmin = SsDataEntryLow7(value);
                SsUtSetVagAtr(score->unk4C, score->programs[channel], i,
                              &vagAtr);
            }
        }
        if (score->unk13 == 1 && score->unk14 == 0) {
            ghost = value;
            if ((u8)(value - 0x41) < 0x3F) {
                fine = (value * 100 / 0x2000) << 13;
            } else {
                fine = (ghost << 4) & 0xF;
            }
            for (i = 0; i < progAtr.tones; i++) {
                SsUtGetVagAtr(score->unk4C, score->programs[channel], i,
                              &vagAtr);
                vagAtr.shift += fine & 0xFF;
                SsUtSetVagAtr(score->unk4C, score->programs[channel], i,
                              &vagAtr);
            }
        }
        if (score->unk13 == 2 && score->unk14 == 0) {
            if ((u8)(value - 0x40) < 0x40) {
                coarse = (value * 25) << 8;
            } else {
                coarse = 0;
            }
            for (i = 0; i < progAtr.tones; i++) {
                SsUtGetVagAtr(score->unk4C, score->programs[channel], i,
                              &vagAtr);
                vagAtr.center += coarse & 0xFF;
                SsUtSetVagAtr(score->unk4C, score->programs[channel], i,
                              &vagAtr);
            }
        }
        score->deltaValue = _SsReadDeltaValue(access, sequence);
        score->unk29 = (((s32)score - channel) << 5) & 0xF;
        return;
    }
    if (score->unk2A == 2) {
        if (score->unk16 == 0x10) {
            for (i = 0; i < progAtr.tones; i++) {
                _SsSndSetVabAttr(score->unk4C, score->programs[channel], i,
                                 *(SdkVagAttr *)&vagAtr, *(SsAdsr *)&adsr,
                                 score->unk15, value);
            }
        } else {
            _SsSndSetVabAttr(score->unk4C, score->programs[channel],
                             score->unk16, *(SdkVagAttr *)&vagAtr,
                             *(SsAdsr *)&adsr, score->unk15, value);
        }
        score->deltaValue = _SsReadDeltaValue(access, sequence);
        score->unk2A = (((s32)score ^ channel) << 4) & 0xF;
        return;
    }
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

s16 SsUtGetVagAtr(s16, s16, s16, VagAtr *);
s16 SsUtSetVagAtr(s16, s16, s16, VagAtr *);
void SsUtSetReverbDepth(short, short);
void SsUtSetReverbFeedback(short);
void SsUtSetReverbDelay(short);
void func_80082B50(void);
void func_80082B70(void);
void _SsSndSetVabAttr(s16 vabId, s16 progNum, s16 toneNum, SdkVagAttr vagAtr,
                      SsAdsr adsrBuffer, s16 idx, u8 attr) {
    s16 temp;
    SsUtGetVagAtr(vabId, progNum, toneNum, (u8 *)&vagAtr);
    switch (idx) {
    case 0:
        vagAtr.prior = attr;
        SsUtSetVagAtr(vabId, progNum, toneNum, (u8 *)&vagAtr);
        break;
    case 1:
        vagAtr.mode = attr;
        SsUtSetVagAtr(vabId, progNum, toneNum, (u8 *)&vagAtr);
        if (attr == 0) {
            func_80082B70();
        } else if (attr == 1) {
        } else if (attr == 2) {
        } else if (attr == 3) {
        } else if (attr == 4) {
            func_80082B50();
        }
        break;
    case 2:
        vagAtr.min = attr;
        SsUtSetVagAtr(vabId, progNum, toneNum, (u8 *)&vagAtr);
        break;
    case 3:
        vagAtr.max = attr;
        SsUtSetVagAtr(vabId, progNum, toneNum, (u8 *)&vagAtr);
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        temp = idx - 4;
        _SsUtResolveADSR(vagAtr.adsr1, vagAtr.adsr2, &adsrBuffer);
        __asm__(".rdata\n.long 0\n.text");
        switch (temp) {
        case 0:
            adsrBuffer.unkA = 0;
            adsrBuffer.unk0 = attr;
            break;
        case 1:
            adsrBuffer.unkA = 1;
            adsrBuffer.unk0 = attr;
            break;
        case 2:
            adsrBuffer.unk2 = attr;
            break;
        case 3:
            adsrBuffer.unk4 = attr;
            break;
        case 4:
            adsrBuffer.unkC = 0;
            adsrBuffer.unk6 = attr;
            break;
        case 5:
            adsrBuffer.unkC = 1;
            adsrBuffer.unk6 = attr;
            break;
        case 6:
            adsrBuffer.unkE = 0;
            adsrBuffer.unk8 = attr;
            break;
        case 7:
            adsrBuffer.unkE = 1;
            adsrBuffer.unk8 = attr;
            break;
        case 8:
            if (attr > 0 && attr < 0x40)
                adsrBuffer.unk10 = 0;
            else if (attr >= 0x40 && attr < 0x80)
                adsrBuffer.unk10 = 1;
            break;
        case 9:
            vagAtr.vibT = attr;
            break;
        case 10:
            vagAtr.porW = attr;
            break;
        }
        _SsUtBuildADSR(&adsrBuffer, &vagAtr.adsr1, &vagAtr.adsr2);
        SsUtSetVagAtr(vabId, progNum, toneNum, (u8 *)&vagAtr);
        break;
    case 15:
        SsUtSetReverbType(attr);
        break;
    case 16:
        SsUtSetReverbDepth(attr, attr);
        break;
    case 17:
        SsUtSetReverbFeedback(attr);
        break;
    case 18:
    case 19:
        SsUtSetReverbDelay(attr);
        break;
    case 20:
    case 21:
    case 22:
        break;
    }
}

/* SPDX-License-Identifier: MIT */
s32 SpuVmPitchBend();
s32 _SsReadDeltaValue(s16, s16);
void _SsSetPitchBend(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    u8 channel;
    u8 *data;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    channel = score->channel;
    data = score->readPos++;
    SpuVmPitchBend((sequence << 8) | access, score->unk4C,
                   score->programs[channel], *data);
    score->deltaValue = _SsReadDeltaValue(access, sequence);
}

extern void _SsSndNextSep(s16, s16);

void _SsGetMetaEvent(s16 arg0, s16 arg1, u8 arg2) {
    struct SeqStruct *score = &D_800BDE3C[arg0][arg1];

    switch (arg2) {
    case 0x51:
        score->unk8C = (*score->readPos++) << 0x10 | (*score->readPos++) << 8 |
                       *score->readPos++;
        score->unk8C = 60000000 / score->unk8C;
        if ((score->unk4A * score->unk8C * 10) < VBLANK_MINUS * 60) {
            score->unk70 = score->unk6E =
                (VBLANK_MINUS * 600) / (score->unk4A * score->unk8C);
        } else {
            score->unk6E = -1;
            score->unk70 =
                (score->unk4A * score->unk8C * 10) / (VBLANK_MINUS * 60);
            if ((VBLANK_MINUS * 30) <
                (score->unk4A * score->unk8C * 10) % (VBLANK_MINUS * 60)) {
                score->unk70++;
            }
        }
        score->deltaValue = _SsReadDeltaValue(arg0, arg1);
        return;
    case 0x2F:
        score->loopIndex++;
        if (score->loopCount == 0) {
            score->unk80 = 0;
            score->unk27 = 0;
            score->deltaValue = 0;
            score->readPos = score->nextSepPos;
            return;
        }
        if (score->loopIndex < score->loopCount) {
            score->unk80 = 0;
            score->unk27 = 0;
            score->deltaValue = 0;
            score->readPos = score->nextSepPos;
            score->loopPos = score->nextSepPos;
            return;
        }
        D_800BDE3C[arg0][arg1].unk90 &= ~1;
        D_800BDE3C[arg0][arg1].unk90 &= ~8;
        D_800BDE3C[arg0][arg1].unk90 &= ~2;
        D_800BDE3C[arg0][arg1].unk90 |= 0x200;
        D_800BDE3C[arg0][arg1].unk90 |= 4;
        score->unk2B = 0;
        score->loopPos = score->nextSepPos;
        if (score->unk3C != 0xFF) {
            score->unk2B = 0;
            _SsSndNextSep(score->unk3C, score->unk0);
            SpuVmSeqKeyOff((arg1 << 8) | arg0);
        }
        SpuVmSeqKeyOff((arg1 << 8) | arg0);
        score->deltaValue = score->unk70;
        return;
    }
}

/* SPDX-License-Identifier: MIT */
s32 _SsReadDeltaValue(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    s32 delta;
    u8 next;
    u32 value;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    value = *score->readPos++;
    if (value == 0) {
        return 0;
    }
    if (value & 0x80) {
        value &= 0x7F;
        do {
            next = *score->readPos++;
            value = (value << 7) + (next & 0x7F);
        } while (next & 0x80);
    }
    delta = value * 10;
    score->unk80 = delta + score->unk80;
    return delta;
}

/* Resolved ADSR envelope of a VagAtr: five rates/levels and four mode
 * flags, split out of the two packed adsr1/adsr2 words. */

void _SsUtResolveADSR(u16 adsr1, u16 adsr2, SsAdsr *adsr) {
    u32 temp;

    adsr->unkA = adsr1 & 0x8000;
    adsr->unkC = adsr2 & 0x8000;
    adsr->unk10 = adsr2 & 0x4000;
    temp = adsr1 & 0xFFFF;
    adsr->unkE = adsr2 & 0x20;
    adsr->unk0 = (temp >> 8) & 0x7F;
    adsr->unk2 = (temp >> 4) & 0xF;
    adsr->unk4 = adsr1 & 0xF;
    adsr->unk6 = (adsr2 >> 6) & 0x7F;
    adsr->unk8 = adsr2 & 0x1F;
}

void _SsUtBuildADSR(SsAdsr *adsr, u16 *adsr1, u16 *adsr2) {
    u16 word2;
    s32 mode;
    s32 am;
    u16 word1;

    mode = -(adsr->unkC != 0) & ~0x7FFF;
    am = -(adsr->unkA != 0) & ~0x7FFF;
    word2 = mode;
    if (adsr->unk10 != 0) {
        word2 = mode | 0x4000;
    }
    word1 = am | ((adsr->unk0 << 8) & 0x7F00) | ((adsr->unk2 << 4) & 0xF0) |
            (adsr->unk4 & 0xF);
    word2 = word2 | ((adsr->unk6 << 6) & 0x1FC0) | (adsr->unk8 & 0x1F);
    *adsr1 = word1;
    *adsr2 = word2;
}

/* SPDX-License-Identifier: MIT */
void _SsSndNextSep(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    score->loopCount = 1;
    score->loopIndex = 0;
    D_800BDE3C[access][sequence].unk90 &= ~0x100;
    D_800BDE3C[access][sequence].unk90 &= ~0x8;
    D_800BDE3C[access][sequence].unk90 &= ~0x2;
    D_800BDE3C[access][sequence].unk90 &= ~0x4;
    D_800BDE3C[access][sequence].unk90 &= ~0x200;
    score->unk2B = 1;
    score->readPos = score->nextSepPos;
    D_800BDE3C[access][sequence].unk90 |= 1;
}

void SsSetTempo(s16 access, s16 sequence, s16 tempo) {
    struct SeqStruct *score = &D_800BDE3C[access][sequence];

    score->unk8C = tempo;
    if ((score->unk4A * score->unk8C * 10) < (VBLANK_MINUS * 60)) {
        score->unk70 = score->unk6E =
            (VBLANK_MINUS * 600) / (score->unk4A * score->unk8C);
    } else {
        score->unk6E = -1;
        score->unk70 = (score->unk4A * score->unk8C * 10) / (VBLANK_MINUS * 60);
        if ((VBLANK_MINUS * 30) <
            (score->unk4A * score->unk8C * 10) % (VBLANK_MINUS * 60)) {
            score->unk70++;
        }
    }
    score->unk72 = score->unk70;
}

void SsSetLoop(s16 access, s16 sequence, s16 count) {
    struct SeqStruct *score;
    score = D_800BDE3C[access];
    score[sequence].loopCount = count;
    score[sequence].loopIndex = 0;
}

s32 SsIsEos(s32 vabId, s32 seqId) {
    return D_800BDE3C[(s16)vabId][(s16)seqId].unk2B;
}

extern s32 D_800BDF0C[][16];

void SsSetMarkCallback(s16 arg0, s16 arg1, s32 arg2) {
    s32 shifted;
    s32(*rows)[16];
    s32 *row;

    shifted = arg0 << 16;
    rows = D_800BDF0C;
    row = (s32 *)((shifted >> 10) + (s32)rows);
    row[arg1] = arg2;
}

void _SsClose(s16 seq_sep_num) {
    s32 seq_num;
    SpuVmSetSeqVol(seq_sep_num, 0, 0, 1);
    SpuVmSeqKeyOff(seq_sep_num);
    _snd_openflag &= ~(1 << seq_sep_num);
    for (seq_num = 0; seq_num < _snd_seq_t_max; seq_num++) {
        D_800BDE3C[seq_sep_num][seq_num].unk90 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk3C = 0xFF;
        D_800BDE3C[seq_sep_num][seq_num].unk0 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk3E = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk40 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk94 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk98 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk42 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unkA4 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unkA0 = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk9C = 0;
        D_800BDE3C[seq_sep_num][seq_num].unk44 = 0;
        D_800BDE3C[seq_sep_num][seq_num].leftVolume = 0x7f;
        D_800BDE3C[seq_sep_num][seq_num].rightVolume = 0x7f;
    }
}

extern void _SsClose(short);

void SsSeqClose(short seq_access_num) {
    _SsClose(seq_access_num);
}

extern void _SsClose(short);

void SsSepClose(short sep_access_num) {
    _SsClose(sep_access_num);
}

extern s16 D_800A2070[];
extern s16 D_800A2080[];
extern s32 D_800BDF0C[][16];
extern void SpuVmInit(u8);

void _SsInit(void) {
    u16 *var_a2;
    s32 i, j;

    var_a2 = (u16 *)0x1F801C00;
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 8; j++) {
            *var_a2++ = D_800A2070[j];
        }
    }

    var_a2 = (u16 *)0x1F801D80;
    for (i = 0; i < 16; i++) {
        *var_a2++ = D_800A2080[i];
    }

    SpuVmInit(24);

    for (j = 0; j < 32; j++) {
        for (i = 0; i < 16; i++) {
            D_800BDF0C[j][i] = 0;
        }
    }

    VBLANK_MINUS = 60;
    _snd_openflag = 0;
    _snd_ev_flag = 0;
}

extern void _SsInit(void);
extern void func_80087CC0(void);

void func_80080728(void) {
    ResetCallback();
    func_80087CC0();
    _SsInit();
}

void func_80080758(void) {
    SpuQuit();
}

/* SPDX-License-Identifier: MIT */

extern s32 D_800A20A0[];
extern s32 D_800A20A4[];
extern Callback D_800A20A8[];
extern s32 D_800A20AC[];
extern u8 D_800A20B0[];
extern u8 D_800A20B1[];
extern u8 D_800A20B2[];
extern void _SsTrapIntrVSync(void);
extern void _SsSeqCalledTbyT_1per2(void);

s32 _SsStart(s32 arg0) {
    s32 wait;
    s32 mode;
    s32 rcntSpec;
    s32 rcntTarget;
    s32 b2;
    Callback callback;

    wait = 1000;
    while (--wait >= 0) {
    }
    rcntSpec = 0xF2000002;
    D_800A20B0[0] = 0;
    mode = D_800A20A0[0];
    D_800A20B2[0] = 6;
    D_800A20B1[0] = 0;
    D_800A20AC[0] = 0;
    switch (mode) {
    case 0:
        ((u8 *)D_800A20B1)[1] = 0xFF;
        return;
    case 5:
        ((u8 *)D_800A20A4)[0xE] = 0;

        if (arg0 == 0) {
            D_800A20B0[0] = 1;
        } else {
            rcntSpec = 0xF2000003;
            rcntTarget = 1;
        }
        break;
    case 3:
        rcntTarget = 0x89D0;
        break;
    case 2:
        rcntTarget = 0x44E8;
        break;
    default: {
        u8 *env;
        register s32 ticks asm("v1");
        register s32 quot asm("v0");
        register s32 envD asm("v1");

        env = (u8 *)D_800A20A4;
        __asm__("" : "=r"(env) : "0"(env));
        if (*(s32 *)env != 0) {
            return;
        }
        ticks = *(s32 *)(env - 4);
        if (ticks < 0x46) {
            quot = 0x204CC0 / ticks;
            envD = env[0xD];
            envD = envD + 1;
            env[0xD] = envD;
        } else {
            quot = 0x409980 / ticks;
        }
        rcntTarget = quot;
        break;
    }
    }
    if (D_800A20B0[0] != 0) {
        EnterCriticalSection();
        VSyncCallback(D_800A20A8[0]);
    } else {
        EnterCriticalSection();
        ResetRCnt(rcntSpec);
        SetRCnt(rcntSpec, rcntTarget & 0xFFFF, 0x1000);
        b2 = ((u8 *)D_800A20B1)[1];
        if (b2 == 0) {
            D_800A20AC[0] = InterruptCallback(0, NULL);
            b2 = D_800A20B2[0];
            callback = _SsTrapIntrVSync;
        } else if (D_800A20B1[0] == 0) {
            callback = D_800A20A8[0];
        } else {
            callback = _SsSeqCalledTbyT_1per2;
        }
        InterruptCallback(b2, callback);
    }
    ExitCriticalSection();
    return;
}

/* SPDX-License-Identifier: MIT */

extern s32 _SsStart(s32); /* extern */

void SsStart(void) {
    _SsStart(1);
}

/* SPDX-License-Identifier: MIT */

extern s32 _SsStart(s32); /* extern */

void SsStart2(void) {
    _SsStart(0);
}

void _SsTrapIntrVSync(void) {
    if (D_800A20AC[0] != 0)
        ((Callback)D_800A20AC[0])();
    ((Callback)D_800A20A8[0])();
}

extern s32 D_800A20B4Read[];
extern s32 D_800A20B4Write[];
void _SsSeqCalledTbyT_1per2(void) {
    if (D_800A20B4Read[0] == 0) {
        D_800A20B4Write[0] = 1;
        return;
    }
    D_800A20B4Write[0] = 0;
    ((Callback)D_800A20A8[0])();
}

extern void SpuVmFlush(void);
extern void _SsSndPlay(s16, s16);
extern void _SsSndCrescendo(s16, s16);
extern void _SsSndDecrescendo(s16, s16);
extern void _SsSndTempo(s16, s16);
extern void _SsSndPause(s16, s16);
extern void _SsSndReplay(s16, s16);
extern void _SsSndStop(s16, s16);

void SsSeqCalledTbyT(void) {
    s32 i;
    s32 j;
    if (_snd_ev_flag != 1) {
        _snd_ev_flag = 1;

        SpuVmFlush();

        for (i = 0; i < _snd_seq_s_max; i++) {
            if ((1 << i) & _snd_openflag) {
                for (j = 0; j < _snd_seq_t_max; j++) {
                    if (D_800BDE3C[i][j].unk90 & 1) {
                        _SsSndPlay(i, j);

                        if (D_800BDE3C[i][j].unk90 & 0x10) {
                            _SsSndCrescendo(i, j);
                        }

                        if (D_800BDE3C[i][j].unk90 & 0x20) {
                            _SsSndDecrescendo(i, j);
                        }

                        if (D_800BDE3C[i][j].unk90 & 0x40) {
                            _SsSndTempo(i, j);
                        }

                        if (D_800BDE3C[i][j].unk90 & 0x80) {
                            _SsSndTempo(i, j);
                        }
                    }

                    if (D_800BDE3C[i][j].unk90 & 2) {
                        _SsSndPause(i, j);
                    }

                    if (D_800BDE3C[i][j].unk90 & 8) {
                        _SsSndReplay(i, j);
                    }

                    if (D_800BDE3C[i][j].unk90 & 4) {
                        ((void (*)())_SsSndStop)(i, j);
                        D_800BDE3C[i][j].unk90 = 0;
                    }
                }
            }
        }
        _snd_ev_flag = 0;
    }
}

extern long SpuVmGetSeqVol(short, short *, short *);
extern s32 SpuVmSetSeqVol(s16, u16, u16, s16);

void _SsSndCrescendo(s16 arg0, s16 arg1) {
    struct SeqStruct *score = &D_800BDE3C[arg0][arg1];
    u16 voll, volr;

    score->unk98--;

    if (score->unk42 > 0) {
        if ((score->unk98 % score->unk42) == 0) {
            score->unk40--;
            if (score->unk40 >= 0) {
                SpuVmGetSeqVol(arg0 | (arg1 << 8), &voll, &volr);
                if ((voll + 1) <= (voll + score->unk40)) {
                    SpuVmSetSeqVol(arg0 | (arg1 << 8), voll + 1, volr + 1, 0);
                }
            } else {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), 0x7F, 0x7F, 0);
                D_800BDE3C[arg0][arg1].unk90 &= ~0x10;
            }
            if ((score->unk98 == 0) || (score->unk40 == 0)) {
                D_800BDE3C[arg0][arg1].unk90 &= ~0x10;
            }
        }
    } else if (score->unk42 < 0) {
        score->unk40 += score->unk42;
        if (score->unk40 >= 0) {
            SpuVmGetSeqVol(arg0 | (arg1 << 8), &voll, &volr);
            if (((voll - score->unk42) >= 0x7F) &&
                ((volr - score->unk42) >= 0x7F)) {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), 0x7F, 0x7F, 0);
            }
            if (((score->unk94 - score->unk98) * -score->unk42) <
                score->unk3E) {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), voll - score->unk42,
                               volr - score->unk42, 0);
            }
        } else {
            SpuVmSetSeqVol(arg0 | (arg1 << 8), 0x7F, 0x7F, 0);
            D_800BDE3C[arg0][arg1].unk90 &= ~0x10;
        }
        if ((score->unk98 == 0) || (score->unk40 == 0)) {
            D_800BDE3C[arg0][arg1].unk90 &= ~0x10;
        }
    }
    SpuVmGetSeqVol(arg0 | (arg1 << 8), &score->unk78, &score->unk7A);
}

void _SsSndDecrescendo(s16 arg0, s16 arg1) {
    struct SeqStruct *score = &D_800BDE3C[arg0][arg1];
    u16 voll, volr;

    score->unk98--;

    if (score->unk42 > 0) {
        if ((score->unk98 % score->unk42) == 0) {
            score->unk40--;
            if (score->unk40 > 0) {
                SpuVmGetSeqVol(arg0 | (arg1 << 8), &voll, &volr);
                if (((voll - score->unk40) > 0) &&
                    ((volr - score->unk40) > 0) && voll != 1) {
                    SpuVmSetSeqVol(arg0 | (arg1 << 8), voll - 1, volr - 1, 0);
                } else {
                    SpuVmSetSeqVol(arg0 | (arg1 << 8), 1, 1, 0);
                }
            } else {
                D_800BDE3C[arg0][arg1].unk90 &= ~0x20;
            }
            if ((score->unk98 == 0) || (score->unk40 == 0)) {
                D_800BDE3C[arg0][arg1].unk90 &= ~0x20;
            }
        }
    } else {
        score->unk40 += score->unk42;
        if (score->unk40 > 0) {
            SpuVmGetSeqVol(arg0 | (arg1 << 8), &voll, &volr);
            if ((score->unk3E >=
                 ((score->unk94 - score->unk98) * -score->unk42)) &&
                -score->unk42 < voll) {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), voll + score->unk42,
                               volr + score->unk42, 0);
            } else {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), 1, 1, 0);
            }
        } else {
            D_800BDE3C[arg0][arg1].unk90 &= ~0x20;
        }
        if ((score->unk98 == 0) || (score->unk40 == 0)) {
            D_800BDE3C[arg0][arg1].unk90 &= ~0x20;
        }
    }
    SpuVmGetSeqVol(arg0 | (arg1 << 8), &score->unk78, &score->unk7A);
}

/* SPDX-License-Identifier: MIT */
void _SsSndPause(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    SpuVmSeqKeyOff((sequence << 8) | access, sequence << 8);
    score->unk2B = 0;
    D_800BDE3C[access][sequence].unk90 &= ~2;
}

void _SsSndPlay(s16 arg0, s16 arg1) {
    _SsSeqPlay(arg0, arg1);
}

/* SPDX-License-Identifier: MIT */
void _SsSndReplay(s16 access, s16 sequence) {
    D_800BDE3C[access][sequence].unk2B = 1;
    D_800BDE3C[access][sequence].unk90 &= ~8;
}

/* SPDX-License-Identifier: MIT */

extern s32 D_800BDE2C[];

void SsSetTickMode(long tickMode) {
    s32 videoMode;
    s32 mode;

    videoMode = GetVideoMode();
    if (tickMode & 0x1000) {
        D_800A20A4[0] = 1;
        D_800A20A0[0] = tickMode & 0xFFF;
    } else {
        D_800A20A4[0] = 0;
        D_800A20A0[0] = tickMode;
    }
    mode = D_800A20A0[0];
    if (mode < 6) {
        switch (mode) {
        case 4:
            D_800BDE2C[0] = 50;
            if (videoMode == 1) {
                D_800A20A0[0] = 5;
            } else {
                D_800A20A0[0] = 50;
            }
            break;
        case 1:
            D_800BDE2C[0] = 60;
            if (videoMode == 0) {
                D_800A20A0[0] = 5;
            } else {
                D_800A20A0[0] = 60;
            }
            break;
        case 3:
            D_800BDE2C[0] = 120;
            break;
        case 2:
            D_800BDE2C[0] = 240;
            break;
        case 5:
            if (videoMode == 0) {
                D_800BDE2C[0] = 60;
            } else if (videoMode == 1) {
                D_800BDE2C[0] = 50;
            } else {
                D_800BDE2C[0] = 60;
            }
            break;
        case 0:
            if (videoMode == 0) {
                D_800BDE2C[0] = 60;
            } else if (videoMode == 1) {
                D_800BDE2C[0] = 50;
            } else {
                D_800BDE2C[0] = 60;
            }
            break;
        default:
            D_800BDE2C[0] = 60;
            break;
        }
    } else {
        D_800BDE2C[0] = mode;
    }
}

extern u8 D_800A20B0Read[];
extern u8 D_800A20B0Write[];
extern s32 D_800A20ACRead[];
extern s32 D_800A20ACWrite[];
extern u8 D_800A20B2Read[];
extern u8 D_800A20B2Write[];
void SsEnd(void) {
    if (D_800A20A4[0] == 0) {
        D_800A20B1[0] = 0;
        EnterCriticalSection();
        if (D_800A20B0Read[0] != 0) {
            VSyncCallback(0);
            D_800A20B0Write[0] = 0;
        } else if (D_800A20B2Read[0] == 0) {
            InterruptCallback(0, (Callback)D_800A20ACRead[0]);
            D_800A20ACWrite[0] = 0;
        } else {
            InterruptCallback(6, 0);
        }
        ExitCriticalSection();
        D_800A20B2Write[0] = 0xFF;
    }
}

void SsSetTableSize(char *table, short s_max, short t_max) {
    s32 i, j;
    struct SeqStruct *pTypedTable;

    _snd_seq_s_max = s_max;
    _snd_seq_t_max = t_max;
    pTypedTable = (struct SeqStruct *)table;
    for (i = 0; i < s_max; i++) {
        D_800BDE3C[i] = &pTypedTable[i * t_max];
    }

    for (i = 0; i < _snd_seq_s_max; i++) {
        for (j = 0; j < _snd_seq_t_max; j++) {
            D_800BDE3C[i][j].unk90 = 0;
            D_800BDE3C[i][j].unk3C = 0xFF;
            D_800BDE3C[i][j].unk0 = 0;
            D_800BDE3C[i][j].unk3E = 0;
            D_800BDE3C[i][j].unk40 = 0;
            D_800BDE3C[i][j].unk94 = 0;
            D_800BDE3C[i][j].unk98 = 0;
            D_800BDE3C[i][j].unk42 = 0;
            D_800BDE3C[i][j].unkA4 = 0;
            D_800BDE3C[i][j].unkA0 = 0;
            D_800BDE3C[i][j].unk9C = 0;
            D_800BDE3C[i][j].unk44 = 0;
            D_800BDE3C[i][j].leftVolume = 0x7F;
            D_800BDE3C[i][j].rightVolume = 0x7F;
            D_800BDE3C[i][j].unk78 = 0x7F;
            D_800BDE3C[i][j].unk7A = 0x7F;
        }
    }
}

extern long SpuVmGetSeqVol(short, short *, short *);
void _SsSndSetPauseMode(short access, short sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    SpuVmGetSeqVol(access | (sequence << 8), &score->unk78, &score->unk7A);
    D_800BDE3C[access][sequence].unk90 &= ~1;
    D_800BDE3C[access][sequence].unk90 &= ~8;
    D_800BDE3C[access][sequence].unk90 |= 2;
}

extern void _SsSndSetPauseMode(short, short);

void SsSeqPause(short seq_access_num) {
    _SsSndSetPauseMode(seq_access_num, 0);
}

extern void _SsSndSetPauseMode(short, short);

void SsSepPause(short sep_access_num, short seq_num) {
    _SsSndSetPauseMode(sep_access_num, seq_num);
}

/* SPDX-License-Identifier: MIT */
extern s32 SpuVmSetSeqVol(s16, u16, u16, s16);
void Snd_SetPlayMode(s16 access, s16 sequence, u8 mode, s16 loopCount) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);
    D_800BDE3C[access][sequence].unk90 &= ~0x200;
    D_800BDE3C[access][sequence].unk90 &= ~4;
    score->loopCount = loopCount;
    if (mode == 1) {
        D_800BDE3C[access][sequence].unk90 |= 1;
        score->loopIndex = 0;
        score->unk2B = 1;
        SpuVmSetSeqVol(access | (sequence << 8), score->leftVolume,
                       score->rightVolume, 0);
    } else if (mode == 0) {
        D_800BDE3C[access][sequence].unk90 |= 2;
    }
}

extern void Snd_SetPlayMode(short, short, unsigned char, short);

void SsSeqPlay(short seq_access_num, char play_mode, short l_count) {
    Snd_SetPlayMode(seq_access_num, 0, play_mode, l_count);
}

extern void Snd_SetPlayMode(short, short, unsigned char, short);

void SsSepPlay(short sep_access_num, short seq_num, char play_mode,
               short l_count) {
    Snd_SetPlayMode(sep_access_num, seq_num, play_mode, l_count);
}

void _SsSndSetReplayMode(short access, short sequence) {
    s32 status;
    status = D_800BDE3C[access][sequence].unk90;
    if ((status & 0x204) != 0) {
        return;
    }
    if ((status & 0x100) != 0) {
        return;
    }
    D_800BDE3C[access][sequence].unk90 &= ~2;
    D_800BDE3C[access][sequence].unk90 |= 8;
    D_800BDE3C[access][sequence].unk90 |= 1;
}

extern void _SsSndSetReplayMode(short, short);

void SsSeqReplay(short seq_access_num) {
    _SsSndSetReplayMode(seq_access_num, 0);
}

extern void _SsSndSetReplayMode(short, short);

void SsSepReplay(short sep_access_num, short seq_num) {
    _SsSndSetReplayMode(sep_access_num, seq_num);
}

extern s32 SpuVmSetSeqVol(s16, u16, u16, s16);

void _SsSndSetVol(s32 access_num, s32 seq_num, u16 voll, u16 volr) {
    SpuVmSetSeqVol(access_num | (seq_num << 8), voll, volr, 0);
}

extern s32 SpuVmSetSeqVol(s16, u16, u16, s16);

void SsSeqSetVol(short access_num, short voll, short volr) {
    SpuVmSetSeqVol(access_num, voll, volr, 0);
}

extern s32 SpuVmSetSeqVol(s16, u16, u16, s16);

void SsSepSetVol(short sep_access_num, short seq_num, short voll, short volr) {
    SpuVmSetSeqVol(sep_access_num | (seq_num << 8), voll & 0xFFFF,
                   volr & 0xFFFF, 0);
}

extern long SpuVmGetSeqVol(short, short *, short *);

void SsSeqGetVol(short access_num, short seq_num, short *voll, short *volr) {
    SpuVmGetSeqVol(access_num | (seq_num << 8), voll, volr);
}

/* SPDX-License-Identifier: MIT */
void _SsSndStop(s16 access, s16 sequence) {
    struct SeqStruct *score;
    s32 row;
    s32 offset;
    int i;
    row = (s32)D_800BDE3C[access];
    offset = sequence * 0xAC;
    score = (struct SeqStruct *)(offset + row);

    D_800BDE3C[access][sequence].unk90 &= ~1;
    D_800BDE3C[access][sequence].unk90 &= ~2;
    D_800BDE3C[access][sequence].unk90 &= ~8;
    D_800BDE3C[access][sequence].unk90 |= 4;
    SpuVmSeqKeyOff(sequence << 8 | access);
    score->unk2B = 0;
    score->unk80 = 0;
    score->unk27 = 0;
    score->unk13 = 0;
    score->unk14 = 0;
    score->unk29 = 0;
    score->unk15 = 0;
    score->unk16 = 0;
    score->unk2A = 0;
    score->channel = 0;
    score->loopIndex = 0;
    score->unk27 = 0;
    score->unk28 = 0;
    score->unk10 = 0;
    score->eventStatus = 0;
    score->deltaValue = score->unk7C;
    score->unk8C = score->unk84;
    score->unk70 = score->unk72;
    score->readPos = score->nextSepPos;
    score->loopPos = score->nextSepPos;
    for (i = 0; i < 16; i++) {
        score->programs[i] = i;
        score->panpot[i] = 0x40;
        score->vol[i] = 127;
    }

    score->unk78 = 0x7F;
    score->unk7A = 0x7F;
}

extern void _SsSndStop(short, short);

void SsSeqStop(short seq_access_num) {
    _SsSndStop(seq_access_num, 0);
}

extern void _SsSndStop(short, short);

void SsSepStop(short sep_access_num, short seq_num) {
    _SsSndStop(sep_access_num, seq_num);
}

void _SsSndTempo(s16 arg0, s16 arg1) {
    struct SeqStruct *pSeq = &D_800BDE3C[arg0][arg1];

    pSeq->unkA0--;

    if (pSeq->unk44 > 0) {
        if ((pSeq->unkA0 % pSeq->unk44) == 0) {
            if (pSeq->unk8C > pSeq->unkA4) {
                pSeq->unk8C--;
            } else if (pSeq->unk8C < pSeq->unkA4) {
                pSeq->unk8C++;
            }

            pSeq->unk70 =
                (pSeq->unk4A * pSeq->unk8C * 10) / (VBLANK_MINUS * 60);
            if (pSeq->unk70 <= 0) {
                pSeq->unk70 = 1;
            }
            if ((pSeq->unkA0 == 0) || (pSeq->unk8C == pSeq->unkA4)) {
                D_800BDE3C[arg0][arg1].unk90 &= ~0x40;
                D_800BDE3C[arg0][arg1].unk90 &= ~0x80;
            }
        }
    } else {
        if (pSeq->unk8C > pSeq->unkA4) {
            pSeq->unk8C += pSeq->unk44;
            if (pSeq->unk8C < pSeq->unkA4) {
                pSeq->unk8C = pSeq->unkA4;
            }
        } else if (pSeq->unk8C < pSeq->unkA4) {
            pSeq->unk8C -= pSeq->unk44;
            if (pSeq->unk8C > pSeq->unkA4) {
                pSeq->unk8C = pSeq->unkA4;
            }
        }

        pSeq->unk70 = (pSeq->unk4A * pSeq->unk8C * 10) / (VBLANK_MINUS * 60);
        if (pSeq->unk70 <= 0) {
            pSeq->unk70 = 1;
        }
        if ((pSeq->unkA0 == 0) || (pSeq->unk8C == pSeq->unkA4)) {
            D_800BDE3C[arg0][arg1].unk90 &= ~0x40;
            D_800BDE3C[arg0][arg1].unk90 &= ~0x80;
        }
    }
}

extern short D_800B1EA4[];
void SsSetMono(void) {
    D_800B1EA4[0] = 1;
}

extern short D_800B1EA4[];
void SsSetStereo(void) {
    D_800B1EA4[0] = 0;
}

extern u8 D_800B9DE4[];
extern void *D_800BE8F0[];
extern u16 D_800BE8EC[];

void SsVabClose(s16 vabid) {
    if ((vabid >= 0 && vabid < 0x10) && D_800B9DE4[vabid] == 1) {
        SpuFree(D_800BE8F0[vabid]);
        D_800B9DE4[vabid] = 0;
        D_800BE8EC[0] = *(u16 *)((u8 *)D_800BE8F0 - 4) - 1;
    }
}

extern s32 D_800BE930[];
extern s32 SsVabTransBody(u8 *, s16);
s32 SsVabOpen(u8 *addr) {
    s32 result;
    s16 vabid;
    result = SsVabOpenHead(addr, -1);
    vabid = result;
    if (vabid != -1) {
        result = SsVabTransBody((u8 *)D_800BE930[vabid], vabid);
    }
    return (s16)result;
}

extern s32 SsVabOpenHeadWithMode(u8 *, s32, s32, s32);
s32 SsVabOpenHead(addr, vabid)
u8 *addr;
s16 vabid;
{
    return (s16)SsVabOpenHeadWithMode(addr, vabid, 0, 0);
}

s32 SsVabOpenHeadSticky(u_char *addr, u_long vabid, u_long sbaddr) {
    return (s16)SsVabOpenHeadWithMode(addr, (s16)vabid, 1, sbaddr);
}

extern s32 SsVabOpenHeadWithMode(u8 *, s32, s32, s32);
s32 SsVabFakeHead(addr, vabid, sbaddr)
u8 *addr;
s16 vabid;
s32 sbaddr;
{
    return (s16)SsVabOpenHeadWithMode(addr, vabid, 1, sbaddr);
}

extern s32 _spu_getInTransfer(void);

s16 SsVabOpenHeadMode(u8 *, s16, s16, u32) asm("SsVabOpenHeadWithMode");
s16 SsVabOpenHeadMode(u8 *addr, s16 vabid, s16 arg2, u32 sbaddr) {
    s32 vagLens[256];
    s32 i;
    s32 var_s0;
    s16 vabId_2;
    u16 temp_v1;
    u16 *ptr_vag_off_table;
    u32 magic;
    u32 spuAllocMem;
    u8 num_vags;
    ProgAtr *pProgTable;
    u8 *var_a2;
    VabHdr *vab_hdr_2;
    vabId_2 = 0x10;
    if (_spu_getInTransfer() == 1) {
        return -1;
    }
    _spu_setInTransfer(1);
    if (vabid >= 0x10) {
        _spu_setInTransfer(0);
        return -1;
    }
    if (vabid == -1) {
        for (i = 0; i < 16; i++) {
            if (_svm_vab_used[i] == 0) {
                _svm_vab_used[i] = 1;
                vabId_2 = i;
                _svm_vab_count++;
                break;
            }
        }
    } else {
        var_a2 = _svm_vab_used;
        if (var_a2[vabid] == 0) {
            _svm_vab_used[vabid] = 1;
            vabId_2 = vabid;
            _svm_vab_count++;
        }
    }
    if (vabId_2 >= 0x10) {
        _spu_setInTransfer(0);
        return -1;
    }
    var_a2 = addr;
    _svm_vab_vh[vabId_2] = var_a2;

    var_a2 = var_a2 + 0x20;
    vab_hdr_2 = addr;
    magic = vab_hdr_2->form;
    if ((magic >> 8) != ('V' << 0x10 | 'A' << 0x8 | 'B')) {
        _svm_vab_used[vabId_2] = 0;
        _spu_setInTransfer(0);
        _svm_vab_count -= 1;
        return -1;
    }
    if ((magic & 0xFF) == 'p') {
        if (vab_hdr_2->ver >= 5) {
            kMaxPrograms = 0x80;
        } else {
            kMaxPrograms = 0x40;
        }
    } else {
        kMaxPrograms = 0x40;
    }
    if (vab_hdr_2->ps <= kMaxPrograms) {
        _svm_vab_pg[vabId_2] = var_a2;
        pProgTable = var_a2;
        var_a2 = var_a2 + (kMaxPrograms * 0x10);
        var_s0 = 0;
        for (i = 0; i < kMaxPrograms; i++) {
            pProgTable[i].reserved1 = var_s0;
            if (pProgTable[i].tones != 0) {
                var_s0++;
            }
        }
        var_s0 = 0;
        _svm_vab_tn[vabId_2] = var_a2;
        ptr_vag_off_table = var_a2 + (vab_hdr_2->ps << 9);
        num_vags = vab_hdr_2->vs;
        for (i = 0; i < 256; i++) {
            if (num_vags >= i) {
                temp_v1 = *ptr_vag_off_table;
                if (vab_hdr_2->ver >= 5) {
                    vagLens[i] = temp_v1 * 8;
                } else {
                    vagLens[i] = temp_v1 * 4;
                }
                var_s0 += vagLens[i];
            }
            ptr_vag_off_table++;
        }

        _svm_brr_start_addr[vabId_2] = ptr_vag_off_table;
        spuAllocMem = sbaddr;
        if (arg2 == 0) {
            spuAllocMem = SpuMalloc(var_s0);
            if (spuAllocMem == -1) {
                _svm_vab_used[vabId_2] = 0;
                _spu_setInTransfer(0);
                _svm_vab_count -= 1;
                return -1;
            }
        }
        if ((spuAllocMem + var_s0) > 0x80000U) {
        end:
            _svm_vab_used[vabId_2] = 0;

            _spu_setInTransfer(0);
            _svm_vab_count -= 1;
            return -1;
        }
        _svm_vab_start[vabId_2] = spuAllocMem;
        var_s0 = 0;
        for (i = 0; i <= num_vags; i++) {
            var_s0 += vagLens[i];
            if (!(i & 1)) {
                pProgTable[i / 2].reserved2 = (spuAllocMem + var_s0) >> 3;
            } else {
                pProgTable[i / 2].reserved3 = (spuAllocMem + var_s0) >> 3;
            }
        }

        _svm_vab_total[vabId_2] = var_s0;
        _svm_vab_used[vabId_2] = 2;
    } else {
        goto end;
    }
    return vabId_2;
}

extern s32 D_800BE8AC[];
extern s32 SpuSetTransferStartAddr(s32);
extern void _spu_setInTransfer(s32);
s32 SsVabTransBody(u8 *addr, s16 vabId) {
    s32 start;
    if (vabId >= 0 && vabId < 0x11) {
        if (_svm_vab_used[vabId] == 2) {
            start = _svm_vab_start[vabId];
            SpuSetTransferMode(0);
            SpuSetTransferStartAddr(start);
            SpuWrite(addr, _svm_vab_total[vabId]);
            _svm_vab_used[vabId] = 1;
            return vabId;
        }
    }
    _spu_setInTransfer(0);
    return -1;
}

extern s32 SpuIsTransferCompleted(s32);
s32 SsVabTransCompleted(immediateFlag)
s16 immediateFlag;
{
    return (s16)SpuIsTransferCompleted(immediateFlag);
}

/* SPDX-License-Identifier: MIT */

extern u16 D_800AFD98[];

void SpuVmDamperOff(void) {
    D_800AFD98[0] = 0;
}

/* SPDX-License-Identifier: MIT */
extern u16 D_800AFD98[];
void SpuVmDamperOn(void) {
    D_800AFD98[0] = 2;
}

extern u8 D_800B9DE4[];
extern s32 SpuVmVSetUp(s16, s16);
extern volatile u32 gProgramAttrsRead[];
s16 SsUtGetProgAtr(s16 vabId, s16 progNum, u8 *progatrptr) {
    u32 offset;
    if (D_800B9DE4[vabId] == 1) {
        SpuVmVSetUp(vabId, progNum);
        offset = progNum * 16;
        progatrptr[0] = *((u8 *)(offset + gProgramAttrsRead[0]));
        progatrptr[1] = ((u8 *)gProgramAttrsRead[0])[offset + 1];
        progatrptr[2] = ((u8 *)gProgramAttrsRead[0])[offset + 2];
        progatrptr[3] = ((u8 *)gProgramAttrsRead[0])[offset + 3];
        progatrptr[4] = ((u8 *)gProgramAttrsRead[0])[offset + 4];
        *(u16 *)&progatrptr[6] =
            *(u16 *)&((u8 *)gProgramAttrsRead[0])[offset + 6];
        return 0;
    }
    return -1;
}

s32 SpuVmVSetUp(s16 vabId, s16 prog) {
    if (vabId < 0 || vabId >= 16 || _svm_vab_used[vabId] != 1 ||
        prog >= kMaxPrograms) {
        return -1;
    }
    _svm_vh = _svm_vab_vh[vabId];
    _svm_pg = _svm_vab_pg[vabId];
    _svm_tn = _svm_vab_tn[vabId];
    _svm_cur.vabId = vabId;
    _svm_cur.program = prog;
    _svm_cur.fakeProgram = _svm_pg[prog].reserved1;
    return 0;
}

s16 SsUtGetVagAtr(s16 vabId, s16 prog, s16 toneNum, VagAtr *vagatrptr) {
    s16 temp_v1;
    if (_svm_vab_used[vabId] == 1) {
        SpuVmVSetUp(vabId, prog);
        temp_v1 = toneNum + _svm_cur.fakeProgram * 0x10;
        vagatrptr->prior = _svm_tn[temp_v1].prior;
        vagatrptr->mode = _svm_tn[temp_v1].mode;
        vagatrptr->vol = _svm_tn[temp_v1].vol;
        vagatrptr->pan = _svm_tn[temp_v1].pan;
        vagatrptr->center = _svm_tn[temp_v1].center;
        vagatrptr->shift = _svm_tn[temp_v1].shift;
        vagatrptr->max = _svm_tn[temp_v1].max;
        vagatrptr->min = _svm_tn[temp_v1].min;
        vagatrptr->vibW = _svm_tn[temp_v1].vibW;
        vagatrptr->vibT = _svm_tn[temp_v1].vibT;
        vagatrptr->porW = _svm_tn[temp_v1].porW;
        vagatrptr->porT = _svm_tn[temp_v1].porT;
        vagatrptr->pbmin = _svm_tn[temp_v1].pbmin;
        vagatrptr->pbmax = _svm_tn[temp_v1].pbmax;
        vagatrptr->adsr1 = _svm_tn[temp_v1].adsr1;
        vagatrptr->adsr2 = _svm_tn[temp_v1].adsr2;
        vagatrptr->prog = _svm_tn[temp_v1].prog;
        vagatrptr->vag = _svm_tn[temp_v1].vag;
        return 0;
    }

    return -1;
}

extern SpuReverbAttr _svm_rattr;

/* libsnd.h declares this void; retail returns the type or -1. */
s16 SsUtSetReverbTypeS16(s16) asm("SsUtSetReverbType");
s16 SsUtSetReverbTypeS16(s16 arg0) {
    s16 var_v1;
    s32 var_a1;

    var_a1 = 0;
    var_v1 = arg0;
    if (arg0 < 0) {
        var_a1 = 1;
        var_v1 = -arg0;
    }

    if ((u16)var_v1 < 10) {
        _svm_rattr.mask = 1;
        if (var_a1 != 0) {
            _svm_rattr.mode = var_v1 | 0x100;
        } else {
            _svm_rattr.mode = var_v1;
        }
        if (var_v1 == 0) {
            SpuSetReverb(0);
        }
        SpuSetReverbModeParam(&_svm_rattr);
        return var_v1;
    }
    return -1;
}

/* SPDX-License-Identifier: MIT */

extern s16 D_800AE280[];

int SsUtGetReverbType(void) {
    return D_800AE280[0];
}

void func_80082B50(void) {
    SpuSetReverb(1);
}

void func_80082B70(void) {
    SpuSetReverb(0);
}

extern SpuReverbAttr D_800AE27C[];

void SsUtSetReverbFeedback(short feedback) {
    D_800AE27C[0].mask = SPU_REV_FEEDBACK;
    D_800AE27C[0].feedback = feedback;
    SpuSetReverbModeParam(D_800AE27C);
}

void SsUtSetReverbDepth(short ldepth, short rdepth) {
    D_800AE27C[0].mask = 6;
    D_800AE27C[0].depth.left = ldepth * 0x7FFF / 0x7F;
    D_800AE27C[0].depth.right = rdepth * 0x7FFF / 0x7F;
    SpuSetReverbModeParam(D_800AE27C);
}

void SsUtSetReverbDelay(short delay) {
    D_800AE27C[0].mask = SPU_REV_DELAYTIME;
    D_800AE27C[0].delay = delay;
    SpuSetReverbModeParam(D_800AE27C);
}

s16 SsUtSetVagAtr(s16 vabId, s16 prog, s16 toneNum, VagAtr *pVagAttr) {
    s16 toneIndex;
    if (_svm_vab_used[vabId] == 1) {
        SpuVmVSetUp(vabId, prog);
        toneIndex = toneNum + _svm_cur.fakeProgram * 0x10;
        _svm_tn[toneIndex].prior = pVagAttr->prior;
        _svm_tn[toneIndex].mode = pVagAttr->mode;
        _svm_tn[toneIndex].vol = pVagAttr->vol;
        _svm_tn[toneIndex].pan = pVagAttr->pan;
        _svm_tn[toneIndex].center = pVagAttr->center;
        _svm_tn[toneIndex].shift = pVagAttr->shift;
        _svm_tn[toneIndex].max = pVagAttr->max;
        _svm_tn[toneIndex].min = pVagAttr->min;
        _svm_tn[toneIndex].vibW = pVagAttr->vibW;
        _svm_tn[toneIndex].vibT = pVagAttr->vibT;
        _svm_tn[toneIndex].porW = pVagAttr->porW;
        _svm_tn[toneIndex].porT = pVagAttr->porT;
        _svm_tn[toneIndex].pbmin = pVagAttr->pbmin;
        _svm_tn[toneIndex].pbmax = pVagAttr->pbmax;
        _svm_tn[toneIndex].adsr1 = pVagAttr->adsr1;
        _svm_tn[toneIndex].adsr2 = pVagAttr->adsr2;
        _svm_tn[toneIndex].prog = pVagAttr->prog;
        _svm_tn[toneIndex].vag = pVagAttr->vag;
        return 0;
    }
    return -1;
}

/* Picks a free voice for a note, or steals the quietest lowest-priority one.
 * Returns spuVmMaxVoice when none can be used. */
u8 SpuVmAllocVoice(s32) asm("SpuVmAlloc");
u8 SpuVmAllocVoice(s32 arg0) {
    u8 var_t2;
    u16 var_t0;
    u16 var_t3;
    u8 cur_voice;
    u8 channel;
    u8 var_t1;
    u16 prior;

    channel = 99;
    var_t3 = -1;
    var_t2 = 0;
    var_t0 = 0;
    prior = _svm_cur.prior;
    var_t1 = 99;
    for (cur_voice = 0; cur_voice < spuVmMaxVoice; cur_voice++) {
        if (_svm_voice[cur_voice].unk1B == 0 &&
            _svm_voice[cur_voice].unk6 == 0) {
            channel = cur_voice;
            break;
        }
        if (_svm_voice[cur_voice].unk18 < prior) {
            prior = _svm_voice[cur_voice].unk18;
            var_t1 = cur_voice;
            var_t3 = _svm_voice[cur_voice].unk6;
            var_t0 = _svm_voice[cur_voice].unk2;
            var_t2 = 1;
        } else if (_svm_voice[cur_voice].unk18 == prior) {
            var_t2 += 1;
            if (_svm_voice[cur_voice].unk6 < var_t3) {
                var_t0 = _svm_voice[cur_voice].unk2;
                var_t3 = _svm_voice[cur_voice].unk6;
                var_t1 = cur_voice;
            } else if (_svm_voice[cur_voice].unk6 == var_t3) {
                if (var_t0 < _svm_voice[cur_voice].unk2) {
                    var_t0 = _svm_voice[cur_voice].unk2;
                    var_t1 = cur_voice;
                }
            }
        }
    }
    if (channel == 99) {
        if (var_t2 == 0) {
            channel = spuVmMaxVoice;
        } else {
            channel = var_t1;
        }
    }
    if (channel < spuVmMaxVoice) {
        for (cur_voice = 0; cur_voice < spuVmMaxVoice; cur_voice++) {
            _svm_voice[cur_voice].unk2++;
        }
        _svm_voice[channel].unk2 = 0;
        _svm_voice[channel].unk18 = _svm_cur.prior;
        if (_svm_voice[channel].unk1B == 2) {
            SpuSetNoiseVoice(0, 0xFFFFFF);
        }
    }
    return channel;
}

/* Matches (0 words) under GNU C 2.6.3-psx only. Retail's codegen needs these
 * spellings:
 * - pos is a u16 (andi 0xFFFF before the shift);
 * - D_800AD224 is the base of the sreg buffer: the pitch store is index
 *   pos + 2, not D_800AD228 + pos;
 * - D_800B1EA4, not D_800B9DD8, is the mono flag;
 * - the voice flag stores go through D_800AD3C0 and D_800AD3D7, so no
 *   voice-table base is shared;
 * - every mask register is read through one symbol and written through a
 *   neighbour symbol (D_800AD9AC[-2] for D_800AD9A8, and so on). A load
 *   and a store of one constant share a single la, which retail doesn't
 *   have. The "on" masks are written first and the "off" masks last. */
void SpuVmKeyOnNow(vagCount, pitch) u8 vagCount;
u16 pitch;
{
    extern s32 D_800B9930[];
    extern u8 D_800B9DC8[];
    extern u8 D_800B9DCE[];
    extern u8 D_800B9DD1[];
    extern u8 D_800B9DD2[];
    extern u8 D_800B9DCF[];
    extern u8 D_800B9DC9[];
    extern u8 D_800B9DD8[];
    extern s16 D_800B9DDA[];
    extern s16 D_800B9DDE[];
    extern struct SeqStruct *D_800BDE3C[];
    extern u16 D_800AD9A8[];
    extern u16 D_800AD9AC[];
    extern u16 D_800AD96C[];
    extern u16 D_800AD970[];
    extern u16 D_800BEB98[];
    extern u16 D_800BEB9C[];
    extern u8 D_800AD3A4[];
    extern u16 D_800AD224[];
    extern u8 D_800AD3C0[];
    extern u8 D_800AD3D7[];
    extern s16 D_800B1EA4[];
    struct SeqStruct *score;
    u16 pos;
    u16 bitsUpper;
    u16 bitsLower;
    u32 voll;
    u32 volr;
    u32 vollT;
    u32 volrT;
    s32 mvolScaled;

    pos = D_800B9DDE[0] * 8;
    mvolScaled = (*(u8 *)((s32)D_800B9930[0] + 0x18)) * 0x3FFF;
    vollT = ((D_800B9DC8[0] * mvolScaled) / 0x7F) / 0x7F;
    vollT = ((vollT * D_800B9DCE[0] * D_800B9DD1[0]) / 0x7F) / 0x7F;
    volrT = vollT;
    score = D_800BDE3C[D_800B9DDA[0] & 0xFF] + ((D_800B9DDA[0] & 0xFF00) >> 8);
    if (D_800B9DDA[0] != 0x21) {
        vollT = (vollT * score->leftVolume) / 0x7F;
        volrT = (volrT * score->rightVolume) / 0x7F;
    }
    if (D_800B9DD2[0] < 0x40) {
        voll = vollT;
        volr = (volrT * D_800B9DD2[0]) / 0x3F;
    } else {
        voll = (vollT * (0x7F - D_800B9DD2[0])) / 0x3F;
        volr = volrT;
    }
    if (D_800B9DCF[0] < 0x40) {
        volr = (volr * D_800B9DCF[0]) / 0x3F;
    } else {
        voll = (voll * (0x7F - D_800B9DCF[0])) / 0x3F;
    }
    if (D_800B9DC9[0] < 0x40) {
        volr = (volr * D_800B9DC9[0]) / 0x3F;
    } else {
        voll = (voll * (0x7F - D_800B9DC9[0])) / 0x3F;
    }
    if (D_800B1EA4[0] == 1) {
        if (voll < volr) {
            voll = volr;
        } else {
            volr = voll;
        }
    }
    voll = (voll * voll) / 0x3FFF;
    volr = (volr * volr) / 0x3FFF;
    D_800AD224[pos + 2] = pitch;
    D_800AD224[pos + 0] = voll;
    D_800AD224[pos + 1] = volr;
    D_800AD3A4[D_800B9DDE[0]] |= 7;
    *(u16 *)(D_800AD3C0 + D_800B9DDE[0] * 52) = pitch;
    D_800AD3D7[D_800B9DDE[0] * 52] = 1;
    if (D_800B9DDE[0] < 0x10) {
        bitsLower = 1 << D_800B9DDE[0];
        bitsUpper = 0;
    } else {
        bitsLower = 0;
        bitsUpper = 1 << (D_800B9DDE[0] - 0x10);
    }
    if (D_800B9DD8[0] & 4) {
        ((u16 *)D_800AD9AC)[-2] = D_800AD9A8[0] | bitsLower;
        ((u16 *)D_800AD9A8)[2] = D_800AD9AC[0] | bitsUpper;
    } else {
        ((u16 *)D_800AD9AC)[-2] = D_800AD9A8[0] & ~bitsLower;
        ((u16 *)D_800AD9A8)[2] = D_800AD9AC[0] & ~bitsUpper;
    }
    ((u16 *)D_800AD970)[-2] = D_800AD96C[0] | bitsLower;
    ((u16 *)D_800AD96C)[2] = D_800AD970[0] | bitsUpper;
    ((u16 *)D_800BEB9C)[-2] = D_800BEB98[0] & ~((u16 *)D_800AD970)[-2];
    ((u16 *)D_800BEB98)[2] = D_800BEB9C[0] & ~((u16 *)D_800AD96C)[2];
}

void SpuVmDoAllocate(void) {
    s32 i;

    _svm_cur.regOff = _svm_cur.voice * 8;
    _svm_cur.toneOff = _svm_cur.vagIdx + (_svm_cur.fakeProgram * 0x10);
    _svm_voice[_svm_cur.voice].unk6 = 0x7FFF;
    for (i = 0; i < 0x10; i++) {
        _svm_envx_hist[i] &= ~(1 << _svm_cur.voice);
    }
    if ((_svm_cur.voiceIdx & 1) > 0) {
        _svm_sreg_buf[_svm_cur.regOff + 3] =
            _svm_pg[(_svm_cur.voiceIdx - 1) / 2].reserved2;
        _svm_sreg_dirty[_svm_cur.voice] |= 8;
    } else {
        _svm_sreg_buf[_svm_cur.regOff + 3] =
            _svm_pg[(_svm_cur.voiceIdx - 1) / 2].reserved3;
        _svm_sreg_dirty[_svm_cur.voice] |= 8;
    }

    _svm_sreg_buf[_svm_cur.regOff + 4] =
        _svm_tn[(_svm_cur.fakeProgram * 0x10) + _svm_cur.vagIdx].adsr1;
    _svm_sreg_buf[_svm_cur.regOff + 5] =
        _svm_tn[(_svm_cur.fakeProgram * 0x10) + _svm_cur.vagIdx].adsr2 +
        _svm_damper;
    _svm_sreg_dirty[_svm_cur.voice] |= 0x30;
}

void vmNoiseOn(arg0) u8 arg0;
{
    struct SeqStruct *score = &D_800BDE3C[_svm_cur.vagIdx16 & 0xFF]
                                         [(_svm_cur.vagIdx16 & 0xFF00) >> 8];
    s16 voice;
    u16 bitsUpper;
    u16 bitsLower;
    u32 voll_t, volr_t;
    u32 voll, volr;
    u16 cnd;
    u32 temp;

    cnd = _svm_spuBase[0x1AA / 2];

    voll_t = score->leftVolume * 0x81;
    volr_t = score->rightVolume * 0x81;

    voll_t = (voll_t * _svm_cur.mvol) / 0x7F;
    volr_t = (volr_t * _svm_cur.mvol) / 0x7F;

    voll_t = (voll_t * _svm_cur.vol) / 0x7F;
    volr_t = (volr_t * _svm_cur.vol) / 0x7F;

    temp = _svm_cur.pan;
    if (temp < 0x40) {
        voll = voll_t;
        volr = (volr_t * temp) / 0x3F;
    } else {
        voll = (voll_t * (0x7F - temp)) / 0x3F;
        volr = volr_t;
    }
    temp = _svm_cur.mpan;
    if (temp < 0x40) {
        volr = (volr * temp) / 0x3F;
    } else {
        voll = (voll * (0x7F - temp)) / 0x3F;
    }
    temp = _svm_cur.field5;
    if (temp < 0x40) {
        volr = (temp * volr) / 0x3F;
    } else {
        voll = (voll * (0x7F - temp)) / 0x3F;
    }

    if (_svm_stereo_mono == 1) {
        if (voll < volr) {
            voll = volr;
        } else {
            volr = voll;
        }
    }

    cnd &= ~0x3F00;
    cnd |= ((_svm_cur.note - _svm_cur.centre) & 0x3F) << 8;
    _svm_spuBase[0x1AA / 2] = cnd;

    _svm_sreg_buf[arg0 * 8 + 0] = voll;
    _svm_sreg_buf[arg0 * 8 + 1] = volr;
    _svm_sreg_dirty[arg0] |= 3;
    if (arg0 < 0x10) {
        bitsLower = 1 << arg0;
        bitsUpper = 0;
    } else {
        bitsLower = 0;
        bitsUpper = 1 << (arg0 - 0x10);
    }
    _svm_voice[arg0].unk4 = 0xA;
    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        _svm_voice[voice].unk1B &= 1;
    }
    _svm_voice[arg0].unk1B = 2;

    _svm_okon1 |= bitsLower;
    _svm_okon2 |= bitsUpper;

    _svm_okof1 &= ~_svm_okon1;
    _svm_okof2 &= ~_svm_okon2;

    if (_svm_cur.seqSepNo & 4) {
        _svm_orev1 |= bitsLower;
        _svm_orev2 |= bitsUpper;
    } else {
        _svm_orev1 &= ~bitsLower;
        _svm_orev2 &= ~bitsUpper;
    }

    _svm_spuBase[0x194 / 2] = bitsLower;
    _svm_spuBase[0x196 / 2] = bitsUpper;
}

void vmNoiseOn2Impl(u8, u16, u16, u16, u16) asm("vmNoiseOn2");
void vmNoiseOn2Impl(u8 voice, u16 arg1, u16 arg2, u16 arg3, u16 arg4) {
    u16 i;
    u16 bitsUpper;
    u16 bitsLower;

    _svm_sreg_buf[voice * 8 + 0] = arg1;
    _svm_sreg_buf[voice * 8 + 1] = arg2;
    _svm_sreg_dirty[voice] |= 3;

    if (voice < 0x10) {
        bitsLower = 1 << voice;
        bitsUpper = 0;
    } else {
        bitsLower = 0;
        bitsUpper = 1 << (voice - 0x10);
    }

    _svm_voice[voice].unk4 = 0xA;
    for (i = 0; i < spuVmMaxVoice; i++) {
        _svm_voice[i].unk1B &= 1;
    }
    _svm_voice[voice].unk1B = 2;
    _svm_voice[voice].unk2 = 0;

    _svm_okon1 |= bitsLower;
    _svm_okon2 |= bitsUpper;

    _svm_okof1 &= ~_svm_okon1;
    _svm_okof2 &= ~_svm_okon2;
    _svm_spuBase[0x194 / 2] = bitsLower;
    _svm_spuBase[0x196 / 2] = bitsUpper;
}

extern u8 D_800B9DC6[];
extern u8 D_800B9DD4[];
extern u8 D_800B9DD5[];
extern u16 D_800A20BC[];
u16 note2pitch(void) {
    s16 new_var;
    s16 octave;
    s16 pos;
    u16 var_a2;
    u16 var_v1;
    new_var = ((u8)_svm_cur.note + 60) - (u8)_svm_cur.centre;
    octave = new_var / 12;
    pos = new_var % 12;
    var_a2 = _svm_cur.shift / 8;
    if (var_a2 > 15) {
        var_a2 = 15;
    }
    var_v1 = D_800A20BC[(pos * 16) + var_a2];
    do {
        octave -= 5;
        if (octave > 0) {
            var_v1 <<= octave;
        } else if (octave < 0) {
            var_v1 >>= -octave;
        }
    } while (0);
    return var_v1;
}

extern u8 D_800B9DCB[];
extern u8 D_800B9DD0[];
extern u8 D_800B9950Raw[] asm("D_800B9950");
extern u16 D_800A20BC[];
s32 note2pitch2(arg0, arg1)
u16 arg0;
u16 arg1;
{
    s32 pos;
    s16 new_var;
    s16 var_a3;
    s16 var_a2;
    s16 octave;
    u16 var_v1;
    var_a3 =
        (arg1 +
         ((u8 *)*(u32 *)
              D_800B9950Raw)[(D_800B9DD0[0] + (D_800B9DCB[0] << 4)) * 0x20 +
                             5]) /
        8;
    var_a2 = 0;
    if (var_a3 >= 16) {
        var_a2 = 1;
        var_a3 -= 16;
    }
    new_var =
        arg0 + 60 -
        ((u8 *)*(u32 *)
             D_800B9950Raw)[(D_800B9DD0[0] + (D_800B9DCB[0] << 4)) * 0x20 + 4] +
        var_a2;
    octave = new_var / 12;
    pos = (new_var % 12) * 16;
    var_v1 = D_800A20BC[pos + var_a3];
    octave -= 5;
    if (octave > 0)
        var_v1 <<= octave;
    else if (octave < 0)
        var_v1 >>= -octave;
    return var_v1;
}

void SePitchBend(u8 voice, s16 arg1) {
    extern u8 D_800AD3CC[];
    extern u8 D_800AD3D0[];
    extern u16 D_800AD3C8[];
    extern u8 D_800AD3A4[];
    extern u8 D_800B9DCB[];
    extern u8 D_800B9DD0[];
    extern u16 D_800B9DDE[];
    extern u32 D_800B9950[];
    extern u16 D_800AD224[];
    extern s32 note2pitch2();
    s32 tone;
    u16 note;
    u16 pbend;
    s32 pos;

    pos = voice * 8;
    if (voice >= 0 && voice < 24) {
        D_800B9DCB[0] = D_800AD3CC[(s32)voice * 52];
        D_800B9DD0[0] = D_800AD3D0[(s32)voice * 52];
        D_800B9DDE[0] = voice;
        tone = D_800B9DCB[5] + D_800B9DCB[0] * 16;
        if (arg1 >= 0) {
            note =
                D_800AD3C8[(s32)voice * 26] +
                (arg1 * *(u8 *)((s32)D_800B9950[0] + tone * 32 + 0xD)) / 0x7F;
            pbend =
                (arg1 * *(u8 *)((s32)D_800B9950[0] + tone * 32 + 0xD)) % 0x7F;
        } else {
            note = (D_800AD3C8[(s32)voice * 26] +
                    (arg1 * *(u8 *)((s32)D_800B9950[0] + tone * 32 + 0xC)) /
                        0x7F) -
                   1;
            pbend = ((arg1 * *(u8 *)((s32)D_800B9950[0] + tone * 32 + 0xC)) /
                     0x7F) +
                    0x7F;
        }
        D_800AD224[pos + 2] = note2pitch2(note, pbend);
        D_800AD3A4[voice] |= 4;
    }
}

void SsUtVibrateOn(void) {
}

void SsUtVibrateOff(void) {
}

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s8 unk18[0x1C];
} AutoSweep;

extern AutoSweep D_800AD3D8[];

void SeAutoVol(s16 seq_access, s16 vol1, s16 vol2, s16 mSec) {
    s32 m;
    s32 q;

    if (vol1 != vol2) {
        D_800AD3D8[seq_access].unk0 = 1;
        D_800AD3D8[seq_access].unk8 = vol1;
        D_800AD3D8[seq_access].unkA = vol2;
        m = mSec;
        if (vol1 - vol2 >= 0) {
            if (vol1 - vol2 < m) {
                goto fast;
            }
            goto slow;
        }
        if (vol2 - vol1 < m) {
        fast:
            q = mSec / (vol1 - vol2);
            D_800AD3D8[seq_access].unk2 = 1;
            D_800AD3D8[seq_access].unk4 = q;
            D_800AD3D8[seq_access].unk6 = q;
            return;
        }
    slow:
        D_800AD3D8[seq_access].unk4 = 0;
        D_800AD3D8[seq_access].unk2 = (vol1 - vol2) / mSec;
    }
}

void SetAutoVol(s16 voice) {
    s16 temp_v1_3;
    u32 voll_t, volr_t;
    u16 voll, volr;
    s16 pos;
    s32 mvol_scaled;

    pos = voice * 8;
    if (_svm_voice[voice].unk20 != 0) {
        if (_svm_voice[voice].unk22-- > 0) {
            return;
        }
        _svm_voice[voice].unk22 = _svm_voice[voice].unk20;
    }
    _svm_voice[voice].startVol += _svm_voice[voice].unk1E;
    if (_svm_voice[voice].unk1E > 0) {
        if (_svm_voice[voice].startVol >= _svm_voice[voice].endVol) {
            _svm_voice[voice].startVol = _svm_voice[voice].endVol;
            _svm_voice[voice].autoVol = 0;
        }
    } else if (_svm_voice[voice].unk1E < 0) {
        if (_svm_voice[voice].startVol <= _svm_voice[voice].endVol) {
            _svm_voice[voice].startVol = _svm_voice[voice].endVol;
            _svm_voice[voice].autoVol = 0;
        }
    }
    temp_v1_3 = _svm_voice[voice].startVol;
    _svm_cur.voll = temp_v1_3;
    mvol_scaled = _svm_vh->mvol * 0x3FFF;

    voll_t = ((temp_v1_3 * mvol_scaled) / 0x7F) / 0x7F;
    volr_t = ((temp_v1_3 * mvol_scaled) / 0x7F) / 0x7F;

    voll_t = ((voll_t * _svm_cur.mvol * _svm_cur.vol) / 0x7F) / 0x7F;
    volr_t = ((volr_t * _svm_cur.mvol * _svm_cur.vol) / 0x7F) / 0x7F;

    if (_svm_cur.pan < 0x40) {
        voll = voll_t;
        volr = (volr_t * _svm_cur.pan) / 0x40;
    } else {
        voll = (voll_t * (0x7F - _svm_cur.pan)) / 0x40;
        volr = volr_t;
    }

    if (_svm_cur.mpan < 0x40) {
        volr = (volr * _svm_cur.mpan) / 0x40;
    } else {
        voll = (voll * (0x7F - _svm_cur.mpan)) / 0x40;
    }

    if (_svm_cur.field5 < 0x40) {
        volr = (volr * _svm_cur.field5) / 0x40;
    } else {
        voll = (voll * (0x7F - _svm_cur.field5)) / 0x40;
    }

    if (_svm_stereo_mono == 1) {
        if (volr > voll) {
            voll = volr;
        } else {
            volr = voll;
        }
    }
    _svm_sreg_buf[pos + 0] = voll;
    _svm_sreg_buf[pos + 1] = volr;
    _svm_sreg_dirty[voice] |= 3;
}

void SeAutoPan(s16 seq_access, s16 pan1, s16 pan2, s16 mSec) {
    s32 m;
    s32 q;

    if (pan1 != pan2) {
        D_800AD3D8[seq_access].unkC = 1;
        D_800AD3D8[seq_access].unk14 = pan1;
        D_800AD3D8[seq_access].unk16 = pan2;
        m = mSec;
        if (pan1 - pan2 >= 0) {
            if (pan1 - pan2 < m) {
                goto fast;
            }
            goto slow;
        }
        if (pan2 - pan1 < m) {
        fast:
            q = mSec / (pan1 - pan2);
            D_800AD3D8[seq_access].unkE = 1;
            D_800AD3D8[seq_access].unk10 = q;
            D_800AD3D8[seq_access].unk12 = q;
            return;
        }
    slow:
        D_800AD3D8[seq_access].unk10 = 0;
        D_800AD3D8[seq_access].unkE = (pan1 - pan2) / mSec;
    }
}

void SetAutoPan(s16 voice) {
    u32 voll_t, volr_t;
    u16 voll, volr;
    s16 pos;
    char new_var;
    u16 new_var2;
    s32 mvol_scaled;

    pos = voice * 8;
    if (_svm_voice[voice].unk2C != 0) {
        if (_svm_voice[voice].unk2E-- > 0) {
            return;
        }
        _svm_voice[voice].unk2E = _svm_voice[voice].unk2C;
    }
    _svm_voice[voice].startPan += _svm_voice[voice].unk2A;
    if (_svm_voice[voice].unk2A > 0) {
        if (_svm_voice[voice].startPan >= _svm_voice[voice].endPan) {
            _svm_voice[voice].startPan = _svm_voice[voice].endPan;
            _svm_voice[voice].autoPan = 0;
        }
    } else if (_svm_voice[voice].unk2A < 0) {
        if (_svm_voice[voice].startPan <= _svm_voice[voice].endPan) {
            _svm_voice[voice].startPan = _svm_voice[voice].endPan;
            _svm_voice[voice].autoPan = 0;
        }
    }
    new_var = _svm_voice[voice].startPan;
    _svm_cur.field5 = new_var;
    mvol_scaled = _svm_vh->mvol * 0x3FFF;

    voll_t = ((_svm_cur.voll * mvol_scaled) / 0x7F) / 0x7F;
    volr_t = ((_svm_cur.voll * mvol_scaled) / 0x7F) / 0x7F;

    voll_t = ((voll_t * _svm_cur.mvol * _svm_cur.vol) / 0x7F) / 0x7F;
    volr_t = ((volr_t * _svm_cur.mvol * _svm_cur.vol) / 0x7F) / 0x7F;

    if (_svm_cur.pan < 0x40) {
        voll = voll_t;
        volr = (volr_t * _svm_cur.pan) / 0x40;
    } else {
        voll = (voll_t * (0x7F - _svm_cur.pan)) / 0x40;
        volr = volr_t;
    }

    if (_svm_cur.mpan < 0x40) {
        volr = (volr * _svm_cur.mpan) / 0x40;
    } else {
        voll = (voll * (0x7F - _svm_cur.mpan)) / 0x40;
    }
    new_var2 = new_var;
    if (new_var2 < 0x40) {
        volr = (volr * new_var2) / 0x40;
    } else {
        voll = (voll * (0x7F - new_var2)) / 0x40;
    }

    if (_svm_stereo_mono == 1) {
        if (volr > voll) {
            voll = volr;
        } else {
            volr = voll;
        }
    }
    _svm_sreg_buf[pos + 0] = voll;
    _svm_sreg_buf[pos + 1] = volr;
    _svm_sreg_dirty[voice] |= 3;
}

void SpuVmInit(u8 arg0) {
    u16 temp_v1;
    u16 var_a1;
    u16 *temp_a0;
    s32 var_a0;
    u16 bitsUpper;
    u16 bitsLower;
    u16 temp;
    _spu_setInTransfer(0);
    _svm_vcf = 0;
    _svm_damper = 0;
    SpuInitMalloc(0x20, _ss_spu_vm_rec);
    for (var_a1 = 0; var_a1 < 8 * 24; var_a1++) {
        _svm_sreg_buf[var_a1] = 0;
    }
    for (var_a1 = 0; var_a1 < 24; var_a1++) {
        _svm_sreg_dirty[var_a1] = 0;
    }

    _svm_vab_count = 0;

    for (var_a1 = 0; var_a1 < 16; var_a1++) {
        _svm_vab_used[var_a1] = 0;
    }

    var_a0 = arg0;
    if (arg0 >= 24) {
        spuVmMaxVoice = 24;
    } else {
        spuVmMaxVoice = var_a0;
    }
    for (var_a1 = 0; var_a1 < spuVmMaxVoice; var_a1++) {
        temp = var_a1 * 8;
        _svm_voice[var_a1].unk2 = 0x18;
        _svm_voice[var_a1].unkE = -1;
        _svm_voice[var_a1].unk0 = 0xFF;
        _svm_voice[var_a1].unk1B = 0;
        _svm_voice[var_a1].unk4 = 0;
        _svm_voice[var_a1].unk6 = 0;
        _svm_voice[var_a1].unk10 = 0;
        _svm_voice[var_a1].prog = 0;
        _svm_voice[var_a1].tone = 0xff;
        _svm_voice[var_a1].unk8 = 0;
        _svm_voice[var_a1].unkA = 0x40;
        _svm_voice[var_a1].autoVol = 0;
        _svm_voice[var_a1].unk1E = 0;
        _svm_voice[var_a1].unk20 = 0;
        _svm_voice[var_a1].unk22 = 0;
        _svm_voice[var_a1].autoPan = 0;
        _svm_voice[var_a1].unk2A = 0;
        _svm_voice[var_a1].unk2C = 0;
        _svm_voice[var_a1].unk2E = 0;
        _svm_voice[var_a1].startPan = 0;
        _svm_voice[var_a1].startVol = 0;

        temp_a0 = &_svm_spuBase[temp];
        temp_a0[3] = 0x200;
        temp_a0[2] = 0x1000;
        temp_a0[4] = 0x80FF;
        temp_a0[0] = 0;
        temp_a0[1] = 0;
        temp_a0[5] = 0x4000;

        _svm_cur.voice = var_a1;
        temp_v1 = GetSvmVoice();
        if (temp_v1 < 0x10) {
            bitsLower = 1 << temp_v1;
            bitsUpper = 0;
        } else {
            bitsLower = 0;
            bitsUpper = 1 << (temp_v1 - 0x10);
        }

        _svm_voice[temp_v1].unk1B = 0;
        _svm_voice[temp_v1].unk4 = 0;
        _svm_voice[temp_v1].unk0 = 0;

        _svm_okof1 |= bitsLower;
        _svm_okof2 |= bitsUpper;

        _svm_okon1 &= ~_svm_okof1;
        _svm_okon2 &= ~_svm_okof2;
    }
    _svm_rattr.depth.left = 0x3FFF;
    _svm_rattr.depth.right = 0x3FFF;
    _svm_okon1 = 0;
    _svm_okon2 = 0;
    _svm_okof1 = 0;
    _svm_orev1 = 0;
    _svm_orev2 = 0;
    _svm_rattr.mask = 0;
    _svm_rattr.mode = 0;
    _svm_auto_kof_mode = 0;
    _svm_stereo_mono = 0;
    kMaxPrograms = 0x80;
    SpuVmFlush();
}

extern u8 D_800B9DD3[];
extern u8 D_800B9C80[];
typedef struct SpuVmVoiceSlot {
    u16 voice;
    s32 padding[2];
} SpuVmVoiceSlot;
extern SpuVmVoiceSlot D_800B9DDERead;
extern SpuVmVoiceSlot D_800B9DDEWrite;
extern s32 SpuVmAlloc();
extern s32 vmNoiseOn2(s32, s32, s32, s32, s32);
void SpuVmNoiseOnWithAdsr(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 voice;
    D_800B9DD3[0] = 0x7F;
    voice = SpuVmAlloc(0xFF);
    voice &= 0xFF;
    D_800B9DDEWrite.voice = voice;
    if (voice < D_800B9C80[0]) {
        vmNoiseOn2(*(u8 *)&D_800B9DDERead.voice, arg0 & 0xFFFF, arg1 & 0xFFFF,
                   arg2 & 0xFFFF, arg3 & 0xFFFF);
    }
}

extern u8 D_800B9C80Start[];
extern u8 D_800B9C80Loop[];
extern u8 D_800AD3D7Read[];
extern u8 D_800AD3D7Write[];
extern u8 D_800AD3C0Write[];
typedef struct SpuPointerStorage {
    u32 pointer;
    s32 padding[2];
} SpuPointerStorage;
extern SpuPointerStorage D_800A20B8Read;
void SpuVmNoiseOff(void) {
    s32 status;
    s16 i;
    s32 index;
    u16 *spu;
    i = 0;
    if (D_800B9C80Start[0] == 0) {
        return;
    }
    status = 2;
again:
    if (D_800AD3D7Read[(s32)i * 52] == status) {
        index = (u8)i * 52;
        D_800AD3D7Write[index] = 0;
        spu = (u16 *)D_800A20B8Read.pointer;
        *(u16 *)(D_800AD3C0Write + index) = 0;
        spu[0x194 / 2] = 0;
        spu[0x196 / 2] = 0;
    }
    i++;
    if (i < D_800B9C80Loop[0]) {
        goto again;
    }
}

extern u8 D_800B9DD3[];
extern u8 D_800B9C80[];
extern SpuVmVoiceSlot D_800B9DDERead;
extern SpuVmVoiceSlot D_800B9DDEWrite;
extern s32 SpuVmAlloc();
extern s32 vmNoiseOn2(s32, s32, s32, s32, s32);
void SpuVmNoiseOn(s32 arg0, s32 arg1) {
    s32 voice;
    D_800B9DD3[0] = 0x7F;
    voice = SpuVmAlloc(0xFF);
    voice &= 0xFF;
    D_800B9DDEWrite.voice = voice;
    if (voice < D_800B9C80[0]) {
        vmNoiseOn2(*(u8 *)&D_800B9DDERead.voice, arg0 & 0xFFFF, arg1 & 0xFFFF,
                   0x80FF, 0x5FC8);
    }
}

s16 SpuVmPBVoiceDraft(s16, s16, s16, s16, u16) asm("SpuVmPBVoice");
s16 SpuVmPBVoiceDraft(s16 voice, s16 seq_sep_no, s16 vabId, s16 program,
                      u16 amount) {
    struct SpuVoice {
        s16 unk0;
        s16 unk2;
        s16 unk04;
        u16 unk6;
        s16 unk8;
        char unka;
        char unkb;
        s16 note;
        s16 unke;
        s16 unk10;
        s16 prog;
        s16 tone;
        s16 vabId;
        s16 unk18;
        u8 pad[1];
        u8 unk1b;
        s16 tail[12];
    };
    extern u8 D_800AD3BC[];
    extern u8 D_800B9DCB[];
    extern u16 D_800B9DDE[];
    extern u8 D_800B9DD0[];
    extern u16 D_800AD224[];
    extern u8 D_800AD3C8[];
    extern u8 D_800AD3CA[];
    extern u8 D_800AD3CE[];
    extern u8 D_800AD3D0[];
    extern u8 D_800AD3D2[];
    extern u8 D_800AD3A4[];
    extern s32 D_800B9950[];
    extern s32 note2pitch2();
    struct SpuVoice *voiceData;
    s16 temp_t1;
    u16 temp_v1;
    u16 pbend;
    u16 temp_a1;
    u16 note;

    voiceData = (struct SpuVoice *)D_800AD3BC;
    temp_t1 = amount - 0x40;
    if (*(s16 *)(D_800AD3CA + voice * 52) == seq_sep_no &&
        *(s16 *)(D_800AD3D2 + voice * 52) == vabId &&
        *(s16 *)(D_800AD3CE + voice * 52) == program) {
        temp_a1 = *(u16 *)(D_800AD3C8 + voice * 52);
        temp_v1 = *(u16 *)(D_800AD3D0 + voice * 52) + (D_800B9DCB[0] * 0x10);
        if (temp_t1 > 0) {
            do {
                note = *(u16 *)(D_800AD3C8 + voice * 52) +
                       ((temp_t1 *
                         *(u8 *)((s32)D_800B9950[0] + temp_v1 * 32 + 0xD)) /
                        0x3F);
            } while (0);
            pbend =
                ((temp_t1 * *(u8 *)((s32)D_800B9950[0] + temp_v1 * 32 + 0xD)) %
                 0x3F) *
                2;
        } else {
            note = temp_a1;
            if (temp_t1 < 0) {
                note = ((temp_t1 *
                         *(u8 *)((s32)D_800B9950[0] + temp_v1 * 32 + 0xC)) /
                        0x40);
                note = (temp_a1 + note) - 1;
                pbend = (((temp_t1 *
                           *(u8 *)((s32)D_800B9950[0] + temp_v1 * 32 + 0xC)) %
                          0x40) *
                         2) +
                        0x7F;
            } else {
                pbend = 0;
            }
        }
        D_800B9DD0[0] = D_800AD3D0[voice * 52];
        D_800B9DDE[0] = voice;
        D_800AD224[voice * 8 + 2] = note2pitch2(note, pbend);
        D_800AD3A4[voice] |= 4;
        return 1;
    }
    return 0;
}

s32 SpuVmPBVoice(s16, s16, s16, s16, u16);

/* `seq` is retail's copy of arg0 for the vagIdx16 store. The
 * `(x << 4) & 0xF` terms are ghost uses (combine folds them to zero) that
 * set allocation priority: `voice` gets s0, the sum outranks arg0, and the
 * extra use of `(s16)arg0` makes loop.c hoist its `<< 16` out of the loop. */
s32 SpuVmPitchBend(arg0, arg1, arg2, arg3)
s32 arg0;
s16 arg1;
s16 arg2;
s16 arg3;
{
    s16 voice;
    s32 var_s1;
    s16 seq;

    seq = arg0;
    SpuVmVSetUp(arg1, arg2);
    _svm_cur.vagIdx16 = seq;
    var_s1 = 0;
    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        var_s1 += (s16)SpuVmPBVoice(voice + ((voice << 4) & 0xF),
                                    (s16)arg0 + (((s16)arg0 << 4) & 0xF), arg1,
                                    arg2, arg3) +
                  ((var_s1 << 4) & 0xF);
    }
    return var_s1;
}

void SpuVmFlush(void) {
    u32 env_mask;
    s32 i;

    _svm_envx_idx = (_svm_envx_idx + 1) & 0xF;
    _svm_envx_hist[_svm_envx_idx] = 0;

    for (i = 0; i < spuVmMaxVoice; i++) {
        _svm_voice[i].unk6 = _svm_spuBase[i * 8 + 6];
        if (_svm_voice[i].unk6 == 0) {
            _svm_envx_hist[_svm_envx_idx] |= 1 << i;
        }
    }
    if (_svm_auto_kof_mode == 0) {
        env_mask = 0xFFFFFFFF;
        for (i = 0; i < 0xF; i++) {
            env_mask &= _svm_envx_hist[i];
        }

        for (i = 0; i < spuVmMaxVoice; i++) {
            if (env_mask & (1 << i)) {
                if (_svm_voice[i].unk1B == 2) {
                    SpuSetNoiseVoice(0, 0xFFFFFF);
                }
                _svm_voice[i].unk1B = 0;
            }
        }
    }

    _svm_okon1 &= ~_svm_okof1;
    _svm_okon2 &= ~_svm_okof2;
    for (i = 0; i < 24; i++) {
        if (_svm_voice[i].autoVol != 0) {
            SetAutoVol(i);
        }
        if (_svm_voice[i].autoPan != 0) {
            SetAutoPan(i);
        }
    }

    for (i = 0; i < 24; i++) {
        if (_svm_sreg_dirty[i] & 1) {
            _svm_spuBase[i * 8 + 0] = _svm_sreg_buf[i * 8 + 0];
            _svm_spuBase[i * 8 + 1] = _svm_sreg_buf[i * 8 + 1];
        }
        if (_svm_sreg_dirty[i] & 4) {
            _svm_spuBase[i * 8 + 2] = _svm_sreg_buf[i * 8 + 2];
        }
        if (_svm_sreg_dirty[i] & 8) {
            _svm_spuBase[i * 8 + 3] = _svm_sreg_buf[i * 8 + 3];
        }
        if (_svm_sreg_dirty[i] & 0x10) {
            _svm_spuBase[i * 8 + 4] = _svm_sreg_buf[i * 8 + 4];
            _svm_spuBase[i * 8 + 5] = _svm_sreg_buf[i * 8 + 5];
        }
        _svm_sreg_dirty[i] = 0;
    }

    _svm_spuBase[0x18C / 2] = _svm_okof1;
    _svm_spuBase[0x18E / 2] = _svm_okof2;
    _svm_spuBase[0x188 / 2] = _svm_okon1;
    _svm_spuBase[0x18A / 2] = _svm_okon2;
    _svm_spuBase[0x198 / 2] = _svm_orev1;
    _svm_spuBase[0x19A / 2] = _svm_orev2;
    _svm_okof1 = 0;
    _svm_okof2 = 0;
    _svm_okon1 = 0;
    _svm_okon2 = 0;
}

struct KeyState {
    u8 toneCount;
    u8 vabId;
    u8 note;
    u8 fine;
    u8 volume;
    u8 pan;
    u8 prog;
    u8 fakeProg;
    u8 unk8[2];
    u8 progVolume;
    u8 progPan;
    u8 tone;
    u8 toneVolume;
    u8 tonePan;
    u8 priority;
    u8 center;
    u8 shift;
    u8 minNote;
    u8 maxNote;
    u8 mode;
    u8 unk15;
    s16 seq;
    u16 vag;
    s16 voice;
};
s32 SpuVmKeyOn(seq, vabId, prog, note, volume, pan)
s16 seq;
s16 vabId;
s16 prog;
u16 note;
u16 volume;
u16 pan;
{

    extern struct KeyState keyState[] asm("D_800B9DC4");
    extern s16 D_800B9DDA[];
    extern u8 D_800B9DC6[];
    extern u8 D_800B9DC7[];
    extern u8 D_800B9DC8[];
    extern u8 D_800B9DC9[];
    extern u8 D_800B9DCE[];
    extern u8 D_800B9DCF[];
    extern u8 D_800B9DC4[];
    extern u8 keyToneCountRead[] asm("D_800B9DC4");
    extern u8 D_800B9DCB[];
    extern u8 D_800B9928[];
    extern u8 D_800B9930[];
    extern u8 D_800B9950[];
    extern u8 D_800B9C80[];
    extern u8 D_800AD3BC[];
    extern u8 D_800AD3BE[];
    extern u8 D_800AD3C4[];
    extern u8 D_800AD3C6[];
    extern u8 D_800AD3C8[];
    extern u8 D_800AD3CA[];
    extern u8 D_800AD3CC[];
    extern u8 D_800AD3CE[];
    extern u8 D_800AD3D0[];
    extern u8 D_800AD3D2[];
    extern u8 D_800AD3D4[];
    extern u8 D_800AD3D7[];
    extern s32 SpuVmAlloc();
    extern s32 keyOff(s16, s16, s16, u16) asm("SpuVmKeyOff");
    extern void vmNoiseOn();
    u8 vags[128];
    u8 tones[128];
    s32 mask;
    u8 tone;
    s32 count;
    u32 vagCount;
    u8 i;
    s16 voice;
    s32 selected;
    s32 oldCount;
    u8 *progAttr;
    u8 *vagList;
    u8 *toneList;
    u8 *toneAttr;
    u8 *selectedTone;
    u8 *voiceLimit;
    struct SeqStruct *score;

    mask = 0;
    score = &D_800BDE3C[seq & 0xFF][(seq >> 8) & 0xFF];
    if (SpuVmVSetUp(vabId, prog) != 0) {
        return -1;
    }
    D_800B9DDA[0] = seq;
    D_800B9DC6[0] = note;
    D_800B9DC7[0] = 0;
    if (seq == 0x21) {
        D_800B9DC8[0] = volume;
    } else {
        D_800B9DC8[0] = volume * score->vol[score->channel] / 127;
    }
    D_800B9DC9[0] = pan;
    progAttr = (u8 *)(prog * 16 + *(s32 *)D_800B9928);
    D_800B9DCE[0] = progAttr[1];
    D_800B9DCF[0] = progAttr[4];
    D_800B9DC4[0] = progAttr[0];
    if (D_800B9DCB[0] >= *(u16 *)(*(u8 **)D_800B9930 + 0x12)) {
        return -1;
    }
    if (volume == 0) {
        mask = keyOff(seq, vabId, prog, note & 0xFFFF);
    } else {
        count = 0;
        toneList = tones;
        vagList = vags;
        tone = 0;
        if (tone >= keyToneCountRead[0]) {
            goto tonesDone;
        }
    findTone:
        {
            toneAttr =
                (u8 *)(((D_800B9DCB[0] * 16 + tone) << 5) + *(s32 *)D_800B9950);
            if (toneAttr[6] <= D_800B9DC6[0] && toneAttr[7] >= D_800B9DC6[0]) {
                selected = (u8)count;
                oldCount = count;
                count++;
                vagList[selected] = toneAttr[0x16];
                toneList[(u8)oldCount] = tone;
            }
        }
        do {
            tone++;
            if (tone < D_800B9DC4[0]) {
                goto findTone;
            }
        } while (0);
    tonesDone:
        {
            /* Keep the count in v0 for the copy and first loop test. */
            register u32 narrowedCount asm("v0");
            narrowedCount = (u8)count;
            vagCount = narrowedCount;
            asm("" : "=r"(narrowedCount) : "0"(narrowedCount));
            i = 0;
            if (narrowedCount != 0) {
                do {
                    keyState[0].vag = vags[(u8)i];
                    keyState[0].tone = tones[(u8)i];
                    selectedTone =
                        (u8 *)(((keyState[0].tone + keyState[0].fakeProg * 16)
                                << 5) +
                               *(s32 *)D_800B9950);
                    keyState[0].priority = selectedTone[0];
                    keyState[0].toneVolume = selectedTone[2];
                    keyState[0].tonePan = selectedTone[3];
                    keyState[0].center = selectedTone[4];
                    voiceLimit = D_800B9C80;
                    keyState[0].shift = selectedTone[5];
                    keyState[0].mode = selectedTone[1];
                    keyState[0].minNote = selectedTone[6];
                    keyState[0].maxNote = selectedTone[7];
                    voice = (u8)SpuVmAlloc(0);
                    keyState[0].voice = voice;
                    if (voice < voiceLimit[0]) {
                        D_800AD3D7[voice * 52] = 1;
                        *(s16 *)(D_800AD3BE + keyState[0].voice * 52) = 0;
                        *(s16 *)(D_800AD3CA + keyState[0].voice * 52) = seq;
                        *(s16 *)(D_800AD3D2 + keyState[0].voice * 52) =
                            keyState[0].vabId;
                        *(s16 *)(D_800AD3CC + keyState[0].voice * 52) =
                            keyState[0].fakeProg;
                        *(s16 *)(D_800AD3CE + keyState[0].voice * 52) = prog;
                        if (seq != 0x21) {
                            *(s16 *)(D_800AD3C4 + keyState[0].voice * 52) =
                                volume;
                        }
                        D_800AD3C6[keyState[0].voice * 52] = pan;
                        *(s16 *)(D_800AD3D0 + keyState[0].voice * 52) =
                            keyState[0].tone;
                        *(s16 *)(D_800AD3C8 + keyState[0].voice * 52) = note;
                        *(s16 *)(D_800AD3D4 + keyState[0].voice * 52) =
                            keyState[0].priority;
                        *(u16 *)(D_800AD3BC + keyState[0].voice * 52) =
                            keyState[0].vag;
                        SpuVmDoAllocate();
                        if ((s16)keyState[0].vag == 0xFF) {
                            vmNoiseOn(*(u8 *)&keyState[0].voice);
                        } else {
                            SpuVmKeyOnNow((u8)vagCount, (u16)note2pitch());
                        }
                        mask |= 1 << keyState[0].voice;
                    } else {
                        mask = -1;
                    }
                    i++;
                } while ((u8)i < vagCount);
            }
        }
    }
    return mask;
}

/* Keys off every voice that plays this note of this program. Returns the
 * number of voices found. */
s32 SpuVmKeyOffVoice(s16, s16, s16, u16) asm("SpuVmKeyOff");
s32 SpuVmKeyOffVoice(s16 arg0, s16 vabId, s16 prog, u16 note) {
    u16 bitsUpper;
    u16 bitsLower;
    u8 voice;
    s32 count;
    u16 tempVoice;

    count = 0;
    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        if ((_svm_voice[voice].note == note) &&
            (_svm_voice[voice].prog == prog) &&
            (_svm_voice[voice].unkE == arg0) &&
            (_svm_voice[voice].vabId == vabId)) {
            if (_svm_voice[voice].unk0 == 0xFF) {
                _svm_voice[voice].unk1B = 0;
                _svm_voice[voice].unk4 = 0;
                _svm_spuBase[202] = 0;
                _svm_spuBase[203] = 0;
            } else {
                _svm_cur.voice = voice;
                tempVoice = GetSvmVoice();
                if (tempVoice < 0x10) {
                    bitsLower = 1 << tempVoice;
                    bitsUpper = 0;
                } else {
                    bitsLower = 0;
                    bitsUpper = 1 << (tempVoice - 0x10);
                }

                _svm_voice[tempVoice].unk1B = 0;
                _svm_voice[tempVoice].unk4 = 0;
                _svm_voice[tempVoice].unk0 = 0;

                _svm_okof1 |= bitsLower;
                _svm_okof2 |= bitsUpper;

                _svm_okon1 &= ~_svm_okof1;
                _svm_okon2 &= ~_svm_okof2;
            }
            count++;
        }
    }
    return count;
}

void SpuVmSeKeyOn(s16 vabId, s16 prog, u16 note, s32 arg3, u16 voll, u16 volr) {
    u16 pan;
    u16 volume;

    if (voll == volr) {
        pan = 0x40;
        volume = voll;
    } else if (volr < voll) {
        volume = voll;
        pan = (volr * 0x40) / voll;
    } else {
        volume = volr;
        pan = 0x7F - ((voll * 0x40) / volr);
    }
    SpuVmKeyOn(0x21, vabId, prog, note, volume, pan);
}

extern void SpuVmKeyOff();

void SpuVmSeKeyOff(s16 vabId, s16 prog, u16 note) {
    SpuVmKeyOff(0x21, vabId, prog, note);
}

void KeyOnCheck(void) {
}

extern s16 D_800B9DDA[];
extern u8 D_800B9C80[];
extern u8 D_800AD224[];
extern u8 D_800AD3A4[];
extern u16 D_800AD3CA[][26];

extern struct SeqStruct *D_800BDE3C[];

/* Stores the sequence volume, and when applyNow is 1 updates the registers
 * of every voice that plays it. */
s32 SpuVmSetSeqVol(s16 seq, u16 voll, u16 volr, s16 applyNow) {
    struct SeqStruct *score = &D_800BDE3C[seq & 0xFF][(seq >> 8) & 0xFF];
    s16 voice;
    s32 vollMul;
    s32 volrMul;
    u8 pad[4];
    s32 temp;
    s16 pos;

    _svm_cur.vagIdx16 = seq;
    score->leftVolume = voll;
    score->rightVolume = volr;
    temp = seq;
    if (score->leftVolume >= 0x80) {
        score->leftVolume = 0x7F;
    }
    if (score->rightVolume >= 0x80) {
        score->rightVolume = 0x7F;
    }
    vollMul = voll * 0x81;
    volrMul = volr * 0x81;

    if (applyNow == 1) {
        for (voice = 0; voice < spuVmMaxVoice; voice++) {
            if ((u16)_svm_voice[voice].unkE == (u16)temp) {
                pos = voice * 8;
                _svm_sreg_buf[pos + 0] = vollMul;
                _svm_sreg_buf[pos + 1] = volrMul;
                _svm_sreg_dirty[voice] |= 3;
            }
        }
    }
    return _svm_cur.vagIdx16;
}

extern s16 D_800B9DDA[];

long SpuVmGetSeqVol(short seq_access, short *volL, short *volR) {
    struct SeqStruct *score;

    score = D_800BDE3C[seq_access & 0xFF];
    D_800B9DDA[0] = seq_access;
    *volL = score[(seq_access & 0xFF00) >> 8].leftVolume;
    *volR = score[(seq_access & 0xFF00) >> 8].rightVolume;
    return D_800B9DDA[0];
}

extern s16 D_800B9DDA[];

s16 SpuVmGetSeqLVol(s16 seq_access) {
    struct SeqStruct *score;

    score = D_800BDE3C[seq_access & 0xFF];
    D_800B9DDA[0] = seq_access;
    return *(s16 *)&score[(seq_access & 0xFF00) >> 8].leftVolume;
}

s16 SpuVmGetSeqRVol(s16 seq_access) {
    struct SeqStruct *score;

    score = D_800BDE3C[seq_access & 0xFF];
    D_800B9DDA[0] = seq_access;
    return *(s16 *)&score[(seq_access & 0xFF00) >> 8].rightVolume;
}

/* Keys off every voice that plays sequence arg0. */
void SpuVmSeqKeyOff(arg0) s16 arg0;
{
    u8 voice;
    u16 bitsUpper;
    u16 bitsLower;
    u16 tempVoice;

    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        if (_svm_voice[voice].unkE == arg0) {
            _svm_cur.voice = voice;
            tempVoice = GetSvmVoice();
            if (tempVoice < 0x10) {
                bitsLower = 1 << tempVoice;
                bitsUpper = 0;
            } else {
                bitsLower = 0;
                bitsUpper = 1 << (tempVoice - 0x10);
            }

            _svm_voice[tempVoice].unk1B = 0;
            _svm_voice[tempVoice].unk4 = 0;
            _svm_voice[tempVoice].unk0 = 0;

            _svm_okof1 |= bitsLower;
            _svm_okof2 |= bitsUpper;

            _svm_okon1 &= ~_svm_okof1;
            _svm_okon2 &= ~_svm_okof2;
        }
    }
}

extern s32 SpuVmVSetUp(s16, s16);
extern u32 D_800B9928[];

s32 SpuVmSetProgVol(vabId, prog, vol)
s16 vabId;
s16 prog;
s32 vol;
{
    if (SpuVmVSetUp(vabId, prog) != 0) {
        return -1;
    }
    ((u8 *)D_800B9928[0])[prog * 16 + 1] = vol;
    return ((u8 *)D_800B9928[0])[prog * 16 + 1];
}

extern s32 SpuVmVSetUp(s16, s16);
extern u32 D_800B9928[];

s32 SpuVmGetProgVol(vabId, prog)
s16 vabId;
s16 prog;
{
    if (SpuVmVSetUp(vabId, prog) != 0) {
        return -1;
    }
    return ((u8 *)D_800B9928[0])[prog * 16 + 1];
}

s32 SpuVmSetProgPan(vabId, prog, pan)
s16 vabId;
s16 prog;
s32 pan;
{
    if (SpuVmVSetUp(vabId, prog) != 0) {
        return -1;
    }
    ((u8 *)D_800B9928[0])[prog * 16 + 4] = pan;
    return ((u8 *)D_800B9928[0])[prog * 16 + 4];
}

s32 SpuVmGetProgPan(vabId, prog)
s16 vabId;
s16 prog;
{
    if (SpuVmVSetUp(vabId, prog) != 0) {
        return -1;
    }
    return ((u8 *)D_800B9928[0])[prog * 16 + 4];
}

/* The unprototyped void declaration above is what the callers see. */
s32 SpuVmSetVolImpl(s16, s16, s16, u16, u16) asm("SpuVmSetVol");
s32 SpuVmSetVolImpl(s16 seq_sep_no, s16 vabId, s16 prog, u16 arg3, u16 arg4) {
    struct SeqStruct *score =
        &D_800BDE3C[seq_sep_no & 0xFF][(seq_sep_no & 0xFF00) >> 8];
    s32 var_s2;
    u8 voice;
    s32 new_var;
    u32 voll, volr;
    u32 voll_t, volr_t;
    s32 mvol_scaled;
    u8 temp;
    s16 new_var2;

    var_s2 = 0;
    SpuVmVSetUp(vabId, prog);
    _svm_cur.vagIdx16 = seq_sep_no;
    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        new_var2 = prog;
        if ((_svm_voice[voice].unkE == seq_sep_no) &&
            (_svm_voice[voice].prog == new_var2) &&
            (_svm_voice[voice].vabId == vabId)) {
            if (score->vol[score->channel] != arg3 &&
                score->vol[score->channel] == 0) {
                score->vol[score->channel] = 1;
            }
            new_var = (_svm_voice[voice].unk8 * arg3) / 0x7F;
            mvol_scaled = _svm_vh->mvol * 0x3FFF;
            voll_t = ((new_var * mvol_scaled) / 0x7F) / 0x7F;
            voll_t =
                ((voll_t * _svm_pg[new_var2].mvol *
                  _svm_tn[_svm_voice[voice].tone + (new_var2 * 0x10)].vol) /
                 0x7F) /
                0x7F;
            volr_t = voll_t;

            voll_t = (voll_t * score->leftVolume) / 0x7F;
            volr_t = (volr_t * score->rightVolume) / 0x7F;

            temp = _svm_tn[_svm_voice[voice].tone].pan;
            if (temp < 0x40) {
                voll = voll_t;
                volr = (volr_t * temp) / 0x3F;
            } else {
                voll = (voll_t * (0x7F - temp)) / 0x3F;
                volr = volr_t;
            }
            temp = _svm_pg[_svm_voice[voice].unk10].mpan;
            if (temp < 0x40) {
                volr = (volr * temp) / 0x3F;
            } else {
                voll = (voll * (0x7F - temp)) / 0x3F;
            }
            do {
                do {
                    temp = arg4;
                } while (0);
            } while (0);
            if (temp < 0x40) {
                volr = (volr * temp) / 0x3F;
            } else {
                voll = (voll * (0x7F - temp)) / 0x3F;
            }
            if (_svm_stereo_mono == 1) {
                if (voll < volr) {
                    voll = volr;
                } else {
                    volr = voll;
                }
            }
            voll = (voll * voll) / 0x3FFF;
            volr = (volr * volr) / 0x3FFF;
            _svm_sreg_buf[voice * 8 + 0] = voll;
            _svm_sreg_buf[voice * 8 + 1] = volr;
            _svm_sreg_dirty[voice] |= 3;
            var_s2++;
        }
    }
    return var_s2;
}

extern s32 D_800B2090[];
extern s32 gOrderingTables[];
extern u16 D_800B9DDE[];
extern s16 D_800B9DDC[];
extern u8 D_800AD3BC[];
extern u8 D_800AD3C8[];
extern u8 D_800AD3CC[];
extern u8 D_800AD3CE[];
extern u8 D_800AD3D0[];
extern u8 D_800AD3D2[];
extern u8 D_800AD3D7[];
extern u8 D_800B9DC4[];
extern u8 D_800B9DC6[];
extern u8 D_800B9DC7[];
extern u8 D_800B9DC8[];
extern u8 D_800B9DC9[];
extern u8 D_800B9DCB[];
extern u8 D_800B9DCE[];
extern u8 D_800B9DCF[];
extern u8 D_800B9DD0[];
extern u8 D_800B9DD1[];
extern u8 D_800B9DD2[];
extern u8 D_800B9DD3[];
extern u8 D_800B9DD4[];
extern u8 D_800B9DD5[];
extern u8 D_800B9DD6[];
extern u8 D_800B9DD7[];
extern u8 D_800B9DD8[];
extern u8 D_800AD3BE[];
extern u8 D_800AD3CC[];
extern u32 D_800B9950[];

/* Retail's codegen needs these spellings:
 * - the (s16)vag test is also the SpuVmAlloc argument, so the sll/sra pair
 *   has a second use and combine can't fold it into the beqz;
 * - (u8)voice in the compare and in the *52 index makes the `move v1,s0`
 *   copy (combine reduces the zero-extend to a copy that has two uses);
 * - D_800B9DD0 + D_800B9DCB * 16 in that operand order;
 * - the post-alloc stores run D3CA, D3D2, D3CC, D3CE, D3BC, D3D0, D3C8,
 *   D3D7, D3BE so sched1 hoists the DCB/DDC/DD0 reloads like retail. */
/* SPDX-License-Identifier: MIT */
s32 SsUtKeyOn(s16 vabId, s16 prog, s16 tone, s16 note, u16 fine, s16 voll,
              s16 volr) {
    extern s32 SpuVmAlloc();
    extern void SpuVmDoAllocate();
    extern void vmNoiseOn();
    extern s32 note2pitch2();
    extern void SpuVmKeyOnNow();
    extern s32 keyOnGuard[] asm("D_800B2090.NON_MATCHING");
    s32 voice;
    u8 *progAttr;
    u8 *toneAttr;
    s32 vag;

    if (D_800B2090[0] == 1) {
        return -1;
    }
    ((s32 *)gOrderingTables)[-1] = 1;
    if (SpuVmVSetUp((s16)vabId, (s16)prog) != 0) {
        keyOnGuard[0] = 0;
        return -1;
    }
    D_800B9DDA[0] = 0x21;
    D_800B9DC6[0] = note;
    D_800B9DC7[0] = fine;
    D_800B9DD0[0] = tone;
    if (voll == volr) {
        D_800B9DC9[0] = 0x40;
        D_800B9DC8[0] = voll;
    } else if (volr < voll) {
        D_800B9DC8[0] = voll;
        D_800B9DC9[0] = (volr << 6) / voll;
    } else {
        D_800B9DC8[0] = volr;
        D_800B9DC9[0] = 0x7F - (voll << 6) / volr;
    }
    progAttr = (u8 *)(prog * 16 + (s32)D_800B9928[0]);
    D_800B9DCE[0] = progAttr[1];
    D_800B9DCF[0] = progAttr[4];
    D_800B9DC4[0] = progAttr[0];
    toneAttr =
        (u8 *)((D_800B9DD0[0] + D_800B9DCB[0] * 16) * 32 + (s32)D_800B9950[0]);
    D_800B9DD3[0] = toneAttr[0];
    vag = *(u16 *)(toneAttr + 0x16);
    D_800B9DDC[0] = vag;
    D_800B9DD1[0] = toneAttr[2];
    D_800B9DD2[0] = toneAttr[3];
    D_800B9DD4[0] = toneAttr[4];
    D_800B9DD5[0] = toneAttr[5];
    D_800B9DD8[0] = toneAttr[1];
    D_800B9DD6[0] = toneAttr[6];
    D_800B9DD7[0] = toneAttr[7];
    if ((s16)vag == 0) {
        keyOnGuard[0] = 0;
        return -1;
    }
    voice = (u8)SpuVmAlloc((s16)vag);
    if ((u8)voice == D_800B9C80[0]) {
        keyOnGuard[0] = 0;
        return -1;
    }
    D_800B9DDE[0] = voice;
    D_800AD3CA[(u8)voice][0] = 0x21;
    *(s16 *)(D_800AD3D2 + (u8)voice * 52) = vabId;
    *(s16 *)(D_800AD3CC + (u8)voice * 52) = D_800B9DC9[2];
    *(s16 *)(D_800AD3CE + (u8)voice * 52) = prog;
    *(s16 *)(D_800AD3BC + (u8)voice * 52) = *(u16 *)&D_800B9DDA[1];
    *(s16 *)(D_800AD3D0 + (u8)voice * 52) = D_800B9DCF[1];
    *(s16 *)(D_800AD3C8 + (u8)voice * 52) = note;
    *(u8 *)(D_800AD3D7 + (u8)voice * 52) = 1;
    *(s16 *)(D_800AD3BE + (u8)voice * 52) = 0;
    SpuVmDoAllocate();
    if (((s16 *)D_800B9DDE)[-1] == 0xFF) {
        vmNoiseOn(voice);
    } else {
        SpuVmKeyOnNow(1, (u16)note2pitch2((u16)note, fine));
    }
    keyOnGuard[0] = 0;
    return voice;
}

extern s32 D_800B2090[];
extern s32 gOrderingTables[];
extern s32 D_800A20B8[];
extern u16 D_800B9DDE[];
extern s16 D_800B9DDC[];
extern u16 D_800BEB98[];
extern u16 D_800BEB9C[];
extern u16 D_800AD96C[];
extern u16 D_800AD970[];
extern u8 D_800AD3BC[];
extern u8 D_800AD3C0[];
extern u8 D_800AD3C8[];
extern u8 D_800AD3CE[];
extern u8 D_800AD3D0[];
extern u8 D_800AD3D2[];
extern u8 D_800AD3D7[];

/* Matches (0 words) under GNU C 2.6.3-psx only. Retail's codegen needs these
 * spellings:
 * - The voice masks reuse the vabId and prog parameters (s32, narrowed with
 *   (s16) in the compares). Their copy pseudos prefer a1 and a2 and conflict
 *   with the constant 1 held in t1. Separate mask locals leave the constant
 *   preferring a0 (a mask merges its preference into it through
 *   expand_preferences), which pushes the vc * 52 index to t0 (20 rows) or,
 *   when the second chain load is captured, puts that load in a1 (2 rows).
 * - D_800B9DDE is stored through its own name and reloaded through the
 *   neighbour spelling D_800B9DDC + 2. cse can't forward the store and the
 *   two accesses don't share a la. Distinct symbols alone let sched1 hoist the
 *   reload above the store; the empty do-while leaves loop notes that stop
 *   that (no asm barrier needed).
 * - orTemp and orTemp2 keep the or operand order, and the four mask stores
 *   use four distinct address spellings. */
/* SPDX-License-Identifier: MIT */
s32 SsUtKeyOff(s16 vc, s32 vabId, s32 prog, s16 tone, s16 note) {
    u16 voice;
    s32 keyOnLow;
    s32 keyOnHigh;
    s32 newLow;
    s32 newHigh;
    s32 seq;

    if (D_800B2090[0] == 1) {
        return -1;
    }
    ((s32 *)gOrderingTables)[-1] = 1;
    if ((u16)vc < 0x18) {
        if (*(s16 *)(D_800AD3D2 + vc * 52) == (s16)vabId &&
            *(s16 *)(D_800AD3CE + vc * 52) == (s16)prog &&
            *(s16 *)(D_800AD3D0 + vc * 52) == tone &&
            *(s16 *)(D_800AD3C8 + vc * 52) == note) {
            if (*(s16 *)(D_800AD3BC + vc * 52) == 0xFF) {
                D_800AD3D7[(u8)vc * 52] = 0;
                seq = D_800A20B8[0];
                *(s16 *)(D_800AD3C0 + (u8)vc * 52) = 0;
                *(s16 *)(seq + 0x194) = 0;
                *(s16 *)(seq + 0x196) = 0;
            } else {
                D_800B9DDE[0] = vc;
                do {
                } while (0);
                voice = ((u16 *)D_800B9DDC)[1];
                if (voice < 0x10) {
                    prog = 1 << voice;
                    vabId = 0;
                } else {
                    prog = 0;
                    vabId = 1 << (voice - 0x10);
                }
                D_800AD3D7[voice * 52] = 0;
                keyOnLow = D_800BEB98[0];
                keyOnHigh = D_800BEB9C[0];
                *(s16 *)(D_800AD3C0 + voice * 52) = 0;
                *(s16 *)(D_800AD3BC + voice * 52) = 0;
                newLow = prog | keyOnLow;
                ((u16 *)D_800BEB9C)[-2] = newLow;
                ((u16 *)D_800AD970)[-2] = D_800AD96C[0] & ~newLow;
                newHigh = vabId | keyOnHigh;
                ((u16 *)D_800BEB98)[2] = newHigh;
                ((u16 *)D_800AD96C)[2] = D_800AD970[0] & ~newHigh;
            }
            D_800B2090[0] = 0;
            return 0;
        }
    }
    ((s32 *)gOrderingTables)[-1] = 0;
    return -1;
}

/* Donor body (sotn vmanager.c). Retail reads note and fine as u16 (no sign
 * extension at the note2pitch2 call), so the C name differs from libsnd.h's
 * all-short prototype; the asm label keeps the SDK name. (u8)voice for
 * vmNoiseOn also fixes the s2/s3 order of voice and voll. */
extern void SpuVmDoAllocate(void);
extern void SpuVmKeyOnNow();
extern void vmNoiseOn();
extern s32 note2pitch2();

s16 SsUtKeyOnVImpl(s16, s16, s16, s16, u16, u16, s16, s16) asm("SsUtKeyOnV");
s16 SsUtKeyOnVImpl(s16 voice, s16 vabId, s16 prog, s16 tone, u16 note, u16 fine,
                   s16 voll, s16 volr) {
    s32 tone2;

    if (_snd_ev_flag == 1) {
        return -1;
    }
    _snd_ev_flag = 1;
    if (voice < 0 || voice >= 24) {
        _snd_ev_flag = 0;
        return -1;
    }
    if (SpuVmVSetUp(vabId, prog)) {
        _snd_ev_flag = 0;
        return -1;
    }
    _svm_cur.vagIdx16 = 0x21;
    _svm_cur.note = note;
    _svm_cur.field3 = fine;
    _svm_cur.vagIdx = tone;

    if (voll == volr) {
        _svm_cur.field5 = 0x40;
        _svm_cur.voll = voll;
    } else if (volr < voll) {
        _svm_cur.field5 = (volr * 0x40) / voll;
        _svm_cur.voll = voll;
    } else {
        _svm_cur.field5 = 0x7F - ((voll * 0x40) / volr);
        _svm_cur.voll = volr;
    }

    _svm_cur.mvol = _svm_pg[prog].mvol;
    _svm_cur.mpan = _svm_pg[prog].mpan;
    _svm_cur.field0 = _svm_pg[prog].tones;

    tone2 = _svm_cur.vagIdx + (_svm_cur.fakeProgram * 0x10);
    _svm_cur.prior = _svm_tn[tone2].prior;
    _svm_cur.voiceIdx = _svm_tn[tone2].vag;
    _svm_cur.vol = _svm_tn[tone2].vol;
    _svm_cur.pan = _svm_tn[tone2].pan;
    _svm_cur.centre = _svm_tn[tone2].center;
    _svm_cur.shift = _svm_tn[tone2].shift;
    _svm_cur.seqSepNo = _svm_tn[tone2].mode;
    _svm_cur.mode = _svm_tn[tone2].min;
    _svm_cur.field13 = _svm_tn[tone2].max;

    if (_svm_cur.voiceIdx == 0) {
        _snd_ev_flag = 0;
        return -1;
    }

    _svm_cur.voice = voice;
    _svm_voice[voice].unkE = 0x21;
    _svm_voice[voice].vabId = vabId;
    _svm_voice[voice].unk10 = _svm_cur.fakeProgram;
    _svm_voice[voice].prog = prog;
    _svm_voice[voice].unk0 = _svm_cur.voiceIdx;
    _svm_voice[voice].tone = _svm_cur.vagIdx;
    _svm_voice[voice].note = note;
    _svm_voice[voice].unk1B = 1;
    _svm_voice[voice].unk2 = 0;
    SpuVmDoAllocate();
    if (_svm_cur.voiceIdx == 0xFF) {
        vmNoiseOn((u8)voice);
    } else {
        SpuVmKeyOnNow(1, (u16)note2pitch2(note, fine));
    }
    _snd_ev_flag = 0;
    return voice;
}

s32 SsUtKeyOffV(s16 voice) {
    u16 bitsUpper;
    u16 bitsLower;
    u16 temp2;

    if (_snd_ev_flag == 1) {
        return -1;
    }
    _snd_ev_flag = 1;

    if (voice >= 0 && voice < 24) {
        _svm_cur.voice = voice;
        temp2 = GetSvmVoice();
        if (temp2 < 0x10) {
            bitsLower = 1 << temp2;
            bitsUpper = 0;
        } else {
            bitsLower = 0;
            bitsUpper = 1 << (temp2 - 0x10);
        }

        _svm_voice[temp2].unk1B = 0;
        _svm_voice[temp2].unk4 = 0;
        _svm_voice[temp2].unk0 = 0;

        _snd_ev_flag = 0;

        _svm_okof1 |= bitsLower;
        _svm_okof2 |= bitsUpper;

        _svm_okon1 &= ~_svm_okof1;
        _svm_okon2 &= ~_svm_okof2;
        return 0;
    }
    _snd_ev_flag = 0;
    return -1;
}

extern s16 D_800B9DDA[];
extern s32 SpuVmVSetUp(s16, s16);
extern s32 SpuVmPBVoice(s16, s16, s16, s16, u16);
s16 SsUtPitchBend(s16 voice, s16 vabId, s16 prog, s16 note, s16 pbend) {
    SpuVmVSetUp(vabId, prog);
    _svm_cur.vagIdx16 = 0x21;
    return -((SpuVmPBVoice(voice, 0x21, vabId, prog, pbend) << 16) == 0);
}

short SsUtChangePitch(voice, vabId, prog, old_note, old_fine, new_note,
                      new_fine)
short voice;
short vabId;
short prog;
short old_note;
short old_fine;
u16 new_note;
u16 new_fine;
{
    extern s32 note2pitch2();
    extern u16 gSpuRegisterBuffer[] asm("D_800AD224");
    if (voice >= 0 && voice < 24) {
        if (((s16 *)D_800AD3D2)[voice * 26] == vabId) {
            if (((s16 *)D_800AD3CE)[voice * 26] == prog) {
                if (((s16 *)D_800AD3C8)[voice * 26] == old_note) {
                    SpuVmVSetUp(((s16 *)D_800AD3D2)[voice * 26],
                                ((s16 *)D_800AD3CE)[voice * 26]);
                    D_800B9DDA[0] = 0x21;
                    D_800B9DDE[0] = voice;
                    D_800B9DD0[0] = D_800AD3D0[voice * 52];
                    gSpuRegisterBuffer[voice * 8 + 2] =
                        note2pitch2(new_note, new_fine);
                    D_800AD3A4[voice] |= 4;
                    return 0;
                }
            }
        }
    }
    return -1;
}

extern u16 gSpuRegisterBuffer[];
extern u8 D_800AD3A4[];
s16 SsUtChangeADSR(s16 voice, s16 vabId, s16 prog, s16 oldNote, u16 adsr1,
                   u16 adsr2) {
    s32 voiceOffset;
    s32 attrOffset;
    if ((u16)voice < 0x18) {
        voiceOffset = voice * 26;
        if (((s16 *)D_800AD3D2)[voiceOffset] == vabId) {
            if (((s16 *)D_800AD3CE)[voiceOffset] == prog) {
                if (((s16 *)D_800AD3C8)[voiceOffset] == oldNote) {
                    attrOffset = voice * 8;
                    gSpuRegisterBuffer[attrOffset + 4] = adsr1;
                    gSpuRegisterBuffer[attrOffset + 5] = adsr2;
                    D_800AD3A4[voice] |= 0x30;
                    return 0;
                }
            }
        }
    }
    return -1;
}

extern s32 D_800A20B8[];

s32 SsUtGetDetVVol(s32 vab, s16 *vl, s16 *vr) {
    if ((u16)vab < 0x18) {
        *vl = *(s16 *)((s32)D_800A20B8[0] + ((s16)vab) * 16);
        *vr = *(s16 *)((s32)D_800A20B8[0] + ((s16)vab) * 16 + 2);
        return 0;
    }
    return -1;
}

short SsUtSetDetVVol(short vc, short vl, short vr) {
    if ((u16)vc < 24) {
        *(s16 *)&D_800AD224[vc * 16 + 2] = vr;
        D_800AD3A4[vc] |= 3;
        *(s16 *)&D_800AD224[vc * 16] = vl;
        return 0;
    }
    return -1;
}

extern s32 D_800A20B8[];

s32 SsUtGetVVol(s32 vc, s16 *voll, s16 *volr) {
    s16 mvolL;
    s16 mvolR;

    if ((u16)vc < 24) {
        mvolL = *(s16 *)&((u8 *)D_800A20B8[0])[(s16)vc * 16];
        mvolR = *(s16 *)&((u8 *)D_800A20B8[0])[(s16)vc * 16 + 2];
        *voll = mvolL / 129;
        *volr = mvolR / 129;
        return 0;
    }
    return -1;
}

short SsUtSetVVol(short vc, short voll, short volr) {
    s16 mvolL;
    s16 mvolR;

    if ((u16)vc < 24) {
        mvolL = voll * 129;
        mvolR = volr * 129;
        *(s16 *)&D_800AD224[vc * 16 + 2] = mvolR;
        D_800AD3A4[vc] |= 3;
        *(s16 *)&D_800AD224[vc * 16] = mvolL;
        return 0;
    }
    return -1;
}

extern void SeAutoVol(s16 seq_access, s16 vol1, s16 vol2, s16 mSec);

s32 SsUtAutoVol(s32 seq_access, s32 vol1, s32 vol2, s32 mSec) {
    if ((u16)seq_access < 24) {
        SeAutoVol(seq_access, vol1, vol2, mSec);
        return 0;
    }
    return -1;
}

extern void SeAutoPan(s16 seq_access, s16 pan1, s16 pan2, s16 mSec);

s32 SsUtAutoPan(s32 seq_access, s32 pan1, s32 pan2, s32 mSec) {
    if ((u16)seq_access < 24) {
        SeAutoPan(seq_access, pan1, pan2, mSec);
        return 0;
    }
    return -1;
}

void SsUtAllKeyOff(void) {
    s16 voice;
    u16 bitsUpper;
    u16 bitsLower;
    u16 temp2;
    s16 pos;

    for (voice = 0; voice < spuVmMaxVoice; voice++) {
        _svm_voice[voice].unk2 = 0x18;
        _svm_voice[voice].unk0 = 0xFF;
        _svm_voice[voice].unk1B = 0;
        _svm_voice[voice].unk4 = 0;
        _svm_voice[voice].unk6 = 0;
        _svm_voice[voice].unkE = 0xFF;
        _svm_voice[voice].unk10 = 0;
        _svm_voice[voice].prog = 0;
        _svm_voice[voice].tone = 0xFF;

        pos = voice * 8;
        _svm_spuBase[pos + 0x6 / 2] = 0x200;
        _svm_spuBase[pos + 0x4 / 2] = 0x1000;
        _svm_spuBase[pos + 0x8 / 2] = 0x80ff;
        _svm_spuBase[pos + 0x0] = 0;
        _svm_spuBase[pos + 0x2 / 2] = 0;
        _svm_spuBase[pos + 0xa / 2] = 0x4000;

        _svm_cur.voice = voice;
        temp2 = GetSvmVoice();
        if (temp2 < 0x10) {
            bitsLower = 1 << temp2;
            bitsUpper = 0;
        } else {
            bitsLower = 0;
            bitsUpper = 1 << (temp2 - 0x10);
        }

        _svm_voice[temp2].unk1B = 0;
        _svm_voice[temp2].unk4 = 0;
        _svm_voice[temp2].unk0 = 0;

        _svm_okof1 |= bitsLower;
        _svm_okof2 |= bitsUpper;

        _svm_okon1 &= ~_svm_okof1;
        _svm_okon2 &= ~_svm_okof2;
    }
}
