#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# ASN.1 Compiler Service Library
#
# Proceed SEQUENCE types
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         18-Aug-2009     KS         1. Initial Version
#-----------------------------------------------------------------------
package Composer::SEQUENCE;



use strict;
use warnings;

use Globals;
use Commons qw/:globals :common_func :filecodes/;

use Composer::Commons;

#------------------ Application-wide Variables ---------------
our $DEBUG;
our %ASN1;
our %ASN1Index;
our %MAP;

# -------------------- Main i/f functions --------------------
sub compose
  {
    my $kind = shift;

    return _composeHEADER(@_) if $kind eq 'HEADER';
    return _composeCODE( 'COMMON', @_ ) if $kind eq 'CODE';
  }

sub _composeHEADER
  {
    my ( $Files, $name, $map, $struct, $upgrade, $masterStatic, $structPrefix )
      = @_;

    return _composeMainHeader( $Files->[MAIN][HANDLE],
        $name, $map, $struct, $upgrade, $masterStatic, $structPrefix );
  }

sub _composeCODE
  {
    my $kind      = shift;
    my $Files     = shift;
    my $sequence  = shift;
    my $root_name = shift;
    my $Params    = shift;

    my $ref = undef;
    $ref = $ASN1{ $sequence->[0] } if $kind eq 'COMMON';
    $ref = $sequence if $kind eq 'INTERNAL';

    my $name = $root_name;
    while ( my $int_ref = _sequenceReady( $Files, $ref, \$name, $Params ) )
      {
        _composeEncode(
            $Files->[ENCS][HANDLE],
            $int_ref,
            (
                defined $int_ref->{DECODE_ONLY}
                  or (  defined $int_ref->{SEQUENCE}
                    and defined $int_ref->{SEQUENCE}{DECODE_ONLY} )
              ) ? TRUE: FALSE,
            $name,
            $Params->{TYPEPREFIX}
        );
        _composeDecode(
            $Files->[DECS][HANDLE],
            $int_ref, $int_ref,
            (
                defined $int_ref->{DECODE_ONLY}
                  or (  defined $int_ref->{SEQUENCE}
                    and defined $int_ref->{SEQUENCE}{DECODE_ONLY} )
              ) ? TRUE: FALSE
        );
        $int_ref->{CODE_DONE} = 1;
        $name = $root_name;
      }
  }

