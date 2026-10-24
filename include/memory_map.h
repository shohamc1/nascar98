#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

/*
 * The game's fixed RAM layout. The addresses themselves come from
 * config/symbol_addrs.txt (fixed_address) through the generated
 * fixed_addrs.h:
 *
 *   SOUND_BANK_BUFFER   0x80140000  sound bank body before its SPU upload
 *   HUD_SPRITE_BUFFER   0x80180000  passed with the HUD sprite table
 *   IMAGE_BANK_BUFFER   0x80193000  image banks
 *   CAR_MODEL_BUFFER    0x801A0000  car models and the menu car images
 *   GEOMETRY_BUFFER     0x801C0000  model geometry files
 *   PRIMITIVE_BUFFER_0  0x801D6C00  GPU packets, frame 0 (0xFA00 bytes)
 *   TIM_LOAD_BUFFER     0x801E0000  TIM staging while loading
 *   PRIMITIVE_BUFFER_1  0x801E6600  GPU packets, frame 1 (0xFA00 bytes)
 *   SCRATCH_TOP         0x801F2800
 *   HEAP_LIMIT          0x801F6000  HeapAlloc's ceiling
 *
 * Files whose size varies load flush against RAM_RESOURCE_BOUNDARY
 * (physical 0x1F4000) through LOAD_BELOW_TOP. A port build replaces
 * this header and fixed_addrs.h to give each region host memory of any
 * size.
 */
#include "fixed_addrs.h"

#define LOAD_BELOW_TOP(size) ((RAM_RESOURCE_BOUNDARY - (size)) | RAM_CACHED_BASE)

#endif
