/*
 * Replacement textures. NASCAR98_TEXTURES=DIR loads DIR/HASH.png for an
 * upload (LoadImage) whose TextureHash is HASH, as 16 hex digits. The PNG
 * may have any size: it covers the upload's VRAM rectangle, and the
 * renderer samples it wherever a primitive's texture lies inside that
 * rectangle. NASCAR98_DUMP_TEXTURES=DIR writes each upload once as
 * HASH.png, its halfwords read as 15-bit colour, to find the hash.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "textures.h"

#define MAX_REPLACEMENTS 256

typedef struct {
    SDL_FRect area;
    SDL_Texture *texture;
} Replacement;

static SDL_Renderer *sRenderer;
static const char *sLoadDir, *sDumpDir;
static Replacement sReplacements[MAX_REPLACEMENTS];
static int sCount;

uint64_t TextureHash(int x, int y, int w, int h, const uint8_t *pixels)
{
    const uint16_t head[4] = {(uint16_t)x, (uint16_t)y, (uint16_t)w, (uint16_t)h};
    uint64_t hash = 0xCBF29CE484222325ull;
    size_t i, n = (size_t)w * h * 2;

    for (i = 0; i < 8; i++) {
        hash = (hash ^ (head[i / 2] >> (i % 2 * 8) & 0xFF)) * 0x100000001B3ull;
    }
    for (i = 0; i < n; i++) {
        hash = (hash ^ pixels[i]) * 0x100000001B3ull;
    }
    return hash;
}

static const char *Dir(const char *name)
{
    const char *v = getenv(name);

    return v && *v ? v : NULL;
}

void TexturesInit(SDL_Renderer *renderer)
{
    sRenderer = renderer;
    sLoadDir = Dir("NASCAR98_TEXTURES");
    sDumpDir = Dir("NASCAR98_DUMP_TEXTURES");
}

void TexturesShutdown(void)
{
    TexturesForget(0, 0, 4096, 4096);
}

static void Dump(const char *path, int w, int h, const uint8_t *pixels)
{
    SDL_Surface *s;
    FILE *f = fopen(path, "rb");

    if (f) {
        fclose(f);
        return;
    }
    s = SDL_CreateSurfaceFrom(w, h, SDL_PIXELFORMAT_XBGR1555, (void *)pixels, w * 2);
    if (!s || !SDL_SavePNG(s, path)) {
        fprintf(stderr, "nascar98: can't dump %s: %s\n", path, SDL_GetError());
    }
    SDL_DestroySurface(s);
}

void TexturesUpload(int x, int y, int w, int h, const uint8_t *pixels)
{
    char path[1024];
    SDL_Surface *s;
    SDL_Texture *t;
    uint64_t hash;

    if (!sLoadDir && !sDumpDir) {
        return;
    }
    hash = TextureHash(x, y, w, h, pixels);
    if (sDumpDir) {
        snprintf(path, sizeof(path), "%s/%016llX.png", sDumpDir, (unsigned long long)hash);
        Dump(path, w, h, pixels);
    }
    if (!sLoadDir || sCount == MAX_REPLACEMENTS) {
        return;
    }
    snprintf(path, sizeof(path), "%s/%016llX.png", sLoadDir, (unsigned long long)hash);
    s = SDL_LoadPNG(path);
    if (!s) {
        return;
    }
    t = SDL_CreateTextureFromSurface(sRenderer, s);
    SDL_DestroySurface(s);
    if (!t) {
        return;
    }
    SDL_SetTextureScaleMode(t, SDL_SCALEMODE_LINEAR);
    sReplacements[sCount].area.x = (float)x;
    sReplacements[sCount].area.y = (float)y;
    sReplacements[sCount].area.w = (float)w;
    sReplacements[sCount].area.h = (float)h;
    sReplacements[sCount].texture = t;
    sCount++;
}

void TexturesForget(int x, int y, int w, int h)
{
    int i = 0;

    while (i < sCount) {
        const SDL_FRect *a = &sReplacements[i].area;

        if (x < a->x + a->w && a->x < x + w && y < a->y + a->h && a->y < y + h) {
            SDL_DestroyTexture(sReplacements[i].texture);
            sReplacements[i] = sReplacements[--sCount];
        } else {
            i++;
        }
    }
}

SDL_Texture *TexturesFind(float x0, float y0, float x1, float y1, SDL_FRect *area)
{
    int i;

    for (i = 0; i < sCount; i++) {
        const SDL_FRect *a = &sReplacements[i].area;

        if (a->x <= x0 && x1 <= a->x + a->w && a->y <= y0 && y1 <= a->y + a->h) {
            *area = *a;
            return sReplacements[i].texture;
        }
    }
    return NULL;
}