sub _composeMainHeader
  {
    my ( $File, $name, $map, $struct, $upgrade, $masterStatic, $structPrefix ) =
      @_;

    my $struct_name = '';
    $struct_name = Composer::Commons::GetName($map) if ref $map;
    if ( not ref $map )
      {
        $struct_name = $map;
        $struct_name =~ s/-/_/g;
        Warning("No name for $map in MAP file");
      }

    $masterStatic = 1 if defined $struct->{STATIC};

    if ( defined $struct->{EXTENDS} )
      {
        my $extend = 'r3';
        $extend       = $1 if $name =~ /\b(r\d+)(?:-IEs)?$/;
        $structPrefix = 'X' . $extend . $structPrefix;

        return "$structPrefix$struct_name"
          if not scalar grep !/dummy/, keys %{ $struct->{EXTENDS}{REF} };
      }

    my $Code  = '';
    my $Print = TRUE;

    $Code .= sprintf <<SEQUENCE_HEADER, $structPrefix, $struct_name;
typedef struct %s%sTag
{
SEQUENCE_HEADER

    my $dummyCounter = '';
    my $fieldsFound  = FALSE;
    foreach my $field ( @{ $struct->{_ORDER_} } )
      {
        next
          if defined $struct->{EXTENDS}
          and not defined $struct->{EXTENDS}{REF}{$field};

        next
          if $field =~ /dummy\d*/
          and scalar @{ $struct->{_ORDER_} } > 1
          and defined $struct->{$field}{OPTIONAL};

        next
          if $field =~ /dummy\d*/
          and scalar @{ $struct->{_ORDER_} } > 1
          and (
            not(    ref $struct->{$field} eq 'HASH'
                and defined $struct->{$field}{KIND}
                and $struct->{$field}{KIND} eq 'FREE'
                and defined $ASN1{ $struct->{$field}{VALUE} } )
            or (
                (
                        ref $struct->{$field} eq 'HASH'
                    and defined $struct->{$field}{KIND}
                    and $struct->{$field}{KIND} eq 'FREE'
                    and defined $ASN1{ $struct->{$field}{VALUE} }
                )
                and ( not defined $ASN1{ $struct->{$field}{VALUE} }{SEQUENCEOF}
                    and not defined $ASN1{ $struct->{$field}{VALUE} }{CHOICE} )
            )
          );

        next
          if defined $struct->{$field}{KIND}
          and $struct->{$field}{KIND}  eq 'FREE'
          and $struct->{$field}{VALUE} eq 'NULL';

        my $field_name = $field;
        $field_name =~ s/-/_/g;
        my $orig_field_name = $field_name;

        my $optional =
          Composer::Commons::GetField( $struct->{$field}, 'OPTIONAL', $struct,
            $field, 'ANY', $structPrefix );

        my $asterisk = '*';
        if (
            (
                ref $struct->{$field} eq 'HASH'
                and (
                    (
                            defined $struct->{$field}{KIND}
                        and $struct->{$field}{KIND} eq 'FREE'
                        and defined $ASN1{ $struct->{$field}{VALUE} }
                        and
                        ( defined $ASN1{ $struct->{$field}{VALUE} }{ENUMERATED}
                            or
                            defined $ASN1{ $struct->{$field}{VALUE} }{INTEGER}
                            or
                            defined $ASN1{ $struct->{$field}{VALUE} }{STATIC} )
                    )
                    or ( defined $struct->{$field}{BITSTRING}
                        and not defined $struct->{$field}{BITSTRING}{OPTIONAL} )
                    or (    defined $struct->{$field}{BITSTRING}
                        and defined $struct->{$field}{BITSTRING}{KIND}
                        and $struct->{$field}{BITSTRING}{KIND} eq 'CONTAINING'
                        and defined $struct->{$field}{BITSTRING}{VALUE}
                        and ref $struct->{$field}{BITSTRING}{VALUE} eq 'ARRAY'
                        and defined $struct->{$field}{BITSTRING}{VALUE}[0]
                        and
                        defined $ASN1{ $struct->{$field}{BITSTRING}{VALUE}[0] }
                        and
                        defined $ASN1{ $struct->{$field}{BITSTRING}{VALUE}[0] }
                        {STATIC} )
                    or defined $struct->{$field}{ENUMERATED}
                    or defined $struct->{$field}{INTEGER}
                    or (    defined $struct->{$field}{SEQUENCE}
                        and defined $struct->{$field}{SEQUENCE}{STATIC} )
                    or (    defined $struct->{$field}{SEQUENCEOF}
                        and defined $struct->{$field}{SEQUENCEOF}{STATIC} )
                    or (    defined $struct->{$field}{CHOICE}
                        and defined $struct->{$field}{CHOICE}{STATIC} )
                )
            )
            or $masterStatic
          )
          {
            $asterisk = '';
          }
        elsif ($optional)
          {
            $asterisk = '*';
          }
        elsif ( Composer::Commons::LikeIntegerLoosely( $struct->{$field} ) )
          {
            $asterisk = '';
          }
        else
          {
            $asterisk = '';
          }

        my $needDefine   = FALSE;
        my $defineSource = [];

        my $label = Composer::Commons::UpdateLabel(
            Composer::Commons::GetField(
                $struct->{$field}, 'LABEL',
                $struct,           $field,
                'SEQUENCE',        $structPrefix
            ),
            $struct->{$field},
            \$field_name,
            \$asterisk,
            $dummyCounter,
            \$needDefine,
            \$defineSource
        );

        $asterisk = '' if $masterStatic;

        $asterisk = '*'
          if $optional == 1
          and ref $struct->{$field} eq 'HASH'
          and defined $struct->{$field}{SEQUENCE}
          and defined $struct->{$field}{SEQUENCE}{KIND}
          and $struct->{$field}{SEQUENCE}{KIND} eq 'EMPTY';

        $asterisk = '*'
          if $optional == 1
          and ref $struct->{$field} eq 'HASH'
          and defined $struct->{$field}{VALUE}
          and ref $struct->{$field}{VALUE} eq 'ARRAY'
          and defined $struct->{$field}{VALUE}[0]
          and $struct->{$field}{VALUE}[0] eq 'BITSTRING';

        my $field_offset =
          ' ' x ( 50 - ( 4 + length($label) + length($asterisk) ) );
        $field_offset = ' ' if not $field_offset;

        $Code .= sprintf <<OPTIONAL_FIELD, $orig_field_name if $optional;
    Boolean                                       %sPresent;
OPTIONAL_FIELD

        $Code .=
          Composer::Commons::WriteInternalDefines( $field_name,
            $struct->{$field}, $defineSource )
          if $needDefine == TRUE;

        $Code .= sprintf
          <<FIELD, $label, $field_offset, $asterisk, $field_name unless $field_name =~ /_dummy\d*_/ and scalar @{ $struct->{_ORDER_} } > 1;
    %s%s%s%s;
FIELD
        $struct->{$field}{POINTER} = FALSE;
        $struct->{$field}{POINTER} = TRUE if $asterisk eq '*';
        $fieldsFound               = TRUE;
      }

    if ($upgrade)
      {
        my @_upgrade = ();
        push @_upgrade, @$upgrade;

        my @sorted_upgrade = sort {
            return -1
              if not defined $a->{NAME}
              or not defined $b->{NAME};

            my $aa = 3;
            $aa = $1 if $a->{NAME} =~ /\br(\d+)(?:-IEs)?$/;

            my $bb = 3;
            $bb = $1 if $b->{NAME} =~ /\br(\d+)(?:-IEs)?$/;

            $aa <=> $bb
        } @_upgrade;

        foreach my $legacy (@sorted_upgrade)
          {
            next if defined $legacy->{REF}{SWALLOWED};

            if ( not defined $legacy->{REF}{LABEL} )
              {
                $legacy->{REF} = SkipStruct( $legacy->{REF} );

                next if defined $legacy->{REF}{SWALLOWED};
                next if not defined $legacy->{REF}{LABEL};
              }

            my $level = '';
            $level = $1 if $legacy->{REF}{LABEL} =~ /^Xr(\d)/;
            my $offset = ' ' x ( 55 - length("    $legacy->{REF}{LABEL}") );

            $Code .= sprintf <<UPGRADE_FIELD, $level;
    $legacy->{REF}{LABEL}$offset*legacyR%s_p;
UPGRADE_FIELD
            $fieldsFound = TRUE;
          }
      }

    if (    $fieldsFound == FALSE
        and scalar @{ $struct->{_ORDER_} } > 1
        and not grep !/dummy/, @{ $struct->{_ORDER_} } )
      {
        $Code .=
            '    Int8                                               _dummy_;'
          . "\n";
        $fieldsFound = TRUE;
      }

    $Code .= sprintf <<SEQUENCE_FOOTER, $structPrefix, $struct_name;
}
%s%s;


SEQUENCE_FOOTER

    if ( $Print and $fieldsFound == TRUE )
      {
        Composer::Commons::WriteHeader( $File, $map, $structPrefix,
            $struct_name );
        print $File $Code;
      }
    return "$structPrefix$struct_name";

  }

