/*
 * The host's PlayStation GPU (see gpu.h). Primitives draw with
 * SDL_RenderGeometry into a render target covering all of VRAM at
 * sScale times its size; textures decode from the 16-bit VRAM shadow.
 * Enhanced, not bit-exact: no dithering, mask bit, or texture window.
 * Texture modulation above 1.0 (vertex colour > 0x80) draws as a second,
 * additive pass of the excess.
 */
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gpu.h"
#include "textures.h"

#define CACHE_SIZE 256

typedef struct {
    int used;
    int pageX, pageY, depth, clutX, clutY;
    SDL_Texture *all;  /* every non-zero texel opaque */
    SDL_Texture *opaque; /* texels without STP */
    SDL_Texture *semi;   /* texels with STP */
} CachedTexture;

typedef struct {
    float x, y;
    SDL_FColor color;
    float u, v;
} Vertex;

static SDL_Window *sWindow;
static SDL_Renderer *sRenderer;
static SDL_Surface *sHeadlessSurface;
static SDL_Window *sHiddenWindow; /* headless: a GPU renderer, for its blend modes */
static SDL_Texture *sTarget;
static SDL_Texture *sScratch;
static SDL_Texture *sUpload; /* the VRAM shadow as XBGR1555, for uploads */
static SDL_Texture *sDisplay24;
static int sScale = 1;
static int sCustomBlend;
static SDL_BlendMode sSemiBlend[4];
static SDL_BlendMode sOpaqueBlend;

static uint16_t sVram[GPU_VRAM_WIDTH * GPU_VRAM_HEIGHT];
static uint8_t *sMem;
static uint64_t sMemSize;

static int sAreaX0, sAreaY0, sAreaX1 = GPU_VRAM_WIDTH - 1, sAreaY1 = GPU_VRAM_HEIGHT - 1;
static int sOffsetX, sOffsetY;
static int sPageX, sPageY, sDepth, sAbr;
static int sDispX, sDispY, sDispW = 320, sDispH = 240, sDisp24;
static int sPackets, sPacketsLast;
static CachedTexture sCache[CACHE_SIZE];
static int sTrace = -1; /* NASCAR98_TRACE_GPU: log uploads and display changes */

static int Tracing(void)
{
    if (sTrace < 0) {
        const char *v = getenv("NASCAR98_TRACE_GPU");

        sTrace = v && *v && *v != '0';
    }
    return sTrace;
}
static int sCacheNext;

/* ---- module memory ---- */

static int Valid(uint32_t address, uint32_t size)
{
    return sMem && (uint64_t)address + size <= sMemSize;
}

static uint32_t Read32(uint32_t address)
{
    uint32_t value = 0;

    if (Valid(address, 4)) {
        memcpy(&value, sMem + address, 4);
    }
    return value;
}

static void ReadRect(uint32_t address, int *x, int *y, int *w, int *h)
{
    int16_t r[4] = {0, 0, 0, 0};

    if (Valid(address, 8)) {
        memcpy(r, sMem + address, 8);
    }
    *x = r[0];
    *y = r[1];
    *w = r[2];
    *h = r[3];
}

void GpuSetMemory(uint8_t *base, uint64_t size)
{
    sMem = base;
    sMemSize = size;
}

uint16_t *GpuVram(void)
{
    return sVram;
}

/* ---- setup ---- */

static SDL_Texture *MakeTarget(int w, int h)
{
    SDL_Texture *t = SDL_CreateTexture(sRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

    if (t) {
        SDL_SetTextureScaleMode(t, SDL_SCALEMODE_NEAREST);
    }
    return t;
}

static void MakeBlendModes(void)
{
    SDL_BlendMode keepAlpha;
    int i;

    /* Colour: src * a OP dst; the target's alpha stays as it is. */
    sOpaqueBlend = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_SRC_ALPHA, SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
                                              SDL_BLENDOPERATION_ADD, SDL_BLENDFACTOR_ZERO,
                                              SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_ADD);
    keepAlpha = sOpaqueBlend;
    sSemiBlend[0] = keepAlpha; /* 0.5 B + 0.5 F through vertex alpha 0.5 */
    sSemiBlend[1] = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_SRC_ALPHA, SDL_BLENDFACTOR_ONE,
                                               SDL_BLENDOPERATION_ADD, SDL_BLENDFACTOR_ZERO,
                                               SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_ADD);
    sSemiBlend[2] = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_SRC_ALPHA, SDL_BLENDFACTOR_ONE,
                                               SDL_BLENDOPERATION_REV_SUBTRACT, SDL_BLENDFACTOR_ZERO,
                                               SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_ADD);
    sSemiBlend[3] = sSemiBlend[1]; /* B + 0.25 F through vertex alpha 0.25 */
    sCustomBlend = SDL_SetRenderDrawBlendMode(sRenderer, sOpaqueBlend);
    if (!sCustomBlend) {
        /* The software renderer has only the standard modes. */
        sOpaqueBlend = SDL_BLENDMODE_BLEND;
        for (i = 0; i < 4; i++) {
            sSemiBlend[i] = i == 1 || i == 3 ? SDL_BLENDMODE_ADD : SDL_BLENDMODE_BLEND;
        }
    }
}

