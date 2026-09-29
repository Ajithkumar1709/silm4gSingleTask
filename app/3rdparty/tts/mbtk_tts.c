#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include <time.h>

#include "mbtk_pub_type.h"
#include "mbtk_tts.h"
#include "mbtk_os.h"

#if 1//def MBTK_TTS_SUPPORT

#include "ol_audio.h"
#include "mbtk_comm_api.h"
#include "mbtk_circle_buf.h"

#define TRUE 1
#define FALSE 0


#define TTS_TASK_SIZE                   4*1024
#define TTS_MIN_SIZE(a,b)               ((a)<(b)?(a):(b))

typedef void(*mbtk_tts_status_cb)(int type);

typedef enum
{
    MBTK_TTS_NONE,
    MBTK_TTS_PLAY,
    MBTK_TTS_MENU_PLAY  //MENU PLAY Priority is lower than normal TTS
}mbtk_tts_status;

typedef struct
{
    uint8 play_status;
    mbtk_tts_status_cb status_cb;
}mbtk_tts_info;

typedef struct
{
    uint8 type;       //mbtk_tts_info play_status
    uint8 data_type;
    uint8 *txt_data;
    uint16 data_len;
}mbtk_tts_msg;


static mbtk_msgqref mbtk_tts_msgq = 0;
static mbtk_flagref mbtk_tts_block_flag;
static mbtk_flagref mbtk_tts_play_flag;
static mbtk_taskref mbtk_tts_ref1;
static mbtk_taskref mbtk_tts_ref2;
static int tts_inited = 0;

static int g_tts_speed = 0;
static int g_tts_volume = MBTK_TTS_VOLUME_MAX;
static int g_tts_language = 0;
static int g_tts_role_type = 0;
static int g_tts_vemode = 0;
static int g_tts_pitch = 0;
static int g_tts_digit = 0;
static char tts_play_buffer[5*MBTK_PCM_16K_SIZE]= {0};
static char tts_data_buff[MBTK_TTS_DATA_BUF_SIZE] = {0};

DRV_CIRCLE_BUF_T mbtk_tts_c_buf;
static mbtk_ostimerref mbtk_tts_timer;


bool g_tts_stop_flag = TRUE;
bool g_tts_convert_flag = FALSE;  //¡À¨ª¨º?¡Áa??¨°?¨ª¨º3¨¦

UINT32 atHandle_t = -1;


extern int mbtk_tts_support_flag(void);
extern int mbtk_tts_data_convert(char *txt, uint16 txt_len, uint8 data_type);

/*************************************************************
    Function Definitions
*************************************************************/
bool mbtk_tts_stop_flag(void)
{
    return g_tts_stop_flag;
}


mbtk_tts_info *mbtk_get_tts_info(void)
{
    static mbtk_tts_info info = {0};
    return &info;
}

static void mbtk_tts_play_cb(int rest_data)
{
    //op_uart_printf("mbtk_tts_play_cb - %d",rest_data);
    ol_os_flag_set(mbtk_tts_block_flag, 0x01, MBTK_OS_FLAG_OR);
}

int mbtk_tts_start_pcmplayer(void)
{
    int status = 0;

    //op_uart_printf("mbtk_tts_start_pcmplayer");

    ol_oem_stop_play();

/*
    if(MBTK_Audio_Enable(MBTK_AUDIO_ITF_LOUDSPEAKER) < 0)
    {
        //op_uart_printf("[%s] tts play Audio_Enable fail\r\n", __func__);
        return -1;
    }
*/
    ol_oem_set_play_callback(mbtk_tts_play_cb);
    status = ol_oem_start_player(MBTK_OEM_SAMPLE_RATE_16K,MBTK_OEM_CHANNEL1,0);
    if(0 != status)
    {
        //op_uart_printf("mbtk_tts_spk_start fail\r\n");
        return -1;
    }
    //op_uart_printf("mbtk_tts_start_pcmplayer ok\r\n");

    return 0;
}

void mbtk_tts_write_buffer(const char *data, int length)
{
    int bytes = 0;
    int remain = 0;
	static int write_num = 0;

    if(NULL != data && length > 0)
    {
        remain = ol_cbuff_remain_size(&mbtk_tts_c_buf);
		ol_os_timer_stop(mbtk_tts_timer);

		while(remain<length){
			ol_os_task_sleep(2);
			remain = ol_cbuff_remain_size(&mbtk_tts_c_buf);
		}
        bytes = ol_cbuff_write(&mbtk_tts_c_buf, data, length);
		write_num++;

		
		if(write_num>=5)
			ol_os_flag_set(mbtk_tts_play_flag, 0x01, MBTK_OS_FLAG_OR);
		
        //if(bytes < length)
        {
            //op_uart_printf("[%s] tts buffer loss, load[%d] in[%d] w[%d]",__func__,remain,length,bytes);
        }
    }
}

