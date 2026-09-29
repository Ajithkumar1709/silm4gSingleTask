#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/bin/perl -w
############################################################################
#
# PURPOSE:
# COMPARE 2 BANK FILES. IF THEY ARE NOT IDENTICAL -
# CALCULATE THE ADDRESS OF THE DIFFERENCE AND THEN LOCATE THE LABEL THAT
# CHANGEDIN IN THE MAP FILE
#
# STEPS:
# 1. ANALYZE ARGUMENTS & INITIALIZE VARIABLES
# 2. COMPARE THE BANKS USING "FC" - AND EXIT IF THEY ARE IDENTICAL
# 3. FIND LINE OF MISMATCH BETWEEN BANKS
# 4. CALCULATE ABSOLUTE ADDRESS IN MAP FILE
# 5. CREATE A LIST OF LABELS FROM THE MAP FILE (WITH SIZE != 0)
# 6. SORT THE LIST OF LABELS EXTRACTED FROM THE MAP FILE
#
# IMPORTANT VARIABLES:
# absolute_address - this is the decimal address in which the first
# 					difference was detected.
# labels_list - contains a list of labels from the map file. these are all
# 				the labels which are located in the current bank - according
# 				to thier addresssed.
# address_hash - this is a hash of all of the labels in the current bank.
# 				IMPORTANT NOTE - some labels share the starting address thus
# 				using the address as the key caused tramping over older values.
# first_prev_address - this is the address of the first avialbale label
# 						which is previous to $absolute_address
#
# HISTORY:
# Nissan Aloni   01-07-2006		Original.
# Nissan Aloni   18-07-2006		BUGFix - new method for comparing banks -
# 								without using the "fc" output.
# 								added a "DEBUG" flag - can be set to 1
# 								for debugging.
#
############################################################################
use strict;
my $DEBUG = 0;

############################################################################
# STEP 1 - ANALYZE ARGUMENTS & INITIALIZE VARIABLES
############################################################################
my $num_args = $#ARGV + 1;
if ($num_args != 7 ) {
	print "Error in number of arguments !!!\n";
	print "Usage:  BA_compare_banks.pl <Map file name> <Name Of Reference Bank> <Name Of Bank> -S <start address - hexa> -E <end address - hexa>\n"; 
	print 'Example: BA_compare_banks.pl TavorA0.map ..\bin\L2_BK5_ROM.init Tavor_A0_ROM\L2_BK5_ROM_A0.init -S 0xD1EC0000 -E 0xD1EDFFFF\n';
	exit 1;
}
my $map_fn;
$map_fn = $ARGV[0];
my $ref_bank_path = $ARGV[1];
my $cur_bank_path = $ARGV[2];
my $bank_start_address;
$bank_start_address = hex($ARGV[4]);
my $bank_end_address;
$bank_end_address = hex($ARGV[6]);

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

############################################################################
# STEP 2 - COMPARE THE BANKS USING "FC" - AND EXIT IF THEY ARE IDENTICAL
############################################################################
my $return_value = system ("fc $ref_bank_path $cur_bank_path > fc_output");
if ($return_value == 0) {
	# NO CHANGE WAS DETECTED
	exit;
}

############################################################################
# STEP 3 - FIND LINE OF MISMATCH BETWEEN BANKS
############################################################################
open (REF_BANK_HANDLE,$ref_bank_path) || die "Can't open $ref_bank_path \n";
open (CUR_BANK_HANDLE,$cur_bank_path) || die "Can't open $cur_bank_path \n";
my $ref_line;
my $cur_line;
my $error_flag = 0;
while(<REF_BANK_HANDLE>) {
	$ref_line = $_;
	$cur_line = <CUR_BANK_HANDLE>;
	if (!defined($cur_line) ) {
		print "!!! ERROR !!!\n";
		print "$ref_bank_path is longer than $cur_bank_path\n";
		exit 1;
	}
	if ( $ref_line ne $cur_line) {
		chomp ($ref_line);
		chomp ($cur_line);
		$error_flag = 1;
		last;
	}
}
if ( $error_flag == 0 ) {
	if (defined($cur_line)) {
		print "!!! ERROR !!!\n";
		print "$cur_bank_path is longer than $ref_bank_path \n";
		exit 1;
	}
}
if ( $DEBUG == 1 ) {
	print "Banks mismath at:\n";
	print "$ref_line\n";
	print "$cur_line\n";
}

