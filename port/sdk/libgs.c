/* Psy-Q libgs for the port: the one function the game calls. */
#include "host.h"
#include <psxsdk/libgpu.h>
#include <psxsdk/libgte.h>
#include <psxsdk/libgs.h>

/*
 * Fills a GsIMAGE from a TIM, starting at its flags word (after the 0x10
 * ID). Bit 3 of the flags says a CLUT block comes first. Each block is
 * its length in bytes, a VRAM rectangle (x and y, then w and h, as
 * halfwords), and its data.
 */
void GsGetTimInfo(u32 *im, u32 *tim)
{
    u32 flags = im[0];
    u32 *block = im + 1;

    PORT_TRACE(GsGetTimInfo);
    tim[0] = flags;
    if (flags & 8) {
        tim[4] = block[1];
        tim[5] = block[2];
        tim[6] = (u32)(block + 3);
        block += block[0] / 4;
    } else {
        tim[4] = tim[5] = tim[6] = 0;
    }
    tim[1] = block[1];
    tim[2] = block[2];
    tim[3] = (u32)(block + 3);
}
