#include "simcom_gpio.h"


SC_GPIOReturnCode sAPI_GpioSetValue(unsigned int gpio, unsigned int value)
{
    if(ol_set_pin_level(gpio, value) != 0)
        return SC_GPIORC_INVALID_PIN_NUM;
    return SC_GPIORC_OK;
}

SC_GPIOReturnCode sAPI_GpioGetValue(unsigned int gpio)
{
    mbtk_pin_level_enum level;
    if(ol_get_pin_level(gpio, &level) != 0)
        return SC_GPIORC_INVALID_PIN_NUM;
    return level;
}

SC_GPIOReturnCode sAPI_GpioConfig(unsigned int gpio, SC_GPIOConfiguration GpioConfig)
{
    mbtk_pin_config_struct config = {0};
    
    if(GpioConfig.pinPull == SC_GPIO_PULLUP_ENABLE)
        config.gpio_pull = mbtk_gpio_config_pull_high;
    else if(GpioConfig.pinPull == SC_GPIO_PULLDN_ENABLE)
        config.gpio_pull = mbtk_gpio_config_pull_low;

    if(gpio == mbtk_pin_78 || gpio == mbtk_pin_79)
        config.gpio_af_num = mbtk_gpio_config_maf1;
    else
        config.gpio_af_num = mbtk_gpio_config_maf0;
    config.gpio_edge = GpioConfig.pinEd;
    config.gpio_sleep = mbtk_gpio_config_sleep_none;

    if (ol_pin_config(gpio, &config) != 0)
        return SC_GPIORC_INVALID_PIN_NUM;
    
    if(ol_set_pin_dir(gpio, GpioConfig.pinDir) != 0)
        return SC_GPIORC_INVALID_PIN_NUM;

    if(GpioConfig.pinDir == SC_GPIO_OUT_PIN)
    {
        if(ol_set_pin_level(gpio, GpioConfig.initLv) != 0)
            return SC_GPIORC_INVALID_PIN_NUM;
        
        return SC_GPIORC_OK;
    }
    else
    {
        if(GpioConfig.isr)
        {
            if (ol_bind_pin_irq_callback(gpio, GpioConfig.isr) != 0)
                return SC_GPIORC_INVALID_PIN_NUM;
            
            if (ol_enable_pin_edge_detect(gpio, GpioConfig.pinEd) != 0)
                return SC_GPIORC_INVALID_PIN_NUM;
            
        }
        else if(GpioConfig.wu)
        {
            if(ol_pin_bind_wakeup_callback(gpio, GpioConfig.wu) != 0)
                return SC_GPIORC_INVALID_PIN_NUM;

            if(ol_enable_pin_wakeup_edge_detect(gpio, mbtk_gpio_config_edge_both) != 0)
                return SC_GPIORC_INVALID_PIN_NUM;
            
        }
        return SC_GPIORC_OK;
    }
}

SC_GPIOReturnCode sAPI_GpioConfigInterrupt(unsigned int gpio, SC_GPIOtransitionType type, GPIOCallBack handler)
{
    if (ol_bind_pin_irq_callback(gpio, handler) != 0)
    {
        return SC_GPIORC_INVALID_PIN_NUM;
    }
    
    if (ol_enable_pin_edge_detect(gpio, type) != 0)
    {
        return SC_GPIORC_INVALID_PIN_NUM;
    }
    return SC_GPIORC_OK;
}

SC_GPIOReturnCode sAPI_GpioSetDirection(unsigned int gpio, unsigned int direction)
{
    if (ol_set_pin_dir(gpio, direction) != 0)
        return SC_GPIORC_INVALID_PIN_NUM;
    
    return SC_GPIORC_OK;
}

SC_GPIOReturnCode sAPI_GpioGetDirection(unsigned int gpio)
{
    mbtk_pin_dir_enum direction;
        
    if (ol_get_pin_dir(gpio, &direction) != 0)
        return SC_GPIORC_INVALID_PIN_NUM;
    
    return direction;
}

SC_GPIOReturnCode sAPI_GpioWakeupEnable(unsigned int gpio, SC_GPIOTransitionType type)
{
    if (ol_enable_pin_edge_detect(gpio, type) != 0)
        return SC_GPIORC_INVALID_PIN_NUM;

    return SC_GPIORC_OK;
}

SC_GPIOReturnCode sAPI_setPinFunction(unsigned int gpio_num, unsigned int pin_func)
{
    mbtk_pin_config_struct config = {0};
    
    config.gpio_pull = mbtk_gpio_config_pull_low;
    config.gpio_edge = mbtk_gpio_config_edge_none;
    config.gpio_af_num = pin_func;
    config.gpio_sleep = mbtk_gpio_config_sleep_none;

    if (ol_pin_config(gpio_num, &config) != 0)
        return SC_GPIORC_INVALID_PIN_NUM;
    
    return 0;
}


