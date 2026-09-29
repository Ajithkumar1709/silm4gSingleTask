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

/* **************************************************************************
 * File Description: This is the main file of adaptation Layer between TTP
 * applications and the USB Manager Package
 *************************************************************************/

#include <string.h>
#include <system.h>
#include <kernel.h>
#include "utils.h"
#include "nucleus.h"

#if defined (UPGRADE_USB)

#include <usbendpoints.h>    /* for configuration identifiers */

#include <usbsigtyp.h>
#include <usbappif.h>
#include <usbscsi.h>
#include "csw_mem.h"

#include "usbmgr_apps_config.h"
#include "UsbMgr.h"
#include "usbmgrttpal_apps_def.h"

#if defined(DIAG_USE_TTPCOM_API)
#include "usbdiag.h"
#endif
#if defined(USB_COMMS_DEVICE_INTERFACE)
#include "ciapex_sig.h"
#endif
#if defined(USB_TTPCOM_EMMI_INTERFACE)
#include <usbemmi.h>    /* for configuration identifiers */
#endif
#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
#include <usbmast.h>
#endif
#if defined(USB_COMMS_DEVICE_INTERFACE)
#include <usbcomm.h>
#endif

#if defined( _FDI_VER_71_ )
#include "mfm_musb_ext.h"
#endif
#define SIGNAL TVSIGNAL
#include <kisigdef.h>
#include <l1ut_sig.h>
#include <l1al_sig.h>
union Signal
{
#include <usbsigdef.h>
#if 0
  /* Signals indicating change in USB cable state (inserted/removed). */
#if defined(DM_USE_NEW_STRUCTURE) && defined(DM_USE_NEW_GPIO_MODULE)
  DmGpioInterruptInd   dmGpioInterruptInd;
#else
  L1AlGpioChangeInd    l1AlGpioChangeInd;
#endif
#endif
  /* Signal to allow/disallow the target to slow clock. */
  L1Dont32kSleepReq    l1Dont32kSleepReq;

#if defined(USB_COMMS_DEVICE_INTERFACE)
    ApexMuxSelectReq            apexMuxSelectReq;
#endif
};





#define USB_MAST_BREQUEST_VALUE         0xFE
#define MAST_CHUNK_SIZE                 512


static  USBMgr_DeviceClassStruct    devClass;

static  ttpEPQStruct                ttpEpQueue[USB_DEVICE_TOTAL_ENDPOINTS];
static  Int16                       requestID = 0;

static  UINT8                      *ttpRxBufPtr[USB_DEVICE_TOTAL_ENDPOINTS];
static  UINT32                      ttpRxBuffLen[USB_DEVICE_TOTAL_ENDPOINTS];
static  BOOL                        ttpALStopTx[USB_DEVICE_TOTAL_ENDPOINTS];
static  BOOL                        ttpALPauseRx[USB_DEVICE_TOTAL_ENDPOINTS];
static  UINT32                      ttpNextRxBuffLen[USB_DEVICE_TOTAL_ENDPOINTS];//used when rx flow is stopped


static  USBMGR_IF_HANDLER           ttpAppsTbl[TTP_APPS_NUMBER];

static  UINT8                       _regAppliacationID;

//static UINT8                      _setupPacket[8];


static UINT8 USBMgrTTPALCtrlRegistered = FALSE;


USBMgr_Status usbMgrStatus_notify = USBMGR_STATUS_NONE;    /* was 0xff; */
#endif //UPGRADE_USB

static UINT32 TTPAL_ative_applications_mask; //will be set from outside which applications are set
static UINT32 TTPAL_MAST_LastChunk = TRUE;
static UINT8  use_card_as_mast = FALSE;

static BOOL usbDriverNeedSetupStatusTxZlp = TRUE;


#if defined (UPGRADE_USB)

static UsbDeviceSelection currentUSBConfiguration = USB_DYNAMIC_SELECTION_C_MAST_MODEM_EMMI;

/****************         Static Functions ******************************************************/

static void     UsbMgrTTPALInterfaceInd( Int8 interface ,Int8 alternate);
static void     UsbMgrTTPALDataphasePayload( UsbDataQuantum dataQuantum );
static UINT32   USBMgrTTPALIsAppEnabled(UINT32 app_id);
static UINT8    TTPALFindAppIdByEPNumber(UINT8 phyEP);
static UINT8    TTPALGetUSBMgrEPIndexByEPNumber(UINT8 phyEP);
static void     UsbMgrTTPALInitGblPrms(void);
static void     UsbMgrTTPALConfigure(void);
static void     UsbMgrTTPALTransmitComp(UsbTransmitDataRequest *request );
static void     UsbMgrTTPALReceiveDataInd( UsbDataQuantum dataQuantum);
static void     UsbMgrTTPALDeviceReq(UINT8 endpoint ,Int8 *setupPacket ,USBMgr_SetupDataType type);
static void     UsbMgrTTPALSetupIndicationFromTask(UsbDeviceRequestInd *device_ctrl_request);
static void     UsbMgrTTPALInterfaceInd( Int8 interface ,Int8 alternate);
static void     UsbMgrTTPALDataphasePayload( UsbDataQuantum dataQuantum );
static void     UsbMgrTTPALAppInitialise(void);
static void     UsbMgrTTPALCtrlIndication(USBMgr_Status usbMgrStatus,USBMgr_Error usbMgrError, UINT32 param );
static void     UsbMgrTTPALCtrlIndicationDummy(USBMgr_Status usbMgrStatus,USBMgr_Error usbMgrError, UINT32 param );
static void     UsbMgrTTPALTxHndIndication(UINT32 cooky,UINT8 endpoint,UINT8* dataPtr,UINT32 dataLen);
static void     UsbMgrTTPALTxIndication(UINT32 cooky,UINT8 endpoint,UINT8* dataPtr,UINT32 dataLen);
static void     UsbMgrTTPALRxIndication(UINT8 endpoint,UINT8* dataPtr,UINT32 dataLength );
static void     UsbMgrTTPALSetupIndication(USBMgr_SetupDataStruct *setupPrm);
static void     UsbMgrTTPALSetupIndicationDummy(USBMgr_SetupDataStruct *setupPrm);
static void     UsbMgrTTPALFindRegPrms(UINT8 appliacationID , usbMgrTTPAL_RegPrmsStruct *regPrm);
static void     USBMgrTTPALEndpointStall(Int8 endpointNumber);

/****************         Static Functions ******************************************************/

extern int UsbMgrTTPALlogical2PhysicalEP(int logicalEP );
extern int UsbMgrTTPALPhysical2logicalEP(int phyEP);
extern void setUSBApplications (UINT16* nmode);

/************************************************************************
* Function:  sendSigUSBCableStateChangeInd
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes: sends SIG_USB_CABLE_STATE_CHANGE_IND signal.
************************************************************************/
static void sendSigUSBCableStateChangeInd( Boolean usbCableInserted )
{
  #if 0
  SignalBuffer signal = kiNullBuffer;

   /* Send Signal to USB task to indicate cable detection */
  KiCreateIntSignal(SIG_USB_CABLE_STATE_CHANGE_IND, sizeof(UsbDclUsbCableStateChangeInd), &signal);

  signal.sig->usbDclUsbCableStateChangeInd.usbCableInserted = usbCableInserted;

  KiSendIntSignal(USB_TARGET_TASK_ID, &signal);
  #endif
}
/************************************************************************
* Function:  USBMgrTTPALIsAppEnabled
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes: check if application is enabled
************************************************************************/
static UINT32 USBMgrTTPALIsAppEnabled(UINT32 app_id)
{
    return((TTPAL_ative_applications_mask & (UINT32)app_id));
}


/************************************************************************
* Function:  TTPALFindAppIdByEPNumber
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes: return application ID by EP number , if does exist return 0xFF
************************************************************************/
static UINT8 TTPALFindAppIdByEPNumber(UINT8 phyEP)
{
    volatile UINT8 app_id = 0xFF;

#if defined(USB_TTPCOM_EMMI_INTERFACE)
    switch(phyEP)
    {
    case USB_EMMI_IN_ENDPOINT_PHY:
    case USB_EMMI_OUT_ENDPOINT_PHY:
        app_id = USBMGR_GENIE_APPID;
        break;
    };
#endif // USB_TTPCOM_EMMI_INTERFACE

#if defined(USB_COMMS_DEVICE_INTERFACE)
    switch(phyEP)
    {
    case USB_COMM_CTRL_IN_ENDPOINT_PHY:
    case USB_COMM_DATA_IN_ENDPOINT_PHY:
    case USB_COMM_DATA_OUT_ENDPOINT_PHY:
        app_id = USBMGR_MODEM_APPID;
    };
#endif // USB_COMMS_DEVICE_INTERFACE

#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
    switch(phyEP)
    {
    case USB_MAST_IN_ENDPOINT_PHY:
    case USB_MAST_OUT_ENDPOINT_PHY:
        app_id = USBMGR_MAST_APPID;
    };
#endif // USB_MASS_STORAGE_BULK_ONLY_INTERFACE

    return(app_id);
}



/************************************************************************
* Function:  TTPALGetUSBMgrEPIndexByEPNumber
*************************************************************************
* Description:
*
* Parameters: UINT8 phyEP - physical enpoint number
*
* Return value:
*
* Notes: return USBMgr logical endpoint index by physical ep number
************************************************************************/
static UINT8 TTPALGetUSBMgrEPIndexByEPNumber(UINT8 phyEP)
{
    //according to the order that those points were registered to USBMgr
    volatile UINT8 ep_ind = 0xFF;

#if defined(USB_TTPCOM_EMMI_INTERFACE)
    switch(phyEP)
    {
    case USB_EMMI_IN_ENDPOINT_PHY:
        ep_ind = 0;
        break;
    case USB_EMMI_OUT_ENDPOINT_PHY:
        ep_ind = 1;
        break;
    };
#endif // USB_TTPCOM_EMMI_INTERFACE

#if defined(USB_COMMS_DEVICE_INTERFACE)
    switch(phyEP)
    {
    case USB_COMM_CTRL_IN_ENDPOINT_PHY:
        ep_ind = 2;
        break;
    case USB_COMM_DATA_IN_ENDPOINT_PHY:
        ep_ind = 0;
        break;
    case USB_COMM_DATA_OUT_ENDPOINT_PHY:
        ep_ind = 1;
        break;
    };
#endif // USB_COMMS_DEVICE_INTERFACE

#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
    switch(phyEP)
    {
    case USB_MAST_IN_ENDPOINT_PHY:
        ep_ind = 0;
        break;
    case USB_MAST_OUT_ENDPOINT_PHY:
        ep_ind = 1;
        break;
    };
#endif // USB_COMMS_DEVICE_INTERFACE

    return(ep_ind);
}



