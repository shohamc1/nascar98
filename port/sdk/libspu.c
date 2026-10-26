/* Port stubs for Psy-Q libspu: each logs its first call and returns 0. */
#include "host.h"
#include <psxsdk/libspu.h>

void SpuFree(s32 arg0)
{
    PORT_STUB(SpuFree);
}

void SpuGetAllKeysStatus(s32 arg0)
{
    PORT_STUB(SpuGetAllKeysStatus);
}

s32 SpuGetKeyStatus(s32 arg0)
{
    PORT_STUB(SpuGetKeyStatus);
    return 0;
}

s32 SpuInitMalloc(s32 arg0, s32 arg1)
{
    PORT_STUB(SpuInitMalloc);
    return 0;
}

s32 SpuMalloc(s32 arg0)
{
    PORT_STUB(SpuMalloc);
    return 0;
}

void SpuSetCommonAttr(s32 arg0)
{
    PORT_STUB(SpuSetCommonAttr);
}

void SpuSetIRQ(s32 arg0)
{
    PORT_STUB(SpuSetIRQ);
}

void SpuSetIRQAddr(s32 arg0)
{
    PORT_STUB(SpuSetIRQAddr);
}

SpuIRQCallbackProc SpuSetIRQCallback(SpuIRQCallbackProc func)
{
    PORT_STUB(SpuSetIRQCallback);
    return 0;
}

void SpuSetKey(long on_off, unsigned long voice_bit)
{
    PORT_STUB(SpuSetKey);
}

s32 SpuSetReverbVoice(s32 arg0, s32 arg1)
{
    PORT_STUB(SpuSetReverbVoice);
    return 0;
}

s32 SpuSetTransferCallback(s32 arg0)
{
    PORT_STUB(SpuSetTransferCallback);
    return 0;
}

long SpuSetTransferMode(long mode)
{
    PORT_STUB(SpuSetTransferMode);
    return 0;
}

void SpuSetTransferStartAddr(s32 arg0)
{
    PORT_STUB(SpuSetTransferStartAddr);
}

void SpuSetVoiceAttr(SpuVoiceAttr* arg)
{
    PORT_STUB(SpuSetVoiceAttr);
}

unsigned long SpuWrite(unsigned char* addr, unsigned long size)
{
    PORT_STUB(SpuWrite);
    return 0;
}
