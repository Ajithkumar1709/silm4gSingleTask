#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# ASN.1 Compiler Service Library
#
# Functions for loading auxiliary compiler files
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         17-Aug-2009     KS         1. Initial Version
#-----------------------------------------------------------------------
package Loader;



use strict;
use warnings;

use Globals;
use Commons qw/:globals :common_func :filecodes/;

#------------------ Application-wide Variables ---------------
our $DEBUG;
our %MAP = ();
our %ASN1;
our $IGNORED;

#-------------------------- Local Globals --------------------
our @MapTypeOrder = ();

#-------------------- Main i/f functions ---------------------
sub loadmap
  {
    my $mapFile = shift;

    print "Loading MAP file $mapFile ... ";

    # Phase I - load map
    _loadmap($mapFile);

    # Phase II - replace aliases
    _replaceAliases();

    # Phase III - find real names
    _findRealNames();

    print "DONE\n";
  }

#----------------- Internal functions ------------------------
sub _loadmap
  {
    my $mapFile = shift;

    Error("Failed to open map file $mapFile") if not open( MAP, "<$mapFile" );

    my $inComments = FALSE;
    my $lineNumber = 0;
    my $IgnoredSet = FALSE;
    while ( my $line = readline MAP )
      {
        $lineNumber++;

        chomp $line;
        next if $line =~ /^\s*\/\//;
        next if $line =~ /^\s*$/;
        next if $line =~ /^\s*\/\*.*\*\/\s*$/;
        if ( $inComments == FALSE and $line =~ /^\s*\/\*/ )
          {
            $inComments = TRUE;
            next;
          }
        if ( $inComments == TRUE )
          {
            $inComments = FALSE if $line =~ /\*\/\s*$/;
            next;
          }

        my @line = split /,/, $line, -1;

        if (    $line[0] ne 'ENUM'
            and $line[0] ne 'TYPE'
            and $line[0] ne 'IGNORE' )
          {
            Error("\nUnrecognized line #$lineNumber: $line");
          }

        if ( not $line[1] )
          {
            Warning "Empty TYPE/ENUM name, #$lineNumber";
          }
        else
          {
            if ( $line[0] eq 'TYPE' )
              {
                $MAP{ $line[0] }{ $line[1] }{FACTUAL} = $line[2];
                push @{ $MAP{ $line[0] }{ $line[1] }{DATA} },
                  @line[ 3 .. $#line ];
                push @MapTypeOrder, $line[1];
                if ( $IgnoredSet == FALSE )
                  {
                    $IGNORED = scalar @{ $MAP{ $line[0] }{ $line[1] }{DATA} };
                    $IgnoredSet = TRUE;
                  }
              }
            elsif ( $line[0] eq 'ENUM' )
              {
                push @{ $MAP{ $line[0] }{ $line[1] }{ $line[2] } },
                  @line[ 3 .. $#line ];
              }
            elsif ( $line[0] eq 'IGNORE' )
              {
                if ( defined $MAP{TYPE}{ $line[1] } )
                  {
                    push @{ $MAP{TYPE}{ $line[1] }{DATA}->[$IGNORED] },
                      $line[2];
                    $MAP{TYPE}{ $line[1] }{DATA}->[ $IGNORED + 1 ] = 'IGNORED';
                  }
                else
                  {
                    $MAP{TYPE}{ $line[1] }{FACTUAL} = $line[1];
                    my $index = 0;
                    while ( $index < $IGNORED )
                      {
                        $MAP{TYPE}{ $line[1] }{DATA}[$index] = 0;
                        $index++;
                      }
                    push @{ $MAP{TYPE}{ $line[1] }{DATA}[$IGNORED] }, $line[2];
                    $MAP{TYPE}{ $line[1] }{DATA}[ $IGNORED + 1 ] = 'IGNORED';
                    push @MapTypeOrder, $line[1];
                  }
              }
          }
      }

    close MAP;
  }

sub _replaceAliases
  {
    my %Aliases = ();

    foreach my $entry (@MapTypeOrder)
      {
        $Aliases{ $MAP{TYPE}{$entry}{FACTUAL} } = $entry
          if $entry ne $MAP{TYPE}{$entry}{FACTUAL};
      }

    my @AllTypes   = keys %{ $MAP{TYPE} };
    my @AllAliases = keys %Aliases;

    foreach my $alias (@AllAliases)
      {
        foreach my $type ( grep /$alias/, @AllTypes )
          {
            $MAP{TYPE}{$type}{ALIAS_FOR} = $type;
            $MAP{TYPE}{$type}{ALIAS_FOR} =~
              s/^((?:.+_)?)$alias((?:_.+)?)$/$1$Aliases{$alias}$2/
              unless $type =~ /$Aliases{$alias}/;
          }
      }
  }

sub _findRealNames
  {
    foreach my $entry (@MapTypeOrder)
      {
        my $seq_entry = undef;
        my $def_path  = 'NORMAL';

        my @realName = _estimateRealName(
            ( defined $MAP{TYPE}{$entry}{ALIAS_FOR} )
            ? $MAP{TYPE}{$entry}{ALIAS_FOR}
            : $entry
        );

        if ( not @realName )
          {
            $MAP{TYPE}{$entry}{REAL} = 'USELESS';
            Warning(
                "Cannot calculate real name for "
                  . (
                    ( defined $MAP{TYPE}{$entry}{ALIAS_FOR} )
                    ? $MAP{TYPE}{$entry}{ALIAS_FOR}
                    : $entry
                  )
            );
            next;
          }
        else
          {
            my @Best = sort { $b->[1] <=> $a->[1] } @realName;

            if ( $entry =~ /_seq/
                and _mapped( $Best[0][0], $entry ) )
              {
                $seq_entry = _getmapped( $Best[0][0], $entry );
                $seq_entry->{ELEMENT}       = $entry;
                $def_path                   = 'SEQUENCEOF';
                $MAP{TYPE}{$entry}{POINTER} = $seq_entry;
              }
            elsif ( ( $entry =~ /_str/ or $entry =~ /_aeStr/ )
                and _mapped( $Best[0][0], $entry ) )
              {
                $seq_entry = _getmapped( $Best[0][0], $entry );
                $seq_entry->{ELEMENT}       = $entry;
                $def_path                   = 'STRING';
                $MAP{TYPE}{$entry}{POINTER} = $seq_entry;
              }
            else
              {
                while ( @Best and _mapped( $Best[0][0], $entry ) )
                  {
                    shift @Best;
                  }
                if ( not @Best )
                  {
                    $MAP{TYPE}{$entry}{REAL} = 'USELESS';
                    Warning(
                        "Cannot calculate real name for "
                          . (
                            ( defined $MAP{TYPE}{$entry}{ALIAS_FOR} )
                            ? $MAP{TYPE}{$entry}{ALIAS_FOR}
                            : $entry
                          )
                    );
                    next;
                  }

                if ( $Best[0][1] == -1 )
                  {
                    Warning(
                        "Nothing appropriate found for "
                          . (
                            ( defined $MAP{TYPE}{$entry}{ALIAS_FOR} )
                            ? $MAP{TYPE}{$entry}{ALIAS_FOR}
                            : $entry
                          )
                          . " best guess was $Best[0][0]"
                    );

                    $MAP{TYPE}{$entry}{REAL} = 'USELESS';
                    next;
                  }
                elsif ( $Best[0][2] == 0 )
                  {
                    Warning(
                        "Too bad guess for "
                          . (
                            ( defined $MAP{TYPE}{$entry}{ALIAS_FOR} )
                            ? $MAP{TYPE}{$entry}{ALIAS_FOR}
                            : $entry
                          )
                          . " - $Best[0][0]"
                    );

                    $MAP{TYPE}{$entry}{REAL} = 'USELESS';
                    next;
                  }
                else
                  {
                    $MAP{TYPE}{$entry}{REAL} = $Best[0][0];
                  }
              }
          }

        if ( $def_path eq 'SEQUENCEOF' )
          {
            Info(
                "Set ELEMENT name to $entry in SEQUENCE OF $seq_entry->{REAL}");
          }
        elsif ( $def_path eq 'STRING' )
          {
            Info(
"Set ELEMENT name to $entry in BIT/OCTET STRING $seq_entry->{REAL}"
            );
          }
        else
          {
            my $realName = $MAP{TYPE}{$entry}{REAL};
            $realName =~ s/-/_/g;
            Info("Set real Name for $entry to $realName")
              if $entry ne $realName;
          }
      }
  }

sub _estimateRealName
  {
    my $orig_name = shift;

    my $name = $orig_name;

    my $string = FALSE;
    $string = TRUE if $name =~ /_(str|aeStr)$/;
    $name =~ s/_(str|aeStr)$//;

    my $sequence   = FALSE;
    my $seq_number = 0;
    if ( $name =~ /_seq_?(\d*)$/ )
      {
        $sequence = TRUE;
        $seq_number = $1 if $1;
        $name =~ s/_seq_?\d*$//;
      }

    my $asn_name = $name;
    $asn_name =~ s/_/-/g;

    return ( [ $asn_name, 0, 1 ] )
      if defined $ASN1{$asn_name} and $sequence == FALSE;

    return _lookupsequenceof( $orig_name, $name ) if $sequence == TRUE;

    my @name  = split /_/, $name;
    my $index = $#name;

    my @Guesses    = ();
    my @Candidates = ();
    my @Fields     = ();
    while ( $index >= 0 )
      {
        if ( defined $ASN1{ join( "-", @name[ 0 .. $index ] ) } )
          {
            my $base_name = join( "-", @name[ 0 .. $index ] );

            @Fields = ( [ $base_name, "(?:$base_name)" ] );
            if ($string)
              {
                _getStrings( $ASN1{$base_name}, \@Fields, 0 );
              }
            else
              {
                GetFields( $ASN1{$base_name}, \@Fields, 0, 'RE' );
              }

            push @Candidates,
              map { $_->[0] } grep { $_->[0] eq $asn_name } @Fields;
            push @Candidates,
              map { $_->[0] } grep { $asn_name =~ /^$_->[1]$/ } @Fields
              if not @Candidates;

            if ( scalar @Candidates != 1 )
              {
                my $number = 0;
                $number = $1 if $asn_name =~ /-(\d)\b/;
                $asn_name =~ s/-\d\b//;

                if ( $number > 0 )
                  {
                    push @Candidates,
                      map { $_->[0] } grep { $_->[0] eq $asn_name } @Fields;

                    foreach my $_cand (
                        map { $_->[0] }
                        grep { $asn_name =~ /^$_->[1]$/ } @Fields
                      )
                      {
                        push @Candidates, $_cand
                          if not scalar grep /^$_cand$/, @Candidates;
                      }
                  }
                @Candidates = ( $Candidates[$number] )
                  if defined $Candidates[$number];
              }
          }

        $index--;
      }

    push @Guesses, [ $Candidates[0], 1, 1 ] if scalar @Candidates == 1;

    return @Guesses;
  }

sub _getStrings
  {
    my $root   = shift;
    my $Fields = shift;
    my $index  = shift;

    $root = SkipStruct($root);

    if ( defined $root->{_ORDER_} )
      {
        foreach my $field ( @{ $root->{_ORDER_} } )
          {
            push @$Fields,
              [
                $Fields->[$index][0] . "-$field",
                $Fields->[$index][1] . "?(?:-$field)"
              ]
              if InternalString( $root->{$field} );

            if ( my $kind = InternalStruct( $root->{$field} ) )
              {
                _getStrings( $root->{$field}, $Fields, $#{$Fields} )
                  unless $kind eq 'ENUMERATED';
              }
          }
      }
  }

sub _lookupsequenceof
  {
    my ( $orig_name, $name ) = @_;

    return ()
      if defined $MAP{TYPE}{$name}
      and defined $MAP{TYPE}{$name}{REAL}
      and $MAP{TYPE}{$name}{REAL} eq 'USELESS';

    my $asn_name = $name;
    $asn_name =~ s/_/-/g;

    my $seq_num = 1;
    $seq_num = $1 + 1 if $orig_name =~ /_seq_(\d)/;

    my @name      = split /_/, $name;
    my $index     = $#name;
    my @calc_name = ();

    my $root = \%ASN1;

    return ( [ $asn_name, 1, 1 ] )
      if defined $ASN1{$asn_name}
      and defined $ASN1{$asn_name}{SEQUENCEOF}
      and $seq_num == 1;

    while ( $index >= 0 )
      {
        if ( defined $root->{ join( "-", @name[ 0 .. $index ] ) } )
          {
            $root = SkipStruct( $root->{ join( "-", @name[ 0 .. $index ] ) } );
            push @calc_name, join( "-", @name[ 0 .. $index ] );
            last if $index == $#name;
            @name  = @name[ $index + 1 .. $#name ];
            $index = $#name;
          }
        else
          {
            $index--;
          }
      }

    my $saw        = 0;
    my $sequenceof = _getsequenceof( $root, $seq_num, \$saw, \@calc_name );

    return ( [ join( "-", @calc_name ), scalar(@calc_name), 1 ] )
      if $sequenceof;

    return ();
  }

sub _getsequenceof
  {
    my ( $root, $num, $saw, $name ) = @_;

    return undef if ref $root ne 'HASH';

    if ( defined $root->{SEQUENCEOF} )
      {
        $$saw++;
        return $root if $$saw == $num;
      }

    $root = SkipStruct($root);

    if ( ref $root eq 'HASH' and defined $root->{_ORDER_} )
      {
        foreach my $field ( @{ $root->{_ORDER_} } )
          {
            push @$name, $field;
            my $new_root = _getsequenceof( $root->{$field}, $num, $saw, $name );
            return $new_root if $new_root;
            pop @$name;
          }
      }
    return undef;
  }

sub _mapped
  {
    my $name  = shift;
    my $entry = shift;

    foreach my $map (@MapTypeOrder)
      {
        return TRUE
          if defined $MAP{TYPE}{$map}{REAL}
          and $MAP{TYPE}{$map}{REAL} eq $name
          and defined $MAP{TYPE}{$map}{FACTUAL}
          and $entry ne $MAP{TYPE}{$map}{FACTUAL};
      }

    return FALSE;
  }

sub _getmapped
  {
    my $name  = shift;
    my $entry = shift;

    foreach my $map (@MapTypeOrder)
      {
        return $MAP{TYPE}{$map}
          if defined $MAP{TYPE}{$map}{REAL}
          and $MAP{TYPE}{$map}{REAL} eq $name
          and defined $MAP{TYPE}{$map}{FACTUAL}
          and $entry ne $MAP{TYPE}{$map}{FACTUAL};
      }

    return undef;
  }

#-------------------------------------------------------------
1;
