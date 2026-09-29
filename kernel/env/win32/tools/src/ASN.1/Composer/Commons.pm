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
package Composer::Commons;

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
sub WriteHeader
  {
    my ( $File, $map, $typePrefix, $struct_name ) = @_;

    my $offset = '';
    my $ref    = '';

    if ( ref $map eq 'HASH' )
      {
        $ref = $map->{DATA}[4]
          if defined $map->{DATA}[4]
          and $map->{DATA}[4]
          and $map->{DATA}[4] =~ /REF=/;
        $ref = $map->{DATA}[5]
          if defined $map->{DATA}[5]
          and $map->{DATA}[5]
          and $map->{DATA}[5] =~ /REF=/;
        $ref = $map->{DATA}[6]
          if defined $map->{DATA}[6]
          and $map->{DATA}[6]
          and $map->{DATA}[6] =~ /REF=/;
        $ref =~ s/REF=//;
      }

    $offset =
      ' ' x
      ( 76 - ( 4 + length("$typePrefix$struct_name") + 2 + length($ref) ) );

    print $File <<HEADER;
/****************************************************************************/
/*  $typePrefix$struct_name  $ref$offset*/
/*                                                                          */
/****************************************************************************/

HEADER
  }

sub WriteInternalDefines
  {
    my $field_name   = shift;
    my $struct       = shift;
    my $defineSource = shift;

    my $define_name = uc $field_name;

    my $Defines = '';

    $Defines .= "\n";

    foreach my $define (
        sort {
            $a =~ /\((\d+)\)/;
            my $aa = $1;
            $b =~ /\((\d+)\)/;
            my $bb = $1;
            $aa <=> $bb
        } @$defineSource
      )
      {
        $define =~ /([-\w]+)\((\d+)\)/;
        my ( $one, $two ) = ( $1, $2 );
        my $name = uc $one;
        $name =~ s/-/_/g;
        my $size = undef;
        $size = $struct->{BITSTRING}{SIZE}
          if defined $struct->{BITSTRING}
          and defined $struct->{BITSTRING}{SIZE};
        $size = $struct->{SIZE} if defined $struct->{SIZE};
        my $value = 1 << ( $size - 1 - $two );
        $Defines .= sprintf "#define %s_%s      0x%x\n", $define_name, $name,
          $value;
      }

    return $Defines;
  }

