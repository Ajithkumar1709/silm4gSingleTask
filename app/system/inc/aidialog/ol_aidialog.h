#ifndef __STB_DIALOG_H__
#define __STB_DIALOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#define STB_DIALOG_SPEAKER_COUNT    32


typedef struct stb_dialog_device_cfg_tag
{
    char *app_id;  // 应用ID，需申请
    char *product_key;  // 产品KEY，每个产品需不同
    char *product_secret;  // 产品密钥，每个产品需不同
    char *device_name; // 设备名称，每个设备需不同
    int (*auth_data_write)(uint8_t *auth_data, uint32_t data_len); // 返回0成功，其它值失败
    int (*auth_data_read)(uint8_t *auth_data, uint32_t max_len); // 返回实际读取的长度，小于等于0表示未读取到数据
} stb_dialog_device_cfg_t;

typedef enum stb_vad_event_tag 
{
    STB_VAD_EVENT_NULL = 0,
    STB_VAD_EVENT_BEGIN = 1,
    STB_VAD_EVENT_END = 2
} stb_vad_event_e;

typedef enum stb_dialog_codec_fmt_type_tag
{
    STB_DIALOG_CODEC_FMT_PCM  = 0,
    STB_DIALOG_CODEC_FMT_OGG  = 1,
    STB_DIALOG_CODEC_FMT_MP3  = 2,
    STB_DIALOG_CODEC_FMT_OPUS = 3,
} stb_dialog_codec_fmt_type_e;

typedef enum stb_dialog_audio_play_mode_tag
{
    STB_DIALOG_AUDIO_PLAY_MODE_DATA = 0,
    STB_DIALOG_AUDIO_PLAY_MODE_FILE = 1,
} stb_dialog_audio_play_mode;

typedef enum stb_dialog_image_fmt_tag
{
    STB_DIALOG_IMAGE_FMT_JPEG = 0,
    STB_DIALOG_IMAGE_FMT_PNG  = 1,
    STB_DIALOG_IMAGE_FMT_GIF  = 2,
    STB_DIALOG_IMAGE_FMT_WEBP  = 3,
    STB_DIALOG_IMAGE_FMT_BMP = 4,
    STB_DIALOG_IMAGE_FMT_TIFF  = 5,
    STB_DIALOG_IMAGE_FMT_ICO = 6,
    STB_DIALOG_IMAGE_FMT_DIB  = 7,
    STB_DIALOG_IMAGE_FMT_ICNS = 8,
    STB_DIALOG_IMAGE_FMT_SGI = 9,
    STB_DIALOG_IMAGE_FMT_JPEG2000  = 10,

} stb_dialog_image_fmt_e;


typedef struct stb_dialog_record_cfg_tag {
    stb_dialog_codec_fmt_type_e fmt; // 录音音频格式
    uint32_t sample_rate; // 录音采样率
    uint8_t channel; // 录音声道数
    uint32_t record_buf_num; // 录音缓存个数
    uint32_t record_timeout; // 录音超时时间，单位ms
    uint32_t record_net_buff_num;   // 录音时网络缓存个数
    uint32_t record_data_max_len;
    int record_gain;

    struct {
        uint16_t in_size;
        uint16_t out_size;
    } opus_param;  // opus格式时参数，仅在fmt为STB_DIALOG_CODEC_FMT_OPUS时有效

    struct {
        uint32_t vad_segment_furation;
        uint32_t end_window_size;
        uint32_t force_to_speech_time;
    } cloud_asr_param;

    // volume: 0~100, 录音增益
    // vad_start_threshold: 单位ms, VAD开始阈值
    // vad_stop_threshold: 单位ms, VAD结束阈值
    // vad_silence_start_threshold: 0~1000, 单位ms, VAD静音开始阈值
    int (*record_open)(int volume, int vad_start_threshold, int vad_stop_threshold, int vad_silence_start_threshold); // 打开录音的回调函数, 返回0表示成功，非0表示失败
    int (*record_start)(void);                    // 开始录音的回调函数, 返回0表示成功，非0表示失败
    int (*record_stop)(void);                     // 停止录音的回调函数, 返回0表示成功，非0表示失败
    int (*record_data)(void *data, uint32_t len); // 录音数据的回调函数, 返回0表示没有数据，非0表示实际数据长度
    int (*record_close)(void);                    // 关闭录音的回调函数, 返回0表示成功，非0表示失败
} stb_dialog_record_cfg_t;

