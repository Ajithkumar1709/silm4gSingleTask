# ============================================================================
# File        : ^FILE
# Programmer  : ^PROGRAMMER
# Description :	Make file for building the test-target of the ^GROUP_BASE/^GROUP 
#               group under the ^ENV environment.
# Create Date : ^DATE
#
# Notes       : This file is used to test the ^GROUP group under the ^ENV environment.  
#               The ENV macro and the HOST macros require definition.
#               This make file generates ^GROUP_BASE_^GROUP.lib
#               in the ^GROUP_BASE/^GROUP/test/obj directory.
#               
# Copyright ^YEAR, Intel Corporation, All rights reserved.
# ============================================================================

HOST = ^HOST
ENV  = ^ENV

# setup the root build directory. On win32 systems
# the vobs mount at the root of the mapped drive. 
ifeq ($(HOST),unix)
 BUILD_ROOT = /vobs
else
 BUILD_ROOT = $(CBA_ROOT)
endif

# get the environment macros and paths.
include $(BUILD_ROOT)/env/$(HOST)/build/$(ENV)_env.mak

ifeq ($(RUN_BUGFIXER),$(empty))
RUN_BUGFIXER	= 1
endif
ifeq ($(USE_FILEIO),$(empty))
USE_FILEIO		= 0
endif
ifeq ($(strip $(USE_FILEIO)),1)
FILEIO_DFLAG	= -DUSE_FILEIO
endif


ifeq ($(_USE_PTIMER_),1)
USE_PTIMER_DFLAG = -D_USE_PTIMER_
USE_PTIMER_VARIANT = _USE_PTIMER_
else
USE_PTIMER_DFLAG =
USE_PTIMER_VARIANT =
endif

#parse options of building executable for flash
ifneq ($(USE_FLASH),$(empty))
BL_SOURCE = BootLoad.asm
BL_CRT_DFLAG = -DNO_GS_DATA_INIT_CRT0 -DNO_ZERO_MEMORY_CRT0
ifeq ($(USE_FLASH),NO_SCRAMBLING)
BL_CRT_DFLAG += -DNO_SCRAMBLING
endif
endif

#parse options of zeroing memory
ifneq ($(NO_ZERO_MEMORY),$(empty))
ifneq ($(USE_FLASH),$(empty))
BL_CRT_DFLAG += -DNO_ZERO_MEMORY_BOOTLOAD
else
BL_CRT_DFLAG = -DNO_ZERO_MEMORY_CRT0
endif
endif

# Target Build Paths -------------------------------------------------

TARGET_NAME = ^GROUP_^ENV
TARGET_BASE = ^GROUP_BASE
TARGET_PATH = $(BUILD_ROOT)/$(TARGET_BASE)/^GROUP/test

# The path locations of source and include file directories.
LOCAL_SRC_PATH  = $(TARGET_PATH)/src
LOCAL_INC_PATHS = $(TARGET_PATH)/src $(TARGET_PATH)/inc $(TARGET_PATH)/bin $(BUILD_ROOT)/cfw/Inc

# Global-Static Data copier part - don't modify
ifeq ($(USE_FLASH),$(empty))
ROM_DATA_NAME		= ROMData
ROM_DATA_SRC		= $(TARGET_PATH)/bin/$(ROM_DATA_NAME).h
TEMP_TARGET_NAME	= $(TARGET_NAME)PreLink
ROM_DATA_SRC_CFILE	= $(ROM_DATA_NAME).c
endif

# Default target variant ---------------------------------------------
ifeq ($(TARGET_VARIANT),$(empty))

#HW platform
HW_PLATFORM = ^UP_HW_PLATFORM

# Variant dependant flags
ifneq ($(HW_PLATFORM),$(empty))
HW_PLATFORM_DFLAG	= -D$(HW_PLATFORM)
endif

# local target source files, paths not required
LOCAL_SRC_FILES = $(ROM_DATA_SRC_CFILE) $(BL_SOURCE) crt0.asm UserMain.c

# local header files for preprocessing, paths not required
LOCAL_HP_FILES = 

TARGET_LINK_FILE = $(TARGET_NAME).ldf
TARGET_MAP_FILE =  $(TARGET_NAME).map

# Source directory of the include global source (crt0 and ROM Data copier)
GLOBAL_SOURCES_PATH = $(BUILD_ROOT)/cfw/Src

# local target build flags for source files
# contained in this target directory
LOCAL_ASMFLAGS =
LOCAL_CFLAGS   =
LOCAL_CPPFLAGS =
LOCAL_DFLAGS   = $(BL_CRT_DFLAG)
GSDEXTARCT_FLAGS =
TARGET_SCFLAGS = -keep-locals -hexdump 

