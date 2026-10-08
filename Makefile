# NASCAR 98 (USA) matching decompilation.
#
#   make extract   copy the EXE and data out of your disc image (once)
#   make split     regenerate asm/ and the linker script with splat
#   make check     build SLUS_005.21 and compare it with the original
#   make expected  snapshot a matching build for objdiff
#   make report    write build/report.json for decomp.dev
#   make format    run clang-format on the C sources and our own headers

SHELL := bash
.SHELLFLAGS := -o pipefail -c
# Make 3.81 (macOS) ignores .SHELLFLAGS, so pipelines that must fail on any
# stage also say `set -o pipefail`. Delete a target whose recipe failed, so
# the next make doesn't reuse a half-written object.
.DELETE_ON_ERROR:

BASENAME := slus_005.21
EXE      := build/SLUS_005.21
ELF      := build/$(BASENAME).elf
LD_SCRIPT := build/$(BASENAME).ld
SPLAT_CFG := config/$(BASENAME).yaml
CUE      ?= $(firstword $(wildcard disc/*.cue) $(wildcard */*.cue))

PYTHON := .venv/bin/python

UNAME := $(shell uname -s)-$(shell uname -m)
ifeq ($(UNAME),Darwin-arm64)
  OBJDIFF_PLATFORM := macos-arm64
  OLD_GCC_SUFFIX := -macos
else ifeq ($(UNAME),Darwin-x86_64)
  OBJDIFF_PLATFORM := macos-x86_64
  OLD_GCC_SUFFIX := -macos
else
  OBJDIFF_PLATFORM := linux-x86_64
  OLD_GCC_SUFFIX :=
endif
CROSS  := mipsel-linux-gnu-
AS      := $(CROSS)as
LD      := $(CROSS)ld
OBJCOPY := $(CROSS)objcopy

# Compiler and assembler versions, decided by matching. See AGENTS.md.
# 2.7.2-psx-nascar98 is GCC 2.7.2 with tools/gcc-nascar98.patch: load
# latency 4, high-part multiply latency 12, and an unfused R4000 multiply.
# See "High-part multiply scheduling" in kb/psx/toolchain.md.
CC_VER    ?= 2.7.2-psx-nascar98
ASPSX_VER ?= 2.34
GP_SIZE   ?= 8
CC_DIR := tools/cc/$(CC_VER)
CPP    := $(CC_DIR)/cpp
CC1    := $(CC_DIR)/cc1
MASPSX := $(PYTHON) tools/maspsx_extern.py --aspsx-version=$(ASPSX_VER) -G$(GP_SIZE) --dont-force-G0 --expand-div

CPPFLAGS := -Iinclude -Ibuild -undef -Wall -lang-c -nostdinc \
            -D__GNUC__=2 -D__OPTIMIZE__ -Dmips -D__mips__ -D__mips -Dpsx \
            -D__psx__ -D__psx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C