void mbtk_tts_spk_play(void)
{
    UINT32 event;
    int status;
    int load_len = 0;
    int play_len = 0;
    int avail_len = 0;
    char *pcm_buf = tts_play_buffer;

   
    while(1)
    {
    	status = ol_os_flag_wait(mbtk_tts_play_flag, 0x01, MBTK_OS_FLAG_OR_CLEAR, &event, MBTK_OS_SUSPEND);

		while(1){
        avail_len = ol_oem_getbufferavail();
        load_len = ol_cbuff_payload_size(&mbtk_tts_c_buf);

        //op_uart_printf("[%s] play load_len %d, avail_len %d",__func__,load_len,avail_len);
        if(0 == load_len)
        {
        	if(g_tts_convert_flag&&!g_tts_stop_flag){
				ol_os_task_sleep(100);//?a¨¢?2£¤¨ª¨º¡Á?o¨®¨°???¡Á??¨²
				g_tts_stop_flag = TRUE;
        	}
            break;
        }

        if(avail_len < MBTK_PCM_8K_SIZE)
        {
            ol_os_task_sleep(2);
            continue;
        }

        memset(pcm_buf, 0, 5*MBTK_PCM_16K_SIZE);
        play_len = TTS_MIN_SIZE(5*MBTK_PCM_16K_SIZE, TTS_MIN_SIZE(avail_len, load_len));
        play_len = ol_cbuff_read(&mbtk_tts_c_buf, pcm_buf, play_len);

        ol_oem_play_set_buffer(pcm_buf, play_len);
        ol_oem_play_resume();
        ol_oem_start_play();

        //ol_os_flag_set(mbtk_tts_block_flag, 0, MBTK_OS_FLAG_AND);
        status = ol_os_flag_wait(mbtk_tts_block_flag, 0x01, MBTK_OS_FLAG_OR_CLEAR, &event, MBTK_OS_SUSPEND);
        //op_uart_printf("ol_os_flag_wait %d\r\n", status);
		}

    }	
    //op_uart_printf("mbtk_tts_spk_play end %d", load_len);
}


void auto_turn_off_audio(void *data)
{
	//op_uart_printf("timeout auto_turn_off_audio");
	g_tts_stop_flag = TRUE;
}




void mbtk_tts_task(void *argv)
{
    mbtk_os_status status;
    mbtk_tts_msg msginfo;
    int id = 0;
    unsigned short read_len = 0;
    mbtk_tts_info *info = mbtk_get_tts_info();
    unsigned char *mbtk_tts_data_buffer = NULL;

    while(1)
    {
        status=ol_os_msgq_recv(mbtk_tts_msgq, (char *)&msginfo, sizeof(mbtk_tts_msg), MBTK_OS_SUSPEND);
        switch(msginfo.type)
        {
            case MBTK_TTS_PLAY:
            case MBTK_TTS_MENU_PLAY:
            {
                mbtk_tts_data_buffer = tts_data_buff;//malloc(MBTK_TTS_DATA_BUF_SIZE);
                if(NULL == mbtk_tts_data_buffer)
                {
                    //op_uart_printf("malloc tts data buffer fail NULL");
                    break;
                }

                //init tts voice data buffer
                memset(mbtk_tts_data_buffer, 0x0, MBTK_TTS_DATA_BUF_SIZE);
                ol_cbuff_init(&mbtk_tts_c_buf, mbtk_tts_data_buffer, MBTK_TTS_DATA_BUF_SIZE);

                g_tts_stop_flag = FALSE;
				g_tts_convert_flag = FALSE;
                info->play_status = msginfo.type;
                if(info->status_cb)
                    info->status_cb(MBTK_TTS_PLAY);

                //op_uart_printf("tts convert start, %d, %d",msginfo.data_type, msginfo.data_len);
				if(mbtk_tts_start_pcmplayer()==0){
					#ifdef MBTK_IVTTS_USE_FILE
						ol_os_timer_start(mbtk_tts_timer, 10*1024, 0, auto_turn_off_audio, 0);
					#else
						ol_os_timer_start(mbtk_tts_timer, 200, 0, auto_turn_off_audio, 0);
					#endif
					if(0 == mbtk_tts_data_convert(msginfo.txt_data,msginfo.data_len,msginfo.data_type)){
						g_tts_convert_flag = TRUE;
	                    while(!mbtk_tts_stop_flag()){
	                    	ol_os_task_sleep(10);
	                    }
               	 	}
				}

            	ol_oem_stop_play();
                mbtk_tts_set_cb(NULL);
                g_tts_stop_flag = TRUE;
				if(NULL != msginfo.txt_data)
				{
					ol_free(msginfo.txt_data);
					msginfo.txt_data = NULL;
				}

                info->play_status = MBTK_TTS_NONE;
                if(info->status_cb)
                    info->status_cb(MBTK_TTS_NONE);

                ol_cbuff_init(&mbtk_tts_c_buf, NULL, 0);
                //free(mbtk_tts_data_buffer);
                mbtk_tts_data_buffer = NULL;
                break;
            }
        }

        if(NULL != msginfo.txt_data)
		{
			ol_free(msginfo.txt_data);
			msginfo.txt_data = NULL;
		}
    }
}


