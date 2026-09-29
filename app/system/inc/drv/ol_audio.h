#ifndef _OL_AUDIO_H_
#define _OL_AUDIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mbtk_pub_type.h"

#define OL_AUDIO_FORMAT_AMR   3
#define OL_AUDIO_FORMAT_PCM8  7
#define OL_AUDIO_FORMAT_PCM16 8

#define OL_AUDIO_SAMPLE_RATE_8K 8000
#define OL_AUDIO_SAMPLE_RATE_16K 16000
#define OL_AUDIO_CHANNEL1 	1
#define OL_AUDIO_CHANNEL2	2

typedef enum
{
	OL_AUDIO_ITF_RECEIVER,
	OL_AUDIO_ITF_LOUDSPEAKER,	
}ol_AUDIO_ITF;

typedef enum
{
    OL_MCI_EVENT_INFO,
    OL_MCI_EVENT_ERROR,
    OL_MCI_EVENT_EOS,
} ol_MCI_EVNET;

typedef enum
{
	OL_MCI_INFO_NONE,
	OL_MCI_INFO_ERROR,
	OL_MCI_INFO_RECORDER_CUR_DURATION_MS,
	OL_MCI_INFO_RECORDER_CUR_SIZE
} ol_MCI_INFO;

typedef enum
{
    OL_TTS_NONE,
    OL_TTS_TYPE_UTF16LE,    /* UTF-16 little-endian */
    OL_TTS_TYPE_GBK,        /* GBK */
    OL_TTS_TYPE_GB2312,     /* GB2312 */
    OL_TTS_TYPE_UTF8,       /* UTF-8 */
    OL_TTS_TYPE_UTF16BE,    /* UTF-16 big-endian */
}ol_TTS_TYPE;

typedef enum
{
    OL_AUDIO_SPK_MUTE = 0,
    OL_AUDIO_SPK_LEVEL_0 = OL_AUDIO_SPK_MUTE,
    OL_AUDIO_SPK_LEVEL_1,
    OL_AUDIO_SPK_LEVEL_2,
    OL_AUDIO_SPK_LEVEL_3,
    OL_AUDIO_SPK_LEVEL_4,
    OL_AUDIO_SPK_LEVEL_5,
    OL_AUDIO_SPK_LEVEL_6,
    OL_AUDIO_SPK_LEVEL_7,
    OL_AUDIO_SPK_LEVEL_8,
    OL_AUDIO_SPK_LEVEL_9,
    OL_AUDIO_SPK_LEVEL_10,
    OL_AUDIO_SPK_LEVEL_MAX = OL_AUDIO_SPK_LEVEL_10
    
} ol_VOLUME_LEVEL;



typedef enum {
	TTS_NONE,
	TTS_TYPE_UTF16LE,	/*play ucs2 pcm */ 
	TTS_TYPE_GBK,		/*play gbk*/
    TTS_TYPE_GB2312,     /* GB2312 */
    TTS_TYPE_UTF8,       /* UTF-8 */
    TTS_TYPE_UTF16BE,    /* UTF-16 big-endian */
}mbtk_tts_type;

typedef enum
{
    TTS_ROLE_AUTO,                  /* role automatically */
    TTS_ROLE_FEMALE,                /* say words by female voice */
    TTS_ROLE_MALE,                  /* say words by male voice */
} OL_TTS_ROLE;

typedef enum
{
    TTS_VEMODE_NONE,                    /* NONE */
    TTS_VEMODE_WANDER,                  /* WANDER */
    TTS_VEMODE_ECHO,                    /* ECHO */
    TTS_VEMODE_ROBERT,                  /* ROBERT */
    TTS_VEMODE_CHROUS,                  /* CHORUS */
    TTS_VEMODE_UNDERWATER,              /* UNDERWATER */
    TTS_VEMODE_REVERB,                  /* REVERB */
    TTS_VEMODE_ECCENTRIC,               /* ECCENTRIC */
} OL_TTS_VEMODE;


typedef enum Mp3PlayEventType {
		/** mp3 playback status, value with type <tt>Mp3PlayEventValue</tt>*/
		MP3_PLAYBACK_EVENT_STATUS,
		/** id3 header size, value with type <tt>int<tt> */
		MP3_FILE_EVENT_ID3OFFSET,
		/** sample rate, value with type <tt>int<tt>*/
		MP3_FILE_EVENT_SAMPLERATE,
		/** channel, value with type <tt>int<tt>*/
		MP3_FILE_EVENT_CHANNEL,
		/** bit rat, value with type <tt>int<tt>*/
		MP3_FILE_EVENT_BITRATE,
	}Mp3PlayEventType;


