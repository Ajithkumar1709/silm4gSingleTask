/* ===========================================================================
File        : nu_xscale_types.h
Description : Data types file for the os/nu_xscale package

Notes       : 

Copyright (c) 2001 Intel CCD. All Rights Reserved
=========================================================================== */

#if !defined(_NU_XSCALE_TYPES_H_)
#define _NU_XSCALE_TYPES_H_

#include "gbl_types.h"

/* ---------------------------------------------------------------------------
Enum name   : Nu_xscaleExampleEnum
Description : This is an example nu_xscale enumerated type
Notes       : Modify as required
--------------------------------------------------------------------------- */
enum _Nu_xscaleExampleEnum
{
  NU_XSCALE_first,
  NU_XSCALE_second,
  NU_XSCALE_MAX
};

typedef UINT8 Nu_xscaleExampleEnum;

/* ---------------------------------------------------------------------------
Struct name : Nu_xscaleExampleType
Description : This is an example nu_xscale data type
Notes       : Modify as required
--------------------------------------------------------------------------- */
typedef struct _Nu_xscaleExampleType
{
  UINT8 first;
  UINT8 second;
  BOOL  third;
} Nu_xscaleExampleType;


#endif /* _NU_XSCALE_TYPES_H_ */


/*                      end of nu_xscale_types.h
--------------------------------------------------------------------------- */




