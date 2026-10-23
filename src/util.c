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
#include "graphics.h"
#include "util.h"

extern s32 *D_800A38AC;
extern s32 D_800A3798[], D_800A37AC[], D_800A3784[];
extern s32 D_800A379C[], D_800A37B4[], D_800A3790[];
extern s32 D_800A37A4[], D_800A37C4[], D_800A3794[];
extern s16 D_800A3AF8Half[] asm("D_800A3AF8");
extern MATRIX D_800A3AF8, D_800A3B18, D_800A3B38;
extern s16 D_800A3AFA[], D_800A3AFC[], D_800A3AFE[], D_800A3B00[], D_800A3B02[],
    D_800A3B04[], D_800A3B06[], D_800A3B08[];
extern u8 *D_800A3674[];
extern u8 D_800A2ED8[];
extern u8 D_800A2EDA[];
extern u8 *D_800A2EA0[];
extern s16 D_800A2D68;
extern void func_8001EEC4(Car *);
extern void func_80043F7C(Car *, u8 *);
extern s32 func_80016ACC(Car *, s16 *);
extern void func_80015EAC(Car *);
extern void func_80025730(void);
extern void func_80032760(u8 *entry, u8 *primitive, s32 remaining);
extern void func_800328AC(void *objects, s32 count);
extern void func_80032544(u8 *entry, s32 remaining);

