#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# ASN.1 Compiler Service Library
#
# Globals
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         09-Aug-2009     KS         1. Initial Version
#-----------------------------------------------------------------------
package Globals;

use strict;
use warnings;

use Exporter;
our ( @ISA, @EXPORT, @EXPORT_OK, %EXPORT_TAGS );

@ISA = qw / Exporter /;

@EXPORT = qw /

  $DEBUG
  &Debug

  $VERBOSE
  &Verbose
  
  &DumpTree

  NO YES
  TRUE FALSE
  SUCCEED FAILED
  FOUND ABSENT
  READY IMMATURE
  UNKNOWN
  
  Panic
  Error
  Warning
  Info
  /;

#-------------- Public Data ---------------
our $DEBUG;
our $VERBOSE;

use constant {
    NO  => 10,
    YES => 20,

    TRUE  => 1,
    FALSE => 0,

    SUCCEED => 1,
    FAILED  => 0,

    FOUND  => 1,
    ABSENT => 0,

    READY    => 1,
    IMMATURE => 0,
    
    UNKNOWN => 100,
};

#------------------------------------------------------
# Functions to Retrive / Manipulate with public data
#------------------------------------------------------

sub Debug   { $DEBUG   = shift }
sub Verbose { $VERBOSE = shift }

sub Panic
  {
    my $Msg = shift;

    chomp $Msg;
    print STDERR "ASN.1 Comp PANIC :: $Msg\n";

    exit 2;
  }

sub Error
  {
    my $Msg = shift;

    chomp $Msg;
    print STDERR "ASN.1 Comp ERROR :: $Msg\n";

    exit 3;
  }

sub Warning
  {
    my $Msg = shift;

    chomp $Msg;
    print STDERR "ASN.1 Comp WARNING :: $Msg\n";
  }

sub Info
  {
    my $Msg = shift;

    chomp $Msg;
    print STDOUT "ASN.1 Comp INFO :: $Msg\n" if $VERBOSE;
  }

#-----------------------------------------------------
sub ShowStatic
  {
    my $asn1      = shift;
    my $asn1usage = shift;
    my $struct    = shift;
    my $usage     = shift;
    my $level     = shift;

    my $offset = ' ' x $level;

    ( print $offset . "Basic Type $struct\n" and return )
      if not defined $asn1->{$struct};

    if ( defined $asn1->{$struct}{STATIC} )
      {
        print "$offset$struct ("
          . ( keys %{ $asn1->{$struct} } )[0]
          . ") STATIC :: ";
      }
    else
      {
        print "$offset$struct (" . ( keys %{ $asn1->{$struct} } )[0] . ") :: ";
      }

    if ( @{ $asn1usage->{$struct}{$usage} } )
      {
        print "\n";
        foreach my $s ( @{ $asn1usage->{$struct}{$usage} } )
          {
            ShowStatic( $asn1, $asn1usage, $s, $usage, $level + 2 );
          }
      }
    else
      {
        print "leaf\n";
      }
  }

sub DumpTree
  {
    my $asn1      = shift;
    my $asn1usage = shift;
    my $name      = shift;
    my $usage     = shift;
    my $what      = shift;

    open( TREE, ">c:\\$name-$what-$usage.txt" ) or die;

    foreach my $struct ( keys %$asn1usage )
      {
        print TREE "$struct";
        print TREE "($what)"
          if defined $asn1->{$struct} and defined $asn1->{$struct}{$what};
        print TREE "(ORIGINAL)"
          if defined $asn1->{$struct} and defined $asn1->{$struct}{'MAP_' . $what};
        print TREE "  ::\n";

        if ( defined $asn1usage->{$struct}{$usage} )
          {
            if ( not @{ $asn1usage->{$struct}{$usage} } )
              {
                print TREE "\tNONE\n";
              }
            else
              {
                foreach my $s ( @{ $asn1usage->{$struct}{$usage} } )
                  {
                    print TREE "\t$s";
                    print TREE "($what)"
                      if defined $asn1->{$s} and defined $asn1->{$s}{$what};
                    print TREE "(ORIGINAL)"
                      if defined $asn1->{$s}
                      and defined $asn1->{$s}{'MAP_' . $what};
                    print TREE "\n";
                  }
              }
          }
      }

    close TREE;
  }

#-----------------------------------------------------
1;