int GpuInit(int scale, int headless)
{
    sScale = scale < 1 ? 1 : scale;
    if (headless) {
        /* SDL's software renderer can't subtract (blend mode 2): use it
         * only without a video device. */
        if (SDL_InitSubSystem(SDL_INIT_VIDEO)) {
            sHiddenWindow = SDL_CreateWindow("NASCAR 98", 320, 240, SDL_WINDOW_HIDDEN);
            sRenderer = sHiddenWindow ? SDL_CreateRenderer(sHiddenWindow, NULL) : NULL;
        }
        if (!sRenderer) {
            sHeadlessSurface = SDL_CreateSurface(4, 4, SDL_PIXELFORMAT_RGBA8888);
            sRenderer = sHeadlessSurface ? SDL_CreateSoftwareRenderer(sHeadlessSurface) : NULL;
        }
    } else {
        if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
            fprintf(stderr, "nascar98: SDL video: %s\n", SDL_GetError());
            return 1;
        }
        sWindow = SDL_CreateWindow("NASCAR 98", 320 * sScale, 240 * sScale, SDL_WINDOW_RESIZABLE);
        sRenderer = sWindow ? SDL_CreateRenderer(sWindow, NULL) : NULL;
        if (sRenderer) {
            SDL_SetRenderVSync(sRenderer, 0);
        }
    }
    if (!sRenderer) {
        fprintf(stderr, "nascar98: SDL renderer: %s\n", SDL_GetError());
        return 1;
    }
    sTarget = MakeTarget(GPU_VRAM_WIDTH * sScale, GPU_VRAM_HEIGHT * sScale);
    sUpload = SDL_CreateTexture(sRenderer, SDL_PIXELFORMAT_XBGR1555, SDL_TEXTUREACCESS_STREAMING, GPU_VRAM_WIDTH,
                                GPU_VRAM_HEIGHT);
    if (!sTarget || !sUpload) {
        fprintf(stderr, "nascar98: SDL textures: %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetTextureScaleMode(sUpload, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(sUpload, SDL_BLENDMODE_NONE);
    MakeBlendModes();
    TexturesInit(sRenderer);
    GpuReset();
    return 0;
}

static void DropTexture(CachedTexture *c)
{
    if (c->all) {
        SDL_DestroyTexture(c->all);
    }
    if (c->opaque) {
        SDL_DestroyTexture(c->opaque);
    }
    if (c->semi) {
        SDL_DestroyTexture(c->semi);
    }
    memset(c, 0, sizeof(*c));
}

void GpuShutdown(void)
{
    int i;

    for (i = 0; i < CACHE_SIZE; i++) {
        DropTexture(&sCache[i]);
    }
    TexturesShutdown();
    SDL_DestroyRenderer(sRenderer);
    if (sWindow) {
        SDL_DestroyWindow(sWindow);
    }
    if (sHiddenWindow) {
        SDL_DestroyWindow(sHiddenWindow);
    }
    if (sHeadlessSurface) {
        SDL_DestroySurface(sHeadlessSurface);
    }
    sRenderer = NULL;
    sWindow = NULL;
    sHiddenWindow = NULL;
    sHeadlessSurface = NULL;
}

void GpuReset(void)
{
    sAreaX0 = sAreaY0 = 0;
    sAreaX1 = GPU_VRAM_WIDTH - 1;
    sAreaY1 = GPU_VRAM_HEIGHT - 1;
    sOffsetX = sOffsetY = 0;
    sPageX = sPageY = sDepth = sAbr = 0;
    SDL_SetRenderTarget(sRenderer, sTarget);
    SDL_SetRenderClipRect(sRenderer, NULL);
    SDL_SetRenderDrawBlendMode(sRenderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(sRenderer, 0, 0, 0, 255);
    SDL_RenderClear(sRenderer);
}

/* ---- texture cache ---- */

static int Overlaps(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh)
{
    return ax < bx + bw && bx < ax + aw && ay < by + bh && by < ay + ah;
}

/* Drops each cached page, CLUT, or replacement that the VRAM rectangle touches. */
static void Invalidate(int x, int y, int w, int h)
{
    int i;

    TexturesForget(x, y, w, h);
    for (i = 0; i < CACHE_SIZE; i++) {
        CachedTexture *c = &sCache[i];
        int pageW = 64 << c->depth;

        if (!c->used) {
            continue;
        }
        if (Overlaps(x, y, w, h, c->pageX, c->pageY, pageW, 256) ||
            (c->depth < 2 && Overlaps(x, y, w, h, c->clutX, c->clutY, c->depth ? 256 : 16, 1))) {
            DropTexture(c);
        }
    }
}

int GpuCachedTextures(void)
{
    int i, n = 0;

    for (i = 0; i < CACHE_SIZE; i++) {
        n += sCache[i].used;
    }
    return n;
}

static uint16_t Vram(int x, int y)
{
    return sVram[(y & (GPU_VRAM_HEIGHT - 1)) * GPU_VRAM_WIDTH + (x & (GPU_VRAM_WIDTH - 1))];
}

uint32_t GpuTexel(int pageX, int pageY, int depth, int clutX, int clutY, int u, int v)
{
    uint16_t c;
    uint32_t r, g, b;

    if (depth == 0) {
        int index = (Vram(pageX + u / 4, pageY + v) >> ((u & 3) * 4)) & 0xF;

        c = Vram(clutX + index, clutY);
    } else if (depth == 1) {
        int index = (Vram(pageX + u / 2, pageY + v) >> ((u & 1) * 8)) & 0xFF;

        c = Vram(clutX + index, clutY);
    } else {
        c = Vram(pageX + u, pageY + v);
    }
    if (c == 0) {
        return 0;
    }
    r = (c & 31) << 3;
    g = ((c >> 5) & 31) << 3;
    b = ((c >> 10) & 31) << 3;
    return (c & 0x8000 ? 0x80000000u : 0xFF000000u) | r << 16 | g << 8 | b;
}

/* KIND 0: every texel; 1: only texels without STP; 2: only with STP. */
static SDL_Texture *DecodePage(const CachedTexture *c, int kind)
{
    static uint32_t pixels[256 * 256];
    SDL_Texture *t;
    int u, v;

    for (v = 0; v < 256; v++) {
        for (u = 0; u < 256; u++) {
            uint32_t texel = GpuTexel(c->pageX, c->pageY, c->depth, c->clutX, c->clutY, u, v);
            int stp = (texel >> 24) == 0x80;

            if (texel == 0 || (kind == 1 && stp) || (kind == 2 && !stp)) {
                texel = 0;
            } else {
                texel |= 0xFF000000u;
            }
            pixels[v * 256 + u] = texel;
        }
    }
    t = SDL_CreateTexture(sRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 256, 256);
    if (t) {
        SDL_UpdateTexture(t, NULL, pixels, 256 * 4);
        SDL_SetTextureScaleMode(t, SDL_SCALEMODE_NEAREST);
    }
    return t;
}

static SDL_Texture *Texture(int pageX, int pageY, int depth, int clutX, int clutY, int kind)
{
    CachedTexture *c = NULL;
    SDL_Texture **slot;
    int i;

    if (depth >= 2) {
        clutX = clutY = 0;
    }
    for (i = 0; i < CACHE_SIZE; i++) {
        CachedTexture *e = &sCache[i];

        if (e->used && e->pageX == pageX && e->pageY == pageY && e->depth == depth && e->clutX == clutX &&
            e->clutY == clutY) {
            c = e;
            break;
        }
    }
    if (!c) {
        for (i = 0; i < CACHE_SIZE && sCache[i].used; i++) {
        }
        if (i == CACHE_SIZE) {
            i = sCacheNext;
            sCacheNext = (sCacheNext + 1) % CACHE_SIZE;
            DropTexture(&sCache[i]);
        }
        c = &sCache[i];
        c->used = 1;
        c->pageX = pageX;
        c->pageY = pageY;
        c->depth = depth;
        c->clutX = clutX;
        c->clutY = clutY;
    }
    slot = kind == 0 ? &c->all : kind == 1 ? &c->opaque : &c->semi;
    if (!*slot) {
        *slot = DecodePage(c, kind);
    }
    return *slot;
}

/* ---- drawing ---- */

static void ApplyClip(void)
{
    SDL_Rect clip;

    clip.x = sAreaX0 * sScale;
    clip.y = sAreaY0 * sScale;
    clip.w = (sAreaX1 - sAreaX0 + 1) * sScale;
    clip.h = (sAreaY1 - sAreaY0 + 1) * sScale;
    if (clip.w <= 0 || clip.h <= 0) {
        clip.w = clip.h = 0;
    }
    SDL_SetRenderClipRect(sRenderer, &clip);
}

static int SignExtend11(uint32_t v)
{
    return (int)((v & 0x7FF) ^ 0x400) - 0x400;
}

static SDL_FColor Color(uint32_t word, int textured, int raw, float alpha)
{
    SDL_FColor c;

    if (textured && raw) {
        c.r = c.g = c.b = 1.0f;
    } else {
        float scale = textured ? 1.0f / 128.0f : 1.0f / 255.0f;

        /* Up to 2.0 when textured; Emit splits off the part above 1.0. */
        c.r = (word & 0xFF) * scale;
        c.g = ((word >> 8) & 0xFF) * scale;
        c.b = ((word >> 16) & 0xFF) * scale;
    }
    c.a = alpha;
    return c;
}

static void SetPage(uint32_t tpage)
{
    sPageX = (tpage & 0xF) * 64;
    sPageY = ((tpage >> 4) & 1) * 256;
    sAbr = (tpage >> 5) & 3;
    sDepth = (tpage >> 7) & 3;
    if (sDepth == 3) {
        sDepth = 2;
    }
}

/* Draws triangles over V (one strip of N vertices) with the given mode. */
static void Emit(const Vertex *v, int n, int textured, int semi, int clutX, int clutY)
{
    static const int quad[6] = {0, 1, 2, 1, 2, 3};
    SDL_Vertex out[6];
    SDL_Texture *replacement = NULL;
    SDL_FRect area;
    int i, k, pass, ratio = 4 >> sDepth, bright = 0;

    if (textured) {
        float u0 = v[0].u, u1 = v[0].u, v0 = v[0].v, v1 = v[0].v;

        for (i = 1; i < n; i++) {
            u0 = SDL_min(u0, v[i].u);
            u1 = SDL_max(u1, v[i].u);
            v0 = SDL_min(v0, v[i].v);
            v1 = SDL_max(v1, v[i].v);
        }
        replacement = TexturesFind(sPageX + u0 / ratio, sPageY + v0, sPageX + u1 / ratio, sPageY + v1, &area);
    }
    /* A replacement's alpha marks its clear texels: one pass draws it. */
    for (pass = 0; pass < (textured && semi && !replacement ? 2 : 1); pass++) {
        SDL_Texture *tex = replacement;
        SDL_BlendMode mode = sOpaqueBlend;
        float alpha = 1.0f;
        int blended = semi && (!textured || replacement || pass == 1);

        if (textured && !replacement) {
            /* Semi-transparent textured: STP-less texels first, opaque. */
            int kind = semi ? (pass == 0 ? 1 : 2) : 0;

            tex = Texture(sPageX, sPageY, sDepth, clutX, clutY, kind);
            if (!tex) {
                return;
            }
        }
        if (blended) {
            mode = sSemiBlend[sAbr];
            alpha = sAbr == 0 ? 0.5f : sAbr == 3 ? 0.25f : 1.0f;
        }
        for (k = 0; k < (n == 4 ? 6 : 3); k++) {
            const Vertex *s = &v[n == 4 ? quad[k] : k];

            out[k].position.x = (float)(s->x * sScale);
            out[k].position.y = (float)(s->y * sScale);
            out[k].color.r = SDL_min(s->color.r, 1.0f);
            out[k].color.g = SDL_min(s->color.g, 1.0f);
            out[k].color.b = SDL_min(s->color.b, 1.0f);
            out[k].color.a = s->color.a * alpha;
            bright |= s->color.r > 1.0f || s->color.g > 1.0f || s->color.b > 1.0f;
            if (replacement) {
                out[k].tex_coord.x = (sPageX + s->u / ratio - area.x) / area.w;
                out[k].tex_coord.y = (sPageY + s->v - area.y) / area.h;
            } else {
                out[k].tex_coord.x = s->u / 256.0f;
                out[k].tex_coord.y = s->v / 256.0f;
            }
        }
        if (tex) {
            SDL_SetTextureBlendMode(tex, mode);
        } else {
            SDL_SetRenderDrawBlendMode(sRenderer, mode);
        }
        SDL_RenderGeometry(sRenderer, tex, out, n == 4 ? 6 : 3, NULL, 0);
        if (!bright || !tex) {
            continue;
        }
        /* Add texel * (colour - 1.0), weighted and signed as the first pass. */
        for (k = 0; k < (n == 4 ? 6 : 3); k++) {
            const Vertex *s = &v[n == 4 ? quad[k] : k];

            out[k].color.r = SDL_max(s->color.r - 1.0f, 0.0f);
            out[k].color.g = SDL_max(s->color.g - 1.0f, 0.0f);
            out[k].color.b = SDL_max(s->color.b - 1.0f, 0.0f);
        }
        SDL_SetTextureBlendMode(tex, sSemiBlend[blended && sAbr == 2 ? 2 : 1]);
        SDL_RenderGeometry(sRenderer, tex, out, n == 4 ? 6 : 3, NULL, 0);
    }
}

/* The GPU skips a triangle more than 1023 wide or 511 tall; the game's
 * vertices projected from behind the camera rely on it. */
static int TooLarge(const Vertex *v)
{
    float x0 = SDL_min(v[0].x, SDL_min(v[1].x, v[2].x)), x1 = SDL_max(v[0].x, SDL_max(v[1].x, v[2].x));
    float y0 = SDL_min(v[0].y, SDL_min(v[1].y, v[2].y)), y1 = SDL_max(v[0].y, SDL_max(v[1].y, v[2].y));

    return x1 - x0 > 1023 || y1 - y0 > 511;
}

static void DrawPolygon(const uint32_t *w)
{
    uint32_t code = w[0] >> 24;
    int gouraud = code & 0x10, quad = code & 0x08, textured = code & 0x04;
    int semi = code & 0x02, raw = code & 0x01;
    int n = quad ? 4 : 3, i, at = 1, clutX = 0, clutY = 0;
    uint32_t color = w[0];
    Vertex v[4];

    for (i = 0; i < n; i++) {
        uint32_t xy;

        if (gouraud && i > 0) {
            color = w[at++];
        }
        xy = w[at++];
        v[i].x = (float)(SignExtend11(xy) + sOffsetX);
        v[i].y = (float)(SignExtend11(xy >> 16) + sOffsetY);
        v[i].color = Color(color, textured, raw, 1.0f);
        v[i].u = v[i].v = 0;
        if (textured) {
            uint32_t uv = w[at++];

            v[i].u = (float)(uv & 0xFF);
            v[i].v = (float)((uv >> 8) & 0xFF);
            if (i == 0) {
                clutX = ((uv >> 16) & 0x3F) * 16;
                clutY = (uv >> 22) & 0x1FF;
            } else if (i == 1) {
                SetPage(uv >> 16);
            }
        }
    }
    if (n == 4 && !TooLarge(v) && !TooLarge(v + 1)) {
        Emit(v, 4, textured, semi, clutX, clutY);
        return;
    }
    if (!TooLarge(v)) {
        Emit(v, 3, textured, semi, clutX, clutY);
    }
    if (n == 4 && !TooLarge(v + 1)) {
        Emit(v + 1, 3, textured, semi, clutX, clutY);
    }
}

static void DrawRectangle(const uint32_t *w)
{
    static const int sizes[4] = {0, 1, 8, 16};
    uint32_t code = w[0] >> 24;
    int textured = code & 0x04, semi = code & 0x02, raw = code & 0x01;
    int size = sizes[(code >> 3) & 3], at = 2, x, y, wdt, hgt, u = 0, vv = 0, clutX = 0, clutY = 0;
    Vertex v[4];
    int i;

    x = SignExtend11(w[1]) + sOffsetX;
    y = SignExtend11(w[1] >> 16) + sOffsetY;
    if (textured) {
        uint32_t uv = w[at++];

        u = uv & 0xFF;
        vv = (uv >> 8) & 0xFF;
        clutX = ((uv >> 16) & 0x3F) * 16;
        clutY = (uv >> 22) & 0x1FF;
    }
    if (size) {
        wdt = hgt = size;
    } else {
        wdt = w[at] & 0x3FF;
        hgt = (w[at] >> 16) & 0x1FF;
    }
    for (i = 0; i < 4; i++) {
        v[i].x = (float)(x + (i & 1 ? wdt : 0));
        v[i].y = (float)(y + (i & 2 ? hgt : 0));
        v[i].u = (float)(u + (i & 1 ? wdt : 0));
        v[i].v = (float)(vv + (i & 2 ? hgt : 0));
        v[i].color = Color(w[0], textured, raw, 1.0f);
    }
    Emit(v, 4, textured, semi, clutX, clutY);
}

/* A line as a quad one VRAM pixel wide. */
static void DrawSegment(int x0, int y0, uint32_t c0, int x1, int y1, uint32_t c1, int semi)
{
    float dx = (float)(x1 - x0), dy = (float)(y1 - y0);
    float len = SDL_sqrtf(dx * dx + dy * dy);
    float nx = len > 0 ? -dy / len * 0.5f : 0.5f, ny = len > 0 ? dx / len * 0.5f : 0.5f;
    Vertex v[4];

    if (SDL_fabsf(dx) > 1023 || SDL_fabsf(dy) > 511) {
        return; /* as for polygons */
    }
    v[0].x = x0 + nx; v[0].y = y0 + ny; v[0].color = Color(c0, 0, 0, 1.0f);
    v[1].x = x1 + nx; v[1].y = y1 + ny; v[1].color = Color(c1, 0, 0, 1.0f);
    v[2].x = x0 - nx; v[2].y = y0 - ny; v[2].color = v[0].color;
    v[3].x = x1 - nx; v[3].y = y1 - ny; v[3].color = v[1].color;
    v[0].u = v[0].v = v[1].u = v[1].v = v[2].u = v[2].v = v[3].u = v[3].v = 0;
    Emit(v, 4, 0, semi, 0, 0);
}

/* Draws a line or polyline; returns the words it used, up to MAX. */
static int DrawLine(const uint32_t *w, int max)
{
    uint32_t code = w[0] >> 24;
    int gouraud = code & 0x10, poly = code & 0x08, semi = code & 0x02;
    int at = 1, x0, y0, x1, y1;
    uint32_t c0 = w[0], c1;

    x0 = SignExtend11(w[at]) + sOffsetX;
    y0 = SignExtend11(w[at] >> 16) + sOffsetY;
    at++;
    for (;;) {
        if (at >= max) {
            return max;
        }
        c1 = c0;
        if (gouraud) {
            if (poly && (w[at] & 0xF000F000u) == 0x50005000u) {
                return at + 1;
            }
            c1 = w[at++];
        }
        if (at >= max) {
            return max;
        }
        if (poly && (w[at] & 0xF000F000u) == 0x50005000u) {
            return at + 1;
        }
        x1 = SignExtend11(w[at]) + sOffsetX;
        y1 = SignExtend11(w[at] >> 16) + sOffsetY;
        at++;
        DrawSegment(x0, y0, c0, x1, y1, c1, semi);
        if (!poly) {
            return at;
        }
        x0 = x1;
        y0 = y1;
        c0 = c1;
    }
}

static void FillRect(int x, int y, int w, int h, int r, int g, int b)
{
    SDL_FRect rect;
    int i, j;
    uint16_t c = (uint16_t)((r >> 3) | (g >> 3) << 5 | (b >> 3) << 10);

    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            sVram[((y + j) & 511) * GPU_VRAM_WIDTH + ((x + i) & 1023)] = c;
        }
    }
    Invalidate(x, y, w, h);
    rect.x = (float)(x * sScale);
    rect.y = (float)(y * sScale);
    rect.w = (float)(w * sScale);
    rect.h = (float)(h * sScale);
    SDL_SetRenderClipRect(sRenderer, NULL);
    SDL_SetRenderDrawBlendMode(sRenderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(sRenderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    SDL_RenderFillRect(sRenderer, &rect);
    ApplyClip();
}

int GpuCommandWords(uint32_t first)
{
    uint32_t code = first >> 24;

    if (code >= 0x20 && code < 0x40) {
        int n = code & 0x08 ? 4 : 3;

        return 1 + n * (1 + (code & 0x04 ? 1 : 0)) + (code & 0x10 ? n - 1 : 0);
    }
    if (code >= 0x40 && code < 0x60) {
        return code & 0x08 ? 0 : code & 0x10 ? 4 : 3;
    }
    if (code >= 0x60 && code < 0x80) {
        return 2 + (code & 0x04 ? 1 : 0) + ((code & 0x18) == 0 ? 1 : 0);
    }
    if (code == 0x02) {
        return 3;
    }
    if (code >= 0x80 && code < 0xA0) {
        return 4;
    }
    if (code >= 0xA0 && code < 0xE0) {
        return 3;
    }
    return 1;
}

/* Runs the commands in one packet's N words. */
static void RunPacket(const uint32_t *w, int n)
{
    int at = 0;

    sPackets++;
    while (at < n) {
        uint32_t code = w[at] >> 24;
        int words = GpuCommandWords(w[at]);

        if (words > n - at) {
            return;
        }
        if (code >= 0x20 && code < 0x40) {
            DrawPolygon(w + at);
        } else if (code >= 0x40 && code < 0x60) {
            words = DrawLine(w + at, n - at);
        } else if (code >= 0x60 && code < 0x80) {
            DrawRectangle(w + at);
        } else if (code == 0x02) {
            FillRect(w[at + 1] & 0x3F0, (w[at + 1] >> 16) & 0x1FF, ((w[at + 2] & 0x3FF) + 15) & ~15,
                     (w[at + 2] >> 16) & 0x1FF, w[at] & 0xFF, (w[at] >> 8) & 0xFF, (w[at] >> 16) & 0xFF);
        } else if (code == 0xE1) {
            SetPage(w[at]);
        } else if (code == 0xE3) {
            sAreaX0 = w[at] & 0x3FF;
            sAreaY0 = (w[at] >> 10) & 0x1FF;
            ApplyClip();
        } else if (code == 0xE4) {
            sAreaX1 = w[at] & 0x3FF;
            sAreaY1 = (w[at] >> 10) & 0x1FF;
            ApplyClip();
        } else if (code == 0xE5) {
            sOffsetX = SignExtend11(w[at]);
            sOffsetY = SignExtend11(w[at] >> 11);
        }
        at += words;
    }
}

/* PRIM's tag holds its length in words in the top byte. */
static void RunTagged(uint32_t prim)
{
    static uint32_t words[256];
    uint32_t tag = Read32(prim);
    int n = tag >> 24, i;

    if (n == 0 || !Valid(prim + 4, n * 4)) {
        return;
    }
    for (i = 0; i < n; i++) {
        words[i] = Read32(prim + 4 + i * 4);
    }
    RunPacket(words, n);
}

void GpuDrawPrim(uint32_t prim)
{
    SDL_SetRenderTarget(sRenderer, sTarget);
    ApplyClip();
    RunTagged(prim);
}

void GpuDrawOTag(uint32_t ot)
{
    uint32_t link = ot & 0xFFFFFF;
    int guard = 1 << 20;

    SDL_SetRenderTarget(sRenderer, sTarget);
    ApplyClip();
    while (link != 0xFFFFFF && --guard) {
        uint32_t address = link | 0x80000000u;

        RunTagged(address);
        link = Read32(address) & 0xFFFFFF;
    }
}

/* ---- VRAM transfers ---- */

/* Copies the shadow rectangle into the render target. */
static void Blit(int x, int y, int w, int h)
{
    SDL_FRect src, dst;

    SDL_UpdateTexture(sUpload, NULL, sVram, GPU_VRAM_WIDTH * 2);
    src.x = (float)x;
    src.y = (float)y;
    src.w = (float)w;
    src.h = (float)h;
    dst.x = (float)(x * sScale);
    dst.y = (float)(y * sScale);
    dst.w = (float)(w * sScale);
    dst.h = (float)(h * sScale);
    SDL_SetRenderTarget(sRenderer, sTarget);
    SDL_SetRenderClipRect(sRenderer, NULL);
    SDL_RenderTexture(sRenderer, sUpload, &src, &dst);
    ApplyClip();
}

void GpuLoadImage(uint32_t rect, uint32_t src)
{
    int x, y, w, h, j;

    ReadRect(rect, &x, &y, &w, &h);
    if (Tracing()) {
        fprintf(stderr, "gpu: LoadImage (%d, %d) %d x %d from %08X\n", x, y, w, h, src);
    }
    if (w <= 0 || h <= 0 || !Valid(src, (uint32_t)(w * h * 2))) {
        return;
    }
    for (j = 0; j < h; j++) {
        int i;

        for (i = 0; i < w; i++) {
            uint16_t c;

            memcpy(&c, sMem + src + (j * w + i) * 2, 2);
            sVram[((y + j) & 511) * GPU_VRAM_WIDTH + ((x + i) & 1023)] = c;
        }
    }
    Invalidate(x, y, w, h);
    TexturesUpload(x, y, w, h, sMem + src);
    Blit(x, y, w, h);
}

void GpuStoreImage(uint32_t rect, uint32_t dst)
{
    int x, y, w, h, i, j;

    ReadRect(rect, &x, &y, &w, &h);
    if (w <= 0 || h <= 0 || !Valid(dst, (uint32_t)(w * h * 2))) {
        return;
    }
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            uint16_t c = Vram(x + i, y + j);

            memcpy(sMem + dst + (j * w + i) * 2, &c, 2);
        }
    }
}

