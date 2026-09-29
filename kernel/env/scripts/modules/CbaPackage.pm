#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!/usr/local/bin/perl -w
#==============================================================================
# File Name      : CbaPackage.pm
# Description    : Perl module of CBA (Cellular Build Architecture)
#                  package functions
#
# Notes          :
#
# Copyright (c) 2001 Intel of Canada, All Rights Reserved
#==============================================================================

package CbaPackage;

use strict;
use Exporter;
use vars qw(@ISA @EXPORT $VERSION);

use Cba;
use CbaClearCase;
use Time::localtime;

use ProjectSettings;

$VERSION  = 1.00;

@ISA    = qw(Exporter);
@EXPORT = qw(isPackage
             getPackageList
             getPackageInterfaceList
			 getPackageConfig
			 createPackageDirTree
			 createPackageMakeFiles
			 createPackageInterfaceFiles
             createPackageTestEnvFiles
             setCbaPackageDebug);

my $ibaPackDebug    = 0;
my $ibaPackDebugStr = "CbaPackage>";

sub setCbaPackageDebug
{
	$ibaPackDebug = $_[0];
	my $str = ($ibaPackDebug ? "Debugging on\n" : "Debugging off\n");
	CbaPackageDebug($str);
}

sub CbaPackageDebug { print "$ibaPackDebugStr @_" if $ibaPackDebug; }


# -----------------------------------------------------------------------------
# Function    : getPackageList
# Description : Finds a list of packages from a start directory
# Parms       : packList - the array to fill with package names
#               root     - root directory to start search
# Returns     : the package list
# Notes       : Ignores the env directory. Returns a list of
#               of basenames and package names in the
#               form : <base>/<package>
# -----------------------------------------------------------------------------
sub getPackageList
{
    # get the arguments
    my ($packList, $root) = @_;

	# get a list of the possible elements
	my @elementList = getElementList($root);

	CbaPackageDebug("Elements: @elementList\n");

	# now check for the actual packages
	foreach my $entry (@elementList)
	{
		if (isPackage("$root/$entry"))
		{
			push @$packList, File::Spec->canonpath($entry);
		}
	}
}

# -----------------------------------------------------------------------------
# Function    : isPackage
# Description : Check whether a element is a package
# Parms       : path - the path to the element to check
# Returns     : true or false
# Notes       :
# -----------------------------------------------------------------------------
sub isPackage
{
	my ($path) = @_;
	return isElement("package", $path);
}

# -----------------------------------------------------------------------------
# Function    : getPackageInterfaceList
# Description : Returns an array of package interface names
# Parms       : interfaceList - reference to an hash array to place results
#               package       - path to a package
# Returns     : none
# Notes       : The interface hash array is in the following format:
#
#               interface[n]{'name'} => <interface name>
#               interface[n]{'file'} => <interface file contents>
#
# -----------------------------------------------------------------------------
sub getPackageInterfaceList
{
	use File::Basename;

    # get the arguments
    my ($interfaceList, $package) = @_;
	my $packName = basename($package);
	my $interface;

	# clean up the directory
	my $interface_dir = File::Spec->canonpath($package."/inc");
	$interface_dir =~ s/\\\\/\\/;
	$interface_dir =~ s/\/\//\//;

	CbaPackageDebug("Checking $interface_dir\n");

	# open the inc directory of the package
	opendir(INC_DIR, $interface_dir) or return;

	# get the package interface files
	while ( defined ($interface = readdir INC_DIR) )
	{
		CbaPackageDebug("Checking $interface\n");

		# skip unless the entry is a directory
		next if ( -d $interface );

		# extract the interface names
		$interface =~ /^($packName)_([\w]+)\.h/;

		push @$interfaceList, $2;
	}

	closedir INC_DIR;
}

# -----------------------------------------------------------------------------
# Function    : getPackageInterface
# Description : Returns an hash of aray entries
# Parms       : interfaceList - reference to an array to place results
#               package       - path to a package
# Returns     : none
# Notes       : The interface names are only the interface names
# -----------------------------------------------------------------------------
sub getPackageInterface
{
	print "getPackageInterface() is under construction\n";
}

