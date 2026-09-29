#include "bot_platform.h"
#include "bot_hal_rtc.h"

int bot_hal_rtc_init(bot_rtc_dev_t *rtc)
{
    return 0;
}

int bot_hal_rtc_get_time(bot_rtc_dev_t *rtc, bot_rtc_time_t *time)
{
    if(time == NULL)
    {
        bot_printf("bot_hal_rtc_get_time fail because time is NULL\r");
        return -1;
    }
    uint32 time_stamp = 0;
    struct tm *rtc_time = NULL;
    ol_time(&time_stamp);
    time_stamp += (8 * 60 * 60);
    rtc_time = localtime(&time_stamp);
    time->year = rtc_time->tm_year + 1900 - 2000;
    time->month = rtc_time->tm_mon + 1;
    time->date  = rtc_time->tm_mday;
    time->hour  = rtc_time->tm_hour;
    time->min   = rtc_time->tm_min;
    time->sec   = rtc_time->tm_sec;
    time->weekday = rtc_time->tm_wday;
    if(time->weekday == 0)time->weekday = 7;
    return 0;
}

int bot_hal_rtc_set_time(bot_rtc_dev_t *rtc, const bot_rtc_time_t *time)
{
    if(time == NULL)
    {
        bot_printf("bot_hal_rtc_set_time fail because time is NULL\r");
        return -1;
    }
    if(time->year < 0 || time->year > 127)/* year, 0-127(2000-2127)*/
    {
        bot_printf("bot_hal_rtc_set_time fail because year value error\r");
        return -1;
    }
    if(time->month < 1 || time->month > 12)/* month, 1-12   */
    {
        bot_printf("bot_hal_rtc_set_time fail because month value error\r");
        return -1;
    }
    if(time->date < 1 || time->date > 31)/* day, 1-31     */
    {
        bot_printf("bot_hal_rtc_set_time fail because date value error\r");
        return -1;
    }
    if(time->hour < 0 || time->hour > 23)/* hours, 0-23   */
    {
        bot_printf("bot_hal_rtc_set_time fail because hour value error\r");
        return -1;
    }
    if(time->min < 0 || time->min > 59)/* minutes, 0-59 */
    {
        bot_printf("bot_hal_rtc_set_time fail because min value error\r");
        return -1;
    }
    if(time->sec < 0 || time->sec > 59)/* sconds, 0-59  */
    {
        bot_printf("bot_hal_rtc_set_time fail because sec value error\r");
        return -1;
    }
    if(time->weekday < 1 || time->weekday > 7)/* wekday, 1-7   */
    {
        bot_printf("bot_hal_rtc_set_time fail because weekday value error\r");
        return -1;
    }
    struct tm rtc_time = {0};
    rtc_time.tm_year = time->year - 1900 + 2000;
    rtc_time.tm_mon  = time->month - 1;
    rtc_time.tm_mday = time->date;
    rtc_time.tm_hour = time->hour;
    rtc_time.tm_min  = time->min;
    rtc_time.tm_sec  = time->sec;
    if(time->weekday == 7)
    {
        rtc_time.tm_wday = 0;
    }
    else
    {
        rtc_time.tm_wday = time->weekday;
    }
    uint32_t time_stamp = mktime(&rtc_time);
    ol_set_time(&time_stamp, 1, 0);
    return 0;
}

int bot_hal_rtc_deinit(bot_rtc_dev_t *rtc)
{
    return 0;
}