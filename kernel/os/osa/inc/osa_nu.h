/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : osa_nu.h
Description : Definition of OSA Software Layer data types specific to the
              Nucleus OS.

Notes       :

=========================================================================== */
#ifndef _OSA_NU_H
#define _OSA_NU_H

#if (!defined PLAT_USE_THREADX) && (!defined PLAT_USE_ALIOS)
#include "nucleus.h"

/*
 * Data Types.
 */
typedef struct
{
    NU_SEMAPHORE    NuRef ;
    UINT32          maximumCount ;
}
OsaSemaphoreT ;

typedef struct
{
    NU_HISR     NuRef ;
    UINT32      intSource ;
    void        (*fisrRoutine)(UINT32) ;
    void        (*sisrRoutine)(void) ;
}
OsaIsrT ;

/*
 * Defines.
 */
#define     OSA_DUMMY_CRITICAL_SECTION_HANDLE       ((OsaRefT)(~0))
#define     OSA_MSGQ_MSG_SIZE(sIZE)                 ((UNSIGNED)(sIZE + sizeof(UNSIGNED) - 1) / sizeof(UNSIGNED))    /*  Size is in UNSIGNED not bytes. */
#define     OSA_UNINITIALIZED_TIMER                 (~TM_TIMER_ID)

/*
 * Macros.
 */

/*
 * Data.
 */

/*
 * Functions.
 */
BOOL Osa_TranslateErrorCode( char *callerFuncName, STATUS ErrorCode, OSA_STATUS *pOsaStatus ) ;
#endif

#endif
