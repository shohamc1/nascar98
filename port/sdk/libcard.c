/* Port stubs for Psy-Q libcard: each logs its first call and returns 0. */
#include "host.h"
#include <psxsdk/libcard.h>

s32 _card_auto(s32 arg0)
{
    PORT_STUB(_card_auto);
    return 0;
}

long _card_clear(long chan)
{
    PORT_STUB(_card_clear);
    return 0;
}

s32 _card_info(s32 arg0)
{
    PORT_STUB(_card_info);
    return 0;
}

s32 _card_load(s32 arg0)
{
    PORT_STUB(_card_load);
    return 0;
}

void _card_read(s32 arg0, s32 arg1, s32 arg2)
{
    PORT_STUB(_card_read);
}

void _card_write(s32 arg0, s32 arg1, s32 arg2)
{
    PORT_STUB(_card_write);
}

void _new_card(void)
{
    PORT_STUB(_new_card);
}

void InitCARD(long val)
{
    PORT_STUB(InitCARD);
}

long StartCARD(void)
{
    PORT_STUB(StartCARD);
    return 0;
}

void StopCARD(void)
{
    PORT_STUB(StopCARD);
}

