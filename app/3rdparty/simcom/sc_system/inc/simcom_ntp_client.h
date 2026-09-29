#ifndef _NTP_CLIENT_H_
#define _NTP_CLIENT_H_

#include "simcom_os.h"


#if 1//def SIM_HTPNTP_APP

typedef enum {
    SC_NTP_OP_SET,
    SC_NTP_OP_GET,
    SC_NTP_OP_EXC,
}SCntpOperationType;


typedef enum {
    SC_NTP_OK = 0,
    SC_NTP_ERROR,
    SC_NTP_ERROR_INVALID_PARAM,
    SC_NTP_ERROR_TIME_CALCULATED,
    SC_NTP_ERROR_NETWORK_FAIL,
    SC_NTP_ERROR_TIME_ZONE,
    SC_NTP_ERROR_TIME_OUT,
    SC_NTP_END
}SCntpResultType;

typedef SCntpResultType SCntpReturnCode;


typedef struct sys_time {
    int tm_sec;//秒(0,59)
    int tm_min;//分钟(0,59)
    int tm_hour;//小时(0,23)
    int tm_mday;//日[1,31]
    int tm_mon;//月[1,12]
    int tm_year;//年自 1970 年以来
    int tm_wday;// 星期 Sunday = 0
} tm_rtc;

typedef tm_rtc SCsysTime_t;

SCntpReturnCode sAPI_NtpUpdate(SCntpOperationType commad_type, char* host_addr, int time_zone, sMsgQRef magQ_urc);
void sAPI_GetSysLocalTime(tm_rtc *currUtcTime);
void sAPI_SetSysLocalTime(char* timeStr);

#endif
#endif

