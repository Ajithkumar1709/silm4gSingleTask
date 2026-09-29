#include "mbtk_cust_atcommands.h"
#include "mbtk_cust_atcommands_handle.h"
#include "teldef.h"
#include "telutl.h"
#include "telatci.h"
#include "mbtk_pub_type.h"
//#include "mbtk_os.h"


static utlAtParameter_T g_mbtk_test_param[] =
{
    utlDEFINE_DECIMAL_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),
};

#ifdef MBTK_POC_SUPPORT
static utlAtParameter_T g_mbtk_zzd_param[] =
{
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),
};

static utlAtParameter_T g_mbtk_set_poc_param[] =
{
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),
    utlDEFINE_DECIMAL_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),
    utlDEFINE_DECIMAL_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),
};

static utlAtParameter_T Poccfg_params[] = {
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),
	utlDEFINE_DECIMAL_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),
	utlDEFINE_DECIMAL_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),
    };


#endif

static utlAtParameter_T g_mbtk_moji_param[] =
{
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),
};

#ifdef MBTK_PYTHON_SUPPORT
static utlAtParameter_T g_mbtk_py_param[] =
{
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),
};
#endif


static utlAtParameter_T g_mbtk_cat_param[] =
{
    utlDEFINE_DECIMAL_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_REQUIRED),
    utlDEFINE_STRING_AT_PARAMETER(utlAT_PARAMETER_ACCESS_READ_WRITE, utlAT_PARAMETER_PRESENCE_OPTIONAL),
};


static utlAtCommand_T mbtk_cust_at_commands_table[] =
{
    utlDEFINE_EXTENDED_VSYNTAX_AT_COMMAND((MATCmdType)MBTK_CUST_CMD_TEST, "+MBCUSTTEST", g_mbtk_test_param, AtMbtkCustTest, AtMbtkCustTest, AtMbtkCustTest),
#ifdef MBTK_POC_SUPPORT
    utlDEFINE_EXTENDED_VSYNTAX_AT_COMMAND((MATCmdType)MBTK_CMD_POC, "+POC", g_mbtk_zzd_param, ciSetPoc, ciSetPoc, ciSetPoc),
    utlDEFINE_EXTENDED_VSYNTAX_AT_COMMAND((MATCmdType)MPOC_SET_PARAM_POC, "+MPOCSET", g_mbtk_set_poc_param, AtMbtkPocSet, AtMbtkPocSet, AtMbtkPocSet),
#endif

#if defined (MBTK_POC_SUPPORT_BND)
	utlDEFINE_EXTENDED_VSYNTAX_AT_COMMAND((MATCmdType)MAT_IND_POCCFG, "+POCCFG", Poccfg_params, ciSetPoccfg, ciSetPoccfg,ciSetPoccfg),
#endif

    utlDEFINE_EXTENDED_VSYNTAX_AT_COMMAND((MATCmdType)MBTK_CUST_CMD_FACTORY, "+FACTORY", g_mbtk_moji_param, AtMbtkCustFactory, AtMbtkCustFactory, AtMbtkCustFactory),
#ifdef MBTK_PYTHON_SUPPORT
    utlDEFINE_EXTENDED_VSYNTAX_AT_COMMAND((MATCmdType)MBTK_CUST_CMD_PYTHON, "+MPFILE", g_mbtk_py_param, AtMbtkPy, AtMbtkPy, AtMbtkPy),	
#endif
    utlDEFINE_EXTENDED_VSYNTAX_AT_COMMAND((MATCmdType)MBTK_CUST_CMD_CAT_FS, "+CATFS", g_mbtk_cat_param, AtMbtkCatFS, AtMbtkCatFS, AtMbtkCatFS),

};


/*************************************************************
    Function Definitions
*************************************************************/
utlAtCommand_T* mbtk_get_cust_atcommands_table(void)
{
    return mbtk_cust_at_commands_table;
}

unsigned int mbtk_get_cust_atcommands_num(void)
{
    return utlNumberOf(mbtk_cust_at_commands_table);
}

void mbtk_opencpu_init_poc(void)
{
#ifdef MBTK_POC_SUPPORT
    extern void mbtk_poc_init(void);
    mbtk_poc_init();
#endif
}

