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

#ifndef _PADS_DEF_H_
#define _PADS_DEF_H_

#define GPIO8_REG IOMCRS0
#define GPIO8_MASK 0x7
#define GPIO8_SHIFT 0
#define GPIO8_GPIO8 0
#define GPIO8_MM_CMD 1
#define GPIO8_MS_SCLK 2
#define GPIO8_SIM_RST_N 3
#define GPIO8_SIM2_RST_N 4

#define GPIO9_REG IOMCRS0
#define GPIO9_MASK 0xF
#define GPIO9_SHIFT 4
#define GPIO9_GPIO9 0
#define GPIO9_MM_DAT1 1
#define GPIO9_CSSP_TX 2
#define GPIO9_HSL_CLK 3
#define GPIO9_DSSP3_TX 4
#define GPIO9_SIM_DIO 5
#define GPIO9_SIM2_DIO 6
#define GPIO9_TCO23 7
#define GPIO9_PWM1 8

#define GPIO45_REG IOMCRS0
#define GPIO45_MASK 0x7
#define GPIO45_SHIFT 8
#define GPIO45_GPIO45 0
#define GPIO45_I2S_SYS_CLK 1
#define GPIO45_CSSP_TX 2
#define GPIO45_HSL_DATA2 3
#define GPIO45_DSSP3_TX 4
#define GPIO45_SIM_CLK 5
#define GPIO45_SIM2_CLK 6

#define GPIO46_REG IOMCRG0
#define GPIO46_MASK 0x3
#define GPIO46_SHIFT 4
#define GPIO46_GPIO46 0
#define GPIO46_I2S_DO 1
#define GPIO46_HSL_DATA3 2

#define GPIO47_REG IOMCRG0
#define GPIO47_MASK 0x3
#define GPIO47_SHIFT 6
#define GPIO47_GPIO47 0
#define GPIO47_I2S_BIT_CLK 1
#define GPIO47_HSL_DATA4 2
#define GPIO47_ONE_WIRE_DQ 3

#define GPIO20_REG IOMCRG1
#define GPIO20_MASK 0x3
#define GPIO20_SHIFT 18
#define GPIO20_GPIO20 0
#define GPIO20_TCO10 1
#define GPIO20_PWM0 2

#define GPIO19_REG IOMCRG1
#define GPIO19_MASK 0x3
#define GPIO19_SHIFT 20
#define GPIO19_GPIO19 0
#define GPIO19_TCO9 1

#define GPIO18_REG IOMCRG1
#define GPIO18_MASK 0x3
#define GPIO18_SHIFT 22
#define GPIO18_GPIO18 0
#define GPIO18_TCO8 1

#define GPIO17_REG IOMCRG1
#define GPIO17_MASK 0x3
#define GPIO17_SHIFT 24
#define GPIO17_GPIO17 0
#define GPIO17_TCO7 1

#define GPIO16_REG IOMCRG1
#define GPIO16_MASK 0x3
#define GPIO16_SHIFT 26
#define GPIO16_GPIO16 0
#define GPIO16_TCO6 1
#define GPIO16_PWM1 2

#define GPIO15_REG IOMCRG1
#define GPIO15_MASK 0x3
#define GPIO15_SHIFT 28
#define GPIO15_GPIO15 0
#define GPIO15_TCO5 1

#define GPIO14_REG IOMCRG1
#define GPIO14_MASK 0x3
#define GPIO14_SHIFT 30
#define GPIO14_GPIO14 0
#define GPIO14_TCO4 1

#define GPIO13_REG IOMCRG2
#define GPIO13_MASK 0x3
#define GPIO13_SHIFT 0
#define GPIO13_GPIO13 0
#define GPIO13_TCO3 1

#define GPIO12_REG IOMCRG2
#define GPIO12_MASK 0x3
#define GPIO12_SHIFT 2
#define GPIO12_GPIO12 0
#define GPIO12_TCO2 1
#define GPIO12_PWM2 2

#define GPIO11_REG IOMCRG2
#define GPIO11_MASK 0x3
#define GPIO11_SHIFT 4
#define GPIO11_GPIO11 0
#define GPIO11_TCO1 1

#define GPIO10_REG IOMCRG2
#define GPIO10_MASK 0x3
#define GPIO10_SHIFT 6
#define GPIO10_GPIO10 0
#define GPIO10_TCO0 1
#define GPIO10_PWM3 2