/************************************************************************
* Function:  UsbMgrTTPALInitGblPrms
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
static void UsbMgrTTPALInitGblPrms(void)
{
    UINT8   appIdx ,epIdx;
    //STATUS    osStatus;

    for ( appIdx = 0; appIdx < TTP_APPS_NUMBER;appIdx++)
    {
        ttpAppsTbl[appIdx] = 0;
    }


    for ( epIdx = USB_DEVICE_ENDPOINT_1; epIdx < USB_DEVICE_TOTAL_ENDPOINTS;epIdx++)
    {
        ttpEpQueue[epIdx].ttpEpQueueAddr = NULL;
        ttpEpQueue[epIdx].ptr.freePtr = 0;
        ttpEpQueue[epIdx].ptr.relPtr = 0;
        ttpEpQueue[epIdx].queueSize = 0;

        ttpRxBufPtr[epIdx] = NULL;
        ttpRxBuffLen[epIdx] = 0;

        ttpALStopTx[epIdx]  = FALSE;
        ttpALPauseRx[epIdx] = FALSE;
    }
}



/************************************************************************
* Function:  UsbMgrTTPALConfigure
* ************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
static void UsbMgrTTPALConfigure(void)
{
#if defined(USB_TTPCOM_EMMI_INTERFACE)
    if(USBMgrTTPALIsAppEnabled(USBMGR_GENIE_APPID))
    {
        usbEmmiConfigure();
    }
#endif

#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
    if(USBMgrTTPALIsAppEnabled(USBMGR_MAST_APPID))
    {
        usbMastConfigure();
        usbMastRxFlushComplete();
      /* Send Signal to USB task to indicate cable detection */
      sendSigUSBCableStateChangeInd( TRUE );
    }
#endif

#if defined(USB_COMMS_DEVICE_INTERFACE)
    if(USBMgrTTPALIsAppEnabled(USBMGR_MODEM_APPID))
        /* forward the signal to the USB Mux task */
    {
        /* forward the signal to the USB Mux task */
        SignalBuffer fwdSignal = kiNullBuffer;

        KiCreateIntSignal( SIG_USB_SET_CONFIGURATION_IND,
                           sizeof(UsbSetConfigurationInd),
                           &fwdSignal );
        fwdSignal.sig->usbSetConfigurationInd.configurationValue = 1; // USB_COMM_CONFIGURATION_VALUE
                     //signal->sig->usbSetConfigurationInd.configurationValue;
        KiSendIntSignal( VG_MUX_USBNULL_TASK_ID, &fwdSignal );
    }
#endif
}

/************************************************************************
* Function:  UsbMgrTTPALTransmitComp
* ************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
static void UsbMgrTTPALTransmitComp(UsbTransmitDataRequest *request )
{
    UINT8 phyEP;

    phyEP = UsbMgrTTPALlogical2PhysicalEP(request->logicalEndpoint);

    switch( phyEP )
    {

#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
        case USB_MAST_IN_ENDPOINT_PHY:
        {
            SignalBuffer signal_mast = kiNullBuffer;

            KiCreateIntSignal(SIG_USB_TRANSMIT_COMPLETE_IND,
                              sizeof(EmptySignal), &signal_mast);
            KiSendIntSignal(USB_TARGET_TASK_ID, &signal_mast);
            break;
        }
#endif


#if defined(USB_COMMS_DEVICE_INTERFACE)
        case USB_COMM_CTRL_IN_ENDPOINT_PHY:
            break;//alla , i think we don't need to send signal in ctrl endpoint, there is an assert in vgmuxtask that it is data point.
            //but may be some other signal special for ctrl endpoint ??
        case USB_COMM_DATA_IN_ENDPOINT_PHY:
        {
            SignalBuffer signal_modem = kiNullBuffer;

#if !defined(USB_ISR_DATA_TRANSFERS)
            KiCreateSignal(SIG_USB_TRANSMIT_COMPLETE_IND,
                           sizeof(UsbTransmitCompleteInd), &signal_modem);
            signal_modem.sig->usbTransmitCompleteInd.requestID      = request->requestID;
            signal_modem.sig->usbTransmitCompleteInd.logicalEndpoint = request->logicalEndpoint;
            KiSendSignal(request->taskID, &signal_modem);
#else
            KiCreateIntSignal(SIG_USB_TRANSMIT_COMPLETE_IND,
                              sizeof(UsbTransmitCompleteInd), &signal_modem);
            signal_modem.sig->usbTransmitCompleteInd.requestID      = request->requestID;
            signal_modem.sig->usbTransmitCompleteInd.logicalEndpoint = request->logicalEndpoint;
            KiSendIntSignal(request->taskID, &signal_modem);
#endif /* !defined(USB_ISR_DATA_TRANSFERS) */
        }
        break;
#endif


#if defined(USB_TTPCOM_EMMI_INTERFACE)
        case USB_EMMI_IN_ENDPOINT_PHY:
        {
            usbEmmiBlockTransmitComplete();
            break;
        }
#endif

        default:
            ASSERT(0); //whose tx ?
            break;
    }
}

/************************************************************************
* Function:  UsbMgrTTPALReceiveDataInd
* ************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
static void  UsbMgrTTPALReceiveDataInd( UsbDataQuantum dataQuantum)
{
    UINT8 phyEP;

    phyEP = UsbMgrTTPALlogical2PhysicalEP(dataQuantum.logicalEndpoint);

    switch(phyEP)
    {

#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
        case USB_MAST_OUT_ENDPOINT_PHY:
            usbMastDataReceived( dataQuantum );
            break;
#endif

#if defined(USB_TTPCOM_EMMI_INTERFACE)
        case USB_EMMI_OUT_ENDPOINT_PHY:
            usbEmmiProcessRxData(dataQuantum.dataPtr, dataQuantum.dataLength);
            usbAppifFreeRxBuffer(dataQuantum);
            break;
#endif

#if defined(USB_COMMS_DEVICE_INTERFACE)
        case USB_COMM_DATA_OUT_ENDPOINT_PHY:
        {
            SignalBuffer signal = kiNullBuffer;
            TaskId task;

            /* Look up the Task that owns this Rx channel */
            //task = usbGetRxBufferTaskId( dataQuantum.logicalEndpoint );
            task = VG_MUX_USBNULL_TASK_ID;

            /* Signal that task with the quantum */
#if !defined(USB_ISR_DATA_TRANSFERS)
            KiCreateSignal(SIG_USB_RECEIVE_DATA_IND,
                           sizeof(UsbReceiveDataInd), &signal);
            signal.sig->usbReceiveDataInd.dataQuantum = dataQuantum;
            KiSendSignal(task, &signal);
#else
            KiCreateIntSignal(SIG_USB_RECEIVE_DATA_IND,
                              sizeof(UsbReceiveDataInd), &signal);
            signal.sig->usbReceiveDataInd.dataQuantum = dataQuantum;
            KiSendIntSignal(task, &signal);
#endif /* defined(USB_ISR_DATA_TRANSFERS) */
        }
        break;
#endif  //USB_COMMS_DEVICE_INTERFACE
    }
}

/************************************************************************
* Function:  UsbMgrTTPALDeviceReq
* ************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
static void  UsbMgrTTPALDeviceReq(UINT8 endpoint ,Int8 *setupPacket ,USBMgr_SetupDataType type)
{
    BOOL    classDevReqHnd=FALSE;
    UINT32  cpsr;
    volatile UINT8 bm_request = setupPacket[USB_SETUP_BMREQUEST_INDEX];
    volatile UINT8 b_request  = setupPacket[USB_SETUP_BREQUEST_INDEX];

    if(type == USBMGR_VENDOR)
    {

    }
    else                                /* Class device request */
    {
        /* CL133748
        ** KE2 01 March 2005
        ** added to allow drivers to ignore calls from usbXXXXdv code to
        **          usbDclControlTransferStatusStage(USB_ENDPOINT_ZERO);
        **
        ** This call is not required in some situations on this hardware
        */
        if( bm_request & USB_SETUP_REQUEST_DIRECTION_TO_HOST )
        {
            usbDriverNeedSetupStatusTxZlp = FALSE;
        }
        /** End KE2 CL133748 **/

#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE) //!!! note only MAST & MODEM have EP 0 requests
        if(  b_request == USB_MAST_BREQUEST_VALUE)//so for MODEM we will just check if brequest does not belong to MAST
        {
            cpsr = disableInterrupts();
            classDevReqHnd = usbMastClassDeviceRequest((Int8) endpoint, setupPacket);
            restoreInterrupts(cpsr);
        }
#endif /*   USB_MASS_STORAGE_BULK_ONLY_INTERFACE */

#if defined(USB_COMMS_DEVICE_INTERFACE)
        if(  b_request != USB_MAST_BREQUEST_VALUE)//so for MODEM we will just check if brequest does not belong to MAST
        {
            classDevReqHnd = usbCommDevAppClassDeviceRequest((Int8) endpoint, setupPacket); //setupPacketlogical);
        }
#endif /*   USB_COMMS_DEVICE_INTERFACE */

        /** KE2 CL133748 **/
        usbDriverNeedSetupStatusTxZlp = TRUE;
        /** End KE2 CL133748 **/
    }


    if(!classDevReqHnd)
    {
        /* It wasn't handled by any of the above, so complain */
        ASSERT(0);
    }
}


/************************************************************************
* Function:  UsbMgrTTPALSetupIndicationFromTask
* ************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes: called from TARGET_TASK , actually setup indication
************************************************************************/
//debug_cnt
UINT32 ind_vendor_cnt=0;
UINT32 ind_class_cnt=0;
UINT32 ind_standard_cnt=0;
UINT32 ind_standard_set_if_cnt=0;
UINT32 ind_other_cnt=0;
static void  UsbMgrTTPALSetupIndicationFromTask(UsbDeviceRequestInd *device_ctrl_request)
{
    volatile UINT8 _setupPacket[USB_SPEC_LENGTH_OF_SETUP_PACKET];
    UsbDataQuantum          dataQuantum;
    USBMgr_SetupDataStruct *setupPrm;
    UINT32 setupPrm_addr;

    //alla - retreive the USBMgr_SetupDataStruct * according to patch during signal sending
    //not to forger to release memory for USBMgr_SetupDataStruct * and all its members pointers

    memcpy(&setupPrm_addr,device_ctrl_request->setupPacket,sizeof(UINT32));
    setupPrm = (USBMgr_SetupDataStruct *)setupPrm_addr;


    //now continue to process
    CONVERT_SETUP_TO_TTPCOM_PRM(setupPrm , _setupPacket);
    if(setupPrm->type == USBMGR_VENDOR)
    {
        UsbMgrTTPALDeviceReq (0 , (Int8 *)&_setupPacket[0],USBMGR_VENDOR);
        ind_vendor_cnt++;
    }
    else
    {
        if(setupPrm->type == USBMGR_CLASS)
        {
            UsbMgrTTPALDeviceReq(0 , (Int8 *)&_setupPacket[0] ,USBMGR_CLASS);
            ind_class_cnt++;
        }
        else /*standard*/
        {
            if(setupPrm->type == USBMGR_STANDARD)
            {
                if(setupPrm->request == USBMGR_SET_INTERFACE)
                {
                    UsbMgrTTPALInterfaceInd( (Int8)setupPrm->index,(Int8) setupPrm->value);
                    ind_standard_set_if_cnt++;
                }

                ind_standard_cnt++;
            }
            else
                ind_other_cnt++;
        }
    }


   //alla
    if(setupPrm->hostToDeviceDataPtr != NULL )
    {
        dataQuantum.logicalEndpoint = (Int8)0;
        dataQuantum.dataLength = (Int16)(setupPrm->dataStagelength);
        //TTP always calls free buffer function so we always allocating on EP 0
        dataQuantum.dataPtr = malloc(dataQuantum.dataLength); //will be released in rx free buffer
        memcpy(dataQuantum.dataPtr,(setupPrm->hostToDeviceDataPtr),dataQuantum.dataLength);
        dataQuantum.counterValue = (Int16)0;
        UsbMgrTTPALDataphasePayload( dataQuantum );

        free(setupPrm->hostToDeviceDataPtr);
    }


    //now release the struct
    free(setupPrm);
}




