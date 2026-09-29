#include "mbtk_comm_api.h"
#include "mbtk_gpio.h"
#include "ol_audio.h"
#include "ol_aidialog.h"
#include "menu_demo_api.h"

int aidialog_demo_init(void);
int aidialog_demo_start(void);
int aidialog_demo_stop(void);


static demo_menu_info menu_info[] =
{
	{"aidialog init","",aidialog_demo_init,NULL},
	{"aidialog start","",aidialog_demo_start,NULL},
	{"aidialog stop","",aidialog_demo_stop,NULL},
};

demo_menu_info *aidialog_demo_menu_info(unsigned int *num)
{
	*num = sizeof(menu_info)/sizeof(menu_info[0]);
	return menu_info;
}


//#define STB_DIALOG_RECORD_FMT_OPUS 1
//#define STB_DIALOG_TTS_FMT_OPUS 1
//#define STB_DIALOG_USE_STB_VAD
#define STB_DIALOG_PLAY_FILE_MODE 1
#define STB_DIALOG_USE_CUSTOM_VAD
#define AIDIALOG_DEMO_TASK_STACK_SIZE		(10*1024) 
#define AIDIALOG_DEMO_TASK_PRIORITY			(224)

typedef struct 
{
	unsigned int cmd_type;
}aidialog_demo_msg_struct;

typedef struct 
{
	unsigned char *record_data;
	unsigned int record_data_len;
}aidialog_demo_record_data_struct;

static unsigned int g_vad_value = 0;
static int g_stb_dialog_vad_prefetch_status = 0;
static aidialog_demo_record_data_struct g_record_dara_t = {0};

#define AIDIALOG_DEMO_TASK_STACK_SIZE		(10*1024) 
#define AIDIALOG_DEMO_TASK_PRIORITY			(224)
#define AIDIALOG_DEMO_MAX_RECORD_DATA_LEN	(5120)

static mbtk_taskref aidialog_main_task = NULL;
static mbtk_semref aidialog_record_data_sem = NULL;
static mbtk_msgqref aidialog_main_msgq = NULL;


void aidialog_demo_tts_play_callback(void *param)
{ 
  op_uart_printf("aidialog_demo_tts_play_callback\n"); 
}


int aidialog_demo_play_file_process_cb(char *in_buf, int in_lens, char *out_buf, int *out_lens, int samperate, int channel, int bits)
{
  op_uart_printf("[aidialog_demo_play_file_process_cb]\n");
  return 0;
}

void aidialog_demo_play_file_callback(int status)
{
	op_uart_printf("[aidialog_demo_play_file_callback]:%d\n", status);
}

void aidialog_demo_continue_record_callback(const char*data, int data_len)
{
	unsigned int input_data_len = 0;
	if(g_record_dara_t.record_data == NULL)
	{
		op_uart_printf("record_data buffer is NULL\n");
	}

	ol_os_sem_request(aidialog_record_data_sem,MBTK_OS_SUSPEND);

	input_data_len = data_len;
	if(g_record_dara_t.record_data_len+data_len >= AIDIALOG_DEMO_MAX_RECORD_DATA_LEN*2)
	{
		input_data_len = AIDIALOG_DEMO_MAX_RECORD_DATA_LEN*2 - g_record_dara_t.record_data_len;
	}

	op_uart_printf("record_data buffer fill data len %d,offset %d\n",input_data_len,g_record_dara_t.record_data_len);
	if(input_data_len > 0)
	{
		memcpy(g_record_dara_t.record_data+g_record_dara_t.record_data_len,data,input_data_len);
		g_record_dara_t.record_data_len+=input_data_len;
	}

	ol_os_sem_release(aidialog_record_data_sem);
}

//record api
int aidialog_record_open(int volume, int vad_start_threshold, int vad_stop_threshold, int vad_silence_start_threshold)
{
  op_uart_printf("aidialog record_open\n");
	memset(&g_record_dara_t,0x0,sizeof(aidialog_demo_record_data_struct));
	g_record_dara_t.record_data = (unsigned char *)ol_malloc(AIDIALOG_DEMO_MAX_RECORD_DATA_LEN*2);
	ol_audio_continue_record_start(aidialog_demo_continue_record_callback);
  return 0;
}

int aidialog_record_start(void)
{
	op_uart_printf("aidialog record_start\n");
	return 0;
}

int aidialog_record_stop(void)
{
	op_uart_printf("aidialog record_stop\n");
  ol_audio_continue_record_stop();
	return 0;
}

