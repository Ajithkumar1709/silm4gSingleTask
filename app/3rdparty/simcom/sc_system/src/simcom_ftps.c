#include <string.h>
#include "simcom_ftps.h"
#include "simcom_os.h"
#include "mbtk_err.h"
#include "ftp_api.h"
#include "mbtk_os.h"


#define SC_ftpErrno mbtk_ftp_errno_parse()

mbtk_open_ftp_config_params_t config_params = {0};

mbtk_taskref MBTK_Ftp_taskRef = NULL;
mbtk_msgqref MBTK_Ftp_msgQRef = NULL;

sMsgQRef SC_Ftp_msgQRef = NULL;

static int mbtk_ftp_errno_parse(void)
{
    switch(ftpErrno)
    {
        case MBTK_FTP_OK:
            return SC_FTPS_RESULT_OK;

        case MBTK_FAILED_TO_READ_FILE:
        case MBTK_FAILED_TO_WRITE_FILE:
        case MBTK_FAILED_TO_SEND_DATA_USING_SOCKET:
        case MBTK_FAILED_TO_RECEVICE_DATA_USING_SOCKET:
            return SC_FTPS_RESULT_ERROR_TRANSFER_FAILED;

        case MBTK_FAILED_TO_LOGIN:
        case MBTK_FAILED_TO_CONNECT_SOCKET:
        case MBTK_FAILED_TOVERIFY_USER_NAME_AND_PASSWORD:
            return SC_FTPS_RESULT_FAILED_TO_CONNECT_SOCKET;

        case MBTK_NOT_ALLOWED_IN_CURRENT_STATE:
            return SC_FTPS_RESULT_STATE_ERROR;
        case MBTK_MEMORY_ERROR:
            return SC_FTPS_RESULT_ERROR_MEMORY_ERROR;

        case MBTK_INAVLID_PARAMETER:
            return SC_FTPS_RESULT_ERROR_INVALID_PARAM;

        case MBTK_FILE_DOES_NOT_EXIST:
            return SC_FTPS_RESULT_ERROR_FILE_ERROR;

    }
    return SC_FTPS_RESULT_UNKNOWN_ERROR;
}


