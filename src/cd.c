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
#include "car.h"
#include "objects.h"
#include "scene.h"
#include "sound.h"
#include "util.h"

extern s32 strlen(char *);

extern Car *gPlayerCar[];
void CarResetMotionCounters(Car *);
extern s32 D_800A3A04nm[] asm("D_800A3A04.NON_MATCHING");
extern s32 D_800A39E0;
extern void CarResetMotionCounters(Car *);
extern u8 D_800B9DA4[];
void CarUpdateWheelVelocityComponents(Car *car);
s32 func_80029EF8(Car *obj);
s32 func_800370B8(s32 a, s32 b);

/* CD control and streaming. */

void RaceSetPlayerFirstStanding(void) {
    u8 index;
    s32 value;
    index = gPlayerCar[0]->driver;
    value = gPlayerCar[0]->time;
    gDriverOrder[0] = index;
    D_800AE1EC[0] = value;
    D_800B9DA4[index & 0xFF] = 0;
}

extern s32 CdSetDebug(s32 level);
void CdDisableDebug(void) {
    CdSetDebug(0);
}

extern s32 gCdTocRead;
extern s32 gCurrentFileId;
extern CdlLOC gCdToc[];
extern s32 gDatFileTable[];
extern s32 gCurrentFilePos[];
extern s32 gCurrentFileSize[];

void *FileOpen(s32 fileId, void *mode) {
    u8 pad[0x40];
    u8 result[8];
    void *pos;
    s32 value;

    if (gCdTocRead == 0) {
        CdGetToc(gCdToc);
        gCdTocRead = 1;
    }
    CdIntToPos(gDatFileTable[fileId * 3] + 0x13C, gCurrentFilePos);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = gDatFileTable[fileId * 3 + 1];
    gCurrentFileSize[0] = value;
    gCurrentFileId = fileId;
    pos = &gCurrentFileSize[-1];
    return pos;
}

void FileClose(void) {
}

/* MATCHED 2026-10-11 (w2i). Two keys beyond the 2026-10-07 draft:
 * 1. The file-table accesses must each use a pairwise-distinct symbol
 *    name for the same address (seek gDatFileTable, checksum compare
 *    D_80098348.NON_MATCHING, first FntPrint D_80098348, size print
 *    D_80098344.NON_MATCHING, sector print gDatFileTable.NON_MATCHING):
 *    a shared name let gcc CSE a sym base pointer into a sixth
 *    call-saved reg (s5), squeezing buf out of s2.
 * 2. result[] is 0x10 bytes here (8 elsewhere in cd.c): the extra 8
 *    bytes are the gap before the register homes, frame 0x38.
 * buf is pinned `register s32 buf asm("s2");` with the birth moved
 * after DrawSync(0) (permuter find): that orders the s2 save/move pair
 * before s4's in the mult->mflo window. */
static const char sChecksumFailureFormat[] =
    "Checksum Failure!\nChecksum   = %x\nCheckvalue = %x\n";
static const char sFileInfoFormat[] =
    "File Info:\nStart ADDR: %x\nFile No: %d\n";
static const char sFileSizeFormat[] = "Size: %d\n";
static const char sFileLocationFormat[] = "Location: %d\n";
extern s32 D_80098348nm[] asm("D_80098348.NON_MATCHING");
extern s32 D_80098344nm[] asm("D_80098344.NON_MATCHING");
extern s32 D_80098340w4[] asm("gDatFileTable.NON_MATCHING");
extern s32 D_80098348fp[] asm("D_80098348");

s32 FileRead(s32 buffer, s32 size, s32 count, s32 handle) {
    s32 total;
    s32 sectors;
    s32 hnd = handle;
    s32 retries;
    u8 result[0x10];
    s32 status;
    s32 *ptr;
    s32 i;
    s32 words;

    asm("" : "=r"(total) : "0"(count));
    retries = 0;
    total = total * size;
    DrawSync(0);
    do {
        VSync(0);
        VSync(0);
        total += 0x7FF;
        sectors = total >> 11;
        while (CdSync(1, result) == 0) {
            VSync(0);
        }
        total = -1;
    retry:
        while (CdControl(2, (u_char *)hnd, 0) == 0) {
        }
        CdSeekToSector(gDatFileTable[gCurrentFileId * 3] + 0x13C);
        CdRead(sectors, buffer, 0x80);
        do {
            status = CdReadSync(1, 0);
        } while (status > 0);
        if (status == total) {
            goto retry;
        }
    } while (0);
    ptr = (s32 *)buffer;
    i = 0;
    words = sectors << 9;
    total = 0;
    if (words > 0) {
        do {
            total += *ptr;
            ptr += 1;
            i += 1;
        } while (i < words);
    }
    retries += 1;
    if (D_80098348nm[gCurrentFileId * 3] != total) {
        if (retries < 0x32) {
            CdControl(9, 0, 0);
            CdSync(0, result);
            CdReady(0, result);
            CdInit();
            total = -1;
            goto retry;
        }
        GraphicsInit();
        do {
            FntPrint(sChecksumFailureFormat, D_80098348fp[gCurrentFileId * 3],
                     total);
            FntPrint(sFileInfoFormat, buffer & 0x7FFFFFFF, gCurrentFileId);
            FntPrint(sFileSizeFormat, D_80098344nm[gCurrentFileId * 3]);
            FntPrint(sFileLocationFormat,
                     D_80098340w4[gCurrentFileId * 3] + 0x13C);
        } while (0);
        FntFlush(-1);
        while (1) {
        }
    }
    return status;
}

s32 func_8003C8B4(void) {
    return 0;
}

s32 FileSeek(s32 *handle) {
    return handle[1];
}

void TextToUpper(u8 *string) {
    s32 length;
    s32 current;
    s32 end;
    u8 value;
    length = strlen((char *)string);
    if (length > 0) {
        current = (s32)string;
        end = length + current;
        do {
            value = *(u8 *)current;
            if ((u32)(value - 'a') < 26) {
                value -= 0x20;
                *(u8 *)current = value;
            }
            current++;
        } while (current < end);
    }
}