#define SIM_RST_N_REG IOMCRG2
#define SIM_RST_N_MASK 0x3
#define SIM_RST_N_SHIFT 10
#define SIM_RST_N_SIM_RST_N 0
#define SIM_RST_N_SIM2_RST_N 1

#define SIM_DIO_REG IOMCRG2
#define SIM_DIO_MASK 0x3
#define SIM_DIO_SHIFT 12
#define SIM_DIO_SIM_DIO 0
#define SIM_DIO_SIM2_DIO 1

#define SIM_CLK_REG IOMCRG2
#define SIM_CLK_MASK 0x3
#define SIM_CLK_SHIFT 14
#define SIM_CLK_SIM_CLK 0
#define SIM_CLK_SIM2_CLK 1

#define GPIO34_REG IOMCRG2
#define GPIO34_MASK 0x3
#define GPIO34_SHIFT 28
#define GPIO34_GPIO34 0
#define GPIO34_TCO21 1
#define GPIO34_PWM2 2
#define GPIO34_EXT_ADDR0 3

#define GPIO35_REG IOMCRG2
#define GPIO35_MASK 0x3
#define GPIO35_SHIFT 30
#define GPIO35_GPIO35 0
#define GPIO35_UART3_RX 1
#define GPIO35_CSSP_RX 2
#define GPIO35_DSSP3_RX 3

#define GPIO38_REG IOMCRG3
#define GPIO38_MASK 0x3
#define GPIO38_SHIFT 0
#define GPIO38_GPIO38 0
#define GPIO38_UART3_TX 1
#define GPIO38_CSSP_TX 2
#define GPIO38_DSSP3_TX 3

#define EXT_ADDR1_REG IOMCRG3
#define EXT_ADDR1_MASK 0x3
#define EXT_ADDR1_SHIFT 2
#define EXT_ADDR1_EXT_ADDR1 0
#define EXT_ADDR1_GPIO20 1

#define GPIO24_REG IOMCRG3
#define GPIO24_MASK 0x3
#define GPIO24_SHIFT 4
#define GPIO24_GPIO24 0
#define GPIO24_EXT_CS2_N 1
#define GPIO24_PWM1 2

#define EXT_DATA8_REG IOMCRG3
#define EXT_DATA8_MASK 0x3
#define EXT_DATA8_SHIFT 10
#define EXT_DATA8_EXT_DATA8 0
#define EXT_DATA8_GPIO45 1

#define EXT_DATA9_REG IOMCRG3
#define EXT_DATA9_MASK 0x3
#define EXT_DATA9_SHIFT 14
#define EXT_DATA9_EXT_DATA9 0
#define EXT_DATA9_GPIO32 1

#define EXT_DATA10_REG IOMCRG3
#define EXT_DATA10_MASK 0x3
#define EXT_DATA10_SHIFT 18
#define EXT_DATA10_EXT_DATA10 0
#define EXT_DATA10_GPIO44 1

#define EXT_DATA11_REG IOMCRG3
#define EXT_DATA11_MASK 0x3
#define EXT_DATA11_SHIFT 22
#define EXT_DATA11_EXT_DATA11 0
#define EXT_DATA11_GPIO30 1

#define EXT_DATA12_REG IOMCRG3
#define EXT_DATA12_MASK 0x3
#define EXT_DATA12_SHIFT 26
#define EXT_DATA12_EXT_DATA12 0
#define EXT_DATA12_GPIO29 1

#define EXT_DATA13_REG IOMCRG3
#define EXT_DATA13_MASK 0x3
#define EXT_DATA13_SHIFT 30
#define EXT_DATA13_EXT_DATA13 0
#define EXT_DATA13_GPIO28 1

#define EXT_DATA14_REG IOMCRG4
#define EXT_DATA14_MASK 0x3
#define EXT_DATA14_SHIFT 2
#define EXT_DATA14_EXT_DATA14 0
#define EXT_DATA14_GPIO43 1

#define EXT_DATA15_REG IOMCRG4
#define EXT_DATA15_MASK 0x3
#define EXT_DATA15_SHIFT 6
#define EXT_DATA15_EXT_DATA15 0
#define EXT_DATA15_GPIO26 1

