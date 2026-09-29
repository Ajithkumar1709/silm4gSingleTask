#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# ASN.1 Compiler Service Library
#
# Common state machine to read/analyze ASN.1 file
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         09-Aug-2009     KS         1. Initial Version
#-----------------------------------------------------------------------
package Parser;



use strict;
use warnings;

use Data::Dumper;

use Globals;
use Commons qw/:globals :common_func/;

#------------------ Application-wide Variables ---------------
our $DEBUG;
our %ASN1;
our @ASN1Index;
our %ASN1Usage;

#--------------------- State Machine ----------------------
my @asn         = ( \%ASN1 );
my @State       = ('ASIDE');
my $lineCounter = 0;
my %State       = ();
my $Accumulator = '';
my $asnUsage    = '';

%State = (
    ASIDE => sub {
        my $l = shift;

        push @State, 'FILE' if $l =~ /\bBEGIN\b/;
    },

    FILE => sub {
        my $l = shift;

        if ( $l =~ /^\s*([\w\-]+)\s*::=\s*(\S.*?)\s*$/ )
          {
            my $ElemName = $1;
            my $ElemType = $2;

            @{ $ASN1Usage{$ElemName}{USES} }   = ();
            @{ $ASN1Usage{$ElemName}{USEDIN} } = ()
              if not defined $ASN1Usage{$ElemName}{USEDIN};
            $asnUsage = $ElemName;

            if (    $ElemType =~ /(SEQUENCE|CHOICE)\s*\{/
                and $ElemType !~ /SEQUENCE.+OF/ )
              {
                push @State, 'SEQUENCECHOICE';
                $asn[-1]->{$ElemName}{$1} = {};
                push @asn, $asn[-1]->{$ElemName}{$1};

                push @ASN1Index, [ $ElemName, $1 ];
              }

            elsif ( $ElemType =~ /SEQUENCE\s*\((.+)\)\s*OF/ )
              {
                my $value = $1;
                if ( $value =~ /SIZE\s*\(\s*([\-\w]+)\s*\.\.\s*([\-\w]+)\s*\)/ )
                  {
                    my ( $one, $two ) = ( $1, $2 );
                    $asn[-1]->{$ElemName}{SEQUENCEOF}{SIZE} = [ $one, $two ];
                    if ( $one !~ /^-?\d+$/ )
                      {
                        push @{ $ASN1Usage{$ElemName}{USES} }, $one;
                        push @{ $ASN1Usage{$one}{USEDIN} },    $ElemName;
                      }
                    if ( $two !~ /^-?\d+$/ )
                      {
                        push @{ $ASN1Usage{$ElemName}{USES} }, $two;
                        push @{ $ASN1Usage{$two}{USEDIN} },    $ElemName;
                      }
                  }
                elsif ( $value =~ /SIZE\s*\(\s*([\-\w]+)\s*\)/ )
                  {
                    my $one = $1;
                    $asn[-1]->{$ElemName}{SEQUENCEOF}{SIZE} = [$one];
                    if ( $one !~ /^-?\d+$/ )
                      {
                        push @{ $ASN1Usage{$ElemName}{USES} }, $one;
                        push @{ $ASN1Usage{$one}{USEDIN} },    $ElemName;
                      }
                  }
                else
                  {
                    &{ $State{ERROR} }($l);
                  }

                push @State, 'SEQUENCEOF';
                push @asn,   $asn[-1]->{$ElemName}{SEQUENCEOF};
                push @ASN1Index, [ $ElemName, 'SEQUENCEOF' ];

                if ( $l !~ /OF\s*$/ )
                  {
                    $l =~ /OF\s*(.+)$/;
                    &{ $State{ $State[-1] } }($1);
                  }
              }

            elsif ( $ElemType =~ /(BIT|OCTET)\s+STRING\s*\{/ )
              {
                push @State, 'BITOCTETSTRING';
                $asn[-1]->{$ElemName}{ $1 . 'STRING' } = {};
                push @asn, $asn[-1]->{$ElemName}{ $1 . 'STRING' };
                push @ASN1Index, [ $ElemName, $1 . 'STRING' ];
              }

            elsif ( $ElemType =~
                /(BIT|OCTET)\s+STRING\s*\(SIZE\s*\(\s*([\-\w]+)\s*\)\s*\)/ )
              {
                my $two = $2;
                $asn[-1]->{$ElemName}{ $1 . 'STRING' } = [$2];
                push @ASN1Index, [ $ElemName, $1 . 'STRING' ];
                if ( $two !~ /^-?\d+$/ )
                  {
                    push @{ $ASN1Usage{$ElemName}{USES} }, $two;
                    push @{ $ASN1Usage{$two}{USEDIN} },    $ElemName;
                  }
              }
            elsif ( $ElemType =~
/(BIT|OCTET)\s+STRING\s*\(SIZE\s*\(\s*([\-\w]+)\s*\.\.\s*([\-\w]+)\s*\)\s*\)/
              )
              {
                my ( $two, $three ) = ( $2, $3 );
                $asn[-1]->{$ElemName}{ $1 . 'STRING' } = [ $2, $3 ];
                push @ASN1Index, [ $ElemName, $1 . 'STRING' ];
                if ( $two !~ /^-?\d+$/ )
                  {
                    push @{ $ASN1Usage{$ElemName}{USES} }, $two;
                    push @{ $ASN1Usage{$two}{USEDIN} },    $ElemName;
                  }
                if ( $three !~ /^-?\d+$/ )
                  {
                    push @{ $ASN1Usage{$ElemName}{USES} }, $three;
                    push @{ $ASN1Usage{$three}{USEDIN} },  $ElemName;
                  }
              }

            elsif ( $ElemType =~ /ENUMERATED\s*\{\s*(\S.+\S)\s*\}/ )
              {
                my $value = $1;
                $asn[-1]->{$ElemName}{ENUMERATED}{ENUM} = [];
                push @{ $asn[-1]->{$ElemName}{ENUMERATED}{ENUM} },
                  map { s/\s//g; $_ if !/^\s*$/ } grep !/OPTIONAL/, split /,/,
                  $value;
                push @ASN1Index, [ $ElemName, 'ENUMERATED' ];
              }

            elsif ( $ElemType =~ /ENUMERATED\s*\{\s*$/ )
              {
                push @State, 'ENUMERATED';
                $asn[-1]->{$ElemName}{ENUMERATED}{ENUM} = [];
                push @asn, $asn[-1]->{$ElemName}{ENUMERATED};
                push @ASN1Index, [ $ElemName, 'ENUMERATED' ];
              }

            elsif ( $ElemType =~ /ENUMERATED\s*\{\s*(\S.*\S?)\s*$/ )
              {
                push @State, 'ENUMERATED';
                $asn[-1]->{$ElemName}{ENUMERATED}{ENUM} = [];
                push @asn, $asn[-1]->{$ElemName}{ENUMERATED};
                my $value = $1;
                if ( $value !~ /^\s*$/ )
                  {
                    push @{ $asn[-1]->{ENUM} }, split /\s*,\s*/, $value;
                  }
                push @ASN1Index, [ $ElemName, 'ENUMERATED' ];
              }

            elsif ( $ElemType =~
                /INTEGER\s*\(\s*([\-\w]+)\s*\.\.\s*([\-\w]+)\s*\)/ )
              {
                $asn[-1]->{$ElemName}{INTEGER} = [ $1, $2 ];
                push @ASN1Index, [ $ElemName, 'INTEGER' ];
              }

            elsif ( $ElemType =~ /[\-\w]+/ )
              {
                $asn[-1]->{$ElemName}{KIND}  = 'FREE';
                $asn[-1]->{$ElemName}{VALUE} = $ElemType;
                push @ASN1Index, [ $ElemName, 'FREE' ];
                push @{ $ASN1Usage{$ElemName}{USES} },   $ElemType;
                push @{ $ASN1Usage{$ElemType}{USEDIN} }, $ElemName;
              }

            else
              {
                &{ $State{ERROR} }($l);
              }
          }

        elsif ( $l =~ /^\s*([\w\-]+)\s+([\w\-]+)\s*::=\s*([\-\w]+)\s*$/ )
          {
            my $ElemName  = $1;
            my $ElemType  = $2;
            my $ElemValue = $3;

            if ( $ElemType =~ /INTEGER/ )
              {
                $asn[0]->{$ElemName}{$ElemType} = $ElemValue;
                push @ASN1Index, [ $ElemName, $ElemType ];
                @{ $ASN1Usage{$ElemName}{USES} }   = ();
                @{ $ASN1Usage{$ElemName}{USEDIN} } = ()
                  if not defined $ASN1Usage{$ElemName}{USEDIN};
              }
            else
              {
                &{ $State{ERROR} }($l);
              }
          }
        elsif ( $l =~ /^\s*([\w\-]+)\s*::=\s*$/ )
          {
            push @State, 'ACCUMULATOR';
            return &{ $State{ $State[-1] } }($l);
          }
        elsif ( $l =~ /^\s*END\s*$/ )
          {
            pop @State;
          }
        elsif ( $l =~ /IMPORTS/ )
          {
            push @State, 'IGNORE';
            return &{ $State{ $State[-1] } }($l);
          }
        else
          {
            &{ $State{ERROR} }($l);
          }
    },

    IGNORE => sub {
        my $l = shift;

        pop @State if $l =~ /;\s*$/;

    },

    SEQUENCECHOICE => sub {
        my $l = shift;

        if ( $l =~ /::=/ )
          {
            &{ $State{ERROR} }($l);
          }

        $l =~ s/(BIT|OCTET)\s+STRING/$1STRING/;

        if (
            (
                    $l =~ /{.*}/
                and $l !~
/{.*}.*(?:,|}|},|{|OPTIONAL\s*,?|}\s*OPTIONAL|}\s*OPTIONAL\s*,)\s*$/
            )
            or (    $l !~ /{.*}/
                and $l !~
                /(?:,|}|},|{|OPTIONAL\s*,|}\s*OPTIONAL|}\s*OPTIONAL\s*,)\s*$/ )
          )
          {
            push @State, 'ACCUMULATOR';
            return &{ $State{ $State[-1] } }($l);
          }

        if ( my $kw = _findKeyword($l) )
          {
            if ( $l =~
/^(\s*([\-\w]+)\s+($kw)\s*(?:DEFAULT\s+([\-\w]+))?\s*(?:,|}|},|OPTIONAL\s*,|}\s*OPTIONAL|}\s*OPTIONAL\s*,|OPTIONAL)\s*).*$/
              )
              {
                my $realLine = $1;
                my $field    = $2;
                my $value    = $3;
                $asn[-1]->{$field}{VALUE}    = [$value];
                $asn[-1]->{$field}{OPTIONAL} = 1 if $realLine =~ /\bOPTIONAL\b/;
                $asn[-1]->{$field}{DEFAULT}  = $1
                  if $realLine =~ /\bDEFAULT\b\s+([\-\w]+)/;

                push @{ $asn[-1]->{_ORDER_} }, $field;

                if ( $l =~ /\s*(?:}|},|}\s*OPTIONAL|}\s*OPTIONAL\s*,)\s*$/ )
                  {
                    pop @State;
                    pop @asn;
                  }
                return;
              }

            $l =~ /^\s*([\-\w]+)/;
            my $elemName = $1;

            $kw = 'SEQUENCE(.+)OF'
              if $kw eq 'SEQUENCE' and $l =~ /SEQUENCE.+OF/;

            if ( $l =~
/($kw\s*\(\s*(\S.*)\s*\)\s*(?:DEFAULT\s+([\-\w]+))?\s*(?:OPTIONAL)?)/
              )
              {
                my $realLine = $1;
                my $value    = $2;

                if ( $value =~ /SIZE\s*\(\s*([\-\w]+)\s*\.\.\s*([\-\w]+)\s*\)/ )
                  {
                    my ( $v1, $v2 ) = ( $1, $2 );
                    $asn[-1]->{$elemName}{$kw}{DEFAULT} = $1
                      if $realLine =~ /DEFAULT\s+([\-\w]+)/;
                    $asn[-1]->{$elemName}{$kw}{OPTIONAL} = 1
                      if $realLine =~ /\bOPTIONAL\b/;

                    if ( $v1 !~ /^-?\d+$/ )
                      {
                        push @{ $ASN1Usage{$asnUsage}{USES} }, $v1;
                        push @{ $ASN1Usage{$v1}{USEDIN} },     $asnUsage;
                      }
                    if ( $v2 !~ /^-?\d+$/ )
                      {
                        push @{ $ASN1Usage{$asnUsage}{USES} }, $v2;
                        push @{ $ASN1Usage{$v2}{USEDIN} },     $asnUsage;
                      }
                    push @{ $asn[-1]->{_ORDER_} }, $elemName;

                    if ( $kw eq 'SEQUENCEOF' )
                      {
                        $asn[-1]->{$elemName}{$kw}{SIZE} = [ $v1, $v2 ];

                        push @State, 'SEQUENCEOF';
                        push @asn,   $asn[-1]->{$elemName}{$kw};

                        return &{ $State{ $State[-1] } }($1)
                          if $l =~ /OF\s*(\S.*)$/;
                      }
                    else
                      {
                        $asn[-1]->{$elemName}{$kw}{VALUE} = [ $v1, $v2 ];
                        $asn[-1]->{$elemName}{$kw}{KIND} = 'SIZE_INTERVAL';
                      }
                  }
                elsif ( $value =~ /SIZE\s*\(\s*([\-\w]+)\s*\)/ )
                  {
                    my $v1 = $1;
                    $asn[-1]->{$elemName}{$kw}{VALUE}   = [$v1];
                    $asn[-1]->{$elemName}{$kw}{KIND}    = 'SIZE_MAGNITUDE';
                    $asn[-1]->{$elemName}{$kw}{DEFAULT} = $1
                      if $realLine =~ /DEFAULT\s+([\-\w]+)/;
                    $asn[-1]->{$elemName}{$kw}{OPTIONAL} = 1
                      if $realLine =~ /\bOPTIONAL\b/;

                    if ( $v1 !~ /^-?\d+$/ )
                      {
                        push @{ $ASN1Usage{$asnUsage}{USES} }, $v1;
                        push @{ $ASN1Usage{$v1}{USEDIN} },     $asnUsage;
                      }
                    push @{ $asn[-1]->{_ORDER_} }, $elemName;
                  }
                elsif ( $value =~ /CONTAINING\s*([\-\w]+)/ )
                  {
                    my $v1 = $1;
                    $asn[-1]->{$elemName}{$kw}{VALUE}   = [$v1];
                    $asn[-1]->{$elemName}{$kw}{KIND}    = 'CONTAINING';
                    $asn[-1]->{$elemName}{$kw}{DEFAULT} = $1
                      if $realLine =~ /DEFAULT\s+([\-\w]+)/;
                    $asn[-1]->{$elemName}{$kw}{OPTIONAL} = 1
                      if $realLine =~ /\bOPTIONAL\b/;

                    if ( $v1 !~ /^-?\d+$/ )
                      {
                        push @{ $ASN1Usage{$asnUsage}{USES} }, $v1;
                        push @{ $ASN1Usage{$v1}{USEDIN} },     $asnUsage;
                      }
                    push @{ $asn[-1]->{_ORDER_} }, $elemName;
                  }
                elsif ( $value =~ /([\-\w]+)\s*\.\.\s*([\-\w]+)/ )
                  {
                    my ( $v1, $v2 ) = ( $1, $2 );
                    $asn[-1]->{$elemName}{$kw}{VALUE}   = [ $v1, $v2 ];
                    $asn[-1]->{$elemName}{$kw}{KIND}    = 'INTERVAL';
                    $asn[-1]->{$elemName}{$kw}{DEFAULT} = $1
                      if $realLine =~ /DEFAULT\s+([\-\w]+)/;
                    $asn[-1]->{$elemName}{$kw}{OPTIONAL} = 1
                      if $realLine =~ /\bOPTIONAL\b/;

                    if ( $v1 !~ /^-?\d+$/ )
                      {
                        push @{ $ASN1Usage{$asnUsage}{USES} }, $v1;
                        push @{ $ASN1Usage{$v1}{USEDIN} },     $asnUsage;
                      }
                    if ( $v2 !~ /^-?\d+$/ )
                      {
                        push @{ $ASN1Usage{$asnUsage}{USES} }, $v2;
                        push @{ $ASN1Usage{$v2}{USEDIN} },     $asnUsage;
                      }
                    push @{ $asn[-1]->{_ORDER_} }, $elemName;
                  }
                elsif ( $value =~ /([\-\w]+)/ )
                  {
                    my $v1 = $1;
                    $asn[-1]->{$elemName}{$kw}{VALUE}   = [$v1];
                    $asn[-1]->{$elemName}{$kw}{KIND}    = 'MAGNITUDE';
                    $asn[-1]->{$elemName}{$kw}{DEFAULT} = $1
                      if $realLine =~ /DEFAULT\s+([\-\w]+)/;
                    $asn[-1]->{$elemName}{$kw}{OPTIONAL} = 1
                      if $realLine =~ /\bOPTIONAL\b/;

                    if ( $v1 !~ /^-?\d+$/ )
                      {
                        push @{ $ASN1Usage{$asnUsage}{USES} }, $v1;
                        push @{ $ASN1Usage{$v1}{USEDIN} },     $asnUsage;
                      }
                    push @{ $asn[-1]->{_ORDER_} }, $elemName;
                  }
                else
                  {
                    &{ $State{ERROR} }($l);
                  }
              }
            elsif ( $l =~ /($kw\s*\{\s*([^}]+)\s*\}\s*(?:OPTIONAL)?\s*,?)/ )
              {
                my $realLine = $1;
                my $value    = $2;
                $asn[-1]->{$elemName}{$kw}{DEFAULT} = $1
                  if $l =~ /DEFAULT\s+([\-\w]+)/;
                $asn[-1]->{$elemName}{$kw}{OPTIONAL} = 1
                  if $realLine =~ /\bOPTIONAL\b/;

                push @{ $asn[-1]->{_ORDER_} }, $elemName;

                if ( $value =~ /^\s*$/ )
                  {
                    $asn[-1]->{$elemName}{$kw}{VALUE} = {};
                    $asn[-1]->{$elemName}{$kw}{KIND}  = 'EMPTY';
                  }
                else
                  {
                    push @{ $asn[-1]->{$elemName}{$kw}{VALUE} },
                      map { s/\s//g; $_ } split /,/, $value;
                    $asn[-1]->{$elemName}{$kw}{KIND} = 'LIST';
                  }
              }
            elsif ( $l =~ /$kw\s*{\s*$/ )
              {
                $asn[-1]->{$elemName}{$kw} = {};

                push @{ $asn[-1]->{_ORDER_} }, $elemName;

                push @State, 'SEQUENCECHOICE' if $kw =~ /SEQUENCE|CHOICE/;
                push @State, 'ENUMERATED' if $kw eq 'ENUMERATED';
                push @State, 'BITOCTETSTRING'
                  if $kw eq 'BITSTRING'
                  or $kw eq 'OCTETSTRING';

                push @asn, $asn[-1]->{$elemName}{$kw};
              }

            elsif ( $l =~ /$kw\s*\{\s*([^}]+)\s*$/ )
              {
                if ( $kw eq 'ENUMERATED' )
                  {
                    push @State, 'ENUMERATED';
                    $asn[-1]->{$elemName}{ENUMERATED} = {};

                    push @{ $asn[-1]->{_ORDER_} }, $elemName;

                    push @asn, $asn[-1]->{$elemName}{ENUMERATED};
                    my $value = $1;
                    if ( $value !~ /^\s*$/ )
                      {
                        push @{ $asn[-1]->{ENUM} }, split /\s*,\s*/, $value;
                      }
                  }
                else
                  {
                    &{ $State{ERROR} }($l);
                  }
              }

            elsif ( $l =~ /$kw\s*\{\s*\}\s*(?:OPTIONAL)?/ )
              {
                $asn[-1]->{$elemName}{$kw}{VALUE}   = {};
                $asn[-1]->{$elemName}{$kw}{KIND}    = 'EMPTY';
                $asn[-1]->{$elemName}{$kw}{DEFAULT} = $1
                  if $l =~ /DEFAULT\s+([\-\w]+)/;
                $asn[-1]->{$elemName}{$kw}{OPTIONAL} = 1
                  if $l =~ /\bOPTIONAL\b/;

                push @{ $asn[-1]->{_ORDER_} }, $elemName;
              }
            elsif ( $l =~ /$kw\s*([\-\w]+)\s*(?:OPTIONAL)?/ )
              {
                my $value = $1;
                my $type  = $2;
                if ( $value =~ /SIZE\s*\(\s*([\-\w]+)\s*\.\.\s*([\-\w]+)\s*\)/ )
                  {
                    my ( $one, $two ) = ( $1, $2 );
                    $asn[-1]->{$elemName}{SEQUENCEOF}{SIZE} = [ $one, $two ];
                  }
                elsif ( $value =~ /SIZE\s*\(\s*([\-\w]+)\s*\)/ )
                  {
                    my $one = $1;
                    $asn[-1]->{$elemName}{SEQUENCEOF}{SIZE} = [$one];
                  }
                else
                  {
                    &{ $State{ERROR} }($l);
                  }

                $asn[-1]->{$elemName}{SEQUENCEOF}{OPTIONAL} = 1
                  if $l =~ /\bOPTIONAL\b/;

                push @{ $asn[-1]->{_ORDER_} }, $elemName;

                push @State, 'SEQUENCEOF';
                push @asn,   $asn[-1]->{$elemName}{SEQUENCEOF};

                if ( $l !~ /OF\s*$/ )
                  {
                    $l =~ /OF\s*(.+)$/;
                    return &{ $State{ $State[-1] } }($1);
                  }

              }
            else
              {
                &{ $State{ERROR} }($l);
              }

            # in case a field that contains a keyword placed last
            if (
                (
                        $l !~ /{.*}/
                    and $l =~ /\s*(}|},|}\s*OPTIONAL|}\s*OPTIONAL\s*,)\s*$/
                )
                or (    $l =~ /{.*}/
                    and $l =~ /{.*}.*(}|},|}\s*OPTIONAL|}\s*OPTIONAL\s*,)\s*$/ )
              )
              {
                my $finale = $1;
                $asn[-1]->{OPTIONAL} = 1 if $finale =~ /\bOPTIONAL\b/;
                $asn[-1]->{DEFAULT} = $1
                  if $finale =~ /\bDEFAULT\b\s+([\-\w]+)/;

                pop @State;
                pop @asn;
              }

            return;
          }

        if ( $l =~ /^\s*(?:}|},|}\s*OPTIONAL|}\s*OPTIONAL\s*,)\s*$/ )
          {
            $asn[-1]->{OPTIONAL} = 1 if $l =~ /\bOPTIONAL\b/;
            $asn[-1]->{DEFAULT} = $1
              if $l =~ /\bDEFAULT\b\s+([\-\w]+)/;

            pop @State;
            pop @asn;
          }
        elsif ( $l =~ /([\-\w]+)\s+([\-\w]+)/ )
          {
            my $field = $1;
            my $value = $2;
            $asn[-1]->{$field}{VALUE} = $value;

            my @l = ();
            if ( $l =~ /}/ )
              {
                @l = split /}/, $l;
                $l[1] = '' if not $l[1];
                $l[1] = '} ' . $l[1];
              }
            else
              {
                $l[0] = $l;
              }

            $asn[-1]->{$field}{KIND}    = 'FREE';
            $asn[-1]->{$field}{DEFAULT} = $1
              if $l[0] =~ /DEFAULT\s+([\-\w]+)/;
            $asn[-1]->{$field}{OPTIONAL} = 1
              if $l[0] =~ /\bOPTIONAL\b/;

            push @{ $asn[-1]->{_ORDER_} }, $field;
            push @{ $ASN1Usage{$asnUsage}{USES} }, $value;
            push @{ $ASN1Usage{$value}{USEDIN} },  $asnUsage;

            if (    $l[1]
                and $l[1] =~
                /\s*(?:}|}\s*,|}\s*OPTIONAL|}\s*OPTIONAL\s*,)\s*$/ )
              {
                $asn[-1]->{OPTIONAL} = 1 if $l[1] =~ /\bOPTIONAL\b/;

                pop @State;
                pop @asn;
              }
          }
        elsif ( $l =~ /\.{3}/ )
          {
            $asn[-1]->{ETC} = 1;

            my @l = ();
            if ( $l =~ /}/ )
              {
                @l = split /}/, $l;
                $l[1] = '' if not $l[1];
                $l[1] = '} ' . $l[1];
              }
            else
              {
                $l[0] = $l;
              }

            if (    $l[1]
                and $l[1] =~
                /\s*(?:}|}\s*,|}\s*OPTIONAL|}\s*OPTIONAL\s*,)\s*$/ )
              {
                $asn[-1]->{OPTIONAL} = 1 if $l[1] =~ /\bOPTIONAL\b/;

                pop @State;
                pop @asn;
              }
          }
        else
          {
            &{ $State{ERROR} }($l);
          }
    },

    SEQUENCEOF => sub {
        my $l = shift;

        if ( $l =~ /::=/ or defined $asn[-1]->{TYPE} )
          {
            pop @State;
            pop @asn;

            return &{ $State{ $State[-1] } }($l);
          }

        $l =~ s/(BIT|OCTET)\s+STRING/$1STRING/;

        if ( my $kw = _findKeyword($l) )
          {
            if ( $l =~ /$kw\s*\(\s*([\-\w]+)\s*\.\.\s*([\-\w]+)\s*\)/ )
              {
                my ( $one, $two ) = ( $1, $2 );
                if ( $one !~ /^-?\d+$/ )
                  {
                    push @{ $ASN1Usage{$asnUsage}{USES} }, $one;
                    push @{ $ASN1Usage{$one}{USEDIN} },    $asnUsage;
                  }
                if ( $two !~ /^-?\d+$/ )
                  {
                    push @{ $ASN1Usage{$asnUsage}{USES} }, $two;
                    push @{ $ASN1Usage{$two}{USEDIN} },    $asnUsage;
                  }
                $asn[-1]->{TYPE}{$kw} = [ $one, $two ];
                $asn[-1]->{OPTIONAL} = 1 if $l =~ /\bOPTIONAL\b/;
                $asn[-1]->{DEFAULT} = $1
                  if $l =~ /\bDEFAULT\b\s+([\-\w]+)/;

                pop @State;
                pop @asn;
              }
            elsif ( $l =~ /$kw\s*\(SIZE\s*\(\s*([\-\w]+)\s*\)\s*\)/ )
              {
                my $one = $1;
                if ( $one !~ /^-?\d+$/ )
                  {
                    push @{ $ASN1Usage{$asnUsage}{USES} }, $one;
                    push @{ $ASN1Usage{$one}{USEDIN} },    $asnUsage;
                  }
                $asn[-1]->{TYPE}{$kw} = [$one];
                $asn[-1]->{OPTIONAL} = 1 if $l =~ /\bOPTIONAL\b/;
                $asn[-1]->{DEFAULT} = $1
                  if $l =~ /\bDEFAULT\b\s+([\-\w]+)/;

                pop @State;
                pop @asn;
              }
            elsif ( $l =~
                /$kw\s*\(SIZE\s*\(\s*([\-\w]+)\s*\.\.\s*([\-\w]+)\s*\)\s*\)/ )
              {
                my ( $one, $two ) = ( $1, $2 );
                if ( $one !~ /^-?\d+$/ )
                  {
                    push @{ $ASN1Usage{$asnUsage}{USES} }, $one;
                    push @{ $ASN1Usage{$one}{USEDIN} },    $asnUsage;
                  }
                if ( $two !~ /^-?\d+$/ )
                  {
                    push @{ $ASN1Usage{$asnUsage}{USES} }, $two;
                    push @{ $ASN1Usage{$two}{USEDIN} },    $asnUsage;
                  }
                $asn[-1]->{TYPE}{$kw} = [ $one, $two ];
                $asn[-1]->{OPTIONAL} = 1 if $l =~ /\bOPTIONAL\b/;
                $asn[-1]->{DEFAULT} = $1
                  if $l =~ /\bDEFAULT\b\s+([\-\w]+)/;

                pop @State;
                pop @asn;
              }
            elsif ( $l =~ /$kw\s*{\s*$/ )
              {
                $asn[-1]->{TYPE}{$kw} = {};

                push @State, 'SEQUENCECHOICE' if $kw =~ /SEQUENCE|CHOICE/;
                if ( $kw eq 'ENUMERATED' )
                  {
                    push @State, 'ENUMERATED';
                    $asn[-1]->{TYPE}{$kw} = {};
                  }
                if ( $kw eq 'BITSTRING' or $kw eq 'OCTETSTRING' )
                  {
                    push @State, 'BITOCTETSTRING';
                  }
                push @asn, $asn[-1]->{TYPE}{$kw};
              }
            elsif ( $l =~ /$kw\s*\{\s*([^}]+)\s*\}\s*(?:OPTIONAL)?/ )
              {
                my $value = $1;
                if ( $value !~ /^\s*$/ )
                  {
                    if ( $kw eq 'ENUMERATED' )
                      {
                        push @{ $asn[-1]->{TYPE}{$kw}{ENUM} },
                          map { s/\s//g; $_ } split /,/, $value;
                      }
                    else
                      {
                        push @{ $asn[-1]->{TYPE}{$kw} },
                          map { s/\s//g; $_ } split /,/, $value;
                      }
                    $asn[-1]->{$kw}{OPTIONAL} = 1 if $l =~ /\bOPTIONAL\b/;
                    $asn[-1]->{$kw}{DEFAULT} = $1
                      if $l =~ /\bDEFAULT\b\s+([\-\w]+)/;
                  }

                pop @State;
                pop @asn;
              }
            else
              {
                &{ $State{ERROR} }($l);
              }
          }
        elsif ( $l =~ /([\-\w]+)/ )
          {
            push @{ $ASN1Usage{$asnUsage}{USES} }, $1;
            push @{ $ASN1Usage{$1}{USEDIN} },      $asnUsage;

            $asn[-1]->{TYPE}     = $1;
            $asn[-1]->{OPTIONAL} = 1 if $l =~ /\bOPTIONAL\b/;
            $asn[-1]->{DEFAULT}  = $1
              if $l =~ /\bDEFAULT\b\s+([\-\w]+)/;

            pop @State;
            pop @asn;

          }
        else
          {
            &{ $State{ERROR} }($l);
          }

        if (
            (
                    $l =~ /{.*}/
                and $l =~ /{.*}.*(}|},|}\s*OPTIONAL|}\s*OPTIONAL\s*,)\s*$/
            )
            or (    $l !~ /{.*}/
                and $l =~ /(}|},|}\s*OPTIONAL|}\s*OPTIONAL\s*,)\s*$/ )
          )
          {
            return &{ $State{ $State[-1] } }($1);
          }

    },

    BITOCTETSTRING => sub {
        my $l = shift;

        if ( $l =~ /::=/ )
          {
            &{ $State{ERROR} }($l);
          }

        if ( $l !~
/(?:,|}|},|{|OPTIONAL\s*,|}\s*OPTIONAL|}\s*OPTIONAL\s*,|BITOCTETSTRING-STOP)\s*$/
          )
          {
            push @State, 'ACCUMULATOR';
            return &{ $State{ $State[-1] } }($l);
          }

        my @fullLine = split /}/, $l;
        my @l = map { s/\s//g; $_ if !/^\s*$/ } grep !/OPTIONAL/, split /,/,
          $fullLine[0];

        push @{ $asn[-1]->{VALUE} }, grep !/^\s*$/, @l;
        if ( defined $fullLine[1]
            and $fullLine[1] =~ /\(\s*SIZE\s*\(\s*([\-\w]+)\s*\)\s*\)/ )
          {
            $asn[-1]->{SIZE}     = $1;
            $asn[-1]->{OPTIONAL} = 1 if $l =~ /\bOPTIONAL\b/;
            $asn[-1]->{DEFAULT}  = $1
              if $l =~ /\bDEFAULT\b\s+([\-\w]+)/;
            pop @State;
            pop @asn;
          }

        # second time if this field is the last one
        if ( $l =~ /\s*(?:}|},|}\s*OPTIONAL|}\s*OPTIONAL\s*,)\s*$/ )
          {
            $asn[-1]->{OPTIONAL} = 1 if $l =~ /\bOPTIONAL\b/;
            $asn[-1]->{DEFAULT} = $1
              if $l =~ /\bDEFAULT\b\s+([\-\w]+)/;
            pop @State;
            pop @asn;
          }

    },

    ENUMERATED => sub {
        my $l = shift;
        $l =~ s/__ENUM-END__/}/;

        if ( $l =~ /::=/ )
          {
            &{ $State{ERROR} }($l);
          }

        if ( $l =~ /}/ and $State[-2] eq 'FILE' and $l !~ /.*}\s*$/ )
          {
            &{ $State{ERROR} }($l);
          }

        if (
            (
                    $l =~ /}/
                and $State[-2] ne 'FILE'
                and $l !~
/.*}.*(?:,|}|},|{|OPTIONAL\s*,|}\s*OPTIONAL|}\s*OPTIONAL\s*,)\s*$/
            )

            or (    $l !~ /}/
                and $l !~ /(?:,|{)\s*$/ )
          )
          {
            push @State, 'ACCUMULATOR';
            $l =~ s/}/__ENUM-END__/;
            return &{ $State{ $State[-1] } }($l);
          }

        my ( $l1, $l2 ) = ( $l, '' );
        if ( $l =~ /^([^}]+})(.*)$/ )
          {
            ( $l1, $l2 ) = ( $1, $2 );
          }
        my @l = map { s/\s//g; $_ } grep !/^\s*$/, grep !/OPTIONAL/,
          split /[,}]/, $l1;

        if ( grep /\.{3}/, @l )
          {
            $asn[-1]->{ETC} = 1;
          }

        push @{ $asn[-1]->{ENUM} }, grep !/\.{3}/, @l;

        if (    $l !~ /}.*}/
            and $l =~
