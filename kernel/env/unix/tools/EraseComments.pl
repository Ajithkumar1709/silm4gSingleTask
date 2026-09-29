#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

############################################################################
# DeleteFiles	#5/12/2007 
# Ron Zeira
############################################################################


#usage: EraseComments.pl path string
#deletes everything between
#  string Section To Remove - Start
#  string Section To Remove - End

#read path
$path = shift;
#read section with spaces
$string = join (' ',@ARGV);

$ReadOnlyFiles = 0;
$NumOfOpenFiles = 0;

# dir the desire directory
@p = `cmd /c dir /B /S $path`;
chomp @p;
#print "\n @p \n";

print "Start removing $string sections from $path\n";
# look for files inside DIR resualts
foreach $line (@p) {
  # with extention *.C *.c *.H *.h *.ldf *.asm *.mak *.txt *.org *.CQ000dddd
	while ($line=~/(.+\.((ldf)|([cChH])|(asm)|(mak)|(txt)|(org)|(CQ000[0-9][0-9][0-9][0-9][0-9])))$/g)
  {
    #$CurrentFilePath = "$path\\$1";
    $CurrentFilePath = "$1";
    #check if file is writable
      #print " Working on $CurrentFilePath\n";
      open	(SOURCE_FILE, "<$CurrentFilePath") || die "cannot open file";
      $NumOfOpenFiles ++;
      $StartCounter = 0;
      $changes = 0;
      @lineDB = "";
      while ($line = <SOURCE_FILE>)
      {
        if ($line =~ /$string Section To Remove - Start/i)
        {
          $StartCounter ++ ;
          $changes++;          
        }
        # Read Source line to array
        if ($StartCounter == 0){
          push @lineDB, $line;
        }

        if ($line =~ /$string Section To Remove - End/i)
        {
          $StartCounter -- ;
        }
        # senety Code check
        if ($StartCounter < 0){
          die " \n **** Error: Section END with no Section Start in file $CurrentFilePath\n"
        }
      }
      # close the source after reading it to array
      close SOURCE_FILE;
      # senety Code check
      if ($StartCounter > 0)
      {
        die " \n **** Error: Section Start with no Section End in file $CurrentFilePath\n"
      }
      if ($changes > 0)
      {
      		# if read only remove option

		   if (!( -w $CurrentFilePath) )
		    {
		 		@com =`cmd /c attrib $CurrentFilePath -R`;
		 		chomp @com;
		 		push (@ReadOnlyFiles, "$1\n");		
	   	 	}
		  $ReadOnlyFiles++;	
	      # open the output file (The same file that we read from ...
	      open(SOURCE_FILE , "> $CurrentFilePath") || die "$0: Can't open $CurrentFilePath \n";

	      for $line ( @lineDB )
	      {
	        print SOURCE_FILE $line;
	      }

	      close SOURCE_FILE;

	    	$NumOfOpenFiles++;
				push (@OpenFiles, "$1\n");
		}
  }
}

if ( $ReadOnlyFiles == 0 ) {
    print "No files files were update\n";
}
else  {
	print "End of process $ReadOnlyFiles files were changed\n";
}

