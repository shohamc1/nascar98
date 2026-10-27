/*
 * Psy-Q libetc for the port: one VBlank is one host frame. VSync waits
 * for the next one; a polling loop with no VSync gets one every
 * POLLS_PER_VBLANK polls (PortPoll), as the console's interrupt would.
 */
#include "host.h"
#include <psxsdk/libetc.h>

void PortAudioTick(void);
void PortEventsVBlank(void);
void PortCdTick(void);
void PortPadTick(void);

#define POLLS_PER_VBLANK 64

static int sFrameCount;
static int sPolls;
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

void PortVBlank(void);

/* A negative MODE only reads the frame count, as on the console. */
int VSync(int mode)
{
    PORT_TRACE(VSync);

    if (mode < 0) {
        return sFrameCount;
    }
    PortVBlank();
    return sFrameCount;
}

/* The VBlank interrupt: a frame, the pads, the CD, the sound, the VBlank
 * events, and the VSync callback. */
void PortVBlank(void)
{
    sPolls = 0;
    if (HostFrame()) {
        HostExit(0);
    }
    sFrameCount++;
    PortPadTick();
    PortCdTick();
    PortAudioTick();
    PortEventsVBlank();
    if (sVSyncCallback) {
        /* wasm checks the type of an indirect call, and the game's one
         * VSync callback, AudioVSyncCallback, returns s32. */
        ((s32 (*)(void))sVSyncCallback)();
    }
}

void PortPoll(void)
{
    if (++sPolls >= POLLS_PER_VBLANK) {
        PortVBlank();
    }
}

void VSyncCallback(Callback f)
{
    PORT_TRACE(VSyncCallback);
    sVSyncCallback = f;
}
