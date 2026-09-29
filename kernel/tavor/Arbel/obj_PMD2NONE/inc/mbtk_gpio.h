
// jx.jiang   2020.8.26



#ifndef __MBTK_GPIO_H
#define __MBTK_GPIO_H



#define MBTK_GPIO_ERR -1
#define MBTK_GPIO_OK   0

#ifndef INVALID_GPIO_MFPR_ADDR 
#define INVALID_GPIO_MFPR_ADDR	0xFFFFFFFF
#endif



typedef enum 
{
	mbtk_pin_not_assigned = -1,
	mbtk_pin_1=0,  mbtk_pin_2,  mbtk_pin_3,  mbtk_pin_4,  mbtk_pin_5,  mbtk_pin_6,  mbtk_pin_7,  mbtk_pin_8,  
	mbtk_pin_9,  mbtk_pin_10, mbtk_pin_11, mbtk_pin_12, mbtk_pin_13, mbtk_pin_14, mbtk_pin_15, mbtk_pin_16, 
	mbtk_pin_17, mbtk_pin_18, mbtk_pin_19, mbtk_pin_20, mbtk_pin_21, mbtk_pin_22, mbtk_pin_23, mbtk_pin_24, 
	mbtk_pin_25, mbtk_pin_26, mbtk_pin_27, mbtk_pin_28, mbtk_pin_29, mbtk_pin_30, mbtk_pin_31, mbtk_pin_32,
	mbtk_pin_33, mbtk_pin_34, mbtk_pin_35, mbtk_pin_36, mbtk_pin_37, mbtk_pin_38, mbtk_pin_39, mbtk_pin_40,
	mbtk_pin_41, mbtk_pin_42, mbtk_pin_43, mbtk_pin_44, mbtk_pin_45, mbtk_pin_46, mbtk_pin_47, mbtk_pin_48,
	mbtk_pin_49, mbtk_pin_50, mbtk_pin_51, mbtk_pin_52, mbtk_pin_53, mbtk_pin_54, mbtk_pin_55, mbtk_pin_56,
	mbtk_pin_57, mbtk_pin_58, mbtk_pin_59, mbtk_pin_60, mbtk_pin_61, mbtk_pin_62, mbtk_pin_63, mbtk_pin_64,
	mbtk_pin_65, mbtk_pin_66, mbtk_pin_67, mbtk_pin_68, mbtk_pin_69, mbtk_pin_70, mbtk_pin_71, mbtk_pin_72,
	mbtk_pin_73, mbtk_pin_74, mbtk_pin_75, mbtk_pin_76, mbtk_pin_77, mbtk_pin_78, mbtk_pin_79, mbtk_pin_80,
	mbtk_pin_81, mbtk_pin_82, mbtk_pin_83, mbtk_pin_84, mbtk_pin_85, mbtk_pin_86, mbtk_pin_87, mbtk_pin_88,
	mbtk_pin_89, mbtk_pin_90, mbtk_pin_91, mbtk_pin_92, mbtk_pin_93, mbtk_pin_94, mbtk_pin_95, mbtk_pin_96,
	mbtk_pin_97, mbtk_pin_98, mbtk_pin_99, mbtk_pin_100, mbtk_pin_101, mbtk_pin_102, mbtk_pin_103, mbtk_pin_104,
	mbtk_pin_105, mbtk_pin_106, mbtk_pin_107, mbtk_pin_108, mbtk_pin_109, mbtk_pin_110, mbtk_pin_111, mbtk_pin_112,
	mbtk_pin_113, mbtk_pin_114, mbtk_pin_115, mbtk_pin_116, mbtk_pin_117, mbtk_pin_118, mbtk_pin_119, mbtk_pin_120,
	mbtk_pin_121, mbtk_pin_122, mbtk_pin_123, mbtk_pin_124, mbtk_pin_125, mbtk_pin_126, mbtk_pin_127,
	mbtk_pin_128, mbtk_pin_129, mbtk_pin_130, mbtk_pin_131, mbtk_pin_132, mbtk_pin_133, mbtk_pin_134, mbtk_pin_135,

	mbtk_pin_max_amout
	
}mbtk_pin_num_enum;

