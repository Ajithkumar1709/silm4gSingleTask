/* ===========================================================================
File        : ^PACKAGE_id.h
Description : File ID's for ^PACKAGE_BASE/^PACKAGE target.

Notes       : This file is designed for use in any environment.
              The files included by this file are created dynamically
              during the package build process.  The actual file included
              is based on the PACKAGE_VARIANT of the ^PACKAGE_BASE/^PACKAGE 
              package.

              Add the PACKAGE_VARIANT's as required.
			  The syntax is as follows:

              #ifdef  <^UP_PACKAGE_VARIANT>
			  #define ^UP_PACKAGE_VARIANT_EXISTS
              #include <^PACKAGE_variant>_id.h
              #endif

              Replace the <VARIANT> tags with the variant names defined in
              the package make file. The none variant case is handled by the 
              default ID file.  It is added after the last variant case. The 
              non-variant case uses the file "^PACKAGE_default_id.h".

Copyright ^YEAR, Intel Corporation, All rights reserved.
=========================================================================== */

#if !defined(_^UP_PACKAGE_ID_H_)
#define _^UP_PACKAGE_ID_H_

/* Add the package and group Id's */
#include "gbl_id.h"

#ifdef  ^UP_PACKAGE_VARIANT_1
#define ^UP_PACKAGE_VARIANT_EXISTS
#include "^PACKAGE_variant_1_id.h"
#endif

#ifdef  ^UP_PACKAGE_VARIANT_2
#define ^UP_PACKAGE_VARIANT_EXISTS
#include "^PACKAGE_variant_2_id.h"
#endif

/* Add the default (no variant) if no other variants exist */
#ifndef ^UP_PACKAGE_VARIANT_EXISTS
#include "^PACKAGE_default_id.h"
#endif

#endif /* _^UP_PACKAGE_ID_H_ */

/*                           end of ^PACKAGE_id.h
--------------------------------------------------------------------------- */



