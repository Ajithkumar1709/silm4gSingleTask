#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mbtk_circle_buf.h"
#include "mbtk_flash_file_system.h"
#include "mbtk_log.h"
#include "mbtk_tts.h"


#ifdef MBTK_TTS_TYPE_N
#include "yike-resource-16K.h"
#endif
#include "ivTTS.h"

/* constant for TTS heap size */
//#define ivTTS_HEAP_SIZE       50000           // Mixed, no effect
#define ivTTS_HEAP_SIZE         (70 * 1024)     // Mixed, effect

typedef enum
{
    TTS_NONE = MBTK_TTS_TYPE_NONE,
    TTS_TYPE_UTF16LE = MBTK_TTS_TYPE_UTF16LE,    /* UTF-16 little-endian */
    TTS_TYPE_GBK = MBTK_TTS_TYPE_GBK,        /* GBK */
    TTS_TYPE_GB2312 = MBTK_TTS_TYPE_GB2312,     /* GB2312 */
    TTS_TYPE_UTF8 = MBTK_TTS_TYPE_UTF8,       /* UTF-8 */
    TTS_TYPE_UTF16BE = MBTK_TTS_TYPE_UTF16BE,    /* UTF-16 big-endian */
}mbtk_tts_type;
typedef enum
{
    TTS_ROLE_AUTO = MBTK_TTS_ROLE_AUTO,                  /* role automatically */
    TTS_ROLE_FEMALE = MBTK_TTS_ROLE_FEMALE,                /* say words by female voice */
    TTS_ROLE_MALE = MBTK_TTS_ROLE_MALE,                  /* say words by male voice */
} mbtk_tts_role_type;


typedef enum
{
	TTS_TYPE_N,
	TTS_TYPE_FILE,
	TTS_TYPE_FLASH
}mbtk_tts_gen_type;

extern bool mbtk_tts_stop_flag(void);
extern int mbtk_tts_get_speed(void);
extern int mbtk_tts_get_volume(void);
extern int mbtk_tts_get_role_type(void);
extern void mbtk_tts_write_buffer(char *data, int length);

int mbtk_get_tts_type()
{
	#ifdef MBTK_TTS_TYPE_FLASH
	return TTS_TYPE_FLASH;
	#elif defined(MBTK_TTS_TYPE_FILE)
	return TTS_TYPE_FILE;
	#else
	return TTS_TYPE_N;
	#endif
}

int mbtk_get_tts_lang()
{
	#ifdef MBTK_TTS_SUPPORT_ivtts_en
	
	return ivTTS_LANGUAGE_ENGLISH;
	#else
	
	return ivTTS_LANGUAGE_CHINESE;
	#endif
}

int mbtk_read_tts_res(unsigned int offset,unsigned char* buf_addr, unsigned int size)
{
	UINT32 tts_start = get_tts_res_begin_address();
	UINT32 len;
	//MLOG_D(MLOG_COMM, COMM,"%s: before %x\n", __func__, tts_start);

	if((buf_addr == NULL))		
		return -1;
	len = mbtk_qspi_read(tts_start+offset, (unsigned int)buf_addr,size);
	if(len) return -1;
	//MLOG_D(MLOG_COMM, COMM,"%s: after %x\n", __func__, tts_start);

	return 0;
}


/*************************************************************
    Function Definitions
*************************************************************/
int ivTTS_speed(int speed)
{
    int ivspeed = ivTTS_SPEED_NORMAL;

    if(speed >= 50 && speed < 100)
    {
        ivspeed = ivTTS_SPEED_MAX - 650*(speed - 50);
    }
    else if(speed > 100 && speed <= 200)
    {
        ivspeed = ivTTS_SPEED_MIN + 325*(200-speed);
    }

    return ivspeed;
}

/* Get User Message, whether to exit synthesis*/
ivTTSErrID DoMessage(void)
{
    if(!mbtk_tts_stop_flag())
    {
        return ivTTS_ERR_OK;    //Continue synthesis
    }
    else
    {
        return ivTTS_ERR_EXIT;  //Stop synthesis
    }
}

ivTTSErrID ivCall OutputCB
(
  ivPointer pParameter,     /* [in] user callback parameter */
  ivUInt16 nCode,           /* [in] output data code */
  ivCPointer pcData,        /* [in] output data buffer */
  ivSize nSize              /* [in] output data size */
)
{
    ivTTSErrID tErr = DoMessage();

	
	MLOG_D(MLOG_TTS, TTS,"tErr = %d nSize %d\n", tErr, nSize);
	
    if ( tErr != ivTTS_ERR_OK )
        return tErr;

    //Play voice data
    mbtk_tts_write_buffer(pcData, nSize);

    return ivTTS_ERR_OK;
}

