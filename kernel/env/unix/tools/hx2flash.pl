#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#* DSPC Proprietary Information, (C) COPYRIGHT 2000 DSPC, an Intel Company
#* File name:    hx2flash.pl
#* Programmer:   Ohad S.
# *				 (updated by Erez Ben-Yaacov)
#* Create Date:  March 2003
#* Last Updated: April 2005
#* Description:
#*  This program Converts hx format files to different FLASH formats files.
#*
#* Notes:
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#configuration parameters and default values
use File::Basename;
#configuration parameters and default values
$Verbose = 0;
$BinOutputFile  = 0;
$MinimalBinOutputFile = 0;
$QT_64Bit_OutputFile   = 0;
$QT_32Bit_OutputFile   = 0;
$QT_16Bit_OutputFile   = 0;
$FTKOutputFile  = 0;
$HexOutputFile  = 0;
$AscOutputFile  = 0;
$FlashStartAddr = 0xD0000000; # default value
$FlashEndAddr   = 0xD0080000; # default value
$FlashAbsolutStartAddr = 0xD0000000; # default value

$Usage =          "Usage: $0 <file_name.hx>[-bin][-QT][-o <file_name.hx>][-inc <Header_File>][-ftk][-hex][-asc][-S][-E][-v]\n";
$Usage = $Usage . " Generates specialy formatted file for Flash burning and/or QuickTurn loading \n";
$Usage = $Usage . " The files will be create in the same path and name of the input *.hx file, with the relavant suffix \n";
$Usage = $Usage . " Parameters:\n";
$Usage = $Usage . "  * file_name.hx ....  Input *.hx file (include *.hx)\n";
$Usage = $Usage . " Options:\n";
$Usage = $Usage . "  * -bin    ....  Output file is in binary format (Size of output file According to Memory size)\n";
$Usage = $Usage . "  * -M      ....  The Binary Output file size is According to Used memory only ! \n";
$Usage = $Usage . "  * -QT64   ....  Output file is in QT 64bit Big Endian init format\n";
$Usage = $Usage . "  * -QT32   ....  Output file is in QT 32bit Little Endian init format\n";
$Usage = $Usage . "  * -QT16   ....  Output file is in QT 16bit Little Endian init format\n";
$Usage = $Usage . "  * -o   <output_file> .. User can specify output file name and path\n";
$Usage = $Usage . "  * -inc <Header_File> .. Put the contents of the Header_File (if provided) at the beginning of output file.\n";
$Usage = $Usage . "  * -hex    ....  Output file is Intel hex  \n";
$Usage = $Usage . "  * -asc    ....  Output file is Flash ASCII\n";
$Usage = $Usage . "  * -S      ....  Set Flash start address (0x%08X default)\n";
$Usage = $Usage . "  * -E      ....  Set Flash end   address (0x%08X default)\n";
$Usage = $Usage . "  * -AS     ....  (Valid in -QT32)Set Absolute Flash start address (0x%08X default) (cases where it different from -S) \n\n";
$Usage = $Usage . "  * -v      ....  Do it verbosely (print some info messages)\n";


$Usage = sprintf $Usage, $FlashStartAddr, $FlashEndAddr, $FlashAbsolutStartAddr;
((scalar @ARGV) < 1) && die "$Usage";

# open input file.
$hx_file = shift (@ARGV);
($in_name, $in_path, $in_suf) = fileparse( $hx_file, '\.\w+');
open(HXFILE , "< $hx_file") || die "$0: Can't open '$hx_file'.\n";
print "\n\n--- Process hx file    [$in_name$in_suf]  ---";

#process parameters and options
$ParamNum = (scalar @ARGV);
while ( $ParamNum != 0 ) {
  $param2 = shift (@ARGV);
  if ( $param2 =~ /^-.*/ ) {
    if    ( $param2 =~ /^-S$/ )     { $FlashStartAddr = hex(shift (@ARGV)); }
    elsif ( $param2 =~ /^-AS$/ )    { $FlashAbsolutStartAddr = hex(shift (@ARGV)); }
    elsif ( $param2 =~ /^-E$/ )     { $FlashEndAddr = hex(shift (@ARGV)); }
    elsif ( $param2 =~ /^-QT64$/ )  { $QT_64Bit_OutputFile = 1; }
    elsif ( $param2 =~ /^-QT32$/ )  { $QT_32Bit_OutputFile = 1; }
    elsif ( $param2 =~ /^-QT16$/ )  { $QT_16Bit_OutputFile = 1; }
    elsif ( $param2 =~ /^-bin$/ )   { $BinOutputFile = 1; }
    elsif ( $param2 =~ /^-M$/ )     { $MinimalBinOutputFile = 1; }
    elsif ( $param2 =~ /^-hex$/ )   { $HexOutputFile = 1; }
    elsif ( $param2 =~ /^-asc$/ )   { $AscOutputFile = 1; }
    elsif ( $param2 =~ /^-inc$/ )   { $HeaderFile = shift (@ARGV); }
    elsif ( $param2 =~ /^-o$/ )     { $OutPutFileName = shift (@ARGV); }
    elsif ( $param2 =~ /^-v$/ )     { $Verbose = 1; }
        else {die "$0: '$param2' - unknown option\n";}
  }
  else { $out_file = $param2;}
  $ParamNum = scalar(@ARGV);
}


