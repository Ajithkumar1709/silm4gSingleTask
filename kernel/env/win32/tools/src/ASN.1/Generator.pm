#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# ASN.1 Compiler Service Library
#
# Generate C/H files
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         09-Aug-2009     KS         1. Initial Version
#-----------------------------------------------------------------------
package Generator;



use strict;
use warnings;

use File::Basename;

use Globals;
use Commons qw/:globals :common_func :filecodes/;

use Composer::Commons;

use Generator::ENUMERATED;
use Generator::STRING;
use Generator::STRUCT;

use Composer::ENUMERATED;

#------------------ Application-wide Variables ---------------
our $DEBUG;
our %ASN1;
our %ASN1Index;
our %MAP;

#----------------- Local Globals ---------------------

#-------------------- Various Generators ---------------
sub makecode
  {
    my $files   = shift;
    my $Version = shift;
    my $Build   = shift;
    my %Params  = @_;

    for ( my $i = 0 ; $i <= $#{$files} ; $i++ )
      {
        return FAILED
          if not open( $files->[$i][HANDLE], ">$files->[$i][NAME]" );
      }

    print "Generating source files ... ";

    _writeHeaders( $files, $Version, $Build );

    # Write INTEGER as macros
    _genMACROS( $files->[MAIN][HANDLE] );

    # Write ENUMERATED nested in SEQUENCE and CHOICE and pure ENUMERATED
    _genENUMERATED( $files, $Params{ENUMPREFIX} );

 # Write BIT/OCTET STRING pure and nested in SEQUENCE and CHOICE and SEQUENCE OF
    _genSTRINGS( $files, $Params{TYPEPREFIX} );

    # Write SEQUENCE and CHOICE
    _genSTRUCTS( $files, \%Params );

    _writeFooters($files);

    for ( my $i = 0 ; $i <= $#{$files} ; $i++ )
      {
        close $files->[$i][HANDLE];
      }
    print "DONE\n";

    return SUCCEED;
  }

#-----------------------------------------------------------------------
sub _genMACROS
  {
    my $Main = shift;
    foreach my $const (@ASN1Index)
      {
        next if $const->[1] ne 'INTEGER';
        next if ref $ASN1{ $const->[0] }{INTEGER};

        my $const_name = $const->[0];
        $const_name =~ s/-/_/g;
        print $Main "#define $const_name"
          . ( ' ' x ( 39 - length("#define $const_name") ) )
          . $ASN1{ $const->[0] }{INTEGER} . "\n";

        $ASN1{ $const->[0] }{DONE}  = 1;
        $ASN1{ $const->[0] }{LABEL} = $const_name;
      }

    print $Main "\n\n";
  }

sub _genENUMERATED
  {
    my $Files  = shift;
    my $Prefix = shift;

    foreach my $struct (@ASN1Index)
      {
        next
          if $struct->[1]  ne 'SEQUENCE'
          and $struct->[1] ne 'CHOICE'
          and $struct->[1] ne 'ENUMERATED'
          and $struct->[1] ne 'SEQUENCEOF';

        if ( $struct->[1] eq 'SEQUENCEOF' )
          {
            next
              unless defined $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}
              and ref $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE} eq 'HASH'
              and
              (    defined $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{SEQUENCE}
                or $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{CHOICE}
                or $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{ENUMERATED} );
          }

        Generator::ENUMERATED::lookin( $Files, $struct, $struct->[1], $Prefix )
          if $struct->[1] eq 'SEQUENCE'
          or $struct->[1] eq 'CHOICE'
          or $struct->[1] eq 'SEQUENCEOF';

        Generator::ENUMERATED::pureENUMERATED( $Files, $struct, $Prefix )
          if $struct->[1] eq 'ENUMERATED';
      }

    Composer::ENUMERATED::flush();
  }

