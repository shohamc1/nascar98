#include "common.h"
#include "libpress.h"
#include "fixed_addrs.h"
#include <psxsdk/libgpu.h>
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/libcd.h>
#include <psxsdk/libgte.h>
#include <psxsdk/libapi.h>
#include <psxsdk/libspu.h>
#include <psxsdk/kernel.h>
#include "game.h"

extern void HeapFree(void *ptr);
extern u32 __heapbase[];
extern u8 *gHeapBase, *gHeapBreak;
extern s8 gHeapInit;
void func_8001D778(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5,
                   u8 arg6, s32 arg7);

void HeapInit(void) {
    if (gHeapBase == NULL) {
        gHeapBase = (u8 *)__heapbase[0];
    }
    gHeapInit = 1;
    gHeapBreak = gHeapBase;
}

void HeapResetInitFlag(void) {
    gHeapInit = 0;
}

/* Heap management. */

typedef struct HeapBlock {
    u32 size; /* payload size in bytes; bit 0 set while the block is free */
} HeapBlock;

extern u8 gHeapBigAllocFlag;

/*
 * First-fit allocator. Each block starts with a header word holding the
 * payload size; bit 0 is set while the block is free. A free block splits
 * when the remainder can hold a header and 0x20 bytes.
 */
void *HeapAlloc(u32 size) {
    u32 *block;
    u32 *result;
    u32 hdr;
    u8 found;

    if (gHeapInit == 0) {
        if (gHeapBase == NULL) {
            gHeapBase = (u8 *)__heapbase[0];
        }
        gHeapInit = 1;
        gHeapBreak = gHeapBase;
    }
    size += 3;
    size = size / 4 * 4;
    switch (size) {
    case 0x3D18:
    case 0x4168:
        gHeapBigAllocFlag = 1;
        break;
    }
    if (gHeapBase == gHeapBreak) {
        result = (u32 *)gHeapBase;
        *result++ = size;
        gHeapBreak = (u8 *)result + size;
    } else {
        block = (u32 *)gHeapBase;
        found = 0;
        while (found == 0 && block != (u32 *)gHeapBreak) {
            hdr = *block;
            if ((hdr & 1) != 0 && (hdr ^= 1) >= size) {
                found = 1;
            } else {
                block = (u32 *)((u8 *)block + (hdr + 4));
            }
        }
        if (found != 0) {
            if (hdr >= size + 0x24) {
                hdr -= size + 4;
                hdr |= 1;
                result = block + 1;
                *block = size;
                block = (u32 *)((u8 *)result + size);
                *block = hdr;
            } else {
                *block = hdr;
                result = block + 1;
            }
        } else {
            if ((u32)block + size + 4 > HEAP_LIMIT) {
                return NULL;
            }
            *block = size;
            result = block + 1;
            gHeapBreak = (u8 *)block + size + 4;
        }
    }
    return result;
}

u32 HeapFreeSpaceCount(void) {
    HeapBlock *block;
    u32 total;
    u32 size;

    total = 0;
    block = (HeapBlock *)gHeapBase;
    while (block != (HeapBlock *)gHeapBreak) {
        size = block->size;
        if (size & 1) {
            size ^= 1;
            total += size;
        }
        block = (HeapBlock *)((u8 *)block + (size + 4));
    }
    size = (HEAP_LIMIT - sizeof(HeapBlock)) - (u32)gHeapBreak;
    return total + size;
}

void HeapCoalesce(void) {
    u32 *cur;
    u32 *next;
    u8 *heapEnd;
    u32 size;
    u32 nextSize;
    u8 freeSeen;

    cur = (u32 *)gHeapBase;
    while (cur != (u32 *)gHeapBreak) {
        freeSeen = 0;
        heapEnd = gHeapBreak;
        if (cur == (u32 *)heapEnd) {
            return;
        }
        do {
            size = *cur;
            if (size & 1) {
                freeSeen = 1;
                size ^= 1;
            } else {
                cur = (u32 *)((u8 *)cur + size + 4);
            }
            if (cur == (u32 *)gHeapBreak) {
                return;
            }
        } while (freeSeen == 0);
        if (cur == (u32 *)gHeapBreak) {
            return;
        }
        next = (u32 *)((u8 *)cur + size + 4);
        if (next == (u32 *)gHeapBreak) {
            gHeapBreak = (u8 *)cur;
            return;
        }
        freeSeen = 1;
        while (freeSeen != 0 && next != (u32 *)gHeapBreak) {
            nextSize = *next;
            if (nextSize & 1) {
                nextSize ^= 1;
                size += 4 + nextSize;
                *cur = size | 1;
                next = (u32 *)((u8 *)cur + size + 4);
                if (next == (u32 *)gHeapBreak) {
                    gHeapBreak = (u8 *)cur;
                    break;
                }
            } else {
                freeSeen = 0;
            }
        }
        if (cur == (u32 *)gHeapBreak) {
            return;
        }
        cur = (u32 *)((u8 *)cur + size + 4);
    }
}

void HeapFree(void *ptr) {
    ((HeapBlock *)((u8 *)ptr - 4))->size |= 1;
    HeapCoalesce();
}

void func_80044A1C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5,
                   u8 arg6, u8 arg7) {
    u8 count;

    count = 0;
    do {
        func_8001D778(arg0 + 2, arg1, arg2 - 4, 1, arg4, arg5, arg6, (s8)arg7);
        func_8001D778(arg0 + 1, arg1 + 1, arg2 - 2, 1, arg4, arg5, arg6,
                      (s8)arg7);
        func_8001D778(arg0, arg1 + 2, arg2, arg3 - 4, arg4, arg5, arg6,
                      (s8)arg7);
        func_8001D778(arg0 + 1, arg1 + arg3 - 2, arg2 - 2, 1, arg4, arg5, arg6,
                      (s8)arg7);
        func_8001D778(arg0 + 2, arg1 + arg3 - 1, arg2 - 4, 1, arg4, arg5, arg6,
                      (s8)arg7);
        count++;
    } while ((s8)count < 2);
}