#define EXT_ADDR17_REG IOMCRG4
#define EXT_ADDR17_MASK 0x3
#define EXT_ADDR17_SHIFT 8
#define EXT_ADDR17_EXT_ADDR17 0
#define EXT_ADDR17_GPIO4 1

#define GPIO37_REG IOMCRS0
#define GPIO37_MASK 0x7
#define GPIO37_SHIFT 12
#define GPIO37_GPIO37 0
#define GPIO37_TCO20 1
#define GPIO37_PWM1 2
#define GPIO37_CSSP_FRM 3
#define GPIO37_DSSP3_FRM 4

#define GPIO28_REG IOMCRG4
#define GPIO28_MASK 0x3
#define GPIO28_SHIFT 10
#define GPIO28_GPIO28 0
#define GPIO28_EXT_SDRAS_N 1
#define GPIO28_UART3_TX 2
#define GPIO28_MSL_OB_DAT2 3

#define GPIO31_REG IOMCRG4
#define GPIO31_MASK 0x3
#define GPIO31_SHIFT 12
#define GPIO31_GPIO31 0
#define GPIO31_EXT_SDCAS_N 1
#define GPIO31_UART3_RX 2

#define GPIO36_REG IOMCRS0
#define GPIO36_MASK 0x7
#define GPIO36_SHIFT 16
#define GPIO36_GPIO36 0
#define GPIO36_TCO19 1
#define GPIO36_PWM0 2
#define GPIO36_CSSP_CLK 3
#define GPIO36_DSSP3_CLK 4

#define GPIO63_REG IOMCRS0
#define GPIO63_MASK 0x7
#define GPIO63_SHIFT 20
#define GPIO63_GPIO63 0
#define GPIO63_TCO15 1
#define GPIO63_UART3_CTS_N 2
#define GPIO63_UART2_RX 3
#define GPIO63_SIM_RST_N 4
#define GPIO63_SIM2_RST_N 5

#define GPIO1_REG IOMCRS0
#define GPIO1_MASK 0x7
#define GPIO1_SHIFT 24
#define GPIO1_GPIO1 0
#define GPIO1_TCO16 1
#define GPIO1_UART3_RTS_N 2
#define GPIO1_UART2_TX 3
#define GPIO1_SIM_DIO 4
#define GPIO1_SIM2_DIO 5

#define GPIO62_REG IOMCRS0
#define GPIO62_MASK 0x7
#define GPIO62_SHIFT 28
#define GPIO62_GPIO62 0
#define GPIO62_TCO17 1
#define GPIO62_UART3_RX 2
#define GPIO62_UART2_CTS_N 3
#define GPIO62_SIM_CLK 4
#define GPIO62_SIM2_CLK 5

#define GPIO3_REG IOMCRG4
#define GPIO3_MASK 0x3
#define GPIO3_SHIFT 24
#define GPIO3_GPIO3 0
#define GPIO3_TCO18 1
#define GPIO3_UART3_TX 2
#define GPIO3_UART2_RTS_N 3

#define EXT_PWE_N_REG IOMCRG4
#define EXT_PWE_N_MASK 0x3
#define EXT_PWE_N_SHIFT 26
#define EXT_PWE_N_EXT_PWE_N 0
#define EXT_PWE_N_PWM2 1
#define EXT_PWE_N_ONE_WIRE_DQ 2

#define KPD_R0_REG IOMCRG5
#define KPD_R0_MASK 0x3
#define KPD_R0_SHIFT 0
#define KPD_R0_KPD_R0 0
#define KPD_R0_MSL_IB_STB 1

#define KPD_R1_REG IOMCRG5
#define KPD_R1_MASK 0x3
#define KPD_R1_SHIFT 2
#define KPD_R1_KPD_R1 0
#define KPD_R1_MSL_RESET_N 1

#define EXT_RDY_REG IOMCRG5
#define EXT_RDY_MASK 0x3
#define EXT_RDY_SHIFT 4
#define EXT_RDY_EXT_RDY 0
#define EXT_RDY_KPD_R6 1

#define EXT_ADDR20_REG IOMCRG5
#define EXT_ADDR20_MASK 0x3
#define EXT_ADDR20_SHIFT 6
#define EXT_ADDR20_EXT_ADDR20 0
#define EXT_ADDR20_GPIO1 1

#define EXT_ADDR21_REG IOMCRG5
#define EXT_ADDR21_MASK 0x3
#define EXT_ADDR21_SHIFT 8
#define EXT_ADDR21_EXT_ADDR21 0
#define EXT_ADDR21_GPIO0 1

