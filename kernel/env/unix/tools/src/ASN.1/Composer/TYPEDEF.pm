#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# ASN.1 Compiler Service Library
#
# Proceed TYPEDEF types
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         17-Jan-2010     KS         1. Initial Version
#-----------------------------------------------------------------------
package Composer::TYPEDEF;



use strict;
use warnings;

use Globals;
use Commons qw/:globals :common_func :filecodes/;

use Composer::Commons;

#------------------ Application-wide Variables ---------------
our $DEBUG;
our %ASN1;
our %ASN1Index;
our %MAP;

# -------------------- Main i/f functions --------------------
sub compose
  {
    my $kind = shift;

    return _composeFREE(@_)    if $kind eq 'FREE';
    return _composeBOOLEAN(@_) if $kind eq 'BOOLEAN';
    return _composeTYPEDEF(@_) if $kind eq 'TYPEDEF';
  }

sub _composeTYPEDEF
  {
    my $Files      = shift;
    my $struct     = shift;
    my $name       = shift;
    my $type       = shift;
    my $typePrefix = shift;

    my %Yield = ();

    return _TYPEDEF_composeMainHeader( $Files->[MAIN][HANDLE],
        $struct, $name, $type, $typePrefix, \%Yield );
  }

sub _composeFREE
  {
    my $Files      = shift;
    my $struct     = shift;
    my $name       = shift;
    my $typePrefix = shift;
    my $curr_label = shift;

    my %Yield = ();

    return _FREE_composeMainHeader( $Files->[MAIN][HANDLE],
        $struct, $name, $typePrefix, $curr_label, \%Yield );
  }

sub _composeBOOLEAN
  {
    my $Files      = shift;
    my $name       = shift;
    my $typePrefix = shift;

    my %Yield = ();

    return _BOOLEAN_composeMainHeader( $Files->[MAIN][HANDLE],
        $name, $typePrefix, \%Yield );
  }

sub _FREE_composeMainHeader
  {
    my $File       = shift;
    my $struct     = shift;
    my $name       = shift;
    my $typePrefix = shift;
    my $curr_label = shift;

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
    $map = $map[0] if not $map and defined $map[0];

    my $struct_name = undef;
    $struct_name = $map->{FACTUAL} if ref $map and defined $map->{FACTUAL};

    if ( not ref $map )
      {
        $struct_name = $name;
        $struct_name =~ s/-/_/g;
        Warning("No name for $name in MAP file");
      }

    Composer::Commons::WriteHeader( $File, $map, $typePrefix, $struct_name );

    my $typedef_offset = ' ' x ( 59 - length("typedef $curr_label") );

    print $File <<FREE_TYPEDEF;
typedef $curr_label$typedef_offset$typePrefix$struct_name;


FREE_TYPEDEF

    return "$typePrefix$struct_name";
  }

sub _BOOLEAN_composeMainHeader
  {
    my $File       = shift;
    my $name       = shift;
    my $typePrefix = shift;

    my $map         = GetGivenName($name);
    my $struct_name = Composer::Commons::GetName( $map ? $map : $name );

    Composer::Commons::WriteHeader( $File, $map, $typePrefix, $struct_name );

    my $typedef_offset = ' ' x ( 59 - length("typedef Boolean") );

    print $File <<BOOLEAN_TYPEDEF;
typedef Boolean$typedef_offset$typePrefix$struct_name;


BOOLEAN_TYPEDEF

    return "$typePrefix$struct_name";
  }

sub _TYPEDEF_composeMainHeader
  {
    my $File       = shift;
    my $struct     = shift;
    my $name       = shift;
    my $type       = shift;
    my $typePrefix = shift;

    my @map = GetGivenName($name);
    my $map;
    my $used = undef;

    $map = $map[0] if scalar @map == 1;
    if ( scalar @map > 1 and defined $ASN1{$name}{LABEL} )
      {
        $used = $ASN1{$name}{LABEL};
        foreach my $m (@map)
          {
            $map = $m if $typePrefix . $m->{FACTUAL} ne $used;
          }
      }
    elsif ( scalar @map == 1 and defined $map[0]->{ELEMENT} )
      {
        $used = $typePrefix . $map[0]->{ELEMENT};
      }

    Warning("No name for $name in MAP file") if not $map;

    my $struct_name = undef;

    if ($map)
      {
        $struct_name = $map->{FACTUAL} if defined $map->{FACTUAL};
      }
    else
      {
        $struct_name = $name;
        $struct_name =~ s/-/_/g;
      }

    Composer::Commons::WriteHeader( $File, $map, $typePrefix, $struct_name );

    if ( not $used )
      {
        my ( $int, $lowerBound, $upperBound );

        if ( ref $struct eq 'ARRAY' )
          {
            if ( scalar @$struct == 1 )
              {
                $int = 'Int8';
                $int = 'Int16'
                  if Composer::Commons::GetInteger( $struct->[0] ) > 8;
                $int = 'Int32'
                  if Composer::Commons::GetInteger( $struct->[0] ) > 16;

                $upperBound =
                  2**Composer::Commons::GetInteger( $struct->[0] ) - 1;
                $lowerBound = 0;
              }
            elsif ( scalar @$struct == 2 )
              {
                if ( Composer::Commons::GetInteger( $struct->[0] ) < 0 )
                  {
                    $int = 'SignedInt8';
                    $int = 'SignedInt16'
                      if abs( Composer::Commons::GetInteger( $struct->[0] ) ) +
                      Composer::Commons::GetInteger( $struct->[1] ) >= 256;
                    $int = 'SignedInt32'
                      if abs( Composer::Commons::GetInteger( $struct->[0] ) ) +
                      Composer::Commons::GetInteger( $struct->[1] ) >= 65536;
                  }
                else
                  {
                    $int = 'Int8';
                    $int = 'Int16'
                      if Composer::Commons::GetInteger( $struct->[1] ) >= 256;
                    $int = 'Int32'
                      if Composer::Commons::GetInteger( $struct->[1] ) >= 65536;
                  }

                $upperBound = $struct->[1];
                $lowerBound = $struct->[0];
              }

            my $typedef_offset =
              ' ' x
              ( 59 - length("typedef $int  /* $lowerBound to $upperBound */") );

            print $File <<TYPEDEF;
typedef $int  /* $lowerBound to $upperBound */$typedef_offset$typePrefix$struct_name;


TYPEDEF
          }
        elsif ( ref $struct eq 'HASH' )
          {
            print $File Composer::Commons::WriteInternalDefines(
                "$typePrefix$struct_name", $struct, $struct->{VALUE} );

            my $upperBound = 2**$struct->{SIZE} - 1;
            my $lowerBound = 0;
            my $type       = '';
            $type = "Int32  /* $lowerBound to $upperBound */"
              if $upperBound < 4294967296;
            $type = "Int16  /* $lowerBound to $upperBound */"
              if $upperBound < 65536;
            $type = "Int8  /* $lowerBound to $upperBound */"
              if $upperBound < 256;
            my $type_offset = ' ' x ( 59 - length("typedef $type") );
            print $File <<FIELD;
typedef $type$type_offset$typePrefix$struct_name;


FIELD
          }
      }
    else
      {
        print $File <<USED_TYPEDEF;
typedef $used                                $typePrefix$struct_name;


USED_TYPEDEF

      }

    return ( "$typePrefix$struct_name", $used );

  }

sub _composeEncode
  {

    # STUB
  }

sub _composeDecode
  {

    # STUB
  }

#-------------------------------------------------------------
1;
