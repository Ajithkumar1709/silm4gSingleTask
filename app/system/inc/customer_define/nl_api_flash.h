#ifndef _NL_API_FLASH_H_
#define _NL_API_FLASH_H_

/**
 * @brief    获取外部flash的设备信息
 *
 * @param < pulId >外部flash的设备ID
 * @param < pulCapacity >外部flash的容量大小，单位Byte
 * 
 * @return  = 0 - 成功  <0 - 失败
 */
INT32 nl_ext_flash_info(UINT32 * pulId, UINT32 * pulCapacity);

/**
 * @brief    读取外部FLASH指定地址的内容
 *
 * @param <faddr>指定flash的起始地址
 * @param <data>用来保存读到的数据BUFFER
 * @param <size>data的长度
 * 
 * @return  = 0 - 成功  <0 - 失败
 */
INT32 nl_ext_flash_read(UINT32 faddr, UINT8 *data,UINT32 size);

/**
 * @brief    将data内容写入内部FLASH指定地址
 *
 * @param <faddr>指定flash的起始地址
 * @param <data>将要写入flash的BUFFER
 * @param <size>data的长度
 * 
 * @return  = 0 - 成功  <0 - 失败
 */
INT32 nl_ext_flash_write(UINT32 faddr, UINT8 *data,UINT32 size);

/**
 * @brief    擦除外部FLASH
 *
 * @param <faddr>指定的flash起始地址
 * @param <size>擦除大小
 * 
 * @return  = 0 - 成功  <0 - 失败
 */
INT32 nl_ext_flash_erase(UINT32 faddr, UINT32 size);

/**
 * @brief    给外置flash挂载文件系统。需要挂载时，单独执行该函数
 *
 * @param <uladdr_start>flash内部的偏移地址，必须是0或者0x10000的整数倍。
 * @param <ulsize>需要挂载的flash空间大小，必须是0x10000的整数倍
 * @param <dir>分区名称，长度不能小于2，最大为10，且第一个字符必须以“/”开头
 * @param <spi_pin_sel>用来指定使用的是哪一组spiflash接口，与硬件连线相关：=0：使用跟LCD复用的那一组spiflash接口；=1：使用跟PCM复用的那一组spiflash接口
 * @param <format_on_fail>文件系统挂载失败是否格式化分区重新挂载：true 格式化  false 不格式化
 * @param <force_format>挂载文件系统前是否强制执行格式化：ture 执行  false 不执行
 * 
 * @return  -6 创建块设备失败  -7 尝试格式化块设备失败  -8  再次创建块设备失败  -9 文件系统强制格式化失败  -10 挂载文件系统失败  -11  尝试文件系统格式化失败  -12  再次挂载文件系统失败
 */
INT32 nl_ffsmountExtflash(UINT32 uladdr_start, UINT32 ulsize, char * dir, UINT8 spi_pin_sel, bool format_on_fail, bool force_format);

/**
 * @brief    初始化内部FLASH
 * 
 * @return  = 0 - 成功  <0 - 失败
 */
INT32 nl_inner_flash_init(void);

/**
 * @brief    读取内部FLASH指定地址的内容
 *
 * @param <faddr>指定flash的起始地址
 * @param <data>用来保存读到的数据BUFFER
 * @param <size>data的长度
 * 
 * @return  = 0 - 成功  <0 - 失败
 */
INT32 nl_inner_flash_read(UINT32 faddr, UINT8 *data,UINT32 size);

/**
 * @brief    将data内容写入内部FLASH指定地址
 *
 * @param <faddr>指定flash的起始地址
 * @param <data>将要写入flash的BUFFER
 * @param <size>data的长度
 * 
 * @return  = 0 - 成功  <0 - 失败
 */
INT32 nl_inner_flash_write(UINT32 faddr, UINT8 *data,UINT32 size);

/**
 * @brief    擦除内部FLASH
 *
 * @param <faddr>指定的flash起始地址
 * @param <size>擦除大小
 * 
 * @return  = 0 - 成功  <0 - 失败
 */
INT32 nl_inner_flash_erase(UINT32 faddr, UINT32 size);

#endif