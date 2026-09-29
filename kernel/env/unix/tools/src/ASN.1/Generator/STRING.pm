#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# ASN.1 Compiler Service Library
#
# Proceed BIT and OCTET STRING types
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         18-Aug-2009     KS         1. Initial Version
#-----------------------------------------------------------------------
package Generator::STRING;

use strict;
use warnings;

use Globals;
use Commons qw/:globals :common_func :filecodes/;

use Composer::STRING;

#------------------ Application-wide Variables ---------------
our $DEBUG;
our $VERBOSE;
our %ASN1;
our %ASN1Index;
our %MAP;

# -------------------- Main i/f functions --------------------
sub lookin
  {
    my $Files      = shift;
    my $struct     = shift;
    my $structType = shift;
    my $typePrefix = shift;
    my $String     = shift;

    return if defined $ASN1{ $struct->[0] }{$structType}{NOTSUPPORTED};

    return if defined $ASN1{ $struct->[0] }{NOTSUPPORTED};

    foreach my $elem ( @{ $ASN1{ $struct->[0] }{$structType}{_ORDER_} } )
      {
        next if defined $ASN1{ $struct->[0] }{$structType}{$elem}{NOTSUPPORTED};

        my $struct_name = $struct->[0];
        if (
            (
                defined $ASN1{ $struct->[0] }{$structType}{$elem}{$String}
                or ( defined $ASN1{ $struct->[0] }{$structType}{$elem}{VALUE}
                    and ref $ASN1{ $struct->[0] }{$structType}{$elem}{VALUE} eq
                    'ARRAY'
                    and
                    defined $ASN1{ $struct->[0] }{$structType}{$elem}{VALUE}[0]
                    and $ASN1{ $struct->[0] }{$structType}{$elem}{VALUE}[0] eq
                    $String )
            )
            and not defined $ASN1{ $struct->[0] }{$structType}{$elem}{DONE}
          )
          {
            my $StringType = 'REGULAR';
            $StringType = 'RANGEOCTETSTRING'
              if defined $ASN1{ $struct->[0] }{$structType}{$elem}{OCTETSTRING}
              and ref $ASN1{ $struct->[0] }{$structType}{$elem}{OCTETSTRING} eq
              'HASH'
              and defined $ASN1{ $struct->[0] }{$structType}{$elem}{OCTETSTRING}
              {VALUE}
              and
              ref $ASN1{ $struct->[0] }{$structType}{$elem}{OCTETSTRING}{VALUE}
              eq 'ARRAY';

            @{ $ASN1{ $struct->[0] }{$structType}{$elem} }{qw/DONE CODE_DONE/} =
              (1) x 2
              if Composer::STRING::compose(
                'BITSTRING',
                $struct->[0],
                $elem,
                $Files,
                $typePrefix,
                $StringType,
                defined $ASN1{ $struct->[0] }{$structType}{$elem}{$String}
                ? $ASN1{ $struct->[0] }{$structType}{$elem}{$String}
                : $ASN1{ $struct->[0] }{$structType}{$elem},
                $ASN1{ $struct->[0] }{$structType}{$elem}
              ) == TRUE;
          }
      }

    foreach my $elem ( @{ $ASN1{ $struct->[0] }{$structType}{_ORDER_} } )
      {

        #next if $elem eq '_ORDER_';
        #next if $elem eq 'OPTIONAL';
        next if defined $ASN1{ $struct->[0] }{$structType}{$elem}{NOTSUPPORTED};

        my $struct_name = $struct->[0];

        @{ $ASN1{ $struct->[0] }{$structType}{$elem} }{qw/DONE CODE_DONE/} =
          (1) x 2
          if not defined $ASN1{ $struct->[0] }{$structType}{$elem}{DONE}
          and (
            (
                    defined $ASN1{ $struct->[0] }{$structType}{$elem}{SEQUENCE}
                and defined $ASN1{ $struct->[0] }{$structType}{$elem}{SEQUENCE}
                {KIND}
                and $ASN1{ $struct->[0] }{$structType}{$elem}{SEQUENCE}{KIND} eq
                'EMPTY'
            )
            and Composer::STRING::compose(
                'BITSTRING',
                "$struct->[0]-$elem",
                '',
                $Files,
                $typePrefix,
                'SEQUENCE',
                $ASN1{ $struct->[0] }{$structType}{$elem}{SEQUENCE},
                $ASN1{ $struct->[0] }{$structType}{$elem}
            ) == TRUE
          );
      }

    foreach my $elem ( @{ $ASN1{ $struct->[0] }{$structType}{_ORDER_} } )
      {
        next if defined $ASN1{ $struct->[0] }{$structType}{$elem}{NOTSUPPORTED};

        my $struct_name = $struct->[0];

        if ( defined $ASN1{ $struct->[0] }{$structType}{$elem}{CHOICE} )
          {
            _proceedNestedSTRING(
                $ASN1{ $struct->[0] }{$structType}{$elem}{CHOICE},
                "$struct_name-$elem", $Files, $typePrefix, $String );
          }
        elsif ( defined $ASN1{ $struct->[0] }{$structType}{$elem}{SEQUENCE}
            and not
            defined $ASN1{ $struct->[0] }{$structType}{$elem}{SEQUENCE}{KIND} )
          {
            _proceedNestedSTRING(
                $ASN1{ $struct->[0] }{$structType}{$elem}{SEQUENCE},
                "$struct_name-$elem", $Files, $typePrefix, $String );
          }
      }
  }