sub _genSTRINGS
  {
    my $Files  = shift;
    my $Prefix = shift;

    foreach my $struct (@ASN1Index)
      {
        next
          if $struct->[1]  ne 'SEQUENCE'
          and $struct->[1] ne 'CHOICE'
          and $struct->[1] ne 'BITSTRING'
          and $struct->[1] ne 'SEQUENCEOF';

        Generator::STRING::lookin( $Files, $struct, $struct->[1], $Prefix,
            'BITSTRING' )
          if $struct->[1] eq 'SEQUENCE'
          or $struct->[1] eq 'CHOICE';

        Generator::STRING::pureSTRING( $Files, $struct, $Prefix )
          if (
            (
                    $struct->[1]                              eq 'BITSTRING'
                and ref $ASN1{ $struct->[0] }{ $struct->[1] } eq 'ARRAY'
                and (
                    (
                        scalar @{ $ASN1{ $struct->[0] }{ $struct->[1] } } == 1
                        and Composer::Commons::GetInteger(
                            $ASN1{ $struct->[0] }{ $struct->[1] }[0]
                        ) > 32
                    )
                    or (
                        scalar @{ $ASN1{ $struct->[0] }{ $struct->[1] } } == 2
                        and Composer::Commons::GetInteger(
                            $ASN1{ $struct->[0] }{ $struct->[1] }[1]
                        ) <= 2048
                    )
                )
            )
            or (    $struct->[1] eq 'SEQUENCEOF'
                and defined $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}
                and ref $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE} eq 'HASH'
                and
                defined $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{BITSTRING} )

          );
      }

    foreach my $struct (@ASN1Index)
      {
        next
          if $struct->[1] ne 'BITSTRING';

        Generator::STRING::pureSTRING( $Files, $struct, $Prefix )
          if ref $ASN1{ $struct->[0] }{ $struct->[1] } eq 'HASH'
          or (
            ref $ASN1{ $struct->[0] }{ $struct->[1] } eq 'ARRAY'
            and (
                (
                    scalar @{ $ASN1{ $struct->[0] }{ $struct->[1] } } == 1
                    and Composer::Commons::GetInteger(
                        $ASN1{ $struct->[0] }{ $struct->[1] }[0]
                    ) <= 32
                )
                or (
                    scalar @{ $ASN1{ $struct->[0] }{ $struct->[1] } } == 2
                    and Composer::Commons::GetInteger(
                        $ASN1{ $struct->[0] }{ $struct->[1] }[1]
                    ) > 2048
                )
            )
          );
      }

    foreach my $struct (@ASN1Index)
      {
        next
          if $struct->[1]  ne 'SEQUENCE'
          and $struct->[1] ne 'CHOICE'
          and $struct->[1] ne 'OCTETSTRING'
          and $struct->[1] ne 'SEQUENCEOF';

        Generator::STRING::lookin( $Files, $struct, $struct->[1], $Prefix,
            'OCTETSTRING' )
          if $struct->[1] eq 'SEQUENCE'
          or $struct->[1] eq 'CHOICE';

        Generator::STRING::pureSTRING( $Files, $struct, $Prefix )
          if ( $struct->[1] eq 'OCTETSTRING'
            and ref $ASN1{ $struct->[0] }{ $struct->[1] } ne 'ARRAY' )
          or (  $struct->[1] eq 'SEQUENCEOF'
            and defined $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}
            and ref $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE} eq 'HASH'
            and
            defined $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{OCTETSTRING} );

        Generator::STRING::pureSTRING( $Files, $struct, $Prefix )
          if $struct->[1]                               eq 'OCTETSTRING'
          and ref $ASN1{ $struct->[0] }{ $struct->[1] } eq 'ARRAY';
      }
  }

