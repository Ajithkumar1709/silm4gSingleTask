/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/**************************************************************************
 * TTPCom Software Copyright (c) 1997-2005 TTPCom Ltd
 * Licensed to Intel Corporation
 **************************************************************************
 *   $Id: //central/releases/development/branch_rel14_hermon/tplgsm/platforms/hermon/hainc/usbmgrttpal.h#2 $
 *   $Revision: #2 $
 *   $DateTime: 2005/10/27 10:45:43 $
 **************************************************************************
 * File Description: This is the main header file of
 *                   the USB Manager Package
 **************************************************************************/

#ifndef _USBMGRTTPAL_H_
#define _USBMGRTTPAL_H_

#include <kernel.h>   /* for TaskId type */
#include "global_types.h"


//extern USBMGR_IF_HANDLER  *usbMgrIfHnd;


/****** Callback function ****/


/****** Services ****/
void  UsbMgrTTPALRegister( UINT8 appliacationID);

UINT8 UsbMgrTTPALGetIntNumber( UINT8 interfaceId );

extern void UsbMgrTTPALSetMuxUART(void);
extern void UsbMgrTTPALSetMuxUSB(void);
extern void UsbMgrTTPALSetMuxUART_INT(void);
extern void UsbMgrTTPALSetMuxUSB_INT(void);
extern void UsbMgrTTPALInit(void);

#endif

