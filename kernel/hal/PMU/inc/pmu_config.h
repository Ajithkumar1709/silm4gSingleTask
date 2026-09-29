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

#ifndef _PMU_CONFIG_H_
#define _PMU_CONFIG_H_

#include "global_types.h"

/***************************   PMU REGISTERS INITIAL VALUES  *******************************************/

/****************************************   FCCR   *****************************************************
 * the initial value of PMU - POCR register:  section 7.5.2.3 on PMU spec
 *
 *  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
 *  0  0  0  0  1  0  0  0  0  1  1  0  0  0  1  1  0  0  0  0  0  0  0  0  0  0  0  0  0  1  1  0
 *
 * bits 31:30 - XSC divider (according to PLL clock)
 * bit  29    - reserved
 * bits 28:26 - DSP divider (according to PLL clock)
 * bits 25:24 - reserved
 * bits 23:18 - PLL Multiplication Factor
 * bits 17:16 - PX divider (according to XScale clock)
 * bits 15:14 - reserved
 * bits 13:11 - PX2DSP ratio
 * bit  10    - reserved
 * bits 9:7   - DPB2DSP ratio
 * bits 8:4   - reserved
 * bits 3:0   - APB divider (according to PLL clock)
 *
 * FCCR_VAL_PLL_312_XSC_312 configuration (0x08630006) means:
 * XScale = 312, DSP = 104, PLL = 312, PX = 104, PX2DSP = 1, DPB2DSP = 1, APB = 26
 *
 * FCCR_VAL_PLL_312_XSC_104 configuration (0x88600006) means:
 * XScale = 104, DSP = 104, PLL = 312, PX = 104, PX2DSP = 1, DPB2DSP = 1, APB = 26
 *
 * FCCR_VAL_PLL_104_XSC_104 configuration (0x00200002) means (this is the HW default configuration):
 * XScale = 104, DSP = 104, PLL = 104, PX = 104, PX2DSP = 1, DPB2DSP = 1, APB = 26
 *
 * FCCR_VAL_PLL_312_XSC_312_MSA_156 configuration (0x04633086) means:
 * XScale = 312, DSP = 156, PLL = 312, PX = 104, PX2DSP = 1.5, DPB2DSP = 2, APB = 26
 *
 * FCCR_VAL_PLL_208_XSC_208_MSA_208 configuration (0x00420884) means:
 * XScale = 208, DSP = 208, PLL = 208, PX = 104, PX2DSP = 2, DPB2DSP = 2, APB = 26
 *
 * *****************************************************************************************************/
#define FCCR_VAL_PLL_312_XSC_312                0x08630006L
#define FCCR_VAL_PLL_312_XSC_104                0x88600006L
#define FCCR_VAL_PLL_104_XSC_104                0x00200002L
#define FCCR_VAL_PLL_312_XSC_312_MSA_156        0x04633086L
#define FCCR_VAL_PLL_208_XSC_208_MSA_208        0x00420884L

/****************************************   POCR   *****************************************************
 * the initial value of PMU - POCR register:  section 7.5.2.4 on PMU spec
 *
 *  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
 *  0  0  0  0  0  0  0  0  1  1  1  0  0  1  0  1  0  0  0  0  1  1  1  1  1  1  1  1  1  1  1  1
 *
 * bit  31    - FORCE
 * bits 30:24 - reserved
 * bits 23:16 - VCTCXO stable time (32KHz cycles)
 * bits 15:12 - reserved
 * bits 11:0  - PLL lock time (VCTCXO cycles), USB PLL lock time (VCTCXO cycles * 16)
 *
 * current configuration (0x00E50FFF) means:
 * Force clk disabled, VCXOST=100 32k clk cycles (~3ms), PLLLock=4096 VCXO cycles (max value) USB PLL Lock = 4096 * 16 VCXO cycles (max value)
 * *****************************************************************************************************/
#if !defined(_MANITOBA_SILICON_)
// Hermon B0, main PLL spec is 144 VCTCXO cycles (VCTCXO is 26MHz)
#define POCR_INITIAL_VALUE                      0x0063008FL
#else
#define POCR_INITIAL_VALUE                      0x00630FFFL
#endif

/****************************************   XPRR2   ****************************************************
 * the initial value of PMU - XPRR2 register:  section 7.5.2.9 on PMU spec
 *
 *  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
 *  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  1  1  0  0
 *
 * bits 31:5 - reserved
 * bit  4    - WDTR
 * bit  3    - BBR
 * bit  2    - DSPR
 * bits 1:0  - reserved
 *
 * current configuration (0x0000001C) means:
 * WDTR reset is negated, BB logic and MSA remain reset
 * *****************************************************************************************************/
#define XPRR2_INITIAL_VALUE                     0x0000001CL