# -----------------------------------------------------------------------------
# Function    : getPackageConfig
# Description : Returns an array of hash entries containing
#               package configuration parameters
# Parms       : path - path and name of the package
# Returns     : the array of configuration parameters
# Notes       :
# -----------------------------------------------------------------------------
sub getPackageConfig
{
	use CbaConfigParm;

	my $path = $_[0];
	my $package = basename($path);
	my $config_file = File::Spec->canonpath("$path/inc/$package"."_config.h");

	return undef unless (-f $config_file);

	CbaPackageDebug("Path = $path\n");
	CbaPackageDebug("Package = $package\n");
	CbaPackageDebug("Opening $config_file\n");

	# open the package configuration file
	open FH, "< $config_file" or die "Cannot open $config_file\n";
	my @config_file_array = <FH>;
	close FH;

	# parse the config file
	my $cp = CbaConfigParm->new();
	my @config_array = $cp->Parse(\@config_file_array, "package");

	return @config_array;
}

# -----------------------------------------------------------------------------
# Function    : createPackageDirTree
# Description : Creates the directory tree for a package
# Parms       : dirArray - reference to the directory array
#               path     - path and name of the package to create
#               cc       - flag for creating ClearCase elements
#               branch   - if using ClearCase, the branch to create
#                          the directory elements on
# Returns     : the directory tree array
# Notes       : The directory tree must be empty
# -----------------------------------------------------------------------------
sub createPackageDirTree
{
	my ($dirArray, $packagePath, $ccFlag) = @_;

	# get the base directory
    my ($package, $packageBase) = fileparse($packagePath);

    push @$dirArray, $packageBase;
    push @$dirArray, $packagePath;
    push @$dirArray, $packagePath."/build";
    push @$dirArray, $packagePath."/inc";
    push @$dirArray, $packagePath."/src";
    push @$dirArray, $packagePath."/doc";
    push @$dirArray, $packagePath."/test";
    push @$dirArray, $packagePath."/test/bin";
    push @$dirArray, $packagePath."/test/build";
    push @$dirArray, $packagePath."/test/inc";
    push @$dirArray, $packagePath."/test/src";
    push @$dirArray, $packagePath."/test/obj";

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
			CbaPackageDebug("Creating $dir ...\n");
	    	mkdir($dir, 0777);
		}
    }
}

# -----------------------------------------------------------------------------
# Function    : subPackageMaros
# Description :
# Parms       :
# Returns     :
# Notes       :
# -----------------------------------------------------------------------------
sub subPackageMaros
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
		$line =~ s/\^MODULE_TYPE/package/g;
		$line =~ s/\^TARGET_TYPE/test-target/g;

		# fill in the group list
		if ( ! exists $macros->{'groups'}  ) {
		  $line =~ s/\^GROUP_LIST\(.*\)//;
		}

		# fill in the package list
		if ( (exists $macros->{'packages'}) && ($line =~ m/^(.*)\^PACKAGE_LIST\((.*)\)(.*)$/ ) ) {
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

		# Fill in the base, Base, or BASE name.
		if ( exists $macros->{'base'} )
		{
			$line =~ s/\^PACKAGE_BASE/$macros->{'base'}/g;
			$line =~ s/\^UP_PACKAGE_BASE/\U$macros->{'base'}/g;
			$line =~ s/\^CAP_PACKAGE_BASE/\u$macros->{'base'}/g;
			$line =~ s/\^TARGET_BASE/$macros->{'base'}/g;
			$line =~ s/\^MODULE_BASE/$macros->{'base'}/g;
			$line =~ s/\^UP_MODULE_BASE/\U$macros->{'base'}/g;
			$line =~ s/\^CAP_MODULE_BASE/\u$macros->{'base'}/g;
		}

		# Fill in the package, Package, or PACKAGE name.
		if ( exists $macros->{'name'} )
		{
			$line =~ s/\^PACKAGE/$macros->{'name'}/g;
			$line =~ s/\^TARGET_DIR/$macros->{'name'}\\test/g;
			$line =~ s/\^TARGET/$macros->{'name'}/g;
			$line =~ s/\^UP_PACKAGE/\U$macros->{'name'}/g;
			$line =~ s/\^CAP_PACKAGE/\u$macros->{'name'}/g;
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

		# fill in the source file list
		if ( exists $macros->{'src'} )
		{
			$line =~ s/\^SRC_FILE_LIST/$macros->{'src'}/g;
		}

		print FILE "$line";
	}

    close FILE;
    close TEMPLATE_FILE;

}