u8 CarDrawModel(Car *car, s32 drawMode) {
    SVECTOR angles;
    VECTOR position;
    VECTOR partPosition;
    VECTOR unused; /* Preserve the original stack frame. */
    s32 flag;
    s32 model;
    s32 primitiveCount;
    s32 basePrimitive;
    s16 spinAngle;
    s32 dx, dy, dz;
    s32 wheelAngle;
    s32 steeringAngle;
    s32 steeringValue;
    s32 value;
    s32 speed;
    s32 i;
    u8 *part;

    spinAngle = 0;
    primitiveCount = *(s16 *)(car->unk36C + 0x2A);
    dx = car->pos.x - D_800A38AC[0];
    dy = car->pos.y - D_800A38AC[1];
    dz = car->pos.z - D_800A38AC[2];
    model = *(s32 *)(car->unk36C + 0x38);
    basePrimitive = car->unk420[gOrderingTableBankAbsolute[0]];
    if ((dx >= 0 ? dx < 30001 : -dx < 30001) == 0 ||
        (dy >= 0 ? dy < 30001 : -dy < 30001) == 0 ||
        (dz >= 0 ? dz < 30001 : -dz < 30001) == 0) {
        return 0;
    }
    angles.vx = dx;
    angles.vy = dy;
    angles.vz = dz;
    func_8001EEC4(car);
    MatrixCombineState();
    D_800A3AF8Half[0] = -D_800A3798[0] / 16;
    D_800A3AFE[0] = -D_800A37AC[0] / 16;
    D_800A3B04[0] = D_800A3784[0] / 16;
    D_800A3AFA[0] = -D_800A379C[0] / 16;
    D_800A3B00[0] = -D_800A37B4[0] / 16;
    D_800A3B06[0] = D_800A3790[0] / 16;
    D_800A3AFC[0] = -D_800A37A4[0] / 16;
    D_800A3B02[0] = -D_800A37C4[0] / 16;
    D_800A3B08[0] = D_800A3794[0] / 16;
    PushMatrix();
    RotTrans(&angles, &position, &flag);
    TransMatrix(&D_800A3AF8, &position);
    SetTransMatrix(&D_800A3AF8);
    SetRotMatrix(&D_800A3AF8);
    if (car == D_800A3674[0]) {
        if (D_800A2ED8[0] == 0) {
            if (car->cameraMode == -2 || car->cameraMode == 0) {
                PopMatrix();
                return 0;
            }
        } else if (D_800A2DE0[0] != 0) {
            PopMatrix();
            return 0;
        }
    }
    if (D_800A2ED4[0] == 0 && ((s8)car->unk3B9 == 0 || car->sliding != 0 ||
                               ((s16 *)&car->speed)[1] > 400)) {
        if (car->speed != 0) {
            wheelAngle = (car->speed >> 16) * 5;
            if (wheelAngle > 1536)
                wheelAngle = 1536;
            car->unk1BA += wheelAngle;
        } else if (!(car->flags & 0x80)) {
            car->unk1BA -= car->reverseSpeed * 5;
        }
        if (car->sliding != 0) {
            D_800A2D68 = (D_800A2D68 + 1024) % 4096;
            spinAngle = D_800A2D68;
        }
    }
    wheelAngle = (s16)(car->unk1BA % 4096);
    spinAngle = (spinAngle + car->unk1BA) % 4096;
    {
        s32 turnValue;
        s32 turnScale;
        s32 turnSum;

        if (D_800A2EB8[0] == 0) {
            turnValue = car->steering;
            turnScale = turnValue * 8;
        } else {
            turnValue = car->steering;
            turnScale = turnValue * 4;
        }
        turnSum = turnScale + turnValue;
        turnValue = turnSum + 4096;
        steeringAngle = turnValue % 4096;
        /* Keep the car-state load after this angle update. */
        asm volatile("" : : : "memory");
    }
    if ((s8)car->unk374 < 2 || (car == D_800A2EA0[0] && car->type == 0 &&
                                D_800A2ED8[0] == 0 && car->cameraMode == 0)) {
        for (i = 0; i < *(s16 *)(car->unk36C + 0x2C); i++) {
            part = *(u8 **)(car->unk36C + 0x40) + i * 24;
            if (*(s16 *)(part + 0x14) < 0) {
                func_80043F7C(car, part);
            } else if (*(s16 *)(part + 0x14) == 10) {
                if ((u8)func_80016ACC(car, (s16 *)part)) {
                    primitiveCount -= *(s16 *)(part + 0x12);
                }
            } else if (*(s16 *)(part + 0x14) < 9 &&
                       *(s8 *)((u8 *)car + *(s16 *)(part + 0x14) + 0x3A5) ==
                           0) {
                primitiveCount -= *(s16 *)(part + 0x12);
            } else {
                PushMatrix();
                angles.vx = *(s32 *)(part + 4);
                angles.vy = *(s32 *)(part + 8);
                angles.vz = *(s32 *)(part + 12);
                RotTrans(&angles, &partPosition, &flag);
                switch ((s16)((u16) * (s16 *)(part + 0x14) - 1)) {
                case 0:
                case 1:
                    angles.vx = 0;
                    angles.vy = wheelAngle;
                    angles.vz = 0;
                    RotMatrix(&angles, &D_800A3B18);
                    angles.vx = 0;
                    angles.vy = 0;
                    angles.vz = steeringAngle;
                    RotMatrix(&angles, &D_800A3B38);
                    MulMatrix2(&D_800A3B38, &D_800A3B18);
                    break;
                case 2:
                case 3:
                    angles.vx = 0;
                    angles.vz = 0;
                    angles.vy = spinAngle;
                    RotMatrix(&angles, &D_800A3B18);
                    break;
                case 8:
                    angles.vx = (4096 - steeringAngle) % 4096;
                    angles.vy = 0;
                    angles.vz = 0;
                    RotMatrix(&angles, &D_800A3B18);
                    break;
                case 4:
                    if (car->unkFE >= 6 ||
                        *(void (**)(void))((u8 *)car + 0x354) ==
                            func_80025730) {
                        func_80015EAC(car);
                    }
                    part = *(u8 **)(car->unk36C + 0x40) + i * 24;
                    angles.vx = *(s32 *)(part + 4);
                    angles.vy = *(s32 *)(part + 8);
                    angles.vz = *(s32 *)(part + 12);
                    RotTrans(&angles, &partPosition, &flag);
                    TransMatrix(&D_800A3B38, &partPosition);
                    SetTransMatrix(&D_800A3B38);
                    func_80032544(model + *(s16 *)(part + 0x10) * 44,
                                  *(s16 *)(part + 0x12));
                    goto partDone;
                case 5:
                case 6:
                case 7:
                    angles.vx = 0;
                    angles.vy = 0;
                    angles.vz = 0;
                    RotMatrix(&angles, &D_800A3B18);
                    break;
                }
                MulMatrix0(&D_800A3AF8, &D_800A3B18, &D_800A3B38);
                TransMatrix(&D_800A3B38, &partPosition);
                SetTransMatrix(&D_800A3B38);
                SetRotMatrix(&D_800A3B38);
                if (drawMode != 0) {
                    s32 primitiveRow;

                    primitiveRow =
                        gOrderingTableBankAbsolute[0] * 48 + (s32)car;
                    primitiveRow += i * 4;
                    func_80032760(model + *(s16 *)(part + 0x10) * 44,
                                  *(s32 *)(primitiveRow + 0x440),
                                  *(s16 *)(part + 0x12));
                } else {
                    func_800328AC(model + *(s16 *)(part + 0x10) * 44,
                                  *(s16 *)(part + 0x12));
                }
            partDone:
                primitiveCount -= *(s16 *)(part + 0x12);
                PopMatrix();
            }
        }
    }
    if (D_800A2EB8[0] == 0) {
        wheelAngle = (((u16)car->unk1BA >> 9) & 15) - 8;
        if (wheelAngle > 0)
            wheelAngle = -wheelAngle;
        speed = (car->unk228 * 3 >> 16) + 10;
        if (speed > 70) {
            speed = 70;
            value = (wheelAngle + 4) * 2;
        } else {
            value = (wheelAngle + 4) * 2;
        }
        speed += 4096;
        wheelAngle = (value + speed) % 4096;
        steeringValue = car->steering * 5;
    } else {
        wheelAngle = (((u16)car->unk1BA >> 9) & 15) - 8;
        if (wheelAngle > 0)
            wheelAngle = -wheelAngle;
        wheelAngle = (wheelAngle + 4100) % 4096;
        steeringValue = car->steering * 3;
    }
    steeringAngle = steeringValue >> 2;
    if (steeringValue < 0)
        steeringAngle = (steeringValue + 3) >> 2;
    angles.vx = 0;
    angles.vy = wheelAngle;
    angles.vz = 0;
    RotMatrix(&angles, &D_800A3B18);
    if (car->unk1D0 == 0)
        steeringAngle = 0;
    if (steeringAngle > 64)
        steeringAngle = 64;
    else if (steeringAngle < -64)
        steeringAngle = -64;
    if (D_800A2EDA[0] != 0)
        steeringAngle /= 4;
    steeringAngle = (steeringAngle + 4096) % 4096;
    angles.vx = steeringAngle;
    angles.vy = 0;
    angles.vz = 0;
    RotMatrix(&angles, &D_800A3B38);
    MulMatrix2(&D_800A3B38, &D_800A3B18);
    MulMatrix0(&D_800A3AF8, &D_800A3B18, &D_800A3B38);
    SetRotMatrix(&D_800A3B38);
    if (drawMode != 0) {
        func_80032760(model, basePrimitive, primitiveCount);
    } else {
        func_800328AC(model, primitiveCount);
    }
    PopMatrix();
    asm(".rdata\n.long 0\n.text");
    return 1;
}

