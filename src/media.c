#include "common.h"
#include "libpress.h"
#include "fixed_addrs.h"
#include <psxsdk/libgpu.h>
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/libcd.h>
#include <psxsdk/libgte.h>
#include <psxsdk/libapi.h>
#include <psxsdk/libspu.h>
#include <psxsdk/kernel.h>
#include "game.h"
#include "pad_axis.h"
#include "cd.h"
#include "input.h"
#include "scene.h"

/* The head of a movie stream chunk. Both words are big-endian. */
typedef struct StreamChunk {
    u32 tag;  /* 0x00: four characters, such as "ad20" or "au00" */
    u32 size; /* 0x04: bytes, header included */
} StreamChunk;
extern s32 SpuSetReverbVoice(s32, s32);

void SpuSetTransferStartAddr(s32);

extern s32 gOrderingTable[];
extern void HeapFree(void *ptr);
extern u8 D_800A2F9CLui asm("D_800A2F9CAbsolute");
extern void SoundPlaySlot(s8, s8);
extern void SsSetMute(s32);
s32 VSync(s32);
extern void MenuDrawString(u8 *, s16, s16, u8, u8, s32, u8, u8);
void TextureLoadTim(void *timImage);
asm(".globl MenuDrawStringW");
extern u16 gCdVolumeAbsolute[];
void *FileOpen(s32 fileId, void *mode);
void *FileLoadToHeap(s32 fileId);
void func_80063A28(void);

extern u8 gPadLayout[];

/* Maps the raw button word of pad `arg0` onto the game's action bits. The
 * mapping depends on the pad type (`gPadType`) and on the layout selected
 * for that pad (`gPadLayout`). Modes that share a prefix share a switch arm
 * and finish with a `mode` test; cross-jumping merges the repeated tails. */
s32 PadMapButtons(u8 arg0) {
    u8 padType;
    u8 mode;
    s32 flags;
    s32 buttons;

    padType = ((u8 *)gPadType)[arg0];
    mode = gPadLayout[arg0];
    flags = 0;
    buttons = PadGetButtons(arg0);
    if (padType == 2) {
        switch (mode) {
        case 0:
        case 2:
        case 4:
            if (buttons & 4) {
                flags |= 4;
            }
            if (buttons & 8) {
                flags |= 0x10;
            }
            if (buttons & 0x1000) {
                flags |= 1;
            }
            if (buttons & 0x4000) {
                flags |= 2;
            }
            break;
        case 1:
        case 3:
        case 5:
        case 6:
            if (buttons & 4) {
                flags |= 2;
            }
            if (buttons & 8) {
                flags |= 1;
            }
            if (buttons & 0x20) {
                flags |= 0x10;
            }
            if (buttons & 0x10) {
                flags |= 4;
            }
            break;
        }
    } else if (padType == 4) {
        asm(".rdata");
        asm(".long 0");
        asm(".text");
        if (buttons & 0x8000) {
            flags = 0x8000;
        }
        if (buttons & 0x2000) {
            flags |= 0x200;
        }
        if (buttons & 0x1000) {
            flags |= 0x800;
        }
        if (buttons & 0x4000) {
            flags |= 0x1000;
        }
        switch (mode) {
        case 0:
        case 1:
            if (buttons & 1) {
                flags |= 0x10;
            }
            if (buttons & 4) {
                flags |= 4;
            }
            if (buttons & 2) {
                flags |= 1;
            }
            if (buttons & 8) {
                flags |= 2;
            }
            if (mode == 0) {
                if (buttons & 0x20) {
                    flags |= 0x10;
                }
                if (buttons & 0x40) {
                    flags |= 0x40;
                }
                if (buttons & 0x80) {
                    flags |= 0x80;
                }
            } else {
                if (buttons & 0x20) {
                    flags |= 0x40;
                }
                if (buttons & 0x40) {
                    flags |= 0x80;
                }
                if (buttons & 0x80) {
                    flags |= 0x10;
                }
            }
            break;
        case 2:
        case 3:
            if (buttons & 1) {
                flags |= 0x10;
            }
            if (buttons & 4) {
                flags |= 2;
            }
            if (buttons & 2) {
                flags |= 4;
            }
            if (buttons & 8) {
                flags |= 1;
            }
            if (buttons & 0x10) {
                flags |= 4;
            }
            if (mode == 2) {
                if (buttons & 0x20) {
                    flags |= 0x10;
                }
                if (buttons & 0x40) {
                    flags |= 0x40;
                }
                if (buttons & 0x80) {
                    flags |= 0x80;
                }
            } else {
                if (buttons & 0x20) {
                    flags |= 0x40;
                }
                if (buttons & 0x40) {
                    flags |= 0x80;
                }
                if (buttons & 0x80) {
                    flags |= 0x10;
                }
            }
            break;
        case 4:
            if (buttons & 1) {
                flags |= 4;
            }
            if (buttons & 4) {
                flags |= 0x10;
            }
            if (buttons & 2) {
                flags |= 2;
            }
            if (buttons & 8) {
                flags |= 1;
            }
            if (buttons & 0x10) {
                flags |= 4;
            }
            if (buttons & 0x20) {
                flags |= 0x10;
            }
            if (buttons & 0x40) {
                flags |= 0x40;
            }
            if (buttons & 0x80) {
                flags |= 0x80;
            }
            break;
        }
    } else if (padType == 5) {
        switch (mode) {
        case 0:
        case 1:
            if (mode == 0) {
                if (buttons & 1) {
                    flags = 2;
                }
                if (buttons & 4) {
                    flags |= 4;
                }
                if (buttons & 2) {
                    flags |= 1;
                }
                if (buttons & 8) {
                    flags |= 0x10;
                }
            } else {
                if (buttons & 1) {
                    flags = 0x10;
                }
                if (buttons & 4) {
                    flags |= 4;
                }
                if (buttons & 2) {
                    flags |= 2;
                }
                if (buttons & 8) {
                    flags |= 1;
                }
            }
            if (buttons & 0x10) {
                flags |= 4;
            }
            if (buttons & 0x20) {
                flags |= 0x80;
            }
            if (buttons & 0x40) {
                flags |= 0x40;
            }
            if (buttons & 0x80) {
                flags |= 0x80;
            }
            break;
        case 2:
            if (buttons & 1) {
                flags = 4;
            }
            if (buttons & 4) {
                flags |= 0x10;
            }
            if (buttons & 2) {
                flags |= 2;
            }
            if (buttons & 8) {
                flags |= 1;
            }
            if (buttons & 0x20) {
                flags |= 4;
            }
            if (buttons & 0x40) {
                flags |= 0x10;
            }
            break;
        }
    } else if (padType == 7) {
        if (mode == 0) {
            if (buttons & 1) {
                flags = 2;
            }
            if (buttons & 4) {
                flags |= 4;
            }
            if (buttons & 2) {
                flags |= 1;
            }
            if (buttons & 8) {
                flags |= 0x10;
            }
        } else {
            if (buttons & 1) {
                flags = 0x10;
            }
            if (buttons & 4) {
                flags |= 4;
            }
            if (buttons & 2) {
                flags |= 2;
            }
            if (buttons & 8) {
                flags |= 1;
            }
        }
        if (buttons & 0x10) {
            flags |= 4;
        }
        if (buttons & 0x20) {
            flags |= 0x80;
        }
        if (buttons & 0x40) {
            flags |= 0x40;
        }
        if (buttons & 0x80) {
            flags |= 0x80;
        }
    }
    return flags;
}

extern PadAxisCal D_800AEE3C[][3];

/* Converts the pad's three stick axes into signed (axis 2) and unsigned
 * (axes 0 and 1) rates using the per-pad calibration table. Indexing the
 * table by axis lets cse fold `i * 3` to a constant in the `i == 2` and
 * `i == 0` arms, which loop.c then hoists after the constant 2. */
void func_8006EB18(Car *obj) {
    u8 scratch[0x500];
    u8 id;
    u8 value;
    u8 denom;
    u8 rate;
    s32 i;

    id = (u8)obj->slot;
    scratch[0x20B] = id;
    PadReadObjectState(scratch);
    for (i = 0; i < 3; i++) {
        value = PadReadAxis(scratch, i, ((u8 *)gPadType)[id], gPadLayout[id]);
        if (i == 2) {
            u8 target;

            target = D_800AEE3C[id][i].center;
            if (value < target - 4) {
                value = target - value;
                denom = target - D_800AEE3C[id][i].min;
                rate = value * 127 / denom;
                if (rate >= 0x80) {
                    rate = 0x7F;
                }
                obj->unk3C5 = -rate;
            } else if (target + 4 < value) {
                value = value - target;
                denom = D_800AEE3C[id][i].max - target;
                rate = value * 127 / denom;
                if (rate >= 0x80) {
                    rate = 0x7F;
                }
                obj->unk3C5 = rate;
            } else {
                obj->unk3C5 = 0;
            }
        } else {
            if (gPadType[id] >= 5) {
                if (i == 0) {
                    u8 target;

                    target = D_800AEE3C[id][i].center;
                    if (value < target - 4) {
                        value = target - value;
                    } else {
                        value = 0;
                    }
                    denom = D_800AEE3C[id][i].center - D_800AEE3C[id][i].max;
                } else {
                    u8 target;

                    target = D_800AEE3C[id][i].center;
                    if (target + 4 < value) {
                        value = value - target;
                    } else {
                        value = 0;
                    }
                    denom = D_800AEE3C[id][i].max - D_800AEE3C[id][i].center;
                }
            } else {
                if (value < 9) {
                    value = 0;
                }
                denom = D_800AEE3C[id][i].max - D_800AEE3C[id][i].min;
            }
            if (value > denom) {
                value = denom;
            }
            rate = value * 255 / denom;
            if (i == 0) {
                obj->unk3C6 = rate;
            } else {
                obj->unk3C7 = rate;
            }
        }
    }
}

extern u8 D_800AD984[];
void BufferClear17Bytes(void) {
    s32 i;
    u8 *ptr;
    i = 16;
    ptr = D_800AD984;
    do {
        *ptr = 0;
        i--;
        ptr--;
    } while (i >= 0);
}

extern s32 D_800A36B4nm[] asm("D_800A36B4.NON_MATCHING");
extern u8 D_800A3578[];
extern s32 D_8009A2E0[];
extern s32 D_8009A300[];
extern s8 gPadTypeAbsolute[];
extern s32 RandomScaledGetVoid(void);
extern void PadResetAndInitializeBuffersi(s32);
asm(".globl RandomScaledGetVoid\nRandomScaledGetVoid = RandomScaledGet");
asm(".globl PadResetAndInitializeBuffersi\nPadResetAndInitializeBuffersi = PadResetAndInitializeBuffers");

void func_8006EEE0(s32 arg0) {
    RECT rect;
    DISPENV disp;
    DRAWENV draw;
    s32 idx;
    void *heap;
    s32 pixptr;
    s32 countdown;
    u8 flag;
    s32 buttons;
    s32 textId;

    idx = arg0 * 2;
    heap = FileLoadToHeap(idx + 0xE);
    MoviePlayFile(idx + 0xF, 2, 0);
    SetDispMask(0);
    TextureLoadTim(heap);
    rect = D_800A39B0[0];
    pixptr = D_800A36B4nm[0];
    SetDefDispEnv(&disp, 0, 0, 0x140, 0xF0);
    if (D_800A3578[0] == 1) {
        rect.x = 0x140;
        LoadImage(&rect, (u_long *)pixptr);
        SetDefDispEnv(&disp, 0x140, 0, 0x140, 0xF0);
    } else {
        SetDefDrawEnv(&draw, 0, 0, 0x140, 0xF0);
        PutDrawEnv(&draw);
    }
    DrawSync(0);
    ClearOTagR((OT_TYPE *)gOrderingTable[0], 0x400);
    MenuFontSet(2, 2);
    if (gPadTypeAbsolute[0] == 2) {
        textId = D_8009A300[0];
    } else {
        textId = D_8009A2E0[0];
    }
    MenuDrawString(textId, 0x131, 0xD8, 1, 0, 0, 0, 0);
    DrawOTag((OT_TYPE *)(gOrderingTable[0] + 0xC));
    PutDispEnv(&disp);
    SetDispMask(1);
    CdEnablePlaybackAndSetVolume();
    do {
        PadResetAndInitializeBuffersi(0);
    } while (PadGetButtons(0) != 0);
    flag = 0;
    countdown = 0x384;
    do {
        RandomScaledGetVoid();
        VSync(0);
        PadResetAndInitializeBuffersi(0);
        buttons = PadGetButtons(0);
        if ((buttons = buttons) & 0x800 || (buttons = buttons) & 0x40 ||
            countdown == 0) {
            flag = 1;
        } else {
            countdown--;
        }
    } while (flag == 0);
    HeapFree(heap);
    SoundPlaySlot(0, 3);
}

void MoviePlayIndexedFile(s32 fileIndex) {
    s32 pad[6];

    if (D_800A2F9CLui != 0) {
        func_8003CCE0(0);
        D_800A2F9CLui = 0;
    }
    MoviePlayFile((fileIndex & 0xFF) + 0x3A, 0, 0);
    CdEnablePlaybackAndSetVolume();
    CdSetMixVolume(((u8 *)gCdVolumeAbsolute)[0]);
}

