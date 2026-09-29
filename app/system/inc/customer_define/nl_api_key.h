#ifndef _NL_API_KEY_H_
#define _NL_API_KEY_H_


typedef struct {
	int32_t key_id;
	int8_t long_or_short_press;
	int8_t press_or_release;
}keypad_info_t;

/**
 * @brief    获取矩阵键盘键值，无按键按下时返回0
 *
 * @return  0 – 无效值  非0 –键值
 */
UINT8 nl_read_key(void);

/**
 * @brief    获取powerkey键值
 * 获取power key的键值、按下、弹起状态、短按或者长按。
 * 
 * @return  返回值为结构体，成员变量key_id即为pwrkey键值，press_or_release = 0,表示处于release状态，等于1表示处于按下状态，long_or_short_press等于2表示短按，等于3表示长按
 */
keypad_info_t nl_get_pwrkeypad_status(void);

typedef void (*key_callback)(void* param);

/**
 * @brief    设置播放tone音，根据不同的tone_id来播放不同的tone音
 * 
 * @param < tone_state >  0 : 停止tone音  1 : 开始tone音 
 * @param <tone_id>播放不同类型的tone音
 * 0.AUDEV_TONE_DTMF_0
 * 1.AUDEV_TONE_DTMF_1
 * 2.AUDEV_TONE_DTMF_2
 * 3.AUDEV_TONE_DTMF_3
 * 4.AUDEV_TONE_DTMF_4
 * 5.AUDEV_TONE_DTMF_5
 * 6.AUDEV_TONE_DTMF_6
 * 7.AUDEV_TONE_DTMF_7
 * 8.AUDEV_TONE_DTMF_8
 * 9.AUDEV_TONE_DTMF_9
 * 10.AUDEV_TONE_DTMF_A
 * 11.AUDEV_TONE_DTMF_B
 * 12.AUDEV_TONE_DTMF_C
 * 13.AUDEV_TONE_DTMF_D
 * 14.AUDEV_TONE_DTMF_SHARP
 * 15.AUDEV_TONE_DTMF_STAR
 * 16.AUDEV_TONE_DIAL
 * 17.AUDEV_TONE_SUBSCRIBER_BUSY
 * 18.AUDEV_TONE_RADIO_PATHACKNOWLEDGEMENT
 * 19.AUDEV_TONE_CALL_DROPPED
 * 20.AUDEV_TONE_SPECIAL_INFORMATIONormation
 * 21.AUDEV_TONE_CALL_WAITING
 * 22.AUDEV_TONE_RINGING
 *
 * @param tone_duration：tone音持续时间，范围1到10，间隔为100ms；
 * @param mix_factor：tone音的音量，范围为1到4，共4个等级；
 * 
 * @return  0：成功  <0 ：失败
 */
INT32 nl_tone_play(uint8_t tone_state, uint8_t tone_id, uint32_t tone_duration, uint8_t mix_factor);

/**
 * @brief    电源键回调设置
 * 
 * @param <pwr_cb>回调
 * @param <long_press>长按时间
 * @param <arg>回调参数
 *
 * @return  = 1 - 成功  0 - 失败
 */
INT32 nl_set_pwr_callback_ex(key_callback pwr_cb, UINT16 long_press, void * arg);

#endif