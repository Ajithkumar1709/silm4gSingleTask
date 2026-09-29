#include <stdio.h>
#include <stdlib.h>
#include "simcom_gps.h"
#include "simcom_os.h"
#include "simcom_common.h"
#include "mbtk_gps.h"
#include "mbtk_err.h"
#include "mbtk_os.h"


sMsgQRef gGpsUrcMsgQueue = NULL;

mbtk_taskref MBTK_Gps_taskRef = NULL;
mbtk_msgqref MBTK_Gps_msgQRef = NULL;
mbtk_ostimerref Mbtk_Gps_TimerRef = NULL;
mbtk_flagref Mbtk_Gps_Flag_Ref = NULL;

#define GPS_INFO_FLAG     (0x01 << 0)
#define GNSS_INFO_FLAG    (0x01 << 1)
#define NMEA_DATA_FLAG    (0x01 << 2)


typedef struct 
{
    uint8_t mode[4];
    uint8_t GPS_SVs[4];
    uint8_t BEIDOU_SVs[4];
    uint8_t latitude[12];
    uint8_t N_S_indicator[4];
    uint8_t longitude[12];
    uint8_t E_W_indicator[4];
    uint8_t date[8];
    uint8_t UTC_time[12];
    uint8_t MSL_Altitude[12];
    uint8_t speed[12];
    uint8_t course[12];
    uint8_t pdop[8];
    uint8_t hdop[8];
    uint8_t vdop[8];
}Sc_Nmea_info_t;


#define GPS_INFO_FLAG_MASK (GPS_INFO_FLAG | GNSS_INFO_FLAG | NMEA_DATA_FLAG)

Sc_Nmea_info_t Sc_Nmea_info = {0};


void Mbtk_Gps_Info_Timer_Cb(uint32_t param)
{
    ol_os_flag_set(Mbtk_Gps_Flag_Ref, GPS_INFO_FLAG, MBTK_OS_FLAG_OR);
    ol_os_flag_set(Mbtk_Gps_Flag_Ref, NMEA_DATA_FLAG, MBTK_OS_FLAG_OR);
}

static char *SC_NMEA_Comma_Pos(char *buf, uint8_t cx)
{
	while (cx)
	{
		if (*buf == '*' || *buf<' ' || *buf>'z')
			return NULL;
		//¨¦????¡ã'*'??¨C¨¨€¡­¨¦???3??-¡ª??????????-???¡§???cx??a¨¦€¡ª??¡¤
			
		if (*buf == ',')
			cx--;
		
		buf++;
	}
	return buf;
}


void Mbtk_Gnss_Nmea_cb(char *Nmeadata)
{
    char *ptr,*pos_start, *pos_end;
    
    if((ptr = strstr(Nmeadata, "$GNRMC")) != NULL)
    {
        pos_start = SC_NMEA_Comma_Pos(ptr, 3);
        pos_end = SC_NMEA_Comma_Pos(ptr, 4);
        if(pos_start && pos_end)
        {
            memset(Sc_Nmea_info.latitude, 0x0, sizeof(Sc_Nmea_info.latitude));
            memcpy(Sc_Nmea_info.latitude, pos_start, pos_end - pos_start - 1);
        }

        pos_start = SC_NMEA_Comma_Pos(ptr, 5);
        pos_end = SC_NMEA_Comma_Pos(ptr, 6);
        if(pos_start && pos_end)
        {
            memset(Sc_Nmea_info.longitude, 0x0, sizeof(Sc_Nmea_info.longitude));
            memcpy(Sc_Nmea_info.longitude, pos_start, pos_end - pos_start - 1);
        }
        
        pos_start = SC_NMEA_Comma_Pos(ptr, 7);
        pos_end = SC_NMEA_Comma_Pos(ptr, 8);
        if(pos_start && pos_end)
        {
            memset(Sc_Nmea_info.speed, 0x0, sizeof(Sc_Nmea_info.speed));
            memcpy(Sc_Nmea_info.speed, pos_start, pos_end - pos_start - 1);
        }
    }
    if((ptr = strstr(Nmeadata, "$GNGGA")) != NULL)
    {
        pos_start = SC_NMEA_Comma_Pos(ptr, 9);
        pos_end = SC_NMEA_Comma_Pos(ptr, 10);
        if(pos_start && pos_end)
        {
            memset(Sc_Nmea_info.MSL_Altitude, 0x0, sizeof(Sc_Nmea_info.MSL_Altitude));
            memcpy(Sc_Nmea_info.MSL_Altitude, pos_start, pos_end - pos_start - 1);
        }
    }
    if((ptr = strstr(Nmeadata, "$GNVTG")) != NULL)
    {
        pos_start = SC_NMEA_Comma_Pos(ptr, 1);
        pos_end = SC_NMEA_Comma_Pos(ptr, 2);
        if(pos_start && pos_end)
        {
            memset(Sc_Nmea_info.course, 0x0, sizeof(Sc_Nmea_info.course));
            memcpy(Sc_Nmea_info.course, pos_start, pos_end - pos_start - 1);
        }
        
        pos_start = SC_NMEA_Comma_Pos(ptr, 7);
        pos_end = SC_NMEA_Comma_Pos(ptr, 8);
        if(pos_start && pos_end)
        {
            memset(Sc_Nmea_info.speed, 0x0, sizeof(Sc_Nmea_info.speed));
            memcpy(Sc_Nmea_info.speed, pos_start, pos_end - pos_start - 1);
        }
    }
}

