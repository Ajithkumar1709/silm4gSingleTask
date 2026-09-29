#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaGroup.pm
# Description    : Perl module of CBA group functions
# 
# Notes          : 
# 
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

package CbaGroup;

use strict;
use Exporter;
use vars qw(@ISA @EXPORT $VERSION);

use Cba;
use CbaClearCase;
use CbaPackage;

use ProjectSettings;

$VERSION  = 1.00;

@ISA    = qw(Exporter);
@EXPORT = qw(isGroup
             getGroupList
             getGroupInterfaceList
             createGroupDirTree
             createGroupMakeFiles
             createGroupInterfaceFiles
             createGroupTestEnvFiles
             setCbaGroupDebug);

my $ibaGroupDebugFlag = 0;
my $ibaGroupDebugStr = "CbaGroup>";

sub setCbaGroupDebug
{ 
	$ibaGroupDebugFlag = $_[0]; 
	my $str = ($ibaGroupDebugFlag ? "Debugging on\n" : "Debugging off\n");
	CbaGroupDebug($str);
}
sub CbaGroupDebug { print "$ibaGroupDebugStr @_" if $ibaGroupDebugFlag; }

# -----------------------------------------------------------------------------
# Function    : getGroupList
# Description : Finds a list of groups from a start directory
# Parms       : groupList - the array to fill with group names
#               root     - root directory to start search
# Returns     : none
# Notes       : Ignores the env directory. Returns a list of 
#               of basenames and group names in the
#               form : <base>/<group>
# -----------------------------------------------------------------------------
sub getGroupList
{
    # get the arguments
    my ($groupList, $root) = @_;

	# get a list of the possible elements
	my @elementList = getElementList($root);

	CbaGroupDebug("Elements: @elementList\n");

	# now check for the actual packages
	foreach my $entry (@elementList)
	{
		if (isGroup("$root/$entry"))
		{
			push @$groupList, File::Spec->canonpath($entry);
		}
	}
}

# -----------------------------------------------------------------------------
# Function    : isGroup
# Description : Check whether a element is a group
# Parms       : path - the path to the element to check
# Returns     : true or false
# Notes       : 
# -----------------------------------------------------------------------------
sub isGroup
{
	my ($path) = @_;
	return isElement("group", $path);
}

# -----------------------------------------------------------------------------
# Function    : getGroupInterfaceList
# Description : Returns an array of group interface names
# Parms       : interfaceList - reference to an hash array to place results
#               group       - path to a group
# Returns     : none
# Notes       : The interface hash array is in the following format:
#
#               interface[n]{'name'} => <interface name>
#               interface[n]{'file'} => <interface file contents>
#
# -----------------------------------------------------------------------------
sub getGroupInterfaceList
{
	use File::Basename;

    # get the arguments
    my ($interfaceList, $group) = @_;
	my $packName = basename($group);
	my $interface;

	# clean up the directory
	my $interface_dir = File::Spec->canonpath($group."/inc");
	$interface_dir =~ s/\\\\/\\/;
	$interface_dir =~ s/\/\//\//;

	CbaGroupDebug("Checking $interface_dir\n");

	# open the inc directory of the group
	opendir(INC_DIR, $interface_dir) or return;

	# get the group interface files
	while ( defined ($interface = readdir INC_DIR) )
	{
		CbaGroupDebug("Checking $interface\n");

		# skip unless the entry is a directory
		next if ( -d $interface );

		# extract the interface names
		$interface =~ /^($packName)_([\w]+)\.h/;

		push @$interfaceList, $2;
	}

	closedir INC_DIR;
}

# -----------------------------------------------------------------------------
# Function    : getGroupInterface
# Description : Returns an hash of aray entries 
# Parms       : interfaceList - reference to an array to place results
#               group       - path to a group
# Returns     : none
# Notes       : The interface names are only the interface names
# -----------------------------------------------------------------------------
sub getGroupInterface
{
	print "getGroupInterface() is under construction\n";
}

# -----------------------------------------------------------------------------
# Function    : getGroupConfig
# Description : Returns an array of hash entries containing 
#               group configuration parameters
# Parms       : path - path and name of the group
# Returns     : the array of configuration parameters
# Notes       : 
# -----------------------------------------------------------------------------
sub getGroupConfig
{
	use CbaConfigParm;

	my $path = $_[0];
	my $group = basename($path);
	my $config_file = File::Spec->canonpath("$path/inc/$group"."_config.h");

	return undef unless (-f $config_file);

	CbaGroupDebug("Path = $path\n");
	CbaGroupDebug("Group = $group\n");
	CbaGroupDebug("Opening $config_file\n");

	# open the group configuration file
	open FH, "< $config_file" or die "Cannot open $config_file\n";
	my @config_file_array = <FH>;
	close FH;

	# parse the config file	
	my $cp = CbaConfigParm->new();
	my @config_array = $cp->Parse(\@config_file_array, "group");
	
	return @config_array;
}

