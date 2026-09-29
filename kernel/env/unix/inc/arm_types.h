/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : arm_types.h
Description : Global types file for the arm environment.

Notes       : This file is designed for use in the arm environment
              and is referenced from the gbl_types.h file. Use of
			  this file requires ENV_ARM to be defined in arm_env.mak.
              
Copyright 2001, Intel Corporation, All rights reserved.
=========================================================================== */

#if !defined(_ARM_TYPES_H_)
#define _ARM_TYPES_H_

typedef unsigned char	BOOL;
typedef unsigned char   UINT8;
typedef unsigned short  UINT16;
typedef unsigned long   UINT32;

typedef signed char     CHAR;
typedef signed char     INT8;
typedef signed short    INT16;
typedef signed long     INT32;

#ifdef  TRUE
#undef  TRUE
#endif	/* TRUE */
#define TRUE	1

#ifdef  FALSE
#undef  FALSE
#endif	/* FALSE */
#define FALSE	0

#endif /* _ARM_TYPES_H_ */

/*                         end of arm_types.h
--------------------------------------------------------------------------- */



