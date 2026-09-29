/* ===========================================================================
File        : ^FILE
Description : Implementation file for the system interface
              of the ^GROUP_BASE/^GROUP group.

Notes       : 

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
=========================================================================== */

#include "^GROUP_sys.h"

static char ^GROUPVersionStr[] = "GP_^UP_GROUP_1.0.0";

/* ---------------------------------------------------------------------------
Function    : ^CAP_GROUPGetVersion
Description : Returns the version of the ^GROUP group
Parameters  : none
Returns     : pointer to a null-terminated char array
Notes       : 
--------------------------------------------------------------------------- */
char *^CAP_GROUPGetVersion ( void ) 
{
	return(^GROUPVersionStr);
}

/* ---------------------------------------------------------------------------
Function    : ^CAP_GROUPInit
Description : Initialization function for system interface
              the ^GROUP group.
Parameters  : 
Returns     : 
Notes       : 
--------------------------------------------------------------------------- */
void ^CAP_GROUPInit ( void ) 
{
	return;
}


/*                   end of ^FILE
--------------------------------------------------------------------------- */