# R4000 scheduling matches func_8002DDA0; keep the PSX instruction set.
CFLAGS   := -O2 -G$(GP_SIZE) -mcpu=r4000 -mips1 -mgas -msoft-float -fgnu-linker -quiet -w
ASFLAGS  := -EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -Iinclude
LDFLAGS  := -nostdlib --no-check-sections -T $(LD_SCRIPT) \
            -T build/undefined_syms_auto.txt -T build/undefined_funcs_auto.txt \
            --defsym=D_800A2F9CAbsolute=D_800A2F9C \
            --defsym=D_800A3A2CAbsolute2=D_800A3A2C \
            --defsym=D_800A3A34Absolute2=D_800A3A34 \
            --defsym=D_800A2F2CAbsolute=D_800A2F2C \
            --defsym=D_800A3378Small=D_800A3378 \
            --defsym=D_800A37E8Small=D_800A37E8 \
            --defsym=D_800A37E8Absolute=D_800A37E8 \
            --defsym=D_800A397CSmall=D_800A397C \
            --defsym=D_800A397CAbsolute=D_800A397C \
            --defsym=D_800A3A3CSmall=D_800A3A3C \
            --defsym=D_800A3A3CAbsolute=D_800A3A3C \
            --defsym=D_800A3A2CSmall=D_800A3A2C \
            --defsym=D_800A3A2CAbsolute=D_800A3A2C \
            --defsym=D_800A3A34Small=D_800A3A34 \
            --defsym=D_800A3A34Absolute=D_800A3A34 \
            --defsym=D_800A2F9DSmall=D_800A2F9D \
            --defsym=D_800A2F9DAbsolute=D_800A2F9D \
            --defsym=D_800A3694Small=D_800A3694 \
            --defsym=D_800A3694Absolute=D_800A3694 \
            --defsym=D_800A2EACSmall=D_800A2EAC \
            --defsym=D_800A2EACAbsolute=D_800A2EAC \
            --defsym=D_800A2EC0Small=D_800A2EC0 \
            --defsym=D_800A2EC0Absolute=D_800A2EC0 \
            --defsym=D_800A2EB0Small=D_800A2EB0 \
            --defsym=D_800A2EB0Absolute=D_800A2EB0 \
            --defsym=D_800A2E24Small=D_800A2E24 \
            --defsym=D_800A2E24Absolute=D_800A2E24 \
            --defsym=D_800A331CSmall=D_800A331C \
            --defsym=D_800A331CAbsolute=D_800A331C \
            --defsym=D_800A3320Small=D_800A3320 \
            --defsym=D_800A3320Absolute=D_800A3320 \
            --defsym=D_800A3668Small=D_800A3668 \
            --defsym=D_800A3668Absolute=D_800A3668 \
            --defsym=D_800A2E84Small=D_800A2E84 \
            --defsym=D_800A2E84Absolute=D_800A2E84 \
            --defsym=D_800A39A4Small=D_800A39A4 \
            --defsym=D_800A39A4Absolute=D_800A39A4 \
            --defsym=D_800A3A40Small=D_800A3A40 \
            --defsym=D_800A3A40Absolute=D_800A3A40 \
            --defsym=gStandingsNameXAbsolute=gStandingsNameX \
            --defsym=D_800A3A8CSmall=D_800A3A8C \
            --defsym=D_800A3A8CAbsolute=D_800A3A8C \
            --defsym=D_800A2EA0Small=D_800A2EA0 \
            --defsym=D_800A2EA0Absolute=D_800A2EA0 \
            --defsym=D_800A2EA4Small=D_800A2EA4 \
            --defsym=D_800A2EA4Absolute=D_800A2EA4 \
            --defsym=D_800A2EC8Small=D_800A2EC8 \
            --defsym=D_800A2EC8Absolute=D_800A2EC8 \
            --defsym=D_800A3A54Small=D_800A3A54 \
            --defsym=D_800A3A54Absolute=D_800A3A54 \
            --defsym=gOrderingTableBankSmall=gOrderingTableBank \
            --defsym=gOrderingTableBankAbsolute=gOrderingTableBank \
            --defsym=D_800A384CSmall=D_800A384C \
            --defsym=D_800A384CAbsolute=D_800A384C \
            --defsym=D_800A3854Small=D_800A3854 \
            --defsym=D_800A3854Absolute=D_800A3854 \
            --defsym=D_800A36D0Small=D_800A36D0 \
            --defsym=D_800A36D0Absolute=D_800A36D0 \
            --defsym=D_800A36D4Small=D_800A36D4 \
            --defsym=D_800A36D4Absolute=D_800A36D4 \
            --defsym=D_800A3784Small=D_800A3784 \
            --defsym=D_800A3784Absolute=D_800A3784 \
            --defsym=D_800A3790Small=D_800A3790 \
            --defsym=D_800A3790Absolute=D_800A3790 \
            --defsym=D_800A3794Small=D_800A3794 \
            --defsym=D_800A3794Absolute=D_800A3794 \
            --defsym=D_800A3798Small=D_800A3798 \
            --defsym=D_800A3798Absolute=D_800A3798 \
            --defsym=D_800A379CSmall=D_800A379C \
            --defsym=D_800A379CAbsolute=D_800A379C \
            --defsym=D_800A37A4Small=D_800A37A4 \
            --defsym=D_800A37A4Absolute=D_800A37A4 \
            --defsym=D_800A37ACSmall=D_800A37AC \
            --defsym=D_800A37ACAbsolute=D_800A37AC \
            --defsym=D_800A37B4Small=D_800A37B4 \
            --defsym=D_800A37B4Absolute=D_800A37B4 \
            --defsym=D_800A37C4Small=D_800A37C4 \
            --defsym=D_800A37C4Absolute=D_800A37C4 \
            --defsym=D_800A36C0Small=D_800A36C0 \
            --defsym=D_800A36C0Absolute=D_800A36C0 \
            --defsym=D_800A36E8Small=D_800A36E8 \
            --defsym=D_800A36E8Absolute=D_800A36E8 \
            --defsym=D_800A2DECSmall=D_800A2DEC \
            --defsym=D_800A2DECAbsolute=D_800A2DEC \
            --defsym=D_800A2DF0Small=D_800A2DF0 \
            --defsym=D_800A2DF0Absolute=D_800A2DF0 \
            --defsym=D_800A2DF4Small=D_800A2DF4 \
            --defsym=D_800A2DF4Absolute=D_800A2DF4 \
            --defsym=D_800A3A24Small=D_800A3A24 \
            --defsym=D_800A3A24Absolute=D_800A3A24 \
            --defsym=D_800A39E4Small=D_800A39E4 \
            --defsym=D_800A39E4Absolute=D_800A39E4 \
            --defsym=D_800A2E9CSmall=D_800A2E9C \
            --defsym=D_800A305BSmall=D_800A305B \
            --defsym=D_800A36E0Small=D_800A36E0 \
            --defsym=D_800A37F0Absolute=D_800A37F0 \
            --defsym=D_800A37F0Absolute2=D_800A37F0 \
            --defsym=D_800A3830Absolute=D_800A3830 \
            --defsym=D_800A3830Absolute2=D_800A3830 \
            --defsym=D_800A37F0Absolute3=D_800A37F0 \
            --defsym=D_800A38C0Small=D_800A38C0 \
            --defsym=D_800A38C0Absolute=D_800A38C0 \
            --defsym=D_800A39E4Absolute2=D_800A39E4

