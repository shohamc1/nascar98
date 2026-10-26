/* Psy-Q libetc for the port: one VSync is one host frame. */
#include "host.h"
#include <psxsdk/libetc.h>

static int sFrameCount;
static Callback sVSyncCallback;

void *ResetCallback(void)
{
    return 0;
}

long SetVideoMode(long mode)
{
    PORT_STUB(SetVideoMode);
    return 0;
}

/* A negative MODE only reads the frame count, as on the console. */
int VSync(int mode)
{
    if (mode < 0) {
        return sFrameCount;
    }
    if (HostFrame()) {
        HostExit(0);
    }
    sFrameCount++;
    if (sVSyncCallback) {
        sVSyncCallback();
    }
    return sFrameCount;
}

void VSyncCallback(Callback f)
{
    sVSyncCallback = f;
}
