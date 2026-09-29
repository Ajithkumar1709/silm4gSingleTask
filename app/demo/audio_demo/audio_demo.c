#include "mbtk_comm_api.h"
#include "mbtk_gpio.h"
#include "ol_audio.h"
#include "auido_demo_resources.h"
#include "menu_demo_api.h"


int auido_demo_record(void);
int auido_demo_wav_play(void);
int auido_demo_amr_play(void);
int auido_demo_mp3_play(void);
int auido_demo_play_pause(void);
int auido_demo_play_resume(void);
int auido_demo_play_volume_up(void);
int auido_demo_play_volume_down(void);

static demo_menu_info menu_info[] =
{

	{"audio record","[use file]",auido_demo_record,NULL},
	{"audio wav play","[use file]",auido_demo_wav_play,NULL},
	{"audio amr play","[use file]",auido_demo_amr_play,NULL},
	{"audio mp3 play","[use file]",auido_demo_mp3_play,NULL},
  {"audio pause","",auido_demo_play_pause,NULL},
  {"audio resume","",auido_demo_play_resume,NULL},
	{"audio volume+","",auido_demo_play_volume_up,NULL},
  {"audio volume-","",auido_demo_play_volume_down,NULL},
};

demo_menu_info *audio_demo_menu_info(unsigned int *num)
{
	*num = sizeof(menu_info)/sizeof(menu_info[0]);
	return menu_info;
}

#define DEMO_HAVE_PA (1)
#define DEMO_PA_PIN	mbtk_pin_80

#define DISK												"C:"
#define ROOT_PATH										""DISK"/"
#define AUDIO_RECORD_FILE_NAME			ROOT_PATH"audio_record"
#define AUDIO_WAV_FILE_NAME					ROOT_PATH"audio_wav.wav"
#define AUDIO_AMR_FILE_NAME					ROOT_PATH"audio_amr.amr"
#define AUDIO_MP3_FILE_NAME					ROOT_PATH"audio_mp3.mp3"

typedef enum
{
	AUDIO_DEMO_RECORD_CMD,
	AUDIO_DEMO_PLAY_WAV_CMD,
	AUDIO_DEMO_PLAY_AMR_CMD,
	AUDIO_DEMO_PLAY_MP3_CMD,
}AUDIO_DEMO_CMD_TYPE;

typedef struct 
{
	unsigned int cmd_type;
	unsigned char use_file;
	unsigned char *resource;
	unsigned int size;
}audio_demo_msg_struct;  

#define AUDIO_DEMO_TASK_STACK_SIZE		(10*1024) 
#define AUDIO_DEMO_TASK_PRIORITY			(224)

static mbtk_taskref play_main_task = NULL;
static mbtk_msgqref play_main_msgq = NULL;

void pa_config(void)
{
	#if DEMO_HAVE_PA
  mbtk_pin_config_struct config;
  config.gpio_af_num = mbtk_gpio_config_maf0;
  config.gpio_pull = mbtk_gpio_config_pull_low;
  config.gpio_sleep = mbtk_gpio_config_sleep_none;
  config.gpio_edge = mbtk_gpio_config_edge_none;
  
  op_uart_printf("auido_demo pa config run\n");
  if (ol_pin_config(DEMO_PA_PIN, &config) != 0)
  {
    op_uart_printf("auido_demo : mbtk_pin_config fail \n");
    return ;
  }
  
  if (ol_set_pin_dir(DEMO_PA_PIN, mbtk_gpio_dir_output) != 0)
  {
    op_uart_printf("auido_demo : mbtk_set_pin_dir_input fail \n");
    return ;
  }
  
   config.gpio_af_num = mbtk_gpio_config_maf1;
  if (ol_pin_config(mbtk_pin_20, &config) != 0)
  {
    op_uart_printf("auido_demo : mbtk_pin_config fail \n");
    return ;
  }
  
  if (ol_set_pin_dir(mbtk_pin_20, mbtk_gpio_dir_output) != 0)
  {
    op_uart_printf("auido_demo : mbtk_set_pin_dir_input fail \n");
    return ;
  }
  ol_set_pin_level(mbtk_pin_20, mbtk_gpio_level_high);
	#endif
}

