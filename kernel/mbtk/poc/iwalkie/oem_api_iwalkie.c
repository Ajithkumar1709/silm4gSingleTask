#ifdef MBTK_POC_SUPPORT_IWALKIE
#include <stdarg.h>
#include "mbtk_nw_api.h"
#include "mbtk_os.h"
#include "mbtk_sim_api.h"
#include "mbtk_device_api.h"
#include "oem_api.h"
#include "oem_api_iwalkie.h"
#include "mbtk_audio_api.h"
#include "mbtk_log.h"
//#include "mbtk_audio_pcm.h"
//#include "mbtk_uart_api.h"

#include "oem_iwalkie_type.h"
struct ip_addr 
{
	unsigned long addr;
};

typedef struct ip_addr ip_addr_t;


struct ip6_addr {
  unsigned long addr[4];
};


typedef struct ip6_addr ip6_addr_t;



typedef struct 
{
	unsigned char iptype;
	union 
	{
		ip_addr_t ipv4;
		ip6_addr_t ipv6;
	}mbtk_ip_addr;
}mbtk_ipaddr_struct;

#define MBTK_TEST_SOC_SER_IPV6

#define SOCKET_LOCAL_CID mbtk_cid_index_2
#define LOCAL_CID_PDN_TYPE mbtk_data_call_v6

#define MBTK_OEM_SAMPLE_RATE 8000
#define MBTK_OEM_CHANNEL 1


extern uint8_t network_registed;
//extern UINT32 g_atHandle;
extern mbtk_tts_info *mbtk_get_tts_info();
extern void mbtk_oem_Play_CB(int rest_data);

extern mbtk_device_api_err_enum mbtk_get_imei(uint8_t *imei);
extern mbtk_sim_api_err_enum mbtk_sim_get_imsi(uint8_t *imsi);
extern mbtk_sim_api_err_enum mbtk_sim_get_iccid(uint8_t *iccid);
//extern broad_init(void);
void poc_ui_enter(char *default_platform, char *default_dns, int is_broad, int is_abroad);
extern void bnd_printf(void *fmt,...);

mbtk_msgqref POC_Msg = NULL;
extern void mbtk_set_volume(int level);////TTS
int poc_volume;

// Tone
extern int mbtk_oem_play_tone(int type,int gain,int onoff);

int OEM_PlayTone(int Type,  int time)
{
	mbtk_app_log("OEM_PlayTone\r\n");
	mbtk_oem_play_tone(Type,0,1);
	mbtk_os_task_sleep(time/5);
	mbtk_oem_play_tone(Type,0,0);

	
	//mbtk_oem_play_tone_ext(Type,1);
	//mbtk_os_task_sleep(time/5);
	//mbtk_oem_play_tone_ext(Type,0);
}

int mbtk_bnd_tts_get_status()
{
    int status = 0;
	#ifdef MBTK_TTS_SUPPORT
    mbtk_tts_info *info = mbtk_get_tts_info();
    status = info->play_status;
	#endif
    return status;
}

void lib_oem_tts_play_end_cb(void)
{

}

int lib_oem_uart_cb(char* data, int size)
{
    mbtk_app_log("[audio-engine]uart receive data:%s, size:5d\r\n", data, size);
    iwalkie_at_parse_uart_buffer(data, size);
}

unsigned char lib_get_cur_battery_percent(void)
{
    return 50;
}

mbtk_bnd_at_struct at_info[PARA_TYPE_MAX] = {
                                    {"open",BND_PARA_OPEN,3},
                                    {"accountfirst",BND_PARA_ACCOUNTFIRST,2}, 
                                    {"setaccount",BND_PARA_SETACCOUNNT,5}, 
                                    {"getaccount",BND_PARA_GETACCOUNNT,1},
                                    {"login",BND_PARA_LOGIN,1},
                                    {"logout",BND_PARA_LOGOUT,1},
                                    {"entergroup",BND_PARA_ENTERGROUP,2},
                                    {"singlecall",BND_PARA_SINGLECALL,2},
                                    {"ptt",BND_PARA_PTT,2},
                                    {"groups",BND_PARA_GROUPS,3},
                                    {"members",BND_PARA_MEMBERS,4},
                                    {"loc",BND_PARA_LOC,7},
                                    {"groupnum",BND_PARA_GROUPNUM,1},
                                    {"membernum",BND_PARA_MEMBERNUM,2},
                                    {"setnotify",BND_PARA_SETNOTIFY,4},
                                    {"localtime",BND_PARA_LOCATIME,2},
                                    {"setping",BND_PARA_SETPING,2},
                                    {"ping",BND_PARA_PING,2},
                                    {"ttslang",BND_PARA_TTSLANG,2},
                                    {"currentuser",BND_PARA_CURRENTUSER,1},
                                    {"tonevol",BND_PARA_TONEVOL,2},
                                    {"toneopen",BND_PARA_TONEOPEN,2},
                                    {"expired",BND_PARA_EXPIRED,2},
                                    {"upgrade",BND_PARA_UPGRADE,2},
                                    {"autoleavetime",BND_PARA_AUTOLEAVETIME,2},
                                    {"leavetempcall",BND_PARA_LEAVETEMPCALL,2},
                                    {"callusers",BND_PARA_CALLUSER,4},
                                 };