utlReturnCode_T AtMbtkCustTest(const utlAtParameterOp_T       op,
                               const char*                    command_name_p,
                               const utlAtParameterValue_P2c  parameter_values_p,
                               const size_t                   num_parameters,
                               const char*                    info_text_p,
                               unsigned int*                  xid_p,
                               void*                          arg_p)
{

    CiRequestHandle atHandle = 0;
    TelAtParserID sAtpIndex = * (TelAtParserID*) arg_p;
    atHandle = MAKE_AT_HANDLE(sAtpIndex);
    *xid_p = atHandle;

    int ret = utlFAILED;
    char ret_buff[64] = {0};

    switch(op)
    {
        case TEL_EXT_TEST_CMD:
        {
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, "MBTK_AT_TEST");
        }
        break;
        case TEL_EXT_ACTION_CMD:
        {
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, "MBTK_AT_ACTION");
        }
        break;
        case TEL_EXT_GET_CMD:
        {
	        void mbtk_sleep_debug();
        	mbtk_sleep_debug();
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, "MBTK_AT_GET");
        }
        break;
        case TEL_EXT_SET_CMD:
        {
            int param1 = 0;
            char param2[128] = {0};
            INT16 param2_len = 0;
            char out_buff[150] = {0};

            DIAG_FILTER(MBTK, ATCI, __FUNCTION__, DIAG_INFORMATION);
            diagPrintf("num_parameters = %d", num_parameters);
            if(getExtValue(parameter_values_p, 0, &param1, 0, 10, 0) == FALSE)
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_INVALID_PARAM, NULL);
                break;
            }
            if(num_parameters > 1)
            {
                if(getExtString(parameter_values_p, 1, param2, 128, &param2_len, NULL) == FALSE)
                {
                    ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_INVALID_PARAM, NULL);
                    break;
                }
                sprintf(out_buff, "param=2,str=%s,int = %d", param2, param1);
            }
            else
            {
                sprintf(out_buff, "param=1,int = %d", param1);
            }
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, out_buff);
        }
        break;
    }

    return ret;
}


#ifdef MBTK_POC_SUPPORT

typedef(*ol_poc_at_recv_cb)(char* buf, int len);

ol_poc_at_recv_cb g_poc_cb = NULL;
void mbtk_poc_set_at_recv_cb(ol_poc_at_recv_cb* cb)
{
    g_poc_cb = cb;
}

extern void OEMPOC_AT_Recv(char* buf, int len);

RETURNCODE_T  ciSetPoc(const utlAtParameterOp_T op,
                       const char*                      command_name_p,
                       const utlAtParameterValue_P2c parameter_values_p,
                       const size_t num_parameters,
                       const char*                      info_text_p,
                       unsigned int*                    xid_p,
                       void*                            arg_p)
{
    UNUSEDPARAM(command_name_p);
    UNUSEDPARAM(info_text_p);

    extern ol_poc_at_recv_cb g_poc_cb;
    RETURNCODE_T rc = INITIAL_RETURN_CODE;
    CiReturnCode ret;

    char ValueBuf[1024] = {0};
    char Value0[100] = {0};
    int len = 0;
    int pos = 0;

    UINT32 atHandle = MAKE_AT_HANDLE(*(TelAtParserID*)arg_p);
    *xid_p = atHandle;

    uart_printf("%s() run. %d\r\n", __func__, atHandle);
    switch(op)
    {
        case TEL_EXT_SET_CMD:
            if(getExtString(parameter_values_p, 0, ValueBuf, 1024, &len, NULL) == FALSE)
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_ERROR, 0, NULL);
                break;
            }
            uart_printf("%s: buf - %s, len - %d, strlen(buf) - %d", __func__, ValueBuf, len, strlen(ValueBuf));
#if defined(MBTK_POC_SUPPORT_BND) || defined(MBTK_POC_SUPPORT_IWALKIE)
            int num = mbtk_bnd_para_handle(ValueBuf, len);
            if(0 == ret)
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_SUPPRESS, 0, NULL);
                return;
            }
            pos += len;
            uart_printf("bnd %s:%d\n", __func__, pos);
            int i;
            for(i = 1; i < num; i++)
            {
                memset(Value0, 0, 100);
                if(getExtString(parameter_values_p, i, Value0, 100, &len, NULL) == FALSE)
                {
                    ret = ATRESP(atHandle, ATCI_RESULT_CODE_ERROR, 0, NULL);
                    return -1;
                }
                uart_printf("%s,%s,%d,%d\n", __func__, Value0, len, pos);

                if(len)
                {
                    pos += sprintf(ValueBuf + pos, ",%s", Value0);
                    uart_printf("%s,%d,ValueBuf:%s\n", __func__, len, ValueBuf);
                }
                else
                {
                    break;
                }
            }
            len = pos;
#endif
#ifdef MBTK_POC_SUPPORT
            OEMPOC_AT_Recv(ValueBuf, len);
#endif
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_SUPPRESS, 0, NULL);
            break;
        default:
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_ERROR, 0, NULL);
            break;
    }

    /* handle the return value */
    rc = HANDLE_RETURN_VALUE(ret);
    return(rc);
}



char patcool_get_imei = 0;

#define POC_DEALER_PASSWORD_FILENAME "poctool_dealer_password.txt"
#define POC_PLATFORM_INFO_FILENAME "poctool_platform_info.txt"
#define POC_PLATFORM_USERINFO_FILENAME "poctool_platform_userinfo.txt"


