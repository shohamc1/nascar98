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
#include "util.h"

extern Car *gCarListnm[] asm("gCarList.NON_MATCHING");
void PadResetAndInitializeBuffers();

/* Controller state and input. */

void PadInitialize(void) {
    PadResetAndInitializeBuffers();
}

extern s32 gPadBuffers[];
extern u32 D_8008CA04[];
extern u32 D_8008CA08[];
extern u32 D_8008CA0C[];
extern u32 D_8008CA10[];
extern u32 D_8008CA14[];
extern u32 D_8008CA18[];
extern u32 D_8008CA1C[];
extern u32 D_8008CA20[];
extern u32 D_800B9DF8[];
extern u32 D_800B9E00[];
extern u32 D_800B9E04[];
extern void func_80041F54(s32 *, s32 *, s32, s32);

void PadResetAndInitializeBuffers(void) {
    D_8008CA14[0] = 0xFFFF0000;
    D_8008CA18[0] = 0;
    D_8008CA1C[0] = 0xFFFF0000;
    D_8008CA20[0] = 0;
    D_8008CA04[0] = gPadBuffers[0];
    D_8008CA08[0] = D_800B9DF8[0];
    D_8008CA0C[0] = D_800B9E00[0];
    D_8008CA10[0] = D_800B9E04[0];
    func_80041F54(gPadBuffers, D_8008CA04, D_800B9DF8[0], D_800B9E00[0]);
}

extern u16 D_8008CA04U16[] asm("D_8008CA04");
s32 PadGetButtons(s32 index) {
    return D_8008CA04U16[index * 4];
}

u16 PadGetButtonWord(s32 index) {
    return D_8008CA04U16[index];
}

/* Wall: retail computes the nibble before the 0xFF branch and keeps it
 * in a0 with a final move v0,a0 on both paths; our shapes either go
 * branchless (xori/sltu/negu) or compute after the branch. */
u32 PadGetType(s32 padIndex) {
    s32 temp;
    s32 result;

    if (padIndex < 0) {
        return 0;
    }
    temp = gPadBuffers[padIndex * 3];
    result = ((u32)(temp & 0xF000)) >> 12;
    if ((temp & 0xFF) == 0xFF) {
        temp = 0;
        result = temp;
    }
    return result;
}

extern u8 D_8008CA06[];

/* Retail keeps an empty 8-byte frame; `framePad` reproduces it. The `u16 mode`
 * keeps the nor result and the or-accumulator in separate registers, and the
 * 0x3C8 store sits in both arms so jump2 cross-jumps only the final sb. */
u16 PadReadObjectState(u8 *object) {
    s32 bank;
    u32 data;
    u16 pad;
    u16 mode;
    volatile s32 framePad[2];

    bank = *(s8 *)(object + 0x20B);
    if (bank < 0) {
        return 0;
    }
    data = *(u32 *)((u8 *)D_8008CA08 + bank * 8);
    if (gPadType[bank] == 2) {
        object[0x3C6] = data >> 8;
        object[0x3C7] = data >> 0x10;
        object[0x3C5] = data;
        object[0x3C8] = data >> 0x18;
    } else {
        object[0x3C6] = data >> 8;
        object[0x3C5] = data >> 0x10;
        object[0x3C7] = data;
        object[0x3C8] = data >> 0x18;
    }
    pad = *(u16 *)(D_8008CA06 + *(s8 *)(object + 0x20B) * 8);
    mode = ~(((pad & 0xFF) << 8) | (pad >> 8));
    if (mode & 0x1000) {
        mode |= 8;
    }
    if (mode & 0x4000) {
        mode |= 2;
    }
    if (mode & 0x2000) {
        mode |= 0x40;
    }
    if (mode & 0x8000) {
        mode |= 0x80;
    }
    return mode;
}