#define GPIO25_REG IOMCRG5
#define GPIO25_MASK 0x3
#define GPIO25_SHIFT 10
#define GPIO25_GPIO25 0
#define GPIO25_EXT_CS1_N 1

#define GPIO23_REG IOMCRG5
#define GPIO23_MASK 0x3
#define GPIO23_SHIFT 14
#define GPIO23_GPIO23 0
#define GPIO23_EXT_CS3_N 1
#define GPIO23_PWM2 2

#define GPIO60_REG IOMCRG5
#define GPIO60_MASK 0x3
#define GPIO60_SHIFT 16
#define GPIO60_GPIO60 0
#define GPIO60_EXT_ADDR24 1

#define KPD_R2_REG IOMCRG5
#define KPD_R2_MASK 0x3
#define KPD_R2_SHIFT 18
#define KPD_R2_KPD_R2 0
#define KPD_R2_MSL_IB_DAT0 1

#define KPD_R3_REG IOMCRG5
#define KPD_R3_MASK 0x3
#define KPD_R3_SHIFT 20
#define KPD_R3_KPD_R3 0
#define KPD_R3_MSL_CLK_REQ 1

#define KPD_R4_REG IOMCRG5
#define KPD_R4_MASK 0x3
#define KPD_R4_SHIFT 22
#define KPD_R4_KPD_R4 0
#define KPD_R4_TCO16 1
#define KPD_R4_UART3_CTS_N 2
#define KPD_R4_MSL_OB_DAT0 3

#define KPD_R5_REG IOMCRG5
#define KPD_R5_MASK 0x3
#define KPD_R5_SHIFT 24
#define KPD_R5_KPD_R5 0
#define KPD_R5_TCO15 1
#define KPD_R5_UART3_RTS_N 2
#define KPD_R5_MSL_OB_STB 3

#define GPIO30_REG IOMCRG5
#define GPIO30_MASK 0x3
#define GPIO30_SHIFT 26
#define GPIO30_GPIO30 0
#define GPIO30_EXT_SDCLK1 1
#define GPIO30_MSL_OB_DAT3 2

#define EXT_SDCLK0_REG IOMCRG5
#define EXT_SDCLK0_MASK 0x3
#define EXT_SDCLK0_SHIFT 28
#define EXT_SDCLK0_EXT_SDCLK0 0
#define EXT_SDCLK0_UART3_TX 1

#define KPD_C0_REG IOMCRG5
#define KPD_C0_MASK 0x3
#define KPD_C0_SHIFT 30
#define KPD_C0_KPD_C0 0
#define KPD_C0_MSL_IB_DAT2 1

#define KPD_C1_REG IOMCRG6
#define KPD_C1_MASK 0x3
#define KPD_C1_SHIFT 0
#define KPD_C1_KPD_C1 0
#define KPD_C1_MSL_OB_DAT1 1

#define KPD_C2_REG IOMCRG6
#define KPD_C2_MASK 0x3
#define KPD_C2_SHIFT 2
#define KPD_C2_KPD_C2 0
#define KPD_C2_MSL_IB_DAT1 1

#define KPD_C3_REG IOMCRG6
#define KPD_C3_MASK 0x3
#define KPD_C3_SHIFT 4
#define KPD_C3_KPD_C3 0
#define KPD_C3_MSL_OB_CLK 1

#define KPD_C4_REG IOMCRG6
#define KPD_C4_MASK 0x3
#define KPD_C4_SHIFT 6
#define KPD_C4_KPD_C4 0
#define KPD_C4_TCO18 1
#define KPD_C4_MSL_IB_CLK 2

#define KPD_C5_REG IOMCRG6
#define KPD_C5_MASK 0x3
#define KPD_C5_SHIFT 8
#define KPD_C5_KPD_C5 0
#define KPD_C5_TCO17 1
#define KPD_C5_MSL_13MCLK_OUT 2

#define GPIO29_REG IOMCRG6
#define GPIO29_MASK 0x3
#define GPIO29_SHIFT 10
#define GPIO29_GPIO29 0
#define GPIO29_EXT_SDCKE 1
#define GPIO29_MSL_IB_DAT3 2

