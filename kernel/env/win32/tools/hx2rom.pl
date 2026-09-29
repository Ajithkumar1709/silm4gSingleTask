#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#* DSPC Proprietary Information, (C) COPYRIGHT 2000 DSPC, an Intel Company
#* File name:    hx2rom.pl
#* Programmer:   Ohad S.
#* Create Date:  April 2004
#* Description:
#*  This program Converts hx format to ROM format.
#*
#* note: The script is a version of hx2flash.pl
#*       The part of processing the *.hx file and creating the temp *.bin file
#*        is fully based on the original hx2flash running with -bin flag
#*       The last section (create the ROM format file) is uniqu to the script.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
$version = "Version: 1.0, CBA00.01.29   Date: April 08, 2004";
#configuration parameters and default values
use File::Basename;
#configuration parameters and default values
$FlashStartAddr = 0xffffffff; 
$FlashEndAddr   = 0x0; 
$OutPutFileName = "";
$SaveTemps = 0; 
$Verbose = 0;
$GrayBackAddrFormat = 0;
$HeaderNumber = 0;
$QuickTurn = 0;
$MinimalBinOutputFile = 0;

$Usage =          "- Usage: $0 <file_name.in> <file_name.out> <-S 0xStartAddress> <-E 0xEndAddress> [-GB <HeaderNumber>] [-M] [-v] [-s]\n";
$Usage = $Usage . "- Purpose: Convert an Motorola(S3) format file into ROM syntax file\n";
$Usage = $Usage . "- Parameters:\n";
$Usage = $Usage . "     * file_name.in  .. Specifies the input file.\n";
$Usage = $Usage . "     * file_name.out .. Specifies the output file.\n";
$Usage = $Usage . "- Options:\n";
$Usage = $Usage . "     * -S   ....  Set ROM start address (0x%08X default)\n";
$Usage = $Usage . "     * -E   ....  Set ROM end address (0x%08X default)\n";
$Usage = $Usage . "     * -GB  ....  Address format for GrayBack ROM (HeaderNumber = Header serial Number. 0 means no header\n";
$Usage = $Usage . "  	* -M   ....  The Binary Output file size is According to Used memory only (supported only with GrayBack address format\n";
$Usage = $Usage . "     * -QT  ....  Generate output file in QT format (when not used - output format is in Silicon format).\n";
$Usage = $Usage . "     * -s   ....  Save temp files.\n";
$Usage = $Usage . "     * -v   ....  Do it verbosely (print some info messages).\n";
$Usage = $Usage . "     * -V   ....  Get script version.\n";


$Usage = sprintf $Usage, $FlashStartAddr, $FlashEndAddr;
((scalar @ARGV) < 1) && die "\n$Usage\n";

####################################################
# Read input parameters and set the relevant vars
####################################################

# open input file.
$hx_file = shift (@ARGV);
if ( $hx_file eq "-V")
{ {die "\n--- hx2rom.pl version : $version \n";}}

$OutPutFileName = shift (@ARGV);

($in_name, $in_path, $in_suf) = fileparse( $hx_file, '\.\w+');
open(HXFILE , "< $hx_file") || die "\n$0 Error: Can't open input file '$hx_file'.\n";
print "\n\n--- Input file  [$in_name$in_suf] ---";

open(ROMOUTFILE , "> $OutPutFileName") || die "\n$0 Error: Can't open output file '$OutPutFileName'.\n";
print "\n--- Output file [$OutPutFileName] ---";



#process parameters and options
$ParamNum = (scalar @ARGV);
while ( $ParamNum != 0 ) {
  $param2 = shift (@ARGV);
  if ( $param2 =~ /^-.*/ ) {
    if    ( $param2 =~ /^-S$/ )     { $FlashStartAddr = hex(shift (@ARGV)); }
    elsif ( $param2 =~ /^-E$/ )     { $FlashEndAddr = hex(shift (@ARGV)); }
	elsif ( $param2 =~ /^-GB$/ )     { $GrayBackAddrFormat = 1; $HeaderNumber = hex(shift (@ARGV));}
	elsif ( $param2 =~ /^-QT$/ )     { $QuickTurn = 1; }
	elsif ( $param2 =~ /^-M$/ )     { $MinimalBinOutputFile = 1; }
    elsif ( $param2 =~ /^-s$/ )     { $SaveTemps = 1; }
    elsif ( $param2 =~ /^-v$/ )     { $Verbose = 1; }
        else {die "\n$0 Error: '$param2' - unknown option\n";}
  }
  $ParamNum = scalar(@ARGV);
}

if ($FlashStartAddr == 0xFFFFFFFF){die "\n$0 Error: Please add -S option \n";}
elsif (($FlashStartAddr % 8)){die "\n$0 Error: ROM start address must be 8-byte aligned\n";}

if ($FlashEndAddr == 0x0){die "\n$0: Please add -E option \n";}
elsif (($FlashEndAddr % 8)){die "\n$0: ROM end address must be 8-byte aligned\n";}

