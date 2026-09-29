/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : gnu_types.h
Description : Global types file for the gnu environment.

Notes       : This file is designed for use in the gnu environment
              and is referenced from the gbl_types.h file. Use of
			  this file requires ENV_GNU to be defined in gnu_env.mak.
              
Copyright 2001, Intel Corporation, All rights reserved.
=========================================================================== */

#if !defined(_GNU_TYPES_H_)
#define _GNU_TYPES_H_

typedef unsigned char	BOOL;
typedef unsigned char   UINT8;
typedef unsigned short  UINT16;
typedef unsigned long   UINT32;

typedef signed char     CHAR;
typedef signed char     INT8;
typedef signed short    INT16;
typedef signed long     INT32;

// disable arm specific keyword when not using arm compiler
#ifndef __arm
#define __packed
#define __align(x) __attribute__ ((aligned (x)))
//#define __MODULE__ "Module name"
#endif

#ifdef  TRUE
#undef  TRUE
#endif	/* TRUE */
#define TRUE	1

#ifdef  FALSE
#undef  FALSE
#endif	/* FALSE */
#define FALSE	0

#endif /* _GNU_TYPES_H_ */

/*                         end of gnu_types.h
--------------------------------------------------------------------------- */



