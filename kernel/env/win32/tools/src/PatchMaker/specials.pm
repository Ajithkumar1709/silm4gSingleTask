#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# Patch Maker Service Library
#
# Methods for special treatment of certain files
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         21-Aug-2008     KS         Initial version
#-----------------------------------------------------------------------
package PatchMaker::specials;

#use lib '\env\win32\tools\src';

use strict;
use warnings;

use Data::Dumper;
use File::Basename;

use PatchMaker::globals;

use PatchMaker::commons qw/
  END__CriticalSection
  APOGEE__CriticalSection
  /;

#-------------- Public Data ----------------
my %SpecialDispatcher = (
    MKCB    => { 'AdaptationLayer.asm' => \&_AdaptationLayer_CB },
    MKPATCH => { 'AdaptationLayer.asm' => \&_AdaptationLayer_PATCH },
);

#---------- Special Treatment Questioning and Dispatching ----------
sub isSpecial
  {
    my $item = shift;

    return YES if $item =~ /AdaptationLayer\.asm/;

    return NO;
  }

sub TreatSpecial
  {
    my $item = shift;
    my $mode = shift;

    my $_item = basename($item);
    print "Special Proceeding $_item ... " if $mode eq 'MKCB';

    Error("No special treatment defined for $_item in mode $mode")
      if not defined $SpecialDispatcher{$mode}{$_item};

    $SpecialDispatcher{$mode}{$_item}->(@_);

    print "done\n" if $mode eq 'MKCB';
  }

#-------------------- Internal Functions ----------------------------
sub _AdaptationLayer_CB
  {
    my ( $CodeCacheFolder, $CodeBaseFolder ) = @_;

    my %AdaptationLayer = ();

    if ( not open( FILE, "<$CodeCacheFolder\\AdaptationLayer.asm" ) )
      {
        Warning("Failed to open $CodeCacheFolder\\AdaptationLayer.asm. SKIP");
        return;
      }

    our $VAR1;
    eval { require "$CodeBaseFolder\\AdaptationLayer.asm.cbf" };
    if ($@)
      {
        Warning("File AdaptationLayer.asm.cbf is missing.");
        close FILE;
        return;
      }
    else
      {
        %AdaptationLayer = %{$VAR1};
      }
    undef $VAR1;

    $AdaptationLayer{SCHEMA} = CB_SCHEMA;

    my $funcCounter = 1;
    while ( my $line = readline *FILE )
      {
        chomp $line;

        if ( $line =~ /^\s*\.SECTION/i )
          {
            $AdaptationLayer{ADPLYR}{SCTN} = $line;
          }
        elsif ( $line =~ /^\s*\.ALIGN/i )
          {
            $AdaptationLayer{ADPLYR}{ALIGN} = $line;
          }

        next unless $line =~ /^\s*(_[\w\$\.]+)(?<!\.end)\s*:/;

        my $f_name = $1;

        $AdaptationLayer{ADPLYR}{TABLE}{$f_name}{LINE}  = $line;
        $AdaptationLayer{ADPLYR}{TABLE}{$f_name}{ORDER} = $funcCounter;

        $funcCounter++;
      }

    close FILE;

    open( CBF, ">$CodeBaseFolder\\AdaptationLayer.asm.cbf" )
      or Panic(
"Failed to update codebase file $CodeBaseFolder\\AdaptationLayer.asm.cbf"
      );
    $Data::Dumper::Indent = 2;
    print CBF Dumper( \%AdaptationLayer );
    close CBF;
  }

sub _AdaptationLayer_PATCH
  {
    my ( $CodeCacheFolder, $CodeBaseFolder ) = @_;

    my @CC_AdaptationLayer = ();
    my %CB_AdaptationLayer = ();

    print "\tPatch Maker :: special proceeding - Adaptation Layer \n";

    our $VAR1;
    eval { require "$CodeBaseFolder\\AdaptationLayer.asm.cbf" };
    if ($@)
      {
        Error("File AdaptationLayer.asm.cbf is missing.");
      }
    else
      {
        %CB_AdaptationLayer = %{$VAR1};
      }
    undef $VAR1;

    Error("Failed to open $CodeCacheFolder\\AdaptationLayer.asm")
      if not open( FILE, "<$CodeCacheFolder\\AdaptationLayer.asm" );

    while ( my $line = readline *FILE )
      {
        chomp $line;

        next unless $line =~ /^\s*(_[\w\$\.]+)(?<!\.end)\s*:/;

        my $f_name = $1;

        push @CC_AdaptationLayer, $line
          if not defined $CB_AdaptationLayer{ADPLYR}{TABLE}{$f_name};
      }

    close FILE;

    PatchMaker::commons::APOGEE__CriticalSection;

    Error("Failed to open $CodeCacheFolder\\AdaptationLayer.asm")
      if not open( FILE, ">$CodeCacheFolder\\AdaptationLayer.asm" );

    print FILE "$CB_AdaptationLayer{ADPLYR}{SCTN}\n"
      if defined $CB_AdaptationLayer{ADPLYR}{SCTN};
    print FILE "$CB_AdaptationLayer{ADPLYR}{ALIGN}\n"
      if defined $CB_AdaptationLayer{ADPLYR}{ALIGN};

    foreach my $f (
        sort {
            $CB_AdaptationLayer{ADPLYR}{TABLE}{$a}
              {ORDER} <=> $CB_AdaptationLayer{ADPLYR}{TABLE}{$b}{ORDER}
        } keys %{ $CB_AdaptationLayer{ADPLYR}{TABLE} }
      )
      {
        print FILE "$CB_AdaptationLayer{ADPLYR}{TABLE}{$f}{LINE}\n";
      }

    if (@CC_AdaptationLayer)
      {
        print
          "\tPatch Maker :: adding adaptation layer entries (in this order):\n";
        print "\t\t"
          . join( "\n\t\t",
            map { $_ =~ /^\s*(_[\w\$\.]+)(?<!\.end)\s*:/; $1 }
              @CC_AdaptationLayer ) . "\n";
        print FILE join( "\n", @CC_AdaptationLayer );
      }
    else
      {
        print "\tPatch Maker :: no new entries in adaptation layer found\n";
        print "\tPatch Maker :: restoring the original order\n";
      }

    close FILE;

    PatchMaker::commons::END__CriticalSection;
  }

#-----------------------------------------------------
1;
