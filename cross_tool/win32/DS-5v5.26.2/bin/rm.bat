@echo off

rem Copyright (C) 2013 ARM Ltd. All rights reserved
rem
rem This batch file is to provide compatability with the Eclipse CDT managed builder
rem which expects to use the 'rm' command to delete files. It is not an rm implementation
rem for Windows.
rem
rem If an 'rm' command is found on the PATH then this script delegates to that command
rem otherwise the DS-5 clean.exe will be used to delete files.
rem

setlocal ENABLEDELAYEDEXPANSION

set COMMAND=
for %%e in (%PATHEXT%) do (
  for %%X in (rm%%e) do (
    if not defined COMMAND (
      if /i not "%%~$PATH:X"=="%~f0" (
        set COMMAND=%%~$PATH:X
      )
    )
  )
)

if not defined COMMAND (
  set COMMAND=%~dp0clean
)

"%COMMAND%" %*
