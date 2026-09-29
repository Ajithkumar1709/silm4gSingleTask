#ifndef _MBTK_AUDIO_API_H_
#define _MBTK_AUDIO_API_H_

#include "mbtk_pub_type.h"
#include "mbtk_audio_define.h"


#ifdef MBTK_AUDIO_PWM
#define MBTK_ADUIO_USE_PCM 0
#else
#define MBTK_ADUIO_USE_PCM 1
#endif


typedef UINT8 BOOL;
typedef void(*MP3_EVENT_CB)(int);

typedef void (*MBTK_AUDIO_CONTINUE_RECORD_CALLBACK)(const char*, int);

INT8 MBTK_Audio_Enable(MBTK_AUDIO_ITF itf);
void MBTK_Audio_Disable(void);

int  mbtk_set_audio_spi_port(uint16 port);
uint16 mbtk_get_audio_spi_port(void);

void MBTK_Audio_Register_PA_Hook(MBTK_AUDIO_PA_HOOK hook);
void MBTK_Audio_ItfSwitch(MBTK_AUDIO_ITF itf);

/***********************************
*buffer play
************************************/
void MBTK_Audio_Play_Onetime(UINT8 *buffer, UINT32 len,MBTK_VOLUME_LEVEL volume,MBTK_AUDIO_PLAYER_CALLBACK func,void *param);
void MBTK_Audio_Play_Repeat(UINT8 *buffer, UINT32 len, MBTK_VOLUME_LEVEL volume);
void MBTK_Audio_Play_End(void);

/***********************************
*file play
************************************/
int MBTK_Audio_Play_File_Start(const char *path, MBTK_VOLUME_LEVEL volume, MBTK_AUDIO_PLAYER_CALLBACK func, void *para);
void MBTK_Audio_Play_File_End(void);

/***********************************
*buffer record
************************************/
void MBTK_Audio_Record_Buffer_Start(UINT8 *buffer, UINT32 bufsize, UINT32 maxDurationMs, MBTK_AUDIO_RECORD_CALLBACK func,UINT8 format);
UINT32 MBTK_Audio_Record_Buffer_Stop(UINT32 *recSize, UINT32 *durationMs);

/***********************************
*file record
************************************/
void MBTK_Audio_Record_File_Start(const char *path, MBTK_AUDIO_RECORD_CALLBACK func,UINT8 format);
UINT32 MBTK_Audio_Record_File_Stop(UINT32 *pFile_size);



void MBTK_Audio_SetSamplerate(UINT32  samplerate);
void MBTK_Audio_SetChannels(UINT32  channels);
void MBTK_Audio_Play_Pause(void);
void MBTK_Audio_Play_Resume(void);
void mbtk_set_volume(int level);
UINT32 mbtk_get_volume(void);
unsigned int mbtk_get_volume_ex(char channel);
void mbtk_set_volume_ex(char channel,char level);
void MBTK_Audio_Tone_Play(UINT8 Type,UINT8 Gain,UINT32 LastTime);

int mbtk_mp3_file_play_start(char *file_name,mbtk_mp3_play_cb *cb,audio_process_cb process_cb);
int mbtk_mp3_file_play_stop(void);

int mbtk_mp3_buffer_start(const char *data,int length, mbtk_mp3_play_cb *cb, audio_process_cb process_cb);
int mbtk_mp3_buffer_play(void *buffer, int size);
int mbtk_mp3_buffer_play_stop(void);
int mbtk_mp3_file_play_stop(void);
int mbtk_mp3_play_pause(UINT8 type);
int mbtk_mp3_play_resume(UINT8 type);
int mbtk_mp3_buffer_start_ex(mbtk_mp3_play_cb *cb, audio_process_cb process_cb);

int mbtk_amr_buffer_play_start(const char *data,int length, mbtk_amr_play_cb *cb);
int mbtk_amr_buffer_play_start_ex(mbtk_amr_play_cb *cb, int close_flag);
int mbtk_amr_file_play_start(char *file_name, mbtk_amr_play_cb *cb);
int mbtk_amr_play_stop(void);
int mbtk_amr_buffer_play(const char *data,int length);


int mbtk_hal_tts_set_cb(MBTK_AUDIO_PLAYER_CALLBACK        cb);
int mbtk_hal_tts_set_speed(unsigned char speed);
int mbtk_hal_tts_get_speed(void);

int mbtk_hal_tts_spk(char *txt, UINT16 txt_len, int data_type, UINT8 from);
int mbtk_hal_tts_spk_ex(char *txt, UINT16 txt_len, int data_type, UINT8 from);
int mbtk_hal_tts_stop(void);
int mbtk_hal_tts_set_volume(int volume);
int mbtk_hal_tts_set_role(int role_type);
int mbtk_hal_tts_set_vemode(int vemode);
uint8_t mbtk_get_tts_status(void);
uint8_t mbtk_get_audio_status(void);
int mbtk_tts_support_flag(void);
int mbtk_hal_tts_set_digit(int digit);
int mbtk_hal_tts_set_pitch(int pitch);
int mbtk_hal_tts_get_pitch(void);

void MBTK_Audio_Continue_Record_Start(MBTK_AUDIO_CONTINUE_RECORD_CALLBACK func);
UINT32 MBTK_Audio_Continue_Record_Stop(void);

void MBTK_Audio_Play_Start(MBTK_AUDIO_PLAYER_CALLBACK cb);
int  MBTK_Audio_Fill(uint8 *data, uint32 size);

int mbtk_tts_get_play_status(void);

#endif
