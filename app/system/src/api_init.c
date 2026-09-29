#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "mbtk_api_init.h"


#define OPEN_FILE_MAGIC_NUM    0x87362510
#define MBTK_ARMCC     0x0
#define MBTK_GCC     0x1
#define MBTK_XIP     0x2

//magic numeber最后当做控制位
#define OPEN_FILE_MAGIC_NUM_B    0x87362510


#define OPEN_FILE_MAGIC_NUM_ARMCC_X  OPEN_FILE_MAGIC_NUM_B|MBTK_ARMCC|MBTK_XIP
#define OPEN_FILE_MAGIC_NUM_ARMCC  OPEN_FILE_MAGIC_NUM_B|MBTK_ARMCC
#define OPEN_FILE_MAGIC_NUM_GCC_X  OPEN_FILE_MAGIC_NUM_B|MBTK_GCC | MBTK_XIP
#define OPEN_FILE_MAGIC_NUM_GCC  OPEN_FILE_MAGIC_NUM_B|MBTK_GCC


typedef struct open_file_head{
    unsigned int  magic;
    unsigned int  zi_addr;
	unsigned int  zi_size;
	unsigned int  rw_addr;
	unsigned int  rw_size;
	unsigned int  ram_exec_addr;
	unsigned int  codeinram_addr;
	unsigned int  codeinram_size;
	unsigned int  codeinramexec_addr;
    void (*app_init)(open_api_table *);	
	unsigned int  stub_addr;
	unsigned int  stub_size;
	unsigned int  stub_exec;
	unsigned int  stub_c_addr;
	unsigned int  stub_c_size;
	unsigned int  stub_c_exec;
}open_file_head;

extern void mbtk_api_init_customer(void *api_table);
void mbtk_api_init(open_api_table *api_table)
{
	mbtk_api_init_customer(api_table->user_data_api);
}


extern void user_app_init(open_api_table *api_table);


#if defined(COMP_TYPE_GCC)
extern void * __rw_length;
extern void * __data_load;
extern void * __data_start;
extern void * __bss_start;
extern void * __zi_length;
extern void *__text_load;
extern void *__ro_length;
extern void *__text_start;

__attribute__ ((section(".INIT")))const open_file_head open_head  = 
	{
	#ifdef MBTK_IS_XIP
		OPEN_FILE_MAGIC_NUM_GCC_X,
	#else
		OPEN_FILE_MAGIC_NUM_GCC, 
	#endif
	(unsigned int)(&__bss_start),(unsigned int)(&__zi_length), 
	(unsigned int)(&__data_load),(unsigned int)(&__rw_length),
	(unsigned int)(&__data_start),
	(unsigned int)(&__text_load),(unsigned int)(&__ro_length),
	(unsigned int)(&__text_start),																
	user_app_init
};
#elif defined(COMP_TYPE_ARMCC)
extern unsigned int  Load$$APP_RW$$RW$$Length;
extern unsigned int  Image$$APP_RW$$RW$$Base;
extern unsigned int  Load$$APP_RW$$RW$$Base;
extern unsigned int  Image$$APP_RW$$ZI$$Base;
extern unsigned int  Image$$APP_RW$$ZI$$Length;
extern unsigned int  Image$$APP_CODE_IN_RW$$Base;
extern unsigned int  Load$$APP_CODE_IN_RW$$Length;
extern unsigned int  Load$$APP_CODE_IN_RW$$Base;

extern unsigned int  Image$$APP_STUB$$Base;
extern unsigned int  Load$$APP_STUB$$Length;
extern unsigned int  Load$$APP_STUB$$Base;
extern unsigned int  Image$$APP_STUB_C$$Base;
extern unsigned int  Load$$APP_STUB_C$$Length;
extern unsigned int  Load$$APP_STUB_C$$Base;

const open_file_head open_head __attribute__ ((section("INIT"))) = {
	
																	#ifdef MBTK_IS_XIP
																		OPEN_FILE_MAGIC_NUM_ARMCC_X,
																	#else
																		OPEN_FILE_MAGIC_NUM_ARMCC, 
																	#endif
																	(unsigned int)(&Image$$APP_RW$$ZI$$Base),(unsigned int)(&Image$$APP_RW$$ZI$$Length), 
																	(unsigned int)(&Load$$APP_RW$$RW$$Base),(unsigned int)(&Load$$APP_RW$$RW$$Length),
																	(unsigned int)(&Image$$APP_RW$$RW$$Base),
																	(unsigned int)(&Load$$APP_CODE_IN_RW$$Base),(unsigned int)(&Load$$APP_CODE_IN_RW$$Length),
																	(unsigned int)(&Image$$APP_CODE_IN_RW$$Base),
																	user_app_init,
																	(unsigned int)(&Load$$APP_STUB$$Base),(unsigned int)(&Load$$APP_STUB$$Length),
																	(unsigned int)(&Image$$APP_STUB$$Base),
																	(unsigned int)(&Load$$APP_STUB_C$$Base),(unsigned int)(&Load$$APP_STUB_C$$Length),
																	(unsigned int)(&Image$$APP_STUB_C$$Base)														
																	};
#else
#error please define comp type
#endif

