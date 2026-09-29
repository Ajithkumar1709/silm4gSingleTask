/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : osa_common_run.c
Description : Common code for the OS Abstraction Layer API.
              This file contains the functions that are usualy used during the run phase.
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
#include "osa.h"
#include "osa_mem.h"
#include "osa_internals.h"

#include "diag.h"
#include <utilities.h>

/*
 * Conversion Functions from OSAApi to OsaApi
 */
OSA_STATUS OSAMsgQSend( OSMsgQRef Ref, UINT32 size, UINT8 *msgPtr, UINT32 timeout )
{
	UINT32 callerAddress ;

    OsaMsgQSendParamsT
        Params ;

#if defined(__ARMCC_VERSION)
					callerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;  //  Keep first.
#else
					callerAddress = 0;
#endif


    memset( &Params, 0, sizeof(Params) ) ;

    Params.msgPtr = (void *)msgPtr ;
    Params.size = size ;
    Params.timeout = timeout ;

	if(Ref == NULL)
	{
		RTI_LOG("%s, caller 0x%x", __FUNCTION__, callerAddress);
	}

    return OsaMsgQSend( (OsaRefT)Ref, &Params ) ;
}

OSA_STATUS OSAMsgQRecv( OSMsgQRef Ref, UINT8 *msgPtr, UINT32 size, UINT32 timeout )
{
    OsaMsgQRecvParamsT
        Params ;

    memset( &Params, 0, sizeof(Params) ) ;

    Params.msgPtr = (void *)msgPtr ;
    Params.size = size ;
    Params.timeout = timeout ;

    return OsaMsgQRecv( (OsaRefT)Ref, &Params ) ;
}

OSA_STATUS OSAFlagWait( OSFlagRef Ref, UINT32 mask, UINT32 operation, UINT32 *flags, UINT32 timeout )
{
    OsaFlagWaitParamsT
        Params ;

    memset( &Params, 0, sizeof(Params) ) ;

    Params.mask = mask ;
    Params.operation = operation ;
    Params.flags = flags ;
    Params.timeout = timeout ;

    return OsaFlagWait( (OsaRefT)Ref, &Params ) ;
}

OSA_STATUS OSATimerStart( OSATimerRef Ref, UINT32 initialTime,
                          UINT32 rescheduleTime, void (*callBackRoutine)(UINT32),
                          UINT32 timerArgc )
{
    OsaTimerParamsT
        Params ;

    memset( &Params, 0, sizeof(Params) ) ;

    Params.initialTime = initialTime ;
    Params.rescheduleTime = rescheduleTime ;
    Params.callBackRoutine = callBackRoutine ;
    Params.timerArgc = timerArgc ;

    return OsaTimerStart( (OsaRefT)Ref, &Params ) ;
}

OSA_STATUS OSAMemPoolAlloc( OSPoolRef poolRef, UINT32 size, void **mem, UINT32 timeout)
{
    OsaRefT
        OsaRef = (OsaRefT)poolRef ;
	UINT32 callerAddress ;


#if defined(__ARMCC_VERSION)
	callerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;  //  Keep first.
#else
	callerAddress = 0;
#endif

    *mem = OsaMemAlloc( OsaRef, size ) ;

    if ( *mem )
    {
		OsaMemSetUserParamsFast(*mem, (UINT32)OsaCurrentThreadRef(), callerAddress);
        return OS_SUCCESS ;
    }
    if ( OsaRef != OsaMemGetPoolRef("DTCMPool",NULL,NULL) )
        return OS_NO_MEMORY ;

    DIAG_FILTER( OSA, OsaMem, NO_DTCM, DIAG_WARNING )
    diagPrintf( "No available memory in DTCM, using the Default Pool" ) ;

    *mem = OsaMemAlloc( OsaMemGetDefaultPoolRef(), size ) ;
	if ( *mem  )
	{
		OsaMemSetUserParamsFast(*mem, (UINT32)OsaCurrentThreadRef(), callerAddress);
	}

    return *mem ? OS_SUCCESS : OS_NO_MEMORY ;
}

OSA_STATUS  OSAMemPoolFree(OSPoolRef poolRef, void* mem)
{
    OsaMemFree( mem ) ;

    return OS_SUCCESS ;
}
