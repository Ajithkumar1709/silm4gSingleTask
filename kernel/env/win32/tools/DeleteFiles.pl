#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

############################################################################
# DeleteFiles	#5/12/2007 
# Ron Zeira
############################################################################

#this scrtipt erases files and folders
#Usage DeleteFiles.pl configfile
#deletes files under [Erase These Files] and folders under 
# [Erase These Folders] from the folder under [Base Folders]

sub ReadParamsFromFile($$);

#get configuration file name
$Configuration_file = shift;

#get base folders from config
@base_folders = ReadParamsFromFile($Configuration_file,"Base Folders");
#get file to delete list
@erase_files = ReadParamsFromFile($Configuration_file,"Erase These Files");
#get folder to delete list
@erase_folders = ReadParamsFromFile($Configuration_file,"Erase These Folders");

foreach $line (@base_folders)
{
	print "Deleting file & folders from $line:\n";
	$base = $line;
	# ERASE FILE !!!!
	foreach $file (@erase_files)
	{
	     if ($file ne "")
        {
          $line = "$base"."$file";
          system("del /Q /F $line");
          print "\n** $line was deleted"
        }
	}
	# ERASE FOLDERS
	foreach $folder (@erase_folders)
	{
	     if ($folder ne "")
        {
     	  $line = "$base"."$folder";
   		  system("rd /S /Q $line");
  		  print "\n** $line was deleted"
        }
	}
	print "\nFinished Deleting\n";
}


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