# -----------------------------------------------------------------------------
# Function    : createGroupDirTree
# Description : Creates the directory tree for a group
# Parms       : dirArray - reference to the directory array
#               path     - path and name of the group to create
#               cc       - flag for creating ClearCase elements
#               branch   - if using ClearCase, the branch to create 
#                          the directory elements on
# Returns     : the directory tree array
# Notes       : The directory tree must be empty
# -----------------------------------------------------------------------------
sub createGroupDirTree
{
	my ($dirArray, $groupPath, $ccFlag, $lvcoFlag) = @_;

	# get the base directory
    my ($group, $groupBase) = fileparse($groupPath);

    push @$dirArray, $groupBase;
    push @$dirArray, $groupPath;
    push @$dirArray, $groupPath."/build";
    push @$dirArray, $groupPath."/inc";
    push @$dirArray, $groupPath."/src";
    push @$dirArray, $groupPath."/doc";
    push @$dirArray, $groupPath."/test";
    push @$dirArray, $groupPath."/test/bin";
    push @$dirArray, $groupPath."/test/build";
    push @$dirArray, $groupPath."/test/src";
    push @$dirArray, $groupPath."/test/inc";
    push @$dirArray, $groupPath."/test/obj";

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
			CbaGroupDebug("Creating $dir ...\n");
	    	mkdir($dir, 0777);
		}
    }
}

# -----------------------------------------------------------------------------
# Function    : createGroupMakeFiles
# Description : 
# Parms       : 
# Returns     : 
# Notes       : 
# -----------------------------------------------------------------------------
sub createGroupMakeFiles
{
	my ($srcList, $platformVar, $memList, $templateDir, $groupPath, $ccFlag, $lvcoFlag) = @_;	

	# get the group name and base
	my ($group, $groupBase) = fileparse($groupPath);
	chop $groupBase;
	my ($base, $root) = fileparse($groupBase);


	# create the macros hash
	my %macros = ();
	$macros{'name'}      = $group;
	$macros{'base'}      = $base;
    $macros{'src'}       = "";
	$macros{'packages'}  = "";
	$macros{'groups'}    = "";
	$macros{'platform'}  = $platformVar;

	# fill in the package and group list strings
	foreach my $mem (@$memList)
	{
		$mem =~ s/\\/\//;
		$macros{'packages'} .= "$mem "  if (isPackage("$root/$mem"));
		$macros{'groups'}   .= "$mem "   if (isGroup("$root/$mem"));
	}

	# fill in the source file string
	foreach my $src (@$srcList)
	{
		$macros{'src'} .= " \\\n                   $src";
	}

	# create the make file
	my $file     = File::Spec->canonpath("$groupPath/build/$group.mak");
	my $template = File::Spec->canonpath("$templateDir/build/group.mak.tpl");

	if (! -e $file)
	{
		CbaGroupDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subGroupMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}

	# create the make dependency file
	$file     = File::Spec->canonpath("$groupPath/build/$group"."_dep.mak");
	$template = File::Spec->canonpath("$templateDir/build/group_dep.mak.tpl");

	if (! -e $file)
	{
		CbaGroupDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subGroupMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}
}

