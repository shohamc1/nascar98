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

BREW_LLVM := $(shell brew --prefix llvm 2>/dev/null)
WASM_CC   ?= $(BREW_LLVM)/bin/clang
WASM_LD   ?= wasm-ld
WASM2C    ?= wasm2c
WASM2C_RT ?= $(shell brew --prefix wabt 2>/dev/null)/share/wabt/wasm2c
PYTHON    ?= .venv/bin/python
NM        ?= mipsel-linux-gnu-nm
WASM_NM   ?= $(BREW_LLVM)/bin/llvm-nm

PORT  := build/port
ELF   := build/slus_005.21.elf
UNDEF := build/undefined_syms_auto.txt

WASM_CFLAGS := --target=wasm32 -O2 -std=gnu89 -DNATIVE=1 -ffreestanding -fno-builtin \
               -nostdlibinc -Wno-incompatible-pointer-types -Wno-int-conversion \
               -Wno-incompatible-function-pointer-types \
               -ferror-limit=0 -include port_asm.h -Iport/include -I$(PORT)/include -Iinclude -Ibuild

# Address spans of asm/data/data.data.s and bss.bss.s, and of the image.
DATA_RANGES := --data-range 0x80090DC8:0x800A2CE0 --data-range 0x800A33C0:0x800BEBA4
IMAGE       := --image 0x80010000:0x800CEFE0

GAME_SRCS := $(wildcard src/*.c)
NATIVES   := $(wildcard port/native/*.c)
PORT_SRCS := $(GAME_SRCS:src/%=$(PORT)/src/%)
OBJS      := $(GAME_SRCS:src/%.c=$(PORT)/obj/%.o)
SDK_OBJS  := $(patsubst port/sdk/%.c,$(PORT)/sdk/%.o,$(wildcard port/sdk/*.c))

# splat's data: initialised .data, .bss, and the .rodata that
# INCLUDE_RODATA lines name.
DATA_INPUTS := asm/data/data.data.s asm/data/bss.bss.s \
               $(shell sed -n 's/^INCLUDE_RODATA("\([^"]*\)", *\([A-Za-z_0-9]*\)).*/\1\/\2.s/p' $(GAME_SRCS))

WASM_LDFLAGS := --global-base=2147549184 --initial-memory=2151677952 \
                --max-memory=2151677952 -z stack-size=262144 --no-entry \
                --export=PortStart --fatal-warnings

.PHONY: objects undefined module FORCE

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

# The filter reads every source at once (aliases cross files), and swaps
# in port/native/FUNC.c for each function whose MIPS asm carries behaviour.
# It runs every time (whole-second mtimes miss same-second edits) and
# rewrites only the outputs that change.
$(PORT)/src/.stamp: FORCE $(UNDEF) $(PORT)/symbols.txt $(PORT)/defined.txt
	$(PYTHON) tools/port_filter.py --makefile Makefile --absolutes $(UNDEF) --fixed build/fixed_addrs.ld \
	  --symbols $(PORT)/symbols.txt --defined $(PORT)/defined.txt \
	  $(DATA_RANGES) $(IMAGE) --native-dir port/native --header-out $(PORT)/include \
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
# --no-gc-sections keeps every function live, not just what PortStart
# reaches, and any link error but an undefined symbol fails the target.
undefined: $(OBJS) $(PORT)/data.o
	@$(WASM_LD) $(filter-out --export=PortStart,$(WASM_LDFLAGS)) --no-gc-sections --error-limit=0 \
	  $(OBJS) $(PORT)/data.o -o $(PORT)/undefined.wasm > $(PORT)/undefined.log 2>&1; \
	  sed -n 's/.*undefined symbol: //p' $(PORT)/undefined.log | sort -u > $(PORT)/sdk-undefined.txt; \
	  if grep 'error:' $(PORT)/undefined.log | grep -v 'undefined symbol' >&2; then exit 1; fi; \
	  echo "$$(wc -l < $(PORT)/sdk-undefined.txt) undefined symbols: $(PORT)/sdk-undefined.txt"

# port/sdk/ must define no symbol the game defines: the game's own code
# and data win, and the SDK fills in only what the game leaves undefined.
module: $(PORT)/nascar98.wasm

$(PORT)/nascar98.wasm: $(OBJS) $(SDK_OBJS) $(PORT)/data.o
	@$(WASM_NM) --defined-only --extern-only -j $(SDK_OBJS) | grep -v -e ':$$' -e '^$$' | sort -u > $(PORT)/sdk-symbols.txt
	@$(WASM_NM) --defined-only --extern-only -j $(OBJS) $(PORT)/data.o | grep -v -e ':$$' -e '^$$' | sort -u | \
	  comm -12 - $(PORT)/sdk-symbols.txt > $(PORT)/sdk-overlap.txt
	@if [ -s $(PORT)/sdk-overlap.txt ]; then \
	  echo "port/sdk defines game symbols:" $$(cat $(PORT)/sdk-overlap.txt) >&2; exit 1; fi
	$(WASM_LD) $(WASM_LDFLAGS) $(OBJS) $(SDK_OBJS) $(PORT)/data.o -o $@
