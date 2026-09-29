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


#ifndef _PS_NVM_DEFS_H_
#define _PS_NVM_DEFS_H_

#define SYSTEM_CURRENT_VERSION   "4.0"
#define SYSTEM_FILE_NAME         "SystemControl.nvm"
//#define CELL_LOCK_FILE_NAME      "CellLockProfile"
#define IMSNW_REPORTING_FILE_NAME  "IMSNWReportingProfile"
#define TERMINAL_PROFILE_FILE_NAME   "TerminalProfile"
//#define BACKGROUND_SEARCH_FILE_NAME      "BackgroundSearch.nvm"
#define PDN_CONFIG_FILE_NAME      "PdnConfig.nvm"
#define DIP_CHANNEL_CHANGE_FILE_NAME         "DipChannelChange.nvm"
/*add by xyma for CQ00125818 begin*/
/* Added by Daniel for PSM 20180201, begin */
#define PSM_CONTEXT_FILE_NAME    "PsmContextProfile.nvm"  //SIM0
#define PSM_CONTEXT_FILE_NAME1    "PsmContextProfile1.nvm"   //SIM1
/* Added by Daniel for PSM 20180201, end */
/*add by xyma for CQ00125818 begin*/
/* TAVOR-HARBEL Notes:
* - Currently only FEATURES are really config in the ps_init.c
* - The flag _HERMON_ is used. ARBEL is not _HERMON_ family
* - Temporary there are 2 different variants with/without NVM (INTEL_FDI)
*     The non-NVM variant has 2 sub-variants with/without WB (TAVOR_WB_USER_MODE)
*/

//                                   ---------------------------- Features -----------------------------
//                                   PS_INIT_AUTO    GSM_DRX_SLEEP;    WBCDMA_DRX_SLEEP     IN_GSM       ONLY_GSM  CIRCUIT_SWITCHED_ONLY   RESERVED    UICC_PROTOCOL_T0_ONLY
#ifdef _HERMON_
#define SYSTEM_FEATURES_DEFAULT_DATA {SYS_ENABLE,    SYS_ENABLE,        SYS_ENABLE,      SYS_DISABLE,  SYS_DISABLE,   SYS_DISABLE,     SYS_DISABLE,    SYS_DISABLE  }
#else
       /*ARBEL*/
 #ifdef INTEL_FDI
 #if defined (GERAN_ONLY)
#define SYSTEM_FEATURES_DEFAULT_DATA {SYS_ENABLE,    SYS_ENABLE,        SYS_ENABLE,      SYS_ENABLE,    SYS_ENABLE,   SYS_DISABLE,     SYS_DISABLE,     SYS_DISABLE  }
 #else /*GERAN_ONLY*/
#define SYSTEM_FEATURES_DEFAULT_DATA {SYS_ENABLE,    SYS_ENABLE,        SYS_ENABLE,      SYS_DISABLE,   SYS_DISABLE,  SYS_DISABLE,     SYS_DISABLE,     SYS_DISABLE  }
#endif /*GERAN_ONLY*/
 #endif
 #ifndef INTEL_FDI
 #if defined (TAVOR_WB_USER_MODE)
#define SYSTEM_FEATURES_DEFAULT_DATA {SYS_ENABLE,    SYS_ENABLE,        SYS_ENABLE,      SYS_DISABLE,   SYS_DISABLE,  SYS_DISABLE,     SYS_DISABLE,     SYS_DISABLE  }
 #else
#define SYSTEM_FEATURES_DEFAULT_DATA {SYS_ENABLE,    SYS_ENABLE,        SYS_ENABLE,      SYS_ENABLE,    SYS_DISABLE,  SYS_DISABLE,     SYS_DISABLE,     SYS_DISABLE  }
 #endif
 #endif
       /*ARBEL end*/
#endif

#define SYSTEM_FEATURES_DEFAULT_DATA_SIZE (8)

//                                       ---- Features under development ----
//
#define SYSTEM_DEV_FEATURES_DEFAULT_DATA      {{ NVM_ACCESS_NORMAL_READ_WRITE, 0, 0 }, { NVM_ACCESS_NORMAL_READ_WRITE, 0, 0 }}
#define SYSTEM_DEV_FEATURES_DEFAULT_DATA_SIZE (2)