/************************************************************************
* Function:  UsbMgrTTPALInterfaceInd
* ************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
static void UsbMgrTTPALInterfaceInd( Int8 interface ,Int8 alternate)
{
}


/************************************************************************
* Function:  UsbMgrTTPALInterfaceInd
* ************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
static void UsbMgrTTPALDataphasePayload( UsbDataQuantum dataQuantum )
{
    BOOL payloadDevReqHnd;

#if defined(USB_COMMS_DEVICE_INTERFACE)
    payloadDevReqHnd = usbCommDevAppClassDevicePayload( dataQuantum );
#endif /*   USB_COMMS_DEVICE_INTERFACE */
}


/************************************************************************
* Function:  UsbMgrTTPALAppInitialise
* ************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
static void UsbMgrTTPALAppInitialise(void)
{
#if defined(USB_TTPCOM_EMMI_INTERFACE)
    //usbEmmiResetApplication(UNKNOWN_TASK_ID); //0xFF
    usbEmmiDevAppInitialise();
#endif

#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
    //usbMastInitialise();
    //usbMastDevAppInitialise();
    usbMastResetApplication(USB_TARGET_TASK_ID);
#endif

#if defined(USB_COMMS_DEVICE_INTERFACE)
    usbCommDevAppInitialise(); /* initialise the application (i.e. the mux) */
    usbCommDevInitialise();    /* initialise the CDC device command handler */
    usbCommNotifyInitialise(); /* initialise the CDC notifications module   */


    {
        UsbMgrTTPALSetMuxUSB();
    }
#endif
}

/************************************************************************
* Function:  USBMgrTTPALInsertToQ
* ************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
USBMgr_RC USBMgrTTPALInsertToQ( UsbTransmitDataRequest *reqMsg )
{
    UINT32                cpsr;
    USBMgr_RC             usbmgrTTPALStatus = USBMGR_RC_OK;
    UINT8                 phyEP;

    cpsr = disableInterrupts();

      /*add message to QUEUE (if  not full)*/

    phyEP = UsbMgrTTPALlogical2PhysicalEP(reqMsg->logicalEndpoint);

    if( FULL_QUEUE(ttpEpQueue[phyEP].ptr ,ttpEpQueue[phyEP].queueSize) )
        usbmgrTTPALStatus = USBMGR_RC_TX_BUFFER_FULL;

    memcpy ((NEXT_PTR_ON_Q((UINT8*)(ttpEpQueue[phyEP].ttpEpQueueAddr),ttpEpQueue[phyEP].ptr.freePtr)) ,
               (UINT8*)reqMsg, sizeof(UsbTransmitDataRequest) );

    INC_Q_PTR(ttpEpQueue[phyEP].ptr.freePtr ,ttpEpQueue[phyEP].queueSize);
    restoreInterrupts(cpsr);

    return(usbmgrTTPALStatus);
}

/************************************************************************
* Function:  USBMgrTTPALGetFromQ
* ************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
USBMgr_RC USBMgrTTPALGetFromQ( UINT8 endpoint ,UsbTransmitDataRequest **reqMsg )
{
    UINT32 cpsr;

    cpsr = disableInterrupts();

    if ( ( EMPTY_QUEUE(ttpEpQueue[endpoint].ptr) )&& ( !(ttpALStopTx[endpoint]) ) )
    {
        restoreInterrupts(cpsr);
        return(USBMGR_RC_NO_MSG);
    }


    *reqMsg = (UsbTransmitDataRequest *)(NEXT_PTR_ON_Q((UINT8*)ttpEpQueue[endpoint].ttpEpQueueAddr , ttpEpQueue[endpoint].ptr.relPtr ) );


    restoreInterrupts(cpsr);
    return(USBMGR_RC_OK);
}



/************************************************************************
* Function:  UsbMgrTTPALCtrlInd
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes: Control Indication
************************************************************************/

static void UsbMgrTTPALCtrlIndication(USBMgr_Status usbMgrStatus,USBMgr_Error usbMgrError, UINT32 param )
{
    volatile UINT8 epIdx;

//alla - we have a problem here in MODEM if this notify arrives before all traffic on EP0 was completed
//UsbMgrTTPALConfigure will call PS function which transmits on EP5 , host might not be ready for it yet
//meanwhile leaving it like this because mostly it worked , but if timings are changed this might cause the problem
//if problem occures the workaround in the usbDclControlTransferStatusStage can be enabling
//configure modem only after EP 0 traffic is over

    usbMgrStatus_notify = usbMgrStatus;
    switch(usbMgrStatus)
    {
        case USBMGR_INTERFACE_ACTIVE:
            UsbMgrTTPALConfigure( );
            break;
        case USBMGR_RESET_DETECT:
        {
            if(USBMgrTTPALIsAppEnabled(USBMGR_MODEM_APPID))
            {
                UsbMgrTTPALSetMuxUSB_INT();
            }

            //clean queues
            for ( epIdx = USB_DEVICE_ENDPOINT_1; epIdx < USB_DEVICE_TOTAL_ENDPOINTS;epIdx++)
            {
                MAKE_Q_EMPTY (ttpEpQueue[epIdx].ptr);
            }
            break;
        }
        case USBMGR_CABLE_OUT: // if was modem USB was active , release MUX
            //removing mux switch because the handling is done in vgmxusbnull.c
            //if(USBMgrTTPALIsAppEnabled(USBMGR_MODEM_APPID))
            // {
            //    UsbMgrTTPALSetMuxUART_INT();
            //}
#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
            if(USBMgrTTPALIsAppEnabled(USBMGR_MAST_APPID))
            {
              /* Send Signal to USB task to indicate cable removal */
              sendSigUSBCableStateChangeInd( FALSE );
            }
#endif
            break;
    }
}


static void UsbMgrTTPALCtrlIndicationDummy(USBMgr_Status usbMgrStatus,USBMgr_Error usbMgrError, UINT32 param )
{
}


/************************************************************************
* Function:  UsbMgrTTPALHndTxlInd
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
static void UsbMgrTTPALTxHndIndication(UINT32 cooky,UINT8 endpoint,UINT8* dataPtr,UINT32 dataLen)
{
    UsbTransmitDataRequest      *request;


    if( USBMgrTTPALGetFromQ(  endpoint , &request ) == USBMGR_RC_NO_MSG )
        ASSERT(0);                            // if no messages in queue  then must be critical error

    if( (request->pData != dataPtr )|| (request->length != dataLen ) )
        ASSERT(0);                            // if no messages in indication  then must be critical error

    INC_Q_PTR(ttpEpQueue[endpoint].ptr.relPtr ,ttpEpQueue[endpoint].queueSize);


    UsbMgrTTPALTransmitComp(request);
}


/************************************************************************
* Function:  UsbMgrTTPALTxlInd
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
static void UsbMgrTTPALTxIndication(UINT32 cooky,UINT8 endpoint,UINT8* dataPtr,UINT32 dataLen)
{
    UsbMgrTTPALTxHndIndication(cooky,endpoint,dataPtr, dataLen);
}


/************************************************************************
* Function:  UsbMgrTTPALRxInd
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
static void UsbMgrTTPALRxIndication(UINT8 endpoint,UINT8* dataPtr,UINT32 dataLength )
{
    UsbDataQuantum dataQuantum;

    dataQuantum.logicalEndpoint = UsbMgrTTPALPhysical2logicalEP((Int8)endpoint);
    dataQuantum.dataPtr = (Int8*)dataPtr;
    dataQuantum.counterValue = (Int16)0;
#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
    if( (dataQuantum.logicalEndpoint == USB_MAST_OUT_ENDPOINT) && (dataLength > MAST_CHUNK_SIZE))
    {

        UINT32 chunks = (dataLength/MAST_CHUNK_SIZE);
        UINT32 last_chunk_length = (dataLength - (chunks*MAST_CHUNK_SIZE));
        UINT32 i;

        TTPAL_MAST_LastChunk = FALSE;
        for(i=0;i<chunks;i++)
        {
             if(last_chunk_length == 0 && i== (chunks-1) )
             {
                TTPAL_MAST_LastChunk = TRUE;
             }
             dataQuantum.dataLength = MAST_CHUNK_SIZE;
             UsbMgrTTPALReceiveDataInd(dataQuantum);
             dataQuantum.dataPtr += MAST_CHUNK_SIZE;
        }

        if(last_chunk_length) //if remains
        {
            TTPAL_MAST_LastChunk = TRUE;
            dataQuantum.dataLength = last_chunk_length;
            UsbMgrTTPALReceiveDataInd(dataQuantum);
        }
    }
    else
#endif
    {
        dataQuantum.dataLength = (Int16)dataLength;
        UsbMgrTTPALReceiveDataInd(dataQuantum);
    }
}


/************************************************************************
* Function:  UsbMgrTTPALSetupInd
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes: called by USBMgr from HISR  for setup message
************************************************************************/
UINT32 ttpal_dbg_addr;
UINT8 ttpal_dbg_buf[8];
UINT32 ttpal_dbg_signal_send_cnt=0;
static void UsbMgrTTPALSetupIndication(USBMgr_SetupDataStruct *setupPrm)
{
    #if 0
    SignalBuffer signal = kiNullBuffer;
    USBMgr_SetupDataStruct *setup_packet_from_usbmgr;
    UINT32 USBMgr_SetupDataStruct_addr;


    //alla -  we can't use TTP struct for SIG_USB_CLASS_DEVICE_REQUEST_IND
    //because it does not include payload buffer and we have no other means
    //to transfer payload rather than with signal buffer;
    //sending signal is within TTPAL file , so we will apply a patch to store
    //in the usbClassDeviceRequestInd.setupPacket pointer to USBMgr_SetupDataStruct *
    //rather than setup packet itself,
    //!!!!! note that this pointer must be freed by task upon completion of invoking PS functions

    setup_packet_from_usbmgr = malloc(sizeof(USBMgr_SetupDataStruct));
    memcpy(setup_packet_from_usbmgr,setupPrm,sizeof(USBMgr_SetupDataStruct));
    memcpy(ttpal_dbg_buf,setupPrm->setup_packet,8);
    if(setupPrm->hostToDeviceDataPtr) //copy payload if any
    {
        setup_packet_from_usbmgr->hostToDeviceDataPtr = malloc(setup_packet_from_usbmgr->dataStagelength);
        memcpy(setup_packet_from_usbmgr->hostToDeviceDataPtr,setupPrm->hostToDeviceDataPtr,setup_packet_from_usbmgr->dataStagelength);
    }

    USBMgr_SetupDataStruct_addr = (UINT32)setup_packet_from_usbmgr; //store ptr it will be copied to signal
    ttpal_dbg_addr = USBMgr_SetupDataStruct_addr;

    KiCreateIntSignal(SIG_USB_CLASS_DEVICE_REQUEST_IND,
                            sizeof(UsbDeviceRequestInd), &signal);
    signal.sig->usbClassDeviceRequestInd.physicalEndpoint = 0;

    //copying address to the first 4 bytes of the setup buffer
    memcpy (signal.sig->usbClassDeviceRequestInd.setupPacket, &USBMgr_SetupDataStruct_addr, sizeof(UINT32));

    ttpal_dbg_signal_send_cnt++;
    KiSendIntSignal(USB_TARGET_TASK_ID, &signal);
    #endif
}

