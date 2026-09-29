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
// Hermon pin MUX control services
//
#ifndef _BSP_MUX_H_
#define _BSP_MUX_H_

#if defined(_HERMON_B0_SILICON_)
//===  If this is not any XSCALE=_HERMON_B0_SILICON_ (Hermon, Bulverde, Boerne) the file is empty ===

#ifdef	_TAVOR_BOERNE_
#include	"brn_mux_defs.h"
#endif

//
// Numbering for General Pins (controlled by GPSRs)
// GPIO and EGPIO pins are referred to as GPIO#xx and EGPIO#xx
//
typedef enum
{
  G_RF_CONT0,                      /* GPSR0[1-0]   ************************/
  G_RF_CONT1,                      /* GPSR0[3-2]   */
  G_RF_CONT2,                      /* GPSR0[5-4]   */
  G_RF_CONT3,                      /* GPSR0[7-6]   */
  G_RF_CONT4,                      /* GPSR0[9-8]   */
  G_RF_CONT5,                      /* GPSR0[11-10] */
  G_RF_CONT6,                      /* GPSR0[13-12] */
  G_DSSP0_RX_TX,                   /* GPSR0[15-14] */
  G_DSSP0_FRM,                     /* GPSR0[17-16] */
  G_DSSP0_CLK,                     /* GPSR0[19-18] */
  G_DSSP1_RX_TX,                   /* GPSR0[21-20] */
  G_DSSP1_FRM,                     /* GPSR0[23-22] */
  G_DSSP1_CLK,                     /* GPSR0[25-24] */
  G_DSSP2_RX_TX,                   /* GPSR0[27-26] */
  G_DSSP2_FRM,                     /* GPSR0[29-28] */
  G_DSSP2_CLK,                     /* GPSR0[31-30] */
  G_GSSP0A_CLK,                    /* GPSR1[1-0]   ************************/
  G_GSSP0A_FRM,                    /* GPSR1[3-2]   */
  G_GSSP0A_RX,                     /* GPSR1[5-4]   */
  G_GSSP0A_TX,                     /* GPSR1[7-6]   */
  G_RF_SPI1_D,                     /* GPSR1[9-8]   */
  G_RF_SPI1_STR_B0,                 /* GPSR1[11-10] */
  G_RF_SPI1_STR_B1,                /* GPSR1[13-12] */
  G_RF_SPI1_CLK,                   /* GPSR1[15-14] */
  G_AFE_RXIQ0,                     /* GPSR1[17-16] */
  G_AFE_RXIQ1,                     /* GPSR1[19-18] */
  G_AFE_RXIQ2,                     /* GPSR1[21-20] */
  G_AFE_RXIQ3,                     /* GPSR1[23-22] */
  G_AFE_RXIQ4,                     /* GPSR1[25-24] */
  G_AFE_RXIQ5,                     /* GPSR1[27-26] */
  G_AFE_RXIQ6,                     /* GPSR1[29-28] */
  G_AFE_RXIQ7,                     /* GPSR1[31-30] */
  G_AFE_RX_CLK,                    /* GPSR2[1-0]   ************************/
  G_AFE_TXIQ0,                     /* GPSR2[3-2]   */
  G_AFE_TXIQ1,                     /* GPSR2[5-4]   */
  G_AFE_TXIQ2,                     /* GPSR2[7-6]   */
  G_AFE_TXIQ3,                     /* GPSR2[9-8]   */
  G_AFE_TXIQ4,                     /* GPSR2[11-10] */
  G_AFE_TXIQ5,                     /* GPSR2[13-12] */
  G_AFE_TXIQ6,                     /* GPSR2[15-14] */
  G_AFE_TXIQ7,                     /* GPSR2[17-16] */
  G_AFE_TXIQ8,                     /* GPSR2[19-18] */
  G_AFE_TXIQ9,                     /* GPSR2[21-20] */
  G_AFE_TX_CLK,                    /* GPSR2[23-22] */
  G_CONT_CLK,                      /* GPSR2[25-24] */
  G_CONT_DATA0,                    /* GPSR2[27-26] */
  G_CONT_DATA1,                    /* GPSR2[29-28] */
  G_CONT_RD_WR,                    /* GPSR2[31-30] */
  G_CONT_READ_INT,                 /* GPSR3[1-0]   ************************/
  G_GPSR3_RESERVED_3_2,            /* GPSR3[3-2]   */
  G_DAC_ST456,                     /* GPSR3[5-4]   */
  G_ADC_ST,                        /* GPSR3[7-6]   */
  G_SYSCLK1,                       /* GPSR3[9-8]   */
  G_GPSR3_RESERVED_11_10,          /* GPSR3[11-10] */
  G_GPSR3_RESERVED_13_12,          /* GPSR3[13-12] */
  G_GPSR3_RESERVED_15_14,          /* GPSR3[15-14] */
  G_GPSR3_RESERVED_17_16,          /* GPSR3[17-16] */
  G_GPSR3_RESERVED_19_18,          /* GPSR3[19-18] */
  G_GPSR3_RESERVED_21_20,          /* GPSR3[21-20] */
  G_GPSR3_RESERVED_23_22,          /* GPSR3[23-22] */
  G_GPSR3_RESERVED_25_24,          /* GPSR3[25-24] */
  G_GPSR3_RESERVED_27_26,          /* GPSR3[27-26] */
  G_GPSR3_RESERVED_29_28,          /* GPSR3[29-28] */
  G_GPSR3_RESERVED_31_30,          /* GPSR3[31-30] */
  G_ADDR23,                        /* GPSR4[1-0]   ************************/
  G_ADDR22,                        /* GPSR4[3-2]   */
  G_ADDR21,                        /* GPSR4[5-4]   */
  G_ADDR20,                        /* GPSR4[7-6]   */
  G_ADDR19,                        /* GPSR4[9-8]   */
  G_ADDR18,                        /* GPSR4[11-10] */
  G_ADDR17,                        /* GPSR4[13-12] */
  G_ADDR16,                        /* GPSR4[15-14] */
  G_ADDR15,                        /* GPSR4[17-16] */
  G_ADDR14,                        /* GPSR4[19-18] */
  G_ADDR13,                        /* GPSR4[21-20] */
  G_ADDR12,                        /* GPSR4[23-22] */
  G_ADDR11,                        /* GPSR4[25-24] */
  G_ADDR10,                        /* GPSR4[27-26] */
  G_ADDR9,                         /* GPSR4[29-28] */
  G_ADDR8,                         /* GPSR4[31-30] */
  G_ADDR7,                         /* GPSR5[1-0]   ************************/
  G_ADDR6,                         /* GPSR5[3-2]   */
  G_ADDR5,                         /* GPSR5[5-4]   */
  G_ADDR4,                         /* GPSR5[7-6]   */
  G_ADDR3,                         /* GPSR5[9-8]   */
  G_ADDR2,                         /* GPSR5[11-10] */
  G_ADDR1,                         /* GPSR5[13-12] */
  G_DATA15,                        /* GPSR5[15-14] */
  G_DATA14,                        /* GPSR5[17-16] */
  G_DATA13,                        /* GPSR5[19-18] */
  G_DATA12,                        /* GPSR5[21-20] */
  G_DATA11,                        /* GPSR5[23-22] */
  G_DATA10,                        /* GPSR5[25-24] */
  G_DATA9,                         /* GPSR5[27-26] */
  G_DATA8,                         /* GPSR5[29-28] */
  G_DATA7,                         /* GPSR5[31-30] */
  G_DATA6,                         /* GPSR6[1-0]   ************************/
  G_DATA5,                         /* GPSR6[3-2]   */
  G_DATA4,                         /* GPSR6[5-4]   */
  G_DATA3,                         /* GPSR6[7-6]   */
  G_DATA2,                         /* GPSR6[9-8]   */
  G_DATA1,                         /* GPSR6[11-10] */
  G_DATA0,                         /* GPSR6[13-12] */
  G_DQM1,                          /* GPSR6[15-14] */
  G_DQM0,                          /* GPSR6[17-16] */
  G_CS1_N,                         /* GPSR6[19-18] */
  G_OE_N,                          /* GPSR6[21-20] */
  G_WE_N,                          /* GPSR6[23-22] */
  G_SDCS0_N,                       /* GPSR6[25-24] */
  G_SDCKE1,                        /* GPSR6[27-26] */
  G_SDRAS_N,                       /* GPSR6[29-28] */
  G_SDCAS_N,                       /* GPSR6[31-30] */
  G_SDCLK0,                        /* GPSR7[1-0]   ************************/
  G_SDCLK1,                        /* GPSR7[3-2]   */
  G_I2C_SDA,                       /* GPSR7[5-4]   */
  G_I2C_SCL,                       /* GPSR7[7-6]   */
  G_VCXO_ENABLE,                   /* GPSR7[9-8]   */
  G_USIM_RST,                      /* GPSR7[11-10] */
  G_USIM_CLK,                      /* GPSR7[13-12] */
  G_USIM_DIO,                      /* GPSR7[15-14] */
  G_PRI_TCK,                       /* GPSR7[17-16] */
  G_PRI_TDI,                       /* GPSR7[19-18] */
  G_PRI_TMS,                       /* GPSR7[21-20] */
  G_PRI_TDO                        /* GPSR7[23-22] */
} GPins;

