#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/bin/perl -w


############################################################################
#
# PURPOSE:
#
# This script checks that there is no RED (Frozen label) output section
# after a GREEN (Dynamic Non Frozen) output section.
#
# THEORETICAL BACKGROUND:
#
# Output sections are labeled as follows :
# RED = frozen label
# GREEN = dynamic non frozen
# BLUE = segment fixed
# BLACK = non frozen static
#
# STEPS:
#
# 1. LOAD MACROS.MK FILE
# 2. LOAD DYNAMIC_NON_FROZEN_OUTPUT_SECTIONS_... FILE
# 3. LOAD FROZEN_LABEL_OUTPUT_SEGMENTS_LIST_... FILE
# 4. LOAD LIST OF SRAM MEMORY SEGMENTS FROM MAP FILE
# 5. LOOP OVER MAP FILE AND CHECK RULES FOR OUTPUT SECTIONS
#
# IMPORTANT VARIABLES:
#
# %ColorsHash;					# HASH TO STORE THE COLOR OF EACH OUTPUT SECTION READ SO FAR - THIS HASH CONTAINS ONLY BLUE / GREEN COLORS
# 									SINCE RED / BLACK ARE MAPPED TO GREEN / BLUE ACCORDING TO LOGICAL RULES
# %EndAddressHash;		        # HASH TO STORE THE END ADDRESS OF EACH OUTPUT SECTION READ SO FAR
# %MemorySegmentHash;		    # HASH TO STORE THE MEMORY SEGMENT OF EACH OUTPUT SECTION READ SO FAR
# %OvlLabelsHash;		        # HASH TO STORE THE OVERLAY LABELS OF EACH OUTPUT SECTION READ SO FAR
# @LineAr;						# ARRAY TO HOLD EACH SPLITTED INPUT LINE
# $templine;					# saves the current line from the map file
# $InMemorySegmentFlag = 0;    # indicates if this line an output section
								# 0 = outside of a memory segment
								# 1 = the first output section in a memory segment
								# 2 = an output section line in a memory segment
# $CurrentMemSection;			# the name of the current memory segment
# $PrevSection;				# stores the name of the previous output section
#
# HISTORY:
# Nissan Aloni   14-05-2006		Original.
# Nissan Aloni   29-05-2006     (1) added legend to *.mymap file
# 								(2) moved *.mymap file to BA directory
# 								(3) in state "13" - the address diff is calculated between the starting address of the current section and the
# 									end address the maximum previous GREEN section
# 								(4) status 1 is returned upon ERROR - in order to fail the build process
# 								(5) error message in state "14" was improved
# 								(6) Print BLUE output sections into Fixed_Output_Sections_<BuildScenario>
#
############################################################################

use strict;


# --------------------------------------------------------------------------
# THIS IS A HASH TABLE FOR PROCESSING THE ARGUMENTS
# --------------------------------------------------------------------------
my %argTable=(-h=>\&help,
		 -i=>\&Input,
		 -m=>\&MapFile,
		 -d=>\&Debug);

# --------------------------------------------------------------------------
# THIS SUBROUTINE IS USED TO DISPLAY EXPLANATIONS FOR THE USER WHEN
# HE USES THE -I FLAG OR WHEN THE ARGUEMNTS ARE WRONG
# --------------------------------------------------------------------------
sub help
{
	print "----------------------------------------------------------------------";
	print "This script checks the order of the output sections and\n";
	print "makes sure that there are no Frozen Label sections after";
	print "Dynamic Non Frozen sections.\n\n";
	print "Usage:  BA_Sections_Order_Rules.pl [-h] -i <Name Of Text File Directory> -m <Map file name> -d <Debug File Name>\n"; 
	print "Example: BA_Sections_Order_Rules.pl -i Tavor_A0_BA -m TavorA0.map -d Debug_File_Name\n";
}

# --------------------------------------------------------------------------
# THIS SUBROUTINE IS USED WHEN THE -i FLAG IS DETECTED AT THE ARGUMENTS
# IT STORES THE NAME OF THE INPUT DIRECTORY INTO $FileLibrary
# --------------------------------------------------------------------------
my $FileLibrary;
sub Input
{
	if(!defined($FileLibrary = shift @ARGV))
	{
		print "ERROR: missing File library Input\n";
		exit 1;
	}
}

