#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#* DSPC Proprietary Information, (C) COPYRIGHT 2000 DSPC, an Intel Company
#* File name:    HSL2dat.pl
#* Programmer:   Evgeny M.
#* Create Date:  September, 2002
#* Description:
#*  This program search for certain HSL massage and log it to a log file .
#*      The data that is logged in the data inseind the {}
#*      The user can set offset inside the {} and to set how many param to log from the {}
#*      If non of the above is set the program log all the params in the {}
#*
#*      The output file formats are :
#*      	# ASCII with adding 0X before the data (can be change or add options if needed)
#*          # binary file
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

$OutputFileFormat = "ASCII";

$Usage =          "Usage: $0 <InputHSLFile> <OutputDatFile> <HSL_Message> [-o <Offset>]   \n";
$Usage = $Usage . " Tracing specific HSL Message and log its data to an output ASCII file \n";
$Usage = $Usage . " The data in inside the {}.\n";
$Usage = $Usage . " Parameters:\n";
$Usage = $Usage . "  InputHSLFile        The name of the input LOF file (with .lof).\n";
$Usage = $Usage . "  OutputDatFile       The name of the output file.\n";
$Usage = $Usage . "  HSL_Message         The message to trace.\n";
$Usage = $Usage . "  Options:\n";
$Usage = $Usage . "  -o                  Set the offset inside the {} to start log from (in WORDS)\n";
$Usage = $Usage . "  -bin                Set the output file format to binary\n";


((scalar @ARGV) < 3) && die "$Usage";

# Get program inputs and flags
$hsl_file 	 = shift (@ARGV);  # Input file
$out_file 	 = shift (@ARGV);
$HSL_Message = shift (@ARGV);  # Message to trace

$ParamNum = (scalar @ARGV);

while ( $ParamNum != 0 ) {
    $param2 = shift (@ARGV);
    if ( $param2 =~ /^-.*/ ) {
	     if    ( $param2 =~ /^-o$/   )    { $DataOffset = hex(shift (@ARGV)); }
  	     elsif ( $param2 =~ /^-bin$/ )    { $OutputFileFormat = "binary"; }
	     else {die "$0: '$param2' - unknown option\n";}
    }
    $ParamNum = scalar(@ARGV);
}

# Open input and output files
open(HSLFILE , "< $hsl_file") || die "$0: Can't open '$hsl_file'.\n";
open(INPFILE , "> $out_file") || die "$0: Can't open '$inp_file'.\n";

# If output file is a binary file it should be set as binary.
if   ( $OutputFileFormat eq "binary"  ) {binmode INPFILE;}


# read the HSL file and analyze it line by line.
while ( $line = <HSLFILE> ) {
	# is the line contain the specific message
    if ($line =~ m/.+ $HSL_Message .+\{(.+)\}.*/){
        $line = $1;
		# Split the line to array of vars, / / is how the var are seperate in the $line
		@samples = split / /, $line;
		# If define offset , pop the not needed data from the array
		for ($tempOffset = $DataOffset-1; $tempOffset> 0; $tempOffset--){
            shift( @samples );
        }
		# if the output file is ASCII mode
		if   ( $OutputFileFormat eq "ASCII"  ){
            foreach my $el (@samples) {
  	           printf INPFILE "0x$el\n" ;
            }
        }
		#if the output file is Binary mode
        elsif ( $OutputFileFormat eq "binary"){
            @hsamples =();
            foreach my $el (@samples) {
                push @hsamples,hex("$el");
            }
            $output = pack "S*",@hsamples;
            syswrite INPFILE, $output, 320;
        }
    }
}


