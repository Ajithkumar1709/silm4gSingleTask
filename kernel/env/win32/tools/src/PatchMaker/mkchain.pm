#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# Patch Maker Service Library
#
# Implements 'Make Chain Patching' main working mode
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 1.3.0         23-Feb-2009     KS         1. Add patch section threshold mechanism
# 1.2.0         17-Feb-2009     KS         1. Read and concatenate lines from file until
#                                             ; or : at the end of line will be reached
# 1.1.0         15-Feb-2009     KS         1. Dump list of patched functions at the end of chain patching
#                                             if run in debug mode
#
# 1.0.0         09-Feb-2009     KS         Official Release
#
# 0.6.0         08-Feb-2009     KS         1. Properly cover chain patching of 'recursive' functions
# 0.5.0         05-Feb-2009     KS         1. Make 'SKIP' mode silent
#                                          2. Accept objects' root folder and use it for compilation
# 0.4.0         28-Jan-2009     KS         1. Apply 'SKIP' mode
#                                          2. More strict fix of non standard semicolons
# 0.3.0         15-Dec-2008     KS         1. Defend critical sections (actual file writing)
# 0.2.0         23-Nov-2008     KS         1. De-patch untouched functions if were pathed previously
# 0.1.0         23-Nov-2008     KS         1. Mark auto-labels of altered function with different
#                                             extension
# 0.0.1         28-Oct-2008     KS         1. Add registering of patch chain during patching
#-----------------------------------------------------------------------
package PatchMaker::mkchain;

use lib '\env\win32\tools\src';

use strict;
use warnings;

use Data::Dumper;
use File::Basename;

use PatchMaker::statemachine;
use PatchMaker::globals;

use PatchMaker::commons qw/
  WriteCacheFile
  CloneFunction
  ShowHash
  ShowArray
  END__CriticalSection
  APOGEE__CriticalSection
  /;

#------------------ Application-wide Variables ---------------
our @ROMSECTIONS   = ();
our %ROMFUNCTREE   = ();
our %PATCHFUNCLIST = ();
our %CodeCache;
our @ccPtr;
our %States;
our $DEBUG;

#-------------------- This mode constants  ------------------

