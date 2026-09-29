/* ===========================================================================
File        : nu_xscale_config.h
Description : Configuration parameters for the 
              os/nu_xscale package.

Notes       : These values can be overridden in gbl_config.h
              The range checks should be updated for each
              parameter.

Copyright (c) 2001 Intel CCD. All Rights Reserved
=========================================================================== */

#if !defined(_NU_XSCALE_CONFIG_H_)
#define _NU_XSCALE_CONFIG_H_

/* ---------------------------------------------------------------------------
Parameter   : nu_xscale <Example> Parameter
Description : nu_xscale parameter description 
Notes       : Why the range is what it is etc.
--------------------------------------------------------------------------- */
#define NU_XSCALE_<EXAMPLE>       <value>
#define NU_XSCALE_<EXAMPLE>_MIN	<min>
#define NU_XSCALE_<EXAMPLE>_STEP	<step>
#define NU_XSCALE_<EXAMPLE>_MAX	<max>


/* Include the global configuration file, so these values
   can be overridden */
#if defined(_GBL_CONFIG_H_)
#undef _GBL_CONFIG_H_
#endif
#include "gbl_config.h"

/* Check the <Example> Parameter Range */
#if (NU_XSCALE_<Example> < NU_XSCALE_<Example>_MIN)|| \
    (NU_XSCALE_<Example> > NU_XSCALE_<Example>_MAX)
#error "Nu_xscale Package <Example> parameter out of range."
#endif

#endif /* _NU_XSCALE_CONFIG_H_ */


/*                      end of nu_xscale_config.h
--------------------------------------------------------------------------- */





