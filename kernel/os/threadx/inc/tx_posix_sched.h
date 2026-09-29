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
/*    sched.h                                             PORTABLE C      */
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

#ifndef _SCHED_H
#define _SCHED_H

#ifdef __cplusplus
extern "C" {
#endif

struct sched_param 
{
    INT     sched_priority;
};


#define   SCHED_FIFO                    0
#define   SCHED_RR                      1
#define   SCHED_OTHER                   SCHED_RR

INT                   sched_get_priority_max(INT policy);
INT                   sched_get_priority_min(INT policy);

INT    sched_yield(void);

#ifdef __cplusplus
}
#endif

#endif
