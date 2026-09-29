#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "mbtk_pub_type.h"
#include "mbtk_nw_api.h"
#include "mbtk_os.h"
#include "mbtk_socket_api.h"
#include "mbtk_datacall_api.h"
#include "mbtk_sim_api.h"
#include "mbtk_device_api.h"
#include "oem_api.h"
#include "mbtk_log.h"

#ifdef  MBTK_POC_SUPPORT_HAWK


typedef enum
{
    PPP_STATUS_NONE = 0,
    PPP_STATUS_CONNECTING,
    PPP_STATUS_CONNECTED,
    PPP_STATUS_DISCONNECTING,
    PPP_STATUS_DISCONNECTED,
}oem_ppp_status_type_e;

typedef struct 
{
    unsigned int MsgType;
    void* MsgData;
    unsigned int DataLen;
    unsigned short param;
}oem_poc_user_msg_s;


typedef enum
{
    NETWORK_MODE_NONE = 0,

    NETWORK_MODE_CDMA = 1,
    NETWORK_MODE_HDR = 1 << 1,

    NETWORK_MODE_LTE = 1 << 2,
    NETWORK_MODE_GSM = 1 << 3,

    NETWORK_MODE_WCDMA = 1 << 4,
    NETWORK_MODE_TDCDMA = 1 << 5,
    NETWORK_MODE_MAX,
}oem_network_mode_type_e;

typedef enum
{
    NETWORK_STATUS_NONE = 0,
    NETWORK_UNREGISTER,
    NETWORK_REGISTER,
}oem_network_status_type_e;

enum
{
    TTS_STOP,
    TTS_PLAY_UTF16LE,    /*play ucs2 pcm */
    TTS_PLAY_GBK,        /*play gbk*/
};

typedef enum
{
    POC_SIM_STATUS_NONE = 0,
    POC_SIM_STATUS_READY,
    POC_SIM_STATUS_NOT_INSERT,
    POC_SIM_STATUS_MAX
}oem_sim_status_type_e;

typedef struct
{
    oem_network_status_type_e network_status;
    oem_network_mode_type_e network_mode;
    unsigned int cell_id;
    unsigned int lac_or_tac;
    char rssi;
    char mcc[4];         //add
    char mnc[4];         //add
}oem_network_info_s;

typedef enum 
{
    NO_PPP_SERVICE = 0,
    PPP_SERVICE_AVAILABLE = 1,
    OEM_PPP_MAX,
}oem_ppp_status;

typedef struct
{
    char long_eons[128];
    char short_eons[128];
    char mcc[4];
    char mnc[4];
}ol_OPERATOR_INFO;

typedef enum 
{
  OL_NW_REG_STA_NOT_REGED = 0,                  /**< Not registered and not searching */
  OL_NW_REG_STA_REG_HPLMN,                      /**< Registered on home PLMN */
  OL_NW_REG_STA_TRYING,                         /**< Not registered, but cellular subsystem is searching for a PLMN to register to */
  OL_NW_REG_STA_REG_DENIED,                     /**< Registration denied */
  OL_NW_REG_STA_UNKNOWN,                        /**< Unknown */
  OL_NW_REG_STA_REG_ROAMING,                    /**< Registered on visited PLMN */
  OL_NW_REG_STA_SMS_ONLY_HOME,                  /**< registered for "SMS only", home network (applicable only when <AcT> indicates E-UTRAN) */
  OL_NW_REG_STA_SMS_ONLY_ROAMING,               /**< registered for "SMS only", roaming (applicable only when <AcT> indicates E-UTRAN) */
  OL_NW_REG_STA_EMERGENCY_ONLY_NOT_USED,        /**< attached for emergency bearer services only (see NOTE 2) (not applicable) */
  OL_NW_REG_STA_CSFB_NOT_PREFERRED_HOME,        /**<registered for "CSFB not preferred", home network (applicable only when <AcT> indicates E-UTRAN) */
  OL_NW_REG_STA_CSFB_NOT_PREFERRED_ROAMING,     /**<registered for "CSFB not preferred", roaming (applicable only when <AcT> indicates E-UTRAN) */
  OL_NW_REG_STA_REG_EMERGENCY,                  /**< attached for emergency bearer services only*/
  OL_NW_REG_STA_REG_DENIED_IN_ROAMING,          /**< registeration denied in roaming, only used for SSG project by now*/
  OL_NW_REG_STA_SYNC_DONE_IN_LTE_ROAMING,       /**< sync done in LTE roaming network, only used for SSG project by now*/
  OL_NW_REGSTATUS                               /**< Number of status values defined */

}OL_NW_REG_STATE;

