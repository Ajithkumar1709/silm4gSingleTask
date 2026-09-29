#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# Patch Maker Service Library
#
# Implements 'Make IN-ROM Sections List' working mode
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
# 0.2.0         22-Oct-2008     KS         1. Move generation of empty CB files to
#                                             speacial module for CB initialization
# 0.1.0         15-Oct-2008     KS         1. Generate empty ROM Functions list
# 0.0.1         15-Aug-2008     KS         1. Initial version
#-----------------------------------------------------------------------
package PatchMaker::mklist;

use lib '\env\win32\tools\src';

use strict;
use warnings;

use Data::Dumper;

use PatchMaker::globals;

use constant EXCLUDE_SECTIONS => qw /program constdata/;

#--------------------- Main i/f Function --------------------
sub GenerateSectionsList
  {
    my ( $MapFile, $CodeBase ) = @_;

    open MAP, "<$MapFile" or Panic("Failed to open map file $MapFile");

    my $STAGE       = 'ROM-MEMORY';
    my $Listen      = 0;
    my $Memory      = '';
    my @RomMemory   = ();
    my @OutSections = ();
    my @InSections  = ();

    while ( my $line = <MAP> )
      {
        $STAGE =
          browse_INSECTION( $line, \$Listen, \@InSections, \@OutSections,
            \*MAP )
          if $STAGE eq 'IN-SECTION';

        $STAGE =
          browse_OUTSECTION( $line, \$Listen, \$Memory, \@RomMemory,
            \@OutSections, \*MAP )
          if $STAGE eq 'OUT-SECTION';

        $STAGE = browse_ROMMEMORY( $line, \$Listen, \@RomMemory )
          if $STAGE eq 'ROM-MEMORY';
      }

    close MAP;
    Panic("No INPUT section found") if not @InSections;

    open CB, ">$CodeBase\\" . PatchMaker::globals::ROMSECTIONS_FILE . ".cbf"
      or Panic("Failed to access codebase folder $CodeBase");

    $Data::Dumper::Indent = 2;
    print CB Dumper( \@InSections );
    close CB;

    print "Found "
      . +( $#InSections + 1 )
      . " input sections in ROM.\nWritten to $CodeBase\\"
      . PatchMaker::mklist::ROMSECTIONS_FILE . ".cbf";
  }

#-------------------- Internal Functions ----------------------------
sub browse_ROMMEMORY
  {
    my ( $line, $listen, $romMemory ) = @_;

    if ($$listen)
      {
        my @line = split /\s+/, $line;
        push @$romMemory, [ $line[0], 1 ]
          if defined $line[4] and $line[4] eq 'ROM';
      }

    $$listen = 1 if $line =~ /Memory Map of/;
    if ( $line =~ /Memory usage information/ )
      {
        Panic("No in ROM memory found") if !@$romMemory;
        $$listen = 0;
        return 'OUT-SECTION';
      }

    return 'ROM-MEMORY';
  }

sub browse_OUTSECTION
  {
    my ( $line, $listen, $memory, $romMemory, $outSections, $map ) = @_;

    if (    $$memory
        and $line =~ /Total free space available in memory \'$$memory\'/ )
      {
        $$listen = 0;
        if ($$memory)
          {
            for ( my $i = 0 ; $i <= $#$romMemory ; $i++ )
              {
                $$romMemory[$i][1] = 0 if $$romMemory[$i][0] eq $$memory;
              }

            my $flag = 0;
            foreach my $rom (@$romMemory)
              {
                $flag = 1 if $rom->[1] == 1;
              }

            if ( not $flag )
              {
                Panic("No OUT sections found") if not @$outSections;
                return 'IN-SECTION';
              }
          }

        $$memory = '';
      }

    if ($$listen)
      {
        my @line = split /\s+/, $line;
        push @$outSections, $line[0];
      }

    if ( $line =~
/The following output sections have been located in the following memory '([\w\.]+)'/
      )
      {
        $$memory = $1;
        if ( grep { $$memory eq $_->[0] } @$romMemory )
          {
            readline $map;
            $$listen = 1;
          }
        else
          {
            $$memory = '';
          }
      }
    return 'OUT-SECTION';
  }

sub browse_INSECTION
  {
    my ( $line, $listen, $inSections, $outSections, $map ) = @_;

    $$listen = 0 if $line =~ /^\s*$/;

    if ($$listen)
      {
        my @line = split /\s+/, $line;
        push @$inSections, $line[0]
          if not grep { $line[0] eq $_ } ( @$inSections, (EXCLUDE_SECTIONS) );

      }

    if ( $line =~ /Output Section ([\w\.]+)/ )
      {
        my $OutSection = $1;
        if ( grep { $OutSection eq $_ } @$outSections )
          {
            $$listen = 1;
            readline $map;
          }
      }

    return 'IN-SECTION';

  }

#-----------------------------------------------------
1;

