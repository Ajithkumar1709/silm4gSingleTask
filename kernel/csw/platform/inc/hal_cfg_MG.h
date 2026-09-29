/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/


/***************************************************************************
*
* Filename: hal_cfg_DEFAULT.h
*
* COMMON DESCRIPTION:
*  Configure the PLATFORM depnding upon HW-presence and SW-FLAVOR requirements.
*  Refer also other configurations in inc_PLAT.mak, Arbel_Plat.mak, syscfg.h files.
*
* ==================================================================
*       This file is cloned from the hal_cfg_DEFAULT.h
*
*         !!!  DO NOT ADD/REMOVE ANY LINE BELOW !!!
*
*            The only permitted modifications are
*      #undef/#define or double-slash-commentary for existing lines
******************************************************************************/

#ifdef _HAL_CFG_FULL_INCLUDE_
#error _HAL_CFG_FULL_INCLUDE_ called more then once
#endif

#ifndef _HAL_CFG_FULL_INCLUDE_
#define _HAL_CFG_FULL_INCLUDE_

/******  Possibilities:
//new       - new flag still   not in use but to be used
//old       - old flag already not in use and to be deleted
//mak       - flag inherited from the MAKEFILE
#undef      - may be defined in MAKFILE, undefine it explicitly
#define     - define flag
//#define   - do not define
*************************/

/*******************************************************************************
*        APP & COM - flags could be present on either or both sides
********************************************************************************/
#define    _OSA_ENABLED_
#define    _DIAG_ENABLED_
#define    _UART_ENABLED_
//new       UART_MAX_ENABLED     1
#define     EE_HANDLER_ENABLE
#define     WATCHDOG_ENABLED            /* Refer also WATCHDOG_MANAGER_ENABLED */
#define    _I2C_ENABLED_
//new       I2C_MAX_ENABLED      1
#define    _PMC_ENABLED_
#define     PMC_TYPE_MICCO
#define     PMC_TYPE_LEVANTE
//#define  _ONEWIRE_ENABLED_
//#define  _SSP_ENABLED_                - refer syscfg.h
//mak       NVM_INCLUDE                 /* From makefile; opens also INTEL_FDI */
//new       POWER_MANAGEMENT_ENABLED    - refer syscfg.h
//new       CACHE_DISABLE
//#define   DISABLE_DCACHE
//mak       L2_CACHE_ENABLE
//new       MMU_ENABLED
//new       INT_MEM_ENABLED
//new       INT_SRAM_ENABLED
//new       EXT_MEM_ENABLED
//new       MSL_ENABLED
//new       ACIPC_ENABLED
//new       DMA_ENABLED
//new       SHMEM_ENABLED
//mak       NO_AUDIO                    /* Refer also resulting  AUDIO_APP_ENABLE */
//#define  _S_INTC_                     /* Enable/Disable Secondary INTC */
//mak      _EPROM_EXIST_
//mak       RELIABLE_DATA
//mak       MIPS_TEST_RAM
//new       DLM_ENABLED
//#define     BSP_LOG_RECORD_ENABLE
//#define   DBG_JTAG_IS_CONNECTED       /*QT: Always JtagIsConnected=TRUE prevents WDT, PM ...*/
//#define   DBG_NO_RW_PROTECTION        /*QT*/
//define    ENABLE_DIAG_LOGGER
//old      _EXTENDED_GPIO_
//mak       CROSS_PLATFORM_INCLUDE

/*******************************************************************************
*         COM - Communication side only specific flags
********************************************************************************/
#if defined(FLAVOR_COM) || defined(FLAVOR_ONECPU)
#define     IPC_ENABLED                 /* Cellular Modem */
#define    _USIM_ENABLED_
#define     USIM_MAX_ENABLED            1
#define     WATCHDOG_MANAGER_ENABLED    /*kick behavior manager*/
//#define    _RTC_ENABLED_              /* separatelly defined for APS and for COM */
#define     OS_TICK_MANAGER_ENABLED     /* if ENA, restore OS_TICK from the 32kClock; else use simple NU-OStick*/
#endif//COM

/*******************************************************************************
*        APP - Application side only specific flags
*              These flags present for FLAVOR_APP or FLAVOR_ONECPU
********************************************************************************/
#if defined(FLAVOR_APP) || defined(FLAVOR_ONECPU)
#define    _USB_ENABLED_
//new       USB2_ENABLED
#define     USB_CABLE_DETECTION_ENABLED
#define    _RTC_ENABLED_                /* separatelly defined for APS and for COM */
//#define   WATCHDOG_MANAGER_ENABLED    /*kick behavior manager*/
//#define  _LCD_ENABLED_
//#define   LCD_MINI_ENABLED
//#define  _KEYPAD_ENABLED_
//#define  _CAMIF_ENABLED_
//#define  _MMCSD_ENABLED_              /* Memory Card "MEMC" */
//#define   BLUETOOTH_ENABLED
//#define   IRDA_ENABLED
//#define   TOUCH_SCREEN_ENABLED
//#define  _ME_ENABLED_
#define     OS_TICK_MANAGER_ENABLED     /* if ENA, restore OS_TICK from the 32kClock; else use simple NU-OStick*/
#define    _I2S_ENABLED_
//new       MMI_ENABLED                 /* KEYPAD, *LCD*, MMCSD, SDMMC - removed and not supported yet */
#endif//APP


