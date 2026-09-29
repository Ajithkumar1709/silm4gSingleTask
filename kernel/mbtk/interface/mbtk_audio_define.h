#ifndef _MBTK_AUDIO_DEFINE_H_
#define _MBTK_AUDIO_DEFINE_H_

#define MBTK_AUDIO_FORMAT_AMR   3
#define MBTK_AUDIO_FORMAT_PCM8  7
#define MBTK_AUDIO_FORMAT_PCM16 8

#define MBTK_OEM_SAMPLE_RATE_8K 8000
#define MBTK_OEM_SAMPLE_RATE_16K 16000
#define MBTK_OEM_CHANNEL1 	1
#define MBTK_OEM_CHANNEL2	2

typedef enum
{
	MBTK_AUDIO_ITF_RECEIVER,
	MBTK_AUDIO_ITF_LOUDSPEAKER,	
}MBTK_AUDIO_ITF;

typedef enum
{
    MBTK_MCI_EVENT_INFO,
    MBTK_MCI_EVENT_ERROR,
    MBTK_MCI_EVENT_EOS,
} MBTK_MCI_EVNET;

typedef enum
{
	MBTK_MCI_INFO_NONE,
	MBTK_MCI_INFO_ERROR,
	MBTK_MCI_INFO_RECORDER_CUR_DURATION_MS,
	MBTK_MCI_INFO_RECORDER_CUR_SIZE
} MBTK_MCI_INFO;

typedef enum
{
    MBTK_AUDIO_SPK_MUTE = 0,
    MBTK_AUDIO_SPK_LEVEL_0 = MBTK_AUDIO_SPK_MUTE,
    MBTK_AUDIO_SPK_LEVEL_1,
    MBTK_AUDIO_SPK_LEVEL_2,
    MBTK_AUDIO_SPK_LEVEL_3,
    MBTK_AUDIO_SPK_LEVEL_4,
    MBTK_AUDIO_SPK_LEVEL_5,
    MBTK_AUDIO_SPK_LEVEL_6,
    MBTK_AUDIO_SPK_LEVEL_7,
    MBTK_AUDIO_SPK_LEVEL_8,
    MBTK_AUDIO_SPK_LEVEL_9,
    MBTK_AUDIO_SPK_LEVEL_10,
    MBTK_AUDIO_SPK_LEVEL_MAX = MBTK_AUDIO_SPK_LEVEL_10
    
} MBTK_VOLUME_LEVEL;

typedef void(* MBTK_AUDIO_PA_HOOK)(int enable);
typedef void(* MBTK_AUDIO_PLAYER_CALLBACK)(void *param);
typedef void (*MBTK_AUDIO_RECORD_CALLBACK)(MBTK_MCI_EVNET event , MBTK_MCI_INFO info_type, int value);
typedef void(*mbtk_mp3_play_cb)(int); 
typedef int (*audio_process_cb)(char *in_buf, int in_lens, char *out_buf, int *out_lens, int samperate, int channel, int bits);
typedef void(*mbtk_amr_play_cb)(int); 

/***********************************
*open define
************************************/


#endif