# SDK C matches with R3000 scheduling. Game flags stay above. The SDK
# compiler adds tools/gcc-sdk.patch: Sony's library compiler never fills
# the epilogue delay slot (0 of 483 SDK returns, 7 of 857 game returns).
build/src/psxsdk.c.o: CFLAGS := $(subst -mcpu=r4000,-mcpu=r3000,$(CFLAGS))
build/src/psxsdk.c.o: CC1 := tools/cc/$(CC_VER)-sdk/cc1

# Splat writes asm/ and the linker script, and the file lists below need
# them, so a fresh tree splits before Make reads the lists.
ifeq ($(wildcard $(LD_SCRIPT)),)
ifneq ($(wildcard disc/SLUS_005.21),)
$(info Running splat on disc/SLUS_005.21)
$(shell $(PYTHON) -m splat split $(SPLAT_CFG) > build-split.log 2>&1 || cat build-split.log >&2; rm -f build-split.log)
endif
endif

C_FILES := $(shell find src -name '*.c' 2>/dev/null)
S_FILES := $(shell find asm -name '*.s' -not -path 'asm/nonmatchings/*' 2>/dev/null)
O_FILES := $(C_FILES:%=build/%.o) $(S_FILES:%=build/%.o)

OBJDIFF := tools/bin/objdiff-cli
OBJDIFF_VER := v3.8.2
OLD_GCC_VER := 0.17

