#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# Patch Maker Service Library
#
# Implements 'Make Patch' main working mode
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 1.3.1         24-Feb-2009     KS         1. Fix section number calculation for new functions
# 1.3.0         23-Feb-2009     KS         1. Add patch section threshold mechanism
# 1.2.0         17-Feb-2009     KS         1. Read and concatenate lines from file until
#                                             ; or : at the end of line will be reached
# 1.1.0         11-Feb-2009     KS         1. Implement FORCE mode of patching
#
# 1.0.0         09-Feb-2009     KS         Official Release
#
# 0.13.0        05-Feb-2009     KS         1. Apply a new mechanism of finction comparison, based on docketed lines
#                                          2. Make skip mode silent
#                                          3. Don't log compiler command; for object name log path after obj_* folder
# 0.12.0        28-Jan-2009     KS         1. More strict fix of non standard semicolons
# 0.11.0        08-Jan-2009     KS         1. ROM-ROM function moving - a new type of function state
# 0.10.0        07-Jan-2009     KS         1. Identify ROM function that was moved to a RAM section as deleted
#                                          2. Identify ROM function that was moved to another ROM section as new
# 0.9.0         29-Dec-2008     KS         1. Correct the way chain_patching functions are built for restoring
# 0.8.0         29-Dec-2008     KS         1. Submit deleted function(s) for chain patching (just like changed ones)
#                                             and make an appropriate record in file's history
# 0.7.0         15-Dec-2008     KS         1. Defend critical sections (actual file writing)
# 0.6.1         14-Dec-2008     KS         1. Call BogusClone function from commons
# 0.6.0         30-Nov-2008     KS         1. Take procedures for cloning a function and writing cache file out
#                                             to separate module.
# 0.5.0         27-Nov-2008     KS         1. Manage the whole process of file compilation:
#                                             - read and keep historical info from existing code cache file
#                                             - compile the file to retreive a new version of code cache file
#                                             - read this file, analize and apply direct patches if needed
#                                             - apply chain patches recorded in historical notes
#                                             - overwrite assembly source with the patched one (including updated historical records)
#                                             - compile final assembly file to obtain object file
# 0.4.0         23-Nov-2008     KS         1. All functions that found not-changed are now registred for possible
#                                             chain de-patching
# 0.3.0         02-Nov-2008     KS         1. Create special stub fuction instead a deleted one
# 0.2.0         27-Oct-2008     KS         1. Add registering of patch chain during patching
# 0.1.0         23-Oct-2008     KS         1. Add 'LOG' mode: create cbf file and record compilation
#                                             details of the source file
# 0.0.3         24-Sep-2008     KS         1. Ignore input lines that contain with only ';'
# 0.0.2         21-Sep-2008     KS         1. Add treatment of added and removed functions and files
# 0.0.1         15-Aug-2008     KS         1. Iitial version
#-----------------------------------------------------------------------
package PatchMaker::mkpatch;

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
  BogusClone
  GetIndex
  END__CriticalSection
  APOGEE__CriticalSection
  /;

#------------------ Application-wide Variables ---------------
our @ROMSECTIONS   = ();
our %PATCHFUNCLIST = ();
our %CodeCache;
our @ccPtr;
our %States;
our $DEBUG;

# -------------------- This mode constants  ------------------
use constant {
    NEW_FUNCTION     => 100,
    DELETED_FUNCTION => 200,
    COMMON_FUNCTION  => 300,
    CRAWLED_FUNCTION => 400,
};

#-------- Global Variables (needed for Emergency Exit) -------
my %HistoricalPatches = ();
my $CodeCacheFile     = '';

