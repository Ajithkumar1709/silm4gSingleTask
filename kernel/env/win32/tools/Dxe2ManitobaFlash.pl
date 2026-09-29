#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
#* DSPC Proprietary Information, (C) COPYRIGHT 2000 DSPC, an Intel Company
#* File name:    Dxe2QTManitobaFlash.pl
#* Programmer:   Evgeny M.
#* Create Date:  Nov, 2002                                                   
#* Description:                                                              
#*  This program generates file for Flash programming for Manitoba flash.   
#*  It uses several MSA and other utilities:
#*   elfsplmsa - MSA splitter, which extracts all loadable sections from dxe file into FTK-formatted file.
#*   x2hex     - Convert FTK format files to Intel Hex file
#* Notes:
#   The script it not modular and any change in the Memory region is not suppoted
#*  
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#configuration parameters and default values
$DEBUG = 1;
$Verbose = 1;
$UnixFormat = 1;
$FTKOutputFile   = 1;
$HexOutputFile   = 0;
$BinOutputFile   = 0;
$AsciiOutputFile = 0;
$FlashStartAddr = 0xD0000000; # default value
$FlashEndAddr   = 0xD0080000; # default value

$Usage =          "Usage: $0 <DXE_file_name> [-bin] [hex] [-asc] [-v]\n";
$Usage = $Usage . " Generates specialy formatted file for MANITOBA Flash programming \n";
$Usage = $Usage . " Parameters:\n";
$Usage = $Usage . "  * DXE_file_name        The name of the input DXE file (with or without .dxe).\n";
$Usage = $Usage . " Options:\n";
$Usage = $Usage . "  * -bin  ....  Output file is binary     \n";
$Usage = $Usage . "  * -hex  ....  Output file is Intel hex  \n";
$Usage = $Usage . "  * -asc  ....  Output file is Flash ASCII\n";
$Usage = $Usage . "  * -v    ....  Do it verbosely (print some info messages)\n\n";

$Usage = sprintf $Usage, $FlashStartAddr, $FlashEndAddr;

((scalar @ARGV) < 1) && die "$Usage";

$dxe_file = shift (@ARGV);

# check if the dxe file name has the extension or not
if ( $dxe_file =~ /(.*[\\\/])(\w+)\.?(\w*)$/ ) {
  $in_path = $1;
  $base_name = $2;
  if ( $3 =~ /^$/ ) { $dxe_file = $in_path . $base_name . ".dxe"; }
}
elsif ( $dxe_file =~ /(\w+)\.?(\w*)$/ ) {
  $in_path = "";
  $base_name = $1;
  if ( $2 =~ /^$/ ) { $dxe_file = $in_path . $base_name . ".dxe"; }
}
else {
  die "Input file name is of unknown format, pls, report bug to Evgeny.Mezhibovsky\@intel.com\n";
}

open(DXEFILE , "< $dxe_file") || die "$0: Can't open '$dxe_file'.\n";

# default values
$out_file = $base_name . $OutFileDefaultExtension;
$Verbose = 0;

#process parameters and options
$ParamNum = (scalar @ARGV);
while ( $ParamNum != 0 ) { 
  $param2 = shift (@ARGV);
  if ( $param2 =~ /^-.*/ ) {
	if    ( $param2 =~ /^-S$/ )    { $FlashStartAddr = hex(shift (@ARGV)); }
	elsif ( $param2 =~ /^-E$/ )    { $FlashEndAddr = hex(shift (@ARGV)); }
	elsif ( $param2 =~ /^-dos$/ )  { $UnixFormat = 0; }
	elsif ( $param2 =~ /^-v$/ )    { $Verbose = 1; }
	elsif ( $param2 =~ /^-hex$/ )  { $HexOutputFile = 1; }
	elsif ( $param2 =~ /^-bin$/ )  { $BinOutputFile = 1; }
	elsif ( $param2 =~ /^-asc$/ )  { $AsciiOutputFile = 1; }
	else {die "$0: '$param2' - unknown option\n";}
  }
  else { $out_file = $param2;}
  $ParamNum = scalar(@ARGV);
}

open(OUTFILE , "> $out_file") || die "$0: Can't open '$out_file'.\n";
if ( $UnixFormat == 1 ) { binmode OUTFILE; }

# End of parameters processing

$EL = "\f";

# Extract loadable sections from dxe fileusing Nordhem tool elfsplmsa
if ( ($DEBUG == 1) || ($Verbose == 1) ) {print "\"elfsplmsa\" -ram -o $base_name -f x $dxe_file\n";}
system("\"elfsplmsa\" -ram -o $base_name -f x $dxe_file") == 0 or die "elfsplmsa exited with error\n";

$x_file = "$base_name" . ".x_0";
open(XFILE , "< $x_file") || die "$0: Can't open '$x_file'.\n";