//                                     ------Xscale Power Management --------
// 0 (disable), 1 (core only), 3 (core+PX), 7 (core+PX+drowsy), F (full)
#define XSCALE_POWER_MANAGEMENT_DEFAULT_DATA  { FULL }
#define XSCALE_POWER_MANAGEMENT_DEFAULT_DATA_SIZE (1)


//                                   ------USB Configuration --------
#if defined (_DIAG_USE_COMMSTACK_)
  #define USB_CONFIGURATION_DEFAULT_DATA  { ICAT }
#else
  #define USB_CONFIGURATION_DEFAULT_DATA  { ICAT_MODEM } /* ICAT only + AT/MODEM        */
#endif

#define USB_CONFIGURATION_DEFAULT_DATA_SIZE (1)

#define UART_CONFIGURATION_DEFAULT_DATA  { UF_UART_1_2_3 }
#define UART_CONFIGURATION_DEFAULT_DATA_SIZE (1)

/*CQ00050854 20131218 by zhangxia begin*/
#define VENDOR_SPECIFIC_INFO_NULL                     (0)
#define VENDOR_SPECIFIC_INFO_ATT                      (0x01)
#define VENDOR_SPECIFIC_INFO_CMCC                     (0x02)
#define VENDOR_SPECIFIC_INFO_IOT                      (0x04)
#define VENDOR_SPECIFIC_INFO_TELCEL                   (0x08)
#define VENDOR_SPECIFIC_INFO_H3G                       (0x10)

#define VENDOR_SPECIFIC_INFO_VDF                       (0x20)

#define VENDOR_SPECIFIC_INFO_MANUFACTURE_SILVER        (0x40)

#define VENDOR_SPECIFIC_INFO_EURORG                    (0x80)
#define VENDOR_SPECIFIC_INFO_TMOBILE                   (0x100)
#define VENDOR_SPECIFIC_INFO_VERIZON                   (0x200)
#define VENDOR_SPECIFIC_INFO_HP                        (0x400)
#define SPECIFIC_INFO_CLOSE_RAMLOG_SWITCH              (0x800)
#define VENDOR_SPECIFIC_INFO_2G_ROAMING                (0x1000)
#define VENDOR_SPECIFIC_INFO_RRM                       (0x2000)

#define VENDOR_SPECIFIC_INFO_CMCC_FRSUPPORT             (0x4000)
#define VENDOR_SPECIFIC_INFO_SILENT_RESET               (0x8000)

#define VENDOR_SPECIFIC_INFO_PS_OPT                            (0x10000)

#define VENDOR_SPECIFIC_INFO_HOMETEST                  (0x20000)

#define VENDOR_SPECIFIC_INFO_MTNET                     (0x40000)
/*CQ00050854 20131218 by zhangxia end*/


/* default for psNvmCreate*/
#define VENDOR_SPECIFIC_INFO_DEFAULT_DATA (VENDOR_SPECIFIC_INFO_CMCC_FRSUPPORT)
/*Fixed CQ00024251 xyzheng for U+D optimistion start 2012-11-07*/
#if !defined (ON_PC)
/*Fixed for U+D begin date: 2010-08-11 yinfei*/
/* 0: optimization off  1: 1000 threhold version  2: strict limit version for higher quility*/
#define U_D_OPT_METHOD_OFF (0)
#define U_D_OPT_METHOD_VERSION_1 (1)
#define U_D_OPT_METHOD_VERSION_2 (2)
/*Fixed for U+D End date: 2010-08-11 yinfei*/
#endif
/*Fixed CQ00024251 xyzheng for U+D optimistion end 2012-11-07*/
/*Alan DIP Channel support -- START*/
#define CHAN_FREQ_MAP_STRUCT_DEFAULT_VALUE (-1)
#define CHAN_FREQ_MAP_STRUCT_MAP_ARRAY_SIZE (256)  /*64 -> 256, Cgliu, 2013-09-22*/
#define CHAN_FREQ_MAP_STRUCT_RESERVE_SIZE (2)
/*Alan DIP Channel support -- END*/
#endif