void pa_hook(int enable)
{
	#if DEMO_HAVE_PA
	op_uart_printf("pa hook enable %d",enable);
	if(enable)
	{
		ol_set_pin_level(DEMO_PA_PIN, mbtk_gpio_level_high);
		ol_os_task_sleep(8);//add for pop clear up
	}
	else
	{
		ol_set_pin_level(DEMO_PA_PIN,mbtk_gpio_level_low);
		ol_os_task_sleep(8);//add for pop clear up
	}
	#endif
}

void auido_demo_main(void *param)
{
	mbtk_os_status os_status;
	audio_demo_msg_struct msg = {0};

	while(1)
	{
		os_status = ol_os_msgq_recv(play_main_msgq, &msg, sizeof(audio_demo_msg_struct), MBTK_OS_SUSPEND);
		if(os_status != mbtk_os_success)
		{
	 		op_uart_printf("demo1_task ol_os_msgq_recv fail, os_status = %d  \n", os_status);
	  }
	  else 
	  {
			switch(msg.cmd_type)
			{
#ifdef MBTK_RECORD_SUPPORT
				case AUDIO_DEMO_RECORD_CMD:
				{
					audio_demo_record_exe(msg.use_file);	
				}
				break;
#endif
				case AUDIO_DEMO_PLAY_WAV_CMD:
				{
					audio_demo_play_wav_exe(msg.use_file,msg.resource,msg.size);
				}
				break;
#ifdef MBTK_AMR_SUPPORT
				case AUDIO_DEMO_PLAY_AMR_CMD:
				{
					audio_demo_play_amr_exe(msg.use_file,msg.resource,msg.size);
				}
				break;
#endif
#ifdef MBTK_MP3_SUPPORT
				case AUDIO_DEMO_PLAY_MP3_CMD:
				{
					audio_demo_play_mp3_exe(msg.use_file,msg.resource,msg.size);
				}
				break;
#endif
				default:
				op_uart_printf("no such audio type supported %d  \n", msg.cmd_type);
				break;
			}
	  }
	}
}

int auido_demo_init(void)
{
	mbtk_os_status os_status;
	static unsigned char inited = 0;

	if(inited)
		return 0;
	
	pa_config();
	ol_audio_register_pa_hook(pa_hook);

  ol_audio_set_samplerate(OL_AUDIO_SAMPLE_RATE_16K);
  //enable audio
  while(0!= ol_audio_enable(OL_AUDIO_ITF_LOUDSPEAKER)){
    ol_os_task_sleep(200);//sleep for 1s
  }

	if(play_main_msgq == NULL){
		os_status = ol_os_msgq_creat(&(play_main_msgq), "audio_demo_msgq", sizeof(audio_demo_msg_struct), 10, MBTK_OS_FIFO);
		if (os_status != mbtk_os_success){
			op_uart_printf("audio_demo ol_os_msgq_creat fail , os_status = %d\n", os_status);
			return -1;
		}
	}

	if(play_main_task == NULL){
		os_status = ol_os_task_creat(&(play_main_task), NULL, AUDIO_DEMO_TASK_STACK_SIZE,
	  	AUDIO_DEMO_TASK_PRIORITY, "demo_sub_task", auido_demo_main,NULL);
	  if (os_status != mbtk_os_success){
	    op_uart_printf("os_demo ol_os_task_creat sub task fail, os_status = %d \n", os_status);
			ol_os_msgq_delete(play_main_msgq);
			play_main_msgq = NULL;
	    return -1;
	  }
	}
	inited = 1;

	return 0;
}

