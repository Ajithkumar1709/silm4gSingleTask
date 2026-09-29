#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/bin/perl -w

############################################################################
#
# NAME: BA_BFF_VALIDATE_FROZEN_LABELS.pl
#
#
# PURPOSE:
# --------
# This script will validate that all the RAM labels which are referenced from ROM
# are mapped to one of the valid input sections
#
#
# ARGUMENTS:
# ----------
# 1. BA CURRENT DIRECTORY
# 2. Files_Sections_list_<BUILD_TYPE>.txt
# 3. Input File For BFF Validation Scripts (Used For List Of Valid Input Sections)
#
#
# USAGE EXAMPLE:
# --------------
# BA_BFF_VALIDATE_FROZEN_LABELS.pl Tavor_BA_M05 Files_Sections_list_ALL_IN_ROM.txt Input_For_BFF_Validation_Scripts.txt
#
#
# STEPS:
# ------
# 1. WELCOME MESSAGE
# 2. ANALYZE ARGUMENTS & OPEN INPUT FILES
# 3. LOAD VALID INPUT SECTIONS INTO HASH
# 4. GO OVER "Part 1: RAM Referenced From ROM" IN "Files_Sections_list_<BUILD_TYPE>.txt"
#    AND VALIDATE ALL OF THE LABELS
#    From "Part 2:..." - Check only labels which are mapped to RAM during runtime
#
#
# HISTORY:
# --------
# Nissan Aloni   30-07-2007		Original.
#
############################################################################

use strict;

############################################################################
# STEP 1 - WELCOME MESSAGE
############################################################################
print "\n\n*****************************\n";
print "BA_BFF_VALIDATE_FROZEN_LABELS\n";
print "*****************************\n\n";
print "INPUT FILES:\n";
print "\t1. Files_Sections_list_<BUILD_TYPE>.txt\n";
print "\t2. Input_For_BFF_Validation_Scripts.txt\n";
print "\n";

############################################################################
# STEP 2 - ANALYZE ARGUMENTS & OPEN INPUT FILES
############################################################################
my $num_args = $#ARGV+1;
if ($num_args != 3 ) {
	print "ERROR IN ARGUMENTS\n";
	print "Usage:\n\tBA_BFF_VALIDATE_FROZEN_LABELS.pl <BA_CURRENT_DIRECTORY> <Files_Sections_list_*> <Input_File_For_BFF_Validation_Scripts>\n"; 
	print "Example: BA_BFF_VALIDATE_FROZEN_LABELS.pl Tavor_BA_M05 Files_Sections_list_ALL_IN_ROM.txt Input_For_BFF_Validation_Scripts.txt\n"; 
	exit 1;
}
my $BACurrentDirectory    = $ARGV[0];
my $FilesSectionsList     = $ARGV[1];
my $FilesSectionsListPath = "$BACurrentDirectory\\$FilesSectionsList";
open (FilesSectionsListHandle, $FilesSectionsListPath) || die "CAN'T OPEN - $FilesSectionsListPath\n";
my $InputFileForBFFValidation = $ARGV[2];
my $InputFileForBFFValidationPath = "$BACurrentDirectory\\$InputFileForBFFValidation";
open (InputFileForBFFValidationHandle, $InputFileForBFFValidationPath) || die "CAN'T OPEN - $InputFileForBFFValidationPath \n";

############################################################################
# STEP 3 - LOAD VALID INPUT SECTIONS INTO HASH
############################################################################
my @Lines = <InputFileForBFFValidationHandle>;
my $i = 1;
my @SplittedLine;
my %InputSectionsHash;
while ($i <= $#Lines) {
	if (!($Lines[$i] =~ /^#/ )) { # SKIP LINES THAT START WITH '#'
		@SplittedLine = split(qq( ),$Lines[$i]);
		$InputSectionsHash{$SplittedLine[1]} = "1";
	}
	$i = $i + 1;
}

############################################################################
# STEP 4 - GO OVER "Part 1: RAM Referenced From ROM" IN
#          "Files_Sections_list_<BUILD_TYPE>.txt"
#          AND VALIDATE ALL OF THE LABELS
############################################################################
my $return_status = 0;
my $state = 0; # INDICATES WHETHER WERE IN "PART 1" IN THE FILE
while (<FilesSectionsListHandle>) {
	my $CurLine = $_;
	if ($CurLine =~ /Part 3: ROM Referenced From RAM/) {
		# FINISHED
		last;
	}
	if ($state == 2) {                 # Part 2: ROM Referenced From ROM
		if (!($CurLine =~ /^\s*$/)) {  # CHECK THAT THIS IS NOT AN EMPTY LINE
			# TAKE ONLY THE FIRST HALF
			my $EndOfFirstHalf = index($CurLine, "is referenced in");
			$CurLine = substr ($CurLine , 0 , $EndOfFirstHalf);

			# CHECK IF IT CONTAINS THE WORDS ".*runtime memory.*(RAM).*"
			if ($CurLine =~ /runtime.*memory.*(RAM)/ ) {
				# THIS IS A FROZEN LABEL - THUS CHECK ITS INPUT SECTION
				@SplittedLine = split(qq( ),$CurLine);
				my $CurInputSection = $SplittedLine[5];
				$CurInputSection =~ s/\'//g;
				if (!(exists $InputSectionsHash{$CurInputSection})) {
					print "ERROR:\tFrozen Label $SplittedLine[1] is mapped to Input Section '$CurInputSection'\n";
					print "\tThis input section is not valid for frozen labels (according to $InputFileForBFFValidation)\n";
					print "\tIt was found in 'Part 2: ROM (runtime is SRAM) Referenced From ROM'\n\n";
					$return_status = -1;
				}
			}
		}
	}

	if ($CurLine =~ /Part 2: ROM Referenced From ROM/) {
		$state = 2;
	}
	if ($state == 1) {                 # Part 1: RAM Referenced From ROM
		if (!($CurLine =~ /^\s*$/)) {  # CHECK THAT THIS IS NOT AN EMPY LINE
			@SplittedLine = split(qq( ),$CurLine);
			my $CurInputSection = $SplittedLine[5];
			$CurInputSection =~ s/\'//g;
			if (!(exists $InputSectionsHash{$CurInputSection})) {
				print "ERROR:\tFrozen Label $SplittedLine[1] is mapped to Input Section '$CurInputSection'\n";
				print "\tThis input section is not valid for frozen labels (according to $InputFileForBFFValidation)\n";
				print "\tIt was found in 'Part 1: RAM Referenced From ROM'\n\n";
				$return_status = -1;
			}
		}
	}
	if ($CurLine =~ /Part 1: RAM Referenced From ROM/) {
		$state = 1;
	}
}

if ( $return_status == 0 ) {
	print "SUCCESS:\tAll frozen labels are verfied to be mapped to legal input sections\n\n\n";
}
exit ($return_status);