void CarDrawPreviewModel(Car *arg0, s32 x, s32 y, s32 z) {
    SVECTOR rot;
    MATRIX m1, m2, m3;
    VECTOR trans[3];
    s32 flag;
    s32 depth;
    u8 *model;
    s32 i;
    u8 *entry;
    MATRIX *m3Ptr;

    depth = *(s16 *)(arg0->unk36C + 0x2A);
    model = *(u8 **)(arg0->unk36C + 0x38);
    rot.vx = 0x400;
    rot.vy = 0;
    rot.vz = (u16)arg0->steering;
    RotMatrix(&rot, &m1);
    m1.t[0] = x;
    m1.t[1] = y;
    m1.t[2] = z;
    SetTransMatrix(&m1);
    SetRotMatrix(&m1);
    for (i = 0; i < *(s16 *)(arg0->unk36C + 0x2C); i++) {
        m3Ptr = &m3;
        entry = *(u8 **)(arg0->unk36C + 0x40) + i * 0x18;
        if (*(s16 *)(entry + 0x14) >= 0) {
            if (*(s16 *)(entry + 0x14) != 10) {
                PushMatrix();
                rot.vx = *(s32 *)(entry + 4);
                rot.vy = *(s32 *)(entry + 8);
                rot.vz = *(s32 *)(entry + 0xC);
                RotTrans(&rot, &trans[1], &flag);
                if (*(s16 *)(entry + 0x14) < 5) {
                    rot.vx = 0;
                    rot.vy = 0;
                    rot.vz = 0;
                    RotMatrix(&rot, &m2);
                }
                switch ((s16)(*(u16 *)(entry + 0x14) - 1)) {
                case 0:
                case 1:
                    rot.vx = 0;
                    rot.vy = 0;
                    rot.vz = 0;
                    RotMatrix(&rot, m3Ptr);
                    MulMatrix2(m3Ptr, &m2);
                    goto common;
                case 5:
                case 6:
                case 7:
                case 8:
                    rot.vx = 0;
                    rot.vy = 0;
                    rot.vz = 0;
                    RotMatrix(&rot, &m2);
                case 2:
                case 3:
                default:
                common:
                    MulMatrix0(&m1, &m2, m3Ptr);
                    TransMatrix(m3Ptr, &trans[1]);
                    SetTransMatrix(m3Ptr);
                    SetRotMatrix(m3Ptr);
                    func_800328AC(model + *(s16 *)(entry + 0x10) * 44,
                                  *(s16 *)(entry + 0x12));
                    depth -= *(s16 *)(entry + 0x12);
                    PopMatrix();
                    break;
                case 4:
                    depth -= *(s16 *)(entry + 0x12);
                    PopMatrix();
                    break;
                }
            }
        }
    }
    func_800328AC(model, depth);
    asm(".rdata\n.long 0\n.text");
}