typedef enum stb_dialog_vad_type_tag
{
    STB_DIALOG_VAD_NULL   = 0,
    STB_DIALOG_VAD_CUSTOM = 1,
    STB_DIALOG_VAD_STB    = 2,
} stb_dialog_vad_type_e;

typedef struct stb_dialog_vad_cfg_tag {
    stb_dialog_vad_type_e vad_type; // VAD类型， 0表示不使用VAD，1表示使用客户的VAD，2表示使用STB自带的VAD
    int vad_start_threshold;
    int vad_stop_threshold;
    int vad_silence_start_threshold;
    union {
        struct {
            int vad_energy_threshold;       // VAD能量阈值
            int min_tailing_silence;        // 最短语音长度
        } stb_vad_cfg;

        struct {
            int (*vad_detect)(void);  // VAD 状态回调函数，返回1表示VAD start，返回2表示VAD end, 0表示非VAD
            int (*vad_clear)(void);  // VAD 状态清除回调函数，将VAD状态设置为0
            int (*vad_silence_detect)(void);  // VAD 静音状态回调函数，返回1表示VAD静音开始，0表示非VAD静音。VAD start后，静音状态持续时间超过vad_silence_start_threshold时，静音开始
            void (*vad_silence_clear)(void);  // VAD 静音状态清除回调函数，将VAD静音状态设置为0
        } custom_vad_cfg;
    };
} stb_dialog_vad_cfg_t;

typedef struct stb_dialog_tts_cfg_tag {
    stb_dialog_codec_fmt_type_e fmt; // TTS音频格式
    uint32_t sample_rate; // 录音采样率
    uint32_t channel; // 录音声道数
    uint32_t tts_data_interval;
    float tts_speed; // 0.8~2.0
    uint32_t tts_max_pcm_data_len;
    uint32_t tts_play_data_buff_num;
    uint32_t tts_remaining_data_waterlevel_high;
    uint32_t tts_remaining_data_waterlevel_low;

    struct {
        uint16_t encode_package_size;
        uint16_t encode_ratio; 
    } opus_param;  // opus格式时参数，仅在fmt为STB_DIALOG_CODEC_FMT_OPUS时有效
    
    // TTS 播放回调函数，支持PCM和OPUS格式。根据fmt配置2选1
    int (*tts_play_open)(void);                        // 打开TTS的回调函数, 返回0表示成功，非0表示失败
    int (*tts_play_start)(void);               // 音频播放开始回调函数，返回0表示成功，非0表示失败
    int (*tts_play_stop)(void);                        // 音频播放结束回调函数，返回0表示成功，非0表示失败。该函数会等待缓冲区数据播放完。
    int (*tts_play_abort)(void);                       // 音频播放取消回调函数，返回0表示成功，非0表示失败。该函数会立即停止播放。
    int (*tts_play_data)(uint8_t *data, uint32_t len); // 音频数据的回调函数, 返回0表示没有数据，非0表示实际数据长度
} stb_dialog_tts_cfg_t;

typedef struct stb_dialog_audio_play_cfg_tag {
    stb_dialog_audio_play_mode audio_play_mode;
    // 音乐播放回调函数，支持MP3/OGG等音频格式
    int (*audio_play_open)(stb_dialog_codec_fmt_type_e fmt);          // 打开播放回调函数, 返回play id，大于等于0表示成功，小于0表示失败
    int (*audio_play_start)(int play_id);                             // 音频播放开始回调函数，返回0表示成功，非0表示失败
    int (*audio_play_stop)(int play_id);                              // 音频播放结束回调函数，返回0表示成功，非0表示失败。该函数会等待缓冲区数据播放完。
    int (*audio_play_abort)(int play_id);                             // 音频播放取消回调函数，返回0表示成功，非0表示失败。该函数会立即停止播放。
    int (*audio_play_data)(int play_id, uint8_t *data, uint32_t len); // 音频数据的回调函数, data=NULL, len=0表示数据结束。 返回0表示没有数据，非0表示实际数据长度
    int (*audio_play_file)(char *file_name);                         // 播放音频文件
} stb_dialog_audio_play_cfg_t;