/****************************************   XCGR   *****************************************************
 * the initial value of PMU - XCGR register:  section 7.5.2.10 on PMU spec
 *
 *  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
 *  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 *
 * bit  31    - UART1
 * bit  30    - UART2
 * bit  29    - UART3
 * bit  28    - USB
 * bit  27    - MMC
 * bit  26    - ETM
 * bit  25    - reserved
 * bit  24    - Non Drowsy TIMER
 * bit  23    - Drowsy TIMER
 * bit  22    - MSL
 * bit  21    - reserved
 * bit  20    - MSHC
 * bit  19    - KEYPAD
 * bit  18    - I2C
 * bits 17:16 - reserved
 * bit  15    - SSP
 * bit  14    - GPC
 * bit  13    - reserved
 * bit  12    - ICP
 * bit  11    - SCI1
 * bit  10    - SCI2
 * bit  9     - SCI3
 * bit  8     - USIM
 * bit  7     - I2S
 * bits 6:4   - reserved
 * bit  3     - PWM1C0
 * bit  2     - PWM1C1
 * bit  1     - PWM2C0
 * bit  0     - PWM2C1
 *
 * current configuration (0x00000000) means:
 * all peripherals functional clocks are OFF
 * *****************************************************************************************************/
#define XCGR_INITIAL_VALUE                      0x00000000L    //all peripheral's functional clocks are disabled

/****************************************   XDCR   ****************************************************
 * the initial value of PMU - XDCR register:  section 7.5.2.12 on PMU spec
 *
 *  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
 *  1  1  1  1  1  1  1  1  0  0  0  0  0  0  0  0  1  1  1  1  1  1  1  1  0  0  0  0  0  0  0  0
 *
 * bits 31:24 - ti4
 * bits 23:16 - reserved
 * bits 15:8  - to2
 * bits 7:0   - reserved
 *
 * current configuration (0xFF00FF00) means:
 * ti4=255 VCXO cycles (max value), to2=255 VCXO cycles (max value)
 * *****************************************************************************************************/
#define XDCR_INITIAL_VALUE                      0xFF00FF00L

/****************************************   GPCR   ****************************************************
 * the initial value of PMU - GPCR register:  section 7.5.2.13 on PMU spec
 *
 *  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
 *  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 *
 * bits 31:16 - GPCDIVN (GPC divider Nom value)
 * bits 15:0  - GPCDIVD (GPC divider Dnom value)
 *
 * current configuration (0x00000000) means:
 * currently not in use
 * *****************************************************************************************************/
#define GPCR_INITIAL_VALUE                      0x00000000L

/***************************   END OF PMU REGISTERS INITIAL VALUES  ************************************/

/****************************************   Functional Clocks Ignore Mask   ****************************
 * used to specify which functional clocks to ignore (even if running) while going to sleep and which not.
 * the mask is 32 bits corresponds to XCGR register bit definition
 * '0' - Ignore this peripheral functional clock -> go to sleep whether it's functional clock is running or not.
 * '1' - Do not ignore this peripheral functional clock -> Do not go to sleep if it's functional clock is running
 *
 *  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
 *  1  1  1  1  1  1  0  1  1  1  0  1  1  1  0  0  1  1  0  1  1  1  1  1  1  0  0  0  1  1  1  1
 *
 * bit  31    - UART1
 * bit  30    - UART2
 * bit  29    - UART3
 * bit  28    - USB
 * bit  27    - MMC
 * bit  26    - ETM
 * bit  25    - reserved
 * bit  24    - Non Drowsy TIMER
 * bit  23    - Drowsy TIMER
 * bit  22    - MSL
 * bit  21    - reserved
 * bit  20    - MSHC
 * bit  19    - KEYPAD
 * bit  18    - I2C
 * bits 17:16 - reserved
 * bit  15    - SSP
 * bit  14    - GPC
 * bit  13    - reserved
 * bit  12    - ICP
 * bit  11    - SCI1
 * bit  10    - SCI2
 * bit  9     - SCI3
 * bit  8     - USIM
 * bit  7     - I2S
 * bits 6:4   - reserved
 * bit  3     - PWM1C0
 * bit  2     - PWM1C1
 * bit  1     - PWM2C0
 * bit  0     - PWM2C1
 *
 * current configuration (0xFDDCDF8F) means:
 * all peripherals functional clocks are not ignored -> don't go to sleep if one of them is running
 * all reserved bits are ignored
 * *****************************************************************************************************/
#define PMU_FUNC_CLK_IGNORE_MASK                0xFDDCDF8FL


