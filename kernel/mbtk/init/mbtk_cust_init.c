
#include "mbtk_pub_type.h"
//#include "mbtk_os.h"
#include "mbtk_gpio.h"
#include "mbtk_uart.h"


void mbtk_cust_cinit1_init(void)
{
	//这里添加cinit1阶段需要执行操作
	//系统分区资源初始化阶段


}


void mbtk_cust_cinit2_init(void)
{
	//这里添加客户cinit2阶段初始化代码
	//os初始化阶段，还未完成

	

}



void mbtk_cust_task_init(void)
{
	//os初始化已完成，task建立阶段
	//这里添加客户task的初始化代码


}

#ifdef MBTK_PYTHON_SUPPORT
#ifdef MBTK_PRODUCT_BSP_L509_13
#define UART_TX mbtk_pin_67
#define UART_RX mbtk_pin_68
#else
#define UART_TX mbtk_pin_17
#define UART_RX mbtk_pin_18
#endif

 //python 所使用的串口，传入值是所需要的串口号，请根据具体项目或者需要修改，目前只写了ST口做为
 //console的情况
int mbtk_console_uart_init(int port_num)
{

  mbtk_pin_config_struct config;

  if(port_num == OL_UART_PORT_STUART){
	  config.gpio_af_num = mbtk_gpio_config_maf1;
	  config.gpio_pull = mbtk_gpio_config_pull_high;
	  config.gpio_sleep = mbtk_gpio_config_sleep_none;
	  config.gpio_edge = mbtk_gpio_config_edge_none;
   }

  
  if (mbtk_pin_config(UART_TX, &config) != 0){
   mbtk_app_log("gpio_demo_output : mbtk_pin_config fail \n");
   return -1;
  }
  if (mbtk_pin_config(UART_RX, &config) != 0){
   mbtk_app_log("gpio_demo_output : mbtk_pin_config fail \n");
   return -1;
  }
 
}


#endif



void mbtk_uart_open_hook(int port_num)
{
#ifdef MBTK_PYTHON_SUPPORT

  mbtk_pin_config_struct config;

  if(port_num == OL_UART_PORT_STUART){
	  config.gpio_af_num = mbtk_gpio_config_maf1;
	  config.gpio_pull = mbtk_gpio_config_pull_high;
	  config.gpio_sleep = mbtk_gpio_config_sleep_none;
	  config.gpio_edge = mbtk_gpio_config_edge_none;
   }
  
  if (mbtk_pin_config(UART_TX, &config) != 0){
   mbtk_app_log("gpio_demo_output : mbtk_pin_config fail \n");
   return -1;
  }
  if (mbtk_pin_config(UART_RX, &config) != 0){
   mbtk_app_log("gpio_demo_output : mbtk_pin_config fail \n");
   return -1;
  }
#endif
  
}


#define K_ATI_VER(s) K_ATI_VER_STR(s)
#define K_ATI_VER_STR(s) #s

char *mbtk_get_ati_ver_str(void)
{
	return K_ATI_VER(CUSTOMER_VERSION);
}