void *FileLoadToHeap(s32 fileId) {
    u8 pad[0x40];
    u8 result[8];
    s32 value;
    s32 size;
    void *buffer;

    if (gCdTocRead == 0) {
        CdGetToc(gCdToc);
        gCdTocRead = 1;
    }
    CdIntToPos(gDatFileTable[fileId * 3] + 0x13C, gCurrentFilePos);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = gDatFileTable[fileId * 3 + 1];
    gCurrentFileId = fileId;
    gCurrentFileSize[0] = value;
    size = (value + 0x7FF) >> 11 << 11;
    buffer = HeapAlloc(size);
    if (buffer != 0) {
        FileRead(buffer, 1, size, gCurrentFilePos);
    }
    return buffer;
}

void CdLoadFileByIndex(s32 buffer, s32 fileId) {
    u8 pad[0x40];
    u8 result[8];
    s32 value;

    if (gCdTocRead == 0) {
        CdGetToc(gCdToc);
        gCdTocRead = 1;
    }
    CdIntToPos(gDatFileTable[fileId * 3] + 0x13C, gCurrentFilePos);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = gDatFileTable[fileId * 3 + 1];
    gCurrentFileId = fileId;
    gCurrentFileSize[0] = value;
    FileRead(buffer, 1, value, gCurrentFilePos);
}

/* The retail layout needs four shapes that look odd in C:
 * - filter is a 4-byte array and result a dead 0x30-byte array, so locals land
 *   at 0x10 (vol), 0x18 (filter) and 0x20 (result) in a 0x58 frame.
 * - The remainder is spelled out, so only the final subtract targets remainder.
 * - arg0 = remainder is a real copy: arg0 stays live in s0 into the negate.
 * - remainder = 0 then -= arg0 makes cse forget remainder == arg0, so the
 *   negate reads s0. The store sits in both arms; cross-jumping merges them.
 */
extern s32 CdGetToc(void *);
extern CdlLOC gCdAudioTrackPos[];
extern s32 gCdAudioTrack;
extern u8 D_800A2F9CAbsolute[];

void CdPlayAudioTrack(s32 arg0) {
    CdlATV vol;
    u8 filter[4];
    volatile u_char result[0x30];
    CdlLOC *lastPos;
    s32 remainder;
    CdlLOC *pos;

    if (CdGetToc(gCdToc) < 2) {
        return;
    }
    filter[0] = 5;
    if (CdControl(0xE, filter, 0) == 0) {
        return;
    }
    CdSetDebug(0);
    remainder = arg0 - arg0 / 6 * 6;
    arg0 = remainder;
    if (arg0 < 0) {
        remainder = 0;
        remainder -= arg0;
        gCdAudioTrack = remainder + 2;
    } else {
        gCdAudioTrack = remainder + 2;
    }
    pos = &gCdAudioTrackPos[0];
    CdIntToPos(0x19649, pos);
    lastPos = pos + 5;
    CdIntToPos(0x1C4B8, gCdAudioTrackPos + 1);
    CdIntToPos(0x1F278, gCdAudioTrackPos + 2);
    CdIntToPos(0x2219A, gCdAudioTrackPos + 3);
    CdIntToPos(0x250DB, gCdAudioTrackPos + 4);
    CdIntToPos(0x25EFF, lastPos);
    CdControl(2, (u_char *)(gCdAudioTrackPos + gCdAudioTrack - 2), 0);
    if (D_800A2F9CAbsolute[0] != 0) {
        CdControlB(3, 0, 0);
    }
    vol.val3 = 0x7F;
    vol.val2 = 0x7F;
    vol.val1 = 0x7F;
    vol.val0 = 0x7F;
    CdMix(&vol);
}

extern u8 D_800AE24C[];

void CdStopIfPlaybackChanged(void) {
    u_char param[8];
    u_char result[8];

    if (D_800A2F9CAbsolute[0] == 0) {
        return;
    }
    if (D_800A2EC8[0] != 0) {
        return;
    }
    CdControl(1, 0, D_800AE24C);
    param[0] = 0;
    CdControl(0x11, param, result);
    if (result[0] == gCdAudioTrack) {
        return;
    }
    CdControl(2, (u_char *)&gCdToc[gCdAudioTrack], 0);
    CdControl(3, 0, 0);
}

void func_8003CCE0(s32 arg0) {
    u_char pad[0x10];
    u_char *status;
    s32 target;

    pad[0] = 0;
    if (arg0 != 0) {
        CdControl(3, 0, 0);
        CdControlB(0xC, 0, 0);
        return;
    }
    status = D_800AE24C;
    CdControlB(1, 0, status);
    if (*(s32 *)status != 0x42) {
        CdControl(9, 0, 0);
        return;
    }
    target = 0x82;
    do {
        CdControl(1, 0, status);
    } while (*(s32 *)status != target);
    CdControl(9, 0, 0);
}

void CdStop(void) {
    CdControl(8, 0, 0);
}

static const char sInputOpenError[] = "Input file couldn't be opened!";

void GraphicsLoadImagePointerTable(s32 fileId) {
    u8 pad[0x40];
    u8 result[8];
    s32 *pos;
    s32 value;
    s32 posValue;
    u32 base;
    s32 count;
    s32 i;
    s32 *src;

    if (gCdTocRead == 0) {
        CdGetToc(gCdToc);
        gCdTocRead = 1;
    }
    CdIntToPos(gDatFileTable[fileId * 3] + 0x13C, &gCurrentFileSize[-1]);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = gDatFileTable[fileId * 3 + 1];
    pos = &gCurrentFileSize[-1];
    gCurrentFileId = fileId;
    gCurrentFileSize[0] = value;
    if (pos == NULL) {
        SystemShowFatalError(sInputOpenError);
    }
    posValue = gCurrentFileSize[0];
    base = (0x1F4000 - posValue) | RAM_CACHED_BASE;
    FileRead(base, posValue, 1, pos);
    src = (s32 *)base;
    count = *src++;
    for (i = 0; i < count; i++) {
        gImagePointerTable[i] = *src++ + base;
    }
}

const char gSsVabOpenHeadFailedMessage[] = "SsVabOpenHead: Open failed\n";
const char gSsVabTransBodyFailedMessage[] = "SsVabTransBody: failed\n";

void func_8003CEFC(void) {
}

void func_8003CF04(void) {
}

