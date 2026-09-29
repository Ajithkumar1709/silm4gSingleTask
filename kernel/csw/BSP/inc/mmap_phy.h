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
// Cotulla CCD board memory map definitions
//
#ifndef MMAP_PHY_H
#define MMAP_PHY_H
#include "global_types.h"
#include "hal_cfg.h" /* SRAM allocation depends on ME module */

#define CS0_BASE                        0x00000000
#define CS1_BASE                        0x04000000
#define CS2_BASE                        0x08000000
#define CS3_BASE                        0x0C000000
#define CS4_BASE                        0x10000000
#define CS5_BASE                        0x14000000


#define MSA_EXT_BOOT_START_ADDRESS	XSCALE_SRAM
#define XSCALE_FLASH                0x80000000
#define XSCALE_FLASH_BASE           0x00000000
#define XSCALE_FLASH_SIZE           0x00400000

#define ADDRESS_IS_IN_XSCALE_FLASH(address)    (((UINT32)(address) < (UINT32)XSCALE_FLASH_SIZE) ? TRUE : FALSE )


// Internal SRAM:
#if defined(_TAVOR_BOERNE_)
   #define XSCALE_SRAM                0x5C000000  /* BOERNE INT_RAM */
   #define XSCALE_SRAM_SIZE           0x20000
   // L2$ - Tavor
   #define L2_CACHE_RAM_SIZE          0x10000                    /* 64KB for code- !!! bug we can not use all L2$ only 192KB- bug !!*/
#elif defined (INTEL_2CHIP_PLAT_BVD)
  #define XSCALE_SRAM                 0x5C000000  /* BULVERDE INT_RAM */
  #define XSCALE_SRAM_SIZE            0x40000
#elif defined(_HERMON_B0_SILICON_)
  #define XSCALE_SRAM                 0x18000000  /* HERMON INT_RAM */
  #if defined(_ME_ENABLED_)
  #define XSCALE_SRAM_SIZE            0x50000 /*bank 5 taken for ME use*/
  #else
  #define XSCALE_SRAM_SIZE            0x60000
  #endif
#endif


//======  APPS/COM "cross-mapping"   ================
// The ARBEL_BASE_ADDRESS 0xD0.../0xBF... is obsolet
//#if defined (FLAVOR_APP)
#if defined (_TAVOR_BOERNE_)
// (Physical HW) and (Virtual SW-mapped) Prefix for COMM DDR address seen from APPS-BOERNE mapping
//#define COM_ADDR_MAX_SIZE           0x01000000 /*max-max physical 16MB*/
#ifdef PHS_SW_DEMO_TTC
#if 1    //20081010
#define APPSMAP_COM_ADDR_HW_PHY     0x07000000
#define APPSMAP_COM_ADDR_SW_VIRT    0x07000000
#if 0
#define APPSMAP_COM_ADDR_HW_PHY     0x0F000000
#define APPSMAP_COM_ADDR_SW_VIRT    0x0F000000
#endif
#else
#define APPSMAP_COM_ADDR_HW_PHY     0x03000000
#define APPSMAP_COM_ADDR_SW_VIRT    0x03000000
#endif
#else
#define APPSMAP_COM_ADDR_HW_PHY     0xBF000000
#define APPSMAP_COM_ADDR_SW_VIRT    0xD0000000
#endif
#endif



#if defined(_HERMON_B0_SILICON_) && !defined(_TAVOR_BOERNE_)
#define APB_BASE                    0x40000000
#define MEMC_CONFIG_REG             0x48000000
#define XSCALE_PX_GASKET_REGS       0x50000000
#define MSA_FLASH                   0x84000000
#define SDRAM_PARTITION0            0xA0000000
#define SDRAM_PARTITION1            0xA4000000

#define DPB_BASE                    0xC0000000
#define MSA_FLASH_BASE              0xD0000000
#define MSA_EXT_FLASH_BASE			0x01000000
#define MSA_PX_SLAVE_GASKET         0xE0000000
#define END_OF_MEMORY               0xFFFFFFFF
#endif

#if defined(_TAVOR_BOERNE_)
#define PX_BUS_1                    0x58000000
#define PX_BUS_2_SIDECAR            0x54000000
#define PX_BUS_1_CAMERA             0x50000000
#define PX_BUS_1_USB_HOST           0x4C000000
#define PX_BUS_1_SMEMC              0x4A000000
#define PX_BUS_1_DMEMC              0x48000000
#define PX_BUS_1_LCD				0x44000000
#define PX_BUS                      0x40000000
#define BOERNE_SMEMC_CS1            0x3C000000 /*256KB*/
#define BOERNE_SMEMC_CS0            0x0C000000 /*256KB*/
#define BOERNE_DMEMC_CS1            0xFC000000 /*1GB*/
#define BOERNE_DMEMC_CS0            0xBC000000 /*1GB*/
#define DDR_BASE                    0x80000000
#define DDR_EXEC_REGION				0x80000000
#define DDR_EXEC_REGION_SIZE		(_48MB+_2MB) /* = 50MB - we reduce from 56MB to 50MB the 6MB is used for gerenal use
															 not for object allocation - currently use for stacks before
												  *          we have OS runing */
//#define ARBEL_EXEC_REG              ARBEL_BASE_ADDRESS
//#define ARBEL_EXEC_REG_VIRT         (ARBEL_BASE_ADDRESS+0x11000000)     //  Harbell's Mapping is used by Boerne as virtual address for the Harbell.
#endif//_TAVOR_BOERNE_

#if defined(SILICON_TTC) ||defined (PHS_SW_DEMO_TTC)
#define TTC_DDR_BASE     0x00000000
#define TTC_SQU_BASE     0xD1000000
#define TTC_SQU_SIZE     0x00020000
#define TTC_APB_AXI_BASE 0xD4000000
#define TTC_APB_AXI_SIZE 0x00400000
#define TTC_APB_EXT_BASE 0xD3000000
#define TTC_APB_EXT_SIZE 0x01000000
#define TTC_MCU_BASE     0xB0000000
#define TTC_MCU_SIZE     0x00100000
#define XSCALE_SRAM      TTC_SQU_BASE                 // alias
#define XSCALE_SRAM_SIZE TTC_SQU_SIZE                 // alias
#endif

#define EXCEPTION_VECTOR_VIRT		0x00000000

#define END_OF_MEMORY               0xFFFFFFFF


#if defined (_HERMON_B0_SILICON_)
/* DSSP  */
#define DSSP1_BASE                       0xC0A01800  /*  TX ssp   */
#define DSSP2_BASE                       0xC0A01A00  /*  IQ ssp   */
#define DSSP4_BASE                       0xC0A01C00  /*  RF ssp  */
#define DSSP5_BASE                       0xC0A01E00  /*  AUX ssp */
/* GSSP  */
#define DSSP3_BASE                     0xC0A01000   /* GSSP0_BASE - AUDIO ssp */
#define DSSP6_BASE                     0xC0A01200   /* GSSP1_BASE - DAI SSP    */

#endif  /* _HERMON_B0_SILICON_  */

#endif //MMAP_H
