/* ===========================================================================
File        : ^FILE
Programmer	: ^PROGRAMMER
Description : Configuration parameters for the ^GROUP_BASE/^GROUP group.
Create Date	: ^DATE
Notes       : These values can be overridden in gbl_config.h

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
=========================================================================== */

#if !defined(_^UP_GROUP_CONFIG_H_)
#define _^UP_GROUP_CONFIG_H_

/* Include the global configuration file, to override local parameters */
#if defined(_GBL_CONFIG_H_)
#undef _GBL_CONFIG_H_
#endif
#include "gbl_config.h"

/////////////////////////////////////////////////////////////////////////
// Below is usage example of the configuration interface
// define PARAM1_DEFAULT value
#undef ^UP_GROUP_PARAM1_DEFAULT
#define ^UP_GROUP_PARAM1_DEFAULT ( 0 )

#if !defined( ^UP_GROUP_PARAM1 ) // if not defined from gbl_config.h, define it to the default value
#define    ^UP_GROUP_PARAM1    ^UP_GROUP_PARAM1_DEFAULT
#endif
// End of the example
/////////////////////////////////////////////////////////////////////////

#endif /* _^UP_GROUP_CONFIG_H_ */
