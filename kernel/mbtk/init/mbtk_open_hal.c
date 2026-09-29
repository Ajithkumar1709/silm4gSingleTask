#include <time.h>
#include "mbtk_pub_type.h"
#include "mbtk_mqttclient.h"
#include "mbtk_fota_open.h"
#include "sys_version.h"
#include "mbtk_acctimer.h"
#include "mbtk_audio_define.h"

#define MBTK_LOG(mod, fun, ...) \
    do { \ 
		DIAG_FILTER(MBTK, mod, fun,DIAG_INFORMATION);	 \
		diagPrintf(##__VA_ARGS__);	 \
    } while(0)


//#define uart_printf(fmt, ...)



#if 1//ndef CUSTOMER_MBTK_ANTI
unsigned char mbtk_get_secboot_status(void)
{
	return 0;
}

unsigned short mbtk_get_flash_id(void)
{
	return 0;
}

#endif





char*  mbtk_mqtt_set_client_id(mqtt_client_t *client, char* id)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_client_id(client, id);
#else
	//uart_printf("not support");
	return NULL;
#endif
}

char *mbtk_mqtt_set_user_name(mqtt_client_t *client, char* name)
{
#ifndef NO_PAHO_MQTT
		return mqtt_set_user_name(client, name);
#else
		//uart_printf("not support");
		return NULL;
#endif
	
}



char*  mbtk_mqtt_set_password(mqtt_client_t *client, char* pwd)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_password(client, pwd);
#else
	//uart_printf("not support");
	return NULL;
#endif
}
char*  mbtk_mqtt_set_host(mqtt_client_t *client, char* host)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_host(client, host);
#else
	//uart_printf("not support");
	return NULL;
#endif
}
char*  mbtk_mqtt_set_port(mqtt_client_t *client, char* port)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_port(client, port);
#else
	//uart_printf("not support");
	return NULL;
#endif
}
char*  mbtk_mqtt_set_ca(mqtt_client_t *client, char* ca)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_ca(client, ca);
#else
	//uart_printf("not support");
	return NULL;
#endif
}
char*  mbtk_mqtt_set_cli_crt(mqtt_client_t *client, char* cli_crt)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_cli_crt(client, cli_crt);
#else
	//uart_printf("not support");
	return NULL;
#endif
}
char*  mbtk_mqtt_set_cli_key(mqtt_client_t *client, char* cli_key)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_cli_key(client, cli_key);
#else
	//uart_printf("not support");
	return NULL;
#endif
}
void*  mbtk_mqtt_set_reconnect_data(mqtt_client_t *client, void* data)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_reconnect_data(client, data);
#else
	//uart_printf("not support");
	return NULL;
#endif
}
uint16_t  mbtk_mqtt_set_keep_alive_interval(mqtt_client_t *client, uint16_t interval)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_keep_alive_interval(client, interval);
#else
	//uart_printf("not support");
	return NULL;
#endif
}


uint32_t  mbtk_mqtt_set_will_flag(mqtt_client_t *client, uint32_t will)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_will_flag(client, will);
#else
	//uart_printf("not support");
	return NULL;
#endif
}

uint32_t  mbtk_mqtt_set_clean_session(mqtt_client_t *client, uint32_t session)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_clean_session(client, session);
#else
	//uart_printf("not support");
	return NULL;
#endif
}



uint32_t  mbtk_mqtt_set_version(mqtt_client_t *client, uint32_t interval)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_version(client, interval);
#else
	//uart_printf("not support");
	return NULL;
#endif
}

uint32_t  mbtk_mqtt_set_cmd_timeout(mqtt_client_t *client, uint32_t time)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_cmd_timeout(client, time);
#else
	//uart_printf("not support");
	return NULL;
#endif
}

uint32_t  mbtk_mqtt_set_conn_timeout(mqtt_client_t *client, uint32_t time)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_conn_timeout(client, time);
#else
	//uart_printf("not support");
	return NULL;
#endif
}

uint32_t  mbtk_mqtt_set_ssl_vsn(mqtt_client_t *client, uint32_t vsn)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_ssl_vsn(client, vsn);
#else
	//uart_printf("not support");
	return NULL;
#endif
}


uint32_t  mbtk_mqtt_set_read_buf_size(mqtt_client_t *client, uint32_t read_size)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_read_buf_size(client, read_size);
#else
	//uart_printf("not support");
	return NULL;
#endif
}


uint32_t  mbtk_mqtt_set_write_buf_size(mqtt_client_t *client, uint32_t write_size)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_write_buf_size(client, write_size);
#else
	//uart_printf("not support");
	return NULL;
#endif
}

uint32_t  mbtk_mqtt_set_reconnect_try_duration(mqtt_client_t *client, uint32_t duration)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_reconnect_try_duration(client, duration);
#else
	//uart_printf("not support");
	return NULL;
#endif
}

reconnect_handler_t  mbtk_mqtt_set_reconnect_handler(mqtt_client_t *client, reconnect_handler_t handler)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_reconnect_handler(client, handler);
#else
	//uart_printf("not support");
	return NULL;
