#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# Patch Maker Service Library
#
# Common swervices for all Patch Maker working modes
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 1.2.0         23-Feb-2009     KS         1. Add GetIndex function (to support)
#                                             threshold mechanism
# 1.1.0         15-Feb-2009     KS         1. Add DumpArray function
#
# 1.0.0         09-Feb-2009     KS         Official Release
#
# 0.0.2         14-Dec-2008     KS         1. Make a public alias for private _bogusClone
# 0.0.1         30-Nov-2008     KS         1. Iitial version
#-----------------------------------------------------------------------
package PatchMaker::commons;

use lib '\env\win32\tools\src';

use strict;
use warnings;

use Data::Dumper;

use PatchMaker::globals;

#--------------------- Main i/f Function --------------------
sub CloneFunction
  {
    my $cf = shift;
    my $CC = shift;
    my $FTHR = shift;
    my $DTHR = shift;

    my $BugFuncName = $cf->[3]{NAME} . '_BUG';
    my $FuncName    = $cf->[3]{NAME};

    # -- Open a new section
    $cf->[0]{__sectcntr__}++;
    my $newSection = 'S-' . $cf->[0]{__sectcntr__};
    $cf->[0]{$newSection}{NAME} =
      $cf->[4]{TYPE} eq 'FUNC'
      ? 'ROM_PATCH_CODE_' . GetIndex( $FuncName, @$FTHR )
      : 'ROM_PATCH_DATA_SSI_' . GetIndex( $FuncName, @$DTHR );
    $cf->[0]{$newSection}{MEMORY}   = 'SRAM';
    $cf->[0]{$newSection}{__line__} = 0;

    if ( $cf->[4]{ALIGN} )
      {
        $cf->[0]{$newSection}{__line__}++;
        $cf->[0]{$newSection}{ 'L-' . $cf->[0]{$newSection}{__line__} } =
          $cf->[4]{ALIGN};
      }
    if ( $cf->[4]{GLOBAL} )
      {
        $cf->[0]{$newSection}{__line__}++;
        $cf->[0]{$newSection}{ 'L-' . $cf->[0]{$newSection}{__line__} } =
          $cf->[4]{GLOBAL};
      }

    # -- Copy new function to new section
    $cf->[0]{$newSection}{__line__}++;
    $cf->[0]{$newSection}{ 'F-' . $cf->[0]{$newSection}{__line__} } = {};
    _cleanClone( $cf->[4],
        $cf->[0]{$newSection}{ 'F-' . $cf->[0]{$newSection}{__line__} } );

    # -- Register new function. It shoould rewrite data about this function
    $CC->{FUNCTIONS}{$FuncName} =
      [ 'S-' . $cf->[0]{__sectcntr__}, 'F-' . $cf->[0]{$newSection}{__line__} ];

    # -- Restore old Function
    $cf->[2]{ $cf->[6] } = {};
    _bogusClone(
        $cf->[3],
        $cf->[2]{ $cf->[6] },
        defined $cf->[3]{LABELS} ? \$cf->[3]{LABELS} : '',
        defined $cf->[7]         ? \$cf->[7]         : undef
    );
    $cf->[4] = $cf->[2]{ $cf->[6] };

    # -- Rename old Function
    foreach my $f_line ( keys %{ $cf->[4]{TAIL} } )
      {
        $cf->[4]{TAIL}{$f_line} =~ s/$FuncName/$BugFuncName/;
      }
    $cf->[4]{NAME} = $BugFuncName;
    $cf->[4]{GLOBAL} =~ s/$FuncName/$BugFuncName/ if $cf->[4]{GLOBAL};

    foreach my $s_line ( keys %{ $cf->[2] } )
      {
        next if ref $cf->[2]{$s_line};
        $cf->[2]{$s_line} =~ s/$FuncName/$BugFuncName/;
      }

    # -- Register old, renamed function
    $CC->{FUNCTIONS}{$BugFuncName} = [ $cf->[5], $cf->[6] ];

  }

