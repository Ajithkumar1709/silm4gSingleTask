/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/******************************************************************************
**
** INTEL CONFIDENTIAL
** Copyright 2003-2004 Intel Corporation All Rights Reserved.
**
** The source code contained or described herein and all documents
** related to the source code (Material) are owned by Intel Corporation
** or its suppliers or licensors.  Title to the Material remains with
** Intel Corporation or its suppliers and licensors. The Material contains
** trade secrets and proprietary and confidential information of Intel
** or its suppliers and licensors. The Material is protected by worldwide
** copyright and trade secret laws and treaty provisions. No part of the
** Material may be used, copied, reproduced, modified, published, uploaded,
** posted, transmitted, distributed, or disclosed in any way without Intel's
** prior express written permission.
**
** No license under any patent, copyright, trade secret or other intellectual
** property right is granted to or conferred upon you by disclosure or
** delivery of the Materials, either expressly, by implication, inducement,
** estoppel or otherwise. Any license under such intellectual property rights
** must be express and approved by Intel in writing.
**
**  FILENAME: xllp_dfc.h
**
**  PURPOSE:  XLLP interface to the data flash controller (DFC).
**
******************************************************************************/

#ifndef __XLLP_DFC_H__
#define __XLLP_DFC_H__


#include "xllp_dfc_defs.h"
#include "xllp_dfc_config.h"

/* Relocation table is always located at the last page in the first block of the NAND FLASH
* Assuming FLASH maximum page size is 2048 bytes and sizeof(Rel_T)=4 bytes, then array length is 255
* -> 255 * 4 + 4 = 2048
*/
#define NAND_RELOC_MAX   511


///////////////////////////////////////////////////////////////////////////////
/////
///     D F C   I N T E R F A C E   R O U T I N E S
///
//////
int  XllpDfcSelfInit(CHIP_TYPE chip, FLASH_TYPE flash);

int  XllpDfcRead       (P_DFC_BUFFER buffer, unsigned int address, unsigned int bytes);
int  XllpDfcWrite      (P_DFC_BUFFER buffer, unsigned int address, unsigned int bytes);
int  XllpDfcErase      (unsigned int address);

int  XllpDfcGetPageSize  (void);
int  XllpDfcGetBlockSize (void);

int  XllpDfcReadID(unsigned char * pMakerID, unsigned char * pDeviceID);

typedef struct {
	unsigned short  From;
	unsigned short  To;
} Rel_T;


typedef struct {
	unsigned short  Header;
	unsigned short  NumReloc;
	Rel_T   Relo[NAND_RELOC_MAX];	
} Reloc_T;

#endif



