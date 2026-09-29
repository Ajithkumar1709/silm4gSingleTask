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
#ifndef __MBTK_FTP_API_H__
#define __MBTK_FTP_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MBTK_FTP_MAX_HOST_LEN 100
#define MBTK_FTP_MAX_NAME_LEN 30
#define MBTK_FTP_MAX_PASSWD_LEN 40

#define ftpErrno ol_ftp_get_errno()

typedef struct {
    CHAR host[MBTK_FTP_MAX_HOST_LEN];
    UINT16 port;
    CHAR username[MBTK_FTP_MAX_NAME_LEN];
    CHAR password[MBTK_FTP_MAX_PASSWD_LEN];
    UINT8 mode;      /*0: passive mode, 1: proactive mode*/
    UINT8 timeout;   /*5-180s, default 30s*/
    UINT8 ftpType;   /*0: binary mode, 1: ascii mode*/
    UINT8 ssl_mode;  /* Security Mode: 0:None  1:implict   2:explict */
    UINT8 cert;      /* Whether to ignore a certificate,Default is 0 */
    UINT8 isipv6;
}mbtk_open_ftp_config_params_t;

enum MBTK_FTP_error_num
{
    MBTK_FTP_OK = 0,
    MBTK_UNKNOW_ERROR_FOR_FTP = 201,             //201
    MBTK_FTP_TASK_IS_BUSY,                       //202
    MBTK_FAILED_TO_RESOLVE_SERVER_ADDRESS,       //203
    MBTK_FTP_TIMEOUT,                            //204
    MBTK_FAILED_TO_READ_FILE,                    //205
    MBTK_FAILED_TO_WRITE_FILE,                   //206
    MBTK_NOT_ALLOWED_IN_CURRENT_STATE,           //207
    MBTK_FAILED_TO_LOGIN,                        //208
    MBTK_FAILED_TO_LOGOUT,                       //209
    MBTK_FAILED_TO_TRANSFER_DATA = 210,          //210
    MBTK_FTP_COMMAND_REJECTED_BY_SERVER,         //211
    MBTK_MEMORY_ERROR,                           //212
    MBTK_INAVLID_PARAMETER,                      //213
    MBTK_NETWORK_ERROR,                          //214
    MBTK_FAILED_TO_CONNECT_SOCKET,               //215
    MBTK_FAILED_TO_SEND_DATA_USING_SOCKET,       //216
    MBTK_FAILED_TO_RECEVICE_DATA_USING_SOCKET,   //217
    MBTK_FAILED_TOVERIFY_USER_NAME_AND_PASSWORD, //218
    MBTK_SOCKET_CONNECT_TIMEOUT,                 //219
    MBTK_FILE_DOES_NOT_EXIST,                    //220
};


/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ftp_mkdir
 * DESCRIPTION 
 *          This API is to mkdir by ftp. 
 * PARAMETERS 
 *        dir      [IN]: dir
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ftp_mkdir(char *dir);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ftp_mkdir
 * DESCRIPTION 
 *          This API is to rmdir by ftp. 
 * PARAMETERS 
 *        dir[IN]: dir
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ftp_rmdir(char *dir);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ftp_delete
 * DESCRIPTION 
 *          This API is to delect file by ftp. 
 * PARAMETERS 
 *        file[IN]: file
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ftp_delete(char *file);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ftp_size
 * DESCRIPTION 
 *          This API is to get file size by ftp. 
 * PARAMETERS 
 *        remote_file[IN]: remote_file
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ftp_size ( char* remote_file );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ftp_list
 * DESCRIPTION 
 *          This API is to get file list by ftp. 
 * PARAMETERS 
 *        dir[IN]: dir
 *        p_list[IN]: p_list
 *        p_list_len[IN]: p_list_len
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ftp_list( char *dir , char ** p_list, unsigned long * p_list_len);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ftp_getfile
 * DESCRIPTION 
 *          This API is to get file by ftp. 
 * PARAMETERS 
 *        remote_file[IN]: remote_file
 *        local_file[IN]: local_file
 *        rest[IN]: result
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ftp_getfile(char *remote_file, char *local_file, int rest);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ftp_putfile
 * DESCRIPTION 
 *          This API is to put file by ftp. 
 * PARAMETERS 
 *        remote_file[IN]: remote_file
 *        local_file[IN]: local_file
 *        rest[IN]: result
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ftp_putfile( char *remote_file, char *local_file, int rest );
/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ftp_get_current_dir
 * DESCRIPTION 
 *          This API is to get remote current dir. 
 * PARAMETERS 
 *        file_path[IN]: file_path
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ftp_get_current_dir(char *file_path);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ftp_get_errno
 * DESCRIPTION 
 *          This API is to get ftp Errno. 
 * PARAMETERS 
 *          NONE
 * RETURN VALUES
 *          Errno
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ftp_get_errno(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ftp_setparams
 * DESCRIPTION 
 *          This API is to set params. 
 * PARAMETERS 
 *        config_params[IN]: config_params, see enum mbtk_open_ftp_config_params_t
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ftp_setparams ( mbtk_open_ftp_config_params_t* config_params );

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ftp_getparams
 * DESCRIPTION 
 *          This API is to get params. 
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *        config_params[OUT]: config_params, see enum mbtk_open_ftp_config_params_t
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_open_ftp_config_params_t* ol_ftp_getparams ( void );

#ifdef __cplusplus
}
#endif

#endif
