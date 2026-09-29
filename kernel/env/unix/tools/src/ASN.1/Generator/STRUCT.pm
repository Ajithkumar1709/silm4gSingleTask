#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# ASN.1 Compiler Service Library
#
# Proceed SEQUENCE and CHOICE types
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         11-Nov-2009     KS         1. Initial Version
#-----------------------------------------------------------------------
package Generator::STRUCT;



use strict;
use warnings;

use Globals;
use Commons qw/:globals :common_func :filecodes/;

use Composer::SEQUENCE;
use Composer::CHOICE;
use Composer::TYPEDEF;

use Composer::Commons;

#------------------ Application-wide Variables ---------------
our $DEBUG;
our $VERBOSE;
our %ASN1;
our %ASN1Index;
our %MAP;

# -------------------- Main i/f functions --------------------
sub generate
  {
    my ( $Files, $struct, $Params, $Generated, $what ) = @_;

    if ( $struct->[1] eq 'BITSTRING' or $struct->[1] eq 'INTEGER' )
      {
        @{ $ASN1{ $struct->[0] } }{qw/DONE CODE_DONE/} = (1) x 2;
        ( $ASN1{ $struct->[0] }{LABEL}, $ASN1{ $struct->[0] }{USED} ) =
          Composer::TYPEDEF::compose( 'TYPEDEF', $Files,
            $ASN1{ $struct->[0] }{ $struct->[1] },
            $struct->[0], $struct->[1], $Params->{TYPEPREFIX} );

        $$Generated = TRUE;
      }
    elsif ( $struct->[1] eq 'SEQUENCEOF' )
      {
        if (
            my @Ready = _readySEQUENCEOF(
                $ASN1{ $struct->[0] }{ $struct->[1] },
                $struct->[0], $what
            )
          )
          {
            if ( $Ready[1] ne $struct->[0] or $Ready[2] ne 'SEQUENCEOF' )
              {
                $Ready[0]->{LABEL} =
                  _writeSTRUCT( $Files, @Ready, undef,
                    ( defined $ASN1{ $struct->[0] }{STATIC} ? 1 : 0 ),
                    $Params );
                ( $Ready[0]->{DONE}, $Ready[0]->{CODE_DONE} ) = (1) x 2;
              }
            else
              {
                $ASN1{ $struct->[0] }{LABEL} =
                  _writeSTRUCT( $Files, @Ready,, undef,
                    ( defined $ASN1{ $struct->[0] }{STATIC} ? 1 : 0 ),
                    $Params );
                @{ $ASN1{ $struct->[0] } }{qw/DONE CODE_DONE/} = (1) x 2;
              }
            $$Generated = TRUE;
          }
      }
    elsif ( $struct->[1] eq 'OCTETSTRING' )
      {
        if ( defined $ASN1{ $struct->[0] }{DONE}
            and $ASN1{ $struct->[0] }{DONE} == 2 )
          {
            $ASN1{ $struct->[0] }{USED}  = $ASN1{ $struct->[0] }{LABEL};
            $ASN1{ $struct->[0] }{LABEL} = Composer::STRING::compose(
                'OCTETSTRING',                         $Files,
                $ASN1{ $struct->[0] }{ $struct->[1] }, $struct->[0],
                $Params->{TYPEPREFIX},                 'STATIC',
                $ASN1{ $struct->[0] }{LABEL}
            );
            @{ $ASN1{ $struct->[0] } }{qw/DONE CODE_DONE/} = (1) x 2;

            $$Generated = TRUE;
          }
      }
    elsif ( $struct->[1] eq 'FREE' )
      {
        if (    defined $ASN1{ $ASN1{ $struct->[0] }{VALUE} }
            and defined $ASN1{ $ASN1{ $struct->[0] }{VALUE} }{DONE}
            and $ASN1{ $ASN1{ $struct->[0] }{VALUE} }{DONE} == 1 )
          {
            $ASN1{ $struct->[0] }{LABEL} =
              Composer::TYPEDEF::compose( 'FREE', $Files, $ASN1{ $struct->[0] },
                $struct->[0], $Params->{TYPEPREFIX},
                $ASN1{ $ASN1{ $struct->[0] }{VALUE} }{LABEL} );
            @{ $ASN1{ $struct->[0] } }{qw/DONE CODE_DONE/} = (1) x 2;

            $$Generated = TRUE;
          }
        elsif ( $ASN1{ $struct->[0] }{VALUE} eq 'BOOLEAN' )
          {
            $ASN1{ $struct->[0] }{LABEL} =
              Composer::TYPEDEF::compose( 'BOOLEAN', $Files, $struct->[0],
                $Params->{TYPEPREFIX} );
            @{ $ASN1{ $struct->[0] } }{qw/DONE CODE_DONE/} = (1) x 2;

            $$Generated = TRUE;
          }
      }
    else
      {
        my @Done = ();

        while (
            my @Ready = &_readyForWriting(
                $ASN1{ $struct->[0] }{ $struct->[1] },
                $struct->[0], $struct->[1], 'OUT', $what
            )
          )
          {
            if ( $Ready[1] ne $struct->[0] )
              {
                my $rest = $Ready[1];
                $rest =~ s/^\Q$struct->[0]-\E//;
                my $root = GetReference( $rest, $ASN1{ $struct->[0] } );

                my $upgrade = undef;
                $upgrade = $Ready[0]->{UPGRADE}
                  if defined $Ready[0]->{UPGRADE}
                  and (
                    $Ready[2] ne 'SEQUENCE'
                    or ( $Ready[2] eq 'SEQUENCE'
                        and _realUpgrade( $Ready[0]->{UPGRADE} ) == TRUE )
                  );
                $upgrade = $root->{UPGRADE}
                  if not $upgrade
                  and defined $root
                  and defined $root->{UPGRADE};

                push @Done,
                  [
                    $Ready[0],
                    _writeSTRUCT(
                        $Files, @Ready, $upgrade,
                        ( defined $ASN1{ $struct->[0] }{STATIC} ? 1 : 0 ),
                        $Params
                    )
                  ];
                $Ready[0]->{SEEN} = 1;
              }
            else
              {
                push @Done,
                  [
                    $ASN1{ $struct->[0] },
                    _writeSTRUCT(
                        $Files, @Ready,
                        (
                            defined $ASN1{ $struct->[0] }{UPGRADE}
                            ? $ASN1{ $struct->[0] }{UPGRADE}
                            : undef
                        ),
                        ( defined $ASN1{ $struct->[0] }{STATIC} ? 1 : 0 ),
                        $Params
                    )
                  ];
                $ASN1{ $struct->[0] }{ $struct->[1] }{SEEN} = 1;
              }

            $$Generated = TRUE;
          }
        foreach my $done (@Done)
          {
            $done->[0]{LABEL} = $done->[1];
            $done->[0]{DONE}  = 1;
          }
      }
  }

