#ifndef __OEM_API_BND__
#define __OEM_API_BND__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifdef POSIX
 #include <semaphore.h>
#endif

/*oem lib extern functions*/
extern void lib_oem_tts_play_end_cb(void);
extern void lib_oem_player_need_data_len_cb(int datalen);
extern void lib_oem_record_cb(const char* data, int length);


/*tts functions*/
/*
* Function: lib_oem_tts_play
*
* Description: 
* push the tts data
*
* Rarameter: 
* text:unicode data
*
* Return:
* none
*/

int lib_oem_tts_play(char *text);

/*
* Function: lib_oem_tts_stop
*
* Description: 
* stop the tts 
*
* Rarameter: 
* none
*
* Return:
* none
*/

int lib_oem_tts_stop(void);

/*
* Function: lib_oem_tts_status
*
* Description: 
* get the tts status
*
* Rarameter: 
* none
*
* Return:
* 0-not work
* 1-working
*/

int lib_oem_tts_status(void);

/*
* Function: lib_oem_start_record
*
* Description: 
* start record for ptt or open device for record
*
* Rarameter: 
* none
*
* Return:
* none
*/

int lib_oem_start_record(void);

/*
* Function: lib_oem_stop_record
*
* Description: 
* stop record or close device for record
*
* Rarameter: 
* none
*
* Return:
* none
*/

int lib_oem_stop_record(void);

/*
* Function: lib_oem_start_play
*
* Description: 
* start play pcm, or open device for play
*
* Rarameter: 
* none
*
* Return:
* none
*/

int lib_oem_start_play(void);

/*
* Function: lib_oem_stop_play
*
* Description: 
* stop play pcm, or close device for play
*
* Rarameter: 
* none
*
* Return:
* none
*/

int lib_oem_stop_play(void);

/*
* Function: lib_oem_play
*
* Description: 
* push  pcm data
*
* Rarameter: 
* data:pcm data
* length: the length of data
*
* Return:
* receive data length
*/

int lib_oem_play(const char* data, int length);

/*
* Function: lib_oem_out_space
*
* Description: 
* pcm free space
*
* Rarameter: 
* none
*
* Return:
* > 0 free
* 0 busy
*/
int lib_oem_out_space(void);
/*
* Function: lib_oem_play_tone
*
* Description: 
* Play tone
*
* Rarameter: 
* type:
* [0]--start ptt
* [1]--stop ptt
* [2]--error
* [3]--start play
* [4]--stop play
*
* Return:
* none
*/
int lib_oem_play_tone(int type);

/*voice call functions */
int lib_oem_setup_call(char* dial_number);
int lib_oem_call_state(void);
int lib_oem_call_state_change_notify(void);
int lib_oem_call_hungup(void);

/* network functions*/

/*
* Function: lib_oem_socket_set_apn
*
* Description: 
* set the new apn 
*
* Rarameter: 
* apn
*
* Return:
* none
*/

void lib_oem_socket_set_apn(char *apn);

/*
* Function: lib_oem_socket_net_open
*
* Description: 
* Open the network data
*
* Rarameter: 
* none
*
* Return:
* 0-FAIL 
* 1-SUCCESS
*/

int  lib_oem_socket_net_open(void);

/*
* Function: lib_oem_socket_get_net_status
*
* Description: 
* Get network data status
*
* Parameter: 
* none
*
* Return:
* 0-FAIL 
* 1-SUCCESS
*/

int lib_oem_socket_get_net_status(void);

/*
* Function: lib_oem_socket_get_network
*
* Description: 
* Get network status
*
* Rarameter: 
* none
*
* Return:
* -1-FAIL
* 0- 
* 1-SUCCESS
*/

int  lib_oem_socket_get_network(void);

/*
* Function: lib_oem_get_rssi
*
* Description: 
* Get network signal strength
*
* Rarameter: 
* none
*
* Return:
* rssi 
*
*/

int  lib_oem_get_rssi(void);

