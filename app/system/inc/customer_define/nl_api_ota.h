#ifndef _NL_API_OTA_H_
#define _NL_API_OTA_H_


/**
 * @brief    主固件升级
 * 
 * @param <data>：主固件差分包数据
 * @param <len>：data的总长度
 *
 * @return  = 0 - 成功  <0 - 失败
 */
INT32 nl_firmware_handle(INT8 *data, UINT32 len);

/**
 * @brief    用户程序升级
 * 
 * @param <data>：用户程序的升级包数据
 * @param <len>：data的总长度
 *
 * @return  = 0 - 成功  <0 - 失败
 */
INT32 nl_ota_handle(INT8 *data, UINT32 len);

#endif