#-------------------------------------------------------------
sub _readySEQUENCEOF
  {
    my $struct = shift;
    my $name   = shift;
    my $what   = shift;

    return () if ref $struct eq 'HASH' and defined $struct->{SEEN};

    return ( $struct, $name, 'SEQUENCEOF' )
      if ref $struct eq 'HASH'
      and defined $struct->{TYPE}
      and (
        (
            defined $ASN1{ $struct->{TYPE} }{DONE}
            and $ASN1{ $struct->{TYPE} }{DONE} == 1
        )
        or (
            ref $struct->{TYPE} eq 'HASH'
            and (  defined $struct->{TYPE}{INTEGER}
                or defined $struct->{TYPE}{BITSTRING}
                or defined $struct->{TYPE}{OCTETSTRING} )
        )
        or (    defined $ASN1{ $struct->{TYPE} }{SWALLOWED}
            and defined $ASN1{ $struct->{TYPE} }{UPGRADED}
            and defined $ASN1{ $ASN1{ $struct->{TYPE} }{UPGRADED} }
            and defined $ASN1{ $ASN1{ $struct->{TYPE} }{UPGRADED} }{DONE}
            and $ASN1{ $ASN1{ $struct->{TYPE} }{UPGRADED} }{DONE} == 1 )
      )
      and not defined $struct->{SEEN}
      and $what eq 'USUAL';

    return ( $struct, $name, 'SEQUENCEOF' )
      if ref $struct eq 'HASH'
      and defined $struct->{TYPE}
      and ref $struct->{TYPE} eq 'HASH'
      and defined $struct->{TYPE}{SEQUENCE}
      and defined $struct->{TYPE}{SEQUENCE}{DONE}
      and $struct->{TYPE}{SEQUENCE}{DONE} == 1
      and $what eq 'USUAL';

    return _readyForWriting( $struct->{TYPE}{SEQUENCE},
        $name, 'SEQUENCE', 'IN', $what )
      if ref $struct eq 'HASH'
      and defined $struct->{TYPE}
      and ref $struct->{TYPE} eq 'HASH'
      and defined $struct->{TYPE}{SEQUENCE}
      and not defined $struct->{TYPE}{SEQUENCE}{DONE};

    return ( $struct, $name, 'SEQUENCEOF' )
      if ref $struct eq 'HASH'
      and defined $struct->{TYPE}
      and ref $struct->{TYPE} eq 'HASH'
      and defined $struct->{TYPE}{CHOICE}
      and defined $struct->{TYPE}{CHOICE}{DONE}
      and $struct->{TYPE}{CHOICE}{DONE} == 1
      and $what eq 'USUAL';

    return _readyForWriting( $struct->{TYPE}{CHOICE}, $name, 'CHOICE', 'IN',
        $what )
      if ref $struct eq 'HASH'
      and defined $struct->{TYPE}
      and ref $struct->{TYPE} eq 'HASH'
      and defined $struct->{TYPE}{CHOICE}
      and not defined $struct->{TYPE}{CHOICE}{DONE};

    return ();
  }

