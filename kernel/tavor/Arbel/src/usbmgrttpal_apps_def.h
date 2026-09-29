/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/**************************************************************************
 * TTPCom Software Copyright (c) 1997-2005 TTPCom Ltd
 * Licensed to Intel Corporation
 **************************************************************************
 *   $Id: //central/releases/development/branch_rel14_hermon/tplgsm/platforms/hermon/hainc/usbmgrttpal_apps_def.h#1 $
 *   $Revision: #1 $
 *   $DateTime: 2005/06/20 13:51:23 $
 **************************************************************************
 * File Description:
 **************************************************************************/

#ifndef _USBMGR_TTPAL_APPS_DEF_H_
#define _USBMGR_TTPAL_APPS_DEF_H_

#include "UsbMgr.h"
#include "usbmgrttpal.h"




/*typedef enum
{
	USB_MGR_TTPAL_DIR_IN,
	USB_MGR_TTPAL_DIR_OUT
} TTPAL_EP_Dir;
*/



/************************************ typedef structures definitions **********************************/

typedef struct{
    UINT8 freePtr;
    UINT8 relPtr;
    UINT8 queueTh;
}TTPALQPtrs;

typedef struct{
	UsbTransmitDataRequest  *ttpEpQueueAddr;
    TTPALQPtrs              ptr;
    UINT32                  queueSize;
}ttpEPQStruct;


typedef struct
{
    UINT8                           numEndpoint;
    USBMgr_EndpointStruct           *endpointCfg;
    USBMgr_DeviceClassStruct        *deviceClass;
    CHAR                            *interfaceString;
    UINT8                           appID;
    USBMgr_CallbackIndicationStruct *indicationCallback;
}usbMgrTTPAL_RegPrmsStruct;



 /*****************endpoints declarations *****************************/


#define     TTP_APPS_NUMBER              (USBMGR_TTPAL_APPID_LAST+1)
#define     MASS_STORAGE_NUM_ENDPOINTS   2
#define     MODEM_NUM_ENDPOINTS          3
#define     GENIE_NUM_ENDPOINTS          2





//alla - obtained by function cal must not be defined like this
//#define USB_MAST_INTERFACE_NUMBER        0
//#define USB_EMMI_INTERFACE_NUMBER        0
//#define USB_COMM_INTERFACE_NUMBER        0
//#define USB_COMM_DATA_INTERFACE_NUMBER   1
//#if defined(USB_DYNAMIC_CONFIGURATION)
#define MAST_QUEUE_LENGTH                16
/*******************************************************************************
 * Manifest Constants
 ******************************************************************************/

#define USB_SETUP_BMREQUEST_INDEX                0
#define USB_SETUP_BREQUEST_INDEX                 1
#define USB_SETUP_WVALUE_INDEX                   2
#define USB_SETUP_DESCRIPTOR_INDEX_WVALUE_INDEX  2
#define USB_SETUP_DESCRIPTOR_TYPE_WVALUE_INDEX   3
#define USB_SETUP_WINDEX_INDEX                   4
#define USB_SETUP_WLENGTH_INDEX                  6

#define USB_SETUP_REQUEST_DIRECTION_MASK          0x80
#define USB_SETUP_REQUEST_DIRECTION_TO_HOST       0x80
#define USB_SETUP_REQUEST_DIRECTION_TO_DEVICE     0x00

#define USB_SETUP_REQUEST_TYPE_MASK               0x60
#define USB_SETUP_REQUEST_TYPE_STANDARD           0x00
#define USB_SETUP_REQUEST_TYPE_CLASS              0x20
#define USB_SETUP_REQUEST_TYPE_VENDOR             0x40
#define USB_SETUP_REQUEST_TYPE_RESERVED           0x60

#define USB_SETUP_REQUEST_RECIPIENT_MASK          0x1F
#define USB_SETUP_REQUEST_RECIPIENT_DEVICE        0x00
#define USB_SETUP_REQUEST_RECIPIENT_INTERFACE     0x01
#define USB_SETUP_REQUEST_RECIPIENT_ENDPOINT      0x02
#define USB_SETUP_REQUEST_RECIPIENT_OTHER         0x03


/*****************************************************************************
*MAST Definition
******************************************************************************/
#define MAST_CBW_LENGTH 31                      //length of MAST Control Block


#define MAST_dCBWDataTransferLength_BYTE_OFFSET 8            //byte number where transfer length resides
#define MAST_bmCBWFlags_BYTE_OFFSET             12           //byte number where flags offset resides