/*******************************************************************************
*     OVERWRITES
********************************************************************************/
#if defined(NODIAG)
#undef _DIAG_ENABLED_
#endif
#if !defined(_DIAG_ENABLED_) && !defined(NODIAG)
//There are 2 flags: NODIAG coming from makefile and _DIAG_ENABLED_ from here
//Let's fix consistency
#define NODIAG
#endif

#if defined(NVM_INCLUDE)
#if !defined(INTEL_FDI)
#define INTEL_FDI
#endif
#endif

#if defined(FLAVOR_DIET_RAM)
#undef  _UART_ENABLED_
#undef  PMC_TYPE_MICCO
#endif

//Assuming DIAGUART as the default choice for MINIPLAT
#if defined(FLAVOR_MINIPLAT) && defined(_DIAG_ENABLED_)
#define _UART_ENABLED_
#endif

#endif //_HAL_CFG_FULL_INCLUDE_



/***********************************************************************
*************                                   ************************
***********      List of main flags defined        *********************
***********    in Platform's inc**.mak files       *********************
***********   and dependig upon Target Variants    *********************
***********       (for information only)           *********************
*************                                   ************************
************************************************************************
VARIANT_LIST_SPREAD2 += FLAVOR_APP
VARIANT_LIST_SPREAD2 += FLAVOR_COM
VARIANT_LIST_SPREAD2 += FEATURE_SHMEM
VARIANT_LIST_SPREAD2 += FLAVOR_MINIPLAT
VARIANT_LIST_SPREAD2 += FLAVOR_ONECPU
VARIANT_LIST_SPREAD2 += SILICON_XSCALE_CORE
TARGET_DFLAGS      += -DSILICON_HARBELL
VARIANT_LIST_SPREAD2 += SILICON_PV2 SILICON_SEAGULL
VARIANT_LIST_SPREAD2 += SILICON_TTC_CORE_SEAGULL
VARIANT_LIST_SPREAD2 += SILICON_TTC
TARGET_DFLAGS      += -DSILICON_TTC_CORE_MOHAWK
--------------------------------------------------------
TARGET_DFLAGS += -DUPGRADE_ARBEL_PLATFORM  - used by L1
--------------------------------------------------------
TARGET_DFLAGS += -DL2_CACHE_ENABLE
TARGET_DFLAGS += -DCREATE_L2_RAM
TARGET_DFLAGS += -DGFS_API
TARGET_DFLAGS += -DRELIABLE_DATA
TARGET_DFLAGS += -DENABLE_ACIPC
TARGET_DFLAGS += -D_DATAOMSL_ENABLED_
TARGET_DFLAGS += -D_DIAG_USE_COMMSTACK_
TARGET_DFLAGS += -DUSB_CABLE_DETECTION_VIA_PMIC
TARGET_CFLAGS += -DDATA_COLLECTOR_IMPL
TARGET_CFLAGS += -DISPT_OVER_SSP
TARGET_CFLAGS += -DMIPS_TEST -DMIPS_TEST_RAM
TARGET_DFLAGS += -DDIAGNEWHEADER
TARGET_DFLAGS += -DNODIAG
TARGET_DFLAGS += -DDIAG_SSP_USE_DMA
TARGET_DFLAGS += -D_DIAG_USE_SSP_
TARGET_DFLAGS += -D_DIAG_DISABLE_USB_
TARGET_DFLAGS += -DDIAG_NO_GKI
TARGET_DFLAGS += -DGFS_OVER_RAM
TARGET_DFLAGS += -DDLM_TAVOR
TARGET_DFLAGS += -DPM_D2NONE_MODE
TARGET_DFLAGS += -DPM_D2ALIKE_MODE
TARGET_DFLAGS += -DPM_D2FULL_MODE
TARGET_DFLAGS += -DPM_DEBUG_MODE_ENABLED
TARGET_DFLAGS += -DPM_EXT_DBG_INT_ARR
--------------------------------------------------------
TARGET_DFLAGS += -DMSL_INCLUDE
TARGET_DFLAGS += -DMSL_POOL_MEM
TARGET_DFLAGS += -DMSL_EXCLUDE_CCI
TARGET_DFLAGS += -DNO_AUDIO
TARGET_DFLAGS += -D_EPROM_EXIST_
TARGET_DFLAGS += -DNVM_INCLUDE
TARGET_DFLAGS += -DFDI_INTERNAL_FLASH
TARGET_DFLAGS += -DNVM_OVER_RAM
TARGET_CFLAGS += -DDIAG_SSP_DOUBLE_BUFFER_USE_DYNAMIC_ALLOCATION
TARGET or GROUP  -DCROSS_PLATFORM_INCLUDE
************************************************************************
************************************************************************/
