/*
 * The port SDK's view of the host: the four functions the wasm module
 * imports from "env". port/host/main.c supplies them.
 */
#ifndef PORT_SDK_HOST_H
#define PORT_SDK_HOST_H

#include "types.h"

#define HOST_IMPORT(name) __attribute__((import_module("env"), import_name(#name)))

/* Writes one line of TEXT to the run log. */
HOST_IMPORT(HostLog) void HostLog(const char *text);
/* Reads COUNT 2048-byte sectors from LBA into DST: sectors read, or -1. */
HOST_IMPORT(HostCdRead) int32_t HostCdRead(uint32_t lba, uint32_t count, void *dst);
/* Ends one frame: nonzero when the run must stop. */
HOST_IMPORT(HostFrame) int32_t HostFrame(void);
HOST_IMPORT(HostExit) void HostExit(int32_t code);

/* Logs "stub: NAME" the first time the enclosing function runs. */
#define PORT_STUB(name)                                                                              \
    do {                                                                                           \
        static int portLogged;                                                                     \
        if (!portLogged) {                                                                         \
            portLogged = 1;                                                                        \
            HostLog("stub: " #name);                                                     \
        }                                                                                          \
    } while (0)

#endif /* PORT_SDK_HOST_H */