extern u8 gCdVolumeAbsoluteU8[] asm("gCdVolumeAbsolute");
void MoviePlayIndexedFileAlternate(s32 arg) {
    if (D_800A2F9CLui != 0) {
        func_8003CCE0(0);
        D_800A2F9CLui = 0;
    }
    MoviePlayFile((arg & 0xFF) + 0xC, 0, 0);
    CdEnablePlaybackAndSetVolume();
    CdSetMixVolume(gCdVolumeAbsoluteU8[0]);
}

extern s32 D_800A3904w16 asm("D_800A3904.NON_MATCHING");
extern u8 *func_800719FC(s32 *);
extern void func_800718D4(s32);
extern void func_80072750(void);
extern void AudioEnableStream(void);
extern s32 AudioGetStreamCounter(void);
extern s32 AudioGetStreamPositionLimit(u32);
extern void AudioQueueAdpcm(u8 *);
extern void AudioQueueStereoAdpcm(u8 *);
extern void MediaBuildVlcLookup(s32);
extern void VideoSwapDisplayAndDrawEnvironments(void);
extern void MovieDispatchFrameUpdateArgs(u8 *, s32, s32);
asm(".globl MovieDispatchFrameUpdateArgs\nMovieDispatchFrameUpdateArgs = MovieDispatchFrameUpdate");
extern void PadResetAndInitializeBuffersArg(s32);
asm(".globl PadResetAndInitializeBuffersArg\nPadResetAndInitializeBuffersArg = PadResetAndInitializeBuffers");

s32 func_8006F200(s32 arg0, s32 arg1, u32 arg2) {
    s32 block;
    u8 *p;
    u32 w0;
    u32 w1;
    u32 magic;
    u32 size;
    s32 status;
    u32 idx;
    u32 limit;
    s32 result;
    u32 i;
    block = arg2;
    func_800719FC(&block);
    i = 0;
    result = 1;
    D_800A3904w16 = 0;
    while (1) {
        if (i >= 4) {
            PadResetAndInitializeBuffersArg(0);
            status = PadGetButtons(0);
            if ((status & 0x840)) {
                D_800A3904w16 = status;
                result = 0;
                break;
            }
        }
        block = 8;
        p = func_800719FC(&block);
        if (p == 0) {
            goto done;
        }
        if (block == 0) {
            goto done;
        }
        idx = 8;
        w0 = ((StreamChunk *)p)->tag;
        magic = (((w0 >> 24) | ((w0 >> 8) & 0xFF00)) | ((w0 & 0xFF00) << 8)) |
                (w0 << 24);
        w1 = ((StreamChunk *)p)->size;
        size = (((w1 >> 24) | ((w1 >> 8) & 0xFF00)) | ((w1 & 0xFF00) << 8)) |
               (w1 << 24);
        if (size < 0x4400) {
            block = size;
            p = func_800719FC(&block);
            if (p == 0) {
                goto done;
            }
            if (block == 0) {
                goto done;
            }
            switch (magic) {
            case 0x564C4330:
                MediaBuildVlcLookup((s32)(p + 8));
                break;

            case 0x41643130:

            case 0x41643131:

            case 0x61643130:

            case 0x61643131:

            case 0x61643230:

            case 0x61643231:
                AudioQueueAdpcm(p);
                break;

            case 0x61753030:

            case 0x61753031:
                AudioQueueStereoAdpcm(p);
                break;

            case 0x4D444332:

            case 0x4D444543:
                idx = i;
                if (idx == 1) {
                    func_80072750();
                }
                AudioEnableStream();
                i = idx + 1;
                limit = AudioGetStreamPositionLimit(idx);
                MovieDispatchFrameUpdateArgs(p, arg0, arg1);
                while (((u32)AudioGetStreamCounter()) < limit) {
                    VSync(0);
                }

                VideoSwapDisplayAndDrawEnvironments();
                break;

            default:
                block = 4;
                break;
            }

        } else {
            block = 4;
        }
        func_800718D4(block);
    }

done:
    return result;
}

extern long SpuMalloc(long size);
extern void SpuFree(unsigned long addr);
extern void AudioDisableStream(void);
extern s32 MdecBuildVlcLookup(u8 *first, u8 *second, u8 *table);
extern s32 CdStreamInit();
extern s32 AudioInit(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                     s32 arg5, s32 arg6);
extern s32 func_800703D0(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                         s32 arg5, s32 arg6);
extern void CdStreamShutdown(void);
extern void AudioShutdown(void);
extern s32 AudioGetContextSize(void);
extern void MdecStreamShutdown(s32);
extern void func_800700F8(void);
extern s32 MdecGetBufferSize(void);
extern void func_8007012C(void);
extern s32 MediaGetBufferAllocationSize(s32, s32, s32);
extern void AudioSetStreamMode(s32);
extern s32 AudioCountActiveStreamBuffers(void);
extern s32 AudioGetSpuBufferSize(void);
extern u8 gPlayerDriver[];
extern u8 D_800A3397;
extern u8 D_800A39BC;
s32 MoviePlay(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
              s32 arg6, s32 arg7) {
    RECT rect;
    u8 result;
    void *frameBuf;
    void *vlcBuf;
    void *vlcTable;
    void *mdecBuf;
    void *cdBuf;
    void *audioCtx;
    s32 spuBuf0;
    s32 spuBuf1;
    s32 tries;

    rect.x = 0x100;
    rect.y = 0x139;
    rect.h = 7;
    rect.w = 0x40;
    MoveImage(&rect, 0x2C0, 0x19B);
    rect.x = 0x100;
    rect.y = 0x1D0;
    rect.h = 0x18;
    rect.w = 0x40;
    MoveImage(&rect, 0x2C0, 0x1D0);
    rect.x = 0x100;
    rect.y = 0x1FF;
    rect.h = 1;
    rect.w = 0x10;
    MoveImage(&rect, 0x2C0, 0x1FF);
    DrawSync(0);
    if (D_800A39BC == 0) {
        func_80063AE0(0, 0);
        func_80063AE0(1, 1);
        DrawSync(0);
    }
    rect.x = 0x280;
    rect.y = 0;
    rect.h = 0x100;
    rect.w = 0x140;
    MoveImage(&rect, 0, 0x100);
    DrawSync(0);
    frameBuf = HeapAlloc(0x20D00);
    if (frameBuf != NULL) {
        vlcBuf = HeapAlloc(0x6000);
        if (vlcBuf != NULL) {
            vlcTable = HeapAlloc(0x600);
            if (vlcTable != NULL) {
                MdecBuildVlcLookup(vlcBuf, vlcTable, NULL);
                func_800700F8();
                mdecBuf = HeapAlloc(MdecGetBufferSize());
                if (mdecBuf != NULL) {
                    if (func_800703D0(mdecBuf, frameBuf,
                                      (u8 *)frameBuf + 0xF000,
                                      (u8 *)frameBuf + 0x1E000, 1, arg5, 1)) {
                        cdBuf = HeapAlloc(
                            MediaGetBufferAllocationSize(arg6, 0x4400, arg1));
                        if (cdBuf != NULL) {
                            if (CdStreamInit(cdBuf, AudioDisableStream, arg0,
                                             arg1, 0x800)) {
                                audioCtx = HeapAlloc(AudioGetContextSize());
                                if (audioCtx != NULL) {
                                    spuBuf0 =
                                        SpuMalloc(AudioGetSpuBufferSize());
                                    if (spuBuf0 != 0) {
                                        spuBuf1 =
                                            SpuMalloc(AudioGetSpuBufferSize());
                                        if (spuBuf1 != 0) {
                                            if (AudioInit(audioCtx, 0x400000,
                                                          spuBuf0, 0x800000,
                                                          spuBuf1, arg2, 1)) {
                                                AudioSetStreamMode(0);
                                                result = func_8006F200(
                                                    arg3, arg4, arg6 * arg7);
                                                tries = 3;
                                                while (
                                                    AudioCountActiveStreamBuffers() &&
                                                    tries > 0) {
                                                    VSync(0);
                                                    tries--;
                                                }
                                                AudioShutdown();
                                            }
                                            SpuFree(spuBuf1);
                                        }
                                        SpuFree(spuBuf0);
                                    }
                                    HeapFree(audioCtx);
                                }
                                CdStreamShutdown();
                            }
                            HeapFree(cdBuf);
                        }
                        MdecStreamShutdown(result);
                    }
                    HeapFree(mdecBuf);
                }
                HeapFree(vlcTable);
            }
            HeapFree(vlcBuf);
        }
        HeapFree(frameBuf);
    }
    rect.x = 0;
    rect.y = 0x100;
    rect.h = 0x100;
    rect.w = 0x140;
    MoveImage(&rect, 0x280, 0);
    DrawSync(0);
    rect.x = 0x2C0;
    rect.y = 0x19B;
    rect.h = 7;
    rect.w = 0x40;
    MoveImage(&rect, 0x100, 0x139);
    rect.x = 0x2C0;
    rect.y = 0x1D0;
    rect.h = 0x18;
    rect.w = 0x40;
    MoveImage(&rect, 0x100, 0x1D0);
    rect.x = 0x2C0;
    rect.y = 0x1FF;
    rect.h = 1;
    rect.w = 0x10;
    MoveImage(&rect, 0x100, 0x1FF);
    DrawSync(0);
    if (D_800A39BC == 0) {
        func_80063A28();
        DrawSync(0);
        func_80063AE0(0, gPlayerDriver[0]);
        DrawSync(0);
        func_80063AE0(1, gPlayerDriver[1]);
        DrawSync(0);
    }
    if (D_800A3397 != 1) {
        func_8007012C();
    }
    return result;
}

extern void CD_initvol(void);
/* Sound output and video. */

void SoundInitOutput(void) {
    CD_initvol();
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, 0x7FFF, 0x7FFF);
    SsSetMute(0);
}

extern u8 gMovieFileModeReadBinary[];
extern s32 MoviePlay(s32, s32, s32, s32, s32, s32, s32, s32);
s32 MoviePlayFile(s32 fileId, s32 arg1, s32 arg2) {
    volatile s32 pad[14];
    void *handle;

    CD_initvol();
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, 0x7FFF, 0x7FFF);
    SsSetMute(0);
    handle = FileOpen(fileId, gMovieFileModeReadBinary);
    D_800A3397 = (u8)arg1;
    D_800A39BC = (u8)arg2;
    return MoviePlay((s32)handle, 1, 0x800, 0, 0xA, 1, 0xC8, 0x400) & 0xFF;
}

extern void SpuSetCommonAttr(SpuCommonAttr *);
void SoundSetMasterVolume(s16 left, s16 right) {
    SpuCommonAttr attr;
    attr.mvol.left = left;
    attr.mask = 3;
    attr.mvol.right = right;
    SpuSetCommonAttr(&attr);
}

/* The movie player's context, pointed to by gMovieContext. */
typedef struct MovieContext {
    RECT uploadRects[2]; /* 0x00 */
    s32 activeRect;      /* 0x10 */
    s32 unk14;
    s32 unk18;
    u16 uploadX; /* 0x1C */
    u16 uploadY;
    u16 imageWidth;
    u16 imageHeight;
    u_long *imageBuffer;   /* 0x24 */
    u32 decodeBuffers[2];  /* 0x28 */
    s32 decodeBufferIndex; /* 0x30 */
    DRAWENV draw[2];       /* 0x34 */
    DISPENV disp[2];       /* 0xEC */
    s32 displayIndex;      /* 0x114: the buffer on screen */
    s32 unk118;
    s32 uploadComplete;   /* 0x11C */
    s32 dctOutCallback;   /* 0x120 */
    s32 dctInCallback;    /* 0x124 */
    s32 drawSyncCallback; /* 0x128 */
    s32 unk12C;
} MovieContext;

extern MovieContext *gMovieContext;
extern s32 D_800A33A0;
void func_8006FAAC(void) {
    volatile MovieContext *st;
    volatile MovieContext *st2;
    s16 *ex;
    s16 *ew;
    s32 xv;
    s32 a;
    s32 b;
    s32 w;
    s32 h;
    u_long *buf;
    s32 n;

    st = (volatile MovieContext *)gMovieContext;
    LoadImage((RECT *)&st->uploadX, st->imageBuffer);
    st2 = (volatile MovieContext *)gMovieContext;
    st2->uploadX = st2->uploadX + D_800A33A0 * 8;
    xv = (s16)st2->uploadX;
    ex = &st2->uploadRects[st2->activeRect].x;
    a = *ex;
    ew = &st2->uploadRects[st2->activeRect].w;
    b = *ew;
    if (xv < a + b) {
        w = (s16)st2->imageWidth;
        h = (s16)st2->imageHeight;
        buf = st2->imageBuffer;
        n = w * h;
        DecDCTout(buf, n / 2);
    } else {
        st2->uploadComplete = 1;
        st2->activeRect = !st2->activeRect;
        st2->uploadX = (u16)st2->uploadRects[st2->activeRect].x;
        st2->uploadY = (u16)st2->uploadRects[st2->activeRect].y;
    }
}

extern void func_800708D8(void *, s32);
extern s32 D_800A339C;

/* The header of a decoded movie frame; the image follows at 0x10. */
typedef struct {
    u32 header; /* 0x00 */
    u32 unk4;
    u16 width;  /* 0x08 */
    u16 height; /* 0x0A */
    u8 unkC[4];
} MovieFrame;

