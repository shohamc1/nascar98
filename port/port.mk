# Native port build. Run from the repo root: make -f port/port.mk TARGET
#
# The game's C compiles to wasm32 with data at the retail addresses, and
# wasm2c turns the module into host C (kb: native-port-pointer-model.md).
# It needs the matching build's outputs, so run `make check` first.
#
# Targets:
#   objects    compile the filtered game sources to build/port/obj/
#   undefined  link without the port SDK and list what it must define
#   module     link the game, port/sdk/, and the data into nascar98.wasm
#   nascar98   translate the module with wasm2c and build the native runner;
#              with HOST=windows, cross-compile nascar98.exe in Docker
#   run        play the game in a window
#   run-headless  run the runner for 600 frames without a window

BREW_LLVM := $(shell brew --prefix llvm 2>/dev/null)
WASM_CC   ?= $(BREW_LLVM)/bin/clang
WASM_LD   ?= wasm-ld
WASM2C    ?= wasm2c
WASM2C_RT ?= $(shell brew --prefix wabt 2>/dev/null)/share/wabt/wasm2c
# wasm-rt.h: Homebrew keeps it in include/. On Debian, set WASM2C_RT and
# WASM2C_INC to /usr/src/wasm2c: /usr/share/wabt/wasm2c lacks the .inc files.
WASM2C_INC ?= $(WASM2C_RT)/../../../include
HOST_CC   ?= cc
SDL_CFLAGS ?= $(shell pkg-config --cflags sdl3)
SDL_LIBS   ?= $(shell pkg-config --libs sdl3)
PYTHON    ?= .venv/bin/python
NM        ?= mipsel-linux-gnu-nm
WASM_NM   ?= $(BREW_LLVM)/bin/llvm-nm

PORT  := build/port
ELF   := build/slus_005.21.elf
UNDEF := build/undefined_syms_auto.txt

# The game writes the same memory through different pointer types (the
# scratchpad as s32 and u16 words), as GCC 2.7.2 allowed. It also reads
# past one global into the next, so globals set to 0 stay in .data beside
# their neighbours, as GCC 2.7.2 put them, and the link keeps them all.
WASM_CFLAGS := --target=wasm32 -O2 -std=gnu89 -DNATIVE=1 -ffreestanding -fno-builtin -fno-strict-aliasing \
               -fno-zero-initialized-in-bss \
               -nostdlibinc -Wno-incompatible-pointer-types -Wno-int-conversion \
               -Wno-incompatible-function-pointer-types \
               -ferror-limit=0 -include port_asm.h -Iport/include -I$(PORT)/include -Iinclude -Ibuild

# Address spans of asm/data/data.data.s and bss.bss.s, and of the image.
DATA_RANGES := --data-range 0x80090DC8:0x800A2CE0 --data-range 0x800A33C0:0x800BEBA4
IMAGE       := --image 0x80010000:0x800CEFE0

