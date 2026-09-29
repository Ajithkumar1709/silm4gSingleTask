@echo off

setlocal
set /p DS_REV=<"%~dp0\..\sw\info\rev.txt"
@echo Environment configured for ARM DS-5 (build %DS_REV%)
@echo Please consult the documentation for available commands and more details
@echo.
endlocal

if not exist "%APPDATA%\ARM\com.arm.ds.toolchain.default" (
	@echo WARNING: No compiler toolchain specified for environment
	goto:message
)

set /p TC_NAME=<"%APPDATA%\ARM\com.arm.ds.toolchain.default"

if "%TC_NAME%" == "" (
	@echo WARNING: No compiler toolchain specified for environment
	goto:message
)

for /f "delims=" %%a in ('%~sdp0..\sw\tcm\get_toolchain_path.bat "%TC_NAME%"') do set TC_PATH=%%a
set PATH=%TC_PATH%;%PATH%
@echo Environment configured for %TC_NAME%
set TC_NAME=
set TC_PATH=

:message
@echo.
@echo You can change the compiler toolchain for this environment at any time by
@echo running the 'select_toolchain' command. A default for all future environments
@echo can be set  with the 'select_default_toolchain' command.
@echo.

@echo on
