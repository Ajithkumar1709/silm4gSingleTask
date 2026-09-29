use Fcntl;
use File::Basename;
use File::Spec::Functions;

$DEBUG = 0;
$OPEN_HEADER_LENGTH = 64;
$OPEN_HEAD_MAGIC_NUM = 0x87362510;
$LZMA_FILENAME = $ARGV[0];
$IMG_FILENAME = $ARGV[1];
$COMPRE_FILENAME = $ARGV[2];
$PART_1 = "part1";
$PART_2 = "part2";

sysopen(INPUT_STREAM,"$IMG_FILENAME",O_BINARY|O_RDONLY)
	or error_exit("Can't open [$IMG_FILENAME] for reading; $!");

sysread(INPUT_STREAM,$OPEN_HEAD_MAGIC,4);
$OPEN_HEAD_MAGIC = raw_to_hex($OPEN_HEAD_MAGIC);
$OPEN_HEAD_MAGIC = $OPEN_HEAD_MAGIC&0xfffffff0;
if ($OPEN_HEAD_MAGIC != $OPEN_HEAD_MAGIC_NUM){	
	error_exit("NO app magic string [$OPEN_HEAD_MAGIC_NUM] detect, exit");
}else{
	#open OUTBIN_P1,">$IMG_FILENAME\_$PART_1" or error_exit("can't open $IMG_FILENAME\_$PART_1 for output");
	sysopen(OUTBIN_P1,"$IMG_FILENAME\_$PART_1",O_BINARY|O_CREAT|O_RDWR);
	debug_msg("create the empty $IMG_FILENAME\_$PART_1");
	close OUTBIN_P1;

	#open OUTBIN_P2,">$IMG_FILENAME\_$PART_2" or error_exit("can't open $IMG_FILENAME\_$PART_2 for output");
	sysopen(OUTBIN_P2,"$IMG_FILENAME\_$PART_2",O_BINARY|O_CREAT|O_RDWR);
	debug_msg("create the empty $IMG_FILENAME\_$PART_2");
	close OUTBIN_P2;
};

#write open header to part1
sysseek(INPUT_STREAM,0,0);
sysopen(OUTBIN_P1,"$IMG_FILENAME\_$PART_1",O_BINARY|O_WRONLY|O_APPEND);
sysread(INPUT_STREAM,$OPEN_HEADER,$OPEN_HEADER_LENGTH);
syswrite(OUTBIN_P1,$OPEN_HEADER,$OPEN_HEADER_LENGTH);
close OUTBIN_P1;

#write other code to part2
$UNCOMPRESSED_SIZE=-s "$IMG_FILENAME";
$UNCOMPRESSED_SIZE=$UNCOMPRESSED_SIZE-$OPEN_HEADER_LENGTH;
sysopen(OUTBIN_P2,"$IMG_FILENAME\_$PART_2",O_BINARY|O_WRONLY|O_APPEND);
sysread(INPUT_STREAM,$UNCOMPRESSED_BUFFER,$UNCOMPRESSED_SIZE);
syswrite(OUTBIN_P2,$UNCOMPRESSED_BUFFER,$UNCOMPRESSED_SIZE);
close OUTBIN_P2;
close INPUT_STREAM;

#compress the part2
qx("$LZMA_FILENAME" e $IMG_FILENAME\_$PART_2 $COMPRE_FILENAME 2>&1 );
unlink("$IMG_FILENAME\_$PART_2");
rename("$COMPRE_FILENAME","$IMG_FILENAME\_$PART_2");

#merge part1 and part2
file_merge("$IMG_FILENAME\_$PART_1","$IMG_FILENAME\_$PART_2",$COMPRE_FILENAME);

unlink("$IMG_FILENAME\_$PART_1");
unlink("$IMG_FILENAME\_$PART_2");
exit(0);

# functions
#
sub hex_32_reorder{
   local $m_hex = $_[0];
   $m_hex = ((($m_hex&0x000000ff)<<24)|
		(($m_hex&0x0000ff00)<<8)|
		(($m_hex&0x00ff0000)>>8)|
		(($m_hex&0xff000000)>>24));
   return $m_hex;
}

sub raw_to_hex{
   local $m_hex = hex(unpack("H*",$_[0]));
   $m_hex = hex_32_reorder($m_hex);
   return $m_hex;
}

sub debug_msg{
	unless($DEBUG){return};
	local $DEBUG_MSG="DEBUG >>> :";
	print "$DEBUG_MSG @_";
	print "\n";
}
sub error_exit{
	local $ERROR_MSG="\nERROR:**";
	print "----------------------";
	print "$ERROR_MSG @_";
	print "\n";
	exit(1);
}

sub file_merge{
	open(RH,$_[0]) or die "$!";
	binmode RH;
	my @src_1=<RH>;
	close RH;

	open(RH,$_[1]) or die "$!";
	binmode RH;
	my @src_2=<RH>;
	close RH;

	#create&overwrite for input file arg0
	open(WH,">$_[2]") or die "$!";
	binmode WH;
	my $i;
	for($i = 0; $i < @src_1; $i++){
		print WH $src_1[$i];
	}
	close WH;

	#append for input file arg1
	open(WH,">>$_[2]") or die "$!";
	binmode WH;
	my $i;
	for($i = 0; $i < @src_2; $i++){
		print WH $src_2[$i];
	}
	close WH;

}
