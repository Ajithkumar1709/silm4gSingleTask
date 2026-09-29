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

/*******************************************************************************
*               MODULE HEADER FILE
********************************************************************************
* Title: diag
*
* Filename: DiagSig_PS.h
*
* Target, platform: Common Platform, SW platform
*
* Authors:  Barak Witkowski
*
* Description: definitions for diag PS (TTPCOM) signals handling. In order to avoid duplicated definitions,
*				this file inherits definitions from h files of the PS.
*
* Last Updated:
*
* Notes:
*******************************************************************************/

#if !defined (DIAG_SIG_PS_H)
#define DIAG_SIG_PS_H

/************************************************************************\
 * includes for this file: sig.h kitvcom.h pssignal.h kisystyp.h kioslow.h ki_sig.h
\************************************************************************/

/************************************************************************\
 * includes from DiagSig_PS source file:
\************************************************************************/
#include "kitvcom.h"
#include "pssignal.h"
#include "kisystyp.h"
#include "kioslow.h"
#include "ki_sig.h"
#include "gkitimer.h"
#include "kiostti.h"
// #include "sig.h"

#ifdef _HERMON_
#include "kinucfg.h"
#else
// lanhao #include "l1cfg.h"
#endif /* _HERMON_ */

#include "global_types.h"
#include "ICAT_config.h"
#include "diag_config.h"
#include "diag_pdu.h"



/***********************************************************/
/* Signal filter matrix definition - coupled with ki_sig.h */
/***********************************************************/
DIAG_EXPORT void TraceSignal( void * signalRecord );
DIAG_EXPORT void TraceLoggedSignal( void * loggedSignalRecord );
DIAG_EXPORT void diagmCreateandSendSignal(void *data);
DIAG_EXPORT void diagSendGkiCommandOrSignal(UINT8 DiagSAP , void* ptr , UINT16 dataLength);

#endif