typedef struct stb_dialog_voice_clone_cfg_tag {
    stb_dialog_codec_fmt_type_e fmt; // 录音音频格式
    uint32_t sample_rate; // 录音采样率
    uint32_t channel; // 录音声道数
    uint8_t no_switch; // 不要自动切换到clone的角色中

    struct {
        uint16_t in_size;
        uint16_t out_size;
    } opus_param;  // opus格式时参数，仅在fmt为STB_DIALOG_CODEC_FMT_OPUS时有效

    int (*voice_clone_record_open)(void);                     // 打开声音复刻的回调函数, 返回0表示成功，非0表示失败
    int (*voice_clone_record_start)(void);                    // 开始声音复刻的回调函数, 返回0表示成功，非0表示失败
    int (*voice_clone_record_stop)(void);                    // 停止声音复刻的回调函数, 返回0表示成功，非0表示失败
    int (*voice_clone_record_data)(void *data, uint32_t len); // 声音复刻数据的回调函数, 返回0表示没有数据，非0表示实际数据长度
    int (*voice_clone_record_close)(void);                    // 关闭声音复刻的回调函数, 返回0表示成功，非0表示失败
} stb_dialog_voice_clone_cfg_t;


typedef struct stb_dialog_image_capture_cfg_tag {
    stb_dialog_image_fmt_e image_fmt; // 上传图片的格式
    uint32_t image_max_len; // 单个图片最大size，单位byte, 0表示使用默认值，默认值512KB
    uint32_t every_capture_time_ms; // 每隔多少毫秒进行一次图片采集，单位毫秒,0表示一次对话只进行一次图片采集，在开始对话的时候截图
    int (*image_capture_open)(void);                     // 打开图片采集的回调函数, 返回0表示成功，非0表示失败
    int (*image_capture_start)(void);                    // 开始图片采集回调函数, 返回0表示成功，非0表示失败
    int (*image_capture_stop)(void);                    // 停止图片采集回调函数, 返回0表示成功，非0表示失败
    int (*image_capture_data)(uint8_t *data, uint32_t len); // 图片采集数据的回调函数, data为图片内容，返回0表示没有数据，非0表示实际数据长度
    int (*image_capture_close)(void);                    // 关闭图片采集的回调函数, 返回0表示成功，非0表示失败
} stb_dialog_image_capture_cfg_t;

/**
 * @brief 对话触发模式枚举。
 *
 * 该枚举定义了对话模块的触发模式。
 *
 * @param STB_DIALOG_TRIGGER_MODE_NULL  无触发模式。
 * @param STB_DIALOG_TRIGGER_MODE_AUTO  自动触发模式，不需要用户触发，会自动开始对话。
 * @param STB_DIALOG_TRIGGER_MODE_USER  用户触发模式，每次对话，需要用户触发，触发后开始一次对话。
 */
typedef enum stb_dialog_trigger_mode_tag
{
    STB_DIALOG_TRIGGER_MODE_NULL    = 0,
    STB_DIALOG_TRIGGER_MODE_AUTO    = 1,  // 自动触发模式，不需要用户触发，会自动开始对话
    STB_DIALOG_TRIGGER_MODE_USER    = 2   // 用户触发模式，每次对话，需要用户触发，触发后开始一次对话
} stb_dialog_trigger_mode_e;

typedef enum stb_dialog_break_mode_tag
{
    STB_DIALOG_BREAK_MODE_NULL    = 0,  // 对话时不打断
    STB_DIALOG_BREAK_MODE_BTN     = 1,  // 按键打断
    STB_DIALOG_BREAK_MODE_VOICE   = 2   // 语音打断
} stb_dialog_break_mode_e;

typedef enum stb_dialog_text_process_mode_tag
{
    STB_DIALOG_TEXT_PROCESS_MODE_INTERMEDIATE   = 0,  // 对话时云端ASR的中间结果
    STB_DIALOG_TEXT_PROCESS_MODE_FINAL          = 1   // 对话时云端ASR的最终结果
} stb_dialog_text_process_mode_e;

typedef enum stb_dialog_text_mode_tag
{
    STB_DIALOG_TEXT_MODE_REQUEST  = 0,  // 返回的文本是提问者的问题
    STB_DIALOG_TEXT_MODE_RESPONSE = 1   // 返回的文本是云端的回复
} stb_dialog_text_mode_e;

/**
 * @brief 对话事件枚举。
 *
 * 该枚举定义了对话模块可能的事件。
 *
 **/
