#include "backlight_drv.h"
//#include "Gpio_api.h"
#include "mfpr_api.h"

#ifndef CRANE_MCU_DONGLE
#include "pmic_api.h"
#endif
#define HAL_GPIO_69 69

#define BACKLIGHT_GPIO HAL_GPIO_69

#define HAL_GPIO_123 123
#define HAL_GPIO_126 126
#define CRANEM_BACKLIGHT_GPIO123 HAL_GPIO_123
#define CRANEM_BACKLIGHT_GPIO126 HAL_GPIO_126

uint8_t g_backlight_status = BACKLIGHT_STATUS_MAX ;
uint8_t g_backlight_brightness = 0xFF;

typedef struct 
{
	UINT32 reg;
	UINT32 padding[2];
}GPIO_Single_Register;


typedef volatile struct
{
	volatile GPIO_Single_Register PLR;//0x0
	volatile GPIO_Single_Register PDR;//0xc
	volatile GPIO_Single_Register PSR;//0X18
	volatile GPIO_Single_Register PCR;//0X24
	volatile GPIO_Single_Register RER;//0X30
	volatile GPIO_Single_Register FER;//0X3C
	volatile GPIO_Single_Register EDR;//0X48
	volatile GPIO_Single_Register SDR;//0X54
	volatile GPIO_Single_Register CDR;//0X60
	volatile GPIO_Single_Register SRER;//0X6C
	volatile GPIO_Single_Register CRER;//0X78
	volatile GPIO_Single_Register SFER;//0X84
	volatile GPIO_Single_Register CFER;//0X90
	volatile GPIO_Single_Register AP_MASK;//0X9C
	volatile GPIO_Single_Register CP_MASK;//0XA8
}GPIORegisters;


#define GPIO_SHIFT(gpio) (1 << (gpio%32))


typedef enum
{
	VSPI_GPIO_0=0,
	VSPI_GPIO_32=32,
	VSPI_GPIO_33=33,
	VSPI_GPIO_34,
	VSPI_GPIO_35,
	VSPI_GPIO_36,
	VSPI_GPIO_64=64,
	VSPI_GPIO_96=96,
	VSPI_GPIO_121=121,
	VSPI_GPIO_MAX=127,
	VSPI_GPIO_NULL=128
}VSpiGpio;

#define GPIO_REGISTER_BASE				0xD4019000
#define GPIO_REGISTER_GROUPS				4

#define GPIO_GROUP_BASE1					0
#define GPIO_GROUP_BASE2					4
#define GPIO_GROUP_BASE3					8
#define GPIO_GROUP_BASE4					0x100

static UINT32 GPIORegisterBase[GPIO_REGISTER_GROUPS] = {	GPIO_GROUP_BASE1,
															GPIO_GROUP_BASE2,
															GPIO_GROUP_BASE3,
															GPIO_GROUP_BASE4};


static UINT32 *GetBaseAddr(UINT32 portHandle)
{
	UINT32 base_addr;
	
	if(portHandle < VSPI_GPIO_32)
		base_addr =  GPIO_REGISTER_BASE + GPIORegisterBase[0];
	else if(portHandle < VSPI_GPIO_64)
		base_addr =  GPIO_REGISTER_BASE + GPIORegisterBase[1];
	else if(portHandle < VSPI_GPIO_96)
		base_addr =  GPIO_REGISTER_BASE + GPIORegisterBase[2];
	else if(portHandle <= VSPI_GPIO_MAX)
		base_addr =  GPIO_REGISTER_BASE + GPIORegisterBase[3];
	else
		base_addr =  0;

	return (UINT32 *)base_addr;
}


void gpio_set_output(unsigned int port)
{
	GPIORegisters *GPIOReg;
	GPIOReg = (GPIORegisters *)GetBaseAddr(port);
	GPIOReg->SDR.reg =	GPIO_SHIFT(port);
}
void gpio_set_value(unsigned int port, int value)
{
	//set high
	GPIORegisters *GPIOReg;
	GPIOReg = (GPIORegisters *)GetBaseAddr(port);
	if(value == 0) {
		GPIOReg->PCR.reg = GPIO_SHIFT(port);
	}
	else {
		GPIOReg->PSR.reg = GPIO_SHIFT(port);
	}
}

#if defined(CONFIG_BOARD_CRANEM_EVB)
extern int pwm_start_work(int port, int period_ns, int duty_ns);

#undef BU_REG_READ
#undef BU_REG_WRITE
#define BU_REG_READ(x) (*(volatile uint32_t *)(x))
#define BU_REG_WRITE(x,y) ((*(volatile uint32_t *)(x)) = (y) )

void craneM_lcd_backlight(uint8_t onoff)
{
	unsigned int vreg;
	vreg = BU_REG_READ(0xd401910c); //gpio_direction_output gpio123
	vreg |= 0x8000000;
	BU_REG_WRITE(0xd401910c, vreg);
	vreg = BU_REG_READ(0xd4019118); // gpio_set_value gpio123
	if(onoff)
		vreg |= 0x8000000;
	else
		vreg &= ~0x8000000;
	BU_REG_WRITE(0xd4019118, vreg);
}