/********************************************
    open TTS hal api
*********************************************/
int mbtk_tts_init(void)
{
    mbtk_os_status status = mbtk_os_success;
    void *mbtk_tts_task_stack = NULL;
    
    //op_uart_printf("mbtk_tts_init, begin");

    if(0 == tts_inited)
    {
        //init create tts flag
        status = ol_os_flag_creat(&mbtk_tts_block_flag);
        //ASSERT(status == ol_os_success);

		status = ol_os_flag_creat(&mbtk_tts_play_flag);
        //ASSERT(status == mbtk_os_success);

		status = ol_os_timer_creat(&mbtk_tts_timer);
		//ASSERT(status == mbtk_os_success);

        //init create tts msg queue
        status = ol_os_msgq_creat(&mbtk_tts_msgq, "mbtk_tts_msgq", sizeof(mbtk_tts_msg), 20, MBTK_OS_FIFO);
       // ASSERT(status == mbtk_os_success);

        //init create tts convert task
        status = ol_os_task_creat(&mbtk_tts_ref1, NULL, TTS_TASK_SIZE, 95,"ttstask", mbtk_tts_task, NULL);
        //ASSERT(status == mbtk_os_success);

		status = ol_os_task_creat(&mbtk_tts_ref2, NULL, TTS_TASK_SIZE, 94,"ttsplay", mbtk_tts_spk_play, NULL);
		//ASSERT(status == mbtk_os_success);

        tts_inited = 1;
    }

    //op_uart_printf("mbtk_tts_init, end");

    return 0;
}


void mbtk_tts_deinit()
{
	if(tts_inited){

		if(mbtk_tts_timer){
			ol_os_timer_delete(mbtk_tts_timer);
			mbtk_tts_timer = NULL;
		}

		if(mbtk_tts_ref1){
			ol_os_task_delete(mbtk_tts_ref1);
			mbtk_tts_ref1 = NULL;
		}

		if(mbtk_tts_ref2){
			ol_os_task_delete(mbtk_tts_ref2);
			mbtk_tts_ref1 = NULL;
		}
	
		if(mbtk_tts_block_flag){
			ol_os_flag_delete(mbtk_tts_block_flag);
			mbtk_tts_block_flag = NULL;
		}
		if(mbtk_tts_play_flag){
			ol_os_flag_delete(mbtk_tts_play_flag);
			mbtk_tts_play_flag = NULL;
		}

		
		if(mbtk_tts_msgq){
			ol_os_msgq_delete(mbtk_tts_msgq);
			mbtk_tts_msgq = NULL;


		}

		tts_inited = 0;
	}

	return 0;
}



int mbtk_tts_stop(void)
{
    mbtk_tts_info *info = mbtk_get_tts_info();

    //op_uart_printf("mbtk_tts_stop  play_status=%d", info->play_status);
    if(info->play_status == MBTK_TTS_NONE)
        return 0;

    g_tts_stop_flag = TRUE;
	g_tts_convert_flag = TRUE;
    ol_os_msgq_flush(mbtk_tts_msgq);
	ol_os_timer_stop(mbtk_tts_timer);
    while(info->play_status!=MBTK_TTS_NONE)
        ol_os_task_sleep(2);
	ol_os_flag_set(mbtk_tts_block_flag, 0x01, MBTK_OS_FLAG_OR);

    //op_uart_printf("mbtk_tts_stop  0");
    return 0;
}

