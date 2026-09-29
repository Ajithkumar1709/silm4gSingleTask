#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#* DSPC Proprietary Information, (C) COPYRIGHT 2004 DSPC, an Intel Company
#* File name:    MacroEval.pl
#* Programmer:   Ohad S.
#* Create Date:  Feb 2004
#* Description:
#*  This program evaluate Macroes apear is specific Header file.
#*
#* Notes:
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

use File::Basename;

$Version    = "Version: 1.0, Date: February 26, 2004";
$SaveTemps  = 0;
$Verbose    = 0;
$OutPutFileName = "text.txt";
#------------------------------------------------------------------------------
# Handle script command line
#------------------------------------------------------------------------------
$Usage =          "\n\nUsage: $0 <file_name.h> [-o <file_name.txt>] [-D <CompilationFlag>] [-I <IncPath>] [-F <HeadersFileName>] [-v] [-S]\n";
$Usage = $Usage . " The script evaluates Macros that are defined in the input file \n";
$Usage = $Usage . "  and provide a list of the computed values of the Macros\n";
$Usage = $Usage . " The evaluation process is done using the pp.exe.\n";
$Usage = $Usage . " The script output is a text file that contains a list of all the Macros.\n";
$Usage = $Usage . " The user can specify the output format by adding comments after the Macros\n";
$Usage = $Usage . "  in the original input file as follows: \n";
$Usage = $Usage . " #define Bin_MACRO 0x0000  // (BinFormat) \n";
$Usage = $Usage . " #define Hex_MACRO 0x0000  // (HexFormat) \n";
$Usage = $Usage . " #define Hex_bin_MACRO 0x0000  // (HexFormat) (BinFormat) \n";
$Usage = $Usage . " Otherwise, output is presented in Hexformat.\n";
$Usage = $Usage . " Parameters:\n";
$Usage = $Usage . "  * file_name.h ....  Input file name\n";
$Usage = $Usage . " Options:\n";
$Usage = $Usage . "  * -o <output_file> .. User can specify the output file name and path.\n";
$Usage = $Usage . "  * -D ....  Preprocessor flags.\n";
$Usage = $Usage . "  * -I ....  Include files path.\n";
$Usage = $Usage . "  * -F ....  Include files name.\n";
$Usage = $Usage . "  * -v ....  Do it verbosely (print some info messages).\n";
$Usage = $Usage . "  * -S ....  Save temporary files.\n";
$Usage = $Usage . "  * -V ....  Script version.\n";
((scalar @ARGV) < 1) && die "$Usage";

# open input file.
$inp_file = shift (@ARGV);
($inp_file eq "-V")  && die "$Version \n";
($in_name, $in_path, $in_suf) = fileparse( $inp_file, '\.\w+');
# pp input filenames
$pp_inp_file = "$in_name"."_pp_inp_$in_suf";
$pp_out_file = "$in_name"."_pp_out_$in_suf";

open(INPFILE , "< $inp_file") || die "$0: Can't open '$inp_file'.\n";
print "\n --- Process file: [$in_name$in_suf]  ---";

#process parameters and options
$ParamNum = (scalar @ARGV);
while ( $ParamNum != 0 ) {
  $param2 = shift (@ARGV);
  if ( $param2 =~ /^-.*/ ) {
    if    ( $param2 =~ /^-D$/ )     { push @DFlagsArray,    shift (@ARGV);}
    elsif ( $param2 =~ /^-I$/ )     { push @IncPathArray,   shift (@ARGV);}
    elsif ( $param2 =~ /^-F$/ )     { push @HeadersArray,   shift (@ARGV);}
    elsif ( $param2 =~ /^-o$/ )     { $OutPutFileName = shift (@ARGV); }
    elsif ( $param2 =~ /^-v$/ )     { $Verbose = 1; }
    elsif ( $param2 =~ /^-S$/ )     { $SaveTemps = 1; }
        else {die "$0: '$param2' - unknown option\n";}
  }
  $ParamNum = scalar(@ARGV);
}