void func_8006FBB0Args(u8 *frameData, s32 x, s16 y) {
    MovieContext *st;
    MovieContext *st2;
    register u32 bsw asm("$5");
    u32 nsec;
    u32 w8;
    u32 cnt;
    u32 word;
    register u32 wA asm("$3");
    u32 w8hi;
    u32 wAlo;
    u32 w8lo;
    u32 xv;
    u32 mdecId;
    register u32 prod asm("$10");
    volatile MovieContext *vst;
    u32 mdecId2;
    s32 magic;
    u32 h16u;
    s32 prod2;
    u_long *outp;
    s32 w32;
    s32 h32;
    u32 i;

    word = ((MovieFrame *)frameData)->header;
    st = gMovieContext;

    bsw = word >> 0x18;
    bsw = bsw | ((word >> 8) & 0xFF00);
    bsw = bsw | ((word & 0xFF00) << 8);
    magic = bsw | (word << 0x18);
    wA = ((MovieFrame *)frameData)->height;
    asm volatile("srl %0, %1, 8" : "=r"(cnt) : "r"(wA));
    wAlo = wA & 0xFF;
    w8 = ((MovieFrame *)frameData)->width;
    wAlo = wAlo << 8;
    bsw = cnt | wAlo;
    cnt = st->unk118;
    asm volatile("srl %0, %1, 8" : "=r"(w8hi) : "r"(w8));
    w8lo = w8 & 0xFF;
    w8lo = w8lo << 8;
    nsec = w8hi | w8lo;
    if (cnt == 0) {
        wA = D_800A33A0;
        mdecId = 0x4D444543;
        asm("" : "=r"(xv) : "0"(x));
        st->uploadRects[0].x = x;
        st->uploadRects[0].y = y;
        st->uploadRects[0].h = bsw;
        st->uploadRects[1].y = y;
        st->uploadRects[1].h = bsw;
        asm volatile("mult %0, %1" : : "r"(nsec), "r"(wA) : "lo", "hi");
        st->uploadX = xv;
        st->uploadY = y;
        do {
        } while (0);
        st->uploadRects[1].x = x + wA * 0xA0;
        st->imageWidth = wA * 8;
        st->imageHeight = bsw;
        st->activeRect = 0;
        asm volatile("mflo %0" : "=r"(prod));
        w8 = prod >> 1;
        st->uploadRects[0].w = w8;
        st->uploadRects[1].w = w8;
        if (magic == mdecId) {
            func_800708D8(frameData + 0x10,
                          (s32)st->decodeBuffers[st->decodeBufferIndex]);
        }
        ((volatile MovieContext *)gMovieContext)->uploadComplete = 0;
    } else {
        st->uploadComplete = 0;
        DecDCTin((u_long *)st->decodeBuffers[1 - st->decodeBufferIndex],
                 D_800A339C);
        st2 = gMovieContext;
        asm volatile("lhu %0, 0x20(%1)" : "=r"(bsw) : "r"(st2));
        asm volatile("lhu %0, 0x22(%1)" : "=r"(h16u) : "r"(st2));
        w32 = (s16)bsw;
        h32 = (s16)h16u;
        asm volatile("mult %0, %1" : : "r"(w32), "r"(h32) : "lo", "hi");
        outp = st2->imageBuffer;
        asm volatile("mflo %0" : "=r"(prod2));
        DecDCTout(outp, prod2 / 2);
        mdecId2 = 0x4D444543;
        if (magic == mdecId2) {
            st2 = gMovieContext;
            func_800708D8(frameData + 0x10,
                          (s32)st2->decodeBuffers[st2->decodeBufferIndex]);
        }
        DecDCToutSync(0);
        vst = (volatile MovieContext *)gMovieContext;
        i = 0;
        if (vst->uploadComplete == 0) {
            bsw = 0x30D40;
        again:
            if (i > bsw) {
                goto done;
            }
            i++;
            if (vst->uploadComplete == 0) {
                goto again;
            }
        }
    }
done:
    DecDCTReset(1);
    gMovieContext->unk118 = gMovieContext->unk118 + 1;
    gMovieContext->decodeBufferIndex = 1 - gMovieContext->decodeBufferIndex;
}
asm(".globl func_8006FBB0\nfunc_8006FBB0 = func_8006FBB0Args");

void func_8006FDDC(u8 *frameData, s32 x, s16 y) {
    RECT rect;
    volatile s32 pad[2];
    u32 word;
    u32 wA;
    u32 w8;
    s32 magic;
    s32 height16;
    s32 output;
    u32 i;
    MovieContext *str;
    u32 nsectors16;
    s32 stride;

    word = ((MovieFrame *)frameData)->header;
    w8 = ((MovieFrame *)frameData)->width;
    wA = ((MovieFrame *)frameData)->height;
    magic = (word >> 24) | ((word >> 8) & 0xFF00) | ((word & 0xFF00) << 8) |
            (word << 0x18);
    rect.y = y;
    str = gMovieContext;
    height16 = (wA >> 8) | ((wA & 0xFF) << 8);
    rect.x = (u32)(x * D_800A33A0) >> 1;
    nsectors16 = (w8 >> 8) | ((w8 & 0xFF) << 8);
    if (str->displayIndex != 0) {
        rect.x = rect.x + D_800A33A0 * 0xA0;
    }
    rect.w = D_800A33A0 * 8;
    rect.h = height16;
    if (str->unk118 == 0) {
        if (magic == 0x4D444543) {
            func_800708D8(frameData + 0x10,
                          str->decodeBuffers[str->decodeBufferIndex]);
        }
        ((volatile MovieContext *)gMovieContext)->uploadComplete = 0;
    } else {
        output = (s32)str->imageBuffer;
        DecDCTin((u_long *)str->decodeBuffers[1 - str->decodeBufferIndex],
                 D_800A339C);
        stride = D_800A33A0 * 8;
        DecDCTout((u_long *)output,
                  ((u32)(height16 * stride) >> 1) * (nsectors16 >> 4));
        if (magic == 0x4D444543) {
            func_800708D8(
                frameData + 0x10,
                gMovieContext->decodeBuffers[gMovieContext->decodeBufferIndex]);
        }
        DecDCToutSync(0);
        i = 0;
        if (nsectors16 != 0) {
            do {
                LoadImage(&rect, (u_long *)output);
                i += 0x10;
                rect.x = (u16)rect.x + D_800A33A0 * 8;
                output += rect.w * rect.h * 2;
            } while (i < nsectors16);
        }
        gMovieContext->uploadComplete = 1;
    }
    DecDCTReset(1);
    gMovieContext->unk118 = gMovieContext->unk118 + 1;
    gMovieContext->decodeBufferIndex = 1 - gMovieContext->decodeBufferIndex;
}

void func_8006FBB0(void);
extern void func_8006FDDCNoArgs(void);
asm(".globl func_8006FDDCNoArgs\nfunc_8006FDDCNoArgs = func_8006FDDC");
void MovieDispatchFrameUpdate(void) {
    if (gMovieContext->unk12C)
        func_8006FBB0();
    else
        func_8006FDDCNoArgs();
}

void VideoSwapDisplayAndDrawEnvironments(void) {
    s32 *s;
    s32 *s2;
    s32 other;

    if (gMovieContext->uploadComplete != 0) {
        DrawSync(0);
        VSync(0);
        s = gMovieContext;
        PutDispEnv((DISPENV *)((u8 *)s + (s[0x114 / 4] * 20 + 0xEC)));
        s2 = gMovieContext;
        other = 1 - s2[0x114 / 4];
        s2[0x114 / 4] = other;
        PutDrawEnv((DRAWENV *)((u8 *)s2 + (other * 92 + 0x34)));
    }
}

void func_800700F8(void) {
    D_800A339C = 1;
    D_800A33A0 = 3;
}

void func_80070110(void) {
    D_800A339C = 2;
    D_800A33A0 = 2;
}

s32 MdecGetBufferSize(void) {
    return 0x130;
}

extern void DrawPrim(void *pri);

void func_8007012C(void) {
    s32 i;
    TILE tile;
    DRAWENV env;
    DISPENV disp;

    for (i = 0; i < 2; i++) {
        SetDefDrawEnv(&env, (0 - (i != 0)) & 0x140, 0, 0x140, 0xF0);
        PutDrawEnv(&env);
        SetDefDispEnv(&disp, (0 - (i == 0)) & 0x140, 0, 0x140, 0xF0);
        PutDispEnv(&disp);
        setBlockFill(&tile);
        tile.x0 = 0;
        tile.y0 = 0;
        tile.w = 0x140;
        tile.h = 0xF0;
        if (D_800A3397 != 0) {
            tile.r0 = 0xFF;
            tile.g0 = 0xFF;
            tile.b0 = 0xFF;
        } else {
            tile.r0 = 0;
            tile.g0 = 0;
            tile.b0 = 0;
        }
        DrawSync(0);
        VSync(0);
        DrawPrim(&tile);
        DrawSync(0);
    }
}

extern void SwEnterCriticalSection(void);
extern void SwExitCriticalSection(void);

void MdecStreamShutdown(s32 arg0) {
    TILE tile;
    DRAWENV env;
    DISPENV disp;

    if (gMovieContext != 0) {
        D_800A3578[0] = (u8)gMovieContext->displayIndex;
        DecDCTinSync(0);
        DecDCToutSync(0);
        DrawSync(0);
        SwEnterCriticalSection();
        DecDCToutCallback((void (*)(void))gMovieContext->dctOutCallback);
        DecDCTinCallback((void (*)(void))gMovieContext->dctInCallback);
        DrawSyncCallback((void (*)())gMovieContext->drawSyncCallback);
        gMovieContext->dctOutCallback = 0;
        gMovieContext->dctInCallback = 0;
        gMovieContext->drawSyncCallback = 0;
        SwExitCriticalSection();
        DecDCTReset(1);
        if (D_800A3397 == 1 && (arg0 & 0xFF)) {
            SetDefDrawEnv(&env, 0, 0, 0x140, 0xF0);
            PutDrawEnv(&env);
            setBlockFill(&tile);
            tile.w = 0x140;
            tile.h = 0xF0;
            tile.x0 = 0;
            tile.y0 = 0;
            tile.r0 = 0xFF;
            tile.g0 = 0xFF;
            tile.b0 = 0xFF;
            DrawSync(0);
            VSync(0);
            DrawPrim(&tile);
            DrawSync(0);
            SetDefDispEnv(&disp, 0, 0, 0x140, 0xF0);
            PutDispEnv(&disp);
        } else {
            SetDispMask(0);
        }
        gMovieContext = 0;
    }
}

extern void bzero(void *, s32);
extern u32 D_800A33B0[];

s32 func_800703D0(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                  s32 arg6) {
    TILE tile;
    s32 pos;
    s32 i;

    if (arg0 != 0) {
        if (arg1 != 0 && arg2 != 0 && arg3 != 0) {
            bzero(arg0, 0x130);
            gMovieContext = arg0;
            DrawSync(0);
            DecDCTinSync(0);
            DecDCToutSync(0);
            SetDispMask(0);
            if (arg5 != 0) {
                setBlockFill(&tile);
                for (i = 0, pos = 0; i < 2; i++) {
                    tile.y0 = 0;
                    tile.h = 0xF0;
                    tile.r0 = 0;
                    tile.g0 = 0;
                    tile.b0 = 0;
                    tile.w = D_800A33A0 * 0xA0;
                    tile.x0 = D_800A33A0 * pos;
                    pos = pos + 0xA0;
                    DrawSync(0);
                    VSync(0);
                    DrawPrim(&tile);
                    DrawSync(0);
                }
            }
            SetDefDrawEnv(&gMovieContext->draw[0], 0, 0, 0x140, 0xF0);
            SetDefDispEnv(&gMovieContext->disp[0], 0, 0, 0x140, 0xF0);
            SetDefDrawEnv(&gMovieContext->draw[1], D_800A33A0 * 0xA0, 0, 0x140,
                          0xF0);
            SetDefDispEnv(&gMovieContext->disp[1], D_800A33A0 * 0xA0, 0, 0x140,
                          0xF0);
            if (D_800A339C == 1) {
                gMovieContext->disp[0].isrgb24 = 1;
                gMovieContext->disp[1].isrgb24 = 1;
            } else {
                gMovieContext->disp[0].isrgb24 = 0;
                gMovieContext->disp[1].isrgb24 = 0;
            }
            gMovieContext->disp[0].isinter = 0;
            gMovieContext->disp[1].isinter = 0;
            gMovieContext->displayIndex = 0;
            *(u16 *)&gMovieContext->disp[0].screen.y = 0;
            *(u16 *)&gMovieContext->disp[1].screen.y = 0;
            if (arg6 != 0) {
                VSync(0);
                PutDrawEnv(
                    &gMovieContext->draw[1 - gMovieContext->displayIndex]);
                PutDispEnv(
                    &gMovieContext->disp[1 - gMovieContext->displayIndex]);
                SetDispMask(1);
            }
            gMovieContext->decodeBuffers[0] = arg1;
            gMovieContext->decodeBuffers[1] = arg2;
            gMovieContext->imageBuffer = arg3;
            DecDCTReset(0);
            SwEnterCriticalSection();
            gMovieContext->unk12C = arg4;
            if (arg4 != 0) {
                gMovieContext->dctOutCallback =
                    DecDCToutCallback(func_8006FAAC);
                gMovieContext->dctInCallback = DecDCTinCallback(0);
                gMovieContext->drawSyncCallback = DrawSyncCallback(0);
                if (D_800A339C == 1) {
                    D_800A33B0[0] = D_800A339C;
                }
            } else {
                s32 cb;

                gMovieContext->dctOutCallback = DecDCToutCallback(0);
                gMovieContext->dctInCallback = DecDCTinCallback(0);
                cb = DrawSyncCallback(0);
                D_800A33B0[0] = 0;
                gMovieContext->drawSyncCallback = cb;
            }
            SwExitCriticalSection();
            return 1;
        }
    }
    return 0;
}