# -----------------------------------------------------------------------------
# Function    : createGroupInterfaceFiles
# Description : 
# Parms       : 
# Returns     : 
# Notes       : 
# -----------------------------------------------------------------------------
sub createGroupInterfaceFiles
{
    my ($ifArray, $memList, $templateDir, $groupPath, $ccFlag, $lvcoFlag) = @_;   

	# get the group name and base
	my ($group,$groupBase) = fileparse($groupPath);
	chop $groupBase;
    my ($base, $root) = fileparse($groupBase);

    # create the macros hash
	my %macros = ();
	$macros{'name'}      = $group;
	$macros{'base'}      = $base;
    $macros{'src'}       = "";
	$macros{'packages'}  = "";
	$macros{'groups'}    = "";

	my ($file, $template);
	my @srcList = ();
    my $promotedIf;

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

   # create the ldf file
        $file     = File::Spec->canonpath("$groupPath/inc/$group".".ldf");
        $template = File::Spec->canonpath("$templateDir/inc/group.ldf.tpl");

        # get the template file
        if (! -e $template)
        {
                $template = File::Spec->canonpath("$templateDir/inc/group.ldf.tpl");
        }

        if (! -e $file)
        {
            CbaGroupDebug("Creating $file\n");
		    createFileElement($file) if ($ccFlag);
			subGroupMaros($file, $template, \%macros);
            checkinElement($file) if (!$lvcoFlag);
        }



    # loop through the interface files
	foreach my $if (@$ifArray)
	{
		# skip any removed interfaces
		next if ($if eq "");

		$macros{'interface'} = "$if";

        # check for an "header-only" interface. i.e. "*interface" 
        if ($if =~ /^\*/)
        {
            $promotedIf = 1;            
            $template = File::Spec->canonpath("$templateDir/inc/group_promote.h.tpl");

            # strip the '*' character
            $if =~ s/^\*//;

			$macros{'interface'} = "$if";
        }
        else
        {
		  if ( $if =~ m/^API$/ ) { $if = ""; }
		  else { $if = "_$if"; }

		  $promotedIf = 0;
		  $template = File::Spec->canonpath("$templateDir/inc/group$if.h.tpl");
        }

		# create the include file
		$file     = File::Spec->canonpath("$groupPath/inc/$group"."$if".".h");

		# get the template file
		if (! -e $template)
		{
			$template = File::Spec->canonpath("$templateDir/inc/group_if.h.tpl");
		}

		if (! -e $file)
		{
			CbaGroupDebug("Creating $file\n");
		    createFileElement($file) if ($ccFlag);
			subGroupMaros($file, $template, \%macros);
	    	checkinElement($file) if (!$lvcoFlag);
		}

		# create the source file
		$file     = File::Spec->canonpath("$groupPath/src/$group"."$if".".c");
		$template = File::Spec->canonpath("$templateDir/src/group$if.c.tpl");

		# get the template file
		if (! -e $template)
		{
			$template = File::Spec->canonpath("$templateDir/src/group_if.c.tpl");
		}
		
		
		# hack -- do not create a source file for the following
		# interface names
        next if ($promotedIf);
		next if ($if eq "_types");
		next if ($if eq "_config");

		# add the file to the source list
		push @srcList, basename($file);

		if (! -e $file)
		{
			CbaGroupDebug("Creating $file\n");
		    createFileElement($file) if ($ccFlag);
			subGroupMaros($file, $template, \%macros);
	    	checkinElement($file) if (!$lvcoFlag);
		}
	}

	return @srcList;
}

# -----------------------------------------------------------------------------
# Function    : createGroupTestEnvFiles
# Description : 
# Parms       : 
# Returns     : 
# Notes       : 
# -----------------------------------------------------------------------------
sub createGroupTestEnvFiles
{
	my ($envArray, $platformVar, $templateDir, $groupPath, $ccFlag, $lvcoFlag) = @_;

	# get the group name and base
	my ($group,$groupBase) = fileparse($groupPath);
	chop $groupBase;
	my $base = basename($groupBase);

	# create the macros hash
	my %macros = ();
	$macros{'name'}      = $group;
	$macros{'base'}      = $base;
	$macros{'host'}      = "win32";
	$macros{'groups'}    = $group;
	$macros{'platform'}  = $platformVar;

	my ($file, $template);

	# loop through the test enviroments
	foreach my $env (@$envArray)
	{
		# skip any removed environments
	  print "[$env]\n";
		next if ($env eq "");

		$macros{'env'} = "$env";

		# create the make file
		$file     = File::Spec->canonpath("$groupPath/test/build/$group"."_$env".".mak");
		$template = File::Spec->canonpath("$templateDir/test/group_env.mak.tpl");

		if (! -e $file)
		{
			CbaGroupDebug("Creating $file\n");
		    createFileElement($file) if ($ccFlag);
			subGroupMaros($file, $template, \%macros);
	    	checkinElement($file) if (!$lvcoFlag);
		}
	}

    # create the ldf file
    $file     = File::Spec->canonpath("$groupPath/test/src/$group"."_msa.ldf");
    $template = File::Spec->canonpath("$templateDir/test/target_env.ldf.tpl");

    if (! -e $file)
	{
		CbaGroupDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subGroupMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
    }

	# create the global config file
	$file     = File::Spec->canonpath("$groupPath/test/inc/gbl_config.h");
	$template = File::Spec->canonpath("$templateDir/inc/gbl_config.h.tpl");

	if (! -e $file)
	{
		CbaGroupDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subGroupMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}

	# create the main test file
	$file     = File::Spec->canonpath("$groupPath/test/src/UserMain.c");
	$template = File::Spec->canonpath("$templateDir/test/main.c.tpl");

	if (! -e $file)
	{
  	   CbaGroupDebug("Creating $file\n");
	   createFileElement($file) if ($ccFlag);
	   subGroupMaros($file, $template, \%macros);
	   checkinElement($file) if (!$lvcoFlag);
	}
	# create the make batch file
	$file     = File::Spec->canonpath("$groupPath/test/build/make.bat");
	$template = File::Spec->canonpath("$templateDir/build/make.bat.tpl");

	if (! -e $file)
	{
		CbaGroupDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subGroupMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}

	# create debugger script
	$file     = File::Spec->canonpath("$groupPath/test/inc/$group" . ".xdb");
	$template = File::Spec->canonpath("$templateDir/inc/StartUpScript.xdb.tpl");

	if (! -e $file)
	{
		CbaGroupDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subGroupMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}

}

