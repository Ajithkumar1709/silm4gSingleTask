#ifndef _NL_API_VOICE_H_
#define _NL_API_VOICE_H_

typedef enum
{
    AUDIO_VOICE_VOLUME,
    AUDIO_PLAY_VOLUME,
    AUDIO_TONE_VOLUME,
} AUDIO_VOLUME_MODE_T;

typedef void (*auPlayerCallback_t)(void);

/**
 * @brief    输入文本GB2312、UTF-8、UNICODE，进行语音播放
 *
 * @param <pData> 文本编码内容，内容为编码的16进制字符串，编码最大长度1024；
 * @param <cEncode> 编码方式支持GB2312、UTF-8、UNICODE   0	： UTF-8   1	： GB2312   2	： UNICODE
 * 
 * @return  0 - 成功    ≠ 0 - 失败
 */
INT32 nl_tts_start(const UINT8 *pData, INT8 cEncode);

/**
 * @brief    查询tts是否正在播放。
 * 
 * @return  true – 正在播放    false – 空闲状态
 */
bool nl_tts_is_playing(void);

/**
 * @brief    停止当前语音播放，此接口仅能停止API播放内容，当AT指令正在播放时此接口会返回失败。
 * 
 * @return  0 - 成功    ≠ 0 - 失败
 */
INT32 nl_tts_stop(void);

/**
 * @brief    设置音量大小，设置后立即生效，但掉电不保存。
 *
 * @param <pData> 文本编码内容，内容为编码的16进制字符串，编码最大长度1024；
 * @param Level:当mode设置为AUDIO_TONE_VOLUME，level：0-4   当mode设置为AUDIO_VOICE_VOLUME  AUDIO_PLAY_VOLUME   level：0-7

 * 
 * @return  0 – 成功    <0 – 失败
 */
INT32 nl_set_volume(AUDIO_VOLUME_MODE_T mode, uint8_t level);

/**
 * @brief    查询音量大小
 * 
 * @return  >=0 – 成功，返回音量等级    <0 – 失败
 */
INT32 nl_get_volume(AUDIO_VOLUME_MODE_T mode);

/**
 * @brief    异步播放，当回调函数不为空时，播放结束执行回调函数。cb_ctx可以为NULL。
 *
 * @param < format >指定播放的音频格式：1：PCM格式  2：WAV格式  3：MP3格式  4：AMR格式
 * @param < buff >存放音频数据的缓冲区地址
 * @param < size >指定音频数据长度
 * @param < cb_ctx >播放结束后的回调函数
 * 
 * @return  0：执行成功  -1：音频格式错误  -2：入参错误  -3：audio忙  -4：播放错误
 */
INT32 nl_audio_mem_play(UINT8 format, UINT8 * buff, UINT32 size, auPlayerCallback_t cb_ctx);

#endif