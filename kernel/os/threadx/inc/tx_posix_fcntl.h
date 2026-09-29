/**************************************************************************/
/*                                                                        */
/*            Copyright (c) 1996-2006 by Express Logic Inc.               */
/*                                                                        */
/*  This software is copyrighted by and is the sole property of Express   */
/*  Logic, Inc.  All rights, title, ownership, or other interests         */
/*  in the software remain the property of Express Logic, Inc.  This      */
/*  software may only be used in accordance with the corresponding        */
/*  license agreement.  Any unauthorized use, duplication, transmission,  */
/*  distribution, or disclosure of this software is expressly forbidden.  */
/*                                                                        */
/*  This Copyright notice may not be removed or modified without prior    */
/*  written consent of Express Logic, Inc.                                */
/*                                                                        */
/*  Express Logic, Inc. reserves the right to modify this software        */
/*  without notice.                                                       */
/*                                                                        */
/*  Express Logic, Inc.                                                   */
/*  11423 West Bernardo Court               info@expresslogic.com         */
/*  San Diego, CA  92127                    http://www.expresslogic.com   */
/*                                                                        */
/*                                                                        */
/**************************************************************************/

/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/**   ThreadX Component                                                   */
/**                                                                       */
/**   POSIX Compliancy Wrapper (POSIX)                                    */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  EKP DEFINITIONS                                        RELEASE        */
/*                                                                        */
/*    fcntl.h                                             PORTABLE C      */
/*                                                           5.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Express Logic, Inc.                                                 */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file defines the constants, structures, etc.needed to          */
/*    implement the Evacuation Kit for POSIX Users (POSIX)                */
/*                                                                        */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  12-12-2005         Stefaan Kiebooms          Initial Version          */
/*                                                                        */
/**************************************************************************/

#ifndef _FCNTL_H
#define _FCNTL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Marvell Change to support including <fcntl.h> from toolchain */
#ifndef _FCNTL_
#define _FCNTL_

#define O_ACCMODE	0x0003

#ifdef O_RDONLY
#if O_RDONLY == 0x0000
#undef O_RDONLY
#else
#error "Duplicated definition of O_RDONLY with different values"
#endif
#endif

#define O_RDONLY	0x0000
#ifdef O_WRONLY
#if O_WRONLY ==0x0001
#undef O_WRONLY
#else
#error "Duplicated definition of O_WRONLY with different values"
#endif
#endif

#define O_WRONLY	0x0001

#ifdef O_RDWR
#if O_RDWR == 0x0002
#undef O_RDWR
#else
#error "Duplicated definition of O_RDWR with different values"
#endif
#endif
#define O_RDWR		0x0002

#define O_APPEND	(1 << 2) //0x0008  Change to match blunk's posix.h
#define O_SYNC		(1 << 7) //0x0010 Change to match blunk's posix.h
#define O_NONBLOCK	(1 << 6)   //0x0080 Change to match blunk's posix.h
#define O_CREAT     (1 << 3)   //0x0100 change to match blunk's posix.h
#define O_TRUNC		(1 << 5)   //0x0200 change to match blunk's posix.h
#define O_EXCL		(1 << 4)   //0x0400 change to match blunk's posix.h

#define O_NOCTTY	0x0800	
#define FASYNC		0x1000	
#define O_LARGEFILE	0x2000	
#define O_DIRECT	0x8000	
#define O_DIRECTORY	0x10000	
#define O_NOFOLLOW	0x20000	

#define O_NDELAY	O_NONBLOCK

#define F_DUPFD		0	
#define F_GETFD		1	
#define F_SETFD		2	
#define F_GETFL		3	
#define F_SETFL		4	
#define F_GETLK		14
#define F_SETLK		6
#define F_SETLKW	7

#define F_SETOWN	24	
#define F_GETOWN	23	
#define F_SETSIG	10	
#define F_GETSIG	11	

#define FD_CLOEXEC	1	

# define POSIX_FADV_NORMAL	0 
# define POSIX_FADV_RANDOM	1 
# define POSIX_FADV_SEQUENTIAL	2 
# define POSIX_FADV_WILLNEED	3 
# define POSIX_FADV_DONTNEED	4 
# define POSIX_FADV_NOREUSE	5

/* no flock structure for Threadx at this time */

#endif

#ifdef __cplusplus
}
#endif

#endif
