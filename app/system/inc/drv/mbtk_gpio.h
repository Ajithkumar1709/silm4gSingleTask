#ifndef __MBTK_GPIO_H
#define __MBTK_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#define MBTK_GPIO_ERR -1
#define MBTK_GPIO_OK   0

#define MBTK_GPIO_HISR_PRIORITY_HIGH 0
#define MBTK_GPIO_HISR_PRIORITY_MID  1
#define MBTK_GPIO_HISR_PRIORITY_LOW  2

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
	mbtk_pin_121, mbtk_pin_122, mbtk_pin_123, mbtk_pin_124, mbtk_pin_125, mbtk_pin_126, mbtk_pin_127, mbtk_pin_128,
	mbtk_pin_129,mbtk_pin_130, mbtk_pin_131,mbtk_pin_132,mbtk_pin_133,mbtk_pin_134,mbtk_pin_135,
	mbtk_pin_max_amout
	
}mbtk_pin_num_enum;


typedef void (*mbtk_gpio_isr_callback)(void);



typedef enum 
{
	mbtk_gpio_config_maf0,
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
	mbtk_gpio_config_pull_float,
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




/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_pin_config
 * DESCRIPTION 
 *  	This API is used to config pin function.  
 * PARAMETERS 
 *		pin_num		[IN]:pin_num
 *		config   	[IN]:A pointer type variable that points to the config function for pin_num
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_pin_config(mbtk_pin_num_enum pin_num, mbtk_pin_config_struct *config);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_set_pin_dir
 * DESCRIPTION 
 *  	This API is used to set pin direction.  
 * PARAMETERS 
 *		pin_num		[IN]:pin_num
 *		dir     	[IN]:pin direction
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_set_pin_dir(mbtk_pin_num_enum pin_num, mbtk_pin_dir_enum dir);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_pin_dir
 * DESCRIPTION 
 *  	This API is used to get pin direction.  
 * PARAMETERS 
 *		pin_num		[IN]:pin_num
 *		dir     	[IN]:A pointer type variable that points to the direction for pin
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_get_pin_dir(mbtk_pin_num_enum pin_num, mbtk_pin_dir_enum *dir);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_set_pin_level
 * DESCRIPTION 
 *  	This API is used to set pin output level.  
 * PARAMETERS 
 *		pin_num		[IN]:pin_num
 *		level     	[IN]:pin output level
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_set_pin_level(mbtk_pin_num_enum pin_num, mbtk_pin_level_enum level);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_pin_dir
 * DESCRIPTION 
 *  	This API is used to get pin input level.  
 * PARAMETERS 
 *		pin_num		[IN]:pin_num
 *		level     	[IN]:pin input level
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_get_pin_level(mbtk_pin_num_enum pin_num, mbtk_pin_level_enum *level);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_set_pin_pull
 * DESCRIPTION 
 *  	This API is used to set pin internal pulldown.  
 * PARAMETERS 
 *		pin_num		[IN]:pin_num
 *		pull     	[IN]:pin internal pulldown
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_set_pin_pull(mbtk_pin_num_enum pin_num, mbtk_pin_pulldown_enum pull);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_enable_pin_edge_detect
 * DESCRIPTION 
 *  	This API is used to eanble pin IRQ edge detect  
 * PARAMETERS 
 *		pin_num		[IN]:pin_num
 *		edge     	[IN]:pin detect edge
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_enable_pin_edge_detect(mbtk_pin_num_enum pin_num, mbtk_pin_edge_enum edge);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_disable_pin_edge_detect
 * DESCRIPTION 
 *  	This API is used to disable pin IRQ edge detect  
 * PARAMETERS 
 *		pin_num		[IN]:pin_num
 *		edge     	[IN]:pin detect edge
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_disable_pin_edge_detect(mbtk_pin_num_enum pin_num, mbtk_pin_edge_enum edge);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_bind_pin_irq_callback
 * DESCRIPTION 
 *  	This API is used to bind pin IRQ callback  
 * PARAMETERS 
 *		pin_num		    [IN]:pin_num
 *		callbackfunc    [IN]:A pointer type variable that points to IRQ callback function
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_bind_pin_irq_callback(mbtk_pin_num_enum pin_num, mbtk_gpio_isr_callback callbackfunc);
extern int ol_bind_pin_irq_callback_ex(mbtk_pin_num_enum pin_num, mbtk_gpio_isr_callback callbackfunc, int debounce_time);



/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_pin_bind_wakeup_callback
 * DESCRIPTION 
 *  	This API is used to bind pin wakeup callback, can not exist IRQ callback at same time  
 * PARAMETERS 
 *		pin_num		    [IN]:pin_num
 *		callbackfunc    [IN]:A pointer type variable that points to wakeup callback function
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_pin_bind_wakeup_callback(unsigned char pin_num, mbtk_gpio_isr_callback callbackfunc);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_enable_pin_wakeup_edge_detect
 * DESCRIPTION 
 *  	This API is used to enable pin wakup edge detect  
 * PARAMETERS 
 *		pin_num		[IN]:pin_num
 *		edge     	[IN]:pin wakeup detect edge
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_enable_pin_wakeup_edge_detect(unsigned char pin_num, unsigned char edge);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_diable_pin_wakeup_edge_detect
 * DESCRIPTION 
 *  	This API is used to disable pin wakup edge detect  
 * PARAMETERS 
 *		pin_num		[IN]:pin_num
 *		edge     	[IN]:pin wakeup detect edge
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_diable_pin_wakeup_edge_detect(unsigned char pin_num, unsigned char edge);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_pin_debind_irq_callbcak
 * DESCRIPTION 
 *  	This API is used to remove bind pin IRQ callback  
 * PARAMETERS 
 *		pin_num		    [IN]:pin_num
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_pin_debind_irq_callbcak(unsigned char pin_num);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_pin_debind_wakeup_callback
 * DESCRIPTION 
 *  	This API is used to remove bind pin wakeup callback  
 * PARAMETERS 
 *		pin_num		    [IN]:pin_num
 * RETURN VALUES
 *		MBTK_GPIO_OK    : Interface executed successfully
 *		MBTK_GPIO_ERR   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_pin_debind_wakeup_callback(unsigned char pin_num);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_pin_get_ver
 * DESCRIPTION 
 *  	This API is used to get pin API version
 * PARAMETERS 
 *		NONE
 * RETURN VALUES
 *		pin API version string
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern unsigned char *ol_pin_get_ver(void);

#ifdef __cplusplus
}
#endif

#endif // #findef __MBTK_GPIO_H

