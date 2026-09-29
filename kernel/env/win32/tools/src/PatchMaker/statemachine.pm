#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# Patch Maker Service Library
#
# Common state machine to read/analyze asm file
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
# 0.3.0         05-Feb-2009     KS         1. New member of function record -
#                                             DOCKET - an array of lines for comparison
# 0.2.0         02-Dec-2008     KS         1. Robust function name recognition pattern
# 0.1.0         03-Nov-2008     KS         1. Add managing of functions list
# 0.0.1         15-Aug-2008     KS         1. Iitial version
#-----------------------------------------------------------------------
package PatchMaker::statemachine;

use strict;
use warnings;

use lib '\env\win32\tools\src';

use Exporter;
our ( @ISA, @EXPORT, @EXPORT_OK, %EXPORT_TAGS );

@ISA    = qw / Exporter /;
@EXPORT = qw / %States %CodeCache @ccPtr &InitStates/;

#--------------------- Public Data --------------------
our %States    = ();
our %CodeCache = ();
our @ccPtr     = ( \%CodeCache );
our @ROMSECTIONS;
our $DEBUG;

my $LastAlignment = '';
my $LastGlobal    = '';

my $FuncCounter   = 0;
my $AfterFunction = 0;

use PatchMaker::globals;

#--------------------- Main i/f Function --------------------
sub InitStates
  {

    %States = (
        'FILE' => sub {
            my ( $f, $l, $m ) = @_;

            return 'FILE'
              unless $l =~
/^\s*(?:(?:\.FILE)|(?:#line\s+1))\s+"([^\.]+\.((?:asm)|(?:c)))";?\s*$/i;

            $ccPtr[-1]->{FILE}{NAME}         = $1;
            $ccPtr[-1]->{FILE}{TYPE}         = $2 eq 'asm' ? 'ASM' : 'C';
            $ccPtr[-1]->{FILE}{__sectcntr__} = 0;

            %{ $ccPtr[-1]->{FUNCTIONS} } = ();
            @{ $ccPtr[-1]->{FUNCLIST} }  = () if $m eq 'BRIEF';
            @{ $ccPtr[-1]->{SECTIONS} }  = () if $m eq 'BRIEF';

            push @ccPtr, $ccPtr[-1]->{FILE};

            ( $LastAlignment, $LastGlobal ) = ('') x 2;
            $FuncCounter   = 0;
            $AfterFunction = 0;

            return 'SECTION_HEADER';
        },

        'SKIP_SECTION' => sub {
            my ( $f, $l, $m ) = @_;

            $AfterFunction = 0;

            return $States{'SECTION_HEADER'}->( $f, $l, $m )
              if $l =~ /^\s*\.SECTION\s+/i;

            return 'SKIP_SECTION';
        },

        'SECTION_HEADER' => sub {
            my ( $f, $l, $m ) = @_;

            return 'SECTION_HEADER' unless $l =~ /^\s*\.SECTION\s+(.+);\s*$/i;

            my $section = $1;
            my $isRom   = grep { $section eq $_ } @ROMSECTIONS;

            return 'SKIP_SECTION'
              if $m eq 'BRIEF' and not $isRom;

            $ccPtr[-1]->{__sectcntr__}++;

            $ccPtr[-1]->{ "S-" . $ccPtr[-1]->{__sectcntr__} }{NAME} = $section;
            $ccPtr[-1]->{ "S-" . $ccPtr[-1]->{__sectcntr__} }{__line__} = 0;

            if ( $m eq 'FULL' )
              {
                $ccPtr[-1]->{ "S-" . $ccPtr[-1]->{__sectcntr__} }{MEMORY} =
                  'ROM';
                $ccPtr[-1]->{ "S-" . $ccPtr[-1]->{__sectcntr__} }{MEMORY} =
                  'SRAM'
                  if not $isRom;
              }

            push @{ $ccPtr[0]->{SECTIONS} },
              [ $1, "S-" . $ccPtr[-1]->{__sectcntr__} ]
              if $m eq 'BRIEF';

            push @ccPtr, $ccPtr[-1]->{ "S-" . $ccPtr[-1]->{__sectcntr__} };

            ( $LastAlignment, $LastGlobal ) = ('') x 2;
            $AfterFunction = 0;

            return 'SECTION_BODY';
        },

        'SECTION_BODY' => sub {
            my ( $f, $l, $m ) = @_;

            if ( $l =~ /^\s*\.SECTION\s+(.+);\s*$/i )
              {
                pop @ccPtr;
                $States{'ERROR'}->( $f, $l, $m ) if not @ccPtr;
                return $States{'SECTION_HEADER'}->( $f, $l, $m );
              }

            if ( $AfterFunction == 1 )
              {
                my $currSectionName = $ccPtr[-1]->{NAME};

                pop @ccPtr;
                $States{'ERROR'}->( $f, ".SECTION $currSectionName;", $m )
                  if not @ccPtr;

                $States{'SECTION_HEADER'}
                  ->( $f, ".SECTION $currSectionName;", $m );
              }

            if ( $l =~ /^\s*(_[\w\$\.]+)(?:\[\]\d+)?(?<!\.end):\s*$/ )
              {
                $ccPtr[-1]->{__line__}++;
                $ccPtr[-1]->{ "F-" . $ccPtr[-1]->{__line__} }{NAME}     = $1;
                $ccPtr[-1]->{ "F-" . $ccPtr[-1]->{__line__} }{__line__} = 0;
                $ccPtr[-1]->{ "F-" . $ccPtr[-1]->{__line__} }{ALIGN}    =
                  $LastAlignment
                  if $LastAlignment;
                $ccPtr[-1]->{ "F-" . $ccPtr[-1]->{__line__} }{GLOBAL} =
                  $LastGlobal
                  if $LastGlobal;
                @{ $ccPtr[-1]->{ "F-" . $ccPtr[-1]->{__line__} }{DOCKET} } = ();

                $ccPtr[0]->{FUNCTIONS}{$1} = [
                    "S-" . $ccPtr[-2]->{__sectcntr__},
                    "F-" . $ccPtr[-1]->{__line__},
                ];
                push @{ $ccPtr[0]->{FUNCLIST} }, $1 if $m eq 'BRIEF';

                push @ccPtr, $ccPtr[-1]->{ "F-" . $ccPtr[-1]->{__line__} };

                return 'FUNC_BODY';
              }

            if ( $l =~ /^\s*\.ALIGN/i )
              {
                $LastAlignment = $l;
              }
            elsif ( $l =~ /^\s*\.GLOBAL/i )
              {
                $LastGlobal = $l;
              }

            $ccPtr[-1]->{__line__}++;
            $ccPtr[-1]->{ 'L-' . $ccPtr[-1]{__line__} } = $l;

            return 'SECTION_BODY';
        },

        'FUNC_BODY' => sub {
            my ( $f, $l, $m ) = @_;

            return 'FUNC_TAIL' if $l =~ /\.?$ccPtr[-1]->{NAME}\.end/;

            if ( $l =~ /^\s*\.SECTION\s+(.+);\s*$/i )
              {
                $States{'ERROR'}->(
                    $f, $l, $m,
"Label $ccPtr[-1]->{NAME} lacks definition of $ccPtr[-1]->{NAME}.end"
                );

                pop @ccPtr;
                pop @ccPtr;
                $States{'ERROR'}->( $f, $l, $m ) if not @ccPtr;
                ( $LastAlignment, $LastGlobal ) = ('') x 2;

                return $States{'SECTION_HEADER'}->( $f, $l, $m );
              }

            unless ( $l =~ /^\s*$/ )
              {
                $ccPtr[-1]->{__line__}++;

                return 'FUNC_BODY'
                  if $m eq 'BRIEF'
                  and ( $l =~ /^\s*\/\// or $l =~ /^\s*\/\*.*\*\/\s*$/ );

                $ccPtr[-1]->{BODY}{ 'L-' . $ccPtr[-1]->{__line__} }{LINE} = $l;

                push @{ $ccPtr[-1]->{DOCKET} }, 'L-' . $ccPtr[-1]->{__line__}
                  if $l !~ /^\s*\/\// and $l !~ /^\s*\/\*.*\*\/\s*$/;

                if ( not defined $ccPtr[-1]->{TYPE} )
                  {
                    $ccPtr[-1]->{TYPE} = 'DATA';
                    $ccPtr[-1]->{TYPE} = 'FUNC' if $l !~ /^\s*\.BYTE/;
                  }
                elsif ( $ccPtr[-1]->{TYPE} eq 'DATA' )
                  {
                    $ccPtr[-1]->{TYPE} = 'FUNC'
                      if $l !~ /^\s*\.BYTE/
                      and $l !~ /^\s*([\.a-zA-Z][\.\w\$]+):\s*$/;
                  }
              }
            return 'FUNC_BODY';
        },

        'FUNC_TAIL' => sub {
            my ( $f, $l, $m ) = @_;

            if ( $l =~ /$ccPtr[-1]->{NAME}/ )
              {
                $ccPtr[-1]->{__line__}++;
                $ccPtr[-1]->{TAIL}{ 'T-' . $ccPtr[-1]->{__line__} } = $l;

                return 'FUNC_TAIL';
              }

            pop @ccPtr;
            $States{'ERROR'}->( $f, $l, $m ) if not @ccPtr;
            ( $LastAlignment, $LastGlobal ) = ('') x 2;

            $AfterFunction = 1;

            return $States{'SECTION_BODY'}->( $f, $l, $m );
        },

        'ERROR' => sub {
            my ( $f, $l, $m, $msg ) = @_;

            print qq(\n\tUnexpected flow in file $f, line $l\n)
              if not defined $msg;
            print qq(\n\t$msg\n);

            exit 128 if not $DEBUG;
          }
    );

  }

#-----------------------------------------------------
1;
