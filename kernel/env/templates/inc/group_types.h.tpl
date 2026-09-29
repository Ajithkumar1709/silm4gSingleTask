/* ===========================================================================
File        : ^FILE
Description : Data types file for the ^GROUP_BASE/^GROUP group

Notes       : These enums and data types exist in the various service
              access points of the ^GROUP_BASE/^GROUP group. It also
			  contains promoted data types from the other groups and
			  packages.

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
=========================================================================== */

#if !defined(_^UP_GROUP_TYPES_H_)
#define _^UP_GROUP_TYPES_H_

#include "cfw_typedef.h"


/* =========================== Promoted Types ============================= */



/* ========================== Local Group Types =========================== */

/* ---------------------------------------------------------------------------
Enum name   : ^CAP_GROUPExampleEnum
Description : This is an example ^GROUP enumerated type
Notes       : Modify as required
--------------------------------------------------------------------------- */
enum _^CAP_GROUPExampleEnum
{
  ^UP_GROUP_^UP_INTERFACE_first,
  ^UP_GROUP_^UP_INTERFACE_second,
  ^UP_GROUP_^UP_INTERFACE_MAX
};

typedef UINT8 ^CAP_GROUPExampleEnum;

/* ---------------------------------------------------------------------------
Struct name : ^CAP_GROUPExampleType
Description : This is an example ^GROUP data type
Notes       : Modify as required
--------------------------------------------------------------------------- */
typedef struct _^CAP_GROUPExampleType
{
  UINT8 first;
  UINT8 second;
  BOOL  third;
} ^CAP_GROUPExampleType;


#endif /* _^UP_GROUP_TYPES_H_ */


/*                      end of ^FILE
--------------------------------------------------------------------------- */




