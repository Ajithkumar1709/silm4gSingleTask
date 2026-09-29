#ifndef _OL_WIFI_API_H_
#define _OL_WIFI_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#define APP_ADP_WIFI_MAC_LEN 6
#define APP_ADP_WIFI_AP_MAX_NUM 32

typedef enum
{
    APP_ADP_WIFI_RESULT_SUCCESS = 0,
    APP_ADP_WIFI_RESULT_FAILURE,
    APP_ADP_WIFI_RESULT_TIMEOUT,
} app_adp_wifi_result_t;

typedef struct
{
    uint8_t mac[APP_ADP_WIFI_MAC_LEN]; //MAC addr
    int32_t rssi; //The signal strength of an AP hotspot
} app_adp_wifi_ap_item;

typedef struct
{
    uint8_t count; //Number of AP hotspots searched
    app_adp_wifi_ap_item item[APP_ADP_WIFI_AP_MAX_NUM];
} app_adp_wifi_ap_list;

typedef struct
{
	//0:start wifi scan with default option 2:start wifi scan with option 3:allow wifi scan under CFUN0/4 with default option
	unsigned int scan_mode;
	//0:not allow rrc release immediately 1:allow rrc release immediately.default 0
	unsigned int fast_rrc_release;
	//config wifi scan round 1~6.defaut 3
	unsigned int scan_round;
	//config wifi scan max hotspot 4~30.default 5
	unsigned int bssid_num;
	//config wifi scan priority 0~1.default 0
	unsigned int scan_priority;
}app_adp_wifi_option;

typedef void (* app_adp_wifi_scan_cb)(app_adp_wifi_result_t result, app_adp_wifi_ap_list * ap_list);

/*****************************************************************************
 *
 * FUNCTIO
 *      ol_wifi_mac_scan
 * DESCRIPTION 
 *      This API is used to scan the wifi info
 * PARAMETERS
 *      timeout_seconds : maximum scan time
 *      cb : scan callback
 * RETURN VALUES
 *      SUCCESS : 0
 *      FAIL : -1
 * RETURN MESSAGE
 *      NONE
 *
 *****************************************************************************/
extern int ol_wifi_mac_scan(uint32_t timeout_seconds, app_adp_wifi_scan_cb cb);

/*****************************************************************************
 *
 * FUNCTIO
 *			ol_wifi_mac_scan_option
 * DESCRIPTION 
 *			This API is used to set\get wifi scan option
 * PARAMETERS
 *			mode : 0 get mode    1:set mode
 *			option : option param
 *      option_len : size of option param struct
 * RETURN VALUES
 *			SUCCESS : 0
 *			FAIL : -1
 * RETURN MESSAGE
 *			NONE
 *
 *****************************************************************************/
extern int ol_wifi_mac_scan_option(unsigned char mode, void * option,unsigned int option_len);



#ifdef __cplusplus
}
#endif

#endif