typedef enum stb_dialog_event_tag
{
    STB_DIALOG_EVENT_NULL             = 0,
    STB_DIALOG_EVENT_SERVICE_AUTH_BEGIN,
    STB_DIALOG_EVENT_SERVICE_AUTH_SUCCESS,
    STB_DIALOG_EVENT_SERVICE_AUTH_FAILED,
    STB_DIALOG_EVENT_SERVICE_AUTH_TIMEOUT,

    STB_DIALOG_EVENT_SERVICE_CONNECT_BEGIN,
    STB_DIALOG_EVENT_SERVICE_CONNECT_SUCCESS,
    STB_DIALOG_EVENT_SERVICE_CONNECT_FAIL,
    STB_DIALOG_EVENT_SERVICE_CONNECT_TIMEOUT,
    STB_DIALOG_EVENT_SERVICE_DISCONNECTED,

    STB_DIALOG_EVENT_WS_LINK_CONNECTING,
    STB_DIALOG_EVENT_WS_LINK_DISCONNECTED,
    STB_DIALOG_EVENT_WS_LINK_CONNECTED,

    STB_DIALOG_EVENT_IDLE,
    STB_DIALOG_EVENT_DIALOG_BEGIN,
    STB_DIALOG_EVENT_DIALOG_END,
    STB_DIALOG_EVENT_RECORDING,
    STB_DIALOG_EVENT_RSP_WAITING,
    STB_DIALOG_EVENT_RSP_TIMEOUT,
    STB_DIALOG_EVENT_PLAYING,
    STB_DIALOG_EVENT_PLAY_END,
    
    STB_DIALOG_EVENT_ANSWER_TIME,
    STB_DIALOG_EVENT_ASR_FAIL,
    STB_DIALOG_EVENT_DIALOG_TEXT,

    STB_DIALOG_EVENT_VOICE_CLONE_SERVICE_CONNECT_BEGIN,
    STB_DIALOG_EVENT_VOICE_CLONE_SERVICE_CONNECT_SUCCESS,
    STB_DIALOG_EVENT_VOICE_CLONE_BEGIN,
    STB_DIALOG_EVENT_VOICE_CLONE_RECORDING_BEGIN,
    STB_DIALOG_EVENT_VOICE_CLONE_SUCCESS,
    STB_DIALOG_EVENT_VOICE_CLONE_REACH_LIMIT,
    STB_DIALOG_EVENT_VOICE_CLONE_FAIL,
    STB_DIALOG_EVENT_VOICE_CLONE_DOWNLOAD_SUCCESS,

    STB_DIALOG_EVENT_VOICE_SELECT_BEGIN,
    STB_DIALOG_EVENT_VOICE_SELECT_NAME,
    STB_DIALOG_EVENT_VOICE_SELECT_TONE_DOWNLOAD,
    STB_DIALOG_EVENT_VOICE_SELECT_END,

    STB_DIALOG_EVENT_LOW_POWER_WAIT,
    STB_DIALOG_EVENT_REPORT_REQUEST_ID,

    STB_DIALOG_EVENT_PLAY_TTS_FINISH,
    STB_DIALOG_EVENT_DOWNLOAD_TTS_FINISH,

    STB_DIALOG_EVENT_QUOTO_EXCEED,
    STB_DIALOG_EVENT_NLP_INTENT,
    STB_DIALOG_EVENT_NLP_EMOTION,

    STB_DIALOG_EVENT_IMAGE_CAPTURE_BEGIN,
    STB_DIALOG_EVENT_IMAGE_CAPTRUE_SUCCESS,
    STB_DIALOG_EVENT_IMAGE_CAPTRUE_FAIL,
    STB_DIALOG_EVENT_IAMGE_RECGNIZE_TIMEOUT,

    STB_DIALOG_EVENT_CUSTOM_DATA_RECV
} stb_dialog_event_e;

typedef void (*stb_dialog_event_cb)(stb_dialog_event_e event, uint8_t *data);

typedef struct stb_dialog_text_result_tag
{
    stb_dialog_text_mode_e           text_mode;
    stb_dialog_text_process_mode_e   process_mode;
    char                            *dialog_data;
} stb_dialog_text_result_t;