void InitPAD(void *, s32, void *, s32);
s32 StartPAD(void);
s32 VSync(s32);
void PadInitBuffers(void) {
    s32 *cursor;
    s32 wordCount;
    s32 emptyValue;
    cursor = gPadBuffers;
    emptyValue = -1;
    wordCount = 0xB;
    do {
        *cursor = emptyValue;
        wordCount -= 1;
        cursor += 1;
    } while (wordCount >= 0);
    InitPAD(gPadBuffers, 0xC, (u8 *)gPadBuffers + 0xC, 0xC);
    do {
    } while (StartPAD() == 0);
    ChangeClearPAD(0);
    VSync(0);
    VSync(0);
}

s32 func_80041D60(void) {
    u16 pads[2];
    u8 *cursor;
    u16 value1;
    u16 value2;

    cursor = (u8 *)gPadBuffers;
    asm("" : "=r"(cursor) : "0"(cursor));
    value1 = *(u16 *)(cursor + 2);
    pads[0] = ~(((value1 & 0xFF) << 8) | (value1 >> 8));
    cursor += 0xC;
    asm("" : "=r"(cursor) : "0"(cursor));
    value2 = *(u16 *)(cursor + 2);
    pads[1] = ~(((value2 & 0xFF) << 8) | (value2 >> 8));
    if ((*(u32 *)gPadBuffers & 0xF000) == 0) {
        pads[0] = 0;
    }
    if ((D_800B9E00[0] & 0xF000) == 0) {
        pads[1] = 0;
    }
    return ((u32)pads[1] << 16) | pads[0];
}

extern u8 gPadTypeSmall;
extern u8 D_800A3A26[];
extern u8 D_800A3A27[];
extern u32 D_8008CA2C[];
extern u32 D_8008CA30[];
extern u32 D_8008CA34[];
extern u32 D_8008CA38[];
extern u32 D_8008CA3C[];
extern u32 D_8008CA40[];
extern u32 D_8008CA44[];
extern u32 D_8008CA48[];

void PadRefreshTypes(void) {
    u32 padWord;
    u32 padType;
    Car *node;
    s32 i;
    u32 pad0;
    u32 pad1;
    u32 pad2;
    u32 pad3;
    s32 *p;
    s32 *cursor;
    u32 noPad;

    /* The do-while (0) wraps raise padType's ref count so it outranks node. */
    padWord = gPadBuffers[0];
    noPad = 0xFF;
    do {
        padType = padWord & 0xF000;
        if ((padWord & 0xFF) == noPad) {
            padType = 0;
        } else {
            padType = padType >> 12;
        }
    } while (0);
    gPadTypeSmall = padType;
    padWord = D_800B9E00[0];
    do {
        padType = padWord & 0xF000;
        if ((padWord & 0xFF) == noPad) {
            padType = 0;
        } else {
            padType = padType >> 12;
        }
    } while (0);
    node = gCarListnm[0];
    D_800A3A25[0] = padType;
    D_800A3A26[0] = 0;
    D_800A3A27[0] = 0;
    if (node != 0) {
        do {
            if (node->type == 0) {
                node->unk3C4 = ((u8 *)gPadType)[node->slot];
            }
            node = node->next;
        } while (node != 0);
    }
    i = 7;
    /* Keeps the cursor address in a register: the dead if splits the block so
       combine can't fold it into the load, and the wrap raises the ref count
       above 2 so local-alloc doesn't substitute the symbol either. */
    do {
        cursor = gPadBuffers;
    } while (0);
    if (node != 0) {
        pad3 = 0;
    }
    pad0 = cursor[0];
    pad1 = D_800B9DF8[0];
    pad2 = D_800B9E00[0];
    pad3 = D_800B9E04[0];
    p = D_8008CA04;
    D_8008CA3C[0] = 0xFFFF0000;
    D_8008CA14[0] = 0xFFFF0000;
    D_8008CA40[0] = 0;
    D_8008CA18[0] = 0;
    D_8008CA44[0] = 0xFFFF0000;
    D_8008CA1C[0] = 0xFFFF0000;
    D_8008CA48[0] = 0;
    D_8008CA20[0] = 0;
    D_8008CA2C[0] = pad0;
    p[0] = pad0;
    D_8008CA30[0] = pad1;
    D_8008CA08[0] = pad1;
    D_8008CA34[0] = pad2;
    D_8008CA0C[0] = pad2;
    D_8008CA38[0] = pad3;
    D_8008CA10[0] = pad3;
    for (i = 7; i >= 0; i--) {
        /* The wrap raises p's ref count so it takes t0 and i takes t1. */
        do {
            p[i] = 0;
        } while (0);
    }
}

