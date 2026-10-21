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
# psyq-3.6 is the Psy-Q 3.6 CC1PSX.EXE (GNU C 2.7.2.SN.1), the retail
# compiler. It's a DOS program that tools/cc1-psyq36.sh runs in DOSBox-X.
# Any other CC_VER names an old-gcc build in tools/cc/, for experiments.
# See "Retail compiler" in kb/psx/toolchain.md.
CC_VER    ?= psyq-3.6
ASPSX_VER ?= 2.34
GP_SIZE   ?= 8
CC_DIR := tools/cc/$(CC_VER)
CPP    := $(firstword $(wildcard $(CC_DIR)/cpp) tools/cc/2.7.2-psx/cpp)
CC1    := $(if $(filter psyq-3.6,$(CC_VER)),tools/cc1-psyq36.sh,$(CC_DIR)/cc1)
# 2.7.2-psx-nascar98 is GCC 2.7.2 with tools/gcc-nascar98.patch, a native
# stand-in that emits the same assembly as the retail compiler at
# -mcpu=r4000. `make standin` builds it. The permuter and RTL dumps (-da) use it; `make check`
# doesn't. See "Fast stand-in" in kb/psx/toolchain.md.
MCPU   := $(if $(filter 2.7.2-psx-nascar98,$(CC_VER)),r4000,3000)
ifneq ($(filter check expected,$(MAKECMDGOALS)),)
ifneq ($(CC_VER),psyq-3.6)
$(error make check runs only on the retail compiler: unset CC_VER)
endif
endif
MASPSX := $(PYTHON) tools/maspsx_extern.py --aspsx-version=$(ASPSX_VER) -G$(GP_SIZE) --dont-force-G0 --expand-div

CPPFLAGS := -Iinclude -Ibuild -undef -Wall -lang-c -nostdinc \
            -D__GNUC__=2 -D__OPTIMIZE__ -Dmips -D__mips__ -D__mips -Dpsx \
            -D__psx__ -D__psx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C
