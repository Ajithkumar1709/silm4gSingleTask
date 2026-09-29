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

#if !defined (_DIAG_COMM_OSIF_H_)
#define _DIAG_COMM_OSIF_H_

#include "diag_rx.h"		// for DB_VERSION_SERVICE

// Define modes of ACIPC work
#if (defined OSA_NUCLEUS)
#define ACIPCD_TX_ACTION ACIPCD_HANDLE_CACHE ;
#define ACIPCD_RX_ACTION ACIPCD_HANDLE_CACHE ;
#endif
#if (defined OSA_WINCE)
#define ACIPCD_TX_ACTION ACIPCD_COPY ;
#define ACIPCD_RX_ACTION ACIPCD_DO_NOTHING ;
#endif

#if (defined ENV_LINUX)
#define ACIPCD_TX_ACTION ACIPCD_COPY ;
#define ACIPCD_RX_ACTION ACIPCD_DO_NOTHING ;		// no need to 'handle_cache' because it is 
													//uncached area from Linux perspective
#endif

// define data of teh external-if task (stack, prioirty)
#if defined (OSA_WINCE)   // stack  is not used by OSA in WinCE - set to small value
#define   DIAG_EXT_IF_STACK_SIZE		256
#define   DIAG_EXT_IF_TASK_PRIORITY     6
#elif defined (OSA_LINUX)
#define   DIAG_EXT_IF_STACK_SIZE        1024
#define   DIAG_EXT_IF_TASK_PRIORITY     42   /* Low (non-RT) to collisions with prevent real-time tasks */
#else
#define   DIAG_EXT_IF_STACK_SIZE        4096
#define   DIAG_EXT_IF_TASK_PRIORITY     42
#endif

// hport definition - on FFOS the device port (socket, usb etc)
#if defined (OSA_LINUX)
extern int hPort;
#endif
#if defined (OSA_WINCE)
extern HANDLE hPort;
#endif

#define DIAG_FS_CONFIG_FILENAME "diag_fs.cfg"
#define DIAG_FILTER_BIN_FILENAME "filter.bin"
#define DIAG_COMMANDS_BIN_FILENAME "commands.bin"

#if defined (OSA_LINUX)
#define DIAG_GZ_NAME "ApDiagDB.gz"
#if !defined (BIONIC)
	#define DIAG_LOG_FILE_PATH  "/log%03d.sdl"
	#define DIAG_AP_DB_GZ_PATH	"/tel/" DIAG_GZ_NAME
#else
	#define DIAG_LOG_FILE_PATH	"/marvell/log%03d.sdl"
	#define DIAG_AP_DB_GZ_PATH	"/marvell/tel/" DIAG_GZ_NAME
#endif
#define DIAG_CMI_CLIENT_ADDR "/" DIAG_TMP_ROOT "/client%d"
#define DIAG_DUMMY_ADDR "/" DIAG_TMP_ROOT "/diagIPdummySocket"

#define DIAG_LNX_SD_MOUNT_POINT "/mnt/SD1"
#if !defined BIONIC
	#define DIAG_BSP_CFG_PATH "/etc"
	#define DIAG_FS_MOUNT_POINT "/tel"
	#define DIAG_STORAG_CARD_MOUNT_POINT "/mnt/mmc"
#else
	#define DIAG_BSP_CFG_PATH "/marvell/etc"
	#define DIAG_FS_MOUNT_POINT "/data/log" /* Dec 7, 2010 was "/marvell/tel" */
	#define DIAG_STORAG_CARD_MOUNT_POINT "/sdcard"
	
#endif
/* Locations to save offline -file, diag status  */
#define DIAG_SAVE_OFFLINE_PATH "/data"
#define DIAG_SAVE_DIAGSTATS_PATH "/" DIAG_TMP_ROOT
#endif //OSA_LINUX

#if defined (OSA_WINCE)
#define DIAG_LOG_FILE_PATH  "\\log%03d.sdl"

#define DIAG_FS_MOUNT_POINT "\\Windows\\Marvell\\NVM"
#define DIAG_STORAG_CARD_MOUNT_POINT "\\Storage Card"
#define DIAG_FS_MOUNT_POINT_W L"\\Windows\\Marvell\\NVM"
#define DIAG_STORAG_CARD_MOUNT_POINT_W L"\\Storage Card"
#endif //OSA_WINCE


// Internal Interface 
#if defined (OSA_WINCE)		   // stack	is not used by OSA in WinCE - set to small value
#define DIAG_INTIF_TX_TASK_PRIORITY     1	// solution for 'calibration issue' - thread prioiority was set to 1 by Israel Davidenko
#define DIAG_INTIF_RX_TASK_PRIORITY     4 // was 6
#define DIAG_INTIF_TX_TASK_STACK		  256
#define DIAG_INTIF_RX_TASK_STACK		  256
#define	DIAG_INTIF_MIN_BUFFERS_NUM		0	
#define	DIAG_INTIF_TASK_TIMER_PERIOD	100
#else
#if defined (OSA_LINUX)		   
#define DIAG_INTIF_TX_TASK_PRIORITY     10 /* RT priority to make CP/MSL/INTIF tolerant to AP heavy load */
#define DIAG_INTIF_RX_TASK_PRIORITY     10 /* RT priority to make CP/MSL/INTIF tolerant to AP heavy load */
#else
#define DIAG_INTIF_TX_TASK_PRIORITY     42
#define DIAG_INTIF_RX_TASK_PRIORITY     DIAG_DEFUALT_PRIORITY
#endif
#define DIAG_INTIF_TX_TASK_STACK		  1024
#define DIAG_INTIF_RX_TASK_STACK		  768 /* DiagTx ack may be sent on the RX context and goes
                                               * very deep into proc-calls with 572 bytes*/
#define	DIAG_INTIF_MIN_BUFFERS_NUM		5	
#define	DIAG_INTIF_TASK_TIMER_PERIOD	2                                               
#endif

// CMI task
#if defined (OSA_WINCE)	  // stack	is not used by OSA in WinCE - set to small value
#define   DIAG_CMI_IF_STACK_SIZE		256 
#define   DIAG_CMI_IF_TASK_PRIORITY     6  //TBDIY
#else
#define   DIAG_CMI_IF_STACK_SIZE		1024
#define   DIAG_CMI_IF_TASK_PRIORITY     42 //TBDIY
#endif



// define for APPS/COMM sanity - getting Acks from APPS on traces transmitted in COMM 
// (many times indicates issues in APPS, or the ap/cp driver (SHM, MSL, AC-IPC)
#if !defined(DIAG_APPS)
#define DEBUG_MSL_ACK_ON_COMM_SIDE
#endif

// Definitions for SD/ FS logging (winCE and Linux) - will be available under DIAG_APPS, for
// RTOS, we dont care... no memory constrains 
#if defined (DIAG_APPS)
	////////////////////////
	//Diag over FS support//
	////////////////////////
	extern CHAR usb_comm_ver_id[];
	extern CHAR usb_apps_ver_id[];
	//CHAR udp_comm_ver_id[]={0x7E, 0x7E, 0x06, 0x14, 0x02, 0x01, 0x00, 0x00, 0x01, 0x00, 0x0C, 0x00, 0x00, 0x00,
	//	0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	//	0x81, 0x81};
	extern CHAR usb_comm_acat_ready[];
	extern CHAR usb_apps_acat_ready[];

#endif //(defined (OSA_LINUX) || defined (OSA_WINCE))

#endif  /* _DIAG_COMM_OSIF_H_ */