typedef struct
{
    unsigned char poc_user_info_update;
    unsigned char poc_user_info[512];
} mbtk_poctool_user_info_struct;


typedef struct
{
    unsigned char poc_platform_name; // 0x01 卓志�?  0x04  公网时代
    unsigned char poc_call_switch;   // 0x01 open     0x02  close
    unsigned char poc_platform_url[256];
} mbtk_poctool_platform_info_struct;

typedef struct
{
    unsigned char poc_dealer_password[64];
    unsigned char poc_dealer_password_new[64];
} mbtk_poctool_dealer_password_struct;




mbtk_poctool_user_info_struct  poctool_user_info = {0};

char poctool_set_param = 0;
char poctool_set_url = 0;


int mbtk_poctool_set_info(uint8_t* user_info, uint8_t* dealer_password, uint8_t* dealer_password_new, uint8_t call_switch,
                          uint8_t platform_index, uint8_t* url)
{
    int dealer_file_handle = 0;
    int userinfo_file_handle = 0;
    int platform_file_handle = 0;
    int iret = 0;
    int count = 0;
    mbtk_poctool_dealer_password_struct poctool_dealer_password = {0};
    mbtk_poctool_platform_info_struct poctool_platform_info = {0};
    char* fs_write_ptr = NULL;


    if(url != NULL)
    {
        poctool_platform_info.poc_call_switch = call_switch;
        poctool_platform_info.poc_platform_name = platform_index;
        memset(poctool_platform_info.poc_platform_url, 0, 256);
        memcpy(poctool_platform_info.poc_platform_url, url, strlen(url));

        //extern void oem_ERequestSetURL(char *url);
        //oem_ERequestSetURL(poctool_platform_info.poc_platform_url);
#if 0
        while(!poctool_set_url && (count <= 10))
        {
            mbtk_os_task_sleep(200);
            count++;
        }

        if((count > 10 || poctool_set_url == 2))
        {
            poctool_set_url = 0;
            memset(poctool_platform_info.poc_platform_url, 0, 256);
            uart_printf("mbtk_poctool_set_info oem_ERequestSetURL fail \n");
            return -1;
        }
        poctool_set_url = 0;
#endif
        if((platform_file_handle = ol_FFS_Open(POC_PLATFORM_INFO_FILENAME, "wb")) < 0)
        {
            uart_printf("mbtk_poctool_set_info open POC_PLATFORM_INFO_FILENAME fail \n");
            return -1;
        }

        uart_printf("mbtk_poctool_set_info platform_file_handle [%u] \n", platform_file_handle);

        if((iret = ol_FFS_Write(platform_file_handle, &poctool_platform_info, sizeof(mbtk_poctool_platform_info_struct))) < 0)
        {
            uart_printf("mbtk_poctool_set_info write poctool_dealer_password fail \n");
            ol_FFS_Close(platform_file_handle);
            return -1;
        }

        uart_printf("mbtk_poctool_set_info ol_FFS_Write ret [%d] struct size[%d] info size [%d]\n", iret, sizeof(mbtk_poctool_platform_info_struct), sizeof(poctool_platform_info));

        ol_FFS_Close(platform_file_handle);
    }


    if(user_info != NULL)
    {
        uart_printf("mbtk_poctool_set_info enter %s\n", user_info);
        //extern void oem_ERequestSetParam(uint8_t *str);
        //oem_ERequestSetParam(user_info);
#if 0
        while(!poctool_set_param && (count <= 10))
        {
            mbtk_os_task_sleep(200);
            count++;
        }

        if((count > 10 || poctool_set_param == 2))
        {
            poctool_set_param = 0;
            uart_printf("mbtk_poctool_set_info oem_ERequestSetParam fail \n");
            return -1;
        }
        poctool_set_param = 0;

        count = 0;
#endif
        if((userinfo_file_handle = ol_FFS_Open(POC_PLATFORM_USERINFO_FILENAME, "wb")) < 0)
        {
            uart_printf("mbtk_poctool_set_info open POC_DEALER_PASSWORD_FILENAME fail \n");
            return -1;
        }

        if(iret = ol_FFS_Write(userinfo_file_handle, user_info, strlen(user_info)) < 0)
        {
            uart_printf("mbtk_poctool_set_info write poctool_platform_userinfo fail \n");
            ol_FFS_Close(userinfo_file_handle);
            return -1;
        }

        ol_FFS_Close(userinfo_file_handle);
    }

    if(dealer_password != NULL || dealer_password_new != NULL)
    {
        if(dealer_password != NULL)
        {
            memset(poctool_dealer_password.poc_dealer_password, 0, 64);
            memcpy(poctool_dealer_password.poc_dealer_password, dealer_password, strlen(dealer_password));
        }
        else
        {
            memset(poctool_dealer_password.poc_dealer_password, 0, 64);
        }

        if(dealer_password_new != NULL)
        {
            memset(poctool_dealer_password.poc_dealer_password_new, 0, 64);
            memcpy(poctool_dealer_password.poc_dealer_password_new, dealer_password, strlen(dealer_password));
            memset(poctool_dealer_password.poc_dealer_password, 0, 64);
            memcpy(poctool_dealer_password.poc_dealer_password, poctool_dealer_password.poc_dealer_password_new, strlen(poctool_dealer_password.poc_dealer_password_new));
        }
        else
        {
            memset(poctool_dealer_password.poc_dealer_password_new, 0, 64);
        }

        if((dealer_file_handle = ol_FFS_Open(POC_DEALER_PASSWORD_FILENAME, "wb")) < 0)
        {
            uart_printf("mbtk_poctool_set_info open POC_DEALER_PASSWORD_FILENAME fail \n");
            return -1;
        }


        if((iret = ol_FFS_Write(dealer_file_handle, &poctool_dealer_password, sizeof(mbtk_poctool_dealer_password_struct))) < 0)
        {
            uart_printf("mbtk_poctool_set_info write poctool_dealer_password fail \n");
            ol_FFS_Close(dealer_file_handle);
            return -1;
        }

        ol_FFS_Close(dealer_file_handle);
    }


    uart_printf("mbtk_poctool_set_info success \n");
    return 0;
}



