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

extern u8 D_800A2D0D;
extern u8 D_800A2D0E;
extern u8 D_800A2D0F;
extern u8 D_800A39E4[];
extern u8 D_800A39E4Absolute[];
extern u8 D_800A39E4Absolute2[];
extern s32 D_800A2EB8[];
extern s32 D_800A2EC8[];
extern s32 D_800A2EB0Absolute[];
extern s32 D_800A2EACAbsolute[];
extern void func_80058D94(void);
extern void func_800531B8(void);
extern void func_800122D8(void);
extern void func_80066B08(void);
extern void func_800587A0(void);
extern void func_80059DC4(void);
extern void func_8005978C(void);
extern void func_800535A0(void);
extern s32 D_800A2CFC;
extern s32 D_800A2D00;
extern s32 D_800A2D04;
extern s32 D_800A2D08;
extern s32 D_800A3708;
extern s32 D_800A370C;
extern s32 D_800B9D54[];
extern s32 D_800B9D58[];
extern s32 D_800B9D5C[];
extern s32 D_800B9D60[];
extern void func_8001D220(s32, s32, s32, s32);
extern u32 D_800A38A0;
extern s8 D_800A2D10;
extern void *D_800A3A8C;
extern s32 strlen(char *);
extern u8 gOrderingTables[];
extern s32 gOrderingTableBank;
extern void func_8001E7EC(void *, s32, s32);
extern u8 D_800A39B0[];
extern s32 D_800A36B4;
extern s32 D_800A3948;
extern u16 D_800A38C0[];
extern void GsGetTimInfo(u8 *, u8 *);
extern u16 D_80090ED8[];
extern s32 D_80099590[];
extern u8 D_800A3320Absolute[];
extern u8 D_800A331CAbsolute[];
extern u16 D_80090ED8[];
extern s32 D_80099590[];
extern u8 D_800A3320Absolute[];
extern u8 D_800A331CAbsolute[];
extern s32 D_800A2EB0Absolute[];
extern void func_8003CAE8(s32);
extern u8 D_800A364Cw15[] asm("D_800A364C.NON_MATCHING");
extern s32 D_800A2EB0w15[] asm("D_800A2EB0.NON_MATCHING");
extern s32 D_800A2E90w15[] asm("D_800A2E90.NON_MATCHING");
extern s32 D_800A2EA8w15[] asm("D_800A2EA8.NON_MATCHING");
extern s16 D_800A3696w15[] asm("D_800A3696.NON_MATCHING");
extern s16 D_800A3694w15[] asm("D_800A3694.NON_MATCHING");
extern u8 D_800A2F9Dw15[] asm("D_800A2F9D.NON_MATCHING");
extern u8 D_800A2F9Cw15[] asm("D_800A2F9C.NON_MATCHING");
extern u8 D_800A2EDCw15[] asm("D_800A2EDC.NON_MATCHING");
extern u8 D_800A2EE0w15[] asm("D_800A2EE0.NON_MATCHING");
extern u8 D_800A2EE4w15[] asm("D_800A2EE4.NON_MATCHING");
extern u8 D_800A2EDBw15[] asm("D_800A2EDB.NON_MATCHING");
extern u8 D_800A3074w15[] asm("D_800A3074.NON_MATCHING");
extern u8 D_800A3073w15[] asm("D_800A3073.NON_MATCHING");
extern u8 D_800A36E1w15[] asm("D_800A36E1.NON_MATCHING");
extern u8 D_800B9DA4w15[] asm("D_800B9DA4.NON_MATCHING");
extern u8 D_800BE70Cw15[] asm("D_800BE70C.NON_MATCHING");
extern s32 D_8008CA28[];
extern s32 D_800A2EA4w15[] asm("D_800A2EA4.NON_MATCHING");
extern u8 D_800A2EDAw15[] asm("D_800A2EDA.NON_MATCHING");
extern s32 D_800A2EA4w18c[] asm("D_800A2EA4.NON_MATCHING");
extern s8 D_800A3A24w18c[] asm("D_800A3A24.NON_MATCHING");
extern s8 D_800A3A25w18c[] asm("D_800A3A25.NON_MATCHING");
extern s32 D_800A2EB0w18c[] asm("D_800A2EB0.NON_MATCHING");
extern u8 D_800A2EDAw18c[] asm("D_800A2EDA.NON_MATCHING");
extern s8 D_800A3620w18c[] asm("D_800A3620.NON_MATCHING");
extern s32 D_800A33CCw18c[] asm("D_800A33CC.NON_MATCHING");
extern u32 D_800A33C0w18c asm("D_800A33C0.NON_MATCHING");
extern u32 D_800A33C0addrw18c[];
extern u32 D_800A33C4w18c asm("D_800A33C4.NON_MATCHING");
extern u32 D_800A2D14w18c asm("D_800A2D14.NON_MATCHING");
extern u32 D_800A2D18w18c asm("D_800A2D18.NON_MATCHING");
extern u32 D_800A359Cw18c;
extern u8 D_800A2D0Cw18c;
extern u8 D_800A2D0Ew18c asm("D_800A2D0E.NON_MATCHING");
extern u8 D_800A2D0Fw18c asm("D_800A2D0F.NON_MATCHING");
extern s32 D_800A2EC8w18c[] asm("D_800A2EC8.NON_MATCHING");
extern s32 func_80041B7C(s32);
extern void func_80023074(void);
extern u32 gPrimitiveCursorNonMatching asm("gPrimitiveCursor.NON_MATCHING");
extern u32 gPrimitiveCursor_gp asm("gPrimitiveCursor.NON_MATCHING");
extern u32 D_800A3570;
extern s32 D_800A38F4;
extern s32 D_800A2F10[];
extern void *HeapAlloc(u32);
extern void SystemShowFatalError(char *);
extern void *D_800A3A40;
extern void *D_800A39A4;
extern s32 D_800BE970[];
extern void *D_800BE97C[];
extern s32 D_800BE984[];
extern char D_8008CB94[];
extern char D_8008CBB4[];
extern char D_8008CBD0[];
extern s32 D_800A2D44;
extern void ListPushFront(u8 *, u8 **, u8 **);
extern void func_8001C668(void *, void *);
extern s32 sprintf(char *, u8 *);
extern u8 D_8008CC6C[];
extern long RotTransPers_nom();
extern long RotTransPers3_nom();
extern void func_80033788();
extern void func_8003379C();
extern s32 D_800A2D60;
extern s32 D_800A2D5C;
extern s32 *D_800A2D64;
extern void *HeapAlloc(u32);
extern s32 D_800A2D5C;
extern s32 gOrderingTableBankAbsolute[];
extern s32 D_800A2CF8[];
extern s32 D_800A2D5C;
extern s32 MathMultiplyFixed16(s32, s32);

