::Turn off the echo from this line
@echo off

set TARGET_CATALOGUE_CURR=%cd%

if "%1%" == "clean" (
    rd /s /Q .\build > nul
    rd /s /Q .\release > nul
    goto END
)

cd ..\
call compile_tools_init.bat
cd %TARGET_CATALOGUE_CURR%


set SOFT_WORKDIR=%cd:\=/%
set path=%CD%\tools\;%path%

::create release directory
if not exist release md release

del /s /q /f release\*
::open comment(goto START and goto SUCCESS) to control build specilize boot33*.bin
::goto START

if %errorlevel% == 0 (goto step1) else (goto ERROR)
:step1

call setenv.bat

if %errorlevel% == 0 (goto step2) else (goto ERROR)

:step2

cd build & gnumake
cd ..


::check file exist in release?
if not exist release\user_app.bin goto ERROR

goto SUCCESS

:ERROR
echo ****************************************************************
echo ***********************  ERROR  ********************************
echo ****************************************************************
goto END

:SUCCESS
echo ****************************************************************
echo ***********************  SUCCESS  ******************************
echo ****************************************************************
:END