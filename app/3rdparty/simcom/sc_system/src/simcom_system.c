#include "simcom_system.h"
#include "mbtk_pmu.h"
#include "mbtk_err.h"

int sAPI_SystemSleepSet(SC_SYSTEM_SLEEP_FLAG flag)
{
    if(flag == SC_SYSTEM_SLEEP_ENABLE)
        ol_set_syssleep_status(1);
    else
        ol_set_syssleep_status(0);
    
    return 0;
}

SC_SYSTEM_SLEEP_FLAG sAPI_SystemSleepGet(void)
{
    int flag;
    flag = ol_get_syssleep_status();
    if(flag == 1)
        return SC_SYSTEM_SLEEP_ENABLE;
    else
        return SC_SYSTEM_SLEEP_DISABLE;
}

int sAPI_SystemSleepExSet(SC_SYSTEM_SLEEP_FLAG flag, unsigned char time)
{
    simcom_api_not_support();
    return 0;
}

int sAPI_SystemAlarmClock2Wakeup(unsigned long time)
{
    simcom_api_not_support();
    return 0;
}


