/* Port stubs for Psy-Q libgte: each logs its first call and returns 0. */
#include "host.h"
#include <psxsdk/libgte.h>

void InitGeom(void)
{
    PORT_STUB(InitGeom);
}

s32 MulMatrix0(s32 arg0, s32 arg1, s32 arg2)
{
    PORT_STUB(MulMatrix0);
    return 0;
}

s32 MulMatrix2(s32 arg0, s32 arg1)
{
    PORT_STUB(MulMatrix2);
    return 0;
}

void MulRotMatrix(s32 arg0)
{
    PORT_STUB(MulRotMatrix);
}

void OuterProduct0(s32 arg0, s32 arg1, s32 arg2)
{
    PORT_STUB(OuterProduct0);
}

void PopMatrix(void)
{
    PORT_STUB(PopMatrix);
}

void PushMatrix(void)
{
    PORT_STUB(PushMatrix);
}

MATRIX* RotMatrix(SVECTOR* r, MATRIX* m)
{
    PORT_STUB(RotMatrix);
    return 0;
}

void RotTrans(SVECTOR* v0, VECTOR* v1, long* flag)
{
    PORT_STUB(RotTrans);
}

s32 RotTransPers3_nom(s32 arg0, s32 arg1, s32 arg2)
{
    PORT_STUB(RotTransPers3_nom);
    return 0;
}

s32 RotTransPers_nom(s32 arg0)
{
    PORT_STUB(RotTransPers_nom);
    return 0;
}

void SetBackColor(long rbk, long gbk, long bbk)
{
    PORT_STUB(SetBackColor);
}

void SetFarColor(long rfc, long gfc, long bfc)
{
    PORT_STUB(SetFarColor);
}

s32 SetFogFar(s32 arg0, s32 arg1)
{
    PORT_STUB(SetFogFar);
    return 0;
}

void SetFogNear(long a, long h)
{
    PORT_STUB(SetFogNear);
}

void SetGeomOffset(long ofx, long ofy)
{
    PORT_STUB(SetGeomOffset);
}

void SetGeomScreen(long h)
{
    PORT_STUB(SetGeomScreen);
}

void SetRotMatrix(MATRIX* m)
{
    PORT_STUB(SetRotMatrix);
}

void SetTransMatrix(MATRIX* m)
{
    PORT_STUB(SetTransMatrix);
}

MATRIX* TransMatrix(MATRIX* m, VECTOR* v)
{
    PORT_STUB(TransMatrix);
    return 0;
}

void VectorNormal(s32 arg0, s32 arg1, s32 arg2)
{
    PORT_STUB(VectorNormal);
}