# Psy-Q's default CPU is the R3000; -mips1 is the PSX instruction set.
CFLAGS   := -O2 -G$(GP_SIZE) -mcpu=$(MCPU) -mips1 -mgas -msoft-float -fgnu-linker -quiet -w
ASFLAGS  := -EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -Iinclude
LDFLAGS  := -nostdlib --no-check-sections -T $(LD_SCRIPT) \
            -T build/undefined_syms_auto.txt -T build/undefined_funcs_auto.txt \
            -T build/fixed_addrs.ld \
            --defsym=D_800A2F68Small=D_800A2F68 \
            --defsym=D_800A2E60Absolute=D_800A2E60 \
            --defsym=D_800A2EA8Absolute=D_800A2EA8 \
            --defsym=D_800A2EF4Absolute=D_800A2EF4 \
            --defsym=D_800A35A4Absolute=D_800A35A4 \
            --defsym=D_800A35E0Absolute=D_800A35E0 \
            --defsym=D_800A372CAbsolute=D_800A372C \
            --defsym=D_800A3910Absolute=D_800A3910 \
            --defsym=D_800A2F9CAbsolute=D_800A2F9C \
            --defsym=D_800A2E6CAbsolute=D_800A2E6C \
            --defsym=D_800A2F50Absolute=D_800A2F50 \
            --defsym=D_800A2F50Absolute2=D_800A2F50 \
            --defsym=D_800A3678Absolute=D_800A3678 \
            --defsym=D_800A3654Absolute=D_800A3654 \
            --defsym=D_800A367CAbsolute=D_800A367C \
            --defsym=D_800A39C8Absolute=D_800A39C8 \
            --defsym=gPrimitiveCursorAbsolute=gPrimitiveCursor \
            --defsym=D_800A3570Absolute=D_800A3570 \
            --defsym=D_800A2F94Absolute=D_800A2F94 \
            --defsym=D_800A3A04Absolute=D_800A3A04 \
            --defsym=D_800A3A38Absolute=D_800A3A38 \
            --defsym=D_800A3848Absolute=D_800A3848 \
            --defsym=D_800A3574Absolute=D_800A3574 \
            --defsym=D_800A3A2CAbsolute2=D_800A3A2C \
            --defsym=D_800A3A34Absolute2=D_800A3A34 \
            --defsym=D_800A2F2CAbsolute=D_800A2F2C \
            --defsym=D_800A3378Small=D_800A3378 \
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
            --defsym=D_800A3694Absolute=D_800A3694 \
            --defsym=D_800A2EACSmall=D_800A2EAC \
            --defsym=D_800A2EACAbsolute=D_800A2EAC \
            --defsym=D_800A2EC0Absolute=D_800A2EC0 \
            --defsym=D_800A2EB0Absolute=D_800A2EB0 \
            --defsym=D_800A2E24Absolute=D_800A2E24 \
            --defsym=D_800A331CAbsolute=D_800A331C \
            --defsym=D_800A3320Absolute=D_800A3320 \
            --defsym=D_800A3668Absolute=D_800A3668 \
            --defsym=D_800A2E84Absolute=D_800A2E84 \
            --defsym=D_800A39A4Absolute=D_800A39A4 \
            --defsym=D_800A3A40Absolute=D_800A3A40 \
            --defsym=gStandingsNameXAbsolute=gStandingsNameX \
            --defsym=D_800A3A8CAbsolute=D_800A3A8C \
            --defsym=D_800A2EA0Small=D_800A2EA0 \
            --defsym=D_800A2EA4Absolute=D_800A2EA4 \
            --defsym=D_800A2EC8Small=D_800A2EC8 \
            --defsym=D_800A2EC8Absolute=D_800A2EC8 \
            --defsym=D_800A3A54Small=D_800A3A54 \
            --defsym=gOrderingTableBankSmall=gOrderingTableBank \
            --defsym=gOrderingTableBankAbsolute=gOrderingTableBank \
            --defsym=D_800A384CAbsolute=D_800A384C \
            --defsym=D_800A3854Absolute=D_800A3854 \
            --defsym=D_800A36D0Absolute=D_800A36D0 \
            --defsym=D_800A36D4Absolute=D_800A36D4 \
            --defsym=D_800A3784Absolute=D_800A3784 \
            --defsym=D_800A3790Absolute=D_800A3790 \
            --defsym=D_800A3794Absolute=D_800A3794 \
            --defsym=D_800A3798Absolute=D_800A3798 \
            --defsym=D_800A379CAbsolute=D_800A379C \
            --defsym=D_800A37A4Absolute=D_800A37A4 \
            --defsym=D_800A37ACAbsolute=D_800A37AC \
            --defsym=D_800A37B4Absolute=D_800A37B4 \
            --defsym=D_800A37C4Absolute=D_800A37C4 \
            --defsym=D_800A36C0Absolute=D_800A36C0 \
            --defsym=D_800A36E8Absolute=D_800A36E8 \
            --defsym=D_800A2DF0Absolute=D_800A2DF0 \
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
            --defsym=D_800A39E4Absolute2=D_800A39E4 \
            --defsym=D_800A26E0Read=D_800A26E0 \
            --defsym=D_800A26E0Write=D_800A26E0 \
            --defsym=D_800B9DDERead=D_800B9DDE \
            --defsym=D_800B9DDEWrite=D_800B9DDE \
            --defsym=D_800A20B4Read=D_800A20B4 \
            --defsym=D_800A20B4Write=D_800A20B4 \
            --defsym=D_800B9C80Start=D_800B9C80 \
            --defsym=D_800B9C80Loop=D_800B9C80 \
            --defsym=D_800AD3D7Read=D_800AD3D7 \
            --defsym=D_800AD3D7Write=D_800AD3D7 \
            --defsym=D_800AD3C0Write=D_800AD3C0 \
            --defsym=D_800A20B8Read=D_800A20B8 \
            --defsym=D_800A26A0Read=D_800A26A0 \
            --defsym=D_800A26A0Write=D_800A26A0 \
            --defsym=D_800A20B0Read=D_800A20B0 \
            --defsym=D_800A20B0Write=D_800A20B0 \
            --defsym=D_800A20ACRead=D_800A20AC \
            --defsym=D_800A20ACWrite=D_800A20AC \
            --defsym=D_800A20B2Read=D_800A20B2 \
            --defsym=D_800A20B2Write=D_800A20B2 \
            --defsym=gProgramAttrsRead=D_800B9928 \
            --defsym=gSpuRegisterBuffer=D_800AD224 \
            --defsym=D_800A2710Init=D_800A2710 \
            --defsym=D_800A2248Init=D_800A2248 \
            --defsym=D_800A224CInit=D_800A224C \
            --defsym=D_800A2258Init=D_800A2258 \
            --defsym=D_800A225CInit=D_800A225C \
            --defsym=D_800A225EInit=D_800A225E \
            --defsym=D_800A2260Init=D_800A2260 \
            --defsym=D_800A2264Init=D_800A2264 \
            --defsym=D_800A2250Init=D_800A2250 \
            --defsym=D_800A2244Init=D_800A2244 \
            --defsym=D_800A26C4Init=D_800A26C4 \
            --defsym=D_800A229CInit=D_800A229C \
            --defsym=D_800A26F8FiDMA=D_800A26F8 \
            --defsym=D_800A26ACFiDMA=D_800A26AC \
            --defsym=D_800A26E0FiDMARead=D_800A26E0 \
            --defsym=D_800A26E0FiDMAWrite=D_800A26E0 \
            --defsym=gSpuRegisters=D_800A26AC \
            --defsym=D_800A26C0r=D_800A26C0 \
            --defsym=D_800A26B0r=D_800A26B0 \
            --defsym=D_800A26B4r=D_800A26B4 \
            --defsym=D_800A26B8r=D_800A26B8 \
            --defsym=D_800A26F8r=D_800A26F8 \
            --defsym=D_800A26ACReverbA=D_800A26AC \
            --defsym=D_800A26ACIRQ=D_800A26AC \
            --defsym=D_800A26ACReverbAttr2=D_800A26AC \
            --defsym=gDispPrintfRead1=D_8009DA8C \
            --defsym=gDispPrintfRead2=D_8009DA8C \
            --defsym=gDispPrintfRead3=D_8009DA8C \
            --defsym=gDispPrintfRead4=D_8009DA8C \
            --defsym=D_800A26ACInitRegs=D_800A26AC \
            --defsym=D_800A26BCInitPtr=D_800A26BC \
            --defsym=D_800A26A4Init=D_800A26A4 \
            --defsym=D_800A26C8Init=D_800A26C8 \
            --defsym=D_800A26A8Init=D_800A26A8 \
            --defsym=D_800A26CCInit=D_800A26CC \
            --defsym=D_800A26D0Init=D_800A26D0 \
            --defsym=D_800A26D4Init=D_800A26D4 \
            --defsym=D_800A26D8Init=D_800A26D8 \
            --defsym=D_800A26E8Init=D_800A26E8 \
            --defsym=D_80090B38Init=D_80090B38 \
            --defsym=D_80090B48Init=D_80090B48 \
            --defsym=_spu_keystat=D_800A229C \
            --defsym=CD_cbsync=D_8009BA7C \
            --defsym=_spu_RXX=D_800A26AC \
            --defsym=_spu_tsa=D_800A26A8 \
            --defsym=_spu_transDir=D_800A26F8 \
            --defsym=_spu_dmaAddr=D_800A26B0 \
            --defsym=_spu_dmaSize=D_800A26B4 \
            --defsym=_spu_dmaCtrl=D_800A26B8 \
            --defsym=_spu_delayCtrl=D_800A26C0 \
            --defsym=_spu_xferAddr=D_800A26FC \
            --defsym=_spu_xferBlocks=D_800A2700 \
            --defsym=_snd_openflag=D_800B9DC0 \
            --defsym=_snd_ev_flag=D_800B2090 \
            --defsym=_snd_seq_s_max=D_800BE724 \
            --defsym=_snd_seq_t_max=D_800BE728 \
            --defsym=VBLANK_MINUS=D_800BDE2C \
            --defsym=_svm_rattr=D_800AE27C \
            --defsym=_svm_vab_used=D_800B9DE4 \
            --defsym=_svm_vh=D_800B9930 \
            --defsym=_svm_stereo_mono=D_800B1EA4 \
            --defsym=_svm_orev1=D_800AD9A8 \
            --defsym=_svm_orev2=D_800AD9AC \
            --defsym=_svm_vcf=D_800B9DBC \
            --defsym=_svm_vab_count=D_800BE8EC \
            --defsym=_ss_spu_vm_rec=D_800AD8E4 \
            --defsym=kMaxPrograms=D_800B60A0 \
            --defsym=_svm_auto_kof_mode=D_800BA044 \
            --defsym=_svm_envx_idx=D_800AD89C \
            --defsym=_svm_vab_vh=D_800AFAD8 \
            --defsym=_svm_vab_pg=D_800AFA98 \
            --defsym=_svm_vab_tn=D_800AFD9C \
            --defsym=_svm_vab_total=D_800BE8AC \
            --defsym=_svm_vab_start=D_800BE8F0 \
            --defsym=_svm_brr_start_addr=D_800BE930 \
            --defsym=Intr=D_8009BD58 \
            --defsym=CD_resultSync=D_800A8CB8 \
            --defsym=CD_resultReady=D_800A8CC0 \
            --defsym=CD_resultC=D_800A8CC8 \
            --defsym=Alarm=D_800A8CD0 \
            --defsym=CD_cbready=D_8009BA80 \
            --defsym=CD_debug=D_8009BA88 \
            --defsym=CD_status=D_8009BA8C \
            --defsym=CD_status1=D_8009BA90 \
            --defsym=CD_nopen=D_8009BA94 \
            --defsym=CD_pos=D_8009BA98 \
            --defsym=CD_mode=D_8009BA9C \
            --defsym=CD_com=D_8009BA9D \
            --defsym=CD_comstr=D_8009BAA0 \
            --defsym=CD_intrstr=D_8009BB20 \
            --defsym=CD_cmdAck=D_8009BB40 \
            --defsym=CD_cmdStat=D_8009BC40 \
            --defsym=CD_cmdParams=D_8009BBC0 \
            --defsym=CD_cmdPos=D_8009BCC0 \
            --defsym=libcd_CDRegister0=D_8009BD40 \
            --defsym=libcd_CDRegister1=D_8009BD44 \
            --defsym=libcd_CDRegister2=D_8009BD48 \
            --defsym=libcd_CDRegister3=D_8009BD4C \
            --defsym=CD_comDelay=D_8009BD50 \
            --defsym=CD_info=D_8009BD5C \
            --defsym=CD_dmaChcr=D_8009BD84 \
            --defsym=CD_spu=D_8009BD54 \
            --defsym=CD_dmaDelay=D_8009BD74 \
            --defsym=CD_dpcr=D_8009BD78 \
            --defsym=CD_dmaMadr=D_8009BD7C \
            --defsym=CD_dmaBcr=D_8009BD80 \
            --defsym=CD_ReadCallbackFunc=D_8009BD88 \
            --defsym=CD_read=D_8009BD8C \
            --defsym=_spu_rev_attr=D_800A2258-4 \
            --defsym=_spu_rev_startaddr=D_800A2710 \
            --defsym=_spu_rev_param=D_800A2760 \
            --defsym=_spu_timeout=D_800A26A4 \
            --defsym=VSync_gpuStat=D_8009BDB8 \
            --defsym=VSync_rcnt=D_8009BDBC \
            --defsym=Hcount=D_8009BDC0 \
            --defsym=prevVcount=D_8009BDC4 \
            --defsym=Vcount=D_8009CE84 \
            --defsym=mdec1=D_800A2CD8 \
            --defsym=d0_chcr=D_800A2CAC \
            --defsym=d1_chcr=D_800A2CB8 \
            --defsym=d0_madr=D_800A2CA4 \
            --defsym=d1_madr=D_800A2CB0 \
            --defsym=_strtokLast=D_800A2B98 \
            --defsym=gGpu=D_8009DA88 \
            --defsym=GPU_printf=D_8009DA8C \
            --defsym=gGfx=D_8009DA90 \
            --defsym=gfxMaxW=D_8009DA94 \
            --defsym=gfxMaxH=D_8009DA96 \
            --defsym=GPU_DATA=D_8009DB60 \
            --defsym=GPU_STATUS=D_8009DB64 \
            --defsym=DMA2_MADR=D_8009DB68 \
            --defsym=DMA2_BCR=D_8009DB6C \
            --defsym=DMA2_CHCR=D_8009DB70 \
            --defsym=DMA6_MADR=D_8009DB74 \
            --defsym=DMA6_BCR=D_8009DB78 \
            --defsym=DMA6_CHCR=D_8009DB7C \
            --defsym=DPCR=D_8009DB80 \
            --defsym=gpuClrBuf=D_800AD0E4 \
            --defsym=gpuQueue=D_800BC54C \
            --defsym=gpuLast=D_8009DB84 \
            --defsym=_qin=D_8009DB94 \
            --defsym=_qout=D_8009DB98 \
            --defsym=gpuSavedMask2=D_8009DBA0 \
            --defsym=gpuSavedMask=D_8009DBA4 \
            --defsym=gpuAlarmEnd=D_8009DBA8 \
            --defsym=gpuAlarmCount=D_8009DBAC \
            --defsym=gpuCtlBuf=D_800AD124 \
            --defsym=Font=D_8009CEB8 \
            --defsym=fntCountX=D_8009D038 \
            --defsym=fntBase=D_8009DA40 \
            --defsym=fntText=D_800A8CDC \
            --defsym=fntSprt=D_800A90DC \
            --defsym=fntTpage=D_800AD0DC \
            --defsym=fntClut=D_800AD0E0 \
            --defsym=_svm_cur=D_800B9DC4 \
            --defsym=spuVmMaxVoice=D_800B9C80 \
            --defsym=_svm_spuBase=D_800A20B8 \
            --defsym=_svm_okon1=D_800AD96C \
            --defsym=_svm_okon2=D_800AD970 \
            --defsym=_svm_okof1=D_800BEB98 \
            --defsym=_svm_okof2=D_800BEB9C \
            --defsym=_svm_voice=D_800AD3BC \
            --defsym=_svm_envx_hist=D_800AD8A0 \
            --defsym=_svm_sreg_buf=D_800AD224 \
            --defsym=_svm_sreg_dirty=D_800AD3A4 \
            --defsym=_svm_pg=D_800B9928 \
            --defsym=_svm_tn=D_800B9950 \
            --defsym=_svm_damper=D_800AFD98 \
            --defsym=_spu_inTransfer=D_800A26DC \
            --defsym=_spu_transferCallback=D_800A26E0 \
            --defsym=_spu_IRQCallback=D_800A26E4 \
            --defsym=_spu_AllocBlockNum=D_800A2704 \
            --defsym=_spu_AllocLastNum=D_800A2708 \
            --defsym=_spu_rev_flag=D_800A2248 \
            --defsym=intrEnv=D_8009BDC8 \
            --defsym=i_mask=D_8009CE54 \
            --defsym=g_InterruptMask=D_8009CE58 \
            --defsym=d_pcr=D_8009CE5C \
            --defsym=dicr=D_8009CE8C \
            --defsym=dmaBase=D_8009CEB0 \
            --defsym=pCallbacks=D_8009CE50 \
            --defsym=intrTimeout=D_8009CE60 \
            --defsym=_spu_rev_reserve_wa=D_800A224C \
            --defsym=_spu_rev_offsetaddr=D_800A2250 \
            --defsym=_spu_mem_mode_plus=D_800A26D0 \
            --defsym=_spu_mem_mode_unitM=D_800A26D8 \
            --defsym=_spu_memList=D_800A270C \
            --defsym=D_800A26ACVA=D_800A26AC \
            --defsym=D_800A2710Clear=D_800A2710 \
            --defsym=D_800A2298Clear=D_800A2298 \
            --defsym=D_800A22A0Clear=D_800A22A0 \
            --defsym=D_800A26D0Clear0=D_800A26D0 \
            --defsym=D_800A26D0Clear2=D_800A26D0 \
            --defsym=D_800A26C4ClearRead=D_800A26C4 \
            --defsym=D_800A26C4ClearWrite=D_800A26C4 \
            --defsym=D_800A26E0ClearCheck=D_800A26E0 \
            --defsym=D_800A26E0ClearSave=D_800A26E0 \
            --defsym=D_800A26E0ClearWrite=D_800A26E0 \
            --defsym=D_800A26E0ClearRestore=D_800A26E0 \
            --defsym=D_800A26ACCommon2=D_800A26AC \
            --defsym=D_800A2CE0.NON_MATCHING=D_800A2CE0 \
            --defsym=D_800A2CFC.NON_MATCHING=D_800A2CFC \
            --defsym=D_800A2D0C.NON_MATCHING=D_800A2D0C \
            --defsym=D_800A2D0E.NON_MATCHING=D_800A2D0E \
            --defsym=D_800A2D0F.NON_MATCHING=D_800A2D0F \
            --defsym=D_800A2D14.NON_MATCHING=D_800A2D14 \
            --defsym=D_800A2D18.NON_MATCHING=D_800A2D18 \
            --defsym=D_800A2D1C.NON_MATCHING=D_800A2D1C \
            --defsym=D_800A2DC4.NON_MATCHING=D_800A2DC4 \
            --defsym=D_800A2DCC.NON_MATCHING=D_800A2DCC \
            --defsym=D_800A2DD0.NON_MATCHING=D_800A2DD0 \
            --defsym=D_800A2DD4.NON_MATCHING=D_800A2DD4 \
            --defsym=D_800A2DD8.NON_MATCHING=D_800A2DD8 \
            --defsym=D_800A2DDC.NON_MATCHING=D_800A2DDC \
            --defsym=D_800A2DE0.NON_MATCHING=D_800A2DE0 \
            --defsym=D_800A2DE1.NON_MATCHING=D_800A2DE1 \
            --defsym=D_800A2DE4.NON_MATCHING=D_800A2DE4 \
            --defsym=D_800A2DE8.NON_MATCHING=D_800A2DE8 \
            --defsym=D_800A2DEC.NON_MATCHING=D_800A2DEC \
            --defsym=D_800A2DF0.NON_MATCHING=D_800A2DF0 \
            --defsym=D_800A2DF4.NON_MATCHING=D_800A2DF4 \
            --defsym=D_800A2E44.NON_MATCHING=D_800A2E44 \
            --defsym=D_800A2E48.NON_MATCHING=D_800A2E48 \
            --defsym=D_800A2E7C.NON_MATCHING=D_800A2E7C \
            --defsym=D_800A2E80.NON_MATCHING=D_800A2E80 \
            --defsym=D_800A2E90.NON_MATCHING=D_800A2E90 \
            --defsym=D_800A2E94.NON_MATCHING=D_800A2E94 \
            --defsym=D_800A2EA4.NON_MATCHING=D_800A2EA4 \
            --defsym=D_800A2EA8.NON_MATCHING=D_800A2EA8 \
            --defsym=D_800A2EAC.NON_MATCHING=D_800A2EAC \
            --defsym=D_800A2EB0.NON_MATCHING=D_800A2EB0 \
            --defsym=D_800A2EB8.NON_MATCHING=D_800A2EB8 \
            --defsym=D_800A2EC0.NON_MATCHING=D_800A2EC0 \
            --defsym=D_800A2EC4.NON_MATCHING=D_800A2EC4 \
            --defsym=D_800A2EC8.NON_MATCHING=D_800A2EC8 \
            --defsym=D_800A2ECC.NON_MATCHING=D_800A2ECC \
            --defsym=D_800A2ED0.NON_MATCHING=D_800A2ED0 \
            --defsym=D_800A2ED4.NON_MATCHING=D_800A2ED4 \
            --defsym=D_800A2ED8.NON_MATCHING=D_800A2ED8 \
            --defsym=D_800A2EDA.NON_MATCHING=D_800A2EDA \
            --defsym=D_800A2EDB.NON_MATCHING=D_800A2EDB \
            --defsym=D_800A2EDC.NON_MATCHING=D_800A2EDC \
            --defsym=D_800A2EE0.NON_MATCHING=D_800A2EE0 \
            --defsym=D_800A2EE4.NON_MATCHING=D_800A2EE4 \
            --defsym=D_800A2EFC.NON_MATCHING=D_800A2EFC \
            --defsym=D_800A2F00.NON_MATCHING=D_800A2F00 \
            --defsym=D_800A2F08.NON_MATCHING=D_800A2F08 \
            --defsym=D_800A2F30.NON_MATCHING=D_800A2F30 \
            --defsym=D_800A2F38.NON_MATCHING=D_800A2F38 \
            --defsym=D_800A2F54.NON_MATCHING=D_800A2F54 \
            --defsym=D_800A2F84.NON_MATCHING=D_800A2F84 \
            --defsym=D_800A2F94.NON_MATCHING=D_800A2F94 \
            --defsym=D_800A2F95.NON_MATCHING=D_800A2F95 \
            --defsym=D_800A2F9C.NON_MATCHING=D_800A2F9C \
            --defsym=D_800A2F9D.NON_MATCHING=D_800A2F9D \
            --defsym=D_800A2FA4.NON_MATCHING=D_800A2FA4 \
            --defsym=D_800A3020.NON_MATCHING=D_800A3020 \
            --defsym=D_800A305A.NON_MATCHING=D_800A305A \
            --defsym=D_800A305B.NON_MATCHING=D_800A305B \
            --defsym=D_800A3064.NON_MATCHING=D_800A3064 \
            --defsym=D_800A3065.NON_MATCHING=D_800A3065 \
            --defsym=D_800A3068.NON_MATCHING=D_800A3068 \
            --defsym=D_800A3069.NON_MATCHING=D_800A3069 \
            --defsym=D_800A306C.NON_MATCHING=D_800A306C \
            --defsym=D_800A306D.NON_MATCHING=D_800A306D \
            --defsym=D_800A306E.NON_MATCHING=D_800A306E \
            --defsym=D_800A306F.NON_MATCHING=D_800A306F \
            --defsym=D_800A3070.NON_MATCHING=D_800A3070 \
            --defsym=D_800A3071.NON_MATCHING=D_800A3071 \
            --defsym=D_800A3072.NON_MATCHING=D_800A3072 \
            --defsym=D_800A3073.NON_MATCHING=D_800A3073 \
            --defsym=D_800A3074.NON_MATCHING=D_800A3074 \
            --defsym=D_800A3078.NON_MATCHING=D_800A3078 \
            --defsym=D_800A307C.NON_MATCHING=D_800A307C \
            --defsym=D_800A308C.NON_MATCHING=D_800A308C \
            --defsym=gOrderingTableBank.NON_MATCHING=gOrderingTableBank \
            --defsym=func_800A2CE0=D_800A2CE0 \
            --defsym=D_800A3384=D_800A3380+4 \
            --defsym=D_800A2FEC=D_800A2FE8+4 \
            --defsym=D_800A338C=D_800A3388+4