int auido_demo_exe_req(char play_type,char play_file,char *resource,int size)
{
	int ret = 0;
	audio_demo_msg_struct msg = {0};
	
	ret = auido_demo_init();
	if(ret != 0){
		op_uart_printf("audio demo process main init fail\r\n");
		return -1;
	}

	msg.cmd_type = play_type;
	msg.use_file = play_file;
	msg.resource = resource;
	msg.size = size;
	
  ol_os_msgq_send(play_main_msgq, sizeof(audio_demo_msg_struct), &msg, MBTK_OS_SUSPEND);
	return 0;
}

int auido_demo_wav_play(void)
{
	int audio_demo_use_file_api = 0;
	char* resource = NULL;
	unsigned int size = 0;
	
	DEMO_MEUN_GET_INT_PARAM(0,&audio_demo_use_file_api, 0,1,0);
	if(audio_demo_use_file_api)
	{
		resource = AUDIO_WAV_FILE_NAME;
		size = 0;
	}
	else
	{
		#if AUIDO_DEMO_RESOURCES_FORM_BUFFER
		resource = wav_buffer;
		size = sizeof(wav_buffer);
		#else
		op_uart_printf("auido_demo_wav_play only support use file!!!\n");
		return -1;
		#endif
	}
	
	return auido_demo_exe_req(AUDIO_DEMO_PLAY_WAV_CMD,audio_demo_use_file_api,
		resource,size);
}

int auido_demo_play_pause(void)
{
	ol_audio_play_pause();
	return 0;
}

int auido_demo_play_resume(void)
{
	ol_audio_play_resume();
	return 0;
}

int auido_demo_play_volume_up(void)
{
	unsigned int current_volume = 0;
	current_volume = ol_audio_get_volume();
	current_volume++;
	if(current_volume >= OL_AUDIO_SPK_LEVEL_MAX)
	{
		op_uart_printf("auido_demo volume up reach max!!!\n");
		return 0;
	}
	ol_audio_set_volume(current_volume);
	return 0;
}
int auido_demo_play_volume_down(void)
{
	unsigned int current_volume = 0;
	current_volume = ol_audio_get_volume();
	current_volume--;
	if(current_volume <= OL_AUDIO_SPK_MUTE)
	{
		op_uart_printf("auido_demo volume up reach min!!!\n");
		return 0;
	}
	ol_audio_set_volume(current_volume);
	return 0;
}

void audio_demo_play_onetime_callback(void *param)
{
  int data = (int)param;
  op_uart_printf("ol_audio_play_onetime end data len = %d!!!\n",data);

  ol_audio_disable();
  op_uart_printf("ol_audio_demo_end!!!\n");
}

#ifdef MBTK_RECORD_SUPPORT
char *record_buffer= NULL;
void audio_demo_file_record_callback(ol_MCI_EVNET event , ol_MCI_INFO info_type, INT32 value)
{
  op_uart_printf("audio_file_record_callback!!!\n");
  op_uart_printf("audio_file_record event = %d,info =%d,currentsize = %d\n",event,info_type,value);

  if(value > 20*1024)
  {
    int currentsize = 0;
    
    ol_audio_record_file_stop(&currentsize);
    op_uart_printf("audio_file_record_end size = %d!!!\n",currentsize);

		auido_demo_exe_req(AUDIO_DEMO_PLAY_WAV_CMD,1,AUDIO_RECORD_FILE_NAME,0);
  }
}

void audio_demo_record_callback(ol_MCI_EVNET event , ol_MCI_INFO info_type, INT32 value)
{
  int currentsize = value;
  
  op_uart_printf("audio_record_callback!!!\n");
  op_uart_printf("audio_record event = %d,info =%d,currentsize = %d\n",event,info_type,currentsize);
  
  if(event == OL_MCI_EVENT_EOS)
  {
    int recSize = 0;
    int durationMs = 0;
    ol_audio_record_buffer_stop(&recSize,&durationMs);
    op_uart_printf("audio_record_end size = %d,time = %d!!!\n",recSize,durationMs);

		auido_demo_exe_req(AUDIO_DEMO_PLAY_WAV_CMD,0,record_buffer,recSize);
  }
}