typedef enum 
{
	mbtk_gpio_not_assigned = -1,
 	mbtk_gpio_0=0,mbtk_gpio_1,  mbtk_gpio_2,  mbtk_gpio_3,  mbtk_gpio_4,  mbtk_gpio_5,  mbtk_gpio_6,  mbtk_gpio_7,
 	mbtk_gpio_8,  mbtk_gpio_9,  mbtk_gpio_10, mbtk_gpio_11, mbtk_gpio_12, mbtk_gpio_13, mbtk_gpio_14, mbtk_gpio_15,
 	mbtk_gpio_16, mbtk_gpio_17, mbtk_gpio_18, mbtk_gpio_19, mbtk_gpio_20, mbtk_gpio_21, mbtk_gpio_22, mbtk_gpio_23,
 	mbtk_gpio_24, mbtk_gpio_25, mbtk_gpio_26, mbtk_gpio_27, mbtk_gpio_28, mbtk_gpio_29, mbtk_gpio_30, mbtk_gpio_31,
 	mbtk_gpio_32, mbtk_gpio_33, mbtk_gpio_34, mbtk_gpio_35, mbtk_gpio_36, mbtk_gpio_37, mbtk_gpio_38, mbtk_gpio_39,
 	mbtk_gpio_40, mbtk_gpio_41, mbtk_gpio_42, mbtk_gpio_43, mbtk_gpio_44, mbtk_gpio_45, mbtk_gpio_46, mbtk_gpio_47,
 	mbtk_gpio_48, mbtk_gpio_49, mbtk_gpio_50, mbtk_gpio_51, mbtk_gpio_52, mbtk_gpio_53, mbtk_gpio_54, mbtk_gpio_55,
 	mbtk_gpio_56, mbtk_gpio_57, mbtk_gpio_58, mbtk_gpio_59, mbtk_gpio_60, mbtk_gpio_61, mbtk_gpio_62, mbtk_gpio_63,
	mbtk_gpio_64, mbtk_gpio_65, mbtk_gpio_66, mbtk_gpio_67, mbtk_gpio_68, mbtk_gpio_69, mbtk_gpio_70, mbtk_gpio_71,
	mbtk_gpio_72, mbtk_gpio_73, mbtk_gpio_74, mbtk_gpio_75, mbtk_gpio_76, mbtk_gpio_77, mbtk_gpio_78, mbtk_gpio_79,
	mbtk_gpio_80, mbtk_gpio_81, mbtk_gpio_82, mbtk_gpio_83, mbtk_gpio_84, mbtk_gpio_85, mbtk_gpio_86, mbtk_gpio_87,
	mbtk_gpio_88, mbtk_gpio_89, mbtk_gpio_90, mbtk_gpio_91, mbtk_gpio_92, mbtk_gpio_93, mbtk_gpio_94, mbtk_gpio_95,
	mbtk_gpio_96, mbtk_gpio_97, mbtk_gpio_98, mbtk_gpio_99, mbtk_gpio_100, mbtk_gpio_101, mbtk_gpio_102, mbtk_gpio_103,
	mbtk_gpio_104, mbtk_gpio_105, mbtk_gpio_106, mbtk_gpio_107, mbtk_gpio_108, mbtk_gpio_109, mbtk_gpio_110, mbtk_gpio_111,
	mbtk_gpio_112, mbtk_gpio_113, mbtk_gpio_114, mbtk_gpio_115, mbtk_gpio_116, mbtk_gpio_117, mbtk_gpio_118, mbtk_gpio_119,
	mbtk_gpio_120, mbtk_gpio_121, mbtk_gpio_122, mbtk_gpio_123, mbtk_gpio_124, mbtk_gpio_125, mbtk_gpio_126, mbtk_gpio_127,
 	mbtk_gpio_max_amount_of_pins
}mbtk_gpio_num_enum;


typedef enum 
{
    MBTK_OK  = 0,
	MBTK_ERROR_PARA1 = -1,
	MBTK_ERROR_PARA2 =  -2,
	MBTK_ERROR_PARA3 = -3,
	MBTK_ERROR_PLATFORM_NOT_SUPPORT = -4,
	MBTk_ERROR_UNDFINED_PIN = -5,
    MBTK_ERROR_PROJECT_NO_SUPPORT = -6,
    MBTK_ERROR_UNKNOWN = -7
}MBTK_RETURN_PARA;