# Read the input file
$Continue = 1;
$line = <XFILE>;
while ( $Continue == 1) {
  	$Section = {};
  	if ( $line =~ /^\@P([\d,\w]{8})/ ) { 
		$Section->{addr} = hex($1);
		$Section->{size} = 0; 
		$Section->{data} = "";
		$SectionEnd = 0;
       $Section->{flag} = 2;    #flagsCahgne
		
		while ( ($SectionEnd == 0) && ($line = <XFILE>) ) {
	  	if ( $line =~ /^\@P([\d,\w]{8})/ ) { 
			$SectionEnd = 1;
	  	}
	  	else {
			$Section->{size}++ ; 
			$Section->{data} = $Section->{data} . "$line";
	  	}
		}
		if ( $SectionEnd == 0) { $Continue = 0;}
  	}
	
  	push @SectionDB, $Section;
	
} # while ( $line = <XFILE> )

# close and remove .x_0 file
close XFILE;
if ($Verbose) {print "Removing $x_file ...\n";}
system("del /Q /F $x_file");

if ($Verbose) {
  print "Original Memory sections ****************\n";
  for $el ( @SectionDB ) {
	printf "Addr = %x   Size = %04.X\n", $el->{addr}, $el->{size};
  }
  print "******************************************\n";
}

# sort the @SectionDB by the starting address
@SectionDB = sort {($a->{addr}) <=> ($b->{addr});} @SectionDB;

# Take all the memory section inside the flashand pad them with 0's or 1's
# ok_section -
#   All memory inside flash with bit 16 (IN WORD ADDRESS !!!) = 1  (sample 0xd0000000-0xd0020000) - Pad with 1's between code sections
# bad_section-
#   All memory inside flash with bit 16 (IN WORD ADDRESS !!!) = 1  (sample 0xd0020000-0xd0040000) - fill with 1's

$EndOfLastSection = $FlashStartAddr;
$EndOfWriteZone   = 0xD0080000; # End of the last "ok_section" to write to. 
								# When set to 0xD0080000 , no bad saction in FLASH
for $el ( @SectionDB ) {
	printf "Proccesing , Please wait. Current original section %x\r", $el->{addr} ;
	if (( ($el->{addr}) >= $FlashStartAddr ) && ( ($el->{addr}) < $FlashEndAddr ) ) {
	   # If the next section is not in the current "ok-section"
		# The current zone have to pad until its end with 0's and the near bad zone
		# need to be fill with 1's until we reach the ok section where the current memory section is located
  		while (( $el->{addr}) > $EndOfWriteZone){
	  		# define a empty section to pad (between existing sections
	  		$Section = {};
	  		$Section->{addr} =  $EndOfLastSection;
	  		$Section->{size} = ($EndOfWriteZone- $EndOfLastSection)/2 ; # (size in words)
	  		$Section->{data} = "";
			$Section->{flag} = 1;    #flagsCahgne

			# add the new 1's section to the output array
			push @OutputDB, $Section ;  
		
	  		# Pad "bad-section" with F's until its end.
	  		$Section = {};
 	  		$Section->{addr} = $EndOfWriteZone ;
	  		$Section->{size} = 0x20000/2 ; # (size in words)
	  		$Section->{data} = "";
			$Section->{flag} = 1;    #flagsCahgne
			# add the new 0's section to the output array
			push @OutputDB, $Section ;  # fill ok zone with 0
	  		#update temp vars that point to the current "ok-section"
	  		$EndOfWriteZone += 0x40000;
	  		$EndOfLastSection= $EndOfWriteZone - 0x20000;
		}
	
		# If the next section is in the cuurent "ok-section"
  		if (( $el->{addr}) > $EndOfLastSection){
			# Pad the "ok-section" with 0's  until its end
			$Section = {};
 			$Section->{addr} = $EndOfLastSection ;
			$Section->{size} = (( $el->{addr}) - $EndOfLastSection)/2 ; # (size in words
		
  $Section->{data} = "";
			$Section->{flag} = 1;    #flagsCahgne

			# add the new 0's section to the output array
			push @OutputDB, $Section ;  
   		}
		$EndOfLastSection = (($el->{addr})) + (($el->{size})*2) ;
		# add the memory section to the output array
		push @OutputDB, $el ;
  	}
}

# Pad the rest of the memort from the end of the last memory section
while ( $EndOfWriteZone <= $FlashEndAddr) {
	if ($EndOfLastSection < $EndOfWriteZone) {
    	$Section = {};
    	$Section->{addr} =  $EndOfLastSection;
    	$Section->{size} = ($EndOfWriteZone- $EndOfLastSection)/2 ; # size in words?
		$Section->{data} = "";
		$Section->{flag} = 1; #flagChange
		push @OutputDB, $Section ;  # fill ok zone with 0
	}
   # Solve case when no bad zones are declare (-> $EndOfWriteZone = 0xD0080000)
	if ($EndOfWriteZone != $FlashEndAddr) {
		# set bad sections untill the end of the bad section
		$Section = {};
  		$Section->{addr} = $EndOfWriteZone ;
  		$Section->{size} = 0x20000/2 ; # size in words
  		$Section->{data} = "";
		$Section->{flag} = 1; #flagChange
		push @OutputDB, $Section ;  # fill ok zone with 0
	}
	$EndOfWriteZone += 0x40000;
  	$EndOfLastSection= $EndOfWriteZone - 0x20000;
}


