#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#
# Included from DlmBuild.mak
# Specifies the default include dir list for DLM building and some global defines
# Suitable for WCDMA targets
#

# Change this for use with "ARM as a Pipe"
#UAFLAGS += -predefine "NO_APLP SETL {FALSE}"
UAFLAGS += -predefine "NO_APLP SETL {TRUE}"

GLOBAL_INC_PATHS  =  \
  /aplp/cotulla/inc \
  /aplp/cp/src/DP \
  /os/osa/inc \
  /diag/diag_logic/inc \
  /diag/diag_logic/src \
  /os/nu_xscale/inc \
  /os/nu_xscale/src \
  /softutil/transport/inc \
  /softutil/transport/src \
  /softutil/tester/inc  \
  /hop/uart/inc  \
  /hop/uart/src  \
  /hop/core/inc \
  /hop/gpio/inc \
  /hop/ipc/inc \
  /hop/intc/inc \
  /hop/timer/inc \
  /handset_mgr/process_mgr/inc \
  /aplp/BSP/inc \
  /env/win32/inc \
  /arbel/p_arbel/inc

GLOBAL_DEF = \
   -DENV_XSCALE \
   -DPLATFORM_CP \
   -DPLATFORM_COTULLA \
   -DOSA_NUCLEUS \
   -DOS_OSA


