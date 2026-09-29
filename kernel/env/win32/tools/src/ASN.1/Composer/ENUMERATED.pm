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
package Composer::ENUMERATED;



use strict;
use warnings;

use Globals;
use Commons qw/:globals :common_func :filecodes/;

#------------------ Application-wide Variables ---------------
our $DEBUG;
our %ASN1;
our %ASN1Index;
our %MAP;

#---------------------- Local Globals --------------------------------
my %COMPOSE = ();
my @COMPOSE = ();

# -------------------- Main i/f functions --------------------
sub compose
  {
    my $name = '';
    $name = $_[0]->[0] if ref $_[0];
    $name = $_[0]      if not ref $_[0];
    my $elem = '_NONE_';
    $elem = $_[1] if $_[1];

    if ( defined $COMPOSE{$name} and defined $COMPOSE{$name}{$elem} )
      {
        my $index = 1;
        while ( defined $COMPOSE{ $name . '_' . $index }
            and defined $COMPOSE{ $name . '_' . $index }{$elem} )
          {
            $index++;
          }
        push @{ $COMPOSE{ $name . '_' . $index }{$elem} }, ( @_, $index + 1 );
        $COMPOSE{$name}{$elem}[-1] = 1;
        push @COMPOSE, [ $name . '_' . $index, $elem ];
      }
    else
      {
        push @{ $COMPOSE{$name}{$elem} }, ( @_, 0 );
        push @COMPOSE, [ $name, $elem ];
      }

    return _checkCompose(@_);
  }

sub flush
  {
    foreach my $comp (@COMPOSE)
      {
        _compose( @{ $COMPOSE{ $comp->[0] }{ $comp->[1] } } );
      }
  }

sub _compose
  {
    my $struct     = shift;
    my $elem       = shift;
    my $type       = shift;
    my $Files      = shift;
    my $enumPrefix = shift;
    my $source     = shift;
    my $index      = shift;

    my %Yield = ();

    my $composed =
      _composeMainHeader( $struct, $elem, $type, $Files->[MAIN][HANDLE],
        $enumPrefix, $source, $index, \%Yield );

    if ( $composed == TRUE )
      {
        _composeEncode(
            $Files->[ENCE][HANDLE],
            \%Yield,
            (
                defined $source->{DECODE_ONLY}
                  or (  defined $source->{ENUMERATED}
                    and defined $source->{ENUMERATED}{DECODE_ONLY} )
              ) ? TRUE: FALSE
        );
        _composeDecode(
            $Files->[DECE][HANDLE],
            \%Yield,
            (
                defined $source->{ENCODE_ONLY}
                  or (  defined $source->{ENUMERATED}
                    and defined $source->{ENUMERATED}{ENCODE_ONLY} )
              ) ? TRUE: FALSE
        );
      }

    return $composed;
  }

sub _checkCompose
  {
    my $struct = shift;
    my $elem   = shift;
    my $type   = shift;

    return FALSE
      if not ref $type
      and defined $ASN1{ $struct->[0] }{$type}{$elem}{NOTSUPPORTED};

    return TRUE;
  }