sub _readyForWriting
  {
    my $struct = shift;
    my $name   = shift;
    my $type   = shift;
    my $level  = shift;
    my $what   = shift;

    return ()
      if $name ne '_NONAME_'
      and ref $ASN1{$name} eq 'HASH'
      and defined $ASN1{$name}{NOTSUPPORTED};

    return ()
      if $name ne '_NONAME_'
      and ref $ASN1{$name} eq 'HASH'
      and defined $ASN1{$name}{DONE}
      and $ASN1{$name}{DONE} == 1;

    return () if defined $struct->{DONE} and $struct->{DONE} == 1;

    my $notReady = FALSE;

    foreach my $field ( @{ $struct->{_ORDER_} } )
      {
        next
          if defined $struct->{EXTENDS}
          and defined $struct->{EXTENDS}{REF}
          and not defined $struct->{EXTENDS}{REF}{$field};

        if (    defined $struct->{EXTENDS}
            and defined $struct->{EXTENDS}{REF}
            and defined $struct->{EXTENDS}{REF}{$field}
            and $struct->{EXTENDS}{REF}{$field} eq 'REFERENCE' )
          {
            if (    ref $struct->{$field} eq 'HASH'
                and defined $struct->{$field}{SEQUENCE}
                and not defined $struct->{$field}{SEQUENCE}{DONE} )
              {
                my @ready = _readyForWriting( $struct->{$field}{SEQUENCE},
                    "$name-$field", 'SEQUENCE', 'IN', $what );
                return @ready
                  if @ready
                  and (
                    $what eq 'UPGRADE_ONLY'
                    or ( $what eq 'USUAL'
                        and not defined $struct->{$field}{EXTENDS} )
                  );
                $notReady = TRUE;
              }

            if (    ref $struct->{$field} eq 'HASH'
                and defined $struct->{$field}{CHOICE}
                and not defined $struct->{$field}{CHOICE}{DONE} )
              {
                my @ready = _readyForWriting( $struct->{$field}{CHOICE},
                    "$name-$field", 'CHOICE', 'IN', $what );
                return @ready
                  if @ready
                  and (
                    $what eq 'UPGRADE_ONLY'
                    or ( $what eq 'USUAL'
                        and not defined $struct->{$field}{EXTENDS} )
                  );
                $notReady = TRUE;
              }

            $notReady = TRUE
              if not grep { $struct->{EXTENDS}{REF}{$_} ne 'REFERENCE' }
              keys %{ $struct->{EXTENDS}{REF} };

            next;
          }

        next
          if ref $struct->{$field} eq 'HASH'
          and defined $struct->{$field}{DONE}
          and $struct->{$field}{DONE} == 1;

        next
          if ref $struct->{$field} eq 'HASH'
          and (
                defined $struct->{$field}{KIND}
            and $struct->{$field}{KIND} eq 'FREE'
            and (  $struct->{$field}{VALUE} eq 'NULL'
                or $struct->{$field}{VALUE} eq 'BOOLEAN' )
          );

        next
          if ref $struct->{$field} eq 'HASH'
          and (
            defined $struct->{$field}{NOTSUPPORTED}
            or (    defined $struct->{$field}{SEQUENCE}
                and defined $struct->{$field}{SEQUENCE}{NOTSUPPORTED} )
            or (    defined $struct->{$field}{CHOICE}
                and defined $struct->{$field}{CHOICE}{NOTSUPPORTED} )
          );

        if (    ref $struct->{$field} eq 'HASH'
            and defined $struct->{$field}{SEQUENCE}
            and not defined $struct->{$field}{SEQUENCE}{DONE} )
          {
            my @ready = _readyForWriting( $struct->{$field}{SEQUENCE},
                "$name-$field", 'SEQUENCE', 'IN', $what );
            return @ready if @ready;
            $notReady = TRUE;
          }

        if (    ref $struct->{$field} eq 'HASH'
            and defined $struct->{$field}{CHOICE}
            and not defined $struct->{$field}{CHOICE}{DONE} )
          {
            my @ready = _readyForWriting( $struct->{$field}{CHOICE},
                "$name-$field", 'CHOICE', 'IN', $what );
            return @ready if @ready;
            $notReady = TRUE;
          }

        if (    ref $struct->{$field} eq 'HASH'
            and defined $struct->{$field}{SEQUENCEOF}
            and not defined $struct->{$field}{SEQUENCEOF}{DONE} )
          {
            my @ready = _readySEQUENCEOF( $struct->{$field}{SEQUENCEOF},
                "$name-$field", $what );
            return @ready if @ready;
          }

        $notReady = TRUE
          if ref $struct->{$field} eq 'HASH'
          and (
            (
                (
                        defined $struct->{$field}{KIND}
                    and $struct->{$field}{KIND} eq 'FREE'
                    and not defined $ASN1{ $struct->{$field}{VALUE} }{UPGRADED}
                )
                and (
                    not defined $ASN1{ $struct->{$field}{VALUE} }{DONE}
                    or ( defined $ASN1{ $struct->{$field}{VALUE} }{DONE}
                        and $ASN1{ $struct->{$field}{VALUE} }{DONE} != 1 )
                )
                and
                ( not defined $ASN1{ $struct->{$field}{VALUE} }{NOTSUPPORTED} )
            )
            or (
                defined $struct->{$field}{SEQUENCEOF}
                and (
                    not defined $struct->{$field}{SEQUENCEOF}{DONE}
                    or ( defined $struct->{$field}{SEQUENCEOF}{DONE}
                        and $struct->{$field}{SEQUENCEOF}{DONE} != 1 )
                )
            )
            or (
                (
                        defined $struct->{$field}{KIND}
                    and $struct->{$field}{KIND} eq 'FREE'
                    and defined $ASN1{ $struct->{$field}{VALUE} }{UPGRADED}
                )
                and (
                    not
                    defined $ASN1{ $ASN1{ $struct->{$field}{VALUE} }{UPGRADED} }
                    {DONE}
                    or (
                        defined
                        $ASN1{ $ASN1{ $struct->{$field}{VALUE} }{UPGRADED} }
                        {DONE}
                        and $ASN1{ $ASN1{ $struct->{$field}{VALUE} }{UPGRADED} }
                        {DONE} != 1 )
                )
                and (
                    not
                    defined $ASN1{ $ASN1{ $struct->{$field}{VALUE} }{UPGRADED} }
                    {NOTSUPPORTED} )
            )
            or (    defined $struct->{$field}{BITSTRING}
                and ref $struct->{$field}{BITSTRING} eq 'HASH'
                and defined $struct->{$field}{BITSTRING}{KIND}
                and $struct->{$field}{BITSTRING}{KIND} eq 'CONTAINING'
                and defined $ASN1{ $struct->{$field}{BITSTRING}{VALUE}[0] }
                {SEQUENCE}
                and not
                defined $ASN1{ $struct->{$field}{BITSTRING}{VALUE}[0] }{DONE} )
          );
      }

    return () if $notReady == TRUE;

    if (    $level eq 'OUT'
        and defined $ASN1{$name}
        and defined $ASN1{$name}{UPGRADE} )
      {
        foreach my $upgrade ( @{ $ASN1{$name}{UPGRADE} } )
          {
            next      if defined $upgrade->{REF}{SWALLOWED};
            return () if not defined $upgrade->{REF}{DONE};
          }
      }

    if ( $level eq 'IN'
        and defined $struct->{UPGRADE} )
      {
        my $upgrade_ready = YES;
        foreach my $upgrade ( @{ $struct->{UPGRADE} } )
          {
            next if defined $upgrade->{REF}{SWALLOWED};
            next if defined $upgrade->{REF}{DONE};

            next
              if defined $upgrade->{REF}
              and defined $upgrade->{REF}{KIND}
              and $upgrade->{REF}{KIND} eq 'FREE'
              and defined $ASN1{ $upgrade->{REF}{VALUE} }{DONE};

            $upgrade_ready = NO;
          }
        return () if $upgrade_ready == NO;
      }

    my $root = GetReference( $name, \%ASN1 );
    if (    $level eq 'IN'
        and defined $root
        and defined $root->{UPGRADE} )
      {
        my $upgrade_ready = YES;
        foreach my $upgrade ( @{ $root->{UPGRADE} } )
          {
            next if not defined $upgrade->{REF};
            next if defined $upgrade->{REF}{SWALLOWED};
            next if defined $upgrade->{REF}{DONE};

            $upgrade->{REF} = SkipStruct( $upgrade->{REF} );
            next if not defined $upgrade->{REF};
            next if defined $upgrade->{REF}{SWALLOWED};
            next if defined $upgrade->{REF}{DONE};

            if (
                    defined $upgrade->{REF}{EXTENDS}
                and defined $upgrade->{REF}{EXTENDS}{REF}
                and not scalar
                grep { $upgrade->{REF}{EXTENDS}{REF}{$_} eq 'LEGACY' }
                keys %{ $upgrade->{REF}{EXTENDS}{REF} }
              )
              {

                foreach my $f ( keys %{ $upgrade->{REF}{EXTENDS}{REF} } )
                  {
                    $upgrade_ready = NO
                      if not defined $upgrade->{REF}{$f}{DONE};
                  }
                next;
              }

            next
              if defined $upgrade->{REF}
              and defined $upgrade->{REF}{KIND}
              and $upgrade->{REF}{KIND} eq 'FREE'
              and defined $ASN1{ $upgrade->{REF}{VALUE} }{DONE};

            $upgrade_ready = NO;
          }
        return () if $upgrade_ready == NO;
      }

    return ( $struct, $name, $type )
      if not defined $struct->{SEEN}
      and (
        $what ne 'UPGRADE_ONLY'
        or ( $what eq 'UPGRADE_ONLY'
            and ( defined $struct->{UPGRADED} or defined $struct->{EXTENDS} ) )
      );

    return ();
  }