# global target build flags to be passed 
# to groups and packages.
GLOBAL_INC_PATHS= $(BUILD_ROOT)/cfw/Inc ^PROJECT_INC_DIR
TARGET_ASMFLAGS = -g
TARGET_CFLAGS   = -O -g
TARGET_CPPFLAGS =
TARGET_DFLAGS   = $(FILEIO_DFLAG) $(HW_PLATFORM_DFLAG) $(USE_PTIMER_DFLAG)
TARGET_LDFLAGS  = -Map $(TARGET_PATH)\bin\$(TARGET_MAP_FILE) -T $(LOCAL_SRC_PATH)\$(TARGET_LINK_FILE) $(subst -D,-MD,$(TARGET_DFLAGS) $(LOCAL_DFLAGS))
TARGET_ARFLAGS  =
BUGFIXER_FLAGS  = --all-fixes

# the packages and groups to be included in the target
# syntax is <basename>/<package> and <basename>/<group>
PACKAGE_LIST = 
GROUP_LIST   = ^GROUP_BASE/^GROUP

# package and group variants required for this target variant
# syntax is <PACKAGE>_<VARIANT> or <GROUP>_<VARIANT>.
VARIANT_LIST = ^UP_HW_PLATFORM

# TRACE_LIST contains package and groups in which diagnostics/tracing
# will be compiled. Not compiling diagnostics/tracing in some modules
# will reduce code size and increase code performance.
TRACE_LIST = $(PACKAGE_LIST) $(GROUP_LIST)

endif

# Variant_1 target variant -------------------------------------------
ifeq ($(TARGET_VARIANT),^UP_HW_PLATFORM_PROTO)

#HW platform
HW_PLATFORM = ^UP_HW_PLATFORM_PROTO

# Variant dependant flags
ifneq ($(HW_PLATFORM),$(empty))
HW_PLATFORM_DFLAG	= -D$(HW_PLATFORM)
endif

# local target source files, paths not required
LOCAL_SRC_FILES = $(ROM_DATA_SRC_CFILE) $(BL_SOURCE) crt0.asm UserMain.c

# local header files for preprocessing, paths not required
LOCAL_HP_FILES = 

TARGET_LINK_FILE = $(TARGET_NAME).ldf
TARGET_MAP_FILE =  $(TARGET_NAME).map

# Source directory of the include global source (crt0 and ROM Data copier)
GLOBAL_SOURCES_PATH = $(BUILD_ROOT)/cfw/Src

# local target build flags are for source files
# contained in this target directory
LOCAL_ASMFLAGS =
LOCAL_CFLAGS   =
LOCAL_CPPFLAGS =
LOCAL_DFLAGS   =$(BL_CRT_DFLAG)
GSDEXTARCT_FLAGS =
TARGET_SCFLAGS = -keep-locals -hexdump 

# global target build flags to be passed 
# to groups and packages.
GLOBAL_INC_PATHS= $(BUILD_ROOT)/cfw/Inc ^PROJECT_INC_DIR
TARGET_ASMFLAGS = -g
TARGET_CFLAGS   = -O -g
TARGET_CPPFLAGS =
TARGET_DFLAGS   = $(FILEIO_DFLAG) $(HW_PLATFORM_DFLAG) $(USE_PTIMER_DFLAG)
TARGET_LDFLAGS  = -Map $(TARGET_PATH)\bin\$(TARGET_MAP_FILE) -T $(LOCAL_SRC_PATH)\$(TARGET_LINK_FILE) $(subst -D,-MD,$(TARGET_DFLAGS) $(LOCAL_DFLAGS))
TARGET_ARFLAGS  =
BUGFIXER_FLAGS  = --all-fixes

# the packages and groups to be included in the target
# syntax is <basename>/<package> and <basename>/<group>
PACKAGE_LIST = 
GROUP_LIST   = ^GROUP_BASE/^GROUP

# package and group variants required for this target variant
# syntax is <PACKAGE>_<VARIANT> or <GROUP>_<VARIANT>.
VARIANT_LIST = ^UP_HW_PLATFORM_PROTO

# TRACE_LIST contains package and groups in which diagnostics/tracing
# will be compiled. Not compiling diagnostics/tracing in some modules
# will reduce code size and increase code performance.
TRACE_LIST = $(PACKAGE_LIST) $(GROUP_LIST)

endif

# Additional source paths (for global sources files)
vpath %.c     $(GLOBAL_SOURCES_PATH)
vpath %.asm   $(GLOBAL_SOURCES_PATH)

# include the standard target make file -------------------------------
include $(BUILD_ROOT)/env/$(HOST)/build/target.mak

# If you need to specify explicit rules for some target, do it here.
# For example, explicit rule for object file:
# There is no need to specify header files in list of dependencies, since clearmake knows about them anyway.
# $(GROUP_OBJ_PATH)/MyFile.doj: MyFile.c
#	$(CC) $(strip $(CFLAGS) $(DFLAGS) $(IFLAGS) $< -o $@)
# ifeq ($(strip $(RUN_BUGFIXER)),1)
#	$(BugFixer) --inp-file $@ $(BUGFIXER_FLAGS)
# endif  





