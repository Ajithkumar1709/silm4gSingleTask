#include <stdint.h>
#include <stdio.h>
#include <string.h>

//#include "mbtk_audio_api.h"
#include "mbtk_os.h"
#ifdef MBTK_TTS_SUPPORT
#include "mbtk_tts.h"
#endif
#include "mbtk_audio_define.h"

void OEMPlayBufferAvailCB(int rest_data);
void OEM_Record(const char* data, int length);
void OEM_TTS_Status_CB(int type);
#define MBTK_OEM_SAMPLE_RATE 8000
#define MBTK_OEM_CHANNEL 1


//#define TONE_HANDLE    //??£¤?¡±??¡ª??€?????¡ã¡±????¡°???€?¡ê¡ãtone¨¦?? 

static mbtk_flagref block_audio_flag;
static uint8 audio_pcm_flag =2;//MBTK_PCM_PLAY_LEV_MAX;




void mbtk_oem_Play_CB(int rest_data)
{
    OEMLogPrintf("mbtk_oem_Play_CB\r\n");
    mbtk_os_flag_set(block_audio_flag, 1, MBTK_OS_FLAG_OR);
}

void oem_auido_init(void)
{
    mbtk_os_status  status;
    static int inited = 0;

    if(inited == 0)
    {
        mbtk_os_flag_creat(&block_audio_flag);
        inited = 1;
    }
}

#ifdef MBTK_POC_SUPPORT_BND
void OEMPlayBufferAvailCB(int rest_data)
{
}
void OEM_Record(const char* data, int length)
{
}
#endif

#ifdef MBTK_POC_SUPPORT_IWALKIE
void OEMPlayBufferAvailCB(int rest_data)
{
}
void OEM_Record(const char* data, int length)
{
}
#endif

int OEM_StarRecord(void)
{
	int ret = 0;

    mbtk_oem_set_record_callback(OEM_Record);
    ret=mbtk_oem_start_recorder(MBTK_OEM_SAMPLE_RATE,MBTK_OEM_CHANNEL,0);//8k 16bit mono

	ret = ((ret==1) ? 0 : 1);

	return ret;
}

int OEM_StopRecord(void)
{
    return mbtk_oem_stop_record();
}

static int f_hdl = -1;
int OEM_StarPlay(void)
{
	OEMLogPrintf("OEM_StarPlay\r\n");
#ifdef MBTK_TTS_SUPPORT
	mbtk_tts_stop();
	//MBTK_PCM_PLAY_LEV0
	
    if(mbtk_oem_pri_set(0)==0){
        return -1;
    }
#endif

    if(mbtk_oem_start_player(MBTK_OEM_SAMPLE_RATE_8K,MBTK_OEM_CHANNEL1,0) == 0)
		mbtk_oem_set_play_callback(OEMPlayBufferAvailCB);
	
    return 0;
}



#ifdef  MBTK_YKS_SUPPORT
int OEM_Stopplay(void)
#else
int OEM_StopPlay(void)
#endif
{
	int ret =0;

	OEMLogPrintf("OEM_StopPlay\r\n");
	ret = mbtk_oem_stop_play();
	#ifdef MBTK_TTS_SUPPORT
	mbtk_oem_pri_clear();
	#endif
	return ret;
}



int OEM_Play(const char *data, int length)
{

	OEMLogPrintf("OEM_Play %d\r\n", length);
	
	mbtk_oem_play_set_buffer(data,length);
	mbtk_oem_play_resume();
	return mbtk_oem_start_play();
}

int OEM_GetPlayBufferAvail(void)
{
    return mbtk_oem_getbufferavail();
}

int OEM_CleanPlayBuffer(void)
{
    return mbtk_oem_cleanplaybuffer();
}