extern u8 *D_800A33A8;
extern u8 *D_800A33AC;
extern u8 D_8009B800[];
void MediaBuildVlcLookup(s32 arg) {
    if (arg != 0) {
        MdecBuildVlcLookup(D_800A33A8, D_800A33AC, (u8 *)arg);
    } else {
        MdecBuildVlcLookup(D_800A33A8, D_800A33AC, D_8009B800);
    }
}

extern u8 D_8009B480[];
extern u8 D_8009B600[];

/* Builds two decode lookup tables: for each code entry, fills 1 << (bits - len)
   slots with the code's length (u8 array) and value (u16 array after it). */
s32 MdecBuildVlcLookup(u8 *dst, u8 *dst2, u8 *src) {
    s32 pad[4];
    u8 *cursor;
    u16 *vals;
    s32 i;

    D_800A33A8 = dst;
    D_800A33AC = dst2;
    if (dst == 0) {
        return -1;
    }
    if (dst2 == 0) {
        return -1;
    }
    vals = (u16 *)(dst + 0x2000);
    if (src == 0) {
        src = D_8009B800;
    }
    {
        u8 *lenPtr;
        u8 *codePtr;
        s32 j;
        s32 count;
        s32 bits;
        s32 one;
        s32 base;
        s32 off;
        u16 val;
        u8 len;
        u8 *entries;

        i = 0;
        bits = 13;
        one = 1;
        entries = D_8009B480;
        codePtr = entries + 2;
        lenPtr = entries;
        cursor = src;
        while (i < 0x60) {
            val = *(u16 *)cursor;
            len = *lenPtr;
            cursor += 2;
            j = 0;
            count = one << (bits - len);
            base = *(u16 *)codePtr >> 3;
            if (count > 0) {
                do {
                    off = base | j;
                    *(u8 *)(dst + off) = len;
                    vals[off] = val;
                    j++;
                } while (j < count);
            }
            codePtr += 4;
            lenPtr += 4;
            i++;
        }
    }
    {
        u8 *lenPtr;
        u8 *codePtr;
        s32 j;
        s32 count;
        s32 bits;
        s32 one;
        s32 base;
        s32 off;
        u16 val;
        u8 len;
        u8 *entries;
        u8 *cursor2;

        dst = dst2;
        vals = (u16 *)(dst + 0x200);
        i = 0;
        bits = 9;
        one = 1;
        entries = D_8009B600;
        codePtr = entries + 2;
        lenPtr = entries;
        cursor2 = cursor;
        while (i < 0x80) {
            val = *(u16 *)cursor2;
            len = *lenPtr;
            cursor2 += 2;
            j = 0;
            count = one << (bits - len);
            base = *(u16 *)codePtr >> 7;
            if (count > 0) {
                do {
                    off = base | j;
                    *(u8 *)(dst + off) = len;
                    vals[off] = val;
                    j++;
                } while (j < count);
            }
            codePtr += 4;
            lenPtr += 4;
            i++;
        }
    }
    return 0;
}

extern s32 func_800708D8Ret(void *arg0, s32 arg1);
asm(".globl func_800708D8\nfunc_800708D8 = func_800708D8Ret");

s32 func_800708D8Ret(void *source, s32 outputAddress) {
    u16 *src;
    u16 *out;
    u8 *tbl1;
    u8 *tbl2;
    u16 *tbl1v;
    u16 *tbl2v;
    u32 bits;
    u32 quant;
    u32 block;
    register u32 nw asm("$7");
    register u32 nw2 asm("$4");
    u32 nwp;
    u32 sym;
    u32 len;
    u32 bitpos;
    u8 *lenp;
    u32 scale;
    u32 hdr;

    src = (u16 *)source;
    out = (u16 *)outputAddress;
    tbl1 = D_800A33A8;
    tbl2 = D_800A33AC;
    bitpos = 0;
    out[0] = src[0];
    nw = src[1];
    tbl1v = (u16 *)(tbl1 + 0x2000);
    tbl2v = (u16 *)(tbl2 + 0x200);
    out++;
    *out++ = nw;
    quant = src[2] << 10;
    nwp = src[4];
    nwp <<= 16;
    nw2 = src[5];
    bits = nwp | nw2;
    src += 6;
    block = bits >> 22;

outer_loop:
    if (block == 0x1FF)
        goto done;
    bitpos += 10;
    bits <<= 10;
    if (bitpos & 0x10) {
        nw = *src;
        bitpos &= 0xF;
        src++;
        bits |= nw << bitpos;
    } else {
        bitpos &= 0xF;
    }
    hdr = block | quant;
    *out++ = hdr;
inner_loop:
    block = bits >> 19;
    if (block < 0x20) {
        bitpos += 8;
        bits <<= 8;
        if (bitpos & 0x10) {
            nw2 = *src;
            bitpos &= 0xF;
            src++;
            bits |= nw2 << bitpos;
        } else {
            bitpos &= 0xF;
        }
        block = bits >> 23;
        lenp = tbl2 + block;
        scale = block * 2;
        nw = (u32)((u8 *)tbl2v + scale);
    } else {
        lenp = tbl1 + block;
        scale = block * 2;
        nw = (u32)((u8 *)tbl1v + scale);
    }
    sym = *(u16 *)nw;
    do {
    } while (0);
    len = *lenp;
    bits <<= len;
    bitpos += len;
    if (bitpos & 0x10) {
        nw2 = *src;
        bitpos &= 0xF;
        src++;
        bits |= nw2 << bitpos;
    } else {
        bitpos &= 0xF;
    }
    if (sym == 0x7C1F)
        goto escape;
    *out++ = sym;
    if (sym != 0xFE00)
        goto inner_loop;
    block = bits >> 22;
    goto outer_loop;
escape:
    *out++ = bits >> 16;
    nw2 = *src++;
    bits <<= 16;
    bits |= nw2 << bitpos;
    goto inner_loop;
done:
    bits = 0x40;
    do {
        *out++ = 0xFE00;
        bits--;
    } while (bits != 0);
    return 0;
}

extern s32 *gCdStream;

/* CD ready callback: on each data-ready interrupt, copy the sector into the
 * stream buffer, or re-seek and re-read when the drive returned the wrong
 * sector. */
extern u32 D_800A33B0Small;
extern volatile u32 *D_800A33B4;
extern s32 D_800A3510;
#define STREAM ((volatile s32 *)gCdStream)

void CdStreamReadyCallback(u8 intr, u8 *result) {
    CdlLOC loc[8];
    s32 *record;
    CdlLOC *loc2;
    u8 *position;
    s32 sector;
    s32 pos;
    s32 i;
    s32 used;
    s32 limit;
    s32 avail;
    s32 contiguous;
    register s32 base asm("a0");
    s32 size;
    s32 n;
    s32 test;
    register s32 availReg asm("t1");
    s32 contiguousReg;
    volatile s32 *stream;

    if (intr != CdlDataReady) {
        ++STREAM[0x424 / 4];
        return;
    }
    if ((u32)STREAM[0x424 / 4] >= 2) {
        return;
    }
    STREAM[0x424 / 4] = 0;
    if (STREAM[0x414 / 4] != 2) {
        return;
    }
    if (STREAM[0] == 0) {
        return;
    }
    if (D_800A33B0Small != 0) {
        i = 0;
        while (*D_800A33B4 & 0x1000000) {
            if (++i == 0x10001) {
                break;
            }
        }
    }
    if (STREAM[1] & 3) {
        goto error;
    }
    CdGetSector(loc, 3);
    CdDataSync(0);
    pos = CdPosToInt(loc);
    position = (u8 *)gCdStream[0x430 / 4];
    loc2 = (CdlLOC *)(position + 0xC);
    sector = ((s32 *)position)[2];
    position += 0x24;
    CdIntToPos(CdPosToInt(loc2) + sector, (CdlLOC *)position);
    if (CdPosToInt((CdlLOC *)((s32 *)gCdStream[0x430 / 4] + 9)) != pos) {
        CdGetSector((void *)gCdStream[1], 0x200);
        CdDataSync(0);
        CdGetSector(gCdStream + 0x458 / 4, 0x46);
        CdDataSync(0);
        position = (u8 *)gCdStream[0x430 / 4];
        loc2 = (CdlLOC *)(position + 0xC);
        sector = ((s32 *)position)[2];
        position += 0x24;
        CdIntToPos(CdPosToInt(loc2) + sector, (CdlLOC *)position);
        ++STREAM[0x428 / 4];
        STREAM[0x418 / 4] = 2;
        STREAM[0x414 / 4] = 1;
        position = (u8 *)gCdStream[0x430 / 4] + 0x24;
        ((s32 *)STREAM)[STREAM[0x40C / 4]++ + 2] = CdlSeekL;
        ((s32 *)STREAM)[STREAM[0x40C / 4]++ + 2] = (s32)position;
        ((s32 *)STREAM)[STREAM[0x40C / 4]++ + 2] = 0;
        STREAM[0x40C / 4] = (u32)STREAM[0x40C / 4] % 48;
        ++STREAM[0x410 / 4];
        if (STREAM[0x410 / 4] == 1) {
            while (CdControlF(CdlSeekL, position) == 0) {
            }
        }
        STREAM[0x450 / 4] = gCdStream[1];
        STREAM[0x454 / 4] = gCdStream[0];
        position = (u8 *)gCdStream[0x430 / 4] + 0x24;
        ((s32 *)STREAM)[STREAM[0x40C / 4]++ + 2] = CdlReadN;
        ((s32 *)STREAM)[STREAM[0x40C / 4]++ + 2] = (s32)position;
        ((s32 *)STREAM)[STREAM[0x40C / 4]++ + 2] = 0;
        STREAM[0x40C / 4] = (u32)STREAM[0x40C / 4] % 48;
        ++STREAM[0x410 / 4];
        if (STREAM[0x410 / 4] == 1) {
            while (CdControlF(CdlReadN, position) == 0) {
            }
        }
        return;
    }
    CdGetSector((void *)gCdStream[1], 0x200);
    CdDataSync(0);
    CdGetSector(gCdStream + 0x458 / 4, 0x46);
    CdDataSync(0);
    stream = STREAM;
    --stream[0];
    stream[1] += 0x800;
    ++((volatile s32 *)((s32 *)stream)[0x430 / 4])[2];
    ++stream[0x448 / 4];
    if (stream[0] != 0) {
        return;
    }
    record = (s32 *)stream[0x430 / 4];
    pos = stream[0];
    limit = record[0] - (((volatile s32 *)record)[2] + pos);
    used = stream[0x448 / 4] + pos;
    size = D_800A3510;
    n = used;
    n = stream[0x440 / 4] + size - n;
    contiguous = size - (u32)used % size;
    avail = n;
    availReg = avail;
    contiguousReg = contiguous;
    /* Keep the minimum operands in the retail registers. */
    test = avail < contiguous;
    if (test) {
        n = avail;
    } else {
        n = contiguous;
    }
    if (n < limit) {
        limit = n;
    }
    if (limit != 0) {
        base = record[0x30 / 4];
        do {
            if (stream[1] == base + (size << 11)) {
                stream[1] = base;
            }
        } while (0);
        STREAM[0] = limit;
        return;
    }
    stream[0] = 0;
    stream[0x414 / 4] = 0;
    return;
error:
    STREAM[0x414 / 4] = 0;
}
#undef STREAM

void func_80070F40(u_char intr, u_char *result) {
    volatile s32 *stream;
    volatile s32 *p;
    s32 cmd;
    s32 parm;
    s32 first;
    s32 second;
    s32 third;
    s32 pad;

    if (intr != CdlComplete) {
        ((volatile s32 *)gCdStream)[0x424 / 4] =
            ((volatile s32 *)gCdStream)[0x424 / 4] + 1;
        ((volatile s32 *)gCdStream)[0x424 / 4];
        return;
    }
    stream = (volatile s32 *)gCdStream;
    if ((u32)stream[0x424 / 4] < 2) {
        stream[0x424 / 4] = 0;
        if (stream[0x41C / 4] == 0)
            return;
        if (stream[0x410 / 4] == 0)
            return;
        if (stream[0x418 / 4] != 0) {
            stream[0x418 / 4] = stream[0x418 / 4] - 1;
            pad = stream[0x418 / 4];
            if (stream[0x418 / 4] == 0) {
                first = stream[0x450 / 4];
                second = stream[0x454 / 4];
                stream[0x4 / 4] = first;
                stream[0x0 / 4] = second;
                stream[0x414 / 4] = intr;
            }
        }
        stream = (volatile s32 *)gCdStream;
        stream[0x410 / 4] = stream[0x410 / 4] - 1;
        pad = stream[0x410 / 4];
        stream[0x408 / 4] = stream[0x408 / 4] + 3;
        stream[0x408 / 4] = (u32)stream[0x408 / 4] % 48;
        if (stream[0x410 / 4] != 0) {
            third = stream[stream[0x408 / 4] + 2];
            p = stream + stream[0x408 / 4];
            parm = p[3];
            cmd = third;
            p = stream + stream[0x408 / 4];
            pad = p[4];
            while (CdControlF((u_char)cmd, (u_char *)parm) == 0) {
            }
        }
    }
}

