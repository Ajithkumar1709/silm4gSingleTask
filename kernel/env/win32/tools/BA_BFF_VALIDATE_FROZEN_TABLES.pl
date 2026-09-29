#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/bin/perl -w

############################################################################
#
# NAME: BA_BFF_VALIDATE_FROZEN_TABLES.pl
#
# PURPOSE:
# --------
# This script will validate the entries in the 3 frozen tables - GAT / ADAPTATION / SW HOOK.
# It will make sure that only valid labels are inside those tables.
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
# BA_BFF_VALIDATE_FROZEN_TABLES.pl Tavor_BA_M05 Tavor_B0_AI_M05_BFF.map Input_For_BFF_Validation_Scripts.txt
#
#
# STEPS:
# ------
# 1. WELCOME MESSAGE
# 2. ANALYZE ARGUMENTS & OPEN INPUT FILES
# 3. LOAD THE INPUT FILE FOR THE VALIDATION SCRIPT
# 	 THIS IS THE "CONFIGURATION" FILE
# 4. LOAD THE LABELS FROM THE MAP FILE "DEMANGLED" TABLE INTO A HASH
# 5. GO OVER THE "Demangled" TABLE IN THE MAP FILE:
# 	    IF THE CURRENT INPUT SECTION SHOULD NOT BE VALIDATED - CONTINUE
# 	    IF THE CURRENT LABEL IS EQUAL TO THE CURRENT INPUT SECTION - CONTINUE
#       IF THE COMPARISON TYPE IS 1 :
# 	 		IF THE LABEL MATCHES THE REGULAR EXPRESSION - CONTINUE
# 	 		ELSE ISSUE AN ERROR
#       IF THE COMPARISON TYPE IS 0 :
# 	  		1. IF THE LABEL END WITH .end - ADD THE SUFFIX TO THE MIDDLE
# 	  			ELSE ADD THE SUFFIX TO THE END OF THE LABEL
# 			2. SEARCH THE NEW LABEL IN THE LABELS HASH TABLE -
# 				IF EXISTS - CONTINUE
# 				ELSE ISSUE AN ERROR#
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
print "\n\n***************************** \n";
print "BA_BFF_VALIDATE_FROZEN_TABLES \n";
print "***************************** \n\n";
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
	print "Usage:\n\tBA_BFF_VALIDATE_FROZEN_TABLES.pl <BA_CURRENT_DIRECTORY> <MAP_FILE_NAME> <Input_File_For_BFF_Validation_Scripts>\n"; 
	print "Example: BA_BFF_VALIDATE_FROZEN_TABLES.pl Tavor_BA_M05 Tavor_B0_AI_M05_BFF.map Input_For_BFF_Validation_Scripts.txt \n";
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
my %ConfigurationHash;
while ($i <= $#Lines) {
	if (!($Lines[$i] =~ /^#/ )) { # SKIP LINES THAT START WITH '#'
		@SplittedLine = split(qq( ),$Lines[$i]);

		# INSERT THE SPLITTED LINE INTO A HASH - THE KEY IS THE INPUT SECTION
		# THIS SYNTAX SAVES THE SPLITTED LINE INTO THE HASH
		$ConfigurationHash{$SplittedLine[1]} = [$SplittedLine[0],$SplittedLine[1],$SplittedLine[2],$SplittedLine[3]];
	}
	$i = $i + 1;
}

############################################################################
# STEP 4 - LOAD THE LABELS FROM THE MAP FILE "DEMANGLED" TABLE INTO A HASH
############################################################################
my %MapLabelsHash;
my $state = 0;
while (<MapFileHandle>) {
	my $CurLine = $_;

	# CHECK IF WE ARE IN THE "DEMANGLED" TABLE
	if ( $state == 1 ) {
		# SPLIT THE LINE
		my @SplittedLine = split(qq( ),$CurLine);

		# ADD THE LABEL TO THE HASH
		$MapLabelsHash{$SplittedLine[0]} = "1";
	}
	if ( $CurLine =~ /Demangled Name/) {
		$state = 1;
	}
	if ($CurLine =~ /Input sections that map into the given output sections/) {
		last; # FINISHED LOADING THE LABELS TABLE
	}
}

############################################################################
# STEP 5 - GO OVER THE "Demangled" TABLE IN THE MAP FILE:
# 		   IF THE CURRENT INPUT SECTION SHOULD NOT BE VALIDATED - CONTINUE
# 		   IF THE CURRENT LABEL IS EQUAL TO THE CURRENT INPUT SECTION - CONTINUE
#          IF THE COMPARISON TYPE IS 1 :
# 				IF THE LABEL MATCHES THE REGULAR EXPRESSION - CONTINUE
# 				ELSE ISSUE AN ERROR
#          IF THE COMPARISON TYPE IS 0 :
# 				1. IF THE LABEL END WITH .end - ADD THE SUFFIX TO THE MIDDLE
# 				ELSE ADD THE SUFFIX TO THE END OF THE LABEL
# 				2. SEARCH THE NEW LABEL IN THE LABELS HASH TABLE -
# 					IF EXISTS - CONTINUE
# 					ELSE ISSUE AN ERROR#
############################################################################
my $state = 0;
seek (MapFileHandle,0,0); # REWIND THE FILE HANDLER
my $status = 0;
while (<MapFileHandle>) {
	my $CurLine = $_;

	# CHECK IF WE ARE IN THE "DEMANGLED" TABLE
	if ( $state == 1 ) {
		# SPLIT THE LINE
		my @SplittedLine = split(qq( ),$CurLine);
		my $CurInputSection = $SplittedLine[5];
		my $CurLabel = $SplittedLine[0];

		# CHECK IF THE CURRENT INPUT SECTION SHOULD BE VALIDATED
		if (!(exists $ConfigurationHash{$CurInputSection})) {
			next; # CONTINUE SINCE NO NEED TO VALIDATE THIS INPUT SECTION
		}

		# CHECK IF THE LABEL IS EQUAL TO THE INPUT SECTION
		if ($CurInputSection eq $CurLabel) {
			next; # CONTINUE SINCE THE LABEL IS THE SAME AS THE INPUT SECTION
		}

		# COMPARISON TYPE 1
		if ($ConfigurationHash{$CurInputSection}[3] eq "1") {
			if (!($CurLabel =~ $ConfigurationHash{$CurInputSection}[2])) {
				print "ERROR:\tThe label '$CurLabel' is located in the input section '$CurInputSection'\n";
				print "\tHowever, this section should hold only permitted frozen labels (stated in $InputFileForBFFValidation)\n\n";
				$status = -1;
			}
		}

		# COMPARISON TYPE 0
		if ($ConfigurationHash{$CurInputSection}[3] eq "0") {
			my $UpdatedLabel;
			if ($CurLabel =~ /\.end/) {
				# ADD THE SUFFIX BEFORE THE '.END'
				my $i = index($CurLabel, ".end");
				$UpdatedLabel = substr ($CurLabel , 0 , $i);
				$UpdatedLabel = "$UpdatedLabel$ConfigurationHash{$CurInputSection}[2].end";
			}
			else {
				# ADD THE SUFFIX AT THE END OF THE LABEL
				$UpdatedLabel = "$CurLabel$ConfigurationHash{$CurInputSection}[2]";
			}
			# CHECK IF THE UPDATED LABEL APPEARS IN THE LABELS HASH TABLE
			if (!(exists $MapLabelsHash{$UpdatedLabel})) {
				print "ERROR:\tThe label '$CurLabel' is located in the input section '$CurInputSection' \n";
				print "\tHowever, this seems to be an invalid entry since the label '$UpdatedLabel' could not be found \n\n";
				$status = -1;
			}
		}
	}
	if ( $CurLine =~ /Demangled Name/) {
		$state = 1;
	}
	if ($CurLine =~ /Input sections that map into the given output sections/) {
		last; # FINISHED LOADING THE LABELS TABLE
	}
}

if ( $status == 0 ) {
	print "SUCCESS:\tOnly valid frozen labels were found in the input section that are authorized for frozen label\n\n\n";
}

exit ($status);

