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
package Composer::STRING;



use strict;
use warnings;

use Globals;
use Commons qw/:globals :common_func :filecodes/;

#------------------ Application-wide Variables ---------------
our $DEBUG;
our %ASN1;
our %ASN1Index;
our %MAP;

# -------------------- Main i/f functions --------------------
sub compose
  {
    my $kind = shift;

    return _composeBITSTRING(@_)   if $kind eq 'BITSTRING';
    return _composeOCTETSTRING(@_) if $kind eq 'OCTETSTRING';
  }

sub _composeBITSTRING
  {
    my $struct_name = shift;
    my $elem        = shift;
    my $Files       = shift;
    my $typePrefix  = shift;
    my $stringType  = shift;
    my $data        = shift;
    my $source      = shift;

    my %Yield = ();

    my $composed =
      _BS_composeMainHeader( $struct_name, $elem, $Files->[MAIN][HANDLE],
        $typePrefix, $stringType, $data, $source, \%Yield );

    if ( $composed == TRUE )
      {
        _BS_composeEncode(
              $stringType =~ /OCTETSTRING/
            ? $Files->[ENCO][HANDLE]
            : $Files->[ENCB][HANDLE],
            \%Yield,
            (
                defined $source->{DECODE_ONLY}
                  or (  defined $source->{BITSTRING}
                    and ref $source->{BITSTRING} eq 'HASH'
                    and defined $source->{BITSTRING}{DECODE_ONLY} )
                  or (  defined $source->{SEQUENCE}
                    and defined $source->{SEQUENCE}{DECODE_ONLY} )
              ) ? TRUE: FALSE
        );
        _BS_composeDecode(
              $stringType =~ /OCTETSTRING/
            ? $Files->[DECO][HANDLE]
            : $Files->[DECB][HANDLE],
            \%Yield,
            (
                defined $source->{ENCODE_ONLY}
                  or (  defined $source->{BITSTRING}
                    and ref $source->{BITSTRING} eq 'HASH'
                    and defined $source->{BITSTRING}{ENCODE_ONLY} )
                  or (  defined $source->{SEQUENCE}
                    and defined $source->{SEQUENCE}{ENCODE_ONLY} )
              ) ? TRUE: FALSE
        );
      }

    return $composed;
  }

sub _composeOCTETSTRING
  {
    my $Files      = shift;
    my $struct     = shift;
    my $name       = shift;
    my $typePrefix = shift;
    my $kind       = shift;
    my $curr_label = shift;

    my %Yield = ();

    my $composed = _OS_composeMainHeader( $Files->[MAIN][HANDLE],
        $struct, $name, $typePrefix, $kind, $curr_label, \%Yield );

    if ($composed)
      {
        _OS_composeEncode( \%Yield, );
        _OS_composeDecode( \%Yield, );
      }

    return $composed;
  }

sub _OS_composeMainHeader
  {
    my $File       = shift;
    my $struct     = shift;
    my $name       = shift;
    my $typePrefix = shift;
    my $kind       = shift;
    my $curr_label = shift;

    my $Yeald = shift;

    my @map = GetGivenName($name);
    my $map;

    if ($curr_label)
      {
        my $orig_curr_label = $curr_label;
        $orig_curr_label =~ s/^$typePrefix//;

        foreach my $m (@map)
          {
            $map = $m if $m->{FACTUAL} ne $orig_curr_label;
          }
      }
    $map = $map[0] if not $map;

    my $struct_name = undef;
    $struct_name = $map->{FACTUAL} if defined $map->{FACTUAL};

    Composer::Commons::WriteHeader( $File, $map, $typePrefix, $struct_name );

    if ( $kind eq 'STATIC' )
      {
        my $typedef_offset = ' ' x ( 59 - length("typedef $curr_label") );

        print $File <<STATIC_OCTETSTRING;
typedef $curr_label$typedef_offset$typePrefix$struct_name;


STATIC_OCTETSTRING
      }

    return "$typePrefix$struct_name";
  }

