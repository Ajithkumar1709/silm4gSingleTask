
@echo off

set TARGET_CATALOGUE_CURR=%cd%

cd ..\
call compile_tools_init.bat
cd %TARGET_CATALOGUE_CURR%


set TARGET_CATALOGUE=%cd%
set TARGET_DEV=%TARGET_CATALOGUE:~0,2%
set CP_BIN_DIR=%TARGET_CATALOGUE%\tavor\Arbel\bin
set TARGET_PROJECT_FW=MBTK_PRODUCT_%TARGET_PROJECT%
if "%CUSTOMER_NAME%" neq "COMMON" (
set MBTK_TARGET_PATH=.\mbtk\target\%TARGET_PROJECT%_%CUSTOMER_NAME%
set MBTK_LIB_DIR=\mbtk\lib\%TARGET_PROJECT%_%CUSTOMER_NAME%
) else (
set MBTK_TARGET_PATH=.\mbtk\target\%TARGET_PROJECT%
set MBTK_LIB_DIR=\mbtk\lib\%TARGET_PROJECT%
)
set MBTK_LIB_DIR_COMMON=\mbtk\lib\common
if defined LIB_SUFFIX (
set MBTK_TARGET_PATH=%MBTK_TARGET_PATH%_%LIB_SUFFIX%
set MBTK_LIB_DIR=%MBTK_LIB_DIR%_%LIB_SUFFIX%
)

set BUILD_ERR=NONE

if not defined FRAMEWORK_CONF (
set FRAMEWORK_CONF=bld_mhal_rel_dm.conf
)

if "%1" == "packrule" (
goto :pack
) else ( if /I %1%==cleanrule (
	rem @echo ****** clean find *********
	set PARAM_1=clean
	
		rem @echo *** clean del exist file ****
		rd /s /Q  .\tavor\Arbel\obj_PMD2NONE > nul
		rd /s /Q  .\tavor\Arbel\bin  > nul
		rd /s /Q  .\framework\build  > nul
		rd /s /Q  .\3g_ps\rls  > nul
		del /s /Q .\tavor\Arbel\build\Arbel_PMD2NONE.opt  > nul
		del /s /Q .\tavor\Arbel\build\Arbel_PMD2NONE.track  > nul
		set BUILD_ERR=BUILD_ERR_NONE
		goto build_end
 )
)

call sdk_stub_gen.bat
if not %ERRORLEVEL% == 0 (
set BUILD_ERR=GEN_SDK_STUB_FAILE
goto build_end
)



if exist %MBTK_TARGET_PATH% (
	copy %MBTK_TARGET_PATH%\target.mak .\mbtk\build\mbtk_pro.mak
) else (
	set BUILD_ERR=BUILD_CUSTOM_TARGET_ERROR
	goto build_end
)

rem @echo ******************  create verno.c for build date/time ***********************
set VERNOSRC=.\mbtk\cust_api\verno.c
if exist %VERNOSRC% (
    del %VERNOSRC%
)
set YEAR=%date:~0,4%
set MONTH=%date:~5,2%
set DAY=%date:~8,2%
set HOUR=%time:~0,2%
set MINUTE=%time:~3,2%
set SECOND=%time:~6,2%
if %HOUR% LEQ 9 set HOUR=0%time:~1,1%

set BUILD_DATE_TIME=%YEAR%-%MONTH%-%DAY% %HOUR%:%MINUTE%:%SECOND%
echo %BUILD_DATE_TIME%
@echo char* build_date_time(void) >> %VERNOSRC%
@echo { >> %VERNOSRC%
@echo    static char build_date_time_str[] = "%BUILD_DATE_TIME%"; >> %VERNOSRC%
@echo    return build_date_time_str; >> %VERNOSRC%
@echo } >> %VERNOSRC%
subst X: .
X:

cd tavor\Arbel\build\

echo %COMP_BAT%

call %COMP_BAT% %CUSTOMER_NAME%


set MBTK_MAPEXE=%XROOT%\releasepack\Ram_map.exe
set RELEASEBIN=%XROOT%\tavor\Arbel\bin\


if not %errorlevel% == 0 (
	cd ../../../
	call map_parser.bat %MBTK_MAPEXE% %RELEASEBIN%
	set BUILD_ERR=BUILD_PLATFORM_ERROR
	goto build_end
)


call project_output_open.bat

cd ../../../

:pack
call sdk_releasepack.bat %1



:build_end
if "%BUILD_ERR%"=="NONE" (
call map_parser.bat %MBTK_MAPEXE% %ARELEASE_CATALOGUE%
)

%TARGET_DEV%
cd %TARGET_CATALOGUE%

if NOT "%1" == "packrule" subst X: /d >nul

:build_end
if "%BUILD_ERR%"=="NONE" (
echo ========================
echo build sucessfully !!!!
echo ========================
) else (
echo ========================
echo build fail %BUILD_ERR%
echo ========================


)