//将utf16大端转换成小�?
void mbtk_bnd_poc_unicodetrans(char *str1, int len)
{
    MLOG_D(MLOG_POC, POC,"%s len:%d,str:%s\r\n",__func__,len,str1);
    char *str = str1;
    char c1;
    char c2;
    int i;
    for (i = 0; i < len; i++)
    {
        c1 = *str;
        c2 = *(str + 1);

        *str = *(str + 2);
        *(str + 1) = *(str + 3);

        *(str + 2) = c1;
        *(str + 3) = c2;
        str += 4;
        len -= 4;
    }
    MLOG_D(MLOG_POC, POC,"%s str %s\r\n",__func__,str);
}

bnd_para_enum mbtk_bnd_para_cmp(char* buf ,int len)
{
    int i;
    mbtk_app_log("%s buf %s\r\n",__func__,buf);
    for(i=0;i < PARA_TYPE_MAX;i++)
    {
        if(!memcmp(buf,at_info[i].str, len))
        {
            return at_info[i].at_type;
        }
    }
    return BND_PARA_MAX;
}

void lib_oem_player_need_data_len_cb(int datalen)
{
    mbtk_app_log("%s datalen %d\r\n",__func__,datalen);
}

void mbtk_bnd_api_load_helper(void)
{
    printf("mbtk_audio_api_load_helper  \n");
}


int mbtk_bnd_para_handle(char *buf,int buff_len)
{
    int ret = -1;
    int para_type = 0;
    int para_num = 0;
    int pos = 0;
    int len = 0;
    
    mbtk_app_log("%s enter...",__func__);
    if(BND_PARA_MAX == (para_type = mbtk_bnd_para_cmp(buf,buff_len)))
    {
        return 0;
    }

    para_num = at_info[para_type].para_num;
    mbtk_app_log("%s:para_num %d",__func__,para_num);
    return para_num;
}

void poc_log_output(void *fmt,...)
{
	va_list ap;
	char buffer[128] = {0};
	char *p = buffer;
	static int fatal_uart_inited = 0;
    int len = 0;
	memset(buffer, 0, sizeof(buffer));
	len = sprintf(buffer,"bnd:",3);
	p+=len;
	va_start(ap, fmt);
	vsnprintf(p, sizeof(buffer)-4, fmt, ap);
	va_end(ap);

	//uart_printf("%s\n",buffer);
	mbtk_app_log("%s\n",buffer);//tpc LOG
	
	//DIAG_FILTER(MBTK, AT, ATRESP, DIAG_INFOMRATION)
	//diagPrintf("%s",buffer);
}


void OEMPOC_AT_Recv(char* buf ,int len)
{
    MLOG_D(MLOG_POC, POC,"%s:%s\r\n",__func__,buf);
    lib_oem_uart_cb(buf,len);
}


int lib_oem_tts_status(void)
{
    MLOG_D(MLOG_POC, POC,"%s",__func__);
	
#ifdef MBTK_TTS_SUPPORT
    return(mbtk_bnd_tts_get_status());
#else
	return 0;
#endif
}

int lib_oem_tts_play(char *text)
{
    int ret = -1;
    MLOG_D(MLOG_POC, POC,"%s:%s\r\n",__func__,text);
#ifdef MBTK_TTS_SUPPORT

    mbtk_oem_stop_play();
    
    mbtk_bnd_play_tts(text);
#endif	
	return 0;
}