#endif
}


interceptor_handler_t  mbtk_mqtt_set_interceptor_handler(mqtt_client_t *client, interceptor_handler_t handler)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_interceptor_handler(client, handler);
#else
	//uart_printf("not support");
	return NULL;
#endif
}

error_handler_t mbtk_mqtt_set_error_callback(mqtt_client_t *client, error_handler_t handler)
{
#ifndef NO_PAHO_MQTT
    return mqtt_set_error_callback(client, handler);
#else
    //uart_printf("not support");
    return NULL;
#endif
}

mqtt_client_t*  mbtk_mqtt_lease()
{
#ifndef NO_PAHO_MQTT
	return mqtt_lease();
#else
	//uart_printf("not support");
	return NULL;
#endif
}


int  mbtk_mqtt_release(mqtt_client_t *client)
{
#ifndef NO_PAHO_MQTT
	return mqtt_release(client);
#else
	//uart_printf("not support");
	return NULL;
#endif
}



int  mbtk_mqtt_connect(mqtt_client_t *client)
{
#ifndef NO_PAHO_MQTT
	return mqtt_connect(client);
#else
	//uart_printf("not support");
	return NULL;
#endif
}


int  mbtk_mqtt_disconnect(mqtt_client_t *client)
{
#ifndef NO_PAHO_MQTT
	return mqtt_disconnect(client);
#else
	//uart_printf("not support");
	return NULL;
#endif
}


int  mbtk_mqtt_keep_alive(mqtt_client_t *client)
{
#ifndef NO_PAHO_MQTT
	return mqtt_keep_alive(client);
#else
	//uart_printf("not support");
	return NULL;
#endif
}


int  mbtk_mqtt_subscribe(mqtt_client_t* c, const char* topic_filter, mqtt_qos_t qos, message_handler_t handler)
{
#ifndef NO_PAHO_MQTT
	return mqtt_subscribe(c, topic_filter, qos, handler);
#else
	//uart_printf("not support");
	return NULL;
#endif
}


int  mbtk_mqtt_unsubscribe(mqtt_client_t *client, const char* topic_filter)
{
#ifndef NO_PAHO_MQTT
	return mqtt_unsubscribe(client, topic_filter);
#else
	//uart_printf("not support");
	return NULL;
#endif
}



int  mbtk_mqtt_publish(mqtt_client_t* client , const char* buffer, mqtt_message_t* msg)
{
#ifndef NO_PAHO_MQTT
	return mqtt_publish(client, buffer, msg);
#else
	//uart_printf("not support");
	return NULL;
#endif
}

int  mbtk_mqtt_list_subscribe_topic(mqtt_client_t* client )
{
#ifndef NO_PAHO_MQTT
	return mqtt_list_subscribe_topic(client);
#else
	//uart_printf("not support");
	return NULL;
#endif
}

int  mbtk_mqtt_set_will_options(mqtt_client_t* client, char *topic, mqtt_qos_t qos, uint8_t retained, char *message)
{
#ifndef NO_PAHO_MQTT
	return mqtt_set_will_options(client, topic, qos, retained, message);
#else
	//uart_printf("not support");
	return NULL;
#endif
}

int mbtk_mqtt_connect_asyn(mqtt_client_t* c,mqtt_callback_handler_t callback_handle)
{
	
#ifndef NO_PAHO_MQTT
		return mqtt_connect_asyn(c, callback_handle);
#else
		//uart_printf("not support");
		return NULL;
#endif
}

int mbtk_mqtt_subscribe_asyn(mqtt_client_t* c, const char* topic_filter, mqtt_qos_t qos, void *handler)
{
	
#ifndef NO_PAHO_MQTT
		return mqtt_subscribe_asyn(c, topic_filter,qos, handler);
#else
		//uart_printf("not support");
		return NULL;
#endif
}


int mbtk_mqtt_unsubscribe_asyn(mqtt_client_t* c, const char* topic_filter)
{
	
#ifndef NO_PAHO_MQTT
		return mqtt_unsubscribe_asyn(c, topic_filter);
#else
		//uart_printf("not support");
		return NULL;
#endif
}

int mbtk_mqtt_publish_asyn(mqtt_client_t* c, const char* topic_filter, mqtt_message_t* msg)
{
	
#ifndef NO_PAHO_MQTT
		return mqtt_publish_asyn(c, topic_filter, msg);
#else
		//uart_printf("not support");
		return NULL;
#endif
}


int mbtk_mqtt_keep_alive_asyn(mqtt_client_t* c)
{
	
#ifndef NO_PAHO_MQTT
		return mqtt_keep_alive_asyn(c);
#else
		//uart_printf("not support");
		return NULL;
#endif
}


int mbtk_mqtt_disconnect_asyn(mqtt_client_t* c)
{
	
#ifndef NO_PAHO_MQTT
		return mqtt_disconnect_asyn(c);
#else
		//uart_printf("not support");
		return NULL;
#endif
}





