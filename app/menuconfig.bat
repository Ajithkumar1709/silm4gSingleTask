@echo off

set ROOT_PATH=.
set KCONFIG_FILE=%ROOT_PATH%\config\Kconfig
set MENUCONFIG_PATH=%ROOT_PATH%\config\menuconfig
set TARGET_PATH=%MENUCONFIG_PATH%\target
set KCONFIG_CONFIG=%TARGET_PATH%\target.config
set KCONFIG_TRISTATE=%TARGET_PATH%\target.tristate
set KCONFIG_AUTOCONFIG=%TARGET_PATH%\target.config.mk
set KCONFIG_AUTOHEADER=%TARGET_PATH%\target.config.h
set HEADER_=MBTK_

del %KCONFIG_TRISTATE%
del %KCONFIG_AUTOCONFIG%
del %KCONFIG_AUTOHEADER%

call %MENUCONFIG_PATH%\mconf.exe %KCONFIG_FILE%

call %MENUCONFIG_PATH%\conf.exe --silentoldconfig %KCONFIG_FILE%
