#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaHeader.pl
# Description    : Perl test module for creating headers
# 
# Notes          : 
# 
# Copyright (c) 2000 Intel of Canada, All Rights Reserved
#==============================================================================

use strict;
use CbaHeader;


if (0)
{
	open FH, "< pk01_config.h";
	my @test_file = <FH>;
	close FH;

	# generate the file header prototype
	my $fileHeader = CbaHeader->new();
	$fileHeader->Fill("=", 1);
	$fileHeader->HeaderField("File");
	my @parsedFileHeaders = $fileHeader->Parse(\@test_file);

	# generate the config header prototype
	my $configHeader = CbaHeader->new();
	$configHeader->HeaderField("Parameter");
	my @parsedConfigHeaders = $configHeader->Parse(\@test_file);

	open SH, "> test.h";
	print SH "@parsedFileHeaders";
	print SH "@parsedConfigHeaders";
}

if (1)
{
    open FH, "< header.txt";
    my @test_file = <FH>;
    close FH;

    # generate the record header prototype
    my $recHeader = CbaHeader->new();
    my @parsedRecHeaders = $recHeader->Parse(\@test_file, 1);

    open FH, "> header.out";
	print FH "@parsedRecHeaders";
    close FH;
}