int mbtk_mqtt_release_asyn(mqtt_client_t* c)
{
	
#ifndef NO_PAHO_MQTT
		return mqtt_release_asyn(c);
#else
		//uart_printf("not support");
		return NULL;
#endif
}

#ifdef NO_AUDIO
typedef void (*audioGsmStartVoicePath_t)(void);
typedef void (*audioGsmStopVoicePath_t)(void);
//#ifdef MACRO_FOR_LWG
typedef void (*audioGsmGetVocoderTypeRate_t)(unsigned short *vocoderType, unsigned short *vocoderRate);
//#endif
typedef char  (*audioGsmGetDtxSupport_t)(void);
typedef void* (*audioGsmGetTxBuffer_t)(void);
typedef void  (*audioGsmSetAmrToc_t)(unsigned short);
typedef void  (*audioGsmSetAmrSidTypeInd_t)(unsigned short);
typedef void  (*audioGsmSetEncoderFlags_t)(unsigned short);
typedef void  (*audioGsmSetDecoderSidInd_t)(unsigned short);

#if 0
void audioPhase1Init(void)
{
    return;
}
#endif

void audioBindGsmGetDtxSupport(audioGsmGetDtxSupport_t audioGsmGetDtxSupport)
{
    return;
}

void audioBindGsmGetTxBuffer(audioGsmGetTxBuffer_t audioGsmGetTxBuffer)
{
    return;
}

void audioBindGsmGetVocoderTypeRate(audioGsmGetVocoderTypeRate_t audioGsmGetVocoderTypeRate)
{
    return;
}

void audioBindGsmSetAmrSidTypeInd(audioGsmSetAmrSidTypeInd_t audioGsmSetAmrSidTypeInd)
{
    return;
}

void audioBindGsmSetAmrToc(audioGsmSetAmrToc_t audioGsmSetAmrToc)
{
    return;
}

void audioBindGsmSetDecoderSidInd(audioGsmSetDecoderSidInd_t audioGsmSetDecoderSidInd)
{
    return;
}

void audioBindGsmSetEncoderFlags(audioGsmSetEncoderFlags_t audioGsmSetEncoderFlags)
{
    return;
}

void audioBindGsmStartVoicePath(audioGsmStartVoicePath_t audioGsmStartVoicePath)
{
    return;
}

void audioBindGsmStopVoicePath(audioGsmStopVoicePath_t audioGsmStopVoicePath)
{
    return;
}

int AudioHAL_AifDrain(void)
{
    return 0;
}

int AudioHAL_AifPlayStream(void *playedStream)
{
    return 0;
}

void AudioHAL_AifStopPlay(void)
{
    return;
}

int AudioHAL_SetResBufCnt(unsigned int bufCnt)
{
    return 0;
}

int AudioHAL_AifPause(char pause)
{
    return 0;
}

char CraneCodecADCOnOff(char OnOff)
{
    return FALSE;
}

typedef void (*AUDIOHAL_HeadsetReport_T) (UINT32 plug, UINT32 type, UINT32 event);

void AudioHAL_AifBindHeadsetDetectionCB(AUDIOHAL_HeadsetReport_T cb)
{
    return;
}

void AudioHAL_AifGetHeadsetInfo(UINT32* plug, UINT32* type)
{
    return;
}

UINT32 AudioHAL_AifGetVolume(void)
{
    return 0;
}

void AudioHAL_AifHeadsetDetection(char onoff)
{
    return;
}

void AudioHAL_set_close_delay(unsigned int cnt)
{
    return;
}

void ACMAudioRBT_Start(int area)
{
    return ;
}

void ACMAudioRBT_Stop(void)
{
    return ;
}

void StartVoLTEAudio(UINT32 volteModeToUse)
{
    return ;
}

void StopVoLTEAudio(void)
{
    return ;
}

void amrBindCpdrRx(void *callback)
{
    return ;
}

void amrBindTxFrameVoLTE(   void *  amrTxFrame)
{
    return ;
}

void ACMAudioDTMFPushButton_Start(int ascii_pushbutton)
{
    return ;
}

void ACMAudioDTMFPushButton_Stop(void)
{
    return ;
}



#endif

#ifndef MBTK_QRCODE_SUPPORT
typedef void (*qrcode_callback)(void *outdata);

int mbtk_pic_scan_get_ver(char *ver, int versize)
{
	return -1;	
}

int mbtk_qr_decoder_init(unsigned char  dectaskprio,
	unsigned int height,
	unsigned int width,
	unsigned char decbufcnt,
	qrcode_callback decodecb)
{
	return -1;
}

int mbtk_qr_decoder_deinit(void)
{
	return -1;
}

int mbtk_qr_start_decode_t(void)
{
	return -1;
}

int mbtk_qr_set_pic_buffer(unsigned int buffaddr,unsigned int dump_addr)
{
	return -1;
}

int mbtk_get_qr_decoder_authorize_statue(void)
{
	return -1;
}

void mbtk_set_qr_decoder_enable(unsigned char op)
{
	return;
}

#endif

#ifdef REMOVE_MBEDTLS

void SSLSetConfig(void * sslCtx, void* config)
{
}

