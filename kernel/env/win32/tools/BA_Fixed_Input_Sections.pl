#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/bin/perl -w
############################################################################
#
# PURPOSE:
#
# This script goes over a list out fixed output sections and replaces
# each output section with a list of its input sections - according to
# map file.
# This list of input sections will be replaced with a list on labels/symbols
# from the map file.
# the final list of fixed labels/symbols will be used to verify
# ROM BIN integrity.
#
# STEPS:
#
# 1. ANALYZE ARGUMENTS & INITIALIZE VARIABLES
# 2. OPEN Fixed_Input_Sections_ FILE & LOAD LIST OF OUTPUT SECTIONS
# 3. READ MAP FILE AND PRINT TO FILE THE CORRESPONDING INPUT SECTIONS
#
# IMPORTANT VARIABLES:
# %output_sections_hash - this hash table holds all the fixed output sections
# 						this list is taken from the input file
#
# HISTORY:
# Nissan Aloni   04-06-2006		Original.
# Nissan Aloni   09-07-2006     Stop reading the MAP file once the line:
# 								"The overlays which belong to the PROCESSOR project p0  are"
# 								is reached.
#
############################################################################

use strict;
print "\n\n";
print "**************************\n";
print "BA_Fixed_Input_Sections.pl\n";
print "**************************\n";

#####################################################
# STEP 1 - ANALYZE ARGUMENTS & INITIALIZE VARIABLES #
#####################################################
my $num_args = $#ARGV + 1;
if ($num_args != 2 ) {
	print "Error in number of arguments !!!\n";
	print "Usage:  BA_Fixed_Input_Sections.pl <Name Of BA Directory> <Map file name>\n"; 
	print "Example: BA_Fixed_Input_Sections.pl Tavor_A0_BA TavorA0.map\n";
	exit 1;
}

my $BA_directory_name;
$BA_directory_name = $ARGV[0];

my $map_fn;
$map_fn = $ARGV[1];

# OPEN MACROS.MK FILE AND READ THE FOLLOWING INFORMATION:
# $root_drive - S:
# $build_scenario - WB_OUT_OF_ROM / GSM_OUT_OF_ROM ETC...
my $root_drive;
my $build_scenario;
my $macro_path = "macros.mk";
open (MACRO,$macro_path) || die "Can't open $macro_path\n" ;
my $templine = <MACRO>;
while(defined($templine)) {
	if ($templine=~/BUILD_TYPE=(.*)/){
		if (( $1 !~ /BUILD_FROZEN_FILES/ ) && ( $1 !~ /BUILD_TARGET_FILES/ )) {
			print "Problem in $macro_path - unknown BUILD_TYPE at:\n$templine\n";
			exit 1;
		}
	}
	if ($templine=~/CBA_ROOT=(.*)/){
		$root_drive = $1;
	}
	if ($templine=~/BUILD_SCENARIO=(.*)/){
		$build_scenario = $1;
	}
	$templine = <MACRO>;
}
close(MACRO);

# CHECK THAT THE BA DIRECTORY CAN BE ACCESSED
my $BA_dir_path = "$BA_directory_name";
if (!(-d $BA_dir_path)) {
	print "The BA directory can't be found / accessed - $BA_dir_path\n";
	exit 1;
}

my $map_file_path;
$map_file_path = "..\\bin\\$map_fn";;
my $fixed_output_sections_file_path;
$fixed_output_sections_file_path = "$BA_dir_path\\Fixed_Output_Sections_${build_scenario}.txt";
my $fixed_input_sections_file_path;
$fixed_input_sections_file_path = "$BA_dir_path\\Fixed_Input_Sections_${build_scenario}.txt";

# WRITE NAMES OF INPUTS / OUTPUTS FILES
print "\n";
print "INPUT:\n";
print "------\n";
print "\t$macro_path\n";
print "\t$map_file_path\n";
print "\t$fixed_output_sections_file_path\n";
print "\n";
print "OUTPUT:\n";
print "------\n";
print "\t$fixed_input_sections_file_path\n";
print "\n";
print "\n";

###########################################################################
# STEP 2 - OPEN Fixed_Input_Sections_ FILE & LOAD LIST OF OUTPUT SECTIONS #
###########################################################################
if (!(-e "$fixed_output_sections_file_path")) {
  print "Can't access $fixed_output_sections_file_path\n";
  exit 1;
}
open (FIXED_OUTPUT_SECTIONS_FILE_HANDLE,$fixed_output_sections_file_path) || die "Can't open $fixed_output_sections_file_path\n";
my %output_sections_hash = ();
while(<FIXED_OUTPUT_SECTIONS_FILE_HANDLE>) {
	my $fixed_output_section = $_;
	chomp $fixed_output_section;
	$output_sections_hash{$fixed_output_section} = 1;
}
close(FIXED_OUTPUT_SECTIONS_FILE_HANDLE);

#############################################################################
# STEP 3 - READ MAP FILE AND PRINT TO FILE THE CORRESPONDING INPUT SECTIONS #
#############################################################################
if (!(-e "$map_file_path")) {
  print "Can't access map file - $map_file_path";
  exit 1;
}
open (MAP_FILE_HANDLE,$map_file_path) || die "Can't open $map_file_path\n";

# OPEN INPUT SECTIONS FILE - THIS IS THE OUTPUT FILE OF THIS SCRIPT
open (FIXED_INPUT_SECTIONS_FILE_HANDLE,">$fixed_input_sections_file_path") || die "Can't open $fixed_input_sections_file_path";

# THIS LOOP READS LINES FROM THE MAP FILE
# WHEN IT RECOGNIZES A "Output Section " LINE IT CHECKS IF THE 3RD
# STRING IN THAT LINE IS A FIXED OUTPUT SECTION (USING THE FIXED
# OUTPUT SECTION HASH TABLE WHICH WAS LOADED FROM THE INPUT FILE)
# IF THE OUTPUT SECTION EXISTS IN THAT LIST - THE SCRIPT SKIPS THE NEXT LINE
# WHICH IS A HEADER LINE AND
# WRITES ALL THE FOLLOWING INPUT SECTIONS TO THE OUTPUT FILE
while(<MAP_FILE_HANDLE>) {
	my $map_line = $_;
	chomp $map_line;
	if ($map_line =~ /Output Section (.*)/){
		# $1 - stores the 3rd argument
		if (exists $output_sections_hash{$1}){
			# SKIP HEADER LINE
			<MAP_FILE_HANDLE>;

			while (<MAP_FILE_HANDLE>) {
				# READ ALL INPUT SECTIONS
				my $line = $_;
				chomp $line;
				if (/^\s*$/) {
					# EMPTY LINE
					last;
				}
				else {
					my @LineAr;
					@LineAr = split(qq( ),$line);
					print FIXED_INPUT_SECTIONS_FILE_HANDLE "$LineAr[0] $LineAr[3]\n";
				}
			}
		}
	}
	if ($map_line =~ /The overlays which belong to the PROCESSOR project p0  are/) {
		last;
	}
}
exit;
