/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *  Filename: diag_mmi_if_PROTOCOL.h
 *
 *  Description:
 *
 *  History:
 *
 *  Notes:
 *
 ******************************************************************************/


#if !defined(DIAG_MMI_IF_PROTOCOL_H)
#define DIAG_MMI_IF_PROTOCOL_H

#define DIAG_MMI_CTRL_START_MSG 		   "start"
#define DIAG_MMI_CTRL_STOP_MSG  		   "stop"
#define DIAG_MMI_CTRL_DEBUG_PRINTS_EN_MSG  "debug_prints_en"
#define DIAG_MMI_CTRL_EEH_ASSERT	 	   "eeh_assert"

//#define ENABLE_DIAG_MMI_TEST

#if defined (ENABLE_DIAG_MMI_TEST)
#define DIAG_MMI_CTRL_TEST_MSG  		   "test"
#endif//ENABLE_DIAG_MMI_TEST

#define DIAG_MMI_SOCKET_NAME_ONLY "DIAG_MMI_IPC_SOCKET"
#define LM_EEH_SOCKET_NAME_ONLY "LM_EEH_SOCKET"
#define EEH_LM_SOCKET_NAME_ONLY "EEH_LM_SOCKET"


#define DIAG_MMI_PIPE_FILENAME "/tmp/DIAG_MMI_IPC_SOCKET"

//EEH - MMI sockets
#define LM_EEH_SOCKET_FILENAME "/tmp/LM_EEH_SOCKET"
#define EEH_LM_SOCKET_FILENAME "/tmp/EEH_LM_SOCKET"

//EEH - File indicating the current log location to make EEH operation independent of the MMI socket response
#define LM_EEH_LOG_LOCATION    "/tmp/diag_log_path"

#endif// DIAG_MMI_IF_PROTOCOL_H
