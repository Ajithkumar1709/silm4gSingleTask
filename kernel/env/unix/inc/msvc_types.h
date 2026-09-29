/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : msvc_types.h
Description : Global types file for the Microsoft Visual C++ environment.

Notes       : This file is designed for use in the arm environment
              and is referenced from the gbl_types.h file. Use of
			  this file requires ENV_MSVC to be defined in msvc_env.mak.
              
Copyright 2001, Intel Corporation, All rights reserved.
=========================================================================== */

#if !defined(_MSVC_TYPES_H_)
#define _MSVC_TYPES_H_

/* BOOL is defined in windef.h. This conflicts when WIN32 is defined */
#if !defined(WIN32)
typedef unsigned char	BOOL;
#endif

typedef unsigned char   UINT8;
typedef unsigned short  UINT16;
typedef unsigned long   UINT32;

typedef char            CHAR;
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

#endif /* _MSVC_TYPES_H_ */

/*                         end of msvc_types.h
--------------------------------------------------------------------------- */