sub _BS_composeMainHeader
  {
    my $struct_name = shift;
    my $elem        = shift;
    my $Main        = shift;
    my $typePrefix  = shift;
    my $stringType  = shift;
    my $data        = shift;
    my $source      = shift;
    my $yield       = shift;

    return FALSE
      if ref $data eq 'HASH'
      and defined $data->{KIND}
      and $data->{KIND} eq 'SIZE_MAGNITUDE'
      and $stringType !~ /OCTETSTRING/
      and scalar @{ $data->{VALUE} } == 1
      and $data->{VALUE}[0] <= 32;

    return FALSE
      if ref $data eq 'HASH'
      and defined $data->{SIZE}
      and defined $data->{VALUE}
      and ref $data->{VALUE} eq 'ARRAY'
      and $data->{VALUE}[0] =~ /\D/;

    if (    ref $data eq 'HASH'
        and defined $data->{KIND}
        and $data->{KIND} eq 'CONTAINING' )
      {
        return FALSE;
      }

    my $map_name = $struct_name;
    $map_name .= "-$elem" if $elem;    # $stringType eq 'REGULAR';
    my $map_record = GetGivenName($map_name);

    my $full_name = '';

    if ( not $map_record )
      {
        my @reminder = ();
        my @map_name = split /-/, $struct_name;
        push @reminder, shift @map_name;

        while (@map_name)
          {
            if ( $reminder[-1] !~ /^\d+$/ and $map_name[0] eq $reminder[-1] )
              {
                push @reminder, 1;
                shift @map_name;
              }
            elsif ( $reminder[-1] =~ /^\d+$/ and $map_name[0] eq $reminder[-2] )
              {
                $reminder[-1]++;
                shift @map_name;
              }
            else
              {
                push @reminder, shift @map_name;
              }
          }

        $full_name = join( "_", @reminder );
        $full_name .= '_' . $elem if $elem;
        $full_name =~ s/-/_/g;
      }

    my $complement_name = TRUE;
    if ( not $full_name )
      {
        if ( defined $map_record and defined $map_record->{ELEMENT} )
          {
            $full_name       = $map_record->{ELEMENT};
            $complement_name = FALSE;
          }
        elsif ( defined $map_record and defined $map_record->{FACTUAL} )
          {
            $full_name       = $map_record->{FACTUAL};
            $complement_name = FALSE;
          }
        else
          {
            $full_name = $struct_name;
            $full_name .= "-$elem" if $elem;
            $full_name =~ s/-/_/g;
          }
      }

    if ($complement_name)
      {
        $full_name .= "_seq" if $stringType =~ /SEQUENCEOF/;
        $full_name .= "_str"
          unless $full_name =~ /_str$/
          or $full_name     =~ /_aeStr$/;
      }

    my $Scope;
    if ( $stringType =~ /(RANGE|SINGLE)/ )
      {
        $Scope = $data if ref $data eq 'ARRAY';
        $Scope = $data->{VALUE}
          if ref $data eq 'HASH'
          and defined $data->{VALUE}
          and ref $data->{VALUE} eq 'ARRAY';
      }
    elsif ( ref $data eq 'HASH'
        and defined $data->{KIND}
        and $data->{KIND} eq 'SIZE_MAGNITUDE' )
      {
        $Scope      = $data->{VALUE};
        $stringType = 'SIZE_MAGNITUDE';
      }
    elsif ( ref $data eq 'HASH'
        and defined $data->{KIND}
        and $data->{KIND} eq 'SIZE_INTERVAL' )
      {
        $Scope      = $data->{VALUE};
        $stringType = 'SIZE_INTERVAL';
      }

    my $offset = ' ';
    $offset = ' ' x ( 76 - ( length("$typePrefix$full_name") + 4 ) )
      if 76 - ( length("$typePrefix$full_name") + 4 ) > 0;

    my $comment = "/* OCTET STRING */";
    $comment = "/* PADDING */" if $stringType eq 'SEQUENCE';
    if ( $stringType =~ /RANGE/ )
      {
        if ( $stringType =~ /OCTETSTRING/ )
          {
            my $add = '';
            $add = "..$Scope->[1]" if defined $Scope->[1];
            $comment = "/* OCTET STRING ($Scope->[0]$add) */";
          }
        else
          {
            my $add = '';
            $add = "..$Scope->[1]" if defined $Scope->[1];
            $comment = "/* BIT STRING ($Scope->[0]$add) */";
          }
      }
    if ( $stringType =~ /SINGLE/ )
      {
        if ( $stringType !~ /OCTETSTRING/ )
          {
            if ( $Scope->[0] =~ /^\d+$/ and $Scope->[0] > 32 )
              {
                $comment    = "/* BIT STRING ($Scope->[0]) */";
                $stringType = "SINGLE_LARGE";
              }
            else
              {
                my $upperBound =
                  $Scope->[0] =~ /^\d+$/ ? 2**$Scope->[0] - 1 : $Scope->[0];
                $comment = "/* 0 to $upperBound */";
              }
          }
        else
          {
            $comment = "/* OCTET STRING ($Scope->[0]) */";
          }
      }
    if ( $stringType eq 'SIZE_MAGNITUDE' )
      {
        $comment = "/* BIT STRING ($Scope->[0]) */";
      }
    if ( $stringType eq 'SIZE_INTERVAL' )
      {
        my $add = '';
        $add = "..$Scope->[1]" if defined $Scope->[1];
        $comment = "/* BIT STRING ($Scope->[0]$add) */";
      }

    my $intSize = '16';
    if (   ( $stringType =~ /SINGLE/ and $Scope->[0] =~ /^\d+$/ )
        or $stringType eq 'SIZE_MAGNITUDE'
        or $stringType eq 'SIZE_INTERVAL' )
      {
        $intSize = '8' if $Scope->[0] <= 255;
      }

    my $offset1 = '';
    $offset1 = ' ' x ( 59 - 15 - length($comment) ) if $stringType eq 'SINGLE';

    my $asterisk = '*';
    $asterisk = ''
      if $stringType =~
      /(RANGE|SIZE_MAGNITUDE|SIZE_INTERVAL|SINGLE_LARGE|SINGLEOCTETSTRING)/;

    my $finale = ';';
    $finale = " [($Scope->[1] + 7)/8];"
      if $stringType =~ /RANGE/ and defined $Scope->[1];

    $finale = " [($Scope->[0] + 7)/8];"
      if $stringType =~ /RANGE/ and not defined $Scope->[1];

    $finale = " [($Scope->[0] + 7)/8];"
      if $stringType eq 'SIZE_MAGNITUDE'
      or $stringType eq 'SINGLE_LARGE';

    $finale = " [($Scope->[1] + 7)/8];"
      if $stringType eq 'SIZE_INTERVAL' and defined $Scope->[1];

    $finale = " [($Scope->[0] + 7)/8];"
      if $stringType eq 'SIZE_INTERVAL' and not defined $Scope->[1];

    $finale = " [$Scope->[1]];"
      if $stringType =~ /RANGE(SEQUENCEOF)?OCTETSTRING/ and defined $Scope->[1];

    $finale = " [$Scope->[0]];"
      if $stringType =~ /RANGE(SEQUENCEOF)?OCTETSTRING/
      and not defined $Scope->[1];

    $finale = " [$Scope->[0]];"
      if $stringType =~ /SINGLE(SEQUENCEOF)?OCTETSTRING/;

    return FALSE if $stringType eq 'SINGLE';

    @{ $yield->{"$typePrefix$full_name"} } = ($stringType);
    @{ $yield->{"$typePrefix$full_name"} } = ('SIZE_INTERVAL')
      if $stringType eq 'RANGESEQUENCEOF';
    @{ $yield->{"$typePrefix$full_name"} } = ('SIZE_MAGNITUDE')
      if $stringType eq 'SINGLE_LARGE';
    @{ $yield->{"$typePrefix$full_name"} } = ('SIZE_INTERVAL')
      if $stringType eq 'RANGE';

    push @{ $yield->{"$typePrefix$full_name"} },
      @{ $source->{BITSTRING}{VALUE} }
      if $stringType eq 'SIZE_MAGNITUDE'
      or $stringType eq 'SIZE_INTERVAL';

    push @{ $yield->{"$typePrefix$full_name"} },
      @{ $source->{SEQUENCEOF}{TYPE}{BITSTRING} }
      if $stringType eq 'RANGESEQUENCEOF';
    push @{ $yield->{"$typePrefix$full_name"} }, @{ $source->{BITSTRING} }
      if $stringType eq 'SINGLE_LARGE';
    push @{ $yield->{"$typePrefix$full_name"} }, @{ $source->{BITSTRING} }
      if $stringType eq 'RANGE';
    push @{ $yield->{"$typePrefix$full_name"} }, @{ $source->{BITSTRING} }
      if $stringType eq 'RANGE';

    push @{ $yield->{"$typePrefix$full_name"} },
      ref $source->{OCTETSTRING} eq 'HASH'
      ? @{ $source->{OCTETSTRING}{VALUE} }
      : @{ $source->{OCTETSTRING} }
      if $stringType eq 'RANGEOCTETSTRING'
      or $stringType eq 'SINGLEOCTETSTRING';

    if ( $stringType =~ /(SIZE_MAGNITUDE|SINGLE_LARGE|SINGLEOCTETSTRING)/
        or ( $stringType eq 'RANGEOCTETSTRING' and not defined $Scope->[1] ) )
      {
        printf $Main
          <<STRINGSTRUCTTYPE, $typePrefix, $full_name, $asterisk, $finale;
/****************************************************************************/
/*  $typePrefix$full_name$offset*/
/*                                                                          */
/****************************************************************************/

typedef struct %s%sTag
{
    $comment
    Int8 %sdata%s
}
$typePrefix$full_name;


STRINGSTRUCTTYPE
      }
    else
      {
        printf $Main
          <<STRINGSTRUCTTYPE, $typePrefix, $full_name, $asterisk, $finale;
/****************************************************************************/
/*  $typePrefix$full_name$offset*/
/*                                                                          */
/****************************************************************************/

typedef struct %s%sTag
{
    Int16 n; $comment
    Int8 %sdata%s
}
$typePrefix$full_name;


STRINGSTRUCTTYPE
      }

    $source->{LABEL} = $typePrefix . $full_name;
    return TRUE;
  }