sub _genSTRUCTS
  {
    my $Files  = shift;
    my $Params = shift;

    my $ThereIsSomethingToGenerate = TRUE;
    my $Counter                    = 1;
    my $Stub                       = TRUE;
    while ($ThereIsSomethingToGenerate)
      {
        $ThereIsSomethingToGenerate = FALSE;

        foreach my $struct (@ASN1Index)
          {
            next
              if defined $ASN1{ $struct->[0] }{DONE}
              and $ASN1{ $struct->[0] }{DONE} == 1;

            next
              if defined $ASN1{ $struct->[0] }{NOTSUPPORTED}
              and $ASN1{ $struct->[0] }{NOTSUPPORTED} == 1;

            next
              if defined $ASN1{ $struct->[0] }{SWALLOWED}
              and ref $ASN1{ $struct->[0] }{ $struct->[1] } eq 'ARRAY';

            next
              if defined $ASN1{ $struct->[0] }{SWALLOWED}
              and (
                not defined $ASN1{ $struct->[0] }{ $struct->[1] }{EXTENDS}
                or (
                        defined $ASN1{ $struct->[0] }{ $struct->[1] }{EXTENDS}
                    and
                    defined $ASN1{ $struct->[0] }{ $struct->[1] }{EXTENDS}{REF}
                    and %{ $ASN1{ $struct->[0] }{ $struct->[1] }{EXTENDS}{REF} }
                    and not scalar grep {
                        $ASN1{ $struct->[0] }{ $struct->[1] }{EXTENDS}{REF}{$_}
                          eq 'REFERENCE'
                    } keys
                    %{ $ASN1{ $struct->[0] }{ $struct->[1] }{EXTENDS}{REF} }
                )
              );

            next
              if _globallyUpgraded( $ASN1{ $struct->[0] }, $struct->[1] ) ==
              TRUE;

            Generator::STRUCT::generate( $Files, $struct, $Params,
                \$ThereIsSomethingToGenerate, 'USUAL' );
          }

        foreach my $struct (@ASN1Index)
          {
            next
              if defined $ASN1{ $struct->[0] }{DONE}
              and $ASN1{ $struct->[0] }{DONE} == 1;
            next
              if defined $ASN1{ $struct->[0] }{NOTSUPPORTED}
              and $ASN1{ $struct->[0] }{NOTSUPPORTED} == 1;

            next
              if defined $ASN1{ $struct->[0] }{SWALLOWED}
              and ref $ASN1{ $struct->[0] }{ $struct->[1] } eq 'ARRAY';

            next
              if defined $ASN1{ $struct->[0] }{SWALLOWED}
              and (
                not defined $ASN1{ $struct->[0] }{ $struct->[1] }{EXTENDS}
                or (
                        defined $ASN1{ $struct->[0] }{ $struct->[1] }{EXTENDS}
                    and
                    defined $ASN1{ $struct->[0] }{ $struct->[1] }{EXTENDS}{REF}
                    and not scalar grep {
                        $ASN1{ $struct->[0] }{ $struct->[1] }{EXTENDS}{REF}{$_}
                          eq 'REFERENCE'
                    } keys
                    %{ $ASN1{ $struct->[0] }{ $struct->[1] }{EXTENDS}{REF} }
                )
              );

            next
              if _globallyUpgraded( $ASN1{ $struct->[0] }, $struct->[1] ) ==
              FALSE
              and _locallyUpgraded( $ASN1{ $struct->[0] } ) == FALSE;

            Generator::STRUCT::generate( $Files, $struct, $Params, \$Stub,
                'UPGRADE_ONLY' );
          }

        $Counter++;
      }

    foreach my $struct (@ASN1Index)
      {
        next
          if defined $ASN1{ $struct->[0] }{CODE_DONE}
          and $ASN1{ $struct->[0] }{CODE_DONE} == 1;
        next
          if defined $ASN1{ $struct->[0] }{NOTSUPPORTED}
          and $ASN1{ $struct->[0] }{NOTSUPPORTED} == 1;

        Composer::SEQUENCE::compose( 'CODE', $Files, $struct, $struct->[0],
            $Params )
          if $struct->[1] eq 'SEQUENCE';
        Composer::CHOICE::compose( 'CODE', $Files, $struct, $struct->[0],
            $Params )
          if $struct->[1] eq 'CHOICE';
      }
  }