sub pureSTRING
  {
    my $Files      = shift;
    my $struct     = shift;
    my $typePrefix = shift;

    return if defined $ASN1{ $struct->[0] }{NOTSUPPORTED};

    my $stringType = 'REGULAR';

    if ( $struct->[1] eq 'SEQUENCEOF' )
      {
        $stringType = 'RANGESEQUENCEOF'
          if defined $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{BITSTRING}
          and ref $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{BITSTRING} eq
          'ARRAY'
          and
          scalar @{ $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{BITSTRING} } ==
          2;

        $stringType = 'RANGESEQUENCEOFOCTETSTRING'
          if defined $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{OCTETSTRING}
          and ref $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{OCTETSTRING} eq
          'ARRAY'
          and
          scalar @{ $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{OCTETSTRING} }
          == 2;

        $stringType = 'SINGLESEQUENCEOF'
          if defined $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{BITSTRING}
          and ref $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{BITSTRING} eq
          'ARRAY'
          and
          scalar @{ $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{BITSTRING} } ==
          1;

        $stringType = 'SINGLESEQUENCEOFOCTETSTRING'
          if defined $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{OCTETSTRING}
          and ref $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{OCTETSTRING} eq
          'ARRAY'
          and
          scalar @{ $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{OCTETSTRING} }
          == 1;

        my $String = 'BITSTRING';
        $String = 'OCTETSTRING'
          if defined $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{OCTETSTRING};

        @{ $ASN1{ $struct->[0] } }{qw/DONE CODE_DONE/} = (0) x 2
          if not defined $ASN1{ $struct->[0] }{DONE}
          and Composer::STRING::compose(
            'BITSTRING',
            $struct->[0],
            '',
            $Files,
            $typePrefix,
            $stringType,
            $ASN1{ $struct->[0] }{ $struct->[1] }{TYPE}{$String},
            $ASN1{ $struct->[0] }
          ) == TRUE;
      }
    else
      {
        $stringType = 'RANGE'
          if ref $ASN1{ $struct->[0] }{ $struct->[1] } eq 'ARRAY'
          and defined $ASN1{ $struct->[0] }{ $struct->[1] }[1];
        $stringType = 'SINGLE'
          if ref $ASN1{ $struct->[0] }{ $struct->[1] } eq 'ARRAY'
          and not defined $ASN1{ $struct->[0] }{ $struct->[1] }[1];

        $stringType .= 'OCTETSTRING' if $struct->[1] eq 'OCTETSTRING';

        @{ $ASN1{ $struct->[0] } }{qw/DONE CODE_DONE/} = (1) x 2
          if not defined $ASN1{ $struct->[0] }{DONE}
          and Composer::STRING::compose(
            'BITSTRING', $struct->[0], '', $Files, $typePrefix, $stringType,
            $ASN1{ $struct->[0] }{ $struct->[1] },
            $ASN1{ $struct->[0] }
          ) == TRUE;

        if ( defined $ASN1{ $struct->[0] }{DONE}
            and $ASN1{ $struct->[0] }{DONE} == 1 )
          {
            my @map = GetGivenName( $struct->[0] );
            $ASN1{ $struct->[0] }{DONE} = 2
              if scalar @map >= 2
              or ( scalar @map == 1 and defined $map[0]->{ELEMENT} );
          }
      }
  }