static void UsbMgrTTPALSetupIndicationDummy(USBMgr_SetupDataStruct *setupPrm)
{
}


/************************************************************************
* Function:  UsbMgrTTPALFindRegPrms
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
static void UsbMgrTTPALFindRegPrms(UINT8 appliacationID , usbMgrTTPAL_RegPrmsStruct *regPrm)
{

    USBMgr_EndpointStruct           *endpointCfg ,*endpointCfgIdx;
    USBMgr_DeviceClassStruct        *deviceClass;
    USBMgr_CallbackIndicationStruct *indicationCallback;

    indicationCallback =  (USBMgr_CallbackIndicationStruct *)Malloc( sizeof(USBMgr_CallbackIndicationStruct ) );

   _regAppliacationID = appliacationID;

    switch ( appliacationID)
    {
        case  USBMGR_MAST_APPID :
            regPrm->numEndpoint                                      = MASS_STORAGE_NUM_ENDPOINTS;
            /*initiates IN endpoint */
            endpointCfg = (USBMgr_EndpointStruct *) Malloc( 2 * sizeof(USBMgr_EndpointStruct) ) ;
            endpointCfgIdx = endpointCfg;

            endpointCfgIdx->type                                     = USBMGR_EP_BULK;
            endpointCfgIdx->direction                                = USBMGR_DIR_IN;
            endpointCfgIdx->useDMA                                   = FALSE;     // was TRUE;
            endpointCfgIdx->endpointDef.txDef.txQueueLen             = MAST_QUEUE_LENGTH;  //ttpEpQueue[USB_DEVICE_ENDPOINT_1].queueSize;
            endpointCfgIdx->endpointDef.txDef.optionalTxQueuePtr     = NULL;
            endpointCfgIdx->endpointDef.txDef.multiTransmitEnabled   = FALSE;
            endpointCfgIdx->endpointDef.txDef.useExternalMem         = FALSE;
            endpointCfgIdx->endpointDef.txDef.cooky                  = 0;
            /*initiates OUT endpoint */
            endpointCfgIdx++;
            endpointCfgIdx->type                                     = USBMGR_EP_BULK;
            endpointCfgIdx->direction                                = USBMGR_DIR_OUT;
            endpointCfgIdx->useDMA                                   = FALSE;
            endpointCfgIdx->endpointDef.rxDef.rxBuffQuantumLen       = ttpRxBuffLen[USB_MAST_OUT_ENDPOINT_PHY];
            endpointCfgIdx->endpointDef.rxDef.optionalRxBufferPtr    = ttpRxBufPtr[USB_MAST_OUT_ENDPOINT_PHY];
            endpointCfgIdx->endpointDef.rxDef.useExternalMem         = FALSE;
            endpointCfgIdx->endpointDef.rxDef.expect_zlp             = FALSE;

            regPrm->endpointCfg                                      = endpointCfg;

            deviceClass = &devClass;

            deviceClass->class                                       = 0x08;
            deviceClass->subClass                                    = 0x06;
            deviceClass->protocol                                    = 0x50;

            regPrm->deviceClass                                      = deviceClass;
            regPrm->interfaceString                                  = "";
            regPrm->appID                                            = appliacationID;
            break;


        case  USBMGR_GENIE_APPID :
            regPrm->numEndpoint                                      = GENIE_NUM_ENDPOINTS;
            /*initiates IN endpoint */
            endpointCfg = (USBMgr_EndpointStruct *) Malloc( 2 * sizeof(USBMgr_EndpointStruct) ) ;
            endpointCfgIdx = endpointCfg;

            endpointCfgIdx->type                                     = USBMGR_EP_BULK;
            endpointCfgIdx->direction                                = USBMGR_DIR_IN;
            endpointCfgIdx->useDMA                                   = FALSE;     // was TRUE;
            endpointCfgIdx->endpointDef.txDef.txQueueLen             = MAST_QUEUE_LENGTH;  //ttpEpQueue[USB_DEVICE_ENDPOINT_1].queueSize;
            endpointCfgIdx->endpointDef.txDef.optionalTxQueuePtr     = NULL;
            endpointCfgIdx->endpointDef.txDef.multiTransmitEnabled   = FALSE;
            endpointCfgIdx->endpointDef.txDef.useExternalMem         = FALSE;
            endpointCfgIdx->endpointDef.txDef.cooky                  = 0;
            /*initiates OUT endpoint */
            endpointCfgIdx++;
            endpointCfgIdx->type                                     = USBMGR_EP_BULK;
            endpointCfgIdx->direction                                = USBMGR_DIR_OUT;
            endpointCfgIdx->useDMA                                   = FALSE;
            endpointCfgIdx->endpointDef.rxDef.rxBuffQuantumLen       = ttpRxBuffLen[USB_EMMI_OUT_ENDPOINT_PHY];
            endpointCfgIdx->endpointDef.rxDef.optionalRxBufferPtr    = ttpRxBufPtr[USB_EMMI_OUT_ENDPOINT_PHY];
            endpointCfgIdx->endpointDef.rxDef.useExternalMem         = FALSE;
            endpointCfgIdx->endpointDef.rxDef.expect_zlp             = TRUE;

            regPrm->endpointCfg                                      = endpointCfg;

            deviceClass = &devClass;

            deviceClass->class                                       = 0xFF;
            deviceClass->subClass                                    = 0x01;
            deviceClass->protocol                                    = 0x01;

            regPrm->deviceClass                                      = deviceClass;
            regPrm->interfaceString                                  = "";
            regPrm->appID                                            = appliacationID;
            break;

        case  USBMGR_MODEM_APPID :
            regPrm->numEndpoint                                      = MODEM_NUM_ENDPOINTS;
            /*initiates IN endpoint */
            endpointCfg = (USBMgr_EndpointStruct *) Malloc( MODEM_NUM_ENDPOINTS * sizeof(USBMgr_EndpointStruct) ) ;
            endpointCfgIdx = endpointCfg;

            endpointCfgIdx->type                                     = USBMGR_EP_BULK;
            endpointCfgIdx->direction                                = USBMGR_DIR_IN;
            endpointCfgIdx->useDMA                                   = FALSE;     // was TRUE;
            endpointCfgIdx->endpointDef.txDef.txQueueLen             = MAST_QUEUE_LENGTH;  //ttpEpQueue[USB_DEVICE_ENDPOINT_1].queueSize;
            endpointCfgIdx->endpointDef.txDef.optionalTxQueuePtr     = NULL;
            endpointCfgIdx->endpointDef.txDef.multiTransmitEnabled   = FALSE;
            endpointCfgIdx->endpointDef.txDef.useExternalMem         = FALSE;
            endpointCfgIdx->endpointDef.txDef.cooky                  = 0;
            /*initiates OUT endpoint */
            endpointCfgIdx++;
            endpointCfgIdx->type                                     = USBMGR_EP_BULK;
            endpointCfgIdx->direction                                = USBMGR_DIR_OUT;
            endpointCfgIdx->useDMA                                   = FALSE;
            endpointCfgIdx->endpointDef.rxDef.rxBuffQuantumLen       = ttpRxBuffLen[USB_COMM_DATA_OUT_ENDPOINT_PHY];
            endpointCfgIdx->endpointDef.rxDef.optionalRxBufferPtr    = ttpRxBufPtr[USB_COMM_DATA_OUT_ENDPOINT_PHY];
            endpointCfgIdx->endpointDef.rxDef.useExternalMem         = FALSE;
            endpointCfgIdx->endpointDef.rxDef.expect_zlp             = FALSE; //alla - can not expect zlp

            /*initiates CONTROL endpoint */
            endpointCfgIdx++;
            endpointCfgIdx->type                                     = USBMGR_EP_INT;
            endpointCfgIdx->direction                                = USBMGR_DIR_IN;
            endpointCfgIdx->useDMA                                   = FALSE;     // was TRUE;
            endpointCfgIdx->endpointDef.txDef.txQueueLen             = MAST_QUEUE_LENGTH;  //ttpEpQueue[USB_DEVICE_ENDPOINT_1].queueSize;
            endpointCfgIdx->endpointDef.txDef.optionalTxQueuePtr     = NULL;
            endpointCfgIdx->endpointDef.txDef.multiTransmitEnabled   = FALSE;
            endpointCfgIdx->endpointDef.txDef.useExternalMem         = FALSE;
            endpointCfgIdx->endpointDef.txDef.cooky                  = 0;

            regPrm->endpointCfg                                      = endpointCfg;

            deviceClass = &devClass;

            deviceClass->class                                       = 0x02;
            deviceClass->subClass                                    = 0x02;
            deviceClass->protocol                                    = 0x01;

            regPrm->deviceClass                                      = deviceClass;
            regPrm->interfaceString                                  = "";
            regPrm->appID                                            = appliacationID;

            break;

        default:
            break;
    }


    //!!! Note this is ugly patch !!!!
    //Will not work if any other applications will register to ep0, assumes that ttpal is the only ep0 receiver in system
    //will not work if one of the appliations unregisters from usbmgr
    //should be implemented differently: each application modem,mast,genie must register with separate functions for CTRL and SETUP
    //function must process message and discard it if it was intented to the specific application in case of setup
    //in case of ctrl perform required actions
    if(USBMgrTTPALCtrlRegistered == FALSE)
    {
        indicationCallback->controllIndFunc                      = UsbMgrTTPALCtrlIndication;
        indicationCallback->setupCommandIndFunc                  = UsbMgrTTPALSetupIndication;
        USBMgrTTPALCtrlRegistered = TRUE;
    }
    else
    {
        indicationCallback->controllIndFunc                      = UsbMgrTTPALCtrlIndicationDummy;
        indicationCallback->setupCommandIndFunc                  = UsbMgrTTPALSetupIndicationDummy;
    }
    indicationCallback->TxIndFunc                            = UsbMgrTTPALTxIndication;
    indicationCallback->RxIndFunc                            = UsbMgrTTPALRxIndication;

    regPrm->indicationCallback                               = indicationCallback;
}



