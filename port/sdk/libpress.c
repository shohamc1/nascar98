/* Port stubs for Psy-Q libpress: each logs its first call and returns 0. */
#include "host.h"

u8 D_8008CA04[0x4C];

void DecDCTin(s32 arg0, s32 arg1)
{
    PORT_STUB(DecDCTin);
}

s32 DecDCTinCallback(s32 arg0)
{
    PORT_STUB(DecDCTinCallback);
    return 0;
}

s32 DecDCTinSync(s32 arg0)
{
    PORT_STUB(DecDCTinSync);
    return 0;
}

void DecDCTout(s32 arg0, s32 arg1)
{
    PORT_STUB(DecDCTout);
}

s32 DecDCToutCallback(s32 arg0)
{
    PORT_STUB(DecDCToutCallback);
    return 0;
}

s32 DecDCToutSync(s32 arg0)
{
    PORT_STUB(DecDCToutSync);
    return 0;
}

void DecDCTReset(s32 arg0)
{
    PORT_STUB(DecDCTReset);
}