# Addressing aliases for func_80023454.
LDFLAGS += \
            --defsym=D_800A2D0CAbsolute=D_800A2D0C \
            --defsym=D_800A2E94Absolute=D_800A2E94 \
            --defsym=D_800A2EB4Absolute=D_800A2EB4 \
            --defsym=D_800A2EC4Absolute=D_800A2EC4 \
            --defsym=D_800A2ECCAbsolute=D_800A2ECC \
            --defsym=D_800A2ED0Absolute=D_800A2ED0 \
            --defsym=D_800A2ED4Absolute=D_800A2ED4 \
            --defsym=D_800A2F95Absolute=D_800A2F95 \
            --defsym=D_800A2FC8Absolute=D_800A2FC8 \
            --defsym=D_800A306CAbsolute=D_800A306C \
            --defsym=D_800A306DAbsolute=D_800A306D \
            --defsym=D_800A3554Absolute=D_800A3554 \
            --defsym=D_800A3590Absolute=D_800A3590 \
            --defsym=D_800A35A8Absolute=D_800A35A8 \
            --defsym=D_800A3614Absolute=D_800A3614 \
            --defsym=D_800A3694Absolute2=D_800A3694 \
            --defsym=D_800A3696Absolute=D_800A3696 \
            --defsym=D_800A3696Absolute2=D_800A3696 \
            --defsym=D_800A36FCAbsolute=D_800A36FC \
            --defsym=D_800A3700Absolute=D_800A3700 \
            --defsym=D_800A380CAbsolute=D_800A380C \
            --defsym=D_800A3878Absolute=D_800A3878 \
            --defsym=D_800A3924Absolute=D_800A3924 \
            --defsym=D_800A3644Absolute=D_800A3644 \
            --defsym=D_800A36E0Absolute=D_800A36E0 \
            --defsym=D_800A36E1Absolute=D_800A36E1 \
            --defsym=D_800A3A94Absolute=D_800A3A94