void audio_demo_record_exe(char is_record_file)
{
	op_uart_printf("audio_record_demo start,record to file %d!!!\n",is_record_file);
	if(is_record_file)
	{
		ol_audio_record_file_start(AUDIO_RECORD_FILE_NAME,audio_demo_file_record_callback,
			OL_AUDIO_FORMAT_PCM8);		
	}
	else
	{
		if(record_buffer == NULL){
			record_buffer = (char *)ol_malloc(160*1024);
			if(record_buffer == NULL){
				op_uart_printf("audio_record_demo can not malloc for record buffer!!!\n");
				return;
			}
		}
		memset(record_buffer,0x0,160*1024);
		ol_audio_record_buffer_start(record_buffer,160*1024,10*1000,
			audio_demo_record_callback,OL_AUDIO_FORMAT_PCM8);
	}
}

int auido_demo_record(void)
{
	int audio_demo_use_file_api = 0;
	
	DEMO_MEUN_GET_INT_PARAM(0,&audio_demo_use_file_api, 0,1,0);
	return auido_demo_exe_req(AUDIO_DEMO_RECORD_CMD,audio_demo_use_file_api,NULL,0);
}
#else
int auido_demo_record(void)
{
	op_uart_printf("this demo not support record \n");
	return -1;	
}

#endif

void audio_demo_play_wav_exe(char is_play_file,char* resource,unsigned int size)
{		
  op_uart_printf("audio_wav_play_demo start,play file %d!!!\n",is_play_file);

	if(is_play_file)
	{
		op_uart_printf("audio_amr_play_demo get resource name %s!!!\n",resource);
		ol_audio_play_file_start(resource, OL_AUDIO_SPK_LEVEL_8, 
			audio_demo_play_onetime_callback,(void*)size );
	}
	else
	{
		if(resource == NULL || size == 0)
		{
			op_uart_printf("audio_amr_play_demo set resource error!!!\n");
			return;
		}
  	ol_audio_play_onetime(resource,size,OL_AUDIO_SPK_LEVEL_8,
			audio_demo_play_onetime_callback,(void*)size);
	}
}

#ifdef MBTK_AMR_SUPPORT
void audio_demo_amr_callback(int status)
{
	op_uart_printf("[AMR_Callback]:%d\n", status);
}

void audio_demo_play_amr_exe(char is_play_file,char* resource,unsigned int size)
{
	op_uart_printf("audio_amr_play_demo start,play file %d!!!\n",is_play_file);
	if(is_play_file)
	{
		op_uart_printf("audio_amr_play_demo get resource name %s!!!\n",resource);
		ol_amr_file_play_start(AUDIO_AMR_FILE_NAME, audio_demo_amr_callback);	
	}
	else
	{
		if(resource == NULL || size == 0)
		{
			op_uart_printf("audio_amr_play_demo set resource error!!!\n");
			return;
		}
		ol_amr_buffer_play_start(resource,size, audio_demo_amr_callback);
	}	
	//ol_amr_play_stop();			
}

int auido_demo_amr_play(void)
{
	int audio_demo_use_file_api = 0;
	char* resource = NULL;
	unsigned int size = 0;
	
	DEMO_MEUN_GET_INT_PARAM(0,&audio_demo_use_file_api, 0,1,0);
	if(audio_demo_use_file_api)
	{
		resource = AUDIO_AMR_FILE_NAME;
		size = 0;
	}
	else
	{
		#if AUIDO_DEMO_RESOURCES_FORM_BUFFER
		resource = amr_buffer;
		size = sizeof(amr_buffer);
		#else
		op_uart_printf("auido_demo_amr_play only support use file!!!\n");
		return -1;
		#endif
	}
	return auido_demo_exe_req(AUDIO_DEMO_PLAY_AMR_CMD,audio_demo_use_file_api,
		resource,size);
}
#else
int auido_demo_amr_play(void)
{
	op_uart_printf("this demo not support amr play \n");
	return -1;
}
#endif

#ifdef MBTK_MP3_SUPPORT

