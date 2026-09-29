#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                FuncTable.h


GENERAL DESCRIPTION

    This head file is for function table.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS

   Copyright (c) 2020 by ASR, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who        what, where, why
--------   ------     ----------------------------------------------------------
11/19/2020   zhoujin    Created module
===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "global_types.h"

/*===========================================================================

                                LOCAL MACRO
===========================================================================*/

/* Function table Max count  */
//#define  FUNC_TABLE_MAX_CNT         1024

/* APP magic  */
//#define  APP_MAGIC                  0xE59F0000

/*===========================================================================

                          Type definition.

===========================================================================*/


/*===========================================================================

            EXTERN DEFINITIONS AND DECLARATIONS FOR MODULE

===========================================================================*/

/* Function entry. */

typedef struct {
	UINT32 function;
	char *name;
}FunctionTable_T;


extern const UINT32 FunctionEntry[1];


/*===========================================================================

                        EXTERN FUNCTION DECLARATIONS

===========================================================================*/
#endif
