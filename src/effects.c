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

extern u8 *gCarListw15[] asm("gCarList.NON_MATCHING");
extern s32 D_800A38AC[];
extern s32 gRandomSeed16;
void func_80029994(u8 *arg0, s32 arg1);
void func_800328AC(void *arg0, s32 arg1);
void func_800364C4(void);
void func_80036540(void);

/* Scene effects and random numbers. */

__inline__ u32 RandomGetScaled16(s32 arg0) {
    s32 value0;
    value0 = ((gRandomSeed16 * 0x6255) + 0x3619) & 0xFFFF;
    gRandomSeed16 = value0;
    value0 *= arg0;
    return (u32)value0 >> 0x10;
}

extern u8 D_800AD9CC[];
void func_80043D6C(void);
void func_80042EC0(void) {
    s32 offset;
    offset = 0x750;
    do {
        D_800AD9CC[offset] = 0;
        offset -= 0x30;
    } while (offset >= 0);
    func_80043D6C();
}

typedef struct EffectPoint {
    s32 unk0;
    s32 x;
    s32 y;
    s32 z;
    s32 unk10;
    s32 unk14;
} EffectPoint;

typedef struct EffectSlot {
    s32 x;
    s32 y;
    s32 z;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s8 active;
    u8 unk1D;
    u8 unk1E;
    u8 pad1F;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
} EffectSlot;

extern EffectSlot gEffectSlots[] asm("D_800AD9B0");

void EffectSpawnParticles(u8 *object, s32 idx) {
    s32 i;
    s32 j;
    s32 twenty;
    s32 ninetysix;
    EffectPoint *table;
    EffectPoint *entry;

    for (i = 0, twenty = 20, ninetysix = 96; i < 5; i++) {
        for (j = 0; j < 0x28; j++) {
            if (gEffectSlots[j].active == 0) {
                break;
            }
        }
        if (j >= 0x28) {
            return;
        }
        table = *(EffectPoint **)(*(u8 **)(object + 0x370) + 0x40);
        gEffectSlots[j].active = 1;
        gEffectSlots[j].unk1D = 0xA;
        gEffectSlots[j].unk1E = *(u16 *)(object + 0x1DE);
        entry = &table[idx];
        gEffectSlots[j].x = *(s32 *)object + entry->x;
        gEffectSlots[j].y = *(s32 *)(object + 4) + entry->y;
        gEffectSlots[j].z = *(s32 *)(object + 8) + entry->z;
        gEffectSlots[j].unk1A = 0x1E;
        gEffectSlots[j].unk20 = gEffectSlots[j].unk24 =
            *(s16 *)(object + 0x1E0);
        if (idx < 5) {
            gEffectSlots[j].unkE = gEffectSlots[j].z;
        } else {
            gEffectSlots[j].unkE = *(s32 *)(object + 8) + 0xF;
        }
        gEffectSlots[j].unkC = 0;
        gEffectSlots[j].unk10 = RandomGetScaled16(twenty) + 0x1E;
        gEffectSlots[j].unk12 =
            (*(u16 *)(object + 0x114) + 0x400 + RandomGetScaled16(ninetysix)) &
            0x3FF;
        gEffectSlots[j].unk14 = (*(s32 *)(object + 0x90) * 7) / 8 >> 16;
        if (gEffectSlots[j].unk14 < 0x14) {
            gEffectSlots[j].unk14 = twenty;
        }
        gEffectSlots[j].unk28 = *(s32 *)(*(u8 **)(object + 0x370) + 0x38);
        gEffectSlots[j].unk2C =
            *(s32 *)(*(u8 **)(object + 0x370) + 0x40) + 0x90;
        /* ABS evaluates its argument twice: two LCG steps per field. */
        gEffectSlots[j].unk16 = ABS((s32)RandomGetScaled16(0x1000));
        gEffectSlots[j].unk18 = ABS((s32)RandomGetScaled16(0x1000));
    }
}

extern u8 D_800A2EE0[];