sub UpdateLabel
  {
    my $label            = shift;
    my $struct           = shift;
    my $ref_fieldname    = shift;
    my $ref_asterisk     = shift;
    my $counter          = shift;
    my $ref_needdefine   = shift;
    my $ref_definesource = shift;

    return $label if not defined $label;

    if ( $label eq 'DUMMY' )
      {
        $label          = 'Int8';
        $$ref_fieldname = '_dummy' . $counter . '_';
        $$ref_asterisk  = '';
      }
    elsif ( $label eq 'Boolean' )
      {
        $$ref_asterisk = '';
      }
    elsif ( $label eq 'NOTSUPPORTED' )
      {
        $label          = 'Int8';
        $$ref_fieldname = '_notSupported' . $counter . '_';
        $$ref_asterisk  = '';
      }
    elsif ( $label eq 'BITSTRING' )
      {
        $label = 'Int16  ';
        my ( $lowerBound, $upperBound ) = ( 0, 0 );
        if ( defined $struct->{BITSTRING}{KIND}
            and $struct->{BITSTRING}{KIND} eq 'SIZE_MAGNITUDE' )
          {
            $lowerBound = 0;
            $upperBound = 2**$struct->{BITSTRING}{VALUE}[0] - 1;
          }
        elsif ( defined $struct->{BITSTRING}{SIZE} )
          {
            $lowerBound        = 0;
            $upperBound        = 2**$struct->{BITSTRING}{SIZE} - 1;
            $$ref_needdefine   = TRUE;
            $$ref_definesource = $struct->{BITSTRING}{VALUE};
          }

        $label = 'Int32  ' if $upperBound < 4294967296;
        $label = 'Int16  ' if $upperBound < 65536;
        $label = 'Int8  '  if $upperBound < 256;
        $label .= "/* $lowerBound to $upperBound */";
        $$ref_asterisk = '';
      }
    elsif ( $label eq 'INTEGER' )
      {
        $label = 'Int16  ';
        my ( $lowerBound, $upperBound ) = ( 0, 0 );
        if ( $struct->{INTEGER}{KIND} eq 'INTERVAL' )
          {
            $lowerBound = $struct->{INTEGER}{VALUE}[0];
            $upperBound = $struct->{INTEGER}{VALUE}[1];
          }
        if ( $upperBound =~ /^-?\d+$/ )
          {
            $label = 'Int32  '
              if ( $lowerBound >= 0 and $upperBound < 4294967296 )
              or (
                $lowerBound < 0
                and abs(
                    sign($upperBound) * abs($upperBound) + (-1) *
                      sign($lowerBound) * abs($lowerBound)
                ) < 4294967295
              );
            $label = 'Int16  '
              if ( $lowerBound >= 0 and $upperBound < 65536 )
              or (
                $lowerBound < 0
                and abs(
                    sign($upperBound) * abs($upperBound) + (-1) *
                      sign($lowerBound) * abs($lowerBound)
                ) < 65535
              );
            $label = 'Int8  '
              if ( $lowerBound >= 0 and $upperBound < 256 )
              or (
                $lowerBound < 0
                and abs(
                    sign($upperBound) * abs($upperBound) + (-1) *
                      sign($lowerBound) * abs($lowerBound)
                ) < 255
              );
            $label = 'Signed' . $label if $lowerBound < 0;
          }
        else
          {
            $label = 'Int32  '
              if defined $ASN1{$upperBound}
              and defined $ASN1{$upperBound}{INTEGER}
              and $ASN1{$upperBound}{INTEGER} < 4294967296;
            $label = 'Int16  '
              if defined $ASN1{$upperBound}
              and defined $ASN1{$upperBound}{INTEGER}
              and $ASN1{$upperBound}{INTEGER} < 65536;
            $label = 'Int8  '
              if defined $ASN1{$upperBound}
              and defined $ASN1{$upperBound}{INTEGER}
              and $ASN1{$upperBound}{INTEGER} < 256;
          }
        $label .= "/* $lowerBound to $upperBound */";
        $$ref_asterisk = '';
      }
    return $label;
  }