void mbtk_gps_thread(void *param)
{
    mbtk_gps_info *info = ol_get_gps_info();
    SIM_MSG_T msg = {SRV_URC, SC_URC_GNSS_MASK, SC_URC_PBDOWN, NULL};
    char *gps_data = NULL;
    int gps_data_len = 0;
    int gps_flag;

    ol_os_timer_creat(&Mbtk_Gps_TimerRef);
    ol_os_flag_creat(&Mbtk_Gps_Flag_Ref);
    
    while(1)
    {
        ol_os_flag_wait(Mbtk_Gps_Flag_Ref, GPS_INFO_FLAG_MASK, MBTK_OS_FLAG_OR_CLEAR, &gps_flag, MBTK_OS_SUSPEND);
        
        if(gps_flag & GPS_INFO_FLAG)
        {
            gps_data = (char *)malloc(256);
            memset(gps_data, 0x0, 256);
            gps_data_len = 0;
            if(info->nmea.fixmode > 1)
            {
                sprintf(gps_data, "%c,%s,%c,%s", info->nmea.nshemi,Sc_Nmea_info.latitude,
                                                 info->nmea.ewhemi,Sc_Nmea_info.longitude);
            }
            else
            {
                gps_data_len += sprintf(gps_data + gps_data_len, ",,,");
            }
            msg.arg2 = SC_URC_GPS_INFO;
            msg.arg3 = gps_data;
            
            if(gGpsUrcMsgQueue)
                sAPI_MsgQSend(gGpsUrcMsgQueue, &msg);
            else
                free(gps_data);
        }
        if(gps_flag & NMEA_DATA_FLAG)
        {
            gps_data = (char *)malloc(512);
            memset(gps_data, 0x0, 512);
            gps_data_len = 0;
            if(info->nmea.fixmode > 1)
            {
                gps_data_len += sprintf(gps_data + gps_data_len, "%d,", info->nmea.fixmode);
            }
            else
            {
                gps_data_len += sprintf(gps_data + gps_data_len, ",");
            }

            if(info->nmea.fixmode > 1)
            {
                gps_data_len += sprintf(gps_data + gps_data_len, "%02d,", info->nmea.svnum);
            }
            else
            {
                gps_data_len += sprintf(gps_data + gps_data_len, ",");
            }
            
            if(info->nmea.fixmode > 1)
            {
                gps_data_len += sprintf(gps_data + gps_data_len, "%02d,", info->nmea.beidou_svnum);
            }
            else
            {
                gps_data_len += sprintf(gps_data + gps_data_len, ",");
            }
            
            gps_data_len += sprintf(gps_data + gps_data_len, "%s,",Sc_Nmea_info.latitude);

            gps_data_len += sprintf(gps_data + gps_data_len, "%c,", info->nmea.nshemi);

            gps_data_len += sprintf(gps_data + gps_data_len, "%s,", Sc_Nmea_info.longitude);

            gps_data_len += sprintf(gps_data + gps_data_len, "%c,", info->nmea.ewhemi);
            
            if(info->nmea.fixmode > 1)
            {
                gps_data_len += sprintf(gps_data + gps_data_len, "%02d%02d%02d,", info->nmea.utc.date, info->nmea.utc.month, info->nmea.utc.year);
                
                gps_data_len += sprintf(gps_data + gps_data_len, "%02d%02d%02d.00,", info->nmea.utc.hour, info->nmea.utc.min, info->nmea.utc.sec);
            }
            else
            {
                gps_data_len += sprintf(gps_data + gps_data_len, ",,");
            }

            gps_data_len += sprintf(gps_data + gps_data_len, "%s,", Sc_Nmea_info.MSL_Altitude);

            gps_data_len += sprintf(gps_data + gps_data_len, "%s,", Sc_Nmea_info.speed);

            if(info->nmea.fixmode > 1)
            {
                gps_data_len += sprintf(gps_data + gps_data_len, "%s,", Sc_Nmea_info.course);
            }
            else
            {
                gps_data_len += sprintf(gps_data + gps_data_len, ",");
            }

            
            if(info->nmea.fixmode > 1)
            {
                gps_data_len += sprintf(gps_data + gps_data_len, "%.2f,", info->nmea.pdop/10.0);
            }
            else
            {
                gps_data_len += sprintf(gps_data + gps_data_len, ",");
            }

            if(info->nmea.fixmode > 1)
            {
                gps_data_len += sprintf(gps_data + gps_data_len, "%.2f,", info->nmea.hdop/10.0);
            }
            else
            {
                gps_data_len += sprintf(gps_data + gps_data_len, ",");
            }
            
            if(info->nmea.fixmode > 1)
            {
                gps_data_len += sprintf(gps_data + gps_data_len, "%.2f", info->nmea.vdop/10.0);
            }
            
            msg.arg2 = SC_URC_NMEA_DATA;
            msg.arg3 = gps_data;
            
            if(gGpsUrcMsgQueue)
                sAPI_MsgQSend(gGpsUrcMsgQueue, &msg);
            else
                free(gps_data);
        }
        

    }
}