/************************************************************************
* Function:  UsbMgrTTPALRegister
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/

void UsbMgrTTPALRegister( UINT8 appliacationID)
{
    USBMgr_RC                   usbmgrStatus;
    usbMgrTTPAL_RegPrmsStruct   regPrmStruct;
    USBMGR_IF_HANDLER           interfaceHnd;


    UsbMgrTTPALFindRegPrms(appliacationID ,&regPrmStruct);



    usbmgrStatus = USBMgrRegister(regPrmStruct.numEndpoint, regPrmStruct.endpointCfg,
                                   regPrmStruct.deviceClass,regPrmStruct.interfaceString,regPrmStruct.appID,
                                   regPrmStruct.indicationCallback, &interfaceHnd);


    Free((void *)regPrmStruct.endpointCfg);
    Free((void *)regPrmStruct.indicationCallback);

    if(usbmgrStatus == USBMGR_RC_OK)
        ttpAppsTbl[appliacationID] = interfaceHnd;
    else
        ASSERT(0);
}

/************************************************************************
* Function:  UsbAppifInitTxQueue
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
void usbAppifInitTxQueue(Int8 logicalEndpoint, UsbTransmitDataRequest *startAddress ,Int8 queuelength, TaskId task)
{
    UINT8               phyEP;

    phyEP = UsbMgrTTPALlogical2PhysicalEP(logicalEndpoint);

    if(ttpEpQueue[phyEP].ttpEpQueueAddr!= NULL )
        ASSERT(0);

    ttpEpQueue[phyEP].ttpEpQueueAddr     = startAddress;
    ttpEpQueue[phyEP].queueSize          = queuelength;
    if(queuelength >5 )
        ttpEpQueue[phyEP].ptr.queueTh = 2;
    else
        ttpEpQueue[phyEP].ptr.queueTh = 1;
}

/************************************************************************
* Function:  UsbAppifDefaultTransmitRequest
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
void  usbAppifDefaultTransmitRequest (UsbTransmitDataRequest *request)
{
    #if 0
    request->requestID          = 0;
    request->pData              = PNULL;
    request->length             = 0;
    request->logicalEndpoint    = 0;
    request->fixedPacketSize    = 0;
    request->variablePacketSize = PNULL;
    request->taskID             = USB_TARGET_TASK_ID; /* Reply-to Task */
    request->requestSubmitMode  = USB_SUBMIT_BY_SIGNAL;
    #endif
}



/************************************************************************
* Function:  UsbGetRequestID
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
Int16 UsbGetRequestID(void)
{
   return ((++requestID) & 0x0fff);
}

/************************************************************************
* Function:  UsbAppifTransmit
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
void  usbAppifTransmit (UsbTransmitDataRequest *request)
{
    USBMgr_RC           usbmgrStatus;
    UINT8               usb_mgr_app_id ,usb_mgr_ep_index, phyEP;
    USBMGR_IF_HANDLER   interfaceHnd;
    BOOL zlp=TRUE;

    if(request->logicalEndpoint != 0)
    {
        phyEP = UsbMgrTTPALlogical2PhysicalEP(request->logicalEndpoint);

        if( (ttpALStopTx[phyEP])&&(FREE_QUEUE(ttpEpQueue[phyEP].ptr ,ttpEpQueue[phyEP].queueSize )) )
            ttpALStopTx[phyEP] = FALSE;

        if (ttpALStopTx[phyEP])
            return;


        usb_mgr_app_id = TTPALFindAppIdByEPNumber(phyEP);
        usb_mgr_ep_index = TTPALGetUSBMgrEPIndexByEPNumber(phyEP);


        interfaceHnd = ttpAppsTbl[usb_mgr_app_id];
        zlp = ((usb_mgr_app_id != USBMGR_MAST_APPID));

    /*insert to  TTP AL Queue */

        if (USBMgrTTPALInsertToQ( request ) != USBMGR_RC_OK)
            ttpALStopTx[phyEP] = TRUE;


        usbmgrStatus = USBMgrTransmit( interfaceHnd,usb_mgr_ep_index, (UINT8 *)request->pData ,(UINT32)request->length, zlp );

        if( (usbmgrStatus != USBMGR_RC_OK)&&(usbmgrStatus != USBMGR_RC_TX_BUFFER_FULL)
            && (usbmgrStatus != USBMGR_RC_ENDPOINT_STALLED) && (usbmgrStatus !=USBMGR_RC_DEVICE_NOT_CONNECTED))
            ASSERT(0);
    }
    else
        USBMgrSetupCommandRsp((UINT8 *)request->pData , (UINT16)request->length);
}


/************************************************************************
* Function:  UsbAppifFlushTransmitRequestQueue
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
void usbAppifFlushTransmitRequestQueue(Int8 logicalEndpoint)
{
    UINT8               usb_mgr_app_id ,usb_mgr_ep_index, phyEP;
    USBMGR_IF_HANDLER   interfaceHnd;

    phyEP = UsbMgrTTPALlogical2PhysicalEP(logicalEndpoint);

    usb_mgr_app_id = TTPALFindAppIdByEPNumber(phyEP);
    usb_mgr_ep_index = TTPALGetUSBMgrEPIndexByEPNumber(phyEP);


    interfaceHnd = ttpAppsTbl[usb_mgr_app_id];


    USBMgrFlushTxQueue( interfaceHnd ,usb_mgr_ep_index);
}


/************************************************************************
* Function:  UsbAppifFlushRxBuffer
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
void  usbAppifFlushRxBuffer(Int8 endpointNumber)
{
    UINT8               usb_mgr_app_id ,usb_mgr_ep_index, phyEP;
    USBMGR_IF_HANDLER   interfaceHnd;

    phyEP = UsbMgrTTPALlogical2PhysicalEP(endpointNumber);


    usb_mgr_app_id   = TTPALFindAppIdByEPNumber(phyEP);
    usb_mgr_ep_index = TTPALGetUSBMgrEPIndexByEPNumber(phyEP);


    usb_mgr_ep_index = TTPALFindAppIdByEPNumber(phyEP);

    interfaceHnd = ttpAppsTbl[usb_mgr_app_id];

    USBMgrFlushRxBuffer (interfaceHnd ,usb_mgr_ep_index);
}

/************************************************************************
* Function:  UsbAppifDefaultRxBufferStructure
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
void  usbAppifDefaultRxBufferStructure(UsbRxBuffer *rxBufferSpec)
{
}

/************************************************************************
* Function:  UsbAppifInitRxBuffer
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
void usbAppifInitRxBuffer( UsbRxBuffer rxBuffer )
{
    UINT8 phyEP;

    phyEP = UsbMgrTTPALlogical2PhysicalEP(rxBuffer.logicalEndpoint);


    ttpRxBufPtr[phyEP]   = (UINT8 *)rxBuffer.startAddress;
    if(phyEP == USB_COMM_DATA_OUT_ENDPOINT_PHY)
    {
        //alla - modifying buffer size to be equal to FIFO size otherwise rx will get stuck//
        ttpRxBuffLen[phyEP]  = USBMgrGetHWCfgEPMaxPacketSize(USB_COMM_DATA_OUT_ENDPOINT_PHY) ;
    }
    else
    {
        ttpRxBuffLen[phyEP]  = (UINT32)rxBuffer.length;
    }
}

/************************************************************************
* Function:  UsbAppifFreeRxBuffer
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
void  usbAppifFreeRxBuffer(UsbDataQuantum dataQuantum)
{
    if(dataQuantum.logicalEndpoint == 0)
    {
        if(dataQuantum.dataPtr)
            free(dataQuantum.dataPtr); //was allocated in setupindication

    }
    else
    {
        UINT8 phy_endpoint = UsbMgrTTPALlogical2PhysicalEP(dataQuantum.logicalEndpoint);

        switch(phy_endpoint)
        {
#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
            //!!! NOTE assuming that MAST endpoint max packet size is bigger than MAST_CBW_LENGTH
            //!!! otherwise this will not work
            case USB_MAST_OUT_ENDPOINT_PHY:
                if(TTPAL_MAST_LastChunk)
                {
                    volatile UINT32 next_packet_length = MAST_CBW_LENGTH;
                    volatile UINT8 bmCBWFlags;
                    if(dataQuantum.dataLength == MAST_CBW_LENGTH)
                    {
                        bmCBWFlags = *((UINT8*)(dataQuantum.dataPtr + MAST_bmCBWFlags_BYTE_OFFSET));
                        next_packet_length  = *((UINT32*)(dataQuantum.dataPtr + MAST_dCBWDataTransferLength_BYTE_OFFSET));
                        if(next_packet_length == 0) //if length is zero next packet will be of MAST_CBW_LENGTH
                        {
                            next_packet_length = MAST_CBW_LENGTH;
                        }
                        else
                        {
                            //if next transfer direction  will be IN so next_packet_length is still MAST_CBW_LENGTH
                            if( (bmCBWFlags & (1<<MAST_bmCBWFlags_DATA_DIR_BIT_OFFSET)) ==
                                (MAST_bmCBWFlags_DATA_DIR_D2H<<MAST_bmCBWFlags_DATA_DIR_BIT_OFFSET)
                              )
                                next_packet_length = MAST_CBW_LENGTH;
                        }
                    }

                    ttpNextRxBuffLen[phy_endpoint]=next_packet_length;

                    if(ttpALPauseRx[phy_endpoint] == FALSE)//if was not paused
                    {
                        USBMgrRxConfirmationExt((USBDevice_EndpointE)phy_endpoint,ttpNextRxBuffLen[phy_endpoint],FALSE);
                    }
                 }
                break;
#endif
#if defined(USB_COMMS_DEVICE_INTERFACE)
            case USB_COMM_DATA_OUT_ENDPOINT_PHY:
                ttpNextRxBuffLen[phy_endpoint]=ttpRxBuffLen[phy_endpoint];
                if(ttpALPauseRx[phy_endpoint] == FALSE)//if was not paused
                {
                    USBMgrRxConfirmationExt((USBDevice_EndpointE)phy_endpoint,ttpNextRxBuffLen[phy_endpoint] ,FALSE); //alla - rx packet size must beequal to fifo size
                }
                break;
#endif
            default:
                ttpNextRxBuffLen[phy_endpoint]=0;//to indicate no length should be used
                if(ttpALPauseRx[phy_endpoint] == FALSE)//if was not paused
                {
                    USBMgrRxConfirmation((USBDevice_EndpointE)phy_endpoint);
                }
                break;
        }
    }
}


/************************************************************************
* Function:  usbAppifRequestReceiveData
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
void usbAppifRequestReceiveData( Int8 logicalEndpoint )
{

}

/************************************************************************
* Function:  usbAppifRequestReceiveBufferFreeSpace
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
void usbAppifRequestReceiveBufferFreeSpace( Int8 logicalEndpoint )
{

}

/************************************************************************
* Function:  UsbAppifPauseRxFlow
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
//debug
static  UINT32  PauseRxFlow_cnt_false=0;
static  UINT32  PauseRxFlow_cnt_true=0;
void  usbAppifPauseRxFlow(Boolean pause ,Int8 endpointNumber)
{
    UINT8   phy_endpoint_ind = UsbMgrTTPALlogical2PhysicalEP(endpointNumber);


    if(pause ==0) PauseRxFlow_cnt_false++;
    if (pause) PauseRxFlow_cnt_true++;

    if(pause)// requested to stop
    {
        DevAssert( (ttpALPauseRx[phy_endpoint_ind] == FALSE )); //make sure we are not stopped already
        ttpALPauseRx[phy_endpoint_ind] = TRUE;
    }
    else //requested to start again
    {
        DevAssert( (ttpALPauseRx[phy_endpoint_ind] == TRUE )); //make sure it really was stopped before
        ttpALPauseRx[phy_endpoint_ind] = FALSE;

        if(ttpNextRxBuffLen[phy_endpoint_ind])
            USBMgrRxConfirmationExt((USBDevice_EndpointE)phy_endpoint_ind,ttpNextRxBuffLen[phy_endpoint_ind] ,FALSE);
        else
            USBMgrRxConfirmation((USBDevice_EndpointE)phy_endpoint_ind);
    }
}

/************************************************************************
* Function:  USBMgrTTPALEndpointStall
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
void  USBMgrTTPALEndpointStall(Int8 endpointNumber)
{
    USBMgr_RC           usbmgrStatus;
    UINT8               phyEP,usb_mgr_app_id ,usb_mgr_ep_index;
    USBMGR_IF_HANDLER   interfaceHnd;

    if(endpointNumber != 0)
    {
       phyEP = UsbMgrTTPALlogical2PhysicalEP(endpointNumber);

       usb_mgr_app_id = TTPALFindAppIdByEPNumber(phyEP);
       usb_mgr_ep_index = TTPALGetUSBMgrEPIndexByEPNumber(phyEP);

       interfaceHnd = ttpAppsTbl[usb_mgr_app_id];

        usbmgrStatus = USBMgrEndpointStall( interfaceHnd,usb_mgr_ep_index);

        if( (usbmgrStatus != USBMGR_RC_OK))
        {
            ASSERT(0);
        }
    }
}


/************************************************************************
* Function:  UsbAppifStallInEndpoint
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
void  usbAppifStallInEndpoint(Int8 endpointNumber)
{
    USBMgrTTPALEndpointStall(endpointNumber);
}

/************************************************************************
* Function:  UsbAppifStallOutEndpoint
*************************************************************************
* Description:
*
* Parameters:
*
* Return value:
*
* Notes:
************************************************************************/
void  usbAppifStallOutEndpoint(Int8 endpointNumber)
{
    USBMgrTTPALEndpointStall(endpointNumber);
}