void EffectSpawnAtCarPoint(u8 *object, s32 idx) {
    s32 i;
    EffectPoint *entry;
    u8 *info;
    s32 slot;
    s32 unk28;
    s32 gate;
    s32 speed;
    s32 flag;

    if (*(s8 *)(object + 0x3B6) == 0) {
        return;
    }
    if (*(s8 *)(object + 0x200) == 4) {
        return;
    }
    if (idx >= 4) {
        if (*(s32 *)(object + 0x90) > 0) {
            EffectSpawnParticles(object, idx);
        }
        return;
    }
    for (i = 0; i < 0x28; i++) {
        if (gEffectSlots[i].active == 0) {
            break;
        }
    }
    if (i >= 0x28) {
        return;
    }
    info = *(u8 **)(object + 0x370);
    if (idx >= *(s16 *)(info + 0x2E)) {
        return;
    }
    entry = (EffectPoint *)(*(u8 **)(info + 0x40) + idx * 24);
    slot = *(s16 *)((u8 *)entry + 0x14);
    if (slot == 0) {
        return;
    }
    if (idx >= 8) {
        return;
    }
    if (*(s8 *)(object + slot + 0x3A5) == 0) {
        return;
    }
    *(u16 *)(object + 0x3A4) |= 1 << idx;
    *(u8 *)(object + idx + 0x3A6) = 0;
    gEffectSlots[i].active = 1;
    gEffectSlots[i].unk1D = idx;
    gEffectSlots[i].unk1E = *(u16 *)(object + 0x1DE);
    gEffectSlots[i].x = *(s32 *)object + entry->x;
    gEffectSlots[i].y = *(s32 *)(object + 4) + entry->y;
    gEffectSlots[i].z = *(s32 *)(object + 8) + entry->z;
    gEffectSlots[i].unk1A = 0xC8;
    gEffectSlots[i].unk20 = gEffectSlots[i].unk24 = *(s16 *)(object + 0x1E0);
    if (idx < 5) {
        gEffectSlots[i].unkE = gEffectSlots[i].z;
    } else {
        gEffectSlots[i].unkE = *(s32 *)(object + 8) + 0xF;
    }
    gEffectSlots[i].unkC = 0;
    gEffectSlots[i].unk10 = RandomGetScaled16(0x32) + 0x23;
    gEffectSlots[i].unk12 =
        (*(u16 *)(object + 0x114) + 0x400 + RandomGetScaled16(0x60)) & 0x3FF;
    if (idx < 5) {
        speed = *(s16 *)(object + 0x92);
        flag = D_800A2EE0[0];
        gEffectSlots[i].unk14 = speed;
        if (flag != 0 && *(u8 *)(object + 0x3B7) == 0) {
            *(u8 *)(object + 0x3B7) = 0x3C;
        }
        if (*(u8 *)(object + 0xF5) != 0) {
            func_80041848(object, 7);
        }
    } else {
        gEffectSlots[i].unk14 = (*(s32 *)(object + 0x90) * 7) / 8 >> 16;
    }
    if (gEffectSlots[i].unk14 < 0x14) {
        gEffectSlots[i].unk14 = 0x14;
    }
    unk28 = *(s32 *)(*(u8 **)(object + 0x370) + 0x38);
    gate = D_8008CA28[0];
    gEffectSlots[i].unk2C = (s32)entry;
    gEffectSlots[i].unk16 = 0;
    gEffectSlots[i].unk18 = 0;
    gEffectSlots[i].unk28 = unk28;
    if (gate == 0) {
        func_80029994(object, idx);
    }
    if (*(s32 *)(object + 0x90) > 0) {
        EffectSpawnParticles(object, idx);
    }
}

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void MulRotMatrix(MATRIX *matrix);

