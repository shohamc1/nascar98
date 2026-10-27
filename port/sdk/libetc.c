/* Psy-Q libetc for the port: one VSync is one host frame. */
#include "host.h"
#include <psxsdk/libetc.h>

void PortCdTick(void);
void PortPadTick(void);

static int sFrameCount;
static Callback sVSyncCallback;

void *ResetCallback(void)
{
    PORT_TRACE(ResetCallback);

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
    PORT_TRACE(VSync);

    if (mode < 0) {
        return sFrameCount;
    }
    if (HostFrame()) {
        HostExit(0);
    }
    sFrameCount++;
    PortPadTick();
    PortCdTick();
    if (sVSyncCallback) {
        sVSyncCallback();
    }
    return sFrameCount;
}

void VSyncCallback(Callback f)
{
    PORT_TRACE(VSyncCallback);
    sVSyncCallback = f;
}