/* Car layout as far as CarUpdateState reads it. The fields are struct members,
 * not (u8 *) casts: a struct store lets sched hoist the gp load of D_800A376C
 * above the 0x286/0x2A4/0x2AA stores, as retail does. */
extern void func_80030D80(Car *, s32 *);
extern void SoundStopConditionalSlots(s32);
extern s32 D_800A376C;
extern u8 D_800A38B0Lui[] asm("D_800A38B0");
extern u16 D_800A35D0Lui[] asm("D_800A35D0");
extern u16 D_800A2EC4Lui[] asm("D_800A2EC4");
extern s32 D_800A2EC4Sw[] asm("D_800A2EC4");
extern Car *gPlayerCarCar[] asm("gPlayerCar");
extern s32 D_800A3680Lui[] asm("D_800A3680");
extern s32 D_800A2EAC[];
extern s8 D_800A3564Lui[] asm("D_800A3564");
extern u8 D_800A35D4Lui[] asm("D_800A35D4");

void CarUpdateState(Car *object) {
    s32 query[3];
    s32 buttons;
    s32 heading;
    s16 segment; /* s16 local: reserves the 8-byte phantom frame slot */
    u16 value;
    Car *player;

    if (object->state == 0) {
        query[0] = object->pos.x;
        query[1] = object->pos.y;
        query[2] = object->pos.z;
        func_80030D80(object, query);
    }
    if (object->state == 4) {
        if (object->unk268 == 0) {
            if (object->type == 0) {
                object->unk20D = object->cameraMode;
                if (D_800A38B0Lui[0] != 0) {
                    value = D_800A35D0Lui[0];
                } else {
                    value = D_800A2EC4Lui[0];
                }
                object->unk26C[13] = value;
                object->unk2A4 = object->unk2A0 + 8;
                object->unk2AA = object->unk2A6 + 8;
                if (ABS(func_800370B8(object->segment, D_800A376C)) < 5) {
                    object->unk269 = 0xFF;
                }
                object->flags = PadGetButtons(object->slot);
                buttons = func_80029EF8(object);
                object->sliding = 0;
                object->unk3B9 = 0;
                player = gPlayerCarCar[0];
                object->unk23C = buttons;
                object->unk120 = 0;
                if (object == player) {
                    SoundStopConditionalSlots(1);
                } else if (gSplitScreenMode[0] != 0 && object == player->next) {
                    SoundStopConditionalSlots(2);
                }
                D_800A3680Lui[0] = 1;
                if (D_800A2CE0[0] == 3) {
                    segment = object->segment;
                    if (segment < 0x10 || (u16)(segment - 0x47) < 0xE) {
                        object->unk269 = 0xFF;
                    } else if (segment >= 0x65) {
                        object->unk269 = 2;
                    }
                }
            }
            if (object->unk268 == 0 && object->type == 1) {
                if (object->callback != (void *)CarResetMotionCounters) {
                    object->callback = (void *)CarResetMotionCounters;
                }
                object->unkFA += RandomScaledGet(3);
                if (object->unkFA <= 0) {
                    object->unkFA = 1;
                }
            }
        }
        if (object->type == 0 && D_800A2EAC[0] == 0) {
            object->cameraMode = 0;
            D_800A2EC4Sw[0] = 0;
        }
        if (object->unk268 == 0) {
            D_800A3564Lui[0] = 1;
        }
        object->unk268 = 1;
    } else {
        if (object->unk268 == 1 && object->type == 0) {
            if (D_800A35D4Lui[0] == 0) {
                D_800A2EC4Sw[0] = object->unk26C[13];
            }
            heading = object->heading;
            object->cameraMode = object->unk20D;
            object->cameraAngle = heading;
            object->unk26C[12] += 1;
            D_800A3680Lui[0] = 1;
            RaceStoreLapRecordCarFields();
        }
        if (object->unk268 != 0) {
            D_800A3564Lui[0] = 1;
        }
        object->unk268 = 0;
        object->unk269 = 0;
        object->unk26B = 0;
        object->unk26A = 3;
        object->unk2A2 = 0;
        object->unk2A8 = 0;
    }
}

extern s32 D_800A2F84nm asm("D_800A2F84.NON_MATCHING");

extern s32 D_800A3A04Lui asm("D_800A3A04Absolute");
void func_8003D25C(Car *object) {
    s32 i;
    s32 value;
    s32 count;
    s32 diff;
    u8 flag;

    D_800A3A04nm[0] = 3;
    func_80029CB4(object);
    D_800A3A04Lui = 0xD;
    flag = 1;
    if (object->unk26A & 0x10) {
        i = object->unk26A & 0x40;
        if (D_800A2F84nm != 0) {
            i = !i;
        }
        if (i != 0) {
            object->wheel[0].unk0 = object->unk26C[4] * 10;
            object->wheel[2].unk0 = object->unk26C[4] * 10;
            object->wheel[1].unk0 = object->unk26C[4] * 4;
            object->wheel[3].unk0 = object->unk26C[4] * 4;
        } else {
            object->wheel[1].unk0 = object->unk26C[4] * 10;
            object->wheel[3].unk0 = object->unk26C[4] * 10;
            object->wheel[0].unk0 = object->unk26C[4] * 4;
            object->wheel[2].unk0 = object->unk26C[4] * 4;
        }
        for (i = 0; i < 4; i++) {
            if (object->unk26A & 0x40) {
                if (i < 2) {
                    continue;
                }
            } else {
                if (i >= 2) {
                    break;
                }
            }
            value = *(u16 *)&object->unk26C[i];
            *(u16 *)&object->unk26C[i] = value - 1;
            count = (s16)(value - 1);
            if (count == 0x5A) {
                goto special;
            }
            if (count == 5) {
            special:
                if (object->type == 0) {
                    SoundPlaySlotAtVolume(object, 8, 3);
                }
                *(u16 *)&object->unk26C[i] = *(u16 *)&object->unk26C[i] - 1;
            } else if (count == 0x46) {
                diff = value - 2;
                object->unk26C[i] = diff;
            } else if (count == 0x28) {
                diff = value - 2;
                object->unk26C[i] = diff;
                func_8002D3EC(object);
                object->unk3A6[i] = 1;
            }
            do {
                if (object->unk26C[i] > 0) {
                    flag = 0;
                }
            } while (0);
        }
        if (flag != 0) {
            if (object->unk26A & 0x40) {
                object->unk26A &= 0xAE;
            } else {
                object->unk26C[4] = -0x23;
                object->unk26A = (object->unk26A | 0x40) & 0xEF;
            }
            i = 3;
            do {
                object->wheel[i].effect = 0;
                i--;
            } while (i >= 0);
        } else {
            if (object->unk26C[4] < 4) {
                object->unk26C[4] = object->unk26C[4] + 1;
            }
        }
    } else {
        if ((s16)++object->unk26C[4] == 5) {
            object->unk26A |= 0x10;
            object->unk26C[4] = 0;
            if (object->unk26A & 0x40) {
                object->unk26C[2] = 100;
                object->unk26C[3] = 100;
            } else {
                object->unk26C[0] = 100;
                object->unk26C[1] = 100;
            }
        }
    }
}