void func_800436D0(u8 *object) {
    SVECTOR input;
    VECTOR trans;
    MATRIX matrix;
    long lvm[18];
    s32 *camera;
    u8 *node;
    s16 angle1;
    s16 angle2;

    PushMatrix();
    camera = (s32 *)D_800A38AC[0];
    input.vx = *(s32 *)(object + 0) - camera[0];
    input.vy = *(s32 *)(object + 4) - camera[1];
    input.vz = *(s32 *)(object + 8) - camera[2];
    RotTrans(&input, &trans, &lvm[16]);
    TransMatrix(&matrix, &trans);
    if (*(s8 *)(object + 0x1D) == 0xA) {
        input.vx = 0;
        input.vy = *(u16 *)(object + 0x18);
        input.vz = *(u16 *)(object + 0x16);
        RotMatrix(&input, &matrix);
        MulRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        SetRotMatrix(&matrix);
        func_80044BCC(*(s8 *)(object + 0x1E));
    } else {
        input.vx = 0;
        input.vy = 0;
        input.vz = *(u16 *)(object + 0x16);
        RotMatrix(&input, &matrix);
        MulRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        SetRotMatrix(&matrix);
        node = *(u8 **)(object + 0x2C);
        angle1 = *(s16 *)(node + 0x10);
        angle2 = *(s16 *)(node + 0x12);
        func_800328AC((void *)(*(u32 *)(object + 0x28) + angle1 * 44), angle2);
    }
    PopMatrix();
}

extern s32 pairTable4382C[] asm("D_800A3A2C");
extern s32 pairTable4382CA[] asm("D_800A3A34");
extern u8 D_800AD9B0p[] asm("D_800AD9B0");
extern s8 D_800AD9CCp[] asm("D_800AD9CC");
extern s32 D_800A38ACw38[] asm("D_800A38AC");
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u16 unkC;
    u8 pad0E[2];
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    u8 unk1C;
    s8 unk1D;
    u8 pad1E[6];
    s32 unk24;
} EffectRow30;
void func_8004382C(void) {
    EffectRow30 *fx;
    s32 i;
    s8 *flagPtr;
    s32 x;
    s32 y;
    s32 idx4;
    s32 dx;
    s32 dy;
    s32 ground;
    s32 f10v;
    s32 value;
    s32 f10;
    s32 oldSection;
    s32 scratch[6];

    flagPtr = D_800AD9CCp;
    for (i = 0; i < 0x28; i++) {
        if (flagPtr[i * 0x30] == 0) {
            continue;
        }
        fx = (EffectRow30 *)(D_800AD9B0p + i * 0x30);
        if (D_800A2ED4[0] == 0) {
            if ((s16)fx->unk1A-- < 0) {
                flagPtr[i * 0x30] = 0;
                continue;
            }
            x = *(volatile s32 *)fx;
            dx = x - ((s32 *)D_800A38AC[0])[0];
            if (dx < 0) {
                dx = ((s32 *)D_800A38AC[0])[0] - x;
            }
            if (dx >= 0x3E81) {
                continue;
            }
            y = *(volatile s32 *)((u8 *)fx + 4);
            dy = y - ((s32 *)D_800A38ACw38[0])[1];
            if (dy < 0) {
                dy = ((s32 *)D_800A38ACw38[0])[1] - y;
            }
            if (dy >= 0x3E81) {
                continue;
            }
            idx4 = (s16)fx->unk12 * 4;
            scratch[0] = fx->unk0;
            scratch[1] = fx->unk4;
            scratch[0] =
                scratch[0] +
                ((*(s32 *)(idx4 + pairTable4382C[0]) * (s16)fx->unk14) >> 16);
            scratch[1] =
                scratch[1] +
                ((*(s32 *)(idx4 + pairTable4382CA[0]) * (s16)fx->unk14) >> 16);
            oldSection = fx->unk24;
            if (TrackFindSection(scratch[0], scratch[1], &fx->unk24,
                                 &scratch[2], &scratch[4]) == -1) {
                fx->unk24 = oldSection;
                scratch[0] = fx->unk0;
                scratch[1] = fx->unk4;
                fx->unk14 = (s16)fx->unk14 * 2 / 3;
                fx->unk12 = (fx->unk12 + 0x200) & 0x3FF;
            }
            f10v = fx->unk10;
            *(volatile s32 *)&fx->unk0 = scratch[0];
            *(volatile s32 *)&fx->unk4 = scratch[1];
            ground = scratch[2] * 4 + (s16)fx->unkC;
            value = *(volatile u16 *)&fx->unkC + f10v;
            fx->unkC = value;
            fx->unk8 = ground;
            if ((s16)value <= 0) {
                fx->unkC = 0;
                f10 = -((s16)fx->unk10 * 2 / 3) - 2;
                fx->unk10 = f10;
                if ((s16)f10 < 0) {
                    fx->unk10 = 0;
                } else {
                    fx->unk14 = (s16)fx->unk14 * 3 / 4;
                }
                if (fx->unk1D >= 5) {
                    fx->unk14 = (s16)fx->unk14 * 3 / 4;
                }
            } else {
                fx->unk10 = fx->unk10 - 8;
            }
            if (fx->unk1D < 5) {
                fx->unk16 = (s16)fx->unk12 * 4;
            } else {
                fx->unk16 = (fx->unk16 + fx->unk14 * 4) & 0xFFF;
            }
            fx->unk18 = (fx->unk18 + 0x80) & 0xFFF;
        }
        func_800436D0((u8 *)fx);
    }
}

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u8 pad[14];
} FxVertex;

