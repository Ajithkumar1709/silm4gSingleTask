#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#----------------------------------------------------------------------
# ASN.1 Compiler Service Library
#
# Proceed ENUMERATED types
#
#----------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#-----------------------------------------------------------------------
# Version       Date            Author     Description
# 0.0.1         18-Aug-2009     KS         1. Initial Version
#-----------------------------------------------------------------------
package Composer::CHOICE;

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
    my $choice    = shift;
    my $root_name = shift;
    my $Params    = shift;

    my $ref = undef;
    $ref = $ASN1{ $choice->[0] } if $kind eq 'COMMON';
    $ref = $choice if $kind eq 'INTERNAL';

    my $name = $root_name;
    while ( my $int_ref = _choiceReady( $Files, $ref, \$name, $Params ) )
      {
        _composeEncode( $Files->[ENCC][HANDLE], $int_ref, $name );
        _composeDecode( $Files->[DECC][HANDLE], $int_ref );
        $int_ref->{CODE_DONE} = 1;
        $name = $root_name;
      }
  }

sub _composeMainHeader
  {
    my ( $File, $name, $map, $struct, $upgrade, $masterStatic, $structPrefix ) =
      @_;

    my $struct_name = Composer::Commons::GetName($map);

    $masterStatic = 1 if defined $struct->{STATIC};

    return "$structPrefix$struct_name" if defined $struct->{EXTENDS};

    my $Code  = '';
    my $Print = TRUE;

    my $union = 'union';
    $union = 'struct'
      if ref $map eq 'HASH'
      and defined $map->{DATA}[3]
      and $map->{DATA}[3] eq 'STRUCTURE';

    $Code .= sprintf <<CHOICE_ENUM_HEADER, $structPrefix, $struct_name;
/* Union TAGS */

typedef enum T_%s%sTag
{
CHOICE_ENUM_HEADER

    my $enumCounter = 0;
    my $firstTag    = 1;
    foreach my $field ( @{ $struct->{_ORDER_} } )
      {
        next
          if defined $struct->{EXTENDS}
          and not defined $struct->{EXTENDS}{REF}{$field};

        $Code .= ",\n" if not $firstTag;
        $firstTag = 0 if $firstTag;

        my $field_name = $field;
        $field_name =~ s/-/_/g;

        my $label = "T_" . "$structPrefix$struct_name" . "_" . $field_name;
        $label = $MAP{ENUM}{"T_$structPrefix$struct_name"}{$field_name}[0]
          if defined $MAP{ENUM}{"T_$structPrefix$struct_name"}
          and defined $MAP{ENUM}{"T_$structPrefix$struct_name"}{$field_name};
        if (    defined defined $MAP{ENUM}{"T_$structPrefix$struct_name"}
            and defined $MAP{ENUM}{"T_$structPrefix$struct_name"}
            { 'asn1' . $field_name } )
          {
            $label =
              $MAP{ENUM}{"T_$structPrefix$struct_name"}{ 'asn1' . $field_name }
              [0];
            $field_name = 'asn1' . $field_name;
          }

        $Code .= "    $label = $enumCounter";
        $enumCounter++;
      }

    if ( $upgrade and ref $upgrade eq 'ARRAY' )
      {
        foreach my $legacy (@$upgrade)
          {
            next if defined $legacy->{REF}{SWALLOWED};

            $Code .= ",\n";

            my $field_name = '';
            $field_name = $legacy->{NAME}  if defined $legacy->{NAME};
            $field_name = $legacy->{FIELD} if defined $legacy->{FIELD};

            my $label = '';
            if (    defined $legacy->{REF}{CHOICE}
                and defined $legacy->{REF}{CHOICE}{EXTENDS}
                and defined $legacy->{REF}{CHOICE}{EXTENDS}{REF}
                and %{ $legacy->{REF}{CHOICE}{EXTENDS}{REF} } )
              {
                foreach
                  my $field ( keys %{ $legacy->{REF}{CHOICE}{EXTENDS}{REF} } )
                  {
                    $label =
                      "T_" . "$structPrefix$struct_name" . "_legacy_" . $field;
                    $label =~ s/-/_/g;
                    $Code .= "    $label = $enumCounter";
                    $enumCounter++;
                  }
              }
            elsif ( defined $legacy->{REF}{EXTENDS}
                and defined $legacy->{REF}{EXTENDS}{REF}
                and %{ $legacy->{REF}{EXTENDS}{REF} } )
              {
                foreach my $field ( keys %{ $legacy->{REF}{EXTENDS}{REF} } )
                  {
                    $label =
                      "T_" . "$structPrefix$struct_name" . "_legacy_" . $field;
                    $label =~ s/-/_/g;
                    $Code .= "    $label = $enumCounter";
                    $enumCounter++;
                  }
              }
            else
              {
                $label =
                  "T_" . "$structPrefix$struct_name" . "_legacy_" . $field_name;
                $Code .= "    $label = $enumCounter";
                $enumCounter++;
              }
          }
      }
    $Code .= "\n";

    $Code .= sprintf <<ENUM_END_STRUCT_START, $structPrefix, $struct_name;
}
T_$structPrefix$struct_name;

typedef struct %s%sTag
{
    T_$structPrefix$struct_name tag;
    $union
    {
ENUM_END_STRUCT_START

    $enumCounter = 0;
    my $dummyCounter = 1;
    foreach my $field ( @{ $struct->{_ORDER_} } )
      {
        next
          if defined $struct->{EXTENDS}
          and not defined $struct->{EXTENDS}{REF}{$field};

        my $field_name = $field;
        $field_name =~ s/-/_/g;

        $field_name = 'asn1' . $field_name
          if defined $MAP{ENUM}{"T_$structPrefix$struct_name"}
          and defined $MAP{ENUM}{"T_$structPrefix$struct_name"}
          { 'asn1' . $field_name };

        my $asterisk = '*';
        $asterisk = '' if $masterStatic;
        $asterisk = ''
          if Composer::Commons::LikeIntegerLoosely( $struct->{$field} );
        $asterisk = ''
          if ref $struct->{$field} eq 'HASH'
          and (
            (
                    defined $struct->{$field}{KIND}
                and $struct->{$field}{KIND} eq 'FREE'
                and (  defined $ASN1{ $struct->{$field}{VALUE} }{ENUMERATED}
                    or defined $ASN1{ $struct->{$field}{VALUE} }{INTEGER}
                    or defined $ASN1{ $struct->{$field}{VALUE} }{STATIC} )
            )
            or defined $struct->{$field}{BITSTRING}
            or defined $struct->{$field}{ENUMERATED}
            or defined $struct->{$field}{INTEGER}

            or (    defined $struct->{$field}{SEQUENCE}
                and defined $struct->{$field}{SEQUENCE}{STATIC} )
            or (    defined $struct->{$field}{SEQUENCEOF}
                and defined $struct->{$field}{SEQUENCEOF}{STATIC} )
            or (    defined $struct->{$field}{CHOICE}
                and defined $struct->{$field}{CHOICE}{STATIC} )
          );

        my $needDefine   = FALSE;
        my $defineSource = [];

        my $label = Composer::Commons::UpdateLabel(
            Composer::Commons::GetField(
                $struct->{$field}, 'LABEL',
                undef,             undef,
                'CHOICE',          $structPrefix
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
          if ref $struct->{$field} eq 'HASH'
          and defined $struct->{$field}{SEQUENCE}
          and defined $struct->{$field}{SEQUENCE}{KIND}
          and $struct->{$field}{SEQUENCE}{KIND} eq 'EMPTY';

        $Print = FALSE
          if $field_name =~ /dummy/
          and defined $struct->{EXTENDS}
          and scalar keys %{ $struct->{EXTENDS}{REF} } == 1;

        my $field_offset =
          ' ' x ( 59 - ( 8 + length($label) + length($asterisk) ) );
        $field_offset = ' ' if not $field_offset;

        $Code .= <<ENUM_COUNTER;
        /* $enumCounter */
ENUM_COUNTER

        $Code .=
          Composer::Commons::WriteInternalDefines( $field_name,
            $struct->{$field}, $defineSource )
          if $needDefine == TRUE;

        $Code .= <<STRUCT_BODY;
        $label$field_offset$asterisk$field_name;
STRUCT_BODY

        $enumCounter++;
        $dummyCounter++;
      }

    if ( $upgrade and ref $upgrade eq 'ARRAY' )
      {
        foreach my $legacy (@$upgrade)
          {
            next if defined $legacy->{REF}{SWALLOWED};

            my $field_name = '';
            $field_name = $legacy->{NAME}  if defined $legacy->{NAME};
            $field_name = $legacy->{FIELD} if defined $legacy->{FIELD};
            $field_name =~ s/-/_/g;
            $field_name = 'legacy_' . $field_name;

            if (    defined $legacy->{REF}{CHOICE}
                and defined $legacy->{REF}{CHOICE}{EXTENDS}
                and defined $legacy->{REF}{CHOICE}{EXTENDS}{REF}
                and %{ $legacy->{REF}{CHOICE}{EXTENDS}{REF} } )
              {
                foreach
                  my $field ( keys %{ $legacy->{REF}{CHOICE}{EXTENDS}{REF} } )
                  {

                    $field_name = 'legacy_' . $field;
                    $field_name =~ s/-/_/g;

                    my $fieldRef = undef;
                    $fieldRef = $legacy->{REF}{CHOICE}{$field};

                    my $asterisk = '*';
                    $asterisk = '' if $masterStatic;
                    $asterisk = ''
                      if Composer::Commons::LikeIntegerLoosely($fieldRef);
                    $asterisk = ''
                      if ref $fieldRef eq 'HASH'
                      and (
                        (
                                defined $fieldRef->{KIND}
                            and $fieldRef->{KIND} eq 'FREE'
                            and
                            ( defined $ASN1{ $fieldRef->{VALUE} }{ENUMERATED}
                                or defined $ASN1{ $fieldRef->{VALUE} }{INTEGER}
                                or defined $ASN1{ $fieldRef->{VALUE} }{STATIC} )
                        )
                        or defined $fieldRef->{BITSTRING}
                        or defined $fieldRef->{ENUMERATED}
                        or defined $fieldRef->{INTEGER}

                        or (    defined $fieldRef->{SEQUENCE}
                            and defined $fieldRef->{SEQUENCE}{STATIC} )
                        or (    defined $fieldRef->{SEQUENCEOF}
                            and defined $fieldRef->{SEQUENCEOF}{STATIC} )
                        or (    defined $fieldRef->{CHOICE}
                            and defined $fieldRef->{CHOICE}{STATIC} )
                      );

                    my $needDefine   = FALSE;
                    my $defineSource = [];

                    my $label = Composer::Commons::UpdateLabel(
                        Composer::Commons::GetField(
                            $fieldRef, 'LABEL',
                            undef,     undef,
                            'CHOICE',  $structPrefix
                        ),
                        $fieldRef,
                        \$field_name,
                        \$asterisk,
                        $dummyCounter,
                        \$needDefine,
                        \$defineSource
                    );

                    $asterisk = '' if $masterStatic;

                    $asterisk = '*'
                      if ref $fieldRef eq 'HASH'
                      and defined $fieldRef->{SEQUENCE}
                      and defined $fieldRef->{SEQUENCE}{KIND}
                      and $fieldRef->{SEQUENCE}{KIND} eq 'EMPTY';

                    my $field_offset =
                      ' ' x ( 59 - ( 8 + length($label) + length($asterisk) ) );
                    $field_offset = ' ' if not $field_offset;

                    $Code .= <<ENUM_COUNTER;
        /* $enumCounter */
ENUM_COUNTER

                    $Code .=
                      Composer::Commons::WriteInternalDefines( $field_name,
                        $fieldRef, $defineSource )
                      if $needDefine == TRUE;

                    $Code .= <<STRUCT_BODY;
        $label$field_offset$asterisk$field_name;
STRUCT_BODY

                    $enumCounter++;
                    $dummyCounter++;
                  }
              }
            elsif ( defined $legacy->{REF}{EXTENDS}
                and defined $legacy->{REF}{EXTENDS}{REF}
                and %{ $legacy->{REF}{EXTENDS}{REF} } )
              {
                foreach my $field ( keys %{ $legacy->{REF}{EXTENDS}{REF} } )
                  {
                    $field_name = 'legacy_' . $field;
                    $field_name =~ s/-/_/g;

                    my $fieldRef = undef;
                    $fieldRef = $legacy->{REF}{$field};

                    my $asterisk = '*';
                    $asterisk = '' if $masterStatic;
                    $asterisk = ''
                      if Composer::Commons::LikeIntegerLoosely($fieldRef);
                    $asterisk = ''
                      if ref $fieldRef eq 'HASH'
                      and (
                        (
                                defined $fieldRef->{KIND}
                            and $fieldRef->{KIND} eq 'FREE'
                            and
                            ( defined $ASN1{ $fieldRef->{VALUE} }{ENUMERATED}
                                or defined $ASN1{ $fieldRef->{VALUE} }{INTEGER}
                                or defined $ASN1{ $fieldRef->{VALUE} }{STATIC} )
                        )
                        or defined $fieldRef->{BITSTRING}
                        or defined $fieldRef->{ENUMERATED}
                        or defined $fieldRef->{INTEGER}

                        or (    defined $fieldRef->{SEQUENCE}
                            and defined $fieldRef->{SEQUENCE}{STATIC} )
                        or (    defined $fieldRef->{SEQUENCEOF}
                            and defined $fieldRef->{SEQUENCEOF}{STATIC} )
                        or (    defined $fieldRef->{CHOICE}
                            and defined $fieldRef->{CHOICE}{STATIC} )
                      );

                    my $needDefine   = FALSE;
                    my $defineSource = [];

                    my $label = Composer::Commons::UpdateLabel(
                        Composer::Commons::GetField(
                            $fieldRef, 'LABEL',
                            undef,     undef,
                            'CHOICE',  $structPrefix
                        ),
                        $fieldRef,
                        \$field_name,
                        \$asterisk,
                        $dummyCounter,
                        \$needDefine,
                        \$defineSource
                    );

                    $asterisk = '' if $masterStatic;

                    $asterisk = '*'
                      if ref $fieldRef eq 'HASH'
                      and defined $fieldRef->{SEQUENCE}
                      and defined $fieldRef->{SEQUENCE}{KIND}
                      and $fieldRef->{SEQUENCE}{KIND} eq 'EMPTY';

                    my $field_offset =
                      ' ' x ( 59 - ( 8 + length($label) + length($asterisk) ) );
                    $field_offset = ' ' if not $field_offset;

                    $Code .= <<ENUM_COUNTER;
        /* $enumCounter */
ENUM_COUNTER

                    $Code .=
                      Composer::Commons::WriteInternalDefines( $field_name,
                        $fieldRef, $defineSource )
                      if $needDefine == TRUE;

                    $Code .= <<STRUCT_BODY;
        $label$field_offset$asterisk$field_name;
STRUCT_BODY

                    $enumCounter++;
                    $dummyCounter++;
                  }
              }
            else
              {
                my $fieldRef = undef;
                $fieldRef = $legacy->{REF}{ $legacy->{NAME} }
                  if defined $legacy->{NAME}
                  and defined $legacy->{REF}{ $legacy->{NAME} };
                $fieldRef = $legacy->{REF}
                  if ( defined $legacy->{NAME}
                    and not defined $legacy->{REF}{ $legacy->{NAME} } )
                  or defined $legacy->{FIELD};

                my $asterisk = '*';
                $asterisk = '' if $masterStatic;
                $asterisk = ''
                  if Composer::Commons::LikeIntegerLoosely($fieldRef);
                $asterisk = ''
                  if ref $fieldRef eq 'HASH'
                  and (
                    (
                            defined $fieldRef->{KIND}
                        and $fieldRef->{KIND} eq 'FREE'
                        and (  defined $ASN1{ $fieldRef->{VALUE} }{ENUMERATED}
                            or defined $ASN1{ $fieldRef->{VALUE} }{INTEGER}
                            or defined $ASN1{ $fieldRef->{VALUE} }{STATIC} )
                    )
                    or defined $fieldRef->{BITSTRING}
                    or defined $fieldRef->{ENUMERATED}
                    or defined $fieldRef->{INTEGER}

                    or (    defined $fieldRef->{SEQUENCE}
                        and defined $fieldRef->{SEQUENCE}{STATIC} )
                    or (    defined $fieldRef->{SEQUENCEOF}
                        and defined $fieldRef->{SEQUENCEOF}{STATIC} )
                    or (    defined $fieldRef->{CHOICE}
                        and defined $fieldRef->{CHOICE}{STATIC} )
                  );

                my $needDefine   = FALSE;
                my $defineSource = [];

                my $label = Composer::Commons::UpdateLabel(
                    Composer::Commons::GetField(
                        $fieldRef, 'LABEL', undef, undef,
                        'CHOICE',  $structPrefix
                    ),
                    $fieldRef,
                    \$field_name,
                    \$asterisk,
                    $dummyCounter,
                    \$needDefine,
                    \$defineSource
                );

                $asterisk = '' if $masterStatic;

                $asterisk = '*'
                  if ref $fieldRef eq 'HASH'
                  and defined $fieldRef->{SEQUENCE}
                  and defined $fieldRef->{SEQUENCE}{KIND}
                  and $fieldRef->{SEQUENCE}{KIND} eq 'EMPTY';

                my $field_offset =
                  ' ' x ( 59 - ( 8 + length($label) + length($asterisk) ) );
                $field_offset = ' ' if not $field_offset;

                $Code .= <<ENUM_COUNTER;
        /* $enumCounter */
ENUM_COUNTER

                $Code .=
                  Composer::Commons::WriteInternalDefines( $field_name,
                    $fieldRef, $defineSource )
                  if $needDefine == TRUE;

                $Code .= <<STRUCT_BODY;
        $label$field_offset$asterisk$field_name;
STRUCT_BODY

                $enumCounter++;
                $dummyCounter++;
              }
          }
      }

    $Code .= <<STRUCT_FOOTER;
    }
    choice;
}
$structPrefix$struct_name;


STRUCT_FOOTER

    if ( $Print == TRUE )
      {
        Composer::Commons::WriteHeader( $File, $map, $structPrefix,
            $struct_name );
        print $File $Code;
      }

    return "$structPrefix$struct_name";
  }

sub _composeEncode
  {
    my $File   = shift;
    my $choice = shift;

    return
      if defined $choice->{SWALLOWED}
      or defined $choice->{NOTSUPPORTED}
      or defined $choice->{IGNORED}
      or defined $choice->{CHOICE}{IGNORED};

    my $typeLabel = '';
    my $funcName  = 'PerEnc_';
    if ( defined $choice->{LABEL} )
      {
        $funcName  = 'PerEnc_' . $choice->{LABEL};
        $typeLabel = $choice->{LABEL};
      }
    elsif ( defined $choice->{CHOICE}{LABEL} )
      {
        $funcName  = 'PerEnc_' . $choice->{CHOICE}{LABEL};
        $typeLabel = $choice->{CHOICE}{LABEL};
      }

    my $headerOffset = ' ' x ( 76 - length("/*  $funcName") );

    my $totalFields = scalar @{ $choice->{CHOICE}{_ORDER_} } - 1;

    print $File <<CHOICE_ENC_CODE_START;
/****************************************************************************/
/*  $funcName$headerOffset*/
/*                                                                          */
/****************************************************************************/

void $funcName (PerBuffer *perBuffer, $typeLabel *value)
{
    /* Encode the CHOICE tag */
    PerEncEnum (perBuffer, (Int8 *) &value->tag, $totalFields);
    switch (value->tag)
    {
CHOICE_ENC_CODE_START

    foreach my $field ( @{ $choice->{CHOICE}{_ORDER_} } )
      {
        next
          if defined $choice->{CHOICE}{$field}{NOTSUPPORTED}
          or (  defined $choice->{CHOICE}{$field}{SEQUENCE}
            and defined $choice->{CHOICE}{$field}{SEQUENCE}{NOTSUPPORTED} )
          or (  defined $choice->{CHOICE}{$field}{CHOICE}
            and defined $choice->{CHOICE}{$field}{CHOICE}{NOTSUPPORTED} );

        my $fieldName = $field;
        $fieldName =~ s/-/_/g;

        my $label = "T_" . $typeLabel . "_" . $fieldName;
        $label = $MAP{ENUM}{"T_$typeLabel"}{$fieldName}[0]
          if defined $MAP{ENUM}{"T_$typeLabel"}
          and defined $MAP{ENUM}{"T_$typeLabel"}{$fieldName};
        if (    defined defined $MAP{ENUM}{"T_$typeLabel"}
            and defined $MAP{ENUM}{"T_$typeLabel"}{ 'asn1' . $fieldName } )
          {
            $label     = $MAP{ENUM}{"T_$typeLabel"}{ 'asn1' . $fieldName }[0];
            $fieldName = 'asn1' . $fieldName;
          }

        my $fieldType = '';
        if ( defined $choice->{CHOICE}{$field}{LABEL} )
          {
            $fieldType = $choice->{CHOICE}{$field}{LABEL};
          }
        elsif ( defined $choice->{CHOICE}{$field}{KIND}
            and $choice->{CHOICE}{$field}{KIND} eq 'FREE'
            and $choice->{CHOICE}{$field}{VALUE} ne 'NULL'
            and $choice->{CHOICE}{$field}{VALUE} ne 'BOOLEAN' )
          {
            next
              if
              defined $ASN1{ $choice->{CHOICE}{$field}{VALUE} }{NOTSUPPORTED};

            if ( defined $ASN1{ $choice->{CHOICE}{$field}{VALUE} }{LABEL} )
              {
                $fieldType = $ASN1{ $choice->{CHOICE}{$field}{VALUE} }{LABEL};
              }
            elsif ( defined $ASN1{ $choice->{CHOICE}{$field}{VALUE} }{SWALLOWED}
                and defined $ASN1{ $choice->{CHOICE}{$field}{VALUE} }{UPGRADED}
                and defined
                $ASN1{ $ASN1{ $choice->{CHOICE}{$field}{VALUE} }{UPGRADED} }
                and defined
                $ASN1{ $ASN1{ $choice->{CHOICE}{$field}{VALUE} }{UPGRADED} }
                {LABEL} )
              {
                $fieldType =
                  $ASN1{ $ASN1{ $choice->{CHOICE}{$field}{VALUE} }{UPGRADED} }
                  {LABEL};
              }
          }
        elsif ( defined $choice->{CHOICE}{$field}{KIND}
            and $choice->{CHOICE}{$field}{KIND}  eq 'FREE'
            and $choice->{CHOICE}{$field}{VALUE} eq 'NULL' )
          {
            $fieldType = 'NONE';
          }
        elsif (defined $choice->{CHOICE}{$field}{SEQUENCE}
            or defined $choice->{CHOICE}{$field}{CHOICE}
            or defined $choice->{CHOICE}{$field}{SEQUENCEOF} )
          {
            my $what = 'SEQUENCE';
            $what = 'CHOICE' if defined $choice->{CHOICE}{$field}{CHOICE};
            $what = 'SEQUENCEOF'
              if defined $choice->{CHOICE}{$field}{SEQUENCEOF};
            $fieldType = $choice->{CHOICE}{$field}{$what}{LABEL}
              if defined $choice->{CHOICE}{$field}{$what}{LABEL};
            $fieldType = $choice->{CHOICE}{$field}{LABEL}
              if defined $choice->{CHOICE}{$field}{LABEL};
          }
        elsif ( defined $choice->{CHOICE}{$field}{BITSTRING} )
          {
            my ( $lowerBound, $upperBound ) = ( 0, 0 );
            if ( defined $choice->{CHOICE}{$field}{BITSTRING}{KIND}
                and $choice->{CHOICE}{$field}{BITSTRING}{KIND} eq
                'SIZE_MAGNITUDE' )
              {
                $lowerBound = 0;
                $upperBound =
                  2**$choice->{CHOICE}{$field}{BITSTRING}{VALUE}[0] - 1;
              }
            elsif ( defined $choice->{CHOICE}{$field}{BITSTRING}{SIZE} )
              {
                $lowerBound = 0;
                $upperBound = 2**$choice->{CHOICE}{$field}{BITSTRING}{SIZE} - 1;
              }

            $fieldType = 'Int32' if $upperBound < 4294967296;
            $fieldType = 'Int16' if $upperBound < 65536;
            $fieldType = 'Int8'  if $upperBound < 256;
          }
        elsif ( defined $choice->{CHOICE}{$field}{INTEGER} )
          {
            my ( $lowerBound, $upperBound ) = ( 0, 0 );
            ( $lowerBound, $upperBound ) =
              @{ $choice->{CHOICE}{$field}{INTEGER}{VALUE} }
              if $choice->{CHOICE}{$field}{INTEGER}{KIND} eq 'INTERVAL';

            if ( $upperBound =~ /^-?\d+$/ )
              {
                $fieldType = 'Int32'
                  if ( $lowerBound >= 0 and $upperBound < 4294967296 )
                  or (
                    $lowerBound < 0
                    and abs(
                        Composer::Commons::sign($upperBound) * abs($upperBound)
                          + (-1) * Composer::Commons::sign($lowerBound) *
                          abs($lowerBound)
                    ) < 4294967296
                  );
                $fieldType = 'Int16'
                  if ( $lowerBound >= 0 and $upperBound < 65536 )
                  or (
                    $lowerBound < 0
                    and abs(
                        Composer::Commons::sign($upperBound) * abs($upperBound)
                          + (-1) * Composer::Commons::sign($lowerBound) *
                          abs($lowerBound)
                    ) < 65536
                  );
                $fieldType = 'Int8'
                  if ( $lowerBound >= 0 and $upperBound < 256 )
                  or (
                    $lowerBound < 0
                    and abs(
                        Composer::Commons::sign($upperBound) * abs($upperBound)
                          + (-1) * Composer::Commons::sign($lowerBound) *
                          abs($lowerBound)
                    ) < 256
                  );
                $fieldType = 'Signed' . $fieldType if $lowerBound < 0;
              }
            else
              {
                $fieldType = 'Int32'
                  if defined $ASN1{$upperBound}
                  and defined $ASN1{$upperBound}{INTEGER}
                  and $ASN1{$upperBound}{INTEGER} < 4294967296;
                $fieldType = 'Int16'
                  if defined $ASN1{$upperBound}
                  and defined $ASN1{$upperBound}{INTEGER}
                  and $ASN1{$upperBound}{INTEGER} < 65536;
                $fieldType = 'Int8'
                  if defined $ASN1{$upperBound}
                  and defined $ASN1{$upperBound}{INTEGER}
                  and $ASN1{$upperBound}{INTEGER} < 256;
              }
          }

        if ( $fieldType ne 'NONE' )
          {
            print $File <<CHOICE_FIELD
        case $label:
            PerEnc_$fieldType (perBuffer, value->choice.$fieldName);
            break;
CHOICE_FIELD
          }
        else
          {
            print $File <<CHOICE_FIELD
          case $label:
            break;
CHOICE_FIELD

          }
      }

    print $File <<CHOICE_ENC_CODE_END
        default:
            DevParam (value->tag, 0, 0);
            break;
    }
}


CHOICE_ENC_CODE_END
  }

sub _composeDecode
  {

  }

sub _choiceReady
  {
    my $Files    = shift;
    my $choice   = shift;
    my $name_ref = shift;
    my $Params   = shift;

    return $choice if not defined $choice->{CODE_DONE};

    my @Fields = ('');
    GetFields( $choice, \@Fields, 0, '', 'NOTSUPPORTED' );

    foreach my $field (@Fields)
      {
        next if not $field;

        my $ref = GetReference( $field, $choice );

        next if defined $ref->{CODE_DONE};

        my $kind = InternalStruct($ref);

        if ( $kind eq 'CHOICE' )
          {
            $$name_ref .= '-' . $field;
            return $ref;
          }

        Composer::SEQUENCE::_composeCODE( 'INTERNAL', $Files, $ref,
            $$name_ref . '-' . $field, $Params )
          if $kind eq 'SEQUENCE';
      }
    return undef;
  }

#-------------------------------------------------------------
1;
