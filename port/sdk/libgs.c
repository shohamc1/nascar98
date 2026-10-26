/* Port stubs for Psy-Q libgs: each logs its first call and returns 0. */
#include "host.h"
#include <psxsdk/libgpu.h>
#include <psxsdk/libgte.h>
#include <psxsdk/libgs.h>

void GsGetTimInfo(s32 arg0, s32 arg1)
{
    PORT_STUB(GsGetTimInfo);
}