void func_80041F54(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 *w;
    u16 hs;
    u16 swap;
    u16 out;
    u32 word;
    u32 w2;
    s32 j;
    s32 i;
    s32 type;
    s32 b1;
    s32 b2;
    s32 b3;
    u32 mask2;
    u32 mask3;

    w = arg0;
    for (j = 7; j >= 0; j--) {
        arg1[j] = 0;
    }
    arg1[1] = w[1];
    arg1[3] = w[4];
    mask2 = 0xFF0000;
    mask3 = 0xFF000000;
    for (i = 0; i < 2; i++) {
        word = *w;
        w2 = *(u32 *)((u16 *)w + 2);
        hs = ((u16 *)w)[1];
        swap = ~(((hs & 0xFF) << 8) | (hs >> 8));
        gPadType[i] = (word & 0xF000) >> 12;
        out = swap;
        if ((word & 0xFF) == 0xFF) {
            gPadType[i] = 0;
        }
        type = gPadType[i];
        if (type == 2) {
            b1 = (w2 & 0xFF00) >> 8;
            b2 = (w2 & mask2) >> 16;
            b3 = (w2 & mask3) >> 24;
            if (b3 > 0x80) {
                out = swap | 4;
            }
            if (b1 > 0x40) {
                out |= 0x40;
            }
            if (b2 > 0x40) {
                out |= 0x80;
            }
        } else if (type >= 5) {
            if (type == 5) {
                if (swap & 8) {
                    out = (swap & 0xFFF7) | 0x10;
                } else if (swap & 4) {
                    out = (swap & 0xFFFB) | 0x80;
                } else if (swap & 0x10) {
                    out = (swap & 0xFFEF) | 8;
                } else if (swap & 0x80) {
                    out = (swap & 0xFF7F) | 2;
                } else if (swap & 2) {
                    out = (swap & 0xFFFD) | 4;
                }
            }
        } else if (type != 4) {
            out = 0;
        }
        *arg1 = out;
        w += 3;
        arg1 += 2;
    }
}

void func_800420D8(u32 *input, u32 flags, u16 *output) {
    u8 *mode;
    u8 *current;
    u8 *settingPtr;
    u32 data;
    u32 fields;
    u32 raw;
    u32 a;
    u32 b;
    u32 c;
    u16 setting;
    u32 state;
    u32 outputState;
    s8 modeValue;

    current = (u8 *)input;
    settingPtr = current;
    mode = (u8 *)gPadType;
    settingPtr += 2;
    do {
        setting = *(u16 *)settingPtr;
        data = *(u32 *)current;
        fields = *(u32 *)(settingPtr + 2);
        state = ~(((setting & 0xFF) << 8) | (setting >> 8));
        outputState = state;
        *mode = (data & 0xF000) >> 12;
        if ((data & 0xFF) == 0xFF) {
            *mode = 0;
        }
        modeValue = *(s8 *)mode;
        raw = modeValue;
        if (raw == 2) {
            c = (fields & 0xFF00) >> 8;
            a = (fields >> 16) & 0xFF;
            b = fields & 0xFF;
            if ((s32)(fields >> 24) >= 0x81) {
                outputState |= 4;
            }
            if (outputState & 0x1000) {
                outputState |= 8;
            }
            if (outputState & 0x4000) {
                outputState |= 2;
            }
            if (outputState & 0x2000) {
                outputState |= 0x40;
            }
            if (outputState & 0x8000) {
                outputState |= 0x80;
            }
        } else if (raw == 4) {
            c = 0;
            a = 0;
            b = 0;
        } else {
            c = 0;
            a = 0;
            b = 0;
            outputState = 0;
        }
        output[0] = outputState;
        output[1] = ((((b & 0xFC) << 8) | ((a & 0xF0) << 2)) |
                     (((s32)(c & 0xF0)) >> 2)) |
                    (flags & 3);
        state = 0xC;
        settingPtr += state;
        current += 0xC;
        input = (u32 *)current;
        output = (u16 *)((u8 *)output + 4);
        mode += 1;
        flags >>= 2;
    } while ((s32)(u32)mode < (s32)(u32)D_800A3A26);
}