void func_8003D528(Car *object) {
    s32 result;
    s32 value;
    s32 mask;

    value = object->unk28C + 0x4B;
    object->unk28C = value;
    result = 0;
    if (value >= 0x3E81) {
        object->unk28C = 0x3E80;
    }
    if (object->type == 0) {
        result = func_80029EF8(object);
    }
    if (object->unk28C == 0x3E80) {
        goto trigger;
    }
    if (object->type == 0 && (object->unk26A & 1) == 0) {
        mask = ~object->unk23C & 0x40;
        if ((result & mask) != 0) {
        trigger:
            object->unk290 = 0x7D000;
            object->unk26A &= 0xDD;
        }
    }
    object->unk23C = result;
}

void func_8003D5F8(Car *object) {
    u16 flags;
    s32 i;
    u32 total;
    Car *entry;

    flags = object->unk3A4;
    total = 0;
    if (flags != 0) {
        i = 0;
        do {
            entry = (u8 *)object + i;
            if ((s8)entry->unk3A6[0] == 0) {
                total = total + 0x14;
            }
            if ((s8)entry->unk3AE[0] != 0) {
                total = total + (s8)entry->unk3AE[0] * 3;
            }
            i = i + 1;
        } while (i < 8);
    }
    object->unk26C[10] = total;
}

void func_8003D654(Car *object) {
    s32 i;
    u16 count;
    count = (u16)object->unk26C[10];
    object->unk26C[10] = count - 1;
    if ((s16)count < 0) {
        object->unk3A4 = 0;
        i = 0;
        do {
            object->unk3A6[i] = 1;
            object->unk3AE[i] = 0;
            i++;
        } while (i < 8);
    }
}

void func_8003D69C(Car *object) {
    s32 value;
    s32 now;

    value = *(volatile u16 *)&object->unk26C[6];
    now = (u16)object->unk26C[6];
    object->unk26C[6] = now - 1;
    object->unk2A2 = (s16)value / 10;
    if ((now << 16) < 0) {
        object->unk2A2 = 0;
        object->unk26A &= ~0x04;
    }
}

void func_8003D6F8(Car *object) {
    s32 value;
    s32 now;

    value = *(volatile u16 *)&object->unk26C[7];
    now = (u16)object->unk26C[7];
    object->unk26C[7] = now - 1;
    object->unk2A8 = (s16)value / 10;
    if ((now << 16) < 0) {
        object->unk2A8 = 0;
        object->unk26A &= ~0x08;
    }
}

void func_8003D754(Car *object) {
    s32 buttons;

    buttons = PadGetButtons(object->slot);
    if (buttons & ((u16)~object->flags & 0x1000)) {
        object->unk26B -= 1;
        SoundPlaySlotAtVolume(object, 10, 6);
    } else if (buttons & ((u16)~object->flags & 0x4000)) {
        object->unk26B += 1;
        SoundPlaySlotAtVolume(object, 10, 6);
    }
    object->unk26B = (object->unk26B + 4) % 4;
    if (buttons & ((u16)~object->flags & 0x8000)) {
        SoundPlaySlotAtVolume(object, 10, 6);
        switch (object->unk26B) {
        case 0:
            if (object->unk26A & 1) {
                object->unk26A &= 0xFE;
            } else {
                object->unk26A |= 1;
            }
            break;
        case 1:
            if (object->unk26A & 2) {
                object->unk26A &= 0xFD;
            } else {
                object->unk26A |= 2;
            }
            break;
        case 2:
            if (object->unk2AA >= -7) {
                object->unk2A8 -= 1;
                object->unk2AA -= 1;
            }
            break;
        case 3:
            if (object->unk2A4 >= -7) {
                object->unk2A2 -= 1;
                object->unk2A4 -= 1;
            }
            break;
        }
        if (object->unk2A2 < -16) {
            object->unk2A2 = -16;
        }
        if (object->unk2A8 < -16) {
            object->unk2A8 = -16;
        }
    }
    if (buttons & ((u16)~object->flags & 0x2000)) {
        SoundPlaySlotAtVolume(object, 10, 6);
        switch (object->unk26B) {
        case 0:
            if (object->unk26A & 1) {
                object->unk26A &= 0xFE;
            } else {
                object->unk26A |= 1;
            }
            break;
        case 1:
            if (object->unk26A & 2) {
                object->unk26A &= 0xFD;
            } else {
                object->unk26A |= 2;
            }
            break;
        case 2:
            if (object->unk2AA < 8) {
                object->unk2A8 += 1;
                object->unk2AA += 1;
            }
            break;
        case 3:
            if (object->unk2A4 < 8) {
                object->unk2A2 += 1;
                object->unk2A4 += 1;
            }
            break;
        }
        if (object->unk2A2 >= 17) {
            object->unk2A2 = 16;
        }
        if (object->unk2A8 >= 17) {
            object->unk2A8 = 16;
        }
    }
    object->unk26A &= 0xF3;
    if (object->unk2A2 != 0) {
        object->unk26A |= 4;
    }
    if (object->unk2A8 != 0) {
        object->unk26A |= 8;
    }
    object->flags = buttons;
}

s32 TrackSectionIsAtOrAfter(s32 a, s32 b) {
    if (b >= gTrackSectionCount[0]) {
        if (a >= gTrackSectionCount[0] / 2)
            return 0;
        b -= gTrackSectionCount[0];
    }
    return !(a < b);
}

