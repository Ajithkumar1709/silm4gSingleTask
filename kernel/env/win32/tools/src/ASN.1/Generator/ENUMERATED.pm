#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# ASN.1 Compiler Service Library
#
# Proceed ENUMERATED types
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         18-Aug-2009     KS         1. Initial Version
#-----------------------------------------------------------------------
package Generator::ENUMERATED;



use strict;
use warnings;

use Globals;
use Commons qw/:globals :common_func :filecodes/;

use Composer::ENUMERATED;

#------------------ Application-wide Variables ---------------
our $DEBUG;
our %ASN1;
our %ASN1Index;
our %MAP;

# -------------------- Main i/f functions --------------------
sub lookin
  {
    my $Files      = shift;
    my $struct     = shift;
    my $structType = shift;
    my $enumPrefix = shift;

    return if defined $ASN1{ $struct->[0] }{NOTSUPPORTED};
    return if defined $ASN1{ $struct->[0] }{$structType}{NOTSUPPORTED};

    if ( defined $ASN1{ $struct->[0] }{UPGRADED} )
      {
        return
          if defined $ASN1{ $struct->[0] }{UPGRADE}
          and defined $ASN1{ $struct->[0] }{UPGRADE}[0]
          and $ASN1{ $struct->[0] }{UPGRADE}[0]{TYPE} eq 'GLOBAL';
      }

    my $root = SkipStruct( $ASN1{ $struct->[0] } );

    if ( defined $root->{TYPE} and defined $root->{TYPE}{ENUMERATED} )
      {
        @{ $root->{TYPE}{ENUMERATED} }{qw/DONE CODE_DONE/} = (1) x 2
          if Composer::ENUMERATED::compose( $struct, '',
            $root->{TYPE}{ENUMERATED}{ENUM},
            $Files, $enumPrefix, $ASN1{ $struct->[0] } ) == TRUE;
        return;
      }

    return if not defined $root->{_ORDER_};

    foreach my $elem ( @{ $root->{_ORDER_} } )
      {
        next if defined $root->{$elem}{NOTSUPPORTED};

        my $struct_name = $struct->[0];

        if ( defined $root->{$elem}{CHOICE} )
          {
            _proceedNestedENUMERATED(
                $root->{$elem}{CHOICE},
                $struct_name . '-' . $elem,
                $Files, $enumPrefix
            );
          }
        elsif ( defined $root->{$elem}{SEQUENCE} )
          {
            _proceedNestedENUMERATED(
                $root->{$elem}{SEQUENCE},
                $struct_name . '-' . $elem,
                $Files, $enumPrefix
            );
          }
        elsif ( defined $root->{$elem}{ENUMERATED} )
          {
            @{ $root->{$elem} }{qw/DONE CODE_DONE/} = (1) x 2
              if Composer::ENUMERATED::compose( $struct, $elem, $structType,
                $Files, $enumPrefix, $root->{$elem} ) == TRUE;
          }
      }
  }

sub pureENUMERATED
  {
    my $Files      = shift;
    my $struct     = shift;
    my $enumPrefix = shift;

    return if defined $ASN1{ $struct->[0] }{NOTSUPPORTED};

    my $values = [];
    $values = $ASN1{ $struct->[0] }{ENUMERATED}{ENUM}
      if defined $ASN1{ $struct->[0] }{ENUMERATED}{ENUM};

    @{ $ASN1{ $struct->[0] } }{qw/DONE CODE_DONE/} = (1) x 2
      if Composer::ENUMERATED::compose( $struct, '', $values, $Files,
        $enumPrefix, $ASN1{ $struct->[0] } ) == TRUE;
  }

sub _proceedNestedENUMERATED
  {
    my $struct      = shift;
    my $struct_name = shift;
    my $Files       = shift;
    my $enumPrefix  = shift;

    return if defined $struct->{'NOTSUPPORTED'};
    return if not defined $struct->{_ORDER_};

    foreach my $elem ( @{ $struct->{_ORDER_} } )
      {
        next if defined $struct->{$elem}{NOTSUPPORTED};

        if ( defined $struct->{$elem}{CHOICE} )
          {
            _proceedNestedENUMERATED(
                $struct->{$elem}{CHOICE},
                $struct_name . '-' . $elem,
                $Files, $enumPrefix
            );
          }
        elsif ( defined $struct->{$elem}{SEQUENCE} )
          {
            _proceedNestedENUMERATED(
                $struct->{$elem}{SEQUENCE},
                $struct_name . '-' . $elem,
                $Files, $enumPrefix
            );
          }
        elsif ( defined $struct->{$elem}{ENUMERATED} )
          {
            my $values;
            $values = $struct->{$elem}{ENUMERATED}{ENUM}
              if defined $struct->{$elem}{ENUMERATED}{ENUM};
            $values = $struct->{$elem}{ENUMERATED}{VALUE}
              if defined $struct->{$elem}{ENUMERATED}{VALUE};

            @{ $struct->{$elem} }{qw/DONE CODE_DONE/} = (1) x 2
              if Composer::ENUMERATED::compose( $struct_name, $elem, $values,
                $Files, $enumPrefix, $struct->{$elem} ) == TRUE;
          }
      }
  }

#-----------------------------------------------------------------------
1;