unsigned char* mbtk_poc_get_user_passwd(char* info)
{

    int userinfo_file_handle = 0;
    int iret = 0;

    if(!info)
    {
        return NULL;
    }

    userinfo_file_handle = ol_FFS_Open(POC_PLATFORM_USERINFO_FILENAME, "rb");
    if(userinfo_file_handle <= 0)
    {
        return NULL;
    }


    if((iret = ol_FFS_Read(userinfo_file_handle, info, ol_FFS_GetSize(POC_PLATFORM_USERINFO_FILENAME))) < 0)
    {
        uart_printf("mbtk_poc_get_dealer_password read poctool_dealer_password fail \n");
        ol_FFS_Close(userinfo_file_handle);
        return NULL;
    }

    ol_FFS_Close(userinfo_file_handle);

    return info;
}


void oem_ERequestGetParam(void)
{
    char cmd[20] = "020000" ;
    OEMPOC_AT_Recv(cmd, strlen(cmd));
}

unsigned char* mbtk_poc_get_user_info(void)
{
    static int waite_count = 0;
    extern void oem_ERequestGetParam(void);
    oem_ERequestGetParam();
    while(!poctool_user_info.poc_user_info_update && (waite_count <= 10))
    {
        mbtk_os_task_sleep(200);
        waite_count++;
    }

    if(waite_count > 10)
    {
        return NULL;
    }

    uart_printf("mbtk_poc_get_user_info break, waite_count = %d, update = %d \n", waite_count, poctool_user_info.poc_user_info_update);

    if(poctool_user_info.poc_user_info_update)
    {
        poctool_user_info.poc_user_info_update = 0;
        if(strlen(poctool_user_info.poc_user_info) > 0)
        {
            return poctool_user_info.poc_user_info;
        }
        else
        {
            return NULL;
        }
    }
}



unsigned char* mbtk_poc_get_dealer_password(void)
{
    int dealer_file_handle = 0;
    int iret = 0;
    mbtk_poctool_dealer_password_struct poctool_dealer_password = {0};

    if((dealer_file_handle = ol_FFS_Open(POC_DEALER_PASSWORD_FILENAME, "wb")) < 0)
    {
        uart_printf("mbtk_poc_get_dealer_password open poctool_dealer_password fail \n");
        return NULL;
    }

    if((iret = ol_FFS_Read(dealer_file_handle, &poctool_dealer_password, sizeof(dealer_file_handle))) < 0)
    {
        uart_printf("mbtk_poc_get_dealer_password read poctool_dealer_password fail \n");
        ol_FFS_Close(dealer_file_handle);
        return NULL;
    }

    ol_FFS_Close(dealer_file_handle);

    if(strlen(poctool_dealer_password.poc_dealer_password) > 0)
    {
        return poctool_dealer_password.poc_dealer_password;
    }
    else
    {
        return NULL;
    }
}


