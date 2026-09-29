#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/bin/perl -w
############################################################################
#
# PURPOSE:
# This script goes over a list of fixed labels - from input file.
# it determines the actual address of each label according to the map file
# (after the BTF).
# This list is then printed to output file - labels which weren't found in
# the map file are not printed to the output file (their address are
# marked as -99999).
# Then a reference list of labels is loaded (this list was created during
# ROM MASK preparation). Each item in the reference list should match an item
# in the list of labels from the current map file.
# (*) warning is issued if the same label is found in both lists but with
# different addresses
# (*) note is issued if a reference label can't be found in current map file
#     & a different label can be found at that address
# (*) note is issued if a reference label can't be found in current map file
#     & no other label is found at that address.
#
# STEPS:
# 1. ANALYZE ARGUMENTS & INITIALIZE VARIABLES
# 2. LOAD FIXED LABELS LIST INTO HASH TABLE
# 3. GO OVER "LABELS TABLE" IN THE MAP FILE AND UPDATE
#     fixed_labels_hash WITH THE ADDRESSES OF ALL THE LABELS
# 4. WRITE THE HASH TABLE - fixed_labels_hash - TO OUTPUT FILE
# 5. COMPARE REFERENCE FILE TO CURRENT ADDRESSES OF LABELS &
#    ISSUE WARNINGS & NOTES -
#    a. Prepare list of fixed labels in current map file - %fixed_labels_hash
#    b. Loop over labels from reference file:
#       if a label cant be found in list of current map file - add it %missing_labels_hash
#       and issue a warning
#    c. loop over map file - check the address of each symbol vs the list of missing label.
#       if addresses match - meaning this label replaces a missing one - add this label to %replaced_labels_hash and issue a note
#    d. go over %missing_labels_hash and issue a note for each label which doesnt exist in
#       %replaced_labels_hash - meaning this label is missing and it wasn't replcaed by another.
#
# IMPORTANT VARIABLES:
#
# %fixed_labels_hash - this hash table holds all the fixed labels
# 					the key of this hash is the name of the label
# 					the value is the address - when the list is first loaded
# 					the address is assigned value of -99999. after map file
# 					is read the actual addresses are loaded into the hash
# %missing_labels_hash - this hash table holds all the fixed labels which
#                        exist in the reference file but not in the current
#                        map file.
#                        the key of this hash is the name of the label
# 	                     the value is the address
# %replaced_labels_hash - this hash tables holds all the fixed labels which
#  						  exist in the reference file but not in the current
# 						  map file - a new label exist in their addresses
#                         the key of this hash is the name of the label
# 	                      the value is '1'
#
# HISTORY:
# Nissan Aloni   04-06-2006		Original.
# Nissan Aloni   11-06-2006		1. addresses are printed to file in hexa
#                                  format and not in decimal.
#                               2. only labels which were found in current
#                                  map file are printed, i.e. label which
#                                  have address of -99999 are not printed
#                                  to output file
# 								3. exit statuses are changed to 0 - prevent
# 									build process from failing.
# 								4. new method for comparing reference file
# 									and current labels list
#
############################################################################
use strict;
print "\n\n";
print "***************************\n";
print "BA_Compare_Fixed_Labelss.pl\n";
print "***************************\n";

############################################################################
# STEP 1 - ANALYZE ARGUMENTS & INITIALIZE VARIABLES
############################################################################
my $num_args = $#ARGV + 1;
if ($num_args != 2 ) {
	print "Error in number of arguments !!!\n";
	print "Usage:  BA_Compare_Fixed_Labels.pl <Name Of BA Directory> <Map file name>\n"; 
	print "Example: BA_Compare_Fixed_Labels.pl Tavor_A0_BA TavorA0.map\n";
	exit;
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
			exit;
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
	exit;
}

my $fixed_symbols_file_path = "$BA_dir_path\\Fixed_Labels_${build_scenario}.txt";
my $map_file_path = "..\\bin\\$map_fn";;
my $fixed_labels_address_file_path = "..\\bin\\Fixed_Labels_Addresses_${build_scenario}.txt";
my $reference_addresses_file_path = "$BA_dir_path\\Fixed_Labels_Addresses_Reference_${build_scenario}.txt";

# WRITE NAMES OF INPUTS / OUTPUTS FILES
print "\n";
print "INPUT:\n";
print "------\n";
print "\t$macro_path\n";
print "\t$fixed_symbols_file_path\n";
print "\t$map_file_path\n";
print "\t$reference_addresses_file_path\n";
print "\n";
print "OUTPUT:\n";
print "------\n";
print "\t$fixed_labels_address_file_path\n";
print "\n";
print "\n";

############################################################################
# STEP 2 - LOAD FIXED LABELS LIST INTO HASH TABLE
############################################################################
if (!(-e "$fixed_symbols_file_path")) {
  print "Can't access $fixed_symbols_file_path\n";
  exit 1;
}
open (FIXED_SYMBOLS_FILE_HANDLE,$fixed_symbols_file_path) || die "Can't open $fixed_symbols_file_path\n";
my %fixed_labels_hash = ();
while(<FIXED_SYMBOLS_FILE_HANDLE>) {
	my $cur_line = $_;
	chomp $cur_line;
	$fixed_labels_hash{$cur_line} = "-99999";
}
close(FIXED_SYMBOLS_FILE_HANDLE);

