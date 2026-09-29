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

#if !defined (_DIAG_COMM_H_)
#define _DIAG_COMM_H_

#include "global_types.h"
#include "ICAT_config.h"
#include "diag_osif.h"

#if defined (HISR_PRIORITY_2)
#define DIAG_HISR_PRIORITY HISR_PRIORITY_2
#else // defined (HISR_PRIORITY_2)
#define DIAG_HISR_PRIORITY 1
#endif// defined (HISR_PRIORITY_2)

#define DIAG_CORE_SELECTOR_RX_MASK		0x80
#define DIAG_CORE_SELECTOR_RX_SHIFT		7
#define DIAG_CORE_SELECTOR_TX_MASK		0x8000
#define DIAG_CORE_SELECTOR_TX_SHIFT		15
#define DIAG_CORE_APP_MASK				0x80

#define DIAG_COMM_EXTIF_ETH_MAX_BUFF_SIZE 4096
/*This define allows the file diag_bsp.cfg and FS logs to be moved under diag_marvell_rw_dir
This is  not always a good decission, specially when supporting old systems, if not defined the file will stay under /tel or /etc */
//#define DIAG_ALLOW_CFGFILE_REPLACEMENT 1

#if !defined (DIAGNEWHEADER)
#if defined (DIAG_APPS)
	#define DIAG_CORE_ID  1
#else
	#define DIAG_CORE_ID  0
#endif /* DIAG_APPS */
#else /* DIAG_NEW_HEADER is defined */
#if defined (DIAG_APPS)
	#define DIAG_CORE_ID  DIAG_APPS_USER
#else
	#define DIAG_CORE_ID  DIAG_COM_USER
#endif /* DIAG_APPS */
#endif /* DIAG_NEW_HEADER */

/*
 enum for defintions of ext-if type. In WM, the ext-if can be USB/UDP/TCP
 when moving to new-header, we can enhance it to include all types of ext-if (also UART, SSP..)
*/
//ICAT EXPORTED ENUM
typedef enum
{
	// for external interfaces
	tNoConnection,
	tUSBConnection,
	tTCPConnection,
	tUDPConnection,
	tUARTConnection,
	tSSPConnection,
	tVIRTIOConnection,
	// for internal interfaces
	tMSLConnection,
	tSHMConnection		// shared memory
} EActiveConnectionType;

//supported communication devices - low level link type ...
// zero is NOT valid device !
//ICAT EXPORTED ENUM
typedef enum
{
	tLL_none,		// not set
	tLL_SSP,		// external int. SSP
	tLL_UART,		// external int. UART
	tLL_USB,		// external int. USB
	tLL_ETHERNET,	// external int. over Ethernet port
	tLL_LocalIP,	// external int./CMI int. localIP
	tLL_ACIPC,		// internal int. SHMEM
	tLL_SAL,		// internal int. MSL o SAL
	tLL_GPC,		// internal int. MSL o GPC
	tLL_FS,			// external int. File System
	tLL_SC			// external int. Storage Card (SD card)
} EActiveConnectionLL_Type;

// MAX tx interfaces
#define DIAG_COMMDEV_TX_MAX 3	// external, internal and CMI interface

// MAX number of clients for split (distributed) diag mode
#define DIAG_COMDEV_MAX_CLIENTS	5	// change (increase) in this value must be accompanied by the COMDEV_NAME update

// we have maximum of 3 types of interfaces: for ext-interface, internal-interface and CMI-interface
// but in CMI mode, we can recieve data from all clients (should be aligned with DIAG_COMDEV_MAX_CLIENTS)
//ICAT EXPORTED ENUM
typedef enum {
	DIAG_COMMDEV_EXT,//EXT is also for clients that communicate with the master CMI
	DIAG_COMMDEV_INT,
	DIAG_COMMDEV_CMI,
	// for client-master  - up to 5 clients
	DIAG_COMMDEV_CMI1 = DIAG_COMMDEV_CMI,
	DIAG_COMMDEV_CMI2,
	DIAG_COMMDEV_CMI3,
	DIAG_COMMDEV_CMI4,
	DIAG_COMMDEV_CMI5,
	DIAG_COMMDEV_RX_MAX=DIAG_COMMDEV_CMI5,

	//This enum is used also in UINT8 DiagReportItem_S.clientID and we want to limit the size to 8 bits.
	DIAG_COMMDEV_NODEVICE = 0xEF,	// large enough value not to be a valid rx interface...
	DIAG_COMMDEV_DUMMY    = 0x1FFFFFFF   // to keep 4 bytes alignment in structs
} COMDEV_NAME;

typedef enum {
	INTIF_CONNECTION_STATUS_DISCONNECTED,
	INTIF_CONNECTION_STATUS_CONNECTED,
	INTIF_CONNECTION_STATUS_LINKDOWN,
	INTIF_CONNECTION_STATUS_LINKUP
}IntIf_ConnectionStatus_te;


// DiagComm function called by DiagBuff to initiate TX after idle period
typedef enum  {
   DIAG_COM_CompletePacketState,
   DIAG_COM_PacketFirstChunkState,
   DIAG_COM_PacketNextChunkState,
   DIAG_COM_PacketLastChunkState
}DIAG_COM_RX_PacketHandlingState;

typedef struct
{
	UINT32 								rxIF;
    CHAR *                              buffer;                     //_diagUSBRxLisrMsgDataPtr;
    UINT16                              data_offset;                //bytes offset in buffer
	                                                                //TBDIY to remove the header and get a clean Diag Rx PDU
    UINT16                              total_bytes_expected;       //total packet length in bytes
    UINT16                              total_bytes_received;       //indicates bytes received at every moment
    UINT16                              current_chunk_bytes;        //length of last received chcunk of a packet in bytes
	UINT32								nReTriesToPerform;			// number of retry to perform on failure of diagRecieveCommand
													// failure can be due to no-memory or diag-rx-queue full
    BOOL                                end_of_packet;
    DIAG_COM_RX_PacketHandlingState		handling_state;
}DIAG_COM_RX_Packet_Info;

DIAG_EXPORT UINT32 GetConnectedDev(void);
DIAG_EXPORT void diagCommTransmit(COMDEV_NAME dev, void *ptr);//TBDIY specify the device to make this more general then just ExtIf
DIAG_EXPORT void diagCommInit(void);
DIAG_EXPORT void setDiagBlock(BOOL ifLock);
DIAG_EXPORT void diag_SetDiagBlock(void);
DIAG_EXPORT void SetDeviceConection(COMDEV_NAME eDev, BOOL bIsConnected);
DIAG_EXPORT void diagCommEnforceTransmit(void *ptr, int devIndx);

extern BOOL IsDeviceConnctedExternally(void);
extern BOOL IsDeviceConnctedInternally(void);

#if defined (DIAG_CMI_IF)
//The CMI interface is only for the master in distributed mode. The clients use their external interface to communicate with the master.
extern COMDEV_NAME CMIfID2RxIf(const void *clientCMIfID,size_t IDsize);//global CMI Interface ID
extern void* RxIf2CMIfID(const UINT8 clientID);
#endif

#endif  /* _DIAG_COMM_H_ */
