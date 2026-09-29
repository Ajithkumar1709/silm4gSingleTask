#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaGuiMemberSelect.pm
# Description    : Perl module of the member selection for the CBA
#                  (Cellular Build Architecture)
#
# Notes          : -title       = name to give the widget
#                  -srcDir      = location of the package/group elements
#                  -destList    = reference to the destination list
#                  -width       = width of the frame
#                  -height      = height of the frame
#                  -listWidth   = width of the list selection box
#                  -listHeight =  height of the list selection box
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

package CbaGuiMemberSelect;

use CbaPackage;
use CbaGroup;

require Tk::Frame;
@ISA = qw(Tk::Frame);

Construct Tk::Widget 'CbaGuiMemberSelect';

sub Populate
{
	require Tk::LabFrame;

	my ($cw, $args) = @_;

	# check for the options
	my $title      = delete $args->{"-title"};
	my $srcDir     = delete $args->{"-srcDir"};
	my $destList   = delete $args->{"-destList"};
	my $width      = delete $args->{"-width"};
	my $height     = delete $args->{"-height"};
	my $listHeight = delete $args->{"-listHeight"};
	my $listWidth  = delete $args->{"-listWidth"};

	# pass on the rest of the arguments
	$cw->SUPER::Populate($args);

	# set the external defaults
	$title      = "Member Selection" unless (defined $title);
	$listHeight = 10 unless (defined $listHeight);
	$listWidth  = 20 unless (defined $listWidth);

	# default widget locations
	my $checkXOff      = 10;
	my $packCheckYOff  = 2;
	my $groupCheckYOff = $packCheckYOff + 20;

	my $listSeparation = 15;
	my $srcListXOff    = $checkXOff;
	my $srcListYOff    = $groupCheckYOff + 30;
	my $destListXOff   = $srcListXOff + $listSeparation + (7 * $listWidth);
	my $destListYOff   = $srcListYOff;

	$width  = ((2 * $srcListXOff) + $listSeparation + (14 * $listWidth)) unless (defined $width);
	$height = ($packCheckYOff + $srcListYOff + (19 * $listHeight)) unless (defined $height);

	# define the widgets
	my $frame;
	my $packCheckBox;
	my $groupCheckBox;
	my $srcListBox;
	my $destListBox;

	# create the package and group lists from the src directory
	my ($usePackages, $useGroups);
	my (@packList, @groupList);
	getPackageList(\@packList, $srcDir);
	getGroupList(\@groupList, $srcDir);

	# create the labeled frame
    $frame = $cw->LabFrame(-label => $title,
			               -labelside=>"acrosstop", 
				           -width => $width,
				           -height => $height,
				          );

	# create the package checkbox
	$packCheckBox = $frame->Checkbutton(-text     => "Show Packages",
                                        -variable => \$usePackages,
	                                    -command  => [ \&BuildEntryList, \$srcListBox, \$usePackages, \$useGroups, \@packList, \@groupList],
                                       )->place(-x => $checkXOff, -y => $packCheckYOff);

	# create the group checkbox
	$groupCheckBox = $frame->Checkbutton(-text     => "Show Groups",
                                         -variable => \$useGroups,
	                                     -command  => [ \&BuildEntryList, \$srcListBox, \$usePackages, \$useGroups, \@packList, \@groupList],
                                        )->place(-x => $checkXOff, -y => $groupCheckYOff);

	# create the source list box
	$srcListBox = $frame->Scrolled('Listbox', 
	                               -background => 'white',
	                               -height => $listHeight,
								   -width  => $listWidth,
                                   -scrollbars => "osoe",
                                   )->place(-x => $srcListXOff, -y => $srcListYOff);

	# create the destination list box
	$destListBox = $frame->Scrolled('Listbox', 
	                                -background => 'white',
	                                -height => $listHeight,
								    -width  => $listWidth,
	                                -scrollbars => "osoe",
	                                )->place(-x => $destListXOff, -y => $destListYOff);

	# bindings for the widget
	$srcListBox->bind("<Double-Button-1>", [ \&AddDest, \$destListBox ]);
	$destListBox->bind("<Double-Button-1>", \&RemoveDest);
	$frame->bind("<Leave>", [ \&UpdateDest, \$destListBox, $destList]);

	# display the widgets
	$frame->pack();

}


sub BuildEntryList
{
	my ($lb, $usePackages, $useGroups, $packList, $groupList) = @_;

	$$lb->delete(0, "end");
	$$lb->insert("end", @$packList) if ($$usePackages);
	$$lb->insert("end", @$groupList) if ($$useGroups);
}

sub AddDest
{
	my ($lb, $dest) = @_;

    # get the entry value
    my $select = $lb->get($lb->curselection());

    # add the element only if it not already there
    my @list = $$dest->get(0, "end");
    my $found = grep(/^\Q$select\E/, @list);
    $$dest->insert("end", $select) unless ($found);
}

sub RemoveDest
{
	my ($lb) = @_;

    $lb->delete($lb->curselection());
}

sub UpdateDest
{ 
	my ($frame, $lb, $array) = @_;

    @$array = $$lb->get(0, "end");
}

1;

    