############################################################################
# STEP 3 - GO OVER "LABELS TABLE" IN THE MAP FILE AND UPDATE
# 			fixed_labels_hash WITH THE ADDRESSES OF ALL THE LABELS
############################################################################
if (!(-e "$map_file_path")) {
  print "Can't access map file - $map_file_path\n";
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
			my @LineAr = split(qq( ),$map_lines_array[$i]);
			my $map_label = $LineAr[0];
			if (exists $fixed_labels_hash{$map_label}) {
				$fixed_labels_hash{$map_label} = hex($LineAr[1]);
			}
		}
	}
}
close(MAP_FILE_HANDLE);

############################################################################
# STEP 4 - WRITE THE HASH TABLE - fixed_labels_hash - TO OUTPUT FILE
############################################################################
open (FIXED_LABELS_ADDRESSES_FILE_HANDLE,">$fixed_labels_address_file_path") || die "Can't open $fixed_labels_address_file_path";
# PRINT ALL THE LABELS WITH THEIR ADDRESS TO OUTPUT FILE
# PRINT IN SORTED WAY
sub hashValueAscendingNum {
   $fixed_labels_hash{$a} <=> $fixed_labels_hash{$b};
}
my $key;
foreach $key (sort hashValueAscendingNum (keys(%fixed_labels_hash))) {
	if ($fixed_labels_hash{$key} != -99999 ) {
		my $hex_address = sprintf "0x%lx", $fixed_labels_hash{$key};
   		print FIXED_LABELS_ADDRESSES_FILE_HANDLE "$key $hex_address\n";
	}
	else {
		# THIS DELETE IS IMPORTANT SINCE IT ENABLES A QUICK CHECK LATER ON
		# WE CHECK WHETHER EACH LABEL IN THE REFERENCE FILE EXISTS
		# IN THE CURRENT MAP FILE OR NOT
		delete $fixed_labels_hash{$key};
	}
}
close(FIXED_LABELS_ADDRESSES_FILE_HANDLE);


############################################################################
# STEP 5 - COMPARE REFERENCE FILE TO CURRENT ADDRESSES OF LABELS &
#          ISSUE WARNINGS & NOTES
############################################################################
my @warn_list = ();
if (!(-e "$reference_addresses_file_path")) {
  print "Can't access file - $reference_addresses_file_path\n";
  exit;
}
my %missing_labels_hash = ();
open (REF_ADDRESS_FILE_HANDLE,$reference_addresses_file_path) || die "Can't open $reference_addresses_file_path\n";
# ------------------------------------------------------------------------
# LOOP OVER REFERENCE FILE - FOR EACH LABEL - CHECK IF THAT LABEL WAS FOUND
# IN THE CURRENT MAP FILE - IF NOT ADD IT TO THE MISSING LABELS LIST.
# ALSO - CHECK THAT THE ADDRESS OF EACH LABEL IS EQUAL TO THE ADDRESS AT THE
# REFERENCE FILE
# ------------------------------------------------------------------------
while(<REF_ADDRESS_FILE_HANDLE>) {
	my @LineAr = split(qq( ),$_);
	if (!(exists $fixed_labels_hash{$LineAr[0]})) {
		$missing_labels_hash{$LineAr[0]} = $LineAr[1];
	}
	else {
		# CHECK REFERENCE ADDRESS VS. CURRENT ADDRESS
		my $label = $LineAr[0];
		my $dec_address = hex $LineAr[1];
		if ( $fixed_labels_hash{$label} != $dec_address ) {
			# APPEND WARNING TO WARNING LIST
			$warn_list[$#warn_list+1] = "\tThe address of $label has changed\n";
		}
	}
}
close(REF_ADDRESS_FILE_HANDLE);
if ($#warn_list > 0) {
	print "---------\n";
	print "WARNINGS:\n";
	print "---------\n";
	print @warn_list;
}



# ------------------------------------------------------------------------
# GO OVER ALL THE MISSING LABELS AND LIST THE CURRENT LABELS AT THOSE
# ADDRESSES - ACCORDING TO THE NEW MAP FILE
# ------------------------------------------------------------------------
my @note_list = ();
$found_labels_table_flag = 0;
my %replaced_labels_hash = ();
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
			my @LineAr = split(qq( ),$map_lines_array[$i]);
			my $label;
			my $address;
			# MATCH THE CURRENT ADDRESS IN THE MAP FILE TO THE
			# LIST OF MISSING LABELS - IF ADDRESSES MATCH THEN ADD THIS LABEL
			# TO THE REPLACED LIST
			while ( ($label,$address) = each %missing_labels_hash)
			{
				if ( $address eq $LineAr[1] ) {
					# APPEND WARNING TO WARNING LIST
					$note_list[$#note_list+1] = sprintf "%-47s\twas replaced by\t%-47s\t%s\n", $label,$LineAr[0],$LineAr[1];
					$replaced_labels_hash{$label} = 1;
				}
			}
		}
	}
}

# ------------------------------------------------------------------------
# LIST ALL THE MISSING LABELS THAT COULDN'T BE MATCHED (BY ADDRESS)
# TO NEW LABELS IN THE MAP FILE
# ------------------------------------------------------------------------
foreach $key (keys %missing_labels_hash) {
	if (!(exists $replaced_labels_hash{$key})) {
		# APPEND WARNING TO WARNING LIST
		$note_list[$#note_list+1] = sprintf "%-47s\twasn't found & no other label was found at that address\n", $key;
	}
}

if ($#note_list > 0) {
	print "------\n";
	print "NOTES:\n";
	print "------\n";
	print sort @note_list;
}
exit;