sub _writeHeaders
  {
    my $files   = shift;
    my $Version = shift;
    my $Build   = shift;

    my $name = basename( $files->[MAIN][NAME] );
    $name =~ s/\./_/g;
    $name =~ tr/[a-z]/[A-Z]/;

    printf { $files->[MAIN][HANDLE] } <<MAIN_HEADER, ($name) x 2;
/***************************************************************************
 * (C) Copyright [2009-2010] Marvell International Ltd.
 * All Rights Reserved
 ***************************************************************************
 *
 * ASN.1 Translator version $Version build $Build
 *
 ***************************************************************************
 *
 * File Description:
 *
 * The file is automatically generated by ASN.1 Conversion SW
 * and should not be edited locally.
 *
 ***************************************************************************
 *
 ***************************************************************************/

#if !defined (%s)
#define %s

#include <system.h>


MAIN_HEADER

    foreach my $file ( ENCE, ENCB, ENCO, ENCS, ENCC )
      {
        $name = basename( $files->[$file][NAME] );
        $name =~ s/\..+$//g;
        $name =~ tr/[a-z]/[A-Z]/;
        my $ext = basename $files->[EXT][NAME];

        printf { $files->[$file][HANDLE] } <<ENC_HEADER, $name, $ext;
/***************************************************************************
 * (C) Copyright [2009-2010] Marvell International Ltd.
 * All Rights Reserved
 ***************************************************************************
 *
 * ASN.1 Translator version $Version build $Build
 *
 ***************************************************************************
 *
 * File Description:
 *
 * The file is automatically generated by ASN.1 Conversion SW
 * and should not be edited locally.
 *
 ***************************************************************************
 *
 ***************************************************************************/

#define MODULE_NAME "%s"

#include <system.h>
#include <%s>


ENC_HEADER
      }

    foreach my $file ( DECE, DECB, DECO, DECS, DECC )
      {
        $name = basename( $files->[$file][NAME] );
        $name =~ s/\..+$//g;
        $name =~ tr/[a-z]/[A-Z]/;
        my $ext = basename $files->[EXT][NAME];

        printf { $files->[$file][HANDLE] } <<DEC_HEADER, $name, $ext;
/***************************************************************************
 * (C) Copyright [2009-2010] Marvell International Ltd.
 * All Rights Reserved
 ***************************************************************************
 *
 * ASN.1 Translator version $Version build $Build
 *
 ***************************************************************************
 *
 * File Description:
 *
 * The file is automatically generated by ASN.1 Conversion SW
 * and should not be edited locally.
 *
 ***************************************************************************
 *
 ***************************************************************************/

#define MODULE_NAME "%s"

#include <system.h>
#include <kernel.h>

#include <%s>

NO_SIGNALS_USED



DEC_HEADER
      }

    $name = basename( $files->[EXT][NAME] );
    $name =~ s/\./_/g;
    $name =~ tr/[a-z]/[A-Z]/;
    my $asn = basename $files->[MAIN][NAME];

    printf { $files->[EXT][HANDLE] } <<EXT_HEADER, ($name) x 2, $asn;
/***************************************************************************
 * (C) Copyright [2009-2010] Marvell International Ltd.
 * All Rights Reserved
 ***************************************************************************
 *
 * ASN.1 Translator version $Version build $Build
 *
 ***************************************************************************
 *
 * File Description:
 *
 * The file is automatically generated by ASN.1 Conversion SW
 * and should not be edited locally.
 *
 ***************************************************************************
 *
 ***************************************************************************/

#if !defined (%s)
#define %s

#include <system.h>
#include <utper.h>
#include <%s>

EXT_HEADER
  }

sub _writeFooters
  {
    my $files = shift;

    print { $files->[MAIN][HANDLE] } <<MAIN_FOOTER;

#endif

MAIN_FOOTER

    print { $files->[EXT][HANDLE] } <<EXT_FOOTER;

#endif

EXT_FOOTER
  }

sub _globallyUpgraded
  {
    my $struct = shift;
    my $type   = shift;

    return FALSE if not defined $struct->{UPGRADED};

    return FALSE if $type eq 'SEQUENCEOF';

    if (    defined $struct->{UPGRADED}
        and not defined $struct->{UPGRADE}
        and not defined $struct->{SWALLOWED} )
      {
        my $isReference = 0;
        if (    defined $struct->{$type}{EXTENDS}
            and defined $struct->{$type}{EXTENDS}{REF} )
          {
            foreach my $field ( keys %{ $struct->{$type}{EXTENDS}{REF} } )
              {
                if ( $struct->{$type}{EXTENDS}{REF}{$field} eq 'REFERENCE' )
                  {
                    $isReference = 1;
                    last;
                  }
              }
            return FALSE if $isReference;
            return TRUE;
          }
      }

    return TRUE
      if defined $struct->{UPGRADE}
      and defined $struct->{UPGRADED}
      and grep { $_->{TYPE} eq 'GLOBAL' } @{ $struct->{UPGRADE} };

    return FALSE;
  }

sub _locallyUpgraded
  {
    my $struct = shift;

    return FALSE if ref $struct ne 'HASH';

    return TRUE if defined $struct->{UPGRADED};

    $struct = SkipStruct($struct);

    return TRUE if defined $struct->{UPGRADED};

    foreach my $field ( keys %$struct )
      {
        next if ref $struct->{$field} ne 'HASH';

        return TRUE if _locallyUpgraded( $struct->{$field} ) == TRUE;
      }

    return FALSE;
  }

#-----------------------------------------------------------------------
1;