/***************************************************************************
 * Function:     usbAppifDynamicSelectionValid
 *
 * Parameters:   conf   Configuration ID to be checked
 *
 * Returns:      Boolean success
 *
 * Description:
 * Checks supplied configuration against the legal set given the build
 * options.
 ***************************************************************************/
extern Boolean usbAppifDynamicSelectionValid( UsbDeviceSelection conf )
{
  Boolean ret = TRUE;

#if defined(USB_DYNAMIC_CONFIGURATION)

  if(
     ( conf >= USB_NUMBER_OF_DYNAMIC_SELECTIONS )
#if !defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
     || ( conf == USB_DYNAMIC_SELECTION_MAST )
     || ( conf == USB_DYNAMIC_SELECTION_C_MAST_MODEM )
     || ( conf == USB_DYNAMIC_SELECTION_C_MAST_MODEM_EMMI )
#endif
#if !defined(USB_TTPCOM_EMMI_INTERFACE)
     || ( conf == USB_DYNAMIC_SELECTION_EMMI )
     || ( conf == USB_DYNAMIC_SELECTION_C_MAST_MODEM_EMMI )
#endif
#if !defined(USB_COMMS_DEVICE_INTERFACE)
     || ( conf == USB_DYNAMIC_SELECTION_MODEM )
     || ( conf == USB_DYNAMIC_SELECTION_C_MAST_MODEM )
     || ( conf == USB_DYNAMIC_SELECTION_C_MAST_MODEM_EMMI )
#endif
#if !defined(USB_INTEL_DIAG_INTERFACE)
     || ( conf == USB_DYNAMIC_SELECTION_DIAG )
#endif
    )
  {
    /* The requested configuration is incompatible with the build options
     * e.g  USB_DYNAMIC_SELECTION_MAST requested without building with
     * USB_MASS_STORAGE_BULK_ONLY_INTERFACE
     *
     * Don't DevFail here, let the caller do so if it desires.
     */
    ret = FALSE;
  }

#endif /*  (USB_DYNAMIC_CONFIGURATION) */

  return ret;

}

/***************************************************************************
 * Function:     usbAppifGetDefaultConfiguration
 *
 * Parameters:   None
 *
 * Returns:      Nothing
 *
 * Description:
 * Determines the power-up default Device selection setting.  This
 * is non-trivial because the set of options available is set by
 * build switches and any one option may not be available.  (e.g. you can't
 * just pick MAST for the default because MAST may not be in the build)
 ***************************************************************************/
extern UsbDeviceSelection usbAppifGetDefaultConfiguration( void )
{
  UsbDeviceSelection defaultSelection = USB_NUMBER_OF_DYNAMIC_SELECTIONS;
                                        /* i.e. invalid */

#if defined (USB_DYNAMIC_CONFIGURATION)

  /* The default is the FIRST one of these that is valid.  If you require a
   * different default - change the order of this code. */

#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
#if defined(USB_COMMS_DEVICE_INTERFACE)
#if defined(USB_TTPCOM_EMMI_INTERFACE)
  if( defaultSelection == USB_NUMBER_OF_DYNAMIC_SELECTIONS )
  { /*
    ** This code will never be run due to the above if statement
    ** It is kept here as a reference another available USB mode
    */
    defaultSelection = USB_DYNAMIC_SELECTION_C_MAST_MODEM_EMMI;
  }
#endif
  if( defaultSelection == USB_NUMBER_OF_DYNAMIC_SELECTIONS )
  {
    defaultSelection = USB_DYNAMIC_SELECTION_C_MAST_MODEM;
  }
#endif
#endif

#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
  if( defaultSelection == USB_NUMBER_OF_DYNAMIC_SELECTIONS )
  {
    defaultSelection = USB_DYNAMIC_SELECTION_MAST;
  }
#endif

#if defined(USB_COMMS_DEVICE_INTERFACE)
  if( defaultSelection == USB_NUMBER_OF_DYNAMIC_SELECTIONS )
  {
    defaultSelection = USB_DYNAMIC_SELECTION_EMMI;
  }
#endif

#if defined(USB_TTPCOM_EMMI_INTERFACE)
  if( defaultSelection == USB_NUMBER_OF_DYNAMIC_SELECTIONS )
  {
    defaultSelection = USB_DYNAMIC_SELECTION_MODEM;
  }
#endif


#if defined(USB_INTEL_DIAG_INTERFACE)
  if( defaultSelection == USB_NUMBER_OF_DYNAMIC_SELECTIONS )
  {
    defaultSelection = USB_DYNAMIC_SELECTION_DIAG;
  }
#endif

  if( defaultSelection == USB_NUMBER_OF_DYNAMIC_SELECTIONS )
  {
    DevFail("No default possible");
  }

#else /* for static builds */

  defaultSelection = (UsbDeviceSelection)(0); /* meaningless */

#endif

  return defaultSelection;
}


/***************************************************************************
 * Function:     usbAppifGetConfiguration
 *
 * Parameters:   response  Configuration-Query table to fill in
 *
 * Returns:      Nothing
 *
 * Description:
 * This fills a UsbConfigQueryStruct with the information relating to the
 * build-time configuration of the USB module - including the options
 * that are selectable via dynamic selection.
 *
 * Applications can get this information by either calling this API function,
 * or by sending SIG_USB_CONFIG_QUERY_REQ and getting SIG_USB_CONFIG_QUERY_CNF
 * in reply with this structure as the payload.  The signal handler calls
 * this function, so the data will be the same.
 ***************************************************************************/
extern void usbAppifGetConfiguration( UsbConfigQueryStruct* response )
{
#if !defined(USB_DYNAMIC_CONFIGURATION)
  {
    /* Static configuration, so this message becomes 'for information only'
     * Describe the one unchangeable configuration according to the build
     * switches. */

    Int8 counter = 0;

    response->numDynamicConfigurations = 1;

#if defined(USB_COMMS_DEVICE_INTERFACE)
    response->config[0].func[counter] = USB_FUNCTION_MODEM;
    counter++;
#endif

#if defined(USB_INTEL_DIAG_INTERFACE)
    response->config[0].func[counter] = USB_FUNCTION_DIAG;
    counter++;
#endif

#if defined(USB_TTPCOM_EMMI_INTERFACE)
    response->config[0].func[counter] = USB_FUNCTION_EMMI;
    counter++;
#endif

#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
    response->config[0].func[counter] = USB_FUNCTION_MAST;
    counter++;
#endif

    response->config[0].numFunctions = counter;
    response->config[0].selectionCode = usbAppifGetDefaultConfiguration();
    response->config[0].isDefault = TRUE;
  }

#else /* This is a Dynamic Configuration */

  {
    /* This code only copes with the 'normal' case of selecting ONE of the
     * available USB functions at any one time.  Should dynamically
     * selectable composites be required then a substantially more complex
     * scheme will be needed */

    Int8 counter = 0;
    UsbDeviceSelection defaultSelect = usbAppifGetDefaultConfiguration();
    Int8 defaultCount = 0;

#if defined(USB_COMMS_DEVICE_INTERFACE)
#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)

    response->config[counter].numFunctions = 2;
    response->config[counter].func[0] = USB_FUNCTION_MODEM;
    response->config[counter].func[1] = USB_FUNCTION_MAST;
    response->config[counter].selectionCode = USB_DYNAMIC_SELECTION_C_MAST_MODEM;
    response->config[counter].isDefault = FALSE;

    if( defaultSelect == USB_DYNAMIC_SELECTION_C_MAST_MODEM )
    {
      response->config[counter].isDefault = TRUE;
      defaultCount++;
    }
    counter++;

#if defined(USB_TTPCOM_EMMI_INTERFACE)
    response->config[counter].numFunctions = 4;
    response->config[counter].func[0] = USB_FUNCTION_MODEM;
    response->config[counter].func[1] = USB_FUNCTION_DIAG;
    response->config[counter].func[2] = USB_FUNCTION_EMMI;
    response->config[counter].func[3] = USB_FUNCTION_MAST;
    response->config[counter].selectionCode = USB_DYNAMIC_SELECTION_C_MAST_MODEM_EMMI;
    response->config[counter].isDefault = FALSE;

    if( defaultSelect == USB_DYNAMIC_SELECTION_C_MAST_MODEM_EMMI )
    {
      response->config[counter].isDefault = TRUE;
      defaultCount++;
    }
    counter++;
#endif
#endif
#endif

#if 0
#if defined(USB_COMMS_DEVICE_INTERFACE)
    response->config[counter].numFunctions = 1;
    response->config[counter].func[0] = USB_FUNCTION_MODEM;
    response->config[counter].selectionCode = USB_DYNAMIC_SELECTION_MODEM;
    response->config[counter].isDefault = FALSE;

    if( defaultSelect == USB_DYNAMIC_SELECTION_MODEM )
    {
      response->config[counter].isDefault = TRUE;
      defaultCount++;
    }
    counter++;
#endif

#if defined(USB_TTPCOM_EMMI_INTERFACE)
    response->config[counter].numFunctions = 1;
    response->config[counter].func[0] = USB_FUNCTION_EMMI;
    response->config[counter].selectionCode = USB_DYNAMIC_SELECTION_EMMI;
    response->config[counter].isDefault = FALSE;

    if( defaultSelect == USB_DYNAMIC_SELECTION_EMMI )
    {
      response->config[counter].isDefault = TRUE;
      defaultCount++;
    }
    counter++;
#endif

#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
    response->config[counter].numFunctions = 1;
    response->config[counter].func[0] = USB_FUNCTION_MAST;
    response->config[counter].selectionCode = USB_DYNAMIC_SELECTION_MAST;
    response->config[counter].isDefault = FALSE;

    if( defaultSelect == USB_DYNAMIC_SELECTION_MAST )
    {
      response->config[counter].isDefault = TRUE;
      defaultCount++;
    }
    counter++;
#endif

#if defined(USB_INTEL_DIAG_INTERFACE)
    response->config[counter].numFunctions = 1;
    response->config[counter].func[0] = USB_FUNCTION_DIAG;
    response->config[counter].selectionCode = USB_DYNAMIC_SELECTION_DIAG;
    response->config[counter].isDefault = FALSE;

    if( defaultSelect == USB_DYNAMIC_SELECTION_DIAG )
    {
      response->config[counter].isDefault = TRUE;
      defaultCount++;
    }
    counter++;
#endif
#endif
    response->numDynamicConfigurations = counter;

    DevAssert( defaultCount == 1 );
  }

#endif /* USB_DYNAMIC_CONFIGURATION */
}

