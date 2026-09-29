#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaTarget.pm
# Description    : Perl module of CBA (Cellular Build Architecture)
#                  target functions
# 
# Notes          : 
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

package CbaTarget;

use strict;
use Exporter;
use vars qw(@ISA @EXPORT $VERSION);

use Cba;
use CbaClearCase;
use File::Basename;
use Time::localtime;

use ProjectSettings;

$VERSION  = 1.00;

@ISA    = qw(Exporter);
@EXPORT = qw(isTarget
             getTargetList
			 getTargetConfig
			 createTargetDirTree
			 createTargetMakeFiles
			 createTargetInterfaceFiles
             setCbaTargetDebug);

my $ibaPackDebug    = 0;
my $ibaPackDebugStr = "CbaTarget>";

sub setCbaTargetDebug
{ 
	$ibaPackDebug = $_[0]; 
	my $str = ($ibaPackDebug ? "Debugging on\n" : "Debugging off\n");
	CbaTargetDebug($str);
}

sub CbaTargetDebug { print "$ibaPackDebugStr @_" if $ibaPackDebug; }


# -----------------------------------------------------------------------------
# Function    : getTargetList
# Description : Finds a list of targets from a start directory
# Parms       : array - reference to an array to place results
#               root  - root directory to start search
# Returns     : none
# Notes       : Ignores the env directory. Returns a list of 
#               of basenames and target names in the
#               form : <base>/<target>
# -----------------------------------------------------------------------------
sub getTargetList
{
    # get the arguments
    my ($targetList, $root) = @_;

	# get a list of the possible elements
	my @elementList = getElementList($root);

	CbaTargetDebug("Elements: @elementList\n");

	# now check for the actual packages
	foreach my $entry (@elementList)
	{
		if (isTarget("$root/$entry"))
		{
			push @$targetList, File::Spec->canonpath($entry);
		}
	}
}

# -----------------------------------------------------------------------------
# Function    : isTarget
# Description : Check whether an element is a target
# Parms       : path - the path to the element to check
# Returns     : true or false
# Notes       : 
# -----------------------------------------------------------------------------
sub isTarget
{
	my ($path) = @_;
	return isElement("target", $path);
}

# -----------------------------------------------------------------------------
# Function    : getTargetConfig
# Description : Returns an array of hash entries containing 
#               target configuration parameters
# Parms       : path - path and name of the target
# Returns     : the array of configuration parameters
# Notes       : 
# -----------------------------------------------------------------------------
sub getTargetConfig
{
	use CbaConfigParm;

	my $path = $_[0];
	my $target = basename($path);
	my $config_file = File::Spec->canonpath("$path/inc/gbl_config.h");

	return undef unless (-f $config_file);

	CbaTargetDebug("Path = $path\n");
	CbaTargetDebug("Target = $target\n");
	CbaTargetDebug("Opening $config_file\n");

	# open the target configuration file
	open FH, "< $config_file" or die "Cannot open $config_file\n";
	my @config_file_array = <FH>;
	close FH;

	# parse the config file	
	my $cp = CbaConfigParm->new();
	my @config_array = $cp->Parse(\@config_file_array, "target");
	
	return @config_array;
}

# -----------------------------------------------------------------------------
# Function    : createTargetDirTree
# Description : Creates the directory tree for a target
# Parms       : dirArray - reference to the directory array
#               path     - path and name of the target to create
#               cc       - flag for creating ClearCase elements
#               branch   - if using ClearCase, the branch to create 
#                          the directory elements on
# Returns     : the directory tree array
# Notes       : The directory tree must be empty
# -----------------------------------------------------------------------------
sub createTargetDirTree
{
	my ($dirArray, $targetPath, $ccFlag, $lvcoFlag) = @_;

	# get the base directory
    my ($target, $targetBase) = fileparse($targetPath);

    push @$dirArray, $targetBase;
    push @$dirArray, $targetPath;
    push @$dirArray, $targetPath."/bin";
    push @$dirArray, $targetPath."/build";
    push @$dirArray, $targetPath."/obj";
    push @$dirArray, $targetPath."/inc";
    push @$dirArray, $targetPath."/src";
    push @$dirArray, $targetPath."/doc";

    # create the directories, if required
    foreach my $dir (@$dirArray)
    {
		$dir = File::Spec->canonpath($dir);
	
		# if using ClearCase, make the dirs in the VOB
		if ($ccFlag)
		{
	    	createDirElement($dir);
		}
		else
		{
			CbaTargetDebug("Creating $dir ...\n");
	    	mkdir($dir, 0777);
		}
    }
}

