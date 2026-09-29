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
*     File name:      diag_restore_fixups.h                                       *
*     Programmer:     Shiri Dolev                                                 *
*                                                                                 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                                 *
*       Create Date:  November, 2003                                              *
*                                                                                 *
*       Description: Restore Fixups IF                                            *
*                                                                                 *
*       Notes:                                                                    *
*                                                                                 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined (RESTOREFIXUPS_H)
#define RESTOREFIXUPS_H

#include "diag_osif.h"

// Relocation header
typedef struct {
    UINT8 nEntries;     //number of valid entries (not including padding entries)
    UINT8 nSize;        //total number of entries, including padding entries
    UINT16 entries[1];  // offsets from PDB user data start to the pointer fields
}RelocationHeader;

// 32-bit fixup found in place of a pointer field inside the PDB user data
typedef struct{
	UINT16 offset;
	UINT16 filler;
}Fixup;

//
// Receives the Relocateable PDB pointer (such PDB includes a Relocation Header and user data area)
// Restores the pointer fields in the data area using the information from Relocation Header
// Parameters:
// 	  (pdb) - Relocateable PDB pointer
//    (len) - PDB size in bytes
// Returns: a pointer to the user data start or NULL if the PDB data is inconsistent
//          (invalid RelocationHeader or pointers out of range specified by (len))
DIAG_EXPORT void* diagRestoreFixups(UINT8 *pdb, int len);

#endif // RESTOREFIXUPS_H