#--------------------- Main i/f Function --------------------
sub MakeChainPatch
  {
    my $CodebaseFolder   = shift;
    my $CodeCacheFolder  = shift;
    my $CodeCacheCompC   = shift;
    my $CodeCacheCompASM = shift;
    my $ObjectRootFolder = shift;
    my $F_Threshold        = shift;
    my $D_Threshold        = shift;
    my $MakePatchMode    = ( shift or 'PATCH' );

    return if $MakePatchMode eq 'SKIP';

    &PatchFunctionsList($CodeCacheFolder);

    my @DumpPatchedFunctions = ();
    my $DumpFile             = $CodeCacheFolder . "\\PatchedFunctions.dump";

    if ( not %PATCHFUNCLIST )
      {
        print "\tClean. No chain patching required\n";

        if ($PatchMaker::globals::DEBUG)
          {
            push @DumpPatchedFunctions, "No Functions were patched";
            &PatchMaker::commons::DumpArray( $DumpFile,
                \@DumpPatchedFunctions );
          }
        return;
      }

    if ($PatchMaker::globals::DEBUG)
      {
        print "DEBUG :: Read PATCH FUNC LIST\n";
        &PatchMaker::commons::ShowHash( 1, \%PATCHFUNCLIST );
      }

    &InitStates();
    &RomSections($CodebaseFolder);
    &RomFunctions($CodebaseFolder);
    &RomFunctionsTree($CodebaseFolder);

    # Fill patched/depatched function chains
    foreach my $patched_func ( @{ $PATCHFUNCLIST{PATCHED} } )
      {
        RegisterPatchChain( $patched_func, 'TOUCHED' );
      }

    foreach my $untouched_func ( @{ $PATCHFUNCLIST{DEPATCHED} } )
      {
        RegisterPatchChain( $untouched_func, 'UNTOUCHED' );
      }

    if ($PatchMaker::globals::DEBUG)
      {
        my $bakCount = 1;
        while ( -f "$CodeCacheFolder\\"
            . PatchMaker::globals::PATCHFUNCLIST_FILE
            . ".cbf.bak$bakCount" )
          {
            $bakCount++;
          }

        open( PATCH,
                ">$CodeCacheFolder\\"
              . PatchMaker::globals::PATCHFUNCLIST_FILE
              . ".cbf.bak$bakCount" )
          or Panic("Failed to create Patch Functions List file");

        $Data::Dumper::Indent = 2;
        print PATCH Dumper( \%PATCHFUNCLIST );

        close PATCH;

        print
"DEBUG :: keep working version of PATCH FUNC LIST for this session in "
          . PatchMaker::globals::PATCHFUNCLIST_FILE
          . ".cbf.bak$bakCount\n";

        push @DumpPatchedFunctions, @{ $PATCHFUNCLIST{PATCHED} };
      }

    my $smthngPatched = NO;
    my @F_THRESHOLD     = split /\s+/, $F_Threshold;
    my @D_THRESHOLD     = split /\s+/, $D_Threshold;

    foreach my $chainpatch_file ( keys %{ $PATCHFUNCLIST{CHAIN} } )
      {
        my $patch_file           = $CodeCacheFolder . "\\" . $chainpatch_file;
        my $chain_patch_file_msg = NO;
        my $reWrite              = NO;

        print "DEBUG :: considering file $chainpatch_file\n"
          if $PatchMaker::globals::DEBUG;

        Panic("Failed to open $patch_file for analysing")
          if not open( FILE, "<$patch_file" );

        #-----------------------------------------------
        # 1. Read historical patches from this file
        #    (needed mainly for self-bug functions)
        #-----------------------------------------------
        my %HistoricalPatches = ();

        #-----------------------------------------------
        # Record format
        # // PM <patched func> <chain root func> <BUG|called by func>
        # 0  1   2              3                 4
        #-----------------------------------------------
        while ( my $line = readline *FILE )
          {
            unless ( $line =~ /^\/\/ PM / )
              {
                seek FILE, -( length($line) + 1 ), 1;
                last;
              }

            chomp $line;
            my @temp = split( /\s+/, $line );
            next if not $temp[2] or not $temp[3];

            push @{ $HistoricalPatches{ $temp[2] }{ $temp[3] } }, $temp[4];
          }

        if ($PatchMaker::globals::DEBUG)
          {
            print "DEBUG :: read Historical Patches:\n";
            &PatchMaker::commons::ShowHash( 1, \%HistoricalPatches );
          }

        FilterPatchFuncList( $chainpatch_file, \%HistoricalPatches );

        #-----------------------------------------------
        # 2. Read the file's content into internal structure
        #-----------------------------------------------
        my $state = 'FILE';
        %CodeCache = ( SCHEMA => CB_SCHEMA );
        @ccPtr     = ( \%CodeCache );

        while ( my $line = readline *FILE )
          {
            chomp $line;

            my @lines = ();
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
                $state = $States{$state}->( $patch_file, $ll . $end, 'FULL' );
              }
          }
        close FILE;

        $States{'ERROR'}->(
            undef, undef, undef,
"Unexpected end of file (Probably improper ending of the last function)"
        ) if $state eq 'FUNC_BODY';

        #-----------------------------------------------
        # 3. Read appropriate Codebase file
        #-----------------------------------------------
        our $VAR1;
        my %CodeCBF = ();
        eval { require "$CodebaseFolder\\$chainpatch_file.cbf " };
        Panic("Filed to open codebase file $chainpatch_file") if $@;
        %CodeCBF = %{$VAR1};
        undef $VAR1;

        #-----------------------------------------------
        # 4. De-patch functions that belong to restored chains
        #-----------------------------------------------
        print "DEBUG :: start DE-paching\n" if $PatchMaker::globals::DEBUG;
        foreach my $patch_func (
            keys %{ $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{UNTOUCHED} } )
          {
            print "DEBUG :: considering function $patch_func\n"
              if $PatchMaker::globals::DEBUG;

            my @CalledBy = ();

            # to cover recursive calls
            push @CalledBy, $patch_func
              if defined $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{UNTOUCHED}
              {$patch_func}{$patch_func}
              and grep /$patch_func/,
              @{ $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{UNTOUCHED}{$patch_func}
                  {$patch_func} };

            foreach my $root_func (
                keys %{
                    $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{UNTOUCHED}
                      {$patch_func}
                }
              )
              {
                push @CalledBy,
                  @{ $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{UNTOUCHED}
                      {$patch_func}{$root_func} };

                if (    defined $HistoricalPatches{$patch_func}
                    and defined $HistoricalPatches{$patch_func}{$root_func} )
                  {
                    $reWrite = YES;
                    delete $HistoricalPatches{$patch_func}{$root_func};
                  }
              }
            next if not @CalledBy;

            my %_uniq = ();
            @_uniq{@CalledBy} = 1;
            @CalledBy = keys %_uniq;

            my $reCalledBy = join( "|", @CalledBy );
            $reCalledBy = qr/$reCalledBy/;

            print "DEBUG :: found called by list "
              . join( ",", @CalledBy ) . "\n"
              if $PatchMaker::globals::DEBUG;

            if ( defined $CodeCache{FUNCTIONS}{ $patch_func . "_BUG" } )
              {

                print "DEBUG :: $patch_func has a patch; check it\n"
                  if $PatchMaker::globals::DEBUG;

                my $bugSectIndex =
                  $CodeCache{FUNCTIONS}{ $patch_func . "_BUG" }->[0];
                my $bugFuncIndex =
                  $CodeCache{FUNCTIONS}{ $patch_func . "_BUG" }->[1];

                my $matches = 0;
                foreach my $line (
                    keys
                    %{ $CodeCache{FILE}{$bugSectIndex}{$bugFuncIndex}{BODY} } )
                  {
                    $CodeCache{FILE}{$bugSectIndex}{$bugFuncIndex}{BODY}{$line}
                      {LINE} =~ s/\b($reCalledBy)_BUG\b/$1/g;

                    $matches +=
                      ( $CodeCache{FILE}{$bugSectIndex}{$bugFuncIndex}{BODY}
                          {$line}{LINE} =~ /\B_BUG\b/ );
                  }

                $reWrite = YES;

                # completely remove function's patch if there is not more
                # chain patching and the function itself was not pathed
                # due to a bug
                if (
                    $matches == 0
                    and not(defined $HistoricalPatches{$patch_func}
                        and defined $HistoricalPatches{$patch_func}{$patch_func}
                        and grep { $_ eq 'BUG' }
                        @{ $HistoricalPatches{$patch_func}{$patch_func} } )
                  )
                  {
                    print "DEBUG :: $patch_func was completely de-pathed\n"
                      if $PatchMaker::globals::DEBUG;

                    # skip writing the function
                    $CodeCache{FILE}
                      { $CodeCache{FUNCTIONS}{ $patch_func . "_BUG" }[0] }
                      { $CodeCache{FUNCTIONS}{ $patch_func . "_BUG" }[1] }
                      {SKIP} = 1;

                    # restore ROM section of the original finction
                    $CodeCache{FILE}{ $CodeCache{FUNCTIONS}{$patch_func}[0] }
                      {NAME} =
                      $CodeCache{FILE}
                      { $CodeCache{FUNCTIONS}{ $patch_func . "_BUG" }[0] }
                      {NAME};
                    $CodeCache{FILE}{ $CodeCache{FUNCTIONS}{$patch_func}[0] }
                      {MEMORY} = 'ROM';

                    if ( $chain_patch_file_msg == NO )
                      {
                        print "\tChain Patcher :: file $chainpatch_file ...\n";
                        $chain_patch_file_msg = YES;
                      }

                    print "\t\t- de-patching $patch_func for "
                      . join( " ", @CalledBy ) . "\n";

                    print
"\t\t- $patch_func all patches removed, function restored\n";
                  }
                else
                  {
                    print
"\t\t- $patch_func remained patched due to a self-patch or another chain patching\n";
                  }
              }
            else
              {
                if ( $chain_patch_file_msg == NO )
                  {
                    print "\tChain Patcher :: file $chainpatch_file ...\n";
                    $chain_patch_file_msg = YES;
                  }
                Error(  "Function $patch_func supposed "
                      . "to be already patched, but it is not. "
                      . "AT THIS STAGE YOU HAVE NO CHOICE. CONSIDER REBUILD\n"
                );
              }

            print "DEBUG :: finished function $patch_func\n"
              if $PatchMaker::globals::DEBUG;
          }
        print "DEBUG :: finish DE-paching\n" if $PatchMaker::globals::DEBUG;

        #-----------------------------------------------
        # 5. Patch functions that belong to 'bug''s chains
        #-----------------------------------------------
        print "DEBUG :: start Paching\n" if $PatchMaker::globals::DEBUG;
        my @ChainPatching = ();
        foreach my $patch_func (
            keys %{ $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{TOUCHED} } )
          {
            print "DEBUG :: cosidering function $patch_func\n"
              if $PatchMaker::globals::DEBUG;

            my @CalledBy = ();

            # to cover recursive calls
            push @CalledBy, $patch_func
              if defined $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{TOUCHED}
              {$patch_func}{$patch_func}
              and grep /$patch_func/,
              @{ $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{TOUCHED}{$patch_func}
                  {$patch_func} };

            foreach my $root_func (
                keys %{
                    $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{TOUCHED}
                      {$patch_func}
                }
              )
              {
                push @CalledBy,
                  @{ $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{TOUCHED}
                      {$patch_func}{$root_func} }
                  if not defined $HistoricalPatches{$patch_func}{$root_func};
              }
            next if not @CalledBy;

            my %_uniq = ();
            @_uniq{@CalledBy} = 1;
            @CalledBy = keys %_uniq;

            my $reCalledBy = join( "|", @CalledBy );
            $reCalledBy = qr/$reCalledBy/;

            print "DEBUG :: found 'called by' list "
              . join( " ", @CalledBy ) . "\n"
              if $PatchMaker::globals::DEBUG;

            if ( defined $CodeCache{FUNCTIONS}{ $patch_func . "_BUG" } )
              {

                print "DEBUG :: $patch_func has a patch; check it\n"
                  if $PatchMaker::globals::DEBUG;

                my $bugSectIndex =
                  $CodeCache{FUNCTIONS}{ $patch_func . "_BUG" }->[0];
                my $bugFuncIndex =
                  $CodeCache{FUNCTIONS}{ $patch_func . "_BUG" }->[1];

                my $replaces = 0;
                foreach my $line (
                    keys
                    %{ $CodeCache{FILE}{$bugSectIndex}{$bugFuncIndex}{BODY} } )
                  {
                    $replaces +=
                      $CodeCache{FILE}{$bugSectIndex}{$bugFuncIndex}{BODY}
                      {$line}{LINE} =~ s/\b($reCalledBy)\b/$1_BUG/g;
                  }

                $reWrite = YES;

                if ( $chain_patch_file_msg == NO )
                  {
                    print "\tChain Patcher :: file $chainpatch_file ...\n";
                    $chain_patch_file_msg = YES;
                  }

                if ( $replaces != 0 )
                  {
                    print
                      "\t\t- complementing chain patching of $patch_func for "
                      . join( ",", @CalledBy ) . "\n";
                  }
                else
                  {
                    print
"\t\t- $patch_func has already been fully patched for required chain patching\n"
                      . "\t\t             now only registering it\n";
                  }
              }
            elsif ( defined $CodeCache{FUNCTIONS}{$patch_func} )
              {
                if ($PatchMaker::globals::DEBUG)
                  {
                    print "DEBUG :: chain patching $patch_func\n";
                    push @DumpPatchedFunctions, $patch_func;
                  }

                my $cacheSectIndex = $CodeCache{FUNCTIONS}{$patch_func}[0];
                my $cacheFuncIndex = $CodeCache{FUNCTIONS}{$patch_func}[1];

                my $cbfSectIndex = $CodeCBF{FUNCTIONS}{$patch_func}[0];
                my $cbfFuncIndex = $CodeCBF{FUNCTIONS}{$patch_func}[1];

                push @ChainPatching, [
                    $CodeCache{FILE},

                    $CodeCBF{FILE}{$cbfSectIndex},
                    $CodeCache{FILE}{$cacheSectIndex},

                    $CodeCBF{FILE}{$cbfSectIndex}{$cbfFuncIndex},
                    $CodeCache{FILE}{$cacheSectIndex}
                      {$cacheFuncIndex},

                    $cacheSectIndex,
                    $cacheFuncIndex,

                    $reCalledBy,
                ];

                if ( $chain_patch_file_msg == NO )
                  {
                    print "\tChain Patcher :: file $chainpatch_file ...\n";
                    $chain_patch_file_msg = YES;
                  }

                print "\t\t- patching $patch_func for "
                  . join( " ", @CalledBy ) . "\n";

              }
            else
              {
                if ( $chain_patch_file_msg == NO )
                  {
                    print "\tChain Patcher :: file $chainpatch_file ...\n";
                    $chain_patch_file_msg = YES;
                  }
                Error(  "Function $patch_func was not found "
                      . "in $chainpatch_file albeit it supposed to be here! "
                      . "SEEMS THAT CODEBASE CORRUPTED\n" );
              }

            print "DEBUG :: finished function $patch_func\n"
              if $PatchMaker::globals::DEBUG;

          }

        if (@ChainPatching)
          {
            $reWrite = YES;
            foreach my $cf (@ChainPatching)
              {
                &PatchMaker::commons::CloneFunction( $cf, \%CodeCache,
                    \@F_THRESHOLD, \@D_THRESHOLD );
              }
          }

        print "DEBUG :: finish Paching\n" if $PatchMaker::globals::DEBUG;

        if ( $reWrite == YES )
          {
            $smthngPatched = YES;

            #-----------------------------------------------
            # 6. Merge new historical patches
            #-----------------------------------------------
            foreach my $pf (
                keys %{ $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{UNTOUCHED} } )
              {
                foreach my $rf (
                    keys
                    %{ $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{UNTOUCHED}{$pf} }
                  )
                  {
                    delete $HistoricalPatches{$pf}{$rf}
                      if defined $HistoricalPatches{$pf}{$rf};
                  }
              }
            foreach my $pf (
                keys %{ $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{TOUCHED} } )
              {
                foreach my $rf (
                    keys
                    %{ $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{TOUCHED}{$pf} } )
                  {
                    push @{ $HistoricalPatches{$pf}{$rf} },
                      @{ $PATCHFUNCLIST{CHAIN}{$chainpatch_file}{TOUCHED}{$pf}
                          {$rf} }
                      if not defined $HistoricalPatches{$pf}{$rf};
                  }
              }
            if ($PatchMaker::globals::DEBUG)
              {
                print
                  "DEBUG :: new and existent Historical Patches were merged:\n";
                &PatchMaker::commons::ShowHash( 1, \%HistoricalPatches );
              }

            #-----------------------------------------------
            # 7. Re-write and build final assembly if needed
            #-----------------------------------------------
            print "\t  writing file\n";

            PatchMaker::commons::APOGEE__CriticalSection;
            &PatchMaker::commons::WriteCacheFile( $patch_file, \%CodeCache,
                \%CodeCBF, \%HistoricalPatches );
            PatchMaker::commons::END__CriticalSection;

            print "\n";

            Panic("No build info for $chainpatch_file")
              if not defined $CodeCBF{OBJECT}{NAME}
              or not defined $CodeCBF{OBJECT}{EXTRA_FLAGS};

            my $CodeCacheCompiler = $CodeCacheCompC;
            $CodeCacheCompiler = $CodeCacheCompASM
              if $CodeCBF{FILE}{TYPE} eq 'ASM';

            print
"\"$CodeCacheCompiler\" $CodeCBF{OBJECT}{EXTRA_FLAGS} -c -o $CodeCBF{OBJECT}{NAME} $CodeCacheFolder\\$chainpatch_file\n"
              if $PatchMaker::globals::DEBUG;

            Error("Compilation of $chainpatch_file failed")
              if system(
"\"$CodeCacheCompiler\" $CodeCBF{OBJECT}{EXTRA_FLAGS} -c -o $ObjectRootFolder\\$CodeCBF{OBJECT}{NAME} $CodeCacheFolder\\$chainpatch_file"
              );
          }

        print "DEBUG :: finished file $chainpatch_file\n"
          if $PatchMaker::globals::DEBUG;
      }

    PatchMaker::commons::APOGEE__CriticalSection;
    open( PATCH,
            ">$CodeCacheFolder\\"
          . PatchMaker::globals::PATCHFUNCLIST_FILE
          . ".cbf" )
      or Panic("Failed to create Patch Functions List file");

    %PATCHFUNCLIST        = ();
    $Data::Dumper::Indent = 2;
    print PATCH Dumper( \%PATCHFUNCLIST );

    close PATCH;
    PatchMaker::commons::END__CriticalSection;

    if ($PatchMaker::globals::DEBUG)
      {
        print "DEBUG :: PATCH FUNC LIST file was nullified for this session\n";
        print "DEBUG :: List of all patched functions dumped to $DumpFile\n";
        &PatchMaker::commons::DumpArray( $DumpFile, \@DumpPatchedFunctions );
      }

    print "\tClean. No chain patching required\n" if $smthngPatched == NO;
  }