sub WriteCacheFile
  {
    my $CodeCacheFile = shift;
    my $CC            = shift;
    my $CBF           = shift;
    my $HP            = shift;

    if ($PatchMaker::globals::DEBUG)
      {
        my $bakCount = 1;
        while ( -f "$CodeCacheFile.bak$bakCount" ) { $bakCount++ }
        require File::Copy;
        File::Copy::copy( $CodeCacheFile, "$CodeCacheFile.bak$bakCount" )
          or carp("Failed to make a 'bak' copy for $CodeCacheFile");
      }

    # Rewrite file
    Panic("Failed to open $CodeCacheFile for updating")
      if not open( FILE, ">$CodeCacheFile" );

    # write special header that will keep historical patches
    foreach my $fc ( keys %$HP )
      {
        foreach my $fr ( keys %{ $HP->{$fc} } )
          {
            foreach my $p ( @{ $HP->{$fc}{$fr} } )
              {
                print FILE "// PM $fc $fr $p\n";
              }
          }
      }

    print FILE ".FILE \"$CC->{FILE}{NAME}\";\n";

    # First - write ROM functions
    foreach my $romFunc ( @{ $CBF->{FUNCLIST} } )
      {
        my $sect = '';
        my $func = '';
        if (
            defined $CC->{FUNCTIONS}{ $romFunc . '_BUG' }
            and (
                not
                defined $CC->{FILE}{ $CC->{FUNCTIONS}{ $romFunc . '_BUG' }[0] }
                { $CC->{FUNCTIONS}{ $romFunc . '_BUG' }[1] }{SKIP}
                or (
                    defined $CC->{FILE}
                    { $CC->{FUNCTIONS}{ $romFunc . '_BUG' }[0] }
                    { $CC->{FUNCTIONS}{ $romFunc . '_BUG' }[1] }{SKIP}
                    and $CC->{FILE}{ $CC->{FUNCTIONS}{ $romFunc . '_BUG' }[0] }
                    { $CC->{FUNCTIONS}{ $romFunc . '_BUG' }[1] }{SKIP} != 1 )
            )
          )
          {
            $sect = $CC->{FUNCTIONS}{ $romFunc . '_BUG' }[0];
            $func = $CC->{FUNCTIONS}{ $romFunc . '_BUG' }[1];
          }
        elsif ( defined $CC->{FUNCTIONS}{$romFunc} )
          {
            $sect = $CC->{FUNCTIONS}{$romFunc}[0];
            $func = $CC->{FUNCTIONS}{$romFunc}[1];
          }
        else
          {
            Error("$romFunc found in Codebase but absent in assembly");
          }

        print FILE ".SECTION " . $CC->{FILE}{$sect}{NAME} . ";\n";
        print FILE "$CC->{FILE}{$sect}{$func}{ALIGN}\n"
          if defined $CC->{FILE}{$sect}{$func}{ALIGN};
        print FILE "$CC->{FILE}{$sect}{$func}{GLOBAL}\n"
          if defined $CC->{FILE}{$sect}{$func}{GLOBAL};
        print FILE "$CC->{FILE}{$sect}{$func}{NAME}:\n";

        my $inBody = 1;
        for ( my $k = 1 ; $k <= $CC->{FILE}{$sect}{$func}{__line__} ; $k++ )
          {
            if ( defined $CC->{FILE}{$sect}{$func}{BODY}{ 'L-' . $k } )
              {
                print FILE "$CC->{FILE}{$sect}{$func}{BODY}{'L-' . $k}{LINE}\n";
              }
            elsif ( defined $CC->{FILE}{$sect}{$func}{TAIL}{ 'T-' . $k } )
              {
                if ($inBody)
                  {
                    print FILE ".$CC->{FILE}{$sect}{$func}{NAME}.end:\n";
                    $inBody = 0;
                  }
                print FILE "$CC->{FILE}{$sect}{$func}{TAIL}{'T-' . $k}\n";
              }
          }
        print FILE ".$CC->{FILE}{$sect}{$func}{NAME}.end:\n"
          if $inBody;
      }

    # Second - write all the rest
    for ( my $i = 1 ; $i <= $CC->{FILE}{__sectcntr__} ; $i++ )
      {
        next if $CC->{FILE}{ 'S-' . $i }{MEMORY} eq 'ROM';

        print FILE ".SECTION " . $CC->{FILE}{ 'S-' . $i }{NAME} . ";\n";

        for ( my $j = 1 ; $j <= $CC->{FILE}{ 'S-' . $i }{__line__} ; $j++ )
          {
            if ( defined $CC->{FILE}{ 'S-' . $i }{ 'L-' . $j } )
              {
                print FILE $CC->{FILE}{ 'S-' . $i }{ 'L-' . $j } . "\n";
              }
            elsif ( defined $CC->{FILE}{ 'S-' . $i }{ 'F-' . $j } )
              {
                print FILE "$CC->{FILE}{'S-' . $i}{'F-' . $j}{NAME}:\n";
                my $inBody = 1;
                for (
                    my $k = 1 ;
                    $k <= $CC->{FILE}{ 'S-' . $i }{ 'F-' . $j }{__line__} ;
                    $k++
                  )
                  {
                    if (
                        defined $CC->{FILE}{ 'S-' . $i }{ 'F-' . $j }{BODY}
                        { 'L-' . $k } )
                      {
                        print FILE
"$CC->{FILE}{'S-' . $i}{'F-' . $j}{BODY}{'L-' . $k}{LINE}\n";
                      }
                    elsif (
                        defined $CC->{FILE}{ 'S-' . $i }{ 'F-' . $j }{TAIL}
                        { 'T-' . $k } )
                      {
                        if ($inBody)
                          {
                            print FILE
                              ".$CC->{FILE}{'S-' . $i}{'F-' . $j}{NAME}.end:\n";
                            $inBody = 0;
                          }
                        print FILE
"$CC->{FILE}{'S-' . $i}{'F-' . $j}{TAIL}{'T-' . $k}\n";
                      }
                  }
                if ($inBody)
                  {
                    print FILE
                      ".$CC->{FILE}{'S-' . $i}{'F-' . $j}{NAME}.end:\n";

                  }
              }
          }
      }
    close FILE;

  }

