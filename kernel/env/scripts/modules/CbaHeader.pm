#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaHeader.pm
# Description    : Perl module for creating headers
# 
# Notes          : 
# 
# Copyright (c) 2000 Intel of Canada, All Rights Reserved
#==============================================================================

package CbaHeader;

use strict;
use overload     q("") => \&Header;

# -----------------------------------------------------------------------------
# Function    : new
# Description : Constructor
# Parms       : none
# Returns     : reference to self
# Notes       : 
# -----------------------------------------------------------------------------
sub new
{
	my $invocant = shift;
	my $class = ref($invocant) || $invocant;
	my $self  = {
				first_start	=> "/* ",
				first_end  	=> "---",
				mid_start  	=> "",
				mid_end		=> "",
				last_start 	=> "---",
				last_end    => " */",
				fill		=> '-',
				delimiter   => "  : ",		# At least 2 spaces before colon needed by 
											# CompareVersions.pm in devsupp vob.
				keybuf      => "",
				type        => "",
				line_width  => 75,
				key_width   => 0,
				lines       => 0,
				line_num    => 0,
				order       => [],
				debug_level => 0,
				@_,
	};

	bless($self, $class);
	return $self;
}

# -----------------------------------------------------------------------------
# Function    : setDebugLevel
# Description : sets the debug level for the object
# Parms       : level
# Returns     : level
# Notes       : 
# -----------------------------------------------------------------------------
sub setDebugLevel
{
	my $self  = shift;

	$self->{debug_level} = shift if (@_);

	return $self->{debug_level};
}

# -----------------------------------------------------------------------------
# Function    : debug
# Description : prints a debug string 
# Parms       : level
# Returns     : 
# Notes       : 
# -----------------------------------------------------------------------------
sub debug
{
	my ($self, $level, $str) = @_;
	return unless ($self->{debug_level});
	print "CbaHeader> $str" if ($level <= $self->{debug_level});
}

# -----------------------------------------------------------------------------
# Function    : clone
# Description : Copies the information contained in the header object
# Parms       : none
# Returns     : 
# Notes       : 
# -----------------------------------------------------------------------------
sub clone
{
	my $self  = shift;

	my $header = CbaHeader->new();

	# copy the header fields
	foreach my $key (keys %$self)
	{
		$header->{$key} = $self->{$key};
	}

	# the order array must be a real copy not a reference
	$header->{order} = [];
	foreach my $key (@{$self->{order}})
	{
		push @{$header->{order}}, $key;
	}

	return $header;
}

# -----------------------------------------------------------------------------
# Function    : Comments
# Description : Sets the comment characters
# Parms       : first_start - 
#               first_end   -
#               mid_start   -
#               mid_end     -
#               last_start  -
#               last_end    -
# Returns     : list of comments
# Notes       : 
# -----------------------------------------------------------------------------
sub Comments
{
	my $self = shift;

	if (@_)
	{
		my ($first_start, $first_end, 
		    $mid_start,   $mid_end, 
		    $last_start,  $last_end) = @_;

		$self->{first_start} = $first_start if (defined $first_start);
		$self->{first_end} = $first_end if (defined $first_end);

		$self->{mid_start} = $mid_start if (defined $mid_start);
		$self->{mid_end} = $mid_end if (defined $mid_end);

		$self->{last_start} = $last_start if (defined $last_start);
		$self->{last_end} = $last_end if (defined $last_end);
	}

	my @ret =  [ $self->{start_first}, $self->{start_end}, 
	    	     $self->{mid_first}, $self->{mid_end}, 
	    	     $self->{last_first}, $self->{last_end} ];
	return @ret;
}

# -----------------------------------------------------------------------------
# Function    : SingleLineComments
# Description : Sets the comment characters
# Parms       : start - start of line comment
#               end   - end of line comment
# Returns     : start and end if a single line comment else undef
# Notes       : 
# -----------------------------------------------------------------------------
sub SingleLineComments
{
	my $self = shift;

	if (@_)
	{
		my ($start, $end) = @_;
		$end = "" unless (defined $end);
		$self->Comments($start, $end, $start, $end, $start, $end);
	}
}