static void mbtk_ftp_thread(void *param)
{
    SIM_MSG_T ftpsMsg = {0, 0, 0, NULL};
    unsigned int ftpsMsg_addr = 0;
    mbtk_ftp_msg_t *ftpmsg = NULL;
    BOOL opt_err = FALSE;

    while(1)
    {
        ol_os_msgq_recv(MBTK_Ftp_msgQRef, &ftpsMsg_addr, sizeof(unsigned int), MBTK_OS_SUSPEND);
        ftpmsg = (mbtk_ftp_msg_t *)ftpsMsg_addr;
        memset(&ftpsMsg, 0x0, sizeof(SIM_MSG_T));
        switch(ftpmsg->msgid)
        {
            case FtpsInit:
            {
                break;
            }
            case FtpsDeInit:
            {
                ol_os_msgq_delete(MBTK_Ftp_msgQRef);
                sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
                MBTK_Ftp_msgQRef = NULL;
                ol_os_task_delete(MBTK_Ftp_taskRef);
                break;
            }
            case FtpsLogin:
            {
                SCftpsLoginMsg *login_msg = ftpmsg->param;
                    
                memset(&config_params,0,sizeof(mbtk_open_ftp_config_params_t));
                memcpy(config_params.host, login_msg->host,strlen(login_msg->host));
                memcpy(config_params.username, login_msg->username,strlen(login_msg->username));
                memcpy(config_params.password, login_msg->password,strlen(login_msg->password));
                
                config_params.port = login_msg->port;
                switch(login_msg->serverType)
                {
                    case 0:
                        config_params.ssl_mode = 0;
                        break;
                    case 1:
                    case 2:
                        config_params.ssl_mode = 2;
                        break;
                    case 3:
                        config_params.ssl_mode = 1;
                        break;
                    default:
                        config_params.ssl_mode = 0;
                }
                
                free(login_msg);
                if(ol_ftp_setparams(&config_params) != 0)
                {
                    opt_err = TRUE;
                    break;
                }
                break;
            }
            case FtpsLogout:
            {
                memset(&config_params,0,sizeof(mbtk_open_ftp_config_params_t));
                if(ol_ftp_setparams(&config_params) != 0)
                {
                    opt_err = TRUE;
                }
                
                break;
            }
            case FtpsDownloadFile:
            {
                break;
            }
            case FtpsDownloadFileToBuffer:
            {
                break;
            }
            case FtpsUploadFile:
            {
                mbtk_ftp_transfer_t *ftp_transfer = (mbtk_ftp_transfer_t *)ftpmsg->param;
                char *fileName = ftp_transfer->arg2;
                int startPos = ftp_transfer->arg1;
                
                if(ol_ftp_putfile(fileName, fileName, startPos) != 0)
                    opt_err = TRUE;
                
                free(ftp_transfer);
                break;
            }
            case FtpsDeleteFile:
            {
                break;
            }
            case FtpsCreateDirectory:
            {
                break;
            }
            case FtpsDeleteDirectory:
            {
                break;
            }
            case FtpsChangeDirectory:
            {
                break;
            }
            case FtpsGetCurrentDirectory:
            {
                char mbtk_file_path[255] = {0};
                
                if(ol_ftp_get_current_dir(mbtk_file_path) != 0)
                {
                    opt_err = TRUE;
                    break;
                }
                
                ftpsMsg.arg3 = mbtk_file_path;
                break;
            }
            case FtpsList:
            {
                mbtk_ftp_transfer_t *ftp_transfer = (mbtk_ftp_transfer_t *)ftpmsg->param;
                char *dir = ftp_transfer->arg2;
                char *list = NULL;
                unsigned long list_len = 0;
                if(ol_ftp_list(dir, &list, &list_len) != 0)
                {
                    opt_err = TRUE;
                    free(ftp_transfer);
                    break;
                }
                SCapiFtpsData *ftpsData  = NULL;
                
                char *start = list;
                char *end = strchr(start, '\n');
                while (end != NULL)
                {
                    ftpsData  = malloc(sizeof(SCapiFtpsData));
                    memset(ftpsData, 0x0, sizeof(SCapiFtpsData));
                    
                    ftpsData->flag = SC_DATA_RESUME;
                    ftpsData->len = end - start + 1;
                    
                    ftpsData->data = malloc(ftpsData->len + 1);
                    memset(ftpsData->data, 0x0, ftpsData->len + 1);
                    memcpy(ftpsData->data, start, ftpsData->len);
                    
                    ftpsMsg.arg3 = ftpsData;
                    sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
                    start = end + 1;
                    end = strchr(start, '\n');

                    ol_os_task_sleep(5);
                }
                ftpsData  = malloc(sizeof(SCapiFtpsData));
                memset(ftpsData, 0x0, sizeof(SCapiFtpsData));
                
                ftpsData->flag = SC_DATA_COMPLETE;
                ftpsData->len = list_len;
                ftpsMsg.arg3 = ftpsData;
                
                free(list);
                free(ftp_transfer);
                break;
            }
            case FtpsGetFileSize:
            {
                break;
            }
            case FtpsTransferType:
            {
                break;
            }
            case FtpsGetTransferType:
            {
                break;
            }
            case FtpsSslConfig:
            {
                break;
            }
        }

        if(SC_Ftp_msgQRef)
        {
            if(opt_err)
                ftpsMsg.arg2 = SC_ftpErrno;
            else
                ftpsMsg.arg2 = SC_FTPS_RESULT_OK;
            ftpsMsg.msg_id = ftpmsg->msgid;
            ftpsMsg.arg1 = ftpmsg->msgid;
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            free(ftpmsg);
        }
        opt_err = FALSE;
    }
}

