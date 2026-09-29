#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# ASN.1 Compiler Service Library
#
# Upgrade structures
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         19-Aug-2009     KS         1. Initial Version
#-----------------------------------------------------------------------
package Upgrader;



use strict;
use warnings;

use File::Basename;

use Globals;
use Commons qw/:globals :common_func :filecodes/;

#------------------ Application-wide Variables ---------------
our $DEBUG;
our %ASN1;
our @ASN1Index;
our %ASN1Usage;
our %MAP;

#---------------------- Local Globals --------------------------------
my %Upgrade   = ();
my @ToUpgrade = ();

use constant {
    LEGACY_CHOICE_EXTRA => 0x8,
    LEGACY_CHOICE       => 0x4,
    LEGACY_UPGRADED     => 0x2,
    LEGACY_SWALLOWED    => 0x1,
    LEGACY_IGNORED      => 0x0
};

#------------------ Main i/f function   ------------------------------
sub marknotsupported
  {
    my @nsSuspected = ();

    print "\tTrashing NOT SUPPORTED and IGNORED elements ... ";

    foreach my $struct ( keys %{ $MAP{TYPE} } )
      {
        next
          unless ( defined $MAP{TYPE}{$struct}{DATA}->[2]
            and $MAP{TYPE}{$struct}{DATA}->[2] =~ /NOT_SUPPORTED/ )
          or ( defined $MAP{TYPE}{$struct}{DATA}->[ $IGNORED + 1 ]
            and $MAP{TYPE}{$struct}{DATA}->[ $IGNORED + 1 ] =~ /IGNORED/ );

        my $dig_struct = $struct;
        if ( defined $MAP{TYPE}{$struct}{POINTER} )
          {
            $dig_struct = $MAP{TYPE}{$struct}{POINTER}->{ALIAS_FOR}
              if defined $MAP{TYPE}{$struct}{POINTER}->{ALIAS_FOR};
            $dig_struct = $MAP{TYPE}{$struct}{POINTER}->{REAL}
              if defined $MAP{TYPE}{$struct}{POINTER}->{REAL};
          }
        else
          {
            $dig_struct = $MAP{TYPE}{$struct}{ALIAS_FOR}
              if defined $MAP{TYPE}{$struct}{ALIAS_FOR};
            $dig_struct = $MAP{TYPE}{$struct}{REAL}
              if defined $MAP{TYPE}{$struct}{REAL};
          }
        $dig_struct =~ s/_/-/g;

        next if $dig_struct eq 'USELESS';

        if (    defined $MAP{TYPE}{$struct}{DATA}->[ $IGNORED + 1 ]
            and $MAP{TYPE}{$struct}{DATA}->[ $IGNORED + 1 ] =~ /IGNORED/
            and $MAP{TYPE}{$struct}{DATA}->[2] !~ /NOT_SUPPORTED/ )
          {
            my $work_struct = undef;
            my @struct_path = ();
            if ( defined $ASN1{$dig_struct} )
              {
                my $root = SkipStruct( $ASN1{$dig_struct} );
                foreach my $f ( @{ $MAP{TYPE}{$struct}{DATA}->[$IGNORED] } )
                  {
                    if ( defined $root->{$f} )
                      {
                        $root->{$f}{IGNORED}     = 1;
                        $root->{$f}{MAP_IGNORED} = 1;
                        $work_struct             = $root;
                      }
                    else
                      {
                        Warning(
"Cannot 'IGNORE' non existent field $MAP{TYPE}{$struct}{DATA}->[$IGNORED]} in $dig_struct"
                        );
                      }
                  }
              }
            else
              {
                my @path           = ();
                my $upgrade_struct =
                  _digstruct( $dig_struct, \%ASN1, \@path, \@struct_path );

                if ( $upgrade_struct
                    and ref $upgrade_struct eq 'HASH' )
                  {
                    foreach my $f ( @{ $MAP{TYPE}{$struct}{DATA}->[$IGNORED] } )
                      {
                        if ( defined $upgrade_struct->{$f} )
                          {
                            $upgrade_struct->{$f}{IGNORED}     = 1;
                            $upgrade_struct->{$f}{MAP_IGNORED} = 1;
                            $work_struct = $upgrade_struct;
                          }
                        else
                          {
                            Warning(
"Cannot 'IGNORE' non existent field $MAP{TYPE}{$struct}{DATA}->[$IGNORED]} in $dig_struct"
                            );
                          }
                      }
                  }
              }
            _markignored( $work_struct, \@struct_path )
              if $work_struct
              and ref $work_struct eq 'HASH'
              and defined $work_struct->{_ORDER_};

            next;
          }

        if ( defined $ASN1{$dig_struct} )
          {
            $ASN1{$dig_struct}{NOTSUPPORTED}     = 1;
            $ASN1{$dig_struct}{MAP_NOTSUPPORTED} = 1;
            push @nsSuspected, @{ $ASN1Usage{$dig_struct}{USES} }
              if defined $ASN1Usage{$dig_struct};
          }
        else
          {
            my @path           = ();
            my $upgrade_struct = _digstruct( $dig_struct, \%ASN1, \@path );

            if ( $upgrade_struct and ref $upgrade_struct eq 'HASH' )
              {
                $upgrade_struct->{NOTSUPPORTED}     = 1;
                $upgrade_struct->{MAP_NOTSUPPORTED} = 1;
                push @nsSuspected, _digFreeFields($upgrade_struct);
              }
          }
      }

    foreach my $free (@nsSuspected)
      {
        next if $free eq 'NULL' or $free eq 'BOOLEAN';

        if ( not defined $ASN1{$free}{NOTSUPPORTED}
            and _fastNotInUse( $free, 'NOTSUPPORTED' ) )
          {
            $ASN1{$free}{NOTSUPPORTED} = 1;
            push @nsSuspected, @{ $ASN1Usage{$free}{USES} }
              if defined $ASN1Usage{$free};
          }
      }

    print "DONE\n";
  }

