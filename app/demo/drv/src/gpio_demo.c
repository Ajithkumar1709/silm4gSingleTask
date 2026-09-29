
#include "mbtk_gpio.h"
#include "mbtk_api.h"
#include "mbtk_comm_api.h"
#include "menu_demo_api.h"


extern void ol_autosleep_enable(unsigned char mode);


int gpio_demo_output(void);
int gpio_demo_input(void);
int gpio_demo_isr_mode(void);
int gpio_demo_pin_wakeup(void);
int gpio_demo_pwm_output(void);


static demo_menu_info menu_info[] =
{
	{"output","[pin]",gpio_demo_output,NULL},
	{"input","[pin]",gpio_demo_input,NULL},
	{"interrupt","[pin]",gpio_demo_isr_mode,NULL},
  {"wakeup","[pin]",gpio_demo_pin_wakeup,NULL},
  {"pwm","[pin]",gpio_demo_pwm_output,NULL},	
};

demo_menu_info *gpio_demo_menu_info(unsigned int *num)
{
	*num = sizeof(menu_info)/sizeof(menu_info[0]);
	return menu_info;
}

#define demo_default_pin mbtk_pin_3
unsigned int demo_interrupt_pin = 0;
unsigned int demo_wakeup_pin = 0;
mbtk_hisrref demo_interrupt_hisr;
mbtk_hisrref demo_wakeup_hisr;

void gpio_demo_isr_callback(void)
{
    ol_disable_pin_edge_detect(demo_interrupt_pin, mbtk_gpio_config_edge_both);
    ol_os_active_hisr(&demo_interrupt_hisr);
}

void gpio_demo_hisr_func(void)
{
		int lev = 0;
		ol_get_pin_level(demo_interrupt_pin, &lev);
    op_uart_printf("gpio_demo_hisr_func enter %d\n", lev);
    ol_enable_pin_edge_detect(demo_interrupt_pin, mbtk_gpio_config_edge_both);
}

void gpio_demo_isr_wakeup_callback(void)
{
    ol_diable_pin_wakeup_edge_detect(demo_wakeup_pin, mbtk_gpio_config_edge_both);
    //ol_disable_pin_edge_detect(demo_wakeup_pin, mbtk_gpio_config_edge_both);
    ol_os_active_hisr(&demo_wakeup_hisr);
}

void gpio_demo_hisr_wakeup_func(void)
{
		op_uart_printf("gpio_demo_hisr_wakeup_func enter\n");
    ol_enable_pin_wakeup_edge_detect(demo_wakeup_pin, mbtk_gpio_config_edge_both);
		ol_autosleep_enable(0);
    //ol_enable_pin_edge_detect(demo_wakeup_pin, mbtk_gpio_config_edge_both);
}


int gpio_demo_output(void)
{
    uint8_t dir = 0;
		unsigned int pin_num = 0;
    mbtk_pin_config_struct config;
    config.gpio_af_num = mbtk_gpio_config_maf0;
    config.gpio_pull = mbtk_gpio_config_pull_low;
    config.gpio_sleep = mbtk_gpio_config_sleep_none;
    config.gpio_edge = mbtk_gpio_config_edge_none;

		DEMO_MEUN_GET_INT_PARAM(0,&pin_num, 0,256,demo_default_pin);
    op_uart_printf("gpio_demo_output run,pin_num = %d\n",pin_num);
		pin_num--;//remap to mbtk_pin
    if (ol_pin_config(pin_num, &config) != 0)
    {
        op_uart_printf("gpio_demo_output : mbtk_pin_config fail \n");
        return -1;
    }

    if (ol_set_pin_dir(pin_num, mbtk_gpio_dir_output) != 0)
    {
        op_uart_printf("gpio_demo_output : mbtk_set_pin_dir_input fail \n");
        return -1;
    }

    if (ol_get_pin_dir(pin_num, &dir) != 0)
    {
        op_uart_printf("mbkt_gpio_demo : mbtk_get_pin_dir fail \n");
        return -1;
    }

    op_uart_printf("gpio_demo_output : mbtk_get_pin_dir = %d \n", dir);
    if (ol_set_pin_level(pin_num, mbtk_gpio_level_high) != 0)
    {
        op_uart_printf("gpio_demo_output : mbtk_set_pin_level fail \n");
        return -1;
    }
    op_uart_printf("check demo_pin level is high\n");
    return 0;
}

int gpio_demo_input(void)
{
    uint8_t dir = 0;
		unsigned int pin_num = 0;
    mbtk_pin_config_struct config;
    config.gpio_af_num = mbtk_gpio_config_maf0;
    config.gpio_pull = mbtk_gpio_config_pull_low;
    config.gpio_sleep = mbtk_gpio_config_sleep_none;
    config.gpio_edge = mbtk_gpio_config_edge_none;

		DEMO_MEUN_GET_INT_PARAM(0,&pin_num, 0,256,demo_default_pin);
    op_uart_printf("gpio_demo_input run,pin_num = %d\n",pin_num);
		pin_num--;//remap to mbtk_pin
    if (ol_pin_config(pin_num, &config) != 0)
    {
        op_uart_printf("gpio_demo_input : mbtk_pin_config fail \n");
        return -1;
    }

    if (ol_set_pin_dir(pin_num, mbtk_gpio_dir_input) != 0)
    {
        op_uart_printf("gpio_demo_input : mbtk_gpio_dir_input fail \n");
        return -1;
    }


    if (ol_get_pin_dir(pin_num, &dir) != 0)
    {
        op_uart_printf("gpio_demo_input : mbtk_get_pin_dir fail \n");
        return -1;
    }

    op_uart_printf("gpio_demo_input : mbtk_get_pin_dir = %d \n", dir);
    return 0;
}