# -----------------------------------------------------------------------------
# Function    : createTargetMakeFiles
# Description : 
# Parms       : 
# Returns     : 
# Notes       : 
# -----------------------------------------------------------------------------
sub createTargetMakeFiles
{
	use CbaPackage;
	use CbaGroup;

	my ($memList, $host, $env, $platformVar, $templateDir, $targetPath, $ccFlag, $lvcoFlag, $targetBaseName) = @_;

	# get the target name, base, and root
	my ($target, $targetBase) = fileparse($targetPath);
	chop $targetBase;
	my ($base, $root) = fileparse($targetBase);

	# create the macros hash
	my %macros = ();
	$macros{'host'}      = $host;
	$macros{'env'}       = $env;
	$macros{'name'}      = $target;
	$macros{'base'}      = $targetBaseName;
	$macros{'packages'}  = "";
	$macros{'groups'}    = "";
	$macros{'platform'}    = $platformVar;

	# fill in the package and group list strings
	foreach my $mem (@$memList)
	{
		$mem =~ s/\\/\//;
		$macros{'packages'} .= "$mem "  if (isPackage("$root/$mem"));
		$macros{'groups'}   .= "$mem "   if (isGroup("$root/$mem"));
	}

	# create the make file
	my $file     = File::Spec->canonpath("$targetPath/build/$target.mak");
	my $template = File::Spec->canonpath("$templateDir/build/target.mak.tpl");

	if (! -e $file)
	{
		CbaTargetDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subTargetMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}

	# create the make dependency file
	$file     = File::Spec->canonpath("$targetPath/build/$target"."_dep.mak");
	$template = File::Spec->canonpath("$templateDir/build/target_dep.mak.tpl");

	if (! -e $file)
	{
		CbaTargetDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subTargetMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}

	# create the make batch file
	$file     = File::Spec->canonpath("$targetPath/build/make.bat");
	$template = File::Spec->canonpath("$templateDir/build/make.bat.tpl");

	if (! -e $file)
	{
		CbaTargetDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subTargetMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}

}


# -----------------------------------------------------------------------------
# Function    : createTargetInterfaceFiles
# Description : 
# Parms       : 
# Returns     : 
# Notes       : 
# -----------------------------------------------------------------------------
sub createTargetInterfaceFiles
{
    my ($memList, $host, $platformVar, $templateDir, $targetPath, $ccFlag, $lvcoFlag, $targetBaseName) = @_;

	# get the target name and base
	my ($target,$targetBase) = fileparse($targetPath);
	chop $targetBase;
    my ($base, $root) = fileparse($targetBase);

    # create the macros hash
	my %macros = ();
	$macros{'name'}      = $target;
	$macros{'base'}      = $targetBaseName;
    $macros{'host'}      = $host;
    $macros{'packages'}  = "";
    $macros{'groups'}    = "";
	$macros{'platform'}    = $platformVar;


	my ($file, $template);

 # fill in the package and group list strings
	foreach my $mem (@$memList)
	{
        $mem =~ m/(\w+)[\/\\](\w+)/;
        if (isPackage("$root/$1/$2")) {
            $macros{'packages'} .= "$2 ";
        }
        if (isGroup("$root/$1/$2")) {
            $macros{'groups'}   .= "$2 ";
        }
	}

    # create the HWPlatform ldf file
    $file     = File::Spec->canonpath("$targetPath/inc/$macros{'platform'}".".ldf");
    $template = File::Spec->canonpath("$templateDir/test/HWPlatform.ldf.tpl");

	if (! -e $file)
	{
		CbaTargetDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subTargetMaros($file, $template, \%macros);
        checkinElement($file) if (!$lvcoFlag);
    }

    # create the main ldf file
    $file     = File::Spec->canonpath("$targetPath/src/$target".".ldf");
    $template = File::Spec->canonpath("$templateDir/test/target_env.ldf.tpl");

    if (! -e $file)
	{
		CbaTargetDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subTargetMaros($file, $template, \%macros);
        checkinElement($file) if (!$lvcoFlag);
    }

	# create the global config file
	$file     = File::Spec->canonpath("$targetPath/inc/gbl_config.h");
	$template = File::Spec->canonpath("$templateDir/inc/gbl_config.h.tpl");

	if (! -e $file)
	{
		CbaTargetDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subTargetMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}

	# create the main entry file
	$file     = File::Spec->canonpath("$targetPath/src/UserMain.c");
	$template = File::Spec->canonpath("$templateDir/test/main.c.tpl");

	if (! -e $file)
	{
		CbaTargetDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subTargetMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}

	# create debugger script
	$file     = File::Spec->canonpath("$targetPath/inc/$target" . ".xdb");
	$template = File::Spec->canonpath("$templateDir/inc/StartUpScript.xdb.tpl");

	if (! -e $file)
	{
		CbaTargetDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subTargetMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}


}

