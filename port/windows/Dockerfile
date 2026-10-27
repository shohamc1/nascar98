# The Windows cross-compiler for the port: MinGW-w64 and SDL3's MinGW
# release. port/port.mk mounts the repository and wasm2c's runtime.
FROM debian:trixie-slim

ARG SDL_VERSION=3.4.18
RUN apt-get update \
 && apt-get install -y --no-install-recommends gcc-mingw-w64-x86-64 curl ca-certificates make \
 && rm -rf /var/lib/apt/lists/*
RUN curl -fsSL "https://github.com/libsdl-org/SDL/releases/download/release-${SDL_VERSION}/SDL3-devel-${SDL_VERSION}-mingw.tar.gz" \
    | tar -xz -C /opt \
 && mv /opt/SDL3-${SDL_VERSION}/x86_64-w64-mingw32 /opt/sdl3 \
 && rm -rf /opt/SDL3-${SDL_VERSION}