#define GPIO21_REG IOMCRG6
#define GPIO21_MASK 0x3
#define GPIO21_SHIFT 12
#define GPIO21_GPIO21 0
#define GPIO21_EXT_ADDR22 1

#define GPIO22_REG IOMCRG6
#define GPIO22_MASK 0x3
#define GPIO22_SHIFT 14
#define GPIO22_GPIO22 0
#define GPIO22_EXT_ADDR23 1

#define GPIO50_REG IOMCRG6
#define GPIO50_MASK 0x3
#define GPIO50_SHIFT 16
#define GPIO50_GPIO50 0
#define GPIO50_EXT_SDCS1_N 1
#define GPIO50_MSL_IB_WAIT 2

#define GPIO51_REG IOMCRG6
#define GPIO51_MASK 0x3
#define GPIO51_SHIFT 18
#define GPIO51_GPIO51 0
#define GPIO51_EXT_SDCS0_N 1
#define GPIO51_MSL_OB_WAIT 2

#define GPIO39_REG IOMCRS1
#define GPIO39_MASK 0x7
#define GPIO39_SHIFT 0
#define GPIO39_GPIO39 0
#define GPIO39_Rotary_Encoder1A 1
#define GPIO39_PWM0 2
#define GPIO39_TCO19 3
#define GPIO39_UART3_TX 4

#define GPIO40_REG IOMCRS1
#define GPIO40_MASK 0x7
#define GPIO40_SHIFT 4
#define GPIO40_GPIO40 0
#define GPIO40_Rotary_Encoder1B 1
#define GPIO40_PWM1 2
#define GPIO40_TCO20 3
#define GPIO40_UART3_RX 4

#define GPIO41_REG IOMCRG6
#define GPIO41_MASK 0x3
#define GPIO41_SHIFT 20
#define GPIO41_GPIO41 0
#define GPIO41_Rotary_Encoder2A 1
#define GPIO41_PWM2 2
#define GPIO41_TCO21 3

#define GPIO42_REG IOMCRG6
#define GPIO42_MASK 0x3
#define GPIO42_SHIFT 22
#define GPIO42_GPIO42 0
#define GPIO42_Rotary_Encoder2B 1
#define GPIO42_PWM3 2
#define GPIO42_TCO22 3

#define GPIO52_REG IOMCRS1
#define GPIO52_MASK 0xF
#define GPIO52_SHIFT 8
#define GPIO52_GPIO52 0
#define GPIO52_UART2_TX 1
#define GPIO52_HSL_DATA0 2
#define GPIO52_DSSP3_RX 3
#define GPIO52_UART1_DSR_N 4

#define GPIO53_REG IOMCRS1
#define GPIO53_MASK 0xF
#define GPIO53_SHIFT 12
#define GPIO53_GPIO53 0
#define GPIO53_UART2_RX 1
#define GPIO53_HSL_DATA1 2
#define GPIO53_DSSP3_TX 3
#define GPIO53_UART1_DTR_N 4

#define GPIO55_REG IOMCRS1
#define GPIO55_MASK 0xF
#define GPIO55_SHIFT 16
#define GPIO55_GPIO55 0
#define GPIO55_DSSP6_CLK 1
#define GPIO55_DSSP3_CLK 2
#define GPIO55_HSL_DATA2 3
#define GPIO55_UART2_CTS_N 4
#define GPIO55_CSSP_CLK 5
#define GPIO55_UART1_DCD 6

#define GPIO27_REG IOMCRS1
#define GPIO27_MASK 0xF
#define GPIO27_SHIFT 20
#define GPIO27_GPIO27 0
#define GPIO27_DSSP6_FRM 1
#define GPIO27_DSSP3_FRM 2
#define GPIO27_HSL_DATA3 3
#define GPIO27_UART2_RTS_N 4
#define GPIO27_CSSP_FRM 5
#define GPIO27_UART1_RI 6

#define GPIO56_REG IOMCRS1
#define GPIO56_MASK 0xF
#define GPIO56_SHIFT 24
#define GPIO56_GPIO56 0
#define GPIO56_DSSP6_RX 1
#define GPIO56_DSSP3_RX 2
#define GPIO56_HSL_DATA4 3
#define GPIO56_CSSP_RX 4
#define GPIO56_UART1_CTS_N 5