void func_80042218(u16 *src, s32 *acc, u32 *dst) {
    s32 i;
    s32 shift;
    u32 bits;
    u32 bitsLo;
    u32 bitsHi;

    *acc = 0;
    i = 0;
    shift = -4;
    do {
        dst[0] = src[0];
        bits = src[1];
        bitsLo = (bits & 0x3C) << 10;
        bitsHi = (bits & 0x3C0) << 14;
        dst[1] = ((bits & 0xFC00) >> 8) | bitsLo | bitsHi;
        if (i >= 2) {
            *acc |= (bits & 3) << shift;
        }
        src += 2;
        dst += 2;
        i += 1;
        shift += 2;
    } while (i < 4);
}

s32 PadTypeNeedsCalibration(s32 padType) {
    s32 var_v0;
    u32 temp_a0;

    temp_a0 = padType & 0xFF;
    if (temp_a0 == 2) {
        var_v0 = 1;
    } else {
        if (temp_a0 < 5U) {
            var_v0 = 0;
            return var_v0;
        }
        var_v0 = 1;
    }
    return var_v0;
}

typedef struct BoxCorner {
    s16 sx, sy, sz, pad;
    s32 vx, vy, vz;
} BoxCorner;
extern BoxCorner D_800B1FF0[8];

void CarInitTumble(Car *car) {
    s32 i;
    register s32 height asm("t1");
    s16 y;
    register BoxCorner *c asm("a1");
    register s32 *pvx asm("t0");
    register s32 *pvz asm("a3");
    register BoxCorner *cb asm("v0");
    s32 *vxb;
    s32 *vzb;

    *(s16 *)((u8 *)car + 0x398) =
        ABS(car->movementHeading - car->heading + 0x400) & 0x3FF;
    car->unk388 = 0;
    car->unk38A = 0;
    *(s16 *)((u8 *)car + 0x39A) = (u16)car->unkFE + 4;
    *(s16 *)((u8 *)car + 0x38C) = RandomScaledGet(0x20);
    if (*(s16 *)((u8 *)car + 0x38C) == 0) {
        *(s16 *)((u8 *)car + 0x38C) = 1;
    }
    *(s16 *)((u8 *)car + 0x38E) = ABS(RandomScaledGet(0x20));
    *(s16 *)((u8 *)car + 0x396) = 1;
    *(s16 *)((u8 *)car + 0x394) = ABS(RandomScaledGet(0x32)) + 0x4B;
    i = 0;
    cb = D_800B1FF0;
    vxb = &cb->vx;
    vzb = &cb->vz;
    height = *(s16 *)((u8 *)car->shape + 0x26);
    pvx = vxb;
    c = cb;
    pvz = vzb;
    for (; i < 8; pvx += 5, c++, pvz += 5, i++) {
        /* Keep the byte-offset induction register ahead of the switch index. */
        asm("" : : "r"(i * 20));
        switch (i) {
        case 0:
        case 4:
            c->sz = *(u16 *)((u8 *)car->shape + 0x1E);
            *pvz = c->sz;
            c->sx = *(u16 *)((u8 *)car->shape + 0x20);
            *pvx = c->sx;
            y = (i / 4) * height;
            c->sy = y;
            break;
        case 1:
        case 5:
            c->sz = *(u16 *)((u8 *)car->shape + 0x1E);
            *pvz = c->sz;
            c->sx = *(u16 *)((u8 *)car->shape + 0x22);
            *pvx = c->sx;
            y = (i / 4) * height;
            c->sy = y;
            break;
        case 2:
        case 6:
            c->sz = *(u16 *)((u8 *)car->shape + 0x1C);
            *pvz = c->sz;
            c->sx = *(u16 *)((u8 *)car->shape + 0x22);
            *pvx = c->sx;
            y = (i / 4) * height;
            c->sy = y;
            break;
        case 3:
        case 7:
            c->sz = *(u16 *)((u8 *)car->shape + 0x1C);
            *pvz = c->sz;
            c->sx = *(u16 *)((u8 *)car->shape + 0x20);
            *pvx = c->sx;
            y = (i / 4) * height;
            c->sy = y;
            break;
        default:
            continue;
        }
        D_800B1FF0[i].vy = y;
    }
}