int mbtk_poc_get_platform_info(mbtk_poctool_platform_info_struct* info)
{
    int platform_file_handle = 0;
    int iret = 0;
    mbtk_poctool_platform_info_struct poctool_platform_info = {0};

    if((platform_file_handle = ol_FFS_Open(POC_PLATFORM_INFO_FILENAME, "rb")) < 0)
    {
        uart_printf("mbtk_poc_get_platform_info open poctool_platform_info fail \n");
        return -1;
    }

    uart_printf("mbtk_poc_get_platform_info platform_file_handle [%u] \n", platform_file_handle);

    if((iret = ol_FFS_Read(platform_file_handle, &poctool_platform_info, sizeof(mbtk_poctool_platform_info_struct))) < 0)
    {
        uart_printf("mbtk_poc_get_dealer_password read poctool_platform_info fail \n");
        ol_FFS_Close(platform_file_handle);
        return -1;
    }

    uart_printf("mbtk_poc_get_platform_info iret [%d], data size[%d] \n", iret, sizeof(mbtk_poctool_platform_info_struct));

    ol_FFS_Close(platform_file_handle);

    uart_printf("mbtk_poc_get_platform_info call [%d], platform [%d], url [%s] \n", poctool_platform_info.poc_call_switch, poctool_platform_info.poc_platform_name, poctool_platform_info.poc_platform_url);

    memcpy(info, &poctool_platform_info, sizeof(poctool_platform_info));

    return 0;
}

int mbtk_poctool_get_info(uint8_t* account_info, uint8_t** firmversion, uint8_t* callswitch,
                          uint8_t* platform_index, uint8_t* url)
{
    unsigned char* user_info = NULL;
    char cap_index = 0;
    mbtk_poctool_platform_info_struct poctool_platform_info = {0};
    int iret = 0;
    uart_printf("mbtk_poctool_get_info enter \n");
#if 0
    if((user_info = mbtk_poc_get_user_info()) == NULL)
    {
        uart_printf("mbtk_poctool_get_info get mbtk_poc_get_user_info fail \n");
        return -1;
    }

    memcpy(account_info, user_info, strlen(user_info));
#endif
    if((*firmversion = mbtk_get_modem_version()) == NULL)
    {
        uart_printf("mbtk_poctool_get_info get mbtk_get_modem_version fail \n");
        return -1;
    }

    if((iret = mbtk_poc_get_platform_info(&poctool_platform_info)) < 0)
    {
        uart_printf("mbtk_poctool_get_info get mbtk_poc_get_platform_info fail \n");
        return -1;
    }

    *callswitch = poctool_platform_info.poc_call_switch;
    *platform_index = poctool_platform_info.poc_platform_name;

    if(strlen(poctool_platform_info.poc_platform_url) > 0)
    {
        memcpy(url, poctool_platform_info.poc_platform_url, strlen(poctool_platform_info.poc_platform_url));
    }

    uart_printf("mbtk_poctool_get_info success  account [%s] , firver [%s], call [%d], platform [%d], url[%s] \n", account_info, *firmversion, callswitch, platform_index, url);

    return 0;

}