int lib_oem_tts_stop(void)
{
    MLOG_D(MLOG_POC, POC,"%s\r\n",__func__);
	
#ifdef MBTK_TTS_SUPPORT
    mbtk_oem_Play_CB(0);
    return mbtk_oem_stop_play();
#else
	return 0;
#endif
}

int lib_oem_start_record(void)
{
    MLOG_D(MLOG_POC, POC,"%s\r\n",__func__);
    mbtk_oem_set_record_callback(lib_oem_record_cb);
    return mbtk_oem_start_recorder(MBTK_OEM_SAMPLE_RATE,MBTK_OEM_CHANNEL,0);//8k 16bit mono
}


int lib_oem_stop_record(void)
{
    return mbtk_oem_stop_record();
}

int lib_oem_start_play(void)
{
	int ret = 0;
    MLOG_D(MLOG_POC, POC,"lib_oem_start_play\r\n");
#ifdef MBTK_TTS_SUPPORT

	//mbtk_oem_stop_play();//3E�ϲ������η�������������
	mbtk_tts_stop();

	ret = mbtk_oem_start_player(MBTK_OEM_SAMPLE_RATE,MBTK_OEM_CHANNEL,0);

	if(ret == 0)
    	mbtk_oem_set_play_callback(lib_oem_player_need_data_len_cb);
#endif
	MLOG_D(MLOG_POC, POC,"lib_oem_start_play end %d\r\n", ret);
    return ret;
}

int lib_oem_stop_play()
{
    MLOG_D(MLOG_POC, POC,"mbtk_bnd_stop_play\r\n");
	mbtk_oem_Play_CB(0);
	return mbtk_oem_stop_play();
}

void lib_oem_tts_call(int type)
{
    MLOG_D(MLOG_POC, POC,"lib_oem_tts_call type:%d\r\n",type);
	
#ifdef MBTK_TTS_SUPPORT
    if(0 == type)//(MBTK_TTS_NONE == type)
        lib_oem_tts_play_end_cb();
#endif
}

bool mbtk_tts_bnd_check_can_stop()
{

#ifdef MBTK_TTS_SUPPORT
	mbtk_tts_info *info = mbtk_get_tts_info();
	if(info->play_status  == MBTK_TTS_PLAY)
		return false;
#endif
	return true;	
}

void mbtk_bnd_play_tts(char* atxt)
{
    uint16 txt_len  =0;
    uint16 *atxt_convert = (uint16 *)atxt;
    int i =0;
    MLOG_D(MLOG_POC, POC,"OEM_TTS_Spk %s\r\n", atxt);
#ifdef MBTK_TTS_SUPPORT

extern int tts_volume;//////TTS
 if(atxt == NULL)
  return 0;
 
 uint16 *pTextBuf_U16 = atxt;
 while(1)
 {
  if(0 == *(pTextBuf_U16+txt_len))
   break;
  txt_len++;
 }

	mbtk_bnd_poc_unicodetrans(atxt,txt_len*4);
 
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

    MLOG_D(MLOG_POC, POC,"mbtk_bnd_play_tts len %d\r\n", i);

    if(mbtk_tts_bnd_check_can_stop())
        mbtk_tts_stop();

    mbtk_tts_set_cb(lib_oem_tts_call);
 	MLOG_D(MLOG_POC, POC,"OEM_Play TTS %d\r\n", poc_volume);
 //mbtk_set_volume(tts_volume);////TTS
    mbtk_tts_spk(atxt, txt_len, 1,1);//MBTK_TTS_PLAY);
#endif    
    return 0;
}

int lib_oem_play(const char* data, int length)
{
    MLOG_D(MLOG_POC, POC,"lib_oem_play %d,%x\r\n",length,data);
	mbtk_oem_play_set_buffer(data,length);
	MLOG_D(MLOG_POC, POC,"OEM_Play %d\r\n", poc_volume);
	//mbtk_set_volume(poc_volume);
	mbtk_oem_play_resume();
	return mbtk_oem_start_play();
}

int lib_oem_play_tone(int type)
{
    MLOG_D(MLOG_POC, POC,"lib_oem_play_tone\r\n");
	mbtk_oem_play_tone_ex();

	return 0;

	
}

void poc_uart_close()
{
    MLOG_D(MLOG_POC, POC,"%s:", __func__);
}


