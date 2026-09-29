#ifndef _MBTK_TTS_H_
#define _MBTK_TTS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <assert.h>

#include <time.h>


#define MBTK_TTS_VOLUME_MIN         -32768
#define MBTK_TTS_VOLUME_NORMAL      0
#define MBTK_TTS_VOLUME_MAX         +32767

#define MBTK_OEM_SAMPLE_RATE_16K 16000
#define MBTK_PCM_8K_SIZE                320
#define MBTK_PCM_16K_SIZE               1280
#define MBTK_TTS_DATA_BUF_SIZE          10*MBTK_PCM_16K_SIZE
#define MBTK_OEM_CHANNEL1 	1



typedef void(*m_tts_status_cb)(int type);

/*****************************************************************************
* DESCRIPTION
*    This API is to play tts
*
* PARAMETERS
*    from  : [IN]     0 tts    1 menu tts
*
* RETURN VALUES
*
* example:
*    unsigned short strText_GBK[100] = {"2019-05-24, this is a test package,电话号码1234567890"};
*    mbtk_tts_spk(strText_GBK, strlen(strText_GBK),TTS_TYPE_GBK);
*
*    unsigned short pTextBuf_U16[6]={0}；
*    pTextBuf_U16[0] = 0x4e00; //一
*    pTextBuf_U16[1] = 0x4e8c; //二
*    pTextBuf_U16[2] = 0x4e09; //三
*    pTextBuf_U16[3] = 0x0000;
*    mbtk_tts_spk(pTextBuf_U16, 3,TTS_TYPE_UTF16LE);
*****************************************************************************/
int mbtk_tts_spk(char *txt, uint16 txt_len, int data_type, uint8 from);

int mbtk_tts_init(void);
int mbtk_tts_stop(void);

int mbtk_tts_set_cb(m_tts_status_cb cb);
int mbtk_tts_set_volume(int volume);
int mbtk_tts_set_speed(int speed);
int mbtk_tts_set_role(int type);
int mbtk_tts_set_vemode(int vemode);
int mbtk_tts_set_pitch(int pitch);

uint8_t mbtk_get_tts_status(void);
int mbtk_tts_get_volume(void);
int mbtk_tts_get_speed(void);
int mbtk_tts_get_role_type(void);
int mbtk_tts_get_vemode(void);
int mbtk_tts_get_pitch(void);

#ifdef __cplusplus
}
#endif

#endif /*MBTK_TTS_SUPPORT*/