sub RegisterPatchChain
  {
    my $func_chain = shift;
    my $fix_manner = shift;

    foreach my $f ( keys %{ $ROMFUNCTREE{$func_chain}{CHAIN} } )
      {
        push @{ $PATCHFUNCLIST{CHAIN}{ $ROMFUNCTIONS{$f} }{$fix_manner}{$f}
              {$func_chain} }, @{ $ROMFUNCTREE{$func_chain}{CHAIN}{$f} };
      }

  }

sub FilterPatchFuncList
  {
    my $file = shift;
    my $HP   = shift;

    foreach my $fp ( keys %{ $PATCHFUNCLIST{CHAIN}{$file}{UNTOUCHED} } )
      {
        foreach
          my $fr ( keys %{ $PATCHFUNCLIST{CHAIN}{$file}{UNTOUCHED}{$fp} } )
          {
            if ( defined $HP->{$fp} )
              {
                foreach my $hp_fr ( keys %{ $HP->{$fp} } )
                  {
                    next if $fr eq $hp_fr;

                    if ($PatchMaker::globals::DEBUG)
                      {
                        print
"DEBUG :: patch Functions list for patch remove candidate $fp, cause $fr\n";
                        print "DEBUG :: before filtering:\n";
                        &PatchMaker::commons::ShowArray( 1,
                            $PATCHFUNCLIST{CHAIN}{$file}{UNTOUCHED}{$fp}{$fr} );
                      }

                    # @A = grep {my $_a = $_; not scalar grep {$_a eq $_} @B} @A
                    # remove from @A all elements that exist in @B
                    @{ $PATCHFUNCLIST{CHAIN}{$file}{UNTOUCHED}{$fp}{$fr} } =
                      grep {
                        my $_a = $_;
                        not scalar grep { $_a eq $_ } @{ $HP->{$fp}{$hp_fr} }
                      } @{ $PATCHFUNCLIST{CHAIN}{$file}{UNTOUCHED}{$fp}{$fr} };

                    if ($PatchMaker::globals::DEBUG)
                      {
                        print "DEBUG :: after filtering:\n";
                        &PatchMaker::commons::ShowArray( 1,
                            $PATCHFUNCLIST{CHAIN}{$file}{UNTOUCHED}{$fp}{$fr} );
                        print "DEBUG :: historical patches are\n";
                        &PatchMaker::commons::ShowArray( 1,
                            $HP->{$fp}{$hp_fr} );
                      }
                  }
              }
          }
      }
  }

#-----------------------------------------------------
1;