int aidialog_record_data(void *data, unsigned int len)
{
  unsigned int read_len = len;

	if(g_record_dara_t.record_data == NULL)
	{
		op_uart_printf("record_data buffer is NULL\n");
	}

	op_uart_printf("record read data len = %d\n",len);
	ol_os_sem_request(aidialog_record_data_sem,MBTK_OS_SUSPEND);

	if(len >= g_record_dara_t.record_data_len)
		read_len = g_record_dara_t.record_data_len;

	if(read_len > 0)
	{
		memcpy(data,g_record_dara_t.record_data,read_len);
		g_record_dara_t.record_data_len-=read_len;
	}

	ol_os_sem_release(aidialog_record_data_sem);
	op_uart_printf("record_data read_len = %d\n", read_len);

 	return read_len;
}

int aidialog_record_close()
{
  op_uart_printf("aidialog record_close\n");
	if(g_record_dara_t.record_data != NULL)
	{
		ol_free(g_record_dara_t.record_data);
	}
	memset(&g_record_dara_t,0x0,sizeof(aidialog_demo_record_data_struct));
  return 0;
}

//vad api
unsigned int vad_detect(void)
{
	op_uart_printf("aidialog vad_detect\n");
	return g_vad_value;
}

unsigned int vad_clear()
{
	op_uart_printf("aidialog vad_clear\n");
	g_vad_value = 0;
  return 0;
}

unsigned int vad_silence_detect(void)
{
	op_uart_printf("aidialog vad_silence_detect\n");
	return g_stb_dialog_vad_prefetch_status;
}

void vad_silence_clear(void)
{
	op_uart_printf("aidialog vad_silence_clear\n");
	g_stb_dialog_vad_prefetch_status = 0;
}

//tts play api
int aidialog_tts_play_start(void)
{
  op_uart_printf("aidialog_tts_play_start\n");
	ol_audio_set_samplerate(OL_AUDIO_SAMPLE_RATE_16K);
	ol_audio_set_channels(OL_AUDIO_CHANNEL1);
  ol_audio_pcm_start(aidialog_demo_tts_play_callback);
  return 0;
}

int aidialog_tts_play_stop(void)
{
  op_uart_printf("aidialog tts_play_stop\n");
  ol_audio_play_end();
  return 0;
} 

int aidialog_tts_play_abort(void)
{
  op_uart_printf("aidialog tts_play_abort\n");
  return 0;
}

int aidialog_tts_play_data(uint8_t *data, uint32_t len)
{
  op_uart_printf("aidialog tts_play_data: %d\n", len);
  ol_audio_pcm_fill(data,len);
  return len;
}

//如选择非文件模式，需要实现以下注册函数
// int aidialog_audio_play_open(stb_dialog_codec_fmt_type_e fmt)
// {
//     op_uart_printf("TODO:play open\n");
//     return -1;
// }
// int aidialog_audio_play_start(int play_id)
// {
//     op_uart_printf("TODO:play start\n");
//     return 0;
// }
// int aidialog_audio_play_stop(int play_id)
// {
//     op_uart_printf("TODO:play stop\n");
//     return 0;
// }
// int aidialog_audio_play_data(int play_id, uint8_t *data, uint32_t len)
// {
//     op_uart_printf("TODO:play data: %d\n", len);
//     return 0;    
// }
// int aidialog_audio_play_abort(int play_id)
// {
//     op_uart_printf("TODO:play abort\n");
//     return -1;
// }

int aidialog_audio_play_file(char *data) 
{
  int ret = 0;
  ret = ol_mp3_file_play(data, aidialog_demo_play_file_callback,
		aidialog_demo_play_file_process_cb);	
  if(ret != 0){
      op_uart_printf("mp3Start fail\n");
      return -1;
  }
  op_uart_printf("mp3Start ret = %d\n");
  return 0;
}

//voice clone api
int aidialog_voice_clone_record_open()
{
  op_uart_printf("voice_clone_record_open\n");
  return 0;
}