int audio_demo_mp3_process_cb(char *in_buf, int in_lens, char *out_buf, int *out_lens, int samperate, int channel, int bits)
{
  op_uart_printf("[Mp3_Callback]:test_audio_process_cb  in_lens %d, sampe=%d,channel=%d, bits =%d \n", in_lens, samperate,channel,bits);
  return 0;
}

void audio_demo_mp3_callback(int status)
{
  op_uart_printf("[Mp3_Callback]:%d\n", status);
}

void audio_demo_mp3_callback_file(int status)
{
	op_uart_printf("[Mp3_Callback_file]:%d\n", status);
}

void audio_demo_play_mp3_exe(char is_play_file,char* resource,unsigned int size)
{
	op_uart_printf("audio_mp3_play_demo start,play file %d!!!\n",is_play_file);
	if(is_play_file)
	{
		op_uart_printf("audio_mp3_play_demo get resource name %s!!!\n",resource);
		ol_mp3_file_play(resource, audio_demo_mp3_callback_file,
			audio_demo_mp3_process_cb);	
	}
  else
  {
		if(resource == NULL || size == 0)
		{
			op_uart_printf("audio_mp3_play_demo set resource error!!!\n");
			return;
		}
		/*
		ol_mp3_buffer_start(resource,size, audio_demo_mp3_callback, 
			audio_demo_mp3_process_cb);
		*/
		ol_mp3_buffer_start_ex(audio_demo_mp3_callback,audio_demo_mp3_process_cb);
		ol_mp3_buffer_play(resource,size);
	}
}

int auido_demo_mp3_play(void)
{
	int audio_demo_use_file_api = 0;
	char* resource = NULL;
	unsigned int size = 0;
	
	DEMO_MEUN_GET_INT_PARAM(0,&audio_demo_use_file_api, 0,1,0);
	if(audio_demo_use_file_api)
	{
		resource = AUDIO_MP3_FILE_NAME;
		size = 0;
	}
	else
	{
		#if AUIDO_DEMO_RESOURCES_FORM_BUFFER
		resource = mp3_buffer;
		size = sizeof(mp3_buffer);
		#else
		op_uart_printf("auido_demo_mp3_play only support use file!!!\n");
		return -1;
		#endif	
	}
	return auido_demo_exe_req(AUDIO_DEMO_PLAY_MP3_CMD,audio_demo_use_file_api,
		resource,size);
}
#else
int auido_demo_mp3_play(void)
{
	op_uart_printf("this demo not support mp3 play \n");
	return -1;
}

#endif

void audio_Callback(int status)
{
    op_uart_printf("[mbtk_audio]audio_Callback:%d\n",  status);
}

void audio_process_callback(int process)
{
    op_uart_printf("[mbtk_audio] audio play process = [%d]", process);
}

void amr_audioplayer_demo(void)
{
    op_uart_printf("mbtk_audioplayer_demo [start]");
    pa_config();
    ol_audio_register_pa_hook(pa_hook);

    ol_audioplay_file_play("U:/test_audio/bbb.amr", audio_Callback, audio_process_callback, 8);
    op_uart_printf("mbtk_audioplayer_demo [end]");
}


void mp3_audioplayer_demo(void)
{
    op_uart_printf("mbtk_audioplayer_demo [start]");
    pa_config();
    ol_audio_register_pa_hook(pa_hook);
    ol_audioplay_file_play("U:/test_audio/test.mp3", audio_Callback, audio_process_callback, 8);
    op_uart_printf("mbtk_audioplayer_demo [end]");
}

void wav_audioplayer_demo(void)
{
    op_uart_printf("mbtk_audioplayer_demo [start]");
    pa_config();
    ol_audio_register_pa_hook(pa_hook);
    ol_audioplay_file_play("U:/test_audio/test.wav", audio_Callback, audio_process_callback, 8);
    op_uart_printf("mbtk_audioplayer_demo [end]");
}

void mbtk_audioplay_stop_test(void)
{
    ol_audioplay_stop();
}

void mbtk_audioplay_pause_test(void)
{
    ol_audioplay_pause();
}

void mbtk_audioplay_resume_test(void)
{
    ol_audioplay_resume();
}