extern s32 D_800A3504;
extern s32 D_800A3508;
extern s32 D_800A350C;
s32 func_800710D8(void) {
    s32 *stream;
    s32 *base;
    u32 index;
    s32 *reset;
    s32 *last;
    s32 *lastRecord;
    s32 status;

    stream = gCdStream;
    status = stream[0x43C / 4];
    if (status != 0) {
        return status;
    }
    index = stream[0x434 / 4];
    if (index < (u32)stream[0x438 / 4]) {
        last = (s32 *)(D_800A3504 + index * 0x38);
        stream[0x430 / 4] = (s32)last;
        if (stream[0x42C / 4] == 0) {
            stream[0x42C / 4] = (s32)last;
        }
        base = gCdStream;
        last = (s32 *)base[0x430 / 4];
        last[0] = (u32)(last[0x10 / 4] + 0x7FF) >> 11;
        reset = (s32 *)base[0x430 / 4];
        reset[1] = 0;
        reset = (s32 *)base[0x430 / 4];
        reset[2] = 0;
        reset = (s32 *)base[0x430 / 4];
        reset[0x28 / 4] = 0;
        if (base[0x434 / 4] == 0) {
            base[0x444 / 4] = 0;
            base[0x440 / 4] = 0;
            base[0x448 / 4] = 0;
            base[0x44C / 4] = 0;
        }
        last = gCdStream;
        last[0x434 / 4] += 1;
        lastRecord = (s32 *)last[0x430 / 4];
        lastRecord[0x34 / 4] = 0;
        lastRecord = (s32 *)last[0x430 / 4];
        lastRecord[0x2C / 4] = D_800A3508;
        lastRecord = (s32 *)last[0x430 / 4];
        lastRecord[0x30 / 4] = D_800A350C;
        last[0x43C / 4] = 0;
    } else {
        stream[0x43C / 4] = 2;
    }
    return gCdStream[0x43C / 4];
}

extern void func_80070F40(u8, u8 *);
extern void CdStreamReadyCallback(u8, u8 *);

void CdUpdateStream(void) {
    u8 param[0x20];
    u8 result[0x20];
    u8 mode;
    u8 *clearResult;
    u8 *controlResult;
    CdlLOC *loc;
    s32 completeStatus;
    s32 test;
    s32 requestState;
    u8 *pendingPosition;
    s32 readSectors;
    s32 availableSectors;
    s32 availableLimit;
    s32 contiguousSectors;
    s32 remainingSectors;
    register s32 *restartRecord asm("a0");
    s32 *activeRecord;
    s32 *refillRecord;
    s32 *bufferRecord;
    register u8 *restartPosition asm("s0");
    register u8 *refillPosition asm("s0");
    u8 *readPosition;
    s32 *initialStream;
    s32 *stoppedStream;
    s32 *startedStream;
    s32 *restartStream;
    s32 *restartSeekStream;
    s32 *restartReadStream;
    s32 *serviceStream;
    s32 *ringStream;
    register s32 *refillSeekStream asm("v1");
    register s32 *refillReadStream asm("a0");
    volatile s32 *restartSeekQueue;
    volatile s32 *restartReadQueue;
    volatile s32 *refillSeekQueue;
    volatile s32 *refillReadQueue;
    u32 bufferSector;
    s32 bufferBase;
    s32 *restartReadRecord;
    s32 readBuffer;
    s32 unusedPending;
    s32 restartSector;
    s32 refillSector;
    void (*callback)(void);
    register CdlCB noCallback asm("a0");

    initialStream = gCdStream;
    if ((u32)initialStream[0x424 / 4] >= 2) {
        callback = (void (*)(void))initialStream[0x570 / 4];
        if (callback != 0) {
            callback();
        }
        completeStatus = CdlComplete;
        SwEnterCriticalSection();
        asm("" : : "r"(completeStatus));
        stoppedStream = gCdStream;
        noCallback = 0;
        asm("" : : "r"(noCallback));
        stoppedStream[0x410 / 4] = 0;
        stoppedStream[0x408 / 4] = 0;
        stoppedStream[0x40C / 4] = 0;
        ((volatile s32 *)stoppedStream)[0x41C / 4] = 0;
        CdSyncCallback(noCallback);
        CdReadyCallback(0);
        SwExitCriticalSection();
        CdControl(CdlStop, 0, 0);
        do {
            bzero(param, 0x20);
            clearResult = result;
            bzero(clearResult, 0x20);
            clearResult = 0;
            controlResult = result;
            test = CdControl(CdlNop, param, controlResult);
            controlResult = 0;
            if (test != 0) {
                if (result[0] == CdlNoIntr || result[0] == completeStatus) {
                    test = 0;
                } else {
                    test = 1;
                }
            } else {
                CdControl(CdlReset, 0, 0);
                test = 1;
            }
        } while (test != 0);
        mode = CdlModeSpeed | CdlModeSize1;
        CdControlB(CdlSetmode, &mode, 0);
        SwEnterCriticalSection();
        CdSyncCallback(func_80070F40);
        CdReadyCallback(CdStreamReadyCallback);
        startedStream = gCdStream;
        startedStream[0x41C / 4] = 1;
        startedStream[0x414 / 4] = 1;
        ((volatile s32 *)startedStream)[0x424 / 4] = 0;
        SwExitCriticalSection();
        restartStream = gCdStream;
        if (restartStream[0x414 / 4] != 0 && restartStream[0] != 0) {
            restartPosition = (u8 *)restartStream[0x430 / 4];

            restartSector = ((s32 *)restartPosition)[2];
            loc = (CdlLOC *)(restartPosition + 0xC);
            restartPosition += 0x24;
            CdIntToPos(CdPosToInt(loc) + restartSector,
                       (CdlLOC *)restartPosition);
            restartSeekStream = gCdStream;
            restartRecord = (s32 *)restartSeekStream[0x430 / 4];
            restartSeekStream[0x418 / 4] = 2;
            restartPosition = (u8 *)restartRecord + 0x24;

            SwEnterCriticalSection();
            restartSeekQueue = (volatile s32 *)gCdStream;
            ((s32 *)restartSeekQueue)[restartSeekQueue[0x40C / 4]++ + 2] =
                CdlSeekL;
            ((s32 *)restartSeekQueue)[restartSeekQueue[0x40C / 4]++ + 2] =
                (s32)restartPosition;
            ((s32 *)restartSeekQueue)[restartSeekQueue[0x40C / 4]++ + 2] = 0;
            restartSeekQueue[0x40C / 4] = (u32)restartSeekQueue[0x40C / 4] % 48;
            restartSeekQueue[0x410 / 4] += 1;
            unusedPending = restartSeekQueue[0x410 / 4];
            if (restartSeekQueue[0x410 / 4] == 1) {
                SwExitCriticalSection();
                while (CdControl(CdlSeekL, restartPosition, 0) == 0) {
                }
            } else {
                SwExitCriticalSection();
            }
            restartReadStream = gCdStream;
            readBuffer = restartReadStream[1];
            restartReadRecord = (s32 *)restartReadStream[0x430 / 4];
            readSectors = restartReadStream[0];
            restartPosition = (u8 *)restartReadRecord + 0x24;
            restartReadStream[0x450 / 4] = readBuffer;
            restartReadStream[0x454 / 4] = readSectors;
            asm(""
                :
                : "r"(readBuffer), "r"(restartReadRecord), "r"(restartPosition),
                  "r"(readSectors)
                : "memory");
            SwEnterCriticalSection();
            restartReadQueue = (volatile s32 *)gCdStream;
            ((s32 *)restartReadQueue)[restartReadQueue[0x40C / 4]++ + 2] =
                CdlReadN;
            ((s32 *)restartReadQueue)[restartReadQueue[0x40C / 4]++ + 2] =
                (s32)restartPosition;
            ((s32 *)restartReadQueue)[restartReadQueue[0x40C / 4]++ + 2] = 0;
            restartReadQueue[0x40C / 4] = (u32)restartReadQueue[0x40C / 4] % 48;
            restartReadQueue[0x410 / 4] += 1;
            unusedPending = restartReadQueue[0x410 / 4];
            if (restartReadQueue[0x410 / 4] == 1) {
                SwExitCriticalSection();
                while (CdControl(CdlReadN, restartPosition, 0) == 0) {
                }
            } else {
                SwExitCriticalSection();
            }
        } else {
            gCdStream[0x414 / 4] = 0;
        }
    }
    serviceStream = gCdStream;
    if (serviceStream[0x414 / 4] == 0) {
        activeRecord = (s32 *)serviceStream[0x430 / 4];
        remainingSectors = activeRecord[0] - activeRecord[2];
        if (remainingSectors == 0) {
            func_800710D8();
        }
        ringStream = gCdStream;
        contiguousSectors = D_800A3510;
        availableSectors =
            (((volatile s32 *)ringStream)[0x440 / 4] + contiguousSectors) -
            ((volatile s32 *)ringStream)[0x448 / 4];
        availableLimit =
            (u32)((volatile s32 *)ringStream)[0x448 / 4] % contiguousSectors;
        contiguousSectors -= availableLimit;
        /* Keep both values until the minimum has been selected. */
        availableLimit = availableSectors;
        asm(""
            : "=r"(availableLimit)
            : "0"(availableLimit), "r"(availableSectors),
              "r"(contiguousSectors));
        test = availableLimit < contiguousSectors;
        if (test) {
            availableSectors = availableLimit;
        } else {
            availableSectors = contiguousSectors;
        }
        readSectors = remainingSectors;
        if (availableSectors < readSectors) {
            readSectors = availableSectors;
        }
        if (readSectors != 0) {
            refillPosition = (u8 *)gCdStream[0x430 / 4];

            refillSector = ((s32 *)refillPosition)[2];
            loc = (CdlLOC *)(refillPosition + 0xC);
            refillPosition += 0x24;
            CdIntToPos(CdPosToInt(loc) + refillSector,
                       (CdlLOC *)refillPosition);
            refillSeekStream = gCdStream;
            refillRecord = (s32 *)refillSeekStream[0x430 / 4];
            refillSeekStream[0x44C / 4] =
                refillSeekStream[0x448 / 4] + readSectors;
            asm("" : : : "v0", "memory");
            requestState = 2;
            pendingPosition = (u8 *)refillRecord + 0x24;
            asm("" : "=r"(refillRecord) : "0"(refillRecord), "r"(requestState));
            refillPosition = pendingPosition;
            refillSeekStream[0x418 / 4] = requestState;
            asm(""
                :
                : "r"(refillRecord), "r"(refillPosition), "r"(refillSeekStream)
                : "memory");
            SwEnterCriticalSection();
            refillSeekQueue = (volatile s32 *)gCdStream;
            ((s32 *)refillSeekQueue)[refillSeekQueue[0x40C / 4]++ + 2] =
                CdlSeekL;
            ((s32 *)refillSeekQueue)[refillSeekQueue[0x40C / 4]++ + 2] =
                (s32)refillPosition;
            ((s32 *)refillSeekQueue)[refillSeekQueue[0x40C / 4]++ + 2] = 0;
            refillSeekQueue[0x40C / 4] = (u32)refillSeekQueue[0x40C / 4] % 48;
            refillSeekQueue[0x410 / 4] += 1;
            unusedPending = refillSeekQueue[0x410 / 4];
            if (refillSeekQueue[0x410 / 4] == 1) {
                SwExitCriticalSection();
                while (CdControl(CdlSeekL, refillPosition, 0) == 0) {
                }
            } else {
                SwExitCriticalSection();
            }
            refillReadStream = gCdStream;

            bufferRecord = (s32 *)refillReadStream[0x430 / 4];
            do {
                bufferSector = (u32)(refillReadStream[0x448 / 4] +
                                     bufferRecord[0x34 / 4]) %
                               D_800A3510;
                bufferBase = bufferRecord[0x30 / 4];

                refillReadStream[0x414 / 4] = 1;
                readPosition = (u8 *)refillReadStream[0x430 / 4] + 0x24;
                readBuffer = bufferBase + (bufferSector << 11);
                do {
                    /* Publish the buffer address before its sector count. */
                    refillReadStream[0x450 / 4] = readBuffer;
                } while (0);

                refillReadStream[0x454 / 4] = readSectors;
            } while (0);
            asm("" : : "r"(readBuffer), "r"(readPosition) : "memory");
            SwEnterCriticalSection();
            refillReadQueue = (volatile s32 *)gCdStream;
            ((s32 *)refillReadQueue)[refillReadQueue[0x40C / 4]++ + 2] =
                CdlReadN;
            ((s32 *)refillReadQueue)[refillReadQueue[0x40C / 4]++ + 2] =
                (s32)readPosition;
            ((s32 *)refillReadQueue)[refillReadQueue[0x40C / 4]++ + 2] = 0;
            refillReadQueue[0x40C / 4] = (u32)refillReadQueue[0x40C / 4] % 48;
            refillReadQueue[0x410 / 4] += 1;
            unusedPending = refillReadQueue[0x410 / 4];
            if (refillReadQueue[0x410 / 4] == 1) {
                SwExitCriticalSection();
                while (CdControl(CdlReadN, readPosition, 0) == 0) {
                }
            } else {
                SwExitCriticalSection();
            }
        }
    }
}

/* All registers match after separating stream phases and reloading the
 * global stream before the tail update. An empty compiler barrier keeps the
 * fast-path store out of the jump delay slot. */