# src/globals.c owns the former .sdata range. splat emits no .sdata
# collection for c subsegments, so compile with -G0: every literal lands
# in .data, and the linker script places globals.c.o(.data) — the last
# .data entry — exactly where sdata began (0x800A2CE0 = main_DATA_END,
# which is _gp). gp-relative references from other files are unchanged.
build/src/globals.c.o: CFLAGS := $(subst -G$(GP_SIZE),-G0,$(CFLAGS))

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

# SDK C (src/psxsdk/) uses the game flags above. The Psy-Q libraries came
# from GNU C 2.6.3, not the game's 2.7.2.SN.1: see "SDK compiler" in
# kb/psx/toolchain.md. tools/cc1-263.sh runs it (Docker off x86 Linux).
SDK_O_FILES := $(filter build/src/psxsdk/%,$(O_FILES))
$(SDK_O_FILES): CC1 := tools/cc1-263.sh
$(SDK_O_FILES): tools/cc1-263.sh

# The Psy-Q libraries reach no global through $gp (the SDK range of the
# retail EXE has no gp-relative access), so they came from -G0. Compile
# them the same way: a plain `extern` scalar then loads with lui/lw.
$(SDK_O_FILES): CFLAGS := $(subst -G$(GP_SIZE),-G0,$(CFLAGS))