sub _composeEncode
  {
    my $File       = shift;
    my $sequence   = shift;
    my $decodeOnly = shift;
    my $name       = shift;
    my $typePrefix = shift;

    return
      if defined $sequence->{SEQUENCE}
      and defined $sequence->{SEQUENCE}{KIND}
      and $sequence->{SEQUENCE}{KIND} eq 'EMPTY';

    return if not defined $sequence->{SEQUENCE}{_ORDER_};

    return
      if defined $sequence->{NOTSUPPORTED}
      or defined $sequence->{SEQUENCE}{NOTSUPPORTED};

    return
      if defined $sequence->{IGNORED}
      or defined $sequence->{SEQUENCE}{IGNORED};

    return if defined $sequence->{SWALLOWED};

    my $funcName    = 'PerEnc_';
    my $typeLabel   = '';
    my $valueLabel  = '';
    my $fieldPrefix = '';

    if ( defined $sequence->{SEQUENCE}{EXTENDS} )
      {
        my $map = GetGivenName($name);
        $typeLabel = $map->{FACTUAL};
        $funcName  = 'PerEnc_' . $typePrefix . $map->{FACTUAL};

        $map        = GetGivenName( $sequence->{SEQUENCE}{EXTENDS}{NAME} );
        $valueLabel = $typePrefix . $map->{FACTUAL};

        my $X = '3';
        $X = $1 if $typeLabel =~ /_r(\d+)(?:-IEs)?$/;
        $fieldPrefix = 'legacyR' . $X . '_p->';
      }
    elsif ( defined $sequence->{LABEL} )
      {
        $funcName   = 'PerEnc_' . $sequence->{LABEL};
        $typeLabel  = $sequence->{LABEL};
        $valueLabel = $sequence->{LABEL};
      }
    elsif ( defined $sequence->{SEQUENCE}{LABEL} )
      {
        $funcName   = 'PerEnc_' . $sequence->{SEQUENCE}{LABEL};
        $typeLabel  = $sequence->{SEQUENCE}{LABEL};
        $valueLabel = $sequence->{SEQUENCE}{LABEL};
      }

    my $headerOffset = ' ' x ( 76 - length("/*  $funcName") );

    print $File <<ALL_ENCODE_FUNC if $decodeOnly == TRUE;
#if defined (ENABLE_ALL_ENCODE_FUNCTIONS)

ALL_ENCODE_FUNC

    print $File <<SEQUENCE_ENC_CODE_START;
/****************************************************************************/
/*  $funcName$headerOffset*/
/*                                                                          */
/****************************************************************************/

void $funcName (PerBuffer *perBuffer, $valueLabel *value)
{
SEQUENCE_ENC_CODE_START

    my $upgrade_root = undef;
    $upgrade_root = GetReference( $sequence->{UPGRADED}, \%ASN1 )
      if defined $sequence->{UPGRADED};

    # DEFALUTs
    my $first = TRUE;
    foreach my $field ( @{ $sequence->{SEQUENCE}{_ORDER_} } )
      {
        my $fieldName = $field;
        $fieldName =~ s/-/_/g;

        if ( defined $sequence->{SEQUENCE}{$field}{DEFALUT} )
          {
            if ($first)
              {
                print $File <<DEFAULT_COMMENTS;
    /* Check if encoded value is the default and if so indicate */
    /* that this value is not present and so it is not encoded. */
DEFAULT_COMMENTS
                $first = FALSE;
              }

            if (    defined $sequence->{SEQUENCE}{$field}{VALUE}
                and defined $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }
                and defined $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }
                {ENUMERATED} )
              {
                my $default =
                    $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }{LABEL} . '_'
                  . $sequence->{SEQUENCE}{$field}{DEFALUT};
                printf $File <<DEFAULT_CHECK, ($fieldName) x 3;
    if (value->%sPresent && value->%s == $default)
        value->%sPresent = FALSE;
DEFAULT_CHECK
              }
          }
        elsif ( defined $sequence->{SEQUENCE}{$field}{INTEGER}
            and defined $sequence->{SEQUENCE}{$field}{INTEGER}{DEFALUT} )
          {
            if ($first)
              {
                print $File <<DEFAULT_COMMENTS;
    /* Check if encoded value is the default and if so indicate */
    /* that this value is not present and so it is not encoded. */
DEFAULT_COMMENTS
                $first = FALSE;
              }

            my $default = $sequence->{SEQUENCE}{$field}{INTEGER}{DEFALUT};
            printf $File <<DEFAULT_CHECK, ($fieldName) x 3;
    if (value->%sPresent && value->%s == $default)
        value->%sPresent = FALSE;
DEFAULT_CHECK
          }
      }

    # OPTIONALs
    foreach my $field ( @{ $sequence->{SEQUENCE}{_ORDER_} } )
      {
        my $fieldName = $field;
        $fieldName =~ s/-/_/g;

        if (
            defined $sequence->{SEQUENCE}{$field}{OPTIONAL}
            or (    defined $sequence->{SEQUENCE}{$field}{SEQUENCE}
                and defined $sequence->{SEQUENCE}{$field}{SEQUENCE}{OPTIONAL} )
            or (    defined $sequence->{SEQUENCE}{$field}{CHOICE}
                and defined $sequence->{SEQUENCE}{$field}{CHOICE}{OPTIONAL} )
            or (    defined $sequence->{SEQUENCE}{$field}{INTEGER}
                and defined $sequence->{SEQUENCE}{$field}{INTEGER}{OPTIONAL} )
            or (    defined $sequence->{SEQUENCE}{$field}{BITSTRING}
                and defined $sequence->{SEQUENCE}{$field}{BITSTRING}{OPTIONAL} )
            or (    defined $sequence->{SEQUENCE}{$field}{ENUMERATED}
                and
                defined $sequence->{SEQUENCE}{$field}{ENUMERATED}{OPTIONAL} )
          )
          {
            if ( $fieldName =~ /dummy/ )
              {
                print $File <<SEQUENCE_OPT_FIELD;
    /* $fieldName not present */
    PerEncBooleanValue (perBuffer, FALSE);
SEQUENCE_OPT_FIELD
              }
            else
              {
                printf $File <<SEQUENCE_OPT_FIELD, $fieldName;
    PerEncBoolean (perBuffer, &value->$fieldPrefix%sPresent);
SEQUENCE_OPT_FIELD
              }
          }
      }

    # All Fields
    my $sawNotSupported = FALSE;

    foreach my $field ( @{ $sequence->{SEQUENCE}{_ORDER_} } )
      {
        my $useFieldPrefix = TRUE;

        my $fieldName = $field;
        $fieldName =~ s/-/_/g;

        if ( $fieldName =~ /dummy/ )
          {
            if (    defined $sequence->{SEQUENCE}{$field}{KIND}
                and $sequence->{SEQUENCE}{$field}{KIND}  eq 'FREE'
                and $sequence->{SEQUENCE}{$field}{VALUE} eq 'BOOLEAN' )
              {
                print $File <<SEQUENCE_DUMMY;
    /* dummy encoded as all 0's */
    PerEncBooleanValue (perBuffer, FALSE);
SEQUENCE_DUMMY
              }
            else
              {
                print $File <<SEQUENCE_DUMMY;
    /* $fieldName not encoded */
SEQUENCE_DUMMY
              }
            next;
          }

        my $pointer = FALSE;
        $pointer = $sequence->{SEQUENCE}{$field}{POINTER}
          if defined $sequence->{SEQUENCE}{$field}{POINTER};
        my $value = '&';
        $value = '' if $pointer == TRUE;

        if (    defined $sequence->{SEQUENCE}{$field}{KIND}
            and $sequence->{SEQUENCE}{$field}{KIND} eq 'FREE'
            and $sequence->{SEQUENCE}{$field}{VALUE} ne 'NULL'
            and $sequence->{SEQUENCE}{$field}{VALUE} ne 'BOOLEAN' )
          {
            my $notSupported = FALSE;
            $notSupported = TRUE
              if defined $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }
              {NOTSUPPORTED};
            $sawNotSupported = $notSupported;

            if ( $notSupported == FALSE
                and
                defined $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }{INTEGER} )
              {
                _pseudoIntegerField(
                    $File, $fieldName, $value,
                    $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} },
                    $sequence->{SEQUENCE}{$field}
                );
              }
            elsif (
                $notSupported == FALSE
                and (
                    defined $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }
                    {BITSTRING}
                    and
                    ref $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }{BITSTRING}
                    eq 'ARRAY' )
              )
              {
                _pseudoBitstringField(
                    $File, $fieldName, $value,
                    $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} },
                    $sequence->{SEQUENCE}{$field}
                );
              }
            else
              {
                my $typeName = '';

                if ( $notSupported == FALSE )
                  {
                    if (
                        (
                            not defined $sequence->{UPGRADED}
                            or (    defined $sequence->{UPGRADED}
                                and defined $sequence->{SEQUENCE}{EXTENDS}{REF}
                                {$field} )
                        )
                        and
                        defined $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }
                        {LABEL}
                      )
                      {
                        $typeName =
                          $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }{LABEL};
                      }
                    elsif (
                        (
                            not defined $sequence->{UPGRADED}
                            or (    defined $sequence->{UPGRADED}
                                and defined $sequence->{SEQUENCE}{EXTENDS}{REF}
                                {$field} )
                        )
                        and (
                            defined
                            $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }
                            {SWALLOWED}
                            and defined
                            $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }
                            {UPGRADED}
                            and defined $ASN1{
                                $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }
                                  {UPGRADED}
                            }
                            and defined $ASN1{
                                $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }
                                  {UPGRADED}
                            }{LABEL}
                        )
                      )
                      {
                        $typeName =
                          $ASN1{ $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }
                              {UPGRADED} }{LABEL};
                      }
                    elsif (
                        defined $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }
                        {USED}
                        and
                        $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }{USED} )
                      {
                        $typeName =
                          $ASN1{ $sequence->{SEQUENCE}{$field}{VALUE} }{USED};
                      }
                    elsif ( defined $sequence->{UPGRADED}
                        and not
                        defined $sequence->{SEQUENCE}{EXTENDS}{REF}{$field} )
                      {
                        $fieldName = _getSimilarField( $field, $upgrade_root );
                        $fieldName =~ s/-/_/g;
                        my $_map =
                          GetGivenName( $sequence->{SEQUENCE}{$field}{VALUE} );
                        $typeName       = $typePrefix . $_map->{FACTUAL};
                        $useFieldPrefix = FALSE;
                      }
                  }
                if (   defined $sequence->{SEQUENCE}{$field}{OPTIONAL}
                    or defined $sequence->{SEQUENCE}{$field}{DEFAULT} )
                  {
                    printf $File
                      <<SEQUENCE_OPT_FIELD, $useFieldPrefix == TRUE ? $fieldPrefix : '', $fieldName, $value, $useFieldPrefix == TRUE ? $fieldPrefix : '' if $notSupported == FALSE;
    if (value->%s%sPresent)
    {
        PerEnc_$typeName (perBuffer, %svalue->%s$fieldName);
    }
SEQUENCE_OPT_FIELD
                    printf $File
                      <<TYPE_NOT_SUPPORTED, $useFieldPrefix == TRUE ? $fieldPrefix : '', $fieldName if $notSupported == TRUE;
    if (value->%s%sPresent)
    {
        DevFail ("Type Not Supported");
    }
TYPE_NOT_SUPPORTED
                  }
                else
                  {
                    printf $File
                      <<SEQUENCE_FIELD, $value, $useFieldPrefix == TRUE ? $fieldPrefix : '' if $notSupported == FALSE;
    PerEnc_$typeName (perBuffer, %svalue->%s$fieldName);
SEQUENCE_FIELD
                    print $File <<TYPE_NOT_SUPPORTED if $notSupported == TRUE;
    DevFail ("Type Not Supported");
TYPE_NOT_SUPPORTED
                  }
              }
          }
        elsif ( defined $sequence->{SEQUENCE}{$field}{KIND}
            and $sequence->{SEQUENCE}{$field}{KIND}  eq 'FREE'
            and $sequence->{SEQUENCE}{$field}{VALUE} eq 'BOOLEAN' )
          {
            if ( defined $sequence->{SEQUENCE}{$field}{OPTIONAL} )
              {
                printf $File <<SEQUENCE_OPT_FIELD, $fieldName, $value;
    if (value->$fieldPrefix%sPresent)
    {
        PerEncBoolean (perBuffer, %svalue->$fieldPrefix$fieldName);
    }
SEQUENCE_OPT_FIELD
              }
            else
              {
                printf $File <<SEQUENCE_FIELD, $value;
    PerEncBoolean (perBuffer, %svalue->$fieldPrefix$fieldName);
SEQUENCE_FIELD
              }
          }
        elsif ( defined $sequence->{SEQUENCE}{$field}{KIND}
            and $sequence->{SEQUENCE}{$field}{KIND}  eq 'FREE'
            and $sequence->{SEQUENCE}{$field}{VALUE} eq 'NULL' )
          {
            next;
          }
        elsif (defined $sequence->{SEQUENCE}{$field}{SEQUENCE}
            or defined $sequence->{SEQUENCE}{$field}{CHOICE}
            or defined $sequence->{SEQUENCE}{$field}{SEQUENCEOF} )
          {
            my $what = 'SEQUENCE';
            $what = 'CHOICE' if defined $sequence->{SEQUENCE}{$field}{CHOICE};
            $what = 'SEQUENCEOF'
              if defined $sequence->{SEQUENCE}{$field}{SEQUENCEOF};

            my $typeName = '';
            $typeName = $sequence->{SEQUENCE}{$field}{$what}{LABEL}
              if defined $sequence->{SEQUENCE}{$field}{$what}{LABEL};
            $typeName = $sequence->{SEQUENCE}{$field}{LABEL}
              if defined $sequence->{SEQUENCE}{$field}{LABEL};

            if (   defined $sequence->{SEQUENCE}{$field}{OPTIONAL}
                or defined $sequence->{SEQUENCE}{$field}{$what}{OPTIONAL} )
              {
                printf $File <<SEQUENCE_OPT_FIELD, $fieldName, $value;
    if (value->$fieldPrefix%sPresent)
    {
        PerEnc_$typeName (perBuffer, %svalue->$fieldPrefix$fieldName);
    }
SEQUENCE_OPT_FIELD
              }
            else
              {
                printf $File <<SEQUENCE_FIELD, $value;
    PerEnc_$typeName (perBuffer, %svalue->$fieldPrefix$fieldName);
SEQUENCE_FIELD
              }
          }
        elsif ( defined $sequence->{SEQUENCE}{$field}{LABEL} )
          {
            my $typeName = $sequence->{SEQUENCE}{$field}{LABEL};

            if (
                defined $sequence->{SEQUENCE}{$field}{OPTIONAL}
                or (    defined $sequence->{SEQUENCE}{$field}{ENUMERATED}
                    and defined
                    defined $sequence->{SEQUENCE}{$field}{ENUMERATED}
                    {OPTIONAL} )
              )
              {
                printf $File <<SEQUENCE_OPT_FIELD, $fieldName, $value;
    if (value->$fieldPrefix%sPresent)
    {
        PerEnc_$typeName (perBuffer, %svalue->$fieldPrefix$fieldName);
    }
SEQUENCE_OPT_FIELD
              }
            else
              {
                printf $File <<SEQUENCE_FIELD, $value;
    PerEnc_$typeName (perBuffer, %svalue->$fieldPrefix$fieldName);
SEQUENCE_FIELD
              }
          }
        elsif ( defined $sequence->{SEQUENCE}{$field}{INTEGER} )
          {
            my ( $lowerBound, $upperBound ) = ( 0, 0 );
            ( $lowerBound, $upperBound ) =
              @{ $sequence->{SEQUENCE}{$field}{INTEGER}{VALUE} }
              if $sequence->{SEQUENCE}{$field}{INTEGER}{KIND} eq 'INTERVAL';

            my $typeName = '';

            if ( $upperBound =~ /^-?\d+$/ )
              {
                $typeName = 'Int32'
                  if ( $lowerBound >= 0 and $upperBound < 4294967296 )
                  or (
                    $lowerBound < 0
                    and abs(
                        Composer::Commons::sign($upperBound) * abs($upperBound)
                          + (-1) * Composer::Commons::sign($lowerBound) *
                          abs($lowerBound)
                    ) < 4294967296
                  );
                $typeName = 'Int16'
                  if ( $lowerBound >= 0 and $upperBound < 65536 )
                  or (
                    $lowerBound < 0
                    and abs(
                        Composer::Commons::sign($upperBound) * abs($upperBound)
                          + (-1) * Composer::Commons::sign($lowerBound) *
                          abs($lowerBound)
                    ) < 65536
                  );
                $typeName = 'Int8'
                  if ( $lowerBound >= 0 and $upperBound < 256 )
                  or (
                    $lowerBound < 0
                    and abs(
                        Composer::Commons::sign($upperBound) * abs($upperBound)
                          + (-1) * Composer::Commons::sign($lowerBound) *
                          abs($lowerBound)
                    ) < 256
                  );
                $typeName = 'Signed' . $typeName if $lowerBound < 0;
              }
            else
              {
                $typeName = 'Int32'
                  if defined $ASN1{$upperBound}
                  and defined $ASN1{$upperBound}{INTEGER}
                  and $ASN1{$upperBound}{INTEGER} < 4294967296;
                $typeName = 'Int16'
                  if defined $ASN1{$upperBound}
                  and defined $ASN1{$upperBound}{INTEGER}
                  and $ASN1{$upperBound}{INTEGER} < 65536;
                $typeName = 'Int8'
                  if defined $ASN1{$upperBound}
                  and defined $ASN1{$upperBound}{INTEGER}
                  and $ASN1{$upperBound}{INTEGER} < 256;
              }

            if ( $typeName eq 'Int32' )
              {
                $lowerBound .= 'UL';
                $upperBound .= 'UL';
              }

            if (   defined $sequence->{SEQUENCE}{$field}{INTEGER}{OPTIONAL}
                or defined
                defined $sequence->{SEQUENCE}{$field}{INTEGER}{DEFAULT} )
              {
                printf $File <<SEQUENCE_OPT_FIELD, $fieldName, $value;
    if (value->$fieldPrefix%sPresent)
    {
        PerEnc$typeName (perBuffer, %svalue->$fieldPrefix$fieldName, $lowerBound, $upperBound);
    }
SEQUENCE_OPT_FIELD
              }
            else
              {
                printf $File <<SEQUENCE_FIELD, $value;
    PerEnc$typeName (perBuffer, %svalue->$fieldPrefix$fieldName, $lowerBound, $upperBound);
SEQUENCE_FIELD
              }
          }
        elsif ( defined $sequence->{SEQUENCE}{$field}{BITSTRING} )
          {
            my $typeName = 'Int16';
            my ( $lowerBound, $upperBound ) = ( 0, 0 );
            if ( defined $sequence->{SEQUENCE}{$field}{BITSTRING}{KIND}
                and $sequence->{SEQUENCE}{$field}{BITSTRING}{KIND} eq
                'SIZE_MAGNITUDE' )
              {
                $lowerBound = 0;
                $upperBound =
                  2**$sequence->{SEQUENCE}{$field}{BITSTRING}{VALUE}[0] - 1;
              }
            elsif ( defined $sequence->{SEQUENCE}{$field}{BITSTRING}{SIZE} )
              {
                $lowerBound = 0;
                $upperBound =
                  2**$sequence->{SEQUENCE}{$field}{BITSTRING}{SIZE} - 1;
              }

            $typeName = 'Int32' if $upperBound < 4294967296;
            $typeName = 'Int16' if $upperBound < 65536;
            $typeName = 'Int8'  if $upperBound < 256;

            if ( $typeName eq 'Int32' )
              {
                $lowerBound .= 'UL';
                $upperBound .= 'UL';
              }

            if ( defined $sequence->{SEQUENCE}{$field}{BITSTRING}{OPTIONAL} )
              {
                printf $File <<SEQUENCE_OPT_FIELD, $fieldName, $value;
    if (value->$fieldPrefix%sPresent)
    {
        PerEnc$typeName (perBuffer, %svalue->$fieldPrefix$fieldName, $lowerBound, $upperBound);
    }
SEQUENCE_OPT_FIELD
              }
            else
              {
                printf $File <<SEQUENCE_FIELD, $value;
    PerEnc$typeName (perBuffer, %svalue->$fieldPrefix$fieldName, $lowerBound, $upperBound);
SEQUENCE_FIELD
              }
          }
      }

    if ( $sawNotSupported == TRUE
        and scalar @{ $sequence->{SEQUENCE}{_ORDER_} } == 1 )
      {
        print $File <<PARAM_NOT_USED
    PARAMETER_NOT_USED (value);
PARAM_NOT_USED
      }

    print $File <<SEQUENCE_ENC_CODE_END if $decodeOnly == FALSE;
}


