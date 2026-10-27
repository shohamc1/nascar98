/*
 * The kernel's events for the port: VBlank (root counter 3) handlers run
 * each VBlank, and libcard delivers the card's results for TestEvent.
 */
#include "host.h"
#include <psxsdk/libapi.h>

#define EVENTS 16
#define EVENT_VBLANK 0xF2000003 /* RCntCNT3 */

static struct {
    u32 cls;
    s32 spec;
    void (*func)(void);
    int open, enabled, ready;
} sEvents[EVENTS];

static int EventIndex(long event)
{
    int i = (int)(event & 0xFFFF);

    return ((u32)event & 0xFFFF0000) == 0xF1000000 && i < EVENTS && sEvents[i].open ? i : -1;
}

long OpenEvent(unsigned long cls, long spec, long mode, long (*func)())
{
    int i;

    PORT_TRACE(OpenEvent);
    for (i = 0; i < EVENTS; i++) {
        if (!sEvents[i].open) {
            sEvents[i].cls = (u32)cls;
            sEvents[i].spec = (s32)spec;
            sEvents[i].ready = 0;
            sEvents[i].func = (void (*)(void))func; /* the game's handlers are void */
            sEvents[i].open = 1;
            sEvents[i].enabled = 0;
            return (long)(0xF1000000 | i);
        }
    }
    return -1;
}

long EnableEvent(long event)
{
    int i = EventIndex(event);

    PORT_TRACE(EnableEvent);
    if (i < 0) {
        return 0;
    }
    sEvents[i].enabled = 1;
    return 1;
}

s32 DisableEvent(s32 event)
{
    int i = EventIndex(event);

    PORT_TRACE(DisableEvent);
    if (i < 0) {
        return 0;
    }
    sEvents[i].enabled = 0;
    return 1;
}

s32 CloseEvent(s32 event)
{
    int i = EventIndex(event);

    PORT_TRACE(CloseEvent);
    if (i < 0) {
        return 0;
    }
    sEvents[i].open = 0;
    return 1;
}

void PortEventsVBlank(void)
{
    int i;

    for (i = 0; i < EVENTS; i++) {
        if (sEvents[i].open && sEvents[i].enabled && sEvents[i].cls == EVENT_VBLANK && sEvents[i].func) {
            sEvents[i].func();
        }
    }
}

/* Marks each enabled event of class CLS and SPEC ready, as the kernel's
 * DeliverEvent does. */
void PortEventDeliver(u32 cls, s32 spec)
{
    int i;

    for (i = 0; i < EVENTS; i++) {
        if (sEvents[i].open && sEvents[i].enabled && sEvents[i].cls == cls && sEvents[i].spec == spec) {
            sEvents[i].ready = 1;
        }
    }
}

/* 1 once for each delivery, then 0. */
long TestEvent(unsigned long event)
{
    int i = EventIndex((long)event);

    PORT_TRACE(TestEvent);
    if (i < 0 || !sEvents[i].ready) {
        return 0;
    }
    sEvents[i].ready = 0;
    return 1;
}