typedef struct stb_dialog_mode_cfg_tag
{
    stb_dialog_trigger_mode_e trigger_mode;       // 对话触发模式
    stb_dialog_break_mode_e   break_mode;         // 对话打断模
    bool                      enable_play_record;  // 是否支持播放时录音，打开后，可以过滤无意义的噪声导致的打断，但是对回声消除的要求比较高，如果回声消除不好，会影响识别率。
    bool                      enable_long_memory;  // 是否支持长记忆，打开后，可以支持长对话，但是会增加对话的延迟。
    bool                      enable_intention;    // 是否支持意图识别，打开后，可以识别对话意图。
    bool                      enable_emotion;      // 是否支持情感识别，打开后，可以识别对话情感。
    uint32_t                  enter_low_power_timeout;   // 低功耗模式下空闲状态超时时间，空闲时间超过该值后会进入低功耗状态，单位秒
} stb_dialog_mode_cfg_t;

typedef struct stb_dialog_event_cfg_tag
{
    stb_dialog_event_cb       event_cb;       // 对话事件回调函数
} stb_dialog_event_cfg_t;

/**
 * @brief 对话状态枚举。
 *
 * 该枚举定义了对话模块的状态。
 *
 * 
 */
typedef enum stb_dialog_status_tag
{
    STB_DIALOG_STATUS_NULL = 0,
    STB_DIALOG_STATUS_DIALOG_INIT,
    STB_DIALOG_STATUS_AUTH_INIT,
    STB_DIALOG_STATUS_AUTH_SUCCESS,
    STB_DIALOG_STATUS_AUTH_FAIL,

    STB_DIALOG_STATUS_WS_INIT,
    STB_DIALOG_STATUS_WS_CONNECTING,
    STB_DIALOG_STATUS_WS_CONNECTED,
    STB_DIALOG_STATUS_WS_CONNECT_FAILED,

    STB_DIALOG_STATUS_DIALOG_IDLE,
    STB_DIALOG_STATUS_RECORD_START,
    STB_DIALOG_STATUS_RECORDING,
    STB_DIALOG_STATUS_RECORD_END,
    STB_DIALOG_STATUS_PLAY_START,
    STB_DIALOG_STATUS_PLAYING,
    STB_DIALOG_STATUS_PLAY_END,

    STB_DIALOG_STATUS_VOICE_CLONE_SERVICE_WAIT,
    STB_DIALOG_STATUS_VOICE_CLONE_START_WAIT,
    STB_DIALOG_STATUS_VOICE_CLONE_RECORDING,
    STB_DIALOG_STATUS_VOICE_CLONE_RECORD_END,
    STB_DIALOG_STATUS_VOICE_CLONE_QUERY,
    STB_DIALOG_STATUS_VOICE_CLONE_SAMPLE_PLAYING,
    STB_DIALOG_STATUS_VOICE_CLONE_TTS_DOWNLOAD,
    STB_DIALOG_STATUS_VOICE_CLONE_END,

    STB_DIALOG_STATUS_VOICE_SELECT_BEGIN,
    STB_DIALOG_STATUS_VOICE_SELECT_PROCESS,
    STB_DIALOG_STATUS_VOICE_SELECT_PLAYING,

    STB_DIALOG_STATUS_ROLE_SET,
    STB_DIALOG_STATUS_LOW_POWER_WAIT,
    STB_DIALOG_STATUS_TTS_PLAY_DOWNLOAD,
    STB_DIALOG_STATUS_SERVER_RESPONSE_TIMEOUT,
    STB_DIALOG_STATUS_DEFAULT_SPEAKER_SET,
    STB_DIALOG_STATUS_IMAGE_START,
    STB_DIALOG_STATUS_IMAGE_CAPTURE,
    STB_DIALOG_STATUS_IMAGE_END
} stb_dialog_status_e;

typedef enum stb_trigger_action_tag 
{
    STB_TRIGGER_ACTION_NULL = 0,
    STB_TRIGGER_ACTION_TRIGGER,
    STB_TRIGGER_ACTION_START,
    STB_TRIGGER_ACTION_STOP,
    STB_TRIGGER_ACTION_RECORD_STOP,
    STB_TRIGGER_ACTION_CLONE_VOICE,
    STB_TRIGGER_ACTION_SELECT_VOICE,
    STB_TRIGGER_ACTION_RESTART,
    STB_TRIGGER_ACTION_IMAGE_START,
} stb_trigger_action_e;