extern void CdUpdateStream(void);
void func_800718D4(s32 arg) {
    s32 remaining;
    s32 offset;
    s32 blocks;
    s32 oldBlocks;
    s32 *stream;
    s32 *node;
    s32 *tail;
    s32 *tailNode;
    s32 *current;
    s32 *after;
    stream = gCdStream;
    node = (s32 *)stream[0x42C / 4];
    do {
        offset = stream[0x444 / 4];
        do {
            node[0x4 / 4] += arg;
        } while (0);
    } while (0);
    remaining = 0x800 - offset;
    if (arg < remaining) {
        do {
            stream[0x444 / 4] = stream[0x444 / 4] + arg;
            asm volatile("");
        } while (0);
    } else {
        arg -= remaining;
        do {
            stream[0x444 / 4] = arg & 0x7FF;
        } while (0);
        oldBlocks = stream[0x440 / 4];
        blocks = (((u32)arg) >> 11) + 1;
        stream[0x440 / 4] = oldBlocks + blocks;
    }
    CdUpdateStream();
    after = gCdStream;
    current = (s32 *)after[0x42C / 4];
    if (current[0x4 / 4] == current[0x10 / 4]) {
        if (((s32 *)after[0x430 / 4]) != current) {
            if (after[0x444 / 4] != 0) {
                after[0x440 / 4] += 1;
            }
            tail = gCdStream;
            tailNode = (s32 *)tail[0x430 / 4];
            tail[0x44C / 4] = 0;
            tail[0x42C / 4] = (s32)tailNode;
            tail[0x444 / 4] = tailNode[0x28 / 4];
        }
    }
}

s32 CdStreamAvailable(void) {
    return (gCdStream[0x448 / 4] << 11) -
           ((gCdStream[0x440 / 4] << 11) + gCdStream[0x444 / 4]);
}

extern u32 D_800A3510w asm("D_800A3510.NON_MATCHING");
extern void *memcpy(void *, const void *, size_t);

u8 *func_800719FC(s32 *arg0) {
    volatile s32 *stream;
    volatile s32 *pre;
    s32 *head;
    s32 room;
    s32 avail;
    u32 counter;
    u32 retries;
    u32 x;
    u32 w;
    u32 left;
    u32 tail;
    u32 size;
    u32 first;
    u32 second;
    s32 *node;
    u32 third;
    u8 *result;
    head = (s32 *)((volatile s32 *)gCdStream)[0x42C / 4];
    room = head[0x10 / 4] - head[0x4 / 4];
    *arg0 = ((*arg0) > room) ? (room) : (*arg0);
    pre = (volatile s32 *)gCdStream;
    counter = 0;
    retries = 0;
    pre[0x448 / 4];
    pre[0x440 / 4];
    pre[0x444 / 4];
    for (;;) {
        stream = (volatile s32 *)gCdStream;
        avail = (stream[0x448 / 4] << 11) -
                ((stream[0x440 / 4] << 11) + stream[0x444 / 4]);
        if (avail < 0) {
            avail = (x = 0);
        }
        if (avail < (*arg0)) {
            if (stream[0x43C / 4] != 0) {
                return 0;
            }
            counter = counter + 1;
            if (counter > 4000000) {
                stream[0x424 / 4] = stream[0x424 / 4] + 2;
            }
            if (((volatile s32 *)gCdStream)[0x414 / 4] != 0) {
                if (((u32)((volatile s32 *)gCdStream)[0x424 / 4]) < 2) {
                    continue;
                }
            }
            retries = retries + 1;
            if (retries >= 3) {
                return 0;
            }
            counter = 0;
            CdUpdateStream();
            continue;
        }
        break;
    }

    {
        node = (s32 *)((volatile s32 *)gCdStream)[0x42C / 4];
        first = ((volatile s32 *)gCdStream)[0x440 / 4];
        second = ((volatile s32 *)gCdStream)[0x444 / 4];
        x = ((u32)(((volatile s32 *)gCdStream)[0x440 / 4] + node[0x34 / 4])) %
            D_800A3510w;
        w = ((u32)first) % D_800A3510w;
        third = ((volatile s32 *)gCdStream)[0x444 / 4];
        result = (u8 *)(node[0x30 / 4] + ((x << 11) + third));
        left = D_800A3510w - 1;
        tail = ((left - w) << 11) + 0x800;
        size = tail - second;
        if (size < (*arg0)) {
            memcpy(result - (D_800A3510w << 11), result, size);
            result = result - (D_800A3510w << 11);
        }
        return result;
    }
}

extern void func_80070F40(u_char, u_char *);
extern void CdStreamReadyCallback(u_char, u_char *);

void func_80071BE8(void) {
    u8 param[0x20];
    u8 result[0x20];
    u8 *resultPtr;
    u8 *resultPtr2;
    u32 i;
    s32 timedOut;
    s32 status;
    s32 retry;
    s32 mode;

    timedOut = 0;
    i = 0;
    if (gCdStream[0x414 / 4] != 0) {
        do {
            VSync(0);
            i++;
            if (i >= 0xB5) {
                timedOut = 1;
                break;
            }
        } while (gCdStream[0x414 / 4] != 0);
    }
    if (timedOut == 0) {
        i = 0;
        if (gCdStream[0] != 0) {
            do {
                VSync(0);
                i++;
                if (i >= 0xB5) {
                    timedOut = 1;
                    break;
                }
            } while (gCdStream[0] != 0);
        }
        if (timedOut == 0) {
            return;
        }
    }
    i = CdlComplete;
    SwEnterCriticalSection();
    ((volatile s32 *)gCdStream)[0x410 / 4] = 0;
    ((volatile s32 *)gCdStream)[0x408 / 4] = 0;
    ((volatile s32 *)gCdStream)[0x40C / 4] = 0;
    ((volatile s32 *)gCdStream)[0x41C / 4] = 0;
    CdSyncCallback(0);
    CdReadyCallback(0);
    SwExitCriticalSection();
    CdControl(CdlStop, 0, 0);
    do {
        bzero(param, 0x20);
        resultPtr = result;
        bzero(resultPtr, 0x20);
        resultPtr = 0;
        resultPtr2 = result;
        status = CdControl(CdlNop, param, resultPtr2);
        resultPtr2 = 0;
        if (status != 0) {
            if (result[0] == CdlNoIntr || result[0] == i) {
                retry = 0;
            } else {
                retry = 1;
            }
        } else {
            CdControl(CdlReset, 0, 0);
            retry = 1;
        }
    } while (retry);
    mode = CdlModeSpeed | CdlModeSize1;
    CdControlB(CdlSetmode, (u_char *)&mode, 0);
    SwEnterCriticalSection();
    CdSyncCallback(func_80070F40);
    CdReadyCallback(CdStreamReadyCallback);
    gCdStream[0x41C / 4] = 1;
    gCdStream[0x424 / 4] = 2;
    ((volatile s32 *)gCdStream)[0x414 / 4] = 0;
    SwExitCriticalSection();
}

extern s32 D_800A33B8, D_800A33BC;
void CdStreamSetEnabled(s32 enable) {
    u8 mode;
    s32 enabled;

    if (enable != 0) {
        CdSync(0, 0);
        mode = CdlModeSpeed | CdlModeSize1;
        CdControlB(CdlSetmode, &mode, 0);
        SwEnterCriticalSection();
        gCdStream[0x410 / 4] = 0;
        gCdStream[0x408 / 4] = 0;
        ((volatile s32 *)gCdStream)[0x40C / 4] = 0;
        D_800A33B8 = (s32)CdSyncCallback(func_80070F40);
        D_800A33BC = (s32)CdReadyCallback(CdStreamReadyCallback);
        gCdStream[0x420 / 4] = 1;
        ((volatile s32 *)gCdStream)[0x41C / 4] = 1;
    } else {
        SwEnterCriticalSection();
        enabled = gCdStream[0x420 / 4];
        gCdStream[0x41C / 4] = 0;
        gCdStream[0x410 / 4] = 0;
        gCdStream[0x408 / 4] = 0;
        ((volatile s32 *)gCdStream)[0x40C / 4] = 0;
        if (enabled != 0) {
            CdSyncCallback((void *)D_800A33B8);
            CdReadyCallback((void *)D_800A33BC);
            D_800A33B8 = 0;
            D_800A33BC = 0;
            gCdStream[0x420 / 4] = 0;
        }
    }
    SwExitCriticalSection();
}

extern s32 D_800A3514;
extern s32 D_800A3518;
s32 MediaGetBufferAllocationSize(s32 index, s32 base, s32 item) {
    D_800A3510 = index;
    index <<= 11;
    index += 0x57C;
    D_800A3514 = base;
    base += index;
    D_800A3518 = item;
    return base + item * 56;
}

s32 CdStreamInit(s32 *mem, s32 arg1, s32 *src, u32 count) {
    typedef struct {
        s32 w[6];
    } SixWords;
    s32 mode;
    s32 pad1;
    s32 pad2;
    s32 len;
    s32 temp;
    s32 end;
    s32 off;
    u32 i;
    s32 *srcp;
    s32 *dstp;

    len = D_800A3510;
    len <<= 11;
    len += 0x57C;
    (void)&mode;
    (void)&pad1;
    (void)&pad2;
    bzero(mem, D_800A3514 + len + D_800A3518 * 56);
    temp = (s32)mem + 0x57C;
    gCdStream = mem;
    D_800A3504 = temp;
    mem[0x570 / 4] = arg1;
    mem[0x414 / 4] = 0;
    mem[0x418 / 4] = 0;
    mem[0x41C / 4] = 0;
    mem[0x43C / 4] = 0;
    mem[0x434 / 4] = 0;
    mem[0x430 / 4] = 0;
    mem[0x42C / 4] = 0;
    mem[0x440 / 4] = 0;
    mem[0x448 / 4] = 0;
    mem[0x44C / 4] = 0;
    end = temp + D_800A3518 * 56;
    D_800A3508 = end;
    D_800A350C = end + D_800A3514;
    if (count != 0) {
        i = 0;
        srcp = src;
        off = 0;
    again:
        dstp = (s32 *)(off + D_800A3504);
        *(SixWords *)&dstp[3] = *(SixWords *)srcp;
        srcp += 6;
        off += 0x38;
        i++;
        if (i < count) {
            goto again;
        }
    }
    ((volatile s32 *)gCdStream)[0x438 / 4] = count;
    ((volatile s32 *)gCdStream)[0x424 / 4] = 0;
    ((volatile s32 *)gCdStream)[0x428 / 4] = 0;
    do {
    } while (0);
    gCdStream[0x574 / 4] = (s32)CdDataCallback(0);
    gCdStream[0x578 / 4] = (s32)CdReadCallback(0);
    func_800710D8();
    CdSync(0, 0);
    *(u8 *)&mode = CdlModeSpeed | CdlModeSize1;
    CdControlB(CdlSetmode, (u_char *)&mode, 0);
    SwEnterCriticalSection();
    gCdStream[0x410 / 4] = 0;
    gCdStream[0x408 / 4] = 0;
    ((volatile s32 *)gCdStream)[0x40C / 4] = 0;
    D_800A33B8 = (s32)CdSyncCallback(func_80070F40);
    D_800A33BC = (s32)CdReadyCallback(CdStreamReadyCallback);
    gCdStream[0x420 / 4] = 1;
    ((volatile s32 *)gCdStream)[0x41C / 4] = 1;
    SwExitCriticalSection();
    return 1;
}

void CdStreamShutdown(void) {
    s32 enabled;
    s32 pad[2];

    if (gCdStream[0x420 / 4] != 0) {
        CdDataCallback((void *)gCdStream[0x574 / 4]);
        CdReadCallback((void *)gCdStream[0x578 / 4]);
        SwEnterCriticalSection();
        enabled = gCdStream[0x420 / 4];
        gCdStream[0x41C / 4] = 0;
        gCdStream[0x410 / 4] = 0;
        gCdStream[0x408 / 4] = 0;
        ((volatile s32 *)gCdStream)[0x40C / 4] = 0;
        if (enabled != 0) {
            CdSyncCallback((void *)D_800A33B8);
            CdReadyCallback((void *)D_800A33BC);
            D_800A33B8 = 0;
            D_800A33BC = 0;
            gCdStream[0x420 / 4] = 0;
        }
        SwExitCriticalSection();
    }
}

extern volatile s32 *D_800A351C;
void AudioTransferCallback(void) {
    u8 *src;
    s32 value;
    u32 i;
    s32 old;
    s32 base;
    s32 count;

    if (D_800A351C[0x7B48 / 4] == 1) {
        src = (u8 *)D_800A351C[0x7B50 / 4];
        value = D_800A351C[0x7B54 / 4];
        for (i = 0; i < 0x300; i += 0x10) {
            src[i + 1] = 2;
        }
        if ((D_800A351C[0x7B44 / 4] & 3) == 0) {
            src[1] = 6;
        } else if (((D_800A351C[0x7B44 / 4] + 1) & 3) == 0) {
            src[0x2F1] = 3;
        }
        D_800A351C[0x7B2C / 4 + (D_800A351C[0x7B44 / 4] & 3)] = value;
        old = D_800A351C[0x7B44 / 4];
        base = D_800A351C[0x7B60 / 4];
        D_800A351C[0x7B44 / 4] = D_800A351C[0x7B44 / 4] + 1;
        count = D_800A351C[0x7B44 / 4];
        base += (old & 3) * 0x300;
        SpuSetTransferMode(0);
        SpuSetTransferStartAddr(base);
        SpuWrite(src, 0x300);
        D_800A351C[0x7B48 / 4] = 2;
    } else if (D_800A351C[0x7B48 / 4] == 2) {
        volatile s32 *spu;
        spu = D_800A351C;
        spu[0x7B48 / 4] = 0;
        if (spu[0x7B4C / 4] != 0) {
            spu[0] += 0x300;
            spu[0x7B4C / 4] = 0;
        }
    }
}

