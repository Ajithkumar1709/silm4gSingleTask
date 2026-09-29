#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# Patch Maker Service Library
#
# Implements 'Make Codebase' working mode
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 1.1.0         17-Feb-2009     KS         1. Read and concatenate lines from file until
#                                             ; or : at the end of line will be reached
#
# 1.0.0         09-Feb-2009     KS         Official Release
#
# 0.3.0         28-Jan-2009     KS         1. Additional definition for Labels - starts with 'LOOP'
# 0.2.1         04-Dec-2008     KS         1. Fix a bug in replacement of aouto-labels with re
# 0.2.0         23-Oct-2008     KS         1. Read existing cbf file istead of (re)create it. It supposes
#                                             to contain object creation info
# 0.1.0         15-Oct-2008     KS         1. Gather ROM functions along with generating codebase
# 0.0.2         24-Sep-2008     KS         1. Ignore input lines that contain with only ';'
# 0.0.1         15-Aug-2008     KS         1. Iitial version
#-----------------------------------------------------------------------
package PatchMaker::mkcb;

use lib '\env\win32\tools\src';

use strict;
use warnings;

use Data::Dumper;

use PatchMaker::statemachine;
use PatchMaker::globals;

#------------------ Application-wide Variables---------------
our @ROMSECTIONS;
our %ROMFUNCTIONS;

our %CodeCache;
our @ccPtr;
our %States;
our $DEBUG;

#--------------------- Main i/f Function --------------------
sub GenerateCodebase
  {
    my $CodeCacheFolder = shift;
    my $CodebaseFolder  = shift;

    &InitStates();
    &RomSections($CodebaseFolder);
    &RomFunctions($CodebaseFolder);

    # Read list of ROM Sections

    opendir( CODE, $CodeCacheFolder )
      or Panic("Failed to open code cache folder");

    while ( my $file = readdir CODE )
      {
        next unless $file =~ /\.(asm|s)$/;

        if ( not open( FILE, "<$CodeCacheFolder\\$file" ) )
          {
            Warning("Failed to open $CodeCacheFolder\\$file. SKIP");
            next;
          }

        print "Proceeding $file ... ";
        my $state = 'FILE';

        our $VAR1;
        eval { require "$CodebaseFolder\\$file.cbf " };
        if ($@)
          {
            print "WARNING :: File $file.cbf is missing.\n";
          }
        else
          {
            %CodeCache = %{$VAR1};
          }
        undef $VAR1;

        $CodeCache{SCHEMA} = CB_SCHEMA;
        @ccPtr = ( \%CodeCache );

        while ( my $line = readline *FILE )
          {
            chomp $line;

            my @lines;

            if (   $line =~ /^\s*$/
                or $line =~ /^\s*\/\//
                or $line =~ /^\s*\/\*.*\*\/\s*$/
                or $line =~ /^\s*#line\s+/ )
                
              {
                $lines[0] = $line;
              }
            else
              {
                until ( $line =~ /[;:]\s*$/ )
                {
                    my $_line = readline *FILE;
                    last if not defined $_line;
                    chomp $_line;
                    $line .= $_line;
                }
                @lines = split /(?:;|:\s*\Z)/, $line, $line =~ tr/;:/;:/;
              }

            foreach my $ll (@lines)
              {
                next if $ll =~ /^\s*$/;
                next if $ll =~ /^\s*;\s*$/;

                my $end = '';
                $end = ';'
                  if $ll !~ /[;:]\s*$/
                  and ( $ll !~ /^\s*\/\// and $ll !~ /^\s*\/\*.*\*\/\s*$/ );
                $ll =~ s/^\s*;//;
                $state = $States{$state}->( $file, $ll . $end, 'BRIEF' );
              }
          }

        close FILE;

        $States{'ERROR'}->(
            undef, undef, undef,
"Unexpected end of file $file (Probably improper ending of the last function)"
        ) if $state eq 'FUNC_BODY';

        # Turn funcions' lines to regular expression, with respect to labels

        foreach my $section ( keys %{ $CodeCache{FILE} } )
          {
            next if $section !~ /^S-/;

            foreach my $func ( keys %{ $CodeCache{FILE}{$section} } )
              {
                next unless $func =~ /^F-/;

                my @Labels = ();

                # 1st pass - identify and store labels
                foreach
                  my $line ( keys %{ $CodeCache{FILE}{$section}{$func}{BODY} } )
                  {
                    if ( $CodeCache{FILE}{$section}{$func}{BODY}{$line}{LINE} =~
/^\s*(?:([\.a-zA-Z_\$][\.\w\$]*):\s*|[Ll][Oo][Oo][Pp]\s+([\.a-zA-Z_\$][\.\w\$]*)\s+)/
                      )
                      {
                        my $_l = $1;
                        $_l = $2 if not defined $_l;
                        my $label = $_l;
                        $label =~ s/([\.\$])/\\$1/g;
                        push @Labels, $label;
                      }
                  }

                # 2nd pass - replace all instances of found labels with re
                my $reLabels = '';
                $reLabels = join "|", @Labels if @Labels;
                $CodeCache{FILE}{$section}{$func}{LABELS} = qr/$reLabels/
                  if $reLabels;

                my $reLabel = qr/[\.a-zA-Z_\$][\.\w\$]*/;
                foreach
                  my $line ( keys %{ $CodeCache{FILE}{$section}{$func}{BODY} } )
                  {
                    my $l =
                      $CodeCache{FILE}{$section}{$func}{BODY}{$line}{LINE};
                    if ( $l =~ /^\s*\/\// or $l =~ /^\s*\/\*.*\*\/\s*$/ )
                      {
                        $CodeCache{FILE}{$section}{$func}{BODY}{$line}{RE} =
                          qr/^.*$/;
                      }
                    else
                      {
                        $l =~ s/(?:$reLabels)\b/____/g
                          if $reLabels and $CodeCache{FILE}{TYPE} eq 'C';
                        $l =~ s/([^a-zA-Z0-9_\s\/])/\\$1/g
                          ; # not to exclude / from escaping also due to a bug in dumper
                        $l =~ s/^\s+//g;
                        $l =~ s/\s+$//g;
                        $l =~ s/\s+/\\s*/g;
                        $l =~ s/____/$reLabel/g
                          if $reLabels and $CodeCache{FILE}{TYPE} eq 'C';
                        $l =~ s/^\s*$/\\s*/;
                        $CodeCache{FILE}{$section}{$func}{BODY}{$line}{RE} =
                          qr/^\s*$l\s*$/;
                      }
                  }
              }
          }

        open( CBF, ">$CodebaseFolder\\$file.cbf" )
          or Panic("Failed to update codebase file $CodebaseFolder\\$file.cbf");
        $Data::Dumper::Indent = 0;
        print CBF Dumper( \%CodeCache );
        close CBF;

        # register found ROM functions (if any)
        if ( $CodeCache{FUNCTIONS} )
          {
            my @temp = keys %{ $CodeCache{FUNCTIONS} };
            @ROMFUNCTIONS{@temp} = ("$file") x ( $#temp + 1 );

            open CB,
              ">$CodebaseFolder\\"
              . PatchMaker::globals::ROMFUNCTIONS_FILE . ".cbf"
              or Panic("Failed to access codebase folder $CodebaseFolder");

            $Data::Dumper::Indent = 2;
            print CB Dumper( \%ROMFUNCTIONS );
            close CB;
          }

        print "done\n";
      }

    closedir CODE;

  }

#-----------------------------------------------------
1;