/*
* Function: lib_oem_net_close
*
* Description: 
* Close the network
*
* Rarameter: 
* none
*
* Return:
* 0-SUCCESS
* 1-FAILURE
*
*/
int  lib_oem_net_close(void);

/*
* Function: lib_oem_reset_ps
*
* Description: 
* network module restart
*
* Rarameter: 
* none
*
* Return:
* 0-SUCCESS
* 1-FAILURE
*
*/
int lib_oem_reset_ps(void);

/*module init*/

/*
* Function: lib_oem_module_init
*
* Description: 
* Initialize mcm cilent for network, sim,sms,etc
*
* Rarameter: 
* none
*
* Return:
* 0-FAILURE
* 1-SUCCESS
*
*/

int lib_oem_module_init(void);


/*
* Function: lib_oem_play_open_pcm
*
* Description: 
* Initialize pcm for TTS
*
* Input: 
* none
*
* Return:
* 0-FAILURE
* 1-SUCCESS
*
*/

int lib_oem_play_open_pcm(void);

/*sim*/

/*
* Function: lib_oem_is_sim_present
*
* Description: 
* Check the status of the SIM card
*
* Input: 
* none
*
* Return:
* 0-SIMcard is absent
* 1-SIM card is present
*
*/
int lib_oem_is_sim_present(void);

/*========================================================================================
FUNCTION: 
lib_oem_get_device_serial_number

DESCRIPTION:
get imei and meid

PARAMETERS:
data:imei+0x0a+meid+0x0a+0x00

RETURN:
[0]SUCCESS
[-1]FAILURE

=========================================================================================*/

int lib_oem_get_device_serial_number(char* data);

/*========================================================================================
FUNCTION: 
lib_oem_get_sim_serial_number

DESCRIPTION:
get iccid and imsi

PARAMETERS:
data:iccid+0x0a+imsi+0x0a+0x00

RETURN:
[0]SUCCESS
[-1]FAILURE

=========================================================================================*/

int lib_oem_get_sim_serial_number(char* data);

/*========================================================================================
FUNCTION: 
lib_oem_get_model

DESCRIPTION:
get model name
RETURN:
name

=========================================================================================*/
char* lib_oem_get_model(void);

/*========================================================================================
FUNCTION: 
lib_oem_get_system_version

DESCRIPTION:
get system version
RETURN:
version

=========================================================================================*/
char* lib_oem_get_system_version(void);

/*========================================================================================
FUNCTION: 
lib_oem_send_uart

DESCRIPTION:
poc uart sent at

PARAMETERS:
data:AT  size: AT len

RETURN:
[0]SUCCESS
[-1]FAILURE

=========================================================================================*/
int lib_oem_send_uart(const char* data, int size);

/*========================================================================================
FUNCTION: 
lib_oem_uart_cb

DESCRIPTION:
poc uart recv at

PARAMETERS:
data:AT  size: AT len

RETURN:
[0]SUCCESS
[-1]FAILURE

=========================================================================================*/
extern int lib_oem_uart_cb(char* data, int size);

/*========================================================================================
FUNCTION: 
poc_uart_open

DESCRIPTION:
poc open uart
=========================================================================================*/
void poc_uart_open(void);

/*========================================================================================
FUNCTION: 
poc_uart_close

DESCRIPTION:
poc close uart
=========================================================================================*/
void poc_uart_close(void);

/**远程升级初始化
*@return 0:  表示成功
*   <0：  表示失败
**/
int lib_oem_ota_init(void);

/**远程升级下载
*@param  data:    下载固件包数据
*@param  len:    下载固件包长度
*@param  total:    固件包总大小
*@return 0:  表示成功
*   <0：  表示失败
**/
int lib_oem_ota_process(char* data, unsigned int len, unsigned int total);

/**远程升级结束且校验
*@return 0:  表示成功, 成功后模块自动重启升级
*   <0：  表示失败
**/
int lib_oem_ota_done(void);

int broad_request_weather_info(double lon,double lat);
int lib_oem_device_bts(int* mcc,int* mnc,int* lac, int* cid);

#ifdef __cplusplus
}
#endif

#endif /*__OEM_API_BND__*/

