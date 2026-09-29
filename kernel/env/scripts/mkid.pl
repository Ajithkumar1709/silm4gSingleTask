#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : MkId.pl
# Description    : Perl script for generating File and module IDs
# 
# Notes          : 
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

use FindBin qw($Bin);
use lib "$Bin/modules";

use strict;
use Getopt::Long;
use CbaHeader;
use File::Basename;
use File::Copy;
use Time::localtime;

# what system are we on ?
my $host = $^O eq "MSWin32" ? "win32" : "unix";

# get the year
my $tm = localtime;
my $year = $tm->year + 1900;

# set the output line lengths
my $defineLength = 35;
my $commentLength = 55;

# get the command line arguments -----------------------------------------
my %options = ();
GetOptions(\%options, "package=s", "group=s", "target=s", "variant=s", "global", "h|?");

# help switch
die usage() if ($options{'h'});

# check for the required arguments
usage() unless (scalar(@ARGV));

my $infile1 = $ARGV[0];
my $infile2 = $ARGV[1];

# convert single line files to multi-line files if needed
# the global lists are already in the correct format
unless ($options{'global'})
{
    convertSingleLineFiles($infile1);
    convertSingleLineFiles($infile2);
}

# check that the files are different and exit or update infile1
my $filesMatch = compareFileLists($infile1, $infile2);
my $file = basename($infile1);

# look for the global element
if ($options{'global'} && !$filesMatch)
{
    createGlobalIds($infile1);
    exit;
}

# look for the package element
if ($options{'package'} && !$filesMatch)
{
    createPackageIds($infile1);
    exit;
}

# look for the group element
if ($options{'group'} && !$filesMatch)
{
    createGroupIds($infile1);
    exit;
}

# look for the target element
if ($options{'target'} && !$filesMatch)
{
    createTargetIds($infile1);
    exit;
}

# no valid element, so display usage
usage();



# -----------------------------------------------------------------------------
# Function    : convertSingleLineFiles
# Description : Converts single line file list files
# Parms       : filename
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub convertSingleLineFiles
{
    my ($filename) = @_;
    my @line_list;

    # check for the existence of the file
    return unless (defined $filename);
    return if (!(-e $filename));

    # read in the file to an array
    open FH, "< $filename" or die "Error: Cannot open $filename.\n"; 
    my @filelist = <FH>;
    close FH;

    open FH, "> $filename" or die "Error: Cannot open $filename.\n"; 

    # process each line of the file
    foreach my $line (@filelist)
    {
        # split the line into separate array items
        @line_list = split(/\s/, $line);

        foreach my $item (@line_list)
        {
            print FH "$item\n";
        }
    }

    close FH;
}

