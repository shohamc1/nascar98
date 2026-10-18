/* SPDX-License-Identifier: MIT */
#ifndef N98_PSXSDK_INTERNAL_H
#define N98_PSXSDK_INTERNAL_H
#include "common.h"
struct SeqStruct {
    u8 unk0; u8 pad1[3];
    u8* readPos; u8* nextSepPos; u8* loopPos;
    u8 unk10; u8 eventStatus; u8 channel; u8 unk13; u8 unk14; u8 unk15; u8 unk16;
    u8 panpot[16];
    u8 unk27; u8 unk28; u8 unk29; u8 unk2A; u8 unk2B;
    u8 programs[16]; u8 unk3C; u8 pad3D;
    s16 unk3E; s16 unk40; s16 unk42; s16 unk44; s16 loopCount; s16 loopIndex; s16 unk4A; s16 unk4C;
    s16 vol[16];
    s16 unk6E; s16 unk70; s16 unk72;
    u16 leftVolume; u16 rightVolume; s16 unk78; s16 unk7A;
    s32 unk7C; u32 unk80; s32 unk84; s32 deltaValue; s32 unk8C; s32 unk90;
    u32 unk94; u32 unk98; s32 unk9C; u32 unkA0; u32 unkA4;
    s16 unkA8; s16 unkAA;
};
typedef char SeqStruct_must_be_0xAC[(sizeof(struct SeqStruct) == 0xAC) ? 1 : -1];
extern struct SeqStruct *D_800BDE3C[];

/* libsnd state. The names follow the Psy-Q headers; the Makefile binds each
 * to its address. */
extern s32 _snd_openflag;
extern s32 _snd_ev_flag;
extern s16 _snd_seq_s_max;
extern s16 _snd_seq_t_max;
extern u32 VBLANK_MINUS;

/* Voice manager state, after the Psy-Q 3.5 libsnd headers. */
typedef struct ProgAtr {
    u8 tones;
    u8 mvol;
    u8 prior;
    u8 mode;
    u8 mpan;
    s8 reserved0;
    s16 attr;
    u32 reserved1;
    u16 reserved2; /* even vag spu pointer */
    u16 reserved3; /* odd vag spu pointer */
} ProgAtr;

typedef struct VagAtr {
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
} VagAtr;

struct SpuVoice {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u16 unk6;
    s16 unk8;
    s8 unkA;
    s8 unkB;
    s16 note;
    s16 unkE;
    s16 unk10;
    s16 prog;
    s16 tone;
    s16 vabId;
    s16 unk18;
    u8 pad1A;
    u8 unk1B;
    s16 autoVol;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 startVol;
    s16 endVol;
    s16 autoPan;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 startPan;
    s16 endPan;
};

struct SvmCur {
    char field0;
    char vabId;
    char note;
    char field3;
    char voll;
    char field5;
    char program;
    char fakeProgram;
    char field8;
    char field9;
    char mvol;
    char mpan;
    char vagIdx;
    char vol;
    char pan;
    char prior;
    char centre;
    u8 shift;
    char mode;
    char field13;
    u8 seqSepNo;
    u8 pad15;
    s16 vagIdx16;
    s16 voiceIdx;
    s16 voice;
    s16 regOff;
    s16 toneOff;
};

extern struct SvmCur _svm_cur;
extern struct SpuVoice _svm_voice[];
extern s32 _svm_envx_hist[];
extern s16 _svm_sreg_buf[];
extern char _svm_sreg_dirty[];
extern ProgAtr *_svm_pg;
extern VagAtr *_svm_tn;
extern s16 _svm_damper;
typedef struct VabHdr {
    s32 form;
    s32 ver;
    s32 id;
    u32 fsize;
    u16 reserved0;
    u16 ps;
    u16 ts;
    u16 vs;
    u8 mvol;
    u8 pan;
    u8 attr1;
    u8 attr2;
    u32 reserved1;
} VabHdr;

typedef struct SpuTRegs2 {
    u8 pad[0x184];
    s16 revVolLeft;
    s16 revVolRight;
    u8 pad1[0x1A6 - 0x188];
    volatile u16 trans_addr;
    volatile u16 trans_fifo;
    volatile u16 spucnt;
    u8 pad3[2];
    volatile u16 spustat;
} SpuTRegs2;
typedef union SpuTRegsUnion2 {
    SpuTRegs2 rxx;
} SpuTRegsUnion2;
extern volatile SpuTRegsUnion2 *_spu_RXX;

extern VabHdr *_svm_vh;
extern s16 _svm_stereo_mono;
extern u16 _svm_orev1;
extern u16 _svm_orev2;
extern s16 _svm_vcf;
extern u16 _svm_vab_count;
extern u32 _ss_spu_vm_rec[];
extern s16 kMaxPrograms;
extern u8 _svm_auto_kof_mode;
extern s32 _svm_envx_idx;
extern VabHdr *_svm_vab_vh[16];
extern ProgAtr *_svm_vab_pg[16];
extern VagAtr *_svm_vab_tn[16];
extern s32 _svm_vab_total[16];
extern s32 _svm_vab_start[16];
extern s32 _svm_brr_start_addr[16];
extern u8 _svm_vab_used[];
extern u8 spuVmMaxVoice;
extern void SpuSetNoiseVoice();

extern u16 *_svm_spuBase;
extern u16 _svm_okon1;
extern u16 _svm_okon2;
extern u16 _svm_okof1;
extern u16 _svm_okof2;

static __inline__ u16 GetSvmVoice(void) {
    return _svm_cur.voice;
}

#endif