# -----------------------------------------------------------------------------
# Function    : Width
# Description : Sets the widths of the header
# Parms       : line width  - 
#               field width -
# Returns     : (line width, field width)
# Notes       : 
# -----------------------------------------------------------------------------
sub Width
{
	my $self = shift;

	if (@_)
	{
		my ($line, $field) = @_;

		$self->{line_width} = $line if ($line);
		$self->{key_width} = $field if ($field);
	}

	return [ $self->{line_width}, $self->{key_width} ];

}

# -----------------------------------------------------------------------------
# Function    : Fill
# Description : Sets the fill characters
# Parms       : fill - value of the fill character
# Returns     : none
# Notes       : If fill length is larger than one only the first char
#               is used. This function will change the first_end, and 
#               last_start if this is a multi-line comment type. 
# -----------------------------------------------------------------------------
sub Fill
{
	my ($self, $fill, $multi_line) = @_;
	$multi_line = 0 unless (defined $multi_line);

	if (@_)
	{
		# update the first_end and last_start if this 
		# header is a multi-line comment block
		if ($multi_line)
		{
			$self->{first_end} =~ s/$self->{fill}/$fill/g;
			$self->{last_start} =~ s/$self->{fill}/$fill/g;
		}

		$self->{fill} = $fill;
	}

	return $self->{fill};
}

# -----------------------------------------------------------------------------
# Function    : HeaderKeys
# Description : returns an array of header key names
# Parms       : none
# Returns     : an array reference
# Notes       : 
# -----------------------------------------------------------------------------
sub HeaderKeys
{
	my $self = shift;
	return(@{$self->{order}});
}

# -----------------------------------------------------------------------------
# Function    : HeaderField
# Description : updates a field and string to the header
# Parms       : key   - the header field to update
#               field - the new key data field
# Returns     : none
# Notes       : If the key does not exist, it is added to the header. If
#               the key exists it value is updated. If no field is given
#               the field for the key is returned.
# -----------------------------------------------------------------------------
sub HeaderField
{
	my $self = shift;
	my ($key, $field) = @_;

	# return the field value
	return $self->{$key} unless (defined $field);

	# the key exist	so update
	if ( exists $self->{$key} )
	{
		$self->{$key} = $field;
		return $self->{$key};
	}
	else
	{
		# add the key and field and save the order
		$self->{$key} = $field;
		push @{ $self->{order} }, $key;

		# embedded <tag> keys have no field width, so do not update 
		# the field width
		unless ($key =~ /<*>/)
		{
			# update the field width and key buffer
			my $length = length $key;
			$self->{key_width} = $length if ($length > $self->{key_width});

			# is this the first real key to be added, set the header type
			$self->{type} = $key unless ($self->{type});
		}

		return $field;
	}
}

# -----------------------------------------------------------------------------
# Function    : Print
# Description : prints the parameter to the io handler
# Parms       : fh - file handler to print to
# Returns     : none
# Notes       : Will print the header if it exists or generate 
#               the autoheader.
# -----------------------------------------------------------------------------
sub Print
{
	my $self = shift;
	my $fh = shift;
	$fh = *STDOUT unless $fh;

	my $text = $self->Header();
	print $fh "$text";
}

# -----------------------------------------------------------------------------
# Function    : Header
# Description : Retrieves a formatted header to an array
# Parms       : none
# Returns     : array
# Notes       : 
# -----------------------------------------------------------------------------
sub Header
{
	my $self = shift;
	my $newHeader;

	# output the first line
	$newHeader = $self->FormatCommentLine('first');

	# print the header fields
	foreach my $key (@{ $self->{order} })
	{
		$newHeader .= $self->FormatField($key);
	}
	
	# print the last line
	$newHeader .= $self->FormatCommentLine('last');

	return($newHeader);

}