# -----------------------------------------------------------------------------
# Function    : compareFileLists
# Description : 
# Parms       : none
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub compareFileLists
{
    my ($file1, $file2) = @_;
    my $match = 1;

    # file 1 does not exist so copy file2
    unless (-e $file1)
    {
	move($file2, $file1);
	return(0);
    }

    # file2 does not exist or was not supplied
    return(0) unless (defined $file2);
    return(0) if (!(-e $file2));

    # open the files
    open FH1, "< $file1" or die "Error: Cannot open $file1.\n"; 
    open FH2, "< $file2" or die "Error: Cannot open $file2.\n"; 

    my @filelist1 = <FH1>;
    my @filelist2 = <FH2>;

    close FH1;
    close FH2;

    # sort the arrays
    @filelist1 = sort @filelist1;
    @filelist2 = sort @filelist2;

    # if the sizes are different then there is no match
    $match = 0 unless ($#filelist1 == $#filelist2);

    for (my $i = 0 ; $i < scalar(@filelist1) ; $i++)
    {
	last unless ($match);
	$match = 0 unless ($filelist1[$i] eq $filelist2[$i]);
    }

    # the files are the same so do not update the header file and exit
    if ($match)
    {
	# delete the file2 file
	unlink($file2);
	exit;
    }
    else
    {
	# update file1
	if (-e $file2)
	{
	    unlink($file1);
	    move($file2, $file1);
	}
    }

    return($match);
}

# -----------------------------------------------------------------------------
# Function    : createPackageIds
# Description : Creates the package file ID header file
# Parms       : none
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub createPackageIds
{
    my ($inFile) = @_;
    my $fileCount = 1;
    my @lines = ();
    my $string;
    my $pad;

    # get the file information ---------------------------------------

    open IN_FILE, "<"."$inFile" 
	or die "Error: Cannot open $inFile.\n"; 

    # read the contents of the list file
    my @inBuffer = <IN_FILE>;
    close IN_FILE;

    # default variant
    my $variant = (defined $options{'variant'}) ? $options{'variant'} : "default";
    my $outFile = (defined $options{'variant'}) ? "../src/$variant"."_id.h" : "../src/$options{'package'}_default_id.h";

    # get the filename
    my $fileName = basename($outFile);

    # create the file header -----------------------------------------

    my $header = CbaHeader->new();
    $header->HeaderField("File", "$fileName");
    $header->HeaderField("Description", "File ID's for the $variant variant of the $options{'package'} package.\n");
    $header->HeaderField("Notes", "This file is auto-generated, do not modify.\nThe package ID for the $options{'package'} package is defined in gbl_id.h\n");
    $header->HeaderField("<Copyright>", "Copyright (c) $year Intel of Canada, All Rights Reserved.");
    $header->Fill("=", 1);

    # parse the file list and create the file ID's ------------------

    foreach my $line (@inBuffer)
    {
	if ($line =~ /\s*(.+)\.(.+)/)
	{
	    $string = "#define \U$1"."_FILE_ID";
	    $pad = $defineLength - length($string);
	    $string .= " " x $pad;
	    push @lines, "$string $fileCount";
	    $fileCount++;
	    next;
	}
    }

    # print the id file ---------------------------------------------

    open OUT_FILE, "> $outFile";

    $outFile = basename($outFile);
    print "--- Building package file id's [$outFile] ---\n";

    $fileName =~ s/\./_/;
    print OUT_FILE "$header\n";
    print OUT_FILE "#ifndef _"."\U$fileName"."_\n";
    print OUT_FILE "#define _"."\U$fileName"."_ 1\n";

    $string = "\u$options{'package'} Package Element ID's ";
    $pad = $commentLength - length($string);
    $string .= "-" x $pad;
    print OUT_FILE "\n/* $string */\n";

    foreach my $line (@lines)
    {
	print OUT_FILE "$line\n";
    }

    print OUT_FILE "\n#endif /* _"."\U$fileName"."_ */\n";

    close OUT_FILE;

}

# -----------------------------------------------------------------------------
# Function    : createGroupIds
# Description : Creates the group file ID header file
# Parms       : none
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub createGroupIds
{
    my ($inFile) = @_;
    my $fileCount = 1;
    my @lines = ();
    my $string;
    my $pad;

    # get the file information ---------------------------------------

    open IN_FILE, "<"."$inFile" 
	or die "Error: Cannot open $inFile.\n"; 

    # read the contents of the list file
    my @inBuffer = <IN_FILE>;
    close IN_FILE;

    # default variant
    my $variant = (defined $options{'variant'}) ? $options{'variant'} : "default";
    my $outFile = (defined $options{'variant'}) ? "../src/$variant"."_id.h" : "../src/$options{'group'}_default_id.h";

    # get the filename
    my $fileName = basename($outFile);

    # create the file header -----------------------------------------

    my $header = CbaHeader->new();
    $header->HeaderField("File", "$fileName");
    $header->HeaderField("Description", "File ID's for the $variant variant of the $options{'group'} group.\n");
    $header->HeaderField("Notes", "This file is auto-generated, do not modify.\nThe Group ID for the $options{'group'} group is defined in gbl_id.h\n");
    $header->HeaderField("<Copyright>", "Copyright (c) $year Intel of Canada, All Rights Reserved.");
    $header->Fill("=", 1);

    # parse the file list and create the file ID's ------------------

    foreach my $line (@inBuffer)
    {
	if ($line =~ /\s*(.+)\.(.+)/)
	{
	    $string = "#define \U$1"."_FILE_ID";
	    $pad = $defineLength - length($string);
	    $string .= " " x $pad;
	    push @lines, "$string $fileCount";
	    $fileCount++;
	    next;
	}
    }

    # print the id file ---------------------------------------------

    open OUT_FILE, "> $outFile";

    $outFile = basename($outFile);
    print "--- Building group file id's [$outFile] ---\n";

    $fileName =~ s/\./_/;
    print OUT_FILE "$header\n";
    print OUT_FILE "#ifndef _"."\U$fileName"."_\n";
    print OUT_FILE "#define _"."\U$fileName"."_ 1\n";

    $string = "\u$options{'group'} Group File ID's ";
    $pad = $commentLength - length($string);
    $string .= "-" x $pad;
    print OUT_FILE "\n/* $string */\n";

    foreach my $line (@lines)
    {
	print OUT_FILE "$line\n";
    }

    print OUT_FILE "\n#endif /* _"."\U$fileName"."_ */\n";

    close OUT_FILE;
}

# -----------------------------------------------------------------------------
# Function    : createTargetIds
# Description : Creates the target file ID header file
# Parms       : none
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub createTargetIds
{
    my ($inFile) = @_;
    my $fileCount = 1;
    my @lines = ();
    my $string;
    my $pad;

    # get the file information ---------------------------------------

    open IN_FILE, "<"."$inFile" 
	or die "Error: Cannot open $inFile.\n"; 

    # read the contents of the list file
    my @inBuffer = <IN_FILE>;
    close IN_FILE;

    # default variant
    my $variant = (defined $options{'variant'}) ? $options{'variant'} : "default";
    my $outFile = (defined $options{'variant'}) ? "../src/$variant"."_id.h" : "../src/$options{'target'}_default_id.h";

    # get the filename
    my $fileName = basename($outFile);

    # create the file header -----------------------------------------

    my $header = CbaHeader->new();
    $header->HeaderField("File", "$fileName");
    $header->HeaderField("Description", "File ID's for the $variant variant of the $options{'target'} target.\n");
    $header->HeaderField("Notes", "This file is auto-generated, do not modify.\nThe target ID for the $options{'target'} target is defined in gbl_id.h\n");
    $header->HeaderField("<Copyright>", "Copyright (c) $year Intel of Canada, All Rights Reserved.");
    $header->Fill("=", 1);

    # parse the file list and create the file ID's ------------------

    foreach my $line (@inBuffer)
    {
	if ($line =~ /\s*(.+)\.(.+)/)
	{
	    $string = "#define \U$1"."_FILE_ID";
	    $pad = $defineLength - length($string);
	    $string .= " " x $pad;
	    push @lines, "$string $fileCount";
	    $fileCount++;
	    next;
	}
    }

    # print the id file ---------------------------------------------

    open OUT_FILE, "> $outFile";

    $outFile = basename($outFile);
    print "--- Building target file id's [$outFile] ---\n";

    $fileName =~ s/\./_/;
    print OUT_FILE "$header\n";
    print OUT_FILE "#ifndef _"."\U$fileName"."_\n";
    print OUT_FILE "#define _"."\U$fileName"."_ 1\n";

    $string = "\u$options{'target'} Target File ID's ";
    $pad = $commentLength - length($string);
    $string .= "-" x $pad;
    print OUT_FILE "\n/* $string */\n";

    foreach my $line (@lines)
    {
	print OUT_FILE "$line\n";
    }

    print OUT_FILE "\n#endif /* _"."\U$fileName"."_ */\n";

    close OUT_FILE;

}

# -----------------------------------------------------------------------------
# Function    : createGlobalIds
# Description : Creates the global element ID header file
# Parms       : none
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub createGlobalIds
{
    my ($inFile) = @_;
    my $elemCount = 1;
    my @lines = ();
    my $string;
    my $pad;

    # get the file information ----------------------------------

    open IN_FILE, "<"."$inFile" 
	or die "Error: Cannot open $inFile.\n"; 

    # read the contents of the list file
    my @inBuffer = <IN_FILE>;
    close IN_FILE;

    # default variant
    my $variant = (defined $options{'variant'}) ? $options{'variant'} : "default";
    my $outFile = "../inc/gbl_$variant"."_id.h";

    # default target
    my $target = (defined $options{'target'}) ? " $options{'target'}" : "";

    # get the filename
    my $fileName = basename($outFile);

    # make the file header --------------------------------------

    my $header = CbaHeader->new();
    $header->HeaderField("File", "$fileName");
    $header->HeaderField("Description", "Element ID's for the $variant variant of the$target target.\n");
    $header->HeaderField("Notes", "This file is auto-generated, do not modify.\nThis file should be included in gbl_id.h\n");
    $header->HeaderField("<Copyright>", "Copyright (c) $year Intel of Canada, All Rights Reserved.");
    $header->Fill("=", 1);

    # extract the element information ---------------------------

    # parse the package, group, and target type
    foreach my $line (@inBuffer)
    {
	# save the package, group, or target ID
	if ($line =~ /\s*(\w+)\s*:\s+(\w+)\s*/)
	{
	    $string = "#define \U$2"."_\U$1"."_ID";
	    $pad = $defineLength - length($string);
	    $string .= " " x $pad;
	    push @lines,  "$string $elemCount";
	    $elemCount++;
	    next;
	}
    }

    # print the id file -----------------------------------------

    open OUT_FILE, "> $outFile";

    $outFile = basename($outFile);
    print "--- Building global element id's [$outFile] ---\n";

    $fileName =~ s/\./_/;
    print OUT_FILE "$header\n";
    print OUT_FILE "#ifndef _"."\U$fileName"."_\n";
    print OUT_FILE "#define _"."\U$fileName"."_ 1\n";

    $string = "\uGlobal$target Element ID's ";
    $pad = $commentLength - length($string);
    $string .= "-" x $pad;
    print OUT_FILE "\n/* $string */\n";

    foreach my $line (@lines)
    {
	print OUT_FILE "$line\n";
    }

    print OUT_FILE "\n#endif /* _"."\U$fileName"."_ */\n";

    close OUT_FILE;

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
		 "usage: mkid [-?|h] -package|group|target|global [-variant <variant>] <infile1> [<infile2>]\n",
		 "\n",
                 "       -package   Create the package file ID header file.\n",
                 "       -group     Create the group file ID header file.\n",
                 "       -target    Create the target file ID header file.\n",
                 "       -global    Create the global element ID header file.\n",
                 "       -variant   The name of the variant of the package,\n",
                 "                  group, target, or global list.\n",
		 "       <infile1>  Input file with file or element list.\n",
                 "       <infile2>  Input file to compare with infile1.\n",
                 "\n",
                 "       If <infile2> is provided then the ID header file will only be created\n",
                 "       if the two files are different. The -target flag must be used as well\n",
				 "       as the -global flag when generating the global flags for a target.\n");

    # write to stdout
    print "@usage\n";
    exit;
}