# --------------
# --------------
#

$DefaultOverlayed = "FF";

# calculating total memory size
$MemSize = $FlashEndAddr - $FlashStartAddr;

# resetting memory array with default value
for ( $i=0; $i<$MemSize; $i++ ) {
	$Memory[$i] = $DefaultOverlayed;
}
#$Overlayed


# Read the input file (format s3)
$line = <HXFILE>;
while ($line =~ /^S3([\d,\w]{2})([\d,\w]{8})/)
{
  $RelativePlaceInMem = hex($2) - $FlashStartAddr;

  if ( (hex($2)>=$FlashStartAddr) && (hex($2)<$FlashEndAddr) )
  {
    $Section = {};
    $Section->{addr} = hex($2);
    $Section->{size} = (hex($1) - 5);; #IN BYTES !!!
    $DataLength = $Section->{size}*2;
    $line =~ /^S3([\d,\w]{2})([\d,\w]{8})(\w{$DataLength})/;
    $Section->{data} = ($3);
	$SectionEnd = 0;

	for ( $i=0; $i < $Section->{size}; $i++ ) {
		$Position = $RelativePlaceInMem + $i;
		# checking if we already met this address (overlayed)
		if ( $Overlayed[$Position] == 1 ) {
			# address is overlayed, use default value instead
			$Memory[$Position] = $DefaultOverlayed;
		} #if
		else {
			# first time we met this address, put relevant data in memory
			$Memory[$Position] = substr($Section->{data}, 2*$i, 2);
			# set the overlayed bit for this address, indicating it was met
			$Overlayed[$Position] = 1;
		} #else
	}   #for i
  }
#if
  $line = <HXFILE>;
}
close HXFILE;

if ( $Verbose ) {print "\nFinish process *.hx file ";}

$Section = {};
$Section->{addr} = $FlashStartAddr;
$Section->{size} = $MemSize; #IN BYTES !!!
$Section->{data} = join '',@Memory;
push @SectionDB, $Section;

#
# --------------
# --------------



# If Output File format is binary
if ($BinOutputFile)
{
    # Open the relevant *bin outpufile.
    # check whether the user specify different output file name then default
    if ($OutPutFileName eq "") {
        $bin_out_file = "$in_path"."$in_name".".bin";
    }
    else {
        $bin_out_file = $OutPutFileName;
    }
    print "\n\n--- Creating bin file  [$bin_out_file]  ---";
    open(BINOUTFILE , "> $bin_out_file") || die "$0: Can't open '$bin_out_file'.\n";
    binmode BINOUTFILE;
    if ( $Verbose ) {print "\n* Create $bin_out_file ";}

    $EndOfLastSection = $FlashStartAddr;
    $OutputDBIsNotEmpty = 0;
    $FF_bin = pack "C" ,0xff ;

    for $el ( @SectionDB ) {
	  if ( $Verbose ) {printf "*** 0x%08X 0x%08X", $el->{addr}, $el->{size};}

        # Flag varify that the memory range holds at least one section
        $OutputDBIsNotEmpty = 1;

        # Fill the range between sections with zeros
        if ($el->{addr} > $EndOfLastSection){
		  my @FFBlock;
		  my $FFBlockBin;
		  my $FFBlockSize = ($el->{addr}-$EndOfLastSection);

		  if ( $Verbose ) {printf " (%08X %08X %08X) ", $el->{addr}, $EndOfLastSection, ($el->{addr}-$EndOfLastSection);}
            for ($i=0 ; $i < $FFBlockSize ; $i += 1 ){
			  push @FFBlock, 0xFF;
			}
		  $FFBlockBin = pack "C$FFBlockSize" ,@FFBlock ;
		  syswrite BINOUTFILE , $FFBlockBin, $FFBlockSize;

        }
        $DataLength = $el->{size} *2;
        $PackData = pack "H$DataLength" ,$el->{data} ;
        syswrite BINOUTFILE , $PackData,$DataLength;
        $EndOfLastSection = $el->{addr} + $el->{size};
	  if ( $Verbose ) {print " ***\n";}
    }
    # Pad the gap between the end of the Used memory and the end of the define memory ($FlashEndAddr)
    if (!$MinimalBinOutputFile) {
        if ($EndOfLastSection < $FlashEndAddr ){
		  my @FFBlock;
		  my $FFBlockBin;
		  $tete=($FlashEndAddr - $EndOfLastSection);
		  for ($i = 0 ; $i < $tete ; $i += 1 ){
			push @FFBlock, 0xFF;
		  }
		  $FFBlockBin = pack "C$tete" ,@FFBlock ;
		  syswrite BINOUTFILE , $FFBlockBin, $tete;


        }
    }
    if ( $Verbose ) {print "\r* $bin_out_file was create successfully";}
    close BINOUTFILE;
}