void GpuMoveImage(uint32_t rect, int32_t dx, int32_t dy)
{
    static uint16_t copy[GPU_VRAM_WIDTH * GPU_VRAM_HEIGHT];
    SDL_FRect src, dst;
    int x, y, w, h, i, j;

    ReadRect(rect, &x, &y, &w, &h);
    if (w <= 0 || h <= 0) {
        return;
    }
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            copy[j * w + i] = Vram(x + i, y + j);
        }
    }
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            sVram[((dy + j) & 511) * GPU_VRAM_WIDTH + ((dx + i) & 1023)] = copy[j * w + i];
        }
    }
    Invalidate(dx, dy, w, h);
    /* The rendered pixels move too, through a scratch target. */
    if (!sScratch) {
        sScratch = MakeTarget(GPU_VRAM_WIDTH * sScale, GPU_VRAM_HEIGHT * sScale);
    }
    if (!sScratch) {
        return;
    }
    src.x = (float)(x * sScale);
    src.y = (float)(y * sScale);
    src.w = dst.w = (float)(w * sScale);
    src.h = dst.h = (float)(h * sScale);
    dst.x = (float)(dx * sScale);
    dst.y = (float)(dy * sScale);
    SDL_SetTextureBlendMode(sTarget, SDL_BLENDMODE_NONE);
    SDL_SetTextureBlendMode(sScratch, SDL_BLENDMODE_NONE);
    SDL_SetRenderTarget(sRenderer, sScratch);
    SDL_SetRenderClipRect(sRenderer, NULL);
    SDL_RenderTexture(sRenderer, sTarget, &src, &src);
    SDL_SetRenderTarget(sRenderer, sTarget);
    SDL_RenderTexture(sRenderer, sScratch, &src, &dst);
    ApplyClip();
}