#ifdef	_TAVOR_BOERNE_
void		setMuxGPin				(PadName pin, PadAltFn fn);
PadAltFn	getMuxGPin				(PadName pin);
void 		setMuxGpio				(int gpio_num, PadAltFn fn);
PadAltFn	getMuxGpio				(int gpio_num);
int 		updateGRs				(void);

void		setPadPull				(PadName pin , PadPull pull);
PadPull		getPadPull				(PadName pin);
void		setPadSleep				(PadName pin , PadSleep sleep);
PadSleep	getPadSleep				(PadName pin);
void		setPadEdge				(PadName pin , PadEdge edge);
PadEdge		getPadEdge				(PadName pin);

void		setPadDriveRate			(PadName pin,  PadDrive drive);
PadDrive 	getPadDriveRate			(PadName pin);

void		setPadParams			(PadName pin , PadParams	*params);
void		setPadParamsSecured		(PadName pin , PadParams	*params);
void		getPadParams			(PadName pin , PadParams	*pad_params);


#define	setMuxEGpio	setMuxGpio	//alias
#define	getMuxEGpio	getMuxGpio	//alias

#else//_TAVOR_BOERNE_

//  GPRS[0..7] registers, 2 bits per pin = functions 0..3
void setMuxGPin(int pin, int fn);
int  getMuxGPin(int pin);

