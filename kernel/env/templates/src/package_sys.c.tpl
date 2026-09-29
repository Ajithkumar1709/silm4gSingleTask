/* ===========================================================================
File        : ^FILE
Description : Implementation file for the system interface
              of the ^PACKAGE_BASE/^PACKAGE package.

Notes       : 

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
=========================================================================== */

#include "^PACKAGE_types.h"
#include "^PACKAGE_sys.h"

static char ^PACKAGEVersionStr[] = "GP_^UP_PACKAGE_1.0.0";

/* ---------------------------------------------------------------------------
Function    : ^CAP_PACKAGEGetVersion
Description : Returns the version of the ^PACKAGE package
Parameters  : none
Returns     : pointer to a null-terminated char array
Notes       : 
--------------------------------------------------------------------------- */
char *^CAP_PACKAGEGetVersion ( void ) 
{
	return(^PACKAGEVersionStr);
}

/* ---------------------------------------------------------------------------
Function    : ^CAP_PACKAGEInit
Description : Initialization function for system interface
              the ^PACKAGE package.
Parameters  : 
Returns     : 
Notes       : 
--------------------------------------------------------------------------- */
void ^CAP_PACKAGEInit ( void ) 
{
	return;
}


/*                   end of ^FILE
--------------------------------------------------------------------------- */