void func_80043B68(u8 *object, s32 idx) {
    u8 *fx;
    u8 *row;
    FxVertex *prim;
    s32 i;
    s32 limit;
    s32 start;
    u16 flags;
    s32 base;
    s32 dcheck;
    u8 *table;
    u8 *verts;

    fx = *(u8 **)(object + 0x370);
    if (*(s8 *)(object + 0x3B6) == 0) {
        return;
    }
    if (*(s8 *)(object + 0x200) == 4) {
        return;
    }
    row = object + idx;
    if ((s8)++row[0x3AE] >= 4) {
        row[0x3AE] = 3;
    }
    flags = *(u16 *)(object + 0x3A4);
    dcheck = D_800A2EB8[0];
    *(u16 *)(object + 0x3A4) = flags | 0x8000;
    if (dcheck == 0 && *(s8 *)(row + 0x3AE) == 3) {
        if (idx == 3) {
            *(u16 *)(object + 0x3A4) = flags | 0x8080;
        } else {
            *(u16 *)(object + 0x3A4) = flags | 0x8000 | (1 << (idx + 5));
        }
    }
    base = *(s16 *)(fx + 0x2E);
    table = *(u8 **)(fx + 0x40);
    if (idx >= 0) {
        base += idx;
    } else {
        base -= idx;
    }
    row = table + base * 24;
    start = *(s16 *)row;
    verts = *(u8 **)(fx + 0x14);
    limit = *(s16 *)(row + 2) - start + 1;
    prim = (FxVertex *)(verts + start * 20);
    for (i = 0; i < limit; i++) {
        prim->x += (u8)RandomGetScaled16(5);
        prim->y += (u8)RandomGetScaled16(5);
        prim->z += (u8)RandomGetScaled16(5);
        prim++;
    }
}

extern u8 D_800B1A24[];
extern u8 D_800B1A25[];
extern u8 D_800B1A26R[] asm("D_800B1A26.NON_MATCHING");

