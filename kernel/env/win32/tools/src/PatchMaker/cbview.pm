#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# Patch Maker Service Library
#
# Codebase Viewer
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
# 0.2.0         04-Dec-2008     KS         1. Aligh patch penalty calculation with
#                                             new structure of penalty table
# 0.1.0         04-Nov-2008     KS         1. Show also patch penalty sizes
# 0.0.1         15-Aug-2008     KS         1. Iitial version
#-----------------------------------------------------------------------
package PatchMaker::cbview;

use lib '\env\win32\tools\src';

use strict;
use warnings;

use Data::Dumper;

use PatchMaker::globals;

#------------------ Application-wide Variables ---------------
our $DEBUG;
our %ROMFUNCPATCHSIZE;
our %ROMFUNCTIONS;

#---------------------- Mode-wide Variables ------------------
my %CodeCBF = ();
our $VAR1;

#--------------------- Main i/f Function --------------------
sub ShowCBFile
  {
    my $CodeBase = shift;
    my @Files    = @_;

    # If no file(s) provided - show the whole codebase
    if ( not @Files )
      {
        opendir( CODE, $CodeBase )
          or Panic("Failed to open codebase folder");

        while ( my $file = readdir CODE )
          {
            next unless $file =~ /\.(asm|s).cbf$/;
            push @Files, $file;
          }
      }

    &RomFunctionsPatchSize($CodeBase);
    &RomFunctions($CodeBase);

    foreach my $cbfFile (@Files)
      {
        my $show = 'FILE';
        $show = 'FUNC' if $cbfFile =~ /^:/;

        my $cbf = $cbfFile;
        my ( $Sect, $Func ) = ( '', '' );

        ( $cbf, $Sect, $Func ) = _findFunction( $cbfFile, $CodeBase )
          if $cbfFile =~ /^:/;

        if ( not $cbf )
          {
            print
              "No function recorded in codebase match your request $cbfFile";
            next;
          }

        $cbf =~ s/\.asm//;
        $cbf =~ s/\.s//;
        $cbf =~ s/\.cbf//;

        if ( -f "$CodeBase\\$cbf.asm.cbf" )
          {
            $cbf .= '.asm.cbf';
          }
        elsif ( -f "$CodeBase\\$cbf.s.cbf" )
          {
            $cbf .= '.s.cbf';
          }
        else
          {
            print "No file match $cbf in codebase\n";
            next;
          }

        eval { require "$CodeBase\\$cbf" };
        if ($@)
          {
            print "Codebase file $CodeBase\\$cbf is broken\n$@";
            next;
          }

        %CodeCBF = ();
        %CodeCBF = %$VAR1;

        if ( $show eq 'FILE' )
          {
            &_showFileBrief;
            &_showFunctionsBrief;
            &_showFunctionsDetail;
          }

        if ( $show eq 'FUNC' )
          {
            &_showFunctionHeader( $Sect, $Func );
            &_showFunction( $Sect, $Func );
          }
      }
  }

