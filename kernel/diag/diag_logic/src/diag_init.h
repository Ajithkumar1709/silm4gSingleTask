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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                                 *
*     File name:      diag_init.h                                                 *
*     Programmer:     Shiri Dolev                                                 *
*                                                                                 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                                 *
*       Create Date:  November, 2003                                              *
*                                                                                 *
*       Description: DIAG Package Inits.                                          *
*                                                                                 *
*       Notes:                                                                    *
*                                                                                 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#if !defined (_DIAG_INIT_H_)
#define _DIAG_INIT_H_

#include "diag_types.h"
#include "global_types.h"
#include "diag_comm.h"
#include "diag_API.h"

#if defined (DIAG_OVER_MSL) && defined (DIAG_OVER_SHMEM)
#error Internal interface can be either MSL or Shared-Memory (not both)
#endif
#undef DIAG_INT_IF		// diag uses internal interface
#if defined (DIAG_OVER_MSL) || defined (DIAG_OVER_SHMEM)
#define DIAG_INT_IF
#endif

#ifdef PHS_SW_TTC_CPONLY
	#ifdef DIAG_INT_IF
		#undef DIAG_INT_IF
	#endif
#else
	#if defined(PHS_SW_TTC_AP) || defined(PHS_SW_DEMO_TTC)
		#define DIAG_INT_IF
	#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define CMI_MASTER_UDP_PORT 13579
#define ACAT_UDP_PORT       12345

/*-- Public Functions Prototypes ---------------------------------------*/

/************************
 *		Typedefs		*
 ************************/
typedef void (*DiagICATReadyNotifyEventFunc)(void);
typedef void (*DiagEnterBootLoaderCBFunc)(void);

extern DiagBlockReasons				diagBlocked;

/************************
 *		Prototypes		*
 ************************/
DIAG_EXPORT void diagICATReayNotifyEventDefaultFunc(void);
DIAG_EXPORT void diagICATReadyNotifyEventBind(DiagICATReadyNotifyEventFunc diagICATReadyFunc);
DIAG_EXPORT void diagEnterBootLoaderCBFuncBind(DiagEnterBootLoaderCBFunc diagBootLoaderFunc);
DIAG_EXPORT void diagInit(void);
DIAG_EXPORT void diagRxInit(void);
DIAG_EXPORT void diagTxInit(void);
DIAG_EXPORT void diagTestInit(void);
DIAG_EXPORT SwVersion diagGetVersion(void);


//Global Variable used for configure the Linux SD
typedef enum
{
	FSTYPE_NO_MOUNT=0,
	FSTYPE_VFAT=1,
	FSTYPE_EXT2=2,//Not supported yet Diag05.00.24
	FSTYPE_EXT3=3,//Not supported yet Diag05.00.24
	FSTYPE_MSDOS=4,
	
}SDFStypeE;

typedef struct {
UINT32 log_auto_start; //MBTODO - For now this exist as global variable in Windows should change it
UINT32 FS_Inc_Reset;
SDFStypeE SD_FSType;

} DiagBSPFSConfigS;

typedef struct {
	UINT32 write_unit_size;//The minimum chunk size to be gathered before writing (unless writing is enforced by flush or timeout)
	                       //Cached write mechanism is disabled when write_unit_size==0
	UINT32 time_out;       //Used in OSATimerStart
} DiagCachedWriteS;

// global variables to be usded by diag_logic, diag_comm
typedef struct {
	OSMsgQRef diagMsgQRef;

	EActiveConnectionType m_eConnectionType;		// Extrernal connection type
	EActiveConnectionLL_Type m_eLLtype;				// EXT type L2 of connection
	EActiveConnectionType m_eIntConnectionType;		// Internal connection type
	EActiveConnectionLL_Type m_eIntLLtype;				// INT type L2 of connection
	UINT32	m_extIfTxMulti;		// does the extIf supports muti Tx (in one call to driver, send multi bufs)
									// default is 0 (not supported), currently (Nov 07) only Nu-USB/SSP has mutil mode

	UINT32 m_bWorkMultiCore;	// Default, we work multi - core (MSL/Shared Memory, internal-connection is active) =1 or single core only (no router mode) =0
	UINT32 m_bMasterClientMode;	//  Masgter-client
	UINT32 m_bIsMaster;			// is master
	UINT32 m_bIsClient;			// is client
	DiagICATReadyNotifyEventFunc	diagICATReadyNotifyEventFunc;
	DiagPSisRunningFn 				_diagSigPsCheckFn;		// PS status CB.
	DiagEnterBootLoaderCBFunc		diagEnterBootLoaderCBFunc;

	DiagBSPFSConfigS diagBSPFScfg;
	DiagCachedWriteS diagCachedWrite;
} diagInternalDataS;  

extern diagInternalDataS diagIntData;

#ifdef __cplusplus
}
#endif

#endif  /* _DIAG_INIT_H_ */