sub _BS_composeEncode
  {
    my $file        = shift;
    my $strDisposal = shift;
    my $decode_only = shift;

    my $strName  = ( keys %$strDisposal )[0];
    my $offset   = ' ' x ( 76 - length("/*  PerEnc_$strName") );
    my $strTotal = $#{ $strDisposal->{$strName} };

    my $decodeonlyAddition = '';
    $decodeonlyAddition = <<DECODE_ONLY if $decode_only;
#if defined (ENABLE_ALL_ENCODE_FUNCTIONS)
DECODE_ONLY

    my $func_body =
      '    PerEncUnconstrainedBitString (perBuffer, value->data, value->n);';
    $func_body = <<FUNC_BODY if $strDisposal->{$strName}[0] eq 'SEQUENCE';
    PARAMETER_NOT_USED (perBuffer);
    PARAMETER_NOT_USED (value);
FUNC_BODY
    $func_body =
"    PerEncFixedBitString (perBuffer, value->data, $strDisposal->{$strName}[1]);"
      if $strDisposal->{$strName}[0] eq 'SIZE_MAGNITUDE';
    $func_body =
"    PerEncVariableBitString (perBuffer, value->data, value->n, $strDisposal->{$strName}[1], $strDisposal->{$strName}[2]);"
      if $strDisposal->{$strName}[0] eq 'SIZE_INTERVAL'
      and defined $strDisposal->{$strName}[2];
    $func_body =
"    PerEncVariableBitString (perBuffer, value->data, value->n, $strDisposal->{$strName}[1]);"
      if $strDisposal->{$strName}[0] eq 'SIZE_INTERVAL'
      and not defined $strDisposal->{$strName}[2];
    $func_body =
"    PerEncFixedOctetString (perBuffer, value->data, $strDisposal->{$strName}[1]);"
      if $strDisposal->{$strName}[0] eq 'SINGLEOCTETSTRING';
    $func_body =
"    PerEncVariableOctetString (perBuffer, value->data, value->n, $strDisposal->{$strName}[1], $strDisposal->{$strName}[2]);"
      if $strDisposal->{$strName}[0] eq 'RANGEOCTETSTRING'
      and defined $strDisposal->{$strName}[2];
    $func_body =
"    PerEncVariableOctetString (perBuffer, value->data, value->n, $strDisposal->{$strName}[1]);"
      if $strDisposal->{$strName}[0] eq 'RANGEOCTETSTRING'
      and not defined $strDisposal->{$strName}[2];

    print $file <<STR_ENC_HEADER;
$decodeonlyAddition
/****************************************************************************/
/*  PerEnc_$strName$offset*/
/*                                                                          */
/****************************************************************************/
void PerEnc_$strName (PerBuffer *perBuffer, $strName *value)
{
$func_body
}

STR_ENC_HEADER

    $decodeonlyAddition = '';
    $decodeonlyAddition = '#endif' if $decode_only;

    print $file <<ENUM_ENC_TAIL
$decodeonlyAddition
ENUM_ENC_TAIL

  }

