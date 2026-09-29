/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : fsm_config.h
Description : Configuration parameters for the 
              genlib/fsm package.

Notes       : These values can be overridden in gbl_config.h
              The range checks should be updated for each
              parameter.

Copyright (c) 2001 Intel CCD. All Rights Reserved
=========================================================================== */

#if !defined(_FSM_CONFIG_H_)
#define _FSM_CONFIG_H_

/* Include the global configuration file, so these values
   can be overridden */
#if defined(_GBL_CONFIG_H_)
#undef _GBL_CONFIG_H_
#endif
#include "gbl_config.h"


#endif /* _FSM_CONFIG_H_ */


/*                      end of fsm_config.h
--------------------------------------------------------------------------- */





