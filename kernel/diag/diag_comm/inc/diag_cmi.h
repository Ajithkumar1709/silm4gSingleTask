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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                 *
 *     File name:      diag_cmi.h                                                  *
 *     Programmer:     Itzik Yankilevich                                           *
 *                                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                 *
 *       Create Date:  May, 2008                                                   *
 *                                                                                 *
 *       Description: DIAG Configuration File.   								   *
 *                                                                                 *
 *       Notes:                                                                    *
 *                                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined (_DIAG_CMI_H_)
#define _DIAG_CMI_H_

#if defined (OSA_LINUX)
#include <sys/un.h>//AF_UNIX
#endif
#if defined (OSA_WINCE)
#include <Winsock2.h>//AF_INET
#endif

/* RX DiagSAP's */
#define MASTER_TO_CLIENT_CMM		8
#define CLIENT_TO_MASTER_CMM		9
/* DIAG CMM Service IDs */
#define REGISTER_CMM_SER_ID			48
#define CONFIRM_REGISTER_CMM_SER_ID	2
#define REJECT_REGISTER_CMM_SER_ID	3
#define ICAT_READY_CMM_SER_ID		4
#define FILTER_ARRAY_CMM_SER_ID		5
#define FILTER_SPECIFIC_CMM_SER_ID	6
#define FILTER_ALL_CMM_SER_ID		7
#define DISCONNECT_CMM_SER_ID		8
#define	SET_MSG_LIMIT_CMM_SER_ID	10

#define CMM_VER                     1

typedef enum {
	CMI_FREE=0,
	CMI_IN_PROGRESS=1,
	CMI_REGISTERED=2,
	CMI_DISCONNECTED=3,
	CMI_NOT_RESPONDING=4,
	CMI_NO_STATUS=0x1fffffff //make sure it's UINT32 in the distributedClient structure
} e_clientStatus;
/* Master Internal Database Distributed Client Structure */
typedef struct {
	/*** DO NOT MOVE THE FIRST 7 UINT32 ENTRIES - USED IN MEMCPY AS ONE CHUNK ***/
	UINT32 CMMver; //for backward and forward CMM compatibility
	UINT32 firstCommandID;
	UINT32 lastCommandID;
	UINT32 firstReportID;
	UINT32 lastReportID;
	UINT32 procID; //this is OS specific
	UINT32 procPriority; //this is OS specific
	/*** DO NOT MOVE THE FIRST 7 UINT32 ENTRIES - USED IN MEMCPY AS ONE CHUNK ***/
	e_clientStatus clientStat; //ensured to be UINT32
	//TBDIY we don't need this! We use the array index instead. UINT32 clientID; //client index for the DIAG_COMMDEV_CMI entries in the COMDEV_NAME enum
	UINT32 lostMsgCollectFlg; //for client response since last request
	UINT32 filterCollectFlg; //for client response since last request
	UINT32 firstMsgTime; //at the master - ms or ticks only for debug
	UINT32 lastMsgTime; //at the master - ms or ticks only for debug
#if defined (OSA_LINUX)
	struct sockaddr_un clientCMIfID;//for AF_UNIX in the CMI interface (LAST entry in this struct because the size may be NOT 4 bytes aligned)
#endif
#if defined (OSA_WINCE)
	SOCKADDR_IN clientCMIfID;//for AF_INET in the CMI interface (LAST entry in this struct because the size may be NOT 4 bytes aligned)
#endif
} distributedClient;

#endif /*_DIAG_CMI_H_*/
