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
#include "objects.h"
#include "scene.h"
#include "sound.h"
#include "util.h"

extern s32 strlen(char *);

extern u8 *gPlayerCar[];
void func_80025594();
extern s32 D_800A3A04nm[] asm("D_800A3A04.NON_MATCHING");
extern s32 D_800A39E0;
extern void func_80025594(u8 *);
extern u8 D_800B9DA4[];
void func_800298E0(s32 *car);
s32 func_80029EF8(u8 *obj);
s32 func_800370B8(s32 a, s32 b);

/* CD control and streaming. */

void func_8003C528(void) {
    u8 index;
    s32 value;
    index = gPlayerCar[0][0x376];
    value = *(s32 *)(gPlayerCar[0] + 0x25C);
    gDriverOrder[0] = index;
    D_800AE1EC[0] = value;
    D_800B9DA4[index & 0xFF] = 0;
}

extern s32 CdSetDebug(s32 level);
void CdDisableDebug(void) {
    CdSetDebug(0);
}

extern s32 D_800A2F74;
extern s32 D_800A37CC;
extern CdlLOC D_800BDEBC[];
extern s32 D_80098340[];
extern s32 D_800A45A8[];
extern s32 D_800A45AC[];

void *FileOpen(s32 fileId, void *mode) {
    u8 pad[0x40];
    u8 result[8];
    void *pos;
    s32 value;

    if (D_800A2F74 == 0) {
        CdGetToc(D_800BDEBC);
        D_800A2F74 = 1;
    }
    CdIntToPos(D_80098340[fileId * 3] + 0x13C, D_800A45A8);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = D_80098340[fileId * 3 + 1];
    D_800A45AC[0] = value;
    D_800A37CC = fileId;
    pos = &D_800A45AC[-1];
    return pos;
}

void FileClose(void) {
}

