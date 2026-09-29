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

//
// PmDsp.h
// DSP reset and PLL2 control
//
#include "global_types.h"

// MSA reset
void pmDspReset(void);

// MSA reset with clock mode setting
void pmDspResetWithClockModeSet(UINT8 multiplier, BOOL flashDiv2, UINT8 flashWaitState);

// Set MSA flash wait-state
void pmSetMsaFlashWaitStates(UINT32 value);

// RECOMMENDED MODES
#if defined(_HERMON_B0_SILICON_)
/*****************************************************************************************************************/
/* NOTE ON MSF WAIT-STATE SETTING
   WS = roundup (Kmsf / ( 1/ MSF Frequency))
      Kmsf = 33 nsec (MSF Sense time)
	  MSF Frequency = MSA_core_freq/2 provided the second parameter below is TRUE
   WS = roundup (Kmsf*MSA_core_freq/2) = roundup(16.5*MSA_core_freq)
*/
#define MSA_RESET_CLOCK_MODE_182  pmDspResetWithClockModeSet(0x1C, TRUE,  3)  /*Optimal wait-state for 182/2=91MHz*/
#define MSA_RESET_CLOCK_MODE_104  pmDspResetWithClockModeSet(0xFF, FALSE, 4)  /*Default at PLL1*/
/*****************************************************************************************************************/
#endif