SC_Gnss_Return_Code sAPI_GnssPowerStatusSet(SC_Gnss_Power_Status power)
{
    switch(power)
    {
        case SC_GNSS_POWER_ON:
        {
            if(ol_gps_power(MBTK_GNSS_POWERON) != mbtk_gps_success)
                return SC_GNSS_RETURN_CODE_ERROR;


            if(!MBTK_Gps_taskRef)
            {
                if(ol_os_task_creat(&MBTK_Gps_taskRef, NULL, 2 * 1024, 200, "MBTK_Gps_task", mbtk_gps_thread, NULL) != mbtk_os_success)
                {
                    return SC_GNSS_RETURN_CODE_ERROR;
                }
            }
            break;
        }
        case SC_GNSS_POWER_OFF:
        {
            if(ol_gps_power(MBTK_GNSS_POWEROFF) != mbtk_gps_success)
                return SC_GNSS_RETURN_CODE_ERROR;
            if(MBTK_Gps_taskRef)
            {
                ol_os_task_delete(MBTK_Gps_taskRef);
                MBTK_Gps_taskRef = NULL;
            }
            break;
        }
    }
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Power_Status sAPI_GnssPowerStatusGet(void)
{
    if(ol_gps_get_status() == ASR_GPS_STATE_ACTIVE)
        return SC_GNSS_POWER_ON;
    
    return SC_GNSS_POWER_OFF;
}

SC_Gnss_Return_Code sAPI_GnssNmeaDataGet(SC_Gnss_Output_Control ctl, SC_Gnss_Nmea_Data_Get mode)
{
    switch(ctl)
    {
        case SC_GNSS_START_OUTPUT_NMEA_DATA:
        {
            ol_gps_set_gps_nmea_cb(Mbtk_Gnss_Nmea_cb);
            break;
        }
        case SC_GNSS_STOP_OUTPUT_NMEA_DATA:
        {
            ol_gps_set_gps_nmea_cb(NULL);
            break;
        }
    }
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Return_Code sAPI_GnssStartMode(SC_Gnss_Start_Mode mode)
{
    Mbtk_gnss_cmd_enum gnss_start_mode;
    switch(mode)
    {
        case SC_GNSS_START_HOT:
        {
            gnss_start_mode = MBTK_GNSS_CMD_HOTSTART;
            break;
        }
        case SC_GNSS_START_WARM:
        {
            gnss_start_mode = MBTK_GNSS_CMD_WARMSTART;
            break;
        }
        case SC_GNSS_START_COLD:
        {
            gnss_start_mode = MBTK_GNSS_CMD_COLDSTART;
            break;
        }
        default:
            gnss_start_mode = MBTK_GNSS_CMD_COLDSTART;
            break;
    }

    if(ol_gps_operation(gnss_start_mode) != mbtk_gps_success)
        return SC_GNSS_RETURN_CODE_ERROR;
    
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Return_Code sAPI_GnssBaudRateSet(SC_Gnss_Baud_Rate baudrate)
{
    simcom_api_not_support();
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Baud_Rate sAPI_GnssBaudRateGet(void)
{
    simcom_api_not_support();
    return SC_GNSS_BAUD_RATE_115200;
}

SC_Gnss_Return_Code sAPI_GnssModeSet(SC_Gnss_Mode mode)
{
    simcom_api_not_support();
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Mode sAPI_GnssModeGet(void)
{
    simcom_api_not_support();
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Return_Code sAPI_GnssNmeaRateSet(SC_Gnss_Nmea_Rate rate)
{
    simcom_api_not_support();
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Nmea_Rate sAPI_GnssNmeaRateGet(void)
{
    simcom_api_not_support();
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Return_Code sAPI_GnssNmeaSentenceSet(unsigned short mask)
{
    simcom_api_not_support();
    return SC_GNSS_RETURN_CODE_OK;
}

UINT8* sAPI_GnssNmeaSentenceGet(void)
{
    simcom_api_not_support();
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Return_Code sAPI_GpsInfoGet(UINT8 period)
{
    if(!Mbtk_Gps_TimerRef)
        return SC_GNSS_RETURN_CODE_ERROR;
    
    if(period > 0)
    {
        if(ol_os_timer_start(Mbtk_Gps_TimerRef, period * 200, period * 200, Mbtk_Gps_Info_Timer_Cb, 0) != mbtk_os_success)
            return SC_GNSS_RETURN_CODE_ERROR;
    }
    else
    {
        if(ol_os_timer_stop(Mbtk_Gps_TimerRef) != mbtk_os_success)
            return SC_GNSS_RETURN_CODE_ERROR;
    }
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Return_Code sAPI_GnssInfoGet(UINT8 period)
{
    if(!Mbtk_Gps_TimerRef)
        return SC_GNSS_RETURN_CODE_ERROR;
    
    if(period > 0)
    {
        if(ol_os_timer_start(Mbtk_Gps_TimerRef, period * 200, period * 200, Mbtk_Gps_Info_Timer_Cb, 0) != mbtk_os_success)
            return SC_GNSS_RETURN_CODE_ERROR;
    }
    else
    {
        if(ol_os_timer_stop(Mbtk_Gps_TimerRef) != mbtk_os_success)
            return SC_GNSS_RETURN_CODE_ERROR;
    }
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Return_Code sAPI_SendCmd2Gnss(char *string)
{
    simcom_api_not_support();
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Return_Code sAPI_GnssAgpsSeviceOpen(void)
{
    simcom_api_not_support();
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Return_Code sAPI_GnssApFlashSet(SC_Gnss_Ap_Flash_Status ctl)
{
    simcom_api_not_support();
    return SC_GNSS_RETURN_CODE_OK;
}

SC_Gnss_Ap_Flash_Status sAPI_GnssApFlashGet(void)
{
    simcom_api_not_support();
    return SC_GNSS_RETURN_CODE_OK;
}


