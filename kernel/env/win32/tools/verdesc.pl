use strict;
use warnings;

my @Handler = ();

if ( not scalar @ARGV or not -f $ARGV[0] )
  {
    @Handler = <main::DATA>;
  }
else
  {
    @Handler = <>;
  }

foreach (@Handler)
  {
    chomp;
    next if not -f $_;
    next if not open( VERS, "<$_" );
    my @vers   = <VERS>;
    my $string = $vers[2];
    close VERS;
    chomp $string;
    $string =~ s/\s//g;
    print "$string\n";
  }

__DATA__
\csw\version.txt
\diag\version.txt
\os\osa\version.txt
\os\nu_xscale\version.txt
