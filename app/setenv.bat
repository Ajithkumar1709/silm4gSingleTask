::Note
::MUST excute build_all.bat in DS-5 env. 

::Turn off the echo from this line
@echo off

set TARGET_CATALOGUE_CURR=%cd%

set COMPILE_TOOL_PATH=%TARGET_CATALOGUE_CURR%/
set GCC_INSTALL_PATH=%M_COMP_TOOL_P%/gcc-arm-none-eabi/bin
set CMAKE_PATH=%M_COMP_TOOL_P%/cmake-3.28.0-rc4-windows-x86_64/bin
set MINGW_PATH=%M_COMP_TOOL_P%/MinGW/bin

set SOFT_WORKDIR=%cd:\=/%
set path=%GCC_INSTALL_PATH%;%TARGET_CATALOGUE_CURR%;%MINGW_PATH%;%path%;%CMAKE_PATH%;
set APP_LDNAME_GCC=appld.ld
set APP_LDNAME_ARMCC=scatter.scat

set CC_PATH=%GCC_INSTALL_PATH%/
set CC=arm-none-eabi-gcc.exe
set CXX=arm-none-eabi-g++.exe
set LD=arm-none-eabi-ld.exe
set FROMELF=arm-none-eabi-objcopy.exe
set AR=arm-none-eabi-ar.exe
set RANLIB=arm-none-eabi-ranlib.exe
set cmake_debug=OFF
set cmake_makefile_debug=OFF
set COMP_TYPE=GCC
set LZMA=%M_COMP_TOOL_P%/lzma_asr.exe

cmake -G "MinGW Makefiles" -B ./build -DCONFIG_CMAKE_DEBUG=%cmake_debug% -DCMAKE_TOOLCHAIN_FILE="scripts/env.cmake" -DTOOLCHAIN_PREFIX=%M_COMP_TOOL_P%/gcc-arm-none-eabi -DCMAKE_VERBOSE_MAKEFILE=%cmake_makefile_debug% -DCOMP_TYPE=%COMP_TYPE% -DLZMA=%LZMA%


