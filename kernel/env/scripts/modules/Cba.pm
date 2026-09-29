#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : Cba.pm
# Description    : Perl module of general CBA functions
# 
# Notes          : 
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

package Cba;

use strict;
use Exporter;
use vars qw(@ISA @EXPORT $VERSION);
use File::Basename;

$VERSION  = 1.00;

@ISA    = qw(Exporter);
@EXPORT = qw(isElement
             getElementList
             setCbaDebug);

my $ibaDebug    = 0;
my $ibaDebugStr = "Cba>";

sub setCbaDebug  
{ 
	$ibaDebug = $_[0]; 
	my $str = ($ibaDebug ? "Debugging on" : "Debugging off");
	CbaDebug($str);
}

sub CbaDebug { print "$ibaDebugStr @_" if $ibaDebug; }


# -----------------------------------------------------------------------------
# Function    : getElementList
# Description : Finds a list of elements from a start directory
# Parms       : root  - root directory to start search
# Returns     : the element list
# Notes       : Ignores the env directory. Returns a list of 
#               of basenames and element names in the
#               form : <base>/<element>
# -----------------------------------------------------------------------------
sub getElementList
{
    # get the arguments
    my ($root) = @_;
	my $firstLevelEntry;
	my $secondLevelEntry;
	my @elementList;

	# handle the null root directory case
	my $defaultRootDir = $^O eq "MSWin32" ? "\\" : "/";
	$root = $defaultRootDir if ($root eq "");

	# open the directory
	opendir(FIRST_DIR, $root) or die "Error: cannot open the $root directory.\n";

	# clean up the root directory
	$root = "" if ($root eq "/" | $root eq "\\");
	$root =~ s/\\\\/\\/;
	$root =~ s/\/\//\//;

	# get the package, group, and target directories
	while ( defined ($firstLevelEntry = readdir FIRST_DIR) )
	{
		my $entry = "$root/$firstLevelEntry";

		CbaDebug("Checking $entry\n");

		# skip the dot entries
		next if $firstLevelEntry =~ /^\.\.?/;

		# skip the env directory
		next if $firstLevelEntry =~ /^env/;

		# skip unless the entry is a directory
		next unless ( -d $entry );

		# open the directory
		if (opendir(SECOND_DIR, $entry)) #MMS
		{
		
			while ( defined ($secondLevelEntry = readdir SECOND_DIR) )
			{
				my $entry = "$root/$firstLevelEntry/$secondLevelEntry";

				# skip the dot entries
				next if $secondLevelEntry =~ /^\.\.?/;

				# skip unless the entry is a directory
				next unless ( -d $entry );

				CbaDebug("Matched $entry\n");
				push @elementList, "$firstLevelEntry/$secondLevelEntry";
			}
		}
		else #MMS - Do nothing
		{
			CbaDebug("Cannot open the $entry directory.\n"); #MMS
		}
	}

	return(@elementList);
}

# -----------------------------------------------------------------------------
# Function    : isElement
# Description : Check whether a element is a package, group, or target
# Parms       : type - the type of element to look for
#               path - the path to the element to check
# Returns     : true or false
# Notes       : 
# -----------------------------------------------------------------------------
sub isElement
{
	my ($type, $path) = @_;
	my $retVal = 0;

	# clean up the path
	$path =~ s/\\\\/\\/;
	$path =~ s/\/\//\//;

	my $makefile = File::Spec->canonpath("$path/build/".basename($path).".mak");

	CbaDebug("Checking $makefile for $type.\n");

	# open the make file or continue
	return($retVal) unless open MAKE_FILE, "< ".$makefile;

	$type = "\U$type"."_NAME";

	CbaDebug("Checking $type\n");

    foreach my $line (<MAKE_FILE>)
	{
		if ($line =~ /\s*$type\s*=./)
		{
			$retVal = 1;
			last;
		}
	}

	$retVal ? CbaDebug("$path is a $type.\n") : CbaDebug("$path is not a $type.\n");

	return($retVal);
}


1;