typedef enum stb_dialog_tone_type_tag
{
    STB_DIALOG_TONE_NETOK = 0,      // 网络连接成功
    STB_DIALOG_TONE_NETFAIL,        // 网络连接失败
    STB_DIALOG_TONE_DLSTART,        // 开始对话
    STB_DIALOG_TONE_DLEND,          // 对话结束
    STB_DIALOG_TONE_ASRFAIL,        // 我没有听清楚
    STB_DIALOG_TONE_VCSTART,        // 现在开始复刻你的声音
    STB_DIALOG_TONE_VCRECEND,       // 录音结束
    STB_DIALOG_TONE_VCTTS,          // 开始下载复刻声音
    STB_DIALOG_TONE_VCEND,          // 复刻声音结束
    STB_DIALOG_TONE_VCCEL,          // 复刻声音取消
    STB_DIALOG_TONE_VCFAIL,         // 复刻声音失败
    STB_DIALOG_TONE_VCSELECT,       // 已选择该声音
    STB_DIALOG_TONE_DISCONNECT,     // 网络已断开
    STB_DIALOG_TONE_RDSTART,        // 角色配置中,请稍等
    STB_DIALOG_TONE_RDEND,          // 角色配置完成
    STB_DIALOG_TONE_DLTIMEOUT,      // 对话超时
} stb_dialog_tone_type_e;

typedef struct stb_dialog_tone_update_tag
{
    stb_dialog_tone_type_e tone_id;
    char *tone_text;
} stb_dialog_tone_update_t;

typedef enum stb_dialog_role_speaker_type_tag 
{
    STB_DIALOG_ROLE_SPEAKER_TYPE_NULL = 0,
    STB_DIALOG_ROLE_SPEAKER_TYPE_VOLC,
    STB_DIALOG_ROLE_SPEAKER_TYPE_CLONE,
} stb_dialog_role_speaker_type_e;

typedef enum stb_dialog_role_tts_type_tag 
{
    STB_DIALOG_ROLE_TTS_TYPE_NULL = 0,
    STB_DIALOG_ROLE_TTS_TYPE_BID,   // 双向流式TTS
} stb_dialog_role_tts_type_e;

// 定义日志级别枚举
typedef enum {
    STB_DIALOG_LOG_LEVEL_PRINT, // PRINT级别仅本地调试，不会上报到云端
    STB_DIALOG_LOG_LEVEL_DEBUG,
    STB_DIALOG_LOG_LEVEL_INFO,
    STB_DIALOG_LOG_LEVEL_WARNING,
    STB_DIALOG_LOG_LEVEL_ERROR,
    STB_DIALOG_LOG_LEVEL_OFF
} stb_dialog_log_level_t;

typedef struct stb_dialog_speaker_info_tag
{
    char *speaker_name;
    char *speaker_id;
    char *speaker_role;
    char *speaker_type;
    char *speaker_tts_type;
} stb_dialog_speaker_info_t;

typedef struct stb_dialog_speaker_list_tag
{
    int total_speaker_num;
    int start;
    int end;
    stb_dialog_speaker_info_t speaker_info[STB_DIALOG_SPEAKER_COUNT];
} stb_dialog_speaker_list_t;

typedef struct stb_dialog_nlp_intent_tag
{
    char *intent;  // 意图类型
    char *value;   // 意图参数
} stb_dialog_nlp_intent_t;


typedef struct stb_dialog_nlp_emotion_tag
{
    char *type;  // 情感类型，目前固定为 "emotion"
    char *value; // 情感参数，包括：Happy;Sad;Caring;Surprised;Afraid;Disgusted;Confused;Bored;Tired;Curious;
                 //              Relaxed;Smiling;Frowning;Grimacing;Winking;Neutral;Pensive;Amused;Doubtful;Angry
} stb_dialog_nlp_emotion_t;

