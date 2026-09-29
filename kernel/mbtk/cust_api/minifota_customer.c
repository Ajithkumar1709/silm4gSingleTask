/*******************************************************************************
 * Copyright (c) mbtk Corp.
 *
 *******************************************************************************/


/*********************
 *      INCLUDES
 *********************/

#include "mbtk_pub_type.h"
#include "stdio.h"
#include "mbtk_gpio.h"
#include "mbtk_uart.h"

//#ifdef MBTK_MINIFOTA_OUTPUT


typedef enum {
	MINIF_STEP_NONE,
	MINIF_STEP_1,    //差分包下载阶段
	MINIF_STEP_2       //整包下载阶段
}MINI_STEPS;


typedef enum {
	FOTA_SUCCESS=0,
	FOTA_DOWNLOADING=50,
	FOTA_COMPLETED=100,
	FOTA_DOMAIN_NOT_EXIST=1001,
	FOTA_DOMAIN_TIMEOUT,
	FOTA_DOMAIN_UNKNOWN,
	FOTA_AUTH_FAILED,
	FOTA_FILE_NOT_EXIST,
	FOTA_FILE_SIZE_INVALID,
	FOTA_FILE_GET_ERR,
	FOTA_FILE_CHECK_ERR,
	FOTA_INTERNAL_ERR,
	FOTA_FILE_SIZE_TOO_LARGE,
	FOTA_SET_FLAG_FAILED,
	FOTA_PARAM_SIZE_INVALID,
	FOTA_NO_ENOUGH_MEMORY,
	FOTA_ENTRY_MINISYS_ERROR
}FOTA_ERROR_CODE;


typedef enum
{
	MBTK_MINIFOTA_START,
	MBTK_MINIFOTA_CONNECTING,
	MBTK_MINIFOTA_DOWNLOADING,
	MBTK_MINIFOTA_DOWNLOAD_DONE,
	MBTK_MINIFOTA_ERROR,
	MBTK_MINIFOTA_RESET
}FOTA_STATUS;	

#define MBTK_MINI_BUFFER_SIZE 100
/*****************************************************************************
 *
 * FUNCTIO 
 *		mbtk_minifota_buffer_hook
 * DESCRIPTION 
 *  	用于生成minifota输出的buffer，需要malloc出来，打印完后会在库中进行释放
 * PARAMETERS 
 *    void
 * RETURN VALUES
 *		创建的字符指针
 *
 *****************************************************************************/
char *mbtk_minifota_buffer_hook(void)
{
	char *buffer = NULL;

	buffer = malloc(MBTK_MINI_BUFFER_SIZE);

	return buffer;
}

/*****************************************************************************
 *
 * FUNCTIO 
 *		mbtk_minifota_urc_hook
 * DESCRIPTION 
 *  	用于生成minifota输出的buffer内容，
 * PARAMETERS 
 *    buffer 输出串口的buffer内容，由mbtk_minifota_buffer_hook生成
 *    mini_steps :  对应MINI_STEPS
 *    fota_status : 对应FOTA_STATUS
      value       : -1 表示此参数目前无效
                    fota_status 为MBTK_MINIFOTA_CONNECTING 时，为下载进度百分比
                                为MBTK_MINIFOTA_DOWNLOAD_DONE 时，为FOTA_ERROR_CODE
                                为MBTK_MINIFOTA_ERROR 时，为FOTA_ERROR_CODE
 *
 * RETURN VALUES
 *		创建的字符指针
 *
 *****************************************************************************/
int mbtk_minifota_urc_hook(char *buffer, int mini_steps, int fota_status, int value)
{	
	int length = 0;
	
	if(value!=-1)
		length = sprintf(buffer,"+MFOTA:%d,%d,%d\r\n", mini_steps, fota_status, value);
	else
		length = sprintf(buffer,"+MFOTA:%d,%d\r\n", mini_steps, fota_status);

	return length;
}


/*****************************************************************************
 *
 * FUNCTIO 
 *		mbtk_minifota_open_uart
 * DESCRIPTION 
 *  	打开用于输出的串口
 * PARAMETERS 
 *    void
 * RETURN VALUES
 *		使用的串口号
 *
 *****************************************************************************/
int mbtk_minifota_open_uart(void)
{
	unsigned int data;
	mbtk_pin_config_struct config;
    #define UART_TX	mbtk_pin_17
    #define UART_RX mbtk_pin_18


	
  config.gpio_af_num = mbtk_gpio_config_maf1;
  config.gpio_pull = mbtk_gpio_config_pull_high;
  config.gpio_sleep = mbtk_gpio_config_sleep_none;
  config.gpio_edge = mbtk_gpio_config_edge_none;
    
  if (mbtk_pin_config(UART_TX, &config) != 0)
  {
    mbtk_app_log("gpio_demo_output : mbtk_pin_config fail \n");
    return -1;
  }

  if (mbtk_pin_config(UART_RX, &config) != 0)
  {
    mbtk_app_log("gpio_demo_output : mbtk_pin_config fail \n");
    return -1;
  }

	ol_Uart_Open(OL_UART_PORT_STUART);

	return OL_UART_PORT_STUART;
}

//#endif