void GpuClearImage(uint32_t rect, int r, int g, int b)
{
    int x, y, w, h;

    ReadRect(rect, &x, &y, &w, &h);
    if (w > 0 && h > 0) {
        SDL_SetRenderTarget(sRenderer, sTarget);
        FillRect(x, y, w, h, r, g, b);
    }
}

void GpuSetDispEnv(uint32_t env)
{
    uint8_t flags[2] = {0, 0};

    ReadRect(env, &sDispX, &sDispY, &sDispW, &sDispH);
    if (Valid(env + 16, 2)) {
        memcpy(flags, sMem + env + 16, 2);
    }
    sDisp24 = flags[1];
    if (Tracing()) {
        fprintf(stderr, "gpu: display (%d, %d) %d x %d%s\n", sDispX, sDispY, sDispW, sDispH, sDisp24 ? " 24-bit" : "");
    }
    if (sDispW <= 0) {
        sDispW = 320;
    }
    if (sDispH <= 0) {
        sDispH = 240;
    }
}

/* ---- display ---- */

/* The display area as a texture and source rectangle. */
static SDL_Texture *DisplaySource(SDL_FRect *src)
{
    if (sDisp24) {
        /* 24-bit mode shows the shadow's bytes as packed RGB. */
        static uint8_t rgb[640 * 512 * 3];
        int w = SDL_min(sDispW, 640), h = SDL_min(sDispH, 512), j;

        if (!sDisplay24) {
            sDisplay24 = SDL_CreateTexture(sRenderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, 640, 512);
        }
        for (j = 0; j < h; j++) {
            int i;

            for (i = 0; i < w * 3; i += 2) {
                uint16_t c = Vram(sDispX + i / 2, sDispY + j);

                rgb[(j * 640) * 3 + i] = c & 0xFF;
                if (i + 1 < w * 3) {
                    rgb[(j * 640) * 3 + i + 1] = c >> 8;
                }
            }
        }
        SDL_UpdateTexture(sDisplay24, NULL, rgb, 640 * 3);
        src->x = src->y = 0;
        src->w = (float)w;
        src->h = (float)h;
        return sDisplay24;
    }
    src->x = (float)(sDispX * sScale);
    src->y = (float)(sDispY * sScale);
    src->w = (float)(sDispW * sScale);
    src->h = (float)(sDispH * sScale);
    return sTarget;
}

