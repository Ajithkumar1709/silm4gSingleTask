@echo off

set MAP_EXE=%1
set RELASE_DIR=%2

for /f "delims=" %%a in ('dir /a-d /s /b %RELASE_DIR%\*.map') do (
set MAP_FILE=%%~nxa
)

%MAP_EXE% "START"

for /f "tokens=2,* delims= " %%i in ('findstr /c:"Execution Region" %RELASE_DIR%\%MAP_FILE%') do (
set VALUE_LIST=%%~j
@call :paser_line
)
%MAP_EXE% "END"

exit /b 0

:paser_line
@rem echo %VALUE_LIST%
%MAP_EXE% "%VALUE_LIST%"
