/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : osa_common_init.c
Description : Common code for the OS Abstraction Layer API.
              This file contains the functions that are usualy used during the init phase.
              The split into 2 files is done to be able to located
              only the "run" functions in a faster memory.

Notes       :

Copyright (c) 2008 Marvell MISL. All Rights Reserved
=========================================================================== */

/*
 * Include File.
 */
#include <string.h>

#include "gbl_types.h"
#include "intc.h"
#define     _OSA_COMMON_INIT
#include "osa.h"
#include "osa_internals.h"
#include <utilities.h>

OsaRefT
    OsaIsrTable[INTC_MAX_INTERRUPT_SOURCES] ;

#if defined (PLAT_USE_THREADX)
static char osaVersionStr[] = "ThreadX R-5.1";
#elif defined (PLAT_USE_ALIOS)
static char osaVersionStr[] = "AliOS R-3.0.0";
#else
static char osaVersionStr[] = "N/A";
#endif
/* ---------------------------------------------------------------------------
Function    : OsaGetVersion
Description : Returns the version of the osa package
Parameters  : none
Returns     : pointer to a null-terminated char array
Notes       :
--------------------------------------------------------------------------- */
char *OsaGetVersion ( void )
{
    return(osaVersionStr);
}

/***********************************************************************
 *
 * Name:        OsaGetClockRate
 *
 * Description: Get the current system clock rate.
 *
 * Parameters:
 *
 * Returns:     UNIT32  - current clock rate (ms / tick)
 *
 * Notes:
 *
 ***********************************************************************/
UINT32 OsaGetClockRate( void *pForFutureUse )
{
    return (UINT32)OSA_TICK_FREQ_IN_MILLISEC ;
}

OSA_STATUS OSATaskCreateEx( OSTaskRef *pRef, void* stackPtr,
                        UINT32 stackSize, UINT8 priority, CHAR *name,
                        void  (*taskStart)(void*), void *argv  )
{
    OsaTaskCreateParamsT
        Params ;

    memset( &Params, 0, sizeof(Params) ) ;

    Params.name = (char *)name ;
    Params.entry = taskStart ;
    Params.argv = argv ;
    Params.stackPtr = (UINT32 *)stackPtr ;
    Params.stackSize = stackSize ;
    Params.priority = priority ;

    return OsaTaskCreateEx( (OsaRefT *)pRef, &Params ) ;
}


/*
 * Conversion Functions from OSAApi to OsaApi
 */
OSA_STATUS OSATaskCreate( OSTaskRef *pRef, void* stackPtr,
                        UINT32 stackSize, UINT8 priority, CHAR *name,
                        void  (*taskStart)(void*), void *argv  )
{
    OsaTaskCreateParamsT
        Params ;

    memset( &Params, 0, sizeof(Params) ) ;

    Params.name = (char *)name ;
    Params.entry = taskStart ;
    Params.argv = argv ;
    Params.stackPtr = (UINT32 *)stackPtr ;
    Params.stackSize = stackSize ;
    Params.priority = priority ;

    return OsaTaskCreate( (OsaRefT *)pRef, &Params ) ;
}

OSA_STATUS OSASemaphoreCreate( OSSemaRef *pRef, UINT32 initialCount, UINT8 waitingMode )
{
    OsaSemaphoreCreateParamsT
        Params ;
	UINT32 callerAddress =NULL;
	callerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;
    memset( &Params, 0, sizeof(Params) ) ;

    Params.initialCount = initialCount ;
    Params.waitingMode = waitingMode ;

    return OsaSemaphoreCreate( (OsaRefT *)pRef, &Params, callerAddress);
}

OSA_STATUS OSASemaphoreCreateExt( OSSemaRef *pRef, UINT32 initialCount, UINT32 maximumCount, UINT8 waitingMode )
{
    OsaSemaphoreCreateParamsT
        Params ;
	UINT32 callerAddress =NULL;
	callerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;
    memset( &Params, 0, sizeof(Params) ) ;

    Params.initialCount = initialCount ;
    Params.maximumCount = maximumCount ;
    Params.waitingMode = waitingMode ;

    return OsaSemaphoreCreate( (OsaRefT *)pRef, &Params, callerAddress);
}


OSA_STATUS OSAMutexCreate( OSMutexRef *pRef, UINT8 waitingMode )
{
    OsaMutexCreateParamsT
        Params ;
	UINT32 callerAddress =NULL;
	callerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;
    memset( &Params, 0, sizeof(Params) ) ;

    Params.waitingMode = waitingMode ;
	Params.inherit = TRUE;

    return OsaMutexCreate( (OsaRefT *)pRef, &Params ,callerAddress) ;
}
#if 0
OSA_STATUS OSAIsrCreate(UINT32 isrNum, void (*fisrRoutine)(UINT32),
                   void (*sisrRoutine)(void))
{
    OsaIsrCreateParamsT
        Params ;

    if ( isrNum >= INTC_MAX_INTERRUPT_SOURCES )
    {
        OSA_ASSERT(0) ;
        return OS_INVALID_VECTOR ;
    }

    memset( &Params, 0, sizeof(Params) ) ;

    Params.intSource = isrNum ;
    Params.fisrRoutine = fisrRoutine ;
    Params.sisrRoutine = sisrRoutine ;
    Params.priority = OSA_SISR_MED_PRIORITY ;


    return OsaIsrCreate( &OsaIsrTable[isrNum], &Params ) ;
}
#endif
OSA_STATUS OSAMsgQCreate( OSMsgQRef *pRef,
#if defined (OSA_QUEUE_NAMES)
                            char *name,
#endif
                            UINT32 maxSize, UINT32 maxNumber, UINT8 waitingMode )
{
    OsaMsgQCreateParamsT
        Params ;
	UINT32 callerAddress=NULL ;
	callerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;
    memset( &Params, 0, sizeof(Params) ) ;

    Params.maxSize = maxSize ;
    Params.maxMsg = maxNumber ;
#if defined (OSA_QUEUE_NAMES)
    Params.name = (char *)name ;
#endif
    Params.waitingMode = waitingMode ;

    return OsaMsgQCreate( (OsaRefT *)pRef, &Params,callerAddress ) ;
}

