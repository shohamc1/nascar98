/*
 * Psy-Q libgte for the port: the functions the game calls, transcribed
 * from the matched source in src/psxsdk/libgte.c onto the software GTE
 * (port_gte.h).
 */
#include "host.h"
#include "port_gte.h"
#include <psxsdk/libgte.h>

#define MATRIX_STACK 20

/* Psy-Q's sine table: sin in the low half, cos in the high, 4096 per turn. */
extern u32 D_8009E070[];

/* The matrix stack in game memory, as retail keeps it: eight control words
 * an entry, and the depth in bytes. */
extern u32 D_8009DD70[];
extern s32 D_8009DD6C;

void InitGeom(void)
{
    PortGteWriteControl(29, 0x155);   /* ZSF3 */
    PortGteWriteControl(30, 0x100);   /* ZSF4 */
    PortGteWriteControl(26, 0x3E8);   /* H */
    PortGteWriteControl(27, -0x1062); /* DQA */
    PortGteWriteControl(28, 0x1400000); /* DQB */
    PortGteWriteControl(24, 0);       /* OFX */
    PortGteWriteControl(25, 0);       /* OFY */
}

void SetRotMatrix(MATRIX *m)
{
    const u32 *w = (const u32 *)m;
    int i;

    for (i = 0; i < 5; i++) {
        PortGteWriteControl(i, w[i]);
    }
}

void SetTransMatrix(MATRIX *m)
{
    PortGteWriteControl(5, (u32)m->t[0]);
    PortGteWriteControl(6, (u32)m->t[1]);
    PortGteWriteControl(7, (u32)m->t[2]);
}

void SetGeomOffset(long ofx, long ofy)
{
    PortGteWriteControl(24, (u32)ofx << 16);
    PortGteWriteControl(25, (u32)ofy << 16);
}

void SetGeomScreen(long h)
{
    PortGteWriteControl(26, (u32)h);
}

void SetBackColor(long rbk, long gbk, long bbk)
{
    PortGteWriteControl(13, (u32)rbk << 4);
    PortGteWriteControl(14, (u32)gbk << 4);
    PortGteWriteControl(15, (u32)bbk << 4);
}

void SetFarColor(long rfc, long gfc, long bfc)
{
    PortGteWriteControl(21, (u32)rfc << 4);
    PortGteWriteControl(22, (u32)gfc << 4);
    PortGteWriteControl(23, (u32)bfc << 4);
}

s32 SetFogFar(s32 a, s32 h)
{
    PortGteWriteControl(27, (u32)((-a << 6) / h));
    PortGteWriteControl(28, 0x01400000);
    return 0;
}

void SetFogNear(long a, long h)
{
    PortGteWriteControl(27, (u32)(-(a * 0x140) / h));
    PortGteWriteControl(28, 0x01400000);
}

/* M0's rows times each column of the rotation registers' operand; the
 * GTE's MVMVA (sf=1, rotation matrix, V0, no translation) per column. */
static MATRIX *Columns(MATRIX *in, MATRIX *out)
{
    s16 col[3][3];
    int j, i;

    for (j = 0; j < 3; j++) {
        PortGteWrite(0, (u16)in->m[0][j] | (u32)(u16)in->m[1][j] << 16);
        PortGteWrite(1, (u32)(s32)in->m[2][j]);
        PortGteCommand(0x4A486012u); /* MVMVA sf=1 RT V0 none */
        for (i = 0; i < 3; i++) {
            col[j][i] = (s16)PortGteRead(9 + i);
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            out->m[i][j] = col[j][i];
        }
    }
    /* Retail stores m[2][2] with swc2 $11: the pad after it takes IR3's sign. */
    ((s16 *)out)[9] = (s16)(PortGteRead(11) >> 16);
    return out;
}

/* M2 = M0 x M1 (the rotation registers keep M0). */
s32 MulMatrix0(MATRIX *m0, MATRIX *m1, MATRIX *m2)
{
    SetRotMatrix(m0);
    return (s32)Columns(m1, m2);
}

/* M1 = M0 x M1. */
s32 MulMatrix2(MATRIX *m0, MATRIX *m1)
{
    SetRotMatrix(m0);
    return (s32)Columns(m1, m1);
}

/* M0 = (the rotation registers) x M0. */
void MulRotMatrix(MATRIX *m0)
{
    Columns(m0, m0);
}

MATRIX *TransMatrix(MATRIX *m, VECTOR *v)
{
    m->t[0] = v->vx;
    m->t[1] = v->vy;
    m->t[2] = v->vz;
    return m;
}

/* Saves the rotation and translation registers, 20 deep. */
void PushMatrix(void)
{
    u32 *entry = D_8009DD70 + D_8009DD6C / 4;
    int i;

    if (D_8009DD6C >= MATRIX_STACK * 0x20) {
        HostLog("libgte: PushMatrix overflow");
        return;
    }
    for (i = 0; i < 8; i++) {
        entry[i] = PortGteReadControl(i);
    }
    D_8009DD6C += 0x20;
}

void PopMatrix(void)
{
    u32 *entry;
    int i;

    if (D_8009DD6C <= 0) {
        HostLog("libgte: PopMatrix underflow");
        return;
    }
    D_8009DD6C -= 0x20;
    entry = D_8009DD70 + D_8009DD6C / 4;
    for (i = 0; i < 8; i++) {
        PortGteWriteControl(i, entry[i]);
    }
}