int SSLCtxInit(void * sslCtx)
{
	return -1;
}

void SSLCtxDeinit(void * sslCtx)
{}

int SSLHandshake(void * sslCtx, int timeout_ms)
{
	return -1;
}

int SSLWrite(void * sslCtx, const void* data, int sz)
{
	return -1;
}


int SSLRead(void * sslCtx, void* data, int sz)
{
	return -1;
}


int SSLShutdown(void * sslCtx)
{
	return -1;
}

int mbtk_ssl_get_optation(char *op_name,void *value)
{
	return -1;
}

int mbtk_ssl_set_optation(char *op_name,void *value)
{
	return -1;
}

#ifdef MBTK_WEBSOCKET_SUPPORT
mbtk_ssl_client_t * mbtk_ssl_client_init(int fd, 
											   const char *addr,
											   char *ca_path,
											   char *cli_cert_path,
											   char *cli_key_path)
{
	return NULL;
}
void mbtk_ssl_client_shutdown(mbtk_ssl_client_t * client, UINT8 cert1)
{
}

int mbtk_ssl_write( void *ssl, char *buf, int len ){	return -1;}
int mbtk_ssl_read( void *ssl, char *buf, int len ){	return -1;}




void mbtk_transport_ssl_enable_global_ca_store(mbtk_transport_handle_t t)
{
    
}

void mbtk_transport_ssl_set_cert_data(mbtk_transport_handle_t t, const char *data, int len)
{
   
}

void mbtk_transport_ssl_set_client_cert_data(mbtk_transport_handle_t t, const char *data, int len)
{
    
}

void mbtk_transport_ssl_set_client_key_data(mbtk_transport_handle_t t, const char *data, int len)
{
}

void mbtk_transport_ssl_skip_common_name_check(mbtk_transport_handle_t t)
{
    
}

void* mbtk_transport_ssl_init()
{
    return NULL;
}

#endif

#ifndef NO_PAHO_MQTT


int nettype_tls_connect(void* n)
{
	return -1;
}


void nettype_tls_disconnect(void* n) 
{
    return -1;
}

int nettype_tls_write(void *n, unsigned char *buf, int len, int timeout)
{
    return -1;
}

int nettype_tls_read(void *n, unsigned char *buf, int len, int timeout)
{
    return -1;
}


int nettype_tls_socket_errno(network_t *n)
{
    return -1;
}



#endif



#endif




#ifndef MBTK_FTP_ENABLE
int mbtk_open_ftp_mkdir(char *dir)
{return -1;}
int mbtk_open_ftp_rmdir(char *dir)
{return -1;}
int mbtk_open_ftp_delete(char *file)
{return -1;}
int mbtk_open_ftp_size ( char* remote_file )
{return -1;}
int mbtk_open_ftp_list( char *dir , char ** p_list, unsigned long * p_list_len)
{return -1;}
int mbtk_open_ftp_getfile(char *remote_file, char *local_file, int rest)
{return -1;}
int mbtk_open_ftp_putfile( char *remote_file, char *local_file, int rest )
{return -1;}
int mbtk_open_ftp_get_current_dir(char *file_path)
{return -1;}
int mbtk_open_ftp_get_errno(void)
{return -1;}
int mbtk_open_ftp_set_config_params ( void* config_params )
{return -1;}
void* mbtk_open_ftp_get_config_params(void)
{return NULL;}
#endif

#ifndef MBTK_SECFOAT_SUPPORT
int secboot_is_fuse_enabled(void){return 0;}
int efuse_read_bank2(unsigned      int* buffer,unsigned int length){return -1;}	
#endif


#if !defined(MBTK_FOTA_SUPPORT)||!defined(MBTK_FOAT_NORMAL) 

void *mbtk_app_update_create_context(void){}
void mbtk_app_update_destory_context(void *context){}
int mbtk_app_update_load_image(void *context,char *data,unsigned int length){return -1;}
int mbtk_app_update_image_verify(void *context,unsigned int package_size){return -1;}
int mbtk_app_update_set_flag(void *context){return -1;}

#if !defined(MBTK_MINI_APP_FOTA)
int mbtk_fota_context_init(mbtk_fota_server_info *server_info,int package_size,bool need_check,void (*callback)(void *)){return -1;}
void mbtk_fota_context_deinit(void){}
int mbtk_fota_pkg_write(char * data, int dataLen ,unsigned int package_size){return -1;}
int mbtk_fota_pkg_flush_flash(void){return -1;}
int mbtk_fota_image_verify(void){return -1;}
#endif

int mbtk_fota_firmware_download(mbtk_fota_server_info *server_info,bool auto_reboot,void (*callback)(void *)){return -1;}
void mbtk_fota_stop_reboot(void){return -1;}

#endif

#if defined(MBTK_FOTA_SUPPORT) && defined(MBTK_FOAT_NORMAL)
int mbtk_mini_fota_firmware_download(mbtk_fota_server_info *server_info, void (*callback)(void *)){return -1;}
void mbtk_mini_fota_force_app_update(char onoff) {}
#endif


