#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#---------------------------------------------------------------------
#
# ASN.1 Compiler
#
#---------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#---------------------------------------------------------------------
# Version     Date            Author     Description
# 0.09        23-Mar-2010     KS         1. Adapt parser for R7
#                                        2. Adapt code generation procedures for R7
# 0.08        21-Mar-2010     KS         1. Resolve some bugs in parser
#                                        2. Beta Release
# 0.07        11-Mar-2010     KS         1. Adapt parser for LTE
#                                        2. Adapt code generation procedures for LTE
# 0.06        09-Mar-2010     KS         1. Alpha Release
# 0.05        02-Feb-2010     KS         1. Add upgrade procedures
# 0.04        17-Jan-2010     KS         1. Generate enc/dec files for SEQUENCE and CHOICE
# 0.03        28-Dec-2009     KS         1. Generate enc/dec files for ENUMERATED
#                                           BIT STRING and OCTET STRING
# 0.02        23-Dec-2009     KS         1. Generate main header file
# 0.01        09-Aug-2009     KS         1. Initial Version
#---------------------------------------------------------------------

# Application version
our $VERSION = '0.09';
our $BUILD   = '102';

use strict;
use warnings;

use lib './ASN.1';

use File::Basename;
use IO::Handle;

use Parser;
use Generator;
use Loader;
use Upgrader;

use Globals;
use Commons qw/:globals :common_func :filecodes/;

# Trap internal errors (hope there are no such)
BEGIN
{
    $SIG{__WARN__} = sub {
        print STDERR "\n\nINTERNAL ERROR :: $_[0]\n";
        my @caller = caller(2);
        print STDERR "Caller :: " . join( ",", map { $_ ? $_ : '' } @caller );
        exit 1;
    };
}

autoflush STDOUT 1;
autoflush STDERR 1;

# Debug or not debug?
Debug(0);
Debug(1) if defined $ENV{ASN_DEBUG} and $ENV{ASN_DEBUG} == 1;

Verbose(0);
Verbose(1) if defined $ENV{ASN_VERBOSE} and $ENV{ASN_VERBOSE} == 1;

# Greetings
print STDERR <<VERSION;
ASN.1 Compiler version $VERSION, build $BUILD
(C) Copyright [2008,2009] Marvell International Ltd. All rights reserved.
VERSION

#--------------------- Start Main Procedure ----------------------

#-----------------------------------------------------------------
# 0. Decode and analyze input parameters
#-----------------------------------------------------------------
my $OutFilenamePrefix = '';
my $MapFile           = '';
my $Asn1File          = '';
my %PARAMS            = ();

# Defaults
$PARAMS{ENUMPREFIX}   = 'U';
$PARAMS{TYPEPREFIX}   = 'U';
$PARAMS{CHOICETYPE}   = 'POINTER';
$PARAMS{OPTIONALTYPE} = 'POINTER';
$PARAMS{SEQOFTHRE}    = 0;

my $DumpTrees = FALSE;

while (@ARGV)
  {
    my $param = shift @ARGV;

    if    ( $param =~ /[\/\-]o=(.+)/ )  { $OutFilenamePrefix  = $1 }
    elsif ( $param =~ /[\/\-]e=(.+)/ )  { $PARAMS{ENUMPREFIX} = $1 }
    elsif ( $param =~ /[\/\-]t=(.+)/ )  { $PARAMS{TYPEPREFIX} = $1 }
    elsif ( $param =~ /[\/\-]mi=(.+)/ ) { $MapFile            = $1 }
    elsif ( $param =~ /[\/\-]dump/ )    { $DumpTrees          = TRUE }
    elsif ( $param =~ /[\/\-]choice=(.+)/ )
      {
        $PARAMS{CHOICETYPE} = $1;
        Error("Unknown type for CHOICE element encoding: $PARAMS{CHOICETYPE}")
          unless $PARAMS{CHOICETYPE} =~ /POINTER|STATIC/;
      }
    elsif ( $param =~ /[\/\-]optional=(.+)/ )
      {
        $PARAMS{OPTIONALTYPE} = $1;
        Error(
            "Unknown type for OPTIONAL element encoding: $PARAMS{OPTIONALTYPE}")
          unless $PARAMS{OPTIONALTYPE} =~ /POINTER|STATIC/;
      }
    elsif ( $param =~ /[\/\-]seqof=(.+)/ )
      {
        $PARAMS{SEQOFTHRE} = $1;
        Error("Value of SEQUENCE OF encoding threshold is not numerical")
          unless $PARAMS{SEQOFTHRE} =~ /\d+/;
      }
    else { $Asn1File = $param }
  }