/**
 * @brief 设置设备信息。
 *
 * 调用此函数配置设备信息。
 *
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_device_cfg_init(stb_dialog_device_cfg_t *device_cfg);

/**
 * @brief 配置录音参数。
 *
 * 调用此函数配置录音参数。
 *
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_record_cfg_init(stb_dialog_record_cfg_t *record_cfg);

/**
 * @brief 配置TTS参数。
 *
 * 调用此函数配置TTS参数。
 *
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_tts_cfg_init(stb_dialog_tts_cfg_t *tts_cfg);

/**
 * @brief 配置复刻声音参数。
 *
 * 调用此函数配置复刻声音参数。
 *
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_voice_clone_cfg_init(stb_dialog_voice_clone_cfg_t *voice_clone_cfg);

/**
 * @brief 配置对话模式参数。
 *
 * 调用此函数配置对话模式参数。
 *
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_mode_cfg_init(stb_dialog_mode_cfg_t *mode_cfg);

/**
 * @brief 初始化事件通知回调。
 *
 * 调用此函数初始化事件通知回调。
 *
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_event_cfg_init(stb_dialog_event_cfg_t *event_cfg);

/**
 * @brief 配置声音播放参数。
 *
 * 调用此函数配置声音播放参数。
 *
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_audio_play_cfg_init(stb_dialog_audio_play_cfg_t *audio_play_cfg);

/**
 * @brief 配置图像参数。
 *
 * 调用此函数配置图像参数。
 *
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_image_capture_cfg_init(stb_dialog_image_capture_cfg_t *image_capture_cfg);

/**
 * @brief 配置用户指定的提示词。
 *
 * 调用此函数配置用户指定的提示词。
 *
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_user_custom_prompt_init(char *user_custom_prompt);

/**
 * @brief 初始化对话模块。
 *
 * 调用此函数以初始化对话模块。
 *
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_init(void);

/**
 * @brief 启动对话。
 *
 * 调用此函数以启动对话模块。
 *
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_start(void);

/**
 * @brief 停止对话。
 *
 * 调用此函数以启动对话模块。
 *
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_stop(void);

/**
 * @brief 触发/停止/取消对话。
 *
 * 调用此函数以触发/停止/取消对话。
 *
 * @param action 触发动作，使用stb_trigger_action_e枚举定义的类型。
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_trigger(stb_trigger_action_e action);

/**
 * @brief 执行音色切换。
 *
 * 调用此函数以执行音色切换。
 *
 */
extern void ol_aidialog_voice_select(void);

/**
 * @brief 通过name选择speaker。
 *
 * 通过speaker name选择对应的speaker。
 *
 * @param speaker_name speaker的名字。
 */
extern void ol_aidialog_voice_select_by_name(const char *speaker_name);

/**
 * @brief 通过id选择speaker。
 *
 * 通过speaker id选择对应的speaker。
 *
 * @param speaker_id speaker的id。
 */
extern void ol_aidialog_voice_select_by_id(const char *speaker_id);

/**
 * @brief 删除提示音文件。
 *
 * 通过speaker id删除该speaker下的提示音。
 *
 * @param speaker_id speaker的id。
 * @param speaker_type 提示音类型。
 */
extern void ol_aidialog_voice_delete(const char *speaker_id, stb_dialog_role_speaker_type_e speaker_type);

/**
 * @brief 获取当前的运行状态。
 *
 * 调用此函数获取当前状态机的运行状态。
 *
 * @return 返回当前的运行状态。
 */
extern stb_dialog_status_e ol_aidialog_status_get(void);

/**
 * @brief 获取process任务的循环次数。
 *
 * 调用此函数获取process任务的循环次数。
 *
 * @return 返回当前process任务循环的次数。
 */
extern uint32_t ol_aidialog_process_running_count_get(void);

/**
 * @brief 下载指定speaker的提示音。
 *
 * 调用此函数下载指定name的speaker的提示音。
 *
 * @param speaker_naem speaker的名字。
 */
extern void ol_aidialog_tone_download_tone_speaker(const char *speaker_name);

/**
 * @brief 设置提示音的文本内容。
 *
 * 调用此函数设置不同提示音的文本内容。
 *
 * @param tone_update 提示音文本内容。
 * @param num 需要设置的提示音文本的个数。
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_tone_set_text(stb_dialog_tone_update_t *tone_update, int num);

/**
 * @brief 设置角色。
 *
 * 调用此函数设置角色。
 *
 * @param role_name 角色名字。
 * @param role_id 角色id。
 * @param speaker_id speaker id。
 * @param speaker_type speaker类型。
 * @param tts_type tts类型。
 */
extern void ol_aidialog_role_set(const char *role_name, const char *role_id, const char *speaker_id, stb_dialog_role_speaker_type_e speaker_type, 
                         stb_dialog_role_tts_type_e tts_type);

/**
 * @brief 获取对话触发模式。
 *
 * 调用此函数获取对话触发模式。
 *
 * @return 返回对话触发模式对应的枚举值。
 */
extern stb_dialog_trigger_mode_e ol_aidialog_trigger_mode_get(void);