#ifndef MBTK_WEBSOCKET_SUPPORT
int mbtk_websocket_client_init()
{	return -1;}

int mbtk_websocket_register_events()
{	return -1;}

int mbtk_websocket_client_start()
{	return -1;}

bool mbtk_websocket_client_is_connected()
{	return -1;}

int mbtk_websocket_client_send()
{	return -1;}

int mbtk_websocket_client_send_text()
{	return -1;}

int mbtk_websocket_client_send_bin()
{	return -1;}


int mbtk_websocket_client_stop()
{	return -1;}


int mbtk_websocket_client_close()
{	return -1;}


int mbtk_websocket_client_close_with_code()
{	return -1;}

int mbtk_websocket_client_destroy()
{	return -1;}

#endif


MBTK_AUDIO_PA_HOOK mbtk_audio_pa_hook = NULL;


#ifdef NO_AUDIO



void MBTK_Audio_Play_Start(MBTK_AUDIO_PLAYER_CALLBACK cb)
{}


int  MBTK_Audio_Fill(uint8 *data, uint32 size)
{
	return -1;
}

INT8 MBTK_Audio_Enable(MBTK_AUDIO_ITF itf)
{
	return -1;
}

/***********************************
*MBTK_Audio_Disable
************************************/
void MBTK_Audio_Disable(void)
{}
void MBTK_Audio_Register_PA_Hook(MBTK_AUDIO_PA_HOOK hook)
{}


/***********************************
*MBTK_Audio_ItfSwitch
************************************/
void MBTK_Audio_ItfSwitch(MBTK_AUDIO_ITF itf)
{
}

/***********************************
*MBTK_Aduio_Play_Onetime
************************************/
void MBTK_Audio_SetSamplerate(UINT32  samplerate)
{
}

/***********************************
*MBTK_Aduio_Play_Onetime
************************************/
void MBTK_Audio_SetChannels(UINT32  channels)
{
}

/***********************************
*MBTK_Aduio_Play_Onetime
************************************/
void MBTK_Audio_Play_Onetime(UINT8 *buffer, UINT32 len,MBTK_VOLUME_LEVEL volume,MBTK_AUDIO_PLAYER_CALLBACK func,void *param)
{
}

/***********************************
*MBTK_Audio_Play_Repeat
************************************/
void MBTK_Audio_Play_Repeat(UINT8 *buffer, UINT32 len, MBTK_VOLUME_LEVEL volume)
{
}

/***********************************
*MBTK_Aduio_Play_End
************************************/
void MBTK_Audio_Play_End(void)
{
}

/***********************************
*MBTK_Audio_Play_File_Start
************************************/ 
void MBTK_Audio_Play_File_Start(const char *path, MBTK_VOLUME_LEVEL volume, MBTK_AUDIO_PLAYER_CALLBACK func, void *para)
{
}

/***********************************
*MBTK_Audio_Play_File_End
************************************/ 
void MBTK_Audio_Play_File_End(void)
{
}

/***********************************
*MBTK_Audio_Play_Pause
************************************/ 
void MBTK_Audio_Play_Pause(void)
{
}

/***********************************
*MBTK_Audio_Play_Resume
************************************/ 
void MBTK_Audio_Play_Resume(void)
{
}

/***********************************
*MBTK_Audio_Record_Buffer_Start
************************************/ 
void MBTK_Audio_Record_Buffer_Start(UINT8 *buffer, UINT32 bufsize, UINT32 maxDurationMs, MBTK_AUDIO_RECORD_CALLBACK func,UINT8 format)
{
}

/***********************************
*MBTK_Audio_Record_Buffer_Stop
************************************/ 
UINT32 MBTK_Audio_Record_Buffer_Stop(UINT32 *recSize, UINT32 *durationMs)
{
	return -1;
}

void MBTK_Audio_Continue_Record_Start(void* func)
{
}

/***********************************
*MBTK_Audio_Continue_Record_Stop
************************************/ 
UINT32 MBTK_Audio_Continue_Record_Stop(void)
{
	return -1;
}

/***********************************
*MBTK_Audio_Record_File_Start
************************************/ 
void MBTK_Audio_Record_File_Start(const char *path, MBTK_AUDIO_RECORD_CALLBACK func,UINT8 format)
{
}

/***********************************
*MBTK_Audio_Record_File_Stop
************************************/ 
UINT32 MBTK_Audio_Record_File_Stop(UINT32 *pFile_size)
{
}

void MBTK_Audio_Tone_Play(UINT8 Type,UINT8 Gain,UINT32 LastTime)
{
	
}


UINT32 mbtk_get_volume()
{
	return 0;
}

void mbtk_set_volume(int level)
{
}
unsigned int mbtk_get_volume_ex(char channel)
{return -1;}

void mbtk_set_volume_ex(char channel,char level)
{return -1;}


int mbtk_audioplay_play_buffer_once(void *buffer, uint32_t len, void *play_cb, MBTK_VOLUME_LEVEL volume)
{return -1;}

