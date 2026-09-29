/******************************************************************************************************************************
*              MODULE IMPLEMENTATION FILE
******************************************************************************************************************************
*  COPYRIGHT (C) 2019 ASR Corporation.
*
*  This file and the software in it is furnished under
*  license and may only be used or copied in accordance with the terms of the
*  license. The information in this file is furnished for informational use
*  only, is subject to change without notice, and should not be construed as
*  a commitment by ASR Corporation. ASR Corporation assumes no
*  responsibility or liability for any errors or inaccuracies that may appear
*  in this document or any software that may be provided in association with
*  this document.
*  Except as permitted by such license, no part of this document may be
*  reproduced, stored in a retrieval system, or transmitted in any form or by
*  any means without the express written consent of ASR Corporation.
*
*  Title:   HTTP Package HTTP API
*
*  Filename:    http_api.h
**
*  Description: This file includes all the API that the http Package support
*
*  Last Modified: <Initial> <date>
*
*  Notes:
*********************************************************************************************************************************/
#ifndef __MBTK_NTP_API_H__
#define __MBTK_NTP_API_H__

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ntp_set_host_name
 * DESCRIPTION 
 *          This API is use to ntp set hostname. 
 * PARAMETERS 
 *        host_name    [IN]: host_name
 * RETURN VALUES
 *         0: successful
 *         other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ntp_set_host_name(char * host_name); /* int mbtk_ck_set_ntp_host_name(char * host_name) */

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ntp_get_host_name
 * DESCRIPTION 
 *          This API is use to ntp get hostname. 
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *         NULL: fail
 *         other: host_name
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern char * ol_ntp_get_host_name(void);          /* char * mbtk_ck_get_ntp_host_name(void) */

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ntp_get_status
 * DESCRIPTION 
 *          This API is use to ntp get status. 
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *         0 || 1: successful
 *         other: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ntp_get_status(void);                /* int mbtk_ck_get_ntp_status(void) */

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ntp_sync_time
 * DESCRIPTION 
 *          This API is use to ntp sync time. 
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *         NULL
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_ntp_sync_time(void);                /* void mbtk_ck_sync_ntp_time(void) */

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ntp_get_utc_time
 * DESCRIPTION 
 *          This API is use to ntp get utc time. 
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *         utc time
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern unsigned long ol_ntp_get_utc_time(void);     /* unsigned int mbtk_ck_get_ntp_utc_time(void) */

#ifdef __cplusplus
}
#endif

#endif
