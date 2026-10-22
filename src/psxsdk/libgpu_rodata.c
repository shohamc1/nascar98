/* Retail libgpu .rodata after the jump table in FntPrint: debug and error
 * strings that the functions in libgpu.c reference. The run holds no code or
 * table, so it is a data-only translation unit. */
#include "common.h"

const char D_80090548[] = "tpage: (%d,%d,%d,%d)\n";
const char D_80090560[] = "clut: (%d,%d)\n";
const char D_80090570[] = "clip (%3d,%3d)-(%d,%d)\n";
const char D_80090588[] = "ofs  (%3d,%3d)\n";
const char D_80090598[] = "tw   (%d,%d)-(%d,%d)\n";
const char D_800905B0[] = "dtd   %d\n";
const char D_800905BC[] = "dfe   %d\n";
const char D_800905C8[] = "disp   (%3d,%3d)-(%d,%d)\n";
const char D_800905E4[] = "screen (%3d,%3d)-(%d,%d)\n";
const char D_80090600[] = "isinter %d\n";
const char D_8009060C[] = "isrgb24 %d\n";
static const char sSysId[] =
    "$Id: sys.c,v 1.120 1996/05/01 12:09:07 noda Exp $";
const char D_8009064C[] = "ResetGraph:jtb=%08x,env=%08x\n";
const char D_8009066C[] = "ResetGraph(%d)...\n";
const char D_80090680[] = "SetGraphReverse(%d)...\n";
const char D_80090698[] = "SetGraphDebug:level:%d,type:%d reverse:%d\n";
const char D_800906C4[] = "SetGrapQue(%d)...\n";
const char D_800906D8[] = "DrawSyncCallback(%08x)...\n";
const char D_800906F4[] = "SetDispMask(%d)...\n";
const char D_80090708[] = "DrawSync(%d)...\n";
const char D_8009071C[] = "%s:bad RECT";
const char D_80090728[] = "(%d,%d)-(%d,%d)\n";
const char D_8009073C[] = "%s:";
const char D_80090740[] = "ClearImage";
const char D_8009074C[] = "LoadImage";
const char D_80090758[] = "StoreImage";
const char D_80090764[] = "MoveImage";
const char D_80090770[] = "ClearOTag(%08x,%d)...\n";
const char D_80090788[] = "ClearOTagR(%08x,%d)...\n";
const char D_800907A0[] = "DrawOTag(%08x)...\n";
const char D_800907B4[] = "PutDrawEnv(%08x)...\n";
const char D_800907CC[] = "DrawOTagEnv(%08x,&08x)...\n";
const char D_800907E8[] = "PutDispEnv(%08x)...\n";
const char D_80090800[] = "GPU timeout:que=%d,stat=%08x,chcr=%08x,madr=%08x,";
const char D_80090834[] = "func=(%08x)(%08x,%08x)\n";