void mbtk_audioplay_buffer_stop()
{}
int  mbtk_audioplay_file_play(const char *path, void *   play_cb, void * process_cb, MBTK_VOLUME_LEVEL volume)
{return -1;}

void mbtk_audioplay_pause(void)
{ return ; }
void mbtk_audioplay_resume(void)
{ return ; }
void mbtk_audioplay_stop(void)
{ return ; }

int  mbtk_set_audio_spi_port(uint16 port)
{return -1;}


uint16 mbtk_get_audio_spi_port(void)
{return -1;}

void mbtk_set_tone_volume(int level){return -1;}
int mbtk_get_tone_volume(){return -1;}
int mbtk_set_mic_volume(int level){return -1;}


#endif



uint8_t mbtk_get_tts_status()
{
	uint8_t ret=0;

	#ifdef MBTK_TTS_SUPPORT
	ret = !mbtk_tts_check_can_stop();
	#endif
	
	return ret;
}

#ifndef MBTK_AUDIO_PWM	
extern bool mp3IsPlaying();
#endif
uint8_t mbtk_get_audio_status()
{
	
#ifndef NO_AUDIO
	if(mbtk_oem_pcm_play_status() || mbtk_get_tts_status() 
	#ifdef MP3_DECODE
	#ifndef MBTK_AUDIO_PWM
	|| mp3IsPlaying()
	#endif
	#endif
	)
		return 1;
#endif
	return 0;
}

int mbtk_hal_tts_set_cb(MBTK_AUDIO_PLAYER_CALLBACK        cb)
{
	int  ret=-1;
	
#ifdef MBTK_TTS_SUPPORT
	ret = mbtk_tts_set_cb(cb);
#endif

	return ret;
}

int mbtk_hal_tts_set_speed(unsigned char speed)
{
	int  ret=-1;
	
#ifdef MBTK_TTS_SUPPORT
	ret = mbtk_tts_set_speed(speed);
#endif

	return ret;
}

int mbtk_hal_tts_get_speed(void)
{
	int  ret=-1;
	
#ifdef MBTK_TTS_SUPPORT
	ret = mbtk_tts_get_speed();
#endif

	return ret;
}

int mbtk_hal_tts_spk(char *txt, UINT16 txt_len, int data_type, UINT8 from)
{
	int  ret=-1;
	
#ifdef MBTK_TTS_SUPPORT
	ret = mbtk_tts_spk(txt, txt_len, data_type, from);
#endif

	return ret;
}

int mbtk_hal_tts_spk_ex(char *txt, UINT16 txt_len, int data_type, UINT8 from)
{
	int  ret=-1;
	
#ifdef MBTK_TTS_SUPPORT
	ret = mbtk_tts_spk_ex(txt, txt_len, data_type, from);
#endif

	return ret;
}

#ifndef MBTK_TTS_SUPPORT
bool mbtk_tts_stop_flag(void)
{
	return 0;
}
#endif

int mbtk_hal_tts_stop()
{
	int  ret=-1;
	
#ifdef MBTK_TTS_SUPPORT
	ret = mbtk_tts_stop();
#endif

	return ret;
}

#ifndef MBTK_TTS_SUPPORT
int mbtk_tts_get_play_status(void)
{return -1;}
#endif

int mbtk_hal_tts_set_volume(int volume)
{
    int ret = -1;

#ifdef MBTK_TTS_SUPPORT
    ret = mbtk_tts_set_volume(volume);
#endif
    return ret;
}

int mbtk_hal_tts_set_role(int role_type)
{
    int ret = -1;

#ifdef MBTK_TTS_SUPPORT
    ret = mbtk_tts_set_role(role_type);
#endif
    return ret;
}

int mbtk_hal_tts_set_vemode(int vemode)
{
    int ret = -1;

#ifdef MBTK_TTS_SUPPORT
    ret = mbtk_tts_set_vemode(vemode);
#endif
    return ret;
}

int mbtk_hal_tts_set_digit(int digit)
{
    int ret = -1;

#ifdef MBTK_TTS_SUPPORT
    ret = mbtk_tts_set_digit(digit);
#endif
    return ret;
}



int mbtk_hal_tts_set_pitch(int pitch)
{
    int ret = -1;

#ifdef MBTK_TTS_SUPPORT
    ret = mbtk_tts_set_pitch(pitch);
#endif
    return ret;
}


int mbtk_hal_tts_get_pitch(void)
{
    int ret = -1;

#ifdef MBTK_TTS_SUPPORT
    ret = mbtk_tts_get_pitch();
#endif
    return ret;
}


int mbtk_tts_support_flag(void)
{
#ifdef MBTK_TTS_SUPPORT
    return 1;
#else
    return 0;
#endif
}



#ifndef MP3_DECODE

typedef void(*mbtk_mp3_play_cb)(int); 

int mbtk_mp3_buffer_start(const char *data,int length, mbtk_mp3_play_cb *cb, void* process_cb)
{return -1;}

int mbtk_mp3_buffer_start_ex(mbtk_mp3_play_cb *cb, audio_process_cb process_cb)
{return -1;}