// GPIO pins (0..63): AFSR[0..8] registers, 4 bits per pin (1 reserved)= functions 0..7
void setMuxGpio(int pin, int fn);
int  getMuxGpio(int pin);


// EGPIO pins (0..21): EGSR[0..1] registers, 2 bits per pin = functions 0..3
void setMuxEGpio(int pin, int fn);
int  getMuxEGpio(int pin);

// CALL IN ORDER FOR THE PREVIOUS setMuxXXXX() operation(s) to take effect
int updateGRs(void);

#endif	//_TAVOR_BOERNE_



#define updateMux updateGRs /*alias*/

//
// ======= Drive-slew rates for pad groups =================================
//

// List of the 32 pad groups
typedef enum
{
  PD_DVDD_A1,
  PD_DVDD_A2,
  PD_DVDD_A3,
  PD_DVDD_A4,
  PD_DVDD_A5,
  PD_DVDD_A6,
  PD_DVDD_A7,
  PD_DVDD_A8,
  PD_DVDD_A9,
  PD_DVDD_A10,
  PD_DVDD_A11,
  PD_DVDD_A12,
  PD_DVDD_A13,
  PD_DVDD_A14,
  PD_DVDD_A15,
  PD_DVDD_A16,
  PD_DVDD_A17,
  PD_DVDD_A18,
  PD_DVDD_A19,
  PD_DVDD_B1,
  PD_DVDD_B2,
  PD_DVDD_B3,
  PD_DVDD_B4,
  PD_DVDD_B5,
  PD_DVDD_B6,
  PD_DVDD_B7,
  PD_DVDD_B8,
  PD_DVDD_B9,
  PD_DVDD_B10,
  PD_DVDD_B11,
  PD_DVDD_B12,
  PD_DVDD_B13,
  PD_DVDD_B14,
  PD_DVDD_B15,
  PD_DVDD_B16,
  PD_DVDD_B17,
  PD_DVDD_C1,
  PD_DVDD_C2,
  PD_DVDD_C3,
  PD_DVDD_C4,
  PD_DVDD_C5,
  PD_DVDD_D1,
  PD_DVDD_D2,
  PD_DVDD_D3,
  PD_DVDD_D4,
  PD_DVDD_D5,
  PD_DVDD_D6,
  PD_DVDD_D7,
  PD_DVDD_D8,
  PD_DVDD_E1,
  PD_DVDD_E2,
  PD_DVDD_F1,
  PD_DVDD_G1,
  PD_DVDD_G2,
  PD_DVDD_G3,
  PD_DVDD_G4,
  PD_DVDD_MAX
} PadGroups;

// Either the "default" or the "optional" setting configureable per pad group
typedef enum
{
	PD_DEFAULT,
	PD_OPTIONAL
}PadSetting;

#if !defined (INTEL_2CHIP_PLAT_BVD) && !defined	(_TAVOR_BOERNE_)
// Value is 3-bit and depends on pad group
void setPadDriveRateFine(PadGroups group, UINT32 value);
#endif

#if !defined(_TAVOR_BOERNE_)
// Per-group setting:
void setPadDriveRate(PadGroups group, PadSetting set);
PadSetting getPadDriveRate(PadGroups group);
void setPadSlewRate(PadGroups group, PadSetting set);
PadSetting  getPadSlewRate(PadGroups group);
#endif//_TAVOR_BOERNE_

#endif//_HERMON_B0_SILICON_

#endif//_BSP_MUX_H_

