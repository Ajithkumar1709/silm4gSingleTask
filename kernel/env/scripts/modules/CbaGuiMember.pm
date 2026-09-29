#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaGuiMember.pm
# Description    : Perl module of the member list for the CBA
#                  (Cellular Build Architecture)
#
# Notes          : -title       = name to give the widget
#                  -srcDir      = location of the package/group elements
#                  -memList     = reference to the members list
#                  -width       = width of the frame
#                  -height      = height of the frame
#                  -listWidth   = width of the list selection box
#                  -listHeight =  height of the list selection box
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

package CbaGuiMember;

use CbaPackage;
use CbaGroup;

require Tk::Frame;
@ISA = qw(Tk::Frame);

Construct Tk::Widget 'CbaGuiMember';

sub Populate
{
	require Tk::LabFrame;

	my ($cw, $args) = @_;

	# check for the options
	my $title      = delete $args->{"-title"};
	my $srcDir     = delete $args->{"-srcDir"};
	my $memList    = delete $args->{"-memList"};
	my $width      = delete $args->{"-width"};
	my $height     = delete $args->{"-height"};
	my $listHeight = delete $args->{"-listHeight"};
	my $listWidth  = delete $args->{"-listWidth"};

	# pass on the rest of the arguments
	$cw->SUPER::Populate($args);

	# set the external defaults
	$title      = "Members" unless (defined $title);
	$listHeight = 20 unless (defined $listHeight);
	$listWidth  = 20 unless (defined $listWidth);

	# default widget locations
	my $checkXOff      = 10;
	my $packCheckYOff  = 2;
	my $groupCheckYOff = $packCheckYOff + 20;

	my $memListXOff    = $checkXOff;
	my $memListYOff    = $groupCheckYOff + 30;

	$width  = ($memListXOff + (7 * $listWidth)) unless (defined $width);
	$height = ($packCheckYOff + $memListYOff + (19 * $listHeight)) unless (defined $height);

	# create the package and group lists from the src directory
	my ($usePackages, $useGroups);
	my (@packList, @groupList);

	# fill in the package and group list strings
	foreach my $mem (@$memList)
	{
		$mem =~ s/\\/\//;
		push(@packList, $mem) if (isPackage("$srcDir/$mem"));
		push(@groupList, $mem) if (isGroup($mem));
	}

	@groupList = ("some_dir\\grp01", "some_dir\\grp02", "some_dir\\grp03", "some_dir\\grp04");

	# define the widgets
	my $frame;
	my $packCheckBox;
	my $groupCheckBox;
	my $memListBox;

	# create the labeled frame
    $frame = $cw->LabFrame(-label => $title,
			               -labelside=>"acrosstop", 
				           -width => $width,
				           -height => $height,
				          );

	# create the package checkbox
	$packCheckBox = $frame->Checkbutton(-text     => "Show Packages",
                                        -variable => \$usePackages,
	                                    -command  => [ \&ShowMemberList, \$memListBox, \$usePackages, \$useGroups, \@packList, \@groupList],
                                       )->place(-x => $checkXOff, -y => $packCheckYOff);

	# create the group checkbox
	$groupCheckBox = $frame->Checkbutton(-text     => "Show Groups",
                                         -variable => \$useGroups,
	                                     -command  => [ \&ShowMemberList, \$memListBox, \$usePackages, \$useGroups, \@packList, \@groupList],
                                        )->place(-x => $checkXOff, -y => $groupCheckYOff);

	# create the members list box
	$memListBox = $frame->Scrolled('Listbox', 
	                               -background => 'white',
	                               -height => $listHeight,
								   -width  => $listWidth,
                                   -scrollbars => "osoe",
                                   )->place(-x => $memListXOff, -y => $memListYOff);
	# display the widgets
	$frame->pack();

}


sub ShowMemberList
{
	my ($lb, $usePackages, $useGroups, $memList) = @_;

	$$lb->delete(0, "end");

	$$lb->insert("end", @$packList) if ($$usePackages);
	$$lb->insert("end", @$groupList) if ($$useGroups);
}

sub UpdateDest
{ 
	my ($frame, $lb, $array) = @_;

    @$array = $$lb->get(0, "end");
}

1;

    