/\s*(?:}|}\s*,|}\s*OPTIONAL|}\s*OPTIONAL\s*,|}\s*DEFAULT\s+[\-\w]+,?)\s*$/
          )
          {
            $asn[-1]->{OPTIONAL} = 1 if $l =~ /\bOPTIONAL\b/;
            $asn[-1]->{DEFAULT} = $1
              if $l =~ /\bDEFAULT\b\s+([\-\w]+)/;

            pop @State;
            pop @asn;
          }
        elsif ( $l =~ /}.*}/
            and $l =~
/\s*(?:}|}\s*,|}\s*OPTIONAL|}\s*OPTIONAL\s*,|}\s*DEFAULT\s+[\-\w]+,?\s*})\s*$/
          )
          {
            $l =~ /^([^}]+}.*)(}.*)$/;
            my ( $one, $two ) = ( $1, $2 );

            $asn[-1]->{OPTIONAL} = 1 if $one =~ /\bOPTIONAL\b/;
            $asn[-1]->{DEFAULT} = $1
              if $one =~ /\bDEFAULT\b\s+([\-\w]+)/;

            pop @State;
            pop @asn;

            return &{ $State{ $State[-1] } }($two);
          }

    },

    ACCUMULATOR => sub {
        my $l = shift;

        if ( $l =~ /::=/ and $State[-2] and $State[-2] ne 'FILE' )
          {
            pop @State;
            my $finalLine = $Accumulator . " $State[-1]-STOP ";
            $Accumulator = '';
            &{ $State{ $State[-1] } }($finalLine);
            &{ $State{ $State[-1] } }($l);
            return;
          }

        $Accumulator .= " $l";

        if (
            (
                    $Accumulator =~ /{.*}/
                and $Accumulator =~
/{.*}.*(?:,|}|},|{|OPTIONAL\s*,|}\s*OPTIONAL|}\s*OPTIONAL\s*,?)\s*$/
            )
            or (    $Accumulator !~ /{.*}/
                and $Accumulator =~
                /(?:,|}|},|{|OPTIONAL\s*,|}\s*OPTIONAL|}\s*OPTIONAL\s*,?)\s*$/ )
          )
          {
            pop @State;
            my $finalLine = $Accumulator;
            $Accumulator = '';
            &{ $State{ $State[-1] } }($finalLine);
          }
    },

    ERROR => sub {
        my $l = shift;

        Error("\n#$lineCounter :: $l");
      }
);

