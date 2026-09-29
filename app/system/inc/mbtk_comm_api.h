#ifndef __MBTK_COMM_API_H__
#define __MBTK_COMM_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "mbtk_pub_type.h"
#include "mbtk_os.h"

extern int op_uart_printf(const char *fmt, ...);
//////////打印


//堆内存申请和释放接口
extern void *ol_malloc(u32 num);
extern void ol_free(void *free);
extern void *ol_calloc(u32 , u32 );
extern void *ol_realloc(void * /*ptr*/, size_t /*size*/);

//#define malloc ol_malloc
//#define free ol_free
//#define calloc ol_calloc
//#define realloc ol_realloc

extern void *__wrap_malloc(size_t num);
extern void __wrap_free(void *free);
extern void *__wrap_calloc(size_t ptr, size_t size);
extern void *__wrap_realloc(void * ptr, size_t size);



/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_mem_freesize
 * DESCRIPTION 
 *  		获取heap内存剩余空间，malloc空间和系统共用
 * PARAMETERS 
 *		
 * RETURN VALUES
 *		  uint32  heap堆内存剩余空间
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern uint32_t ol_get_mem_freesize(void);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_mem_totalsize
 * DESCRIPTION 
 *  		获取heap内存总大小，malloc空间和系统共用
 * PARAMETERS 
 *		
 * RETURN VALUES
 *		  uint32  heap堆内存总大小
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern uint32_t ol_get_mem_totalsize(void);
//os 
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_modem_ver
 * DESCRIPTION 
 *  		This API is to get version of sdk
 * PARAMETERS 
 *		
 * RETURN VALUES
 *		char point to version string
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern char *ol_get_modem_ver(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_device_sn
 * DESCRIPTION 
 *  		This API is to get version of hardware
 * PARAMETERS 
 * RETURN VALUES
 *		char point to version string
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern char *ol_get_hw_ver(void);

#ifdef __cplusplus
}
#endif

#endif
