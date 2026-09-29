/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
INTEL CONFIDENTIAL
Copyright 2006 Intel Corporation All Rights Reserved.
The source code contained or described herein and all documents related to the source code ("Material") are owned
by Intel Corporation or its suppliers or licensors. Title to the Material remains with Intel Corporation or
its suppliers and licensors. The Material contains trade secrets and proprietary and confidential information of
Intel or its suppliers and licensors. The Material is protected by worldwide copyright and trade secret laws and
treaty provisions. No part of the Material may be used, copied, reproduced, modified, published, uploaded, posted,
transmitted, distributed, or disclosed in any way without Intel's prior express written permission.

No license under any patent, copyright, trade secret or other intellectual property right is granted to or
conferred upon you by disclosure or delivery of the Materials, either expressly, by implication, inducement,
estoppel or otherwise. Any license under such intellectual property rights must be express and approved by
Intel in writing.
-------------------------------------------------------------------------------------------------------------------*/

/*******************************************************************************
*               MODULE HEADER FILE
********************************************************************************
* Title: pmu.h
*
* Filename: pmu.h
*
* PMU Header file
*
* Authors:    Yabbo Shuki
*
* Description:
*
* Last Updated:
*
* Notes:
*******************************************************************************/

#ifndef _PMU_H_
#define _PMU_H_

#include "global_types.h"
#include "syscfg.h"
#define PMU_API_DECOUPLING_STAGE_1
#if defined(PERIPHERAL_CLOCKS_VIA_PMU_API)

#ifdef _PMU_NO_EXTERN_
#define  MODULE_ID DIAGM_PMU_H
#endif
/*----------- Global defines -------------------------------------------------*/

/*----------- Global macro definitions ---------------------------------------*/

/*----------- Global type definitions ----------------------------------------*/



#endif


typedef enum
{
	PMU_RC_WRONG_VALUE = -100,
    PMU_RC_OK = 0,
	PMU_RC_POR,
	PMU_RC_EMR,
    PMU_RC_WDTR = (PMU_RC_EMR+2)
}PMU_ReturnCode;



/*----------- Global function prototypes -------------------------------------*/
PMU_ReturnCode         PMUPhase1Init(void);                       /* implemented in pmu.c */


#undef EXTERN
#endif  /* _PMU_H_ */

