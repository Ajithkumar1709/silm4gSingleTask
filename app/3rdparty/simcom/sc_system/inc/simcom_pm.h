/** 
* @file         simcom_pm.h 
* @brief        SIMCom PMU API
* @author       dengchao
* @date         2020/5/4
* @version      V1.0.0 
* @par Copyright (c):  
*               SIMCom Co.Ltd 2003-2019
* @par History: 1:Create         
*   
*/

#ifndef __SIMCOM_PM_H__
#define __SIMCOM_PM_H__

unsigned int sAPI_ReadAdc(int channel);
unsigned int sAPI_ReadVbat(void);
void sAPI_SysPowerOff(void);
void sAPI_SysReset(void);
int sAPI_SetVddAux(unsigned int voltage);



#endif