#-------------------- Internal Functions ----------------------------
sub _showFileBrief
  {
    print <<FILE_BRIEF;
        
FILE IN BRIEF ::
    Original File Name : $CodeCBF{FILE}{NAME}
    Original File Type : $CodeCBF{FILE}{TYPE}
FILE_BRIEF

    my %Sect = ();
    foreach my $sect ( @{ $CodeCBF{SECTIONS} } )
      {
        if ( not defined $Sect{ $sect->[0] } )
          {
            $Sect{ $sect->[0] } = 1;
          }
        else
          {
            $Sect{ $sect->[0] }++;
          }
      }

    my @S = keys %Sect;
    my $S = $#S + 1;
    print <<SECT_HEADER_BRIEF;
    Recorded Sections  : $S
    
SECT_HEADER_BRIEF

    foreach my $sect (@S)
      {
        print <<SECT_LIST;
          $sect x $Sect{$sect}
SECT_LIST
      }

    my @F = keys %{ $CodeCBF{FUNCTIONS} };
    print "\n    Recorded Entities   : " . +( $#F + 1 ) . "\n\n";
    foreach my $func (@F)
      {
        print <<FUNC_LIST;
          $func
FUNC_LIST
      }

  }

sub _showFunctionsBrief
  {
    print <<FUNC_BRIEF_HEADER;

        
ENTITIES IN BRIEF ::

FUNC_BRIEF_HEADER

    foreach my $func ( keys %{ $CodeCBF{FUNCTIONS} } )
      {
        _showFunctionHeader( $CodeCBF{FUNCTIONS}{$func}[0],
            $CodeCBF{FUNCTIONS}{$func}[1] );
      }
  }

sub _showFunctionHeader
  {
    my ( $S, $F ) = @_;

    my $name = $CodeCBF{FILE}{$S}{$F}{NAME};

    my $type =
      $CodeCBF{FILE}{$S}{$F}{TYPE} eq 'FUNC'
      ? 'function'
      : 'data';

    my $sect = $CodeCBF{FILE}{$S}{NAME};

    my $lines = $CodeCBF{FILE}{$S}{$F}{__line__};

    my $alignment = '.see.entity.footer.';
    $alignment = $1
      if defined $CodeCBF{FILE}{$S}{$F}{ALIGN}
      and $CodeCBF{FILE}{$S}{$F}{ALIGN} =~ /(\d+)\s*;\s*$/;

    my $global = '.see.entity.footer.';
    $global = 'YES'
      if defined $CodeCBF{FILE}{$S}{$F}{GLOBAL}
      and $CodeCBF{FILE}{$S}{$F}{GLOBAL} =~ /global/i;

    my $penalty = 'NOT FOUND(!)';
    $penalty = $ROMFUNCPATCHSIZE{ $CodeCBF{FILE}{$S}{$F}{NAME} }{TOTAL} . '('
      . (
        defined $ROMFUNCPATCHSIZE{ $CodeCBF{FILE}{$S}{$F}{NAME} }{SELF}
        ? $ROMFUNCPATCHSIZE{ $CodeCBF{FILE}{$S}{$F}{NAME} }{SELF}
        : '0'
      )
      . ')'
      if defined $ROMFUNCPATCHSIZE{ $CodeCBF{FILE}{$S}{$F}{NAME} }{TOTAL};

    my $footer = "\t\tNONE\n";
    if ( defined $CodeCBF{FILE}{$S}{$F}{TAIL} )
      {
        $footer = '';
        foreach my $t (
            sort {
                $a =~ /^T-(\d+)$/;
                my $aa = ( $1 or 0 );

                $b =~ /^T-(\d+)$/;
                my $bb = ( $1 or 0 );

                $aa <=> $bb
            } keys %{ $CodeCBF{FILE}{$S}{$F}{TAIL} }
          )
          {
            $footer .= "\t\t" . $CodeCBF{FILE}{$S}{$F}{TAIL}{$t} . "\n";
          }
      }

    print <<FUNC_BRIEF;
        
    Entity Name      : $name
    Entity Type      : $type
    In Sections      : $sect
    Meaningful Lines : $lines
    Patch Penalty    : $penalty
    Allignment       : $alignment
    Global           : $global
    Recorded Footer  :
    
$footer
FUNC_BRIEF

  }

sub _showFunctionsDetail
  {
    print <<FUNC_DETAIL_HEADER;

        
ENTITIES IN DETAIL ::

FUNC_DETAIL_HEADER

    foreach my $func ( keys %{ $CodeCBF{FUNCTIONS} } )
      {
        print <<FUNC_DETAIL_HEADER;
        
------- $func -------

FUNC_DETAIL_HEADER
        _showFunction( $CodeCBF{FUNCTIONS}{$func}[0],
            $CodeCBF{FUNCTIONS}{$func}[1] );
      }
  }

sub _showFunction
  {
    my ( $S, $F ) = @_;

    my $lg   = 0;
    my $lgre = 100;

    foreach my $l ( keys %{ $CodeCBF{FILE}{$S}{$F}{BODY} } )
      {
        my $real_line = $CodeCBF{FILE}{$S}{$F}{BODY}{$l}{LINE};
        $real_line =~ s/\t/      /g;

        $lg = length $real_line
          if $lg < length $real_line;
      }

    $lg = 100 if $lg > 100;

    for ( my $i = 1 ; $i <= $CodeCBF{FILE}{$S}{$F}{__line__} ; $i++ )
      {
        my $to_print = '';
        my $space    = '';

        if ( defined $CodeCBF{FILE}{$S}{$F}{BODY}{ 'L-' . $i } )
          {
            my $line = '';
            my $re   = '';

            my $real_line = $CodeCBF{FILE}{$S}{$F}{BODY}{ 'L-' . $i }{LINE};
            $real_line =~ s/\t/      /g;

            if ( length $real_line <= $lg )
              {
                $space = ' ' x ( $lg - length $real_line );
                $line = $real_line . $space;
              }
            else
              {
                $line = substr( $real_line, 0, $lg - 3 ) . '...';
              }

            $re = $CodeCBF{FILE}{$S}{$F}{BODY}{ 'L-' . $i }{RE};
            if ( length $CodeCBF{FILE}{$S}{$F}{BODY}{ 'L-' . $i }{RE} > $lgre )
              {
                $re = substr( $CodeCBF{FILE}{$S}{$F}{BODY}{ 'L-' . $i }{RE},
                    0, $lgre - 3 )
                  . '...';
              }

            $to_print = "$line|$re\n";
          }
        else
          {
            $space = ' ' x (
                int(
                    $lg - length("----skiped----line----skiped----line----") / 2
                )
            );
            $to_print =
              "$space----skiped----line----skiped----line----$space\n";
          }

        print $to_print;
      }
  }

sub _findFunction
  {
    my ( $Func, $CB ) = @_;

    $Func =~ s/://g;

    my $file     = '';
    my $realFunc = '';
    foreach my $func ( keys %ROMFUNCTIONS )
      {
        if ( $func =~ /$Func/ )
          {
            $file     = "$ROMFUNCTIONS{$func}.cbf";
            $realFunc = $func;
            last;
          }
      }
    return ( '', '', '' ) if not $file;

    eval { require "$CB\\$file" };
    if ($@)
      {
        Warning("Codebase file $CB\\$file is broken\n$@");
        return ( '', '', '' );
      }

    my %CBF = ();
    %CBF = %$VAR1;

    return ( $file, $CBF{FUNCTIONS}{$realFunc}[0],
        $CBF{FUNCTIONS}{$realFunc}[1] )
      if defined $CBF{FUNCTIONS}{$realFunc}[0]
      and defined $CBF{FUNCTIONS}{$realFunc}[1];

    return ( '', '', '' );

  }

#-----------------------------------------------------
1;
