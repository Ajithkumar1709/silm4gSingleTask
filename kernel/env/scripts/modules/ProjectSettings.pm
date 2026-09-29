#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

package ProjectSettings;
use Exporter;
#use vars qw(@ISA @EXPORT);
@ISA    = qw(Exporter);
@EXPORT = qw(GetProjectSettings);

my %ProjectSettingsDB = (
					Threepoint => {
								   VOBName    => "3p_l1control",
								   MainIncDir => "Inc"
								  },
					Manitoba   => {
								   VOBName    => "Manitoba",
								   MainIncDir => "Inc"
								  }
);

sub GetProjectSettings
{
  my ( $project, $projSetHash ) = @_;

#  print "[$project]: ";
  foreach $el ( keys %{ $ProjectSettingsDB{$project} } ) {
#	print "[$el] ";
	$$projSetHash->{$el} = $ProjectSettingsDB{$project}{$el};
  }
#  print "\n";
}
					   
