#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# Patch Maker Service Library
#
# Implements Generating inverse function call tree working mode
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
#
# 1.0.0         09-Feb-2009     KS         Official Release
#
# 0.2.0         08-Feb-2009     KS         1. Recognize 'Referenced by local' function calls
# 0.1.0         25-Nov-2008     KS         1. Generate ROM Function Tree to list
#                                             the whole 'called by' chain for each function
#                                             instead of keeping only the first level
# 0.0.1         22-Oct-2008     KS         1. Initial version
#-----------------------------------------------------------------------
package PatchMaker::mktree;

use lib '\env\win32\tools\src';

use strict;
use warnings;

use Data::Dumper;

use PatchMaker::globals;

our %ROMFUNCTIONS;
our %ROMFUNCTREE;

#--------------------- Main i/f Function --------------------
sub GenerateInverseCallTree
  {
    my ( $xrfFile, $Codebase ) = @_;

    my %XRF    = ();
    my $Symbol = '';

    open XRF, "<$xrfFile"
      or Panic("Failed to open XREF file $xrfFile for reading");

    while ( my $line = readline XRF )
      {
        chomp $line;

        if ( $line =~ /Symbol "([\.a-zA-Z_\$][\.\w\$]*)"/ )
          {
            $Symbol = $1;
            @{ $XRF{$1} } = ();
          }

        if ( $line =~ /\s+Referenced by (?:local )?"([\.a-zA-Z_\$][\.\w\$]*).*"/ )
          {
            push @{ $XRF{$Symbol} }, $1
              if not grep { $_ eq $1 } @{ $XRF{$Symbol} };
          }
      }

    close XRF;

    &RomFunctions($Codebase);
    foreach my $romFunc ( keys %ROMFUNCTIONS )
      {
        %{ $ROMFUNCTREE{$romFunc}{CHAIN} } = ();
        FuncCallTreeBrowse( $romFunc, $romFunc, \%XRF );

        my @Chain = keys %{ $ROMFUNCTREE{$romFunc}{CHAIN} };
        foreach my $f (@Chain)
          {
            for (
                my $i = 0 ;
                $i <= $#{ $ROMFUNCTREE{$romFunc}{CHAIN}{$f} } ;
                $i++
              )
              {
                delete $ROMFUNCTREE{$romFunc}{CHAIN}{$f}->[$i]
                  if not( $ROMFUNCTREE{$romFunc}{CHAIN}{$f}->[$i] eq $romFunc
                    or grep { $_ eq $ROMFUNCTREE{$romFunc}{CHAIN}{$f}->[$i] }
                    @Chain );
              }
          }
      }

    open CB, ">$Codebase\\" . PatchMaker::globals::ROMFUNCTREE_FILE . ".cbf"
      or Panic("Failed to access codebase folder $Codebase");

    $Data::Dumper::Indent = 2;
    print CB Dumper( \%ROMFUNCTREE );
    close CB;

  }

sub FuncCallTreeBrowse
  {
    my $keyFunc = shift;
    my $romFunc = shift;
    my $xrf     = shift;

    foreach my $func ( @{ $xrf->{$romFunc} } )
      {
        @{ $ROMFUNCTREE{$keyFunc}{CHAIN}{$func} } = ()
          if defined $ROMFUNCTIONS{$func}
          and not defined $ROMFUNCTREE{$keyFunc}{CHAIN}{$func};

        push @{ $ROMFUNCTREE{$keyFunc}{CHAIN}{$func} }, $romFunc
          if defined $ROMFUNCTIONS{$func}
          and not grep { $_ eq $romFunc }
          @{ $ROMFUNCTREE{$keyFunc}{CHAIN}{$func} };
      }

    foreach my $func ( @{ $xrf->{$romFunc} } )
      {
        if ( $keyFunc eq $func )
          {
            print "Recursive call $keyFunc\n";
            next;
          }
        FuncCallTreeBrowse( $keyFunc, $func, $xrf )
          if defined $ROMFUNCTIONS{$func};
      }
  }

#-----------------------------------------------------
1;
