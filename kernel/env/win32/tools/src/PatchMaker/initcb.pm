#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# Patch Maker Service Library
#
# Initialize codebase
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
# 0.1.0         28-Oct-2008     KS         1. Add initialization of code cache
# 0.0.1         22-Oct-2008     KS         1. Initial version
#-----------------------------------------------------------------------
package PatchMaker::initcb;

use lib '\env\win32\tools\src';

use strict;
use warnings;

use Data::Dumper;

use PatchMaker::globals;

#--------------------- Main i/f Function --------------------
sub InitCodebase
  {
    my $CodeBase = shift;

    my %StubHash  = ();
    my @StubArray = ();

    open CB, ">$CodeBase\\" . PatchMaker::globals::ROMSECTIONS_FILE . ".cbf"
      or Panic("Failed to access codebase folder $CodeBase");

    $Data::Dumper::Indent = 2;
    print CB Dumper( \@StubArray );
    close CB;

    open CB, ">$CodeBase\\" . PatchMaker::globals::ROMFUNCTIONS_FILE . ".cbf"
      or Panic("Failed to access codebase folder $CodeBase");

    $Data::Dumper::Indent = 2;
    print CB Dumper( \%StubHash );
    close CB;

    open CB, ">$CodeBase\\" . PatchMaker::globals::ROMFUNCTREE_FILE . ".cbf"
      or Panic("Failed to access codebase folder $CodeBase");

    $Data::Dumper::Indent = 2;
    print CB Dumper( \%StubHash );
    close CB;
  }

sub InitCodecache
  {
    my $CodeCache = shift;

    my %StubHash = ();

    open CC, ">$CodeCache\\" . PatchMaker::globals::PATCHFUNCLIST_FILE . ".cbf"
      or Panic("Failed to access codecache folder $CodeCache");

    $Data::Dumper::Indent = 2;
    print CC Dumper( \%StubHash );
    close CC;
  }

#-----------------------------------------------------
1;