extern void SpuSetIRQ(s32);
extern void SpuSetIRQAddr(s32);
extern void SpuSetTransferStartAddr(s32);
void AudioIrqCallback(void) {
    u8 *src;
    s32 addr;
    s32 addr2;
    u32 value;
    u32 i;
    s32 mode;
    s32 result;
    s32 base;
    s32 fallback;

    SpuSetIRQ(0);
    SpuSetIRQCallback(0);
    if (D_800A351C[0x7B48 / 4] == 0 &&
        D_800A351C[0x7B44 / 4] * 2 - D_800A351C[0x7B40 / 4] < 6) {
        u32 size;

        size = 0x300;
        if ((u32)(D_800A351C[1] - D_800A351C[0]) > size &&
            D_800A351C[0x7B78 / 4] == 0) {
            addr =
                (s32)((u8 *)D_800A351C + ((u32)D_800A351C[0] % 0x3C00 + 0x10));
        } else {
            addr = 0;
        }
        src = (u8 *)addr;
        if (src != 0) {
            u32 size;

            size = 0x300;
            if ((u32)(D_800A351C[1] - D_800A351C[0]) > size &&
                D_800A351C[0x7B78 / 4] == 0) {
                addr2 = (s32)((u8 *)D_800A351C +
                              ((u32)D_800A351C[0] % 0x3C00 + 0x3C10));
            } else {
                addr2 = 0;
            }
            D_800A351C[0x7B58 / 4] = 1;
            D_800A351C[0x7B4C / 4] = 1;
            D_800A351C[0x7B48 / 4] = 1;
            D_800A351C[0x7B50 / 4] = addr2;
            D_800A351C[0x7B54 / 4] = D_800A351C[0x7B3C / 4];
            value = D_800A351C[0x7B3C / 4];
            for (i = 0; i < 0x300; i += 0x10) {
                src[i + 1] = 2;
            }
            if ((D_800A351C[0x7B44 / 4] & 3) == 0) {
                src[1] = 6;
            } else if (((D_800A351C[0x7B44 / 4] + 1) & 3) == 0) {
                src[0x2F1] = 3;
            }
            D_800A351C[0x7B2C / 4 + (D_800A351C[0x7B44 / 4] & 3)] = value;
            {
                s32 idx;

                idx = D_800A351C[0x7B44 / 4];
                base = D_800A351C[0x7B5C / 4];
                base += (idx & 3) * 0x300;
                SpuSetTransferMode(0);
                SpuSetTransferStartAddr(base);
                SpuWrite(src, 0x300);
                D_800A351C[0x7B3C / 4] = D_800A351C[0x7B3C / 4] + 0x300;
            }
        } else {
            u8 *buf;

            fallback = (s32)((u8 *)D_800A351C + 0x7810);
            D_800A351C[0x7B58 / 4] = 0;
            D_800A351C[0x7B4C / 4] = 0;
            D_800A351C[0x7B48 / 4] = 1;
            D_800A351C[0x7B50 / 4] = fallback;
            buf = (u8 *)fallback;
            D_800A351C[0x7B54 / 4] = 0;
            for (i = 0; i < 0x300; i += 0x10) {
                buf[i + 1] = 2;
            }
            if ((D_800A351C[0x7B44 / 4] & 3) == 0) {
                buf[1] = 6;
            } else if (((D_800A351C[0x7B44 / 4] + 1) & 3) == 0) {
                buf[0x2F1] = 3;
            }
            D_800A351C[0x7B2C / 4 + (D_800A351C[0x7B44 / 4] & 3)] = 0;
            {
                s32 idx;

                idx = D_800A351C[0x7B44 / 4];
                base = D_800A351C[0x7B5C / 4];
                base += (idx & 3) * 0x300;
                SpuSetTransferMode(0);
                SpuSetTransferStartAddr(base);
                SpuWrite(buf, 0x300);
            }
        }
    }
    if ((D_800A351C[0x7B40 / 4] & 1) == 0) {
        value = *(u32 *)((u8 *)D_800A351C + 0x7B2C +
                         ((D_800A351C[0x7B40 / 4] * 2) & 0xC));
        if (value != 0) {
            mode = D_800A351C[0x7B74 / 4];
            result = 0;
            if (mode != 0) {
                if (mode == 1) {
                    result =
                        (s32)((long long)((unsigned long long)value * 0x40) /
                              0x3F);
                }
            } else {
                if (D_800A351C[0x7B7C / 4] == 0x800) {
                    result =
                        (s32)((long long)((unsigned long long)value * 0x14D0) /
                              0x1117);
                } else {
                    result =
                        (s32)((long long)((unsigned long long)value * 0x6D440) /
                              0x82BA3);
                }
            }
            D_800A351C[0x7B24 / 4] = result;
        }
    }
    D_800A351C[0x7B40 / 4] = D_800A351C[0x7B40 / 4] + 1;
    D_800A351C[0x7B40 / 4];
    SpuSetIRQAddr(D_800A351C[0x7B5C / 4] +
                  (D_800A351C[0x7B40 / 4] & 7) * 0x180);
    SpuSetIRQCallback(AudioIrqCallback);
    SpuSetIRQ(1);
}

s32 AudioVSyncCallback(void) {
    s32 result;
    result = D_800A351C[0x7B20 / 4];
    if (result != 0) {
        D_800A351C[0x7B24 / 4] += 0x100;
        D_800A351C[0x7B28 / 4] = D_800A351C[0x7B28 / 4] + 1;
        result = D_800A351C[0x7B28 / 4];
    }
    return result;
}

void func_80072750(void) {
    u8 *src;
    s32 addr;
    s32 addr2;
    u32 size;
    u32 i;
    u32 j;
    s32 base;

    if (D_800A351C[2] == 0) {
        D_800A351C[0x7B3C / 4] = 0x300;
        for (i = 0; i < 3; i++) {
            size = 0x300;
            if ((u32)(D_800A351C[1] - D_800A351C[0]) > size &&
                D_800A351C[0x7B78 / 4] == 0) {
                addr = (s32)((u8 *)D_800A351C +
                             ((u32)D_800A351C[0] % 0x3C00 + 0x10));
            } else {
                addr = 0;
            }
            src = (u8 *)addr;
            if (src != 0) {
                if ((u32)(D_800A351C[1] - D_800A351C[0]) > size &&
                    D_800A351C[0x7B78 / 4] == 0) {
                    addr2 = (s32)((u8 *)D_800A351C +
                                  ((u32)D_800A351C[0] % 0x3C00 + 0x3C10));
                } else {
                    addr2 = 0;
                }
                addr = addr2;
            } else {
                src = (u8 *)D_800A351C + 0x7810;
                addr = (s32)src;
            }
            j = 0;
            D_800A351C[0x7B48 / 4] = 1;
            D_800A351C[0x7B4C / 4] = 1;
            D_800A351C[0x7B50 / 4] = addr;
            D_800A351C[0x7B54 / 4] = 1;
            addr = D_800A351C[0x7B3C / 4];
            for (; j < 0x300; j += 0x10) {
                src[j + 1] = 2;
            }
            if ((D_800A351C[0x7B44 / 4] & 3) == 0) {
                src[1] = 6;
            } else if (((D_800A351C[0x7B44 / 4] + 1) & 3) == 0) {
                src[0x2F1] = 3;
            }
            D_800A351C[0x7B2C / 4 + (D_800A351C[0x7B44 / 4] & 3)] = addr;
            base =
                D_800A351C[0x7B5C / 4] + (D_800A351C[0x7B44 / 4] & 3) * 0x300;
            SpuSetTransferMode(0);
            SpuSetTransferStartAddr(base);
            SpuWrite(src, 0x300);
            D_800A351C[0x7B3C / 4] += 0x300;
            do {
            } while (D_800A351C[0x7B48 / 4] != 0);
        }
        D_800A351C[0x7B48 / 4] = 3;
        AudioIrqCallback();
        D_800A351C[0x7B48 / 4] = 0;
        D_800A351C[2] = 1;
    }
    D_800A351C[0x7B6C / 4] = SpuSetReverbVoice(0, D_800A351C[0x7B64 / 4]);
    D_800A351C[0x7B70 / 4] = SpuSetReverbVoice(0, D_800A351C[0x7B68 / 4]);
    SpuSetKey(1, D_800A351C[0x7B64 / 4] | D_800A351C[0x7B68 / 4]);
}

void AudioSetStreamMode(s32 value) {
    D_800A351C[0x7B74 / 4] = value;
}

void AudioEnableStream(void) {
    D_800A351C[0x7B20 / 4] = 1;
}

void AudioDisableStream(void) {
    D_800A351C[0x7B20 / 4] = 0;
}

s32 AudioGetStreamCounter(void) {
    return D_800A351C[0x7B24 / 4];
}

s32 AudioGetScaledStreamPosition(void) {
    u32 val;
    long long q;
    s32 mode;

    val = D_800A351C[0x7B24 / 4];
    q = (long long)val * 100 / 0x100;
    /* Retail reloads the pointer after the libcall; gcc treats it as const. */
    mode = (*(volatile s32 *volatile *)&D_800A351C)[0x7B74 / 4];
    if (mode != 0) {
        if (mode == 1) {
            q /= 0x1388;
        }
    } else {
        q /= 0x176A;
    }
    return (s32)q;
}

/* Enabled after the maspsx li-$reg,0 wrapper fix; see matching.md. */
s32 AudioGetStreamPositionLimit(u32 arg) {
    if (D_800A351C[0x7B74 / 4] == 1) {
        return (long long)arg * 0x271000 / 0xBB5;
    }
    return arg << 10;
}

s32 AudioCountActiveStreamBuffers(void) {
    u16 flag;
    volatile s32 *p;
    u32 i;
    s32 count;
    count = 0;
    i = 0;
    p = D_800A351C;
    do {
        flag = p[0x7B2C / 4] != 0;
        if (flag) {
            flag = 1;
            count += flag;
        }
        i += 1;
        p += 1;
    } while (i < 4);
    return count;
}

s32 AudioGetStreamReadPosition(void) {
    return D_800A351C[0];
}

s32 AudioGetStreamWritePosition(void) {
    return D_800A351C[1];
}

s32 AudioGetStreamFreeSpace(s32 *size) {
    s32 difference;
    if (size)
        *size = 0x3C00;
    difference = D_800A351C[1] - 0x3C00;
    return D_800A351C[0] - difference;
}

#define SWAP32(w)                                                              \
    (((w) >> 24) | (((w) >> 8) & 0xFF00) | (((w) & 0xFF00) << 8) | ((w) << 24))

u32 AudioGetAdpcmSize(StreamChunk *header) {
    u32 swapped;
    u32 size;
    u32 isAd2;

    swapped = SWAP32(header->tag);
    isAd2 = (swapped & 0xFFFFFF00) == 0x61643200;
    if ((swapped & 0xFFFF0000) == 0x61640000) {
        size = SWAP32(header->size) - 0x10;
    } else {
        size = SWAP32(header->size) - 0xC;
    }
    if (isAd2) {
        size >>= 1;
    }
    return size;
}

void AudioQueueAdpcm(u8 *block) {
    volatile u32 *pollState;
    volatile u32 *state;
    volatile u32 *tailState;
    u32 swapped;
    u32 isAd2;
    u32 size;
    u32 firstLength;
    u32 pollTail;
    u32 pollHead;
    u8 *leftBase;
    u8 *leftSource;
    u8 *rightSource;
    u8 *secondSource;

    swapped = SWAP32(((StreamChunk *)block)->tag);
    isAd2 = (swapped & 0xFFFFFF00) == 0x61643200;
    if ((swapped & 0xFFFF0000) == 0x61640000) {
        leftSource = block + 0x10;
        size = SWAP32(((StreamChunk *)block)->size) - 0x10;
    } else {
        leftSource = block + 0xC;
        size = SWAP32(((StreamChunk *)block)->size) - 0xC;
    }
    rightSource = leftSource;
    if (isAd2) {
        size >>= 1;
        rightSource = leftSource + size;
    }
    pollState = (volatile u32 *)D_800A351C;
    do {
        pollTail = pollState[1];
        pollHead = pollState[0];
        pollTail -= 0x3C00;
    } while (pollHead - pollTail < size);
    state = (volatile u32 *)D_800A351C;
    firstLength = 0x3C00 - ((u32)state[1] % 0x3C00);
    if (firstLength >= size) {
        memcpy((u8 *)(((u32)state[1] % 0x3C00) + (u32)state) + 0x10, leftSource,
               size);
        state = (volatile u32 *)D_800A351C;
        if (isAd2) {
            memcpy((u8 *)(((u32)state[1] % 0x3C00) + (u32)state) + 0x3C10,
                   rightSource, size);
        } else {
            memcpy((u8 *)(((u32)state[1] % 0x3C00) + (u32)state) + 0x3C10,
                   leftSource, size);
        }
    } else {
        memcpy((u8 *)(((u32)state[1] % 0x3C00) + (u32)state) + 0x10, leftSource,
               firstLength);
        leftBase = (u8 *)D_800A351C;
        secondSource = leftSource + firstLength;
        memcpy(leftBase + 0x10, secondSource, size - firstLength);
        state = (volatile u32 *)D_800A351C;
        if (isAd2) {
            memcpy((u8 *)(((u32)state[1] % 0x3C00) + (u32)state) + 0x3C10,
                   rightSource, firstLength);
            memcpy((u8 *)D_800A351C + 0x3C10, rightSource + firstLength,
                   size - firstLength);
        } else {
            memcpy((u8 *)(((u32)state[1] % 0x3C00) + (u32)state) + 0x3C10,
                   leftSource, firstLength);
            memcpy((u8 *)D_800A351C + 0x3C10, secondSource, size - firstLength);
        }
    }
    tailState = (volatile u32 *)D_800A351C;
    tailState[1] = tailState[1] + size;
}