sub _writeSTRUCT
  {
    my $Files   = shift;
    my $struct  = shift;
    my $name    = shift;
    my $type    = shift;
    my $upgrade = shift;
    my $static  = shift;
    my $Params  = shift;

    my $_name =
      ( ref $struct eq 'HASH' and defined $struct->{EXTENDS} )
      ? $struct->{EXTENDS}{NAME}
      : $name;

    my $map = GetGivenName(
        ( ref $struct eq 'HASH' and defined $struct->{EXTENDS} )
        ? $struct->{EXTENDS}{NAME}
        : $name
    );

    if ( $type eq 'SEQUENCE' )
      {
        return Composer::SEQUENCE::compose( 'HEADER', $Files, $name,
            $map ? $map : $name,
            $struct, $upgrade, $static, $Params->{TYPEPREFIX} );
      }
    elsif ( $type eq 'CHOICE' )
      {
        return Composer::CHOICE::compose( 'HEADER', $Files, $name,
            $map ? $map : $name,
            $struct, $upgrade, $static, $Params->{TYPEPREFIX} );
      }
    elsif ( $type eq 'SEQUENCEOF' )
      {
        return _writeSEQUENCEOF(
            $Files->[MAIN][HANDLE],
            $map ? $map : $name,
            $struct, $static, $Params
        );
      }
    else
      {
        Error("Undefined structure");
      }

  }