//event api
void aidialog_event_cb(stb_dialog_event_e event, uint8_t *data)
{
  static int idle_flag = 0;
  op_uart_printf("event: %d\n", event);
  static uint64_t start_time = 0;
  static char time_str[64] = {0};
  uint64_t use_time = 0;
  static char emotion[64] = {0};

	switch (event) {
	  case STB_DIALOG_EVENT_SERVICE_CONNECT_BEGIN:
	      op_uart_printf("STB Dialog Service connecting!\n");
	      break;

	  case STB_DIALOG_EVENT_SERVICE_CONNECT_SUCCESS:
	      op_uart_printf("STB Dialog Service connected !\n");
	      break;

	  case STB_DIALOG_EVENT_SERVICE_CONNECT_FAIL:
	      op_uart_printf("STB Dialog Service connect fail!\n");
	      break;
	  
	  case STB_DIALOG_EVENT_SERVICE_CONNECT_TIMEOUT:
	      op_uart_printf("STB Dialog Service connect timeout!\n");
	      break;

	  case STB_DIALOG_EVENT_SERVICE_DISCONNECTED:
	      op_uart_printf("STB Dialog Service disconnected !\n");
	      break;

	  case STB_DIALOG_EVENT_DIALOG_BEGIN:
	      op_uart_printf("STB Dialog Service begin!\n");
	      break;

	  case STB_DIALOG_EVENT_DIALOG_END:
	      op_uart_printf("STB Dialog Service end!\n");
	      break;

	  case STB_DIALOG_EVENT_IDLE:
	      op_uart_printf("STB Dialog Service idle!\n");    
	      break;

	  case STB_DIALOG_EVENT_RECORDING:
	      op_uart_printf("STB Dialog Service recording!\n");
	      break;

	  case STB_DIALOG_EVENT_PLAYING:
	      op_uart_printf("STB Dialog Service playing!\n");
	      break;

	  case STB_DIALOG_EVENT_RSP_WAITING:
	      op_uart_printf("STB Dialog Service rsp waiting!\n");
	      break;

	  case STB_DIALOG_EVENT_ANSWER_TIME:
	  		{
	      	unsigned int wait_time = *(unsigned int *)data;
	      	op_uart_printf("STB Dialog Service answer time %u!\n", wait_time);
	  		}
	      break;

	  case STB_DIALOG_EVENT_ASR_FAIL:
	      op_uart_printf("STB Dialog Service asr fail!\n");
	      break;

	  case STB_DIALOG_EVENT_VOICE_CLONE_BEGIN:
	      op_uart_printf("STB Dialog Service voice clone begin!\n");
	      break;

	  case STB_DIALOG_EVENT_VOICE_CLONE_SUCCESS:
	      op_uart_printf("STB Dialog Service voice clone success!\n");
	      break;

	  case STB_DIALOG_EVENT_VOICE_SELECT_BEGIN:
	      op_uart_printf("STB Dialog Service voice select begin!\n");
	      break;
	  
	  case STB_DIALOG_EVENT_VOICE_SELECT_NAME:
	      op_uart_printf("STB Dialog Service voice voice select name!\n");
	      break;

	  case STB_DIALOG_EVENT_VOICE_SELECT_TONE_DOWNLOAD:
	      op_uart_printf("STB Dialog Service voice clone tone download!\n");
	      break;

	  case STB_DIALOG_EVENT_VOICE_SELECT_END:
	      op_uart_printf("STB Dialog Service voice select end!\n");
	      use_time = ol_os_get_ticks() * 5 - start_time; //one tick 5ms
	      op_uart_printf("STB Dialog download tone use time %u!\n", use_time);
	      break;
	  
	  case STB_DIALOG_EVENT_RSP_TIMEOUT:
	      op_uart_printf("STB Dialog Service rsp timeout!\n");
	      break;

	  case STB_DIALOG_EVENT_VOICE_CLONE_RECORDING_BEGIN:
	      op_uart_printf("STB Dialog Service voice clone recording begin!\n");
	      break;

	  case STB_DIALOG_EVENT_VOICE_CLONE_REACH_LIMIT:
	      op_uart_printf("STB Dialog Service voice clone reach limit!\n");
	      break;

	  case STB_DIALOG_EVENT_VOICE_CLONE_FAIL:
	      op_uart_printf("STB Dialog Service voice clone fail!\n");
	      break;

	  case STB_DIALOG_EVENT_DIALOG_TEXT:
	      {
		      stb_dialog_text_result_t *dialog_text = (stb_dialog_text_result_t *)data;
		      char *dialog_type[2] = {"Request", "Response"};
		      char *process_mode[2] = {"intermediate", "final"};
		      op_uart_printf("STB Dialog Get %s %s Dialog Text: %s\n", 
		                  dialog_type[dialog_text->text_mode], 
		                  process_mode[dialog_text->process_mode],
		                  (char *)dialog_text->dialog_data);
	      }
	      break;

	  case STB_DIALOG_EVENT_NLP_INTENT:
	      {
		      stb_dialog_nlp_intent_t *nlp_intent = (stb_dialog_nlp_intent_t *)data;
		      if (nlp_intent->intent == NULL)
		      {
	          op_uart_printf("STB Dialog Get NLP Intent: NULL\n");
	          return;
		      }
		      op_uart_printf("STB Dialog Get NLP Intent: %s %s\n", nlp_intent->intent, nlp_intent->value);
	      }

	      break;

	  case STB_DIALOG_EVENT_NLP_EMOTION:
	      {
	      stb_dialog_nlp_emotion_t *nlp_emotion = (stb_dialog_nlp_emotion_t *)data;
	      if (nlp_emotion->type == NULL)
	      {
          op_uart_printf("STB Dialog Get NLP Emotion: NULL\n");
          return;
	      }
	      op_uart_printf("STB Dialog Get NLP Emotion: %s %s\n", nlp_emotion->type, nlp_emotion->value);
	      }
	      break;

	  default:
	      break;
	}
}