int mbtk_mp3_buffer_play(void *buffer, int size)
{return -1;}

int mbtk_mp3_buffer_play_stop()
{return -1;}

int mbtk_mp3_file_play_start(char *file_name,mbtk_mp3_play_cb *cb,void* process_cb)
{return -1;}

int mbtk_mp3_file_play_stop(char drain)
{return -1;}

int mbtk_mp3_play_pause(UINT8 type)
{return -1;}

int mbtk_mp3_play_resume(UINT8 type)
{return -1;}


int mbtk_tts_send_next(const char *data,int length,int data_type, int form)
{return -1;}


void mbtk_tts_stop_before()
{}

void mbtk_tts_stop_after()
{}




#endif


#ifndef MBTK_AMR_AUDIO_SUPPORT 
typedef void(*mbtk_amr_play_cb)(int); 

int mbtk_amr_buffer_play_start(const char *data,int length, void* *cb)
{return -1;}

int mbtk_amr_buffer_play_start_ex(mbtk_amr_play_cb *cb)
{return -1;}


int mbtk_amr_file_play_start(char *file_name, void* *cb)
{return -1;}

int mbtk_amr_play_stop(void)
{return -1;}

int mbtk_amr_buffer_play(const char *data,int length)
{return -1;}


#endif



#ifndef MBTK_ACCTIMER_SUPPORT

int ol_acc_timer_create(mbtk_acc_timer_config *cfg)
{   return -1;  }



int ol_acc_timer_delete(int acc_timer_id)
{   return -1;  }


int ol_acc_timer_start(int acc_timer_id,mbtk_acc_timer_config *pTimerCfg)
{   return -1;  }


int ol_acc_timer_stop(int acc_timer_id)
{   return -1;  }


int ol_acc_timer_start_ex(unsigned int flag,
						  unsigned int period,
						  ol_acc_timer_cb timer_cb,
						  unsigned int timer_params
					     )
{   return -1;  }




MBTK_ACC_TIMER_STATUS ol_acc_get_timer_status(int acc_timer_id)
{   return -1;  }



#endif

#ifndef MBTK_AWSIOT_SUPPORT
//#include "aws_iot_fleet_provisioning_api.h"
bool mbtk_aws_iot_fleet_provisioning(int aws_fp_config, void *aws_fp_info)
{   return false;  }
#endif


#ifndef __MBTK_GNSS_SUPPORT__

typedef void(*mbtk_gps_nmea)(char *nmea);

void *mbtk_get_gps_info()
{
	return 0;
}

int mbtk_gps_power(int on_off)
{
	return -1;
}

int mbtk_gps_operation(int cmd)
{
	return -1;
}

int mbtk_set_gps_nmea_cb(mbtk_gps_nmea nmea_cb)
{
	return -1;
}

int mbtk_gps_get_status(void)
{
	return -1;
}


int mbtk_gps_agps_open(void)
{
	return -1;
}


#endif



#ifndef MBTK_MQTT_IBM_SUPPORT
void NetworkInit(void *param, void*param1, int param2)
{
  
}
int NetworkConnect(void*param, char*param1, int param2)
{
	return -1;
}
void NetworkDisconnect(void*param)
{}
void MQTTClientInit(void* client, void* network, unsigned int command_timeout_ms,
		unsigned char* sendbuf, size_t sendbuf_size, unsigned char* readbuf, size_t readbuf_size)
{}
void MQTTClientDeinit(void* client){}
int MQTTConnect(void* client, void* options)
{ 	return -1;  }
int MQTTDisconnect(void* client){ 	return -1;  }
int MQTTStartTask(void* client)
{ 	return -1;  }
int MQTTSubscribe(void* client, const char* topicFilter, int QoS, void *messageHandler)
{ 	return -1;  }
int MQTTUnsubscribe(void* client, const char* topicFilter){ 	return -1;  }
int MQTTPublish(void* client, const char*param, void*param1){ 	return -1;  }
int MQTTYield(void* client, int time){ 	return -1;  }

#endif

#ifndef MBTK_ZIP_SUPPORT
int mbtk_file_unzip(const char *zip_filename, const char *extract_dir){ return -1; }
#endif
#ifndef MBTK_ESIM_SUPPORT
typedef struct {
    int opt_int;
    char *opt_string;
}EsimProfileOptList_t;

typedef void (*EsimMessageCallback)(int msg_type, const char *data, int data_len);

