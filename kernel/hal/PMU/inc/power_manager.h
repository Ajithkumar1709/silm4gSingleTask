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
* Title: XScale power manager
*
* Filename: power_manager.h
*
* API header file
*
* Authors:    Anton Eidelman
*
* Description:
*
* Last Updated:
*
* Notes:
*******************************************************************************/
#ifndef _POWER_MANAGER_H_
#define _POWER_MANAGER_H_

#include "gbl_types.h"

// Mode control constants
typedef enum
{
  PMM_CORE_EN   = 1,
  PMM_PXSD_EN   = 2,
  PMM_DRSY_EN   = 4,
  PMM_VCOFF_EN  = 8,
  PMM_DONT_WAKE_MEMC_WITH_PX = 0x10,
  PMM_NO_TIMER_RESCHEDULING  = 0x100,
  PMM_NO_APB_SHUTDOWN        = 0x200,
  PMM_NO_PX_MEMC_OFF         = 0x400
} PmMode_E;

#define PMM_ALL_EN (PMM_CORE_EN|PMM_PXSD_EN|PMM_DRSY_EN|PMM_VCOFF_EN)
#define PMM_NONE_EN (0)

void pmActivate(void);

void pmDeactivate(void);

void 	pmModeSet(UINT32 mode);            // Supply OR-combined PmMode_E values
UINT32	pmModeGet(void);

#endif