typedef enum 
{
    OL_NW_ACT_GSM = 0,              /**< GSM */
    OL_NW_ACT_GSM_COMPACT,          /**< Not supported */
    OL_NW_ACT_UTRAN,                /**< UTRAN */
    OL_NW_ACT_GSM_EGPRS,            /**< GSM w/EGPRS */
    OL_NW_ACT_UTRAN_HSDPA,          /**< UTRAN w/HSDPA */
    OL_NW_ACT_UTRAN_HSUPA,          /**< UTRAN w/HSUPA */
    OL_NW_ACT_UTRAN_HSPA,           /**< UTRAN w/HSDPA and HSUPA */
    OL_NW_ACT_EUTRAN,               /**< E-UTRAN */  
    OL_NW_ACT_UTRAN_HSPA_PLUS,      /**< UTRAN w/HSPA+ */ 
    OL_NW_ACT_EUTRAN_PLUS,          /*E-UTRAN CA*/
    OL_NW_ACT_UTRAN_DC_HSPA,        /*DC-HSPA*/
    OL_NW_NUM_ACT
}OL_NW_ACCESS_TECHNOLOGY;

typedef struct
{
    OL_NW_REG_STATE state;
    OL_NW_ACCESS_TECHNOLOGY act;
    int lac;
    int cid;
    int t3324;
    int t3412ext2;
}ol_REG_STATUS_INFO;

void OEM_TTS_Status_CB(int status);

void hawk_printf(void *fmt,...)
{
    va_list ap;
    char buffer[128] = {0};
    static int fatal_uart_inited = 0;

    memset(buffer, 0, sizeof(buffer));
    va_start(ap, fmt);
    vsnprintf(buffer, sizeof(buffer)-1, fmt, ap);
    va_end(ap);

	MLOG_D(MLOG_POC, POC,"%s\n",buffer);}

int OEM_pppOpen(void)
{
    MLOG_D(MLOG_POC, POC,"OEM_pppOpen %d", OEMGetNetStatus());
    OEMNetworkStatusChange(OEMGetNetStatus());
    return OEMGetNetStatus();
}

int OEM_pppClose(void)
{
    MLOG_D(MLOG_POC, POC,"OEM_pppClose");
    return 1;
}

oem_ppp_status_type_e OEM_getPppStatus(void)
{
    MLOG_D(MLOG_POC, POC,"OEM_getPppStatus");
    if(OEMGetNetStatus() == 1)
    {
        return PPP_STATUS_CONNECTED;
    }
    else
    {
        return PPP_STATUS_DISCONNECTED;
    }
}

void OEMSleep(int ticks)
{
    MLOG_D(MLOG_POC, POC,"OEMSleep %d", ticks);
    mbtk_os_task_sleep(ticks);
}

unsigned long OEM_Get_time()
{
    return mbtk_os_get_ticks();
}


extern mbtk_ostimerref g_oem_timer;
//定时器回调函�?
typedef void (* timercallbackfunc_t)(unsigned long param);

void OEM_SetTimer(void **TimerRef, unsigned long timeout, unsigned long rescheduleTime, timercallbackfunc_t callbackfunc, unsigned long timerArgc)
{
    /*creat timer*/
    mbtk_os_status status;
    mbtk_os_timer_status_struct status_s = {0};

    TimerRef = &g_oem_timer;
    mbtk_os_get_timer_status(g_oem_timer, &status_s);
    if (status_s.status == MBTK_OS_TIMER_ACTIVE)
    {
        OEM_CancelTimer();
    }

    status = mbtk_os_timer_start(g_oem_timer, timeout, rescheduleTime, callbackfunc, timerArgc);
    //DIAG_ASSERT(status == mbtk_os_success);
    MLOG_D(MLOG_POC, POC,"%s:oemtimer start. %d", __func__, timeout);
    return status;
}



void OEM_CancelTimer(void *TimerRef)
{
    mbtk_os_timer_stop(g_oem_timer);
}