void func_80072FE4(u8 *dst, u8 *src, u32 n) {
    u32 i;

    for (i = 0; i < n; i += 15) {
        *dst++ = *src++;
        *dst++ = 0;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
        *dst++ = *src++;
    }
}

#define COPY_ADPCM_BLOCKS_BODY(copySource, copyDestination, copyCount, length) \
    if ((length) != 0) {                                                       \
        do {                                                                   \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = 0;                                            \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = *copySource++;                                \
            *copyDestination++ = *copySource++;                                \
            copyCount += 15;                                                   \
        } while (copyCount < (length));                                        \
    }

#define COPY_ADPCM_BLOCKS(src, dst, length, srcReg)                            \
    {                                                                          \
        register u8 *copySource asm(srcReg) = (src);                           \
        u8 *copyDestination = (dst);                                           \
        u32 copyCount = 0;                                                     \
        COPY_ADPCM_BLOCKS_BODY(copySource, copyDestination, copyCount,         \
                               length);                                        \
    }

void AudioQueueStereoAdpcm(u8 *block) {
    /* Compiler frame extent; retail does not access these bytes. */
    u8 frameExtent[0x30];
    u32 pollTail;
    u32 pollHead;
    u32 headerWord;
    u32 headerSize;
    u32 blockCount;
    u32 outputBlocks;
    u32 encodedTimes16;
    u32 spaceBlocks;
    u32 spaceTimes16;
    u32 encodedLength;
    u32 outputLength;
    u32 head;
    u32 firstLength;
    u32 secondLength;
    u32 lastLength;
    u8 *leftSource;
    u8 *rightSource;
    u8 *leftDestination;
    u8 *rightDestination;
    u8 *leftBase;
    u8 *rightBase;
    volatile u32 *pollState;
    register volatile u32 *spaceState asm("a3");
    volatile u32 *rightState;
    volatile u32 *tailState;

    headerWord = ((StreamChunk *)block)->size;
    headerSize = SWAP32(headerWord) - 0x10;
    encodedLength = headerSize >> 1;
    blockCount = encodedLength / 15;
    encodedTimes16 = blockCount << 4;
    encodedLength = encodedTimes16 - blockCount;
    outputBlocks = encodedLength / 15;
    outputLength = outputBlocks * 16;
    leftSource = block + 0x10;
    rightSource = leftSource + encodedLength;
    pollState = (volatile u32 *)D_800A351C;
    do {
        pollTail = pollState[1];
        pollHead = pollState[0];
        pollTail -= 0x3C00;
    } while (pollHead - pollTail < outputLength);
    spaceState = (volatile u32 *)D_800A351C;
    head = spaceState[1];
    spaceBlocks = (0x3C00 - (head % 0x3C00)) >> 4;
    spaceTimes16 = spaceBlocks << 4;
    firstLength = spaceTimes16 - spaceBlocks;
    if (firstLength >= encodedLength) {
        leftDestination =
            (u8 *)(((u32)spaceState[1] % 0x3C00) + (u32)spaceState) + 0x10;
        {
            u8 *copySource = leftSource;
            u8 *copyDestination = leftDestination;
            u32 copyCount = 0;

            COPY_ADPCM_BLOCKS_BODY(copySource, copyDestination, copyCount,
                                   encodedLength);
        }
        rightState = (volatile u32 *)D_800A351C;
        rightDestination =
            (u8 *)(((u32)rightState[1] % 0x3C00) + (u32)rightState) + 0x3C10;
        {
            u8 *copySource = rightSource;
            u8 *copyDestination = rightDestination;
            u32 copyCount = 0;

            COPY_ADPCM_BLOCKS_BODY(copySource, copyDestination, copyCount,
                                   encodedLength);
        }
    } else {
        leftDestination =
            (u8 *)(((u32)spaceState[1] % 0x3C00) + (u32)spaceState) + 0x10;
        COPY_ADPCM_BLOCKS(leftSource, leftDestination, firstLength, "a1");
        leftBase = (u8 *)D_800A351C;
        {
            u8 *copySource = leftSource + firstLength;
            u8 *copyDestination;
            u32 copyCount = 0;

            secondLength = encodedLength - firstLength;
            copyDestination = leftBase + 0x10;
            COPY_ADPCM_BLOCKS_BODY(copySource, copyDestination, copyCount,
                                   secondLength);
        }
        rightState = (volatile u32 *)D_800A351C;
        rightDestination =
            (u8 *)(((u32)rightState[1] % 0x3C00) + (u32)rightState) + 0x3C10;
        COPY_ADPCM_BLOCKS(rightSource, rightDestination, firstLength, "a2");
        rightBase = (u8 *)D_800A351C;
        {
            u8 *copySource = rightSource + firstLength;
            u8 *copyDestination;
            register u32 copyCount asm("a2") = 0;

            lastLength = encodedLength - firstLength;
            copyDestination = rightBase + 0x3C10;
            COPY_ADPCM_BLOCKS_BODY(copySource, copyDestination, copyCount,
                                   lastLength);
        }
    }
    tailState = (volatile u32 *)D_800A351C;
    tailState[1] = tailState[1] + outputLength;
}

#undef COPY_ADPCM_BLOCKS
#undef COPY_ADPCM_BLOCKS_BODY

void AudioBeginStreamUpdate(void) {
    volatile s32 *p;
    volatile s32 *field;
    u32 i;

    i = 0;
    p = D_800A351C;
    p[0x7B78 / 4] = 1;
    field = p;
    do {
        field[0x7B2C / 4] = 0;
        i += 1;
        field += 1;
    } while (i < 4);
}

void AudioEndStreamUpdate(void) {
    D_800A351C[0x7B78 / 4] = 0;
}

void AudioResetStreamState(void) {
    volatile s32 *field;
    volatile s32 *p;
    u32 i;

    SwEnterCriticalSection();
    i = 0;
    p = D_800A351C;
    p[0] = 0;
    p[1] = 0;
    p[3] = 0;
    field = p;
    do {
        field[0x7B2C / 4] = 0;
        i += 1;
        field += 1;
    } while (i < 4);
    SwExitCriticalSection();
}

void func_800739E0(void) {
    volatile s32 *field;
    volatile s32 *p;
    u32 i;

    SwEnterCriticalSection();
    i = 0;
    p = D_800A351C;
    p[0] = 0;
    p[1] = 0;
    p[3] = 0;
    field = p;
    do {
        field[0x7B2C / 4] = 0;
        i += 1;
        field += 1;
    } while (i < 4);
    D_800A351C[0x7B3C / 4] = 1;
    D_800A351C[0x7B24 / 4] = 0;
    SwExitCriticalSection();
}

void AudioApplyStreamReverbVoices(void) {
    SpuSetKey(0, D_800A351C[0x7B64 / 4] | D_800A351C[0x7B68 / 4]);
    SpuSetReverbVoice(D_800A351C[0x7B6C / 4], D_800A351C[0x7B64 / 4]);
    SpuSetReverbVoice(D_800A351C[0x7B70 / 4], D_800A351C[0x7B68 / 4]);
}

extern void *SpuSetTransferCallback(void *);

void AudioShutdown(void) {
    volatile s32 *field;
    volatile s32 *p;
    u32 i;

    SwEnterCriticalSection();
    SpuSetKey(0, D_800A351C[0x7B64 / 4] | D_800A351C[0x7B68 / 4]);
    SpuSetReverbVoice(D_800A351C[0x7B6C / 4], D_800A351C[0x7B64 / 4]);
    SpuSetReverbVoice(D_800A351C[0x7B70 / 4], D_800A351C[0x7B68 / 4]);
    SpuSetIRQ(0);
    SpuSetIRQCallback((SpuIRQCallbackProc)D_800A351C[0x7B14 / 4]);
    SpuSetTransferCallback((void *)D_800A351C[0x7B18 / 4]);
    D_800A351C[0x7B20 / 4] = 0;
    if (D_800A351C[0x7B1C / 4] != 0) {
        VSyncCallback((Callback)D_800A351C[0x7B10 / 4]);
    }
    D_800A351C[0x7B24 / 4] = 0;
    SwExitCriticalSection();
    SwEnterCriticalSection();
    i = 0;
    p = D_800A351C;
    p[0] = 0;
    p[1] = 0;
    p[3] = 0;
    field = p;
    do {
        field[0x7B2C / 4] = 0;
        i += 1;
        field += 1;
    } while (i < 4);
    D_800A351C[0x7B3C / 4] = 1;
    D_800A351C[0x7B24 / 4] = 0;
    SwExitCriticalSection();
}

s32 AudioGetSpuBufferSize(void) {
    return 0xC00;
}

s32 AudioGetContextSize(void) {
    return 0x7B80;
}

s32 AudioGetStreamStatus(void) {
    return D_800A351C[0x7B58 / 4];
}

s32 AudioInit(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
              s32 arg6) {
    SpuVoiceAttr va;
    SpuCommonAttr ca;
    SpuCommonAttr *caarg;
    u32 off;
    s32 voice;
    s32 addr;
    u8 val;
    u32 rawVoice;
    s32 base;

    if (arg0 == 0) {
        goto bail;
    }
    if (arg2 == 0) {
        goto bail;
    }
    if (arg4 == 0) {
        goto bail;
    }
    if (arg1 == 0) {
        goto bail;
    }
    if (arg3 == 0) {
        goto bail;
    }
    D_800A351C = (volatile s32 *)arg0;
    bzero(arg0, 0x7B80);
    off = 0;
    val = 2;
    do {
        ((u8 *)D_800A351C + off)[0x7811] = val;
        off = off + 0x10;
    } while (off < 0x300);
    D_800A351C[0x7B3C / 4] = 1;
    D_800A351C[0x7B58 / 4] = 0;
    D_800A351C[0x7B5C / 4] = arg2;
    D_800A351C[0x7B60 / 4] = arg4;
    D_800A351C[0x7B64 / 4] = arg1;
    D_800A351C[0x7B68 / 4] = arg3;
    D_800A351C[0x7B7C / 4] = arg5;
    voice = D_800A351C[0x7B64 / 4];
    addr = D_800A351C[0x7B5C / 4];
    ca.mask = 3;
    ca.mvol.left = 0x3FFF;
    ca.mvol.right = 0x3FFF;
    SpuSetCommonAttr(&ca);
    va.mask = 0xFF93;
    va.voice = voice;
    va.volume.left = -(voice == D_800A351C[0x7B64 / 4]) & 0x3FFF;
    va.volume.right = -(voice == D_800A351C[0x7B68 / 4]) & 0x3FFF;
    va.pitch = arg5;
    va.addr = addr;
    va.a_mode = 1;
    va.s_mode = 1;
    va.r_mode = 3;
    va.ar = 0;
    va.dr = 0;
    va.sr = 0;
    va.rr = 0;
    va.sl = 0xF;
    SpuSetVoiceAttr(&va);
    rawVoice = D_800A351C[0x7B68 / 4];
    voice = rawVoice;
    addr = (base = D_800A351C[0x7B60 / 4]);
    {
        asm volatile("addiu %0, $sp, 0x50" : "=r"(caarg));
        ca.mask = 3;
        ca.mvol.left = 0x3FFF;
        ca.mvol.right = 0x3FFF;
        SpuSetCommonAttr(caarg);
        va.mask = 0xFF93;
        va.voice = voice;
        va.volume.left = -(voice == D_800A351C[0x7B64 / 4]) & 0x3FFF;
        va.volume.right = -(voice == D_800A351C[0x7B68 / 4]) & 0x3FFF;
        va.pitch = arg5;
        va.addr = addr;
        va.a_mode = 1;
        va.s_mode = 1;
        va.r_mode = 3;
        va.ar = 0;
        va.dr = 0;
        va.sr = 0;
        va.rr = 0;
        va.sl = 0xF;
        SpuSetVoiceAttr(&va);
    }
    SwEnterCriticalSection();
    D_800A351C[0x7B14 / 4] = (s32)SpuSetIRQCallback(0);
    D_800A351C[0x7B18 / 4] = (s32)SpuSetTransferCallback(AudioTransferCallback);
    D_800A351C[0x7B1C / 4] = arg6;
    if (arg6 != 0) {
        D_800A351C[0x7B10 / 4] =
            (s32)((Callback (*)(Callback))VSyncCallback)(AudioVSyncCallback);
    } else {
        D_800A351C[0x7B10 / 4] = 0;
    }
    SwExitCriticalSection();
    return 1;
bail:
    return 0;
}
