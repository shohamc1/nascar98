/*
 * The port SDK's view of the host: the functions the wasm module imports
 * from "env". port/host/main.c supplies them.
 */
#ifndef PORT_SDK_HOST_H
#define PORT_SDK_HOST_H

#include "types.h"

#define HOST_IMPORT(name) __attribute__((import_module("env"), import_name(#name)))

/* Writes one line of TEXT to the run log. */
HOST_IMPORT(HostLog) void HostLog(const char *text);
/* Reads COUNT 2048-byte sectors from LBA into DST: sectors read, or -1. */
HOST_IMPORT(HostCdRead) int32_t HostCdRead(uint32_t lba, uint32_t count, void *dst);
/* Reads the raw 2352-byte sector at LBA into DST: 0, or -1 past the end. */
HOST_IMPORT(HostCdReadRaw) int32_t HostCdReadRaw(uint32_t lba, void *dst);
/* Ends one frame: nonzero when the run must stop. */
HOST_IMPORT(HostFrame) int32_t HostFrame(void);
HOST_IMPORT(HostExit) void HostExit(int32_t code);

/* Port 0 or 1's buttons, active high; bit 16 set when a pad is connected. */
HOST_IMPORT(HostPadRead) uint32_t HostPadRead(int32_t port);

/* The GPU (port/host/gpu.h): pointers are module addresses. */
HOST_IMPORT(HostGpuReset) void HostGpuReset(void);
HOST_IMPORT(HostGpuLoadImage) void HostGpuLoadImage(const void *rect, const void *src);
HOST_IMPORT(HostGpuStoreImage) void HostGpuStoreImage(const void *rect, void *dst);
HOST_IMPORT(HostGpuMoveImage) void HostGpuMoveImage(const void *rect, int32_t x, int32_t y);
HOST_IMPORT(HostGpuClearImage) void HostGpuClearImage(const void *rect, int32_t r, int32_t g, int32_t b);
HOST_IMPORT(HostGpuDrawOTag) void HostGpuDrawOTag(const void *ot);
HOST_IMPORT(HostGpuDrawPrim) void HostGpuDrawPrim(const void *prim);
HOST_IMPORT(HostGpuSetDispEnv) void HostGpuSetDispEnv(const void *env);

/*
 * The last 16 SDK functions entered, oldest first from gPortCallNext.
 * The module exports both, and the host's watchdog prints them.
 */
extern const char *gPortCallRing[16];
extern u32 gPortCallNext;
#define PORT_TRACE(name) (gPortCallRing[gPortCallNext++ & 15] = #name)

/* Traces the call, and logs "stub: NAME" the first time it runs. */
#define PORT_STUB(name)                                                                              \
    do {                                                                                           \
        static int portLogged;                                                                     \
        PORT_TRACE(name);                                                                          \
        if (!portLogged) {                                                                         \
            portLogged = 1;                                                                        \
            HostLog("stub: " #name);                                                     \
        }                                                                                          \
    } while (0)

#endif /* PORT_SDK_HOST_H */
