/* ===========================================================================
File        : gbl_id.h
Description : Global file ID's for ^TARGET_BASE/^TARGET target.

Notes       : This file is designed for use in any environment.
              The files included by this file are created dynamically
              during the build process.  The actual file included
              is based on the VARIANT of the ^TARGET_BASE/^TARGET target.

              Add the VARIANT's as required. The syntax is as follows:

              #ifdef <VARIANT>
              #include gbl_<variant>_id.h
              #endif

              Replace the <VARIANT> tags with the variant names defined in
              the target make file. The none variant case is handled by the 
              default ID file.  It is added after the last variant case. The 
              non-variant case uses the file "gbl_default_id.h".

Copyright ^YEAR, Intel Corporation, All rights reserved.
=========================================================================== */

#if !defined(_GBL_ID_H_)
#define _GBL_ID_H_

#ifdef VARIANT_1
#include "gbl_variant_1_id.h"
#endif

#ifdef VARIANT_2
#include "gbl_variant_2_id.h"
#endif

#ifdef VARIANT_LAST
#include "gbl_variant_last_id.h"
#else
#include "gbl_default_id.h"
#endif

#endif /* _GBL_ID_H_ */

/*                           end of gbl_id.h
--------------------------------------------------------------------------- */