void poc_uart_open()
{
    MLOG_D(MLOG_POC, POC,"%s:", __func__);
}

int lib_oem_ota_done(void)
{
    MLOG_D(MLOG_POC, POC,"%s:", __func__);
}
int lib_oem_ota_init(void)
{
    MLOG_D(MLOG_POC, POC,"%s:", __func__);
}
int lib_oem_ota_process(char* data, unsigned int len, unsigned int total)
{
    MLOG_D(MLOG_POC, POC,"%s:", __func__);
}

char* lib_oem_get_model(void)
{
    char *model_str = NULL;
    mbtk_device_firmware_ver_struct *version_struct;
    if(0 != mbtk_get_firmware_version(&version_struct))
    {
        return NULL;
    }
    else
    {
        MLOG_D(MLOG_POC, POC,"get_firmware_version projectname[%s]\n", version_struct->projectname);
        model_str = version_struct->projectname;
    }
    MLOG_D(MLOG_POC, POC,"lib_oem_get_model:%s", model_str); 
    return model_str;
}

void lib_oem_get_rssi(int *rssi, int *carrier)
{
    int scsq;
    int srssi;
    mbtk_get_csq(&scsq);
    srssi = scsq*2-113;
    MLOG_D(MLOG_POC, POC,"%s:rssi %d", __func__,srssi);
    *rssi = srssi;
    *carrier = 4;
}

//平台自动激活通道
int lib_oem_socket_net_open(void)
{
   MLOG_D(MLOG_POC, POC,"%s", __func__); 
   return 1;
}

int lib_oem_net_close(void)
{
   MLOG_D(MLOG_POC, POC,"%s", __func__); 
   return 1;
}

int lib_oem_reset_ps(void)
{
   MLOG_D(MLOG_POC, POC,"%s", __func__); 
   return 1;
}


int lib_oem_get_device_serial_number(char* data)
{
    MLOG_D(MLOG_POC, POC,"%s", __func__); 
    char imei[20]={0};
    char meid[20]={0};
    int ret = mbtk_get_imei(imei);
    if(-1 == ret)
        return ret;

    MLOG_D(MLOG_POC, POC,"%s:imei %s", __func__,imei); 
    if(strlen(imei)>=15)
	{
		strncpy(meid,imei,14);
		sprintf(data, "%s\n%s\n", imei, meid);
		return 0;
	}
    return -1;
}

int lib_oem_send_uart(const char* data, int size)
{
    MLOG_D(MLOG_POC, POC,"%s:size %d,data %s", __func__,size,data); 
//    ol_Uart_Write(OL_UART_PORT_STUART, data,size);
    mbtk_app_log("[audio-engine]%s:size %d,data %s", __func__,size,data);
    atRespStr( 1, 0, 0, data);
	return drv_uart_visual_write(data, size);
}

int lib_oem_get_sim_serial_number(char* data)
{
    MLOG_D(MLOG_POC, POC,"%s", __func__); 
    char imsi[100]={0};
    char iccid[100]={0};
    int ret = mbtk_sim_get_imsi(imsi);
    if(-1 == ret)
        return -1;
    mbtk_sim_get_iccid(iccid);
    if(-1 == ret)
        return -1;

    MLOG_D(MLOG_POC, POC,"%s:iccid:%s,imsi:%s", __func__,iccid,imsi); 
    sprintf(data, "%s\n%s\n", iccid, imsi);
    MLOG_D(MLOG_POC, POC,"aagggaaa%s:%s", __func__,data);
	return 0;
}

char* lib_oem_get_system_version(void)
{
    char *ver_str = NULL;
    mbtk_device_firmware_ver_struct *version_struct;
    if(0 != mbtk_get_firmware_version(&version_struct))
    {
        return NULL;
    }
    else
    {
        MLOG_D(MLOG_POC, POC,"get_firmware_version softversion[%s]\n", version_struct->softversion);
        ver_str = version_struct->softversion;
    }
    MLOG_D(MLOG_POC, POC,"lib_oem_get_system_version:%s", ver_str); 
    return ver_str;
}
#if 0
int lib_oem_socket_get_net_status(void)
{
    //return network_registed;
     return mbtk_get_data_call_state();//tpc  220119
}
#endif
int lib_oem_socket_get_net_status(void)
{
	//return network_registed;
    MBTK_REG_STATUS_INFO reg_info = {0};
    int ret=0;
	
	ret = mbtk_get_reg_status_ex(&reg_info);
	MLOG_D(MLOG_POC, POC,"mbtk_get_reg_status sim_status %d,state %d, act %d", ret, reg_info.state,reg_info.act);

	int reg_state = mbtk_get_data_call_state();
	if(reg_state)
	{
		mbtk_ipaddr_struct taddr;
		MLOG_D(MLOG_POC, POC,"bnd_network_registed succ");
		int ret = mbtk_get_hostbyname("www.baidu.com", &taddr);
		if(ret == 0)
		{
			return 1;
		}
	}
	return 0;
}