GAME_SRCS := $(wildcard src/*.c)
PORT_SRCS := $(GAME_SRCS:src/%=$(PORT)/src/%)
OBJS      := $(GAME_SRCS:src/%.c=$(PORT)/obj/%.o)
SDK_OBJS  := $(patsubst port/sdk/%.c,$(PORT)/sdk/%.o,$(wildcard port/sdk/*.c))

# splat's initialised .data and .bss. Rodata is defined in the C sources.
DATA_INPUTS := asm/data/data.data.s asm/data/bss.bss.s

WASM_LDFLAGS := --global-base=2147557376 --initial-memory=2151677952 \
                --max-memory=2151677952 -z stack-size=262144 --no-stack-first --no-entry \
                --export=PortStart --export=gPortCallRing \
                --export=gPortCallNext --no-gc-sections --fatal-warnings

.PHONY: objects undefined module nascar98 run run-headless FORCE

objects:
	@fail=0; for o in $(OBJS); do \
	  $(MAKE) -s -f port/port.mk $$o || { echo "FAIL $$o (log: $${o%.o}.log)"; fail=1; }; \
	done; exit $$fail

$(ELF) $(UNDEF):
	@echo "port: $@ is missing: run make check first" >&2; exit 1

$(PORT)/symbols.txt: $(ELF)
	@mkdir -p $(@D)
	$(NM) -S --defined-only $< > $@

$(PORT)/defined.txt: $(ELF)
	@mkdir -p $(@D)
	$(NM) --defined-only build/src/*.c.o | awk 'NF == 3' > $@

# The filter reads every source at once (aliases cross files), and keeps
# the #ifdef NATIVE body of each function whose MIPS asm carries behaviour.
# It runs every time (whole-second mtimes miss same-second edits) and
# rewrites only the outputs that change.
$(PORT)/src/.stamp: FORCE $(UNDEF) $(PORT)/symbols.txt $(PORT)/defined.txt
	$(PYTHON) tools/port_filter.py --makefile Makefile --absolutes $(UNDEF) --fixed build/fixed_addrs.ld \
	  --symbols $(PORT)/symbols.txt --defined $(PORT)/defined.txt \
	  $(DATA_RANGES) $(IMAGE) --padded-ok port/padded-ok.txt --header-out $(PORT)/include \
	  $(GAME_SRCS) $(PORT)/src
	@touch $@

$(PORT_SRCS): $(PORT)/src/.stamp

# memory_card.c calls strcat before declaring it (see port_prelude.h).
$(PORT)/obj/memory_card.o: WASM_CFLAGS += -include port_prelude.h

# -MMD tracks the headers each object includes, filtered ones among them.
$(PORT)/obj/%.o: $(PORT)/src/%.c
	@mkdir -p $(@D)
	$(WASM_CC) $(WASM_CFLAGS) -MMD -MP -c $< -o $@ 2> $(@:.o=.log) || { tail -3 $(@:.o=.log) >&2; exit 1; }

$(PORT)/sdk/%.o: port/sdk/%.c
	@mkdir -p $(@D)
	$(WASM_CC) $(WASM_CFLAGS) -Iport/sdk -MMD -MP -c $< -o $@

-include $(OBJS:.o=.d) $(SDK_OBJS:.o=.d)

$(PORT)/sdk-defined.txt: $(ELF)
	@mkdir -p $(@D)
	$(NM) --defined-only build/src/psxsdk/*.c.o | awk 'NF == 3' > $@

# Signatures of every port function, for function pointers in data.
$(PORT)/objdump.txt: $(OBJS) $(SDK_OBJS)
	wasm-objdump -x $(OBJS) $(SDK_OBJS) > $@

$(PORT)/data.s: $(DATA_INPUTS) tools/port_data.py tools/port_filter.py $(PORT)/objdump.txt \
                $(PORT)/symbols.txt $(PORT)/defined.txt $(PORT)/sdk-defined.txt $(UNDEF)
	$(PYTHON) tools/port_data.py --signatures $(PORT)/objdump.txt --makefile Makefile \
	  --absolutes $(UNDEF) --fixed build/fixed_addrs.ld --symbols $(PORT)/symbols.txt --defined $(PORT)/defined.txt \
	  --sdk-defined $(PORT)/sdk-defined.txt $(DATA_RANGES) $(IMAGE) $@ $(DATA_INPUTS)

$(PORT)/data.o: $(PORT)/data.s
	$(WASM_CC) --target=wasm32 -c $< -o $@

# The symbols the port SDK must define: everything the game leaves undefined.
# --no-gc-sections keeps every function live, not just what the exports
# reach, and any link error but an undefined symbol fails the target.
undefined: $(OBJS) $(PORT)/data.o
	@$(WASM_LD) $(filter-out --export=%,$(WASM_LDFLAGS)) --no-gc-sections --error-limit=0 \
	  $(OBJS) $(PORT)/data.o -o $(PORT)/undefined.wasm > $(PORT)/undefined.log 2>&1; \
	  sed -n 's/.*undefined symbol: //p' $(PORT)/undefined.log | sort -u > $(PORT)/sdk-undefined.txt; \
	  if grep 'error:' $(PORT)/undefined.log | grep -v 'undefined symbol' >&2; then exit 1; fi; \
	  echo "$$(wc -l < $(PORT)/sdk-undefined.txt) undefined symbols: $(PORT)/sdk-undefined.txt"

# port/sdk/ must define no symbol the game defines, in the port's objects
# or in the matching build (defined.txt), so a game function the filter
# drops fails here instead of resolving to a stub.
module: $(PORT)/nascar98.wasm

$(PORT)/nascar98.wasm: $(OBJS) $(SDK_OBJS) $(PORT)/data.o $(PORT)/defined.txt port/port.mk
	@$(WASM_NM) --defined-only --extern-only -j $(SDK_OBJS) | grep -v -e ':$$' -e '^$$' | sort -u > $(PORT)/sdk-symbols.txt
	@{ $(WASM_NM) --defined-only --extern-only -j $(OBJS) $(PORT)/data.o | grep -v -e ':$$' -e '^$$'; \
	  awk '{print $$NF}' $(PORT)/defined.txt; } | sort -u | \
	  comm -12 - $(PORT)/sdk-symbols.txt > $(PORT)/sdk-overlap.txt
	@if [ -s $(PORT)/sdk-overlap.txt ]; then \
	  echo "port/sdk defines game symbols:" $$(cat $(PORT)/sdk-overlap.txt) >&2; exit 1; fi
	@# Clang compiles a call whose types don't match the callee's definition
	@# in the same file into a trap (a _bitcast_invalid stub): fail on any.
	@if wasm-objdump -d $(OBJS) $(SDK_OBJS) | grep -m5 'call .*bitcast_invalid' >&2; then \
	  echo "port: calls compiled to traps (see tools/port_filter.py rule 9)" >&2; exit 1; fi
	$(WASM_LD) $(WASM_LDFLAGS) -Map=$(PORT)/nascar98.map $(OBJS) $(SDK_OBJS) $(PORT)/data.o -o $@

# wasm2c's output is one large file: -O1 builds it in about a quarter of
# the time -O2 takes.
ifeq ($(HOST),windows)
nascar98: $(PORT)/windows/nascar98.exe
else
nascar98: $(PORT)/nascar98
endif

# port/host/mips_div.h replaces the division macros: MIPS doesn't trap.
$(PORT)/nascar98_wasm.c: $(PORT)/nascar98.wasm port/host/mips_div.h
	$(WASM2C) $< -n nascar98 -o $@
	sed -i.bak '/^#define REM_U(x, y) DIVREM_U/r port/host/mips_div.h' $@ && rm $@.bak
	@grep -q PORT_MIPS_DIV $@ || { echo "port: wasm2c's division macros changed: update port/host/mips_div.h" >&2; rm $@; exit 1; }

$(PORT)/nascar98: $(PORT)/nascar98_wasm.c $(wildcard port/host/*.c port/host/*.h)
	$(HOST_CC) -O1 -I$(PORT) -Iport/host -I$(WASM2C_RT) -I$(WASM2C_INC) $(SDL_CFLAGS) -o $@ \
	  $(PORT)/nascar98_wasm.c $(wildcard port/host/*.c) $(WASM2C_RT)/wasm-rt-impl.c \
	  $(WASM2C_RT)/wasm-rt-mem-impl.c $(WASM2C_RT)/wasm-rt-exceptions-impl.c $(SDL_LIBS) -lm

run-headless: $(PORT)/nascar98
	NASCAR98_HEADLESS=1 NASCAR98_FRAMES=600 $(PORT)/nascar98

# Opens the game in a window.
run: $(PORT)/nascar98
	$(PORT)/nascar98

# Windows: MinGW-w64 and SDL3's MinGW release in Docker (port/windows/).
# The host's wasm2c runtime is copied in, so it matches the translated
# module, and SDL3.dll goes beside the executable.
WIN := $(PORT)/windows

$(WIN)/nascar98.exe: $(PORT)/nascar98_wasm.c $(wildcard port/host/*.c port/host/*.h) port/windows/Dockerfile
	@mkdir -p $(WIN)/wasm2c
	cp $(WASM2C_RT)/wasm-rt-* $(WASM2C_INC)/wasm-rt*.h $(WIN)/wasm2c/
	docker build -q -t nascar98-mingw port/windows
	docker run --rm -v "$(CURDIR)":/src -w /src nascar98-mingw sh -c '\
	  x86_64-w64-mingw32-gcc -O1 -I$(PORT) -Iport/host -I$(WIN)/wasm2c -I/opt/sdl3/include -o $@ \
	    $(PORT)/nascar98_wasm.c port/host/*.c $(WIN)/wasm2c/wasm-rt-impl.c $(WIN)/wasm2c/wasm-rt-mem-impl.c \
	    $(WIN)/wasm2c/wasm-rt-exceptions-impl.c -L/opt/sdl3/lib -lSDL3 -lm && \
	  cp /opt/sdl3/bin/SDL3.dll $(WIN)/'