# -----------------------------------------------------------------------------
# Function    : FormatCommentLine
# Description : formats the first or last line of a comment
# Parms       : line - 'first' or 'last' 
# Returns     : output string
# Notes       : 
# -----------------------------------------------------------------------------
sub FormatCommentLine
{
	my ($self, $line) = @_;
	my $start_key = $line."_start";
	my $end_key = $line."_end";

	$self->debug(5, "Header Line Width = $self->{line_width}\n");

	my $length = $self->{line_width} - 
	             length($self->{$start_key}) - 
	             length($self->{$end_key});
	
	($length = $length / length($self->{fill})) if length($self->{fill});

	return $self->{$start_key}.
	       ("$self->{fill}" x $length).
	       "$self->{$end_key}\n";
}

# -----------------------------------------------------------------------------
# Function    : FormatField
# Description : formats a field line in the header
# Parms       : key - field to format
# Returns     : 
# Notes       : Tab characters will be lost
# -----------------------------------------------------------------------------
sub FormatField
{
	my ($self, $key) = @_;
	my $output;
	my $line_pos = 0;
    my $line_left;
	my $debugStr;
	my $fill;

	$self->{keybuf} = ' ' x $self->{key_width};
	my $line_limit = $self->{line_width} - length($self->{mid_end}) + 1;
	my $buf_length = length($self->{keybuf}) + length($self->{delimiter});

    $self->debug(1, "Line Limit = $line_limit\n");

 	# output the field start comment characters
	$output .= $self->{mid_start};
	$line_pos = length $self->{mid_start};

	# output the key and the delimiter only if
	# the key is not an embedded key
	unless ($key =~ /<*>/)
	{
		$output .= $key;
		$output .= ' ' x ($self->{key_width} - length($key));
		$output .= $self->{delimiter};
		$line_pos += $buf_length;
	}

	# format the field text - Embed the CR's
	# and break the string into words.
	my $str = $self->{$key};

	# the field may be empty
	unless (defined $str)
	{
		$output .= "\n";
		return $output;
	}

	$str =~ s/\n/ <cr> /g;
	my @field_text = split(/\s/, $str);

	# output the text a word at a time
	foreach my $word (@field_text)
	{
		# newline found 
		# pad the line to the end if mid_end exists
		if ($word eq "<cr>")
		{
			# insert the carriage return now, do not pad
			if ($self->{mid_end} eq "")
			{
				$line_pos = $line_limit;
			}
			else
			{
				$line_left = $line_limit - $line_pos;
				$word = ' ' x ($line_left - 1);
			}
		}

		# output the word on the current line if room
		if (($line_pos + length($word)) < $line_limit)
		{
			$output .= "$word ";
			$line_pos += length($word) + 1;
			next;
		}

		# move to the next line and output if no room
		if (($line_pos + length($word)) >= $line_limit)
		{
			# pad out the current line, if mid_end exists
			if ($self->{mid_end} eq "")
			{
				$line_left = 0;
			}
			else
			{
				$line_left = $line_limit - $line_pos;				
			}
			
			$fill = ' ' x $line_left;
			$output .= "$fill$self->{mid_end}\n";
			$line_pos += $line_left;
			
			# start the next line
			$output .= "$self->{mid_start}$self->{keybuf}";
			$output .= ' ' x length($self->{delimiter});
			$line_pos = length($self->{mid_start}) + $buf_length;

			$output .= "$word " unless ($word eq "<cr>");
			$line_pos += length($word) + 1;
		}
	}

	# pad the last line
	unless ($self->{mid_end} eq "")
	{
		$line_left = $line_limit - $line_pos;
		$fill = ' ' x $line_left;
		$output .= "$fill$self->{mid_end}";
	}

	# finish the field
	$output .= "\n";
	
	return $output;
}