#------------------------------------------------------------------------
# 1. Parse the original ASN.1 description, and store extracted structures
#    in global hash ASN1. Also fill ASN1 Index array
#------------------------------------------------------------------------
my $parserState = Parser::parse($Asn1File);
Error("Unexpected end of ASN.1 file $Asn1File") if $parserState ne 'ASIDE';

#------------------------------------------------------------------------
# 2. Load and analyze MAP file (if any)
#------------------------------------------------------------------------
&Loader::loadmap($MapFile) if $MapFile;

#------------------------------------------------------------------------
# 3.
#    3.1 Mark 'NON SUPPORTED' elements
#    3.2 Locate and try to upgrade all structures that mark for upgrading
#------------------------------------------------------------------------
if (%MAP)
  {
    print "Applying mapping:\n";

    # 3.1
    &Upgrader::marknotsupported;

    # 3.2
    &Upgrader::markstatic;

    # 3.3
    &Upgrader::markencodeonly;

    # 3.4
    &Upgrader::markdecodeonly;

    # 3.5
    &Upgrader::upgrade;

    print "DONE\n";
  }

if ( $DumpTrees == TRUE )
  {
    foreach my $pref (qw/NOTSUPPORTED STATIC IGNORED ENCODE_ONLY DECODE_ONLY/)
      {
        Globals::DumpTree( \%ASN1, \%ASN1Usage, $OutFilenamePrefix, 'USES',
            $pref );
        Globals::DumpTree( \%ASN1, \%ASN1Usage, $OutFilenamePrefix, 'USEDIN',
            $pref );
      }

    print "Trees dumped to c:\\\n";
    exit 0;
  }

#------------------------------------------------------------------------
# 4. Now generate files
#------------------------------------------------------------------------
my $path   = dirname $Asn1File;
my $spacer = '_';
$spacer = '' if not $OutFilenamePrefix;
my @Files = (
    [ $path . "\\" . $OutFilenamePrefix . $spacer . 'asn.h' ]
    ,    # header file containing data type definitions

    [ $path . "\\" . $OutFilenamePrefix . $spacer . 'ENCE.c' ]
    ,    # encode functions for ENUMERATED data types
    [ $path . "\\" . $OutFilenamePrefix . $spacer . 'ENCB.c' ]
    ,    # encode functions for BIT STRING data types
    [ $path . "\\" . $OutFilenamePrefix . $spacer . 'ENCO.c' ]
    ,    # encode functions for OCTET STRING data types
    [ $path . "\\" . $OutFilenamePrefix . $spacer . 'ENCS.c' ]
    ,    # encode functions for SEQUENCE data types
    [ $path . "\\" . $OutFilenamePrefix . $spacer . 'ENCC.c' ]
    ,    # encode functions for CHOICE data types

    [ $path . "\\" . $OutFilenamePrefix . $spacer . 'DECE.c' ]
    ,    # decode functions for ENUMERATED data types
    [ $path . "\\" . $OutFilenamePrefix . $spacer . 'DECB.c' ]
    ,    # decode functions for BIT STRING data types
    [ $path . "\\" . $OutFilenamePrefix . $spacer . 'DECO.c' ]
    ,    # decode functions for OCTET STRING data types
    [ $path . "\\" . $OutFilenamePrefix . $spacer . 'DECS.c' ]
    ,    # decode functions for SEQUENCE data types
    [ $path . "\\" . $OutFilenamePrefix . $spacer . 'DECC.c' ]
    ,    # decode functions for CHOICE data types

    [ $path . "\\" . $OutFilenamePrefix . $spacer . 'ext.h' ]
    ,    # function prototypes for encode and decode functions
);

Generator::makecode( \@Files, $VERSION, $BUILD, %PARAMS );

#----------------------- END OF MAIN -------------------------------------
