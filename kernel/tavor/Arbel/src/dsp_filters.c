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
#include "IPCCommFilters.h"
#if defined(IPC_NVM_FILTERS)
#include "IPCHandleFilterFiles.h"
#endif

/*******************************************************************************
* Function: setupDspFilters
********************************************************************************
* Description: Sets up the DSP filters (DSP CMD and DSP MSG filters):
*             1. Sets up the default filters; these are imported from
*                two h-files produced automatically from the corrsponding .txt
*                files. Automatic conversion is done at every build in order
*                to make sure filter files are applied even if older than the
*                build derived objects.
*             2. Looks up for NVM files for DSP CMD and DSP MSG filters
*                and applies these "on top" of the defaults.
*                Note: entries for every opcode in the NVM override the default
*                while entries for all other opcodes default is retained.
* Parameters:
*                None
* Return value:
*                None
* Notes:
*                An empty implementation is supplied for application-side builds
*******************************************************************************/

void setupDspFilters(void)
{
	static const IPC_Filter_ts dspMessageFilters[]=
	{
		/* Import the filter produced from the txt-file */
#include "DSP_Filter_file.h"
	};

	static const IPC_Filter_ts dspCommandFilters[]=
	{
		/* Import the filter produced from the txt-file */
#include "DSP_Cmd_Filter_file.h"
	};

	filterPlpMessage((IPC_Filter_ts*)dspMessageFilters,sizeof(dspMessageFilters));
	filterPlpCommand((IPC_Filter_ts*)dspCommandFilters,sizeof(dspCommandFilters));

#if defined(IPC_NVM_FILTERS)
    //reading MSG and CMD filter NVM files and updating IPC accordingly.
    ipcReadAndSendIpcFilter();
#endif
} /* setupDspFilters() */
