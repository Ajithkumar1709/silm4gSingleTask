#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# Patch Maker Service Library
#
# Compare map files and report patch penalty
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 1.3.0         05-Oct-2011     KS         1. filter out previously manuall patched finctions from report
# 1.2.0         18-Oct-2009     KS         1. Out Folder parameter is now a name of out file
# 1.1.0         08-Sep-2009     KS         1. Fix an issue with calculation of sizes of patched functions
#                                          2. Include 'HW Hooks' in comparison report
# 1.0.0         09-Jun-2009     KS         1. Allow setting final table proportions from
#                                             command line
# 0.1.0         27-May-2009     KS         1. Change output format
#                                          2. Write report also in text file
# 0.0.1         26-May-2009     KS         Iitial version
#-----------------------------------------------------------------------
package PatchMaker::compare;

#use lib '\env\win32\tools\src';

use strict;
use warnings;

use PatchMaker::globals;

use PatchMaker::commons qw/
  ShowHash
  ShowArray
  /;

#------------------ Application-wide Variables---------------

#--------------------- Main i/f Function --------------------
sub CompareMaps
  {
    my $CurrentMap   = shift;
    my $BaselineMap  = shift;
    my $CriticalSize = shift;
    my @Args         = @_;

    my $CodeCacheFolder = '';
    my $CodebaseFolder  = '';
    my $OutFile         = '';
    my $Metric1         = 0;
    my $Metric2         = 0;

    ( $CodeCacheFolder, $CodebaseFolder, $OutFile, $Metric1, $Metric2 ) = @Args
      if scalar @Args == 5;

    ( $CodeCacheFolder, $CodebaseFolder, $Metric1, $Metric2 ) = @Args
      if scalar @Args == 4
          and $Args[2] =~ /^[\d\.]+$/
          and $Args[3] =~ /^[\d\.]+$/;

    ( $CodeCacheFolder, $CodebaseFolder, $OutFile, $Metric1 ) = @Args
      if scalar @Args == 4
          and $Args[2] !~ /^[\d\.]+$/
          and $Args[3] =~ /^[\d\.]+$/;

    ( $CodeCacheFolder, $Metric1, $Metric2 ) = @Args
      if scalar @Args == 3
          and $Args[1] =~ /^[\d\.]+$/
          and $Args[2] =~ /^[\d\.]+$/;
    ( $CodeCacheFolder, $CodebaseFolder, $OutFile ) = @Args
      if scalar @Args == 3
          and $Args[1] !~ /^[\d\.]+$/
          and $Args[2] !~ /^[\d\.]+$/;
    ( $CodeCacheFolder, $CodebaseFolder, $Metric1 ) = @Args
      if scalar @Args == 3
          and $Args[1] =~ /^[\d\.]+$/
          and $Args[2] !~ /^[\d\.]+$/;

    ( $CodeCacheFolder, $CodebaseFolder ) = @Args
      if scalar @Args == 2
          and $Args[0] !~ /^[\d\.]+$/
          and $Args[1] !~ /^[\d\.]+$/;
    ( $Metric1, $Metric2 ) = @Args
      if scalar @Args == 2
          and $Args[0] =~ /^[\d\.]+$/
          and $Args[1] =~ /^[\d\.]+$/;
    ( $CodeCacheFolder, $Metric1 ) = @Args
      if scalar @Args == 2
          and $Args[0] !~ /^[\d\.]+$/
          and $Args[1] =~ /^[\d\.]+$/;

    ($CodeCacheFolder) = @Args if scalar @Args == 1 and $Args[0] !~ /^[\d\.]+$/;
    ($Metric1) = @Args if scalar @Args == 1 and $Args[0] =~ /^[\d\.]+$/;

    my $FuncNameLength = 28;
    my $ReasonLength   = 42;

    if ( $Metric1 and not $Metric2 )
      {
        $FuncNameLength = int( $Metric1 * 0.35 );
        $ReasonLength = $Metric1 - ( $FuncNameLength + 4 + 1 + 4 + 4 );

        #----------------------------------         # of | ACTION ROM SRAM
      }
    elsif ( $Metric1 and $Metric2 )
      {
        $FuncNameLength = $Metric1;
        $ReasonLength   = $Metric2;
      }

    my $TableLength = $FuncNameLength + $ReasonLength + 4 + 1 + 4 + 4;

    open( MAP, "<$BaselineMap" ) or Error("Failed to open $BaselineMap");
    my @BaselineMap = sort { $a cmp $b }
      map { my @a = split /\s+/, $_; $a[0] }
      grep { my @a = $_ ? split /\s+/ : (); $a[0] ? $a[0] =~ /_BUG$/ : 0 }
      <MAP>;
    close MAP;

    open( MAP, "<$CurrentMap" ) or Error("Failed to open $CurrentMap");
    my @CurrentMap = sort { $a cmp $b }
      map { my @a = split /\s+/; $a[0] }
      grep { my @a = $_ ? split /\s+/ : (); $a[0] ? $a[0] =~ /_BUG$/ : 0 }
      <MAP>;
    close MAP;

    open( MAP, "<$BaselineMap" ) or Error("Failed to open $BaselineMap");
    my @PreviousManuallyPatched = sort { $a cmp $b }
      grep {
        my @a = $_ ? split /\s+/ : ();
        $a[0] ? $a[0] =~ /_ManualPatch$/ : 0
      } <MAP>;
    close MAP;

    open( MAP, "<$CurrentMap" ) or Error("Failed to open $CurrentMap");
    my @ManuallyPatched = sort { $a cmp $b }
      grep {
        my @a = $_ ? split /\s+/ : ();
        $a[0]
          ? (
            $a[0] =~ /_ManualPatch$/ and not grep /\Q$a[0]\E/,
            @PreviousManuallyPatched
          )
          : 0
      } <MAP>;
    close MAP;

    my @DePatched = grep {
        my $f = $_;
        not grep { $_ eq $f } @CurrentMap
    } @BaselineMap;

    my @Patched = grep {
        my $f = $_;
        not grep { $_ eq $f } @BaselineMap
    } @CurrentMap;

    my $rePurePatched = join "|", map { $_ =~ s/_BUG//; "\\b$_\\b" } @Patched;
    my $rePureDePatched = join "|",
      map { $_ =~ s/_BUG//; "\\b$_\\b" } @DePatched;

    open( MAP, "<$CurrentMap" ) or Error("Failed to open $CurrentMap");
    my @PatchedSizes = grep /(?:$rePurePatched)(?!\.end)/, <MAP>;
    close MAP;

    open( MAP, "<$BaselineMap" ) or Error("Failed to open $BaselineMap");
    my @DepatchedSizes = grep /(?:$rePureDePatched)(?!\.end)/, <MAP>;
    close MAP;

    my $TotalPenalty = 0;
    my $PatchPenalty = 0;
    my $PatchGain    = 0;

    my %RomPatchPenalty = ();
    our $VAR1;
    eval { require "$CodebaseFolder\\RomPatchPenalty.cbf " };
    if ($@)
      {
        Warning(" File RomPatchPenalty.cbf is missing in Codebase");
      }
    else
      {
        %RomPatchPenalty = %{$VAR1};
      }
    undef $VAR1;

    my %RomFuncList = ();
    eval { require "$CodebaseFolder\\RomFuncList.cbf " };
    if ($@)
      {
        Warning("File RomFuncList.cbf is missing in Codebase");
      }
    else
      {
        %RomFuncList = %{$VAR1};
      }
    undef $VAR1;

    my %Report = ();
    foreach my $func (@Patched)
      {
        my $real_func = $func;
        $real_func =~ s/_BUG$//;

        $Report{$real_func}{ACTION}      = 'PATCHED';
        $Report{$real_func}{SIZE}{ROM}   = 0;
        $Report{$real_func}{SIZE}{SRAM}  = 0;
        $Report{$real_func}{SIZE}{TOTAL} = 0;
        if ( defined $RomPatchPenalty{$real_func} )
          {
            $Report{$real_func}{SIZE}{ROM} = $RomPatchPenalty{$real_func}{SELF};
            $Report{$real_func}{SIZE}{TOTAL} =
              $RomPatchPenalty{$real_func}{TOTAL};
          }
        else
          {
            Warning(
                "Function $real_func is missing in ROM Patch Penalty table");
          }

        my @mapLine = grep /$real_func/, @PatchedSizes;
        if ( $mapLine[0] )
          {
            my @funcLine = split /\s+/, $mapLine[0];

            $Report{$real_func}{SIZE}{SRAM} = hex( $funcLine[2] )
              if $funcLine[2] and $funcLine[2] =~ /[0-9a-fx]+/i;
          }

        $PatchPenalty += $Report{$real_func}{SIZE}{SRAM};

        if ( defined $RomFuncList{$real_func} )
          {

            my %HistoricalPatches = ();
            if ( open( CACHE, "<$CodeCacheFolder\\$RomFuncList{$real_func}" ) )
              {

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

                    push @{ $HistoricalPatches{ $temp[2] }{ $temp[3] } },
                      $temp[4];
                  }
                close CACHE;

                if ( defined $HistoricalPatches{$real_func} )
                  {
                    foreach
                      my $f_reason ( keys %{ $HistoricalPatches{$real_func} } )
                      {
                        push @{ $Report{$real_func}{REASON} }, 'CHANGED'
                          if $f_reason eq $real_func;
                        push @{ $Report{$real_func}{REASON} }, $f_reason
                          if $f_reason ne $real_func;
                      }
                  }
                else
                  {
                    Warning(
                        "Historical record for finction $real_func not found");
                    @{ $Report{$real_func}{REASON} } = ();
                  }
              }
            else
              {
                Warning(
"Failed to open $CodeCacheFolder\\$RomFuncList{$real_func} to read patch history"
                );
                @{ $Report{$real_func}{REASON} } = ();
              }

          }
        else
          {
            Warning("Function $real_func is missing in ROM Funtions list");
            @{ $Report{$real_func}{REASON} } = ();
          }

      }

    foreach my $func (@DePatched)
      {
        my $real_func = $func;
        $real_func =~ s/_BUG$//;

        $Report{$real_func}{ACTION} = 'DE-PATCHED';
        @{ $Report{$real_func}{REASON} } = ();

        $Report{$real_func}{SIZE}{ROM}   = 0;
        $Report{$real_func}{SIZE}{TOTAL} = 0;
        if ( defined $RomPatchPenalty{$real_func} )
          {
            $Report{$real_func}{SIZE}{ROM} = $RomPatchPenalty{$real_func}{SELF};
            $Report{$real_func}{SIZE}{TOTAL} =
              $RomPatchPenalty{$real_func}{TOTAL};
          }
        else
          {
            Warning(
                "Function $real_func is missing in ROM Patch Penalty table");
          }

        my @mapLine = grep /$real_func/, @DepatchedSizes;
        if ( $mapLine[0] )
          {
            my @funcLine = split /\s+/, $mapLine[0];

            $Report{$real_func}{SIZE}{SRAM} = hex( $funcLine[2] )
              if $funcLine[2] and $funcLine[2] =~ /[0-9a-fx]+/i;
          }

        $PatchGain += ( $Report{$real_func}{SIZE}{SRAM} or 0 );

      }

    foreach my $info (@ManuallyPatched)
      {
        my @info = split /\s+/, $info;
        my $real_func = $info[0];
        $real_func =~ s/_ManualPatch$//;

        $Report{$real_func}{ACTION} = 'MANUALLY PATCHED';
        @{ $Report{$real_func}{REASON} } = ();
        $Report{$real_func}{SIZE}{ROM}   = 0;
        $Report{$real_func}{SIZE}{SRAM}  = 0;
        $Report{$real_func}{SIZE}{TOTAL} = 0;
        if ( defined $RomPatchPenalty{$real_func} )
          {
            $Report{$real_func}{SIZE}{ROM} = $RomPatchPenalty{$real_func}{SELF};
            $Report{$real_func}{SIZE}{TOTAL} =
              $RomPatchPenalty{$real_func}{SELF};
          }
        else
          {
            Warning(
                "Function $real_func is missing in ROM Patch Penalty table");
          }

        $Report{$real_func}{SIZE}{SRAM} = hex( $info[2] )
          if $info[2] and $info[2] =~ /[0-9a-fx]+/i;

        $PatchPenalty += $Report{$real_func}{SIZE}{SRAM};
      }

    my %Recommendation = ();
    foreach my $func ( keys %Report )
      {
        $Recommendation{ $Report{$func}{REASON}[0] } +=
          ( $Report{$func}{SIZE}{SRAM} or 0 )
          if scalar @{ $Report{$func}{REASON} } == 1
              and $Report{$func}{REASON}[0] ne 'CHANGED';
      }

    my $Recommendation = '';
    foreach my $chain_root ( keys %Recommendation )
      {
        $Recommendation .=
"$chain_root may be consider as HW hook candidate - exclusive patch size $Recommendation{$chain_root}\n"
          if $Recommendation{$chain_root} >= $CriticalSize;
      }

    $TotalPenalty = $PatchPenalty - $PatchGain;

    my $TableLine = '-' x $TableLength;
    my $TableHeader =
      'FUNC' . ( ' ' x ( $FuncNameLength - 4 ) ) . '|A|ROM |SRAM|REASON';

    print "\n\nROM Patch Comparison Report\n";
    print <<REPORT_HEADER;
$TableLine
$TableHeader
$TableLine
REPORT_HEADER

    if ( not %Report )
      {
        print "    NONE\n";
      }
    else
      {
        foreach my $func ( keys %Report )
          {
            my $line = "";
            if ( length $func <= $FuncNameLength )
              {
                $line .= $func . ( " " x ( $FuncNameLength - length $func ) );
              }
            else
              {
                my $abbrev = substr( $func, 0, $FuncNameLength - 3 ) . '...';
                $line .= $abbrev;
              }

            $line .= "|";
            $line .= '+' if $Report{$func}{ACTION} eq 'PATCHED';
            $line .= '-' if $Report{$func}{ACTION} eq 'DE-PATCHED';
            $line .= '~' if $Report{$func}{ACTION} eq 'MANUALLY PATCHED';
            $line .= "|";
            $line .=
              $Report{$func}{SIZE}{ROM}
              . ( ' ' x ( 4 - length $Report{$func}{SIZE}{ROM} ) );
            $line .= "|";
            $line .=
              ( $Report{$func}{SIZE}{SRAM} or '' )
              . (
                ' ' x ( 4 - length( ( $Report{$func}{SIZE}{SRAM} or '' ) ) ) );
            $line .= "|";

            my $reason = join( ",", @{ $Report{$func}{REASON} } );
            if ( length $reason <= $ReasonLength )
              {
                $line .= $reason . ( " " x ( $ReasonLength - length $reason ) );
              }
            else
              {
                my $abbrev = substr( $reason, 0, $ReasonLength - 3 ) . '...';
                $line .= $abbrev;
              }
            $line .= "\n";

            print $line;
          }
      }

    print <<REPORT_FOOTER;
$TableLine
TOTAL PATCHED/DE-PATCHED :: $TotalPenalty Bytes
$Recommendation
REPORT_FOOTER

    if ( defined $OutFile )
      {

        # Prepare CSV Report
        if ( open( CSV, ">$OutFile.csv" ) )
          {
            print CSV "FUNC,ACTION,ROM,SRAM,REASON\n";
            if ( not %Report )
              {
                print CSV "NONE\n";
              }
            else
              {
                foreach my $func ( keys %Report )
                  {
                    my $line = "$func,";
                    $line .= $Report{$func}{ACTION} . ",";
                    $line .= $Report{$func}{SIZE}{ROM} . ",";
                    $line .= ( $Report{$func}{SIZE}{SRAM} or '' ) . ",";
                    my $reason = join( ",", @{ $Report{$func}{REASON} } );
                    $line .= "\"$reason\"";

                    print CSV $line . "\n";
                  }
              }

            print CSV "\nTOTAL PATCHED/DE-PATCHED :: $TotalPenalty Bytes\n";
            print CSV "$Recommendation\n";
            close CSV;
          }
        else
          {
            Warning("Failed to write to $OutFile.csv");
          }

        #Prepare text report
        if ( open( TXT, ">$OutFile.txt" ) )
          {

            print TXT "ROM Patch Comparison Report\n";
            print TXT <<TXT_REPORT_HEADER;
-----------------------------------------------------------------------------------------------------------------------------
| FUNC                                     | ACTION           | ROM  | SRAM | REASON
-----------------------------------------------------------------------------------------------------------------------------
TXT_REPORT_HEADER

            if ( not %Report )
              {
                print TXT "    NONE\n";
              }
            else
              {
                foreach my $func ( keys %Report )
                  {
                    my $line = "| ";
                    if ( length $func <= 40 )
                      {
                        $line .= $func . ( " " x ( 40 - length $func ) );
                      }
                    else
                      {
                        my $abbrev = substr( $func, 0, 37 ) . '...';
                        $line .= $abbrev;
                      }

                    $line .= " | ";
                    $line .= $Report{$func}{ACTION};
                    $line .= '         ' if $Report{$func}{ACTION} eq 'PATCHED';
                    $line .= '      ' if $Report{$func}{ACTION} eq 'DE-PATCHED';
                    $line .= " | ";
                    $line .=
                      $Report{$func}{SIZE}{ROM}
                      . ( ' ' x ( 6 - length $Report{$func}{SIZE}{ROM} ) );
                    $line .= " | ";
                    $line .=
                      ( $Report{$func}{SIZE}{SRAM} or '' )
                      . (
                        ' ' x ( 6 - length( $Report{$func}{SIZE}{SRAM} or '' ) )
                      );
                    $line .= " | ";

                    my $reason = join( ",", @{ $Report{$func}{REASON} } );
                    $line .= $reason;
                    $line .= "\n";

                    print TXT $line;
                  }
              }

            print TXT <<TXT_REPORT_FOOTER;
-----------------------------------------------------------------------------------------------------------------------------
TOTAL PATCHED/DE-PATCHED :: $TotalPenalty Bytes
$Recommendation
TXT_REPORT_FOOTER

            close TXT;
          }
        else
          {
            Warning("Failed to write to $OutFile.txt");
          }
      }
  }

#-----------------------------------------------------
1;