int OEM_getSimIccid(char *iccid)
{
    int iret = 0;
    char imeibuf[20] = {0};

    MLOG_D(MLOG_POC, POC,"%s:\n", __func__);

    if(iret = mbtk_sim_get_iccid(iccid) != mbtk_device_api_err_none)
    {
        return -1;
    }

    return 0;
}

int mbtk_oem_netstatus_convert(ol_REG_STATUS_INFO *info)
{
    int ret_mode = 0;
    MLOG_D(MLOG_POC, POC,"%s:\n", __func__);

    switch(info->act)
    {
        case MBTK_NW_ACT_GSM:
            ret_mode =  NETWORK_MODE_GSM;
            break;
        case MBTK_NW_ACT_UTRAN:
            ret_mode =  NETWORK_MODE_CDMA;
            break;
        case MBTK_NW_ACT_UTRAN_HSDPA:
        case MBTK_NW_ACT_UTRAN_HSUPA:
        case MBTK_NW_ACT_UTRAN_HSPA:
            ret_mode =  NETWORK_MODE_WCDMA;
            break;
        case MBTK_NW_ACT_EUTRAN:
            ret_mode = NETWORK_MODE_LTE;
            break;
    }

    if(info->state == MBTK_NW_REG_STA_NOT_REGED)
    {
        ret_mode = NETWORK_MODE_NONE;
    }
    return ret_mode;
}


#define CHECK_RET(ret) if(ret!=0) return -1

int OEM_GetNetworkInfo(oem_network_info_s *network_info)
{
    int csq ;
    ol_REG_STATUS_INFO reg_info = {0};
    ol_OPERATOR_INFO operator_info = {0};
    char sim_status = 0;
    int ret=0;
    MLOG_D(MLOG_POC, POC,"OEM_GetNetworkInfo");

    mbtk_get_sim_status(&sim_status);
    
    MLOG_D(MLOG_POC, POC,"OEM_GetNetworkInfo sim_status %d", sim_status);
    if(sim_status != mbtk_sim_ready)
    {
        return -1;
    }
	
	ret = mbtk_get_reg_status_ex(&reg_info);
	MLOG_D(MLOG_POC, POC,"mbtk_get_reg_status sim_status %d,state %d, act %d", ret, reg_info.state,reg_info.act);
	#if 0
    while(1)
    {
		ret = mbtk_get_reg_status_ex(&reg_info);
		MLOG_D(MLOG_POC, POC,"mbtk_get_reg_status sim_status %d,state %d, act %d", ret, reg_info.state,reg_info.act);
        if(ret==0 && reg_info.state!=MBTK_NW_REG_STA_REG_HPLMN&&reg_info.state!=MBTK_NW_REG_STA_REG_ROAMING)
        {
            mbtk_os_task_sleep(200);
        }
        else
        {
            break;
        }
    }
	
	#endif

    CHECK_RET(ret);
    ret = mbtk_get_csq(&csq);

    MLOG_D(MLOG_POC, POC,"mbtk_get_csq  %d", csq);
    CHECK_RET(ret);
    
    network_info->rssi = csq*2-113;
    network_info->cell_id = reg_info.cid;
    network_info->lac_or_tac = reg_info.lac;

    network_info->network_mode = mbtk_oem_netstatus_convert(&reg_info);
    if(reg_info.state!=MBTK_NW_REG_STA_REG_HPLMN && 
       reg_info.state!=MBTK_NW_REG_STA_REG_ROAMING)
    {
        network_info->network_status = NETWORK_UNREGISTER;
    }
    else
    {
        network_info->network_status = NETWORK_REGISTER;
    }

    ret = mbtk_get_operator_info(&operator_info);
    MLOG_D(MLOG_POC, POC,"mbtk_get_operator_info ret %d", ret);
    CHECK_RET(ret);
    
    memcpy(network_info->mcc, operator_info.mcc, sizeof(operator_info.mcc));
    memcpy(network_info->mnc, operator_info.mnc, sizeof(operator_info.mnc));

    MLOG_D(MLOG_POC, POC,"OEM_GetNetworkInfo %d,%d,%d, %d,%s, %s , %d", network_info->rssi, network_info->cell_id,
        network_info->network_mode, network_info->network_status,network_info->mcc, network_info->mnc,
        network_info->lac_or_tac );
    return 0;
}


