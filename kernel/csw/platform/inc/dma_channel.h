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
/* Title: 																*/
/*                                                                      */
/* Filename: Dma_channel.h     		                                    */
/*                                                                      */
/* Author: Rony Hanina                                                  */
/*																		*/
/* Target, subsystem: Common Platform, HAL                              */
/************************************************************************/
#ifndef _DMA_CHANNEL_H_
#define _DMA_CHANNEL_H_
/***************************************************************************/


#define CLCD_0_DMA_CHANNEL                  0
#define CLCD_1_DMA_CHANNEL                  1
#define WCIPHER_DMA_CHANNEL                 2
#define CAMIF_DMA_CHANNEL               	3
#define CAMIF_DMA_U_CHANNEL                 4
#define CAMIF_DMA_V_CHANNEL                 5
#define SSP0_TX_DMA_CHANNEL                 6
#define SSP0_RX_DMA_CHANNEL                 7
#define SSP1_TX_DMA_CHANNEL                 8
#define SSP1_RX_DMA_CHANNEL                 9

#if !defined (INTEL_2CHIP_PLAT)

#define SSP2_TX_DMA_CHANNEL                 10
#define SSP2_RX_DMA_CHANNEL                 11
#define SSP3_TX_DMA_CHANNEL                 12
#define SSP3_RX_DMA_CHANNEL                 13

#ifdef SSP_TEST_ENABLE
#define GSSP0_TX_DMA_CHANNEL                 19
#define GSSP0_RX_DMA_CHANNEL                 20
#define GSSP1_TX_DMA_CHANNEL                 21
#define GSSP1_RX_DMA_CHANNEL                 22
#endif

#if(1) // defined(HERMON_MVT)           // required by ME in order to compile OK
#define	ME_SRC_FRAME_COPY_FROM_SDRAM_2_SRAM_DMA_CHANNEL		(14)
#define	ME_REF_FRAME_COPY_FROM_SDRAM_2_SRAM_DMA_CHANNEL		(14)
#define ME_LUT_DMA_CHANNEL       							(14)
#define ME_FBRC_FBSC_DMA_CHANNEL       						(15)
#define	ME_OUTPUT_DMA_CHANNEL								(14)
#endif

#define DIAG_USB_DMA_TX_CH_NUM             16  // 0-3 and 16-19 have highest priority
#define MMCSD_TX_DMA_CHANNEL		17	//MMCSD DVT test
#define MMCSD_RX_DMA_CHANNEL		18	//MMCSD DVT test
//#define DIAG_USB_DMA_RX_CH_NUM             14  // RX with no DMA

#else /*INTEL_2CHIP_PLAT*/

#define DIAG_USB_DMA_TX_CH_NUM             10  // 0-3 and 16-19 have highest priority
//#define DIAG_USB_DMA_RX_CH_NUM             14  // RX with no DMA

#ifdef PHS_SW_DEMO_TTC    
#define USIM1_TRANSMIT_DMA_CHANNEL         11 /*DMA_USIM1_TRANSMIT*/
#define USIM1_RECEIVE_DMA_CHANNEL          12 /*DMA_USIM1_RECEIVE*/
#else
#define MSL_RX1_DMA_CHANNEL                11 /*DMA_MSL_RECEIVE_1*/
#define MSL_TX1_DMA_CHANNEL                12 /*DMA_MSL_TRANSMIT_1*/
#define MSL_RX2_DMA_CHANNEL                13 /*DMA_MSL_RECEIVE_2*/
#define MSL_TX2_DMA_CHANNEL                14 /*DMA_MSL_TRANSMIT_2*/
#define MSL_RX3_DMA_CHANNEL                15 /*DMA_MSL_RECEIVE_3 */
#define MSL_TX3_DMA_CHANNEL                16 /*DMA_MSL_TRANSMIT_3*/
#define MSL_RX4_DMA_CHANNEL                17 /*DMA_MSL_RECEIVE_4*/
#define MSL_TX4_DMA_CHANNEL                18 /*DMA_MSL_TRANSMIT_4*/
#endif

#if defined (INTEL_2CHIP_PLAT_BVD) || defined (_TAVOR_BOERNE_) /*APP_SIDE*/
#define MSL_RX5_DMA_CHANNEL                19 /*DMA_MSL_RECEIVE_5*/
#define MSL_TX5_DMA_CHANNEL                20 /*DMA_MSL_TRANSMIT_5*/
#define MSL_RX6_DMA_CHANNEL                21 /*DMA_MSL_RECEIVE_6*/
#define MSL_TX6_DMA_CHANNEL                22 /*DMA_MSL_TRANSMIT_6*/

#if !defined (_TAVOR_BOERNE_) || (NO_APLP==0)
#define I2S_RX_DMA_CHANNEL                 23
#define I2S_TX_DMA_CHANNEL                 24
#else
#define MSL_RX7_DMA_CHANNEL                23 /*DMA_MSL_RECEIVE_7 */
#define MSL_TX7_DMA_CHANNEL                24 /*DMA_MSL_TRANSMIT_7*/
#define I2S_RX_DMA_CHANNEL                 SSP3_TX_DMA_CHANNEL
#define I2S_TX_DMA_CHANNEL                 SSP3_RX_DMA_CHANNEL
#endif
#endif //(INTEL_2CHIP_PLAT_BVD)

#define SSP2_TX_DMA_CHANNEL                25
#define SSP2_RX_DMA_CHANNEL                26
#define SSP3_TX_DMA_CHANNEL                27
#define SSP3_RX_DMA_CHANNEL                28

#define MMCSD_TX_DMA_CHANNEL               29
#define MMCSD_RX_DMA_CHANNEL               30

#endif /*INTEL_2CHIP_PLAT*/

#define TCU_DIRQ_PX_VOTE_DUMMY_CHANNEL		31

/***************************************************************************/
/***************************************************************************/
#endif /* _DMA_CHANNEL_H_ */
