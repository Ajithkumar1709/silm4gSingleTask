#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

((scalar @ARGV) < 1) && die "Usage: $0 <in.ldf> <out.ldf>";
$c_file = shift (@ARGV);
$inc_file = shift (@ARGV);

open(CFILE , "< $c_file") || die "Can't open '$c_file'.\n";
open(INCFILE, "> $inc_file") || die "Can't open '$inc_file'.\n";


while ( $line = <CFILE> ) { 
  next if ( $line =~ m/^\s*$/ );
  next if ( $line =~ m/^\#line .*$/ );
  if ( $line =~ m/^(.*)START\((.*)\)\s+LENGTH\((.*)\)\s+WIDTH(.*)$/ ) {
	$start = $1;
	$saddr = $2;
	$len = $3;
	$end = $4;
	
	$saddr =~ s/L//g;
	$len =~ s/L//g;
	  
	$saddr =~ s/0x([0-9,a-f,A-F]+)/ hex($1) /ge;
	$naddr = eval "$saddr";

	$len =~ s/0x([0-9,a-f,A-F]+)/ hex($1) /ge;
	$nlen = eval "$len";
	
	$line = sprintf "\n$start START(0x%08X) LENGTH(0x%08X) WIDTH$end\n", $naddr, $nlen;
  }
  else {
	$line =~ s/COMAP/\n\n\tCOMAP/g;             # format COMAPs
	$line =~ s/OVERLAY/\n\n\tOVERLAY/g;         # start of overlayed output section
	$line =~ s/OVERLAY_START/\n\n\tOVERLAY_START/g;    # format start of overlay
	$line =~ s/\{/\n\t\{/g;       # format start of all output sections
	$line =~ s/INPUT_SECTION/\n\t\tINPUT_SECTION/g;  # format input sections
	$line =~ s/\}/\n\t}/g;                             # format end of all ouput sections
  }
  print INCFILE $line;

}
