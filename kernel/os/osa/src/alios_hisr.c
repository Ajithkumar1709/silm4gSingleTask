#include "bsp.h"
#include "bsp_hisr.h"
#include <stdio.h>
#include <string.h>
#include "gbl_types.h"
#include "intc.h"
#include "k_api.h"
#include "osa.h"
#include "alios_hisr.h"
#include "osa_ali.h"
#include "osa_internals.h"
#include "diag.h"
#include "csw_mem.h"
#include "platform_nvm.h"
#include "utilities.h"


/*
 * This file is copied from tx_hisr.c of ThreadX.
 * Port functions to AliOS APIs.
 */



/*
 * Macros.
 */
#define     MALLOC_REF(rEF,sIZE)                    \
    {                                               \
        rEF = (OsaRefT)OsaMemAlloc( NULL, sIZE ) ;  \
                                                    \
        if ( ! rEF )                                \
        {                                           \
            OSA_ASSERT(0) ;                         \
            return OS_NO_MEMORY ;                   \
        }                                           \
                                                    \
        memset( (void *)rEF, 0, sIZE ) ;            \
    }


#define     MALLOC(tYPE,pTR,sIZE)                   \
    {                                               \
        pTR = (tYPE)OsaMemAlloc( NULL, sIZE ) ;     \
                                                    \
        if ( ! pTR )                                \
        {                                           \
            OSA_ASSERT(0) ;                         \
            return OS_NO_MEMORY ;                   \
        }                                           \
    }

#define     FREE_REF_AND_RETURN_STATUS(sTATUS,rEF,tYPE) \
    {                                                   \
        RETURN_STATUS_ON_FAILURE(sTATUS,OS_SUCCESS) ;   \
                                                        \
        CacheCleanMemory( (void *)rEF, sizeof(tYPE) ) ; \
        OsaMemFree( (void *)rEF ) ;                     \
                                                        \
        return OS_SUCCESS ;                             \
    }    /*  Need to Clean Cache bucause of Nucleus *_id magic number. */

#define RHINO_TASK_AUTOSTART  1
#define RHINO_NO_TIME_SLICE   0


void hisr_thread(void *entry_input){
	RHINO_HISR *rhino_hisr = (RHINO_HISR *)entry_input;
	UINT32 status;

	while(1){
		status = krhino_sem_take(&(rhino_hisr->hisr_semaphore), RHINO_WAIT_FOREVER);
		if(status == RHINO_SUCCESS){
//			uart_printf("Hey, we are going to call the hisr entry function(%s)\r\n", tx_hisr->tx_hisr_thread.tx_thread_name);
			rhino_hisr->hisr_entry(rhino_hisr->hisr_entry_parameter);
		}
//		uart_printf("thread name: %s, status = %u\r\n", tx_hisr->tx_hisr_thread.tx_thread_name, status);
	}

}


UINT32 _ali_hisr_create(RHINO_HISR *hisr_ptr, CHAR * name, VOID(* entry_function)(UINT32),
				UINT32 entry_input, UINT8 priority){
	char *pName = NULL;
	UINT32 status = RHINO_SUCCESS;
	UINT32 stack_level = 0, stack_size = 0;

    stack_level = priority & 0xF0;
    priority = priority & 0x0F;

	if(priority > 2)
		OSA_ASSERT(0); //HISR Priority should be 0~2

	hisr_ptr->hisr_entry_parameter = entry_input;
	hisr_ptr->hisr_entry = entry_function;

	MALLOC( char *, pName, strlen(name)+6);
    sprintf( pName, "%s-hisr",  name) ;
	hisr_ptr->hisr_name = pName;

	hisr_ptr->abs_task.aos_thread_id = ALI_THREAD_ID;

	status = krhino_sem_create(&(hisr_ptr->hisr_semaphore), pName, 0);

	OSA_ASSERT(status == RHINO_SUCCESS);

	switch(stack_level)
	{
        case HISR_STACK_LEVEL_1:
        {
            stack_size = HISR_STACK_LEVEL_1_SIZE;
            break;
        }

        case HISR_STACK_LEVEL_2:
        {
            stack_size = HISR_STACK_LEVEL_2_SIZE;
            break;
        }

        case HISR_STACK_DEFAULT_LEVEL:
        default:
        {
            stack_size = HISR_STACK_SIZE;
            break;
        }
	}

	MALLOC(char *, hisr_ptr->hisr_stack_start, stack_size);

	status = krhino_task_create(&(hisr_ptr->abs_task.hisr_task), pName, (void *)hisr_ptr,
				priority, RHINO_NO_TIME_SLICE, (cpu_stack_t *)hisr_ptr->hisr_stack_start,
				AOS_STACK_SIZE(stack_size), hisr_thread, RHINO_TASK_AUTOSTART);

	OSA_ASSERT(status == RHINO_SUCCESS);

	return status;

}


UINT32 _ali_hisr_delete(RHINO_HISR *hisr_ptr){
	UINT32 status1, status2;

	OSA_ASSERT(hisr_ptr);

	status1 = krhino_task_del(&(hisr_ptr->abs_task.hisr_task));
	status2 = krhino_sem_del(&(hisr_ptr->hisr_semaphore));

	OsaMemFree(hisr_ptr->hisr_stack_start);
	OsaMemFree(hisr_ptr->hisr_name);

	if(status1 == RHINO_SUCCESS && status2 == RHINO_SUCCESS){
		hisr_ptr->abs_task.aos_thread_id = 0;
		return RHINO_SUCCESS;
	} else
		return RHINO_KOBJ_DEL_ERR;
}

UINT32 _ali_hisr_activate(RHINO_HISR *hisr_ptr){
	uint32_t callerAddress ;

#if defined(__ARMCC_VERSION)
	callerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;  //  Keep first.
#else
	callerAddress = 0;
#endif

	OSA_ASSERT(hisr_ptr);

	extern uint32_t EEHandlerFlag;

	if(EEHandlerFlag)
	{
		uart_printf("--- %s:0x%x (%s) ---\r\n",
			__FUNCTION__,
			callerAddress,
			hisr_ptr->hisr_name);
		return RHINO_SUCCESS;
	}

	return krhino_sem_give(&(hisr_ptr->hisr_semaphore));
}


