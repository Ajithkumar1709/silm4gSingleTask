#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

#!perl -w
#---------------------------------------------------------
# CBA Utilities
#
# Build Suite
#
# 1. Create a lock file. (lock)
# 2. Wait for locked file (locked)
# 3. Delete lock file (unlock)
# 4. Delete lock file with error
#
# Programer(s): Kiril Serebnik
#
# REVISION HISTORY
#---------------------------------------------------------
# Version   When           Who    What
#---------------------------------------------------------
# 1.0.0     23-Oct-2007    KS     Initial version
#--------------------------------------------------------

use Time::HiRes;
use Win32;
use File::Touch;

my $Version = '1.0.0';

my $t;

my $mode      = $ARGV[0];
my $lock_file = $ARGV[1];

if ( $mode eq 'LOCK' )
  {

    # insert random delay up to 3 secs
    my $delay = int rand 3000;
    Win32::Sleep($delay);

    if ( -f qq($lock_file) )
      {
        $t = Time::HiRes::gettimeofday();
        print "\n\n==$t== Build locked. Waiting ... \n\n";

        while ( -f qq($lock_file) )
          {
            Win32::Sleep(10000);
          }
      }

    until ( touch($lock_file) )
    {
        $t = Time::HiRes::gettimeofday();
        print
"==$t== Failed to create lock file $lock_file. Will retry in 10 secs\n";
        Win32::Sleep(10000);
    }

    $t = Time::HiRes::gettimeofday();
    print "==$t== LOCKED [$lock_file]\n";
  }

if ( $mode eq 'UNLOCK' )
  {
    if ( -f $lock_file )
      {
        until ( unlink(qq($lock_file)) )
        {
            $t = Time::HiRes::gettimeofday();
            print "==$t== Failed to create lock file. Will retry in 10 secs\n";
            Win32::Sleep(10000);
        }
      }
    else
      {
        $t = Time::HiRes::gettimeofday();
        print "==$t== Lock file does not exist\n";
      }

    $t = Time::HiRes::gettimeofday();
    print "==$t== UNLOCKED [$lock_file]\n";
  }

if ( $mode eq 'UNLOCK_W_ERROR' )
  {
    if ( -f $lock_file )
      {
        until ( unlink(qq($lock_file)) )
        {
            $t = Time::HiRes::gettimeofday();
            print "==$t== Failed to create lock file. Will retry in 10 secs\n";
            Win32::Sleep(10000);
        }
      }
    else
      {
        $t = Time::HiRes::gettimeofday();
        print "==$t== Lock file does not exist\n";
      }

    $t = Time::HiRes::gettimeofday();
    print "==$t== UNLOCKED [$lock_file]\n";

    exit 1;
  }
