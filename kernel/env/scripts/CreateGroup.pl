#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#==============================================================================
# File Name      : CreateGroup.pl
# Description    : Perl script to generate group directory structure. 
# 
# Notes          : This script creates the required directories and
#                  template files for a new group.  The scripts can
#                  be 'ClearCase' aware and create the directory elements
#                  if desired.
#
# Usage          : CreateGroup [-?|h] [-r <root>] [<vob>/<pack>]
#                  -r      Group root directory. This defaults to /vobs on
#                          unix systems and / on win32 systems. The group
#		                   root directory can also be defined via the
#		                   CBA_ROOT environment variable.
#                  -?      This help.
#                  <base>  Group ClearCase VOB name of where to create
#                          the group. 
#                  <pack>  Name of the group to create.
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
sub createGroup;
sub usage;

# turn on the debugging for the modules
setCbaGroupDebug(0);
setCbaClearCaseDebug(0);


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
my $mainWinHeight = 590;
my $mainWinWidth  = 665;
my $mainWinResize = 1;
my $mainWinBorder = 20;

# create the main window
my $mw = MainWindow->new();
$mw->title("CreateGroup");
$mw->geometry("$mainWinWidth"."x"."$mainWinHeight");
$mw->resizable($mainWinResize, $mainWinResize);

# add the notebook widget
my $note = $mw->NoteBook();

# Page 1 GUI Variables
my $groupBaseName;
my $groupName;
my $ccFlag = 0;
my $lvcoFlag = 1;

my @envList = ("msa", "xscale", "arm", "gnu",);
my $platformVar = "River";
my @platformList = ($platformVar, "Manitoba", "Hermon", "Threepoint", );
my @ifList = ("API", "config",);

my @memList;

# add the group page to the notebook
my $page1 = $note->add("group",
	                   -label => "Group",
	                   );

guiGroupPage($page1);

# button geometry
my $buttonWidth      = 6;
my $buttonCancelXoff = $mainWinWidth - 70; 
my $buttonOkXoff     = $buttonCancelXoff - 60; 

# place the OK and cancel buttons
my $buttonFrame = $mw->Frame(-height => 40)->pack(-side => 'bottom', -fill => 'both');
$buttonFrame->Button(-text    => "Ok",
	                 -command => sub { createGroup;  $mw->destroy; },
	                 -width   => $buttonWidth)->place(-x => $buttonOkXoff);

$buttonFrame->Button(-text    => "Cancel",
	                 -command => sub { exit },
	                 -width   => $buttonWidth)->place(-x => $buttonCancelXoff);

# run the GUI ...
$note->place(-x => 10, -y => 10);
MainLoop;


# -----------------------------------------------------------------------------
# Function    : createGroup
# Description : 
# Parms       : 
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub createGroup
{
    my $groupPath = "$RootDir/$groupBaseName/$groupName";
    
    # create the directories and return the dir list
    my @dirs = ();
    createGroupDirTree(\@dirs, $groupPath, $ccFlag, $lvcoFlag);
    
    # create the interface files
    my @srcList = createGroupInterfaceFiles(\@ifList,\@memList, $TemplateDir, $groupPath, $ccFlag, $lvcoFlag);
    
    # create the test environment files
    createGroupTestEnvFiles(\@envList, $platformVar, $TemplateDir, $groupPath, $ccFlag, $lvcoFlag);
    
    # create the group make files
    createGroupMakeFiles(\@srcList, $platformVar, \@memList, $TemplateDir, $groupPath, $ccFlag, $lvcoFlag);
    
    # checkin the directories if using ClearCase
    checkinDirs(\@dirs) if (!$lvcoFlag);

}


# -----------------------------------------------------------------------------
# Function    : guiGroupPage
# Description : 
# Parms       : 
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub guiGroupPage
{
	my ($page) = @_;

    my $leftFrame  = $page->Frame();
    my $rightFrame = $page->Frame();
    my $botFrame   = $page->Frame();
    
    # create the group name widget
    my $groupWidget = $leftFrame->CbaGuiName(-label => "Group",
					    -nameVar => \$groupName,
				        -baseVar => \$groupBaseName,
				        -width  => 300,
#                        -height => 80,
				        )->pack;

    # create the ClearCase widget
    my $ccWidget = $rightFrame->CbaGuiClearCase(-ccFlagVar   => \$ccFlag,
				        -lvcoFlagVar   => \$lvcoFlag,
				        -width       => 320,
#					    -height      => 60,
				        )->pack;

	# create the interface widget
	my $interfaceWidget = $leftFrame->CbaGuiCheckList(-title   => "Interface",
  					        -width   => 300,
	                        -checkList => \@ifList,
	                        )->pack();

    # create the Member selection widget
    my $memberWidget =  $rightFrame->CbaGuiMemberSelect(-title => "Member Selection",
                         -width    => 320,
                         -height   => 360,
                         -listHeight => 17,
                         -srcDir   =>  $RootDir,
                         -destList =>  \@memList,
                         )->pack; 

	# create the test env widget
	my $testEnvWidget = $leftFrame->CbaGuiCheckList(-title   => "Test Platform",
					        -width   => 300,
	                        -checkList => \@envList,
	                        )->pack();

	my $testPlatWidget = $leftFrame->CbaGuiRadioList(-title   => "HW Platform",
                     -entry   => 1,
					 -width   => 300,
#					 -height  => 60,
					 -radioList => \@platformList,
					 -variable => \$platformVar,
					 )->pack();



    $leftFrame->pack(-side => 'left');
    $rightFrame->pack(-side => 'right');
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
		 "usage: CreateGroup [-?|h] [-r <root>] [<vob>/<group>]\n",
		 "\n",
         "       -r        Group root directory. This defaults to /vobs on\n",
         "                 unix systems and \\ on win32 systems. The group\n",
		 "                 root directory can also be defined via the\n",
		 "                 CBA_ROOT environment variable.\n",
		 "       -?        This help.\n",
		 "       <vob>     Group ClearCase VOB name of where to create\n",
		 "                 the group.\n",
		 "       <group>   Name of the group to create.\n");
    
    # write to stdout
    print "@usage\n";
    exit;
}
