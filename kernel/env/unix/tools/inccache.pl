#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

use File::Copy;

my %SeenDirs        = ();
my %SeenFiles       = ();
my @Doubles         = ();
my $StopOnDuplicate = 0;

$StopOnDuplicate = 1 if defined $ARGV[1] and $ARGV[1] eq 'YES';

while (<main::DATA>)
  {
  	print "-----------------------------\n";
    next if /^\s*$/;
    foreach my $dir ( ( split /\s+/ ) )
      {
        next if $dir =~ /^\s*$/;
        next if defined $SeenDirs{$dir};
		
				print "--- MAIN:$dir ---\n";

        if ( opendir( DIR, $dir ) )
          {
            $SeenDirs{$dir} = 1;
            while ( my $h = readdir(DIR) )
              {
                next if $h !~ /\.(h|inc|csp|mfp)$/i;
                if ( defined $SeenFiles{$h} )
                  {
#                  	print "MAIN:$dir:$SeenFiles{$h}:$h\n";
                    $SeenDirs{$dir} = 0;
                    $SeenDirs{ $SeenFiles{$h} } = 0;

                    if ($StopOnDuplicate)
                      {
                        print
"INCLUDE CACHE ERROR :: duplicate file $h (found in $dir and $SeenFiles{$h})\n";
                        exit 128;
                      }
                    else
                      {

# (Un)comment for warining on duplicated files
#                    print
#"INCLUDE CACHE WARNING :: duplicate file $h (found in $dir and $SeenFiles{$h})\n";
                    print
"INCLUDE CACHE WARNING :: duplicate file $h (found in $dir and $SeenFiles{$h})\n";


 #                       last;
                      }
                  }
                print "MAIN:$dir:$h\n";                  
                $SeenFiles{$h} = $dir;
              }
            closedir DIR;
          }
      }
  }

my $counter = 0;
foreach my $header ( keys %SeenFiles )
  {
    next if $SeenDirs{ $SeenFiles{$header} } == 0;

    if ( not -e "$ARGV[0]/$header"
        or ( -M "$SeenFiles{$header}/$header" < -M "$ARGV[0]/$header" ) )
      {
        if ( copy( "$SeenFiles{$header}/$header", "$ARGV[0]/$header" ) )
          {
            chmod 0777, "$ARGV[0]/$header";

          # uncomment for debuging - will show files that were sucessfuly copied
            print "\t$SeenFiles{$header}/$header\n";
            $counter++;
          }
      }
  }
if ( $counter > 0 )
  {
    print "    $counter file(s) copied to / updated in include cache\n";
  }
else
  {
    print "    no files need to be updated in include cache\n";
  }

foreach ( keys %SeenDirs )
  {
    push @Doubles, $_ if $SeenDirs{$_} == 0;
  }

if ( open( DOUBLES, ">$ARGV[0]/doubles.cache" ) )
  {
  	print "doubles.cache --- @Doubles\n";
    print DOUBLES "EXPLICIT_INC_PATHS = " . join( " ", @Doubles );
    close DOUBLES;
  }
else
  {
    print "Failed to create double headers list file (doubles.cache)";
    exit 1;
  }

__DATA__
