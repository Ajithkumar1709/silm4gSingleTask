#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/bin/perl -w

########## ------------------ BA_Sort_Copy_Files.pl ---------------- #######################
#  this file porpuses:
#
#    1. sort all filef according to the linker output to all Labels
#    2. check for errors (Frozen and Non Frozen labels in the same file). If so exit.
#    3. copy all the Frozen doj files to a dedicated library
# 	 4. Sort files for unrefferen files
# 	 5. sort unreffered to Frozen files and add them to the Frozen list
#    7. look for more frozen files from the non frozen and frozen labe lists using map file
#
########## --------------------------------------------------- #######################

#To check for errors. '0' means - no error. '1' means - error
$ErrorFlag = 0;
#defines a hash for user switches
$Arg=0;
%dTable=(-h=>\&help,
		 -i=>\&Input,
		 -m=>\&MapFile,
		 -S=>\&StartAdd,
		 -E=>\&EndAdd,
		 -p=>\&OutputPath);

# function : help function for user
# ---------------------------------
sub help
{
	print "--------------------------------------------------------------------------------";
	print "this file is part of the BA module.\n";
	print "this file porpuse is to sort all files into lists according to the Linker output.\n";
	print "the program create lists of Frozen, Non Frozen and Frozen Label files.\n";
	print "it also copy the Frozen Files doj files to a dedicated library.\n";
	print "in addition it creates a text file with the path of the files to the linker\n";
	print "the program receive the project root directory from macros.mk\n";
	print "Input:  Program must receive as an input the following arguments:\n";
	print "Text File library name , the doj Library Name , map file name , ROM start address , ROM end adress\n";			 
	print "Usage:  BA_Frozen_Label_Mapping [-h],[-i]  < Text File Libaray Name> <doj Library Name> [-m] <map file name> -S <StartAdd> -E <EndAdd> -p <OutputPath>\n"; 
}
# function : get input arguments
# -------------------------------
sub Input
{
	if(!defined($FileLibrary = shift @ARGV))
	{
		print "ERROR: missing Text File library Input\n";
		exit 1;
	}
	else
	{
		$Arg = $Arg + 1;
	}
	if(!defined($DojFileLibrary = shift @ARGV))
	{
		print "ERROR: missing Doj File library Input\n";
		exit 1;
	}
	else
	{
		$Arg = $Arg + 1;
	}
}