sub GetField
  {
    my $struct     = shift;
    my $field      = shift;
    my $par_struct = shift;
    my $orig_field = shift;
    my $kind       = shift;
    my $sp         = shift;

    return 'NOTSUPPORTED'
      if $field ne 'OPTIONAL'
      and ref $struct eq 'HASH'
      and (
        defined $struct->{NOTSUPPORTED}
        or (    defined $struct->{SEQUENCE}
            and defined $struct->{SEQUENCE}{NOTSUPPORTED} )
        or (    defined $struct->{CHOICE}
            and defined $struct->{CHOICE}{NOTSUPPORTED} )
        or (    $kind eq 'CHOICE'
            and defined $struct->{KIND}
            and $struct->{KIND} eq 'FREE'
            and $struct->{VALUE} ne 'NULL'
            and defined $ASN1{ $struct->{VALUE} }{NOTSUPPORTED} )
      );

    if (    $field ne 'OPTIONAL'
        and $kind eq 'CHOICE'
        and defined $struct->{UPGRADED} )
      {
        my $map = GetGivenName( $struct->{UPGRADED} );
        return $sp . $map->{FACTUAL} if $map and defined $map->{FACTUAL};
      }

    return $ASN1{ $struct->{BITSTRING}{VALUE}[0] }{$field}
      if $field ne 'OPTIONAL'
      and ref $struct eq 'HASH'
      and defined $struct->{BITSTRING}
      and defined $struct->{BITSTRING}{KIND}
      and $struct->{BITSTRING}{KIND} eq 'CONTAINING'
      and defined $struct->{BITSTRING}{VALUE}
      and ref $struct->{BITSTRING}{VALUE} eq 'ARRAY'
      and defined $ASN1{ $struct->{BITSTRING}{VALUE}[0] }
      and defined $ASN1{ $struct->{BITSTRING}{VALUE}[0] }{$field};

    return 'BITSTRING'
      if $field ne 'OPTIONAL'
      and ref $struct eq 'HASH'
      and defined $struct->{BITSTRING}
      and not defined $struct->{$field};

    return 'INTEGER'
      if $field ne 'OPTIONAL'
      and ref $struct eq 'HASH'
      and defined $struct->{INTEGER}
      and not defined $struct->{$field};

    return 0
      if $field           eq 'OPTIONAL'
      and ref $par_struct eq 'HASH'
      and $orig_field =~ /dummy/
      and defined $par_struct->{_ORDER_}
      and scalar @{ $par_struct->{_ORDER_} } == 1;

    return $struct->{$field} if defined $struct->{$field};

    return $struct->{SEQUENCE}{$field}
      if defined $struct->{SEQUENCE} and defined $struct->{SEQUENCE}{$field};
    return $struct->{CHOICE}{$field}
      if defined $struct->{CHOICE} and defined $struct->{CHOICE}{$field};
    return $struct->{SEQUENCEOF}{$field}
      if defined $struct->{SEQUENCEOF}
      and defined $struct->{SEQUENCEOF}{$field};

    return 'DUMMY'
      if $field ne 'OPTIONAL'
      and (
        (
                defined $struct->{KIND}
            and $struct->{KIND} eq 'FREE'
            and ( $struct->{VALUE} eq 'NULL'
                or defined $ASN1{ $struct->{VALUE} }{NOTSUPPORTED} )
        )
        or (
                defined $orig_field
            and $orig_field =~ /dummy/
            and defined $par_struct->{_ORDER_}
            and scalar @{ $par_struct->{_ORDER_} } == 1
            and not(defined $struct->{KIND}
                and $struct->{KIND} eq 'FREE'
                and defined $ASN1{ $struct->{VALUE} }{$field} )
        )
      );

    return $ASN1{ $ASN1{ $struct->{VALUE} }{UPGRADED} }{$field}
      if $field ne 'OPTIONAL'
      and defined $struct->{KIND}
      and $struct->{KIND} eq 'FREE'
      and defined $ASN1{ $struct->{VALUE} }{UPGRADED}
      and defined $ASN1{ $ASN1{ $struct->{VALUE} }{UPGRADED} }
      and defined $ASN1{ $ASN1{ $struct->{VALUE} }{UPGRADED} }{$field};

    return $ASN1{ $struct->{VALUE} }{$field}
      if defined $struct->{KIND}
      and $struct->{KIND} eq 'FREE'
      and defined $ASN1{ $struct->{VALUE} }{$field};

    return 'Boolean'
      if $field ne 'OPTIONAL'
      and ( defined $struct->{KIND}
        and $struct->{KIND}  eq 'FREE'
        and $struct->{VALUE} eq 'BOOLEAN' );

    return 1
      if $field eq 'OPTIONAL'
      and (
        defined $struct->{DEFAULT}
        or (    defined $struct->{INTEGER}
            and defined $struct->{INTEGER}{DEFAULT} )
        or (    defined $struct->{ENUMERATED}
            and defined $struct->{ENUMERATED}{DEFAULT} )
        or (    defined $struct->{BITSTRING}
            and defined $struct->{BITSTRING}{DEFAULT} )
        or (    defined $struct->{OCTETSTRING}
            and defined $struct->{OCTETSTRING}{DEFAULT} )
      );

    return 1
      if $field eq 'OPTIONAL'
      and (
        (
                defined $struct->{ENUMERATED}
            and defined $struct->{ENUMERATED}{OPTIONAL}
        )
        or (    defined $struct->{BITSTRING}
            and defined $struct->{BITSTRING}{OPTIONAL} )
        or (    defined $struct->{OCTETSTRING}
            and defined $struct->{OCTETSTRING}{OPTIONAL} )
        or
        ( defined $struct->{INTEGER} and defined $struct->{INTEGER}{OPTIONAL} )
      );

    return 0 if $field eq 'OPTIONAL';

    return undef;
  }

