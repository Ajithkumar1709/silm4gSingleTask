#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#
# Included from DlmBuild.mak
# Specifies the default include dir list for DLM building and some global defines
# Suitable for WCDMA targets
# NOTE: change the lines marked BVD: ... in order to compile a DLM to be run on Bulverde
#

# Change this for use with "ARM as a Pipe"
#UAFLAGS += -predefine "NO_APLP SETL {FALSE}"
UAFLAGS += -predefine "NO_APLP SETL {TRUE}"

# Define HARBELL configuration as default - REQUIRES MANUAL CHANGE TO USE ON BOERNE OR OTHER PLATFORMS
# Only required in case the JumpTable is dependent on the platform switches
#UAFLAGS += -predefine "_TAVOR_HARBELL_ SETL {TRUE}"
#UAFLAGS += -predefine "_TAVOR_BOERNE_ SETL {TRUE}"
#UAFLAGS += -predefine "_SILICON_TTC_ SETL {TRUE}"
UAFLAGS += -predefine "SILICON_PV2 SETL {TRUE}"
UAFLAGS += -predefine "SILICON_SEAGULL SETL {TRUE}"

GLOBAL_INC_PATHS  =  \
  /csw/platform/inc \
  /csw/platform/dev_plat/inc \
  /aplp/plw/inc \
  /gplc/gplc/inc \
  /os/osa/inc \
  /diag/diag_logic/inc \
  /diag/diag_logic/src \
  /os/nu_xscale/inc \
  /os/nu_xscale/src \
  /crd/IPC/inc \
  /hal/UART/inc  \
  /hal/UART/src  \
  /hal/CORE/inc \
  /hop/core/inc \
  /hop/gpio/inc \
  /hop/intc/inc \
  /hop/timer/inc \
  /env/win32/inc \
  /csw/PM/inc  \
  /softutil/tickmanager/inc

ifneq  (,$(findstring SILICON_SEAGULL,${VARIANT_LIST}))
GLOBAL_INC_PATHS  +=  \
  /hop/pm/inc \
  /csw/SysCfg/inc
endif

# Define HARBELL configuration as default - REQUIRES MANUAL CHANGE TO USE ON BOERNE OR OTHER PLATFORMS
#Only required in case public API's used by a DLM  are dependent on the platform switches
GLOBAL_DEF = \
   -DENV_XSCALE \
   -DSILICON_PV2 \
   -DSILICON_SEAGULL
#  -D_TAVOR_HARBELL_


#Uncomment for Hermon 2CHIP & BVD
#GLOBAL_DEF += \
#   -D"NO_APLP=1" \
#   -DINTEL_2CHIP_PLAT \
#   -DMSL_INCLUDE \
#   -DMSL_POOL_MEM

#Uncomment for Hermon 2CHIP
#GLOBAL_DEF += \
#   -DHERMON_MCP2_CFG  \
#   -DHERMON_MCP2_CONFIGURATION

#Uncomment for BVD
#GLOBAL_DEF += \
#   -DINTEL_2CHIP_PLAT_BVD  \
#   -DGENERIC_MSL_CLIENT_INCLUDE  \
#   -DDISABLE_NVRAM_ACCESS

#Uncomment for BOERNE
#GLOBAL_DEF = \
#   -DENV_XSCALE \
#   -D_TAVOR_BOERNE_

#Uncomment for TTC
#GLOBAL_DEF = \
#   -DENV_XSCALE \
#   -DSILICON_TTC