utlReturnCode_T AtMbtkPocSet(const utlAtParameterOp_T    op,
                             const char*                    command_name_p,
                             const utlAtParameterValue_P2c  parameter_values_p,
                             const size_t                   num_parameters,
                             const char*                    info_text_p,
                             unsigned int*            xid_p,
                             void*                    arg_p)
{

    CiRequestHandle atHandle = 0;
    TelAtParserID sAtpIndex = * (TelAtParserID*) arg_p;
    atHandle = MAKE_AT_HANDLE(sAtpIndex);
    *xid_p = atHandle;

    int ret = utlFAILED;

    uart_printf("AtMbtkPocSet enter cmd type[%d] \n", op);


    switch(op)
    {
        case TEL_EXT_TEST_CMD:
        {
            uart_printf("AtMbtkPocSet TEL_EXT_TEST_CMD enter \n");
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, "AT+MPOCSET=\"accountinfo\",\"dealerpassword\",\"dealerpasswordnew\",call,platform,\"url\"");
            break;
        }

        case TEL_EXT_ACTION_CMD:
        {
            uart_printf("AtMbtkPocSet TEL_EXT_ACTION_CMD is not support \n");
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_NOT_FOUND, NULL);
            break;
        }

        case TEL_EXT_GET_CMD:
        {
            char resp_buf[512] = {0};
            char account_buf[256] = {0};
            char* firm_ver = NULL;
            char call_switch = 0;
            char platform_index = 0;
            char url[256] = {0};



            extern CiReturnCode DEV_GetSerialNumId(UINT32 atHandle);

            patcool_get_imei = 1;
            DEV_GetSerialNumId(atHandle);

            while(patcool_get_imei)
            {
                mbtk_os_task_sleep(2);
            }

            ret = mbtk_poctool_get_info(account_buf, &firm_ver, &call_switch, &platform_index, url);
            uart_printf("AtMbtkPocSet TEL_EXT_GET_CMD mbtk_poctool_get_param ret = %d \n", ret);
            if(ret < 0)
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CMS_ME_FAILURE, NULL);
                break;
            }

            if(strlen(account_buf) == 0 && strlen(url) == 0)
            {
                sprintf(resp_buf, "+MPOCSET:\"\",\"%s\",%d,%d,\"\"", firm_ver, call_switch, platform_index);
            }
            else if(strlen(account_buf) == 0)
            {
                sprintf(resp_buf, "+MPOCSET:\"\",\"%s\",%d,%d,\"%s\"", firm_ver, call_switch, platform_index, url);
            }
            else if(strlen(url) == 0)
            {
                sprintf(resp_buf, "+MPOCSET:\"%s\",\"%s\",%d,%d,\"\"", account_buf, firm_ver, call_switch, platform_index);
            }
            else
            {
                sprintf(resp_buf, "+MPOCSET:\"%s\",\"%s\",%d,%d,\"%s\"", account_buf, firm_ver, call_switch, platform_index, url);
            }

            ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, resp_buf);
            break;
        }

        case TEL_EXT_SET_CMD:
        {
            char account_buf[512] = {0};
            int account_buf_len = 0;
            char dealer_password[256] = {0};
            int dealer_password_len = 0;
            char dealer_password_new[256] = {0};
            int dealer_password_new_len = 0;
            char call_switch = 0;
            char platform_index = 0;
            char url[256] = {0};
            int url_len = 0;

            uart_printf("AtMbtkPocSet num_parameters = %d \n", num_parameters);

            if(num_parameters != 6)
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_INVALID_PARAM, NULL);
                break;
            }

            if(getExtString(parameter_values_p, 0, account_buf, 512, &account_buf_len, NULL) == FALSE)
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_INVALID_PARAM, NULL);
                break;
            }

            if(getExtString(parameter_values_p, 1, dealer_password, 256, &dealer_password_len, NULL) == FALSE)
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_INVALID_PARAM, NULL);
                break;
            }

            if(getExtString(parameter_values_p, 2, dealer_password_new, 256, &dealer_password_new_len, NULL) == FALSE)
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_INVALID_PARAM, NULL);
                break;
            }

            if(getExtValue(parameter_values_p, 3, &call_switch, 1, 2, 2) == FALSE)
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_INVALID_PARAM, NULL);
                break;
            }

            if(getExtValue(parameter_values_p, 4, &platform_index, 0, 5, 0) == FALSE)
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_INVALID_PARAM, NULL);
                break;
            }

            if(getExtString(parameter_values_p, 5, url, 256, &url_len, NULL) == FALSE)
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_INVALID_PARAM, NULL);
                break;
            }

            ret = mbtk_poctool_set_info(account_buf, dealer_password, dealer_password_new, call_switch, platform_index, url);
            uart_printf("AtMbtkPocSet TEL_EXT_SET_CMD mbtk_poctool_set_param ret = %d \n", ret);
            if(ret < 0)
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CMS_ME_FAILURE, NULL);
                break;
            }

            ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, "+MPOCSET:SUCCESS");
            break;
        }
    }

    return ret;
}




utlReturnCode_T  ciSetPoccfg(            const utlAtParameterOp_T op,
                  const char                      *command_name_p,
                  const utlAtParameterValue_P2c parameter_values_p,
                  const size_t num_parameters,
                  const char                      *info_text_p,
                  unsigned int                    *xid_p,
                  void                            *arg_p)
{
    UNUSEDPARAM(command_name_p);
    UNUSEDPARAM(info_text_p);

    utlReturnCode_T rc = utlFAILED;
    CiReturnCode ret;

    char str_platform[32]={0};
	int  is_broad = 0;
	int  is_abroad = 0;
    INT16 len = 0;
    int pos = 0;
    UINT32 atHandle = MAKE_AT_HANDLE(*(TelAtParserID *)arg_p);
    *xid_p = atHandle;

	int i;
    switch (op)
    {
        case TEL_EXT_SET_CMD:
			if (getExtString(parameter_values_p, 0, str_platform, 32, &len, NULL) == FALSE)
            {
                ret = ATRESP( atHandle, ATCI_RESULT_CODE_ERROR, 0, NULL);
                break;
            }
			if( getExtValue( parameter_values_p, 1, &is_broad, 0, 1, 0) == FALSE )
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, 0, NULL);
                break;
            }
            if( getExtValue( parameter_values_p, 2, &is_abroad, 0, 1, 0) == FALSE )
            {
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, 0, NULL);
                break;
            }
			CPUartLogPrintf("%s (%s,%d,%d)", __func__,str_platform,is_broad,is_abroad);
			/*
			strcpy(poc_info.str_platform,str_platform);
			poc_info.is_broad = is_broad;
			poc_info.is_abroad = is_abroad;
			poccfg_savenvm(&poc_info);
			*/
			ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, 0);
			break;				
        default:
            ret = ATRESP( atHandle, ATCI_RESULT_CODE_ERROR, 0, NULL);
            break;
    }

    /* handle the return value */
    rc = HANDLE_RETURN_VALUE(ret);
    return(rc);
}
			