void aidialog_demo_cfg_init(void)
{
  stb_dialog_device_cfg_t device_cfg;
  stb_dialog_record_cfg_t record_cfg;
  stb_dialog_tts_cfg_t tts_cfg;
  stb_dialog_audio_play_cfg_t audio_play_cfg;
  stb_dialog_voice_clone_cfg_t voice_clone_cfg;
  stb_dialog_mode_cfg_t mode_cfg;
  stb_dialog_event_cfg_t event_cfg;
	stb_dialog_vad_cfg_t vad_cfg;
	char device_imei[16] = {"864788050910749"};

  op_uart_printf("ai dialog begin...\n");

  // device config
  memset(&device_cfg, 0, sizeof(stb_dialog_device_cfg_t));
  device_cfg.app_id = "prj2R1AJLAh9T";
  device_cfg.product_key = "tsvZwYyEawu";
  device_cfg.product_secret = "JaIecF7EbE9N85gN";
  device_cfg.device_name = device_imei;
  ol_aidialog_device_cfg_init(&device_cfg);

  // record config
  memset(&record_cfg, 0, sizeof(stb_dialog_record_cfg_t));
  record_cfg.channel = 1;
  record_cfg.sample_rate = 16000;
  record_cfg.record_buf_num = 2;
  record_cfg.record_timeout = 10000;
  record_cfg.record_net_buff_num = 64;
  record_cfg.record_gain = 80;
  record_cfg.record_data_max_len = AIDIALOG_DEMO_MAX_RECORD_DATA_LEN;
  
#ifdef STB_DIALOG_RECORD_FMT_OPUS
  record_cfg.fmt = STB_DIALOG_CODEC_FMT_OPUS;
  record_cfg.opus_param.in_size = 160;
  record_cfg.opus_param.out_size = record_cfg.sample_rate / 100 * 8;
#else
  record_cfg.fmt = STB_DIALOG_CODEC_FMT_PCM;
#endif
  record_cfg.cloud_asr_param.vad_segment_furation = 1000;
  record_cfg.cloud_asr_param.end_window_size = 800;
  record_cfg.cloud_asr_param.force_to_speech_time = 1000;

  record_cfg.record_open = aidialog_record_open;
  record_cfg.record_start = aidialog_record_start;
  record_cfg.record_stop = aidialog_record_stop;
  record_cfg.record_data = aidialog_record_data;
  record_cfg.record_close = aidialog_record_close;

  ol_aidialog_record_cfg_init(&record_cfg);

#ifdef STB_DIALOG_USE_CUSTOM_VAD
  vad_cfg.vad_type = STB_DIALOG_VAD_CUSTOM;
  vad_cfg.custom_vad_cfg.vad_detect = vad_detect;
  vad_cfg.custom_vad_cfg.vad_clear = vad_clear;
  vad_cfg.custom_vad_cfg.vad_silence_detect = vad_silence_detect;
  vad_cfg.custom_vad_cfg.vad_silence_clear = vad_silence_clear;
  vad_cfg.vad_start_threshold = 350;
  vad_cfg.vad_stop_threshold = 900;
  vad_cfg.vad_silence_start_threshold = 320;
#elif defined(STB_DIALOG_USE_STB_VAD)
  vad_cfg.vad_type = STB_DIALOG_VAD_STB;
  vad_cfg.vad_start_threshold = 240;
  vad_cfg.vad_stop_threshold = 900;
  vad_cfg.vad_silence_start_threshold = 320;
  vad_cfg.stb_vad_cfg.vad_energy_threshold = 10000;
  vad_cfg.stb_vad_cfg.min_tailing_silence = 480;
#endif

  ol_aidialog_vad_cfg_init(&vad_cfg);

  // tts config
  memset(&tts_cfg, 0, sizeof(stb_dialog_tts_cfg_t));
  tts_cfg.channel = 1;
#ifdef STB_DIALOG_TTS_FMT_OPUS
  tts_cfg.fmt = STB_DIALOG_CODEC_FMT_OPUS;
  tts_cfg.opus_param.encode_package_size = 640;
  tts_cfg.opus_param.encode_ratio = 4;
#else
  tts_cfg.fmt = STB_DIALOG_CODEC_FMT_PCM;
#endif
  tts_cfg.tts_play_start = aidialog_tts_play_start;
  tts_cfg.tts_play_stop = aidialog_tts_play_stop;
  tts_cfg.tts_play_abort = aidialog_tts_play_abort;
  tts_cfg.tts_play_data = aidialog_tts_play_data;
  tts_cfg.tts_speed = 1.0;
  tts_cfg.tts_data_interval = 125;
  tts_cfg.sample_rate = 16000;
  tts_cfg.tts_max_pcm_data_len = 5120;
  tts_cfg.tts_play_data_buff_num = 256;
  tts_cfg.tts_remaining_data_waterlevel_high = 800;
  tts_cfg.tts_remaining_data_waterlevel_low = 400;

  ol_aidialog_tts_cfg_init(&tts_cfg);

  // audio play config
  memset(&audio_play_cfg, 0, sizeof(stb_dialog_audio_play_cfg_t));
#ifdef STB_DIALOG_PLAY_FILE_MODE
  audio_play_cfg.audio_play_mode = STB_DIALOG_AUDIO_PLAY_MODE_FILE;
  audio_play_cfg.audio_play_file = aidialog_audio_play_file;
#else
  audio_play_cfg.audio_play_open = aidialog_audio_play_open;
  audio_play_cfg.audio_play_start = aidialog_audio_play_start;
  audio_play_cfg.audio_play_stop = aidialog_audio_play_stop;
  audio_play_cfg.audio_play_abort = aidialog_audio_play_abort;
  audio_play_cfg.audio_play_data = aidialog_audio_play_data;
#endif
  ol_aidialog_audio_play_cfg_init(&audio_play_cfg);

  // voice clone config
  memset(&voice_clone_cfg, 0, sizeof(stb_dialog_voice_clone_cfg_t));
  voice_clone_cfg.channel = 1;
  voice_clone_cfg.fmt = STB_DIALOG_CODEC_FMT_PCM;
  voice_clone_cfg.sample_rate = 16000;
  voice_clone_cfg.voice_clone_record_open = aidialog_voice_clone_record_open;
  voice_clone_cfg.voice_clone_record_start = aidialog_record_start;
  voice_clone_cfg.voice_clone_record_stop = aidialog_record_stop;
  voice_clone_cfg.voice_clone_record_data = aidialog_record_data;
  voice_clone_cfg.voice_clone_record_close = aidialog_record_close;
  ol_aidialog_voice_clone_cfg_init(&voice_clone_cfg);

  // mode config
  memset(&mode_cfg, 0, sizeof(stb_dialog_mode_cfg_t));
#if 1 //auto mode
	mode_cfg.trigger_mode = STB_DIALOG_TRIGGER_MODE_AUTO;
  mode_cfg.break_mode = STB_DIALOG_BREAK_MODE_VOICE;
#else //tgigger mode
  mode_cfg.trigger_mode = STB_DIALOG_TRIGGER_MODE_USER;
  mode_cfg.break_mode = STB_DIALOG_BREAK_MODE_BTN;
#endif
  mode_cfg.enable_play_record = 0;
  mode_cfg.enable_long_memory = false;
  mode_cfg.enable_intention = false;
  mode_cfg.enable_emotion = false;

  ol_aidialog_mode_cfg_init(&mode_cfg);

  // event config
  memset(&event_cfg, 0, sizeof(stb_dialog_event_cfg_t));
  event_cfg.event_cb = aidialog_event_cb;
  ol_aidialog_event_cfg_init(&event_cfg);

  ol_aidialog_init();

  op_uart_printf("aidialog init success!\n");
}