void func_80043D6C(void) {
    s32 base;
    s32 m3base;
    s32 m3;
    s32 m1;
    s32 m2;
    register s32 d1 asm("s1");
    register s32 d2 asm("s0");
    register s32 d3 asm("t8");
    s32 d4;
    s32 value;
    register s32 temp asm("a0");
    s32 value2;
    s32 masked;
    s32 value3;
    s32 prod;
    s32 prodlo;
    s32 rowOff;
    s32 end;
    s32 midOff;
    s32 mo;
    register s32 colOff asm("a1");
    s32 off1;
    s32 off2;
    s32 off3;
    s32 i;
    s32 j;

    i = 0;
    base = 9;
    do {
        j = 0;
        rowOff = i * 0x40;
        m3base = i << 3;
        d1 = base;
        asm volatile("addu %0, %1, $zero" : "=r"(d2) : "r"(base));
        asm volatile("addu %0, %1, $zero" : "=r"(m1) : "r"(base));
        asm volatile("addu %0, %1, $zero" : "=r"(d3) : "r"(base));
        midOff = 0;
        do {
            mo = midOff;
            asm volatile("addu %0, %1, $zero" : "=r"(d4) : "r"(base));
            asm volatile("addu %0, %1, $zero" : "=r"(m2) : "r"(base));
            asm volatile("addiu %0, %1, 8" : "=r"(m3) : "r"(m3base));
            colOff = rowOff;
            do {
                temp = gRandomSeed16;
                off1 = colOff + mo;
                do {
                } while (0);
                value = (temp * 0x6255) + 0x3619;
                asm("andi %0, %1, 0xFFFF" : "=r"(masked) : "r"(value));
                gRandomSeed16 = masked;
                asm volatile("" ::: "memory");
                value &= 0xFFFF;
                value2 = ((value * 0x6255) + 0x3619) & 0xFFFF;
                gRandomSeed16 = value2;
                asm volatile("mult %0, %1"
                             :
                             : "r"(value2), "r"(m1)
                             : "lo", "hi");
                asm volatile("mflo %0" : "=r"(prodlo));
                D_800B1A24[off1] = -(s32)((u32)prodlo >> 16);
                temp = gRandomSeed16;
                asm volatile("addu %0, %1, %2"
                             : "=r"(off2)
                             : "r"(colOff), "r"(mo));
                value = (temp * 0x6255) + 0x3619;
                asm("andi %0, %1, 0xFFFF" : "=r"(masked) : "r"(value));
                gRandomSeed16 = masked;
                asm volatile("" ::: "memory");
                value &= 0xFFFF;
                value2 = ((value * 0x6255) + 0x3619) & 0xFFFF;
                gRandomSeed16 = value2;
                asm volatile("mult %0, %1"
                             :
                             : "r"(value2), "r"(m2)
                             : "lo", "hi");
                asm volatile("mflo %0" : "=r"(prodlo));
                D_800B1A25[off2] = -(s32)((u32)prodlo >> 16);
                temp = gRandomSeed16;
                value3 = ((temp * 0x6255) + 0x3619) & 0xFFFF;
                gRandomSeed16 = value3;
                asm volatile("mult %0, %1"
                             :
                             : "r"(value3), "r"(m3)
                             : "lo", "hi");
                asm volatile("addu %0, %1, %2"
                             : "=r"(off3)
                             : "r"(colOff), "r"(mo));
                colOff += 4;
                asm volatile("mflo %0" : "=r"(prodlo));
                D_800B1A26R[off3] = (s32)((u32)prodlo >> 16);
                asm volatile("addiu %0, %1, 0x40" : "=r"(end) : "r"(rowOff));
            } while (colOff < end);
            asm("" ::"r"(d4));
            j += 1;
            midOff += 0xC0;
        } while (j < 6);
        asm("" ::"r"(d1));
        asm("" ::"r"(d2));
        i += 1;
        base += 9;
    } while (i < 3);
}

extern u8 D_800B19E4[];

void func_80043F7C(u8 *arg0, s16 *arg1) {
    s16 first;
    s32 count;
    u8 *e;
    u8 *src;
    s8 delta;
    s32 off;
    s32 i;
    s16 w;
    u8 *b;
    s32 mv;

    first = arg1[0];
    e = *(u8 **)(*(u8 **)(arg0 + 0x36C) + 0x14) + first * 0x14;
    count = arg1[1] - first + 1;
    w = arg1[10];
    if (*(s8 *)((w >= 0) ? (b = arg0 + 0x3AD, b + w) : (arg0 + (0x3AD - w))) !=
        0) {
        w = arg1[10];
        b = arg0 + 0x3AD;
        delta = *(s8 *)((w >= 0) ? (b + w) : (b - w));
        w = arg1[10];
        off = delta * 0x40;
        if (w >= 0) {
            mv = (w - 1) * 0xC0;
            mv += (s32)D_800B19E4;
            src = (u8 *)(mv + off);
        } else {
            mv = (-w - 1) * 0xC0;
            mv += (s32)D_800B19E4;
            src = (u8 *)(mv + off);
        }
        for (i = 0; i < count; i++) {
            *(s16 *)(e + 0) = (s8)src[0] + *(s32 *)(e + 8);
            *(s16 *)(e + 2) = (s8)src[1] + *(s32 *)(e + 12);
            *(s16 *)(e + 4) = (s8)src[2] + *(s32 *)(e + 16);
            src += 4;
            e += 0x14;
        }
    } else {
        for (i = 0; i < count; i++) {
            *(s16 *)(e + 0) = *(s32 *)(e + 8);
            *(s16 *)(e + 2) = *(s32 *)(e + 12);
            *(s16 *)(e + 4) = *(s32 *)(e + 16);
            e += 0x14;
        }
    }
}

