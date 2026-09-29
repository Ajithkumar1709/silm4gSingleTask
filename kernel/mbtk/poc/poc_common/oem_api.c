#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "mbtk_os.h"
#include "mbtk_device_api.h"
#include "mbtk_flash_file_system.h"

#include "oem_api.h"
#include "corget_api.h"

void OEMLogPrintf(const char *fmt, ...)
{
  char msg[1024] = {0};
  va_list ap;

  va_start(ap, fmt);
  vsnprintf(msg, 1024, fmt, ap);
  va_end(ap);

  msg[1024 - 1] = 0;
  MLOG_D(MLOG_POC, POC,"%s\r\n", msg);
}


#ifndef MBTK_POC_SUPPORT_TL
#define MBTK_KERNEL_TASK_STACK_SIZE    4*1024
#define MBTK_KERNEL_TASH_PRIORITY      220

#define IS_UPPER( alpha_char )   \
  ( ( (alpha_char >= 'A') && (alpha_char <= 'Z') ) ?  1 : 0 )

typedef enum
{
    MBTK_ZZD_EVENT_TONE,
    MBTK_ZZD_EVENT_MENU_TTS,
    MBTK_ZZD_EVENT_MAX
};

mbtk_taskref g_mbtk_zzd_task = NULL;
static mbtk_msgqref mbtk_zzd_msgq = 0;


mbtk_msgqref g_oem_msgq;
static mbtk_taskref g_oem_task_ref;
mbtk_ostimerref g_oem_timer;
static mbtk_ostimerref oemchecktimer;

void oem_thread(void *arg);
#if defined(MBTK_POC_SUPPORT_ZZD) || defined(MBTK_POC_SUPPORT_HAWK) || defined(MBTK_POC_SUPPORT_CHAYU) 
	mbtk_msgqref POC_Msg = NULL;
#endif

//No use
int OEM_SetCPUPerformance(int level)
{
}

unsigned long OEM_PocGetMsgQueueRestSpace(void)
{
    int cnt;
    mbtk_os_msgq_poll(g_oem_msgq, &cnt);
    return OEM_MSGQ_QUEUE_SIZE - cnt;
}


static void toLower(uint8 *str)
{
    uint8 *ptr;

    if(str == NULL)
    {
        return;
    }
    ptr = str;

    while (*ptr != 0)
    {
        if (IS_UPPER(*ptr))
        {
            *ptr -= 'A' - 'a';
        }
        ptr++;
    }
}

int OEMFile_Open(const char *path, const char *oflag)
{
    int ret = 0;
    int i = 0;
    char oflag_t[10] = {0};

    if (path == NULL)
        return -1;

    memcpy(oflag_t, oflag, strlen(oflag));
    toLower(oflag_t);

    ret = ol_FFS_Open(path, oflag_t);
    //OEMLogPrintf("%s: %d, %s:%s", __func__, ret, path, oflag);
    return ret;
}

int OEMFile_Close(unsigned short filedes)
{
    int ret = 0;

    if (filedes < 0)
        return -1;

    //OEMLogPrintf("%s: %d, %d", __func__, filedes, ret); 
    return ol_FFS_Close(filedes);
}

int OEMFile_Seek(unsigned short filedes, long offset, int where)
{
    int ret = 0;

    if(offset<0 && where == 0)
    {
        //OEMLogPrintf("%s: %d, %d,%d,-1", __func__, filedes, offset,where);
        return -1;
    }

    ret = ol_FFS_Seek(filedes, offset, where);

    //OEMLogPrintf("%s: %d, %d,%d,%d", __func__, filedes, offset,where, ret);
    return ret;
}

int OEMFile_Getlength(int filedes)
{
    return ol_FFS_GetSize(filedes);
}

int OEMFile_Read(unsigned short filedes,void *buf,int size,int count)
{
    int ret = 0;

    ret = ol_FFS_Read(filedes, buf, size*count);

    //OEMLogPrintf("%s: %d, %d,%d, %d", __func__, filedes,size, count, ret);

    return ret;
}

