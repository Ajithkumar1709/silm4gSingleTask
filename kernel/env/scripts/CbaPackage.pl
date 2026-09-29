#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaPackage.pl
# Description    : Perl scripts for the testing of CBA package functions
# 
# Notes          : 
# 
# Copyright (c) 2000 Intel of Canada, All Rights Reserved
#==============================================================================

use strict;
use CbaPackage;

# set the default directories 
my $MSWin32RootDir = $ENV{'CBA_ROOT'} || "/";
my $root = $^O eq "MSWin32" ? $MSWin32RootDir : "/vobs";

my @packageList = ();
my @interfaceList = ();

setCbaPackageDebug(0);

# get the list of packages
getPackageList(\@packageList, $root);
print "Packages: @packageList\n";

# get a list of interfaces
foreach my $package (@packageList)
{
	CbaPackage::getPackageInterfaceList(\@interfaceList, "$root/$package");
	print "$package Interfaces: @interfaceList\n";
	@interfaceList = ();
}





















