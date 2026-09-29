#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

use File::Basename;

my $originListFile   = shift @ARGV;
my $linkByOrderFile  = shift @ARGV;
my $resultListFile   = shift @ARGV;

open(LIST, "<$originListFile") or die "Failed to open $originListFile for reading";
my @OriginList = <LIST>;
chomp @OriginList;
close LIST;

open(LIST, "<$linkByOrderFile") or die "Failed to open $linkByOrderFile for reading";
my @LinkByOrderList = <LIST>;
chomp @LinkByOrderList;
close LIST;

my @NewObjList;
my @NewLinkByOrderList;
foreach my $link (@LinkByOrderList)
{
    $link =~ s/\.\w+$//;
    my @temp = grep {/\W$link\./} @OriginList;

    if(scalar(@temp) == 1)
    {
		push @NewLinkByOrderList, @temp;
		for(my $i=0; $i<=$#OriginList; $i++)
		{
			if($OriginList[$i] eq $temp[0])
			{
				delete $OriginList[$i];
				last
			}
		}
    }
    elsif(scalar(@temp) > 1)
    {
		print "$link file name appears more than once\n";
		exit 1;
    }
}

foreach (@OriginList)
{
	push @NewObjList, $_ if $_;
}

my @SortedLinkByOrderList = sort {lc(basename($a)) cmp lc(basename($b))} @NewLinkByOrderList;
my @SortedNewObjList      = sort {lc(basename($a)) cmp lc(basename($b))} @NewObjList;

my $str;

open(LIST,">$originListFile") or die "Failed to open $originListFile for writing";
$str = join("\n", @SortedNewObjList);
print LIST $str;
close LIST;

open(LIST,">$resultListFile") or die "Failed to open $resultListFile for writing";
$str = join("\n", @SortedLinkByOrderList);
print LIST $str;
close LIST;