# -----------------------------------------------------------------------------
# Function    : Parse
# Description : parses an array for the header info
# Parms       : array ref - the array to parse
# Returns     : array of header objects
# Notes       : The line numbers for the start of the headers are
#               contained in the header object
# -----------------------------------------------------------------------------
sub Parse
{
	my ($self, $array) = @_;

	my $fill        = $self->{fill};
	my $delimiter   = $self->{delimiter};
	my $first_start = $self->{first_start};
    my $first_end   = $self->{first_end};
	my $last_start  = $self->{last_start};
	my $last_end    = $self->{last_end};
	my $mid_start   = $self->{mid_start};
	my $mid_end     = $self->{mid_end};

	my $key;						# the key for the current header entry
	my $key_width = 0;			    # the maximum key width for the current header
	my $field;						# the field for a current header entry
	my $field_line;					# the field data for the current line
    my $first_word;                 # the first word of the line or field

	my @header_array = ();			# all the headers in the file
    my $header;                     # the current header object
	my $header_count = 0;			# the headers parsed so far
	my $header_match = 0;			# whether a matching header is being parsed

	my $entry_match  = 0;			# an entry has been found
	my $entry_line_pos = 0;		    # last char position on the current entry line
	my $entry_prev_line_pos = 0;	# last char position on the current entry line	
	my $entry_field_pos = $self->{line_width};

	my $line_num = 0;

	# extract the headers from the array
	foreach my $line (@$array)
	{
		$line_num++;		
		$self->debug(2, "\n           $line");
		$self->debug(2, "12345678901234567890123456789012345678901234567890123456789012345678901234567890\n");
		$self->debug(2, "         1         2         3         4         5         6         7         8\n");

		# check for the first line of the header
		if ($line =~ /^(\Q$first_start\E(\Q$fill\E)*\Q$first_end\E)/ && $header_match == 0)
		{	
			$self->debug(1, "[$line_num] First line type.\n");

			# we are in a header if no header type was given, 
			# else check that the first entry matches
			$header_match = 1 if (($self->{type} eq "") && $header_match == 0);

			# create a new header object and update the header information.
            # if the header type does not match, it will be created anyway.
            # The next first header line match will create another header 
            # oobject, replacing the first header object. Perl's garbage 
            # collection will handle this memory leak.
			$header = $self->clone();
			$header->{line_num} = $line_num;
			$header->{line_width} = length($1);
			$self->debug(2, "Line width = $header->{line_width}\n");
			next;
		}

		# check for the last line of the header
		if ($line =~ /^\Q$last_start\E(\Q$fill\E)*?\Q$last_end\E/)
		{
			# do not parse this line unless inside a matching header
			next unless ($header_match);
			$self->debug(1, "[$line_num] Last line type.\n");

			# Add the previous entry to the header object.
			if ($entry_match)
			{
				$self->debug(3, "Adding <$key> header entry !\n");
				$header->HeaderField($key, $field);
			}

			# save the number of lines in the header
			$header->{lines} = $line_num - $self->{line_num};

			# adjust the key width if required. If the key width
			# is larger than the string length of any of the keys
			# then update the header's key width
			my @keylist = $header->HeaderKeys();
			my $max_str_length = 0;

			foreach my $key (@keylist)
			{
				# skip embedded keys
				next if ($key =~ /<.*>/);
				$header->{key_width} = $key_width if ($key_width > length $key);
			}

			$self->debug(1, "Parsed Header[$header_count]...\n$header\n");
			
			# save the header object and disable header parsing
			push @header_array, $header;
			$header_count++;
			$header_match = 0;
			$entry_match = 0;
			$field = "";
			next;
		}

		# check for a blank line
		if ($line =~ /^\Q$mid_start\E\s+\Q$mid_end\E$/)
		{
			# do not parse this line unless inside a matching header
			next unless ($header_match);
			$self->debug(1, "[$line_num] Blank line type.\n");

			$field .= "\n";
			next;
		}

		# check for the first entry line
		if ($line =~ /^(\Q$mid_start\E(([^\s]+?)\s*\Q$delimiter\E)(.+?))\s*?\Q$mid_end\E$/)
		{
			# we are in a header if the key matches the header type
			$header_match = 1 if ($3 eq $self->{type} && $header_match == 0);

			# do not parse this line unless inside a matching header
			next unless ($header_match);
			$self->debug(1, "[$line_num] First entry line type.\n");

			# Add the previous entry to the header object.
			if ($entry_match)
			{
				$self->debug(3, "Adding <$key> header entry !\n");
				$header->HeaderField($key, $field);
			}

			$self->debug(2, "Regex 1 = <$1>\n");
			$self->debug(2, "Regex 2 = <$2>\n");
			$self->debug(2, "Regex 3 = <$3>\n");
			$self->debug(2, "Regex 4 = <$4>\n");

            # extract the values
			$entry_line_pos  = length $1;
			$entry_field_pos = length $2;
            $key = $3;
            $field = $4;

			$self->debug(3, "Entry pos = $entry_field_pos\n");
			$self->debug(3, "Last char = $entry_line_pos\n");

            # we have entry data for the header object
            $entry_match = 1;
			next;
		}

		# check for an entry continuation line
		if ($line =~ /^(\Q$mid_start\E\s{$entry_field_pos}(.*?))\s*\Q$mid_end\E$/)
		{
			# do not parse this line unless inside a matching header
			next unless ($header_match);
			$self->debug(1, "[$line_num] Entry continuation line type.\n");

			$self->debug(2, "Regex 1 = <$1>\n");
			$self->debug(2, "Regex 2 = <$2>\n");

			# save the end position of the last line
			$entry_prev_line_pos = $entry_line_pos;
			$entry_line_pos  = length $1;

			# save the field line and get the first word so we can determine
			# if the previous line has an embedded <cr>.
			$field_line = $2;
			$field_line =~ /^.*?(\S*)/;
			$first_word = $1;
			$self->debug(2, "First word = <$1>\n");

			# If the previous line did not wrap, 
			# then a <cr> was present on the previous line.
			if (length($first_word) + $entry_prev_line_pos < $header->{line_width})
			{
				$field .= "\n"; 
			}
			else
			{
				$field .= " ";
			}

			$field .= "$field_line";
			next;
		}

		# check for a keyless entry line
		if ($line =~ /^\Q$mid_start\E(\s*\S.*?)\s*?\Q$mid_end\E$/)
		{
			# do not parse this line unless inside a matching header
			next unless ($header_match);
			$self->debug(1, "[$line_num] Keyless entry line type.\n");

			$self->debug(2, "Regex 1 = <$1>\n");

			# add the previous entry
			if ($entry_match)
			{
				$self->debug(3, "Adding $key header entry !\n");
				$header->HeaderField($key, $field);
				$field = "";
			}

			# extract the first word of the entry and use it as an embedded key
			$field_line = $1;
			$field_line =~ /^.*?(\S*)/;
			$first_word = $1;
			$self->debug(2, "First word = <$1>\n");

            # check for existing embedded key of the same name
			my @keylist = $header->HeaderKeys();
            my $embedded_key_count = 0;
			foreach my $key (@keylist)
			{
                $self->debug(4, "Checking $key\n");

				# only check embedded keys
				next unless ($key =~ m/<(.*)_\d+>/);

                # check for a matching key name
                $self->debug(4, "Checking $key for $first_word\n");
                $embedded_key_count++ if ($first_word eq $1);
			}

			# add the entry
            $key = "$first_word" . "_$embedded_key_count";
			$self->debug(3, "Adding <$key> header entry !\n");
			$header->HeaderField("<$key>", $field_line);

			$entry_match = 0;
            $field = "";
			next;
		}
	}

	return @header_array; 
}

1;