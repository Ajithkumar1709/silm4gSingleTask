#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# ASN.1 Compiler Service Library
#
# Compose Code for SEQUENCE OF types
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         31-Jan-2010     KS         1. Initial Version
#-----------------------------------------------------------------------
package Composer::SEQUENCEOF;



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

    return _composeHEADER(@_) if $kind eq 'HEADER';
    return _composeCODE( 'COMMON', @_ ) if $kind eq 'CODE';
  }

sub _composeHEADER
  {
    my ( $Files, $map, $struct, $masterStatic, $structPrefix ) = @_;

    return _composeMainHeader( $Files->[MAIN][HANDLE],
        $map, $struct, $masterStatic, $structPrefix );
  }

sub _composeCODE
  {
    my $kind     = shift;
    my $Files    = shift;
    my $sequence = shift;

    my $ref = undef;
    $ref = $ASN1{ $sequence->[0] } if $kind eq 'COMMON';
    $ref = $sequence if $kind eq 'INTERNAL';

    while ( my $int_ref = _sequenceReady( $Files, $ref ) )
      {
        _composeEncode(
            $Files->[ENCS][HANDLE],
            $int_ref,
            (
                defined $int_ref->{DECODE_ONLY}
                  or (  defined $int_ref->{SEQUENCE}
                    and defined $int_ref->{SEQUENCE}{DECODE_ONLY} )
              ) ? TRUE: FALSE
        );
        _composeDecode(
            $Files->[DECS][HANDLE],
            $int_ref, $int_ref,
            (
                defined $int_ref->{DECODE_ONLY}
                  or (  defined $int_ref->{SEQUENCE}
                    and defined $int_ref->{SEQUENCE}{DECODE_ONLY} )
              ) ? TRUE: FALSE
        );
        $int_ref->{CODE_DONE} = 1;
      }
  }

sub _composeMainHeader
{
    
}

sub _composeEncode
  {
    my $File       = shift;
    my $sequence   = shift;
    my $decodeOnly = shift;

  }

sub _composeDecode
  {
    my $file        = shift;
    my $strDisposal = shift;
    my $encode_only = shift;

  }

#-------------------------------------------------------------
1;