// enum and struct dec

typedef void (*mbtk_gpio_isr_callback)(void);


typedef enum 
{
	mbtk_gpio_config_maf0=0,
	mbtk_gpio_config_maf1,
	mbtk_gpio_config_maf2,
	mbtk_gpio_config_maf3,
	mbtk_gpio_config_maf4,
	mbtk_gpio_config_maf5,
	mbtk_gpio_config_maf6,
	mbtk_gpio_config_maf7
}mbtk_gpio_config_af_enum;


typedef enum 
{
	mbtk_gpio_config_pull_none,
	mbtk_gpio_config_pull_low,
	mbtk_gpio_config_pull_high,
	mbtk_gpio_config_pull_both
}mbtk_gpio_config_pull_enum;


typedef enum 
{
	mbtk_gpio_config_sleep_none,
	mbtk_gpio_config_sleep_dir,   // not use usual
	mbtk_gpio_config_sleep_data,  // not use usual
	mbtk_gpio_config_sleep_float, // not use usual
	mbtk_gpio_config_sleep_out_high,
	mbtk_gpio_config_sleep_out_low
}mbtk_gpio_config_sleep_enum;


typedef enum 
{
	mbtk_gpio_config_edge_none,
	mbtk_gpio_config_edge_rise,
	mbtk_gpio_config_edge_fall,
	mbtk_gpio_config_edge_both
}mbtk_gpio_config_edge_enum;


typedef struct 
{
	mbtk_gpio_config_af_enum gpio_af_num;
	mbtk_gpio_config_pull_enum gpio_pull;
	mbtk_gpio_config_sleep_enum gpio_sleep;
	mbtk_gpio_config_edge_enum gpio_edge;
}mbtk_pin_config_struct;


typedef enum
{
	mbtk_gpio_dir_input,
	mbtk_gpio_dir_output
}mbtk_pin_dir_enum;


typedef enum 
{
	mbtk_gpio_pulldown_disable,
	mbtk_gpio_pull_enable,
	mbtk_gpio_down_enable
}mbtk_pin_pulldown_enum;


typedef enum 
{
	mbtk_gpio_level_low,
	mbtk_gpio_level_high
}mbtk_pin_level_enum;


typedef enum 
{
	mbtk_gpio_no_detection,
	mbtk_gpio_rising_edge,
	mbtk_gpio_falling_edge,
	mbtk_gpio_both_edge
}mbtk_pin_edge_enum;



typedef struct 
{
	mbtk_pin_num_enum mbtk_pin_num;
	mbtk_gpio_num_enum mbtk_gpio_num;
	int mbtk_gpio_mfpr_num;
}mbtk_pin_map_struct;



typedef enum 
{
  mbtk_adc_1 = 0xd1, //need larger then "mbtk_pin_max_amout"
  mbtk_adc_2 = 0xd2,
  mbtk_adc_3 = 0xd3,
  mbtk_adc_RTP = 0xd6, //need larger then "mbtk_pin_max_amout"
  mbtk_adc_RTN = 0xd7,
}mbtk_adc_num_enum;

typedef enum 
{
  mbtk_ldo_1 = 0xF1, //need larger then "mbtk_pin_max_amout"
  mbtk_ldo_2 = 0xF2,
  mbtk_ldo_3 = 0xF3,
  mbtk_ldo_4 = 0xF4,
  mbtk_ldo_5 = 0xF5,
  mbtk_ldo_6 = 0xF6,  
  mbtk_ldo_7 = 0xF7,
  mbtk_ldo_8 = 0xF8,
  mbtk_ldo_max = 0xFF  
}mbtk_ldo_num_enum;

#define MBTK_FUNCTION_PIN_NOT_USED 0xFF

