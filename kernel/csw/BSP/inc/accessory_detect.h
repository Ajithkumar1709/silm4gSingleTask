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

/*********************************************************************
*                      M O D U L E     B O D Y                       *
**********************************************************************
* Title: accessory detection                                         *
*                                                                    *
* Filename: accessory_detect.h                                       *
*                                                                    *
* Target, platform: Common Platform, SW platform                     *
*                                                                    *
* Author: Amos Barak                                                 *
*                                                                    *
* Description: header file for accessory detection                   *
*                                                                    *
*                                                                    *
*********************************************************************/
#ifndef _ACCESSORY_DETECT_H_
#define _ACCESSORY_DETECT_H_

#include "global_types.h"

//ICAT EXPORTED ENUM
typedef enum
{
    ACD_HEADSET = 0,
	ACD_CHARGER,
	ACD_MAX_ACCESSORIES
} ACD_type;


typedef enum
{
    ACD_DET_NOT_PRESENT = 0,
	ACD_DET_PRESENT
} ACD_Det_Status;

/************************************************************************
* This is the callback function type (one callback for all accessories)
* ACD_type type  - the accessory that changed
* ACD_Det_Status present - in or out
* BOOL underInt - FALSE if under task context; TRUE if under HISR or low level interrupt
************************************************************************/
typedef void (*ACDAccessDetectCnf_t)(ACD_type type, ACD_Det_Status present, BOOL underInt);



/************************************************************************
* Function: ACDBind
*************************************************************************
* Description: accessory detection bind function
*
* Parameters: accessDetectCnf - callback function (for all accessories)
*
* Return value: void
*
* Notes:
************************************************************************/
void ACDBind (ACDAccessDetectCnf_t accessDetectCnf);


/************************************************************************
* Function: ACDUnBind
*************************************************************************
* Description: unbinds all accessories
*
* Parameters:
*
* Return value: void
*
* Notes:
************************************************************************/
void ACDUnBind(void);


/************************************************************************
* Function: ACDAccessoryDetectStatus
*************************************************************************
* Description: Called to determine the status of an accessory
*
* Parameters:
*
* Return value: void
*
* Notes:
************************************************************************/
ACD_Det_Status ACDAccessoryDetectStatus ( ACD_type accessoryID );


void ACDAccessoryDetectInitialise ( void );  /* will be called by bsp init */



#endif /* _ACCESSORY_DETECT_H_ */