int OEMFile_Write(unsigned short filedes,void *buf,int size,int count)
{
    int ret = 0;

    ret = ol_FFS_Write(filedes, buf, size*count);

    //OEMLogPrintf("%s: %d, %d,  %d, %d", __func__, filedes,size, count, ret);

    return ret;
}

long OEMFile_Tell(unsigned int filedes)
{
    int ret = 0;

    ret = ol_FFS_Ftell(filedes);

    //OEMLogPrintf("%s: %d, %d", __func__, filedes, ret);
    return ret;
}

int OEMFile_ftruncate(unsigned int filedes, unsigned int size)
{
    OEMLogPrintf("%s: ", __func__); 
    return 0;
}

void OEM_initMessage(void)
{
    mbtk_os_status status;

    status = mbtk_os_msgq_creat(&g_oem_msgq, "oem_msgq", OEM_MSGQ_MSG_SIZE, OEM_MSGQ_QUEUE_SIZE, MBTK_OS_FIFO);

    OEMLogPrintf("%s: %d .", __func__, status); 
}

static mbtk_taskref g_oem_task_ref;
int OEM_init(void)
{
    void *atOemProxyWokerTaskStack;
    mbtk_os_status status;

    OEM_initMessage();

    status = mbtk_os_timer_creat(&g_oem_timer);

    //DIAG_ASSERT(status == mbtk_os_success);
    atOemProxyWokerTaskStack = malloc(OEM_THREAD_STACKSIZE);
    if(atOemProxyWokerTaskStack == NULL)
    {
        //DIAG_ASSERT(0);
        OEMLogPrintf("Out of memory in atOemProxyWokerTaskStack!");
        return 0;
    }
#ifndef MBTK_POC_SUPPORT_BND
#ifndef MBTK_POC_SUPPORT_IWALKIE
    if(mbtk_os_task_creat(&g_oem_task_ref,
                          atOemProxyWokerTaskStack,
                          OEM_THREAD_STACKSIZE,
                          OEM_THREAD_PRIO,
                          (char*)"atOemProxyWokerTaskStack",
                          oem_thread, NULL) != 0)
    {
        //DIAG_ASSERT(0);
        OEMLogPrintf("Cannot start atOemProxyWokerTaskStack!");
        return 0;
    }
    OEM_PocInit();
#endif
#endif

    OEMLogPrintf("%s:init finished!", __func__);
    return 0;
}

int OEM_GetImeiInfo(char *imei)
{
    int iret = 0;

    if(!imei)
        return -1;

    if(iret = mbtk_get_imei(imei) != mbtk_device_api_err_none)
        return -1;

    return 0;
}

int OEM_GetModeVersion(char *mode)
{
    memcpy(mode, mbtk_get_modem_version(), strlen(mbtk_get_modem_version()));
    mode[strlen(mbtk_get_modem_version())]='\0';
    return 0;
}
extern void mbtk_poc_send_msg2atdecoder(char *encode_str);

int mbtk_poc_check_line_break(char src)
{
    if(src == '\r' || src == '\n')
        return 0;
    else
        return 1;
}

char *mbtk_poc_resp_hand(char *src)
{
    int src_len = strlen(src);
    char *ret = ( char *)malloc(src_len);
    char *temp2 = ( char *)malloc(src_len);
    char *temp = temp2;
    int index;
    memset(ret, 0, src_len);
    memcpy(temp2,src, src_len);

    //check head \r\n
    for(index = 0; index < 2 ; index++)
    {
        if(!mbtk_poc_check_line_break(temp2[index]))
        {
            temp++;
        }
    }
    for(index = src_len; index > (src_len - 3); index --)
    {
        if(!mbtk_poc_check_line_break(temp2[index]))
        {
            temp2[index] = '\0';
        }
    }

    strcat(ret, temp);
    free(temp2);

    return ret;
}