__inline__ s32 TrackSectionIsInWrappedRange(s32 start, s32 end, s32 value) {
    s32 result;
    s32 offset;
    offset = gTrackSectionCount[0];
    if (value < end) {
        if (value >= start) {
            value += offset;
            return 1;
        }
        value += offset;
    }
    result = 0;
    if (start >= end)
        result = value >= start;
    return result;
}

s32 func_8003DB5C(s32 arg0, s32 arg1, s32 arg2) {
    s32 cmp;
    s32 result;
    s32 offset;
    offset = gTrackSectionCount[0];
    if (arg2 < arg1) {
        arg2 += offset;
        if ((offset / 2) >= arg0) {
            arg0 += offset;
        }
    }
    result = 0;
    offset = arg0 < arg1;
    cmp = offset;
    if (cmp == 0) {
        result = arg2 >= arg0;
    }
    return result;
}

extern void func_8003D754(Car *);
extern void CarSteerTowardHeading(Car *, s32);
extern void func_80041564(Car *, s32);
extern s32 D_800A2EA8CarState[] asm("D_800A2EA8");
extern s32 D_800A2EACCarState[] asm("D_800A2EAC");
extern s32 gSessionTypeCarState[] asm("gSessionType");
extern u8 D_800A2EE0CarState[] asm("D_800A2EE0");
extern s32 D_800A2F4CCarState[] asm("D_800A2F4C");
extern Car *gPlayerCarCarState[] asm("gPlayerCar");
extern Car *D_800A3960CarState[] asm("gCrashCar");
extern s32 D_800A39E0CarState asm("D_800A39E0");
extern s32 D_800A3A04CarState[] asm("D_800A3A04");
extern s32 gTrackSectionCountCarState[] asm("gTrackSectionCount");
extern TrackSection *gTrackSectionsCarState[] asm("gTrackSections");

