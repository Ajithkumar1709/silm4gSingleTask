@rem ------------------------------------------------------------
@rem (C) Copyright Mobiletek Ltd.
@rem All Rights Reserved
@rem ------------------------------------------------------------

@echo off

set TARGET_CATALOGUE=%cd%
set TARGET_DEV=%TARGET_CATALOGUE:~0,2%


set M_COMP_TOOL_P=%TARGET_CATALOGUE%\cross_tool\win32
set DS5_PATCH=%M_COMP_TOOL_P%\DS-5v5.26.2
set ZIP_TOOL=%M_COMP_TOOL_P%\unzip.exe
set Perl_PATH=%M_COMP_TOOL_P%\Perl
set RESULT_STR=Success
set ARMLMD_LICENSE_FILE=%DS5_PATCH%\license.dat
set MIGWIN=%M_COMP_TOOL_P%\MinGW

if not exist %DS5_PATCH% (

  echo ********************************************************
  echo ******* install compile tools,please wait...  **********
  echo ********************************************************
  %ZIP_TOOL% -o %M_COMP_TOOL_P%\compile.zip -d %M_COMP_TOOL_P%\  > nul
  if not exist %DS5_PATCH% (
    set RESULT_STR=unpack compile tools error
    goto exit
  )  
)

if not exist %MIGWIN% (

  echo ********************************************************
  echo ******* install compile_app tools,please wait...  **********
  echo ********************************************************
  %ZIP_TOOL% -o %M_COMP_TOOL_P%\compile_app.zip -d %M_COMP_TOOL_P%\  > nul
  if not exist %DS5_PATCH% (
    set RESULT_STR=unpack compile tools error
    goto exit
  )  
)


echo %PATH% | findstr /C:"%DS5_PATCH%" >nul && goto exit


set PATH=%DS5_PATCH%\sw\ARMCompiler5.06u4\bin;%M_COMP_TOOL_P%;%Perl_PATH%\site\bin;%Perl_PATH%\bin;%M_COMP_TOOL_P%\python;%PATH%
echo CURRENT PATH:
path





:exit

echo ***************************************************
echo                %RESULT_STR%
echo ***************************************************