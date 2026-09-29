#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

use File::Find;
use File::Copy;
use File::Basename;

my $TargetVariant            = shift @ARGV;
my $RawListOfFilesAfterStrip = shift @ARGV;

my $ObjExt = '\.doj';
$ObjExt = $ENV{STRIP_OBJ_EXT} if defined $ENV{STRIP_OBJ_EXT};
my $AsmExt = '\.asm';
$AsmExt = $ENV{STRIP_ASM_EXT} if defined $ENV{STRIP_ASM_EXT};

my $ObjStoreDir = "..\\objstore";
$ObjStoreDir .= "_$TargetVariant";

mkdir $ObjStoreDir;

my %Names = ();
if (open(SRCLIST, "<$RawListOfFilesAfterStrip"))
  {
    while (<SRCLIST>)
      {
	next if !/^Source/;

	s/^Source\s+:\s+//;
	foreach my $file (split /\s+/)
	  {
	    next if not $file or $file =~ /^\s*$/;
	    $file =~ s/\.\w+$//;
	    $Names{ $file } = 1;
	  }
      }
    close SRCLIST;
  }
else
  {
    print "Failed to open source list file $RawListOfFilesAfterStrip\n";
    exit 1;
  }

my @OBJ    = ();
my @LOG    = ();
my $ObjDir = 'obj';
$ObjDir .= "_$TargetVariant" if $TargetVariant;

find(
    {
        wanted => sub {
            my $name = basename($_);
            $name =~ s/\.\w+$//;
            my $obj = $_;
	    print "NOT DEFINED $name $obj\n" if not defined $Names{$name};
            if ( $obj =~ /$ObjExt$/ and not defined $Names{$name} )
              {
                my $CleanName = $File::Find::name;
                $CleanName =~ s/^\\\.//;
                if ( copy( $CleanName, "$ObjStoreDir\\" . basename($_) ) )
                  {
                    push @OBJ, "$ObjStoreDir\\" . basename($_);
                    push @LOG, "$CleanName to $ObjStoreDir\\" . basename($_);
                  }
                else
                  {
                    print "Failed to copy $CleanName to $ObjStoreDir\\"
                      . baseline($_)
                      . " :: $!\n";
                    exit 1;
                  }
              }
        },
        no_chdir => 1
    },
    ("../$ObjDir")
);

my $ObjListFile = "$ObjStoreDir\\objstore_list.txt";
my $ObjListLog  = "$ObjStoreDir\\objstore_list.log";

$ObjListFile = "$ObjStoreDir\\objstore_list_$TargetVariant.txt"
  if defined $TargetVariant;
$ObjListLog = "$ObjStoreDir\\objstore_list_$TargetVariant.log"
  if defined $TargetVariant;

if ( open( OBJLIST, ">$ObjListFile" ) )
  {
    print OBJLIST join( "\n", @OBJ );
    close OBJLIST;
  }
else
  {
    print "Failed to open obj store list file ($ObjListFile) for writing\n";
    exit 1;
  }

if ( open( LOGLIST, ">$ObjListLog" ) )
  {
    print LOGLIST join( "\n", @LOG );
    close LOGLIST;
  }
