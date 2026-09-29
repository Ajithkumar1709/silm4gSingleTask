/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : ict_types.h
Description : Global types file for the Nordheim environment.

Notes       : This file is designed for use in the Nordheim environment
              and is referenced from the gbl_types.h file. Use of
              this file requires ENV_ICT to be defined in ict_env.mak.

Copyright 2001, Intel Corporation, All rights reserved.
=========================================================================== */

#if !defined(_ICT_TYPES_H_)
#define _ICT_TYPES_H_

typedef unsigned char	BOOL;
typedef unsigned char   UINT8;
typedef unsigned short  UINT16;
typedef unsigned long   UINT32;

typedef char            CHAR;
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

#endif /* _ICT_TYPES_H_ */

/*                         end of ict_types.h
--------------------------------------------------------------------------- */




