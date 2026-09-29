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

/************************************************************************/
/*                                                                      */
/* Title: BOARD information                               				*/
/*                                                                      */
/* Filename:  board_ecn.h                                              */
/*                                                                      */
/* Authors: Rony Hanina                                                 */
/*                                                                      */
/* Target, subsystem: Common Platform, HAL                              */
/************************************************************************/

#ifndef _BOARD_ECN_H_
#define _BOARD_ECN_H_
/***************************************************************************/

#define EPROM_NO_ECN			(0x0)
#define EPROM_NOTHING_TO_IGNOR	(0x0)

#define EPROM_ECN_1		(0x0001)
#define EPROM_ECN_2		(0x0002)
#define EPROM_ECN_3		(0x0004)
#define EPROM_ECN_4		(0x0008)
#define EPROM_ECN_5		(0x0010)
#define EPROM_ECN_6		(0x0020)
#define EPROM_ECN_7		(0x0040)
#define EPROM_ECN_8		(0x0080)

#define EPROM_ECN_9		(0x0100)
#define EPROM_ECN_10   	(0x0200)
#define EPROM_ECN_11   	(0x0400)
#define EPROM_ECN_12   	(0x0800)
#define EPROM_ECN_13   	(0x1000)
#define EPROM_ECN_14   	(0x2000)
#define EPROM_ECN_15   	(0x4000)
#define EPROM_ECN_16   	(0x8000)

#define EPROM_ECN_TILL_01		(EPROM_ECN_1)
#define EPROM_ECN_TILL_02		(EPROM_ECN_TILL_01 | EPROM_ECN_2)
#define EPROM_ECN_TILL_03		(EPROM_ECN_TILL_02 | EPROM_ECN_3)
#define EPROM_ECN_TILL_04		(EPROM_ECN_TILL_03 | EPROM_ECN_4)
#define EPROM_ECN_TILL_05		(EPROM_ECN_TILL_04 | EPROM_ECN_5)
#define EPROM_ECN_TILL_06		(EPROM_ECN_TILL_05 | EPROM_ECN_6)
#define EPROM_ECN_TILL_07		(EPROM_ECN_TILL_06 | EPROM_ECN_7)
#define EPROM_ECN_TILL_08		(EPROM_ECN_TILL_07 | EPROM_ECN_8)
#define EPROM_ECN_TILL_09		(EPROM_ECN_TILL_08 | EPROM_ECN_9)
#define EPROM_ECN_TILL_10		(EPROM_ECN_TILL_09 | EPROM_ECN_10)
#define EPROM_ECN_TILL_11		(EPROM_ECN_TILL_10 | EPROM_ECN_11)
#define EPROM_ECN_TILL_12		(EPROM_ECN_TILL_11 | EPROM_ECN_12)
#define EPROM_ECN_TILL_13		(EPROM_ECN_TILL_12 | EPROM_ECN_13)
#define EPROM_ECN_TILL_14		(EPROM_ECN_TILL_13 | EPROM_ECN_14)
#define EPROM_ECN_TILL_15		(EPROM_ECN_TILL_14 | EPROM_ECN_15)
#define EPROM_ECN_TILL_16		(EPROM_ECN_TILL_15 | EPROM_ECN_16)
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/



// For A0
#define MB_ECN          (EPROM_ECN_TILL_09)
#define LCD_CAM_ECN     (EPROM_ECN_TILL_02)
#define MICCO_ECN       (EPROM_ECN_TILL_03)
#define DC_35_ECN       (EPROM_ECN_TILL_10)
#define DC_14_ECN       (EPROM_ECN_TILL_10)
#define DC_40_ECN       (EPROM_ECN_TILL_10)
#define MISC_ECN        (EPROM_ECN_TILL_07)
#define KEYPAD_ECN      (EPROM_ECN_TILL_01)
#define TEC_ECN         (EPROM_ECN_TILL_06)
#define MEMORY_ECN      (EPROM_NO_ECN)
#define MAXIM_ECN       (EPROM_ECN_TILL_06)
#define POLARIS_ECN     (EPROM_ECN_TILL_03)
#define POLEG_ECN       (EPROM_ECN_TILL_09)
#define GILON_ECN       (EPROM_ECN_TILL_02)


// For B0
#define DC_14_B0_ECN    (EPROM_ECN_TILL_03)




// For A0
#define MB_IGMOR_ECN          (EPROM_ECN_11 | EPROM_ECN_12)
#define LCD_CAM_IGMOR_ECN     (EPROM_NOTHING_TO_IGNOR)
#define MICCO_IGMOR_ECN       (EPROM_NOTHING_TO_IGNOR)
#define DC_35_IGMOR_ECN       (EPROM_NOTHING_TO_IGNOR)
#define DC_14_IGMOR_ECN       (EPROM_ECN_12)
#define DC_40_IGMOR_ECN       (EPROM_NOTHING_TO_IGNOR)
#define MISC_IGMOR_ECN        (EPROM_NOTHING_TO_IGNOR)
#define KEYPAD_IGMOR_ECN      (EPROM_NOTHING_TO_IGNOR)
#define TEC_IGMOR_ECN         (EPROM_ECN_7 | EPROM_ECN_8 | EPROM_ECN_9 | EPROM_ECN_10 | EPROM_ECN_11)
#define MEMORY_IGMOR_ECN      (EPROM_NOTHING_TO_IGNOR)
#define MAXIM_IGMOR_ECN       (EPROM_ECN_6)
#define POLARIS_IGMOR_ECN     (EPROM_ECN_3)
#define POLEG_IGMOR_ECN       (EPROM_ECN_8)
#define GILON_IGMOR_ECN       (EPROM_NOTHING_TO_IGNOR)




// For B0
#define DC_14_IGMOR_B0_ECN    (EPROM_ECN_2 | EPROM_ECN_4 | EPROM_ECN_5 | EPROM_ECN_6 | EPROM_ECN_7)



/***************************************************************************/
/***************************************************************************/
#endif