extern u8 *D_800A3960w17[] asm("D_800A3960.NON_MATCHING");

void func_80044114(u8 *arg0) {
    s32 i;
    u8 *entry;

    *(volatile s16 *)(arg0 + 0x3A4) = 0;
    for (i = 0; i < 8; i++) {
        *(volatile u8 *)(arg0 + i + 0x3A6) = 1;
        *(volatile u8 *)(arg0 + i + 0x3AE) = 0;
    }
    if (D_800A2EE0[0] != 0) {
        *(volatile s16 *)(arg0 + 0x1BC) = 3;
        for (i = 0, entry = arg0; i < 4; i++) {
            *(volatile s16 *)(entry + 0x2AC) = 0;
            *(volatile s16 *)(entry + 0x2B0) = 0;
            entry += 0x28;
        }
        *(volatile s16 *)(arg0 + 0x10C) = 0;
    }
    if (arg0 == D_800A3960[0]) {
        D_800A3960w17[0] = 0;
    }
}

void func_8004419C(u8 *object) {
    s32 i;
    *(volatile s16 *)(object + 0x1BC) = 3;
    for (i = 0; i < 4; i++) {
        *(volatile s16 *)(object + 0x2AC) = 0;
        *(volatile s16 *)(object + 0x2B0) = 0;
        object += 0x28;
    }
}

typedef struct {
    u32 w[12];
} CopyRow30;

extern CopyRow30 D_800AD9B0[];
extern CopyRow30 D_800BBAAC[];
void func_800441C8(void) {
    s32 row;
    func_800364C4();
    for (row = 0; row < 0x28; row++) {
        D_800BBAAC[row] = D_800AD9B0[row];
    }
}

void func_80044248(void) {
    s32 row;
    func_80036540();
    for (row = 0; row < 0x28; row++) {
        D_800AD9B0[row] = D_800BBAAC[row];
    }
}

void func_800442C8(u8 *arg0, u8 *arg1) {
    u32 bits;
    s32 i;

    bits = *(u32 *)(arg1 + 8);
    if (D_800A2EDC[0] != 0) {
        i = 0;
        do {
            if ((*(u16 *)(arg1 + 0xC) >> i & 1) != 0) {
                *(u8 *)(arg0 + 0x3A6 + i) = 0;
            } else {
                *(u8 *)(arg0 + 0x3A6 + i) = 1;
            }
            i++;
        } while (i < 8);
        arg0[0x3AE] = (bits & 0x3FFF) >> 12;
        arg0[0x3AF] = (bits & 0xFFF) >> 10;
        arg0[0x3B0] = (bits & 0x3FF) >> 8;
        arg0[0x3B1] = (bits & 0xFF) >> 6;
    }
}

extern u8 *gCarListPack asm("gCarListAbsolute");

/* One replay entry: position of an effect slot relative to its owner object
   in 64-unit steps (dz in 32-unit steps), then the owner index in word bits
   24-28 and the slot kind in bits 29-31. */
typedef struct {
    s8 dx;
    s8 dy;
    s8 dz;
    u8 tag;
} EffectPacked;

/* Packs the active effect slots into at most ten entries: first the slots whose
   kind isn't 10, then the kind-10 slots (stored as kind 4). A list that ends
   before ten entries gets a zero word. The mask and kind locals keep the
   constants in registers across both passes. */