/***************************************************************************
 * Function:     usbAppifSelectDynamicConfiguration
 *
 * Parameters:   newSelection  The configuration to change to
 *
 * Returns:      Nothing
 *
 * Description:  Temporary
 ***************************************************************************/
void usbAppifSelectDynamicConfiguration( UsbDeviceSelection newSelection, TaskId replyTo )
{
  UINT16 nmode = 0;

  switch( newSelection )
  {
  case USB_DYNAMIC_SELECTION_MAST:                 /* Mass Storage */
    nmode =  USBMGR_MAST_APPID;
    break;

  case USB_DYNAMIC_SELECTION_EMMI:                 /* Genie */
    nmode =  USBMGR_GENIE_APPID;
    break;

  case USB_DYNAMIC_SELECTION_MODEM:                /* Modem */
    nmode =  USBMGR_MODEM_APPID;
    break;

  case USB_DYNAMIC_SELECTION_DIAG:                 /* ICAT */
    nmode =  USBMGR_ICAT_APPID;
    break;

  case USB_DYNAMIC_SELECTION_C_MAST_MODEM:           /* Modem + Mass Storage */
    nmode =  USBMGR_MODEM_APPID | USBMGR_MAST_APPID;
    break;

  case USB_DYNAMIC_SELECTION_C_MAST_MODEM_EMMI: /* Modem + Mass Storage + Genie + ICAT */
    nmode =  USBMGR_ICAT_APPID | USBMGR_MODEM_APPID | USBMGR_GENIE_APPID | USBMGR_MAST_APPID;
    break;

  default:
    newSelection = currentUSBConfiguration;
    break;
  }

  currentUSBConfiguration = newSelection;
  //setUSBApplications( &nmode );
}

/***************************************************************************
 * Function:     usbDevAppGetInterfaceNumber
 *
 * Parameters:   interfaceId type of interface
 *
 * Returns:      USB interface number
 *
 * Description:  Obtain interface number for application
 ***************************************************************************/
extern Int8 usbDevAppGetInterfaceNumber( Int8 interfaceId )
{
  switch(currentUSBConfiguration)
  {
  case USB_DYNAMIC_SELECTION_MAST:                 /* Mass Storage */
    if (interfaceId == USB_MAST_INTERFACE)
    {
      return UsbMgrGetIfIndexByAppId(USBMGR_MAST_APPID);
    }
    break;

  case USB_DYNAMIC_SELECTION_EMMI:                 /* Genie */
    if (interfaceId == USB_EMMI_INTERFACE)
    {
      return UsbMgrGetIfIndexByAppId(USBMGR_GENIE_APPID);
    }
    break;

  case USB_DYNAMIC_SELECTION_MODEM:                /* Modem */
    if( (interfaceId == USB_COMM_INTERFACE) ||
        (interfaceId == USB_COMM_DATA_INTERFACE) )
    {
      return UsbMgrGetIfIndexByAppId(USBMGR_MODEM_APPID);
    }
    break;

  case USB_DYNAMIC_SELECTION_C_MAST_MODEM:           /* Modem + Mass Storage */
    if( (interfaceId == USB_COMM_INTERFACE) ||
        (interfaceId == USB_COMM_DATA_INTERFACE) )
    {
      return UsbMgrGetIfIndexByAppId(USBMGR_MODEM_APPID);
    }
    else if (interfaceId == USB_MAST_INTERFACE)
    {
      return UsbMgrGetIfIndexByAppId(USBMGR_MAST_APPID);
    }
    break;

  case USB_DYNAMIC_SELECTION_C_MAST_MODEM_EMMI: /* Modem + Mass Storage + Genie + ICAT */
    if( (interfaceId == USB_COMM_INTERFACE) ||
        (interfaceId == USB_COMM_DATA_INTERFACE) )
    {
      return( 0 );
    }
    else if (interfaceId == USB_EMMI_INTERFACE)
    {
      return UsbMgrGetIfIndexByAppId(USBMGR_GENIE_APPID);
    }
    else if (interfaceId == USB_MAST_INTERFACE)
    {
      return UsbMgrGetIfIndexByAppId(USBMGR_MAST_APPID);
    }
    break;
  }

  /* Unknown interface ID for the current configuration */
  DevParam(interfaceId,currentUSBConfiguration,0);

  return 0;
}

/***************************************************************************
 * Function:     usbDclControlTransferStatusStage
 *
 * Parameters:   logicalEndpoint - assuming it is zero, Control only on zero
 *
 * Returns:      void
 *
 * Description:  send empty ACK on EP0
 ***************************************************************************/
//needed for workaround of EP0 2packets problem in modem
UINT32 VD_RSP__CNT=0;
extern void usbDclControlTransferStatusStage(Int8 logicalEndpoint)
{//alla

    if ( usbDriverNeedSetupStatusTxZlp != FALSE )
    {/* Explicitly transmit a ZLP */
        USBMgrSetupCommandRsp(NULL, 0);
    }
    /*if(VD_RSP__CNT==0) //currently disabling enumeration
    {
        ASSERT(usbMgrStatus_notify == USBMGR_INTERFACE_ACTIVE);
        UsbMgrTTPALConfigure( );
    }
    VD_RSP__CNT++;
   */

    return;
}

/***************************************************************************
 * Function:     usbStackStallEndpointAddress
 *
 * Parameters:
 *
 * Returns:      void
 *
 * Description:
 ***************************************************************************/
extern void usbStackStallEndpointAddress( Int8 endpointAddress )
{
    ASSERT(0);//not supported
}

/***************************************************************************
 * Function:     usbNotifyError
 *
 * Parameters:
 *
 * Returns:      void
 *
 * Description:
 ***************************************************************************/
extern void usbNotifyError(UsbErrorCode errorCode, Boolean isISR)
{
    return; // stub
}

/***************************************************************************
 * Function:     usbHandleError
 *
 * Parameters:
 *
 * Returns:      void
 *
 * Description:
 ***************************************************************************/
extern void usbHandleError(UsbErrorCode errorCode)
{
    return; // stub
}

/***************************************************************************
 * Function:     UsbMgrTTPALlogical2PhysicalEP
 *
 * Parameters:   int logicalEP - as defined in the enum from usbinc.h
 *
 * Returns:      physical endpoint number
 *
 * Description:
 ***************************************************************************/
int UsbMgrTTPALlogical2PhysicalEP(int logicalEP )
{
  if (logicalEP == 0)
    return 0;

  switch(logicalEP)
  {
#if defined(USB_TTPCOM_EMMI_INTERFACE)
  case USB_EMMI_IN_ENDPOINT:
      return USB_EMMI_IN_ENDPOINT_PHY;

  case USB_EMMI_OUT_ENDPOINT:
        return USB_EMMI_OUT_ENDPOINT_PHY;

#endif // USB_TTPCOM_EMMI_INTERFACE
#if defined(USB_COMMS_DEVICE_INTERFACE)
  case USB_COMM_CTRL_IN_ENDPOINT:
      return (USB_COMM_CTRL_IN_ENDPOINT_PHY);

  case USB_COMM_DATA_IN_ENDPOINT:
      return(USB_COMM_DATA_IN_ENDPOINT_PHY);

  case USB_COMM_DATA_OUT_ENDPOINT:
      return(USB_COMM_DATA_OUT_ENDPOINT_PHY);

#endif // USB_COMMS_DEVICE_INTERFACE
#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
  case USB_MAST_IN_ENDPOINT:
      return (USB_MAST_IN_ENDPOINT_PHY);

  case USB_MAST_OUT_ENDPOINT:
      return(USB_MAST_OUT_ENDPOINT_PHY);

#endif // USB_MASS_STORAGE_BULK_ONLY_INTERFACE
  default:
      ASSERT(0);//arrived here means received wrong logical point number
  };
/*
** Return the logical endpoint to ensure something other than rogue data
** on the stack gets returned.
*/
  return logicalEP;
}

/***************************************************************************
 * Function:     UsbMgrTTPALPhysical2logicalEP
 *
 * Parameters:   int phyEP - physical endpoint number
 *
 * Returns:      logical endpoint number as defined in the enum from usbinc.h
 *
 * Description:
 ***************************************************************************/
int UsbMgrTTPALPhysical2logicalEP(int phyEP)
{
    if (phyEP == 0)
        return 0;

    switch(phyEP)
    {
#if defined(USB_TTPCOM_EMMI_INTERFACE)
    case USB_EMMI_IN_ENDPOINT_PHY:
        return (USB_EMMI_IN_ENDPOINT);

    case USB_EMMI_OUT_ENDPOINT_PHY:
        return (USB_EMMI_OUT_ENDPOINT);

#endif // USB_TTPCOM_EMMI_INTERFACE
#if defined(USB_COMMS_DEVICE_INTERFACE)
    case USB_COMM_CTRL_IN_ENDPOINT_PHY:
        return (USB_COMM_CTRL_IN_ENDPOINT);

    case USB_COMM_DATA_IN_ENDPOINT_PHY:
        return(USB_COMM_DATA_IN_ENDPOINT);

    case USB_COMM_DATA_OUT_ENDPOINT_PHY:
        return(USB_COMM_DATA_OUT_ENDPOINT);

#endif // USB_COMMS_DEVICE_INTERFACE
#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
    case USB_MAST_IN_ENDPOINT_PHY:
        return (USB_MAST_IN_ENDPOINT);

    case USB_MAST_OUT_ENDPOINT_PHY:
        return(USB_MAST_OUT_ENDPOINT);

#endif // USB_MASS_STORAGE_BULK_ONLY_INTERFACE
    default:
      ASSERT(0);//arrived here means received wrong physical point number
    };
/*
** Return the physical endpoint to ensure something other than rogue data
** on the stack gets returned.
*/
    return phyEP;

}
#if 0
QueueId cfUsbAlQueueId = USB_TARGET_QUEUE_ID;

