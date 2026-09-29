/* ===========================================================================
File        : ^FILE
Programmer	: ^PROGRAMMER
Description : Configuration parameters for the ^PACKAGE_BASE/^PACKAGE package.
Create Date	: ^DATE
Notes       : These values can be overridden in gbl_config.h

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
=========================================================================== */

#if !defined(_^UP_PACKAGE_CONFIG_H_)
#define _^UP_PACKAGE_CONFIG_H_

/* Include the global configuration file, to override local parameters */
#if defined(_GBL_CONFIG_H_)
#undef _GBL_CONFIG_H_
#endif
#include "gbl_config.h"

/////////////////////////////////////////////////////////////////////////
// Below is usage example of the configuration interface
// define PARAM1_DEFAULT value
#undef ^UP_PACKAGE_PARAM1_DEFAULT
#define ^UP_PACKAGE_PARAM1_DEFAULT ( 0 )

#if !defined( ^UP_PACKAGE_PARAM1 ) // if not defined from gbl_config.h, define it to the default value
#define    ^UP_PACKAGE_PARAM1    ^UP_PACKAGE_PARAM1_DEFAULT
#endif
// End of the example
/////////////////////////////////////////////////////////////////////////

#endif /* _^UP_PACKAGE_CONFIG_H_ */




