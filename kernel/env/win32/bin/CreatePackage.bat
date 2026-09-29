@rem ------------------------------------------------------------
@rem (C) Copyright [2006-2008] Marvell International Ltd.
@rem All Rights Reserved
@rem ------------------------------------------------------------

@echo off
rem ==============================================================================
rem  File Name      : CreatePackage.bat
rem  Description    : Perl script to generate package directory structure. 
rem  
rem  Notes          : This script creates the required directories and
rem                   template files for a new package.  The scripts can
rem                   be 'ClearCase' aware and create the directory elements
rem                   if desired.
rem 
rem  Usage          : CreatePackage [-?|h] [-r <root>] [<base>/<pack>]
rem                   -r      Package root directory. This defaults to /vobs on
rem                           unix systems and / on win32 systems. The package
rem 		                   root directory can also be defined via the
rem 		                   CBA_ROOT environment variable.
rem                   -?      This help.
rem                   <base>  Package base directory name of where to create
rem                           the package. The base name is optional if the user
rem                           is currently in a package base directory. 
rem                   <pack>  Name of the package to create.
rem  
rem  Copyright (c) 2001 Intel of Canada, All Rights Reserved
rem ==============================================================================

perl %CBA_ROOT%\env\scripts\CreatePackage.pl %1 %2 %3