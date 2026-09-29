#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaConfigParm.pm
# Description    : Perl module of the package/group configuration object
#                  for the CBA (Cellular Build Architecture)
# 
# Notes          : 
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

package CbaConfigParm;

use CbaHeader;
use overload     q("") => \&ConfigParm;

my $CbaConfigParmDebugStr = "CbaConfigParm>";
my $CbaConfigParmDebugLevel = 0;

sub CbaConfigParmDebug
{
	my ($level, $str) = @_;
	print "$CbaConfigParmDebugStr $str" if ($level <= $CbaConfigParmDebugLevel);
}

sub setCbaConfigParmDebug
{
	$CbaConfigParmDebugLevel = $_[0]; 
	my $str = ($CbaConfigParmDebugLevel ? "Debugging on\n" : "Debugging off\n");
	CbaConfigParmDebug($CbaConfigParmDebugLevel, $str) if ($_[0]);
}


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
		element_type => "package",
		element_name => "<package>",
		name => "<name>",
		value => "<value>",
		header => CbaHeader->new(),
		line_num => 0,
		@_,
	};
	bless($self, $class);

	# Initialize the header
	$self->{header}->HeaderField("Parameter",$self->{name});
	$self->{header}->HeaderField("Description","Add configuration parameter description here.");
	$self->{header}->HeaderField("Notes","Add configuration parameter notes here.");

	return $self;
}

# -----------------------------------------------------------------------------
# Function    : Name
# Description : Sets the name of the config parameter
# Parms       : name - string containing the name
# Returns     : name
# Notes       : Can be case insensitive
# -----------------------------------------------------------------------------
sub Name
{
	my $self = shift;
	if (@_) 
	{ 
		$self->{name} = shift;
		$self->{header}->HeaderField("Parameter", $self->{name});
	}

	return $self->{name};
}

# -----------------------------------------------------------------------------
# Function    : Type
# Description : Sets the type of the config parameter
# Parms       : type - string containing the type [package, group, global]
# Returns     : type
# Notes       : 
# -----------------------------------------------------------------------------
sub Type
{
	my $self = shift;
	if (@_) { $self->{element_type} = shift; }
	return $self->{element_type};
}

# -----------------------------------------------------------------------------
# Function    : PackageName
# Description : Sets the name of the package and sets the element type
# Parms       : name - string containing the name of the package
# Returns     : name or undef
# Notes       : If the config element is not a package the function
#               returns undef.
# -----------------------------------------------------------------------------
sub PackageName
{
	my $self = shift;
	
	if (@_) 
	{ 
		$self->Name(shift);
		$self->{element_type} = "package";
	}
	
	return $self->Name() if ( $self->{element_type} eq "package" );
	return undef;
}

# -----------------------------------------------------------------------------
# Function    : GroupName
# Description : Sets the name of the group and sets the element type
# Parms       : name - string containing the name of the group
# Returns     : name or undef
# Notes       : If the config element is not a group the function
#               returns undef.
# -----------------------------------------------------------------------------
sub GroupName
{
	my $self = shift;
	
	if (@_) 
	{ 
		$self->Name(shift);
		$self->{element_type} = "group";
	}
	
	return $self->Name() if ( $self->{element_type} eq "group" );
	return undef;
}

# -----------------------------------------------------------------------------
# Function    : GlobalName
# Description : Sets the name of the global parmaeter and sets the element type
# Parms       : name - string containing the name of the global element
# Returns     : name or undef
# Notes       : If the config element is not a global the function
#               returns undef.
# -----------------------------------------------------------------------------
sub GlobalName
{
	my $self = shift;
	
	if (@_) 
	{ 
		$self->Name(shift);
		$self->{element_type} = "global";
	}
	
	return $self->Name() if ( $self->{element_type} eq "global" );
	return undef;
}

# -----------------------------------------------------------------------------
# Function    : Description
# Description : Sets the description field for the auto-generated header
# Parms       : desc - string containing the parameter description text
# Returns     : desc
# Notes       : The description text can be an unformatted string
# -----------------------------------------------------------------------------
sub Description
{
	my $self = shift;
	if (@_) { $self->{header}->HeaderField("Description", shift); }
	return $self->{header}->HeaderField("Description");
}

# -----------------------------------------------------------------------------
# Function    : Notes
# Description : Sets the notes field for the auto-generated header
# Parms       : notes - string containing the parameter notes text
# Returns     : notes
# Notes       : The notes text can be an unformatted string
# -----------------------------------------------------------------------------
sub Notes
{
	my $self = shift;
	if (@_) { $self->{header}->HeaderField("Notes", shift); }
	return $self->{header}->HeaderField("Notes");
}

