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
* Title: PM
*
* Filename: pm.h
*
* Target, platform: Common Platform, SW platform
*
* Authors: Isar Ariel
*
* Description:
*
* Last Updated:
*
* Notes:
*******************************************************************************/

#ifndef _PM_H_
    #define _PM_H_

#include "global_types.h"

/*----------- Global defines -------------------------------------------------*/

/*----------- Global macro definitions ---------------------------------------*/

/*----------- Global type definitions ----------------------------------------*/
// groups ID defenition
typedef enum
{
    HW_PLATFORM_ID,
    SW_PLATFORM_ID,
    COMMON_APPLICATION_ID,
    WIRELESS_MODEM_SUBSYSTEM_ID,
    //HS_MANAGER_ID,
    MAX_GROUP_ID
} GROUP_ID;

typedef enum
{
  SYSTEM_ACTION_PHASE1_INIT,
  SYSTEM_ACTION_PHASE2_INIT,
  SYSTEM_ACTION_POWER_DOWN,
  SYSTEM_ACTION_RESET,
  SYSTEM_ACTION_TECHNICIAN_MODE,
  SYSTEM_ACTION_SLEEP_MODE,
  MAX_SYSTEM_ACTION
} SYSTEM_ACTION;

typedef enum
{
  SYSTEM_EVENT_INIT,
  SYSTEM_EVENT_POWER_UP,
  SYSTEM_EVENT_POWER_DOWN,
  SYSTEM_EVENT_RESET,
  SYSTEM_EVENT_TECHNICIAN_MODE,
  SYSTEM_EVENT_SLEEP_MODE,
  MAX_SYSTEM_EVENT
} SYSTEM_EVENT;

typedef enum
{
  SYSTEM_STATE_NORMAL,
  SYSTEM_STATE_TECHNICIAN_MODE,
  MAX_SYSTEM_STATE
}SYSTEM_STATE;

// Definition of Array of pointers to Group Actions Routines.
typedef struct
{
  void (*FuncPtr[MAX_SYSTEM_ACTION])(int state);
} GROUP_ACTIONS;

#endif  /* _PM_H_ */