void sAPI_FtpsInit(SC_PDP_ACTIVE_TYPE type,sMsgQRef msgQRef)
{
    mbtk_os_status status;
    static SIM_MSG_T ftpsMsg = {FtpsInit, FtpsInit, SC_FTPS_DO_NOTHING, NULL};
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    
    switch(type)
    {
        case SC_FTPS_USB:
        {
            break;
        }
        case SC_FTPS_UART:
        {
            break;
        }
    }

    if(MBTK_Ftp_msgQRef && MBTK_Ftp_taskRef)
    {
        sAPI_MsgQSend(msgQRef, &ftpsMsg);
        return ;
    }
    else
    {
        status = ol_os_msgq_creat(&MBTK_Ftp_msgQRef, "MBTK_Ftp_msgQ", sizeof(unsigned int), 10, MBTK_OS_FIFO);
        if(status != mbtk_os_success)
        {
            sAPI_MsgQSend(msgQRef, &ftpsMsg);
            return ;
        }
        status = ol_os_task_creat(&MBTK_Ftp_taskRef, NULL, 10 * 1024, 200, "MBTK_Ftp_task", mbtk_ftp_thread, NULL);
        if(status != mbtk_os_success)
        {
            sAPI_MsgQSend(msgQRef, &ftpsMsg);
            return ;
        }
    }

    SC_Ftp_msgQRef = msgQRef;
    
    ftpmsg->msgid = FtpsInit;
    ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
}

void sAPI_FtpsDeInit(SC_PDP_ACTIVE_TYPE TYPE)
{
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsDeInit, FtpsDeInit, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
        }
        return ;
    }

    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsDeInit;
    
    ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
}

SC_FTPS_RETURNCODE sAPI_FtpsLogin(SCftpsLoginMsg msg)
{
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsLogin, FtpsLogin, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }
    
    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    SCftpsLoginMsg *login_msg = malloc(sizeof(SCftpsLoginMsg));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    memcpy(login_msg, &msg, sizeof(SCftpsLoginMsg));
    ftpmsg->msgid = FtpsLogin;
    ftpmsg->param = login_msg;

    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;
    
    return SC_FTPS_RESULT_OK;
}

SC_FTPS_RETURNCODE sAPI_FtpsLogout(void)
{
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsLogout, FtpsLogout, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }
    
    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsLogout;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;

    return SC_FTPS_RESULT_OK;
}

SC_FTPS_RETURNCODE sAPI_FtpsDownloadFile(char* fileName,SC_FTPS_FILE_LOCATION loc)
{
    simcom_api_not_support();
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsDownloadFile, FtpsDownloadFile, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }

    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsDownloadFile;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;

    return SC_FTPS_RESULT_OK;
}

SC_FTPS_RETURNCODE sAPI_FtpsDownloadFileToBuffer(char* fileName,int startPos)
{
    simcom_api_not_support();
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsDownloadFileToBuffer, FtpsDownloadFileToBuffer, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }
    

    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsDownloadFileToBuffer;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;

    return SC_FTPS_RESULT_OK;
}

SC_FTPS_RETURNCODE sAPI_FtpsUploadFile(char* fileName,SC_FTPS_FILE_LOCATION loc,int startPos)
{
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsUploadFile, FtpsUploadFile, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }
    
    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    mbtk_ftp_transfer_t *ftp_transfer = malloc(sizeof(mbtk_ftp_transfer_t));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    memset(ftp_transfer, 0x0, sizeof(mbtk_ftp_transfer_t));

    ftp_transfer->arg1 = startPos;
    memcpy(ftp_transfer->arg2, fileName, sizeof(ftp_transfer->arg2));

    ftpmsg->msgid = FtpsUploadFile;
    ftpmsg->param = ftp_transfer;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;

    return SC_FTPS_RESULT_OK;
}