sub _composeMainHeader
  {
    my $struct     = shift;
    my $elem       = shift;
    my $type       = shift;
    my $file       = shift;
    my $enumPrefix = shift;
    my $source     = shift;
    my $index      = shift;
    my $yield      = shift;

    return FALSE
      if not ref $type
      and defined $ASN1{ $struct->[0] }{$type}{$elem}{NOTSUPPORTED};

    my $struct_name = '';
    my $suffix      = '';
    if ( ref $struct )
      {
        $struct_name = $struct->[0];
        $struct_name =~ s/-/_/g;
        $suffix = '_seq' if $struct->[1] eq 'SEQUENCEOF' and not $elem;

      }
    else
      {
        $struct_name = $struct;
      }

    my $elem_name = $elem;
    $elem_name =~ s/-/_/g;
    my $spacer = '_';
    $spacer = '' if not $elem_name;

    my $full_name      = $struct_name . $spacer . $elem_name;
    my $real_full_name = $struct;
    $real_full_name .= '-' . $elem if $elem;

    my $map = Commons::GetGivenName($real_full_name);

    if (    $map
        and ref $map eq 'HASH'
        and defined $map->{FACTUAL}
        and $map->{FACTUAL} )
      {
        $full_name      = $map->{FACTUAL};
        $real_full_name = $map->{FACTUAL};
      }
    elsif ( defined $MAP{TYPE}{$full_name}
        and defined $MAP{TYPE}{$full_name}{FACTUAL} )
      {
        $full_name      = $MAP{TYPE}{$full_name}{FACTUAL};
        $real_full_name = $full_name;
        if ( $suffix and $full_name !~ /$suffix$/ )
          {
            $full_name      .= $suffix;
            $real_full_name .= $suffix;
          }
      }
    else
      {
        $full_name .= $suffix if $suffix and $full_name !~ /$suffix$/;
        $real_full_name = $full_name;
        $real_full_name =
          $struct_name . "$spacer$elem_name" . $suffix . '_' . $index
          if $index;
      }

    my $yieldKey = "$enumPrefix$real_full_name";

    Composer::Commons::WriteHeader( $file, $map ? $map : $MAP{TYPE}{$full_name},
        $enumPrefix, $real_full_name );

    print $file "typedef enum $enumPrefix$real_full_name" . "Tag\n";
    print $file "{\n";

    my $values;
    if ( ref $type )
      {
        $values = $type;
      }
    elsif ( defined $ASN1{ $struct->[0] }{$type}{$elem}{ENUMERATED}
        and defined $ASN1{ $struct->[0] }{$type}{$elem}{ENUMERATED}{ENUM} )
      {
        $values = $ASN1{ $struct->[0] }{$type}{$elem}{ENUMERATED}{ENUM};
      }
    elsif ( defined $ASN1{ $struct->[0] }{$type}{$elem}{ENUMERATED}
        and defined
        defined $ASN1{ $struct->[0] }{$type}{$elem}{ENUMERATED}{VALUE} )
      {
        $values = $ASN1{ $struct->[0] }{$type}{$elem}{ENUMERATED}{VALUE};
      }
    elsif ( ref $source eq 'HASH'
        and defined $source->{ENUMERATED}
        and defined $source->{ENUMERATED}{ENUM} )
      {
        $values = $source->{ENUMERATED}{ENUM};
      }
    elsif ( ref $source eq 'HASH'
        and defined $source->{ENUMERATED}
        and defined $source->{ENUMERATED}{VALUE} )
      {
        $values = $source->{ENUMERATED}{VALUE};
      }

    my $first = TRUE;
    foreach my $enum ( @{$values} )
      {
        $enum =~ s/-/_/g;

        print $file ",\n" if $first == FALSE;
        $first = FALSE if $first == TRUE;

        my $final_name = "$enumPrefix$real_full_name" . "_$enum";
        if ( defined $MAP{ENUM}{$real_full_name}{$enum}
            and $MAP{ENUM}{$real_full_name}{$enum}->[0] )
          {
            $final_name = $enumPrefix . $MAP{ENUM}{$real_full_name}{$enum}->[0];
            $final_name .= " = $MAP{ENUM}{$real_full_name}{$enum}->[1]"
              if defined $MAP{ENUM}{$real_full_name}{$enum}->[1]
              and $MAP{ENUM}{$real_full_name}{$enum}->[1] =~ /\w+/
              and $MAP{ENUM}{$real_full_name}{$enum}->[0] ne
              $MAP{ENUM}{$real_full_name}{$enum}->[1];
          }
        print $file "    $final_name";
        push @{ $yield->{$yieldKey} }, $final_name;
      }
    print $file "\n}\n";
    print $file "$enumPrefix$real_full_name;\n\n\n";

    $source->{LABEL} = $enumPrefix . $real_full_name;
    return TRUE;
  }

