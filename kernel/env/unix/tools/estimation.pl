#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

use File::Basename;
$out = shift @ARGV;
@a=@ARGV;

while(<>)
{
    $f=basename(shift(@a));
    $f=~/^(.+)\.(.+)$/;
    $b=eval($_);
    $report{$2}{$1}=$b;
    $report{$2}{'TOTAL'} +=$b;
} 
print "\n\n";
foreach $k (keys %report)
{
    if($report{$k}{'TOTAL'} != 0)
    {
	$a = abs($report{$k}{'TOTAL'});
	print qq(By using macro $k code size );
	print qq(increases ) if $report{$k}{'TOTAL'} > 0;
	print qq(decreases ) if $report{$k}{'TOTAL'} < 0;
	print qq(by $a lines\n); 
    }
    else
    {
	print qq(Macro $k has no influence on code\n);
    }
    
}


if(open(OUT,">>$out"))
{
    foreach $k (keys %report)
    {
	if($report{$k}{'TOTAL'} != 0)
	{
	    $a = abs($report{$k}{'TOTAL'});
	    print OUT qq(>> BY USING MACRO $k CODE SIZE );
	    print OUT qq(INCREASES ) if $report{$k}{'TOTAL'} > 0;
	    print OUT qq(DECREASES ) if $report{$k}{'TOTAL'} < 0;
	    print OUT qq(BY $a LINES\n); 
	}
	else
	{
	    print OUT qq(>> MACRO $k HAS NO INFLUENCE ON CODE\n);
	}
    }

    foreach $k (keys %report)
    {
	$flag=0;
	foreach $e (keys %{$report{$k}})
	{
	    $flag =1 if $report{$k}{$e} != 0;
	}
	if(!$flag)
	{
	    print OUT "\t Macro $k has no influence on code at all (most probably it is not in use)\n\n";
	}
	else
	{
	    print OUT "\n\t Details\n\t\tMacro $k influences the following entities:\n";
	    foreach $e (keys %{$report{$k}})
	    {
		next if $e eq 'TOTAL';
		if($report{$k}{$e} != 0)
		{
		    ($entity = $e) =~ s|_|\\|;
		    $influence = "increases";
		    $influence = "decreases" if $report{$k}{$e} < 0;
		    $lines = abs($report{$k}{$e});
		    print OUT "\t\t\t$entity code size $influence by $lines lines\n";
		}
	    }
	    print OUT "\n\n";
	}
    }
    close OUT;
}
else
{
    print "Failed to open $out file. No report will be generated\n";
}