int gpio_demo_isr_mode(void)
{
    uint8_t dir = 0;
		unsigned int pin_num = 0;
    mbtk_pin_config_struct config;
    config.gpio_af_num = mbtk_gpio_config_maf0;
    config.gpio_pull = mbtk_gpio_config_pull_low;
    config.gpio_sleep = mbtk_gpio_config_sleep_none;
    config.gpio_edge = mbtk_gpio_config_edge_none;

		DEMO_MEUN_GET_INT_PARAM(0,&pin_num, 0,256,demo_default_pin);
    op_uart_printf("gpio_demo_isr_mode run,pin_num = %d\n",pin_num);
		pin_num--;//remap to mbtk_pin
		demo_interrupt_pin = pin_num;
    if (ol_pin_config(pin_num, &config) != 0)
    {
        op_uart_printf("gpio_demo_isr_mode : mbtk_pin_config fail \n");
        return -1;
    }

    if (ol_set_pin_dir(pin_num, mbtk_gpio_dir_input) != 0)
    {
        op_uart_printf("gpio_demo_isr_mode : mbtk_gpio_dir_input fail \n");
        return -1;
    }

    if (ol_get_pin_dir(pin_num, &dir) != 0)
    {
        op_uart_printf("gpio_demo_isr_mode : mbtk_get_pin_dir fail \n");
        return -1;
    }

    ol_os_creat_hisr(&demo_interrupt_hisr, "gpio_demo_hisr", gpio_demo_hisr_func, MBTK_GPIO_HISR_PRIORITY_HIGH);
    if (ol_enable_pin_edge_detect(pin_num, mbtk_gpio_rising_edge) != 0)
    {
        op_uart_printf("gpio_demo_isr_mode : mbtk_enable_pin_edge_detect fail \n");
        return -1;
    }

    if (ol_bind_pin_irq_callback(pin_num, gpio_demo_isr_callback) != 0)
    {
        op_uart_printf("gpio_demo_isr_mode : mbtk_pin_bind_irq_callback fail \n");
        return -1;
    }

		op_uart_printf("enable system auto sleep");
		ol_autosleep_enable(1);

    op_uart_printf("gpio_demo_isr_mode : test gpio hisr func \n");
    return 0;
}


int gpio_demo_pin_wakeup(void)
{
		unsigned int pin_num = 0;
    mbtk_pin_config_struct config;
    config.gpio_af_num = mbtk_gpio_config_maf0;
    config.gpio_pull = mbtk_gpio_config_pull_low;
    config.gpio_sleep = mbtk_gpio_config_sleep_none;
    config.gpio_edge = mbtk_gpio_config_edge_both;

		DEMO_MEUN_GET_INT_PARAM(0,&pin_num, 0,256,demo_default_pin);
		op_uart_printf("gpio_demo_pin_wakeup run,pin_num = %d\n",pin_num);
		pin_num--;//remap to mbtk_pin
		demo_wakeup_pin = pin_num;
    if(ol_pin_config(pin_num, &config) != 0)
    {
        op_uart_printf("config_demo_pin_wakeup : mbtk_pin_config fail \n");
        return -1;
    }

    if(ol_set_pin_dir(pin_num, mbtk_gpio_dir_input) != 0)
    {
        op_uart_printf("config_demo_pin_wakeup : mbtk_gpio_dir_input fail \n");
        return -1;
    }

    ol_os_creat_hisr(&demo_wakeup_hisr, "gpio_demo_hisr_wakeup", gpio_demo_hisr_wakeup_func, MBTK_GPIO_HISR_PRIORITY_HIGH);
    if(ol_pin_bind_wakeup_callback(pin_num, gpio_demo_isr_wakeup_callback) != 0)
    {
        op_uart_printf("config_demo_pin_wakeup : ol_pin_bind_wakeup_callback fail \n");
        return -1;
    }

    if(ol_enable_pin_wakeup_edge_detect(pin_num, mbtk_gpio_config_edge_both) != 0)
    {
        op_uart_printf("config_demo_pin_wakeup : ol_enable_pin_wakeup_edge_detect fail \n");
        return -1;
    }

		op_uart_printf("enable system auto sleep");
		ol_autosleep_enable(1);

    op_uart_printf("config_demo_pin_wakeup : config_demo_pin_wakeup end \n");
    return 0;
}

int gpio_demo_pwm_output(void)
{
		unsigned int pin_num = 0;
    mbtk_pin_config_struct config;
    config.gpio_af_num = mbtk_gpio_config_maf2;
    config.gpio_pull = mbtk_gpio_config_pull_none;
    config.gpio_sleep = mbtk_gpio_config_sleep_none;
    config.gpio_edge = mbtk_gpio_config_edge_none;

		DEMO_MEUN_GET_INT_PARAM(0,&pin_num, 0,256,demo_default_pin);
		op_uart_printf("gpio_demo_pin_wakeup run,pin_num = %d\n",pin_num);
		pin_num--;//remap to mbtk_pin

		if (ol_pin_config(pin_num, &config) != 0)
    {
        op_uart_printf("gpio_demo_input : mbtk_pin_config fail \n");
        return -1;
    }

    if (ol_set_pin_dir(pin_num, mbtk_gpio_dir_output) != 0)
    {
        op_uart_printf("gpio_demo_input : mbtk_gpio_dir_input fail \n");
        return -1;
    }

		ol_pwm_enable_ex(mbtk_pwm_no_0,50,1000);
}