sub _markignored
  {
    my $work_struct = shift;
    my $struct_path = shift;

    foreach my $field ( @{ $work_struct->{_ORDER_} } )
      {
        return
          unless defined $work_struct->{$field}{NOTSUPPORTED}
          or defined SkipStruct( $work_struct->{$field} )->{NOTSUPPORTED}
          or defined $work_struct->{$field}{IGNORED}
          or defined SkipStruct( $work_struct->{$field} )->{IGNORED};
      }

    $work_struct->{IGNORED} = 1;
    return unless @$struct_path;

    while (@$struct_path)
      {
        $work_struct = pop @$struct_path;
        next unless defined $work_struct->{_ORDER_};

        foreach my $field ( @{ $work_struct->{_ORDER_} } )
          {
            return
              unless defined $work_struct->{$field}{NOTSUPPORTED}
              or defined SkipStruct( $work_struct->{$field} )->{NOTSUPPORTED}
              or defined $work_struct->{$field}{IGNORED}
              or defined SkipStruct( $work_struct->{$field} )->{IGNORED}
              or (  defined $work_struct->{$field}{KIND}
                and $work_struct->{$field}{KIND}  eq 'FREE'
                and $work_struct->{$field}{VALUE} eq 'NULL' );
          }

        $work_struct->{IGNORED} = 1;
      }
  }

sub markstatic
  {
    my @staticSuspected = ();

    print "\tRegistering STATIC elements ... ";
    foreach my $struct ( keys %{ $MAP{TYPE} } )
      {
        next
          unless defined $MAP{TYPE}{$struct}{DATA}->[1]
          and $MAP{TYPE}{$struct}{DATA}->[1] =~ /STATIC/;

        my $dig_struct = $struct;
        if ( defined $MAP{TYPE}{$struct}{POINTER} )
          {
            $dig_struct = $MAP{TYPE}{$struct}{POINTER}->{ALIAS_FOR}
              if defined $MAP{TYPE}{$struct}{POINTER}->{ALIAS_FOR};
            $dig_struct = $MAP{TYPE}{$struct}{POINTER}->{REAL}
              if defined $MAP{TYPE}{$struct}{POINTER}->{REAL};
          }
        else
          {
            $dig_struct = $MAP{TYPE}{$struct}{ALIAS_FOR}
              if defined $MAP{TYPE}{$struct}{ALIAS_FOR};
            $dig_struct = $MAP{TYPE}{$struct}{REAL}
              if defined $MAP{TYPE}{$struct}{REAL};
          }
        $dig_struct =~ s/_/-/g;

        next if $dig_struct eq 'USELESS';

        if ( defined $ASN1{$dig_struct} )
          {
            $ASN1{$dig_struct}{STATIC}     = 1;
            $ASN1{$dig_struct}{MAP_STATIC} = 1;
            _traverseFields( $ASN1{$dig_struct}, 'STATIC' );

            push @staticSuspected, @{ $ASN1Usage{$dig_struct}{USES} }
              if defined $ASN1Usage{$dig_struct};

          }
        else
          {
            my @path           = ();
            my @struct_path    = ();
            my $upgrade_struct =
              _digstruct( $dig_struct, \%ASN1, \@path, \@struct_path );

            if ( $upgrade_struct and ref $upgrade_struct eq 'HASH' )
              {
                $upgrade_struct->{STATIC}     = 1;
                $upgrade_struct->{MAP_STATIC} = 1;
                _traverseFields( $upgrade_struct, 'STATIC' );

                my @frees = _digFreeFields($upgrade_struct);
                push @staticSuspected, @frees;
              }
          }
      }

    foreach my $simple ( keys %ASN1 )
      {
        next
          unless defined $ASN1{$simple}{ENUMERATED}
          or defined $ASN1{$simple}{INTEGER}
          or (  defined $ASN1{$simple}{BITSTRING}
            and ref $ASN1{$simple}{BITSTRING} eq 'ARRAY'
            and scalar @{ $ASN1{$simple}{BITSTRING} } == 1 )
          or (  defined $ASN1{$simple}{KIND}
            and $ASN1{$simple}{KIND}  eq 'FREE'
            and $ASN1{$simple}{VALUE} eq 'BOOLEAN' );

        $ASN1{$simple}{STATIC} = 1;
      }

    foreach my $free (@staticSuspected)
      {
        next if $free eq 'NULL' or $free eq 'BOOLEAN';

        if ( not defined $ASN1{$free}{STATIC} )
          {
            $ASN1{$free}{STATIC} = 1;
            _traverseFields( $ASN1{$free}, 'STATIC' );

            push @staticSuspected, @{ $ASN1Usage{$free}{USES} }
              if defined $ASN1Usage{$free};
          }
      }

    print "DONE\n";
  }

sub markencodeonly
  {
    my @encodeSuspected = ();

    print "\tRegistering ENCODE ONLY elements ... ";
    foreach my $struct ( keys %{ $MAP{TYPE} } )
      {
        next
          unless defined $MAP{TYPE}{$struct}{DATA}->[0]
          and $MAP{TYPE}{$struct}{DATA}->[0] =~ /ENCODE_ONLY/;

        my $dig_struct = $struct;
        if ( defined $MAP{TYPE}{$struct}{POINTER} )
          {
            $dig_struct = $MAP{TYPE}{$struct}{POINTER}->{ALIAS_FOR}
              if defined $MAP{TYPE}{$struct}{POINTER}->{ALIAS_FOR};
            $dig_struct = $MAP{TYPE}{$struct}{POINTER}->{REAL}
              if defined $MAP{TYPE}{$struct}{POINTER}->{REAL};
          }
        else
          {
            $dig_struct = $MAP{TYPE}{$struct}{ALIAS_FOR}
              if defined $MAP{TYPE}{$struct}{ALIAS_FOR};
            $dig_struct = $MAP{TYPE}{$struct}{REAL}
              if defined $MAP{TYPE}{$struct}{REAL};
          }
        $dig_struct =~ s/_/-/g;

        next if $dig_struct eq 'USELESS';

        if ( defined $ASN1{$dig_struct} )
          {
            $ASN1{$dig_struct}{ENCODE_ONLY}     = 1;
            $ASN1{$dig_struct}{MAP_ENCODE_ONLY} = 1;
            _traverseFields( $ASN1{$dig_struct}, 'ENCODE_ONLY' );

            push @encodeSuspected, @{ $ASN1Usage{$dig_struct}{USES} }
              if defined $ASN1Usage{$dig_struct};

          }
        else
          {
            my @path           = ();
            my @struct_path    = ();
            my $upgrade_struct =
              _digstruct( $dig_struct, \%ASN1, \@path, \@struct_path );

            if ( $upgrade_struct and ref $upgrade_struct eq 'HASH' )
              {
                $upgrade_struct->{ENCODE_ONLY}     = 1;
                $upgrade_struct->{MAP_ENCODE_ONLY} = 1;

                _traverseFields( $upgrade_struct, 'ENCODE_ONLY' );

                my @frees = _digFreeFields($upgrade_struct);
                push @encodeSuspected, @frees;

              }
          }
      }

    foreach my $free (@encodeSuspected)
      {
        next if $free eq 'NULL' or $free eq 'BOOLEAN';

        if ( not defined $ASN1{$free}{ENCODE_ONLY}
            and _fastNotInUse( $free, 'ENCODE_ONLY' ) )
          {
            $ASN1{$free}{ENCODE_ONLY} = 1;
            _traverseFields( $ASN1{$free}, 'ENCODE_ONLY' );

            push @encodeSuspected, @{ $ASN1Usage{$free}{USES} }
              if defined $ASN1Usage{$free};
          }
      }

    print "DONE\n";
  }

