#------------------------------------------------------------
# (C) Copyright [2011] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#---------------------------------------------------------------------
#
# CBA Command Line Interface Tool
#
#---------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#---------------------------------------------------------------------
# Version     Date            Author     Description
# 0.03        01-Mar-2011     KS         1. Add 'link' option
# 0.02        24-Feb-2011     KS         1. Add target auto-detection and option
# 0.01        23-Feb-2011     KS         1. Initial Version
#---------------------------------------------------------------------
use strict;
use warnings;

use Data::Dumper;

use lib ".\\";

my $VERSION = '0.03';

print STDERR <<VERSION;
CBA Command Line Interface. Version $VERSION
(C) Copyright [2011] Marvell International Ltd. All rights reserved.

VERSION

print <<'HELP' if not @ARGV or grep /help/i, @ARGV;
Usage:
    cba.exe [-target=target_name] [-tv=target_variant]
            [-refresh] [-force] [-link] [-build]
            [<space separated list of targets>]

HELP

exit 0 if not @ARGV or grep /help/i, @ARGV;

#---------------------------------------------------------------------------------------
# Decode Input parameters
#---------------------------------------------------------------------------------------
my $TV     = '';
my $pureTV = '';
my @_tv    = grep /tv=/i, @ARGV;
@ARGV = grep !/tv=/i, @ARGV;
if ( @_tv and defined $_tv[0] and $_tv[0] =~ /tv=(.+)$/ )
  {
    $TV     = "_$1";
    $pureTV = $1;
  }

my $refresh = 'NO';
$refresh = 'YES' if grep /refresh$/i, @ARGV;
@ARGV = grep !/refresh$/i, @ARGV;

my $link = 'NO';
$link = 'YES' if grep /link$/i, @ARGV;
@ARGV = grep !/link$/i, @ARGV;

my $build = 'NO';
$build = 'YES' if grep /build$/i, @ARGV;
@ARGV = grep !/build$/i, @ARGV;

my $force = '';
$force = '-B' if grep /force$/i, @ARGV;
@ARGV = grep !/force$/i, @ARGV;

my $Target = '';
my @_target = grep /target=/i, @ARGV;
@ARGV = grep !/target=/i, @ARGV;
$Target = $1 if @_target and $_target[0] =~ /target=(.+)$/;

#---------------------------------------------------------------------------------------
# Generate Build Base if needed; load build base
#---------------------------------------------------------------------------------------
GenerateBuildBase( $Target, $pureTV, $TV )
  if not -e "build$TV.base"
      or $refresh eq 'YES';

#exit 0 if not @ARGV;

my %BuildBase = ();
our $VAR1;
eval { require "build$TV.base" };
if ($@)
  {
    print "ERROR :: Failed to load Build Tree build$TV.base. STOP\n";
    exit 1;
  }

%BuildBase = %$VAR1;
undef $VAR1;

#---------------------------------------------------------------------------------------
# Run all required builds
#---------------------------------------------------------------------------------------
my @CmdChain = ();
my @Done     = ();
foreach my $request (@ARGV)
  {
    if ( defined $BuildBase{ELEMENT}{$request} )
      {
        if ( $BuildBase{ELEMENT}{$request}{TYPE} eq 'FILE' )
          {
            my $object = $request;
            $object =~ s/\.c$/.o/;
            push @CmdChain,
"gnumake -C \\$BuildBase{ELEMENT}{$request}{BASE}\\$BuildBase{ELEMENT}{$request}{ENTITY}\\build $force -f $BuildBase{ELEMENT}{$request}{ENTITY}.mak OPT_FILE=$BuildBase{ELEMENT}{$request}{OPT} VL_DTL=\@ VL_EXP=\@ $BuildBase{ELEMENT}{$request}{OUT}/$object";
          }
        elsif ( $BuildBase{ELEMENT}{$request}{TYPE} eq 'ENTITY' )
          {
            if ( $BuildBase{ELEMENT}{$request}{OPT} )
              {
                push @CmdChain,
"gnumake -C \\$BuildBase{ELEMENT}{$request}{BASE}\\$request\\build $force -f $request.mak OPT_FILE=$BuildBase{ELEMENT}{$request}{OPT} VL_DTL=\@ VL_EXP=\@";
                push @Done, $request;
              }
            if ( not $BuildBase{ELEMENT}{$request}{OPT} )
              {
                my $PreCmd = '';
                $PreCmd =
"\\$BuildBase{ELEMENT}{$request}{BASE}\\$request\\build\\set_variables.bat"
                  . " && "
                  . "\\$BuildBase{ELEMENT}{$request}{BASE}\\$request\\build\\SetPSEnv.bat"
                  . " &&"
                  if
                    -e "\\$BuildBase{ELEMENT}{$request}{BASE}\\$request\\build\\set_variables.bat"
                      and
                      -e "\\$BuildBase{ELEMENT}{$request}{BASE}\\$request\\build\\SetPSEnv.bat";

                push @CmdChain,
"$PreCmd gnumake -C \\$BuildBase{ELEMENT}{$request}{BASE}\\$request\\build $force -f $request.mak $TV";
              }
          }
      }
    else
      {
        push @CmdChain,
"echo WARN :: Don't know how to build $request. It is not registered in Build Base.";
      }
  }

