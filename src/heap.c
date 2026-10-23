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
void GraphicsDrawRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5,
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
    u32 *currentBlock;
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
        currentBlock = (u32 *)gHeapBase;
        found = 0;
        while (found == 0 && currentBlock != (u32 *)gHeapBreak) {
            hdr = *currentBlock;
            if ((hdr & 1) != 0 && (hdr ^= 1) >= size) {
                found = 1;
            } else {
                currentBlock = (u32 *)((u8 *)currentBlock + (hdr + 4));
            }
        }
        if (found != 0) {
            if (hdr >= size + 0x24) {
                hdr -= size + 4;
                hdr |= 1;
                result = currentBlock + 1;
                *currentBlock = size;
                currentBlock = (u32 *)((u8 *)result + size);
                *currentBlock = hdr;
            } else {
                *currentBlock = hdr;
                result = currentBlock + 1;
            }
        } else {
            if ((u32)currentBlock + size + 4 > HEAP_LIMIT) {
                return NULL;
            }
            *currentBlock = size;
            result = currentBlock + 1;
            gHeapBreak = (u8 *)currentBlock + size + 4;
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
    u32 *currentBlock;
    u32 *nextBlock;
    u8 *heapEnd;
    u32 size;
    u32 nextSize;
    u8 freeSeen;

    currentBlock = (u32 *)gHeapBase;
    while (currentBlock != (u32 *)gHeapBreak) {
        freeSeen = 0;
        heapEnd = gHeapBreak;
        if (currentBlock == (u32 *)heapEnd) {
            return;
        }
        do {
            size = *currentBlock;
            if (size & 1) {
                freeSeen = 1;
                size ^= 1;
            } else {
                currentBlock = (u32 *)((u8 *)currentBlock + size + 4);
            }
            if (currentBlock == (u32 *)gHeapBreak) {
                return;
            }
        } while (freeSeen == 0);
        if (currentBlock == (u32 *)gHeapBreak) {
            return;
        }
        nextBlock = (u32 *)((u8 *)currentBlock + size + 4);
        if (nextBlock == (u32 *)gHeapBreak) {
            gHeapBreak = (u8 *)currentBlock;
            return;
        }
        freeSeen = 1;
        while (freeSeen != 0 && nextBlock != (u32 *)gHeapBreak) {
            nextSize = *nextBlock;
            if (nextSize & 1) {
                nextSize ^= 1;
                size += 4 + nextSize;
                *currentBlock = size | 1;
                nextBlock = (u32 *)((u8 *)currentBlock + size + 4);
                if (nextBlock == (u32 *)gHeapBreak) {
                    gHeapBreak = (u8 *)currentBlock;
                    break;
                }
            } else {
                freeSeen = 0;
            }
        }
        if (currentBlock == (u32 *)gHeapBreak) {
            return;
        }
        currentBlock = (u32 *)((u8 *)currentBlock + size + 4);
    }
}

void HeapFree(void *ptr) {
    ((HeapBlock *)((u8 *)ptr - 4))->size |= 1;
    HeapCoalesce();
}

void GraphicsDrawDoubleBorderRect(s16 x, s16 y, s16 width, s16 height, u8 red,
                                  u8 green, u8 blue, u8 semiTrans) {
    u8 count;

    count = 0;
    do {
        GraphicsDrawRect(x + 2, y, width - 4, 1, red, green, blue,
                         (s8)semiTrans);
        GraphicsDrawRect(x + 1, y + 1, width - 2, 1, red, green, blue,
                         (s8)semiTrans);
        GraphicsDrawRect(x, y + 2, width, height - 4, red, green, blue,
                         (s8)semiTrans);
        GraphicsDrawRect(x + 1, y + height - 2, width - 2, 1, red, green, blue,
                         (s8)semiTrans);
        GraphicsDrawRect(x + 2, y + height - 1, width - 4, 1, red, green, blue,
                         (s8)semiTrans);
        count++;
    } while ((s8)count < 2);
}
