/* Replacement textures for the renderer (see textures.c). */
#ifndef PORT_HOST_TEXTURES_H
#define PORT_HOST_TEXTURES_H

#include <SDL3/SDL.h>
#include <stdint.h>

/* 64-bit FNV-1a of X, Y, W, H (little-endian u16s), then W * H pixels. */
uint64_t TextureHash(int x, int y, int w, int h, const uint8_t *pixels);
/* Reads NASCAR98_TEXTURES and NASCAR98_DUMP_TEXTURES. */
void TexturesInit(SDL_Renderer *renderer);
void TexturesShutdown(void);
/* An upload of W x H halfwords at (X, Y): dump it, and load its replacement. */
void TexturesUpload(int x, int y, int w, int h, const uint8_t *pixels);
/* Drops each replacement that the VRAM rectangle overwrites. */
void TexturesForget(int x, int y, int w, int h);
/* The replacement covering VRAM [X0, X1) x [Y0, Y1), and its VRAM rectangle. */
SDL_Texture *TexturesFind(float x0, float y0, float x1, float y1, SDL_FRect *area);

#endif /* PORT_HOST_TEXTURES_H */