oem_sim_status_type_e OEM_getSimStatus()
{
    char sim_status = 0;
    int ret=0;

    if(mbtk_get_sim_status(&sim_status) == 0)
    {
        if(sim_status == mbtk_sim_ready)
        {
            ret = POC_SIM_STATUS_READY;
        }
        else if(sim_status == mbtk_sim_not_insert)
        {
            ret = POC_SIM_STATUS_NOT_INSERT;
        }
    }
    return ret;
}

void OEM_FotaUpdate(char *path)
{
}

unsigned short OEM_ConvertFourChars(char *strFourChars);

extern void mbtk_set_volume(int level);

#if defined(MBTK_TTS_SUPPORT_ivTTS)
int OEM_TTS_Spk(int type, char *atxt)
{
	#ifdef MBTK_TTS_SUPPORT
	uint16 txt_len	= 0;
	uint16 *atxt_convert = (uint16 *)atxt;
	int i =0;	
	
	if(type ==0 && atxt ==NULL )
	{
	  OEM_TTS_Stop();
	  return 0;
	}
	
	if(atxt == NULL){
		return 0;
	}

	if(type == TTS_PLAY_GBK)
	{
		txt_len = strlen(atxt);
	}
	else if(type == TTS_PLAY_UTF16LE)
	{	
		uint16 *pTextBuf_U16 = atxt;
		txt_len = strlen(atxt)/4;

		if(txt_len!=0)
		{
			while(i< txt_len)
			{
				*atxt_convert = OEM_ConvertFourChars(atxt+i*4);
				i++;
				atxt_convert++;
			}
			*atxt_convert = 0;
		}
	}
	
	mbtk_tts_set_cb(OEM_TTS_Status_CB);
	mbtk_tts_spk(atxt, txt_len, type, 0);
	#endif
	return 0;
}
#else

int OEM_TTS_Spk(int type, char *atxt)
{
	#ifdef MBTK_TTS_SUPPORT
	uint16 txt_len	= 0;
	uint16 *atxt_convert = (uint16 *)atxt;
	int i =0;	
	
	MLOG_D(MLOG_POC, POC,"OEM_TTS_Spk %d: %s\r\n",type, atxt);

	if(type ==0 && atxt ==NULL){
	  OEM_TTS_Stop();
	  return 0;
	}

	if(atxt == NULL)
		return 0;

	if(type == TTS_PLAY_GBK)
	{
		txt_len = strlen(atxt);
	}
	else if(type == TTS_PLAY_UTF16LE)
	{	
		uint16 *pTextBuf_U16 = atxt;
		while(1)
		{
			if(0 == *(pTextBuf_U16+txt_len))
				break;
			txt_len++;
		}

		if(txt_len!=0)
		{
			while(i< txt_len)
			{
				*atxt_convert = OEM_ConvertFourChars(atxt+i*4);
				i++;
				atxt_convert++;
			}
			*atxt_convert = 0;
		}
	}
	
	MLOG_D(MLOG_POC, POC,"OEM_TTS_Spk len %d\r\n", txt_len);
	mbtk_tts_set_cb(OEM_TTS_Status_CB);
	mbtk_tts_spk(atxt, txt_len, type, 0);
	#endif
	return 0;
}

#endif


int OEM_PlayTone(int Type,  int time)
{
	MLOG_D(MLOG_POC, POC,"OEM_PlayTone\r\n");
	mbtk_oem_play_tone_ex();
	return 0;
}



int  OEM_PendMessage(oem_poc_user_msg_s *msg);
extern mbtk_msgqref g_oem_msgq;
int OEM_PostMessage(oem_poc_user_msg_s msg)
{
    oem_msg_struct msg_str= {0};
    mbtk_os_status osaStatus;
    int ret = 0;
    //MLOG_D(MLOG_POC, POC,"%s: msg ", __func__);

    if(!g_oem_msgq)
    {
        return -1;
    }

    msg_str.msg_id = MI_OEM_REQ;
    msg_str.param = malloc(sizeof(oem_poc_user_msg_s));
    memset(msg_str.param, 0, sizeof(oem_poc_user_msg_s));
    memcpy(msg_str.param, &msg,  sizeof(oem_poc_user_msg_s));
    osaStatus = mbtk_os_msgq_send(g_oem_msgq, OEM_MSGQ_MSG_SIZE, &msg_str,MBTK_OS_NO_SUSPEND);
    
   // MLOG_D(MLOG_POC, POC,"%s: %dsend msg done.", __func__, osaStatus);
    return ret;
    
}

