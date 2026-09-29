#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/bin/perl -w

############################################################################
#
# NAME: BA_BFF_VALIDATE_FROZEN_OUTPUT_SECTIONS.pl
#
# PURPOSE:
# --------
# THIS SCRIPT WILL VALIDATE THE OUTPUT SECTIONS OF THE FROZEN LABELS:
# 1. THEY APPEAR FIRST IN THIER MEMORIES
# 2. THEY CONTAIN ONLY INPUT SECTIONS OF FROZEN LABELS
#
# ARGUMENTS:
# ----------
# 1. BA CURRENT DIRECTORY
# 2. MAP FILE NAME
# 3. Input File For BFF Validation Scripts (Used For List Of Valid Input Sections)
#
#
# USAGE EXAMPLE:
# --------------
# BA_BFF_VALIDATE_FROZEN_OUTPUT_SECTIONS.pl Tavor_BA_M05 Tavor_B0_AI_M05_BFF.map Input_For_BFF_Validation_Scripts.txt
#
#
# STEPS:
# ------
# 1. WELCOME MESSAGE
# 2. ANALYZE ARGUMENTS & OPEN INPUT FILES
# 3. LOAD THE INPUT FILE FOR THE VALIDATION SCRIPT
# 	 THIS IS THE "CONFIGURATION" FILE
# 4. VALIDATE OUTPUT SECTIONS ARE FIRST IN THIER MEMORIES
# 5. CHECK THAT EACH OUTPUT SECTION CONTAINS ONLY VALID INPUT SECTION
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
print "\n\n************************************** \n";
print "BA_BFF_VALIDATE_FROZEN_OUTPUT_SECTIONS \n";
print "************************************** \n\n";
print "INPUT FILES:\n";
print "\t1. MAP FILE\n";
print "\t2. Input_For_BFF_Validation_Scripts.txt\n";
print "\n";

############################################################################
# STEP 2 - ANALYZE ARGUMENTS & OPEN INPUT FILES
############################################################################
my $num_args = $#ARGV + 1;
if ($num_args != 3 ) {
	print "$num_args\n";
	print "ERROR IN ARGUMENTS\n";
	print "Usage:\n\t BA_BFF_VALIDATE_FROZEN_OUTPUT_SECTIONS.pl <BA_CURRENT_DIRECTORY> <MAP_FILE_NAME> <Input_File_For_BFF_Validation_Scripts>\n"; 
	print "Example: BA_BFF_VALIDATE_FROZEN_OUTPUT_SECTIONS.pl Tavor_BA_M05 Tavor_B0_AI_M05_BFF.map Input_For_BFF_Validation_Scripts.txt \n";
	exit 1;
}
my $BACurrentDirectory    = $ARGV[0];
my $MapFile				  = $ARGV[1];
my $MapFilePath = "..\\bin\\$MapFile";
open (MapFileHandle, $MapFilePath) || die "CAN'T OPEN - $MapFilePath \n";
my $InputFileForBFFValidation = $ARGV[2];
my $InputFileForBFFValidationPath = "$BACurrentDirectory\\$InputFileForBFFValidation";
open (InputFileForBFFValidationHandle, $InputFileForBFFValidationPath) || die "CAN'T OPEN - $InputFileForBFFValidationPath \n";