KI_SINGLE_TASK (usbTargetTask, cfUsbAlQueueId, USB_TARGET_TASK_ID)
#endif
#if defined(USB_DYNAMIC_CONFIGURATION)
/***************************************************************************
 * Function:     usbHandleNewConfigurationRequest
 *
 * Parameters:   newSelection  The configuration to change to
 *               replyTo       The Task to send the CNF back to
 *
 * Returns:      Nothing
 *
 * Description:
 * Select the new dynamic composite
 ***************************************************************************/
static void usbHandleNewConfigurationRequest( UsbDeviceSelection newSelection,
                                               TaskId replyTo )
{
  SignalBuffer signal = kiNullBuffer;

  if( usbAppifDynamicSelectionValid( newSelection ) )
  {
    /* Send CNF back */
    KiCreateSignal(SIG_USB_DYNAMIC_CONFIGURE_CNF,
                   sizeof(UsbDynamicConfigureCnf),
                   &signal);
    signal.sig->usbDynamicConfigureCnf.deviceSelectionOk = TRUE;
    KiSendSignal(replyTo, &signal);
    /* Change USB configuration */
    usbAppifSelectDynamicConfiguration( newSelection, replyTo );
  }
  else
  {
    /* Send CNF back with error flag */
    KiCreateSignal(SIG_USB_DYNAMIC_CONFIGURE_CNF,
                   sizeof(UsbDynamicConfigureCnf),
                   &signal);
    signal.sig->usbDynamicConfigureCnf.deviceSelectionOk = FALSE;
    KiSendSignal(replyTo, &signal);
  }
}
#endif /* defined(USB_DYNAMIC_CONFIGURATION) */

/***************************************************************************
 * Function:     usbHandleConfigurationQuery
 *
 * Parameters:   replyTo       The Task to send the CNF back to
 *
 * Returns:      Nothing
 *
 * Description:
 * Send the USB Build configuration back to the Sender
 ***************************************************************************/
static void usbHandleConfigurationQuery( TaskId replyTo )
{
  SignalBuffer signal = kiNullBuffer;

  KiCreateSignal(SIG_USB_CONFIG_QUERY_CNF, sizeof(UsbConfigQueryCnf), &signal);

  usbAppifGetConfiguration( &(signal.sig->usbConfigQueryCnf.response) );

  KiSendSignal(replyTo, &signal);
}


/***************************************************************************
 * Function:     usbTargetTask
 *
 * Parameters:   none
 *
 * Returns:      Nothing
 *
 * Description:
 * USB Target task signal handler
 ***************************************************************************/
KI_ENTRY_POINT
usbTargetTask(void)
{
  #if 0
  SignalBuffer signal = kiNullBuffer;

  /* Now loop forever, processing signals sent to the USB AL task queue. */
  while (TRUE)
  {
    KiReceiveSignal(cfUsbAlQueueId, &signal);

    /* Process the signal. */
    switch(*(signal.type))
    {
     case SIG_USB_TRANSMIT_COMPLETE_IND:
#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
      usbMastStateMachineTxInd();
#endif
      break;

     case SIG_USB_CLASS_DEVICE_REQUEST_IND:
        UsbMgrTTPALSetupIndicationFromTask(&(signal.sig->usbClassDeviceRequestInd));
      break;

#if defined(USB_DYNAMIC_CONFIGURATION)
  /* Some external entity (MMI?) is requesting a new Dynamic Configuration */
  case SIG_USB_DYNAMIC_CONFIGURE_REQ:
    usbHandleNewConfigurationRequest(
                signal.sig->usbDynamicConfigureReq.newDeviceSelection,
                signal.sig->usbDynamicConfigureReq.sender );
    break;

  /* The USB stack confirming receipt of configure request */
  case SIG_USB_DYNAMIC_CONFIGURE_CNF:
    /* Not doing anything with this currently */
    break;
#endif /* defined(USB_DYNAMIC_CONFIGURATION) */
  case SIG_USB_CONFIG_QUERY_REQ:
    usbHandleConfigurationQuery( signal.sig->usbConfigQueryReq.sender );
    break;

    case SIG_USB_CABLE_STATE_CHANGE_IND:
#if defined( _FDI_VER_71_ )
      if( signal.sig->usbDclUsbCableStateChangeInd.usbCableInserted )
      {
        /* Mount the MAST USB drive */
        MUSB_MountDrive();
      }
      else
      {
        MUSB_UnmountDrive();

      }
#endif
      break;
    default:
      break;
    }

    KiDestroySignal(&signal);
  }
  #endif
}

extern void usbDclEnableEndpointZeroEvents( void )
{
}
#endif

/***************************************************************************
 * Function:     USBMgrTTPALUpdateEnabledApps
 *
 * Parameters:   mask_app - each bit set indicates application is enabled
 *
 * Returns:
 *
 * Description:  bit numbers are according applications IDs
 ***************************************************************************/
extern void USBMgrTTPALUpdateEnabledApps(UINT32 mask_app, UINT8 card)
{
#if defined(UPGRADE_USB)
  TTPAL_ative_applications_mask = mask_app;
  use_card_as_mast = (card == 1 ? TRUE : FALSE);
#endif
}

#if defined(UPGRADE_USB)
/***************************************************************************
 * Function:     USBMgrTTPALSwapFSDrives
 *
 * Parameters:
 *
 * Returns:      void
 *
 * Description:  swaps drives of MAST (Card/Flash) if user asked for it
 ***************************************************************************/
#if defined( UPGRADE_MMC )
extern  BOOL    mmcsdCardInserted;

void USBMgrTTPALSwapFSDrives(usbScsiFsDevice* drive1, usbScsiFsDevice* drive2)
{
    usbScsiFsDevice tmp;
    if (use_card_as_mast && mmcsdCardInserted)
    {
        memcpy(&tmp,        drive1,     sizeof(usbScsiFsDevice));
        memcpy(drive1,      drive2,     sizeof(usbScsiFsDevice));
        memcpy(drive2,      &tmp,       sizeof(usbScsiFsDevice));
    }
}
#endif /* UPGRADE_MMC */
#endif

/***************************************************************************
 * Function:     UsbMgrTTPALSetMuxUART
 *
 * Parameters:
 *
 * Returns:      void
 *
 * Description:  Is called from outside to set the Mux to UART
 ***************************************************************************/
extern void UsbMgrTTPALSetMuxUART(void)
{
#if 0
#if defined(UPGRADE_USB)
#if defined(USB_COMMS_DEVICE_INTERFACE)
    SignalBuffer signal = kiNullBuffer;

    /* switch the mux */
    KiCreateIntSignal (SIG_APEX_MUX_SELECT_REQ, sizeof(ApexMuxSelectReq), &signal);
    signal.sig->apexMuxSelectReq.sender      = TASK_FL_ID;
//MR - NOTICE!!! If need to work with nullmux (and not nullmuxnopl) then changes
//   should be made in modemhermon.inc (under flag: TINI_MODEL), and next line
//   will have: VG_MUX_NULL
    signal.sig->apexMuxSelectReq.multiplexer = VG_MUX_NULL_NOPL;
////
    KiSendIntSignal (VG_CI_TASK_ID, &signal);
#endif
#endif
#endif
}

/***************************************************************************
 * Function:     UsbMgrTTPALSetMuxUSB
 *
 * Parameters:
 *
 * Returns:      void
 *
 * Description:  Is called from outside to set the Mux to USB
 ***************************************************************************/
extern void UsbMgrTTPALSetMuxUSB(void)
{
#if 0
#if defined(UPGRADE_USB)
#if defined(USB_COMMS_DEVICE_INTERFACE)
    SignalBuffer signal = kiNullBuffer;

    /* switch the mux */
    KiCreateIntSignal (SIG_APEX_MUX_SELECT_REQ, sizeof(ApexMuxSelectReq), &signal);
    signal.sig->apexMuxSelectReq.sender      = TASK_FL_ID;
    signal.sig->apexMuxSelectReq.multiplexer = USB_NULL_MUX;
    KiSendIntSignal (VG_CI_TASK_ID, &signal);
#endif
#endif
#endif
}

/***************************************************************************
 * Function:     UsbMgrTTPALSetMuxUART_INT
 *
 * Parameters:
 *
 * Returns:      void
 *
 * Description:
 ***************************************************************************/
extern void UsbMgrTTPALSetMuxUART_INT(void)
{
#if 0
#if defined(UPGRADE_USB)
#if defined(USB_COMMS_DEVICE_INTERFACE)
    SignalBuffer signal = kiNullBuffer;

    /* switch the mux */
    KiCreateIntSignal (SIG_APEX_MUX_SELECT_REQ, sizeof(ApexMuxSelectReq), &signal);
    signal.sig->apexMuxSelectReq.sender      = TASK_FL_ID;
//MR - NOTICE!!! If need to work with nullmux (and not nullmuxnopl) then changes
//   should be made in modemhermon.inc (under flag: TINI_MODEL), and next line
//   will have: VG_MUX_NULL
    signal.sig->apexMuxSelectReq.multiplexer = VG_MUX_NULL_NOPL;
    KiSendIntSignal (VG_CI_TASK_ID, &signal);
#endif
#endif
#endif
}

/***************************************************************************
 * Function:     UsbMgrTTPALSetMuxUSB
 *
 * Parameters:
 *
 * Returns:      void
 *
 * Description:  Is called from outside to set the Mux to USB
 ***************************************************************************/
extern void UsbMgrTTPALSetMuxUSB_INT(void)
{
#if 0
#if defined(UPGRADE_USB)
#if defined(USB_COMMS_DEVICE_INTERFACE)
    SignalBuffer signal = kiNullBuffer;

    /* switch the mux */
    KiCreateIntSignal (SIG_APEX_MUX_SELECT_REQ, sizeof(ApexMuxSelectReq), &signal);
    signal.sig->apexMuxSelectReq.sender      = TASK_FL_ID;
    signal.sig->apexMuxSelectReq.multiplexer = USB_NULL_MUX;
    KiSendIntSignal (VG_CI_TASK_ID, &signal);
#endif
#endif
#endif
}


/***************************************************************************
 * Function:     UsbMgrTTPALInit
 *
 * Parameters:
 *
 * Returns:      void
 *
 * Description:  Is called from outside to init ttpal module
 ***************************************************************************/
void UsbMgrTTPALInit(void)
{
#if defined(UPGRADE_USB)
    UsbMgrTTPALInitGblPrms();

    UsbMgrTTPALAppInitialise();

#if defined(USB_TTPCOM_EMMI_INTERFACE)
    UsbMgrTTPALRegister( USBMGR_GENIE_APPID);
#endif

#if defined(USB_COMMS_DEVICE_INTERFACE)
    UsbMgrTTPALRegister( USBMGR_MODEM_APPID);
#endif
#if defined(USB_MASS_STORAGE_BULK_ONLY_INTERFACE)
    UsbMgrTTPALRegister( USBMGR_MAST_APPID);
#endif
#endif
}