extern Car *D_800A3960CarStateStore[] asm("gCrashCar");
extern s32 D_800A3A04CarStateStore[] asm("D_800A3A04");
void func_8003DBA8(Car *object) {
    s32 delta[3];
    s32 ringResult;
    s32 ringV1;
    s32 ringA0;
    s32 ringA1;
    register s32 ringA2 asm("a2");
    register s32 ringA3 asm("a3");
    s32 sectionCount;
    s32 centerSection;
    s32 mask;
    s32 previousOffset;
    s32 earlierOffset;
    s32 trailingOffset;
    s32 offset;
    s32 section;
    TrackSection *earlier;
    s32 coordinate;
    s32 coordinateY;
    s32 targetX;
    s32 targetY;
    s32 trailingX;
    s32 direction;
    s32 steerAmount;
    s32 otherSteerAmount;
    register s32 trailingSection asm("a1");
    s32 charge;
    s32 trailingY;
    s32 control;
    s32 i;
    s32 buttons;
    s32 earlierSection;
    s32 angle;
    s32 turnLimit;
    s32 j;
    s8 severity;
    u16 oldSteerTime;
    u16 oldOtherSteerTime;
    u16 brake;
    u16 oldWait;
    u16 newBrake;
    u16 oldDamageTime;
    u16 steerTime;
    u16 otherSteerTime;
    s32 damageTime;
    s32 state;
    u8 flags;
    u8 nextState;
    TrackSection *trailing;
    TrackSection *entry;
    u8 *targets;
    TrackSection *previous;
    Car *damage;

    sectionCount = gTrackSectionCountCarState[0];
    section = object->segment;
    if ((sectionCount < section) || (section < 0)) {
        section = 0;
    }
    entry = &gTrackSectionsCarState[0][section];
    targets = (u8 *)entry + 0x34;
    if (entry->unk34 != section) {
        entry->unk34 = section;
        entry->unk36 = 0;
        previousOffset = gTrackSectionCountCarState[0] - 1;
        earlierOffset = gTrackSectionCountCarState[0] - 2;
        earlierSection =
            (s32)(section + earlierOffset) % (s32)gTrackSectionCountCarState[0];
        previous = (u8 *)gTrackSectionsCarState[0] +
                   (((s32)(section + previousOffset) %
                     (s32)gTrackSectionCountCarState[0]) *
                    0x90);
        earlier = &gTrackSectionsCarState[0][earlierSection];
        coordinate = previous->unk40;
        entry->unk40 = (s32)((coordinate - earlier->unk40) + coordinate);
        coordinateY = previous->unk44;
        entry->unk44 = (s32)((coordinateY - earlier->unk44) + coordinateY);
        targetX = previous->unk38;
        entry->unk38 = (s32)((targetX - earlier->unk38) + targetX);
        targetY = previous->unk3C;
        entry->unk3C = (s32)((targetY - earlier->unk3C) + targetY);
        trailingX = previous->unk48;
        entry->unk48 = (s32)((trailingX - earlier->unk48) + trailingX);
        trailingY = previous->unk4C;
        entry->unk4C = (s32)((trailingY - earlier->unk4C) + trailingY);
    }
    state = object->unk269;
    offset = object->unk28A;
    object->unk84 = 0xAA0000;
    object->speedBoost = 0;
    switch (state) {
    case 0x0:
        delta[0] = entry->unk38 - object->pos.x;
        delta[1] = entry->unk3C - object->pos.y;
        delta[2] = 0;
        object->unk26C[5] = 0xFU;
        object->unk26C[6] = 0U;
        object->unk26C[9] = 0U;
        if ((object->type == 0) && ((D_800A2EE0CarState[0] != 0) ||
                                    !(*(s32 *)&object->unk3A4 & 0x100F))) {
            func_8003D754(object);
        }
        if (MathGetAngleDelta(
                object->heading,
                gTrackSectionsCarState[0][object->segment].angle) < 0) {
            if (-MathGetAngleDelta(
                    object->heading,
                    gTrackSectionsCarState[0][object->segment].angle) < 0x15) {
                turnLimit = 4;
            } else {
                turnLimit = 0x14;
            }
        } else {
            if (MathGetAngleDelta(
                    object->heading,
                    gTrackSectionsCarState[0][object->segment].angle) >= 0x15) {
                turnLimit = 0x14;
            } else {
                turnLimit = 4;
            }
        }
        do {
            ringResult = D_800A39E0CarState;
        } while (0);
        D_800A2F4CCarState[0] = turnLimit;
        ringV1 = gTrackSectionCountCarState[0];
        ringA1 = object->segment;
        {
            const s32 section = ringA1;
            s32 end = ringResult + offset - 4;
            s32 count;
            count = ringV1;
            if (end >= count) {
                if (section >= count / 2) {
                    ringResult = 0;
                } else {
                    end -= count;
                    ringResult = !(section < end);
                }
            } else {
                ringResult = !(section < end);
            }
        }
        if ((u8)ringResult) {
            nextState = 2;
            if (object->unk26A != 0) {
                nextState = 1;
            }
            object->unk269 = nextState;
        }
        if ((gSessionTypeCarState[0] == 0) && (object->place == 1) &&
            (D_800A2EA8CarState[0] >= object->lap)) {
            func_80041564(gPlayerCarCarState[0], 0x23);
        }
        goto updateMotion;
    case 0x1:
        if ((object->type == 0) && ((D_800A2EE0CarState[0] != 0) ||
                                    !(*(s32 *)&object->unk3A4 & 0x100F))) {
            func_8003D754(object);
        }
        delta[0] = ((TrackSection *)(targets - 0x34))->unk48 - object->pos.x;
        ringResult = ((TrackSection *)(targets - 0x34))->unk4C;
        ringV1 = object->pos.y;
        ringResult -= ringV1;
        ringV1 = D_800A39E0CarState;
        delta[2] = 0;
        delta[1] = ringResult;
        object->unk84 = 0x6B0000;
        ringA0 = gTrackSectionCountCarState[0];
        ringA1 = object->segment;
        D_800A2F4CCarState[0] = 8;
        {
            const s32 section = ringA1;
            s32 end = ringV1 + offset;
            const s32 count = ringA0;
            if (end >= count) {
                if (section >= count / 2) {
                    ringResult = 0;
                } else {
                    end -= count;
                    ringResult = !(section < end);
                }
            } else {
                ringResult = !(section < end);
            }
        }
        if ((u8)ringResult) {
            object->unk84 = 0x3D0000;
            brake = object->unk26C[8] + 0x14;
            object->unk26C[8] = brake;
            if ((s16)brake >= 0x15F) {
                object->unk26C[8] = 0x15EU;
            }
        }
        {
            const s32 section = object->segment;
            s32 end = D_800A39E0CarState + offset + 1;
            ringV1 = gTrackSectionCountCarState[0];
            if (end >= ringV1) {
                if (section >= ringV1 / 2) {
                    ringResult = 0;
                } else {
                    end -= ringV1;
                    ringResult = !(section < end);
                }
            } else {
                ringResult = !(section < end);
            }
        }
        if ((u8)ringResult) {
            ringResult = 3;
            ringV1 = object->unk2A2;
            object->unk269 = ringResult;
            object->unk26C[4] = 0;
            if (ringV1 < 0)
                ringV1 = -ringV1;
            do {
                ringResult = ringV1 * 10;
            } while (0);
            ringV1 = object->unk2A8;
            object->unk26C[6] = ringResult;
            if (ringV1 < 0)
                ringV1 = -ringV1;
            ringResult = ringV1 * 5;
            ringA3 = ringResult * 2;
            ringResult = (u16)object->unk2A0;
            ringA0 = (u16)object->unk2A2;
            ringV1 = (u16)object->unk2A6;
            ringA1 = (u16)object->unk2A8;
            ringA2 = object->unk28C;
            object->unk26C[7] = ringA3;
            ringResult += ringA0;
            ringV1 += ringA1;
            object->unk2A0 = ringResult;
            object->unk2A6 = ringV1;
            if (ringA2 == 0) {
                object->unk28C = 0x64;
            }
            damageTime = 0;
            if (object->unk3A4 != 0) {
                i = 0;
                do {
                    damage = (u8 *)object + i;
                    if ((s8)damage->unk3A6[0] == 0) {
                        damageTime += 0x14;
                    }
                    severity = (s8)damage->unk3AE[0];
                    if (severity != 0) {
                        damageTime += severity * 3;
                    }
                    i += 1;
                } while (i < 8);
            }
            object->unk26C[10] = damageTime;
        }
        goto updateMotion;
    case 0x2:
        delta[0] = entry->unk40 - object->pos.x;
        delta[1] = entry->unk44 - object->pos.y;
        D_800A2F4CCarState[0] = 4;
        delta[2] = 0;
        object->unk26C[5] = 0U;
        goto updateMotion;
    case 0x3:
        ringResult = (u16)object->unk26C[9];
        ringV1 = D_800A2EACCarState[0];
        object->speed = 0;
        object->unk84 = 0;
        object->rpm = 0;
        ringResult += 1;
        object->unk26C[9] = ringResult;
        if (ringV1 == 0) {
            if (*(s32 *)&object->unk3A4 & 0x100F) {
                if (object == D_800A3960CarState[0]) {
                    D_800A3960CarStateStore[0] = 0;
                }
                if (D_800A2EE0CarState[0] == 0) {
                    object->unkF4 = 0;
                    object->unk414 = -1;
                    func_80041848(object, 0xC);
                    return;
                }
                goto block_74;
            }
        block_74:
            if (object->unk26A == 0) {
                if (object->unk3A4 == 0) {
                    if (object->lap < (D_800A2EA8CarState[0] + 1)) {
                        D_800A3A04CarStateStore[0] = 3;
                        func_80029CB4(object);
                        control = object->type;
                        D_800A3A04CarState[0] = 0xD;
                        if (control == 0) {
                            func_80041564(object, 0x42);
                        }
                        oldWait = (u16)object->unk26C[5];
                        object->unk26C[5] = (u16)(oldWait - 1);
                        if ((oldWait << 0x10) <= 0) {
                            object->unk269 = 2U;
                        }
                        newBrake = object->unk26C[8] - 0x1E;
                        object->unk26C[8] = newBrake;
                        if ((newBrake << 16) < 0) {
                            object->unk26C[8] = 0U;
                        }
                    }
                    goto block_83;
                }
                goto block_84;
            }
        block_83:
            if (object->unk3A4 != 0) {
            block_84:
                oldDamageTime = object->unk26C[10];
                object->unk26C[10] = (u16)(oldDamageTime - 1);
                if ((oldDamageTime << 16) < 0) {
                    object->unk3A4 = 0;
                    j = 0;
                    do {
                        object->unk3A6[j] = 1;
                        object->unk3AE[j] = 0;
                        j++;
                    } while (j < 8);
                }
            } else {
                flags = object->unk26A;
                if (flags & 1) {
                    func_8003D25C(object);
                } else {
                    if (flags & 4) {
                        steerTime = object->unk26C[6];
                        steerAmount = (s16)steerTime / 10;
                        oldSteerTime = (*(volatile u16 *)&object->unk26C[6]);

                        object->unk26C[6] = (u16)(oldSteerTime - 1);
                        object->unk2A2 = (s16)steerAmount;
                        if ((oldSteerTime << 16) < 0) {
                            object->unk2A2 = 0;
                            object->unk26A = (u8)(object->unk26A & 0xFB);
                        }
                    }
                    if (object->unk26A & 8) {
                        otherSteerTime = object->unk26C[7];
                        otherSteerAmount = (s16)otherSteerTime / 10;
                        oldOtherSteerTime =
                            (*(volatile u16 *)&object->unk26C[7]);

                        object->unk26C[7] = (u16)(oldOtherSteerTime - 1);
                        object->unk2A8 = (s16)otherSteerAmount;
                        if ((oldOtherSteerTime << 16) < 0) {
                            object->unk2A8 = 0;
                            object->unk26A = (u8)(object->unk26A & 0xF7);
                        }
                    }
                }
            }
            if (object->unk26A & 2) {
                charge = object->unk28C + 0x4B;
                object->unk28C = charge;
                buttons = 0;
                if (charge >= 0x3E81) {
                    object->unk28C = 0x3E80;
                }
                if (object->type == 0) {
                    buttons = func_80029EF8(object);
                }
                if (object->unk28C == 0x3E80)
                    goto pulse;
                if (object->type == 0 && (object->unk26A & 1) == 0) {
                    mask = ~object->unk23C & 0x40;
                    if ((buttons & mask) != 0) {
                    pulse:
                        object->unk290 = 0x7D000;
                        object->unk26A &= 0xDD;
                    }
                }
                object->unk23C = buttons;
                return;
            }
        }
        return;
    case 0xFF:
        ringV1 = object->speed;
        D_800A2F4CCarState[0] = 0xA;
        if (ringV1 > 0x140000) {
            trailingOffset = sectionCount - 3;
            trailingSection =
                (s32)(object->segment + trailingOffset) % sectionCount;
            object->unk84 = 0xA0000;
            trailing = &gTrackSectionsCarState[0][trailingSection];
            if (trailing->unk34 == trailingSection) {
                delta[0] = trailing->unk38 - object->pos.x;
                delta[1] = trailing->unk3C - object->pos.y;
                delta[2] = 0;
                goto updateMotion;
            }
        } else {
            ringA1 = MathGetAngleDelta(
                object->heading,
                gTrackSectionsCarState[0][object->segment].angle);
            if (ringA1 >= 0) {
                if (ringA1 < 0x14) {
                    goto block_114;
                }
                goto block_115;
            }
            if (-ringA1 < 0x14) {
            block_114:
                ringV1 = gTrackSectionsCarState[0][object->segment].angle;
                object->unk269 = 2U;
                object->heading = ringV1;
            } else {
            block_115:
                if (ringA1 > 0) {
                    angle = (u16)object->heading + 0x3EC;
                } else {
                    angle = (u16)object->heading + 0x14;
                }
                object->heading = (s16)(angle & 0x3FF);
            }
            object->speed = 0;
            object->fineHeading = (s16)(object->heading * 4);
            ObjectAdvanceAlongHeading(object);
            func_80029CB4(object);
            object->callback(object);
            return;
        }
        return;
    default:
        /* Retail also reaches updateMotion with delta unset for unknown states. */
        break;
    }
updateMotion:
    ringResult = object->speed;
    ringV1 = object->unk84;
    ringA0 = 0x20000;
    ringV1 = ringV1 < ringResult;
    object->driveScale = ringA0;
    if (ringV1) {
        CarReduceSpeed(object);
    }
    if ((object->unk269 == 1) && (object->speed <= 0xA0000)) {
        object->speed = 0xA0000;
    }
    CarUpdateWheelVelocityComponents(object);
    direction = func_800358EC(delta);
    if (object->type == 1) {
        D_800A2F4CCarState[0] = 0xE;
    }
    CarSteerTowardHeading(object, direction);
    ringV1 = (u16)object->heading;
    D_800A2F4CCarState[0] = 0x14;
    object->movementHeading = ringV1;
    ObjectAdvanceAlongHeading(object);
    func_80029CB4(object);
    object->callback(object);
    if (object->unk269 == 3) {
        object->steering = 0;
    }
}