# -----------------------------------------------------------------------------
# Function    : subTargetMaros
# Description : Substitutes macro placeholders in a file with values
# Parms       : $file     - 
#               $template - 
#               $macros   - 
# Returns     : 
# Notes       : 
# -----------------------------------------------------------------------------
sub subTargetMaros
{
	my ($file, $template, $macros) = @_;

	# get the year
	my $tm = localtime;
	my $year = $tm->year + 1900;
	my $date = $tm->mday;
	my $month = ("Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec")[$tm->mon];

	my $filename = basename($file);

	# open the destination and template file
	open FILE, ">"."$file" 
	or die "Error: Cannot open $file.\n";
	    
	open TEMPLATE_FILE, "<"."$template" 
	or die "Error: Cannot open $template.\n"; 

	# read the contents of the template file	    
	my @buffer = <TEMPLATE_FILE>;

	# Get project-specific settings
	my $ProjSet ={};
	GetProjectSettings( $macros->{'platform'}, \$ProjSet );
	    
	# read the lines of the template file and replace the 
	# key words with the specific file information.
	foreach my $line (@buffer)
	{	
		# Fill in the file name and year into the file headers
		$line =~ s/\^FILE/$filename/g;
        $line =~ s/\^DATE/$month $date, $year/g;
        $line =~ s/\^YEAR/$year/g;
		$line =~ s/\^PROGRAMMER/$ENV{USERNAME}/g;
		$line =~ s/\^MODULE_TYPE/target/g;
		$line =~ s/\^TARGET_TYPE/target/g;
		if ( exists $macros->{'name'} ) { 
		  $line =~ s/\^TARGET_\^ENV/$macros->{'name'}/g;
		}

		# Fill in the base, Base, or BASE name.
		if ( exists $macros->{'base'} )
		{
			$line =~ s/\^TARGET_BASE/$macros->{'base'}/g;
			$line =~ s/\^UP_TARGET_BASE/\U$macros->{'base'}/g;
			$line =~ s/\^CAP_TARGET_BASE/\u$macros->{'base'}/g;
			$line =~ s/\^MODULE_BASE/$macros->{'base'}/g;
			$line =~ s/\^UP_MODULE_BASE/\U$macros->{'base'}/g;
			$line =~ s/\^CAP_MODULE_BASE/\u$macros->{'base'}/g;
		}

		# fill in the group list
		if ( (exists $macros->{'groups'}) && ($line =~ m/^(.*)\^GROUP_LIST\((.*)\)(.*)$/ ) ) {
		  my $start = $1;
		  my $pattern = $2;
		  my $end = $3;
		  my $npattern = "";
		  $line = "";
		  foreach my $el ( split(/\s+/, $macros->{'groups'}) ) {
			$npattern = $pattern;
			$npattern =~ s/CAP_LIST_ELEMENT/\u$el/;
			$npattern =~ s/UP_LIST_ELEMENT/\U$el/;
			$npattern =~ s/LIST_ELEMENT/$el/;
			$line = "$line" . "$start" . "$npattern" . "$end\n";
		  }
		}
		else {
		  $line =~ s/\^GROUP_LIST\(.*\)//;
		}
		
		# fill in the package list
		if ( (exists $macros->{'packages'}) && ( $line =~ m/^(.*)\^PACKAGE_LIST\((.*)\)(.*)$/ ) ) {
		  my $start = $1;
		  my $pattern = $2;
		  my $end = $3;
		  my $npattern = "";
		  $line = "";
		  foreach my $el ( split(/\s+/, $macros->{'packages'}) ) {
			$npattern = $pattern;
			$npattern =~ s/CAP_LIST_ELEMENT/\u$el/;
			$npattern =~ s/UP_LIST_ELEMENT/\U$el/;
			$npattern =~ s/LIST_ELEMENT/$el/;
			$line = "$line" . "$start" . "$npattern" . "$end\n";
		  }
		}
		else {
		  $line =~ s/\^PACKAGE_LIST\(.*\)//;
		}

		# Fill in the target, Target, or TARGET name.
		if ( exists $macros->{'name'} )
		{
			$line =~ s/\^TARGET_DIR/$macros->{'name'}/g;
			$line =~ s/\^TARGET/$macros->{'name'}/g;
			$line =~ s/\^UP_TARGET/\U$macros->{'name'}/g;
			$line =~ s/\^CAP_TARGET/\u$macros->{'name'}/g;
			$line =~ s/\^MODULE/$macros->{'name'}/g;
			$line =~ s/\^UP_MODULE/\U$macros->{'name'}/g;
			$line =~ s/\^CAP_MODULE/\u$macros->{'name'}/g;
		}
		
		# Fill in the interface, Interface, or INTERFACE name.
		if ( exists $macros->{'interface'} )
		{
			$line =~ s/\^INTERFACE/$macros->{'interface'}/g;
			$line =~ s/\^UP_INTERFACE/\U$macros->{'interface'}/g;
			$line =~ s/\^CAP_INTERFACE/\u$macros->{'interface'}/g;
		}
		
		# Fill in the env, Env, or ENV name.
		if ( exists $macros->{'env'} )
		{
			$line =~ s/\^ENV/$macros->{'env'}/g;
			$line =~ s/\^UP_ENV/\U$macros->{'env'}/g;
			$line =~ s/\^CAP_ENV/\u$macros->{'env'}/g;
		}

		# Fill in the HW platform name.
		$line =~ s/\^HW_PLATFORM/$macros->{'platform'}/g;
		$line =~ s/\^UP_HW_PLATFORM/\U$macros->{'platform'}/g;
		$line =~ s/\^CAP_HW_PLATFORM/\u$macros->{'platform'}/g;
		
		# Fill in project settings
		if ( exists $ProjSet->{VOBName}  ) {
		  $line =~ s/\^PROJECT_INC_DIR/\$(BUILD_ROOT)\/$ProjSet->{VOBName}\/$ProjSet->{MainIncDir}/g;
		}
		else {
		  $line =~ s/\^PROJECT_INC_DIR//g;
		}
		
		# Fill in the host, Host, HOST name.
		if ( exists $macros->{'host'} )
		{
			$line =~ s/\^HOST/$macros->{'host'}/g;
			$line =~ s/\^UP_HOST/\U$macros->{'host'}/g;
			$line =~ s/\^CAP_HOST/\u$macros->{'host'}/g;
		}

		# fill in the package list
		if ( exists $macros->{'packages'} )
		{
		  my $subst = "";
		  foreach my $el ( split(/\s+/, $macros->{'packages'}) ) {
			$subst = "$subst" . "\\\n                   $el";
		  }
			$line =~ s/\^PACKAGE_LIST/$subst\n/g;
		}
		else {
		  $line =~ s/\^PACKAGE_LIST//g;
		}

		# fill in the group list
		if ( exists $macros->{'groups'} )
		{
		  my $subst = "";
		  foreach my $el ( split(/\s+/, $macros->{'groups'}) ) {
			$subst = "$subst" . "\\\n                   $el";
		  }
			$line =~ s/\^GROUP_LIST/$subst\n/g;
		}
		else {
		  $line =~ s/\^GROUP_LIST//g;
		}

		print FILE "$line"; 
	}

    close FILE;
    close TEMPLATE_FILE;

}

1;