## End Create an Struct that hold all the memory section that place in the FALSH
## The FLASH memory is pad with 0's in the write erea and with f's in the bad eraes
if ($Verbose) {
  print "New Memory sections **********************                                \n";
  for $el ( @OutputDB ) {
	printf "Addr = %x   Size = %04.X\n", $el->{addr}, $el->{size};
  }
  print "******************************************\n";
}


# Create an update ftk file (AlwaYs !)
###########################
if ( $FTKOutputFile ) {
	$ftk_file = "$base_name" . ".ftk";
	open(FTKFILE , "> $ftk_file") || die "$0: Can't open '$ftk_file'.\n";
	printf "* Creating '$ftk_file' 										\n";
	for $el ( @OutputDB )
	{
  	    # Write Section Address
		printf FTKFILE "\@P%x\n", $el->{addr};
		# Write Section Data
		# Empty section that where pad with 1's
		if ( $el->{flag} == 1 ) {
			$word = "\$ffff\n";
			for ( $loopcounter = $el->{size} ; $loopcounter > 0 ; $loopcounter-= 1 ) {
				printf FTKFILE "%s", $word;
    		}
		}
		# Original memory sections
		else  {
  			@DataW = split /\$/m, $el->{data}; # split data into the array of words
			shift @DataW;
			for $word ( @DataW ) {
				printf FTKFILE "\$%s", $word;
  			}
		}
	}
}

# Create an update INTELHEX file
################################
if ( $HexOutputFile ) {
	$hex_file = "$base_name" . ".hex";
	printf "* Creating '$hex_file'									    \n";
	system("\"x2hex\" $ftk_file > $hex_file" ) == 0 or die "x2hex exited with error\n";
}

# Create bin output file
########################
if ( $BinOutputFile  ) {
   	$bin_file = "$base_name" . ".bin";
	open(BINFILE , "> $bin_file") || die "$0: Can't open '$bin_file'.\n";
	binmode BINFILE;
	printf "* Creating '$bin_file' 										\n";
	for $el ( @OutputDB ) {
		# Empty section that where pad with 1's
		if ( $el->{flag} == 1 ) {
  			# Write @Data to output file
  			for ( $loopcounter = ($el->{size})*2 ; $loopcounter > 0 ; $loopcounter-= 1 ) {
				$temp =  0xffff ;
				$temp_bin = pack "S" ,$temp ;
				syswrite BINFILE , $temp_bin, 1; 
			}
		}
		# Original memory sections
		else {
			$el->{data} =~ s/\$//g; # remove '$' sign from data
  			$el->{data} =~ s/\s/ /g; # remove '\n' sign from data
  			@DataW = split / /m, $el->{data}; # split data into the array of words
	
			# split data into the array of bytes
  			for $word ( @DataW ) {
				$word =~ /^(\w{2})(\w{2})$/;
				push @BinData, $2, $1;
   			}
	
  			# Write @Data to output file
  			for ( $loopcounter = ($el->{size})*2 ; $loopcounter > 0 ; $loopcounter-= 1 ) {
				$temp =  hex(shift( @BinData ) );
				$temp_bin = pack "S" ,$temp ;
				syswrite BINFILE , $temp_bin, 1; 
			}
		}
    }
}

# Create ASCII output file
########################## 
if ( $AsciiOutputFile ) {
	$ascii_file = "$base_name" . ".asc";
	open(ASCIIFILE , "> $ascii_file") || die "$0: Can't open '$ascii_file'.\n";
	printf "* Creating '$ascii_file' 									\n";

	$Address = 0x0000;
   	for $el ( @OutputDB )
	{
  		# Write Section Address
  		#printf "%x\n", $el->{addr};
	
  		printf FTKFILE "\@P%x\n", $el->{addr};
  		# Write Section Data
		# Pad section memory
		if ( $el->{flag} == 1 ) {
			$word = "ffff";
			for ( $loopcounter = $el->{size} ; $loopcounter > 0 ; $loopcounter-= 1 ) {
				printf ASCIIFILE "%05X %s\r", $Address++, $word;
    		}
		}
		# Original section memory
		else  {
			$el->{data} =~ s/\$//g; # remove '$' sign from data
  			$el->{data} =~ s/\s/ /g; # remove '\n' sign from data
  			@DataW = split / /m, $el->{data}; # split data into the array of words
		
			#@DataW = split /\$/m, $el->{data}; # split data into the array of words
			for $word ( @DataW ) {
	  			printf ASCIIFILE "%05X %s\r", $Address++, $word;
  			}
		}
	} # end of ASCII
}





























































































































































































































