# -----------------------------------------------------------------------------
# Function    : subGroupMarcos
# Description : Replaces the Group macros in a group template file
# Parms       : file     - the output file
#               template - the template file to use
#               macros   - hash with macro replacement values
# Returns     : none
# Notes       : 
# -----------------------------------------------------------------------------
sub subGroupMaros
{
    use Time::localtime;

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
		$line =~ s/\^MODULE_TYPE/group/g;
		$line =~ s/\^TARGET_TYPE/test-target/g;

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

		# fill in the source file list
		if ( exists $macros->{'src'} )
		{
			$line =~ s/\^SRC_FILE_LIST/$macros->{'src'}/g;
		}

		# Fill in the base, Base, or BASE name.
		if ( exists $macros->{'base'} )
		{
			$line =~ s/\^GROUP_BASE/$macros->{'base'}/g;
			$line =~ s/\^UP_GROUP_BASE/\U$macros->{'base'}/g;
			$line =~ s/\^CAP_GROUP_BASE/\u$macros->{'base'}/g;
			$line =~ s/\^TARGET_BASE/$macros->{'base'}/g;
			$line =~ s/\^UP_TARGET_BASE/\U$macros->{'base'}/g;
			$line =~ s/\^CAP_TARGET_BASE/\u$macros->{'base'}/g;
			$line =~ s/\^MODULE_BASE/$macros->{'base'}/g;
			$line =~ s/\^UP_MODULE_BASE/\U$macros->{'base'}/g;
			$line =~ s/\^CAP_MODULE_BASE/\u$macros->{'base'}/g;
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
		
		# Fill in the env, Env, or ENV name.
		if ( exists $macros->{'env'} )
		{
			$line =~ s/\^ENV/$macros->{'env'}/g;
			$line =~ s/\^UP_ENV/\U$macros->{'env'}/g;
			$line =~ s/\^CAP_ENV/\u$macros->{'env'}/g;
		}

		# Fill in the host, Host, HOST name.
		if ( exists $macros->{'host'} )
		{
			$line =~ s/\^HOST/$macros->{'host'}/g;
			$line =~ s/\^UP_HOST/\U$macros->{'host'}/g;
			$line =~ s/\^CAP_HOST/\u$macros->{'host'}/g;
		}


		# fill in the package list
		if ( ($line =~ m/\^PACKAGE_LIST/) && ( exists $macros->{'packages'} ) )
		{
		  my $subst = "";
		  foreach my $el ( split(/\s+/, $macros->{'packages'}) ) {
			$subst .= " \\\n                   $el";
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
			$subst .= " \\\n                   $el";
		  }
			$line =~ s/\^GROUP_LIST/$subst\n/g;
		}
		else {
		  $line =~ s/\^GROUP_LIST//g;
		}

        # Fill in the group, Group, or GROUP name.
		# Fill in the target, Target, or TARGET name.
		if ( exists $macros->{'name'} )
		{
			$line =~ s/\^GROUP/$macros->{'name'}/g;
			$line =~ s/\^UP_GROUP/\U$macros->{'name'}/g;
			$line =~ s/\^CAP_GROUP/\u$macros->{'name'}/g;
			$line =~ s/\^TARGET_DIR/$macros->{'name'}\\test/g;
			$line =~ s/\^TARGET/$macros->{'name'}/g;
			$line =~ s/\^UP_TARGET/\U$macros->{'name'}/g;
			$line =~ s/\^CAP_TARGET/\u$macros->{'name'}/g;
			$line =~ s/\^MODULE/$macros->{'name'}/g;
			$line =~ s/\^UP_MODULE/\U$macros->{'name'}/g;
			$line =~ s/\^CAP_MODULE/\u$macros->{'name'}/g;
		}

        print FILE "$line"; 
	}

    close FILE;
    close TEMPLATE_FILE;

}

1;