/**
 * @brief 设置对话触发模式。
 *
 * 调用此函数设置对话触发模式。
 *
 * @param trigger_mode 对话触发模式。
 */
extern void ol_aidialog_trigger_mode_set(stb_dialog_trigger_mode_e trigger_mode);

/**
 * @brief 发送用户自定义数据到云端。
 *
 * 调用此函数发送用户自定义数据到云端。
 *
 * @param data 用户需要发送的数据。
 * @param len 用户发送数据的长度。
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_send_user_data(const char *data, int len);

/**
 * @brief 设置发送日志到云端的等级。
 *
 * 调用此函数设置发送日志到云端的等级，高于该等级的则发送到云端。
 *
 * @param level 日志等级。
 */
extern void ol_aidialog_log_level_set(stb_dialog_log_level_t level);

/**
 * @brief 设置打印日志的等级。
 *
 * 调用此函数设置打印日志的等级，高于该等级的则通过串口打印输出。
 *
 * @param level 日志等级。
 */
extern void ol_aidialog_print_level_set(stb_dialog_log_level_t level);

/**
 * @brief 将用户指定的文本内容通过TTS播放出来。
 *
 * 调用此函数将用户指定的文本内容通过TTS播放出来。
 *
 * @param tts_text 用户指定的文本内容。
 */
extern void ol_aidialog_play_user_tts(const char *tts_text);

/**
 * @brief 将用户指定的文本内容的音频保存到指定的路径中。
 *
 * 调用此函数将用户指定的文本内容的音频保存到指定的路径中。
 *
 * @param tts_text 用户指定的文本内容。
 * @param tts_file_path 音频文件需要保存到的路径。
 */
extern void ol_aidialog_download_user_tts(const char *tts_text, const char *tts_file_path);

/**
 * @brief 设置是否可以语音打断。
 *
 * 调用此函数设置是否可以语音打断。
 *
 * @param enable 语音是否可以打断。
 */
extern void ol_aidialog_voice_interrupt_enable_set(bool enable);

/**
 * @brief 设置对话打断模式。
 *
 * 调用此函数设置对话打断模式。
 *
 * @param break_mode 打断模式。
 */
extern void ol_aidialog_break_mode_set(stb_dialog_break_mode_e break_mode);

/**
 * @brief 获取SDK版本号。
 *
 * 调用此函数设置对话打断模式。
 *
 * @return 返回SDK版本号字符串。
 */
extern const char *ol_aidialog_version_get(void);

/**
 * @brief 播放指定类型的提示音。
 *
 * 调用此函数播放指定类型的提示音。
 *
 * @param tone_type 提示音类型。
 */
extern void ol_aidialog_tone_play(stb_dialog_tone_type_e tone_type);

/**
 * @brief 获取speaker list。
 *
 * 调用此函数获取设备支持的speaker list。
 *
 * @param speaker_list speaker列表。
 * @param start 用户指定的从哪个speaker开始获取
 * @param end 用户指定的获取到哪个speaker
 * @return 返回0表示成功，非0表示失败。
 */
extern int ol_aidialog_get_speaker_list(stb_dialog_speaker_list_t *speaker_list, int start, int end);

/**
 * @brief 设置进入音色选择时的提示音内容
 *
 * 调用此函数设置进入音色选择时的提示音内容。
 *
 * @param tips 进入音色选择时的提示音内容
 */
extern void ol_aidialog_set_voice_select_tips(const char *tips);

/**
 * @brief 获取进入音色选择时的提示音内容
 *
 * 调用此函数获取进入音色选择时的提示音内容。
 *
 * @return 音色选择时的提示音内容
 */
extern char *ol_aidialog_get_voice_select_tips(void);

/**
 * @brief 设置是否需要自动播放提示音
 *
 * 调用此函数设置是否需要自动播放提示音。
 * 
 * @param enable 指定是否需要SDK自动播放提示音，0表示不需要SDK自动播放，且不会下载提示音文件
 */
extern void ol_aidialog_config_tone_playing(uint8_t enable);

/**
 * @brief 初始化VAD配置
 *
 * 调用此函数初始化STB VAD配置。
 *
 * @return 0表示成功，非0表示失败。
 */
extern int ol_aidialog_vad_cfg_init(stb_dialog_vad_cfg_t *vad_cfg);

#ifdef __cplusplus
}
#endif

#endif  // __STB_DIALOG_H__