void oem_thread(void *arg)
{
    oem_msg_struct req;

    UINT32 reqHandle;
    oem_poc_user_msg_s *msg_s;
    while(1)
    {
        memset(&req,0,OEM_MSGQ_MSG_SIZE);

        mbtk_os_msgq_recv(g_oem_msgq, (void *)&req, OEM_MSGQ_MSG_SIZE, MBTK_OS_SUSPEND);
        msg_s = req.param;
        
        if(req.msg_id == MI_OEM_REQ)
        {            
            OEM_PendMessage(msg_s);
        }

        free(msg_s);
    }
}

typedef struct
{
    char devNm[20];
    unsigned short devVersion;
    char fotaAddr[50];
    unsigned short fotaPort;
}fota_info_t;

void Fota_setInfo(fota_info_t data)
{
}

int OEM_FotaSizeInit(int size)
{
    return 0;
}

typedef enum {
    NO_SERVICE = 0,
    SERVICE_AVAILABLE = 1, 
    OEM_NET_MAX,
}oem_net_status;

typedef enum {
    CALL_BACK_REPORT_RECORD_DATA,           //  上报录音数据
    CALL_BACK_REPORT_NETWORK_STATUS,        //  上报注网状�?
    CALL_BACK_REPORT_AT_POC_CMD,            //  上报 at+poc 指令
    CALL_BACK_REPORT_USER_MSG,              //  上报用户消息 
    CALL_BACK_REPORT_CONNECT_TCP_ID,        //  上报已连�?tcp sokcet 标识 
    CALL_BACK_REPORT_RECV_TCP_ID,           //  上报可读 tcp socket 标识 
    CALL_BACK_REPORT_RECV_UDP_ID,           //  上报可读 udp socket 标识 
    CALL_BACK_REPORT_PLAY_BUFFER_REST_DATA,  //  上报  poc  播放缓存剩余    poc 数据
    CALL_BACK_REPORT_TTS_STATUS,            //  上报 tts 播放状�?
    CALL_BACK_REPORT_PPP_STATUS,            //  上报 ppp 状�?
    CALL_BACK_REPORT_TCP_CLOSE_ID,
    CALL_BACK_MAX
}oem_poc_call_back_type_e;


//录音数据上报回调函数
typedef void (* fn_type_report_record_data_cb)(const char* data, int length);
///网络状�?上报回调函数
typedef void (* fn_type_report_network_status_cb)(oem_net_status result);
//AT+POC 命令上报回调函数
typedef void (* fn_type_report_at_poc_cmd_cb)(char* buf ,int len);
//用户自定义消息上报回调函�?
typedef void (* fn_type_report_user_msg_cb)(oem_poc_user_msg_s msg);
//TCP 连接成功上报回调函数
typedef void (* fn_type_report_connect_tcp_id_cb)(unsigned char socket_id);
//TCP socket 可读上报回调函数
typedef void (* fn_type_report_recv_tcp_id_cb)(unsigned char socket_id);
//UDP socket 可读上报回调函数
typedef void (* fn_type_report_recv_udp_id_cb)(unsigned char socket_id);
//播放缓冲区剩余数据量上报回调函数
typedef void (* fn_type_report_play_buffer_rest_data_cb)(int rest_data);
//TTS 播放状�?上报回调函数
typedef void (* fn_type_report_tts_status_cb)(int status);
//数据链路状�?上报回调函数
typedef void (* fn_type_report_ppp_status_cb)(oem_ppp_status status);
typedef void (* fn_type_report_tcp_close_id_cb)(unsigned char socket_id);


static fn_type_report_record_data_cb record_cb;
static fn_type_report_network_status_cb network_status_cb;
static fn_type_report_at_poc_cmd_cb at_poc_cmd_cb;
static fn_type_report_user_msg_cb user_msg_cb;
static fn_type_report_connect_tcp_id_cb connect_tcp_id_cb;
static fn_type_report_recv_tcp_id_cb recv_tcp_id_cb;
static fn_type_report_recv_udp_id_cb recv_udp_id_cb;
static fn_type_report_play_buffer_rest_data_cb play_buffer_rest_data_cb;
static fn_type_report_tts_status_cb tts_status_cb;
static fn_type_report_ppp_status_cb ppp_status_cb;
static fn_type_report_tcp_close_id_cb tcp_close_cb;
void OEM_Record(const char* data, int length)
{
    if(record_cb)
        record_cb(data, length);
}

