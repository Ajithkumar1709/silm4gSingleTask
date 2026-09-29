#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

my @cmd = grep { !/^\s*$/ } <main::DATA>; chomp @cmd;
foreach my $cmd (@cmd[0.. $#cmd-1]) { exit system $cmd if fork == 0 }
exit system $cmd[-1];

__DATA__

