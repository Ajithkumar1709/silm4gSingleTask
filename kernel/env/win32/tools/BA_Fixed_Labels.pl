#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/bin/perl -w
############################################################################
#
# PURPOSE:
# This script goes over a list of fixed input sections and replaces
# each input section with a list of its labels - according to map file.
# The list of fixed labels is saved into an output file
#
# STEPS:
# 1. ANALYZE ARGUMENTS & INITIALIZE VARIABLES
# 2. LOAD FIXED INPUT SECTIONS LIST INTO HASH TABLE
# 3. GO OVER LABELS TABLE IN THE MAP FILE AND PRINT THE	FIXED LABELS
#
# IMPORTANT VARIABLES:
#
# %input_sections_hash - this hash table holds all the fixed input sections
# 					and the corresponding doj file for each input section.
# 					this hash is loaded from the input file -
# 					Fixed_Input_Sections_${build_scenario}.txt
#
#  					This table is used to determine whether a label is a fixed
# 				label - it is done by comparing its doj & input section with
# 				those in the hash table.
#
# HISTORY:
# Nissan Aloni   04-06-2006		Original.
# Nissan Aloni   10-07-2006		BUG fix - the key for %input_sections_hash is the name of the Input Section - taken from the
# 								first word in each line in Fixed_Input_Sections_${build_scenario}.txt
# 								Each input section can appear in several lines (with different doj's) - and since the key to the hash
# 								is the name of the input section it means that the hash will hold only the last occurrence of the input section
# 								we want the hash to hold all the occurrences of the input section - with all the doj files
# 								I've changed the key of the hash to be "<input section> <doj file>"
#
############################################################################

use strict;
print "\n\n";
print "******************\n";
print "BA_Fixed_Labels.pl\n";
print "******************\n";

############################################################################
# STEP 1 - ANALYZE ARGUMENTS & INITIALIZE VARIABLES
############################################################################
my $num_args = $#ARGV + 1;
if ($num_args != 2 ) {
	print "Error in number of arguments !!!\n";
	print "Usage:  BA_Fixed_Labels.pl <Name Of BA Directory> <Map file name>\n"; 
	print "Example: BA_Fixed_Labels.pl Tavor_A0_BA TavorA0.map\n";
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

my $fixed_input_sections_file_path = "$BA_dir_path\\Fixed_Input_Sections_${build_scenario}.txt";
my $map_file_path;
$map_file_path = "..\\bin\\$map_fn";;
my $fixed_labels_file_path = "$BA_dir_path\\Fixed_Labels_${build_scenario}.txt";

# WRITE NAMES OF INPUTS / OUTPUTS FILES
print "\n";
print "INPUT:\n";
print "------\n";
print "\t$macro_path\n";
print "\t$map_file_path\n";
print "\t$fixed_input_sections_file_path\n";
print "\n";
print "OUTPUT:\n";
print "------\n";
print "\t$fixed_labels_file_path\n";
print "\n";
print "\n";

############################################################################
# STEP 2 - LOAD FIXED INPUT SECTIONS LIST INTO HASH TABLE
############################################################################
if (!(-e "$fixed_input_sections_file_path")) {
  print "Can't access $fixed_input_sections_file_path\n";
  exit 1;
}
open (FIXED_INPUT_SECTIONS_FILE_HANDLE,$fixed_input_sections_file_path) || die "Can't open $fixed_input_sections_file_path\n";
my %input_sections_hash = ();
my @LineAr;
while(<FIXED_INPUT_SECTIONS_FILE_HANDLE>) {
	my $cur_line = $_;
	chomp $cur_line;
	@LineAr = split(qq( ),$cur_line);
	$input_sections_hash{"$LineAr[0] $LineAr[1]"} = 1;
}
close(FIXED_INPUT_SECTIONS_FILE_HANDLE);

############################################################################
# STEP 3 - GO OVER LABELS TABLE IN THE MAP FILE AND PRINT THE
# 			FIXED LABELS
############################################################################
open (FIXED_LABELS_FILE_HANDLE,">$fixed_labels_file_path") || die "Can't open $fixed_labels_file_path";

if (!(-e "$map_file_path")) {
  print "Can't access map file - $map_file_path";
  exit 1;
}
open (MAP_FILE_HANDLE,$map_file_path) || die "Can't open $map_file_path\n";


my @map_lines_array = <MAP_FILE_HANDLE>;
my $i;
my $found_labels_table_flag = 0;
for($i=0;$i<=$#map_lines_array;$i++) {
	# FOUND THE FIRST LINE OF THE LABELS PART
	if ($map_lines_array[$i] =~ /Name                          Demangled Name                 Address      Size        Binding     Filename/ ) {
		$found_labels_table_flag = 1;
	}
	if ( $found_labels_table_flag == 1 ) {
		# END OF LABELS TALBE
		if ( $map_lines_array[$i] =~ (/^\s*$/) ) {
			last;
		}
		else  {
			@LineAr = split(qq( ),$map_lines_array[$i]);
			my $input_section_name = $LineAr[5];
			my $doj_name = $LineAr[4];
			if (exists $input_sections_hash{"$input_section_name $doj_name"}) {
#				if ($input_sections_hash{$input_section_name} eq $doj_name) {
					print FIXED_LABELS_FILE_HANDLE "$LineAr[0]\n";
#				}
			}
		}
	}
}
close(MAP_FILE_HANDLE);
close(FIXED_LABELS_FILE_HANDLE);

exit;
