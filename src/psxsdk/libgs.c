/* SPDX-License-Identifier: AGPL-3.0-only AND MIT AND GPL-2.0-or-later */
/* SDK C from sotn-decomp d818995ec49ef76e3b1625a96f4360108b3168be. */
#include "common.h"
#include "psxsdk_internal.h"
#include "libpress.h"
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/stdarg.h>

#include <psxsdk/libspu.h>
#include <psxsdk/libgpu.h>
#include <psxsdk/libcd.h>

void GsGetTimInfo(u8 *src, u8 *dst) {
    u32 flags;
    u8 *image;
    flags = *(u32 *)src;
    *(u32 *)dst = flags;
    if ((flags >> 3) & 1) {
        src += 4;
        image = src + ((*(u32 *)src >> 2) * 4);
        src += 4;
        *(u16 *)(dst + 0x10) = *(u16 *)src;
        *(u16 *)(dst + 0x12) = *(u16 *)(src + 2);
        src += 4;
        *(u16 *)(dst + 0x14) = *(u16 *)src;
        *(u16 *)(dst + 0x16) = *(u16 *)(src + 2);
        src += 4;
        *(u32 *)(dst + 0x18) = (u32)src;
        image += 4;
        *(u16 *)(dst + 4) = *(u16 *)image;
        *(u16 *)(dst + 6) = *(u16 *)(image + 2);
        image += 4;
        *(u16 *)(dst + 8) = *(u16 *)image;
        *(u16 *)(dst + 0xA) = *(u16 *)(image + 2);
        image += 4;
        *(u32 *)(dst + 0xC) = (u32)image;
        return;
    }
    src += 8;
    *(u16 *)(dst + 4) = *(u16 *)src;
    *(u16 *)(dst + 6) = *(u16 *)(src + 2);
    src += 4;
    *(u16 *)(dst + 8) = *(u16 *)src;
    *(u16 *)(dst + 0xA) = *(u16 *)(src + 2);
    src += 4;
    *(u32 *)(dst + 0xC) = (u32)src;
}