int GpuPresent(void)
{
    SDL_Event event;
    int closed = 0;

    if (Tracing()) {
        fprintf(stderr, "gpu: frame, %d packets\n", sPackets);
    }
    sPacketsLast = sPackets;
    sPackets = 0;
    while (sWindow && SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            closed = 1;
        }
    }
    if (sWindow) {
        SDL_FRect src, dst;
        SDL_Texture *t = DisplaySource(&src);
        int ww, wh;
        float w, h;

        SDL_GetRenderOutputSize(sRenderer, &ww, &wh);
        /* 4:3 whatever the display width, letterboxed. */
        w = (float)ww;
        h = w * 3 / 4;
        if (h > wh) {
            h = (float)wh;
            w = h * 4 / 3;
        }
        dst.x = (ww - w) / 2;
        dst.y = (wh - h) / 2;
        dst.w = w;
        dst.h = h;
        SDL_SetRenderTarget(sRenderer, NULL);
        SDL_SetRenderClipRect(sRenderer, NULL);
        SDL_SetRenderDrawColor(sRenderer, 0, 0, 0, 255);
        SDL_RenderClear(sRenderer);
        SDL_SetTextureBlendMode(t, SDL_BLENDMODE_NONE);
        SDL_SetTextureScaleMode(t, SDL_SCALEMODE_LINEAR);
        SDL_RenderTexture(sRenderer, t, &src, &dst);
        SDL_RenderPresent(sRenderer);
        SDL_SetTextureScaleMode(t, SDL_SCALEMODE_NEAREST);
    }
    SDL_SetRenderTarget(sRenderer, sTarget);
    ApplyClip();
    return closed;
}

