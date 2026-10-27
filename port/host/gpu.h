/*
 * The host's PlayStation GPU: a 1024 x 512 16-bit VRAM shadow that
 * texture reads use, and an SDL3 render target of the same area scaled
 * by GpuInit's scale, which every primitive draws into. The display shows
 * the DISPENV rectangle of the target. Addresses are wasm addresses into
 * the module memory that GpuSetMemory names.
 */
#ifndef PORT_HOST_GPU_H
#define PORT_HOST_GPU_H

#include <stdint.h>

#define GPU_VRAM_WIDTH 1024
#define GPU_VRAM_HEIGHT 512

/* Opens a window, or an offscreen renderer when HEADLESS is nonzero. */
int GpuInit(int scale, int headless);
void GpuShutdown(void);
void GpuSetMemory(uint8_t *base, uint64_t size);

void GpuReset(void);
void GpuLoadImage(uint32_t rect, uint32_t src);
void GpuStoreImage(uint32_t rect, uint32_t dst);
void GpuMoveImage(uint32_t rect, int32_t x, int32_t y);
void GpuClearImage(uint32_t rect, int r, int g, int b);
/* Walks a reverse-linked ordering table from OT, drawing each packet. */
void GpuDrawOTag(uint32_t ot);
void GpuDrawPrim(uint32_t prim);
void GpuSetDispEnv(uint32_t env);

/* Shows the display area; returns nonzero when the window was closed. */
int GpuPresent(void);
/* Saves the display area as a BMP file. */
int GpuScreenshot(const char *path);
/* Packets drawn since the last GpuPresent. */
int GpuPacketsLastFrame(void);

/* For tests: the words one GPU command takes, from its first word, or 0
 * for a polyline, whose length depends on its terminator. */
int GpuCommandWords(uint32_t first);
/* For tests: texel (U, V) of a page as 0xAARRGGBB, with A 0 when
 * transparent, 0x80 when semi-transparent (STP set), else 0xFF. */
uint32_t GpuTexel(int pageX, int pageY, int depth, int clutX, int clutY, int u, int v);
uint16_t *GpuVram(void);
/* For tests: the render target's colour at VRAM (X, Y), as 0xAARRGGBB. */
uint32_t GpuTargetPixel(int x, int y);
/* For tests: live texture cache entries. */
int GpuCachedTextures(void);

#endif /* PORT_HOST_GPU_H */