sub markdecodeonly
  {
    my @decodeSuspected = ();

    print "\tRegistering DECODE ONLY elements ... ";
    foreach my $struct ( keys %{ $MAP{TYPE} } )
      {
        next
          unless defined $MAP{TYPE}{$struct}{DATA}->[0]
          and $MAP{TYPE}{$struct}{DATA}->[0] =~ /DECODE_ONLY/;

        my $dig_struct = $struct;
        if ( defined $MAP{TYPE}{$struct}{POINTER} )
          {
            $dig_struct = $MAP{TYPE}{$struct}{POINTER}->{ALIAS_FOR}
              if defined $MAP{TYPE}{$struct}{POINTER}->{ALIAS_FOR};
            $dig_struct = $MAP{TYPE}{$struct}{POINTER}->{REAL}
              if defined $MAP{TYPE}{$struct}{POINTER}->{REAL};
          }
        else
          {
            $dig_struct = $MAP{TYPE}{$struct}{ALIAS_FOR}
              if defined $MAP{TYPE}{$struct}{ALIAS_FOR};
            $dig_struct = $MAP{TYPE}{$struct}{REAL}
              if defined $MAP{TYPE}{$struct}{REAL};
          }
        $dig_struct =~ s/_/-/g;

        next if $dig_struct eq 'USELESS';

        if ( defined $ASN1{$dig_struct} )
          {
            $ASN1{$dig_struct}{DECODE_ONLY}     = 1;
            $ASN1{$dig_struct}{MAP_DECODE_ONLY} = 1;
            _traverseFields( $ASN1{$dig_struct}, 'DECODE_ONLY' );

            push @decodeSuspected, @{ $ASN1Usage{$dig_struct}{USES} }
              if defined $ASN1Usage{$dig_struct};
          }
        else
          {
            my @path           = ();
            my @struct_path    = ();
            my $upgrade_struct =
              _digstruct( $dig_struct, \%ASN1, \@path, \@struct_path );

            if ( $upgrade_struct and ref $upgrade_struct eq 'HASH' )
              {
                $upgrade_struct->{DECODE_ONLY}     = 1;
                $upgrade_struct->{MAP_DECODE_ONLY} = 1;
                _traverseFields( $upgrade_struct, 'DECODE_ONLY' );

                my @frees = _digFreeFields($upgrade_struct);
                push @decodeSuspected, @frees;

              }
          }
      }

    foreach my $free (@decodeSuspected)
      {
        next if $free eq 'NULL' or $free eq 'BOOLEAN';

        if ( not defined $ASN1{$free}{DECODE_ONLY}
            and _fastNotInUse( $free, 'DECODE_ONLY' ) )
          {
            $ASN1{$free}{DECODE_ONLY} = 1;
            _traverseFields( $ASN1{$free}, 'DECODE_ONLY' );

            push @decodeSuspected, @{ $ASN1Usage{$free}{USES} }
              if defined $ASN1Usage{$free};
          }
      }

    print "DONE\n";
  }

sub _traverseFields
  {
    my $root         = shift;
    my $specialfield = shift;

    $root = SkipStruct($root);

    if ( defined $root->{_ORDER_} )
      {
        foreach my $field ( @{ $root->{_ORDER_} } )
          {
            if ( my $kind = InternalStruct( $root->{$field} ) )
              {
                $root->{$field}{$kind}{$specialfield} = 1;
                _traverseFields( $root->{$field}, $specialfield )
                  unless $kind eq 'ENUMERATED';
              }
            elsif ( ref $root->{$field} eq 'HASH' )
              {
                if ( defined $root->{$field}{SEQUENCE} )
                  {
                    $root->{$field}{SEQUENCE}{$specialfield} = 1;
                  }
                else
                  {
                    $root->{$field}{$specialfield} = 1;
                  }
              }
          }
      }
  }

sub upgrade
  {
    print "\tPerforming UPGRADES: \n";

    print "\t\t- mark upgrades ... ";
    &_markupgrades;
    print "DONE\n";

    print "\t\t- interlace structures ... ";
    &_interlacing;
    print "DONE\n";

    print "\t\t- upgrade structures ... ";
    &_upgrading;
    print "DONE\n";
  }

#------------------- Internal functions -------------------------------
sub _markupgrades
  {
    my @all_names = keys %ASN1;

    # High level names
    foreach my $name (@all_names)
      {
        _markstructureupgrades( $name, $name, \@all_names );
      }

    # Internal Names
    foreach my $name (@all_names)
      {
        next unless ref $ASN1{$name} eq 'HASH';

        _markinternalupgrades( $name, $ASN1{$name}{SEQUENCE} )
          if defined $ASN1{$name}{SEQUENCE};
        _markinternalupgrades( $name, $ASN1{$name}{CHOICE} )
          if defined $ASN1{$name}{CHOICE};
      }
  }

