@echo off

rem Copyright (C) 2014 ARM Limited. All rights reserved.
rem This script is used to select a toolchain to add to the PATH

if "%~1"=="-h" goto:usage
if "%~1"=="--help" goto:usage
if "%~1"=="/?" goto:usage

@echo Select a toolchain to use in the current environment
@echo.

set TEMP_FILE=%TMP%\dstc-%RANDOM%.tmp

call "%~dp0\..\sw\java\bin\java.exe" -jar "%~dp0\..\sw\eclipse\dropins\plugins\com.arm.ds.toolchains_5.26.2.20161214_123335.jar" select "%TEMP_FILE%"

@echo.

if not exist %TEMP_FILE% (
	@echo No toolchain configured for environment
	goto:exit
)

set /p TC_NAME=<"%TEMP_FILE%"
for /f "delims=" %%a in ('%~sdp0..\sw\tcm\get_toolchain_path.bat "%TC_NAME%"') do set TC_PATH=%%a
set PATH=%TC_PATH%;%PATH%
@echo Environment configured for %TC_NAME%
del "%TEMP_FILE%"
set TC_NAME=
set TC_PATH=

:exit

set TEMP_FILE=

exit /B

:usage
echo Usage: select_toolchain
echo Allows the selection of a compiler toolchain to add to the PATH.
echo.
echo The list of known toolchains will be printed to stdout to allow
echo an interactive selection. Once selected the path to the toolchains
echo binaries is prepended to the PATH environment variable.
echo.
exit /B 0
