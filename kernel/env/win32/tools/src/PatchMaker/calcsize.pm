#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# Patch Maker Service Library
#
# Calculate PAtch Penalties
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
# 0.1.0         17-Nov-2008     KS         1. Extend penalty table: for each
#                                             function's penalty add sizes of its
#                                             ingridients
# 0.0.1         04-Nov-2008     KS         1. Iitial version
#-----------------------------------------------------------------------
package PatchMaker::calcsize;

use lib '\env\win32\tools\src';

use strict;
use warnings;

use Data::Dumper;

use PatchMaker::globals;

#------------------ Application-wide Variables ---------------
our $DEBUG;
our %ROMFUNCTREE = ();

#---------------------- Mode-wide Variables ------------------
my %FuncSize = ();

#--------------------- Main i/f Function ---------------------
sub CalculatePatchPenalty
  {
    my $mapFile        = shift;
    my $CodebaseFolder = shift;

    &RomFunctionsTree($CodebaseFolder);

    if ( not open( MAP, "<$mapFile" ) )
      {
        Warning("Failed to read from MAP file $mapFile");
        return;
      }

    my $inFuncData   = NO;
    my %PatchPenalty = ();
    while ( my $line = readline *MAP )
      {
        chomp $line;

        if ( $line =~ /^\s*$/ and $inFuncData == YES )
          {
            last;
          }
        elsif ( $inFuncData == YES )
          {
            my @temp = split( /\s+/, $line );

            next if $temp[0] =~ /\.end$/;

            if ( $temp[1] =~ /^0x/ and $temp[2] =~ /^0x/ )
              {
                $FuncSize{ $temp[0] } = hex $temp[2] if hex( $temp[2] ) != 0;
              }
            elsif ( $temp[2] =~ /^0x/ and $temp[3] =~ /^0x/ )
              {
                $FuncSize{ $temp[0] } = hex $temp[3] if hex( $temp[3] ) != 0;
              }
            else
              {
                Warning("Failed to read size of function $temp[0]");
              }
          }
        elsif ( $line =~
/Name\s+Demangled Name\s+Address\s+Size\s+Binding\s+Filename\s+Section\s+Shndx/
          )
          {
            $inFuncData = YES;
            next;
          }
      }

    close MAP;

    foreach my $func ( keys %ROMFUNCTREE )
      {
        my @chain = ();
        $PatchPenalty{$func}{SELF} =
          defined $FuncSize{$func} ? $FuncSize{$func} : 0;
        $PatchPenalty{$func}{TOTAL} =
          ( defined $FuncSize{$func} ? $FuncSize{$func} : 0 ) +
          BrowesPatchChain( $func, \@chain );
        foreach my $ch (@chain)
          {
            push @{ $PatchPenalty{$func}{CHAIN} }, [ $ch->[0], $ch->[1] ];
          }
      }

    if ( not open( PENALTY, ">$CodebaseFolder\\RomPatchPenalty.cbf" ) )
      {
        Warning("Failed to create Rom Patch Penalty CODEBASE file");
        return;
      }

    $Data::Dumper::Indent = 2;
    print PENALTY Dumper( \%PatchPenalty );

    close PENALTY;

    if ( not open( PENALTY, ">$CodebaseFolder\\RomPatchPenalty.csv" ) )
      {
        Warning("Failed to create Rom Patch Penalty TABLE file");
        return;
      }

    print PENALTY "Function Name,Penalty Size,Function Size,Ingridients\n";
    foreach my $func ( keys %PatchPenalty )
      {
        my $ingr_str = '';
        foreach my $ingr ( @{ $PatchPenalty{$func}{CHAIN} } )
          {
            $ingr_str .= "$ingr->[0]($ingr->[1]) ";
          }
        $ingr_str = "NONE" if not $ingr_str;
        print PENALTY
"$func,$PatchPenalty{$func}{TOTAL},$PatchPenalty{$func}{SELF},$ingr_str\n";

      }

    close PENALTY;
    print "\tSuccesfully created Rom Patch Penalty TABLE and CODEBASE files\n";
  }

sub BrowesPatchChain
  {
    my $func_chain = shift;
    my $calculated = shift;

    my $size = 0;

    foreach my $f ( keys %{ $ROMFUNCTREE{$func_chain}{CHAIN} } )
      {
        my $fsize = defined $FuncSize{$f} ? $FuncSize{$f} : 0;
        push @$calculated, [ $f, $fsize ];

        $size += $FuncSize{$f} if defined $FuncSize{$f};
      }

    return $size;
  }

#-----------------------------------------------------
1;
