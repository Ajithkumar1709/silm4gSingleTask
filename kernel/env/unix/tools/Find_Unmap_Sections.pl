#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
#* DSPC Proprietary Information, (C) COPYRIGHT 2000 DSPC, an Intel Company
#* File name:    FindUnmapSections.pl
#* Programmer:   Ohad S.
#* Create Date:  Dec, 2002                                                   
#* Description:                                                              
#*	This script Open a map file and look for input setion that are not mapped
#*  The problematic sections can be find using their address and size
#*  Adress == 0x0 and size !== 0x0 point that the section was not mapped !!!
#*
#* Notes:
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

$Usage =          "Usage: $0 <MapFile> \n";
$Usage = $Usage . "Look in Map file for linker problems \n";
$Usage = $Usage . "1. Look for Input sections with Address == 0 and Size != 0 \n";


((scalar @ARGV) < 1) && die "$Usage";
$map_file = shift (@ARGV);
open(MAPFILE , "< $map_file") || die "$0: Can't open '$map_file'.\n";

# The Section to work on start with a comment that contain 'Input section'
#  for the first time in the file
$SectionToSearch = 0;
while ( $SectionToSearch == 0 ) {
	$line = <MAPFILE>;
	if ($line =~ m/Input section/){
		$SectionToSearch =1;
	}
}

$Error = 0 ;
# Outer loop read all the lines until the end of the file that is
#  ends about 4 lines after the last data
printf " \nStart checking %s  for unmapped sections , please wait ...\n",$map_file;
print "Unmapped Sections ... ";

while ( $line = <MAPFILE> ) {
	# Read the line , Extract from the line to datas.
	# The second and the third word in the line are the Address and the Size

	@samples = split /\s+/ , $line ;       # Split the line on whitespaces
	$FirstDataInLine = shift( @samples );

	if ( $line =~ m/Output Section/) {     # Save the current Output section
		$OutputSection = shift( @samples );
		$OutputSection = shift( @samples );
	}
	elsif ( $FirstDataInLine !~ m/.debug/ ) {  # Ignor Debugger sections
    	$Address = shift( @samples );
    	$Size = shift( @samples );
    	if ( ($Address eq "0x0")&&($Size ne "0x0" ) )  {
			$Error = 1;
			printf "\n* Output Section: %s  Input section : %s" , $OutputSection, $FirstDataInLine;
		}
	}
}

if ( $Error == 0  ) {
	printf " \r Good Work .... No Unmapped sections !!!\n ";
}
else{
	print  "\n *****";
	printf "\n No more unmapped sections in the current map file !!!\n ";
}

close(MAPFILE);
exit 1;
