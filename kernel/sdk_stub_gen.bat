@echo off


set MBTK_STUB_API_AS_PATH=%M_COMP_TOOL_P%/gcc-arm-none-eabi/bin
set MBTK_STUB_AS_FLAG= -mcpu=cortex-r4 
set MBTK_STUB_AS= %MBTK_STUB_API_AS_PATH%/arm-none-eabi-as.exe
set MBTK_STUB_NAME=sdk_api_stub
set MBTK_STUB_LOG=1
if "%CUSTOMER_NAME%" neq "COMMON" (
set PROJECT_OUTPUT=%TARGET_CATALOGUE%\OUTPUT_%TARGET_PROJECT%_%CUSTOMER_NAME%
) else (
set PROJECT_OUTPUT=%TARGET_CATALOGUE%\OUTPUT_%TARGET_PROJECT%
)


if defined LIB_SUFFIX (
set PROJECT_OUTPUT=%PROJECT_OUTPUT%_%LIB_SUFFIX%
) 


set MBTK_RELEASE_DIR=%PROJECT_OUTPUT:\=/%
set MBTK_STUB_SDK_GEN_CUST_FILE=gen_api_c.exe

set MBTK_STUB_AS_ARMCC= %DS5_PATCH%\sw\ARMCompiler5.06u4\bin\armasm.exe
set MBTK_STUB_AS_FLAG_ARMCC= --cpu Cortex-R4

if exist %PROJECT_OUTPUT% (
del /f /q %PROJECT_OUTPUT%\*.*
)

if not exist %PROJECT_OUTPUT% (
mkdir %PROJECT_OUTPUT%
)



::这里生成用户自映射接口
set MBTK_STUB_SDK_GEN_PATH_C=%TARGET_CATALOGUE%/mbtk/cust_api
echo ********    gen cust sdk stub ing      *******
cd %MBTK_STUB_SDK_GEN_PATH_C%
call %MBTK_STUB_SDK_GEN_CUST_FILE% %MBTK_STUB_LOG% stub_api_c
if not %ERRORLEVEL% == 0 goto error
rem 编译
%MBTK_STUB_AS% ./%MBTK_STUB_NAME%_c.s %MBTK_STUB_AS_FLAG% -o %MBTK_STUB_NAME%_c.o
%MBTK_STUB_AS_ARMCC% ./%MBTK_STUB_NAME%_c_armcc.s  %MBTK_STUB_AS_FLAG_ARMCC% -o %MBTK_STUB_NAME%_c_armcc.o

del /f /s /q  %MBTK_STUB_NAME%_c.s > nul
del /f /s /q  %MBTK_STUB_NAME%_c_armcc.s > nul
copy  %MBTK_STUB_NAME%_c.o %PROJECT_OUTPUT%\%MBTK_STUB_NAME%_c.o
copy  %MBTK_STUB_NAME%_c_armcc.o %PROJECT_OUTPUT%\%MBTK_STUB_NAME%_c_armcc.o
del /f /s /q  %MBTK_STUB_NAME%_c.o > nul
del /f /s /q  %MBTK_STUB_NAME%_c_armcc.o > nul



cd %TARGET_CATALOGUE%

echo *********************************
echo ***** SDK  GEN  SUCCESS   *******
echo *********************************
exit /b 0

:error
cd %TARGET_CATALOGUE%
echo *********************************
echo ***** SDK  GEN  ERROR     *******
echo *********************************
exit /b 1