.PHONY: all check extract split expected report format tools clean distclean
.DELETE_ON_ERROR:

all: $(EXE)

check: $(EXE)
	@shasum -c config/SLUS_005.21.sha1 >/dev/null 2>&1 \
	  && echo "MATCH" || (echo "MISMATCH"; exit 1)

extract:
	@test -n "$(CUE)" || (echo "Set CUE=path/to/NASCAR 98 (USA).cue"; exit 1)
	$(PYTHON) tools/extract.py "$(CUE)" disc

split:
	$(PYTHON) -m splat split $(SPLAT_CFG)

$(LD_SCRIPT): $(SPLAT_CFG) config/symbol_addrs.txt
	$(PYTHON) -m splat split $(SPLAT_CFG)

build/fixed_addrs.h: config/symbol_addrs.txt tools/fixed_addrs.py
	@mkdir -p $(@D)
	$(PYTHON) tools/fixed_addrs.py $< > $@

build/%.c.o: %.c $(LD_SCRIPT) build/fixed_addrs.h
	@mkdir -p $(@D)
	set -o pipefail; $(CPP) $(CPPFLAGS) $< | $(CC1) $(CFLAGS) | $(MASPSX) | $(AS) $(ASFLAGS) -G$(GP_SIZE) -o $@

build/%.s.o: %.s $(LD_SCRIPT)
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) -G0 -o $@ $<

$(ELF): $(O_FILES) $(LD_SCRIPT)
	$(LD) $(LDFLAGS) -Map build/$(BASENAME).map -o $@

# The retail EXE pads its last sector with zeros to 0x92000 bytes.
$(EXE): $(ELF)
	$(OBJCOPY) -O binary --gap-fill 0 --pad-to 0x92000 $< $@

objdiff.json: tools/objdiff_config.py $(C_FILES)
	python3 tools/objdiff_config.py > $@

# objdiff's target objects. Take the snapshot only from a matching build.
expected: check objdiff.json
	rm -rf expected
	mkdir -p expected
	cp -R build expected/build

# Our headers only: include/psxsdk/ and include/types.h come from sotn-decomp.
format:
	clang-format -i $(C_FILES) include/common.h include/include_asm.h

report: objdiff.json $(EXE)
	@test -d expected || $(MAKE) expected
	$(OBJDIFF) report generate -o build/report.json
	@python3 -c "import json; m=json.load(open('build/report.json'))['measures']; \
	  print('code %.2f%%  functions %s/%s  data %.2f%%' % (m.get('matched_code_percent', 0), \
	  m.get('matched_functions', 0), m.get('total_functions', 0), \
	  m.get('matched_data_percent', 0)))"

# Download the compilers and objdiff, and set up the Python environment.
tools:
	git submodule update --init
	uv venv -q --allow-existing .venv
	uv pip install -q --python $(PYTHON) -r requirements.txt
	mkdir -p tools/bin
	curl -sL -o $(OBJDIFF) https://github.com/encounter/objdiff/releases/download/$(OBJDIFF_VER)/objdiff-cli-$(OBJDIFF_PLATFORM)
	chmod +x $(OBJDIFF)
	for v in 2.7.2-psx 2.8.1-psx; do mkdir -p tools/cc/$$v && \
	  curl -sL https://github.com/decompals/old-gcc/releases/download/$(OLD_GCC_VER)/gcc-$$v$(OLD_GCC_SUFFIX).tar.gz \
	  | tar xz -C tools/cc/$$v; done
	cmp -s tools/gcc-nascar98.patch tools/cc/2.7.2-psx-nascar98/nascar98.patch \
	  || sh tools/build_cc.sh
	cat tools/gcc-nascar98.patch tools/gcc-sdk.patch \
	  | cmp -s - tools/cc/2.7.2-psx-nascar98-sdk/nascar98.patch \
	  || sh tools/build_cc.sh sdk

clean:
	rm -rf build

distclean: clean
	rm -rf asm expected objdiff.json