#define GPIO57_REG IOMCRS1
#define GPIO57_MASK 0xF
#define GPIO57_SHIFT 28
#define GPIO57_GPIO57 0
#define GPIO57_DSSP6_TX 1
#define GPIO57_DSSP3_TX 2
#define GPIO57_HSL_CLK 3
#define GPIO57_CSSP_TX 4
#define GPIO57_UART1_RTS_N 5

#define GPIO54_REG IOMCRG6
#define GPIO54_MASK 0x3
#define GPIO54_SHIFT 24
#define GPIO54_GPIO54 0
#define GPIO54_UART1_RX 1

#define GPIO33_REG IOMCRG6
#define GPIO33_MASK 0x3
#define GPIO33_SHIFT 26
#define GPIO33_GPIO33 0
#define GPIO33_MUX_CLK0 1
#define GPIO33_UART1_TX 2

#define GPIO26_REG IOMCRG6
#define GPIO26_MASK 0x3
#define GPIO26_SHIFT 28
#define GPIO26_GPIO26 0
#define GPIO26_PWM1 1
#define GPIO26_MUX_CLK0 2

#define MN_CLK_OUT0_REG IOMCRG6
#define MN_CLK_OUT0_MASK 0x3
#define MN_CLK_OUT0_SHIFT 30
#define MN_CLK_OUT0_MN_CLK_OUT0 0
#define MN_CLK_OUT0_PWM0 1

#define EXT_ADDR16_REG IOMCRG7
#define EXT_ADDR16_MASK 0x3
#define EXT_ADDR16_SHIFT 0
#define EXT_ADDR16_EXT_ADDR16 0
#define EXT_ADDR16_GPIO5 1

#define EXT_ADDR15_REG IOMCRG7
#define EXT_ADDR15_MASK 0x3
#define EXT_ADDR15_SHIFT 2
#define EXT_ADDR15_EXT_ADDR15 0
#define EXT_ADDR15_GPIO6 1

#define EXT_ADDR14_REG IOMCRG7
#define EXT_ADDR14_MASK 0x3
#define EXT_ADDR14_SHIFT 4
#define EXT_ADDR14_EXT_ADDR14 0
#define EXT_ADDR14_GPIO7 1

#define EXT_ADDR13_REG IOMCRG7
#define EXT_ADDR13_MASK 0x3
#define EXT_ADDR13_SHIFT 6
#define EXT_ADDR13_EXT_ADDR13 0
#define EXT_ADDR13_GPIO8 1

#define EXT_ADDR11_REG IOMCRG7
#define EXT_ADDR11_MASK 0x3
#define EXT_ADDR11_SHIFT 10
#define EXT_ADDR11_EXT_ADDR11 0
#define EXT_ADDR11_GPIO9 1

#define EXT_ADDR10_REG IOMCRG7
#define EXT_ADDR10_MASK 0x3
#define EXT_ADDR10_SHIFT 12
#define EXT_ADDR10_EXT_ADDR10 0
#define EXT_ADDR10_GPIO11 1

#define EXT_ADDR9_REG IOMCRG7
#define EXT_ADDR9_MASK 0x3
#define EXT_ADDR9_SHIFT 14
#define EXT_ADDR9_EXT_ADDR9 0
#define EXT_ADDR9_GPIO12 1

#define EXT_DQM1_REG IOMCRG7
#define EXT_DQM1_MASK 0x3
#define EXT_DQM1_SHIFT 18
#define EXT_DQM1_EXT_DQM1 0
#define EXT_DQM1_GPIO49 1

#define EXT_DQM0_REG IOMCRG7
#define EXT_DQM0_MASK 0x3
#define EXT_DQM0_SHIFT 20
#define EXT_DQM0_EXT_DQM0 0
#define EXT_DQM0_GPIO48 1

#define EXT_ADDR19_REG IOMCRG7
#define EXT_ADDR19_MASK 0x3
#define EXT_ADDR19_SHIFT 22
#define EXT_ADDR19_EXT_ADDR19 0
#define EXT_ADDR19_GPIO2 1

#define EXT_ADDR18_REG IOMCRG7
#define EXT_ADDR18_MASK 0x3
#define EXT_ADDR18_SHIFT 24
#define EXT_ADDR18_EXT_ADDR18 0
#define EXT_ADDR18_GPIO3 1