extern u8 D_800A372C[];
extern s32 D_800A3560;
extern s32 D_800A3820;

s32 func_8003E78C(Car *object) {
    s32 laps;
    s32 ahead;
    u32 pace;
    u8 adjustment;
    s32 lead;
    s32 lag;
    s32 near;
    s32 far;

    if (object->unk26C[14] != 0) {
        if (D_800A372C[0] != 0 && D_800A2CE0[0] == 3 && object->type == 0 &&
            object->segment >= 100)
            return 1;
        lead = D_800A3560 + 8;
        lag = D_800A3820 + 0x14;
        if (!(u8)TrackSectionIsInWrappedRange(
                object->segment,
                (D_800A39E0 - lag + gTrackSectionCount[0]) %
                    gTrackSectionCount[0],
                (D_800A376C + lead) % gTrackSectionCount[0])) {
            object->unk26C[14] = 0;
            object->unk26C[12] = (u16)object->unk26C[12] + 1;
            return 0;
        }
        return 1;
    }
    laps = object->lap;
    if (laps < 2)
        return 0;
    if (object->unk26C[5] != 0) {
        if (D_800A372C[0] != 0)
            return 0;
        near = D_800A3820 + 7;
        far = D_800A3820 + 0xF;
        if (!(u8)TrackSectionIsInWrappedRange(
                object->segment,
                (D_800A39E0 - far + gTrackSectionCount[0]) %
                    gTrackSectionCount[0],
                (D_800A39E0 - near + gTrackSectionCount[0]) %
                    gTrackSectionCount[0]))
            return 0;
        ahead = object->unk26C[11];
        pace = (u32)object->unk29C;
        adjustment = 2;
        object->unk26C[14] = 1;
        if (RandomScaledGet(5) < 0)
            object->unk29C = (pace - adjustment) + (ahead - RandomScaledGet(5));
        else
            object->unk29C = (pace - adjustment) + (ahead + RandomScaledGet(5));
        return 1;
    }
    if ((u32)laps >= (u32)object->unk29C || D_800A2EA8[0] < laps)
        object->unk26C[5] = 1;
    return 0;
}