############################################
#   Produce a 64 bit *init File
############################################
if ($QT_64Bit_OutputFile)
{
    # If QT output file , the script creates  *_QT.hx and *_QT.bd file
    # Make a QT copy of bd and hx files
    $bd = "$in_path" . "$in_name" . ".bd";
    $QTbd = "$in_path" . "$in_name" . "_QT.bd";
    $QThx = "$in_path" . "$in_name" . "_QT.hx";

	# process hx file
    open(QTHXFILE , "> $QThx") || die "$0: Can't open '$QThx'.\n";
    open(HXFILE , "< $hx_file") || die "$0: Can't open '$hx_file'.\n";
    while ( $qtline = <HXFILE> ) {
        $qtline =~ /^\w{4}(\w{8}).*/;
  		if ( ! (( hex($1) >= $FlashStartAddr ) && ( hex($1) < $FlashEndAddr )) ) {
        print QTHXFILE $qtline;
  		}
	}
    close (QTHXFILE);
    close (HXFILE);

  if ($Verbose )  {print "\n- Copy $hx_file $QThx";}

    # perform the copy of the bd
    system("copy /Y $bd $QTbd > temp0123456789QTcopy.txt") == 0 or die; # the > operation is to suppress the copy output message
	  system("del /Q /F temp0123456789QTcopy.txt");

   if ($Verbose )  {print "\n- Copy $bd $QTbd\n";}

    # Open the relevant *init outpufile.
    # check whether the user specify different output file name then default
    if ($OutPutFileName eq ""){
        $QT_out_file = "$in_path"."$in_name".".init";
    }
    else {
        $QT_out_file = $OutPutFileName;
    }
    print "\n\n--- Creating 64 bit init file [$QT_out_file] ---";
    open(QTOUTFILE , "> $QT_out_file") || die "$0: Can't open '$QT_out_file'.\n";
    binmode QTOUTFILE;
    if ( $Verbose ) {print "\n- Create $QT_out_file ";}

    # Copy header file into output file.
	if ( $HeaderFile =~ /\w+/ ) {
        open(HFILE , "< $HeaderFile") || die "$0: Can't open '$HeaderFile'.\n";
        while ( $line = <HFILE> ) {
        print QTOUTFILE $line;
  	}
  	close HFILE;
    print QTOUTFILE "\n\n";
	}

  if ($Verbose )  {print "\n- Copy header to $QT_out_file";}
	$EmptyBytes = 0;
	$Offset = 0;
	$PrevOffset = 0xFFFFFFFF;
    for $el ( @SectionDB ) {

      if ($Verbose )  {
            printf "\n- Current sections Addr = %x   Size = %04.X byte", $el->{addr}, $el->{size};
        }
        @Data = split //m, $el->{data}; # split data into the array of chars

        # Calculate the initial offset and number of bytes to be printed in the previous line
  		eval{ $Offset = ( $el->{addr}  - $FlashStartAddr) >> 3 };

		#if current section starts at the same *init line the previos section was end
		if ($Offset == $PrevOffset) {
			if ($EmptyBytes != 0 ) {
                $SpaceBetweenSections =  $el->{addr} - ($FlashStartAddr + ($Offset<< 3) + (8- $EmptyBytes));

                # case the current section is shorter then the EmptyBytes of the current line
                if ($EmptyBytes > ($el->{size}+$SpaceBetweenSections)){
                    #case there is space between sections (in the same line of course)
                    while ( $SpaceBetweenSections ) {
                        printf QTOUTFILE "00" ;
                        $SpaceBetweenSections--;  $EmptyBytes--;
                    }
                    while ( $el->{size} ) {
                        printf QTOUTFILE "%01X%01X",hex(shift(@Data)),hex(shift(@Data));
                        $EmptyBytes--; $el->{size}--;
                    }
                    # Case the original $EmptyBytes = $SpaceBetweenSections + $el->{size}
                    # in this case we have to pass to the next line (This case is not supported in the next IF's )
                    if ( $EmptyBytes == 0 ) {
                        print QTOUTFILE "\n";
                    }
                }
                # case the current section is bigger than the EmptyBytes of the current line
                else{
                    #case there is space between sections (in the same line of course)
                    while ( $SpaceBetweenSections ) {
                        printf QTOUTFILE "00" ;
                        $SpaceBetweenSections--;  $EmptyBytes--;
                    }
                    eval{ $el->{size} = $el->{size} - ($EmptyBytes);};
                    while ( $EmptyBytes ) {
                        printf QTOUTFILE "%01X%01X",hex(shift(@Data)),hex(shift(@Data));
                        $EmptyBytes--;
                    }
                    $Offset++;
                    print QTOUTFILE "\n";
                }
			}
  		}
  		else{
			#ends the previos section line with 00's
			if ($EmptyBytes != 0 ) { #{ print OUTFILE "\n"; }
                while ( $EmptyBytes ) {
                    printf QTOUTFILE "00" ;
					$EmptyBytes--;
				}
                print QTOUTFILE "\n";
			}
			#align current section from its begining
			$AlingSection = ($el->{addr} - ( ($Offset<< 3) + $FlashStartAddr) );
			if ( $AlingSection !=  0 ) {
				$el->{addr} =  $el->{addr} -  $AlingSection;
				$el->{size} =  $el->{size} +  $AlingSection;
                while ($AlingSection)   {unshift  @Data, "a";unshift  @Data, "a";$AlingSection --;}
			}
  		}


  		# data ( full lines)
  		eval{ $FullLines = $el->{size} >> 3; $Rem = $el->{size} - ($FullLines << 3); };
        while ( $FullLines ) {
			$i = 8;
            printf QTOUTFILE "%X  ", $Offset;
            while ( $i ) {printf QTOUTFILE "%01X%01X", hex(shift(@Data)),hex(shift(@Data)); $i--;}
            print QTOUTFILE "\n";
			$FullLines--;
			$Offset++;
  		}

  		# print the rest of the data if needed
  		if ( $Rem != 0 ) {
			eval{ $EmptyBytes = 8 - $Rem;};
            printf QTOUTFILE "%X  ", $Offset;
            while ( $Rem ) { printf QTOUTFILE "%01X%01X", hex(shift(@Data)), hex(shift(@Data)); $Rem--; }
  		}
        elsif ($PrevOffset != $Offset) {
			$EmptyBytes = 0;
        }
        $PrevOffset = $Offset;
	}
	# if last section ends with EmptyBytes (meaning the last 64 bit *.init line was not full)
	if ($EmptyBytes != 0 ) {
  		while ( $EmptyBytes ) {
            printf QTOUTFILE "00" ;
			$EmptyBytes--;
		}
        print QTOUTFILE "\n";
	}
    close QTOUTFILE;
} # end of QT 64 bit


