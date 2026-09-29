#include "bot_platform.h"
#include "bot_hal_at.h"

int bot_hal_at_send(unsigned char * cmd, unsigned int len)
{
    return 0;
}

int bot_hal_at_cb_register(bot_at_rx_cb cb)
{
    return 0;
}

int bot_hal_at_callback(unsigned char *data, unsigned int len)
{
    return 0;
}