# -----------------------------------------------------------------------------
# Function    : Header
# Description : Sets the entire header for the configuration parameter
# Parms       : header - header object
# Returns     : header
# Notes       : 
# -----------------------------------------------------------------------------
sub Header
{
	my $self = shift;
	if (@_) 
	{ 
		$self->{header} = shift; 
	}
	return $self->{header};
}

# -----------------------------------------------------------------------------
# Function    : Value
# Description : Sets the value of the parameter
# Parms       : value - the parameter value
# Returns     : value
# Notes       : 
# -----------------------------------------------------------------------------
sub Value
{
	my $self = shift;
	if (@_) { $self->{value} = shift; }
	return $self->{value};
}

# -----------------------------------------------------------------------------
# Function    : Max
# Description : Sets the maximum value of the parameter
# Parms       : value - the maximum value
# Returns     : max
# Notes       : 
# -----------------------------------------------------------------------------
sub Max
{
	my $self = shift;
	if (@_) 
	{ 
		$self->{max} = shift;
		$self->{updated} = 1;
	}
	return $self->{max};
}

# -----------------------------------------------------------------------------
# Function    : Min
# Description : Sets the minimum value of the parameter
# Parms       : value - the minimum value
# Returns     : min
# Notes       : 
# -----------------------------------------------------------------------------
sub Min
{
	my $self = shift;
	if (@_) 
	{ 
		$self->{min} = shift; 
	}
	return $self->{min};
}

# -----------------------------------------------------------------------------
# Function    : MinMaxUpdated
# Description : The min or max values have been updated
# Parms       : value - the minimum value
# Returns     : min
# Notes       : 
# -----------------------------------------------------------------------------
sub MinMaxUpdated
{
	my $self = shift;
	$self->{updated} = 1;
}

# -----------------------------------------------------------------------------
# Function    : Step
# Description : Sets the step value of the parameter
# Parms       : value - the step value
# Returns     : step
# Notes       : 
# -----------------------------------------------------------------------------
sub Step
{
	my $self = shift;
	if (@_) { $self->{step} = shift; }
	return $self->{step};
}

# -----------------------------------------------------------------------------
# Function    : ConfigParm
# Description : returns the configuration parameter
# Parms       : 
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub ConfigParm
{
	my $self = shift;
	my $output;

	# get the header
	$output = $self->{header}->Header();

	# output the configuration parameter
	my $prefix = "$self->{element_name}_"."$self->{name}";
	$prefix =~ s/$prefix/\U$prefix/;

	# if the parameter is a target parameter
	# surround with #ifdef statements
	if ($self->{element_type} eq "global")
	{
		$output .= "#ifdef  $prefix\n";
		$output .= "#undef  $prefix\n";
	}

	$output .= "#define $prefix"."       "."$self->{value}\n";

	if (($self->{element_type} eq "package") || $self->{updated})
	{
		$output .= "#define $prefix"."_MIN   "."$self->{min}\n"  if (exists $self->{min});
	}

	if ($self->{element_type} eq "package")
	{
		$output .= "#define $prefix"."_STEP  "."$self->{step}\n" if (exists $self->{step});
	}

	if (($self->{element_type} eq "package") || $self->{updated})
	{
		$output .= "#define $prefix"."_MAX   "."$self->{max}\n"  if (exists $self->{max});
	}

	if ($self->{element_type} eq "global")
	{
		$output .= "#endif  /* $prefix */\n";
	}

	return $output;
}

# -----------------------------------------------------------------------------
# Function    : ConfigParmGuard
# Description : returns the configuration parameter compile guard
# Parms       : none
# Returns     : string containing the compile guard for the parameter
# Notes       : This function should only be used for packages
# -----------------------------------------------------------------------------
sub ConfigParmGuard
{
	my $self = shift;
	my $output;

	# setup the common string information
	my $parm = "$self->{element_name}_"."$self->{name}";
	$parm =~ s/$parm/\U$parm/;

	# get the element type
	my $element = $self->{element_type};
	$element =~ s/$element/\u$element/;

	$output  = "/* Check the $parm Parameter Range */\n";
	$output .= "#if ($parm < $parm"."_MIN)||\n";
	$output .= "    ($parm > $parm"."_MAX)\n";
	$output .= "#error \"$element $parm parameter out of range\"\n";
	$output .= "#endif\n";

	return $output;
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

	print $fh $self->ConfigParm();
}


