#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaGuiCheckList.pm
# Description    : Perl module of the Check List gui widget for the CBA
#                  (Cellular Build Architecture)
#
# Notes          : -title       = name to give the widget
#                  -checkList   = reference to the check list array
#                  -width       = width of the frame
#                  -height      = height of the frame
#                  -checkOffset = x offset location of the check boxes
#                  -entryOffset = x offset location of the check boxes
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

package CbaGuiCheckList;

require Tk::Frame;
@ISA = qw(Tk::Frame);

Construct Tk::Widget 'CbaGuiCheckList';

sub Populate
{
	require Tk::LabFrame;

	my ($cw, $args) = @_;

	# check for the options
	my $title          = delete $args->{"-title"};
	my $checkList      = delete $args->{"-checkList"};
	my $width          = delete $args->{"-width"};
	my $fixedheight    = delete $args->{"-height"};
	my $checkOffset    = delete $args->{"-checkOffset"};
	my $entryOffset    = delete $args->{"-entryOffset"};

	# pass on the rest of the arguments
	$cw->SUPER::Populate($args);

	# set the external defaults
	$title = "<Title>" unless (defined $title);
	$width = 225 unless (defined $width);
	$checkOffset = 15 unless (defined $checkOffset);
	$entryOffset = 120 unless (defined $entryOffset);

	# placement values for the check boxes
	my $checkYoff   = 7;
	my $checkYspace = 20;

	# determine the height of the frame and the entry box
	$entryYoff     = 5;
	$envTextWidth  = 20;
	$envTextHeight = 2 + scalar(@$checkList);
	$height        = 32 + (20 * scalar(@$checkList));

	# override the height
	$height = $fixedheight if (defined $fixedheight);

	# define the widgets
	my $frame;
	my @checkBoxes;
	my $textBox;

	# create the labeled frame
    $frame = $cw->LabFrame(-label => $title,
			               -labelside=>"acrosstop", 
				           -width => $width,
				           -height => $height,
				          );

	# create the standard check boxes
	my @checkBoxNames  = @$checkList;
	my $i = 0;

	foreach my $name (@checkBoxNames)
	{
		my $checkbox = $frame->Checkbutton(-text     => "\u$name",
			     	  		               -onvalue  => $name,
				   	                       -offvalue => "", 
                                           )->place(-x => $checkOffset, -y => $checkYoff);

		if ( $name =~ m/^msa$/ )   { $checkbox->select(); }
		if ( $name =~ m/^API$/ ) { $checkbox->select(); }
		if ( $name =~ m/^config$/ ) { $checkbox->select(); }
		push @checkBoxes, $checkbox;
		$checkYoff += $checkYspace;
		$i++;
	}

	# create the entry box
    $textBox = $frame->Scrolled("Text", 
	                            -scrollbars => 'oe',                                            
				                -height => $envTextHeight,
				                -width =>  $envTextWidth,
				                -wrap => "none",
				               )->place(-x => $entryOffset, -y => $entryYoff);

	# bind the mouse movement to the update the list
	$frame->bind("<Leave>", [\&BuildCheckList, $checkList, \@checkBoxes, $textBox ]);

	# display the widgets
	$frame->pack();

}


# -----------------------------------------------------------------------------
# Function    : BuildCheckList
# Description : Replaces the current checklist with an updated one
# Parms       : $frame      -
#               $checkList  -
#               $checkBoxes -
#               $testBox    - 
# Returns     : 
# Notes       : 
# -----------------------------------------------------------------------------
sub BuildCheckList
{
	my ($frame , $checkList, $checkBoxes, $textBox) = @_;

	my @localCheckList = ();
	
	# get the values from the checkbox
	foreach $checkbox (@$checkBoxes)
	{
		my $var = $checkbox->cget(-variable);
		push @localCheckList, $$var;
	}

	# get the text from the list
	my $text = $textBox->get("1.0", "end");
	push @localCheckList, split(/\s+/, $text);
	
	# Truncate the lists
	@{$checkList} = @localCheckList;
}

1;

    






