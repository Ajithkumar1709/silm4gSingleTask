#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
#* DSPC Proprietary Information, (C) COPYRIGHT 2000 DSPC, an Intel Company
#* File name:    Add EOFpl
#* Programmer:   Ohad S.
#* Create Date:  Jan , 2003                                                   
#* Description:  This script get a PATH to an exist folder. It look for all the
#*			     C files in it and add \n at the end of all these files
#* Notes:
#*    The Script does not handle read only files.
#*  
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#configuration parameters and default values
$DEBUG = 0;
$Verbose = 0;
$NumOfOpenFiles = 0;
$ReadOnlyFiles =0;

$Usage =          "Usage: $0 <PATH>\n";
$Usage = $Usage . " \n";
$Usage = $Usage . " The Script will add \\n To all *.c files in the given dir.\n";
$Usage = $Usage . " (!) It will not write to Read-only files \n";
$Usage = $Usage . " Parameters:\n";
$Usage = $Usage . "  PATH : Full path (include driver) to the folder\n";
$Usage = $Usage . "  -v   : Do it verbosely (print some info messages)\n\n";

((scalar @ARGV) < 1) && die "$Usage";

$path = shift (@ARGV);	#Read Path from input

$ParamNum = (scalar @ARGV);
while ( $ParamNum != 0 ) { 
  $param2 = shift (@ARGV);
  if ( $param2 =~ /^-.*/ ) {
	if    ( $param2 =~ /^-v$/ )    { $Verbose = 1; }
	else {die "$0: '$param2' - unknown option\n";}
  }
  $ParamNum = scalar(@ARGV);
}

#dir the desire directory
@p = `dir $path`;
foreach $line (@p) {
	while ($line=~/(\w+\.[CcHh])/g) {#Match word.c or word.C
    $CurrentFilePath = "$path\\$1";
    if (!( -w $CurrentFilePath) ) { #check if file is writable
			if ( $Verbose == 1 ) {print "\n Error: $1 is Read-only";}
			$ReadOnlyFiles++;
			push (@ReadOnlyFiles, "$1\n"); 
		}
		else  {
			open	(C_FILENAME, ">>$CurrentFilePath") || die "cannot open file";
			print	C_FILENAME "\n";
			close	(C_FILENAME);
			$NumOfOpenFiles++;
			push (@OpenFiles, "$1\n");
		}
	}
}

WriteResultsFiles();

if ( $ReadOnlyFiles == 0 ) {
	print "\n End of process :\n* Add \\n to $NumOfOpenFiles files \n";
 	print "* List of files in $TextFilePath\n";
}
else  {
	print "\n End of process :\n* Add \\n to $NumOfOpenFiles files \n";
	print "* $ReadOnlyFiles files were Read only\n";
	print "* List of files in $TextFilePath\n";
}



############################################################################
sub WriteResultsFiles
############################################################################
{
	$TextFilePath = ">"."$path"."\\FilesList.txt";
	open	(RESULTSFILE, $TextFilePath) || die "cannot open results file";
	print   RESULTSFILE ("Last execute of AddEOF.pl Results:\n");
	print   RESULTSFILE ("Files that were open and \\n was added\n");
	print   RESULTSFILE ("--------------------------------------\n");
	print   RESULTSFILE "@OpenFiles \n";
	if ( $ReadOnlyFiles > 0 ) {
	 print   RESULTSFILE ("Read Only files \n");
	 print   RESULTSFILE ("----------------\n");
	 print   RESULTSFILE "@ReadOnlyFiles";
	}

}##WriteResults