void tts_play_cb(void *param)
{
    int type = (int)param;

    op_uart_printf("[mbtk_audio] tts_play_cb: %d\n", type);
}

void test_tts_demo(void)
{
    int res = 0;
    unsigned char strText[]= {"In retaliation for the Hamas militant attack on Saturday, Israeli airplanes bombarded Gaza City's downtown nonstop until early Tuesday, cutting off the Gaza Strip from food and other supplies. According to Reuters, the Israeli military activated an unprecedented 300,000 reserve soldiers and placed a blockade on the Gaza Strip, increasing concerns that it was preparing a ground invasion in response to the most daring and deadliest Hamas offensive in decades"};
    unsigned char strText_GBK[]={"10月10日下午，习近平总书记在江西省九江市考察了长江国家文化公园九江城区段，了解当地长江国家文化公园建设、长江岸线生态修复等情况。长江国家文化公园九江城区段于2022年4月启动建设，按照“共抓大保护、不搞大开发”要求，坚持“还江于民、便民利民，生态优先、文化铸魂”原则进行建设。建设过程以保护传承弘扬长江文化为核心，按照“堤内园林景观带，堤外生态绿化带”标准，改造提升琵琶亭、浔阳楼、锁江楼及周边景点，打造水清岸绿、河畅景美、人水和谐的自然生态空间。群众可通过绿道亲水观江，真正做到还江于民."};
    unsigned char strText_UTF8[]={0xE6,0x88,0x90,0xE9,0x83,0xBD,0xE7,0xA7,0xBB,0xE6,0x9F,0xAF,0x54,0x54,0x53};
    unsigned char strText_UTF16_BE[]={0x62,0x10,0x90,0xfd,0x79,0xfb,0x67,0xef,0x00,0x54,0x00,0x54,0x00,0x53};
    unsigned char strText_UTF16_LE[]={0x10,0x62,0xfd,0x90,0xfb,0x79,0xef,0x67,0x54,0x00,0x54,0x00,0x53,0x00};
    unsigned char strText_UTF16_BO[]={0xfe,0xff,0x62,0x10,0x90,0xfd,0x79,0xfb,0x67,0xef,0x00,0x54,0x00,0x54,0x00,0x53};
    unsigned char strText_UTF16_LO[]={0xff,0xfe,0x10,0x62,0xfd,0x90,0xfb,0x79,0xef,0x67,0x54,0x00,0x54,0x00,0x53,0x00};
		
	  pa_config();
		ol_audio_register_pa_hook(pa_hook);

    while(0!= ol_audio_enable(OL_AUDIO_ITF_RECEIVER))
    {
        ol_os_task_sleep(200);//sleep for 1s
    }		

    op_uart_printf("------tts_demo play------");

    ol_audio_set_volume(OL_AUDIO_SPK_LEVEL_9);
    ol_os_task_sleep(200);

    ol_tts_set_role(TTS_ROLE_MALE);
    ol_tts_set_vemode(TTS_VEMODE_REVERB);

    ol_tts_set_cb(tts_play_cb);
    res = ol_tts_set_speed(100);
    op_uart_printf("ol_tts_set_speed, res = %d", res);

    res = ol_tts_set_volume(32767);
    op_uart_printf("ol_tts_set_volume,res = %d",res);

#if 0
    res = ol_tts_spk(strText, sizeof(strText),OL_TTS_NONE,0);
    op_uart_printf("ol_tts_spk, res = %d", res);
    ol_os_task_sleep(10*200);
#else
    res = ol_tts_spk(strText_GBK, sizeof(strText_GBK),OL_TTS_TYPE_GBK,0);
    op_uart_printf("ol_tts_spk, res = %d", res);
    ol_os_task_sleep(10*200);
#endif

    ol_audio_disable();
}

void tts_demo(void)
{
    op_uart_printf("------ol_audio_demo  start!!!------\n");
    test_tts_demo();
    op_uart_printf("------ol_audio_demo  end!!!------\n");
}