OSA_STATUS OSAMailboxQCreate( OSMailboxQRef *pRef,
#ifdef OSA_QUEUE_NAMES
                                char *name,
#endif
                                UINT32 maxNumber, UINT8 waitingMode )
{
    OsaMailboxQCreateParamsT
        Params ;

    memset( &Params, 0, sizeof(Params) ) ;

    Params.maxMsg = maxNumber ;
#ifdef OSA_QUEUE_NAMES
    Params.name = (char *)name ;
#endif
    Params.waitingMode = waitingMode ;

    return OsaMailboxQCreate( (OsaRefT *)pRef, &Params ) ;
}

OSA_STATUS OSAMemPoolCreate( OSPoolRef *poolRef, UINT32 poolType, UINT8 *poolBase, UINT32 poolSize, UINT32 partitionSize, UINT8 waitingMode )
{
    OsaRefT
        OsaRef ;

    OsaMemCreateParamsT
        Params ;

    OSA_ASSERT(poolRef) ;

/*
 * Case when we want to create a pool within a pool.
 */
    OsaRef = OsaMemGetPoolRef( NULL, (void *)poolBase, NULL ) ;

    if ( OsaRef )
    {
        OsaMemFree( poolBase ) ;
        *poolRef = OsaRef ;
        return OS_SUCCESS ;
    }

    memset( (void *)&Params, 0, sizeof(Params) ) ;

/*
 * DTCM Pool.
 */
#if (defined FLAVOR_COM)
    {
        extern UINT32
            Image$$DDR_DTCM$$Base,
            Image$$DDR_DTCM$$ZI$$Limit,
            Image$$DDR_DTCM_ENDMARKER$$Base ;

        if ( (UINT32)&Image$$DDR_DTCM$$Base <= (UINT32)poolBase  &&  (UINT32)poolBase <= (UINT32)&Image$$DDR_DTCM_ENDMARKER$$Base )
        {
            OsaRef = OsaMemGetPoolRef( "DTCMPool", NULL, NULL ) ;   //  Try D-TCM pool.

            if ( ! OsaRef )
            {
                Params.name = "DTCMPool" ;
                Params.poolBase = NULL ;        //  Pool header will be taken from the default pool.
                Params.poolSize = 0 ;
                OSA_ASSERT( OS_SUCCESS == OsaMemCreatePool(&OsaRef,&Params) ) ;

                OsaMemAddMemoryToPool( OsaRef, (void *)&Image$$DDR_DTCM$$ZI$$Limit, (UINT32)&Image$$DDR_DTCM_ENDMARKER$$Base-(UINT32)&Image$$DDR_DTCM$$ZI$$Limit, NULL ) ;
            }

            *poolRef = OsaRef ;
            return OsaMemAddMemoryToPool( OsaRef, (void *)poolBase, poolSize, NULL ) ;
        }
    }
#endif

/*
 * Heap.
 */
    if ( ! OsaMemGetDefaultPoolRef() )
    {
        Params.name = "Heap" ;
        Params.poolBase = (void *)poolBase ;
        Params.poolSize = poolSize ;
        OSA_ASSERT( OS_SUCCESS == OsaMemCreatePool(&OsaRef,&Params) ) ;
        OsaMemSetDefaultPool( OsaRef ) ;
    }

/*
 * Old OSAMemPools
 */
    else
    {
    #if (defined FLAVOR_COM)    //  Untill the csw_mem change set will be entered.
        OsaRef = OsaMemGetPoolRef( "Old-OSAMemPools", NULL, NULL ) ;   //  Try old OSAMemPools.

        if ( ! OsaRef )
    #endif
        {
            Params.name = "Old-OSAMemPools" ;
            Params.poolBase = NULL ;        //  Pool header will be taken from the default pool.
            Params.poolSize = 0 ;
            OSA_ASSERT( OS_SUCCESS == OsaMemCreatePool(&OsaRef,&Params) ) ;
        }
        OsaMemAddMemoryToPool( OsaRef, (void *)poolBase, poolSize, NULL ) ;
    }

    *poolRef = OsaRef ;

    return OS_SUCCESS ;
}
OSA_STATUS OSAMemPoolCreateExt( OSPoolRef *poolRef, UINT32 poolType, UINT8 *poolBase, UINT32 poolSize, UINT32 partitionSize, UINT8 waitingMode, char *poolName )
{
	OsaMemCreateParamsT Params ;
	OsaRefT OsaRef ;

	memset(&Params,0,sizeof(OsaMemCreateParamsT));
	Params.name = poolName ;
	Params.poolBase = NULL ;  //  Pool header will be taken from the default pool.
	Params.poolSize = 0 ;

	OSA_ASSERT( OS_SUCCESS == OsaMemCreatePool(&OsaRef,&Params));
	*poolRef = OsaRef;

	return OsaMemAddMemoryToPool( OsaRef, (void *)poolBase,poolSize, NULL ) ;
}

OSA_STATUS OsaGetMaxThreadCount(unsigned long *maxCnt, void *pForFutureUse )
{
	OSA_ASSERT(maxCnt);
	*maxCnt =RTI_THREAD_ARRAY_SIZE;
	return OS_SUCCESS ;
}

