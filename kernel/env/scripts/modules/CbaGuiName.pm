#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaGuiName.pm
# Description    : Perl module of Build Element Name gui widget for the CBA
#                  (Cellular Build Architecture)
#
# Notes          : -label       = the label for the widget
#                  -nameVar     = reference to the name variable location
#                  -baseVar     = reference to the base variable location
#                  -width       = width of the frame
#                  -height      = height of the frame
#                  -entryOffset = x offset location of the entry boxes
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

package CbaGuiName;

require Tk::Frame;
@ISA = qw(Tk::Frame);

Construct Tk::Widget 'CbaGuiName';

sub Populate
{
	require Tk::LabFrame;

	my ($cw, $args) = @_;

	# check for the options
	my $label     = delete $args->{"-label"};
	my $nameVar   = delete $args->{"-nameVar"};
	my $baseVar   = delete $args->{"-baseVar"};
	my $width     = delete $args->{"-width"};
	my $entryXoff = delete $args->{"-entryOffset"};
	my $height    = delete $args->{"-height"};

	# pass on the rest of the arguments
	$cw->SUPER::Populate($args);

	# set the external defaults
	$label = "Package" unless (defined $label);
	$width = 225 unless (defined $width);
	$entryXoff = 60 unless (defined $entryXoff);
	$height = 60 unless (defined $height);

	# default internal values
	my $lineYoff  = 25;

    my $nameXoff = $entryXoff - 40;
    my $nameYoff = 5;
	my $nameEntryXoff = $entryXoff;
	my $nameEntryYoff = $nameYoff;

    my $baseXoff = $nameXoff;
    my $baseYoff = $nameYoff + $lineYoff;
	my $baseEntryXoff = $entryXoff;
	my $baseEntryYoff = $baseYoff;

	# create the labelled frame
    my $frame = $cw->LabFrame(-label => $label,
				              -labelside=>"acrosstop", 
				              -width => $width,
				              -height => $height
				             );

	# create the labels and entry boxes
    my $nameLabel = $frame->Label(-text => "Name:");
    my $nameEntry = $frame->Entry(-textvariable => $nameVar);

    my $baseLabel = $frame->Label(-text => "VOB:");
    my $baseEntry = $frame->Entry(-textvariable => $baseVar);

	# display the widgets
	$nameLabel->place(-x => $nameXoff,      -y => $nameYoff);
	$nameEntry->place(-x => $nameEntryXoff, -y => $nameEntryYoff);

	$baseLabel->place(-x => $baseXoff,      -y => $baseYoff);
	$baseEntry->place(-x => $baseEntryXoff, -y => $baseEntryYoff);

	$frame->pack();

}

1;