extern s32 D_800A2EC4Lui asm("D_800A2EC4Absolute");
extern s32 gSplitScreenModeLui asm("gSplitScreenModeAbsolute");
extern u32 gCarListLui asm("gCarListAbsolute");
extern s32 gOrderingTableBankLui asm("gOrderingTableBankAbsolute");
extern s32 D_800A2D6C;
extern s32 D_800A3818;
extern s32 func_800167BC(u8 *);
extern s32 GraphicsHasFreePrimitives(s32);

/* Draw every car in the list, or release the ones that were skipped. */
void CarDrawAll(void) {
    u32 car;
    s32 released;
    s32 bankFlag;
    s32 slot;
    s32 bank;
    u32 entries;
    s32 oldEntry;
    s32 value;
    s32 offset;
    s32 hw;
    u32 ptr;
    s32 size;
    s32 extra;
    s32 bank2;
    u32 entries2;
    s32 oldEntry2;
    s32 value2;
    s32 offset2;
    s32 hw2;
    u32 ptr2;
    s32 size2;
    s32 extra2;
    u8 *carState;

    D_800A2D6C = 1;
    bankFlag = 0;
    if (D_800A2EC4Lui == 0) {
        bankFlag = gSplitScreenModeLui == 0;
    }
    for (car = gCarListLui; car != 0; car = *(u32 *)(car + 0x3E0)) {
        released = 0;
        slot = *(s16 *)(car + 0x1E2);
        if (slot != -1 && *(s16 *)(car + 0x1E4) != -1 &&
            *(u16 *)((carState = (u8 *)gTrackSections[0] + slot * 0x90) +
                     0xE) == 1 &&
            *(s32 *)(car + 0x36C) != 0 && *(s8 *)(car + 0x374) < 4) {
            D_800A3818 = 0x808080;
            if (func_800167BC((u8 *)car) & 0xFF) {
                if (GraphicsHasFreePrimitives(
                        *(s16 *)(*(u8 **)(car + 0x36C) + 0x2A))) {
                    func_800168F8(*(u8 **)(car + 0x36C),
                                  (s8)((s8) * (u8 *)(car + 0x200) / 5));
                    CarDrawModel(car, 0);
                }
                continue;
            }
            released = 1;
            if (CarDrawModel(car, 1) & 0xFF) {
                *(u8 *)(car + 0x358) = 1;
            } else {
                *(u8 *)(car + 0x358) = 0;
            }
        }
        if (released == 0) {
            bank = gOrderingTableBankLui;
            entries = (bank << 2) + car;
            oldEntry = *(s32 *)(entries + 0x420);
            if (oldEntry != 0) {
                value = *(s8 *)(car + bank + 0x41C);
                offset = value * 0x44 + *(s32 *)(car + 0x370);
                hw = *(s16 *)(offset + 0x2A);
                ptr = (u32)D_800A2D64;
                size = D_800A2D5C;
                extra = *(s32 *)(entries + 0x430);
                *(s32 *)(ptr + 0x34) = oldEntry;
                D_800A2D64 = (s32 *)extra;
                *(s32 *)(entries + 0x420) = 0;
                D_800A2D5C = size + hw;
            }
            *(s8 *)(car + gOrderingTableBankLui + 0x41C) = -1;
        }
        if (bankFlag != 0) {
            bank2 = gOrderingTableBankLui + 1;
            entries2 = (bank2 << 2) + car;
            oldEntry2 = *(s32 *)(entries2 + 0x420);
            gOrderingTableBankLui = bank2;
            if (oldEntry2 != 0) {
                value2 = *(s8 *)(car + bank2 + 0x41C);
                offset2 = value2 * 0x44 + *(s32 *)(car + 0x370);
                hw2 = *(s16 *)(offset2 + 0x2A);
                ptr2 = (u32)D_800A2D64;
                size2 = D_800A2D5C;
                extra2 = *(s32 *)(entries2 + 0x430);
                *(s32 *)(ptr2 + 0x34) = oldEntry2;
                D_800A2D64 = (s32 *)extra2;
                *(s32 *)(entries2 + 0x420) = 0;
                D_800A2D5C = size2 + hw2;
            }
            *(s8 *)(car + gOrderingTableBankLui + 0x41C) = -1;
            gOrderingTableBankLui--;
        }
    }
    D_800A2D6C = 0;
}