/****************************************   APB Clocks Ignore Mask Low   *******************************
 * used to specify which APB clocks to ignore (even if running) while going to sleep and which not.
 * the mask is 32 bits corresponds to the first 32 APB users
 * '0' - Ignore this peripheral APB clock -> go to sleep whether it's APB clock is running or not.
 * '1' - Do not ignore this peripheral APB clock -> Do not go to sleep if it's APB clock is running
 *
 *  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
 *  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1
 *
 * bit  31    - MSHC
 * bit  30    - EXT_PERIPHERAL_7
 * bit  29    - EXT_PERIPHERAL_6
 * bit  28    - EXT_PERIPHERAL_5
 * bit  27    - EXT_PERIPHERAL_4
 * bit  26    - EXT_PERIPHERAL_3
 * bit  25    - EXT_PERIPHERAL_2
 * bit  24    - EXT_PERIPHERAL_1
 * bit  23    - EXT_PERIPHERAL_0
 * bit  22    - ONE_WIRE
 * bit  21    - NDSYTMR
 * bit  20    - DSYTMR
 * bit  19    - INTC
 * bit  18    - GPIO
 * bit  17    - RTC
 * bit  16    - MSL
 * bit  15    - SCI3
 * bit  14    - SCI2
 * bit  13    - SCI1
 * bit  12    - PWM
 * bit  11    - LCD_IF
 * bit  10    - USIM
 * bit  9     - KEYPAD
 * bit  8     - MMC
 * bit  7     - SSP
 * bit  6     - ICP
 * bit  5     - USB
 * bit  4     - IPC
 * bit  3     - I2C
 * bit  2     - UART3
 * bit  1     - UART2
 * bit  0     - UART1
 *
 * current configuration (0xFFFFFFFF) means:
 * all peripherals functional clocks are not ignored -> don't go to sleep if one of them is running
 * *****************************************************************************************************/
#define PMU_APB_CLK_IGNORE_MASK_LOW             0xFFFFFFFFL

/****************************************   APB Clocks Ignore Mask High   ******************************
 * used to specify which APB clocks to ignore (even if running) while going to sleep and which not.
 * the mask is 8 bits -> the last (33rd) APB user
 * '0' - Ignore this peripheral APB clock -> go to sleep whether it's APB clock is running or not.
 * '1' - Do not ignore this peripheral APB clock -> Do not go to sleep if it's APB clock is running
 *
 *  07 06 05 04 03 02 01 00
 *  0  0  0  0  0  0  0  1
 *
 * bits 7:1   - reserved
 * bit  0     - CAM_BIT
 *
 * current configuration (0x01) means:
 * don't ignore the CAM_BIT -> don't go to sleep if it's APB clock is running
 * all reserved bits are ignored
 * *****************************************************************************************************/
#define PMU_APB_CLK_IGNORE_MASK_HIGH            0x01


 /* *****************************************************************************************************/

/***************************   MSA CLOCK DOMAIN USERS  *************************************************
 * the following enum defined the list of users that may use the MSA clock domain (via PMUMSAClock service)
 * the list is limited to 32 users
 * new user may add it's name instead of one of the unused defines
 * *****************************************************************************************************/
typedef enum
{
    PMU_MSA_USER_COMMUNICATION = 0,
    PMU_MSA_USER_AUDIO,
    PMU_MSA_USER_VR,
    PMU_MSA_USER_VMP,
    PMU_MSA_USER_MP3,
    PMU_MSA_USER_5, PMU_MSA_USER_PM  = PMU_MSA_USER_5, /*PM force (init etc) */
    PMU_MSA_USER_IPCSEND,
    PMU_MSA_USER_IPCRECEIVE,
    PMU_MSA_USER_IPCDATAREAD,
    PMU_MSA_USER_IPCDATAWRITE,
    PMU_MSA_USER_L1P_GSM,
    PMU_MSA_USER_HSL,
    PMU_MSA_USER_L1P_GSM_PH,
    PMU_MSA_USER_L1P_GSM_INIT,
    PMU_MSA_USER_L1P_GSM_ASNYC,
    PMU_MSA_USER_L1P_APLP_GSM_INIT,
    PMU_MSA_USER_AUDIO_GSM,
    PMU_MSA_USER_17,
    PMU_MSA_USER_18,
    PMU_MSA_USER_19,
    PMU_MSA_USER_20,
    PMU_MSA_USER_21,
    PMU_MSA_USER_22,
    PMU_MSA_USER_23,
    PMU_MSA_USER_24,
    PMU_MSA_USER_25,
    PMU_MSA_USER_26,
    PMU_MSA_USER_27,
    PMU_MSA_USER_28,
    PMU_MSA_USER_29,
    PMU_MSA_USER_30,
    PMU_MSA_USER_31
}PMUMsaUsers;

/***************************   MEMC CLOCK DOMAIN USERS  *************************************************
 * the following enum defined the list of users that may use the MEMC clock domain (via PMUMEMCClock service)
 * the list is limited to 32 users
 * new user may add it's name instead of one of the unused defines
 * *****************************************************************************************************/