# -----------------------------------------------------------------------------
# Function    : createPackageMakeFiles
# Description :
# Parms       :
# Returns     :
# Notes       :
# -----------------------------------------------------------------------------
sub createPackageMakeFiles
{
	my ($srcList, $platformVar, $templateDir, $packagePath, $ccFlag, $lvcoFlag) = @_;

	# get the package name and base
	my ($package,$packageBase) = fileparse($packagePath);
	chop $packageBase;
	my $base = basename($packageBase);

	# create the macros hash
	my %macros = ();
	$macros{'name'}      = $package;
	$macros{'base'}      = $base;
	$macros{'platform'}  = $platformVar;

	# fill in the source file string
	foreach my $src (@$srcList)
	{
		$macros{'src'} .= "\\\n                    $src";
	}

	# create the make file
	my $file     = File::Spec->canonpath("$packagePath/build/$package.mak");
	my $template = File::Spec->canonpath("$templateDir/build/package.mak.tpl");

	if (! -e $file)
	{
		CbaPackageDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subPackageMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}

	# create the make dependency file
	$file     = File::Spec->canonpath("$packagePath/build/$package"."_dep.mak");
	$template = File::Spec->canonpath("$templateDir/build/package_dep.mak.tpl");

	if (! -e $file)
	{
		CbaPackageDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subPackageMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}
}

# -----------------------------------------------------------------------------
# Function    : createPackageInterfaceFiles
# Description :
# Parms       :
# Returns     :
# Notes       :
# -----------------------------------------------------------------------------
sub createPackageInterfaceFiles
{
	my ($ifArray, $templateDir, $packagePath, $ccFlag, $lvcoFlag) = @_;

	# get the package name and base
	my ($package,$packageBase) = fileparse($packagePath);
	chop $packageBase;
	my $base = basename($packageBase);

	# create the macros hash
	my %macros = ();
	$macros{'name'}      = $package;
	$macros{'base'}      = $base;
	$macros{'platform'}  = "";

	my ($file, $template);
        my @srcList = ();

        # create the ldf file
        $file     = File::Spec->canonpath("$packagePath/inc/$package".".ldf");
        $template = File::Spec->canonpath("$templateDir/inc/package.ldf.tpl");

        # get the template file
        if (! -e $template)
        {
                $template = File::Spec->canonpath("$templateDir/inc/package.ldf.tpl");
        }

        if (! -e $file)
        {
                CbaPackageDebug("Creating $file\n");
                createFileElement($file) if ($ccFlag);
                subPackageMaros($file, $template, \%macros);
        checkinElement($file) if (!$lvcoFlag);
        }


	# loop through the interface files
	foreach my $if (@$ifArray)
	{
		# skip any removed interfaces
		next if ($if eq "");

		$macros{'interface'} = "$if";

		if ( $if =~ m/^API$/ ) { $if = ""; }
		else { $if = "_$if"; }

		# create the include file
		$file     = File::Spec->canonpath("$packagePath/inc/$package"."$if".".h");
		$template = File::Spec->canonpath("$templateDir/inc/package$if.h.tpl");

		# get the template file
		if (! -e $template)
		{
			$template = File::Spec->canonpath("$templateDir/inc/package_if.h.tpl");
		}

		if (! -e $file)
		{
			CbaPackageDebug("Creating $file\n");
		    createFileElement($file) if ($ccFlag);
			subPackageMaros($file, $template, \%macros);
	    	checkinElement($file) if (!$lvcoFlag);
		}

		# create the source file
		$file     = File::Spec->canonpath("$packagePath/src/$package"."$if".".c");
		$template = File::Spec->canonpath("$templateDir/src/package$if.c.tpl");

		# get the template file
		if (! -e $template)
		{
			$template = File::Spec->canonpath("$templateDir/src/package_if.c.tpl");
		}

		# hack -- do not create a source file for the following
		# interface names
		next if ($if eq "_types");
		next if ($if eq "_config");

		# add the file to the source list
		push @srcList, basename($file);

		if (! -e $file)
		{
			CbaPackageDebug("Creating $file\n");
		    createFileElement($file) if ($ccFlag);
			subPackageMaros($file, $template, \%macros);
	    	checkinElement($file) if (!$lvcoFlag);
		}
	}

	return @srcList;
}