OBJDIFF := tools/bin/objdiff-cli
OBJDIFF_VER := v3.8.2
OLD_GCC_VER := 0.17
PSYQ36_URL  := https://github.com/mkst/esa/releases/download/psyq-binaries/psyq3.6.tar.gz
PSYQ36_EXE  := tools/cc/psyq-3.6/CC1PSX.EXE
PSYQ36_SHA1 := 6da49839dd22aa2f3aea678b46447bad7a16859a

.PHONY: all check extract split expected report format tools standin clean distclean
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

build/fixed_addrs.ld: config/symbol_addrs.txt tools/fixed_addrs.py
	@mkdir -p build
	$(PYTHON) tools/fixed_addrs.py --ld $< > $@

build/%.c.o: %.c $(LD_SCRIPT) build/fixed_addrs.h
	@mkdir -p $(@D)
	set -o pipefail; $(CPP) $(CPPFLAGS) $< | $(CC1) $(CFLAGS) | $(MASPSX) | $(AS) $(ASFLAGS) -G$(GP_SIZE) -o $@

build/%.s.o: %.s $(LD_SCRIPT)
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) -G0 -o $@ $<

$(ELF): $(O_FILES) $(LD_SCRIPT) build/fixed_addrs.ld
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
	clang-format -i $(C_FILES) include/common.h include/game.h include/include_asm.h