typedef enum
{
    PMU_MEMC_USER_0 = 0,
    PMU_MEMC_USER_1,
    PMU_MEMC_USER_2,
    PMU_MEMC_USER_3,
    PMU_MEMC_USER_4,
    PMU_MEMC_USER_5,
    PMU_MEMC_USER_6,
    PMU_MEMC_USER_7,
    PMU_MEMC_USER_8,
    PMU_MEMC_USER_9,
    PMU_MEMC_USER_10,
    PMU_MEMC_USER_11,
    PMU_MEMC_USER_12,
    PMU_MEMC_USER_13,
    PMU_MEMC_USER_14,
    PMU_MEMC_USER_15,
    PMU_MEMC_USER_16,
    PMU_MEMC_USER_17,
    PMU_MEMC_USER_18,
    PMU_MEMC_USER_19,
    PMU_MEMC_USER_20,
    PMU_MEMC_USER_21,
    PMU_MEMC_USER_22,
    PMU_MEMC_USER_23,
    PMU_MEMC_USER_24,
    PMU_MEMC_USER_25,
    PMU_MEMC_USER_26,
    PMU_MEMC_USER_27,
    PMU_MEMC_USER_28,
    PMU_MEMC_USER_29,
    PMU_MEMC_USER_30,
    PMU_MEMC_USER_31
}PMUMemcUsers;

/***************************   BB LOGIC CLOCK DOMAIN USERS  *************************************************
 * the following enum defined the list of users that may use the BB Logic clock domain (via PMUBBLogicClock service)
 * the list is limited to 32 users
 * new user may add it's name instead of one of the unused defines
 * *****************************************************************************************************/
typedef enum
{
    PMU_BB_LOGIC_USER_0 = 0, PMU_BB_LOGIC_USER_PM  =PMU_BB_LOGIC_USER_0, /*PM force (init etc) */
    PMU_BB_LOGIC_USER_1,     PMU_BB_LOGIC_USER_PMUE=PMU_BB_LOGIC_USER_1, /*Allocated to EXT APB - PMUE*/
    PMU_BB_LOGIC_USER_2,     PMU_BB_LOGIC_USER_GSM =PMU_BB_LOGIC_USER_2, /*DIRQ controlled through PMUE*/
    PMU_BB_LOGIC_USER_GSM_DSSP_INIT,
    PMU_BB_LOGIC_USER_WCI,   PMU_BB_LOGIC_USER_4=PMU_BB_LOGIC_USER_WCI,
    PMU_BB_LOGIC_USER_5,
    PMU_BB_LOGIC_USER_6,
    PMU_BB_LOGIC_USER_7,
    PMU_BB_LOGIC_USER_8,
    PMU_BB_LOGIC_USER_9,
    PMU_BB_LOGIC_USER_10,
    PMU_BB_LOGIC_USER_11,
    PMU_BB_LOGIC_USER_12,
    PMU_BB_LOGIC_USER_13,
    PMU_BB_LOGIC_USER_14,
    PMU_BB_LOGIC_USER_15,
    PMU_BB_LOGIC_USER_16,
    PMU_BB_LOGIC_USER_17,
    PMU_BB_LOGIC_USER_18,
    PMU_BB_LOGIC_USER_19,
    PMU_BB_LOGIC_USER_20,
    PMU_BB_LOGIC_USER_21,
    PMU_BB_LOGIC_USER_22,
    PMU_BB_LOGIC_USER_23,
    PMU_BB_LOGIC_USER_24,
    PMU_BB_LOGIC_USER_25,
    PMU_BB_LOGIC_USER_26,
    PMU_BB_LOGIC_USER_27,
    PMU_BB_LOGIC_USER_28,
    PMU_BB_LOGIC_USER_29,
    PMU_BB_LOGIC_USER_30,
    PMU_BB_LOGIC_USER_31
}PMUBBLogicUsers;

/***********************************************************************************************************/


#define PMU_BREAK_THE_LOOP_MAX_CYCLES   10000

#define PMU_MAX_USB_PLL_RECIPIENTS      6       //the 6 USB PLL recipients are: USIM, ICP, I2C, MSL, MMC and USB
#define PMU_NUMBER_OF_PLL_MF_VALUES     21      //the pll_mf is between 4 to 24 -> 21 values, those values are translated to 0 - 20 and used by the table below

#if !defined(_MANITOBA_SILICON_)
#define _SKIP_MFC_AT_INIT_
#endif

#define PMU_BSP_SETS_MEMC_CLOCK //preserve the CGCR.MEMC value when initializing the PMU package: this is set earlier by BSP

#endif /*_PMU_CONFIG_H_*/