close (REF_BANK_HANDLE);
close (CUR_BANK_HANDLE);

my @LineAr = split(qq( ),$ref_line);
my $ref_data = $LineAr[1];
@LineAr = split(qq( ),$cur_line);
my $cur_data = $LineAr[1];

############################################################################
# STEP 4 - CALCULATE ABSOLUTE ADDRESS IN MAP FILE
############################################################################
# THE LINE WITH THE DIFFERENCE BETWEEN THE 2 BANKS IS A LIST OF 16 CHARACTERS WHICH REPRESENT 8 BYTES
# NOW WE WILL COMPARE THE 2 LINES BYTE-TO-BYTE AND LOCATE THE PROBLEMATIC BYTE
# THE COUNT IS FROM RIGHT TO LEFT (FROM BYTE NUMBER 0 TILL BYTE NUMBER 7)
# MEANING:
# BYTE NUMBER 0 IS LOCATES AT CHARS 14-15
# BYTE NUMBER 7 IS LOCATES AT CHARS 0-1
my $diff_byte_index_RTL;
for($diff_byte_index_RTL=0;$diff_byte_index_RTL <= 7;$diff_byte_index_RTL+=1) {
	my $char_start = 14 - $diff_byte_index_RTL * 2;
if ( $DEBUG == 1 ) {
	my $s1 = substr($ref_data,$char_start,2);
	my $s2 = substr($cur_data,$char_start,2);
	print "Comparing the following parts of the line with the difference:\n";
	print "\tFrom ref_data: $s1\n";
	print "\tFrom cur_data: $s2\n";
}
	if (substr($ref_data,$char_start,2) ne substr($cur_data,$char_start,2)) {
		last;
	}
}

# AND NOW TO THE ACTUAL ADDRESS (ADDRESS IN MAP FILE)
@LineAr = split(qq( ),$cur_line);
my $absolute_address = $bank_start_address + (hex($LineAr[0]) * 8) + $diff_byte_index_RTL;
if ( $DEBUG == 1 ) {
	printf ("MISMATCH is located at absolute address: 0x%lx + (0x%lx * 8) + 0x%lx = 0x%lx\n",$bank_start_address,hex($LineAr[0]),$diff_byte_index_RTL,$absolute_address);
}

############################################################################
# STEP 5 - CREATE A LIST OF LABELS FROM THE MAP FILE (WITH SIZE != 0)
############################################################################
if ( $DEBUG == 1 ) {
	printf ("\n\nExtracting labels from the MAP, these labels are inside the current bank - according to thier address");
}
my $map_file_path;
$map_file_path = "..\\bin\\$map_fn";;
if (!(-e "$map_file_path")) {
  print "Can't access map file - $map_file_path";
  exit 1;
}
open (MAP_FILE_HANDLE,$map_file_path) || die "Can't open $map_file_path\n";