#endif







int mbtk_save_factory_msg_to_fs(char *file_name, char *file_data)
{
    int fd;
    
    if(256 >= FDI_GetFreeSpaceSize())
    {
        uart_printf("%s: don't have enough memory to store file. FreeSpaceSize = %u.", __FUNCTION__, FDI_GetFreeSpaceSize());
        return -1;
    }
    fd = FDI_fopen(file_name, "wb+");
    if (fd <= 0)
    {
        uart_printf("[%s %d] open %s error!\n", __FUNCTION__, __LINE__, file_name);
        return -1;
    }
    
    if(FDI_fwrite(file_data, 1, strlen(file_data), fd) <= 0)
    {
        uart_printf("[%s %d] wrtie %s error!\n", __FUNCTION__, __LINE__, file_name);
        return -1;
    }
    FDI_fclose(fd);
    return 0;
}
int mbtk_get_factory_msg_from_fs(char *file_name, char *file_data)
{
    int fd;
    fd = FDI_fopen(file_name, "rb+");
    if (fd <= 0)
    {
        uart_printf("[%s %d] open %s error!\n", __FUNCTION__, __LINE__, file_name);
        return -1;
    }
    
    if(FDI_fread(file_data, 1, FDI_GetFileSize(fd), fd) <= 0)
    {
        uart_printf("[%s %d] read %s error!\n", __FUNCTION__, __LINE__, file_name);
        return -1;
    }
    
    FDI_fclose(fd);
    return 0;
}

utlReturnCode_T AtMbtkCustFactory(const utlAtParameterOp_T       op,
                                const char*                    command_name_p,
                                const utlAtParameterValue_P2c  parameter_values_p,
                                const size_t                   num_parameters,
                                const char*                    info_text_p,
                                unsigned int*                  xid_p,
                                void*                          arg_p)
{
    CiRequestHandle atHandle = 0;
    TelAtParserID sAtpIndex = * (TelAtParserID*) arg_p;
    atHandle = MAKE_AT_HANDLE(sAtpIndex);
    *xid_p = atHandle;
    
    int ret = utlFAILED;
    char resp_buf[256] = {0};
    char product_id[64] = {0};
    char device_name[64] = {0};
    char device_secret[64] = {0};
    
    uart_printf("AtMbtkPocSet enter cmd type[%d] \n", op);

    switch(op)
    {
        case TEL_EXT_TEST_CMD:
        {
            uart_printf("%s TEL_EXT_TEST_CMD enter \n", __func__);
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, "+FACTORY:<ProductId>,<DeviceName>,<DeviceSecret>");
            break;
        }
        
        case TEL_EXT_GET_CMD:
        {
            mbtk_get_factory_msg_from_fs("ProductId", product_id);
            mbtk_get_factory_msg_from_fs("DeviceName", device_name);
            mbtk_get_factory_msg_from_fs("DeviceSecret", device_secret);
            
            sprintf(resp_buf, "+FACTORY:<%s>,<%s>,<%s>", product_id, device_name, device_secret);
            ret = ATRESP(atHandle,ATCI_RESULT_CODE_OK,0,resp_buf);
            break;
        }
        
        case TEL_EXT_SET_CMD:
        {
            int paraStrLength = 0;
            if (getExtString(parameter_values_p, 0, product_id, 64, &paraStrLength, NULL) == FALSE )
            {
                ret = ATRESP(atHandle,ATCI_RESULT_CODE_CME_ERROR,CME_INVALID_PARAM,NULL);
                break;
            }
            mbtk_save_factory_msg_to_fs("ProductId", product_id);
            if (getExtString(parameter_values_p, 1, device_name, 64, &paraStrLength, NULL) == FALSE )
            {
                ret = ATRESP(atHandle,ATCI_RESULT_CODE_CME_ERROR,CME_INVALID_PARAM,NULL);
                break;
            }
            mbtk_save_factory_msg_to_fs("DeviceName", device_name);
            if (getExtString(parameter_values_p, 2, device_secret, 64, &paraStrLength, NULL) == FALSE )
            {
                ret = ATRESP(atHandle,ATCI_RESULT_CODE_CME_ERROR,CME_INVALID_PARAM,NULL);
                break;
            }
            mbtk_save_factory_msg_to_fs("DeviceSecret", device_secret);
            ret = ATRESP(atHandle,ATCI_RESULT_CODE_OK,0,NULL);
            break;
        }
        default:
        {
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_ERROR, 0, NULL);
            break;
        }
    }

    return ret;
}




#ifdef MBTK_PYTHON_SUPPORT

int python_change_main_py_name(char *file);
char *python_get_main_py_name(void);