if ( $link eq 'YES' or $build eq 'YES' )
  {
    my $chain;
    foreach my $target (@ARGV)
      {
        $chain = $target;
        while ( defined $BuildBase{TREE}{ $BuildBase{TREE}{$chain} } )
          {
            if ( not grep /$BuildBase{TREE}{$chain}/, @Done )
              {
                push @CmdChain,
"gnumake -C \\$BuildBase{ELEMENT}{$BuildBase{TREE}{$chain}}{BASE}\\$BuildBase{TREE}{$chain}\\build $force -f $BuildBase{TREE}{$chain}.mak OPT_FILE=$BuildBase{ELEMENT}{$BuildBase{TREE}{$chain}}{OPT} VL_DTL=\@ VL_EXP=\@";
                push @Done, $BuildBase{TREE}{$chain};
              }
            $chain = $BuildBase{TREE}{$chain};
          }
      }
    $chain = $BuildBase{TREE}{$chain}
      if $chain and defined $BuildBase{TREE}{$chain};
    $chain = GetLinkTarget( \%BuildBase )
      if not $chain
          or not defined $BuildBase{TREE}{$chain};

    if ($chain)
      {
        if ( $build eq 'YES' )
          {
            my $PreCmd = '';
            $PreCmd =
"\\$BuildBase{ELEMENT}{$chain}{BASE}\\$chain\\build\\set_variables.bat"
              . " && "
              . "\\$BuildBase{ELEMENT}{$chain}{BASE}\\$chain\\build\\SetPSEnv.bat"
              . " &&"
              if
                -e "\\$BuildBase{ELEMENT}{$chain}{BASE}\\$chain\\build\\set_variables.bat"
                  and
                  -e "\\$BuildBase{ELEMENT}{$chain}{BASE}\\$chain\\build\\SetPSEnv.bat";

            push @CmdChain,
"$PreCmd gnumake -C \\$BuildBase{ELEMENT}{$chain}{BASE}\\$chain\\build $force -f $chain.mak $TV";
          }
        elsif ( $link eq 'YES' )
          {
            if ( defined $BuildBase{ELEMENT}{$chain}{LINK}
                and $BuildBase{ELEMENT}{$chain}{LINK} )
              {
                push @CmdChain, "echo $BuildBase{ELEMENT}{$chain}{LINK}";
                push @CmdChain, "$BuildBase{ELEMENT}{$chain}{LINK}";
              }
            else
              {
                push @CmdChain, "echo WARN :: Dont know how to link $chain";
              }
          }
      }
    else
      {
        push @CmdChain,
          "echo WARN :: cannot determine link target from the Build Base";
      }
  }

foreach my $cmd (@CmdChain)
  {
    system($cmd);
    my $errors = '';
    $errors = "(with errors) " if $?;

    print "--- DONE $errors---\n\n" if $cmd !~ /^echo/;
  }

