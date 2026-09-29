#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

############################################################################
# Source_clean	#5/12/2007
# Ron Zeira
############################################################################

# Source clean script
# the following scripts consists of activating 3 scripts:
# 1. delete files under or folder under [Erase These File/Folder] in the config file
#	uses DeleteFiles.pl
# 2. remove sections defined in [Remove These Sections] with EraseComments.pl
# 3. removes flags in [Remove These Flags] with constraints according to 
# 	[Ignore These Files] [Ignore These Folders] [Flag DB]. uses RemoveCompilationFlagConfig.pl
# all these actions are done to all the subfolders under each path of [Base Folders]
# activatione Source_clean.pl config.txt
#where config.txt is from the form below:
# [Base Folders]
# H:\
# [Erase These Files]
# wb_fw\wb_drivers\inc\AfcDriver.h
# [Erase These Folders]
# wb_fw\wb_drivers\src
# [Remove These Sections]
# GERAN only
# [Remove These Flags]
# ROM_MASK_M03
# [Ignore These Files]
# tavor_config.h
# [Ignore These Folders]
# gsm_fw_ttp
# [Flag DB]
# ROM_MASK,6
# ROM_MASK_M03,3


# Ron Zeira
# December 2007 

#function prototype
sub ReadParamsFromFile($$);

$Configuration_file = '';
$strip = 0;
$deletion = 0;
$compilation = 0;
$help = 0;
#read configuartione file name and options
foreach $param (@ARGV)
{
	if ($param =~ /^\-/)
	{
		#options
		if ($param eq '-S'){
			$strip = 1;
		} elsif ($param eq '-D') {
			$deletion = 1;
		} elsif ($param eq '-C') {
			$compilation = 1;
		} elsif ($param eq '-h') {
			$help = 1;
		}
	}
	else
	{
		#configuration file
		$Configuration_file = $param;
	}
}

if ($help)
{
	print "Usage: source_clean.pl configuration_file_name [options]\n";
	print "\toptions:\n";
	print "\t\t-S for strip script\n";
	print "\t\t-D for deletion script\n";
	print "\t\t-C for Compilation-Flag-Remover script\n";
	print "\t\t-h for help\n";
	die "\nThanks for asking\n";
}

print "Start Cleaning:\n\n";

# call the delete files script with the config file
if ($deletion)
{
	print "\nDeleting:\n\n";
	system("perl DeleteFiles.pl $Configuration_file");
}

if ($strip)
{
#get base folders from config
	@base_folders = ReadParamsFromFile($Configuration_file,"Base Folders");
#get sections to remove list
	@sections = ReadParamsFromFile($Configuration_file,"Remove These Sections");
#call the remove comments script for each of the of the paths and sections
	print "\nRemoving comments:\n\n";
	foreach $path (@base_folders)
	{
		foreach $section (@sections)
		{
			system("perl EraseComments.pl $path $section");		
		}
	}
}

if ($compilation)
{
# call remove flags script with the config file
	print "\nRemove flags:\n\n";
	system("perl RemoveCompilationFlagConfig.pl $Configuration_file");		
}


print "\nEnd Clean\n";



#reads from the given file name the list under a given [string]
sub ReadParamsFromFile($$)
{
	my $name = shift;
	my $string = shift;
	my $line;
	my @array;
	my $inside_section = 0;
	open(SOURCE_FILE, "< $name") || die "\ncannot open file $name";
	#read file
	@file_lines = <SOURCE_FILE>;
	close SOURCE_FILE;
	#go over the lines
	foreach $line (@file_lines)
	{
		chomp $line;
		#[.*]doesn't count and end the section
		if ($line =~ /\[.*\]/)
		{
			$inside_section = 0;
		}
		#collect the items under the string
		if ($inside_section == 1)
		{
			#do not insert empty lines
			if ($line ne ""){
				push (@array,$line);
			}
		}
		#start collecting
		if ($line =~ /\[$string\]/)
		{
			$inside_section = 1;
		}	
	}
	return @array;
}
