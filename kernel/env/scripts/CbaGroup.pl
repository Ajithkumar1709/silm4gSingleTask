#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaGroup.pl
# Description    : Perl scripts for the testing of CBA group functions
# 
# Notes          : 
# 
# Copyright (c) 2000 Intel of Canada, All Rights Reserved
#==============================================================================

use strict;
use CbaGroup;

# set the default directories 
my $MSWin32RootDir = $ENV{'CBA_ROOT'} || "/";
my $root = $^O eq "MSWin32" ? $MSWin32RootDir : "/vobs";

my @groupList = ();
my @interfaceList = ();

setCbaGroupDebug(0);

# get the list of groups
getGroupList(\@groupList, $root);
print "Groups: @groupList\n";

# get a list of interfaces
foreach my $group (@groupList)
{
	getGroupInterfaceList(\@interfaceList, "$root/$group");
	print "$group Interfaces: @interfaceList\n";
	@interfaceList = ();
}





















