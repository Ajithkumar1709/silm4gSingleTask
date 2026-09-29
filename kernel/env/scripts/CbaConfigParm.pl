#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaConfigParm.pl
# Description    : Perl script to test the configuration object
# 
# Notes          : 
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

use strict;
use CbaPackage;
use CbaConfigParm;

my $package = "C:\\viewstore\\sharker_snap_ba_dev\\stutest\\pk02";

my @config_array = getPackageConfig($package);

foreach my $config (@config_array)
{
	# print out the config information
	print "$config\n";
}