sub OutputPath
{
	if(!defined($OutPutFilesPath = shift @ARGV))
	{
		print "ERROR: missing output path after -p\n";
		exit 1;
	}
	else
	{
		$Arg = $Arg + 1;
	}
	$OutPutFilesPath = "$OutPutFilesPath\\";
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
sub StartAdd
{
	if(!defined($RomStartAddress = hex(shift (@ARGV))))
	{
		print "ERROR: missing Start Adress Input\n";
		exit 1;
	}
	else
	{
		$Arg = $Arg + 1;
	}
}
sub EndAdd
{
	if(!defined($RomEndAddress = hex(shift (@ARGV))))
	{
		print "ERROR: missing End Adress Input\n";
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
if ( $Arg < 5 )
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

if ( $TargetVariant!~ /BUILD_FROZEN_FILES/ )
{
	exit;
}

# create target paths
$ProjectPath = ".\\";

# Linker output labels
$Part1 = "Part1";
$Part2 = "Part2";
$Part3 = "Part3";
$Part4 = "Part4";
$function = "function";

# the dedicated library for which we want to copy the doj files
$DojFilesTarget = $ProjectPath.$DojFileLibrary."\\";


$index = 0;
# indexes for referred files
$RefIndex1=0;
$RefIndex2=0;

########################## open the file with the linker output ######################################
$SectionListPath = $OutPutFilesPath."Files_Sections_list_".$BuildScenario.".txt";
open(LOG,$SectionListPath) || die "Can not open $SectionListPath.\n";
$templine = <LOG>;
print "-----------ENTERED SOTRING AND COPING PERL SCRIPT -----------------\n";
print "----------  PAY ATTENTION FOR WARNINGS AND ERRORS  ----------------\n";
print "start sorting names...\n";
while(defined($templine))
{
	if ($templine =~ (/Part 1: (.*)/))
	{
	    $Part_name = $1;
		print "entered $Part_name\n";
		$templine = <LOG>;
		while (($templine !~ (/^Part(.*)/)) && (!eof))
		{
			# for each Part : we extract the file name from an array - place 8
			# we lower the case and save it in the correct part

			if (( $templine =~ /\sFunction\s.*/) || ( $templine =~ /\sData\s.*/))
			{
				@a=split(qq( ),$templine);
				$FileName = $a[7];
				$FileName =~ s/.*\\(.*)\.DOJ.*/$1/e;
				$FileName =~ s/.*\((.*)/$1/e;
				$FileName=~ tr/[A-Z]/[a-z]/;
				$FilesList{$FileName}{$Part1} = 1; # to indicate file appears in Part 1
				# The below is to handle Frozen-Label labels which are also Non Frozen labels. Those labels should became Frozen label (worst case scenario)
				# we create list os all the labels in Part 1 for further check in Part 4
				$Frozen_Label_List{$a[1]}=1;
				# if this is a Frozen Label function label we remember it and will check it later on
				if ( $templine =~ /\sFunction\s.*/)
				{
					$templine =~ /.*?_(.*?)'/;   #Entering frozen label function name to $1
					$FilesList{$FileName}{$function} = $1;
				}
				$index +=1;
			}
			$templine = <LOG>;
		}
	}
	if ($templine =~ (/Part 2: (.*)/))
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
				$FileName =~ s/.*\\(.*)\.DOJ.*/$1/e;
				$FileName =~ s/.*\((.*)/$1/e;
				$FileName=~ tr/[A-Z]/[a-z]/;
				$FilesList{$FileName}{$Part2} = 1; # to indicate file appears in Part 2
				$index +=1;
			}
			$templine = <LOG>;
		}
	}
	if ($templine =~ (/Part 3: (.*)/))
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
				$FileName =~ s/.*\\(.*)\.DOJ.*/$1/e;
				$FileName =~ s/.*\((.*)/$1/e;
				$FileName=~ tr/[A-Z]/[a-z]/;
				$FilesList{$FileName}{$Part3} = 1;  # to indicate file appears in Part 3
				$index +=1;
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
				$FileName =~ s/.*\\(.*)\.DOJ.*/$1/e;
				$FileName =~ s/.*\((.*)/$1/e;
				$FileName=~ tr/[A-Z]/[a-z]/;
				# ----------------  Labal check ------------------------------------------------------------------------------------
				# we check that the current label is not also a Frozen label, if so we dont include this file as a Non Frozen one
				if (!defined($Frozen_Label_List{$a[1]}))
				{
					$FilesList{$FileName}{$Part4} = 1; # to indicate file appears in Part 4
					$index +=1;
				}
			}
			$templine = <LOG>;
		}
	}
	$templine = <LOG>;
}
close (LOG);
print "num of segments mapped $index\n";


###################### get path for doj files before coping them    ##############################
$EntitiesPath = $OutPutFilesPath."FilesEntities_".$BuildScenario.".txt";
open(ENTITY,$EntitiesPath)||die "Cant open $EntitiesPath\n" ;
$templine = <ENTITY>;
while(defined($templine))
{
		@b=split(qq( ),$templine);
		$entity{$b[0]}=$b[1];
		$templine = <ENTITY>;
}
close(ENTITY);

######################## load suffix hash before printing then to file ###############################
$SuffixPath = $OutPutFilesPath."FilesSuffixes_".$BuildScenario.".txt";
open(SUFFIX,$SuffixPath)||die "Cant open $SuffixPath\n" ;
$templine = <SUFFIX>;
while(defined($templine))
{
		@c=split(qq( ),$templine);
		#if not defined load to a list that we use to filter the copi
		$suffix{$c[0]}=$c[1];
		$templine = <SUFFIX>;
}
close(SUFFIX);

################################# open Frozen Label code labels files list ####################################
# create a list - in this list there are the only files we allow to be with code labels and Frozen Labels
$FrozenLabelCodeFilesPath = $OutPutFilesPath."\\Frozen_Label_Code_Files_List.txt";
open (FROZEN_LABEL_CODE_LIST,$FrozenLabelCodeFilesPath) || die "Can not open the input file Frozen_Label_Code_Files_List.txt.\n";

$templine = <FROZEN_LABEL_CODE_LIST>;
while(defined($templine))
{
	chomp($templine);
	$FLCodeList{$templine}=1;
	$templine = <FROZEN_LABEL_CODE_LIST>;
}

####################  Sort Files + create text files lists ###############################3
# here we do the sorting of the files for all labels
# in addition we check if there are files with warnings (Frozen and Non Frozen labels in the same file)

$FrozenLabelIndex = 0;
$FrozenIndex = 0;
$NonFrozenIndex = 0;
$WarningCounter = 0;
$FilesNumber=0;
$SortFilesNumber=0;

foreach  $CurrentFileName (keys (%FilesList ))
{
	$FilesNumber+=1;

	#check for un autorized files with code labels
   	if ( defined($FilesList{$CurrentFileName}{$function}))
   	{
   		if (!defined($FLCodeList{$CurrentFileName}))
   		{
   			print "ERROR : In file '$CurrentFileName' there is at least one frozen label function ($FilesList{$CurrentFileName}{$function}). However, according to Frozen_Label_Code_Files_List.txt, '$CurrentFileName' is not allowed to hold frozen label functions.\n";
   			# we raise a flag that will send error to the gnumake - it should stop the procedure of the Build
   			$ErrorFlag = 1;
   		}
   	}

	#sort Frozen Label files
	if ((defined($FilesList{$CurrentFileName}{$Part1})) && (!defined($FilesList{$CurrentFileName}{$Part2})) && (!defined($FilesList{$CurrentFileName}{$Part3})))
	{
		# update Frozen Label Hush
		$FrozenLabelFilesHush{$CurrentFileName}=1;
		# we also update Refferred files hash
		$RefFilesHash{$CurrentFileName} = 1;
		#update number of sorted files
		$SortFilesNumber+=1;
		# update frozen labels files counter
		$FrozenLabelIndex += 1;
	}
  	else
	{
		#sort non frozen files
		if ((defined($FilesList{$CurrentFileName}{$Part4})) && (!defined($FilesList{$CurrentFileName}{$Part1})) && (!defined($FilesList{$CurrentFileName}{$Part2})) && (!defined($FilesList{$CurrentFileName}{$Part3})))
		{
			# update Non Frozen Hush
			$NonFrozenFilesHush{$CurrentFileName}=1;
		  	# we also update Ref hash 
			$RefFilesHash{$CurrentFileName} = 1;
			# update files counters
	   		$SortFilesNumber+=1;
	   		$NonFrozenIndex += 1;
		}
  		else
		{
			#sort frozen files
			if ((defined($FilesList{$CurrentFileName}{$Part2})) || (defined($FilesList{$CurrentFileName}{$Part3})))
			{
				# if there is a warning file we print it to a different list but also to the frozen list
				# we dont want to lose the reference for these files
				if (defined($FilesList{$CurrentFileName}{$Part4}))
				{
 					#updtae warning files Array
					push(@WarningFilesArr,$CurrentFileName);
					$WarningCounter += 1;
	   			}
				# we update Ref hash
				$RefFilesHash{$CurrentFileName} = 1;
				# before we print to frozen we need to recover the file suffix, since we need to copy this file.
				# if the suffix doesnot exists this file doj should be already in the dedicated library
				if (defined($suffix{$CurrentFileName}))
				{
					$FrozenTextOutputFormat =$DojFileLibrary."\\".$CurrentFileName.".doj";
					# we prepare an array for the linker text file. we will print it only after sorting it.
					# the reason is that in order to preduce same ROM mask we need same files order for the linker
					push(@FrozenTextFilesList,$FrozenTextOutputFormat);
					#prepare list of files to be copied
					$FilesToBeCopied{$CurrentFileName}=1;
					#get suffix before adding to frozen files list (for filtering in the gnumake)
					$CurrentFileName = $suffix{$CurrentFileName};
				}
				# updtae Frozen files Array for filtering
				# this list is out of the if because it also the list of all frozen files for users
				# we dont worry about files without suffix here because they will not be regarded by the filter (not relevant)
				push(@FrozenFilesArr,$CurrentFileName);
				# update counters
				$SortFilesNumber+=1;
		   		$FrozenIndex += 1;
   	   		}
			else
			{
				    print "$CurrentFileName was not sorted\n";
			}
		}
	}
	#debugg:
	#foreach $Part (keys (%{$FilesList{$CurrentFileName}}))
	#{
	#	print"$CurrentFileName => $Part\n";
	#}
}
# if errors were detected we will now exit the Program
if ( $ErrorFlag == 1 )
{
	exit 1;
}

##debug:
#die;

if ( $WarningCounter > 0 )
{
	print "----------- WARNING WARNING WARNING -----------------------\n";
	print "WARNING : there are files with both Frozen and Non Frozen segments\ntotal number of files with warnings  = $WarningCounter\nNOTE: these files will be regarded as Frozen and their doj file will be copied to the dedicated library\n";
}

##################### ----------------  Create UnReferred_Files_List ------------------------- ############################
# create list of all the files that are compiled and not reported by the -memRv command
# these files will not be in the Sort Perl script output lists
######################### ------------------------------------------------------------------- ############################


# now we check from all the files that were compiled (list in suffix file) which was not reported
$MacroPath2 = ">".$OutPutFilesPath."UnReferred_Files_list_".$BuildScenario.".txt";
open (ALL,$SuffixPath) || die "Can not open $SuffixPath.\n" ;
open (UNREF,$MacroPath2) || die "Can not open $MacroPath2.\nFile might not exists or exists as read only.\n" ;
$templine = <ALL>;
while(defined($templine))
{
	$RefIndex1 = $RefIndex1 + 1;
	@file=split(qq( ),$templine);
	$file[0] =~ tr/[A-Z]/[a-z]/;
	if (!defined($RefFilesHash{$file[0]}))
	{
		# update an unref files hash as Non Frozen by default
		$UnferHash{$file[0]} = "NonFrozen";
		$RefIndex2 = $RefIndex2 + 1;
		print UNREF "$file[0]\n";
	}
	$templine = <ALL>;
}
close(ALL);
close(UNREF);

## Debug:
#$d=scalar (keys %RefFilesHash);
#print "RefFilesHash size is $d\n";

######################### Check for more Frozen files from the unreffered list  ######################################
######################################################################################################################

$MapPath = "..\\bin\\";
$OutPutFilesPath = $FileLibrary."\\";
$RefIndx = 0;
$MapFilePath = $MapPath.$MapFileName;
open (MAP, $MapFilePath) || die "cant open map file\n";
$templine = <MAP>;
while(defined($templine))
{
	#only from here start the segments information we are intersted with
	if ( $templine=~ /Input sections that map into the given output sections/ )
	{
   		while(defined($templine))
		{
			# make sure we work with a not empty line and a line that dont begin with input section
			if ($templine =~ /^w*/)
			{
			if ($templine !~ /^Input section.*/ )
			{
				@a = split(qq( ),$templine);
				#only lines with 4 parameters
				if(scalar(@a) == 4)
				{
				if($templine !~ /^No.*/)
	   			{
			 		#check the segment is not empty
					if ((hex($a[2]) != 0 ))
					{
						#extract file name
						$CurrFileName = $a[3];
						$CurrFileName =~ s/.*\\(.*)\.DOJ.*/$1/e;
						$CurrFileName =~ tr/[A-Z]/[a-z]/;
						# Here we will check existense of more Frozen files.
						# this situation regards to the following situations:
						#  1) unreffered files which contains labels in ROM
						#  2) Non frozen or Frozen Label files with label in the ROM that were not reffered (was not reported by the linker).

						# -------   check for frozen files in unreffed ------------- 
						# first check if the file is unreffed
	   					if (!defined($RefFilesHash{$CurrFileName}))
	   					{
	   						# check if it is mapped to the ROM
	   						if ((hex($a[1]) >= $RomStartAddress) && (hex($a[1]) < $RomEndAddress))
	   						{
								#check files hash to not copy twice the same file
								if (!defined($CheckFiles{$CurrFileName}))
								{
									# update the hash
									$CheckFiles{$CurrFileName}=1;
									# update the unreferenced hash
									$UnferHash{$CurrFileName} = "Frozen";
									if (defined($suffix{$CurrFileName}))
									{
										# sending file to text files
			   							# ---------------------------------
		   	   							# send to linker files list
	   		   							$FrozenTextOutputFormat =$DojFileLibrary."\\".$CurrFileName.".doj";
										# we prepare an array for the linker text file. we will print it only after sorting it.
										# the reason is that in order to preduce same ROM mask we need same files order for the linker
										push(@FrozenTextFilesList,$FrozenTextOutputFormat);
										#prepare list of files to be copied
										$FilesToBeCopied{$CurrFileName}=1;
										#get suffix before adding to frozen files list (for filtering in the gnumake)
										$CurrFileName = $suffix{$CurrFileName};
									}
									# updtae Frozen files Array for filtering
									# this list is out of the if because it also the list of all frozen files for users
									# we dont worry about files without suffix here because they will not be regarded by the filter (not relevant)
									push(@FrozenFilesArr,$CurrFileName);

									#update counters
									$SortFilesNumber+=1;
		   							$FrozenIndex += 1;
									$RefIndx+=1;
								}
							}
	   					}

						#----------------  check for Frozen files in the Non Frozen files ------------------
						# first check if the file is Non Frozen
	   					if (defined($NonFrozenFilesHush{$CurrFileName}))
	   					{
	   						# check if it is mapped to the ROM
	   						if ((hex($a[1]) >= $RomStartAddress) && (hex($a[1]) < $RomEndAddress))
	   						{
								#check files hash to not copy twice the same file
								if (!defined($CheckFiles{$CurrFileName}))
								{
									# update the hash
									$CheckFiles{$CurrFileName}=1;
									if (defined($suffix{$CurrFileName}))
									{
										# sending file to text files
			   							# ---------------------------------
		   	   							# send to linker files list
	   		   							$FrozenTextOutputFormat =$DojFileLibrary."\\".$CurrFileName.".doj";
										# we prepare an array for the linker text file. we wioll print it only after sorting it.
										# the reason is that in order to preduce same ROM mask we need same files order for the linker
										push(@FrozenTextFilesList,$FrozenTextOutputFormat);
										#prepare list of files to be copied
										$FilesToBeCopied{$CurrFileName}=1;
										# remove file name from non frozen list
										delete $NonFrozenFilesHush{$CurrFileName};
										# update counter
										$NonFrozenIndex = $NonFrozenIndex - 1;
										#get suffix before adding to frozen files list (for filtering in the gnumake)
										$CurrFileName = $suffix{$CurrFileName};
									}
									# updtae Frozen files Array for filtering
									# this list is out of the if because it also the list of all frozen files for users
									# we dont worry about files without suffix here because they will not be regarded by the filter (not relevant)
									push(@FrozenFilesArr,$CurrFileName);
									#update counters
									$SortFilesNumber+=1;
									$FrozenIndex+= 1;
							   	}
							}
	   					}

						#----------------  check for Frozen files in the Frozen Label files ------------------
						# first check if the file is Frozen Label
	   					if (defined($FrozenLabelFilesHush{$CurrFileName}))
	   					{
	   						# check if it is mapped to the ROM
	   						if ((hex($a[1]) >= $RomStartAddress) && (hex($a[1]) < $RomEndAddress))
	   						{
								#check files hash to not copy twice the same file
								if (!defined($CheckFiles{$CurrFileName}))
								{
									# update the hash
									$CheckFiles{$CurrFileName}=1;
									if (defined($suffix{$CurrFileName}))
									{
										# sending file to text files
			   							# ---------------------------------
		   	   							# send to linker files list
	   		   							$FrozenTextOutputFormat =$DojFileLibrary."\\".$CurrFileName.".doj";
										# we prepare an array for the linker text file. we wioll print it only after sorting it.
										# the reason is that in order to preduce same ROM mask we need same files order for the linker
										push(@FrozenTextFilesList,$FrozenTextOutputFormat);
									  	#prepare list of files to be copied
										$FilesToBeCopied{$CurrFileName}=1;
										# remove file name from frozen Label list
										delete $FrozenLabelFilesHush{$CurrFileName};
										# update counter
										$FrozenLabelIndex = $FrozenLabelIndex - 1;
										#get suffix before adding to frozen files list (for filtering in the gnumake)
										$CurrFileName = $suffix{$CurrFileName};
									}
									# updtae Frozen files Array for filtering
									# this list is out of the if because it also the list of all frozen files for users
									# we dont worry about files without suffix here because they will not be regarded by the filter (not relevant)
									push(@FrozenFilesArr,$CurrFileName);
									#update counters
									$SortFilesNumber+=1;
		   							$FrozenIndex+= 1;
								}
							}
	   					}
	   				}
	   			}
				}
	   		 }
			 }
	   		 $templine = <MAP>;
	 	}
	}
	$templine = <MAP>;
}

# close files handles
close (FROZEN);
close (NON_FROZEN);
close (FROZEN_TEXT_FILE);

############################ printing to files all the lists ######################################
# open text files we create as output
$FrozenLabelPath = ">".$OutPutFilesPath."Frozen_Label_Files_list_".$BuildScenario.".txt";
$FrozenPath = ">".$OutPutFilesPath."Frozen_Files_list_".$BuildScenario.".txt";
$FrozenTextPath = ">".$OutPutFilesPath."\\A0_ROM_file_list_".$BuildScenario.".txt";
$NonFrozenPath = ">".$OutPutFilesPath."Non_Frozen_Files_list_".$BuildScenario.".txt";
$ErrorPath = ">".$OutPutFilesPath."Warning_Files_list_".$BuildScenario.".txt";

open (FROZEN_LABEL, $FrozenLabelPath) || die "Can not open $FrozenLabelPath file.\nFile might not exists or exists as read only.\n";
open (FROZEN, $FrozenPath) || die "Can not open $FrozenPath file.\nFile might not exists or exists as read only.\n";
open (FROZEN_TEXT_FILE, $FrozenTextPath) || die "Can not open $FrozenTextPath file.\nFile might not exists or exists as read only.\n";
open (NON_FROZEN, $NonFrozenPath) || die "Can not open $NonFrozenPath file.\nFile might not exists or exists as read only.\n";
open (WARNING, $ErrorPath) || die "Can not open $ErrorPath file.\nFile might not exists or exists as read only.\n";

#----------------------------------- printing ------------------------------------------------

# ------------------------------- linker text file --------------------------------------
# first we print the text file for the linker including all the frozen files to be linked.
# first we sort the list
@FrozenTextFilesList = sort(@FrozenTextFilesList);
# now we print it
foreach $files (@FrozenTextFilesList)
{
	print FROZEN_TEXT_FILE ("$files\n");
}
# -------------------------------- frozen files list -------------------------------------
# first we sort the list
@FrozenFilesArr = sort(@FrozenFilesArr);
foreach $files (@FrozenFilesArr)
{
	print FROZEN ("$files\n");
}
# -------------------------------- Non Frozen files list -------------------------------------
foreach $files (keys %NonFrozenFilesHush)
{
	print NON_FROZEN ("$files\n");
}
# -------------------------------- Frozen Label files list -------------------------------------
foreach $files (keys %FrozenLabelFilesHush)
{
	print FROZEN_LABEL ("$files\n");
}
# ---------------------------------- Warning files list -----------------------------------------
foreach $files (@WarningFilesArr)
{
	print WARNING ("$files\n");
}

# each file of the unreferenced that was not reported as a Frozen file will be reported as Non Frozen
# create a title in the Non Frozen file to seperate between the used and unreferenced files

print NON_FROZEN "\n  ----------------------------------------------------------------------------------\n";
print NON_FROZEN "  -------- from this point these files are unreferenced Non Frozen files -----------\n\n";

$NonFrozenUnRefIndex = 0;
foreach $UnrefFile (keys %UnferHash)
{
	if ($UnferHash{$UnrefFile}=~ /NonFrozen/)
	{
		$NonFrozenUnRefIndex = $NonFrozenUnRefIndex + 1;
		print NON_FROZEN "$UnrefFile\n";
	}
}



###################################  Copy the Files #################################################
$i = 0;
foreach  $CurrentFile (keys (%FilesToBeCopied ))
{
	# GENERAL REMARK:
	# we copy only Frozen files which need to be copied (also warning files) - files in the linker list.
	# it is not a bug to treat an warning file as a Frozen - the user just lose flexibility in the code
   	# NOTE: there are files we dont have their source code and therefore their doj files
   	# we use the libraries of these files. these files doj files should be already present in the dedicated library
  	# list of some of this files: if (($CurrentFileName !~ /memcpy_align32/)&&($CurrentFileName !~ /memcpy_align16/)&&($CurrentFileName !~ /ippsfftfwd_ctoc_n_16sc/)&&($CurrentFileName !~ /ippsfftinv_ctoc_n_16sc/)&&($CurrentFileName !~ /ippszero_16s/)&&($CurrentFileName !~ /abs/)&&($CurrentFileName !~ /ippsmax_16s/)&&($CurrentFileName !~ /ippssqrt_16s_isfs/)&&($CurrentFileName !~ /ippsaddc_16s_i/)&&($CurrentFileName !~ /ippsthreshold_lt_16s_i/)&&($CurrentFileName !~ /ippscopy_16s/)&&($CurrentFileName !~ /ippsmean_16s/))
   	# we filter these files by their presence in the suffix hash because if they dont have source files then they wont be there.

  	#copy the doj files
  	#-------------------------
	if (defined($suffix{$CurrentFile}))
	{
		$i = $i+1;
		print "The number of the copied file is: $i\n";
	  	# prepare the path
	  	$CurrentFilePath = $entity{$CurrentFile};
		$CurrentFilePath = $CurrentFilePath."\\".$CurrentFile.".doj";
		# dos command for copy files
	  	system 'copy'.' '.$CurrentFilePath.' '.$DojFilesTarget.' /Y';
	  	if ($? != 0 )
	  	{
	  		print "ERROR: could not copy $CurrentFilePath: Bad path or does not exist or already exists another read-only file with the same name under build\\Tavor_A0_ROM directory!\n";
	  		exit 1;
	  	}
	}
}
#} #end of copy debugg if

################################### close files ##################################################
close (FROZEN); #done in the end after checking the unreffered files
close (FROZEN_LABEL);
close (NON_FROZEN); #done in the end after checking the unreffered files
close (FROZEN_TEXT_FILE); #done in the end after checking the unreffered files
close (WARNING);


####################################### print summery ############################################
print "\n----------- SORT COPY FILES PROGRAM REPORT -----------------------\n";
print "finished sorting files into groups\n";
print "total number of files that were sorted : $FilesNumber\n";
print "total number of sorted files is $SortFilesNumber\n";
print "sub groups:\n";
print "Frozen files = $FrozenIndex files \n";
print "Frozen Label files = $FrozenLabelIndex files\n";
print "Non Frozen files = $NonFrozenIndex files\n\n";
print "number of unreferred files $RefIndex2\n";
print "There were $RefIndx Unreferred files that were classified as Frozen files\n";
print "There were $i files that were copied\n";
print "------------- END OF SORT COPY PROGRAM ---------------------------\n";
################################### End of Program ##################################################