/* sin and cos of ANGLE (4096 per turn) from Psy-Q's table. */
static void SinCos(int angle, s32 *s, s32 *c)
{
    u32 entry;

    if (angle >= 0) {
        entry = D_8009E070[angle & 0xFFF];
        *s = (s16)entry;
    } else {
        entry = D_8009E070[-angle & 0xFFF];
        *s = -(s16)entry;
    }
    *c = (s32)entry >> 16;
}

/* As Psy-Q's RotMatrix: M = Rx * Ry * Rz, in 4.12 fixed point. */
MATRIX *RotMatrix(SVECTOR *r, MATRIX *m)
{
    s32 sx, cx, sy, cy, sz, cz, t;

    SinCos(r->vx, &sx, &cx);
    SinCos(r->vy, &sy, &cy);
    SinCos(r->vz, &sz, &cz);
    m->m[0][2] = (s16)sy;
    m->m[1][2] = (s16)(-(cy * sx) >> 12);
    m->m[2][2] = (s16)((cy * cx) >> 12);
    m->m[0][0] = (s16)((cz * cy) >> 12);
    m->m[0][1] = (s16)(-(sz * cy) >> 12);
    t = (cz * -sy) >> 12;
    m->m[1][0] = (s16)(((sz * cx) >> 12) - ((t * sx) >> 12));
    m->m[2][0] = (s16)(((sz * sx) >> 12) + ((t * cx) >> 12));
    t = (sz * -sy) >> 12;
    m->m[1][1] = (s16)(((cz * cx) >> 12) + ((t * sx) >> 12));
    m->m[2][1] = (s16)(((cz * sx) >> 12) - ((t * cx) >> 12));
    return m;
}

static void LoadVertex(int slot, SVECTOR *v)
{
    const u32 *w = (const u32 *)v;

    PortGteWrite(slot * 2, w[0]);
    PortGteWrite(slot * 2 + 1, w[1]);
}

/* V1 = rotation x V0 + translation (MVMVA sf=1); FLAG goes to *FLAG. */
void RotTrans(SVECTOR *v0, VECTOR *v1, long *flag)
{
    LoadVertex(0, v0);
    PortGteCommand(0x4A480012u); /* MVMVA sf=1 RT V0 TR */
    v1->vx = (long)PortGteRead(25);
    v1->vy = (long)PortGteRead(26);
    v1->vz = (long)PortGteRead(27);
    *flag = (long)PortGteReadControl(31);
}

s32 RotTransPers_nom(SVECTOR *v0)
{
    LoadVertex(0, v0);
    PortGteCommand(PORT_GTE_RTPS);
    return 0;
}

s32 RotTransPers3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2)
{
    LoadVertex(0, v0);
    LoadVertex(1, v1);
    LoadVertex(2, v2);
    PortGteCommand(PORT_GTE_RTPT);
    return 0;
}

/* V2 = V0 x V1 through OP, keeping the rotation registers. */
void OuterProduct0(VECTOR *v0, VECTOR *v1, VECTOR *v2)
{
    u32 r0 = PortGteReadControl(0), r2 = PortGteReadControl(2), r4 = PortGteReadControl(4);

    PortGteWriteControl(0, (u32)v0->vx);
    PortGteWriteControl(2, (u32)v0->vy);
    PortGteWriteControl(4, (u32)v0->vz);
    PortGteWrite(11, (u32)v1->vz);
    PortGteWrite(9, (u32)v1->vx);
    PortGteWrite(10, (u32)v1->vy);
    PortGteCommand(0x4B70000Cu); /* OP sf=0 */
    v2->vx = (long)PortGteRead(25);
    v2->vy = (long)PortGteRead(26);
    v2->vz = (long)PortGteRead(27);
    PortGteWriteControl(0, r0);
    PortGteWriteControl(2, r2);
    PortGteWriteControl(4, r4);
}

/* Reciprocal square roots, 0x40 to 0xFF in 1.7, as 1.12 (game data). */
extern s16 D_8009DBD4[];

/*
 * Retail's normaliser (func_8007C548), step for step: SQR, LZCS on the
 * sum of squares, a reciprocal square root from the table, GPF, then a
 * shift. The GTE keeps the registers it leaves.
 */
static void Normalise(s32 v[3])
{
    s32 sum, zeros, shift, scaled;
    int i;

    for (i = 0; i < 3; i++) {
        PortGteWrite(9 + i, (u32)v[i]);
    }
    PortGteCommand(0x4AA00428u); /* SQR sf=0 */
    sum = (s32)(PortGteRead(25) + PortGteRead(26) + PortGteRead(27));
    PortGteWrite(30, (u32)sum);
    zeros = (s32)(PortGteRead(31) & ~1u);
    shift = (31 - zeros) >> 1;
    scaled = zeros >= 24 ? (s32)((u32)sum << (zeros - 24)) : sum >> (24 - zeros);
    PortGteWrite(8, (u32)(s32)D_8009DBD4[scaled - 0x40]);
    for (i = 0; i < 3; i++) {
        PortGteWrite(9 + i, (u32)v[i]);
    }
    PortGteCommand(0x4B90003Du); /* GPF sf=0 */
    for (i = 0; i < 3; i++) {
        v[i] = (s32)PortGteRead(25 + i) >> (shift & 31);
    }
}

/* V1 = V0 scaled to length 4096 (1.0 in 4.12). */
void VectorNormal(VECTOR *v0, VECTOR *v1, s32 unused)
{
    s32 v[3];

    v[0] = v0->vx;
    v[1] = v0->vy;
    v[2] = v0->vz;
    Normalise(v);
    v1->vx = v[0];
    v1->vy = v[1];
    v1->vz = v[2];
}