void mbtk_esim_set_location(int location){   return;  }
int mbtk_esim_chip_info(void){         return -1;  }
int mbtk_esim_chip_defaultsmdp(const char *defaultsmdp){   return -1;  }
int mbtk_esim_chip_purge(void){         return -1;  }
int mbtk_esim_profile_list(void){         return -1;  }
int mbtk_esim_profile_nickname  (const char *iccid, const char *alias){         return -1;  }
int mbtk_esim_profile_enable  (const char *iccid_or_aid, int refreshflag){         return -1;  }
int mbtk_esim_profile_disable  (const char *iccid_or_aid,int refreshflag){         return -1;  }
int mbtk_esim_profile_delete  (const char *iccid_or_aid){         return -1;  }
int mbtk_esim_profile_download(EsimProfileOptList_t *opt_list, unsigned int numbers, unsigned int timeout){         return -1;  }
int mbtk_esim_profile_discovery(EsimProfileOptList_t *opt_list, unsigned int numbers){         return -1;  }
void mbtk_esim_profile_read_new_iccid(char *iccid){   return;}
int mbtk_esim_notification_list(void){         return -1;  }
int mbtk_esim_notification_process  (int remove_flag, int all_flag, unsigned long *sequence_id, unsigned int numbers, unsigned int timeout){         return -1;  }
int mbtk_esim_notification_remove   (int all_flag, unsigned long *sequence_id, unsigned int numbers){         return -1;  }
void mbtk_esim_set_info_callback(EsimMessageCallback callback){         return -1;  }
void mbtk_esim_set_error_callback(EsimMessageCallback callback){         return -1;  }
#endif


#ifndef MBTK_POC_SUPPORT_TL
int jemcu_check_binding_status(char* SN){ return -1; }
int jemcu_do_accout_polling(char* SN){ return -1; }
char* jemcu_get_tl_account(void){ return 0; }
char* jemcu_get_ind_url(void){ return 0; }
char OS_Wrap_get_clc_set(){	return 0;}

#endif

#ifndef MBTK_CODEC_TYPE_CJC8910
void codec_cjc_mic_speaker_switch(UINT32 sth){}
void mbtk_cjc8910_set_liv(uint8 *volume){}
void CJC8910_MIC_GAIN(int gain){}
void mbtk_cjc8910_set_ldv(uint8 volume){}
void mbtk_cjc8910_set_l_adc_volume(uint8 volume){}
void mbtk_cjc8910_set_l_r32_value(uint8 value){}
#endif


#ifdef REMOVE_FOTA
void init_fota()
{}

#endif

#ifndef MBTK_AIDIALOG_SUPPORT
int mbtk_aidialog_device_cfg_init(void *device_cfg){ return -1; }
int mbtk_aidialog_record_cfg_init(void *record_cfg){ return -1; }
int mbtk_aidialog_tts_cfg_init(void *tts_cfg){ return -1; }
int mbtk_aidialog_voice_clone_cfg_init(void *voice_clone_cfg){ return -1; }
int mbtk_aidialog_mode_cfg_init(void *mode_cfg){ return -1; }
int mbtk_aidialog_event_cfg_init(void *event_cfg){ return -1; }
int mbtk_aidialog_audio_play_cfg_init(void *audio_play_cfg){ return -1; }
int mbtk_aidialog_image_capture_cfg_init(void *image_capture_cfg){ return -1; }
int mbtk_aidialog_user_custom_prompt_init(char *user_custom_prompt){ return -1; }
int mbtk_aidialog_init(void){ return -1; }
int mbtk_aidialog_start(void){ return -1; }
int mbtk_aidialog_stop(void){ return -1; }
int mbtk_aidialog_trigger(unsigned int action){ return -1; }
void mbtk_aidialog_voice_select(void){}
void mbtk_aidialog_voice_select_by_name(const char *speaker_name){}
void mbtk_aidialog_voice_select_by_id(const char *speaker_id){}
void mbtk_aidialog_voice_delete(const char *speaker_id, unsigned int speaker_type){}
unsigned int mbtk_aidialog_status_get(void){ return -1; }
unsigned int mbtk_aidialog_process_running_count_get(void){ return -1; }
void mbtk_aidialog_tone_download_tone_speaker(const char *speaker_name){}
int mbtk_aidialog_tone_set_text(void *tone_update, int num){ return -1; }
void mbtk_aidialog_role_set(const char *role_name, const char *role_id, const char *speaker_id, unsigned int speaker_type, unsigned int tts_type){}
unsigned int mbtk_aidialog_trigger_mode_get(void){ return -1; }
void mbtk_aidialog_trigger_mode_set(unsigned int trigger_mode){}
int mbtk_aidialog_send_user_data(const char *data, int len){ return -1; }
void mbtk_aidialog_log_level_set(unsigned int level){}
void mbtk_aidialog_print_level_set(unsigned int level){}
void mbtk_aidialog_play_user_tts(const char *tts_text){}
void mbtk_aidialog_download_user_tts(const char *tts_text, const char *tts_file_path){}
void mbtk_aidialog_voice_interrupt_enable_set(bool enable){}
void mbtk_aidialog_break_mode_set(unsigned int break_mode){}
const char *mbtk_aidialog_version_get(void){ return NULL; }
void mbtk_aidialog_tone_play(int tone_type){}
int mbtk_aidialog_get_speaker_list(void *speaker_list, int start, int end){ return -1; }
void mbtk_aidialog_set_voice_select_tips(const char *tips){}
char *mbtk_aidialog_get_voice_select_tips(void){ return NULL; }
void mbtk_aidialog_config_tone_playing(unsigned char enable){}
int mbtk_aidialog_vad_cfg_init(void *vad_cfg){return -1;}
#endif