int GpuPacketsLastFrame(void)
{
    return sPacketsLast;
}

uint32_t GpuTargetPixel(int x, int y)
{
    SDL_Rect r;
    SDL_Surface *s;
    uint32_t pixel = 0;
    Uint8 cr, cg, cb, ca;

    r.x = x * sScale;
    r.y = y * sScale;
    r.w = r.h = 1;
    SDL_SetRenderTarget(sRenderer, sTarget);
    SDL_SetRenderClipRect(sRenderer, NULL);
    s = SDL_RenderReadPixels(sRenderer, &r);
    ApplyClip();
    if (!s) {
        return 0;
    }
    if (SDL_ReadSurfacePixel(s, 0, 0, &cr, &cg, &cb, &ca)) {
        pixel = (uint32_t)ca << 24 | (uint32_t)cr << 16 | (uint32_t)cg << 8 | cb;
    }
    SDL_DestroySurface(s);
    return pixel;
}

int GpuScreenshot(const char *path)
{
    SDL_FRect src;
    SDL_Texture *t = DisplaySource(&src);
    SDL_Surface *s;
    SDL_Rect r;
    int ok;

    if (t == sTarget) {
        r.x = (int)src.x;
        r.y = (int)src.y;
        r.w = (int)src.w;
        r.h = (int)src.h;
        SDL_SetRenderTarget(sRenderer, sTarget);
        SDL_SetRenderClipRect(sRenderer, NULL);
        s = SDL_RenderReadPixels(sRenderer, &r);
        ApplyClip();
    } else {
        /* 24-bit: rebuild from the shadow. */
        int w = (int)src.w, h = (int)src.h, j, i;

        s = SDL_CreateSurface(w, h, SDL_PIXELFORMAT_RGB24);
        for (j = 0; s && j < h; j++) {
            for (i = 0; i < w * 3; i++) {
                uint16_t c = Vram(sDispX + i / 2, sDispY + j);

                ((uint8_t *)s->pixels)[j * s->pitch + i] = i & 1 ? c >> 8 : c & 0xFF;
            }
        }
    }
    if (!s) {
        return 1;
    }
    ok = SDL_SaveBMP(s, path);
    SDL_DestroySurface(s);
    return ok ? 0 : 1;
}