# Create the PP command line switches string according to input flags
$CommandLineSwitchs = "";
# -D flag
$temp = shift (@DFlagsArray);
while ($temp ne "")
{
  $CommandLineSwitchs = $CommandLineSwitchs." -D"."$temp";
  $temp = shift (@DFlagsArray);
}
# -I flag
$temp = shift (@IncPathArray);
while ($temp ne "")
{
  $CommandLineSwitchs = $CommandLineSwitchs." -I"."$temp";
  $temp = shift (@IncPathArray);
}
# -o flag
$CommandLineSwitchs = $CommandLineSwitchs." -o"." $pp_out_file";
# -v flag
if ( $Verbose == 1 ) {
    $CommandLineSwitchs = $CommandLineSwitchs." -v";
}

#------------------------------------------------------------------------------
# Edit the PP.exe input file
#------------------------------------------------------------------------------

# Create temp input and output files for the PP.exe.
open(PPINP , "> $pp_inp_file") || die "$0: Can't open temp file (please contact ohads] .\n";
if ( $Verbose ==1 ) { print "\n --- Preprocessor input  file: [$pp_inp_file]  ---";}
if ( $Verbose ==1 ) { print "\n --- Preprocessor output file: [$pp_out_file]  ---";}

# Add all the needed #include command (according to command line at the start of pp intput file)
print PPINP "\nAdded includes acording to input command line\n";
$temp = shift (@HeadersArray);
while ($temp ne "")
{
  print PPINP "#include \"$temp\" \n";
  $temp = shift (@HeadersArray);
}
# Dump all the original input file to the temp pp input file and log all the #define Macros
while ( $line = <INPFILE> ) {
    print PPINP $line;
    # is the line contain #define ?
    if ($line =~ /\s*\#define\s+([a-zA-Z0-9_]+)/ ){
        # Create an array of defines
        $Macro = {};
        $Macro->{name} = $1;
        # Set the Display mode (Default HEX)
        $Macro->{HexDisplay} = 1;
        # is the line contain "// (BinFormat)" ?
        if ($line =~ /\/\/\s*\(BinFormat\)/){
            $Macro->{BinDisplay} = 1;
            $Macro->{HexDisplay} = 0;
            if ($line =~ /\(BinFormat\)\s*\(HexFormat\)/){
                $Macro->{HexDisplay} = 1;
            }
        }
        # is the line contain "// (HexFormat)" ?
        elsif ($line =~ /\/\/\s*\(HexFormat\)/){
            $Macro->{HexDisplay} = 1;
            $Macro->{BinDisplay} = 0;
            if ($line =~ /\(HexFormat\)\s*\(BinFormat\)/){
                $Macro->{BinDisplay} = 1;
            }
        }
        push @MacrosArray, $Macro; # @MacrosArray - holds all the Macros that were listed
    }
}
# Copy only one event of each macro from @MacrosArray to @comprassMacrosArray
# sort in alphabetic order (filed name only)
@MacrosArray = sort {$a->{name} cmp $b->{name};} @MacrosArray;
# Moves only one item (of every macro) to the compress array
$first = shift (@MacrosArray);
push @comprassMacrosArray, $first;
for $el ( @MacrosArray ) {
    if ($first->{name} ne $el->{name} ) {
        push @comprassMacrosArray, $el;
        $first = $el;
    }
}
# Add ,at the end of the file, section that holds all the needed Macro
print PPINP "\nAdded Macros to be solve section \n";
for $el ( @comprassMacrosArray ) {
    $temp = $el -> {name};
    print PPINP "\$$temp = $temp";
    print PPINP "\n";
}

#------------------------------------------------------------------------------
# Calling preprocessor utility
#------------------------------------------------------------------------------
if ( $Verbose ==1 ) { print "\n --- Preprocessor Command-Line :\n";}
system("\"pp.exe\" $pp_inp_file $CommandLineSwitchs") == 0 or die " \n **** Error: Preprocessor utility error\n";

