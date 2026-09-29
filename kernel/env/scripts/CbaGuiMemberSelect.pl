#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : getList.pl
# Description    : Perl test script for get list widget
# 
# Notes          : 
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

use strict;

# Tk modules
use Tk;
use CbaGuiMemberSelect;

# standard modules
use Getopt::Long;

# Cba modules
use CbaTarget;
use CbaGroup;
use CbaPackage;

sub getList;

# what system are we on ?
my $host = $^O eq "MSWin32" ? "win32" : "unix";

my %options = ();
GetOptions(\%options, "r=s"); 

# set the root directory base on the system or environmental variable
my $MSWin32RootDir = $ENV{'CBA_ROOT'} || "";
my $DefaultRootDir = $^O eq "MSWin32" ? $MSWin32RootDir : "/vobs";
my $RootDir =  $options{'r'} || $DefaultRootDir;

my @memList;

# Build the GUI ----------------------------------------------------------

# main window geometry
my $mainWinHeight = 530;
my $mainWinWidth  = 530;
my $mainWinResize = 1;
my $mainWinBorder = 20;

# create the main window
my $mw = MainWindow->new();
$mw->title("MkTarget");
$mw->geometry("$mainWinWidth"."x"."$mainWinHeight");
$mw->resizable($mainWinResize, $mainWinResize);

my $selectWidget = $mw->CbaGuiMemberSelect(-srcDir  => $RootDir,
                                           -destList => \@memList,
                                          )->place(-x => 10, -y => 10);

# button geometry
my $buttonWidth      = 6;
my $buttonCancelXoff = $mainWinWidth - 70; 
my $buttonOkXoff     = $buttonCancelXoff - 60; 

# place the OK and cancel buttons
my $buttonFrame = $mw->Frame(-height => 40)->pack(-side => 'bottom', -fill => 'both');
$buttonFrame->Button(-text    => "Ok",
	                 -command => sub { getList;  $mw->destroy; },
	                 -width   => $buttonWidth)->place(-x => $buttonOkXoff);

$buttonFrame->Button(-text    => "Cancel",
	                 -command => sub { exit },
	                 -width   => $buttonWidth)->place(-x => $buttonCancelXoff);

# run the GUI ...
MainLoop;

sub getList
{
	print "Elements: @memList\n";
}