void func_8003EA94(ModelPart *part, s32 *arg1, s32 arg2) {
    s32 *entries;
    s32 count;
    s32 value;
    s32 pad[2];
    s32 i;
    i = 0;
    entries = arg1;
    count = (part->lastVertex - part->firstVertex) + 1;
    value = part->origin.y + arg2;
    part->origin.y = value;
    if (count <= 0) {
        goto done;
    }
    entries += 3;
again:
    *entries += arg2;

    entries += 5;
    i++;
    if (i < count) {
        goto again;
    }
done:
    (void)(&pad);
}

void func_8003EAE8(Car *object, s32 index) {
    s32 pad[4];
    Model *group;
    ModelPart *entry;
    s32 count;
    s32 total;
    s32 *base;
    s32 *ptr;
    s32 i;

    group = object->shape;
    entry = &group[4].parts[index];
    count = entry->origin.y;
    if (count > 0) {
        {
            s32 low;
            s32 *table;

            low = entry->firstVertex;
            table = (s32 *)group[4].vertices;
            i = 0;
            entry->origin.y = count + 0xE;
            {
                s32 high;

                high = entry->lastVertex;
                base = (s32 *)(low * 20 + (u32)table);
                total = high - low + 1;
            }
        }
        if (total > 0) {
            ptr = base + 3;
            do {
                *ptr += 0xE;
                ptr += 5;
                i++;
            } while (i < total);
        }
    } else {
        {
            s32 low;
            s32 *table;

            low = entry->firstVertex;
            table = (s32 *)group[4].vertices;
            i = 0;
            entry->origin.y = count - 0xE;
            {
                s32 high;

                high = entry->lastVertex;
                base = (s32 *)(low * 20 + (u32)table);
                total = high - low + 1;
            }
        }
        if (total > 0) {
            ptr = base + 3;
            do {
                *ptr -= 0xE;
                ptr += 5;
                i++;
            } while (i < total);
        }
    }
}

void func_8003EBD0(Car *object, s32 index) {
    Model *group;
    ModelPart *entry;
    s32 count;
    s32 total;
    s32 *base;
    s32 *ptr;
    s32 i;
    volatile s32 pad[4];

    group = object->shape;
    entry = &group[4].parts[index];
    count = entry->origin.y;
    if (count > 0) {
        {
            s32 low;
            s32 *table;

            low = entry->firstVertex;
            table = (s32 *)group[4].vertices;
            i = 0;
            entry->origin.y = count - 0xE;
            base = (s32 *)(low * 0x14 + (u32)table);
            total = entry->lastVertex - low + 1;
        }
        if (total > 0) {
            ptr = base + 3;
            do {
                *ptr -= 0xE;
                ptr += 5;
                i++;
            } while (i < total);
        }
    } else {
        {
            s32 low;
            s32 *table;

            low = entry->firstVertex;
            table = (s32 *)group[4].vertices;
            i = 0;
            entry->origin.y = count + 0xE;
            base = (s32 *)(low * 0x14 + (u32)table);
            total = entry->lastVertex - low + 1;
        }
        if (total > 0) {
            ptr = base + 3;
            do {
                *ptr += 0xE;
                ptr += 5;
                i++;
            } while (i < total);
        }
    }
}

extern u8 D_800A387C[];
extern u8 *gCarListAbsolute[];

void func_8003ECB8(TrackCallback *object) {
    Car *current;
    register u8 *base;
    s32 id;
    s32 depth;
    s32 i;
    s32 value;
    s32 sum;
    s32 moved;
    s32 extra;
    u16 u16v;
    u8 *row;
    u8 *src;
    u8 *dst;

    current = gCarListAbsolute[0];
    base = D_800BE97C[0];
    if (current != 0) {
        id = object->callback - 1;
        for (; current != 0; current = (u8 *)current->next) {
            if (current->unk1DE == id) {
                break;
            }
        }
        if (current != 0 && current->type != 1 && current->unk268 != 0) {
            depth = current->unk26C[8];
            i = 0;
            if (i < object->count) {
                s32 *adjust;

                adjust = D_800AE84C;
                src = (u8 *)object;
                dst = (u8 *)object;
                do {
                    /* src and dst step through coord[i] and index[i]. */
                    value = ((TrackCallback *)src)->coord[0][2];
                    extra = object->offset[2];
                    u16v = ((TrackCallback *)dst)->index[0];
                    row = (u8 *)((u32)(u16v << 3) + (u32)base);
                    sum = value + extra;
                    moved = sum - depth;
                    if (moved < 0) {
                        moved += 3;
                    }
                    ((SVECTOR *)row)->vz = (moved >> 2) - adjust[0];
                    src += 6;
                    dst += 2;
                    i++;
                } while (i < object->count);
            }
        }
    }
}

extern s32 D_800A2F88;

void func_8003EDA0(Car *object) {
    u32 pace;
    s32 dist;
    s32 value;
    s32 delta;
    u8 adjustment;

    dist = gTrackSectionCount[0] * D_800A2EA8[0] / D_800A2F88;
    value = (D_800A2EA8[0] + dist) / (dist + 1) + 1;
    object->unk29C = value;
    object->unk26C[11] = value;
    if (dist != 0) {
        adjustment = 2;
        pace = (u32)object->unk29C;
        if (RandomScaledGet(5) < 0)
            delta = (pace - adjustment) - RandomScaledGet(5);
        else
            delta = (pace - adjustment) + RandomScaledGet(5);
        object->unk29C = delta;
    }
}