void ReplayWriteEffects(EffectPacked *out) {
    s32 count;
    s32 i;
    EffectSlot *slot;
    u8 *object;
    u32 clearOwner;
    u32 clearKind;
    s32 kindSpawned;
    s32 field;
    u32 word;

    slot = gEffectSlots;
    count = 0;
    i = 0;
    *(u32 *)out = 0;
    kindSpawned = 10;
    clearOwner = 0xE0FFFFFF;
    clearKind = 0x1FFFFFFF;
pass1:
    if (slot->active != 0 && (s8)slot->unk1D != kindSpawned) {
        object = gCarListPack + (s8)slot->unk1E * 0x500;
        out->dx = (slot->x - *(s32 *)object) / 64;
        out->dy = (slot->y - *(s32 *)(object + 4)) / 64;
        out->dz = slot->unkC / 32;
        field = (s8)slot->unk1E;
        word = *(u32 *)out;
        word = (word & clearOwner) | ((field & 0x1F) << 24);
        *(u32 *)out = word;
        count++;
        field = (s8)slot->unk1D;
        word = (word & clearKind) | (field << 29);
        *(u32 *)out = word;
        out++;
    }
    i++;
    if (i >= 40) {
        slot = gEffectSlots;
        i = 0;
        if (count < 10) {
            for (;;) {
                if (slot->active != 0 && (s8)slot->unk1D == kindSpawned) {
                    object = gCarListPack + (s8)slot->unk1E * 0x500;
                    out->dx = (slot->x - *(s32 *)object) / 64;
                    out->dy = (slot->y - *(s32 *)(object + 4)) / 64;
                    out->dz = slot->unkC / 32;
                    field = (s8)slot->unk1E;
                    word = *(u32 *)out;
                    word = (word & clearOwner) | ((field & 0x1F) << 24);
                    word = (word & clearKind) | 0x80000000;
                    *(u32 *)out = word;
                    out++;
                    count++;
                }
                i++;
                slot++;
                if (i >= 40) {
                    *(u32 *)out = 0;
                    return;
                }
                if (count >= 10) {
                    return;
                }
            }
        }
        return;
    }
    slot++;
    if (count < 10) {
        goto pass1;
    }
}

void ReplayReadEffects(u8 *arg0) {
    u32 *wp;
    u8 *rec;
    u8 *typ;
    s32 i;
    s8 *bp;
    u8 *fp;
    u32 word;
    u32 src40;
    u32 mode;
    u8 w;
    u32 val38;
    s32 z;

    wp = (u32 *)arg0;
    rec = (u8 *)&D_800AD9B0[0];
    do {
        i = 0;
        bp = (s8 *)arg0 + 2;
        fp = rec + 0x1A;
    loop:
        if (*wp == 0) {
            for (; i < 0x28; i++, fp += 0x30) {
                fp[2] = 0;
            }
            return;
        }
        fp[2] = 1;
        word = *wp;
        typ = gCarListw15[0] + ((word >> 24) & 0x1F) * 0x500;
        if ((word & 0xE0000000) == 0x80000000) {
            src40 = *(u32 *)(*(u8 **)(typ + 0x370) + 0x40);
            fp[3] = 10;
        } else {
            do {
                mode = word >> 29;
                src40 = *(u32 *)(*(u8 **)(typ + 0x370) + 0x40) + mode * 0x18;
                fp[3] = mode;
            } while (0);
        }
    } while (0);
    *(s32 *)rec = (*(s8 *)wp << 6) + *(s32 *)typ;
    *(s32 *)(fp - 0x16) = (bp[-1] << 6) + *(s32 *)(typ + 4);
    w = ((u8 *)wp)[3];
    *(u32 *)(fp + 0x12) = src40;
    fp[4] = w & 0x1F;
    val38 = *(u32 *)(*(u8 **)(typ + 0x370) + 0x38);
    i++;
    rec += 0x30;
    *(u32 *)(fp + 0xA) = 0;
    *(u32 *)(fp + 0x6) = 0;
    *(s16 *)(fp - 0x8) = 0;
    *(s16 *)(fp - 0x6) = 0;
    *(u32 *)(fp + 0xE) = val38;
    z = *bp;
    wp++;
    bp += 4;
    *(s16 *)fp = 0xC8;
    *(s16 *)(fp - 0xA) = 0;
    *(s16 *)(fp - 4) = 0;
    *(s16 *)(fp - 2) = 0;
    *(s16 *)(fp - 0xE) = z << 5;
    fp += 0x30;
    if (i < 10) {
        goto loop;
    }
}