# --------------------------------------------------------------------------
# THIS SUBROUTINE IS USED WHEN THE -m FLAG IS DETECTED AT THE ARGUMENTS
# IT STORES THE NAME OF THE MAP FILE INTO $MapFN
# --------------------------------------------------------------------------
my $MapFN;
sub MapFile
{
	if(!defined($MapFN = shift @ARGV))
	{
		print "ERROR: missing Map File Name\n";
		exit 1;
	}
}

# --------------------------------------------------------------------------
# THIS SUBROUTINE IS USED WHEN THE -d FLAG IS DETECTED AT THE ARGUMENTS
# IT STORED THE NAME OF THE DEBUG FILE INTO $DebugFileName
# IT TURNS $DEBUG_FLAG TO 1 AND OPENS A HANDLE TO THE FILE - DebugFileHandle
# --------------------------------------------------------------------------
my $DEBUG_FLAG = 0;
my $DebugFileName;
sub Debug
{
	if(!defined($DebugFileName = shift @ARGV))
	{
		print "ERROR: missing DEBUG File Name\n";
		exit 1;
	}
	else
 	{
		open (DebugFileHandle,">$DebugFileName") || die "cant open $DebugFileName\n" ;
		$DEBUG_FLAG = 1;
	}
}

# --------------------------------------------------------------------------
# THIS SUBROUTINE PRINTS A HASH - IT IS USEFUL FOR DEBUGGIN ETC.
# EXAMPLE : &PrintHash (%SectionsColors);
# --------------------------------------------------------------------------
sub PrintHash
{
	my %MyHash;
	my $key;
	my $value;
	(%MyHash) = @_;
	while ( ($key,$value) = each %MyHash)
	{
		print "$key => $value\n";
	}
}


# --------------------------------------------------------------------------
# OPEN MACROS.MK FILE AND READ THE FOLLOWING INFORMATION:
# $RootDirectory - S:
# $BuildScenario - WB_OUT_OF_ROM / GSM_OUT_OF_ROM ETC...
# --------------------------------------------------------------------------
my $RootDirectory;
my $BuildScenario;
my $MacroPath;
sub LoadMacrosFile
{
	$MacroPath = "macros.mk";
	open (MACRO,$MacroPath) || die "Can't open $MacroPath\n" ;
	my $templine = <MACRO>;
	while(defined($templine))
	{
			if ($templine=~/BUILD_TYPE=(.*)/)
			{
				if (( $1 !~ /BUILD_FROZEN_FILES/ ) && ( $1 !~ /BUILD_TARGET_FILES/ ))
				{
					print "Problem in $MacroPath - unknown prarm at $templine\n";
					exit 1;
				}
			}
			if ($templine=~/CBA_ROOT=(.*)/)
			{
				$RootDirectory = $1;
			}
			if ($templine=~/BUILD_SCENARIO=(.*)/)
			{
				$BuildScenario = $1;
			}
			$templine = <MACRO>;
	}
	close(MACRO);
}

# --------------------------------------------------------------------------
# READ THE Dynamic_Non_Frozen_Output_Sections_... FILE
# THIS FILE IS READ INTO $GreenHash
# THIS HASH WILL BE USED LATER TO DETERMINE IF A SECTION IS GREEN
# --------------------------------------------------------------------------
my %GreenHash = ();
my $DynamicNonFrozenFilePath;
sub LoadDynamicNonFrozenLabels
{
	my $OutPutFilesPath = $FileLibrary."\\";
	$DynamicNonFrozenFilePath = $OutPutFilesPath."Dynamic_Non_Frozen_Output_Sections_".$BuildScenario.".txt";
	open (TempHandle,$DynamicNonFrozenFilePath) || die "cant open $DynamicNonFrozenFilePath\n" ;
	my $templine = <TempHandle>;
	while(defined($templine))
	{
		if ($templine =~ /^\S/)
		{
			chomp($templine);
			$GreenHash{$templine}=1;
		}
		$templine = <TempHandle>;
	}
	close(TempHandle);
}

