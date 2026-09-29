#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <assert.h>
#include <time.h>
#include "diag_API.h"
#include "mbtk_circle_buf.h"
#include "mbtk_os.h"
#include "mbtk_log.h"
#ifdef MBTK_TTS_SUPPORT_ytTTS

#include "yt_tts_interface_300.h"
#include "yt_tts_cb_define.h"

#ifdef _MSC_VER
#include <windows.h>
#include <mmsystem.h>
#include <io.h>
#endif

extern unsigned int yt_get_imei_info(char *imei);
extern bool mbtk_tts_stop_flag(void);
extern unsigned char mbtk_tts_get_speed(void);
extern void mbtk_pcm_play_internal(DRV_CIRCLE_BUF_T *circle_buff, char *pcm_buff);


/*************************************************************
    Function Definitions
*************************************************************/
int mbtk_tts_data_convert(char *txt, uint16 txt_len, uint8 data_type, DRV_CIRCLE_BUF_T *circle_buff, char *pcm_buff)
{
    int nReturn;
    char *pMemoryBufferForTTS = NULL;
    unsigned int nMemorySizeInByte = YT_TTS_MEM_SIZE_IN_BYTE ;

    short pSpeechFrame[400];
    unsigned int nSampleNumber, nSampleNumber_ALL;

    clock_t lStart, lEnd;
    int nFlag;
    int frame_num =0;
    int tts_speed = 100;
    unsigned char charOne = 0;
    char strTwoChars[3];
    char strArgOne[200], strArgTwo[200], strReserved[100]="Reserved";

    if(NULL == txt || txt_len <= 0 || NULL == circle_buff || NULL == pcm_buff)
    {
        MLOG_D(MLOG_TTS, TTS,"ytTTS input param check error\n");
        return -1;
    }

    strcpy(strTwoChars,"FA");
    strcpy(strTwoChars,"[A");

    //charOne = yt_ConvertTwoCharsToByte(strTwoChars, &nFlag);
    charOne += 2;
    charOne = 'A';
    //yt_ConvertByteToTwoChars(charOne,strTwoChars);

    MLOG_D(MLOG_TTS, TTS,"STEP 1.1: set 6 callback functions for File I/O!!");
    //STEP 1.1: set 6 callback functions for File I/O
    yt_set_cb_for_fopen_read_300(yt_open_file_for_read);
    yt_set_cb_for_fopen_write_300(yt_open_file_for_write);
    yt_set_cb_for_fseek_300(yt_seek_file);
    yt_set_cb_for_fread_300(yt_read_file);
    yt_set_cb_for_fwrite_300(yt_write_file);
    yt_set_cb_for_fclose_300(yt_close_file);

    MLOG_D(MLOG_TTS, TTS,"//STEP 1.2: set 5 callback functions for Networking!!");
    //STEP 1.2: set 5 callback functions for Networking
    yt_tts_set_cb_gethostbyname_300(yt_gethostbyname);
    yt_tts_set_cb_socket_300(yt_socket);
    yt_tts_set_cb_send_300(yt_send);
    yt_tts_set_cb_recv_300(yt_recv);
    yt_tts_set_cb_closesocket_300(yt_closesocket);

    MLOG_D(MLOG_TTS, TTS,"//STEP 1.3: set 1 callback function for ChipID!!");
    //STEP 1.3: set 1 callback function for ChipID
    yt_tts_set_cb_getChipID_300(yt_get_imei_info);
    //STEP 1.4: set callback function for printing TTS engine  info...
    //yt_tts_set_cb_print_info_300(mbtk_print_info);

    yt_tts_set_file_one_300("yt_server_info_one.dat");//strFileOne: maximum valid length: 150 bytes
    yt_tts_set_file_two_300("yt_server_info_two.dat");//strFileTwo: maximum valid length: 150 bytes
    if(0 != yt_tts_is_active_300())
    {
        //not activated, start activation...
        nReturn = yt_tts_start_activation_300(); //try to activate this device
    }
    MLOG_D(MLOG_TTS, TTS,"//STEP 2: prepare memory buffer!!");

    //STEP 2: prepare memory buffer
    pMemoryBufferForTTS = (char *)malloc(nMemorySizeInByte);
    assert(NULL != pMemoryBufferForTTS);
    yt_tts_set_memory_buffer_300(pMemoryBufferForTTS,nMemorySizeInByte);	

    MLOG_D(MLOG_TTS, TTS,"//STEP 3: initialize TTS engine!!");

    //STEP 3: initialize TTS engine
    strcpy(strArgOne,"ReservedArgOne");
    strcpy(strArgTwo,"ReservedArgTwo");

    nReturn = yt_tts_initialize_300(strReserved,YT_LANG_ID_MANDARIN_300,strArgOne,YT_VOICE_ID_FEMALE_300,strArgTwo);
    assert(0 == nReturn);

    MLOG_D(MLOG_TTS, TTS,"//STEP 4: input text to TTS engine!!");
    //STEP 4: input text to TTS engine
    MLOG_D(MLOG_TTS, TTS,"//yt_tts_input_text_mbcs_180..!! %d", txt_len);
    MLOG_D(MLOG_TTS, TTS,"//yt_tts_input_text_mbcs_180..!! %s", txt);
    if(data_type == 2)
        nReturn = yt_tts_input_text_mbcs_300(txt,txt_len,YT_DATE_YYYY_MM_DD_300,YT_TEXT_TYPE_DEFAULT_300);
    else
        nReturn = yt_tts_input_text_utf16_300(txt,txt_len,YT_DATE_YYYY_MM_DD_300,YT_TEXT_TYPE_DEFAULT_300);						
    MLOG_D(MLOG_TTS, TTS,"yt_tts_input_text_utf16_180 return =  %d!!",nReturn);

    //STEP 3: synthesize speech for text
    tts_speed = mbtk_tts_get_speed();
    yt_tts_set_rate_300(tts_speed);
    yt_tts_set_pitch_300(105);

    lStart = mbtk_os_get_ticks();
    nSampleNumber_ALL = 0;

    if(mbtk_tts_spk_start() != 0)
    {
        yt_tts_free_resource_300();
        free(pMemoryBufferForTTS);
        return -1;
    }

    while(1)
    {
        nReturn = yt_tts_get_speech_frame_300(pSpeechFrame,&nSampleNumber);

        if(nSampleNumber > 0)
        {
            DRV_CBufWrite(circle_buff, pSpeechFrame, nSampleNumber*2);
            MLOG_D(MLOG_TTS, TTS,"yt_tts_get_speech_frame_300: %d \r\n",nSampleNumber*2);
            frame_num++;

            if(0 == nSampleNumber_ALL)
            {
                lEnd = mbtk_os_get_ticks();
                MLOG_D(MLOG_TTS, TTS,"Response_time: %i ms\r\n",(lEnd-lStart)*200);
            }
            nSampleNumber_ALL += nSampleNumber;
        }

        if(1 == nReturn)
        {
            mbtk_pcm_play_internal(circle_buff, pcm_buff);
            frame_num = 0;
        }
        else if(nReturn == 2)
        {
            if(frame_num % 5 == 0)
            {
                mbtk_pcm_play_internal(circle_buff, pcm_buff);
                frame_num = 0;
            }
        }

        if(0 == nReturn || mbtk_tts_stop_flag())
        {
            if(mbtk_tts_stop_flag())
                break;

            if(tts_speed > 149)
                mbtk_os_task_sleep(300-tts_speed);
            else
                mbtk_os_task_sleep(200-tts_speed);
            break; //complete the entire input text
        }
    }

    MLOG_D(MLOG_TTS, TTS,"//STEP 4: free resources...!!");
    yt_tts_free_resource_300();
    //STEP 4: free resources...
    free(pMemoryBufferForTTS);
}

#endif /*MBTK_TTS_SUPPORT_ytTTS*/