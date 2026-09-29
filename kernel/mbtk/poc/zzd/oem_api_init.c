#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "mbtk_os.h"
#include "corget_api.h"
#include "mbtk_device_api.h"


extern void mbtk_app_log(const char *fmt,...);
extern int  drv_uart_visual_write(const u8 *data, unsigned size);

#if (defined(MBTK_POC_SUPPORT_ZZD) || defined(MBTK_POC_SUPPORT_HAWK)|| defined(MBTK_POC_SUPPORT_CHAYU))

void mbtk_zzd_init_internal(void)
{
    mbtk_os_task_sleep(200);

    oem_internal_init();
    OEM_init();
}

int OEM_SendUart(char *uf, int len)
{
    mbtk_app_log("%s:%d, %s!", __func__, len,uf);
    atRespStr( 1, 0, 0, uf);
    drv_uart_visual_write(uf, len);
    return 0;
}

#endif /*MBTK_POC_SUPPORT*/