/* read resource callback */
ivBool ivCall ReadResCB
(
  ivPointer pParameter,     /* [in] user callback parameter */
  ivPointer pBuffer,        /* [out] read resource buffer */
  ivResAddress iPos,        /* [in] read start position */
  ivResSize nSize           /* [in] read size */
)
{

	#ifdef MBTK_TTS_TYPE_FILE
	
	int ret = 0;
    int fd = (int)pParameter;

    ol_FFS_Seek(fd, iPos, SEEK_SET);
    ret = ol_FFS_Read(fd, pBuffer, nSize);

    return (ret == (int)nSize)?ivTrue:ivFalse;
	#elif defined(MBTK_TTS_TYPE_FLASH)
	int ret = 0;
	ret = mbtk_read_tts_res(iPos, pBuffer, nSize);

	if(ret == 0)
		return ivTrue;

	return ivFalse;
	#else
	
	char *p = (char*)pParameter;

    memcpy(pBuffer, p + iPos, nSize);
    return ivTrue;
	#endif
}

int mbtk_tts_check_data_codepage(uint8 data_type)
{
    int codepage = ivTTS_CODEPAGE_GBK;

    switch(data_type)
    {
        case TTS_TYPE_GBK:
            codepage = ivTTS_CODEPAGE_GBK;
            break;
        case TTS_TYPE_GB2312:
            codepage = ivTTS_CODEPAGE_GB2312;
            break;
        case TTS_TYPE_UTF8:
            codepage = ivTTS_CODEPAGE_UTF8;
            break;
        case TTS_TYPE_UTF16LE:
            codepage = ivTTS_CODEPAGE_UTF16LE;
            break;
        case TTS_TYPE_UTF16BE:
            codepage = ivTTS_CODEPAGE_UTF16BE;
            break;
    }

    return codepage;
}

int mbtk_tts_convert_role(int role_type)
{
    int type = ivTTS_ROLE_XIAOYAN;

    switch(role_type)
    {
        case TTS_ROLE_MALE:
            type = ivTTS_ROLE_DUOXU;
            break;
        case TTS_ROLE_AUTO:
        case TTS_ROLE_FEMALE:
            type = ivTTS_ROLE_XIAOYAN;
            break;
    }
    return type;
}


#ifdef MBTK_TTS_HEAP_STATIC
  static unsigned char tts_heap_g[ivTTS_HEAP_SIZE] = {0};
#endif

