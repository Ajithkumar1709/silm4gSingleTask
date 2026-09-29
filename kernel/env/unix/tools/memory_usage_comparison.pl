#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/bin/perl -w
############################################################################
#
# PURPOSE:
# This script compares the used memory of segments between two map files.
# Not all segments are compared - the segments are selected using input file
# For each segments the script outputs a line of the following format:
# <segment name> <delta> <free>
# where "delta" meaning - used memory in the new map file minus used memory
# in the reference map file.
# "free" is the amount of free memory in the current segment according
# to the current map file.
#
# STEPS:
# STEP 1 - ANALYZE ARGUMENTS & INITIALIZE VARIABLES
# STEP 2 - OPEN FILE HANDLES
# STEP 3 - LOAD SEGMENTS TABLES FROM REFERENCE MAP FILE
# STEP 4 - LOAD SEGMENTS TABLES FROM MAP FILE
# STEP 5 - GO OVER LIST OF SEGMENTS AND PRINT THE OUTPUT
#
# HISTORY:
# Nissan Aloni   18-07-2006		Original.
# Nissan Aloni   27-07-2006     Change format of the "FREE" column in the
#                               output - print the data in decimal format
#                               and not in Hexa
#
############################################################################
use strict;

print "***********************\n";
print "MEMORY USAGE COMPARISON\n";
print "***********************\n\n";

############################################################################
# STEP 1 - ANALYZE ARGUMENTS & INITIALIZE VARIABLES
############################################################################
my $num_args = $#ARGV + 1;
if ($num_args != 4 ) {
	print "Error in number of arguments !!!\n";
	print "Usage:  memory_usage_comparison.pl <Meomry Segments List File> <Map file> <Reference Map file> <Output File>\n"; 
	print "Example: memory_usage_comparison.pl S:\\l1p_fw_targets\\tavor\\build\\MUC_segments_list.INI S:\\l1p_fw_targets\\tavor\\bin\\TavorA0.map S:\\l1p_fw_targets\\tavor\bin\\TavorA0_baseline.map muc_output.txt\n"; 
	exit 1;
}
my $segments_file_path;
$segments_file_path = $ARGV[0];
my $map_file_path;
$map_file_path = $ARGV[1];
my $reference_map_file_path;
$reference_map_file_path = $ARGV[2];
my $output_file_path;
$output_file_path = $ARGV[3];

############################################################################
# STEP 2 - OPEN FILE HANDLES
############################################################################
open (SEGMENTS_HANDLE,$segments_file_path) || die "Can't open $segments_file_path \n";
open (MAP_HANDLE,$map_file_path) || die "Can't open $map_file_path \n";
open (REF_MAP_HANDLE,$reference_map_file_path) || die "Can't open $reference_map_file_path \n";
open (OUTPUT_HANDLE,">$output_file_path") || die "Can't open $output_file_path \n";

############################################################################
# STEP 3 - LOAD SEGMENTS TABLES FROM REFERENCE MAP FILE
############################################################################
my %ref_map_segments_hash;
my $flag = "FALSE";
while (<REF_MAP_HANDLE>) {
	my $map_line = $_;
	if ( $flag eq "TRUE" ) {
		chomp $map_line;
		if (/^\s*$/) {
			# EMPTY LINE
			last;
		}
		else {
			# NON EMPTY LINE
			my @LineAr;
			@LineAr = split(qq( ),$map_line);
			$ref_map_segments_hash{$LineAr[0]} = [($LineAr[6],$LineAr[7])];
		}
	}
	if ( $map_line =~ /Name            Start Address  End Address   Type  Qualifier       Width  Memory-Bytes-Used   Memory-Bytes-Unused/) {
		$flag = "TRUE";
	}
}

############################################################################
# STEP 4 - LOAD SEGMENTS TABLES FROM MAP FILE
############################################################################
my %map_segments_hash;
$flag = "FALSE";
while (<MAP_HANDLE>) {
	my $map_line = $_;
	if ( $flag eq "TRUE" ) {
		chomp $map_line;
		if (/^\s*$/) {
			# EMPTY LINE
			last;
		}
		else {
			# NON EMPTY LINE
			my @LineAr;
			@LineAr = split(qq( ),$map_line);
			$map_segments_hash{$LineAr[0]} = [($LineAr[6],$LineAr[7])];
		}
	}
	if ( $map_line =~ /Name            Start Address  End Address   Type  Qualifier       Width  Memory-Bytes-Used   Memory-Bytes-Unused/) {
		$flag = "TRUE";
	}
}

############################################################################
# STEP 5 - GO OVER LIST OF SEGMENTS AND PRINT THE OUTPUT
############################################################################
printf ("%-29s %20s %10s\n","SEGMENT","DELTA FROM BASELINE","FREE");
printf ("%-29s %20s %10s\n","-------","-------------------","----");

printf OUTPUT_HANDLE ("%-29s %14s %10s\n","SEGMENT","USED (DELTA)","FREE");
printf OUTPUT_HANDLE ("%-29s %14s %10s\n","-------","------------","----");

while(<SEGMENTS_HANDLE>) {
	my ($line) = $_;
	chomp($line);
	my $delta = hex($map_segments_hash{$line}[0]) - hex($ref_map_segments_hash{$line}[0]);
	my $free = hex($map_segments_hash{$line}[1]);
	printf ("%-29s %20d %10d\n",$line,$delta,$free);
	printf OUTPUT_HANDLE ("%-29s %20d %10d\n",$line,$delta,$free);
}
exit;