/* Fatal error display. */

void SystemShowFatalError(char *message) {
    GraphicsInit();
    FntPrint(message);
    FntFlush(-1);
    for (;;) {
    }
}

/* Math and random numbers. */

u32 MathSqrt(u32 value) {
    u32 result;
    u32 bit;
    u32 rootBitSum;

    result = 0;
    bit = 0x40000000;
    while (bit != 0) {
        rootBitSum = result + bit;
        result >>= 1;
        if (value >= rootBitSum) {
            value -= rootBitSum;
            result += bit;
        }
        bit >>= 2;
    }
    if (result < value) {
        return result + 1;
    }
    return result;
}

extern s32 gRandomCount;
extern s32 gRandomCountMark;

void RandomCountMark(void) {
    gRandomCountMark = gRandomCount;
}

extern s32 gRandomSeed;

s32 RandomSeedGet(void) {
    return gRandomSeed;
}

void RandomSeedSet(s32 seed) {
    gRandomSeed = seed;
    gRandomCount = 0;
    gRandomCountMark = 0;
}

s32 RandomScaledGet(s32 scale) {
    s32 seed;

    gRandomCount++;
    if (gRandomCount >= 1000) {
        gRandomCount = 0;
    }
    seed = (gRandomSeed * 25173 + 13849) & 0xFFFF;
    gRandomSeed = seed;
    seed *= scale;
    return (u32)seed >> 16;
}
