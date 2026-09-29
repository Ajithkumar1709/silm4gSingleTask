#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/bin/perl -w

########## ------------------ BA_Frozen_Label_Mapping.pl ---------------- #######################
#  this file porpuses:
#
#    1. create a list of all the Frozen label segments.
# 	 2. check that in these segments there are no Labels in a Non Frozen file.
# 	 3. create list of all the Non Frozen Output segments
#
########## --------------------------------------------------- #######################

#defines a hash for user switches
$Arg = 0;
%dTable=(-h=>\&help,
		 -i=>\&Input,
		 -m=>\&MapFile);

# function : help function for user
# ---------------------------------
sub help
{
	print "--------------------------------------------------------------------------------";
	print "this file is part of the BA module.\n";
	print "this file porpuse is to create a list of all the Frozen label segments.\n";
	print "the program check that in these segments there are no Labels in a Non Frozen file.\n";
	print "it output the proper text file with the required list.\n";
	print "In addition it create a list of all the Non Frozen Output Segments.\n";
	print "Input:  Program must receive as an input the File library name and Map file name\n"; 
	print "Usage:  BA_Frozen_Label_Mapping [-h -i]  <Text File Libaray Name> [-m] <Map file name>\n"; 
}
# function : get input library
# -------------------------------
sub Input
{
	if(!defined($FileLibrary = shift @ARGV))
	{
		print "ERROR: missing File library Input\n";
		exit 1;
	}
	else
	{
		$Arg = $Arg + 1;
	}		
}
sub MapFile
{
	if(!defined($MapFileName = shift @ARGV))
	{
		print "ERROR: missing Map File Name\n";
		exit 1;
	}
	else
 	{
		$Arg = $Arg + 1;
	}
}

# get program arguments
# -------------------------------------
while ($p=shift @ARGV)
{

	if (exists $dTable{$p})
	{

		$dTable{$p}->();

	}

	else

	{

		print "Illigal Switch $p\n";
		help();
		exit;

	}
}

#check we got the proper number of arguments
if ( $Arg < 2 )
{
	print "ERROR: wrong usage of program - missing arguments \n";
	help();
	exit 1;
}

##########  get defines from macro.mk  #################

$MacroPath = "macros.mk";
open (MACRO,$MacroPath) || die "cant open macros.mk\n" ;
$templine = <MACRO>;
while(defined($templine))
{
		if ($templine=~/BUILD_TYPE=(.*)/)
		{
			$TargetVariant = $1;
		}
		if ($templine=~/CBA_ROOT=(.*)/)
		{
			$RootDirectory = $1;
		}
		if ($templine=~/HW_PLATFORM_VARIANT=(.*)/)
		{
			#$PlatformVariant = $1;
		}
		if ($templine=~/BUILD_SCENARIO=(.*)/)
		{
			$BuildScenario = $1;
		}
		$templine = <MACRO>;
}
close(MACRO);

if (( $TargetVariant !~ /BUILD_FROZEN_FILES/ ) && ( $TargetVariant !~ /BUILD_TARGET_FILES/ ))
{
	exit;
}

# create target paths
$OutPutFilesPath = $FileLibrary."\\";

$FrozenLabelSegment = "FrozenLabel";

$index = 0;
$testindex = 0;
$ErrorFlag = 0;
##########################   prepare a Non Frozen files list	######################################
#####                  this file was created by the Sort Perl script                             #####

$NonFrozenPath1 = $OutPutFilesPath."Non_Frozen_Files_list_".$BuildScenario.".txt";
open (ALL,$NonFrozenPath1) || die "cant open $NonFrozenPath1\n" ;
$templine = <ALL>;
while(defined($templine))
{
	if ($templine =~ /^\S/)
	{
		chomp($templine);
		$templine =~ tr/[A-Z]/[a-z]/;
		$NonFrozenFiles{$templine}=1;
		$testindex = $testindex + 1;
	}
	$templine = <ALL>;
}
close(ALL);
########################## open the file with the linker output ######################################

