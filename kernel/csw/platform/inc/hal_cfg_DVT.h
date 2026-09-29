/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

#ifndef _HAL_CFG_DVT_
#define _HAL_CFG_DVT_

#if !defined (FLAVOR_MINIPLAT) && !defined (_QT_)

/*******************************************************************************
 *                      Driver Validation Test (DVT)
 ******************************************************************************/

// Drivers Validation Team(DVT)  Defines.
#if defined (PLATFORM_ONLY)
   //#if defined(_TAVOR_BOERNE_) || defined(_TAVOR_HARBELL_) || defined(SILICON_PV2)
   #if defined(_TAVOR_BOERNE_) || defined(SILICON_PV2)
      #define COMMON_DVT_ENABLE
      #define I2C_TEST_ENABLE
      #define UART_TEST_ENABLE
   #endif
   //#if defined (_TAVOR_HARBELL_)|| defined(SILICON_PV2)
   #if defined(SILICON_PV2)
      #define INTC_TEST_DVT_ENABLE
      #define USIM_TEST_DVT_ENABLE
      #define DMA_TEST_ENABLE
      //#define FDI_TEST_ENABLE
      //#define POWER_TEST_DVT_ENABLE
      //#define PMCHIP_TEST_DVT_ENABLE
      #define LDMA_TEST_DVT_ENABLE
  #endif
#endif    //PLATFORM_ONLY


// Non-HARBELL platforms
//#define COMMON_DVT_ENABLE
//#define DIAG_TEST_ENABLE
//#define I2C_TEST_ENABLE
//#define DMA_TEST_ENABLE
//#define RTCC_TEST_ENABLE
//#define RTC_TEST_ENABLE
//#define FDI_TEST_ENABLE
//#define FAT12_TEST_ENABLE
//#define TIMER_TEST_ENABLE
//#define MMCSD_TEST_ENABLE
//#define WATCHDOG_TEST_ENABLE
//#define USIM_TEST_ENABLE
//#define UART_TEST_ENABLE
//#define LCDIF_TEST_ENABLE
//#define INTC_TEST_ENABLE
//#define SSP_TEST_ENABLE
//#define KEYPAD_SILICON_TEST_ENABLE
// Harbell
    //#define COMMON_DVT_ENABLE
    //#define I2C_TEST_ENABLE
    //#define UART_TEST_ENABLE
    //#define UART_PC_TEST_ENABLE
#ifdef UART_PC_TEST_ENABLE
    #define DVT_DOUBLE_BUFFER_CLASS
#endif
	//#define IPC_TEST_DVT_ENABLE
    //#define TIMER_TEST_DVT_ENABLE
	//#define INTC_TEST_DVT_ENABLE
	//#define LDMA_TEST_DVT_ENABLE
	//#define RM_TEST_DVT_ENABLE
	//#define SSP_TEST_DVT_ENABLE
    //#define USIM_TEST_DVT_ENABLE
	//#define FDI_TEST_ENABLE

#endif// !defined (FLAVOR_MINIPLAT) && !defined (_QT_)

#endif	 // _HAL_CFG_DVT_