sub ShowHash
  {
    my $offset = shift;
    my $hash   = shift;

    return if ref $hash ne 'HASH';

    my $str_offset = '  ' x $offset;

    foreach my $key ( keys %$hash )
      {
        if ( ref $hash->{$key} eq 'HASH' )
          {
            print $str_offset . "$key =>\n";
            ShowHash( $offset + 1, $hash->{$key} );
          }
        elsif ( ref $hash->{$key} eq 'ARRAY' )
          {
            print $str_offset . "$key =>\n";
            ShowArray( $offset + 1, $hash->{$key} );
          }
        else
          {
            my $value = $hash->{$key};
            $value = 'NEW FUNCTION'     if $value =~ /100/;
            $value = 'DELETED FUNCTION' if $value =~ /200/;
            $value = 'COMMON FUNCTION'  if $value =~ /300/;
            $value = 'CRAWLED FUNCTION' if $value =~ /400/;

            print $str_offset . "$key => $value\n";
          }
      }
  }

sub ShowArray
  {
    my $offset = shift;
    my $array  = shift;

    return if ref $array ne 'ARRAY';

    my $str_offset = '  ' x $offset;

    for ( my $i = 0 ; $i <= $#{$array} ; $i++ )
      {
        if ( ref $array->[$i] eq 'HASH' )
          {
            print $str_offset . "[$i] :\n";
            ShowHash( $offset + 1, $array->[$i] );
          }
        elsif ( ref $array->[$i] eq 'ARRAY' )
          {
            print $str_offset . "[$i] :\n";
            ShowArray( $offset + 1, $array->[$i] );
          }
        else
          {
            print $str_offset . "[$i] : $array->[$i]\n",;
          }
      }
  }

sub DumpArray
  {
    my ( $DumpFile, $Array ) = @_;

    if ( not open( DUMP, ">$DumpFile" ) )
      {
        Warning("Failed to dump data to $DumpFile");
        return;
      }

    print DUMP join( "\n", @$Array );
    close DUMP;
  }

sub GetIndex
  {
    my @ARRAY = @_;
    $ARRAY[0] =~ s/^_//;
    $ARRAY[0] = lc $ARRAY[0];

    my $str = $ARRAY[0];

    my $i     = 0;
    my $place = 0;

    map { $i++; $place = $i if $_ eq $str } sort { $a cmp $b } @ARRAY;

    $place;
  }

sub BogusClone { _bogusClone(@_) }

sub END__CriticalSection    { $SIG{INT} = 'DEFAULT'; $SIG{QUIT} = 'DEFAULT'; }
sub APOGEE__CriticalSection { $SIG{INT} = 'IGNORE';  $SIG{QUIT} = 'IGNORE'; }

#-------------------- Internal Functions ----------------------------
sub _cleanClone
  {
    my ( $src, $dest ) = @_;

    foreach my $key ( keys %{$src} )
      {
        next if $key eq 'RE';

        if ( ref $src->{$key} eq 'HASH' )
          {
            $dest->{$key} = {};
            _cleanClone( $src->{$key}, $dest->{$key} );
          }
        else
          {
            $dest->{$key} = $src->{$key};
          }
      }
  }

sub _bogusClone
  {
    my ( $src, $dest, $reLabels, $reFuncs ) = @_;

    foreach my $key ( keys %{$src} )
      {
        next if $key eq 'RE';

        if ( ref $src->{$key} eq 'HASH' )
          {
            $dest->{$key} = {};
            _bogusClone( $src->{$key}, $dest->{$key}, $reLabels, $reFuncs );
          }
        else
          {
            $dest->{$key} = $src->{$key};
            $dest->{$key} =~ s/($$reLabels)\b/$1__BOGUS/g
              if $reLabels and $key eq 'LINE';
            $dest->{$key} =~ s/($$reFuncs)\b/$1_BUG/g
              if $reFuncs and $key eq 'LINE';
          }
      }
  }

#-----------------------------------------------------
1;
