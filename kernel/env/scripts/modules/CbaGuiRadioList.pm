#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaGuiRadioList.pm
# Description    : Perl module of the Radio List gui widget for the CBA
#                  (Cellular Build Architecture)
#
# Notes          : -title       = name to give the widget
#                  -radioList   = reference to the radio List array
#                  -variable    = contains the result value
#                  -width       = width of the frame
#                  -height      = height of the frame
#                  -entry       = enable/disable entry value
#                  -radioOffset = x offset location of the radio buttons
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

package CbaGuiRadioList;

require Tk::Frame;
@ISA = qw(Tk::Frame);

Construct Tk::Widget 'CbaGuiRadioList';

sub Populate
{
	require Tk::LabFrame;

	my ($cw, $args) = @_;

	# check for the options
	my $title          = delete $args->{"-title"};
	my $radioList      = delete $args->{"-radioList"};
	my $variable       = delete $args->{"-variable"};
	my $width          = delete $args->{"-width"};
	my $fixedheight    = delete $args->{"-height"};
	my $entry          = delete $args->{"-entry"};
	my $radioOffset    = delete $args->{"-radioOffset"};

	# pass on the rest of the arguments
	$cw->SUPER::Populate($args);

	# set the external defaults
	$title = "<Title>" unless (defined $title);
	$width = 225 unless (defined $width);
	$radioOffset = 15 unless (defined $radioOffset);
	$entry = 0 unless (defined $entry);

	# placement values for the radio buttons
	my $radioYoff   = 0;
	my $radioYspace = 20;

	# determine the placement values for the entry box
	my $entryXoff     = $radioOffset + 92;
	my $entryYoff     = $radioYoff + 4 + ($radioYspace * scalar(@$radioList));

	# determine the height of the frame
	$height = 15 + ($radioYspace * scalar(@$radioList));
	$height += 20 if ($entry);

	# override the height
	$height = $fixedheight if (defined $fixedheight);

	# define the widgets
	my $frame;
	my $entryRadio;
	my $entryBox;

	# create the labeled frame
    $frame = $cw->LabFrame(-label => $title,
			               -labelside=>"acrosstop", 
				           -width => $width,
				           -height => $height,
				          );

	# create the standard radio buttons and add the entry value
	my $i = 0;

	foreach my $name (@$radioList)
	{

		if ($entry)
		{
			$frame->Radiobutton(-text  => "\u$name",
				                -value    => $name,
								-variable => $variable,
  							    -command  => [ \&DisableEntry, \$entryBox ],
                        	    )->place(-x => $radioOffset, -y => $radioYoff);
		}
		else
		{
			$frame->Radiobutton(-text  => "\u$name",
				                -value    => $name,
								-variable => $variable,
                        	    )->place(-x => $radioOffset, -y => $radioYoff);
		}
		
		$radioYoff += $radioYspace;
		$i++;
	}

	if ($entry)
	{
		# create the last button
		$entryRadio = $frame->Radiobutton(-text  => "Enter value:",
				                          -value    => "<entry>",
								          -variable => $variable,
										  -command  => [ \&EnableEntry, \$entryBox, $variable ],
                	            )->place(-x => $radioOffset, -y => $radioYoff);

		# create the entry box
    	$entryBox = $frame->Entry(-textvariable => \$entryVar,
        	                     )->place(-x => $entryXoff, -y => $entryYoff);

		# display the widgets
		DisableEntry(\$entryBox);
		$frame->bind("<Leave>", [\&CheckEntry, \$entryVar, $variable ]);
	}

	$frame->pack();

}

sub DisableEntry
{ 
	my ($eb) = @_;

	$$eb->configure(-state => 'disabled');
#    $$eb->configure(-background => 'SystemButtonFace');
}

sub EnableEntry
{ 
	my ($eb, $var) = @_;
	$$eb->configure(-state => 'normal');
#    $$eb->configure(-background => 'SystemWindow');
}

sub CheckEntry
{
	my ($frame, $entryVar, $radioVar) = @_;

	# if the $radioVar is <entry>, use the entry value
	if ($$radioVar eq "<entry>")
	{
		$$radioVar = $$entryVar;
	}
}

1;

    






