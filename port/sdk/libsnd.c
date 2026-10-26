/* Port stubs for Psy-Q libsnd: each logs its first call and returns 0. */
#include "host.h"
#include <psxsdk/libsnd.h>

void func_80080728(void)
{
    PORT_STUB(func_80080728);
}

void func_80080758(void)
{
    PORT_STUB(func_80080758);
}

void func_80082B50(void)
{
    PORT_STUB(func_80082B50);
}

void func_80082B70(void)
{
    PORT_STUB(func_80082B70);
}

void SsEnd(void)
{
    PORT_STUB(SsEnd);
}

void SsSeqClose(short seq_access_num)
{
    PORT_STUB(SsSeqClose);
}

s32 SsSeqOpen(s32 arg0, s32 arg1)
{
    PORT_STUB(SsSeqOpen);
    return 0;
}

s32 SsSeqPause(s32 arg0)
{
    PORT_STUB(SsSeqPause);
    return 0;
}

void SsSeqPlay(s32 arg0, s32 arg1, s32 arg2)
{
    PORT_STUB(SsSeqPlay);
}

void SsSeqReplay(s32 arg0)
{
    PORT_STUB(SsSeqReplay);
}

void SsSeqSetVol(s32 arg0, s32 arg1, s32 arg2)
{
    PORT_STUB(SsSeqSetVol);
}

void SsSeqStop(short seq_access_num)
{
    PORT_STUB(SsSeqStop);
}

void SsSetLoop(s32 arg0, s32 arg1, s32 arg2)
{
    PORT_STUB(SsSetLoop);
}

void SsSetMono(void)
{
    PORT_STUB(SsSetMono);
}

void SsSetMute(s32 arg0)
{
    PORT_STUB(SsSetMute);
}

void SsSetMVol(short voll, short volr)
{
    PORT_STUB(SsSetMVol);
}

void SsSetSerialAttr(char s_num, char attr, char mode)
{
    PORT_STUB(SsSetSerialAttr);
}

void SsSetSerialVol(short s_num, short voll, short volr)
{
    PORT_STUB(SsSetSerialVol);
}

void SsSetStereo(void)
{
    PORT_STUB(SsSetStereo);
}

void SsSetTableSize(char* table, short s_max, short t_max)
{
    PORT_STUB(SsSetTableSize);
}

void SsSetTickMode(long tick_mode)
{
    PORT_STUB(SsSetTickMode);
}

void SsStart2(void)
{
    PORT_STUB(SsStart2);
}

s32 SsUtChangePitch(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    PORT_STUB(SsUtChangePitch);
    return 0;
}

s32 SsUtKeyOffV(s32 arg0)
{
    PORT_STUB(SsUtKeyOffV);
    return 0;
}

short SsUtKeyOnV(short voice, short vabId, short prog, short tone, short note, short fine, short voll, short volr)
{
    PORT_STUB(SsUtKeyOnV);
    return 0;
}

s32 SsUtPitchBend(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    PORT_STUB(SsUtPitchBend);
    return 0;
}

void SsUtSetReverbDepth(short ldepth, short rdepth)
{
    PORT_STUB(SsUtSetReverbDepth);
}

void SsUtSetReverbType(short type)
{
    PORT_STUB(SsUtSetReverbType);
}

short SsUtSetVVol(short vc, short voll, short volr)
{
    PORT_STUB(SsUtSetVVol);
    return 0;
}

void SsVabClose(s32 arg0)
{
    PORT_STUB(SsVabClose);
}

s32 SsVabOpenHead(s32 arg0, s32 arg1)
{
    PORT_STUB(SsVabOpenHead);
    return 0;
}

s32 SsVabTransBody(s32 arg0, s32 arg1)
{
    PORT_STUB(SsVabTransBody);
    return 0;
}

s32 SsVabTransCompleted(short immediateFlag)
{
    PORT_STUB(SsVabTransCompleted);
    return 0;
}
