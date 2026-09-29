@rem ------------------------------------------------------------
@rem (C) Copyright [2006-2008] Marvell International Ltd.
@rem All Rights Reserved
@rem ------------------------------------------------------------

@echo off
rem ==============================================================================
rem  File Name      : CreateGroup.bat
rem  Description    : Perl script to generate group directory structure. 
rem  
rem  Notes          : This script creates the required directories and
rem                   template files for a new group.  The scripts can
rem                   be 'ClearCase' aware and create the directory elements
rem                   if desired.
rem 
rem  Usage          : Creategroup [-?|h] [-r <root>] [<base>/<group>]
rem                   -r      Group root directory. This defaults to /vobs on
rem                           unix systems and / on win32 systems. The group
rem 		                  root directory can also be defined via the
rem 		                  CBA_ROOT environment variable.
rem                   -?      This help.
rem                   <base>  Group base directory name of where to create
rem                           the group. The base name is optional if the user
rem                           is currently in a group base directory. 
rem                   <group> Name of the group to create.
rem  
rem  Copyright (c) 2001 Intel of Canada, All Rights Reserved
rem ==============================================================================

perl %CBA_ROOT%\env\scripts\CreateGroup.pl %1 %2 %3