int mbtk_tts_data_convert(char *txt, uint16 txt_len, uint8 data_type)
{
    ivHTTS hTTS;
    ivPByte pHeap = NULL;
    ivTResPackDescExt tResPackDesc;
    ivTTSErrID ivReturn;
    int tts_speed = 0;
	#ifdef MBTK_TTS_TYPE_FILE
    int fd = 0;
	#endif
    int codepage = ivTTS_CODEPAGE_GBK;
    int tts_volume = 0;
    int tts_role_type = 0;

    if(NULL == txt || txt_len <= 0)
    {
        MLOG_D(MLOG_TTS, TTS,"ivTTS input param check error\n");
        return -1;
    }

	#ifdef MBTK_TTS_TYPE_FILE
	fd = ol_FFS_Open("english_16K.irf", "rb");
    if(fd < 0)
    {
        MLOG_D(MLOG_TTS, TTS,"ivTTS open file english_16K.irf fail, %d\n", fd);
        return -1;
    }
	MLOG_D(MLOG_TTS, TTS,"ivTTS open file english_16K.irf success");
	
	#endif

    //Init resource package

	#ifdef MBTK_TTS_TYPE_FILE
    tResPackDesc.pCBParam = fd;
	#elif defined(MBTK_TTS_TYPE_N)
	tResPackDesc.pCBParam = mlp_resource;
	#endif
    tResPackDesc.pfnRead = ReadResCB;
    tResPackDesc.pfnMap = NULL;
    tResPackDesc.nSize = 0;

    //TTS internal use
    tResPackDesc.pCacheBlockIndex = NULL;
    tResPackDesc.pCacheBuffer = NULL;
    tResPackDesc.nCacheBlockSize = 0;
    tResPackDesc.nCacheBlockCount = 0;
    tResPackDesc.nCacheBlockExt = 0;

	#ifdef MBTK_TTS_HEAP_STATIC
	pHeap = tts_heap_g;
	#else
    pHeap = (ivPByte)malloc(ivTTS_HEAP_SIZE);
	#endif
	memset(pHeap,0,ivTTS_HEAP_SIZE);
    if(NULL == pHeap)
    {
    	#ifdef MBTK_TTS_TYPE_FILE
        ol_FFS_Close(fd);
		#endif
        MLOG_D(MLOG_TTS, TTS,"ivTTS malloc pHeap memery fail\n");
        return -1;
    }


    memset(pHeap, 0x0, ivTTS_HEAP_SIZE);

    //Create TTS instance
    ivReturn = ivTTS_Create(&hTTS, (ivPointer)pHeap, ivTTS_HEAP_SIZE, ivNull, (ivPResPackDescExt)&tResPackDesc, (ivSize)1,NULL);
    if(ivTTS_ERR_OK != ivReturn)
    {
        MLOG_D(MLOG_TTS, TTS,"ivTTS_Create return 0x%x\n", ivReturn);
		
		#ifndef MBTK_TTS_HEAP_STATIC
        free(pHeap);
		#endif
        return -1;
    }

    //Set output callback
    ivReturn = ivTTS_SetParam(hTTS, ivTTS_PARAM_OUTPUT_CALLBACK, (ivUInt32)OutputCB);
    //MLOG_D(MLOG_TTS, TTS,"ivTTS_SetParam ivTTS_PARAM_OUTPUT_CALLBACK return 0x%x\n", ivReturn);

    //Set input code page
    codepage = mbtk_tts_check_data_codepage(data_type);
    ivReturn = ivTTS_SetParam(hTTS, ivTTS_PARAM_INPUT_CODEPAGE, codepage);
    //MLOG_D(MLOG_TTS, TTS,"ivTTS_SetParam ivTTS_PARAM_INPUT_CODEPAGE return 0x%x\n", ivReturn);

    //Set language
    #ifdef MBTK_TTS_SUPPORT_ivtts_en	
    ivReturn = ivTTS_SetParam(hTTS, ivTTS_PARAM_LANGUAGE, ivTTS_LANGUAGE_ENGLISH);
	#else
    ivReturn = ivTTS_SetParam(hTTS, ivTTS_PARAM_LANGUAGE, ivTTS_LANGUAGE_AUTO);
	#endif
    //MLOG_D(MLOG_TTS, TTS,"ivTTS_SetParam ivTTS_PARAM_LANGUAGE return 0x%x\n", ivReturn);

    //Set speed
    tts_speed = mbtk_tts_get_speed();
    ivReturn = ivTTS_SetParam(hTTS, ivTTS_PARAM_VOICE_SPEED, tts_speed);
    //MLOG_D(MLOG_TTS, TTS,"ivTTS_SetParam ivTTS_PARAM_VOICE_SPEED return 0x%x\n", ivReturn);

    //Set volume
    tts_volume = mbtk_tts_get_volume();
    ivReturn = ivTTS_SetParam(hTTS, ivTTS_PARAM_VOLUME, tts_volume);
    //MLOG_D(MLOG_TTS, TTS,"ivTTS_SetParam ivTTS_PARAM_VOLUME return 0x%x\n", ivReturn);

    //Set speaker role
    int type_temp = mbtk_tts_get_role_type();
    tts_role_type = mbtk_tts_convert_role(type_temp);
    ivReturn = ivTTS_SetParam(hTTS, ivTTS_PARAM_ROLE, tts_role_type);

    //set vemode
    int tts_vemode = mbtk_tts_get_vemode();
    ivReturn = ivTTS_SetParam(hTTS, ivTTS_PARAM_VEMODE, tts_vemode);

    int tts_pitch = mbtk_tts_get_pitch();
    ivReturn = ivTTS_SetParam(hTTS, ivTTS_PARAM_VOICE_PITCH, tts_pitch);


	int tts_digit = mbtk_tts_get_digit();
	ivReturn = ivTTS_SetParam(hTTS, ivTTS_PARAM_READ_DIGIT, tts_digit);

	
        //========================
        //TTS synthesis
        //========================
        //unsigned char strText_GBK[]= {"你好，这里是科大讯飞语音合成系统。这个字母读h。"};
        //ivReturn = ivTTS_SynthText(hTTS, ivText(strText_GBK), -1););

        ivReturn = ivTTS_SynthText(hTTS, ivText(txt), txt_len);
        MLOG_D(MLOG_TTS, TTS,"ivTTS_SynthText return 0x%x\n", ivReturn);

    ivReturn = ivTTS_Destroy(hTTS);

    if( tResPackDesc.pCacheBlockIndex )
    {
        free(tResPackDesc.pCacheBlockIndex);
    }
    if( tResPackDesc.pCacheBuffer )
    {
        free(tResPackDesc.pCacheBuffer);
    }
    if(NULL != pHeap)
    {
		#ifndef MBTK_TTS_HEAP_STATIC
		free(pHeap);
		#endif
    }

	#ifdef MBTK_TTS_TYPE_FILE
	ol_FFS_Close(tResPackDesc.pCBParam);
	#endif
    return 0;
}

int mbtk_tts_get_version(UINT8 *piMajor, UINT8 *piMinor, UINT16 *piRevision)
{
    int ret = -1;

    ret = ivTTS_GetVersion(piMajor,piMinor,piRevision);
    MLOG_D(MLOG_TTS, TTS,"Version is %d.%d.%d",piMajor,piMinor,piRevision);
    return ret;
}
