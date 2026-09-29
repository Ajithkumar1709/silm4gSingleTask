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
**  FILENAME: xllp_dfc_config.h
**
**  PURPOSE:  XLLP DFC configuration file.
**            Anything configurable should be placed here.
**
******************************************************************************/

#ifndef __XLLP_DFC_CONFIG_H__
#define __XLLP_DFC_CONFIG_H__


#include "xllp_dfc_defs.h"


//
// Clock in nanoseconds. Not likely to be changing all that often...
//
#define NAND_CONTROLLER_CLOCK  104  // MHz
#define CLOCK_NS 9 //(1000/NAND_CONTROLLER_CLOCK)

#define DFC_TIMEOUT 10000000 // Wait for a while...


/****************************************************************************************/
/**///
/**///    These two constructs need to be kept in tandem -- they are codependent.
/**///       (Order corresponds to order in GPIO_Registers[]. *** KEEP CONSISTENT ***)
/**/
/**/  typedef enum {
/**/     //MONAHANS,
/**/     TAVOR,
/**/     CHIP_TYPE_SIZE
/**/     } CHIP_TYPE;
/**/  
/**/
/****************************************************************************************/


/****************************************************************************************/
/**///
/**///    These two constructs need to be kept in tandem -- they are codependent.
/**///       (Order corresponds to order in Flash_Specs[]. *** KEEP CONSISTENT ***)
/**///
/**/  //
/**/  // Flash types.
/**/  //
/**/  // NOTE: When support for a NAND device is added that requires more or less
/**/  //       than THREE address cycles for an erase command, the xdfc_erase() routine
/**/  //       will need to be generalized.
/**/  //
/**/  typedef enum {
/**/     SAMSUNG_ZYLONITE,
/**/     MICRON_ZYLONITE,
/**/     FLASH_TYPE_SIZE  // Necessarily at the end.
/**/     } FLASH_TYPE;
/**/

/**/

/****************************************************************************************/

#endif