sub _composeEncode
  {
    my $file         = shift;
    my $enumDisposal = shift;
    my $decode_only  = shift;

    my $enumName = ( keys %$enumDisposal )[0];

    my $offset    = ' ' x ( 76 - length("/*  PerEnc_$enumName") );
    my $enumTotal = $#{ $enumDisposal->{$enumName} };

    my $decodeonlyAddition = '';
    $decodeonlyAddition = <<DECODE_ONLY if $decode_only;
#if defined (ENABLE_ALL_ENCODE_FUNCTIONS)
DECODE_ONLY

    print $file <<ENUM_ENC_HEADER;
$decodeonlyAddition
/****************************************************************************/
/*  PerEnc_$enumName$offset*/
/*                                                                          */
/****************************************************************************/

void PerEnc_$enumName (PerBuffer *perBuffer, $enumName *value)
{
    Int8 result;

    switch (*value)
    {
ENUM_ENC_HEADER

    my $counter = 0;
    foreach my $value ( @{ $enumDisposal->{$enumName} } )
      {
        $value =~ /^(\w+)/;
        my $_val = $1;
        print $file <<ENUM_ENC_BODY;
        case $_val:
            result = $counter;
            break;
ENUM_ENC_BODY
        $counter++;
      }

    $decodeonlyAddition = '';
    $decodeonlyAddition = '#endif' if $decode_only;

    print $file <<ENUM_ENC_TAIL
        default:
            DevParam (*value, 0, 0);
            break;
    }
    PerEncEnum (perBuffer, &result, $enumTotal);
}
$decodeonlyAddition
ENUM_ENC_TAIL

  }

sub _composeDecode
  {
    my $file         = shift;
    my $enumDisposal = shift;
    my $encode_only  = shift;

    my $enumName  = ( keys %$enumDisposal )[0];
    my $offset    = ' ' x ( 76 - length("/*  PerDec_$enumName") );
    my $enumTotal = $#{ $enumDisposal->{$enumName} };

    my $isAddition = scalar grep /spare/, @{ $enumDisposal->{$enumName} };
    my $spareAddition = ')';
    $spareAddition = ", Boolean defaultPresent, $enumName defaultValue)"
      if $isAddition;

    my $encodeonlyAddition = '';
    $encodeonlyAddition = <<ENCODE_ONLY if $encode_only;
#if defined (ENABLE_ALL_DECODE_FUNCTIONS)
ENCODE_ONLY

    print $file <<ENUM_DEC_HEADER;
$encodeonlyAddition
/****************************************************************************/
/*  PerDec_$enumName$offset*/
/*                                                                          */
/****************************************************************************/

PerError PerDec_$enumName (PerBuffer *perBuffer, $enumName *value$spareAddition
{
    PerError error;
    Int8 result;
    error = PerDecEnum (perBuffer, &result, $enumTotal);
    if (error == PER_NO_ERROR)
    {
        switch (result)
        {
ENUM_DEC_HEADER

    my $counter = 0;
    foreach my $value ( @{ $enumDisposal->{$enumName} } )
      {
        $value =~ /^(\w+)/;
        my $_val = $1;
        if ( $_val =~ /spare/ )
          {
            print $file <<ENUM_ENC_BODY;
            case $counter:
                if (defaultPresent)
                {
                    perBuffer->spareValueSubstituted = TRUE;
                    *value = defaultValue;
                }
                else
                {
                    perBuffer->decodedSpareValue = TRUE;
                    *value = $_val;
                }
                break;
ENUM_ENC_BODY
          }
        else
          {
            print $file <<ENUM_DEC_BODY;
            case $counter:
                *value = $_val;
                break;
ENUM_DEC_BODY
          }
        $counter++;
      }

    $encodeonlyAddition = '';
    $encodeonlyAddition = '#endif' if $encode_only;

    print $file <<ENUM_DEC_TAIL
            default:
                error = PER_ERROR_INVALID_ENUM;
                break;
        }
    }
    return (error);
}
$encodeonlyAddition
ENUM_DEC_TAIL

  }

#-------------------------------------------------------------
1;