############################################
#   Produce a 32 bit *init File
############################################
if ($QT_32Bit_OutputFile)
{
    # If QT output file , the script creates  *_QT.hx and *_QT.bd file
    # Make a QT copy of bd and hx files
    $bd = "$in_path" . "$in_name" . ".bd";
    $QTbd = "$in_path" . "$in_name" . "_QT.bd";
    $QThx = "$in_path" . "$in_name" . "_QT.hx";

	# process hx file
    open(QTHXFILE , "> $QThx") || die "$0: Can't open '$QThx'.\n";
    open(HXFILE , "< $hx_file") || die "$0: Can't open '$hx_file'.\n";
    while ( $qtline = <HXFILE> ) {
        $qtline =~ /^\w{4}(\w{8}).*/;
  		if ( ! (( hex($1) >= $FlashStartAddr ) && ( hex($1) < $FlashEndAddr )) ) {
        print QTHXFILE $qtline;
  		}
	}
    close (QTHXFILE);
    close (HXFILE);

    if ($Verbose )  {print "\n- Copy $hx_file $QThx";}

    # perform the copy of the bd
    system("copy /Y $bd $QTbd > temp0123456789QTcopy.txt") == 0 or die; # the > operation is to suppress the copy output message
	system("del /Q /F temp0123456789QTcopy.txt");

    if ($Verbose )  {print "\n- Copy $bd $QTbd\n";}

    # Open the relevant *init outpufile.
    # check whether the user specify different output file name then default
    if ($OutPutFileName eq ""){
        $QT_out_file = "$in_path"."$in_name".".init";
    }
    else {
        $QT_out_file = $OutPutFileName;
    }
    print "\n\n--- Creating 32 bit init file [$QT_out_file] ---";
    open(QTOUTFILE , "> $QT_out_file") || die "$0: Can't open '$QT_out_file'.\n";
    binmode QTOUTFILE;
    if ( $Verbose ) {print "\n- Create $QT_out_file ";}

    # Copy header file into output file.
	if ( $HeaderFile =~ /\w+/ ) {
        open(HFILE , "< $HeaderFile") || die "$0: Can't open '$HeaderFile'.\n";
        while ( $line = <HFILE> ) {
        print QTOUTFILE $line;
  	}
  	close HFILE;
    print QTOUTFILE "\n\n";
	}

    # if the memory location whee the init is heading for does not start
    # at the same address as -S ( FlashStartAddr )
    $AbsoluteOffset = ($FlashStartAddr - $FlashAbsolutStartAddr)/4;

    if ($Verbose )  {print "\n- Copy header to $QT_out_file";}
	$EmptyBytes = 0;
	$Offset = 0;
	$PrevOffset = 0xFFFFFFFF;
    $ZeroByte = 0x0;
    for $el ( @SectionDB ) {

      if ($Verbose )  {printf "\n- Current sections Addr = %x   Size = %04.X byte", $el->{addr}, $el->{size};}

        @Data = split //m, $el->{data}; # split data into the array of chars

        # Calculate the initial offset (in 32 bit address)
        eval{ $Offset = ( $el->{addr}  - $FlashStartAddr) >> 2 ;};

        #if current section starts at the same *init line the previos section was end
		if ($Offset == $PrevOffset) {
            # case the current section is shorter then the EmptyBytes of the current line
            if ($EmptyBytes > $el->{size}){
                print "\n Known Bug - current section is shorter then the EmptyBytes. Call Ohad (7535)";
            } 
            # case the current section is bigger then the EmptyBytes of the current line
            else{
                #case there is space between sections (in the same line of course)
                $SpaceBetweenSections =  $el->{addr} - ($FlashStartAddr + ($Offset<< 2) + (8- $EmptyBytes));
                if ($EmptyBytes == 6 ){
                    if ( $SpaceBetweenSections == 0) {
                        $thirdByte   =   hex(shift(@Data));
                        $fourthByte  =   hex(shift(@Data));
                        $fifthByte   =   hex(shift(@Data));
                        $sixthByte   =   hex(shift(@Data));
                        $SeventhByte =   hex(shift(@Data));
                        $EighthByte  =   hex(shift(@Data));
                    }

                    if ( $SpaceBetweenSections == 2) {
                        $thirdByte   =   $ZeroByte;
                        $fourthByte  =   $ZeroByte;
                        $fifthByte   =   hex(shift(@Data));
                        $sixthByte   =   hex(shift(@Data));
                        $SeventhByte =   hex(shift(@Data));
                        $EighthByte  =   hex(shift(@Data));
                    }

                    if ( $SpaceBetweenSections == 4) {
                        $thirdByte   =   $ZeroByte;
                        $fourthByte  =   $ZeroByte;
                        $fifthByte   =   $ZeroByte;
                        $sixthByte   =   $ZeroByte;
                        $SeventhByte =   hex(shift(@Data));
                        $EighthByte  =   hex(shift(@Data));

                    }
                }
                if ($EmptyBytes == 4 ){
                    if ( $SpaceBetweenSections == 0) {
                        $fifthByte   =   hex(shift(@Data));
                        $sixthByte   =   hex(shift(@Data));
                        $SeventhByte =   hex(shift(@Data));
                        $EighthByte  =   hex(shift(@Data));
                    }

                    if ( $SpaceBetweenSections == 2) {
                        $fifthByte   =   $ZeroByte;
                        $sixthByte   =   $ZeroByte;
                        $SeventhByte =   hex(shift(@Data));
                        $EighthByte  =   hex(shift(@Data));
                    }
                }

                printf QTOUTFILE "%01X%01X%01X%01X%01X%01X%01X%01X",$SeventhByte,$EighthByte,$fifthByte,$sixthByte,$thirdByte,$fourthByte,$firstByte,$secondByte;
                eval{ $el->{size} = $el->{size} - ($EmptyBytes);};
                $Offset++;
                print QTOUTFILE "\n";
            }
        }
  		else{
            # Ends the previos section line with 00's
            if ($EmptyBytes != 0 ) {
                if ($EmptyBytes == 6 ) {printf QTOUTFILE "%01X%01X%01X%01X%01X%01X%01X%01X",$ZeroByte,$ZeroByte,$ZeroByte,$ZeroByte,$ZeroByte,$ZeroByte,$firstByte,$secondByte;}
                if ($EmptyBytes == 4 ) {printf QTOUTFILE "%01X%01X%01X%01X%01X%01X%01X%01X",$ZeroByte,$ZeroByte,$ZeroByte,$ZeroByte,$thirdByte,$fourthByte,$firstByte,$secondByte;}
                if ($EmptyBytes == 2 ) {printf QTOUTFILE "%01X%01X%01X%01X%01X%01X%01X%01X",$ZeroByte,$ZeroByte,$fifthByte,$sixthByte,$thirdByte,$fourthByte,$firstByte,$secondByte;}
                print QTOUTFILE "\n";
            }
            # Is the current section starts 32 bit align ???  ($Offset != $PrevOffset)
            eval{ $Section32BitNOTAlign = ( $el->{addr}  - $FlashStartAddr) - ($Offset << 2);};
            while ($Section16BitNOTAlign) {
                # align the section start. Each loop add byte.
                $el->{addr} =  $el->{addr} -  1;
                $el->{size} =  $el->{size} +  1;
                unshift  @Data, "0"; 
                unshift  @Data, "0";
            }
        }

        # 32 bit full lines
        eval{ $CurentSize = $el->{size} >> 2};  # 32bit full lines
        eval{ $alignCurrentSize = $el->{size} - ($CurentSize << 2) }; # sparebytes in the last *init line
        while ( $CurentSize ) {
            printf QTOUTFILE "%08X ", ($Offset+$AbsoluteOffset);
            $firstByte   =   hex(shift(@Data));
            $secondByte  =   hex(shift(@Data));
            $thirdByte   =   hex(shift(@Data));
            $fourthByte  =   hex(shift(@Data));
            $fifthByte   =   hex(shift(@Data));
            $sixthByte   =   hex(shift(@Data));
            $SeventhByte =   hex(shift(@Data));
            $EighthByte  =   hex(shift(@Data));
            printf QTOUTFILE "%01X%01X%01X%01X%01X%01X%01X%01X",$SeventhByte,$EighthByte,$fifthByte,$sixthByte,$thirdByte,$fourthByte,$firstByte,$secondByte;
            print QTOUTFILE "\n";
            $Offset++; $CurentSize--;
        }
        $Offset--;

        $EmptyBytes = 0;
        # Open new line if the section size was not "align" 32 bit
        if ( $alignCurrentSize ) {
            $EmptyBytes = 8 - $alignCurrentSize;
            $Offset++;
            printf QTOUTFILE "%08X ", ($Offset+$AbsoluteOffset);
            # save the current data and will use after reding the next section and see if we will add 00 or the first data of the next section
            $firstByte = hex(shift(@Data));
            $secondByte = hex(shift(@Data));
            if ($alignCurrentSize > 2 ) {
                $thirdByte   =   hex(shift(@Data));
                $fourthByte  =   hex(shift(@Data));
            }
            if ($alignCurrentSize > 4 ) {
                $fifthByte   =   hex(shift(@Data));
                $sixthByte   =   hex(shift(@Data));
            }
        }
        $PrevOffset = $Offset;
    }

    # if last section ends with EmptyBytes (meaning the last 64 bit *.init line was not full)
    if ($EmptyBytes != 0 ) {
        if ($EmptyBytes == 6 ) {printf QTOUTFILE "%01X%01X%01X%01X%01X%01X%01X%01X",$ZeroByte,$ZeroByte,$ZeroByte,$ZeroByte,$ZeroByte,$ZeroByte,$firstByte,$secondByte;}
        if ($EmptyBytes == 4 ) {printf QTOUTFILE "%01X%01X%01X%01X%01X%01X%01X%01X",$ZeroByte,$ZeroByte,$ZeroByte,$ZeroByte,$thirdByte,$fourthByte,$firstByte,$secondByte;}
        if ($EmptyBytes == 2 ) {printf QTOUTFILE "%01X%01X%01X%01X%01X%01X%01X%01X",$ZeroByte,$ZeroByte,$fifthByte,$sixthByte,$thirdByte,$fourthByte,$firstByte,$secondByte;}
    }
    print QTOUTFILE "\n";
    close QTOUTFILE;
} # end of QT