utlReturnCode_T AtMbtkPy(const utlAtParameterOp_T       op,
                                const char*                    command_name_p,
                                const utlAtParameterValue_P2c  parameter_values_p,
                                const size_t                   num_parameters,
                                const char*                    info_text_p,
                                unsigned int*                  xid_p,
                                void*                          arg_p)
{
    CiRequestHandle atHandle = 0;
    TelAtParserID sAtpIndex = * (TelAtParserID*) arg_p;
    atHandle = MAKE_AT_HANDLE(sAtpIndex);
    *xid_p = atHandle;
    
    int ret = utlFAILED;
    char resp_buf[256] = {0};
    char file_name[127] = {0};
    
    uart_printf("AtMbtkPy enter cmd type[%d] \n", op);

    switch(op)
    {
        case TEL_EXT_TEST_CMD:
        {
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, "+MPFILE:<filename>");
            break;
        }
        
        case TEL_EXT_GET_CMD:
        {            
            sprintf(resp_buf, "+MPFILE:<%s>", python_get_main_py_name());
            ret = ATRESP(atHandle,ATCI_RESULT_CODE_OK,0,resp_buf);
            break;
        }
        
        case TEL_EXT_SET_CMD:
        {
            int paraStrLength = 0;
            if (getExtString(parameter_values_p, 0, file_name, 127, &paraStrLength, NULL) == FALSE )
            {
                ret = ATRESP(atHandle,ATCI_RESULT_CODE_CME_ERROR,CME_INVALID_PARAM,NULL);
                break;
            }
			if(paraStrLength!=0)
            	python_change_main_py_name(file_name);
			
            ret = ATRESP(atHandle,ATCI_RESULT_CODE_OK,0,NULL);
            break;
        }
        default:
        {
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_ERROR, 0, NULL);
            break;
        }
    }

    return ret;
}

#endif




utlReturnCode_T AtMbtkCatFS(const utlAtParameterOp_T       op,
                                const char*                    command_name_p,
                                const utlAtParameterValue_P2c  parameter_values_p,
                                const size_t                   num_parameters,
                                const char*                    info_text_p,
                                unsigned int*                  xid_p,
                                void*                          arg_p)
{
    CiRequestHandle atHandle = 0;
    TelAtParserID sAtpIndex = * (TelAtParserID*) arg_p;
    atHandle = MAKE_AT_HANDLE(sAtpIndex);
    *xid_p = atHandle;
    
    int ret = utlFAILED;
	int operation = 0;
	char resp_buf[64] = {0};
	char disable_deivce[20] = {0};
    
	int mbtk_catfs_isdisable(void);
	int mbtk_catfs_disable_str(char *disable_deivce, int buf_size);
	int mbtk_set_catfs_disable_device(char *device);
	int mbtk_catfs_enable(char *device);
    switch(op)
    {
        case TEL_EXT_TEST_CMD:
        {
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, "+CATFS:<oper>,<device>");
            break;
        }
        
        case TEL_EXT_GET_CMD:
        {            
        	if(mbtk_catfs_isdisable()){
				mbtk_catfs_disable_str(disable_deivce, sizeof(disable_deivce));
            	sprintf(resp_buf, "+CATFS:1,<%s>", disable_deivce);
        	}
			else
				sprintf(resp_buf, "+CATFS:0");
			
            ret = ATRESP(atHandle,ATCI_RESULT_CODE_OK,0,resp_buf);
            break;
        }
        
        case TEL_EXT_SET_CMD:
        {
            int paraStrLength = 0;

			
            if(getExtValue(parameter_values_p, 0, &operation, 0, 1, 0) == FALSE)
			{
                ret = ATRESP(atHandle, ATCI_RESULT_CODE_CME_ERROR, CME_INVALID_PARAM, NULL);
                break;
            }
			
           
			if (getExtString(parameter_values_p, 1, disable_deivce, 4, &paraStrLength, NULL) == FALSE )
            {
                ret = ATRESP(atHandle,ATCI_RESULT_CODE_CME_ERROR,CME_INVALID_PARAM,NULL);
                break;
            }


			if(operation == 0){
				if(strlen(disable_deivce)==0)
					ret = mbtk_catfs_enable(0);
				else
					ret = mbtk_catfs_enable(disable_deivce);
				
			}else{
				ret = mbtk_set_catfs_disable_device(disable_deivce);
			}
			
			if(ret == 0)
				ret = ATRESP(atHandle, ATCI_RESULT_CODE_OK, 0, NULL);
			else
            	ret = ATRESP(atHandle,ATCI_RESULT_CODE_ERROR,0,NULL);
            break;
        }
        default:
        {
            ret = ATRESP(atHandle, ATCI_RESULT_CODE_ERROR, 0, NULL);
            break;
        }
    }

    return ret;
}

