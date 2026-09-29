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
 *     File name:      diaglogger.h                                                *
 *     Programmer:     Ohad Peled                                                  *
 *                                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *																				   *
 *       Create Date:  December, 2005											   *
 *																				   *
 *       Description: DIAG Logging mechanism									   *
 *																				   *
 *       Notes: header file for cyclic buffer  Diag logging feature				   *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */

#if !defined (DIAG_LOGGER_DEFS_H)
#define     DIAG_LOGGER_DEFS_H

#if defined(ENABLE_DIAG_LOGGER)
#include "diag.h"
#include "diag_API.h"

#include "FDI_EXT.h"
#include "FDI_FILE.h"
#include "FDI_ERR.h"



/************************************************************************/
/* This structure defines the entry of a trace in the diag log buffer	*/
/* Note that the 4th field in this structure is different between XSC	*/
/* and DSP messages														*/
/************************************************************************/
typedef struct
{
	UINT16 nModuleID;
	UINT16 nMessageID;
	UINT32 tTimeStamp;
	UINT16 nOPCodeOrFN;	//with protocol type 0, DSP message contains the OP code, and XSC message contains the frame number
	UINT16 nDataLen; //with protocol type 0, will be used only on DSP traces
}TraceLogEntryHeader;

typedef struct
{
	ProtocolType eProtocolType;
	UINT16 nMaxDataLen;
	UINT32 nDiagDBID;
}DiagLogFileHeader;

typedef enum
{
	nvhsOK,
	nvhsFileTooShort,
	nvhsStructNameMismatch,
	nvhsStructFormat
} NVM_Header_Status_te;





#define MAX_LOG_SIZE	(0xF00)/* save space for the pointers */

#define DATA_FIXED_SIZE 8

#define DIAG_LOG_NAME	"postreset.dgl"

#define DIAG_LOG_CFG_FILE_NAME "diagloggercfg.nvm"

#define INVALID_OP_CODE	-1

#define MIN_TRACE_ENTRY sizeof(TraceLogEntryHeader) // this is the minimum header required for a DSP message




#endif// defined(ENABLE_DIAG_LOGGER)
#endif //DIAG_LOGGER_DEFS_H
