#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CreatePackage.pl
# Description    : Perl script to generate package directory structure. 
# 
# Notes          : This script creates the required directories and
#                  template files for a new package.  The scripts can
#                  be 'ClearCase' aware and create the directory elements
#                  if desired.
#
# Usage          : CreatePackage [-?|h] [-r <root>] [<vob>/<pack>]
#                  -r      Package root directory. This defaults to /vobs on
#                          unix systems and / on win32 systems. The package
#		                   root directory can also be defined via the
#		                   CBA_ROOT environment variable.
#                  -?      This help.
#                  <vob>   Package ClearCase VOB name of where to create
#                          the package. 
#                  <pack>  Name of the package to create.
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

use FindBin qw($Bin);
use lib "$Bin/modules";

use strict;

# standard modules
use Tk;
use locale;
use Getopt::Long;
use File::Basename;
use File::Path;
use Cwd;
use File::Spec;

# local modules
use CbaGuiName;
use CbaGuiClearCase;
use CbaGuiCheckList;
use CbaGuiRadioList;
use CbaPackage;
use CbaClearCase;

# script sub-routines
sub createPackage;
sub usage;

# what system are we on ?
my $Host = $^O eq "MSWin32" ? "win32" : "unix";

# get the command line arguments -----------------------------------------
my %options = ();
GetOptions(\%options, "d", "r=s", "h|?"); 

my $DEBUG = 0;
$DEBUG = 1 if $options{'d'};

# help switch
die usage() if ($options{'h'});

# set the default directories 
my $MSWin32RootDir = $ENV{'CBA_ROOT'} || "";
my $UnixRootDir    = $ENV{'CBA_ROOT'} || "/vobs";
my $DefaultRootDir = $^O eq "MSWin32" ? $MSWin32RootDir : $UnixRootDir;
my $RootDir =  $options{'r'} || $DefaultRootDir;
my $TemplateDir = $RootDir."/env/templates";

# Build the GUI ----------------------------------------------------------

# GUI variables
my $packageBaseName;
my $packageName;
my $ccFlag = 0;
my $lvcoFlag = 1;
my @envList = ("msa", "xscale", "arm", "gnu",);
my $platformVar = "River";
my @platformList = ($platformVar, "Manitoba", "Hermon", "Threepoint", );
my @ifList = ("API", "config",);

# main window geometry
my $mainWinHeight = 600;
my $mainWinWidth  = 330;
my $mainWinResize = 1;
my $mainWinBorder = 20;

# create the main window
my $mw = MainWindow->new();
$mw->title("CreatePackage");
$mw->geometry("$mainWinWidth"."x"."$mainWinHeight");
$mw->resizable($mainWinResize, $mainWinResize);

# create the package name widget
my $packageWidget = $mw->CbaGuiName(-nameVar => \$packageName,
				    -baseVar => \$packageBaseName,
				    -width  => ($mainWinWidth - $mainWinBorder),
				    )->pack;
# create the ClearCase widget
my $ccWidget = $mw->CbaGuiClearCase(-ccFlagVar   => \$ccFlag,
				    -lvcoFlagVar   => \$lvcoFlag,
				    -width       => ($mainWinWidth - $mainWinBorder),
				    )->pack;

# create the test env widget
my $testEnvWidget = $mw->CbaGuiCheckList(-title   => "Test Platform",
					 -width   => ($mainWinWidth - $mainWinBorder),
					 -checkList => \@envList,
					 )->pack();

# create the interface widget
my $interfaceWidget = $mw->CbaGuiCheckList(-title   => "Interface",
					   -width   => ($mainWinWidth - $mainWinBorder),
					   -checkList => \@ifList,
					   )->pack();

my $testPlatWidget = $mw->CbaGuiRadioList(-title   => "HW Platform",
                     -entry   => 1,
					 -width   => ($mainWinWidth - $mainWinBorder),
#					 -height  => (60),
					 -radioList => \@platformList,
					 -variable => \$platformVar,
					 )->pack();

# button geometry
my $buttonWidth      = 6;
my $buttonCancelXpos = $mainWinWidth - 80; 
my $buttonCancelYpos = $mainWinHeight - 40; 
my $buttonOkXpos     = $buttonCancelXpos - 80; 
my $buttonOkYpos     = $buttonCancelYpos;

# place the OK and cancel buttons
$mw->Button(-text    => "Cancel",
	    -command => sub { exit },
	    -width   => $buttonWidth)->place(-x => $buttonCancelXpos, -y => $buttonCancelYpos);
$mw->Button(-text    => "Ok",
	    -command => sub { createPackage;  $mw->destroy; },
	    -width   => $buttonWidth)->place(-x => $buttonOkXpos, -y => $buttonOkYpos);

# run the GUI ...
MainLoop;


# -----------------------------------------------------------------------------
# Function    : createPackage
# Description : Creates the package elements
# Parms       : none
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub createPackage
{
    # turn on the debugging for the modules
#    setCbaPackageDebug(1);
#    setCbaClearCaseDebug(1);
    
    my $packagePath = "$RootDir/$packageBaseName/$packageName";
    
    # create the directories and return the dir list
    my @dirs = ();
    createPackageDirTree(\@dirs, $packagePath, $ccFlag);
    
    # create the interface files
    my @srcList = createPackageInterfaceFiles(\@ifList, $TemplateDir, $packagePath, $ccFlag, $lvcoFlag);
    
    # create the test environment files
    createPackageTestEnvFiles(\@envList, $platformVar, $TemplateDir, $packagePath, $ccFlag, $lvcoFlag);
    
    # create the package make files
    createPackageMakeFiles(\@srcList, $platformVar, $TemplateDir, $packagePath, $ccFlag, $lvcoFlag);
    
    # checkin the directories if using ClearCase
    checkinDirs(\@dirs) if (!$lvcoFlag);
    
}

# -----------------------------------------------------------------------------
# Function    : usage
# Description : Writes the usage string
# Parms       : none
# Returns     : none
# Notes       : writes to stdout
# -----------------------------------------------------------------------------
sub usage
{
    # define the help string
    my @usage = (
		 "usage: CreatePackage [-?|h] [-r <root>] [<vob>/<pack>]\n",
		 "\n",
		 "       -r        Package root directory. This defaults to /vobs on\n",
		 "                 unix systems and \\ on win32 systems. The package\n",
		 "                 root directory can also be defined via the\n",
		 "                 CBA_ROOT environment variable.\n",
		 "       -?        This help.\n",
		 "       <base>    Package ClearCase VOB name of where to create\n",
		 "                 the package.\n",
		 "       <pack>    Name of the package to create.\n");
    
    # write to stdout
    print "@usage\n";
    exit;
}