#define CHECK_RET(ret) if(ret!=0) return -1

int lib_oem_device_bts(int* mcc,int* mnc,int* lac, int* cid)
{
	int csq ;
	MBTK_REG_STATUS_INFO reg_info = {0};
	MBTK_OPERATOR_INFO operator_info = {0};
	char sim_status = 0;
	int ret=0;
	MLOG_D(MLOG_POC, POC,"lib_oem_device_bts");

	mbtk_get_sim_status(&sim_status);
	
	MLOG_D(MLOG_POC, POC,"%s sim_status %d",__FUNCTION__, sim_status);
	if(sim_status != mbtk_sim_ready)
	{	
		return -1;
	}

	while(1)
	{
		ret = mbtk_get_reg_status(&reg_info, 1);
		MLOG_D(MLOG_POC, POC,"%s ret %d",__FUNCTION__, ret);
		if(ret==0 && reg_info.state!=MBTK_NW_REG_STA_REG_HPLMN&&reg_info.state!=MBTK_NW_REG_STA_REG_ROAMING)
			mbtk_os_task_sleep(200);
		else
			break;
	}
	MLOG_D(MLOG_POC, POC,"%s ret %d",__FUNCTION__, ret);

	CHECK_RET(ret);
		
	*cid = reg_info.cid;
	*lac = reg_info.lac;

	ret = mbtk_get_operator_info(&operator_info);
	MLOG_D(MLOG_POC, POC,"%s ret %d",__FUNCTION__, ret);
	CHECK_RET(ret);
	sscanf(operator_info.mcc, "%x", mcc);
	sscanf(operator_info.mnc, "%x", mnc);

	MLOG_D(MLOG_POC, POC,"lib_oem_device_bts %d,%d,%d,%d", *cid, *lac, *mcc, *mnc);
	return 0;
}


void poc_ui_Select(char *default_platform, char *default_dns, int is_broad, int is_abroad)
{ 
	mbtk_app_log("poc_ui_Select11111111111111");
}

void mbtk_iwalkie_init()
{
    MLOG_D(MLOG_POC, POC,"mbtk_bnd_init");
}

#if 0
//打开网络
int lib_oem_socket_net_open(void)
{

}

//获取网络状�?
int lib_oem_socket_get_net_status(void)
{

}

//关闭网络
int lib_oem_net_close(void)
{

}

//获取网络信噪�?
int lib_oem_get_rssi(void)
{

}

//获取设备信息(IMEI和MEID)
int lib_oem_get_device_serial_number(char* data)
{

}

//获取SIM卡信�?ICCID和IMSI)
int lib_oem_get_device_serial_number(char* data)
{

}


//获取系统版本
char* lib_oem_get_system_version(void)
{

}

//发送uart数据
int lib_oem_send_uart(const char* data, int size)
{

}

//系统相关接口
//创建线程
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
void *(*start_routine) (void *), void *arg)
{

}

//等待线程结束
int pthread_join(pthread_t thread, void **retval)
{

}

//获取线程ID
int pthread_t pthread_self(void);
{

}

//互斥�?
int pthread_mutex_lock(pthread_mutex_t *mutex)
{

}

//互斥锁解�?
int pthread_mutex_unlock(pthread_mutex_t *mutex)
{

}

//销毁互斥锁
int pthread_mutex_destroy(pthread_mutex_t *mutex)
{

}

//条件变量初始�?
int pthread_cond_init(pthread_cond_t *cv, const pthread_condattr_t *cattr)
{

}

//等待条件变量
int pthread_cond_wait(pthread_cond_t *cv, pthread_mutex_t *mutex)
{

}

//解除条件变量等待
int pthread_cond_signal(pthread_cond_t *cv)
{

}

