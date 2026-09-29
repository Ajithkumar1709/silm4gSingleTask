#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaGuiClearCase.pm
# Description    : Perl module of the ClearCase gui widget for the CBA
#                  (Cellular Build Architecture)
#
# Notes          : -ccFlagVar   = reference to the ccFlag variable
#                  -lvcoFlagVar = reference to the lvcoFlag variable
#                  -height      = height of the frame
#                  -width       = width of the frame
#                  -entryOffset = x offset location of the entry boxes
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

package CbaGuiClearCase;

require Tk::Frame;
@ISA = qw(Tk::Frame);

Construct Tk::Widget 'CbaGuiClearCase';

sub Populate
{
    require Tk::LabFrame;
    
    my ($cw, $args) = @_;
    
    # check for the options
    my $ccFlagVar    = delete $args->{"-ccFlagVar"};
    my $lvcoFlagVar  = delete $args->{"-lvcoFlagVar"};
    my $width        = delete $args->{"-width"};
	my $height       = delete $args->{"-height"};
    my $entryOffset  = delete $args->{"-entryOffset"};
    
    # pass on the rest of the arguments
    $cw->SUPER::Populate($args);
    
    # set the external defaults
    $width = 225 unless (defined $width);
    $entryXoff = 20 unless (defined $entryXoff);
	$height = 55 unless (defined $height);
    
    my $lineYoff  = 25;
    
    my $ccCheckXoff = $entryXoff;
    my $ccCheckYoff = 20;
    
    my $ciCheckXoff = $entryXoff;
    my $ciCheckYoff = $ccCheckYoff + $lineYoff;
    
    # define the widgets
    my $frame;
    my $ccCheck;
    my $ciCheck;
    
    # create the labeled frame
    $frame = $cw->LabFrame(-label => "ClearCase",
			   -labelside=>"acrosstop", 
			   -width => $width,
			   -height => $height,
			   );
    
    # create the ClearCase check box
    $ccCheck = $cw->Checkbutton(-text => "Create CC elements in current view?",
				-variable => $ccFlagVar,
				-command => sub { if ($$ccFlagVar)
						  {
						      $ciCheck->configure(-state => 'normal');
						  }
						  else
						  {
						      $ciCheck->configure(-state => 'disable');
						      $ciCheck->select;
							  $lvcoFlag = 1;
						  }},
				);
    
    # create the ClearCase check-in check box
    $ciCheck = $cw->Checkbutton(-text => "Leave CC elements checked out?",
                                -state => 'disable',
				-command => sub { if ($$lvcoFlagVar)
						  {
						      $ccCheck->select;
						      $ccCheck->configure(-state => 'disable');
						  }
						  else
						  {
						      $ccCheck->configure(-state => 'normal');
						  }},
				-variable => $lvcoFlagVar,
				);
    
    # display the widgets
    $ccCheck->place( -x => $ccCheckXoff,  -y => $ccCheckYoff);
    $ciCheck->place( -x => $ciCheckXoff,  -y => $ciCheckYoff);
    $frame->pack();
    
}
1;