# -----------------------------------------------------------------------------
# Function    : Parse
# Description : parses an array for the config parm info
# Parms       : array ref - the array to parse
# Returns     : array of config parm objects
# Notes       : 
# -----------------------------------------------------------------------------
sub Parse
{
	my ($self, $array, $element_type) = @_;

	my @header_array = ();		# all the config headers in the array
	my $header_name = "";

	my $cparm;					# the current config parameter object
	my @cparm_array = ();		# all the config parms in the array
	my $cparm_count = 0;		# the config parameters parsed so far
	my $cparm_match = 0;		# whether a matching config parm is being parsed

	my $line_num = 0;			# the current array line number
	my $parm_name = "";

	# get the array of headers
	@header_array = $self->{header}->Parse($array);

	# extract the config parms from the array
	foreach my $line (@$array)
	{
		# we need the line number so we can save the starting line of each header
		$line_num++;
		CbaConfigParmDebug(3, "[Line $line_num] $line");

		# extract the parameter's min value
		if ($line =~ /^\s*#define\s+([^_].*?)_(.*?)_MIN\s+(.+)$/)
		{
			CbaConfigParmDebug(4, "Minimum line found!\n");
			CbaConfigParmDebug(5, "Arg[1] = $1\n");
			CbaConfigParmDebug(5, "Arg[2] = $2\n");
			CbaConfigParmDebug(5, "Arg[3] = $3\n");
			$cparm->{min} = $3;
			next;
		}

		# extract the parameter's max value
		if ($line =~ /^\s*#define\s+([^_].*?)_(.*?)_MAX\s+(.+)$/)
		{
			CbaConfigParmDebug(4, "Maximum line found!\n");
			CbaConfigParmDebug(5, "Arg[1] = $1\n");
			CbaConfigParmDebug(5, "Arg[2] = $2\n");
			CbaConfigParmDebug(5, "Arg[3] = $3\n");
			$cparm->{max} = $3;
			next;
		}

		# extract the parameter's step value
		if ($line =~ /^\s*#define\s+([^_].*?)_(.*?)_STEP\s+(.+)$/)
		{
			CbaConfigParmDebug(4, "Step line found!\n");
			CbaConfigParmDebug(5, "Arg[1] = $1\n");
			CbaConfigParmDebug(5, "Arg[2] = $2\n");
			CbaConfigParmDebug(5, "Arg[3] = $3\n");
			$cparm->{step} = $3;
			next;
		}

		# extract the parameter's value
		if ($line =~ /^\s*#define\s+([^_].*?)_(.*?)\s+(.+)$/)
		{
			CbaConfigParmDebug(4, "Parameter line found!\n");
			CbaConfigParmDebug(5, "Arg[1] = $1\n");
			CbaConfigParmDebug(5, "Arg[2] = $2\n");
			CbaConfigParmDebug(5, "Arg[3] = $3\n");

			# save the previous config parameter
			if (($parm_name ne $2) && $cparm)
			{
				CbaConfigParmDebug(1, "Saving previous cparm object!\n");
				CbaConfigParmDebug(2, "Element Type    = $element_type\n");
				CbaConfigParmDebug(2, "Element name    = $cparm->{element_name}\n");
				CbaConfigParmDebug(2, "Parameter name  = $cparm->{name}\n");
				CbaConfigParmDebug(2, "Parameter value = $cparm->{value}\n");
				CbaConfigParmDebug(2, "Parameter min   = $cparm->{min}\n")  if (exists $cparm->{min});
				CbaConfigParmDebug(2, "Parameter step  = $cparm->{step}\n") if (exists $cparm->{step});
				CbaConfigParmDebug(2, "Parameter max   = $cparm->{max}\n")  if (exists $cparm->{max});
				push @cparm_array, $cparm;
			}

			# create the new config element
			CbaConfigParmDebug(1, "Creating new cparm object!\n");
			$cparm = CbaConfigParm->new();
			$cparm->{line_num} = $line_num;
			$cparm->{element_type} = $element_type;
			$cparm->{element_name} = "\L$1";
			$cparm->Name("\L$2");
			$cparm->{value} = $3;
			$parm_name = $2;
			next;
		}
	}

	# save the last parameter
	if ($cparm)
	{
		CbaConfigParmDebug(1, "Saving previous cparm object!\n");
		CbaConfigParmDebug(2, "Element Type    = $element_type\n");
		CbaConfigParmDebug(2, "Element name    = $cparm->{element_name}\n");
		CbaConfigParmDebug(2, "Parameter name  = $cparm->{name}\n");
		CbaConfigParmDebug(2, "Parameter value = $cparm->{value}\n");
		CbaConfigParmDebug(2, "Parameter min   = $cparm->{min}\n")  if (exists $cparm->{min});
		CbaConfigParmDebug(2, "Parameter step  = $cparm->{step}\n") if (exists $cparm->{step});
		CbaConfigParmDebug(2, "Parameter max   = $cparm->{max}\n")  if (exists $cparm->{max});
		push @cparm_array, $cparm;
	}

	# match the headers to the parameters
	foreach $cparm (@cparm_array)
	{
		# compare the names of the headers
		# with the names of the config parameters
		foreach my $header (@header_array)
		{
			$parm_name = $cparm->Name();
			$header_name = $header->HeaderField("Parameter");

			if ($parm_name eq $header_name)
			{
				$cparm->{header} = $header;
				last;
			}
		}
	}

	return @cparm_array;
}

1;