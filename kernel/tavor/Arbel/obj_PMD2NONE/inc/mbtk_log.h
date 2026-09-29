#ifndef __MBTK_LOG_H__
#define __MBTK_LOG_H__

#include <stdbool.h>
#include "diag_api.h"
#include "diag_nvm.h"

#define MLOG_KEY_WORLD_LEN 24
#define MLOG_MAX_LENTH 512
typedef enum
{
	MLOG_NONE = 0,
	MLOG_COMM,
	MLOG_ATS,
	MLOG_ATGPRS,
	MLOG_FOTA,
	MLOG_DEV,
	MLOG_AUDIO,
	MLOG_UART,
	MLOG_DEVICE,
	MLOG_VIS_AT,
	MLOG_DATACALL,
	MLOG_VCALL,
	MLOG_NETWORK,
	MLOG_SIM,
	MLOG_SOC,
	MLOG_ADC,
	MLOG_WIFI,
	MLOG_SMS,
	MLOG_GPS,
	MLOG_PPP,
	MLOG_TTS,
	MLOG_MQTT,
	MLOG_PWM,
	MLOG_WS,
	MLOG_TLS,
	MLOG_PYTHON,
	MLOG_POC,
#ifdef  MBTK_MP3_DECODE
	MLOG_AUDIO,
#endif
	MLOG_MAX,
}MLOG_EVENT;

typedef enum
{
	MLOG_LEVEL_NONE = 0,
	MLOG_LEVEL_ERR,
	MLOG_LEVEL_WARN,
	MLOG_LEVEL_INFO,
	MLOG_LEVEL_DEBUG,
}MLOG_LEVEL;

bool MLog_SyncConfig(MLOG_EVENT event_type,MLOG_LEVEL level);
MLOG_LEVEL MLog_GetLevel(MLOG_EVENT event_type);
char *Mlog_buffer(const char *func,unsigned int line,const char *fmt,...);
extern void MlogMutexLock(void);
extern void MlogMutexUnlock(void);
extern 	char mbtk_log_enable;
#define MLOG(event,title,level,level_i,func,line,fmt,...)	 							\
	do{																									\
		if(MLog_GetLevel(event) >= MLOG_LEVEL_DEBUG && level_i<=mbtk_log_enable){				\
			char *mlog_buffer = Mlog_buffer(func,line,fmt,##__VA_ARGS__);							\
			DIAG_FILTER(MBTK,title,level, DIAG_INFORMATION) 		\
			diagPrintf("%s",mlog_buffer); \
			free(mlog_buffer);} 	\
	}while(0)

#define MLOG_D(event,title,fmt,...) 	MLOG(event,title,DEBUG,MLOG_LEVEL_DEBUG,__func__,__LINE__,fmt,##__VA_ARGS__)
#define MLOG_I(event,title,fmt,...) 		MLOG(event,title,INFO,MLOG_LEVEL_INFO,__func__,__LINE__,fmt,##__VA_ARGS__)
#define MLOG_W(event,title,fmt,...) 	MLOG(event,title,WARN,__func__,MLOG_LEVEL_WARN,__LINE__,fmt,##__VA_ARGS__)
#define MLOG_E(event,title,fmt,...) 	MLOG(event,title,ERR,__func__,MLOG_LEVEL_ERR,__LINE__,fmt,##__VA_ARGS__)


typedef enum
{
	APP_LOG_NONE,
	APP_LOG_DIAG,
	APP_LOG_UART,
}APP_LOG_DIR;

void ol_printf(const char *fmt,...);
void ol_printf_ctl(char output_dir);
#endif