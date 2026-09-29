
@echo off


if "%1" == "packrule" (echo pack only 
				   set XROOT=.\
)


if "%CUSTOMER_NAME%" neq "COMMON" (
set ARELEASE_CATALOGUE=%XROOT%\OUTPUT_%TARGET_PROJECT%_%CUSTOMER_NAME%
set ARELEASE_IMAGES=%XROOT%\releasepack\%TARGET_PROJECT%_%CUSTOMER_NAME%\images
set ARELEASEPACK=%XROOT%\releasepack\%TARGET_PROJECT%_%CUSTOMER_NAME%
) else (
set ARELEASE_CATALOGUE=%XROOT%\OUTPUT_%TARGET_PROJECT%
set ARELEASE_IMAGES=%XROOT%\releasepack\%TARGET_PROJECT%\images
set ARELEASEPACK=%XROOT%\releasepack\%TARGET_PROJECT%
)

if defined LIB_SUFFIX (
set ARELEASE_CATALOGUE=%ARELEASE_CATALOGUE%_%LIB_SUFFIX%
set ARELEASE_IMAGES=%XROOT%\releasepack\%TARGET_PROJECT%_%CUSTOMER_NAME%_%LIB_SUFFIX%\images
set ARELEASEPACK=%ARELEASEPACK%_%LIB_SUFFIX%
) 


set ARELEASE=%XROOT%\releasepack\arelease.exe
set MBTK_MAPEXE=%XROOT%\releasepack\Ram_map.exe

set ZIP_FILE=%ARELEASE_CATALOGUE%\%ASR_PROJECT_NAME%_%ASR_PRODUCT_TYPE%.zip
set DYNAMICS_RESOURCE_CMD=
if "%MBTK_TTS_GEN_TYPE%" == "FLASH" (
set DYNAMICS_RESOURCE_CMD=%DYNAMICS_RESOURCE_CMD% -i tts_source=%ARELEASE_IMAGES%\tts\%MBTK_TTS_LAN_TYPE%\tts_source.bin
)

for /f "delims=" %%a in ('dir /a-d /s /b .\%ARELEASE_CATALOGUE%\%TARGET_PROJECT%@*_compressed.bin') do (
set COMPRESSED_BIN_NAME=%%~nxa
set DYNAMICS_RESOURCE_CMD=%DYNAMICS_RESOURCE_CMD% -i cp2=%ARELEASE_CATALOGUE%\%%~nxa
goto :next
)

:next
for /f "delims=" %%a in ('dir /a-d /s /b .\%ARELEASE_CATALOGUE%\%TARGET_PROJECT%@*.bin') do (
set BIN_NAME=%%~nxa
set DYNAMICS_RESOURCE_CMD=%DYNAMICS_RESOURCE_CMD% -i cp=%ARELEASE_CATALOGUE%\%%~nxa
goto :break
)

set BUILD_ERR=%TARGET_PROJECT%@*.bin NOT EXIST
goto :build_end

:break
echo COMPRESSED_BIN_NAME %COMPRESSED_BIN_NAME%
echo BIN_NAME %BIN_NAME%
echo DYNAMICS_RESOURCE_CMD=%DYNAMICS_RESOURCE_CMD%

setlocal enabledelayedexpansion 
set /a j=0
if exist %ARELEASE% (

	echo **************************************************************************************
	echo ***********************  generate    zip      **********************
		:n_name
		if defined RELEASE_PROFILE_LIST[!j!] (
			if exist %ARELEASE_CATALOGUE% (
				::set BUILD_ERR=BUILD_ERR_NONE
				 %ARELEASE% -c %ARELEASEPACK% -g -p !RELEASE_PROFILE_LIST[%j%]! -v %ASR_PRODUCT_TYPE%^
				 %DYNAMICS_RESOURCE_CMD%^
				 -i dsp=%ARELEASE_IMAGES%\dsp.bin^
				 -i rfbin=%ARELEASE_IMAGES%\rf.bin^
				 -i boot33=%ARELEASE_IMAGES%\boot33.bin^
				 -i apn=%ARELEASE_IMAGES%\apn.bin^
				 %ARELEASE_CATALOGUE%\!RELEASE_PROFILE_LIST[%j%]!_%ASR_PRODUCT_TYPE%.zip
			) else (
				set BUILD_ERR=%ARELEASE_CATALOGUE% NOT EXIST
				goto build_end
			)
			
		set /a j=!j!+1
		goto n_name
	)
	echo ********************************finish********************************	
) else (
	set BUILD_ERR=arelease NOT EXIST
	goto build_end
)

:build_end