///from   0  tts   1  menu tts
int mbtk_tts_spk(char *txt, uint16 txt_len, int data_type, uint8 from)
{
    mbtk_tts_msg msg = {0};
    mbtk_os_status os_status = mbtk_os_success;
    mbtk_tts_info *info = mbtk_get_tts_info();

    if(NULL == txt || 0 == txt_len)
    {
        //op_uart_printf("mbtk_tts_spk input check fail");
        return -1;
    }

    if(0 != mbtk_tts_init())
    {
        return -1;
    }
    mbtk_tts_stop();

    msg.txt_data = ol_malloc(txt_len+2);
    if(NULL == msg.txt_data)
    {
        //op_uart_printf("mbtk_tts_spk maolloc NULL");
        return -1;
    }

    memset(msg.txt_data, 0, txt_len+2);
    memcpy(msg.txt_data,txt, txt_len);

    msg.type = from+1;
    msg.data_len = txt_len;
    msg.data_type = (uint8)data_type;
    //op_uart_printf("mbtk_tts_spk data_type-%d len-%d", msg.data_type,msg.data_len);

    os_status = ol_os_msgq_send(mbtk_tts_msgq, sizeof(mbtk_tts_msg), &msg, MBTK_OS_NO_SUSPEND);
    return os_status;
}

int mbtk_tts_set_cb(mbtk_tts_status_cb      cb)
{
    mbtk_tts_info *info = mbtk_get_tts_info();
    bool ret = 0;

    if(MBTK_TTS_PLAY != info->play_status)
        info->status_cb = cb;
    else
        ret = -1;

    //op_uart_printf("mbtk_tts_set_cb - %x", cb);

    return ret;
}

int mbtk_tts_set_speed(int speed)
{
    g_tts_speed = speed;

    return 0;
}

int mbtk_tts_set_volume(int volume)
{
    if(volume < MBTK_TTS_VOLUME_MIN || volume > MBTK_TTS_VOLUME_MAX)
    {
        return -1;
    }

    g_tts_volume = volume;
    return 0;
}

int mbtk_tts_set_role(int type)
{
    g_tts_role_type = type;
    return 0;
}

int mbtk_tts_set_vemode(int vemode)
{
    g_tts_vemode = vemode;
    return 0;
}

int mbtk_tts_set_pitch(int pitch)
{
    g_tts_pitch = pitch;
	return 0;
}

int mbtk_tts_set_digit(int digit)
{
	g_tts_digit = digit;
	return 0;
}


int mbtk_tts_get_speed(void)
{
    return g_tts_speed;
}

int mbtk_tts_get_volume(void)
{
    return g_tts_volume;
}

int mbtk_tts_get_role_type(void)
{
    return g_tts_role_type;
}

int mbtk_tts_get_vemode(void)
{
    return g_tts_vemode;
}

int mbtk_tts_get_pitch(void)
{
    return g_tts_pitch;
}

int mbtk_tts_get_digit()
{
	return g_tts_digit;
}


int mbtk_tts_get_play_status(void)
{
    mbtk_tts_info *info = mbtk_get_tts_info();
    return info->play_status;
}

bool mbtk_tts_check_can_stop(void)
{
    mbtk_tts_info *info = mbtk_get_tts_info();

    if(info->play_status  == MBTK_TTS_PLAY)
        return false;

    return true;
}



int ol_tts_set_cb(OL_AUDIO_PLAYER_CALLBACK        cb)
{
	int  ret=-1;
	
	ret = mbtk_tts_set_cb(cb);

	return ret;
}

int ol_tts_set_speed(int speed)
{
	int  ret=-1;
	
	ret = mbtk_tts_set_speed(speed);
	return ret;
}
int ol_tts_spk(char *txt, UINT16 txt_len, int data_type, UINT8 from)
{
	int  ret=-1;
	
	ret = mbtk_tts_spk(txt, txt_len, data_type, from);

	return ret;
}

int ol_tts_stop()
{
	int  ret=-1;
	
	ret = mbtk_tts_stop();

	return ret;
}

int ol_tts_set_volume(int volume)
{
    int ret = -1;

    ret = mbtk_tts_set_volume(volume);
    return ret;
}

int ol_tts_set_role(OL_TTS_ROLE role_type)
{
    int ret = -1;

    ret = mbtk_tts_set_role(role_type);

    return ret;
}

int ol_tts_set_vemode(OL_TTS_VEMODE vemode)
{
    int ret = -1;

    ret = mbtk_tts_set_vemode(vemode);

    return ret;
}

int ol_tts_set_digit(int digit)
{
    int ret = -1;

    ret = mbtk_tts_set_digit(digit);

    return ret;
}



int ol_tts_set_pitch(int pitch)
{
    int ret = -1;

    ret = mbtk_tts_get_pitch();

    return ret;
}



#endif /*MBTK_TTS_SUPPORT*/