$SectionListPath = $OutPutFilesPath."Files_Sections_list_".$BuildScenario.".txt";
$FrozenLabelSegmentsPath = ">".$OutPutFilesPath."Frozen_Label_Input_Segments_list_".$BuildScenario.".txt";
open(SEG,$FrozenLabelSegmentsPath) || die "cant open $FrozenLabelSegmentsPath\n" ;
open(LOG,$SectionListPath) || die "can't open : $SectionListPath\n ";
$templine = <LOG>;
print "----------- ENTERED FROZEN LABEL MAPPING PERL SCRIPT -----------------\n";
print "start mapping Frozen Labels Segments...\n";
while(defined($templine))
{
	if ($templine =~ (/Part 1: (.*)/))
	{
	    $Part_name = $1;
		print "entered $Part_name\n";
		$templine = <LOG>;
		while (($templine !~ (/^Part(.*)/)) && (!eof))
		{
			# for each Part : we extract the Segment name from an array - place 6
			# we lower the case and save it in the correct part

			if (( $templine =~ /\sFunction\s.*/) || ( $templine =~ /\sData\s.*/))
			{
				@a=split(qq( ),$templine);
				$SegmentName = $a[5];
				# we ommit the - ' - from the name (beginning and end);
				chop ($SegmentName);
				$SegmentName = substr($SegmentName,1);
				#Eli - bug fix: the frozen label is not interesting - only the frozen label segment
				#$FileName = $a[7];
				#$FileName =~ s/.*\\(.*)\.DOJ.*/$1/e;
				#$FileName =~ s/.*\((.*)/$1/e;
				#$FileName=~ tr/[A-Z]/[a-z]/;
				# we create list os all the labels in Part 1 associated with their file name (to handle static labels from different files but with the same name) for further check in Part 4
				#$Frozen_Label_List{$a[1]}=$FileName;

				if (!defined ($SegmentHash{$SegmentName}))
				{
					 $SegmentHash{$SegmentName} = $FrozenLabelSegment;
					 print SEG "$SegmentName\n";
					 $index = $index+1;
				}
			}
			$templine = <LOG>;
		}
	}
	if ($templine =~ (/Part 4: (.*)/))
	{
        $Part_name = $1;
		print "entered $Part_name\n";
		$templine = <LOG>;
		while (($templine !~ (/^Part(.*)/)) && (!eof))
		{
			if (( $templine =~ /\sFunction\s.*/) || ( $templine =~ /\sData\s.*/))
			{
				@a=split(qq( ),$templine);
				$FileName = $a[7];
				$SegmentName = $a[5];
				# we ommit the - ' - from the name (beginning and end);
				chop ($SegmentName);
				$SegmentName = substr($SegmentName,1);
				$FileName =~ s/.*\\(.*)\.DOJ.*/$1/e;
				$FileName =~ s/.*\((.*)/$1/e;
				$FileName=~ tr/[A-Z]/[a-z]/;
				# ----------------  Labal check ------------------------------------------------------------------------------------
				# If the non-frozen label is in frozen-label segment but inside non-frozen file this is an error.
				# Since non-frozen label can be only in non-frozen file, no need to check if the label is non-frozen. It is enough to look for frozen-label segments inside non-frozen files.

				#Eli - bug fix: the label is not interesting - only segment and the file (see description above). Therefore the first 'if' was omitted.
				# we check that the current label is not also a Frozen label, if so we dont include this file as a Frozen label one
				# Note: since static labels can share the same name, we also verify that if there is a frozen label with the same name - it is from the same file
				#if (!defined($Frozen_Label_List{$a[1]}) || ($Frozen_Label_List{$a[1]} ne $FileName) )
				#{
					# now after we know this is a Non Frozen label we check if it belong to a Frozen Label Segment
					if ( defined($SegmentHash{$SegmentName}))
					{
						# now we will check if the file is a Non Frozen one
						if ( defined($NonFrozenFiles{$FileName}))
						{
							print "-------------- ERROR ERROR ERROR ---------------\n";
							print "Error: the Non Frozen label $a[1] from the Non Frozen file $FileName was found in the Frozen Label Segment $SegmentName\n";
							$ErrorFlag = 1;
							#exit 1;
						}

					}
				#}
			}
			$templine = <LOG>;
		}
	}
	$templine = <LOG>;
}
close (LOG);
close (SEG);
# check that there are no errors before we continue (the next check is based on the validity of this check) 
if ( $ErrorFlag != 0 )
{
	exit 1;
}

print "finished mapping Frozen Label segments and no Errors were found\n$index Segments were mapped\n";


#################################### now we map the non Frozen Otput segments ############################

print "start mapping output segments...\n";
$MapPath = "..\\bin\\";
# initialize variables
$OutputSegmentNonFrozenFlag = 0;
$OutputSegmentFrozenLabelFlag = 0;
# prepare open files paths
$OutPutFilesPath = $FileLibrary."\\";
$MapFilePath = $MapPath.$MapFileName;
$Non_F_OutputPath = ">".$OutPutFilesPath."Dynamic_Non_Frozen_Output_Sections_".$BuildScenario.".txt";
$F_Label_OutputPath = ">".$OutPutFilesPath."Frozen_Label_Output_Segments_list_".$BuildScenario.".txt";
open (MAP, $MapFilePath) || die "cant open map file\n";
open (NON_F_OUT, $Non_F_OutputPath) || die "cant open $Non_F_OutputPath file\n";
open (F_LABEL_OUT, $F_Label_OutputPath) || die "cant open $F_Label_OutputPath file\n";
$templine = <MAP>;
while(defined($templine))
{
	#only from here start the segments information we are intersted with
	if ( $templine=~ /Input sections that map into the given output sections/ )
	{
   		while(defined($templine))
		{
	   		# make sure we work with a not empty line and
			if ($templine =~ /^\S/)
			{
				# look for output section line
				if ($templine =~ /^Output Section (.*)/ )
				{
					# we load the output section name
					$CurrentOutputSection = $1;
					#check we have not been here before - overlay double the reports
					if (!defined($OuputSections{$CurrentOutputSection}))
					{
						$OuputSections{$CurrentOutputSection}=1;
						if ( $CurrentOutputSection !~ /\.\w+/ ) #to avoid .debug sections
						{
							$templine = <MAP>;
							# we have entered a output section and we run until the next one
							while (($templine !~ /^Output Section.*/ ) && ($templine =~ /^\S/))
							{
								@a = split(qq( ),$templine);
	 		   					#only lines with 4 parameters
			   					if(scalar(@a) == 4)
	   							{
									# we check these are not lines starts with these strings
									if(($templine !~ /^No .*/) && ($a[0] !~ /^Input .*/))
	   	   	   	   					{
										# extract file name
 	  	   	   							$CurrFileName = $a[3];
	   	   	 	  						$CurrFileName =~ s/.*\\(.*)\.DOJ.*/$1/e;
   		   	   							$CurrFileName =~ tr/[A-Z]/[a-z]/;
			   							# check it is not an empty segment to deal with the defaults labels (program, const data ...)
			   							if ((hex($a[2]) != 0 ))
			   							{
											# check if this input segment is Dynamic Non Frozen (=Non Frozen input segment inside Non-Frozen file)
											if (defined($NonFrozenFiles{$CurrFileName}))
											{
												# we raise a flag to note this output segment in a non Frozen
												$OutputSegmentNonFrozenFlag = 1;
												# we store the current input segment and the current file, in case we need to print it if there is an error
												$CurrNonFrozenSeg = $a[0];
												$CurrNonFrozenFile = $CurrFileName;
											}
											# check if this is an input Frozen Label segment
											if (defined($SegmentHash{$a[0]}))
											{
												# we raise a flag to note that this output segment contains an input Frozen Label segment
												$OutputSegmentFrozenLabelFlag = 1;
												# we store the current label in case we need to print it if there is an error
												$CurrFrozenLabelSeg = $a[0];
											}
										}
 								   	}
								}
								$templine = <MAP>;
							}
							# we are out of the current Output Section so we check for vealidity:
							# only if the section contains only Non Frozen Input section the output segment is Non Frozen
							# We declare Error if there is a mixture
 							if (($OutputSegmentNonFrozenFlag == 1) && ($OutputSegmentFrozenLabelFlag != 1))
							{
								print NON_F_OUT "$CurrentOutputSection\n";
							}
							if (($OutputSegmentNonFrozenFlag == 1) && ($OutputSegmentFrozenLabelFlag == 1))
							{
 		  						print "-------------------- ERROR ERROR ERROR ---------------------\n";
								print "In the Output segment - $CurrentOutputSection there are both:\n";
								print "1. Frozen Label - $CurrFrozenLabelSeg, and\n";
								print "2. Dynamic Non Frozen - $CurrNonFrozenSeg Input segments (From Non-Frozen file $CurrNonFrozenFile)\n";
								$ErrorFlag = 1;
								#exit 1;
					   		}
							# Now - after we checked validity we print the output segment name if it contains only Frozen Label input segments
 							if (($OutputSegmentNonFrozenFlag != 1) && ($OutputSegmentFrozenLabelFlag == 1))
							{
								print F_LABEL_OUT "$CurrentOutputSection\n";
							}

							# initialize variables
 					   		$OutputSegmentNonFrozenFlag = 0;
				   			$OutputSegmentFrozenLabelFlag = 0;
						}
						else
						{
				 		$templine = <MAP>;
						}
					}
					else
					{
				 		$templine = <MAP>;
					}
				}
				else
				{
				 		$templine = <MAP>;
				}
			}
			else
			{
				$templine = <MAP>;
			}
		}
	}
	$templine = <MAP>;
}
# close files handles
close (MAP);
close (NON_F_OUT);

# check that there are no errors before we finsh the Build
if ( $ErrorFlag != 0 )
{
	exit 1;
}

print "finished mapping Non frozen Output sections.\n";
######################################### End of program ################################################