void craneM_lcd_backlight_Ctrl(unsigned int level)
{
	if (level == 5)
		pwm_start_work(0, 50000, 50000);
	else
	 	pwm_start_work(0, 50000, level * 130 * 76);
	//76 =(1*1000*1000*1000) /pwm_source_clk_freq //pwm_source_clk_freq=13mhz
	//204 = 1024 / 5// level:1~5
}
#endif

static void backlight_on(uint8_t brightness)
{
    /*
    * z2 use pm813, check first
    */
    unsigned int value[2];
    if(Pmic_is_pm813()){
        PmicLcdBackLightCtrl(brightness);
    }
    else if (Pmic_is_pm812()){
        if(BACKLIGHT_STATUS_OFF == brightness){
            //gpio_direction_output(BACKLIGHT_GPIO);
            //gpio_set_value(BACKLIGHT_GPIO, 0);
            
			value[0] = MFP_REG(GPIO_77| MFP_AF0 | MFP_DRIVE_MEDIUM | MFP_PULL_LOW & ~MFP_SLEEP_DIR | MFP_LPM_EDGE_NONE);
			value[1] = MFP_EOC;
			mfp_config(value);
			//set output
			gpio_set_output(BACKLIGHT_GPIO);
			gpio_set_value(BACKLIGHT_GPIO,1);

		} else {
            //gpio_direction_output(BACKLIGHT_GPIO);
            //gpio_set_value(BACKLIGHT_GPIO, 1);
            value[0] = MFP_REG(GPIO_77| MFP_AF0 | MFP_DRIVE_MEDIUM | MFP_PULL_LOW & ~MFP_SLEEP_DIR | MFP_LPM_EDGE_NONE);
			value[1] = MFP_EOC;
			mfp_config(value);
			//set output
			gpio_set_output(BACKLIGHT_GPIO);
			gpio_set_value(BACKLIGHT_GPIO,1);
        }
    } else if (PMIC_IS_PM803()) {
#if defined(CONFIG_BOARD_CRANEM_EVB)
#if 0
			value[0] = MFP_REG(GPIO_VCXO_OUT | MFP_AF1 | MFP_DRIVE_MEDIUM | MFP_PULL_LOW & ~MFP_SLEEP_DIR | MFP_LPM_EDGE_NONE);
			value[1] = MFP_REG(GPIO_CLK_REQ | MFP_AF1 | MFP_DRIVE_MEDIUM | MFP_PULL_LOW & ~MFP_SLEEP_DIR | MFP_LPM_EDGE_NONE);
			value[2] = MFP_EOC;
			mfp_config(value);
#endif
			/* Note: DKB uses a external LDO to power backlight */
			BU_REG_WRITE(0xd401e0cc, 0xd0c1); //GPIO123 FUN1 GPIO to enable the external ldo
			BU_REG_WRITE(0xd401e0d8, 0xd0c2); //GPIO126 FUN2 GPIO, always pull up. FUN1 work as PWM

			gpio_set_output(CRANEM_BACKLIGHT_GPIO123);
			gpio_set_output(CRANEM_BACKLIGHT_GPIO126);
			if (0 == brightness) {
    			raw_uart_log("turn off backlight\r\n"); 
				gpio_set_value(CRANEM_BACKLIGHT_GPIO123, 0);
				gpio_set_value(CRANEM_BACKLIGHT_GPIO126, 0);
			} else {
    			raw_uart_log("turn on backlight\r\n"); 
				gpio_set_value(CRANEM_BACKLIGHT_GPIO123, 1);
				gpio_set_value(CRANEM_BACKLIGHT_GPIO126, 1);
			}
			//craneM_lcd_backlight(TRUE);
			//craneM_lcd_backlight_Ctrl(brightness);
#endif
			gpio_set_output(77);
			gpio_set_value(77, 1);
	} else {

    }
}

void backlight_set_brightness(uint8_t brightness)
{
    uint8_t orig_status = g_backlight_status;
    uint8_t orig_light = g_backlight_brightness;

    if(brightness > 5)
        brightness = 5;

    if(0 == brightness){
        if(BACKLIGHT_STATUS_OFF != g_backlight_status){
            backlight_on(brightness);
            g_backlight_status = BACKLIGHT_STATUS_OFF;
            /*
            * do not save brightness value when OFF
            */
        }
    } else {
        if(BACKLIGHT_STATUS_OFF == g_backlight_status){
            g_backlight_brightness = brightness;
            backlight_on(brightness);
            g_backlight_status = BACKLIGHT_STATUS_ON;
        } else {
            if(brightness != g_backlight_brightness){
                backlight_on(brightness);
                g_backlight_brightness = brightness;
                g_backlight_status = BACKLIGHT_STATUS_ON;
            }
        }
    }

    raw_uart_log("backlight_set_brightness(%d), [%d,%d]->[%d,%d]\r\n", 
            brightness, orig_status, orig_light, g_backlight_status, g_backlight_brightness);

}