SC_FTPS_RETURNCODE sAPI_FtpsDeleteFile(char* fileName)
{
    simcom_api_not_support();
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsDeleteFile, FtpsDeleteFile, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }
    

    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsDeleteFile;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;

    return SC_FTPS_RESULT_OK;
}
SC_FTPS_RETURNCODE sAPI_FtpsCreateDirectory(char* dir)
{
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsCreateDirectory, FtpsCreateDirectory, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }
    
    simcom_api_not_support();

    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsCreateDirectory;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;

    return SC_FTPS_RESULT_OK;
}
SC_FTPS_RETURNCODE sAPI_FtpsDeleteDirectory(char* dir)
{
    simcom_api_not_support();
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsDeleteDirectory, FtpsDeleteDirectory, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }
    

    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsDeleteDirectory;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;

    return SC_FTPS_RESULT_OK;
}

SC_FTPS_RETURNCODE sAPI_FtpsChangeDirectory(char* dir)
{
    simcom_api_not_support();
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsChangeDirectory, FtpsChangeDirectory, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }
    

    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsChangeDirectory;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;

    return SC_FTPS_RESULT_OK;
}

SC_FTPS_RETURNCODE sAPI_FtpsGetCurrentDirectory(void)
{
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsGetCurrentDirectory, FtpsGetCurrentDirectory, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }
    
    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsGetCurrentDirectory;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;
        
    return SC_FTPS_RESULT_OK;
}
SC_FTPS_RETURNCODE sAPI_FtpsList(char* dir)
{
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsList, FtpsList, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }

    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    mbtk_ftp_transfer_t *ftp_transfer = malloc(sizeof(mbtk_ftp_transfer_t));
    
    memset(ftp_transfer, 0x0, sizeof(mbtk_ftp_transfer_t));

    memcpy(ftp_transfer->arg2, dir, sizeof(ftp_transfer->arg2));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsList;
    ftpmsg->param = ftp_transfer;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;

    return SC_FTPS_RESULT_OK;
}

SC_FTPS_RETURNCODE sAPI_FtpsGetFileSize(char* fileName)
{
    simcom_api_not_support();
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsGetFileSize, FtpsGetFileSize, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }
    

    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsGetFileSize;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;

    return SC_FTPS_RESULT_OK;
}

SC_FTPS_RETURNCODE sAPI_FtpsTransferType(char* type)
{
    simcom_api_not_support();
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsTransferType, FtpsTransferType, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }
    

    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsTransferType;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;

    return SC_FTPS_RESULT_OK;
}
SC_FTPS_RETURNCODE sAPI_FtpsGetTransferType(void)
{
    simcom_api_not_support();
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsGetTransferType, FtpsGetTransferType, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }
    

    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsGetTransferType;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;

    return SC_FTPS_RESULT_OK;
}
SC_FTPS_RETURNCODE sAPI_FtpsSslConfig(int session,int sslId)
{
    simcom_api_not_support();
    if(!MBTK_Ftp_msgQRef || !MBTK_Ftp_taskRef)
    {
        if(SC_Ftp_msgQRef)
        {
            static SIM_MSG_T ftpsMsg = {FtpsSslConfig, FtpsSslConfig, SC_FTPS_DO_NOTHING, NULL};
            sAPI_MsgQSend(SC_Ftp_msgQRef, &ftpsMsg);
            return SC_FTPS_RESULT_OK;
        }
        return SC_FTPS_DO_NOTHING;
    }
    

    mbtk_os_status status;
    mbtk_ftp_msg_t *ftpmsg = malloc(sizeof(mbtk_ftp_msg_t));
    
    memset(ftpmsg, 0x0, sizeof(mbtk_ftp_msg_t));
    ftpmsg->msgid = FtpsSslConfig;
    
    status = ol_os_msgq_send(MBTK_Ftp_msgQRef, sizeof(unsigned int), &ftpmsg, MBTK_OS_NO_SUSPEND);
    if(status != mbtk_os_success)
        return SC_FTPS_RESULT_UNKNOWN_ERROR;

    return SC_FTPS_RESULT_OK;
}