/* MATCHED 2026-10-11 (w2i). Two keys beyond the 2026-10-07 draft:
 * 1. The file-table accesses must each use a pairwise-distinct symbol
 *    name for the same address (seek D_80098340, checksum compare
 *    D_80098348.NON_MATCHING, first FntPrint D_80098348, size print
 *    D_80098344.NON_MATCHING, sector print D_80098340.NON_MATCHING):
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
extern s32 D_80098340w4[] asm("D_80098340.NON_MATCHING");
extern s32 D_80098348fp[] asm("D_80098348");

s32 FileRead(s32 buffer, s32 size, s32 count, s32 handle) {
    s32 total;
    s32 sectors;
    s32 hnd = handle;
    register s32 buf asm("s2");
    register s32 retries asm("s4");
    u8 result[0x10];
    register s32 status asm("a1");
    s32 *ptr;
    s32 i;
    s32 words;

    asm("" : "=r"(total) : "0"(count));
    retries = 0;
    total = total * size;
    DrawSync(0);
    buf = buffer;
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
    CdSeekToSector(D_80098340[D_800A37CC * 3] + 0x13C);
    CdRead(sectors, buf, 0x80);
    do {
        status = CdReadSync(1, 0);
    } while (status > 0);
    if (status == total) {
        goto retry;
    }
    ptr = (s32 *)buf;
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
    if (D_80098348nm[D_800A37CC * 3] != total) {
        if (retries < 0x32) {
            CdControl(9, 0, 0);
            CdSync(0, result);
            CdReady(0, result);
            CdInit();
            total = -1;
            goto retry;
        }
        GraphicsInit();
        FntPrint(sChecksumFailureFormat, D_80098348fp[D_800A37CC * 3], total);
        FntPrint(sFileInfoFormat, buf & 0x7FFFFFFF, D_800A37CC);
        FntPrint(sFileSizeFormat, D_80098344nm[D_800A37CC * 3]);
        FntPrint(sFileLocationFormat, D_80098340w4[D_800A37CC * 3] + 0x13C);
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

void *FileLoadToHeap(s32 arg0) {
    u8 pad[0x40];
    u8 result[8];
    s32 value;
    s32 size;
    void *buffer;

    if (D_800A2F74 == 0) {
        CdGetToc(D_800BDEBC);
        D_800A2F74 = 1;
    }
    CdIntToPos(D_80098340[arg0 * 3] + 0x13C, D_800A45A8);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = D_80098340[arg0 * 3 + 1];
    D_800A37CC = arg0;
    D_800A45AC[0] = value;
    size = (value + 0x7FF) >> 11 << 11;
    buffer = HeapAlloc(size);
    if (buffer != 0) {
        FileRead(buffer, 1, size, D_800A45A8);
    }
    return buffer;
}

void func_8003CA18(s32 arg0, s32 arg1) {
    u8 pad[0x40];
    u8 result[8];
    s32 value;

    if (D_800A2F74 == 0) {
        CdGetToc(D_800BDEBC);
        D_800A2F74 = 1;
    }
    CdIntToPos(D_80098340[arg1 * 3] + 0x13C, D_800A45A8);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = D_80098340[arg1 * 3 + 1];
    D_800A37CC = arg1;
    D_800A45AC[0] = value;
    FileRead(arg0, 1, value, D_800A45A8);
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
extern CdlLOC D_800BDEC4[];
extern s32 D_800A2F70;
extern u8 D_800A2F9CAbsolute[];

void func_8003CAE8(s32 arg0) {
    CdlATV vol;
    u8 filter[4];
    volatile u_char result[0x30];
    CdlLOC *lastPos;
    s32 remainder;
    CdlLOC *pos;

    if (CdGetToc(D_800BDEBC) < 2) {
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
        D_800A2F70 = remainder + 2;
    } else {
        D_800A2F70 = remainder + 2;
    }
    pos = &D_800BDEC4[0];
    CdIntToPos(0x19649, pos);
    lastPos = pos + 5;
    CdIntToPos(0x1C4B8, D_800BDEC4 + 1);
    CdIntToPos(0x1F278, D_800BDEC4 + 2);
    CdIntToPos(0x2219A, D_800BDEC4 + 3);
    CdIntToPos(0x250DB, D_800BDEC4 + 4);
    CdIntToPos(0x25EFF, lastPos);
    CdControl(2, (u_char *)(D_800BDEC4 + D_800A2F70 - 2), 0);
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

void func_8003CC48(void) {
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
    if (result[0] == D_800A2F70) {
        return;
    }
    CdControl(2, (u_char *)&D_800BDEBC[D_800A2F70], 0);
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

void func_8003CDBC(s32 arg0) {
    u8 pad[0x40];
    u8 result[8];
    s32 *pos;
    s32 value;
    s32 posValue;
    u32 base;
    s32 count;
    s32 i;
    s32 *src;

    if (D_800A2F74 == 0) {
        CdGetToc(D_800BDEBC);
        D_800A2F74 = 1;
    }
    CdIntToPos(D_80098340[arg0 * 3] + 0x13C, &D_800A45AC[-1]);
    while (CdSync(1, result) == 0) {
        VSync(0);
    }
    value = D_80098340[arg0 * 3 + 1];
    pos = &D_800A45AC[-1];
    D_800A37CC = arg0;
    D_800A45AC[0] = value;
    if (pos == NULL) {
        SystemShowFatalError(sInputOpenError);
    }
    posValue = D_800A45AC[0];
    base = (0x1F4000 - posValue) | RAM_CACHED_BASE;
    FileRead(base, posValue, 1, pos);
    src = (s32 *)base;
    count = *src++;
    for (i = 0; i < count; i++) {
        D_800B9F44[i] = *src++ + base;
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
typedef struct CarStateObject {
    s32 unk0;                      /* 0x000 */
    s32 unk4;                      /* 0x004 */
    s32 unk8;                      /* 0x008 */
    u8 padC[0xED];                 /* 0x00C */
    u8 unkF9;                      /* 0x0F9 */
    s16 unkFA;                     /* 0x0FA */
    u8 padFC[0x18];                /* 0x0FC */
    s16 heading;                   /* 0x114 */
    u8 pad116[0xA];                /* 0x116 */
    s16 unk120;                    /* 0x120 */
    u8 pad122[0xBE];               /* 0x122 */
    s16 unk1E0;                    /* 0x1E0 */
    u8 pad1E2[0xA];                /* 0x1E2 */
    s16 unk1EC;                    /* 0x1EC */
    u8 pad1EE[0x1D];               /* 0x1EE */
    s8 slot;                       /* 0x20B */
    u8 unk20C;                     /* 0x20C */
    u8 unk20D;                     /* 0x20D */
    u8 pad20E[0x2A];               /* 0x20E */
    s32 unk238;                    /* 0x238 */
    s32 unk23C;                    /* 0x23C */
    u8 pad240[0x28];               /* 0x240 */
    u8 unk268;                     /* 0x268 */
    u8 unk269;                     /* 0x269 */
    u8 unk26A;                     /* 0x26A */
    u8 unk26B;                     /* 0x26B */
    u8 pad26C[0x18];               /* 0x26C */
    u16 unk284;                    /* 0x284 */
    s16 unk286;                    /* 0x286 */
    u8 pad288[0x18];               /* 0x288 */
    u16 unk2A0;                    /* 0x2A0 */
    s16 unk2A2;                    /* 0x2A2 */
    s16 unk2A4;                    /* 0x2A4 */
    u16 unk2A6;                    /* 0x2A6 */
    s16 unk2A8;                    /* 0x2A8 */
    s16 unk2AA;                    /* 0x2AA */
    u8 pad2AC[0xA8];               /* 0x2AC */
    void *unk354;                  /* 0x354 */
    u8 pad358[0x8];                /* 0x358 */
    u16 unk360;                    /* 0x360 */
    u8 pad362[0x1E];               /* 0x362 */
    s32 unk380;                    /* 0x380 */
    u8 pad384[0x35];               /* 0x384 */
    u8 unk3B9;                     /* 0x3B9 */
    u8 pad3BA[0x26];               /* 0x3BA */
    struct CarStateObject *unk3E0; /* 0x3E0 */
} CarStateObject;
extern void func_80030D80(CarStateObject *, s32 *);
extern void func_80052FC4(s32);
extern s32 D_800A376C;
extern u8 D_800A38B0Lui[] asm("D_800A38B0");
extern u16 D_800A35D0Lui[] asm("D_800A35D0");
extern u16 D_800A2EC4Lui[] asm("D_800A2EC4");
extern s32 D_800A2EC4Sw[] asm("D_800A2EC4");
extern CarStateObject *gPlayerCarCar[] asm("gPlayerCar");
extern s32 D_800A3680Lui[] asm("D_800A3680");
extern s32 D_800A2EAC[];
extern s8 D_800A3564Lui[] asm("D_800A3564");
extern u8 D_800A35D4Lui[] asm("D_800A35D4");