extern s32 D_800A3A34Absolute[];
extern void EffectSpawnAtCarPoint(Car *, s32);
extern void func_80043B68(Car *, s32);

extern s32 D_800A3A2CAbsolute[];
void CarCheckGroundContact(Car *car) {
    s32 i;
    s32 best;
    s32 bestIdx;
    s32 t;
    s32 x;
    s32 z;
    s32 idxA;
    s32 idxB;
    s32 idxC;
    BoxCorner *c;
    s32 *sinTab;
    s32 *cosTab;

    best = 0x7FFF;
    bestIdx = 0;
    sinTab = *(s32 **)D_800A3A2CAbsolute;
    cosTab = *(s32 **)D_800A3A34Absolute;
    idxA = car->unk388;
    idxB = car->unk38A;
    c = D_800B1FF0;
    for (i = 0; i < 8; c++, i++) {
        z = c->vz;
        c->sx = c->vx;
        c->sy = c->vy;
        t = (sinTab[idxA] * c->sx - cosTab[idxA] * c->sy) >> 16;
        x = (cosTab[idxA] * c->sx + sinTab[idxA] * c->sy) >> 16;
        c->sz = (sinTab[idxB] * z - cosTab[idxB] * x) >> 16;
        c->sy = (cosTab[idxB] * z + sinTab[idxB] * x) >> 16;
        c->sx = t;
        idxC = *(s16 *)((u8 *)car + 0x398);
        z = ((sinTab[idxC] * c->sz - cosTab[idxC] * t) >> 16) + *(s32 *)car;
        c->sx = ((cosTab[idxC] * c->sz + sinTab[idxC] * t) >> 16) + car->pos.y;
        c->sz = z;
        if (c->sy < best) {
            best = c->sy;
            bestIdx = i;
        }
    }
    if (best <= 0 && -best >= *(s16 *)((u8 *)car + 0x39A)) {
        *(s16 *)((u8 *)car + 0x39A) = -best;
        car->unk1C0 = 0;
        *(u16 *)((u8 *)car + 0x396) |= 8;
        if (RandomScaledGet(3) < 0) {
            t = -RandomScaledGet(3);
        } else {
            t = RandomScaledGet(3);
        }
        if (ABS(*(s16 *)((u8 *)car + 0x394)) < 0x3C) {
            t += 2;
        }
        switch (bestIdx % 4) {
        case 3:
            if (t == 0) {
                EffectSpawnAtCarPoint(car, 0);
            }
            if (t < 3) {
                EffectSpawnAtCarPoint(car, 5);
            }
            func_80043B68(car, 0);
            break;
        case 2:
            if (t == 0) {
                EffectSpawnAtCarPoint(car, 1);
            }
            if (t < 3) {
                EffectSpawnAtCarPoint(car, 6);
            }
            func_80043B68(car, 1);
            break;
        case 1:
            if (t == 0) {
                EffectSpawnAtCarPoint(car, 2);
            }
            if (t < 3) {
                EffectSpawnAtCarPoint(car, 7);
            }
            func_80043B68(car, 2);
            break;
        case 0:
            if (t == 0) {
                EffectSpawnAtCarPoint(car, 3);
            }
            if (t < 3) {
                EffectSpawnAtCarPoint(car, 7);
            }
            func_80043B68(car, 3);
            break;
        }
    } else {
        car->unk1C0 = -1;
        *(u16 *)((u8 *)car + 0x396) &= ~8;
    }
    for (i = 0; i < 4; i++) {
        *(u16 *)((u8 *)car + 0x2AC + i * 0x28) = *(u16 *)((u8 *)car + 0x39A);
        *(u16 *)((u8 *)car + 0x2B0 + i * 0x28) = 0;
    }
}

