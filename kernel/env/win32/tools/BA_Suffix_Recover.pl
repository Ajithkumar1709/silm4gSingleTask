#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/bin/perl -w

########## ------------------ BA_Suffix_Recover.pl ---------------- #######################
#  this file porpuses:
#
#    1. generate a list of all the files without their suffix and their match suffix.
# 		used to create filter list for the gnumake.
#
# ########## --------------------------------------------------- #######################

#defines a hash for user switches
%dTable=(-h=>\&help,
		 -i=>\&Input);

# function : help function for user
# ---------------------------------
sub help
{
	print "--------------------------------------------------------------------------------";
	print "this file is part of the BA module.\n";
	print "generate a list of all the files without their suffix and their match suffix.\n";
 	print "that list is used to create filter list for the gnumake.\n";
	print "the program receive the project root directory from macro.mk in the target\n";
	print "Input:  Program must receive as an input the Text File library name \n"; 
	print "Usage:  BA_Frozen_Label_Mapping [-h -i]  <Text File Libaray Name>\n"; 
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
}

# get program arguments
# -------------------------------------
if ($p=shift @ARGV)
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
else
{
	print "ERROR: wrong usage of program - missing arguments\n";
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

# Project paths
$BuildDirPath = ".\\";
$OutPutFilesPath = $FileLibrary."\\";

############################### retrieve suffixes from FilesNameslist.txt  ####################################

$NamesPath = $BuildDirPath."Files_Names_list.txt";
open(LOG, $NamesPath) || die "can't open : Files_Names_list.txt - problem with gnumake";
$templine = <LOG>;
while(defined($templine))
{
	if ($templine=~ /Source.*: (.*)$/) #in this line there are all the source files in the package/group
	{
		@a=split(qq( ),$1);
		foreach $a (@a)
		{
			$b=$a;
			$b =~ s/^(\w+)\.\w+$/$1/;
			$b =~ tr/[A-Z]/[a-z]/;
			if (not defined $b{$b})
			{
		   		$b{$b}=$a;
			}
		}
	}
	$templine = <LOG>;
}

close(LOG);

################################## printing all the files with their entities #########################
$SuffixPath = ">".$OutPutFilesPath."FilesSuffixes_".$BuildScenario.".txt";
open(LIBRARY,$SuffixPath)||die "Cant open FilesSuffixes.txt\n" ;
foreach $CurrentFileName (keys (%b))
{
	print LIBRARY "$CurrentFileName ";
	print LIBRARY "$b{$CurrentFileName}\n";
}
close(LIBRARY);