#------------------------------- END of MAIN ----------------------------------------------
sub GenerateBuildBase
  {
    my ( $target, $ptv, $tv ) = @_;
    my %buildBase = ();

    print "Cannot find Build Base..."
      if $refresh eq 'NO';
    print "Generating Build Base and refresh include cache ... "
      if $refresh eq 'YES';

    if ( not $target )
      {
        $target = GetTarget();
      }
    else
      {
        $target .= '.mak' if $target !~ /\.mak$/;
      }

    if ( not $target )
      {
        print "\n\n\tERROR :: Cannot find any suitable CBA target. STOP.\n";
        exit 1;
      }

    print "\nINFO :: Generating build base ... ";

    my @_buildbase = qx/gnumake -f $target TV=$ptv buildbase/;
    if ($?)
      {
        print
"\n\n\tERROR:: Failed to run target in 'build base' mode. Cannot generate build base. STOP";
        exit 1;
      }
    system("gnumake -f $target TV=$ptv include_cache");
    if ($?)
      {
        print "\n\n\tERROR :: Failed to generate include cache. STOP";
        exit 1;
      }

    chomp @_buildbase;
    my @buildbase = grep /bb\./, @_buildbase;
    undef @_buildbase;

    my $out      = '';
    my $list     = '';
    my $name     = '';
    my $base     = '';
    my $opt      = '';
    my $targ     = '';
    my $groups   = '';
    my $packages = '';
    my $kind     = '';
    my $link     = '';
    foreach my $line (@buildbase)
      {

        if ( $line =~ /bb\.start/ )
          {
            (
                $out,  $list,   $name,     $base, $opt,
                $targ, $groups, $packages, $kind, $link
            ) = ('') x 10;
          }

        elsif ( $line =~ /^bb\.out=(.+)$/ )      { $out      = $1 }
        elsif ( $line =~ /^bb\.name=(.+)$/ )     { $name     = $1 }
        elsif ( $line =~ /^bb\.base=(.+)$/ )     { $base     = $1 }
        elsif ( $line =~ /^bb\.opt=(.*)$/ )      { $opt      = $1 }
        elsif ( $line =~ /^bb\.files=(.*)$/ )    { $list     = $1 }
        elsif ( $line =~ /^bb\.target=(.+)$/ )   { $targ     = $1 }
        elsif ( $line =~ /^bb\.groups=(.*)$/ )   { $groups   = $1 }
        elsif ( $line =~ /^bb\.packages=(.*)$/ ) { $packages = $1 }
        elsif ( $line =~ /^bb\.entity=(.+)$/ )   { $kind     = $1 }
        elsif ( $line =~ /^bb\.link=(.+)$/ )     { $link     = $1 }

        elsif ( $line =~ /bb\.end/ )
          {
            foreach my $file ( split /\s+/, $list )
              {
                $buildBase{ELEMENT}{$file}{TYPE}   = 'FILE';
                $buildBase{ELEMENT}{$file}{OUT}    = $out;
                $buildBase{ELEMENT}{$file}{ENTITY} = $name;
                $buildBase{ELEMENT}{$file}{BASE}   = $base;
                $buildBase{ELEMENT}{$file}{OPT}    = $opt;
                $buildBase{ELEMENT}{$file}{TARGET} = $targ;
                $buildBase{ELEMENT}{$file}{KIND}   = $kind;
                @{ $buildBase{ELEMENT}{$file}{GROUPS} } = (
                    $groups
                    ? map { /[\\\/]([^\\\/]+)$/; $1 } split( /\s+/, $groups )
                    : ()
                );
                @{ $buildBase{ELEMENT}{$file}{PACKAGES} } = (
                    $packages
                    ? map { /[\\\/]([^\\\/]+)$/; $1 } split( /\s+/, $packages )
                    : ()
                );
              }

            $buildBase{ELEMENT}{$name}{TYPE}   = 'ENTITY';
            $buildBase{ELEMENT}{$name}{BASE}   = $base;
            $buildBase{ELEMENT}{$name}{OPT}    = $opt;
            $buildBase{ELEMENT}{$name}{TARGET} = $targ;
            $buildBase{ELEMENT}{$name}{KIND}   = $kind;
            @{ $buildBase{ELEMENT}{$name}{GROUPS} } = (
                $groups
                ? map { /[\\\/]([^\\\/]+)$/; $1 } split( /\s+/, $groups )
                : ()
            );
            @{ $buildBase{ELEMENT}{$name}{PACKAGES} } = (
                $packages
                ? map { /[\\\/]([^\\\/]+)$/; $1 } split( /\s+/, $packages )
                : ()
            );
            $buildBase{ELEMENT}{$name}{LINK} = $link;

          }
      }

    foreach my $entity ( keys %{ $buildBase{ELEMENT} } )
      {
        if ( $buildBase{ELEMENT}{$entity}{TYPE} eq 'FILE' )
          {
            $buildBase{TREE}{$entity} = $buildBase{ELEMENT}{$entity}{ENTITY};
            next;
          }

        next
          if not @{ $buildBase{ELEMENT}{$entity}{GROUPS} }
              and not @{ $buildBase{ELEMENT}{$entity}{PACKAGES} };

        foreach my $child (
            (
                @{ $buildBase{ELEMENT}{$entity}{GROUPS} },
                @{ $buildBase{ELEMENT}{$entity}{PACKAGES} }
            )
          )
          {
            $buildBase{TREE}{$child} = $entity;
          }
      }

    if ( open( BUILD, ">build$tv.base" ) )
      {
        print BUILD Dumper( \%buildBase );
        close BUILD;
      }
    else
      {
        print "\n\n\tERROR :: Fail to write build$tv.base. STOP\n";
        exit 1;
      }

    print "DONE\n";
  }

sub GetTarget
  {
    if ( not opendir( DIR, "." ) )
      {
        print
          "\n\n\tERROR :: Failed to read content of current folder. STOP.\n";
        exit 1;
      }

    my @Dir = readdir DIR;
    close DIR;

    my @Makes = grep /\.mak$/, @Dir;
    if ( not @Makes )
      {
        print
"\n\n\tERROR :: Failed to find make file(s) in current folder. STOP.\n";
        exit 1;
      }

    my $target = '';
    foreach my $make (@Makes)
      {
        if ( not open( MAKE, "<$make" ) )
          {
            print "\n\n\tWARN :: Failed to read $make. SKIP.";
            next;
          }

        my @Make = <MAKE>;
        close MAKE;

        if ( grep /TARGET_NAME/, @Make )
          {
            $target = $make;
            print "\n\nINFO :: Found target $target. WILL USE IT.";
            last;
          }
      }

    return $target;
  }

sub GetLinkTarget
  {
    my $base = shift;

    foreach my $target ( keys %{ $BuildBase{ELEMENT} } )
      {
        return $target
          if defined $BuildBase{ELEMENT}{$target}{LINK}
              and $BuildBase{ELEMENT}{$target}{LINK};
      }

    return '';
  }

#------------------------------------------------------------------------------------------