typedef enum 
{
    MBTK_STATUS_PIN = 0,
	MBTK_NET_STATUS_LED_PIN,
	MBTK_NET_MODE_LED_PIN,
	MBTK_WAKEUP_IN_PIN,
	MBTK_AP_READY_PIN,
	MBTK_FLIGTH_MODE_PIN,
	MBTK_WAKEOUT_PIN,
	MBTK_USIM_DET,
	MBTK_CP_UART_RXD,
	MBTK_CP_UART_TXD,
	MBTK_CP_UART_CTS,
	MBTK_CP_UART_RTS,
	MBTK_CP_UART_DTR,
	MBTK_CP_UART_RI,
	MBTK_CP_UART_DCD,
	MBTK_AP_UART1_TXD,
	MBTK_AP_UART1_RXD,
	MBTK_GPS_RXD_PIN,
	MBTK_GPS_TXD_PIN,
	MBTK_I2C_SDA_PIN,
	MBTK_I2C_SCL_PIN,
	MBTK_LCD_TE_PIN,
	MBTK_LCD_CS_PIN,
	MBTK_LCD_SPI_RS,
	MBTK_LCD_SPI_RST,
	MBTK_LCD_SPI_DOUT,
	MBTK_LCD_SPI_CLK,
	MBTK_LCD_LCD_VDDIO,
	MBTK_CAM_I2C_SCL,
	MBTK_CAM_I2C_SDA,
	MBTK_CAM_SPI_MCLK,
	MBTK_CAM_SPI_CLK,
	MBTK_CAM_SPI_DATA0,
	MBTK_CAM_SPI_DATA1,
	MBTK_CAM_PWDN1,
	MBTK_CAM_VDD,
	MBTK_PCM_SYNC,
	MBTK_PCM_RXD,
	MBTK_PCM_TXD,
	MBTK_PCM_CLK,
	MBTK_GPS_UART_RXD,
	MBTK_GPS_UART_TXD,
	MBTK_GPS_RST,
	MBTK_GPS_SLEEP_EN,
	MBTK_HOST_WAKE_GPS,
	MBTK_GPS_WAKE_HOST,
	MBTK_GPS_32K,
	MBTK_GPS_BLINK,
	MBTK_GPS_LNA_EN,
	MBTK_AUDIO_PA_EN,
	MBTk_SPI_CLK,
	MBTK_SPI_DOUT,
	MBTK_SPI_DIN,
	MBTK_SPI_CS,
	MBTK_GPIO_PIN_1,
	MBTK_GPIO_PIN_2,
	
	MBTK_MAX_GPIO_FUNC_PIN,   //PLEASE ADD GPIO DEFINE ON ABOVER
	MBTK_ADC1_PIN,
	MBTK_ADC2_PIN,
	MBTK_ADC3_PIN,
	MBTK_MAX_FUNC_PIN
}mbtk_project_function_pin_enum;

// mbtk_gpio_apis

int mbtk_pin_config(mbtk_pin_num_enum pin_num, mbtk_pin_config_struct *config);

int mbtk_set_pin_dir(mbtk_pin_num_enum pin_num, mbtk_pin_dir_enum dir);

int mbtk_get_pin_dir(mbtk_pin_num_enum pin_num, mbtk_pin_dir_enum *dir);

int mbtk_set_pin_level(mbtk_pin_num_enum pin_num, mbtk_pin_level_enum level);

int mbtk_get_pin_level(mbtk_pin_num_enum pin_num, mbtk_pin_level_enum *level);

int mbtk_set_pin_pull(mbtk_pin_num_enum pin_num, mbtk_pin_pulldown_enum pull);

int mbtk_enable_pin_edge_detect(mbtk_pin_num_enum pin_num, mbtk_pin_edge_enum edge);

int mbtk_diable_pin_edge_detect(mbtk_pin_num_enum pin_num, mbtk_pin_edge_enum edge);

int mbtk_pin_bind_irq_callback(mbtk_pin_num_enum pin_num, mbtk_gpio_isr_callback callbackfunc);

int mbtk_pin_bind_wakeup_callback(mbtk_pin_num_enum pin_num, mbtk_gpio_isr_callback callbackfunc);

int mbtk_enable_pin_wakeup_edge_detect(mbtk_pin_num_enum pin_num, mbtk_gpio_config_edge_enum edge);

int mbtk_diable_pin_wakeup_edge_detect(mbtk_pin_num_enum pin_num, mbtk_gpio_config_edge_enum edge);

int mbtk_pin_debind_irq_callbcak(mbtk_pin_num_enum pin_num);

int mbtk_pin_debind_wakeup_callback(mbtk_pin_num_enum pin_num);

extern void RTI_LOG(const char* fmt, ...);


#endif // #findef __MBTK_GPIO_H