sub LikeIntegerLoosely
  {
    my $struct = shift;

    return TRUE
      if defined $struct->{VALUE}
      and not ref $struct->{VALUE}
      and defined $ASN1{ $struct->{VALUE} }
      and defined $ASN1{ $struct->{VALUE} }{SEQUENCEOF}
      and defined $ASN1{ $struct->{VALUE} }{SEQUENCEOF}{TYPE}
      and not ref $ASN1{ $struct->{VALUE} }{SEQUENCEOF}{TYPE}
      and defined $ASN1{ $ASN1{ $struct->{VALUE} }{SEQUENCEOF}{TYPE} }
      and
      defined $ASN1{ $ASN1{ $struct->{VALUE} }{SEQUENCEOF}{TYPE} }{BITSTRING};

    return FALSE;
  }

sub GetName
  {
    my $map  = shift;
    my $kind = ( shift or undef );

    my $struct_name = undef;
    if ( ref $map )
      {
        if ($kind)
          {
            $struct_name = $map->{$kind} if defined $map->{$kind};
          }
        else
          {
            $struct_name = $map->{ELEMENT} if defined $map->{ELEMENT};
            $struct_name = $map->{FACTUAL}
              if defined $map->{FACTUAL} and not defined $map->{ELEMENT};
          }
      }
    else
      {
        my @name = split /-/, $map;
        my @tail = ();
        undef $map;

        $map = GetGivenName( join( "-", @name ) );

        while ( not $map and @name )
          {
            push @tail, pop @name;
            $map = GetGivenName( join( "-", @name ) );
          }

        if ($kind)
          {
            $struct_name = $map->{$kind} if defined $map->{$kind};
          }
        else
          {
            $struct_name = $map->{ELEMENT} if defined $map->{ELEMENT};
            $struct_name = $map->{FACTUAL}
              if defined $map->{FACTUAL} and not defined $map->{ELEMENT};
          }
        $struct_name .= join( "-", @tail );
        $struct_name =~ s/-/_/g;
      }

    return $struct_name;
  }

sub GetInteger
  {
    my $int = shift;

    return $int if not ref $int and $int =~ /^-?\d+$/;

    return $ASN1{$int}{INTEGER}
      if not ref $int
      and defined $ASN1{$int}
      and ref $ASN1{$int} eq 'HASH'
      and defined $ASN1{$int}{INTEGER};

    return $int->{INTEGER}
      if ref $int eq 'HASH'
      and defined $int->{INTEGER};

    return undef;
  }

sub LikeStatic
  {
    my $struct = shift;

    return TRUE if defined $struct->{STATIC};

    my $_struct = SkipStruct($struct);

    return FALSE if not defined $_struct->{_ORDER_};

    foreach my $field ( @{ $_struct->{_ORDER_} } )
      {
        return FALSE
          unless defined $_struct->{$field}{KIND}
          and $_struct->{$field}{KIND} eq 'FREE'
          and (
            $_struct->{$field}{VALUE} eq 'BOOLEAN'
            or (    defined $ASN1{ $_struct->{$field}{VALUE} }
                and defined $ASN1{ $_struct->{$field}{VALUE} }{ENUMERATED} )
          );
      }

    return TRUE;
  }

#---------------------- internal i/f -------------------------
sub sign
  {
    return 1 if $_[0] > 0;
    return 0 if $_[0] == 0;
    return -1;
  }

#-------------------------------------------------------------
1;