#ifndef MBTK_YKS_SUPPORT
unsigned short OEM_ConvertFourChars(char *strFourChars)
{

	//"fdf9": 0xfd, 0xf9

	unsigned char charHigh, charLow;
	unsigned char charOne;

	unsigned short nCode = 0x0000;

	//arHigh
	charOne = strFourChars[0];
	if(charOne <= 'F' && charOne >= 'A') charOne += 0x20; //make lower

	if(charOne <= '9' && charOne >='0')  charOne -= 0x30;
    if(charOne <='f' && charOne >= 'a')  charOne = charOne - 'a' + 10; // a --> 10

	charHigh = charOne ; 
        charHigh <<= 4;

	charOne = strFourChars[1];
	if(charOne <= 'F' && charOne >= 'A') charOne += 0x20; //make lower

	if(charOne <= '9' && charOne >='0')  charOne -= 0x30;
    if(charOne <='f' && charOne >= 'a')  charOne = charOne - 'a' + 10; // a --> 10

	charHigh += charOne;

	//for charLow...
	charOne = strFourChars[2];
	if(charOne <= 'F' && charOne >= 'A') charOne += 0x20; //make lower

	if(charOne <= '9' && charOne >='0')  charOne -= 0x30;
    if(charOne <='f' && charOne >= 'a')  charOne = charOne - 'a' + 10; // a --> 10

	charLow = charOne ;
        charLow <<= 4;

	charOne = strFourChars[3];
	if(charOne <= 'F' && charOne >= 'A') charOne += 0x20; //make lower

	if(charOne <= '9' && charOne >='0')  charOne -= 0x30;
    if(charOne <='f' && charOne >= 'a')  charOne = charOne - 'a' + 10; // a --> 10

	charLow += charOne;
	//ttle endian 
	nCode = charLow;
	nCode <<= 8;
	nCode |= charHigh;


	return nCode;

}

#else

unsigned short OEM_ConvertFourChars(char *strFourChars)
{

	//"fdf9": 0xfd, 0xf9

	unsigned char charHigh, charLow;
	unsigned char charOne;

	unsigned short nCode = 0x0000;

	//arHigh
	charOne = strFourChars[0];
	if(charOne <= 'F' && charOne >= 'A') charOne += 0x20; //make lower

	if(charOne <= '9' && charOne >='0')  charOne -= 0x30;
    if(charOne <='f' && charOne >= 'a')  charOne = charOne - 'a' + 10; // a --> 10

	charHigh = charOne ; 
        charHigh <<= 4;

	charOne = strFourChars[1];
	if(charOne <= 'F' && charOne >= 'A') charOne += 0x20; //make lower

	if(charOne <= '9' && charOne >='0')  charOne -= 0x30;
    if(charOne <='f' && charOne >= 'a')  charOne = charOne - 'a' + 10; // a --> 10

	charHigh += charOne;

	//for charLow...
	charOne = strFourChars[2];
	if(charOne <= 'F' && charOne >= 'A') charOne += 0x20; //make lower

	if(charOne <= '9' && charOne >='0')  charOne -= 0x30;
    if(charOne <='f' && charOne >= 'a')  charOne = charOne - 'a' + 10; // a --> 10

	charLow = charOne ;
        charLow <<= 4;

	charOne = strFourChars[3];
	if(charOne <= 'F' && charOne >= 'A') charOne += 0x20; //make lower

	if(charOne <= '9' && charOne >='0')  charOne -= 0x30;
    if(charOne <='f' && charOne >= 'a')  charOne = charOne - 'a' + 10; // a --> 10

	charLow += charOne;
	//ttle endian 
	nCode = charHigh;
	nCode <<= 8;
	nCode |= charLow;


	return nCode;

}
#endif

#ifndef AUDIO_TTS_SUPPORT

int OEM_TTS_Stop()
{
	OEMLogPrintf("OEM_TTS_Stop\r\n");
	
#ifdef MBTK_TTS_SUPPORT
	mbtk_tts_stop();
#endif
	return 0;
}
#endif





