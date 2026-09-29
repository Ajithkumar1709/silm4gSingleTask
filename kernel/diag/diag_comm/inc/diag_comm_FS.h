#ifndef _DIAGCOMMFS_H_
#define _DIAGCOMMFS_H_
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                diag_comm_FS.h


GENERAL DESCRIPTION

    This file is for diag communication log.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS

   Copyright (c) 2011 by Marvell, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who        what, where, why
--------   ------     ----------------------------------------------------------
07/25/2013   zhoujin    Created module
===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "osa.h"
#include "diag.h"
#include "UART.h"
#include <stdlib.h>
#include <string.h>
#include "platform.h"

/*===========================================================================

                                LOCAL MACRO
===========================================================================*/

/* Diag comm sd log length. */
#define DIAG_COMM_LOG_LENGTH                        0x00020000

/* Diag comm sd initialize flag. */
#define DIAG_COMM_LOG_INIT_DONE                     0xEBEDBEDE

/* Diag comm sd rotation flag. */
#define DIAG_COMM_LOG_ROTATION_FLAG                 0xDEAFBEEF

/*===========================================================================

                          Struct definition.

===========================================================================*/

/* Diag comm FS transfer flag */
typedef enum diagFsTransferFlag
{
    DIAG_FS_TRANSFER_NONE,
    DIAG_FS_TRANSFER_START,
	DIAG_FS_TRANSFER_DONE
}diagFsTransferFlag;


/* Diag comm FS result code */
typedef enum diagCommFsResultCode
{
    DIAG_COMM_FS_OK,
    DIAG_COMM_FS_DISABLE,
	DIAG_COMM_FS_NOT_INIT,
	DIAG_COMM_FS_INVALID_NAME,
	DIAG_COMM_FS_ALREADY_INIT,
	DIAG_COMM_FS_NULL_POINTER,
	DIAG_COMM_FS_NO_FREE_SPACE,
	DIAG_COMM_FS_INVALID_LENGTH,
	DIAG_COMM_FS_INVALID_BUFFER,
	DIAG_COMM_FS_INVALID_FILE,
	DIAG_COMM_FS_WRITE_ERROR,
	DIAG_COMM_FS_OTHER_ERROR
}diagCommFsResultCode;

/* Diag comm log information */
typedef struct diagCommLogInfo{
	UINT32      Log_Begin;
	UINT32      Log_Index;
	UINT32      Rota_Flag;
	UINT32      Init_Flag;
	UINT32      Trsf_Flag;
	UINT32      Index_Rcd;
	UINT32      Rota_Rcd;
	char       *Log_Name;
}diagCommLogInfo;

/*===========================================================================

            EXTERN DECLARATIONS FOR MODULE

===========================================================================*/


/*===========================================================================

                        EXTERN FUNCTION DECLARATIONS

===========================================================================*/
/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      send_data_2uart                                                  */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      This function send data to uart.                                 */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      size                                Memory size                  */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
extern void send_data_2uart(UINT8 *bufPtr, UINT32 length);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      fdi_sem_lock                                                     */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function lock FAT system mutex.                              */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
extern void fdi_sem_lock(void);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      fdi_sem_unlock                                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function unlock FAT system mutex.                            */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
extern void fdi_sem_unlock(void);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      fatCARD_ReadBytesFree                                            */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function get the number of free space of FAT system.         */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
extern long fatCARD_ReadBytesFree(void);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      diagCommUsbLogEnable                                             */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function check whether usb logging is enbale or not.         */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
extern BOOL diagCommUsbLogEnable(void);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      diagCommLogDisable                                               */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function disbale diag comm log.                              */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
extern void diagCommLogDisable(void);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      diagCommSdLogEnable                                              */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function check whether the Diag SD logging is enable or not. */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
extern BOOL diagCommSdLogEnable(void);

/*===========================================================================

                          INTERNAL FUNCTION DECLARATIONS

===========================================================================*/
/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      DiagCommFsMutexInit                                              */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function initialize the diag FS log mutex.                   */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void DiagCommFsMutexInit(void);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      DiagCommFsMutexLock                                              */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function lock the diag FS log mutex.                         */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void DiagCommFsMutexLock(void);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      DiagCommFsMutexUnlock                                            */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function unlock the diag FS log mutex.                       */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void DiagCommFsMutexUnlock(void);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      diagCommFsInit                                                   */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function initialize the diag FS communication.               */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      Result                              Result code                  */
/*                                                                       */
/*************************************************************************/
diagCommFsResultCode diagCommFsInit(void);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      diagCommFsUninit                                                 */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function uninitialize the diag FS communication.             */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      Result                              Result code                  */
/*                                                                       */
/*************************************************************************/
diagCommFsResultCode diagCommFsUninit(void);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      diagCommFsLogEnable                                              */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function check whether FS logging is enbale or not.          */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
BOOL diagCommFsLogEnable(void);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      diagCommFsLogSaveStatus                                          */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function get fs logging save status.                         */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
BOOL diagCommFsLogSaveStatus(void);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      diagCommGetLogInfo                                               */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function get the diag log information.                       */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
diagCommLogInfo *diagCommGetLogInfo(void);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      diagCommSaveLogToBuffer                                          */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function save the diag lod to buffer.                        */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      Data                                Diag message                 */
/*      Length                              Message length               */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void diagCommSaveLogToBuffer(char* data, unsigned int length);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      diagCommSaveLogToFs                                              */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function save the diag log to FS.                            */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      Name                                Log name                     */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      Result                              Result code                  */
/*                                                                       */
/*************************************************************************/
diagCommFsResultCode diagCommSaveLogToFs(char *name);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      diagCommSendLogToUart                                            */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function send the diag log to uart.                          */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      Result                              Result code                  */
/*                                                                       */
/*************************************************************************/
diagCommFsResultCode diagCommSendLogToUart(void);

#endif