void mbtk_play_menu_req(char * menu)
{
    mbtk_os_status status;
    mbtk_event_msg msg = {0};

    msg.type = MBTK_ZZD_EVENT_MENU_TTS;
    msg.data = menu;
    status = mbtk_os_msgq_send(mbtk_zzd_msgq, sizeof(mbtk_event_msg), &msg, MBTK_OS_NO_SUSPEND);
}

#endif

#if (defined(MBTK_POC_SUPPORT_ZZD) || defined(MBTK_POC_SUPPORT_HAWK)|| defined(MBTK_POC_SUPPORT_CHAYU))
void mbtk_zzd_init_task(void)
{
    mbtk_os_status status;
    mbtk_event_msg apiMsg;
    char imei[20] = {0};

    mbtk_zzd_init_internal();

    mbtk_get_imei(imei);
    while(1)
    {
        status=mbtk_os_msgq_recv(mbtk_zzd_msgq, (char *)&apiMsg, sizeof(mbtk_event_msg), MBTK_OS_SUSPEND);
        switch(apiMsg.type)
        {

            /*case MBTK_ZZD_EVENT_MENU_TTS:
                OEM_TTS_Spk_Menu(apiMsg.data);
                break;*/
        }
    }
    //mbtk_os_task_delete(g_mbtk_zzd_task);
}

void mbtk_zzd_init(void)
{
    mbtk_os_status status = 0;
    char *stack = NULL;

    status = mbtk_os_msgq_creat(&mbtk_zzd_msgq, "mbtk_zzd_msgq", sizeof(mbtk_event_msg), 10, MBTK_OS_FIFO);

    MLOG_D(MLOG_POC, POC,"[mbtk_poc_task]:create poc task \n");

    stack = malloc(MBTK_KERNEL_TASK_STACK_SIZE);
    if(stack == NULL)
    {
        MLOG_D(MLOG_POC, POC,"[mbtk_zzd_task]:stack ol_malloc fail\n");
        return ;
    }

    status = mbtk_os_task_creat(&g_mbtk_zzd_task,
                                (void *)stack,
                                MBTK_KERNEL_TASK_STACK_SIZE,
                                MBTK_KERNEL_TASH_PRIORITY,
                                "mbtk_zzd_task",
                                mbtk_zzd_init_task, NULL);
    if(status != mbtk_os_success)
    {
        MLOG_D(MLOG_POC, POC,"[mbtk_zzd_task]:kernel task create fail\n");
        free(stack);
        return ;
    }
}

void poc_ui_Select(char *default_platform, char *default_dns, int is_broad, int is_abroad)
{ 
#ifdef MBTK_POC_SUPPORT_BND
		poc_ui_enter(default_platform, default_dns,is_broad,is_abroad);
#else
		char temp[30]={0};
		OEM_getSimIccid(temp);
		MLOG_D(MLOG_POC, POC,"HAWK GET ICCID=%s\r\n",temp);
#endif
}
#endif

void mbtk_poc_init(void)
{
	static int init_flag = 0;
	if(init_flag == 0)
	{
		init_flag = 1;

		#ifdef MBTK_CODEC_TYPE_ES8311
		extern void codec_es_8311_init(void);
	    codec_es_8311_init(); 
		#endif
		#ifdef MBTK_CODEC_TYPE_CJC8910
		extern void codec_cjc_8910_init(void);
	    codec_cjc_8910_init(); 
		#endif

		oem_auido_init();
#ifdef MBTK_POC_SUPPORT_BND
    mbtk_bnd_init();
#endif

#if (defined(MBTK_POC_SUPPORT_HAWK) || defined(MBTK_POC_SUPPORT_CHAYU) || defined(MBTK_POC_SUPPORT_ZZD))
    mbtk_zzd_init();
#endif

#if defined(MBTK_POC_SUPPORT_TL)
	extern int jptt_start_main(int mode);
	jptt_start_main(1);
#endif

#ifdef MBTK_POC_SUPPORT_IWALKIE
        MLOG_D(MLOG_POC, POC,"%s:iwalkie init start 2!", __func__);
        iwalkie_poc_init();
#endif

	}

}

