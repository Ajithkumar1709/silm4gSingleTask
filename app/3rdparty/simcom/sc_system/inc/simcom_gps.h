#ifndef _SIMCOM_GPS_H_
#define _SIMCOM_GPS_H_

#include "mbtk_pub_type.h"

typedef enum {
    SC_GNSS_RETURN_CODE_OK,
    SC_GNSS_RETURN_CODE_ERROR
}SC_Gnss_Return_Code;

typedef enum {
    SC_GNSS_POWER_OFF,
    SC_GNSS_POWER_ON
}SC_Gnss_Power_Status;

typedef enum {
    SC_GNSS_START_OUTPUT_NMEA_DATA,
    SC_GNSS_STOP_OUTPUT_NMEA_DATA
}SC_Gnss_Output_Control;

typedef enum {
    SC_GNSS_NMEA_DATA_GET_BY_PORT,
    SC_GNSS_NMEA_DATA_GET_BY_URC
}SC_Gnss_Nmea_Data_Get;

typedef enum {
    SC_GNSS_START_HOT,
    SC_GNSS_START_WARM,
    SC_GNSS_START_COLD
}SC_Gnss_Start_Mode;

typedef enum {
    SC_GNSS_BAUD_RATE_4800      = 4800,
    SC_GNSS_BAUD_RATE_9600      = 9600,
    SC_GNSS_BAUD_RATE_19200     = 19200,
    SC_GNSS_BAUD_RATE_38400     = 38400,
    SC_GNSS_BAUD_RATE_57600     = 57600,
    SC_GNSS_BAUD_RATE_115200    = 115200,
    SC_GNSS_BAUD_RATE_230400    = 230400,
}SC_Gnss_Baud_Rate;

typedef enum {
    SC_GNSS_MODE_GPS,
    SC_GNSS_MODE_BDS,
    SC_GNSS_MODE_GPS_BDS,
    SC_GNSS_MODE_GPS_QZSS,
    SC_GNSS_MODE_GLONASS,
    SC_GNSS_MODE_GPS_GLONASS,
    SC_GNSS_MODE_BDS_GLONASS,
    SC_GNSS_MODE_GPS_BDS_GLONASS,
    SC_GNSS_MODE_GPS_L1_SBAS_QZSS,
    SC_GNSS_MODE_GPS_BDS_GALILEO_SBAS_QZSS,
    SC_GNSS_MODE_GPS_BDS_QZSS,
}SC_Gnss_Mode;

typedef enum {
    SC_GNSS_NMEA_UPDATE_RATE_1HZ,
    SC_GNSS_NMEA_UPDATE_RATE_2HZ,
    SC_GNSS_NMEA_UPDATE_RATE_5HZ,
}SC_Gnss_Nmea_Rate;

typedef enum {
    SC_GNSS_AP_FLASH_ON,
    SC_GNSS_AP_FLASH_OFF
}SC_Gnss_Ap_Flash_Status;

SC_Gnss_Return_Code sAPI_GnssPowerStatusSet(SC_Gnss_Power_Status power);
SC_Gnss_Power_Status sAPI_GnssPowerStatusGet(void);
SC_Gnss_Return_Code sAPI_GnssNmeaDataGet(SC_Gnss_Output_Control ctl, SC_Gnss_Nmea_Data_Get mode);
SC_Gnss_Return_Code sAPI_GnssStartMode(SC_Gnss_Start_Mode mode);
SC_Gnss_Return_Code sAPI_GnssBaudRateSet(SC_Gnss_Baud_Rate baudrate);
SC_Gnss_Baud_Rate sAPI_GnssBaudRateGet(void);
SC_Gnss_Return_Code sAPI_GnssModeSet(SC_Gnss_Mode mode);
SC_Gnss_Mode sAPI_GnssModeGet(void);
SC_Gnss_Return_Code sAPI_GnssNmeaRateSet(SC_Gnss_Nmea_Rate rate);
SC_Gnss_Nmea_Rate sAPI_GnssNmeaRateGet(void);
SC_Gnss_Return_Code sAPI_GnssNmeaSentenceSet(unsigned short mask);
UINT8* sAPI_GnssNmeaSentenceGet(void);
SC_Gnss_Return_Code sAPI_GpsInfoGet(UINT8 period);
SC_Gnss_Return_Code sAPI_GnssInfoGet(UINT8 period);
SC_Gnss_Return_Code sAPI_SendCmd2Gnss(char *string);
SC_Gnss_Return_Code sAPI_GnssAgpsSeviceOpen(void);
SC_Gnss_Return_Code sAPI_GnssApFlashSet(SC_Gnss_Ap_Flash_Status ctl);
SC_Gnss_Ap_Flash_Status sAPI_GnssApFlashGet(void);




#endif
