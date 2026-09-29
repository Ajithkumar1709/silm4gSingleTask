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

/*********************************************************************
*                      M O D U L E     B O D Y                       *
**********************************************************************
*                                                                    *
* Title: CGPIO (Comm side General Purpose Input Output) HW Header File *
*                                                                    *
* Author: Idan Hemdat		                                         *
*                                                                    *
* Target, subsystem: Common Platform, HAL                            *
*                                                                    *
*                                                                    *
*********************************************************************/


#ifndef _CGPIO_HW_H_
#define _CGPIO_HW_H_

#define GPIO_REGISTERS_BASE				0xF0240050
#define GPIO_REGISTERS_AMOUNT				2
#define WRST_WR_BASE						0xF0240000
#define WRST_RD_BASE						0xF0240004

typedef volatile struct
{
	volatile UINT32 IN[GPIO_REGISTERS_AMOUNT];
	volatile UINT32 DIR[GPIO_REGISTERS_AMOUNT];
	volatile UINT32 OUT[GPIO_REGISTERS_AMOUNT];
	volatile UINT32 PU[GPIO_REGISTERS_AMOUNT];
	volatile UINT32 PD[GPIO_REGISTERS_AMOUNT];
	volatile UINT32 CM[GPIO_REGISTERS_AMOUNT];

}GPIO_Registers;



#endif //_CGPIO_HW_H_