#------------------------------------------------------------------------------
# Processing the PP output file and create the script output file
#------------------------------------------------------------------------------
open(SCRIPTOUT , "> $OutPutFileName") || die "$0: Can't open $OutPutFileName .\n";
print "\n --- Script output file: [$OutPutFileName]  ---";

open(TEMP , "< $pp_out_file") || die "$0: Can't open $pp_out_file \n";

# Read the PP output file and search for the section that starts with "Added Macros to be solve section"
$flag =0;
while ( ($flag == 0)&& ($line = <TEMP>) ) {
    if ($line =~ /Added Macros to be solve section/ ){
        $flag = 1;
    }
}
# Read a line to be evaluate
while ($line = <TEMP>){
    # Check if line contain an Eval Macro (Solve a bug where the pp added blank lines)
    if ( $line =~ /^([a-zA-Z0-9_\$]+)s*/){
        # assumption (1) :
        # I assume the Macros in the file are at the same order as the Array
        $el = shift (@comprassMacrosArray);
        # $word is the Macro name that was resolved
        $word = $1;
        $word =~ tr/\$//d; # Remove $ from the Macro name
        # Check if assumption (1) is TRUE ?
        ( $word  eq $el ->{name } ) || die "\n$0: Bug : Please call ohads 7535\n";

        # Remove the (B) and the (H) to set the $line as a valid input to eval
        $temp = $line;
        $temp =~ tr/L//d; # Remove L from the Macro name
       #case the original Macro is only L's
        if ( $temp =~ /^\$ =/) {
            $temp =~ tr/$//d;
            $temp = "\$Dummy ".$temp;
        }
        # Eval the expression !!!
        $temp1 = eval ($temp); #calculate the expretion
    }
    $OutputLine = "$word = ";
    # Translet eval value to a Bin display
    if ( $el ->{BinDisplay} ){
        $outstring = "";
        $TempVal = sprintf " %08X", $temp1;
        while ( $TempVal =~ /([A-F0-9])/g)
        {
            $Temp1 = $1;
            if ($Temp1 eq "0") {$outstring = $outstring." 0000";}
            elsif ($Temp1 eq "1") {$outstring = $outstring." 0001";}
            elsif ($Temp1 eq "2") {$outstring = $outstring." 0010";}
            elsif ($Temp1 eq "3") {$outstring = $outstring." 0011";}
            elsif ($Temp1 eq "4") {$outstring = $outstring." 0100";}
            elsif ($Temp1 eq "5") {$outstring = $outstring." 0101";}
            elsif ($Temp1 eq "6") {$outstring = $outstring." 0110";}
            elsif ($Temp1 eq "8") {$outstring = $outstring." 1000";}
            elsif ($Temp1 eq "9") {$outstring = $outstring." 1001";}
            elsif ($Temp1 eq "A") {$outstring = $outstring." 1010";}
            elsif ($Temp1 eq "B") {$outstring = $outstring." 1011";}
            elsif ($Temp1 eq "C") {$outstring = $outstring." 1100";}
            elsif ($Temp1 eq "D") {$outstring = $outstring." 1101";}
            elsif ($Temp1 eq "E") {$outstring = $outstring." 1110";}
            elsif ($Temp1 eq "F") {$outstring = $outstring." 1111";}
        }
        $BinVal = "\t(Bin)".$outstring;
    }
    # Translet eval value to a Hex display
    if ( $el ->{HexDisplay}){
        $HexVal = sprintf " 0x%08X ", $temp1;
        $HexVal = "\t(Hex)".$HexVal
    }
    print SCRIPTOUT  "$OutputLine $HexVal $BinVal \n";
    $BinVal="";$HexVal="";
}
#------------------------------------------
# Close all files and delete the temp files
#------------------------------------------
close PPINP;
close SCRIPTOUT;
close TEMP;
if ( $SaveTemps == 0 ) {
    system("del /Q /F $pp_inp_file");
    system("del /Q /F $pp_out_file");
}
print "\n";
(1);

