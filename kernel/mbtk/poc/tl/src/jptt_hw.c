#include <stdio.h>
#include <string.h>
#include "oem_uart.h"
#include "jptt_debug.h"

#include "osa.h"
#include "asserts.h"
//#include "audio_bind.h"
#include "mbtk_os.h"
#include "mbtk_circle_buf.h"

extern void jmain_request_power_down(void);


/***********************************************
 *
 *  CODEC functions:
 *
 ***********************************************/
#define SAVE_RECV_MAX_BUFF (10*640)
static char *record_buff = 0;
static DRV_CIRCLE_BUF_T  record_c_buff;
static int IsPocPlayOver = 0;

static mbtk_mutexref mbtk_record_mutex = 0;

extern void hw_init_codec(int samp_rate, void (*earph_cb)(int)) 
{
    DEBUG_D("start player @%d.", samp_rate);
	if(record_buff==0){
		record_buff = (u8 *)malloc(SAVE_RECV_MAX_BUFF);
		DRV_CBufInit(&record_c_buff, record_buff, SAVE_RECV_MAX_BUFF);
	}

	if(mbtk_record_mutex == 0)
		mbtk_os_mutex_creat(&mbtk_record_mutex, OS_FIFO);

}

extern void hw_deinit_codec() {}

extern void hw_tone_gen(int type) { 

    DEBUG_D("hw_tone_genr %d",type);
	}

int hw_play_over()
{
	DEBUG_D("IsPocPlayOver:%d\n", __func__,IsPocPlayOver);
	return IsPocPlayOver;
}


/*
**  Player
*/
void OEMPlayBufferAvailCB(int rest_data)
{
    MLOG_D(MLOG_POC, POC,"%s:\n", __func__);
	if(rest_data == 0)
		IsPocPlayOver = 1;
    
}

extern int hw_open_player(int samp_rate, int *prior_bytes) {
    int i, res;

    DEBUG_D("start player @%d.", samp_rate);
    res = OEM_StarPlay();

    return res;
}

extern int hw_write_player(unsigned char *buffer, int length) {
    UINT32 res;
    OSA_STATUS status;
    
    //DEBUG_I("w%d (%d) ", length, OSAGetTicks());
    if(OEM_GetPlayBufferAvail()<length){
   		OSATaskSleep(4);
    }

	OEM_Play(buffer, length);
	IsPocPlayOver=0;
	
    return 0;
}

extern void hw_close_player() {
    DEBUG_D("stop player.");
    OEM_StopPlay();
}

extern int hw_write_tone(unsigned char *buffer, int length) 
{  
    DEBUG_D("hw_write_tone %d",length);

    hw_write_player(buffer,length);
    return 0;
}


extern int hw_route_player(int on) {
    /*if (on) {
        set_audio_path_accordingly();
    }*/
    return 0;
}

/*
**  Recorder
*/



void OEM_Record(const char* data, int length)
{
	int mbtk_oem_pcm_record_status(void);
	if(mbtk_oem_pcm_record_status()){
		mbtk_os_mutex_lock(mbtk_record_mutex, OSA_SUSPEND);
		DRV_CBufWrite(&record_c_buff, data, length);
		mbtk_os_mutex_unlock(mbtk_record_mutex);
	}
}


extern int hw_open_recorder(int samp_rate, int *prior_bytes) {
    int res = 0;
    
    DEBUG_D("start recorder @%d.", samp_rate);

    OEM_StarRecord();
    
    return 0;
}

extern int hw_read_recorder(unsigned char *buffer, int length) {
    OSA_STATUS status;
	int ret = 0;
	
    DEBUG_D("hw_read_recorder @%d.", length);

	while(!ret)
	{
		ret = DRV_CBufPayloadSize(&record_c_buff);
		DEBUG_D("DRV_CBufPayloadSize=%d\n", __func__,ret);
		if(ret==0)
		{
			OSATaskSleep(2);
		}
	}

	mbtk_os_mutex_lock(mbtk_record_mutex, OSA_SUSPEND);
	ret = DRV_CBufRead(&record_c_buff, buffer, length);	
	mbtk_os_mutex_unlock(mbtk_record_mutex);

    return 0;
}

extern void hw_close_recorder() {
    DEBUG_D("stop rec.");
	mbtk_os_mutex_lock(mbtk_record_mutex, OSA_SUSPEND);
	DRV_CBufFlush(&record_c_buff);
	mbtk_os_mutex_unlock(mbtk_record_mutex);
    OEM_StopRecord();
}

extern int hw_route_recorder(int on) {
    /*if (on) {
        set_audio_path_accordingly();
    }*/
    return 0;
}

/*
** other prepherials
*/

extern int hw_get_battery(void (*cb)(int, int)) {}

extern void hw_config_DRC() {
    // TODO...  player volume & EQ
}

extern void hw_config_ALC() {
    // TODO... recorder volume ALC EQ
}

extern int hw_write_5616eq(unsigned short * prs, int count) {
    return -1;
}



extern void hw_set_default_volume(int type, int level, int max_l) {
    DEBUG_I("set %d volume to %d / %d", type, level, max_l);
    if (type == 0) {  // main vol
        //ql_set_volume(level);
        //ql_set_dtmf_volume(level);  // rec tone
    }
}

/*
** wake lock & power-key monitor
*/

extern int hw_wakelock_lock(void) {
    return 0;
}

extern int hw_wakelock_unlock(void) {
    return 0;
}

extern int hw_wakelock_init() {
    return 0;
}

extern void hw_wakelock_deinit() {
}

/*
 *  notion CBs
 */
extern void lib_oem_tts_play_end_cb() {
}

extern void lib_oem_player_need_data_len_cb(int datalen) {
}

extern void lib_oem_record_cb(const char* data, int length) {
}


void jemcu_init(){}
void jemcu_deinit(){}

void quec_debug_print_uart()
{
}


extern void YJC_LOG_PRINT(const char *fmt, ...)
{
	va_list ap;
	char *mlog_buffer = (char *)malloc(MLOG_MAX_LENTH);
	memset(mlog_buffer, 0x0, MLOG_MAX_LENTH);
	char *p = mlog_buffer;
	va_start (ap, fmt);
	vsnprintf(p, MLOG_MAX_LENTH - 1, fmt, ap);
	va_end (ap);
	
	mbtk_app_log("%s",mlog_buffer);

	free(mlog_buffer);
}



void jdprintf(const char *fmt, ...)
{
    char msg[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(msg, 1024, fmt, ap);
    va_end(ap);
    msg[1024 - 1] = 0;
    CPUartLogPrintf("[oem_tl]%s", msg);
}



static char dbg_ts_char[30]={0};
void PMIC_RTC_tm_to_str(char *buf,UINT32 rtc_count);

extern const char *dbg_ts(void)
{
	uint32 curr = 0;
	memset(dbg_ts_char,0,30);

	curr = time(NULL);
	PMIC_RTC_tm_to_str(dbg_ts_char, curr);
    return dbg_ts_char;
}

extern void set_dbg_log_on(int on) {
}