############################################
#   Produce a 16 bit *init File
############################################
if ($QT_16Bit_OutputFile)
{
    # If QT output file , the script creates  *_QT.hx and *_QT.bd file
    # Make a QT copy of bd and hx files
    $bd = "$in_path" . "$in_name" . ".bd";
    $QTbd = "$in_path" . "$in_name" . "_QT.bd";
    $QThx = "$in_path" . "$in_name" . "_QT.hx";

	# process hx file
    open(QTHXFILE , "> $QThx") || die "$0: Can't open '$QThx'.\n";
    open(HXFILE , "< $hx_file") || die "$0: Can't open '$hx_file'.\n";
    while ( $qtline = <HXFILE> ) {
        $qtline =~ /^\w{4}(\w{8}).*/;
  		if ( ! (( hex($1) >= $FlashStartAddr ) && ( hex($1) < $FlashEndAddr )) ) {
        print QTHXFILE $qtline;
  		}
	}
    close (QTHXFILE);
    close (HXFILE);

    if ($Verbose )  {print "\n- Copy $hx_file $QThx";}

    # perform the copy of the bd
    system("copy /Y $bd $QTbd > temp0123456789QTcopy.txt") == 0 or die; # the > operation is to suppress the copy output message
	system("del /Q /F temp0123456789QTcopy.txt");

    if ($Verbose )  {print "\n- Copy $bd $QTbd\n";}

    # Open the relevant *init outpufile.
    # check whether the user specify different output file name then default
    if ($OutPutFileName eq ""){
        $QT_out_file = "$in_path"."$in_name".".init";
    }
    else {
        $QT_out_file = $OutPutFileName;
    }
    print "\n\n--- Creating 16bit  init file [$QT_out_file] ---";
    open(QTOUTFILE , "> $QT_out_file") || die "$0: Can't open '$QT_out_file'.\n";
    binmode QTOUTFILE;
    if ( $Verbose ) {print "\n- Create $QT_out_file ";}

    # Copy header file into output file.
	if ( $HeaderFile =~ /\w+/ ) {
        open(HFILE , "< $HeaderFile") || die "$0: Can't open '$HeaderFile'.\n";
        while ( $line = <HFILE> ) {
        print QTOUTFILE $line;
  	}
  	close HFILE;
    print QTOUTFILE "\n\n";
	}

    if ($Verbose )  {print "\n- Copy header to $QT_out_file";}
	$EmptyBytes = 0;
	$Offset = 0;
	$PrevOffset = 0xFFFFFFFF;
    for $el ( @SectionDB ) {

      if ($Verbose )  {printf "\n- Current sections Addr = %x   Size = %04.X byte", $el->{addr}, $el->{size};}

        @Data = split //m, $el->{data}; # split data into the array of chars

        # Calculate the initial offset (in 16 bit address)
        eval{ $Offset = ( $el->{addr}  - $FlashStartAddr) >> 1 ;};

        #if current section starts at the same *init line the previos section was end
		if ($Offset == $PrevOffset) {
            # using the data from the last section ..... ( $firstByte,$secondByte )
            $thirdByte = hex(shift(@Data));
            printf QTOUTFILE "%01X%01X%01X%01X",$thirdByte,hex(shift(@Data)),$firstByte,$secondByte;
            print QTOUTFILE "\n";
            $el->{size} =  $el->{size} -1;
            $Offset++;
        }
  		else{
            #Ends the previos section line with 00's
            if ($EmptyBytes != 0 ) {
                $thirdByte = 0;
                printf QTOUTFILE "%01X%01X%01X%01X",$thirdByte,$thirdByte,$firstByte,$secondByte;
                print QTOUTFILE "\n";
            }
            #Is the current section starts 16 bit align ???  ($Offset != $PrevOffset)
            eval{ $Section16BitNOTAlign = ( $el->{addr}  - $FlashStartAddr) - ($Offset << 1);};
            if ( $Section16BitNOTAlign == 1 ) {
                $el->{addr} =  $el->{addr} -  1;
                $el->{size} =  $el->{size} +  1;
                unshift  @Data, "0";
                unshift  @Data, "0";
            }
        }


        # data ( full lines) Print current section "full lines"
        eval{ $CurentSize = $el->{size} >> 1};
        eval{ $alignCurrentSize = $el->{size} - ($CurentSize << 1) };
        while ( $CurentSize ) {
            printf QTOUTFILE "%05X    ", $Offset;
            $firstByte = hex(shift(@Data));
            $secondByte = hex(shift(@Data));
            $thirdByte = hex(shift(@Data));
            printf QTOUTFILE "%01X%01X%01X%01X",$thirdByte,hex(shift(@Data)),$firstByte,$secondByte;
            print QTOUTFILE "\n";
            $Offset++; $CurentSize--;
        }

        $Offset--;

        $EmptyBytes = 0;
        # Open new line if the section size was not "align" 16 bit
        if ( $alignCurrentSize ) {
            $Offset++;
            printf QTOUTFILE "%05X    ", $Offset;
            # save the current data and will use after reding the next section and see if we will add 00 or the first data of the next section
            $firstByte = hex(shift(@Data));
            $secondByte = hex(shift(@Data));
            #printf QTOUTFILE "%01X%01X", hex(shift(@Data)),hex(shift(@Data));
            $EmptyBytes = 1;
        }
        $PrevOffset = $Offset;
    }

    # if last section ends with EmptyBytes (meaning the last 64 bit *.init line was not full)
	if ($EmptyBytes != 0 ) {
        $thirdByte = 0;
        printf QTOUTFILE "%01X%01X%01X%01X",$thirdByte,$thirdByte,$firstByte,$secondByte;
        print QTOUTFILE "\n";
       $EmptyBytes--;
    }
    print QTOUTFILE "\n";
    close QTOUTFILE;
} # end of QT

