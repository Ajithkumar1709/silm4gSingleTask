#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CreateTarget.pl
# Description    : Perl script to generate target directory structure. 
# 
# Notes          : This script creates the required directories and
#                  template files for a new target.  The scripts can
#                  be 'ClearCase' aware and create the directory elements
#                  if desired.
#
# Usage          : CreateTarget [-?|h] [-r <root>] [<base>/<target>]
#                  -r       Target root directory. This defaults to /vobs on
#                           unix systems and / on win32 systems. The target
#		                    root directory can also be defined via the
#		                    CBA_ROOT environment variable.
#                  -?       This help.
#                  <base>   Target base directory name of where to create
#                           the target. 
#                  <target> Name of the target to create.
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

use FindBin qw($Bin);
use lib "$Bin/modules";
use strict;

# standard modules
use Tk;
use Tk::NoteBook;
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
use CbaGuiMemberSelect;
use CbaClearCase;
use CbaTarget;
use CbaGroup;
use CbaPackage;

# script sub-routines
sub createTarget;
sub usage;

# what system are we on ?
my $host = $^O eq "MSWin32" ? "win32" : "unix";

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

# main window geometry
my $mainWinHeight = 550;
my $mainWinWidth  = 620;
my $mainWinResize = 1;
my $mainWinBorder = 20;

# create the main window
my $mw = MainWindow->new();
$mw->title("CreateTarget");
$mw->geometry("$mainWinWidth"."x"."$mainWinHeight");
$mw->resizable($mainWinResize, $mainWinResize);

# add the notebook widget
my $note = $mw->NoteBook();

# Page 1 GUI Variables
my $targetBaseName;
my $targetName;
my $ccFlag = 0;
my $lvcoFlag = 1;

my $envVar = "msa";
my $hostVar = $host;
my $platformVar = "River";

my @envList = ($envVar, "arm", "gnu" , "xscale",);
my @platformList = ($platformVar, "Manitoba", "Hermon", "Threepoint", );
my @hostList = ("win32", "unix",);
my @memList;

# add the target page to the notebook
my $page1 = $note->add("target",
	                   -label => "Target",
	                   );

# Add the Inherit page in the Beta version
# my $page2 = $note->add("inherit",
# 	                   -label => "Inheritance",
# 	                   );

guiTargetPage($page1);

# Add the Inherit page in the Beta version
# guiInheritPage($page2);

# button geometry
my $buttonWidth      = 6;
my $buttonCancelXoff = $mainWinWidth - 70; 
my $buttonOkXoff     = $buttonCancelXoff - 60; 

# place the OK and cancel buttons
my $buttonFrame = $mw->Frame(-height => 40)->pack(-side => 'bottom', -fill => 'both');
$buttonFrame->Button(-text    => "Ok",
	                 -command => sub { createTarget;  $mw->destroy; },
	                 -width   => $buttonWidth)->place(-x => $buttonOkXoff);

$buttonFrame->Button(-text    => "Cancel",
	                 -command => sub { exit },
	                 -width   => $buttonWidth)->place(-x => $buttonCancelXoff);

# run the GUI ...
$note->place(-x => 10, -y => 10);
MainLoop;

# -----------------------------------------------------------------------------
# Function    : guiTargetPage
# Description : 
# Parms       : 
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub guiTargetPage
{
	my ($page) = @_;

    my $leftFrame  = $page->Frame();
    my $rightFrame = $page->Frame();
    my $botFrame   = $page->Frame();
    
    # create the target name widget
    my $targetWidget = $leftFrame->CbaGuiName(-label => "Target",
					    -nameVar => \$targetName,
				        -baseVar => \$targetBaseName,
				        -width  => 250,
#                        -height => 65,
				        )->pack;

    # create the ClearCase widget
    my $ccWidget = $rightFrame->CbaGuiClearCase(-ccFlagVar   => \$ccFlag,
				        -lvcoFlagVar   => \$lvcoFlag,
				        -width       => 320,
#					    -height      => 100,
				        )->pack;

    # create the Environment widget
    my $envWidget = $leftFrame->CbaGuiRadioList(-title => "Platform",
                         -entry   => 1,
					     -width   => 250,
#					     -height  => 110,
					     -radioList => \@envList,
					     -variable  => \$envVar,
				        )->pack;

    # create the Member selection widget
    my $memberWidget =  $rightFrame->CbaGuiMemberSelect(-title => "Member Selection",
                         -listHeight => 16,
                         -width    => 320,
                         -height   => 345,
                         -srcDir   =>  $RootDir,
                         -destList =>  \@memList,
                         )->pack; 


	my $testPlatWidget = $leftFrame->CbaGuiRadioList(-title   => "HW Platform",
                     -entry   => 1,
					 -width   => 250,
#					 -height  => 110,
					 -radioList => \@platformList,
					 -variable => \$platformVar,
					 )->pack();

    # create the Host widget
    my $interfaceWidget = $leftFrame->CbaGuiRadioList(-title   => "Host",
					       -width   => 250,
#					       -height  => 53,
					       -radioList => \@hostList,
					       -variable => \$hostVar,
				        )->pack;

    $leftFrame->pack(-side => 'left');
    $rightFrame->pack(-side => 'right');
}

# -----------------------------------------------------------------------------
# Function    : guiInheritPage
# Description : 
# Parms       : 
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub guiInheritPage
{
    use CbaGuiMember;

	my ($page) = @_;

    my $leftFrame  = $page->Frame();

    # create the Member selection widget
    my $memberWidget =  $leftFrame->CbaGuiMember(-title => "Members",
##                         -width    => 320,
##                         -height   => 240,
                         -srcDir   =>  $RootDir,
                         -memList =>  \@memList,
                         )->pack; 

    $leftFrame->pack(-side => 'left');
}

# -----------------------------------------------------------------------------
# Function    : createTarget
# Description : Creates the target elements
# Parms       : none
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub createTarget
{
    # turn on the debugging for the modules
    setCbaTargetDebug(1);
    setCbaClearCaseDebug(1);
    
    my $targetPath = "$RootDir/$targetBaseName/$targetName";
    
    # create the directories and return the dir list
    my @dirs = ();
    createTargetDirTree(\@dirs, $targetPath, $ccFlag, $lvcoFlag);
    
    # create the global interface files
    createTargetInterfaceFiles(\@memList,$hostVar, $platformVar, $TemplateDir, $targetPath, $ccFlag, $lvcoFlag, $targetBaseName);
    
    # create the target make files
    createTargetMakeFiles(\@memList, $hostVar, $envVar, $platformVar, $TemplateDir, $targetPath, $ccFlag, $lvcoFlag, $targetBaseName);
    
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
		 "usage: CreateTarget [-?|h] [-r <root>] [<base>/<target>]\n",
		 "\n",
		 "       -r        Target root directory. This defaults to /vobs on\n",
		 "                 unix systems and \\ on win32 systems. The target\n",
		 "                 root directory can also be defined via the\n",
		 "                 CBA_ROOT environment variable.\n",
		 "       -?        This help.\n",
		 "       <base>    Target base directory name of where to create\n",
		 "                 the target.\n",
		 "       <target>  Name of the target to create.\n");
    
    # write to stdout
    print "@usage\n";
    exit;
}