typedef enum Mp3PlayEventValue {
	/** play out all for file or stream*/
  MP3_PLAYBACK_STATUS_ENDED = 0,
  /** indicate current playback is started*/
  MP3_PLAYBACK_STATUS_STARTED,
  /** indicate output device is opened*/
  MP3_PLAYBACK_STATUS_OPENED,
  /** reach file end*/
  MP3_PLAYBACK_STATUS_FILE_READED,

  MP3_PLAYBACK_STATUS_STREAM = 100,
  /** indicate mp3 data producer should slow down to avoid overrun*/
  MP3_STREAM_STATUS_NEARLY_OVERRUN,
  MP3_STREAM_STATUS_SLOW_DOWN = MP3_STREAM_STATUS_NEARLY_OVERRUN,
  /** indicate mp3 data producer should fast up to avoid underrun*/
  MP3_STREAM_STATUS_NEARLY_UNDERRUN,
  MP3_STREAM_STATUS_FAST_UP = MP3_STREAM_STATUS_NEARLY_UNDERRUN,
  MP3_STREAM_STATUS_END_BUT_NOT_STOP
}Mp3PlayEventValue;

typedef enum AmrPlaybackEventValue {
	/** play out all for file or stream*/
	AMR_PLAYBACK_STATUS_ENDED = 0,
	/** indicate current playback is started*/
	AMR_PLAYBACK_STATUS_STARTED,

	AMR_PLAYBACK_STATUS_STREAM = 100,
	/** indicate amr data producer should slow down to avoid overrun*/
	AMR_STREAM_STATUS_NEARLY_OVERRUN,
	AMR_STREAM_STATUS_SLOW_DOWN = AMR_STREAM_STATUS_NEARLY_OVERRUN,
	/** indicate amr data producer should fast up to avoid underrun*/
	AMR_STREAM_STATUS_NEARLY_UNDERRUN,
	AMR_STREAM_STATUS_FAST_UP = AMR_STREAM_STATUS_NEARLY_UNDERRUN,
}AmrPlaybackEventValue;


typedef enum {
    AUDIO_PORT_SSP0 = 1,
    AUDIO_PORT_SSP1,
    AUDIO_PORT_SSP2,
}AUDIO_PORT_T;

enum
{
	MBTK_AUDIO_PLAY_ST_END,
	MBTK_AUDIO_PLAY_ST_START,
	MBTK_AUDIO_PLAY_ST_PAUSE,
	MBTK_AUDIO_PLAY_ST_RESUME,
	MBTK_AUDIP_PLAY_ST_FILE_ERROR,
	MBTK_AUDIO_PLAY_ST_ERROR = 4, 

	MBTK_AUDIO_PLAY_ST_SLOW_DOWN = 101,
	MBTK_AUDIO_PLAY_ST_FAST_UP
};



#define AMR_DEC_STOP_MANUAL         (0x01)
#define AMR_DEC_STOP_AUTO           (0x02)