############################################
#   Produce a ASCII  File
############################################
if ($AscOutputFile)
{
    # Open the relevant *asc outpufile.
    # check whether the user specify different output file name then default
    if ($OutPutFileName eq ""){
        $asc_out_file = "$in_path"."$in_name".".asc";
    }
    else {
        $asc_out_file = $OutPutFileName;
    }

    print "\n\n--- Creating ASCII file [$asc_out_file] ---";
    open(ASCOUTFILE , "> $asc_out_file") || die "$0: Can't open '$asc_out_file'.\n";
    binmode ASCOUTFILE;

    $EmptyBytes = 0;
    $Offset = 0;
    $PrevOffset = 0xFFFFFFFF;
    for $el ( @SectionDB ) {

      if ($Verbose )  {printf "\n- Current sections Addr = %x   Size = %04.X byte", $el->{addr}, $el->{size};}

        @Data = split //m, $el->{data}; # split data into the array of chars

        # Calculate the initial offset (in 16 bit address)
        eval{ $Offset = ( $el->{addr}  - $FlashStartAddr) >> 1 ;};

        #if current section starts at the same *init line the previos section was end
        if ($Offset == $PrevOffset) {
            # using the data from the last section ..... ( $firstByte,$secondByte )
            $thirdByte = hex(shift(@Data));
            printf ASCOUTFILE "%01X%01X%01X%01X",$thirdByte,hex(shift(@Data)),$firstByte,$secondByte;
            print ASCOUTFILE "\r";
            $el->{size} =  $el->{size} -1;
            $Offset++;
        }
        else{
            #Ends the previos section line with 00's
            if ($EmptyBytes != 0 ) {
                $thirdByte = 0;
                printf ASCOUTFILE "%01X%01X%01X%01X",$thirdByte,$thirdByte,$firstByte,$secondByte;
                print ASCOUTFILE "\r";
            }
            #Is the current section starts 16 bit align ???  ($Offset != $PrevOffset)
            eval{ $Section16BitNOTAlign = ( $el->{addr}  - $FlashStartAddr) - ($Offset << 1);};
            if ( $Section16BitNOTAlign == 1 ) {
                $el->{addr} =  $el->{addr} -  1;
                $el->{size} =  $el->{size} +  1;
                unshift  @Data, "0";
                unshift  @Data, "0";
            }
        }


        # data ( full lines) Print current section "full lines"
        eval{ $CurentSize = $el->{size} >> 1};
        eval{ $alignCurrentSize = $el->{size} - ($CurentSize << 1) };
        while ( $CurentSize ) {
            printf ASCOUTFILE "%05X ", $Offset;
            $firstByte = hex(shift(@Data));
            $secondByte = hex(shift(@Data));
            $thirdByte = hex(shift(@Data));
            printf ASCOUTFILE "%01X%01X%01X%01X",$thirdByte,hex(shift(@Data)),$firstByte,$secondByte;
            print ASCOUTFILE "\r";
            $Offset++; $CurentSize--;
        }

        $Offset--;

        $EmptyBytes = 0;
        # Open new line if the section size was not "align" 16 bit
        if ( $alignCurrentSize ) {
            $Offset++;
            printf ASCOUTFILE "%05X ", $Offset;
            # save the current data and will use after reding the next section and see if we will add 00 or the first data of the next section
            $firstByte = hex(shift(@Data));
            $secondByte = hex(shift(@Data));
            #printf ASCOUTFILE "%01X%01X", hex(shift(@Data)),hex(shift(@Data));
            $EmptyBytes = 1;
        }
        $PrevOffset = $Offset;
    }

    # if last section ends with EmptyBytes (meaning the last 64 bit *.init line was not full)
    if ($EmptyBytes != 0 ) {
        $thirdByte = 0;
        printf ASCOUTFILE "%01X%01X%01X%01X",$thirdByte,$thirdByte,$firstByte,$secondByte;
        print ASCOUTFILE "\r";
       $EmptyBytes--;
    }
    print ASCOUTFILE "\r";
    close ASCOUTFILE;
} # end of ascii



if ($FTKOutputFile) {print "\n* Sorry - Do not support FTK output yet "};
if ($HexOutputFile) {print "\n* Sorry - Do not support HEX output yet "};


if ($Verbose) {print "\nend process  \n";}
print "\n\n";
exit 0;






















