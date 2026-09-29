#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#=========================================================================
# File Name      : clearcase.pm
# Description    : Perl module to access Rational Inc. ClearCase
# 
# Notes          : This module contain various utilities for
#                  accessing and querying ClearCase.
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#=========================================================================

package CbaClearCase;

use strict;
use File::Basename;
use File::Spec;

use vars qw(@ISA @EXPORT $VERSION);
use Exporter;

$VERSION  = 1.00;

@ISA    = qw(Exporter);
@EXPORT = qw(createDirElement
             createFileElement
			 checkinDirs
             checkinElement
             isElementCheckedOut
             setCbaClearCaseDebug);

my $ibaClearCaseDebug    = 0;
my $ibaClearCaseDebugStr = "CbaClearCase>";

sub setCbaClearCaseDebug  
{ 
	$ibaClearCaseDebug = $_[0]; 
	my $str = ($ibaClearCaseDebug ? "Debugging on\n" : "Debugging off\n");
	CbaClearCaseDebug($str);
}

sub CbaClearCaseDebug { print "$ibaClearCaseDebugStr @_" if $ibaClearCaseDebug; }


# ------------------------------------------------------------------------
# Function    : createDirElement
# Description : Creates a directory element within ClearCase
# Parms       : $dir    - the directory name to create
#               $branch - ClearCase branch to create dir on. 
#               $trunk  - ClearCase trunk to create dir on. 
# Returns     : none
# Notes       : The directories will remain checked out after creating
#               any sub-directories. This function assumes that any
#               parent directory of the current directory is already
#               checked out. If no trunk is givrn the main branch 
#               is assumed.
# ------------------------------------------------------------------------
sub createDirElement
{
    # get the arguments
    my ($dir) = @_;

    # get the name of the parent directory
    my $rootDir = dirname($dir);

    # ClearCase command string
    my $cmd;

    # create only if the directory does not exist
    if (! -e $dir)
    {
		# check if the parent directory is checked out
		if (!isElementCheckedOut(1, $rootDir))
		{
		    $cmd = "cleartool co -nc $rootDir";
			CbaClearCaseDebug("$cmd\n");
		    die "\n" if system $cmd; 
		}
		
		# make the ClearCase directory element
		$cmd = "cleartool mkdir -nc $dir";
		CbaClearCaseDebug("$cmd\n");
		die "\n" if system $cmd; 
    }
}

# ------------------------------------------------------------------------
# Function    : createFileElement
# Description : Creates a file element within ClearCase
# Parms       : $file   - the file to create
#               $branch - ClearCase branch to create element on.
#               $trunk  - ClearCase trunk to create element on. 
# Returns     : none
# Notes       : The files will remain checked out after creation.
#               Assumes the element type is auto-determined. If no
#               trunk is given, the main branch is assumed.
# ------------------------------------------------------------------------
sub createFileElement
{
    # get the arguments
    my ($file) = @_;

    # get the name of the directory
    my $dir = dirname($file);

    # ClearCase command string
    my $cmd;

    if (! -e $file)
    {
		# check if the current directory is checked out
		if (!isElementCheckedOut(1, $dir))
		{
		    $cmd = "cleartool co -nc $dir"; 
			CbaClearCaseDebug("$cmd\n");
		    die "\n" if system $cmd;
		}
		
		# make the ClearCase file element
		$cmd = "cleartool mkelem -nc $file"; 
		CbaClearCaseDebug("$cmd\n");
		die "\n" if system $cmd;
    }
}

# ------------------------------------------------------------------------
# Function    : isElementCheckedOut
# Description : Checks whether an element is checked out
# Parms       : $dirFlag - indicated whether an element is a
#                          a file or a directory.
#               $element - the file or directory name to check
# Returns     : 1 (true) if checked out otherwise 0 (false).
# Notes       : 
# ------------------------------------------------------------------------
sub isElementCheckedOut
{
    # get the arguments
    my ($dirFlag, $element) = @_;
    
    my $dir = ($dirFlag ? "-dir" : ""); 

    my $cmd = "cleartool lsco -short -cview $dir $element";
	CbaClearCaseDebug("$cmd\n");

    my $lsco = `$cmd`;
    
	# escape the win32 dir slashes
	$element =~ s/\\/\\\\/g;

	# regex requires \. not .
    $element = '\.' if ($element eq '.');

    return(1) if ($lsco =~ /^$element/);
    return(0);
}

# ------------------------------------------------------------------------
# Function    : checkinDirs
# Description : Checks an array of directory elements into ClearCase
# Parms       : $dirArray - reference to the dir list to checkin
# Returns     : none
# Notes       : The array is reversed so the bottom of the tree
#               is checked in first.
# ------------------------------------------------------------------------
sub checkinDirs
{
    # get the dir list
    my ($dirArray) = @_;

    foreach my $dir (reverse @$dirArray)
    {
    	my $DirElement = File::Spec->canonpath($dir);
        checkinElement($DirElement);
    }
}

# ------------------------------------------------------------------------
# Function    : checkinElement
# Description : Checks a file or directory element into ClearCase
# Parms       : $element - the file or directory name to checkin
# Returns     : none
# Notes       : 
# ------------------------------------------------------------------------
sub checkinElement
{
    # get the arguments
    my ($element) = @_;

    # ClearCase command string
    my $cmd;

    # check in the file or directory
    $cmd = "cleartool ci -nc $element";
	CbaClearCaseDebug("$cmd\n");
    die "\n" if system $cmd;
}

1;