extern s32 *D_800A38AC;
extern s32 D_800A3798[], D_800A37AC[], D_800A3784[];
extern s32 D_800A379C[], D_800A37B4[], D_800A3790[];
extern s32 D_800A37A4[], D_800A37C4[], D_800A3794[];
extern s16 D_800A3AF8Half[] asm("D_800A3AF8");
extern MATRIX D_800A3AF8, D_800A3B18, D_800A3B38;
extern s16 D_800A3AFA[], D_800A3AFC[], D_800A3AFE[], D_800A3B00[], D_800A3B02[],
    D_800A3B04[], D_800A3B06[], D_800A3B08[];
extern u8 *D_800A3674[];
extern u8 D_800A2ED8[], D_800A2DE0[], D_800A2EDA[];
extern s32 D_800A2ED4[];
extern u8 *D_800A2EA0[];
extern s16 D_800A2D68;
extern void func_8001EEC4(u8 *);
extern void MatrixCombineState(void);
extern void func_80043F7C(u8 *, u8 *);
extern s32 func_80016ACC(u8 *, s16 *);
extern void func_80015EAC(u8 *);
extern void func_80025730(void);
extern void func_80032760();
extern void func_800328AC();
extern void func_80032544();

u8 CarDrawModel(u8 *car, s32 drawMode) {
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
    register s32 value asm("v0"); /* Keep the tilt sum in v0. */
    s32 speed;
    s32 i;
    u8 *part;

    spinAngle = 0;
    primitiveCount = *(s16 *)(*(u8 **)(car + 0x36C) + 0x2A);
    dx = *(s32 *)(car + 0) - D_800A38AC[0];
    dy = *(s32 *)(car + 4) - D_800A38AC[1];
    dz = *(s32 *)(car + 8) - D_800A38AC[2];
    model = *(s32 *)(*(u8 **)(car + 0x36C) + 0x38);
    basePrimitive = *(s32 *)(car + gOrderingTableBankAbsolute[0] * 4 + 0x420);
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
            if (*(s8 *)(car + 0x20C) == -2 || *(s8 *)(car + 0x20C) == 0) {
                PopMatrix();
                return 0;
            }
        } else if (D_800A2DE0[0] != 0) {
            PopMatrix();
            return 0;
        }
    }
    if (D_800A2ED4[0] == 0 && (*(s8 *)(car + 0x3B9) == 0 || car[0xF9] != 0 ||
                               *(s16 *)(car + 0x92) > 400)) {
        if (*(s32 *)(car + 0x90) != 0) {
            wheelAngle = (*(s32 *)(car + 0x90) >> 16) * 5;
            if (wheelAngle > 1536)
                wheelAngle = 1536;
            *(u16 *)(car + 0x1BA) += wheelAngle;
        } else if (!(*(s32 *)(car + 0x238) & 0x80)) {
            *(u16 *)(car + 0x1BA) -= car[0x410] * 5;
        }
        if (car[0xF9] != 0) {
            D_800A2D68 = (D_800A2D68 + 1024) % 4096;
            spinAngle = D_800A2D68;
        }
    }
    wheelAngle = (s16)(*(s16 *)(car + 0x1BA) % 4096);
    spinAngle = (spinAngle + *(s16 *)(car + 0x1BA)) % 4096;
    {
        s32 turnValue;
        s32 turnScale;
        s32 turnSum;

        if (D_800A2EB8[0] == 0) {
            turnValue = *(s16 *)(car + 0x20E);
            turnScale = turnValue * 8;
        } else {
            turnValue = *(s16 *)(car + 0x20E);
            turnScale = turnValue * 4;
        }
        turnSum = turnScale + turnValue;
        turnValue = turnSum + 4096;
        steeringAngle = turnValue % 4096;
        /* Keep the car-state load after this angle update. */
        asm volatile("" : : : "memory");
    }
    if (*(s8 *)(car + 0x374) < 2 ||
        (car == D_800A2EA0[0] && *(s16 *)(car + 0x1EC) == 0 &&
         D_800A2ED8[0] == 0 && *(s8 *)(car + 0x20C) == 0)) {
        for (i = 0; i < *(s16 *)(*(u8 **)(car + 0x36C) + 0x2C); i++) {
            part = *(u8 **)(*(u8 **)(car + 0x36C) + 0x40) + i * 24;
            if (*(s16 *)(part + 0x14) < 0) {
                func_80043F7C(car, part);
            } else if (*(s16 *)(part + 0x14) == 10) {
                if ((u8)func_80016ACC(car, (s16 *)part)) {
                    primitiveCount -= *(s16 *)(part + 0x12);
                }
            } else if (*(s16 *)(part + 0x14) < 9 &&
                       *(s8 *)(car + *(s16 *)(part + 0x14) + 0x3A5) == 0) {
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
                    if (*(s16 *)(car + 0xFE) >= 6 ||
                        *(void (**)(void))(car + 0x354) == func_80025730) {
                        func_80015EAC(car);
                    }
                    part = *(u8 **)(*(u8 **)(car + 0x36C) + 0x40) + i * 24;
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
        wheelAngle = ((*(u16 *)(car + 0x1BA) >> 9) & 15) - 8;
        if (wheelAngle > 0)
            wheelAngle = -wheelAngle;
        speed = (*(s32 *)(car + 0x228) * 3 >> 16) + 10;
        if (speed > 70)
            speed = 70;
        value = (wheelAngle + 4) * 2;
        speed += 4096;
        wheelAngle = (value + speed) % 4096;
        steeringValue = *(s16 *)(car + 0x20E) * 5;
    } else {
        wheelAngle = ((*(u16 *)(car + 0x1BA) >> 9) & 15) - 8;
        if (wheelAngle > 0)
            wheelAngle = -wheelAngle;
        wheelAngle = (wheelAngle + 4100) % 4096;
        steeringValue = *(s16 *)(car + 0x20E) * 3;
    }
    steeringAngle = steeringValue >> 2;
    if (steeringValue < 0)
        steeringAngle = (steeringValue + 3) >> 2;
    angles.vx = 0;
    angles.vy = wheelAngle;
    angles.vz = 0;
    RotMatrix(&angles, &D_800A3B18);
    if (*(s16 *)(car + 0x1D0) == 0)
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

INCLUDE_ASM("asm/nonmatchings/util", func_8001775C);

INCLUDE_ASM("asm/nonmatchings/util", func_800179AC);

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

extern s32 gRandomSeed, gRandomCount;
extern s32 gRandomCountMark;
void RandomSeedSet(s32 seed) {
    gRandomSeed = seed;
    gRandomCount = 0;
    gRandomCountMark = 0;
}

extern s32 gRandomSeed;
extern s32 gRandomCount;

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
