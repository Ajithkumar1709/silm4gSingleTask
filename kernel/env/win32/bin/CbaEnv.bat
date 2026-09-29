@rem ------------------------------------------------------------
@rem (C) Copyright [2006-2008] Marvell International Ltd.
@rem All Rights Reserved
@rem ------------------------------------------------------------

@echo off
rem =================================================================
rem  File Name   : CbaEnv.bat
rem  Description : Environmental variables for the Cellular 
rem                Build Architecture Environment
rem  Usage       : CbaEnv -iuq [<cba_base_dir>]
rem =================================================================

set cba_str=Cellular Build Architecture

rem Get the base directory or set the default
if "%2x" == "x" goto switches
set CBA_ROOT=%2

rem Parse Switches ------------------------------------
:switches
if "%1" == "-q" goto query
if "%1" == "-i" goto install
if "%1" == "-u" goto uninstall

:usage
echo usage: CbaEnv -iuq [cba_base_dir]
echo               -i   install.
echo               -u   uninstall.
echo               -q   query current state.
echo     cba_base_dir   Base directory for builds. Set when  
echo                    using snapshot views, dynamic views
echo                    should use the default of \.
goto end

rem Show state ----------------------------------------
:query
if "%CBA_PATH%x" == "x" goto un_msg
goto install_msg

rem Install -------------------------------------------
:install
if not "%CBA_PATH%x" == "x" goto install_msg
set CBA_PATH=%PATH%
set PATH=%CBA_ROOT%\env\win32\bin;%PATH%

:install_msg
echo %cba_str% Environment Installed
goto end

rem Uninstall -----------------------------------------
:uninstall
if "%CBA_PATH%x" == "x" goto un_msg
set PATH=%CBA_PATH%
set CBA_PATH=
set CBA_ROOT=

:un_msg
echo %cba_str% Environment Uninstalled
goto end

rem Cleanup -------------------------------------------
:end
echo CBA_ROOT = %CBA_ROOT%
set cba_str=