report: objdiff.json $(EXE)
	@test -d expected || $(MAKE) expected
	$(OBJDIFF) report generate -o build/report.json
	@python3 -c "import json; m=json.load(open('build/report.json'))['measures']; \
	  print('code %.2f%%  functions %s/%s  data %.2f%%' % (m.get('matched_code_percent', 0), \
	  m.get('matched_functions', 0), m.get('total_functions', 0), \
	  m.get('matched_data_percent', 0)))"

# The Psy-Q 3.6 compiler is a Sony DOS program: download it, never commit it.
$(PSYQ36_EXE):
	mkdir -p $(@D)
	curl -sL $(PSYQ36_URL) | tar xz -C $(@D) --strip-components=1 psyq3.6/CC1PSX.EXE
	echo "$(PSYQ36_SHA1)  $@" | shasum -c - || { rm -f $@; exit 1; }

# Build the instrumentable stand-in compiler for permute.py and RTL dumps.
# make check doesn't use it. Rebuilds when tools/gcc-nascar98.patch changes.
standin:
	cmp -s tools/gcc-nascar98.patch tools/cc/2.7.2-psx-nascar98/nascar98.patch \
	  || sh tools/build_cc.sh

# Download the compilers and objdiff, and set up the Python environment.
tools: $(PSYQ36_EXE)
	@command -v dosbox-x >/dev/null 2>&1 || echo "Install DOSBox-X to run the Psy-Q compiler: brew install --cask dosbox-x, or apt install dosbox-x (Ubuntu 24.04, Debian 13)."
	git submodule update --init
	uv venv -q --allow-existing .venv
	uv pip install -q --python $(PYTHON) -r requirements.txt
	mkdir -p tools/bin
	curl -sL -o $(OBJDIFF) https://github.com/encounter/objdiff/releases/download/$(OBJDIFF_VER)/objdiff-cli-$(OBJDIFF_PLATFORM)
	chmod +x $(OBJDIFF)
	for v in 2.7.2-psx 2.8.1-psx; do mkdir -p tools/cc/$$v && \
	  curl -sL https://github.com/decompals/old-gcc/releases/download/$(OLD_GCC_VER)/gcc-$$v$(OLD_GCC_SUFFIX).tar.gz \
	  | tar xz -C tools/cc/$$v; done
	mkdir -p tools/cc/2.6.3-psx && \
	  curl -sL https://github.com/decompals/old-gcc/releases/download/$(OLD_GCC_VER)/gcc-2.6.3-psx.tar.gz \
	  | tar xz -C tools/cc/2.6.3-psx

clean:
	rm -rf build

distclean: clean
	rm -rf asm expected objdiff.json

# Absolute scalar loads for model geometry scales.
LDFLAGS += --defsym=D_800A353CAbsolute=D_800A353C \
           --defsym=D_800A3758Absolute=D_800A3758