void OEMNetworkStatusChange(oem_net_status result)
{
    MLOG_D(MLOG_POC, POC,"OEMNetworkStatusChange %d\r\n", result);
    if(network_status_cb)
    {
        network_status_cb(result);
    }
    if(ppp_status_cb)
    {
        ppp_status_cb(result);
    }
}

void OEMPOC_AT_Recv(char* buf ,int len)
{
    MLOG_D(MLOG_POC, POC,"OEMPOC_AT_Recv %s\r\n", buf);
    if(at_poc_cmd_cb)
    {
        at_poc_cmd_cb(buf, len);
    }
}

void OEMSocket_TCP_Connected(unsigned char socket_id)
{
    MLOG_D(MLOG_POC, POC,"%s:\n", __func__);
    if(connect_tcp_id_cb)
    {
        MLOG_D(MLOG_POC, POC,"%s: %d\n", __func__, socket_id);
        connect_tcp_id_cb(socket_id);
    }
}

int OEMSocket_RecvTCPDataCB(unsigned char socket_id)
{
    if(recv_tcp_id_cb)
    {
        recv_tcp_id_cb(socket_id);
    }
    return 0;
}

int OEMSocket_RecvUDPDataCB(unsigned char socket_id)
{
    if(recv_udp_id_cb)
    {
        recv_udp_id_cb(socket_id);
    }
    return 0;
}

int OEMSocket_TcpCloseCB(unsigned char socket_id)
{
    if(tcp_close_cb)
    {
        tcp_close_cb(socket_id);
    }
    return 0;
}

void OEM_TTS_Status_CB(int status)
{
    if(tts_status_cb)
    {
        tts_status_cb(status);
    }
}

int  OEM_PendMessage(oem_poc_user_msg_s *msg)
{
    oem_poc_user_msg_s msg_str = {0};
    if(user_msg_cb)
    {
        if(msg)
        {
            memcpy(&msg_str, msg, sizeof(oem_poc_user_msg_s));
        }
        //MLOG_D(MLOG_POC, POC,"OEM_PendMessage %s\r\n", msg->MsgData);
        user_msg_cb(msg_str);
    }
}

void OEMPlayBufferAvailCB(int rest_data)
{
    MLOG_D(MLOG_POC, POC,"%s:\n", __func__);
    if(play_buffer_rest_data_cb)
    {
        play_buffer_rest_data_cb(rest_data);
    }
}

void OEM_RegisterUserCallBack(oem_poc_call_back_type_e type, void *callback)
{

    MLOG_D(MLOG_POC, POC,"OEM_RegisterUserCallBack %d\r\n", type);

    switch(type)
    {
        case CALL_BACK_REPORT_RECORD_DATA:
            record_cb = callback;
            break;
        case CALL_BACK_REPORT_NETWORK_STATUS:
            network_status_cb = callback;
            break;
        case CALL_BACK_REPORT_AT_POC_CMD:
            at_poc_cmd_cb = callback;
            break;
        case CALL_BACK_REPORT_USER_MSG:
            user_msg_cb = callback;
            break;
        case CALL_BACK_REPORT_CONNECT_TCP_ID:
            connect_tcp_id_cb = callback;
            break;
        case CALL_BACK_REPORT_RECV_TCP_ID:
            recv_tcp_id_cb = callback;
            break;
        case CALL_BACK_REPORT_RECV_UDP_ID:
            recv_udp_id_cb = callback;
            break;
        case CALL_BACK_REPORT_PLAY_BUFFER_REST_DATA:
            play_buffer_rest_data_cb = callback;
            break;
        case CALL_BACK_REPORT_TTS_STATUS:
            tts_status_cb = callback;
            break;
        case CALL_BACK_REPORT_PPP_STATUS:
            //PPP暂时不处�?
            ppp_status_cb = callback;
            break;
        case CALL_BACK_REPORT_TCP_CLOSE_ID:
            tcp_close_cb = callback;
        default:
            break;
    }
}

#endif /*MBTK_POC_SUPPORT_HAWK*/