#define EXT_ADDR8_REG IOMCRG7
#define EXT_ADDR8_MASK 0x3
#define EXT_ADDR8_SHIFT 26
#define EXT_ADDR8_EXT_ADDR8 0
#define EXT_ADDR8_GPIO13 1

#define EXT_ADDR7_REG IOMCRG7
#define EXT_ADDR7_MASK 0x3
#define EXT_ADDR7_SHIFT 28
#define EXT_ADDR7_EXT_ADDR7 0
#define EXT_ADDR7_GPIO14 1

#define EXT_ADDR6_REG IOMCRG7
#define EXT_ADDR6_MASK 0x3
#define EXT_ADDR6_SHIFT 30
#define EXT_ADDR6_EXT_ADDR6 0
#define EXT_ADDR6_GPIO15 1

#define EXT_ADDR5_REG IOMCRG8
#define EXT_ADDR5_MASK 0x3
#define EXT_ADDR5_SHIFT 0
#define EXT_ADDR5_EXT_ADDR5 0
#define EXT_ADDR5_GPIO16 1

#define EXT_ADDR4_REG IOMCRG8
#define EXT_ADDR4_MASK 0x3
#define EXT_ADDR4_SHIFT 2
#define EXT_ADDR4_EXT_ADDR4 0
#define EXT_ADDR4_GPIO17 1

#define EXT_ADDR3_REG IOMCRG8
#define EXT_ADDR3_MASK 0x3
#define EXT_ADDR3_SHIFT 4
#define EXT_ADDR3_EXT_ADDR3 0
#define EXT_ADDR3_GPIO18 1

#define EXT_ADDR2_REG IOMCRG8
#define EXT_ADDR2_MASK 0x3
#define EXT_ADDR2_SHIFT 6
#define EXT_ADDR2_EXT_ADDR2 0
#define EXT_ADDR2_GPIO19 1

#define GPIO32_REG IOMCRG8
#define GPIO32_MASK 0x3
#define GPIO32_SHIFT 8
#define GPIO32_GPIO32 0
#define GPIO32_I2C_SDA 1
#define GPIO32_CSSP_CLK 2
#define GPIO32_DSSP3_CLK 3

#define GPIO2_REG IOMCRG8
#define GPIO2_MASK 0x3
#define GPIO2_SHIFT 10
#define GPIO2_GPIO2 0
#define GPIO2_I2C_SCL 1
#define GPIO2_CSSP_FRM 2
#define GPIO2_DSSP3_FRM 3

#define GPIO5_REG IOMCRS2
#define GPIO5_MASK 0x7
#define GPIO5_SHIFT 0
#define GPIO5_GPIO5 0
#define GPIO5_MM_DAT3_CS1 1
#define GPIO5_TCO22 2
#define GPIO5_PWM0 3
#define GPIO5_SIM_RST_N 4
#define GPIO5_SIM2_RST_N 5
#define GPIO5_ONE_WIRE_DQ 6

#define GPIO6_REG IOMCRS2
#define GPIO6_MASK 0x7
#define GPIO6_SHIFT 4
#define GPIO6_GPIO6 0
#define GPIO6_MM_DAT0 1
#define GPIO6_MS_DIO 2
#define GPIO6_SIM_DIO 3
#define GPIO6_SIM2_DIO 4

#define GPIO7_REG IOMCRG8
#define GPIO7_MASK 0x3
#define GPIO7_SHIFT 12
#define GPIO7_GPIO7 0
#define GPIO7_MM_CLK 1
#define GPIO7_MS_BS 2

#define GPIO4_REG IOMCRG8
#define GPIO4_MASK 0x7
#define GPIO4_SHIFT 14
#define GPIO4_GPIO4 0
#define GPIO4_MM_DAT2_CS0 1
#define GPIO4_SIM_CLK 2
#define GPIO4_SIM2_CLK 3

#define GPIO43_REG IOMCRG8
#define GPIO43_MASK 0x3
#define GPIO43_SHIFT 16
#define GPIO43_GPIO43 0
#define GPIO43_I2S_FS 1
#define GPIO43_HSL_DATA0 2

#define GPIO44_REG IOMCRS2
#define GPIO44_MASK 0x7
#define GPIO44_SHIFT 8
#define GPIO44_GPIO44 0
#define GPIO44_I2S_DI 1
#define GPIO44_CSSP_RX 2
#define GPIO44_HSL_DATA1 3
#define GPIO44_DSSP3_RX 4

#endif