#--------------------- Main i/f Function --------------------
sub MakePatch
  {
    $CodeCacheFile = shift;
    my $CodebaseFolder     = shift;
    my $CodeCacheObject    = shift;
    my $CodeCacheType      = shift;
    my $CodeCacheFolder    = shift;
    my $MakePatchMode      = ( shift or 'PATCH' );
    my $CodeCacheCompiler  = shift;
    my $F_Threshold        = shift;
    my $D_Threshold        = shift;
    my $__reserved         = shift;
    my @PrimaryCompilation = @_;

    #----------------------------------------------------------------
    # 1. read and keep historical info from existing assembly
    #----------------------------------------------------------------
    %HistoricalPatches = ();

    if (
        (
            not $MakePatchMode
            or ( $MakePatchMode eq 'PATCH' or $MakePatchMode eq 'FORCE' )
        )
        and -e $CodeCacheFile
      )
      {
        Panic("Failed to open $CodeCacheFile to read patch history")
          if not open( CACHE, "<$CodeCacheFile" );

        #-----------------------------------------------
        # Record format
        # // PM <patched func> <chain root func> <BUG|called by func>
        # 0  1   2              3                 4
        #-----------------------------------------------
        while ( my $line = readline *CACHE )
          {
            last unless $line =~ /^\/\/ PM /;
            chomp $line;
            my @temp = split( /\s+/, $line );
            next if not $temp[2] or not $temp[3];

            push @{ $HistoricalPatches{ $temp[2] }{ $temp[3] } }, $temp[4];
          }
        close CACHE;

        if ($PatchMaker::globals::DEBUG)
          {
            print "DEBUG :: read Historical Patches:\n";
            &PatchMaker::commons::ShowHash( 1, \%HistoricalPatches );
          }

      }

    #----------------------------------------------------------------
    # 2. compile the file to retreive a new version of code cache file
    #----------------------------------------------------------------
    Error("Compilation of $CodeCacheFile failed")
      if system(@PrimaryCompilation);

    &START__CriticalSection;

    #----------------------------------------------------------------
    # - speacial modes of operation
    #----------------------------------------------------------------
    my $ExtraFlags = '';
    $ExtraFlags = '-flags-asm -g' if $CodeCacheType eq 'ASM';

    if ( $MakePatchMode eq 'SKIP' )
      {
        PatchMaker::commons::END__CriticalSection;

        print
"\"$CodeCacheCompiler\" $ExtraFlags -c -o $CodeCacheObject $CodeCacheFile\n"
          if $PatchMaker::globals::DEBUG;

        Error("Compilation of $CodeCacheFile failed")
          if system(
"\"$CodeCacheCompiler\" $ExtraFlags -c -o $CodeCacheObject $CodeCacheFile"
          );

        return;
      }

    if ( $MakePatchMode eq 'LOG' )
      {
        PatchMaker::commons::END__CriticalSection;

        print "\n\t Log & compile \n\n";

        my $file = basename $CodeCacheFile;
        open( CBF, ">$CodebaseFolder\\$file.cbf" )
          or Panic("Failed to create codebase file $CodebaseFolder\\$file.cbf");

        ( $CodeCache{OBJECT}{NAME} = $CodeCacheObject ) =~
          s/^.+?obj(?:_[^\\\/]+)?[\\\/]//;

        $CodeCache{OBJECT}{EXTRA_FLAGS} = $ExtraFlags;

        $Data::Dumper::Indent = 0;
        print CBF Dumper( \%CodeCache );
        close CBF;

        print
"\"$CodeCacheCompiler\" $ExtraFlags -c -o $CodeCacheObject $CodeCacheFile\n"
          if $PatchMaker::globals::DEBUG;

        Error("Compilation of $CodeCacheFile failed")
          if system(
"\"$CodeCacheCompiler\" $ExtraFlags -c -o $CodeCacheObject $CodeCacheFile"
          );

        return;
      }

    #----------------------------------------------------------------
    # 3. read newly generated code cache file, analize it
    #    and apply direct patches if needed
    #----------------------------------------------------------------
    &InitStates();
    &RomSections($CodebaseFolder);
    &PatchFunctionsList($CodeCacheFolder);

    # Read file, convert it to internal structure
    Panic("Failed to open $CodeCacheFile for analysing")
      if not open( FILE, "<$CodeCacheFile" );

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
            $state = $States{$state}->( $CodeCacheFile, $ll . $end, 'FULL' );
          }
      }
    close FILE;

    $States{'ERROR'}->(
        undef, undef, undef,
        "Unexpected end of file (Probably improper ending of the last function)"
    ) if $state eq 'FUNC_BODY';

    # read image of the original file from codebaser
    my $cbfFile = basename $CodeCacheFile;

    our $VAR1;
    my %CodeCBF = ();
    eval { require "$CodebaseFolder\\$cbfFile.cbf " };
    if ($@)
      {
        print "File $cbfFile is missing in codebase. Assuming a new file\n";
      }
    else
      {
        %CodeCBF = %{$VAR1};
      }
    undef $VAR1;

    my @ChangedFunc     = ();
    my $reWrite         = NO;
    my $updatePatchList = NO;

    my @F_THRESHOLD = split /\s+/, $F_Threshold;
    my @D_THRESHOLD = split /\s+/, $D_Threshold;

    # Compare two structures, changes (if any) will be accumulated in the
    # above array

    # 3.1. build lists of added, common and removed functions
    my %Functions = ();
    foreach my $ccFunc ( keys %{ $CodeCache{FUNCTIONS} } )
      {
        if (
            not grep {
                $CodeCache{FILE}{ $CodeCache{FUNCTIONS}{$ccFunc}[0] }{NAME} eq
                  $_
            } @ROMSECTIONS
          )
          {
            if ( not defined $CodeCBF{FUNCTIONS}{$ccFunc} )
              {
                next;
              }
            else
              {
                $Functions{$ccFunc} = DELETED_FUNCTION;
              }
          }
        else
          {
            if ( defined $CodeCBF{FUNCTIONS}{$ccFunc} )
              {
                if ( $CodeCache{FILE}{ $CodeCache{FUNCTIONS}{$ccFunc}[0] }{NAME}
                    eq $CodeCBF{FILE}{ $CodeCBF{FUNCTIONS}{$ccFunc}[0] }{NAME} )
                  {
                    $Functions{$ccFunc} = COMMON_FUNCTION;
                  }
                else
                  {
                    $Functions{$ccFunc} = CRAWLED_FUNCTION;

                  }
              }
            else
              {
                $Functions{$ccFunc} = NEW_FUNCTION;
              }
          }
      }

    foreach my $cbfFunc ( keys %{ $CodeCBF{FUNCTIONS} } )
      {
        $Functions{$cbfFunc} = DELETED_FUNCTION
          if not defined $CodeCache{FUNCTIONS}{$cbfFunc};
      }

    if ($PatchMaker::globals::DEBUG)
      {
        print "DEBUG :: comparison of functions' list found that:\n";
        &PatchMaker::commons::ShowHash( 1, \%Functions );
      }

  # 3.2 go through all functions (common, new and deleted) and treat accordingly
    foreach my $func ( keys %Functions )
      {

        # Case 1: Same functions - compare bodies
        if (   $Functions{$func} == COMMON_FUNCTION
            or $Functions{$func} == CRAWLED_FUNCTION )
          {
            if ( $Functions{$func} == CRAWLED_FUNCTION )
              {
                $CodeCache{FILE}{ $CodeCache{FUNCTIONS}{$func}[0] }{NAME} =
                  $CodeCBF{FILE}{ $CodeCBF{FUNCTIONS}{$func}[0] }{NAME};

                print "\n" if $reWrite == NO;
                $reWrite = YES;

                print "\tPatch Maker :: taking back crawled function $func\n";
              }

            my $cbfSectIndex   = $CodeCBF{FUNCTIONS}{$func}[0];
            my $cacheSectIndex = $CodeCache{FUNCTIONS}{$func}[0];

            my $cbfFuncIndex   = $CodeCBF{FUNCTIONS}{$func}[1];
            my $cacheFuncIndex = $CodeCache{FUNCTIONS}{$func}[1];

            my $funcChanged = NO;

            if (
                $#{ $CodeCache{FILE}{$cacheSectIndex}{$cacheFuncIndex}{DOCKET} }
                != $#{ $CodeCBF{FILE}{$cbfSectIndex}{$cbfFuncIndex}{DOCKET} }
                or $MakePatchMode eq 'FORCE' )
              {
                push @ChangedFunc, [
                    $CodeCache{FILE},

                    $CodeCBF{FILE}{$cbfSectIndex},
                    $CodeCache{FILE}{$cacheSectIndex},

                    $CodeCBF{FILE}{$cbfSectIndex}{$cbfFuncIndex},
                    $CodeCache{FILE}{$cacheSectIndex}
                      {$cacheFuncIndex},

                    $cacheSectIndex,
                    $cacheFuncIndex,
                ];

                print "\n" if $reWrite == NO;

                $reWrite     = YES;
                $funcChanged = YES;

                if (
                    ( not defined $HistoricalPatches{$func} )
                    or ( defined $HistoricalPatches{$func}
                        and not defined $HistoricalPatches{$func}{$func} )
                    or (    defined $HistoricalPatches{$func}
                        and defined $HistoricalPatches{$func}{$func}
                        and not grep { $_ eq 'BUG' }
                        @{ $HistoricalPatches{$func}{$func} } )
                  )
                  {
                    print "\tPatch Maker :: generating patch for $func\n";

                    push @{ $HistoricalPatches{$func}{$func} }, 'BUG';

                    push @{ $PATCHFUNCLIST{PATCHED} }, $func;
                    $updatePatchList = YES;
                  }
                else
                  {
                    print "\tPatch Maker :: renewing patch for $func\n";
                  }
              }

            # same lengths of dockets - compare lines
            else
              {
                for (
                    my $func_line = 0 ;
                    $func_line <= $#{
                        $CodeCache{FILE}{$cacheSectIndex}{$cacheFuncIndex}
                          {DOCKET}
                    } ;
                    $func_line++
                  )
                  {
                    if (
                        $CodeCache{FILE}{$cacheSectIndex}{$cacheFuncIndex}{BODY}
                        {
                            $CodeCache{FILE}{$cacheSectIndex}{$cacheFuncIndex}
                              {DOCKET}[$func_line]
                        }{LINE} !~
                        $CodeCBF{FILE}{$cbfSectIndex}{$cbfFuncIndex}{BODY}{
                            $CodeCBF{FILE}{$cbfSectIndex}{$cbfFuncIndex}{DOCKET}
                              [$func_line]
                        }{RE}
                      )
                      {
                        push @ChangedFunc, [
                            $CodeCache{FILE},

                            $CodeCBF{FILE}{$cbfSectIndex},
                            $CodeCache{FILE}{$cacheSectIndex},

                            $CodeCBF{FILE}{$cbfSectIndex}{$cbfFuncIndex},
                            $CodeCache{FILE}{$cacheSectIndex}
                              {$cacheFuncIndex},

                            $cacheSectIndex,
                            $cacheFuncIndex,
                        ];

                        print "\n" if $reWrite == NO;

                        $reWrite     = YES;
                        $funcChanged = YES;

                        if (
                            ( not defined $HistoricalPatches{$func} )
                            or ( defined $HistoricalPatches{$func}
                                and not
                                defined $HistoricalPatches{$func}{$func} )
                            or (    defined $HistoricalPatches{$func}
                                and defined $HistoricalPatches{$func}{$func}
                                and not grep { $_ eq 'BUG' }
                                @{ $HistoricalPatches{$func}{$func} } )
                          )
                          {
                            print
                              "\tPatch Maker :: generating patch for $func\n";

                            push @{ $HistoricalPatches{$func}{$func} }, 'BUG';

                            push @{ $PATCHFUNCLIST{PATCHED} }, $func;
                            $updatePatchList = YES;
                          }
                        else
                          {
                            print "\tPatch Maker :: renewing patch for $func\n";
                          }

                        last;
                      }
                  }
              }

            if (    $funcChanged == NO
                and defined $HistoricalPatches{$func}
                and defined $HistoricalPatches{$func}{$func}
                and grep { $_ eq 'BUG' } @{ $HistoricalPatches{$func}{$func} } )
              {
                @{ $HistoricalPatches{$func}{$func} } =
                  grep { $_ ne 'BUG' } @{ $HistoricalPatches{$func}{$func} };

                push @{ $PATCHFUNCLIST{DEPATCHED} }, $func;
                $updatePatchList = YES;
              }
          }

        # Case 2. New function - change section to not ROM section
        elsif ( $Functions{$func} == NEW_FUNCTION )
          {
            $CodeCache{FILE}{ $CodeCache{FUNCTIONS}{$func}[0] }{NAME} =
              $CodeCache{FILE}{ $CodeCache{FUNCTIONS}{$func}[0] }
              { $CodeCache{FUNCTIONS}{$func}[1] }{TYPE} eq 'FUNC'
              ? 'ROM_PATCH_CODE_'
              . &PatchMaker::commons::GetIndex( $func, @F_THRESHOLD )
              : 'ROM_PATCH_DATA_SSI_'
              . &PatchMaker::commons::GetIndex( $func, @D_THRESHOLD );

            $CodeCache{FILE}{ $CodeCache{FUNCTIONS}{$func}[0] }{MEMORY} =
              'SRAM';

            print "\n" if $reWrite == NO;
            $reWrite = YES;

            print "\tPatch Maker :: registering new function $func\n";
          }

        # Case 3. Deleted function - bring it back rename to _BUG
        # create speciall stub with the same name
        elsif ( $Functions{$func} == DELETED_FUNCTION )
          {
            print "\n" if $reWrite == NO;
            $reWrite = YES;

            if (
                ( not defined $HistoricalPatches{$func} )
                or ( defined $HistoricalPatches{$func}
                    and not defined $HistoricalPatches{$func}{$func} )
                or (    defined $HistoricalPatches{$func}
                    and defined $HistoricalPatches{$func}{$func}
                    and not grep { $_ eq 'BUG' }
                    @{ $HistoricalPatches{$func}{$func} } )
              )
              {
                push @{ $HistoricalPatches{$func}{$func} }, 'BUG';

                push @{ $PATCHFUNCLIST{PATCHED} }, $func;
                $updatePatchList = YES;
              }

            print
              "\tPatch Maker :: making bogus copy of deleted function $func\n";

            my $bugFunc = $func . '_BUG';

            # -- Restore Section & function
            $CodeCache{FILE}{__sectcntr__}++;
            my $newSection = 'S-' . $CodeCache{FILE}{__sectcntr__};

            $CodeCache{FILE}{$newSection}{NAME} =
              $CodeCBF{FILE}{ $CodeCBF{FUNCTIONS}{$func}[0] }{NAME};
            $CodeCache{FILE}{$newSection}{MEMORY}   = 'ROM';
            $CodeCache{FILE}{$newSection}{__line__} = 0;

            $CodeCache{FILE}{$newSection}{__line__}++;
            $CodeCache{FILE}{$newSection}{'F-1'} = {};

            # Restore deleted function
            &PatchMaker::commons::BogusClone(
                $CodeCBF{FILE}{ $CodeCBF{FUNCTIONS}{$func}[0] }
                  { $CodeCBF{FUNCTIONS}{$func}[1] },
                $CodeCache{FILE}{$newSection}{'F-1'},
                defined $CodeCBF{FILE}{ $CodeCBF{FUNCTIONS}{$func}[0] }
                  { $CodeCBF{FUNCTIONS}{$func}[1] }{LABELS}
                ? \$CodeCBF{FILE}{ $CodeCBF{FUNCTIONS}{$func}[0] }
                  { $CodeCBF{FUNCTIONS}{$func}[1] }{LABELS}
                : ''
            );

            # -- Rename old Function
            foreach my $f_line (
                keys %{ $CodeCache{FILE}{$newSection}{'F-1'}{TAIL} } )
              {
                $CodeCache{FILE}{$newSection}{'F-1'}{TAIL}{$f_line} =~
                  s/$func/$bugFunc/;
              }
            $CodeCache{FILE}{$newSection}{'F-1'}{NAME} = $bugFunc;
            $CodeCache{FILE}{$newSection}{'F-1'}{GLOBAL} =~ s/$func/$bugFunc/
              if defined $CodeCache{FILE}{$newSection}{'F-1'}{GLOBAL};

            $CodeCache{FUNCTIONS}{$bugFunc} = [ $newSection, 'F-1' ];

            # -- Create a stub (only if the function has suffix _AdpLyr)
            if ( $func =~ /_AdpLyr$/ )
              {
                if ( $CodeCBF{FILE}{ $CodeCBF{FUNCTIONS}{$func}[0] }
                    { $CodeCBF{FUNCTIONS}{$func}[1] }{TYPE} eq 'FUNC' )
                  {
                    $CodeCache{FILE}{__sectcntr__}++;
                    my $stubSection = 'S-' . $CodeCache{FILE}{__sectcntr__};
                    $CodeCache{FILE}{$stubSection}{NAME} =
                      'ROM_PATCH_CODE_'
                      . &PatchMaker::commons::GetIndex( $func, @F_THRESHOLD );
                    $CodeCache{FILE}{$stubSection}{MEMORY}      = 'SRAM';
                    $CodeCache{FILE}{$stubSection}{'L-1'}       = '.ALIGN 2;';
                    $CodeCache{FILE}{$stubSection}{'F-2'}{NAME} = $func;
                    $CodeCache{FILE}{$stubSection}{'F-2'}{BODY}{'L-1'}{LINE} =
'// This function was made by the ROM automatic environment';
                    $CodeCache{FILE}{$stubSection}{'F-2'}{BODY}{'L-2'}{LINE} =
                      'CALL _MainFatalErrorIDNewDeletedFunctionIsCalled;';
                    $CodeCache{FILE}{$stubSection}{'F-2'}{TAIL}{'T-3'} =
                      ".GLOBAL $func;";
                    $CodeCache{FILE}{$stubSection}{'F-2'}{TAIL}{'T-4'} =
                      ".TYPE $func, STT_FUNC;";
                    $CodeCache{FILE}{$stubSection}{'F-2'}{__line__} = 4;
                    $CodeCache{FILE}{$stubSection}{__line__} = 2;
                  }
              }
          }
      }

    # 3.3 go through all changed objects (functions and data) and make patches
    foreach my $cf (@ChangedFunc)
      {
        &PatchMaker::commons::CloneFunction( $cf, \%CodeCache, \@F_THRESHOLD,
            \@D_THRESHOLD );
      }

    #----------------------------------------------------------------
    # 4. apply chain patches recorded in historical notes
    #----------------------------------------------------------------
    if ($PatchMaker::globals::DEBUG)
      {
        print "DEBUG :: after functions comparison Historical Patches are:\n";
        &PatchMaker::commons::ShowHash( 1, \%HistoricalPatches );
      }

    my @ChainRepatching = ();
    foreach my $chain_func ( keys %HistoricalPatches )
      {
        my @chain_func = ();
        foreach my $root_func ( keys %{ $HistoricalPatches{$chain_func} } )
          {
            my @partial_chain =
              grep { $_ ne 'BUG' }
              @{ $HistoricalPatches{$chain_func}{$root_func} };

            push @chain_func, @partial_chain if @partial_chain;
          }
        next if not @chain_func;

        my %_uniq = ();
        @_uniq{@chain_func} = 1;
        @chain_func = keys %_uniq;

        my $reTemp         = join( "|", @chain_func );
        my $reChainFunc    = qr/$reTemp/;
        my $patch_func_msg = NO;
        my $funcList       = join( ",", @chain_func );

        if ( defined $CodeCache{FUNCTIONS}{ $chain_func . '_BUG' } )
          {
            my $cacheSectIndex =
              $CodeCache{FUNCTIONS}{ $chain_func . '_BUG' }[0];
            my $cacheFuncIndex =
              $CodeCache{FUNCTIONS}{ $chain_func . '_BUG' }[1];

            foreach my $l (
                keys
                %{ $CodeCache{FILE}{$cacheSectIndex}{$cacheFuncIndex}{BODY} } )
              {
                my $count =
                  $CodeCache{FILE}{$cacheSectIndex}{$cacheFuncIndex}{BODY}{$l}
                  {LINE} =~ s/\b($reChainFunc)\b/$1_BUG/g;

                $patch_func_msg = $reWrite = YES if $count;
              }
          }
        elsif ( defined $CodeCache{FUNCTIONS}{$chain_func} )
          {
            my $cacheSectIndex = $CodeCache{FUNCTIONS}{$chain_func}[0];
            my $cacheFuncIndex = $CodeCache{FUNCTIONS}{$chain_func}[1];

            my $cbfSectIndex = $CodeCBF{FUNCTIONS}{$chain_func}[0];
            my $cbfFuncIndex = $CodeCBF{FUNCTIONS}{$chain_func}[1];

            push @ChainRepatching, [
                $CodeCache{FILE},

                $CodeCBF{FILE}{$cbfSectIndex},
                $CodeCache{FILE}{$cacheSectIndex},

                $CodeCBF{FILE}{$cbfSectIndex}{$cbfFuncIndex},
                $CodeCache{FILE}{$cacheSectIndex}
                  {$cacheFuncIndex},

                $cacheSectIndex,
                $cacheFuncIndex,

                $reChainFunc,
            ];

            $patch_func_msg = $reWrite = YES;
          }

        print
"\tPatch Maker :: restore chain patching of $chain_func for $funcList\n"
          if $patch_func_msg == YES;
      }

    foreach my $cf (@ChainRepatching)
      {
        &PatchMaker::commons::CloneFunction( $cf, \%CodeCache, \@F_THRESHOLD,
            \@D_THRESHOLD );
      }

    #----------------------------------------------------------------
    # 5. overwrite assembly source with the patched one
    #    (including updated historical records)
    #----------------------------------------------------------------

    # fully disable any attempts to interrupt execution
    # intraption will be enabled at any case by unconditional
    # END_CriticalSection below
    PatchMaker::commons::APOGEE__CriticalSection;

    # 5.1 Write the assembly
    if ( $reWrite == YES )
      {
        print "\tPatch Maker :: writing patched file\n";
        &PatchMaker::commons::WriteCacheFile( $CodeCacheFile, \%CodeCache,
            \%CodeCBF, \%HistoricalPatches );
        print "\n";
      }

    # 5.2 update current patch/depatch func list
    if ( $updatePatchList == YES )
      {

        open( PATCH,
                ">$CodeCacheFolder\\"
              . PatchMaker::globals::PATCHFUNCLIST_FILE
              . ".cbf" )
          or Panic("Failed to create Patch Functions List file");

        $Data::Dumper::Indent = 2;
        print PATCH Dumper( \%PATCHFUNCLIST );

        close PATCH;

        if ($PatchMaker::globals::DEBUG)
          {
            print "DEBUG :: PATCH FUNC LIST updated\n";
          }
      }

    PatchMaker::commons::END__CriticalSection;

    #----------------------------------------------------------------
    # 6. compile final assembly file to obtain object file
    #----------------------------------------------------------------
    print
