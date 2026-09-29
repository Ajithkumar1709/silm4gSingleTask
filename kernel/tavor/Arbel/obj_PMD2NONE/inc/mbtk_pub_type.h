/***************************************************************************
*
*                         FILENAME
*
*                Copyright (c) 2020 mbtk
*
*****************************************************************************/
#ifndef  __MBTK_PUB_BASIC_TYPE_H_
#define  __MBTK_PUB_BASIC_TYPE_H_

#include "stdbool.h"
/***************************************************************************
* Macros
***************************************************************************/
#ifndef false
#define false	0
#endif

#ifndef true
#define true	1
#endif

#ifndef NULL
#define NULL	(void *)0
#endif

#ifndef FALSE
#define FALSE		0
#endif

#ifndef TRUE
#define TRUE		1
#endif

/***************************************************************************
* Types
***************************************************************************/

typedef unsigned char				u8;
	typedef unsigned short				u16;
	typedef unsigned char				uint8;
	typedef unsigned short				uint16;
	
	typedef unsigned int				u32;
	typedef unsigned int				uint;
	typedef unsigned int				uint32;
	
	typedef unsigned long long			u64;
	typedef unsigned long long			uint64;
	
	typedef unsigned int				uint_t;
	typedef unsigned char				uint8_t;
	typedef unsigned short				uint16_t;
	typedef unsigned int				uint32_t;
	typedef unsigned long long			uint64_t;
	
	typedef unsigned int				uint_t;
	typedef unsigned char				uint_8;
	typedef unsigned short				uint_16;
	typedef unsigned int				uint_32;
	typedef unsigned long long			uint_64;
	
	typedef signed char 				int8;
	typedef signed short				int16;
	typedef signed int					int32;
	typedef signed int					int_32;
	typedef signed long long			int64;
	
	typedef signed char 				int8_t;
	typedef signed short				int16_t;
	typedef signed int					int32_t;
	typedef signed long long			int64_t;
	//typedef long						  intptr_t;
	
	typedef unsigned char				UINT8;
	typedef unsigned short				UINT16;
	typedef unsigned int				UINT;
	#ifndef MBTK_GPIO_UIN32_T
	#define MBTK_GPIO_UIN32_T
	typedef unsigned int				UINT32;
	#endif
	typedef unsigned long long			UINT64;
	typedef int 						INT;
	#ifndef MBTK_DEFINE_INT8
	#define MBTK_DEFINE_INT8
	typedef char						INT8;
	#endif
	typedef short						INT16;

	#ifndef MBTK_DEFINE_INT32
	#define MBTK_DEFINE_INT32
	typedef int 						INT32;
	#endif

	typedef long long					INT64;
	
	typedef unsigned char				U8;
	typedef unsigned short				U16;

	#ifndef MBTK_U32
	#define MBTK_U32
	typedef unsigned int				U32;
	typedef int 						S32;
	#endif
	typedef unsigned long long			U64;
	
	typedef char						S8;
	typedef short						S16;

	typedef long long					S64;
	
	typedef char						s8;
	typedef short						s16;
	typedef int 						s32;
	
	typedef unsigned int				size_t;
	
	typedef char						ascii;
	typedef unsigned char				byte;			/*	unsigned 8-bit data 	*/
	typedef unsigned short				word;			/*	unsigned 16-bit data	*/
	typedef unsigned long				dword;			/*	unsigned 32-bit data	*/
	
	typedef unsigned char				BYTE;
	typedef char						CHAR;
	typedef unsigned short				WCHAR;
	typedef unsigned short				WORD;
	#ifndef MBTK_WORD
	#define MBTK_WORD
	typedef signed int					WORD32;
	typedef unsigned int				UWORD32;
	#endif
	//typedef unsigned long				DWORD;
	
	typedef unsigned short				RESID;

	typedef float						float32;
	typedef float						FLOAT;
	typedef double						DOUBLE;
	typedef UINT8*						PUINT8;
	typedef INT32*						PINT32;
	typedef UINT16* 					PUINT16;
	typedef INT16*						PINT16;
	typedef CHAR *						PCHAR;
	typedef void*						PVOID;
	typedef char *						PS8;
	typedef unsigned char * 			PU8;
	typedef short * 					PS16; 
	typedef unsigned short *			PU16;
	typedef int *						PS32;
	typedef unsigned int *				PU32;
	typedef unsigned short				pBOOL; 
	
	typedef volatile unsigned char		REG8;
	typedef volatile unsigned short 	REG16;
	typedef volatile unsigned int		REG32;
	
	typedef unsigned char			kal_uint8;
	typedef signed char 			kal_int8;
	typedef char					kal_char;
	typedef unsigned short			kal_wchar;
	
	typedef unsigned short int		kal_uint16;
	typedef signed short int		kal_int16;
	
	typedef unsigned int			kal_uint32;
	typedef signed int				kal_int32;
	
	typedef unsigned int			HRES;
	typedef unsigned int			HAO;
	
	typedef unsigned char       u8_t;
	
	typedef unsigned short      u16_t;

//	typedef unsigned int   		u32_t; 




typedef u32 mbtk_mutex;
typedef u32 mbtk_sema;
#endif  /*__MBTK_PUB_BASIC_TYPE_H_*/