#define MAST_bmCBWFlags_DATA_DIR_BIT_OFFSET 7
//Direction - the device shall ignore this bit if the dCBWDataTransferLength field is
//zero, otherwise:
//0 = Data-Out from host to the device,
//1 = Data-In from the device to the host.
#define MAST_bmCBWFlags_DATA_DIR_H2D     0
#define MAST_bmCBWFlags_DATA_DIR_D2H     1

/*******************************************************************************
 * Macros
 ******************************************************************************/



//#define FULL_QUEUE(ptrs ,queueSize)  ( (((ptrs).freePtr == queueSize-2)&&((ptrs).relPtr == 0) )||((ptrs).freePtr+2 == (ptrs).relPtr) )

//#define FULL_QUEUE(ptrs ,queueSize)  ( (((ptrs).freePtr == queueSize-2)&&((ptrs).relPtr == 0) )|| (((ptrs).freePtr == queueSize-1)&&((ptrs).relPtr == 1) ) || ((ptrs).freePtr+2 == (ptrs).relPtr) )

#define FULL_QUEUE(ptrs ,queueSize)  ( (((ptrs).freePtr == queueSize-(ptrs).queueTh)&&((ptrs).relPtr == 0) )|| (((ptrs).freePtr == queueSize-(ptrs).queueTh +1)&&((ptrs).relPtr == 1) ) || ((ptrs).freePtr+(ptrs).queueTh == (ptrs).relPtr) )


//#define FREE_QUEUE(ptrs ,queueSize)  ( (( (ptrs).freePtr + 1 == queueSize )&&((ptrs).relPtr == 0) )|| ( (ptrs).freePtr + 1 ==(ptrs).relPtr ) )


#define FREE_QUEUE(ptrs ,queueSize)  ( (( (ptrs).freePtr + (ptrs).queueTh == queueSize )&&((ptrs).relPtr == 0) )|| ( (ptrs).freePtr + (ptrs).queueTh ==(ptrs).relPtr ) )

#define MAKE_Q_EMPTY(ptrs)           ((ptrs).freePtr = (ptrs).relPtr )

#define EMPTY_QUEUE(ptrs)            ((ptrs).freePtr == (ptrs).relPtr )

#define NEXT_PTR_ON_Q(QAdd , nextPtr )    (QAdd) + ((nextPtr)*sizeof(UsbTransmitDataRequest) )

#define INC_Q_PTR(ptr ,queueSize)        {   if( (ptr) == (queueSize)-1 )  \
                                                    (ptr) = 0;                  \
                                                  else                           \
                                                    (ptr) = ((ptr)+1);         \
                                         }



#define CONVERT_SETUP_TO_TTPCOM_PRM(iPrm , tPrm)    {    \
													   tPrm[0] = (iPrm->setup_packet[0]);  \
													   tPrm[1] = (iPrm->setup_packet[1]); \
													   tPrm[2] = (iPrm->setup_packet[2]); \
													   tPrm[3] = (iPrm->setup_packet[3]); \
													   tPrm[4] = (iPrm->setup_packet[4]); \
													   tPrm[5] = (iPrm->setup_packet[5]); \
													   tPrm[6] = (iPrm->setup_packet[6]); \
													   tPrm[7] = (iPrm->setup_packet[7]); \
													 }





#define CONVERT_SETUP_TO_USB_FIELDS(sPacket , sField) { (sField).bmRequestType = *((sPacket) + USB_SETUP_BMREQUEST_INDEX);  \
														(sField).bmRequestTypeFields.type = ((sField).bmRequestType & USB_SETUP_REQUEST_TYPE_MASK);\
														(sField).bmRequestTypeFields.dataTransferDirection = ((sField).bmRequestType & USB_SETUP_REQUEST_DIRECTION_MASK);\
														(sField).bmRequestTypeFields.recipient = ((sField).bmRequestType & USB_SETUP_REQUEST_RECIPIENT_MASK);\
														(sField).bRequest = *((sPacket) + USB_SETUP_BREQUEST_INDEX);  \
														(sField).wValue = (Int16) ((Int16)(*((sPacket) + USB_SETUP_WVALUE_INDEX)) + \
																		   (Int16)( (*((sPacket) + USB_SETUP_WVALUE_INDEX+1))<<8) ); \
														(sField).wIndex = (Int16) ((Int16)(*((sPacket) + USB_SETUP_WINDEX_INDEX)) + \
																		   (Int16)( (*((sPacket) + USB_SETUP_WINDEX_INDEX+1))<<8) ); \
														(sField).wLength = (Int16) ((Int16)(*((sPacket) + USB_SETUP_WLENGTH_INDEX)) + \
																		   (Int16)( (*((sPacket) + USB_SETUP_WLENGTH_INDEX+1))<<8) ); \
													  }






#endif
