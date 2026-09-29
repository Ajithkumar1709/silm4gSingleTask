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
* Title: pmu_tests.h
*
* Filename: pmu_tests.h
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

#ifndef _PMU_TESTS_H_
#define _PMU_TESTS_H_


#include "global_types.h"
#include "pmu_config.h"
#include "intc.h"

void                   PMUIndependentAPITest(void);
void                   i2ctest(void);
void                   forYossi(void);
void                   PMUEnablePeripheralsClocks(void);
void                   PMUIndependentAPITest_2(void);
void                   PMULastResetTest(void);
void                   PMUGlobalTest(void);
void                   PMUSleepControlTest(void);
void                   HWWakeupInterruptHandler(INTC_InterruptInfo interruptInfo);
void                   PMUphase2Init_DEBUG(void);
void                   PMUMemoryWhileDrowsyTest(void);
void 				   PMUHighFreqCounterTest(void);
void				   PMUHighFreqCounterTestIsr(void);

#endif  /* _PMU_TESTS_H_ */