SEQUENCE_ENC_CODE_END

    print $File <<ALL_ENCODE_FUNC if $decodeOnly == TRUE;
}
#endif

ALL_ENCODE_FUNC

  }

sub _composeDecode
  {
    my $file        = shift;
    my $strDisposal = shift;
    my $encode_only = shift;

  }

sub _sequenceReady
  {
    my $Files    = shift;
    my $seq      = shift;
    my $name_ref = shift;
    my $Params   = shift;

    return $seq if not defined $seq->{CODE_DONE};

    my @Fields = ('');
    GetFields( $seq, \@Fields, 0, '', 'NOTSUPPORTED' );

    foreach my $field (@Fields)
      {
        next if not $field;

        my $ref = GetReference( $field, $seq );

        next if defined $ref->{CODE_DONE};

        my $kind = InternalStruct($ref);

        if ( $kind eq 'SEQUENCE' )
          {
            $$name_ref .= '-' . $field;
            return $ref;
          }

        Composer::CHOICE::_composeCODE( 'INTERNAL', $Files, $ref,
            $$name_ref . '-' . $field, $Params )
          if $kind eq 'CHOICE';
      }

    return undef;
  }

sub _pseudoIntegerField
  {
    my $File      = shift;
    my $fieldName = shift;
    my $value     = shift;
    my $type      = shift;
    my $source    = shift;

    my ( $lowerBound, $upperBound ) = @{ $type->{INTEGER} };

    $upperBound = Composer::Commons::GetInteger($upperBound);
    $lowerBound = Composer::Commons::GetInteger($lowerBound);

    my $typeName = '';

    $typeName = 'Int32'
      if ( $lowerBound >= 0 and $upperBound < 4294967296 )
      or (
        $lowerBound < 0
        and abs(
            Composer::Commons::sign($upperBound) * abs($upperBound) + (-1) *
              Composer::Commons::sign($lowerBound) * abs($lowerBound)
        ) < 4294967296
      );
    $typeName = 'Int16'
      if ( $lowerBound >= 0 and $upperBound < 65536 )
      or (
        $lowerBound < 0
        and abs(
            Composer::Commons::sign($upperBound) * abs($upperBound) + (-1) *
              Composer::Commons::sign($lowerBound) * abs($lowerBound)
        ) < 65536
      );
    $typeName = 'Int8'
      if ( $lowerBound >= 0 and $upperBound < 256 )
      or (
        $lowerBound < 0
        and abs(
            Composer::Commons::sign($upperBound) * abs($upperBound) + (-1) *
              Composer::Commons::sign($lowerBound) * abs($lowerBound)
        ) < 256
      );
    $typeName = 'Signed' . $typeName if $lowerBound < 0;

    if ( $typeName eq 'Int32' )
      {
        $lowerBound .= 'UL';
        $upperBound .= 'UL';
      }

    if ( defined $source->{OPTIONAL} )
      {
        printf $File <<SEQUENCE_OPT_FIELD, $fieldName, $value;
    if (value->%sPresent)
    {
        PerEnc$typeName (perBuffer, %svalue->$fieldName, $lowerBound, $upperBound);
    }
SEQUENCE_OPT_FIELD
      }
    else
      {
        printf $File <<SEQUENCE_FIELD, $value;
    PerEnc$typeName (perBuffer, %svalue->$fieldName, $lowerBound, $upperBound);
SEQUENCE_FIELD
      }
  }