# -----------------------------------------------------------------------------
# Function    : createPackageTestEnvFiles
# Description :
# Parms       :
# Returns     :
# Notes       :
# -----------------------------------------------------------------------------
sub createPackageTestEnvFiles
{
	my ($envArray, $platformVar, $templateDir, $packagePath, $ccFlag, $lvcoFlag) = @_;

	# get the package name and base
	my ($package,$packageBase) = fileparse($packagePath);
	chop $packageBase;
	my $base = basename($packageBase);

	# create the macros hash
	my %macros = ();
	$macros{'name'}      = $package;
	$macros{'base'}      = $base;
	$macros{'host'}      = "win32";
	$macros{'packages'}  = $package;
	$macros{'platform'}  = $platformVar;

	my ($file, $template);

	# loop through the test enviroments
	foreach my $env (@$envArray)
	{
		# skip any removed environments
		next if ($env eq "");

		$macros{'env'} = "$env";

		# create the make file
		$file     = File::Spec->canonpath("$packagePath/test/build/$package"."_$env".".mak");
		$template = File::Spec->canonpath("$templateDir/test/package_env.mak.tpl");

		if (! -e $file)
		{
			CbaPackageDebug("Creating $file\n");
		    createFileElement($file) if ($ccFlag);
			subPackageMaros($file, $template, \%macros);
	    	checkinElement($file) if (!$lvcoFlag);
		}
	}

    # create the ldf file
        $file     = File::Spec->canonpath("$packagePath/test/src/$package"."_msa.ldf");
        $template = File::Spec->canonpath("$templateDir/test/target_env.ldf.tpl");

		if (! -e $file)
		{
			CbaPackageDebug("Creating $file\n");
		    createFileElement($file) if ($ccFlag);
			subPackageMaros($file, $template, \%macros);
	    	checkinElement($file) if (!$lvcoFlag);
		}


	# create the global config file
	$file     = File::Spec->canonpath("$packagePath/test/inc/gbl_config.h");
	$template = File::Spec->canonpath("$templateDir/inc/gbl_config.h.tpl");

	if (! -e $file)
	{
		CbaPackageDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subPackageMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}

	# create the main test file
	$file     = File::Spec->canonpath("$packagePath/test/src/UserMain.c");
	$template = File::Spec->canonpath("$templateDir/test/main.c.tpl");

	if (! -e $file)
	{
		CbaPackageDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subPackageMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}

	# create the make batch file
	$file     = File::Spec->canonpath("$packagePath/test/build/make.bat");
	$template = File::Spec->canonpath("$templateDir/build/make.bat.tpl");

	if (! -e $file)
	{
		CbaPackageDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subPackageMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}

	# create debugger script
	$file     = File::Spec->canonpath("$packagePath/test/inc/$package" . ".xdb");
	$template = File::Spec->canonpath("$templateDir/inc/StartUpScript.xdb.tpl");

	if (! -e $file)
	{
		CbaPackageDebug("Creating $file\n");
	    createFileElement($file) if ($ccFlag);
		subPackageMaros($file, $template, \%macros);
	    checkinElement($file) if (!$lvcoFlag);
	}


}

1;