void CarUpdateState(CarStateObject *object) {
    s32 query[3];
    s32 buttons;
    s32 heading;
    s16 segment; /* s16 local: reserves the 8-byte phantom frame slot */
    u16 value;
    CarStateObject *player;

    if (object->unk360 == 0) {
        query[0] = object->unk0;
        query[1] = object->unk4;
        query[2] = object->unk8;
        func_80030D80(object, query);
    }
    if (object->unk360 == 4) {
        if (object->unk268 == 0) {
            if (object->unk1EC == 0) {
                object->unk20D = object->unk20C;
                if (D_800A38B0Lui[0] != 0) {
                    value = D_800A35D0Lui[0];
                } else {
                    value = D_800A2EC4Lui[0];
                }
                object->unk286 = value;
                object->unk2A4 = object->unk2A0 + 8;
                object->unk2AA = object->unk2A6 + 8;
                if (ABS(func_800370B8(object->unk1E0, D_800A376C)) < 5) {
                    object->unk269 = 0xFF;
                }
                object->unk238 = PadGetButtons(object->slot);
                buttons = func_80029EF8((u8 *)object);
                object->unkF9 = 0;
                object->unk3B9 = 0;
                player = gPlayerCarCar[0];
                object->unk23C = buttons;
                object->unk120 = 0;
                if (object == player) {
                    func_80052FC4(1);
                } else if (D_800A2EA4[0] != 0 && object == player->unk3E0) {
                    func_80052FC4(2);
                }
                D_800A3680Lui[0] = 1;
                if (D_800A2CE0[0] == 3) {
                    segment = object->unk1E0;
                    if (segment < 0x10 || (u16)(segment - 0x47) < 0xE) {
                        object->unk269 = 0xFF;
                    } else if (segment >= 0x65) {
                        object->unk269 = 2;
                    }
                }
            }
            if (object->unk268 == 0 && object->unk1EC == 1) {
                if (object->unk354 != (void *)func_80025594) {
                    object->unk354 = (void *)func_80025594;
                }
                object->unkFA += RandomScaledGet(3);
                if (object->unkFA <= 0) {
                    object->unkFA = 1;
                }
            }
        }
        if (object->unk1EC == 0 && D_800A2EAC[0] == 0) {
            object->unk20C = 0;
            D_800A2EC4Sw[0] = 0;
        }
        if (object->unk268 == 0) {
            D_800A3564Lui[0] = 1;
        }
        object->unk268 = 1;
    } else {
        if (object->unk268 == 1 && object->unk1EC == 0) {
            if (D_800A35D4Lui[0] == 0) {
                D_800A2EC4Sw[0] = object->unk286;
            }
            heading = object->heading;
            object->unk20C = object->unk20D;
            object->unk380 = heading;
            object->unk284 += 1;
            D_800A3680Lui[0] = 1;
            func_8004FF3C();
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
void func_8003D25C(u8 *object) {
    s32 i;
    s32 value;
    s32 count;
    s32 diff;
    u8 flag;

    D_800A3A04nm[0] = 3;
    func_80029CB4(object);
    D_800A3A04Lui = 0xD;
    flag = 1;
    if (*(u8 *)(object + 0x26A) & 0x10) {
        i = *(u8 *)(object + 0x26A) & 0x40;
        if (D_800A2F84nm != 0) {
            i = !i;
        }
        if (i != 0) {
            *(s16 *)(object + 0x2AC) = *(s16 *)(object + 0x274) * 10;
            *(s16 *)(object + 0x2FC) = *(s16 *)(object + 0x274) * 10;
            *(s16 *)(object + 0x2D4) = *(s16 *)(object + 0x274) * 4;
            *(s16 *)(object + 0x324) = *(s16 *)(object + 0x274) * 4;
        } else {
            *(s16 *)(object + 0x2D4) = *(s16 *)(object + 0x274) * 10;
            *(s16 *)(object + 0x324) = *(s16 *)(object + 0x274) * 10;
            *(s16 *)(object + 0x2AC) = *(s16 *)(object + 0x274) * 4;
            *(s16 *)(object + 0x2FC) = *(s16 *)(object + 0x274) * 4;
        }
        for (i = 0; i < 4; i++) {
            if (*(u8 *)(object + 0x26A) & 0x40) {
                if (i < 2) {
                    continue;
                }
            } else {
                if (i >= 2) {
                    break;
                }
            }
            value = *(u16 *)(object + i * 2 + 0x26C);
            *(u16 *)(object + i * 2 + 0x26C) = value - 1;
            count = (s16)(value - 1);
            if (count == 0x5A) {
                goto special;
            }
            if (count == 5) {
            special:
                if (*(s16 *)(object + 0x1EC) == 0) {
                    func_800414E0(object, 8, 3);
                }
                *(u16 *)(object + i * 2 + 0x26C) =
                    *(u16 *)(object + i * 2 + 0x26C) - 1;
            } else if (count == 0x46) {
                diff = value - 2;
                *(s16 *)(object + i * 2 + 0x26C) = diff;
            } else if (count == 0x28) {
                diff = value - 2;
                *(s16 *)(object + i * 2 + 0x26C) = diff;
                func_8002D3EC(object);
                *(u8 *)(object + i + 0x3A6) = 1;
            }
            do {
                if (*(s16 *)(object + i * 2 + 0x26C) > 0) {
                    flag = 0;
                }
            } while (0);
        }
        if (flag != 0) {
            if (*(u8 *)(object + 0x26A) & 0x40) {
                *(u8 *)(object + 0x26A) &= 0xAE;
            } else {
                *(s16 *)(object + 0x274) = -0x23;
                *(u8 *)(object + 0x26A) =
                    (*(u8 *)(object + 0x26A) | 0x40) & 0xEF;
            }
            i = 3;
            do {
                *(s16 *)(object + i * 0x28 + 0x2B0) = 0;
                i--;
            } while (i >= 0);
        } else {
            if (*(s16 *)(object + 0x274) < 4) {
                *(s16 *)(object + 0x274) = *(s16 *)(object + 0x274) + 1;
            }
        }
    } else {
        if ((s16)++ * (u16 *)(object + 0x274) == 5) {
            *(u8 *)(object + 0x26A) |= 0x10;
            *(s16 *)(object + 0x274) = 0;
            if (*(u8 *)(object + 0x26A) & 0x40) {
                *(s16 *)(object + 0x270) = 100;
                *(s16 *)(object + 0x272) = 100;
            } else {
                *(s16 *)(object + 0x26C) = 100;
                *(s16 *)(object + 0x26E) = 100;
            }
        }
    }
}

void func_8003D528(u8 *object) {
    s32 result;
    s32 value;
    s32 mask;

    value = *(s32 *)(object + 0x28C) + 0x4B;
    *(s32 *)(object + 0x28C) = value;
    result = 0;
    if (value >= 0x3E81) {
        *(s32 *)(object + 0x28C) = 0x3E80;
    }
    if (*(s16 *)(object + 0x1EC) == 0) {
        result = func_80029EF8(object);
    }
    if (*(s32 *)(object + 0x28C) == 0x3E80) {
        goto trigger;
    }
    if (*(s16 *)(object + 0x1EC) == 0 && (*(u8 *)(object + 0x26A) & 1) == 0) {
        mask = ~*(s32 *)(object + 0x23C) & 0x40;
        if ((result & mask) != 0) {
        trigger:
            *(s32 *)(object + 0x290) = 0x7D000;
            *(u8 *)(object + 0x26A) &= 0xDD;
        }
    }
    *(s32 *)(object + 0x23C) = result;
}

void func_8003D5F8(u8 *object) {
    u16 flags;
    s32 i;
    u32 total;
    u8 *entry;

    flags = *(u16 *)(object + 0x3A4);
    total = 0;
    if (flags != 0) {
        i = 0;
        do {
            entry = object + i;
            if (*(s8 *)(entry + 0x3A6) == 0) {
                total = total + 0x14;
            }
            if (*(s8 *)(entry + 0x3AE) != 0) {
                total = total + *(s8 *)(entry + 0x3AE) * 3;
            }
            i = i + 1;
        } while (i < 8);
    }
    *(u16 *)(object + 0x280) = total;
}

void func_8003D654(u8 *object) {
    s32 i;
    u16 count;
    count = *(u16 *)(object + 0x280);
    *(u16 *)(object + 0x280) = count - 1;
    if ((s16)count < 0) {
        *(s16 *)(object + 0x3A4) = 0;
        i = 0;
        do {
            *(object + i + 0x3A6) = 1;
            *(object + i + 0x3AE) = 0;
            i++;
        } while (i < 8);
    }
}

void func_8003D69C(u8 *object) {
    s32 value;
    s32 now;

    value = *(volatile u16 *)(object + 0x278);
    now = *(u16 *)(object + 0x278);
    *(u16 *)(object + 0x278) = now - 1;
    *(s16 *)(object + 0x2A2) = (s16)value / 10;
    if ((now << 16) < 0) {
        *(u16 *)(object + 0x2A2) = 0;
        *(u8 *)(object + 0x26A) &= ~0x04;
    }
}

void func_8003D6F8(u8 *object) {
    s32 value;
    s32 now;

    value = *(volatile u16 *)(object + 0x27A);
    now = *(u16 *)(object + 0x27A);
    *(u16 *)(object + 0x27A) = now - 1;
    *(s16 *)(object + 0x2A8) = (s16)value / 10;
    if ((now << 16) < 0) {
        *(u16 *)(object + 0x2A8) = 0;
        *(u8 *)(object + 0x26A) &= ~0x08;
    }
}

void func_8003D754(u8 *object) {
    s32 buttons;

    buttons = PadGetButtons(*(s8 *)(object + 0x20B));
    if (buttons & ((u16) ~*(s32 *)(object + 0x238) & 0x1000)) {
        *(u8 *)(object + 0x26B) -= 1;
        func_800414E0(object, 10, 6);
    } else if (buttons & ((u16) ~*(s32 *)(object + 0x238) & 0x4000)) {
        *(u8 *)(object + 0x26B) += 1;
        func_800414E0(object, 10, 6);
    }
    *(u8 *)(object + 0x26B) = (*(u8 *)(object + 0x26B) + 4) % 4;
    if (buttons & ((u16) ~*(s32 *)(object + 0x238) & 0x8000)) {
        func_800414E0(object, 10, 6);
        switch (*(u8 *)(object + 0x26B)) {
        case 0:
            if (*(u8 *)(object + 0x26A) & 1) {
                *(u8 *)(object + 0x26A) &= 0xFE;
            } else {
                *(u8 *)(object + 0x26A) |= 1;
            }
            break;
        case 1:
            if (*(u8 *)(object + 0x26A) & 2) {
                *(u8 *)(object + 0x26A) &= 0xFD;
            } else {
                *(u8 *)(object + 0x26A) |= 2;
            }
            break;
        case 2:
            if (*(s16 *)(object + 0x2AA) >= -7) {
                *(u16 *)(object + 0x2A8) -= 1;
                *(u16 *)(object + 0x2AA) -= 1;
            }
            break;
        case 3:
            if (*(s16 *)(object + 0x2A4) >= -7) {
                *(u16 *)(object + 0x2A2) -= 1;
                *(u16 *)(object + 0x2A4) -= 1;
            }
            break;
        }
        if (*(s16 *)(object + 0x2A2) < -16) {
            *(s16 *)(object + 0x2A2) = -16;
        }
        if (*(s16 *)(object + 0x2A8) < -16) {
            *(s16 *)(object + 0x2A8) = -16;
        }
    }
    if (buttons & ((u16) ~*(s32 *)(object + 0x238) & 0x2000)) {
        func_800414E0(object, 10, 6);
        switch (*(u8 *)(object + 0x26B)) {
        case 0:
            if (*(u8 *)(object + 0x26A) & 1) {
                *(u8 *)(object + 0x26A) &= 0xFE;
            } else {
                *(u8 *)(object + 0x26A) |= 1;
            }
            break;
        case 1:
            if (*(u8 *)(object + 0x26A) & 2) {
                *(u8 *)(object + 0x26A) &= 0xFD;
            } else {
                *(u8 *)(object + 0x26A) |= 2;
            }
            break;
        case 2:
            if (*(s16 *)(object + 0x2AA) < 8) {
                *(u16 *)(object + 0x2A8) += 1;
                *(u16 *)(object + 0x2AA) += 1;
            }
            break;
        case 3:
            if (*(s16 *)(object + 0x2A4) < 8) {
                *(u16 *)(object + 0x2A2) += 1;
                *(u16 *)(object + 0x2A4) += 1;
            }
            break;
        }
        if (*(s16 *)(object + 0x2A2) >= 17) {
            *(s16 *)(object + 0x2A2) = 16;
        }
        if (*(s16 *)(object + 0x2A8) >= 17) {
            *(s16 *)(object + 0x2A8) = 16;
        }
    }
    *(u8 *)(object + 0x26A) &= 0xF3;
    if (*(s16 *)(object + 0x2A2) != 0) {
        *(u8 *)(object + 0x26A) |= 4;
    }
    if (*(s16 *)(object + 0x2A8) != 0) {
        *(u8 *)(object + 0x26A) |= 8;
    }
    *(s32 *)(object + 0x238) = buttons;
}

s32 func_8003DAD0(s32 a, s32 b) {
    if (b >= gTrackSectionCount[0]) {
        if (a >= gTrackSectionCount[0] / 2)
            return 0;
        b -= gTrackSectionCount[0];
    }
    return !(a < b);
}

__inline__ s32 func_8003DB18(s32 start, s32 end, s32 value) {
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

extern void func_8003D754(u8 *);
extern void CarSteerTowardHeading(u8 *, s32);
extern void func_80041564(u8 *, s32);
extern s32 D_800A2EA8CarState[] asm("D_800A2EA8");
extern s32 D_800A2EACCarState[] asm("D_800A2EAC");
extern s32 D_800A2EB0CarState[] asm("D_800A2EB0");
extern u8 D_800A2EE0CarState[] asm("D_800A2EE0");
extern s32 D_800A2F4CCarState[] asm("D_800A2F4C");
extern u8 *gPlayerCarCarState[] asm("gPlayerCar");
extern u8 *D_800A3960CarState[] asm("D_800A3960");
extern s32 D_800A39E0CarState asm("D_800A39E0");
extern s32 D_800A3A04CarState[] asm("D_800A3A04");
extern s32 gTrackSectionCountCarState[] asm("gTrackSectionCount");
extern u8 *gTrackSectionsCarState[] asm("gTrackSections");

extern u8 *D_800A3960CarStateStore[] asm("D_800A3960");
extern s32 D_800A3A04CarStateStore[] asm("D_800A3A04");
void func_8003DBA8(u8 *object) {
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
    u8 *earlier;
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
    register s32 angleDelta asm("a1");
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
    u8 *trailing;
    u8 *entry;
    u8 *targets;
    u8 *previous;
    u8 *damage;

    sectionCount = gTrackSectionCountCarState[0];
    section = *(s16 *)(object + 0x1E0);
    if ((sectionCount < section) || (section < 0)) {
        section = 0;
    }
    entry = gTrackSectionsCarState[0] + (section * 0x90);
    targets = entry + 0x34;
    if (*(s16 *)(entry + 0x34) != section) {
        *(s16 *)(entry + 0x34) = section;
        *(s16 *)(entry + 0x36) = 0;
        previousOffset = gTrackSectionCountCarState[0] - 1;
        earlierOffset = gTrackSectionCountCarState[0] - 2;
        earlierSection =
            (s32)(section + earlierOffset) % (s32)gTrackSectionCountCarState[0];
        previous =
            gTrackSectionsCarState[0] + (((s32)(section + previousOffset) %
                                          (s32)gTrackSectionCountCarState[0]) *
                                         0x90);
        earlier = gTrackSectionsCarState[0] + (earlierSection * 0x90);
        coordinate = *(s32 *)(previous + 0x40);
        *(s32 *)(entry + 0x40) =
            (s32)((coordinate - *(s32 *)(earlier + 0x40)) + coordinate);
        coordinateY = *(s32 *)(previous + 0x44);
        *(s32 *)(entry + 0x44) =
            (s32)((coordinateY - *(s32 *)(earlier + 0x44)) + coordinateY);
        targetX = *(s32 *)(previous + 0x38);
        *(s32 *)(entry + 0x38) =
            (s32)((targetX - *(s32 *)(earlier + 0x38)) + targetX);
        targetY = *(s32 *)(previous + 0x3C);
        *(s32 *)(entry + 0x3C) =
            (s32)((targetY - *(s32 *)(earlier + 0x3C)) + targetY);
        trailingX = *(s32 *)(previous + 0x48);
        *(s32 *)(entry + 0x48) =
            (s32)((trailingX - *(s32 *)(earlier + 0x48)) + trailingX);
        trailingY = *(s32 *)(previous + 0x4C);
        *(s32 *)(entry + 0x4C) =
            (s32)((trailingY - *(s32 *)(earlier + 0x4C)) + trailingY);
    }
    state = *(u8 *)(object + 0x269);
    offset = *(s16 *)(object + 0x28A);
    *(s32 *)(object + 0x84) = 0xAA0000;
    *(s32 *)(object + 0x22C) = 0;
    switch (state) {
    case 0x0:
        delta[0] = *(s32 *)(entry + 0x38) - *(s32 *)(object + 0x0);
        delta[1] = *(s32 *)(entry + 0x3C) - *(s32 *)(object + 0x4);
        delta[2] = 0;
        *(u16 *)(object + 0x276) = 0xFU;
        *(u16 *)(object + 0x278) = 0U;
        *(u16 *)(object + 0x27E) = 0U;
        if ((*(s16 *)(object + 0x1EC) == 0) &&
            ((D_800A2EE0CarState[0] != 0) ||
             !(*(s32 *)(object + 0x3A4) & 0x100F))) {
            func_8003D754(object);
        }
        if (MathGetAngleDelta(*(s16 *)(object + 0x114),
                              *(u16 *)(gTrackSectionsCarState[0] +
                                       *(s16 *)(object + 0x1E0) * 0x90 +
                                       0x10)) < 0) {
            if (-MathGetAngleDelta(*(s16 *)(object + 0x114),
                                   *(u16 *)(gTrackSectionsCarState[0] +
                                            *(s16 *)(object + 0x1E0) * 0x90 +
                                            0x10)) < 0x15) {
                turnLimit = 4;
            } else {
                turnLimit = 0x14;
            }
        } else {
            if (MathGetAngleDelta(*(s16 *)(object + 0x114),
                                  *(u16 *)(gTrackSectionsCarState[0] +
                                           *(s16 *)(object + 0x1E0) * 0x90 +
                                           0x10)) >= 0x15) {
                turnLimit = 0x14;
            } else {
                turnLimit = 4;
            }
        }
        ringResult = D_800A39E0CarState;
        D_800A2F4CCarState[0] = turnLimit;
        asm("" : "=r"(ringResult) : "0"(ringResult) : "memory");
        ringV1 = gTrackSectionCountCarState[0];
        ringA1 = *(s16 *)(object + 0x1E0);
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
            if (*(u8 *)(object + 0x26A) != 0) {
                nextState = 1;
            }
            *(u8 *)(object + 0x269) = nextState;
        }
        if ((D_800A2EB0CarState[0] == 0) && (*(s8 *)(object + 0x204) == 1) &&
            (D_800A2EA8CarState[0] >= *(s16 *)(object + 0x1D6))) {
            func_80041564(gPlayerCarCarState[0], 0x23);
        }
        goto updateMotion;
    case 0x1:
        if ((*(s16 *)(object + 0x1EC) == 0) &&
            ((D_800A2EE0CarState[0] != 0) ||
             !(*(s32 *)(object + 0x3A4) & 0x100F))) {
            func_8003D754(object);
        }
        delta[0] = *(s32 *)(targets + 0x14) - *(s32 *)(object + 0);
        ringResult = *(s32 *)(targets + 0x18);
        ringV1 = *(s32 *)(object + 4);
        ringResult -= ringV1;
        ringV1 = D_800A39E0CarState;
        delta[2] = 0;
        delta[1] = ringResult;
        *(s32 *)(object + 0x84) = 0x6B0000;
        ringA0 = gTrackSectionCountCarState[0];
        ringA1 = *(s16 *)(object + 0x1E0);
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
            *(s32 *)(object + 0x84) = 0x3D0000;
            brake = *(u16 *)(object + 0x27C) + 0x14;
            *(u16 *)(object + 0x27C) = brake;
            if ((s16)brake >= 0x15F) {
                *(u16 *)(object + 0x27C) = 0x15EU;
            }
        }
        {
            const s32 section = *(s16 *)(object + 0x1E0);
            s32 end = D_800A39E0CarState + offset + 1;
            register s32 count asm("v1");
            count = gTrackSectionCountCarState[0];
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
            ringResult = 3;
            ringV1 = *(s16 *)(object + 0x2A2);
            *(u8 *)(object + 0x269) = ringResult;
            *(u16 *)(object + 0x274) = 0;
            if (ringV1 < 0)
                ringV1 = -ringV1;
            ringResult = ringV1 * 10;
            asm("" : "=r"(ringResult) : "0"(ringResult) : "memory");
            ringV1 = *(s16 *)(object + 0x2A8);
            *(u16 *)(object + 0x278) = ringResult;
            if (ringV1 < 0)
                ringV1 = -ringV1;
            ringResult = ringV1 * 5;
            ringA3 = ringResult * 2;
            ringResult = *(u16 *)(object + 0x2A0);
            ringA0 = *(u16 *)(object + 0x2A2);
            ringV1 = *(u16 *)(object + 0x2A6);
            ringA1 = *(u16 *)(object + 0x2A8);
            ringA2 = *(s32 *)(object + 0x28C);
            *(u16 *)(object + 0x27A) = ringA3;
            ringResult += ringA0;
            ringV1 += ringA1;
            *(u16 *)(object + 0x2A0) = ringResult;
            *(u16 *)(object + 0x2A6) = ringV1;
            if (ringA2 == 0) {
                *(s32 *)(object + 0x28C) = 0x64;
            }
            damageTime = 0;
            if (*(u16 *)(object + 0x3A4) != 0) {
                i = 0;
                do {
                    damage = object + i;
                    if (*(s8 *)(damage + 0x3A6) == 0) {
                        damageTime += 0x14;
                    }
                    severity = *(s8 *)(damage + 0x3AE);
                    if (severity != 0) {
                        damageTime += severity * 3;
                    }
                    i += 1;
                } while (i < 8);
            }
            *(u16 *)(object + 0x280) = damageTime;
        }
        goto updateMotion;
    case 0x2:
        delta[0] = *(s32 *)(entry + 0x40) - *(s32 *)(object + 0x0);
        delta[1] = *(s32 *)(entry + 0x44) - *(s32 *)(object + 0x4);
        D_800A2F4CCarState[0] = 4;
        delta[2] = 0;
        *(u16 *)(object + 0x276) = 0U;
        goto updateMotion;
    case 0x3:
        ringResult = *(u16 *)(object + 0x27E);
        ringV1 = D_800A2EACCarState[0];
        *(s32 *)(object + 0x90) = 0;
        *(s32 *)(object + 0x84) = 0;
        *(u16 *)(object + 0x108) = 0;
        ringResult += 1;
        *(u16 *)(object + 0x27E) = ringResult;
        if (ringV1 == 0) {
            if (*(s32 *)(object + 0x3A4) & 0x100F) {
                if (object == D_800A3960CarState[0]) {
                    D_800A3960CarStateStore[0] = 0;
                }
                if (D_800A2EE0CarState[0] == 0) {
                    *(u8 *)(object + 0xF4) = 0;
                    *(s32 *)(object + 0x414) = -1;
                    func_80041848(object, 0xC);
                    return;
                }
                goto block_74;
            }
        block_74:
            if (*(u8 *)(object + 0x26A) == 0) {
                if (*(u16 *)(object + 0x3A4) == 0) {
                    if (*(s16 *)(object + 0x1D6) <
                        (D_800A2EA8CarState[0] + 1)) {
                        D_800A3A04CarStateStore[0] = 3;
                        func_80029CB4(object);
                        control = *(s16 *)(object + 0x1EC);
                        D_800A3A04CarState[0] = 0xD;
                        if (control == 0) {
                            func_80041564(object, 0x42);
                        }
                        oldWait = *(u16 *)(object + 0x276);
                        *(u16 *)(object + 0x276) = (u16)(oldWait - 1);
                        if ((oldWait << 0x10) <= 0) {
                            *(u8 *)(object + 0x269) = 2U;
                        }
                        newBrake = *(u16 *)(object + 0x27C) - 0x1E;
                        *(u16 *)(object + 0x27C) = newBrake;
                        if ((newBrake << 16) < 0) {
                            *(u16 *)(object + 0x27C) = 0U;
                        }
                    }
                    goto block_83;
                }
                goto block_84;
            }
        block_83:
            if (*(u16 *)(object + 0x3A4) != 0) {
            block_84:
                oldDamageTime = *(u16 *)(object + 0x280);
                *(u16 *)(object + 0x280) = (u16)(oldDamageTime - 1);
                if ((oldDamageTime << 16) < 0) {
                    *(u16 *)(object + 0x3A4) = 0;
                    j = 0;
                    do {
                        *(object + j + 0x3A6) = 1;
                        *(object + j + 0x3AE) = 0;
                        j++;
                    } while (j < 8);
                }
            } else {
                flags = *(u8 *)(object + 0x26A);
                if (flags & 1) {
                    func_8003D25C(object);
                } else {
                    if (flags & 4) {
                        steerTime = *(u16 *)(object + 0x278);
                        steerAmount = (s16)steerTime / 10;
                        oldSteerTime = (*(volatile u16 *)(object + 0x278));

                        *(u16 *)(object + 0x278) = (u16)(oldSteerTime - 1);
                        *(s16 *)(object + 0x2A2) = (s16)steerAmount;
                        if ((oldSteerTime << 16) < 0) {
                            *(s16 *)(object + 0x2A2) = 0;
                            *(u8 *)(object + 0x26A) =
                                (u8)(*(u8 *)(object + 0x26A) & 0xFB);
                        }
                    }
                    if (*(u8 *)(object + 0x26A) & 8) {
                        otherSteerTime = *(u16 *)(object + 0x27A);
                        otherSteerAmount = (s16)otherSteerTime / 10;
                        oldOtherSteerTime = (*(volatile u16 *)(object + 0x27A));

                        *(u16 *)(object + 0x27A) = (u16)(oldOtherSteerTime - 1);
                        *(s16 *)(object + 0x2A8) = (s16)otherSteerAmount;
                        if ((oldOtherSteerTime << 16) < 0) {
                            *(s16 *)(object + 0x2A8) = 0;
                            *(u8 *)(object + 0x26A) =
                                (u8)(*(u8 *)(object + 0x26A) & 0xF7);
                        }
                    }
                }
            }
            if (*(u8 *)(object + 0x26A) & 2) {
                charge = *(s32 *)(object + 0x28C) + 0x4B;
                *(s32 *)(object + 0x28C) = charge;
                buttons = 0;
                if (charge >= 0x3E81) {
                    *(s32 *)(object + 0x28C) = 0x3E80;
                }
                if (*(s16 *)(object + 0x1EC) == 0) {
                    buttons = func_80029EF8(object);
                }
                if (*(s32 *)(object + 0x28C) == 0x3E80)
                    goto pulse;
                if (*(s16 *)(object + 0x1EC) == 0 &&
                    (*(u8 *)(object + 0x26A) & 1) == 0) {
                    mask = ~*(s32 *)(object + 0x23C) & 0x40;
                    if ((buttons & mask) != 0) {
                    pulse:
                        *(s32 *)(object + 0x290) = 0x7D000;
                        *(u8 *)(object + 0x26A) &= 0xDD;
                    }
                }
                *(s32 *)(object + 0x23C) = buttons;
                return;
            }
        }
        return;
    case 0xFF:
        ringV1 = *(s32 *)(object + 0x90);
        D_800A2F4CCarState[0] = 0xA;
        if (ringV1 > 0x140000) {
            trailingOffset = sectionCount - 3;
            trailingSection =
                (s32)(*(s16 *)(object + 0x1E0) + trailingOffset) % sectionCount;
            *(s32 *)(object + 0x84) = 0xA0000;
            trailing = gTrackSectionsCarState[0] + (trailingSection * 0x90);
            if (*(s16 *)(trailing + 0x34) == trailingSection) {
                delta[0] = *(s32 *)(trailing + 0x38) - *(s32 *)(object + 0x0);
                delta[1] = *(s32 *)(trailing + 0x3C) - *(s32 *)(object + 0x4);
                delta[2] = 0;
                goto updateMotion;
            }
        } else {
            angleDelta = MathGetAngleDelta(
                *(s16 *)(object + 0x114),
                *(u16 *)(gTrackSectionsCarState[0] +
                         *(s16 *)(object + 0x1E0) * 0x90 + 0x10));
            if (angleDelta >= 0) {
                if (angleDelta < 0x14) {
                    goto block_114;
                }
                goto block_115;
            }
            if (-angleDelta < 0x14) {
            block_114:
                ringV1 = *(u16 *)(gTrackSectionsCarState[0] +
                                  *(s16 *)(object + 0x1E0) * 0x90 + 0x10);
                *(u8 *)(object + 0x269) = 2U;
                *(s16 *)(object + 0x114) = ringV1;
            } else {
            block_115:
                if (angleDelta > 0) {
                    angle = (u16) * (s16 *)(object + 0x114) + 0x3EC;
                } else {
                    angle = (u16) * (s16 *)(object + 0x114) + 0x14;
                }
                *(s16 *)(object + 0x114) = (s16)(angle & 0x3FF);
            }
            *(s32 *)(object + 0x90) = 0;
            *(s16 *)(object + 0x116) = (s16)(*(s16 *)(object + 0x114) * 4);
            func_80037130(object);
            func_80029CB4(object);
            (*(void (**)(u8 *))(object + 0x354))(object);
            return;
        }
        return;
    default:
        /* Retail also reaches updateMotion with delta unset for unknown states. */
        break;
    }
updateMotion:
    ringResult = *(s32 *)(object + 0x90);
    ringV1 = *(s32 *)(object + 0x84);
    ringA0 = 0x20000;
    ringV1 = ringV1 < ringResult;
    *(s32 *)(object + 0x88) = ringA0;
    if (ringV1) {
        func_80028F98(object);
    }
    if ((*(u8 *)(object + 0x269) == 1) &&
        (*(s32 *)(object + 0x90) <= 0xA0000)) {
        *(s32 *)(object + 0x90) = 0xA0000;
    }
    func_800298E0(object);
    direction = func_800358EC(delta);
    if (*(s16 *)(object + 0x1EC) == 1) {
        D_800A2F4CCarState[0] = 0xE;
    }
    CarSteerTowardHeading(object, direction);
    ringV1 = *(u16 *)(object + 0x114);
    D_800A2F4CCarState[0] = 0x14;
    *(u16 *)(object + 0x104) = ringV1;
    func_80037130(object);
    func_80029CB4(object);
    (*(void (**)(u8 *))(object + 0x354))(object);
    if (*(u8 *)(object + 0x269) == 3) {
        *(s16 *)(object + 0x20E) = 0;
    }
}

extern u8 D_800A372C[];
extern s32 D_800A3560;
extern s32 D_800A3820;

s32 func_8003E78C(u8 *object) {
    s32 laps;
    s32 ahead;
    u32 pace;
    u8 adjustment;
    s32 lead;
    s32 lag;
    s32 near;
    s32 far;

    if (*(s16 *)(object + 0x288) != 0) {
        if (D_800A372C[0] != 0 && D_800A2CE0[0] == 3 &&
            *(s16 *)(object + 0x1EC) == 0 && *(s16 *)(object + 0x1E0) >= 100)
            return 1;
        lead = D_800A3560 + 8;
        lag = D_800A3820 + 0x14;
        if (!(u8)func_8003DB18(*(s16 *)(object + 0x1E0),
                               (D_800A39E0 - lag + gTrackSectionCount[0]) %
                                   gTrackSectionCount[0],
                               (D_800A376C + lead) % gTrackSectionCount[0])) {
            *(s16 *)(object + 0x288) = 0;
            *(u16 *)(object + 0x284) = *(u16 *)(object + 0x284) + 1;
            return 0;
        }
        return 1;
    }
    laps = *(s16 *)(object + 0x1D6);
    if (laps < 2)
        return 0;
    if (*(s16 *)(object + 0x276) != 0) {
        if (D_800A372C[0] != 0)
            return 0;
        near = D_800A3820 + 7;
        far = D_800A3820 + 0xF;
        if (!(u8)func_8003DB18(*(s16 *)(object + 0x1E0),
                               (D_800A39E0 - far + gTrackSectionCount[0]) %
                                   gTrackSectionCount[0],
                               (D_800A39E0 - near + gTrackSectionCount[0]) %
                                   gTrackSectionCount[0]))
            return 0;
        ahead = *(s16 *)(object + 0x282);
        pace = *(u32 *)(object + 0x29C);
        adjustment = 2;
        *(s16 *)(object + 0x288) = 1;
        if (RandomScaledGet(5) < 0)
            *(s32 *)(object + 0x29C) =
                (pace - adjustment) + (ahead - RandomScaledGet(5));
        else
            *(s32 *)(object + 0x29C) =
                (pace - adjustment) + (ahead + RandomScaledGet(5));
        return 1;
    }
    if ((u32)laps >= (u32) * (s32 *)(object + 0x29C) || D_800A2EA8[0] < laps)
        *(s16 *)(object + 0x276) = 1;
    return 0;
}

void func_8003EA94(u8 *object, s32 *arg1, s32 arg2) {
    s32 *entries;
    s32 count;
    s32 value;
    s32 pad[2];
    s32 i;
    i = 0;
    entries = arg1;
    count = ((*((s16 *)(object + 2))) - (*((s16 *)(object + 0)))) + 1;
    value = (*((s32 *)(object + 8))) + arg2;
    *((s32 *)(object + 8)) = value;
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

void func_8003EAE8(u8 *object, s32 index) {
    s32 pad[4];
    u8 *group;
    u8 *entry;
    s32 count;
    s32 total;
    s32 *base;
    s32 *ptr;
    s32 i;

    group = *(u8 **)(object + 0x370);
    entry = *(u8 **)(group + 0x150);
    entry += index * 0x18;
    count = *(s32 *)(entry + 8);
    if (count > 0) {
        {
            s32 low;
            s32 *table;

            low = *(s16 *)(entry + 0);
            table = *(s32 **)(group + 0x124);
            i = 0;
            *(s32 *)(entry + 8) = count + 0xE;
            {
                s32 high;

                high = *(s16 *)(entry + 2);
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

            low = *(s16 *)(entry + 0);
            table = *(s32 **)(group + 0x124);
            i = 0;
            *(s32 *)(entry + 8) = count - 0xE;
            {
                s32 high;

                high = *(s16 *)(entry + 2);
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

void func_8003EBD0(u8 *object, s32 index) {
    u8 *group;
    u8 *entry;
    s32 count;
    s32 total;
    s32 *base;
    s32 *ptr;
    s32 i;
    volatile s32 pad[4];

    group = *(u8 **)(object + 0x370);
    entry = *(u8 **)(group + 0x150);
    entry += index * 0x18;
    count = *(s32 *)(entry + 8);
    if (count > 0) {
        {
            s32 low;
            s32 *table;

            low = *(s16 *)(entry + 0);
            table = *(s32 **)(group + 0x124);
            i = 0;
            *(s32 *)(entry + 8) = count - 0xE;
            base = (s32 *)(low * 0x14 + (u32)table);
            total = *(s16 *)(entry + 2) - low + 1;
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

            low = *(s16 *)(entry + 0);
            table = *(s32 **)(group + 0x124);
            i = 0;
            *(s32 *)(entry + 8) = count + 0xE;
            base = (s32 *)(low * 0x14 + (u32)table);
            total = *(s16 *)(entry + 2) - low + 1;
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

/* The two pins put base and the src walker in retail's registers. The
 * opaque dst copy keeps cse from copying it out of src, and the explicit
 * `adjust` local keeps the D_800AE84C address ahead of the walker copies. */
void func_8003ECB8(u8 *object) {
    u8 *current;
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
    register u8 *src asm("$8");
    u8 *dst;

    current = *(u8 **)(D_800A387C - 4);
    base = D_800BE97C[0];
    if (current != 0) {
        id = *(s16 *)(object + 0xC) - 1;
        for (; current != 0; current = *(u8 **)(current + 0x3E0)) {
            if (*(s16 *)(current + 0x1DE) == id) {
                break;
            }
        }
        if (current != 0 && *(s16 *)(current + 0x1EC) != 1 &&
            *(u8 *)(current + 0x268) != 0) {
            depth = *(s16 *)(current + 0x27C);
            i = 0;
            if (i < *(s16 *)(object + 0xA)) {
                s32 *adjust;

                adjust = D_800AE84C;
                src = object;
                asm("" : "=r"(dst) : "0"(object));
                do {
                    current = src;
                    value = *(s16 *)(current + 0x94);
                    extra = *(s32 *)(object + 0x218);
                    u16v = *(u16 *)(dst + 0x10);
                    row = (u8 *)((u32)(u16v << 3) + (u32)base);
                    sum = value + extra;
                    moved = sum - depth;
                    if (moved < 0) {
                        moved += 3;
                    }
                    *(s16 *)(row + 4) = (moved >> 2) - adjust[0];
                    src += 6;
                    dst += 2;
                    i++;
                } while (i < *(s16 *)(object + 0xA));
            }
        }
    }
}

extern s32 D_800A2F88;

void func_8003EDA0(u8 *object) {
    u32 pace;
    s32 dist;
    s32 value;
    s32 delta;
    u8 adjustment;

    dist = gTrackSectionCount[0] * D_800A2EA8[0] / D_800A2F88;
    value = (D_800A2EA8[0] + dist) / (dist + 1) + 1;
    *(s32 *)(object + 0x29C) = value;
    *(s16 *)(object + 0x282) = value;
    if (dist != 0) {
        adjustment = 2;
        pace = *(u32 *)(object + 0x29C);
        if (RandomScaledGet(5) < 0)
            delta = (pace - adjustment) - RandomScaledGet(5);
        else
            delta = (pace - adjustment) + RandomScaledGet(5);
        *(s32 *)(object + 0x29C) = delta;
    }
}
