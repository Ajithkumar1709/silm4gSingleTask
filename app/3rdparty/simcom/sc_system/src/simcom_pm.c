#include "simcom_pm.h"
#include "mbtk_pmu.h"

unsigned int sAPI_ReadAdc(int channel);
unsigned int sAPI_ReadVbat(void);
void sAPI_SysPowerOff(void);
void sAPI_SysReset(void)
{
    ol_power_reset();
}
int sAPI_SetVddAux(unsigned int voltage);