sub _pseudoBitstringField
  {
    my $File      = shift;
    my $fieldName = shift;
    my $value     = shift;
    my $type      = shift;
    my $source    = shift;

    my $typeName = 'Int16';
    my ( $lowerBound, $upperBound ) = ( 0, 0 );

    if (
        (
            not defined $type->{BITSTRING}[1]
            and Composer::Commons::GetInteger( $type->{BITSTRING}[0] ) <= 32
        )
        or ( defined $type->{BITSTRING}[1]
            and Composer::Commons::GetInteger( $type->{BITSTRING}[1] ) <= 32 )
      )
      {
        $lowerBound =
          defined $type->{BITSTRING}[1]
          ? Composer::Commons::GetInteger( $type->{BITSTRING}[0] )
          : 0;
        $upperBound = 2**(
              defined $type->{BITSTRING}[1]
            ? defined $type->{BITSTRING}[1]
            : Composer::Commons::GetInteger( $type->{BITSTRING}[0] )
        ) - 1;

        $typeName = 'Int32' if $upperBound < 4294967296;
        $typeName = 'Int16' if $upperBound < 65536;
        $typeName = 'Int8'  if $upperBound < 256;

        if ( $typeName eq 'Int32' )
          {
            $lowerBound .= 'UL';
            $upperBound .= 'UL';
          }

        if ( defined $source->{OPTIONAL} )
          {
            printf $File <<SEQUENCE_OPT_FIELD, $fieldName, $value;
    if (value->%sPresent)
    {
        PerEnc$typeName (perBuffer, %svalue->$fieldName, $lowerBound, $upperBound);
    }
SEQUENCE_OPT_FIELD
          }
        else
          {
            printf $File <<SEQUENCE_FIELD, $value;
    PerEnc$typeName (perBuffer, %svalue->$fieldName, $lowerBound, $upperBound);
SEQUENCE_FIELD
          }
      }
    else
      {
        $typeName = $type->{USED};
        if ( defined $source->{OPTIONAL} )
          {
            printf $File <<SEQUENCE_OPT_FIELD, $fieldName, $value;
    if (value->%sPresent)
    {
        PerEnc_$typeName (perBuffer, %svalue->$fieldName);
    }
SEQUENCE_OPT_FIELD
          }
        else
          {
            printf $File <<SEQUENCE_FIELD, $value;
    PerEnc_$typeName (perBuffer, %svalue->$fieldName);
SEQUENCE_FIELD
          }
      }
  }

sub _getSimilarField
  {
    my $field  = shift;
    my $struct = shift;

    my $fieldRE = $field;
    $fieldRE =~ s/\br\d+\b/r\\d+/g;

    $struct = SkipStruct($struct);

    return undef if not defined $struct->{_ORDER_};

    foreach my $cand ( @{ $struct->{_ORDER_} } )
      {
        return $cand if $cand eq $field or $cand =~ /$fieldRE/;
      }

    return undef;
  }

#-------------------------------------------------------------
1;
