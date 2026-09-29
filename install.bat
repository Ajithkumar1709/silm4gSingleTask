
@echo off

set CURR_DIR=%cd%
set M_COMP_TOOL_P=%CURR_DIR%\cross_tool\win32
set DS5_PATCH=%M_COMP_TOOL_P%\DS-5v5.26.2
set RESULT_STR=Success
set ARMLMD_LICENSE_FILE=%DS5_PATCH%\license.dat


if not exist %M_COMP_TOOL_P%\patcher.exe (
   set RESULT_STR=patcher is not exist
   goto exit:
)

echo *****************************************
echo install DS5
%M_COMP_TOOL_P%\patcher.exe --dir %M_COMP_TOOL_P%\DS-5v5.26.2 -c
%M_COMP_TOOL_P%\patcher.exe --license=ARM_DS_5 %M_COMP_TOOL_P%\DS-5v5.26.2 > nul
echo *****************************************

echo check env
%DS5_PATCH%\sw\ARMCompiler5.06u4\bin\armcc --vsn

SETLOCAL ENABLEDELAYEDEXPANSION
for /f "delims=" %%i in ('%DS5_PATCH%\sw\ARMCompiler5.06u4\bin\armcc --vsn') do (set ret=!ret!%%i;)
echo !ret! | findstr /C:"Software supplied by" >nul || ( ENDLOCAL & set RESULT_STR=armcc install error & goto exit)
ENDLOCAL


echo *****************************************
echo check perl
echo %M_COMP_TOOL_P%\perl\bin\perl    -v
echo *****************************************

echo *****************************************
echo check gnu
echo %M_COMP_TOOL_P%\gnumake -v
echo *****************************************



:exit

echo ***************************************************
echo                %RESULT_STR%
echo ***************************************************