sub _upgrading
  {
    foreach my $toUpgrade (@ToUpgrade)
      {
        foreach my $upgrade ( @{ $toUpgrade->{TO_REF}{UPGRADE} } )
          {
            next
              unless $upgrade->{TYPE} eq 'GLOBAL';

            Info("Extending  $toUpgrade->{TO_NAME} with $upgrade->{NAME}");

            my $legacy_result =
              _upgradestructure( $toUpgrade->{TO_NAME}, $toUpgrade->{TO_REF},
                $upgrade->{REF}, $upgrade->{NAME}, 'WEAK', 'OUT',
                $toUpgrade->{TO_REF}, 'ANY' );

            if ( $legacy_result & LEGACY_UPGRADED )
              {
                foreach my $level ( keys %{ $Upgrade{ $upgrade->{NAME} } } )
                  {
                    if ( $Upgrade{ $upgrade->{NAME} }{$level} eq
                        $toUpgrade->{TO_NAME} )
                      {
                        $upgrade->{REF}{EXTENDS}{LEVEL} = $level;
                        last;
                      }
                  }
                my $extends = SkipStruct( $upgrade->{REF} );
                $upgrade->{REF}{SWALLOWED} = 1
                  if defined $extends->{EXTENDS}
                  and defined $extends->{EXTENDS}{REF}
                  and not grep { $extends->{EXTENDS}{REF}{$_} eq 'LEGACY' }
                  keys %{ $extends->{EXTENDS}{REF} };
              }

            $upgrade->{REF}{SWALLOWED} = 1
              if ( $legacy_result & LEGACY_SWALLOWED
                and not $legacy_result & LEGACY_UPGRADED )
              or $legacy_result == LEGACY_IGNORED;
          }
      }
  }

