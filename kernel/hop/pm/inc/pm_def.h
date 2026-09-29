/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/************************************************************************/
/*  COPYRIGHT (C) 2002 Intel Corporation.                               */
/*                                                                      */
/*  This file and the software in it is furnished under                 */
/*  license and may only be used or copied in accordance with the terms */
/*  of the license. The information in this file is furnished for       */
/*  informational use only, is subject to change without notice, and    */
/*  should not be construed as a commitment by Intel Corporation.       */
/*  Intel Corporation assumes no responsibility or liability for any    */
/*  errors or inaccuracies that may appear in this document or any      */
/*  software that may be provided in association with this document.    */
/*  Except as permitted by such license, no part of this document may   */
/*  be reproduced, stored in a retrieval system, or transmitted in any  */
/*  form or by any means without the express written consent of Intel   */
/*  Corporation.                                                        */
/*                                                                      */
/* Title: Power Management definitions Header File                      */
/*                                                                      */
/* Filename: pm_def.h                                                   */
/*                                                                      */
/* Author:   Raviv Levi                                                 */
/*                                                                      */
/* Project, Target, subsystem: Tavor, Arbel, HOP     					*/
/*																		*/
/* Remarks: This file contains definitions used by the entire           */
/*          communication power management system                       */
/*    													                */
/* Created: 1/1/2006                                                    */
/*                                                                      */
/* Modified:                                                            */
/************************************************************************/


#ifndef _PM_DEF_H_
#define _PM_DEF_H_
    
#include "powerManagement.h"
    
//#if defined (PM_DEBUG_MODE_ENABLED)
#if 0
		// Check if the power state is indeed expected after LPS recovery.    
		#define PM_CHECK_RECOVERY_PS(POWERsTATE)								\
			{ if (((PM_PS_OPERATIONAL_D0 == POWERsTATE ) && (PM_PS_D4 == POWERsTATE)))		\
				{																\
					ASSERT(FALSE);												\
				}																\
			}
	#else	//PM_DEBUG_MODE_ENABLED
		#define PM_CHECK_RECOVERY_PS(POWERsTATE)		/* Do nothing */						

	#endif	//PM_DEBUG_MODE_ENABLED
	
	// Invalid value definition.
	#define PM_INVALID_VALUE				 (0x2BAD2BADUL)

	/*
	 *	Debug Macros
	 */
	#if defined PM_TCM_TEST_ENABLED
		#define PM_DEBUG_TCM_TEST_BEFORE_D2()		CommPMTCMTestBeforeD2()
		#define PM_DEBUG_TCM_TEST_AFTER_D2()		CommPMTCMTestAfterD2()		
		#define PM_DEBUG_TCM_TEST_PROCESS_RESULTS()	CommPMTCMProcessResults()
		#define PM_DEBUG_TCM_TEST_INITIATE()		CommPMTCMTestPhase1Init()

	#else
		#define PM_DEBUG_TCM_TEST_BEFORE_D2()			/* Nothing */
		#define PM_DEBUG_TCM_TEST_AFTER_D2(RESULTSaRR)	/* Nothing */	
		#define PM_DEBUG_TCM_TEST_PROCESS_RESULTS()		/* Nothing */	
		#define PM_DEBUG_TCM_TEST_INITIATE()			/* Nothing */	
	#endif // defined PM_TCM_TEST_ENABLED

   
#endif  /* _PM_DEF_H_ */
