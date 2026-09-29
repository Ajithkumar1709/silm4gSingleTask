#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# Patch Maker Service Library
#
# Patch maker globals
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
# 0.4.0         04-Nov-2008     KS         1. Add common stuff (read function, global structure, name, etc)
#                                             for ROM Functions Patch Size Panalty
# 0.3.0         27-Oct-2008     KS         1. Add common stuff (read function, global structure, name, etc)
#                                             for ROM Functions Tree
# 0.2.0         22-Oct-2008     KS         1. Add common stuff (read function, global structure, name, etc)
#                                             for ROM Functions Tree
#                                          2. Add feailure treatment to all functions
# 0.1.0         15-Oct-2008     KS         1. Add common stuff (read function, global structure, name, etc)
#                                             for ROM Functions List
# 0.0.2         01-Sep-2008     KS         1. Add common stuff (read function, global structure, name, etc)
#                                             for ROM Sections List
# 0.0.1         15-Aug-2008     KS         1. Initial Version
#-----------------------------------------------------------------------
package PatchMaker::globals;

use Data::Dumper;

use Exporter;
our ( @ISA, @EXPORT, @EXPORT_OK, %EXPORT_TAGS );

@ISA = qw / Exporter /;

@EXPORT = qw /

  @ROMSECTIONS
  &RomSections
  ROMSECTIONS_FILE

  %ROMFUNCTIONS
  &RomFunctions
  ROMFUNCTIONS_FILE

  %ROMFUNCTREE
  &RomFunctionsTree
  ROMFUNCTREE_FILE

  %ROMFUNCPATCHSIZE
  &RomFunctionsPatchSize
  ROMFUNCPATCHSIZE_FILE

  %PATCHFUNCLIST
  &PatchFunctionsList
  PATCHFUNCTLIST_FILE

  $DEBUG
  &Debug

  CB_SCHEMA

  NO YES
  TRUE FALSE

  Panic
  Error
  Warning
  /;

#-------------- Public Data ---------------
our @ROMSECTIONS;
our %ROMFUNCTIONS;
our %ROMFUNCTREE;
our %ROMFUNCPATCHSIZE;
our %PATCHFUNCLIST;

our $DEBUG;

use constant ROMSECTIONS_FILE      => 'RomSections';
use constant ROMFUNCTIONS_FILE     => 'RomFuncList';
use constant ROMFUNCTREE_FILE      => 'RomFuncTree';
use constant ROMFUNCPATCHSIZE_FILE => 'RomPatchPenalty';

use constant PATCHFUNCLIST_FILE => 'PatchFuncList';

use constant CB_SCHEMA => 1;

use constant {
    NO  => 10,
    YES => 20,

    TRUE  => 1,
    FALSE => 0
};

#------------------------------------------------------
# Functions to Retrive / Manipulate with public data
#------------------------------------------------------
sub RomSections
  {
    my $CodebaseFolder = shift;

    our $VAR1;
    eval { require "$CodebaseFolder\\" . ROMSECTIONS_FILE . ".cbf" };
    Error(  "Failed to evaluate "
          . ROMSECTIONS_FILE
          . "from $CodebaseFolder :: $@" )
      if $@;

    @ROMSECTIONS = @$VAR1;
    undef $VAR1;
  }

sub RomFunctions
  {
    my $CodebaseFolder = shift;

    our $VAR1;
    eval { require "$CodebaseFolder\\" . ROMFUNCTIONS_FILE . ".cbf" };
    Error(  "Failed to evaluate "
          . ROMFUNCTIONS_FILE
          . "from $CodebaseFolder :: $@" )
      if $@;

    %ROMFUNCTIONS = %$VAR1;
    undef $VAR1;
  }

sub RomFunctionsTree
  {
    my $CodebaseFolder = shift;

    our $VAR1;
    eval { require "$CodebaseFolder\\" . ROMFUNCTREE_FILE . ".cbf" };
    Error(  "Failed to evaluate "
          . ROMFUNCTREE_FILE
          . "from $CodebaseFolder :: $@" )
      if $@;

    %ROMFUNCTREE = %$VAR1;
    undef $VAR1;
  }

sub RomFunctionsPatchSize
  {
    my $CodebaseFolder = shift;

    our $VAR1;
    eval { require "$CodebaseFolder\\" . ROMFUNCPATCHSIZE_FILE . ".cbf" };
    if ($@)
      {
        Warning("Failed to evaluate "
              . ROMFUNCPATCHSIZE_FILE
              . "from $CodebaseFolder :: $@" );
        %ROMFUNCPATCHSIZE = ();
        return;
      }

    %ROMFUNCPATCHSIZE = %$VAR1;
    undef $VAR1;
  }

sub PatchFunctionsList
  {
    my $CodeCacheFolder = shift;

    eval { require "$CodeCacheFolder\\" . PATCHFUNCLIST_FILE . ".cbf" };
    if ($@)
      {
        %PATCHFUNCLIST = ();
        open( PATCH, ">$CodeCacheFolder\\" . PATCHFUNCLIST_FILE . ".cbf" )
          or Error("Failed to create Patch Functions List file");
        $Data::Dumper::Indent = 2;
        print PATCH Dumper( \%PATCHFUNCLIST );
        close PATCH;
      }
    else
      {
        our $VAR1;
        %PATCHFUNCLIST = %$VAR1;
        undef $VAR1;
      }
  }

sub Debug { $DEBUG = shift }

sub Panic
  {
    my $Msg = shift;

    print STDERR "PM PANIC :: $Msg";

    exit 128;
  }

sub Error
  {
    my $Msg = shift;

    print STDERR "PM ERROR :: $Msg";

    exit 128;
  }

sub Warning
  {
    my $Msg = shift;

    print STDERR "PM WARNING :: $Msg";
  }

#-----------------------------------------------------
1;

