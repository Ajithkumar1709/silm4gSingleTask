@rem ------------------------------------------------------------
@rem (C) Copyright [2006-2008] Marvell International Ltd.
@rem All Rights Reserved
@rem ------------------------------------------------------------

@echo off
rem ==============================================================================
rem  File Name      : CreateTarget.bat
rem  Description    : Perl script to generate target directory structure. 
rem  
rem  Notes          : This script creates the required directories and
rem                   template files for a new target.  The scripts can
rem                   be 'ClearCase' aware and create the directory elements
rem                   if desired.
rem 
rem  Usage          : CreateTarget [-?|h] [-r <root>] [<base>/<target>]
rem                   -r       Target root directory. This defaults to /vobs on
rem                            unix systems and / on win32 systems. The target
rem 		                    root directory can also be defined via the
rem 		                    CBA_ROOT environment variable.
rem                   -?       This help.
rem                   <base>   Target base directory name of where to create
rem                            the target. The base name is optional if the user
rem                            is currently in a target base directory. 
rem                   <target> Name of the target to create.
rem  
rem  Copyright (c) 2001 Intel of Canada, All Rights Reserved
rem ==============================================================================

perl %CBA_ROOT%\env\scripts\CreateTarget.pl %1 %2 %3