sub _writeSEQUENCEOF
  {
    my ( $File, $map, $struct, $masterStatic, $Params ) = @_;

    my $struct_name = '';
    $struct_name = Composer::Commons::GetName( $map, 'FACTUAL' ) if ref $map;
    if ( not ref $map )
      {
        $struct_name = $map;
        $struct_name =~ s/-/_/g;
        $struct_name .= '_seq';
        Warning("No name for $map in MAP file");
      }

    $masterStatic = 1 if defined $struct->{STATIC};

    Composer::Commons::WriteHeader( $File, $map, $Params->{TYPEPREFIX},
        $struct_name );

    my ( $lowerBound, $upperBound ) = ( undef, undef );
    if ( scalar @{ $struct->{SIZE} } == 2 )
      {
        $lowerBound = $struct->{SIZE}[0];
        $upperBound = $struct->{SIZE}[1];
      }
    elsif ( scalar @{ $struct->{SIZE} } == 1 )
      {
        $upperBound = $struct->{SIZE}[0];
      }

    $upperBound =~ s/-/_/g;

    my $typename    = undef;
    my $elementname = undef;

    if ( ref $struct->{TYPE} eq 'HASH' and defined $struct->{TYPE}{INTEGER} )
      {
        $typename =
"Int8 /* $struct->{TYPE}{INTEGER}[0] to $struct->{TYPE}{INTEGER}[1] */";
        $typename =
"Int16 /* $struct->{TYPE}{INTEGER}[0] to $struct->{TYPE}{INTEGER}[1] */"
          if $struct->{TYPE}{INTEGER}[1] > 256;
      }
    elsif ( ref $struct->{TYPE} eq 'HASH'
        and defined $struct->{TYPE}{BITSTRING}
        and ref $struct->{TYPE}{BITSTRING} eq 'ARRAY'
        and ref $map
        and defined $map->{REAL}
        and defined $ASN1{ $map->{REAL} }{LABEL} )
      {
        $typename = $ASN1{ $map->{REAL} }{LABEL};
      }
    elsif ( ref $struct->{TYPE} eq 'HASH'
        and defined $struct->{TYPE}{SEQUENCE}
        and defined $struct->{TYPE}{SEQUENCE}{LABEL} )
      {
        $typename = $struct->{TYPE}{SEQUENCE}{LABEL};
      }
    elsif ( ref $struct->{TYPE} eq 'HASH'
        and defined $struct->{TYPE}{CHOICE}
        and defined $struct->{TYPE}{CHOICE}{LABEL} )
      {
        $typename = $struct->{TYPE}{CHOICE}{LABEL};
      }
    elsif ( not ref $struct->{TYPE}
        and defined $ASN1{ $struct->{TYPE} }
        and defined $ASN1{ $struct->{TYPE} }{LABEL} )
      {
        $typename = $ASN1{ $struct->{TYPE} }{LABEL};
      }
    elsif ( not ref $struct->{TYPE}
        and defined $ASN1{ $struct->{TYPE} }
        and defined $ASN1{ $struct->{TYPE} }{SWALLOWED}
        and defined $ASN1{ $struct->{TYPE} }{UPGRADED}
        and defined $ASN1{ $ASN1{ $struct->{TYPE} }{UPGRADED} }
        and defined $ASN1{ $ASN1{ $struct->{TYPE} }{UPGRADED} }{LABEL} )
      {
        $typename = $ASN1{ $ASN1{ $struct->{TYPE} }{UPGRADED} }{LABEL};
      }
    elsif ( ref $map and defined $map->{ELEMENT} )
      {
        $typename    = $Params->{TYPEPREFIX} . $struct_name . 'Element';
        $elementname = $map->{ELEMENT};
      }
    else
      {
        Error("Cannot estimate type name");
      }

    my $type_offset = ' ' x ( 55 - ( 4 + length($typename) ) );
    $type_offset = ' ' if not $type_offset;

    if ($elementname)
      {
        printf $File <<LINKED_LIST, ($typename) x 3, ($struct_name) x 2;
typedef struct %sTag
{
    $Params->{TYPEPREFIX}$elementname                     data;
    struct %sTag *next;
}
%s;

typedef struct $Params->{TYPEPREFIX}%sTag
{
    $typename *firstElement;

}
$Params->{TYPEPREFIX}%s;


LINKED_LIST

        $struct->{POINTER} = 1;
      }
    elsif (
        (
            defined $ASN1{ $struct->{TYPE} }
            and (
                   defined $ASN1{ $struct->{TYPE} }{ENUMERATED}
                or defined $ASN1{ $struct->{TYPE} }{INTEGER}
                or defined $ASN1{ $struct->{TYPE} }{STATIC}

                or Composer::Commons::LikeIntegerLoosely(
                    $ASN1{ $struct->{TYPE} }
                )

                or Composer::Commons::LikeStatic( $ASN1{ $struct->{TYPE} } ) ==
                TRUE
            )
        )
        or (
            ref $struct->{TYPE} eq 'HASH'
            and (  defined $struct->{TYPE}{INTEGER}
                or defined $struct->{TYPE}{ENUMERATED} )
        )
        or _belowThreshold(
            Composer::Commons::GetInteger($upperBound),
            $Params->{SEQOFTHRE}
        )
        or $masterStatic
      )
      {

        printf $File <<STRUCT_SEQUENCEOF, $Params->{TYPEPREFIX}, $struct_name;
typedef struct %s%sTag
{
STRUCT_SEQUENCEOF

        if ( defined $lowerBound )
          {
            print $File <<BOUNDARIES
    Int16 n; /* $lowerBound to $upperBound */
BOUNDARIES
          }

        printf $File <<REST_SEQUENCEOF, $type_offset;
    $typename%sdata [$upperBound];
}
$Params->{TYPEPREFIX}$struct_name;


REST_SEQUENCEOF
      }
    else
      {
        my $offset1 = ' ' x ( 55 - ( length("    $typename") + 1 ) );
        $offset1 = ' ' if not $offset1;

        printf $File
          <<LINKEDLIST_SEQUENCEOF, ( $Params->{TYPEPREFIX}, $struct_name ) x 5;
typedef struct %s%sElementTag
{
    $typename$offset1 data;
    struct %s%sElementTag *next;
}
%s%sElement;

typedef struct %s%sTag
{
    %s%sElement *firstElement;

}
$Params->{TYPEPREFIX}$struct_name;


LINKEDLIST_SEQUENCEOF

        $struct->{POINTER} = 1;
      }

    return "$Params->{TYPEPREFIX}$struct_name";
  }

sub _belowThreshold
  {
    my $int       = shift;
    my $threshold = shift;

    return TRUE  if not $threshold;
    return FALSE if not $int;

    return $int < $threshold;
  }

sub _realUpgrade
  {
    my $upgrade = shift;

    foreach my $u (@$upgrade)
      {
        next if defined $u->{FIELD};
        return TRUE;
      }

    return FALSE;
  }

#-------------------------------------------------------------
1;
