#ifndef __OPENCPU_PUB_DEF__
#define __OPENCPU_PUB_DEF__

#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
	///COMMON
	OL_E_NONE = 0,
	OL_E_FAIL = -1,
	OL_E_PARAM_INVALID = -2,
	OL_E_NOT_SUPPORT = -3,


	///GPIO
	OL_E_PIN_INUSE =    -200,
	OL_E_NOT_SUPPORT_STATE = -201,
	OL_E_NO_GPIO_PIN = -202,
	OL_E_INIT_FIRST = -203,
	OL_E_HAS_INITED = -204,
	OL_E_EINIT_NUM_FULL= -205,
	//PWM
	OL_E_PWM_NOT_INIT = -900,
	
	//系统错误-1    ---   -99

	//功能错误
	//adc     -100  ---  -149
	//at		-150  --   -199
	//gpio	-200 ---  -299  (包括EINT)
	//fs		-300 ---- -399
    	OL_E_FS_IS_DIRECTORY = -305,//The named file is a directory.
    	OL_E_FS_NOT_DIRECTORY = -306,//The named file is not a directory.
    	OL_E_FS_NO_DIR_ENTRY = -307,//A component of the path prefix does not name
    	//an existing directory or path is an empty string or O_CREAT is set and either 
    	//the path prefix does not exist or the path a rgument points to an empty string.
    	OL_E_FS_OPERATION_NOT_GRANTED = -308,//Operation is not granted
    	OL_E_FS_DIR_NOT_EMPTY = -309,// Directory is not empty.
    	OL_E_FS_FDS_MAX = -310,// No file descriptor is available.
    	OL_E_FS_PROCESS_FILE_MAX = -311,//open files too many for a process
    	OL_E_FS_FILE_EXIST = -312,// File has existed.
    	OL_E_FS_NO_BASENAME = -313,// The base file name (or directory name) 
    	//length is zero in the path string.
    	OL_E_FS_BAD_FD = -314,// Bad file descriptor or find descriptor.
    	OL_E_FS_NO_MORE_FILES = -315,// No more files in the specifiyed directory.
    	OL_E_FS_UNKNOWN_FILESYSTEM = -316,//The FS type is not support.
    	OL_E_FS_NOT_SUPPORT = -317,// The FS type not support.
    	OL_E_FS_NO_MORE_MEMORY = -318,// Malloc failed.
    	OL_E_FS_DISK_FULL = -319,// The disk is full,no more space to use.
    	OL_E_FS_ROOT_FULL = -320,// The count more than the max count of root entry count,
    	//that dir entry in the root dirctory.
    	OL_E_FS_PATHNAME_PARSE_FAILED = -321,// Parse the path name error.
    	OL_E_FS_READ_DIR_FAILED = -322,// Get the dir entry failed in the specifiy dirctory.
    	OL_E_FS_RENAME_DIFF_PATH = -323,// Move directory is not permitted
    	OL_E_FS_READ_SECTOR_FAILED = -324,// Read the FAT entry failed.
    	OL_E_FS_WRITE_SECTOR_FAILED = -325,// Write the FAT entry failed.
    	OL_E_FS_READ_FILE_EXCEED = -326,// Read the file exceed the end of file.
    	OL_E_FS_WRITE_FILE_EXCEED = -327,// The pos exceed the end of file when write a file.
    	OL_E_FS_FILE_TOO_MORE = -328,// The sample long name too more in a dirctory,
    	//so can't make a short file as "fo~xxx ext".the max count is 999 in a dirctory.
    	OL_E_FS_FILE_NOT_EXIST = -329,// The file not exist.
    	OL_E_FS_DEVICE_DIFF = -330,// Try to rename a file to another device.
    	OL_E_FS_NOT_REGULAR = -331,// The inode not reguler.
    	OL_E_FS_VOLLAB_IS_NULL = -332,// The inode not reguler.
    	OL_FILE_IS_OPERATING = -333,//file is opened by others
	// IIC	 -400   ----    -499
		OL_E_IIC_HAS_OPENED = -400,
		OL_E_IIC_OPEN_FIRST = -401,
		OL_E_IIC_RES_TIMEOUT = -402,
	///SPI	 -500   ------  -599
    	OL_E_SPI_CHANNO_INITED = -505,
    	OL_E_SPI_CHANNO_UNINIT = -506,
    	OL_E_SPI_CHANNO_OPENED = -507,
    	OL_E_SPI_CHANNO_NOTOPEN = -508,
	//TIMER	   -600    -----   -699
	OL_E_TIMER_NO_HANDLE  = -600,
	OL_E_TIMER_NO_TIMER_ID = -601,
	//UART      -700  -----   -799
	OL_E_UART_BAUD_NOT_SUPPORT = -705,
	OL_E_UART_PORT_NOT_SUPPORT = -706,
	OL_E_UART_CREATE_FAIL = -707,
	//WTD      -800    ------    -899
	//PWM      -900   ------    -999

	//BT       -1000 -----     -1100
	OL_E_BT_BUSY = -1000,
	OL_E_BT_TIMEOUT = -1001,
	OL_E_BT_NOT_POWERON = -1002,
	OL_E_BT_NOT_CONNECT = -1003,

	//OTA APP UPDATE  -1101 -----  -1200
	OL_E_APP_UPDATE_PACK_ERR = -1101,
    	OL_E_APP_UPDATE_PACK_STROE_ERR = -1102,
    	OL_E_APP_UPDATE_PACK_GET_ERR = -1103,
    	OL_E_APP_UPDATE_STATE_ERR = -1104,
	OL_E_MAX
}OL_ERROR_TYPE;

#ifdef __cplusplus
}
#endif

#endif