"\"$CodeCacheCompiler\" $ExtraFlags -c -o $CodeCacheObject $CodeCacheFile\n"
      if $PatchMaker::globals::DEBUG;

    Error("Compilation of $CodeCacheFile failed")
      if system(
"\"$CodeCacheCompiler\" $ExtraFlags -c -o $CodeCacheObject $CodeCacheFile"
      );
  }

sub EmergencyExit
  {
    PatchMaker::commons::APOGEE__CriticalSection;

    if ( $CodeCacheFile and open( CACHE, "<$CodeCacheFile" ) )
      {
        print
"PATCH MAKER EMERGENCY :: Will Restore Historical Patches from $CodeCacheFile\n";
        my @cc_file = <CACHE>;

        foreach my $fc ( keys %HistoricalPatches )
          {
            foreach my $fr ( keys %{ $HistoricalPatches{$fc} } )
              {
                foreach my $p ( @{ $HistoricalPatches{$fc}{$fr} } )
                  {
                    print CACHE "// PM $fc $fr $p\n";
                  }
              }
          }
        print CACHE @cc_file;
        close CACHE;
      }
    else
      {
        print "PATCH MAKER EMERGENCY :: "
          . "Failed to restore historical patches for $CodeCacheFile. "
          . "CONSIDER REBUILD IF SOMETHING GOES WRONG\n"
          if $CodeCacheFile;
      }

    exit 0;
  }

sub START__CriticalSection
  {
    $SIG{INT}  = \&EmergencyExit;
    $SIG{QUIT} = \&EmergencyExit;
  }

#-----------------------------------------------------
1;
