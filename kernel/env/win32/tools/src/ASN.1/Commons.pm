#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# ASN.1 Compiler Service Library
#
# Commons
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         19-Nov-2009     KS         1. Initial Version
#-----------------------------------------------------------------------
package Commons;



use strict;
use warnings;

use Globals;
use Exporter;
our ( @ISA, @EXPORT, @EXPORT_OK, %EXPORT_TAGS );

@ISA = qw / Exporter /;

%EXPORT_TAGS =
  ( filecodes => [qw/MAIN ENCE ENCB ENCO ENCS ENCC DECE DECB DECO DECS DECC EXT NAME HANDLE/],
    globals   => [qw/%MAP %ASN1 @ASN1Index %ASN1Usage $IGNORED/],
    common_func => [qw/&GetGivenName &SkipStruct &InternalStruct &InternalString &GetReference &GetFields/]
   );
  

@EXPORT = qw /
  %MAP
  %ASN1
  @ASN1Index
  %ASN1Usage
  $IGNORED

  &GetGivenName
  &SkipStruct
  &InternalStruct
  &InternalString
  &GetReference
  &GetFields

  MAIN

  ENCE
  ENCB
  ENCO
  ENCS
  ENCC

  DECE
  DECB
  DECO
  DECS
  DECC

  EXT
  
  NAME
  HANDLE
  /;

use constant {
    MAIN => 0,

    ENCE => 1,
    ENCB => 2,
    ENCO => 3,
    ENCS => 4,
    ENCC => 5,

    DECE => 6,
    DECB => 7,
    DECO => 8,
    DECS => 9,
    DECC => 10,

    EXT => 11,
    
    NAME => 0,
    HANDLE => 1,
};

#------------------ Application-wide Variables ---------------
our $DEBUG;
our $VERBOSE;

our %ASN1      = ();
our %ASN1Index = ();
our %ASN1USAGE = ();
our %MAP       = ();
our $IGNORED   = 6;

# -------------------- Main i/f functions --------------------
sub GetGivenName
  {
    my $standard_name = shift;

    return undef if not $standard_name;

    my $simple_name = $standard_name;
    $simple_name =~ s/-/_/g;

    my @list = ();

    foreach my $map ( keys %{ $MAP{TYPE} } )
      {
        if ( $map eq $simple_name )
          {
            return $MAP{TYPE}{$map} if not wantarray;
            push @list, $MAP{TYPE}{$map};
            next;
          }

        if ( defined $MAP{TYPE}{$map}{FACTUAL}
            and $MAP{TYPE}{$map}{FACTUAL} eq $simple_name )
          {
            return $MAP{TYPE}{$map} if not wantarray;
            push @list, $MAP{TYPE}{$map};
            next;
          }

        if ( defined $MAP{TYPE}{$map}{REAL}
            and $MAP{TYPE}{$map}{REAL} eq $standard_name )
          {
            return $MAP{TYPE}{$map} if not wantarray;
            push @list, $MAP{TYPE}{$map};
            next;
          }

        if ( defined $MAP{TYPE}{$map}{ALIAS_FOR}
            and $MAP{TYPE}{$map}{ALIAS_FOR} eq $standard_name )
          {
            return $MAP{TYPE}{$map} if not wantarray;
            push @list, $MAP{TYPE}{$map};
            next;
          }
      }

    return @list if wantarray;
    return undef;
  }

sub SkipStruct
  {
    my $struct = shift;

    return $struct if ref $struct ne 'HASH';

    return $struct->{SEQUENCE} if defined $struct->{SEQUENCE};
    return $struct->{CHOICE}   if defined $struct->{CHOICE};
    return $struct->{SEQUENCEOF}{TYPE}{SEQUENCE}
      if defined $struct->{SEQUENCEOF}
      and defined $struct->{SEQUENCEOF}{TYPE}
      and ref $struct->{SEQUENCEOF}{TYPE} eq 'HASH'
      and defined $struct->{SEQUENCEOF}{TYPE}{SEQUENCE};
    return $struct->{SEQUENCEOF}{TYPE}{CHOICE}
      if defined $struct->{SEQUENCEOF}
      and defined $struct->{SEQUENCEOF}{TYPE}
      and ref $struct->{SEQUENCEOF}{TYPE} eq 'HASH'
      and defined $struct->{SEQUENCEOF}{TYPE}{CHOICE};
    return $struct->{SEQUENCEOF} if defined $struct->{SEQUENCEOF};

    return $struct;
  }

sub InternalStruct
  {
    my $struct = shift;

    if ( ref $struct eq 'HASH' )
      {
        return 'SEQUENCE'
          if defined $struct->{SEQUENCE}
          and defined $struct->{SEQUENCE}{_ORDER_};
        return 'CHOICE'     if defined $struct->{CHOICE};
        return 'SEQUENCEOF' if defined $struct->{SEQUENCEOF};
        return 'ENUMERATED' if defined $struct->{ENUMERATED};
      }
    return '';
  }

sub InternalString
  {
    my $struct = shift;

    return TRUE
      if ref $struct eq 'HASH'
      and (defined $struct->{BITSTRING}
        or defined defined $struct->{OCTETSTRING} );
    return FALSE;
  }

sub GetReference
  {
    my $name = shift;
    my $root = shift;

    $root = SkipStruct($root);

    return $root->{$name} if defined $root->{$name};

    my @name = split /-/, $name;
    my $index = $#name;
    while ( not defined $root->{ join( '-', @name[ 0 .. $index ] ) } )
      {
        $index--;
        last if $index < 0;
      }

    return undef if $index < 0;
    return $root->{ join( '-', @name[ 0 .. $index ] ) } if $index == $#name;
    return GetReference(
        join( '-', @name[ $index + 1 .. $#name ] ),
        $root->{ join( '-', @name[ 0 .. $index ] ) }
    );
  }

sub GetFields
  {
    my $root   = shift;
    my $Fields = shift;
    my $index  = shift;
    my $needRE = shift;
    my $skip   = (shift or '');

    return if $skip and defined $root->{$skip};
    
    $root = SkipStruct($root);

    return if $skip and defined $root->{$skip};

    if ( defined $root->{_ORDER_} )
      {
        foreach my $field ( @{ $root->{_ORDER_} } )
          {
            
            if ( my $kind = InternalStruct( $root->{$field} ) )
              {
                if ($needRE)
                {
                    my $separ = '-';
                    $separ = '' if not $Fields->[$index];
                push @$Fields,
                  [
                    $Fields->[$index][0] . $separ . $field,
                    $Fields->[$index][1] . "?(?:" . $separ . "$field)"
                  ];
                }
                else
                {
                    my $separ = '-';
                    $separ = '' if not $Fields->[$index];
                push @$Fields, $Fields->[$index] . $separ . $field;
                }
                GetFields( $root->{$field}, $Fields, $#{$Fields}, $needRE, $skip )
                  unless $kind eq 'ENUMERATED';
              }
          }
      }
  }

#-----------------------------------------------------
1;