sub _BS_composeDecode
  {
    my $file        = shift;
    my $strDisposal = shift;
    my $encode_only = shift;

    my $strName  = ( keys %$strDisposal )[0];
    my $offset   = ' ' x ( 76 - length("/*  PerDec_$strName") );
    my $strTotal = $#{ $strDisposal->{$strName} };

    my $encodeonlyAddition = '';
    $encodeonlyAddition = <<ENCODE_ONLY if $encode_only;
#if defined (ENABLE_ALL_DECODE_FUNCTIONS)
ENCODE_ONLY

    my $function = 'PerDecUnconstrainedBitString';
    $function = 'PerDecPadding' if $strDisposal->{$strName}[0] eq 'SEQUENCE';
    $function = 'PerDecFixedBitString'
      if $strDisposal->{$strName}[0] eq 'SIZE_MAGNITUDE';
    $function = 'PerDecVariableBitString'
      if $strDisposal->{$strName}[0] eq 'SIZE_INTERVAL';
    $function = 'PerDecVariableOctetString'
      if $strDisposal->{$strName}[0] eq 'RANGEOCTETSTRING';
    $function = 'PerDecFixedOctetString'
      if $strDisposal->{$strName}[0] eq 'SINGLEOCTETSTRING';

    my $lastParams = '&value->data, &value->n';
    $lastParams = "value->data, $strDisposal->{$strName}[1]"
      if $strDisposal->{$strName}[0] eq 'SIZE_MAGNITUDE'
      or $strDisposal->{$strName}[0] eq 'SINGLEOCTETSTRING';

    $lastParams =
"value->data, &value->n, $strDisposal->{$strName}[1], $strDisposal->{$strName}[2]"
      if ( $strDisposal->{$strName}[0] eq 'SIZE_INTERVAL'
        or $strDisposal->{$strName}[0] eq 'RANGEOCTETSTRING' )
      and defined $strDisposal->{$strName}[2];

    $lastParams = "value->data, &value->n, $strDisposal->{$strName}[1]"
      if ( $strDisposal->{$strName}[0] eq 'SIZE_INTERVAL'
        or $strDisposal->{$strName}[0] eq 'RANGEOCTETSTRING' )
      and not defined $strDisposal->{$strName}[2];

    print $file <<STR_DEC_HEADER;
$encodeonlyAddition
/****************************************************************************/
/*  PerDec_$strName$offset*/
/*                                                                          */
/****************************************************************************/

PerError PerDec_$strName (PerBuffer *perBuffer, $strName *value)
{
    return ($function (perBuffer, $lastParams));
}
STR_DEC_HEADER

    $encodeonlyAddition = '';
    $encodeonlyAddition = '#endif' if $encode_only;

    print $file <<STR_DEC_TAIL
$encodeonlyAddition
STR_DEC_TAIL

  }

sub _OS_composeEncode
  {

  }

sub _OS_composeDecode
  {

  }

#-------------------------------------------------------------
1;