//阻塞条件变量到指定时�?
int pthread_cond_timedwait(pthread_cond_t *cv, pthread_mutex_t *mp, const
structtimespec * abstime)
{

}

//释放条件变量
int pthread_cond_destroy(pthread_cond_t *cv)
{

}

//时间相关
//获取当前精确时间
int gettimeofday(struct timeval *tv, struct timezone *tz)
{

}

//获取当前时间到秒
time_t time(time_t *calptr)
{

}

//转换为本地时�?
struct tm*localtime(const time_t *calptr)
{

}

//返回自设备启动后的毫秒数
DWORD GetTickCount(void)
{

}

//延时（秒�?
unsigned int sleep (unsigned int seconds)
{

}

//延时（毫秒）
int usleep (useconds_t usec)
{

}

//内存
void *malloc(size_t size);
{

}
void *calloc(unsigned n, unsigned size)
{

}
void *realloc(void *ptr, size_t size)
{

}
void free(void *ptr)
{

}
void *memset(void *s, int c, size_t n)
{

}

void *memcpy(void *dest, const void *src, size_t n)
{

}
void *memmove(void *dest, const void *src, size_t n)
{

}
char *strcpy(char *dest, const char *src)
{

}
char *strncpy(char *dest, const char *src, size_t n)
{

}

int memcmp(const void *s1, const void *s2, size_t n)
{

}
int strcmp(const char *s1, const char *s2)
{

}
int strncmp(const char *s1, const char *s2, size_t n)
{

}
size_t strlen(const char *s)
{

}

char *strchr(const char *s, int c)
{

}

char *strtok(char *str, const char *delim)
{

}

char *strstr(const char *haystack, const char *needle)
{

}

char *strcat(char *dest, const char *src)
{

}

char *strncat(char *dest, const char *src, size_t n)
{

}

int vsprintf(char *str, const char *format, va_list ap)
{

}
int vsnprintf(char *str, size_t size, const char *format, va_list ap)
{

}
int fprintf(FILE *stream, const char *format, ...)
{

}

char *strdup(const char *s)
{

}

//5.5 文件操作
//文件判断
int access(const char *pathname, int mode)
{

}

//获取文件属�?
int stat(const char *pathname, struct stat *statbuf)
{

}
//打开文件
FILE *fopen(const char *path, const char *mode)
{

}
//读文�?
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{


}

//写文�?
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{

}

//网络接口
//创建套接�?
int socket(int domain, int type, int protocol)
{

}


//网络连接
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{

}
//发�?
ssize_t send(int sockfd, const void *buf, size_t len, int flags)
{

}
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
const struct sockaddr *dest_addr, socklen_t addrlen)
{

}

//接收
ssize_t recv(int sockfd, void *buf, size_t len, int flags)
{

}
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
struct sockaddr *src_addr, socklen_t *addrlen)
{

}

//关闭套接�?
int shutdown(int sockfd,int howto)
{

}


//刷新缓冲区到文件
int fflush(FILE *stream)
{

}
//获取套接字选项
int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen)
{

}
//设置套接字选项
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t
optlen)
{

}
//字节序转�?
uint32_t htonl(uint32_t hostlong)
{
}
uint16_t htons(uint16_t hostshort)
{
}
uint32_t ntohl(uint32_t netlong)
{
}
uint16_t ntohs(uint16_t netshort)
{
}

//地址转换
int inet_aton(const char *cp, struct in_addr *inp)
{
}
char *inet_ntoa(struct in_addr in)
{
}
in_addr_t inet_addr(const char *cp)
{
}

//域名解析
struct hostent *gethostbyname(const char *name)
{

}


int fseek(FILE *stream, long offset, int whence)
{

}
long ftell(FILE *stream)
{
}
void rewind(FILE *stream)
{

}
//设备控制接口
int ioctl(int fd, unsigned long request, ...)
{

}

//系统IO
//关闭文件描述�?
int close(int fd)
{

}

//设备控制接口
int ioctl(int fd, unsigned long request, ...)
{

}

// 文件描述符监�?
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct
timeval *timeout)
{
}
void FD_CLR(int fd, fd_set *set)
{
}
int FD_ISSET(int fd, fd_set *set)
{
}
void FD_SET(int fd, fd_set *set)
{
}
void FD_ZERO(fd_set *set)
{
}

//管道
int pipe(int pipefd[2])
{

}
#endif
#endif
