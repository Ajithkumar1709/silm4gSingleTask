#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#conversion script
# Ron Zeira
# September 2007
# ------------------------------------------------------------------------
# Last updated by: Avishai Ziv 2010 (new ROM structure)
# ------------------------------------------------------------------------
#
#
#use warnings;
#use Switch;

sub InsertHeaderFile ($$$$@);
sub OutputFile ($$$@);

((scalar @ARGV) != 2) && die "Usage: file_name type(silicon/QT)";
$input_file = shift;
$type = shift;
if ( ($type ne 'silicon')&&($type ne 'QT') ) {
	die "Usage: file_name type(silicon\QT)";
}
$line_num = 0;
open	(SOURCE_FILE, "<$input_file") || die "\ncannot open file $input_file";
@input_lines = <SOURCE_FILE>;
@output_lines;
$instance_line = shift @input_lines;
$radix_line = shift @input_lines;
$address_line = shift @input_lines;
$address_line =~ s/3fff/1fff/;
@output_file0;
@output_file1;
@output_file2;
@output_file3;
$checksum0 = 0;
$checksum1 = 0;
$checksum2 = 0;
$checksum3 = 0;
if ( ($type eq 'QT') ) {
	@output_file0 = InsertHeaderFile (0,$instance_line,$radix_line,$address_line,@output_file0);
	@output_file1 = InsertHeaderFile (1,$instance_line,$radix_line,$address_line,@output_file1);
	@output_file2 = InsertHeaderFile (2,$instance_line,$radix_line,$address_line,@output_file2);
	@output_file3 = InsertHeaderFile (3,$instance_line,$radix_line,$address_line,@output_file3);
}

while ( $line = shift @input_lines ) {
	$line_num++;
	chomp $line;
	$line =~ /([0-9a-fA-F]{8})    ([0-9a-fA-F]{16})/;
	$address = $1;
	$data = $2;
	$serial_num = $address;
	$part = substr($serial_num,4,1);
	if ( $type eq 'QT' ) {
		$high = substr($data,0,8);
		$low = substr($data,8,8);
		$msb = ($part&0x1);
		substr($serial_num,4,1,$msb);
		$new_line1 = "$serial_num    $low\n";
		$new_line2 = "$serial_num    $high\n";
	}
	else
	{
		#silicon
		substr($serial_num,0,5,'');
		my $one = substr($serial_num,0,1);
		my $two = substr($serial_num,1,1);
		my $three = substr($serial_num,2,1);
		#next three lines are to remove leading zeros from the addresses.
		# In addition: $msb = (($part&0x1)?1:''); this line maps address [0x0,0x1FFF] to [0x0,0x1FFF]
		#                                                       and also [0x2000,0x3FFF] to [0x0,0x1FFF]
		$msb = (($part&0x1)?1:'');
		$one = (($one eq '0')?($msb eq ''?'':$one):$one);
		$two = (($two eq '0')?($one eq ''?'':$two):$two);
		$serial_num = $msb.$one.$two.$three;
		$high = substr($data,0,8);
		$low = substr($data,8,8);
		$new_line1 = "$low\n";
		$new_line2 = "$high";
	}

	if ( ($part eq '0') || ($part eq '1') ) {
		push @output_file0, $new_line2;
		push @output_file0, $new_line1;
		$checksum0 += ( hex($new_line1) >> 16 ) + ( hex($new_line1) & 0xFFFF );
		$checksum0 += ( hex($new_line2) >> 16 ) + ( hex($new_line2) & 0xFFFF );
	}
	elsif (($part eq '2') || ($part eq '3'))
	{
		push @output_file1, $new_line2;
		push @output_file1, $new_line1;
		$checksum1+= ( hex($new_line1) >> 16 ) + ( hex($new_line1) & 0xFFFF );;
		$checksum1+= ( hex($new_line2) >> 16 ) + ( hex($new_line2) & 0xFFFF );

	}
	else
	{
	   	die "Invalid address $address in line $line_num\n";
	}	
}

OutputFile (0,$input_file,$checksum0,@output_file0);
OutputFile (1,$input_file,$checksum1,@output_file1);
#OutputFile (2,$input_file,$checksum2,@output_file2);
#OutputFile (3,$input_file,$checksum3,@output_file3);

print "\nDone\n";

sub OutputFile ($$$@)
{
	my ($num,$input_name,$checksum_dec,@file) = @_;
	my $temp = "\_$num\_ROM";
	my $checksum_filename_suffix = $checksum_dec.".0x".sprintf("%X",$checksum_dec);
	my ($rom_bank_number) = $input_name;
	$rom_bank_number =~ s/L2/L/;
	$rom_bank_number =~ tr/0-9//cd;;

#	$input_name =~ s/_ROM/$temp/;
#	$input_name =~ s/\.init/\./;

	#concat the output filename to hold the checksum suffix (decimal and hex)
#	$input_name = $input_name.$checksum_filename_suffix;
#	$input_name = $input_name.".init";


	$input_name = "tavor_nevo_bank".sprintf("%02d",$rom_bank_number).".".$num.".init.".$checksum_filename_suffix;

	open(OUT_FILE , "> $input_name") || die "$0: Can't open $input_name ";
	#writing file back
	my $line;
	for $line ( @file )
	{
		print OUT_FILE $line;
	}
	close SOURCE_FILE;
}


sub InsertHeaderFile ($$$$@)
{
	 my ($num,$instance,$radix,$address,@file) = @_;
	 my $temp = "\_$num\_mem";
	 $instance =~ /u_tavor_top__u_comm_top__u_gsram__u_crom128kr_c(\d+)__u_crom128kr_c(\d+)_mem/;
	 $temp = "\_c$1\_$num\_mem";
	 $instance =~ s/_c(\d+)_mem/$temp/;
	 $instance =~ s/tavor_//;
	 push @file, $instance;
	 push @file, $radix;
	 push @file, $address;
	 return @file;
}