sub _upgradestructure
  {
    my $struct_name      = shift;
    my $upgrade          = shift;
    my $upgrade_with     = shift;
    my $field_name       = shift;
    my $mode             = shift;
    my $level            = shift;
    my $source           = shift;
    my $parentStructType = shift;

    my $upgraded = LEGACY_IGNORED;

    return LEGACY_IGNORED
      if defined $upgrade_with->{IGNORED}
      or defined $upgrade_with->{NOTSUPPORTED};

    my $upgrade_proceed      = SkipStruct($upgrade);
    my $upgrade_with_proceed = SkipStruct($upgrade_with);

    return LEGACY_IGNORED
      if defined $upgrade_with_proceed->{IGNORED}
      or defined $upgrade_with_proceed->{NOTSUPPORTED};

    my $structType = 'ANY';
    $structType = 'CHOICE'
      if ref $upgrade eq 'HASH'
      and defined $upgrade->{CHOICE}
      and ref $upgrade_with eq 'HASH'
      and defined $upgrade_with->{CHOICE};

    return LEGACY_SWALLOWED
      if $level eq 'OUT'
      and defined $upgrade_proceed->{TYPE}
      and defined $upgrade_with_proceed->{TYPE}
      and defined $ASN1{ $upgrade_with_proceed->{TYPE} }{UPGRADED}
      and $upgrade_proceed->{TYPE} eq
      $ASN1{ $upgrade_with_proceed->{TYPE} }{UPGRADED};

    return LEGACY_IGNORED
      if defined $upgrade_with_proceed->{NOTSUPPORTED}
      and defined $upgrade_proceed->{NOTSUPPORTED};

    if (    $mode eq 'STRICT'
        and defined $upgrade_with_proceed->{NOTSUPPORTED}
        and not defined $upgrade_proceed->{NOTSUPPORTED} )
      {
        Warning("Have to ignore NOT SUPPORTED directive for $field_name");
        delete $upgrade_with_proceed->{NOTSUPPORTED};
      }

    if (    $mode eq 'STRICT'
        and not defined $upgrade_with_proceed->{NOTSUPPORTED}
        and defined $upgrade_proceed->{NOTSUPPORTED} )
      {
        Panic("Impossible NOT SUPPORTED configuration for upgrade");
      }

    if (
        $mode eq 'STRICT'
        and (
            (
                not defined $upgrade_proceed->{_ORDER_}
                and defined $upgrade_with_proceed->{_ORDER_}
            )
            or ( defined $upgrade_proceed->{_ORDER_}
                and not defined $upgrade_with_proceed->{_ORDER_} )
        )
      )
      {
        if ( $parentStructType eq 'CHOICE' )
          {
            return LEGACY_CHOICE;
          }
        push @{ $upgrade_proceed->{UPGRADE} }, $upgrade_with_proceed;
        return LEGACY_UPGRADED;
      }

    return LEGACY_IGNORED
      if not defined $upgrade_proceed->{_ORDER_}
      and not defined $upgrade_with_proceed->{_ORDER_};

    foreach my $field ( @{ $upgrade_with_proceed->{_ORDER_} } )
      {
        next if _similarField( $field, $upgrade_proceed->{_ORDER_} ) == YES;
        next
          if defined $upgrade_with_proceed->{$field}{IGNORED}
          or defined $upgrade_with_proceed->{$field}{NOTSUPPORTED};

        $upgrade_with_proceed->{EXTENDS}{NAME} = $struct_name;
        $upgrade_with_proceed->{EXTENDS}{REF}{$field} = 'LEGACY';

        if ( $level eq 'IN' )
          {
            push @{ $upgrade_proceed->{UPGRADE} },
              { FIELD => $field, REF => $upgrade_with_proceed->{$field} };
          }

        $upgraded |= LEGACY_UPGRADED;
      }

    if ( $structType eq 'CHOICE' and $level eq 'IN' )
      {
        foreach my $field ( @{ $upgrade_proceed->{_ORDER_} } )
          {
            next
              if _similarField( $field, $upgrade_with_proceed->{_ORDER_} ) ==
              YES;
            next
              if defined $upgrade_proceed->{$field}{IGNORED}
              or defined $upgrade_proceed->{$field}{NOTSUPPORTED};

            $upgraded |= LEGACY_CHOICE_EXTRA;
          }
      }

    foreach my $field ( @{ $upgrade_with_proceed->{_ORDER_} } )
      {
        next if _similarField( $field, $upgrade_proceed->{_ORDER_} ) == NO;
        next
          if defined $upgrade_with_proceed->{$field}{IGNORED}
          or defined $upgrade_with_proceed->{$field}{NOTSUPPORTED}
          or defined SkipStruct( $upgrade_with_proceed->{$field} )->{IGNORED}
          or
          defined SkipStruct( $upgrade_with_proceed->{$field} )->{NOTSUPPORTED};

        my $upgrade_field =
          _getFieldName( $field, $upgrade_proceed->{_ORDER_} );

        if (
            defined $upgrade_proceed->{$upgrade_field}
            and (   ref $upgrade_proceed->{$upgrade_field} eq 'HASH'
                and ref $upgrade_with_proceed->{$field} eq 'HASH' )
            and (
                (
                        defined $upgrade_proceed->{$upgrade_field}{SEQUENCE}
                    and defined $upgrade_with_proceed->{$field}{SEQUENCE}
                )
                or (    defined $upgrade_proceed->{$upgrade_field}{CHOICE}
                    and defined $upgrade_with_proceed->{$field}{CHOICE} )
            )
          )
          {
            Info("Start Field upgrade $field");
            my $res = _upgradestructure(
                $struct_name . '-' . $field,
                $upgrade_proceed->{$upgrade_field},
                $upgrade_with_proceed->{$field},
                $field_name . '-' . $field,
                'STRICT',
                'IN',
                $source,
                $structType
            );
            $upgraded |= $res;

            if ( $res & LEGACY_UPGRADED or $res & LEGACY_CHOICE_EXTRA )
              {
                $upgrade_with_proceed->{EXTENDS}{NAME} = $struct_name;
                $upgrade_with_proceed->{EXTENDS}{REF}{$field} = 'REFERENCE';
              }

            if ( $res & LEGACY_CHOICE and $level eq 'OUT' )
              {
                $upgrade_with_proceed->{EXTENDS}{NAME} = $struct_name;
                $upgrade_with_proceed->{EXTENDS}{REF}{$field} = 'REFERENCE';
              }
            elsif ( $res & LEGACY_CHOICE and $level eq 'IN' )
              {
                push @{ $upgrade_proceed->{UPGRADE} },
                  { FIELD => $field, REF => $upgrade_with_proceed->{$field} };
              }

            my $conclusion = '';
            $conclusion = 'nothing to upgrade' if $res == LEGACY_IGNORED;
            Info("Finish Field Upgrade $conclusion");
          }
        elsif (
            defined $upgrade_proceed->{$upgrade_field}
            and (   ref $upgrade_proceed->{$upgrade_field} eq 'HASH'
                and ref $upgrade_with_proceed->{$field} eq 'HASH' )
            and (
                (
                    (
                        defined $upgrade_proceed->{$upgrade_field}{SEQUENCE}
                        and not
                        defined $upgrade_with_proceed->{$field}{SEQUENCE}
                    )
                    or
                    ( not defined $upgrade_proceed->{$upgrade_field}{SEQUENCE}
                        and defined $upgrade_with_proceed->{$field}{SEQUENCE} )
                )
                or (
                    (
                        defined $upgrade_proceed->{$upgrade_field}{CHOICE}
                        and not defined $upgrade_with_proceed->{$field}{CHOICE}
                    )
                    or ( not defined $upgrade_proceed->{$upgrade_field}{CHOICE}
                        and defined $upgrade_with_proceed->{$field}{CHOICE} )
                )
            )
          )
          {
            if ( $level eq 'OUT' )
              {
                $upgrade_with_proceed->{EXTENDS}{NAME} = $struct_name;
                $upgrade_with_proceed->{EXTENDS}{REF}{$field} = 'LEGACY';
              }
            else
              {
                push @{ $upgrade_proceed->{$upgrade_field}{UPGRADE} },
                  $upgrade_with_proceed->{$field};
              }
            $upgraded |= LEGACY_UPGRADED;
          }
        elsif (
            defined $upgrade_proceed->{$upgrade_field}

            and ref $upgrade_proceed->{$upgrade_field} eq 'HASH'
            and defined $upgrade_proceed->{$upgrade_field}{KIND}
            and $upgrade_proceed->{$upgrade_field}{KIND} eq 'FREE'

            and ref $upgrade_with_proceed->{$field} eq 'HASH'
            and defined $upgrade_with_proceed->{$field}{KIND}
            and $upgrade_with_proceed->{$field}{KIND} eq 'FREE'

            and $upgrade_with_proceed->{$field}{VALUE} ne
            $upgrade_proceed->{$upgrade_field}{VALUE}

            and (
                    $upgrade_with_proceed->{$field}{VALUE}    ne 'NULL'
                and $upgrade_proceed->{$upgrade_field}{VALUE} ne 'NULL'
                and (
                    (
                        not defined
                        $ASN1{ $upgrade_proceed->{$upgrade_field}{VALUE} }
                        {UPGRADED}
                        and not
                        defined $ASN1{ $upgrade_with_proceed->{$field}{VALUE} }
                        {UPGRADED}
                    )
                    or (
                        defined
                        $ASN1{ $upgrade_proceed->{$upgrade_field}{VALUE} }
                        {UPGRADED}
                        and
                        defined $ASN1{ $upgrade_with_proceed->{$field}{VALUE} }
                        {UPGRADED}
                        and $ASN1{ $upgrade_proceed->{$upgrade_field}{VALUE} }
                        {UPGRADED} ne
                        $ASN1{ $upgrade_with_proceed->{$field}{VALUE} }
                        {UPGRADED} )
                    or (
                        not defined
                        $ASN1{ $upgrade_proceed->{$upgrade_field}{VALUE} }
                        {UPGRADED}
                        and
                        defined $ASN1{ $upgrade_with_proceed->{$field}{VALUE} }
                        {UPGRADED}
                        and $upgrade_proceed->{$upgrade_field}{VALUE} ne
                        $ASN1{ $upgrade_with_proceed->{$field}{VALUE} }
                        {UPGRADED} )
                    or (
                        defined
                        $ASN1{ $upgrade_proceed->{$upgrade_field}{VALUE} }
                        {UPGRADED}
                        and not
                        defined $ASN1{ $upgrade_with_proceed->{$field}{VALUE} }
                        {UPGRADED}
                        and $ASN1{ $upgrade_proceed->{$upgrade_field}{VALUE} }
                        {UPGRADED} ne $upgrade_with_proceed->{$field}{VALUE} )
                )
            )
          )
          {
            if ( $level eq 'OUT' )
              {
                $upgrade_with_proceed->{EXTENDS}{NAME} = $struct_name;
                $upgrade_with_proceed->{EXTENDS}{REF}{$field} = 'LEGACY';
              }
            else
              {
                push @{ $upgrade_proceed->{$upgrade_field}{UPGRADE} },
                  $upgrade_with_proceed->{$field};
              }
            $upgraded |= LEGACY_UPGRADED;
          }
      }

    $upgraded |= LEGACY_SWALLOWED
      if $upgraded == LEGACY_IGNORED
      and scalar @{ $upgrade_proceed->{_ORDER_} } >=
      scalar @{ $upgrade_with_proceed->{_ORDER_} };

    return $upgraded;
  }