sub _proceedNestedSTRING
  {
    my $struct      = shift;
    my $struct_name = shift;
    my $Files       = shift;
    my $typePrefix  = shift;
    my $String      = shift;

    return if defined $struct->{'NOTSUPPORTED'};
    return if not defined $struct->{_ORDER_};

    foreach my $elem ( @{ $struct->{_ORDER_} } )
      {
        next if defined $struct->{$elem}{NOTSUPPORTED};

        @{ $struct->{$elem} }{qw/DONE CODE_DONE/} = (1) x 2
          if (  not defined $struct->{$elem}{DONE}
            and defined $struct->{$elem}{BITSTRING}
            and defined $struct->{$elem}{BITSTRING}{KIND}
            and $struct->{$elem}{BITSTRING}{KIND} eq 'SIZE_MAGNITUDE'
            and defined $struct->{$elem}{BITSTRING}{VALUE}
            and ref $struct->{$elem}{BITSTRING}{VALUE} eq 'ARRAY'
            and $struct->{$elem}{BITSTRING}{VALUE}[0] > 32 )
          and
          Composer::STRING::compose( 'BITSTRING', $struct_name, $elem, $Files,
            $typePrefix, 'REGULAR', $struct->{$elem}{BITSTRING},
            $struct->{$elem} ) == TRUE;

        @{ $struct->{$elem} }{qw/DONE CODE_DONE/} = (1) x 2
          if (  not defined $struct->{$elem}{DONE}
            and defined $struct->{$elem}{VALUE}
            and ref $struct->{$elem}{VALUE} eq 'ARRAY'
            and ( $struct->{$elem}{VALUE}->[0] eq $String ) )
          and
          Composer::STRING::compose( 'BITSTRING', $struct_name, $elem, $Files,
            $typePrefix, 'REGULAR', $struct->{$elem}, $struct->{$elem} ) ==
          TRUE;

        @{ $struct->{$elem} }{qw/DONE CODE_DONE/} = (1) x 2
          if $String eq 'OCTETSTRING'
          and not defined $struct->{$elem}{DONE}
          and (
            (
                    defined $struct->{$elem}{OCTETSTRING}
                and defined $struct->{$elem}{OCTETSTRING}{VALUE}
                and ref $struct->{$elem}{OCTETSTRING}{VALUE} eq 'ARRAY'
            )
            and Composer::STRING::compose(
                'BITSTRING',                          $struct_name,
                $elem,                                $Files,
                $typePrefix,                          'RANGEOCTETSTRING',
                $struct->{$elem}{OCTETSTRING}{VALUE}, $struct->{$elem}
            ) == TRUE
          );

        @{ $struct->{$elem} }{qw/DONE CODE_DONE/} = (1) x 2
          if ref $struct->{$elem} eq 'HASH'
          and not defined $struct->{$elem}{DONE}
          and defined $struct->{$elem}{SEQUENCE}
          and defined $struct->{$elem}{SEQUENCE}{KIND}
          and $struct->{$elem}{SEQUENCE}{KIND} eq 'EMPTY'
          and Composer::STRING::compose(
            'BITSTRING', $struct_name, $elem, $Files, $typePrefix, 'SEQUENCE',
            $struct->{$elem}{SEQUENCE},
            $struct->{$elem}{SEQUENCE}
          ) == TRUE;
      }

    foreach my $elem ( @{ $struct->{_ORDER_} } )
      {
        next unless ref $struct->{$elem} eq 'HASH';
        next if defined $struct->{$elem}{NOTSUPPORTED};

        if ( defined $struct->{$elem}{CHOICE} )
          {
            _proceedNestedSTRING( $struct->{$elem}{CHOICE},
                "$struct_name-$elem", $Files, $typePrefix, $String );
          }
        elsif ( defined $struct->{$elem}{SEQUENCE} )
          {
            _proceedNestedSTRING( $struct->{$elem}{SEQUENCE},
                "$struct_name-$elem", $Files, $typePrefix, $String )
              if not defined $struct->{$elem}{SEQUENCE}{KIND}
              or ( defined $struct->{$elem}{SEQUENCE}{KIND}
                and $struct->{$elem}{SEQUENCE}{KIND} ne 'EMPTY' );
          }
      }
  }

#-----------------------------------------------------------------------
1;