# --------------------------------------------------------------------------
# READ THE Frozen_Label_Output_Segments_list_ FILE
# THIS FILE IS READ INTO $RedHash
# THIS HASH WILL BE USED LATER TO DETERMINE IF A SECTION IS RED
# --------------------------------------------------------------------------
my %RedHash = ();
my $FrozenLabelFilePath;
sub LoadFrozenLabels
{
	my $OutPutFilesPath = $FileLibrary."\\";
	$FrozenLabelFilePath = $OutPutFilesPath."Frozen_Label_Output_Segments_list_".$BuildScenario.".txt";

	open (TmpHandle,$FrozenLabelFilePath) || die "cant open $FrozenLabelFilePath\n" ;
	my $templine = <TmpHandle>;
	while(defined($templine))
	{
		if ($templine =~ /^\S/)
		{
			chomp($templine);
			$RedHash{$templine}=1;
		}
		$templine = <TmpHandle>;
	}
	close(TmpHandle);
}


# --------------------------------------------------------------------------
# READ THE LIST OF MEMORY SEGMENTS FROM THE MAP FILE AND CREATE A LIST
# OF SRAM MEMORY SEGMENTS - THIS LIST IS STORED IN A HASH - $SRAMSections
# --------------------------------------------------------------------------
my %SRAMSectionsHash = ();
sub LoadSramSections
{
	my @LineAr;
	my $templine = <MapHandle>;
	while ( $templine !~ /Memory usage information.*/ )
	{
		# make sure we work with line start eith a word character
		if ($templine =~ /^w*/)
		{
			@LineAr = split(qq( ),$templine);
			if ($#LineAr >= 4  )
			{
				if ($LineAr[4] =~ /RAM/ )
				{
					# add section to SRAM hash
					$SRAMSectionsHash{$LineAr[0]} = 1;
				}
			}
		}
		$templine = <MapHandle>;
	}
}


# ------------------------------------------------------------------------
# THESE ARE GLOBAL VARIABLES USED IN THE MAIN LOOP WHICH GOES OVER THE
# MAP FILE AND CHECKS THE RULES
# THEY ARE UPDATED IN THE MarkAsGreen,MarkAsBlue SUBROUTINES
my %ColorsHash;					# HASH TO STORE THE COLOR OF EACH OUTPUT SECTION READ SO FAR
my %EndAddressHash;		        # HASH TO STORE THE END ADDRESS OF EACH OUTPUT SECTION READ SO FAR
my %MemorySegmentHash;		    # HASH TO STORE THE MEMORY SEGMENT OF EACH OUTPUT SECTION READ SO FAR
my %OvlLabelsHash;		        # HASH TO STORE THE OVERLAY LABELS OF EACH OUTPUT SECTION READ SO FAR
my @LineAr;						# ARRAY TO HOLD EACH SPLITTED INPUT LINE
my $templine;					# saves the current line from the map file
my $InMemorySegmentFlag = 0;    # indicates if this line an output section
								# 0 = outside of a memory segment
								# 1 = the first output section in a memory segment
								# 2 = an output section line in a memory segment
my $CurrentMemSection;			# the name of the current memory segment
my $PrevSection;				# stores the name of the previous output section


sub MarkAs
{
	my ($color) = @_;

	$ColorsHash{$LineAr[0]} = $color;
	$EndAddressHash{$LineAr[0]} = hex($LineAr[2]) + hex($LineAr[3]);
	$MemorySegmentHash{$LineAr[0]} = $CurrentMemSection;

	# NOT ALL OUTPUT SECTION HAVE A LIST OF OVELRAY LABELS
	if ($LineAr[4] =~ /OVERLAY/)
	{
		$OvlLabelsHash{$LineAr[0]} = $LineAr[5];
	}
	else
	{
		$OvlLabelsHash{$LineAr[0]} = "NoOVLSections";
	}

	# WRITE TO MYMAP FILE ONLY IF THIS IS A SRAM MEMORY SEGMENT
	if (exists $SRAMSectionsHash{$CurrentMemSection})
	{
		# Write this line to the MyMap file
		if ($color eq "GREEN")
		{
			print MyMapHandle "2$templine";
		}
		elsif ($color eq "BLUE")
		{
			print MyMapHandle "3$templine";
		}
		else
		{
			print "ERROR usage of MarkAs() - MarkAs($color) !!!!\n";
			exit 1;
		}
	}

}

# ------------------------------------------------------------------------
# THIS SUBROUTINE SPLITS LineAr[5] INTO A LIST OF OVERLAY LABELS
# THE LIST IS STORED AT OverlaySections
# --------------------------------------------------------------------------
my @OverlaySections;
sub SplitOverlayList
{
	@OverlaySections = qw/NO_SECTION/;
	if ($LineAr[4] =~ /OVERLAY/)
	{
		# extract the list of overlay sections
		my $temp = $LineAr[5];
		# remove '(' , ')' from beginning and end
		$temp =~ tr/)(//d;

		#$temp =~ tr/(/ /;
		#$temp =~ tr/)/ /;
		# remove leading & trailing spaces
		#$temp =~ s/^\s+//;
		#$temp =~ s/\s+$//;
		# split by ','
		@OverlaySections = split(",",$temp);
	}
}


sub by_end_address
{
	$EndAddressHash{$b} <=> $EndAddressHash{$a};
}

# --------------------------------------------------------------------------
# Find previous section with MAX end address with a different OVL_START label
# --------------------------------------------------------------------------
sub FindPreviousSectionForOverlayStart
{
	# get list of output sections in this memory segment
	my @SectionsInTheSameMemory = ();
	my $key;
	my $value;
	while ( ($key,$value) = each %MemorySegmentHash)
	{
		if ( $value eq $CurrentMemSection )
		{
			$SectionsInTheSameMemory[$#SectionsInTheSameMemory+1] = $key;
		}
	}

	# FOR DEBUG
	if ($DEBUG_FLAG == 1)
	{
		print DebugFileHandle "\t\t\tAll output sections in this memory are:\n";
		print DebugFileHandle "\t\t\t\t@SectionsInTheSameMemory\n";
	}


	# get list of end address of output sections in this memory segment
	my %TempAddressHash = ();
	my $section;
	foreach $section (@SectionsInTheSameMemory)
	{
		$TempAddressHash{$section} = $EndAddressHash{$section};
	}

	# sort according to end address
 	my @SortedSections;
	@SortedSections = sort by_end_address keys %TempAddressHash;

	# FOR DEBUG
	if ($DEBUG_FLAG == 1)
	{
		print DebugFileHandle "\t\t\tAfter sorting according to end address:\n";
		print DebugFileHandle "\t\t\t\t@SortedSections\n";
	}

	# choose a previous section with a different start label
	my $Section;
	foreach $Section (@SortedSections)
	{
		# FOR DEBUG
		if ($DEBUG_FLAG == 1)
		{
			print DebugFileHandle "\t\t\tChecking $Section\n";
		}

		if ($LineAr[5] ne $OvlLabelsHash{$Section})
		{
			# FOR DEBUG
			if ($DEBUG_FLAG == 1)
			{
				print DebugFileHandle "\t\t\tOverlay Label is different - selecting $Section as previous\n";
			}


			# found a section which had a different OVL label
			$PrevSection = $Section;
			last; # same as break
		}
	}

}


# --------------------------------------------
# Find a previous section with MAX end address
# --------------------------------------------
sub FindPreviousSectionForStandard
{
	# get list of output sections in this memory segment
	my @SectionsInTheSameMemory = ();
	my $key;
	my $value;
	while ( ($key,$value) = each %MemorySegmentHash)
	{
		if ( $value eq $CurrentMemSection )
		{
			$SectionsInTheSameMemory[$#SectionsInTheSameMemory+1] = $key;
		}
	}

	# FOR DEBUG
	if ($DEBUG_FLAG == 1)
	{
		print DebugFileHandle "\t\t\tAll output sections in this memory are:\n";
		print DebugFileHandle "\t\t\t\t@SectionsInTheSameMemory\n";
	}


	# get list of end address of output sections in this memory segment
	my %TempAddressHash = ();
	my $section;
	foreach $section (@SectionsInTheSameMemory)
	{
		$TempAddressHash{$section} = $EndAddressHash{$section};
	}

	# sort according to end address
 	my @SortedSections;
	@SortedSections = sort by_end_address keys %TempAddressHash;

	# FOR DEBUG
	if ($DEBUG_FLAG == 1)
	{
		print DebugFileHandle "\t\t\tAfter sorting according to end address:\n";
		print DebugFileHandle "\t\t\t\t@SortedSections\n";
	}

	# FOR DEBUG
	if ($DEBUG_FLAG == 1)
	{
		print DebugFileHandle "\t\t\tChoosing the section with the biggest end address $SortedSections[0]\n";
	}

	# Choosing the section with the biggest end address
	$PrevSection = $SortedSections[0];
}


############################################################################
# PROGRAM STARTS
############################################################################
print "\n\n";
print "**************************\n";
print "BA_Sections_Order_Rules.pl\n";
print "**************************\n";

# LOOP OVER THE ARGUMENTS AND PROCESS THEM
my $p;
while ($p=shift @ARGV)
{
	if (exists $argTable{$p})
	{
		$argTable{$p}->();
	}
	else
	{
		print "Illigal Switch $p\n";
		help();
		exit 1;
	}
}

# LOAD THE DATA FROM MACROS.MK INTO $RootDirectory , $BuildScenario
&LoadMacrosFile;

my $FixedOutputSectionsPath = $FileLibrary."\\"."Fixed_Output_Sections_".$BuildScenario.".txt";
# LOAD THE LIST OF THE GREEN SECTIONS - DYNAMIC NON FROZEN LABELS
&LoadDynamicNonFrozenLabels;

# LOAD THE LIST OF THE RED SECTIONS - FROZEN LABELS
&LoadFrozenLabels;

# OPEN MAP FILE & MyMap FILE
my $MapFilePath = "..\\bin\\$MapFN";
open (MapHandle, $MapFilePath) || die "cant open - $MapFilePath\n";
my $MyMapFilePath = ">$FileLibrary\\$MapFN.mymap";
open (MyMapHandle, $MyMapFilePath) || die "cant open - $MyMapFilePath\n";

# WRITE NAMES OF INPUTS / OUTPUTS FILES
print "\n";
print "INPUT:\n";
print "------\n";
print "\t$MacroPath\n";
print "\t$MapFilePath\n";
print "\t$FrozenLabelFilePath\n";
print "\t$DynamicNonFrozenFilePath\n";
print "\n";
print "OUTPUT:\n";
print "------\n";
print "\t$MyMapFilePath\n";
print "\t$FixedOutputSectionsPath\n";
if ($DEBUG_FLAG == 1)
{
	print "\t$DebugFileName\n";
}
print "\n";
print "\n";
# WRITE LEGEND TO MYMAP FILE
print MyMapHandle "-------\n";
print MyMapHandle "LEGEND:\n";
print MyMapHandle "-------\n";
print MyMapHandle "2 = GREEN = dynamic non frozen\n";
print MyMapHandle "3 = BLUE = segment fixed\n\n\n";

# LOAD A LIST OF SRAM MEMORY SEGMENTS FROM MAP FILE
&LoadSramSections;		#&PrintHash(%SRAMSectionsHash);

# THIS IS THE MAIL LOOP WHICH GOES OVER THE MAP FILE AND CHECKS THE RULES
$templine = <MapHandle>;
while(defined($templine))
{
	if ($templine =~ /^The following output sections have been located in the following memory (.*)/)
	{
		# load section name
		$CurrentMemSection = $1;
		$CurrentMemSection =~ tr/"'"//d;# REMOVE ' FROM THE NAME

		$InMemorySegmentFlag = 1;

		# WRITE THE NAME OF THE MEMORY SEGMENT TO MYMAP FILE - THIS IS FOR
		# BEYOND COMAPRE ALIGNMENT
		# check if it is an SRAM section
		if (exists $SRAMSectionsHash{$CurrentMemSection})
		{
			print MyMapHandle "$CurrentMemSection\n";
		}

		# FOR DEBUG
		if ($DEBUG_FLAG == 1)
		{
			print DebugFileHandle "*******************\n$CurrentMemSection\n*******************\n";
		}

		# SKIP THE NEXT LINE - AFTER THAT THE LIST OF OUTPUT SECTIONS WILL APPEAR
		$templine = <MapHandle>;
	}
	elsif ($templine =~ /^Total free space available in memory/)
	{
		$InMemorySegmentFlag = 0;
	}
	elsif ($InMemorySegmentFlag == 1) # THE FIRST LINE IN A SRAM MEMORY SEGMENT
	{
		# SPLIT INPUT LINE
		@LineAr = split(qq( ),$templine);

		# FOR DEBUG
		if ($DEBUG_FLAG == 1)
		{
			print DebugFileHandle "\t$LineAr[0]\n";
		}

		# Is Green ? (first section in memory)
		if ( exists $GreenHash{$LineAr[0]})
		{
	  		&MarkAs("GREEN");

			# FOR DEBUG
			if ($DEBUG_FLAG == 1)
			{
				print DebugFileHandle "\t\t01\n";
			}
		}
		else
		{
	   		&MarkAs("BLUE");

			# FOR DEBUG
			if ($DEBUG_FLAG == 1)
			{
				print DebugFileHandle "\t\t02\n";
			}
		}

		# INDICATE THAT THE NEXT LINE IS NOT THE FIRST OUTPUT SECTION IN THIS SEGMENT
		$InMemorySegmentFlag = 2;
	}
	elsif ($InMemorySegmentFlag == 2) # AN OUTPUT SECTION LINE IN A SRAM MEMORY SEGMENT
	{
		# SPLIT INPUT LINE
		@LineAr = split(qq( ),$templine);

		# FOR DEBUG
		if ($DEBUG_FLAG == 1)
		{
			print DebugFileHandle "\t$LineAr[0]\n";
		}

		# Is Green ?
		if ( exists $GreenHash{$LineAr[0]})
		{
	  		&MarkAs("GREEN");

			# FOR DEBUG
			if ($DEBUG_FLAG == 1)
			{
				print DebugFileHandle "\t\t03\n";
			}
		}
		else
		{
			# FOR DEBUG
			if ($DEBUG_FLAG == 1)
			{
				print DebugFileHandle "\t\t04\n";
			}

			&SplitOverlayList; # THIS SUBROUTINE UPDATES @OverlaySections

			# IS THIS AN OVERLAY BUT NO THE BEGINGING OF THE OVERLAY?
			# exists $ColorsHash{$OverlaySections[0]} => means that the label of the OVL was inserted into the colors list => IT IS NOT A BEGINGING OF AN OVERLAY
			if (($LineAr[4] =~ /OVERLAY/)&&(exists $ColorsHash{$OverlaySections[0]}))
			{
				# FOR DEBUG
				if ($DEBUG_FLAG == 1)
				{
					print DebugFileHandle "\t\t05\n";
				}

				# Is RED ?
				if ( exists $RedHash{$LineAr[0]})
				{
					# FOR DEBUG
					if ($DEBUG_FLAG == 1)
					{
						print DebugFileHandle "\t\t07\n";
						print DebugFileHandle "\t\t\tGoing over list of overlays:\n";
						print DebugFileHandle "\t\t\t\t@OverlaySections\n";
					}

					my $AllOVLsAreGreenWithoutPLCH = "true";
					my $AllOVLsAreBLUEorPLCH = "true";
					my $OVLSection;
					foreach $OVLSection (@OverlaySections)
	 				{
						if (exists $ColorsHash{$OVLSection})
						{
							if ($ColorsHash{$OVLSection} ne "GREEN" )
							{
								$AllOVLsAreGreenWithoutPLCH = "false";
  							}
							if ($OVLSection =~ /PLCH/)
							{
								$AllOVLsAreGreenWithoutPLCH = "false";
							}
							if (($ColorsHash{$OVLSection} ne "BLUE" ) && ($OVLSection !~ /PLCH/))
							{
								$AllOVLsAreBLUEorPLCH = "false";
							}
						}
						else
						{
							print "WARNING - $OVLSection is listed in the overlay list of $LineAr[0] but this label can't be found\n";
							# check if it is an SRAM section
							if (exists $SRAMSectionsHash{$CurrentMemSection})
							{
								print MyMapHandle "WARNING - $OVLSection is listed in the overlay list of $LineAr[0] but this label can't be found\n";
							}
						}
					}
					# All OVLs are GREEN without even 1 PLCH?
					if ( $AllOVLsAreGreenWithoutPLCH eq "true")
					{
						# FOR DEBUG
						if ($DEBUG_FLAG == 1)
						{
							print DebugFileHandle "\t\t09\n";
						}

						# ERROR
						print "ERROR - $LineAr[0] (RED) is after OVLs (@OverlaySections) and they are all GREEN without even 1 PLCH\n";
						# check if it is an SRAM section
						if (exists $SRAMSectionsHash{$CurrentMemSection})
						{
							print MyMapHandle "ERROR - $LineAr[0] (RED) is after OVLs (@OverlaySections) and they are all GREEN without even 1 PLCH\n";
						}
						exit 1; 
					}
					else
					{
						# FOR DEBUG
						if ($DEBUG_FLAG == 1)
						{
							print DebugFileHandle "\t\t10\n";
						}

						# All OVLs are BLUE / PLCH?
						if ( $AllOVLsAreBLUEorPLCH eq "true")
						{
							# FOR DEBUG
							if ($DEBUG_FLAG == 1)
							{
								print DebugFileHandle "\t\t11\n";
							}

							&MarkAs("BLUE");
						}
						else
						{
							# FOR DEBUG
							if ($DEBUG_FLAG == 1)
							{
								print DebugFileHandle "\t\t12\n";
							}

							# Find previous section (from list of OVLs) with MAX end address

							# get list of end address
							my %TempEndAddressHash = ();
							my $Section;
							foreach $Section (@OverlaySections)
			 				{
								# copy data from one hash to the other
								$TempEndAddressHash{$Section} = $EndAddressHash{$Section};
							}

							# sort according to end address
							my @SortedSections;
		 					@SortedSections = sort by_end_address keys %TempEndAddressHash;

							$PrevSection = $SortedSections[0];

							# FOR DEBUG
							if ($DEBUG_FLAG == 1)
							{
								print DebugFileHandle "\t\t\tAfter sorting according to end address\n";
								print DebugFileHandle "\t\t\t\t@SortedSections\n";
								print DebugFileHandle "\t\t\t$PrevSection was selected as previous\n";
							}

							# Is after PLCH / BLUE ?
							if (($PrevSection =~ /PLCH/) || ($ColorsHash{$PrevSection} eq "BLUE"))
							{
								# FOR DEBUG
								if ($DEBUG_FLAG == 1)
								{
									print DebugFileHandle "\t\t13\n";
								}

								# MARK as BLUE
								&MarkAs("BLUE");

								# FIND GREEN WITH MAX END ADDRESS
								my $PrevGreenSection = "";
								foreach $Section (@SortedSections)
								{
									if ( ($ColorsHash{$Section} eq "GREEN") && !($Section =~ /PLCH/))
									{
										$PrevGreenSection = $Section;
										last;
									}
								}

								# ISSUE A WARNING
								my $diff = hex($LineAr[2]) - $EndAddressHash{$PrevGreenSection};
								print "WARNING - $LineAr[0] (RED) after $PrevSection (BLUE/PLCH).\nThe address diff from $PrevGreenSection (which is the previous GREEN with the maximum end address) is $diff bytes\n\n";
								# check if it is an SRAM section
								if (exists $SRAMSectionsHash{$CurrentMemSection})
								{
									print MyMapHandle "WARNING - $LineAr[0] (RED) after $PrevSection (BLUE/PLCH).\nThe address diff from $PrevGreenSection (which is the previous GREEN with the maximum end address) is $diff bytes\n\n";
								}
							}
							else
							{
								# FOR DEBUG
								if ($DEBUG_FLAG == 1)
								{
									print DebugFileHandle "\t\t14\n";
								}

								print "ERROR - $LineAr[0] (RED) is after OVLs (@OverlaySections) and they are mixed (BLUE & GREEN).\nThe section on which $LineAr[0] is sitting is $PrevSection and it is not PLCH / BLUE\n";
								# check if it is an SRAM section
								if (exists $SRAMSectionsHash{$CurrentMemSection})
								{
									print MyMapHandle "ERROR - $LineAr[0] (RED) is after OVLs (@OverlaySections) and they are mixed (BLUE & GREEN).\nThe section on which $LineAr[0] is sitting is $PrevSection and it is not PLCH / BLUE\n";
								}
								exit 1;
							}
						}
					}
				}
				else
				{
					# FOR DEBUG
					if ($DEBUG_FLAG == 1)
					{
						print DebugFileHandle "\t\t08\n";
						print DebugFileHandle "\t\t\tGoing over list of overlays:\n";
						print DebugFileHandle "\t\t\t\t@OverlaySections\n";
					}

					my $OneOVLIsGreenAndNotPLCH = "false";
					my $OVLSection;
					foreach $OVLSection (@OverlaySections)
	 				{
						if (($ColorsHash{$OVLSection} eq "GREEN" ) && ($OVLSection !~ /PLCH/))
						{
							$OneOVLIsGreenAndNotPLCH = "true";
						}
					}
					if ( $OneOVLIsGreenAndNotPLCH eq "true")
					{
						# FOR DEBUG
						if ($DEBUG_FLAG == 1)
						{
							print DebugFileHandle "\t\t21\n";
						}

						&MarkAs("GREEN");
					}
					else
					{
						# FOR DEBUG
						if ($DEBUG_FLAG == 1)
						{
							print DebugFileHandle "\t\t22\n";
						}

						&MarkAs("BLUE");
					}
				}
			}
			else
			{
				# FOR DEBUG
				if ($DEBUG_FLAG == 1)
				{
					print DebugFileHandle "\t\t06\n";
				}

				# Is it OVL start ?
				if (($LineAr[4] =~ /OVERLAY/)&&!(exists $ColorsHash{$OverlaySections[0]}))
				{
					# FOR DEBUG
					if ($DEBUG_FLAG == 1)
					{
						print DebugFileHandle "\t\t15\n";
					}

					&FindPreviousSectionForOverlayStart; # THIS SUBROUTINE WILL UPDATE $PrevSection
				}
				else
				{
					# FOR DEBUG
					if ($DEBUG_FLAG == 1)
					{
						print DebugFileHandle "\t\t16\n";
					}

					&FindPreviousSectionForStandard;   # THIS SUBROUTINE WILL UPDATE $PrevSection
				}

				# Is after PLCH / BLUE?
				if (($PrevSection =~ /PLCH/) || ($ColorsHash{$PrevSection} eq "BLUE"))
				{
					# FOR DEBUG
					if ($DEBUG_FLAG == 1)
					{
						print DebugFileHandle "\t\t17\n";
					}

					&MarkAs("BLUE");
				}
				else
				{
					# FOR DEBUG
					if ($DEBUG_FLAG == 1)
					{
						print DebugFileHandle "\t\t18\n";
					}

					# Is RED ?
					if ( exists $RedHash{$LineAr[0]})
					{
						# FOR DEBUG
						if ($DEBUG_FLAG == 1)
						{
							print DebugFileHandle "\t\t19\n";
						}

						print "ERROR - $LineAr[0] (RED - FROZEN) is after $PrevSection (DYNAMIC) !!!!!!!!";
						# check if it is an SRAM section
						if (exists $SRAMSectionsHash{$CurrentMemSection})
						{
							print MyMapHandle "ERROR - $LineAr[0] (RED - FROZEN) is after $PrevSection (DYNAMIC) !!!!!!!!";
						}
						exit 1;
					}
					else
					{
						# FOR DEBUG
						if ($DEBUG_FLAG == 1)
						{
							print DebugFileHandle "\t\t20\n";
						}

						&MarkAs("GREEN");
					}
				}
			}
		}
	}

	# READ NEXT LINE AND SPLIT IT
	$PrevSection = $LineAr[0];
	$templine = <MapHandle>;
}


# OPEN FIXED_OUTPUT_SECTIONS_... FILE
open (FixedOutputSectionsHandle, ">".$FixedOutputSectionsPath) || die "cant open - $FixedOutputSectionsPath\n";

# Print The List Of Fixed Output Sections (BLUE) To File
my $key;
my $value;
while ( ($key,$value) = each %ColorsHash)
{
	if ( $value eq "BLUE" ) {
		print FixedOutputSectionsHandle "$key\n";
	}
}

exit;
