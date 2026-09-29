#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

$Usage =          "Usage: $0 <MapFile> [OutputSectionName1 OutputSectionName2 ... ]\n";
$Usage = $Usage . " Extracts from the MapFile lines with OutputSectionNames\n";

((scalar @ARGV) < 1) && die "$Usage";
$map_file = shift (@ARGV);
open(MAPFILE , "< $map_file") || die "$0: Can't open '$map_file'.\n";

$ParamNum = scalar(@ARGV);

while ( $line = <MAPFILE> ) {
  foreach $el (@ARGV) {
	if ( $line =~ /^$el\s+SHT.*/ ) { print $line; }
  }
}
