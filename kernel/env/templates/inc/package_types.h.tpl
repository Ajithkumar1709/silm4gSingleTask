/* ===========================================================================
File        : ^FILE
Description : Data types file for the ^PACKAGE_BASE/^PACKAGE package

Notes       : 

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
=========================================================================== */

#if !defined(_^UP_PACKAGE_TYPES_H_)
#define _^UP_PACKAGE_TYPES_H_

#include "cfw_typedef.h"

/* ---------------------------------------------------------------------------
Enum name   : ^CAP_PACKAGEExampleEnum
Description : This is an example ^PACKAGE enumerated type
Notes       : Modify as required
--------------------------------------------------------------------------- */
enum _^CAP_PACKAGEExampleEnum
{
  ^UP_PACKAGE_first,
  ^UP_PACKAGE_second,
  ^UP_PACKAGE_MAX
};

typedef UINT8 ^CAP_PACKAGEExampleEnum;

/* ---------------------------------------------------------------------------
Struct name : ^CAP_PACKAGEExampleType
Description : This is an example ^PACKAGE data type
Notes       : Modify as required
--------------------------------------------------------------------------- */
typedef struct _^CAP_PACKAGEExampleType
{
  UINT8 first;
  UINT8 second;
  BOOL  third;
} ^CAP_PACKAGEExampleType;


#endif /* _^UP_PACKAGE_TYPES_H_ */


/*                      end of ^FILE
--------------------------------------------------------------------------- */