void aidialog_demo_main(void)
{
	mbtk_os_status os_status;
	unsigned int exe_ret = 0;
	aidialog_demo_msg_struct msg = {0};

	//audio config
	extern void pa_config(void);
	extern void pa_hook(int enable);
	pa_config();
	ol_audio_register_pa_hook(pa_hook);
	
  op_uart_printf("sdk version %s\n", ol_aidialog_version_get());
  aidialog_demo_cfg_init();
  ol_os_task_sleep(1000);
  ol_aidialog_start();
	
	while(1)
	{
		os_status = ol_os_msgq_recv(aidialog_main_msgq, &msg, sizeof(aidialog_demo_msg_struct), MBTK_OS_SUSPEND);
		if(os_status != mbtk_os_success)
		{
			op_uart_printf("aidialog_demo ol_os_msgq_recv fail, os_status = %d  \n", os_status);
		}
		else 
		{
			op_uart_printf("aidialog status : %d\n", ol_aidialog_status_get());
			switch(msg.cmd_type)
			{
				case STB_TRIGGER_ACTION_START:
				{
					exe_ret = ol_aidialog_trigger(STB_TRIGGER_ACTION_START);
					op_uart_printf("aidialog trigger start exe ret %d",exe_ret);
				}
				break;
				case STB_TRIGGER_ACTION_STOP:
				{
					exe_ret = ol_aidialog_trigger(STB_TRIGGER_ACTION_STOP);
					op_uart_printf("aidialog trigger stop exe ret %d",exe_ret);
				}
				break;

				default:
				op_uart_printf("no such cmd type supported %d\n", msg.cmd_type);
				break;
			}
		}
	}
}