############################################################
# Read the input hx file (format Motorola s3)
############################################################
print "\n--- Process input file     [$in_name$in_suf]  ---";
$line = <HXFILE>;
while ($line =~ /^S3([\d,\w]{2})([\d,\w]{8})/)
{
  if ( ( (hex($2) + hex($1) - 5) >= $FlashStartAddr) && (hex($2)<$FlashEndAddr) )
  {
    $Section = {};
	#Three relevant cases:
	# First: the current hx line (hex($2)) starts before $FlashStartAddr
	# Second: the current hx line ends (hex($2) + hex($1)-5) after $FlashEndAddr
	# Third (normal): all current hx line is within the flash range
	if($FlashStartAddr > hex($2))
	{
		#First case: the current hx line (hex($2)) starts before $FlashStartAddr
	   	$Section->{addr} = $FlashStartAddr;
        $Section->{size} = hex($2) + (hex($1) - 5) - $FlashStartAddr; #IN BYTES !!!
#size = current hx start address plus current hx size minus flash start adress
        $DataLength = $Section->{size}*2;
		$PreData = ((hex($1)-5)*2) - $DataLength;    #The data before the flash start address = hx line size minus actual (valid) data length
        $line =~ /^S3([\d,\w]{2})([\d,\w]{8})(\w{$PreData})(\w{$DataLength})/;
		$Section->{data} = ($4);
	    $SectionEnd = 0;
	    push @SectionDB, $Section;
	}
	elsif ((hex($2) + hex($1)-5) > $FlashEndAddr)
	{
		#Second case: the current hx line ends (hex($2) + hex($1)-5) after $FlashEndAddr
	   	$Section->{addr} = hex($2);
        $Section->{size} = $FlashEndAddr - hex($2); #IN BYTES !!!  Flash End address minus current hx start line address
        $DataLength = $Section->{size}*2;
        $line =~ /^S3([\d,\w]{2})([\d,\w]{8})(\w{$DataLength})/;
		$Section->{data} = ($3);
	    $SectionEnd = 0;
	    push @SectionDB, $Section;
	}
	else
	{
		# Third (normal) case: all current hx line is within the flash range
	   	$Section->{addr} = hex($2);
        $Section->{size} = (hex($1) - 5);; #IN BYTES !!!
        $DataLength = $Section->{size}*2;
        $line =~ /^S3([\d,\w]{2})([\d,\w]{8})(\w{$DataLength})/;
        $Section->{data} = ($3);
	    $SectionEnd = 0;
	    push @SectionDB, $Section;
	}
	
  }
  $line = <HXFILE>;
}
close HXFILE;
@SectionDB = sort {$a->{addr} <=> $b->{addr};} @SectionDB;
if ( $Verbose ) {print "\nFinish process *.hx file ";}


###################################################
# Create a temp bin file                          #
###################################################
# Open the relevant *bin outpufile.
$bin_out_file = "$in_path"."HX2ROM_BIN_TEMP_FILE".".bin";
if ( $Verbose ) {print "\nCreating temp bin file  [$bin_out_file]  ---";}
if ( $SaveTemps ) {print "\nTemp bin file will no be deleted ! ---";}
open(BINOUTFILE , "> $bin_out_file") || die "\n$0 Error: Can't open script temp file for writing '$bin_out_file'.\n";
binmode BINOUTFILE;

if ( $Verbose ) {print "\n";}
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
if ($MinimalBinOutputFile && $GrayBackAddrFormat)
{
	if ($EndOfLastSection < $FlashEndAddr ){
	  my @FFBlock;
	  my $FFBlockBin;
	  $tete=((8-$EndOfLastSection%8)%8);
	  for ($i = 0 ; $i < $tete ; $i += 1 ){
	    push @FFBlock, 0xFF;
	  }
	  $FFBlockBin = pack "C$tete" ,@FFBlock ;
	  syswrite BINOUTFILE , $FFBlockBin, $tete;
	}
}
else{
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


if ( $Verbose ) {print "\n$bin_out_file was create successfully";}
#close BINOUTFILE;

###################################################
# Create output file from bin file                #
###################################################
open(BINTEMPFILE , "< $bin_out_file") || die "\n$0 Error: Can't open script temp file for reading '$bin_out_file'.\n";
if ( $Verbose ) {print "\nTemp bin file was open for reading ---";}

print "\n--- Creating ROM init file [$OutPutFileName] ---";
binmode ROMOUTFILE;

if ( $GrayBackAddrFormat && $QuickTurn) {
 	if ( $HeaderNumber > 0 ) {
		printf ROMOUTFILE "\$INSTANCE u_tavor_top__u_comm_top__u_gsram__u_crom128kr_c%d__u_crom128kr_c1_mem\n", $HeaderNumber;

		printf ROMOUTFILE "\$RADIX   HEX\n";
		printf ROMOUTFILE "\$ADDRESS   0    3fff\n";
	}
}

 
$teta = 8;
$DataReadFromBinFile;
$RomAddressIndex = 0;
while ((sysread BINTEMPFILE , $DataReadFromBinFile, $teta))
{
    # Unpack the binary word. For Big indian use "h16"
    $TempHexWord  =  unpack "H16" , $DataReadFromBinFile;
    # The order of the byte in the output file can be reverse by relacing $byte1 with $byte8 etc ...
    $byte1 = substr ($TempHexWord,14,2);
    $byte2 = substr ($TempHexWord,12,2);
    $byte3 = substr ($TempHexWord,10,2);
    $byte4 = substr ($TempHexWord, 8,2);
    $byte5 = substr ($TempHexWord, 6,2);
    $byte6 = substr ($TempHexWord, 4,2);
    $byte7 = substr ($TempHexWord, 2,2);
    $byte8 = substr ($TempHexWord, 0,2);
	if ( $QuickTurn) {
		printf ROMOUTFILE "%08X    ", $RomAddressIndex++;
	}
	else {
	   printf ROMOUTFILE "\@%X\n", $RomAddressIndex++;
	}
    printf ROMOUTFILE "$byte1$byte2$byte3$byte4$byte5$byte6$byte7$byte8\n";
}

# close all file heandlers
close HXFILE;
close ROMOUTFILE;
close BINOUTFILE;
close BINTEMPFILE;

# delete temp files
if ( $SaveTemps == 0 ) {
    system("del /Q /F $bin_out_file");
    if ( $Verbose ) {print "\nTemp bin file was deleted ---";}
}

print "\nend of process  \n";
print "\n";
exit 0;
# End of script