#--------------------- Main i/f Function --------------------
sub parse
  {
    my $file = shift;

    Panic("Failed to open $file") if not open( ASN1, "<$file" );

    print "Parsing $file ... ";

    while ( my $line = readline ASN1 )
      {
        $lineCounter++;

        next if $line =~ /^\s*$/;
        next if $line =~ /^\s*--/;

        $line =~ s/^(.+)--.*$/$1/;

        chomp $line;

        if ( $line =~ /(?:}.*){2,}/ )
          {
            my $pos = 0;

            while ( ( my $nextpos = index $line, '}', $pos ) != -1 )
              {
                my $subline = substr $line, $pos, $nextpos + 1;
                &{ $State{ERROR} }($line) if not defined $State{ $State[-1] };

                &{ $State{ $State[-1] } }($subline);
                $pos = $nextpos + 1;
              }
            &{ $State{ERROR} }($line) if not defined $State{ $State[-1] };

            &{ $State{ $State[-1] } }( substr( $line, $pos + 1 ) )
              if length $line >= $pos + 1
              and substr( $line, $pos + 1 ) !~ /^\s*$/;
          }
        elsif ( $line =~ tr/,/,/ > 1 )
          {
            my @line = split /,/, $line;
            for ( my $i = 0 ; $i <= $#line ; $i++ )
              {
                next if $line[$i] =~ /^\s*$/;
                my $end = ',';
                $end = '' if $i == $#line and $line !~ /,\s*$/;
                &{ $State{ERROR} }( $line[$i] . $end )
                  if not defined $State{ $State[-1] };
                &{ $State{ $State[-1] } }( $line[$i] . $end );
              }
          }
        else
          {
            &{ $State{ERROR} }($line) if not defined $State{ $State[-1] };
            &{ $State{ $State[-1] } }($line);
          }
      }

    close ASN1;

    print "DONE\n";

    return $State[-1];
  }

#-----------------------------------------------------------------------
sub _findKeyword
  {
    $_[0] =~
      /(SEQUENCE|CHOICE|ENUMERATED|OCTETSTRING|BITSTRING|OCTETSTRING|INTEGER)/
      ? $1
      : '';
  }

#-----------------------------------------------------------------------
1;

