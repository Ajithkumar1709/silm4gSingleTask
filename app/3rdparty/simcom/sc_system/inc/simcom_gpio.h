/** 
* @file         simcom_gpio.h 
* @brief        SIMCom GPIO API
* @author       dengchao
* @date         2020/5/4
* @version      V1.0.0 
* @par Copyright (c):  
*               SIMCom Co.Ltd 2003-2019
* @par History: 1:Create         
*   
*/


#ifndef __SIMCOM_GPIO_H__
#define __SIMCOM_GPIO_H__

#include "mbtk_pub_type.h"
#include "mbtk_gpio.h"

typedef void (*GPIOCallback)(void);
//typedef unsigned long UINT32;



typedef enum
{
    SC_MODULE_GPIO_NOT_ASSIGNED,
/**********************************************/     
/* Module commom GPIO handle */      
    #if defined(SIMCOM_A7600E)
    SC_MODULE_GPIO_1 = 1,
    SC_MODULE_GPIO_2 = 2,    
    SC_MODULE_GPIO_3 = 3,
    SC_MODULE_GPIO_6 = 6,
    SC_MODULE_GPIO_12 = 12,
    SC_MODULE_GPIO_14 = 14,
    SC_MODULE_GPIO_16 = 16,    
    SC_MODULE_GPIO_18 = 18,
    SC_MODULE_GPIO_22 = 22,    
    SC_MODULE_GPIO_41 = 41,
    SC_MODULE_GPIO_43 = 43,    
    SC_MODULE_GPIO_63 = 63,        
    SC_MODULE_GPIO_77 = 77,
    #elif defined(SIMCOM_A7620)
    SC_MODULE_GPIO_4 = 4,
    SC_MODULE_GPIO_5 = 5,
    SC_MODULE_GPIO_6 = 6,
    SC_MODULE_GPIO_7 = 7,
    SC_MODULE_GPIO_8 = 8, 
    #endif

/**********************************************/     
/* Module special GPIO handle */    
    SC_MODULE_DTR = 128,
    SC_MODULE_FLIGHT_MODE = 129,
    SC_MODULE_NET_STATUS = 130,
    SC_MODULE_USIM_DET = 131,
    SC_MODULE_STATUS = 132,
    SC_MODULE_RI = 133,
    SC_MODULE_DCD = 134,
    SC_MODULE_RTS = 135,
    SC_MODULE_CTS = 136,
/**********************************************/ 
}SC_Module_GPIONumbers;



typedef enum
{
	SC_GPIORC_FALSE = 0,
	SC_GPIORC_TRUE = 1,
	SC_GPIORC_LOW = 0,
	SC_GPIORC_HIGH = 1,

	SC_GPIORC_OK = 0,
    SC_GPIORC_INVALID_PORT_HANDLE = -100,
    SC_GPIORC_NOT_OUTPUT_PORT,
    SC_GPIORC_NO_TIMER,
    SC_GPIORC_NO_FREE_HANDLE,
    SC_GPIORC_AMOUNT_OUT_OF_RANGE,
    SC_GPIORC_INCORRECT_PORT_SIZE,
    SC_GPIORC_PORT_NOT_ON_ONE_REG,
    SC_GPIORC_INVALID_PIN_NUM,
    SC_GPIORC_PIN_USED_IN_PORT,
    SC_GPIORC_PIN_NOT_FREE,
    SC_GPIORC_PIN_NOT_LOCKED,
    SC_GPIORC_NULL_POINTER,
    SC_GPIORC_PULLED_AND_OUTPUT,
	SC_GPIORC_INCORRECT_PORT_TYPE,
	SC_GPIORC_INCORRECT_DEBOUNCE,
    SC_GPIORC_INCORRECT_TRANSITION_TYPE,
	SC_GPIORC_INCORRECT_DIRECTION,
	SC_GPIORC_INCORRECT_PULL,	
	SC_GPIORC_INCORRECT_INIT_VALUE,
	SC_GPIORC_WRITE_TO_INPUT
}SC_GPIOReturnCode;

typedef enum
{
    SC_GPIO_IN_PIN = 0,
    SC_GPIO_OUT_PIN = 1
}SC_GPIOPinDirection;

typedef enum
{
    SC_GPIO_PULL_DISABLE = 0,
    SC_GPIO_PULLUP_ENABLE,
    SC_GPIO_PULLDN_ENABLE
}SC_GPIOPullUpDown;

typedef enum
{
    SC_GPIO_NO_EDGE = 0,
    SC_GPIO_RISE_EDGE,
    SC_GPIO_FALL_EDGE,
    SC_GPIO_TWO_EDGE,
}SC_GPIOTransitionType;


typedef struct
{
	SC_GPIOPinDirection pinDir;
	UINT32			initLv;
	SC_GPIOPullUpDown 	pinPull;
	SC_GPIOTransitionType pinEd;
	GPIOCallback isr;
	GPIOCallback wu;
} SC_GPIOConfiguration;


typedef SC_GPIOTransitionType SC_GPIOtransitionType;

typedef void(*GPIOCallBack)(void);

SC_GPIOReturnCode sAPI_GpioSetValue(unsigned int gpio, unsigned int value);
SC_GPIOReturnCode sAPI_GpioGetValue(unsigned int gpio);
SC_GPIOReturnCode sAPI_GpioConfig(unsigned int gpio,SC_GPIOConfiguration GpioConfig);
SC_GPIOReturnCode sAPI_GpioConfigInterrupt(unsigned int gpio, SC_GPIOtransitionType type, GPIOCallBack handler);
SC_GPIOReturnCode sAPI_GpioSetDirection(unsigned int gpio, unsigned int direction);
SC_GPIOReturnCode sAPI_GpioGetDirection(unsigned int gpio);
SC_GPIOReturnCode sAPI_GpioWakeupEnable(unsigned int gpio, SC_GPIOTransitionType type);
SC_GPIOReturnCode sAPI_setPinFunction(unsigned int gpio_num, unsigned int pin_func);



#endif