sub _similarField
  {
    my $field  = shift;
    my $Fields = shift;

    return YES if grep /^\Q$field\E$/, @$Fields;
    return NO  if $field !~ /\br\d\b/;

    my $field_re = $field;
    $field_re =~ s/\br\d\b/r\\d/;

    return YES if grep /^$field_re$/, @$Fields;
    return NO;
  }

sub _getFieldName
  {
    my $field  = shift;
    my $Fields = shift;

    my @__ = grep /^\Q$field\E$/, @$Fields;

    return $__[0] if @__;
    return undef  if $field !~ /\br\d\b/;

    my $field_re = $field;
    $field_re =~ s/\br\d\b/r\\d/;

    @__ = grep /^$field_re$/, @$Fields;
    return $__[0] if @__;

    return undef;
  }

sub _upgradedWith
  {
    my ( $upgrade_array, $name ) = @_;

    return ( grep { $_->{NAME} eq $name } @{$upgrade_array} ) ? TRUE: FALSE;
  }

sub _interlacing
  {
    foreach my $struct ( keys %{ $MAP{TYPE} } )
      {
        next
          unless ( defined $MAP{TYPE}{$struct}{DATA}->[5]
            and $MAP{TYPE}{$struct}{DATA}->[5] =~
            /RELEASE_VERSION_UPGRADE_R(\d+)/ )
          or ( defined $MAP{TYPE}{$struct}{DATA}->[4]
            and $MAP{TYPE}{$struct}{DATA}->[4] =~
            /RELEASE_VERSION_UPGRADE_R(\d+)/ );

        my $upgrade_level = $1;
        my @candid        = ();

        my $dig_struct = $struct;
        $dig_struct = $MAP{TYPE}{$struct}{ALIAS_FOR}
          if defined $MAP{TYPE}{$struct}{ALIAS_FOR};
        $dig_struct = $MAP{TYPE}{$struct}{REAL}
          if defined $MAP{TYPE}{$struct}{REAL};
        $dig_struct =~ s/_/-/g;

        next if $dig_struct eq 'USELESS';

        if ( defined $Upgrade{$dig_struct} )
          {
            push @candid, $dig_struct;
          }
        else
          {
            my @path           = ();
            my @struct_path    = ();
            my $upgrade_struct =
              _digstruct( $dig_struct, \%ASN1, \@path, \@struct_path );

            if ( $upgrade_struct and ref $upgrade_struct eq 'HASH' )
              {
                if ( defined $Upgrade{ $path[0] } )
                  {
                    foreach my $r ( keys %{ $Upgrade{ $path[0] } } )
                      {
                        my $cand =
                          $Upgrade{ $path[0] }{$r} . '-'
                          . join( '-', @path[ 1 .. $#path ] );

                        if (
                            GetReference(
                                join( '-', @path[ 1 .. $#path ] ),
                                $ASN1{ $path[0] }
                            )
                          )
                          {
                            $Upgrade{ join( '-', @path ) }{$r} = $cand;
                            push @candid, join( '-', @path );
                          }
                      }
                  }
              }
          }

        if ( not @candid or not defined $Upgrade{ $candid[0] } )
          {
            Warning(
                "Don't know how to upgrade $struct to version $upgrade_level");
            next;
          }

        my $actual_upgrade = $upgrade_level;
        while ( not defined $Upgrade{ $candid[0] }{$actual_upgrade} )
          {
            if ( $actual_upgrade =~ /ANY/ )
              {
                $actual_upgrade = 0;
                last;
              }
            elsif ( $actual_upgrade =~ /\d+/ )
              {
                $actual_upgrade-- if $actual_upgrade > 3;
                $actual_upgrade = 'ANY' if $actual_upgrade == 3;
              }
          }

        if ( $actual_upgrade =~ /\d+/ and $actual_upgrade == 0 )
          {
            Warning(
                "Don't know how to upgrade $struct to version $upgrade_level");
            next;
          }

        my $UpgradeFrom = $candid[0];
        my $UpgradeTo   = $Upgrade{ $candid[0] }{$actual_upgrade};

        if ( $UpgradeFrom !~ /\|/ and $UpgradeTo !~ /\|/ )
          {
            my $refUpgradeFrom = GetReference( $UpgradeFrom, \%ASN1 );
            my $refUpgradeTo   = GetReference( $UpgradeTo,   \%ASN1 );
            push @{ $refUpgradeTo->{UPGRADE} },
              {
                NAME => $UpgradeFrom,
                REF  => $refUpgradeFrom,
                TYPE => 'GLOBAL'
              }
              if not grep { $_->{NAME} eq $UpgradeFrom }
              @{ $refUpgradeTo->{UPGRADE} };
            $refUpgradeFrom->{UPGRADED} = $UpgradeTo;
            push @ToUpgrade,
              {
                FROM_REF  => $refUpgradeFrom,
                FROM_NAME => $UpgradeFrom,
                TO_REF    => $refUpgradeTo,
                TO_NAME   => $UpgradeTo
              };
          }
        elsif ( $UpgradeFrom =~ /\|/ and $UpgradeTo =~ /\|/ )
          {
            my @from = split /\|/, $UpgradeFrom;
            my @to   = split /\|/, $UpgradeTo;

            my $refFrom = $ASN1{ $from[0] };
            foreach my $f ( @from[ 1 .. $#from ] )
              {
                $refFrom = $refFrom->{SEQUENCE}{$f}
                  if ref $refFrom eq 'HASH'
                  and defined $refFrom->{SEQUENCE}
                  and defined $refFrom->{SEQUENCE}{$f};
              }

            my $refTo = $ASN1{ $to[0] };
            foreach my $t ( @to[ 1 .. $#to ] )
              {
                $refTo = $refTo->{SEQUENCE}{$t}
                  if ref $refTo eq 'HASH'
                  and defined $refTo->{SEQUENCE}
                  and defined $refTo->{SEQUENCE}{$t};
              }

            if ( $refFrom and $refTo )
              {
                push @{ $refTo->{UPGRADE} },
                  {
                    'TO-FIELD'   => $to[-1],
                    'FROM-FIELD' => $from[-1],
                    'TO-PATH'    => join( "|", @to ),
                    'FROM-PATH'  => join( "|", @from ),
                    'TO-REF'     => $refTo,
                    'FROM-REF'   => $refFrom,
                    TYPE         => 'INTERNAL'
                  }
                  if not grep { $_->{'FROM-FIELD'} eq $from[-1] }
                  @{ $refTo->{UPGRADE} };
                $refFrom->{UPGRADED} = $to[-1];
              }
            else
              {
                Warning(
"Upgrade structures $UpgradeFrom -> $UpgradeTo just disappeared"
                );
                next;
              }
          }
        else
          {
            Warning(
                "Unexcpected upgrade structures $UpgradeFrom -> $UpgradeTo");
            next;
          }

        Info(
            <<LONG_INFO
  Marking $struct for upgrading to release $actual_upgrade(requested $upgrade_level)
        with $Upgrade{$candid[0]}{$actual_upgrade}
LONG_INFO
        );
      }
  }

sub _digstruct
  {
    my $s_name      = shift;
    my $struct      = shift;
    my $path        = shift;
    my $struct_path = shift;

    $struct = SkipStruct($struct);

    my @s_name = split /-/, $s_name;

    my $field = '';
    while (@s_name)
      {
        $field .= '-' if $field;
        $field .= shift @s_name;

        if ( defined $struct->{$field} )
          {
            push @$path,        $field;
            push @$struct_path, $struct;

            if ( defined $struct->{$field}{SEQUENCE} )
              {
                $struct = $struct->{$field}{SEQUENCE};
              }
            elsif ( defined $struct->{$field}{CHOICE} )
              {
                $struct = $struct->{$field}{CHOICE};
              }
            elsif ( defined $struct->{$field}{SEQUENCEOF}
                and defined $struct->{$field}{SEQUENCEOF}{TYPE}
                and ref $struct->{$field}{SEQUENCEOF}{TYPE} eq 'HASH'
                and defined $struct->{$field}{SEQUENCEOF}{TYPE}{SEQUENCE} )
              {
                $struct = $struct->{$field}{SEQUENCEOF}{TYPE}{SEQUENCE};
              }
            elsif ( defined $struct->{$field}{SEQUENCEOF}
                and defined $struct->{$field}{SEQUENCEOF}{TYPE}
                and ref $struct->{$field}{SEQUENCEOF}{TYPE} eq 'HASH'
                and defined $struct->{$field}{SEQUENCEOF}{TYPE}{CHOICE} )
              {
                $struct = $struct->{$field}{SEQUENCEOF}{TYPE}{CHOICE};
              }
            else
              {
                $struct = $struct->{$field};
              }

            $field = '';
          }

        if ( $field and not @s_name )
          {
            push @s_name, split /-/, $field;
            $field  = pop @$path;
            $struct = pop @$struct_path;
          }
      }

    return $struct if not $field;
    return undef;
  }

sub _markinternalupgrades
  {
    my $s_name = shift;
    my $struct = shift;

    my @Fields = ($s_name);
    _listFields( $struct, \@Fields, 0 );

    if ( my @R = grep /\|r\d$/, @Fields )
      {
        foreach my $r (@R)
          {
            $r =~ /\|r(\d)$/;
            my $release = $1;
            foreach my $R (@R)
              {
                $R =~ /\|r(\d)$/;
                my $next_release = $1;

                if ( $next_release > $release )
                  {
                    my $_R_ = $R;
                    $_R_ =~ s/\|/-/g;
                    my $_r_ = $r;
                    $_r_ =~ s/\|/-/g;

                    $Upgrade{$_r_}{$next_release} = $_R_;
                  }
              }
          }
      }
  }

sub _markstructureupgrades
  {
    my $name      = shift;
    my $full_name = shift;
    my $all_names = shift;

    my @candidates = ();

    if ( $name =~ /^r(\d+)$/ )
      {
        my $release = $1;
        @candidates = grep {
            ( /^r(\d+)$/ and $1 > $release )

              # or ( /^later-than-r(\d+)$/ and $1 == $release )
        } @$all_names;
      }
    elsif ( $name =~ /(?:-|\A)r(\d+)\b/ )
      {
        my $release   = $1;
        my $pre_name  = $`;
        my $post_name = $';
        @candidates =
          grep { /^$pre_name(?:-|\A)r(\d+)$post_name$/ and $1 > $release }
          @$all_names;
      }
    else
      {
        @candidates = grep { /^$name-r\d+$/ } @$all_names;
      }

    if (@candidates)
      {
        my @name = split /\|/, $full_name;
        my $candid_head = '';
        $candid_head = join( "|", @name[ 0 .. $#name - 1 ] ) . "|"
          if scalar @name > 1;
        foreach my $candidate (@candidates)
          {
            $candidate =~ /-r(\d+)/;
            $Upgrade{$full_name}{$1} = $candid_head . $candidate;
          }
      }

  }

sub _digFreeFields
  {
    my $root  = shift;
    my @frees = ();

    my $toDig = SkipStruct($root);

    $toDig = {}
      if ref $root eq 'HASH'
      and defined $root->{KIND};

    foreach my $field ( keys %$toDig )
      {
        push @frees, $toDig->{$field}
          if $field eq 'TYPE' and not ref $toDig->{$field};

        next if ref $toDig->{$field} ne 'HASH';

        push @frees, $toDig->{$field}{BITSTRING}{VALUE}[0]
          if defined $toDig->{$field}{BITSTRING}
          and ref $toDig->{$field}{BITSTRING} eq 'HASH'
          and defined $toDig->{$field}{BITSTRING}{KIND}
          and $toDig->{$field}{BITSTRING}{KIND} eq 'CONTAINING'
          and defined $toDig->{$field}{BITSTRING}{VALUE}
          and ref $toDig->{$field}{BITSTRING}{VALUE} eq 'ARRAY'
          and defined $toDig->{$field}{BITSTRING}{VALUE}[0]
          and defined $ASN1{ $toDig->{$field}{BITSTRING}{VALUE}[0] };

        push @frees, $toDig->{$field}{VALUE}
          if defined $toDig->{$field}{KIND}
          and $toDig->{$field}{KIND} eq 'FREE';

        push @frees, $toDig->{$field}
          if $field eq 'TYPE' and not ref $toDig->{$field};

        push @frees, _digFreeFields( $toDig->{$field} )
          if defined $toDig->{$field}{SEQUENCE}
          or defined $toDig->{$field}{CHOICE}
          or defined $toDig->{$field}{SEQUENCEOF};
      }

    push @frees, $root->{VALUE}
      if not %$toDig
      and defined $root->{KIND}
      and $root->{KIND} eq 'FREE';

    return @frees;
  }

sub _notInUse
  {
    my $struct = shift;
    my $toDig  = shift;
    my $manner = shift;

    foreach my $field ( keys %$toDig )
      {
        next
          if ref $toDig->{$field} eq 'HASH'
          and defined $toDig->{$field}{$manner};

        return FALSE
          if $field eq 'TYPE'
          and not ref $toDig->{$field}
          and $toDig->{$field} eq $struct;

        next if ref $toDig->{$field} ne 'HASH';

        return FALSE
          if defined $toDig->{$field}{KIND}
          and $toDig->{$field}{KIND}  eq 'FREE'
          and $toDig->{$field}{VALUE} eq $struct;

        return FALSE
          if defined $toDig->{$field}{SEQUENCE}
          and not defined $toDig->{$field}{SEQUENCE}{$manner}
          and _notInUse( $struct, $toDig->{$field}{SEQUENCE}, $manner ) ==
          FALSE;

        return FALSE
          if defined $toDig->{$field}{CHOICE}
          and not defined $toDig->{$field}{CHOICE}{$manner}
          and _notInUse( $struct, $toDig->{$field}{CHOICE}, $manner ) == FALSE;

        return FALSE
          if defined $toDig->{$field}{SEQUENCEOF}
          and not defined $toDig->{$field}{SEQUENCEOF}{$manner}
          and _notInUse( $struct, $toDig->{$field}{SEQUENCEOF}, $manner ) ==
          FALSE;
      }

    return TRUE;
  }

sub _fastNotInUse
  {
    my $struct = shift;
    my $manner = shift;

    return FALSE if not defined $ASN1Usage{$struct};

    my $res = FALSE;
    foreach my $usedin ( @{ $ASN1Usage{$struct}{USEDIN} } )
      {
        return FALSE
          if _underManner( $ASN1{$usedin}, $struct, $manner, FALSE ) == ABSENT;
      }

    return TRUE;
  }

sub _underManner
  {
    my $root        = shift;
    my $struct      = shift;
    my $special     = shift;
    my $underManner = shift;

    $underManner = TRUE if defined $root->{$special};

    $root = SkipStruct($root);

    if ( defined $root->{_ORDER_} )
      {
        foreach my $field ( @{ $root->{_ORDER_} } )
          {
            my $kind = InternalStruct( $root->{$field} );
            if ($kind)
              {
                $underManner = TRUE if defined $root->{$field}{$kind}{$special};
                $underManner = TRUE if defined $root->{$field}{$special};
                unless ( $kind eq 'ENUMERATED' )
                  {
                    return ABSENT
                      if _underManner( $root->{$field}, $struct, $special,
                        $underManner ) == ABSENT;
                  }
              }

            elsif ( defined $root->{$field}{KIND}
                and $root->{$field}{KIND}  eq 'FREE'
                and $root->{$field}{VALUE} eq $struct )
              {
                return $underManner == TRUE ? FOUND: ABSENT;
              }

            elsif ( defined $root->{$field}{BITSTRING}
                and ref $root->{$field}{BITSTRING} eq 'HASH'
                and defined $root->{$field}{BITSTRING}{VALUE}
                and ref $root->{$field}{BITSTRING}{VALUE} eq 'ARRAY'
                and $root->{$field}{BITSTRING}{VALUE}[0]  eq $struct )
              {
                return $underManner == TRUE ? FOUND: ABSENT;
              }
          }
      }

    return $underManner == TRUE ? FOUND: ABSENT
      if defined $root->{SIZE}
      and ref $root->{SIZE} eq 'ARRAY'
      and (
        (
                defined $root->{SIZE}[0]
            and $root->{SIZE}[0] !~ /^\d+$/
            and $root->{SIZE}[0] eq $struct
        )
        or (    defined $root->{SIZE}[1]
            and $root->{SIZE}[1] !~ /^\d+$/
            and $root->{SIZE}[1] eq $struct )
      );

    return $underManner == TRUE ? FOUND: ABSENT
      if defined $root->{TYPE}
      and not ref $root->{TYPE}
      and $root->{TYPE} eq $struct;

    return $underManner == TRUE ? FOUND: ABSENT
      if defined $root->{VALUE}
      and not ref $root->{VALUE}
      and $root->{VALUE} eq $struct;

    return UNKNOWN;
  }

sub _listFields
  {
    my $root   = shift;
    my $Fields = shift;
    my $index  = shift;

    $root = SkipStruct($root);

    if ( defined $root->{_ORDER_} )
      {
        foreach my $field ( @{ $root->{_ORDER_} } )
          {
            push @$Fields, $Fields->[$index] . "|$field";
            if ( my $kind = InternalStruct( $root->{$field} ) )
              {
                _listFields( $root->{$field}, $Fields, $#{$Fields} )
                  unless $kind eq 'ENUMERATED';
              }
          }
      }
  }

#----------------------------------------------------------------------
1;