typedef void(* OL_AUDIO_PA_HOOK)(int enable);
typedef void(* OL_AUDIO_PLAYER_CALLBACK)(void *param);
typedef void (*OL_AUDIO_RECORD_CALLBACK)(ol_MCI_EVNET event , ol_MCI_INFO info_type, INT32 value);
typedef void (*OL_AUDIO_CONTINUE_RECORD_CALLBACK)(const char*, int);
typedef void(*Mp3PlaybackEventCallback)(Mp3PlayEventType, int);
typedef int (*audio_process_cb)(char *in_buf, int in_lens, char *out_buf, int *out_lens, int samperate, int channel, int bits);
typedef void (*play_ev_cb)(int status);
typedef void (*player_process_cb)(int process);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_enable
 * DESCRIPTION 
 *  		This API is to enable the audio hardware.  
 * PARAMETERS 
 *			itf			[IN]:voice output path,support spaker and receiver
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern INT8 ol_audio_enable(ol_AUDIO_ITF itf);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_disable
 * DESCRIPTION 
 *  		This API is to enable the audio hardware.  
 * PARAMETERS 
 *		VOID
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_disable(void);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_set_audio_spi_port
 * DESCRIPTION 
 *  		This API is to set audio spi port when extern codec to output pcm  
 * PARAMETERS 
 *		port[in]         AUDIO_PORT_T enum
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern uint16 ol_set_audio_spi_port(uint16 port);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_audio_spi_port
 * DESCRIPTION 
 *  		This API is to get audio spi port when extern codec to output pcm  
 * PARAMETERS 
 *		VOID
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_get_audio_spi_port(void);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_register_pa_hook
 * DESCRIPTION 
 *  		This API is to register a pa enable/disable hook for auido underlying api.  
 * PARAMETERS 
 *			hook	[IN]:the pa hook
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_register_pa_hook(OL_AUDIO_PA_HOOK hook);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_itfswitch
 * DESCRIPTION 
 *  		This API is to switch the voice output path.  
 * PARAMETERS 
 *			itf			[IN]:voice output path,support spaker and receiver
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_itfswitch(ol_AUDIO_ITF itf);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_set_samplerate
 * DESCRIPTION 
 *  		This API is to set PCM data samplerate .  
 * PARAMETERS 
 *			samplerate		[IN]:PCM data samplerate
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
 extern void ol_audio_set_samplerate(UINT32 samplerate);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_set_channels
 * DESCRIPTION 
 *  		This API is to set PCM data channels .  
 * PARAMETERS 
 *			samplerate		[IN]:PCM data channels
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_set_channels(UINT32 channels);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_play_onetime
 * DESCRIPTION 
 *  		This API is to play a audio data for once.  
 * PARAMETERS 
 *		buffer				[IN]:The pointer to auido data
 *		len					[IN]:length of the audio data
 *		volume				[IN]:volume level
 *		func					[IN]:The callback function when audio play finish
 *		param				[IN]:param with callback function
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_play_onetime(UINT8 *buffer, UINT32 len,ol_VOLUME_LEVEL volume,OL_AUDIO_PLAYER_CALLBACK func,void *param);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_play_repeat
 * DESCRIPTION 
 *  		This API is to play a audio data repeated.  
 * PARAMETERS 
 *		buffer				[IN]:The pointer to auido data
 *		len					[IN]:length of the audio data
 *		volume				[IN]:volume level
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_play_repeat(UINT8 *buffer, UINT32 len, ol_VOLUME_LEVEL volume);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_play_end
 * DESCRIPTION 
 *  		This API is to finish the audio play.  
 * PARAMETERS 
 *		VOID
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_play_end(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_play_file_start
 * DESCRIPTION 
 *  		This API is to start play a audio file.  
 * PARAMETERS 
 *		path					[IN]:The file path
 *		volume				[IN]:volume level
 *		func					[IN]:The callback function when audio play end
 *		param				[IN]:param with callback function
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_play_file_start(const char *path, ol_VOLUME_LEVEL volume, OL_AUDIO_PLAYER_CALLBACK func, void *para);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_play_file_end
 * DESCRIPTION 
 *  		This API is to finish playing the audio file.  
 * PARAMETERS 
 *		VOID
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_play_file_end(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_play_pause
 * DESCRIPTION 
 *  		This API is to pause play the audio data.  
 * PARAMETERS 
 *		VOID
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_play_pause(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_play_resume
 * DESCRIPTION 
 *  		This API is to resume play the audio data.  
 * PARAMETERS 
 *		VOID
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_play_resume(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_record_buffer_start
 * DESCRIPTION 
 *  		This API is to start record sound data to buffer.  
 * PARAMETERS 
 *		buffer					[IN]:The data buffer
 *		bufsize					[IN]:the length of buffer
 *		maxDurationMs	[IN]:the record time
 *		func						[IN]:record callback when record finish
 *		format					[IN]:record data format
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_record_buffer_start(UINT8 *buffer, UINT32 bufsize, UINT32 maxDurationMs, OL_AUDIO_RECORD_CALLBACK func,UINT8 format);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_record_buffer_stop
 * DESCRIPTION 
 *  		This API is to stop recording sound.  
 * PARAMETERS 
 *		recSize				[OUT]:record data size
 *		durationMs		[OUT]:record time
 * RETURN VALUES
 *		=0 	: record success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern UINT32 ol_audio_record_buffer_stop(UINT32 *recSize, UINT32 *durationMs);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_record_file_start
 * DESCRIPTION 
 *  		This API is  to start record sound data to file.  
 * PARAMETERS 
 *		path					[IN]:file path
 *		func					[IN]:record callback when record finish
 *		format				[IN]:record data format
 * RETURN VALUES
 *		VOID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_record_file_start(const char *path, OL_AUDIO_RECORD_CALLBACK func,UINT8 format);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_record_file_stop
 * DESCRIPTION 
 *  		This API is to stop recording sound.  
 * PARAMETERS 
 *		pFile_size		[OUT]:record file size
 * RETURN VALUES
 *		=0 	: record success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern UINT32 ol_audio_record_file_stop(UINT32 *pFile_size);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_continue_record_start
 * DESCRIPTION 
 *  		This API is to start recording sound.  
 * PARAMETERS 
 *		func		[OUT]:record callback function
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern void ol_audio_continue_record_start(OL_AUDIO_CONTINUE_RECORD_CALLBACK func);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_continue_record_stop
 * DESCRIPTION 
 *  		This API is to stop recording sound.  
 * PARAMETERS 
 *		NONE
 * RETURN VALUES
 *		=0 	: stop success
 *		>0   : error
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern UINT32 ol_audio_continue_record_stop(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_set_volume
 * DESCRIPTION 
 *  		This API is to set volume level.  
 * PARAMETERS 
 *		pFile_size		[OUT]:record file size
 * RETURN VALUES
 * void
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_set_volume(UINT16 level);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_get_volume
 * DESCRIPTION 
 *  		This API is to get volume level.  
 * PARAMETERS 
 *		void
 * RETURN VALUES
 *		
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern UINT32 ol_audio_get_volume(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_tone_play
 * DESCRIPTION 
 *  		This API is to play tone last via LastTime.  
 * PARAMETERS 
 *		Type		[IN]: tone type
 *		Gain		[IN]: voice gain
 *		LastTime	[IN]: play last time
 * RETURN VALUES
 *		
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_audio_tone_play(UINT8 Type,UINT8 Gain,UINT32 LastTime);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mp3_file_play
 * DESCRIPTION 
 *  		This API is to start play mp3 file.  
 * PARAMETERS 
 *		file_name    mp3 file name
 * RETURN VALUES
 *		=0 	: play success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_mp3_file_play(const char *file_name, void(*mbtk_mp3_play_cb)(int), audio_process_cb process_cb);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mp3_file_stop
 * DESCRIPTION 
 *  		This API is to stop play mp3 file.  
 * PARAMETERS 
 *		drain[IN] Set whether to release the frame cache that has not been played yet,0:immediate release,1:waiting for the playback to complete
 * RETURN VALUES
 *		=0 	: stop success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_mp3_file_stop(char drain);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mp3_buffer_start
 * DESCRIPTION 
 *  		This API is to start play mp3 buffer.  
 * PARAMETERS 
 *		data[IN]     mp3 buffer 
 *		length[IN]     mp3 buffer size
 *		mbtk_mp3_play_cb[IN]  mp3 buffer play callback
 *		process_cb[IN] mp3 buffer process callback
 * RETURN VALUES
 *		=0 	: stop success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_mp3_buffer_start(const char *data,int length,void(*mbtk_mp3_play_cb)(int), audio_process_cb process_cb);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mp3_buffer_start_ex
 * DESCRIPTION 
 *  		This API is to set mp3 player callback.  
 * PARAMETERS 
 *		mbtk_mp3_play_cb[IN]  mp3 buffer play callback
 *		process_cb[IN] mp3 buffer process callback
 * RETURN VALUES
 *		=0 	: stop success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_mp3_buffer_start_ex(void(*mbtk_mp3_play_cb)(int), audio_process_cb process_cb);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mp3_buffer_play
 * DESCRIPTION 
 *  		This API is to set mp3 play buffer.  
 * PARAMETERS 
 *		buffer[IN]     mp3 buffer 
 *		size[IN]     mp3 buffer size
 * RETURN VALUES
 *		=0 	: stop success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_mp3_buffer_play(void *buffer, UINT32 size);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mp3_buffer_stop
 * DESCRIPTION 
 *  		This API is to stop the  mp3 buffer player.  
 * PARAMETERS 
 *		drain[IN] Set whether to release the frame cache that has not been played yet,0:immediate release,1:waiting for the playback to complete
 * RETURN VALUES
 *		=0 	: stop success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_mp3_buffer_stop(char drain);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mp3_play_pause
 * DESCRIPTION 
 *  		This API is to pause the  mp3 player.  
 * PARAMETERS 
 *		type[IN]: undefined,need set to 0
 * RETURN VALUES
 *		=0 	: stop success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_mp3_play_pause(UINT8 type);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mp3_play_resume
 * DESCRIPTION 
 *  		This API is to resume the  mp3 player.  
 * PARAMETERS 
 *		type[IN]: undefined,need set to 0
 * RETURN VALUES
 *		=0 	: stop success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_mp3_play_resume(UINT8 type);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_amr_buffer_play_start
 * DESCRIPTION 
 *  		This API is to play amr buffer.  
 * PARAMETERS 
 *      data[IN]             The pointer to amr data
 *		length[IN]			 length of the amr data
 *		cb[IN]               set callback when amr buffer play
 * RETURN VALUES
 *		=0 	: play success
 *		<0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_amr_buffer_play_start(const char *data,int length, void(*mbtk_mp3_play_cb)(int));


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_amr_buffer_play_start_ex
 * DESCRIPTION 
 *  		This API is to start  amr play ,use withol_amr_buffer_play
 * PARAMETERS 
 *		cb[IN]               set callback when amr buffer play
 *		close_flag[IN]			 length of the amr data    AMR_DEC_STOP_MANUAL or AMR_DEC_STOP_AUTO
 * RETURN VALUES
 *		=0 	: play success
 *		<0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_amr_buffer_play_start_ex(void(*mbtk_mp3_play_cb)(int), int close_flag);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_amr_buffer_play
 * DESCRIPTION 
 *  		This API is to set data to ol_amr play
 * PARAMETERS 
 *      data[IN]             The pointer to amr data
 *		length[IN]			 length of the amr data
 * RETURN VALUES
 *		=0 	: play success
 *		<0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
int ol_amr_buffer_play(const char *data,int length);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_amr_file_play_start
 * DESCRIPTION 
 *  		This API is to play amr file.  
 * PARAMETERS 
 *      file_name[IN]        The pointer to amr file name
 *		cb[IN]               set callback when amr buffer play
 * RETURN VALUES
 *		=0 	: play success
 *		<0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_amr_file_play_start(char *file_name, void(*mbtk_mp3_play_cb)(int));
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_amr_play_stop
 * DESCRIPTION 
 *  		This API is to stop amr play.
 * PARAMETERS 
 *		NONE
 * RETURN VALUES
 *		=0 	 : stop success
 *		=-1  : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_amr_play_stop(void);



/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audioplay_play_buffer_once
 * DESCRIPTION 
 *  		This API is to set play mp3、amr、midi audio.  
 * PARAMETERS 
 *		buffer[IN]               set audio buffer ,must have audio head, for example ,mp3 head, or amr head
	    len[IN]                 len of buffer
	    play_cb[IN]               set audio callbacke
	    volume[IN]               volume of auido
 * RETURN VALUES
 *		=0 	: stop success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *	
	void audio_Callback(int status)
	{
		uart_printf("[mbtk_kernel]audio_Callback:%d\n",  status);
	}
	uint8_t power_on_video[] = {
		0x23, 0x21, 0x41, 0x4d, 0x52, 0x0a, 0x14, 0x47, 0x8d, 0x79, 0xff, 0xff, 0xe7, 0xe7, 0xef, 0x9f,
		0xfc, 0xc0, 0x40, 0x04, 0x0c, 0xcc, 0x14, 0x1f, 0xd4, 0xf9, 0xff, 0xff, 0xe7, 0xf5, 0xf9, 0x9d,
		0xf5, 0xdf, 0xeb, 0x5d, 0x47, 0x6c, 0x14, 0x1d, 0x8d, 0x79, 0xff, 0xff, 0xe7, 0xe7, 0xf9, 0x9f,
		0xfc, 0xe6, 0x26, 0xe0, 0xce, 0x24, 0x14, 0xff, 0xd4, 0xf9, 0xff, 0xff, 0xe7, 0xf3, 0xf9, 0x9f,
		0xf6, 0xcb, 0xcb, 0x7b, 0x9f, 0xb0, 0x14, 0x19, 0xa6, 0x79, 0xff, 0xff, 0xe7, 0xeb, 0xe3, 0xdf,
		0xfa, 0xef, 0xb9, 0xfa, 0x3f, 0x2c, 0x14, 0x01, 0xcc, 0xba, 0x07, 0xe6, 0xe4, 0x13, 0x09, 0x15,
		0x2d, 0xfe, 0x79, 0xf3, 0xe4, 0xa0, 0x14, 0x01, 0x87, 0x30, 0x28, 0xb1, 0xdc, 0x6c, 0x54, 0x3a,
		0x35, 0xa0, 0xb2, 0xc0, 0x29, 0x3c, 0x14, 0x01, 0x14, 0xe0, 0x7d, 0xe7, 0x43, 0xae, 0xa8, 0x3b,
		0x55, 0x7e, 0xd5, 0x73, 0xc9, 0x30, 0x14, 0x01, 0x29, 0x60, 0x7d, 0xe3, 0x46, 0xfb, 0xb1, 0xde,
		0xd8, 0x50, 0x77, 0x21, 0xd6, 0xfc, 0x14, 0x01, 0x07, 0x48, 0x4f, 0xd0, 0x5b, 0xbf, 0xd1, 0xc5,
		0x33, 0x9a, 0x1d, 0x06, 0x46, 0xe8, 0x14, 0x01, 0x0f, 0xe0, 0x7f, 0xe0, 0xb3, 0x7d, 0xe6, 0x7c,
		0xfc, 0x10, 0xc8, 0xe0, 0x30, 0x10, 0x14, 0x01, 0x53, 0xea, 0xff, 0xdb, 0x8d, 0xe6, 0x76, 0x59,
		0xfb, 0xca, 0xc5, 0x67, 0x85, 0x44, 0x14, 0xbc, 0x52, 0x94, 0x36, 0x1a, 0x59, 0xa1, 0x19, 0xbf,
		0x25, 0x81, 0xb3, 0xf1, 0x93, 0x2c, 0x14, 0xe1, 0x52, 0xe0, 0x7f, 0xeb, 0x87, 0x4b, 0x78, 0x08,
		0xd2, 0x9f, 0x47, 0x5e, 0x51, 0x3c, 0x14, 0x90, 0x52, 0xc0, 0x76, 0xc1, 0x2a, 0xf5, 0xa8, 0x22,
		0x3c, 0xf2, 0x8f, 0xf2, 0xdf, 0x34, 0x14, 0xf4, 0xbb, 0x60, 0x6f, 0xe5, 0xaf, 0xad, 0x89, 0xfe,
		0x76, 0x1d, 0xe3, 0x6a, 0x2c, 0xec, 0x14, 0xaa, 0xbb, 0x00, 0x67, 0x81, 0x6d, 0xac, 0x86, 0x76,
		0xf3, 0xe2, 0x0d, 0xc3, 0xec, 0x40, 0x14, 0xdf, 0x4b, 0xb0, 0x67, 0xf7, 0xe2, 0xf2, 0xd1, 0xca,
		0x3b, 0xa2, 0xcb, 0x9a, 0x27, 0xec, 0x14, 0xa5, 0x5a, 0x3d, 0xff, 0xbf, 0xa3, 0xfb, 0xef, 0x96,
		0xfa, 0xd8, 0x0a, 0x40, 0xd6, 0xd4, 0x14, 0x01, 0xc2, 0x59, 0x7f, 0xdf, 0xe5, 0xf5, 0x85, 0x9f,
		0xc7, 0xfd, 0xf9, 0xee, 0x7c, 0x58, 0x14, 0xbb, 0xe3, 0xa0, 0x69, 0xa1, 0xb0, 0x26, 0x0a, 0xb8,
		0xe1, 0x22, 0x23, 0x62, 0x40, 0x54, 0x14, 0xbb, 0xb2, 0x60, 0x78, 0x67, 0xe5, 0xf7, 0xf1, 0xc5,
		0xfd, 0x24, 0x91, 0x92, 0xfc, 0xfc, 0x14, 0xbb, 0xb2, 0x60, 0x7d, 0xe2, 0x01, 0xff, 0xf1, 0xd5,
		0xd8, 0xc6, 0xa2, 0x89, 0x42, 0xac, 0x14, 0xe3, 0xb2, 0x60, 0x7f, 0xc6, 0x0b, 0x6e, 0x71, 0xcf,
		0xb7, 0xc0, 0x54, 0x6b, 0x05, 0x4c, 0x14, 0xe3, 0xd0, 0xe0, 0x6f, 0x81, 0x19, 0x7f, 0x26, 0x7f,
		0xdf, 0x44, 0xd3, 0x1b, 0x74, 0x4c, 0x14, 0x6d, 0xbf, 0x48, 0xcf, 0xd7, 0x67, 0xf8, 0xc6, 0x77,
		0xf9, 0xbe, 0x06, 0x49, 0xde, 0x20, 0x14, 0x6d, 0x66, 0xb8, 0x5f, 0xce, 0xfa, 0xfb, 0xea, 0xb7,
		0x2e, 0xe6, 0x02, 0x62, 0x84, 0x84, 0x14, 0x65, 0xb4, 0x48, 0x3f, 0x9f, 0xe5, 0xfc, 0xf6, 0xad,
		0x3d, 0xce, 0xb7, 0x1e, 0x6a, 0x9c, 0x14, 0x1f, 0x1f, 0xf9, 0xff, 0xff, 0xe7, 0xfd, 0xf9, 0x9d,
		0xf1, 0xdd, 0x6b, 0x5e, 0xfc, 0xa8, 0x14, 0x1d, 0xd4, 0xf9, 0xff, 0xfd, 0xe7, 0xff, 0x79, 0x9f,
		0xf4, 0xf3, 0x53, 0xf6, 0xfd, 0x14, 0x14, 0xff, 0x8d, 0x79, 0xff, 0xfd, 0xe7, 0xf5, 0xf9, 0x9f,
		0xf4, 0xf1, 0x91, 0x38, 0x90, 0x80, 0x14, 0x1d, 0xd4, 0xf9, 0xff, 0xff, 0xe7, 0xf7, 0xf9, 0x9f,
		0xf4, 0xf4, 0xd9, 0x6c, 0xc2, 0x78, 0x14, 0xff, 0x8d, 0x79, 0xff, 0xff, 0xe7, 0xe3, 0xf9, 0x9e,
		0xfe, 0xdf, 0xaf, 0x79, 0x3b, 0xb8, 0x14, 0x1d, 0xd4, 0xf9, 0xff, 0xff, 0xe7, 0xfd, 0xf9, 0x8f,
		0xf1, 0xdd, 0x5a, 0xd6, 0x20, 0x5c, 0x14, 0xff, 0x8d, 0x79, 0xff, 0xfd, 0x67, 0xf1, 0x59, 0x9f,
		0x77, 0xd7, 0xfd, 0xff, 0x0c, 0xfc, 0x14, 0x1d, 0xd4, 0xf9, 0xff, 0xff, 0xe7, 0xeb, 0xf9, 0x9f,
		0xfa, 0xfe, 0xf1, 0xad, 0xa2, 0x28, 0x14, 0xff, 0x8d, 0x79, 0xff, 0xff, 0xe7, 0xe3, 0xf9, 0x9f,
		0xf6, 0xfb, 0xbe, 0xbb, 0x7a, 0x98, 0x14, 0x1d, 0xd4, 0xf9, 0xff, 0xff, 0xe7, 0xfd, 0xf9, 0x9f,
		0xf1, 0xc9, 0x5f, 0xc6, 0x25, 0x1c, 0x14, 0xff, 0x8d, 0x79, 0xff, 0xff, 0xe7, 0xf1, 0xf9, 0x9f,
		0xf7, 0xd3, 0xb9, 0xbb, 0x19, 0xa8, 0x14, 0x1d, 0xd4, 0xf9, 0xff, 0xff, 0xe7, 0xfd, 0xf9, 0x9f,
		0xf1, 0xf5, 0xd1, 0xec, 0xe8, 0x58, 0x14, 0xff, 0x8d, 0x79, 0xff, 0xff, 0xe7, 0xe3, 0xf9, 0x9e,
		0xde, 0xfb, 0xc7, 0xbb, 0xb7, 0x98, 0x14, 0x1d, 0xd4, 0xf9, 0xff, 0xff, 0xe7, 0xff, 0xf9, 0x9f,
		0xf0, 0xc8, 0x0f, 0xc2, 0x64, 0x1c, 0x14, 0xff, 0x8d, 0x79, 0xff, 0xff, 0xe7, 0xf9, 0xf9, 0x9f,
		0xf3, 0xd7, 0xec, 0xbf, 0x4c, 0xfc, 0x14, 0x1d, 0xd4, 0xf9, 0xff, 0xff, 0xe7, 0xef, 0xf9, 0x9f,
		0xf8, 0xf6, 0x71, 0xa5, 0xaa, 0x20, 0x14, 0xff, 0x8d, 0x79, 0xff, 0xff, 0xe7, 0xf5, 0xf9, 0x8f,
		0xf4, 0xf5, 0xf2, 0x5d, 0xd0, 0xf4, 0x14, 0x1d, 0xd4, 0xf9, 0xff, 0xff, 0xe7, 0xf7, 0xf9, 0x9f,
		0xf4, 0xc8, 0x4e, 0xc2, 0x64, 0x0c, 0x14, 0xff, 0x8d, 0x79, 0xff, 0xff, 0xe7, 0xe1, 0xf9, 0x9f,
		0xff, 0xd7, 0xec, 0xff, 0x19, 0xf8, 0x14, 0x1d, 0xd4, 0xf9, 0xff, 0xff, 0xe7, 0xfd, 0xf9, 0x9f,
		0xf1, 0xdc, 0x5b, 0x87, 0x20, 0x08, 0x14, 0xff, 0x8d, 0x79, 0xff, 0xff, 0xe7, 0xf1, 0xf9, 0x8f,
		0xf7, 0xd7, 0xf8, 0xff, 0x58, 0xfc, 0x14, 0x1d, 0xd4, 0xf9, 0xff, 0xff, 0xe7, 0xfd, 0xf9, 0x9f,
		0xf1, 0xdc, 0x5b, 0x87, 0x20, 0x08,
	};

	ol_audioplay_play_buffer_once(audio_msg_map, sizeof(audio_msg_map), audio_Callback, 3);
 *****************************************************************************/
extern int ol_audioplay_play_buffer_once(void *buffer, uint32 len, OL_AUDIO_PLAYER_CALLBACK play_cb, ol_VOLUME_LEVEL volume);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audioplay_file_play
 * DESCRIPTION 
 *  		This API is to play audio file , like mp3�?amr 、mid
 * PARAMETERS 
 *		path[IN]               file path
	    play_cb[IN]               set audio callbacke
 * RETURN VALUES
 *		=0 	: stop success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *	
	void audio_Callback(int status)
	{
		uart_printf("[mbtk_kernel]audio_Callback:%d\n",  status);
	}

	ol_audioplay_file_play("C:/aaa.mp3", audio_Callback, audio_process_callback, 3);
 *****************************************************************************/
extern int  ol_audioplay_file_play(const char *path,play_ev_cb	 play_cb, player_process_cb process_cb, ol_VOLUME_LEVEL volume);
extern void ol_audioplay_pause(void);
extern void ol_audioplay_resume(void);
extern void ol_audioplay_stop(void);
extern void ol_audioplay_buffer_stop(void);


/*****************************************************************************
* FUNCTION
*	ol_tts_spk
* DESCRIPTION
*	This API is to play tts
*
* PARAMETERS
*	portNumber		: [IN]	txt    text will be tts
*   txt_len		    : [IN]	portNumber length
*   data_type	    : [IN]  text type   mbtk_tts_type
*   from		    : [IN]  0 or 1  0 can interupt 1 when 1 is playing

* RETURN VALUES
*
*  example:
*     unsigned short strText_GBK[100] = {"2019-05-24  , this is a test  package,电话号码1234567890"};
	  mbtk_tts_spk(strText_GBK, strlen(strText_GBK),TTS_TYPE_GBK,0);
	  
     unsigned short pTextBuf_U16[6]={0}�?*    pTextBuf_U16[0] = 0x4e00; //一
	 pTextBuf_U16[1] = 0x4e8c;//�?	 pTextBuf_U16[2] = 0x4e09;//�?	 pTextBuf_U16[3] = 0x0000;
*    mbtk_tts_spk(pTextBuf_U16, 3,TTS_TYPE_UTF16LE,0);
*****************************************************************************/

extern int ol_tts_spk(char *txt, UINT16 txt_len, int data_type, UINT8 from);
extern int ol_tts_spk_ex(char *txt, UINT16 txt_len, int data_type, UINT8 from);

extern int ol_tts_stop(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_tts_set_cb
 * DESCRIPTION 
 *  		This API is to set tts play status cb
 * PARAMETERS 
 *		cb    		: [IN]  callback  function
 * RETURN VALUES
 *		=0 	: success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_tts_set_cb(OL_AUDIO_PLAYER_CALLBACK cb);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_tts_set_speed
 * DESCRIPTION 
 *  		This API is to set tts play speed
 * PARAMETERS 
 *		speed    		: [IN]  50--200    50 is fastest, 200 is lowest
 * RETURN VALUES
 *		=0 	: success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_tts_set_speed(int speed);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_tts_get_speed
 * DESCRIPTION 
 *  		This API is to get tts play speed
 * PARAMETERS 
 *		
 * RETURN VALUES
 *		speed    		: [OUT]  50--200    50 is fastest, 200 is lowest
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_tts_get_speed(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_pcm_start
 * DESCRIPTION 
 *  		This API is to start pcm play
 * PARAMETERS 
 *		cb    		: [IN]  callback of pcm play status
 * RETURN VALUES
 *		
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
void ol_audio_pcm_start(OL_AUDIO_PLAYER_CALLBACK cb);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_tts_get_speed
 * DESCRIPTION 
 *  		This API is to fill pcm data, use together with ol_audio_pcm_start,
            when finish play, should set size 0, like ol_audio_pcm_fill(p, 0);
 * PARAMETERS 
 *		
 * RETURN VALUES
 *		data    		: [IN]  pcm data
        size            : [IN]  pcm data size
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
int  ol_audio_pcm_fill(uint8 *data, uint32 size);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_tts_play_status
 * DESCRIPTION 
 *  		This API is to get tts play status
 * PARAMETERS 
 *		
 * RETURN VALUES
 *		status     		: 0   STOP
                          1   PLAYING
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
int mbtk_tts_get_play_status(void);




/*****************************************************************************
 *
 * FUNCTIO
 *      ol_tts_set_volume
 * DESCRIPTION 
 *      This API is to set tts play volume
 * PARAMETERS 
 *      volume       : [IN]  -32768 -> 32767
 * RETURN VALUES
 *      =0      : success
 *      >0      : error
 * RETURN MESSAGE
 *      NONE
 *
 *****************************************************************************/
extern int ol_tts_set_volume(int volume);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_audio_status
 * DESCRIPTION 
 *  		This API is to get audio play status
            Only can get ol_audio_play_xxx like pcm and wav status
            MP3 play status should use callback interface to acqure by user
 * PARAMETERS 
 *		void
 * RETURN VALUES
 *		=1 	: in use
 *		0   : idle
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern UINT8 ol_audio_status(void);

extern UINT32 ol_audio_get_volume_ex(char channel);
extern void ol_audio_set_volume_ex(char channel,char level);
extern UINT8 ol_tts_status(void);

/*****************************************************************************
 *
 * FUNCTIO
 *      ol_tts_set_role
 * DESCRIPTION
 *      This API is to set a male or female voice
 * PARAMETERS
 *      role:OL_TTS_ROLE
 * RETURN VALUES
 *      !0      : error
 *      0       : sucess
 * RETURN MESSAGE
 *      NONE
 *
 *****************************************************************************/
extern int ol_tts_set_role(OL_TTS_ROLE role);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_tts_set_vemode
 * DESCRIPTION 
 *  		This API is to set tts vemode
 * PARAMETERS 
 *		vemode    		: [IN]  vemode
 * RETURN VALUES
 *		=0 	: success
 *		>0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_tts_set_vemode(OL_TTS_VEMODE vemode);

/*****************************************************************************
 *
 * FUNCTIO
 *      ol_tts_set_pitch
 * DESCRIPTION
 *      This API is to set voice tone
 * PARAMETERS
 *      pitch       : [IN]  -32768 -> 32767
 * RETURN VALUES
 *      !0      : error
 *      0       : sucess
 * RETURN MESSAGE
 *      NONE
 *
 *****************************************************************************/
extern int ol_tts_set_pitch(int pitch);


/*****************************************************************************
 *
 * FUNCTIO
 *      ol_tts_get_pitch
 * DESCRIPTION
 *      This API is to get voice tone
 * PARAMETERS
 *      
 * RETURN VALUES
 *      pitch       : [OUT]  -32768 -> 32767
 * RETURN MESSAGE
 *      NONE
 *
 *****************************************************************************/
extern int ol_tts_get_pitch(void);



/*****************************************************************************
 *
 * FUNCTIO
 *      ol_tts_set_digit
 * DESCRIPTION
 *      This API is to set how to read digit, e.g. read as number, read as value
 * PARAMETERS
 *      pitch       : [IN]  0 -> 1
 * RETURN VALUES
 *      !0      : error
 *      0       : sucess
 * RETURN MESSAGE
 *      NONE
 *
 *****************************************************************************/
extern int ol_tts_set_digit(int pitch);

/*****************************************************************************
 *
 * FUNCTIO
 *		ol_set_tone_vol
 * DESCRIPTION
 *		This API is to set tone value
 * PARAMETERS
 *		level		: [IN]	ol_VOLUME_LEVEL
 * RETURN VALUES

 * RETURN MESSAGE
 *		NONE
 *
 *****************************************************************************/
void ol_set_tone_vol(int level);
	
	/*****************************************************************************
 *
 * FUNCTIO
 *      ol_get_tone_vol
 * DESCRIPTION
 *      This API is to get tone value
 * PARAMETERS
 *     
 * RETURN VALUES
 *      ol_VOLUME_LEVEL
 * RETURN MESSAGE
 *      NONE
 *
 *****************************************************************************/
	
	int ol_get_tone_vol(void);
	
	/*****************************************************************************
 *
 * FUNCTIO
 *      ol_set_mic_vol
 * DESCRIPTION
 *      This API is to set mic vol
 * PARAMETERS
 *      level       : [IN]  ol_VOLUME_LEVEL
 * RETURN VALUES
 * RETURN MESSAGE
 *      NONE
 *
 *****************************************************************************/
	void ol_set_mic_vol(int level);
	
	/*****************************************************************************
 *
 * FUNCTIO
 *      8910  mic gain
 *      NONE
 *
 *****************************************************************************/
void mbtk_cjc8910_set_liv(uint8 *volume);
void mbtk_cjc8910_set_l_adc_volume(uint8 volume);
void mbtk_cjc8910_set_l_r32_value(uint8 value);

/*****************************************************************************
 *
 * FUNCTIO
 *      8910  dac gain
 *      NONE
 *
 *****************************************************************************/
void mbtk_cjc8910_set_ldv(uint8 volume);


#ifdef __cplusplus
}
#endif

#endif