extern s32 D_800A3A34Small[];

void CarUpdateTumble(Car *car) {
    s32 heading;
    s32 t;
    s32 i;
    s16 r;
    s32 d;

    CarCheckGroundContact(car);
    if (!(*(u16 *)((u8 *)car + 0x396) & 8)) {
        *(s16 *)((u8 *)car + 0x39A) += *(s16 *)((u8 *)car + 0x394);
        *(s16 *)((u8 *)car + 0x394) -= 8;
        *(s32 *)&car->speed -= 0x8000;
        if (*(s32 *)&car->speed < 0) {
            *(s32 *)&car->speed = 0;
        }
    } else {
        if (*(s32 *)&car->speed < 0x320000 ||
            ABS(*(s16 *)((u8 *)car + 0x394)) < 0x14) {
            if (*(u16 *)((u8 *)car + 0x396) & 1) {
                *(u16 *)((u8 *)car + 0x396) =
                    (*(u16 *)((u8 *)car + 0x396) & ~1) | 2;
            }
        }
        *(s16 *)((u8 *)car + 0x394) = -*(s16 *)((u8 *)car + 0x394) / 2 - 10;
        *(s16 *)((u8 *)car + 0x39A) += *(s16 *)((u8 *)car + 0x394);
        if (*(u16 *)((u8 *)car + 0x396) & 1) {
            r = *(s16 *)&car->unk388 % 512;
            heading = *(s16 *)((u8 *)car + 0x398);
            t = MathMultiplyFixed16((*(s32 **)D_800A3A34Absolute)[r],
                                    *(s32 *)&car->speed / 3);
            t = MathMultiplyFixed16((*(s32 **)D_800A3A34Absolute2)[heading], t);
            *(s16 *)((u8 *)car + 0x38C) = t >> 16;
            if (*(u16 *)&car->unk38A > 0x100 && *(u16 *)&car->unk38A < 0x300) {
                *(s16 *)((u8 *)car + 0x38C) = -*(s16 *)((u8 *)car + 0x38C);
            }
            r = *(s16 *)&car->unk38A % 512;
            t = MathMultiplyFixed16((*(s32 **)D_800A3A34Small)[r],
                                    *(s32 *)&car->speed / 3);
            t = MathMultiplyFixed16((*(s32 **)D_800A3A2CAbsolute)[heading], t);
            *(s16 *)((u8 *)car + 0x38E) = t >> 16;
            *(s32 *)&car->speed = *(s32 *)&car->speed * 9 / 10;
            if (*(s32 *)&car->speed < 0) {
                *(s32 *)&car->speed = 0;
            }
        }
    }
    if (*(u16 *)((u8 *)car + 0x396) & 3) {
        *(u16 *)&car->unk388 =
            (*(u16 *)&car->unk388 + *(u16 *)((u8 *)car + 0x38C) + 0x400) &
            0x3FF;
        *(u16 *)&car->unk38A =
            (*(u16 *)&car->unk38A + *(u16 *)((u8 *)car + 0x38E) + 0x400) &
            0x3FF;
        if (*(u16 *)((u8 *)car + 0x396) & 8) {
            SoundPlaySlotAtVolume(car, 6, 1);
        }
    }
    if (*(u16 *)((u8 *)car + 0x396) & 2) {
        r = *(u16 *)&car->unk388 & 0x1FF;
        d = r - 0x100;
        if (d > 0x40 || (d > -0x40 && d < 0)) {
            *(s16 *)((u8 *)car + 0x390) = *(u16 *)&car->unk388 - r + 0x200;
            *(s16 *)((u8 *)car + 0x38C) = 1;
        } else {
            *(s16 *)((u8 *)car + 0x390) = *(u16 *)&car->unk388 - r;
            *(s16 *)((u8 *)car + 0x38C) = -1;
        }
        r = *(u16 *)&car->unk38A & 0x1FF;
        if (r > 0x100) {
            *(s16 *)((u8 *)car + 0x392) = *(u16 *)&car->unk38A - r + 0x200;
            *(s16 *)((u8 *)car + 0x38E) = 1;
        } else {
            *(s16 *)((u8 *)car + 0x392) = *(u16 *)&car->unk38A - r;
            *(s16 *)((u8 *)car + 0x38E) = -1;
        }
        *(u16 *)((u8 *)car + 0x396) = (*(u16 *)((u8 *)car + 0x396) & ~2) | 4;
    }
    if (*(u16 *)((u8 *)car + 0x396) & 4) {
        *(s16 *)&car->unk388 += *(s16 *)((u8 *)car + 0x38C) / 2;
        if ((*(s16 *)((u8 *)car + 0x38C) > 0 &&
             *(s16 *)&car->unk388 >= *(s16 *)((u8 *)car + 0x390)) ||
            (*(s16 *)((u8 *)car + 0x38C) <= 0 &&
             *(s16 *)&car->unk388 <= *(s16 *)((u8 *)car + 0x390))) {
            *(s16 *)((u8 *)car + 0x38C) = 0;
            *(s16 *)&car->unk388 = *(s16 *)((u8 *)car + 0x390) & 0x3FF;
        } else if (*(s16 *)((u8 *)car + 0x38C) > 0) {
            *(s16 *)((u8 *)car + 0x38C) += 1;
        } else {
            *(s16 *)((u8 *)car + 0x38C) -= 1;
        }
        *(s16 *)&car->unk38A += *(s16 *)((u8 *)car + 0x38E) / 2;
        if ((*(s16 *)((u8 *)car + 0x38E) > 0 &&
             *(s16 *)&car->unk38A >= *(s16 *)((u8 *)car + 0x392)) ||
            (*(s16 *)((u8 *)car + 0x38E) <= 0 &&
             *(s16 *)&car->unk38A <= *(s16 *)((u8 *)car + 0x392))) {
            *(s16 *)((u8 *)car + 0x38E) = 0;
            *(s16 *)&car->unk38A = *(s16 *)((u8 *)car + 0x392) & 0x3FF;
        } else if (*(s16 *)((u8 *)car + 0x38E) > 0) {
            *(s16 *)((u8 *)car + 0x38E) += 1;
        } else {
            *(s16 *)((u8 *)car + 0x38E) -= 1;
        }
        d = *(s16 *)((u8 *)car + 0x390) & 0x3FF;
        heading = *(s16 *)((u8 *)car + 0x392) & 0x3FF;
        if (*(s16 *)&car->unk388 == d && *(s16 *)&car->unk38A == heading) {
            if (!D_800A2EDC[0] || d + heading == 0 || *(s16 *)&car->type == 1) {
                *(s16 *)&car->unk1BC = 3;
                for (i = 0; i < 4; i++) {
                    *(s16 *)((u8 *)car + 0x2B0 + i * 0x28) =
                        *(s16 *)((u8 *)car + 0x394) / 2;
                }
                return;
            }
            if (*(s16 *)&car->unk1BC != 4) {
                *(u8 *)&car->unk3B7 = 0x14;
            }
            *(s16 *)&car->unk1BC = 4;
        }
    }
    CarSetVelocityFromHeading((s32 *)car, *(s16 *)&car->movementHeading);
}