############################################################################
# STEP 3 - LOAD THE INPUT FILE FOR THE VALIDATION SCRIPT
# 		   THIS IS THE "CONFIGURATION" FILE
############################################################################
my @Lines = <InputFileForBFFValidationHandle>;
my $i = 1;
my @SplittedLine;
my %ToBeValidatedOutputSectionsHash;
while ($i <= $#Lines) {
	if (!($Lines[$i] =~ /^#/ )) { # SKIP LINES THAT START WITH '#'
		@SplittedLine = split(qq( ),$Lines[$i]);

		# ADD THE OUTPUT SECTION TO THE ARRAY OF OUTPUT SECTIONS TO BE VALIDATED
		$ToBeValidatedOutputSectionsHash{$SplittedLine[0]} = $SplittedLine[1];
	}
	$i = $i + 1;
}

############################################################################
# STEP 4 - VALIDATE OUTPUT SECTIONS ARE FIRST IN THIER MEMORIES
############################################################################
my $state = 0;
my $status = 0;
my %FirstOutputSectionsHash;
# CREATE A HASH WITH ALL OF THE OUTPUT SECTIONS WHICH ARE FIRST IN THIER MEMORY
while (<MapFileHandle>) {
	my $CurLine = $_;
	if ($CurLine =~ /Input objects used to create the executable image are/) {
		last; # FINISHED LOADING THE LABELS TABLE
	}
	if ( $state == 1 ) {
		# PREVIOUS LINE STARTED WITH 'Output Section'
		# SAVE THE NAME OF THIS OUTPUT SECTION INTO HASH
		my @SplittedLine = split(qq( ),$CurLine);
		$FirstOutputSectionsHash{$SplittedLine[0]} = "1";
		$state = 0;
	}
	if ($CurLine =~ /^Output Section/) {
		$state = 1; # START OF LIST OF OUTPUT SECTIONS
	}
	if ($CurLine =~ /Total free space available in memory/) {
		$state = 0; # END OF LIST OF OUTPUT SECTIONS
	}
}
# GO OVER LIST OF OUTPUT SECTION THAT WERE TAKEN FROM CONFIGURATION FILE
# CHECK THAT EACH ONE OF THEM APPEARS IN THE HASH OF FIRST OUTPUT SECTIONS
while ( my ($key, $value) = each(%ToBeValidatedOutputSectionsHash) ) {
	my $OutputSectionName = $key;
	if (!(exists $FirstOutputSectionsHash{$OutputSectionName})) {
		print "ERROR:\t$OutputSectionName is a frozen label output section according to $InputFileForBFFValidation\n";
		print "\tHowever, it is not at the top of its memory segment\n\n";
		$status = -1;
	}
}

############################################################################
# STEP 5 - CHECK THAT EACH OUTPUT SECTION CONTAINS ONLY VALID INPUT SECTION
############################################################################
$state = 0;
my $CurOutputSection;
while (<MapFileHandle>) {
	my $CurLine = $_;
	if ($CurLine =~ /The overlays which belong to the/) {
		last;
	}
	if ($CurLine =~ /^\s*$/) {
		# AN EMPTY LINE MEANS THAT THERE ARE NO MORE INPUT SECTIONS FOR THIS
		$state = 1;
	}
	if ($CurLine =~ /No input section mapped/) {
		# NO MORE INPUT SECTIONS FOR THIS OUTPUT SECTION
		$state = 1;
	}
	if ( $state == 2 ) {
		# WE ARE READING A LINE WITH AN INPUT SECTION OF AN OUTPUT SECTION THAT SHOULD BE VALIDTED
		my @SplittedLine = split(qq( ),$CurLine);

		# CHECK THAT THE INPUT SECTION MATCHES THE ONE THAT WE EXPECT
		if ($SplittedLine[0] ne $ToBeValidatedOutputSectionsHash{$CurOutputSection}) {
			print "ERROR:\tThe frozen label output section '$CurOutputSection' contains a non frozen input section '$SplittedLine[0]'\n\n";
			$status = -1;
		}
	}
	if ( ($CurLine =~ /^Output Section (.*)/) && ($state == 1) ){
		$CurOutputSection = $1;

		# CHECK IF THIS OUTPUT SECTION SHOULD BE VALIDATED
		if (!(exists $ToBeValidatedOutputSectionsHash{$CurOutputSection})) {
			next;
		}

		# SKIP NEXT LINE (IT IS A HEADER) - 'Input section                  Address      Size        Input file'
		$_ = <MapFileHandle>;

		$state = 2;
	}
	if ($CurLine =~ /Input sections that map into the given output sections/) {
		$state = 1;
	}
}

if ( $status == 0 ) {
	print "SUCCESS:\tThe frozen label output sections are holding only frozen label input sections\n";
	print "\t\tThe frozen label output sections were found at the top of thier physical memories\n\n\n";
}

exit ($status);