my @map_lines_array = <MAP_FILE_HANDLE>;
my $found_labels_table_flag = 0;
my @labels_list;
my %address_hash;
my $i;
#print "Extracting labels from MAP\n";
for($i=0;$i<=$#map_lines_array;$i++) {
	if ( $found_labels_table_flag == 1 ) {
		# END OF LABELS TALBE
		if ( $map_lines_array[$i] =~ (/^\s*$/) ) {
			last;
		}
		else  {
			@LineAr = split(qq( ),$map_lines_array[$i]);
			my $cur_address = hex($LineAr[1]);
			my $cur_size = hex($LineAr[2]);
			if ($cur_size != 0) {
				#print "adding $LineAr[0] since it is in the bank\n";
				$labels_list[$#labels_list+1] = $map_lines_array[$i];
				$address_hash{$cur_address} = $cur_address;
			}
		}
	}
	# FOUND THE FIRST LINE OF THE LABELS PART
	if ($map_lines_array[$i] =~ /Name                          Demangled Name                 Address      Size        Binding     Filename/ ) {
		$found_labels_table_flag = 1;
	}
}
close(MAP_FILE_HANDLE);

if ( $DEBUG == 1 ) {
	printf ("\n\n@labels_list\n");
}

############################################################################
# STEP 6 - SORT THE LIST OF LABELS EXTRACTED FROM THE MAP FILE
############################################################################
if ( $DEBUG == 1 ) {
	printf ("\n\nSorting the list of labels\n");
}

# SORT THE LIST OF LABELS TAKEN FROM THE MAP FILE
sub by_address
{
	$address_hash{$b} <=> $address_hash{$a};
}
my @sorted_addresses = sort by_address keys %address_hash;

# ------------------------------------------------------------------------
# NOW WE SHALL START AN INFINITE LOOP
# IT WILL SELECT A PREVIOUS ADDRESS AND TRY TO MATCH A VALID LABEL TO IT
# IT WILL REPEAT THIS PROCESS - BUT NOW IT WILL SELECT A PREVIOUS
# ADDRESS WITH RESPECT TO THE PREVIOUS ONE FOUND
my $cur_respect_address = $absolute_address;
while ( 1 == 1 ) {
	my $first_prev_address;
	foreach my $tmp (@sorted_addresses) {
		if ($tmp <= $cur_respect_address) {
			$first_prev_address = $tmp;
			last;
		}
	}
	if ( $DEBUG == 1 ) {
		my $first_prev_address_hex = sprintf "0x%lx", $first_prev_address ;
		print ("\n\nFound the address that is the biggest one but still smaller than the address of the MISMATCH - $first_prev_address_hex");
	}

	if ( $DEBUG == 1 ) {
		print ("\n\nGoing over list of labels in that address and selecting the one that :\n");
		print ("\t1. doesn't have .end in its name\n");
		print ("\t2. is a true fuction label and not segment (meaning - the 0 & 5 fields in the MAP file are different\n");
	}

	for($i=0;$i<=$#labels_list;$i++) {
		@LineAr = split(qq( ),$labels_list[$i]);
		my $cur_address = hex($LineAr[1]);
		if ($cur_address == $first_prev_address) {
			if ( $DEBUG == 1 ) {
				print "\tfound a label with a good address - $LineAr[0]\n"  ;
			}
			if (($LineAr[0] =~ '\.end')||($LineAr[0] eq $LineAr[5])) {
				#nothing to do - skip it
				if ( $DEBUG == 1 ) {
					print "\tSkipping $LineAr[0]\n";
				}
			}
			else {
				my $hex_address = sprintf "0x%lx", $absolute_address;
				print "The BIN Integrity failed because of a mismatch at address $hex_address\n";
				print "The previous label in the map file is: $LineAr[0]\n";
				print "Located at DOJ file: $LineAr[4]\n";
				exit 1;
			}
		}
	}


	# WE NEED TO SUBSTRACT 1 FROM THE ADDRESS THAT WE WILL USE FOR THE NEXT ITERATION
	# IF WE DONT DO SO WE WILL GO INTO AN INFINITE LOOP - THE NEXT ADDRESS THAT WE'LL FIND
	# WILL BE EXACTLY THE SAME AS THE ONE THAT WE FOUND NOW (WE USE "<=" AND NOT "<" IN THE SEARCHING LOOP)
	$cur_respect_address = $first_prev_address - 1;

	if ( $DEBUG == 1 ) {
		my $first_prev_address_hex = sprintf "0x%lx", $first_prev_address ;
		my $cur_respect_address_hex = sprintf "0x%lx", $cur_respect_address ;
		print ("updating the respect address to $cur_respect_address_hex ($first_prev_address_hex - 1)"); # next iteration a more previous address will be found
	}
}

exit 1;
