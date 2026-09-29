#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------
#---------------------------------------------------------------------
#
# Patch Maker main procedure
#
#    Patching source code according to hardcoded rules
#
#    Working modes:
#
# -- Initial
#    1. init codebase  - create empty mandatory structures of the future codebase
#    2. init codecache - create empty patch function list structure in code cache repository
#
# -- Codebase Creation
#    1. make codebase - generate codebase to compare actual code to
#    2. make list     - generate list of ROM input sections and store it in the codebase
#    3. make tree     - generate functions call tree
#
# -- Patch Generation
#    1. make patch    - look for changes & produce a patch if appropriate
#       Submodes:
#       a. PATCH or noname - make patch as usual
#       b. LOG    - record compilation data in codebase and compile
#       c. SKIP   - transparent mode - compile only
#       d. FORCE  - patch COMMON functions regardless of results of body comparison
#
# -- Minor
#    1. show            - print content of the codebase in human-readable form
#    2. calculate size  - calculate penalty, that is memory that will be used after
#                         patching a function
#
#---------------------------------------------------------------------
# Programers: Kiril Serebnik
#
# REVISION HISTORY
#---------------------------------------------------------------------
# Version     Date            Author     Description
# 1.03        23-Feb-2009     KS         1. Implement mechanism of sorting patched functions
#                                           acoording to list of thresholds
#             24-Feb-2009     KS         1. Fix section number calculation for new functions
# 1.02        17-Feb-2009     KS         1. Read and concatenate lines from file until
#                                           ; or : at the end of line will be reached
#             18-Feb-2009     KS         2. Eliminate from concatanation enlty lines, comments
#                                           and lines that start with #
# 1.01        11-Feb-2009     KS         1. Implement FORCE working mode. In this mode all
#                                           COMMON functions will be patched regardless of results
#                                           of body comparison
#                                        2. Dump list of patched functions at the end of chain patching
#                                           if run in debug mode
#
# 1.00        09-Feb-2009     KS         Production Release
#
#
# 0.13        05-Feb-2009     KS         1. Change function comparison mechanism:
#                                           - in function's record there is a new field - DOCKET
#                                             that holds array of significant lines for comparison
#                                           - while comparing finctions - if lengths of these arrays are
#                                             different - function was changed
#                                           - otherwise compare only lines that where docketed
#                                        2. Make 'SKIP' mode silent
#                                        3. Don't log compiler command; for object name log path after obj_* folder
#                                        4. Produce compact (and hardly readable) codebase
#                                        5. Replace using function from Carp with internal functions for Panic/Error/Warning
#                                        6. Recognize 'Referenced by local' function calls
#                                        7. Properly cover chain patching of 'recursive' functions
# 0.12        05-Jan-2009     KS         1. Register all functions in separate sections
#                                        2. Arrange registration of new (artifical) section right after
#                                           the previuos function ends and not before next one begins
#                                        3. Identify ROM functions that were moved to RAM as deleted
#                                        4. Identify ROM function that was moved to another ROM section as new
#                                        5. ROM-ROM function moving - a new type of function state
#                                        6. Additional definition of labels declaration - 'LOOP'
#                                        7. Apply 'SKIP' mode to Chaon Patching working mode
#                                        8. More strict fix of non standard semicolons
# 0.11        27-Nov-2008     KS         1. Keep and use functions patching history as special comments in
#                                           the source assembly file
#                                        2. Print Patch Maker version to STDERR
#                                        3. Catch perl warnings and treat them as errors
#                                        4. Defend critical section in make patch and make chain
#                                        5. Chain patching has to be done also for deleted functions
#                                        6. Build full list of chain-patched functions to restore
# 0.10        23-Nov-2008     KS         1. Allow chain patching de-patch as well as patch functions
# 0.09        04-Nov-2008     KS         1. Add 'calculate patch penalty' mode
# 0.08        03-Nov-2008     KS         1. Make Patche & Msake Chain modes - change procedure
#                                           of writing patched file to keep order of ROM functions
# 0.07        27-Oct-2008     KS         1. Add 'make chain patching' mode
#                                        2. Add 'init codecache' mode
# 0.06        22-Oct-2008     KS         1. Add 'init codebase' mode
# 0.05        15-Oct-2008     KS         1. Add 'make call tree' mode
# 0.04        24-Sep-2008     KS         1. Make Patch & Make Codebase Modes - ignore input
#                                           lines that contain only ';'
# 0.03        21-Sep-2008     KS         1. Make Patch Mode - add treatment for added and
#                                           removed functions and files
# 0.02        15-Aug-2008     KS         1. Initial version
#---------------------------------------------------------------------

# Application version
our $VERSION = '1.03';

use strict;
use warnings;

use lib '/env/win32/tools/src';

use PatchMaker::globals;

use PatchMaker::initcb qw/ InitCodebase
  InitCodecache
  /;

use PatchMaker::mklist qw/ GenerateSectionsList     /;
use PatchMaker::mktree qw/ GenerateInverseCallTree  /;
use PatchMaker::mkcb qw/ GenerateCodebase           /;
use PatchMaker::mkpatch qw/ MakePatch               /;
use PatchMaker::mkchain qw/ MakeChainPatch          /;

use PatchMaker::cbview qw/ ShowCBFile               /;
use PatchMaker::calcsize qw/ CalculatePatchPenalty  /;

BEGIN
{
    $SIG{__WARN__} = sub {
        print "INTERNAL ERROR :: $_[0]";
        exit 1;
    };
}

#------------------- Main Procedure ---------------------

# Debug or not debug?
our $DEBUG;
Debug(0);

Debug(1) if $ARGV[0] =~ /^-*d(ebug)?$/i;
Debug(1) if defined $ENV{CB_DEBUG} and $ENV{CB_DEBUG} == 1;

shift @ARGV if $ARGV[0] =~ /^-*d(ebug)?$/i;

print STDERR <<VERSION;
ROM Patch Maker version $VERSION, build 215
(C) Copyright [2008,2009] Marvell International Ltd. All rights reserved.
VERSION

# Now, what exactly should we do?
my $MODE = 'NONE';

$MODE = shift @ARGV;

if ( $MODE =~ /^initcb$/i )
  {
    &PatchMaker::initcb::InitCodebase(@ARGV);
  }
elsif ( $MODE =~ /^initcc$/i )
  {
    &PatchMaker::initcb::InitCodecache(@ARGV);
  }
elsif ( $MODE =~ /^mkcb$/i )
  {
    &PatchMaker::mkcb::GenerateCodebase(@ARGV);
  }
elsif ( $MODE =~ /mkpatch/i )
  {
    &PatchMaker::mkpatch::MakePatch(@ARGV);
  }
elsif ( $MODE =~ /mkchain/i )
  {
    &PatchMaker::mkchain::MakeChainPatch(@ARGV);
  }
elsif ( $MODE =~ /mklist/i )
  {
    &PatchMaker::mklist::GenerateSectionsList(@ARGV);
  }
elsif ( $MODE =~ /mktree/i )
  {
    &PatchMaker::mktree::GenerateInverseCallTree(@ARGV);
  }
elsif ( $MODE =~ /show/i )
  {
    &PatchMaker::cbview::ShowCBFile(@ARGV);
  }
elsif ( $MODE =~ /calcsize/i )
  {
    &PatchMaker::calcsize::CalculatePatchPenalty(@ARGV);
  }
else
  {
    &PatchMaker::globals::Panic("Bad working mode $MODE");
  }

#-------------------------- END OF MAIN -------------------------------