int aidialog_demo_init_main(void)
{
	mbtk_os_status os_status;
	static unsigned char inited = 0;

#ifndef MBTK_RECORD_SUPPORT
	op_uart_printf("aidialog need reocrd support\n");
	return -1;
#endif

	if(inited)
		return 0;
	

	if(aidialog_main_msgq == NULL){
		os_status = ol_os_msgq_creat(&(aidialog_main_msgq), "aidialog_demo_msgq", sizeof(aidialog_demo_msg_struct), 10, MBTK_OS_FIFO);
		if (os_status != mbtk_os_success){
			op_uart_printf("aidialog_demo ol_os_msgq_creat fail , os_status = %d\n", os_status);
			return -1;
		}
	}

	if(aidialog_record_data_sem == NULL){
		os_status = ol_os_sem_creat(&(aidialog_record_data_sem), 1, MBTK_OS_FIFO);
		if (os_status != mbtk_os_success){
			op_uart_printf("aidialog_demo ol_os_sem_creat fail , os_status = %d\n", os_status);
			ol_os_msgq_delete(aidialog_main_msgq);
			aidialog_main_msgq = NULL;
			return -1;
		}
	}	

	if(aidialog_main_task == NULL){
		os_status = ol_os_task_creat(&(aidialog_main_task), NULL, AIDIALOG_DEMO_TASK_STACK_SIZE,
	  	AIDIALOG_DEMO_TASK_PRIORITY, "aidialog_demo_task", aidialog_demo_main,NULL);
	  if (os_status != mbtk_os_success){
	    op_uart_printf("aidialog_demo ol_os_task_creat sub task fail, os_status = %d \n", os_status);
			ol_os_sem_delete(aidialog_record_data_sem);
			aidialog_record_data_sem = NULL;
			ol_os_msgq_delete(aidialog_main_msgq);
			aidialog_main_msgq = NULL;
	    return -1;
	  }
	}
	inited = 1;

	return 0;
}

int aidialog_demo_exe_req(char cmd_type)
{	
	aidialog_demo_msg_struct msg = {0};

	if(aidialog_main_msgq == NULL)
	{
		op_uart_printf("audio demo aidialog_main_msgq is NULL\r\n");
		return -1;
	}
	
	msg.cmd_type = cmd_type;
  ol_os_msgq_send(aidialog_main_msgq, sizeof(aidialog_demo_msg_struct), &msg, MBTK_OS_SUSPEND);
	return 0;
}

int aidialog_demo_init(void)
{
	int ret = 0;
	
	ret = aidialog_demo_init_main();
	if(ret != 0){
		op_uart_printf("audio demo process main init fail\r\n");
		return -1;
	}

	return 0;
}

int aidialog_demo_start(void)
{
	return aidialog_demo_exe_req(STB_TRIGGER_ACTION_START);
}
int aidialog_demo_stop(void)
{
	return aidialog_demo_exe_req(STB_TRIGGER_ACTION_STOP);	
}

